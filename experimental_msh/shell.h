#ifndef SHELL_H
# define SHELL_H

# ifdef HAVE_CONFIG_H
#  include "config.h"
#  include "bashjmp.h"
# endif
# include "arrayfunc.h"
# include "command.h"
# include "dispose_cmd.h"
# include "error.h"
# include "externs.h"
# include "general.h"
# include "make_cmd.h"
# include "maxpath.h"
# include "ocache.h"
# include "pathnames.h"
# include "quit.h"
# include "sig.h"
# include "subst.h"
# include "syntax.h"
# include "unwind_prot.h"
# include "variables.h"

extern int g_eof_reached; /* EOF_reached */

# define NO_PIPE -1
# define REDIRECT_BOTH -2

# define NO_VARIABLE -1

/* Values that can be returned by execute_command(). */
# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0

/* Usage messages by builtins result in a return status of 2. */
# define EX_BADUSAGE 2

# define EX_MISCERROR 2

/* Special exit statuses used by the shell, internally and externally. */
# define EX_RETRYFAIL 124
# define EX_WEXPCOMSUB 125
# define EX_BINARY_FILE 126
# define EX_NOEXEC 126
# define EX_NOINPUT 126
# define EX_NOTFOUND 127

# define EX_SHERRBASE 256 /* all special error values are > this. */

# define EX_BADSYNTAX 257 /* shell syntax error */
# define EX_USAGE 258 /* syntax error in usage */
# define EX_REDIRFAIL 259 /* redirection failed */
# define EX_BADASSIGN 260 /* variable assignment error */
# define EX_EXPFAIL 261 /* word expansion failed */
# define EX_DISKFALLBACK 262 /* fall back to disk command from builtin */

/* Flag values that control parameter pattern substitution. */
# define MATCH_ANY 0x000
# define MATCH_BEG 0x001
# define MATCH_END 0x002

# define MATCH_TYPEMASK 0x003

# define MATCH_GLOBREP 0x010
# define MATCH_QUOTED 0x020
# define MATCH_ASSIGNRHS 0x040
# define MATCH_STARSUB 0x080

/* Some needed external declarations. */
extern char		**g_shell_environment;
extern t_wlst	*g_rest_of_args;

/* Generalized global variables. */
extern char		*g_command_execution_string;

extern int		g_debugging_mode;
extern int		g_executing, g_login_shell;
extern int		g_interactive, g_interactive_shell;
extern int		g_startup_state;
extern int		g_reading_shell_script;
extern int		g_shell_initialized;
extern int		g_shell_argv_initialized;
extern int		g_subshell_environment;
extern int		g_current_command_number;
extern int		g_indirection_level;
extern int		g_shell_compatibility_level;
extern int		g_running_under_emacs;

extern int		g_posixly_correct;
extern int		g_no_line_editing;

extern char		*g_shell_name;
extern char		*g_current_host_name;

extern int		g_subshell_argc;
extern char		**g_subshell_argv;
extern char		**g_subshell_envp;

/* variables managed using shopt */
extern int		g_hup_on_exit;
extern int		g_check_jobs_at_exit;
extern int		g_autocd;
extern int		g_check_window_size;

/* from version.c */
extern int		g_build_version, g_patch_level;
extern char		*g_dist_version, *g_release_status;

extern int		g_locale_mb_cur_max;
extern int		g_locale_utf8locale;

/* Structure to pass around that holds a bitmap of file descriptors
to close, and the size of that structure. Used it execute_cmd.c. */
typedef struct fd_bitmap t_fdbmp;
struct fd_bitmap
{
	int		size;
	char	*bitmap;
};

# define FD_BITMAP_SIZE 32

# define CTLESC '\001'
# define CTLNUL '\177'

/* Information about the current user. */
struct user_info
{
	uid_t	uid, euid;
	gid_t	gid, egid;
	char	*user_name;
	char	*shell; /* shell from the password file */
	char	*home_dir;
};

extern struct user_info current_user;

# define HEREDOC_MAX 16

/* Structure in which to save partial parsing state when doing things like
PROMPT_COMMAND and bash_execute_unix_command execution. */
typedef struct s_sh_parser_state
{
	/* parsing state */
	int	parser_state;
	int	*token_state;

	char *token;
	int toke_buffer_size;

	/* input line state -- line number saved elsewhere */
	int input_line_terminator;
	int eof_encountered;

	char **prompt_string_pointer;

	/* history state affecting or modified by the parser */
	int current_command_line_count;
	int remember_on_history;
	int history_expansion_inhibited;

	/* execution state possibly modified by the parser */
	int last_command_exit_value;
	t_array *pipestatus;
	t_sh_builtin_func *last_shell_builtin, *this_shell_builtin;

	/* flags state affecting the parser */
	int expand_aliases;
	int echo_input_at_read;
	int need_here_doc;
	int here_doc_first_line;

	/* structures affecting the parser */
	t_redir *redir_stack[HEREDOC_MAX];
} t_sh_parser_state;

#endif
