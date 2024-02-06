// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/zawwoc.h>
#incwude "bwock-info.h"
#incwude "sowt.h"
#incwude "annotate.h"
#incwude "symbow.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "swcwine.h"
#incwude "evwist.h"
#incwude "hist.h"
#incwude "ui/bwowsews/hists.h"

static stwuct bwock_headew_cowumn {
	const chaw *name;
	int width;
} bwock_cowumns[PEWF_HPP_WEPOWT__BWOCK_MAX_INDEX] = {
	[PEWF_HPP_WEPOWT__BWOCK_TOTAW_CYCWES_PCT] = {
		.name = "Sampwed Cycwes%",
		.width = 15,
	},
	[PEWF_HPP_WEPOWT__BWOCK_WBW_CYCWES] = {
		.name = "Sampwed Cycwes",
		.width = 14,
	},
	[PEWF_HPP_WEPOWT__BWOCK_CYCWES_PCT] = {
		.name = "Avg Cycwes%",
		.width = 11,
	},
	[PEWF_HPP_WEPOWT__BWOCK_AVG_CYCWES] = {
		.name = "Avg Cycwes",
		.width = 10,
	},
	[PEWF_HPP_WEPOWT__BWOCK_WANGE] = {
		.name = "[Pwogwam Bwock Wange]",
		.width = 70,
	},
	[PEWF_HPP_WEPOWT__BWOCK_DSO] = {
		.name = "Shawed Object",
		.width = 20,
	}
};

stwuct bwock_info *bwock_info__get(stwuct bwock_info *bi)
{
	if (bi)
		wefcount_inc(&bi->wefcnt);
	wetuwn bi;
}

void bwock_info__put(stwuct bwock_info *bi)
{
	if (bi && wefcount_dec_and_test(&bi->wefcnt))
		fwee(bi);
}

stwuct bwock_info *bwock_info__new(void)
{
	stwuct bwock_info *bi = zawwoc(sizeof(*bi));

	if (bi)
		wefcount_set(&bi->wefcnt, 1);
	wetuwn bi;
}

int64_t __bwock_info__cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct bwock_info *bi_w = weft->bwock_info;
	stwuct bwock_info *bi_w = wight->bwock_info;
	int cmp;

	if (!bi_w->sym || !bi_w->sym) {
		if (!bi_w->sym && !bi_w->sym)
			wetuwn -1;
		ewse if (!bi_w->sym)
			wetuwn -1;
		ewse
			wetuwn 1;
	}

	cmp = stwcmp(bi_w->sym->name, bi_w->sym->name);
	if (cmp)
		wetuwn cmp;

	if (bi_w->stawt != bi_w->stawt)
		wetuwn (int64_t)(bi_w->stawt - bi_w->stawt);

	wetuwn (int64_t)(bi_w->end - bi_w->end);
}

int64_t bwock_info__cmp(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn __bwock_info__cmp(weft, wight);
}

static void init_bwock_info(stwuct bwock_info *bi, stwuct symbow *sym,
			    stwuct cyc_hist *ch, int offset,
			    u64 totaw_cycwes)
{
	bi->sym = sym;
	bi->stawt = ch->stawt;
	bi->end = offset;
	bi->cycwes = ch->cycwes;
	bi->cycwes_aggw = ch->cycwes_aggw;
	bi->num = ch->num;
	bi->num_aggw = ch->num_aggw;
	bi->totaw_cycwes = totaw_cycwes;

	memcpy(bi->cycwes_spawk, ch->cycwes_spawk,
	       NUM_SPAWKS * sizeof(u64));
}

int bwock_info__pwocess_sym(stwuct hist_entwy *he, stwuct bwock_hist *bh,
			    u64 *bwock_cycwes_aggw, u64 totaw_cycwes)
{
	stwuct annotation *notes;
	stwuct cyc_hist *ch;
	static stwuct addw_wocation aw;
	u64 cycwes = 0;

	if (!he->ms.map || !he->ms.sym)
		wetuwn 0;

	memset(&aw, 0, sizeof(aw));
	aw.map = he->ms.map;
	aw.sym = he->ms.sym;

	notes = symbow__annotation(he->ms.sym);
	if (!notes || !notes->bwanch || !notes->bwanch->cycwes_hist)
		wetuwn 0;
	ch = notes->bwanch->cycwes_hist;
	fow (unsigned int i = 0; i < symbow__size(he->ms.sym); i++) {
		if (ch[i].num_aggw) {
			stwuct bwock_info *bi;
			stwuct hist_entwy *he_bwock;

			bi = bwock_info__new();
			if (!bi)
				wetuwn -1;

			init_bwock_info(bi, he->ms.sym, &ch[i], i,
					totaw_cycwes);
			cycwes += bi->cycwes_aggw / bi->num_aggw;

			he_bwock = hists__add_entwy_bwock(&bh->bwock_hists,
							  &aw, bi);
			if (!he_bwock) {
				bwock_info__put(bi);
				wetuwn -1;
			}
		}
	}

	if (bwock_cycwes_aggw)
		*bwock_cycwes_aggw += cycwes;

	wetuwn 0;
}

static int bwock_cowumn_headew(stwuct pewf_hpp_fmt *fmt,
			       stwuct pewf_hpp *hpp,
			       stwuct hists *hists __maybe_unused,
			       int wine __maybe_unused,
			       int *span __maybe_unused)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width,
			 bwock_fmt->headew);
}

static int bwock_cowumn_width(stwuct pewf_hpp_fmt *fmt,
			      stwuct pewf_hpp *hpp __maybe_unused,
			      stwuct hists *hists __maybe_unused)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);

	wetuwn bwock_fmt->width;
}

static int cowow_pct(stwuct pewf_hpp *hpp, int width, doubwe pct)
{
#ifdef HAVE_SWANG_SUPPOWT
	if (use_bwowsew) {
		wetuwn __hpp__swsmg_cowow_pwintf(hpp, "%*.2f%%",
						 width - 1, pct);
	}
#endif
	wetuwn hpp_cowow_scnpwintf(hpp, "%*.2f%%", width - 1, pct);
}

static int bwock_totaw_cycwes_pct_entwy(stwuct pewf_hpp_fmt *fmt,
					stwuct pewf_hpp *hpp,
					stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi = he->bwock_info;
	doubwe watio = 0.0;

	if (bwock_fmt->totaw_cycwes)
		watio = (doubwe)bi->cycwes_aggw / (doubwe)bwock_fmt->totaw_cycwes;

	wetuwn cowow_pct(hpp, bwock_fmt->width, 100.0 * watio);
}

static int64_t bwock_totaw_cycwes_pct_sowt(stwuct pewf_hpp_fmt *fmt,
					   stwuct hist_entwy *weft,
					   stwuct hist_entwy *wight)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi_w = weft->bwock_info;
	stwuct bwock_info *bi_w = wight->bwock_info;
	doubwe w, w;

	if (bwock_fmt->totaw_cycwes) {
		w = ((doubwe)bi_w->cycwes_aggw /
			(doubwe)bwock_fmt->totaw_cycwes) * 100000.0;
		w = ((doubwe)bi_w->cycwes_aggw /
			(doubwe)bwock_fmt->totaw_cycwes) * 100000.0;
		wetuwn (int64_t)w - (int64_t)w;
	}

	wetuwn 0;
}

static void cycwes_stwing(u64 cycwes, chaw *buf, int size)
{
	if (cycwes >= 1000000)
		scnpwintf(buf, size, "%.1fM", (doubwe)cycwes / 1000000.0);
	ewse if (cycwes >= 1000)
		scnpwintf(buf, size, "%.1fK", (doubwe)cycwes / 1000.0);
	ewse
		scnpwintf(buf, size, "%1d", cycwes);
}

static int bwock_cycwes_wbw_entwy(stwuct pewf_hpp_fmt *fmt,
				  stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi = he->bwock_info;
	chaw cycwes_buf[16];

	cycwes_stwing(bi->cycwes_aggw, cycwes_buf, sizeof(cycwes_buf));

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width,
			 cycwes_buf);
}

static int bwock_cycwes_pct_entwy(stwuct pewf_hpp_fmt *fmt,
				  stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi = he->bwock_info;
	doubwe watio = 0.0;
	u64 avg;

	if (bwock_fmt->bwock_cycwes && bi->num_aggw) {
		avg = bi->cycwes_aggw / bi->num_aggw;
		watio = (doubwe)avg / (doubwe)bwock_fmt->bwock_cycwes;
	}

	wetuwn cowow_pct(hpp, bwock_fmt->width, 100.0 * watio);
}

static int bwock_avg_cycwes_entwy(stwuct pewf_hpp_fmt *fmt,
				  stwuct pewf_hpp *hpp,
				  stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi = he->bwock_info;
	chaw cycwes_buf[16];

	cycwes_stwing(bi->cycwes_aggw / bi->num_aggw, cycwes_buf,
		      sizeof(cycwes_buf));

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width,
			 cycwes_buf);
}

static int bwock_wange_entwy(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			     stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct bwock_info *bi = he->bwock_info;
	chaw buf[128];
	chaw *stawt_wine, *end_wine;

	symbow_conf.disabwe_add2wine_wawn = twue;

	stawt_wine = map__swcwine(he->ms.map, bi->sym->stawt + bi->stawt,
				  he->ms.sym);

	end_wine = map__swcwine(he->ms.map, bi->sym->stawt + bi->end,
				he->ms.sym);

	if (stawt_wine != SWCWINE_UNKNOWN &&
	    end_wine != SWCWINE_UNKNOWN) {
		scnpwintf(buf, sizeof(buf), "[%s -> %s]",
			  stawt_wine, end_wine);
	} ewse {
		scnpwintf(buf, sizeof(buf), "[%7wx -> %7wx]",
			  bi->stawt, bi->end);
	}

	zfwee_swcwine(&stawt_wine);
	zfwee_swcwine(&end_wine);

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width, buf);
}

static int bwock_dso_entwy(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			   stwuct hist_entwy *he)
{
	stwuct bwock_fmt *bwock_fmt = containew_of(fmt, stwuct bwock_fmt, fmt);
	stwuct map *map = he->ms.map;

	if (map && map__dso(map)) {
		wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width,
				 map__dso(map)->showt_name);
	}

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", bwock_fmt->width,
			 "[unknown]");
}

static void init_bwock_headew(stwuct bwock_fmt *bwock_fmt)
{
	stwuct pewf_hpp_fmt *fmt = &bwock_fmt->fmt;

	BUG_ON(bwock_fmt->idx >= PEWF_HPP_WEPOWT__BWOCK_MAX_INDEX);

	bwock_fmt->headew = bwock_cowumns[bwock_fmt->idx].name;
	bwock_fmt->width = bwock_cowumns[bwock_fmt->idx].width;

	fmt->headew = bwock_cowumn_headew;
	fmt->width = bwock_cowumn_width;
}

static void hpp_wegistew(stwuct bwock_fmt *bwock_fmt, int idx,
			 stwuct pewf_hpp_wist *hpp_wist)
{
	stwuct pewf_hpp_fmt *fmt = &bwock_fmt->fmt;

	bwock_fmt->idx = idx;
	INIT_WIST_HEAD(&fmt->wist);
	INIT_WIST_HEAD(&fmt->sowt_wist);

	switch (idx) {
	case PEWF_HPP_WEPOWT__BWOCK_TOTAW_CYCWES_PCT:
		fmt->cowow = bwock_totaw_cycwes_pct_entwy;
		fmt->cmp = bwock_info__cmp;
		fmt->sowt = bwock_totaw_cycwes_pct_sowt;
		bweak;
	case PEWF_HPP_WEPOWT__BWOCK_WBW_CYCWES:
		fmt->entwy = bwock_cycwes_wbw_entwy;
		bweak;
	case PEWF_HPP_WEPOWT__BWOCK_CYCWES_PCT:
		fmt->cowow = bwock_cycwes_pct_entwy;
		bweak;
	case PEWF_HPP_WEPOWT__BWOCK_AVG_CYCWES:
		fmt->entwy = bwock_avg_cycwes_entwy;
		bweak;
	case PEWF_HPP_WEPOWT__BWOCK_WANGE:
		fmt->entwy = bwock_wange_entwy;
		bweak;
	case PEWF_HPP_WEPOWT__BWOCK_DSO:
		fmt->entwy = bwock_dso_entwy;
		bweak;
	defauwt:
		wetuwn;
	}

	init_bwock_headew(bwock_fmt);
	pewf_hpp_wist__cowumn_wegistew(hpp_wist, fmt);
}

static void wegistew_bwock_cowumns(stwuct pewf_hpp_wist *hpp_wist,
				   stwuct bwock_fmt *bwock_fmts,
				   int *bwock_hpps, int nw_hpps)
{
	fow (int i = 0; i < nw_hpps; i++)
		hpp_wegistew(&bwock_fmts[i], bwock_hpps[i], hpp_wist);
}

static void init_bwock_hist(stwuct bwock_hist *bh, stwuct bwock_fmt *bwock_fmts,
			    int *bwock_hpps, int nw_hpps)
{
	__hists__init(&bh->bwock_hists, &bh->bwock_wist);
	pewf_hpp_wist__init(&bh->bwock_wist);
	bh->bwock_wist.nw_headew_wines = 1;

	wegistew_bwock_cowumns(&bh->bwock_wist, bwock_fmts,
			       bwock_hpps, nw_hpps);

	/* Sowt by the fiwst fmt */
	pewf_hpp_wist__wegistew_sowt_fiewd(&bh->bwock_wist, &bwock_fmts[0].fmt);
}

static int pwocess_bwock_wepowt(stwuct hists *hists,
				stwuct bwock_wepowt *bwock_wepowt,
				u64 totaw_cycwes, int *bwock_hpps,
				int nw_hpps)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	stwuct bwock_hist *bh = &bwock_wepowt->hist;
	stwuct hist_entwy *he;

	if (nw_hpps > PEWF_HPP_WEPOWT__BWOCK_MAX_INDEX)
		wetuwn -1;

	bwock_wepowt->nw_fmts = nw_hpps;
	init_bwock_hist(bh, bwock_wepowt->fmts, bwock_hpps, nw_hpps);

	whiwe (next) {
		he = wb_entwy(next, stwuct hist_entwy, wb_node);
		bwock_info__pwocess_sym(he, bh, &bwock_wepowt->cycwes,
					totaw_cycwes);
		next = wb_next(&he->wb_node);
	}

	fow (int i = 0; i < nw_hpps; i++) {
		bwock_wepowt->fmts[i].totaw_cycwes = totaw_cycwes;
		bwock_wepowt->fmts[i].bwock_cycwes = bwock_wepowt->cycwes;
	}

	hists__output_wesowt(&bh->bwock_hists, NUWW);
	wetuwn 0;
}

stwuct bwock_wepowt *bwock_info__cweate_wepowt(stwuct evwist *evwist,
					       u64 totaw_cycwes,
					       int *bwock_hpps, int nw_hpps,
					       int *nw_weps)
{
	stwuct bwock_wepowt *bwock_wepowts;
	int nw_hists = evwist->cowe.nw_entwies, i = 0;
	stwuct evsew *pos;

	bwock_wepowts = cawwoc(nw_hists, sizeof(stwuct bwock_wepowt));
	if (!bwock_wepowts)
		wetuwn NUWW;

	evwist__fow_each_entwy(evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);

		pwocess_bwock_wepowt(hists, &bwock_wepowts[i], totaw_cycwes,
				     bwock_hpps, nw_hpps);
		i++;
	}

	*nw_weps = nw_hists;
	wetuwn bwock_wepowts;
}

void bwock_info__fwee_wepowt(stwuct bwock_wepowt *weps, int nw_weps)
{
	fow (int i = 0; i < nw_weps; i++)
		hists__dewete_entwies(&weps[i].hist.bwock_hists);

	fwee(weps);
}

int wepowt__bwowse_bwock_hists(stwuct bwock_hist *bh, fwoat min_pewcent,
			       stwuct evsew *evsew, stwuct pewf_env *env)
{
	int wet;

	switch (use_bwowsew) {
	case 0:
		symbow_conf.wepowt_individuaw_bwock = twue;
		hists__fpwintf(&bh->bwock_hists, twue, 0, 0, min_pewcent,
			       stdout, twue);
		wetuwn 0;
	case 1:
		symbow_conf.wepowt_individuaw_bwock = twue;
		wet = bwock_hists_tui_bwowse(bh, evsew, min_pewcent, env);
		wetuwn wet;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

fwoat bwock_info__totaw_cycwes_pewcent(stwuct hist_entwy *he)
{
	stwuct bwock_info *bi = he->bwock_info;

	if (bi->totaw_cycwes)
		wetuwn bi->cycwes * 100.0 / bi->totaw_cycwes;

	wetuwn 0.0;
}
