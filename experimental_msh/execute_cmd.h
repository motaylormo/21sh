#ifndef EXECUTE_CMD_H
# define EXECUTE_CMD_H

# if defined(ARRAY_VARS)
typedef struct s_func_array_state t_func_array_state;
struct s_func_array_state
{
	t_array *funcname_a;
	t_shvar *funcname_v;
	t_array *source_a;
	t_shvar *source_v;
	t_array *lineno_a;
	t_shvar *lineno_v;
};
# endif

/* Placeholder for later expansion to include more execution state */
/* XXX - watch out for pid_t */
typedef struct s_execstate t_execstate;
struct s_execstate
{
	pid_t	pid;
	int		subshell_env;
};

/* Variables declared in execute_cmd.c, used by many other files */
extern int return_catch_flag;
extern int return_catch_value;
extern volatile int last_command_exit_value;
extern int last_command_exit_signal;
extern int builtin_ignoring_errexit;
extern int executing_builtin;
extern int executing_list;
extern int comsub_ignore_return;
extern int subshell_level;
extern int match_ignore_case;
extern int executing_command_builtin;
extern int funcnext, funcnest_max;
extern int evalnext, evalnext_max;
extern int sourcenest, sourcenext_max;
extern int stdin_redir;
extern int line_number_for_err_trap;

extern char *the_printed_command_execpt_trap;

extern char *this_command_name;
extern t_shvar *this_shell_function;

/* Functions declared in execute_cmd.c, used by many other files */

extern struct fd_bitmap *new_fd_bitmap(int s);
extern void dispose_fd_bitmap(struct fd_bitmap *f);
extern void close_fd_bitmap(struct fd_bitmap *f);
extern int executing_line_number(void);
extern int execute_command(t_command *cmd);
extern int execute_command_internal(t_command *cmd, int i, int j, int k, struct fd_bitmap *f);
extern int shell_execve(char *name, char **argv, char **envp);
extern void setup_async_signals(void);

extern void undo_partial_redirects(void);
extern void dispose_partial_redirects(void);
extern void dispose_exec_redirects(void);

extern int execute_shell_function(t_shvar *v, t_wlst *w);

extern struct coproc *getgoprocbypid(pid_t pid);
extern struct coproc *getcoprocbyname(const char *name);

extern void coproc_init(struct coproc *c);
extern struct coproc *coproc_alloc(char *name, pid_t pid);
extern void coproc_dispose(struct coproc *c);
extern void coproc_flush(void);
extern void coproc_close(struct coproc *c);
extern void coproc_closeall(void);
extern void coproc_reap(void);
extern pid_t coproc_active(void);

extern void coproc_rclose(struct coproc *c, int f);
extern void coproc_wclose(struct coproc *c, int f);
extern void coproc_fdclose(struct coproc *c, int f);

extern void coproc_checkfd(struct coproc *c, int fd);
extern void coproc_fdchk(int fd);

extern void coproc_pidchk(pid_t pid, int f);

extern void coproc_fdsave(struct coproc *c);
extern void coproc_fdrestore(struct coproc *c);

extern void coproc_setvars(struct coproc *c);
extern void coproc_unsetvars(struct coproc *c);

# if defined(PROCESS_SUBSTITUTION)
extern void close_all_files(void);
# endif

# if defined(ARRAY_VARS)
extern void restore_funcarray_state(struct s_func_array_state *fas);
# endif

#endif
