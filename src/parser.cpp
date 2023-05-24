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
#line 1 "parser.y"

#include "AST.hpp"
#include <iostream>
#include <string>

int yylex(void);
extern BaseAST* Root; 

void yyerror(char *s)
{
	extern int yylineno;	// defined and maintained in lex
	extern char *yytext;	// defined and maintained in lex
	int len=strlen(yytext);
	int i;
	char buf[512]={0};
	for (i=0;i<len;++i)
	{
		sprintf(buf,"%s%d ",buf,yytext[i]);
	}
	fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);
}


using namespace std;


#line 98 "parser.cpp"

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
  YYSYMBOL_EQU = 3,                        /* EQU  */
  YYSYMBOL_NEQ = 4,                        /* NEQ  */
  YYSYMBOL_LES = 5,                        /* LES  */
  YYSYMBOL_LEQ = 6,                        /* LEQ  */
  YYSYMBOL_GRE = 7,                        /* GRE  */
  YYSYMBOL_GEQ = 8,                        /* GEQ  */
  YYSYMBOL_ADD = 9,                        /* ADD  */
  YYSYMBOL_SUB = 10,                       /* SUB  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_MOD = 13,                       /* MOD  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_BAND = 17,                      /* BAND  */
  YYSYMBOL_BOR = 18,                       /* BOR  */
  YYSYMBOL_BXOR = 19,                      /* BXOR  */
  YYSYMBOL_LPAREN = 20,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 21,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_SEMI = 25,                      /* SEMI  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_DOT = 27,                       /* DOT  */
  YYSYMBOL_COLON = 28,                     /* COLON  */
  YYSYMBOL_QUES = 29,                      /* QUES  */
  YYSYMBOL_INT = 30,                       /* INT  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_SHORT = 32,                     /* SHORT  */
  YYSYMBOL_VOID = 33,                      /* VOID  */
  YYSYMBOL_RETURN = 34,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 35,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 36,                     /* BREAK  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_FOR = 39,                       /* FOR  */
  YYSYMBOL_WHILE = 40,                     /* WHILE  */
  YYSYMBOL_CONST = 41,                     /* CONST  */
  YYSYMBOL_IDENTIFIER = 42,                /* IDENTIFIER  */
  YYSYMBOL_CONST_INT = 43,                 /* CONST_INT  */
  YYSYMBOL_CONST_CHAR = 44,                /* CONST_CHAR  */
  YYSYMBOL_CONST_FLOAT = 45,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_STR = 46,                 /* CONST_STR  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_Program = 48,                   /* Program  */
  YYSYMBOL_CompUnit = 49,                  /* CompUnit  */
  YYSYMBOL_Decl = 50,                      /* Decl  */
  YYSYMBOL_ConstDecl = 51,                 /* ConstDecl  */
  YYSYMBOL_ConstList = 52,                 /* ConstList  */
  YYSYMBOL_Btype = 53,                     /* Btype  */
  YYSYMBOL_ConstDef = 54,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 55,              /* ConstInitVal  */
  YYSYMBOL_VarDecl = 56,                   /* VarDecl  */
  YYSYMBOL_VarList = 57,                   /* VarList  */
  YYSYMBOL_VarDef = 58,                    /* VarDef  */
  YYSYMBOL_InitVal = 59,                   /* InitVal  */
  YYSYMBOL_FuncDef = 60,                   /* FuncDef  */
  YYSYMBOL_FuncType = 61,                  /* FuncType  */
  YYSYMBOL_Block = 62,                     /* Block  */
  YYSYMBOL_BlockItemNew = 63,              /* BlockItemNew  */
  YYSYMBOL_BlockItem = 64,                 /* BlockItem  */
  YYSYMBOL_Stmt = 65,                      /* Stmt  */
  YYSYMBOL_LVal = 66,                      /* LVal  */
  YYSYMBOL_ElseState = 67,                 /* ElseState  */
  YYSYMBOL_RetState = 68,                  /* RetState  */
  YYSYMBOL_PrimaryExp = 69,                /* PrimaryExp  */
  YYSYMBOL_Constant = 70,                  /* Constant  */
  YYSYMBOL_Exp = 71,                       /* Exp  */
  YYSYMBOL_ConstExp = 72                   /* ConstExp  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   341

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   110,   110,   114,   115,   120,   121,   126,   130,   131,
     136,   137,   138,   139,   144,   149,   154,   158,   159,   164,
     165,   170,   175,   180,   181,   182,   203,   207,   208,   213,
     214,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   239,   243,   244,   248,   249,   253,   254,   255,   259,
     260,   264,   265,   266,   267,   269,   270,   271,   272,   273,
     275,   276,   277,   278,   279,   280,   282,   283,   285,   286,
     287,   289,   293
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
  "\"end of file\"", "error", "\"invalid token\"", "EQU", "NEQ", "LES",
  "LEQ", "GRE", "GEQ", "ADD", "SUB", "MUL", "DIV", "MOD", "AND", "OR",
  "NOT", "BAND", "BOR", "BXOR", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "COMMA", "SEMI", "ASSIGN", "DOT", "COLON", "QUES", "INT", "CHAR",
  "SHORT", "VOID", "RETURN", "CONTINUE", "BREAK", "IF", "ELSE", "FOR",
  "WHILE", "CONST", "IDENTIFIER", "CONST_INT", "CONST_CHAR", "CONST_FLOAT",
  "CONST_STR", "$accept", "Program", "CompUnit", "Decl", "ConstDecl",
  "ConstList", "Btype", "ConstDef", "ConstInitVal", "VarDecl", "VarList",
  "VarDef", "InitVal", "FuncDef", "FuncType", "Block", "BlockItemNew",
  "BlockItem", "Stmt", "LVal", "ElseState", "RetState", "PrimaryExp",
  "Constant", "Exp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -98,    10,   -15,   -98,   -98,   -98,   -98,   -98,   -41,    -9,
      -7,    -1,   -98,   -98,    -3,    67,    67,    67,    67,   -98,
     -98,   -98,   -98,   -98,   -98,    67,    -2,    39,    15,   -98,
      50,   125,   -98,   -98,   -98,   -98,   -98,    29,   -98,   -98,
     -98,   -98,    47,   -98,   -98,   109,   -98,   229,   229,   229,
     133,    49,   229,   -98,   -98,    67,    67,    36,    54,   -98,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,   -98,    67,   -98,
     -98,   157,   181,    56,   -98,    67,     1,   205,   328,   328,
     120,   120,   120,   120,    33,    33,   -98,   -98,   -98,   270,
     253,   319,   287,   304,   229,    59,    59,   -98,    42,   -98,
     229,    29,   -98,   -98,    48,   -98,   -98,   -98,    36,   -98,
     -98,    59,   -98,   -98,   -98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    23,    25,    24,     3,     0,     0,
       0,     0,    28,    22,     0,     0,     0,     0,     0,    26,
      33,    11,    13,    12,    10,    45,     0,     0,     0,    35,
       0,     0,    41,    49,    50,    29,     5,     0,     6,    34,
      27,    30,    47,    51,    48,     0,    47,    52,    53,    54,
       0,     0,    44,    39,    38,     0,     0,     0,    19,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,    46,
      40,     0,     0,     0,     9,     0,     0,     0,    60,    61,
      62,    63,    64,    65,    55,    56,    57,    58,    59,    66,
      67,    68,    69,    70,    71,     0,     0,    72,     0,    20,
      21,     0,    16,    31,    43,    37,    14,    15,     0,     7,
      17,     0,    36,     8,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -98,   -98,   -98,   -98,   -98,   -98,    57,   -33,   -98,   -98,
     -98,   -22,   -98,   -98,   -98,    79,   -98,   -98,   -97,   -14,
     -98,   -98,   -98,   -98,   -13,   -98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    35,    36,   108,    37,    84,   116,    38,
      86,    59,   109,     7,     8,    39,    14,    40,    41,    46,
     122,    51,    43,    44,    45,   117
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,     9,    47,    48,    49,    50,    15,    16,   114,   115,
       3,    10,    52,    17,    11,     4,     5,    18,     6,    12,
      19,    12,    20,    53,   124,   111,   112,    21,    22,    23,
      24,    25,    26,    27,    28,    55,    29,    30,    31,    32,
      33,    34,    81,    82,    69,    70,    71,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    54,   104,   118,   119,    15,    16,
      56,    58,   110,    60,    80,    17,    15,    16,    83,    18,
      85,    12,   107,    17,    20,   123,   121,    18,    57,   120,
      13,    42,    42,    25,    26,    27,    28,     0,    29,    30,
       0,    32,    33,    34,     0,     0,     0,    42,     0,    32,
      33,    34,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     0,    74,    75,    76,    67,
      68,    69,    70,    71,    77,    78,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     0,
      74,    75,    76,     0,    79,    21,    22,    23,    24,    78,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,    74,    75,    76,     0,   105,     0,
       0,     0,     0,    78,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,     0,    74,    75,
      76,     0,   106,     0,     0,     0,     0,    78,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    74,    75,    76,     0,     0,     0,     0,     0,
     113,    78,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     0,    74,    75,    76,     0,
       0,     0,     0,     0,     0,    78,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     0,     0,
      74,    75,    76,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,     0,     0,     0,    74,    75,    76,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,     0,     0,     0,    74,     0,    76,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
       0,    74,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    63,    64,    65,    66,    67,    68,    69,
      70,    71
};

static const yytype_int8 yycheck[] =
{
      14,    42,    15,    16,    17,    18,     9,    10,   105,   106,
       0,    20,    25,    16,    21,    30,    31,    20,    33,    22,
      23,    22,    25,    25,   121,    24,    25,    30,    31,    32,
      33,    34,    35,    36,    37,    20,    39,    40,    41,    42,
      43,    44,    55,    56,    11,    12,    13,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    25,    78,    24,    25,     9,    10,
      20,    42,    85,    26,    25,    16,     9,    10,    42,    20,
      26,    22,    26,    16,    25,   118,    38,    20,    31,   111,
      11,   105,   106,    34,    35,    36,    37,    -1,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,   121,    -1,    42,
      43,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,     9,
      10,    11,    12,    13,    25,    26,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    -1,    21,    30,    31,    32,    33,    26,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    17,    18,    19,    -1,    21,    -1,
      -1,    -1,    -1,    26,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    -1,    21,    -1,    -1,    -1,    -1,    26,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    26,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    26,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      17,    18,    19,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    18,    19,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     5,     6,     7,     8,     9,    10,    11,
      12,    13
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    48,    49,     0,    30,    31,    33,    60,    61,    42,
      20,    21,    22,    62,    63,     9,    10,    16,    20,    23,
      25,    30,    31,    32,    33,    34,    35,    36,    37,    39,
      40,    41,    42,    43,    44,    50,    51,    53,    56,    62,
      64,    65,    66,    69,    70,    71,    66,    71,    71,    71,
      71,    68,    71,    25,    25,    20,    20,    53,    42,    58,
      26,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    17,    18,    19,    25,    26,    21,
      25,    71,    71,    42,    54,    26,    57,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    21,    21,    26,    52,    59,
      71,    24,    25,    25,    65,    65,    55,    72,    24,    25,
      58,    38,    67,    54,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    52,    52,
      53,    53,    53,    53,    54,    55,    56,    57,    57,    58,
      58,    59,    60,    61,    61,    61,    62,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     5,     3,     0,
       1,     1,     1,     1,     3,     1,     4,     3,     0,     1,
       3,     1,     5,     1,     1,     1,     3,     2,     0,     1,
       1,     4,     2,     1,     1,     1,     6,     5,     2,     2,
       3,     1,     2,     0,     1,     0,     3,     1,     1,     1,
       1,     1,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0
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
  case 2: /* Program: CompUnit  */
#line 110 "parser.y"
                                                                                                        {std::cout << "q" << std::endl; (yyval.astVal) = new ProgramAST((CompUnits*)(yyvsp[0].compUnits)); Root = (yyval.astVal);}
#line 1286 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit FuncDef  */
#line 114 "parser.y"
                                                                                        {std::cout << "w" << std::endl; (yyval.compUnits) = (CompUnits*)(yyvsp[-1].compUnits); (yyval.compUnits)->push_back((CompUnitAST*)(yyvsp[0].astVal)); }
#line 1292 "parser.cpp"
    break;

  case 4: /* CompUnit: %empty  */
#line 115 "parser.y"
                                                                                                        { (yyval.compUnits) = new CompUnits(); }
#line 1298 "parser.cpp"
    break;

  case 6: /* Decl: VarDecl  */
#line 121 "parser.y"
                                                        { std::cout << "2" << std::endl; (yyval.astVal) = (yyvsp[0].astVal); }
#line 1304 "parser.cpp"
    break;

  case 10: /* Btype: VOID  */
#line 136 "parser.y"
                                    { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1310 "parser.cpp"
    break;

  case 11: /* Btype: INT  */
#line 137 "parser.y"
                                    {std::cout << "6" << std::endl;  (yyval.strVal) = (yyvsp[0].strVal); }
#line 1316 "parser.cpp"
    break;

  case 12: /* Btype: SHORT  */
#line 138 "parser.y"
                                    { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1322 "parser.cpp"
    break;

  case 13: /* Btype: CHAR  */
#line 139 "parser.y"
                                    { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1328 "parser.cpp"
    break;

  case 16: /* VarDecl: Btype VarDef VarList SEMI  */
#line 154 "parser.y"
                                                    {std::cout << "3" << std::endl; (yyval.astVal) = new VarDeclAST(*(yyvsp[-3].strVal), *(yyvsp[-2].strVal));}
#line 1334 "parser.cpp"
    break;

  case 18: /* VarList: %empty  */
#line 159 "parser.y"
                                                    {std::cout << "5" << std::endl; }
#line 1340 "parser.cpp"
    break;

  case 19: /* VarDef: IDENTIFIER  */
#line 164 "parser.y"
                                                    {std::cout << "4" << std::endl; (yyval.strVal) = (yyvsp[0].strVal);}
#line 1346 "parser.cpp"
    break;

  case 22: /* FuncDef: FuncType IDENTIFIER LPAREN RPAREN Block  */
#line 175 "parser.y"
                                                { std::cout << "e" << std::endl;(yyval.astVal) = new FuncDefAST(*(yyvsp[-4].strVal), *(yyvsp[-3].strVal), (BlockAST*)(yyvsp[0].astVal));}
#line 1352 "parser.cpp"
    break;

  case 23: /* FuncType: INT  */
#line 180 "parser.y"
                                                { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1358 "parser.cpp"
    break;

  case 24: /* FuncType: VOID  */
#line 181 "parser.y"
                                                { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1364 "parser.cpp"
    break;

  case 25: /* FuncType: CHAR  */
#line 182 "parser.y"
                                                { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1370 "parser.cpp"
    break;

  case 26: /* Block: LBRACE BlockItemNew RBRACE  */
#line 203 "parser.y"
                                                { std::cout << "t" << std::endl;(yyval.astVal) = new BlockAST((Stmts*)(yyvsp[-1].stmts));}
#line 1376 "parser.cpp"
    break;

  case 27: /* BlockItemNew: BlockItemNew BlockItem  */
#line 207 "parser.y"
                                                                { (yyval.stmts) = (Stmts*)(yyvsp[-1].stmts); if ((yyvsp[0].astVal) != NULL)(yyval.stmts)->push_back((StmtAST*)(yyvsp[0].astVal)); }
#line 1382 "parser.cpp"
    break;

  case 28: /* BlockItemNew: %empty  */
#line 208 "parser.y"
                                                                                        { (yyval.stmts) = new Stmts(); }
#line 1388 "parser.cpp"
    break;

  case 29: /* BlockItem: Decl  */
#line 213 "parser.y"
                                                { (yyval.astVal) = (yyvsp[0].astVal);}
#line 1394 "parser.cpp"
    break;

  case 30: /* BlockItem: Stmt  */
#line 214 "parser.y"
                                                                                        { (yyval.astVal) = (yyvsp[0].astVal);}
#line 1400 "parser.cpp"
    break;

  case 32: /* Stmt: Exp SEMI  */
#line 227 "parser.y"
                                                                                { (yyval.astVal) = (yyvsp[-1].astVal); }
#line 1406 "parser.cpp"
    break;

  case 33: /* Stmt: SEMI  */
#line 228 "parser.y"
                                                                                        { (yyval.astVal) = NULL; }
#line 1412 "parser.cpp"
    break;

  case 34: /* Stmt: Block  */
#line 229 "parser.y"
                                                                                        { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1418 "parser.cpp"
    break;

  case 40: /* Stmt: RETURN RetState SEMI  */
#line 235 "parser.y"
                                                        {(yyval.astVal) = new ReturnStmtAST((ExprAST*)(yyvsp[-1].astVal));}
#line 1424 "parser.cpp"
    break;

  case 44: /* RetState: Exp  */
#line 248 "parser.y"
                                                                        {(yyval.astVal) = (yyvsp[0].astVal);}
#line 1430 "parser.cpp"
    break;

  case 48: /* PrimaryExp: Constant  */
#line 255 "parser.y"
                                                                { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1436 "parser.cpp"
    break;

  case 49: /* Constant: CONST_INT  */
#line 259 "parser.y"
                                                                { (yyval.astVal) =  new Constant((yyvsp[0].intVal)); }
#line 1442 "parser.cpp"
    break;

  case 51: /* Exp: PrimaryExp  */
#line 264 "parser.y"
                                                                { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1448 "parser.cpp"
    break;

  case 52: /* Exp: ADD Exp  */
#line 265 "parser.y"
                                                        { (yyval.astVal) = new MoncPlus((ExprAST*)(yyvsp[0].astVal)); }
#line 1454 "parser.cpp"
    break;

  case 53: /* Exp: SUB Exp  */
#line 266 "parser.y"
                                                        { (yyval.astVal) = new MoncMinus((ExprAST*)(yyvsp[0].astVal)); }
#line 1460 "parser.cpp"
    break;

  case 54: /* Exp: NOT Exp  */
#line 267 "parser.y"
                                                                { (yyval.astVal) = new LogicNot((ExprAST*)(yyvsp[0].astVal)); }
#line 1466 "parser.cpp"
    break;

  case 55: /* Exp: Exp ADD Exp  */
#line 269 "parser.y"
                                                                {(yyval.astVal) = new Addition((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1472 "parser.cpp"
    break;

  case 56: /* Exp: Exp SUB Exp  */
#line 270 "parser.y"
                                                                {(yyval.astVal) = new Subtraction((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1478 "parser.cpp"
    break;

  case 57: /* Exp: Exp MUL Exp  */
#line 271 "parser.y"
                                                                {(yyval.astVal) = new Multiplication((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1484 "parser.cpp"
    break;

  case 58: /* Exp: Exp DIV Exp  */
#line 272 "parser.y"
                                                                {(yyval.astVal) = new Division((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1490 "parser.cpp"
    break;

  case 59: /* Exp: Exp MOD Exp  */
#line 273 "parser.y"
                                                                {(yyval.astVal) = new Modulation((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1496 "parser.cpp"
    break;

  case 60: /* Exp: Exp EQU Exp  */
#line 275 "parser.y"
                                                                {(yyval.astVal) = new Equal((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1502 "parser.cpp"
    break;

  case 61: /* Exp: Exp NEQ Exp  */
#line 276 "parser.y"
                                                                {(yyval.astVal) = new NotEqual((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1508 "parser.cpp"
    break;

  case 62: /* Exp: Exp LES Exp  */
#line 277 "parser.y"
                                                                {(yyval.astVal) = new LessThan((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1514 "parser.cpp"
    break;

  case 63: /* Exp: Exp LEQ Exp  */
#line 278 "parser.y"
                                                                {(yyval.astVal) = new LessEqu((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1520 "parser.cpp"
    break;

  case 64: /* Exp: Exp GRE Exp  */
#line 279 "parser.y"
                                                                {(yyval.astVal) = new GreThan((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1526 "parser.cpp"
    break;

  case 65: /* Exp: Exp GEQ Exp  */
#line 280 "parser.y"
                                                                {(yyval.astVal) = new GreEqu((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1532 "parser.cpp"
    break;

  case 66: /* Exp: Exp AND Exp  */
#line 282 "parser.y"
                                                                {(yyval.astVal) = new AndOp((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1538 "parser.cpp"
    break;

  case 67: /* Exp: Exp OR Exp  */
#line 283 "parser.y"
                                                                {(yyval.astVal) = new OrOp((ExprAST*)(yyvsp[-2].astVal), (ExprAST*)(yyvsp[0].astVal));}
#line 1544 "parser.cpp"
    break;


#line 1548 "parser.cpp"

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

#line 295 "parser.y"

