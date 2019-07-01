#ifndef QUIT_H
# define QUIT_H

# include "sig.h" /* for sig_atomic_t */

/* Non-zero means SIGINT has already occurred. */
extern volatile sig_atomic_t interrupt_state;
extern volatile sig_atomic_t terminating_signal;

/* Macro to call a great deal. SIGINT just sets the interrupt_state variable.
   When it is safe, put QUIT in the code, and the "interrupt" will take
   place. The same scheme is used for terminating signals (e.g., SIGHUP)
   and the terminating_signal variable. That calls a function which will
   end up exiting the shell. */
# define QUIT \
	do { \
		if (terminating_signal) termsig_handler(terminating_signal); \
		if (interrupt_state) throw_to_top_level(); \
	} while (0)

# define CHECK_ALRM \
	do { \
		if (sigalrm_seen) \
			sh_longjmp(alrmbuf, 1); \
	} while (0)

# define SETINTERRUPT interrupt_state = 1
# define CLRINTERRUPT interrupt_state = 0

# define ADDINTERRUPT interrupt_state++
# define DELINTERRUPT interrupt_state--

# define ISINTERRUPT interrupt_state != 0

/* The same sort of thing, this time just for signals that would ordinarily
   casue the shell to terminate. */
# define CHECK_TERMSIG \
	do { \
		if (terminating_signal) termsig_handler(terminating_signal); \
	} while (0)

# define LASTSIG() (terminating_signal ? terminating_signal : (interrupt_state ? SIGINT : 0))

# define CHECK_WAIT_INTR \
	do { \
		if (wait_intr_flag && wait_signal_recieved && this_shell_builtin && (this_shell_builtin == wait_builtin)) \
			sh_longjmp(wait_intr_buf, 1); \
	} while (0)

# define RESET_SIGTERM \
	do { \
		sigterm_recieved = 0; \
	} while (0)

# define CHECK_SIGTERM \
	do { \
		if (sigterm_recieved) termsig_handler(SIGTERM); \
	} while (0)

#endif
