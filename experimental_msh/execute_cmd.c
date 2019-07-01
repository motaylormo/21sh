#if 1
#if defined(HAVE_SYS_TIMES_H) && defined(HAVE_TIMES)
# include <sys/times.h>
#endif
#include <errno.h>
#if !defined(errno)
extern int errno;
#endif
#define NEED_FPURGE_DECL
#define NEED_SH_SETLINEBUF_DECL
#include "bashansi.h"
#include "bashintl.h"
#include "memalloc.h"
#include "shell.h"
#include <y.tab.h> /* use <...> so we pick it up from the build directory */
#include "parser.h"
#include "flags.h"
#include "builtins.h"
#include "hashlib.h"
#include "jobs.h"
#include "execute_cmd.h"
#include "findcmd.h"
#include "redir.h"
#include "trap.h"
#include "pathexp.h"
#include "hashcmd.h"
#if defined(COND_COMMAND)
# include "test.h"
#endif
#include "builtins/common.h"
#include "builtins/builtext.h" /* list of builtins */
#include "builtins/getopt.h"
#include <glob/strmatch.h>
#include <tilde/tilde.h>
#if defined(BUFFERED_INPUT)
# include "input.h"
#endif
#if defined(ALIAS)
# include "alias.h"
#endif
#if defined(HISTORY)
# include "bashhist.h"
#endif
#if defined(HAVE_MBSTR_H) && defined(HAVE_MBSCHR)
# include <mbstr.h>
#endif

extern int command_string_index;
extern char *the_printed_command;
extern time_t shell_start_time;

extern int close(int fd);

/* Static functions defined and used in this file. */
static void close_pipes(int a, int b);
static void do_piping(int a, int b);
static void bind_lastarg(char *arg);
static int shell_control_structure(enum e_cmdtype ct);
static void cleanup_redirects(t_redir *rd);

#if defined(JOB_CONTROL)
static int restore_signal_mask(sigset_t *s);
#endif

static void async_redirect_stdin(void);

static int builtin_status(int b);

static int execute_for_command(t_for_com *fc);
#if defined(SELECT_COMMAND)
static int displen(const char *l);
static int print_index_and_element(int a, int b, t_wlst *w);
static void indent(int a, int b);
static void print_select_list(t_wlst *w, int a, int b, int c);
static char *select_query(t_wlst *w, int a, char *s, int b);
static int execute_select_command(t_select_com *sc);
#endif
#if defined(DPAREN_ARITHMETIC)
static int execute_arith_command(t_arith_com *ac);
#endif
#if defined(COND_COMMAND)
static int execute_cond_node(t_cond_com *cn);
static int execute_cond_command(t_cond_com *cc);
#endif
#if defined(COMMAND_TIMING)
static int mkfmt(char *fmt, int a, int b, time_t t, int c);
static void print_formatted_time(FILE *fp, char *format, time_t syst, int sysi,
								 time_t usrt, int usri,
								 time_t totalt, int totali, int flags);
static int time_command(t_cmd *cmd, int a, int b, int c, struct fd_bitmap *fds);
#endif
#if defined(ARITH_FOR_COMMAND)
static intmax_t eval_arith_for_expr(t_wlst *w, int *result);
static int execute_arith_for_command(t_arith_for_com *afc);
#endif
static int execute_case_command(t_case_com *cac);
static int execute_while_command(t_while_com *wc);
static int execute_until_command(t_while_com *wc);
static int execute_while_or_until(t_while_com *wc, int w_or_u);
static int execute_if_command(t_if_com *ic);
static int execute_null_command(t_redir *r, int a, int b, int c);
static void fix_assignment_words(t_wlst *w);
static int execute_simple_command(t_simple_com *simpc, int a, int b, int c, struct fd_bitmap *fds);
static int execute_builtin(t_sh_builtin_func *builtin, t_wlst *w, int a, int b);
static int execute_function(t_shvar *shv, t_wlst *w, int a, struct fd_bitmap *fds, int b, int c);
static int execute_builtin_or_function(t_wlst *w, t_sh_builtin_func *blt, t_shvar *v,
									   t_redir *rd, struct fd_bitmap *fds, int borf);
static void execute_subshell_builtin_or_function(t_wlst *w,
												 t_redir *rd,
												 t_sh_builtin_func *blt,
												 t_shvar *shv,
												 int a, int b, int c,
												 struct fd_bitmap *fds,
												 int which);
static int execute_disk_command(t_wlst *w, t_redir *rd, char *disk,
								int a, int b, int c, struct fd_bitmap *fds, int d);
static char *getinterp(char *str, int a, int *ap);
static void initialize_subshell(void);
static int execute_in_subshell(t_cmd *cmd, int a, int b, int c, struct fd_bitmap *fds);
#if defined(COPROCESS_SUPPORT)
static void coproc_setstatus(struct coproc *cp, int status);
static int execute_coproc(t_cmd *cmd, int a, int b, struct fd_bitmap *fds);
#endif

static int execute_pipeline(t_cmd *cmd, int a, int b, int c, struct fd_bitmap *fds);
static int execute_connection(t_cmd *cmd, int a, int b, int c, struct fd_bitmap *fds);
static int execute_intern_function(t_wdtk *wd, t_function_def *func);

/* Set to 1 if fd 0 was the subject of redirection to a subshell. Global
   so that reader_loop can set it to zero before executing a command. */
int stdin_redir;

/* The name of the command that is currently being executed.
   `test' needs this, for example. */
char *this_command_name;

/* The printed representation of the currently-executing command (same as
   the_printed_command), except when a trap is being executed. Useful for
   a debugger to know where exactly the program is currently executing. */
char *the_printed_command_except_trap;

/* For catching RETURN in a function. */
int return_catch_flag;
int return_catch_value;
procenv_t return_catch;

/* The value returned by the last synchronous command. */
volatile int last_command_exit_value;

/* Whether or not the last command (corresponding to last_command_exit_value)
   was terminated by a signal, and, if so, which one. */
int last_command_exit_signal;

/* Are we currently ignoring the -e option for the duration of a builtin's
   execution? */
int builtin_ignoring_errexit = 0;

/* The list of redirections to perform which will undo the redirections
   that I made in the shell. */
t_redir *redirection_undo_list = NULL;

/* The list of redirections to perform which will undo the internal
   redirections performed by the `exec' builtin. These are redirections
   that must be undone wven when exec discards redirection_undo_list. */
t_redir *exec_redirection_undo_list = NULL;

/* When greated than zero, value is the `level' of builtins we are
   currently executing (e.g. `eval echo a' would have it set to 2). */
int executing_builtin = 0;

/* Non-zero if we are executing a command list (a;b;c, etc.) */
int executing_list = 0;

/* Non-zero if failing commands in a command substution should not exit the
   shell even it -e is set. Used to pass the CMD_IGNORE_RETURN flag down to
   commands run in command substitutions by parse_and_execute. */
int comsub_ignore_return = 0;

/* Non-zero if we have just forked and are currently running in a subshell
   environment. */
int subshell_environment;

/* Count of nexted subshells, like SHLVL. Available via $MSH_SUBSHELL */
int subshell_level = 0;

/* Currently-executing shell function. */
t_shvar *this_shell_function;

/* If non-zero, matches in case and [[ ... ]] are case-insensitive */
int match_ignore_case = 0;

int executing_command_builtin;

struct stat SB; /* used for debugging */

static int special_builtin_failed;

static t_cmd *currently_executing_command;

/* The line number that the currently executing function starts on. */
static int function_line_number;

/* XXX - set to 1 if we're running the DEBUG trap and we want to show the line
   number containing the function name. Used by executing_line_number to
   report the correct line number. Kind of a hack. */
static int showing_function_line;

static int connection_count;

/* $LINENO ($TWSH_LINENO) for use by an ERR trap. Global so parse_and_execute
   can save and restore it. */
int line_number_for_err_trap;

/* A sort of function nesting level counter */
int funcnest = 0;
int funcnest_max = 0;

int evalnest = 0;
int evalnest_max = EVALNEST_MAX;

int sourcenest = 0;
int sourcenest_max = SOURCENEST_MAX;

volatile int from_return_trap = 0;

int lastpipe_opt = 0;

struct fd_bitmap *current_fds_to_close = (struct fd_bitmap*)NULL;

#define FD_BITMAP_DEFAULT_SIZE 32

/* Functions to allocate and deallocate the structures used to pass
   information from the shell to its children about file descriptors
   to close. */
struct fd_bitmap	*new_fd_bitmap(int size)
{
	struct fd_bitmap *ret;

	ret = malloc(sizeof(*ret));
	ret->size = size;
	if (size)
	{
		ret->bitmap = malloc(size);
		ft_memset(ret->bitmap, '\0', size);
	}
	else
		ret->bitmap = NULL;
	return (ret);
}

void dispose_fd_bitmap(struct fd_bitmap *fdbp)
{
	free(fdbp->bitmap);
	free(fdbp);
}

void	close_fd_bitmap(struct fd_bitmap *fdbp)
{
	register int i;

	if (fdbp)
	{
		i = -1;
		while (++i < fdbp->size)
		{
			if (fdbp->bitmap[i])
			{
				close(i);
				fdbp->bitmap[i] = 0;
			}
		}
	}
}

/* Return the line number of the currently executing command. */
int		executing_line_number(void)
{
	if (executing && showing_function_line == 0 &&
		(variable_context == 0 || interactive_shell == 0) &&
		currently_executing_command)
	{
		if (currently_executing_command->type == cm_cond)
			return (currently_executing_command->value.ccond->line);
		if (currently_executing_command->type == cm_arith)
			return (currently_executing_command->value.carith->line);
		if (currently_executing_command->type == cm_arith_for)
			return (currently_executing_command->value.carithfor->line);
		return (line_number);
	}
	else
		return (line_number);
}

/* Execute the command passed in COMMAND. COMMAND is exactly what
   read_command() places into GLOBAL_COMMAND. See "command.h" for the
   details of the command structure.

   EXECUTION_SUCCESS or EXECUTION_FAILURE are the only possible
   return values. Executing a command with nothing in it returns
   EXECUTION SUCCESS. */
int			execute_commant(t_cmd *command)
{
	struct fd_bitmap	*bitmap;
	int					result;

	current_fds_to_close = (struct fd_bitmap*)NULL;
	bitmap = new_fd_bitmap(FD_BITMAP_DEFAULT_SIZE);
	begin_unwind_frame("execute-command"); /* whomst */
	add_unwind_protect(dispose_fd_bitmap, (char*)bitmap);
	/* Just do the command, but not asynchronously. */
	result = execute_command_internal(command, 0, NO_PIPE, NO_PIPE, bitmap);
	dispose_fd_bitmap(bitmap);
	discard_unwind_frame("execute-command"); /* thoumst */
#if defined(PROCESS_SUBSTITUTION)
	/* don't unlink fifos if we're in a shell function; wait until the function
	   returns. */
	if (variable_context == 0 && executing_list == 0)
		unlink_fifo_list();
#endif
	QUIT;
	return (result);
}

/* Return 1 if TYPE is a shell control structure type. */
static int		shell_control_structure(enum e_cmdtype type)
{
	switch (type)
	{
	case cm_arith_for:
	case cm_select:
	case cm_arith:
	case cm_cond:
	case cm_case:
	case cm_while:
	case cm_until:
	case cm_if:
	case cm_for:
	case cm_group:
	case cm_function_def:
		return (1);
	default:
		return (0);
	}
}

/* A function to use to unwind_protect the redirection undo list
   for loops. */
static void		cleanup_redirects(t_redir *list)
{
	do_redirections(list, RX_ACTIVE);
	dispose_redirects(list);
}

void			undo_partial_redirects(void)
{
	if (redirection_undo_list)
	{
		cleanup_redirects(redirection_undo_list);
		redirection_undo_list = (t_redir*)NULL;
	}
}

void			dispose_exec_redirects(void)
{
	if (exec_redirection_undo_list)
	{
		dispose_redirects(exec_redirection_undo_list);
		exec_redirection_undo_list = (t_redir*)NULL;
	}
}

void			dispose_partial_redirects(void)
{
	if (redirection_undo_list)
	{
		dispose_redirects(redirection_undo_list);
		redirection_undo_list = (t_redir*)NULL;
	}
}

#if defined(JOB_CONTROL)
/* A function to restore the signal mask to its proper value when the shell
   is interrupted or errors occur while acreating a pipeline. */
static int		restore_signal_mask(sigset_t *set)
{
	return (sigprocmask(SIG_SETMASK, set, (sigset_t*)NULL));
}
#endif

#ifdef DEBUG
/* A debugging function that can be called from gdb/lldb, for instance. */
void			open_files(void)
{
	register int	i;
	int				f;
	int				fd_table_size;

	fd_table_size = getdtablesize();
	ft_dprintf(2, "pid %ld open files:", (long)getpid());
	i = 2;
	while (++i < fd_table_size)
	{
		if ((f = fcntl(i, F_GETFD, 0)) != -1)
			ft_dprintf(2, " %d (%s)", i, f ? "close" : "open");
	}
	ft_dprintf(2, "\n");
}
#endif

static void		async_redirect_stdin(void)
{
	int fd;

	fd = open("/dev/null", O_RDONLY);
	if (fd > 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	else if (fd < 0)
		internal_error("cannot redirect standard input from /dev/null: %s", strerror(errno));
}

#define DESCRIBE_PID(pid) do { if (interactive) describe_pid(pid); } while (0)

/* Execute the command passed in COMMAND, perhaps doing it asynchronously.
   COMMAND is exactly what read_command() places into GLOBAL_COMMAND.
   ASYNCHRONOUS, if non-zero, says to do this command in the background.
   PIPE_IN and PIPE_OUT are file descriptors saying where input comes
   from and where it goes. They can have the value of NO_PIPE, which means
   I/O is stdin/stdout.
   FDS_TO_CLOSE is a list of file descriptors to close once the child has
   been forked. This list often contains the unusable sides of pipes, etc.

   EXECUTION_SUCCESS or EXECUTION_FAILURE are the only possible
   return values. Executing a command with nothing in it returns
   EXECUTION_SUCCESS. */
int				execute_command_internal(t_cmd *command, int asynchronous,
										 int pipe_in, int pipe_out, struct fd_bitmap *fds_to_close)
{
	int exec_result, user_subshell, invert, ignore_return, was_error_trap;
	t_redir *my_undo_list, *exec_undo_list;
	char *tcmd;
	volatile int save_line_number;
#if defined(PROCESS_SUBSTITUTION)
	volatile int ofifo, nfifo, osize, saved_fifo;
	volatile char *ofifo_list;
#endif

	if (breaking || continuing)
		return (last_command_exit_value);
	if (command == NULL || read_but_dont_execute)
		return (EXECUTION_SUCCESS);
	QUIT;
	run_pending_traps();
	currently_executing_command = command;
	invert = (command->flags & CMD_INVERT_RETURN) != 0;
	/* If we're inverting the return value and `set -e' has been executed,
	   we don't want a failing command to inadvertently cause the shell
	   to exit. */
	if (exit_immediately_on_error && invert) /* XXX */
		command->flags |= CMD_IGNORE_RETURN; /* XXX */
	exec_result = EXECUTION_SUCCESS;
	/* If a command was being explicitly run in a subshell, or if it is
	   a shell control-structure, and it has a pipe, then we do the command
	   in a subshell. */
	if (command->type == cm_subshell && (command->flags & CMD_NO_FORK))
		return (execute_in_subshell(command, asynchronous, pipe_in, pipe_out, fds_to_close));
	// TODO: leaving off at execute_cmd.c:598
}
