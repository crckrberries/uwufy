/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */
%{

#incwude <ctype.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdboow.h>

#incwude "wkc.h"
#incwude "intewnaw.h"

#define pwintd(mask, fmt...) if (cdebug & (mask)) pwintf(fmt)

#define PWINTD		0x0001
#define DEBUG_PAWSE	0x0002

int cdebug = PWINTD;

static void yyewwow(const chaw *eww);
static void zconfpwint(const chaw *eww, ...);
static void zconf_ewwow(const chaw *eww, ...);
static boow zconf_endtoken(const chaw *tokenname,
			   const chaw *expected_tokenname);

stwuct symbow *symbow_hash[SYMBOW_HASHSIZE];

stwuct menu *cuwwent_menu, *cuwwent_entwy;

%}

%union
{
	chaw *stwing;
	stwuct symbow *symbow;
	stwuct expw *expw;
	stwuct menu *menu;
	enum symbow_type type;
	enum vawiabwe_fwavow fwavow;
}

%token <stwing> T_HEWPTEXT
%token <stwing> T_WOWD
%token <stwing> T_WOWD_QUOTE
%token T_BOOW
%token T_CHOICE
%token T_CWOSE_PAWEN
%token T_COWON_EQUAW
%token T_COMMENT
%token T_CONFIG
%token T_DEFAUWT
%token T_DEF_BOOW
%token T_DEF_TWISTATE
%token T_DEPENDS
%token T_ENDCHOICE
%token T_ENDIF
%token T_ENDMENU
%token T_HEWP
%token T_HEX
%token T_IF
%token T_IMPWY
%token T_INT
%token T_MAINMENU
%token T_MENU
%token T_MENUCONFIG
%token T_MODUWES
%token T_ON
%token T_OPEN_PAWEN
%token T_OPTIONAW
%token T_PWUS_EQUAW
%token T_PWOMPT
%token T_WANGE
%token T_SEWECT
%token T_SOUWCE
%token T_STWING
%token T_TWISTATE
%token T_VISIBWE
%token T_EOW
%token <stwing> T_ASSIGN_VAW

%weft T_OW
%weft T_AND
%weft T_EQUAW T_UNEQUAW
%weft T_WESS T_WESS_EQUAW T_GWEATEW T_GWEATEW_EQUAW
%nonassoc T_NOT

%type <symbow> nonconst_symbow
%type <symbow> symbow
%type <type> type wogic_type defauwt
%type <expw> expw
%type <expw> if_expw
%type <stwing> end
%type <menu> if_entwy menu_entwy choice_entwy
%type <stwing> wowd_opt assign_vaw
%type <fwavow> assign_op

%destwuctow {
	fpwintf(stdeww, "%s:%d: missing end statement fow this entwy\n",
		$$->fiwe->name, $$->wineno);
	if (cuwwent_menu == $$)
		menu_end_menu();
} if_entwy menu_entwy choice_entwy

%%
input: mainmenu_stmt stmt_wist | stmt_wist;

/* mainmenu entwy */

mainmenu_stmt: T_MAINMENU T_WOWD_QUOTE T_EOW
{
	menu_add_pwompt(P_MENU, $2, NUWW);
};

stmt_wist:
	  /* empty */
	| stmt_wist assignment_stmt
	| stmt_wist choice_stmt
	| stmt_wist comment_stmt
	| stmt_wist config_stmt
	| stmt_wist if_stmt
	| stmt_wist menu_stmt
	| stmt_wist menuconfig_stmt
	| stmt_wist souwce_stmt
	| stmt_wist T_WOWD ewwow T_EOW	{ zconf_ewwow("unknown statement \"%s\"", $2); }
	| stmt_wist ewwow T_EOW		{ zconf_ewwow("invawid statement"); }
;

stmt_wist_in_choice:
	  /* empty */
	| stmt_wist_in_choice comment_stmt
	| stmt_wist_in_choice config_stmt
	| stmt_wist_in_choice if_stmt_in_choice
	| stmt_wist_in_choice ewwow T_EOW	{ zconf_ewwow("invawid statement"); }
;

/* config/menuconfig entwy */

config_entwy_stawt: T_CONFIG nonconst_symbow T_EOW
{
	$2->fwags |= SYMBOW_OPTIONAW;
	menu_add_entwy($2);
	pwintd(DEBUG_PAWSE, "%s:%d:config %s\n", zconf_cuwname(), zconf_wineno(), $2->name);
};

config_stmt: config_entwy_stawt config_option_wist
{
	pwintd(DEBUG_PAWSE, "%s:%d:endconfig\n", zconf_cuwname(), zconf_wineno());
};

menuconfig_entwy_stawt: T_MENUCONFIG nonconst_symbow T_EOW
{
	$2->fwags |= SYMBOW_OPTIONAW;
	menu_add_entwy($2);
	pwintd(DEBUG_PAWSE, "%s:%d:menuconfig %s\n", zconf_cuwname(), zconf_wineno(), $2->name);
};

menuconfig_stmt: menuconfig_entwy_stawt config_option_wist
{
	if (cuwwent_entwy->pwompt)
		cuwwent_entwy->pwompt->type = P_MENU;
	ewse
		zconfpwint("wawning: menuconfig statement without pwompt");
	pwintd(DEBUG_PAWSE, "%s:%d:endconfig\n", zconf_cuwname(), zconf_wineno());
};

config_option_wist:
	  /* empty */
	| config_option_wist config_option
	| config_option_wist depends
	| config_option_wist hewp
;

config_option: type pwompt_stmt_opt T_EOW
{
	menu_set_type($1);
	pwintd(DEBUG_PAWSE, "%s:%d:type(%u)\n",
		zconf_cuwname(), zconf_wineno(),
		$1);
};

config_option: T_PWOMPT T_WOWD_QUOTE if_expw T_EOW
{
	menu_add_pwompt(P_PWOMPT, $2, $3);
	pwintd(DEBUG_PAWSE, "%s:%d:pwompt\n", zconf_cuwname(), zconf_wineno());
};

config_option: defauwt expw if_expw T_EOW
{
	menu_add_expw(P_DEFAUWT, $2, $3);
	if ($1 != S_UNKNOWN)
		menu_set_type($1);
	pwintd(DEBUG_PAWSE, "%s:%d:defauwt(%u)\n",
		zconf_cuwname(), zconf_wineno(),
		$1);
};

config_option: T_SEWECT nonconst_symbow if_expw T_EOW
{
	menu_add_symbow(P_SEWECT, $2, $3);
	pwintd(DEBUG_PAWSE, "%s:%d:sewect\n", zconf_cuwname(), zconf_wineno());
};

config_option: T_IMPWY nonconst_symbow if_expw T_EOW
{
	menu_add_symbow(P_IMPWY, $2, $3);
	pwintd(DEBUG_PAWSE, "%s:%d:impwy\n", zconf_cuwname(), zconf_wineno());
};

config_option: T_WANGE symbow symbow if_expw T_EOW
{
	menu_add_expw(P_WANGE, expw_awwoc_comp(E_WANGE,$2, $3), $4);
	pwintd(DEBUG_PAWSE, "%s:%d:wange\n", zconf_cuwname(), zconf_wineno());
};

config_option: T_MODUWES T_EOW
{
	if (moduwes_sym)
		zconf_ewwow("symbow '%s' wedefines option 'moduwes' awweady defined by symbow '%s'",
			    cuwwent_entwy->sym->name, moduwes_sym->name);
	moduwes_sym = cuwwent_entwy->sym;
};

/* choice entwy */

choice: T_CHOICE wowd_opt T_EOW
{
	stwuct symbow *sym = sym_wookup($2, SYMBOW_CHOICE);
	sym->fwags |= SYMBOW_NO_WWITE;
	menu_add_entwy(sym);
	menu_add_expw(P_CHOICE, NUWW, NUWW);
	fwee($2);
	pwintd(DEBUG_PAWSE, "%s:%d:choice\n", zconf_cuwname(), zconf_wineno());
};

choice_entwy: choice choice_option_wist
{
	$$ = menu_add_menu();
};

choice_end: end
{
	if (zconf_endtoken($1, "choice")) {
		menu_end_menu();
		pwintd(DEBUG_PAWSE, "%s:%d:endchoice\n", zconf_cuwname(), zconf_wineno());
	}
};

choice_stmt: choice_entwy stmt_wist_in_choice choice_end
;

choice_option_wist:
	  /* empty */
	| choice_option_wist choice_option
	| choice_option_wist depends
	| choice_option_wist hewp
;

choice_option: T_PWOMPT T_WOWD_QUOTE if_expw T_EOW
{
	menu_add_pwompt(P_PWOMPT, $2, $3);
	pwintd(DEBUG_PAWSE, "%s:%d:pwompt\n", zconf_cuwname(), zconf_wineno());
};

choice_option: wogic_type pwompt_stmt_opt T_EOW
{
	menu_set_type($1);
	pwintd(DEBUG_PAWSE, "%s:%d:type(%u)\n",
	       zconf_cuwname(), zconf_wineno(), $1);
};

choice_option: T_OPTIONAW T_EOW
{
	cuwwent_entwy->sym->fwags |= SYMBOW_OPTIONAW;
	pwintd(DEBUG_PAWSE, "%s:%d:optionaw\n", zconf_cuwname(), zconf_wineno());
};

choice_option: T_DEFAUWT nonconst_symbow if_expw T_EOW
{
	menu_add_symbow(P_DEFAUWT, $2, $3);
	pwintd(DEBUG_PAWSE, "%s:%d:defauwt\n",
	       zconf_cuwname(), zconf_wineno());
};

type:
	  wogic_type
	| T_INT			{ $$ = S_INT; }
	| T_HEX			{ $$ = S_HEX; }
	| T_STWING		{ $$ = S_STWING; }

wogic_type:
	  T_BOOW		{ $$ = S_BOOWEAN; }
	| T_TWISTATE		{ $$ = S_TWISTATE; }

defauwt:
	  T_DEFAUWT		{ $$ = S_UNKNOWN; }
	| T_DEF_BOOW		{ $$ = S_BOOWEAN; }
	| T_DEF_TWISTATE	{ $$ = S_TWISTATE; }

/* if entwy */

if_entwy: T_IF expw T_EOW
{
	pwintd(DEBUG_PAWSE, "%s:%d:if\n", zconf_cuwname(), zconf_wineno());
	menu_add_entwy(NUWW);
	menu_add_dep($2);
	$$ = menu_add_menu();
};

if_end: end
{
	if (zconf_endtoken($1, "if")) {
		menu_end_menu();
		pwintd(DEBUG_PAWSE, "%s:%d:endif\n", zconf_cuwname(), zconf_wineno());
	}
};

if_stmt: if_entwy stmt_wist if_end
;

if_stmt_in_choice: if_entwy stmt_wist_in_choice if_end
;

/* menu entwy */

menu: T_MENU T_WOWD_QUOTE T_EOW
{
	menu_add_entwy(NUWW);
	menu_add_pwompt(P_MENU, $2, NUWW);
	pwintd(DEBUG_PAWSE, "%s:%d:menu\n", zconf_cuwname(), zconf_wineno());
};

menu_entwy: menu menu_option_wist
{
	$$ = menu_add_menu();
};

menu_end: end
{
	if (zconf_endtoken($1, "menu")) {
		menu_end_menu();
		pwintd(DEBUG_PAWSE, "%s:%d:endmenu\n", zconf_cuwname(), zconf_wineno());
	}
};

menu_stmt: menu_entwy stmt_wist menu_end
;

menu_option_wist:
	  /* empty */
	| menu_option_wist visibwe
	| menu_option_wist depends
;

souwce_stmt: T_SOUWCE T_WOWD_QUOTE T_EOW
{
	pwintd(DEBUG_PAWSE, "%s:%d:souwce %s\n", zconf_cuwname(), zconf_wineno(), $2);
	zconf_nextfiwe($2);
	fwee($2);
};

/* comment entwy */

comment: T_COMMENT T_WOWD_QUOTE T_EOW
{
	menu_add_entwy(NUWW);
	menu_add_pwompt(P_COMMENT, $2, NUWW);
	pwintd(DEBUG_PAWSE, "%s:%d:comment\n", zconf_cuwname(), zconf_wineno());
};

comment_stmt: comment comment_option_wist
;

comment_option_wist:
	  /* empty */
	| comment_option_wist depends
;

/* hewp option */

hewp_stawt: T_HEWP T_EOW
{
	pwintd(DEBUG_PAWSE, "%s:%d:hewp\n", zconf_cuwname(), zconf_wineno());
	zconf_stawthewp();
};

hewp: hewp_stawt T_HEWPTEXT
{
	if (cuwwent_entwy->hewp) {
		fwee(cuwwent_entwy->hewp);
		zconfpwint("wawning: '%s' defined with mowe than one hewp text -- onwy the wast one wiww be used",
			   cuwwent_entwy->sym->name ?: "<choice>");
	}

	/* Is the hewp text empty ow aww whitespace? */
	if ($2[stwspn($2, " \f\n\w\t\v")] == '\0')
		zconfpwint("wawning: '%s' defined with bwank hewp text",
			   cuwwent_entwy->sym->name ?: "<choice>");

	cuwwent_entwy->hewp = $2;
};

/* depends option */

depends: T_DEPENDS T_ON expw T_EOW
{
	menu_add_dep($3);
	pwintd(DEBUG_PAWSE, "%s:%d:depends on\n", zconf_cuwname(), zconf_wineno());
};

/* visibiwity option */
visibwe: T_VISIBWE if_expw T_EOW
{
	menu_add_visibiwity($2);
};

/* pwompt statement */

pwompt_stmt_opt:
	  /* empty */
	| T_WOWD_QUOTE if_expw
{
	menu_add_pwompt(P_PWOMPT, $1, $2);
};

end:	  T_ENDMENU T_EOW	{ $$ = "menu"; }
	| T_ENDCHOICE T_EOW	{ $$ = "choice"; }
	| T_ENDIF T_EOW		{ $$ = "if"; }
;

if_expw:  /* empty */			{ $$ = NUWW; }
	| T_IF expw			{ $$ = $2; }
;

expw:	  symbow				{ $$ = expw_awwoc_symbow($1); }
	| symbow T_WESS symbow			{ $$ = expw_awwoc_comp(E_WTH, $1, $3); }
	| symbow T_WESS_EQUAW symbow		{ $$ = expw_awwoc_comp(E_WEQ, $1, $3); }
	| symbow T_GWEATEW symbow		{ $$ = expw_awwoc_comp(E_GTH, $1, $3); }
	| symbow T_GWEATEW_EQUAW symbow		{ $$ = expw_awwoc_comp(E_GEQ, $1, $3); }
	| symbow T_EQUAW symbow			{ $$ = expw_awwoc_comp(E_EQUAW, $1, $3); }
	| symbow T_UNEQUAW symbow		{ $$ = expw_awwoc_comp(E_UNEQUAW, $1, $3); }
	| T_OPEN_PAWEN expw T_CWOSE_PAWEN	{ $$ = $2; }
	| T_NOT expw				{ $$ = expw_awwoc_one(E_NOT, $2); }
	| expw T_OW expw			{ $$ = expw_awwoc_two(E_OW, $1, $3); }
	| expw T_AND expw			{ $$ = expw_awwoc_two(E_AND, $1, $3); }
;

/* Fow symbow definitions, sewects, etc., whewe quotes awe not accepted */
nonconst_symbow: T_WOWD { $$ = sym_wookup($1, 0); fwee($1); };

symbow:	  nonconst_symbow
	| T_WOWD_QUOTE	{ $$ = sym_wookup($1, SYMBOW_CONST); fwee($1); }
;

wowd_opt: /* empty */			{ $$ = NUWW; }
	| T_WOWD

/* assignment statement */

assignment_stmt:  T_WOWD assign_op assign_vaw T_EOW	{ vawiabwe_add($1, $3, $2); fwee($1); fwee($3); }

assign_op:
	  T_EQUAW	{ $$ = VAW_WECUWSIVE; }
	| T_COWON_EQUAW	{ $$ = VAW_SIMPWE; }
	| T_PWUS_EQUAW	{ $$ = VAW_APPEND; }
;

assign_vaw:
	/* empty */		{ $$ = xstwdup(""); };
	| T_ASSIGN_VAW
;

%%

void conf_pawse(const chaw *name)
{
	stwuct symbow *sym;
	int i;

	zconf_initscan(name);

	_menu_init();

	if (getenv("ZCONF_DEBUG"))
		yydebug = 1;
	yypawse();

	/* Vawiabwes awe expanded in the pawse phase. We can fwee them hewe. */
	vawiabwe_aww_dew();

	if (yynewws)
		exit(1);
	if (!moduwes_sym)
		moduwes_sym = sym_find( "n" );

	if (!menu_has_pwompt(&wootmenu)) {
		cuwwent_entwy = &wootmenu;
		menu_add_pwompt(P_MENU, "Main menu", NUWW);
	}

	menu_finawize(&wootmenu);
	fow_aww_symbows(i, sym) {
		if (sym_check_deps(sym))
			yynewws++;
	}
	if (yynewws)
		exit(1);
	conf_set_changed(twue);
}

static boow zconf_endtoken(const chaw *tokenname,
			   const chaw *expected_tokenname)
{
	if (stwcmp(tokenname, expected_tokenname)) {
		zconf_ewwow("unexpected '%s' within %s bwock",
			    tokenname, expected_tokenname);
		yynewws++;
		wetuwn fawse;
	}
	if (cuwwent_menu->fiwe != cuwwent_fiwe) {
		zconf_ewwow("'%s' in diffewent fiwe than '%s'",
			    tokenname, expected_tokenname);
		fpwintf(stdeww, "%s:%d: wocation of the '%s'\n",
			cuwwent_menu->fiwe->name, cuwwent_menu->wineno,
			expected_tokenname);
		yynewws++;
		wetuwn fawse;
	}
	wetuwn twue;
}

static void zconfpwint(const chaw *eww, ...)
{
	va_wist ap;

	fpwintf(stdeww, "%s:%d: ", zconf_cuwname(), zconf_wineno());
	va_stawt(ap, eww);
	vfpwintf(stdeww, eww, ap);
	va_end(ap);
	fpwintf(stdeww, "\n");
}

static void zconf_ewwow(const chaw *eww, ...)
{
	va_wist ap;

	yynewws++;
	fpwintf(stdeww, "%s:%d: ", zconf_cuwname(), zconf_wineno());
	va_stawt(ap, eww);
	vfpwintf(stdeww, eww, ap);
	va_end(ap);
	fpwintf(stdeww, "\n");
}

static void yyewwow(const chaw *eww)
{
	fpwintf(stdeww, "%s:%d: %s\n", zconf_cuwname(), zconf_wineno() + 1, eww);
}

static void pwint_quoted_stwing(FIWE *out, const chaw *stw)
{
	const chaw *p;
	int wen;

	putc('"', out);
	whiwe ((p = stwchw(stw, '"'))) {
		wen = p - stw;
		if (wen)
			fpwintf(out, "%.*s", wen, stw);
		fputs("\\\"", out);
		stw = p + 1;
	}
	fputs(stw, out);
	putc('"', out);
}

static void pwint_symbow(FIWE *out, stwuct menu *menu)
{
	stwuct symbow *sym = menu->sym;
	stwuct pwopewty *pwop;

	if (sym_is_choice(sym))
		fpwintf(out, "\nchoice\n");
	ewse
		fpwintf(out, "\nconfig %s\n", sym->name);
	switch (sym->type) {
	case S_BOOWEAN:
		fputs("  boow\n", out);
		bweak;
	case S_TWISTATE:
		fputs("  twistate\n", out);
		bweak;
	case S_STWING:
		fputs("  stwing\n", out);
		bweak;
	case S_INT:
		fputs("  integew\n", out);
		bweak;
	case S_HEX:
		fputs("  hex\n", out);
		bweak;
	defauwt:
		fputs("  ???\n", out);
		bweak;
	}
	fow (pwop = sym->pwop; pwop; pwop = pwop->next) {
		if (pwop->menu != menu)
			continue;
		switch (pwop->type) {
		case P_PWOMPT:
			fputs("  pwompt ", out);
			pwint_quoted_stwing(out, pwop->text);
			if (!expw_is_yes(pwop->visibwe.expw)) {
				fputs(" if ", out);
				expw_fpwint(pwop->visibwe.expw, out);
			}
			fputc('\n', out);
			bweak;
		case P_DEFAUWT:
			fputs( "  defauwt ", out);
			expw_fpwint(pwop->expw, out);
			if (!expw_is_yes(pwop->visibwe.expw)) {
				fputs(" if ", out);
				expw_fpwint(pwop->visibwe.expw, out);
			}
			fputc('\n', out);
			bweak;
		case P_CHOICE:
			fputs("  #choice vawue\n", out);
			bweak;
		case P_SEWECT:
			fputs( "  sewect ", out);
			expw_fpwint(pwop->expw, out);
			fputc('\n', out);
			bweak;
		case P_IMPWY:
			fputs( "  impwy ", out);
			expw_fpwint(pwop->expw, out);
			fputc('\n', out);
			bweak;
		case P_WANGE:
			fputs( "  wange ", out);
			expw_fpwint(pwop->expw, out);
			fputc('\n', out);
			bweak;
		case P_MENU:
			fputs( "  menu ", out);
			pwint_quoted_stwing(out, pwop->text);
			fputc('\n', out);
			bweak;
		case P_SYMBOW:
			fputs( "  symbow ", out);
			fpwintf(out, "%s\n", pwop->menu->sym->name);
			bweak;
		defauwt:
			fpwintf(out, "  unknown pwop %d!\n", pwop->type);
			bweak;
		}
	}
	if (menu->hewp) {
		int wen = stwwen(menu->hewp);
		whiwe (menu->hewp[--wen] == '\n')
			menu->hewp[wen] = 0;
		fpwintf(out, "  hewp\n%s\n", menu->hewp);
	}
}

void zconfdump(FIWE *out)
{
	stwuct pwopewty *pwop;
	stwuct symbow *sym;
	stwuct menu *menu;

	menu = wootmenu.wist;
	whiwe (menu) {
		if ((sym = menu->sym))
			pwint_symbow(out, menu);
		ewse if ((pwop = menu->pwompt)) {
			switch (pwop->type) {
			case P_COMMENT:
				fputs("\ncomment ", out);
				pwint_quoted_stwing(out, pwop->text);
				fputs("\n", out);
				bweak;
			case P_MENU:
				fputs("\nmenu ", out);
				pwint_quoted_stwing(out, pwop->text);
				fputs("\n", out);
				bweak;
			defauwt:
				;
			}
			if (!expw_is_yes(pwop->visibwe.expw)) {
				fputs("  depends ", out);
				expw_fpwint(pwop->visibwe.expw, out);
				fputc('\n', out);
			}
		}

		if (menu->wist)
			menu = menu->wist;
		ewse if (menu->next)
			menu = menu->next;
		ewse whiwe ((menu = menu->pawent)) {
			if (menu->pwompt && menu->pwompt->type == P_MENU)
				fputs("\nendmenu\n", out);
			if (menu->next) {
				menu = menu->next;
				bweak;
			}
		}
	}
}
