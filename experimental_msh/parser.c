#include "command.h"

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* #include "libft.h" */

/*
** parser.c --- TODO Notes 21sh
** Don't worry about multiline input yet
** needs to take a line of input such as:
** $ mkdir test ; cd test ; ls -a ; ls | cat | wc -c > output ; cat output
** .	..
**        5
** $
** parse into `struct s_element' or other useful parsing struct
struct	s_element {
	t_wdtk	*word;
	t_redir	*redirect;
}
** translate to struct s_command
struct	s_command {
	enum e_cmdtype	type;
	int				flags;
	int				line;
	t_redir			*redirects;
	t_cmd_val		value;
}
{	.word="mkdir" .args={"test"} .type=cm_simple .rhs={
	.word="cd" .args={"test"} .type=cm_simple .rhs={
	.word="ls" .args={"-a"} .type=cm_simple .rhs={
	.word=NULL .args=NULL .type=cm_connection .}}}}}}

----------
linked list of commands with arguments
typedef struct s_cmd {
	struct s_cmd *next;
	int type;
	WORD_TOKEN *command;
	WORD_TOKEN **arguments;
	redirections?
}
*/

/*
**
** CWORD		- nothing special; an ordinary character
** CSHMETA		- shell meta character
** CSHBRK		- shell break character
** CBACKQ		- back quote
** CQUOTE		- shell quote character
** CSPECL		- special character that needs quoting
** CEXP			- shell expansion character
** CBSDQUOTE	- characters escaped by backslash in double quotes
** CBSHDOC		- characters escaped by backslash in here doc
** CGLOB		- globbing characters
** CXGLOB		- extended globbing characters
** CXQUOTE		- cquote + backslash
** CSPECVAR		- single-character shell variable name
** CSUBSTOP		- values of OP for ${word[:]OPstuff}
** CBLANK		- whitespace (blank) character
*/

# define CWORD		0x0000
# define CSHMETA	0x0001
# define CSHBRK		0x0002
# define CBACKQ		0x0004
# define CQUOTE		0x0008
# define CSPECL		0x0010
# define CEXP		0x0020
# define CBSDQUOTE	0x0040
# define CBSHDOC	0x0080
# define CGLOB		0x0100
# define CXGLOB		0x0200
# define CXQUOTE	0x0400
# define CSPECVAR	0x0800
# define CSUBSTOP	0x1000
# define CBLANK		0x2000

# define REVLIST(l,t) ((l && l->next) ? (t)list_reverse((t_glist*)l) : (t)(l))
# define STRSAV(x) strcpy(malloc(1 + strlen(x)), (x))
# define STRDUP(x) ((x) ? strcpy(malloc(1+strlen(x)), (x)) : (char*)NULL)

typedef struct s_glist	t_glist;
struct		s_glist
{
	struct s_glist	*next;
};

int			list_length(t_glist *lst)
{
	register int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_glist		*list_reverse(t_glist *list)
{
	register t_glist *n;
	register t_glist *p;

	p = 0;
	while (list)
	{
		n = list->next;
		list->next = p;
		p = list;
		list = n;
	}
	return (p);
}

t_glist		*list_append(t_glist *head, t_glist *tail)
{
	register t_glist	*t_head;

	if (head == 0)
		return (tail);
	t_head = head;
	while (t_head->next)
		t_head = t_head->next;
	t_head->next = tail;
	return (head);
}

/* make_cmd.c */
t_wdtk		*make_bare_word(const char *s)
{
	t_wdtk *w;

	w = malloc(sizeof(*w));
	w->word = s ? STRSAV(s) : STRSAV("");
	w->flags = 0;
	return (w);
}

/* make_cmd.c */
t_wlst		*make_word_list(t_wdtk *x, t_wlst *l)
{
	t_wlst *w;

	w = malloc(sizeof(*w));
	w->word = x;
	w->next = l;
	return (w);
}

/* make_cmd.c */
t_wdtk		*make_word_flags(t_wdtk *w, const char *string)
{
	register int	i;
	int				slen;

	i = 0;
	slen = strlen(string);
	while (i < slen)
	{
		if (string[i] == '$')
			w->flags |= W_HASDOLLAR;
		if (string[i] == '\\' && i++)
			continue;
		if (string[i] == '\'' || string[i] == '`' || string[i] == '"')
			w->flags |= W_QUOTED;
		i++;
	}
	return (w);
}

/* make_cmd.c */
t_wdtk		*make_word(const char *string)
{
	t_wdtk	*temp;

	temp = make_bare_word(string);
	return (make_word_flags(temp, string));
}

/* dispose_cmd.c */
void		dispose_word(t_wdtk *w)
{
	if (w == NULL)
		return ;
	free(w->word);
	free(w);
}

#define WHITESPACE(c) ((c) == ' ' || (c) == '\t')
#define DIGIT(c) ((c) >= '0' && (c) <= '9')
/* general.c */
int			legal_number(const char *str, intmax_t *res)
{
	intmax_t	val;
	char		*ep;

	if (res)
		*res = 0;
	if (str == NULL)
		return (0);
	errno = 0;
	val = strtoimax(str, &ep, 10);
	if (errno || ep == str)
		return (0); /* errno is set on overflow or underflow */

	/* Skip any trailing whitespace, since strtoimax does not. */
	while (WHITESPACE(*ep))
		ep++;

	/* If *str is not '\0' but *ep is '\0' on return, the entire string
	is valid. */
	if (*str && *ep == '\0')
	{
		if (res)
			*res = val;
		/* If it spill, don't do the fill. */
		return (1);
	}
	return (0);
}

/* general.c */
int			all_digits(const char *str)
{
	register const char	*s;

	s = str;
	while (*s)
	{
		if (DIGIT(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

/* make_cmd.c */
t_redir		*make_redirection(t_rdtgt source, enum r_instruction instruction,
		t_rdtgt dest_and_filename, int flags)
{
	t_redir		*temp;
	t_wdtk		*w;
	int			wlen;
	intmax_t	lfd;

	temp = malloc(sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->redirector = source;
	temp->redirectee = dest_and_filename;
	temp->here_doc_eof = 0;
	temp->ins = instruction;
	temp->flags = 0;
	temp->rflags = flags;
	temp->next = (t_redir*)NULL;
	switch (instruction) {
		case r_output_direction:		/* >foo */
		case r_output_force:			/* >| foo */
		case r_err_and_out:				/* &>filename */
			temp->flags = O_TRUNC | O_WRONLY | O_CREAT;
			break;

		case r_appending_to:			/* >>foo */
		case r_append_err_and_out:		/* &>> filename */
			temp->flags = O_APPEND | O_WRONLY | O_CREAT;
			break;

		case r_input_direction:			/* <foo */
		case r_inputa_direction:		/* foo & makes this. */
			temp->flags = O_RDONLY;
			break;

		case r_input_output:			/* <>foo */
			temp->flags = O_RDWR | O_CREAT;
			break;

		case r_deblank_reading_until:	/* <<-foo */
		case r_reading_until:			/* << foo */
		case r_reading_string:			/* <<< foo */
		case r_close_this:				/* <&- */
		case r_duplicating_input:		/* 1<&2 */
		case r_duplicating_output:		/* 1>&2 */
			break;

		/* the parser doesn't pass these. */
		case r_move_input:				/* 1<&2- */
		case r_move_output:				/* 1>&2- */
		case r_move_input_word:			/* 1<&$foo- */
		case r_move_output_word:		/* 1>&$foo- */
			break;

		/* The way the lexer works we have to do this here. */
		case r_duplicating_input_word:	/* 1<&$foo */
		case r_duplicating_output_word:	/* 1>&$foo */
			w = dest_and_filename.filename;
			wlen = strlen(w->word) - 1;
			if (w->word[wlen] == '-') /* Ack, big gross. */
			{
				w->word[wlen] = '\0';
				if (all_digits(w->word) && legal_number(w->word, &lfd) &&
						lfd == (int)lfd)
				{
					dispose_word(w);
					temp->ins = (instruction == r_duplicating_input_word)
						? r_move_input
						: r_move_output;
				}
				else
					temp->ins = (instruction == r_duplicating_input_word)
						? r_move_input_word
						: r_move_output_word;
			}
			break;
		default:
			fprintf(stderr, "Error make_redirection: redirection instruction `%d' out of range\n", instruction);
			abort();
			break;
	}
	return (temp);
}

void		print_word_token(t_wdtk *word)
{
	if (word == NULL)
		return ;
	printf("{word(%s) flags(%d)}\n", word->word, word->flags);
}

void		map_word_list(t_wlst *list, void (*func)(t_wdtk *))
{
	t_wlst	*w;

	if (list == NULL || func == NULL)
		return ;
	w = list;
	while (w != NULL)
	{
		func(w->word);
		w = w->next;
	}
}

int tok_word_len(const char *str);

#define TOKEN_SEP " \t\n\r#"
/* Parse input into a WORD_LIST */
void parse_input(char *argv)
{
	char *tofree=0, *tmp=0, *str=0;
	t_wlst *inpt=0;
	size_t token_length=0, idx=0, total=0;
	int inpt_length=0;

	tofree = str = strdup(argv);
	if (str == NULL)
		return ;
	total = strlen(str);
	while (idx+token_length < total)
	{
		/* is it an invalid starting word */
		token_length = strcspn(str+idx, TOKEN_SEP);
		fprintf(stderr, "DEBUG: token_length(%zd) idx(%zd)\n", token_length, idx);
		if (token_length == 0)
			break;

		/* read word */
		tmp = strndup(str+idx, token_length);

		/* TODO classify word */
		fprintf(stderr, "DEBUG: tmp(%s)\n", tmp);

		/* if command, check for arguments and */

		/* if redirection, ensure it is valid: [n] */
		inpt = make_word_list(make_word(tmp), inpt);
		/* inpt = make_word_list(make_bare_word(tmp), inpt); */
		idx += token_length + 1;
		token_length = 0;
	}
	free(tofree);
	inpt = REVLIST(inpt, t_wlst*);
	inpt_length = list_length((t_glist*)inpt);
	fprintf(stderr, "DEBUG: inpt_length(%d)\n", inpt_length);
	map_word_list(inpt, print_word_token);
}

int main(int argc, char *argv[])
{
	if (argc >= 2)
	{
		parse_input(argv[1]);
	}
	else
	{
		fprintf(stderr, "%s: not enough arguments\n", *argv);
	}
}
