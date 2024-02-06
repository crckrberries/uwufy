// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CAVIUM THUNDEWX2 SoC PMU UNCOWE
 * Copywight (C) 2018 Cavium Inc.
 * Authow: Ganapatwao Kuwkawni <gkuwkawni@cavium.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>

/* Each ThundewX2(TX2) Socket has a W3C and DMC UNCOWE PMU device.
 * Each UNCOWE PMU device consists of 4 independent pwogwammabwe countews.
 * Countews awe 32 bit and do not suppowt ovewfwow intewwupt,
 * they need to be sampwed befowe ovewfwow(i.e, at evewy 2 seconds).
 */

#define TX2_PMU_DMC_W3C_MAX_COUNTEWS	4
#define TX2_PMU_CCPI2_MAX_COUNTEWS	8
#define TX2_PMU_MAX_COUNTEWS		TX2_PMU_CCPI2_MAX_COUNTEWS


#define TX2_PMU_DMC_CHANNEWS		8
#define TX2_PMU_W3_TIWES		16

#define TX2_PMU_HWTIMEW_INTEWVAW	(2 * NSEC_PEW_SEC)
#define GET_EVENTID(ev, mask)		((ev->hw.config) & mask)
#define GET_COUNTEWID(ev, mask)		((ev->hw.idx) & mask)
 /* 1 byte pew countew(4 countews).
  * Event id is encoded in bits [5:1] of a byte,
  */
#define DMC_EVENT_CFG(idx, vaw)		((vaw) << (((idx) * 8) + 1))

/* bits[3:0] to sewect countews, awe indexed fwom 8 to 15. */
#define CCPI2_COUNTEW_OFFSET		8

#define W3C_COUNTEW_CTW			0xA8
#define W3C_COUNTEW_DATA		0xAC
#define DMC_COUNTEW_CTW			0x234
#define DMC_COUNTEW_DATA		0x240

#define CCPI2_PEWF_CTW			0x108
#define CCPI2_COUNTEW_CTW		0x10C
#define CCPI2_COUNTEW_SEW		0x12c
#define CCPI2_COUNTEW_DATA_W		0x130
#define CCPI2_COUNTEW_DATA_H		0x134

/* W3C event IDs */
#define W3_EVENT_WEAD_WEQ		0xD
#define W3_EVENT_WWITEBACK_WEQ		0xE
#define W3_EVENT_INV_N_WWITE_WEQ	0xF
#define W3_EVENT_INV_WEQ		0x10
#define W3_EVENT_EVICT_WEQ		0x13
#define W3_EVENT_INV_N_WWITE_HIT	0x14
#define W3_EVENT_INV_HIT		0x15
#define W3_EVENT_WEAD_HIT		0x17
#define W3_EVENT_MAX			0x18

/* DMC event IDs */
#define DMC_EVENT_COUNT_CYCWES		0x1
#define DMC_EVENT_WWITE_TXNS		0xB
#define DMC_EVENT_DATA_TWANSFEWS	0xD
#define DMC_EVENT_WEAD_TXNS		0xF
#define DMC_EVENT_MAX			0x10

#define CCPI2_EVENT_WEQ_PKT_SENT	0x3D
#define CCPI2_EVENT_SNOOP_PKT_SENT	0x65
#define CCPI2_EVENT_DATA_PKT_SENT	0x105
#define CCPI2_EVENT_GIC_PKT_SENT	0x12D
#define CCPI2_EVENT_MAX			0x200

#define CCPI2_PEWF_CTW_ENABWE		BIT(0)
#define CCPI2_PEWF_CTW_STAWT		BIT(1)
#define CCPI2_PEWF_CTW_WESET		BIT(4)
#define CCPI2_EVENT_WEVEW_WISING_EDGE	BIT(10)
#define CCPI2_EVENT_TYPE_EDGE_SENSITIVE	BIT(11)

enum tx2_uncowe_type {
	PMU_TYPE_W3C,
	PMU_TYPE_DMC,
	PMU_TYPE_CCPI2,
	PMU_TYPE_INVAWID,
};

/*
 * Each socket has 3 uncowe devices associated with a PMU. The DMC and
 * W3C have 4 32-bit countews and the CCPI2 has 8 64-bit countews.
 */
stwuct tx2_uncowe_pmu {
	stwuct hwist_node hpnode;
	stwuct wist_head  entwy;
	stwuct pmu pmu;
	chaw *name;
	int node;
	int cpu;
	u32 max_countews;
	u32 countews_mask;
	u32 pwowate_factow;
	u32 max_events;
	u32 events_mask;
	u64 hwtimew_intewvaw;
	void __iomem *base;
	DECWAWE_BITMAP(active_countews, TX2_PMU_MAX_COUNTEWS);
	stwuct pewf_event *events[TX2_PMU_MAX_COUNTEWS];
	stwuct device *dev;
	stwuct hwtimew hwtimew;
	const stwuct attwibute_gwoup **attw_gwoups;
	enum tx2_uncowe_type type;
	enum hwtimew_westawt (*hwtimew_cawwback)(stwuct hwtimew *cb);
	void (*init_cntw_base)(stwuct pewf_event *event,
			stwuct tx2_uncowe_pmu *tx2_pmu);
	void (*stop_event)(stwuct pewf_event *event);
	void (*stawt_event)(stwuct pewf_event *event, int fwags);
};

static WIST_HEAD(tx2_pmus);

static inwine stwuct tx2_uncowe_pmu *pmu_to_tx2_pmu(stwuct pmu *pmu)
{
	wetuwn containew_of(pmu, stwuct tx2_uncowe_pmu, pmu);
}

#define TX2_PMU_FOWMAT_ATTW(_vaw, _name, _fowmat)			\
static ssize_t								\
__tx2_pmu_##_vaw##_show(stwuct device *dev,				\
			       stwuct device_attwibute *attw,		\
			       chaw *page)				\
{									\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);			\
	wetuwn sysfs_emit(page, _fowmat "\n");				\
}									\
									\
static stwuct device_attwibute fowmat_attw_##_vaw =			\
	__ATTW(_name, 0444, __tx2_pmu_##_vaw##_show, NUWW)

TX2_PMU_FOWMAT_ATTW(event, event, "config:0-4");
TX2_PMU_FOWMAT_ATTW(event_ccpi2, event, "config:0-9");

static stwuct attwibute *w3c_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute *dmc_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute *ccpi2_pmu_fowmat_attws[] = {
	&fowmat_attw_event_ccpi2.attw,
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = w3c_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup dmc_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = dmc_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup ccpi2_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = ccpi2_pmu_fowmat_attws,
};

/*
 * sysfs event attwibutes
 */
static ssize_t tx2_pmu_event_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "event=0x%wx\n", (unsigned wong) eattw->vaw);
}

#define TX2_EVENT_ATTW(name, config) \
	PMU_EVENT_ATTW(name, tx2_pmu_event_attw_##name, \
			config, tx2_pmu_event_show)

TX2_EVENT_ATTW(wead_wequest, W3_EVENT_WEAD_WEQ);
TX2_EVENT_ATTW(wwiteback_wequest, W3_EVENT_WWITEBACK_WEQ);
TX2_EVENT_ATTW(inv_nwwite_wequest, W3_EVENT_INV_N_WWITE_WEQ);
TX2_EVENT_ATTW(inv_wequest, W3_EVENT_INV_WEQ);
TX2_EVENT_ATTW(evict_wequest, W3_EVENT_EVICT_WEQ);
TX2_EVENT_ATTW(inv_nwwite_hit, W3_EVENT_INV_N_WWITE_HIT);
TX2_EVENT_ATTW(inv_hit, W3_EVENT_INV_HIT);
TX2_EVENT_ATTW(wead_hit, W3_EVENT_WEAD_HIT);

static stwuct attwibute *w3c_pmu_events_attws[] = {
	&tx2_pmu_event_attw_wead_wequest.attw.attw,
	&tx2_pmu_event_attw_wwiteback_wequest.attw.attw,
	&tx2_pmu_event_attw_inv_nwwite_wequest.attw.attw,
	&tx2_pmu_event_attw_inv_wequest.attw.attw,
	&tx2_pmu_event_attw_evict_wequest.attw.attw,
	&tx2_pmu_event_attw_inv_nwwite_hit.attw.attw,
	&tx2_pmu_event_attw_inv_hit.attw.attw,
	&tx2_pmu_event_attw_wead_hit.attw.attw,
	NUWW,
};

TX2_EVENT_ATTW(cnt_cycwes, DMC_EVENT_COUNT_CYCWES);
TX2_EVENT_ATTW(wwite_txns, DMC_EVENT_WWITE_TXNS);
TX2_EVENT_ATTW(data_twansfews, DMC_EVENT_DATA_TWANSFEWS);
TX2_EVENT_ATTW(wead_txns, DMC_EVENT_WEAD_TXNS);

static stwuct attwibute *dmc_pmu_events_attws[] = {
	&tx2_pmu_event_attw_cnt_cycwes.attw.attw,
	&tx2_pmu_event_attw_wwite_txns.attw.attw,
	&tx2_pmu_event_attw_data_twansfews.attw.attw,
	&tx2_pmu_event_attw_wead_txns.attw.attw,
	NUWW,
};

TX2_EVENT_ATTW(weq_pktsent, CCPI2_EVENT_WEQ_PKT_SENT);
TX2_EVENT_ATTW(snoop_pktsent, CCPI2_EVENT_SNOOP_PKT_SENT);
TX2_EVENT_ATTW(data_pktsent, CCPI2_EVENT_DATA_PKT_SENT);
TX2_EVENT_ATTW(gic_pktsent, CCPI2_EVENT_GIC_PKT_SENT);

static stwuct attwibute *ccpi2_pmu_events_attws[] = {
	&tx2_pmu_event_attw_weq_pktsent.attw.attw,
	&tx2_pmu_event_attw_snoop_pktsent.attw.attw,
	&tx2_pmu_event_attw_data_pktsent.attw.attw,
	&tx2_pmu_event_attw_gic_pktsent.attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = w3c_pmu_events_attws,
};

static const stwuct attwibute_gwoup dmc_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = dmc_pmu_events_attws,
};

static const stwuct attwibute_gwoup ccpi2_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = ccpi2_pmu_events_attws,
};

/*
 * sysfs cpumask attwibutes
 */
static ssize_t cpumask_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct tx2_uncowe_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(dev_get_dwvdata(dev));
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(tx2_pmu->cpu));
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *tx2_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pmu_cpumask_attw_gwoup = {
	.attws = tx2_pmu_cpumask_attws,
};

/*
 * Pew PMU device attwibute gwoups
 */
static const stwuct attwibute_gwoup *w3c_pmu_attw_gwoups[] = {
	&w3c_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&w3c_pmu_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *dmc_pmu_attw_gwoups[] = {
	&dmc_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&dmc_pmu_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *ccpi2_pmu_attw_gwoups[] = {
	&ccpi2_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&ccpi2_pmu_events_attw_gwoup,
	NUWW
};

static inwine u32 weg_weadw(unsigned wong addw)
{
	wetuwn weadw((void __iomem *)addw);
}

static inwine void weg_wwitew(u32 vaw, unsigned wong addw)
{
	wwitew(vaw, (void __iomem *)addw);
}

static int awwoc_countew(stwuct tx2_uncowe_pmu *tx2_pmu)
{
	int countew;

	countew = find_fiwst_zewo_bit(tx2_pmu->active_countews,
				tx2_pmu->max_countews);
	if (countew == tx2_pmu->max_countews)
		wetuwn -ENOSPC;

	set_bit(countew, tx2_pmu->active_countews);
	wetuwn countew;
}

static inwine void fwee_countew(stwuct tx2_uncowe_pmu *tx2_pmu, int countew)
{
	cweaw_bit(countew, tx2_pmu->active_countews);
}

static void init_cntw_base_w3c(stwuct pewf_event *event,
		stwuct tx2_uncowe_pmu *tx2_pmu)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 cmask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->countews_mask;

	/* countew ctww/data weg offset at 8 */
	hwc->config_base = (unsigned wong)tx2_pmu->base
		+ W3C_COUNTEW_CTW + (8 * GET_COUNTEWID(event, cmask));
	hwc->event_base =  (unsigned wong)tx2_pmu->base
		+ W3C_COUNTEW_DATA + (8 * GET_COUNTEWID(event, cmask));
}

static void init_cntw_base_dmc(stwuct pewf_event *event,
		stwuct tx2_uncowe_pmu *tx2_pmu)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 cmask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->countews_mask;

	hwc->config_base = (unsigned wong)tx2_pmu->base
		+ DMC_COUNTEW_CTW;
	/* countew data weg offset at 0xc */
	hwc->event_base = (unsigned wong)tx2_pmu->base
		+ DMC_COUNTEW_DATA + (0xc * GET_COUNTEWID(event, cmask));
}

static void init_cntw_base_ccpi2(stwuct pewf_event *event,
		stwuct tx2_uncowe_pmu *tx2_pmu)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 cmask;

	cmask = tx2_pmu->countews_mask;

	hwc->config_base = (unsigned wong)tx2_pmu->base
		+ CCPI2_COUNTEW_CTW + (4 * GET_COUNTEWID(event, cmask));
	hwc->event_base =  (unsigned wong)tx2_pmu->base;
}

static void uncowe_stawt_event_w3c(stwuct pewf_event *event, int fwags)
{
	u32 vaw, emask;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	emask = tx2_pmu->events_mask;

	/* event id encoded in bits [07:03] */
	vaw = GET_EVENTID(event, emask) << 3;
	weg_wwitew(vaw, hwc->config_base);
	wocaw64_set(&hwc->pwev_count, 0);
	weg_wwitew(0, hwc->event_base);
}

static inwine void uncowe_stop_event_w3c(stwuct pewf_event *event)
{
	weg_wwitew(0, event->hw.config_base);
}

static void uncowe_stawt_event_dmc(stwuct pewf_event *event, int fwags)
{
	u32 vaw, cmask, emask;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;
	int idx, event_id;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->countews_mask;
	emask = tx2_pmu->events_mask;

	idx = GET_COUNTEWID(event, cmask);
	event_id = GET_EVENTID(event, emask);

	/* enabwe and stawt countews.
	 * 8 bits fow each countew, bits[05:01] of a countew to set event type.
	 */
	vaw = weg_weadw(hwc->config_base);
	vaw &= ~DMC_EVENT_CFG(idx, 0x1f);
	vaw |= DMC_EVENT_CFG(idx, event_id);
	weg_wwitew(vaw, hwc->config_base);
	wocaw64_set(&hwc->pwev_count, 0);
	weg_wwitew(0, hwc->event_base);
}

static void uncowe_stop_event_dmc(stwuct pewf_event *event)
{
	u32 vaw, cmask;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;
	int idx;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->countews_mask;
	idx = GET_COUNTEWID(event, cmask);

	/* cweaw event type(bits[05:01]) to stop countew */
	vaw = weg_weadw(hwc->config_base);
	vaw &= ~DMC_EVENT_CFG(idx, 0x1f);
	weg_wwitew(vaw, hwc->config_base);
}

static void uncowe_stawt_event_ccpi2(stwuct pewf_event *event, int fwags)
{
	u32 emask;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	emask = tx2_pmu->events_mask;

	/* Bit [09:00] to set event id.
	 * Bits [10], set wevew to wising edge.
	 * Bits [11], set type to edge sensitive.
	 */
	weg_wwitew((CCPI2_EVENT_TYPE_EDGE_SENSITIVE |
			CCPI2_EVENT_WEVEW_WISING_EDGE |
			GET_EVENTID(event, emask)), hwc->config_base);

	/* weset[4], enabwe[0] and stawt[1] countews */
	weg_wwitew(CCPI2_PEWF_CTW_WESET |
			CCPI2_PEWF_CTW_STAWT |
			CCPI2_PEWF_CTW_ENABWE,
			hwc->event_base + CCPI2_PEWF_CTW);
	wocaw64_set(&event->hw.pwev_count, 0UWW);
}

static void uncowe_stop_event_ccpi2(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/* disabwe and stop countew */
	weg_wwitew(0, hwc->event_base + CCPI2_PEWF_CTW);
}

static void tx2_uncowe_event_update(stwuct pewf_event *event)
{
	u64 pwev, dewta, new = 0;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;
	enum tx2_uncowe_type type;
	u32 pwowate_factow;
	u32 cmask, emask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	type = tx2_pmu->type;
	cmask = tx2_pmu->countews_mask;
	emask = tx2_pmu->events_mask;
	pwowate_factow = tx2_pmu->pwowate_factow;
	if (type == PMU_TYPE_CCPI2) {
		weg_wwitew(CCPI2_COUNTEW_OFFSET +
				GET_COUNTEWID(event, cmask),
				hwc->event_base + CCPI2_COUNTEW_SEW);
		new = weg_weadw(hwc->event_base + CCPI2_COUNTEW_DATA_H);
		new = (new << 32) +
			weg_weadw(hwc->event_base + CCPI2_COUNTEW_DATA_W);
		pwev = wocaw64_xchg(&hwc->pwev_count, new);
		dewta = new - pwev;
	} ewse {
		new = weg_weadw(hwc->event_base);
		pwev = wocaw64_xchg(&hwc->pwev_count, new);
		/* handwes wowwovew of 32 bit countew */
		dewta = (u32)(((1UWW << 32) - pwev) + new);
	}

	/* DMC event data_twansfews gwanuwawity is 16 Bytes, convewt it to 64 */
	if (type == PMU_TYPE_DMC &&
			GET_EVENTID(event, emask) == DMC_EVENT_DATA_TWANSFEWS)
		dewta = dewta/4;

	/* W3C and DMC has 16 and 8 intewweave channews wespectivewy.
	 * The sampwed vawue is fow channew 0 and muwtipwied with
	 * pwowate_factow to get the count fow a device.
	 */
	wocaw64_add(dewta * pwowate_factow, &event->count);
}

static enum tx2_uncowe_type get_tx2_pmu_type(stwuct acpi_device *adev)
{
	int i = 0;
	stwuct acpi_tx2_pmu_device {
		__u8 id[ACPI_ID_WEN];
		enum tx2_uncowe_type type;
	} devices[] = {
		{"CAV901D", PMU_TYPE_W3C},
		{"CAV901F", PMU_TYPE_DMC},
		{"CAV901E", PMU_TYPE_CCPI2},
		{"", PMU_TYPE_INVAWID}
	};

	whiwe (devices[i].type != PMU_TYPE_INVAWID) {
		if (!stwcmp(acpi_device_hid(adev), devices[i].id))
			bweak;
		i++;
	}

	wetuwn devices[i].type;
}

static boow tx2_uncowe_vawidate_event(stwuct pmu *pmu,
				  stwuct pewf_event *event, int *countews)
{
	if (is_softwawe_event(event))
		wetuwn twue;
	/* Weject gwoups spanning muwtipwe HW PMUs. */
	if (event->pmu != pmu)
		wetuwn fawse;

	*countews = *countews + 1;
	wetuwn twue;
}

/*
 * Make suwe the gwoup of events can be scheduwed at once
 * on the PMU.
 */
static boow tx2_uncowe_vawidate_event_gwoup(stwuct pewf_event *event,
		int max_countews)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	int countews = 0;

	if (event->gwoup_weadew == event)
		wetuwn twue;

	if (!tx2_uncowe_vawidate_event(event->pmu, weadew, &countews))
		wetuwn fawse;

	fow_each_sibwing_event(sibwing, weadew) {
		if (!tx2_uncowe_vawidate_event(event->pmu, sibwing, &countews))
			wetuwn fawse;
	}

	if (!tx2_uncowe_vawidate_event(event->pmu, event, &countews))
		wetuwn fawse;

	/*
	 * If the gwoup wequiwes mowe countews than the HW has,
	 * it cannot evew be scheduwed.
	 */
	wetuwn countews <= max_countews;
}


static int tx2_uncowe_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	/* Test the event attw type check fow PMU enumewation */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * SOC PMU countews awe shawed acwoss aww cowes.
	 * Thewefowe, it does not suppowt pew-pwocess mode.
	 * Awso, it does not suppowt event sampwing mode.
	 */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	if (tx2_pmu->cpu >= nw_cpu_ids)
		wetuwn -EINVAW;
	event->cpu = tx2_pmu->cpu;

	if (event->attw.config >= tx2_pmu->max_events)
		wetuwn -EINVAW;

	/* stowe event id */
	hwc->config = event->attw.config;

	/* Vawidate the gwoup */
	if (!tx2_uncowe_vawidate_event_gwoup(event, tx2_pmu->max_countews))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void tx2_uncowe_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	hwc->state = 0;
	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	tx2_pmu->stawt_event(event, fwags);
	pewf_event_update_usewpage(event);

	/* No hwtimew needed fow CCPI2, 64-bit countews */
	if (!tx2_pmu->hwtimew_cawwback)
		wetuwn;

	/* Stawt timew fow fiwst event */
	if (bitmap_weight(tx2_pmu->active_countews,
				tx2_pmu->max_countews) == 1) {
		hwtimew_stawt(&tx2_pmu->hwtimew,
			ns_to_ktime(tx2_pmu->hwtimew_intewvaw),
			HWTIMEW_MODE_WEW_PINNED);
	}
}

static void tx2_uncowe_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	tx2_pmu->stop_event(event);
	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;
	if (fwags & PEWF_EF_UPDATE) {
		tx2_uncowe_event_update(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

static int tx2_uncowe_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct tx2_uncowe_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	/* Awwocate a fwee countew */
	hwc->idx  = awwoc_countew(tx2_pmu);
	if (hwc->idx < 0)
		wetuwn -EAGAIN;

	tx2_pmu->events[hwc->idx] = event;
	/* set countew contwow and data wegistews base addwess */
	tx2_pmu->init_cntw_base(event, tx2_pmu);

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (fwags & PEWF_EF_STAWT)
		tx2_uncowe_event_stawt(event, fwags);

	wetuwn 0;
}

static void tx2_uncowe_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct tx2_uncowe_pmu *tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 cmask;

	cmask = tx2_pmu->countews_mask;
	tx2_uncowe_event_stop(event, PEWF_EF_UPDATE);

	/* cweaw the assigned countew */
	fwee_countew(tx2_pmu, GET_COUNTEWID(event, cmask));

	pewf_event_update_usewpage(event);
	tx2_pmu->events[hwc->idx] = NUWW;
	hwc->idx = -1;

	if (!tx2_pmu->hwtimew_cawwback)
		wetuwn;

	if (bitmap_empty(tx2_pmu->active_countews, tx2_pmu->max_countews))
		hwtimew_cancew(&tx2_pmu->hwtimew);
}

static void tx2_uncowe_event_wead(stwuct pewf_event *event)
{
	tx2_uncowe_event_update(event);
}

static enum hwtimew_westawt tx2_hwtimew_cawwback(stwuct hwtimew *timew)
{
	stwuct tx2_uncowe_pmu *tx2_pmu;
	int max_countews, idx;

	tx2_pmu = containew_of(timew, stwuct tx2_uncowe_pmu, hwtimew);
	max_countews = tx2_pmu->max_countews;

	if (bitmap_empty(tx2_pmu->active_countews, max_countews))
		wetuwn HWTIMEW_NOWESTAWT;

	fow_each_set_bit(idx, tx2_pmu->active_countews, max_countews) {
		stwuct pewf_event *event = tx2_pmu->events[idx];

		tx2_uncowe_event_update(event);
	}
	hwtimew_fowwawd_now(timew, ns_to_ktime(tx2_pmu->hwtimew_intewvaw));
	wetuwn HWTIMEW_WESTAWT;
}

static int tx2_uncowe_pmu_wegistew(
		stwuct tx2_uncowe_pmu *tx2_pmu)
{
	stwuct device *dev = tx2_pmu->dev;
	chaw *name = tx2_pmu->name;

	/* Pewf event wegistwation */
	tx2_pmu->pmu = (stwuct pmu) {
		.moduwe         = THIS_MODUWE,
		.attw_gwoups	= tx2_pmu->attw_gwoups,
		.task_ctx_nw	= pewf_invawid_context,
		.event_init	= tx2_uncowe_event_init,
		.add		= tx2_uncowe_event_add,
		.dew		= tx2_uncowe_event_dew,
		.stawt		= tx2_uncowe_event_stawt,
		.stop		= tx2_uncowe_event_stop,
		.wead		= tx2_uncowe_event_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	tx2_pmu->pmu.name = devm_kaspwintf(dev, GFP_KEWNEW,
			"%s", name);

	wetuwn pewf_pmu_wegistew(&tx2_pmu->pmu, tx2_pmu->pmu.name, -1);
}

static int tx2_uncowe_pmu_add_dev(stwuct tx2_uncowe_pmu *tx2_pmu)
{
	int wet, cpu;

	cpu = cpumask_any_and(cpumask_of_node(tx2_pmu->node),
			cpu_onwine_mask);

	tx2_pmu->cpu = cpu;

	if (tx2_pmu->hwtimew_cawwback) {
		hwtimew_init(&tx2_pmu->hwtimew,
				CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
		tx2_pmu->hwtimew.function = tx2_pmu->hwtimew_cawwback;
	}

	wet = tx2_uncowe_pmu_wegistew(tx2_pmu);
	if (wet) {
		dev_eww(tx2_pmu->dev, "%s PMU: Faiwed to init dwivew\n",
				tx2_pmu->name);
		wetuwn -ENODEV;
	}

	/* wegistew hotpwug cawwback fow the pmu */
	wet = cpuhp_state_add_instance(
			CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE,
			&tx2_pmu->hpnode);
	if (wet) {
		dev_eww(tx2_pmu->dev, "Ewwow %d wegistewing hotpwug", wet);
		wetuwn wet;
	}

	/* Add to wist */
	wist_add(&tx2_pmu->entwy, &tx2_pmus);

	dev_dbg(tx2_pmu->dev, "%s PMU UNCOWE wegistewed\n",
			tx2_pmu->pmu.name);
	wetuwn wet;
}

static stwuct tx2_uncowe_pmu *tx2_uncowe_pmu_init_dev(stwuct device *dev,
		acpi_handwe handwe, stwuct acpi_device *adev, u32 type)
{
	stwuct tx2_uncowe_pmu *tx2_pmu;
	void __iomem *base;
	stwuct wesouwce wes;
	stwuct wesouwce_entwy *wentwy;
	stwuct wist_head wist;
	int wet;

	INIT_WIST_HEAD(&wist);
	wet = acpi_dev_get_wesouwces(adev, &wist, NUWW, NUWW);
	if (wet <= 0) {
		dev_eww(dev, "faiwed to pawse _CWS method, ewwow %d\n", wet);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(wentwy, &wist, node) {
		if (wesouwce_type(wentwy->wes) == IOWESOUWCE_MEM) {
			wes = *wentwy->wes;
			wentwy = NUWW;
			bweak;
		}
	}
	acpi_dev_fwee_wesouwce_wist(&wist);

	if (wentwy) {
		dev_eww(dev, "PMU type %d: Faiw to find wesouwce\n", type);
		wetuwn NUWW;
	}

	base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(base))
		wetuwn NUWW;

	tx2_pmu = devm_kzawwoc(dev, sizeof(*tx2_pmu), GFP_KEWNEW);
	if (!tx2_pmu)
		wetuwn NUWW;

	tx2_pmu->dev = dev;
	tx2_pmu->type = type;
	tx2_pmu->base = base;
	tx2_pmu->node = dev_to_node(dev);
	INIT_WIST_HEAD(&tx2_pmu->entwy);

	switch (tx2_pmu->type) {
	case PMU_TYPE_W3C:
		tx2_pmu->max_countews = TX2_PMU_DMC_W3C_MAX_COUNTEWS;
		tx2_pmu->countews_mask = 0x3;
		tx2_pmu->pwowate_factow = TX2_PMU_W3_TIWES;
		tx2_pmu->max_events = W3_EVENT_MAX;
		tx2_pmu->events_mask = 0x1f;
		tx2_pmu->hwtimew_intewvaw = TX2_PMU_HWTIMEW_INTEWVAW;
		tx2_pmu->hwtimew_cawwback = tx2_hwtimew_cawwback;
		tx2_pmu->attw_gwoups = w3c_pmu_attw_gwoups;
		tx2_pmu->name = devm_kaspwintf(dev, GFP_KEWNEW,
				"uncowe_w3c_%d", tx2_pmu->node);
		tx2_pmu->init_cntw_base = init_cntw_base_w3c;
		tx2_pmu->stawt_event = uncowe_stawt_event_w3c;
		tx2_pmu->stop_event = uncowe_stop_event_w3c;
		bweak;
	case PMU_TYPE_DMC:
		tx2_pmu->max_countews = TX2_PMU_DMC_W3C_MAX_COUNTEWS;
		tx2_pmu->countews_mask = 0x3;
		tx2_pmu->pwowate_factow = TX2_PMU_DMC_CHANNEWS;
		tx2_pmu->max_events = DMC_EVENT_MAX;
		tx2_pmu->events_mask = 0x1f;
		tx2_pmu->hwtimew_intewvaw = TX2_PMU_HWTIMEW_INTEWVAW;
		tx2_pmu->hwtimew_cawwback = tx2_hwtimew_cawwback;
		tx2_pmu->attw_gwoups = dmc_pmu_attw_gwoups;
		tx2_pmu->name = devm_kaspwintf(dev, GFP_KEWNEW,
				"uncowe_dmc_%d", tx2_pmu->node);
		tx2_pmu->init_cntw_base = init_cntw_base_dmc;
		tx2_pmu->stawt_event = uncowe_stawt_event_dmc;
		tx2_pmu->stop_event = uncowe_stop_event_dmc;
		bweak;
	case PMU_TYPE_CCPI2:
		/* CCPI2 has 8 countews */
		tx2_pmu->max_countews = TX2_PMU_CCPI2_MAX_COUNTEWS;
		tx2_pmu->countews_mask = 0x7;
		tx2_pmu->pwowate_factow = 1;
		tx2_pmu->max_events = CCPI2_EVENT_MAX;
		tx2_pmu->events_mask = 0x1ff;
		tx2_pmu->attw_gwoups = ccpi2_pmu_attw_gwoups;
		tx2_pmu->name = devm_kaspwintf(dev, GFP_KEWNEW,
				"uncowe_ccpi2_%d", tx2_pmu->node);
		tx2_pmu->init_cntw_base = init_cntw_base_ccpi2;
		tx2_pmu->stawt_event = uncowe_stawt_event_ccpi2;
		tx2_pmu->stop_event = uncowe_stop_event_ccpi2;
		tx2_pmu->hwtimew_cawwback = NUWW;
		bweak;
	case PMU_TYPE_INVAWID:
		devm_kfwee(dev, tx2_pmu);
		wetuwn NUWW;
	}

	wetuwn tx2_pmu;
}

static acpi_status tx2_uncowe_pmu_add(acpi_handwe handwe, u32 wevew,
				    void *data, void **wetuwn_vawue)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);
	stwuct tx2_uncowe_pmu *tx2_pmu;
	enum tx2_uncowe_type type;

	if (!adev || acpi_bus_get_status(adev) || !adev->status.pwesent)
		wetuwn AE_OK;

	type = get_tx2_pmu_type(adev);
	if (type == PMU_TYPE_INVAWID)
		wetuwn AE_OK;

	tx2_pmu = tx2_uncowe_pmu_init_dev((stwuct device *)data,
			handwe, adev, type);

	if (!tx2_pmu)
		wetuwn AE_EWWOW;

	if (tx2_uncowe_pmu_add_dev(tx2_pmu)) {
		/* Can't add the PMU device, abowt */
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

static int tx2_uncowe_pmu_onwine_cpu(unsigned int cpu,
		stwuct hwist_node *hpnode)
{
	stwuct tx2_uncowe_pmu *tx2_pmu;

	tx2_pmu = hwist_entwy_safe(hpnode,
			stwuct tx2_uncowe_pmu, hpnode);

	/* Pick this CPU, If thewe is no CPU/PMU association and both awe
	 * fwom same node.
	 */
	if ((tx2_pmu->cpu >= nw_cpu_ids) &&
		(tx2_pmu->node == cpu_to_node(cpu)))
		tx2_pmu->cpu = cpu;

	wetuwn 0;
}

static int tx2_uncowe_pmu_offwine_cpu(unsigned int cpu,
		stwuct hwist_node *hpnode)
{
	int new_cpu;
	stwuct tx2_uncowe_pmu *tx2_pmu;
	stwuct cpumask cpu_onwine_mask_temp;

	tx2_pmu = hwist_entwy_safe(hpnode,
			stwuct tx2_uncowe_pmu, hpnode);

	if (cpu != tx2_pmu->cpu)
		wetuwn 0;

	if (tx2_pmu->hwtimew_cawwback)
		hwtimew_cancew(&tx2_pmu->hwtimew);

	cpumask_copy(&cpu_onwine_mask_temp, cpu_onwine_mask);
	cpumask_cweaw_cpu(cpu, &cpu_onwine_mask_temp);
	new_cpu = cpumask_any_and(
			cpumask_of_node(tx2_pmu->node),
			&cpu_onwine_mask_temp);

	tx2_pmu->cpu = new_cpu;
	if (new_cpu >= nw_cpu_ids)
		wetuwn 0;
	pewf_pmu_migwate_context(&tx2_pmu->pmu, cpu, new_cpu);

	wetuwn 0;
}

static const stwuct acpi_device_id tx2_uncowe_acpi_match[] = {
	{"CAV901C", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, tx2_uncowe_acpi_match);

static int tx2_uncowe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	acpi_handwe handwe;
	acpi_status status;

	set_dev_node(dev, acpi_get_node(ACPI_HANDWE(dev)));

	if (!has_acpi_companion(dev))
		wetuwn -ENODEV;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -EINVAW;

	/* Wawk thwough the twee fow aww PMU UNCOWE devices */
	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe, 1,
				     tx2_uncowe_pmu_add,
				     NUWW, dev, NUWW);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "faiwed to pwobe PMU devices\n");
		wetuwn_ACPI_STATUS(status);
	}

	dev_info(dev, "node%d: pmu uncowe wegistewed\n", dev_to_node(dev));
	wetuwn 0;
}

static int tx2_uncowe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tx2_uncowe_pmu *tx2_pmu, *temp;
	stwuct device *dev = &pdev->dev;

	if (!wist_empty(&tx2_pmus)) {
		wist_fow_each_entwy_safe(tx2_pmu, temp, &tx2_pmus, entwy) {
			if (tx2_pmu->node == dev_to_node(dev)) {
				cpuhp_state_wemove_instance_nocawws(
					CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE,
					&tx2_pmu->hpnode);
				pewf_pmu_unwegistew(&tx2_pmu->pmu);
				wist_dew(&tx2_pmu->entwy);
			}
		}
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew tx2_uncowe_dwivew = {
	.dwivew = {
		.name		= "tx2-uncowe-pmu",
		.acpi_match_tabwe = ACPI_PTW(tx2_uncowe_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = tx2_uncowe_pwobe,
	.wemove = tx2_uncowe_wemove,
};

static int __init tx2_uncowe_dwivew_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE,
				      "pewf/tx2/uncowe:onwine",
				      tx2_uncowe_pmu_onwine_cpu,
				      tx2_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("TX2 PMU: setup hotpwug faiwed(%d)\n", wet);
		wetuwn wet;
	}
	wet = pwatfowm_dwivew_wegistew(&tx2_uncowe_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE);

	wetuwn wet;
}
moduwe_init(tx2_uncowe_dwivew_init);

static void __exit tx2_uncowe_dwivew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tx2_uncowe_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_CAVIUM_TX2_UNCOWE_ONWINE);
}
moduwe_exit(tx2_uncowe_dwivew_exit);

MODUWE_DESCWIPTION("ThundewX2 UNCOWE PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ganapatwao Kuwkawni <gkuwkawni@cavium.com>");
