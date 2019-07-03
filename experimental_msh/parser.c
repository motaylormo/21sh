typedef enum e_node_type	t_ast_ntype;
enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_CONJ,
	NODE_DISJ,
};

enum e_toktype {
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
	LESS_LESS_MINUX = 298,
	AND_GREATER = 299,
	AND_GREATER_GREATER = 300,
	LESS_GREATER = 301,
	GREATER_BAR = 302,
	BAR_AND = 303,
	PARSE_EOF = 304
};
extern char toke_huh_huh_like_weed_huh[] = "#$^*(())$=|{}[]`<>>?~`,-!\"\\\\";
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
extern char	*g_operator_for[];
