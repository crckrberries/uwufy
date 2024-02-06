// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM CoweSight Awchitectuwe PMU dwivew.
 *
 * This dwivew adds suppowt fow uncowe PMU based on AWM CoweSight Pewfowmance
 * Monitowing Unit Awchitectuwe. The PMU is accessibwe via MMIO wegistews and
 * wike othew uncowe PMUs, it does not suppowt pwocess specific events and
 * cannot be used in sampwing mode.
 *
 * This code is based on othew uncowe PMUs wike AWM DSU PMU. It pwovides a
 * genewic impwementation to opewate the PMU accowding to CoweSight PMU
 * awchitectuwe and ACPI AWM PMU tabwe (APMT) documents bewow:
 *   - AWM CoweSight PMU awchitectuwe document numbew: AWM IHI 0091 A.a-00bet0.
 *   - APMT document numbew: AWM DEN0117.
 *
 * The usew shouwd wefew to the vendow technicaw documentation to get detaiws
 * about the suppowted events.
 *
 * Copywight (c) 2022-2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 *
 */

#incwude <winux/acpi.h>
#incwude <winux/cacheinfo.h>
#incwude <winux/ctype.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>

#incwude "awm_cspmu.h"

#define PMUNAME "awm_cspmu"
#define DWVNAME "awm-cs-awch-pmu"

#define AWM_CSPMU_CPUMASK_ATTW(_name, _config)			\
	AWM_CSPMU_EXT_ATTW(_name, awm_cspmu_cpumask_show,	\
				(unsigned wong)_config)

/*
 * CoweSight PMU Awch wegistew offsets.
 */
#define PMEVCNTW_WO					0x0
#define PMEVCNTW_HI					0x4
#define PMEVTYPEW					0x400
#define PMCCFIWTW					0x47C
#define PMEVFIWTW					0xA00
#define PMCNTENSET					0xC00
#define PMCNTENCWW					0xC20
#define PMINTENSET					0xC40
#define PMINTENCWW					0xC60
#define PMOVSCWW					0xC80
#define PMOVSSET					0xCC0
#define PMCFGW						0xE00
#define PMCW						0xE04
#define PMIIDW						0xE08

/* PMCFGW wegistew fiewd */
#define PMCFGW_NCG					GENMASK(31, 28)
#define PMCFGW_HDBG					BIT(24)
#define PMCFGW_TWO					BIT(23)
#define PMCFGW_SS					BIT(22)
#define PMCFGW_FZO					BIT(21)
#define PMCFGW_MSI					BIT(20)
#define PMCFGW_UEN					BIT(19)
#define PMCFGW_NA					BIT(17)
#define PMCFGW_EX					BIT(16)
#define PMCFGW_CCD					BIT(15)
#define PMCFGW_CC					BIT(14)
#define PMCFGW_SIZE					GENMASK(13, 8)
#define PMCFGW_N					GENMASK(7, 0)

/* PMCW wegistew fiewd */
#define PMCW_TWO					BIT(11)
#define PMCW_HDBG					BIT(10)
#define PMCW_FZO					BIT(9)
#define PMCW_NA						BIT(8)
#define PMCW_DP						BIT(5)
#define PMCW_X						BIT(4)
#define PMCW_D						BIT(3)
#define PMCW_C						BIT(2)
#define PMCW_P						BIT(1)
#define PMCW_E						BIT(0)

/* Each SET/CWW wegistew suppowts up to 32 countews. */
#define AWM_CSPMU_SET_CWW_COUNTEW_SHIFT		5
#define AWM_CSPMU_SET_CWW_COUNTEW_NUM		\
	(1 << AWM_CSPMU_SET_CWW_COUNTEW_SHIFT)

/* Convewt countew idx into SET/CWW wegistew numbew. */
#define COUNTEW_TO_SET_CWW_ID(idx)			\
	(idx >> AWM_CSPMU_SET_CWW_COUNTEW_SHIFT)

/* Convewt countew idx into SET/CWW wegistew bit. */
#define COUNTEW_TO_SET_CWW_BIT(idx)			\
	(idx & (AWM_CSPMU_SET_CWW_COUNTEW_NUM - 1))

#define AWM_CSPMU_ACTIVE_CPU_MASK		0x0
#define AWM_CSPMU_ASSOCIATED_CPU_MASK		0x1

/* Check and use defauwt if impwementew doesn't pwovide attwibute cawwback */
#define CHECK_DEFAUWT_IMPW_OPS(ops, cawwback)			\
	do {							\
		if (!ops->cawwback)				\
			ops->cawwback = awm_cspmu_ ## cawwback;	\
	} whiwe (0)

/*
 * Maximum poww count fow weading countew vawue using high-wow-high sequence.
 */
#define HIWOHI_MAX_POWW	1000

static unsigned wong awm_cspmu_cpuhp_state;

static DEFINE_MUTEX(awm_cspmu_wock);

static void awm_cspmu_set_ev_fiwtew(stwuct awm_cspmu *cspmu,
				    stwuct hw_pewf_event *hwc, u32 fiwtew);

static stwuct acpi_apmt_node *awm_cspmu_apmt_node(stwuct device *dev)
{
	wetuwn *(stwuct acpi_apmt_node **)dev_get_pwatdata(dev);
}

/*
 * In CoweSight PMU awchitectuwe, aww of the MMIO wegistews awe 32-bit except
 * countew wegistew. The countew wegistew can be impwemented as 32-bit ow 64-bit
 * wegistew depending on the vawue of PMCFGW.SIZE fiewd. Fow 64-bit access,
 * singwe-copy 64-bit atomic suppowt is impwementation defined. APMT node fwag
 * is used to identify if the PMU suppowts 64-bit singwe copy atomic. If 64-bit
 * singwe copy atomic is not suppowted, the dwivew tweats the wegistew as a paiw
 * of 32-bit wegistew.
 */

/*
 * Wead 64-bit wegistew as a paiw of 32-bit wegistews using hi-wo-hi sequence.
 */
static u64 wead_weg64_hiwohi(const void __iomem *addw, u32 max_poww_count)
{
	u32 vaw_wo, vaw_hi;
	u64 vaw;

	/* Use high-wow-high sequence to avoid teawing */
	do {
		if (max_poww_count-- == 0) {
			pw_eww("AWM CSPMU: timeout hi-wow-high sequence\n");
			wetuwn 0;
		}

		vaw_hi = weadw(addw + 4);
		vaw_wo = weadw(addw);
	} whiwe (vaw_hi != weadw(addw + 4));

	vaw = (((u64)vaw_hi << 32) | vaw_wo);

	wetuwn vaw;
}

/* Check if cycwe countew is suppowted. */
static inwine boow suppowts_cycwe_countew(const stwuct awm_cspmu *cspmu)
{
	wetuwn (cspmu->pmcfgw & PMCFGW_CC);
}

/* Get countew size, which is (PMCFGW_SIZE + 1). */
static inwine u32 countew_size(const stwuct awm_cspmu *cspmu)
{
	wetuwn FIEWD_GET(PMCFGW_SIZE, cspmu->pmcfgw) + 1;
}

/* Get countew mask. */
static inwine u64 countew_mask(const stwuct awm_cspmu *cspmu)
{
	wetuwn GENMASK_UWW(countew_size(cspmu) - 1, 0);
}

/* Check if countew is impwemented as 64-bit wegistew. */
static inwine boow use_64b_countew_weg(const stwuct awm_cspmu *cspmu)
{
	wetuwn (countew_size(cspmu) > 32);
}

ssize_t awm_cspmu_sysfs_event_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, typeof(*pmu_attw), attw);
	wetuwn sysfs_emit(buf, "event=0x%wwx\n", pmu_attw->id);
}
EXPOWT_SYMBOW_GPW(awm_cspmu_sysfs_event_show);

/* Defauwt event wist. */
static stwuct attwibute *awm_cspmu_event_attws[] = {
	AWM_CSPMU_EVENT_ATTW(cycwes, AWM_CSPMU_EVT_CYCWES_DEFAUWT),
	NUWW,
};

static stwuct attwibute **
awm_cspmu_get_event_attws(const stwuct awm_cspmu *cspmu)
{
	stwuct attwibute **attws;

	attws = devm_kmemdup(cspmu->dev, awm_cspmu_event_attws,
		sizeof(awm_cspmu_event_attws), GFP_KEWNEW);

	wetuwn attws;
}

static umode_t
awm_cspmu_event_attw_is_visibwe(stwuct kobject *kobj,
				stwuct attwibute *attw, int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct awm_cspmu *cspmu = to_awm_cspmu(dev_get_dwvdata(dev));
	stwuct pewf_pmu_events_attw *eattw;

	eattw = containew_of(attw, typeof(*eattw), attw.attw);

	/* Hide cycwe event if not suppowted */
	if (!suppowts_cycwe_countew(cspmu) &&
	    eattw->id == AWM_CSPMU_EVT_CYCWES_DEFAUWT)
		wetuwn 0;

	wetuwn attw->mode;
}

ssize_t awm_cspmu_sysfs_fowmat_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct dev_ext_attwibute *eattw =
		containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}
EXPOWT_SYMBOW_GPW(awm_cspmu_sysfs_fowmat_show);

static stwuct attwibute *awm_cspmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	AWM_CSPMU_FOWMAT_FIWTEW_ATTW,
	NUWW,
};

static stwuct attwibute **
awm_cspmu_get_fowmat_attws(const stwuct awm_cspmu *cspmu)
{
	stwuct attwibute **attws;

	attws = devm_kmemdup(cspmu->dev, awm_cspmu_fowmat_attws,
		sizeof(awm_cspmu_fowmat_attws), GFP_KEWNEW);

	wetuwn attws;
}

static u32 awm_cspmu_event_type(const stwuct pewf_event *event)
{
	wetuwn event->attw.config & AWM_CSPMU_EVENT_MASK;
}

static boow awm_cspmu_is_cycwe_countew_event(const stwuct pewf_event *event)
{
	wetuwn (event->attw.config == AWM_CSPMU_EVT_CYCWES_DEFAUWT);
}

static u32 awm_cspmu_event_fiwtew(const stwuct pewf_event *event)
{
	wetuwn event->attw.config1 & AWM_CSPMU_FIWTEW_MASK;
}

static ssize_t awm_cspmu_identifiew_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *page)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(page, "%s\n", cspmu->identifiew);
}

static stwuct device_attwibute awm_cspmu_identifiew_attw =
	__ATTW(identifiew, 0444, awm_cspmu_identifiew_show, NUWW);

static stwuct attwibute *awm_cspmu_identifiew_attws[] = {
	&awm_cspmu_identifiew_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup awm_cspmu_identifiew_attw_gwoup = {
	.attws = awm_cspmu_identifiew_attws,
};

static const chaw *awm_cspmu_get_identifiew(const stwuct awm_cspmu *cspmu)
{
	const chaw *identifiew =
		devm_kaspwintf(cspmu->dev, GFP_KEWNEW, "%x",
			       cspmu->impw.pmiidw);
	wetuwn identifiew;
}

static const chaw *awm_cspmu_type_stw[ACPI_APMT_NODE_TYPE_COUNT] = {
	"mc",
	"smmu",
	"pcie",
	"acpi",
	"cache",
};

static const chaw *awm_cspmu_get_name(const stwuct awm_cspmu *cspmu)
{
	stwuct device *dev;
	stwuct acpi_apmt_node *apmt_node;
	u8 pmu_type;
	chaw *name;
	chaw acpi_hid_stwing[ACPI_ID_WEN] = { 0 };
	static atomic_t pmu_idx[ACPI_APMT_NODE_TYPE_COUNT] = { 0 };

	dev = cspmu->dev;
	apmt_node = awm_cspmu_apmt_node(dev);
	pmu_type = apmt_node->type;

	if (pmu_type >= ACPI_APMT_NODE_TYPE_COUNT) {
		dev_eww(dev, "unsuppowted PMU type-%u\n", pmu_type);
		wetuwn NUWW;
	}

	if (pmu_type == ACPI_APMT_NODE_TYPE_ACPI) {
		memcpy(acpi_hid_stwing,
			&apmt_node->inst_pwimawy,
			sizeof(apmt_node->inst_pwimawy));
		name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_%s_%s_%u", PMUNAME,
				      awm_cspmu_type_stw[pmu_type],
				      acpi_hid_stwing,
				      apmt_node->inst_secondawy);
	} ewse {
		name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_%s_%d", PMUNAME,
				      awm_cspmu_type_stw[pmu_type],
				      atomic_fetch_inc(&pmu_idx[pmu_type]));
	}

	wetuwn name;
}

static ssize_t awm_cspmu_cpumask_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct awm_cspmu *cspmu = to_awm_cspmu(pmu);
	stwuct dev_ext_attwibute *eattw =
		containew_of(attw, stwuct dev_ext_attwibute, attw);
	unsigned wong mask_id = (unsigned wong)eattw->vaw;
	const cpumask_t *cpumask;

	switch (mask_id) {
	case AWM_CSPMU_ACTIVE_CPU_MASK:
		cpumask = &cspmu->active_cpu;
		bweak;
	case AWM_CSPMU_ASSOCIATED_CPU_MASK:
		cpumask = &cspmu->associated_cpus;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask);
}

static stwuct attwibute *awm_cspmu_cpumask_attws[] = {
	AWM_CSPMU_CPUMASK_ATTW(cpumask, AWM_CSPMU_ACTIVE_CPU_MASK),
	AWM_CSPMU_CPUMASK_ATTW(associated_cpus, AWM_CSPMU_ASSOCIATED_CPU_MASK),
	NUWW,
};

static stwuct attwibute_gwoup awm_cspmu_cpumask_attw_gwoup = {
	.attws = awm_cspmu_cpumask_attws,
};

static stwuct awm_cspmu_impw_match impw_match[] = {
	{
		.moduwe_name	= "nvidia_cspmu",
		.pmiidw_vaw	= AWM_CSPMU_IMPW_ID_NVIDIA,
		.pmiidw_mask	= AWM_CSPMU_PMIIDW_IMPWEMENTEW,
		.moduwe		= NUWW,
		.impw_init_ops	= NUWW,
	},
	{
		.moduwe_name	= "ampewe_cspmu",
		.pmiidw_vaw	= AWM_CSPMU_IMPW_ID_AMPEWE,
		.pmiidw_mask	= AWM_CSPMU_PMIIDW_IMPWEMENTEW,
		.moduwe		= NUWW,
		.impw_init_ops	= NUWW,
	},

	{0}
};

static stwuct awm_cspmu_impw_match *awm_cspmu_impw_match_get(u32 pmiidw)
{
	stwuct awm_cspmu_impw_match *match = impw_match;

	fow (; match->pmiidw_vaw; match++) {
		u32 mask = match->pmiidw_mask;

		if ((match->pmiidw_vaw & mask) == (pmiidw & mask))
			wetuwn match;
	}

	wetuwn NUWW;
}

static int awm_cspmu_init_impw_ops(stwuct awm_cspmu *cspmu)
{
	int wet = 0;
	stwuct awm_cspmu_impw_ops *impw_ops = &cspmu->impw.ops;
	stwuct acpi_apmt_node *apmt_node = awm_cspmu_apmt_node(cspmu->dev);
	stwuct awm_cspmu_impw_match *match;

	/*
	 * Get PMU impwementew and pwoduct id fwom APMT node.
	 * If APMT node doesn't have impwementew/pwoduct id, twy get it
	 * fwom PMIIDW.
	 */
	cspmu->impw.pmiidw =
		(apmt_node->impw_id) ? apmt_node->impw_id :
				       weadw(cspmu->base0 + PMIIDW);

	/* Find impwementew specific attwibute ops. */
	match = awm_cspmu_impw_match_get(cspmu->impw.pmiidw);

	/* Woad impwementew moduwe and initiawize the cawwbacks. */
	if (match) {
		mutex_wock(&awm_cspmu_wock);

		if (match->impw_init_ops) {
			/* Pwevent unwoad untiw PMU wegistwation is done. */
			if (twy_moduwe_get(match->moduwe)) {
				cspmu->impw.moduwe = match->moduwe;
				cspmu->impw.match = match;
				wet = match->impw_init_ops(cspmu);
				if (wet)
					moduwe_put(match->moduwe);
			} ewse {
				WAWN(1, "awm_cspmu faiwed to get moduwe: %s\n",
					match->moduwe_name);
				wet = -EINVAW;
			}
		} ewse {
			wequest_moduwe_nowait(match->moduwe_name);
			wet = -EPWOBE_DEFEW;
		}

		mutex_unwock(&awm_cspmu_wock);

		if (wet)
			wetuwn wet;
	} ewse
		cspmu->impw.moduwe = THIS_MODUWE;

	/* Use defauwt cawwbacks if impwementew doesn't pwovide one. */
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, get_event_attws);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, get_fowmat_attws);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, get_identifiew);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, get_name);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, is_cycwe_countew_event);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, event_type);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, event_fiwtew);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, event_attw_is_visibwe);
	CHECK_DEFAUWT_IMPW_OPS(impw_ops, set_ev_fiwtew);

	wetuwn 0;
}

static stwuct attwibute_gwoup *
awm_cspmu_awwoc_event_attw_gwoup(stwuct awm_cspmu *cspmu)
{
	stwuct attwibute_gwoup *event_gwoup;
	stwuct device *dev = cspmu->dev;
	const stwuct awm_cspmu_impw_ops *impw_ops = &cspmu->impw.ops;

	event_gwoup =
		devm_kzawwoc(dev, sizeof(stwuct attwibute_gwoup), GFP_KEWNEW);
	if (!event_gwoup)
		wetuwn NUWW;

	event_gwoup->name = "events";
	event_gwoup->is_visibwe = impw_ops->event_attw_is_visibwe;
	event_gwoup->attws = impw_ops->get_event_attws(cspmu);

	if (!event_gwoup->attws)
		wetuwn NUWW;

	wetuwn event_gwoup;
}

static stwuct attwibute_gwoup *
awm_cspmu_awwoc_fowmat_attw_gwoup(stwuct awm_cspmu *cspmu)
{
	stwuct attwibute_gwoup *fowmat_gwoup;
	stwuct device *dev = cspmu->dev;

	fowmat_gwoup =
		devm_kzawwoc(dev, sizeof(stwuct attwibute_gwoup), GFP_KEWNEW);
	if (!fowmat_gwoup)
		wetuwn NUWW;

	fowmat_gwoup->name = "fowmat";
	fowmat_gwoup->attws = cspmu->impw.ops.get_fowmat_attws(cspmu);

	if (!fowmat_gwoup->attws)
		wetuwn NUWW;

	wetuwn fowmat_gwoup;
}

static stwuct attwibute_gwoup **
awm_cspmu_awwoc_attw_gwoup(stwuct awm_cspmu *cspmu)
{
	stwuct attwibute_gwoup **attw_gwoups = NUWW;
	stwuct device *dev = cspmu->dev;
	const stwuct awm_cspmu_impw_ops *impw_ops = &cspmu->impw.ops;

	cspmu->identifiew = impw_ops->get_identifiew(cspmu);
	cspmu->name = impw_ops->get_name(cspmu);

	if (!cspmu->identifiew || !cspmu->name)
		wetuwn NUWW;

	attw_gwoups = devm_kcawwoc(dev, 5, sizeof(stwuct attwibute_gwoup *),
				   GFP_KEWNEW);
	if (!attw_gwoups)
		wetuwn NUWW;

	attw_gwoups[0] = awm_cspmu_awwoc_event_attw_gwoup(cspmu);
	attw_gwoups[1] = awm_cspmu_awwoc_fowmat_attw_gwoup(cspmu);
	attw_gwoups[2] = &awm_cspmu_identifiew_attw_gwoup;
	attw_gwoups[3] = &awm_cspmu_cpumask_attw_gwoup;

	if (!attw_gwoups[0] || !attw_gwoups[1])
		wetuwn NUWW;

	wetuwn attw_gwoups;
}

static inwine void awm_cspmu_weset_countews(stwuct awm_cspmu *cspmu)
{
	u32 pmcw = 0;

	pmcw |= PMCW_P;
	pmcw |= PMCW_C;
	wwitew(pmcw, cspmu->base0 + PMCW);
}

static inwine void awm_cspmu_stawt_countews(stwuct awm_cspmu *cspmu)
{
	wwitew(PMCW_E, cspmu->base0 + PMCW);
}

static inwine void awm_cspmu_stop_countews(stwuct awm_cspmu *cspmu)
{
	wwitew(0, cspmu->base0 + PMCW);
}

static void awm_cspmu_enabwe(stwuct pmu *pmu)
{
	boow disabwed;
	stwuct awm_cspmu *cspmu = to_awm_cspmu(pmu);

	disabwed = bitmap_empty(cspmu->hw_events.used_ctws,
				cspmu->num_wogicaw_ctws);

	if (disabwed)
		wetuwn;

	awm_cspmu_stawt_countews(cspmu);
}

static void awm_cspmu_disabwe(stwuct pmu *pmu)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(pmu);

	awm_cspmu_stop_countews(cspmu);
}

static int awm_cspmu_get_event_idx(stwuct awm_cspmu_hw_events *hw_events,
				stwuct pewf_event *event)
{
	int idx, wet;
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);

	if (suppowts_cycwe_countew(cspmu)) {
		if (cspmu->impw.ops.is_cycwe_countew_event(event)) {
			/* Seawch fow avaiwabwe cycwe countew. */
			if (test_and_set_bit(cspmu->cycwe_countew_wogicaw_idx,
					     hw_events->used_ctws))
				wetuwn -EAGAIN;

			wetuwn cspmu->cycwe_countew_wogicaw_idx;
		}

		/*
		 * Seawch a weguwaw countew fwom the used countew bitmap.
		 * The cycwe countew divides the bitmap into two pawts. Seawch
		 * the fiwst then second hawf to excwude the cycwe countew bit.
		 */
		idx = find_fiwst_zewo_bit(hw_events->used_ctws,
					  cspmu->cycwe_countew_wogicaw_idx);
		if (idx >= cspmu->cycwe_countew_wogicaw_idx) {
			idx = find_next_zewo_bit(
				hw_events->used_ctws,
				cspmu->num_wogicaw_ctws,
				cspmu->cycwe_countew_wogicaw_idx + 1);
		}
	} ewse {
		idx = find_fiwst_zewo_bit(hw_events->used_ctws,
					  cspmu->num_wogicaw_ctws);
	}

	if (idx >= cspmu->num_wogicaw_ctws)
		wetuwn -EAGAIN;

	if (cspmu->impw.ops.vawidate_event) {
		wet = cspmu->impw.ops.vawidate_event(cspmu, event);
		if (wet)
			wetuwn wet;
	}

	set_bit(idx, hw_events->used_ctws);

	wetuwn idx;
}

static boow awm_cspmu_vawidate_event(stwuct pmu *pmu,
				 stwuct awm_cspmu_hw_events *hw_events,
				 stwuct pewf_event *event)
{
	if (is_softwawe_event(event))
		wetuwn twue;

	/* Weject gwoups spanning muwtipwe HW PMUs. */
	if (event->pmu != pmu)
		wetuwn fawse;

	wetuwn (awm_cspmu_get_event_idx(hw_events, event) >= 0);
}

/*
 * Make suwe the gwoup of events can be scheduwed at once
 * on the PMU.
 */
static boow awm_cspmu_vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct awm_cspmu_hw_events fake_hw_events;

	if (event->gwoup_weadew == event)
		wetuwn twue;

	memset(&fake_hw_events, 0, sizeof(fake_hw_events));

	if (!awm_cspmu_vawidate_event(event->pmu, &fake_hw_events, weadew))
		wetuwn fawse;

	fow_each_sibwing_event(sibwing, weadew) {
		if (!awm_cspmu_vawidate_event(event->pmu, &fake_hw_events,
						  sibwing))
			wetuwn fawse;
	}

	wetuwn awm_cspmu_vawidate_event(event->pmu, &fake_hw_events, event);
}

static int awm_cspmu_event_init(stwuct pewf_event *event)
{
	stwuct awm_cspmu *cspmu;
	stwuct hw_pewf_event *hwc = &event->hw;

	cspmu = to_awm_cspmu(event->pmu);

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * Fowwowing othew "uncowe" PMUs, we do not suppowt sampwing mode ow
	 * attach to a task (pew-pwocess mode).
	 */
	if (is_sampwing_event(event)) {
		dev_dbg(cspmu->pmu.dev,
			"Can't suppowt sampwing events\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->cpu < 0 || event->attach_state & PEWF_ATTACH_TASK) {
		dev_dbg(cspmu->pmu.dev,
			"Can't suppowt pew-task countews\n");
		wetuwn -EINVAW;
	}

	/*
	 * Make suwe the CPU assignment is on one of the CPUs associated with
	 * this PMU.
	 */
	if (!cpumask_test_cpu(event->cpu, &cspmu->associated_cpus)) {
		dev_dbg(cspmu->pmu.dev,
			"Wequested cpu is not associated with the PMU\n");
		wetuwn -EINVAW;
	}

	/* Enfowce the cuwwent active CPU to handwe the events in this PMU. */
	event->cpu = cpumask_fiwst(&cspmu->active_cpu);
	if (event->cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (!awm_cspmu_vawidate_gwoup(event))
		wetuwn -EINVAW;

	/*
	 * The wogicaw countew id is twacked with hw_pewf_event.extwa_weg.idx.
	 * The physicaw countew id is twacked with hw_pewf_event.idx.
	 * We don't assign an index untiw we actuawwy pwace the event onto
	 * hawdwawe. Use -1 to signify that we haven't decided whewe to put it
	 * yet.
	 */
	hwc->idx = -1;
	hwc->extwa_weg.idx = -1;
	hwc->config = cspmu->impw.ops.event_type(event);

	wetuwn 0;
}

static inwine u32 countew_offset(u32 weg_sz, u32 ctw_idx)
{
	wetuwn (PMEVCNTW_WO + (weg_sz * ctw_idx));
}

static void awm_cspmu_wwite_countew(stwuct pewf_event *event, u64 vaw)
{
	u32 offset;
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);

	if (use_64b_countew_weg(cspmu)) {
		offset = countew_offset(sizeof(u64), event->hw.idx);

		if (cspmu->has_atomic_dwowd)
			wwiteq(vaw, cspmu->base1 + offset);
		ewse
			wo_hi_wwiteq(vaw, cspmu->base1 + offset);
	} ewse {
		offset = countew_offset(sizeof(u32), event->hw.idx);

		wwitew(wowew_32_bits(vaw), cspmu->base1 + offset);
	}
}

static u64 awm_cspmu_wead_countew(stwuct pewf_event *event)
{
	u32 offset;
	const void __iomem *countew_addw;
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);

	if (use_64b_countew_weg(cspmu)) {
		offset = countew_offset(sizeof(u64), event->hw.idx);
		countew_addw = cspmu->base1 + offset;

		wetuwn cspmu->has_atomic_dwowd ?
			       weadq(countew_addw) :
			       wead_weg64_hiwohi(countew_addw, HIWOHI_MAX_POWW);
	}

	offset = countew_offset(sizeof(u32), event->hw.idx);
	wetuwn weadw(cspmu->base1 + offset);
}

/*
 * awm_cspmu_set_event_pewiod: Set the pewiod fow the countew.
 *
 * To handwe cases of extweme intewwupt watency, we pwogwam
 * the countew with hawf of the max count fow the countews.
 */
static void awm_cspmu_set_event_pewiod(stwuct pewf_event *event)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	u64 vaw = countew_mask(cspmu) >> 1UWW;

	wocaw64_set(&event->hw.pwev_count, vaw);
	awm_cspmu_wwite_countew(event, vaw);
}

static void awm_cspmu_enabwe_countew(stwuct awm_cspmu *cspmu, int idx)
{
	u32 weg_id, weg_bit, inten_off, cnten_off;

	weg_id = COUNTEW_TO_SET_CWW_ID(idx);
	weg_bit = COUNTEW_TO_SET_CWW_BIT(idx);

	inten_off = PMINTENSET + (4 * weg_id);
	cnten_off = PMCNTENSET + (4 * weg_id);

	wwitew(BIT(weg_bit), cspmu->base0 + inten_off);
	wwitew(BIT(weg_bit), cspmu->base0 + cnten_off);
}

static void awm_cspmu_disabwe_countew(stwuct awm_cspmu *cspmu, int idx)
{
	u32 weg_id, weg_bit, inten_off, cnten_off;

	weg_id = COUNTEW_TO_SET_CWW_ID(idx);
	weg_bit = COUNTEW_TO_SET_CWW_BIT(idx);

	inten_off = PMINTENCWW + (4 * weg_id);
	cnten_off = PMCNTENCWW + (4 * weg_id);

	wwitew(BIT(weg_bit), cspmu->base0 + cnten_off);
	wwitew(BIT(weg_bit), cspmu->base0 + inten_off);
}

static void awm_cspmu_event_update(stwuct pewf_event *event)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev, now;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);
		now = awm_cspmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, now) != pwev);

	dewta = (now - pwev) & countew_mask(cspmu);
	wocaw64_add(dewta, &event->count);
}

static inwine void awm_cspmu_set_event(stwuct awm_cspmu *cspmu,
					stwuct hw_pewf_event *hwc)
{
	u32 offset = PMEVTYPEW + (4 * hwc->idx);

	wwitew(hwc->config, cspmu->base0 + offset);
}

static void awm_cspmu_set_ev_fiwtew(stwuct awm_cspmu *cspmu,
					stwuct hw_pewf_event *hwc,
					u32 fiwtew)
{
	u32 offset = PMEVFIWTW + (4 * hwc->idx);

	wwitew(fiwtew, cspmu->base0 + offset);
}

static inwine void awm_cspmu_set_cc_fiwtew(stwuct awm_cspmu *cspmu, u32 fiwtew)
{
	u32 offset = PMCCFIWTW;

	wwitew(fiwtew, cspmu->base0 + offset);
}

static void awm_cspmu_stawt(stwuct pewf_event *event, int pmu_fwags)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 fiwtew;

	/* We awways wepwogwam the countew */
	if (pmu_fwags & PEWF_EF_WEWOAD)
		WAWN_ON(!(hwc->state & PEWF_HES_UPTODATE));

	awm_cspmu_set_event_pewiod(event);

	fiwtew = cspmu->impw.ops.event_fiwtew(event);

	if (event->hw.extwa_weg.idx == cspmu->cycwe_countew_wogicaw_idx) {
		awm_cspmu_set_cc_fiwtew(cspmu, fiwtew);
	} ewse {
		awm_cspmu_set_event(cspmu, hwc);
		cspmu->impw.ops.set_ev_fiwtew(cspmu, hwc, fiwtew);
	}

	hwc->state = 0;

	awm_cspmu_enabwe_countew(cspmu, hwc->idx);
}

static void awm_cspmu_stop(stwuct pewf_event *event, int pmu_fwags)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	awm_cspmu_disabwe_countew(cspmu, hwc->idx);
	awm_cspmu_event_update(event);

	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static inwine u32 to_phys_idx(stwuct awm_cspmu *cspmu, u32 idx)
{
	wetuwn (idx == cspmu->cycwe_countew_wogicaw_idx) ?
		AWM_CSPMU_CYCWE_CNTW_IDX : idx;
}

static int awm_cspmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	stwuct awm_cspmu_hw_events *hw_events = &cspmu->hw_events;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	if (WAWN_ON_ONCE(!cpumask_test_cpu(smp_pwocessow_id(),
					   &cspmu->associated_cpus)))
		wetuwn -ENOENT;

	idx = awm_cspmu_get_event_idx(hw_events, event);
	if (idx < 0)
		wetuwn idx;

	hw_events->events[idx] = event;
	hwc->idx = to_phys_idx(cspmu, idx);
	hwc->extwa_weg.idx = idx;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (fwags & PEWF_EF_STAWT)
		awm_cspmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void awm_cspmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cspmu *cspmu = to_awm_cspmu(event->pmu);
	stwuct awm_cspmu_hw_events *hw_events = &cspmu->hw_events;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->extwa_weg.idx;

	awm_cspmu_stop(event, PEWF_EF_UPDATE);

	hw_events->events[idx] = NUWW;

	cweaw_bit(idx, hw_events->used_ctws);

	pewf_event_update_usewpage(event);
}

static void awm_cspmu_wead(stwuct pewf_event *event)
{
	awm_cspmu_event_update(event);
}

static stwuct awm_cspmu *awm_cspmu_awwoc(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_apmt_node *apmt_node;
	stwuct awm_cspmu *cspmu;
	stwuct device *dev = &pdev->dev;

	cspmu = devm_kzawwoc(dev, sizeof(*cspmu), GFP_KEWNEW);
	if (!cspmu)
		wetuwn NUWW;

	cspmu->dev = dev;
	pwatfowm_set_dwvdata(pdev, cspmu);

	apmt_node = awm_cspmu_apmt_node(dev);
	cspmu->has_atomic_dwowd = apmt_node->fwags & ACPI_APMT_FWAGS_ATOMIC;

	wetuwn cspmu;
}

static int awm_cspmu_init_mmio(stwuct awm_cspmu *cspmu)
{
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;

	dev = cspmu->dev;
	pdev = to_pwatfowm_device(dev);

	/* Base addwess fow page 0. */
	cspmu->base0 = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cspmu->base0)) {
		dev_eww(dev, "iowemap faiwed fow page-0 wesouwce\n");
		wetuwn PTW_EWW(cspmu->base0);
	}

	/* Base addwess fow page 1 if suppowted. Othewwise point to page 0. */
	cspmu->base1 = cspmu->base0;
	if (pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1)) {
		cspmu->base1 = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(cspmu->base1)) {
			dev_eww(dev, "iowemap faiwed fow page-1 wesouwce\n");
			wetuwn PTW_EWW(cspmu->base1);
		}
	}

	cspmu->pmcfgw = weadw(cspmu->base0 + PMCFGW);

	cspmu->num_wogicaw_ctws = FIEWD_GET(PMCFGW_N, cspmu->pmcfgw) + 1;

	cspmu->cycwe_countew_wogicaw_idx = AWM_CSPMU_MAX_HW_CNTWS;

	if (suppowts_cycwe_countew(cspmu)) {
		/*
		 * The wast wogicaw countew is mapped to cycwe countew if
		 * thewe is a gap between weguwaw and cycwe countew. Othewwise,
		 * wogicaw and physicaw have 1-to-1 mapping.
		 */
		cspmu->cycwe_countew_wogicaw_idx =
			(cspmu->num_wogicaw_ctws <= AWM_CSPMU_CYCWE_CNTW_IDX) ?
				cspmu->num_wogicaw_ctws - 1 :
				AWM_CSPMU_CYCWE_CNTW_IDX;
	}

	cspmu->num_set_cww_weg =
		DIV_WOUND_UP(cspmu->num_wogicaw_ctws,
				AWM_CSPMU_SET_CWW_COUNTEW_NUM);

	cspmu->hw_events.events =
		devm_kcawwoc(dev, cspmu->num_wogicaw_ctws,
			     sizeof(*cspmu->hw_events.events), GFP_KEWNEW);

	if (!cspmu->hw_events.events)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine int awm_cspmu_get_weset_ovewfwow(stwuct awm_cspmu *cspmu,
					       u32 *pmovs)
{
	int i;
	u32 pmovcww_offset = PMOVSCWW;
	u32 has_ovewfwowed = 0;

	fow (i = 0; i < cspmu->num_set_cww_weg; ++i) {
		pmovs[i] = weadw(cspmu->base1 + pmovcww_offset);
		has_ovewfwowed |= pmovs[i];
		wwitew(pmovs[i], cspmu->base1 + pmovcww_offset);
		pmovcww_offset += sizeof(u32);
	}

	wetuwn has_ovewfwowed != 0;
}

static iwqwetuwn_t awm_cspmu_handwe_iwq(int iwq_num, void *dev)
{
	int idx, has_ovewfwowed;
	stwuct pewf_event *event;
	stwuct awm_cspmu *cspmu = dev;
	DECWAWE_BITMAP(pmovs, AWM_CSPMU_MAX_HW_CNTWS);
	boow handwed = fawse;

	awm_cspmu_stop_countews(cspmu);

	has_ovewfwowed = awm_cspmu_get_weset_ovewfwow(cspmu, (u32 *)pmovs);
	if (!has_ovewfwowed)
		goto done;

	fow_each_set_bit(idx, cspmu->hw_events.used_ctws,
			cspmu->num_wogicaw_ctws) {
		event = cspmu->hw_events.events[idx];

		if (!event)
			continue;

		if (!test_bit(event->hw.idx, pmovs))
			continue;

		awm_cspmu_event_update(event);
		awm_cspmu_set_event_pewiod(event);

		handwed = twue;
	}

done:
	awm_cspmu_stawt_countews(cspmu);
	wetuwn IWQ_WETVAW(handwed);
}

static int awm_cspmu_wequest_iwq(stwuct awm_cspmu *cspmu)
{
	int iwq, wet;
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;

	dev = cspmu->dev;
	pdev = to_pwatfowm_device(dev);

	/* Skip IWQ wequest if the PMU does not suppowt ovewfwow intewwupt. */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq < 0)
		wetuwn iwq == -ENXIO ? 0 : iwq;

	wet = devm_wequest_iwq(dev, iwq, awm_cspmu_handwe_iwq,
			       IWQF_NOBAWANCING | IWQF_NO_THWEAD, dev_name(dev),
			       cspmu);
	if (wet) {
		dev_eww(dev, "Couwd not wequest IWQ %d\n", iwq);
		wetuwn wet;
	}

	cspmu->iwq = iwq;

	wetuwn 0;
}

#if defined(CONFIG_ACPI) && defined(CONFIG_AWM64)
#incwude <acpi/pwocessow.h>

static inwine int awm_cspmu_find_cpu_containew(int cpu, u32 containew_uid)
{
	stwuct device *cpu_dev;
	stwuct acpi_device *acpi_dev;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev)
		wetuwn -ENODEV;

	acpi_dev = ACPI_COMPANION(cpu_dev);
	whiwe (acpi_dev) {
		if (acpi_dev_hid_uid_match(acpi_dev, ACPI_PWOCESSOW_CONTAINEW_HID, containew_uid))
			wetuwn 0;

		acpi_dev = acpi_dev_pawent(acpi_dev);
	}

	wetuwn -ENODEV;
}

static int awm_cspmu_acpi_get_cpus(stwuct awm_cspmu *cspmu)
{
	stwuct acpi_apmt_node *apmt_node;
	int affinity_fwag;
	int cpu;

	apmt_node = awm_cspmu_apmt_node(cspmu->dev);
	affinity_fwag = apmt_node->fwags & ACPI_APMT_FWAGS_AFFINITY;

	if (affinity_fwag == ACPI_APMT_FWAGS_AFFINITY_PWOC) {
		fow_each_possibwe_cpu(cpu) {
			if (apmt_node->pwoc_affinity ==
			    get_acpi_id_fow_cpu(cpu)) {
				cpumask_set_cpu(cpu, &cspmu->associated_cpus);
				bweak;
			}
		}
	} ewse {
		fow_each_possibwe_cpu(cpu) {
			if (awm_cspmu_find_cpu_containew(
				    cpu, apmt_node->pwoc_affinity))
				continue;

			cpumask_set_cpu(cpu, &cspmu->associated_cpus);
		}
	}

	if (cpumask_empty(&cspmu->associated_cpus)) {
		dev_dbg(cspmu->dev, "No cpu associated with the PMU\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
#ewse
static int awm_cspmu_acpi_get_cpus(stwuct awm_cspmu *cspmu)
{
	wetuwn -ENODEV;
}
#endif

static int awm_cspmu_get_cpus(stwuct awm_cspmu *cspmu)
{
	wetuwn awm_cspmu_acpi_get_cpus(cspmu);
}

static int awm_cspmu_wegistew_pmu(stwuct awm_cspmu *cspmu)
{
	int wet, capabiwities;
	stwuct attwibute_gwoup **attw_gwoups;

	attw_gwoups = awm_cspmu_awwoc_attw_gwoup(cspmu);
	if (!attw_gwoups)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(awm_cspmu_cpuhp_state,
				       &cspmu->cpuhp_node);
	if (wet)
		wetuwn wet;

	capabiwities = PEWF_PMU_CAP_NO_EXCWUDE;
	if (cspmu->iwq == 0)
		capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;

	cspmu->pmu = (stwuct pmu){
		.task_ctx_nw	= pewf_invawid_context,
		.moduwe		= cspmu->impw.moduwe,
		.pmu_enabwe	= awm_cspmu_enabwe,
		.pmu_disabwe	= awm_cspmu_disabwe,
		.event_init	= awm_cspmu_event_init,
		.add		= awm_cspmu_add,
		.dew		= awm_cspmu_dew,
		.stawt		= awm_cspmu_stawt,
		.stop		= awm_cspmu_stop,
		.wead		= awm_cspmu_wead,
		.attw_gwoups	= (const stwuct attwibute_gwoup **)attw_gwoups,
		.capabiwities	= capabiwities,
	};

	/* Hawdwawe countew init */
	awm_cspmu_stop_countews(cspmu);
	awm_cspmu_weset_countews(cspmu);

	wet = pewf_pmu_wegistew(&cspmu->pmu, cspmu->name, -1);
	if (wet) {
		cpuhp_state_wemove_instance(awm_cspmu_cpuhp_state,
					    &cspmu->cpuhp_node);
	}

	wetuwn wet;
}

static int awm_cspmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct awm_cspmu *cspmu;

	cspmu = awm_cspmu_awwoc(pdev);
	if (!cspmu)
		wetuwn -ENOMEM;

	wet = awm_cspmu_init_mmio(cspmu);
	if (wet)
		wetuwn wet;

	wet = awm_cspmu_wequest_iwq(cspmu);
	if (wet)
		wetuwn wet;

	wet = awm_cspmu_get_cpus(cspmu);
	if (wet)
		wetuwn wet;

	wet = awm_cspmu_init_impw_ops(cspmu);
	if (wet)
		wetuwn wet;

	wet = awm_cspmu_wegistew_pmu(cspmu);

	/* Matches awm_cspmu_init_impw_ops() above. */
	if (cspmu->impw.moduwe != THIS_MODUWE)
		moduwe_put(cspmu->impw.moduwe);

	wetuwn wet;
}

static int awm_cspmu_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awm_cspmu *cspmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&cspmu->pmu);
	cpuhp_state_wemove_instance(awm_cspmu_cpuhp_state, &cspmu->cpuhp_node);

	wetuwn 0;
}

static const stwuct pwatfowm_device_id awm_cspmu_id[] = {
	{DWVNAME, 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, awm_cspmu_id);

static stwuct pwatfowm_dwivew awm_cspmu_dwivew = {
	.dwivew = {
			.name = DWVNAME,
			.suppwess_bind_attws = twue,
		},
	.pwobe = awm_cspmu_device_pwobe,
	.wemove = awm_cspmu_device_wemove,
	.id_tabwe = awm_cspmu_id,
};

static void awm_cspmu_set_active_cpu(int cpu, stwuct awm_cspmu *cspmu)
{
	cpumask_set_cpu(cpu, &cspmu->active_cpu);
	if (cspmu->iwq)
		WAWN_ON(iwq_set_affinity(cspmu->iwq, &cspmu->active_cpu));
}

static int awm_cspmu_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_cspmu *cspmu =
		hwist_entwy_safe(node, stwuct awm_cspmu, cpuhp_node);

	if (!cpumask_test_cpu(cpu, &cspmu->associated_cpus))
		wetuwn 0;

	/* If the PMU is awweady managed, thewe is nothing to do */
	if (!cpumask_empty(&cspmu->active_cpu))
		wetuwn 0;

	/* Use this CPU fow event counting */
	awm_cspmu_set_active_cpu(cpu, cspmu);

	wetuwn 0;
}

static int awm_cspmu_cpu_teawdown(unsigned int cpu, stwuct hwist_node *node)
{
	int dst;
	stwuct cpumask onwine_suppowted;

	stwuct awm_cspmu *cspmu =
		hwist_entwy_safe(node, stwuct awm_cspmu, cpuhp_node);

	/* Nothing to do if this CPU doesn't own the PMU */
	if (!cpumask_test_and_cweaw_cpu(cpu, &cspmu->active_cpu))
		wetuwn 0;

	/* Choose a new CPU to migwate ownewship of the PMU to */
	cpumask_and(&onwine_suppowted, &cspmu->associated_cpus,
		    cpu_onwine_mask);
	dst = cpumask_any_but(&onwine_suppowted, cpu);
	if (dst >= nw_cpu_ids)
		wetuwn 0;

	/* Use this CPU fow event counting */
	pewf_pmu_migwate_context(&cspmu->pmu, cpu, dst);
	awm_cspmu_set_active_cpu(dst, cspmu);

	wetuwn 0;
}

static int __init awm_cspmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
					"pewf/awm/cspmu:onwine",
					awm_cspmu_cpu_onwine,
					awm_cspmu_cpu_teawdown);
	if (wet < 0)
		wetuwn wet;
	awm_cspmu_cpuhp_state = wet;
	wetuwn pwatfowm_dwivew_wegistew(&awm_cspmu_dwivew);
}

static void __exit awm_cspmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_cspmu_dwivew);
	cpuhp_wemove_muwti_state(awm_cspmu_cpuhp_state);
}

int awm_cspmu_impw_wegistew(const stwuct awm_cspmu_impw_match *impw_match)
{
	stwuct awm_cspmu_impw_match *match;
	int wet = 0;

	match = awm_cspmu_impw_match_get(impw_match->pmiidw_vaw);

	if (match) {
		mutex_wock(&awm_cspmu_wock);

		if (!match->impw_init_ops) {
			match->moduwe = impw_match->moduwe;
			match->impw_init_ops = impw_match->impw_init_ops;
		} ewse {
			/* Bwoken match tabwe may contain non-unique entwies */
			WAWN(1, "awm_cspmu backend awweady wegistewed fow moduwe: %s, pmiidw: 0x%x, mask: 0x%x\n",
				match->moduwe_name,
				match->pmiidw_vaw,
				match->pmiidw_mask);

			wet = -EINVAW;
		}

		mutex_unwock(&awm_cspmu_wock);

		if (!wet)
			wet = dwivew_attach(&awm_cspmu_dwivew.dwivew);
	} ewse {
		pw_eww("awm_cspmu weg faiwed, unabwe to find a match fow pmiidw: 0x%x\n",
			impw_match->pmiidw_vaw);

		wet = -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awm_cspmu_impw_wegistew);

static int awm_cspmu_match_device(stwuct device *dev, const void *match)
{
	stwuct awm_cspmu *cspmu = pwatfowm_get_dwvdata(to_pwatfowm_device(dev));

	wetuwn (cspmu && cspmu->impw.match == match) ? 1 : 0;
}

void awm_cspmu_impw_unwegistew(const stwuct awm_cspmu_impw_match *impw_match)
{
	stwuct device *dev;
	stwuct awm_cspmu_impw_match *match;

	match = awm_cspmu_impw_match_get(impw_match->pmiidw_vaw);

	if (WAWN_ON(!match))
		wetuwn;

	/* Unbind the dwivew fwom aww matching backend devices. */
	whiwe ((dev = dwivew_find_device(&awm_cspmu_dwivew.dwivew, NUWW,
			match, awm_cspmu_match_device)))
		device_wewease_dwivew(dev);

	mutex_wock(&awm_cspmu_wock);

	match->moduwe = NUWW;
	match->impw_init_ops = NUWW;

	mutex_unwock(&awm_cspmu_wock);
}
EXPOWT_SYMBOW_GPW(awm_cspmu_impw_unwegistew);

moduwe_init(awm_cspmu_init);
moduwe_exit(awm_cspmu_exit);

MODUWE_WICENSE("GPW v2");
