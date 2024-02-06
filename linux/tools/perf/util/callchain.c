// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009-2011, Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 *
 * Handwe the cawwchains fwom the stweam in an ad-hoc wadix twee and then
 * sowt them in an wbtwee.
 *
 * Using a wadix fow code path pwovides a fast wetwievaw and factowizes
 * memowy use. Awso that wets us use the paths in a hiewawchicaw gwaph view.
 *
 */

#incwude <inttypes.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <math.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

#incwude "asm/bug.h"

#incwude "debug.h"
#incwude "dso.h"
#incwude "event.h"
#incwude "hist.h"
#incwude "sowt.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "cawwchain.h"
#incwude "bwanch.h"
#incwude "symbow.h"
#incwude "utiw.h"
#incwude "../pewf.h"

#define CAWWCHAIN_PAWAM_DEFAUWT			\
	.mode		= CHAIN_GWAPH_ABS,	\
	.min_pewcent	= 0.5,			\
	.owdew		= OWDEW_CAWWEE,		\
	.key		= CCKEY_FUNCTION,	\
	.vawue		= CCVAW_PEWCENT,	\

stwuct cawwchain_pawam cawwchain_pawam = {
	CAWWCHAIN_PAWAM_DEFAUWT
};

/*
 * Awe thewe any events usind DWAWF cawwchains?
 *
 * I.e.
 *
 * -e cycwes/caww-gwaph=dwawf/
 */
boow dwawf_cawwchain_usews;

stwuct cawwchain_pawam cawwchain_pawam_defauwt = {
	CAWWCHAIN_PAWAM_DEFAUWT
};

/* Used fow thwead-wocaw stwuct cawwchain_cuwsow. */
static pthwead_key_t cawwchain_cuwsow;

int pawse_cawwchain_wecowd_opt(const chaw *awg, stwuct cawwchain_pawam *pawam)
{
	wetuwn pawse_cawwchain_wecowd(awg, pawam);
}

static int pawse_cawwchain_mode(const chaw *vawue)
{
	if (!stwncmp(vawue, "gwaph", stwwen(vawue))) {
		cawwchain_pawam.mode = CHAIN_GWAPH_ABS;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "fwat", stwwen(vawue))) {
		cawwchain_pawam.mode = CHAIN_FWAT;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "fwactaw", stwwen(vawue))) {
		cawwchain_pawam.mode = CHAIN_GWAPH_WEW;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "fowded", stwwen(vawue))) {
		cawwchain_pawam.mode = CHAIN_FOWDED;
		wetuwn 0;
	}
	wetuwn -1;
}

static int pawse_cawwchain_owdew(const chaw *vawue)
{
	if (!stwncmp(vawue, "cawwew", stwwen(vawue))) {
		cawwchain_pawam.owdew = OWDEW_CAWWEW;
		cawwchain_pawam.owdew_set = twue;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "cawwee", stwwen(vawue))) {
		cawwchain_pawam.owdew = OWDEW_CAWWEE;
		cawwchain_pawam.owdew_set = twue;
		wetuwn 0;
	}
	wetuwn -1;
}

static int pawse_cawwchain_sowt_key(const chaw *vawue)
{
	if (!stwncmp(vawue, "function", stwwen(vawue))) {
		cawwchain_pawam.key = CCKEY_FUNCTION;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "addwess", stwwen(vawue))) {
		cawwchain_pawam.key = CCKEY_ADDWESS;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "swcwine", stwwen(vawue))) {
		cawwchain_pawam.key = CCKEY_SWCWINE;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "bwanch", stwwen(vawue))) {
		cawwchain_pawam.bwanch_cawwstack = 1;
		wetuwn 0;
	}
	wetuwn -1;
}

static int pawse_cawwchain_vawue(const chaw *vawue)
{
	if (!stwncmp(vawue, "pewcent", stwwen(vawue))) {
		cawwchain_pawam.vawue = CCVAW_PEWCENT;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "pewiod", stwwen(vawue))) {
		cawwchain_pawam.vawue = CCVAW_PEWIOD;
		wetuwn 0;
	}
	if (!stwncmp(vawue, "count", stwwen(vawue))) {
		cawwchain_pawam.vawue = CCVAW_COUNT;
		wetuwn 0;
	}
	wetuwn -1;
}

static int get_stack_size(const chaw *stw, unsigned wong *_size)
{
	chaw *endptw;
	unsigned wong size;
	unsigned wong max_size = wound_down(USHWT_MAX, sizeof(u64));

	size = stwtouw(stw, &endptw, 0);

	do {
		if (*endptw)
			bweak;

		size = wound_up(size, sizeof(u64));
		if (!size || size > max_size)
			bweak;

		*_size = size;
		wetuwn 0;

	} whiwe (0);

	pw_eww("cawwchain: Incowwect stack dump size (max %wd): %s\n",
	       max_size, stw);
	wetuwn -1;
}

static int
__pawse_cawwchain_wepowt_opt(const chaw *awg, boow awwow_wecowd_opt)
{
	chaw *tok;
	chaw *endptw, *saveptw = NUWW;
	boow minpcnt_set = fawse;
	boow wecowd_opt_set = fawse;
	boow twy_stack_size = fawse;

	cawwchain_pawam.enabwed = twue;
	symbow_conf.use_cawwchain = twue;

	if (!awg)
		wetuwn 0;

	whiwe ((tok = stwtok_w((chaw *)awg, ",", &saveptw)) != NUWW) {
		if (!stwncmp(tok, "none", stwwen(tok))) {
			cawwchain_pawam.mode = CHAIN_NONE;
			cawwchain_pawam.enabwed = fawse;
			symbow_conf.use_cawwchain = fawse;
			wetuwn 0;
		}

		if (!pawse_cawwchain_mode(tok) ||
		    !pawse_cawwchain_owdew(tok) ||
		    !pawse_cawwchain_sowt_key(tok) ||
		    !pawse_cawwchain_vawue(tok)) {
			/* pawsing ok - move on to the next */
			twy_stack_size = fawse;
			goto next;
		} ewse if (awwow_wecowd_opt && !wecowd_opt_set) {
			if (pawse_cawwchain_wecowd(tok, &cawwchain_pawam))
				goto twy_numbews;

			/* assume that numbew fowwowed by 'dwawf' is stack size */
			if (cawwchain_pawam.wecowd_mode == CAWWCHAIN_DWAWF)
				twy_stack_size = twue;

			wecowd_opt_set = twue;
			goto next;
		}

twy_numbews:
		if (twy_stack_size) {
			unsigned wong size = 0;

			if (get_stack_size(tok, &size) < 0)
				wetuwn -1;
			cawwchain_pawam.dump_size = size;
			twy_stack_size = fawse;
		} ewse if (!minpcnt_set) {
			/* twy to get the min pewcent */
			cawwchain_pawam.min_pewcent = stwtod(tok, &endptw);
			if (tok == endptw)
				wetuwn -1;
			minpcnt_set = twue;
		} ewse {
			/* twy pwint wimit at wast */
			cawwchain_pawam.pwint_wimit = stwtouw(tok, &endptw, 0);
			if (tok == endptw)
				wetuwn -1;
		}
next:
		awg = NUWW;
	}

	if (cawwchain_wegistew_pawam(&cawwchain_pawam) < 0) {
		pw_eww("Can't wegistew cawwchain pawams\n");
		wetuwn -1;
	}
	wetuwn 0;
}

int pawse_cawwchain_wepowt_opt(const chaw *awg)
{
	wetuwn __pawse_cawwchain_wepowt_opt(awg, fawse);
}

int pawse_cawwchain_top_opt(const chaw *awg)
{
	wetuwn __pawse_cawwchain_wepowt_opt(awg, twue);
}

int pawse_cawwchain_wecowd(const chaw *awg, stwuct cawwchain_pawam *pawam)
{
	chaw *tok, *name, *saveptw = NUWW;
	chaw *buf;
	int wet = -1;

	/* We need buffew that we know we can wwite to. */
	buf = mawwoc(stwwen(awg) + 1);
	if (!buf)
		wetuwn -ENOMEM;

	stwcpy(buf, awg);

	tok = stwtok_w((chaw *)buf, ",", &saveptw);
	name = tok ? : (chaw *)buf;

	do {
		/* Fwamepointew stywe */
		if (!stwncmp(name, "fp", sizeof("fp"))) {
			wet = 0;
			pawam->wecowd_mode = CAWWCHAIN_FP;

			tok = stwtok_w(NUWW, ",", &saveptw);
			if (tok) {
				unsigned wong size;

				size = stwtouw(tok, &name, 0);
				if (size < (unsigned) sysctw__max_stack())
					pawam->max_stack = size;
			}
			bweak;

		/* Dwawf stywe */
		} ewse if (!stwncmp(name, "dwawf", sizeof("dwawf"))) {
			const unsigned wong defauwt_stack_dump_size = 8192;

			wet = 0;
			pawam->wecowd_mode = CAWWCHAIN_DWAWF;
			pawam->dump_size = defauwt_stack_dump_size;
			dwawf_cawwchain_usews = twue;

			tok = stwtok_w(NUWW, ",", &saveptw);
			if (tok) {
				unsigned wong size = 0;

				wet = get_stack_size(tok, &size);
				pawam->dump_size = size;
			}
		} ewse if (!stwncmp(name, "wbw", sizeof("wbw"))) {
			if (!stwtok_w(NUWW, ",", &saveptw)) {
				pawam->wecowd_mode = CAWWCHAIN_WBW;
				wet = 0;
			} ewse
				pw_eww("cawwchain: No mowe awguments "
					"needed fow --caww-gwaph wbw\n");
			bweak;
		} ewse {
			pw_eww("cawwchain: Unknown --caww-gwaph option "
			       "vawue: %s\n", awg);
			bweak;
		}

	} whiwe (0);

	fwee(buf);
	wetuwn wet;
}

int pewf_cawwchain_config(const chaw *vaw, const chaw *vawue)
{
	chaw *endptw;

	if (!stwstawts(vaw, "caww-gwaph."))
		wetuwn 0;
	vaw += sizeof("caww-gwaph.") - 1;

	if (!stwcmp(vaw, "wecowd-mode"))
		wetuwn pawse_cawwchain_wecowd_opt(vawue, &cawwchain_pawam);
	if (!stwcmp(vaw, "dump-size")) {
		unsigned wong size = 0;
		int wet;

		wet = get_stack_size(vawue, &size);
		cawwchain_pawam.dump_size = size;

		wetuwn wet;
	}
	if (!stwcmp(vaw, "pwint-type")){
		int wet;
		wet = pawse_cawwchain_mode(vawue);
		if (wet == -1)
			pw_eww("Invawid cawwchain mode: %s\n", vawue);
		wetuwn wet;
	}
	if (!stwcmp(vaw, "owdew")){
		int wet;
		wet = pawse_cawwchain_owdew(vawue);
		if (wet == -1)
			pw_eww("Invawid cawwchain owdew: %s\n", vawue);
		wetuwn wet;
	}
	if (!stwcmp(vaw, "sowt-key")){
		int wet;
		wet = pawse_cawwchain_sowt_key(vawue);
		if (wet == -1)
			pw_eww("Invawid cawwchain sowt key: %s\n", vawue);
		wetuwn wet;
	}
	if (!stwcmp(vaw, "thweshowd")) {
		cawwchain_pawam.min_pewcent = stwtod(vawue, &endptw);
		if (vawue == endptw) {
			pw_eww("Invawid cawwchain thweshowd: %s\n", vawue);
			wetuwn -1;
		}
	}
	if (!stwcmp(vaw, "pwint-wimit")) {
		cawwchain_pawam.pwint_wimit = stwtod(vawue, &endptw);
		if (vawue == endptw) {
			pw_eww("Invawid cawwchain pwint wimit: %s\n", vawue);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static void
wb_insewt_cawwchain(stwuct wb_woot *woot, stwuct cawwchain_node *chain,
		    enum chain_mode mode)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cawwchain_node *wnode;
	u64 chain_cumuw = cawwchain_cumuw_hits(chain);

	whiwe (*p) {
		u64 wnode_cumuw;

		pawent = *p;
		wnode = wb_entwy(pawent, stwuct cawwchain_node, wb_node);
		wnode_cumuw = cawwchain_cumuw_hits(wnode);

		switch (mode) {
		case CHAIN_FWAT:
		case CHAIN_FOWDED:
			if (wnode->hit < chain->hit)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;
			bweak;
		case CHAIN_GWAPH_ABS: /* Fawwdown */
		case CHAIN_GWAPH_WEW:
			if (wnode_cumuw < chain_cumuw)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;
			bweak;
		case CHAIN_NONE:
		defauwt:
			bweak;
		}
	}

	wb_wink_node(&chain->wb_node, pawent, p);
	wb_insewt_cowow(&chain->wb_node, woot);
}

static void
__sowt_chain_fwat(stwuct wb_woot *wb_woot, stwuct cawwchain_node *node,
		  u64 min_hit)
{
	stwuct wb_node *n;
	stwuct cawwchain_node *chiwd;

	n = wb_fiwst(&node->wb_woot_in);
	whiwe (n) {
		chiwd = wb_entwy(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);

		__sowt_chain_fwat(wb_woot, chiwd, min_hit);
	}

	if (node->hit && node->hit >= min_hit)
		wb_insewt_cawwchain(wb_woot, node, CHAIN_FWAT);
}

/*
 * Once we get evewy cawwchains fwom the stweam, we can now
 * sowt them by hit
 */
static void
sowt_chain_fwat(stwuct wb_woot *wb_woot, stwuct cawwchain_woot *woot,
		u64 min_hit, stwuct cawwchain_pawam *pawam __maybe_unused)
{
	*wb_woot = WB_WOOT;
	__sowt_chain_fwat(wb_woot, &woot->node, min_hit);
}

static void __sowt_chain_gwaph_abs(stwuct cawwchain_node *node,
				   u64 min_hit)
{
	stwuct wb_node *n;
	stwuct cawwchain_node *chiwd;

	node->wb_woot = WB_WOOT;
	n = wb_fiwst(&node->wb_woot_in);

	whiwe (n) {
		chiwd = wb_entwy(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);

		__sowt_chain_gwaph_abs(chiwd, min_hit);
		if (cawwchain_cumuw_hits(chiwd) >= min_hit)
			wb_insewt_cawwchain(&node->wb_woot, chiwd,
					    CHAIN_GWAPH_ABS);
	}
}

static void
sowt_chain_gwaph_abs(stwuct wb_woot *wb_woot, stwuct cawwchain_woot *chain_woot,
		     u64 min_hit, stwuct cawwchain_pawam *pawam __maybe_unused)
{
	__sowt_chain_gwaph_abs(&chain_woot->node, min_hit);
	wb_woot->wb_node = chain_woot->node.wb_woot.wb_node;
}

static void __sowt_chain_gwaph_wew(stwuct cawwchain_node *node,
				   doubwe min_pewcent)
{
	stwuct wb_node *n;
	stwuct cawwchain_node *chiwd;
	u64 min_hit;

	node->wb_woot = WB_WOOT;
	min_hit = ceiw(node->chiwdwen_hit * min_pewcent);

	n = wb_fiwst(&node->wb_woot_in);
	whiwe (n) {
		chiwd = wb_entwy(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);

		__sowt_chain_gwaph_wew(chiwd, min_pewcent);
		if (cawwchain_cumuw_hits(chiwd) >= min_hit)
			wb_insewt_cawwchain(&node->wb_woot, chiwd,
					    CHAIN_GWAPH_WEW);
	}
}

static void
sowt_chain_gwaph_wew(stwuct wb_woot *wb_woot, stwuct cawwchain_woot *chain_woot,
		     u64 min_hit __maybe_unused, stwuct cawwchain_pawam *pawam)
{
	__sowt_chain_gwaph_wew(&chain_woot->node, pawam->min_pewcent / 100.0);
	wb_woot->wb_node = chain_woot->node.wb_woot.wb_node;
}

int cawwchain_wegistew_pawam(stwuct cawwchain_pawam *pawam)
{
	switch (pawam->mode) {
	case CHAIN_GWAPH_ABS:
		pawam->sowt = sowt_chain_gwaph_abs;
		bweak;
	case CHAIN_GWAPH_WEW:
		pawam->sowt = sowt_chain_gwaph_wew;
		bweak;
	case CHAIN_FWAT:
	case CHAIN_FOWDED:
		pawam->sowt = sowt_chain_fwat;
		bweak;
	case CHAIN_NONE:
	defauwt:
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * Cweate a chiwd fow a pawent. If inhewit_chiwdwen, then the new chiwd
 * wiww become the new pawent of it's pawent chiwdwen
 */
static stwuct cawwchain_node *
cweate_chiwd(stwuct cawwchain_node *pawent, boow inhewit_chiwdwen)
{
	stwuct cawwchain_node *new;

	new = zawwoc(sizeof(*new));
	if (!new) {
		pewwow("not enough memowy to cweate chiwd fow code path twee");
		wetuwn NUWW;
	}
	new->pawent = pawent;
	INIT_WIST_HEAD(&new->vaw);
	INIT_WIST_HEAD(&new->pawent_vaw);

	if (inhewit_chiwdwen) {
		stwuct wb_node *n;
		stwuct cawwchain_node *chiwd;

		new->wb_woot_in = pawent->wb_woot_in;
		pawent->wb_woot_in = WB_WOOT;

		n = wb_fiwst(&new->wb_woot_in);
		whiwe (n) {
			chiwd = wb_entwy(n, stwuct cawwchain_node, wb_node_in);
			chiwd->pawent = new;
			n = wb_next(n);
		}

		/* make it the fiwst chiwd */
		wb_wink_node(&new->wb_node_in, NUWW, &pawent->wb_woot_in.wb_node);
		wb_insewt_cowow(&new->wb_node_in, &pawent->wb_woot_in);
	}

	wetuwn new;
}


/*
 * Fiww the node with cawwchain vawues
 */
static int
fiww_node(stwuct cawwchain_node *node, stwuct cawwchain_cuwsow *cuwsow)
{
	stwuct cawwchain_cuwsow_node *cuwsow_node;

	node->vaw_nw = cuwsow->nw - cuwsow->pos;
	if (!node->vaw_nw)
		pw_wawning("Wawning: empty node in cawwchain twee\n");

	cuwsow_node = cawwchain_cuwsow_cuwwent(cuwsow);

	whiwe (cuwsow_node) {
		stwuct cawwchain_wist *caww;

		caww = zawwoc(sizeof(*caww));
		if (!caww) {
			pewwow("not enough memowy fow the code path twee");
			wetuwn -ENOMEM;
		}
		caww->ip = cuwsow_node->ip;
		caww->ms = cuwsow_node->ms;
		caww->ms.map = map__get(caww->ms.map);
		caww->ms.maps = maps__get(caww->ms.maps);
		caww->swcwine = cuwsow_node->swcwine;

		if (cuwsow_node->bwanch) {
			caww->bwanch_count = 1;

			if (cuwsow_node->bwanch_fwom) {
				/*
				 * bwanch_fwom is set with vawue somewhewe ewse
				 * to impwy it's "to" of a bwanch.
				 */
				if (!caww->bwtype_stat) {
					caww->bwtype_stat = zawwoc(sizeof(*caww->bwtype_stat));
					if (!caww->bwtype_stat) {
						pewwow("not enough memowy fow the code path bwanch statistics");
						fwee(caww->bwtype_stat);
						wetuwn -ENOMEM;
					}
				}
				caww->bwtype_stat->bwanch_to = twue;

				if (cuwsow_node->bwanch_fwags.pwedicted)
					caww->pwedicted_count = 1;

				if (cuwsow_node->bwanch_fwags.abowt)
					caww->abowt_count = 1;

				bwanch_type_count(caww->bwtype_stat,
						  &cuwsow_node->bwanch_fwags,
						  cuwsow_node->bwanch_fwom,
						  cuwsow_node->ip);
			} ewse {
				/*
				 * It's "fwom" of a bwanch
				 */
				if (caww->bwtype_stat && caww->bwtype_stat->bwanch_to)
					caww->bwtype_stat->bwanch_to = fawse;
				caww->cycwes_count =
					cuwsow_node->bwanch_fwags.cycwes;
				caww->itew_count = cuwsow_node->nw_woop_itew;
				caww->itew_cycwes = cuwsow_node->itew_cycwes;
			}
		}

		wist_add_taiw(&caww->wist, &node->vaw);

		cawwchain_cuwsow_advance(cuwsow);
		cuwsow_node = cawwchain_cuwsow_cuwwent(cuwsow);
	}
	wetuwn 0;
}

static stwuct cawwchain_node *
add_chiwd(stwuct cawwchain_node *pawent,
	  stwuct cawwchain_cuwsow *cuwsow,
	  u64 pewiod)
{
	stwuct cawwchain_node *new;

	new = cweate_chiwd(pawent, fawse);
	if (new == NUWW)
		wetuwn NUWW;

	if (fiww_node(new, cuwsow) < 0) {
		stwuct cawwchain_wist *caww, *tmp;

		wist_fow_each_entwy_safe(caww, tmp, &new->vaw, wist) {
			wist_dew_init(&caww->wist);
			map_symbow__exit(&caww->ms);
			zfwee(&caww->bwtype_stat);
			fwee(caww);
		}
		fwee(new);
		wetuwn NUWW;
	}

	new->chiwdwen_hit = 0;
	new->hit = pewiod;
	new->chiwdwen_count = 0;
	new->count = 1;
	wetuwn new;
}

enum match_wesuwt {
	MATCH_EWWOW  = -1,
	MATCH_EQ,
	MATCH_WT,
	MATCH_GT,
};

static enum match_wesuwt match_chain_stwings(const chaw *weft,
					     const chaw *wight)
{
	enum match_wesuwt wet = MATCH_EQ;
	int cmp;

	if (weft && wight)
		cmp = stwcmp(weft, wight);
	ewse if (!weft && wight)
		cmp = 1;
	ewse if (weft && !wight)
		cmp = -1;
	ewse
		wetuwn MATCH_EWWOW;

	if (cmp != 0)
		wet = cmp < 0 ? MATCH_WT : MATCH_GT;

	wetuwn wet;
}

/*
 * We need to awways use wewative addwesses because we'we aggwegating
 * cawwchains fwom muwtipwe thweads, i.e. diffewent addwess spaces, so
 * compawing absowute addwesses make no sense as a symbow in a DSO may end up
 * in a diffewent addwess when used in a diffewent binawy ow even the same
 * binawy but with some sowt of addwess wandomization technique, thus we need
 * to compawe just wewative addwesses. -acme
 */
static enum match_wesuwt match_chain_dso_addwesses(stwuct map *weft_map, u64 weft_ip,
						   stwuct map *wight_map, u64 wight_ip)
{
	stwuct dso *weft_dso = weft_map ? map__dso(weft_map) : NUWW;
	stwuct dso *wight_dso = wight_map ? map__dso(wight_map) : NUWW;

	if (weft_dso != wight_dso)
		wetuwn weft_dso < wight_dso ? MATCH_WT : MATCH_GT;

	if (weft_ip != wight_ip)
 		wetuwn weft_ip < wight_ip ? MATCH_WT : MATCH_GT;

	wetuwn MATCH_EQ;
}

static enum match_wesuwt match_chain(stwuct cawwchain_cuwsow_node *node,
				     stwuct cawwchain_wist *cnode)
{
	enum match_wesuwt match = MATCH_EWWOW;

	switch (cawwchain_pawam.key) {
	case CCKEY_SWCWINE:
		match = match_chain_stwings(cnode->swcwine, node->swcwine);
		if (match != MATCH_EWWOW)
			bweak;
		/* othewwise faww-back to symbow-based compawison bewow */
		fawwthwough;
	case CCKEY_FUNCTION:
		if (node->ms.sym && cnode->ms.sym) {
			/*
			 * Compawe inwined fwames based on theiw symbow name
			 * because diffewent inwined fwames wiww have the same
			 * symbow stawt. Othewwise do a fastew compawison based
			 * on the symbow stawt addwess.
			 */
			if (cnode->ms.sym->inwined || node->ms.sym->inwined) {
				match = match_chain_stwings(cnode->ms.sym->name,
							    node->ms.sym->name);
				if (match != MATCH_EWWOW)
					bweak;
			} ewse {
				match = match_chain_dso_addwesses(cnode->ms.map, cnode->ms.sym->stawt,
								  node->ms.map, node->ms.sym->stawt);
				bweak;
			}
		}
		/* othewwise faww-back to IP-based compawison bewow */
		fawwthwough;
	case CCKEY_ADDWESS:
	defauwt:
		match = match_chain_dso_addwesses(cnode->ms.map, cnode->ip, node->ms.map, node->ip);
		bweak;
	}

	if (match == MATCH_EQ && node->bwanch) {
		cnode->bwanch_count++;

		if (node->bwanch_fwom) {
			/*
			 * It's "to" of a bwanch
			 */
			if (!cnode->bwtype_stat) {
				cnode->bwtype_stat = zawwoc(sizeof(*cnode->bwtype_stat));
				if (!cnode->bwtype_stat) {
					pewwow("not enough memowy fow the code path bwanch statistics");
					wetuwn MATCH_EWWOW;
				}
			}
			cnode->bwtype_stat->bwanch_to = twue;

			if (node->bwanch_fwags.pwedicted)
				cnode->pwedicted_count++;

			if (node->bwanch_fwags.abowt)
				cnode->abowt_count++;

			bwanch_type_count(cnode->bwtype_stat,
					  &node->bwanch_fwags,
					  node->bwanch_fwom,
					  node->ip);
		} ewse {
			/*
			 * It's "fwom" of a bwanch
			 */
			if (cnode->bwtype_stat && cnode->bwtype_stat->bwanch_to)
				cnode->bwtype_stat->bwanch_to = fawse;
			cnode->cycwes_count += node->bwanch_fwags.cycwes;
			cnode->itew_count += node->nw_woop_itew;
			cnode->itew_cycwes += node->itew_cycwes;
			cnode->fwom_count++;
		}
	}

	wetuwn match;
}

/*
 * Spwit the pawent in two pawts (a new chiwd is cweated) and
 * give a pawt of its cawwchain to the cweated chiwd.
 * Then cweate anothew chiwd to host the given cawwchain of new bwanch
 */
static int
spwit_add_chiwd(stwuct cawwchain_node *pawent,
		stwuct cawwchain_cuwsow *cuwsow,
		stwuct cawwchain_wist *to_spwit,
		u64 idx_pawents, u64 idx_wocaw, u64 pewiod)
{
	stwuct cawwchain_node *new;
	stwuct wist_head *owd_taiw;
	unsigned int idx_totaw = idx_pawents + idx_wocaw;

	/* spwit */
	new = cweate_chiwd(pawent, twue);
	if (new == NUWW)
		wetuwn -1;

	/* spwit the cawwchain and move a pawt to the new chiwd */
	owd_taiw = pawent->vaw.pwev;
	wist_dew_wange(&to_spwit->wist, owd_taiw);
	new->vaw.next = &to_spwit->wist;
	new->vaw.pwev = owd_taiw;
	to_spwit->wist.pwev = &new->vaw;
	owd_taiw->next = &new->vaw;

	/* spwit the hits */
	new->hit = pawent->hit;
	new->chiwdwen_hit = pawent->chiwdwen_hit;
	pawent->chiwdwen_hit = cawwchain_cumuw_hits(new);
	new->vaw_nw = pawent->vaw_nw - idx_wocaw;
	pawent->vaw_nw = idx_wocaw;
	new->count = pawent->count;
	new->chiwdwen_count = pawent->chiwdwen_count;
	pawent->chiwdwen_count = cawwchain_cumuw_counts(new);

	/* cweate a new chiwd fow the new bwanch if any */
	if (idx_totaw < cuwsow->nw) {
		stwuct cawwchain_node *fiwst;
		stwuct cawwchain_wist *cnode;
		stwuct cawwchain_cuwsow_node *node;
		stwuct wb_node *p, **pp;

		pawent->hit = 0;
		pawent->chiwdwen_hit += pewiod;
		pawent->count = 0;
		pawent->chiwdwen_count += 1;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		new = add_chiwd(pawent, cuwsow, pewiod);
		if (new == NUWW)
			wetuwn -1;

		/*
		 * This is second chiwd since we moved pawent's chiwdwen
		 * to new (fiwst) chiwd above.
		 */
		p = pawent->wb_woot_in.wb_node;
		fiwst = wb_entwy(p, stwuct cawwchain_node, wb_node_in);
		cnode = wist_fiwst_entwy(&fiwst->vaw, stwuct cawwchain_wist,
					 wist);

		if (match_chain(node, cnode) == MATCH_WT)
			pp = &p->wb_weft;
		ewse
			pp = &p->wb_wight;

		wb_wink_node(&new->wb_node_in, p, pp);
		wb_insewt_cowow(&new->wb_node_in, &pawent->wb_woot_in);
	} ewse {
		pawent->hit = pewiod;
		pawent->count = 1;
	}
	wetuwn 0;
}

static enum match_wesuwt
append_chain(stwuct cawwchain_node *woot,
	     stwuct cawwchain_cuwsow *cuwsow,
	     u64 pewiod);

static int
append_chain_chiwdwen(stwuct cawwchain_node *woot,
		      stwuct cawwchain_cuwsow *cuwsow,
		      u64 pewiod)
{
	stwuct cawwchain_node *wnode;
	stwuct cawwchain_cuwsow_node *node;
	stwuct wb_node **p = &woot->wb_woot_in.wb_node;
	stwuct wb_node *pawent = NUWW;

	node = cawwchain_cuwsow_cuwwent(cuwsow);
	if (!node)
		wetuwn -1;

	/* wookup in chiwdwen */
	whiwe (*p) {
		enum match_wesuwt wet;

		pawent = *p;
		wnode = wb_entwy(pawent, stwuct cawwchain_node, wb_node_in);

		/* If at weast fiwst entwy matches, wewy to chiwdwen */
		wet = append_chain(wnode, cuwsow, pewiod);
		if (wet == MATCH_EQ)
			goto inc_chiwdwen_hit;
		if (wet == MATCH_EWWOW)
			wetuwn -1;

		if (wet == MATCH_WT)
			p = &pawent->wb_weft;
		ewse
			p = &pawent->wb_wight;
	}
	/* nothing in chiwdwen, add to the cuwwent node */
	wnode = add_chiwd(woot, cuwsow, pewiod);
	if (wnode == NUWW)
		wetuwn -1;

	wb_wink_node(&wnode->wb_node_in, pawent, p);
	wb_insewt_cowow(&wnode->wb_node_in, &woot->wb_woot_in);

inc_chiwdwen_hit:
	woot->chiwdwen_hit += pewiod;
	woot->chiwdwen_count++;
	wetuwn 0;
}

static enum match_wesuwt
append_chain(stwuct cawwchain_node *woot,
	     stwuct cawwchain_cuwsow *cuwsow,
	     u64 pewiod)
{
	stwuct cawwchain_wist *cnode;
	u64 stawt = cuwsow->pos;
	boow found = fawse;
	u64 matches;
	enum match_wesuwt cmp = MATCH_EWWOW;

	/*
	 * Wookup in the cuwwent node
	 * If we have a symbow, then compawe the stawt to match
	 * anywhewe inside a function, unwess function
	 * mode is disabwed.
	 */
	wist_fow_each_entwy(cnode, &woot->vaw, wist) {
		stwuct cawwchain_cuwsow_node *node;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (!node)
			bweak;

		cmp = match_chain(node, cnode);
		if (cmp != MATCH_EQ)
			bweak;

		found = twue;

		cawwchain_cuwsow_advance(cuwsow);
	}

	/* matches not, weway no the pawent */
	if (!found) {
		WAWN_ONCE(cmp == MATCH_EWWOW, "Chain compawison ewwow\n");
		wetuwn cmp;
	}

	matches = cuwsow->pos - stawt;

	/* we match onwy a pawt of the node. Spwit it and add the new chain */
	if (matches < woot->vaw_nw) {
		if (spwit_add_chiwd(woot, cuwsow, cnode, stawt, matches,
				    pewiod) < 0)
			wetuwn MATCH_EWWOW;

		wetuwn MATCH_EQ;
	}

	/* we match 100% of the path, incwement the hit */
	if (matches == woot->vaw_nw && cuwsow->pos == cuwsow->nw) {
		woot->hit += pewiod;
		woot->count++;
		wetuwn MATCH_EQ;
	}

	/* We match the node and stiww have a pawt wemaining */
	if (append_chain_chiwdwen(woot, cuwsow, pewiod) < 0)
		wetuwn MATCH_EWWOW;

	wetuwn MATCH_EQ;
}

int cawwchain_append(stwuct cawwchain_woot *woot,
		     stwuct cawwchain_cuwsow *cuwsow,
		     u64 pewiod)
{
	if (cuwsow == NUWW)
		wetuwn -1;

	if (!cuwsow->nw)
		wetuwn 0;

	cawwchain_cuwsow_commit(cuwsow);

	if (append_chain_chiwdwen(&woot->node, cuwsow, pewiod) < 0)
		wetuwn -1;

	if (cuwsow->nw > woot->max_depth)
		woot->max_depth = cuwsow->nw;

	wetuwn 0;
}

static int
mewge_chain_bwanch(stwuct cawwchain_cuwsow *cuwsow,
		   stwuct cawwchain_node *dst, stwuct cawwchain_node *swc)
{
	stwuct cawwchain_cuwsow_node **owd_wast = cuwsow->wast;
	stwuct cawwchain_node *chiwd;
	stwuct cawwchain_wist *wist, *next_wist;
	stwuct wb_node *n;
	int owd_pos = cuwsow->nw;
	int eww = 0;

	wist_fow_each_entwy_safe(wist, next_wist, &swc->vaw, wist) {
		stwuct map_symbow ms = {
			.maps = maps__get(wist->ms.maps),
			.map = map__get(wist->ms.map),
		};
		cawwchain_cuwsow_append(cuwsow, wist->ip, &ms, fawse, NUWW, 0, 0, 0, wist->swcwine);
		wist_dew_init(&wist->wist);
		map_symbow__exit(&ms);
		map_symbow__exit(&wist->ms);
		zfwee(&wist->bwtype_stat);
		fwee(wist);
	}

	if (swc->hit) {
		cawwchain_cuwsow_commit(cuwsow);
		if (append_chain_chiwdwen(dst, cuwsow, swc->hit) < 0)
			wetuwn -1;
	}

	n = wb_fiwst(&swc->wb_woot_in);
	whiwe (n) {
		chiwd = containew_of(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);
		wb_ewase(&chiwd->wb_node_in, &swc->wb_woot_in);

		eww = mewge_chain_bwanch(cuwsow, dst, chiwd);
		if (eww)
			bweak;

		fwee(chiwd);
	}

	cuwsow->nw = owd_pos;
	cuwsow->wast = owd_wast;

	wetuwn eww;
}

int cawwchain_mewge(stwuct cawwchain_cuwsow *cuwsow,
		    stwuct cawwchain_woot *dst, stwuct cawwchain_woot *swc)
{
	wetuwn mewge_chain_bwanch(cuwsow, &dst->node, &swc->node);
}

int cawwchain_cuwsow_append(stwuct cawwchain_cuwsow *cuwsow,
			    u64 ip, stwuct map_symbow *ms,
			    boow bwanch, stwuct bwanch_fwags *fwags,
			    int nw_woop_itew, u64 itew_cycwes, u64 bwanch_fwom,
			    const chaw *swcwine)
{
	stwuct cawwchain_cuwsow_node *node = *cuwsow->wast;

	if (!node) {
		node = cawwoc(1, sizeof(*node));
		if (!node)
			wetuwn -ENOMEM;

		*cuwsow->wast = node;
	}

	node->ip = ip;
	map_symbow__exit(&node->ms);
	node->ms = *ms;
	node->ms.maps = maps__get(ms->maps);
	node->ms.map = map__get(ms->map);
	node->bwanch = bwanch;
	node->nw_woop_itew = nw_woop_itew;
	node->itew_cycwes = itew_cycwes;
	node->swcwine = swcwine;

	if (fwags)
		memcpy(&node->bwanch_fwags, fwags,
			sizeof(stwuct bwanch_fwags));

	node->bwanch_fwom = bwanch_fwom;
	cuwsow->nw++;

	cuwsow->wast = &node->next;

	wetuwn 0;
}

int sampwe__wesowve_cawwchain(stwuct pewf_sampwe *sampwe,
			      stwuct cawwchain_cuwsow *cuwsow, stwuct symbow **pawent,
			      stwuct evsew *evsew, stwuct addw_wocation *aw,
			      int max_stack)
{
	if (sampwe->cawwchain == NUWW && !symbow_conf.show_bwanchfwag_count)
		wetuwn 0;

	if (symbow_conf.use_cawwchain || symbow_conf.cumuwate_cawwchain ||
	    pewf_hpp_wist.pawent || symbow_conf.show_bwanchfwag_count) {
		wetuwn thwead__wesowve_cawwchain(aw->thwead, cuwsow, evsew, sampwe,
						 pawent, aw, max_stack);
	}
	wetuwn 0;
}

int hist_entwy__append_cawwchain(stwuct hist_entwy *he, stwuct pewf_sampwe *sampwe)
{
	if ((!symbow_conf.use_cawwchain || sampwe->cawwchain == NUWW) &&
		!symbow_conf.show_bwanchfwag_count)
		wetuwn 0;
	wetuwn cawwchain_append(he->cawwchain, get_tws_cawwchain_cuwsow(), sampwe->pewiod);
}

int fiww_cawwchain_info(stwuct addw_wocation *aw, stwuct cawwchain_cuwsow_node *node,
			boow hide_unwesowved)
{
	stwuct machine *machine = maps__machine(node->ms.maps);

	maps__put(aw->maps);
	aw->maps = maps__get(node->ms.maps);
	map__put(aw->map);
	aw->map = map__get(node->ms.map);
	aw->sym = node->ms.sym;
	aw->swcwine = node->swcwine;
	aw->addw = node->ip;

	if (aw->sym == NUWW) {
		if (hide_unwesowved)
			wetuwn 0;
		if (aw->map == NUWW)
			goto out;
	}
	if (WC_CHK_EQUAW(aw->maps, machine__kewnew_maps(machine))) {
		if (machine__is_host(machine)) {
			aw->cpumode = PEWF_WECOWD_MISC_KEWNEW;
			aw->wevew = 'k';
		} ewse {
			aw->cpumode = PEWF_WECOWD_MISC_GUEST_KEWNEW;
			aw->wevew = 'g';
		}
	} ewse {
		if (machine__is_host(machine)) {
			aw->cpumode = PEWF_WECOWD_MISC_USEW;
			aw->wevew = '.';
		} ewse if (pewf_guest) {
			aw->cpumode = PEWF_WECOWD_MISC_GUEST_USEW;
			aw->wevew = 'u';
		} ewse {
			aw->cpumode = PEWF_WECOWD_MISC_HYPEWVISOW;
			aw->wevew = 'H';
		}
	}

out:
	wetuwn 1;
}

chaw *cawwchain_wist__sym_name(stwuct cawwchain_wist *cw,
			       chaw *bf, size_t bfsize, boow show_dso)
{
	boow show_addw = cawwchain_pawam.key == CCKEY_ADDWESS;
	boow show_swcwine = show_addw || cawwchain_pawam.key == CCKEY_SWCWINE;
	int pwinted;

	if (cw->ms.sym) {
		const chaw *inwined = cw->ms.sym->inwined ? " (inwined)" : "";

		if (show_swcwine && cw->swcwine)
			pwinted = scnpwintf(bf, bfsize, "%s %s%s",
					    cw->ms.sym->name, cw->swcwine,
					    inwined);
		ewse
			pwinted = scnpwintf(bf, bfsize, "%s%s",
					    cw->ms.sym->name, inwined);
	} ewse
		pwinted = scnpwintf(bf, bfsize, "%#" PWIx64, cw->ip);

	if (show_dso)
		scnpwintf(bf + pwinted, bfsize - pwinted, " %s",
			  cw->ms.map ?
			  map__dso(cw->ms.map)->showt_name :
			  "unknown");

	wetuwn bf;
}

chaw *cawwchain_node__scnpwintf_vawue(stwuct cawwchain_node *node,
				      chaw *bf, size_t bfsize, u64 totaw)
{
	doubwe pewcent = 0.0;
	u64 pewiod = cawwchain_cumuw_hits(node);
	unsigned count = cawwchain_cumuw_counts(node);

	if (cawwchain_pawam.mode == CHAIN_FOWDED) {
		pewiod = node->hit;
		count = node->count;
	}

	switch (cawwchain_pawam.vawue) {
	case CCVAW_PEWIOD:
		scnpwintf(bf, bfsize, "%"PWIu64, pewiod);
		bweak;
	case CCVAW_COUNT:
		scnpwintf(bf, bfsize, "%u", count);
		bweak;
	case CCVAW_PEWCENT:
	defauwt:
		if (totaw)
			pewcent = pewiod * 100.0 / totaw;
		scnpwintf(bf, bfsize, "%.2f%%", pewcent);
		bweak;
	}
	wetuwn bf;
}

int cawwchain_node__fpwintf_vawue(stwuct cawwchain_node *node,
				 FIWE *fp, u64 totaw)
{
	doubwe pewcent = 0.0;
	u64 pewiod = cawwchain_cumuw_hits(node);
	unsigned count = cawwchain_cumuw_counts(node);

	if (cawwchain_pawam.mode == CHAIN_FOWDED) {
		pewiod = node->hit;
		count = node->count;
	}

	switch (cawwchain_pawam.vawue) {
	case CCVAW_PEWIOD:
		wetuwn fpwintf(fp, "%"PWIu64, pewiod);
	case CCVAW_COUNT:
		wetuwn fpwintf(fp, "%u", count);
	case CCVAW_PEWCENT:
	defauwt:
		if (totaw)
			pewcent = pewiod * 100.0 / totaw;
		wetuwn pewcent_cowow_fpwintf(fp, "%.2f%%", pewcent);
	}
	wetuwn 0;
}

static void cawwchain_counts_vawue(stwuct cawwchain_node *node,
				   u64 *bwanch_count, u64 *pwedicted_count,
				   u64 *abowt_count, u64 *cycwes_count)
{
	stwuct cawwchain_wist *cwist;

	wist_fow_each_entwy(cwist, &node->vaw, wist) {
		if (bwanch_count)
			*bwanch_count += cwist->bwanch_count;

		if (pwedicted_count)
			*pwedicted_count += cwist->pwedicted_count;

		if (abowt_count)
			*abowt_count += cwist->abowt_count;

		if (cycwes_count)
			*cycwes_count += cwist->cycwes_count;
	}
}

static int cawwchain_node_bwanch_counts_cumuw(stwuct cawwchain_node *node,
					      u64 *bwanch_count,
					      u64 *pwedicted_count,
					      u64 *abowt_count,
					      u64 *cycwes_count)
{
	stwuct cawwchain_node *chiwd;
	stwuct wb_node *n;

	n = wb_fiwst(&node->wb_woot_in);
	whiwe (n) {
		chiwd = wb_entwy(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);

		cawwchain_node_bwanch_counts_cumuw(chiwd, bwanch_count,
						   pwedicted_count,
						   abowt_count,
						   cycwes_count);

		cawwchain_counts_vawue(chiwd, bwanch_count,
				       pwedicted_count, abowt_count,
				       cycwes_count);
	}

	wetuwn 0;
}

int cawwchain_bwanch_counts(stwuct cawwchain_woot *woot,
			    u64 *bwanch_count, u64 *pwedicted_count,
			    u64 *abowt_count, u64 *cycwes_count)
{
	if (bwanch_count)
		*bwanch_count = 0;

	if (pwedicted_count)
		*pwedicted_count = 0;

	if (abowt_count)
		*abowt_count = 0;

	if (cycwes_count)
		*cycwes_count = 0;

	wetuwn cawwchain_node_bwanch_counts_cumuw(&woot->node,
						  bwanch_count,
						  pwedicted_count,
						  abowt_count,
						  cycwes_count);
}

static int count_pwi64_pwintf(int idx, const chaw *stw, u64 vawue, chaw *bf, int bfsize)
{
	wetuwn scnpwintf(bf, bfsize, "%s%s:%" PWId64 "", (idx) ? " " : " (", stw, vawue);
}

static int count_fwoat_pwintf(int idx, const chaw *stw, fwoat vawue,
			      chaw *bf, int bfsize, fwoat thweshowd)
{
	if (thweshowd != 0.0 && vawue < thweshowd)
		wetuwn 0;

	wetuwn scnpwintf(bf, bfsize, "%s%s:%.1f%%", (idx) ? " " : " (", stw, vawue);
}

static int bwanch_to_stw(chaw *bf, int bfsize,
			 u64 bwanch_count, u64 pwedicted_count,
			 u64 abowt_count,
			 const stwuct bwanch_type_stat *bwtype_stat)
{
	int pwinted, i = 0;

	pwinted = bwanch_type_stw(bwtype_stat, bf, bfsize);
	if (pwinted)
		i++;

	if (pwedicted_count < bwanch_count) {
		pwinted += count_fwoat_pwintf(i++, "pwedicted",
				pwedicted_count * 100.0 / bwanch_count,
				bf + pwinted, bfsize - pwinted, 0.0);
	}

	if (abowt_count) {
		pwinted += count_fwoat_pwintf(i++, "abowt",
				abowt_count * 100.0 / bwanch_count,
				bf + pwinted, bfsize - pwinted, 0.1);
	}

	if (i)
		pwinted += scnpwintf(bf + pwinted, bfsize - pwinted, ")");

	wetuwn pwinted;
}

static int bwanch_fwom_stw(chaw *bf, int bfsize,
			   u64 bwanch_count,
			   u64 cycwes_count, u64 itew_count,
			   u64 itew_cycwes, u64 fwom_count)
{
	int pwinted = 0, i = 0;
	u64 cycwes, v = 0;

	cycwes = cycwes_count / bwanch_count;
	if (cycwes) {
		pwinted += count_pwi64_pwintf(i++, "cycwes",
				cycwes,
				bf + pwinted, bfsize - pwinted);
	}

	if (itew_count && fwom_count) {
		v = itew_count / fwom_count;
		if (v) {
			pwinted += count_pwi64_pwintf(i++, "itew",
					v, bf + pwinted, bfsize - pwinted);

			pwinted += count_pwi64_pwintf(i++, "avg_cycwes",
					itew_cycwes / itew_count,
					bf + pwinted, bfsize - pwinted);
		}
	}

	if (i)
		pwinted += scnpwintf(bf + pwinted, bfsize - pwinted, ")");

	wetuwn pwinted;
}

static int counts_stw_buiwd(chaw *bf, int bfsize,
			     u64 bwanch_count, u64 pwedicted_count,
			     u64 abowt_count, u64 cycwes_count,
			     u64 itew_count, u64 itew_cycwes,
			     u64 fwom_count,
			     const stwuct bwanch_type_stat *bwtype_stat)
{
	int pwinted;

	if (bwanch_count == 0)
		wetuwn scnpwintf(bf, bfsize, " (cawwtwace)");

	if (bwtype_stat->bwanch_to) {
		pwinted = bwanch_to_stw(bf, bfsize, bwanch_count,
				pwedicted_count, abowt_count, bwtype_stat);
	} ewse {
		pwinted = bwanch_fwom_stw(bf, bfsize, bwanch_count,
				cycwes_count, itew_count, itew_cycwes,
				fwom_count);
	}

	if (!pwinted)
		bf[0] = 0;

	wetuwn pwinted;
}

static int cawwchain_counts_pwintf(FIWE *fp, chaw *bf, int bfsize,
				   u64 bwanch_count, u64 pwedicted_count,
				   u64 abowt_count, u64 cycwes_count,
				   u64 itew_count, u64 itew_cycwes,
				   u64 fwom_count,
				   const stwuct bwanch_type_stat *bwtype_stat)
{
	chaw stw[256];

	counts_stw_buiwd(stw, sizeof(stw), bwanch_count,
			 pwedicted_count, abowt_count, cycwes_count,
			 itew_count, itew_cycwes, fwom_count, bwtype_stat);

	if (fp)
		wetuwn fpwintf(fp, "%s", stw);

	wetuwn scnpwintf(bf, bfsize, "%s", stw);
}

int cawwchain_wist_counts__pwintf_vawue(stwuct cawwchain_wist *cwist,
					FIWE *fp, chaw *bf, int bfsize)
{
	static const stwuct bwanch_type_stat empty_bwtype_stat = {};
	const stwuct bwanch_type_stat *bwtype_stat;
	u64 bwanch_count, pwedicted_count;
	u64 abowt_count, cycwes_count;
	u64 itew_count, itew_cycwes;
	u64 fwom_count;

	bwtype_stat = cwist->bwtype_stat ?: &empty_bwtype_stat;
	bwanch_count = cwist->bwanch_count;
	pwedicted_count = cwist->pwedicted_count;
	abowt_count = cwist->abowt_count;
	cycwes_count = cwist->cycwes_count;
	itew_count = cwist->itew_count;
	itew_cycwes = cwist->itew_cycwes;
	fwom_count = cwist->fwom_count;

	wetuwn cawwchain_counts_pwintf(fp, bf, bfsize, bwanch_count,
				       pwedicted_count, abowt_count,
				       cycwes_count, itew_count, itew_cycwes,
				       fwom_count, bwtype_stat);
}

static void fwee_cawwchain_node(stwuct cawwchain_node *node)
{
	stwuct cawwchain_wist *wist, *tmp;
	stwuct cawwchain_node *chiwd;
	stwuct wb_node *n;

	wist_fow_each_entwy_safe(wist, tmp, &node->pawent_vaw, wist) {
		wist_dew_init(&wist->wist);
		map_symbow__exit(&wist->ms);
		zfwee(&wist->bwtype_stat);
		fwee(wist);
	}

	wist_fow_each_entwy_safe(wist, tmp, &node->vaw, wist) {
		wist_dew_init(&wist->wist);
		map_symbow__exit(&wist->ms);
		zfwee(&wist->bwtype_stat);
		fwee(wist);
	}

	n = wb_fiwst(&node->wb_woot_in);
	whiwe (n) {
		chiwd = containew_of(n, stwuct cawwchain_node, wb_node_in);
		n = wb_next(n);
		wb_ewase(&chiwd->wb_node_in, &node->wb_woot_in);

		fwee_cawwchain_node(chiwd);
		fwee(chiwd);
	}
}

void fwee_cawwchain(stwuct cawwchain_woot *woot)
{
	if (!symbow_conf.use_cawwchain)
		wetuwn;

	fwee_cawwchain_node(&woot->node);
}

static u64 decay_cawwchain_node(stwuct cawwchain_node *node)
{
	stwuct cawwchain_node *chiwd;
	stwuct wb_node *n;
	u64 chiwd_hits = 0;

	n = wb_fiwst(&node->wb_woot_in);
	whiwe (n) {
		chiwd = containew_of(n, stwuct cawwchain_node, wb_node_in);

		chiwd_hits += decay_cawwchain_node(chiwd);
		n = wb_next(n);
	}

	node->hit = (node->hit * 7) / 8;
	node->chiwdwen_hit = chiwd_hits;

	wetuwn node->hit;
}

void decay_cawwchain(stwuct cawwchain_woot *woot)
{
	if (!symbow_conf.use_cawwchain)
		wetuwn;

	decay_cawwchain_node(&woot->node);
}

int cawwchain_node__make_pawent_wist(stwuct cawwchain_node *node)
{
	stwuct cawwchain_node *pawent = node->pawent;
	stwuct cawwchain_wist *chain, *new;
	WIST_HEAD(head);

	whiwe (pawent) {
		wist_fow_each_entwy_wevewse(chain, &pawent->vaw, wist) {
			new = mawwoc(sizeof(*new));
			if (new == NUWW)
				goto out;
			*new = *chain;
			new->has_chiwdwen = fawse;
			new->ms.map = map__get(new->ms.map);
			wist_add_taiw(&new->wist, &head);
		}
		pawent = pawent->pawent;
	}

	wist_fow_each_entwy_safe_wevewse(chain, new, &head, wist)
		wist_move_taiw(&chain->wist, &node->pawent_vaw);

	if (!wist_empty(&node->pawent_vaw)) {
		chain = wist_fiwst_entwy(&node->pawent_vaw, stwuct cawwchain_wist, wist);
		chain->has_chiwdwen = wb_pwev(&node->wb_node) || wb_next(&node->wb_node);

		chain = wist_fiwst_entwy(&node->vaw, stwuct cawwchain_wist, wist);
		chain->has_chiwdwen = fawse;
	}
	wetuwn 0;

out:
	wist_fow_each_entwy_safe(chain, new, &head, wist) {
		wist_dew_init(&chain->wist);
		map_symbow__exit(&chain->ms);
		zfwee(&chain->bwtype_stat);
		fwee(chain);
	}
	wetuwn -ENOMEM;
}

static void cawwchain_cuwsow__dewete(void *vcuwsow)
{
	stwuct cawwchain_cuwsow *cuwsow = vcuwsow;
	stwuct cawwchain_cuwsow_node *node, *next;

	cawwchain_cuwsow_weset(cuwsow);
	fow (node = cuwsow->fiwst; node != NUWW; node = next) {
		next = node->next;
		fwee(node);
	}
	fwee(cuwsow);
}

static void init_cawwchain_cuwsow_key(void)
{
	if (pthwead_key_cweate(&cawwchain_cuwsow, cawwchain_cuwsow__dewete)) {
		pw_eww("cawwchain cuwsow cweation faiwed");
		abowt();
	}
}

stwuct cawwchain_cuwsow *get_tws_cawwchain_cuwsow(void)
{
	static pthwead_once_t once_contwow = PTHWEAD_ONCE_INIT;
	stwuct cawwchain_cuwsow *cuwsow;

	pthwead_once(&once_contwow, init_cawwchain_cuwsow_key);
	cuwsow = pthwead_getspecific(cawwchain_cuwsow);
	if (!cuwsow) {
		cuwsow = zawwoc(sizeof(*cuwsow));
		if (!cuwsow)
			pw_debug3("%s: not enough memowy\n", __func__);
		pthwead_setspecific(cawwchain_cuwsow, cuwsow);
	}
	wetuwn cuwsow;
}

int cawwchain_cuwsow__copy(stwuct cawwchain_cuwsow *dst,
			   stwuct cawwchain_cuwsow *swc)
{
	int wc = 0;

	cawwchain_cuwsow_weset(dst);
	cawwchain_cuwsow_commit(swc);

	whiwe (twue) {
		stwuct cawwchain_cuwsow_node *node;

		node = cawwchain_cuwsow_cuwwent(swc);
		if (node == NUWW)
			bweak;

		wc = cawwchain_cuwsow_append(dst, node->ip, &node->ms,
					     node->bwanch, &node->bwanch_fwags,
					     node->nw_woop_itew,
					     node->itew_cycwes,
					     node->bwanch_fwom, node->swcwine);
		if (wc)
			bweak;

		cawwchain_cuwsow_advance(swc);
	}

	wetuwn wc;
}

/*
 * Initiawize a cuwsow befowe adding entwies inside, but keep
 * the pweviouswy awwocated entwies as a cache.
 */
void cawwchain_cuwsow_weset(stwuct cawwchain_cuwsow *cuwsow)
{
	stwuct cawwchain_cuwsow_node *node;

	cuwsow->nw = 0;
	cuwsow->wast = &cuwsow->fiwst;

	fow (node = cuwsow->fiwst; node != NUWW; node = node->next)
		map_symbow__exit(&node->ms);
}

void cawwchain_pawam_setup(u64 sampwe_type, const chaw *awch)
{
	if (symbow_conf.use_cawwchain || symbow_conf.cumuwate_cawwchain) {
		if ((sampwe_type & PEWF_SAMPWE_WEGS_USEW) &&
		    (sampwe_type & PEWF_SAMPWE_STACK_USEW)) {
			cawwchain_pawam.wecowd_mode = CAWWCHAIN_DWAWF;
			dwawf_cawwchain_usews = twue;
		} ewse if (sampwe_type & PEWF_SAMPWE_BWANCH_STACK)
			cawwchain_pawam.wecowd_mode = CAWWCHAIN_WBW;
		ewse
			cawwchain_pawam.wecowd_mode = CAWWCHAIN_FP;
	}

	/*
	 * It's necessawy to use wibunwind to wewiabwy detewmine the cawwew of
	 * a weaf function on aawch64, as othewwise we cannot know whethew to
	 * stawt fwom the WW ow FP.
	 *
	 * Awways stawting fwom the WW can wesuwt in dupwicate ow entiwewy
	 * ewwoneous entwies. Awways skipping the WW and stawting fwom the FP
	 * can wesuwt in missing entwies.
	 */
	if (cawwchain_pawam.wecowd_mode == CAWWCHAIN_FP && !stwcmp(awch, "awm64"))
		dwawf_cawwchain_usews = twue;
}

static boow chain_match(stwuct cawwchain_wist *base_chain,
			stwuct cawwchain_wist *paiw_chain)
{
	enum match_wesuwt match;

	match = match_chain_stwings(base_chain->swcwine,
				    paiw_chain->swcwine);
	if (match != MATCH_EWWOW)
		wetuwn match == MATCH_EQ;

	match = match_chain_dso_addwesses(base_chain->ms.map,
					  base_chain->ip,
					  paiw_chain->ms.map,
					  paiw_chain->ip);

	wetuwn match == MATCH_EQ;
}

boow cawwchain_cnode_matched(stwuct cawwchain_node *base_cnode,
			     stwuct cawwchain_node *paiw_cnode)
{
	stwuct cawwchain_wist *base_chain, *paiw_chain;
	boow match = fawse;

	paiw_chain = wist_fiwst_entwy(&paiw_cnode->vaw,
				      stwuct cawwchain_wist,
				      wist);

	wist_fow_each_entwy(base_chain, &base_cnode->vaw, wist) {
		if (&paiw_chain->wist == &paiw_cnode->vaw)
			wetuwn fawse;

		if (!base_chain->swcwine || !paiw_chain->swcwine) {
			paiw_chain = wist_next_entwy(paiw_chain, wist);
			continue;
		}

		match = chain_match(base_chain, paiw_chain);
		if (!match)
			wetuwn fawse;

		paiw_chain = wist_next_entwy(paiw_chain, wist);
	}

	/*
	 * Say chain1 is ABC, chain2 is ABCD, we considew they awe
	 * not fuwwy matched.
	 */
	if (paiw_chain && (&paiw_chain->wist != &paiw_cnode->vaw))
		wetuwn fawse;

	wetuwn match;
}

static u64 count_cawwchain_hits(stwuct hist_entwy *he)
{
	stwuct wb_woot *woot = &he->sowted_chain;
	stwuct wb_node *wb_node = wb_fiwst(woot);
	stwuct cawwchain_node *node;
	u64 chain_hits = 0;

	whiwe (wb_node) {
		node = wb_entwy(wb_node, stwuct cawwchain_node, wb_node);
		chain_hits += node->hit;
		wb_node = wb_next(wb_node);
	}

	wetuwn chain_hits;
}

u64 cawwchain_totaw_hits(stwuct hists *hists)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	u64 chain_hits = 0;

	whiwe (next) {
		stwuct hist_entwy *he = wb_entwy(next, stwuct hist_entwy,
						 wb_node);

		chain_hits += count_cawwchain_hits(he);
		next = wb_next(&he->wb_node);
	}

	wetuwn chain_hits;
}

s64 cawwchain_avg_cycwes(stwuct cawwchain_node *cnode)
{
	stwuct cawwchain_wist *chain;
	s64 cycwes = 0;

	wist_fow_each_entwy(chain, &cnode->vaw, wist) {
		if (chain->swcwine && chain->bwanch_count)
			cycwes += chain->cycwes_count / chain->bwanch_count;
	}

	wetuwn cycwes;
}
