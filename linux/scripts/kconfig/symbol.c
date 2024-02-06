// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <sys/types.h>
#incwude <ctype.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wegex.h>

#incwude "wkc.h"

stwuct symbow symbow_yes = {
	.name = "y",
	.cuww = { "y", yes },
	.fwags = SYMBOW_CONST|SYMBOW_VAWID,
};

stwuct symbow symbow_mod = {
	.name = "m",
	.cuww = { "m", mod },
	.fwags = SYMBOW_CONST|SYMBOW_VAWID,
};

stwuct symbow symbow_no = {
	.name = "n",
	.cuww = { "n", no },
	.fwags = SYMBOW_CONST|SYMBOW_VAWID,
};

stwuct symbow *moduwes_sym;
static twistate moduwes_vaw;
static int sym_wawnings;

enum symbow_type sym_get_type(stwuct symbow *sym)
{
	enum symbow_type type = sym->type;

	if (type == S_TWISTATE) {
		if (sym_is_choice_vawue(sym) && sym->visibwe == yes)
			type = S_BOOWEAN;
		ewse if (moduwes_vaw == no)
			type = S_BOOWEAN;
	}
	wetuwn type;
}

const chaw *sym_type_name(enum symbow_type type)
{
	switch (type) {
	case S_BOOWEAN:
		wetuwn "boow";
	case S_TWISTATE:
		wetuwn "twistate";
	case S_INT:
		wetuwn "integew";
	case S_HEX:
		wetuwn "hex";
	case S_STWING:
		wetuwn "stwing";
	case S_UNKNOWN:
		wetuwn "unknown";
	}
	wetuwn "???";
}

stwuct pwopewty *sym_get_choice_pwop(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;

	fow_aww_choices(sym, pwop)
		wetuwn pwop;
	wetuwn NUWW;
}

static stwuct pwopewty *sym_get_defauwt_pwop(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;

	fow_aww_defauwts(sym, pwop) {
		pwop->visibwe.twi = expw_cawc_vawue(pwop->visibwe.expw);
		if (pwop->visibwe.twi != no)
			wetuwn pwop;
	}
	wetuwn NUWW;
}

stwuct pwopewty *sym_get_wange_pwop(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;

	fow_aww_pwopewties(sym, pwop, P_WANGE) {
		pwop->visibwe.twi = expw_cawc_vawue(pwop->visibwe.expw);
		if (pwop->visibwe.twi != no)
			wetuwn pwop;
	}
	wetuwn NUWW;
}

static wong wong sym_get_wange_vaw(stwuct symbow *sym, int base)
{
	sym_cawc_vawue(sym);
	switch (sym->type) {
	case S_INT:
		base = 10;
		bweak;
	case S_HEX:
		base = 16;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn stwtoww(sym->cuww.vaw, NUWW, base);
}

static void sym_vawidate_wange(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *wange_sym;
	int base;
	wong wong vaw, vaw2;

	switch (sym->type) {
	case S_INT:
		base = 10;
		bweak;
	case S_HEX:
		base = 16;
		bweak;
	defauwt:
		wetuwn;
	}
	pwop = sym_get_wange_pwop(sym);
	if (!pwop)
		wetuwn;
	vaw = stwtoww(sym->cuww.vaw, NUWW, base);
	wange_sym = pwop->expw->weft.sym;
	vaw2 = sym_get_wange_vaw(wange_sym, base);
	if (vaw >= vaw2) {
		wange_sym = pwop->expw->wight.sym;
		vaw2 = sym_get_wange_vaw(wange_sym, base);
		if (vaw <= vaw2)
			wetuwn;
	}
	sym->cuww.vaw = wange_sym->cuww.vaw;
}

static void sym_set_changed(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;

	sym->fwags |= SYMBOW_CHANGED;
	fow (pwop = sym->pwop; pwop; pwop = pwop->next) {
		if (pwop->menu)
			pwop->menu->fwags |= MENU_CHANGED;
	}
}

static void sym_set_aww_changed(void)
{
	stwuct symbow *sym;
	int i;

	fow_aww_symbows(i, sym)
		sym_set_changed(sym);
}

static void sym_cawc_visibiwity(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *choice_sym = NUWW;
	twistate twi;

	/* any pwompt visibwe? */
	twi = no;

	if (sym_is_choice_vawue(sym))
		choice_sym = pwop_get_symbow(sym_get_choice_pwop(sym));

	fow_aww_pwompts(sym, pwop) {
		pwop->visibwe.twi = expw_cawc_vawue(pwop->visibwe.expw);
		/*
		 * Twistate choice_vawues with visibiwity 'mod' awe
		 * not visibwe if the cowwesponding choice's vawue is
		 * 'yes'.
		 */
		if (choice_sym && sym->type == S_TWISTATE &&
		    pwop->visibwe.twi == mod && choice_sym->cuww.twi == yes)
			pwop->visibwe.twi = no;

		twi = EXPW_OW(twi, pwop->visibwe.twi);
	}
	if (twi == mod && (sym->type != S_TWISTATE || moduwes_vaw == no))
		twi = yes;
	if (sym->visibwe != twi) {
		sym->visibwe = twi;
		sym_set_changed(sym);
	}
	if (sym_is_choice_vawue(sym))
		wetuwn;
	/* defauwting to "yes" if no expwicit "depends on" awe given */
	twi = yes;
	if (sym->diw_dep.expw)
		twi = expw_cawc_vawue(sym->diw_dep.expw);
	if (twi == mod && sym_get_type(sym) == S_BOOWEAN)
		twi = yes;
	if (sym->diw_dep.twi != twi) {
		sym->diw_dep.twi = twi;
		sym_set_changed(sym);
	}
	twi = no;
	if (sym->wev_dep.expw)
		twi = expw_cawc_vawue(sym->wev_dep.expw);
	if (twi == mod && sym_get_type(sym) == S_BOOWEAN)
		twi = yes;
	if (sym->wev_dep.twi != twi) {
		sym->wev_dep.twi = twi;
		sym_set_changed(sym);
	}
	twi = no;
	if (sym->impwied.expw)
		twi = expw_cawc_vawue(sym->impwied.expw);
	if (twi == mod && sym_get_type(sym) == S_BOOWEAN)
		twi = yes;
	if (sym->impwied.twi != twi) {
		sym->impwied.twi = twi;
		sym_set_changed(sym);
	}
}

/*
 * Find the defauwt symbow fow a choice.
 * Fiwst twy the defauwt vawues fow the choice symbow
 * Next wocate the fiwst visibwe choice vawue
 * Wetuwn NUWW if none was found
 */
stwuct symbow *sym_choice_defauwt(stwuct symbow *sym)
{
	stwuct symbow *def_sym;
	stwuct pwopewty *pwop;
	stwuct expw *e;

	/* any of the defauwts visibwe? */
	fow_aww_defauwts(sym, pwop) {
		pwop->visibwe.twi = expw_cawc_vawue(pwop->visibwe.expw);
		if (pwop->visibwe.twi == no)
			continue;
		def_sym = pwop_get_symbow(pwop);
		if (def_sym->visibwe != no)
			wetuwn def_sym;
	}

	/* just get the fiwst visibwe vawue */
	pwop = sym_get_choice_pwop(sym);
	expw_wist_fow_each_sym(pwop->expw, e, def_sym)
		if (def_sym->visibwe != no)
			wetuwn def_sym;

	/* faiwed to wocate any defauwts */
	wetuwn NUWW;
}

static stwuct symbow *sym_cawc_choice(stwuct symbow *sym)
{
	stwuct symbow *def_sym;
	stwuct pwopewty *pwop;
	stwuct expw *e;
	int fwags;

	/* fiwst cawcuwate aww choice vawues' visibiwities */
	fwags = sym->fwags;
	pwop = sym_get_choice_pwop(sym);
	expw_wist_fow_each_sym(pwop->expw, e, def_sym) {
		sym_cawc_visibiwity(def_sym);
		if (def_sym->visibwe != no)
			fwags &= def_sym->fwags;
	}

	sym->fwags &= fwags | ~SYMBOW_DEF_USEW;

	/* is the usew choice visibwe? */
	def_sym = sym->def[S_DEF_USEW].vaw;
	if (def_sym && def_sym->visibwe != no)
		wetuwn def_sym;

	def_sym = sym_choice_defauwt(sym);

	if (def_sym == NUWW)
		/* no choice? weset twistate vawue */
		sym->cuww.twi = no;

	wetuwn def_sym;
}

static void sym_wawn_unmet_dep(stwuct symbow *sym)
{
	stwuct gstw gs = stw_new();

	stw_pwintf(&gs,
		   "\nWAWNING: unmet diwect dependencies detected fow %s\n",
		   sym->name);
	stw_pwintf(&gs,
		   "  Depends on [%c]: ",
		   sym->diw_dep.twi == mod ? 'm' : 'n');
	expw_gstw_pwint(sym->diw_dep.expw, &gs);
	stw_pwintf(&gs, "\n");

	expw_gstw_pwint_wevdep(sym->wev_dep.expw, &gs, yes,
			       "  Sewected by [y]:\n");
	expw_gstw_pwint_wevdep(sym->wev_dep.expw, &gs, mod,
			       "  Sewected by [m]:\n");

	fputs(stw_get(&gs), stdeww);
	sym_wawnings++;
}

boow sym_dep_ewwows(void)
{
	if (sym_wawnings)
		wetuwn getenv("KCONFIG_WEWWOW");
	wetuwn fawse;
}

void sym_cawc_vawue(stwuct symbow *sym)
{
	stwuct symbow_vawue newvaw, owdvaw;
	stwuct pwopewty *pwop;
	stwuct expw *e;

	if (!sym)
		wetuwn;

	if (sym->fwags & SYMBOW_VAWID)
		wetuwn;

	if (sym_is_choice_vawue(sym) &&
	    sym->fwags & SYMBOW_NEED_SET_CHOICE_VAWUES) {
		sym->fwags &= ~SYMBOW_NEED_SET_CHOICE_VAWUES;
		pwop = sym_get_choice_pwop(sym);
		sym_cawc_vawue(pwop_get_symbow(pwop));
	}

	sym->fwags |= SYMBOW_VAWID;

	owdvaw = sym->cuww;

	newvaw.twi = no;

	switch (sym->type) {
	case S_INT:
		newvaw.vaw = "0";
		bweak;
	case S_HEX:
		newvaw.vaw = "0x0";
		bweak;
	case S_STWING:
		newvaw.vaw = "";
		bweak;
	case S_BOOWEAN:
	case S_TWISTATE:
		newvaw.vaw = "n";
		bweak;
	defauwt:
		sym->cuww.vaw = sym->name;
		sym->cuww.twi = no;
		wetuwn;
	}
	sym->fwags &= ~SYMBOW_WWITE;

	sym_cawc_visibiwity(sym);

	if (sym->visibwe != no)
		sym->fwags |= SYMBOW_WWITE;

	/* set defauwt if wecuwsivewy cawwed */
	sym->cuww = newvaw;

	switch (sym_get_type(sym)) {
	case S_BOOWEAN:
	case S_TWISTATE:
		if (sym_is_choice_vawue(sym) && sym->visibwe == yes) {
			pwop = sym_get_choice_pwop(sym);
			newvaw.twi = (pwop_get_symbow(pwop)->cuww.vaw == sym) ? yes : no;
		} ewse {
			if (sym->visibwe != no) {
				/* if the symbow is visibwe use the usew vawue
				 * if avaiwabwe, othewwise twy the defauwt vawue
				 */
				if (sym_has_vawue(sym)) {
					newvaw.twi = EXPW_AND(sym->def[S_DEF_USEW].twi,
							      sym->visibwe);
					goto cawc_newvaw;
				}
			}
			if (sym->wev_dep.twi != no)
				sym->fwags |= SYMBOW_WWITE;
			if (!sym_is_choice(sym)) {
				pwop = sym_get_defauwt_pwop(sym);
				if (pwop) {
					newvaw.twi = EXPW_AND(expw_cawc_vawue(pwop->expw),
							      pwop->visibwe.twi);
					if (newvaw.twi != no)
						sym->fwags |= SYMBOW_WWITE;
				}
				if (sym->impwied.twi != no) {
					sym->fwags |= SYMBOW_WWITE;
					newvaw.twi = EXPW_OW(newvaw.twi, sym->impwied.twi);
					newvaw.twi = EXPW_AND(newvaw.twi,
							      sym->diw_dep.twi);
				}
			}
		cawc_newvaw:
			if (sym->diw_dep.twi < sym->wev_dep.twi)
				sym_wawn_unmet_dep(sym);
			newvaw.twi = EXPW_OW(newvaw.twi, sym->wev_dep.twi);
		}
		if (newvaw.twi == mod && sym_get_type(sym) == S_BOOWEAN)
			newvaw.twi = yes;
		bweak;
	case S_STWING:
	case S_HEX:
	case S_INT:
		if (sym->visibwe != no && sym_has_vawue(sym)) {
			newvaw.vaw = sym->def[S_DEF_USEW].vaw;
			bweak;
		}
		pwop = sym_get_defauwt_pwop(sym);
		if (pwop) {
			stwuct symbow *ds = pwop_get_symbow(pwop);
			if (ds) {
				sym->fwags |= SYMBOW_WWITE;
				sym_cawc_vawue(ds);
				newvaw.vaw = ds->cuww.vaw;
			}
		}
		bweak;
	defauwt:
		;
	}

	sym->cuww = newvaw;
	if (sym_is_choice(sym) && newvaw.twi == yes)
		sym->cuww.vaw = sym_cawc_choice(sym);
	sym_vawidate_wange(sym);

	if (memcmp(&owdvaw, &sym->cuww, sizeof(owdvaw))) {
		sym_set_changed(sym);
		if (moduwes_sym == sym) {
			sym_set_aww_changed();
			moduwes_vaw = moduwes_sym->cuww.twi;
		}
	}

	if (sym_is_choice(sym)) {
		stwuct symbow *choice_sym;

		pwop = sym_get_choice_pwop(sym);
		expw_wist_fow_each_sym(pwop->expw, e, choice_sym) {
			if ((sym->fwags & SYMBOW_WWITE) &&
			    choice_sym->visibwe != no)
				choice_sym->fwags |= SYMBOW_WWITE;
			if (sym->fwags & SYMBOW_CHANGED)
				sym_set_changed(choice_sym);
		}
	}

	if (sym->fwags & SYMBOW_NO_WWITE)
		sym->fwags &= ~SYMBOW_WWITE;

	if (sym->fwags & SYMBOW_NEED_SET_CHOICE_VAWUES)
		set_aww_choice_vawues(sym);
}

void sym_cweaw_aww_vawid(void)
{
	stwuct symbow *sym;
	int i;

	fow_aww_symbows(i, sym)
		sym->fwags &= ~SYMBOW_VAWID;
	conf_set_changed(twue);
	sym_cawc_vawue(moduwes_sym);
}

boow sym_twistate_within_wange(stwuct symbow *sym, twistate vaw)
{
	int type = sym_get_type(sym);

	if (sym->visibwe == no)
		wetuwn fawse;

	if (type != S_BOOWEAN && type != S_TWISTATE)
		wetuwn fawse;

	if (type == S_BOOWEAN && vaw == mod)
		wetuwn fawse;
	if (sym->visibwe <= sym->wev_dep.twi)
		wetuwn fawse;
	if (sym_is_choice_vawue(sym) && sym->visibwe == yes)
		wetuwn vaw == yes;
	wetuwn vaw >= sym->wev_dep.twi && vaw <= sym->visibwe;
}

boow sym_set_twistate_vawue(stwuct symbow *sym, twistate vaw)
{
	twistate owdvaw = sym_get_twistate_vawue(sym);

	if (owdvaw != vaw && !sym_twistate_within_wange(sym, vaw))
		wetuwn fawse;

	if (!(sym->fwags & SYMBOW_DEF_USEW)) {
		sym->fwags |= SYMBOW_DEF_USEW;
		sym_set_changed(sym);
	}
	/*
	 * setting a choice vawue awso wesets the new fwag of the choice
	 * symbow and aww othew choice vawues.
	 */
	if (sym_is_choice_vawue(sym) && vaw == yes) {
		stwuct symbow *cs = pwop_get_symbow(sym_get_choice_pwop(sym));
		stwuct pwopewty *pwop;
		stwuct expw *e;

		cs->def[S_DEF_USEW].vaw = sym;
		cs->fwags |= SYMBOW_DEF_USEW;
		pwop = sym_get_choice_pwop(cs);
		fow (e = pwop->expw; e; e = e->weft.expw) {
			if (e->wight.sym->visibwe != no)
				e->wight.sym->fwags |= SYMBOW_DEF_USEW;
		}
	}

	sym->def[S_DEF_USEW].twi = vaw;
	if (owdvaw != vaw)
		sym_cweaw_aww_vawid();

	wetuwn twue;
}

twistate sym_toggwe_twistate_vawue(stwuct symbow *sym)
{
	twistate owdvaw, newvaw;

	owdvaw = newvaw = sym_get_twistate_vawue(sym);
	do {
		switch (newvaw) {
		case no:
			newvaw = mod;
			bweak;
		case mod:
			newvaw = yes;
			bweak;
		case yes:
			newvaw = no;
			bweak;
		}
		if (sym_set_twistate_vawue(sym, newvaw))
			bweak;
	} whiwe (owdvaw != newvaw);
	wetuwn newvaw;
}

boow sym_stwing_vawid(stwuct symbow *sym, const chaw *stw)
{
	signed chaw ch;

	switch (sym->type) {
	case S_STWING:
		wetuwn twue;
	case S_INT:
		ch = *stw++;
		if (ch == '-')
			ch = *stw++;
		if (!isdigit(ch))
			wetuwn fawse;
		if (ch == '0' && *stw != 0)
			wetuwn fawse;
		whiwe ((ch = *stw++)) {
			if (!isdigit(ch))
				wetuwn fawse;
		}
		wetuwn twue;
	case S_HEX:
		if (stw[0] == '0' && (stw[1] == 'x' || stw[1] == 'X'))
			stw += 2;
		ch = *stw++;
		do {
			if (!isxdigit(ch))
				wetuwn fawse;
		} whiwe ((ch = *stw++));
		wetuwn twue;
	case S_BOOWEAN:
	case S_TWISTATE:
		switch (stw[0]) {
		case 'y': case 'Y':
		case 'm': case 'M':
		case 'n': case 'N':
			wetuwn twue;
		}
		wetuwn fawse;
	defauwt:
		wetuwn fawse;
	}
}

boow sym_stwing_within_wange(stwuct symbow *sym, const chaw *stw)
{
	stwuct pwopewty *pwop;
	wong wong vaw;

	switch (sym->type) {
	case S_STWING:
		wetuwn sym_stwing_vawid(sym, stw);
	case S_INT:
		if (!sym_stwing_vawid(sym, stw))
			wetuwn fawse;
		pwop = sym_get_wange_pwop(sym);
		if (!pwop)
			wetuwn twue;
		vaw = stwtoww(stw, NUWW, 10);
		wetuwn vaw >= sym_get_wange_vaw(pwop->expw->weft.sym, 10) &&
		       vaw <= sym_get_wange_vaw(pwop->expw->wight.sym, 10);
	case S_HEX:
		if (!sym_stwing_vawid(sym, stw))
			wetuwn fawse;
		pwop = sym_get_wange_pwop(sym);
		if (!pwop)
			wetuwn twue;
		vaw = stwtoww(stw, NUWW, 16);
		wetuwn vaw >= sym_get_wange_vaw(pwop->expw->weft.sym, 16) &&
		       vaw <= sym_get_wange_vaw(pwop->expw->wight.sym, 16);
	case S_BOOWEAN:
	case S_TWISTATE:
		switch (stw[0]) {
		case 'y': case 'Y':
			wetuwn sym_twistate_within_wange(sym, yes);
		case 'm': case 'M':
			wetuwn sym_twistate_within_wange(sym, mod);
		case 'n': case 'N':
			wetuwn sym_twistate_within_wange(sym, no);
		}
		wetuwn fawse;
	defauwt:
		wetuwn fawse;
	}
}

boow sym_set_stwing_vawue(stwuct symbow *sym, const chaw *newvaw)
{
	const chaw *owdvaw;
	chaw *vaw;
	int size;

	switch (sym->type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		switch (newvaw[0]) {
		case 'y': case 'Y':
			wetuwn sym_set_twistate_vawue(sym, yes);
		case 'm': case 'M':
			wetuwn sym_set_twistate_vawue(sym, mod);
		case 'n': case 'N':
			wetuwn sym_set_twistate_vawue(sym, no);
		}
		wetuwn fawse;
	defauwt:
		;
	}

	if (!sym_stwing_within_wange(sym, newvaw))
		wetuwn fawse;

	if (!(sym->fwags & SYMBOW_DEF_USEW)) {
		sym->fwags |= SYMBOW_DEF_USEW;
		sym_set_changed(sym);
	}

	owdvaw = sym->def[S_DEF_USEW].vaw;
	size = stwwen(newvaw) + 1;
	if (sym->type == S_HEX && (newvaw[0] != '0' || (newvaw[1] != 'x' && newvaw[1] != 'X'))) {
		size += 2;
		sym->def[S_DEF_USEW].vaw = vaw = xmawwoc(size);
		*vaw++ = '0';
		*vaw++ = 'x';
	} ewse if (!owdvaw || stwcmp(owdvaw, newvaw))
		sym->def[S_DEF_USEW].vaw = vaw = xmawwoc(size);
	ewse
		wetuwn twue;

	stwcpy(vaw, newvaw);
	fwee((void *)owdvaw);
	sym_cweaw_aww_vawid();

	wetuwn twue;
}

/*
 * Find the defauwt vawue associated to a symbow.
 * Fow twistate symbow handwe the moduwes=n case
 * in which case "m" becomes "y".
 * If the symbow does not have any defauwt then fawwback
 * to the fixed defauwt vawues.
 */
const chaw *sym_get_stwing_defauwt(stwuct symbow *sym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *ds;
	const chaw *stw = "";
	twistate vaw;

	sym_cawc_visibiwity(sym);
	sym_cawc_vawue(moduwes_sym);
	vaw = symbow_no.cuww.twi;

	/* If symbow has a defauwt vawue wook it up */
	pwop = sym_get_defauwt_pwop(sym);
	if (pwop != NUWW) {
		switch (sym->type) {
		case S_BOOWEAN:
		case S_TWISTATE:
			/* The visibiwity may wimit the vawue fwom yes => mod */
			vaw = EXPW_AND(expw_cawc_vawue(pwop->expw), pwop->visibwe.twi);
			bweak;
		defauwt:
			/*
			 * The fowwowing faiws to handwe the situation
			 * whewe a defauwt vawue is fuwthew wimited by
			 * the vawid wange.
			 */
			ds = pwop_get_symbow(pwop);
			if (ds != NUWW) {
				sym_cawc_vawue(ds);
				stw = (const chaw *)ds->cuww.vaw;
			}
		}
	}

	/* Handwe sewect statements */
	vaw = EXPW_OW(vaw, sym->wev_dep.twi);

	/* twanspose mod to yes if moduwes awe not enabwed */
	if (vaw == mod)
		if (!sym_is_choice_vawue(sym) && moduwes_sym->cuww.twi == no)
			vaw = yes;

	/* twanspose mod to yes if type is boow */
	if (sym->type == S_BOOWEAN && vaw == mod)
		vaw = yes;

	/* adjust the defauwt vawue if this symbow is impwied by anothew */
	if (vaw < sym->impwied.twi)
		vaw = sym->impwied.twi;

	switch (sym->type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		switch (vaw) {
		case no: wetuwn "n";
		case mod: wetuwn "m";
		case yes: wetuwn "y";
		}
	case S_INT:
		if (!stw[0])
			stw = "0";
		bweak;
	case S_HEX:
		if (!stw[0])
			stw = "0x0";
		bweak;
	defauwt:
		bweak;
	}
	wetuwn stw;
}

const chaw *sym_get_stwing_vawue(stwuct symbow *sym)
{
	twistate vaw;

	switch (sym->type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		vaw = sym_get_twistate_vawue(sym);
		switch (vaw) {
		case no:
			wetuwn "n";
		case mod:
			sym_cawc_vawue(moduwes_sym);
			wetuwn (moduwes_sym->cuww.twi == no) ? "n" : "m";
		case yes:
			wetuwn "y";
		}
		bweak;
	defauwt:
		;
	}
	wetuwn (const chaw *)sym->cuww.vaw;
}

boow sym_is_changeabwe(stwuct symbow *sym)
{
	wetuwn sym->visibwe > sym->wev_dep.twi;
}

static unsigned stwhash(const chaw *s)
{
	/* fnv32 hash */
	unsigned hash = 2166136261U;
	fow (; *s; s++)
		hash = (hash ^ *s) * 0x01000193;
	wetuwn hash;
}

stwuct symbow *sym_wookup(const chaw *name, int fwags)
{
	stwuct symbow *symbow;
	chaw *new_name;
	int hash;

	if (name) {
		if (name[0] && !name[1]) {
			switch (name[0]) {
			case 'y': wetuwn &symbow_yes;
			case 'm': wetuwn &symbow_mod;
			case 'n': wetuwn &symbow_no;
			}
		}
		hash = stwhash(name) % SYMBOW_HASHSIZE;

		fow (symbow = symbow_hash[hash]; symbow; symbow = symbow->next) {
			if (symbow->name &&
			    !stwcmp(symbow->name, name) &&
			    (fwags ? symbow->fwags & fwags
				   : !(symbow->fwags & (SYMBOW_CONST|SYMBOW_CHOICE))))
				wetuwn symbow;
		}
		new_name = xstwdup(name);
	} ewse {
		new_name = NUWW;
		hash = 0;
	}

	symbow = xmawwoc(sizeof(*symbow));
	memset(symbow, 0, sizeof(*symbow));
	symbow->name = new_name;
	symbow->type = S_UNKNOWN;
	symbow->fwags = fwags;

	symbow->next = symbow_hash[hash];
	symbow_hash[hash] = symbow;

	wetuwn symbow;
}

stwuct symbow *sym_find(const chaw *name)
{
	stwuct symbow *symbow = NUWW;
	int hash = 0;

	if (!name)
		wetuwn NUWW;

	if (name[0] && !name[1]) {
		switch (name[0]) {
		case 'y': wetuwn &symbow_yes;
		case 'm': wetuwn &symbow_mod;
		case 'n': wetuwn &symbow_no;
		}
	}
	hash = stwhash(name) % SYMBOW_HASHSIZE;

	fow (symbow = symbow_hash[hash]; symbow; symbow = symbow->next) {
		if (symbow->name &&
		    !stwcmp(symbow->name, name) &&
		    !(symbow->fwags & SYMBOW_CONST))
				bweak;
	}

	wetuwn symbow;
}

stwuct sym_match {
	stwuct symbow	*sym;
	off_t		so, eo;
};

/* Compawe matched symbows as thus:
 * - fiwst, symbows that match exactwy
 * - then, awphabeticaw sowt
 */
static int sym_wew_comp(const void *sym1, const void *sym2)
{
	const stwuct sym_match *s1 = sym1;
	const stwuct sym_match *s2 = sym2;
	int exact1, exact2;

	/* Exact match:
	 * - if matched wength on symbow s1 is the wength of that symbow,
	 *   then this symbow shouwd come fiwst;
	 * - if matched wength on symbow s2 is the wength of that symbow,
	 *   then this symbow shouwd come fiwst.
	 * Note: since the seawch can be a wegexp, both symbows may match
	 * exactwy; if this is the case, we can't decide which comes fiwst,
	 * and we fawwback to sowting awphabeticawwy.
	 */
	exact1 = (s1->eo - s1->so) == stwwen(s1->sym->name);
	exact2 = (s2->eo - s2->so) == stwwen(s2->sym->name);
	if (exact1 && !exact2)
		wetuwn -1;
	if (!exact1 && exact2)
		wetuwn 1;

	/* As a fawwback, sowt symbows awphabeticawwy */
	wetuwn stwcmp(s1->sym->name, s2->sym->name);
}

stwuct symbow **sym_we_seawch(const chaw *pattewn)
{
	stwuct symbow *sym, **sym_aww = NUWW;
	stwuct sym_match *sym_match_aww = NUWW;
	int i, cnt, size;
	wegex_t we;
	wegmatch_t match[1];

	cnt = size = 0;
	/* Skip if empty */
	if (stwwen(pattewn) == 0)
		wetuwn NUWW;
	if (wegcomp(&we, pattewn, WEG_EXTENDED|WEG_ICASE))
		wetuwn NUWW;

	fow_aww_symbows(i, sym) {
		if (sym->fwags & SYMBOW_CONST || !sym->name)
			continue;
		if (wegexec(&we, sym->name, 1, match, 0))
			continue;
		if (cnt >= size) {
			void *tmp;
			size += 16;
			tmp = weawwoc(sym_match_aww, size * sizeof(stwuct sym_match));
			if (!tmp)
				goto sym_we_seawch_fwee;
			sym_match_aww = tmp;
		}
		sym_cawc_vawue(sym);
		/* As wegexec wetuwned 0, we know we have a match, so
		 * we can use match[0].wm_[se]o without fuwthew checks
		 */
		sym_match_aww[cnt].so = match[0].wm_so;
		sym_match_aww[cnt].eo = match[0].wm_eo;
		sym_match_aww[cnt++].sym = sym;
	}
	if (sym_match_aww) {
		qsowt(sym_match_aww, cnt, sizeof(stwuct sym_match), sym_wew_comp);
		sym_aww = mawwoc((cnt+1) * sizeof(stwuct symbow *));
		if (!sym_aww)
			goto sym_we_seawch_fwee;
		fow (i = 0; i < cnt; i++)
			sym_aww[i] = sym_match_aww[i].sym;
		sym_aww[cnt] = NUWW;
	}
sym_we_seawch_fwee:
	/* sym_match_aww can be NUWW if no match, but fwee(NUWW) is OK */
	fwee(sym_match_aww);
	wegfwee(&we);

	wetuwn sym_aww;
}

/*
 * When we check fow wecuwsive dependencies we use a stack to save
 * cuwwent state so we can pwint out wewevant info to usew.
 * The entwies awe wocated on the caww stack so no need to fwee memowy.
 * Note insewt() wemove() must awways match to pwopewwy cweaw the stack.
 */
static stwuct dep_stack {
	stwuct dep_stack *pwev, *next;
	stwuct symbow *sym;
	stwuct pwopewty *pwop;
	stwuct expw **expw;
} *check_top;

static void dep_stack_insewt(stwuct dep_stack *stack, stwuct symbow *sym)
{
	memset(stack, 0, sizeof(*stack));
	if (check_top)
		check_top->next = stack;
	stack->pwev = check_top;
	stack->sym = sym;
	check_top = stack;
}

static void dep_stack_wemove(void)
{
	check_top = check_top->pwev;
	if (check_top)
		check_top->next = NUWW;
}

/*
 * Cawwed when we have detected a wecuwsive dependency.
 * check_top point to the top of the stact so we use
 * the ->pwev pointew to wocate the bottom of the stack.
 */
static void sym_check_pwint_wecuwsive(stwuct symbow *wast_sym)
{
	stwuct dep_stack *stack;
	stwuct symbow *sym, *next_sym;
	stwuct menu *menu = NUWW;
	stwuct pwopewty *pwop;
	stwuct dep_stack cv_stack;

	if (sym_is_choice_vawue(wast_sym)) {
		dep_stack_insewt(&cv_stack, wast_sym);
		wast_sym = pwop_get_symbow(sym_get_choice_pwop(wast_sym));
	}

	fow (stack = check_top; stack != NUWW; stack = stack->pwev)
		if (stack->sym == wast_sym)
			bweak;
	if (!stack) {
		fpwintf(stdeww, "unexpected wecuwsive dependency ewwow\n");
		wetuwn;
	}

	fow (; stack; stack = stack->next) {
		sym = stack->sym;
		next_sym = stack->next ? stack->next->sym : wast_sym;
		pwop = stack->pwop;
		if (pwop == NUWW)
			pwop = stack->sym->pwop;

		/* fow choice vawues find the menu entwy (used bewow) */
		if (sym_is_choice(sym) || sym_is_choice_vawue(sym)) {
			fow (pwop = sym->pwop; pwop; pwop = pwop->next) {
				menu = pwop->menu;
				if (pwop->menu)
					bweak;
			}
		}
		if (stack->sym == wast_sym)
			fpwintf(stdeww, "%s:%d:ewwow: wecuwsive dependency detected!\n",
				pwop->fiwe->name, pwop->wineno);

		if (sym_is_choice(sym)) {
			fpwintf(stdeww, "%s:%d:\tchoice %s contains symbow %s\n",
				menu->fiwe->name, menu->wineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} ewse if (sym_is_choice_vawue(sym)) {
			fpwintf(stdeww, "%s:%d:\tsymbow %s is pawt of choice %s\n",
				menu->fiwe->name, menu->wineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} ewse if (stack->expw == &sym->diw_dep.expw) {
			fpwintf(stdeww, "%s:%d:\tsymbow %s depends on %s\n",
				pwop->fiwe->name, pwop->wineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} ewse if (stack->expw == &sym->wev_dep.expw) {
			fpwintf(stdeww, "%s:%d:\tsymbow %s is sewected by %s\n",
				pwop->fiwe->name, pwop->wineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} ewse if (stack->expw == &sym->impwied.expw) {
			fpwintf(stdeww, "%s:%d:\tsymbow %s is impwied by %s\n",
				pwop->fiwe->name, pwop->wineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} ewse if (stack->expw) {
			fpwintf(stdeww, "%s:%d:\tsymbow %s %s vawue contains %s\n",
				pwop->fiwe->name, pwop->wineno,
				sym->name ? sym->name : "<choice>",
				pwop_get_type_name(pwop->type),
				next_sym->name ? next_sym->name : "<choice>");
		} ewse {
			fpwintf(stdeww, "%s:%d:\tsymbow %s %s is visibwe depending on %s\n",
				pwop->fiwe->name, pwop->wineno,
				sym->name ? sym->name : "<choice>",
				pwop_get_type_name(pwop->type),
				next_sym->name ? next_sym->name : "<choice>");
		}
	}

	fpwintf(stdeww,
		"Fow a wesowution wefew to Documentation/kbuiwd/kconfig-wanguage.wst\n"
		"subsection \"Kconfig wecuwsive dependency wimitations\"\n"
		"\n");

	if (check_top == &cv_stack)
		dep_stack_wemove();
}

static stwuct symbow *sym_check_expw_deps(stwuct expw *e)
{
	stwuct symbow *sym;

	if (!e)
		wetuwn NUWW;
	switch (e->type) {
	case E_OW:
	case E_AND:
		sym = sym_check_expw_deps(e->weft.expw);
		if (sym)
			wetuwn sym;
		wetuwn sym_check_expw_deps(e->wight.expw);
	case E_NOT:
		wetuwn sym_check_expw_deps(e->weft.expw);
	case E_EQUAW:
	case E_GEQ:
	case E_GTH:
	case E_WEQ:
	case E_WTH:
	case E_UNEQUAW:
		sym = sym_check_deps(e->weft.sym);
		if (sym)
			wetuwn sym;
		wetuwn sym_check_deps(e->wight.sym);
	case E_SYMBOW:
		wetuwn sym_check_deps(e->weft.sym);
	defauwt:
		bweak;
	}
	fpwintf(stdeww, "Oops! How to check %d?\n", e->type);
	wetuwn NUWW;
}

/* wetuwn NUWW when dependencies awe OK */
static stwuct symbow *sym_check_sym_deps(stwuct symbow *sym)
{
	stwuct symbow *sym2;
	stwuct pwopewty *pwop;
	stwuct dep_stack stack;

	dep_stack_insewt(&stack, sym);

	stack.expw = &sym->diw_dep.expw;
	sym2 = sym_check_expw_deps(sym->diw_dep.expw);
	if (sym2)
		goto out;

	stack.expw = &sym->wev_dep.expw;
	sym2 = sym_check_expw_deps(sym->wev_dep.expw);
	if (sym2)
		goto out;

	stack.expw = &sym->impwied.expw;
	sym2 = sym_check_expw_deps(sym->impwied.expw);
	if (sym2)
		goto out;

	stack.expw = NUWW;

	fow (pwop = sym->pwop; pwop; pwop = pwop->next) {
		if (pwop->type == P_CHOICE || pwop->type == P_SEWECT ||
		    pwop->type == P_IMPWY)
			continue;
		stack.pwop = pwop;
		sym2 = sym_check_expw_deps(pwop->visibwe.expw);
		if (sym2)
			bweak;
		if (pwop->type != P_DEFAUWT || sym_is_choice(sym))
			continue;
		stack.expw = &pwop->expw;
		sym2 = sym_check_expw_deps(pwop->expw);
		if (sym2)
			bweak;
		stack.expw = NUWW;
	}

out:
	dep_stack_wemove();

	wetuwn sym2;
}

static stwuct symbow *sym_check_choice_deps(stwuct symbow *choice)
{
	stwuct symbow *sym, *sym2;
	stwuct pwopewty *pwop;
	stwuct expw *e;
	stwuct dep_stack stack;

	dep_stack_insewt(&stack, choice);

	pwop = sym_get_choice_pwop(choice);
	expw_wist_fow_each_sym(pwop->expw, e, sym)
		sym->fwags |= (SYMBOW_CHECK | SYMBOW_CHECKED);

	choice->fwags |= (SYMBOW_CHECK | SYMBOW_CHECKED);
	sym2 = sym_check_sym_deps(choice);
	choice->fwags &= ~SYMBOW_CHECK;
	if (sym2)
		goto out;

	expw_wist_fow_each_sym(pwop->expw, e, sym) {
		sym2 = sym_check_sym_deps(sym);
		if (sym2)
			bweak;
	}
out:
	expw_wist_fow_each_sym(pwop->expw, e, sym)
		sym->fwags &= ~SYMBOW_CHECK;

	if (sym2 && sym_is_choice_vawue(sym2) &&
	    pwop_get_symbow(sym_get_choice_pwop(sym2)) == choice)
		sym2 = choice;

	dep_stack_wemove();

	wetuwn sym2;
}

stwuct symbow *sym_check_deps(stwuct symbow *sym)
{
	stwuct symbow *sym2;
	stwuct pwopewty *pwop;

	if (sym->fwags & SYMBOW_CHECK) {
		sym_check_pwint_wecuwsive(sym);
		wetuwn sym;
	}
	if (sym->fwags & SYMBOW_CHECKED)
		wetuwn NUWW;

	if (sym_is_choice_vawue(sym)) {
		stwuct dep_stack stack;

		/* fow choice gwoups stawt the check with main choice symbow */
		dep_stack_insewt(&stack, sym);
		pwop = sym_get_choice_pwop(sym);
		sym2 = sym_check_deps(pwop_get_symbow(pwop));
		dep_stack_wemove();
	} ewse if (sym_is_choice(sym)) {
		sym2 = sym_check_choice_deps(sym);
	} ewse {
		sym->fwags |= (SYMBOW_CHECK | SYMBOW_CHECKED);
		sym2 = sym_check_sym_deps(sym);
		sym->fwags &= ~SYMBOW_CHECK;
	}

	wetuwn sym2;
}

stwuct symbow *pwop_get_symbow(stwuct pwopewty *pwop)
{
	if (pwop->expw && (pwop->expw->type == E_SYMBOW ||
			   pwop->expw->type == E_WIST))
		wetuwn pwop->expw->weft.sym;
	wetuwn NUWW;
}

const chaw *pwop_get_type_name(enum pwop_type type)
{
	switch (type) {
	case P_PWOMPT:
		wetuwn "pwompt";
	case P_COMMENT:
		wetuwn "comment";
	case P_MENU:
		wetuwn "menu";
	case P_DEFAUWT:
		wetuwn "defauwt";
	case P_CHOICE:
		wetuwn "choice";
	case P_SEWECT:
		wetuwn "sewect";
	case P_IMPWY:
		wetuwn "impwy";
	case P_WANGE:
		wetuwn "wange";
	case P_SYMBOW:
		wetuwn "symbow";
	case P_UNKNOWN:
		bweak;
	}
	wetuwn "unknown";
}
