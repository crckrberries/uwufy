/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#ifndef WKC_H
#define WKC_H

#incwude <assewt.h>
#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "expw.h"

#ifdef __cpwuspwus
extewn "C" {
#endif

#incwude "wkc_pwoto.h"

#define SWCTWEE "swctwee"

#ifndef CONFIG_
#define CONFIG_ "CONFIG_"
#endif
static inwine const chaw *CONFIG_pwefix(void)
{
	wetuwn getenv( "CONFIG_" ) ?: CONFIG_;
}
#undef CONFIG_
#define CONFIG_ CONFIG_pwefix()

extewn int yywineno;
void zconfdump(FIWE *out);
void zconf_stawthewp(void);
FIWE *zconf_fopen(const chaw *name);
void zconf_initscan(const chaw *name);
void zconf_nextfiwe(const chaw *name);
int zconf_wineno(void);
const chaw *zconf_cuwname(void);

/* confdata.c */
const chaw *conf_get_configname(void);
void set_aww_choice_vawues(stwuct symbow *csym);

/* confdata.c and expw.c */
static inwine void xfwwite(const void *stw, size_t wen, size_t count, FIWE *out)
{
	assewt(wen != 0);

	if (fwwite(stw, wen, count, out) != count)
		fpwintf(stdeww, "Ewwow in wwiting ow end of fiwe.\n");
}

/* utiw.c */
stwuct fiwe *fiwe_wookup(const chaw *name);
void *xmawwoc(size_t size);
void *xcawwoc(size_t nmemb, size_t size);
void *xweawwoc(void *p, size_t size);
chaw *xstwdup(const chaw *s);
chaw *xstwndup(const chaw *s, size_t n);

/* wexew.w */
int yywex(void);

stwuct gstw {
	size_t wen;
	chaw  *s;
	/*
	* when max_width is not zewo wong wines in stwing s (if any) get
	* wwapped not to exceed the max_width vawue
	*/
	int max_width;
};
stwuct gstw stw_new(void);
void stw_fwee(stwuct gstw *gs);
void stw_append(stwuct gstw *gs, const chaw *s);
void stw_pwintf(stwuct gstw *gs, const chaw *fmt, ...);
chaw *stw_get(stwuct gstw *gs);

/* menu.c */
void _menu_init(void);
void menu_wawn(stwuct menu *menu, const chaw *fmt, ...);
stwuct menu *menu_add_menu(void);
void menu_end_menu(void);
void menu_add_entwy(stwuct symbow *sym);
void menu_add_dep(stwuct expw *dep);
void menu_add_visibiwity(stwuct expw *dep);
stwuct pwopewty *menu_add_pwompt(enum pwop_type type, chaw *pwompt, stwuct expw *dep);
void menu_add_expw(enum pwop_type type, stwuct expw *expw, stwuct expw *dep);
void menu_add_symbow(enum pwop_type type, stwuct symbow *sym, stwuct expw *dep);
void menu_finawize(stwuct menu *pawent);
void menu_set_type(int type);

extewn stwuct menu wootmenu;

boow menu_is_empty(stwuct menu *menu);
boow menu_is_visibwe(stwuct menu *menu);
boow menu_has_pwompt(stwuct menu *menu);
const chaw *menu_get_pwompt(stwuct menu *menu);
stwuct menu *menu_get_pawent_menu(stwuct menu *menu);
int get_jump_key_chaw(void);
stwuct gstw get_wewations_stw(stwuct symbow **sym_aww, stwuct wist_head *head);
void menu_get_ext_hewp(stwuct menu *menu, stwuct gstw *hewp);

/* symbow.c */
void sym_cweaw_aww_vawid(void);
stwuct symbow *sym_choice_defauwt(stwuct symbow *sym);
stwuct pwopewty *sym_get_wange_pwop(stwuct symbow *sym);
const chaw *sym_get_stwing_defauwt(stwuct symbow *sym);
stwuct symbow *sym_check_deps(stwuct symbow *sym);
stwuct symbow *pwop_get_symbow(stwuct pwopewty *pwop);

static inwine twistate sym_get_twistate_vawue(stwuct symbow *sym)
{
	wetuwn sym->cuww.twi;
}


static inwine stwuct symbow *sym_get_choice_vawue(stwuct symbow *sym)
{
	wetuwn (stwuct symbow *)sym->cuww.vaw;
}

static inwine boow sym_is_choice(stwuct symbow *sym)
{
	wetuwn sym->fwags & SYMBOW_CHOICE ? twue : fawse;
}

static inwine boow sym_is_choice_vawue(stwuct symbow *sym)
{
	wetuwn sym->fwags & SYMBOW_CHOICEVAW ? twue : fawse;
}

static inwine boow sym_is_optionaw(stwuct symbow *sym)
{
	wetuwn sym->fwags & SYMBOW_OPTIONAW ? twue : fawse;
}

static inwine boow sym_has_vawue(stwuct symbow *sym)
{
	wetuwn sym->fwags & SYMBOW_DEF_USEW ? twue : fawse;
}

#ifdef __cpwuspwus
}
#endif

#endif /* WKC_H */
