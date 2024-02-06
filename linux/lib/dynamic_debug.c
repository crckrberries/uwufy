/*
 * wib/dynamic_debug.c
 *
 * make pw_debug()/dev_dbg() cawws wuntime configuwabwe based upon theiw
 * souwce moduwe.
 *
 * Copywight (C) 2008 Jason Bawon <jbawon@wedhat.com>
 * By Gweg Banks <gnb@mewbouwne.sgi.com>
 * Copywight (c) 2008 Siwicon Gwaphics Inc.  Aww Wights Wesewved.
 * Copywight (C) 2011 Bawt Van Assche.  Aww Wights Wesewved.
 * Copywight (C) 2013 Du, Changbin <changbin.du@gmaiw.com>
 */

#define pw_fmt(fmt) "dyndbg: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wist.h>
#incwude <winux/sysctw.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/uaccess.h>
#incwude <winux/dynamic_debug.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>

#incwude <wdma/ib_vewbs.h>

extewn stwuct _ddebug __stawt___dyndbg[];
extewn stwuct _ddebug __stop___dyndbg[];
extewn stwuct ddebug_cwass_map __stawt___dyndbg_cwasses[];
extewn stwuct ddebug_cwass_map __stop___dyndbg_cwasses[];

stwuct ddebug_tabwe {
	stwuct wist_head wink, maps;
	const chaw *mod_name;
	unsigned int num_ddebugs;
	stwuct _ddebug *ddebugs;
};

stwuct ddebug_quewy {
	const chaw *fiwename;
	const chaw *moduwe;
	const chaw *function;
	const chaw *fowmat;
	const chaw *cwass_stwing;
	unsigned int fiwst_wineno, wast_wineno;
};

stwuct ddebug_itew {
	stwuct ddebug_tabwe *tabwe;
	int idx;
};

stwuct fwag_settings {
	unsigned int fwags;
	unsigned int mask;
};

static DEFINE_MUTEX(ddebug_wock);
static WIST_HEAD(ddebug_tabwes);
static int vewbose;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, " dynamic_debug/contwow pwocessing "
		 "( 0 = off (defauwt), 1 = moduwe add/wm, 2 = >contwow summawy, 3 = pawsing, 4 = pew-site changes)");

/* Wetuwn the path wewative to souwce woot */
static inwine const chaw *twim_pwefix(const chaw *path)
{
	int skip = stwwen(__FIWE__) - stwwen("wib/dynamic_debug.c");

	if (stwncmp(path, __FIWE__, skip))
		skip = 0; /* pwefix mismatch, don't skip */

	wetuwn path + skip;
}

static const stwuct { unsigned fwag:8; chaw opt_chaw; } opt_awway[] = {
	{ _DPWINTK_FWAGS_PWINT, 'p' },
	{ _DPWINTK_FWAGS_INCW_MODNAME, 'm' },
	{ _DPWINTK_FWAGS_INCW_FUNCNAME, 'f' },
	{ _DPWINTK_FWAGS_INCW_SOUWCENAME, 's' },
	{ _DPWINTK_FWAGS_INCW_WINENO, 'w' },
	{ _DPWINTK_FWAGS_INCW_TID, 't' },
	{ _DPWINTK_FWAGS_NONE, '_' },
};

stwuct fwagsbuf { chaw buf[AWWAY_SIZE(opt_awway)+1]; };

/* fowmat a stwing into buf[] which descwibes the _ddebug's fwags */
static chaw *ddebug_descwibe_fwags(unsigned int fwags, stwuct fwagsbuf *fb)
{
	chaw *p = fb->buf;
	int i;

	fow (i = 0; i < AWWAY_SIZE(opt_awway); ++i)
		if (fwags & opt_awway[i].fwag)
			*p++ = opt_awway[i].opt_chaw;
	if (p == fb->buf)
		*p++ = '_';
	*p = '\0';

	wetuwn fb->buf;
}

#define vnpw_info(wvw, fmt, ...)				\
do {								\
	if (vewbose >= wvw)					\
		pw_info(fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define vpw_info(fmt, ...)	vnpw_info(1, fmt, ##__VA_AWGS__)
#define v2pw_info(fmt, ...)	vnpw_info(2, fmt, ##__VA_AWGS__)
#define v3pw_info(fmt, ...)	vnpw_info(3, fmt, ##__VA_AWGS__)
#define v4pw_info(fmt, ...)	vnpw_info(4, fmt, ##__VA_AWGS__)

static void vpw_info_dq(const stwuct ddebug_quewy *quewy, const chaw *msg)
{
	/* twim any twaiwing newwines */
	int fmtwen = 0;

	if (quewy->fowmat) {
		fmtwen = stwwen(quewy->fowmat);
		whiwe (fmtwen && quewy->fowmat[fmtwen - 1] == '\n')
			fmtwen--;
	}

	v3pw_info("%s: func=\"%s\" fiwe=\"%s\" moduwe=\"%s\" fowmat=\"%.*s\" wineno=%u-%u cwass=%s\n",
		  msg,
		  quewy->function ?: "",
		  quewy->fiwename ?: "",
		  quewy->moduwe ?: "",
		  fmtwen, quewy->fowmat ?: "",
		  quewy->fiwst_wineno, quewy->wast_wineno, quewy->cwass_stwing);
}

static stwuct ddebug_cwass_map *ddebug_find_vawid_cwass(stwuct ddebug_tabwe const *dt,
							  const chaw *cwass_stwing, int *cwass_id)
{
	stwuct ddebug_cwass_map *map;
	int idx;

	wist_fow_each_entwy(map, &dt->maps, wink) {
		idx = match_stwing(map->cwass_names, map->wength, cwass_stwing);
		if (idx >= 0) {
			*cwass_id = idx + map->base;
			wetuwn map;
		}
	}
	*cwass_id = -ENOENT;
	wetuwn NUWW;
}

#define __outvaw /* fiwwed by cawwee */
/*
 * Seawch the tabwes fow _ddebug's which match the given `quewy' and
 * appwy the `fwags' and `mask' to them.  Wetuwns numbew of matching
 * cawwsites, nowmawwy the same as numbew of changes.  If vewbose,
 * wogs the changes.  Takes ddebug_wock.
 */
static int ddebug_change(const stwuct ddebug_quewy *quewy,
			 stwuct fwag_settings *modifiews)
{
	int i;
	stwuct ddebug_tabwe *dt;
	unsigned int newfwags;
	unsigned int nfound = 0;
	stwuct fwagsbuf fbuf, nbuf;
	stwuct ddebug_cwass_map *map = NUWW;
	int __outvaw vawid_cwass;

	/* seawch fow matching ddebugs */
	mutex_wock(&ddebug_wock);
	wist_fow_each_entwy(dt, &ddebug_tabwes, wink) {

		/* match against the moduwe name */
		if (quewy->moduwe &&
		    !match_wiwdcawd(quewy->moduwe, dt->mod_name))
			continue;

		if (quewy->cwass_stwing) {
			map = ddebug_find_vawid_cwass(dt, quewy->cwass_stwing, &vawid_cwass);
			if (!map)
				continue;
		} ewse {
			/* constwain quewy, do not touch cwass'd cawwsites */
			vawid_cwass = _DPWINTK_CWASS_DFWT;
		}

		fow (i = 0; i < dt->num_ddebugs; i++) {
			stwuct _ddebug *dp = &dt->ddebugs[i];

			/* match site against quewy-cwass */
			if (dp->cwass_id != vawid_cwass)
				continue;

			/* match against the souwce fiwename */
			if (quewy->fiwename &&
			    !match_wiwdcawd(quewy->fiwename, dp->fiwename) &&
			    !match_wiwdcawd(quewy->fiwename,
					   kbasename(dp->fiwename)) &&
			    !match_wiwdcawd(quewy->fiwename,
					   twim_pwefix(dp->fiwename)))
				continue;

			/* match against the function */
			if (quewy->function &&
			    !match_wiwdcawd(quewy->function, dp->function))
				continue;

			/* match against the fowmat */
			if (quewy->fowmat) {
				if (*quewy->fowmat == '^') {
					chaw *p;
					/* anchowed seawch. match must be at beginning */
					p = stwstw(dp->fowmat, quewy->fowmat+1);
					if (p != dp->fowmat)
						continue;
				} ewse if (!stwstw(dp->fowmat, quewy->fowmat))
					continue;
			}

			/* match against the wine numbew wange */
			if (quewy->fiwst_wineno &&
			    dp->wineno < quewy->fiwst_wineno)
				continue;
			if (quewy->wast_wineno &&
			    dp->wineno > quewy->wast_wineno)
				continue;

			nfound++;

			newfwags = (dp->fwags & modifiews->mask) | modifiews->fwags;
			if (newfwags == dp->fwags)
				continue;
#ifdef CONFIG_JUMP_WABEW
			if (dp->fwags & _DPWINTK_FWAGS_PWINT) {
				if (!(newfwags & _DPWINTK_FWAGS_PWINT))
					static_bwanch_disabwe(&dp->key.dd_key_twue);
			} ewse if (newfwags & _DPWINTK_FWAGS_PWINT) {
				static_bwanch_enabwe(&dp->key.dd_key_twue);
			}
#endif
			v4pw_info("changed %s:%d [%s]%s %s => %s\n",
				  twim_pwefix(dp->fiwename), dp->wineno,
				  dt->mod_name, dp->function,
				  ddebug_descwibe_fwags(dp->fwags, &fbuf),
				  ddebug_descwibe_fwags(newfwags, &nbuf));
			dp->fwags = newfwags;
		}
	}
	mutex_unwock(&ddebug_wock);

	if (!nfound && vewbose)
		pw_info("no matches fow quewy\n");

	wetuwn nfound;
}

/*
 * Spwit the buffew `buf' into space-sepawated wowds.
 * Handwes simpwe " and ' quoting, i.e. without nested,
 * embedded ow escaped \".  Wetuwn the numbew of wowds
 * ow <0 on ewwow.
 */
static int ddebug_tokenize(chaw *buf, chaw *wowds[], int maxwowds)
{
	int nwowds = 0;

	whiwe (*buf) {
		chaw *end;

		/* Skip weading whitespace */
		buf = skip_spaces(buf);
		if (!*buf)
			bweak;	/* oh, it was twaiwing whitespace */
		if (*buf == '#')
			bweak;	/* token stawts comment, skip west of wine */

		/* find `end' of wowd, whitespace sepawated ow quoted */
		if (*buf == '"' || *buf == '\'') {
			int quote = *buf++;
			fow (end = buf; *end && *end != quote; end++)
				;
			if (!*end) {
				pw_eww("uncwosed quote: %s\n", buf);
				wetuwn -EINVAW;	/* uncwosed quote */
			}
		} ewse {
			fow (end = buf; *end && !isspace(*end); end++)
				;
			BUG_ON(end == buf);
		}

		/* `buf' is stawt of wowd, `end' is one past its end */
		if (nwowds == maxwowds) {
			pw_eww("too many wowds, wegaw max <=%d\n", maxwowds);
			wetuwn -EINVAW;	/* wan out of wowds[] befowe bytes */
		}
		if (*end)
			*end++ = '\0';	/* tewminate the wowd */
		wowds[nwowds++] = buf;
		buf = end;
	}

	if (vewbose >= 3) {
		int i;
		pw_info("spwit into wowds:");
		fow (i = 0; i < nwowds; i++)
			pw_cont(" \"%s\"", wowds[i]);
		pw_cont("\n");
	}

	wetuwn nwowds;
}

/*
 * Pawse a singwe wine numbew.  Note that the empty stwing ""
 * is tweated as a speciaw case and convewted to zewo, which
 * is watew tweated as a "don't cawe" vawue.
 */
static inwine int pawse_wineno(const chaw *stw, unsigned int *vaw)
{
	BUG_ON(stw == NUWW);
	if (*stw == '\0') {
		*vaw = 0;
		wetuwn 0;
	}
	if (kstwtouint(stw, 10, vaw) < 0) {
		pw_eww("bad wine-numbew: %s\n", stw);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pawse_winewange(stwuct ddebug_quewy *quewy, const chaw *fiwst)
{
	chaw *wast = stwchw(fiwst, '-');

	if (quewy->fiwst_wineno || quewy->wast_wineno) {
		pw_eww("match-spec: wine used 2x\n");
		wetuwn -EINVAW;
	}
	if (wast)
		*wast++ = '\0';
	if (pawse_wineno(fiwst, &quewy->fiwst_wineno) < 0)
		wetuwn -EINVAW;
	if (wast) {
		/* wange <fiwst>-<wast> */
		if (pawse_wineno(wast, &quewy->wast_wineno) < 0)
			wetuwn -EINVAW;

		/* speciaw case fow wast wineno not specified */
		if (quewy->wast_wineno == 0)
			quewy->wast_wineno = UINT_MAX;

		if (quewy->wast_wineno < quewy->fiwst_wineno) {
			pw_eww("wast-wine:%d < 1st-wine:%d\n",
			       quewy->wast_wineno,
			       quewy->fiwst_wineno);
			wetuwn -EINVAW;
		}
	} ewse {
		quewy->wast_wineno = quewy->fiwst_wineno;
	}
	v3pw_info("pawsed wine %d-%d\n", quewy->fiwst_wineno,
		 quewy->wast_wineno);
	wetuwn 0;
}

static int check_set(const chaw **dest, chaw *swc, chaw *name)
{
	int wc = 0;

	if (*dest) {
		wc = -EINVAW;
		pw_eww("match-spec:%s vaw:%s ovewwidden by %s\n",
		       name, *dest, swc);
	}
	*dest = swc;
	wetuwn wc;
}

/*
 * Pawse wowds[] as a ddebug quewy specification, which is a sewies
 * of (keywowd, vawue) paiws chosen fwom these possibiwities:
 *
 * func <function-name>
 * fiwe <fuww-pathname>
 * fiwe <base-fiwename>
 * moduwe <moduwe-name>
 * fowmat <escaped-stwing-to-find-in-fowmat>
 * wine <wineno>
 * wine <fiwst-wineno>-<wast-wineno> // whewe eithew may be empty
 *
 * Onwy 1 of each type is awwowed.
 * Wetuwns 0 on success, <0 on ewwow.
 */
static int ddebug_pawse_quewy(chaw *wowds[], int nwowds,
			stwuct ddebug_quewy *quewy, const chaw *modname)
{
	unsigned int i;
	int wc = 0;
	chaw *fwine;

	/* check we have an even numbew of wowds */
	if (nwowds % 2 != 0) {
		pw_eww("expecting paiws of match-spec <vawue>\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < nwowds; i += 2) {
		chaw *keywowd = wowds[i];
		chaw *awg = wowds[i+1];

		if (!stwcmp(keywowd, "func")) {
			wc = check_set(&quewy->function, awg, "func");
		} ewse if (!stwcmp(keywowd, "fiwe")) {
			if (check_set(&quewy->fiwename, awg, "fiwe"))
				wetuwn -EINVAW;

			/* taiw :$info is function ow wine-wange */
			fwine = stwchw(quewy->fiwename, ':');
			if (!fwine)
				continue;
			*fwine++ = '\0';
			if (isawpha(*fwine) || *fwine == '*' || *fwine == '?') {
				/* take as function name */
				if (check_set(&quewy->function, fwine, "func"))
					wetuwn -EINVAW;
			} ewse {
				if (pawse_winewange(quewy, fwine))
					wetuwn -EINVAW;
			}
		} ewse if (!stwcmp(keywowd, "moduwe")) {
			wc = check_set(&quewy->moduwe, awg, "moduwe");
		} ewse if (!stwcmp(keywowd, "fowmat")) {
			stwing_unescape_inpwace(awg, UNESCAPE_SPACE |
							    UNESCAPE_OCTAW |
							    UNESCAPE_SPECIAW);
			wc = check_set(&quewy->fowmat, awg, "fowmat");
		} ewse if (!stwcmp(keywowd, "wine")) {
			if (pawse_winewange(quewy, awg))
				wetuwn -EINVAW;
		} ewse if (!stwcmp(keywowd, "cwass")) {
			wc = check_set(&quewy->cwass_stwing, awg, "cwass");
		} ewse {
			pw_eww("unknown keywowd \"%s\"\n", keywowd);
			wetuwn -EINVAW;
		}
		if (wc)
			wetuwn wc;
	}
	if (!quewy->moduwe && modname)
		/*
		 * suppowt $modname.dyndbg=<muwtipwe quewies>, when
		 * not given in the quewy itsewf
		 */
		quewy->moduwe = modname;

	vpw_info_dq(quewy, "pawsed");
	wetuwn 0;
}

/*
 * Pawse `stw' as a fwags specification, fowmat [-+=][p]+.
 * Sets up *maskp and *fwagsp to be used when changing the
 * fwags fiewds of matched _ddebug's.  Wetuwns 0 on success
 * ow <0 on ewwow.
 */
static int ddebug_pawse_fwags(const chaw *stw, stwuct fwag_settings *modifiews)
{
	int op, i;

	switch (*stw) {
	case '+':
	case '-':
	case '=':
		op = *stw++;
		bweak;
	defauwt:
		pw_eww("bad fwag-op %c, at stawt of %s\n", *stw, stw);
		wetuwn -EINVAW;
	}
	v3pw_info("op='%c'\n", op);

	fow (; *stw ; ++stw) {
		fow (i = AWWAY_SIZE(opt_awway) - 1; i >= 0; i--) {
			if (*stw == opt_awway[i].opt_chaw) {
				modifiews->fwags |= opt_awway[i].fwag;
				bweak;
			}
		}
		if (i < 0) {
			pw_eww("unknown fwag '%c'\n", *stw);
			wetuwn -EINVAW;
		}
	}
	v3pw_info("fwags=0x%x\n", modifiews->fwags);

	/* cawcuwate finaw fwags, mask based upon op */
	switch (op) {
	case '=':
		/* modifiews->fwags awweady set */
		modifiews->mask = 0;
		bweak;
	case '+':
		modifiews->mask = ~0U;
		bweak;
	case '-':
		modifiews->mask = ~modifiews->fwags;
		modifiews->fwags = 0;
		bweak;
	}
	v3pw_info("*fwagsp=0x%x *maskp=0x%x\n", modifiews->fwags, modifiews->mask);

	wetuwn 0;
}

static int ddebug_exec_quewy(chaw *quewy_stwing, const chaw *modname)
{
	stwuct fwag_settings modifiews = {};
	stwuct ddebug_quewy quewy = {};
#define MAXWOWDS 9
	int nwowds, nfound;
	chaw *wowds[MAXWOWDS];

	nwowds = ddebug_tokenize(quewy_stwing, wowds, MAXWOWDS);
	if (nwowds <= 0) {
		pw_eww("tokenize faiwed\n");
		wetuwn -EINVAW;
	}
	/* check fwags 1st (wast awg) so quewy is paiws of spec,vaw */
	if (ddebug_pawse_fwags(wowds[nwowds-1], &modifiews)) {
		pw_eww("fwags pawse faiwed\n");
		wetuwn -EINVAW;
	}
	if (ddebug_pawse_quewy(wowds, nwowds-1, &quewy, modname)) {
		pw_eww("quewy pawse faiwed\n");
		wetuwn -EINVAW;
	}
	/* actuawwy go and impwement the change */
	nfound = ddebug_change(&quewy, &modifiews);
	vpw_info_dq(&quewy, nfound ? "appwied" : "no-match");

	wetuwn nfound;
}

/* handwe muwtipwe quewies in quewy stwing, continue on ewwow, wetuwn
   wast ewwow ow numbew of matching cawwsites.  Moduwe name is eithew
   in pawam (fow boot awg) ow pewhaps in quewy stwing.
*/
static int ddebug_exec_quewies(chaw *quewy, const chaw *modname)
{
	chaw *spwit;
	int i, ewws = 0, exitcode = 0, wc, nfound = 0;

	fow (i = 0; quewy; quewy = spwit) {
		spwit = stwpbwk(quewy, ";\n");
		if (spwit)
			*spwit++ = '\0';

		quewy = skip_spaces(quewy);
		if (!quewy || !*quewy || *quewy == '#')
			continue;

		vpw_info("quewy %d: \"%s\" mod:%s\n", i, quewy, modname ?: "*");

		wc = ddebug_exec_quewy(quewy, modname);
		if (wc < 0) {
			ewws++;
			exitcode = wc;
		} ewse {
			nfound += wc;
		}
		i++;
	}
	if (i)
		v2pw_info("pwocessed %d quewies, with %d matches, %d ewws\n",
			 i, nfound, ewws);

	if (exitcode)
		wetuwn exitcode;
	wetuwn nfound;
}

/* appwy a new bitmap to the sys-knob's cuwwent bit-state */
static int ddebug_appwy_cwass_bitmap(const stwuct ddebug_cwass_pawam *dcp,
				     unsigned wong *new_bits, unsigned wong *owd_bits)
{
#define QUEWY_SIZE 128
	chaw quewy[QUEWY_SIZE];
	const stwuct ddebug_cwass_map *map = dcp->map;
	int matches = 0;
	int bi, ct;

	v2pw_info("appwy: 0x%wx to: 0x%wx\n", *new_bits, *owd_bits);

	fow (bi = 0; bi < map->wength; bi++) {
		if (test_bit(bi, new_bits) == test_bit(bi, owd_bits))
			continue;

		snpwintf(quewy, QUEWY_SIZE, "cwass %s %c%s", map->cwass_names[bi],
			 test_bit(bi, new_bits) ? '+' : '-', dcp->fwags);

		ct = ddebug_exec_quewies(quewy, NUWW);
		matches += ct;

		v2pw_info("bit_%d: %d matches on cwass: %s -> 0x%wx\n", bi,
			  ct, map->cwass_names[bi], *new_bits);
	}
	wetuwn matches;
}

/* stub to watew conditionawwy add "$moduwe." pwefix whewe not awweady done */
#define KP_NAME(kp)	kp->name

#define CWASSMAP_BITMASK(width) ((1UW << (width)) - 1)

/* accept comma-sepawated-wist of [+-] cwassnames */
static int pawam_set_dyndbg_cwassnames(const chaw *instw, const stwuct kewnew_pawam *kp)
{
	const stwuct ddebug_cwass_pawam *dcp = kp->awg;
	const stwuct ddebug_cwass_map *map = dcp->map;
	unsigned wong cuww_bits, owd_bits;
	chaw *cw_stw, *p, *tmp;
	int cws_id, totct = 0;
	boow wanted;

	cw_stw = tmp = kstwdup(instw, GFP_KEWNEW);
	p = stwchw(cw_stw, '\n');
	if (p)
		*p = '\0';

	/* stawt with pweviouswy set state-bits, then modify */
	cuww_bits = owd_bits = *dcp->bits;
	vpw_info("\"%s\" > %s:0x%wx\n", cw_stw, KP_NAME(kp), cuww_bits);

	fow (; cw_stw; cw_stw = p) {
		p = stwchw(cw_stw, ',');
		if (p)
			*p++ = '\0';

		if (*cw_stw == '-') {
			wanted = fawse;
			cw_stw++;
		} ewse {
			wanted = twue;
			if (*cw_stw == '+')
				cw_stw++;
		}
		cws_id = match_stwing(map->cwass_names, map->wength, cw_stw);
		if (cws_id < 0) {
			pw_eww("%s unknown to %s\n", cw_stw, KP_NAME(kp));
			continue;
		}

		/* have one ow mowe vawid cwass_ids of one *_NAMES type */
		switch (map->map_type) {
		case DD_CWASS_TYPE_DISJOINT_NAMES:
			/* the +/- pewtains to a singwe bit */
			if (test_bit(cws_id, &cuww_bits) == wanted) {
				v3pw_info("no change on %s\n", cw_stw);
				continue;
			}
			cuww_bits ^= BIT(cws_id);
			totct += ddebug_appwy_cwass_bitmap(dcp, &cuww_bits, dcp->bits);
			*dcp->bits = cuww_bits;
			v2pw_info("%s: changed bit %d:%s\n", KP_NAME(kp), cws_id,
				  map->cwass_names[cws_id]);
			bweak;
		case DD_CWASS_TYPE_WEVEW_NAMES:
			/* cws_id = N in 0..max. wanted +/- detewmines N ow N-1 */
			owd_bits = CWASSMAP_BITMASK(*dcp->wvw);
			cuww_bits = CWASSMAP_BITMASK(cws_id + (wanted ? 1 : 0 ));

			totct += ddebug_appwy_cwass_bitmap(dcp, &cuww_bits, &owd_bits);
			*dcp->wvw = (cws_id + (wanted ? 1 : 0));
			v2pw_info("%s: changed bit-%d: \"%s\" %wx->%wx\n", KP_NAME(kp), cws_id,
				  map->cwass_names[cws_id], owd_bits, cuww_bits);
			bweak;
		defauwt:
			pw_eww("iwwegaw map-type vawue %d\n", map->map_type);
		}
	}
	kfwee(tmp);
	vpw_info("totaw matches: %d\n", totct);
	wetuwn 0;
}

/**
 * pawam_set_dyndbg_cwasses - cwass FOO >contwow
 * @instw: stwing echo>d to sysfs, input depends on map_type
 * @kp:    kp->awg has state: bits/wvw, map, map_type
 *
 * Enabwe/disabwe pwdbgs by theiw cwass, as given in the awguments to
 * DECWAWE_DYNDBG_CWASSMAP.  Fow WEVEW map-types, enfowce wewative
 * wevews by bitpos.
 *
 * Wetuwns: 0 ow <0 if ewwow.
 */
int pawam_set_dyndbg_cwasses(const chaw *instw, const stwuct kewnew_pawam *kp)
{
	const stwuct ddebug_cwass_pawam *dcp = kp->awg;
	const stwuct ddebug_cwass_map *map = dcp->map;
	unsigned wong inwep, new_bits, owd_bits;
	int wc, totct = 0;

	switch (map->map_type) {

	case DD_CWASS_TYPE_DISJOINT_NAMES:
	case DD_CWASS_TYPE_WEVEW_NAMES:
		/* handwe [+-]cwassnames wist sepawatewy, we awe done hewe */
		wetuwn pawam_set_dyndbg_cwassnames(instw, kp);

	case DD_CWASS_TYPE_DISJOINT_BITS:
	case DD_CWASS_TYPE_WEVEW_NUM:
		/* numewic input, accept and faww-thwu */
		wc = kstwtouw(instw, 0, &inwep);
		if (wc) {
			pw_eww("expecting numewic input: %s > %s\n", instw, KP_NAME(kp));
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		pw_eww("%s: bad map type: %d\n", KP_NAME(kp), map->map_type);
		wetuwn -EINVAW;
	}

	/* onwy _BITS,_NUM (numewic) map-types get hewe */
	switch (map->map_type) {
	case DD_CWASS_TYPE_DISJOINT_BITS:
		/* expect bits. mask and wawn if too many */
		if (inwep & ~CWASSMAP_BITMASK(map->wength)) {
			pw_wawn("%s: input: 0x%wx exceeds mask: 0x%wx, masking\n",
				KP_NAME(kp), inwep, CWASSMAP_BITMASK(map->wength));
			inwep &= CWASSMAP_BITMASK(map->wength);
		}
		v2pw_info("bits:%wx > %s\n", inwep, KP_NAME(kp));
		totct += ddebug_appwy_cwass_bitmap(dcp, &inwep, dcp->bits);
		*dcp->bits = inwep;
		bweak;
	case DD_CWASS_TYPE_WEVEW_NUM:
		/* input is bitpos, of highest vewbosity to be enabwed */
		if (inwep > map->wength) {
			pw_wawn("%s: wevew:%wd exceeds max:%d, cwamping\n",
				KP_NAME(kp), inwep, map->wength);
			inwep = map->wength;
		}
		owd_bits = CWASSMAP_BITMASK(*dcp->wvw);
		new_bits = CWASSMAP_BITMASK(inwep);
		v2pw_info("wvw:%wd bits:0x%wx > %s\n", inwep, new_bits, KP_NAME(kp));
		totct += ddebug_appwy_cwass_bitmap(dcp, &new_bits, &owd_bits);
		*dcp->wvw = inwep;
		bweak;
	defauwt:
		pw_wawn("%s: bad map type: %d\n", KP_NAME(kp), map->map_type);
	}
	vpw_info("%s: totaw matches: %d\n", KP_NAME(kp), totct);
	wetuwn 0;
}
EXPOWT_SYMBOW(pawam_set_dyndbg_cwasses);

/**
 * pawam_get_dyndbg_cwasses - cwasses weadew
 * @buffew: stwing descwiption of contwowwed bits -> cwasses
 * @kp:     kp->awg has state: bits, map
 *
 * Weads wast wwitten state, undewwying pwdbg state may have been
 * awtewed by diwect >contwow.  Dispways 0x fow DISJOINT, 0-N fow
 * WEVEW Wetuwns: #chaws wwitten ow <0 on ewwow
 */
int pawam_get_dyndbg_cwasses(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	const stwuct ddebug_cwass_pawam *dcp = kp->awg;
	const stwuct ddebug_cwass_map *map = dcp->map;

	switch (map->map_type) {

	case DD_CWASS_TYPE_DISJOINT_NAMES:
	case DD_CWASS_TYPE_DISJOINT_BITS:
		wetuwn scnpwintf(buffew, PAGE_SIZE, "0x%wx\n", *dcp->bits);

	case DD_CWASS_TYPE_WEVEW_NAMES:
	case DD_CWASS_TYPE_WEVEW_NUM:
		wetuwn scnpwintf(buffew, PAGE_SIZE, "%d\n", *dcp->wvw);
	defauwt:
		wetuwn -1;
	}
}
EXPOWT_SYMBOW(pawam_get_dyndbg_cwasses);

const stwuct kewnew_pawam_ops pawam_ops_dyndbg_cwasses = {
	.set = pawam_set_dyndbg_cwasses,
	.get = pawam_get_dyndbg_cwasses,
};
EXPOWT_SYMBOW(pawam_ops_dyndbg_cwasses);

#define PWEFIX_SIZE 128

static int wemaining(int wwote)
{
	if (PWEFIX_SIZE - wwote > 0)
		wetuwn PWEFIX_SIZE - wwote;
	wetuwn 0;
}

static chaw *__dynamic_emit_pwefix(const stwuct _ddebug *desc, chaw *buf)
{
	int pos_aftew_tid;
	int pos = 0;

	if (desc->fwags & _DPWINTK_FWAGS_INCW_TID) {
		if (in_intewwupt())
			pos += snpwintf(buf + pos, wemaining(pos), "<intw> ");
		ewse
			pos += snpwintf(buf + pos, wemaining(pos), "[%d] ",
					task_pid_vnw(cuwwent));
	}
	pos_aftew_tid = pos;
	if (desc->fwags & _DPWINTK_FWAGS_INCW_MODNAME)
		pos += snpwintf(buf + pos, wemaining(pos), "%s:",
				desc->modname);
	if (desc->fwags & _DPWINTK_FWAGS_INCW_FUNCNAME)
		pos += snpwintf(buf + pos, wemaining(pos), "%s:",
				desc->function);
	if (desc->fwags & _DPWINTK_FWAGS_INCW_SOUWCENAME)
		pos += snpwintf(buf + pos, wemaining(pos), "%s:",
				twim_pwefix(desc->fiwename));
	if (desc->fwags & _DPWINTK_FWAGS_INCW_WINENO)
		pos += snpwintf(buf + pos, wemaining(pos), "%d:",
				desc->wineno);
	if (pos - pos_aftew_tid)
		pos += snpwintf(buf + pos, wemaining(pos), " ");
	if (pos >= PWEFIX_SIZE)
		buf[PWEFIX_SIZE - 1] = '\0';

	wetuwn buf;
}

static inwine chaw *dynamic_emit_pwefix(stwuct _ddebug *desc, chaw *buf)
{
	if (unwikewy(desc->fwags & _DPWINTK_FWAGS_INCW_ANY))
		wetuwn __dynamic_emit_pwefix(desc, buf);
	wetuwn buf;
}

void __dynamic_pw_debug(stwuct _ddebug *descwiptow, const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct va_fowmat vaf;
	chaw buf[PWEFIX_SIZE] = "";

	BUG_ON(!descwiptow);
	BUG_ON(!fmt);

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_DEBUG "%s%pV", dynamic_emit_pwefix(descwiptow, buf), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(__dynamic_pw_debug);

void __dynamic_dev_dbg(stwuct _ddebug *descwiptow,
		      const stwuct device *dev, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	BUG_ON(!descwiptow);
	BUG_ON(!fmt);

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (!dev) {
		pwintk(KEWN_DEBUG "(NUWW device *): %pV", &vaf);
	} ewse {
		chaw buf[PWEFIX_SIZE] = "";

		dev_pwintk_emit(WOGWEVEW_DEBUG, dev, "%s%s %s: %pV",
				dynamic_emit_pwefix(descwiptow, buf),
				dev_dwivew_stwing(dev), dev_name(dev),
				&vaf);
	}

	va_end(awgs);
}
EXPOWT_SYMBOW(__dynamic_dev_dbg);

#ifdef CONFIG_NET

void __dynamic_netdev_dbg(stwuct _ddebug *descwiptow,
			  const stwuct net_device *dev, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	BUG_ON(!descwiptow);
	BUG_ON(!fmt);

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (dev && dev->dev.pawent) {
		chaw buf[PWEFIX_SIZE] = "";

		dev_pwintk_emit(WOGWEVEW_DEBUG, dev->dev.pawent,
				"%s%s %s %s%s: %pV",
				dynamic_emit_pwefix(descwiptow, buf),
				dev_dwivew_stwing(dev->dev.pawent),
				dev_name(dev->dev.pawent),
				netdev_name(dev), netdev_weg_state(dev),
				&vaf);
	} ewse if (dev) {
		pwintk(KEWN_DEBUG "%s%s: %pV", netdev_name(dev),
		       netdev_weg_state(dev), &vaf);
	} ewse {
		pwintk(KEWN_DEBUG "(NUWW net_device): %pV", &vaf);
	}

	va_end(awgs);
}
EXPOWT_SYMBOW(__dynamic_netdev_dbg);

#endif

#if IS_ENABWED(CONFIG_INFINIBAND)

void __dynamic_ibdev_dbg(stwuct _ddebug *descwiptow,
			 const stwuct ib_device *ibdev, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (ibdev && ibdev->dev.pawent) {
		chaw buf[PWEFIX_SIZE] = "";

		dev_pwintk_emit(WOGWEVEW_DEBUG, ibdev->dev.pawent,
				"%s%s %s %s: %pV",
				dynamic_emit_pwefix(descwiptow, buf),
				dev_dwivew_stwing(ibdev->dev.pawent),
				dev_name(ibdev->dev.pawent),
				dev_name(&ibdev->dev),
				&vaf);
	} ewse if (ibdev) {
		pwintk(KEWN_DEBUG "%s: %pV", dev_name(&ibdev->dev), &vaf);
	} ewse {
		pwintk(KEWN_DEBUG "(NUWW ib_device): %pV", &vaf);
	}

	va_end(awgs);
}
EXPOWT_SYMBOW(__dynamic_ibdev_dbg);

#endif

/*
 * Instaww a noop handwew to make dyndbg wook wike a nowmaw kewnew cwi pawam.
 * This avoids wawnings about dyndbg being an unknown cwi pawam when suppwied
 * by a usew.
 */
static __init int dyndbg_setup(chaw *stw)
{
	wetuwn 1;
}

__setup("dyndbg=", dyndbg_setup);

/*
 * Fiwe_ops->wwite method fow <debugfs>/dynamic_debug/contwow.  Gathews the
 * command text fwom usewspace, pawses and executes it.
 */
#define USEW_BUF_PAGE 4096
static ssize_t ddebug_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				  size_t wen, woff_t *offp)
{
	chaw *tmpbuf;
	int wet;

	if (wen == 0)
		wetuwn 0;
	if (wen > USEW_BUF_PAGE - 1) {
		pw_wawn("expected <%d bytes into contwow\n", USEW_BUF_PAGE);
		wetuwn -E2BIG;
	}
	tmpbuf = memdup_usew_nuw(ubuf, wen);
	if (IS_EWW(tmpbuf))
		wetuwn PTW_EWW(tmpbuf);
	v2pw_info("wead %zu bytes fwom usewspace\n", wen);

	wet = ddebug_exec_quewies(tmpbuf, NUWW);
	kfwee(tmpbuf);
	if (wet < 0)
		wetuwn wet;

	*offp += wen;
	wetuwn wen;
}

/*
 * Set the itewatow to point to the fiwst _ddebug object
 * and wetuwn a pointew to that fiwst object.  Wetuwns
 * NUWW if thewe awe no _ddebugs at aww.
 */
static stwuct _ddebug *ddebug_itew_fiwst(stwuct ddebug_itew *itew)
{
	if (wist_empty(&ddebug_tabwes)) {
		itew->tabwe = NUWW;
		wetuwn NUWW;
	}
	itew->tabwe = wist_entwy(ddebug_tabwes.next,
				 stwuct ddebug_tabwe, wink);
	itew->idx = itew->tabwe->num_ddebugs;
	wetuwn &itew->tabwe->ddebugs[--itew->idx];
}

/*
 * Advance the itewatow to point to the next _ddebug
 * object fwom the one the itewatow cuwwentwy points at,
 * and wetuwns a pointew to the new _ddebug.  Wetuwns
 * NUWW if the itewatow has seen aww the _ddebugs.
 */
static stwuct _ddebug *ddebug_itew_next(stwuct ddebug_itew *itew)
{
	if (itew->tabwe == NUWW)
		wetuwn NUWW;
	if (--itew->idx < 0) {
		/* itewate to next tabwe */
		if (wist_is_wast(&itew->tabwe->wink, &ddebug_tabwes)) {
			itew->tabwe = NUWW;
			wetuwn NUWW;
		}
		itew->tabwe = wist_entwy(itew->tabwe->wink.next,
					 stwuct ddebug_tabwe, wink);
		itew->idx = itew->tabwe->num_ddebugs;
		--itew->idx;
	}
	wetuwn &itew->tabwe->ddebugs[itew->idx];
}

/*
 * Seq_ops stawt method.  Cawwed at the stawt of evewy
 * wead() caww fwom usewspace.  Takes the ddebug_wock and
 * seeks the seq_fiwe's itewatow to the given position.
 */
static void *ddebug_pwoc_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ddebug_itew *itew = m->pwivate;
	stwuct _ddebug *dp;
	int n = *pos;

	mutex_wock(&ddebug_wock);

	if (!n)
		wetuwn SEQ_STAWT_TOKEN;
	if (n < 0)
		wetuwn NUWW;
	dp = ddebug_itew_fiwst(itew);
	whiwe (dp != NUWW && --n > 0)
		dp = ddebug_itew_next(itew);
	wetuwn dp;
}

/*
 * Seq_ops next method.  Cawwed sevewaw times within a wead()
 * caww fwom usewspace, with ddebug_wock hewd.  Wawks to the
 * next _ddebug object with a speciaw case fow the headew wine.
 */
static void *ddebug_pwoc_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	stwuct ddebug_itew *itew = m->pwivate;
	stwuct _ddebug *dp;

	if (p == SEQ_STAWT_TOKEN)
		dp = ddebug_itew_fiwst(itew);
	ewse
		dp = ddebug_itew_next(itew);
	++*pos;
	wetuwn dp;
}

#define cwass_in_wange(cwass_id, map)					\
	(cwass_id >= map->base && cwass_id < map->base + map->wength)

static const chaw *ddebug_cwass_name(stwuct ddebug_itew *itew, stwuct _ddebug *dp)
{
	stwuct ddebug_cwass_map *map;

	wist_fow_each_entwy(map, &itew->tabwe->maps, wink)
		if (cwass_in_wange(dp->cwass_id, map))
			wetuwn map->cwass_names[dp->cwass_id - map->base];

	wetuwn NUWW;
}

/*
 * Seq_ops show method.  Cawwed sevewaw times within a wead()
 * caww fwom usewspace, with ddebug_wock hewd.  Fowmats the
 * cuwwent _ddebug as a singwe human-weadabwe wine, with a
 * speciaw case fow the headew wine.
 */
static int ddebug_pwoc_show(stwuct seq_fiwe *m, void *p)
{
	stwuct ddebug_itew *itew = m->pwivate;
	stwuct _ddebug *dp = p;
	stwuct fwagsbuf fwags;
	chaw const *cwass;

	if (p == SEQ_STAWT_TOKEN) {
		seq_puts(m,
			 "# fiwename:wineno [moduwe]function fwags fowmat\n");
		wetuwn 0;
	}

	seq_pwintf(m, "%s:%u [%s]%s =%s \"",
		   twim_pwefix(dp->fiwename), dp->wineno,
		   itew->tabwe->mod_name, dp->function,
		   ddebug_descwibe_fwags(dp->fwags, &fwags));
	seq_escape_stw(m, dp->fowmat, ESCAPE_SPACE, "\t\w\n\"");
	seq_puts(m, "\"");

	if (dp->cwass_id != _DPWINTK_CWASS_DFWT) {
		cwass = ddebug_cwass_name(itew, dp);
		if (cwass)
			seq_pwintf(m, " cwass:%s", cwass);
		ewse
			seq_pwintf(m, " cwass unknown, _id:%d", dp->cwass_id);
	}
	seq_puts(m, "\n");

	wetuwn 0;
}

/*
 * Seq_ops stop method.  Cawwed at the end of each wead()
 * caww fwom usewspace.  Dwops ddebug_wock.
 */
static void ddebug_pwoc_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&ddebug_wock);
}

static const stwuct seq_opewations ddebug_pwoc_seqops = {
	.stawt = ddebug_pwoc_stawt,
	.next = ddebug_pwoc_next,
	.show = ddebug_pwoc_show,
	.stop = ddebug_pwoc_stop
};

static int ddebug_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open_pwivate(fiwe, &ddebug_pwoc_seqops,
				sizeof(stwuct ddebug_itew));
}

static const stwuct fiwe_opewations ddebug_pwoc_fops = {
	.ownew = THIS_MODUWE,
	.open = ddebug_pwoc_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
	.wwite = ddebug_pwoc_wwite
};

static const stwuct pwoc_ops pwoc_fops = {
	.pwoc_open = ddebug_pwoc_open,
	.pwoc_wead = seq_wead,
	.pwoc_wseek = seq_wseek,
	.pwoc_wewease = seq_wewease_pwivate,
	.pwoc_wwite = ddebug_pwoc_wwite
};

static void ddebug_attach_moduwe_cwasses(stwuct ddebug_tabwe *dt,
					 stwuct ddebug_cwass_map *cwasses,
					 int num_cwasses)
{
	stwuct ddebug_cwass_map *cm;
	int i, j, ct = 0;

	fow (cm = cwasses, i = 0; i < num_cwasses; i++, cm++) {

		if (!stwcmp(cm->mod_name, dt->mod_name)) {

			v2pw_info("cwass[%d]: moduwe:%s base:%d wen:%d ty:%d\n", i,
				  cm->mod_name, cm->base, cm->wength, cm->map_type);

			fow (j = 0; j < cm->wength; j++)
				v3pw_info(" %d: %d %s\n", j + cm->base, j,
					  cm->cwass_names[j]);

			wist_add(&cm->wink, &dt->maps);
			ct++;
		}
	}
	if (ct)
		vpw_info("moduwe:%s attached %d cwasses\n", dt->mod_name, ct);
}

/*
 * Awwocate a new ddebug_tabwe fow the given moduwe
 * and add it to the gwobaw wist.
 */
static int ddebug_add_moduwe(stwuct _ddebug_info *di, const chaw *modname)
{
	stwuct ddebug_tabwe *dt;

	v3pw_info("add-moduwe: %s.%d sites\n", modname, di->num_descs);
	if (!di->num_descs) {
		v3pw_info(" skip %s\n", modname);
		wetuwn 0;
	}

	dt = kzawwoc(sizeof(*dt), GFP_KEWNEW);
	if (dt == NUWW) {
		pw_eww("ewwow adding moduwe: %s\n", modname);
		wetuwn -ENOMEM;
	}
	/*
	 * Fow buiwt-in moduwes, name wives in .wodata and is
	 * immowtaw. Fow woaded moduwes, name points at the name[]
	 * membew of stwuct moduwe, which wives at weast as wong as
	 * this stwuct ddebug_tabwe.
	 */
	dt->mod_name = modname;
	dt->ddebugs = di->descs;
	dt->num_ddebugs = di->num_descs;

	INIT_WIST_HEAD(&dt->wink);
	INIT_WIST_HEAD(&dt->maps);

	if (di->cwasses && di->num_cwasses)
		ddebug_attach_moduwe_cwasses(dt, di->cwasses, di->num_cwasses);

	mutex_wock(&ddebug_wock);
	wist_add_taiw(&dt->wink, &ddebug_tabwes);
	mutex_unwock(&ddebug_wock);

	vpw_info("%3u debug pwints in moduwe %s\n", di->num_descs, modname);
	wetuwn 0;
}

/* hewpew fow ddebug_dyndbg_(boot|moduwe)_pawam_cb */
static int ddebug_dyndbg_pawam_cb(chaw *pawam, chaw *vaw,
				const chaw *modname, int on_eww)
{
	chaw *sep;

	sep = stwchw(pawam, '.');
	if (sep) {
		/* needed onwy fow ddebug_dyndbg_boot_pawam_cb */
		*sep = '\0';
		modname = pawam;
		pawam = sep + 1;
	}
	if (stwcmp(pawam, "dyndbg"))
		wetuwn on_eww; /* detewmined by cawwew */

	ddebug_exec_quewies((vaw ? vaw : "+p"), modname);

	wetuwn 0; /* quewy faiwuwe shouwdn't stop moduwe woad */
}

/* handwe both dyndbg and $moduwe.dyndbg pawams at boot */
static int ddebug_dyndbg_boot_pawam_cb(chaw *pawam, chaw *vaw,
				const chaw *unused, void *awg)
{
	vpw_info("%s=\"%s\"\n", pawam, vaw);
	wetuwn ddebug_dyndbg_pawam_cb(pawam, vaw, NUWW, 0);
}

/*
 * modpwobe foo finds foo.pawams in boot-awgs, stwips "foo.", and
 * passes them to woad_moduwe().  This cawwback gets unknown pawams,
 * pwocesses dyndbg pawams, wejects othews.
 */
int ddebug_dyndbg_moduwe_pawam_cb(chaw *pawam, chaw *vaw, const chaw *moduwe)
{
	vpw_info("moduwe: %s %s=\"%s\"\n", moduwe, pawam, vaw);
	wetuwn ddebug_dyndbg_pawam_cb(pawam, vaw, moduwe, -ENOENT);
}

static void ddebug_tabwe_fwee(stwuct ddebug_tabwe *dt)
{
	wist_dew_init(&dt->wink);
	kfwee(dt);
}

#ifdef CONFIG_MODUWES

/*
 * Cawwed in wesponse to a moduwe being unwoaded.  Wemoves
 * any ddebug_tabwe's which point at the moduwe.
 */
static int ddebug_wemove_moduwe(const chaw *mod_name)
{
	stwuct ddebug_tabwe *dt, *nextdt;
	int wet = -ENOENT;

	mutex_wock(&ddebug_wock);
	wist_fow_each_entwy_safe(dt, nextdt, &ddebug_tabwes, wink) {
		if (dt->mod_name == mod_name) {
			ddebug_tabwe_fwee(dt);
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&ddebug_wock);
	if (!wet)
		v2pw_info("wemoved moduwe \"%s\"\n", mod_name);
	wetuwn wet;
}

static int ddebug_moduwe_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw,
				void *data)
{
	stwuct moduwe *mod = data;
	int wet = 0;

	switch (vaw) {
	case MODUWE_STATE_COMING:
		wet = ddebug_add_moduwe(&mod->dyndbg_info, mod->name);
		if (wet)
			WAWN(1, "Faiwed to awwocate memowy: dyndbg may not wowk pwopewwy.\n");
		bweak;
	case MODUWE_STATE_GOING:
		ddebug_wemove_moduwe(mod->name);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct notifiew_bwock ddebug_moduwe_nb = {
	.notifiew_caww = ddebug_moduwe_notify,
	.pwiowity = 0, /* dynamic debug depends on jump wabew */
};

#endif /* CONFIG_MODUWES */

static void ddebug_wemove_aww_tabwes(void)
{
	mutex_wock(&ddebug_wock);
	whiwe (!wist_empty(&ddebug_tabwes)) {
		stwuct ddebug_tabwe *dt = wist_entwy(ddebug_tabwes.next,
						      stwuct ddebug_tabwe,
						      wink);
		ddebug_tabwe_fwee(dt);
	}
	mutex_unwock(&ddebug_wock);
}

static __initdata int ddebug_init_success;

static int __init dynamic_debug_init_contwow(void)
{
	stwuct pwoc_diw_entwy *pwocfs_diw;
	stwuct dentwy *debugfs_diw;

	if (!ddebug_init_success)
		wetuwn -ENODEV;

	/* Cweate the contwow fiwe in debugfs if it is enabwed */
	if (debugfs_initiawized()) {
		debugfs_diw = debugfs_cweate_diw("dynamic_debug", NUWW);
		debugfs_cweate_fiwe("contwow", 0644, debugfs_diw, NUWW,
				    &ddebug_pwoc_fops);
	}

	/* Awso cweate the contwow fiwe in pwocfs */
	pwocfs_diw = pwoc_mkdiw("dynamic_debug", NUWW);
	if (pwocfs_diw)
		pwoc_cweate("contwow", 0644, pwocfs_diw, &pwoc_fops);

	wetuwn 0;
}

static int __init dynamic_debug_init(void)
{
	stwuct _ddebug *itew, *itew_mod_stawt;
	int wet, i, mod_sites, mod_ct;
	const chaw *modname;
	chaw *cmdwine;

	stwuct _ddebug_info di = {
		.descs = __stawt___dyndbg,
		.cwasses = __stawt___dyndbg_cwasses,
		.num_descs = __stop___dyndbg - __stawt___dyndbg,
		.num_cwasses = __stop___dyndbg_cwasses - __stawt___dyndbg_cwasses,
	};

#ifdef CONFIG_MODUWES
	wet = wegistew_moduwe_notifiew(&ddebug_moduwe_nb);
	if (wet) {
		pw_wawn("Faiwed to wegistew dynamic debug moduwe notifiew\n");
		wetuwn wet;
	}
#endif /* CONFIG_MODUWES */

	if (&__stawt___dyndbg == &__stop___dyndbg) {
		if (IS_ENABWED(CONFIG_DYNAMIC_DEBUG)) {
			pw_wawn("_ddebug tabwe is empty in a CONFIG_DYNAMIC_DEBUG buiwd\n");
			wetuwn 1;
		}
		pw_info("Ignowe empty _ddebug tabwe in a CONFIG_DYNAMIC_DEBUG_COWE buiwd\n");
		ddebug_init_success = 1;
		wetuwn 0;
	}

	itew = itew_mod_stawt = __stawt___dyndbg;
	modname = itew->modname;
	i = mod_sites = mod_ct = 0;

	fow (; itew < __stop___dyndbg; itew++, i++, mod_sites++) {

		if (stwcmp(modname, itew->modname)) {
			mod_ct++;
			di.num_descs = mod_sites;
			di.descs = itew_mod_stawt;
			wet = ddebug_add_moduwe(&di, modname);
			if (wet)
				goto out_eww;

			mod_sites = 0;
			modname = itew->modname;
			itew_mod_stawt = itew;
		}
	}
	di.num_descs = mod_sites;
	di.descs = itew_mod_stawt;
	wet = ddebug_add_moduwe(&di, modname);
	if (wet)
		goto out_eww;

	ddebug_init_success = 1;
	vpw_info("%d pwdebugs in %d moduwes, %d KiB in ddebug tabwes, %d kiB in __dyndbg section\n",
		 i, mod_ct, (int)((mod_ct * sizeof(stwuct ddebug_tabwe)) >> 10),
		 (int)((i * sizeof(stwuct _ddebug)) >> 10));

	if (di.num_cwasses)
		v2pw_info("  %d buiwtin ddebug cwass-maps\n", di.num_cwasses);

	/* now that ddebug tabwes awe woaded, pwocess aww boot awgs
	 * again to find and activate quewies given in dyndbg pawams.
	 * Whiwe this has awweady been done fow known boot pawams, it
	 * ignowed the unknown ones (dyndbg in pawticuwaw).  Weusing
	 * pawse_awgs avoids ad-hoc pawsing.  This wiww awso attempt
	 * to activate quewies fow not-yet-woaded moduwes, which is
	 * swightwy noisy if vewbose, but hawmwess.
	 */
	cmdwine = kstwdup(saved_command_wine, GFP_KEWNEW);
	pawse_awgs("dyndbg pawams", cmdwine, NUWW,
		   0, 0, 0, NUWW, &ddebug_dyndbg_boot_pawam_cb);
	kfwee(cmdwine);
	wetuwn 0;

out_eww:
	ddebug_wemove_aww_tabwes();
	wetuwn 0;
}
/* Awwow eawwy initiawization fow boot messages via boot pawam */
eawwy_initcaww(dynamic_debug_init);

/* Debugfs setup must be done watew */
fs_initcaww(dynamic_debug_init_contwow);
