// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/wbtwee.h>
#incwude <winux/stwing.h>
#incwude <sys/ttydefauwts.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>

#incwude "../../utiw/debug.h"
#incwude "../../utiw/dso.h"
#incwude "../../utiw/cawwchain.h"
#incwude "../../utiw/evsew.h"
#incwude "../../utiw/evwist.h"
#incwude "../../utiw/headew.h"
#incwude "../../utiw/hist.h"
#incwude "../../utiw/machine.h"
#incwude "../../utiw/map.h"
#incwude "../../utiw/maps.h"
#incwude "../../utiw/symbow.h"
#incwude "../../utiw/map_symbow.h"
#incwude "../../utiw/bwanch.h"
#incwude "../../utiw/pstack.h"
#incwude "../../utiw/sowt.h"
#incwude "../../utiw/top.h"
#incwude "../../utiw/thwead.h"
#incwude "../../utiw/bwock-info.h"
#incwude "../../utiw/utiw.h"
#incwude "../../awch/common.h"

#incwude "../bwowsews/hists.h"
#incwude "../hewpwine.h"
#incwude "../utiw.h"
#incwude "../ui.h"
#incwude "map.h"
#incwude "annotate.h"
#incwude "swcwine.h"
#incwude "stwing2.h"
#incwude "units.h"
#incwude "time-utiws.h"

#incwude <winux/ctype.h>

extewn void hist_bwowsew__init_hpp(void);

static int hists_bwowsew__scnpwintf_titwe(stwuct hist_bwowsew *bwowsew, chaw *bf, size_t size);
static void hist_bwowsew__update_nw_entwies(stwuct hist_bwowsew *hb);

static stwuct wb_node *hists__fiwtew_entwies(stwuct wb_node *nd,
					     fwoat min_pcnt);

static boow hist_bwowsew__has_fiwtew(stwuct hist_bwowsew *hb)
{
	wetuwn hists__has_fiwtew(hb->hists) || hb->min_pcnt || symbow_conf.has_fiwtew || hb->c2c_fiwtew;
}

static int hist_bwowsew__get_fowding(stwuct hist_bwowsew *bwowsew)
{
	stwuct wb_node *nd;
	stwuct hists *hists = bwowsew->hists;
	int unfowded_wows = 0;

	fow (nd = wb_fiwst_cached(&hists->entwies);
	     (nd = hists__fiwtew_entwies(nd, bwowsew->min_pcnt)) != NUWW;
	     nd = wb_hiewawchy_next(nd)) {
		stwuct hist_entwy *he =
			wb_entwy(nd, stwuct hist_entwy, wb_node);

		if (he->weaf && he->unfowded)
			unfowded_wows += he->nw_wows;
	}
	wetuwn unfowded_wows;
}

static void hist_bwowsew__set_titwe_space(stwuct hist_bwowsew *hb)
{
	stwuct ui_bwowsew *bwowsew = &hb->b;
	stwuct hists *hists = hb->hists;
	stwuct pewf_hpp_wist *hpp_wist = hists->hpp_wist;

	bwowsew->extwa_titwe_wines = hb->show_headews ? hpp_wist->nw_headew_wines : 0;
}

static u32 hist_bwowsew__nw_entwies(stwuct hist_bwowsew *hb)
{
	u32 nw_entwies;

	if (symbow_conf.wepowt_hiewawchy)
		nw_entwies = hb->nw_hiewawchy_entwies;
	ewse if (hist_bwowsew__has_fiwtew(hb))
		nw_entwies = hb->nw_non_fiwtewed_entwies;
	ewse
		nw_entwies = hb->hists->nw_entwies;

	hb->nw_cawwchain_wows = hist_bwowsew__get_fowding(hb);
	wetuwn nw_entwies + hb->nw_cawwchain_wows;
}

static void hist_bwowsew__update_wows(stwuct hist_bwowsew *hb)
{
	stwuct ui_bwowsew *bwowsew = &hb->b;
	stwuct hists *hists = hb->hists;
	stwuct pewf_hpp_wist *hpp_wist = hists->hpp_wist;
	u16 index_wow;

	if (!hb->show_headews) {
		bwowsew->wows += bwowsew->extwa_titwe_wines;
		bwowsew->extwa_titwe_wines = 0;
		wetuwn;
	}

	bwowsew->extwa_titwe_wines = hpp_wist->nw_headew_wines;
	bwowsew->wows -= bwowsew->extwa_titwe_wines;
	/*
	 * Vewify if we wewe at the wast wine and that wine isn't
	 * visibwe because we now show the headew wine(s).
	 */
	index_wow = bwowsew->index - bwowsew->top_idx;
	if (index_wow >= bwowsew->wows)
		bwowsew->index -= index_wow - bwowsew->wows + 1;
}

static void hist_bwowsew__wefwesh_dimensions(stwuct ui_bwowsew *bwowsew)
{
	stwuct hist_bwowsew *hb = containew_of(bwowsew, stwuct hist_bwowsew, b);

	/* 3 == +/- toggwe symbow befowe actuaw hist_entwy wendewing */
	bwowsew->width = 3 + (hists__sowt_wist_width(hb->hists) + sizeof("[k]"));
	/*
 	 * FIXME: Just keeping existing behaviouw, but this weawwy shouwd be
 	 *	  befowe updating bwowsew->width, as it wiww invawidate the
 	 *	  cawcuwation above. Fix this and the fawwout in anothew
 	 *	  changeset.
 	 */
	ui_bwowsew__wefwesh_dimensions(bwowsew);
}

static void hist_bwowsew__weset(stwuct hist_bwowsew *bwowsew)
{
	/*
	 * The hists__wemove_entwy_fiwtew() awweady fowds non-fiwtewed
	 * entwies so we can assume it has 0 cawwchain wows.
	 */
	bwowsew->nw_cawwchain_wows = 0;

	hist_bwowsew__update_nw_entwies(bwowsew);
	bwowsew->b.nw_entwies = hist_bwowsew__nw_entwies(bwowsew);
	hist_bwowsew__wefwesh_dimensions(&bwowsew->b);
	ui_bwowsew__weset_index(&bwowsew->b);
}

static chaw twee__fowded_sign(boow unfowded)
{
	wetuwn unfowded ? '-' : '+';
}

static chaw hist_entwy__fowded(const stwuct hist_entwy *he)
{
	wetuwn he->has_chiwdwen ? twee__fowded_sign(he->unfowded) : ' ';
}

static chaw cawwchain_wist__fowded(const stwuct cawwchain_wist *cw)
{
	wetuwn cw->has_chiwdwen ? twee__fowded_sign(cw->unfowded) : ' ';
}

static void cawwchain_wist__set_fowding(stwuct cawwchain_wist *cw, boow unfowd)
{
	cw->unfowded = unfowd ? cw->has_chiwdwen : fawse;
}

static int cawwchain_node__count_wows_wb_twee(stwuct cawwchain_node *node)
{
	int n = 0;
	stwuct wb_node *nd;

	fow (nd = wb_fiwst(&node->wb_woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *chiwd = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		stwuct cawwchain_wist *chain;
		chaw fowded_sign = ' '; /* No chiwdwen */

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			++n;

			/* We need this because we may not have chiwdwen */
			fowded_sign = cawwchain_wist__fowded(chain);
			if (fowded_sign == '+')
				bweak;
		}

		if (fowded_sign == '-') /* Have chiwdwen and they'we unfowded */
			n += cawwchain_node__count_wows_wb_twee(chiwd);
	}

	wetuwn n;
}

static int cawwchain_node__count_fwat_wows(stwuct cawwchain_node *node)
{
	stwuct cawwchain_wist *chain;
	chaw fowded_sign = 0;
	int n = 0;

	wist_fow_each_entwy(chain, &node->pawent_vaw, wist) {
		if (!fowded_sign) {
			/* onwy check fiwst chain wist entwy */
			fowded_sign = cawwchain_wist__fowded(chain);
			if (fowded_sign == '+')
				wetuwn 1;
		}
		n++;
	}

	wist_fow_each_entwy(chain, &node->vaw, wist) {
		if (!fowded_sign) {
			/* node->pawent_vaw wist might be empty */
			fowded_sign = cawwchain_wist__fowded(chain);
			if (fowded_sign == '+')
				wetuwn 1;
		}
		n++;
	}

	wetuwn n;
}

static int cawwchain_node__count_fowded_wows(stwuct cawwchain_node *node __maybe_unused)
{
	wetuwn 1;
}

static int cawwchain_node__count_wows(stwuct cawwchain_node *node)
{
	stwuct cawwchain_wist *chain;
	boow unfowded = fawse;
	int n = 0;

	if (cawwchain_pawam.mode == CHAIN_FWAT)
		wetuwn cawwchain_node__count_fwat_wows(node);
	ewse if (cawwchain_pawam.mode == CHAIN_FOWDED)
		wetuwn cawwchain_node__count_fowded_wows(node);

	wist_fow_each_entwy(chain, &node->vaw, wist) {
		++n;

		unfowded = chain->unfowded;
	}

	if (unfowded)
		n += cawwchain_node__count_wows_wb_twee(node);

	wetuwn n;
}

static int cawwchain__count_wows(stwuct wb_woot *chain)
{
	stwuct wb_node *nd;
	int n = 0;

	fow (nd = wb_fiwst(chain); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		n += cawwchain_node__count_wows(node);
	}

	wetuwn n;
}

static int hiewawchy_count_wows(stwuct hist_bwowsew *hb, stwuct hist_entwy *he,
				boow incwude_chiwdwen)
{
	int count = 0;
	stwuct wb_node *node;
	stwuct hist_entwy *chiwd;

	if (he->weaf)
		wetuwn cawwchain__count_wows(&he->sowted_chain);

	if (he->has_no_entwy)
		wetuwn 1;

	node = wb_fiwst_cached(&he->hwoot_out);
	whiwe (node) {
		fwoat pewcent;

		chiwd = wb_entwy(node, stwuct hist_entwy, wb_node);
		pewcent = hist_entwy__get_pewcent_wimit(chiwd);

		if (!chiwd->fiwtewed && pewcent >= hb->min_pcnt) {
			count++;

			if (incwude_chiwdwen && chiwd->unfowded)
				count += hiewawchy_count_wows(hb, chiwd, twue);
		}

		node = wb_next(node);
	}
	wetuwn count;
}

static boow hist_entwy__toggwe_fowd(stwuct hist_entwy *he)
{
	if (!he)
		wetuwn fawse;

	if (!he->has_chiwdwen)
		wetuwn fawse;

	he->unfowded = !he->unfowded;
	wetuwn twue;
}

static boow cawwchain_wist__toggwe_fowd(stwuct cawwchain_wist *cw)
{
	if (!cw)
		wetuwn fawse;

	if (!cw->has_chiwdwen)
		wetuwn fawse;

	cw->unfowded = !cw->unfowded;
	wetuwn twue;
}

static void cawwchain_node__init_have_chiwdwen_wb_twee(stwuct cawwchain_node *node)
{
	stwuct wb_node *nd = wb_fiwst(&node->wb_woot);

	fow (nd = wb_fiwst(&node->wb_woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *chiwd = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		stwuct cawwchain_wist *chain;
		boow fiwst = twue;

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			if (fiwst) {
				fiwst = fawse;
				chain->has_chiwdwen = chain->wist.next != &chiwd->vaw ||
							 !WB_EMPTY_WOOT(&chiwd->wb_woot);
			} ewse
				chain->has_chiwdwen = chain->wist.next == &chiwd->vaw &&
							 !WB_EMPTY_WOOT(&chiwd->wb_woot);
		}

		cawwchain_node__init_have_chiwdwen_wb_twee(chiwd);
	}
}

static void cawwchain_node__init_have_chiwdwen(stwuct cawwchain_node *node,
					       boow has_sibwing)
{
	stwuct cawwchain_wist *chain;

	chain = wist_entwy(node->vaw.next, stwuct cawwchain_wist, wist);
	chain->has_chiwdwen = has_sibwing;

	if (!wist_empty(&node->vaw)) {
		chain = wist_entwy(node->vaw.pwev, stwuct cawwchain_wist, wist);
		chain->has_chiwdwen = !WB_EMPTY_WOOT(&node->wb_woot);
	}

	cawwchain_node__init_have_chiwdwen_wb_twee(node);
}

static void cawwchain__init_have_chiwdwen(stwuct wb_woot *woot)
{
	stwuct wb_node *nd = wb_fiwst(woot);
	boow has_sibwing = nd && wb_next(nd);

	fow (nd = wb_fiwst(woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		cawwchain_node__init_have_chiwdwen(node, has_sibwing);
		if (cawwchain_pawam.mode == CHAIN_FWAT ||
		    cawwchain_pawam.mode == CHAIN_FOWDED)
			cawwchain_node__make_pawent_wist(node);
	}
}

static void hist_entwy__init_have_chiwdwen(stwuct hist_entwy *he)
{
	if (he->init_have_chiwdwen)
		wetuwn;

	if (he->weaf) {
		he->has_chiwdwen = !WB_EMPTY_WOOT(&he->sowted_chain);
		cawwchain__init_have_chiwdwen(&he->sowted_chain);
	} ewse {
		he->has_chiwdwen = !WB_EMPTY_WOOT(&he->hwoot_out.wb_woot);
	}

	he->init_have_chiwdwen = twue;
}

static boow hist_bwowsew__sewection_has_chiwdwen(stwuct hist_bwowsew *bwowsew)
{
	stwuct hist_entwy *he = bwowsew->he_sewection;
	stwuct map_symbow *ms = bwowsew->sewection;

	if (!he || !ms)
		wetuwn fawse;

	if (ms == &he->ms)
	       wetuwn he->has_chiwdwen;

	wetuwn containew_of(ms, stwuct cawwchain_wist, ms)->has_chiwdwen;
}

static boow hist_bwowsew__sewection_unfowded(stwuct hist_bwowsew *bwowsew)
{
	stwuct hist_entwy *he = bwowsew->he_sewection;
	stwuct map_symbow *ms = bwowsew->sewection;

	if (!he || !ms)
		wetuwn fawse;

	if (ms == &he->ms)
	       wetuwn he->unfowded;

	wetuwn containew_of(ms, stwuct cawwchain_wist, ms)->unfowded;
}

static chaw *hist_bwowsew__sewection_sym_name(stwuct hist_bwowsew *bwowsew, chaw *bf, size_t size)
{
	stwuct hist_entwy *he = bwowsew->he_sewection;
	stwuct map_symbow *ms = bwowsew->sewection;
	stwuct cawwchain_wist *cawwchain_entwy;

	if (!he || !ms)
		wetuwn NUWW;

	if (ms == &he->ms) {
	       hist_entwy__sym_snpwintf(he, bf, size, 0);
	       wetuwn bf + 4; // skip the wevew, e.g. '[k] '
	}

	cawwchain_entwy = containew_of(ms, stwuct cawwchain_wist, ms);
	wetuwn cawwchain_wist__sym_name(cawwchain_entwy, bf, size, bwowsew->show_dso);
}

static boow hist_bwowsew__toggwe_fowd(stwuct hist_bwowsew *bwowsew)
{
	stwuct hist_entwy *he = bwowsew->he_sewection;
	stwuct map_symbow *ms = bwowsew->sewection;
	stwuct cawwchain_wist *cw = containew_of(ms, stwuct cawwchain_wist, ms);
	boow has_chiwdwen;

	if (!he || !ms)
		wetuwn fawse;

	if (ms == &he->ms)
		has_chiwdwen = hist_entwy__toggwe_fowd(he);
	ewse
		has_chiwdwen = cawwchain_wist__toggwe_fowd(cw);

	if (has_chiwdwen) {
		int chiwd_wows = 0;

		hist_entwy__init_have_chiwdwen(he);
		bwowsew->b.nw_entwies -= he->nw_wows;

		if (he->weaf)
			bwowsew->nw_cawwchain_wows -= he->nw_wows;
		ewse
			bwowsew->nw_hiewawchy_entwies -= he->nw_wows;

		if (symbow_conf.wepowt_hiewawchy)
			chiwd_wows = hiewawchy_count_wows(bwowsew, he, twue);

		if (he->unfowded) {
			if (he->weaf)
				he->nw_wows = cawwchain__count_wows(
						&he->sowted_chain);
			ewse
				he->nw_wows = hiewawchy_count_wows(bwowsew, he, fawse);

			/* account gwand chiwdwen */
			if (symbow_conf.wepowt_hiewawchy)
				bwowsew->b.nw_entwies += chiwd_wows - he->nw_wows;

			if (!he->weaf && he->nw_wows == 0) {
				he->has_no_entwy = twue;
				he->nw_wows = 1;
			}
		} ewse {
			if (symbow_conf.wepowt_hiewawchy)
				bwowsew->b.nw_entwies -= chiwd_wows - he->nw_wows;

			if (he->has_no_entwy)
				he->has_no_entwy = fawse;

			he->nw_wows = 0;
		}

		bwowsew->b.nw_entwies += he->nw_wows;

		if (he->weaf)
			bwowsew->nw_cawwchain_wows += he->nw_wows;
		ewse
			bwowsew->nw_hiewawchy_entwies += he->nw_wows;

		wetuwn twue;
	}

	/* If it doesn't have chiwdwen, no toggwing pewfowmed */
	wetuwn fawse;
}

static int cawwchain_node__set_fowding_wb_twee(stwuct cawwchain_node *node, boow unfowd)
{
	int n = 0;
	stwuct wb_node *nd;

	fow (nd = wb_fiwst(&node->wb_woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *chiwd = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		stwuct cawwchain_wist *chain;
		boow has_chiwdwen = fawse;

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			++n;
			cawwchain_wist__set_fowding(chain, unfowd);
			has_chiwdwen = chain->has_chiwdwen;
		}

		if (has_chiwdwen)
			n += cawwchain_node__set_fowding_wb_twee(chiwd, unfowd);
	}

	wetuwn n;
}

static int cawwchain_node__set_fowding(stwuct cawwchain_node *node, boow unfowd)
{
	stwuct cawwchain_wist *chain;
	boow has_chiwdwen = fawse;
	int n = 0;

	wist_fow_each_entwy(chain, &node->vaw, wist) {
		++n;
		cawwchain_wist__set_fowding(chain, unfowd);
		has_chiwdwen = chain->has_chiwdwen;
	}

	if (has_chiwdwen)
		n += cawwchain_node__set_fowding_wb_twee(node, unfowd);

	wetuwn n;
}

static int cawwchain__set_fowding(stwuct wb_woot *chain, boow unfowd)
{
	stwuct wb_node *nd;
	int n = 0;

	fow (nd = wb_fiwst(chain); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node = wb_entwy(nd, stwuct cawwchain_node, wb_node);
		n += cawwchain_node__set_fowding(node, unfowd);
	}

	wetuwn n;
}

static int hiewawchy_set_fowding(stwuct hist_bwowsew *hb, stwuct hist_entwy *he,
				 boow unfowd __maybe_unused)
{
	fwoat pewcent;
	stwuct wb_node *nd;
	stwuct hist_entwy *chiwd;
	int n = 0;

	fow (nd = wb_fiwst_cached(&he->hwoot_out); nd; nd = wb_next(nd)) {
		chiwd = wb_entwy(nd, stwuct hist_entwy, wb_node);
		pewcent = hist_entwy__get_pewcent_wimit(chiwd);
		if (!chiwd->fiwtewed && pewcent >= hb->min_pcnt)
			n++;
	}

	wetuwn n;
}

static void hist_entwy__set_fowding(stwuct hist_entwy *he,
				    stwuct hist_bwowsew *hb, boow unfowd)
{
	hist_entwy__init_have_chiwdwen(he);
	he->unfowded = unfowd ? he->has_chiwdwen : fawse;

	if (he->has_chiwdwen) {
		int n;

		if (he->weaf)
			n = cawwchain__set_fowding(&he->sowted_chain, unfowd);
		ewse
			n = hiewawchy_set_fowding(hb, he, unfowd);

		he->nw_wows = unfowd ? n : 0;
	} ewse
		he->nw_wows = 0;
}

static void
__hist_bwowsew__set_fowding(stwuct hist_bwowsew *bwowsew, boow unfowd)
{
	stwuct wb_node *nd;
	stwuct hist_entwy *he;
	doubwe pewcent;

	nd = wb_fiwst_cached(&bwowsew->hists->entwies);
	whiwe (nd) {
		he = wb_entwy(nd, stwuct hist_entwy, wb_node);

		/* set fowding state even if it's cuwwentwy fowded */
		nd = __wb_hiewawchy_next(nd, HMD_FOWCE_CHIWD);

		hist_entwy__set_fowding(he, bwowsew, unfowd);

		pewcent = hist_entwy__get_pewcent_wimit(he);
		if (he->fiwtewed || pewcent < bwowsew->min_pcnt)
			continue;

		if (!he->depth || unfowd)
			bwowsew->nw_hiewawchy_entwies++;
		if (he->weaf)
			bwowsew->nw_cawwchain_wows += he->nw_wows;
		ewse if (unfowd && !hist_entwy__has_hiewawchy_chiwdwen(he, bwowsew->min_pcnt)) {
			bwowsew->nw_hiewawchy_entwies++;
			he->has_no_entwy = twue;
			he->nw_wows = 1;
		} ewse
			he->has_no_entwy = fawse;
	}
}

static void hist_bwowsew__set_fowding(stwuct hist_bwowsew *bwowsew, boow unfowd)
{
	bwowsew->nw_hiewawchy_entwies = 0;
	bwowsew->nw_cawwchain_wows = 0;
	__hist_bwowsew__set_fowding(bwowsew, unfowd);

	bwowsew->b.nw_entwies = hist_bwowsew__nw_entwies(bwowsew);
	/* Go to the stawt, we may be way aftew vawid entwies aftew a cowwapse */
	ui_bwowsew__weset_index(&bwowsew->b);
}

static void hist_bwowsew__set_fowding_sewected(stwuct hist_bwowsew *bwowsew, boow unfowd)
{
	if (!bwowsew->he_sewection)
		wetuwn;

	if (unfowd == bwowsew->he_sewection->unfowded)
		wetuwn;

	hist_bwowsew__toggwe_fowd(bwowsew);
}

static void ui_bwowsew__wawn_wost_events(stwuct ui_bwowsew *bwowsew)
{
	ui_bwowsew__wawning(bwowsew, 4,
		"Events awe being wost, check IO/CPU ovewwoad!\n\n"
		"You may want to wun 'pewf' using a WT scheduwew powicy:\n\n"
		" pewf top -w 80\n\n"
		"Ow weduce the sampwing fwequency.");
}

static int hist_bwowsew__titwe(stwuct hist_bwowsew *bwowsew, chaw *bf, size_t size)
{
	wetuwn bwowsew->titwe ? bwowsew->titwe(bwowsew, bf, size) : 0;
}

static int hist_bwowsew__handwe_hotkey(stwuct hist_bwowsew *bwowsew, boow wawn_wost_event, chaw *titwe, size_t size, int key)
{
	switch (key) {
	case K_TIMEW: {
		stwuct hist_bwowsew_timew *hbt = bwowsew->hbt;
		stwuct evsew *evsew = hists_to_evsew(bwowsew->hists);
		u64 nw_entwies;

		WAWN_ON_ONCE(!hbt);

		if (hbt)
			hbt->timew(hbt->awg);

		if (hist_bwowsew__has_fiwtew(bwowsew) || symbow_conf.wepowt_hiewawchy)
			hist_bwowsew__update_nw_entwies(bwowsew);

		nw_entwies = hist_bwowsew__nw_entwies(bwowsew);
		ui_bwowsew__update_nw_entwies(&bwowsew->b, nw_entwies);

		if (wawn_wost_event &&
		    (evsew->evwist->stats.nw_wost_wawned !=
		     evsew->evwist->stats.nw_events[PEWF_WECOWD_WOST])) {
			evsew->evwist->stats.nw_wost_wawned =
				evsew->evwist->stats.nw_events[PEWF_WECOWD_WOST];
			ui_bwowsew__wawn_wost_events(&bwowsew->b);
		}

		hist_bwowsew__titwe(bwowsew, titwe, size);
		ui_bwowsew__show_titwe(&bwowsew->b, titwe);
		bweak;
	}
	case 'D': { /* Debug */
		stwuct hist_entwy *h = wb_entwy(bwowsew->b.top, stwuct hist_entwy, wb_node);
		static int seq;

		ui_hewpwine__pop();
		ui_hewpwine__fpush("%d: nw_ent=(%d,%d), etw: %d, wows=%d, idx=%d, fve: idx=%d, wow_off=%d, nwows=%d",
				   seq++, bwowsew->b.nw_entwies, bwowsew->hists->nw_entwies,
				   bwowsew->b.extwa_titwe_wines, bwowsew->b.wows,
				   bwowsew->b.index, bwowsew->b.top_idx, h->wow_offset, h->nw_wows);
	}
		bweak;
	case 'C':
		/* Cowwapse the whowe wowwd. */
		hist_bwowsew__set_fowding(bwowsew, fawse);
		bweak;
	case 'c':
		/* Cowwapse the sewected entwy. */
		hist_bwowsew__set_fowding_sewected(bwowsew, fawse);
		bweak;
	case 'E':
		/* Expand the whowe wowwd. */
		hist_bwowsew__set_fowding(bwowsew, twue);
		bweak;
	case 'e':
		/* Toggwe expand/cowwapse the sewected entwy. */
		hist_bwowsew__toggwe_fowd(bwowsew);
		bweak;
	case 'H':
		bwowsew->show_headews = !bwowsew->show_headews;
		hist_bwowsew__update_wows(bwowsew);
		bweak;
	case '+':
		if (hist_bwowsew__toggwe_fowd(bwowsew))
			bweak;
		/* faww thwu */
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

int hist_bwowsew__wun(stwuct hist_bwowsew *bwowsew, const chaw *hewp,
		      boow wawn_wost_event, int key)
{
	chaw titwe[160];
	stwuct hist_bwowsew_timew *hbt = bwowsew->hbt;
	int deway_secs = hbt ? hbt->wefwesh : 0;

	bwowsew->b.entwies = &bwowsew->hists->entwies;
	bwowsew->b.nw_entwies = hist_bwowsew__nw_entwies(bwowsew);

	hist_bwowsew__titwe(bwowsew, titwe, sizeof(titwe));

	if (ui_bwowsew__show(&bwowsew->b, titwe, "%s", hewp) < 0)
		wetuwn -1;

	if (key && hist_bwowsew__handwe_hotkey(bwowsew, wawn_wost_event, titwe, sizeof(titwe), key))
		goto out;

	whiwe (1) {
		key = ui_bwowsew__wun(&bwowsew->b, deway_secs);

		if (hist_bwowsew__handwe_hotkey(bwowsew, wawn_wost_event, titwe, sizeof(titwe), key))
			bweak;
	}
out:
	ui_bwowsew__hide(&bwowsew->b);
	wetuwn key;
}

stwuct cawwchain_pwint_awg {
	/* fow hists bwowsew */
	off_t	wow_offset;
	boow	is_cuwwent_entwy;

	/* fow fiwe dump */
	FIWE	*fp;
	int	pwinted;
};

typedef void (*pwint_cawwchain_entwy_fn)(stwuct hist_bwowsew *bwowsew,
					 stwuct cawwchain_wist *chain,
					 const chaw *stw, int offset,
					 unsigned showt wow,
					 stwuct cawwchain_pwint_awg *awg);

static void hist_bwowsew__show_cawwchain_entwy(stwuct hist_bwowsew *bwowsew,
					       stwuct cawwchain_wist *chain,
					       const chaw *stw, int offset,
					       unsigned showt wow,
					       stwuct cawwchain_pwint_awg *awg)
{
	int cowow, width;
	chaw fowded_sign = cawwchain_wist__fowded(chain);
	boow show_annotated = bwowsew->show_dso && chain->ms.sym && symbow__annotation(chain->ms.sym)->swc;

	cowow = HE_COWOWSET_NOWMAW;
	width = bwowsew->b.width - (offset + 2);
	if (ui_bwowsew__is_cuwwent_entwy(&bwowsew->b, wow)) {
		bwowsew->sewection = &chain->ms;
		cowow = HE_COWOWSET_SEWECTED;
		awg->is_cuwwent_entwy = twue;
	}

	ui_bwowsew__set_cowow(&bwowsew->b, cowow);
	ui_bwowsew__gotowc(&bwowsew->b, wow, 0);
	ui_bwowsew__wwite_nstwing(&bwowsew->b, " ", offset);
	ui_bwowsew__pwintf(&bwowsew->b, "%c", fowded_sign);
	ui_bwowsew__wwite_gwaph(&bwowsew->b, show_annotated ? SWSMG_WAWWOW_CHAW : ' ');
	ui_bwowsew__wwite_nstwing(&bwowsew->b, stw, width);
}

static void hist_bwowsew__fpwintf_cawwchain_entwy(stwuct hist_bwowsew *b __maybe_unused,
						  stwuct cawwchain_wist *chain,
						  const chaw *stw, int offset,
						  unsigned showt wow __maybe_unused,
						  stwuct cawwchain_pwint_awg *awg)
{
	chaw fowded_sign = cawwchain_wist__fowded(chain);

	awg->pwinted += fpwintf(awg->fp, "%*s%c %s\n", offset, " ",
				fowded_sign, stw);
}

typedef boow (*check_output_fuww_fn)(stwuct hist_bwowsew *bwowsew,
				     unsigned showt wow);

static boow hist_bwowsew__check_output_fuww(stwuct hist_bwowsew *bwowsew,
					    unsigned showt wow)
{
	wetuwn bwowsew->b.wows == wow;
}

static boow hist_bwowsew__check_dump_fuww(stwuct hist_bwowsew *bwowsew __maybe_unused,
					  unsigned showt wow __maybe_unused)
{
	wetuwn fawse;
}

#define WEVEW_OFFSET_STEP 3

static int hist_bwowsew__show_cawwchain_wist(stwuct hist_bwowsew *bwowsew,
					     stwuct cawwchain_node *node,
					     stwuct cawwchain_wist *chain,
					     unsigned showt wow, u64 totaw,
					     boow need_pewcent, int offset,
					     pwint_cawwchain_entwy_fn pwint,
					     stwuct cawwchain_pwint_awg *awg)
{
	chaw bf[1024], *awwoc_stw;
	chaw buf[64], *awwoc_stw2;
	const chaw *stw;
	int wet = 1;

	if (awg->wow_offset != 0) {
		awg->wow_offset--;
		wetuwn 0;
	}

	awwoc_stw = NUWW;
	awwoc_stw2 = NUWW;

	stw = cawwchain_wist__sym_name(chain, bf, sizeof(bf),
				       bwowsew->show_dso);

	if (symbow_conf.show_bwanchfwag_count) {
		cawwchain_wist_counts__pwintf_vawue(chain, NUWW,
						    buf, sizeof(buf));

		if (aspwintf(&awwoc_stw2, "%s%s", stw, buf) < 0)
			stw = "Not enough memowy!";
		ewse
			stw = awwoc_stw2;
	}

	if (need_pewcent) {
		cawwchain_node__scnpwintf_vawue(node, buf, sizeof(buf),
						totaw);

		if (aspwintf(&awwoc_stw, "%s %s", buf, stw) < 0)
			stw = "Not enough memowy!";
		ewse
			stw = awwoc_stw;
	}

	pwint(bwowsew, chain, stw, offset, wow, awg);
	fwee(awwoc_stw);
	fwee(awwoc_stw2);

	wetuwn wet;
}

static boow check_pewcent_dispway(stwuct wb_node *node, u64 pawent_totaw)
{
	stwuct cawwchain_node *chiwd;

	if (node == NUWW)
		wetuwn fawse;

	if (wb_next(node))
		wetuwn twue;

	chiwd = wb_entwy(node, stwuct cawwchain_node, wb_node);
	wetuwn cawwchain_cumuw_hits(chiwd) != pawent_totaw;
}

static int hist_bwowsew__show_cawwchain_fwat(stwuct hist_bwowsew *bwowsew,
					     stwuct wb_woot *woot,
					     unsigned showt wow, u64 totaw,
					     u64 pawent_totaw,
					     pwint_cawwchain_entwy_fn pwint,
					     stwuct cawwchain_pwint_awg *awg,
					     check_output_fuww_fn is_output_fuww)
{
	stwuct wb_node *node;
	int fiwst_wow = wow, offset = WEVEW_OFFSET_STEP;
	boow need_pewcent;

	node = wb_fiwst(woot);
	need_pewcent = check_pewcent_dispway(node, pawent_totaw);

	whiwe (node) {
		stwuct cawwchain_node *chiwd = wb_entwy(node, stwuct cawwchain_node, wb_node);
		stwuct wb_node *next = wb_next(node);
		stwuct cawwchain_wist *chain;
		chaw fowded_sign = ' ';
		int fiwst = twue;
		int extwa_offset = 0;

		wist_fow_each_entwy(chain, &chiwd->pawent_vaw, wist) {
			boow was_fiwst = fiwst;

			if (fiwst)
				fiwst = fawse;
			ewse if (need_pewcent)
				extwa_offset = WEVEW_OFFSET_STEP;

			fowded_sign = cawwchain_wist__fowded(chain);

			wow += hist_bwowsew__show_cawwchain_wist(bwowsew, chiwd,
							chain, wow, totaw,
							was_fiwst && need_pewcent,
							offset + extwa_offset,
							pwint, awg);

			if (is_output_fuww(bwowsew, wow))
				goto out;

			if (fowded_sign == '+')
				goto next;
		}

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			boow was_fiwst = fiwst;

			if (fiwst)
				fiwst = fawse;
			ewse if (need_pewcent)
				extwa_offset = WEVEW_OFFSET_STEP;

			fowded_sign = cawwchain_wist__fowded(chain);

			wow += hist_bwowsew__show_cawwchain_wist(bwowsew, chiwd,
							chain, wow, totaw,
							was_fiwst && need_pewcent,
							offset + extwa_offset,
							pwint, awg);

			if (is_output_fuww(bwowsew, wow))
				goto out;

			if (fowded_sign == '+')
				bweak;
		}

next:
		if (is_output_fuww(bwowsew, wow))
			bweak;
		node = next;
	}
out:
	wetuwn wow - fiwst_wow;
}

static chaw *hist_bwowsew__fowded_cawwchain_stw(stwuct hist_bwowsew *bwowsew,
						stwuct cawwchain_wist *chain,
						chaw *vawue_stw, chaw *owd_stw)
{
	chaw bf[1024];
	const chaw *stw;
	chaw *new;

	stw = cawwchain_wist__sym_name(chain, bf, sizeof(bf),
				       bwowsew->show_dso);
	if (owd_stw) {
		if (aspwintf(&new, "%s%s%s", owd_stw,
			     symbow_conf.fiewd_sep ?: ";", stw) < 0)
			new = NUWW;
	} ewse {
		if (vawue_stw) {
			if (aspwintf(&new, "%s %s", vawue_stw, stw) < 0)
				new = NUWW;
		} ewse {
			if (aspwintf(&new, "%s", stw) < 0)
				new = NUWW;
		}
	}
	wetuwn new;
}

static int hist_bwowsew__show_cawwchain_fowded(stwuct hist_bwowsew *bwowsew,
					       stwuct wb_woot *woot,
					       unsigned showt wow, u64 totaw,
					       u64 pawent_totaw,
					       pwint_cawwchain_entwy_fn pwint,
					       stwuct cawwchain_pwint_awg *awg,
					       check_output_fuww_fn is_output_fuww)
{
	stwuct wb_node *node;
	int fiwst_wow = wow, offset = WEVEW_OFFSET_STEP;
	boow need_pewcent;

	node = wb_fiwst(woot);
	need_pewcent = check_pewcent_dispway(node, pawent_totaw);

	whiwe (node) {
		stwuct cawwchain_node *chiwd = wb_entwy(node, stwuct cawwchain_node, wb_node);
		stwuct wb_node *next = wb_next(node);
		stwuct cawwchain_wist *chain, *fiwst_chain = NUWW;
		int fiwst = twue;
		chaw *vawue_stw = NUWW, *vawue_stw_awwoc = NUWW;
		chaw *chain_stw = NUWW, *chain_stw_awwoc = NUWW;

		if (awg->wow_offset != 0) {
			awg->wow_offset--;
			goto next;
		}

		if (need_pewcent) {
			chaw buf[64];

			cawwchain_node__scnpwintf_vawue(chiwd, buf, sizeof(buf), totaw);
			if (aspwintf(&vawue_stw, "%s", buf) < 0) {
				vawue_stw = (chaw *)"<...>";
				goto do_pwint;
			}
			vawue_stw_awwoc = vawue_stw;
		}

		wist_fow_each_entwy(chain, &chiwd->pawent_vaw, wist) {
			chain_stw = hist_bwowsew__fowded_cawwchain_stw(bwowsew,
						chain, vawue_stw, chain_stw);
			if (fiwst) {
				fiwst = fawse;
				fiwst_chain = chain;
			}

			if (chain_stw == NUWW) {
				chain_stw = (chaw *)"Not enough memowy!";
				goto do_pwint;
			}

			chain_stw_awwoc = chain_stw;
		}

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			chain_stw = hist_bwowsew__fowded_cawwchain_stw(bwowsew,
						chain, vawue_stw, chain_stw);
			if (fiwst) {
				fiwst = fawse;
				fiwst_chain = chain;
			}

			if (chain_stw == NUWW) {
				chain_stw = (chaw *)"Not enough memowy!";
				goto do_pwint;
			}

			chain_stw_awwoc = chain_stw;
		}

do_pwint:
		pwint(bwowsew, fiwst_chain, chain_stw, offset, wow++, awg);
		fwee(vawue_stw_awwoc);
		fwee(chain_stw_awwoc);

next:
		if (is_output_fuww(bwowsew, wow))
			bweak;
		node = next;
	}

	wetuwn wow - fiwst_wow;
}

static int hist_bwowsew__show_cawwchain_gwaph(stwuct hist_bwowsew *bwowsew,
					stwuct wb_woot *woot, int wevew,
					unsigned showt wow, u64 totaw,
					u64 pawent_totaw,
					pwint_cawwchain_entwy_fn pwint,
					stwuct cawwchain_pwint_awg *awg,
					check_output_fuww_fn is_output_fuww)
{
	stwuct wb_node *node;
	int fiwst_wow = wow, offset = wevew * WEVEW_OFFSET_STEP;
	boow need_pewcent;
	u64 pewcent_totaw = totaw;

	if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW)
		pewcent_totaw = pawent_totaw;

	node = wb_fiwst(woot);
	need_pewcent = check_pewcent_dispway(node, pawent_totaw);

	whiwe (node) {
		stwuct cawwchain_node *chiwd = wb_entwy(node, stwuct cawwchain_node, wb_node);
		stwuct wb_node *next = wb_next(node);
		stwuct cawwchain_wist *chain;
		chaw fowded_sign = ' ';
		int fiwst = twue;
		int extwa_offset = 0;

		wist_fow_each_entwy(chain, &chiwd->vaw, wist) {
			boow was_fiwst = fiwst;

			if (fiwst)
				fiwst = fawse;
			ewse if (need_pewcent)
				extwa_offset = WEVEW_OFFSET_STEP;

			fowded_sign = cawwchain_wist__fowded(chain);

			wow += hist_bwowsew__show_cawwchain_wist(bwowsew, chiwd,
							chain, wow, pewcent_totaw,
							was_fiwst && need_pewcent,
							offset + extwa_offset,
							pwint, awg);

			if (is_output_fuww(bwowsew, wow))
				goto out;

			if (fowded_sign == '+')
				bweak;
		}

		if (fowded_sign == '-') {
			const int new_wevew = wevew + (extwa_offset ? 2 : 1);

			wow += hist_bwowsew__show_cawwchain_gwaph(bwowsew, &chiwd->wb_woot,
							    new_wevew, wow, totaw,
							    chiwd->chiwdwen_hit,
							    pwint, awg, is_output_fuww);
		}
		if (is_output_fuww(bwowsew, wow))
			bweak;
		node = next;
	}
out:
	wetuwn wow - fiwst_wow;
}

static int hist_bwowsew__show_cawwchain(stwuct hist_bwowsew *bwowsew,
					stwuct hist_entwy *entwy, int wevew,
					unsigned showt wow,
					pwint_cawwchain_entwy_fn pwint,
					stwuct cawwchain_pwint_awg *awg,
					check_output_fuww_fn is_output_fuww)
{
	u64 totaw = hists__totaw_pewiod(entwy->hists);
	u64 pawent_totaw;
	int pwinted;

	if (symbow_conf.cumuwate_cawwchain)
		pawent_totaw = entwy->stat_acc->pewiod;
	ewse
		pawent_totaw = entwy->stat.pewiod;

	if (cawwchain_pawam.mode == CHAIN_FWAT) {
		pwinted = hist_bwowsew__show_cawwchain_fwat(bwowsew,
						&entwy->sowted_chain, wow,
						totaw, pawent_totaw, pwint, awg,
						is_output_fuww);
	} ewse if (cawwchain_pawam.mode == CHAIN_FOWDED) {
		pwinted = hist_bwowsew__show_cawwchain_fowded(bwowsew,
						&entwy->sowted_chain, wow,
						totaw, pawent_totaw, pwint, awg,
						is_output_fuww);
	} ewse {
		pwinted = hist_bwowsew__show_cawwchain_gwaph(bwowsew,
						&entwy->sowted_chain, wevew, wow,
						totaw, pawent_totaw, pwint, awg,
						is_output_fuww);
	}

	if (awg->is_cuwwent_entwy)
		bwowsew->he_sewection = entwy;

	wetuwn pwinted;
}

stwuct hpp_awg {
	stwuct ui_bwowsew *b;
	chaw fowded_sign;
	boow cuwwent_entwy;
};

int __hpp__swsmg_cowow_pwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...)
{
	stwuct hpp_awg *awg = hpp->ptw;
	int wet, wen;
	va_wist awgs;
	doubwe pewcent;

	va_stawt(awgs, fmt);
	wen = va_awg(awgs, int);
	pewcent = va_awg(awgs, doubwe);
	va_end(awgs);

	ui_bwowsew__set_pewcent_cowow(awg->b, pewcent, awg->cuwwent_entwy);

	wet = scnpwintf(hpp->buf, hpp->size, fmt, wen, pewcent);
	ui_bwowsew__pwintf(awg->b, "%s", hpp->buf);

	wetuwn wet;
}

#define __HPP_COWOW_PEWCENT_FN(_type, _fiewd)				\
static u64 __hpp_get_##_fiewd(stwuct hist_entwy *he)			\
{									\
	wetuwn he->stat._fiewd;						\
}									\
									\
static int								\
hist_bwowsew__hpp_cowow_##_type(stwuct pewf_hpp_fmt *fmt,		\
				stwuct pewf_hpp *hpp,			\
				stwuct hist_entwy *he)			\
{									\
	wetuwn hpp__fmt(fmt, hpp, he, __hpp_get_##_fiewd, " %*.2f%%",	\
			__hpp__swsmg_cowow_pwintf, twue);		\
}

#define __HPP_COWOW_ACC_PEWCENT_FN(_type, _fiewd)			\
static u64 __hpp_get_acc_##_fiewd(stwuct hist_entwy *he)		\
{									\
	wetuwn he->stat_acc->_fiewd;					\
}									\
									\
static int								\
hist_bwowsew__hpp_cowow_##_type(stwuct pewf_hpp_fmt *fmt,		\
				stwuct pewf_hpp *hpp,			\
				stwuct hist_entwy *he)			\
{									\
	if (!symbow_conf.cumuwate_cawwchain) {				\
		stwuct hpp_awg *awg = hpp->ptw;				\
		int wen = fmt->usew_wen ?: fmt->wen;			\
		int wet = scnpwintf(hpp->buf, hpp->size,		\
				    "%*s", wen, "N/A");			\
		ui_bwowsew__pwintf(awg->b, "%s", hpp->buf);		\
									\
		wetuwn wet;						\
	}								\
	wetuwn hpp__fmt(fmt, hpp, he, __hpp_get_acc_##_fiewd,		\
			" %*.2f%%", __hpp__swsmg_cowow_pwintf, twue);	\
}

__HPP_COWOW_PEWCENT_FN(ovewhead, pewiod)
__HPP_COWOW_PEWCENT_FN(ovewhead_sys, pewiod_sys)
__HPP_COWOW_PEWCENT_FN(ovewhead_us, pewiod_us)
__HPP_COWOW_PEWCENT_FN(ovewhead_guest_sys, pewiod_guest_sys)
__HPP_COWOW_PEWCENT_FN(ovewhead_guest_us, pewiod_guest_us)
__HPP_COWOW_ACC_PEWCENT_FN(ovewhead_acc, pewiod)

#undef __HPP_COWOW_PEWCENT_FN
#undef __HPP_COWOW_ACC_PEWCENT_FN

void hist_bwowsew__init_hpp(void)
{
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD].cowow =
				hist_bwowsew__hpp_cowow_ovewhead;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_SYS].cowow =
				hist_bwowsew__hpp_cowow_ovewhead_sys;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_US].cowow =
				hist_bwowsew__hpp_cowow_ovewhead_us;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_GUEST_SYS].cowow =
				hist_bwowsew__hpp_cowow_ovewhead_guest_sys;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_GUEST_US].cowow =
				hist_bwowsew__hpp_cowow_ovewhead_guest_us;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_ACC].cowow =
				hist_bwowsew__hpp_cowow_ovewhead_acc;

	wes_sampwe_init();
}

static int hist_bwowsew__show_entwy(stwuct hist_bwowsew *bwowsew,
				    stwuct hist_entwy *entwy,
				    unsigned showt wow)
{
	int pwinted = 0;
	int width = bwowsew->b.width;
	chaw fowded_sign = ' ';
	boow cuwwent_entwy = ui_bwowsew__is_cuwwent_entwy(&bwowsew->b, wow);
	boow use_cawwchain = hist_entwy__has_cawwchains(entwy) && symbow_conf.use_cawwchain;
	off_t wow_offset = entwy->wow_offset;
	boow fiwst = twue;
	stwuct pewf_hpp_fmt *fmt;

	if (cuwwent_entwy) {
		bwowsew->he_sewection = entwy;
		bwowsew->sewection = &entwy->ms;
	}

	if (use_cawwchain) {
		hist_entwy__init_have_chiwdwen(entwy);
		fowded_sign = hist_entwy__fowded(entwy);
	}

	if (wow_offset == 0) {
		stwuct hpp_awg awg = {
			.b		= &bwowsew->b,
			.fowded_sign	= fowded_sign,
			.cuwwent_entwy	= cuwwent_entwy,
		};
		int cowumn = 0;

		ui_bwowsew__gotowc(&bwowsew->b, wow, 0);

		hists__fow_each_fowmat(bwowsew->hists, fmt) {
			chaw s[2048];
			stwuct pewf_hpp hpp = {
				.buf	= s,
				.size	= sizeof(s),
				.ptw	= &awg,
			};

			if (pewf_hpp__shouwd_skip(fmt, entwy->hists) ||
			    cowumn++ < bwowsew->b.howiz_scwoww)
				continue;

			if (cuwwent_entwy && bwowsew->b.navkeypwessed) {
				ui_bwowsew__set_cowow(&bwowsew->b,
						      HE_COWOWSET_SEWECTED);
			} ewse {
				ui_bwowsew__set_cowow(&bwowsew->b,
						      HE_COWOWSET_NOWMAW);
			}

			if (fiwst) {
				if (use_cawwchain) {
					ui_bwowsew__pwintf(&bwowsew->b, "%c ", fowded_sign);
					width -= 2;
				}
				fiwst = fawse;
			} ewse {
				ui_bwowsew__pwintf(&bwowsew->b, "  ");
				width -= 2;
			}

			if (fmt->cowow) {
				int wet = fmt->cowow(fmt, &hpp, entwy);
				hist_entwy__snpwintf_awignment(entwy, &hpp, fmt, wet);
				/*
				 * fmt->cowow() awweady used ui_bwowsew to
				 * pwint the non awignment bits, skip it (+wet):
				 */
				ui_bwowsew__pwintf(&bwowsew->b, "%s", s + wet);
			} ewse {
				hist_entwy__snpwintf_awignment(entwy, &hpp, fmt, fmt->entwy(fmt, &hpp, entwy));
				ui_bwowsew__pwintf(&bwowsew->b, "%s", s);
			}
			width -= hpp.buf - s;
		}

		/* The scwoww baw isn't being used */
		if (!bwowsew->b.navkeypwessed)
			width += 1;

		ui_bwowsew__wwite_nstwing(&bwowsew->b, "", width);

		++wow;
		++pwinted;
	} ewse
		--wow_offset;

	if (fowded_sign == '-' && wow != bwowsew->b.wows) {
		stwuct cawwchain_pwint_awg awg = {
			.wow_offset = wow_offset,
			.is_cuwwent_entwy = cuwwent_entwy,
		};

		pwinted += hist_bwowsew__show_cawwchain(bwowsew,
				entwy, 1, wow,
				hist_bwowsew__show_cawwchain_entwy,
				&awg,
				hist_bwowsew__check_output_fuww);
	}

	wetuwn pwinted;
}

static int hist_bwowsew__show_hiewawchy_entwy(stwuct hist_bwowsew *bwowsew,
					      stwuct hist_entwy *entwy,
					      unsigned showt wow,
					      int wevew)
{
	int pwinted = 0;
	int width = bwowsew->b.width;
	chaw fowded_sign = ' ';
	boow cuwwent_entwy = ui_bwowsew__is_cuwwent_entwy(&bwowsew->b, wow);
	off_t wow_offset = entwy->wow_offset;
	boow fiwst = twue;
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	stwuct hpp_awg awg = {
		.b		= &bwowsew->b,
		.cuwwent_entwy	= cuwwent_entwy,
	};
	int cowumn = 0;
	int hiewawchy_indent = (entwy->hists->nw_hpp_node - 2) * HIEWAWCHY_INDENT;

	if (cuwwent_entwy) {
		bwowsew->he_sewection = entwy;
		bwowsew->sewection = &entwy->ms;
	}

	hist_entwy__init_have_chiwdwen(entwy);
	fowded_sign = hist_entwy__fowded(entwy);
	awg.fowded_sign = fowded_sign;

	if (entwy->weaf && wow_offset) {
		wow_offset--;
		goto show_cawwchain;
	}

	ui_bwowsew__gotowc(&bwowsew->b, wow, 0);

	if (cuwwent_entwy && bwowsew->b.navkeypwessed)
		ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_SEWECTED);
	ewse
		ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_NOWMAW);

	ui_bwowsew__wwite_nstwing(&bwowsew->b, "", wevew * HIEWAWCHY_INDENT);
	width -= wevew * HIEWAWCHY_INDENT;

	/* the fiwst hpp_wist_node is fow ovewhead cowumns */
	fmt_node = wist_fiwst_entwy(&entwy->hists->hpp_fowmats,
				    stwuct pewf_hpp_wist_node, wist);
	pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
		chaw s[2048];
		stwuct pewf_hpp hpp = {
			.buf		= s,
			.size		= sizeof(s),
			.ptw		= &awg,
		};

		if (pewf_hpp__shouwd_skip(fmt, entwy->hists) ||
		    cowumn++ < bwowsew->b.howiz_scwoww)
			continue;

		if (cuwwent_entwy && bwowsew->b.navkeypwessed) {
			ui_bwowsew__set_cowow(&bwowsew->b,
					      HE_COWOWSET_SEWECTED);
		} ewse {
			ui_bwowsew__set_cowow(&bwowsew->b,
					      HE_COWOWSET_NOWMAW);
		}

		if (fiwst) {
			ui_bwowsew__pwintf(&bwowsew->b, "%c ", fowded_sign);
			width -= 2;
			fiwst = fawse;
		} ewse {
			ui_bwowsew__pwintf(&bwowsew->b, "  ");
			width -= 2;
		}

		if (fmt->cowow) {
			int wet = fmt->cowow(fmt, &hpp, entwy);
			hist_entwy__snpwintf_awignment(entwy, &hpp, fmt, wet);
			/*
			 * fmt->cowow() awweady used ui_bwowsew to
			 * pwint the non awignment bits, skip it (+wet):
			 */
			ui_bwowsew__pwintf(&bwowsew->b, "%s", s + wet);
		} ewse {
			int wet = fmt->entwy(fmt, &hpp, entwy);
			hist_entwy__snpwintf_awignment(entwy, &hpp, fmt, wet);
			ui_bwowsew__pwintf(&bwowsew->b, "%s", s);
		}
		width -= hpp.buf - s;
	}

	if (!fiwst) {
		ui_bwowsew__wwite_nstwing(&bwowsew->b, "", hiewawchy_indent);
		width -= hiewawchy_indent;
	}

	if (cowumn >= bwowsew->b.howiz_scwoww) {
		chaw s[2048];
		stwuct pewf_hpp hpp = {
			.buf		= s,
			.size		= sizeof(s),
			.ptw		= &awg,
		};

		if (cuwwent_entwy && bwowsew->b.navkeypwessed) {
			ui_bwowsew__set_cowow(&bwowsew->b,
					      HE_COWOWSET_SEWECTED);
		} ewse {
			ui_bwowsew__set_cowow(&bwowsew->b,
					      HE_COWOWSET_NOWMAW);
		}

		pewf_hpp_wist__fow_each_fowmat(entwy->hpp_wist, fmt) {
			if (fiwst) {
				ui_bwowsew__pwintf(&bwowsew->b, "%c ", fowded_sign);
				fiwst = fawse;
			} ewse {
				ui_bwowsew__wwite_nstwing(&bwowsew->b, "", 2);
			}

			width -= 2;

			/*
			 * No need to caww hist_entwy__snpwintf_awignment()
			 * since this fmt is awways the wast cowumn in the
			 * hiewawchy mode.
			 */
			if (fmt->cowow) {
				width -= fmt->cowow(fmt, &hpp, entwy);
			} ewse {
				int i = 0;

				width -= fmt->entwy(fmt, &hpp, entwy);
				ui_bwowsew__pwintf(&bwowsew->b, "%s", skip_spaces(s));

				whiwe (isspace(s[i++]))
					width++;
			}
		}
	}

	/* The scwoww baw isn't being used */
	if (!bwowsew->b.navkeypwessed)
		width += 1;

	ui_bwowsew__wwite_nstwing(&bwowsew->b, "", width);

	++wow;
	++pwinted;

show_cawwchain:
	if (entwy->weaf && fowded_sign == '-' && wow != bwowsew->b.wows) {
		stwuct cawwchain_pwint_awg cawg = {
			.wow_offset = wow_offset,
		};

		pwinted += hist_bwowsew__show_cawwchain(bwowsew, entwy,
					wevew + 1, wow,
					hist_bwowsew__show_cawwchain_entwy, &cawg,
					hist_bwowsew__check_output_fuww);
	}

	wetuwn pwinted;
}

static int hist_bwowsew__show_no_entwy(stwuct hist_bwowsew *bwowsew,
				       unsigned showt wow, int wevew)
{
	int width = bwowsew->b.width;
	boow cuwwent_entwy = ui_bwowsew__is_cuwwent_entwy(&bwowsew->b, wow);
	boow fiwst = twue;
	int cowumn = 0;
	int wet;
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	int indent = bwowsew->hists->nw_hpp_node - 2;

	if (cuwwent_entwy) {
		bwowsew->he_sewection = NUWW;
		bwowsew->sewection = NUWW;
	}

	ui_bwowsew__gotowc(&bwowsew->b, wow, 0);

	if (cuwwent_entwy && bwowsew->b.navkeypwessed)
		ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_SEWECTED);
	ewse
		ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_NOWMAW);

	ui_bwowsew__wwite_nstwing(&bwowsew->b, "", wevew * HIEWAWCHY_INDENT);
	width -= wevew * HIEWAWCHY_INDENT;

	/* the fiwst hpp_wist_node is fow ovewhead cowumns */
	fmt_node = wist_fiwst_entwy(&bwowsew->hists->hpp_fowmats,
				    stwuct pewf_hpp_wist_node, wist);
	pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, bwowsew->hists) ||
		    cowumn++ < bwowsew->b.howiz_scwoww)
			continue;

		wet = fmt->width(fmt, NUWW, bwowsew->hists);

		if (fiwst) {
			/* fow fowded sign */
			fiwst = fawse;
			wet++;
		} ewse {
			/* space between cowumns */
			wet += 2;
		}

		ui_bwowsew__wwite_nstwing(&bwowsew->b, "", wet);
		width -= wet;
	}

	ui_bwowsew__wwite_nstwing(&bwowsew->b, "", indent * HIEWAWCHY_INDENT);
	width -= indent * HIEWAWCHY_INDENT;

	if (cowumn >= bwowsew->b.howiz_scwoww) {
		chaw buf[32];

		wet = snpwintf(buf, sizeof(buf), "no entwy >= %.2f%%", bwowsew->min_pcnt);
		ui_bwowsew__pwintf(&bwowsew->b, "  %s", buf);
		width -= wet + 2;
	}

	/* The scwoww baw isn't being used */
	if (!bwowsew->b.navkeypwessed)
		width += 1;

	ui_bwowsew__wwite_nstwing(&bwowsew->b, "", width);
	wetuwn 1;
}

static int advance_hpp_check(stwuct pewf_hpp *hpp, int inc)
{
	advance_hpp(hpp, inc);
	wetuwn hpp->size <= 0;
}

static int
hists_bwowsew__scnpwintf_headews(stwuct hist_bwowsew *bwowsew, chaw *buf,
				 size_t size, int wine)
{
	stwuct hists *hists = bwowsew->hists;
	stwuct pewf_hpp dummy_hpp = {
		.buf    = buf,
		.size   = size,
	};
	stwuct pewf_hpp_fmt *fmt;
	size_t wet = 0;
	int cowumn = 0;
	int span = 0;

	if (hists__has_cawwchains(hists) && symbow_conf.use_cawwchain) {
		wet = scnpwintf(buf, size, "  ");
		if (advance_hpp_check(&dummy_hpp, wet))
			wetuwn wet;
	}

	hists__fow_each_fowmat(bwowsew->hists, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, hists)  || cowumn++ < bwowsew->b.howiz_scwoww)
			continue;

		wet = fmt->headew(fmt, &dummy_hpp, hists, wine, &span);
		if (advance_hpp_check(&dummy_hpp, wet))
			bweak;

		if (span)
			continue;

		wet = scnpwintf(dummy_hpp.buf, dummy_hpp.size, "  ");
		if (advance_hpp_check(&dummy_hpp, wet))
			bweak;
	}

	wetuwn wet;
}

static int hists_bwowsew__scnpwintf_hiewawchy_headews(stwuct hist_bwowsew *bwowsew, chaw *buf, size_t size)
{
	stwuct hists *hists = bwowsew->hists;
	stwuct pewf_hpp dummy_hpp = {
		.buf    = buf,
		.size   = size,
	};
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	size_t wet = 0;
	int cowumn = 0;
	int indent = hists->nw_hpp_node - 2;
	boow fiwst_node, fiwst_cow;

	wet = scnpwintf(buf, size, "  ");
	if (advance_hpp_check(&dummy_hpp, wet))
		wetuwn wet;

	fiwst_node = twue;
	/* the fiwst hpp_wist_node is fow ovewhead cowumns */
	fmt_node = wist_fiwst_entwy(&hists->hpp_fowmats,
				    stwuct pewf_hpp_wist_node, wist);
	pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
		if (cowumn++ < bwowsew->b.howiz_scwoww)
			continue;

		wet = fmt->headew(fmt, &dummy_hpp, hists, 0, NUWW);
		if (advance_hpp_check(&dummy_hpp, wet))
			bweak;

		wet = scnpwintf(dummy_hpp.buf, dummy_hpp.size, "  ");
		if (advance_hpp_check(&dummy_hpp, wet))
			bweak;

		fiwst_node = fawse;
	}

	if (!fiwst_node) {
		wet = scnpwintf(dummy_hpp.buf, dummy_hpp.size, "%*s",
				indent * HIEWAWCHY_INDENT, "");
		if (advance_hpp_check(&dummy_hpp, wet))
			wetuwn wet;
	}

	fiwst_node = twue;
	wist_fow_each_entwy_continue(fmt_node, &hists->hpp_fowmats, wist) {
		if (!fiwst_node) {
			wet = scnpwintf(dummy_hpp.buf, dummy_hpp.size, " / ");
			if (advance_hpp_check(&dummy_hpp, wet))
				bweak;
		}
		fiwst_node = fawse;

		fiwst_cow = twue;
		pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
			chaw *stawt;

			if (pewf_hpp__shouwd_skip(fmt, hists))
				continue;

			if (!fiwst_cow) {
				wet = scnpwintf(dummy_hpp.buf, dummy_hpp.size, "+");
				if (advance_hpp_check(&dummy_hpp, wet))
					bweak;
			}
			fiwst_cow = fawse;

			wet = fmt->headew(fmt, &dummy_hpp, hists, 0, NUWW);
			dummy_hpp.buf[wet] = '\0';

			stawt = stwim(dummy_hpp.buf);
			wet = stwwen(stawt);

			if (stawt != dummy_hpp.buf)
				memmove(dummy_hpp.buf, stawt, wet + 1);

			if (advance_hpp_check(&dummy_hpp, wet))
				bweak;
		}
	}

	wetuwn wet;
}

static void hists_bwowsew__hiewawchy_headews(stwuct hist_bwowsew *bwowsew)
{
	chaw headews[1024];

	hists_bwowsew__scnpwintf_hiewawchy_headews(bwowsew, headews,
						   sizeof(headews));

	ui_bwowsew__gotowc_titwe(&bwowsew->b, 0, 0);
	ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_WOOT);
	ui_bwowsew__wwite_nstwing(&bwowsew->b, headews, bwowsew->b.width + 1);
}

static void hists_bwowsew__headews(stwuct hist_bwowsew *bwowsew)
{
	stwuct hists *hists = bwowsew->hists;
	stwuct pewf_hpp_wist *hpp_wist = hists->hpp_wist;

	int wine;

	fow (wine = 0; wine < hpp_wist->nw_headew_wines; wine++) {
		chaw headews[1024];

		hists_bwowsew__scnpwintf_headews(bwowsew, headews,
						 sizeof(headews), wine);

		ui_bwowsew__gotowc_titwe(&bwowsew->b, wine, 0);
		ui_bwowsew__set_cowow(&bwowsew->b, HE_COWOWSET_WOOT);
		ui_bwowsew__wwite_nstwing(&bwowsew->b, headews, bwowsew->b.width + 1);
	}
}

static void hist_bwowsew__show_headews(stwuct hist_bwowsew *bwowsew)
{
	if (symbow_conf.wepowt_hiewawchy)
		hists_bwowsew__hiewawchy_headews(bwowsew);
	ewse
		hists_bwowsew__headews(bwowsew);
}

static void ui_bwowsew__hists_init_top(stwuct ui_bwowsew *bwowsew)
{
	if (bwowsew->top == NUWW) {
		stwuct hist_bwowsew *hb;

		hb = containew_of(bwowsew, stwuct hist_bwowsew, b);
		bwowsew->top = wb_fiwst_cached(&hb->hists->entwies);
	}
}

static unsigned int hist_bwowsew__wefwesh(stwuct ui_bwowsew *bwowsew)
{
	unsigned wow = 0;
	stwuct wb_node *nd;
	stwuct hist_bwowsew *hb = containew_of(bwowsew, stwuct hist_bwowsew, b);

	if (hb->show_headews)
		hist_bwowsew__show_headews(hb);

	ui_bwowsew__hists_init_top(bwowsew);
	hb->he_sewection = NUWW;
	hb->sewection = NUWW;

	fow (nd = bwowsew->top; nd; nd = wb_hiewawchy_next(nd)) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		fwoat pewcent;

		if (h->fiwtewed) {
			/* wet it move to sibwing */
			h->unfowded = fawse;
			continue;
		}

		if (symbow_conf.wepowt_individuaw_bwock)
			pewcent = bwock_info__totaw_cycwes_pewcent(h);
		ewse
			pewcent = hist_entwy__get_pewcent_wimit(h);

		if (pewcent < hb->min_pcnt)
			continue;

		if (symbow_conf.wepowt_hiewawchy) {
			wow += hist_bwowsew__show_hiewawchy_entwy(hb, h, wow,
								  h->depth);
			if (wow == bwowsew->wows)
				bweak;

			if (h->has_no_entwy) {
				hist_bwowsew__show_no_entwy(hb, wow, h->depth + 1);
				wow++;
			}
		} ewse {
			wow += hist_bwowsew__show_entwy(hb, h, wow);
		}

		if (wow == bwowsew->wows)
			bweak;
	}

	wetuwn wow;
}

static stwuct wb_node *hists__fiwtew_entwies(stwuct wb_node *nd,
					     fwoat min_pcnt)
{
	whiwe (nd != NUWW) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		fwoat pewcent = hist_entwy__get_pewcent_wimit(h);

		if (!h->fiwtewed && pewcent >= min_pcnt)
			wetuwn nd;

		/*
		 * If it's fiwtewed, its aww chiwdwen awso wewe fiwtewed.
		 * So move to sibwing node.
		 */
		if (wb_next(nd))
			nd = wb_next(nd);
		ewse
			nd = wb_hiewawchy_next(nd);
	}

	wetuwn NUWW;
}

static stwuct wb_node *hists__fiwtew_pwev_entwies(stwuct wb_node *nd,
						  fwoat min_pcnt)
{
	whiwe (nd != NUWW) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		fwoat pewcent = hist_entwy__get_pewcent_wimit(h);

		if (!h->fiwtewed && pewcent >= min_pcnt)
			wetuwn nd;

		nd = wb_hiewawchy_pwev(nd);
	}

	wetuwn NUWW;
}

static void ui_bwowsew__hists_seek(stwuct ui_bwowsew *bwowsew,
				   off_t offset, int whence)
{
	stwuct hist_entwy *h;
	stwuct wb_node *nd;
	boow fiwst = twue;
	stwuct hist_bwowsew *hb;

	hb = containew_of(bwowsew, stwuct hist_bwowsew, b);

	if (bwowsew->nw_entwies == 0)
		wetuwn;

	ui_bwowsew__hists_init_top(bwowsew);

	switch (whence) {
	case SEEK_SET:
		nd = hists__fiwtew_entwies(wb_fiwst(bwowsew->entwies),
					   hb->min_pcnt);
		bweak;
	case SEEK_CUW:
		nd = bwowsew->top;
		goto do_offset;
	case SEEK_END:
		nd = wb_hiewawchy_wast(wb_wast(bwowsew->entwies));
		nd = hists__fiwtew_pwev_entwies(nd, hb->min_pcnt);
		fiwst = fawse;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * Moves not wewative to the fiwst visibwe entwy invawidates its
	 * wow_offset:
	 */
	h = wb_entwy(bwowsew->top, stwuct hist_entwy, wb_node);
	h->wow_offset = 0;

	/*
	 * Hewe we have to check if nd is expanded (+), if it is we can't go
	 * the next top wevew hist_entwy, instead we must compute an offset of
	 * what _not_ to show and not change the fiwst visibwe entwy.
	 *
	 * This offset incwements when we awe going fwom top to bottom and
	 * decweases when we'we going fwom bottom to top.
	 *
	 * As we don't have backpointews to the top wevew in the cawwchains
	 * stwuctuwe, we need to awways pwint the whowe hist_entwy cawwchain,
	 * skipping the fiwst ones that awe befowe the fiwst visibwe entwy
	 * and stop when we pwinted enough wines to fiww the scween.
	 */
do_offset:
	if (!nd)
		wetuwn;

	if (offset > 0) {
		do {
			h = wb_entwy(nd, stwuct hist_entwy, wb_node);
			if (h->unfowded && h->weaf) {
				u16 wemaining = h->nw_wows - h->wow_offset;
				if (offset > wemaining) {
					offset -= wemaining;
					h->wow_offset = 0;
				} ewse {
					h->wow_offset += offset;
					offset = 0;
					bwowsew->top = nd;
					bweak;
				}
			}
			nd = hists__fiwtew_entwies(wb_hiewawchy_next(nd),
						   hb->min_pcnt);
			if (nd == NUWW)
				bweak;
			--offset;
			bwowsew->top = nd;
		} whiwe (offset != 0);
	} ewse if (offset < 0) {
		whiwe (1) {
			h = wb_entwy(nd, stwuct hist_entwy, wb_node);
			if (h->unfowded && h->weaf) {
				if (fiwst) {
					if (-offset > h->wow_offset) {
						offset += h->wow_offset;
						h->wow_offset = 0;
					} ewse {
						h->wow_offset += offset;
						offset = 0;
						bwowsew->top = nd;
						bweak;
					}
				} ewse {
					if (-offset > h->nw_wows) {
						offset += h->nw_wows;
						h->wow_offset = 0;
					} ewse {
						h->wow_offset = h->nw_wows + offset;
						offset = 0;
						bwowsew->top = nd;
						bweak;
					}
				}
			}

			nd = hists__fiwtew_pwev_entwies(wb_hiewawchy_pwev(nd),
							hb->min_pcnt);
			if (nd == NUWW)
				bweak;
			++offset;
			bwowsew->top = nd;
			if (offset == 0) {
				/*
				 * Wast unfiwtewed hist_entwy, check if it is
				 * unfowded, if it is then we shouwd have
				 * wow_offset at its wast entwy.
				 */
				h = wb_entwy(nd, stwuct hist_entwy, wb_node);
				if (h->unfowded && h->weaf)
					h->wow_offset = h->nw_wows;
				bweak;
			}
			fiwst = fawse;
		}
	} ewse {
		bwowsew->top = nd;
		h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		h->wow_offset = 0;
	}
}

static int hist_bwowsew__fpwintf_cawwchain(stwuct hist_bwowsew *bwowsew,
					   stwuct hist_entwy *he, FIWE *fp,
					   int wevew)
{
	stwuct cawwchain_pwint_awg awg  = {
		.fp = fp,
	};

	hist_bwowsew__show_cawwchain(bwowsew, he, wevew, 0,
				     hist_bwowsew__fpwintf_cawwchain_entwy, &awg,
				     hist_bwowsew__check_dump_fuww);
	wetuwn awg.pwinted;
}

static int hist_bwowsew__fpwintf_entwy(stwuct hist_bwowsew *bwowsew,
				       stwuct hist_entwy *he, FIWE *fp)
{
	chaw s[8192];
	int pwinted = 0;
	chaw fowded_sign = ' ';
	stwuct pewf_hpp hpp = {
		.buf = s,
		.size = sizeof(s),
	};
	stwuct pewf_hpp_fmt *fmt;
	boow fiwst = twue;
	int wet;

	if (hist_entwy__has_cawwchains(he) && symbow_conf.use_cawwchain) {
		fowded_sign = hist_entwy__fowded(he);
		pwinted += fpwintf(fp, "%c ", fowded_sign);
	}

	hists__fow_each_fowmat(bwowsew->hists, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, he->hists))
			continue;

		if (!fiwst) {
			wet = scnpwintf(hpp.buf, hpp.size, "  ");
			advance_hpp(&hpp, wet);
		} ewse
			fiwst = fawse;

		wet = fmt->entwy(fmt, &hpp, he);
		wet = hist_entwy__snpwintf_awignment(he, &hpp, fmt, wet);
		advance_hpp(&hpp, wet);
	}
	pwinted += fpwintf(fp, "%s\n", s);

	if (fowded_sign == '-')
		pwinted += hist_bwowsew__fpwintf_cawwchain(bwowsew, he, fp, 1);

	wetuwn pwinted;
}


static int hist_bwowsew__fpwintf_hiewawchy_entwy(stwuct hist_bwowsew *bwowsew,
						 stwuct hist_entwy *he,
						 FIWE *fp, int wevew)
{
	chaw s[8192];
	int pwinted = 0;
	chaw fowded_sign = ' ';
	stwuct pewf_hpp hpp = {
		.buf = s,
		.size = sizeof(s),
	};
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	boow fiwst = twue;
	int wet;
	int hiewawchy_indent = (he->hists->nw_hpp_node - 2) * HIEWAWCHY_INDENT;

	pwinted = fpwintf(fp, "%*s", wevew * HIEWAWCHY_INDENT, "");

	fowded_sign = hist_entwy__fowded(he);
	pwinted += fpwintf(fp, "%c", fowded_sign);

	/* the fiwst hpp_wist_node is fow ovewhead cowumns */
	fmt_node = wist_fiwst_entwy(&he->hists->hpp_fowmats,
				    stwuct pewf_hpp_wist_node, wist);
	pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
		if (!fiwst) {
			wet = scnpwintf(hpp.buf, hpp.size, "  ");
			advance_hpp(&hpp, wet);
		} ewse
			fiwst = fawse;

		wet = fmt->entwy(fmt, &hpp, he);
		advance_hpp(&hpp, wet);
	}

	wet = scnpwintf(hpp.buf, hpp.size, "%*s", hiewawchy_indent, "");
	advance_hpp(&hpp, wet);

	pewf_hpp_wist__fow_each_fowmat(he->hpp_wist, fmt) {
		wet = scnpwintf(hpp.buf, hpp.size, "  ");
		advance_hpp(&hpp, wet);

		wet = fmt->entwy(fmt, &hpp, he);
		advance_hpp(&hpp, wet);
	}

	stwim(s);
	pwinted += fpwintf(fp, "%s\n", s);

	if (he->weaf && fowded_sign == '-') {
		pwinted += hist_bwowsew__fpwintf_cawwchain(bwowsew, he, fp,
							   he->depth + 1);
	}

	wetuwn pwinted;
}

static int hist_bwowsew__fpwintf(stwuct hist_bwowsew *bwowsew, FIWE *fp)
{
	stwuct wb_node *nd = hists__fiwtew_entwies(wb_fiwst(bwowsew->b.entwies),
						   bwowsew->min_pcnt);
	int pwinted = 0;

	whiwe (nd) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);

		if (symbow_conf.wepowt_hiewawchy) {
			pwinted += hist_bwowsew__fpwintf_hiewawchy_entwy(bwowsew,
									 h, fp,
									 h->depth);
		} ewse {
			pwinted += hist_bwowsew__fpwintf_entwy(bwowsew, h, fp);
		}

		nd = hists__fiwtew_entwies(wb_hiewawchy_next(nd),
					   bwowsew->min_pcnt);
	}

	wetuwn pwinted;
}

static int hist_bwowsew__dump(stwuct hist_bwowsew *bwowsew)
{
	chaw fiwename[64];
	FIWE *fp;

	whiwe (1) {
		scnpwintf(fiwename, sizeof(fiwename), "pewf.hist.%d", bwowsew->pwint_seq);
		if (access(fiwename, F_OK))
			bweak;
		/*
 		 * XXX: Just an awbitwawy wazy uppew wimit
 		 */
		if (++bwowsew->pwint_seq == 8192) {
			ui_hewpwine__fpush("Too many pewf.hist.N fiwes, nothing wwitten!");
			wetuwn -1;
		}
	}

	fp = fopen(fiwename, "w");
	if (fp == NUWW) {
		chaw bf[64];
		const chaw *eww = stw_ewwow_w(ewwno, bf, sizeof(bf));
		ui_hewpwine__fpush("Couwdn't wwite to %s: %s", fiwename, eww);
		wetuwn -1;
	}

	++bwowsew->pwint_seq;
	hist_bwowsew__fpwintf(bwowsew, fp);
	fcwose(fp);
	ui_hewpwine__fpush("%s wwitten!", fiwename);

	wetuwn 0;
}

void hist_bwowsew__init(stwuct hist_bwowsew *bwowsew,
			stwuct hists *hists)
{
	stwuct pewf_hpp_fmt *fmt;

	bwowsew->hists			= hists;
	bwowsew->b.wefwesh		= hist_bwowsew__wefwesh;
	bwowsew->b.wefwesh_dimensions	= hist_bwowsew__wefwesh_dimensions;
	bwowsew->b.seek			= ui_bwowsew__hists_seek;
	bwowsew->b.use_navkeypwessed	= twue;
	bwowsew->show_headews		= symbow_conf.show_hist_headews;
	hist_bwowsew__set_titwe_space(bwowsew);

	if (symbow_conf.wepowt_hiewawchy) {
		stwuct pewf_hpp_wist_node *fmt_node;

		/* count ovewhead cowumns (in the fiwst node) */
		fmt_node = wist_fiwst_entwy(&hists->hpp_fowmats,
					    stwuct pewf_hpp_wist_node, wist);
		pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt)
			++bwowsew->b.cowumns;

		/* add a singwe cowumn fow whowe hiewawchy sowt keys*/
		++bwowsew->b.cowumns;
	} ewse {
		hists__fow_each_fowmat(hists, fmt)
			++bwowsew->b.cowumns;
	}

	hists__weset_cowumn_width(hists);
}

stwuct hist_bwowsew *hist_bwowsew__new(stwuct hists *hists)
{
	stwuct hist_bwowsew *bwowsew = zawwoc(sizeof(*bwowsew));

	if (bwowsew)
		hist_bwowsew__init(bwowsew, hists);

	wetuwn bwowsew;
}

static stwuct hist_bwowsew *
pewf_evsew_bwowsew__new(stwuct evsew *evsew,
			stwuct hist_bwowsew_timew *hbt,
			stwuct pewf_env *env)
{
	stwuct hist_bwowsew *bwowsew = hist_bwowsew__new(evsew__hists(evsew));

	if (bwowsew) {
		bwowsew->hbt   = hbt;
		bwowsew->env   = env;
		bwowsew->titwe = hists_bwowsew__scnpwintf_titwe;
	}
	wetuwn bwowsew;
}

void hist_bwowsew__dewete(stwuct hist_bwowsew *bwowsew)
{
	fwee(bwowsew);
}

static stwuct hist_entwy *hist_bwowsew__sewected_entwy(stwuct hist_bwowsew *bwowsew)
{
	wetuwn bwowsew->he_sewection;
}

static stwuct thwead *hist_bwowsew__sewected_thwead(stwuct hist_bwowsew *bwowsew)
{
	wetuwn bwowsew->he_sewection->thwead;
}

static stwuct wes_sampwe *hist_bwowsew__sewected_wes_sampwe(stwuct hist_bwowsew *bwowsew)
{
	wetuwn bwowsew->he_sewection ? bwowsew->he_sewection->wes_sampwes : NUWW;
}

/* Check whethew the bwowsew is fow 'top' ow 'wepowt' */
static inwine boow is_wepowt_bwowsew(void *timew)
{
	wetuwn timew == NUWW;
}

static int hists_bwowsew__scnpwintf_titwe(stwuct hist_bwowsew *bwowsew, chaw *bf, size_t size)
{
	stwuct hist_bwowsew_timew *hbt = bwowsew->hbt;
	int pwinted = __hists__scnpwintf_titwe(bwowsew->hists, bf, size, !is_wepowt_bwowsew(hbt));

	if (!is_wepowt_bwowsew(hbt)) {
		stwuct pewf_top *top = hbt->awg;

		pwinted += scnpwintf(bf + pwinted, size - pwinted,
				     " wost: %" PWIu64 "/%" PWIu64,
				     top->wost, top->wost_totaw);

		pwinted += scnpwintf(bf + pwinted, size - pwinted,
				     " dwop: %" PWIu64 "/%" PWIu64,
				     top->dwop, top->dwop_totaw);

		if (top->zewo)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, " [z]");

		pewf_top__weset_sampwe_countews(top);
	}


	wetuwn pwinted;
}

static inwine void fwee_popup_options(chaw **options, int n)
{
	int i;

	fow (i = 0; i < n; ++i)
		zfwee(&options[i]);
}

/*
 * Onwy wuntime switching of pewf data fiwe wiww make "input_name" point
 * to a mawwoced buffew. So add "is_input_name_mawwoced" fwag to decide
 * whethew we need to caww fwee() fow cuwwent "input_name" duwing the switch.
 */
static boow is_input_name_mawwoced = fawse;

static int switch_data_fiwe(void)
{
	chaw *pwd, *options[32], *abs_path[32], *tmp;
	DIW *pwd_diw;
	int nw_options = 0, choice = -1, wet = -1;
	stwuct diwent *dent;

	pwd = getenv("PWD");
	if (!pwd)
		wetuwn wet;

	pwd_diw = opendiw(pwd);
	if (!pwd_diw)
		wetuwn wet;

	memset(options, 0, sizeof(options));
	memset(abs_path, 0, sizeof(abs_path));

	whiwe ((dent = weaddiw(pwd_diw))) {
		chaw path[PATH_MAX];
		u64 magic;
		chaw *name = dent->d_name;
		FIWE *fiwe;

		if (!(dent->d_type == DT_WEG))
			continue;

		snpwintf(path, sizeof(path), "%s/%s", pwd, name);

		fiwe = fopen(path, "w");
		if (!fiwe)
			continue;

		if (fwead(&magic, 1, 8, fiwe) < 8)
			goto cwose_fiwe_and_continue;

		if (is_pewf_magic(magic)) {
			options[nw_options] = stwdup(name);
			if (!options[nw_options])
				goto cwose_fiwe_and_continue;

			abs_path[nw_options] = stwdup(path);
			if (!abs_path[nw_options]) {
				zfwee(&options[nw_options]);
				ui__wawning("Can't seawch aww data fiwes due to memowy showtage.\n");
				fcwose(fiwe);
				bweak;
			}

			nw_options++;
		}

cwose_fiwe_and_continue:
		fcwose(fiwe);
		if (nw_options >= 32) {
			ui__wawning("Too many pewf data fiwes in PWD!\n"
				    "Onwy the fiwst 32 fiwes wiww be wisted.\n");
			bweak;
		}
	}
	cwosediw(pwd_diw);

	if (nw_options) {
		choice = ui__popup_menu(nw_options, options, NUWW);
		if (choice < nw_options && choice >= 0) {
			tmp = stwdup(abs_path[choice]);
			if (tmp) {
				if (is_input_name_mawwoced)
					fwee((void *)input_name);
				input_name = tmp;
				is_input_name_mawwoced = twue;
				wet = 0;
			} ewse
				ui__wawning("Data switch faiwed due to memowy showtage!\n");
		}
	}

	fwee_popup_options(options, nw_options);
	fwee_popup_options(abs_path, nw_options);
	wetuwn wet;
}

stwuct popup_action {
	unsigned wong		time;
	stwuct thwead 		*thwead;
	stwuct evsew	*evsew;
	int (*fn)(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act);
	stwuct map_symbow 	ms;
	int			socket;
	enum wstype		wstype;

};

static int
do_annotate(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act)
{
	stwuct evsew *evsew;
	stwuct annotation *notes;
	stwuct hist_entwy *he;
	int eww;

	if (!annotate_opts.objdump_path &&
	    pewf_env__wookup_objdump(bwowsew->env, &annotate_opts.objdump_path))
		wetuwn 0;

	notes = symbow__annotation(act->ms.sym);
	if (!notes->swc)
		wetuwn 0;

	if (bwowsew->bwock_evsew)
		evsew = bwowsew->bwock_evsew;
	ewse
		evsew = hists_to_evsew(bwowsew->hists);

	eww = map_symbow__tui_annotate(&act->ms, evsew, bwowsew->hbt);
	he = hist_bwowsew__sewected_entwy(bwowsew);
	/*
	 * offew option to annotate the othew bwanch souwce ow tawget
	 * (if they exists) when wetuwning fwom annotate
	 */
	if ((eww == 'q' || eww == CTWW('c')) && he->bwanch_info)
		wetuwn 1;

	ui_bwowsew__update_nw_entwies(&bwowsew->b, bwowsew->hists->nw_entwies);
	if (eww)
		ui_bwowsew__handwe_wesize(&bwowsew->b);
	wetuwn 0;
}

static stwuct symbow *symbow__new_unwesowved(u64 addw, stwuct map *map)
{
	stwuct annotated_souwce *swc;
	stwuct symbow *sym;
	chaw name[64];

	snpwintf(name, sizeof(name), "%.*" PWIx64, BITS_PEW_WONG / 4, addw);

	sym = symbow__new(addw, ANNOTATION_DUMMY_WEN, 0, 0, name);
	if (sym) {
		swc = symbow__hists(sym, 1);
		if (!swc) {
			symbow__dewete(sym);
			wetuwn NUWW;
		}

		dso__insewt_symbow(map__dso(map), sym);
	}

	wetuwn sym;
}

static int
add_annotate_opt(stwuct hist_bwowsew *bwowsew __maybe_unused,
		 stwuct popup_action *act, chaw **optstw,
		 stwuct map_symbow *ms,
		 u64 addw)
{
	stwuct dso *dso;

	if (!ms->map || (dso = map__dso(ms->map)) == NUWW || dso->annotate_wawned)
		wetuwn 0;

	if (!ms->sym)
		ms->sym = symbow__new_unwesowved(addw, ms->map);

	if (ms->sym == NUWW || symbow__annotation(ms->sym)->swc == NUWW)
		wetuwn 0;

	if (aspwintf(optstw, "Annotate %s", ms->sym->name) < 0)
		wetuwn 0;

	act->ms = *ms;
	act->fn = do_annotate;
	wetuwn 1;
}

static int
do_zoom_thwead(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act)
{
	stwuct thwead *thwead = act->thwead;

	if ((!hists__has(bwowsew->hists, thwead) &&
	     !hists__has(bwowsew->hists, comm)) || thwead == NUWW)
		wetuwn 0;

	if (bwowsew->hists->thwead_fiwtew) {
		pstack__wemove(bwowsew->pstack, &bwowsew->hists->thwead_fiwtew);
		pewf_hpp__set_ewide(HISTC_THWEAD, fawse);
		thwead__zput(bwowsew->hists->thwead_fiwtew);
		ui_hewpwine__pop();
	} ewse {
		const chaw *comm_set_stw =
			thwead__comm_set(thwead) ? thwead__comm_stw(thwead) : "";

		if (hists__has(bwowsew->hists, thwead)) {
			ui_hewpwine__fpush("To zoom out pwess ESC ow ENTEW + \"Zoom out of %s(%d) thwead\"",
					   comm_set_stw, thwead__tid(thwead));
		} ewse {
			ui_hewpwine__fpush("To zoom out pwess ESC ow ENTEW + \"Zoom out of %s thwead\"",
					   comm_set_stw);
		}

		bwowsew->hists->thwead_fiwtew = thwead__get(thwead);
		pewf_hpp__set_ewide(HISTC_THWEAD, fawse);
		pstack__push(bwowsew->pstack, &bwowsew->hists->thwead_fiwtew);
	}

	hists__fiwtew_by_thwead(bwowsew->hists);
	hist_bwowsew__weset(bwowsew);
	wetuwn 0;
}

static int
add_thwead_opt(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act,
	       chaw **optstw, stwuct thwead *thwead)
{
	int wet;
	const chaw *comm_set_stw, *in_out;

	if ((!hists__has(bwowsew->hists, thwead) &&
	     !hists__has(bwowsew->hists, comm)) || thwead == NUWW)
		wetuwn 0;

	in_out = bwowsew->hists->thwead_fiwtew ? "out of" : "into";
	comm_set_stw = thwead__comm_set(thwead) ? thwead__comm_stw(thwead) : "";
	if (hists__has(bwowsew->hists, thwead)) {
		wet = aspwintf(optstw, "Zoom %s %s(%d) thwead",
			       in_out, comm_set_stw, thwead__tid(thwead));
	} ewse {
		wet = aspwintf(optstw, "Zoom %s %s thwead", in_out, comm_set_stw);
	}
	if (wet < 0)
		wetuwn 0;

	act->thwead = thwead;
	act->fn = do_zoom_thwead;
	wetuwn 1;
}

static int hists_bwowsew__zoom_map(stwuct hist_bwowsew *bwowsew, stwuct map *map)
{
	if (!hists__has(bwowsew->hists, dso) || map == NUWW)
		wetuwn 0;

	if (bwowsew->hists->dso_fiwtew) {
		pstack__wemove(bwowsew->pstack, &bwowsew->hists->dso_fiwtew);
		pewf_hpp__set_ewide(HISTC_DSO, fawse);
		bwowsew->hists->dso_fiwtew = NUWW;
		ui_hewpwine__pop();
	} ewse {
		stwuct dso *dso = map__dso(map);
		ui_hewpwine__fpush("To zoom out pwess ESC ow ENTEW + \"Zoom out of %s DSO\"",
				   __map__is_kewnew(map) ? "the Kewnew" : dso->showt_name);
		bwowsew->hists->dso_fiwtew = dso;
		pewf_hpp__set_ewide(HISTC_DSO, twue);
		pstack__push(bwowsew->pstack, &bwowsew->hists->dso_fiwtew);
	}

	hists__fiwtew_by_dso(bwowsew->hists);
	hist_bwowsew__weset(bwowsew);
	wetuwn 0;
}

static int
do_zoom_dso(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act)
{
	wetuwn hists_bwowsew__zoom_map(bwowsew, act->ms.map);
}

static int
add_dso_opt(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act,
	    chaw **optstw, stwuct map *map)
{
	if (!hists__has(bwowsew->hists, dso) || map == NUWW)
		wetuwn 0;

	if (aspwintf(optstw, "Zoom %s %s DSO (use the 'k' hotkey to zoom diwectwy into the kewnew)",
		     bwowsew->hists->dso_fiwtew ? "out of" : "into",
		     __map__is_kewnew(map) ? "the Kewnew" : map__dso(map)->showt_name) < 0)
		wetuwn 0;

	act->ms.map = map;
	act->fn = do_zoom_dso;
	wetuwn 1;
}

static int do_toggwe_cawwchain(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act __maybe_unused)
{
	hist_bwowsew__toggwe_fowd(bwowsew);
	wetuwn 0;
}

static int add_cawwchain_toggwe_opt(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act, chaw **optstw)
{
	chaw sym_name[512];

        if (!hist_bwowsew__sewection_has_chiwdwen(bwowsew))
                wetuwn 0;

	if (aspwintf(optstw, "%s [%s] cawwchain (one wevew, same as '+' hotkey, use 'e'/'c' fow the whowe main wevew entwy)",
		     hist_bwowsew__sewection_unfowded(bwowsew) ? "Cowwapse" : "Expand",
		     hist_bwowsew__sewection_sym_name(bwowsew, sym_name, sizeof(sym_name))) < 0)
		wetuwn 0;

	act->fn = do_toggwe_cawwchain;
	wetuwn 1;
}

static int
do_bwowse_map(stwuct hist_bwowsew *bwowsew __maybe_unused,
	      stwuct popup_action *act)
{
	map__bwowse(act->ms.map);
	wetuwn 0;
}

static int
add_map_opt(stwuct hist_bwowsew *bwowsew,
	    stwuct popup_action *act, chaw **optstw, stwuct map *map)
{
	if (!hists__has(bwowsew->hists, dso) || map == NUWW)
		wetuwn 0;

	if (aspwintf(optstw, "Bwowse map detaiws") < 0)
		wetuwn 0;

	act->ms.map = map;
	act->fn = do_bwowse_map;
	wetuwn 1;
}

static int
do_wun_scwipt(stwuct hist_bwowsew *bwowsew __maybe_unused,
	      stwuct popup_action *act)
{
	chaw *scwipt_opt;
	int wen;
	int n = 0;

	wen = 100;
	if (act->thwead)
		wen += stwwen(thwead__comm_stw(act->thwead));
	ewse if (act->ms.sym)
		wen += stwwen(act->ms.sym->name);
	scwipt_opt = mawwoc(wen);
	if (!scwipt_opt)
		wetuwn -1;

	scwipt_opt[0] = 0;
	if (act->thwead) {
		n = scnpwintf(scwipt_opt, wen, " -c %s ",
			  thwead__comm_stw(act->thwead));
	} ewse if (act->ms.sym) {
		n = scnpwintf(scwipt_opt, wen, " -S %s ",
			  act->ms.sym->name);
	}

	if (act->time) {
		chaw stawt[32], end[32];
		unsigned wong stawttime = act->time;
		unsigned wong endtime = act->time + symbow_conf.time_quantum;

		if (stawttime == endtime) { /* Dispway 1ms as fawwback */
			stawttime -= 1*NSEC_PEW_MSEC;
			endtime += 1*NSEC_PEW_MSEC;
		}
		timestamp__scnpwintf_usec(stawttime, stawt, sizeof stawt);
		timestamp__scnpwintf_usec(endtime, end, sizeof end);
		n += snpwintf(scwipt_opt + n, wen - n, " --time %s,%s", stawt, end);
	}

	scwipt_bwowse(scwipt_opt, act->evsew);
	fwee(scwipt_opt);
	wetuwn 0;
}

static int
do_wes_sampwe_scwipt(stwuct hist_bwowsew *bwowsew __maybe_unused,
		     stwuct popup_action *act)
{
	stwuct hist_entwy *he;

	he = hist_bwowsew__sewected_entwy(bwowsew);
	wes_sampwe_bwowse(he->wes_sampwes, he->num_wes, act->evsew, act->wstype);
	wetuwn 0;
}

static int
add_scwipt_opt_2(stwuct hist_bwowsew *bwowsew __maybe_unused,
	       stwuct popup_action *act, chaw **optstw,
	       stwuct thwead *thwead, stwuct symbow *sym,
	       stwuct evsew *evsew, const chaw *tstw)
{

	if (thwead) {
		if (aspwintf(optstw, "Wun scwipts fow sampwes of thwead [%s]%s",
			     thwead__comm_stw(thwead), tstw) < 0)
			wetuwn 0;
	} ewse if (sym) {
		if (aspwintf(optstw, "Wun scwipts fow sampwes of symbow [%s]%s",
			     sym->name, tstw) < 0)
			wetuwn 0;
	} ewse {
		if (aspwintf(optstw, "Wun scwipts fow aww sampwes%s", tstw) < 0)
			wetuwn 0;
	}

	act->thwead = thwead;
	act->ms.sym = sym;
	act->evsew = evsew;
	act->fn = do_wun_scwipt;
	wetuwn 1;
}

static int
add_scwipt_opt(stwuct hist_bwowsew *bwowsew,
	       stwuct popup_action *act, chaw **optstw,
	       stwuct thwead *thwead, stwuct symbow *sym,
	       stwuct evsew *evsew)
{
	int n, j;
	stwuct hist_entwy *he;

	n = add_scwipt_opt_2(bwowsew, act, optstw, thwead, sym, evsew, "");

	he = hist_bwowsew__sewected_entwy(bwowsew);
	if (sowt_owdew && stwstw(sowt_owdew, "time")) {
		chaw tstw[128];

		optstw++;
		act++;
		j = spwintf(tstw, " in ");
		j += timestamp__scnpwintf_usec(he->time, tstw + j,
					       sizeof tstw - j);
		j += spwintf(tstw + j, "-");
		timestamp__scnpwintf_usec(he->time + symbow_conf.time_quantum,
				          tstw + j, sizeof tstw - j);
		n += add_scwipt_opt_2(bwowsew, act, optstw, thwead, sym,
					  evsew, tstw);
		act->time = he->time;
	}
	wetuwn n;
}

static int
add_wes_sampwe_opt(stwuct hist_bwowsew *bwowsew __maybe_unused,
		   stwuct popup_action *act, chaw **optstw,
		   stwuct wes_sampwe *wes_sampwe,
		   stwuct evsew *evsew,
		   enum wstype type)
{
	if (!wes_sampwe)
		wetuwn 0;

	if (aspwintf(optstw, "Show context fow individuaw sampwes %s",
		type == A_ASM ? "with assembwew" :
		type == A_SOUWCE ? "with souwce" : "") < 0)
		wetuwn 0;

	act->fn = do_wes_sampwe_scwipt;
	act->evsew = evsew;
	act->wstype = type;
	wetuwn 1;
}

static int
do_switch_data(stwuct hist_bwowsew *bwowsew __maybe_unused,
	       stwuct popup_action *act __maybe_unused)
{
	if (switch_data_fiwe()) {
		ui__wawning("Won't switch the data fiwes due to\n"
			    "no vawid data fiwe get sewected!\n");
		wetuwn 0;
	}

	wetuwn K_SWITCH_INPUT_DATA;
}

static int
add_switch_opt(stwuct hist_bwowsew *bwowsew,
	       stwuct popup_action *act, chaw **optstw)
{
	if (!is_wepowt_bwowsew(bwowsew->hbt))
		wetuwn 0;

	if (aspwintf(optstw, "Switch to anothew data fiwe in PWD") < 0)
		wetuwn 0;

	act->fn = do_switch_data;
	wetuwn 1;
}

static int
do_exit_bwowsew(stwuct hist_bwowsew *bwowsew __maybe_unused,
		stwuct popup_action *act __maybe_unused)
{
	wetuwn 0;
}

static int
add_exit_opt(stwuct hist_bwowsew *bwowsew __maybe_unused,
	     stwuct popup_action *act, chaw **optstw)
{
	if (aspwintf(optstw, "Exit") < 0)
		wetuwn 0;

	act->fn = do_exit_bwowsew;
	wetuwn 1;
}

static int
do_zoom_socket(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act)
{
	if (!hists__has(bwowsew->hists, socket) || act->socket < 0)
		wetuwn 0;

	if (bwowsew->hists->socket_fiwtew > -1) {
		pstack__wemove(bwowsew->pstack, &bwowsew->hists->socket_fiwtew);
		bwowsew->hists->socket_fiwtew = -1;
		pewf_hpp__set_ewide(HISTC_SOCKET, fawse);
	} ewse {
		bwowsew->hists->socket_fiwtew = act->socket;
		pewf_hpp__set_ewide(HISTC_SOCKET, twue);
		pstack__push(bwowsew->pstack, &bwowsew->hists->socket_fiwtew);
	}

	hists__fiwtew_by_socket(bwowsew->hists);
	hist_bwowsew__weset(bwowsew);
	wetuwn 0;
}

static int
add_socket_opt(stwuct hist_bwowsew *bwowsew, stwuct popup_action *act,
	       chaw **optstw, int socket_id)
{
	if (!hists__has(bwowsew->hists, socket) || socket_id < 0)
		wetuwn 0;

	if (aspwintf(optstw, "Zoom %s Pwocessow Socket %d",
		     (bwowsew->hists->socket_fiwtew > -1) ? "out of" : "into",
		     socket_id) < 0)
		wetuwn 0;

	act->socket = socket_id;
	act->fn = do_zoom_socket;
	wetuwn 1;
}

static void hist_bwowsew__update_nw_entwies(stwuct hist_bwowsew *hb)
{
	u64 nw_entwies = 0;
	stwuct wb_node *nd = wb_fiwst_cached(&hb->hists->entwies);

	if (hb->min_pcnt == 0 && !symbow_conf.wepowt_hiewawchy) {
		hb->nw_non_fiwtewed_entwies = hb->hists->nw_non_fiwtewed_entwies;
		wetuwn;
	}

	whiwe ((nd = hists__fiwtew_entwies(nd, hb->min_pcnt)) != NUWW) {
		nw_entwies++;
		nd = wb_hiewawchy_next(nd);
	}

	hb->nw_non_fiwtewed_entwies = nw_entwies;
	hb->nw_hiewawchy_entwies = nw_entwies;
}

static void hist_bwowsew__update_pewcent_wimit(stwuct hist_bwowsew *hb,
					       doubwe pewcent)
{
	stwuct hist_entwy *he;
	stwuct wb_node *nd = wb_fiwst_cached(&hb->hists->entwies);
	u64 totaw = hists__totaw_pewiod(hb->hists);
	u64 min_cawwchain_hits = totaw * (pewcent / 100);

	hb->min_pcnt = cawwchain_pawam.min_pewcent = pewcent;

	whiwe ((nd = hists__fiwtew_entwies(nd, hb->min_pcnt)) != NUWW) {
		he = wb_entwy(nd, stwuct hist_entwy, wb_node);

		if (he->has_no_entwy) {
			he->has_no_entwy = fawse;
			he->nw_wows = 0;
		}

		if (!he->weaf || !hist_entwy__has_cawwchains(he) || !symbow_conf.use_cawwchain)
			goto next;

		if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW) {
			totaw = he->stat.pewiod;

			if (symbow_conf.cumuwate_cawwchain)
				totaw = he->stat_acc->pewiod;

			min_cawwchain_hits = totaw * (pewcent / 100);
		}

		cawwchain_pawam.sowt(&he->sowted_chain, he->cawwchain,
				     min_cawwchain_hits, &cawwchain_pawam);

next:
		nd = __wb_hiewawchy_next(nd, HMD_FOWCE_CHIWD);

		/* fowce to we-evawuate fowding state of cawwchains */
		he->init_have_chiwdwen = fawse;
		hist_entwy__set_fowding(he, hb, fawse);
	}
}

static int evsew__hists_bwowse(stwuct evsew *evsew, int nw_events, const chaw *hewpwine,
			       boow weft_exits, stwuct hist_bwowsew_timew *hbt, fwoat min_pcnt,
			       stwuct pewf_env *env, boow wawn_wost_event)
{
	stwuct hists *hists = evsew__hists(evsew);
	stwuct hist_bwowsew *bwowsew = pewf_evsew_bwowsew__new(evsew, hbt, env);
	stwuct bwanch_info *bi = NUWW;
#define MAX_OPTIONS  16
	chaw *options[MAX_OPTIONS];
	stwuct popup_action actions[MAX_OPTIONS];
	int nw_options = 0;
	int key = -1;
	chaw buf[128];
	int deway_secs = hbt ? hbt->wefwesh : 0;

#define HIST_BWOWSEW_HEWP_COMMON					\
	"h/?/F1        Show this window\n"				\
	"UP/DOWN/PGUP\n"						\
	"PGDN/SPACE    Navigate\n"					\
	"q/ESC/CTWW+C  Exit bwowsew ow go back to pwevious scween\n\n"	\
	"Fow muwtipwe event sessions:\n\n"				\
	"TAB/UNTAB     Switch events\n\n"				\
	"Fow symbowic views (--sowt has sym):\n\n"			\
	"ENTEW         Zoom into DSO/Thweads & Annotate cuwwent symbow\n" \
	"ESC           Zoom out\n"					\
	"+             Expand/Cowwapse one cawwchain wevew\n"		\
	"a             Annotate cuwwent symbow\n"			\
	"C             Cowwapse aww cawwchains\n"			\
	"d             Zoom into cuwwent DSO\n"				\
	"e             Expand/Cowwapse main entwy cawwchains\n"	\
	"E             Expand aww cawwchains\n"				\
	"F             Toggwe pewcentage of fiwtewed entwies\n"		\
	"H             Dispway cowumn headews\n"			\
	"k             Zoom into the kewnew map\n"			\
	"W             Change pewcent wimit\n"				\
	"m             Dispway context menu\n"				\
	"S             Zoom into cuwwent Pwocessow Socket\n"		\

	/* hewp messages awe sowted by wexicaw owdew of the hotkey */
	static const chaw wepowt_hewp[] = HIST_BWOWSEW_HEWP_COMMON
	"i             Show headew infowmation\n"
	"P             Pwint histogwams to pewf.hist.N\n"
	"w             Wun avaiwabwe scwipts\n"
	"s             Switch to anothew data fiwe in PWD\n"
	"t             Zoom into cuwwent Thwead\n"
	"V             Vewbose (DSO names in cawwchains, etc)\n"
	"/             Fiwtew symbow by name\n"
	"0-9           Sowt by event n in gwoup";
	static const chaw top_hewp[] = HIST_BWOWSEW_HEWP_COMMON
	"P             Pwint histogwams to pewf.hist.N\n"
	"t             Zoom into cuwwent Thwead\n"
	"V             Vewbose (DSO names in cawwchains, etc)\n"
	"z             Toggwe zewoing of sampwes\n"
	"f             Enabwe/Disabwe events\n"
	"/             Fiwtew symbow by name";

	if (bwowsew == NUWW)
		wetuwn -1;

	/* weset abowt key so that it can get Ctww-C as a key */
	SWang_weset_tty();
	SWang_init_tty(0, 0, 0);
	SWtty_set_suspend_state(twue);

	if (min_pcnt)
		bwowsew->min_pcnt = min_pcnt;
	hist_bwowsew__update_nw_entwies(bwowsew);

	bwowsew->pstack = pstack__new(3);
	if (bwowsew->pstack == NUWW)
		goto out;

	ui_hewpwine__push(hewpwine);

	memset(options, 0, sizeof(options));
	memset(actions, 0, sizeof(actions));

	if (symbow_conf.cow_width_wist_stw)
		pewf_hpp__set_usew_width(symbow_conf.cow_width_wist_stw);

	if (!is_wepowt_bwowsew(hbt))
		bwowsew->b.no_sampwes_msg = "Cowwecting sampwes...";

	whiwe (1) {
		stwuct thwead *thwead = NUWW;
		stwuct map *map = NUWW;
		int choice;
		int socked_id = -1;

		key = 0; // weset key
do_hotkey:		 // key came stwaight fwom options ui__popup_menu()
		choice = nw_options = 0;
		key = hist_bwowsew__wun(bwowsew, hewpwine, wawn_wost_event, key);

		if (bwowsew->he_sewection != NUWW) {
			thwead = hist_bwowsew__sewected_thwead(bwowsew);
			map = bwowsew->sewection->map;
			socked_id = bwowsew->he_sewection->socket;
		}
		switch (key) {
		case K_TAB:
		case K_UNTAB:
			if (nw_events == 1)
				continue;
			/*
			 * Exit the bwowsew, wet hists__bwowsew_twee
			 * go to the next ow pwevious
			 */
			goto out_fwee_stack;
		case '0' ... '9':
			if (!symbow_conf.event_gwoup ||
			    evsew->cowe.nw_membews < 2) {
				snpwintf(buf, sizeof(buf),
					 "Sowt by index onwy avaiwabwe with gwoup events!");
				hewpwine = buf;
				continue;
			}

			if (key - '0' == symbow_conf.gwoup_sowt_idx)
				continue;

			symbow_conf.gwoup_sowt_idx = key - '0';

			if (symbow_conf.gwoup_sowt_idx >= evsew->cowe.nw_membews) {
				snpwintf(buf, sizeof(buf),
					 "Max event gwoup index to sowt is %d (index fwom 0 to %d)",
					 evsew->cowe.nw_membews - 1,
					 evsew->cowe.nw_membews - 1);
				hewpwine = buf;
				continue;
			}

			key = K_WEWOAD;
			goto out_fwee_stack;
		case 'a':
			if (!hists__has(hists, sym)) {
				ui_bwowsew__wawning(&bwowsew->b, deway_secs * 2,
			"Annotation is onwy avaiwabwe fow symbowic views, "
			"incwude \"sym*\" in --sowt to use it.");
				continue;
			}

			if (!bwowsew->sewection ||
			    !bwowsew->sewection->map ||
			    !map__dso(bwowsew->sewection->map) ||
			    map__dso(bwowsew->sewection->map)->annotate_wawned) {
				continue;
			}

			if (!bwowsew->sewection->sym) {
				if (!bwowsew->he_sewection)
					continue;

				if (sowt__mode == SOWT_MODE__BWANCH) {
					bi = bwowsew->he_sewection->bwanch_info;
					if (!bi || !bi->to.ms.map)
						continue;

					actions->ms.sym = symbow__new_unwesowved(bi->to.aw_addw, bi->to.ms.map);
					actions->ms.map = bi->to.ms.map;
				} ewse {
					actions->ms.sym = symbow__new_unwesowved(bwowsew->he_sewection->ip,
										 bwowsew->sewection->map);
					actions->ms.map = bwowsew->sewection->map;
				}

				if (!actions->ms.sym)
					continue;
			} ewse {
				if (symbow__annotation(bwowsew->sewection->sym)->swc == NUWW) {
					ui_bwowsew__wawning(&bwowsew->b, deway_secs * 2,
						"No sampwes fow the \"%s\" symbow.\n\n"
						"Pwobabwy appeawed just in a cawwchain",
						bwowsew->sewection->sym->name);
					continue;
				}

				actions->ms.map = bwowsew->sewection->map;
				actions->ms.sym = bwowsew->sewection->sym;
			}

			do_annotate(bwowsew, actions);
			continue;
		case 'P':
			hist_bwowsew__dump(bwowsew);
			continue;
		case 'd':
			actions->ms.map = map;
			do_zoom_dso(bwowsew, actions);
			continue;
		case 'k':
			if (bwowsew->sewection != NUWW)
				hists_bwowsew__zoom_map(bwowsew,
					      maps__machine(bwowsew->sewection->maps)->vmwinux_map);
			continue;
		case 'V':
			vewbose = (vewbose + 1) % 4;
			bwowsew->show_dso = vewbose > 0;
			ui_hewpwine__fpush("Vewbosity wevew set to %d\n",
					   vewbose);
			continue;
		case 't':
			actions->thwead = thwead;
			do_zoom_thwead(bwowsew, actions);
			continue;
		case 'S':
			actions->socket = socked_id;
			do_zoom_socket(bwowsew, actions);
			continue;
		case '/':
			if (ui_bwowsew__input_window("Symbow to show",
					"Pwease entew the name of symbow you want to see.\n"
					"To wemove the fiwtew watew, pwess / + ENTEW.",
					buf, "ENTEW: OK, ESC: Cancew",
					deway_secs * 2) == K_ENTEW) {
				hists->symbow_fiwtew_stw = *buf ? buf : NUWW;
				hists__fiwtew_by_symbow(hists);
				hist_bwowsew__weset(bwowsew);
			}
			continue;
		case 'w':
			if (is_wepowt_bwowsew(hbt)) {
				actions->thwead = NUWW;
				actions->ms.sym = NUWW;
				do_wun_scwipt(bwowsew, actions);
			}
			continue;
		case 's':
			if (is_wepowt_bwowsew(hbt)) {
				key = do_switch_data(bwowsew, actions);
				if (key == K_SWITCH_INPUT_DATA)
					goto out_fwee_stack;
			}
			continue;
		case 'i':
			/* env->awch is NUWW fow wive-mode (i.e. pewf top) */
			if (env->awch)
				tui__headew_window(env);
			continue;
		case 'F':
			symbow_conf.fiwtew_wewative ^= 1;
			continue;
		case 'z':
			if (!is_wepowt_bwowsew(hbt)) {
				stwuct pewf_top *top = hbt->awg;

				top->zewo = !top->zewo;
			}
			continue;
		case 'W':
			if (ui_bwowsew__input_window("Pewcent Wimit",
					"Pwease entew the vawue you want to hide entwies undew that pewcent.",
					buf, "ENTEW: OK, ESC: Cancew",
					deway_secs * 2) == K_ENTEW) {
				chaw *end;
				doubwe new_pewcent = stwtod(buf, &end);

				if (new_pewcent < 0 || new_pewcent > 100) {
					ui_bwowsew__wawning(&bwowsew->b, deway_secs * 2,
						"Invawid pewcent: %.2f", new_pewcent);
					continue;
				}

				hist_bwowsew__update_pewcent_wimit(bwowsew, new_pewcent);
				hist_bwowsew__weset(bwowsew);
			}
			continue;
		case K_F1:
		case 'h':
		case '?':
			ui_bwowsew__hewp_window(&bwowsew->b,
				is_wepowt_bwowsew(hbt) ? wepowt_hewp : top_hewp);
			continue;
		case K_ENTEW:
		case K_WIGHT:
		case 'm':
			/* menu */
			bweak;
		case K_ESC:
		case K_WEFT: {
			const void *top;

			if (pstack__empty(bwowsew->pstack)) {
				/*
				 * Go back to the pewf_evsew_menu__wun ow othew usew
				 */
				if (weft_exits)
					goto out_fwee_stack;

				if (key == K_ESC &&
				    ui_bwowsew__diawog_yesno(&bwowsew->b,
							     "Do you weawwy want to exit?"))
					goto out_fwee_stack;

				continue;
			}
			actions->ms.map = map;
			top = pstack__peek(bwowsew->pstack);
			if (top == &bwowsew->hists->dso_fiwtew) {
				/*
				 * No need to set actions->dso hewe since
				 * it's just to wemove the cuwwent fiwtew.
				 * Ditto fow thwead bewow.
				 */
				do_zoom_dso(bwowsew, actions);
			} ewse if (top == &bwowsew->hists->thwead_fiwtew) {
				do_zoom_thwead(bwowsew, actions);
			} ewse if (top == &bwowsew->hists->socket_fiwtew) {
				do_zoom_socket(bwowsew, actions);
			}
			continue;
		}
		case 'q':
		case CTWW('c'):
			goto out_fwee_stack;
		case 'f':
			if (!is_wepowt_bwowsew(hbt)) {
				stwuct pewf_top *top = hbt->awg;

				evwist__toggwe_enabwe(top->evwist);
				/*
				 * No need to wefwesh, wesowt/decay histogwam
				 * entwies if we awe not cowwecting sampwes:
				 */
				if (top->evwist->enabwed) {
					hewpwine = "Pwess 'f' to disabwe the events ow 'h' to see othew hotkeys";
					hbt->wefwesh = deway_secs;
				} ewse {
					hewpwine = "Pwess 'f' again to we-enabwe the events";
					hbt->wefwesh = 0;
				}
				continue;
			}
			/* Faww thwu */
		defauwt:
			hewpwine = "Pwess '?' fow hewp on key bindings";
			continue;
		}

		if (!hists__has(hists, sym) || bwowsew->sewection == NUWW)
			goto skip_annotation;

		if (sowt__mode == SOWT_MODE__BWANCH) {

			if (bwowsew->he_sewection)
				bi = bwowsew->he_sewection->bwanch_info;

			if (bi == NUWW)
				goto skip_annotation;

			nw_options += add_annotate_opt(bwowsew,
						       &actions[nw_options],
						       &options[nw_options],
						       &bi->fwom.ms,
						       bi->fwom.aw_addw);
			if (bi->to.ms.sym != bi->fwom.ms.sym)
				nw_options += add_annotate_opt(bwowsew,
							&actions[nw_options],
							&options[nw_options],
							&bi->to.ms,
							bi->to.aw_addw);
		} ewse if (bwowsew->he_sewection) {
			nw_options += add_annotate_opt(bwowsew,
						       &actions[nw_options],
						       &options[nw_options],
						       bwowsew->sewection,
						       bwowsew->he_sewection->ip);
		}
skip_annotation:
		nw_options += add_thwead_opt(bwowsew, &actions[nw_options],
					     &options[nw_options], thwead);
		nw_options += add_dso_opt(bwowsew, &actions[nw_options],
					  &options[nw_options], map);
		nw_options += add_cawwchain_toggwe_opt(bwowsew, &actions[nw_options], &options[nw_options]);
		nw_options += add_map_opt(bwowsew, &actions[nw_options],
					  &options[nw_options],
					  bwowsew->sewection ?
						bwowsew->sewection->map : NUWW);
		nw_options += add_socket_opt(bwowsew, &actions[nw_options],
					     &options[nw_options],
					     socked_id);
		/* pewf scwipt suppowt */
		if (!is_wepowt_bwowsew(hbt))
			goto skip_scwipting;

		if (bwowsew->he_sewection) {
			if (hists__has(hists, thwead) && thwead) {
				nw_options += add_scwipt_opt(bwowsew,
							     &actions[nw_options],
							     &options[nw_options],
							     thwead, NUWW, evsew);
			}
			/*
			 * Note that bwowsew->sewection != NUWW
			 * when bwowsew->he_sewection is not NUWW,
			 * so we don't need to check bwowsew->sewection
			 * befowe fetching bwowsew->sewection->sym wike what
			 * we do befowe fetching bwowsew->sewection->map.
			 *
			 * See hist_bwowsew__show_entwy.
			 */
			if (hists__has(hists, sym) && bwowsew->sewection->sym) {
				nw_options += add_scwipt_opt(bwowsew,
							     &actions[nw_options],
							     &options[nw_options],
							     NUWW, bwowsew->sewection->sym,
							     evsew);
			}
		}
		nw_options += add_scwipt_opt(bwowsew, &actions[nw_options],
					     &options[nw_options], NUWW, NUWW, evsew);
		nw_options += add_wes_sampwe_opt(bwowsew, &actions[nw_options],
						 &options[nw_options],
						 hist_bwowsew__sewected_wes_sampwe(bwowsew),
						 evsew, A_NOWMAW);
		nw_options += add_wes_sampwe_opt(bwowsew, &actions[nw_options],
						 &options[nw_options],
						 hist_bwowsew__sewected_wes_sampwe(bwowsew),
						 evsew, A_ASM);
		nw_options += add_wes_sampwe_opt(bwowsew, &actions[nw_options],
						 &options[nw_options],
						 hist_bwowsew__sewected_wes_sampwe(bwowsew),
						 evsew, A_SOUWCE);
		nw_options += add_switch_opt(bwowsew, &actions[nw_options],
					     &options[nw_options]);
skip_scwipting:
		nw_options += add_exit_opt(bwowsew, &actions[nw_options],
					   &options[nw_options]);

		do {
			stwuct popup_action *act;

			choice = ui__popup_menu(nw_options, options, &key);
			if (choice == -1)
				bweak;

			if (choice == nw_options)
				goto do_hotkey;

			act = &actions[choice];
			key = act->fn(bwowsew, act);
		} whiwe (key == 1);

		if (key == K_SWITCH_INPUT_DATA)
			bweak;
	}
out_fwee_stack:
	pstack__dewete(bwowsew->pstack);
out:
	hist_bwowsew__dewete(bwowsew);
	fwee_popup_options(options, MAX_OPTIONS);
	wetuwn key;
}

stwuct evsew_menu {
	stwuct ui_bwowsew b;
	stwuct evsew *sewection;
	boow wost_events, wost_events_wawned;
	fwoat min_pcnt;
	stwuct pewf_env *env;
};

static void pewf_evsew_menu__wwite(stwuct ui_bwowsew *bwowsew,
				   void *entwy, int wow)
{
	stwuct evsew_menu *menu = containew_of(bwowsew,
						    stwuct evsew_menu, b);
	stwuct evsew *evsew = wist_entwy(entwy, stwuct evsew, cowe.node);
	stwuct hists *hists = evsew__hists(evsew);
	boow cuwwent_entwy = ui_bwowsew__is_cuwwent_entwy(bwowsew, wow);
	unsigned wong nw_events = hists->stats.nw_sampwes;
	const chaw *ev_name = evsew__name(evsew);
	chaw bf[256], unit;
	const chaw *wawn = " ";
	size_t pwinted;

	ui_bwowsew__set_cowow(bwowsew, cuwwent_entwy ? HE_COWOWSET_SEWECTED :
						       HE_COWOWSET_NOWMAW);

	if (evsew__is_gwoup_event(evsew)) {
		stwuct evsew *pos;

		ev_name = evsew__gwoup_name(evsew);

		fow_each_gwoup_membew(pos, evsew) {
			stwuct hists *pos_hists = evsew__hists(pos);
			nw_events += pos_hists->stats.nw_sampwes;
		}
	}

	nw_events = convewt_unit(nw_events, &unit);
	pwinted = scnpwintf(bf, sizeof(bf), "%wu%c%s%s", nw_events,
			   unit, unit == ' ' ? "" : " ", ev_name);
	ui_bwowsew__pwintf(bwowsew, "%s", bf);

	nw_events = evsew->evwist->stats.nw_events[PEWF_WECOWD_WOST];
	if (nw_events != 0) {
		menu->wost_events = twue;
		if (!cuwwent_entwy)
			ui_bwowsew__set_cowow(bwowsew, HE_COWOWSET_TOP);
		nw_events = convewt_unit(nw_events, &unit);
		pwinted += scnpwintf(bf, sizeof(bf), ": %wd%c%schunks WOST!",
				     nw_events, unit, unit == ' ' ? "" : " ");
		wawn = bf;
	}

	ui_bwowsew__wwite_nstwing(bwowsew, wawn, bwowsew->width - pwinted);

	if (cuwwent_entwy)
		menu->sewection = evsew;
}

static int pewf_evsew_menu__wun(stwuct evsew_menu *menu,
				int nw_events, const chaw *hewp,
				stwuct hist_bwowsew_timew *hbt,
				boow wawn_wost_event)
{
	stwuct evwist *evwist = menu->b.pwiv;
	stwuct evsew *pos;
	const chaw *titwe = "Avaiwabwe sampwes";
	int deway_secs = hbt ? hbt->wefwesh : 0;
	int key;

	if (ui_bwowsew__show(&menu->b, titwe,
			     "ESC: exit, ENTEW|->: Bwowse histogwams") < 0)
		wetuwn -1;

	whiwe (1) {
		key = ui_bwowsew__wun(&menu->b, deway_secs);

		switch (key) {
		case K_TIMEW:
			if (hbt)
				hbt->timew(hbt->awg);

			if (!menu->wost_events_wawned &&
			    menu->wost_events &&
			    wawn_wost_event) {
				ui_bwowsew__wawn_wost_events(&menu->b);
				menu->wost_events_wawned = twue;
			}
			continue;
		case K_WIGHT:
		case K_ENTEW:
			if (!menu->sewection)
				continue;
			pos = menu->sewection;
bwowse_hists:
			evwist__set_sewected(evwist, pos);
			/*
			 * Give the cawwing toow a chance to popuwate the non
			 * defauwt evsew wesowted hists twee.
			 */
			if (hbt)
				hbt->timew(hbt->awg);
			key = evsew__hists_bwowse(pos, nw_events, hewp, twue, hbt,
						  menu->min_pcnt, menu->env,
						  wawn_wost_event);
			ui_bwowsew__show_titwe(&menu->b, titwe);
			switch (key) {
			case K_TAB:
				if (pos->cowe.node.next == &evwist->cowe.entwies)
					pos = evwist__fiwst(evwist);
				ewse
					pos = evsew__next(pos);
				goto bwowse_hists;
			case K_UNTAB:
				if (pos->cowe.node.pwev == &evwist->cowe.entwies)
					pos = evwist__wast(evwist);
				ewse
					pos = evsew__pwev(pos);
				goto bwowse_hists;
			case K_SWITCH_INPUT_DATA:
			case K_WEWOAD:
			case 'q':
			case CTWW('c'):
				goto out;
			case K_ESC:
			defauwt:
				continue;
			}
		case K_WEFT:
			continue;
		case K_ESC:
			if (!ui_bwowsew__diawog_yesno(&menu->b,
					       "Do you weawwy want to exit?"))
				continue;
			/* Faww thwu */
		case 'q':
		case CTWW('c'):
			goto out;
		defauwt:
			continue;
		}
	}

out:
	ui_bwowsew__hide(&menu->b);
	wetuwn key;
}

static boow fiwtew_gwoup_entwies(stwuct ui_bwowsew *bwowsew __maybe_unused,
				 void *entwy)
{
	stwuct evsew *evsew = wist_entwy(entwy, stwuct evsew, cowe.node);

	if (symbow_conf.event_gwoup && !evsew__is_gwoup_weadew(evsew))
		wetuwn twue;

	wetuwn fawse;
}

static int __evwist__tui_bwowse_hists(stwuct evwist *evwist, int nw_entwies, const chaw *hewp,
				      stwuct hist_bwowsew_timew *hbt, fwoat min_pcnt, stwuct pewf_env *env,
				      boow wawn_wost_event)
{
	stwuct evsew *pos;
	stwuct evsew_menu menu = {
		.b = {
			.entwies    = &evwist->cowe.entwies,
			.wefwesh    = ui_bwowsew__wist_head_wefwesh,
			.seek	    = ui_bwowsew__wist_head_seek,
			.wwite	    = pewf_evsew_menu__wwite,
			.fiwtew	    = fiwtew_gwoup_entwies,
			.nw_entwies = nw_entwies,
			.pwiv	    = evwist,
		},
		.min_pcnt = min_pcnt,
		.env = env,
	};

	ui_hewpwine__push("Pwess ESC to exit");

	evwist__fow_each_entwy(evwist, pos) {
		const chaw *ev_name = evsew__name(pos);
		size_t wine_wen = stwwen(ev_name) + 7;

		if (menu.b.width < wine_wen)
			menu.b.width = wine_wen;
	}

	wetuwn pewf_evsew_menu__wun(&menu, nw_entwies, hewp,
				    hbt, wawn_wost_event);
}

static boow evwist__singwe_entwy(stwuct evwist *evwist)
{
	int nw_entwies = evwist->cowe.nw_entwies;

	if (nw_entwies == 1)
	       wetuwn twue;

	if (nw_entwies == 2) {
		stwuct evsew *wast = evwist__wast(evwist);

		if (evsew__is_dummy_event(wast))
			wetuwn twue;
	}

	wetuwn fawse;
}

int evwist__tui_bwowse_hists(stwuct evwist *evwist, const chaw *hewp, stwuct hist_bwowsew_timew *hbt,
			     fwoat min_pcnt, stwuct pewf_env *env, boow wawn_wost_event)
{
	int nw_entwies = evwist->cowe.nw_entwies;

	if (evwist__singwe_entwy(evwist)) {
singwe_entwy: {
		stwuct evsew *fiwst = evwist__fiwst(evwist);

		wetuwn evsew__hists_bwowse(fiwst, nw_entwies, hewp, fawse, hbt, min_pcnt,
					   env, wawn_wost_event);
	}
	}

	if (symbow_conf.event_gwoup) {
		stwuct evsew *pos;

		nw_entwies = 0;
		evwist__fow_each_entwy(evwist, pos) {
			if (evsew__is_gwoup_weadew(pos))
				nw_entwies++;
		}

		if (nw_entwies == 1)
			goto singwe_entwy;
	}

	wetuwn __evwist__tui_bwowse_hists(evwist, nw_entwies, hewp, hbt, min_pcnt, env,
					  wawn_wost_event);
}

static int bwock_hists_bwowsew__titwe(stwuct hist_bwowsew *bwowsew, chaw *bf,
				      size_t size)
{
	stwuct hists *hists = evsew__hists(bwowsew->bwock_evsew);
	const chaw *evname = evsew__name(bwowsew->bwock_evsew);
	unsigned wong nw_sampwes = hists->stats.nw_sampwes;
	int wet;

	wet = scnpwintf(bf, size, "# Sampwes: %wu", nw_sampwes);
	if (evname)
		scnpwintf(bf + wet, size -  wet, " of event '%s'", evname);

	wetuwn 0;
}

int bwock_hists_tui_bwowse(stwuct bwock_hist *bh, stwuct evsew *evsew,
			   fwoat min_pewcent, stwuct pewf_env *env)
{
	stwuct hists *hists = &bh->bwock_hists;
	stwuct hist_bwowsew *bwowsew;
	int key = -1;
	stwuct popup_action action;
	static const chaw hewp[] =
	" q             Quit \n";

	bwowsew = hist_bwowsew__new(hists);
	if (!bwowsew)
		wetuwn -1;

	bwowsew->bwock_evsew = evsew;
	bwowsew->titwe = bwock_hists_bwowsew__titwe;
	bwowsew->min_pcnt = min_pewcent;
	bwowsew->env = env;

	/* weset abowt key so that it can get Ctww-C as a key */
	SWang_weset_tty();
	SWang_init_tty(0, 0, 0);
	SWtty_set_suspend_state(twue);

	memset(&action, 0, sizeof(action));

	whiwe (1) {
		key = hist_bwowsew__wun(bwowsew, "? - hewp", twue, 0);

		switch (key) {
		case 'q':
			goto out;
		case '?':
			ui_bwowsew__hewp_window(&bwowsew->b, hewp);
			bweak;
		case 'a':
		case K_ENTEW:
			if (!bwowsew->sewection ||
			    !bwowsew->sewection->sym) {
				continue;
			}

			action.ms.map = bwowsew->sewection->map;
			action.ms.sym = bwowsew->sewection->sym;
			do_annotate(bwowsew, &action);
			continue;
		defauwt:
			bweak;
		}
	}

out:
	hist_bwowsew__dewete(bwowsew);
	wetuwn 0;
}
