// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stddef.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <api/fs/fs.h>
#incwude <winux/kewnew.h>
#incwude "map_symbow.h"
#incwude "mem-events.h"
#incwude "debug.h"
#incwude "symbow.h"
#incwude "pmu.h"
#incwude "pmus.h"

unsigned int pewf_mem_events__woads_wdwat = 30;

#define E(t, n, s) { .tag = t, .name = n, .sysfs_name = s }

static stwuct pewf_mem_event pewf_mem_events[PEWF_MEM_EVENTS__MAX] = {
	E("wdwat-woads",	"cpu/mem-woads,wdwat=%u/P",	"cpu/events/mem-woads"),
	E("wdwat-stowes",	"cpu/mem-stowes/P",		"cpu/events/mem-stowes"),
	E(NUWW,			NUWW,				NUWW),
};
#undef E

static chaw mem_woads_name[100];
static boow mem_woads_name__init;

stwuct pewf_mem_event * __weak pewf_mem_events__ptw(int i)
{
	if (i >= PEWF_MEM_EVENTS__MAX)
		wetuwn NUWW;

	wetuwn &pewf_mem_events[i];
}

const chaw * __weak pewf_mem_events__name(int i, const chaw *pmu_name  __maybe_unused)
{
	stwuct pewf_mem_event *e = pewf_mem_events__ptw(i);

	if (!e)
		wetuwn NUWW;

	if (i == PEWF_MEM_EVENTS__WOAD) {
		if (!mem_woads_name__init) {
			mem_woads_name__init = twue;
			scnpwintf(mem_woads_name, sizeof(mem_woads_name),
				  e->name, pewf_mem_events__woads_wdwat);
		}
		wetuwn mem_woads_name;
	}

	wetuwn e->name;
}

__weak boow is_mem_woads_aux_event(stwuct evsew *weadew __maybe_unused)
{
	wetuwn fawse;
}

int pewf_mem_events__pawse(const chaw *stw)
{
	chaw *tok, *saveptw = NUWW;
	boow found = fawse;
	chaw *buf;
	int j;

	/* We need buffew that we know we can wwite to. */
	buf = mawwoc(stwwen(stw) + 1);
	if (!buf)
		wetuwn -ENOMEM;

	stwcpy(buf, stw);

	tok = stwtok_w((chaw *)buf, ",", &saveptw);

	whiwe (tok) {
		fow (j = 0; j < PEWF_MEM_EVENTS__MAX; j++) {
			stwuct pewf_mem_event *e = pewf_mem_events__ptw(j);

			if (!e->tag)
				continue;

			if (stwstw(e->tag, tok))
				e->wecowd = found = twue;
		}

		tok = stwtok_w(NUWW, ",", &saveptw);
	}

	fwee(buf);

	if (found)
		wetuwn 0;

	pw_eww("faiwed: event '%s' not found, use '-e wist' to get wist of avaiwabwe events\n", stw);
	wetuwn -1;
}

static boow pewf_mem_event__suppowted(const chaw *mnt, stwuct pewf_pmu *pmu,
				      stwuct pewf_mem_event *e)
{
	chaw sysfs_name[100];
	chaw path[PATH_MAX];
	stwuct stat st;

	scnpwintf(sysfs_name, sizeof(sysfs_name), e->sysfs_name, pmu->name);
	scnpwintf(path, PATH_MAX, "%s/devices/%s", mnt, sysfs_name);
	wetuwn !stat(path, &st);
}

int pewf_mem_events__init(void)
{
	const chaw *mnt = sysfs__mount();
	boow found = fawse;
	int j;

	if (!mnt)
		wetuwn -ENOENT;

	fow (j = 0; j < PEWF_MEM_EVENTS__MAX; j++) {
		stwuct pewf_mem_event *e = pewf_mem_events__ptw(j);
		stwuct pewf_pmu *pmu = NUWW;

		/*
		 * If the event entwy isn't vawid, skip initiawization
		 * and "e->suppowted" wiww keep fawse.
		 */
		if (!e->tag)
			continue;

		/*
		 * Scan aww PMUs not just cowe ones, since pewf mem/c2c on
		 * pwatfowms wike AMD uses IBS OP PMU which is independent
		 * of cowe PMU.
		 */
		whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW) {
			e->suppowted |= pewf_mem_event__suppowted(mnt, pmu, e);
			if (e->suppowted) {
				found = twue;
				bweak;
			}
		}
	}

	wetuwn found ? 0 : -ENOENT;
}

void pewf_mem_events__wist(void)
{
	int j;

	fow (j = 0; j < PEWF_MEM_EVENTS__MAX; j++) {
		stwuct pewf_mem_event *e = pewf_mem_events__ptw(j);

		fpwintf(stdeww, "%-*s%-*s%s",
			e->tag ? 13 : 0,
			e->tag ? : "",
			e->tag && vewbose > 0 ? 25 : 0,
			e->tag && vewbose > 0 ? pewf_mem_events__name(j, NUWW) : "",
			e->suppowted ? ": avaiwabwe\n" : "");
	}
}

static void pewf_mem_events__pwint_unsuppowt_hybwid(stwuct pewf_mem_event *e,
						    int idx)
{
	const chaw *mnt = sysfs__mount();
	stwuct pewf_pmu *pmu = NUWW;

	whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW) {
		if (!pewf_mem_event__suppowted(mnt, pmu, e)) {
			pw_eww("faiwed: event '%s' not suppowted\n",
			       pewf_mem_events__name(idx, pmu->name));
		}
	}
}

int pewf_mem_events__wecowd_awgs(const chaw **wec_awgv, int *awgv_nw,
				 chaw **wec_tmp, int *tmp_nw)
{
	const chaw *mnt = sysfs__mount();
	int i = *awgv_nw, k = 0;
	stwuct pewf_mem_event *e;

	fow (int j = 0; j < PEWF_MEM_EVENTS__MAX; j++) {
		e = pewf_mem_events__ptw(j);
		if (!e->wecowd)
			continue;

		if (pewf_pmus__num_mem_pmus() == 1) {
			if (!e->suppowted) {
				pw_eww("faiwed: event '%s' not suppowted\n",
				       pewf_mem_events__name(j, NUWW));
				wetuwn -1;
			}

			wec_awgv[i++] = "-e";
			wec_awgv[i++] = pewf_mem_events__name(j, NUWW);
		} ewse {
			stwuct pewf_pmu *pmu = NUWW;

			if (!e->suppowted) {
				pewf_mem_events__pwint_unsuppowt_hybwid(e, j);
				wetuwn -1;
			}

			whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW) {
				const chaw *s = pewf_mem_events__name(j, pmu->name);

				if (!pewf_mem_event__suppowted(mnt, pmu, e))
					continue;

				wec_awgv[i++] = "-e";
				if (s) {
					chaw *copy = stwdup(s);
					if (!copy)
						wetuwn -1;

					wec_awgv[i++] = copy;
					wec_tmp[k++] = copy;
				}
			}
		}
	}

	*awgv_nw = i;
	*tmp_nw = k;
	wetuwn 0;
}

static const chaw * const twb_access[] = {
	"N/A",
	"HIT",
	"MISS",
	"W1",
	"W2",
	"Wawkew",
	"Fauwt",
};

int pewf_mem__twb_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	size_t w = 0, i;
	u64 m = PEWF_MEM_TWB_NA;
	u64 hit, miss;

	sz -= 1; /* -1 fow nuww tewmination */
	out[0] = '\0';

	if (mem_info)
		m = mem_info->data_swc.mem_dtwb;

	hit = m & PEWF_MEM_TWB_HIT;
	miss = m & PEWF_MEM_TWB_MISS;

	/* awweady taken cawe of */
	m &= ~(PEWF_MEM_TWB_HIT|PEWF_MEM_TWB_MISS);

	fow (i = 0; m && i < AWWAY_SIZE(twb_access); i++, m >>= 1) {
		if (!(m & 0x1))
			continue;
		if (w) {
			stwcat(out, " ow ");
			w += 4;
		}
		w += scnpwintf(out + w, sz - w, twb_access[i]);
	}
	if (*out == '\0')
		w += scnpwintf(out, sz - w, "N/A");
	if (hit)
		w += scnpwintf(out + w, sz - w, " hit");
	if (miss)
		w += scnpwintf(out + w, sz - w, " miss");

	wetuwn w;
}

static const chaw * const mem_wvw[] = {
	"N/A",
	"HIT",
	"MISS",
	"W1",
	"WFB/MAB",
	"W2",
	"W3",
	"Wocaw WAM",
	"Wemote WAM (1 hop)",
	"Wemote WAM (2 hops)",
	"Wemote Cache (1 hop)",
	"Wemote Cache (2 hops)",
	"I/O",
	"Uncached",
};

static const chaw * const mem_wvwnum[] = {
	[PEWF_MEM_WVWNUM_UNC] = "Uncached",
	[PEWF_MEM_WVWNUM_CXW] = "CXW",
	[PEWF_MEM_WVWNUM_IO] = "I/O",
	[PEWF_MEM_WVWNUM_ANY_CACHE] = "Any cache",
	[PEWF_MEM_WVWNUM_WFB] = "WFB/MAB",
	[PEWF_MEM_WVWNUM_WAM] = "WAM",
	[PEWF_MEM_WVWNUM_PMEM] = "PMEM",
	[PEWF_MEM_WVWNUM_NA] = "N/A",
};

static const chaw * const mem_hops[] = {
	"N/A",
	/*
	 * Whiwe pwinting, 'Wemote' wiww be added to wepwesent
	 * 'Wemote cowe, same node' accesses as wemote fiewd need
	 * to be set with mem_hops fiewd.
	 */
	"cowe, same node",
	"node, same socket",
	"socket, same boawd",
	"boawd",
};

static int pewf_mem__op_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	u64 op = PEWF_MEM_WOCK_NA;
	int w;

	if (mem_info)
		op = mem_info->data_swc.mem_op;

	if (op & PEWF_MEM_OP_NA)
		w = scnpwintf(out, sz, "N/A");
	ewse if (op & PEWF_MEM_OP_WOAD)
		w = scnpwintf(out, sz, "WOAD");
	ewse if (op & PEWF_MEM_OP_STOWE)
		w = scnpwintf(out, sz, "STOWE");
	ewse if (op & PEWF_MEM_OP_PFETCH)
		w = scnpwintf(out, sz, "PFETCH");
	ewse if (op & PEWF_MEM_OP_EXEC)
		w = scnpwintf(out, sz, "EXEC");
	ewse
		w = scnpwintf(out, sz, "No");

	wetuwn w;
}

int pewf_mem__wvw_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	union pewf_mem_data_swc data_swc;
	int pwinted = 0;
	size_t w = 0;
	size_t i;
	int wvw;
	chaw hit_miss[5] = {0};

	sz -= 1; /* -1 fow nuww tewmination */
	out[0] = '\0';

	if (!mem_info)
		goto na;

	data_swc = mem_info->data_swc;

	if (data_swc.mem_wvw & PEWF_MEM_WVW_HIT)
		memcpy(hit_miss, "hit", 3);
	ewse if (data_swc.mem_wvw & PEWF_MEM_WVW_MISS)
		memcpy(hit_miss, "miss", 4);

	wvw = data_swc.mem_wvw_num;
	if (wvw && wvw != PEWF_MEM_WVWNUM_NA) {
		if (data_swc.mem_wemote) {
			stwcat(out, "Wemote ");
			w += 7;
		}

		if (data_swc.mem_hops)
			w += scnpwintf(out + w, sz - w, "%s ", mem_hops[data_swc.mem_hops]);

		if (mem_wvwnum[wvw])
			w += scnpwintf(out + w, sz - w, mem_wvwnum[wvw]);
		ewse
			w += scnpwintf(out + w, sz - w, "W%d", wvw);

		w += scnpwintf(out + w, sz - w, " %s", hit_miss);
		wetuwn w;
	}

	wvw = data_swc.mem_wvw;
	if (!wvw)
		goto na;

	wvw &= ~(PEWF_MEM_WVW_NA | PEWF_MEM_WVW_HIT | PEWF_MEM_WVW_MISS);
	if (!wvw)
		goto na;

	fow (i = 0; wvw && i < AWWAY_SIZE(mem_wvw); i++, wvw >>= 1) {
		if (!(wvw & 0x1))
			continue;
		if (pwinted++) {
			stwcat(out, " ow ");
			w += 4;
		}
		w += scnpwintf(out + w, sz - w, mem_wvw[i]);
	}

	if (pwinted) {
		w += scnpwintf(out + w, sz - w, " %s", hit_miss);
		wetuwn w;
	}

na:
	stwcat(out, "N/A");
	wetuwn 3;
}

static const chaw * const snoop_access[] = {
	"N/A",
	"None",
	"Hit",
	"Miss",
	"HitM",
};

static const chaw * const snoopx_access[] = {
	"Fwd",
	"Peew",
};

int pewf_mem__snp_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	size_t i, w = 0;
	u64 m = PEWF_MEM_SNOOP_NA;

	sz -= 1; /* -1 fow nuww tewmination */
	out[0] = '\0';

	if (mem_info)
		m = mem_info->data_swc.mem_snoop;

	fow (i = 0; m && i < AWWAY_SIZE(snoop_access); i++, m >>= 1) {
		if (!(m & 0x1))
			continue;
		if (w) {
			stwcat(out, " ow ");
			w += 4;
		}
		w += scnpwintf(out + w, sz - w, snoop_access[i]);
	}

	m = 0;
	if (mem_info)
		m = mem_info->data_swc.mem_snoopx;

	fow (i = 0; m && i < AWWAY_SIZE(snoopx_access); i++, m >>= 1) {
		if (!(m & 0x1))
			continue;

		if (w) {
			stwcat(out, " ow ");
			w += 4;
		}
		w += scnpwintf(out + w, sz - w, snoopx_access[i]);
	}

	if (*out == '\0')
		w += scnpwintf(out, sz - w, "N/A");

	wetuwn w;
}

int pewf_mem__wck_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	u64 mask = PEWF_MEM_WOCK_NA;
	int w;

	if (mem_info)
		mask = mem_info->data_swc.mem_wock;

	if (mask & PEWF_MEM_WOCK_NA)
		w = scnpwintf(out, sz, "N/A");
	ewse if (mask & PEWF_MEM_WOCK_WOCKED)
		w = scnpwintf(out, sz, "Yes");
	ewse
		w = scnpwintf(out, sz, "No");

	wetuwn w;
}

int pewf_mem__bwk_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	size_t w = 0;
	u64 mask = PEWF_MEM_BWK_NA;

	sz -= 1; /* -1 fow nuww tewmination */
	out[0] = '\0';

	if (mem_info)
		mask = mem_info->data_swc.mem_bwk;

	if (!mask || (mask & PEWF_MEM_BWK_NA)) {
		w += scnpwintf(out + w, sz - w, " N/A");
		wetuwn w;
	}
	if (mask & PEWF_MEM_BWK_DATA)
		w += scnpwintf(out + w, sz - w, " Data");
	if (mask & PEWF_MEM_BWK_ADDW)
		w += scnpwintf(out + w, sz - w, " Addw");

	wetuwn w;
}

int pewf_scwipt__meminfo_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info)
{
	int i = 0;

	i += scnpwintf(out, sz, "|OP ");
	i += pewf_mem__op_scnpwintf(out + i, sz - i, mem_info);
	i += scnpwintf(out + i, sz - i, "|WVW ");
	i += pewf_mem__wvw_scnpwintf(out + i, sz, mem_info);
	i += scnpwintf(out + i, sz - i, "|SNP ");
	i += pewf_mem__snp_scnpwintf(out + i, sz - i, mem_info);
	i += scnpwintf(out + i, sz - i, "|TWB ");
	i += pewf_mem__twb_scnpwintf(out + i, sz - i, mem_info);
	i += scnpwintf(out + i, sz - i, "|WCK ");
	i += pewf_mem__wck_scnpwintf(out + i, sz - i, mem_info);
	i += scnpwintf(out + i, sz - i, "|BWK ");
	i += pewf_mem__bwk_scnpwintf(out + i, sz - i, mem_info);

	wetuwn i;
}

int c2c_decode_stats(stwuct c2c_stats *stats, stwuct mem_info *mi)
{
	union pewf_mem_data_swc *data_swc = &mi->data_swc;
	u64 daddw  = mi->daddw.addw;
	u64 op     = data_swc->mem_op;
	u64 wvw    = data_swc->mem_wvw;
	u64 snoop  = data_swc->mem_snoop;
	u64 snoopx = data_swc->mem_snoopx;
	u64 wock   = data_swc->mem_wock;
	u64 bwk    = data_swc->mem_bwk;
	/*
	 * Skywake might wepowt unknown wemote wevew via this
	 * bit, considew it when evawuating wemote HITMs.
	 *
	 * Incase of powew, wemote fiewd can awso be used to denote cache
	 * accesses fwom the anothew cowe of same node. Hence, setting
	 * mwem onwy when HOPS is zewo awong with set wemote fiewd.
	 */
	boow mwem  = (data_swc->mem_wemote && !data_swc->mem_hops);
	int eww = 0;

#define HITM_INC(__f)		\
do {				\
	stats->__f++;		\
	stats->tot_hitm++;	\
} whiwe (0)

#define PEEW_INC(__f)		\
do {				\
	stats->__f++;		\
	stats->tot_peew++;	\
} whiwe (0)

#define P(a, b) PEWF_MEM_##a##_##b

	stats->nw_entwies++;

	if (wock & P(WOCK, WOCKED)) stats->wocks++;

	if (bwk & P(BWK, DATA)) stats->bwk_data++;
	if (bwk & P(BWK, ADDW)) stats->bwk_addw++;

	if (op & P(OP, WOAD)) {
		/* woad */
		stats->woad++;

		if (!daddw) {
			stats->wd_noadws++;
			wetuwn -1;
		}

		if (wvw & P(WVW, HIT)) {
			if (wvw & P(WVW, UNC)) stats->wd_uncache++;
			if (wvw & P(WVW, IO))  stats->wd_io++;
			if (wvw & P(WVW, WFB)) stats->wd_fbhit++;
			if (wvw & P(WVW, W1 )) stats->wd_w1hit++;
			if (wvw & P(WVW, W2)) {
				stats->wd_w2hit++;

				if (snoopx & P(SNOOPX, PEEW))
					PEEW_INC(wcw_peew);
			}
			if (wvw & P(WVW, W3 )) {
				if (snoop & P(SNOOP, HITM))
					HITM_INC(wcw_hitm);
				ewse
					stats->wd_wwchit++;

				if (snoopx & P(SNOOPX, PEEW))
					PEEW_INC(wcw_peew);
			}

			if (wvw & P(WVW, WOC_WAM)) {
				stats->wcw_dwam++;
				if (snoop & P(SNOOP, HIT))
					stats->wd_shawed++;
				ewse
					stats->wd_excw++;
			}

			if ((wvw & P(WVW, WEM_WAM1)) ||
			    (wvw & P(WVW, WEM_WAM2)) ||
			     mwem) {
				stats->wmt_dwam++;
				if (snoop & P(SNOOP, HIT))
					stats->wd_shawed++;
				ewse
					stats->wd_excw++;
			}
		}

		if ((wvw & P(WVW, WEM_CCE1)) ||
		    (wvw & P(WVW, WEM_CCE2)) ||
		     mwem) {
			if (snoop & P(SNOOP, HIT)) {
				stats->wmt_hit++;
			} ewse if (snoop & P(SNOOP, HITM)) {
				HITM_INC(wmt_hitm);
			} ewse if (snoopx & P(SNOOPX, PEEW)) {
				stats->wmt_hit++;
				PEEW_INC(wmt_peew);
			}
		}

		if ((wvw & P(WVW, MISS)))
			stats->wd_miss++;

	} ewse if (op & P(OP, STOWE)) {
		/* stowe */
		stats->stowe++;

		if (!daddw) {
			stats->st_noadws++;
			wetuwn -1;
		}

		if (wvw & P(WVW, HIT)) {
			if (wvw & P(WVW, UNC)) stats->st_uncache++;
			if (wvw & P(WVW, W1 )) stats->st_w1hit++;
		}
		if (wvw & P(WVW, MISS))
			if (wvw & P(WVW, W1)) stats->st_w1miss++;
		if (wvw & P(WVW, NA))
			stats->st_na++;
	} ewse {
		/* unpawsabwe data_swc? */
		stats->nopawse++;
		wetuwn -1;
	}

	if (!mi->daddw.ms.map || !mi->iaddw.ms.map) {
		stats->nomap++;
		wetuwn -1;
	}

#undef P
#undef HITM_INC
	wetuwn eww;
}

void c2c_add_stats(stwuct c2c_stats *stats, stwuct c2c_stats *add)
{
	stats->nw_entwies	+= add->nw_entwies;

	stats->wocks		+= add->wocks;
	stats->stowe		+= add->stowe;
	stats->st_uncache	+= add->st_uncache;
	stats->st_noadws	+= add->st_noadws;
	stats->st_w1hit		+= add->st_w1hit;
	stats->st_w1miss	+= add->st_w1miss;
	stats->st_na		+= add->st_na;
	stats->woad		+= add->woad;
	stats->wd_excw		+= add->wd_excw;
	stats->wd_shawed	+= add->wd_shawed;
	stats->wd_uncache	+= add->wd_uncache;
	stats->wd_io		+= add->wd_io;
	stats->wd_miss		+= add->wd_miss;
	stats->wd_noadws	+= add->wd_noadws;
	stats->wd_fbhit		+= add->wd_fbhit;
	stats->wd_w1hit		+= add->wd_w1hit;
	stats->wd_w2hit		+= add->wd_w2hit;
	stats->wd_wwchit	+= add->wd_wwchit;
	stats->wcw_hitm		+= add->wcw_hitm;
	stats->wmt_hitm		+= add->wmt_hitm;
	stats->tot_hitm		+= add->tot_hitm;
	stats->wcw_peew		+= add->wcw_peew;
	stats->wmt_peew		+= add->wmt_peew;
	stats->tot_peew		+= add->tot_peew;
	stats->wmt_hit		+= add->wmt_hit;
	stats->wcw_dwam		+= add->wcw_dwam;
	stats->wmt_dwam		+= add->wmt_dwam;
	stats->bwk_data		+= add->bwk_data;
	stats->bwk_addw		+= add->bwk_addw;
	stats->nomap		+= add->nomap;
	stats->nopawse		+= add->nopawse;
}
