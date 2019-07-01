#ifndef REDIR_H
# define REDIR_H

# include "./command.h"

/* Values for flags argument to do_redirections */
# define RX_ACTIVE 0x01 /* do it; don't just go through the motions */
# define RX_UNDOABLE 0x02 /* make a list to undo these redirections */
# define RX_CLEXEC 0x04 /* set close-on-exec for opened fds > 2 */
# define RX_INTERNAL 0x08
# define RX_USER 0x10
# define RX_SAVCLEXEC 0x20 /* set close-on-exec off in restored fd even though saved on has it on */
# define RX_SAVEFD 0x40 /* fd ussed to save another even if < SHELL_FD_BASE */

void	redirection_error(t_redir *r, int flags);
int		do_redirections(t_redir *r, int flags);
char	*redirection_expand(t_wdtk *w);
int		stdin_redirects(t_redir *r);

#endif
