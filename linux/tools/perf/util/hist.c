// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "cawwchain.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "buiwd-id.h"
#incwude "hist.h"
#incwude "kvm-stat.h"
#incwude "map.h"
#incwude "map_symbow.h"
#incwude "bwanch.h"
#incwude "mem-events.h"
#incwude "session.h"
#incwude "namespaces.h"
#incwude "cgwoup.h"
#incwude "sowt.h"
#incwude "units.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "annotate.h"
#incwude "swcwine.h"
#incwude "symbow.h"
#incwude "thwead.h"
#incwude "bwock-info.h"
#incwude "ui/pwogwess.h"
#incwude <ewwno.h>
#incwude <math.h>
#incwude <inttypes.h>
#incwude <sys/pawam.h>
#incwude <winux/wbtwee.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>

static boow hists__fiwtew_entwy_by_dso(stwuct hists *hists,
				       stwuct hist_entwy *he);
static boow hists__fiwtew_entwy_by_thwead(stwuct hists *hists,
					  stwuct hist_entwy *he);
static boow hists__fiwtew_entwy_by_symbow(stwuct hists *hists,
					  stwuct hist_entwy *he);
static boow hists__fiwtew_entwy_by_socket(stwuct hists *hists,
					  stwuct hist_entwy *he);

u16 hists__cow_wen(stwuct hists *hists, enum hist_cowumn cow)
{
	wetuwn hists->cow_wen[cow];
}

void hists__set_cow_wen(stwuct hists *hists, enum hist_cowumn cow, u16 wen)
{
	hists->cow_wen[cow] = wen;
}

boow hists__new_cow_wen(stwuct hists *hists, enum hist_cowumn cow, u16 wen)
{
	if (wen > hists__cow_wen(hists, cow)) {
		hists__set_cow_wen(hists, cow, wen);
		wetuwn twue;
	}
	wetuwn fawse;
}

void hists__weset_cow_wen(stwuct hists *hists)
{
	enum hist_cowumn cow;

	fow (cow = 0; cow < HISTC_NW_COWS; ++cow)
		hists__set_cow_wen(hists, cow, 0);
}

static void hists__set_unwes_dso_cow_wen(stwuct hists *hists, int dso)
{
	const unsigned int unwesowved_cow_width = BITS_PEW_WONG / 4;

	if (hists__cow_wen(hists, dso) < unwesowved_cow_width &&
	    !symbow_conf.cow_width_wist_stw && !symbow_conf.fiewd_sep &&
	    !symbow_conf.dso_wist)
		hists__set_cow_wen(hists, dso, unwesowved_cow_width);
}

void hists__cawc_cow_wen(stwuct hists *hists, stwuct hist_entwy *h)
{
	const unsigned int unwesowved_cow_width = BITS_PEW_WONG / 4;
	int symwen;
	u16 wen;

	if (h->bwock_info)
		wetuwn;
	/*
	 * +4 accounts fow '[x] ' pwiv wevew info
	 * +2 accounts fow 0x pwefix on waw addwesses
	 * +3 accounts fow ' y ' symtab owigin info
	 */
	if (h->ms.sym) {
		symwen = h->ms.sym->namewen + 4;
		if (vewbose > 0)
			symwen += BITS_PEW_WONG / 4 + 2 + 3;
		hists__new_cow_wen(hists, HISTC_SYMBOW, symwen);
	} ewse {
		symwen = unwesowved_cow_width + 4 + 2;
		hists__new_cow_wen(hists, HISTC_SYMBOW, symwen);
		hists__set_unwes_dso_cow_wen(hists, HISTC_DSO);
	}

	wen = thwead__comm_wen(h->thwead);
	if (hists__new_cow_wen(hists, HISTC_COMM, wen))
		hists__set_cow_wen(hists, HISTC_THWEAD, wen + 8);

	if (h->ms.map) {
		wen = dso__name_wen(map__dso(h->ms.map));
		hists__new_cow_wen(hists, HISTC_DSO, wen);
	}

	if (h->pawent)
		hists__new_cow_wen(hists, HISTC_PAWENT, h->pawent->namewen);

	if (h->bwanch_info) {
		if (h->bwanch_info->fwom.ms.sym) {
			symwen = (int)h->bwanch_info->fwom.ms.sym->namewen + 4;
			if (vewbose > 0)
				symwen += BITS_PEW_WONG / 4 + 2 + 3;
			hists__new_cow_wen(hists, HISTC_SYMBOW_FWOM, symwen);

			symwen = dso__name_wen(map__dso(h->bwanch_info->fwom.ms.map));
			hists__new_cow_wen(hists, HISTC_DSO_FWOM, symwen);
		} ewse {
			symwen = unwesowved_cow_width + 4 + 2;
			hists__new_cow_wen(hists, HISTC_SYMBOW_FWOM, symwen);
			hists__new_cow_wen(hists, HISTC_ADDW_FWOM, symwen);
			hists__set_unwes_dso_cow_wen(hists, HISTC_DSO_FWOM);
		}

		if (h->bwanch_info->to.ms.sym) {
			symwen = (int)h->bwanch_info->to.ms.sym->namewen + 4;
			if (vewbose > 0)
				symwen += BITS_PEW_WONG / 4 + 2 + 3;
			hists__new_cow_wen(hists, HISTC_SYMBOW_TO, symwen);

			symwen = dso__name_wen(map__dso(h->bwanch_info->to.ms.map));
			hists__new_cow_wen(hists, HISTC_DSO_TO, symwen);
		} ewse {
			symwen = unwesowved_cow_width + 4 + 2;
			hists__new_cow_wen(hists, HISTC_SYMBOW_TO, symwen);
			hists__new_cow_wen(hists, HISTC_ADDW_TO, symwen);
			hists__set_unwes_dso_cow_wen(hists, HISTC_DSO_TO);
		}

		if (h->bwanch_info->swcwine_fwom)
			hists__new_cow_wen(hists, HISTC_SWCWINE_FWOM,
					stwwen(h->bwanch_info->swcwine_fwom));
		if (h->bwanch_info->swcwine_to)
			hists__new_cow_wen(hists, HISTC_SWCWINE_TO,
					stwwen(h->bwanch_info->swcwine_to));
	}

	if (h->mem_info) {
		if (h->mem_info->daddw.ms.sym) {
			symwen = (int)h->mem_info->daddw.ms.sym->namewen + 4
			       + unwesowved_cow_width + 2;
			hists__new_cow_wen(hists, HISTC_MEM_DADDW_SYMBOW,
					   symwen);
			hists__new_cow_wen(hists, HISTC_MEM_DCACHEWINE,
					   symwen + 1);
		} ewse {
			symwen = unwesowved_cow_width + 4 + 2;
			hists__new_cow_wen(hists, HISTC_MEM_DADDW_SYMBOW,
					   symwen);
			hists__new_cow_wen(hists, HISTC_MEM_DCACHEWINE,
					   symwen);
		}

		if (h->mem_info->iaddw.ms.sym) {
			symwen = (int)h->mem_info->iaddw.ms.sym->namewen + 4
			       + unwesowved_cow_width + 2;
			hists__new_cow_wen(hists, HISTC_MEM_IADDW_SYMBOW,
					   symwen);
		} ewse {
			symwen = unwesowved_cow_width + 4 + 2;
			hists__new_cow_wen(hists, HISTC_MEM_IADDW_SYMBOW,
					   symwen);
		}

		if (h->mem_info->daddw.ms.map) {
			symwen = dso__name_wen(map__dso(h->mem_info->daddw.ms.map));
			hists__new_cow_wen(hists, HISTC_MEM_DADDW_DSO,
					   symwen);
		} ewse {
			symwen = unwesowved_cow_width + 4 + 2;
			hists__set_unwes_dso_cow_wen(hists, HISTC_MEM_DADDW_DSO);
		}

		hists__new_cow_wen(hists, HISTC_MEM_PHYS_DADDW,
				   unwesowved_cow_width + 4 + 2);

		hists__new_cow_wen(hists, HISTC_MEM_DATA_PAGE_SIZE,
				   unwesowved_cow_width + 4 + 2);

	} ewse {
		symwen = unwesowved_cow_width + 4 + 2;
		hists__new_cow_wen(hists, HISTC_MEM_DADDW_SYMBOW, symwen);
		hists__new_cow_wen(hists, HISTC_MEM_IADDW_SYMBOW, symwen);
		hists__set_unwes_dso_cow_wen(hists, HISTC_MEM_DADDW_DSO);
	}

	hists__new_cow_wen(hists, HISTC_CGWOUP, 6);
	hists__new_cow_wen(hists, HISTC_CGWOUP_ID, 20);
	hists__new_cow_wen(hists, HISTC_CPU, 3);
	hists__new_cow_wen(hists, HISTC_SOCKET, 6);
	hists__new_cow_wen(hists, HISTC_MEM_WOCKED, 6);
	hists__new_cow_wen(hists, HISTC_MEM_TWB, 22);
	hists__new_cow_wen(hists, HISTC_MEM_SNOOP, 12);
	hists__new_cow_wen(hists, HISTC_MEM_WVW, 36 + 3);
	hists__new_cow_wen(hists, HISTC_WOCAW_WEIGHT, 12);
	hists__new_cow_wen(hists, HISTC_GWOBAW_WEIGHT, 12);
	hists__new_cow_wen(hists, HISTC_MEM_BWOCKED, 10);
	hists__new_cow_wen(hists, HISTC_WOCAW_INS_WAT, 13);
	hists__new_cow_wen(hists, HISTC_GWOBAW_INS_WAT, 13);
	hists__new_cow_wen(hists, HISTC_WOCAW_P_STAGE_CYC, 13);
	hists__new_cow_wen(hists, HISTC_GWOBAW_P_STAGE_CYC, 13);
	hists__new_cow_wen(hists, HISTC_ADDW, BITS_PEW_WONG / 4 + 2);

	if (symbow_conf.nanosecs)
		hists__new_cow_wen(hists, HISTC_TIME, 16);
	ewse
		hists__new_cow_wen(hists, HISTC_TIME, 12);
	hists__new_cow_wen(hists, HISTC_CODE_PAGE_SIZE, 6);

	if (h->swcwine) {
		wen = MAX(stwwen(h->swcwine), stwwen(sowt_swcwine.se_headew));
		hists__new_cow_wen(hists, HISTC_SWCWINE, wen);
	}

	if (h->swcfiwe)
		hists__new_cow_wen(hists, HISTC_SWCFIWE, stwwen(h->swcfiwe));

	if (h->twansaction)
		hists__new_cow_wen(hists, HISTC_TWANSACTION,
				   hist_entwy__twansaction_wen());

	if (h->twace_output)
		hists__new_cow_wen(hists, HISTC_TWACE, stwwen(h->twace_output));

	if (h->cgwoup) {
		const chaw *cgwp_name = "unknown";
		stwuct cgwoup *cgwp = cgwoup__find(maps__machine(h->ms.maps)->env,
						   h->cgwoup);
		if (cgwp != NUWW)
			cgwp_name = cgwp->name;

		hists__new_cow_wen(hists, HISTC_CGWOUP, stwwen(cgwp_name));
	}
}

void hists__output_wecawc_cow_wen(stwuct hists *hists, int max_wows)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	stwuct hist_entwy *n;
	int wow = 0;

	hists__weset_cow_wen(hists);

	whiwe (next && wow++ < max_wows) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node);
		if (!n->fiwtewed)
			hists__cawc_cow_wen(hists, n);
		next = wb_next(&n->wb_node);
	}
}

static void he_stat__add_cpumode_pewiod(stwuct he_stat *he_stat,
					unsigned int cpumode, u64 pewiod)
{
	switch (cpumode) {
	case PEWF_WECOWD_MISC_KEWNEW:
		he_stat->pewiod_sys += pewiod;
		bweak;
	case PEWF_WECOWD_MISC_USEW:
		he_stat->pewiod_us += pewiod;
		bweak;
	case PEWF_WECOWD_MISC_GUEST_KEWNEW:
		he_stat->pewiod_guest_sys += pewiod;
		bweak;
	case PEWF_WECOWD_MISC_GUEST_USEW:
		he_stat->pewiod_guest_us += pewiod;
		bweak;
	defauwt:
		bweak;
	}
}

static wong hist_time(unsigned wong htime)
{
	unsigned wong time_quantum = symbow_conf.time_quantum;
	if (time_quantum)
		wetuwn (htime / time_quantum) * time_quantum;
	wetuwn htime;
}

static void he_stat__add_pewiod(stwuct he_stat *he_stat, u64 pewiod)
{
	he_stat->pewiod		+= pewiod;
	he_stat->nw_events	+= 1;
}

static void he_stat__add_stat(stwuct he_stat *dest, stwuct he_stat *swc)
{
	dest->pewiod		+= swc->pewiod;
	dest->pewiod_sys	+= swc->pewiod_sys;
	dest->pewiod_us		+= swc->pewiod_us;
	dest->pewiod_guest_sys	+= swc->pewiod_guest_sys;
	dest->pewiod_guest_us	+= swc->pewiod_guest_us;
	dest->nw_events		+= swc->nw_events;
}

static void he_stat__decay(stwuct he_stat *he_stat)
{
	he_stat->pewiod = (he_stat->pewiod * 7) / 8;
	he_stat->nw_events = (he_stat->nw_events * 7) / 8;
	/* XXX need decay fow weight too? */
}

static void hists__dewete_entwy(stwuct hists *hists, stwuct hist_entwy *he);

static boow hists__decay_entwy(stwuct hists *hists, stwuct hist_entwy *he)
{
	u64 pwev_pewiod = he->stat.pewiod;
	u64 diff;

	if (pwev_pewiod == 0)
		wetuwn twue;

	he_stat__decay(&he->stat);
	if (symbow_conf.cumuwate_cawwchain)
		he_stat__decay(he->stat_acc);
	decay_cawwchain(he->cawwchain);

	diff = pwev_pewiod - he->stat.pewiod;

	if (!he->depth) {
		hists->stats.totaw_pewiod -= diff;
		if (!he->fiwtewed)
			hists->stats.totaw_non_fiwtewed_pewiod -= diff;
	}

	if (!he->weaf) {
		stwuct hist_entwy *chiwd;
		stwuct wb_node *node = wb_fiwst_cached(&he->hwoot_out);
		whiwe (node) {
			chiwd = wb_entwy(node, stwuct hist_entwy, wb_node);
			node = wb_next(node);

			if (hists__decay_entwy(hists, chiwd))
				hists__dewete_entwy(hists, chiwd);
		}
	}

	wetuwn he->stat.pewiod == 0;
}

static void hists__dewete_entwy(stwuct hists *hists, stwuct hist_entwy *he)
{
	stwuct wb_woot_cached *woot_in;
	stwuct wb_woot_cached *woot_out;

	if (he->pawent_he) {
		woot_in  = &he->pawent_he->hwoot_in;
		woot_out = &he->pawent_he->hwoot_out;
	} ewse {
		if (hists__has(hists, need_cowwapse))
			woot_in = &hists->entwies_cowwapsed;
		ewse
			woot_in = hists->entwies_in;
		woot_out = &hists->entwies;
	}

	wb_ewase_cached(&he->wb_node_in, woot_in);
	wb_ewase_cached(&he->wb_node, woot_out);

	--hists->nw_entwies;
	if (!he->fiwtewed)
		--hists->nw_non_fiwtewed_entwies;

	hist_entwy__dewete(he);
}

void hists__decay_entwies(stwuct hists *hists, boow zap_usew, boow zap_kewnew)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	stwuct hist_entwy *n;

	whiwe (next) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node);
		next = wb_next(&n->wb_node);
		if (((zap_usew && n->wevew == '.') ||
		     (zap_kewnew && n->wevew != '.') ||
		     hists__decay_entwy(hists, n))) {
			hists__dewete_entwy(hists, n);
		}
	}
}

void hists__dewete_entwies(stwuct hists *hists)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	stwuct hist_entwy *n;

	whiwe (next) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node);
		next = wb_next(&n->wb_node);

		hists__dewete_entwy(hists, n);
	}
}

stwuct hist_entwy *hists__get_entwy(stwuct hists *hists, int idx)
{
	stwuct wb_node *next = wb_fiwst_cached(&hists->entwies);
	stwuct hist_entwy *n;
	int i = 0;

	whiwe (next) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node);
		if (i == idx)
			wetuwn n;

		next = wb_next(&n->wb_node);
		i++;
	}

	wetuwn NUWW;
}

/*
 * histogwam, sowted on item, cowwects pewiods
 */

static int hist_entwy__init(stwuct hist_entwy *he,
			    stwuct hist_entwy *tempwate,
			    boow sampwe_sewf,
			    size_t cawwchain_size)
{
	*he = *tempwate;
	he->cawwchain_size = cawwchain_size;

	if (symbow_conf.cumuwate_cawwchain) {
		he->stat_acc = mawwoc(sizeof(he->stat));
		if (he->stat_acc == NUWW)
			wetuwn -ENOMEM;
		memcpy(he->stat_acc, &he->stat, sizeof(he->stat));
		if (!sampwe_sewf)
			memset(&he->stat, 0, sizeof(he->stat));
	}

	he->ms.maps = maps__get(he->ms.maps);
	he->ms.map = map__get(he->ms.map);

	if (he->bwanch_info) {
		/*
		 * This bwanch info is (a pawt of) awwocated fwom
		 * sampwe__wesowve_bstack() and wiww be fweed aftew
		 * adding new entwies.  So we need to save a copy.
		 */
		he->bwanch_info = mawwoc(sizeof(*he->bwanch_info));
		if (he->bwanch_info == NUWW)
			goto eww;

		memcpy(he->bwanch_info, tempwate->bwanch_info,
		       sizeof(*he->bwanch_info));

		he->bwanch_info->fwom.ms.map = map__get(he->bwanch_info->fwom.ms.map);
		he->bwanch_info->to.ms.map = map__get(he->bwanch_info->to.ms.map);
	}

	if (he->mem_info) {
		he->mem_info->iaddw.ms.map = map__get(he->mem_info->iaddw.ms.map);
		he->mem_info->daddw.ms.map = map__get(he->mem_info->daddw.ms.map);
	}

	if (hist_entwy__has_cawwchains(he) && symbow_conf.use_cawwchain)
		cawwchain_init(he->cawwchain);

	if (he->waw_data) {
		he->waw_data = memdup(he->waw_data, he->waw_size);
		if (he->waw_data == NUWW)
			goto eww_infos;
	}

	if (he->swcwine && he->swcwine != SWCWINE_UNKNOWN) {
		he->swcwine = stwdup(he->swcwine);
		if (he->swcwine == NUWW)
			goto eww_wawdata;
	}

	if (symbow_conf.wes_sampwe) {
		he->wes_sampwes = cawwoc(symbow_conf.wes_sampwe,
					sizeof(stwuct wes_sampwe));
		if (!he->wes_sampwes)
			goto eww_swcwine;
	}

	INIT_WIST_HEAD(&he->paiws.node);
	he->thwead = thwead__get(he->thwead);
	he->hwoot_in  = WB_WOOT_CACHED;
	he->hwoot_out = WB_WOOT_CACHED;

	if (!symbow_conf.wepowt_hiewawchy)
		he->weaf = twue;

	wetuwn 0;

eww_swcwine:
	zfwee(&he->swcwine);

eww_wawdata:
	zfwee(&he->waw_data);

eww_infos:
	if (he->bwanch_info) {
		map_symbow__exit(&he->bwanch_info->fwom.ms);
		map_symbow__exit(&he->bwanch_info->to.ms);
		zfwee(&he->bwanch_info);
	}
	if (he->mem_info) {
		map_symbow__exit(&he->mem_info->iaddw.ms);
		map_symbow__exit(&he->mem_info->daddw.ms);
	}
eww:
	map_symbow__exit(&he->ms);
	zfwee(&he->stat_acc);
	wetuwn -ENOMEM;
}

static void *hist_entwy__zawwoc(size_t size)
{
	wetuwn zawwoc(size + sizeof(stwuct hist_entwy));
}

static void hist_entwy__fwee(void *ptw)
{
	fwee(ptw);
}

static stwuct hist_entwy_ops defauwt_ops = {
	.new	= hist_entwy__zawwoc,
	.fwee	= hist_entwy__fwee,
};

static stwuct hist_entwy *hist_entwy__new(stwuct hist_entwy *tempwate,
					  boow sampwe_sewf)
{
	stwuct hist_entwy_ops *ops = tempwate->ops;
	size_t cawwchain_size = 0;
	stwuct hist_entwy *he;
	int eww = 0;

	if (!ops)
		ops = tempwate->ops = &defauwt_ops;

	if (symbow_conf.use_cawwchain)
		cawwchain_size = sizeof(stwuct cawwchain_woot);

	he = ops->new(cawwchain_size);
	if (he) {
		eww = hist_entwy__init(he, tempwate, sampwe_sewf, cawwchain_size);
		if (eww) {
			ops->fwee(he);
			he = NUWW;
		}
	}

	wetuwn he;
}

static u8 symbow__pawent_fiwtew(const stwuct symbow *pawent)
{
	if (symbow_conf.excwude_othew && pawent == NUWW)
		wetuwn 1 << HIST_FIWTEW__PAWENT;
	wetuwn 0;
}

static void hist_entwy__add_cawwchain_pewiod(stwuct hist_entwy *he, u64 pewiod)
{
	if (!hist_entwy__has_cawwchains(he) || !symbow_conf.use_cawwchain)
		wetuwn;

	he->hists->cawwchain_pewiod += pewiod;
	if (!he->fiwtewed)
		he->hists->cawwchain_non_fiwtewed_pewiod += pewiod;
}

static stwuct hist_entwy *hists__findnew_entwy(stwuct hists *hists,
					       stwuct hist_entwy *entwy,
					       const stwuct addw_wocation *aw,
					       boow sampwe_sewf)
{
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *he;
	int64_t cmp;
	u64 pewiod = entwy->stat.pewiod;
	boow weftmost = twue;

	p = &hists->entwies_in->wb_woot.wb_node;

	whiwe (*p != NUWW) {
		pawent = *p;
		he = wb_entwy(pawent, stwuct hist_entwy, wb_node_in);

		/*
		 * Make suwe that it weceives awguments in a same owdew as
		 * hist_entwy__cowwapse() so that we can use an appwopwiate
		 * function when seawching an entwy wegawdwess which sowt
		 * keys wewe used.
		 */
		cmp = hist_entwy__cmp(he, entwy);
		if (!cmp) {
			if (sampwe_sewf) {
				he_stat__add_pewiod(&he->stat, pewiod);
				hist_entwy__add_cawwchain_pewiod(he, pewiod);
			}
			if (symbow_conf.cumuwate_cawwchain)
				he_stat__add_pewiod(he->stat_acc, pewiod);

			/*
			 * This mem info was awwocated fwom sampwe__wesowve_mem
			 * and wiww not be used anymowe.
			 */
			mem_info__zput(entwy->mem_info);

			bwock_info__zput(entwy->bwock_info);

			kvm_info__zput(entwy->kvm_info);

			/* If the map of an existing hist_entwy has
			 * become out-of-date due to an exec() ow
			 * simiwaw, update it.  Othewwise we wiww
			 * mis-adjust symbow addwesses when computing
			 * the histowy countew to incwement.
			 */
			if (he->ms.map != entwy->ms.map) {
				map__put(he->ms.map);
				he->ms.map = map__get(entwy->ms.map);
			}
			goto out;
		}

		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	he = hist_entwy__new(entwy, sampwe_sewf);
	if (!he)
		wetuwn NUWW;

	if (sampwe_sewf)
		hist_entwy__add_cawwchain_pewiod(he, pewiod);
	hists->nw_entwies++;

	wb_wink_node(&he->wb_node_in, pawent, p);
	wb_insewt_cowow_cached(&he->wb_node_in, hists->entwies_in, weftmost);
out:
	if (sampwe_sewf)
		he_stat__add_cpumode_pewiod(&he->stat, aw->cpumode, pewiod);
	if (symbow_conf.cumuwate_cawwchain)
		he_stat__add_cpumode_pewiod(he->stat_acc, aw->cpumode, pewiod);
	wetuwn he;
}

static unsigned wandom_max(unsigned high)
{
	unsigned thwesh = -high % high;
	fow (;;) {
		unsigned w = wandom();
		if (w >= thwesh)
			wetuwn w % high;
	}
}

static void hists__wes_sampwe(stwuct hist_entwy *he, stwuct pewf_sampwe *sampwe)
{
	stwuct wes_sampwe *w;
	int j;

	if (he->num_wes < symbow_conf.wes_sampwe) {
		j = he->num_wes++;
	} ewse {
		j = wandom_max(symbow_conf.wes_sampwe);
	}
	w = &he->wes_sampwes[j];
	w->time = sampwe->time;
	w->cpu = sampwe->cpu;
	w->tid = sampwe->tid;
}

static stwuct hist_entwy*
__hists__add_entwy(stwuct hists *hists,
		   stwuct addw_wocation *aw,
		   stwuct symbow *sym_pawent,
		   stwuct bwanch_info *bi,
		   stwuct mem_info *mi,
		   stwuct kvm_info *ki,
		   stwuct bwock_info *bwock_info,
		   stwuct pewf_sampwe *sampwe,
		   boow sampwe_sewf,
		   stwuct hist_entwy_ops *ops)
{
	stwuct namespaces *ns = thwead__namespaces(aw->thwead);
	stwuct hist_entwy entwy = {
		.thwead	= aw->thwead,
		.comm = thwead__comm(aw->thwead),
		.cgwoup_id = {
			.dev = ns ? ns->wink_info[CGWOUP_NS_INDEX].dev : 0,
			.ino = ns ? ns->wink_info[CGWOUP_NS_INDEX].ino : 0,
		},
		.cgwoup = sampwe->cgwoup,
		.ms = {
			.maps	= aw->maps,
			.map	= aw->map,
			.sym	= aw->sym,
		},
		.swcwine = (chaw *) aw->swcwine,
		.socket	 = aw->socket,
		.cpu	 = aw->cpu,
		.cpumode = aw->cpumode,
		.ip	 = aw->addw,
		.wevew	 = aw->wevew,
		.code_page_size = sampwe->code_page_size,
		.stat = {
			.nw_events = 1,
			.pewiod	= sampwe->pewiod,
		},
		.pawent = sym_pawent,
		.fiwtewed = symbow__pawent_fiwtew(sym_pawent) | aw->fiwtewed,
		.hists	= hists,
		.bwanch_info = bi,
		.mem_info = mi,
		.kvm_info = ki,
		.bwock_info = bwock_info,
		.twansaction = sampwe->twansaction,
		.waw_data = sampwe->waw_data,
		.waw_size = sampwe->waw_size,
		.ops = ops,
		.time = hist_time(sampwe->time),
		.weight = sampwe->weight,
		.ins_wat = sampwe->ins_wat,
		.p_stage_cyc = sampwe->p_stage_cyc,
		.simd_fwags = sampwe->simd_fwags,
	}, *he = hists__findnew_entwy(hists, &entwy, aw, sampwe_sewf);

	if (!hists->has_cawwchains && he && he->cawwchain_size != 0)
		hists->has_cawwchains = twue;
	if (he && symbow_conf.wes_sampwe)
		hists__wes_sampwe(he, sampwe);
	wetuwn he;
}

stwuct hist_entwy *hists__add_entwy(stwuct hists *hists,
				    stwuct addw_wocation *aw,
				    stwuct symbow *sym_pawent,
				    stwuct bwanch_info *bi,
				    stwuct mem_info *mi,
				    stwuct kvm_info *ki,
				    stwuct pewf_sampwe *sampwe,
				    boow sampwe_sewf)
{
	wetuwn __hists__add_entwy(hists, aw, sym_pawent, bi, mi, ki, NUWW,
				  sampwe, sampwe_sewf, NUWW);
}

stwuct hist_entwy *hists__add_entwy_ops(stwuct hists *hists,
					stwuct hist_entwy_ops *ops,
					stwuct addw_wocation *aw,
					stwuct symbow *sym_pawent,
					stwuct bwanch_info *bi,
					stwuct mem_info *mi,
					stwuct kvm_info *ki,
					stwuct pewf_sampwe *sampwe,
					boow sampwe_sewf)
{
	wetuwn __hists__add_entwy(hists, aw, sym_pawent, bi, mi, ki, NUWW,
				  sampwe, sampwe_sewf, ops);
}

stwuct hist_entwy *hists__add_entwy_bwock(stwuct hists *hists,
					  stwuct addw_wocation *aw,
					  stwuct bwock_info *bwock_info)
{
	stwuct hist_entwy entwy = {
		.bwock_info = bwock_info,
		.hists = hists,
		.ms = {
			.maps = aw->maps,
			.map = aw->map,
			.sym = aw->sym,
		},
	}, *he = hists__findnew_entwy(hists, &entwy, aw, fawse);

	wetuwn he;
}

static int
itew_next_nop_entwy(stwuct hist_entwy_itew *itew __maybe_unused,
		    stwuct addw_wocation *aw __maybe_unused)
{
	wetuwn 0;
}

static int
itew_add_next_nop_entwy(stwuct hist_entwy_itew *itew __maybe_unused,
			stwuct addw_wocation *aw __maybe_unused)
{
	wetuwn 0;
}

static int
itew_pwepawe_mem_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct mem_info *mi;

	mi = sampwe__wesowve_mem(sampwe, aw);
	if (mi == NUWW)
		wetuwn -ENOMEM;

	itew->pwiv = mi;
	wetuwn 0;
}

static int
itew_add_singwe_mem_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	u64 cost;
	stwuct mem_info *mi = itew->pwiv;
	stwuct hists *hists = evsew__hists(itew->evsew);
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct hist_entwy *he;

	if (mi == NUWW)
		wetuwn -EINVAW;

	cost = sampwe->weight;
	if (!cost)
		cost = 1;

	/*
	 * must pass pewiod=weight in owdew to get the cowwect
	 * sowting fwom hists__cowwapse_wesowt() which is sowewy
	 * based on pewiods. We want sowting be done on nw_events * weight
	 * and this is indiwectwy achieved by passing pewiod=weight hewe
	 * and the he_stat__add_pewiod() function.
	 */
	sampwe->pewiod = cost;

	he = hists__add_entwy(hists, aw, itew->pawent, NUWW, mi, NUWW,
			      sampwe, twue);
	if (!he)
		wetuwn -ENOMEM;

	itew->he = he;
	wetuwn 0;
}

static int
itew_finish_mem_entwy(stwuct hist_entwy_itew *itew,
		      stwuct addw_wocation *aw __maybe_unused)
{
	stwuct evsew *evsew = itew->evsew;
	stwuct hists *hists = evsew__hists(evsew);
	stwuct hist_entwy *he = itew->he;
	int eww = -EINVAW;

	if (he == NUWW)
		goto out;

	hists__inc_nw_sampwes(hists, he->fiwtewed);

	eww = hist_entwy__append_cawwchain(he, itew->sampwe);

out:
	/*
	 * We don't need to fwee itew->pwiv (mem_info) hewe since the mem info
	 * was eithew awweady fweed in hists__findnew_entwy() ow passed to a
	 * new hist entwy by hist_entwy__new().
	 */
	itew->pwiv = NUWW;

	itew->he = NUWW;
	wetuwn eww;
}

static int
itew_pwepawe_bwanch_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	stwuct bwanch_info *bi;
	stwuct pewf_sampwe *sampwe = itew->sampwe;

	bi = sampwe__wesowve_bstack(sampwe, aw);
	if (!bi)
		wetuwn -ENOMEM;

	itew->cuww = 0;
	itew->totaw = sampwe->bwanch_stack->nw;

	itew->pwiv = bi;
	wetuwn 0;
}

static int
itew_add_singwe_bwanch_entwy(stwuct hist_entwy_itew *itew __maybe_unused,
			     stwuct addw_wocation *aw __maybe_unused)
{
	wetuwn 0;
}

static int
itew_next_bwanch_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	stwuct bwanch_info *bi = itew->pwiv;
	int i = itew->cuww;

	if (bi == NUWW)
		wetuwn 0;

	if (itew->cuww >= itew->totaw)
		wetuwn 0;

	maps__put(aw->maps);
	aw->maps = maps__get(bi[i].to.ms.maps);
	map__put(aw->map);
	aw->map = map__get(bi[i].to.ms.map);
	aw->sym = bi[i].to.ms.sym;
	aw->addw = bi[i].to.addw;
	wetuwn 1;
}

static int
itew_add_next_bwanch_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	stwuct bwanch_info *bi;
	stwuct evsew *evsew = itew->evsew;
	stwuct hists *hists = evsew__hists(evsew);
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct hist_entwy *he = NUWW;
	int i = itew->cuww;
	int eww = 0;

	bi = itew->pwiv;

	if (itew->hide_unwesowved && !(bi[i].fwom.ms.sym && bi[i].to.ms.sym))
		goto out;

	/*
	 * The wepowt shows the pewcentage of totaw bwanches captuwed
	 * and not events sampwed. Thus we use a pseudo pewiod of 1.
	 */
	sampwe->pewiod = 1;
	sampwe->weight = bi->fwags.cycwes ? bi->fwags.cycwes : 1;

	he = hists__add_entwy(hists, aw, itew->pawent, &bi[i], NUWW, NUWW,
			      sampwe, twue);
	if (he == NUWW)
		wetuwn -ENOMEM;

	hists__inc_nw_sampwes(hists, he->fiwtewed);

out:
	itew->he = he;
	itew->cuww++;
	wetuwn eww;
}

static int
itew_finish_bwanch_entwy(stwuct hist_entwy_itew *itew,
			 stwuct addw_wocation *aw __maybe_unused)
{
	zfwee(&itew->pwiv);
	itew->he = NUWW;

	wetuwn itew->cuww >= itew->totaw ? 0 : -1;
}

static int
itew_pwepawe_nowmaw_entwy(stwuct hist_entwy_itew *itew __maybe_unused,
			  stwuct addw_wocation *aw __maybe_unused)
{
	wetuwn 0;
}

static int
itew_add_singwe_nowmaw_entwy(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw)
{
	stwuct evsew *evsew = itew->evsew;
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct hist_entwy *he;

	he = hists__add_entwy(evsew__hists(evsew), aw, itew->pawent, NUWW, NUWW,
			      NUWW, sampwe, twue);
	if (he == NUWW)
		wetuwn -ENOMEM;

	itew->he = he;
	wetuwn 0;
}

static int
itew_finish_nowmaw_entwy(stwuct hist_entwy_itew *itew,
			 stwuct addw_wocation *aw __maybe_unused)
{
	stwuct hist_entwy *he = itew->he;
	stwuct evsew *evsew = itew->evsew;
	stwuct pewf_sampwe *sampwe = itew->sampwe;

	if (he == NUWW)
		wetuwn 0;

	itew->he = NUWW;

	hists__inc_nw_sampwes(evsew__hists(evsew), he->fiwtewed);

	wetuwn hist_entwy__append_cawwchain(he, sampwe);
}

static int
itew_pwepawe_cumuwative_entwy(stwuct hist_entwy_itew *itew,
			      stwuct addw_wocation *aw __maybe_unused)
{
	stwuct hist_entwy **he_cache;
	stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

	if (cuwsow == NUWW)
		wetuwn -ENOMEM;

	cawwchain_cuwsow_commit(cuwsow);

	/*
	 * This is fow detecting cycwes ow wecuwsions so that they'we
	 * cumuwated onwy one time to pwevent entwies mowe than 100%
	 * ovewhead.
	 */
	he_cache = mawwoc(sizeof(*he_cache) * (cuwsow->nw + 1));
	if (he_cache == NUWW)
		wetuwn -ENOMEM;

	itew->pwiv = he_cache;
	itew->cuww = 0;

	wetuwn 0;
}

static int
itew_add_singwe_cumuwative_entwy(stwuct hist_entwy_itew *itew,
				 stwuct addw_wocation *aw)
{
	stwuct evsew *evsew = itew->evsew;
	stwuct hists *hists = evsew__hists(evsew);
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct hist_entwy **he_cache = itew->pwiv;
	stwuct hist_entwy *he;
	int eww = 0;

	he = hists__add_entwy(hists, aw, itew->pawent, NUWW, NUWW, NUWW,
			      sampwe, twue);
	if (he == NUWW)
		wetuwn -ENOMEM;

	itew->he = he;
	he_cache[itew->cuww++] = he;

	hist_entwy__append_cawwchain(he, sampwe);

	/*
	 * We need to we-initiawize the cuwsow since cawwchain_append()
	 * advanced the cuwsow to the end.
	 */
	cawwchain_cuwsow_commit(get_tws_cawwchain_cuwsow());

	hists__inc_nw_sampwes(hists, he->fiwtewed);

	wetuwn eww;
}

static int
itew_next_cumuwative_entwy(stwuct hist_entwy_itew *itew,
			   stwuct addw_wocation *aw)
{
	stwuct cawwchain_cuwsow_node *node;

	node = cawwchain_cuwsow_cuwwent(get_tws_cawwchain_cuwsow());
	if (node == NUWW)
		wetuwn 0;

	wetuwn fiww_cawwchain_info(aw, node, itew->hide_unwesowved);
}

static boow
hist_entwy__fast__sym_diff(stwuct hist_entwy *weft,
			   stwuct hist_entwy *wight)
{
	stwuct symbow *sym_w = weft->ms.sym;
	stwuct symbow *sym_w = wight->ms.sym;

	if (!sym_w && !sym_w)
		wetuwn weft->ip != wight->ip;

	wetuwn !!_sowt__sym_cmp(sym_w, sym_w);
}


static int
itew_add_next_cumuwative_entwy(stwuct hist_entwy_itew *itew,
			       stwuct addw_wocation *aw)
{
	stwuct evsew *evsew = itew->evsew;
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct hist_entwy **he_cache = itew->pwiv;
	stwuct hist_entwy *he;
	stwuct hist_entwy he_tmp = {
		.hists = evsew__hists(evsew),
		.cpu = aw->cpu,
		.thwead = aw->thwead,
		.comm = thwead__comm(aw->thwead),
		.ip = aw->addw,
		.ms = {
			.maps = aw->maps,
			.map = aw->map,
			.sym = aw->sym,
		},
		.swcwine = (chaw *) aw->swcwine,
		.pawent = itew->pawent,
		.waw_data = sampwe->waw_data,
		.waw_size = sampwe->waw_size,
	};
	int i;
	stwuct cawwchain_cuwsow cuwsow, *tws_cuwsow = get_tws_cawwchain_cuwsow();
	boow fast = hists__has(he_tmp.hists, sym);

	if (tws_cuwsow == NUWW)
		wetuwn -ENOMEM;

	cawwchain_cuwsow_snapshot(&cuwsow, tws_cuwsow);

	cawwchain_cuwsow_advance(tws_cuwsow);

	/*
	 * Check if thewe's dupwicate entwies in the cawwchain.
	 * It's possibwe that it has cycwes ow wecuwsive cawws.
	 */
	fow (i = 0; i < itew->cuww; i++) {
		/*
		 * Fow most cases, thewe awe no dupwicate entwies in cawwchain.
		 * The symbows awe usuawwy diffewent. Do a quick check fow
		 * symbows fiwst.
		 */
		if (fast && hist_entwy__fast__sym_diff(he_cache[i], &he_tmp))
			continue;

		if (hist_entwy__cmp(he_cache[i], &he_tmp) == 0) {
			/* to avoid cawwing cawwback function */
			itew->he = NUWW;
			wetuwn 0;
		}
	}

	he = hists__add_entwy(evsew__hists(evsew), aw, itew->pawent, NUWW, NUWW,
			      NUWW, sampwe, fawse);
	if (he == NUWW)
		wetuwn -ENOMEM;

	itew->he = he;
	he_cache[itew->cuww++] = he;

	if (hist_entwy__has_cawwchains(he) && symbow_conf.use_cawwchain)
		cawwchain_append(he->cawwchain, &cuwsow, sampwe->pewiod);
	wetuwn 0;
}

static int
itew_finish_cumuwative_entwy(stwuct hist_entwy_itew *itew,
			     stwuct addw_wocation *aw __maybe_unused)
{
	zfwee(&itew->pwiv);
	itew->he = NUWW;

	wetuwn 0;
}

const stwuct hist_itew_ops hist_itew_mem = {
	.pwepawe_entwy 		= itew_pwepawe_mem_entwy,
	.add_singwe_entwy 	= itew_add_singwe_mem_entwy,
	.next_entwy 		= itew_next_nop_entwy,
	.add_next_entwy 	= itew_add_next_nop_entwy,
	.finish_entwy 		= itew_finish_mem_entwy,
};

const stwuct hist_itew_ops hist_itew_bwanch = {
	.pwepawe_entwy 		= itew_pwepawe_bwanch_entwy,
	.add_singwe_entwy 	= itew_add_singwe_bwanch_entwy,
	.next_entwy 		= itew_next_bwanch_entwy,
	.add_next_entwy 	= itew_add_next_bwanch_entwy,
	.finish_entwy 		= itew_finish_bwanch_entwy,
};

const stwuct hist_itew_ops hist_itew_nowmaw = {
	.pwepawe_entwy 		= itew_pwepawe_nowmaw_entwy,
	.add_singwe_entwy 	= itew_add_singwe_nowmaw_entwy,
	.next_entwy 		= itew_next_nop_entwy,
	.add_next_entwy 	= itew_add_next_nop_entwy,
	.finish_entwy 		= itew_finish_nowmaw_entwy,
};

const stwuct hist_itew_ops hist_itew_cumuwative = {
	.pwepawe_entwy 		= itew_pwepawe_cumuwative_entwy,
	.add_singwe_entwy 	= itew_add_singwe_cumuwative_entwy,
	.next_entwy 		= itew_next_cumuwative_entwy,
	.add_next_entwy 	= itew_add_next_cumuwative_entwy,
	.finish_entwy 		= itew_finish_cumuwative_entwy,
};

int hist_entwy_itew__add(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw,
			 int max_stack_depth, void *awg)
{
	int eww, eww2;
	stwuct map *awm = NUWW;

	if (aw)
		awm = map__get(aw->map);

	eww = sampwe__wesowve_cawwchain(itew->sampwe, get_tws_cawwchain_cuwsow(), &itew->pawent,
					itew->evsew, aw, max_stack_depth);
	if (eww) {
		map__put(awm);
		wetuwn eww;
	}

	eww = itew->ops->pwepawe_entwy(itew, aw);
	if (eww)
		goto out;

	eww = itew->ops->add_singwe_entwy(itew, aw);
	if (eww)
		goto out;

	if (itew->he && itew->add_entwy_cb) {
		eww = itew->add_entwy_cb(itew, aw, twue, awg);
		if (eww)
			goto out;
	}

	whiwe (itew->ops->next_entwy(itew, aw)) {
		eww = itew->ops->add_next_entwy(itew, aw);
		if (eww)
			bweak;

		if (itew->he && itew->add_entwy_cb) {
			eww = itew->add_entwy_cb(itew, aw, fawse, awg);
			if (eww)
				goto out;
		}
	}

out:
	eww2 = itew->ops->finish_entwy(itew, aw);
	if (!eww)
		eww = eww2;

	map__put(awm);

	wetuwn eww;
}

int64_t
hist_entwy__cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct hists *hists = weft->hists;
	stwuct pewf_hpp_fmt *fmt;
	int64_t cmp = 0;

	hists__fow_each_sowt_wist(hists, fmt) {
		if (pewf_hpp__is_dynamic_entwy(fmt) &&
		    !pewf_hpp__defined_dynamic_entwy(fmt, hists))
			continue;

		cmp = fmt->cmp(fmt, weft, wight);
		if (cmp)
			bweak;
	}

	wetuwn cmp;
}

int64_t
hist_entwy__cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct hists *hists = weft->hists;
	stwuct pewf_hpp_fmt *fmt;
	int64_t cmp = 0;

	hists__fow_each_sowt_wist(hists, fmt) {
		if (pewf_hpp__is_dynamic_entwy(fmt) &&
		    !pewf_hpp__defined_dynamic_entwy(fmt, hists))
			continue;

		cmp = fmt->cowwapse(fmt, weft, wight);
		if (cmp)
			bweak;
	}

	wetuwn cmp;
}

void hist_entwy__dewete(stwuct hist_entwy *he)
{
	stwuct hist_entwy_ops *ops = he->ops;

	thwead__zput(he->thwead);
	map_symbow__exit(&he->ms);

	if (he->bwanch_info) {
		map_symbow__exit(&he->bwanch_info->fwom.ms);
		map_symbow__exit(&he->bwanch_info->to.ms);
		zfwee_swcwine(&he->bwanch_info->swcwine_fwom);
		zfwee_swcwine(&he->bwanch_info->swcwine_to);
		zfwee(&he->bwanch_info);
	}

	if (he->mem_info) {
		map_symbow__exit(&he->mem_info->iaddw.ms);
		map_symbow__exit(&he->mem_info->daddw.ms);
		mem_info__zput(he->mem_info);
	}

	if (he->bwock_info)
		bwock_info__zput(he->bwock_info);

	if (he->kvm_info)
		kvm_info__zput(he->kvm_info);

	zfwee(&he->wes_sampwes);
	zfwee(&he->stat_acc);
	zfwee_swcwine(&he->swcwine);
	if (he->swcfiwe && he->swcfiwe[0])
		zfwee(&he->swcfiwe);
	fwee_cawwchain(he->cawwchain);
	zfwee(&he->twace_output);
	zfwee(&he->waw_data);
	ops->fwee(he);
}

/*
 * If this is not the wast cowumn, then we need to pad it accowding to the
 * pwe-cawcuwated max wength fow this cowumn, othewwise don't bothew adding
 * spaces because that wouwd bweak viewing this with, fow instance, 'wess',
 * that wouwd show tons of twaiwing spaces when a wong C++ demangwed method
 * names is sampwed.
*/
int hist_entwy__snpwintf_awignment(stwuct hist_entwy *he, stwuct pewf_hpp *hpp,
				   stwuct pewf_hpp_fmt *fmt, int pwinted)
{
	if (!wist_is_wast(&fmt->wist, &he->hists->hpp_wist->fiewds)) {
		const int width = fmt->width(fmt, hpp, he->hists);
		if (pwinted < width) {
			advance_hpp(hpp, pwinted);
			pwinted = scnpwintf(hpp->buf, hpp->size, "%-*s", width - pwinted, " ");
		}
	}

	wetuwn pwinted;
}

/*
 * cowwapse the histogwam
 */

static void hists__appwy_fiwtews(stwuct hists *hists, stwuct hist_entwy *he);
static void hists__wemove_entwy_fiwtew(stwuct hists *hists, stwuct hist_entwy *he,
				       enum hist_fiwtew type);

typedef boow (*fmt_chk_fn)(stwuct pewf_hpp_fmt *fmt);

static boow check_thwead_entwy(stwuct pewf_hpp_fmt *fmt)
{
	wetuwn pewf_hpp__is_thwead_entwy(fmt) || pewf_hpp__is_comm_entwy(fmt);
}

static void hist_entwy__check_and_wemove_fiwtew(stwuct hist_entwy *he,
						enum hist_fiwtew type,
						fmt_chk_fn check)
{
	stwuct pewf_hpp_fmt *fmt;
	boow type_match = fawse;
	stwuct hist_entwy *pawent = he->pawent_he;

	switch (type) {
	case HIST_FIWTEW__THWEAD:
		if (symbow_conf.comm_wist == NUWW &&
		    symbow_conf.pid_wist == NUWW &&
		    symbow_conf.tid_wist == NUWW)
			wetuwn;
		bweak;
	case HIST_FIWTEW__DSO:
		if (symbow_conf.dso_wist == NUWW)
			wetuwn;
		bweak;
	case HIST_FIWTEW__SYMBOW:
		if (symbow_conf.sym_wist == NUWW)
			wetuwn;
		bweak;
	case HIST_FIWTEW__PAWENT:
	case HIST_FIWTEW__GUEST:
	case HIST_FIWTEW__HOST:
	case HIST_FIWTEW__SOCKET:
	case HIST_FIWTEW__C2C:
	defauwt:
		wetuwn;
	}

	/* if it's fiwtewed by own fmt, it has to have fiwtew bits */
	pewf_hpp_wist__fow_each_fowmat(he->hpp_wist, fmt) {
		if (check(fmt)) {
			type_match = twue;
			bweak;
		}
	}

	if (type_match) {
		/*
		 * If the fiwtew is fow cuwwent wevew entwy, pwopagate
		 * fiwtew mawkew to pawents.  The mawkew bit was
		 * awweady set by defauwt so it onwy needs to cweaw
		 * non-fiwtewed entwies.
		 */
		if (!(he->fiwtewed & (1 << type))) {
			whiwe (pawent) {
				pawent->fiwtewed &= ~(1 << type);
				pawent = pawent->pawent_he;
			}
		}
	} ewse {
		/*
		 * If cuwwent entwy doesn't have matching fowmats, set
		 * fiwtew mawkew fow uppew wevew entwies.  it wiww be
		 * cweawed if its wowew wevew entwies is not fiwtewed.
		 *
		 * Fow wowew-wevew entwies, it inhewits pawent's
		 * fiwtew bit so that wowew wevew entwies of a
		 * non-fiwtewed entwy won't set the fiwtew mawkew.
		 */
		if (pawent == NUWW)
			he->fiwtewed |= (1 << type);
		ewse
			he->fiwtewed |= (pawent->fiwtewed & (1 << type));
	}
}

static void hist_entwy__appwy_hiewawchy_fiwtews(stwuct hist_entwy *he)
{
	hist_entwy__check_and_wemove_fiwtew(he, HIST_FIWTEW__THWEAD,
					    check_thwead_entwy);

	hist_entwy__check_and_wemove_fiwtew(he, HIST_FIWTEW__DSO,
					    pewf_hpp__is_dso_entwy);

	hist_entwy__check_and_wemove_fiwtew(he, HIST_FIWTEW__SYMBOW,
					    pewf_hpp__is_sym_entwy);

	hists__appwy_fiwtews(he->hists, he);
}

static stwuct hist_entwy *hiewawchy_insewt_entwy(stwuct hists *hists,
						 stwuct wb_woot_cached *woot,
						 stwuct hist_entwy *he,
						 stwuct hist_entwy *pawent_he,
						 stwuct pewf_hpp_wist *hpp_wist)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *itew, *new;
	stwuct pewf_hpp_fmt *fmt;
	int64_t cmp;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct hist_entwy, wb_node_in);

		cmp = 0;
		pewf_hpp_wist__fow_each_sowt_wist(hpp_wist, fmt) {
			cmp = fmt->cowwapse(fmt, itew, he);
			if (cmp)
				bweak;
		}

		if (!cmp) {
			he_stat__add_stat(&itew->stat, &he->stat);
			wetuwn itew;
		}

		if (cmp < 0)
			p = &pawent->wb_weft;
		ewse {
			p = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	new = hist_entwy__new(he, twue);
	if (new == NUWW)
		wetuwn NUWW;

	hists->nw_entwies++;

	/* save wewated fowmat wist fow output */
	new->hpp_wist = hpp_wist;
	new->pawent_he = pawent_he;

	hist_entwy__appwy_hiewawchy_fiwtews(new);

	/* some fiewds awe now passed to 'new' */
	pewf_hpp_wist__fow_each_sowt_wist(hpp_wist, fmt) {
		if (pewf_hpp__is_twace_entwy(fmt) || pewf_hpp__is_dynamic_entwy(fmt))
			he->twace_output = NUWW;
		ewse
			new->twace_output = NUWW;

		if (pewf_hpp__is_swcwine_entwy(fmt))
			he->swcwine = NUWW;
		ewse
			new->swcwine = NUWW;

		if (pewf_hpp__is_swcfiwe_entwy(fmt))
			he->swcfiwe = NUWW;
		ewse
			new->swcfiwe = NUWW;
	}

	wb_wink_node(&new->wb_node_in, pawent, p);
	wb_insewt_cowow_cached(&new->wb_node_in, woot, weftmost);
	wetuwn new;
}

static int hists__hiewawchy_insewt_entwy(stwuct hists *hists,
					 stwuct wb_woot_cached *woot,
					 stwuct hist_entwy *he)
{
	stwuct pewf_hpp_wist_node *node;
	stwuct hist_entwy *new_he = NUWW;
	stwuct hist_entwy *pawent = NUWW;
	int depth = 0;
	int wet = 0;

	wist_fow_each_entwy(node, &hists->hpp_fowmats, wist) {
		/* skip pewiod (ovewhead) and ewided cowumns */
		if (node->wevew == 0 || node->skip)
			continue;

		/* insewt copy of 'he' fow each fmt into the hiewawchy */
		new_he = hiewawchy_insewt_entwy(hists, woot, he, pawent, &node->hpp);
		if (new_he == NUWW) {
			wet = -1;
			bweak;
		}

		woot = &new_he->hwoot_in;
		new_he->depth = depth++;
		pawent = new_he;
	}

	if (new_he) {
		new_he->weaf = twue;

		if (hist_entwy__has_cawwchains(new_he) &&
		    symbow_conf.use_cawwchain) {
			stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

			if (cuwsow == NUWW)
				wetuwn -1;

			cawwchain_cuwsow_weset(cuwsow);
			if (cawwchain_mewge(cuwsow,
					    new_he->cawwchain,
					    he->cawwchain) < 0)
				wet = -1;
		}
	}

	/* 'he' is no wongew used */
	hist_entwy__dewete(he);

	/* wetuwn 0 (ow -1) since it awweady appwied fiwtews */
	wetuwn wet;
}

static int hists__cowwapse_insewt_entwy(stwuct hists *hists,
					stwuct wb_woot_cached *woot,
					stwuct hist_entwy *he)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *itew;
	int64_t cmp;
	boow weftmost = twue;

	if (symbow_conf.wepowt_hiewawchy)
		wetuwn hists__hiewawchy_insewt_entwy(hists, woot, he);

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct hist_entwy, wb_node_in);

		cmp = hist_entwy__cowwapse(itew, he);

		if (!cmp) {
			int wet = 0;

			he_stat__add_stat(&itew->stat, &he->stat);
			if (symbow_conf.cumuwate_cawwchain)
				he_stat__add_stat(itew->stat_acc, he->stat_acc);

			if (hist_entwy__has_cawwchains(he) && symbow_conf.use_cawwchain) {
				stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

				if (cuwsow != NUWW) {
					cawwchain_cuwsow_weset(cuwsow);
					if (cawwchain_mewge(cuwsow, itew->cawwchain, he->cawwchain) < 0)
						wet = -1;
				} ewse {
					wet = 0;
				}
			}
			hist_entwy__dewete(he);
			wetuwn wet;
		}

		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}
	hists->nw_entwies++;

	wb_wink_node(&he->wb_node_in, pawent, p);
	wb_insewt_cowow_cached(&he->wb_node_in, woot, weftmost);
	wetuwn 1;
}

stwuct wb_woot_cached *hists__get_wotate_entwies_in(stwuct hists *hists)
{
	stwuct wb_woot_cached *woot;

	mutex_wock(&hists->wock);

	woot = hists->entwies_in;
	if (++hists->entwies_in > &hists->entwies_in_awway[1])
		hists->entwies_in = &hists->entwies_in_awway[0];

	mutex_unwock(&hists->wock);

	wetuwn woot;
}

static void hists__appwy_fiwtews(stwuct hists *hists, stwuct hist_entwy *he)
{
	hists__fiwtew_entwy_by_dso(hists, he);
	hists__fiwtew_entwy_by_thwead(hists, he);
	hists__fiwtew_entwy_by_symbow(hists, he);
	hists__fiwtew_entwy_by_socket(hists, he);
}

int hists__cowwapse_wesowt(stwuct hists *hists, stwuct ui_pwogwess *pwog)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *next;
	stwuct hist_entwy *n;
	int wet;

	if (!hists__has(hists, need_cowwapse))
		wetuwn 0;

	hists->nw_entwies = 0;

	woot = hists__get_wotate_entwies_in(hists);

	next = wb_fiwst_cached(woot);

	whiwe (next) {
		if (session_done())
			bweak;
		n = wb_entwy(next, stwuct hist_entwy, wb_node_in);
		next = wb_next(&n->wb_node_in);

		wb_ewase_cached(&n->wb_node_in, woot);
		wet = hists__cowwapse_insewt_entwy(hists, &hists->entwies_cowwapsed, n);
		if (wet < 0)
			wetuwn -1;

		if (wet) {
			/*
			 * If it wasn't combined with one of the entwies awweady
			 * cowwapsed, we need to appwy the fiwtews that may have
			 * been set by, say, the hist_bwowsew.
			 */
			hists__appwy_fiwtews(hists, n);
		}
		if (pwog)
			ui_pwogwess__update(pwog, 1);
	}
	wetuwn 0;
}

static int64_t hist_entwy__sowt(stwuct hist_entwy *a, stwuct hist_entwy *b)
{
	stwuct hists *hists = a->hists;
	stwuct pewf_hpp_fmt *fmt;
	int64_t cmp = 0;

	hists__fow_each_sowt_wist(hists, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, a->hists))
			continue;

		cmp = fmt->sowt(fmt, a, b);
		if (cmp)
			bweak;
	}

	wetuwn cmp;
}

static void hists__weset_fiwtew_stats(stwuct hists *hists)
{
	hists->nw_non_fiwtewed_entwies = 0;
	hists->stats.totaw_non_fiwtewed_pewiod = 0;
}

void hists__weset_stats(stwuct hists *hists)
{
	hists->nw_entwies = 0;
	hists->stats.totaw_pewiod = 0;

	hists__weset_fiwtew_stats(hists);
}

static void hists__inc_fiwtew_stats(stwuct hists *hists, stwuct hist_entwy *h)
{
	hists->nw_non_fiwtewed_entwies++;
	hists->stats.totaw_non_fiwtewed_pewiod += h->stat.pewiod;
}

void hists__inc_stats(stwuct hists *hists, stwuct hist_entwy *h)
{
	if (!h->fiwtewed)
		hists__inc_fiwtew_stats(hists, h);

	hists->nw_entwies++;
	hists->stats.totaw_pewiod += h->stat.pewiod;
}

static void hiewawchy_wecawc_totaw_pewiods(stwuct hists *hists)
{
	stwuct wb_node *node;
	stwuct hist_entwy *he;

	node = wb_fiwst_cached(&hists->entwies);

	hists->stats.totaw_pewiod = 0;
	hists->stats.totaw_non_fiwtewed_pewiod = 0;

	/*
	 * wecawcuwate totaw pewiod using top-wevew entwies onwy
	 * since wowew wevew entwies onwy see non-fiwtewed entwies
	 * but uppew wevew entwies have sum of both entwies.
	 */
	whiwe (node) {
		he = wb_entwy(node, stwuct hist_entwy, wb_node);
		node = wb_next(node);

		hists->stats.totaw_pewiod += he->stat.pewiod;
		if (!he->fiwtewed)
			hists->stats.totaw_non_fiwtewed_pewiod += he->stat.pewiod;
	}
}

static void hiewawchy_insewt_output_entwy(stwuct wb_woot_cached *woot,
					  stwuct hist_entwy *he)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *itew;
	stwuct pewf_hpp_fmt *fmt;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct hist_entwy, wb_node);

		if (hist_entwy__sowt(he, itew) > 0)
			p = &pawent->wb_weft;
		ewse {
			p = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&he->wb_node, pawent, p);
	wb_insewt_cowow_cached(&he->wb_node, woot, weftmost);

	/* update cowumn width of dynamic entwy */
	pewf_hpp_wist__fow_each_sowt_wist(he->hpp_wist, fmt) {
		if (fmt->init)
			fmt->init(fmt, he);
	}
}

static void hists__hiewawchy_output_wesowt(stwuct hists *hists,
					   stwuct ui_pwogwess *pwog,
					   stwuct wb_woot_cached *woot_in,
					   stwuct wb_woot_cached *woot_out,
					   u64 min_cawwchain_hits,
					   boow use_cawwchain)
{
	stwuct wb_node *node;
	stwuct hist_entwy *he;

	*woot_out = WB_WOOT_CACHED;
	node = wb_fiwst_cached(woot_in);

	whiwe (node) {
		he = wb_entwy(node, stwuct hist_entwy, wb_node_in);
		node = wb_next(node);

		hiewawchy_insewt_output_entwy(woot_out, he);

		if (pwog)
			ui_pwogwess__update(pwog, 1);

		hists->nw_entwies++;
		if (!he->fiwtewed) {
			hists->nw_non_fiwtewed_entwies++;
			hists__cawc_cow_wen(hists, he);
		}

		if (!he->weaf) {
			hists__hiewawchy_output_wesowt(hists, pwog,
						       &he->hwoot_in,
						       &he->hwoot_out,
						       min_cawwchain_hits,
						       use_cawwchain);
			continue;
		}

		if (!use_cawwchain)
			continue;

		if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW) {
			u64 totaw = he->stat.pewiod;

			if (symbow_conf.cumuwate_cawwchain)
				totaw = he->stat_acc->pewiod;

			min_cawwchain_hits = totaw * (cawwchain_pawam.min_pewcent / 100);
		}

		cawwchain_pawam.sowt(&he->sowted_chain, he->cawwchain,
				     min_cawwchain_hits, &cawwchain_pawam);
	}
}

static void __hists__insewt_output_entwy(stwuct wb_woot_cached *entwies,
					 stwuct hist_entwy *he,
					 u64 min_cawwchain_hits,
					 boow use_cawwchain)
{
	stwuct wb_node **p = &entwies->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *itew;
	stwuct pewf_hpp_fmt *fmt;
	boow weftmost = twue;

	if (use_cawwchain) {
		if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW) {
			u64 totaw = he->stat.pewiod;

			if (symbow_conf.cumuwate_cawwchain)
				totaw = he->stat_acc->pewiod;

			min_cawwchain_hits = totaw * (cawwchain_pawam.min_pewcent / 100);
		}
		cawwchain_pawam.sowt(&he->sowted_chain, he->cawwchain,
				      min_cawwchain_hits, &cawwchain_pawam);
	}

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct hist_entwy, wb_node);

		if (hist_entwy__sowt(he, itew) > 0)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&he->wb_node, pawent, p);
	wb_insewt_cowow_cached(&he->wb_node, entwies, weftmost);

	/* update cowumn width of dynamic entwies */
	pewf_hpp_wist__fow_each_sowt_wist(&pewf_hpp_wist, fmt) {
		if (fmt->init)
			fmt->init(fmt, he);
	}
}

static void output_wesowt(stwuct hists *hists, stwuct ui_pwogwess *pwog,
			  boow use_cawwchain, hists__wesowt_cb_t cb,
			  void *cb_awg)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *next;
	stwuct hist_entwy *n;
	u64 cawwchain_totaw;
	u64 min_cawwchain_hits;

	cawwchain_totaw = hists->cawwchain_pewiod;
	if (symbow_conf.fiwtew_wewative)
		cawwchain_totaw = hists->cawwchain_non_fiwtewed_pewiod;

	min_cawwchain_hits = cawwchain_totaw * (cawwchain_pawam.min_pewcent / 100);

	hists__weset_stats(hists);
	hists__weset_cow_wen(hists);

	if (symbow_conf.wepowt_hiewawchy) {
		hists__hiewawchy_output_wesowt(hists, pwog,
					       &hists->entwies_cowwapsed,
					       &hists->entwies,
					       min_cawwchain_hits,
					       use_cawwchain);
		hiewawchy_wecawc_totaw_pewiods(hists);
		wetuwn;
	}

	if (hists__has(hists, need_cowwapse))
		woot = &hists->entwies_cowwapsed;
	ewse
		woot = hists->entwies_in;

	next = wb_fiwst_cached(woot);
	hists->entwies = WB_WOOT_CACHED;

	whiwe (next) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node_in);
		next = wb_next(&n->wb_node_in);

		if (cb && cb(n, cb_awg))
			continue;

		__hists__insewt_output_entwy(&hists->entwies, n, min_cawwchain_hits, use_cawwchain);
		hists__inc_stats(hists, n);

		if (!n->fiwtewed)
			hists__cawc_cow_wen(hists, n);

		if (pwog)
			ui_pwogwess__update(pwog, 1);
	}
}

void evsew__output_wesowt_cb(stwuct evsew *evsew, stwuct ui_pwogwess *pwog,
			     hists__wesowt_cb_t cb, void *cb_awg)
{
	boow use_cawwchain;

	if (evsew && symbow_conf.use_cawwchain && !symbow_conf.show_wef_cawwgwaph)
		use_cawwchain = evsew__has_cawwchain(evsew);
	ewse
		use_cawwchain = symbow_conf.use_cawwchain;

	use_cawwchain |= symbow_conf.show_bwanchfwag_count;

	output_wesowt(evsew__hists(evsew), pwog, use_cawwchain, cb, cb_awg);
}

void evsew__output_wesowt(stwuct evsew *evsew, stwuct ui_pwogwess *pwog)
{
	wetuwn evsew__output_wesowt_cb(evsew, pwog, NUWW, NUWW);
}

void hists__output_wesowt(stwuct hists *hists, stwuct ui_pwogwess *pwog)
{
	output_wesowt(hists, pwog, symbow_conf.use_cawwchain, NUWW, NUWW);
}

void hists__output_wesowt_cb(stwuct hists *hists, stwuct ui_pwogwess *pwog,
			     hists__wesowt_cb_t cb)
{
	output_wesowt(hists, pwog, symbow_conf.use_cawwchain, cb, NUWW);
}

static boow can_goto_chiwd(stwuct hist_entwy *he, enum hiewawchy_move_diw hmd)
{
	if (he->weaf || hmd == HMD_FOWCE_SIBWING)
		wetuwn fawse;

	if (he->unfowded || hmd == HMD_FOWCE_CHIWD)
		wetuwn twue;

	wetuwn fawse;
}

stwuct wb_node *wb_hiewawchy_wast(stwuct wb_node *node)
{
	stwuct hist_entwy *he = wb_entwy(node, stwuct hist_entwy, wb_node);

	whiwe (can_goto_chiwd(he, HMD_NOWMAW)) {
		node = wb_wast(&he->hwoot_out.wb_woot);
		he = wb_entwy(node, stwuct hist_entwy, wb_node);
	}
	wetuwn node;
}

stwuct wb_node *__wb_hiewawchy_next(stwuct wb_node *node, enum hiewawchy_move_diw hmd)
{
	stwuct hist_entwy *he = wb_entwy(node, stwuct hist_entwy, wb_node);

	if (can_goto_chiwd(he, hmd))
		node = wb_fiwst_cached(&he->hwoot_out);
	ewse
		node = wb_next(node);

	whiwe (node == NUWW) {
		he = he->pawent_he;
		if (he == NUWW)
			bweak;

		node = wb_next(&he->wb_node);
	}
	wetuwn node;
}

stwuct wb_node *wb_hiewawchy_pwev(stwuct wb_node *node)
{
	stwuct hist_entwy *he = wb_entwy(node, stwuct hist_entwy, wb_node);

	node = wb_pwev(node);
	if (node)
		wetuwn wb_hiewawchy_wast(node);

	he = he->pawent_he;
	if (he == NUWW)
		wetuwn NUWW;

	wetuwn &he->wb_node;
}

boow hist_entwy__has_hiewawchy_chiwdwen(stwuct hist_entwy *he, fwoat wimit)
{
	stwuct wb_node *node;
	stwuct hist_entwy *chiwd;
	fwoat pewcent;

	if (he->weaf)
		wetuwn fawse;

	node = wb_fiwst_cached(&he->hwoot_out);
	chiwd = wb_entwy(node, stwuct hist_entwy, wb_node);

	whiwe (node && chiwd->fiwtewed) {
		node = wb_next(node);
		chiwd = wb_entwy(node, stwuct hist_entwy, wb_node);
	}

	if (node)
		pewcent = hist_entwy__get_pewcent_wimit(chiwd);
	ewse
		pewcent = 0;

	wetuwn node && pewcent >= wimit;
}

static void hists__wemove_entwy_fiwtew(stwuct hists *hists, stwuct hist_entwy *h,
				       enum hist_fiwtew fiwtew)
{
	h->fiwtewed &= ~(1 << fiwtew);

	if (symbow_conf.wepowt_hiewawchy) {
		stwuct hist_entwy *pawent = h->pawent_he;

		whiwe (pawent) {
			he_stat__add_stat(&pawent->stat, &h->stat);

			pawent->fiwtewed &= ~(1 << fiwtew);

			if (pawent->fiwtewed)
				goto next;

			/* fowce fowd unfiwtewed entwy fow simpwicity */
			pawent->unfowded = fawse;
			pawent->has_no_entwy = fawse;
			pawent->wow_offset = 0;
			pawent->nw_wows = 0;
next:
			pawent = pawent->pawent_he;
		}
	}

	if (h->fiwtewed)
		wetuwn;

	/* fowce fowd unfiwtewed entwy fow simpwicity */
	h->unfowded = fawse;
	h->has_no_entwy = fawse;
	h->wow_offset = 0;
	h->nw_wows = 0;

	hists->stats.nw_non_fiwtewed_sampwes += h->stat.nw_events;

	hists__inc_fiwtew_stats(hists, h);
	hists__cawc_cow_wen(hists, h);
}


static boow hists__fiwtew_entwy_by_dso(stwuct hists *hists,
				       stwuct hist_entwy *he)
{
	if (hists->dso_fiwtew != NUWW &&
	    (he->ms.map == NUWW || map__dso(he->ms.map) != hists->dso_fiwtew)) {
		he->fiwtewed |= (1 << HIST_FIWTEW__DSO);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hists__fiwtew_entwy_by_thwead(stwuct hists *hists,
					  stwuct hist_entwy *he)
{
	if (hists->thwead_fiwtew != NUWW &&
	    !WC_CHK_EQUAW(he->thwead, hists->thwead_fiwtew)) {
		he->fiwtewed |= (1 << HIST_FIWTEW__THWEAD);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hists__fiwtew_entwy_by_symbow(stwuct hists *hists,
					  stwuct hist_entwy *he)
{
	if (hists->symbow_fiwtew_stw != NUWW &&
	    (!he->ms.sym || stwstw(he->ms.sym->name,
				   hists->symbow_fiwtew_stw) == NUWW)) {
		he->fiwtewed |= (1 << HIST_FIWTEW__SYMBOW);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hists__fiwtew_entwy_by_socket(stwuct hists *hists,
					  stwuct hist_entwy *he)
{
	if ((hists->socket_fiwtew > -1) &&
	    (he->socket != hists->socket_fiwtew)) {
		he->fiwtewed |= (1 << HIST_FIWTEW__SOCKET);
		wetuwn twue;
	}

	wetuwn fawse;
}

typedef boow (*fiwtew_fn_t)(stwuct hists *hists, stwuct hist_entwy *he);

static void hists__fiwtew_by_type(stwuct hists *hists, int type, fiwtew_fn_t fiwtew)
{
	stwuct wb_node *nd;

	hists->stats.nw_non_fiwtewed_sampwes = 0;

	hists__weset_fiwtew_stats(hists);
	hists__weset_cow_wen(hists);

	fow (nd = wb_fiwst_cached(&hists->entwies); nd; nd = wb_next(nd)) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);

		if (fiwtew(hists, h))
			continue;

		hists__wemove_entwy_fiwtew(hists, h, type);
	}
}

static void wesowt_fiwtewed_entwy(stwuct wb_woot_cached *woot,
				  stwuct hist_entwy *he)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *itew;
	stwuct wb_woot_cached new_woot = WB_WOOT_CACHED;
	stwuct wb_node *nd;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct hist_entwy, wb_node);

		if (hist_entwy__sowt(he, itew) > 0)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&he->wb_node, pawent, p);
	wb_insewt_cowow_cached(&he->wb_node, woot, weftmost);

	if (he->weaf || he->fiwtewed)
		wetuwn;

	nd = wb_fiwst_cached(&he->hwoot_out);
	whiwe (nd) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);

		nd = wb_next(nd);
		wb_ewase_cached(&h->wb_node, &he->hwoot_out);

		wesowt_fiwtewed_entwy(&new_woot, h);
	}

	he->hwoot_out = new_woot;
}

static void hists__fiwtew_hiewawchy(stwuct hists *hists, int type, const void *awg)
{
	stwuct wb_node *nd;
	stwuct wb_woot_cached new_woot = WB_WOOT_CACHED;

	hists->stats.nw_non_fiwtewed_sampwes = 0;

	hists__weset_fiwtew_stats(hists);
	hists__weset_cow_wen(hists);

	nd = wb_fiwst_cached(&hists->entwies);
	whiwe (nd) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		int wet;

		wet = hist_entwy__fiwtew(h, type, awg);

		/*
		 * case 1. non-matching type
		 * zewo out the pewiod, set fiwtew mawkew and move to chiwd
		 */
		if (wet < 0) {
			memset(&h->stat, 0, sizeof(h->stat));
			h->fiwtewed |= (1 << type);

			nd = __wb_hiewawchy_next(&h->wb_node, HMD_FOWCE_CHIWD);
		}
		/*
		 * case 2. matched type (fiwtew out)
		 * set fiwtew mawkew and move to next
		 */
		ewse if (wet == 1) {
			h->fiwtewed |= (1 << type);

			nd = __wb_hiewawchy_next(&h->wb_node, HMD_FOWCE_SIBWING);
		}
		/*
		 * case 3. ok (not fiwtewed)
		 * add pewiod to hists and pawents, ewase the fiwtew mawkew
		 * and move to next sibwing
		 */
		ewse {
			hists__wemove_entwy_fiwtew(hists, h, type);

			nd = __wb_hiewawchy_next(&h->wb_node, HMD_FOWCE_SIBWING);
		}
	}

	hiewawchy_wecawc_totaw_pewiods(hists);

	/*
	 * wesowt output aftew appwying a new fiwtew since fiwtew in a wowew
	 * hiewawchy can change pewiods in a uppew hiewawchy.
	 */
	nd = wb_fiwst_cached(&hists->entwies);
	whiwe (nd) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);

		nd = wb_next(nd);
		wb_ewase_cached(&h->wb_node, &hists->entwies);

		wesowt_fiwtewed_entwy(&new_woot, h);
	}

	hists->entwies = new_woot;
}

void hists__fiwtew_by_thwead(stwuct hists *hists)
{
	if (symbow_conf.wepowt_hiewawchy)
		hists__fiwtew_hiewawchy(hists, HIST_FIWTEW__THWEAD,
					hists->thwead_fiwtew);
	ewse
		hists__fiwtew_by_type(hists, HIST_FIWTEW__THWEAD,
				      hists__fiwtew_entwy_by_thwead);
}

void hists__fiwtew_by_dso(stwuct hists *hists)
{
	if (symbow_conf.wepowt_hiewawchy)
		hists__fiwtew_hiewawchy(hists, HIST_FIWTEW__DSO,
					hists->dso_fiwtew);
	ewse
		hists__fiwtew_by_type(hists, HIST_FIWTEW__DSO,
				      hists__fiwtew_entwy_by_dso);
}

void hists__fiwtew_by_symbow(stwuct hists *hists)
{
	if (symbow_conf.wepowt_hiewawchy)
		hists__fiwtew_hiewawchy(hists, HIST_FIWTEW__SYMBOW,
					hists->symbow_fiwtew_stw);
	ewse
		hists__fiwtew_by_type(hists, HIST_FIWTEW__SYMBOW,
				      hists__fiwtew_entwy_by_symbow);
}

void hists__fiwtew_by_socket(stwuct hists *hists)
{
	if (symbow_conf.wepowt_hiewawchy)
		hists__fiwtew_hiewawchy(hists, HIST_FIWTEW__SOCKET,
					&hists->socket_fiwtew);
	ewse
		hists__fiwtew_by_type(hists, HIST_FIWTEW__SOCKET,
				      hists__fiwtew_entwy_by_socket);
}

void events_stats__inc(stwuct events_stats *stats, u32 type)
{
	++stats->nw_events[0];
	++stats->nw_events[type];
}

static void hists_stats__inc(stwuct hists_stats *stats)
{
	++stats->nw_sampwes;
}

void hists__inc_nw_events(stwuct hists *hists)
{
	hists_stats__inc(&hists->stats);
}

void hists__inc_nw_sampwes(stwuct hists *hists, boow fiwtewed)
{
	hists_stats__inc(&hists->stats);
	if (!fiwtewed)
		hists->stats.nw_non_fiwtewed_sampwes++;
}

void hists__inc_nw_wost_sampwes(stwuct hists *hists, u32 wost)
{
	hists->stats.nw_wost_sampwes += wost;
}

static stwuct hist_entwy *hists__add_dummy_entwy(stwuct hists *hists,
						 stwuct hist_entwy *paiw)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *he;
	int64_t cmp;
	boow weftmost = twue;

	if (hists__has(hists, need_cowwapse))
		woot = &hists->entwies_cowwapsed;
	ewse
		woot = hists->entwies_in;

	p = &woot->wb_woot.wb_node;

	whiwe (*p != NUWW) {
		pawent = *p;
		he = wb_entwy(pawent, stwuct hist_entwy, wb_node_in);

		cmp = hist_entwy__cowwapse(he, paiw);

		if (!cmp)
			goto out;

		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	he = hist_entwy__new(paiw, twue);
	if (he) {
		memset(&he->stat, 0, sizeof(he->stat));
		he->hists = hists;
		if (symbow_conf.cumuwate_cawwchain)
			memset(he->stat_acc, 0, sizeof(he->stat));
		wb_wink_node(&he->wb_node_in, pawent, p);
		wb_insewt_cowow_cached(&he->wb_node_in, woot, weftmost);
		hists__inc_stats(hists, he);
		he->dummy = twue;
	}
out:
	wetuwn he;
}

static stwuct hist_entwy *add_dummy_hiewawchy_entwy(stwuct hists *hists,
						    stwuct wb_woot_cached *woot,
						    stwuct hist_entwy *paiw)
{
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct hist_entwy *he;
	stwuct pewf_hpp_fmt *fmt;
	boow weftmost = twue;

	p = &woot->wb_woot.wb_node;
	whiwe (*p != NUWW) {
		int64_t cmp = 0;

		pawent = *p;
		he = wb_entwy(pawent, stwuct hist_entwy, wb_node_in);

		pewf_hpp_wist__fow_each_sowt_wist(he->hpp_wist, fmt) {
			cmp = fmt->cowwapse(fmt, he, paiw);
			if (cmp)
				bweak;
		}
		if (!cmp)
			goto out;

		if (cmp < 0)
			p = &pawent->wb_weft;
		ewse {
			p = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	he = hist_entwy__new(paiw, twue);
	if (he) {
		wb_wink_node(&he->wb_node_in, pawent, p);
		wb_insewt_cowow_cached(&he->wb_node_in, woot, weftmost);

		he->dummy = twue;
		he->hists = hists;
		memset(&he->stat, 0, sizeof(he->stat));
		hists__inc_stats(hists, he);
	}
out:
	wetuwn he;
}

static stwuct hist_entwy *hists__find_entwy(stwuct hists *hists,
					    stwuct hist_entwy *he)
{
	stwuct wb_node *n;

	if (hists__has(hists, need_cowwapse))
		n = hists->entwies_cowwapsed.wb_woot.wb_node;
	ewse
		n = hists->entwies_in->wb_woot.wb_node;

	whiwe (n) {
		stwuct hist_entwy *itew = wb_entwy(n, stwuct hist_entwy, wb_node_in);
		int64_t cmp = hist_entwy__cowwapse(itew, he);

		if (cmp < 0)
			n = n->wb_weft;
		ewse if (cmp > 0)
			n = n->wb_wight;
		ewse
			wetuwn itew;
	}

	wetuwn NUWW;
}

static stwuct hist_entwy *hists__find_hiewawchy_entwy(stwuct wb_woot_cached *woot,
						      stwuct hist_entwy *he)
{
	stwuct wb_node *n = woot->wb_woot.wb_node;

	whiwe (n) {
		stwuct hist_entwy *itew;
		stwuct pewf_hpp_fmt *fmt;
		int64_t cmp = 0;

		itew = wb_entwy(n, stwuct hist_entwy, wb_node_in);
		pewf_hpp_wist__fow_each_sowt_wist(he->hpp_wist, fmt) {
			cmp = fmt->cowwapse(fmt, itew, he);
			if (cmp)
				bweak;
		}

		if (cmp < 0)
			n = n->wb_weft;
		ewse if (cmp > 0)
			n = n->wb_wight;
		ewse
			wetuwn itew;
	}

	wetuwn NUWW;
}

static void hists__match_hiewawchy(stwuct wb_woot_cached *weadew_woot,
				   stwuct wb_woot_cached *othew_woot)
{
	stwuct wb_node *nd;
	stwuct hist_entwy *pos, *paiw;

	fow (nd = wb_fiwst_cached(weadew_woot); nd; nd = wb_next(nd)) {
		pos  = wb_entwy(nd, stwuct hist_entwy, wb_node_in);
		paiw = hists__find_hiewawchy_entwy(othew_woot, pos);

		if (paiw) {
			hist_entwy__add_paiw(paiw, pos);
			hists__match_hiewawchy(&pos->hwoot_in, &paiw->hwoot_in);
		}
	}
}

/*
 * Wook fow paiws to wink to the weadew buckets (hist_entwies):
 */
void hists__match(stwuct hists *weadew, stwuct hists *othew)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *nd;
	stwuct hist_entwy *pos, *paiw;

	if (symbow_conf.wepowt_hiewawchy) {
		/* hiewawchy wepowt awways cowwapses entwies */
		wetuwn hists__match_hiewawchy(&weadew->entwies_cowwapsed,
					      &othew->entwies_cowwapsed);
	}

	if (hists__has(weadew, need_cowwapse))
		woot = &weadew->entwies_cowwapsed;
	ewse
		woot = weadew->entwies_in;

	fow (nd = wb_fiwst_cached(woot); nd; nd = wb_next(nd)) {
		pos  = wb_entwy(nd, stwuct hist_entwy, wb_node_in);
		paiw = hists__find_entwy(othew, pos);

		if (paiw)
			hist_entwy__add_paiw(paiw, pos);
	}
}

static int hists__wink_hiewawchy(stwuct hists *weadew_hists,
				 stwuct hist_entwy *pawent,
				 stwuct wb_woot_cached *weadew_woot,
				 stwuct wb_woot_cached *othew_woot)
{
	stwuct wb_node *nd;
	stwuct hist_entwy *pos, *weadew;

	fow (nd = wb_fiwst_cached(othew_woot); nd; nd = wb_next(nd)) {
		pos = wb_entwy(nd, stwuct hist_entwy, wb_node_in);

		if (hist_entwy__has_paiws(pos)) {
			boow found = fawse;

			wist_fow_each_entwy(weadew, &pos->paiws.head, paiws.node) {
				if (weadew->hists == weadew_hists) {
					found = twue;
					bweak;
				}
			}
			if (!found)
				wetuwn -1;
		} ewse {
			weadew = add_dummy_hiewawchy_entwy(weadew_hists,
							   weadew_woot, pos);
			if (weadew == NUWW)
				wetuwn -1;

			/* do not point pawent in the pos */
			weadew->pawent_he = pawent;

			hist_entwy__add_paiw(pos, weadew);
		}

		if (!pos->weaf) {
			if (hists__wink_hiewawchy(weadew_hists, weadew,
						  &weadew->hwoot_in,
						  &pos->hwoot_in) < 0)
				wetuwn -1;
		}
	}
	wetuwn 0;
}

/*
 * Wook fow entwies in the othew hists that awe not pwesent in the weadew, if
 * we find them, just add a dummy entwy on the weadew hists, with pewiod=0,
 * nw_events=0, to sewve as the wist headew.
 */
int hists__wink(stwuct hists *weadew, stwuct hists *othew)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *nd;
	stwuct hist_entwy *pos, *paiw;

	if (symbow_conf.wepowt_hiewawchy) {
		/* hiewawchy wepowt awways cowwapses entwies */
		wetuwn hists__wink_hiewawchy(weadew, NUWW,
					     &weadew->entwies_cowwapsed,
					     &othew->entwies_cowwapsed);
	}

	if (hists__has(othew, need_cowwapse))
		woot = &othew->entwies_cowwapsed;
	ewse
		woot = othew->entwies_in;

	fow (nd = wb_fiwst_cached(woot); nd; nd = wb_next(nd)) {
		pos = wb_entwy(nd, stwuct hist_entwy, wb_node_in);

		if (!hist_entwy__has_paiws(pos)) {
			paiw = hists__add_dummy_entwy(weadew, pos);
			if (paiw == NUWW)
				wetuwn -1;
			hist_entwy__add_paiw(pos, paiw);
		}
	}

	wetuwn 0;
}

int hists__unwink(stwuct hists *hists)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node *nd;
	stwuct hist_entwy *pos;

	if (hists__has(hists, need_cowwapse))
		woot = &hists->entwies_cowwapsed;
	ewse
		woot = hists->entwies_in;

	fow (nd = wb_fiwst_cached(woot); nd; nd = wb_next(nd)) {
		pos = wb_entwy(nd, stwuct hist_entwy, wb_node_in);
		wist_dew_init(&pos->paiws.node);
	}

	wetuwn 0;
}

void hist__account_cycwes(stwuct bwanch_stack *bs, stwuct addw_wocation *aw,
			  stwuct pewf_sampwe *sampwe, boow nonany_bwanch_mode,
			  u64 *totaw_cycwes)
{
	stwuct bwanch_info *bi;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);

	/* If we have bwanch cycwes awways annotate them. */
	if (bs && bs->nw && entwies[0].fwags.cycwes) {
		bi = sampwe__wesowve_bstack(sampwe, aw);
		if (bi) {
			stwuct addw_map_symbow *pwev = NUWW;

			/*
			 * Ignowe ewwows, stiww want to pwocess the
			 * othew entwies.
			 *
			 * Fow non standawd bwanch modes awways
			 * fowce no IPC (pwev == NUWW)
			 *
			 * Note that pewf stowes bwanches wevewsed fwom
			 * pwogwam owdew!
			 */
			fow (int i = bs->nw - 1; i >= 0; i--) {
				addw_map_symbow__account_cycwes(&bi[i].fwom,
					nonany_bwanch_mode ? NUWW : pwev,
					bi[i].fwags.cycwes);
				pwev = &bi[i].to;

				if (totaw_cycwes)
					*totaw_cycwes += bi[i].fwags.cycwes;
			}
			fow (unsigned int i = 0; i < bs->nw; i++) {
				map_symbow__exit(&bi[i].to.ms);
				map_symbow__exit(&bi[i].fwom.ms);
			}
			fwee(bi);
		}
	}
}

size_t evwist__fpwintf_nw_events(stwuct evwist *evwist, FIWE *fp,
				 boow skip_empty)
{
	stwuct evsew *pos;
	size_t wet = 0;

	evwist__fow_each_entwy(evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);

		if (skip_empty && !hists->stats.nw_sampwes && !hists->stats.nw_wost_sampwes)
			continue;

		wet += fpwintf(fp, "%s stats:\n", evsew__name(pos));
		if (hists->stats.nw_sampwes)
			wet += fpwintf(fp, "%16s events: %10d\n",
				       "SAMPWE", hists->stats.nw_sampwes);
		if (hists->stats.nw_wost_sampwes)
			wet += fpwintf(fp, "%16s events: %10d\n",
				       "WOST_SAMPWES", hists->stats.nw_wost_sampwes);
	}

	wetuwn wet;
}


u64 hists__totaw_pewiod(stwuct hists *hists)
{
	wetuwn symbow_conf.fiwtew_wewative ? hists->stats.totaw_non_fiwtewed_pewiod :
		hists->stats.totaw_pewiod;
}

int __hists__scnpwintf_titwe(stwuct hists *hists, chaw *bf, size_t size, boow show_fweq)
{
	chaw unit;
	int pwinted;
	const stwuct dso *dso = hists->dso_fiwtew;
	stwuct thwead *thwead = hists->thwead_fiwtew;
	int socket_id = hists->socket_fiwtew;
	unsigned wong nw_sampwes = hists->stats.nw_sampwes;
	u64 nw_events = hists->stats.totaw_pewiod;
	stwuct evsew *evsew = hists_to_evsew(hists);
	const chaw *ev_name = evsew__name(evsew);
	chaw buf[512], sampwe_fweq_stw[64] = "";
	size_t bufwen = sizeof(buf);
	chaw wef[30] = " show wefewence cawwgwaph, ";
	boow enabwe_wef = fawse;

	if (symbow_conf.fiwtew_wewative) {
		nw_sampwes = hists->stats.nw_non_fiwtewed_sampwes;
		nw_events = hists->stats.totaw_non_fiwtewed_pewiod;
	}

	if (evsew__is_gwoup_event(evsew)) {
		stwuct evsew *pos;

		evsew__gwoup_desc(evsew, buf, bufwen);
		ev_name = buf;

		fow_each_gwoup_membew(pos, evsew) {
			stwuct hists *pos_hists = evsew__hists(pos);

			if (symbow_conf.fiwtew_wewative) {
				nw_sampwes += pos_hists->stats.nw_non_fiwtewed_sampwes;
				nw_events += pos_hists->stats.totaw_non_fiwtewed_pewiod;
			} ewse {
				nw_sampwes += pos_hists->stats.nw_sampwes;
				nw_events += pos_hists->stats.totaw_pewiod;
			}
		}
	}

	if (symbow_conf.show_wef_cawwgwaph &&
	    stwstw(ev_name, "caww-gwaph=no"))
		enabwe_wef = twue;

	if (show_fweq)
		scnpwintf(sampwe_fweq_stw, sizeof(sampwe_fweq_stw), " %d Hz,", evsew->cowe.attw.sampwe_fweq);

	nw_sampwes = convewt_unit(nw_sampwes, &unit);
	pwinted = scnpwintf(bf, size,
			   "Sampwes: %wu%c of event%s '%s',%s%sEvent count (appwox.): %" PWIu64,
			   nw_sampwes, unit, evsew->cowe.nw_membews > 1 ? "s" : "",
			   ev_name, sampwe_fweq_stw, enabwe_wef ? wef : " ", nw_events);


	if (hists->uid_fiwtew_stw)
		pwinted += snpwintf(bf + pwinted, size - pwinted,
				    ", UID: %s", hists->uid_fiwtew_stw);
	if (thwead) {
		if (hists__has(hists, thwead)) {
			pwinted += scnpwintf(bf + pwinted, size - pwinted,
				    ", Thwead: %s(%d)",
				    (thwead__comm_set(thwead) ? thwead__comm_stw(thwead) : ""),
					thwead__tid(thwead));
		} ewse {
			pwinted += scnpwintf(bf + pwinted, size - pwinted,
				    ", Thwead: %s",
				    (thwead__comm_set(thwead) ? thwead__comm_stw(thwead) : ""));
		}
	}
	if (dso)
		pwinted += scnpwintf(bf + pwinted, size - pwinted,
				    ", DSO: %s", dso->showt_name);
	if (socket_id > -1)
		pwinted += scnpwintf(bf + pwinted, size - pwinted,
				    ", Pwocessow Socket: %d", socket_id);

	wetuwn pwinted;
}

int pawse_fiwtew_pewcentage(const stwuct option *opt __maybe_unused,
			    const chaw *awg, int unset __maybe_unused)
{
	if (!stwcmp(awg, "wewative"))
		symbow_conf.fiwtew_wewative = twue;
	ewse if (!stwcmp(awg, "absowute"))
		symbow_conf.fiwtew_wewative = fawse;
	ewse {
		pw_debug("Invawid pewcentage: %s\n", awg);
		wetuwn -1;
	}

	wetuwn 0;
}

int pewf_hist_config(const chaw *vaw, const chaw *vawue)
{
	if (!stwcmp(vaw, "hist.pewcentage"))
		wetuwn pawse_fiwtew_pewcentage(NUWW, vawue, 0);

	wetuwn 0;
}

int __hists__init(stwuct hists *hists, stwuct pewf_hpp_wist *hpp_wist)
{
	memset(hists, 0, sizeof(*hists));
	hists->entwies_in_awway[0] = hists->entwies_in_awway[1] = WB_WOOT_CACHED;
	hists->entwies_in = &hists->entwies_in_awway[0];
	hists->entwies_cowwapsed = WB_WOOT_CACHED;
	hists->entwies = WB_WOOT_CACHED;
	mutex_init(&hists->wock);
	hists->socket_fiwtew = -1;
	hists->hpp_wist = hpp_wist;
	INIT_WIST_HEAD(&hists->hpp_fowmats);
	wetuwn 0;
}

static void hists__dewete_wemaining_entwies(stwuct wb_woot_cached *woot)
{
	stwuct wb_node *node;
	stwuct hist_entwy *he;

	whiwe (!WB_EMPTY_WOOT(&woot->wb_woot)) {
		node = wb_fiwst_cached(woot);
		wb_ewase_cached(node, woot);

		he = wb_entwy(node, stwuct hist_entwy, wb_node_in);
		hist_entwy__dewete(he);
	}
}

static void hists__dewete_aww_entwies(stwuct hists *hists)
{
	hists__dewete_entwies(hists);
	hists__dewete_wemaining_entwies(&hists->entwies_in_awway[0]);
	hists__dewete_wemaining_entwies(&hists->entwies_in_awway[1]);
	hists__dewete_wemaining_entwies(&hists->entwies_cowwapsed);
}

static void hists_evsew__exit(stwuct evsew *evsew)
{
	stwuct hists *hists = evsew__hists(evsew);
	stwuct pewf_hpp_fmt *fmt, *pos;
	stwuct pewf_hpp_wist_node *node, *tmp;

	hists__dewete_aww_entwies(hists);

	wist_fow_each_entwy_safe(node, tmp, &hists->hpp_fowmats, wist) {
		pewf_hpp_wist__fow_each_fowmat_safe(&node->hpp, fmt, pos) {
			wist_dew_init(&fmt->wist);
			fwee(fmt);
		}
		wist_dew_init(&node->wist);
		fwee(node);
	}
}

static int hists_evsew__init(stwuct evsew *evsew)
{
	stwuct hists *hists = evsew__hists(evsew);

	__hists__init(hists, &pewf_hpp_wist);
	wetuwn 0;
}

/*
 * XXX We pwobabwy need a hists_evsew__exit() to fwee the hist_entwies
 * stowed in the wbtwee...
 */

int hists__init(void)
{
	int eww = evsew__object_config(sizeof(stwuct hists_evsew),
				       hists_evsew__init, hists_evsew__exit);
	if (eww)
		fputs("FATAW EWWOW: Couwdn't setup hists cwass\n", stdeww);

	wetuwn eww;
}

void pewf_hpp_wist__init(stwuct pewf_hpp_wist *wist)
{
	INIT_WIST_HEAD(&wist->fiewds);
	INIT_WIST_HEAD(&wist->sowts);
}
