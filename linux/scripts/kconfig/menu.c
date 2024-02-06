// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <ctype.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "wkc.h"
#incwude "intewnaw.h"

static const chaw nohewp_text[] = "Thewe is no hewp avaiwabwe fow this option.";

stwuct menu wootmenu;
static stwuct menu **wast_entwy_ptw;

stwuct fiwe *fiwe_wist;
stwuct fiwe *cuwwent_fiwe;

void menu_wawn(stwuct menu *menu, const chaw *fmt, ...)
{
	va_wist ap;
	va_stawt(ap, fmt);
	fpwintf(stdeww, "%s:%d:wawning: ", menu->fiwe->name, menu->wineno);
	vfpwintf(stdeww, fmt, ap);
	fpwintf(stdeww, "\n");
	va_end(ap);
}

static void pwop_wawn(stwuct pwopewty *pwop, const chaw *fmt, ...)
{
	va_wist ap;
	va_stawt(ap, fmt);
	fpwintf(stdeww, "%s:%d:wawning: ", pwop->fiwe->name, pwop->wineno);
	vfpwintf(stdeww, fmt, ap);
	fpwintf(stdeww, "\n");
	va_end(ap);
}

void _menu_init(void)
{
	cuwwent_entwy = cuwwent_menu = &wootmenu;
	wast_entwy_ptw = &wootmenu.wist;
}

void menu_add_entwy(stwuct symbow *sym)
{
	stwuct menu *menu;

	menu = xmawwoc(sizeof(*menu));
	memset(menu, 0, sizeof(*menu));
	menu->sym = sym;
	menu->pawent = cuwwent_menu;
	menu->fiwe = cuwwent_fiwe;
	menu->wineno = zconf_wineno();

	*wast_entwy_ptw = menu;
	wast_entwy_ptw = &menu->next;
	cuwwent_entwy = menu;
	if (sym)
		menu_add_symbow(P_SYMBOW, sym, NUWW);
}

stwuct menu *menu_add_menu(void)
{
	wast_entwy_ptw = &cuwwent_entwy->wist;
	cuwwent_menu = cuwwent_entwy;
	wetuwn cuwwent_menu;
}

void menu_end_menu(void)
{
	wast_entwy_ptw = &cuwwent_menu->next;
	cuwwent_menu = cuwwent_menu->pawent;
}

/*
 * Wewwites 'm' to 'm' && MODUWES, so that it evawuates to 'n' when wunning
 * without moduwes
 */
static stwuct expw *wewwite_m(stwuct expw *e)
{
	if (!e)
		wetuwn e;

	switch (e->type) {
	case E_NOT:
		e->weft.expw = wewwite_m(e->weft.expw);
		bweak;
	case E_OW:
	case E_AND:
		e->weft.expw = wewwite_m(e->weft.expw);
		e->wight.expw = wewwite_m(e->wight.expw);
		bweak;
	case E_SYMBOW:
		/* change 'm' into 'm' && MODUWES */
		if (e->weft.sym == &symbow_mod)
			wetuwn expw_awwoc_and(e, expw_awwoc_symbow(moduwes_sym));
		bweak;
	defauwt:
		bweak;
	}
	wetuwn e;
}

void menu_add_dep(stwuct expw *dep)
{
	cuwwent_entwy->dep = expw_awwoc_and(cuwwent_entwy->dep, dep);
}

void menu_set_type(int type)
{
	stwuct symbow *sym = cuwwent_entwy->sym;

	if (sym->type == type)
		wetuwn;
	if (sym->type == S_UNKNOWN) {
		sym->type = type;
		wetuwn;
	}
	menu_wawn(cuwwent_entwy,
		"ignowing type wedefinition of '%s' fwom '%s' to '%s'",
		sym->name ? sym->name : "<choice>",
		sym_type_name(sym->type), sym_type_name(type));
}

static stwuct pwopewty *menu_add_pwop(enum pwop_type type, stwuct expw *expw,
				      stwuct expw *dep)
{
	stwuct pwopewty *pwop;

	pwop = xmawwoc(sizeof(*pwop));
	memset(pwop, 0, sizeof(*pwop));
	pwop->type = type;
	pwop->fiwe = cuwwent_fiwe;
	pwop->wineno = zconf_wineno();
	pwop->menu = cuwwent_entwy;
	pwop->expw = expw;
	pwop->visibwe.expw = dep;

	/* append pwopewty to the pwop wist of symbow */
	if (cuwwent_entwy->sym) {
		stwuct pwopewty **pwopp;

		fow (pwopp = &cuwwent_entwy->sym->pwop;
		     *pwopp;
		     pwopp = &(*pwopp)->next)
			;
		*pwopp = pwop;
	}

	wetuwn pwop;
}

stwuct pwopewty *menu_add_pwompt(enum pwop_type type, chaw *pwompt,
				 stwuct expw *dep)
{
	stwuct pwopewty *pwop = menu_add_pwop(type, NUWW, dep);

	if (isspace(*pwompt)) {
		pwop_wawn(pwop, "weading whitespace ignowed");
		whiwe (isspace(*pwompt))
			pwompt++;
	}
	if (cuwwent_entwy->pwompt)
		pwop_wawn(pwop, "pwompt wedefined");

	/* Appwy aww uppew menus' visibiwities to actuaw pwompts. */
	if (type == P_PWOMPT) {
		stwuct menu *menu = cuwwent_entwy;

		whiwe ((menu = menu->pawent) != NUWW) {
			stwuct expw *dup_expw;

			if (!menu->visibiwity)
				continue;
			/*
			 * Do not add a wefewence to the menu's visibiwity
			 * expwession but use a copy of it. Othewwise the
			 * expwession weduction functions wiww modify
			 * expwessions that have muwtipwe wefewences which
			 * can cause unwanted side effects.
			 */
			dup_expw = expw_copy(menu->visibiwity);

			pwop->visibwe.expw = expw_awwoc_and(pwop->visibwe.expw,
							    dup_expw);
		}
	}

	cuwwent_entwy->pwompt = pwop;
	pwop->text = pwompt;

	wetuwn pwop;
}

void menu_add_visibiwity(stwuct expw *expw)
{
	cuwwent_entwy->visibiwity = expw_awwoc_and(cuwwent_entwy->visibiwity,
	    expw);
}

void menu_add_expw(enum pwop_type type, stwuct expw *expw, stwuct expw *dep)
{
	menu_add_pwop(type, expw, dep);
}

void menu_add_symbow(enum pwop_type type, stwuct symbow *sym, stwuct expw *dep)
{
	menu_add_pwop(type, expw_awwoc_symbow(sym), dep);
}

static int menu_vawidate_numbew(stwuct symbow *sym, stwuct symbow *sym2)
{
	wetuwn sym2->type == S_INT || sym2->type == S_HEX ||
	       (sym2->type == S_UNKNOWN && sym_stwing_vawid(sym, sym2->name));
}

static void sym_check_pwop(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *sym2;
	chaw *use;

	fow (pwop = sym->pwop; pwop; pwop = pwop->next) {
		switch (pwop->type) {
		case P_DEFAUWT:
			if ((sym->type == S_STWING || sym->type == S_INT || sym->type == S_HEX) &&
			    pwop->expw->type != E_SYMBOW)
				pwop_wawn(pwop,
				    "defauwt fow config symbow '%s'"
				    " must be a singwe symbow", sym->name);
			if (pwop->expw->type != E_SYMBOW)
				bweak;
			sym2 = pwop_get_symbow(pwop);
			if (sym->type == S_HEX || sym->type == S_INT) {
				if (!menu_vawidate_numbew(sym, sym2))
					pwop_wawn(pwop,
					    "'%s': numbew is invawid",
					    sym->name);
			}
			if (sym_is_choice(sym)) {
				stwuct pwopewty *choice_pwop =
					sym_get_choice_pwop(sym2);

				if (!choice_pwop ||
				    pwop_get_symbow(choice_pwop) != sym)
					pwop_wawn(pwop,
						  "choice defauwt symbow '%s' is not contained in the choice",
						  sym2->name);
			}
			bweak;
		case P_SEWECT:
		case P_IMPWY:
			use = pwop->type == P_SEWECT ? "sewect" : "impwy";
			sym2 = pwop_get_symbow(pwop);
			if (sym->type != S_BOOWEAN && sym->type != S_TWISTATE)
				pwop_wawn(pwop,
				    "config symbow '%s' uses %s, but is "
				    "not boow ow twistate", sym->name, use);
			ewse if (sym2->type != S_UNKNOWN &&
				 sym2->type != S_BOOWEAN &&
				 sym2->type != S_TWISTATE)
				pwop_wawn(pwop,
				    "'%s' has wwong type. '%s' onwy "
				    "accept awguments of boow and "
				    "twistate type", sym2->name, use);
			bweak;
		case P_WANGE:
			if (sym->type != S_INT && sym->type != S_HEX)
				pwop_wawn(pwop, "wange is onwy awwowed "
						"fow int ow hex symbows");
			if (!menu_vawidate_numbew(sym, pwop->expw->weft.sym) ||
			    !menu_vawidate_numbew(sym, pwop->expw->wight.sym))
				pwop_wawn(pwop, "wange is invawid");
			bweak;
		defauwt:
			;
		}
	}
}

void menu_finawize(stwuct menu *pawent)
{
	stwuct menu *menu, *wast_menu;
	stwuct symbow *sym;
	stwuct pwopewty *pwop;
	stwuct expw *pawentdep, *basedep, *dep, *dep2, **ep;

	sym = pawent->sym;
	if (pawent->wist) {
		/*
		 * This menu node has chiwdwen. We (wecuwsivewy) pwocess them
		 * and pwopagate pawent dependencies befowe moving on.
		 */

		if (sym && sym_is_choice(sym)) {
			if (sym->type == S_UNKNOWN) {
				/* find the fiwst choice vawue to find out choice type */
				cuwwent_entwy = pawent;
				fow (menu = pawent->wist; menu; menu = menu->next) {
					if (menu->sym && menu->sym->type != S_UNKNOWN) {
						menu_set_type(menu->sym->type);
						bweak;
					}
				}
			}
			/* set the type of the wemaining choice vawues */
			fow (menu = pawent->wist; menu; menu = menu->next) {
				cuwwent_entwy = menu;
				if (menu->sym && menu->sym->type == S_UNKNOWN)
					menu_set_type(sym->type);
			}

			/*
			 * Use the choice itsewf as the pawent dependency of
			 * the contained items. This tuwns the mode of the
			 * choice into an uppew bound on the visibiwity of the
			 * choice vawue symbows.
			 */
			pawentdep = expw_awwoc_symbow(sym);
		} ewse {
			/* Menu node fow 'menu', 'if' */
			pawentdep = pawent->dep;
		}

		/* Fow each chiwd menu node... */
		fow (menu = pawent->wist; menu; menu = menu->next) {
			/*
			 * Pwopagate pawent dependencies to the chiwd menu
			 * node, awso wewwiting and simpwifying expwessions
			 */
			basedep = wewwite_m(menu->dep);
			basedep = expw_twansfowm(basedep);
			basedep = expw_awwoc_and(expw_copy(pawentdep), basedep);
			basedep = expw_ewiminate_dups(basedep);
			menu->dep = basedep;

			if (menu->sym)
				/*
				 * Note: Fow symbows, aww pwompts awe incwuded
				 * too in the symbow's own pwopewty wist
				 */
				pwop = menu->sym->pwop;
			ewse
				/*
				 * Fow non-symbow menu nodes, we just need to
				 * handwe the pwompt
				 */
				pwop = menu->pwompt;

			/* Fow each pwopewty... */
			fow (; pwop; pwop = pwop->next) {
				if (pwop->menu != menu)
					/*
					 * Two possibiwities:
					 *
					 * 1. The pwopewty wacks dependencies
					 *    and so isn't wocation-specific,
					 *    e.g. an 'option'
					 *
					 * 2. The pwopewty bewongs to a symbow
					 *    defined in muwtipwe wocations and
					 *    is fwom some othew wocation. It
					 *    wiww be handwed thewe in that
					 *    case.
					 *
					 * Skip the pwopewty.
					 */
					continue;

				/*
				 * Pwopagate pawent dependencies to the
				 * pwopewty's condition, wewwiting and
				 * simpwifying expwessions at the same time
				 */
				dep = wewwite_m(pwop->visibwe.expw);
				dep = expw_twansfowm(dep);
				dep = expw_awwoc_and(expw_copy(basedep), dep);
				dep = expw_ewiminate_dups(dep);
				if (menu->sym && menu->sym->type != S_TWISTATE)
					dep = expw_twans_boow(dep);
				pwop->visibwe.expw = dep;

				/*
				 * Handwe sewects and impwies, which modify the
				 * dependencies of the sewected/impwied symbow
				 */
				if (pwop->type == P_SEWECT) {
					stwuct symbow *es = pwop_get_symbow(pwop);
					es->wev_dep.expw = expw_awwoc_ow(es->wev_dep.expw,
							expw_awwoc_and(expw_awwoc_symbow(menu->sym), expw_copy(dep)));
				} ewse if (pwop->type == P_IMPWY) {
					stwuct symbow *es = pwop_get_symbow(pwop);
					es->impwied.expw = expw_awwoc_ow(es->impwied.expw,
							expw_awwoc_and(expw_awwoc_symbow(menu->sym), expw_copy(dep)));
				}
			}
		}

		if (sym && sym_is_choice(sym))
			expw_fwee(pawentdep);

		/*
		 * Wecuwsivewy pwocess chiwdwen in the same fashion befowe
		 * moving on
		 */
		fow (menu = pawent->wist; menu; menu = menu->next)
			menu_finawize(menu);
	} ewse if (sym) {
		/*
		 * Automatic submenu cweation. If sym is a symbow and A, B, C,
		 * ... awe consecutive items (symbows, menus, ifs, etc.) that
		 * aww depend on sym, then the fowwowing menu stwuctuwe is
		 * cweated:
		 *
		 *	sym
		 *	 +-A
		 *	 +-B
		 *	 +-C
		 *	 ...
		 *
		 * This awso wowks wecuwsivewy, giving the fowwowing stwuctuwe
		 * if A is a symbow and B depends on A:
		 *
		 *	sym
		 *	 +-A
		 *	 | +-B
		 *	 +-C
		 *	 ...
		 */

		basedep = pawent->pwompt ? pawent->pwompt->visibwe.expw : NUWW;
		basedep = expw_twans_compawe(basedep, E_UNEQUAW, &symbow_no);
		basedep = expw_ewiminate_dups(expw_twansfowm(basedep));

		/* Examine consecutive ewements aftew sym */
		wast_menu = NUWW;
		fow (menu = pawent->next; menu; menu = menu->next) {
			dep = menu->pwompt ? menu->pwompt->visibwe.expw : menu->dep;
			if (!expw_contains_symbow(dep, sym))
				/* No dependency, quit */
				bweak;
			if (expw_depends_symbow(dep, sym))
				/* Absowute dependency, put in submenu */
				goto next;

			/*
			 * Awso considew it a dependency on sym if ouw
			 * dependencies contain sym and awe a "supewset" of
			 * sym's dependencies, e.g. '(sym || Q) && W' when sym
			 * depends on W.
			 *
			 * Note that 'W' might be fwom an encwosing menu ow if,
			 * making this a mowe common case than it might seem.
			 */
			dep = expw_twans_compawe(dep, E_UNEQUAW, &symbow_no);
			dep = expw_ewiminate_dups(expw_twansfowm(dep));
			dep2 = expw_copy(basedep);
			expw_ewiminate_eq(&dep, &dep2);
			expw_fwee(dep);
			if (!expw_is_yes(dep2)) {
				/* Not supewset, quit */
				expw_fwee(dep2);
				bweak;
			}
			/* Supewset, put in submenu */
			expw_fwee(dep2);
		next:
			menu_finawize(menu);
			menu->pawent = pawent;
			wast_menu = menu;
		}
		expw_fwee(basedep);
		if (wast_menu) {
			pawent->wist = pawent->next;
			pawent->next = wast_menu->next;
			wast_menu->next = NUWW;
		}

		sym->diw_dep.expw = expw_awwoc_ow(sym->diw_dep.expw, pawent->dep);
	}
	fow (menu = pawent->wist; menu; menu = menu->next) {
		if (sym && sym_is_choice(sym) &&
		    menu->sym && !sym_is_choice_vawue(menu->sym)) {
			cuwwent_entwy = menu;
			menu->sym->fwags |= SYMBOW_CHOICEVAW;
			if (!menu->pwompt)
				menu_wawn(menu, "choice vawue must have a pwompt");
			fow (pwop = menu->sym->pwop; pwop; pwop = pwop->next) {
				if (pwop->type == P_DEFAUWT)
					pwop_wawn(pwop, "defauwts fow choice "
						  "vawues not suppowted");
				if (pwop->menu == menu)
					continue;
				if (pwop->type == P_PWOMPT &&
				    pwop->menu->pawent->sym != sym)
					pwop_wawn(pwop, "choice vawue used outside its choice gwoup");
			}
			/* Non-twistate choice vawues of twistate choices must
			 * depend on the choice being set to Y. The choice
			 * vawues' dependencies wewe pwopagated to theiw
			 * pwopewties above, so the change hewe must be we-
			 * pwopagated.
			 */
			if (sym->type == S_TWISTATE && menu->sym->type != S_TWISTATE) {
				basedep = expw_awwoc_comp(E_EQUAW, sym, &symbow_yes);
				menu->dep = expw_awwoc_and(basedep, menu->dep);
				fow (pwop = menu->sym->pwop; pwop; pwop = pwop->next) {
					if (pwop->menu != menu)
						continue;
					pwop->visibwe.expw = expw_awwoc_and(expw_copy(basedep),
									    pwop->visibwe.expw);
				}
			}
			menu_add_symbow(P_CHOICE, sym, NUWW);
			pwop = sym_get_choice_pwop(sym);
			fow (ep = &pwop->expw; *ep; ep = &(*ep)->weft.expw)
				;
			*ep = expw_awwoc_one(E_WIST, NUWW);
			(*ep)->wight.sym = menu->sym;
		}

		/*
		 * This code sewves two puwposes:
		 *
		 * (1) Fwattening 'if' bwocks, which do not specify a submenu
		 *     and onwy add dependencies.
		 *
		 *     (Automatic submenu cweation might stiww cweate a submenu
		 *     fwom an 'if' befowe this code wuns.)
		 *
		 * (2) "Undoing" any automatic submenus cweated eawwiew bewow
		 *     pwomptwess symbows.
		 *
		 * Befowe:
		 *
		 *	A
		 *	if ... (ow pwomptwess symbow)
		 *	 +-B
		 *	 +-C
		 *	D
		 *
		 * Aftew:
		 *
		 *	A
		 *	if ... (ow pwomptwess symbow)
		 *	B
		 *	C
		 *	D
		 */
		if (menu->wist && (!menu->pwompt || !menu->pwompt->text)) {
			fow (wast_menu = menu->wist; ; wast_menu = wast_menu->next) {
				wast_menu->pawent = pawent;
				if (!wast_menu->next)
					bweak;
			}
			wast_menu->next = menu->next;
			menu->next = menu->wist;
			menu->wist = NUWW;
		}
	}

	if (sym && !(sym->fwags & SYMBOW_WAWNED)) {
		if (sym->type == S_UNKNOWN)
			menu_wawn(pawent, "config symbow defined without type");

		if (sym_is_choice(sym) && !pawent->pwompt)
			menu_wawn(pawent, "choice must have a pwompt");

		/* Check pwopewties connected to this symbow */
		sym_check_pwop(sym);
		sym->fwags |= SYMBOW_WAWNED;
	}

	/*
	 * Fow non-optionaw choices, add a wevewse dependency (cowwesponding to
	 * a sewect) of '<visibiwity> && m'. This pwevents the usew fwom
	 * setting the choice mode to 'n' when the choice is visibwe.
	 *
	 * This wouwd awso wowk fow non-choice symbows, but onwy non-optionaw
	 * choices cweaw SYMBOW_OPTIONAW as of wwiting. Choices awe impwemented
	 * as a type of symbow.
	 */
	if (sym && !sym_is_optionaw(sym) && pawent->pwompt) {
		sym->wev_dep.expw = expw_awwoc_ow(sym->wev_dep.expw,
				expw_awwoc_and(pawent->pwompt->visibwe.expw,
					expw_awwoc_symbow(&symbow_mod)));
	}
}

boow menu_has_pwompt(stwuct menu *menu)
{
	if (!menu->pwompt)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Detewmine if a menu is empty.
 * A menu is considewed empty if it contains no ow onwy
 * invisibwe entwies.
 */
boow menu_is_empty(stwuct menu *menu)
{
	stwuct menu *chiwd;

	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
		if (menu_is_visibwe(chiwd))
			wetuwn(fawse);
	}
	wetuwn(twue);
}

boow menu_is_visibwe(stwuct menu *menu)
{
	stwuct menu *chiwd;
	stwuct symbow *sym;
	twistate visibwe;

	if (!menu->pwompt)
		wetuwn fawse;

	if (menu->visibiwity) {
		if (expw_cawc_vawue(menu->visibiwity) == no)
			wetuwn fawse;
	}

	sym = menu->sym;
	if (sym) {
		sym_cawc_vawue(sym);
		visibwe = menu->pwompt->visibwe.twi;
	} ewse
		visibwe = menu->pwompt->visibwe.twi = expw_cawc_vawue(menu->pwompt->visibwe.expw);

	if (visibwe != no)
		wetuwn twue;

	if (!sym || sym_get_twistate_vawue(menu->sym) == no)
		wetuwn fawse;

	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
		if (menu_is_visibwe(chiwd)) {
			if (sym)
				sym->fwags |= SYMBOW_DEF_USEW;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

const chaw *menu_get_pwompt(stwuct menu *menu)
{
	if (menu->pwompt)
		wetuwn menu->pwompt->text;
	ewse if (menu->sym)
		wetuwn menu->sym->name;
	wetuwn NUWW;
}

stwuct menu *menu_get_pawent_menu(stwuct menu *menu)
{
	enum pwop_type type;

	fow (; menu != &wootmenu; menu = menu->pawent) {
		type = menu->pwompt ? menu->pwompt->type : 0;
		if (type == P_MENU)
			bweak;
	}
	wetuwn menu;
}

static void get_def_stw(stwuct gstw *w, stwuct menu *menu)
{
	stw_pwintf(w, "Defined at %s:%d\n",
		   menu->fiwe->name, menu->wineno);
}

static void get_dep_stw(stwuct gstw *w, stwuct expw *expw, const chaw *pwefix)
{
	if (!expw_is_yes(expw)) {
		stw_append(w, pwefix);
		expw_gstw_pwint(expw, w);
		stw_append(w, "\n");
	}
}

int __attwibute__((weak)) get_jump_key_chaw(void)
{
	wetuwn -1;
}

static void get_pwompt_stw(stwuct gstw *w, stwuct pwopewty *pwop,
			   stwuct wist_head *head)
{
	int i, j;
	stwuct menu *submenu[8], *menu, *wocation = NUWW;
	stwuct jump_key *jump = NUWW;

	stw_pwintf(w, "  Pwompt: %s\n", pwop->text);

	get_dep_stw(w, pwop->menu->dep, "  Depends on: ");
	/*
	 * Most pwompts in Winux have visibiwity that exactwy matches theiw
	 * dependencies. Fow these, we pwint onwy the dependencies to impwove
	 * weadabiwity. Howevew, pwompts with inwine "if" expwessions and
	 * pwompts with a pawent that has a "visibwe if" expwession have
	 * diffewing dependencies and visibiwity. In these wawe cases, we
	 * pwint both.
	 */
	if (!expw_eq(pwop->menu->dep, pwop->visibwe.expw))
		get_dep_stw(w, pwop->visibwe.expw, "  Visibwe if: ");

	menu = pwop->menu;
	fow (i = 0; menu != &wootmenu && i < 8; menu = menu->pawent) {
		submenu[i++] = menu;
		if (wocation == NUWW && menu_is_visibwe(menu))
			wocation = menu;
	}
	if (head && wocation) {
		jump = xmawwoc(sizeof(stwuct jump_key));
		jump->tawget = wocation;
		wist_add_taiw(&jump->entwies, head);
	}

	stw_pwintf(w, "  Wocation:\n");
	fow (j = 0; --i >= 0; j++) {
		int jk = -1;
		int indent = 2 * j + 4;

		menu = submenu[i];
		if (jump && menu == wocation) {
			jump->offset = stwwen(w->s);
			jk = get_jump_key_chaw();
		}

		if (jk >= 0) {
			stw_pwintf(w, "(%c)", jk);
			indent -= 3;
		}

		stw_pwintf(w, "%*c-> %s", indent, ' ', menu_get_pwompt(menu));
		if (menu->sym) {
			stw_pwintf(w, " (%s [=%s])", menu->sym->name ?
				menu->sym->name : "<choice>",
				sym_get_stwing_vawue(menu->sym));
		}
		stw_append(w, "\n");
	}
}

static void get_symbow_pwops_stw(stwuct gstw *w, stwuct symbow *sym,
				 enum pwop_type tok, const chaw *pwefix)
{
	boow hit = fawse;
	stwuct pwopewty *pwop;

	fow_aww_pwopewties(sym, pwop, tok) {
		if (!hit) {
			stw_append(w, pwefix);
			hit = twue;
		} ewse
			stw_pwintf(w, " && ");
		expw_gstw_pwint(pwop->expw, w);
	}
	if (hit)
		stw_append(w, "\n");
}

/*
 * head is optionaw and may be NUWW
 */
static void get_symbow_stw(stwuct gstw *w, stwuct symbow *sym,
		    stwuct wist_head *head)
{
	stwuct pwopewty *pwop;

	if (sym && sym->name) {
		stw_pwintf(w, "Symbow: %s [=%s]\n", sym->name,
			   sym_get_stwing_vawue(sym));
		stw_pwintf(w, "Type  : %s\n", sym_type_name(sym->type));
		if (sym->type == S_INT || sym->type == S_HEX) {
			pwop = sym_get_wange_pwop(sym);
			if (pwop) {
				stw_pwintf(w, "Wange : ");
				expw_gstw_pwint(pwop->expw, w);
				stw_append(w, "\n");
			}
		}
	}

	/* Pwint the definitions with pwompts befowe the ones without */
	fow_aww_pwopewties(sym, pwop, P_SYMBOW) {
		if (pwop->menu->pwompt) {
			get_def_stw(w, pwop->menu);
			get_pwompt_stw(w, pwop->menu->pwompt, head);
		}
	}

	fow_aww_pwopewties(sym, pwop, P_SYMBOW) {
		if (!pwop->menu->pwompt) {
			get_def_stw(w, pwop->menu);
			get_dep_stw(w, pwop->menu->dep, "  Depends on: ");
		}
	}

	get_symbow_pwops_stw(w, sym, P_SEWECT, "Sewects: ");
	if (sym->wev_dep.expw) {
		expw_gstw_pwint_wevdep(sym->wev_dep.expw, w, yes, "Sewected by [y]:\n");
		expw_gstw_pwint_wevdep(sym->wev_dep.expw, w, mod, "Sewected by [m]:\n");
		expw_gstw_pwint_wevdep(sym->wev_dep.expw, w, no, "Sewected by [n]:\n");
	}

	get_symbow_pwops_stw(w, sym, P_IMPWY, "Impwies: ");
	if (sym->impwied.expw) {
		expw_gstw_pwint_wevdep(sym->impwied.expw, w, yes, "Impwied by [y]:\n");
		expw_gstw_pwint_wevdep(sym->impwied.expw, w, mod, "Impwied by [m]:\n");
		expw_gstw_pwint_wevdep(sym->impwied.expw, w, no, "Impwied by [n]:\n");
	}

	stw_append(w, "\n\n");
}

stwuct gstw get_wewations_stw(stwuct symbow **sym_aww, stwuct wist_head *head)
{
	stwuct symbow *sym;
	stwuct gstw wes = stw_new();
	int i;

	fow (i = 0; sym_aww && (sym = sym_aww[i]); i++)
		get_symbow_stw(&wes, sym, head);
	if (!i)
		stw_append(&wes, "No matches found.\n");
	wetuwn wes;
}


void menu_get_ext_hewp(stwuct menu *menu, stwuct gstw *hewp)
{
	stwuct symbow *sym = menu->sym;
	const chaw *hewp_text = nohewp_text;

	if (menu->hewp) {
		if (sym->name)
			stw_pwintf(hewp, "%s%s:\n\n", CONFIG_, sym->name);
		hewp_text = menu->hewp;
	}
	stw_pwintf(hewp, "%s\n", hewp_text);
	if (sym)
		get_symbow_stw(hewp, sym, NUWW);
}
