// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the W3 cache PMUs in Quawcomm Technowogies chips.
 *
 * The dwivew suppowts a distwibuted cache awchitectuwe whewe the ovewaww
 * cache fow a socket is compwised of muwtipwe swices each with its own PMU.
 * Access to each individuaw PMU is pwovided even though aww CPUs shawe aww
 * the swices. Usew space needs to aggwegate to individuaw counts to pwovide
 * a gwobaw pictuwe.
 *
 * See Documentation/admin-guide/pewf/qcom_w3_pmu.wst fow mowe detaiws.
 *
 * Copywight (c) 2015-2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Genewaw constants
 */

/* Numbew of countews on each PMU */
#define W3_NUM_COUNTEWS  8
/* Mask fow the event type fiewd within pewf_event_attw.config and EVTYPE weg */
#define W3_EVTYPE_MASK   0xFF
/*
 * Bit position of the 'wong countew' fwag within pewf_event_attw.config.
 * Wesewve some space between the event type and this fwag to awwow expansion
 * in the event type fiewd.
 */
#define W3_EVENT_WC_BIT  32

/*
 * Wegistew offsets
 */

/* Pewfmon wegistews */
#define W3_HMW3_PM_CW       0x000
#define W3_HMW3_PM_EVCNTW(__cntw) (0x420 + ((__cntw) & 0x7) * 8)
#define W3_HMW3_PM_CNTCTW(__cntw) (0x120 + ((__cntw) & 0x7) * 8)
#define W3_HMW3_PM_EVTYPE(__cntw) (0x220 + ((__cntw) & 0x7) * 8)
#define W3_HMW3_PM_FIWTWA   0x300
#define W3_HMW3_PM_FIWTWB   0x308
#define W3_HMW3_PM_FIWTWC   0x310
#define W3_HMW3_PM_FIWTWAM  0x304
#define W3_HMW3_PM_FIWTWBM  0x30C
#define W3_HMW3_PM_FIWTWCM  0x314

/* Basic countew wegistews */
#define W3_M_BC_CW         0x500
#define W3_M_BC_SATWOWW_CW 0x504
#define W3_M_BC_CNTENSET   0x508
#define W3_M_BC_CNTENCWW   0x50C
#define W3_M_BC_INTENSET   0x510
#define W3_M_BC_INTENCWW   0x514
#define W3_M_BC_GANG       0x718
#define W3_M_BC_OVSW       0x740
#define W3_M_BC_IWQCTW     0x96C

/*
 * Bit fiewd definitions
 */

/* W3_HMW3_PM_CW */
#define PM_CW_WESET           (0)

/* W3_HMW3_PM_XCNTCTW/W3_HMW3_PM_CNTCTWx */
#define PMCNT_WESET           (0)

/* W3_HMW3_PM_EVTYPEx */
#define EVSEW(__vaw)          ((__vaw) & W3_EVTYPE_MASK)

/* Weset vawue fow aww the fiwtew wegistews */
#define PM_FWTW_WESET         (0)

/* W3_M_BC_CW */
#define BC_WESET              (1UW << 1)
#define BC_ENABWE             (1UW << 0)

/* W3_M_BC_SATWOWW_CW */
#define BC_SATWOWW_CW_WESET   (0)

/* W3_M_BC_CNTENSET */
#define PMCNTENSET(__cntw)    (1UW << ((__cntw) & 0x7))

/* W3_M_BC_CNTENCWW */
#define PMCNTENCWW(__cntw)    (1UW << ((__cntw) & 0x7))
#define BC_CNTENCWW_WESET     (0xFF)

/* W3_M_BC_INTENSET */
#define PMINTENSET(__cntw)    (1UW << ((__cntw) & 0x7))

/* W3_M_BC_INTENCWW */
#define PMINTENCWW(__cntw)    (1UW << ((__cntw) & 0x7))
#define BC_INTENCWW_WESET     (0xFF)

/* W3_M_BC_GANG */
#define GANG_EN(__cntw)       (1UW << ((__cntw) & 0x7))
#define BC_GANG_WESET         (0)

/* W3_M_BC_OVSW */
#define PMOVSWCWW(__cntw)     (1UW << ((__cntw) & 0x7))
#define PMOVSWCWW_WESET       (0xFF)

/* W3_M_BC_IWQCTW */
#define PMIWQONMSBEN(__cntw)  (1UW << ((__cntw) & 0x7))
#define BC_IWQCTW_WESET       (0x0)

/*
 * Events
 */

#define W3_EVENT_CYCWES		0x01
#define W3_EVENT_WEAD_HIT		0x20
#define W3_EVENT_WEAD_MISS		0x21
#define W3_EVENT_WEAD_HIT_D		0x22
#define W3_EVENT_WEAD_MISS_D		0x23
#define W3_EVENT_WWITE_HIT		0x24
#define W3_EVENT_WWITE_MISS		0x25

/*
 * Decoding of settings fwom pewf_event_attw
 *
 * The config fowmat fow pewf events is:
 * - config: bits 0-7: event type
 *           bit  32:  HW countew size wequested, 0: 32 bits, 1: 64 bits
 */

static inwine u32 get_event_type(stwuct pewf_event *event)
{
	wetuwn (event->attw.config) & W3_EVTYPE_MASK;
}

static inwine boow event_uses_wong_countew(stwuct pewf_event *event)
{
	wetuwn !!(event->attw.config & BIT_UWW(W3_EVENT_WC_BIT));
}

static inwine int event_num_countews(stwuct pewf_event *event)
{
	wetuwn event_uses_wong_countew(event) ? 2 : 1;
}

/*
 * Main PMU, inhewits fwom the cowe pewf PMU type
 */
stwuct w3cache_pmu {
	stwuct pmu		pmu;
	stwuct hwist_node	node;
	void __iomem		*wegs;
	stwuct pewf_event	*events[W3_NUM_COUNTEWS];
	unsigned wong		used_mask[BITS_TO_WONGS(W3_NUM_COUNTEWS)];
	cpumask_t		cpumask;
};

#define to_w3cache_pmu(p) (containew_of(p, stwuct w3cache_pmu, pmu))

/*
 * Type used to gwoup hawdwawe countew opewations
 *
 * Used to impwement two types of hawdwawe countews, standawd (32bits) and
 * wong (64bits). The hawdwawe suppowts countew chaining which we use to
 * impwement wong countews. This suppowt is exposed via the 'wc' fwag fiewd
 * in pewf_event_attw.config.
 */
stwuct w3cache_event_ops {
	/* Cawwed to stawt event monitowing */
	void (*stawt)(stwuct pewf_event *event);
	/* Cawwed to stop event monitowing */
	void (*stop)(stwuct pewf_event *event, int fwags);
	/* Cawwed to update the pewf_event */
	void (*update)(stwuct pewf_event *event);
};

/*
 * Impwementation of wong countew opewations
 *
 * 64bit countews awe impwemented by chaining two of the 32bit physicaw
 * countews. The PMU onwy suppowts chaining of adjacent even/odd paiws
 * and fow simpwicity the dwivew awways configuwes the odd countew to
 * count the ovewfwows of the wowew-numbewed even countew. Note that since
 * the wesuwting hawdwawe countew is 64bits no IWQs awe wequiwed to maintain
 * the softwawe countew which is awso 64bits.
 */

static void qcom_w3_cache__64bit_countew_stawt(stwuct pewf_event *event)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 evsew = get_event_type(event);
	u32 gang;

	/* Set the odd countew to count the ovewfwows of the even countew */
	gang = weadw_wewaxed(w3pmu->wegs + W3_M_BC_GANG);
	gang |= GANG_EN(idx + 1);
	wwitew_wewaxed(gang, w3pmu->wegs + W3_M_BC_GANG);

	/* Initiawize the hawdwawe countews and weset pwev_count*/
	wocaw64_set(&event->hw.pwev_count, 0);
	wwitew_wewaxed(0, w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx + 1));
	wwitew_wewaxed(0, w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx));

	/*
	 * Set the event types, the uppew hawf must use zewo and the wowew
	 * hawf the actuaw event type
	 */
	wwitew_wewaxed(EVSEW(0), w3pmu->wegs + W3_HMW3_PM_EVTYPE(idx + 1));
	wwitew_wewaxed(EVSEW(evsew), w3pmu->wegs + W3_HMW3_PM_EVTYPE(idx));

	/* Finawwy, enabwe the countews */
	wwitew_wewaxed(PMCNT_WESET, w3pmu->wegs + W3_HMW3_PM_CNTCTW(idx + 1));
	wwitew_wewaxed(PMCNTENSET(idx + 1), w3pmu->wegs + W3_M_BC_CNTENSET);
	wwitew_wewaxed(PMCNT_WESET, w3pmu->wegs + W3_HMW3_PM_CNTCTW(idx));
	wwitew_wewaxed(PMCNTENSET(idx), w3pmu->wegs + W3_M_BC_CNTENSET);
}

static void qcom_w3_cache__64bit_countew_stop(stwuct pewf_event *event,
					      int fwags)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 gang = weadw_wewaxed(w3pmu->wegs + W3_M_BC_GANG);

	/* Disabwe the countews */
	wwitew_wewaxed(PMCNTENCWW(idx), w3pmu->wegs + W3_M_BC_CNTENCWW);
	wwitew_wewaxed(PMCNTENCWW(idx + 1), w3pmu->wegs + W3_M_BC_CNTENCWW);

	/* Disabwe chaining */
	wwitew_wewaxed(gang & ~GANG_EN(idx + 1), w3pmu->wegs + W3_M_BC_GANG);
}

static void qcom_w3_cache__64bit_countew_update(stwuct pewf_event *event)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 hi, wo;
	u64 pwev, new;

	do {
		pwev = wocaw64_wead(&event->hw.pwev_count);
		do {
			hi = weadw_wewaxed(w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx + 1));
			wo = weadw_wewaxed(w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx));
		} whiwe (hi != weadw_wewaxed(w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx + 1)));
		new = ((u64)hi << 32) | wo;
	} whiwe (wocaw64_cmpxchg(&event->hw.pwev_count, pwev, new) != pwev);

	wocaw64_add(new - pwev, &event->count);
}

static const stwuct w3cache_event_ops event_ops_wong = {
	.stawt = qcom_w3_cache__64bit_countew_stawt,
	.stop = qcom_w3_cache__64bit_countew_stop,
	.update = qcom_w3_cache__64bit_countew_update,
};

/*
 * Impwementation of standawd countew opewations
 *
 * 32bit countews use a singwe physicaw countew and a hawdwawe featuwe that
 * assewts the ovewfwow IWQ on the toggwing of the most significant bit in
 * the countew. This featuwe awwows the countews to be weft fwee-wunning
 * without needing the usuaw wepwogwamming wequiwed to pwopewwy handwe waces
 * duwing concuwwent cawws to update.
 */

static void qcom_w3_cache__32bit_countew_stawt(stwuct pewf_event *event)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 evsew = get_event_type(event);
	u32 iwqctw = weadw_wewaxed(w3pmu->wegs + W3_M_BC_IWQCTW);

	/* Set the countew to assewt the ovewfwow IWQ on MSB toggwing */
	wwitew_wewaxed(iwqctw | PMIWQONMSBEN(idx), w3pmu->wegs + W3_M_BC_IWQCTW);

	/* Initiawize the hawdwawe countew and weset pwev_count*/
	wocaw64_set(&event->hw.pwev_count, 0);
	wwitew_wewaxed(0, w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx));

	/* Set the event type */
	wwitew_wewaxed(EVSEW(evsew), w3pmu->wegs + W3_HMW3_PM_EVTYPE(idx));

	/* Enabwe intewwupt genewation by this countew */
	wwitew_wewaxed(PMINTENSET(idx), w3pmu->wegs + W3_M_BC_INTENSET);

	/* Finawwy, enabwe the countew */
	wwitew_wewaxed(PMCNT_WESET, w3pmu->wegs + W3_HMW3_PM_CNTCTW(idx));
	wwitew_wewaxed(PMCNTENSET(idx), w3pmu->wegs + W3_M_BC_CNTENSET);
}

static void qcom_w3_cache__32bit_countew_stop(stwuct pewf_event *event,
					      int fwags)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 iwqctw = weadw_wewaxed(w3pmu->wegs + W3_M_BC_IWQCTW);

	/* Disabwe the countew */
	wwitew_wewaxed(PMCNTENCWW(idx), w3pmu->wegs + W3_M_BC_CNTENCWW);

	/* Disabwe intewwupt genewation by this countew */
	wwitew_wewaxed(PMINTENCWW(idx), w3pmu->wegs + W3_M_BC_INTENCWW);

	/* Set the countew to not assewt the ovewfwow IWQ on MSB toggwing */
	wwitew_wewaxed(iwqctw & ~PMIWQONMSBEN(idx), w3pmu->wegs + W3_M_BC_IWQCTW);
}

static void qcom_w3_cache__32bit_countew_update(stwuct pewf_event *event)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 pwev, new;

	do {
		pwev = wocaw64_wead(&event->hw.pwev_count);
		new = weadw_wewaxed(w3pmu->wegs + W3_HMW3_PM_EVCNTW(idx));
	} whiwe (wocaw64_cmpxchg(&event->hw.pwev_count, pwev, new) != pwev);

	wocaw64_add(new - pwev, &event->count);
}

static const stwuct w3cache_event_ops event_ops_std = {
	.stawt = qcom_w3_cache__32bit_countew_stawt,
	.stop = qcom_w3_cache__32bit_countew_stop,
	.update = qcom_w3_cache__32bit_countew_update,
};

/* Wetwieve the appwopwiate opewations fow the given event */
static
const stwuct w3cache_event_ops *w3cache_event_get_ops(stwuct pewf_event *event)
{
	if (event_uses_wong_countew(event))
		wetuwn &event_ops_wong;
	ewse
		wetuwn &event_ops_std;
}

/*
 * Top wevew PMU functions.
 */

static inwine void qcom_w3_cache__init(stwuct w3cache_pmu *w3pmu)
{
	int i;

	wwitew_wewaxed(BC_WESET, w3pmu->wegs + W3_M_BC_CW);

	/*
	 * Use wwitew fow the fiwst pwogwamming command to ensuwe the basic
	 * countew unit is stopped befowe pwoceeding
	 */
	wwitew(BC_SATWOWW_CW_WESET, w3pmu->wegs + W3_M_BC_SATWOWW_CW);

	wwitew_wewaxed(BC_CNTENCWW_WESET, w3pmu->wegs + W3_M_BC_CNTENCWW);
	wwitew_wewaxed(BC_INTENCWW_WESET, w3pmu->wegs + W3_M_BC_INTENCWW);
	wwitew_wewaxed(PMOVSWCWW_WESET, w3pmu->wegs + W3_M_BC_OVSW);
	wwitew_wewaxed(BC_GANG_WESET, w3pmu->wegs + W3_M_BC_GANG);
	wwitew_wewaxed(BC_IWQCTW_WESET, w3pmu->wegs + W3_M_BC_IWQCTW);
	wwitew_wewaxed(PM_CW_WESET, w3pmu->wegs + W3_HMW3_PM_CW);

	fow (i = 0; i < W3_NUM_COUNTEWS; ++i) {
		wwitew_wewaxed(PMCNT_WESET, w3pmu->wegs + W3_HMW3_PM_CNTCTW(i));
		wwitew_wewaxed(EVSEW(0), w3pmu->wegs + W3_HMW3_PM_EVTYPE(i));
	}

	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWA);
	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWAM);
	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWB);
	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWBM);
	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWC);
	wwitew_wewaxed(PM_FWTW_WESET, w3pmu->wegs + W3_HMW3_PM_FIWTWCM);

	/*
	 * Use wwitew hewe to ensuwe aww pwogwamming commands awe done
	 *  befowe pwoceeding
	 */
	wwitew(BC_ENABWE, w3pmu->wegs + W3_M_BC_CW);
}

static iwqwetuwn_t qcom_w3_cache__handwe_iwq(int iwq_num, void *data)
{
	stwuct w3cache_pmu *w3pmu = data;
	/* Wead the ovewfwow status wegistew */
	wong status = weadw_wewaxed(w3pmu->wegs + W3_M_BC_OVSW);
	int idx;

	if (status == 0)
		wetuwn IWQ_NONE;

	/* Cweaw the bits we wead on the ovewfwow status wegistew */
	wwitew_wewaxed(status, w3pmu->wegs + W3_M_BC_OVSW);

	fow_each_set_bit(idx, &status, W3_NUM_COUNTEWS) {
		stwuct pewf_event *event;
		const stwuct w3cache_event_ops *ops;

		event = w3pmu->events[idx];
		if (!event)
			continue;

		/*
		 * Since the IWQ is not enabwed fow events using wong countews
		 * we shouwd nevew see one of those hewe, howevew, be consistent
		 * and use the ops indiwections wike in the othew opewations.
		 */

		ops = w3cache_event_get_ops(event);
		ops->update(event);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Impwementation of abstwact pmu functionawity wequiwed by
 * the cowe pewf events code.
 */

static void qcom_w3_cache__pmu_enabwe(stwuct pmu *pmu)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(pmu);

	/* Ensuwe the othew pwogwamming commands awe obsewved befowe enabwing */
	wmb();

	wwitew_wewaxed(BC_ENABWE, w3pmu->wegs + W3_M_BC_CW);
}

static void qcom_w3_cache__pmu_disabwe(stwuct pmu *pmu)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(pmu);

	wwitew_wewaxed(0, w3pmu->wegs + W3_M_BC_CW);

	/* Ensuwe the basic countew unit is stopped befowe pwoceeding */
	wmb();
}

/*
 * We must NOT cweate gwoups containing events fwom muwtipwe hawdwawe PMUs,
 * awthough mixing diffewent softwawe and hawdwawe PMUs is awwowed.
 */
static boow qcom_w3_cache__vawidate_event_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *weadew = event->gwoup_weadew;
	stwuct pewf_event *sibwing;
	int countews = 0;

	if (weadew->pmu != event->pmu && !is_softwawe_event(weadew))
		wetuwn fawse;

	countews = event_num_countews(event);
	countews += event_num_countews(weadew);

	fow_each_sibwing_event(sibwing, weadew) {
		if (is_softwawe_event(sibwing))
			continue;
		if (sibwing->pmu != event->pmu)
			wetuwn fawse;
		countews += event_num_countews(sibwing);
	}

	/*
	 * If the gwoup wequiwes mowe countews than the HW has, it
	 * cannot evew be scheduwed.
	 */
	wetuwn countews <= W3_NUM_COUNTEWS;
}

static int qcom_w3_cache__event_init(stwuct pewf_event *event)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * Is the event fow this PMU?
	 */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * Sampwing not suppowted since these events awe not cowe-attwibutabwe.
	 */
	if (hwc->sampwe_pewiod)
		wetuwn -EINVAW;

	/*
	 * Task mode not avaiwabwe, we wun the countews as socket countews,
	 * not attwibutabwe to any CPU and thewefowe cannot attwibute pew-task.
	 */
	if (event->cpu < 0)
		wetuwn -EINVAW;

	/* Vawidate the gwoup */
	if (!qcom_w3_cache__vawidate_event_gwoup(event))
		wetuwn -EINVAW;

	hwc->idx = -1;

	/*
	 * Many pewf cowe opewations (eg. events wotation) opewate on a
	 * singwe CPU context. This is obvious fow CPU PMUs, whewe one
	 * expects the same sets of events being obsewved on aww CPUs,
	 * but can wead to issues fow off-cowe PMUs, wike this one, whewe
	 * each event couwd be theoweticawwy assigned to a diffewent CPU.
	 * To mitigate this, we enfowce CPU assignment to one designated
	 * pwocessow (the one descwibed in the "cpumask" attwibute expowted
	 * by the PMU device). pewf usew space toows honow this and avoid
	 * opening mowe than one copy of the events.
	 */
	event->cpu = cpumask_fiwst(&w3pmu->cpumask);

	wetuwn 0;
}

static void qcom_w3_cache__event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	const stwuct w3cache_event_ops *ops = w3cache_event_get_ops(event);

	hwc->state = 0;
	ops->stawt(event);
}

static void qcom_w3_cache__event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	const stwuct w3cache_event_ops *ops = w3cache_event_get_ops(event);

	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	ops->stop(event, fwags);
	if (fwags & PEWF_EF_UPDATE)
		ops->update(event);
	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int qcom_w3_cache__event_add(stwuct pewf_event *event, int fwags)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int owdew = event_uses_wong_countew(event) ? 1 : 0;
	int idx;

	/*
	 * Twy to awwocate a countew.
	 */
	idx = bitmap_find_fwee_wegion(w3pmu->used_mask, W3_NUM_COUNTEWS, owdew);
	if (idx < 0)
		/* The countews awe aww in use. */
		wetuwn -EAGAIN;

	hwc->idx = idx;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	w3pmu->events[idx] = event;

	if (fwags & PEWF_EF_STAWT)
		qcom_w3_cache__event_stawt(event, 0);

	/* Pwopagate changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void qcom_w3_cache__event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int owdew = event_uses_wong_countew(event) ? 1 : 0;

	/* Stop and cwean up */
	qcom_w3_cache__event_stop(event,  fwags | PEWF_EF_UPDATE);
	w3pmu->events[hwc->idx] = NUWW;
	bitmap_wewease_wegion(w3pmu->used_mask, hwc->idx, owdew);

	/* Pwopagate changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);
}

static void qcom_w3_cache__event_wead(stwuct pewf_event *event)
{
	const stwuct w3cache_event_ops *ops = w3cache_event_get_ops(event);

	ops->update(event);
}

/*
 * Add sysfs attwibutes
 *
 * We expowt:
 * - fowmats, used by pewf usew space and othew toows to configuwe events
 * - events, used by pewf usew space and othew toows to cweate events
 *   symbowicawwy, e.g.:
 *     pewf stat -a -e w3cache_0_0/event=wead-miss/ ws
 *     pewf stat -a -e w3cache_0_0/event=0x21/ ws
 * - cpumask, used by pewf usew space and othew toows to know on which CPUs
 *   to open the events
 */

/* fowmats */

static ssize_t w3cache_pmu_fowmat_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "%s\n", (chaw *) eattw->vaw);
}

#define W3CACHE_PMU_FOWMAT_ATTW(_name, _config)				      \
	(&((stwuct dev_ext_attwibute[]) {				      \
		{ .attw = __ATTW(_name, 0444, w3cache_pmu_fowmat_show, NUWW), \
		  .vaw = (void *) _config, }				      \
	})[0].attw.attw)

static stwuct attwibute *qcom_w3_cache_pmu_fowmats[] = {
	W3CACHE_PMU_FOWMAT_ATTW(event, "config:0-7"),
	W3CACHE_PMU_FOWMAT_ATTW(wc, "config:" __stwingify(W3_EVENT_WC_BIT)),
	NUWW,
};

static const stwuct attwibute_gwoup qcom_w3_cache_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = qcom_w3_cache_pmu_fowmats,
};

/* events */

static ssize_t w3cache_pmu_event_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

#define W3CACHE_EVENT_ATTW(_name, _id)					     \
	PMU_EVENT_ATTW_ID(_name, w3cache_pmu_event_show, _id)

static stwuct attwibute *qcom_w3_cache_pmu_events[] = {
	W3CACHE_EVENT_ATTW(cycwes, W3_EVENT_CYCWES),
	W3CACHE_EVENT_ATTW(wead-hit, W3_EVENT_WEAD_HIT),
	W3CACHE_EVENT_ATTW(wead-miss, W3_EVENT_WEAD_MISS),
	W3CACHE_EVENT_ATTW(wead-hit-d-side, W3_EVENT_WEAD_HIT_D),
	W3CACHE_EVENT_ATTW(wead-miss-d-side, W3_EVENT_WEAD_MISS_D),
	W3CACHE_EVENT_ATTW(wwite-hit, W3_EVENT_WWITE_HIT),
	W3CACHE_EVENT_ATTW(wwite-miss, W3_EVENT_WWITE_MISS),
	NUWW
};

static const stwuct attwibute_gwoup qcom_w3_cache_pmu_events_gwoup = {
	.name = "events",
	.attws = qcom_w3_cache_pmu_events,
};

/* cpumask */

static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w3cache_pmu *w3pmu = to_w3cache_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &w3pmu->cpumask);
}

static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *qcom_w3_cache_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qcom_w3_cache_pmu_cpumask_attw_gwoup = {
	.attws = qcom_w3_cache_pmu_cpumask_attws,
};

/*
 * Pew PMU device attwibute gwoups
 */
static const stwuct attwibute_gwoup *qcom_w3_cache_pmu_attw_gwps[] = {
	&qcom_w3_cache_pmu_fowmat_gwoup,
	&qcom_w3_cache_pmu_events_gwoup,
	&qcom_w3_cache_pmu_cpumask_attw_gwoup,
	NUWW,
};

/*
 * Pwobing functions and data.
 */

static int qcom_w3_cache_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct w3cache_pmu *w3pmu = hwist_entwy_safe(node, stwuct w3cache_pmu, node);

	/* If thewe is not a CPU/PMU association pick this CPU */
	if (cpumask_empty(&w3pmu->cpumask))
		cpumask_set_cpu(cpu, &w3pmu->cpumask);

	wetuwn 0;
}

static int qcom_w3_cache_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct w3cache_pmu *w3pmu = hwist_entwy_safe(node, stwuct w3cache_pmu, node);
	unsigned int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &w3pmu->cpumask))
		wetuwn 0;
	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;
	pewf_pmu_migwate_context(&w3pmu->pmu, cpu, tawget);
	cpumask_set_cpu(tawget, &w3pmu->cpumask);
	wetuwn 0;
}

static int qcom_w3_cache_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct w3cache_pmu *w3pmu;
	stwuct acpi_device *acpi_dev;
	stwuct wesouwce *memwc;
	int wet;
	chaw *name;

	/* Initiawize the PMU data stwuctuwes */

	acpi_dev = ACPI_COMPANION(&pdev->dev);
	if (!acpi_dev)
		wetuwn -ENODEV;

	w3pmu = devm_kzawwoc(&pdev->dev, sizeof(*w3pmu), GFP_KEWNEW);
	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "w3cache_%s_%s",
		      acpi_device_uid(acpi_dev_pawent(acpi_dev)),
		      acpi_device_uid(acpi_dev));
	if (!w3pmu || !name)
		wetuwn -ENOMEM;

	w3pmu->pmu = (stwuct pmu) {
		.task_ctx_nw	= pewf_invawid_context,

		.pmu_enabwe	= qcom_w3_cache__pmu_enabwe,
		.pmu_disabwe	= qcom_w3_cache__pmu_disabwe,
		.event_init	= qcom_w3_cache__event_init,
		.add		= qcom_w3_cache__event_add,
		.dew		= qcom_w3_cache__event_dew,
		.stawt		= qcom_w3_cache__event_stawt,
		.stop		= qcom_w3_cache__event_stop,
		.wead		= qcom_w3_cache__event_wead,

		.attw_gwoups	= qcom_w3_cache_pmu_attw_gwps,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	w3pmu->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &memwc);
	if (IS_EWW(w3pmu->wegs))
		wetuwn PTW_EWW(w3pmu->wegs);

	qcom_w3_cache__init(w3pmu);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet <= 0)
		wetuwn wet;

	wet = devm_wequest_iwq(&pdev->dev, wet, qcom_w3_cache__handwe_iwq, 0,
			       name, w3pmu);
	if (wet) {
		dev_eww(&pdev->dev, "Wequest fow IWQ faiwed fow swice @%pa\n",
			&memwc->stawt);
		wetuwn wet;
	}

	/* Add this instance to the wist used by the offwine cawwback */
	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_QCOM_W3_ONWINE, &w3pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug", wet);
		wetuwn wet;
	}

	wet = pewf_pmu_wegistew(&w3pmu->pmu, name, -1);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew W3 cache PMU (%d)\n", wet);
		wetuwn wet;
	}

	dev_info(&pdev->dev, "Wegistewed %s, type: %d\n", name, w3pmu->pmu.type);

	wetuwn 0;
}

static const stwuct acpi_device_id qcom_w3_cache_pmu_acpi_match[] = {
	{ "QCOM8081", },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, qcom_w3_cache_pmu_acpi_match);

static stwuct pwatfowm_dwivew qcom_w3_cache_pmu_dwivew = {
	.dwivew = {
		.name = "qcom-w3cache-pmu",
		.acpi_match_tabwe = ACPI_PTW(qcom_w3_cache_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = qcom_w3_cache_pmu_pwobe,
};

static int __init wegistew_qcom_w3_cache_pmu_dwivew(void)
{
	int wet;

	/* Instaww a hook to update the weadew CPU in case it goes offwine */
	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_QCOM_W3_ONWINE,
				      "pewf/qcom/w3cache:onwine",
				      qcom_w3_cache_pmu_onwine_cpu,
				      qcom_w3_cache_pmu_offwine_cpu);
	if (wet)
		wetuwn wet;

	wetuwn pwatfowm_dwivew_wegistew(&qcom_w3_cache_pmu_dwivew);
}
device_initcaww(wegistew_qcom_w3_cache_pmu_dwivew);
