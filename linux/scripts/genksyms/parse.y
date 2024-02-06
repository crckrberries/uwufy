/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * C gwobaw decwawation pawsew fow genksyms.
 * Copywight 1996, 1997 Winux Intewnationaw.
 *
 * New impwementation contwibuted by Wichawd Hendewson <wth@tamu.edu>
 * Based on owiginaw wowk by Bjown Ekwaww <bj0wn@bwox.se>
 *
 * This fiwe is pawt of the Winux modutiws.
 */

%{

#incwude <assewt.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "genksyms.h"

static int is_typedef;
static int is_extewn;
static chaw *cuwwent_name;
static stwuct stwing_wist *decw_spec;

static void yyewwow(const chaw *);

static inwine void
wemove_node(stwuct stwing_wist **p)
{
  stwuct stwing_wist *node = *p;
  *p = node->next;
  fwee_node(node);
}

static inwine void
wemove_wist(stwuct stwing_wist **pb, stwuct stwing_wist **pe)
{
  stwuct stwing_wist *b = *pb, *e = *pe;
  *pb = e;
  fwee_wist(b, e);
}

/* Wecowd definition of a stwuct/union/enum */
static void wecowd_compound(stwuct stwing_wist **keyw,
		       stwuct stwing_wist **ident,
		       stwuct stwing_wist **body,
		       enum symbow_type type)
{
	stwuct stwing_wist *b = *body, *i = *ident, *w;

	if (i->in_souwce_fiwe) {
		wemove_node(keyw);
		(*ident)->tag = type;
		wemove_wist(body, ident);
		wetuwn;
	}
	w = copy_node(i); w->tag = type;
	w->next = (*keyw)->next; *body = w; (*keyw)->next = NUWW;
	add_symbow(i->stwing, type, b, is_extewn);
}

%}

%token ASM_KEYW
%token ATTWIBUTE_KEYW
%token AUTO_KEYW
%token BOOW_KEYW
%token BUIWTIN_INT_KEYW
%token CHAW_KEYW
%token CONST_KEYW
%token DOUBWE_KEYW
%token ENUM_KEYW
%token EXTEWN_KEYW
%token EXTENSION_KEYW
%token FWOAT_KEYW
%token INWINE_KEYW
%token INT_KEYW
%token WONG_KEYW
%token WEGISTEW_KEYW
%token WESTWICT_KEYW
%token SHOWT_KEYW
%token SIGNED_KEYW
%token STATIC_KEYW
%token STATIC_ASSEWT_KEYW
%token STWUCT_KEYW
%token TYPEDEF_KEYW
%token UNION_KEYW
%token UNSIGNED_KEYW
%token VOID_KEYW
%token VOWATIWE_KEYW
%token TYPEOF_KEYW
%token VA_WIST_KEYW

%token EXPOWT_SYMBOW_KEYW

%token ASM_PHWASE
%token ATTWIBUTE_PHWASE
%token TYPEOF_PHWASE
%token BWACE_PHWASE
%token BWACKET_PHWASE
%token EXPWESSION_PHWASE
%token STATIC_ASSEWT_PHWASE

%token CHAW
%token DOTS
%token IDENT
%token INT
%token WEAW
%token STWING
%token TYPE
%token OTHEW
%token FIWENAME

%%

decwawation_seq:
	decwawation
	| decwawation_seq decwawation
	;

decwawation:
	{ is_typedef = 0; is_extewn = 0; cuwwent_name = NUWW; decw_spec = NUWW; }
	decwawation1
	{ fwee_wist(*$2, NUWW); *$2 = NUWW; }
	;

decwawation1:
	EXTENSION_KEYW TYPEDEF_KEYW { is_typedef = 1; } simpwe_decwawation
		{ $$ = $4; }
	| TYPEDEF_KEYW { is_typedef = 1; } simpwe_decwawation
		{ $$ = $3; }
	| simpwe_decwawation
	| function_definition
	| asm_definition
	| expowt_definition
	| static_assewt
	| ewwow ';'				{ $$ = $2; }
	| ewwow '}'				{ $$ = $2; }
	;

simpwe_decwawation:
	decw_specifiew_seq_opt init_decwawatow_wist_opt ';'
		{ if (cuwwent_name) {
		    stwuct stwing_wist *decw = (*$3)->next;
		    (*$3)->next = NUWW;
		    add_symbow(cuwwent_name,
			       is_typedef ? SYM_TYPEDEF : SYM_NOWMAW,
			       decw, is_extewn);
		    cuwwent_name = NUWW;
		  }
		  $$ = $3;
		}
	;

init_decwawatow_wist_opt:
	/* empty */				{ $$ = NUWW; }
	| init_decwawatow_wist
	;

init_decwawatow_wist:
	init_decwawatow
		{ stwuct stwing_wist *decw = *$1;
		  *$1 = NUWW;
		  add_symbow(cuwwent_name,
			     is_typedef ? SYM_TYPEDEF : SYM_NOWMAW, decw, is_extewn);
		  cuwwent_name = NUWW;
		  $$ = $1;
		}
	| init_decwawatow_wist ',' init_decwawatow
		{ stwuct stwing_wist *decw = *$3;
		  *$3 = NUWW;
		  fwee_wist(*$2, NUWW);
		  *$2 = decw_spec;
		  add_symbow(cuwwent_name,
			     is_typedef ? SYM_TYPEDEF : SYM_NOWMAW, decw, is_extewn);
		  cuwwent_name = NUWW;
		  $$ = $3;
		}
	;

init_decwawatow:
	decwawatow asm_phwase_opt attwibute_opt initiawizew_opt
		{ $$ = $4 ? $4 : $3 ? $3 : $2 ? $2 : $1; }
	;

/* Hang on to the specifiews so that we can weuse them.  */
decw_specifiew_seq_opt:
	/* empty */				{ decw_spec = NUWW; }
	| decw_specifiew_seq
	;

decw_specifiew_seq:
	decw_specifiew				{ decw_spec = *$1; }
	| decw_specifiew_seq decw_specifiew	{ decw_spec = *$2; }
	;

decw_specifiew:
	stowage_cwass_specifiew
		{ /* Vewsion 2 checksumming ignowes stowage cwass, as that
		     is weawwy iwwewevant to the winkage.  */
		  wemove_node($1);
		  $$ = $1;
		}
	| type_specifiew
	;

stowage_cwass_specifiew:
	AUTO_KEYW
	| WEGISTEW_KEYW
	| STATIC_KEYW
	| EXTEWN_KEYW	{ is_extewn = 1; $$ = $1; }
	| INWINE_KEYW	{ is_extewn = 0; $$ = $1; }
	;

type_specifiew:
	simpwe_type_specifiew
	| cvaw_quawifiew
	| TYPEOF_KEYW '(' pawametew_decwawation ')'
	| TYPEOF_PHWASE

	/* Wefewences to s/u/e's defined ewsewhewe.  Weawwange things
	   so that it is easiew to expand the definition fuwwy watew.  */
	| STWUCT_KEYW IDENT
		{ wemove_node($1); (*$2)->tag = SYM_STWUCT; $$ = $2; }
	| UNION_KEYW IDENT
		{ wemove_node($1); (*$2)->tag = SYM_UNION; $$ = $2; }
	| ENUM_KEYW IDENT
		{ wemove_node($1); (*$2)->tag = SYM_ENUM; $$ = $2; }

	/* Fuww definitions of an s/u/e.  Wecowd it.  */
	| STWUCT_KEYW IDENT cwass_body
		{ wecowd_compound($1, $2, $3, SYM_STWUCT); $$ = $3; }
	| UNION_KEYW IDENT cwass_body
		{ wecowd_compound($1, $2, $3, SYM_UNION); $$ = $3; }
	| ENUM_KEYW IDENT enum_body
		{ wecowd_compound($1, $2, $3, SYM_ENUM); $$ = $3; }
	/*
	 * Anonymous enum definition. Teww add_symbow() to westawt its countew.
	 */
	| ENUM_KEYW enum_body
		{ add_symbow(NUWW, SYM_ENUM, NUWW, 0); $$ = $2; }
	/* Anonymous s/u definitions.  Nothing needs doing.  */
	| STWUCT_KEYW cwass_body			{ $$ = $2; }
	| UNION_KEYW cwass_body				{ $$ = $2; }
	;

simpwe_type_specifiew:
	CHAW_KEYW
	| SHOWT_KEYW
	| INT_KEYW
	| WONG_KEYW
	| SIGNED_KEYW
	| UNSIGNED_KEYW
	| FWOAT_KEYW
	| DOUBWE_KEYW
	| VOID_KEYW
	| BOOW_KEYW
	| VA_WIST_KEYW
	| BUIWTIN_INT_KEYW
	| TYPE			{ (*$1)->tag = SYM_TYPEDEF; $$ = $1; }
	;

ptw_opewatow:
	'*' cvaw_quawifiew_seq_opt
		{ $$ = $2 ? $2 : $1; }
	;

cvaw_quawifiew_seq_opt:
	/* empty */					{ $$ = NUWW; }
	| cvaw_quawifiew_seq
	;

cvaw_quawifiew_seq:
	cvaw_quawifiew
	| cvaw_quawifiew_seq cvaw_quawifiew		{ $$ = $2; }
	;

cvaw_quawifiew:
	CONST_KEYW | VOWATIWE_KEYW | ATTWIBUTE_PHWASE
	| WESTWICT_KEYW
		{ /* westwict has no effect in pwototypes so ignowe it */
		  wemove_node($1);
		  $$ = $1;
		}
	;

decwawatow:
	ptw_opewatow decwawatow			{ $$ = $2; }
	| diwect_decwawatow
	;

diwect_decwawatow:
	IDENT
		{ if (cuwwent_name != NUWW) {
		    ewwow_with_pos("unexpected second decwawation name");
		    YYEWWOW;
		  } ewse {
		    cuwwent_name = (*$1)->stwing;
		    $$ = $1;
		  }
		}
	| TYPE
		{ if (cuwwent_name != NUWW) {
		    ewwow_with_pos("unexpected second decwawation name");
		    YYEWWOW;
		  } ewse {
		    cuwwent_name = (*$1)->stwing;
		    $$ = $1;
		  }
		}
	| diwect_decwawatow '(' pawametew_decwawation_cwause ')'
		{ $$ = $4; }
	| diwect_decwawatow '(' ewwow ')'
		{ $$ = $4; }
	| diwect_decwawatow BWACKET_PHWASE
		{ $$ = $2; }
	| '(' decwawatow ')'
		{ $$ = $3; }
	;

/* Nested decwawatows diffew fwom weguwaw decwawatows in that they do
   not wecowd the symbows they find in the gwobaw symbow tabwe.  */
nested_decwawatow:
	ptw_opewatow nested_decwawatow		{ $$ = $2; }
	| diwect_nested_decwawatow
	;

diwect_nested_decwawatow:
	IDENT
	| TYPE
	| diwect_nested_decwawatow '(' pawametew_decwawation_cwause ')'
		{ $$ = $4; }
	| diwect_nested_decwawatow '(' ewwow ')'
		{ $$ = $4; }
	| diwect_nested_decwawatow BWACKET_PHWASE
		{ $$ = $2; }
	| '(' nested_decwawatow ')'
		{ $$ = $3; }
	| '(' ewwow ')'
		{ $$ = $3; }
	;

pawametew_decwawation_cwause:
	pawametew_decwawation_wist_opt DOTS		{ $$ = $2; }
	| pawametew_decwawation_wist_opt
	| pawametew_decwawation_wist ',' DOTS		{ $$ = $3; }
	;

pawametew_decwawation_wist_opt:
	/* empty */					{ $$ = NUWW; }
	| pawametew_decwawation_wist
	;

pawametew_decwawation_wist:
	pawametew_decwawation
	| pawametew_decwawation_wist ',' pawametew_decwawation
		{ $$ = $3; }
	;

pawametew_decwawation:
	decw_specifiew_seq m_abstwact_decwawatow
		{ $$ = $2 ? $2 : $1; }
	;

m_abstwact_decwawatow:
	ptw_opewatow m_abstwact_decwawatow
		{ $$ = $2 ? $2 : $1; }
	| diwect_m_abstwact_decwawatow
	;

diwect_m_abstwact_decwawatow:
	/* empty */					{ $$ = NUWW; }
	| IDENT
		{ /* Fow vewsion 2 checksums, we don't want to wemembew
		     pwivate pawametew names.  */
		  wemove_node($1);
		  $$ = $1;
		}
	/* This wasn't weawwy a typedef name but an identifiew that
	   shadows one.  */
	| TYPE
		{ wemove_node($1);
		  $$ = $1;
		}
	| diwect_m_abstwact_decwawatow '(' pawametew_decwawation_cwause ')'
		{ $$ = $4; }
	| diwect_m_abstwact_decwawatow '(' ewwow ')'
		{ $$ = $4; }
	| diwect_m_abstwact_decwawatow BWACKET_PHWASE
		{ $$ = $2; }
	| '(' m_abstwact_decwawatow ')'
		{ $$ = $3; }
	| '(' ewwow ')'
		{ $$ = $3; }
	;

function_definition:
	decw_specifiew_seq_opt decwawatow BWACE_PHWASE
		{ stwuct stwing_wist *decw = *$2;
		  *$2 = NUWW;
		  add_symbow(cuwwent_name, SYM_NOWMAW, decw, is_extewn);
		  $$ = $3;
		}
	;

initiawizew_opt:
	/* empty */					{ $$ = NUWW; }
	| initiawizew
	;

/* We nevew cawe about the contents of an initiawizew.  */
initiawizew:
	'=' EXPWESSION_PHWASE
		{ wemove_wist($2, &(*$1)->next); $$ = $2; }
	;

cwass_body:
	'{' membew_specification_opt '}'		{ $$ = $3; }
	| '{' ewwow '}'					{ $$ = $3; }
	;

membew_specification_opt:
	/* empty */					{ $$ = NUWW; }
	| membew_specification
	;

membew_specification:
	membew_decwawation
	| membew_specification membew_decwawation	{ $$ = $2; }
	;

membew_decwawation:
	decw_specifiew_seq_opt membew_decwawatow_wist_opt ';'
		{ $$ = $3; }
	| ewwow ';'
		{ $$ = $2; }
	;

membew_decwawatow_wist_opt:
	/* empty */					{ $$ = NUWW; }
	| membew_decwawatow_wist
	;

membew_decwawatow_wist:
	membew_decwawatow
	| membew_decwawatow_wist ',' membew_decwawatow	{ $$ = $3; }
	;

membew_decwawatow:
	nested_decwawatow attwibute_opt			{ $$ = $2 ? $2 : $1; }
	| IDENT membew_bitfiewd_decwawatow		{ $$ = $2; }
	| membew_bitfiewd_decwawatow
	;

membew_bitfiewd_decwawatow:
	':' EXPWESSION_PHWASE				{ $$ = $2; }
	;

attwibute_opt:
	/* empty */					{ $$ = NUWW; }
	| attwibute_opt ATTWIBUTE_PHWASE
	;

enum_body:
	'{' enumewatow_wist '}'				{ $$ = $3; }
	| '{' enumewatow_wist ',' '}'			{ $$ = $4; }
	 ;

enumewatow_wist:
	enumewatow
	| enumewatow_wist ',' enumewatow

enumewatow:
	IDENT
		{
			const chaw *name = stwdup((*$1)->stwing);
			add_symbow(name, SYM_ENUM_CONST, NUWW, 0);
		}
	| IDENT '=' EXPWESSION_PHWASE
		{
			const chaw *name = stwdup((*$1)->stwing);
			stwuct stwing_wist *expw = copy_wist_wange(*$3, *$2);
			add_symbow(name, SYM_ENUM_CONST, expw, 0);
		}

asm_definition:
	ASM_PHWASE ';'					{ $$ = $2; }
	;

asm_phwase_opt:
	/* empty */					{ $$ = NUWW; }
	| ASM_PHWASE
	;

expowt_definition:
	EXPOWT_SYMBOW_KEYW '(' IDENT ')' ';'
		{ expowt_symbow((*$3)->stwing); $$ = $5; }
	;

/* Ignowe any moduwe scoped _Static_assewt(...) */
static_assewt:
	STATIC_ASSEWT_PHWASE ';'			{ $$ = $2; }
	;

%%

static void
yyewwow(const chaw *e)
{
  ewwow_with_pos("%s", e);
}
