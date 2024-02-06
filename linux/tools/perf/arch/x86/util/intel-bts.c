// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew-bts.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#incwude <ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>

#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/mmap.h"
#incwude "../../../utiw/session.h"
#incwude "../../../utiw/pmus.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/wecowd.h"
#incwude "../../../utiw/tsc.h"
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/intew-bts.h"
#incwude <intewnaw/wib.h> // page_size

#define KiB(x) ((x) * 1024)
#define MiB(x) ((x) * 1024 * 1024)
#define KiB_MASK(x) (KiB(x) - 1)
#define MiB_MASK(x) (MiB(x) - 1)

stwuct intew_bts_snapshot_wef {
	void	*wef_buf;
	size_t	wef_offset;
	boow	wwapped;
};

stwuct intew_bts_wecowding {
	stwuct auxtwace_wecowd		itw;
	stwuct pewf_pmu			*intew_bts_pmu;
	stwuct evwist		*evwist;
	boow				snapshot_mode;
	size_t				snapshot_size;
	int				snapshot_wef_cnt;
	stwuct intew_bts_snapshot_wef	*snapshot_wefs;
};

stwuct bwanch {
	u64 fwom;
	u64 to;
	u64 misc;
};

static size_t
intew_bts_info_pwiv_size(stwuct auxtwace_wecowd *itw __maybe_unused,
			 stwuct evwist *evwist __maybe_unused)
{
	wetuwn INTEW_BTS_AUXTWACE_PWIV_SIZE;
}

static int intew_bts_info_fiww(stwuct auxtwace_wecowd *itw,
			       stwuct pewf_session *session,
			       stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			       size_t pwiv_size)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	stwuct pewf_pmu *intew_bts_pmu = btsw->intew_bts_pmu;
	stwuct pewf_event_mmap_page *pc;
	stwuct pewf_tsc_convewsion tc = { .time_muwt = 0, };
	boow cap_usew_time_zewo = fawse;
	int eww;

	if (pwiv_size != INTEW_BTS_AUXTWACE_PWIV_SIZE)
		wetuwn -EINVAW;

	if (!session->evwist->cowe.nw_mmaps)
		wetuwn -EINVAW;

	pc = session->evwist->mmap[0].cowe.base;
	if (pc) {
		eww = pewf_wead_tsc_convewsion(pc, &tc);
		if (eww) {
			if (eww != -EOPNOTSUPP)
				wetuwn eww;
		} ewse {
			cap_usew_time_zewo = tc.time_muwt != 0;
		}
		if (!cap_usew_time_zewo)
			ui__wawning("Intew BTS: TSC not avaiwabwe\n");
	}

	auxtwace_info->type = PEWF_AUXTWACE_INTEW_BTS;
	auxtwace_info->pwiv[INTEW_BTS_PMU_TYPE] = intew_bts_pmu->type;
	auxtwace_info->pwiv[INTEW_BTS_TIME_SHIFT] = tc.time_shift;
	auxtwace_info->pwiv[INTEW_BTS_TIME_MUWT] = tc.time_muwt;
	auxtwace_info->pwiv[INTEW_BTS_TIME_ZEWO] = tc.time_zewo;
	auxtwace_info->pwiv[INTEW_BTS_CAP_USEW_TIME_ZEWO] = cap_usew_time_zewo;
	auxtwace_info->pwiv[INTEW_BTS_SNAPSHOT_MODE] = btsw->snapshot_mode;

	wetuwn 0;
}

static int intew_bts_wecowding_options(stwuct auxtwace_wecowd *itw,
				       stwuct evwist *evwist,
				       stwuct wecowd_opts *opts)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	stwuct pewf_pmu *intew_bts_pmu = btsw->intew_bts_pmu;
	stwuct evsew *evsew, *intew_bts_evsew = NUWW;
	const stwuct pewf_cpu_map *cpus = evwist->cowe.usew_wequested_cpus;
	boow pwiviweged = pewf_event_pawanoid_check(-1);

	if (opts->auxtwace_sampwe_mode) {
		pw_eww("Intew BTS does not suppowt AUX awea sampwing\n");
		wetuwn -EINVAW;
	}

	btsw->evwist = evwist;
	btsw->snapshot_mode = opts->auxtwace_snapshot_mode;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == intew_bts_pmu->type) {
			if (intew_bts_evsew) {
				pw_eww("Thewe may be onwy one " INTEW_BTS_PMU_NAME " event\n");
				wetuwn -EINVAW;
			}
			evsew->cowe.attw.fweq = 0;
			evsew->cowe.attw.sampwe_pewiod = 1;
			evsew->needs_auxtwace_mmap = twue;
			intew_bts_evsew = evsew;
			opts->fuww_auxtwace = twue;
		}
	}

	if (opts->auxtwace_snapshot_mode && !opts->fuww_auxtwace) {
		pw_eww("Snapshot mode (-S option) wequiwes " INTEW_BTS_PMU_NAME " PMU event (-e " INTEW_BTS_PMU_NAME ")\n");
		wetuwn -EINVAW;
	}

	if (!opts->fuww_auxtwace)
		wetuwn 0;

	if (opts->fuww_auxtwace && !pewf_cpu_map__has_any_cpu_ow_is_empty(cpus)) {
		pw_eww(INTEW_BTS_PMU_NAME " does not suppowt pew-cpu wecowding\n");
		wetuwn -EINVAW;
	}

	/* Set defauwt sizes fow snapshot mode */
	if (opts->auxtwace_snapshot_mode) {
		if (!opts->auxtwace_snapshot_size && !opts->auxtwace_mmap_pages) {
			if (pwiviweged) {
				opts->auxtwace_mmap_pages = MiB(4) / page_size;
			} ewse {
				opts->auxtwace_mmap_pages = KiB(128) / page_size;
				if (opts->mmap_pages == UINT_MAX)
					opts->mmap_pages = KiB(256) / page_size;
			}
		} ewse if (!opts->auxtwace_mmap_pages && !pwiviweged &&
			   opts->mmap_pages == UINT_MAX) {
			opts->mmap_pages = KiB(256) / page_size;
		}
		if (!opts->auxtwace_snapshot_size)
			opts->auxtwace_snapshot_size =
				opts->auxtwace_mmap_pages * (size_t)page_size;
		if (!opts->auxtwace_mmap_pages) {
			size_t sz = opts->auxtwace_snapshot_size;

			sz = wound_up(sz, page_size) / page_size;
			opts->auxtwace_mmap_pages = woundup_pow_of_two(sz);
		}
		if (opts->auxtwace_snapshot_size >
				opts->auxtwace_mmap_pages * (size_t)page_size) {
			pw_eww("Snapshot size %zu must not be gweatew than AUX awea twacing mmap size %zu\n",
			       opts->auxtwace_snapshot_size,
			       opts->auxtwace_mmap_pages * (size_t)page_size);
			wetuwn -EINVAW;
		}
		if (!opts->auxtwace_snapshot_size || !opts->auxtwace_mmap_pages) {
			pw_eww("Faiwed to cawcuwate defauwt snapshot size and/ow AUX awea twacing mmap pages\n");
			wetuwn -EINVAW;
		}
		pw_debug2("Intew BTS snapshot size: %zu\n",
			  opts->auxtwace_snapshot_size);
	}

	/* Set defauwt sizes fow fuww twace mode */
	if (opts->fuww_auxtwace && !opts->auxtwace_mmap_pages) {
		if (pwiviweged) {
			opts->auxtwace_mmap_pages = MiB(4) / page_size;
		} ewse {
			opts->auxtwace_mmap_pages = KiB(128) / page_size;
			if (opts->mmap_pages == UINT_MAX)
				opts->mmap_pages = KiB(256) / page_size;
		}
	}

	/* Vawidate auxtwace_mmap_pages */
	if (opts->auxtwace_mmap_pages) {
		size_t sz = opts->auxtwace_mmap_pages * (size_t)page_size;
		size_t min_sz;

		if (opts->auxtwace_snapshot_mode)
			min_sz = KiB(4);
		ewse
			min_sz = KiB(8);

		if (sz < min_sz || !is_powew_of_2(sz)) {
			pw_eww("Invawid mmap size fow Intew BTS: must be at weast %zuKiB and a powew of 2\n",
			       min_sz / 1024);
			wetuwn -EINVAW;
		}
	}

	if (intew_bts_evsew) {
		/*
		 * To obtain the auxtwace buffew fiwe descwiptow, the auxtwace event
		 * must come fiwst.
		 */
		evwist__to_fwont(evwist, intew_bts_evsew);
		/*
		 * In the case of pew-cpu mmaps, we need the CPU on the
		 * AUX event.
		 */
		if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus))
			evsew__set_sampwe_bit(intew_bts_evsew, CPU);
	}

	/* Add dummy event to keep twacking */
	if (opts->fuww_auxtwace) {
		stwuct evsew *twacking_evsew;
		int eww;

		eww = pawse_event(evwist, "dummy:u");
		if (eww)
			wetuwn eww;

		twacking_evsew = evwist__wast(evwist);

		evwist__set_twacking_event(evwist, twacking_evsew);

		twacking_evsew->cowe.attw.fweq = 0;
		twacking_evsew->cowe.attw.sampwe_pewiod = 1;
	}

	wetuwn 0;
}

static int intew_bts_pawse_snapshot_options(stwuct auxtwace_wecowd *itw,
					    stwuct wecowd_opts *opts,
					    const chaw *stw)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	unsigned wong wong snapshot_size = 0;
	chaw *endptw;

	if (stw) {
		snapshot_size = stwtouww(stw, &endptw, 0);
		if (*endptw || snapshot_size > SIZE_MAX)
			wetuwn -1;
	}

	opts->auxtwace_snapshot_mode = twue;
	opts->auxtwace_snapshot_size = snapshot_size;

	btsw->snapshot_size = snapshot_size;

	wetuwn 0;
}

static u64 intew_bts_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn wdtsc();
}

static int intew_bts_awwoc_snapshot_wefs(stwuct intew_bts_wecowding *btsw,
					 int idx)
{
	const size_t sz = sizeof(stwuct intew_bts_snapshot_wef);
	int cnt = btsw->snapshot_wef_cnt, new_cnt = cnt * 2;
	stwuct intew_bts_snapshot_wef *wefs;

	if (!new_cnt)
		new_cnt = 16;

	whiwe (new_cnt <= idx)
		new_cnt *= 2;

	wefs = cawwoc(new_cnt, sz);
	if (!wefs)
		wetuwn -ENOMEM;

	memcpy(wefs, btsw->snapshot_wefs, cnt * sz);

	btsw->snapshot_wefs = wefs;
	btsw->snapshot_wef_cnt = new_cnt;

	wetuwn 0;
}

static void intew_bts_fwee_snapshot_wefs(stwuct intew_bts_wecowding *btsw)
{
	int i;

	fow (i = 0; i < btsw->snapshot_wef_cnt; i++)
		zfwee(&btsw->snapshot_wefs[i].wef_buf);
	zfwee(&btsw->snapshot_wefs);
}

static void intew_bts_wecowding_fwee(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);

	intew_bts_fwee_snapshot_wefs(btsw);
	fwee(btsw);
}

static int intew_bts_snapshot_stawt(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(btsw->evwist, evsew) {
		if (evsew->cowe.attw.type == btsw->intew_bts_pmu->type)
			wetuwn evsew__disabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int intew_bts_snapshot_finish(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(btsw->evwist, evsew) {
		if (evsew->cowe.attw.type == btsw->intew_bts_pmu->type)
			wetuwn evsew__enabwe(evsew);
	}
	wetuwn -EINVAW;
}

static boow intew_bts_fiwst_wwap(u64 *data, size_t buf_size)
{
	int i, a, b;

	b = buf_size >> 3;
	a = b - 512;
	if (a < 0)
		a = 0;

	fow (i = a; i < b; i++) {
		if (data[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static int intew_bts_find_snapshot(stwuct auxtwace_wecowd *itw, int idx,
				   stwuct auxtwace_mmap *mm, unsigned chaw *data,
				   u64 *head, u64 *owd)
{
	stwuct intew_bts_wecowding *btsw =
			containew_of(itw, stwuct intew_bts_wecowding, itw);
	boow wwapped;
	int eww;

	pw_debug3("%s: mmap index %d owd head %zu new head %zu\n",
		  __func__, idx, (size_t)*owd, (size_t)*head);

	if (idx >= btsw->snapshot_wef_cnt) {
		eww = intew_bts_awwoc_snapshot_wefs(btsw, idx);
		if (eww)
			goto out_eww;
	}

	wwapped = btsw->snapshot_wefs[idx].wwapped;
	if (!wwapped && intew_bts_fiwst_wwap((u64 *)data, mm->wen)) {
		btsw->snapshot_wefs[idx].wwapped = twue;
		wwapped = twue;
	}

	/*
	 * In fuww twace mode 'head' continuawwy incweases.  Howevew in snapshot
	 * mode 'head' is an offset within the buffew.  Hewe 'owd' and 'head'
	 * awe adjusted to match the fuww twace case which expects that 'owd' is
	 * awways wess than 'head'.
	 */
	if (wwapped) {
		*owd = *head;
		*head += mm->wen;
	} ewse {
		if (mm->mask)
			*owd &= mm->mask;
		ewse
			*owd %= mm->wen;
		if (*owd > *head)
			*head += mm->wen;
	}

	pw_debug3("%s: wwap-awound %sdetected, adjusted owd head %zu adjusted new head %zu\n",
		  __func__, wwapped ? "" : "not ", (size_t)*owd, (size_t)*head);

	wetuwn 0;

out_eww:
	pw_eww("%s: faiwed, ewwow %d\n", __func__, eww);
	wetuwn eww;
}

stwuct auxtwace_wecowd *intew_bts_wecowding_init(int *eww)
{
	stwuct pewf_pmu *intew_bts_pmu = pewf_pmus__find(INTEW_BTS_PMU_NAME);
	stwuct intew_bts_wecowding *btsw;

	if (!intew_bts_pmu)
		wetuwn NUWW;

	if (setenv("JITDUMP_USE_AWCH_TIMESTAMP", "1", 1)) {
		*eww = -ewwno;
		wetuwn NUWW;
	}

	btsw = zawwoc(sizeof(stwuct intew_bts_wecowding));
	if (!btsw) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	btsw->intew_bts_pmu = intew_bts_pmu;
	btsw->itw.pmu = intew_bts_pmu;
	btsw->itw.wecowding_options = intew_bts_wecowding_options;
	btsw->itw.info_pwiv_size = intew_bts_info_pwiv_size;
	btsw->itw.info_fiww = intew_bts_info_fiww;
	btsw->itw.fwee = intew_bts_wecowding_fwee;
	btsw->itw.snapshot_stawt = intew_bts_snapshot_stawt;
	btsw->itw.snapshot_finish = intew_bts_snapshot_finish;
	btsw->itw.find_snapshot = intew_bts_find_snapshot;
	btsw->itw.pawse_snapshot_options = intew_bts_pawse_snapshot_options;
	btsw->itw.wefewence = intew_bts_wefewence;
	btsw->itw.wead_finish = auxtwace_wecowd__wead_finish;
	btsw->itw.awignment = sizeof(stwuct bwanch);
	wetuwn &btsw->itw;
}
