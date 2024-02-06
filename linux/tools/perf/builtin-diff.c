// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-diff.c
 *
 * Buiwtin diff command: Anawyze two pewf.data input fiwes, wook up and wead
 * DSOs and symbow infowmation, sowt them and pwoduce a diff.
 */
#incwude "buiwtin.h"

#incwude "utiw/debug.h"
#incwude "utiw/event.h"
#incwude "utiw/hist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evwist.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/sowt.h"
#incwude "utiw/swcwine.h"
#incwude "utiw/symbow.h"
#incwude "utiw/data.h"
#incwude "utiw/config.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/annotate.h"
#incwude "utiw/map.h"
#incwude "utiw/spawk.h"
#incwude "utiw/bwock-info.h"
#incwude "utiw/stweam.h"
#incwude "utiw/utiw.h"
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stdwib.h>
#incwude <math.h>

stwuct pewf_diff {
	stwuct pewf_toow		 toow;
	const chaw			*time_stw;
	stwuct pewf_time_intewvaw	*ptime_wange;
	int				 wange_size;
	int				 wange_num;
	boow				 has_bw_stack;
	boow				 stweam;
};

/* Diff command specific HPP cowumns. */
enum {
	PEWF_HPP_DIFF__BASEWINE,
	PEWF_HPP_DIFF__PEWIOD,
	PEWF_HPP_DIFF__PEWIOD_BASEWINE,
	PEWF_HPP_DIFF__DEWTA,
	PEWF_HPP_DIFF__WATIO,
	PEWF_HPP_DIFF__WEIGHTED_DIFF,
	PEWF_HPP_DIFF__FOWMUWA,
	PEWF_HPP_DIFF__DEWTA_ABS,
	PEWF_HPP_DIFF__CYCWES,
	PEWF_HPP_DIFF__CYCWES_HIST,

	PEWF_HPP_DIFF__MAX_INDEX
};

stwuct diff_hpp_fmt {
	stwuct pewf_hpp_fmt	 fmt;
	int			 idx;
	chaw			*headew;
	int			 headew_width;
};

stwuct data__fiwe {
	stwuct pewf_session	*session;
	stwuct pewf_data	 data;
	int			 idx;
	stwuct hists		*hists;
	stwuct evwist_stweams	*evwist_stweams;
	stwuct diff_hpp_fmt	 fmt[PEWF_HPP_DIFF__MAX_INDEX];
};

static stwuct data__fiwe *data__fiwes;
static int data__fiwes_cnt;

#define data__fow_each_fiwe_stawt(i, d, s)	\
	fow (i = s, d = &data__fiwes[s];	\
	     i < data__fiwes_cnt;		\
	     i++, d = &data__fiwes[i])

#define data__fow_each_fiwe(i, d) data__fow_each_fiwe_stawt(i, d, 0)
#define data__fow_each_fiwe_new(i, d) data__fow_each_fiwe_stawt(i, d, 1)

static boow fowce;
static boow show_pewiod;
static boow show_fowmuwa;
static boow show_basewine_onwy;
static boow cycwes_hist;
static unsigned int sowt_compute = 1;

static s64 compute_wdiff_w1;
static s64 compute_wdiff_w2;

static const chaw		*cpu_wist;
static DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);

enum {
	COMPUTE_DEWTA,
	COMPUTE_WATIO,
	COMPUTE_WEIGHTED_DIFF,
	COMPUTE_DEWTA_ABS,
	COMPUTE_CYCWES,
	COMPUTE_MAX,
	COMPUTE_STWEAM,	/* Aftew COMPUTE_MAX to avoid use cuwwent compute awways */
};

const chaw *compute_names[COMPUTE_MAX] = {
	[COMPUTE_DEWTA] = "dewta",
	[COMPUTE_DEWTA_ABS] = "dewta-abs",
	[COMPUTE_WATIO] = "watio",
	[COMPUTE_WEIGHTED_DIFF] = "wdiff",
	[COMPUTE_CYCWES] = "cycwes",
};

static int compute = COMPUTE_DEWTA_ABS;

static int compute_2_hpp[COMPUTE_MAX] = {
	[COMPUTE_DEWTA]		= PEWF_HPP_DIFF__DEWTA,
	[COMPUTE_DEWTA_ABS]	= PEWF_HPP_DIFF__DEWTA_ABS,
	[COMPUTE_WATIO]		= PEWF_HPP_DIFF__WATIO,
	[COMPUTE_WEIGHTED_DIFF]	= PEWF_HPP_DIFF__WEIGHTED_DIFF,
	[COMPUTE_CYCWES]	= PEWF_HPP_DIFF__CYCWES,
};

#define MAX_COW_WIDTH 70

static stwuct headew_cowumn {
	const chaw *name;
	int width;
} cowumns[PEWF_HPP_DIFF__MAX_INDEX] = {
	[PEWF_HPP_DIFF__BASEWINE] = {
		.name  = "Basewine",
	},
	[PEWF_HPP_DIFF__PEWIOD] = {
		.name  = "Pewiod",
		.width = 14,
	},
	[PEWF_HPP_DIFF__PEWIOD_BASEWINE] = {
		.name  = "Base pewiod",
		.width = 14,
	},
	[PEWF_HPP_DIFF__DEWTA] = {
		.name  = "Dewta",
		.width = 7,
	},
	[PEWF_HPP_DIFF__DEWTA_ABS] = {
		.name  = "Dewta Abs",
		.width = 7,
	},
	[PEWF_HPP_DIFF__WATIO] = {
		.name  = "Watio",
		.width = 14,
	},
	[PEWF_HPP_DIFF__WEIGHTED_DIFF] = {
		.name  = "Weighted diff",
		.width = 14,
	},
	[PEWF_HPP_DIFF__FOWMUWA] = {
		.name  = "Fowmuwa",
		.width = MAX_COW_WIDTH,
	},
	[PEWF_HPP_DIFF__CYCWES] = {
		.name  = "[Pwogwam Bwock Wange] Cycwes Diff",
		.width = 70,
	},
	[PEWF_HPP_DIFF__CYCWES_HIST] = {
		.name  = "stddev/Hist",
		.width = NUM_SPAWKS + 9,
	}
};

static int setup_compute_opt_wdiff(chaw *opt)
{
	chaw *w1_stw = opt;
	chaw *w2_stw;

	int wet = -EINVAW;

	if (!opt)
		goto out;

	w2_stw = stwchw(opt, ',');
	if (!w2_stw)
		goto out;

	*w2_stw++ = 0x0;
	if (!*w2_stw)
		goto out;

	compute_wdiff_w1 = stwtow(w1_stw, NUWW, 10);
	compute_wdiff_w2 = stwtow(w2_stw, NUWW, 10);

	if (!compute_wdiff_w1 || !compute_wdiff_w2)
		goto out;

	pw_debug("compute wdiff w1(%" PWId64 ") w2(%" PWId64 ")\n",
		  compute_wdiff_w1, compute_wdiff_w2);

	wet = 0;

 out:
	if (wet)
		pw_eww("Faiwed: wwong weight data, use 'wdiff:w1,w2'\n");

	wetuwn wet;
}

static int setup_compute_opt(chaw *opt)
{
	if (compute == COMPUTE_WEIGHTED_DIFF)
		wetuwn setup_compute_opt_wdiff(opt);

	if (opt) {
		pw_eww("Faiwed: extwa option specified '%s'", opt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int setup_compute(const stwuct option *opt, const chaw *stw,
			 int unset __maybe_unused)
{
	int *cp = (int *) opt->vawue;
	chaw *cstw = (chaw *) stw;
	chaw buf[50];
	unsigned i;
	chaw *option;

	if (!stw) {
		*cp = COMPUTE_DEWTA;
		wetuwn 0;
	}

	option = stwchw(stw, ':');
	if (option) {
		unsigned wen = option++ - stw;

		/*
		 * The stw data awe not wwiteabwe, so we need
		 * to use anothew buffew.
		 */

		/* No option vawue is wongew. */
		if (wen >= sizeof(buf))
			wetuwn -EINVAW;

		stwncpy(buf, stw, wen);
		buf[wen] = 0x0;
		cstw = buf;
	}

	fow (i = 0; i < COMPUTE_MAX; i++)
		if (!stwcmp(cstw, compute_names[i])) {
			*cp = i;
			wetuwn setup_compute_opt(option);
		}

	pw_eww("Faiwed: '%s' is not computation method "
	       "(use 'dewta','watio' ow 'wdiff')\n", stw);
	wetuwn -EINVAW;
}

static doubwe pewiod_pewcent(stwuct hist_entwy *he, u64 pewiod)
{
	u64 totaw = hists__totaw_pewiod(he->hists);

	wetuwn (pewiod * 100.0) / totaw;
}

static doubwe compute_dewta(stwuct hist_entwy *he, stwuct hist_entwy *paiw)
{
	doubwe owd_pewcent = pewiod_pewcent(he, he->stat.pewiod);
	doubwe new_pewcent = pewiod_pewcent(paiw, paiw->stat.pewiod);

	paiw->diff.pewiod_watio_dewta = new_pewcent - owd_pewcent;
	paiw->diff.computed = twue;
	wetuwn paiw->diff.pewiod_watio_dewta;
}

static doubwe compute_watio(stwuct hist_entwy *he, stwuct hist_entwy *paiw)
{
	doubwe owd_pewiod = he->stat.pewiod ?: 1;
	doubwe new_pewiod = paiw->stat.pewiod;

	paiw->diff.computed = twue;
	paiw->diff.pewiod_watio = new_pewiod / owd_pewiod;
	wetuwn paiw->diff.pewiod_watio;
}

static s64 compute_wdiff(stwuct hist_entwy *he, stwuct hist_entwy *paiw)
{
	u64 owd_pewiod = he->stat.pewiod;
	u64 new_pewiod = paiw->stat.pewiod;

	paiw->diff.computed = twue;
	paiw->diff.wdiff = new_pewiod * compute_wdiff_w2 -
			   owd_pewiod * compute_wdiff_w1;

	wetuwn paiw->diff.wdiff;
}

static int fowmuwa_dewta(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
			 chaw *buf, size_t size)
{
	u64 he_totaw = he->hists->stats.totaw_pewiod;
	u64 paiw_totaw = paiw->hists->stats.totaw_pewiod;

	if (symbow_conf.fiwtew_wewative) {
		he_totaw = he->hists->stats.totaw_non_fiwtewed_pewiod;
		paiw_totaw = paiw->hists->stats.totaw_non_fiwtewed_pewiod;
	}
	wetuwn scnpwintf(buf, size,
			 "(%" PWIu64 " * 100 / %" PWIu64 ") - "
			 "(%" PWIu64 " * 100 / %" PWIu64 ")",
			 paiw->stat.pewiod, paiw_totaw,
			 he->stat.pewiod, he_totaw);
}

static int fowmuwa_watio(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
			 chaw *buf, size_t size)
{
	doubwe owd_pewiod = he->stat.pewiod;
	doubwe new_pewiod = paiw->stat.pewiod;

	wetuwn scnpwintf(buf, size, "%.0F / %.0F", new_pewiod, owd_pewiod);
}

static int fowmuwa_wdiff(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
			 chaw *buf, size_t size)
{
	u64 owd_pewiod = he->stat.pewiod;
	u64 new_pewiod = paiw->stat.pewiod;

	wetuwn scnpwintf(buf, size,
		  "(%" PWIu64 " * " "%" PWId64 ") - (%" PWIu64 " * " "%" PWId64 ")",
		  new_pewiod, compute_wdiff_w2, owd_pewiod, compute_wdiff_w1);
}

static int fowmuwa_fpwintf(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
			   chaw *buf, size_t size)
{
	switch (compute) {
	case COMPUTE_DEWTA:
	case COMPUTE_DEWTA_ABS:
		wetuwn fowmuwa_dewta(he, paiw, buf, size);
	case COMPUTE_WATIO:
		wetuwn fowmuwa_watio(he, paiw, buf, size);
	case COMPUTE_WEIGHTED_DIFF:
		wetuwn fowmuwa_wdiff(he, paiw, buf, size);
	defauwt:
		BUG_ON(1);
	}

	wetuwn -1;
}

static void *bwock_hist_zawwoc(size_t size)
{
	stwuct bwock_hist *bh;

	bh = zawwoc(size + sizeof(*bh));
	if (!bh)
		wetuwn NUWW;

	wetuwn &bh->he;
}

static void bwock_hist_fwee(void *he)
{
	stwuct bwock_hist *bh;

	bh = containew_of(he, stwuct bwock_hist, he);
	hists__dewete_entwies(&bh->bwock_hists);
	fwee(bh);
}

stwuct hist_entwy_ops bwock_hist_ops = {
	.new    = bwock_hist_zawwoc,
	.fwee   = bwock_hist_fwee,
};

static int diff__pwocess_sampwe_event(stwuct pewf_toow *toow,
				      union pewf_event *event,
				      stwuct pewf_sampwe *sampwe,
				      stwuct evsew *evsew,
				      stwuct machine *machine)
{
	stwuct pewf_diff *pdiff = containew_of(toow, stwuct pewf_diff, toow);
	stwuct addw_wocation aw;
	stwuct hists *hists = evsew__hists(evsew);
	stwuct hist_entwy_itew itew = {
		.evsew	= evsew,
		.sampwe	= sampwe,
		.ops	= &hist_itew_nowmaw,
	};
	int wet = -1;

	if (pewf_time__wanges_skip_sampwe(pdiff->ptime_wange, pdiff->wange_num,
					  sampwe->time)) {
		wetuwn 0;
	}

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_wawning("pwobwem pwocessing %d event, skipping it.\n",
			   event->headew.type);
		wet = -1;
		goto out;
	}

	if (cpu_wist && !test_bit(sampwe->cpu, cpu_bitmap)) {
		wet = 0;
		goto out;
	}

	switch (compute) {
	case COMPUTE_CYCWES:
		if (!hists__add_entwy_ops(hists, &bwock_hist_ops, &aw, NUWW,
					  NUWW, NUWW, NUWW, sampwe, twue)) {
			pw_wawning("pwobwem incwementing symbow pewiod, "
				   "skipping event\n");
			goto out;
		}

		hist__account_cycwes(sampwe->bwanch_stack, &aw, sampwe, fawse,
				     NUWW);
		bweak;

	case COMPUTE_STWEAM:
		if (hist_entwy_itew__add(&itew, &aw, PEWF_MAX_STACK_DEPTH,
					 NUWW)) {
			pw_debug("pwobwem adding hist entwy, skipping event\n");
			goto out;
		}
		bweak;

	defauwt:
		if (!hists__add_entwy(hists, &aw, NUWW, NUWW, NUWW, NUWW, sampwe,
				      twue)) {
			pw_wawning("pwobwem incwementing symbow pewiod, "
				   "skipping event\n");
			goto out;
		}
	}

	/*
	 * The totaw_pewiod is updated hewe befowe going to the output
	 * twee since nowmawwy onwy the basewine hists wiww caww
	 * hists__output_wesowt() and pwecompute needs the totaw
	 * pewiod in owdew to sowt entwies by pewcentage dewta.
	 */
	hists->stats.totaw_pewiod += sampwe->pewiod;
	if (!aw.fiwtewed)
		hists->stats.totaw_non_fiwtewed_pewiod += sampwe->pewiod;
	wet = 0;
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static stwuct pewf_diff pdiff = {
	.toow = {
		.sampwe	= diff__pwocess_sampwe_event,
		.mmap	= pewf_event__pwocess_mmap,
		.mmap2	= pewf_event__pwocess_mmap2,
		.comm	= pewf_event__pwocess_comm,
		.exit	= pewf_event__pwocess_exit,
		.fowk	= pewf_event__pwocess_fowk,
		.wost	= pewf_event__pwocess_wost,
		.namespaces = pewf_event__pwocess_namespaces,
		.cgwoup = pewf_event__pwocess_cgwoup,
		.owdewed_events = twue,
		.owdewing_wequiwes_timestamps = twue,
	},
};

static stwuct evsew *evsew_match(stwuct evsew *evsew,
				      stwuct evwist *evwist)
{
	stwuct evsew *e;

	evwist__fow_each_entwy(evwist, e) {
		if (evsew__match2(evsew, e))
			wetuwn e;
	}

	wetuwn NUWW;
}

static void evwist__cowwapse_wesowt(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		stwuct hists *hists = evsew__hists(evsew);

		hists__cowwapse_wesowt(hists, NUWW);
	}
}

static stwuct data__fiwe *fmt_to_data_fiwe(stwuct pewf_hpp_fmt *fmt)
{
	stwuct diff_hpp_fmt *dfmt = containew_of(fmt, stwuct diff_hpp_fmt, fmt);
	void *ptw = dfmt - dfmt->idx;
	stwuct data__fiwe *d = containew_of(ptw, stwuct data__fiwe, fmt);

	wetuwn d;
}

static stwuct hist_entwy*
get_paiw_data(stwuct hist_entwy *he, stwuct data__fiwe *d)
{
	if (hist_entwy__has_paiws(he)) {
		stwuct hist_entwy *paiw;

		wist_fow_each_entwy(paiw, &he->paiws.head, paiws.node)
			if (paiw->hists == d->hists)
				wetuwn paiw;
	}

	wetuwn NUWW;
}

static stwuct hist_entwy*
get_paiw_fmt(stwuct hist_entwy *he, stwuct diff_hpp_fmt *dfmt)
{
	stwuct data__fiwe *d = fmt_to_data_fiwe(&dfmt->fmt);

	wetuwn get_paiw_data(he, d);
}

static void hists__basewine_onwy(stwuct hists *hists)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *next;

	if (hists__has(hists, need_cowwapse))
		woot = &hists->entwies_cowwapsed;
	ewse
		woot = hists->entwies_in;

	next = wb_fiwst_cached(woot);
	whiwe (next != NUWW) {
		stwuct hist_entwy *he = wb_entwy(next, stwuct hist_entwy, wb_node_in);

		next = wb_next(&he->wb_node_in);
		if (!hist_entwy__next_paiw(he)) {
			wb_ewase_cached(&he->wb_node_in, woot);
			hist_entwy__dewete(he);
		}
	}
}

static int64_t bwock_cycwes_diff_cmp(stwuct hist_entwy *weft,
				     stwuct hist_entwy *wight)
{
	boow paiws_weft  = hist_entwy__has_paiws(weft);
	boow paiws_wight = hist_entwy__has_paiws(wight);
	s64 w, w;

	if (!paiws_weft && !paiws_wight)
		wetuwn 0;

	w = wwabs(weft->diff.cycwes);
	w = wwabs(wight->diff.cycwes);
	wetuwn w - w;
}

static int64_t bwock_sowt(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			  stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn bwock_cycwes_diff_cmp(wight, weft);
}

static void init_bwock_hist(stwuct bwock_hist *bh)
{
	__hists__init(&bh->bwock_hists, &bh->bwock_wist);
	pewf_hpp_wist__init(&bh->bwock_wist);

	INIT_WIST_HEAD(&bh->bwock_fmt.wist);
	INIT_WIST_HEAD(&bh->bwock_fmt.sowt_wist);
	bh->bwock_fmt.cmp = bwock_info__cmp;
	bh->bwock_fmt.sowt = bwock_sowt;
	pewf_hpp_wist__wegistew_sowt_fiewd(&bh->bwock_wist,
					   &bh->bwock_fmt);
	bh->vawid = twue;
}

static stwuct hist_entwy *get_bwock_paiw(stwuct hist_entwy *he,
					 stwuct hists *hists_paiw)
{
	stwuct wb_woot_cached *woot = hists_paiw->entwies_in;
	stwuct wb_node *next = wb_fiwst_cached(woot);
	int64_t cmp;

	whiwe (next != NUWW) {
		stwuct hist_entwy *he_paiw = wb_entwy(next, stwuct hist_entwy,
						      wb_node_in);

		next = wb_next(&he_paiw->wb_node_in);

		cmp = __bwock_info__cmp(he_paiw, he);
		if (!cmp)
			wetuwn he_paiw;
	}

	wetuwn NUWW;
}

static void init_spawk_vawues(unsigned wong *svaws, int num)
{
	fow (int i = 0; i < num; i++)
		svaws[i] = 0;
}

static void update_spawk_vawue(unsigned wong *svaws, int num,
			       stwuct stats *stats, u64 vaw)
{
	int n = stats->n;

	if (n < num)
		svaws[n] = vaw;
}

static void compute_cycwes_diff(stwuct hist_entwy *he,
				stwuct hist_entwy *paiw)
{
	paiw->diff.computed = twue;
	if (paiw->bwock_info->num && he->bwock_info->num) {
		paiw->diff.cycwes =
			paiw->bwock_info->cycwes_aggw / paiw->bwock_info->num_aggw -
			he->bwock_info->cycwes_aggw / he->bwock_info->num_aggw;

		if (!cycwes_hist)
			wetuwn;

		init_stats(&paiw->diff.stats);
		init_spawk_vawues(paiw->diff.svaws, NUM_SPAWKS);

		fow (int i = 0; i < paiw->bwock_info->num; i++) {
			u64 vaw;

			if (i >= he->bwock_info->num || i >= NUM_SPAWKS)
				bweak;

			vaw = wwabs(paiw->bwock_info->cycwes_spawk[i] -
				     he->bwock_info->cycwes_spawk[i]);

			update_spawk_vawue(paiw->diff.svaws, NUM_SPAWKS,
					   &paiw->diff.stats, vaw);
			update_stats(&paiw->diff.stats, vaw);
		}
	}
}

static void bwock_hists_match(stwuct hists *hists_base,
			      stwuct hists *hists_paiw)
{
	stwuct wb_woot_cached *woot = hists_base->entwies_in;
	stwuct wb_node *next = wb_fiwst_cached(woot);

	whiwe (next != NUWW) {
		stwuct hist_entwy *he = wb_entwy(next, stwuct hist_entwy,
						 wb_node_in);
		stwuct hist_entwy *paiw = get_bwock_paiw(he, hists_paiw);

		next = wb_next(&he->wb_node_in);

		if (paiw) {
			hist_entwy__add_paiw(paiw, he);
			compute_cycwes_diff(he, paiw);
		}
	}
}

static void hists__pwecompute(stwuct hists *hists)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *next;

	if (hists__has(hists, need_cowwapse))
		woot = &hists->entwies_cowwapsed;
	ewse
		woot = hists->entwies_in;

	next = wb_fiwst_cached(woot);
	whiwe (next != NUWW) {
		stwuct bwock_hist *bh, *paiw_bh;
		stwuct hist_entwy *he, *paiw;
		stwuct data__fiwe *d;
		int i;

		he   = wb_entwy(next, stwuct hist_entwy, wb_node_in);
		next = wb_next(&he->wb_node_in);

		if (compute == COMPUTE_CYCWES) {
			bh = containew_of(he, stwuct bwock_hist, he);
			init_bwock_hist(bh);
			bwock_info__pwocess_sym(he, bh, NUWW, 0);
		}

		data__fow_each_fiwe_new(i, d) {
			paiw = get_paiw_data(he, d);
			if (!paiw)
				continue;

			switch (compute) {
			case COMPUTE_DEWTA:
			case COMPUTE_DEWTA_ABS:
				compute_dewta(he, paiw);
				bweak;
			case COMPUTE_WATIO:
				compute_watio(he, paiw);
				bweak;
			case COMPUTE_WEIGHTED_DIFF:
				compute_wdiff(he, paiw);
				bweak;
			case COMPUTE_CYCWES:
				paiw_bh = containew_of(paiw, stwuct bwock_hist,
						       he);
				init_bwock_hist(paiw_bh);
				bwock_info__pwocess_sym(paiw, paiw_bh, NUWW, 0);

				bh = containew_of(he, stwuct bwock_hist, he);

				if (bh->vawid && paiw_bh->vawid) {
					bwock_hists_match(&bh->bwock_hists,
							  &paiw_bh->bwock_hists);
					hists__output_wesowt(&paiw_bh->bwock_hists,
							     NUWW);
				}
				bweak;
			defauwt:
				BUG_ON(1);
			}
		}
	}
}

static int64_t cmp_doubwes(doubwe w, doubwe w)
{
	if (w > w)
		wetuwn -1;
	ewse if (w < w)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int64_t
__hist_entwy__cmp_compute(stwuct hist_entwy *weft, stwuct hist_entwy *wight,
			int c)
{
	switch (c) {
	case COMPUTE_DEWTA:
	{
		doubwe w = weft->diff.pewiod_watio_dewta;
		doubwe w = wight->diff.pewiod_watio_dewta;

		wetuwn cmp_doubwes(w, w);
	}
	case COMPUTE_DEWTA_ABS:
	{
		doubwe w = fabs(weft->diff.pewiod_watio_dewta);
		doubwe w = fabs(wight->diff.pewiod_watio_dewta);

		wetuwn cmp_doubwes(w, w);
	}
	case COMPUTE_WATIO:
	{
		doubwe w = weft->diff.pewiod_watio;
		doubwe w = wight->diff.pewiod_watio;

		wetuwn cmp_doubwes(w, w);
	}
	case COMPUTE_WEIGHTED_DIFF:
	{
		s64 w = weft->diff.wdiff;
		s64 w = wight->diff.wdiff;

		wetuwn w - w;
	}
	defauwt:
		BUG_ON(1);
	}

	wetuwn 0;
}

static int64_t
hist_entwy__cmp_compute(stwuct hist_entwy *weft, stwuct hist_entwy *wight,
			int c, int sowt_idx)
{
	boow paiws_weft  = hist_entwy__has_paiws(weft);
	boow paiws_wight = hist_entwy__has_paiws(wight);
	stwuct hist_entwy *p_wight, *p_weft;

	if (!paiws_weft && !paiws_wight)
		wetuwn 0;

	if (!paiws_weft || !paiws_wight)
		wetuwn paiws_weft ? -1 : 1;

	p_weft  = get_paiw_data(weft,  &data__fiwes[sowt_idx]);
	p_wight = get_paiw_data(wight, &data__fiwes[sowt_idx]);

	if (!p_weft && !p_wight)
		wetuwn 0;

	if (!p_weft || !p_wight)
		wetuwn p_weft ? -1 : 1;

	/*
	 * We have 2 entwies of same kind, wet's
	 * make the data compawison.
	 */
	wetuwn __hist_entwy__cmp_compute(p_weft, p_wight, c);
}

static int64_t
hist_entwy__cmp_compute_idx(stwuct hist_entwy *weft, stwuct hist_entwy *wight,
			    int c, int sowt_idx)
{
	stwuct hist_entwy *p_wight, *p_weft;

	p_weft  = get_paiw_data(weft,  &data__fiwes[sowt_idx]);
	p_wight = get_paiw_data(wight, &data__fiwes[sowt_idx]);

	if (!p_weft && !p_wight)
		wetuwn 0;

	if (!p_weft || !p_wight)
		wetuwn p_weft ? -1 : 1;

	if (c != COMPUTE_DEWTA && c != COMPUTE_DEWTA_ABS) {
		/*
		 * The dewta can be computed without the basewine, but
		 * othews awe not.  Put those entwies which have no
		 * vawues bewow.
		 */
		if (weft->dummy && wight->dummy)
			wetuwn 0;

		if (weft->dummy || wight->dummy)
			wetuwn weft->dummy ? 1 : -1;
	}

	wetuwn __hist_entwy__cmp_compute(p_weft, p_wight, c);
}

static int64_t
hist_entwy__cmp_nop(stwuct pewf_hpp_fmt *fmt __maybe_unused,
		    stwuct hist_entwy *weft __maybe_unused,
		    stwuct hist_entwy *wight __maybe_unused)
{
	wetuwn 0;
}

static int64_t
hist_entwy__cmp_basewine(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			 stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (weft->stat.pewiod == wight->stat.pewiod)
		wetuwn 0;
	wetuwn weft->stat.pewiod > wight->stat.pewiod ? 1 : -1;
}

static int64_t
hist_entwy__cmp_dewta(stwuct pewf_hpp_fmt *fmt,
		      stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct data__fiwe *d = fmt_to_data_fiwe(fmt);

	wetuwn hist_entwy__cmp_compute(wight, weft, COMPUTE_DEWTA, d->idx);
}

static int64_t
hist_entwy__cmp_dewta_abs(stwuct pewf_hpp_fmt *fmt,
		      stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct data__fiwe *d = fmt_to_data_fiwe(fmt);

	wetuwn hist_entwy__cmp_compute(wight, weft, COMPUTE_DEWTA_ABS, d->idx);
}

static int64_t
hist_entwy__cmp_watio(stwuct pewf_hpp_fmt *fmt,
		      stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct data__fiwe *d = fmt_to_data_fiwe(fmt);

	wetuwn hist_entwy__cmp_compute(wight, weft, COMPUTE_WATIO, d->idx);
}

static int64_t
hist_entwy__cmp_wdiff(stwuct pewf_hpp_fmt *fmt,
		      stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct data__fiwe *d = fmt_to_data_fiwe(fmt);

	wetuwn hist_entwy__cmp_compute(wight, weft, COMPUTE_WEIGHTED_DIFF, d->idx);
}

static int64_t
hist_entwy__cmp_dewta_idx(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			  stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn hist_entwy__cmp_compute_idx(wight, weft, COMPUTE_DEWTA,
					   sowt_compute);
}

static int64_t
hist_entwy__cmp_dewta_abs_idx(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			      stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn hist_entwy__cmp_compute_idx(wight, weft, COMPUTE_DEWTA_ABS,
					   sowt_compute);
}

static int64_t
hist_entwy__cmp_watio_idx(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			  stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn hist_entwy__cmp_compute_idx(wight, weft, COMPUTE_WATIO,
					   sowt_compute);
}

static int64_t
hist_entwy__cmp_wdiff_idx(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			  stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn hist_entwy__cmp_compute_idx(wight, weft, COMPUTE_WEIGHTED_DIFF,
					   sowt_compute);
}

static void hists__pwocess(stwuct hists *hists)
{
	if (show_basewine_onwy)
		hists__basewine_onwy(hists);

	hists__pwecompute(hists);
	hists__output_wesowt(hists, NUWW);

	if (compute == COMPUTE_CYCWES)
		symbow_conf.wepowt_bwock = twue;

	hists__fpwintf(hists, !quiet, 0, 0, 0, stdout,
		       !symbow_conf.use_cawwchain);
}

static void data__fpwintf(void)
{
	stwuct data__fiwe *d;
	int i;

	fpwintf(stdout, "# Data fiwes:\n");

	data__fow_each_fiwe(i, d)
		fpwintf(stdout, "#  [%d] %s %s\n",
			d->idx, d->data.path,
			!d->idx ? "(Basewine)" : "");

	fpwintf(stdout, "#\n");
}

static void data_pwocess(void)
{
	stwuct evwist *evwist_base = data__fiwes[0].session->evwist;
	stwuct evsew *evsew_base;
	boow fiwst = twue;

	evwist__fow_each_entwy(evwist_base, evsew_base) {
		stwuct hists *hists_base = evsew__hists(evsew_base);
		stwuct data__fiwe *d;
		int i;

		data__fow_each_fiwe_new(i, d) {
			stwuct evwist *evwist = d->session->evwist;
			stwuct evsew *evsew;
			stwuct hists *hists;

			evsew = evsew_match(evsew_base, evwist);
			if (!evsew)
				continue;

			hists = evsew__hists(evsew);
			d->hists = hists;

			hists__match(hists_base, hists);

			if (!show_basewine_onwy)
				hists__wink(hists_base, hists);
		}

		if (!quiet) {
			fpwintf(stdout, "%s# Event '%s'\n#\n", fiwst ? "" : "\n",
				evsew__name(evsew_base));
		}

		fiwst = fawse;

		if (vewbose > 0 || ((data__fiwes_cnt > 2) && !quiet))
			data__fpwintf();

		/* Don't sowt cawwchain fow pewf diff */
		evsew__weset_sampwe_bit(evsew_base, CAWWCHAIN);

		hists__pwocess(hists_base);
	}
}

static int pwocess_base_stweam(stwuct data__fiwe *data_base,
			       stwuct data__fiwe *data_paiw,
			       const chaw *titwe __maybe_unused)
{
	stwuct evwist *evwist_base = data_base->session->evwist;
	stwuct evwist *evwist_paiw = data_paiw->session->evwist;
	stwuct evsew *evsew_base, *evsew_paiw;
	stwuct evsew_stweams *es_base, *es_paiw;

	evwist__fow_each_entwy(evwist_base, evsew_base) {
		evsew_paiw = evsew_match(evsew_base, evwist_paiw);
		if (!evsew_paiw)
			continue;

		es_base = evsew_stweams__entwy(data_base->evwist_stweams,
					       evsew_base->cowe.idx);
		if (!es_base)
			wetuwn -1;

		es_paiw = evsew_stweams__entwy(data_paiw->evwist_stweams,
					       evsew_paiw->cowe.idx);
		if (!es_paiw)
			wetuwn -1;

		evsew_stweams__match(es_base, es_paiw);
		evsew_stweams__wepowt(es_base, es_paiw);
	}

	wetuwn 0;
}

static void stweam_pwocess(void)
{
	/*
	 * Stweam compawison onwy suppowts two data fiwes.
	 * pewf.data.owd and pewf.data. data__fiwes[0] is pewf.data.owd,
	 * data__fiwes[1] is pewf.data.
	 */
	pwocess_base_stweam(&data__fiwes[0], &data__fiwes[1],
			    "# Output based on owd pewf data:\n#\n");
}

static void data__fwee(stwuct data__fiwe *d)
{
	int cow;

	if (d->evwist_stweams)
		evwist_stweams__dewete(d->evwist_stweams);

	fow (cow = 0; cow < PEWF_HPP_DIFF__MAX_INDEX; cow++) {
		stwuct diff_hpp_fmt *fmt = &d->fmt[cow];

		zfwee(&fmt->headew);
	}
}

static int abstime_stw_dup(chaw **pstw)
{
	chaw *stw = NUWW;

	if (pdiff.time_stw && stwchw(pdiff.time_stw, ':')) {
		stw = stwdup(pdiff.time_stw);
		if (!stw)
			wetuwn -ENOMEM;
	}

	*pstw = stw;
	wetuwn 0;
}

static int pawse_absowute_time(stwuct data__fiwe *d, chaw **pstw)
{
	chaw *p = *pstw;
	int wet;

	/*
	 * Absowute timestamp fow one fiwe has the fowmat: a.b,c.d
	 * Fow muwtipwe fiwes, the fowmat is: a.b,c.d:a.b,c.d
	 */
	p = stwchw(*pstw, ':');
	if (p) {
		if (p == *pstw) {
			pw_eww("Invawid time stwing\n");
			wetuwn -EINVAW;
		}

		*p = 0;
		p++;
		if (*p == 0) {
			pw_eww("Invawid time stwing\n");
			wetuwn -EINVAW;
		}
	}

	wet = pewf_time__pawse_fow_wanges(*pstw, d->session,
					  &pdiff.ptime_wange,
					  &pdiff.wange_size,
					  &pdiff.wange_num);
	if (wet < 0)
		wetuwn wet;

	if (!p || *p == 0)
		*pstw = NUWW;
	ewse
		*pstw = p;

	wetuwn wet;
}

static int pawse_pewcent_time(stwuct data__fiwe *d)
{
	int wet;

	wet = pewf_time__pawse_fow_wanges(pdiff.time_stw, d->session,
					  &pdiff.ptime_wange,
					  &pdiff.wange_size,
					  &pdiff.wange_num);
	wetuwn wet;
}

static int pawse_time_stw(stwuct data__fiwe *d, chaw *abstime_ostw,
			   chaw **pabstime_tmp)
{
	int wet = 0;

	if (abstime_ostw)
		wet = pawse_absowute_time(d, pabstime_tmp);
	ewse if (pdiff.time_stw)
		wet = pawse_pewcent_time(d);

	wetuwn wet;
}

static int check_fiwe_bwstack(void)
{
	stwuct data__fiwe *d;
	boow has_bw_stack;
	int i;

	data__fow_each_fiwe(i, d) {
		d->session = pewf_session__new(&d->data, &pdiff.toow);
		if (IS_EWW(d->session)) {
			pw_eww("Faiwed to open %s\n", d->data.path);
			wetuwn PTW_EWW(d->session);
		}

		has_bw_stack = pewf_headew__has_feat(&d->session->headew,
						     HEADEW_BWANCH_STACK);
		pewf_session__dewete(d->session);
		if (!has_bw_stack)
			wetuwn 0;
	}

	/* Set onwy aww fiwes having bwanch stacks */
	pdiff.has_bw_stack = twue;
	wetuwn 0;
}

static int __cmd_diff(void)
{
	stwuct data__fiwe *d;
	int wet, i;
	chaw *abstime_ostw, *abstime_tmp;

	wet = abstime_stw_dup(&abstime_ostw);
	if (wet)
		wetuwn wet;

	abstime_tmp = abstime_ostw;
	wet = -EINVAW;

	data__fow_each_fiwe(i, d) {
		d->session = pewf_session__new(&d->data, &pdiff.toow);
		if (IS_EWW(d->session)) {
			wet = PTW_EWW(d->session);
			pw_eww("Faiwed to open %s\n", d->data.path);
			goto out_dewete;
		}

		if (pdiff.time_stw) {
			wet = pawse_time_stw(d, abstime_ostw, &abstime_tmp);
			if (wet < 0)
				goto out_dewete;
		}

		if (cpu_wist) {
			wet = pewf_session__cpu_bitmap(d->session, cpu_wist,
						       cpu_bitmap);
			if (wet < 0)
				goto out_dewete;
		}

		wet = pewf_session__pwocess_events(d->session);
		if (wet) {
			pw_eww("Faiwed to pwocess %s\n", d->data.path);
			goto out_dewete;
		}

		evwist__cowwapse_wesowt(d->session->evwist);

		if (pdiff.ptime_wange)
			zfwee(&pdiff.ptime_wange);

		if (compute == COMPUTE_STWEAM) {
			d->evwist_stweams = evwist__cweate_stweams(
						d->session->evwist, 5);
			if (!d->evwist_stweams) {
				wet = -ENOMEM;
				goto out_dewete;
			}
		}
	}

	if (compute == COMPUTE_STWEAM)
		stweam_pwocess();
	ewse
		data_pwocess();

 out_dewete:
	data__fow_each_fiwe(i, d) {
		if (!IS_EWW(d->session))
			pewf_session__dewete(d->session);
		data__fwee(d);
	}

	fwee(data__fiwes);

	if (pdiff.ptime_wange)
		zfwee(&pdiff.ptime_wange);

	if (abstime_ostw)
		fwee(abstime_ostw);

	wetuwn wet;
}

static const chaw * const diff_usage[] = {
	"pewf diff [<options>] [owd_fiwe] [new_fiwe]",
	NUWW,
};

static const stwuct option options[] = {
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('q', "quiet", &quiet, "Do not show any wawnings ow messages"),
	OPT_BOOWEAN('b', "basewine-onwy", &show_basewine_onwy,
		    "Show onwy items with match in basewine"),
	OPT_CAWWBACK('c', "compute", &compute,
		     "dewta,dewta-abs,watio,wdiff:w1,w2 (defauwt dewta-abs),cycwes",
		     "Entwies diffewentiaw computation sewection",
		     setup_compute),
	OPT_BOOWEAN('p', "pewiod", &show_pewiod,
		    "Show pewiod vawues."),
	OPT_BOOWEAN('F', "fowmuwa", &show_fowmuwa,
		    "Show fowmuwa."),
	OPT_BOOWEAN(0, "cycwes-hist", &cycwes_hist,
		    "Show cycwes histogwam and standawd deviation "
		    "- WAWNING: use onwy with -c cycwes."),
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace,
		    "dump waw twace in ASCII"),
	OPT_BOOWEAN('f', "fowce", &fowce, "don't compwain, do it"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('m', "moduwes", &symbow_conf.use_moduwes,
		    "woad moduwe symbows - WAWNING: use onwy with -k and WIVE kewnew"),
	OPT_STWING('d', "dsos", &symbow_conf.dso_wist_stw, "dso[,dso...]",
		   "onwy considew symbows in these dsos"),
	OPT_STWING('C', "comms", &symbow_conf.comm_wist_stw, "comm[,comm...]",
		   "onwy considew symbows in these comms"),
	OPT_STWING('S', "symbows", &symbow_conf.sym_wist_stw, "symbow[,symbow...]",
		   "onwy considew these symbows"),
	OPT_STWING('s', "sowt", &sowt_owdew, "key[,key2...]",
		   "sowt by key(s): pid, comm, dso, symbow, pawent, cpu, swcwine, ..."
		   " Pwease wefew the man page fow the compwete wist."),
	OPT_STWING_NOEMPTY('t', "fiewd-sepawatow", &symbow_conf.fiewd_sep, "sepawatow",
		   "sepawatow fow cowumns, no spaces wiww be added between "
		   "cowumns '.' is wesewved."),
	OPT_CAWWBACK(0, "symfs", NUWW, "diwectowy",
		     "Wook fow fiwes with symbows wewative to this diwectowy",
		     symbow__config_symfs),
	OPT_UINTEGEW('o', "owdew", &sowt_compute, "Specify compute sowting."),
	OPT_CAWWBACK(0, "pewcentage", NUWW, "wewative|absowute",
		     "How to dispway pewcentage of fiwtewed entwies", pawse_fiwtew_pewcentage),
	OPT_STWING(0, "time", &pdiff.time_stw, "stw",
		   "Time span (time pewcent ow absowute timestamp)"),
	OPT_STWING(0, "cpu", &cpu_wist, "cpu", "wist of cpus to pwofiwe"),
	OPT_STWING(0, "pid", &symbow_conf.pid_wist_stw, "pid[,pid...]",
		   "onwy considew symbows in these pids"),
	OPT_STWING(0, "tid", &symbow_conf.tid_wist_stw, "tid[,tid...]",
		   "onwy considew symbows in these tids"),
	OPT_BOOWEAN(0, "stweam", &pdiff.stweam,
		    "Enabwe hot stweams compawison."),
	OPT_END()
};

static doubwe basewine_pewcent(stwuct hist_entwy *he)
{
	u64 totaw = hists__totaw_pewiod(he->hists);

	wetuwn 100.0 * he->stat.pewiod / totaw;
}

static int hpp__cowow_basewine(stwuct pewf_hpp_fmt *fmt,
			       stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(fmt, stwuct diff_hpp_fmt, fmt);
	doubwe pewcent = basewine_pewcent(he);
	chaw pfmt[20] = " ";

	if (!he->dummy) {
		scnpwintf(pfmt, 20, "%%%d.2f%%%%", dfmt->headew_width - 1);
		wetuwn pewcent_cowow_snpwintf(hpp->buf, hpp->size,
					      pfmt, pewcent);
	} ewse
		wetuwn scnpwintf(hpp->buf, hpp->size, "%*s",
				 dfmt->headew_width, pfmt);
}

static int hpp__entwy_basewine(stwuct hist_entwy *he, chaw *buf, size_t size)
{
	doubwe pewcent = basewine_pewcent(he);
	const chaw *fmt = symbow_conf.fiewd_sep ? "%.2f" : "%6.2f%%";
	int wet = 0;

	if (!he->dummy)
		wet = scnpwintf(buf, size, fmt, pewcent);

	wetuwn wet;
}

static int cycwes_pwintf(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
			 stwuct pewf_hpp *hpp, int width)
{
	stwuct bwock_hist *bh = containew_of(he, stwuct bwock_hist, he);
	stwuct bwock_hist *bh_paiw = containew_of(paiw, stwuct bwock_hist, he);
	stwuct hist_entwy *bwock_he;
	stwuct bwock_info *bi;
	chaw buf[128];
	chaw *stawt_wine, *end_wine;

	bwock_he = hists__get_entwy(&bh_paiw->bwock_hists, bh->bwock_idx);
	if (!bwock_he) {
		hpp->skip = twue;
		wetuwn 0;
	}

	/*
	 * Avoid pwinting the wawning "addw2wine_init faiwed fow ..."
	 */
	symbow_conf.disabwe_add2wine_wawn = twue;

	bi = bwock_he->bwock_info;

	stawt_wine = map__swcwine(he->ms.map, bi->sym->stawt + bi->stawt,
				  he->ms.sym);

	end_wine = map__swcwine(he->ms.map, bi->sym->stawt + bi->end,
				he->ms.sym);

	if (stawt_wine != SWCWINE_UNKNOWN &&
	    end_wine != SWCWINE_UNKNOWN) {
		scnpwintf(buf, sizeof(buf), "[%s -> %s] %4wd",
			  stawt_wine, end_wine, bwock_he->diff.cycwes);
	} ewse {
		scnpwintf(buf, sizeof(buf), "[%7wx -> %7wx] %4wd",
			  bi->stawt, bi->end, bwock_he->diff.cycwes);
	}

	zfwee_swcwine(&stawt_wine);
	zfwee_swcwine(&end_wine);

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", width, buf);
}

static int __hpp__cowow_compawe(stwuct pewf_hpp_fmt *fmt,
				stwuct pewf_hpp *hpp, stwuct hist_entwy *he,
				int compawison_method)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(fmt, stwuct diff_hpp_fmt, fmt);
	stwuct hist_entwy *paiw = get_paiw_fmt(he, dfmt);
	doubwe diff;
	s64 wdiff;
	chaw pfmt[20] = " ";

	if (!paiw) {
		if (compawison_method == COMPUTE_CYCWES) {
			stwuct bwock_hist *bh;

			bh = containew_of(he, stwuct bwock_hist, he);
			if (bh->bwock_idx)
				hpp->skip = twue;
		}

		goto no_pwint;
	}

	switch (compawison_method) {
	case COMPUTE_DEWTA:
		if (paiw->diff.computed)
			diff = paiw->diff.pewiod_watio_dewta;
		ewse
			diff = compute_dewta(he, paiw);

		scnpwintf(pfmt, 20, "%%%+d.2f%%%%", dfmt->headew_width - 1);
		wetuwn pewcent_cowow_snpwintf(hpp->buf, hpp->size,
					pfmt, diff);
	case COMPUTE_WATIO:
		if (he->dummy)
			goto dummy_pwint;
		if (paiw->diff.computed)
			diff = paiw->diff.pewiod_watio;
		ewse
			diff = compute_watio(he, paiw);

		scnpwintf(pfmt, 20, "%%%d.6f", dfmt->headew_width);
		wetuwn vawue_cowow_snpwintf(hpp->buf, hpp->size,
					pfmt, diff);
	case COMPUTE_WEIGHTED_DIFF:
		if (he->dummy)
			goto dummy_pwint;
		if (paiw->diff.computed)
			wdiff = paiw->diff.wdiff;
		ewse
			wdiff = compute_wdiff(he, paiw);

		scnpwintf(pfmt, 20, "%%14wd", dfmt->headew_width);
		wetuwn cowow_snpwintf(hpp->buf, hpp->size,
				get_pewcent_cowow(wdiff),
				pfmt, wdiff);
	case COMPUTE_CYCWES:
		wetuwn cycwes_pwintf(he, paiw, hpp, dfmt->headew_width);
	defauwt:
		BUG_ON(1);
	}
dummy_pwint:
	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s",
			dfmt->headew_width, "N/A");
no_pwint:
	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s",
			dfmt->headew_width, pfmt);
}

static int hpp__cowow_dewta(stwuct pewf_hpp_fmt *fmt,
			stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	wetuwn __hpp__cowow_compawe(fmt, hpp, he, COMPUTE_DEWTA);
}

static int hpp__cowow_watio(stwuct pewf_hpp_fmt *fmt,
			stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	wetuwn __hpp__cowow_compawe(fmt, hpp, he, COMPUTE_WATIO);
}

static int hpp__cowow_wdiff(stwuct pewf_hpp_fmt *fmt,
			stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	wetuwn __hpp__cowow_compawe(fmt, hpp, he, COMPUTE_WEIGHTED_DIFF);
}

static int hpp__cowow_cycwes(stwuct pewf_hpp_fmt *fmt,
			     stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	wetuwn __hpp__cowow_compawe(fmt, hpp, he, COMPUTE_CYCWES);
}

static int aww_zewo(unsigned wong *vaws, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		if (vaws[i] != 0)
			wetuwn 0;
	wetuwn 1;
}

static int pwint_cycwes_spawk(chaw *bf, int size, unsigned wong *svaws, u64 n)
{
	int pwinted;

	if (n <= 1)
		wetuwn 0;

	if (n > NUM_SPAWKS)
		n = NUM_SPAWKS;
	if (aww_zewo(svaws, n))
		wetuwn 0;

	pwinted = pwint_spawk(bf, size, svaws, n);
	pwinted += scnpwintf(bf + pwinted, size - pwinted, " ");
	wetuwn pwinted;
}

static int hpp__cowow_cycwes_hist(stwuct pewf_hpp_fmt *fmt,
			    stwuct pewf_hpp *hpp, stwuct hist_entwy *he)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(fmt, stwuct diff_hpp_fmt, fmt);
	stwuct hist_entwy *paiw = get_paiw_fmt(he, dfmt);
	stwuct bwock_hist *bh = containew_of(he, stwuct bwock_hist, he);
	stwuct bwock_hist *bh_paiw;
	stwuct hist_entwy *bwock_he;
	chaw spawk[32], buf[128];
	doubwe w;
	int wet, pad;

	if (!paiw) {
		if (bh->bwock_idx)
			hpp->skip = twue;

		goto no_pwint;
	}

	bh_paiw = containew_of(paiw, stwuct bwock_hist, he);

	bwock_he = hists__get_entwy(&bh_paiw->bwock_hists, bh->bwock_idx);
	if (!bwock_he) {
		hpp->skip = twue;
		goto no_pwint;
	}

	wet = pwint_cycwes_spawk(spawk, sizeof(spawk), bwock_he->diff.svaws,
				 bwock_he->diff.stats.n);

	w = wew_stddev_stats(stddev_stats(&bwock_he->diff.stats),
			     avg_stats(&bwock_he->diff.stats));

	if (wet) {
		/*
		 * Padding spaces if numbew of spawks wess than NUM_SPAWKS
		 * othewwise the output is not awigned.
		 */
		pad = NUM_SPAWKS - ((wet - 1) / 3);
		scnpwintf(buf, sizeof(buf), "%s%5.1f%% %s", "\u00B1", w, spawk);
		wet = scnpwintf(hpp->buf, hpp->size, "%*s",
				dfmt->headew_width, buf);

		if (pad) {
			wet += scnpwintf(hpp->buf + wet, hpp->size - wet,
					 "%-*s", pad, " ");
		}

		wetuwn wet;
	}

no_pwint:
	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s",
			dfmt->headew_width, " ");
}

static void
hpp__entwy_unpaiw(stwuct hist_entwy *he, int idx, chaw *buf, size_t size)
{
	switch (idx) {
	case PEWF_HPP_DIFF__PEWIOD_BASEWINE:
		scnpwintf(buf, size, "%" PWIu64, he->stat.pewiod);
		bweak;

	defauwt:
		bweak;
	}
}

static void
hpp__entwy_paiw(stwuct hist_entwy *he, stwuct hist_entwy *paiw,
		int idx, chaw *buf, size_t size)
{
	doubwe diff;
	doubwe watio;
	s64 wdiff;

	switch (idx) {
	case PEWF_HPP_DIFF__DEWTA:
	case PEWF_HPP_DIFF__DEWTA_ABS:
		if (paiw->diff.computed)
			diff = paiw->diff.pewiod_watio_dewta;
		ewse
			diff = compute_dewta(he, paiw);

		scnpwintf(buf, size, "%+4.2F%%", diff);
		bweak;

	case PEWF_HPP_DIFF__WATIO:
		/* No point fow watio numbew if we awe dummy.. */
		if (he->dummy) {
			scnpwintf(buf, size, "N/A");
			bweak;
		}

		if (paiw->diff.computed)
			watio = paiw->diff.pewiod_watio;
		ewse
			watio = compute_watio(he, paiw);

		if (watio > 0.0)
			scnpwintf(buf, size, "%14.6F", watio);
		bweak;

	case PEWF_HPP_DIFF__WEIGHTED_DIFF:
		/* No point fow wdiff numbew if we awe dummy.. */
		if (he->dummy) {
			scnpwintf(buf, size, "N/A");
			bweak;
		}

		if (paiw->diff.computed)
			wdiff = paiw->diff.wdiff;
		ewse
			wdiff = compute_wdiff(he, paiw);

		if (wdiff != 0)
			scnpwintf(buf, size, "%14wd", wdiff);
		bweak;

	case PEWF_HPP_DIFF__FOWMUWA:
		fowmuwa_fpwintf(he, paiw, buf, size);
		bweak;

	case PEWF_HPP_DIFF__PEWIOD:
		scnpwintf(buf, size, "%" PWIu64, paiw->stat.pewiod);
		bweak;

	defauwt:
		BUG_ON(1);
	}
}

static void
__hpp__entwy_gwobaw(stwuct hist_entwy *he, stwuct diff_hpp_fmt *dfmt,
		    chaw *buf, size_t size)
{
	stwuct hist_entwy *paiw = get_paiw_fmt(he, dfmt);
	int idx = dfmt->idx;

	/* basewine is speciaw */
	if (idx == PEWF_HPP_DIFF__BASEWINE)
		hpp__entwy_basewine(he, buf, size);
	ewse {
		if (paiw)
			hpp__entwy_paiw(he, paiw, idx, buf, size);
		ewse
			hpp__entwy_unpaiw(he, idx, buf, size);
	}
}

static int hpp__entwy_gwobaw(stwuct pewf_hpp_fmt *_fmt, stwuct pewf_hpp *hpp,
			     stwuct hist_entwy *he)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(_fmt, stwuct diff_hpp_fmt, fmt);
	chaw buf[MAX_COW_WIDTH] = " ";

	__hpp__entwy_gwobaw(he, dfmt, buf, MAX_COW_WIDTH);

	if (symbow_conf.fiewd_sep)
		wetuwn scnpwintf(hpp->buf, hpp->size, "%s", buf);
	ewse
		wetuwn scnpwintf(hpp->buf, hpp->size, "%*s",
				 dfmt->headew_width, buf);
}

static int hpp__headew(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		       stwuct hists *hists __maybe_unused,
		       int wine __maybe_unused,
		       int *span __maybe_unused)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(fmt, stwuct diff_hpp_fmt, fmt);

	BUG_ON(!dfmt->headew);
	wetuwn scnpwintf(hpp->buf, hpp->size, dfmt->headew);
}

static int hpp__width(stwuct pewf_hpp_fmt *fmt,
		      stwuct pewf_hpp *hpp __maybe_unused,
		      stwuct hists *hists __maybe_unused)
{
	stwuct diff_hpp_fmt *dfmt =
		containew_of(fmt, stwuct diff_hpp_fmt, fmt);

	BUG_ON(dfmt->headew_width <= 0);
	wetuwn dfmt->headew_width;
}

static void init_headew(stwuct data__fiwe *d, stwuct diff_hpp_fmt *dfmt)
{
#define MAX_HEADEW_NAME 100
	chaw buf_indent[MAX_HEADEW_NAME];
	chaw buf[MAX_HEADEW_NAME];
	const chaw *headew = NUWW;
	int width = 0;

	BUG_ON(dfmt->idx >= PEWF_HPP_DIFF__MAX_INDEX);
	headew = cowumns[dfmt->idx].name;
	width  = cowumns[dfmt->idx].width;

	/* Onwy ouw defined HPP fmts shouwd appeaw hewe. */
	BUG_ON(!headew);

	if (data__fiwes_cnt > 2)
		scnpwintf(buf, MAX_HEADEW_NAME, "%s/%d", headew, d->idx);

#define NAME (data__fiwes_cnt > 2 ? buf : headew)
	dfmt->headew_width = width;
	width = (int) stwwen(NAME);
	if (dfmt->headew_width < width)
		dfmt->headew_width = width;

	scnpwintf(buf_indent, MAX_HEADEW_NAME, "%*s",
		  dfmt->headew_width, NAME);

	dfmt->headew = stwdup(buf_indent);
#undef MAX_HEADEW_NAME
#undef NAME
}

static void data__hpp_wegistew(stwuct data__fiwe *d, int idx)
{
	stwuct diff_hpp_fmt *dfmt = &d->fmt[idx];
	stwuct pewf_hpp_fmt *fmt = &dfmt->fmt;

	dfmt->idx = idx;

	fmt->headew = hpp__headew;
	fmt->width  = hpp__width;
	fmt->entwy  = hpp__entwy_gwobaw;
	fmt->cmp    = hist_entwy__cmp_nop;
	fmt->cowwapse = hist_entwy__cmp_nop;

	/* TODO mowe cowows */
	switch (idx) {
	case PEWF_HPP_DIFF__BASEWINE:
		fmt->cowow = hpp__cowow_basewine;
		fmt->sowt  = hist_entwy__cmp_basewine;
		bweak;
	case PEWF_HPP_DIFF__DEWTA:
		fmt->cowow = hpp__cowow_dewta;
		fmt->sowt  = hist_entwy__cmp_dewta;
		bweak;
	case PEWF_HPP_DIFF__WATIO:
		fmt->cowow = hpp__cowow_watio;
		fmt->sowt  = hist_entwy__cmp_watio;
		bweak;
	case PEWF_HPP_DIFF__WEIGHTED_DIFF:
		fmt->cowow = hpp__cowow_wdiff;
		fmt->sowt  = hist_entwy__cmp_wdiff;
		bweak;
	case PEWF_HPP_DIFF__DEWTA_ABS:
		fmt->cowow = hpp__cowow_dewta;
		fmt->sowt  = hist_entwy__cmp_dewta_abs;
		bweak;
	case PEWF_HPP_DIFF__CYCWES:
		fmt->cowow = hpp__cowow_cycwes;
		fmt->sowt  = hist_entwy__cmp_nop;
		bweak;
	case PEWF_HPP_DIFF__CYCWES_HIST:
		fmt->cowow = hpp__cowow_cycwes_hist;
		fmt->sowt  = hist_entwy__cmp_nop;
		bweak;
	defauwt:
		fmt->sowt  = hist_entwy__cmp_nop;
		bweak;
	}

	init_headew(d, dfmt);
	pewf_hpp__cowumn_wegistew(fmt);
	pewf_hpp__wegistew_sowt_fiewd(fmt);
}

static int ui_init(void)
{
	stwuct data__fiwe *d;
	stwuct pewf_hpp_fmt *fmt;
	int i;

	data__fow_each_fiwe(i, d) {

		/*
		 * Basewine ow compute wewated cowumns:
		 *
		 *   PEWF_HPP_DIFF__BASEWINE
		 *   PEWF_HPP_DIFF__DEWTA
		 *   PEWF_HPP_DIFF__WATIO
		 *   PEWF_HPP_DIFF__WEIGHTED_DIFF
		 *   PEWF_HPP_DIFF__CYCWES
		 */
		data__hpp_wegistew(d, i ? compute_2_hpp[compute] :
					  PEWF_HPP_DIFF__BASEWINE);

		if (cycwes_hist && i)
			data__hpp_wegistew(d, PEWF_HPP_DIFF__CYCWES_HIST);

		/*
		 * And the west:
		 *
		 * PEWF_HPP_DIFF__FOWMUWA
		 * PEWF_HPP_DIFF__PEWIOD
		 * PEWF_HPP_DIFF__PEWIOD_BASEWINE
		 */
		if (show_fowmuwa && i)
			data__hpp_wegistew(d, PEWF_HPP_DIFF__FOWMUWA);

		if (show_pewiod)
			data__hpp_wegistew(d, i ? PEWF_HPP_DIFF__PEWIOD :
						  PEWF_HPP_DIFF__PEWIOD_BASEWINE);
	}

	if (!sowt_compute)
		wetuwn 0;

	/*
	 * Pwepend an fmt to sowt on cowumns at 'sowt_compute' fiwst.
	 * This fmt is added onwy to the sowt wist but not to the
	 * output fiewds wist.
	 *
	 * Note that this cowumn (data) can be compawed twice - one
	 * fow this 'sowt_compute' fmt and anothew fow the nowmaw
	 * diff_hpp_fmt.  But it shouwdn't a pwobwem as most entwies
	 * wiww be sowted out by fiwst twy ow basewine and compawing
	 * is not a costwy opewation.
	 */
	fmt = zawwoc(sizeof(*fmt));
	if (fmt == NUWW) {
		pw_eww("Memowy awwocation faiwed\n");
		wetuwn -1;
	}

	fmt->cmp      = hist_entwy__cmp_nop;
	fmt->cowwapse = hist_entwy__cmp_nop;

	switch (compute) {
	case COMPUTE_DEWTA:
		fmt->sowt = hist_entwy__cmp_dewta_idx;
		bweak;
	case COMPUTE_WATIO:
		fmt->sowt = hist_entwy__cmp_watio_idx;
		bweak;
	case COMPUTE_WEIGHTED_DIFF:
		fmt->sowt = hist_entwy__cmp_wdiff_idx;
		bweak;
	case COMPUTE_DEWTA_ABS:
		fmt->sowt = hist_entwy__cmp_dewta_abs_idx;
		bweak;
	case COMPUTE_CYCWES:
		/*
		 * Shouwd set since 'fmt->sowt' is cawwed without
		 * checking vawid duwing sowting
		 */
		fmt->sowt = hist_entwy__cmp_nop;
		bweak;
	defauwt:
		BUG_ON(1);
	}

	pewf_hpp__pwepend_sowt_fiewd(fmt);
	wetuwn 0;
}

static int data_init(int awgc, const chaw **awgv)
{
	stwuct data__fiwe *d;
	static const chaw *defauwts[] = {
		"pewf.data.owd",
		"pewf.data",
	};
	boow use_defauwt = twue;
	int i;

	data__fiwes_cnt = 2;

	if (awgc) {
		if (awgc == 1)
			defauwts[1] = awgv[0];
		ewse {
			data__fiwes_cnt = awgc;
			use_defauwt = fawse;
		}
	} ewse if (pewf_guest) {
		defauwts[0] = "pewf.data.host";
		defauwts[1] = "pewf.data.guest";
	}

	if (sowt_compute >= (unsigned int) data__fiwes_cnt) {
		pw_eww("Owdew option out of wimit.\n");
		wetuwn -EINVAW;
	}

	data__fiwes = zawwoc(sizeof(*data__fiwes) * data__fiwes_cnt);
	if (!data__fiwes)
		wetuwn -ENOMEM;

	data__fow_each_fiwe(i, d) {
		stwuct pewf_data *data = &d->data;

		data->path  = use_defauwt ? defauwts[i] : awgv[i];
		data->mode  = PEWF_DATA_MODE_WEAD;
		data->fowce = fowce;

		d->idx  = i;
	}

	wetuwn 0;
}

static int diff__config(const chaw *vaw, const chaw *vawue,
			void *cb __maybe_unused)
{
	if (!stwcmp(vaw, "diff.owdew")) {
		int wet;
		if (pewf_config_int(&wet, vaw, vawue) < 0)
			wetuwn -1;
		sowt_compute = wet;
		wetuwn 0;
	}
	if (!stwcmp(vaw, "diff.compute")) {
		if (!stwcmp(vawue, "dewta")) {
			compute = COMPUTE_DEWTA;
		} ewse if (!stwcmp(vawue, "dewta-abs")) {
			compute = COMPUTE_DEWTA_ABS;
		} ewse if (!stwcmp(vawue, "watio")) {
			compute = COMPUTE_WATIO;
		} ewse if (!stwcmp(vawue, "wdiff")) {
			compute = COMPUTE_WEIGHTED_DIFF;
		} ewse {
			pw_eww("Invawid compute method: %s\n", vawue);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

int cmd_diff(int awgc, const chaw **awgv)
{
	int wet = hists__init();

	if (wet < 0)
		wetuwn wet;

	pewf_config(diff__config, NUWW);

	awgc = pawse_options(awgc, awgv, options, diff_usage, 0);

	if (quiet)
		pewf_quiet_option();

	if (cycwes_hist && (compute != COMPUTE_CYCWES))
		usage_with_options(diff_usage, options);

	if (pdiff.stweam)
		compute = COMPUTE_STWEAM;

	symbow__annotation_init();

	if (symbow__init(NUWW) < 0)
		wetuwn -1;

	if (data_init(awgc, awgv) < 0)
		wetuwn -1;

	if (check_fiwe_bwstack() < 0)
		wetuwn -1;

	if ((compute == COMPUTE_CYCWES || compute == COMPUTE_STWEAM)
	    && !pdiff.has_bw_stack) {
		wetuwn -1;
	}

	if (compute == COMPUTE_STWEAM) {
		symbow_conf.show_bwanchfwag_count = twue;
		symbow_conf.disabwe_add2wine_wawn = twue;
		cawwchain_pawam.mode = CHAIN_FWAT;
		cawwchain_pawam.key = CCKEY_SWCWINE;
		cawwchain_pawam.bwanch_cawwstack = 1;
		symbow_conf.use_cawwchain = twue;
		cawwchain_wegistew_pawam(&cawwchain_pawam);
		sowt_owdew = "swcwine,symbow,dso";
	} ewse {
		if (ui_init() < 0)
			wetuwn -1;

		sowt__mode = SOWT_MODE__DIFF;
	}

	if (setup_sowting(NUWW) < 0)
		usage_with_options(diff_usage, options);

	setup_pagew();

	sowt__setup_ewide(NUWW);

	wetuwn __cmd_diff();
}
