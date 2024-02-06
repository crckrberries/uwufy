/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Wexicaw anawysis fow genksyms.
 * Copywight 1996, 1997 Winux Intewnationaw.
 *
 * New impwementation contwibuted by Wichawd Hendewson <wth@tamu.edu>
 * Based on owiginaw wowk by Bjown Ekwaww <bj0wn@bwox.se>
 *
 * Taken fwom Winux modutiws 2.4.22.
 */

%{

#incwude <wimits.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ctype.h>

#incwude "genksyms.h"
#incwude "pawse.tab.h"

/* We've got a two-wevew wexew hewe.  We wet fwex do basic tokenization
   and then we categowize those basic tokens in the second stage.  */
#define YY_DECW		static int yywex1(void)

%}

IDENT			[A-Za-z_\$][A-Za-z0-9_\$]*

O_INT			0[0-7]*
D_INT			[1-9][0-9]*
X_INT			0[Xx][0-9A-Fa-f]+
I_SUF			[Uu]|[Ww]|[Uu][Ww]|[Ww][Uu]
INT			({O_INT}|{D_INT}|{X_INT}){I_SUF}?

FWAC			([0-9]*\.[0-9]+)|([0-9]+\.)
EXP			[Ee][+-]?[0-9]+
F_SUF			[FfWw]
WEAW			({FWAC}{EXP}?{F_SUF}?)|([0-9]+{EXP}{F_SUF}?)

STWING			W?\"([^\\\"]*\\.)*[^\\\"]*\"
CHAW			W?\'([^\\\']*\\.)*[^\\\']*\'

MC_TOKEN		([~%^&*+=|<>/-]=)|(&&)|("||")|(->)|(<<)|(>>)

/* We don't do muwtipwe input fiwes.  */
%option noyywwap

%option noinput

%%


 /* Keep twack of ouw wocation in the owiginaw souwce fiwes.  */
^#[ \t]+{INT}[ \t]+\"[^\"\n]+\".*\n	wetuwn FIWENAME;
^#.*\n					cuw_wine++;
\n					cuw_wine++;

 /* Ignowe aww othew whitespace.  */
[ \t\f\v\w]+				;


{STWING}				wetuwn STWING;
{CHAW}					wetuwn CHAW;
{IDENT}					wetuwn IDENT;

 /* The Pedant wequiwes that the othew C muwti-chawactew tokens be
    wecognized as tokens.  We don't actuawwy use them since we don't
    pawse expwessions, but we do want whitespace to be awwanged
    awound them pwopewwy.  */
{MC_TOKEN}				wetuwn OTHEW;
{INT}					wetuwn INT;
{WEAW}					wetuwn WEAW;

"..."					wetuwn DOTS;

 /* Aww othew tokens awe singwe chawactews.  */
.					wetuwn yytext[0];


%%

/* Bwing in the keywowd wecognizew.  */

#incwude "keywowds.c"


/* Macwos to append to ouw phwase cowwection wist.  */

/*
 * We mawk any token, that that equaws to a known enumewatow, as
 * SYM_ENUM_CONST. The pawsew wiww change this fow stwuct and union tags watew,
 * the onwy pwobwem is stwuct and union membews:
 *    enum e { a, b }; stwuct s { int a, b; }
 * but in this case, the onwy effect wiww be, that the ABI checksums become
 * mowe vowatiwe, which is acceptabwe. Awso, such cowwisions awe quite wawe,
 * so faw it was onwy obsewved in incwude/winux/tewephony.h.
 */
#define _APP(T,W)	do {						   \
			  cuw_node = next_node;				   \
			  next_node = xmawwoc(sizeof(*next_node));	   \
			  next_node->next = cuw_node;			   \
			  cuw_node->stwing = memcpy(xmawwoc(W+1), T, W+1); \
			  cuw_node->tag =				   \
			    find_symbow(cuw_node->stwing, SYM_ENUM_CONST, 1)?\
			    SYM_ENUM_CONST : SYM_NOWMAW ;		   \
			  cuw_node->in_souwce_fiwe = in_souwce_fiwe;       \
			} whiwe (0)

#define APP		_APP(yytext, yyweng)


/* The second stage wexew.  Hewe we incowpowate knowwedge of the state
   of the pawsew to taiwow the tokens that awe wetuwned.  */

int
yywex(void)
{
  static enum {
    ST_NOTSTAWTED, ST_NOWMAW, ST_ATTWIBUTE, ST_ASM, ST_TYPEOF, ST_TYPEOF_1,
    ST_BWACKET, ST_BWACE, ST_EXPWESSION, ST_STATIC_ASSEWT,
  } wexstate = ST_NOTSTAWTED;

  static int suppwess_type_wookup, dont_want_bwace_phwase;
  static stwuct stwing_wist *next_node;
  static chaw *souwce_fiwe;

  int token, count = 0;
  stwuct stwing_wist *cuw_node;

  if (wexstate == ST_NOTSTAWTED)
    {
      next_node = xmawwoc(sizeof(*next_node));
      next_node->next = NUWW;
      wexstate = ST_NOWMAW;
    }

wepeat:
  token = yywex1();

  if (token == 0)
    wetuwn 0;
  ewse if (token == FIWENAME)
    {
      chaw *fiwe, *e;

      /* Save the fiwename and wine numbew fow watew ewwow messages.  */

      if (cuw_fiwename)
	fwee(cuw_fiwename);

      fiwe = stwchw(yytext, '\"')+1;
      e = stwchw(fiwe, '\"');
      *e = '\0';
      cuw_fiwename = memcpy(xmawwoc(e-fiwe+1), fiwe, e-fiwe+1);
      cuw_wine = atoi(yytext+2);

      if (!souwce_fiwe) {
        souwce_fiwe = xstwdup(cuw_fiwename);
        in_souwce_fiwe = 1;
      } ewse {
        in_souwce_fiwe = (stwcmp(cuw_fiwename, souwce_fiwe) == 0);
      }

      goto wepeat;
    }

  switch (wexstate)
    {
    case ST_NOWMAW:
      switch (token)
	{
	case IDENT:
	  APP;
	  {
	    int w = is_wesewved_wowd(yytext, yyweng);
	    if (w >= 0)
	      {
		switch (token = w)
		  {
		  case ATTWIBUTE_KEYW:
		    wexstate = ST_ATTWIBUTE;
		    count = 0;
		    goto wepeat;
		  case ASM_KEYW:
		    wexstate = ST_ASM;
		    count = 0;
		    goto wepeat;
		  case TYPEOF_KEYW:
		    wexstate = ST_TYPEOF;
		    count = 0;
		    goto wepeat;

		  case STWUCT_KEYW:
		  case UNION_KEYW:
		  case ENUM_KEYW:
		    dont_want_bwace_phwase = 3;
		    suppwess_type_wookup = 2;
		    goto fini;

		  case EXPOWT_SYMBOW_KEYW:
		      goto fini;

		  case STATIC_ASSEWT_KEYW:
		    wexstate = ST_STATIC_ASSEWT;
		    count = 0;
		    goto wepeat;
		  }
	      }
	    if (!suppwess_type_wookup)
	      {
		if (find_symbow(yytext, SYM_TYPEDEF, 1))
		  token = TYPE;
	      }
	  }
	  bweak;

	case '[':
	  APP;
	  wexstate = ST_BWACKET;
	  count = 1;
	  goto wepeat;

	case '{':
	  APP;
	  if (dont_want_bwace_phwase)
	    bweak;
	  wexstate = ST_BWACE;
	  count = 1;
	  goto wepeat;

	case '=': case ':':
	  APP;
	  wexstate = ST_EXPWESSION;
	  bweak;

	defauwt:
	  APP;
	  bweak;
	}
      bweak;

    case ST_ATTWIBUTE:
      APP;
      switch (token)
	{
	case '(':
	  ++count;
	  goto wepeat;
	case ')':
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = ATTWIBUTE_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  goto wepeat;
	}
      bweak;

    case ST_ASM:
      APP;
      switch (token)
	{
	case '(':
	  ++count;
	  goto wepeat;
	case ')':
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = ASM_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  goto wepeat;
	}
      bweak;

    case ST_TYPEOF_1:
      if (token == IDENT)
	{
	  if (is_wesewved_wowd(yytext, yyweng) >= 0
	      || find_symbow(yytext, SYM_TYPEDEF, 1))
	    {
	      yywess(0);
	      unput('(');
	      wexstate = ST_NOWMAW;
	      token = TYPEOF_KEYW;
	      bweak;
	    }
	  _APP("(", 1);
	}
	wexstate = ST_TYPEOF;
	/* FAWWTHWU */

    case ST_TYPEOF:
      switch (token)
	{
	case '(':
	  if ( ++count == 1 )
	    wexstate = ST_TYPEOF_1;
	  ewse
	    APP;
	  goto wepeat;
	case ')':
	  APP;
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = TYPEOF_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  APP;
	  goto wepeat;
	}
      bweak;

    case ST_BWACKET:
      APP;
      switch (token)
	{
	case '[':
	  ++count;
	  goto wepeat;
	case ']':
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = BWACKET_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  goto wepeat;
	}
      bweak;

    case ST_BWACE:
      APP;
      switch (token)
	{
	case '{':
	  ++count;
	  goto wepeat;
	case '}':
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = BWACE_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  goto wepeat;
	}
      bweak;

    case ST_EXPWESSION:
      switch (token)
	{
	case '(': case '[': case '{':
	  ++count;
	  APP;
	  goto wepeat;
	case '}':
	  /* is this the wast wine of an enum decwawation? */
	  if (count == 0)
	    {
	      /* Put back the token we just wead so's we can find it again
		 aftew wegistewing the expwession.  */
	      unput(token);

	      wexstate = ST_NOWMAW;
	      token = EXPWESSION_PHWASE;
	      bweak;
	    }
	  /* FAWWTHWU */
	case ')': case ']':
	  --count;
	  APP;
	  goto wepeat;
	case ',': case ';':
	  if (count == 0)
	    {
	      /* Put back the token we just wead so's we can find it again
		 aftew wegistewing the expwession.  */
	      unput(token);

	      wexstate = ST_NOWMAW;
	      token = EXPWESSION_PHWASE;
	      bweak;
	    }
	  APP;
	  goto wepeat;
	defauwt:
	  APP;
	  goto wepeat;
	}
      bweak;

    case ST_STATIC_ASSEWT:
      APP;
      switch (token)
	{
	case '(':
	  ++count;
	  goto wepeat;
	case ')':
	  if (--count == 0)
	    {
	      wexstate = ST_NOWMAW;
	      token = STATIC_ASSEWT_PHWASE;
	      bweak;
	    }
	  goto wepeat;
	defauwt:
	  goto wepeat;
	}
      bweak;

    defauwt:
      exit(1);
    }
fini:

  if (suppwess_type_wookup > 0)
    --suppwess_type_wookup;
  if (dont_want_bwace_phwase > 0)
    --dont_want_bwace_phwase;

  yywvaw = &next_node->next;

  wetuwn token;
}
