/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./parser/parser.y"


#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"

#define YYDEBUG 1

extern int line_number;


#line 84 "./parser/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_byte = 3,                     /* "byte"  */
  YYSYMBOL_T_false = 4,                    /* "false"  */
  YYSYMBOL_T_if = 5,                       /* "if"  */
  YYSYMBOL_T_int = 6,                      /* "int"  */
  YYSYMBOL_T_proc = 7,                     /* "proc"  */
  YYSYMBOL_T_reference = 8,                /* "reference"  */
  YYSYMBOL_T_return = 9,                   /* "return"  */
  YYSYMBOL_T_while = 10,                   /* "while"  */
  YYSYMBOL_T_true = 11,                    /* "true"  */
  YYSYMBOL_T_else = 12,                    /* "else"  */
  YYSYMBOL_T_equal = 13,                   /* "=="  */
  YYSYMBOL_T_notequal = 14,                /* "!="  */
  YYSYMBOL_T_lessequal = 15,               /* "<="  */
  YYSYMBOL_T_greaterequal = 16,            /* ">="  */
  YYSYMBOL_T_id = 17,                      /* T_id  */
  YYSYMBOL_T_const = 18,                   /* T_const  */
  YYSYMBOL_T_char = 19,                    /* T_char  */
  YYSYMBOL_T_string = 20,                  /* T_string  */
  YYSYMBOL_21_ = 21,                       /* '&'  */
  YYSYMBOL_22_ = 22,                       /* '|'  */
  YYSYMBOL_23_ = 23,                       /* '<'  */
  YYSYMBOL_24_ = 24,                       /* '>'  */
  YYSYMBOL_25_ = 25,                       /* '+'  */
  YYSYMBOL_26_ = 26,                       /* '-'  */
  YYSYMBOL_27_ = 27,                       /* '*'  */
  YYSYMBOL_28_ = 28,                       /* '/'  */
  YYSYMBOL_29_ = 29,                       /* '%'  */
  YYSYMBOL_NOELSE = 30,                    /* NOELSE  */
  YYSYMBOL_31_ = 31,                       /* '['  */
  YYSYMBOL_32_ = 32,                       /* ']'  */
  YYSYMBOL_33_ = 33,                       /* '('  */
  YYSYMBOL_34_ = 34,                       /* ')'  */
  YYSYMBOL_35_ = 35,                       /* '!'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_data_type = 43,                 /* data_type  */
  YYSYMBOL_type = 44,                      /* type  */
  YYSYMBOL_r_type = 45,                    /* r_type  */
  YYSYMBOL_cond = 46,                      /* cond  */
  YYSYMBOL_l_value = 47,                   /* l_value  */
  YYSYMBOL_expr = 48,                      /* expr  */
  YYSYMBOL_expr_list = 49,                 /* expr_list  */
  YYSYMBOL_func_call = 50,                 /* func_call  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_stmt_list = 52,                 /* stmt_list  */
  YYSYMBOL_compound_stmt = 53,             /* compound_stmt  */
  YYSYMBOL_var_def = 54,                   /* var_def  */
  YYSYMBOL_local_def = 55,                 /* local_def  */
  YYSYMBOL_local_def_list = 56,            /* local_def_list  */
  YYSYMBOL_fpar_def = 57,                  /* fpar_def  */
  YYSYMBOL_fpar_list = 58,                 /* fpar_list  */
  YYSYMBOL_func_def = 59,                  /* func_def  */
  YYSYMBOL_program = 60                    /* program  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,    29,    21,     2,
      33,    34,    27,    25,    36,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    37,
      23,    38,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    22,    40,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    56,    60,    61,    65,    66,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      85,    86,    87,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   107,   108,   109,   113,   117,
     118,   119,   120,   121,   122,   123,   124,   128,   129,   133,
     138,   139,   143,   144,   148,   149,   155,   156,   160,   161,
     162,   166,   170
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"byte\"",
  "\"false\"", "\"if\"", "\"int\"", "\"proc\"", "\"reference\"",
  "\"return\"", "\"while\"", "\"true\"", "\"else\"", "\"==\"", "\"!=\"",
  "\"<=\"", "\">=\"", "T_id", "T_const", "T_char", "T_string", "'&'",
  "'|'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "NOELSE", "'['",
  "']'", "'('", "')'", "'!'", "','", "';'", "'='", "'{'", "'}'", "':'",
  "$accept", "data_type", "type", "r_type", "cond", "l_value", "expr",
  "expr_list", "func_call", "stmt", "stmt_list", "compound_stmt",
  "var_def", "local_def", "local_def_list", "fpar_def", "fpar_list",
  "func_def", "program", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,     3,   -73,    31,    30,   -73,     9,   -73,    59,    43,
      14,    30,   -73,   -73,    13,    27,   -73,    97,   -73,   -73,
      33,   -73,   -73,   -73,   -73,   -13,   -27,   -73,   -73,   -73,
     -73,   -73,    13,    -2,    44,    35,   125,    40,    47,   -73,
     -73,   -73,    39,    65,   -73,   -73,    88,   -73,    72,   -73,
     -73,   125,   125,   125,   -73,   127,   -73,    72,   125,   125,
     125,   -73,    85,   -73,   -73,    72,    72,    -9,   112,    57,
      57,   140,   125,   125,   125,   125,   125,   -73,    18,   150,
      87,    60,   134,    96,    32,    95,   109,    72,    72,    62,
     125,   125,   125,   125,   125,   125,   -73,    57,    57,   -73,
     -73,   -73,    62,   -73,   -73,   125,   -73,   -73,   -73,   110,
     -73,   122,    87,    87,    87,    87,    87,    87,   -73,    87,
      62,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    62,     0,    58,     1,     0,    60,     0,     0,
       0,     0,     3,     2,     0,     5,    57,     0,    59,    56,
       0,     7,     6,    54,     4,     0,     0,    47,    61,    53,
      55,    52,     0,     0,     0,     0,     0,     0,    22,    20,
      39,    49,     0,     0,    48,    41,     0,    50,     0,    24,
      23,     0,     0,     0,    25,     0,    27,     0,     0,    35,
       0,    42,     0,     9,     8,     0,     0,     0,     0,    28,
      29,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      37,     0,     0,     0,     0,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    30,    31,    32,
      33,    34,     0,    21,    38,     0,    40,    51,    10,    18,
      19,    43,    14,    15,    16,    17,    12,    13,    45,    36,
       0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,    -8,   132,   -73,   -55,   -33,   -31,   -73,   -32,   -72,
     -73,   123,   -73,   -73,   -73,   136,   -73,   124,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    15,    16,    23,    67,    54,    68,    81,    56,    44,
      33,    45,    29,    30,    25,     7,     8,     2,     3
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,    43,    78,    35,    26,    55,     4,    36,    37,    22,
      84,    86,    87,    88,    32,    38,    12,   111,    39,    13,
      69,    70,    71,     1,    34,    89,    27,    79,    80,    82,
     118,     5,   109,   110,    85,    40,     4,    27,    41,    87,
      88,    97,    98,    99,   100,   101,    12,     6,   121,    13,
       9,    14,   102,    87,    88,    17,    42,    43,    20,   112,
     113,   114,   115,   116,   117,    24,   108,    35,    48,    42,
      43,    36,    37,    57,   119,    46,    63,    60,    58,    38,
      59,    47,    39,    64,    74,    75,    76,    42,    43,    38,
      49,    50,    39,    10,   104,    11,   105,    51,    52,    40,
      12,    27,    61,    13,    21,    65,    62,    66,    90,    91,
      92,    93,    72,    73,    74,    75,    76,    83,    94,    95,
      72,    73,    74,    75,    76,    90,    91,    92,    93,    96,
      87,    88,    88,   107,   120,    94,    95,    72,    73,    74,
      75,    76,    38,    49,    50,    39,    19,    18,    28,    31,
      51,    52,    72,    73,    74,    75,    76,     0,    53,    72,
      73,    74,    75,    76,    77,    72,    73,    74,    75,    76,
       0,   106,     0,     0,    96,    72,    73,    74,    75,    76,
       0,     0,   103
};

static const yytype_int8 yycheck[] =
{
      33,    33,    57,     5,    17,    36,    33,     9,    10,    17,
      65,    66,    21,    22,    41,    17,     3,    89,    20,     6,
      51,    52,    53,    17,    32,    34,    39,    58,    59,    60,
     102,     0,    87,    88,    65,    37,    33,    39,    40,    21,
      22,    72,    73,    74,    75,    76,     3,    17,   120,     6,
      41,     8,    34,    21,    22,    41,    89,    89,    31,    90,
      91,    92,    93,    94,    95,    32,    34,     5,    33,   102,
     102,     9,    10,    33,   105,    31,     4,    38,    31,    17,
      33,    37,    20,    11,    27,    28,    29,   120,   120,    17,
      18,    19,    20,    34,    34,    36,    36,    25,    26,    37,
       3,    39,    37,     6,     7,    33,    18,    35,    13,    14,
      15,    16,    25,    26,    27,    28,    29,    32,    23,    24,
      25,    26,    27,    28,    29,    13,    14,    15,    16,    34,
      21,    22,    22,    37,    12,    23,    24,    25,    26,    27,
      28,    29,    17,    18,    19,    20,    14,    11,    25,    25,
      25,    26,    25,    26,    27,    28,    29,    -1,    33,    25,
      26,    27,    28,    29,    37,    25,    26,    27,    28,    29,
      -1,    37,    -1,    -1,    34,    25,    26,    27,    28,    29,
      -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    59,    60,    33,     0,    17,    57,    58,    41,
      34,    36,     3,     6,     8,    43,    44,    41,    57,    44,
      31,     7,    43,    45,    32,    56,    17,    39,    53,    54,
      55,    59,    41,    52,    43,     5,     9,    10,    17,    20,
      37,    40,    47,    50,    51,    53,    31,    37,    33,    18,
      19,    25,    26,    33,    47,    48,    50,    33,    31,    33,
      38,    37,    18,     4,    11,    33,    35,    46,    48,    48,
      48,    48,    25,    26,    27,    28,    29,    37,    46,    48,
      48,    49,    48,    32,    46,    48,    46,    21,    22,    34,
      13,    14,    15,    16,    23,    24,    34,    48,    48,    48,
      48,    48,    34,    32,    34,    36,    37,    37,    34,    46,
      46,    51,    48,    48,    48,    48,    48,    48,    51,    48,
      12,    51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    49,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      54,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    59,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     1,     1,     1,     1,     3,     1,     2,     2,
       3,     3,     3,     3,     3,     0,     3,     1,     4,     1,
       4,     1,     2,     5,     7,     5,     3,     0,     2,     3,
       4,     7,     1,     1,     0,     2,     4,     3,     0,     3,
       1,     8,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* data_type: "int"  */
#line 55 "./parser/parser.y"
                { }
#line 1219 "./parser/parser.cpp"
    break;

  case 3: /* data_type: "byte"  */
#line 56 "./parser/parser.y"
                { }
#line 1225 "./parser/parser.cpp"
    break;

  case 4: /* type: data_type '[' ']'  */
#line 60 "./parser/parser.y"
                        { }
#line 1231 "./parser/parser.cpp"
    break;

  case 5: /* type: data_type  */
#line 61 "./parser/parser.y"
                        { }
#line 1237 "./parser/parser.cpp"
    break;

  case 6: /* r_type: data_type  */
#line 65 "./parser/parser.y"
                        {  }
#line 1243 "./parser/parser.cpp"
    break;

  case 7: /* r_type: "proc"  */
#line 66 "./parser/parser.y"
                        {  }
#line 1249 "./parser/parser.cpp"
    break;

  case 8: /* cond: "true"  */
#line 70 "./parser/parser.y"
                        {  }
#line 1255 "./parser/parser.cpp"
    break;

  case 9: /* cond: "false"  */
#line 71 "./parser/parser.y"
                        {  }
#line 1261 "./parser/parser.cpp"
    break;

  case 10: /* cond: '(' cond ')'  */
#line 72 "./parser/parser.y"
                        {  }
#line 1267 "./parser/parser.cpp"
    break;

  case 11: /* cond: '!' cond  */
#line 73 "./parser/parser.y"
                        {  }
#line 1273 "./parser/parser.cpp"
    break;

  case 12: /* cond: expr '<' expr  */
#line 74 "./parser/parser.y"
                        {  }
#line 1279 "./parser/parser.cpp"
    break;

  case 13: /* cond: expr '>' expr  */
#line 75 "./parser/parser.y"
                        {  }
#line 1285 "./parser/parser.cpp"
    break;

  case 14: /* cond: expr "==" expr  */
#line 76 "./parser/parser.y"
                        {  }
#line 1291 "./parser/parser.cpp"
    break;

  case 15: /* cond: expr "!=" expr  */
#line 77 "./parser/parser.y"
                        {  }
#line 1297 "./parser/parser.cpp"
    break;

  case 16: /* cond: expr "<=" expr  */
#line 78 "./parser/parser.y"
                        {  }
#line 1303 "./parser/parser.cpp"
    break;

  case 17: /* cond: expr ">=" expr  */
#line 79 "./parser/parser.y"
                        {  }
#line 1309 "./parser/parser.cpp"
    break;

  case 18: /* cond: cond '&' cond  */
#line 80 "./parser/parser.y"
                        {  }
#line 1315 "./parser/parser.cpp"
    break;

  case 19: /* cond: cond '|' cond  */
#line 81 "./parser/parser.y"
                        {  }
#line 1321 "./parser/parser.cpp"
    break;

  case 20: /* l_value: T_string  */
#line 85 "./parser/parser.y"
                        {  }
#line 1327 "./parser/parser.cpp"
    break;

  case 21: /* l_value: T_id '[' expr ']'  */
#line 86 "./parser/parser.y"
                        {  }
#line 1333 "./parser/parser.cpp"
    break;

  case 22: /* l_value: T_id  */
#line 87 "./parser/parser.y"
                        {  }
#line 1339 "./parser/parser.cpp"
    break;

  case 23: /* expr: T_char  */
#line 91 "./parser/parser.y"
                        {  }
#line 1345 "./parser/parser.cpp"
    break;

  case 24: /* expr: T_const  */
#line 92 "./parser/parser.y"
                        {  }
#line 1351 "./parser/parser.cpp"
    break;

  case 25: /* expr: l_value  */
#line 93 "./parser/parser.y"
                        {  }
#line 1357 "./parser/parser.cpp"
    break;

  case 26: /* expr: '(' expr ')'  */
#line 94 "./parser/parser.y"
                        {  }
#line 1363 "./parser/parser.cpp"
    break;

  case 27: /* expr: func_call  */
#line 95 "./parser/parser.y"
                        {  }
#line 1369 "./parser/parser.cpp"
    break;

  case 28: /* expr: '+' expr  */
#line 96 "./parser/parser.y"
                        {  }
#line 1375 "./parser/parser.cpp"
    break;

  case 29: /* expr: '-' expr  */
#line 97 "./parser/parser.y"
                        {  }
#line 1381 "./parser/parser.cpp"
    break;

  case 30: /* expr: expr '+' expr  */
#line 98 "./parser/parser.y"
                        {  }
#line 1387 "./parser/parser.cpp"
    break;

  case 31: /* expr: expr '-' expr  */
#line 99 "./parser/parser.y"
                        {  }
#line 1393 "./parser/parser.cpp"
    break;

  case 32: /* expr: expr '*' expr  */
#line 100 "./parser/parser.y"
                        {  }
#line 1399 "./parser/parser.cpp"
    break;

  case 33: /* expr: expr '/' expr  */
#line 101 "./parser/parser.y"
                        {  }
#line 1405 "./parser/parser.cpp"
    break;

  case 34: /* expr: expr '%' expr  */
#line 102 "./parser/parser.y"
                        {  }
#line 1411 "./parser/parser.cpp"
    break;

  case 36: /* expr_list: expr_list ',' expr  */
#line 108 "./parser/parser.y"
                            {}
#line 1417 "./parser/parser.cpp"
    break;

  case 37: /* expr_list: expr  */
#line 109 "./parser/parser.y"
                            {}
#line 1423 "./parser/parser.cpp"
    break;

  case 38: /* func_call: T_id '(' expr_list ')'  */
#line 113 "./parser/parser.y"
                             {}
#line 1429 "./parser/parser.cpp"
    break;

  case 39: /* stmt: ';'  */
#line 117 "./parser/parser.y"
                            {}
#line 1435 "./parser/parser.cpp"
    break;

  case 40: /* stmt: l_value '=' expr ';'  */
#line 118 "./parser/parser.y"
                            {}
#line 1441 "./parser/parser.cpp"
    break;

  case 41: /* stmt: compound_stmt  */
#line 119 "./parser/parser.y"
                            {}
#line 1447 "./parser/parser.cpp"
    break;

  case 42: /* stmt: func_call ';'  */
#line 120 "./parser/parser.y"
                            {}
#line 1453 "./parser/parser.cpp"
    break;

  case 43: /* stmt: "if" '(' cond ')' stmt  */
#line 121 "./parser/parser.y"
                                                         {}
#line 1459 "./parser/parser.cpp"
    break;

  case 44: /* stmt: "if" '(' cond ')' stmt "else" stmt  */
#line 122 "./parser/parser.y"
                                            {}
#line 1465 "./parser/parser.cpp"
    break;

  case 45: /* stmt: "while" '(' cond ')' stmt  */
#line 123 "./parser/parser.y"
                                            {}
#line 1471 "./parser/parser.cpp"
    break;

  case 46: /* stmt: "return" expr ';'  */
#line 124 "./parser/parser.y"
                                            {}
#line 1477 "./parser/parser.cpp"
    break;

  case 48: /* stmt_list: stmt_list stmt  */
#line 129 "./parser/parser.y"
                        {}
#line 1483 "./parser/parser.cpp"
    break;

  case 49: /* compound_stmt: '{' stmt_list '}'  */
#line 133 "./parser/parser.y"
                        {}
#line 1489 "./parser/parser.cpp"
    break;

  case 50: /* var_def: T_id ':' data_type ';'  */
#line 138 "./parser/parser.y"
                            {}
#line 1495 "./parser/parser.cpp"
    break;

  case 51: /* var_def: T_id ':' data_type '[' T_const ']' ';'  */
#line 139 "./parser/parser.y"
                                             {}
#line 1501 "./parser/parser.cpp"
    break;

  case 52: /* local_def: func_def  */
#line 143 "./parser/parser.y"
               {}
#line 1507 "./parser/parser.cpp"
    break;

  case 53: /* local_def: var_def  */
#line 144 "./parser/parser.y"
              {}
#line 1513 "./parser/parser.cpp"
    break;

  case 55: /* local_def_list: local_def_list local_def  */
#line 149 "./parser/parser.y"
                               {}
#line 1519 "./parser/parser.cpp"
    break;

  case 56: /* fpar_def: T_id ':' "reference" type  */
#line 155 "./parser/parser.y"
                                {}
#line 1525 "./parser/parser.cpp"
    break;

  case 57: /* fpar_def: T_id ':' type  */
#line 156 "./parser/parser.y"
                    {}
#line 1531 "./parser/parser.cpp"
    break;

  case 59: /* fpar_list: fpar_list ',' fpar_def  */
#line 161 "./parser/parser.y"
                             {}
#line 1537 "./parser/parser.cpp"
    break;

  case 60: /* fpar_list: fpar_def  */
#line 162 "./parser/parser.y"
               {}
#line 1543 "./parser/parser.cpp"
    break;

  case 61: /* func_def: T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt  */
#line 166 "./parser/parser.y"
                                                                     {}
#line 1549 "./parser/parser.cpp"
    break;

  case 62: /* program: func_def  */
#line 170 "./parser/parser.y"
               {}
#line 1555 "./parser/parser.cpp"
    break;


#line 1559 "./parser/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 173 "./parser/parser.y"


int main(int argc, char *argv[]) {
    
    yydebug = 1;

    int res = yyparse();
    if (res == 0) {
        std::cout << "Parsing successful" << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::cout << "Parsing failed at " << line_number << std::endl;
    exit(EXIT_FAILURE);
}
