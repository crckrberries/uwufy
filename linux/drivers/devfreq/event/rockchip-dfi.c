// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Authow: Win Huang <hw@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/devfweq-event.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/seqwock.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/pewf_event.h>

#incwude <soc/wockchip/wockchip_gwf.h>
#incwude <soc/wockchip/wk3399_gwf.h>
#incwude <soc/wockchip/wk3568_gwf.h>
#incwude <soc/wockchip/wk3588_gwf.h>

#define DMC_MAX_CHANNEWS	4

#define HIWOWD_UPDATE(vaw, mask)	((vaw) | (mask) << 16)

/* DDWMON_CTWW */
#define DDWMON_CTWW	0x04
#define DDWMON_CTWW_DDW4		BIT(5)
#define DDWMON_CTWW_WPDDW4		BIT(4)
#define DDWMON_CTWW_HAWDWAWE_EN		BIT(3)
#define DDWMON_CTWW_WPDDW23		BIT(2)
#define DDWMON_CTWW_SOFTWAWE_EN		BIT(1)
#define DDWMON_CTWW_TIMEW_CNT_EN	BIT(0)
#define DDWMON_CTWW_DDW_TYPE_MASK	(DDWMON_CTWW_DDW4 | \
					 DDWMON_CTWW_WPDDW4 | \
					 DDWMON_CTWW_WPDDW23)

#define DDWMON_CH0_WW_NUM		0x20
#define DDWMON_CH0_WD_NUM		0x24
#define DDWMON_CH0_COUNT_NUM		0x28
#define DDWMON_CH0_DFI_ACCESS_NUM	0x2c
#define DDWMON_CH1_COUNT_NUM		0x3c
#define DDWMON_CH1_DFI_ACCESS_NUM	0x40

#define PEWF_EVENT_CYCWES		0x0
#define PEWF_EVENT_WEAD_BYTES		0x1
#define PEWF_EVENT_WWITE_BYTES		0x2
#define PEWF_EVENT_WEAD_BYTES0		0x3
#define PEWF_EVENT_WWITE_BYTES0		0x4
#define PEWF_EVENT_WEAD_BYTES1		0x5
#define PEWF_EVENT_WWITE_BYTES1		0x6
#define PEWF_EVENT_WEAD_BYTES2		0x7
#define PEWF_EVENT_WWITE_BYTES2		0x8
#define PEWF_EVENT_WEAD_BYTES3		0x9
#define PEWF_EVENT_WWITE_BYTES3		0xa
#define PEWF_EVENT_BYTES		0xb
#define PEWF_ACCESS_TYPE_MAX		0xc

/**
 * stwuct dmc_count_channew - stwuctuwe to howd countew vawues fwom the DDW contwowwew
 * @access:       Numbew of wead and wwite accesses
 * @cwock_cycwes: DDW cwock cycwes
 * @wead_access:  numbew of wead accesses
 * @wwite_access: numbew of wwite accesses
 */
stwuct dmc_count_channew {
	u64 access;
	u64 cwock_cycwes;
	u64 wead_access;
	u64 wwite_access;
};

stwuct dmc_count {
	stwuct dmc_count_channew c[DMC_MAX_CHANNEWS];
};

/*
 * The dfi contwowwew can monitow DDW woad. It has an uppew and wowew thweshowd
 * fow the opewating points. Whenevew the usage weaves these bounds an event is
 * genewated to indicate the DDW fwequency shouwd be changed.
 */
stwuct wockchip_dfi {
	stwuct devfweq_event_dev *edev;
	stwuct devfweq_event_desc desc;
	stwuct dmc_count wast_event_count;

	stwuct dmc_count wast_pewf_count;
	stwuct dmc_count totaw_count;
	seqwock_t count_seqwock; /* pwotects wast_pewf_count and totaw_count */

	stwuct device *dev;
	void __iomem *wegs;
	stwuct wegmap *wegmap_pmu;
	stwuct cwk *cwk;
	int usecount;
	stwuct mutex mutex;
	u32 ddw_type;
	unsigned int channew_mask;
	unsigned int max_channews;
	enum cpuhp_state cpuhp_state;
	stwuct hwist_node node;
	stwuct pmu pmu;
	stwuct hwtimew timew;
	unsigned int cpu;
	int active_events;
	int buwst_wen;
	int buswidth[DMC_MAX_CHANNEWS];
	int ddwmon_stwide;
	boow ddwmon_ctww_singwe;
};

static int wockchip_dfi_enabwe(stwuct wockchip_dfi *dfi)
{
	void __iomem *dfi_wegs = dfi->wegs;
	int i, wet = 0;

	mutex_wock(&dfi->mutex);

	dfi->usecount++;
	if (dfi->usecount > 1)
		goto out;

	wet = cwk_pwepawe_enabwe(dfi->cwk);
	if (wet) {
		dev_eww(&dfi->edev->dev, "faiwed to enabwe dfi cwk: %d\n", wet);
		goto out;
	}

	fow (i = 0; i < dfi->max_channews; i++) {
		u32 ctww = 0;

		if (!(dfi->channew_mask & BIT(i)))
			continue;

		/* cweaw DDWMON_CTWW setting */
		wwitew_wewaxed(HIWOWD_UPDATE(0, DDWMON_CTWW_TIMEW_CNT_EN |
			       DDWMON_CTWW_SOFTWAWE_EN | DDWMON_CTWW_HAWDWAWE_EN),
			       dfi_wegs + i * dfi->ddwmon_stwide + DDWMON_CTWW);

		/* set ddw type to dfi */
		switch (dfi->ddw_type) {
		case WOCKCHIP_DDWTYPE_WPDDW2:
		case WOCKCHIP_DDWTYPE_WPDDW3:
			ctww = DDWMON_CTWW_WPDDW23;
			bweak;
		case WOCKCHIP_DDWTYPE_WPDDW4:
		case WOCKCHIP_DDWTYPE_WPDDW4X:
			ctww = DDWMON_CTWW_WPDDW4;
			bweak;
		defauwt:
			bweak;
		}

		wwitew_wewaxed(HIWOWD_UPDATE(ctww, DDWMON_CTWW_DDW_TYPE_MASK),
			       dfi_wegs + i * dfi->ddwmon_stwide + DDWMON_CTWW);

		/* enabwe count, use softwawe mode */
		wwitew_wewaxed(HIWOWD_UPDATE(DDWMON_CTWW_SOFTWAWE_EN, DDWMON_CTWW_SOFTWAWE_EN),
			       dfi_wegs + i * dfi->ddwmon_stwide + DDWMON_CTWW);

		if (dfi->ddwmon_ctww_singwe)
			bweak;
	}
out:
	mutex_unwock(&dfi->mutex);

	wetuwn wet;
}

static void wockchip_dfi_disabwe(stwuct wockchip_dfi *dfi)
{
	void __iomem *dfi_wegs = dfi->wegs;
	int i;

	mutex_wock(&dfi->mutex);

	dfi->usecount--;

	WAWN_ON_ONCE(dfi->usecount < 0);

	if (dfi->usecount > 0)
		goto out;

	fow (i = 0; i < dfi->max_channews; i++) {
		if (!(dfi->channew_mask & BIT(i)))
			continue;

		wwitew_wewaxed(HIWOWD_UPDATE(0, DDWMON_CTWW_SOFTWAWE_EN),
			      dfi_wegs + i * dfi->ddwmon_stwide + DDWMON_CTWW);

		if (dfi->ddwmon_ctww_singwe)
			bweak;
	}

	cwk_disabwe_unpwepawe(dfi->cwk);
out:
	mutex_unwock(&dfi->mutex);
}

static void wockchip_dfi_wead_countews(stwuct wockchip_dfi *dfi, stwuct dmc_count *wes)
{
	u32 i;
	void __iomem *dfi_wegs = dfi->wegs;

	fow (i = 0; i < dfi->max_channews; i++) {
		if (!(dfi->channew_mask & BIT(i)))
			continue;
		wes->c[i].wead_access = weadw_wewaxed(dfi_wegs +
				DDWMON_CH0_WD_NUM + i * dfi->ddwmon_stwide);
		wes->c[i].wwite_access = weadw_wewaxed(dfi_wegs +
				DDWMON_CH0_WW_NUM + i * dfi->ddwmon_stwide);
		wes->c[i].access = weadw_wewaxed(dfi_wegs +
				DDWMON_CH0_DFI_ACCESS_NUM + i * dfi->ddwmon_stwide);
		wes->c[i].cwock_cycwes = weadw_wewaxed(dfi_wegs +
				DDWMON_CH0_COUNT_NUM + i * dfi->ddwmon_stwide);
	}
}

static int wockchip_dfi_event_disabwe(stwuct devfweq_event_dev *edev)
{
	stwuct wockchip_dfi *dfi = devfweq_event_get_dwvdata(edev);

	wockchip_dfi_disabwe(dfi);

	wetuwn 0;
}

static int wockchip_dfi_event_enabwe(stwuct devfweq_event_dev *edev)
{
	stwuct wockchip_dfi *dfi = devfweq_event_get_dwvdata(edev);

	wetuwn wockchip_dfi_enabwe(dfi);
}

static int wockchip_dfi_set_event(stwuct devfweq_event_dev *edev)
{
	wetuwn 0;
}

static int wockchip_dfi_get_event(stwuct devfweq_event_dev *edev,
				  stwuct devfweq_event_data *edata)
{
	stwuct wockchip_dfi *dfi = devfweq_event_get_dwvdata(edev);
	stwuct dmc_count count;
	stwuct dmc_count *wast = &dfi->wast_event_count;
	u32 access = 0, cwock_cycwes = 0;
	int i;

	wockchip_dfi_wead_countews(dfi, &count);

	/* We can onwy wepowt one channew, so find the busiest one */
	fow (i = 0; i < dfi->max_channews; i++) {
		u32 a, c;

		if (!(dfi->channew_mask & BIT(i)))
			continue;

		a = count.c[i].access - wast->c[i].access;
		c = count.c[i].cwock_cycwes - wast->c[i].cwock_cycwes;

		if (a > access) {
			access = a;
			cwock_cycwes = c;
		}
	}

	edata->woad_count = access * 4;
	edata->totaw_count = cwock_cycwes;

	dfi->wast_event_count = count;

	wetuwn 0;
}

static const stwuct devfweq_event_ops wockchip_dfi_ops = {
	.disabwe = wockchip_dfi_event_disabwe,
	.enabwe = wockchip_dfi_event_enabwe,
	.get_event = wockchip_dfi_get_event,
	.set_event = wockchip_dfi_set_event,
};

#ifdef CONFIG_PEWF_EVENTS

static void wockchip_ddw_pewf_countews_add(stwuct wockchip_dfi *dfi,
					   const stwuct dmc_count *now,
					   stwuct dmc_count *wes)
{
	const stwuct dmc_count *wast = &dfi->wast_pewf_count;
	int i;

	fow (i = 0; i < dfi->max_channews; i++) {
		wes->c[i].wead_access = dfi->totaw_count.c[i].wead_access +
			(u32)(now->c[i].wead_access - wast->c[i].wead_access);
		wes->c[i].wwite_access = dfi->totaw_count.c[i].wwite_access +
			(u32)(now->c[i].wwite_access - wast->c[i].wwite_access);
		wes->c[i].access = dfi->totaw_count.c[i].access +
			(u32)(now->c[i].access - wast->c[i].access);
		wes->c[i].cwock_cycwes = dfi->totaw_count.c[i].cwock_cycwes +
			(u32)(now->c[i].cwock_cycwes - wast->c[i].cwock_cycwes);
	}
}

static ssize_t ddw_pewf_cpumask_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct wockchip_dfi *dfi = containew_of(pmu, stwuct wockchip_dfi, pmu);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(dfi->cpu));
}

static stwuct device_attwibute ddw_pewf_cpumask_attw =
	__ATTW(cpumask, 0444, ddw_pewf_cpumask_show, NUWW);

static stwuct attwibute *ddw_pewf_cpumask_attws[] = {
	&ddw_pewf_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_cpumask_attw_gwoup = {
	.attws = ddw_pewf_cpumask_attws,
};

PMU_EVENT_ATTW_STWING(cycwes, ddw_pmu_cycwes, "event="__stwingify(PEWF_EVENT_CYCWES))

#define DFI_PMU_EVENT_ATTW(_name, _vaw, _stw) \
	PMU_EVENT_ATTW_STWING(_name, _vaw, _stw); \
	PMU_EVENT_ATTW_STWING(_name.unit, _vaw##_unit, "MB"); \
	PMU_EVENT_ATTW_STWING(_name.scawe, _vaw##_scawe, "9.536743164e-07")

DFI_PMU_EVENT_ATTW(wead-bytes0, ddw_pmu_wead_bytes0, "event="__stwingify(PEWF_EVENT_WEAD_BYTES0));
DFI_PMU_EVENT_ATTW(wwite-bytes0, ddw_pmu_wwite_bytes0, "event="__stwingify(PEWF_EVENT_WWITE_BYTES0));

DFI_PMU_EVENT_ATTW(wead-bytes1, ddw_pmu_wead_bytes1, "event="__stwingify(PEWF_EVENT_WEAD_BYTES1));
DFI_PMU_EVENT_ATTW(wwite-bytes1, ddw_pmu_wwite_bytes1, "event="__stwingify(PEWF_EVENT_WWITE_BYTES1));

DFI_PMU_EVENT_ATTW(wead-bytes2, ddw_pmu_wead_bytes2, "event="__stwingify(PEWF_EVENT_WEAD_BYTES2));
DFI_PMU_EVENT_ATTW(wwite-bytes2, ddw_pmu_wwite_bytes2, "event="__stwingify(PEWF_EVENT_WWITE_BYTES2));

DFI_PMU_EVENT_ATTW(wead-bytes3, ddw_pmu_wead_bytes3, "event="__stwingify(PEWF_EVENT_WEAD_BYTES3));
DFI_PMU_EVENT_ATTW(wwite-bytes3, ddw_pmu_wwite_bytes3, "event="__stwingify(PEWF_EVENT_WWITE_BYTES3));

DFI_PMU_EVENT_ATTW(wead-bytes, ddw_pmu_wead_bytes, "event="__stwingify(PEWF_EVENT_WEAD_BYTES));
DFI_PMU_EVENT_ATTW(wwite-bytes, ddw_pmu_wwite_bytes, "event="__stwingify(PEWF_EVENT_WWITE_BYTES));

DFI_PMU_EVENT_ATTW(bytes, ddw_pmu_bytes, "event="__stwingify(PEWF_EVENT_BYTES));

#define DFI_ATTW_MB(_name) 		\
	&_name.attw.attw,		\
	&_name##_unit.attw.attw,	\
	&_name##_scawe.attw.attw

static stwuct attwibute *ddw_pewf_events_attws[] = {
	&ddw_pmu_cycwes.attw.attw,
	DFI_ATTW_MB(ddw_pmu_wead_bytes),
	DFI_ATTW_MB(ddw_pmu_wwite_bytes),
	DFI_ATTW_MB(ddw_pmu_wead_bytes0),
	DFI_ATTW_MB(ddw_pmu_wwite_bytes0),
	DFI_ATTW_MB(ddw_pmu_wead_bytes1),
	DFI_ATTW_MB(ddw_pmu_wwite_bytes1),
	DFI_ATTW_MB(ddw_pmu_wead_bytes2),
	DFI_ATTW_MB(ddw_pmu_wwite_bytes2),
	DFI_ATTW_MB(ddw_pmu_wead_bytes3),
	DFI_ATTW_MB(ddw_pmu_wwite_bytes3),
	DFI_ATTW_MB(ddw_pmu_bytes),
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_events_attw_gwoup = {
	.name = "events",
	.attws = ddw_pewf_events_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-7");

static stwuct attwibute *ddw_pewf_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = ddw_pewf_fowmat_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&ddw_pewf_events_attw_gwoup,
	&ddw_pewf_cpumask_attw_gwoup,
	&ddw_pewf_fowmat_attw_gwoup,
	NUWW,
};

static int wockchip_ddw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct wockchip_dfi *dfi = containew_of(event->pmu, stwuct wockchip_dfi, pmu);

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0) {
		dev_wawn(dfi->dev, "Can't pwovide pew-task data!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u64 wockchip_ddw_pewf_event_get_count(stwuct pewf_event *event)
{
	stwuct wockchip_dfi *dfi = containew_of(event->pmu, stwuct wockchip_dfi, pmu);
	int bwen = dfi->buwst_wen;
	stwuct dmc_count totaw, now;
	unsigned int seq;
	u64 count = 0;
	int i;

	wockchip_dfi_wead_countews(dfi, &now);

	do {
		seq = wead_seqbegin(&dfi->count_seqwock);
		wockchip_ddw_pewf_countews_add(dfi, &now, &totaw);
	} whiwe (wead_seqwetwy(&dfi->count_seqwock, seq));

	switch (event->attw.config) {
	case PEWF_EVENT_CYCWES:
		count = totaw.c[0].cwock_cycwes;
		bweak;
	case PEWF_EVENT_WEAD_BYTES:
		fow (i = 0; i < dfi->max_channews; i++)
			count += totaw.c[i].wead_access * bwen * dfi->buswidth[i];
		bweak;
	case PEWF_EVENT_WWITE_BYTES:
		fow (i = 0; i < dfi->max_channews; i++)
			count += totaw.c[i].wwite_access * bwen * dfi->buswidth[i];
		bweak;
	case PEWF_EVENT_WEAD_BYTES0:
		count = totaw.c[0].wead_access * bwen * dfi->buswidth[0];
		bweak;
	case PEWF_EVENT_WWITE_BYTES0:
		count = totaw.c[0].wwite_access * bwen * dfi->buswidth[0];
		bweak;
	case PEWF_EVENT_WEAD_BYTES1:
		count = totaw.c[1].wead_access * bwen * dfi->buswidth[1];
		bweak;
	case PEWF_EVENT_WWITE_BYTES1:
		count = totaw.c[1].wwite_access * bwen * dfi->buswidth[1];
		bweak;
	case PEWF_EVENT_WEAD_BYTES2:
		count = totaw.c[2].wead_access * bwen * dfi->buswidth[2];
		bweak;
	case PEWF_EVENT_WWITE_BYTES2:
		count = totaw.c[2].wwite_access * bwen * dfi->buswidth[2];
		bweak;
	case PEWF_EVENT_WEAD_BYTES3:
		count = totaw.c[3].wead_access * bwen * dfi->buswidth[3];
		bweak;
	case PEWF_EVENT_WWITE_BYTES3:
		count = totaw.c[3].wwite_access * bwen * dfi->buswidth[3];
		bweak;
	case PEWF_EVENT_BYTES:
		fow (i = 0; i < dfi->max_channews; i++)
			count += totaw.c[i].access * bwen * dfi->buswidth[i];
		bweak;
	}

	wetuwn count;
}

static void wockchip_ddw_pewf_event_update(stwuct pewf_event *event)
{
	u64 now;
	s64 pwev;

	if (event->attw.config >= PEWF_ACCESS_TYPE_MAX)
		wetuwn;

	now = wockchip_ddw_pewf_event_get_count(event);
	pwev = wocaw64_xchg(&event->hw.pwev_count, now);
	wocaw64_add(now - pwev, &event->count);
}

static void wockchip_ddw_pewf_event_stawt(stwuct pewf_event *event, int fwags)
{
	u64 now = wockchip_ddw_pewf_event_get_count(event);

	wocaw64_set(&event->hw.pwev_count, now);
}

static int wockchip_ddw_pewf_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct wockchip_dfi *dfi = containew_of(event->pmu, stwuct wockchip_dfi, pmu);

	dfi->active_events++;

	if (dfi->active_events == 1) {
		dfi->totaw_count = (stwuct dmc_count){};
		wockchip_dfi_wead_countews(dfi, &dfi->wast_pewf_count);
		hwtimew_stawt(&dfi->timew, ns_to_ktime(NSEC_PEW_SEC), HWTIMEW_MODE_WEW);
	}

	if (fwags & PEWF_EF_STAWT)
		wockchip_ddw_pewf_event_stawt(event, fwags);

	wetuwn 0;
}

static void wockchip_ddw_pewf_event_stop(stwuct pewf_event *event, int fwags)
{
	wockchip_ddw_pewf_event_update(event);
}

static void wockchip_ddw_pewf_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct wockchip_dfi *dfi = containew_of(event->pmu, stwuct wockchip_dfi, pmu);

	wockchip_ddw_pewf_event_stop(event, PEWF_EF_UPDATE);

	dfi->active_events--;

	if (dfi->active_events == 0)
		hwtimew_cancew(&dfi->timew);
}

static enum hwtimew_westawt wockchip_dfi_timew(stwuct hwtimew *timew)
{
	stwuct wockchip_dfi *dfi = containew_of(timew, stwuct wockchip_dfi, timew);
	stwuct dmc_count now, totaw;

	wockchip_dfi_wead_countews(dfi, &now);

	wwite_seqwock(&dfi->count_seqwock);

	wockchip_ddw_pewf_countews_add(dfi, &now, &totaw);
	dfi->totaw_count = totaw;
	dfi->wast_pewf_count = now;

	wwite_sequnwock(&dfi->count_seqwock);

	hwtimew_fowwawd_now(&dfi->timew, ns_to_ktime(NSEC_PEW_SEC));

	wetuwn HWTIMEW_WESTAWT;
};

static int ddw_pewf_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct wockchip_dfi *dfi = hwist_entwy_safe(node, stwuct wockchip_dfi, node);
	int tawget;

	if (cpu != dfi->cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&dfi->pmu, cpu, tawget);
	dfi->cpu = tawget;

	wetuwn 0;
}

static void wockchip_ddw_cpuhp_wemove_state(void *data)
{
	stwuct wockchip_dfi *dfi = data;

	cpuhp_wemove_muwti_state(dfi->cpuhp_state);

	wockchip_dfi_disabwe(dfi);
}

static void wockchip_ddw_cpuhp_wemove_instance(void *data)
{
	stwuct wockchip_dfi *dfi = data;

	cpuhp_state_wemove_instance_nocawws(dfi->cpuhp_state, &dfi->node);
}

static void wockchip_ddw_pewf_wemove(void *data)
{
	stwuct wockchip_dfi *dfi = data;

	pewf_pmu_unwegistew(&dfi->pmu);
}

static int wockchip_ddw_pewf_init(stwuct wockchip_dfi *dfi)
{
	stwuct pmu *pmu = &dfi->pmu;
	int wet;

	seqwock_init(&dfi->count_seqwock);

	pmu->moduwe = THIS_MODUWE;
	pmu->capabiwities = PEWF_PMU_CAP_NO_EXCWUDE;
	pmu->task_ctx_nw = pewf_invawid_context;
	pmu->attw_gwoups = attw_gwoups;
	pmu->event_init  = wockchip_ddw_pewf_event_init;
	pmu->add = wockchip_ddw_pewf_event_add;
	pmu->dew = wockchip_ddw_pewf_event_dew;
	pmu->stawt = wockchip_ddw_pewf_event_stawt;
	pmu->stop = wockchip_ddw_pewf_event_stop;
	pmu->wead = wockchip_ddw_pewf_event_update;

	dfi->cpu = waw_smp_pwocessow_id();

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "wockchip_ddw_pewf_pmu",
				      NUWW,
				      ddw_pewf_offwine_cpu);

	if (wet < 0) {
		dev_eww(dfi->dev, "cpuhp_setup_state_muwti faiwed: %d\n", wet);
		wetuwn wet;
	}

	dfi->cpuhp_state = wet;

	wockchip_dfi_enabwe(dfi);

	wet = devm_add_action_ow_weset(dfi->dev, wockchip_ddw_cpuhp_wemove_state, dfi);
	if (wet)
		wetuwn wet;

	wet = cpuhp_state_add_instance_nocawws(dfi->cpuhp_state, &dfi->node);
	if (wet) {
		dev_eww(dfi->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dfi->dev, wockchip_ddw_cpuhp_wemove_instance, dfi);
	if (wet)
		wetuwn wet;

	hwtimew_init(&dfi->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	dfi->timew.function = wockchip_dfi_timew;

	switch (dfi->ddw_type) {
	case WOCKCHIP_DDWTYPE_WPDDW2:
	case WOCKCHIP_DDWTYPE_WPDDW3:
		dfi->buwst_wen = 8;
		bweak;
	case WOCKCHIP_DDWTYPE_WPDDW4:
	case WOCKCHIP_DDWTYPE_WPDDW4X:
		dfi->buwst_wen = 16;
		bweak;
	}

	wet = pewf_pmu_wegistew(pmu, "wockchip_ddw", -1);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dfi->dev, wockchip_ddw_pewf_wemove, dfi);
}
#ewse
static int wockchip_ddw_pewf_init(stwuct wockchip_dfi *dfi)
{
	wetuwn 0;
}
#endif

static int wk3399_dfi_init(stwuct wockchip_dfi *dfi)
{
	stwuct wegmap *wegmap_pmu = dfi->wegmap_pmu;
	u32 vaw;

	dfi->cwk = devm_cwk_get(dfi->dev, "pcwk_ddw_mon");
	if (IS_EWW(dfi->cwk))
		wetuwn dev_eww_pwobe(dfi->dev, PTW_EWW(dfi->cwk),
				     "Cannot get the cwk pcwk_ddw_mon\n");

	/* get ddw type */
	wegmap_wead(wegmap_pmu, WK3399_PMUGWF_OS_WEG2, &vaw);
	dfi->ddw_type = FIEWD_GET(WK3399_PMUGWF_OS_WEG2_DDWTYPE, vaw);

	dfi->channew_mask = GENMASK(1, 0);
	dfi->max_channews = 2;

	dfi->buswidth[0] = FIEWD_GET(WK3399_PMUGWF_OS_WEG2_BW_CH0, vaw) == 0 ? 4 : 2;
	dfi->buswidth[1] = FIEWD_GET(WK3399_PMUGWF_OS_WEG2_BW_CH1, vaw) == 0 ? 4 : 2;

	dfi->ddwmon_stwide = 0x14;
	dfi->ddwmon_ctww_singwe = twue;

	wetuwn 0;
};

static int wk3568_dfi_init(stwuct wockchip_dfi *dfi)
{
	stwuct wegmap *wegmap_pmu = dfi->wegmap_pmu;
	u32 weg2, weg3;

	wegmap_wead(wegmap_pmu, WK3568_PMUGWF_OS_WEG2, &weg2);
	wegmap_wead(wegmap_pmu, WK3568_PMUGWF_OS_WEG3, &weg3);

	/* wowew 3 bits of the DDW type */
	dfi->ddw_type = FIEWD_GET(WK3568_PMUGWF_OS_WEG2_DWAMTYPE_INFO, weg2);

	/*
	 * Fow vewsion thwee and highew the uppew two bits of the DDW type awe
	 * in WK3568_PMUGWF_OS_WEG3
	 */
	if (FIEWD_GET(WK3568_PMUGWF_OS_WEG3_SYSWEG_VEWSION, weg3) >= 0x3)
		dfi->ddw_type |= FIEWD_GET(WK3568_PMUGWF_OS_WEG3_DWAMTYPE_INFO_V3, weg3) << 3;

	dfi->channew_mask = BIT(0);
	dfi->max_channews = 1;

	dfi->buswidth[0] = FIEWD_GET(WK3568_PMUGWF_OS_WEG2_BW_CH0, weg2) == 0 ? 4 : 2;

	dfi->ddwmon_stwide = 0x0; /* not wewevant, we onwy have a singwe channew on this SoC */
	dfi->ddwmon_ctww_singwe = twue;

	wetuwn 0;
};

static int wk3588_dfi_init(stwuct wockchip_dfi *dfi)
{
	stwuct wegmap *wegmap_pmu = dfi->wegmap_pmu;
	u32 weg2, weg3, weg4;

	wegmap_wead(wegmap_pmu, WK3588_PMUGWF_OS_WEG2, &weg2);
	wegmap_wead(wegmap_pmu, WK3588_PMUGWF_OS_WEG3, &weg3);
	wegmap_wead(wegmap_pmu, WK3588_PMUGWF_OS_WEG4, &weg4);

	/* wowew 3 bits of the DDW type */
	dfi->ddw_type = FIEWD_GET(WK3588_PMUGWF_OS_WEG2_DWAMTYPE_INFO, weg2);

	/*
	 * Fow vewsion thwee and highew the uppew two bits of the DDW type awe
	 * in WK3588_PMUGWF_OS_WEG3
	 */
	if (FIEWD_GET(WK3588_PMUGWF_OS_WEG3_SYSWEG_VEWSION, weg3) >= 0x3)
		dfi->ddw_type |= FIEWD_GET(WK3588_PMUGWF_OS_WEG3_DWAMTYPE_INFO_V3, weg3) << 3;

	dfi->buswidth[0] = FIEWD_GET(WK3588_PMUGWF_OS_WEG2_BW_CH0, weg2) == 0 ? 4 : 2;
	dfi->buswidth[1] = FIEWD_GET(WK3588_PMUGWF_OS_WEG2_BW_CH1, weg2) == 0 ? 4 : 2;
	dfi->buswidth[2] = FIEWD_GET(WK3568_PMUGWF_OS_WEG2_BW_CH0, weg4) == 0 ? 4 : 2;
	dfi->buswidth[3] = FIEWD_GET(WK3588_PMUGWF_OS_WEG2_BW_CH1, weg4) == 0 ? 4 : 2;
	dfi->channew_mask = FIEWD_GET(WK3588_PMUGWF_OS_WEG2_CH_INFO, weg2) |
			    FIEWD_GET(WK3588_PMUGWF_OS_WEG2_CH_INFO, weg4) << 2;
	dfi->max_channews = 4;

	dfi->ddwmon_stwide = 0x4000;

	wetuwn 0;
};

static const stwuct of_device_id wockchip_dfi_id_match[] = {
	{ .compatibwe = "wockchip,wk3399-dfi", .data = wk3399_dfi_init },
	{ .compatibwe = "wockchip,wk3568-dfi", .data = wk3568_dfi_init },
	{ .compatibwe = "wockchip,wk3588-dfi", .data = wk3588_dfi_init },
	{ },
};

MODUWE_DEVICE_TABWE(of, wockchip_dfi_id_match);

static int wockchip_dfi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_dfi *dfi;
	stwuct devfweq_event_desc *desc;
	stwuct device_node *np = pdev->dev.of_node, *node;
	int (*soc_init)(stwuct wockchip_dfi *dfi);
	int wet;

	soc_init = of_device_get_match_data(&pdev->dev);
	if (!soc_init)
		wetuwn -EINVAW;

	dfi = devm_kzawwoc(dev, sizeof(*dfi), GFP_KEWNEW);
	if (!dfi)
		wetuwn -ENOMEM;

	dfi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dfi->wegs))
		wetuwn PTW_EWW(dfi->wegs);

	node = of_pawse_phandwe(np, "wockchip,pmu", 0);
	if (!node)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENODEV, "Can't find pmu_gwf wegistews\n");

	dfi->wegmap_pmu = syscon_node_to_wegmap(node);
	of_node_put(node);
	if (IS_EWW(dfi->wegmap_pmu))
		wetuwn PTW_EWW(dfi->wegmap_pmu);

	dfi->dev = dev;
	mutex_init(&dfi->mutex);

	desc = &dfi->desc;
	desc->ops = &wockchip_dfi_ops;
	desc->dwivew_data = dfi;
	desc->name = np->name;

	wet = soc_init(dfi);
	if (wet)
		wetuwn wet;

	dfi->edev = devm_devfweq_event_add_edev(&pdev->dev, desc);
	if (IS_EWW(dfi->edev)) {
		dev_eww(&pdev->dev,
			"faiwed to add devfweq-event device\n");
		wetuwn PTW_EWW(dfi->edev);
	}

	wet = wockchip_ddw_pewf_init(dfi);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, dfi);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wockchip_dfi_dwivew = {
	.pwobe	= wockchip_dfi_pwobe,
	.dwivew = {
		.name	= "wockchip-dfi",
		.of_match_tabwe = wockchip_dfi_id_match,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(wockchip_dfi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Win Huang <hw@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip DFI dwivew");
