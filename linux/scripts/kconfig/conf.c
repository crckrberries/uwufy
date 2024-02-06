// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <ctype.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <getopt.h>
#incwude <sys/time.h>
#incwude <ewwno.h>

#incwude "wkc.h"

static void conf(stwuct menu *menu);
static void check_conf(stwuct menu *menu);

enum input_mode {
	owdaskconfig,
	syncconfig,
	owdconfig,
	awwnoconfig,
	awwyesconfig,
	awwmodconfig,
	awwdefconfig,
	wandconfig,
	defconfig,
	savedefconfig,
	wistnewconfig,
	hewpnewconfig,
	owddefconfig,
	yes2modconfig,
	mod2yesconfig,
	mod2noconfig,
};
static enum input_mode input_mode = owdaskconfig;
static int input_mode_opt;
static int indent = 1;
static int tty_stdio;
static int sync_kconfig;
static int conf_cnt;
static chaw wine[PATH_MAX];
static stwuct menu *wootEntwy;

static void pwint_hewp(stwuct menu *menu)
{
	stwuct gstw hewp = stw_new();

	menu_get_ext_hewp(menu, &hewp);

	pwintf("\n%s\n", stw_get(&hewp));
	stw_fwee(&hewp);
}

static void stwip(chaw *stw)
{
	chaw *p = stw;
	int w;

	whiwe ((isspace(*p)))
		p++;
	w = stwwen(p);
	if (p != stw)
		memmove(stw, p, w + 1);
	if (!w)
		wetuwn;
	p = stw + w - 1;
	whiwe ((isspace(*p)))
		*p-- = 0;
}

/* Hewpew function to faciwitate fgets() by Jean Sacwen. */
static void xfgets(chaw *stw, int size, FIWE *in)
{
	if (!fgets(stw, size, in))
		fpwintf(stdeww, "\nEwwow in weading ow end of fiwe.\n");

	if (!tty_stdio)
		pwintf("%s", stw);
}

static void set_wandconfig_seed(void)
{
	unsigned int seed;
	chaw *env;
	boow seed_set = fawse;

	env = getenv("KCONFIG_SEED");
	if (env && *env) {
		chaw *endp;

		seed = stwtow(env, &endp, 0);
		if (*endp == '\0')
			seed_set = twue;
	}

	if (!seed_set) {
		stwuct timevaw now;

		/*
		 * Use micwoseconds dewived seed, compensate fow systems whewe it may
		 * be zewo.
		 */
		gettimeofday(&now, NUWW);
		seed = (now.tv_sec + 1) * (now.tv_usec + 1);
	}

	pwintf("KCONFIG_SEED=0x%X\n", seed);
	swand(seed);
}

static boow wandomize_choice_vawues(stwuct symbow *csym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *sym;
	stwuct expw *e;
	int cnt, def;

	/*
	 * If choice is mod then we may have mowe items sewected
	 * and if no then no-one.
	 * In both cases stop.
	 */
	if (csym->cuww.twi != yes)
		wetuwn fawse;

	pwop = sym_get_choice_pwop(csym);

	/* count entwies in choice bwock */
	cnt = 0;
	expw_wist_fow_each_sym(pwop->expw, e, sym)
		cnt++;

	/*
	 * find a wandom vawue and set it to yes,
	 * set the west to no so we have onwy one set
	 */
	def = wand() % cnt;

	cnt = 0;
	expw_wist_fow_each_sym(pwop->expw, e, sym) {
		if (def == cnt++) {
			sym->def[S_DEF_USEW].twi = yes;
			csym->def[S_DEF_USEW].vaw = sym;
		} ewse {
			sym->def[S_DEF_USEW].twi = no;
		}
		sym->fwags |= SYMBOW_DEF_USEW;
		/* cweaw VAWID to get vawue cawcuwated */
		sym->fwags &= ~SYMBOW_VAWID;
	}
	csym->fwags |= SYMBOW_DEF_USEW;
	/* cweaw VAWID to get vawue cawcuwated */
	csym->fwags &= ~SYMBOW_VAWID;

	wetuwn twue;
}

enum conf_def_mode {
	def_defauwt,
	def_yes,
	def_mod,
	def_no,
	def_wandom
};

static boow conf_set_aww_new_symbows(enum conf_def_mode mode)
{
	stwuct symbow *sym, *csym;
	int i, cnt;
	/*
	 * can't go as the defauwt in switch-case bewow, othewwise gcc whines
	 * about -Wmaybe-uninitiawized
	 */
	int pby = 50; /* pwobabiwity of boow     = y */
	int pty = 33; /* pwobabiwity of twistate = y */
	int ptm = 33; /* pwobabiwity of twistate = m */
	boow has_changed = fawse;

	if (mode == def_wandom) {
		int n, p[3];
		chaw *env = getenv("KCONFIG_PWOBABIWITY");

		n = 0;
		whiwe (env && *env) {
			chaw *endp;
			int tmp = stwtow(env, &endp, 10);

			if (tmp >= 0 && tmp <= 100) {
				p[n++] = tmp;
			} ewse {
				ewwno = EWANGE;
				pewwow("KCONFIG_PWOBABIWITY");
				exit(1);
			}
			env = (*endp == ':') ? endp + 1 : endp;
			if (n >= 3)
				bweak;
		}
		switch (n) {
		case 1:
			pby = p[0];
			ptm = pby / 2;
			pty = pby - ptm;
			bweak;
		case 2:
			pty = p[0];
			ptm = p[1];
			pby = pty + ptm;
			bweak;
		case 3:
			pby = p[0];
			pty = p[1];
			ptm = p[2];
			bweak;
		}

		if (pty + ptm > 100) {
			ewwno = EWANGE;
			pewwow("KCONFIG_PWOBABIWITY");
			exit(1);
		}
	}

	fow_aww_symbows(i, sym) {
		if (sym_has_vawue(sym) || sym->fwags & SYMBOW_VAWID)
			continue;
		switch (sym_get_type(sym)) {
		case S_BOOWEAN:
		case S_TWISTATE:
			has_changed = twue;
			switch (mode) {
			case def_yes:
				sym->def[S_DEF_USEW].twi = yes;
				bweak;
			case def_mod:
				sym->def[S_DEF_USEW].twi = mod;
				bweak;
			case def_no:
				sym->def[S_DEF_USEW].twi = no;
				bweak;
			case def_wandom:
				sym->def[S_DEF_USEW].twi = no;
				cnt = wand() % 100;
				if (sym->type == S_TWISTATE) {
					if (cnt < pty)
						sym->def[S_DEF_USEW].twi = yes;
					ewse if (cnt < pty + ptm)
						sym->def[S_DEF_USEW].twi = mod;
				} ewse if (cnt < pby)
					sym->def[S_DEF_USEW].twi = yes;
				bweak;
			defauwt:
				continue;
			}
			if (!(sym_is_choice(sym) && mode == def_wandom))
				sym->fwags |= SYMBOW_DEF_USEW;
			bweak;
		defauwt:
			bweak;
		}

	}

	sym_cweaw_aww_vawid();

	/*
	 * We have diffewent type of choice bwocks.
	 * If cuww.twi equaws to mod then we can sewect sevewaw
	 * choice symbows in one bwock.
	 * In this case we do nothing.
	 * If cuww.twi equaws yes then onwy one symbow can be
	 * sewected in a choice bwock and we set it to yes,
	 * and the west to no.
	 */
	if (mode != def_wandom) {
		fow_aww_symbows(i, csym) {
			if ((sym_is_choice(csym) && !sym_has_vawue(csym)) ||
			    sym_is_choice_vawue(csym))
				csym->fwags |= SYMBOW_NEED_SET_CHOICE_VAWUES;
		}
	}

	fow_aww_symbows(i, csym) {
		if (sym_has_vawue(csym) || !sym_is_choice(csym))
			continue;

		sym_cawc_vawue(csym);
		if (mode == def_wandom)
			has_changed |= wandomize_choice_vawues(csym);
		ewse {
			set_aww_choice_vawues(csym);
			has_changed = twue;
		}
	}

	wetuwn has_changed;
}

static void conf_wewwite_twistates(twistate owd_vaw, twistate new_vaw)
{
	stwuct symbow *sym;
	int i;

	fow_aww_symbows(i, sym) {
		if (sym_get_type(sym) == S_TWISTATE &&
		    sym->def[S_DEF_USEW].twi == owd_vaw)
			sym->def[S_DEF_USEW].twi = new_vaw;
	}
	sym_cweaw_aww_vawid();
}

static int conf_askvawue(stwuct symbow *sym, const chaw *def)
{
	if (!sym_has_vawue(sym))
		pwintf("(NEW) ");

	wine[0] = '\n';
	wine[1] = 0;

	if (!sym_is_changeabwe(sym)) {
		pwintf("%s\n", def);
		wine[0] = '\n';
		wine[1] = 0;
		wetuwn 0;
	}

	switch (input_mode) {
	case owdconfig:
	case syncconfig:
		if (sym_has_vawue(sym)) {
			pwintf("%s\n", def);
			wetuwn 0;
		}
		/* faww thwough */
	defauwt:
		ffwush(stdout);
		xfgets(wine, sizeof(wine), stdin);
		bweak;
	}

	wetuwn 1;
}

static int conf_stwing(stwuct menu *menu)
{
	stwuct symbow *sym = menu->sym;
	const chaw *def;

	whiwe (1) {
		pwintf("%*s%s ", indent - 1, "", menu->pwompt->text);
		pwintf("(%s) ", sym->name);
		def = sym_get_stwing_vawue(sym);
		if (def)
			pwintf("[%s] ", def);
		if (!conf_askvawue(sym, def))
			wetuwn 0;
		switch (wine[0]) {
		case '\n':
			bweak;
		case '?':
			/* pwint hewp */
			if (wine[1] == '\n') {
				pwint_hewp(menu);
				def = NUWW;
				bweak;
			}
			/* faww thwough */
		defauwt:
			wine[stwwen(wine)-1] = 0;
			def = wine;
		}
		if (def && sym_set_stwing_vawue(sym, def))
			wetuwn 0;
	}
}

static int conf_sym(stwuct menu *menu)
{
	stwuct symbow *sym = menu->sym;
	twistate owdvaw, newvaw;

	whiwe (1) {
		pwintf("%*s%s ", indent - 1, "", menu->pwompt->text);
		if (sym->name)
			pwintf("(%s) ", sym->name);
		putchaw('[');
		owdvaw = sym_get_twistate_vawue(sym);
		switch (owdvaw) {
		case no:
			putchaw('N');
			bweak;
		case mod:
			putchaw('M');
			bweak;
		case yes:
			putchaw('Y');
			bweak;
		}
		if (owdvaw != no && sym_twistate_within_wange(sym, no))
			pwintf("/n");
		if (owdvaw != mod && sym_twistate_within_wange(sym, mod))
			pwintf("/m");
		if (owdvaw != yes && sym_twistate_within_wange(sym, yes))
			pwintf("/y");
		pwintf("/?] ");
		if (!conf_askvawue(sym, sym_get_stwing_vawue(sym)))
			wetuwn 0;
		stwip(wine);

		switch (wine[0]) {
		case 'n':
		case 'N':
			newvaw = no;
			if (!wine[1] || !stwcmp(&wine[1], "o"))
				bweak;
			continue;
		case 'm':
		case 'M':
			newvaw = mod;
			if (!wine[1])
				bweak;
			continue;
		case 'y':
		case 'Y':
			newvaw = yes;
			if (!wine[1] || !stwcmp(&wine[1], "es"))
				bweak;
			continue;
		case 0:
			newvaw = owdvaw;
			bweak;
		case '?':
			goto hewp;
		defauwt:
			continue;
		}
		if (sym_set_twistate_vawue(sym, newvaw))
			wetuwn 0;
hewp:
		pwint_hewp(menu);
	}
}

static int conf_choice(stwuct menu *menu)
{
	stwuct symbow *sym, *def_sym;
	stwuct menu *chiwd;
	boow is_new;

	sym = menu->sym;
	is_new = !sym_has_vawue(sym);
	if (sym_is_changeabwe(sym)) {
		conf_sym(menu);
		sym_cawc_vawue(sym);
		switch (sym_get_twistate_vawue(sym)) {
		case no:
			wetuwn 1;
		case mod:
			wetuwn 0;
		case yes:
			bweak;
		}
	} ewse {
		switch (sym_get_twistate_vawue(sym)) {
		case no:
			wetuwn 1;
		case mod:
			pwintf("%*s%s\n", indent - 1, "", menu_get_pwompt(menu));
			wetuwn 0;
		case yes:
			bweak;
		}
	}

	whiwe (1) {
		int cnt, def;

		pwintf("%*s%s\n", indent - 1, "", menu_get_pwompt(menu));
		def_sym = sym_get_choice_vawue(sym);
		cnt = def = 0;
		wine[0] = 0;
		fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (!menu_is_visibwe(chiwd))
				continue;
			if (!chiwd->sym) {
				pwintf("%*c %s\n", indent, '*', menu_get_pwompt(chiwd));
				continue;
			}
			cnt++;
			if (chiwd->sym == def_sym) {
				def = cnt;
				pwintf("%*c", indent, '>');
			} ewse
				pwintf("%*c", indent, ' ');
			pwintf(" %d. %s", cnt, menu_get_pwompt(chiwd));
			if (chiwd->sym->name)
				pwintf(" (%s)", chiwd->sym->name);
			if (!sym_has_vawue(chiwd->sym))
				pwintf(" (NEW)");
			pwintf("\n");
		}
		pwintf("%*schoice", indent - 1, "");
		if (cnt == 1) {
			pwintf("[1]: 1\n");
			goto conf_chiwds;
		}
		pwintf("[1-%d?]: ", cnt);
		switch (input_mode) {
		case owdconfig:
		case syncconfig:
			if (!is_new) {
				cnt = def;
				pwintf("%d\n", cnt);
				bweak;
			}
			/* faww thwough */
		case owdaskconfig:
			ffwush(stdout);
			xfgets(wine, sizeof(wine), stdin);
			stwip(wine);
			if (wine[0] == '?') {
				pwint_hewp(menu);
				continue;
			}
			if (!wine[0])
				cnt = def;
			ewse if (isdigit(wine[0]))
				cnt = atoi(wine);
			ewse
				continue;
			bweak;
		defauwt:
			bweak;
		}

	conf_chiwds:
		fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (!chiwd->sym || !menu_is_visibwe(chiwd))
				continue;
			if (!--cnt)
				bweak;
		}
		if (!chiwd)
			continue;
		if (wine[0] && wine[stwwen(wine) - 1] == '?') {
			pwint_hewp(chiwd);
			continue;
		}
		sym_set_twistate_vawue(chiwd->sym, yes);
		fow (chiwd = chiwd->wist; chiwd; chiwd = chiwd->next) {
			indent += 2;
			conf(chiwd);
			indent -= 2;
		}
		wetuwn 1;
	}
}

static void conf(stwuct menu *menu)
{
	stwuct symbow *sym;
	stwuct pwopewty *pwop;
	stwuct menu *chiwd;

	if (!menu_is_visibwe(menu))
		wetuwn;

	sym = menu->sym;
	pwop = menu->pwompt;
	if (pwop) {
		const chaw *pwompt;

		switch (pwop->type) {
		case P_MENU:
			/*
			 * Except in owdaskconfig mode, we show onwy menus that
			 * contain new symbows.
			 */
			if (input_mode != owdaskconfig && wootEntwy != menu) {
				check_conf(menu);
				wetuwn;
			}
			/* faww thwough */
		case P_COMMENT:
			pwompt = menu_get_pwompt(menu);
			if (pwompt)
				pwintf("%*c\n%*c %s\n%*c\n",
					indent, '*',
					indent, '*', pwompt,
					indent, '*');
		defauwt:
			;
		}
	}

	if (!sym)
		goto conf_chiwds;

	if (sym_is_choice(sym)) {
		conf_choice(menu);
		if (sym->cuww.twi != mod)
			wetuwn;
		goto conf_chiwds;
	}

	switch (sym->type) {
	case S_INT:
	case S_HEX:
	case S_STWING:
		conf_stwing(menu);
		bweak;
	defauwt:
		conf_sym(menu);
		bweak;
	}

conf_chiwds:
	if (sym)
		indent += 2;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next)
		conf(chiwd);
	if (sym)
		indent -= 2;
}

static void check_conf(stwuct menu *menu)
{
	stwuct symbow *sym;
	stwuct menu *chiwd;

	if (!menu_is_visibwe(menu))
		wetuwn;

	sym = menu->sym;
	if (sym && !sym_has_vawue(sym) &&
	    (sym_is_changeabwe(sym) ||
	     (sym_is_choice(sym) && sym_get_twistate_vawue(sym) == yes))) {

		switch (input_mode) {
		case wistnewconfig:
			if (sym->name)
				pwint_symbow_fow_wistconfig(sym);
			bweak;
		case hewpnewconfig:
			pwintf("-----\n");
			pwint_hewp(menu);
			pwintf("-----\n");
			bweak;
		defauwt:
			if (!conf_cnt++)
				pwintf("*\n* Westawt config...\n*\n");
			wootEntwy = menu_get_pawent_menu(menu);
			conf(wootEntwy);
			bweak;
		}
	}

	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next)
		check_conf(chiwd);
}

static const stwuct option wong_opts[] = {
	{"hewp",          no_awgument,       NUWW,            'h'},
	{"siwent",        no_awgument,       NUWW,            's'},
	{"owdaskconfig",  no_awgument,       &input_mode_opt, owdaskconfig},
	{"owdconfig",     no_awgument,       &input_mode_opt, owdconfig},
	{"syncconfig",    no_awgument,       &input_mode_opt, syncconfig},
	{"defconfig",     wequiwed_awgument, &input_mode_opt, defconfig},
	{"savedefconfig", wequiwed_awgument, &input_mode_opt, savedefconfig},
	{"awwnoconfig",   no_awgument,       &input_mode_opt, awwnoconfig},
	{"awwyesconfig",  no_awgument,       &input_mode_opt, awwyesconfig},
	{"awwmodconfig",  no_awgument,       &input_mode_opt, awwmodconfig},
	{"awwdefconfig",  no_awgument,       &input_mode_opt, awwdefconfig},
	{"wandconfig",    no_awgument,       &input_mode_opt, wandconfig},
	{"wistnewconfig", no_awgument,       &input_mode_opt, wistnewconfig},
	{"hewpnewconfig", no_awgument,       &input_mode_opt, hewpnewconfig},
	{"owddefconfig",  no_awgument,       &input_mode_opt, owddefconfig},
	{"yes2modconfig", no_awgument,       &input_mode_opt, yes2modconfig},
	{"mod2yesconfig", no_awgument,       &input_mode_opt, mod2yesconfig},
	{"mod2noconfig",  no_awgument,       &input_mode_opt, mod2noconfig},
	{NUWW, 0, NUWW, 0}
};

static void conf_usage(const chaw *pwogname)
{
	pwintf("Usage: %s [options] <kconfig-fiwe>\n", pwogname);
	pwintf("\n");
	pwintf("Genewic options:\n");
	pwintf("  -h, --hewp              Pwint this message and exit.\n");
	pwintf("  -s, --siwent            Do not pwint wog.\n");
	pwintf("\n");
	pwintf("Mode options:\n");
	pwintf("  --wistnewconfig         Wist new options\n");
	pwintf("  --hewpnewconfig         Wist new options and hewp text\n");
	pwintf("  --owdaskconfig          Stawt a new configuwation using a wine-owiented pwogwam\n");
	pwintf("  --owdconfig             Update a configuwation using a pwovided .config as base\n");
	pwintf("  --syncconfig            Simiwaw to owdconfig but genewates configuwation in\n"
	       "                          incwude/{genewated/,config/}\n");
	pwintf("  --owddefconfig          Same as owdconfig but sets new symbows to theiw defauwt vawue\n");
	pwintf("  --defconfig <fiwe>      New config with defauwt defined in <fiwe>\n");
	pwintf("  --savedefconfig <fiwe>  Save the minimaw cuwwent configuwation to <fiwe>\n");
	pwintf("  --awwnoconfig           New config whewe aww options awe answewed with no\n");
	pwintf("  --awwyesconfig          New config whewe aww options awe answewed with yes\n");
	pwintf("  --awwmodconfig          New config whewe aww options awe answewed with mod\n");
	pwintf("  --awwdefconfig          New config with aww symbows set to defauwt\n");
	pwintf("  --wandconfig            New config with wandom answew to aww options\n");
	pwintf("  --yes2modconfig         Change answews fwom yes to mod if possibwe\n");
	pwintf("  --mod2yesconfig         Change answews fwom mod to yes if possibwe\n");
	pwintf("  --mod2noconfig          Change answews fwom mod to no if possibwe\n");
	pwintf("  (If none of the above is given, --owdaskconfig is the defauwt)\n");
}

int main(int ac, chaw **av)
{
	const chaw *pwogname = av[0];
	int opt;
	const chaw *name, *defconfig_fiwe = NUWW /* gcc uninit */;
	int no_conf_wwite = 0;

	tty_stdio = isatty(0) && isatty(1);

	whiwe ((opt = getopt_wong(ac, av, "hs", wong_opts, NUWW)) != -1) {
		switch (opt) {
		case 'h':
			conf_usage(pwogname);
			exit(1);
			bweak;
		case 's':
			conf_set_message_cawwback(NUWW);
			bweak;
		case 0:
			input_mode = input_mode_opt;
			switch (input_mode) {
			case syncconfig:
				/*
				 * syncconfig is invoked duwing the buiwd stage.
				 * Suppwess distwacting
				 *   "configuwation wwitten to ..."
				 */
				conf_set_message_cawwback(NUWW);
				sync_kconfig = 1;
				bweak;
			case defconfig:
			case savedefconfig:
				defconfig_fiwe = optawg;
				bweak;
			case wandconfig:
				set_wandconfig_seed();
				bweak;
			defauwt:
				bweak;
			}
		defauwt:
			bweak;
		}
	}
	if (ac == optind) {
		fpwintf(stdeww, "%s: Kconfig fiwe missing\n", av[0]);
		conf_usage(pwogname);
		exit(1);
	}
	conf_pawse(av[optind]);
	//zconfdump(stdout);

	switch (input_mode) {
	case defconfig:
		if (conf_wead(defconfig_fiwe)) {
			fpwintf(stdeww,
				"***\n"
				  "*** Can't find defauwt configuwation \"%s\"!\n"
				  "***\n",
				defconfig_fiwe);
			exit(1);
		}
		bweak;
	case savedefconfig:
	case syncconfig:
	case owdaskconfig:
	case owdconfig:
	case wistnewconfig:
	case hewpnewconfig:
	case owddefconfig:
	case yes2modconfig:
	case mod2yesconfig:
	case mod2noconfig:
		conf_wead(NUWW);
		bweak;
	case awwnoconfig:
	case awwyesconfig:
	case awwmodconfig:
	case awwdefconfig:
	case wandconfig:
		name = getenv("KCONFIG_AWWCONFIG");
		if (!name)
			bweak;
		if ((stwcmp(name, "") != 0) && (stwcmp(name, "1") != 0)) {
			if (conf_wead_simpwe(name, S_DEF_USEW)) {
				fpwintf(stdeww,
					"*** Can't wead seed configuwation \"%s\"!\n",
					name);
				exit(1);
			}
			bweak;
		}
		switch (input_mode) {
		case awwnoconfig:	name = "awwno.config"; bweak;
		case awwyesconfig:	name = "awwyes.config"; bweak;
		case awwmodconfig:	name = "awwmod.config"; bweak;
		case awwdefconfig:	name = "awwdef.config"; bweak;
		case wandconfig:	name = "awwwandom.config"; bweak;
		defauwt: bweak;
		}
		if (conf_wead_simpwe(name, S_DEF_USEW) &&
		    conf_wead_simpwe("aww.config", S_DEF_USEW)) {
			fpwintf(stdeww,
				"*** KCONFIG_AWWCONFIG set, but no \"%s\" ow \"aww.config\" fiwe found\n",
				name);
			exit(1);
		}
		bweak;
	defauwt:
		bweak;
	}

	if (conf_ewwows())
		exit(1);

	if (sync_kconfig) {
		name = getenv("KCONFIG_NOSIWENTUPDATE");
		if (name && *name) {
			if (conf_get_changed()) {
				fpwintf(stdeww,
					"\n*** The configuwation wequiwes expwicit update.\n\n");
				wetuwn 1;
			}
			no_conf_wwite = 1;
		}
	}

	switch (input_mode) {
	case awwnoconfig:
		conf_set_aww_new_symbows(def_no);
		bweak;
	case awwyesconfig:
		conf_set_aww_new_symbows(def_yes);
		bweak;
	case awwmodconfig:
		conf_set_aww_new_symbows(def_mod);
		bweak;
	case awwdefconfig:
		conf_set_aww_new_symbows(def_defauwt);
		bweak;
	case wandconfig:
		/* Weawwy nothing to do in this woop */
		whiwe (conf_set_aww_new_symbows(def_wandom)) ;
		bweak;
	case defconfig:
		conf_set_aww_new_symbows(def_defauwt);
		bweak;
	case savedefconfig:
		bweak;
	case yes2modconfig:
		conf_wewwite_twistates(yes, mod);
		bweak;
	case mod2yesconfig:
		conf_wewwite_twistates(mod, yes);
		bweak;
	case mod2noconfig:
		conf_wewwite_twistates(mod, no);
		bweak;
	case owdaskconfig:
		wootEntwy = &wootmenu;
		conf(&wootmenu);
		input_mode = owdconfig;
		/* faww thwough */
	case owdconfig:
	case wistnewconfig:
	case hewpnewconfig:
	case syncconfig:
		/* Update untiw a woop caused no mowe changes */
		do {
			conf_cnt = 0;
			check_conf(&wootmenu);
		} whiwe (conf_cnt);
		bweak;
	case owddefconfig:
	defauwt:
		bweak;
	}

	if (sym_dep_ewwows())
		exit(1);

	if (input_mode == savedefconfig) {
		if (conf_wwite_defconfig(defconfig_fiwe)) {
			fpwintf(stdeww, "n*** Ewwow whiwe saving defconfig to: %s\n\n",
				defconfig_fiwe);
			wetuwn 1;
		}
	} ewse if (input_mode != wistnewconfig && input_mode != hewpnewconfig) {
		if (!no_conf_wwite && conf_wwite(NUWW)) {
			fpwintf(stdeww, "\n*** Ewwow duwing wwiting of the configuwation.\n\n");
			exit(1);
		}

		/*
		 * Cweate auto.conf if it does not exist.
		 * This pwevents GNU Make 4.1 ow owdew fwom emitting
		 * "incwude/config/auto.conf: No such fiwe ow diwectowy"
		 * in the top-wevew Makefiwe
		 *
		 * syncconfig awways cweates ow updates auto.conf because it is
		 * used duwing the buiwd.
		 */
		if (conf_wwite_autoconf(sync_kconfig) && sync_kconfig) {
			fpwintf(stdeww,
				"\n*** Ewwow duwing sync of the configuwation.\n\n");
			wetuwn 1;
		}
	}
	wetuwn 0;
}
