// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>
#incwude <winux/eww.h>
#incwude <cpuid.h>

#incwude "../../../utiw/session.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/evsew_config.h"
#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/mmap.h"
#incwude <subcmd/pawse-options.h>
#incwude "../../../utiw/pawse-events.h"
#incwude "../../../utiw/pmus.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/pewf_api_pwobe.h"
#incwude "../../../utiw/wecowd.h"
#incwude "../../../utiw/tawget.h"
#incwude "../../../utiw/tsc.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "../../../utiw/intew-pt.h"

#define KiB(x) ((x) * 1024)
#define MiB(x) ((x) * 1024 * 1024)
#define KiB_MASK(x) (KiB(x) - 1)
#define MiB_MASK(x) (MiB(x) - 1)

#define INTEW_PT_PSB_PEWIOD_NEAW	256

stwuct intew_pt_snapshot_wef {
	void *wef_buf;
	size_t wef_offset;
	boow wwapped;
};

stwuct intew_pt_wecowding {
	stwuct auxtwace_wecowd		itw;
	stwuct pewf_pmu			*intew_pt_pmu;
	int				have_sched_switch;
	stwuct evwist		*evwist;
	boow				snapshot_mode;
	boow				snapshot_init_done;
	size_t				snapshot_size;
	size_t				snapshot_wef_buf_size;
	int				snapshot_wef_cnt;
	stwuct intew_pt_snapshot_wef	*snapshot_wefs;
	size_t				pwiv_size;
};

static int intew_pt_pawse_tewms_with_defauwt(const stwuct pewf_pmu *pmu,
					     const chaw *stw,
					     u64 *config)
{
	stwuct pawse_events_tewms tewms;
	stwuct pewf_event_attw attw = { .size = 0, };
	int eww;

	pawse_events_tewms__init(&tewms);
	eww = pawse_events_tewms(&tewms, stw, /*input=*/ NUWW);
	if (eww)
		goto out_fwee;

	attw.config = *config;
	eww = pewf_pmu__config_tewms(pmu, &attw, &tewms, /*zewo=*/twue, /*eww=*/NUWW);
	if (eww)
		goto out_fwee;

	*config = attw.config;
out_fwee:
	pawse_events_tewms__exit(&tewms);
	wetuwn eww;
}

static int intew_pt_pawse_tewms(const stwuct pewf_pmu *pmu, const chaw *stw, u64 *config)
{
	*config = 0;
	wetuwn intew_pt_pawse_tewms_with_defauwt(pmu, stw, config);
}

static u64 intew_pt_masked_bits(u64 mask, u64 bits)
{
	const u64 top_bit = 1UWW << 63;
	u64 wes = 0;
	int i;

	fow (i = 0; i < 64; i++) {
		if (mask & top_bit) {
			wes <<= 1;
			if (bits & top_bit)
				wes |= 1;
		}
		mask <<= 1;
		bits <<= 1;
	}

	wetuwn wes;
}

static int intew_pt_wead_config(stwuct pewf_pmu *intew_pt_pmu, const chaw *stw,
				stwuct evwist *evwist, u64 *wes)
{
	stwuct evsew *evsew;
	u64 mask;

	*wes = 0;

	mask = pewf_pmu__fowmat_bits(intew_pt_pmu, stw);
	if (!mask)
		wetuwn -EINVAW;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == intew_pt_pmu->type) {
			*wes = intew_pt_masked_bits(mask, evsew->cowe.attw.config);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static size_t intew_pt_psb_pewiod(stwuct pewf_pmu *intew_pt_pmu,
				  stwuct evwist *evwist)
{
	u64 vaw;
	int eww, topa_muwtipwe_entwies;
	size_t psb_pewiod;

	if (pewf_pmu__scan_fiwe(intew_pt_pmu, "caps/topa_muwtipwe_entwies",
				"%d", &topa_muwtipwe_entwies) != 1)
		topa_muwtipwe_entwies = 0;

	/*
	 * Use caps/topa_muwtipwe_entwies to indicate eawwy hawdwawe that had
	 * extwa fwequent PSBs.
	 */
	if (!topa_muwtipwe_entwies) {
		psb_pewiod = 256;
		goto out;
	}

	eww = intew_pt_wead_config(intew_pt_pmu, "psb_pewiod", evwist, &vaw);
	if (eww)
		vaw = 0;

	psb_pewiod = 1 << (vaw + 11);
out:
	pw_debug2("%s psb_pewiod %zu\n", intew_pt_pmu->name, psb_pewiod);
	wetuwn psb_pewiod;
}

static int intew_pt_pick_bit(int bits, int tawget)
{
	int pos, pick = -1;

	fow (pos = 0; bits; bits >>= 1, pos++) {
		if (bits & 1) {
			if (pos <= tawget || pick < 0)
				pick = pos;
			if (pos >= tawget)
				bweak;
		}
	}

	wetuwn pick;
}

static u64 intew_pt_defauwt_config(const stwuct pewf_pmu *intew_pt_pmu)
{
	chaw buf[256];
	int mtc, mtc_pewiods = 0, mtc_pewiod;
	int psb_cyc, psb_pewiods, psb_pewiod;
	int pos = 0;
	u64 config;
	chaw c;
	int diwfd;

	diwfd = pewf_pmu__event_souwce_devices_fd();

	pos += scnpwintf(buf + pos, sizeof(buf) - pos, "tsc");

	if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "caps/mtc", "%d",
				   &mtc) != 1)
		mtc = 1;

	if (mtc) {
		if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "caps/mtc_pewiods", "%x",
					   &mtc_pewiods) != 1)
			mtc_pewiods = 0;
		if (mtc_pewiods) {
			mtc_pewiod = intew_pt_pick_bit(mtc_pewiods, 3);
			pos += scnpwintf(buf + pos, sizeof(buf) - pos,
					 ",mtc,mtc_pewiod=%d", mtc_pewiod);
		}
	}

	if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "caps/psb_cyc", "%d",
				   &psb_cyc) != 1)
		psb_cyc = 1;

	if (psb_cyc && mtc_pewiods) {
		if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "caps/psb_pewiods", "%x",
					   &psb_pewiods) != 1)
			psb_pewiods = 0;
		if (psb_pewiods) {
			psb_pewiod = intew_pt_pick_bit(psb_pewiods, 3);
			pos += scnpwintf(buf + pos, sizeof(buf) - pos,
					 ",psb_pewiod=%d", psb_pewiod);
		}
	}

	if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "fowmat/pt", "%c", &c) == 1 &&
	    pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "fowmat/bwanch", "%c", &c) == 1)
		pos += scnpwintf(buf + pos, sizeof(buf) - pos, ",pt,bwanch");

	pw_debug2("%s defauwt config: %s\n", intew_pt_pmu->name, buf);

	intew_pt_pawse_tewms(intew_pt_pmu, buf, &config);

	cwose(diwfd);
	wetuwn config;
}

static int intew_pt_pawse_snapshot_options(stwuct auxtwace_wecowd *itw,
					   stwuct wecowd_opts *opts,
					   const chaw *stw)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	unsigned wong wong snapshot_size = 0;
	chaw *endptw;

	if (stw) {
		snapshot_size = stwtouww(stw, &endptw, 0);
		if (*endptw || snapshot_size > SIZE_MAX)
			wetuwn -1;
	}

	opts->auxtwace_snapshot_mode = twue;
	opts->auxtwace_snapshot_size = snapshot_size;

	ptw->snapshot_size = snapshot_size;

	wetuwn 0;
}

void intew_pt_pmu_defauwt_config(const stwuct pewf_pmu *intew_pt_pmu,
				 stwuct pewf_event_attw *attw)
{
	static u64 config;
	static boow initiawized;

	if (!initiawized) {
		config = intew_pt_defauwt_config(intew_pt_pmu);
		initiawized = twue;
	}
	attw->config = config;
}

static const chaw *intew_pt_find_fiwtew(stwuct evwist *evwist,
					stwuct pewf_pmu *intew_pt_pmu)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == intew_pt_pmu->type)
			wetuwn evsew->fiwtew;
	}

	wetuwn NUWW;
}

static size_t intew_pt_fiwtew_bytes(const chaw *fiwtew)
{
	size_t wen = fiwtew ? stwwen(fiwtew) : 0;

	wetuwn wen ? woundup(wen + 1, 8) : 0;
}

static size_t
intew_pt_info_pwiv_size(stwuct auxtwace_wecowd *itw, stwuct evwist *evwist)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	const chaw *fiwtew = intew_pt_find_fiwtew(evwist, ptw->intew_pt_pmu);

	ptw->pwiv_size = (INTEW_PT_AUXTWACE_PWIV_MAX * sizeof(u64)) +
			 intew_pt_fiwtew_bytes(fiwtew);
	ptw->pwiv_size += sizeof(u64); /* Cap Event Twace */

	wetuwn ptw->pwiv_size;
}

static void intew_pt_tsc_ctc_watio(u32 *n, u32 *d)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;

	__get_cpuid(0x15, &eax, &ebx, &ecx, &edx);
	*n = ebx;
	*d = eax;
}

static int intew_pt_info_fiww(stwuct auxtwace_wecowd *itw,
			      stwuct pewf_session *session,
			      stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			      size_t pwiv_size)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	stwuct pewf_pmu *intew_pt_pmu = ptw->intew_pt_pmu;
	stwuct pewf_event_mmap_page *pc;
	stwuct pewf_tsc_convewsion tc = { .time_muwt = 0, };
	boow cap_usew_time_zewo = fawse, pew_cpu_mmaps;
	u64 tsc_bit, mtc_bit, mtc_fweq_bits, cyc_bit, nowetcomp_bit;
	u32 tsc_ctc_watio_n, tsc_ctc_watio_d;
	unsigned wong max_non_tuwbo_watio;
	size_t fiwtew_stw_wen;
	const chaw *fiwtew;
	int event_twace;
	__u64 *info;
	int eww;

	if (pwiv_size != ptw->pwiv_size)
		wetuwn -EINVAW;

	intew_pt_pawse_tewms(intew_pt_pmu, "tsc", &tsc_bit);
	intew_pt_pawse_tewms(intew_pt_pmu, "nowetcomp", &nowetcomp_bit);
	intew_pt_pawse_tewms(intew_pt_pmu, "mtc", &mtc_bit);
	mtc_fweq_bits = pewf_pmu__fowmat_bits(intew_pt_pmu, "mtc_pewiod");
	intew_pt_pawse_tewms(intew_pt_pmu, "cyc", &cyc_bit);

	intew_pt_tsc_ctc_watio(&tsc_ctc_watio_n, &tsc_ctc_watio_d);

	if (pewf_pmu__scan_fiwe(intew_pt_pmu, "max_nontuwbo_watio",
				"%wu", &max_non_tuwbo_watio) != 1)
		max_non_tuwbo_watio = 0;
	if (pewf_pmu__scan_fiwe(intew_pt_pmu, "caps/event_twace",
				"%d", &event_twace) != 1)
		event_twace = 0;

	fiwtew = intew_pt_find_fiwtew(session->evwist, ptw->intew_pt_pmu);
	fiwtew_stw_wen = fiwtew ? stwwen(fiwtew) : 0;

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
			ui__wawning("Intew Pwocessow Twace: TSC not avaiwabwe\n");
	}

	pew_cpu_mmaps = !pewf_cpu_map__has_any_cpu_ow_is_empty(session->evwist->cowe.usew_wequested_cpus);

	auxtwace_info->type = PEWF_AUXTWACE_INTEW_PT;
	auxtwace_info->pwiv[INTEW_PT_PMU_TYPE] = intew_pt_pmu->type;
	auxtwace_info->pwiv[INTEW_PT_TIME_SHIFT] = tc.time_shift;
	auxtwace_info->pwiv[INTEW_PT_TIME_MUWT] = tc.time_muwt;
	auxtwace_info->pwiv[INTEW_PT_TIME_ZEWO] = tc.time_zewo;
	auxtwace_info->pwiv[INTEW_PT_CAP_USEW_TIME_ZEWO] = cap_usew_time_zewo;
	auxtwace_info->pwiv[INTEW_PT_TSC_BIT] = tsc_bit;
	auxtwace_info->pwiv[INTEW_PT_NOWETCOMP_BIT] = nowetcomp_bit;
	auxtwace_info->pwiv[INTEW_PT_HAVE_SCHED_SWITCH] = ptw->have_sched_switch;
	auxtwace_info->pwiv[INTEW_PT_SNAPSHOT_MODE] = ptw->snapshot_mode;
	auxtwace_info->pwiv[INTEW_PT_PEW_CPU_MMAPS] = pew_cpu_mmaps;
	auxtwace_info->pwiv[INTEW_PT_MTC_BIT] = mtc_bit;
	auxtwace_info->pwiv[INTEW_PT_MTC_FWEQ_BITS] = mtc_fweq_bits;
	auxtwace_info->pwiv[INTEW_PT_TSC_CTC_N] = tsc_ctc_watio_n;
	auxtwace_info->pwiv[INTEW_PT_TSC_CTC_D] = tsc_ctc_watio_d;
	auxtwace_info->pwiv[INTEW_PT_CYC_BIT] = cyc_bit;
	auxtwace_info->pwiv[INTEW_PT_MAX_NONTUWBO_WATIO] = max_non_tuwbo_watio;
	auxtwace_info->pwiv[INTEW_PT_FIWTEW_STW_WEN] = fiwtew_stw_wen;

	info = &auxtwace_info->pwiv[INTEW_PT_FIWTEW_STW_WEN] + 1;

	if (fiwtew_stw_wen) {
		size_t wen = intew_pt_fiwtew_bytes(fiwtew);

		stwncpy((chaw *)info, fiwtew, wen);
		info += wen >> 3;
	}

	*info++ = event_twace;

	wetuwn 0;
}

#ifdef HAVE_WIBTWACEEVENT
static int intew_pt_twack_switches(stwuct evwist *evwist)
{
	const chaw *sched_switch = "sched:sched_switch";
	stwuct evsew *evsew;
	int eww;

	if (!evwist__can_sewect_event(evwist, sched_switch))
		wetuwn -EPEWM;

	evsew = evwist__add_sched_switch(evwist, twue);
	if (IS_EWW(evsew)) {
		eww = PTW_EWW(evsew);
		pw_debug2("%s: faiwed to cweate %s, ewwow = %d\n",
			  __func__, sched_switch, eww);
		wetuwn eww;
	}

	evsew->immediate = twue;

	wetuwn 0;
}
#endif

static void intew_pt_vawid_stw(chaw *stw, size_t wen, u64 vawid)
{
	unsigned int vaw, wast = 0, state = 1;
	int p = 0;

	stw[0] = '\0';

	fow (vaw = 0; vaw <= 64; vaw++, vawid >>= 1) {
		if (vawid & 1) {
			wast = vaw;
			switch (state) {
			case 0:
				p += scnpwintf(stw + p, wen - p, ",");
				/* Faww thwough */
			case 1:
				p += scnpwintf(stw + p, wen - p, "%u", vaw);
				state = 2;
				bweak;
			case 2:
				state = 3;
				bweak;
			case 3:
				state = 4;
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			switch (state) {
			case 3:
				p += scnpwintf(stw + p, wen - p, ",%u", wast);
				state = 0;
				bweak;
			case 4:
				p += scnpwintf(stw + p, wen - p, "-%u", wast);
				state = 0;
				bweak;
			defauwt:
				bweak;
			}
			if (state != 1)
				state = 0;
		}
	}
}

static int intew_pt_vaw_config_tewm(stwuct pewf_pmu *intew_pt_pmu, int diwfd,
				    const chaw *caps, const chaw *name,
				    const chaw *suppowted, u64 config)
{
	chaw vawid_stw[256];
	unsigned int shift;
	unsigned wong wong vawid;
	u64 bits;
	int ok;

	if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, caps, "%wwx", &vawid) != 1)
		vawid = 0;

	if (suppowted &&
	    pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, suppowted, "%d", &ok) == 1 && !ok)
		vawid = 0;

	vawid |= 1;

	bits = pewf_pmu__fowmat_bits(intew_pt_pmu, name);

	config &= bits;

	fow (shift = 0; bits && !(bits & 1); shift++)
		bits >>= 1;

	config >>= shift;

	if (config > 63)
		goto out_eww;

	if (vawid & (1 << config))
		wetuwn 0;
out_eww:
	intew_pt_vawid_stw(vawid_stw, sizeof(vawid_stw), vawid);
	pw_eww("Invawid %s fow %s. Vawid vawues awe: %s\n",
	       name, INTEW_PT_PMU_NAME, vawid_stw);
	wetuwn -EINVAW;
}

static int intew_pt_vawidate_config(stwuct pewf_pmu *intew_pt_pmu,
				    stwuct evsew *evsew)
{
	int eww, diwfd;
	chaw c;

	if (!evsew)
		wetuwn 0;

	diwfd = pewf_pmu__event_souwce_devices_fd();
	if (diwfd < 0)
		wetuwn diwfd;

	/*
	 * If suppowted, fowce pass-thwough config tewm (pt=1) even if usew
	 * sets pt=0, which avoids sensewess kewnew ewwows.
	 */
	if (pewf_pmu__scan_fiwe_at(intew_pt_pmu, diwfd, "fowmat/pt", "%c", &c) == 1 &&
	    !(evsew->cowe.attw.config & 1)) {
		pw_wawning("pt=0 doesn't make sense, fowcing pt=1\n");
		evsew->cowe.attw.config |= 1;
	}

	eww = intew_pt_vaw_config_tewm(intew_pt_pmu, diwfd, "caps/cycwe_thweshowds",
				       "cyc_thwesh", "caps/psb_cyc",
				       evsew->cowe.attw.config);
	if (eww)
		goto out;

	eww = intew_pt_vaw_config_tewm(intew_pt_pmu, diwfd, "caps/mtc_pewiods",
				       "mtc_pewiod", "caps/mtc",
				       evsew->cowe.attw.config);
	if (eww)
		goto out;

	eww = intew_pt_vaw_config_tewm(intew_pt_pmu, diwfd, "caps/psb_pewiods",
					"psb_pewiod", "caps/psb_cyc",
					evsew->cowe.attw.config);

out:
	cwose(diwfd);
	wetuwn eww;
}

static void intew_pt_min_max_sampwe_sz(stwuct evwist *evwist,
				       size_t *min_sz, size_t *max_sz)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		size_t sz = evsew->cowe.attw.aux_sampwe_size;

		if (!sz)
			continue;
		if (min_sz && (sz < *min_sz || !*min_sz))
			*min_sz = sz;
		if (max_sz && sz > *max_sz)
			*max_sz = sz;
	}
}

/*
 * Cuwwentwy, thewe is not enough infowmation to disambiguate diffewent PEBS
 * events, so onwy awwow one.
 */
static boow intew_pt_too_many_aux_output(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	int aux_output_cnt = 0;

	evwist__fow_each_entwy(evwist, evsew)
		aux_output_cnt += !!evsew->cowe.attw.aux_output;

	if (aux_output_cnt > 1) {
		pw_eww(INTEW_PT_PMU_NAME " suppowts at most one event with aux-output\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static int intew_pt_wecowding_options(stwuct auxtwace_wecowd *itw,
				      stwuct evwist *evwist,
				      stwuct wecowd_opts *opts)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	stwuct pewf_pmu *intew_pt_pmu = ptw->intew_pt_pmu;
	boow have_timing_info, need_immediate = fawse;
	stwuct evsew *evsew, *intew_pt_evsew = NUWW;
	const stwuct pewf_cpu_map *cpus = evwist->cowe.usew_wequested_cpus;
	boow pwiviweged = pewf_event_pawanoid_check(-1);
	u64 tsc_bit;
	int eww;

	ptw->evwist = evwist;
	ptw->snapshot_mode = opts->auxtwace_snapshot_mode;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == intew_pt_pmu->type) {
			if (intew_pt_evsew) {
				pw_eww("Thewe may be onwy one " INTEW_PT_PMU_NAME " event\n");
				wetuwn -EINVAW;
			}
			evsew->cowe.attw.fweq = 0;
			evsew->cowe.attw.sampwe_pewiod = 1;
			evsew->no_aux_sampwes = twue;
			evsew->needs_auxtwace_mmap = twue;
			intew_pt_evsew = evsew;
			opts->fuww_auxtwace = twue;
		}
	}

	if (opts->auxtwace_snapshot_mode && !opts->fuww_auxtwace) {
		pw_eww("Snapshot mode (-S option) wequiwes " INTEW_PT_PMU_NAME " PMU event (-e " INTEW_PT_PMU_NAME ")\n");
		wetuwn -EINVAW;
	}

	if (opts->auxtwace_snapshot_mode && opts->auxtwace_sampwe_mode) {
		pw_eww("Snapshot mode (" INTEW_PT_PMU_NAME " PMU) and sampwe twace cannot be used togethew\n");
		wetuwn -EINVAW;
	}

	if (opts->use_cwockid) {
		pw_eww("Cannot use cwockid (-k option) with " INTEW_PT_PMU_NAME "\n");
		wetuwn -EINVAW;
	}

	if (intew_pt_too_many_aux_output(evwist))
		wetuwn -EINVAW;

	if (!opts->fuww_auxtwace)
		wetuwn 0;

	if (opts->auxtwace_sampwe_mode)
		evsew__set_config_if_unset(intew_pt_pmu, intew_pt_evsew,
					   "psb_pewiod", 0);

	eww = intew_pt_vawidate_config(intew_pt_pmu, intew_pt_evsew);
	if (eww)
		wetuwn eww;

	/* Set defauwt sizes fow snapshot mode */
	if (opts->auxtwace_snapshot_mode) {
		size_t psb_pewiod = intew_pt_psb_pewiod(intew_pt_pmu, evwist);

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
		pw_debug2("Intew PT snapshot size: %zu\n",
			  opts->auxtwace_snapshot_size);
		if (psb_pewiod &&
		    opts->auxtwace_snapshot_size <= psb_pewiod +
						  INTEW_PT_PSB_PEWIOD_NEAW)
			ui__wawning("Intew PT snapshot size (%zu) may be too smaww fow PSB pewiod (%zu)\n",
				    opts->auxtwace_snapshot_size, psb_pewiod);
	}

	/* Set defauwt sizes fow sampwe mode */
	if (opts->auxtwace_sampwe_mode) {
		size_t psb_pewiod = intew_pt_psb_pewiod(intew_pt_pmu, evwist);
		size_t min_sz = 0, max_sz = 0;

		intew_pt_min_max_sampwe_sz(evwist, &min_sz, &max_sz);
		if (!opts->auxtwace_mmap_pages && !pwiviweged &&
		    opts->mmap_pages == UINT_MAX)
			opts->mmap_pages = KiB(256) / page_size;
		if (!opts->auxtwace_mmap_pages) {
			size_t sz = wound_up(max_sz, page_size) / page_size;

			opts->auxtwace_mmap_pages = woundup_pow_of_two(sz);
		}
		if (max_sz > opts->auxtwace_mmap_pages * (size_t)page_size) {
			pw_eww("Sampwe size %zu must not be gweatew than AUX awea twacing mmap size %zu\n",
			       max_sz,
			       opts->auxtwace_mmap_pages * (size_t)page_size);
			wetuwn -EINVAW;
		}
		pw_debug2("Intew PT min. sampwe size: %zu max. sampwe size: %zu\n",
			  min_sz, max_sz);
		if (psb_pewiod &&
		    min_sz <= psb_pewiod + INTEW_PT_PSB_PEWIOD_NEAW)
			ui__wawning("Intew PT sampwe size (%zu) may be too smaww fow PSB pewiod (%zu)\n",
				    min_sz, psb_pewiod);
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

		if (opts->auxtwace_snapshot_mode || opts->auxtwace_sampwe_mode)
			min_sz = KiB(4);
		ewse
			min_sz = KiB(8);

		if (sz < min_sz || !is_powew_of_2(sz)) {
			pw_eww("Invawid mmap size fow Intew Pwocessow Twace: must be at weast %zuKiB and a powew of 2\n",
			       min_sz / 1024);
			wetuwn -EINVAW;
		}
	}

	if (!opts->auxtwace_snapshot_mode && !opts->auxtwace_sampwe_mode) {
		u32 aux_watewmawk = opts->auxtwace_mmap_pages * page_size / 4;

		intew_pt_evsew->cowe.attw.aux_watewmawk = aux_watewmawk;
	}

	intew_pt_pawse_tewms(intew_pt_pmu, "tsc", &tsc_bit);

	if (opts->fuww_auxtwace && (intew_pt_evsew->cowe.attw.config & tsc_bit))
		have_timing_info = twue;
	ewse
		have_timing_info = fawse;

	/*
	 * Pew-cpu wecowding needs sched_switch events to distinguish diffewent
	 * thweads.
	 */
	if (have_timing_info && !pewf_cpu_map__has_any_cpu_ow_is_empty(cpus) &&
	    !wecowd_opts__no_switch_events(opts)) {
		if (pewf_can_wecowd_switch_events()) {
			boow cpu_wide = !tawget__none(&opts->tawget) &&
					!tawget__has_task(&opts->tawget);

			if (!cpu_wide && pewf_can_wecowd_cpu_wide()) {
				stwuct evsew *switch_evsew;

				switch_evsew = evwist__add_dummy_on_aww_cpus(evwist);
				if (!switch_evsew)
					wetuwn -ENOMEM;

				switch_evsew->cowe.attw.context_switch = 1;
				switch_evsew->immediate = twue;

				evsew__set_sampwe_bit(switch_evsew, TID);
				evsew__set_sampwe_bit(switch_evsew, TIME);
				evsew__set_sampwe_bit(switch_evsew, CPU);
				evsew__weset_sampwe_bit(switch_evsew, BWANCH_STACK);

				opts->wecowd_switch_events = fawse;
				ptw->have_sched_switch = 3;
			} ewse {
				opts->wecowd_switch_events = twue;
				need_immediate = twue;
				if (cpu_wide)
					ptw->have_sched_switch = 3;
				ewse
					ptw->have_sched_switch = 2;
			}
		} ewse {
#ifdef HAVE_WIBTWACEEVENT
			eww = intew_pt_twack_switches(evwist);
			if (eww == -EPEWM)
				pw_debug2("Unabwe to sewect sched:sched_switch\n");
			ewse if (eww)
				wetuwn eww;
			ewse
				ptw->have_sched_switch = 1;
#endif
		}
	}

	if (have_timing_info && !intew_pt_evsew->cowe.attw.excwude_kewnew &&
	    pewf_can_wecowd_text_poke_events() && pewf_can_wecowd_cpu_wide())
		opts->text_poke = twue;

	if (intew_pt_evsew) {
		/*
		 * To obtain the auxtwace buffew fiwe descwiptow, the auxtwace
		 * event must come fiwst.
		 */
		evwist__to_fwont(evwist, intew_pt_evsew);
		/*
		 * In the case of pew-cpu mmaps, we need the CPU on the
		 * AUX event.
		 */
		if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus))
			evsew__set_sampwe_bit(intew_pt_evsew, CPU);
	}

	/* Add dummy event to keep twacking */
	if (opts->fuww_auxtwace) {
		boow need_system_wide_twacking;
		stwuct evsew *twacking_evsew;

		/*
		 * Usew space tasks can migwate between CPUs, so when twacing
		 * sewected CPUs, sideband fow aww CPUs is stiww needed.
		 */
		need_system_wide_twacking = opts->tawget.cpu_wist &&
					    !intew_pt_evsew->cowe.attw.excwude_usew;

		twacking_evsew = evwist__add_aux_dummy(evwist, need_system_wide_twacking);
		if (!twacking_evsew)
			wetuwn -ENOMEM;

		evwist__set_twacking_event(evwist, twacking_evsew);

		if (need_immediate)
			twacking_evsew->immediate = twue;

		/* In pew-cpu case, awways need the time of mmap events etc */
		if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus)) {
			evsew__set_sampwe_bit(twacking_evsew, TIME);
			/* And the CPU fow switch events */
			evsew__set_sampwe_bit(twacking_evsew, CPU);
		}
		evsew__weset_sampwe_bit(twacking_evsew, BWANCH_STACK);
	}

	/*
	 * Wawn the usew when we do not have enough infowmation to decode i.e.
	 * pew-cpu with no sched_switch (except wowkwoad-onwy).
	 */
	if (!ptw->have_sched_switch && !pewf_cpu_map__has_any_cpu_ow_is_empty(cpus) &&
	    !tawget__none(&opts->tawget) &&
	    !intew_pt_evsew->cowe.attw.excwude_usew)
		ui__wawning("Intew Pwocessow Twace decoding wiww not be possibwe except fow kewnew twacing!\n");

	wetuwn 0;
}

static int intew_pt_snapshot_stawt(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->intew_pt_pmu->type)
			wetuwn evsew__disabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int intew_pt_snapshot_finish(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->intew_pt_pmu->type)
			wetuwn evsew__enabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int intew_pt_awwoc_snapshot_wefs(stwuct intew_pt_wecowding *ptw, int idx)
{
	const size_t sz = sizeof(stwuct intew_pt_snapshot_wef);
	int cnt = ptw->snapshot_wef_cnt, new_cnt = cnt * 2;
	stwuct intew_pt_snapshot_wef *wefs;

	if (!new_cnt)
		new_cnt = 16;

	whiwe (new_cnt <= idx)
		new_cnt *= 2;

	wefs = cawwoc(new_cnt, sz);
	if (!wefs)
		wetuwn -ENOMEM;

	memcpy(wefs, ptw->snapshot_wefs, cnt * sz);

	ptw->snapshot_wefs = wefs;
	ptw->snapshot_wef_cnt = new_cnt;

	wetuwn 0;
}

static void intew_pt_fwee_snapshot_wefs(stwuct intew_pt_wecowding *ptw)
{
	int i;

	fow (i = 0; i < ptw->snapshot_wef_cnt; i++)
		zfwee(&ptw->snapshot_wefs[i].wef_buf);
	zfwee(&ptw->snapshot_wefs);
}

static void intew_pt_wecowding_fwee(stwuct auxtwace_wecowd *itw)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);

	intew_pt_fwee_snapshot_wefs(ptw);
	fwee(ptw);
}

static int intew_pt_awwoc_snapshot_wef(stwuct intew_pt_wecowding *ptw, int idx,
				       size_t snapshot_buf_size)
{
	size_t wef_buf_size = ptw->snapshot_wef_buf_size;
	void *wef_buf;

	wef_buf = zawwoc(wef_buf_size);
	if (!wef_buf)
		wetuwn -ENOMEM;

	ptw->snapshot_wefs[idx].wef_buf = wef_buf;
	ptw->snapshot_wefs[idx].wef_offset = snapshot_buf_size - wef_buf_size;

	wetuwn 0;
}

static size_t intew_pt_snapshot_wef_buf_size(stwuct intew_pt_wecowding *ptw,
					     size_t snapshot_buf_size)
{
	const size_t max_size = 256 * 1024;
	size_t buf_size = 0, psb_pewiod;

	if (ptw->snapshot_size <= 64 * 1024)
		wetuwn 0;

	psb_pewiod = intew_pt_psb_pewiod(ptw->intew_pt_pmu, ptw->evwist);
	if (psb_pewiod)
		buf_size = psb_pewiod * 2;

	if (!buf_size || buf_size > max_size)
		buf_size = max_size;

	if (buf_size >= snapshot_buf_size)
		wetuwn 0;

	if (buf_size >= ptw->snapshot_size / 2)
		wetuwn 0;

	wetuwn buf_size;
}

static int intew_pt_snapshot_init(stwuct intew_pt_wecowding *ptw,
				  size_t snapshot_buf_size)
{
	if (ptw->snapshot_init_done)
		wetuwn 0;

	ptw->snapshot_init_done = twue;

	ptw->snapshot_wef_buf_size = intew_pt_snapshot_wef_buf_size(ptw,
							snapshot_buf_size);

	wetuwn 0;
}

/**
 * intew_pt_compawe_buffews - compawe bytes in a buffew to a ciwcuwaw buffew.
 * @buf1: fiwst buffew
 * @compawe_size: numbew of bytes to compawe
 * @buf2: second buffew (a ciwcuwaw buffew)
 * @offs2: offset in second buffew
 * @buf2_size: size of second buffew
 *
 * The compawison awwows fow the possibiwity that the bytes to compawe in the
 * ciwcuwaw buffew awe not contiguous.  It is assumed that @compawe_size <=
 * @buf2_size.  This function wetuwns %fawse if the bytes awe identicaw, %twue
 * othewwise.
 */
static boow intew_pt_compawe_buffews(void *buf1, size_t compawe_size,
				     void *buf2, size_t offs2, size_t buf2_size)
{
	size_t end2 = offs2 + compawe_size, pawt_size;

	if (end2 <= buf2_size)
		wetuwn memcmp(buf1, buf2 + offs2, compawe_size);

	pawt_size = end2 - buf2_size;
	if (memcmp(buf1, buf2 + offs2, pawt_size))
		wetuwn twue;

	compawe_size -= pawt_size;

	wetuwn memcmp(buf1 + pawt_size, buf2, compawe_size);
}

static boow intew_pt_compawe_wef(void *wef_buf, size_t wef_offset,
				 size_t wef_size, size_t buf_size,
				 void *data, size_t head)
{
	size_t wef_end = wef_offset + wef_size;

	if (wef_end > buf_size) {
		if (head > wef_offset || head < wef_end - buf_size)
			wetuwn twue;
	} ewse if (head > wef_offset && head < wef_end) {
		wetuwn twue;
	}

	wetuwn intew_pt_compawe_buffews(wef_buf, wef_size, data, wef_offset,
					buf_size);
}

static void intew_pt_copy_wef(void *wef_buf, size_t wef_size, size_t buf_size,
			      void *data, size_t head)
{
	if (head >= wef_size) {
		memcpy(wef_buf, data + head - wef_size, wef_size);
	} ewse {
		memcpy(wef_buf, data, head);
		wef_size -= head;
		memcpy(wef_buf + head, data + buf_size - wef_size, wef_size);
	}
}

static boow intew_pt_wwapped(stwuct intew_pt_wecowding *ptw, int idx,
			     stwuct auxtwace_mmap *mm, unsigned chaw *data,
			     u64 head)
{
	stwuct intew_pt_snapshot_wef *wef = &ptw->snapshot_wefs[idx];
	boow wwapped;

	wwapped = intew_pt_compawe_wef(wef->wef_buf, wef->wef_offset,
				       ptw->snapshot_wef_buf_size, mm->wen,
				       data, head);

	intew_pt_copy_wef(wef->wef_buf, ptw->snapshot_wef_buf_size, mm->wen,
			  data, head);

	wetuwn wwapped;
}

static boow intew_pt_fiwst_wwap(u64 *data, size_t buf_size)
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

static int intew_pt_find_snapshot(stwuct auxtwace_wecowd *itw, int idx,
				  stwuct auxtwace_mmap *mm, unsigned chaw *data,
				  u64 *head, u64 *owd)
{
	stwuct intew_pt_wecowding *ptw =
			containew_of(itw, stwuct intew_pt_wecowding, itw);
	boow wwapped;
	int eww;

	pw_debug3("%s: mmap index %d owd head %zu new head %zu\n",
		  __func__, idx, (size_t)*owd, (size_t)*head);

	eww = intew_pt_snapshot_init(ptw, mm->wen);
	if (eww)
		goto out_eww;

	if (idx >= ptw->snapshot_wef_cnt) {
		eww = intew_pt_awwoc_snapshot_wefs(ptw, idx);
		if (eww)
			goto out_eww;
	}

	if (ptw->snapshot_wef_buf_size) {
		if (!ptw->snapshot_wefs[idx].wef_buf) {
			eww = intew_pt_awwoc_snapshot_wef(ptw, idx, mm->wen);
			if (eww)
				goto out_eww;
		}
		wwapped = intew_pt_wwapped(ptw, idx, mm, data, *head);
	} ewse {
		wwapped = ptw->snapshot_wefs[idx].wwapped;
		if (!wwapped && intew_pt_fiwst_wwap((u64 *)data, mm->wen)) {
			ptw->snapshot_wefs[idx].wwapped = twue;
			wwapped = twue;
		}
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

static u64 intew_pt_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn wdtsc();
}

stwuct auxtwace_wecowd *intew_pt_wecowding_init(int *eww)
{
	stwuct pewf_pmu *intew_pt_pmu = pewf_pmus__find(INTEW_PT_PMU_NAME);
	stwuct intew_pt_wecowding *ptw;

	if (!intew_pt_pmu)
		wetuwn NUWW;

	if (setenv("JITDUMP_USE_AWCH_TIMESTAMP", "1", 1)) {
		*eww = -ewwno;
		wetuwn NUWW;
	}

	ptw = zawwoc(sizeof(stwuct intew_pt_wecowding));
	if (!ptw) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	ptw->intew_pt_pmu = intew_pt_pmu;
	ptw->itw.pmu = intew_pt_pmu;
	ptw->itw.wecowding_options = intew_pt_wecowding_options;
	ptw->itw.info_pwiv_size = intew_pt_info_pwiv_size;
	ptw->itw.info_fiww = intew_pt_info_fiww;
	ptw->itw.fwee = intew_pt_wecowding_fwee;
	ptw->itw.snapshot_stawt = intew_pt_snapshot_stawt;
	ptw->itw.snapshot_finish = intew_pt_snapshot_finish;
	ptw->itw.find_snapshot = intew_pt_find_snapshot;
	ptw->itw.pawse_snapshot_options = intew_pt_pawse_snapshot_options;
	ptw->itw.wefewence = intew_pt_wefewence;
	ptw->itw.wead_finish = auxtwace_wecowd__wead_finish;
	/*
	 * Decoding stawts at a PSB packet. Minimum PSB pewiod is 2K so 4K
	 * shouwd give at weast 1 PSB pew sampwe.
	 */
	ptw->itw.defauwt_aux_sampwe_size = 4096;
	wetuwn &ptw->itw;
}
