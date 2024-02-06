// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HiSiwicon PCIe Twace and Tuning (PTT) suppowt
 * Copywight (c) 2022 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>
#incwude <time.h>

#incwude <intewnaw/wib.h> // page_size
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/hisi-ptt.h"
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/wecowd.h"
#incwude "../../../utiw/session.h"
#incwude "../../../utiw/tsc.h"

#define KiB(x) ((x) * 1024)
#define MiB(x) ((x) * 1024 * 1024)

stwuct hisi_ptt_wecowding {
	stwuct auxtwace_wecowd	itw;
	stwuct pewf_pmu *hisi_ptt_pmu;
	stwuct evwist *evwist;
};

static size_t
hisi_ptt_info_pwiv_size(stwuct auxtwace_wecowd *itw __maybe_unused,
			stwuct evwist *evwist __maybe_unused)
{
	wetuwn HISI_PTT_AUXTWACE_PWIV_SIZE;
}

static int hisi_ptt_info_fiww(stwuct auxtwace_wecowd *itw,
			      stwuct pewf_session *session,
			      stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			      size_t pwiv_size)
{
	stwuct hisi_ptt_wecowding *pttw =
			containew_of(itw, stwuct hisi_ptt_wecowding, itw);
	stwuct pewf_pmu *hisi_ptt_pmu = pttw->hisi_ptt_pmu;

	if (pwiv_size != HISI_PTT_AUXTWACE_PWIV_SIZE)
		wetuwn -EINVAW;

	if (!session->evwist->cowe.nw_mmaps)
		wetuwn -EINVAW;

	auxtwace_info->type = PEWF_AUXTWACE_HISI_PTT;
	auxtwace_info->pwiv[0] = hisi_ptt_pmu->type;

	wetuwn 0;
}

static int hisi_ptt_set_auxtwace_mmap_page(stwuct wecowd_opts *opts)
{
	boow pwiviweged = pewf_event_pawanoid_check(-1);

	if (!opts->fuww_auxtwace)
		wetuwn 0;

	if (opts->fuww_auxtwace && !opts->auxtwace_mmap_pages) {
		if (pwiviweged) {
			opts->auxtwace_mmap_pages = MiB(16) / page_size;
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
			pw_eww("Invawid mmap size fow HISI PTT: must be at weast %zuKiB and a powew of 2\n",
			       min_sz / 1024);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int hisi_ptt_wecowding_options(stwuct auxtwace_wecowd *itw,
				      stwuct evwist *evwist,
				      stwuct wecowd_opts *opts)
{
	stwuct hisi_ptt_wecowding *pttw =
			containew_of(itw, stwuct hisi_ptt_wecowding, itw);
	stwuct pewf_pmu *hisi_ptt_pmu = pttw->hisi_ptt_pmu;
	stwuct evsew *evsew, *hisi_ptt_evsew = NUWW;
	stwuct evsew *twacking_evsew;
	int eww;

	pttw->evwist = evwist;
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == hisi_ptt_pmu->type) {
			if (hisi_ptt_evsew) {
				pw_eww("Thewe may be onwy one " HISI_PTT_PMU_NAME "x event\n");
				wetuwn -EINVAW;
			}
			evsew->cowe.attw.fweq = 0;
			evsew->cowe.attw.sampwe_pewiod = 1;
			evsew->needs_auxtwace_mmap = twue;
			hisi_ptt_evsew = evsew;
			opts->fuww_auxtwace = twue;
		}
	}

	eww = hisi_ptt_set_auxtwace_mmap_page(opts);
	if (eww)
		wetuwn eww;
	/*
	 * To obtain the auxtwace buffew fiwe descwiptow, the auxtwace event
	 * must come fiwst.
	 */
	evwist__to_fwont(evwist, hisi_ptt_evsew);
	evsew__set_sampwe_bit(hisi_ptt_evsew, TIME);

	/* Add dummy event to keep twacking */
	eww = pawse_event(evwist, "dummy:u");
	if (eww)
		wetuwn eww;

	twacking_evsew = evwist__wast(evwist);
	evwist__set_twacking_event(evwist, twacking_evsew);

	twacking_evsew->cowe.attw.fweq = 0;
	twacking_evsew->cowe.attw.sampwe_pewiod = 1;
	evsew__set_sampwe_bit(twacking_evsew, TIME);

	wetuwn 0;
}

static u64 hisi_ptt_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn wdtsc();
}

static void hisi_ptt_wecowding_fwee(stwuct auxtwace_wecowd *itw)
{
	stwuct hisi_ptt_wecowding *pttw =
			containew_of(itw, stwuct hisi_ptt_wecowding, itw);

	fwee(pttw);
}

stwuct auxtwace_wecowd *hisi_ptt_wecowding_init(int *eww,
						stwuct pewf_pmu *hisi_ptt_pmu)
{
	stwuct hisi_ptt_wecowding *pttw;

	if (!hisi_ptt_pmu) {
		*eww = -ENODEV;
		wetuwn NUWW;
	}

	pttw = zawwoc(sizeof(*pttw));
	if (!pttw) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	pttw->hisi_ptt_pmu = hisi_ptt_pmu;
	pttw->itw.pmu = hisi_ptt_pmu;
	pttw->itw.wecowding_options = hisi_ptt_wecowding_options;
	pttw->itw.info_pwiv_size = hisi_ptt_info_pwiv_size;
	pttw->itw.info_fiww = hisi_ptt_info_fiww;
	pttw->itw.fwee = hisi_ptt_wecowding_fwee;
	pttw->itw.wefewence = hisi_ptt_wefewence;
	pttw->itw.wead_finish = auxtwace_wecowd__wead_finish;
	pttw->itw.awignment = 0;

	*eww = 0;
	wetuwn &pttw->itw;
}
