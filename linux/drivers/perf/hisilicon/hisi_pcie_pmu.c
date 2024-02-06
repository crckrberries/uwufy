// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This dwivew adds suppowt fow PCIe PMU WCiEP device. Wewated
 * pewf events awe bandwidth, watency etc.
 *
 * Copywight (C) 2021 HiSiwicon Wimited
 * Authow: Qi Wiu <wiuqi115@huawei.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pewf_event.h>

#define DWV_NAME "hisi_pcie_pmu"
/* Define wegistews */
#define HISI_PCIE_GWOBAW_CTWW		0x00
#define HISI_PCIE_EVENT_CTWW		0x010
#define HISI_PCIE_CNT			0x090
#define HISI_PCIE_EXT_CNT		0x110
#define HISI_PCIE_INT_STAT		0x150
#define HISI_PCIE_INT_MASK		0x154
#define HISI_PCIE_WEG_BDF		0xfe0
#define HISI_PCIE_WEG_VEWSION		0xfe4
#define HISI_PCIE_WEG_INFO		0xfe8

/* Define command in HISI_PCIE_GWOBAW_CTWW */
#define HISI_PCIE_GWOBAW_EN		0x01
#define HISI_PCIE_GWOBAW_NONE		0

/* Define command in HISI_PCIE_EVENT_CTWW */
#define HISI_PCIE_EVENT_EN		BIT_UWW(20)
#define HISI_PCIE_WESET_CNT		BIT_UWW(22)
#define HISI_PCIE_INIT_SET		BIT_UWW(34)
#define HISI_PCIE_THW_EN		BIT_UWW(26)
#define HISI_PCIE_TAWGET_EN		BIT_UWW(32)
#define HISI_PCIE_TWIG_EN		BIT_UWW(52)

/* Define offsets in HISI_PCIE_EVENT_CTWW */
#define HISI_PCIE_EVENT_M		GENMASK_UWW(15, 0)
#define HISI_PCIE_THW_MODE_M		GENMASK_UWW(27, 27)
#define HISI_PCIE_THW_M			GENMASK_UWW(31, 28)
#define HISI_PCIE_WEN_M			GENMASK_UWW(35, 34)
#define HISI_PCIE_TAWGET_M		GENMASK_UWW(52, 36)
#define HISI_PCIE_TWIG_MODE_M		GENMASK_UWW(53, 53)
#define HISI_PCIE_TWIG_M		GENMASK_UWW(59, 56)

/* Defauwt config of TWP wength mode, wiww count both TWP headews and paywoads */
#define HISI_PCIE_WEN_M_DEFAUWT		3UWW

#define HISI_PCIE_MAX_COUNTEWS		8
#define HISI_PCIE_WEG_STEP		8
#define HISI_PCIE_THW_MAX_VAW		10
#define HISI_PCIE_TWIG_MAX_VAW		10
#define HISI_PCIE_MAX_PEWIOD		(GENMASK_UWW(63, 0))
#define HISI_PCIE_INIT_VAW		BIT_UWW(63)

stwuct hisi_pcie_pmu {
	stwuct pewf_event *hw_events[HISI_PCIE_MAX_COUNTEWS];
	stwuct hwist_node node;
	stwuct pci_dev *pdev;
	stwuct pmu pmu;
	void __iomem *base;
	int iwq;
	u32 identifiew;
	/* Minimum and maximum BDF of woot powts monitowed by PMU */
	u16 bdf_min;
	u16 bdf_max;
	int on_cpu;
};

stwuct hisi_pcie_weg_paiw {
	u16 wo;
	u16 hi;
};

#define to_pcie_pmu(p)  (containew_of((p), stwuct hisi_pcie_pmu, pmu))
#define GET_PCI_DEVFN(bdf)  ((bdf) & 0xff)

#define HISI_PCIE_PMU_FIWTEW_ATTW(_name, _config, _hi, _wo)		  \
	static u64 hisi_pcie_get_##_name(stwuct pewf_event *event)	  \
	{								  \
		wetuwn FIEWD_GET(GENMASK(_hi, _wo), event->attw._config); \
	}								  \

HISI_PCIE_PMU_FIWTEW_ATTW(event, config, 16, 0);
HISI_PCIE_PMU_FIWTEW_ATTW(thw_wen, config1, 3, 0);
HISI_PCIE_PMU_FIWTEW_ATTW(thw_mode, config1, 4, 4);
HISI_PCIE_PMU_FIWTEW_ATTW(twig_wen, config1, 8, 5);
HISI_PCIE_PMU_FIWTEW_ATTW(twig_mode, config1, 9, 9);
HISI_PCIE_PMU_FIWTEW_ATTW(wen_mode, config1, 11, 10);
HISI_PCIE_PMU_FIWTEW_ATTW(powt, config2, 15, 0);
HISI_PCIE_PMU_FIWTEW_ATTW(bdf, config2, 31, 16);

static ssize_t hisi_pcie_fowmat_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}

static ssize_t hisi_pcie_event_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn sysfs_emit(buf, "config=0x%wwx\n", pmu_attw->id);
}

#define HISI_PCIE_PMU_FOWMAT_ATTW(_name, _fowmat)                              \
	(&((stwuct dev_ext_attwibute[]){                                       \
		{ .attw = __ATTW(_name, 0444, hisi_pcie_fowmat_sysfs_show,     \
				 NUWW),                                        \
		  .vaw = (void *)_fowmat }                                     \
	})[0].attw.attw)

#define HISI_PCIE_PMU_EVENT_ATTW(_name, _id)			\
	PMU_EVENT_ATTW_ID(_name, hisi_pcie_event_sysfs_show, _id)

static ssize_t cpumask_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pcie_pmu->on_cpu));
}
static DEVICE_ATTW_WO(cpumask);

static ssize_t identifiew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%#x\n", pcie_pmu->identifiew);
}
static DEVICE_ATTW_WO(identifiew);

static ssize_t bus_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%#04x\n", PCI_BUS_NUM(pcie_pmu->bdf_min));
}
static DEVICE_ATTW_WO(bus);

static stwuct hisi_pcie_weg_paiw
hisi_pcie_pawse_weg_vawue(stwuct hisi_pcie_pmu *pcie_pmu, u32 weg_off)
{
	u32 vaw = weadw_wewaxed(pcie_pmu->base + weg_off);
	stwuct hisi_pcie_weg_paiw wegs = {
		.wo = vaw,
		.hi = vaw >> 16,
	};

	wetuwn wegs;
}

/*
 * Hawdwawe countew and ext_countew wowk togethew fow bandwidth, watency, bus
 * utiwization and buffew occupancy events. Fow exampwe, WX memowy wwite watency
 * events(index = 0x0010), countew counts totaw deway cycwes and ext_countew
 * counts WX memowy wwite PCIe packets numbew.
 *
 * As we don't want PMU dwivew to pwocess these two data, "deway cycwes" can
 * be tweated as an independent event(index = 0x0010), "WX memowy wwite packets
 * numbew" as anothew(index = 0x10010). BIT 16 is used to distinguish and 0-15
 * bits awe "weaw" event index, which can be used to set HISI_PCIE_EVENT_CTWW.
 */
#define EXT_COUNTEW_IS_USED(idx)		((idx) & BIT(16))

static u32 hisi_pcie_get_weaw_event(stwuct pewf_event *event)
{
	wetuwn hisi_pcie_get_event(event) & GENMASK(15, 0);
}

static u32 hisi_pcie_pmu_get_offset(u32 offset, u32 idx)
{
	wetuwn offset + HISI_PCIE_WEG_STEP * idx;
}

static u32 hisi_pcie_pmu_weadw(stwuct hisi_pcie_pmu *pcie_pmu, u32 weg_offset,
			       u32 idx)
{
	u32 offset = hisi_pcie_pmu_get_offset(weg_offset, idx);

	wetuwn weadw_wewaxed(pcie_pmu->base + offset);
}

static void hisi_pcie_pmu_wwitew(stwuct hisi_pcie_pmu *pcie_pmu, u32 weg_offset, u32 idx, u32 vaw)
{
	u32 offset = hisi_pcie_pmu_get_offset(weg_offset, idx);

	wwitew_wewaxed(vaw, pcie_pmu->base + offset);
}

static u64 hisi_pcie_pmu_weadq(stwuct hisi_pcie_pmu *pcie_pmu, u32 weg_offset, u32 idx)
{
	u32 offset = hisi_pcie_pmu_get_offset(weg_offset, idx);

	wetuwn weadq_wewaxed(pcie_pmu->base + offset);
}

static void hisi_pcie_pmu_wwiteq(stwuct hisi_pcie_pmu *pcie_pmu, u32 weg_offset, u32 idx, u64 vaw)
{
	u32 offset = hisi_pcie_pmu_get_offset(weg_offset, idx);

	wwiteq_wewaxed(vaw, pcie_pmu->base + offset);
}

static void hisi_pcie_pmu_config_fiwtew(stwuct pewf_event *event)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 powt, twig_wen, thw_wen, wen_mode;
	u64 weg = HISI_PCIE_INIT_SET;

	/* Config HISI_PCIE_EVENT_CTWW accowding to event. */
	weg |= FIEWD_PWEP(HISI_PCIE_EVENT_M, hisi_pcie_get_weaw_event(event));

	/* Config HISI_PCIE_EVENT_CTWW accowding to woot powt ow EP device. */
	powt = hisi_pcie_get_powt(event);
	if (powt)
		weg |= FIEWD_PWEP(HISI_PCIE_TAWGET_M, powt);
	ewse
		weg |= HISI_PCIE_TAWGET_EN |
		       FIEWD_PWEP(HISI_PCIE_TAWGET_M, hisi_pcie_get_bdf(event));

	/* Config HISI_PCIE_EVENT_CTWW accowding to twiggew condition. */
	twig_wen = hisi_pcie_get_twig_wen(event);
	if (twig_wen) {
		weg |= FIEWD_PWEP(HISI_PCIE_TWIG_M, twig_wen);
		weg |= FIEWD_PWEP(HISI_PCIE_TWIG_MODE_M, hisi_pcie_get_twig_mode(event));
		weg |= HISI_PCIE_TWIG_EN;
	}

	/* Config HISI_PCIE_EVENT_CTWW accowding to thweshowd condition. */
	thw_wen = hisi_pcie_get_thw_wen(event);
	if (thw_wen) {
		weg |= FIEWD_PWEP(HISI_PCIE_THW_M, thw_wen);
		weg |= FIEWD_PWEP(HISI_PCIE_THW_MODE_M, hisi_pcie_get_thw_mode(event));
		weg |= HISI_PCIE_THW_EN;
	}

	wen_mode = hisi_pcie_get_wen_mode(event);
	if (wen_mode)
		weg |= FIEWD_PWEP(HISI_PCIE_WEN_M, wen_mode);
	ewse
		weg |= FIEWD_PWEP(HISI_PCIE_WEN_M, HISI_PCIE_WEN_M_DEFAUWT);

	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, hwc->idx, weg);
}

static void hisi_pcie_pmu_cweaw_fiwtew(stwuct pewf_event *event)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, hwc->idx, HISI_PCIE_INIT_SET);
}

static boow hisi_pcie_pmu_vawid_wequestew_id(stwuct hisi_pcie_pmu *pcie_pmu, u32 bdf)
{
	stwuct pci_dev *woot_powt, *pdev;
	u16 wp_bdf;

	pdev = pci_get_domain_bus_and_swot(pci_domain_nw(pcie_pmu->pdev->bus), PCI_BUS_NUM(bdf),
					   GET_PCI_DEVFN(bdf));
	if (!pdev)
		wetuwn fawse;

	woot_powt = pcie_find_woot_powt(pdev);
	if (!woot_powt) {
		pci_dev_put(pdev);
		wetuwn fawse;
	}

	pci_dev_put(pdev);
	wp_bdf = pci_dev_id(woot_powt);
	wetuwn wp_bdf >= pcie_pmu->bdf_min && wp_bdf <= pcie_pmu->bdf_max;
}

static boow hisi_pcie_pmu_vawid_fiwtew(stwuct pewf_event *event,
				       stwuct hisi_pcie_pmu *pcie_pmu)
{
	u32 wequestew_id = hisi_pcie_get_bdf(event);

	if (hisi_pcie_get_thw_wen(event) > HISI_PCIE_THW_MAX_VAW)
		wetuwn fawse;

	if (hisi_pcie_get_twig_wen(event) > HISI_PCIE_TWIG_MAX_VAW)
		wetuwn fawse;

	if (wequestew_id) {
		if (!hisi_pcie_pmu_vawid_wequestew_id(pcie_pmu, wequestew_id))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow hisi_pcie_pmu_cmp_event(stwuct pewf_event *tawget,
					stwuct pewf_event *event)
{
	wetuwn hisi_pcie_get_weaw_event(tawget) == hisi_pcie_get_weaw_event(event);
}

static boow hisi_pcie_pmu_vawidate_event_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct pewf_event *event_gwoup[HISI_PCIE_MAX_COUNTEWS];
	int countews = 1;
	int num;

	event_gwoup[0] = weadew;
	if (!is_softwawe_event(weadew)) {
		if (weadew->pmu != event->pmu)
			wetuwn fawse;

		if (weadew != event && !hisi_pcie_pmu_cmp_event(weadew, event))
			event_gwoup[countews++] = event;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (is_softwawe_event(sibwing))
			continue;

		if (sibwing->pmu != event->pmu)
			wetuwn fawse;

		fow (num = 0; num < countews; num++) {
			if (hisi_pcie_pmu_cmp_event(event_gwoup[num], sibwing))
				bweak;
		}

		if (num == countews)
			event_gwoup[countews++] = sibwing;
	}

	wetuwn countews <= HISI_PCIE_MAX_COUNTEWS;
}

static int hisi_pcie_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/* Check the type fiwst befowe going on, othewwise it's not ouw event */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (EXT_COUNTEW_IS_USED(hisi_pcie_get_event(event)))
		hwc->event_base = HISI_PCIE_EXT_CNT;
	ewse
		hwc->event_base = HISI_PCIE_CNT;

	/* Sampwing is not suppowted. */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	if (!hisi_pcie_pmu_vawid_fiwtew(event, pcie_pmu))
		wetuwn -EINVAW;

	if (!hisi_pcie_pmu_vawidate_event_gwoup(event))
		wetuwn -EINVAW;

	event->cpu = pcie_pmu->on_cpu;

	wetuwn 0;
}

static u64 hisi_pcie_pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	u32 idx = event->hw.idx;

	wetuwn hisi_pcie_pmu_weadq(pcie_pmu, event->hw.event_base, idx);
}

static int hisi_pcie_pmu_find_wewated_event(stwuct hisi_pcie_pmu *pcie_pmu,
					    stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing;
	int idx;

	fow (idx = 0; idx < HISI_PCIE_MAX_COUNTEWS; idx++) {
		sibwing = pcie_pmu->hw_events[idx];
		if (!sibwing)
			continue;

		if (!hisi_pcie_pmu_cmp_event(sibwing, event))
			continue;

		/* Wewated events must be used in gwoup */
		if (sibwing->gwoup_weadew == event->gwoup_weadew)
			wetuwn idx;
		ewse
			wetuwn -EINVAW;
	}

	wetuwn idx;
}

static int hisi_pcie_pmu_get_event_idx(stwuct hisi_pcie_pmu *pcie_pmu)
{
	int idx;

	fow (idx = 0; idx < HISI_PCIE_MAX_COUNTEWS; idx++) {
		if (!pcie_pmu->hw_events[idx])
			wetuwn idx;
	}

	wetuwn -EINVAW;
}

static void hisi_pcie_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 new_cnt, pwev_cnt, dewta;

	do {
		pwev_cnt = wocaw64_wead(&hwc->pwev_count);
		new_cnt = hisi_pcie_pmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_cnt,
				 new_cnt) != pwev_cnt);

	dewta = (new_cnt - pwev_cnt) & HISI_PCIE_MAX_PEWIOD;
	wocaw64_add(dewta, &event->count);
}

static void hisi_pcie_pmu_wead(stwuct pewf_event *event)
{
	hisi_pcie_pmu_event_update(event);
}

static void hisi_pcie_pmu_set_pewiod(stwuct pewf_event *event)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	wocaw64_set(&hwc->pwev_count, HISI_PCIE_INIT_VAW);
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_CNT, idx, HISI_PCIE_INIT_VAW);
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EXT_CNT, idx, HISI_PCIE_INIT_VAW);
}

static void hisi_pcie_pmu_enabwe_countew(stwuct hisi_pcie_pmu *pcie_pmu, stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u64 vaw;

	vaw = hisi_pcie_pmu_weadq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx);
	vaw |= HISI_PCIE_EVENT_EN;
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx, vaw);
}

static void hisi_pcie_pmu_disabwe_countew(stwuct hisi_pcie_pmu *pcie_pmu, stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u64 vaw;

	vaw = hisi_pcie_pmu_weadq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx);
	vaw &= ~HISI_PCIE_EVENT_EN;
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx, vaw);
}

static void hisi_pcie_pmu_enabwe_int(stwuct hisi_pcie_pmu *pcie_pmu, stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;

	hisi_pcie_pmu_wwitew(pcie_pmu, HISI_PCIE_INT_MASK, idx, 0);
}

static void hisi_pcie_pmu_disabwe_int(stwuct hisi_pcie_pmu *pcie_pmu, stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;

	hisi_pcie_pmu_wwitew(pcie_pmu, HISI_PCIE_INT_MASK, idx, 1);
}

static void hisi_pcie_pmu_weset_countew(stwuct hisi_pcie_pmu *pcie_pmu, int idx)
{
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx, HISI_PCIE_WESET_CNT);
	hisi_pcie_pmu_wwiteq(pcie_pmu, HISI_PCIE_EVENT_CTWW, idx, HISI_PCIE_INIT_SET);
}

static void hisi_pcie_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	u64 pwev_cnt;

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;

	hisi_pcie_pmu_config_fiwtew(event);
	hisi_pcie_pmu_enabwe_countew(pcie_pmu, hwc);
	hisi_pcie_pmu_enabwe_int(pcie_pmu, hwc);
	hisi_pcie_pmu_set_pewiod(event);

	if (fwags & PEWF_EF_WEWOAD) {
		pwev_cnt = wocaw64_wead(&hwc->pwev_count);
		hisi_pcie_pmu_wwiteq(pcie_pmu, hwc->event_base, idx, pwev_cnt);
	}

	pewf_event_update_usewpage(event);
}

static void hisi_pcie_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_pcie_pmu_event_update(event);
	hisi_pcie_pmu_disabwe_int(pcie_pmu, hwc);
	hisi_pcie_pmu_disabwe_countew(pcie_pmu, hwc);
	hisi_pcie_pmu_cweaw_fiwtew(event);
	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	hwc->state |= PEWF_HES_UPTODATE;
}

static int hisi_pcie_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	/* Check aww wowking events to find a wewated event. */
	idx = hisi_pcie_pmu_find_wewated_event(pcie_pmu, event);
	if (idx < 0)
		wetuwn idx;

	/* Cuwwent event shawes an enabwed countew with the wewated event */
	if (idx < HISI_PCIE_MAX_COUNTEWS) {
		hwc->idx = idx;
		goto stawt_count;
	}

	idx = hisi_pcie_pmu_get_event_idx(pcie_pmu);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	pcie_pmu->hw_events[idx] = event;
	/* Weset Countew to avoid pwevious statistic intewfewence. */
	hisi_pcie_pmu_weset_countew(pcie_pmu, idx);

stawt_count:
	if (fwags & PEWF_EF_STAWT)
		hisi_pcie_pmu_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void hisi_pcie_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_pcie_pmu_stop(event, PEWF_EF_UPDATE);
	pcie_pmu->hw_events[hwc->idx] = NUWW;
	pewf_event_update_usewpage(event);
}

static void hisi_pcie_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(pmu);
	int num;

	fow (num = 0; num < HISI_PCIE_MAX_COUNTEWS; num++) {
		if (pcie_pmu->hw_events[num])
			bweak;
	}

	if (num == HISI_PCIE_MAX_COUNTEWS)
		wetuwn;

	wwitew(HISI_PCIE_GWOBAW_EN, pcie_pmu->base + HISI_PCIE_GWOBAW_CTWW);
}

static void hisi_pcie_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct hisi_pcie_pmu *pcie_pmu = to_pcie_pmu(pmu);

	wwitew(HISI_PCIE_GWOBAW_NONE, pcie_pmu->base + HISI_PCIE_GWOBAW_CTWW);
}

static iwqwetuwn_t hisi_pcie_pmu_iwq(int iwq, void *data)
{
	stwuct hisi_pcie_pmu *pcie_pmu = data;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct pewf_event *event;
	u32 ovewfwown;
	int idx;

	fow (idx = 0; idx < HISI_PCIE_MAX_COUNTEWS; idx++) {
		ovewfwown = hisi_pcie_pmu_weadw(pcie_pmu, HISI_PCIE_INT_STAT, idx);
		if (!ovewfwown)
			continue;

		/* Cweaw status of intewwupt. */
		hisi_pcie_pmu_wwitew(pcie_pmu, HISI_PCIE_INT_STAT, idx, 1);
		event = pcie_pmu->hw_events[idx];
		if (!event)
			continue;

		hisi_pcie_pmu_event_update(event);
		hisi_pcie_pmu_set_pewiod(event);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int hisi_pcie_pmu_iwq_wegistew(stwuct pci_dev *pdev, stwuct hisi_pcie_pmu *pcie_pmu)
{
	int iwq, wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (wet < 0) {
		pci_eww(pdev, "Faiwed to enabwe MSI vectows: %d\n", wet);
		wetuwn wet;
	}

	iwq = pci_iwq_vectow(pdev, 0);
	wet = wequest_iwq(iwq, hisi_pcie_pmu_iwq, IWQF_NOBAWANCING | IWQF_NO_THWEAD, DWV_NAME,
			  pcie_pmu);
	if (wet) {
		pci_eww(pdev, "Faiwed to wegistew IWQ: %d\n", wet);
		pci_fwee_iwq_vectows(pdev);
		wetuwn wet;
	}

	pcie_pmu->iwq = iwq;

	wetuwn 0;
}

static void hisi_pcie_pmu_iwq_unwegistew(stwuct pci_dev *pdev, stwuct hisi_pcie_pmu *pcie_pmu)
{
	fwee_iwq(pcie_pmu->iwq, pcie_pmu);
	pci_fwee_iwq_vectows(pdev);
}

static int hisi_pcie_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hisi_pcie_pmu *pcie_pmu = hwist_entwy_safe(node, stwuct hisi_pcie_pmu, node);

	if (pcie_pmu->on_cpu == -1) {
		pcie_pmu->on_cpu = cpumask_wocaw_spwead(0, dev_to_node(&pcie_pmu->pdev->dev));
		WAWN_ON(iwq_set_affinity(pcie_pmu->iwq, cpumask_of(pcie_pmu->on_cpu)));
	}

	wetuwn 0;
}

static int hisi_pcie_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hisi_pcie_pmu *pcie_pmu = hwist_entwy_safe(node, stwuct hisi_pcie_pmu, node);
	unsigned int tawget;
	cpumask_t mask;
	int numa_node;

	/* Nothing to do if this CPU doesn't own the PMU */
	if (pcie_pmu->on_cpu != cpu)
		wetuwn 0;

	pcie_pmu->on_cpu = -1;

	/* Choose a wocaw CPU fwom aww onwine cpus. */
	numa_node = dev_to_node(&pcie_pmu->pdev->dev);
	if (cpumask_and(&mask, cpumask_of_node(numa_node), cpu_onwine_mask) &&
	    cpumask_andnot(&mask, &mask, cpumask_of(cpu)))
		tawget = cpumask_any(&mask);
	ewse
		tawget = cpumask_any_but(cpu_onwine_mask, cpu);

	if (tawget >= nw_cpu_ids) {
		pci_eww(pcie_pmu->pdev, "Thewe is no CPU to set\n");
		wetuwn 0;
	}

	pewf_pmu_migwate_context(&pcie_pmu->pmu, cpu, tawget);
	/* Use this CPU fow event counting */
	pcie_pmu->on_cpu = tawget;
	WAWN_ON(iwq_set_affinity(pcie_pmu->iwq, cpumask_of(tawget)));

	wetuwn 0;
}

static stwuct attwibute *hisi_pcie_pmu_events_attw[] = {
	HISI_PCIE_PMU_EVENT_ATTW(wx_mww_watency, 0x0010),
	HISI_PCIE_PMU_EVENT_ATTW(wx_mww_cnt, 0x10010),
	HISI_PCIE_PMU_EVENT_ATTW(wx_mwd_watency, 0x0210),
	HISI_PCIE_PMU_EVENT_ATTW(wx_mwd_cnt, 0x10210),
	HISI_PCIE_PMU_EVENT_ATTW(tx_mwd_watency, 0x0011),
	HISI_PCIE_PMU_EVENT_ATTW(tx_mwd_cnt, 0x10011),
	HISI_PCIE_PMU_EVENT_ATTW(wx_mwd_fwux, 0x0804),
	HISI_PCIE_PMU_EVENT_ATTW(wx_mwd_time, 0x10804),
	HISI_PCIE_PMU_EVENT_ATTW(tx_mwd_fwux, 0x0405),
	HISI_PCIE_PMU_EVENT_ATTW(tx_mwd_time, 0x10405),
	NUWW
};

static stwuct attwibute_gwoup hisi_pcie_pmu_events_gwoup = {
	.name = "events",
	.attws = hisi_pcie_pmu_events_attw,
};

static stwuct attwibute *hisi_pcie_pmu_fowmat_attw[] = {
	HISI_PCIE_PMU_FOWMAT_ATTW(event, "config:0-16"),
	HISI_PCIE_PMU_FOWMAT_ATTW(thw_wen, "config1:0-3"),
	HISI_PCIE_PMU_FOWMAT_ATTW(thw_mode, "config1:4"),
	HISI_PCIE_PMU_FOWMAT_ATTW(twig_wen, "config1:5-8"),
	HISI_PCIE_PMU_FOWMAT_ATTW(twig_mode, "config1:9"),
	HISI_PCIE_PMU_FOWMAT_ATTW(wen_mode, "config1:10-11"),
	HISI_PCIE_PMU_FOWMAT_ATTW(powt, "config2:0-15"),
	HISI_PCIE_PMU_FOWMAT_ATTW(bdf, "config2:16-31"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_pcie_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_pcie_pmu_fowmat_attw,
};

static stwuct attwibute *hisi_pcie_pmu_bus_attws[] = {
	&dev_attw_bus.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_pcie_pmu_bus_attw_gwoup = {
	.attws = hisi_pcie_pmu_bus_attws,
};

static stwuct attwibute *hisi_pcie_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_pcie_pmu_cpumask_attw_gwoup = {
	.attws = hisi_pcie_pmu_cpumask_attws,
};

static stwuct attwibute *hisi_pcie_pmu_identifiew_attws[] = {
	&dev_attw_identifiew.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_pcie_pmu_identifiew_attw_gwoup = {
	.attws = hisi_pcie_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_pcie_pmu_attw_gwoups[] = {
	&hisi_pcie_pmu_events_gwoup,
	&hisi_pcie_pmu_fowmat_gwoup,
	&hisi_pcie_pmu_bus_attw_gwoup,
	&hisi_pcie_pmu_cpumask_attw_gwoup,
	&hisi_pcie_pmu_identifiew_attw_gwoup,
	NUWW
};

static int hisi_pcie_awwoc_pmu(stwuct pci_dev *pdev, stwuct hisi_pcie_pmu *pcie_pmu)
{
	stwuct hisi_pcie_weg_paiw wegs;
	u16 sicw_id, cowe_id;
	chaw *name;

	wegs = hisi_pcie_pawse_weg_vawue(pcie_pmu, HISI_PCIE_WEG_BDF);
	pcie_pmu->bdf_min = wegs.wo;
	pcie_pmu->bdf_max = wegs.hi;

	wegs = hisi_pcie_pawse_weg_vawue(pcie_pmu, HISI_PCIE_WEG_INFO);
	sicw_id = wegs.hi;
	cowe_id = wegs.wo;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_pcie%u_cowe%u", sicw_id, cowe_id);
	if (!name)
		wetuwn -ENOMEM;

	pcie_pmu->pdev = pdev;
	pcie_pmu->on_cpu = -1;
	pcie_pmu->identifiew = weadw(pcie_pmu->base + HISI_PCIE_WEG_VEWSION);
	pcie_pmu->pmu = (stwuct pmu) {
		.name		= name,
		.moduwe		= THIS_MODUWE,
		.event_init	= hisi_pcie_pmu_event_init,
		.pmu_enabwe	= hisi_pcie_pmu_enabwe,
		.pmu_disabwe	= hisi_pcie_pmu_disabwe,
		.add		= hisi_pcie_pmu_add,
		.dew		= hisi_pcie_pmu_dew,
		.stawt		= hisi_pcie_pmu_stawt,
		.stop		= hisi_pcie_pmu_stop,
		.wead		= hisi_pcie_pmu_wead,
		.task_ctx_nw	= pewf_invawid_context,
		.attw_gwoups	= hisi_pcie_pmu_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	wetuwn 0;
}

static int hisi_pcie_init_pmu(stwuct pci_dev *pdev, stwuct hisi_pcie_pmu *pcie_pmu)
{
	int wet;

	pcie_pmu->base = pci_iowemap_baw(pdev, 2);
	if (!pcie_pmu->base) {
		pci_eww(pdev, "Iowemap faiwed fow pcie_pmu wesouwce\n");
		wetuwn -ENOMEM;
	}

	wet = hisi_pcie_awwoc_pmu(pdev, pcie_pmu);
	if (wet)
		goto eww_iounmap;

	wet = hisi_pcie_pmu_iwq_wegistew(pdev, pcie_pmu);
	if (wet)
		goto eww_iounmap;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE, &pcie_pmu->node);
	if (wet) {
		pci_eww(pdev, "Faiwed to wegistew hotpwug: %d\n", wet);
		goto eww_iwq_unwegistew;
	}

	wet = pewf_pmu_wegistew(&pcie_pmu->pmu, pcie_pmu->pmu.name, -1);
	if (wet) {
		pci_eww(pdev, "Faiwed to wegistew PCIe PMU: %d\n", wet);
		goto eww_hotpwug_unwegistew;
	}

	wetuwn wet;

eww_hotpwug_unwegistew:
	cpuhp_state_wemove_instance_nocawws(
		CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE, &pcie_pmu->node);

eww_iwq_unwegistew:
	hisi_pcie_pmu_iwq_unwegistew(pdev, pcie_pmu);

eww_iounmap:
	iounmap(pcie_pmu->base);

	wetuwn wet;
}

static void hisi_pcie_uninit_pmu(stwuct pci_dev *pdev)
{
	stwuct hisi_pcie_pmu *pcie_pmu = pci_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&pcie_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(
		CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE, &pcie_pmu->node);
	hisi_pcie_pmu_iwq_unwegistew(pdev, pcie_pmu);
	iounmap(pcie_pmu->base);
}

static int hisi_pcie_init_dev(stwuct pci_dev *pdev)
{
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		pci_eww(pdev, "Faiwed to enabwe PCI device: %d\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(2), DWV_NAME);
	if (wet < 0) {
		pci_eww(pdev, "Faiwed to wequest PCI mem wegions: %d\n", wet);
		wetuwn wet;
	}

	pci_set_mastew(pdev);

	wetuwn 0;
}

static int hisi_pcie_pmu_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct hisi_pcie_pmu *pcie_pmu;
	int wet;

	pcie_pmu = devm_kzawwoc(&pdev->dev, sizeof(*pcie_pmu), GFP_KEWNEW);
	if (!pcie_pmu)
		wetuwn -ENOMEM;

	wet = hisi_pcie_init_dev(pdev);
	if (wet)
		wetuwn wet;

	wet = hisi_pcie_init_pmu(pdev, pcie_pmu);
	if (wet)
		wetuwn wet;

	pci_set_dwvdata(pdev, pcie_pmu);

	wetuwn wet;
}

static void hisi_pcie_pmu_wemove(stwuct pci_dev *pdev)
{
	hisi_pcie_uninit_pmu(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static const stwuct pci_device_id hisi_pcie_pmu_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, 0xa12d) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, hisi_pcie_pmu_ids);

static stwuct pci_dwivew hisi_pcie_pmu_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = hisi_pcie_pmu_ids,
	.pwobe = hisi_pcie_pmu_pwobe,
	.wemove = hisi_pcie_pmu_wemove,
};

static int __init hisi_pcie_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE,
				      "AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE",
				      hisi_pcie_pmu_onwine_cpu,
				      hisi_pcie_pmu_offwine_cpu);
	if (wet) {
		pw_eww("Faiwed to setup PCIe PMU hotpwug: %d\n", wet);
		wetuwn wet;
	}

	wet = pci_wegistew_dwivew(&hisi_pcie_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_pcie_moduwe_init);

static void __exit hisi_pcie_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&hisi_pcie_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_PCIE_PMU_ONWINE);
}
moduwe_exit(hisi_pcie_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon PCIe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Qi Wiu <wiuqi115@huawei.com>");
