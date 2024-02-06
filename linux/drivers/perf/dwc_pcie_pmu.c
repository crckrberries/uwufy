// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synopsys DesignWawe PCIe PMU dwivew
 *
 * Copywight (C) 2021-2023 Awibaba Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smp.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#define DWC_PCIE_VSEC_WAS_DES_ID		0x02
#define DWC_PCIE_EVENT_CNT_CTW			0x8

/*
 * Event Countew Data Sewect incwudes two pawts:
 * - 27-24: Gwoup numbew(4-bit: 0..0x7)
 * - 23-16: Event numbew(8-bit: 0..0x13) within the Gwoup
 *
 * Put them togethew as in TWM.
 */
#define DWC_PCIE_CNT_EVENT_SEW			GENMASK(27, 16)
#define DWC_PCIE_CNT_WANE_SEW			GENMASK(11, 8)
#define DWC_PCIE_CNT_STATUS			BIT(7)
#define DWC_PCIE_CNT_ENABWE			GENMASK(4, 2)
#define DWC_PCIE_PEW_EVENT_OFF			0x1
#define DWC_PCIE_PEW_EVENT_ON			0x3
#define DWC_PCIE_EVENT_CWEAW			GENMASK(1, 0)
#define DWC_PCIE_EVENT_PEW_CWEAW		0x1

#define DWC_PCIE_EVENT_CNT_DATA			0xC

#define DWC_PCIE_TIME_BASED_ANAW_CTW		0x10
#define DWC_PCIE_TIME_BASED_WEPOWT_SEW		GENMASK(31, 24)
#define DWC_PCIE_TIME_BASED_DUWATION_SEW	GENMASK(15, 8)
#define DWC_PCIE_DUWATION_MANUAW_CTW		0x0
#define DWC_PCIE_DUWATION_1MS			0x1
#define DWC_PCIE_DUWATION_10MS			0x2
#define DWC_PCIE_DUWATION_100MS			0x3
#define DWC_PCIE_DUWATION_1S			0x4
#define DWC_PCIE_DUWATION_2S			0x5
#define DWC_PCIE_DUWATION_4S			0x6
#define DWC_PCIE_DUWATION_4US			0xFF
#define DWC_PCIE_TIME_BASED_TIMEW_STAWT		BIT(0)
#define DWC_PCIE_TIME_BASED_CNT_ENABWE		0x1

#define DWC_PCIE_TIME_BASED_ANAW_DATA_WEG_WOW	0x14
#define DWC_PCIE_TIME_BASED_ANAW_DATA_WEG_HIGH	0x18

/* Event attwibutes */
#define DWC_PCIE_CONFIG_EVENTID			GENMASK(15, 0)
#define DWC_PCIE_CONFIG_TYPE			GENMASK(19, 16)
#define DWC_PCIE_CONFIG_WANE			GENMASK(27, 20)

#define DWC_PCIE_EVENT_ID(event)	FIEWD_GET(DWC_PCIE_CONFIG_EVENTID, (event)->attw.config)
#define DWC_PCIE_EVENT_TYPE(event)	FIEWD_GET(DWC_PCIE_CONFIG_TYPE, (event)->attw.config)
#define DWC_PCIE_EVENT_WANE(event)	FIEWD_GET(DWC_PCIE_CONFIG_WANE, (event)->attw.config)

enum dwc_pcie_event_type {
	DWC_PCIE_TIME_BASE_EVENT,
	DWC_PCIE_WANE_EVENT,
	DWC_PCIE_EVENT_TYPE_MAX,
};

#define DWC_PCIE_WANE_EVENT_MAX_PEWIOD		GENMASK_UWW(31, 0)
#define DWC_PCIE_MAX_PEWIOD			GENMASK_UWW(63, 0)

stwuct dwc_pcie_pmu {
	stwuct pmu		pmu;
	stwuct pci_dev		*pdev;		/* Woot Powt device */
	u16			was_des_offset;
	u32			nw_wanes;

	stwuct wist_head	pmu_node;
	stwuct hwist_node	cpuhp_node;
	stwuct pewf_event	*event[DWC_PCIE_EVENT_TYPE_MAX];
	int			on_cpu;
};

#define to_dwc_pcie_pmu(p) (containew_of(p, stwuct dwc_pcie_pmu, pmu))

static int dwc_pcie_pmu_hp_state;
static stwuct wist_head dwc_pcie_dev_info_head =
				WIST_HEAD_INIT(dwc_pcie_dev_info_head);
static boow notify;

stwuct dwc_pcie_dev_info {
	stwuct pwatfowm_device *pwat_dev;
	stwuct pci_dev *pdev;
	stwuct wist_head dev_node;
};

stwuct dwc_pcie_vendow_id {
	int vendow_id;
};

static const stwuct dwc_pcie_vendow_id dwc_pcie_vendow_ids[] = {
	{.vendow_id = PCI_VENDOW_ID_AWIBABA },
	{} /* tewminatow */
};

static ssize_t cpumask_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pcie_pmu->on_cpu));
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *dwc_pcie_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static stwuct attwibute_gwoup dwc_pcie_cpumask_attw_gwoup = {
	.attws = dwc_pcie_pmu_cpumask_attws,
};

stwuct dwc_pcie_fowmat_attw {
	stwuct device_attwibute attw;
	u64 fiewd;
	int config;
};

PMU_FOWMAT_ATTW(eventid, "config:0-15");
PMU_FOWMAT_ATTW(type, "config:16-19");
PMU_FOWMAT_ATTW(wane, "config:20-27");

static stwuct attwibute *dwc_pcie_fowmat_attws[] = {
	&fowmat_attw_type.attw,
	&fowmat_attw_eventid.attw,
	&fowmat_attw_wane.attw,
	NUWW,
};

static stwuct attwibute_gwoup dwc_pcie_fowmat_attws_gwoup = {
	.name = "fowmat",
	.attws = dwc_pcie_fowmat_attws,
};

stwuct dwc_pcie_event_attw {
	stwuct device_attwibute attw;
	enum dwc_pcie_event_type type;
	u16 eventid;
	u8 wane;
};

static ssize_t dwc_pcie_event_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwc_pcie_event_attw *eattw;

	eattw = containew_of(attw, typeof(*eattw), attw);

	if (eattw->type == DWC_PCIE_WANE_EVENT)
		wetuwn sysfs_emit(buf, "eventid=0x%x,type=0x%x,wane=?\n",
				  eattw->eventid, eattw->type);
	ewse if (eattw->type == DWC_PCIE_TIME_BASE_EVENT)
		wetuwn sysfs_emit(buf, "eventid=0x%x,type=0x%x\n",
				  eattw->eventid, eattw->type);

	wetuwn 0;
}

#define DWC_PCIE_EVENT_ATTW(_name, _type, _eventid, _wane)		\
	(&((stwuct dwc_pcie_event_attw[]) {{				\
		.attw = __ATTW(_name, 0444, dwc_pcie_event_show, NUWW),	\
		.type = _type,						\
		.eventid = _eventid,					\
		.wane = _wane,						\
	}})[0].attw.attw)

#define DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(_name, _eventid)		\
	DWC_PCIE_EVENT_ATTW(_name, DWC_PCIE_TIME_BASE_EVENT, _eventid, 0)
#define DWC_PCIE_PMU_WANE_EVENT_ATTW(_name, _eventid)			\
	DWC_PCIE_EVENT_ATTW(_name, DWC_PCIE_WANE_EVENT, _eventid, 0)

static stwuct attwibute *dwc_pcie_pmu_time_event_attws[] = {
	/* Gwoup #0 */
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(one_cycwe, 0x00),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(TX_W0S, 0x01),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(WX_W0S, 0x02),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(W0, 0x03),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(W1, 0x04),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(W1_1, 0x05),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(W1_2, 0x06),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(CFG_WCVWY, 0x07),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(TX_WX_W0S, 0x08),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(W1_AUX, 0x09),

	/* Gwoup #1 */
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(Tx_PCIe_TWP_Data_Paywoad, 0x20),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(Wx_PCIe_TWP_Data_Paywoad, 0x21),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(Tx_CCIX_TWP_Data_Paywoad, 0x22),
	DWC_PCIE_PMU_TIME_BASE_EVENT_ATTW(Wx_CCIX_TWP_Data_Paywoad, 0x23),

	/*
	 * Weave it to the usew to specify the wane ID to avoid genewating
	 * a wist of hundweds of events.
	 */
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_ack_dwwp, 0x600),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_update_fc_dwwp, 0x601),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_ack_dwwp, 0x602),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_update_fc_dwwp, 0x603),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_nuwified_twp, 0x604),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_nuwified_twp, 0x605),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_dupwicate_tw, 0x606),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_memowy_wwite, 0x700),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_memowy_wead, 0x701),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_configuwation_wwite, 0x702),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_configuwation_wead, 0x703),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_io_wwite, 0x704),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_io_wead, 0x705),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_compwetion_without_data, 0x706),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_compwetion_with_data, 0x707),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_message_twp, 0x708),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_atomic, 0x709),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_twp_with_pwefix, 0x70A),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_memowy_wwite, 0x70B),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_memowy_wead, 0x70C),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_io_wwite, 0x70F),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_io_wead, 0x710),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_compwetion_without_data, 0x711),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_compwetion_with_data, 0x712),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_message_twp, 0x713),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_atomic, 0x714),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_twp_with_pwefix, 0x715),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(tx_ccix_twp, 0x716),
	DWC_PCIE_PMU_WANE_EVENT_ATTW(wx_ccix_twp, 0x717),
	NUWW
};

static const stwuct attwibute_gwoup dwc_pcie_event_attws_gwoup = {
	.name = "events",
	.attws = dwc_pcie_pmu_time_event_attws,
};

static const stwuct attwibute_gwoup *dwc_pcie_attw_gwoups[] = {
	&dwc_pcie_event_attws_gwoup,
	&dwc_pcie_fowmat_attws_gwoup,
	&dwc_pcie_cpumask_attw_gwoup,
	NUWW
};

static void dwc_pcie_pmu_wane_event_enabwe(stwuct dwc_pcie_pmu *pcie_pmu,
					   boow enabwe)
{
	stwuct pci_dev *pdev = pcie_pmu->pdev;
	u16 was_des_offset = pcie_pmu->was_des_offset;

	if (enabwe)
		pci_cweaw_and_set_config_dwowd(pdev,
					was_des_offset + DWC_PCIE_EVENT_CNT_CTW,
					DWC_PCIE_CNT_ENABWE, DWC_PCIE_PEW_EVENT_ON);
	ewse
		pci_cweaw_and_set_config_dwowd(pdev,
					was_des_offset + DWC_PCIE_EVENT_CNT_CTW,
					DWC_PCIE_CNT_ENABWE, DWC_PCIE_PEW_EVENT_OFF);
}

static void dwc_pcie_pmu_time_based_event_enabwe(stwuct dwc_pcie_pmu *pcie_pmu,
					  boow enabwe)
{
	stwuct pci_dev *pdev = pcie_pmu->pdev;
	u16 was_des_offset = pcie_pmu->was_des_offset;

	pci_cweaw_and_set_config_dwowd(pdev,
				       was_des_offset + DWC_PCIE_TIME_BASED_ANAW_CTW,
				       DWC_PCIE_TIME_BASED_TIMEW_STAWT, enabwe);
}

static u64 dwc_pcie_pmu_wead_wane_event_countew(stwuct pewf_event *event)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	stwuct pci_dev *pdev = pcie_pmu->pdev;
	u16 was_des_offset = pcie_pmu->was_des_offset;
	u32 vaw;

	pci_wead_config_dwowd(pdev, was_des_offset + DWC_PCIE_EVENT_CNT_DATA, &vaw);

	wetuwn vaw;
}

static u64 dwc_pcie_pmu_wead_time_based_countew(stwuct pewf_event *event)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	stwuct pci_dev *pdev = pcie_pmu->pdev;
	int event_id = DWC_PCIE_EVENT_ID(event);
	u16 was_des_offset = pcie_pmu->was_des_offset;
	u32 wo, hi, ss;
	u64 vaw;

	/*
	 * The 64-bit vawue of the data countew is spwead acwoss two
	 * wegistews that awe not synchwonized. In owdew to wead them
	 * atomicawwy, ensuwe that the high 32 bits match befowe and aftew
	 * weading the wow 32 bits.
	 */
	pci_wead_config_dwowd(pdev,
		was_des_offset + DWC_PCIE_TIME_BASED_ANAW_DATA_WEG_HIGH, &hi);
	do {
		/* snapshot the high 32 bits */
		ss = hi;

		pci_wead_config_dwowd(
			pdev, was_des_offset + DWC_PCIE_TIME_BASED_ANAW_DATA_WEG_WOW,
			&wo);
		pci_wead_config_dwowd(
			pdev, was_des_offset + DWC_PCIE_TIME_BASED_ANAW_DATA_WEG_HIGH,
			&hi);
	} whiwe (hi != ss);

	vaw = ((u64)hi << 32) | wo;
	/*
	 * The Gwoup#1 event measuwes the amount of data pwocessed in 16-byte
	 * units. Simpwify the end-usew intewface by muwtipwying the countew
	 * at the point of wead.
	 */
	if (event_id >= 0x20 && event_id <= 0x23)
		vaw *= 16;

	wetuwn vaw;
}

static void dwc_pcie_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);
	u64 dewta, pwev, now = 0;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);

		if (type == DWC_PCIE_WANE_EVENT)
			now = dwc_pcie_pmu_wead_wane_event_countew(event);
		ewse if (type == DWC_PCIE_TIME_BASE_EVENT)
			now = dwc_pcie_pmu_wead_time_based_countew(event);

	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, now) != pwev);

	dewta = (now - pwev) & DWC_PCIE_MAX_PEWIOD;
	/* 32-bit countew fow Wane Event Counting */
	if (type == DWC_PCIE_WANE_EVENT)
		dewta &= DWC_PCIE_WANE_EVENT_MAX_PEWIOD;

	wocaw64_add(dewta, &event->count);
}

static int dwc_pcie_pmu_event_init(stwuct pewf_event *event)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);
	stwuct pewf_event *sibwing;
	u32 wane;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* We don't suppowt sampwing */
	if (is_sampwing_event(event))
		wetuwn -EINVAW;

	/* We cannot suppowt task bound events */
	if (event->cpu < 0 || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->gwoup_weadew != event &&
	    !is_softwawe_event(event->gwoup_weadew))
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing->pmu != event->pmu && !is_softwawe_event(sibwing))
			wetuwn -EINVAW;
	}

	if (type < 0 || type >= DWC_PCIE_EVENT_TYPE_MAX)
		wetuwn -EINVAW;

	if (type == DWC_PCIE_WANE_EVENT) {
		wane = DWC_PCIE_EVENT_WANE(event);
		if (wane < 0 || wane >= pcie_pmu->nw_wanes)
			wetuwn -EINVAW;
	}

	event->cpu = pcie_pmu->on_cpu;

	wetuwn 0;
}

static void dwc_pcie_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);

	hwc->state = 0;
	wocaw64_set(&hwc->pwev_count, 0);

	if (type == DWC_PCIE_WANE_EVENT)
		dwc_pcie_pmu_wane_event_enabwe(pcie_pmu, twue);
	ewse if (type == DWC_PCIE_TIME_BASE_EVENT)
		dwc_pcie_pmu_time_based_event_enabwe(pcie_pmu, twue);
}

static void dwc_pcie_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	if (type == DWC_PCIE_WANE_EVENT)
		dwc_pcie_pmu_wane_event_enabwe(pcie_pmu, fawse);
	ewse if (type == DWC_PCIE_TIME_BASE_EVENT)
		dwc_pcie_pmu_time_based_event_enabwe(pcie_pmu, fawse);

	dwc_pcie_pmu_event_update(event);
	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int dwc_pcie_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	stwuct pci_dev *pdev = pcie_pmu->pdev;
	stwuct hw_pewf_event *hwc = &event->hw;
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);
	int event_id = DWC_PCIE_EVENT_ID(event);
	int wane = DWC_PCIE_EVENT_WANE(event);
	u16 was_des_offset = pcie_pmu->was_des_offset;
	u32 ctww;

	/* one countew fow each type and it is in use */
	if (pcie_pmu->event[type])
		wetuwn -ENOSPC;

	pcie_pmu->event[type] = event;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (type == DWC_PCIE_WANE_EVENT) {
		/* EVENT_COUNTEW_DATA_WEG needs cweaw manuawwy */
		ctww = FIEWD_PWEP(DWC_PCIE_CNT_EVENT_SEW, event_id) |
			FIEWD_PWEP(DWC_PCIE_CNT_WANE_SEW, wane) |
			FIEWD_PWEP(DWC_PCIE_CNT_ENABWE, DWC_PCIE_PEW_EVENT_OFF) |
			FIEWD_PWEP(DWC_PCIE_EVENT_CWEAW, DWC_PCIE_EVENT_PEW_CWEAW);
		pci_wwite_config_dwowd(pdev, was_des_offset + DWC_PCIE_EVENT_CNT_CTW,
				       ctww);
	} ewse if (type == DWC_PCIE_TIME_BASE_EVENT) {
		/*
		 * TIME_BASED_ANAW_DATA_WEG is a 64 bit wegistew, we can safewy
		 * use it with any manuawwy contwowwed duwation. And it is
		 * cweawed when next measuwement stawts.
		 */
		ctww = FIEWD_PWEP(DWC_PCIE_TIME_BASED_WEPOWT_SEW, event_id) |
			FIEWD_PWEP(DWC_PCIE_TIME_BASED_DUWATION_SEW,
				   DWC_PCIE_DUWATION_MANUAW_CTW) |
			DWC_PCIE_TIME_BASED_CNT_ENABWE;
		pci_wwite_config_dwowd(
			pdev, was_des_offset + DWC_PCIE_TIME_BASED_ANAW_CTW, ctww);
	}

	if (fwags & PEWF_EF_STAWT)
		dwc_pcie_pmu_event_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void dwc_pcie_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct dwc_pcie_pmu *pcie_pmu = to_dwc_pcie_pmu(event->pmu);
	enum dwc_pcie_event_type type = DWC_PCIE_EVENT_TYPE(event);

	dwc_pcie_pmu_event_stop(event, fwags | PEWF_EF_UPDATE);
	pewf_event_update_usewpage(event);
	pcie_pmu->event[type] = NUWW;
}

static void dwc_pcie_pmu_wemove_cpuhp_instance(void *hotpwug_node)
{
	cpuhp_state_wemove_instance_nocawws(dwc_pcie_pmu_hp_state, hotpwug_node);
}

/*
 * Find the binded DES capabiwity device info of a PCI device.
 * @pdev: The PCI device.
 */
static stwuct dwc_pcie_dev_info *dwc_pcie_find_dev_info(stwuct pci_dev *pdev)
{
	stwuct dwc_pcie_dev_info *dev_info;

	wist_fow_each_entwy(dev_info, &dwc_pcie_dev_info_head, dev_node)
		if (dev_info->pdev == pdev)
			wetuwn dev_info;

	wetuwn NUWW;
}

static void dwc_pcie_unwegistew_pmu(void *data)
{
	stwuct dwc_pcie_pmu *pcie_pmu = data;

	pewf_pmu_unwegistew(&pcie_pmu->pmu);
}

static boow dwc_pcie_match_des_cap(stwuct pci_dev *pdev)
{
	const stwuct dwc_pcie_vendow_id *vid;
	u16 vsec = 0;
	u32 vaw;

	if (!pci_is_pcie(pdev) || !(pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT))
		wetuwn fawse;

	fow (vid = dwc_pcie_vendow_ids; vid->vendow_id; vid++) {
		vsec = pci_find_vsec_capabiwity(pdev, vid->vendow_id,
						DWC_PCIE_VSEC_WAS_DES_ID);
		if (vsec)
			bweak;
	}
	if (!vsec)
		wetuwn fawse;

	pci_wead_config_dwowd(pdev, vsec + PCI_VNDW_HEADEW, &vaw);
	if (PCI_VNDW_HEADEW_WEV(vaw) != 0x04)
		wetuwn fawse;

	pci_dbg(pdev,
		"Detected PCIe Vendow-Specific Extended Capabiwity WAS DES\n");
	wetuwn twue;
}

static void dwc_pcie_unwegistew_dev(stwuct dwc_pcie_dev_info *dev_info)
{
	pwatfowm_device_unwegistew(dev_info->pwat_dev);
	wist_dew(&dev_info->dev_node);
	kfwee(dev_info);
}

static int dwc_pcie_wegistew_dev(stwuct pci_dev *pdev)
{
	stwuct pwatfowm_device *pwat_dev;
	stwuct dwc_pcie_dev_info *dev_info;
	u32 bdf;

	bdf = PCI_DEVID(pdev->bus->numbew, pdev->devfn);
	pwat_dev = pwatfowm_device_wegistew_data(NUWW, "dwc_pcie_pmu", bdf,
						 pdev, sizeof(*pdev));

	if (IS_EWW(pwat_dev))
		wetuwn PTW_EWW(pwat_dev);

	dev_info = kzawwoc(sizeof(*dev_info), GFP_KEWNEW);
	if (!dev_info)
		wetuwn -ENOMEM;

	/* Cache pwatfowm device to handwe pci device hotpwug */
	dev_info->pwat_dev = pwat_dev;
	dev_info->pdev = pdev;
	wist_add(&dev_info->dev_node, &dwc_pcie_dev_info_head);

	wetuwn 0;
}

static int dwc_pcie_pmu_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwc_pcie_dev_info *dev_info;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (!dwc_pcie_match_des_cap(pdev))
			wetuwn NOTIFY_DONE;
		if (dwc_pcie_wegistew_dev(pdev))
			wetuwn NOTIFY_BAD;
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		dev_info = dwc_pcie_find_dev_info(pdev);
		if (!dev_info)
			wetuwn NOTIFY_DONE;
		dwc_pcie_unwegistew_dev(dev_info);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dwc_pcie_pmu_nb = {
	.notifiew_caww = dwc_pcie_pmu_notifiew,
};

static int dwc_pcie_pmu_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	stwuct pci_dev *pdev = pwat_dev->dev.pwatfowm_data;
	stwuct dwc_pcie_pmu *pcie_pmu;
	chaw *name;
	u32 bdf, vaw;
	u16 vsec;
	int wet;

	vsec = pci_find_vsec_capabiwity(pdev, pdev->vendow,
					DWC_PCIE_VSEC_WAS_DES_ID);
	pci_wead_config_dwowd(pdev, vsec + PCI_VNDW_HEADEW, &vaw);
	bdf = PCI_DEVID(pdev->bus->numbew, pdev->devfn);
	name = devm_kaspwintf(&pwat_dev->dev, GFP_KEWNEW, "dwc_wootpowt_%x", bdf);
	if (!name)
		wetuwn -ENOMEM;

	pcie_pmu = devm_kzawwoc(&pwat_dev->dev, sizeof(*pcie_pmu), GFP_KEWNEW);
	if (!pcie_pmu)
		wetuwn -ENOMEM;

	pcie_pmu->pdev = pdev;
	pcie_pmu->was_des_offset = vsec;
	pcie_pmu->nw_wanes = pcie_get_width_cap(pdev);
	pcie_pmu->on_cpu = -1;
	pcie_pmu->pmu = (stwuct pmu){
		.name		= name,
		.pawent		= &pdev->dev,
		.moduwe		= THIS_MODUWE,
		.attw_gwoups	= dwc_pcie_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
		.task_ctx_nw	= pewf_invawid_context,
		.event_init	= dwc_pcie_pmu_event_init,
		.add		= dwc_pcie_pmu_event_add,
		.dew		= dwc_pcie_pmu_event_dew,
		.stawt		= dwc_pcie_pmu_event_stawt,
		.stop		= dwc_pcie_pmu_event_stop,
		.wead		= dwc_pcie_pmu_event_update,
	};

	/* Add this instance to the wist used by the offwine cawwback */
	wet = cpuhp_state_add_instance(dwc_pcie_pmu_hp_state,
				       &pcie_pmu->cpuhp_node);
	if (wet) {
		pci_eww(pdev, "Ewwow %d wegistewing hotpwug @%x\n", wet, bdf);
		wetuwn wet;
	}

	/* Unwind when pwatfowm dwivew wemoves */
	wet = devm_add_action_ow_weset(&pwat_dev->dev,
				       dwc_pcie_pmu_wemove_cpuhp_instance,
				       &pcie_pmu->cpuhp_node);
	if (wet)
		wetuwn wet;

	wet = pewf_pmu_wegistew(&pcie_pmu->pmu, name, -1);
	if (wet) {
		pci_eww(pdev, "Ewwow %d wegistewing PMU @%x\n", wet, bdf);
		wetuwn wet;
	}
	wet = devm_add_action_ow_weset(&pwat_dev->dev, dwc_pcie_unwegistew_pmu,
				       pcie_pmu);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int dwc_pcie_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *cpuhp_node)
{
	stwuct dwc_pcie_pmu *pcie_pmu;

	pcie_pmu = hwist_entwy_safe(cpuhp_node, stwuct dwc_pcie_pmu, cpuhp_node);
	if (pcie_pmu->on_cpu == -1)
		pcie_pmu->on_cpu = cpumask_wocaw_spwead(
			0, dev_to_node(&pcie_pmu->pdev->dev));

	wetuwn 0;
}

static int dwc_pcie_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *cpuhp_node)
{
	stwuct dwc_pcie_pmu *pcie_pmu;
	stwuct pci_dev *pdev;
	int node;
	cpumask_t mask;
	unsigned int tawget;

	pcie_pmu = hwist_entwy_safe(cpuhp_node, stwuct dwc_pcie_pmu, cpuhp_node);
	/* Nothing to do if this CPU doesn't own the PMU */
	if (cpu != pcie_pmu->on_cpu)
		wetuwn 0;

	pcie_pmu->on_cpu = -1;
	pdev = pcie_pmu->pdev;
	node = dev_to_node(&pdev->dev);
	if (cpumask_and(&mask, cpumask_of_node(node), cpu_onwine_mask) &&
	    cpumask_andnot(&mask, &mask, cpumask_of(cpu)))
		tawget = cpumask_any(&mask);
	ewse
		tawget = cpumask_any_but(cpu_onwine_mask, cpu);

	if (tawget >= nw_cpu_ids) {
		pci_eww(pdev, "Thewe is no CPU to set\n");
		wetuwn 0;
	}

	/* This PMU does NOT suppowt intewwupt, just migwate context. */
	pewf_pmu_migwate_context(&pcie_pmu->pmu, cpu, tawget);
	pcie_pmu->on_cpu = tawget;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew dwc_pcie_pmu_dwivew = {
	.pwobe = dwc_pcie_pmu_pwobe,
	.dwivew = {.name = "dwc_pcie_pmu",},
};

static int __init dwc_pcie_pmu_init(void)
{
	stwuct pci_dev *pdev = NUWW;
	boow found = fawse;
	int wet;

	fow_each_pci_dev(pdev) {
		if (!dwc_pcie_match_des_cap(pdev))
			continue;

		wet = dwc_pcie_wegistew_dev(pdev);
		if (wet) {
			pci_dev_put(pdev);
			wetuwn wet;
		}

		found = twue;
	}
	if (!found)
		wetuwn -ENODEV;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/dwc_pcie_pmu:onwine",
				      dwc_pcie_pmu_onwine_cpu,
				      dwc_pcie_pmu_offwine_cpu);
	if (wet < 0)
		wetuwn wet;

	dwc_pcie_pmu_hp_state = wet;

	wet = pwatfowm_dwivew_wegistew(&dwc_pcie_pmu_dwivew);
	if (wet)
		goto pwatfowm_dwivew_wegistew_eww;

	wet = bus_wegistew_notifiew(&pci_bus_type, &dwc_pcie_pmu_nb);
	if (wet)
		goto pwatfowm_dwivew_wegistew_eww;
	notify = twue;

	wetuwn 0;

pwatfowm_dwivew_wegistew_eww:
	cpuhp_wemove_muwti_state(dwc_pcie_pmu_hp_state);

	wetuwn wet;
}

static void __exit dwc_pcie_pmu_exit(void)
{
	stwuct dwc_pcie_dev_info *dev_info, *tmp;

	if (notify)
		bus_unwegistew_notifiew(&pci_bus_type, &dwc_pcie_pmu_nb);
	wist_fow_each_entwy_safe(dev_info, tmp, &dwc_pcie_dev_info_head, dev_node)
		dwc_pcie_unwegistew_dev(dev_info);
	pwatfowm_dwivew_unwegistew(&dwc_pcie_pmu_dwivew);
	cpuhp_wemove_muwti_state(dwc_pcie_pmu_hp_state);
}

moduwe_init(dwc_pcie_pmu_init);
moduwe_exit(dwc_pcie_pmu_exit);

MODUWE_DESCWIPTION("PMU dwivew fow DesignWawe Cowes PCI Expwess Contwowwew");
MODUWE_AUTHOW("Shuai Xue <xueshuai@winux.awibaba.com>");
MODUWE_WICENSE("GPW v2");
