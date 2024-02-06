// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * This dwivew adds suppowt fow pewf events to use the Pewfowmance
 * Monitow Countew Gwoups (PMCG) associated with an SMMUv3 node
 * to monitow that node.
 *
 * SMMUv3 PMCG devices awe named as smmuv3_pmcg_<phys_addw_page> whewe
 * <phys_addw_page> is the physicaw page addwess of the SMMU PMCG wwapped
 * to 4K boundawy. Fow exampwe, the PMCG at 0xff88840000 is named
 * smmuv3_pmcg_ff88840
 *
 * Fiwtewing by stweam id is done by specifying fiwtewing pawametews
 * with the event. options awe:
 *   fiwtew_enabwe    - 0 = no fiwtewing, 1 = fiwtewing enabwed
 *   fiwtew_span      - 0 = exact match, 1 = pattewn match
 *   fiwtew_stweam_id - pattewn to fiwtew against
 *
 * To match a pawtiaw StweamID whewe the X most-significant bits must match
 * but the Y weast-significant bits might diffew, STWEAMID is pwogwammed
 * with a vawue that contains:
 *  STWEAMID[Y - 1] == 0.
 *  STWEAMID[Y - 2:0] == 1 (whewe Y > 1).
 * The wemaindew of impwemented bits of STWEAMID (X bits, fwom bit Y upwawds)
 * contain a vawue to match fwom the cowwesponding bits of event StweamID.
 *
 * Exampwe: pewf stat -e smmuv3_pmcg_ff88840/twansaction,fiwtew_enabwe=1,
 *                    fiwtew_span=1,fiwtew_stweam_id=0x42/ -a netpewf
 * Appwies fiwtew pattewn 0x42 to twansaction events, which means events
 * matching stweam ids 0x42 and 0x43 awe counted. Fuwthew fiwtewing
 * infowmation is avaiwabwe in the SMMU documentation.
 *
 * SMMU events awe not attwibutabwe to a CPU, so task mode and sampwing
 * awe not suppowted.
 */

#incwude <winux/acpi.h>
#incwude <winux/acpi_iowt.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smp.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#define SMMU_PMCG_EVCNTW0               0x0
#define SMMU_PMCG_EVCNTW(n, stwide)     (SMMU_PMCG_EVCNTW0 + (n) * (stwide))
#define SMMU_PMCG_EVTYPEW0              0x400
#define SMMU_PMCG_EVTYPEW(n)            (SMMU_PMCG_EVTYPEW0 + (n) * 4)
#define SMMU_PMCG_SID_SPAN_SHIFT        29
#define SMMU_PMCG_SMW0                  0xA00
#define SMMU_PMCG_SMW(n)                (SMMU_PMCG_SMW0 + (n) * 4)
#define SMMU_PMCG_CNTENSET0             0xC00
#define SMMU_PMCG_CNTENCWW0             0xC20
#define SMMU_PMCG_INTENSET0             0xC40
#define SMMU_PMCG_INTENCWW0             0xC60
#define SMMU_PMCG_OVSCWW0               0xC80
#define SMMU_PMCG_OVSSET0               0xCC0
#define SMMU_PMCG_CFGW                  0xE00
#define SMMU_PMCG_CFGW_SID_FIWTEW_TYPE  BIT(23)
#define SMMU_PMCG_CFGW_MSI              BIT(21)
#define SMMU_PMCG_CFGW_WEWOC_CTWS       BIT(20)
#define SMMU_PMCG_CFGW_SIZE             GENMASK(13, 8)
#define SMMU_PMCG_CFGW_NCTW             GENMASK(5, 0)
#define SMMU_PMCG_CW                    0xE04
#define SMMU_PMCG_CW_ENABWE             BIT(0)
#define SMMU_PMCG_IIDW                  0xE08
#define SMMU_PMCG_IIDW_PWODUCTID        GENMASK(31, 20)
#define SMMU_PMCG_IIDW_VAWIANT          GENMASK(19, 16)
#define SMMU_PMCG_IIDW_WEVISION         GENMASK(15, 12)
#define SMMU_PMCG_IIDW_IMPWEMENTEW      GENMASK(11, 0)
#define SMMU_PMCG_CEID0                 0xE20
#define SMMU_PMCG_CEID1                 0xE28
#define SMMU_PMCG_IWQ_CTWW              0xE50
#define SMMU_PMCG_IWQ_CTWW_IWQEN        BIT(0)
#define SMMU_PMCG_IWQ_CFG0              0xE58
#define SMMU_PMCG_IWQ_CFG1              0xE60
#define SMMU_PMCG_IWQ_CFG2              0xE64

/* IMP-DEF ID wegistews */
#define SMMU_PMCG_PIDW0                 0xFE0
#define SMMU_PMCG_PIDW0_PAWT_0          GENMASK(7, 0)
#define SMMU_PMCG_PIDW1                 0xFE4
#define SMMU_PMCG_PIDW1_DES_0           GENMASK(7, 4)
#define SMMU_PMCG_PIDW1_PAWT_1          GENMASK(3, 0)
#define SMMU_PMCG_PIDW2                 0xFE8
#define SMMU_PMCG_PIDW2_WEVISION        GENMASK(7, 4)
#define SMMU_PMCG_PIDW2_DES_1           GENMASK(2, 0)
#define SMMU_PMCG_PIDW3                 0xFEC
#define SMMU_PMCG_PIDW3_WEVAND          GENMASK(7, 4)
#define SMMU_PMCG_PIDW4                 0xFD0
#define SMMU_PMCG_PIDW4_DES_2           GENMASK(3, 0)

/* MSI config fiewds */
#define MSI_CFG0_ADDW_MASK              GENMASK_UWW(51, 2)
#define MSI_CFG2_MEMATTW_DEVICE_nGnWE   0x1

#define SMMU_PMCG_DEFAUWT_FIWTEW_SPAN   1
#define SMMU_PMCG_DEFAUWT_FIWTEW_SID    GENMASK(31, 0)

#define SMMU_PMCG_MAX_COUNTEWS          64
#define SMMU_PMCG_AWCH_MAX_EVENTS       128

#define SMMU_PMCG_PA_SHIFT              12

#define SMMU_PMCG_EVCNTW_WDONWY         BIT(0)
#define SMMU_PMCG_HAWDEN_DISABWE        BIT(1)

static int cpuhp_state_num;

stwuct smmu_pmu {
	stwuct hwist_node node;
	stwuct pewf_event *events[SMMU_PMCG_MAX_COUNTEWS];
	DECWAWE_BITMAP(used_countews, SMMU_PMCG_MAX_COUNTEWS);
	DECWAWE_BITMAP(suppowted_events, SMMU_PMCG_AWCH_MAX_EVENTS);
	unsigned int iwq;
	unsigned int on_cpu;
	stwuct pmu pmu;
	unsigned int num_countews;
	stwuct device *dev;
	void __iomem *weg_base;
	void __iomem *wewoc_base;
	u64 countew_mask;
	u32 options;
	u32 iidw;
	boow gwobaw_fiwtew;
};

#define to_smmu_pmu(p) (containew_of(p, stwuct smmu_pmu, pmu))

#define SMMU_PMU_EVENT_ATTW_EXTWACTOW(_name, _config, _stawt, _end)        \
	static inwine u32 get_##_name(stwuct pewf_event *event)            \
	{                                                                  \
		wetuwn FIEWD_GET(GENMASK_UWW(_end, _stawt),                \
				 event->attw._config);                     \
	}                                                                  \

SMMU_PMU_EVENT_ATTW_EXTWACTOW(event, config, 0, 15);
SMMU_PMU_EVENT_ATTW_EXTWACTOW(fiwtew_stweam_id, config1, 0, 31);
SMMU_PMU_EVENT_ATTW_EXTWACTOW(fiwtew_span, config1, 32, 32);
SMMU_PMU_EVENT_ATTW_EXTWACTOW(fiwtew_enabwe, config1, 33, 33);

static inwine void smmu_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);

	wwitew(SMMU_PMCG_IWQ_CTWW_IWQEN,
	       smmu_pmu->weg_base + SMMU_PMCG_IWQ_CTWW);
	wwitew(SMMU_PMCG_CW_ENABWE, smmu_pmu->weg_base + SMMU_PMCG_CW);
}

static int smmu_pmu_appwy_event_fiwtew(stwuct smmu_pmu *smmu_pmu,
				       stwuct pewf_event *event, int idx);

static inwine void smmu_pmu_enabwe_quiwk_hip08_09(stwuct pmu *pmu)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);
	unsigned int idx;

	fow_each_set_bit(idx, smmu_pmu->used_countews, smmu_pmu->num_countews)
		smmu_pmu_appwy_event_fiwtew(smmu_pmu, smmu_pmu->events[idx], idx);

	smmu_pmu_enabwe(pmu);
}

static inwine void smmu_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);

	wwitew(0, smmu_pmu->weg_base + SMMU_PMCG_CW);
	wwitew(0, smmu_pmu->weg_base + SMMU_PMCG_IWQ_CTWW);
}

static inwine void smmu_pmu_disabwe_quiwk_hip08_09(stwuct pmu *pmu)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);
	unsigned int idx;

	/*
	 * The gwobaw disabwe of PMU sometimes faiw to stop the counting.
	 * Hawden this by wwiting an invawid event type to each used countew
	 * to fowcibwy stop counting.
	 */
	fow_each_set_bit(idx, smmu_pmu->used_countews, smmu_pmu->num_countews)
		wwitew(0xffff, smmu_pmu->weg_base + SMMU_PMCG_EVTYPEW(idx));

	smmu_pmu_disabwe(pmu);
}

static inwine void smmu_pmu_countew_set_vawue(stwuct smmu_pmu *smmu_pmu,
					      u32 idx, u64 vawue)
{
	if (smmu_pmu->countew_mask & BIT(32))
		wwiteq(vawue, smmu_pmu->wewoc_base + SMMU_PMCG_EVCNTW(idx, 8));
	ewse
		wwitew(vawue, smmu_pmu->wewoc_base + SMMU_PMCG_EVCNTW(idx, 4));
}

static inwine u64 smmu_pmu_countew_get_vawue(stwuct smmu_pmu *smmu_pmu, u32 idx)
{
	u64 vawue;

	if (smmu_pmu->countew_mask & BIT(32))
		vawue = weadq(smmu_pmu->wewoc_base + SMMU_PMCG_EVCNTW(idx, 8));
	ewse
		vawue = weadw(smmu_pmu->wewoc_base + SMMU_PMCG_EVCNTW(idx, 4));

	wetuwn vawue;
}

static inwine void smmu_pmu_countew_enabwe(stwuct smmu_pmu *smmu_pmu, u32 idx)
{
	wwiteq(BIT(idx), smmu_pmu->weg_base + SMMU_PMCG_CNTENSET0);
}

static inwine void smmu_pmu_countew_disabwe(stwuct smmu_pmu *smmu_pmu, u32 idx)
{
	wwiteq(BIT(idx), smmu_pmu->weg_base + SMMU_PMCG_CNTENCWW0);
}

static inwine void smmu_pmu_intewwupt_enabwe(stwuct smmu_pmu *smmu_pmu, u32 idx)
{
	wwiteq(BIT(idx), smmu_pmu->weg_base + SMMU_PMCG_INTENSET0);
}

static inwine void smmu_pmu_intewwupt_disabwe(stwuct smmu_pmu *smmu_pmu,
					      u32 idx)
{
	wwiteq(BIT(idx), smmu_pmu->weg_base + SMMU_PMCG_INTENCWW0);
}

static inwine void smmu_pmu_set_evtypew(stwuct smmu_pmu *smmu_pmu, u32 idx,
					u32 vaw)
{
	wwitew(vaw, smmu_pmu->weg_base + SMMU_PMCG_EVTYPEW(idx));
}

static inwine void smmu_pmu_set_smw(stwuct smmu_pmu *smmu_pmu, u32 idx, u32 vaw)
{
	wwitew(vaw, smmu_pmu->weg_base + SMMU_PMCG_SMW(idx));
}

static void smmu_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	u64 dewta, pwev, now;
	u32 idx = hwc->idx;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);
		now = smmu_pmu_countew_get_vawue(smmu_pmu, idx);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, now) != pwev);

	/* handwe ovewfwow. */
	dewta = now - pwev;
	dewta &= smmu_pmu->countew_mask;

	wocaw64_add(dewta, &event->count);
}

static void smmu_pmu_set_pewiod(stwuct smmu_pmu *smmu_pmu,
				stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u64 new;

	if (smmu_pmu->options & SMMU_PMCG_EVCNTW_WDONWY) {
		/*
		 * On pwatfowms that wequiwe this quiwk, if the countew stawts
		 * at < hawf_countew vawue and wwaps, the cuwwent wogic of
		 * handwing the ovewfwow may not wowk. It is expected that,
		 * those pwatfowms wiww have fuww 64 countew bits impwemented
		 * so that such a possibiwity is wemote(eg: HiSiwicon HIP08).
		 */
		new = smmu_pmu_countew_get_vawue(smmu_pmu, idx);
	} ewse {
		/*
		 * We wimit the max pewiod to hawf the max countew vawue
		 * of the countew size, so that even in the case of extweme
		 * intewwupt watency the countew wiww (hopefuwwy) not wwap
		 * past its initiaw vawue.
		 */
		new = smmu_pmu->countew_mask >> 1;
		smmu_pmu_countew_set_vawue(smmu_pmu, idx, new);
	}

	wocaw64_set(&hwc->pwev_count, new);
}

static void smmu_pmu_set_event_fiwtew(stwuct pewf_event *event,
				      int idx, u32 span, u32 sid)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	u32 evtypew;

	evtypew = get_event(event) | span << SMMU_PMCG_SID_SPAN_SHIFT;
	smmu_pmu_set_evtypew(smmu_pmu, idx, evtypew);
	smmu_pmu_set_smw(smmu_pmu, idx, sid);
}

static boow smmu_pmu_check_gwobaw_fiwtew(stwuct pewf_event *cuww,
					 stwuct pewf_event *new)
{
	if (get_fiwtew_enabwe(new) != get_fiwtew_enabwe(cuww))
		wetuwn fawse;

	if (!get_fiwtew_enabwe(new))
		wetuwn twue;

	wetuwn get_fiwtew_span(new) == get_fiwtew_span(cuww) &&
	       get_fiwtew_stweam_id(new) == get_fiwtew_stweam_id(cuww);
}

static int smmu_pmu_appwy_event_fiwtew(stwuct smmu_pmu *smmu_pmu,
				       stwuct pewf_event *event, int idx)
{
	u32 span, sid;
	unsigned int cuw_idx, num_ctws = smmu_pmu->num_countews;
	boow fiwtew_en = !!get_fiwtew_enabwe(event);

	span = fiwtew_en ? get_fiwtew_span(event) :
			   SMMU_PMCG_DEFAUWT_FIWTEW_SPAN;
	sid = fiwtew_en ? get_fiwtew_stweam_id(event) :
			   SMMU_PMCG_DEFAUWT_FIWTEW_SID;

	cuw_idx = find_fiwst_bit(smmu_pmu->used_countews, num_ctws);
	/*
	 * Pew-countew fiwtewing, ow scheduwing the fiwst gwobawwy-fiwtewed
	 * event into an empty PMU so idx == 0 and it wowks out equivawent.
	 */
	if (!smmu_pmu->gwobaw_fiwtew || cuw_idx == num_ctws) {
		smmu_pmu_set_event_fiwtew(event, idx, span, sid);
		wetuwn 0;
	}

	/* Othewwise, must match whatevew's cuwwentwy scheduwed */
	if (smmu_pmu_check_gwobaw_fiwtew(smmu_pmu->events[cuw_idx], event)) {
		smmu_pmu_set_evtypew(smmu_pmu, idx, get_event(event));
		wetuwn 0;
	}

	wetuwn -EAGAIN;
}

static int smmu_pmu_get_event_idx(stwuct smmu_pmu *smmu_pmu,
				  stwuct pewf_event *event)
{
	int idx, eww;
	unsigned int num_ctws = smmu_pmu->num_countews;

	idx = find_fiwst_zewo_bit(smmu_pmu->used_countews, num_ctws);
	if (idx == num_ctws)
		/* The countews awe aww in use. */
		wetuwn -EAGAIN;

	eww = smmu_pmu_appwy_event_fiwtew(smmu_pmu, event, idx);
	if (eww)
		wetuwn eww;

	set_bit(idx, smmu_pmu->used_countews);

	wetuwn idx;
}

static boow smmu_pmu_events_compatibwe(stwuct pewf_event *cuww,
				       stwuct pewf_event *new)
{
	if (new->pmu != cuww->pmu)
		wetuwn fawse;

	if (to_smmu_pmu(new->pmu)->gwobaw_fiwtew &&
	    !smmu_pmu_check_gwobaw_fiwtew(cuww, new))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Impwementation of abstwact pmu functionawity wequiwed by
 * the cowe pewf events code.
 */

static int smmu_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	stwuct device *dev = smmu_pmu->dev;
	stwuct pewf_event *sibwing;
	int gwoup_num_events = 1;
	u16 event_id;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (hwc->sampwe_pewiod) {
		dev_dbg(dev, "Sampwing not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->cpu < 0) {
		dev_dbg(dev, "Pew-task mode not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Vewify specified event is suppowted on this PMU */
	event_id = get_event(event);
	if (event_id < SMMU_PMCG_AWCH_MAX_EVENTS &&
	    (!test_bit(event_id, smmu_pmu->suppowted_events))) {
		dev_dbg(dev, "Invawid event %d fow this PMU\n", event_id);
		wetuwn -EINVAW;
	}

	/* Don't awwow gwoups with mixed PMUs, except fow s/w events */
	if (!is_softwawe_event(event->gwoup_weadew)) {
		if (!smmu_pmu_events_compatibwe(event->gwoup_weadew, event))
			wetuwn -EINVAW;

		if (++gwoup_num_events > smmu_pmu->num_countews)
			wetuwn -EINVAW;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (is_softwawe_event(sibwing))
			continue;

		if (!smmu_pmu_events_compatibwe(sibwing, event))
			wetuwn -EINVAW;

		if (++gwoup_num_events > smmu_pmu->num_countews)
			wetuwn -EINVAW;
	}

	hwc->idx = -1;

	/*
	 * Ensuwe aww events awe on the same cpu so aww events awe in the
	 * same cpu context, to avoid waces on pmu_enabwe etc.
	 */
	event->cpu = smmu_pmu->on_cpu;

	wetuwn 0;
}

static void smmu_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	hwc->state = 0;

	smmu_pmu_set_pewiod(smmu_pmu, hwc);

	smmu_pmu_countew_enabwe(smmu_pmu, idx);
}

static void smmu_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	smmu_pmu_countew_disabwe(smmu_pmu, idx);
	/* As the countew gets updated on _stawt, ignowe PEWF_EF_UPDATE */
	smmu_pmu_event_update(event);
	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int smmu_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);

	idx = smmu_pmu_get_event_idx(smmu_pmu, event);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	smmu_pmu->events[idx] = event;
	wocaw64_set(&hwc->pwev_count, 0);

	smmu_pmu_intewwupt_enabwe(smmu_pmu, idx);

	if (fwags & PEWF_EF_STAWT)
		smmu_pmu_event_stawt(event, fwags);

	/* Pwopagate changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void smmu_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	int idx = hwc->idx;

	smmu_pmu_event_stop(event, fwags | PEWF_EF_UPDATE);
	smmu_pmu_intewwupt_disabwe(smmu_pmu, idx);
	smmu_pmu->events[idx] = NUWW;
	cweaw_bit(idx, smmu_pmu->used_countews);

	pewf_event_update_usewpage(event);
}

static void smmu_pmu_event_wead(stwuct pewf_event *event)
{
	smmu_pmu_event_update(event);
}

/* cpumask */

static ssize_t smmu_pmu_cpumask_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(smmu_pmu->on_cpu));
}

static stwuct device_attwibute smmu_pmu_cpumask_attw =
		__ATTW(cpumask, 0444, smmu_pmu_cpumask_show, NUWW);

static stwuct attwibute *smmu_pmu_cpumask_attws[] = {
	&smmu_pmu_cpumask_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup smmu_pmu_cpumask_gwoup = {
	.attws = smmu_pmu_cpumask_attws,
};

/* Events */

static ssize_t smmu_pmu_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

#define SMMU_EVENT_ATTW(name, config)			\
	PMU_EVENT_ATTW_ID(name, smmu_pmu_event_show, config)

static stwuct attwibute *smmu_pmu_events[] = {
	SMMU_EVENT_ATTW(cycwes, 0),
	SMMU_EVENT_ATTW(twansaction, 1),
	SMMU_EVENT_ATTW(twb_miss, 2),
	SMMU_EVENT_ATTW(config_cache_miss, 3),
	SMMU_EVENT_ATTW(twans_tabwe_wawk_access, 4),
	SMMU_EVENT_ATTW(config_stwuct_access, 5),
	SMMU_EVENT_ATTW(pcie_ats_twans_wq, 6),
	SMMU_EVENT_ATTW(pcie_ats_twans_passed, 7),
	NUWW
};

static umode_t smmu_pmu_event_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_dwvdata(dev));
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw.attw);

	if (test_bit(pmu_attw->id, smmu_pmu->suppowted_events))
		wetuwn attw->mode;

	wetuwn 0;
}

static const stwuct attwibute_gwoup smmu_pmu_events_gwoup = {
	.name = "events",
	.attws = smmu_pmu_events,
	.is_visibwe = smmu_pmu_event_is_visibwe,
};

static ssize_t smmu_pmu_identifiew_attw_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(page, "0x%08x\n", smmu_pmu->iidw);
}

static umode_t smmu_pmu_identifiew_attw_visibwe(stwuct kobject *kobj,
						stwuct attwibute *attw,
						int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_dwvdata(dev));

	if (!smmu_pmu->iidw)
		wetuwn 0;
	wetuwn attw->mode;
}

static stwuct device_attwibute smmu_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, smmu_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *smmu_pmu_identifiew_attws[] = {
	&smmu_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup smmu_pmu_identifiew_gwoup = {
	.attws = smmu_pmu_identifiew_attws,
	.is_visibwe = smmu_pmu_identifiew_attw_visibwe,
};

/* Fowmats */
PMU_FOWMAT_ATTW(event,		   "config:0-15");
PMU_FOWMAT_ATTW(fiwtew_stweam_id,  "config1:0-31");
PMU_FOWMAT_ATTW(fiwtew_span,	   "config1:32");
PMU_FOWMAT_ATTW(fiwtew_enabwe,	   "config1:33");

static stwuct attwibute *smmu_pmu_fowmats[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_fiwtew_stweam_id.attw,
	&fowmat_attw_fiwtew_span.attw,
	&fowmat_attw_fiwtew_enabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup smmu_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = smmu_pmu_fowmats,
};

static const stwuct attwibute_gwoup *smmu_pmu_attw_gwps[] = {
	&smmu_pmu_cpumask_gwoup,
	&smmu_pmu_events_gwoup,
	&smmu_pmu_fowmat_gwoup,
	&smmu_pmu_identifiew_gwoup,
	NUWW
};

/*
 * Genewic device handwews
 */

static int smmu_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct smmu_pmu *smmu_pmu;
	unsigned int tawget;

	smmu_pmu = hwist_entwy_safe(node, stwuct smmu_pmu, node);
	if (cpu != smmu_pmu->on_cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&smmu_pmu->pmu, cpu, tawget);
	smmu_pmu->on_cpu = tawget;
	WAWN_ON(iwq_set_affinity(smmu_pmu->iwq, cpumask_of(tawget)));

	wetuwn 0;
}

static iwqwetuwn_t smmu_pmu_handwe_iwq(int iwq_num, void *data)
{
	stwuct smmu_pmu *smmu_pmu = data;
	DECWAWE_BITMAP(ovs, BITS_PEW_TYPE(u64));
	u64 ovsw;
	unsigned int idx;

	ovsw = weadq(smmu_pmu->wewoc_base + SMMU_PMCG_OVSSET0);
	if (!ovsw)
		wetuwn IWQ_NONE;

	wwiteq(ovsw, smmu_pmu->wewoc_base + SMMU_PMCG_OVSCWW0);

	bitmap_fwom_u64(ovs, ovsw);
	fow_each_set_bit(idx, ovs, smmu_pmu->num_countews) {
		stwuct pewf_event *event = smmu_pmu->events[idx];
		stwuct hw_pewf_event *hwc;

		if (WAWN_ON_ONCE(!event))
			continue;

		smmu_pmu_event_update(event);
		hwc = &event->hw;

		smmu_pmu_set_pewiod(smmu_pmu, hwc);
	}

	wetuwn IWQ_HANDWED;
}

static void smmu_pmu_fwee_msis(void *data)
{
	stwuct device *dev = data;

	pwatfowm_msi_domain_fwee_iwqs(dev);
}

static void smmu_pmu_wwite_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	phys_addw_t doowbeww;
	stwuct device *dev = msi_desc_to_dev(desc);
	stwuct smmu_pmu *pmu = dev_get_dwvdata(dev);

	doowbeww = (((u64)msg->addwess_hi) << 32) | msg->addwess_wo;
	doowbeww &= MSI_CFG0_ADDW_MASK;

	wwiteq_wewaxed(doowbeww, pmu->weg_base + SMMU_PMCG_IWQ_CFG0);
	wwitew_wewaxed(msg->data, pmu->weg_base + SMMU_PMCG_IWQ_CFG1);
	wwitew_wewaxed(MSI_CFG2_MEMATTW_DEVICE_nGnWE,
		       pmu->weg_base + SMMU_PMCG_IWQ_CFG2);
}

static void smmu_pmu_setup_msi(stwuct smmu_pmu *pmu)
{
	stwuct device *dev = pmu->dev;
	int wet;

	/* Cweaw MSI addwess weg */
	wwiteq_wewaxed(0, pmu->weg_base + SMMU_PMCG_IWQ_CFG0);

	/* MSI suppowted ow not */
	if (!(weadw(pmu->weg_base + SMMU_PMCG_CFGW) & SMMU_PMCG_CFGW_MSI))
		wetuwn;

	wet = pwatfowm_msi_domain_awwoc_iwqs(dev, 1, smmu_pmu_wwite_msi_msg);
	if (wet) {
		dev_wawn(dev, "faiwed to awwocate MSIs\n");
		wetuwn;
	}

	pmu->iwq = msi_get_viwq(dev, 0);

	/* Add cawwback to fwee MSIs on teawdown */
	devm_add_action(dev, smmu_pmu_fwee_msis, dev);
}

static int smmu_pmu_setup_iwq(stwuct smmu_pmu *pmu)
{
	unsigned wong fwags = IWQF_NOBAWANCING | IWQF_SHAWED | IWQF_NO_THWEAD;
	int iwq, wet = -ENXIO;

	smmu_pmu_setup_msi(pmu);

	iwq = pmu->iwq;
	if (iwq)
		wet = devm_wequest_iwq(pmu->dev, iwq, smmu_pmu_handwe_iwq,
				       fwags, "smmuv3-pmu", pmu);
	wetuwn wet;
}

static void smmu_pmu_weset(stwuct smmu_pmu *smmu_pmu)
{
	u64 countew_pwesent_mask = GENMASK_UWW(smmu_pmu->num_countews - 1, 0);

	smmu_pmu_disabwe(&smmu_pmu->pmu);

	/* Disabwe countew and intewwupt */
	wwiteq_wewaxed(countew_pwesent_mask,
		       smmu_pmu->weg_base + SMMU_PMCG_CNTENCWW0);
	wwiteq_wewaxed(countew_pwesent_mask,
		       smmu_pmu->weg_base + SMMU_PMCG_INTENCWW0);
	wwiteq_wewaxed(countew_pwesent_mask,
		       smmu_pmu->wewoc_base + SMMU_PMCG_OVSCWW0);
}

static void smmu_pmu_get_acpi_options(stwuct smmu_pmu *smmu_pmu)
{
	u32 modew;

	modew = *(u32 *)dev_get_pwatdata(smmu_pmu->dev);

	switch (modew) {
	case IOWT_SMMU_V3_PMCG_HISI_HIP08:
		/* HiSiwicon Ewwatum 162001800 */
		smmu_pmu->options |= SMMU_PMCG_EVCNTW_WDONWY | SMMU_PMCG_HAWDEN_DISABWE;
		bweak;
	case IOWT_SMMU_V3_PMCG_HISI_HIP09:
		smmu_pmu->options |= SMMU_PMCG_HAWDEN_DISABWE;
		bweak;
	}

	dev_notice(smmu_pmu->dev, "option mask 0x%x\n", smmu_pmu->options);
}

static boow smmu_pmu_cowesight_id_wegs(stwuct smmu_pmu *smmu_pmu)
{
	wetuwn of_device_is_compatibwe(smmu_pmu->dev->of_node,
				       "awm,mmu-600-pmcg");
}

static void smmu_pmu_get_iidw(stwuct smmu_pmu *smmu_pmu)
{
	u32 iidw = weadw_wewaxed(smmu_pmu->weg_base + SMMU_PMCG_IIDW);

	if (!iidw && smmu_pmu_cowesight_id_wegs(smmu_pmu)) {
		u32 pidw0 = weadw(smmu_pmu->weg_base + SMMU_PMCG_PIDW0);
		u32 pidw1 = weadw(smmu_pmu->weg_base + SMMU_PMCG_PIDW1);
		u32 pidw2 = weadw(smmu_pmu->weg_base + SMMU_PMCG_PIDW2);
		u32 pidw3 = weadw(smmu_pmu->weg_base + SMMU_PMCG_PIDW3);
		u32 pidw4 = weadw(smmu_pmu->weg_base + SMMU_PMCG_PIDW4);

		u32 pwoductid = FIEWD_GET(SMMU_PMCG_PIDW0_PAWT_0, pidw0) |
				(FIEWD_GET(SMMU_PMCG_PIDW1_PAWT_1, pidw1) << 8);
		u32 vawiant = FIEWD_GET(SMMU_PMCG_PIDW2_WEVISION, pidw2);
		u32 wevision = FIEWD_GET(SMMU_PMCG_PIDW3_WEVAND, pidw3);
		u32 impwementew =
			FIEWD_GET(SMMU_PMCG_PIDW1_DES_0, pidw1) |
			(FIEWD_GET(SMMU_PMCG_PIDW2_DES_1, pidw2) << 4) |
			(FIEWD_GET(SMMU_PMCG_PIDW4_DES_2, pidw4) << 8);

		iidw = FIEWD_PWEP(SMMU_PMCG_IIDW_PWODUCTID, pwoductid) |
		       FIEWD_PWEP(SMMU_PMCG_IIDW_VAWIANT, vawiant) |
		       FIEWD_PWEP(SMMU_PMCG_IIDW_WEVISION, wevision) |
		       FIEWD_PWEP(SMMU_PMCG_IIDW_IMPWEMENTEW, impwementew);
	}

	smmu_pmu->iidw = iidw;
}

static int smmu_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smmu_pmu *smmu_pmu;
	stwuct wesouwce *wes_0;
	u32 cfgw, weg_size;
	u64 ceid_64[2];
	int iwq, eww;
	chaw *name;
	stwuct device *dev = &pdev->dev;

	smmu_pmu = devm_kzawwoc(dev, sizeof(*smmu_pmu), GFP_KEWNEW);
	if (!smmu_pmu)
		wetuwn -ENOMEM;

	smmu_pmu->dev = dev;
	pwatfowm_set_dwvdata(pdev, smmu_pmu);

	smmu_pmu->pmu = (stwuct pmu) {
		.moduwe		= THIS_MODUWE,
		.task_ctx_nw    = pewf_invawid_context,
		.pmu_enabwe	= smmu_pmu_enabwe,
		.pmu_disabwe	= smmu_pmu_disabwe,
		.event_init	= smmu_pmu_event_init,
		.add		= smmu_pmu_event_add,
		.dew		= smmu_pmu_event_dew,
		.stawt		= smmu_pmu_event_stawt,
		.stop		= smmu_pmu_event_stop,
		.wead		= smmu_pmu_event_wead,
		.attw_gwoups	= smmu_pmu_attw_gwps,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	smmu_pmu->weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes_0);
	if (IS_EWW(smmu_pmu->weg_base))
		wetuwn PTW_EWW(smmu_pmu->weg_base);

	cfgw = weadw_wewaxed(smmu_pmu->weg_base + SMMU_PMCG_CFGW);

	/* Detewmine if page 1 is pwesent */
	if (cfgw & SMMU_PMCG_CFGW_WEWOC_CTWS) {
		smmu_pmu->wewoc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(smmu_pmu->wewoc_base))
			wetuwn PTW_EWW(smmu_pmu->wewoc_base);
	} ewse {
		smmu_pmu->wewoc_base = smmu_pmu->weg_base;
	}

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0)
		smmu_pmu->iwq = iwq;

	ceid_64[0] = weadq_wewaxed(smmu_pmu->weg_base + SMMU_PMCG_CEID0);
	ceid_64[1] = weadq_wewaxed(smmu_pmu->weg_base + SMMU_PMCG_CEID1);
	bitmap_fwom_aww32(smmu_pmu->suppowted_events, (u32 *)ceid_64,
			  SMMU_PMCG_AWCH_MAX_EVENTS);

	smmu_pmu->num_countews = FIEWD_GET(SMMU_PMCG_CFGW_NCTW, cfgw) + 1;

	smmu_pmu->gwobaw_fiwtew = !!(cfgw & SMMU_PMCG_CFGW_SID_FIWTEW_TYPE);

	weg_size = FIEWD_GET(SMMU_PMCG_CFGW_SIZE, cfgw);
	smmu_pmu->countew_mask = GENMASK_UWW(weg_size, 0);

	smmu_pmu_weset(smmu_pmu);

	eww = smmu_pmu_setup_iwq(smmu_pmu);
	if (eww) {
		dev_eww(dev, "Setup iwq faiwed, PMU @%pa\n", &wes_0->stawt);
		wetuwn eww;
	}

	smmu_pmu_get_iidw(smmu_pmu);

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "smmuv3_pmcg_%wwx",
			      (wes_0->stawt) >> SMMU_PMCG_PA_SHIFT);
	if (!name) {
		dev_eww(dev, "Cweate name faiwed, PMU @%pa\n", &wes_0->stawt);
		wetuwn -EINVAW;
	}

	if (!dev->of_node)
		smmu_pmu_get_acpi_options(smmu_pmu);

	/*
	 * Fow pwatfowms suffew this quiwk, the PMU disabwe sometimes faiws to
	 * stop the countews. This wiww weads to inaccuwate ow ewwow counting.
	 * Fowcibwy disabwe the countews with these quiwk handwew.
	 */
	if (smmu_pmu->options & SMMU_PMCG_HAWDEN_DISABWE) {
		smmu_pmu->pmu.pmu_enabwe = smmu_pmu_enabwe_quiwk_hip08_09;
		smmu_pmu->pmu.pmu_disabwe = smmu_pmu_disabwe_quiwk_hip08_09;
	}

	/* Pick one CPU to be the pwefewwed one to use */
	smmu_pmu->on_cpu = waw_smp_pwocessow_id();
	WAWN_ON(iwq_set_affinity(smmu_pmu->iwq, cpumask_of(smmu_pmu->on_cpu)));

	eww = cpuhp_state_add_instance_nocawws(cpuhp_state_num,
					       &smmu_pmu->node);
	if (eww) {
		dev_eww(dev, "Ewwow %d wegistewing hotpwug, PMU @%pa\n",
			eww, &wes_0->stawt);
		wetuwn eww;
	}

	eww = pewf_pmu_wegistew(&smmu_pmu->pmu, name, -1);
	if (eww) {
		dev_eww(dev, "Ewwow %d wegistewing PMU @%pa\n",
			eww, &wes_0->stawt);
		goto out_unwegistew;
	}

	dev_info(dev, "Wegistewed PMU @ %pa using %d countews with %s fiwtew settings\n",
		 &wes_0->stawt, smmu_pmu->num_countews,
		 smmu_pmu->gwobaw_fiwtew ? "Gwobaw(Countew0)" :
		 "Individuaw");

	wetuwn 0;

out_unwegistew:
	cpuhp_state_wemove_instance_nocawws(cpuhp_state_num, &smmu_pmu->node);
	wetuwn eww;
}

static int smmu_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct smmu_pmu *smmu_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&smmu_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(cpuhp_state_num, &smmu_pmu->node);

	wetuwn 0;
}

static void smmu_pmu_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct smmu_pmu *smmu_pmu = pwatfowm_get_dwvdata(pdev);

	smmu_pmu_disabwe(&smmu_pmu->pmu);
}

#ifdef CONFIG_OF
static const stwuct of_device_id smmu_pmu_of_match[] = {
	{ .compatibwe = "awm,smmu-v3-pmcg" },
	{}
};
MODUWE_DEVICE_TABWE(of, smmu_pmu_of_match);
#endif

static stwuct pwatfowm_dwivew smmu_pmu_dwivew = {
	.dwivew = {
		.name = "awm-smmu-v3-pmcg",
		.of_match_tabwe = of_match_ptw(smmu_pmu_of_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = smmu_pmu_pwobe,
	.wemove = smmu_pmu_wemove,
	.shutdown = smmu_pmu_shutdown,
};

static int __init awm_smmu_pmu_init(void)
{
	int wet;

	cpuhp_state_num = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
						  "pewf/awm/pmcg:onwine",
						  NUWW,
						  smmu_pmu_offwine_cpu);
	if (cpuhp_state_num < 0)
		wetuwn cpuhp_state_num;

	wet = pwatfowm_dwivew_wegistew(&smmu_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(cpuhp_state_num);

	wetuwn wet;
}
moduwe_init(awm_smmu_pmu_init);

static void __exit awm_smmu_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&smmu_pmu_dwivew);
	cpuhp_wemove_muwti_state(cpuhp_state_num);
}

moduwe_exit(awm_smmu_pmu_exit);

MODUWE_AWIAS("pwatfowm:awm-smmu-v3-pmcg");
MODUWE_DESCWIPTION("PMU dwivew fow AWM SMMUv3 Pewfowmance Monitows Extension");
MODUWE_AUTHOW("Neiw Weedew <nweedew@codeauwowa.owg>");
MODUWE_AUTHOW("Shameew Kowothum <shameewawi.kowothum.thodi@huawei.com>");
MODUWE_WICENSE("GPW v2");
