
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"
#include "../types/types.hpp"
#include "../ast/ast.hpp"
#include "../correcting/correcting.hpp"

#define YYDEBUG 1
//%option noyywrap nodefault;
extern FILE* yyin;
extern int line_number;
extern int yylex();


/* Line 189 of yacc.c  */
#line 90 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_byte = 258,
     T_false = 259,
     T_if = 260,
     T_int = 261,
     T_proc = 262,
     T_reference = 263,
     T_return = 264,
     T_while = 265,
     T_true = 266,
     T_else = 267,
     T_equal = 268,
     T_notequal = 269,
     T_lessequal = 270,
     T_greaterequal = 271,
     T_id = 272,
     T_const = 273,
     T_char = 274,
     T_string = 275,
     NOELSE = 276
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 17 "parser.y"

    ast::ASTPtr *a;
    ast::ASTList *al;
    types::TypePtr *tp;
    int ival;
    char cval;
    const char *sval;



/* Line 214 of yacc.c  */
#line 158 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 170 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,     2,     2,    30,    22,     2,
      34,    35,    28,    26,    36,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    37,
      24,    38,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    23,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    11,    13,    15,    17,    19,
      21,    25,    28,    32,    36,    40,    44,    48,    52,    56,
      60,    62,    67,    69,    71,    73,    75,    79,    81,    84,
      87,    91,    95,    99,   103,   107,   108,   112,   114,   119,
     121,   126,   128,   131,   137,   145,   151,   155,   156,   159,
     163,   168,   176,   178,   180,   181,   184,   189,   193,   194,
     198,   200,   209
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      60,     0,    -1,     6,    -1,     3,    -1,    43,    32,    33,
      -1,    43,    -1,    43,    -1,     7,    -1,    11,    -1,     4,
      -1,    34,    46,    35,    -1,    21,    46,    -1,    48,    24,
      48,    -1,    48,    25,    48,    -1,    48,    13,    48,    -1,
      48,    14,    48,    -1,    48,    15,    48,    -1,    48,    16,
      48,    -1,    46,    22,    46,    -1,    46,    23,    46,    -1,
      20,    -1,    17,    32,    48,    33,    -1,    17,    -1,    19,
      -1,    18,    -1,    47,    -1,    34,    48,    35,    -1,    50,
      -1,    26,    48,    -1,    27,    48,    -1,    48,    26,    48,
      -1,    48,    27,    48,    -1,    48,    28,    48,    -1,    48,
      29,    48,    -1,    48,    30,    48,    -1,    -1,    49,    36,
      48,    -1,    48,    -1,    17,    34,    49,    35,    -1,    37,
      -1,    47,    38,    48,    37,    -1,    53,    -1,    50,    37,
      -1,     5,    34,    46,    35,    51,    -1,     5,    34,    46,
      35,    51,    12,    51,    -1,    10,    34,    46,    35,    51,
      -1,     9,    48,    37,    -1,    -1,    52,    51,    -1,    39,
      52,    40,    -1,    17,    41,    43,    37,    -1,    17,    41,
      43,    32,    18,    33,    37,    -1,    59,    -1,    54,    -1,
      -1,    56,    55,    -1,    17,    41,     8,    44,    -1,    17,
      41,    44,    -1,    -1,    58,    36,    57,    -1,    57,    -1,
      17,    34,    58,    35,    41,    45,    56,    53,    -1,    59,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    86,    86,    87,    91,    92,    96,    97,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     116,   117,   118,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   138,   139,   140,   144,   148,
     149,   150,   151,   152,   153,   154,   155,   159,   160,   164,
     169,   171,   176,   177,   181,   182,   188,   189,   193,   194,
     195,   199,   204
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"byte\"", "\"false\"", "\"if\"",
  "\"int\"", "\"proc\"", "\"reference\"", "\"return\"", "\"while\"",
  "\"true\"", "\"else\"", "\"==\"", "\"!=\"", "\"<=\"", "\">=\"", "T_id",
  "T_const", "T_char", "T_string", "'!'", "'&'", "'|'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "NOELSE", "'['", "']'", "'('", "')'",
  "','", "';'", "'='", "'{'", "'}'", "':'", "$accept", "data_type", "type",
  "r_type", "cond", "l_value", "expr", "expr_list", "func_call", "stmt",
  "stmt_list", "compound_stmt", "var_def", "local_def", "local_def_list",
  "fpar_def", "fpar_list", "func_def", "program", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    33,    38,   124,    60,    62,    43,    45,    42,    47,
      37,   276,    91,    93,    40,    41,    44,    59,    61,   123,
     125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    49,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      54,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    59,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     1,     1,     1,     1,     3,     1,     2,     2,
       3,     3,     3,     3,     3,     0,     3,     1,     4,     1,
       4,     1,     2,     5,     7,     5,     3,     0,     2,     3,
       4,     7,     1,     1,     0,     2,     4,     3,     0,     3,
       1,     8,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    62,     0,    58,     1,     0,    60,     0,     0,
       0,     0,     3,     2,     0,     5,    57,     0,    59,    56,
       0,     7,     6,    54,     4,     0,     0,    47,    61,    53,
      55,    52,     0,     0,     0,     0,     0,     0,    22,    20,
      39,    49,     0,     0,    48,    41,     0,    50,     0,    24,
      23,     0,     0,     0,    25,     0,    27,     0,     0,    35,
       0,    42,     0,     9,     8,     0,     0,     0,     0,    28,
      29,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      37,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    30,    31,    32,
      33,    34,     0,    21,    38,     0,    40,    51,    10,    18,
      19,    43,    14,    15,    16,    17,    12,    13,    45,    36,
       0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    15,    16,    23,    67,    54,    68,    81,    56,    44,
      33,    45,    29,    30,    25,     7,     8,     2,     3
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
     -14,    -2,   -72,    40,    31,   -72,    13,   -72,    45,     7,
      17,    31,   -72,   -72,    27,    34,   -72,   114,   -72,   -72,
      35,   -72,   -72,   -72,   -72,   -13,   -22,   -72,   -72,   -72,
     -72,   -72,    27,    -3,    18,    39,    58,    49,   -23,   -72,
     -72,   -72,    48,    56,   -72,   -72,    82,   -72,    85,   -72,
     -72,    58,    58,    58,   -72,   123,   -72,    85,    58,    58,
      58,   -72,    89,   -72,   -72,    85,    85,    16,   118,    80,
      80,   140,    58,    58,    58,    58,    58,   -72,    30,   150,
     110,    55,   128,    81,    75,    72,   100,    85,    85,    62,
      58,    58,    58,    58,    58,    58,   -72,    80,    80,   -72,
     -72,   -72,    62,   -72,   -72,    58,   -72,   -72,   -72,   136,
     -72,   111,   110,   110,   110,   110,   110,   110,   -72,   110,
      62,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,    -9,   127,   -72,   -41,   -33,   -31,   -72,   -32,   -71,
     -72,   137,   -72,   -72,   -72,   152,   -72,   139,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      42,    43,    35,     1,    26,    55,    36,    37,    22,    58,
      12,    59,     4,    13,    38,    14,    78,    39,   111,    32,
      69,    70,    71,    34,    84,    85,    27,    79,    80,    82,
      12,   118,     4,    13,    40,    86,    27,    41,    87,    88,
       5,    97,    98,    99,   100,   101,   109,   110,     6,   121,
      46,    89,    87,    88,     9,    47,    42,    43,    17,   112,
     113,   114,   115,   116,   117,   102,    20,    35,    24,    42,
      43,    36,    37,    48,   119,    38,    49,    50,    39,    38,
      10,    11,    39,    57,    51,    52,    60,    42,    43,    63,
     104,   105,    53,    61,    87,    88,    64,    87,    88,    40,
      62,    27,    38,    49,    50,    39,    65,   108,    74,    75,
      76,    51,    52,    90,    91,    92,    93,    12,   107,    66,
      13,    21,    83,   120,    94,    95,    72,    73,    74,    75,
      76,    90,    91,    92,    93,    96,    72,    73,    74,    75,
      76,    19,    94,    95,    72,    73,    74,    75,    76,    72,
      73,    74,    75,    76,    72,    73,    74,    75,    76,    88,
      77,     0,    28,    18,    31,   106,    72,    73,    74,    75,
      76,     0,     0,     0,     0,    96,    72,    73,    74,    75,
      76,     0,     0,   103
};

static const yytype_int8 yycheck[] =
{
      33,    33,     5,    17,    17,    36,     9,    10,    17,    32,
       3,    34,    34,     6,    17,     8,    57,    20,    89,    41,
      51,    52,    53,    32,    65,    66,    39,    58,    59,    60,
       3,   102,    34,     6,    37,    66,    39,    40,    22,    23,
       0,    72,    73,    74,    75,    76,    87,    88,    17,   120,
      32,    35,    22,    23,    41,    37,    89,    89,    41,    90,
      91,    92,    93,    94,    95,    35,    32,     5,    33,   102,
     102,     9,    10,    34,   105,    17,    18,    19,    20,    17,
      35,    36,    20,    34,    26,    27,    38,   120,   120,     4,
      35,    36,    34,    37,    22,    23,    11,    22,    23,    37,
      18,    39,    17,    18,    19,    20,    21,    35,    28,    29,
      30,    26,    27,    13,    14,    15,    16,     3,    37,    34,
       6,     7,    33,    12,    24,    25,    26,    27,    28,    29,
      30,    13,    14,    15,    16,    35,    26,    27,    28,    29,
      30,    14,    24,    25,    26,    27,    28,    29,    30,    26,
      27,    28,    29,    30,    26,    27,    28,    29,    30,    23,
      37,    -1,    25,    11,    25,    37,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    35,    26,    27,    28,    29,
      30,    -1,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    59,    60,    34,     0,    17,    57,    58,    41,
      35,    36,     3,     6,     8,    43,    44,    41,    57,    44,
      32,     7,    43,    45,    33,    56,    17,    39,    53,    54,
      55,    59,    41,    52,    43,     5,     9,    10,    17,    20,
      37,    40,    47,    50,    51,    53,    32,    37,    34,    18,
      19,    26,    27,    34,    47,    48,    50,    34,    32,    34,
      38,    37,    18,     4,    11,    21,    34,    46,    48,    48,
      48,    48,    26,    27,    28,    29,    30,    37,    46,    48,
      48,    49,    48,    33,    46,    46,    48,    22,    23,    35,
      13,    14,    15,    16,    24,    25,    35,    48,    48,    48,
      48,    48,    35,    33,    35,    36,    37,    37,    35,    46,
      46,    51,    48,    48,    48,    48,    48,    48,    51,    48,
      12,    51
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    { (yyval.tp) = &types::intType;  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    { (yyval.tp) = &types::byteType; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    { (yyval.tp) = new types::TypePtr(std::make_shared<types::ArrayType>(*(yyvsp[(1) - (3)].tp))); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    { (yyval.tp) = (yyvsp[(1) - (1)].tp);                                               ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { (yyval.tp) = (yyvsp[(1) - (1)].tp);                                   ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { (yyval.tp) = new types::TypePtr(std::make_shared<types::VoidType>()); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("true"));       ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("false"));      ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    { (yyval.a) = (yyvsp[(2) - (3)].a);                                              ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    { (yyval.a) = (yyvsp[(2) - (2)].a);                                              ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("<", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a)));  ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>(">", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a)));  ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("==", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("!=", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("<=", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>(">=", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("&", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a)));  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Cond>("|", *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a)));  ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::String>((yyvsp[(1) - (1)].sval)));       ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::LValue>((yyvsp[(1) - (4)].sval), *(yyvsp[(3) - (4)].a)));   ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::LValue>((yyvsp[(1) - (1)].sval)));       ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Char>((yyvsp[(1) - (1)].cval)));           ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Const>((yyvsp[(1) - (1)].ival)));          ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a);                                               ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { (yyval.a) = (yyvsp[(2) - (3)].a);                                               ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a);                                               ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('+', *(yyvsp[(2) - (2)].a)));     ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('-', *(yyvsp[(2) - (2)].a)));     ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('+', *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('-', *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('*', *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('/', *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::BinOp>('%', *(yyvsp[(1) - (3)].a), *(yyvsp[(3) - (3)].a))); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { (yyval.al) = new ast::ASTList();                     ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    { (yyvsp[(1) - (3)].al)->push_back(*(yyvsp[(3) - (3)].a)); (yyval.al) = (yyvsp[(1) - (3)].al);                 ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { (yyval.al) = new ast::ASTList(); (yyval.al)->push_back(*(yyvsp[(1) - (1)].a)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Call>((yyvsp[(1) - (4)].sval), *(yyvsp[(3) - (4)].al))); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.a) = nullptr;            ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Assign>(*(yyvsp[(1) - (4)].a), *(yyvsp[(3) - (4)].a))); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a);                 ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (2)].a);                 ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::If>(*(yyvsp[(3) - (5)].a), *(yyvsp[(5) - (5)].a)));     ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::If>(*(yyvsp[(3) - (7)].a), *(yyvsp[(5) - (7)].a), *(yyvsp[(7) - (7)].a))); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::While>(*(yyvsp[(3) - (5)].a), *(yyvsp[(5) - (5)].a)));  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Return>(*(yyvsp[(2) - (3)].a)));     ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.al) = new ast::ASTList();      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyvsp[(1) - (2)].al)->push_back(*(yyvsp[(2) - (2)].a)); (yyval.al) = (yyvsp[(1) - (2)].al); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Block>(*(yyvsp[(2) - (3)].al))); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Var>((yyvsp[(1) - (4)].sval), *(yyvsp[(3) - (4)].tp)));     ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Var>((yyvsp[(1) - (7)].sval), *(yyvsp[(3) - (7)].tp), (yyvsp[(5) - (7)].ival))); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    { (yyval.a) = (yyvsp[(1) - (1)].a); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { (yyval.al) = new ast::ASTList(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    { (yyvsp[(1) - (2)].al)->push_back(*(yyvsp[(2) - (2)].a)); (yyval.al) = (yyvsp[(1) - (2)].al);                     ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Param>((yyvsp[(1) - (4)].sval), "reference", *(yyvsp[(4) - (4)].tp))); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Param>((yyvsp[(1) - (3)].sval), "value" , *(yyvsp[(3) - (3)].tp)));    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.al) = new ast::ASTList(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyvsp[(1) - (3)].al)->push_back(*(yyvsp[(3) - (3)].a)); (yyval.al) = (yyvsp[(1) - (3)].al);                     ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.al) = new ast::ASTList(); (yyval.al)->push_back(*(yyvsp[(1) - (1)].a)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    { (yyval.a) = new ast::ASTPtr(std::make_shared<ast::Func>((yyvsp[(1) - (8)].sval), *(yyvsp[(3) - (8)].al), *(yyvsp[(6) - (8)].tp), *(yyvsp[(7) - (8)].al), *(yyvsp[(8) - (8)].a))); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    { std::cout << "AST: " << *(*(yyvsp[(1) - (1)].a)) << std::endl;
                if((yyvsp[(1) - (1)].a) == nullptr) std::cout << "shit" << std::endl;
                (yyval.a) = (yyvsp[(1) - (1)].a);;}
    break;



/* Line 1455 of yacc.c  */
#line 1908 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 209 "parser.y"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char *filename = argv[1];
    FILE *inputFile = fopen(filename, "r");

    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }

    yyin = inputFile;  // Set yyin to read from the provided file

    int res = yyparse();  // Use the generated parser
    fclose(inputFile);   // Close the file when done

    if (res == 0) {
        std::cout << "Parsing successful" << std::endl;
        return 0;
    }

    std::cerr << "Parsing failed at line " << line_number << std::endl;
    return 1;
}

//int main(int argc, char *argv[]) {
//    
//    yydebug = 1;
//
//    int res = yyparse();
//    if (res == 0) {
//        std::cout << "Parsing successful" << std::endl;
//        exit(EXIT_SUCCESS);
//    }
//
//    std::cout << "Parsing failed at " << line_number << std::endl;
//    exit(EXIT_FAILURE);
//}

