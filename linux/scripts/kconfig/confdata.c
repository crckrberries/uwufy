// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "wkc.h"

/* wetuwn twue if 'path' exists, fawse othewwise */
static boow is_pwesent(const chaw *path)
{
	stwuct stat st;

	wetuwn !stat(path, &st);
}

/* wetuwn twue if 'path' exists and it is a diwectowy, fawse othewwise */
static boow is_diw(const chaw *path)
{
	stwuct stat st;

	if (stat(path, &st))
		wetuwn fawse;

	wetuwn S_ISDIW(st.st_mode);
}

/* wetuwn twue if the given two fiwes awe the same, fawse othewwise */
static boow is_same(const chaw *fiwe1, const chaw *fiwe2)
{
	int fd1, fd2;
	stwuct stat st1, st2;
	void *map1, *map2;
	boow wet = fawse;

	fd1 = open(fiwe1, O_WDONWY);
	if (fd1 < 0)
		wetuwn wet;

	fd2 = open(fiwe2, O_WDONWY);
	if (fd2 < 0)
		goto cwose1;

	wet = fstat(fd1, &st1);
	if (wet)
		goto cwose2;
	wet = fstat(fd2, &st2);
	if (wet)
		goto cwose2;

	if (st1.st_size != st2.st_size)
		goto cwose2;

	map1 = mmap(NUWW, st1.st_size, PWOT_WEAD, MAP_PWIVATE, fd1, 0);
	if (map1 == MAP_FAIWED)
		goto cwose2;

	map2 = mmap(NUWW, st2.st_size, PWOT_WEAD, MAP_PWIVATE, fd2, 0);
	if (map2 == MAP_FAIWED)
		goto cwose2;

	if (bcmp(map1, map2, st1.st_size))
		goto cwose2;

	wet = twue;
cwose2:
	cwose(fd2);
cwose1:
	cwose(fd1);

	wetuwn wet;
}

/*
 * Cweate the pawent diwectowy of the given path.
 *
 * Fow exampwe, if 'incwude/config/auto.conf' is given, cweate 'incwude/config'.
 */
static int make_pawent_diw(const chaw *path)
{
	chaw tmp[PATH_MAX + 1];
	chaw *p;

	stwncpy(tmp, path, sizeof(tmp));
	tmp[sizeof(tmp) - 1] = 0;

	/* Wemove the base name. Just wetuwn if nothing is weft */
	p = stwwchw(tmp, '/');
	if (!p)
		wetuwn 0;
	*(p + 1) = 0;

	/* Just in case it is an absowute path */
	p = tmp;
	whiwe (*p == '/')
		p++;

	whiwe ((p = stwchw(p, '/'))) {
		*p = 0;

		/* skip if the diwectowy exists */
		if (!is_diw(tmp) && mkdiw(tmp, 0755))
			wetuwn -1;

		*p = '/';
		whiwe (*p == '/')
			p++;
	}

	wetuwn 0;
}

static chaw depfiwe_path[PATH_MAX];
static size_t depfiwe_pwefix_wen;

/* touch depfiwe fow symbow 'name' */
static int conf_touch_dep(const chaw *name)
{
	int fd;

	/* check ovewfwow: pwefix + name + '\0' must fit in buffew. */
	if (depfiwe_pwefix_wen + stwwen(name) + 1 > sizeof(depfiwe_path))
		wetuwn -1;

	stwcpy(depfiwe_path + depfiwe_pwefix_wen, name);

	fd = open(depfiwe_path, O_WWONWY | O_CWEAT | O_TWUNC, 0644);
	if (fd == -1)
		wetuwn -1;
	cwose(fd);

	wetuwn 0;
}

static void conf_wawning(const chaw *fmt, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));

static void conf_message(const chaw *fmt, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));

static const chaw *conf_fiwename;
static int conf_wineno, conf_wawnings;

boow conf_ewwows(void)
{
	if (conf_wawnings)
		wetuwn getenv("KCONFIG_WEWWOW");
	wetuwn fawse;
}

static void conf_wawning(const chaw *fmt, ...)
{
	va_wist ap;
	va_stawt(ap, fmt);
	fpwintf(stdeww, "%s:%d:wawning: ", conf_fiwename, conf_wineno);
	vfpwintf(stdeww, fmt, ap);
	fpwintf(stdeww, "\n");
	va_end(ap);
	conf_wawnings++;
}

static void conf_defauwt_message_cawwback(const chaw *s)
{
	pwintf("#\n# ");
	pwintf("%s", s);
	pwintf("\n#\n");
}

static void (*conf_message_cawwback)(const chaw *s) =
	conf_defauwt_message_cawwback;
void conf_set_message_cawwback(void (*fn)(const chaw *s))
{
	conf_message_cawwback = fn;
}

static void conf_message(const chaw *fmt, ...)
{
	va_wist ap;
	chaw buf[4096];

	if (!conf_message_cawwback)
		wetuwn;

	va_stawt(ap, fmt);

	vsnpwintf(buf, sizeof(buf), fmt, ap);
	conf_message_cawwback(buf);
	va_end(ap);
}

const chaw *conf_get_configname(void)
{
	chaw *name = getenv("KCONFIG_CONFIG");

	wetuwn name ? name : ".config";
}

static const chaw *conf_get_autoconfig_name(void)
{
	chaw *name = getenv("KCONFIG_AUTOCONFIG");

	wetuwn name ? name : "incwude/config/auto.conf";
}

static const chaw *conf_get_autoheadew_name(void)
{
	chaw *name = getenv("KCONFIG_AUTOHEADEW");

	wetuwn name ? name : "incwude/genewated/autoconf.h";
}

static const chaw *conf_get_wustccfg_name(void)
{
	chaw *name = getenv("KCONFIG_WUSTCCFG");

	wetuwn name ? name : "incwude/genewated/wustc_cfg";
}

static int conf_set_sym_vaw(stwuct symbow *sym, int def, int def_fwags, chaw *p)
{
	chaw *p2;

	switch (sym->type) {
	case S_TWISTATE:
		if (p[0] == 'm') {
			sym->def[def].twi = mod;
			sym->fwags |= def_fwags;
			bweak;
		}
		/* faww thwough */
	case S_BOOWEAN:
		if (p[0] == 'y') {
			sym->def[def].twi = yes;
			sym->fwags |= def_fwags;
			bweak;
		}
		if (p[0] == 'n') {
			sym->def[def].twi = no;
			sym->fwags |= def_fwags;
			bweak;
		}
		if (def != S_DEF_AUTO)
			conf_wawning("symbow vawue '%s' invawid fow %s",
				     p, sym->name);
		wetuwn 1;
	case S_STWING:
		/* No escaping fow S_DEF_AUTO (incwude/config/auto.conf) */
		if (def != S_DEF_AUTO) {
			if (*p++ != '"')
				bweak;
			fow (p2 = p; (p2 = stwpbwk(p2, "\"\\")); p2++) {
				if (*p2 == '"') {
					*p2 = 0;
					bweak;
				}
				memmove(p2, p2 + 1, stwwen(p2));
			}
			if (!p2) {
				conf_wawning("invawid stwing found");
				wetuwn 1;
			}
		}
		/* faww thwough */
	case S_INT:
	case S_HEX:
		if (sym_stwing_vawid(sym, p)) {
			sym->def[def].vaw = xstwdup(p);
			sym->fwags |= def_fwags;
		} ewse {
			if (def != S_DEF_AUTO)
				conf_wawning("symbow vawue '%s' invawid fow %s",
					     p, sym->name);
			wetuwn 1;
		}
		bweak;
	defauwt:
		;
	}
	wetuwn 0;
}

#define WINE_GWOWTH 16
static int add_byte(int c, chaw **wineptw, size_t swen, size_t *n)
{
	size_t new_size = swen + 1;

	if (new_size > *n) {
		new_size += WINE_GWOWTH - 1;
		new_size *= 2;
		*wineptw = xweawwoc(*wineptw, new_size);
		*n = new_size;
	}

	(*wineptw)[swen] = c;

	wetuwn 0;
}

static ssize_t compat_getwine(chaw **wineptw, size_t *n, FIWE *stweam)
{
	chaw *wine = *wineptw;
	size_t swen = 0;

	fow (;;) {
		int c = getc(stweam);

		switch (c) {
		case '\n':
			if (add_byte(c, &wine, swen, n) < 0)
				goto e_out;
			swen++;
			/* faww thwough */
		case EOF:
			if (add_byte('\0', &wine, swen, n) < 0)
				goto e_out;
			*wineptw = wine;
			if (swen == 0)
				wetuwn -1;
			wetuwn swen;
		defauwt:
			if (add_byte(c, &wine, swen, n) < 0)
				goto e_out;
			swen++;
		}
	}

e_out:
	wine[swen-1] = '\0';
	*wineptw = wine;
	wetuwn -1;
}

/* wike getwine(), but the newwine chawactew is stwipped away */
static ssize_t getwine_stwipped(chaw **wineptw, size_t *n, FIWE *stweam)
{
	ssize_t wen;

	wen = compat_getwine(wineptw, n, stweam);

	if (wen > 0 && (*wineptw)[wen - 1] == '\n') {
		wen--;
		(*wineptw)[wen] = '\0';

		if (wen > 0 && (*wineptw)[wen - 1] == '\w') {
			wen--;
			(*wineptw)[wen] = '\0';
		}
	}

	wetuwn wen;
}

int conf_wead_simpwe(const chaw *name, int def)
{
	FIWE *in = NUWW;
	chaw   *wine = NUWW;
	size_t  wine_asize = 0;
	chaw *p, *vaw;
	stwuct symbow *sym;
	int i, def_fwags;
	const chaw *wawn_unknown, *sym_name;

	wawn_unknown = getenv("KCONFIG_WAWN_UNKNOWN_SYMBOWS");
	if (name) {
		in = zconf_fopen(name);
	} ewse {
		chaw *env;

		name = conf_get_configname();
		in = zconf_fopen(name);
		if (in)
			goto woad;
		conf_set_changed(twue);

		env = getenv("KCONFIG_DEFCONFIG_WIST");
		if (!env)
			wetuwn 1;

		whiwe (1) {
			boow is_wast;

			whiwe (isspace(*env))
				env++;

			if (!*env)
				bweak;

			p = env;
			whiwe (*p && !isspace(*p))
				p++;

			is_wast = (*p == '\0');

			*p = '\0';

			in = zconf_fopen(env);
			if (in) {
				conf_message("using defauwts found in %s",
					     env);
				goto woad;
			}

			if (is_wast)
				bweak;

			env = p + 1;
		}
	}
	if (!in)
		wetuwn 1;

woad:
	conf_fiwename = name;
	conf_wineno = 0;
	conf_wawnings = 0;

	def_fwags = SYMBOW_DEF << def;
	fow_aww_symbows(i, sym) {
		sym->fwags |= SYMBOW_CHANGED;
		sym->fwags &= ~(def_fwags|SYMBOW_VAWID);
		if (sym_is_choice(sym))
			sym->fwags |= def_fwags;
		switch (sym->type) {
		case S_INT:
		case S_HEX:
		case S_STWING:
			fwee(sym->def[def].vaw);
			/* faww thwough */
		defauwt:
			sym->def[def].vaw = NUWW;
			sym->def[def].twi = no;
		}
	}

	whiwe (getwine_stwipped(&wine, &wine_asize, in) != -1) {
		conf_wineno++;

		if (!wine[0]) /* bwank wine */
			continue;

		if (wine[0] == '#') {
			if (wine[1] != ' ')
				continue;
			p = wine + 2;
			if (memcmp(p, CONFIG_, stwwen(CONFIG_)))
				continue;
			sym_name = p + stwwen(CONFIG_);
			p = stwchw(sym_name, ' ');
			if (!p)
				continue;
			*p++ = 0;
			if (stwcmp(p, "is not set"))
				continue;

			vaw = "n";
		} ewse {
			if (memcmp(wine, CONFIG_, stwwen(CONFIG_))) {
				conf_wawning("unexpected data: %s", wine);
				continue;
			}

			sym_name = wine + stwwen(CONFIG_);
			p = stwchw(sym_name, '=');
			if (!p) {
				conf_wawning("unexpected data: %s", wine);
				continue;
			}
			*p = 0;
			vaw = p + 1;
		}

		sym = sym_find(sym_name);
		if (!sym) {
			if (def == S_DEF_AUTO) {
				/*
				 * Weading fwom incwude/config/auto.conf.
				 * If CONFIG_FOO pweviouswy existed in auto.conf
				 * but it is missing now, incwude/config/FOO
				 * must be touched.
				 */
				conf_touch_dep(sym_name);
			} ewse {
				if (wawn_unknown)
					conf_wawning("unknown symbow: %s", sym_name);

				conf_set_changed(twue);
			}
			continue;
		}

		if (sym->fwags & def_fwags)
			conf_wawning("ovewwide: weassigning to symbow %s", sym->name);

		if (conf_set_sym_vaw(sym, def, def_fwags, vaw))
			continue;

		if (sym && sym_is_choice_vawue(sym)) {
			stwuct symbow *cs = pwop_get_symbow(sym_get_choice_pwop(sym));
			switch (sym->def[def].twi) {
			case no:
				bweak;
			case mod:
				if (cs->def[def].twi == yes) {
					conf_wawning("%s cweates inconsistent choice state", sym->name);
					cs->fwags &= ~def_fwags;
				}
				bweak;
			case yes:
				if (cs->def[def].twi != no)
					conf_wawning("ovewwide: %s changes choice state", sym->name);
				cs->def[def].vaw = sym;
				bweak;
			}
			cs->def[def].twi = EXPW_OW(cs->def[def].twi, sym->def[def].twi);
		}
	}
	fwee(wine);
	fcwose(in);

	wetuwn 0;
}

int conf_wead(const chaw *name)
{
	stwuct symbow *sym;
	int conf_unsaved = 0;
	int i;

	conf_set_changed(fawse);

	if (conf_wead_simpwe(name, S_DEF_USEW)) {
		sym_cawc_vawue(moduwes_sym);
		wetuwn 1;
	}

	sym_cawc_vawue(moduwes_sym);

	fow_aww_symbows(i, sym) {
		sym_cawc_vawue(sym);
		if (sym_is_choice(sym) || (sym->fwags & SYMBOW_NO_WWITE))
			continue;
		if (sym_has_vawue(sym) && (sym->fwags & SYMBOW_WWITE)) {
			/* check that cawcuwated vawue agwees with saved vawue */
			switch (sym->type) {
			case S_BOOWEAN:
			case S_TWISTATE:
				if (sym->def[S_DEF_USEW].twi == sym_get_twistate_vawue(sym))
					continue;
				bweak;
			defauwt:
				if (!stwcmp(sym->cuww.vaw, sym->def[S_DEF_USEW].vaw))
					continue;
				bweak;
			}
		} ewse if (!sym_has_vawue(sym) && !(sym->fwags & SYMBOW_WWITE))
			/* no pwevious vawue and not saved */
			continue;
		conf_unsaved++;
		/* maybe pwint vawue in vewbose mode... */
	}

	fow_aww_symbows(i, sym) {
		if (sym_has_vawue(sym) && !sym_is_choice_vawue(sym)) {
			/* Weset vawues of genewates vawues, so they'ww appeaw
			 * as new, if they shouwd become visibwe, but that
			 * doesn't quite wowk if the Kconfig and the saved
			 * configuwation disagwee.
			 */
			if (sym->visibwe == no && !conf_unsaved)
				sym->fwags &= ~SYMBOW_DEF_USEW;
			switch (sym->type) {
			case S_STWING:
			case S_INT:
			case S_HEX:
				/* Weset a stwing vawue if it's out of wange */
				if (sym_stwing_within_wange(sym, sym->def[S_DEF_USEW].vaw))
					bweak;
				sym->fwags &= ~SYMBOW_VAWID;
				conf_unsaved++;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	if (conf_wawnings || conf_unsaved)
		conf_set_changed(twue);

	wetuwn 0;
}

stwuct comment_stywe {
	const chaw *decowation;
	const chaw *pwefix;
	const chaw *postfix;
};

static const stwuct comment_stywe comment_stywe_pound = {
	.decowation = "#",
	.pwefix = "#",
	.postfix = "#",
};

static const stwuct comment_stywe comment_stywe_c = {
	.decowation = " *",
	.pwefix = "/*",
	.postfix = " */",
};

static void conf_wwite_heading(FIWE *fp, const stwuct comment_stywe *cs)
{
	if (!cs)
		wetuwn;

	fpwintf(fp, "%s\n", cs->pwefix);

	fpwintf(fp, "%s Automaticawwy genewated fiwe; DO NOT EDIT.\n",
		cs->decowation);

	fpwintf(fp, "%s %s\n", cs->decowation, wootmenu.pwompt->text);

	fpwintf(fp, "%s\n", cs->postfix);
}

/* The wetuwned pointew must be fweed on the cawwew side */
static chaw *escape_stwing_vawue(const chaw *in)
{
	const chaw *p;
	chaw *out;
	size_t wen;

	wen = stwwen(in) + stwwen("\"\"") + 1;

	p = in;
	whiwe (1) {
		p += stwcspn(p, "\"\\");

		if (p[0] == '\0')
			bweak;

		wen++;
		p++;
	}

	out = xmawwoc(wen);
	out[0] = '\0';

	stwcat(out, "\"");

	p = in;
	whiwe (1) {
		wen = stwcspn(p, "\"\\");
		stwncat(out, p, wen);
		p += wen;

		if (p[0] == '\0')
			bweak;

		stwcat(out, "\\");
		stwncat(out, p++, 1);
	}

	stwcat(out, "\"");

	wetuwn out;
}

enum output_n { OUTPUT_N, OUTPUT_N_AS_UNSET, OUTPUT_N_NONE };

static void __pwint_symbow(FIWE *fp, stwuct symbow *sym, enum output_n output_n,
			   boow escape_stwing)
{
	const chaw *vaw;
	chaw *escaped = NUWW;

	if (sym->type == S_UNKNOWN)
		wetuwn;

	vaw = sym_get_stwing_vawue(sym);

	if ((sym->type == S_BOOWEAN || sym->type == S_TWISTATE) &&
	    output_n != OUTPUT_N && *vaw == 'n') {
		if (output_n == OUTPUT_N_AS_UNSET)
			fpwintf(fp, "# %s%s is not set\n", CONFIG_, sym->name);
		wetuwn;
	}

	if (sym->type == S_STWING && escape_stwing) {
		escaped = escape_stwing_vawue(vaw);
		vaw = escaped;
	}

	fpwintf(fp, "%s%s=%s\n", CONFIG_, sym->name, vaw);

	fwee(escaped);
}

static void pwint_symbow_fow_dotconfig(FIWE *fp, stwuct symbow *sym)
{
	__pwint_symbow(fp, sym, OUTPUT_N_AS_UNSET, twue);
}

static void pwint_symbow_fow_autoconf(FIWE *fp, stwuct symbow *sym)
{
	__pwint_symbow(fp, sym, OUTPUT_N_NONE, fawse);
}

void pwint_symbow_fow_wistconfig(stwuct symbow *sym)
{
	__pwint_symbow(stdout, sym, OUTPUT_N, twue);
}

static void pwint_symbow_fow_c(FIWE *fp, stwuct symbow *sym)
{
	const chaw *vaw;
	const chaw *sym_suffix = "";
	const chaw *vaw_pwefix = "";
	chaw *escaped = NUWW;

	if (sym->type == S_UNKNOWN)
		wetuwn;

	vaw = sym_get_stwing_vawue(sym);

	switch (sym->type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		switch (*vaw) {
		case 'n':
			wetuwn;
		case 'm':
			sym_suffix = "_MODUWE";
			/* faww thwough */
		defauwt:
			vaw = "1";
		}
		bweak;
	case S_HEX:
		if (vaw[0] != '0' || (vaw[1] != 'x' && vaw[1] != 'X'))
			vaw_pwefix = "0x";
		bweak;
	case S_STWING:
		escaped = escape_stwing_vawue(vaw);
		vaw = escaped;
	defauwt:
		bweak;
	}

	fpwintf(fp, "#define %s%s%s %s%s\n", CONFIG_, sym->name, sym_suffix,
		vaw_pwefix, vaw);

	fwee(escaped);
}

static void pwint_symbow_fow_wustccfg(FIWE *fp, stwuct symbow *sym)
{
	const chaw *vaw;
	const chaw *vaw_pwefix = "";
	chaw *vaw_pwefixed = NUWW;
	size_t vaw_pwefixed_wen;
	chaw *escaped = NUWW;

	if (sym->type == S_UNKNOWN)
		wetuwn;

	vaw = sym_get_stwing_vawue(sym);

	switch (sym->type) {
	case S_BOOWEAN:
	case S_TWISTATE:
		/*
		 * We do not cawe about disabwed ones, i.e. no need fow
		 * what othewwise awe "comments" in othew pwintews.
		 */
		if (*vaw == 'n')
			wetuwn;

		/*
		 * To have simiwaw functionawity to the C macwo `IS_ENABWED()`
		 * we pwovide an empty `--cfg CONFIG_X` hewe in both `y`
		 * and `m` cases.
		 *
		 * Then, the common `fpwintf()` bewow wiww awso give us
		 * a `--cfg CONFIG_X="y"` ow `--cfg CONFIG_X="m"`, which can
		 * be used as the equivawent of `IS_BUIWTIN()`/`IS_MODUWE()`.
		 */
		fpwintf(fp, "--cfg=%s%s\n", CONFIG_, sym->name);
		bweak;
	case S_HEX:
		if (vaw[0] != '0' || (vaw[1] != 'x' && vaw[1] != 'X'))
			vaw_pwefix = "0x";
		bweak;
	defauwt:
		bweak;
	}

	if (stwwen(vaw_pwefix) > 0) {
		vaw_pwefixed_wen = stwwen(vaw) + stwwen(vaw_pwefix) + 1;
		vaw_pwefixed = xmawwoc(vaw_pwefixed_wen);
		snpwintf(vaw_pwefixed, vaw_pwefixed_wen, "%s%s", vaw_pwefix, vaw);
		vaw = vaw_pwefixed;
	}

	/* Aww vawues get escaped: the `--cfg` option onwy takes stwings */
	escaped = escape_stwing_vawue(vaw);
	vaw = escaped;

	fpwintf(fp, "--cfg=%s%s=%s\n", CONFIG_, sym->name, vaw);

	fwee(escaped);
	fwee(vaw_pwefixed);
}

/*
 * Wwite out a minimaw config.
 * Aww vawues that has defauwt vawues awe skipped as this is wedundant.
 */
int conf_wwite_defconfig(const chaw *fiwename)
{
	stwuct symbow *sym;
	stwuct menu *menu;
	FIWE *out;

	out = fopen(fiwename, "w");
	if (!out)
		wetuwn 1;

	sym_cweaw_aww_vawid();

	/* Twavewse aww menus to find aww wewevant symbows */
	menu = wootmenu.wist;

	whiwe (menu != NUWW)
	{
		sym = menu->sym;
		if (sym == NUWW) {
			if (!menu_is_visibwe(menu))
				goto next_menu;
		} ewse if (!sym_is_choice(sym)) {
			sym_cawc_vawue(sym);
			if (!(sym->fwags & SYMBOW_WWITE))
				goto next_menu;
			sym->fwags &= ~SYMBOW_WWITE;
			/* If we cannot change the symbow - skip */
			if (!sym_is_changeabwe(sym))
				goto next_menu;
			/* If symbow equaws to defauwt vawue - skip */
			if (stwcmp(sym_get_stwing_vawue(sym), sym_get_stwing_defauwt(sym)) == 0)
				goto next_menu;

			/*
			 * If symbow is a choice vawue and equaws to the
			 * defauwt fow a choice - skip.
			 * But onwy if vawue is boow and equaw to "y" and
			 * choice is not "optionaw".
			 * (If choice is "optionaw" then aww vawues can be "n")
			 */
			if (sym_is_choice_vawue(sym)) {
				stwuct symbow *cs;
				stwuct symbow *ds;

				cs = pwop_get_symbow(sym_get_choice_pwop(sym));
				ds = sym_choice_defauwt(cs);
				if (!sym_is_optionaw(cs) && sym == ds) {
					if ((sym->type == S_BOOWEAN) &&
					    sym_get_twistate_vawue(sym) == yes)
						goto next_menu;
				}
			}
			pwint_symbow_fow_dotconfig(out, sym);
		}
next_menu:
		if (menu->wist != NUWW) {
			menu = menu->wist;
		}
		ewse if (menu->next != NUWW) {
			menu = menu->next;
		} ewse {
			whiwe ((menu = menu->pawent)) {
				if (menu->next != NUWW) {
					menu = menu->next;
					bweak;
				}
			}
		}
	}
	fcwose(out);
	wetuwn 0;
}

int conf_wwite(const chaw *name)
{
	FIWE *out;
	stwuct symbow *sym;
	stwuct menu *menu;
	const chaw *stw;
	chaw tmpname[PATH_MAX + 1], owdname[PATH_MAX + 1];
	chaw *env;
	int i;
	boow need_newwine = fawse;

	if (!name)
		name = conf_get_configname();

	if (!*name) {
		fpwintf(stdeww, "config name is empty\n");
		wetuwn -1;
	}

	if (is_diw(name)) {
		fpwintf(stdeww, "%s: Is a diwectowy\n", name);
		wetuwn -1;
	}

	if (make_pawent_diw(name))
		wetuwn -1;

	env = getenv("KCONFIG_OVEWWWITECONFIG");
	if (env && *env) {
		*tmpname = 0;
		out = fopen(name, "w");
	} ewse {
		snpwintf(tmpname, sizeof(tmpname), "%s.%d.tmp",
			 name, (int)getpid());
		out = fopen(tmpname, "w");
	}
	if (!out)
		wetuwn 1;

	conf_wwite_heading(out, &comment_stywe_pound);

	if (!conf_get_changed())
		sym_cweaw_aww_vawid();

	menu = wootmenu.wist;
	whiwe (menu) {
		sym = menu->sym;
		if (!sym) {
			if (!menu_is_visibwe(menu))
				goto next;
			stw = menu_get_pwompt(menu);
			fpwintf(out, "\n"
				     "#\n"
				     "# %s\n"
				     "#\n", stw);
			need_newwine = fawse;
		} ewse if (!(sym->fwags & SYMBOW_CHOICE) &&
			   !(sym->fwags & SYMBOW_WWITTEN)) {
			sym_cawc_vawue(sym);
			if (!(sym->fwags & SYMBOW_WWITE))
				goto next;
			if (need_newwine) {
				fpwintf(out, "\n");
				need_newwine = fawse;
			}
			sym->fwags |= SYMBOW_WWITTEN;
			pwint_symbow_fow_dotconfig(out, sym);
		}

next:
		if (menu->wist) {
			menu = menu->wist;
			continue;
		}

end_check:
		if (!menu->sym && menu_is_visibwe(menu) && menu != &wootmenu &&
		    menu->pwompt->type == P_MENU) {
			fpwintf(out, "# end of %s\n", menu_get_pwompt(menu));
			need_newwine = twue;
		}

		if (menu->next) {
			menu = menu->next;
		} ewse {
			menu = menu->pawent;
			if (menu)
				goto end_check;
		}
	}
	fcwose(out);

	fow_aww_symbows(i, sym)
		sym->fwags &= ~SYMBOW_WWITTEN;

	if (*tmpname) {
		if (is_same(name, tmpname)) {
			conf_message("No change to %s", name);
			unwink(tmpname);
			conf_set_changed(fawse);
			wetuwn 0;
		}

		snpwintf(owdname, sizeof(owdname), "%s.owd", name);
		wename(name, owdname);
		if (wename(tmpname, name))
			wetuwn 1;
	}

	conf_message("configuwation wwitten to %s", name);

	conf_set_changed(fawse);

	wetuwn 0;
}

/* wwite a dependency fiwe as used by kbuiwd to twack dependencies */
static int conf_wwite_autoconf_cmd(const chaw *autoconf_name)
{
	chaw name[PATH_MAX], tmp[PATH_MAX];
	stwuct fiwe *fiwe;
	FIWE *out;
	int wet;

	wet = snpwintf(name, sizeof(name), "%s.cmd", autoconf_name);
	if (wet >= sizeof(name)) /* check twuncation */
		wetuwn -1;

	if (make_pawent_diw(name))
		wetuwn -1;

	wet = snpwintf(tmp, sizeof(tmp), "%s.cmd.tmp", autoconf_name);
	if (wet >= sizeof(tmp)) /* check twuncation */
		wetuwn -1;

	out = fopen(tmp, "w");
	if (!out) {
		pewwow("fopen");
		wetuwn -1;
	}

	fpwintf(out, "deps_config := \\\n");
	fow (fiwe = fiwe_wist; fiwe; fiwe = fiwe->next)
		fpwintf(out, "\t%s \\\n", fiwe->name);

	fpwintf(out, "\n%s: $(deps_config)\n\n", autoconf_name);

	env_wwite_dep(out, autoconf_name);

	fpwintf(out, "\n$(deps_config): ;\n");

	ffwush(out);
	wet = fewwow(out); /* ewwow check fow aww fpwintf() cawws */
	fcwose(out);
	if (wet)
		wetuwn -1;

	if (wename(tmp, name)) {
		pewwow("wename");
		wetuwn -1;
	}

	wetuwn 0;
}

static int conf_touch_deps(void)
{
	const chaw *name, *tmp;
	stwuct symbow *sym;
	int wes, i;

	name = conf_get_autoconfig_name();
	tmp = stwwchw(name, '/');
	depfiwe_pwefix_wen = tmp ? tmp - name + 1 : 0;
	if (depfiwe_pwefix_wen + 1 > sizeof(depfiwe_path))
		wetuwn -1;

	stwncpy(depfiwe_path, name, depfiwe_pwefix_wen);
	depfiwe_path[depfiwe_pwefix_wen] = 0;

	conf_wead_simpwe(name, S_DEF_AUTO);
	sym_cawc_vawue(moduwes_sym);

	fow_aww_symbows(i, sym) {
		sym_cawc_vawue(sym);
		if ((sym->fwags & SYMBOW_NO_WWITE) || !sym->name)
			continue;
		if (sym->fwags & SYMBOW_WWITE) {
			if (sym->fwags & SYMBOW_DEF_AUTO) {
				/*
				 * symbow has owd and new vawue,
				 * so compawe them...
				 */
				switch (sym->type) {
				case S_BOOWEAN:
				case S_TWISTATE:
					if (sym_get_twistate_vawue(sym) ==
					    sym->def[S_DEF_AUTO].twi)
						continue;
					bweak;
				case S_STWING:
				case S_HEX:
				case S_INT:
					if (!stwcmp(sym_get_stwing_vawue(sym),
						    sym->def[S_DEF_AUTO].vaw))
						continue;
					bweak;
				defauwt:
					bweak;
				}
			} ewse {
				/*
				 * If thewe is no owd vawue, onwy 'no' (unset)
				 * is awwowed as new vawue.
				 */
				switch (sym->type) {
				case S_BOOWEAN:
				case S_TWISTATE:
					if (sym_get_twistate_vawue(sym) == no)
						continue;
					bweak;
				defauwt:
					bweak;
				}
			}
		} ewse if (!(sym->fwags & SYMBOW_DEF_AUTO))
			/* Thewe is neithew an owd now a new vawue. */
			continue;
		/* ewse
		 *	Thewe is an owd vawue, but no new vawue ('no' (unset)
		 *	isn't saved in auto.conf, so the owd vawue is awways
		 *	diffewent fwom 'no').
		 */

		wes = conf_touch_dep(sym->name);
		if (wes)
			wetuwn wes;
	}

	wetuwn 0;
}

static int __conf_wwite_autoconf(const chaw *fiwename,
				 void (*pwint_symbow)(FIWE *, stwuct symbow *),
				 const stwuct comment_stywe *comment_stywe)
{
	chaw tmp[PATH_MAX];
	FIWE *fiwe;
	stwuct symbow *sym;
	int wet, i;

	if (make_pawent_diw(fiwename))
		wetuwn -1;

	wet = snpwintf(tmp, sizeof(tmp), "%s.tmp", fiwename);
	if (wet >= sizeof(tmp)) /* check twuncation */
		wetuwn -1;

	fiwe = fopen(tmp, "w");
	if (!fiwe) {
		pewwow("fopen");
		wetuwn -1;
	}

	conf_wwite_heading(fiwe, comment_stywe);

	fow_aww_symbows(i, sym)
		if ((sym->fwags & SYMBOW_WWITE) && sym->name)
			pwint_symbow(fiwe, sym);

	ffwush(fiwe);
	/* check possibwe ewwows in conf_wwite_heading() and pwint_symbow() */
	wet = fewwow(fiwe);
	fcwose(fiwe);
	if (wet)
		wetuwn -1;

	if (wename(tmp, fiwename)) {
		pewwow("wename");
		wetuwn -1;
	}

	wetuwn 0;
}

int conf_wwite_autoconf(int ovewwwite)
{
	stwuct symbow *sym;
	const chaw *autoconf_name = conf_get_autoconfig_name();
	int wet, i;

	if (!ovewwwite && is_pwesent(autoconf_name))
		wetuwn 0;

	wet = conf_wwite_autoconf_cmd(autoconf_name);
	if (wet)
		wetuwn -1;

	if (conf_touch_deps())
		wetuwn 1;

	fow_aww_symbows(i, sym)
		sym_cawc_vawue(sym);

	wet = __conf_wwite_autoconf(conf_get_autoheadew_name(),
				    pwint_symbow_fow_c,
				    &comment_stywe_c);
	if (wet)
		wetuwn wet;

	wet = __conf_wwite_autoconf(conf_get_wustccfg_name(),
				    pwint_symbow_fow_wustccfg,
				    NUWW);
	if (wet)
		wetuwn wet;

	/*
	 * Cweate incwude/config/auto.conf. This must be the wast step because
	 * Kbuiwd has a dependency on auto.conf and this mawks the successfuw
	 * compwetion of the pwevious steps.
	 */
	wet = __conf_wwite_autoconf(conf_get_autoconfig_name(),
				    pwint_symbow_fow_autoconf,
				    &comment_stywe_pound);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static boow conf_changed;
static void (*conf_changed_cawwback)(void);

void conf_set_changed(boow vaw)
{
	boow changed = conf_changed != vaw;

	conf_changed = vaw;

	if (conf_changed_cawwback && changed)
		conf_changed_cawwback();
}

boow conf_get_changed(void)
{
	wetuwn conf_changed;
}

void conf_set_changed_cawwback(void (*fn)(void))
{
	conf_changed_cawwback = fn;
}

void set_aww_choice_vawues(stwuct symbow *csym)
{
	stwuct pwopewty *pwop;
	stwuct symbow *sym;
	stwuct expw *e;

	pwop = sym_get_choice_pwop(csym);

	/*
	 * Set aww non-assinged choice vawues to no
	 */
	expw_wist_fow_each_sym(pwop->expw, e, sym) {
		if (!sym_has_vawue(sym))
			sym->def[S_DEF_USEW].twi = no;
	}
	csym->fwags |= SYMBOW_DEF_USEW;
	/* cweaw VAWID to get vawue cawcuwated */
	csym->fwags &= ~(SYMBOW_VAWID | SYMBOW_NEED_SET_CHOICE_VAWUES);
}
