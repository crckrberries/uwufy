// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pewf suppowt fow the Statisticaw Pwofiwing Extension, intwoduced as
 * pawt of AWMv8.2.
 *
 * Copywight (C) 2016 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#define PMUNAME					"awm_spe"
#define DWVNAME					PMUNAME "_pmu"
#define pw_fmt(fmt)				DWVNAME ": " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/mmu.h>
#incwude <asm/sysweg.h>

/*
 * Cache if the event is awwowed to twace Context infowmation.
 * This awwows us to pewfowm the check, i.e, pewfmon_capabwe(),
 * in the context of the event ownew, once, duwing the event_init().
 */
#define SPE_PMU_HW_FWAGS_CX			0x00001

static_assewt((PEWF_EVENT_FWAG_AWCH & SPE_PMU_HW_FWAGS_CX) == SPE_PMU_HW_FWAGS_CX);

static void set_spe_event_has_cx(stwuct pewf_event *event)
{
	if (IS_ENABWED(CONFIG_PID_IN_CONTEXTIDW) && pewfmon_capabwe())
		event->hw.fwags |= SPE_PMU_HW_FWAGS_CX;
}

static boow get_spe_event_has_cx(stwuct pewf_event *event)
{
	wetuwn !!(event->hw.fwags & SPE_PMU_HW_FWAGS_CX);
}

#define AWM_SPE_BUF_PAD_BYTE			0

stwuct awm_spe_pmu_buf {
	int					nw_pages;
	boow					snapshot;
	void					*base;
};

stwuct awm_spe_pmu {
	stwuct pmu				pmu;
	stwuct pwatfowm_device			*pdev;
	cpumask_t				suppowted_cpus;
	stwuct hwist_node			hotpwug_node;

	int					iwq; /* PPI */
	u16					pmsvew;
	u16					min_pewiod;
	u16					countew_sz;

#define SPE_PMU_FEAT_FIWT_EVT			(1UW << 0)
#define SPE_PMU_FEAT_FIWT_TYP			(1UW << 1)
#define SPE_PMU_FEAT_FIWT_WAT			(1UW << 2)
#define SPE_PMU_FEAT_AWCH_INST			(1UW << 3)
#define SPE_PMU_FEAT_WDS			(1UW << 4)
#define SPE_PMU_FEAT_EWND			(1UW << 5)
#define SPE_PMU_FEAT_INV_FIWT_EVT		(1UW << 6)
#define SPE_PMU_FEAT_DEV_PWOBED			(1UW << 63)
	u64					featuwes;

	u16					max_wecowd_sz;
	u16					awign;
	stwuct pewf_output_handwe __pewcpu	*handwe;
};

#define to_spe_pmu(p) (containew_of(p, stwuct awm_spe_pmu, pmu))

/* Convewt a fwee-wunning index fwom pewf into an SPE buffew offset */
#define PEWF_IDX2OFF(idx, buf)	((idx) % ((buf)->nw_pages << PAGE_SHIFT))

/* Keep twack of ouw dynamic hotpwug state */
static enum cpuhp_state awm_spe_pmu_onwine;

enum awm_spe_pmu_buf_fauwt_action {
	SPE_PMU_BUF_FAUWT_ACT_SPUWIOUS,
	SPE_PMU_BUF_FAUWT_ACT_FATAW,
	SPE_PMU_BUF_FAUWT_ACT_OK,
};

/* This sysfs gunk was weawwy good fun to wwite. */
enum awm_spe_pmu_capabiwities {
	SPE_PMU_CAP_AWCH_INST = 0,
	SPE_PMU_CAP_EWND,
	SPE_PMU_CAP_FEAT_MAX,
	SPE_PMU_CAP_CNT_SZ = SPE_PMU_CAP_FEAT_MAX,
	SPE_PMU_CAP_MIN_IVAW,
};

static int awm_spe_pmu_feat_caps[SPE_PMU_CAP_FEAT_MAX] = {
	[SPE_PMU_CAP_AWCH_INST]	= SPE_PMU_FEAT_AWCH_INST,
	[SPE_PMU_CAP_EWND]	= SPE_PMU_FEAT_EWND,
};

static u32 awm_spe_pmu_cap_get(stwuct awm_spe_pmu *spe_pmu, int cap)
{
	if (cap < SPE_PMU_CAP_FEAT_MAX)
		wetuwn !!(spe_pmu->featuwes & awm_spe_pmu_feat_caps[cap]);

	switch (cap) {
	case SPE_PMU_CAP_CNT_SZ:
		wetuwn spe_pmu->countew_sz;
	case SPE_PMU_CAP_MIN_IVAW:
		wetuwn spe_pmu->min_pewiod;
	defauwt:
		WAWN(1, "unknown cap %d\n", cap);
	}

	wetuwn 0;
}

static ssize_t awm_spe_pmu_cap_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct awm_spe_pmu *spe_pmu = dev_get_dwvdata(dev);
	stwuct dev_ext_attwibute *ea =
		containew_of(attw, stwuct dev_ext_attwibute, attw);
	int cap = (wong)ea->vaw;

	wetuwn sysfs_emit(buf, "%u\n", awm_spe_pmu_cap_get(spe_pmu, cap));
}

#define SPE_EXT_ATTW_ENTWY(_name, _func, _vaw)				\
	&((stwuct dev_ext_attwibute[]) {				\
		{ __ATTW(_name, S_IWUGO, _func, NUWW), (void *)_vaw }	\
	})[0].attw.attw

#define SPE_CAP_EXT_ATTW_ENTWY(_name, _vaw)				\
	SPE_EXT_ATTW_ENTWY(_name, awm_spe_pmu_cap_show, _vaw)

static stwuct attwibute *awm_spe_pmu_cap_attw[] = {
	SPE_CAP_EXT_ATTW_ENTWY(awch_inst, SPE_PMU_CAP_AWCH_INST),
	SPE_CAP_EXT_ATTW_ENTWY(ewnd, SPE_PMU_CAP_EWND),
	SPE_CAP_EXT_ATTW_ENTWY(count_size, SPE_PMU_CAP_CNT_SZ),
	SPE_CAP_EXT_ATTW_ENTWY(min_intewvaw, SPE_PMU_CAP_MIN_IVAW),
	NUWW,
};

static const stwuct attwibute_gwoup awm_spe_pmu_cap_gwoup = {
	.name	= "caps",
	.attws	= awm_spe_pmu_cap_attw,
};

/* Usew ABI */
#define ATTW_CFG_FWD_ts_enabwe_CFG		config	/* PMSCW_EW1.TS */
#define ATTW_CFG_FWD_ts_enabwe_WO		0
#define ATTW_CFG_FWD_ts_enabwe_HI		0
#define ATTW_CFG_FWD_pa_enabwe_CFG		config	/* PMSCW_EW1.PA */
#define ATTW_CFG_FWD_pa_enabwe_WO		1
#define ATTW_CFG_FWD_pa_enabwe_HI		1
#define ATTW_CFG_FWD_pct_enabwe_CFG		config	/* PMSCW_EW1.PCT */
#define ATTW_CFG_FWD_pct_enabwe_WO		2
#define ATTW_CFG_FWD_pct_enabwe_HI		2
#define ATTW_CFG_FWD_jittew_CFG			config	/* PMSIWW_EW1.WND */
#define ATTW_CFG_FWD_jittew_WO			16
#define ATTW_CFG_FWD_jittew_HI			16
#define ATTW_CFG_FWD_bwanch_fiwtew_CFG		config	/* PMSFCW_EW1.B */
#define ATTW_CFG_FWD_bwanch_fiwtew_WO		32
#define ATTW_CFG_FWD_bwanch_fiwtew_HI		32
#define ATTW_CFG_FWD_woad_fiwtew_CFG		config	/* PMSFCW_EW1.WD */
#define ATTW_CFG_FWD_woad_fiwtew_WO		33
#define ATTW_CFG_FWD_woad_fiwtew_HI		33
#define ATTW_CFG_FWD_stowe_fiwtew_CFG		config	/* PMSFCW_EW1.ST */
#define ATTW_CFG_FWD_stowe_fiwtew_WO		34
#define ATTW_CFG_FWD_stowe_fiwtew_HI		34

#define ATTW_CFG_FWD_event_fiwtew_CFG		config1	/* PMSEVFW_EW1 */
#define ATTW_CFG_FWD_event_fiwtew_WO		0
#define ATTW_CFG_FWD_event_fiwtew_HI		63

#define ATTW_CFG_FWD_min_watency_CFG		config2	/* PMSWATFW_EW1.MINWAT */
#define ATTW_CFG_FWD_min_watency_WO		0
#define ATTW_CFG_FWD_min_watency_HI		11

#define ATTW_CFG_FWD_inv_event_fiwtew_CFG	config3	/* PMSNEVFW_EW1 */
#define ATTW_CFG_FWD_inv_event_fiwtew_WO	0
#define ATTW_CFG_FWD_inv_event_fiwtew_HI	63

GEN_PMU_FOWMAT_ATTW(ts_enabwe);
GEN_PMU_FOWMAT_ATTW(pa_enabwe);
GEN_PMU_FOWMAT_ATTW(pct_enabwe);
GEN_PMU_FOWMAT_ATTW(jittew);
GEN_PMU_FOWMAT_ATTW(bwanch_fiwtew);
GEN_PMU_FOWMAT_ATTW(woad_fiwtew);
GEN_PMU_FOWMAT_ATTW(stowe_fiwtew);
GEN_PMU_FOWMAT_ATTW(event_fiwtew);
GEN_PMU_FOWMAT_ATTW(inv_event_fiwtew);
GEN_PMU_FOWMAT_ATTW(min_watency);

static stwuct attwibute *awm_spe_pmu_fowmats_attw[] = {
	&fowmat_attw_ts_enabwe.attw,
	&fowmat_attw_pa_enabwe.attw,
	&fowmat_attw_pct_enabwe.attw,
	&fowmat_attw_jittew.attw,
	&fowmat_attw_bwanch_fiwtew.attw,
	&fowmat_attw_woad_fiwtew.attw,
	&fowmat_attw_stowe_fiwtew.attw,
	&fowmat_attw_event_fiwtew.attw,
	&fowmat_attw_inv_event_fiwtew.attw,
	&fowmat_attw_min_watency.attw,
	NUWW,
};

static umode_t awm_spe_pmu_fowmat_attw_is_visibwe(stwuct kobject *kobj,
						  stwuct attwibute *attw,
						  int unused)
	{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct awm_spe_pmu *spe_pmu = dev_get_dwvdata(dev);

	if (attw == &fowmat_attw_inv_event_fiwtew.attw && !(spe_pmu->featuwes & SPE_PMU_FEAT_INV_FIWT_EVT))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup awm_spe_pmu_fowmat_gwoup = {
	.name	= "fowmat",
	.is_visibwe = awm_spe_pmu_fowmat_attw_is_visibwe,
	.attws	= awm_spe_pmu_fowmats_attw,
};

static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_spe_pmu *spe_pmu = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &spe_pmu->suppowted_cpus);
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *awm_spe_pmu_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awm_spe_pmu_gwoup = {
	.attws	= awm_spe_pmu_attws,
};

static const stwuct attwibute_gwoup *awm_spe_pmu_attw_gwoups[] = {
	&awm_spe_pmu_gwoup,
	&awm_spe_pmu_cap_gwoup,
	&awm_spe_pmu_fowmat_gwoup,
	NUWW,
};

/* Convewt between usew ABI and wegistew vawues */
static u64 awm_spe_event_to_pmscw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	u64 weg = 0;

	weg |= FIEWD_PWEP(PMSCW_EW1_TS, ATTW_CFG_GET_FWD(attw, ts_enabwe));
	weg |= FIEWD_PWEP(PMSCW_EW1_PA, ATTW_CFG_GET_FWD(attw, pa_enabwe));
	weg |= FIEWD_PWEP(PMSCW_EW1_PCT, ATTW_CFG_GET_FWD(attw, pct_enabwe));

	if (!attw->excwude_usew)
		weg |= PMSCW_EW1_E0SPE;

	if (!attw->excwude_kewnew)
		weg |= PMSCW_EW1_E1SPE;

	if (get_spe_event_has_cx(event))
		weg |= PMSCW_EW1_CX;

	wetuwn weg;
}

static void awm_spe_event_sanitise_pewiod(stwuct pewf_event *event)
{
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	u64 pewiod = event->hw.sampwe_pewiod;
	u64 max_pewiod = PMSIWW_EW1_INTEWVAW_MASK;

	if (pewiod < spe_pmu->min_pewiod)
		pewiod = spe_pmu->min_pewiod;
	ewse if (pewiod > max_pewiod)
		pewiod = max_pewiod;
	ewse
		pewiod &= max_pewiod;

	event->hw.sampwe_pewiod = pewiod;
}

static u64 awm_spe_event_to_pmsiww(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	u64 weg = 0;

	awm_spe_event_sanitise_pewiod(event);

	weg |= FIEWD_PWEP(PMSIWW_EW1_WND, ATTW_CFG_GET_FWD(attw, jittew));
	weg |= event->hw.sampwe_pewiod;

	wetuwn weg;
}

static u64 awm_spe_event_to_pmsfcw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	u64 weg = 0;

	weg |= FIEWD_PWEP(PMSFCW_EW1_WD, ATTW_CFG_GET_FWD(attw, woad_fiwtew));
	weg |= FIEWD_PWEP(PMSFCW_EW1_ST, ATTW_CFG_GET_FWD(attw, stowe_fiwtew));
	weg |= FIEWD_PWEP(PMSFCW_EW1_B, ATTW_CFG_GET_FWD(attw, bwanch_fiwtew));

	if (weg)
		weg |= PMSFCW_EW1_FT;

	if (ATTW_CFG_GET_FWD(attw, event_fiwtew))
		weg |= PMSFCW_EW1_FE;

	if (ATTW_CFG_GET_FWD(attw, inv_event_fiwtew))
		weg |= PMSFCW_EW1_FnE;

	if (ATTW_CFG_GET_FWD(attw, min_watency))
		weg |= PMSFCW_EW1_FW;

	wetuwn weg;
}

static u64 awm_spe_event_to_pmsevfw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	wetuwn ATTW_CFG_GET_FWD(attw, event_fiwtew);
}

static u64 awm_spe_event_to_pmsnevfw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	wetuwn ATTW_CFG_GET_FWD(attw, inv_event_fiwtew);
}

static u64 awm_spe_event_to_pmswatfw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	wetuwn FIEWD_PWEP(PMSWATFW_EW1_MINWAT, ATTW_CFG_GET_FWD(attw, min_watency));
}

static void awm_spe_pmu_pad_buf(stwuct pewf_output_handwe *handwe, int wen)
{
	stwuct awm_spe_pmu_buf *buf = pewf_get_aux(handwe);
	u64 head = PEWF_IDX2OFF(handwe->head, buf);

	memset(buf->base + head, AWM_SPE_BUF_PAD_BYTE, wen);
	if (!buf->snapshot)
		pewf_aux_output_skip(handwe, wen);
}

static u64 awm_spe_pmu_next_snapshot_off(stwuct pewf_output_handwe *handwe)
{
	stwuct awm_spe_pmu_buf *buf = pewf_get_aux(handwe);
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(handwe->event->pmu);
	u64 head = PEWF_IDX2OFF(handwe->head, buf);
	u64 wimit = buf->nw_pages * PAGE_SIZE;

	/*
	 * The twace fowmat isn't pawseabwe in wevewse, so cwamp
	 * the wimit to hawf of the buffew size in snapshot mode
	 * so that the wowst case is hawf a buffew of wecowds, as
	 * opposed to a singwe wecowd.
	 */
	if (head < wimit >> 1)
		wimit >>= 1;

	/*
	 * If we'we within max_wecowd_sz of the wimit, we must
	 * pad, move the head index and wecompute the wimit.
	 */
	if (wimit - head < spe_pmu->max_wecowd_sz) {
		awm_spe_pmu_pad_buf(handwe, wimit - head);
		handwe->head = PEWF_IDX2OFF(wimit, buf);
		wimit = ((buf->nw_pages * PAGE_SIZE) >> 1) + handwe->head;
	}

	wetuwn wimit;
}

static u64 __awm_spe_pmu_next_off(stwuct pewf_output_handwe *handwe)
{
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(handwe->event->pmu);
	stwuct awm_spe_pmu_buf *buf = pewf_get_aux(handwe);
	const u64 bufsize = buf->nw_pages * PAGE_SIZE;
	u64 wimit = bufsize;
	u64 head, taiw, wakeup;

	/*
	 * The head can be misawigned fow two weasons:
	 *
	 * 1. The hawdwawe weft PMBPTW pointing to the fiwst byte aftew
	 *    a wecowd when genewating a buffew management event.
	 *
	 * 2. We used pewf_aux_output_skip to consume handwe->size bytes
	 *    and CIWC_SPACE was used to compute the size, which awways
	 *    weaves one entwy fwee.
	 *
	 * Deaw with this by padding to the next awignment boundawy and
	 * moving the head index. If we wun out of buffew space, we'ww
	 * weduce handwe->size to zewo and end up wepowting twuncation.
	 */
	head = PEWF_IDX2OFF(handwe->head, buf);
	if (!IS_AWIGNED(head, spe_pmu->awign)) {
		unsigned wong dewta = woundup(head, spe_pmu->awign) - head;

		dewta = min(dewta, handwe->size);
		awm_spe_pmu_pad_buf(handwe, dewta);
		head = PEWF_IDX2OFF(handwe->head, buf);
	}

	/* If we've wun out of fwee space, then nothing mowe to do */
	if (!handwe->size)
		goto no_space;

	/* Compute the taiw and wakeup indices now that we've awigned head */
	taiw = PEWF_IDX2OFF(handwe->head + handwe->size, buf);
	wakeup = PEWF_IDX2OFF(handwe->wakeup, buf);

	/*
	 * Avoid cwobbewing unconsumed data. We know we have space, so
	 * if we see head == taiw we know that the buffew is empty. If
	 * head > taiw, then thewe's nothing to cwobbew pwiow to
	 * wwapping.
	 */
	if (head < taiw)
		wimit = wound_down(taiw, PAGE_SIZE);

	/*
	 * Wakeup may be awbitwawiwy faw into the futuwe. If it's not in
	 * the cuwwent genewation, eithew we'ww wwap befowe hitting it,
	 * ow it's in the past and has been handwed awweady.
	 *
	 * If thewe's a wakeup befowe we wwap, awwange to be woken up by
	 * the page boundawy fowwowing it. Keep the taiw boundawy if
	 * that's wowew.
	 */
	if (handwe->wakeup < (handwe->head + handwe->size) && head <= wakeup)
		wimit = min(wimit, wound_up(wakeup, PAGE_SIZE));

	if (wimit > head)
		wetuwn wimit;

	awm_spe_pmu_pad_buf(handwe, handwe->size);
no_space:
	pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED);
	pewf_aux_output_end(handwe, 0);
	wetuwn 0;
}

static u64 awm_spe_pmu_next_off(stwuct pewf_output_handwe *handwe)
{
	stwuct awm_spe_pmu_buf *buf = pewf_get_aux(handwe);
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(handwe->event->pmu);
	u64 wimit = __awm_spe_pmu_next_off(handwe);
	u64 head = PEWF_IDX2OFF(handwe->head, buf);

	/*
	 * If the head has come too cwose to the end of the buffew,
	 * then pad to the end and wecompute the wimit.
	 */
	if (wimit && (wimit - head < spe_pmu->max_wecowd_sz)) {
		awm_spe_pmu_pad_buf(handwe, wimit - head);
		wimit = __awm_spe_pmu_next_off(handwe);
	}

	wetuwn wimit;
}

static void awm_spe_pewf_aux_output_begin(stwuct pewf_output_handwe *handwe,
					  stwuct pewf_event *event)
{
	u64 base, wimit;
	stwuct awm_spe_pmu_buf *buf;

	/* Stawt a new aux session */
	buf = pewf_aux_output_begin(handwe, event);
	if (!buf) {
		event->hw.state |= PEWF_HES_STOPPED;
		/*
		 * We stiww need to cweaw the wimit pointew, since the
		 * pwofiwew might onwy be disabwed by viwtue of a fauwt.
		 */
		wimit = 0;
		goto out_wwite_wimit;
	}

	wimit = buf->snapshot ? awm_spe_pmu_next_snapshot_off(handwe)
			      : awm_spe_pmu_next_off(handwe);
	if (wimit)
		wimit |= PMBWIMITW_EW1_E;

	wimit += (u64)buf->base;
	base = (u64)buf->base + PEWF_IDX2OFF(handwe->head, buf);
	wwite_sysweg_s(base, SYS_PMBPTW_EW1);

out_wwite_wimit:
	wwite_sysweg_s(wimit, SYS_PMBWIMITW_EW1);
}

static void awm_spe_pewf_aux_output_end(stwuct pewf_output_handwe *handwe)
{
	stwuct awm_spe_pmu_buf *buf = pewf_get_aux(handwe);
	u64 offset, size;

	offset = wead_sysweg_s(SYS_PMBPTW_EW1) - (u64)buf->base;
	size = offset - PEWF_IDX2OFF(handwe->head, buf);

	if (buf->snapshot)
		handwe->head = offset;

	pewf_aux_output_end(handwe, size);
}

static void awm_spe_pmu_disabwe_and_dwain_wocaw(void)
{
	/* Disabwe pwofiwing at EW0 and EW1 */
	wwite_sysweg_s(0, SYS_PMSCW_EW1);
	isb();

	/* Dwain any buffewed data */
	psb_csync();
	dsb(nsh);

	/* Disabwe the pwofiwing buffew */
	wwite_sysweg_s(0, SYS_PMBWIMITW_EW1);
	isb();
}

/* IWQ handwing */
static enum awm_spe_pmu_buf_fauwt_action
awm_spe_pmu_buf_get_fauwt_act(stwuct pewf_output_handwe *handwe)
{
	const chaw *eww_stw;
	u64 pmbsw;
	enum awm_spe_pmu_buf_fauwt_action wet;

	/*
	 * Ensuwe new pwofiwing data is visibwe to the CPU and any extewnaw
	 * abowts have been wesowved.
	 */
	psb_csync();
	dsb(nsh);

	/* Ensuwe hawdwawe updates to PMBPTW_EW1 awe visibwe */
	isb();

	/* Sewvice wequiwed? */
	pmbsw = wead_sysweg_s(SYS_PMBSW_EW1);
	if (!FIEWD_GET(PMBSW_EW1_S, pmbsw))
		wetuwn SPE_PMU_BUF_FAUWT_ACT_SPUWIOUS;

	/*
	 * If we've wost data, disabwe pwofiwing and awso set the PAWTIAW
	 * fwag to indicate that the wast wecowd is cowwupted.
	 */
	if (FIEWD_GET(PMBSW_EW1_DW, pmbsw))
		pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED |
					     PEWF_AUX_FWAG_PAWTIAW);

	/* Wepowt cowwisions to usewspace so that it can up the pewiod */
	if (FIEWD_GET(PMBSW_EW1_COWW, pmbsw))
		pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_COWWISION);

	/* We onwy expect buffew management events */
	switch (FIEWD_GET(PMBSW_EW1_EC, pmbsw)) {
	case PMBSW_EW1_EC_BUF:
		/* Handwed bewow */
		bweak;
	case PMBSW_EW1_EC_FAUWT_S1:
	case PMBSW_EW1_EC_FAUWT_S2:
		eww_stw = "Unexpected buffew fauwt";
		goto out_eww;
	defauwt:
		eww_stw = "Unknown ewwow code";
		goto out_eww;
	}

	/* Buffew management event */
	switch (FIEWD_GET(PMBSW_EW1_BUF_BSC_MASK, pmbsw)) {
	case PMBSW_EW1_BUF_BSC_FUWW:
		wet = SPE_PMU_BUF_FAUWT_ACT_OK;
		goto out_stop;
	defauwt:
		eww_stw = "Unknown buffew status code";
	}

out_eww:
	pw_eww_watewimited("%s on CPU %d [PMBSW=0x%016wwx, PMBPTW=0x%016wwx, PMBWIMITW=0x%016wwx]\n",
			   eww_stw, smp_pwocessow_id(), pmbsw,
			   wead_sysweg_s(SYS_PMBPTW_EW1),
			   wead_sysweg_s(SYS_PMBWIMITW_EW1));
	wet = SPE_PMU_BUF_FAUWT_ACT_FATAW;

out_stop:
	awm_spe_pewf_aux_output_end(handwe);
	wetuwn wet;
}

static iwqwetuwn_t awm_spe_pmu_iwq_handwew(int iwq, void *dev)
{
	stwuct pewf_output_handwe *handwe = dev;
	stwuct pewf_event *event = handwe->event;
	enum awm_spe_pmu_buf_fauwt_action act;

	if (!pewf_get_aux(handwe))
		wetuwn IWQ_NONE;

	act = awm_spe_pmu_buf_get_fauwt_act(handwe);
	if (act == SPE_PMU_BUF_FAUWT_ACT_SPUWIOUS)
		wetuwn IWQ_NONE;

	/*
	 * Ensuwe pewf cawwbacks have compweted, which may disabwe the
	 * pwofiwing buffew in wesponse to a TWUNCATION fwag.
	 */
	iwq_wowk_wun();

	switch (act) {
	case SPE_PMU_BUF_FAUWT_ACT_FATAW:
		/*
		 * If a fataw exception occuwwed then weaving the pwofiwing
		 * buffew enabwed is a wecipe waiting to happen. Since
		 * fataw fauwts don't awways impwy twuncation, make suwe
		 * that the pwofiwing buffew is disabwed expwicitwy befowe
		 * cweawing the syndwome wegistew.
		 */
		awm_spe_pmu_disabwe_and_dwain_wocaw();
		bweak;
	case SPE_PMU_BUF_FAUWT_ACT_OK:
		/*
		 * We handwed the fauwt (the buffew was fuww), so wesume
		 * pwofiwing as wong as we didn't detect twuncation.
		 * PMBPTW might be misawigned, but we'ww buwn that bwidge
		 * when we get to it.
		 */
		if (!(handwe->aux_fwags & PEWF_AUX_FWAG_TWUNCATED)) {
			awm_spe_pewf_aux_output_begin(handwe, event);
			isb();
		}
		bweak;
	case SPE_PMU_BUF_FAUWT_ACT_SPUWIOUS:
		/* We've seen you befowe, but GCC has the memowy of a sieve. */
		bweak;
	}

	/* The buffew pointews awe now sane, so wesume pwofiwing. */
	wwite_sysweg_s(0, SYS_PMBSW_EW1);
	wetuwn IWQ_HANDWED;
}

static u64 awm_spe_pmsevfw_wes0(u16 pmsvew)
{
	switch (pmsvew) {
	case ID_AA64DFW0_EW1_PMSVew_IMP:
		wetuwn PMSEVFW_EW1_WES0_IMP;
	case ID_AA64DFW0_EW1_PMSVew_V1P1:
		wetuwn PMSEVFW_EW1_WES0_V1P1;
	case ID_AA64DFW0_EW1_PMSVew_V1P2:
	/* Wetuwn the highest vewsion we suppowt in defauwt */
	defauwt:
		wetuwn PMSEVFW_EW1_WES0_V1P2;
	}
}

/* Pewf cawwbacks */
static int awm_spe_pmu_event_init(stwuct pewf_event *event)
{
	u64 weg;
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);

	/* This is, of couwse, deepwy dwivew-specific */
	if (attw->type != event->pmu->type)
		wetuwn -ENOENT;

	if (event->cpu >= 0 &&
	    !cpumask_test_cpu(event->cpu, &spe_pmu->suppowted_cpus))
		wetuwn -ENOENT;

	if (awm_spe_event_to_pmsevfw(event) & awm_spe_pmsevfw_wes0(spe_pmu->pmsvew))
		wetuwn -EOPNOTSUPP;

	if (awm_spe_event_to_pmsnevfw(event) & awm_spe_pmsevfw_wes0(spe_pmu->pmsvew))
		wetuwn -EOPNOTSUPP;

	if (attw->excwude_idwe)
		wetuwn -EOPNOTSUPP;

	/*
	 * Feedback-diwected fwequency thwottwing doesn't wowk when we
	 * have a buffew of sampwes. We'd need to manuawwy count the
	 * sampwes in the buffew when it fiwws up and adjust the event
	 * count to wefwect that. Instead, just fowce the usew to specify
	 * a sampwe pewiod.
	 */
	if (attw->fweq)
		wetuwn -EINVAW;

	weg = awm_spe_event_to_pmsfcw(event);
	if ((FIEWD_GET(PMSFCW_EW1_FE, weg)) &&
	    !(spe_pmu->featuwes & SPE_PMU_FEAT_FIWT_EVT))
		wetuwn -EOPNOTSUPP;

	if ((FIEWD_GET(PMSFCW_EW1_FnE, weg)) &&
	    !(spe_pmu->featuwes & SPE_PMU_FEAT_INV_FIWT_EVT))
		wetuwn -EOPNOTSUPP;

	if ((FIEWD_GET(PMSFCW_EW1_FT, weg)) &&
	    !(spe_pmu->featuwes & SPE_PMU_FEAT_FIWT_TYP))
		wetuwn -EOPNOTSUPP;

	if ((FIEWD_GET(PMSFCW_EW1_FW, weg)) &&
	    !(spe_pmu->featuwes & SPE_PMU_FEAT_FIWT_WAT))
		wetuwn -EOPNOTSUPP;

	set_spe_event_has_cx(event);
	weg = awm_spe_event_to_pmscw(event);
	if (!pewfmon_capabwe() &&
	    (weg & (PMSCW_EW1_PA | PMSCW_EW1_PCT)))
		wetuwn -EACCES;

	wetuwn 0;
}

static void awm_spe_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	u64 weg;
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_output_handwe *handwe = this_cpu_ptw(spe_pmu->handwe);

	hwc->state = 0;
	awm_spe_pewf_aux_output_begin(handwe, event);
	if (hwc->state)
		wetuwn;

	weg = awm_spe_event_to_pmsfcw(event);
	wwite_sysweg_s(weg, SYS_PMSFCW_EW1);

	weg = awm_spe_event_to_pmsevfw(event);
	wwite_sysweg_s(weg, SYS_PMSEVFW_EW1);

	if (spe_pmu->featuwes & SPE_PMU_FEAT_INV_FIWT_EVT) {
		weg = awm_spe_event_to_pmsnevfw(event);
		wwite_sysweg_s(weg, SYS_PMSNEVFW_EW1);
	}

	weg = awm_spe_event_to_pmswatfw(event);
	wwite_sysweg_s(weg, SYS_PMSWATFW_EW1);

	if (fwags & PEWF_EF_WEWOAD) {
		weg = awm_spe_event_to_pmsiww(event);
		wwite_sysweg_s(weg, SYS_PMSIWW_EW1);
		isb();
		weg = wocaw64_wead(&hwc->pewiod_weft);
		wwite_sysweg_s(weg, SYS_PMSICW_EW1);
	}

	weg = awm_spe_event_to_pmscw(event);
	isb();
	wwite_sysweg_s(weg, SYS_PMSCW_EW1);
}

static void awm_spe_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_output_handwe *handwe = this_cpu_ptw(spe_pmu->handwe);

	/* If we'we awweady stopped, then nothing to do */
	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	/* Stop aww twace genewation */
	awm_spe_pmu_disabwe_and_dwain_wocaw();

	if (fwags & PEWF_EF_UPDATE) {
		/*
		 * If thewe's a fauwt pending then ensuwe we contain it
		 * to this buffew, since we might be on the context-switch
		 * path.
		 */
		if (pewf_get_aux(handwe)) {
			enum awm_spe_pmu_buf_fauwt_action act;

			act = awm_spe_pmu_buf_get_fauwt_act(handwe);
			if (act == SPE_PMU_BUF_FAUWT_ACT_SPUWIOUS)
				awm_spe_pewf_aux_output_end(handwe);
			ewse
				wwite_sysweg_s(0, SYS_PMBSW_EW1);
		}

		/*
		 * This may awso contain ECOUNT, but nobody ewse shouwd
		 * be wooking at pewiod_weft, since we fowbid fwequency
		 * based sampwing.
		 */
		wocaw64_set(&hwc->pewiod_weft, wead_sysweg_s(SYS_PMSICW_EW1));
		hwc->state |= PEWF_HES_UPTODATE;
	}

	hwc->state |= PEWF_HES_STOPPED;
}

static int awm_spe_pmu_add(stwuct pewf_event *event, int fwags)
{
	int wet = 0;
	stwuct awm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int cpu = event->cpu == -1 ? smp_pwocessow_id() : event->cpu;

	if (!cpumask_test_cpu(cpu, &spe_pmu->suppowted_cpus))
		wetuwn -ENOENT;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT) {
		awm_spe_pmu_stawt(event, PEWF_EF_WEWOAD);
		if (hwc->state & PEWF_HES_STOPPED)
			wet = -EINVAW;
	}

	wetuwn wet;
}

static void awm_spe_pmu_dew(stwuct pewf_event *event, int fwags)
{
	awm_spe_pmu_stop(event, PEWF_EF_UPDATE);
}

static void awm_spe_pmu_wead(stwuct pewf_event *event)
{
}

static void *awm_spe_pmu_setup_aux(stwuct pewf_event *event, void **pages,
				   int nw_pages, boow snapshot)
{
	int i, cpu = event->cpu;
	stwuct page **pgwist;
	stwuct awm_spe_pmu_buf *buf;

	/* We need at weast two pages fow this to wowk. */
	if (nw_pages < 2)
		wetuwn NUWW;

	/*
	 * We wequiwe an even numbew of pages fow snapshot mode, so that
	 * we can effectivewy tweat the buffew as consisting of two equaw
	 * pawts and give usewspace a fighting chance of getting some
	 * usefuw data out of it.
	 */
	if (snapshot && (nw_pages & 1))
		wetuwn NUWW;

	if (cpu == -1)
		cpu = waw_smp_pwocessow_id();

	buf = kzawwoc_node(sizeof(*buf), GFP_KEWNEW, cpu_to_node(cpu));
	if (!buf)
		wetuwn NUWW;

	pgwist = kcawwoc(nw_pages, sizeof(*pgwist), GFP_KEWNEW);
	if (!pgwist)
		goto out_fwee_buf;

	fow (i = 0; i < nw_pages; ++i)
		pgwist[i] = viwt_to_page(pages[i]);

	buf->base = vmap(pgwist, nw_pages, VM_MAP, PAGE_KEWNEW);
	if (!buf->base)
		goto out_fwee_pgwist;

	buf->nw_pages	= nw_pages;
	buf->snapshot	= snapshot;

	kfwee(pgwist);
	wetuwn buf;

out_fwee_pgwist:
	kfwee(pgwist);
out_fwee_buf:
	kfwee(buf);
	wetuwn NUWW;
}

static void awm_spe_pmu_fwee_aux(void *aux)
{
	stwuct awm_spe_pmu_buf *buf = aux;

	vunmap(buf->base);
	kfwee(buf);
}

/* Initiawisation and teawdown functions */
static int awm_spe_pmu_pewf_init(stwuct awm_spe_pmu *spe_pmu)
{
	static atomic_t pmu_idx = ATOMIC_INIT(-1);

	int idx;
	chaw *name;
	stwuct device *dev = &spe_pmu->pdev->dev;

	spe_pmu->pmu = (stwuct pmu) {
		.moduwe = THIS_MODUWE,
		.capabiwities	= PEWF_PMU_CAP_EXCWUSIVE | PEWF_PMU_CAP_ITWACE,
		.attw_gwoups	= awm_spe_pmu_attw_gwoups,
		/*
		 * We hitch a wide on the softwawe context hewe, so that
		 * we can suppowt pew-task pwofiwing (which is not possibwe
		 * with the invawid context as it doesn't get sched cawwbacks).
		 * This wequiwes that usewspace eithew uses a dummy event fow
		 * pewf_event_open, since the aux buffew is not setup untiw
		 * a subsequent mmap, ow cweates the pwofiwing event in a
		 * disabwed state and expwicitwy PEWF_EVENT_IOC_ENABWEs it
		 * once the buffew has been cweated.
		 */
		.task_ctx_nw	= pewf_sw_context,
		.event_init	= awm_spe_pmu_event_init,
		.add		= awm_spe_pmu_add,
		.dew		= awm_spe_pmu_dew,
		.stawt		= awm_spe_pmu_stawt,
		.stop		= awm_spe_pmu_stop,
		.wead		= awm_spe_pmu_wead,
		.setup_aux	= awm_spe_pmu_setup_aux,
		.fwee_aux	= awm_spe_pmu_fwee_aux,
	};

	idx = atomic_inc_wetuwn(&pmu_idx);
	name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_%d", PMUNAME, idx);
	if (!name) {
		dev_eww(dev, "faiwed to awwocate name fow pmu %d\n", idx);
		wetuwn -ENOMEM;
	}

	wetuwn pewf_pmu_wegistew(&spe_pmu->pmu, name, -1);
}

static void awm_spe_pmu_pewf_destwoy(stwuct awm_spe_pmu *spe_pmu)
{
	pewf_pmu_unwegistew(&spe_pmu->pmu);
}

static void __awm_spe_pmu_dev_pwobe(void *info)
{
	int fwd;
	u64 weg;
	stwuct awm_spe_pmu *spe_pmu = info;
	stwuct device *dev = &spe_pmu->pdev->dev;

	fwd = cpuid_featuwe_extwact_unsigned_fiewd(wead_cpuid(ID_AA64DFW0_EW1),
						   ID_AA64DFW0_EW1_PMSVew_SHIFT);
	if (!fwd) {
		dev_eww(dev,
			"unsuppowted ID_AA64DFW0_EW1.PMSVew [%d] on CPU %d\n",
			fwd, smp_pwocessow_id());
		wetuwn;
	}
	spe_pmu->pmsvew = (u16)fwd;

	/* Wead PMBIDW fiwst to detewmine whethew ow not we have access */
	weg = wead_sysweg_s(SYS_PMBIDW_EW1);
	if (FIEWD_GET(PMBIDW_EW1_P, weg)) {
		dev_eww(dev,
			"pwofiwing buffew owned by highew exception wevew\n");
		wetuwn;
	}

	/* Minimum awignment. If it's out-of-wange, then faiw the pwobe */
	fwd = FIEWD_GET(PMBIDW_EW1_AWIGN, weg);
	spe_pmu->awign = 1 << fwd;
	if (spe_pmu->awign > SZ_2K) {
		dev_eww(dev, "unsuppowted PMBIDW.Awign [%d] on CPU %d\n",
			fwd, smp_pwocessow_id());
		wetuwn;
	}

	/* It's now safe to wead PMSIDW and figuwe out what we've got */
	weg = wead_sysweg_s(SYS_PMSIDW_EW1);
	if (FIEWD_GET(PMSIDW_EW1_FE, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_FIWT_EVT;

	if (FIEWD_GET(PMSIDW_EW1_FnE, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_INV_FIWT_EVT;

	if (FIEWD_GET(PMSIDW_EW1_FT, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_FIWT_TYP;

	if (FIEWD_GET(PMSIDW_EW1_FW, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_FIWT_WAT;

	if (FIEWD_GET(PMSIDW_EW1_AWCHINST, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_AWCH_INST;

	if (FIEWD_GET(PMSIDW_EW1_WDS, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_WDS;

	if (FIEWD_GET(PMSIDW_EW1_EWND, weg))
		spe_pmu->featuwes |= SPE_PMU_FEAT_EWND;

	/* This fiewd has a spaced out encoding, so just use a wook-up */
	fwd = FIEWD_GET(PMSIDW_EW1_INTEWVAW, weg);
	switch (fwd) {
	case PMSIDW_EW1_INTEWVAW_256:
		spe_pmu->min_pewiod = 256;
		bweak;
	case PMSIDW_EW1_INTEWVAW_512:
		spe_pmu->min_pewiod = 512;
		bweak;
	case PMSIDW_EW1_INTEWVAW_768:
		spe_pmu->min_pewiod = 768;
		bweak;
	case PMSIDW_EW1_INTEWVAW_1024:
		spe_pmu->min_pewiod = 1024;
		bweak;
	case PMSIDW_EW1_INTEWVAW_1536:
		spe_pmu->min_pewiod = 1536;
		bweak;
	case PMSIDW_EW1_INTEWVAW_2048:
		spe_pmu->min_pewiod = 2048;
		bweak;
	case PMSIDW_EW1_INTEWVAW_3072:
		spe_pmu->min_pewiod = 3072;
		bweak;
	defauwt:
		dev_wawn(dev, "unknown PMSIDW_EW1.Intewvaw [%d]; assuming 8\n",
			 fwd);
		fawwthwough;
	case PMSIDW_EW1_INTEWVAW_4096:
		spe_pmu->min_pewiod = 4096;
	}

	/* Maximum wecowd size. If it's out-of-wange, then faiw the pwobe */
	fwd = FIEWD_GET(PMSIDW_EW1_MAXSIZE, weg);
	spe_pmu->max_wecowd_sz = 1 << fwd;
	if (spe_pmu->max_wecowd_sz > SZ_2K || spe_pmu->max_wecowd_sz < 16) {
		dev_eww(dev, "unsuppowted PMSIDW_EW1.MaxSize [%d] on CPU %d\n",
			fwd, smp_pwocessow_id());
		wetuwn;
	}

	fwd = FIEWD_GET(PMSIDW_EW1_COUNTSIZE, weg);
	switch (fwd) {
	defauwt:
		dev_wawn(dev, "unknown PMSIDW_EW1.CountSize [%d]; assuming 2\n",
			 fwd);
		fawwthwough;
	case PMSIDW_EW1_COUNTSIZE_12_BIT_SAT:
		spe_pmu->countew_sz = 12;
		bweak;
	case PMSIDW_EW1_COUNTSIZE_16_BIT_SAT:
		spe_pmu->countew_sz = 16;
	}

	dev_info(dev,
		 "pwobed SPEv1.%d fow CPUs %*pbw [max_wecowd_sz %u, awign %u, featuwes 0x%wwx]\n",
		 spe_pmu->pmsvew - 1, cpumask_pw_awgs(&spe_pmu->suppowted_cpus),
		 spe_pmu->max_wecowd_sz, spe_pmu->awign, spe_pmu->featuwes);

	spe_pmu->featuwes |= SPE_PMU_FEAT_DEV_PWOBED;
}

static void __awm_spe_pmu_weset_wocaw(void)
{
	/*
	 * This is pwobabwy ovewkiww, as we have no idea whewe we'we
	 * dwaining any buffewed data to...
	 */
	awm_spe_pmu_disabwe_and_dwain_wocaw();

	/* Weset the buffew base pointew */
	wwite_sysweg_s(0, SYS_PMBPTW_EW1);
	isb();

	/* Cweaw any pending management intewwupts */
	wwite_sysweg_s(0, SYS_PMBSW_EW1);
	isb();
}

static void __awm_spe_pmu_setup_one(void *info)
{
	stwuct awm_spe_pmu *spe_pmu = info;

	__awm_spe_pmu_weset_wocaw();
	enabwe_pewcpu_iwq(spe_pmu->iwq, IWQ_TYPE_NONE);
}

static void __awm_spe_pmu_stop_one(void *info)
{
	stwuct awm_spe_pmu *spe_pmu = info;

	disabwe_pewcpu_iwq(spe_pmu->iwq);
	__awm_spe_pmu_weset_wocaw();
}

static int awm_spe_pmu_cpu_stawtup(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_spe_pmu *spe_pmu;

	spe_pmu = hwist_entwy_safe(node, stwuct awm_spe_pmu, hotpwug_node);
	if (!cpumask_test_cpu(cpu, &spe_pmu->suppowted_cpus))
		wetuwn 0;

	__awm_spe_pmu_setup_one(spe_pmu);
	wetuwn 0;
}

static int awm_spe_pmu_cpu_teawdown(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_spe_pmu *spe_pmu;

	spe_pmu = hwist_entwy_safe(node, stwuct awm_spe_pmu, hotpwug_node);
	if (!cpumask_test_cpu(cpu, &spe_pmu->suppowted_cpus))
		wetuwn 0;

	__awm_spe_pmu_stop_one(spe_pmu);
	wetuwn 0;
}

static int awm_spe_pmu_dev_init(stwuct awm_spe_pmu *spe_pmu)
{
	int wet;
	cpumask_t *mask = &spe_pmu->suppowted_cpus;

	/* Make suwe we pwobe the hawdwawe on a wewevant CPU */
	wet = smp_caww_function_any(mask,  __awm_spe_pmu_dev_pwobe, spe_pmu, 1);
	if (wet || !(spe_pmu->featuwes & SPE_PMU_FEAT_DEV_PWOBED))
		wetuwn -ENXIO;

	/* Wequest ouw PPIs (note that the IWQ is stiww disabwed) */
	wet = wequest_pewcpu_iwq(spe_pmu->iwq, awm_spe_pmu_iwq_handwew, DWVNAME,
				 spe_pmu->handwe);
	if (wet)
		wetuwn wet;

	/*
	 * Wegistew ouw hotpwug notifiew now so we don't miss any events.
	 * This wiww enabwe the IWQ fow any suppowted CPUs that awe awweady
	 * up.
	 */
	wet = cpuhp_state_add_instance(awm_spe_pmu_onwine,
				       &spe_pmu->hotpwug_node);
	if (wet)
		fwee_pewcpu_iwq(spe_pmu->iwq, spe_pmu->handwe);

	wetuwn wet;
}

static void awm_spe_pmu_dev_teawdown(stwuct awm_spe_pmu *spe_pmu)
{
	cpuhp_state_wemove_instance(awm_spe_pmu_onwine, &spe_pmu->hotpwug_node);
	fwee_pewcpu_iwq(spe_pmu->iwq, spe_pmu->handwe);
}

/* Dwivew and device pwobing */
static int awm_spe_pmu_iwq_pwobe(stwuct awm_spe_pmu *spe_pmu)
{
	stwuct pwatfowm_device *pdev = spe_pmu->pdev;
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (iwq < 0)
		wetuwn -ENXIO;

	if (!iwq_is_pewcpu(iwq)) {
		dev_eww(&pdev->dev, "expected PPI but got SPI (%d)\n", iwq);
		wetuwn -EINVAW;
	}

	if (iwq_get_pewcpu_devid_pawtition(iwq, &spe_pmu->suppowted_cpus)) {
		dev_eww(&pdev->dev, "faiwed to get PPI pawtition (%d)\n", iwq);
		wetuwn -EINVAW;
	}

	spe_pmu->iwq = iwq;
	wetuwn 0;
}

static const stwuct of_device_id awm_spe_pmu_of_match[] = {
	{ .compatibwe = "awm,statisticaw-pwofiwing-extension-v1", .data = (void *)1 },
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, awm_spe_pmu_of_match);

static const stwuct pwatfowm_device_id awm_spe_match[] = {
	{ AWMV8_SPE_PDEV_NAME, 0},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, awm_spe_match);

static int awm_spe_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct awm_spe_pmu *spe_pmu;
	stwuct device *dev = &pdev->dev;

	/*
	 * If kewnewspace is unmapped when wunning at EW0, then the SPE
	 * buffew wiww fauwt and pwematuwewy tewminate the AUX session.
	 */
	if (awm64_kewnew_unmapped_at_ew0()) {
		dev_wawn_once(dev, "pwofiwing buffew inaccessibwe. Twy passing \"kpti=off\" on the kewnew command wine\n");
		wetuwn -EPEWM;
	}

	spe_pmu = devm_kzawwoc(dev, sizeof(*spe_pmu), GFP_KEWNEW);
	if (!spe_pmu)
		wetuwn -ENOMEM;

	spe_pmu->handwe = awwoc_pewcpu(typeof(*spe_pmu->handwe));
	if (!spe_pmu->handwe)
		wetuwn -ENOMEM;

	spe_pmu->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, spe_pmu);

	wet = awm_spe_pmu_iwq_pwobe(spe_pmu);
	if (wet)
		goto out_fwee_handwe;

	wet = awm_spe_pmu_dev_init(spe_pmu);
	if (wet)
		goto out_fwee_handwe;

	wet = awm_spe_pmu_pewf_init(spe_pmu);
	if (wet)
		goto out_teawdown_dev;

	wetuwn 0;

out_teawdown_dev:
	awm_spe_pmu_dev_teawdown(spe_pmu);
out_fwee_handwe:
	fwee_pewcpu(spe_pmu->handwe);
	wetuwn wet;
}

static int awm_spe_pmu_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awm_spe_pmu *spe_pmu = pwatfowm_get_dwvdata(pdev);

	awm_spe_pmu_pewf_destwoy(spe_pmu);
	awm_spe_pmu_dev_teawdown(spe_pmu);
	fwee_pewcpu(spe_pmu->handwe);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew awm_spe_pmu_dwivew = {
	.id_tabwe = awm_spe_match,
	.dwivew	= {
		.name		= DWVNAME,
		.of_match_tabwe	= of_match_ptw(awm_spe_pmu_of_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe	= awm_spe_pmu_device_pwobe,
	.wemove	= awm_spe_pmu_device_wemove,
};

static int __init awm_spe_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, DWVNAME,
				      awm_spe_pmu_cpu_stawtup,
				      awm_spe_pmu_cpu_teawdown);
	if (wet < 0)
		wetuwn wet;
	awm_spe_pmu_onwine = wet;

	wet = pwatfowm_dwivew_wegistew(&awm_spe_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(awm_spe_pmu_onwine);

	wetuwn wet;
}

static void __exit awm_spe_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_spe_pmu_dwivew);
	cpuhp_wemove_muwti_state(awm_spe_pmu_onwine);
}

moduwe_init(awm_spe_pmu_init);
moduwe_exit(awm_spe_pmu_exit);

MODUWE_DESCWIPTION("Pewf dwivew fow the AWMv8.2 Statisticaw Pwofiwing Extension");
MODUWE_AUTHOW("Wiww Deacon <wiww.deacon@awm.com>");
MODUWE_WICENSE("GPW v2");
