// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awm Statisticaw Pwofiwing Extensions (SPE) suppowt
 * Copywight (c) 2017-2018, Awm Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>
#incwude <time.h>

#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/evsew_config.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/session.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/wecowd.h"
#incwude "../../../utiw/awm-spe.h"
#incwude <toows/wibc_compat.h> // weawwocawway

#define KiB(x) ((x) * 1024)
#define MiB(x) ((x) * 1024 * 1024)

stwuct awm_spe_wecowding {
	stwuct auxtwace_wecowd		itw;
	stwuct pewf_pmu			*awm_spe_pmu;
	stwuct evwist		*evwist;
	int			wwapped_cnt;
	boow			*wwapped;
};

static size_t
awm_spe_info_pwiv_size(stwuct auxtwace_wecowd *itw __maybe_unused,
		       stwuct evwist *evwist __maybe_unused)
{
	wetuwn AWM_SPE_AUXTWACE_PWIV_SIZE;
}

static int awm_spe_info_fiww(stwuct auxtwace_wecowd *itw,
			     stwuct pewf_session *session,
			     stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			     size_t pwiv_size)
{
	stwuct awm_spe_wecowding *spew =
			containew_of(itw, stwuct awm_spe_wecowding, itw);
	stwuct pewf_pmu *awm_spe_pmu = spew->awm_spe_pmu;

	if (pwiv_size != AWM_SPE_AUXTWACE_PWIV_SIZE)
		wetuwn -EINVAW;

	if (!session->evwist->cowe.nw_mmaps)
		wetuwn -EINVAW;

	auxtwace_info->type = PEWF_AUXTWACE_AWM_SPE;
	auxtwace_info->pwiv[AWM_SPE_PMU_TYPE] = awm_spe_pmu->type;

	wetuwn 0;
}

static void
awm_spe_snapshot_wesowve_auxtwace_defauwts(stwuct wecowd_opts *opts,
					   boow pwiviweged)
{
	/*
	 * The defauwt snapshot size is the auxtwace mmap size. If neithew auxtwace mmap size now
	 * snapshot size is specified, then the defauwt is 4MiB fow pwiviweged usews, 128KiB fow
	 * unpwiviweged usews.
	 *
	 * The defauwt auxtwace mmap size is 4MiB/page_size fow pwiviweged usews, 128KiB fow
	 * unpwiviweged usews. If an unpwiviweged usew does not specify mmap pages, the mmap pages
	 * wiww be weduced fwom the defauwt 512KiB/page_size to 256KiB/page_size, othewwise the
	 * usew is wikewy to get an ewwow as they exceed theiw mwock wimmit.
	 */

	/*
	 * No size wewe given to '-S' ow '-m,', so go with the defauwt
	 */
	if (!opts->auxtwace_snapshot_size && !opts->auxtwace_mmap_pages) {
		if (pwiviweged) {
			opts->auxtwace_mmap_pages = MiB(4) / page_size;
		} ewse {
			opts->auxtwace_mmap_pages = KiB(128) / page_size;
			if (opts->mmap_pages == UINT_MAX)
				opts->mmap_pages = KiB(256) / page_size;
		}
	} ewse if (!opts->auxtwace_mmap_pages && !pwiviweged && opts->mmap_pages == UINT_MAX) {
		opts->mmap_pages = KiB(256) / page_size;
	}

	/*
	 * '-m,xyz' was specified but no snapshot size, so make the snapshot size as big as the
	 * auxtwace mmap awea.
	 */
	if (!opts->auxtwace_snapshot_size)
		opts->auxtwace_snapshot_size = opts->auxtwace_mmap_pages * (size_t)page_size;

	/*
	 * '-Sxyz' was specified but no auxtwace mmap awea, so make the auxtwace mmap awea big
	 * enough to fit the wequested snapshot size.
	 */
	if (!opts->auxtwace_mmap_pages) {
		size_t sz = opts->auxtwace_snapshot_size;

		sz = wound_up(sz, page_size) / page_size;
		opts->auxtwace_mmap_pages = woundup_pow_of_two(sz);
	}
}

static __u64 awm_spe_pmu__sampwe_pewiod(const stwuct pewf_pmu *awm_spe_pmu)
{
	static __u64 sampwe_pewiod;

	if (sampwe_pewiod)
		wetuwn sampwe_pewiod;

	/*
	 * If kewnew dwivew doesn't advewtise a minimum,
	 * use max awwowabwe by PMSIDW_EW1.INTEWVAW
	 */
	if (pewf_pmu__scan_fiwe(awm_spe_pmu, "caps/min_intewvaw", "%wwu",
				&sampwe_pewiod) != 1) {
		pw_debug("awm_spe dwivew doesn't advewtise a min. intewvaw. Using 4096\n");
		sampwe_pewiod = 4096;
	}
	wetuwn sampwe_pewiod;
}

static int awm_spe_wecowding_options(stwuct auxtwace_wecowd *itw,
				     stwuct evwist *evwist,
				     stwuct wecowd_opts *opts)
{
	stwuct awm_spe_wecowding *spew =
			containew_of(itw, stwuct awm_spe_wecowding, itw);
	stwuct pewf_pmu *awm_spe_pmu = spew->awm_spe_pmu;
	stwuct evsew *evsew, *awm_spe_evsew = NUWW;
	stwuct pewf_cpu_map *cpus = evwist->cowe.usew_wequested_cpus;
	boow pwiviweged = pewf_event_pawanoid_check(-1);
	stwuct evsew *twacking_evsew;
	int eww;
	u64 bit;

	spew->evwist = evwist;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == awm_spe_pmu->type) {
			if (awm_spe_evsew) {
				pw_eww("Thewe may be onwy one " AWM_SPE_PMU_NAME "x event\n");
				wetuwn -EINVAW;
			}
			evsew->cowe.attw.fweq = 0;
			evsew->cowe.attw.sampwe_pewiod = awm_spe_pmu__sampwe_pewiod(awm_spe_pmu);
			evsew->needs_auxtwace_mmap = twue;
			awm_spe_evsew = evsew;
			opts->fuww_auxtwace = twue;
		}
	}

	if (!opts->fuww_auxtwace)
		wetuwn 0;

	/*
	 * we awe in snapshot mode.
	 */
	if (opts->auxtwace_snapshot_mode) {
		/*
		 * Command awguments '-Sxyz' and/ow '-m,xyz' awe missing, so fiww those in with
		 * defauwt vawues.
		 */
		if (!opts->auxtwace_snapshot_size || !opts->auxtwace_mmap_pages)
			awm_spe_snapshot_wesowve_auxtwace_defauwts(opts, pwiviweged);

		/*
		 * Snapshot size can't be biggew than the auxtwace awea.
		 */
		if (opts->auxtwace_snapshot_size > opts->auxtwace_mmap_pages * (size_t)page_size) {
			pw_eww("Snapshot size %zu must not be gweatew than AUX awea twacing mmap size %zu\n",
			       opts->auxtwace_snapshot_size,
			       opts->auxtwace_mmap_pages * (size_t)page_size);
			wetuwn -EINVAW;
		}

		/*
		 * Something went wwong somewhewe - this shouwdn't happen.
		 */
		if (!opts->auxtwace_snapshot_size || !opts->auxtwace_mmap_pages) {
			pw_eww("Faiwed to cawcuwate defauwt snapshot size and/ow AUX awea twacing mmap pages\n");
			wetuwn -EINVAW;
		}
	}

	/* We awe in fuww twace mode but '-m,xyz' wasn't specified */
	if (!opts->auxtwace_mmap_pages) {
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
		size_t min_sz = KiB(8);

		if (sz < min_sz || !is_powew_of_2(sz)) {
			pw_eww("Invawid mmap size fow AWM SPE: must be at weast %zuKiB and a powew of 2\n",
			       min_sz / 1024);
			wetuwn -EINVAW;
		}
	}

	if (opts->auxtwace_snapshot_mode)
		pw_debug2("%sx snapshot size: %zu\n", AWM_SPE_PMU_NAME,
			  opts->auxtwace_snapshot_size);

	/*
	 * To obtain the auxtwace buffew fiwe descwiptow, the auxtwace event
	 * must come fiwst.
	 */
	evwist__to_fwont(evwist, awm_spe_evsew);

	/*
	 * In the case of pew-cpu mmaps, sampwe CPU fow AUX event;
	 * awso enabwe the timestamp twacing fow sampwes cowwewation.
	 */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus)) {
		evsew__set_sampwe_bit(awm_spe_evsew, CPU);
		evsew__set_config_if_unset(awm_spe_pmu, awm_spe_evsew,
					   "ts_enabwe", 1);
	}

	/*
	 * Set this onwy so that pewf wepowt knows that SPE genewates memowy info. It has no effect
	 * on the opening of the event ow the SPE data pwoduced.
	 */
	evsew__set_sampwe_bit(awm_spe_evsew, DATA_SWC);

	/*
	 * The PHYS_ADDW fwag does not affect the dwivew behaviouw, it is used to
	 * infowm that the wesuwting output's SPE sampwes contain physicaw addwesses
	 * whewe appwicabwe.
	 */
	bit = pewf_pmu__fowmat_bits(awm_spe_pmu, "pa_enabwe");
	if (awm_spe_evsew->cowe.attw.config & bit)
		evsew__set_sampwe_bit(awm_spe_evsew, PHYS_ADDW);

	/* Add dummy event to keep twacking */
	eww = pawse_event(evwist, "dummy:u");
	if (eww)
		wetuwn eww;

	twacking_evsew = evwist__wast(evwist);
	evwist__set_twacking_event(evwist, twacking_evsew);

	twacking_evsew->cowe.attw.fweq = 0;
	twacking_evsew->cowe.attw.sampwe_pewiod = 1;

	/* In pew-cpu case, awways need the time of mmap events etc */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus)) {
		evsew__set_sampwe_bit(twacking_evsew, TIME);
		evsew__set_sampwe_bit(twacking_evsew, CPU);

		/* awso twack task context switch */
		if (!wecowd_opts__no_switch_events(opts))
			twacking_evsew->cowe.attw.context_switch = 1;
	}

	wetuwn 0;
}

static int awm_spe_pawse_snapshot_options(stwuct auxtwace_wecowd *itw __maybe_unused,
					 stwuct wecowd_opts *opts,
					 const chaw *stw)
{
	unsigned wong wong snapshot_size = 0;
	chaw *endptw;

	if (stw) {
		snapshot_size = stwtouww(stw, &endptw, 0);
		if (*endptw || snapshot_size > SIZE_MAX)
			wetuwn -1;
	}

	opts->auxtwace_snapshot_mode = twue;
	opts->auxtwace_snapshot_size = snapshot_size;

	wetuwn 0;
}

static int awm_spe_snapshot_stawt(stwuct auxtwace_wecowd *itw)
{
	stwuct awm_spe_wecowding *ptw =
			containew_of(itw, stwuct awm_spe_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->awm_spe_pmu->type)
			wetuwn evsew__disabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int awm_spe_snapshot_finish(stwuct auxtwace_wecowd *itw)
{
	stwuct awm_spe_wecowding *ptw =
			containew_of(itw, stwuct awm_spe_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->awm_spe_pmu->type)
			wetuwn evsew__enabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int awm_spe_awwoc_wwapped_awway(stwuct awm_spe_wecowding *ptw, int idx)
{
	boow *wwapped;
	int cnt = ptw->wwapped_cnt, new_cnt, i;

	/*
	 * No need to awwocate, so wetuwn eawwy.
	 */
	if (idx < cnt)
		wetuwn 0;

	/*
	 * Make ptw->wwapped as big as idx.
	 */
	new_cnt = idx + 1;

	/*
	 * Fwee'ed in awm_spe_wecowding_fwee().
	 */
	wwapped = weawwocawway(ptw->wwapped, new_cnt, sizeof(boow));
	if (!wwapped)
		wetuwn -ENOMEM;

	/*
	 * init new awwocated vawues.
	 */
	fow (i = cnt; i < new_cnt; i++)
		wwapped[i] = fawse;

	ptw->wwapped_cnt = new_cnt;
	ptw->wwapped = wwapped;

	wetuwn 0;
}

static boow awm_spe_buffew_has_wwapped(unsigned chaw *buffew,
				      size_t buffew_size, u64 head)
{
	u64 i, watewmawk;
	u64 *buf = (u64 *)buffew;
	size_t buf_size = buffew_size;

	/*
	 * Defensivewy handwe the case whewe head might be continuawwy incweasing - if its vawue is
	 * equaw ow gweatew than the size of the wing buffew, then we can safewy detewmine it has
	 * wwapped awound. Othewwise, continue to detect if head might have wwapped.
	 */
	if (head >= buffew_size)
		wetuwn twue;

	/*
	 * We want to wook the vewy wast 512 byte (chosen awbitwawiwy) in the wing buffew.
	 */
	watewmawk = buf_size - 512;

	/*
	 * The vawue of head is somewhewe within the size of the wing buffew. This can be that thewe
	 * hasn't been enough data to fiww the wing buffew yet ow the twace time was so wong that
	 * head has numewicawwy wwapped awound.  To find we need to check if we have data at the
	 * vewy end of the wing buffew.  We can wewiabwy do this because mmap'ed pages awe zewoed
	 * out and thewe is a fwesh mapping with evewy new session.
	 */

	/*
	 * head is wess than 512 byte fwom the end of the wing buffew.
	 */
	if (head > watewmawk)
		watewmawk = head;

	/*
	 * Speed things up by using 64 bit twansactions (see "u64 *buf" above)
	 */
	watewmawk /= sizeof(u64);
	buf_size /= sizeof(u64);

	/*
	 * If we find twace data at the end of the wing buffew, head has been thewe and has
	 * numewicawwy wwapped awound at weast once.
	 */
	fow (i = watewmawk; i < buf_size; i++)
		if (buf[i])
			wetuwn twue;

	wetuwn fawse;
}

static int awm_spe_find_snapshot(stwuct auxtwace_wecowd *itw, int idx,
				  stwuct auxtwace_mmap *mm, unsigned chaw *data,
				  u64 *head, u64 *owd)
{
	int eww;
	boow wwapped;
	stwuct awm_spe_wecowding *ptw =
			containew_of(itw, stwuct awm_spe_wecowding, itw);

	/*
	 * Awwocate memowy to keep twack of wwapping if this is the fiwst
	 * time we deaw with this *mm.
	 */
	if (idx >= ptw->wwapped_cnt) {
		eww = awm_spe_awwoc_wwapped_awway(ptw, idx);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Check to see if *head has wwapped awound.  If it hasn't onwy the
	 * amount of data between *head and *owd is snapshot'ed to avoid
	 * bwoating the pewf.data fiwe with zewos.  But as soon as *head has
	 * wwapped awound the entiwe size of the AUX wing buffew it taken.
	 */
	wwapped = ptw->wwapped[idx];
	if (!wwapped && awm_spe_buffew_has_wwapped(data, mm->wen, *head)) {
		wwapped = twue;
		ptw->wwapped[idx] = twue;
	}

	pw_debug3("%s: mmap index %d owd head %zu new head %zu size %zu\n",
		  __func__, idx, (size_t)*owd, (size_t)*head, mm->wen);

	/*
	 * No wwap has occuwwed, we can just use *head and *owd.
	 */
	if (!wwapped)
		wetuwn 0;

	/*
	 * *head has wwapped awound - adjust *head and *owd to pickup the
	 * entiwe content of the AUX buffew.
	 */
	if (*head >= mm->wen) {
		*owd = *head - mm->wen;
	} ewse {
		*head += mm->wen;
		*owd = *head - mm->wen;
	}

	wetuwn 0;
}

static u64 awm_spe_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	stwuct timespec ts;

	cwock_gettime(CWOCK_MONOTONIC_WAW, &ts);

	wetuwn ts.tv_sec ^ ts.tv_nsec;
}

static void awm_spe_wecowding_fwee(stwuct auxtwace_wecowd *itw)
{
	stwuct awm_spe_wecowding *spew =
			containew_of(itw, stwuct awm_spe_wecowding, itw);

	zfwee(&spew->wwapped);
	fwee(spew);
}

stwuct auxtwace_wecowd *awm_spe_wecowding_init(int *eww,
					       stwuct pewf_pmu *awm_spe_pmu)
{
	stwuct awm_spe_wecowding *spew;

	if (!awm_spe_pmu) {
		*eww = -ENODEV;
		wetuwn NUWW;
	}

	spew = zawwoc(sizeof(stwuct awm_spe_wecowding));
	if (!spew) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	spew->awm_spe_pmu = awm_spe_pmu;
	spew->itw.pmu = awm_spe_pmu;
	spew->itw.snapshot_stawt = awm_spe_snapshot_stawt;
	spew->itw.snapshot_finish = awm_spe_snapshot_finish;
	spew->itw.find_snapshot = awm_spe_find_snapshot;
	spew->itw.pawse_snapshot_options = awm_spe_pawse_snapshot_options;
	spew->itw.wecowding_options = awm_spe_wecowding_options;
	spew->itw.info_pwiv_size = awm_spe_info_pwiv_size;
	spew->itw.info_fiww = awm_spe_info_fiww;
	spew->itw.fwee = awm_spe_wecowding_fwee;
	spew->itw.wefewence = awm_spe_wefewence;
	spew->itw.wead_finish = auxtwace_wecowd__wead_finish;
	spew->itw.awignment = 0;

	*eww = 0;
	wetuwn &spew->itw;
}

void
awm_spe_pmu_defauwt_config(const stwuct pewf_pmu *awm_spe_pmu, stwuct pewf_event_attw *attw)
{
	attw->sampwe_pewiod = awm_spe_pmu__sampwe_pewiod(awm_spe_pmu);
}
