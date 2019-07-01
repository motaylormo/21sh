#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "input.h"

/*
** Possible statse for the parser that requires it to do special things.
**
** PST_CASEPAT - in a case pattern list
** PST_ALEXPNEXT - expand next word for aliases
** PST_ALLOWOPNBRC - allow open brace for function def
** PST_NEEDCLOSBRC - need close brace
** PST_DBLPAREN - double-paren parsing
** PST_SUBSHELL - ( ... ) subshell
** PST_CMDSUBST - $( ... ) command substitution
** PST_CASESTMT - parsing a case statement
** PST_CONDCMD - parsing a [[...]] command
** PST_CONDEXPR - parsing the guts of [[...]]
** PST_ARITHFOR - parsing an arithmetic for command - unused
** PST_EXTPAT - parsing an extended shell pattern
** PST_COMPASSIGN - parsing x=(...) compound assignment
** PST_ASSIGNOK - assignment statement ok in this context
** PST_EOFTOKEN - yylex checks against shell_eof_token
** PST_REGEXP - parsing an ERE/BRE as a single word
** PST_HEREDOC - reading body of here-document
** PST_REPARSE - re-parsing in parse_string_to_word_list
** PST_REDIRLIST - parsing a list of redirections preceding a simple command name
** PST_COMMENT - parsing a shell comment; used by aliases
** PST_ENDALIAS - just finished expanding and consuming an alias
*/

# define PST_CASEPAT		0x000001
# define PST_ALEXPNEXT		0x000002
# define PST_ALLOWOPNBRC	0x000004
# define PST_NEEDCLOSBRC	0x000008
# define PST_DBLPAREN		0x000010
# define PST_SUBSHELL		0x000020
# define PST_CMDSUBST		0x000040
# define PST_CASESTMT		0x000080
# define PST_CONDCMD		0x000100
# define PST_CONDEXPR		0x000200
# define PST_ARITHFOR		0x000400
# define PST_ALEXPAND		0x000800
# define PST_EXTPAT			0x001000
# define PST_COMPASSIGN		0x002000
# define PST_ASSIGNOK		0x004000
# define PST_EOFTOKEN		0x008000
# define PST_REGEXP			0x010000
# define PST_HEREDOC		0x020000
# define PST_REPARSE		0x040000
# define PST_REDIRLIST		0x080000
# define PST_COMMENT		0x100000
# define PST_ENDALIAS		0x200000

/* Definition of the delimiter stack. Needed by parse.y and bashhist.c. */
typedef struct s_dstack t_dstack;
struct s_dstack
{
/* DELIMITERS is a stack of the nested delimiters that we have
   encountered so far. */
	char *delimeters;
/* Offset into the stack of delimiters. */
	int delimiter_depth;
/* How many slots are allocated to DELIMITERS. */
	int delimiter_space;
};

/* States we can be in while scanning a ${...} expansion. Shared between
   parse.y and subst.c */
# define DOLBRACE_PARAM		0x01
# define DOLBRACE_OP		0x02
# define DOLBRACE_WORD		0x04
# define DOLBRACE_QUOTE		0x40 /* single quote is special in double qoutes */
# define DOLBRACE_QUOTE2	0x80 /* single quote is semi-special in double quotes */

/* variable declarations from parse.y */
extern t_dstack dstack;

extern char *primary_prompt;
extern char *secondary_prompt;

extern char *current_prompt_string;

extern char *ps1_prompt;
extern char *ps2_prompt;
extern char *ps0_prompt;

extern int expand_aliases;
extern int current_command_line_count;
extern int saved_command_line_count;
extern int shell_eof_token;
extern int current_token;
extern int parser_state;
extern int need_here_doc;

extern int ignoreeof;
extern int eof_encountered;
extern int eof_encountered_limit;

extern int line_number;
extern int line_number_base;

#endif
