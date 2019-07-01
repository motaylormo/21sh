#ifndef MAKECMD_H
# define MAKECMD_H

# include "stdc.h"

extern int here_doc_first_line;

extern void cmd_init(void);

extern t_wdtk *alloc_word_desc(void);
extern t_wdtk *make_bare_word(const char *str);
extern t_wdtk *make_word_flags(t_wdtk *wd, const char *str);
extern t_wdtk *make_word(const char *str);
extern t_wdtk *make_word_from_token(int tk);

extern t_wlst *make_word_list(t_wdtk *wd, t_wlst *lst);

#define ADD_STRING_TO_LIST(s, l) make_word_list(make_word(s), (l))

extern t_cmd *make_command(enum e_cmdtype type, t_simple_com *simpc);
extern t_cmd *command_connect(t_cmd *cmd1, t_cmd *cmd2, int flags);
extern t_cmd *make_for_command(t_wdtk *wd, t_wlst *wl, t_cmd *cmd, int flags);
extern t_cmd *make_group_command(t_cmd *cmd);
extern t_cmd *make_case_command(t_wdtk *wd, t_pattern_list *plst, int flags);
extern t_pattern_list *make_pattern_list(t_wlst *wl, t_cmd *cmd);
extern t_cmd *make_if_command(t_cmd *cmd1, t_cmd *cmd2, t_cmd *cmd3);
extern t_cmd *make_while_command(t_cmd *cmd1, t_cmd *cmd2);
extern t_cmd *make_until_command(t_cmd *cmd1, t_cmd *cmd2);
extern t_cmd *make_bare_simple_command(void);
extern t_cmd *make_simple_command(t_rdelm elm, t_cmd *cmd);
extern void make_here_document(t_redir *redir, int flags);
extern t_redir *make_redirection(t_rdtgt rd, enum r_instruction ri, t_rdtgt sd, int flags);
extern t_cmd *make_function_def(t_wdtk *wd, t_cmd *cmd, int fl1, int fl2);
extern t_cmd *clean_simple_command(t_cmd *cmd);

extern t_cmd *make_arith_command(t_wlst *wl);

extern t_cmd *make_select_command(t_wdtk *wd, t_wlst *wl, t_cmd *cmd, int flags);

# if defined(COND_COMMAND)
extern t_cond_cmd *make_cond_node(int h, t_wdtk *wd, t_cond_cmd *cd1, t_cond_com *cd2);
extern t_cmd *make_cond_command(t_cond_com *cond);
# endif

extern t_cmd *make_arith_for_command(t_wlst *wl, t_cmd *cmd, int flags);

extern t_cmd *make_subshell_command(t_cmd *cmd);
extern t_cmd *make_coproc_command(char *str, t_cmd *cmd);

extern t_cmd *connect_async_list(t_cmd *l1, t_cmd *l2, int flags);

#endif
