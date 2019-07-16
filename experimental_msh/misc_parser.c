#include "command.h"
#include "libft.h"

typedef struct s_token t_token;
struct s_token
{
	char	*word;
	int		token;
};
enum e_node_type
{
	NODE_PIPE,
	NODE_AND_AND,
	NODE_OR_OR,
	NODE_GREATER,
	NODE_GREATER_AND,
	NODE_LESS,
	NODE_LESS_AND,
	NODE_GREATER_GREATER,
	NODE_LESS_LESS,
	NODE_LESS_LESS_MINUS,
	NODE_LESS_GREATER,
	NODE_GREATER_BAR,
	NODE_BAR_AND,
	NODE_COMMAND,
	NODE_CMDARG,
};
t_token g_simple[] = {
	{"|", NODE_PIPE},
	{"&&", NODE_AND_AND},
	{"||", NODE_OR_OR},
	{">", NODE_GREATER},
	{">&", NODE_GREATER_AND},
	{"<", NODE_LESS},
	{"<&", NODE_LESS_AND},
	{">>", NODE_GREATER_GREATER},
	{"<<", NODE_LESS_LESS},
	{"<<-", NODE_LESS_LESS_MINUS},
	{"<>", NODE_LESS_GREATER},
	{">|", NODE_GREATER_BAR},
	{"|&", NODE_BAR_AND},
};
typedef struct s_ast	t_ast;
typedef struct s_astnode	t_astnode;
struct	s_astnode
{
	t_ast	*l;
	t_ast	*r;
};
union	u_val
{
	char		**tokens;
	t_astnode	child;
};
struct	s_ast
{
	t_ast_ntype	type;
	union u_val	node;
};
struct	s_abs_syn_tree
{
	t_ast_ntype				type;
	struct s_abs_syn_tree	*lhs;
	struct s_abs_syn_tree	*rhs;
};
static t_ast *parse_binop(char **toks, enum e_node_type ty)
{
	char **stoks = toks;
	t_ast *n;
	t_ast *m;

	if (ty == NODE_COMMAND)
	{
		if (!*toks)
			ft_dprintf(2, "parse_binop: ack badnull toks\n");
		n = malloc(sizeof(*n));
		n->type = NODE_COMMAND;
		n->node.tokens = stoks;
		return (n);
	}
	while (toks[0])
	{
		if (ft_strequ(g_simple[ty].word, toks[0]))
		{
			toks[0] = NULL;
			m = malloc(sizeof(*m));
			m->type = ty;
			if (!(m->node.child.l = parse_binop(stoks, ty - 1)))
				return (NULL);
			if (!(m->node.child.r = parse_binop(toks + 1, ty)));
				return (NULL);
			return (m);
		}
		else
			toks++;
	}
	return (parse_binop(stoks, ty - 1));
}
static t_ast *parse_tokens(char **toks, int *bg)
{
	int tokc = 0;

	while (toks[tokc])
		tokc++;
	if (tokc > 0 && ft_strequ("&", toks[--tokc]))
	{
		*bg = 1;
		toks[tokc] = NULL;
	}
}
static int is_quote(char c)
{
	return (c && ft_strchr("\"'`", c));
}
static int is_eot(char c)
{
	return (c && ft_strchr(" \t\n\r#", c));
}
char g_escs[][2] = {
	{'\\', '\\'},
	{'t', '\t'},
	{'n', '\n'},
	{'r', '\r'},
	{'"', '"'},
	{'\'', '\''},
	{'`', '`'}
};
static int is_esc(int c)
{
	size_t	i;

	i = 0;
	while (i < 7)
	{
		if (g_escs[i][0] == c)
			return (1);
		i++;
	}
	return (0);
}
char *ft_strsep(char **str, const char *sep)
{
	char *start;
	char *end;

	start = *str;
	if (!start)
		return (NULL);
	end = start + ft_strcspn(start, sep);
	if (*end)
		*end++ = '\0';
	else
		end = NULL;
	*str = end;
	return (start);
}
int tokenize(const char *token)
{
	size_t i;

	if (!token)
		return (-1);
	i = 0;
	while (i < NODE_COMMAND)
	{
		if (ft_strequ(g_simple[i].word, token))
			return (g_simple[i].token);
		i++;
	}
	return (NODE_COMMAND);
}
void insert_node(char *word, int tok)
{
}
char **read_tokens(char *line)
{
	char	*s;
	char	*tok;
	char	*tofree;
	int		tk;

	s = strdup(line);
	tofree = s;
	while ((tok = strsep(&s, " \n\t")) != NULL)
	{
		tk = tokenize(tok);
		push_token(tk);
	}
	return (&line);
}
t_ast *parse(char *line, int *bg)
{
	char **toks = read_tokens(line);

	if (!toks || !*toks)
		return (NULL);
	return (parse_tokens(toks, bg));
}
typedef enum e_toktype {
	IF = 258,
	THEN = 259,
	ELSE = 260,
	ELIF = 261,
	FI = 262,
	CASE = 263,
	ESAC = 264,
	FOR = 265,
	SELECT = 266,
	WHILE = 267,
	UNTIL = 268,
	DO = 269,
	DONE = 270,
	FUNCTION = 271,
	COPROC = 272,
	COND_START = 273,
	COND_END = 274,
	COND_ERROR = 275,
	IN = 276,
	BANG = 277,
	TIME = 278,
	TIMEOPT = 279,
	TIMEIGN = 280,
	WORD = 281,
	ASSIGNMENT_WORD = 282,
	REDIR_WORD = 283,
	NUMBER = 284,
	ARITH_CMD = 285,
	ARITH_FOR_EXPRS = 286,
	COND_CMD = 287,
	AND_AND = 288,
	OR_OR = 289,
	GREATER_GREATER = 290,
	LESS_LESS = 291,
	LESS_AND = 292,
	LESS_LESS_LESS = 293,
	GREATER_AND = 294,
	SEMI_SEMI = 295,
	SEMI_AND = 296,
	SEMI_SEMI_AND = 297,
	LESS_LESS_MINUS = 298,
	AND_GREATER = 299,
	AND_GREATER_GREATER = 300,
	LESS_GREATER = 301,
	GREATER_BAR = 302,
	BAR_AND = 303,
	PARSE_EOF = 304
} t_symbol;

extern char	*g_operator_for[];
char *end_of_token = "&;\n\x04";

/*
** Reserved words. These are only recognized as the first word of a command.
*/
t_wdtk	g_word_token_alist[] = {
	{"if", IF},
	{"then", THEN},
	{"else", ELSE},
	{"elif", ELIF},
	{"fi", FI},
	{"case", CASE},
	{"esac", ESAC},
	{"for", FOR},
	{"select", SELECT},
	{"while", WHILE},
	{"until", UNTIL},
	{"do", DO},
	{"done", DONE},
	{"in", IN},
	{"function", FUNCTION},
	{"time", TIME},
	{"{", '{'},
	{"}", '}'},
	{"!", BANG},
	{"[[", COND_START},
	{"]]", COND_END},
	{"coproc", COPROC},
	{(char*)NULL, 0}
};

/* other tokens that can be returned by read_token() */
t_wdtk	g_other_token_alist[] = {
	/* Multiple-character tokens with special values */
	{"--", TIMEIGN},
	{"-p", TIMEOPT},
	{"&&", AND_AND},
	{"||", OR_OR},
	{">>", GREATER_GREATER},
	{"<<", LESS_LESS},
	{"<&", LESS_AND},
	{">&", GREATER_AND},
	{";;", SEMI_SEMI},
	{";&", SEMI_AND},
	{";;&", SEMI_SEMI_AND},
	{"<<-", LESS_LESS_MINUS},
	{"<<<", LESS_LESS_LESS},
	{"&>", AND_GREATER},
	{"&>>", AND_GREATER_GREATER},
	{"<>", LESS_GREATER},
	{">|", GREATER_BAR},
	{"|&", BAR_AND},
	{"EOF", PARSE_EOF},
	/* Tokens whose value is the character itself */
	{">", '>'},
	{"<", '<'},
	{"-", '-'},
	{"{", '{'},
	{"}", '}'},
	{";", ';'},
	{"(", '('},
	{")", ')'},
	{"|", '|'},
	{"&", '&'},
	{"newline", '\n'},
	{(char*)NULL, 0}
};

extern char tokens[] = "#$^*(())$=|{}[]`<>>?~`,-!\"\\\\";
typedef enum e_node_type	t_ast_ntype;

t_symbol g_sym;
t_symbol g_prev_sym;
t_symbol g_before_prev_sym;

t_symbol g_current_token;
t_symbol g_last_read_token;
t_symbol g_token_before_that;
t_symbol g_two_tokens_ago;
char **g_tokens;
int shell_eof_token;
int current_token;
int parser_state;
static int last_read_token;
static int token_before_that;
static int two_tokens_ago;

/* Use a stack or keeping track of delimiters */
/* Definition of the delimiter stack. */
struct dstack {
/* DELIMITERS is a stack of the nested delimiters that we have
encountered so far */
	char	*delimiters;
/* Offset into the stack of delimiters. */
	int		depth;
/* How many slots are allocated to DELIMITERS. */
	int		space;
};
static int token_to_read;
static t_wdtk *word_desc_to_read;

static t_rdtgt source;
static t_rdtgt redir;
struct dstack dstack = {NULL, 0, 0};

#define current_delimiter(ds) (ds.depth ? ds.delimiters[ds.depth - 1] : 0)

#define push_delimiter(ds, character) \
	do { \
		if (ds.depth + 2 > ds.space) \
			ds.delimiters = (char*)realloc \
			(ds.delimiters, (ds.space += 10) * sizeof(char)); \
			ds.delimiters[ds.depth] = character; \
			ds.depth++; \
	} while (0)

#define pop_delimiter(ds) ds.depth--

void expression(void);

void push_token(int x)
{
	g_two_tokens_ago = g_token_before_that;
	g_token_before_that = g_last_read_token;
	g_last_read_token = g_current_token;
	g_current_token = x;
}
void	nextsym(void)
{
	int		i;

	if (!g_tokens || !*g_tokens)
		push_token(PARSE_EOF);
	i = -1;
	while (g_other_token_alist[++i].word != NULL)
	{
		if (ft_strequ(g_other_token_alist[i].word, *g_tokens)) {
			push_token(g_other_token_alist[i].flags);
			break;
		}
	}
	g_tokens++;
	if (g_other_token_alist[i].word == NULL)
		push_token(WORD);
}

void	parse_error(const char msg[])
{
	ft_dprintf("%s\n", msg);
}

int		accept(t_symbol s)
{
	if (g_sym == s)
	{
		nextsym();
		return (1);
	}
	return (0);
}

void expect(t_symbol s)
{
	if (accept(s))
		return (1);
	error("expect: unexpected symbol");
	return (0);
}

void factor(void)
{
	if (accept(WORD))
		;
	else if (accept(NUMBER));
	else if (accept('('))
	{
		expression();
		expect(')');
	}
	else
	{
		error("factor: syntax error");
		nextsym();
	}
}

void term(void)
{
	factor();
	while (g_sym == AND_AND || g_sym == OR_OR)
	{
		nextsym();
		factor();
	}
}

void expression(void)
{
	if (g_sym == '&' || g_sym == ';')
		nextsym();
	term();
	while (g_sym == '&' || g_sym == ';')
	{
		nextsym();
		term();
	}
}

void condition(void)
{
	if (accept(WORD))
		expression();
	else
	{
		expression();
		if (g_sym == '=' || g_sym == '<' || g_sym == '>')
		{
			nextsym();
			expression();
		}
		else
		{
			error("condition: invalid operator");
			nextsym();
		}
	}
}
/*
command

VAR=VAL
CMD CMDOPT CMDARG [;&|>]
*/
void statement(void)
{
	if (accept(ASSIGNMENT_WORD))
	{
		expect('=');
		expression();
	}
	else if (accept('|'))
	{
		expect(WORD);
	}
	else if (accept(WORD))
	{
		do {
			statement();
		} while (accept(';'));
		expect('\n');
	}
	else if (accept(IF))
	{
		condition();
		expect(THEN);
		statement();
	}
	else if (accept(WHILE))
	{
		condition();
		expect(DO);
		statement();
	}
	else
	{
		error("statement: syntax error");
		nextsym();
	}
}

void block(void)
{
	if (accept(1))
		return ;
}
