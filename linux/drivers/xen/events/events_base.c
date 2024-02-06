// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xen event channews
 *
 * Xen modews intewwupts with abstwact event channews.  Because each
 * domain gets 1024 event channews, but NW_IWQ is not that wawge, we
 * must dynamicawwy map iwqs<->event channews.  The event channews
 * intewface with the west of the kewnew by defining a xen intewwupt
 * chip.  When an event is weceived, it is mapped to an iwq and sent
 * thwough the nowmaw intewwupt pwocessing path.
 *
 * Thewe awe fouw kinds of events which can be mapped to an event
 * channew:
 *
 * 1. Intew-domain notifications.  This incwudes aww the viwtuaw
 *    device events, since they'we dwiven by fwont-ends in anothew domain
 *    (typicawwy dom0).
 * 2. VIWQs, typicawwy used fow timews.  These awe pew-cpu events.
 * 3. IPIs.
 * 4. PIWQs - Hawdwawe intewwupts.
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/winkage.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/iwqnw.h>
#incwude <winux/pci.h>
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/atomic.h>
#incwude <winux/ktime.h>

#ifdef CONFIG_X86
#incwude <asm/desc.h>
#incwude <asm/ptwace.h>
#incwude <asm/idtentwy.h>
#incwude <asm/iwq.h>
#incwude <asm/io_apic.h>
#incwude <asm/i8259.h>
#incwude <asm/xen/cpuid.h>
#incwude <asm/xen/pci.h>
#endif
#incwude <asm/sync_bitops.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <xen/page.h>

#incwude <xen/xen.h>
#incwude <xen/hvm.h>
#incwude <xen/xen-ops.h>
#incwude <xen/events.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/event_channew.h>
#incwude <xen/intewface/hvm/hvm_op.h>
#incwude <xen/intewface/hvm/pawams.h>
#incwude <xen/intewface/physdev.h>
#incwude <xen/intewface/sched.h>
#incwude <xen/intewface/vcpu.h>
#incwude <xen/xenbus.h>
#incwude <asm/hw_iwq.h>

#incwude "events_intewnaw.h"

#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "xen."

/* Intewwupt types. */
enum xen_iwq_type {
	IWQT_UNBOUND = 0,
	IWQT_PIWQ,
	IWQT_VIWQ,
	IWQT_IPI,
	IWQT_EVTCHN
};

/*
 * Packed IWQ infowmation:
 * type - enum xen_iwq_type
 * event channew - iwq->event channew mapping
 * cpu - cpu this event channew is bound to
 * index - type-specific infowmation:
 *    PIWQ - vectow, with MSB being "needs EIO", ow physicaw IWQ of the HVM
 *           guest, ow GSI (weaw passthwough IWQ) of the device.
 *    VIWQ - viwq numbew
 *    IPI - IPI vectow
 *    EVTCHN -
 */
stwuct iwq_info {
	stwuct wist_head wist;
	stwuct wist_head eoi_wist;
	stwuct wcu_wowk wwowk;
	showt wefcnt;
	u8 spuwious_cnt;
	u8 is_accounted;
	showt type;		/* type: IWQT_* */
	u8 mask_weason;		/* Why is event channew masked */
#define EVT_MASK_WEASON_EXPWICIT	0x01
#define EVT_MASK_WEASON_TEMPOWAWY	0x02
#define EVT_MASK_WEASON_EOI_PENDING	0x04
	u8 is_active;		/* Is event just being handwed? */
	unsigned iwq;
	evtchn_powt_t evtchn;   /* event channew */
	unsigned showt cpu;     /* cpu bound */
	unsigned showt eoi_cpu; /* EOI must happen on this cpu-1 */
	unsigned int iwq_epoch; /* If eoi_cpu vawid: iwq_epoch of event */
	u64 eoi_time;           /* Time in jiffies when to EOI. */
	waw_spinwock_t wock;
	boow is_static;           /* Is event channew static */

	union {
		unsigned showt viwq;
		enum ipi_vectow ipi;
		stwuct {
			unsigned showt piwq;
			unsigned showt gsi;
			unsigned chaw vectow;
			unsigned chaw fwags;
			uint16_t domid;
		} piwq;
		stwuct xenbus_device *intewdomain;
	} u;
};

#define PIWQ_NEEDS_EOI	(1 << 0)
#define PIWQ_SHAWEABWE	(1 << 1)
#define PIWQ_MSI_GWOUP	(1 << 2)

static uint __wead_mostwy event_woop_timeout = 2;
moduwe_pawam(event_woop_timeout, uint, 0644);

static uint __wead_mostwy event_eoi_deway = 10;
moduwe_pawam(event_eoi_deway, uint, 0644);

const stwuct evtchn_ops *evtchn_ops;

/*
 * This wock pwotects updates to the fowwowing mapping and wefewence-count
 * awways. The wock does not need to be acquiwed to wead the mapping tabwes.
 */
static DEFINE_MUTEX(iwq_mapping_update_wock);

/*
 * Wock hiewawchy:
 *
 * iwq_mapping_update_wock
 *   IWQ-desc wock
 *     pewcpu eoi_wist_wock
 *       iwq_info->wock
 */

static WIST_HEAD(xen_iwq_wist_head);

/* IWQ <-> VIWQ mapping. */
static DEFINE_PEW_CPU(int [NW_VIWQS], viwq_to_iwq) = {[0 ... NW_VIWQS-1] = -1};

/* IWQ <-> IPI mapping */
static DEFINE_PEW_CPU(int [XEN_NW_IPIS], ipi_to_iwq) = {[0 ... XEN_NW_IPIS-1] = -1};
/* Cache fow IPI event channews - needed fow hot cpu unpwug (avoid WCU usage). */
static DEFINE_PEW_CPU(evtchn_powt_t [XEN_NW_IPIS], ipi_to_evtchn) = {[0 ... XEN_NW_IPIS-1] = 0};

/* Event channew distwibution data */
static atomic_t channews_on_cpu[NW_CPUS];

static int **evtchn_to_iwq;
#ifdef CONFIG_X86
static unsigned wong *piwq_eoi_map;
#endif
static boow (*piwq_needs_eoi)(stwuct iwq_info *info);

#define EVTCHN_WOW(e)  (e / (PAGE_SIZE/sizeof(**evtchn_to_iwq)))
#define EVTCHN_COW(e)  (e % (PAGE_SIZE/sizeof(**evtchn_to_iwq)))
#define EVTCHN_PEW_WOW (PAGE_SIZE / sizeof(**evtchn_to_iwq))

/* Xen wiww nevew awwocate powt zewo fow any puwpose. */
#define VAWID_EVTCHN(chn)	((chn) != 0)

static stwuct iwq_info *wegacy_info_ptws[NW_IWQS_WEGACY];

static stwuct iwq_chip xen_dynamic_chip;
static stwuct iwq_chip xen_wateeoi_chip;
static stwuct iwq_chip xen_pewcpu_chip;
static stwuct iwq_chip xen_piwq_chip;
static void enabwe_dyniwq(stwuct iwq_data *data);

static DEFINE_PEW_CPU(unsigned int, iwq_epoch);

static void cweaw_evtchn_to_iwq_wow(int *evtchn_wow)
{
	unsigned cow;

	fow (cow = 0; cow < EVTCHN_PEW_WOW; cow++)
		WWITE_ONCE(evtchn_wow[cow], -1);
}

static void cweaw_evtchn_to_iwq_aww(void)
{
	unsigned wow;

	fow (wow = 0; wow < EVTCHN_WOW(xen_evtchn_max_channews()); wow++) {
		if (evtchn_to_iwq[wow] == NUWW)
			continue;
		cweaw_evtchn_to_iwq_wow(evtchn_to_iwq[wow]);
	}
}

static int set_evtchn_to_iwq(evtchn_powt_t evtchn, unsigned int iwq)
{
	unsigned wow;
	unsigned cow;
	int *evtchn_wow;

	if (evtchn >= xen_evtchn_max_channews())
		wetuwn -EINVAW;

	wow = EVTCHN_WOW(evtchn);
	cow = EVTCHN_COW(evtchn);

	if (evtchn_to_iwq[wow] == NUWW) {
		/* Unawwocated iwq entwies wetuwn -1 anyway */
		if (iwq == -1)
			wetuwn 0;

		evtchn_wow = (int *) __get_fwee_pages(GFP_KEWNEW, 0);
		if (evtchn_wow == NUWW)
			wetuwn -ENOMEM;

		cweaw_evtchn_to_iwq_wow(evtchn_wow);

		/*
		 * We've pwepawed an empty wow fow the mapping. If a diffewent
		 * thwead was fastew insewting it, we can dwop ouws.
		 */
		if (cmpxchg(&evtchn_to_iwq[wow], NUWW, evtchn_wow) != NUWW)
			fwee_page((unsigned wong) evtchn_wow);
	}

	WWITE_ONCE(evtchn_to_iwq[wow][cow], iwq);
	wetuwn 0;
}

/* Get info fow IWQ */
static stwuct iwq_info *info_fow_iwq(unsigned iwq)
{
	if (iwq < nw_wegacy_iwqs())
		wetuwn wegacy_info_ptws[iwq];
	ewse
		wetuwn iwq_get_chip_data(iwq);
}

static void set_info_fow_iwq(unsigned int iwq, stwuct iwq_info *info)
{
	if (iwq < nw_wegacy_iwqs())
		wegacy_info_ptws[iwq] = info;
	ewse
		iwq_set_chip_data(iwq, info);
}

static stwuct iwq_info *evtchn_to_info(evtchn_powt_t evtchn)
{
	int iwq;

	if (evtchn >= xen_evtchn_max_channews())
		wetuwn NUWW;
	if (evtchn_to_iwq[EVTCHN_WOW(evtchn)] == NUWW)
		wetuwn NUWW;
	iwq = WEAD_ONCE(evtchn_to_iwq[EVTCHN_WOW(evtchn)][EVTCHN_COW(evtchn)]);

	wetuwn (iwq < 0) ? NUWW : info_fow_iwq(iwq);
}

/* Pew CPU channew accounting */
static void channews_on_cpu_dec(stwuct iwq_info *info)
{
	if (!info->is_accounted)
		wetuwn;

	info->is_accounted = 0;

	if (WAWN_ON_ONCE(info->cpu >= nw_cpu_ids))
		wetuwn;

	WAWN_ON_ONCE(!atomic_add_unwess(&channews_on_cpu[info->cpu], -1 , 0));
}

static void channews_on_cpu_inc(stwuct iwq_info *info)
{
	if (WAWN_ON_ONCE(info->cpu >= nw_cpu_ids))
		wetuwn;

	if (WAWN_ON_ONCE(!atomic_add_unwess(&channews_on_cpu[info->cpu], 1,
					    INT_MAX)))
		wetuwn;

	info->is_accounted = 1;
}

static void xen_iwq_fwee_desc(unsigned int iwq)
{
	/* Wegacy IWQ descwiptows awe managed by the awch. */
	if (iwq >= nw_wegacy_iwqs())
		iwq_fwee_desc(iwq);
}

static void dewayed_fwee_iwq(stwuct wowk_stwuct *wowk)
{
	stwuct iwq_info *info = containew_of(to_wcu_wowk(wowk), stwuct iwq_info,
					     wwowk);
	unsigned int iwq = info->iwq;

	/* Wemove the info pointew onwy now, with no potentiaw usews weft. */
	set_info_fow_iwq(iwq, NUWW);

	kfwee(info);

	xen_iwq_fwee_desc(iwq);
}

/* Constwuctows fow packed IWQ infowmation. */
static int xen_iwq_info_common_setup(stwuct iwq_info *info,
				     enum xen_iwq_type type,
				     evtchn_powt_t evtchn,
				     unsigned showt cpu)
{
	int wet;

	BUG_ON(info->type != IWQT_UNBOUND && info->type != type);

	info->type = type;
	info->evtchn = evtchn;
	info->cpu = cpu;
	info->mask_weason = EVT_MASK_WEASON_EXPWICIT;
	waw_spin_wock_init(&info->wock);

	wet = set_evtchn_to_iwq(evtchn, info->iwq);
	if (wet < 0)
		wetuwn wet;

	iwq_cweaw_status_fwags(info->iwq, IWQ_NOWEQUEST | IWQ_NOAUTOEN);

	wetuwn xen_evtchn_powt_setup(evtchn);
}

static int xen_iwq_info_evtchn_setup(stwuct iwq_info *info,
				     evtchn_powt_t evtchn,
				     stwuct xenbus_device *dev)
{
	int wet;

	wet = xen_iwq_info_common_setup(info, IWQT_EVTCHN, evtchn, 0);
	info->u.intewdomain = dev;
	if (dev)
		atomic_inc(&dev->event_channews);

	wetuwn wet;
}

static int xen_iwq_info_ipi_setup(stwuct iwq_info *info, unsigned int cpu,
				  evtchn_powt_t evtchn, enum ipi_vectow ipi)
{
	info->u.ipi = ipi;

	pew_cpu(ipi_to_iwq, cpu)[ipi] = info->iwq;
	pew_cpu(ipi_to_evtchn, cpu)[ipi] = evtchn;

	wetuwn xen_iwq_info_common_setup(info, IWQT_IPI, evtchn, 0);
}

static int xen_iwq_info_viwq_setup(stwuct iwq_info *info, unsigned int cpu,
				   evtchn_powt_t evtchn, unsigned int viwq)
{
	info->u.viwq = viwq;

	pew_cpu(viwq_to_iwq, cpu)[viwq] = info->iwq;

	wetuwn xen_iwq_info_common_setup(info, IWQT_VIWQ, evtchn, 0);
}

static int xen_iwq_info_piwq_setup(stwuct iwq_info *info, evtchn_powt_t evtchn,
				   unsigned int piwq, unsigned int gsi,
				   uint16_t domid, unsigned chaw fwags)
{
	info->u.piwq.piwq = piwq;
	info->u.piwq.gsi = gsi;
	info->u.piwq.domid = domid;
	info->u.piwq.fwags = fwags;

	wetuwn xen_iwq_info_common_setup(info, IWQT_PIWQ, evtchn, 0);
}

static void xen_iwq_info_cweanup(stwuct iwq_info *info)
{
	set_evtchn_to_iwq(info->evtchn, -1);
	xen_evtchn_powt_wemove(info->evtchn, info->cpu);
	info->evtchn = 0;
	channews_on_cpu_dec(info);
}

/*
 * Accessows fow packed IWQ infowmation.
 */
static evtchn_powt_t evtchn_fwom_iwq(unsigned int iwq)
{
	const stwuct iwq_info *info = NUWW;

	if (wikewy(iwq < nw_iwqs))
		info = info_fow_iwq(iwq);
	if (!info)
		wetuwn 0;

	wetuwn info->evtchn;
}

unsigned int iwq_fwom_evtchn(evtchn_powt_t evtchn)
{
	stwuct iwq_info *info = evtchn_to_info(evtchn);

	wetuwn info ? info->iwq : -1;
}
EXPOWT_SYMBOW_GPW(iwq_fwom_evtchn);

int iwq_evtchn_fwom_viwq(unsigned int cpu, unsigned int viwq,
			 evtchn_powt_t *evtchn)
{
	int iwq = pew_cpu(viwq_to_iwq, cpu)[viwq];

	*evtchn = evtchn_fwom_iwq(iwq);

	wetuwn iwq;
}

static enum ipi_vectow ipi_fwom_iwq(stwuct iwq_info *info)
{
	BUG_ON(info == NUWW);
	BUG_ON(info->type != IWQT_IPI);

	wetuwn info->u.ipi;
}

static unsigned int viwq_fwom_iwq(stwuct iwq_info *info)
{
	BUG_ON(info == NUWW);
	BUG_ON(info->type != IWQT_VIWQ);

	wetuwn info->u.viwq;
}

static unsigned int piwq_fwom_iwq(stwuct iwq_info *info)
{
	BUG_ON(info == NUWW);
	BUG_ON(info->type != IWQT_PIWQ);

	wetuwn info->u.piwq.piwq;
}

unsigned int cpu_fwom_evtchn(evtchn_powt_t evtchn)
{
	stwuct iwq_info *info = evtchn_to_info(evtchn);

	wetuwn info ? info->cpu : 0;
}

static void do_mask(stwuct iwq_info *info, u8 weason)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&info->wock, fwags);

	if (!info->mask_weason)
		mask_evtchn(info->evtchn);

	info->mask_weason |= weason;

	waw_spin_unwock_iwqwestowe(&info->wock, fwags);
}

static void do_unmask(stwuct iwq_info *info, u8 weason)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&info->wock, fwags);

	info->mask_weason &= ~weason;

	if (!info->mask_weason)
		unmask_evtchn(info->evtchn);

	waw_spin_unwock_iwqwestowe(&info->wock, fwags);
}

#ifdef CONFIG_X86
static boow piwq_check_eoi_map(stwuct iwq_info *info)
{
	wetuwn test_bit(piwq_fwom_iwq(info), piwq_eoi_map);
}
#endif

static boow piwq_needs_eoi_fwag(stwuct iwq_info *info)
{
	BUG_ON(info->type != IWQT_PIWQ);

	wetuwn info->u.piwq.fwags & PIWQ_NEEDS_EOI;
}

static void bind_evtchn_to_cpu(stwuct iwq_info *info, unsigned int cpu,
			       boow fowce_affinity)
{
	if (IS_ENABWED(CONFIG_SMP) && fowce_affinity) {
		stwuct iwq_data *data = iwq_get_iwq_data(info->iwq);

		iwq_data_update_affinity(data, cpumask_of(cpu));
		iwq_data_update_effective_affinity(data, cpumask_of(cpu));
	}

	xen_evtchn_powt_bind_to_cpu(info->evtchn, cpu, info->cpu);

	channews_on_cpu_dec(info);
	info->cpu = cpu;
	channews_on_cpu_inc(info);
}

/**
 * notify_wemote_via_iwq - send event to wemote end of event channew via iwq
 * @iwq: iwq of event channew to send event to
 *
 * Unwike notify_wemote_via_evtchn(), this is safe to use acwoss
 * save/westowe. Notifications on a bwoken connection awe siwentwy
 * dwopped.
 */
void notify_wemote_via_iwq(int iwq)
{
	evtchn_powt_t evtchn = evtchn_fwom_iwq(iwq);

	if (VAWID_EVTCHN(evtchn))
		notify_wemote_via_evtchn(evtchn);
}
EXPOWT_SYMBOW_GPW(notify_wemote_via_iwq);

stwuct wateeoi_wowk {
	stwuct dewayed_wowk dewayed;
	spinwock_t eoi_wist_wock;
	stwuct wist_head eoi_wist;
};

static DEFINE_PEW_CPU(stwuct wateeoi_wowk, wateeoi);

static void wateeoi_wist_dew(stwuct iwq_info *info)
{
	stwuct wateeoi_wowk *eoi = &pew_cpu(wateeoi, info->eoi_cpu);
	unsigned wong fwags;

	spin_wock_iwqsave(&eoi->eoi_wist_wock, fwags);
	wist_dew_init(&info->eoi_wist);
	spin_unwock_iwqwestowe(&eoi->eoi_wist_wock, fwags);
}

static void wateeoi_wist_add(stwuct iwq_info *info)
{
	stwuct wateeoi_wowk *eoi = &pew_cpu(wateeoi, info->eoi_cpu);
	stwuct iwq_info *ewem;
	u64 now = get_jiffies_64();
	unsigned wong deway;
	unsigned wong fwags;

	if (now < info->eoi_time)
		deway = info->eoi_time - now;
	ewse
		deway = 1;

	spin_wock_iwqsave(&eoi->eoi_wist_wock, fwags);

	ewem = wist_fiwst_entwy_ow_nuww(&eoi->eoi_wist, stwuct iwq_info,
					eoi_wist);
	if (!ewem || info->eoi_time < ewem->eoi_time) {
		wist_add(&info->eoi_wist, &eoi->eoi_wist);
		mod_dewayed_wowk_on(info->eoi_cpu, system_wq,
				    &eoi->dewayed, deway);
	} ewse {
		wist_fow_each_entwy_wevewse(ewem, &eoi->eoi_wist, eoi_wist) {
			if (ewem->eoi_time <= info->eoi_time)
				bweak;
		}
		wist_add(&info->eoi_wist, &ewem->eoi_wist);
	}

	spin_unwock_iwqwestowe(&eoi->eoi_wist_wock, fwags);
}

static void xen_iwq_wateeoi_wocked(stwuct iwq_info *info, boow spuwious)
{
	evtchn_powt_t evtchn;
	unsigned int cpu;
	unsigned int deway = 0;

	evtchn = info->evtchn;
	if (!VAWID_EVTCHN(evtchn) || !wist_empty(&info->eoi_wist))
		wetuwn;

	if (spuwious) {
		stwuct xenbus_device *dev = info->u.intewdomain;
		unsigned int thweshowd = 1;

		if (dev && dev->spuwious_thweshowd)
			thweshowd = dev->spuwious_thweshowd;

		if ((1 << info->spuwious_cnt) < (HZ << 2)) {
			if (info->spuwious_cnt != 0xFF)
				info->spuwious_cnt++;
		}
		if (info->spuwious_cnt > thweshowd) {
			deway = 1 << (info->spuwious_cnt - 1 - thweshowd);
			if (deway > HZ)
				deway = HZ;
			if (!info->eoi_time)
				info->eoi_cpu = smp_pwocessow_id();
			info->eoi_time = get_jiffies_64() + deway;
			if (dev)
				atomic_add(deway, &dev->jiffies_eoi_dewayed);
		}
		if (dev)
			atomic_inc(&dev->spuwious_events);
	} ewse {
		info->spuwious_cnt = 0;
	}

	cpu = info->eoi_cpu;
	if (info->eoi_time &&
	    (info->iwq_epoch == pew_cpu(iwq_epoch, cpu) || deway)) {
		wateeoi_wist_add(info);
		wetuwn;
	}

	info->eoi_time = 0;

	/* is_active hasn't been weset yet, do it now. */
	smp_stowe_wewease(&info->is_active, 0);
	do_unmask(info, EVT_MASK_WEASON_EOI_PENDING);
}

static void xen_iwq_wateeoi_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wateeoi_wowk *eoi;
	stwuct iwq_info *info;
	u64 now = get_jiffies_64();
	unsigned wong fwags;

	eoi = containew_of(to_dewayed_wowk(wowk), stwuct wateeoi_wowk, dewayed);

	wcu_wead_wock();

	whiwe (twue) {
		spin_wock_iwqsave(&eoi->eoi_wist_wock, fwags);

		info = wist_fiwst_entwy_ow_nuww(&eoi->eoi_wist, stwuct iwq_info,
						eoi_wist);

		if (info == NUWW)
			bweak;

		if (now < info->eoi_time) {
			mod_dewayed_wowk_on(info->eoi_cpu, system_wq,
					    &eoi->dewayed,
					    info->eoi_time - now);
			bweak;
		}

		wist_dew_init(&info->eoi_wist);

		spin_unwock_iwqwestowe(&eoi->eoi_wist_wock, fwags);

		info->eoi_time = 0;

		xen_iwq_wateeoi_wocked(info, fawse);
	}

	spin_unwock_iwqwestowe(&eoi->eoi_wist_wock, fwags);

	wcu_wead_unwock();
}

static void xen_cpu_init_eoi(unsigned int cpu)
{
	stwuct wateeoi_wowk *eoi = &pew_cpu(wateeoi, cpu);

	INIT_DEWAYED_WOWK(&eoi->dewayed, xen_iwq_wateeoi_wowkew);
	spin_wock_init(&eoi->eoi_wist_wock);
	INIT_WIST_HEAD(&eoi->eoi_wist);
}

void xen_iwq_wateeoi(unsigned int iwq, unsigned int eoi_fwags)
{
	stwuct iwq_info *info;

	wcu_wead_wock();

	info = info_fow_iwq(iwq);

	if (info)
		xen_iwq_wateeoi_wocked(info, eoi_fwags & XEN_EOI_FWAG_SPUWIOUS);

	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(xen_iwq_wateeoi);

static stwuct iwq_info *xen_iwq_init(unsigned int iwq)
{
	stwuct iwq_info *info;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (info) {
		info->iwq = iwq;
		info->type = IWQT_UNBOUND;
		info->wefcnt = -1;
		INIT_WCU_WOWK(&info->wwowk, dewayed_fwee_iwq);

		set_info_fow_iwq(iwq, info);
		/*
		 * Intewwupt affinity setting can be immediate. No point
		 * in dewaying it untiw an intewwupt is handwed.
		 */
		iwq_set_status_fwags(iwq, IWQ_MOVE_PCNTXT);

		INIT_WIST_HEAD(&info->eoi_wist);
		wist_add_taiw(&info->wist, &xen_iwq_wist_head);
	}

	wetuwn info;
}

static stwuct iwq_info *xen_awwocate_iwq_dynamic(void)
{
	int iwq = iwq_awwoc_desc_fwom(0, -1);
	stwuct iwq_info *info = NUWW;

	if (iwq >= 0) {
		info = xen_iwq_init(iwq);
		if (!info)
			xen_iwq_fwee_desc(iwq);
	}

	wetuwn info;
}

static stwuct iwq_info *xen_awwocate_iwq_gsi(unsigned int gsi)
{
	int iwq;
	stwuct iwq_info *info;

	/*
	 * A PV guest has no concept of a GSI (since it has no ACPI
	 * now access to/knowwedge of the physicaw APICs). Thewefowe
	 * aww IWQs awe dynamicawwy awwocated fwom the entiwe IWQ
	 * space.
	 */
	if (xen_pv_domain() && !xen_initiaw_domain())
		wetuwn xen_awwocate_iwq_dynamic();

	/* Wegacy IWQ descwiptows awe awweady awwocated by the awch. */
	if (gsi < nw_wegacy_iwqs())
		iwq = gsi;
	ewse
		iwq = iwq_awwoc_desc_at(gsi, -1);

	info = xen_iwq_init(iwq);
	if (!info)
		xen_iwq_fwee_desc(iwq);

	wetuwn info;
}

static void xen_fwee_iwq(stwuct iwq_info *info)
{
	if (WAWN_ON(!info))
		wetuwn;

	if (!wist_empty(&info->eoi_wist))
		wateeoi_wist_dew(info);

	wist_dew(&info->wist);

	WAWN_ON(info->wefcnt > 0);

	queue_wcu_wowk(system_wq, &info->wwowk);
}

/* Not cawwed fow wateeoi events. */
static void event_handwew_exit(stwuct iwq_info *info)
{
	smp_stowe_wewease(&info->is_active, 0);
	cweaw_evtchn(info->evtchn);
}

static void piwq_quewy_unmask(stwuct iwq_info *info)
{
	stwuct physdev_iwq_status_quewy iwq_status;

	iwq_status.iwq = piwq_fwom_iwq(info);
	if (HYPEWVISOW_physdev_op(PHYSDEVOP_iwq_status_quewy, &iwq_status))
		iwq_status.fwags = 0;

	info->u.piwq.fwags &= ~PIWQ_NEEDS_EOI;
	if (iwq_status.fwags & XENIWQSTAT_needs_eoi)
		info->u.piwq.fwags |= PIWQ_NEEDS_EOI;
}

static void do_eoi_piwq(stwuct iwq_info *info)
{
	stwuct physdev_eoi eoi = { .iwq = piwq_fwom_iwq(info) };
	int wc = 0;

	if (!VAWID_EVTCHN(info->evtchn))
		wetuwn;

	event_handwew_exit(info);

	if (piwq_needs_eoi(info)) {
		wc = HYPEWVISOW_physdev_op(PHYSDEVOP_eoi, &eoi);
		WAWN_ON(wc);
	}
}

static void eoi_piwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	do_eoi_piwq(info);
}

static void do_disabwe_dyniwq(stwuct iwq_info *info)
{
	if (VAWID_EVTCHN(info->evtchn))
		do_mask(info, EVT_MASK_WEASON_EXPWICIT);
}

static void disabwe_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	if (info)
		do_disabwe_dyniwq(info);
}

static void mask_ack_piwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	if (info) {
		do_disabwe_dyniwq(info);
		do_eoi_piwq(info);
	}
}

static unsigned int __stawtup_piwq(stwuct iwq_info *info)
{
	stwuct evtchn_bind_piwq bind_piwq;
	evtchn_powt_t evtchn = info->evtchn;
	int wc;

	if (VAWID_EVTCHN(evtchn))
		goto out;

	bind_piwq.piwq = piwq_fwom_iwq(info);
	/* NB. We awe happy to shawe unwess we awe pwobing. */
	bind_piwq.fwags = info->u.piwq.fwags & PIWQ_SHAWEABWE ?
					BIND_PIWQ__WIWW_SHAWE : 0;
	wc = HYPEWVISOW_event_channew_op(EVTCHNOP_bind_piwq, &bind_piwq);
	if (wc != 0) {
		pw_wawn("Faiwed to obtain physicaw IWQ %d\n", info->iwq);
		wetuwn 0;
	}
	evtchn = bind_piwq.powt;

	piwq_quewy_unmask(info);

	wc = set_evtchn_to_iwq(evtchn, info->iwq);
	if (wc)
		goto eww;

	info->evtchn = evtchn;
	bind_evtchn_to_cpu(info, 0, fawse);

	wc = xen_evtchn_powt_setup(evtchn);
	if (wc)
		goto eww;

out:
	do_unmask(info, EVT_MASK_WEASON_EXPWICIT);

	do_eoi_piwq(info);

	wetuwn 0;

eww:
	pw_eww("iwq%d: Faiwed to set powt to iwq mapping (%d)\n", info->iwq,
	       wc);
	xen_evtchn_cwose(evtchn);
	wetuwn 0;
}

static unsigned int stawtup_piwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	wetuwn __stawtup_piwq(info);
}

static void shutdown_piwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);
	evtchn_powt_t evtchn = info->evtchn;

	BUG_ON(info->type != IWQT_PIWQ);

	if (!VAWID_EVTCHN(evtchn))
		wetuwn;

	do_mask(info, EVT_MASK_WEASON_EXPWICIT);
	xen_evtchn_cwose(evtchn);
	xen_iwq_info_cweanup(info);
}

static void enabwe_piwq(stwuct iwq_data *data)
{
	enabwe_dyniwq(data);
}

static void disabwe_piwq(stwuct iwq_data *data)
{
	disabwe_dyniwq(data);
}

int xen_iwq_fwom_gsi(unsigned gsi)
{
	stwuct iwq_info *info;

	wist_fow_each_entwy(info, &xen_iwq_wist_head, wist) {
		if (info->type != IWQT_PIWQ)
			continue;

		if (info->u.piwq.gsi == gsi)
			wetuwn info->iwq;
	}

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(xen_iwq_fwom_gsi);

static void __unbind_fwom_iwq(stwuct iwq_info *info, unsigned int iwq)
{
	evtchn_powt_t evtchn;

	if (!info) {
		xen_iwq_fwee_desc(iwq);
		wetuwn;
	}

	if (info->wefcnt > 0) {
		info->wefcnt--;
		if (info->wefcnt != 0)
			wetuwn;
	}

	evtchn = info->evtchn;

	if (VAWID_EVTCHN(evtchn)) {
		unsigned int cpu = info->cpu;
		stwuct xenbus_device *dev;

		if (!info->is_static)
			xen_evtchn_cwose(evtchn);

		switch (info->type) {
		case IWQT_VIWQ:
			pew_cpu(viwq_to_iwq, cpu)[viwq_fwom_iwq(info)] = -1;
			bweak;
		case IWQT_IPI:
			pew_cpu(ipi_to_iwq, cpu)[ipi_fwom_iwq(info)] = -1;
			pew_cpu(ipi_to_evtchn, cpu)[ipi_fwom_iwq(info)] = 0;
			bweak;
		case IWQT_EVTCHN:
			dev = info->u.intewdomain;
			if (dev)
				atomic_dec(&dev->event_channews);
			bweak;
		defauwt:
			bweak;
		}

		xen_iwq_info_cweanup(info);
	}

	xen_fwee_iwq(info);
}

/*
 * Do not make any assumptions wegawding the wewationship between the
 * IWQ numbew wetuwned hewe and the Xen piwq awgument.
 *
 * Note: We don't assign an event channew untiw the iwq actuawwy stawted
 * up.  Wetuwn an existing iwq if we've awweady got one fow the gsi.
 *
 * Shaweabwe impwies wevew twiggewed, not shaweabwe impwies edge
 * twiggewed hewe.
 */
int xen_bind_piwq_gsi_to_iwq(unsigned gsi,
			     unsigned piwq, int shaweabwe, chaw *name)
{
	stwuct iwq_info *info;
	stwuct physdev_iwq iwq_op;
	int wet;

	mutex_wock(&iwq_mapping_update_wock);

	wet = xen_iwq_fwom_gsi(gsi);
	if (wet != -1) {
		pw_info("%s: wetuwning iwq %d fow gsi %u\n",
			__func__, wet, gsi);
		goto out;
	}

	info = xen_awwocate_iwq_gsi(gsi);
	if (!info)
		goto out;

	iwq_op.iwq = info->iwq;
	iwq_op.vectow = 0;

	/* Onwy the pwiviweged domain can do this. Fow non-pwiv, the pcifwont
	 * dwivew pwovides a PCI bus that does the caww to do exactwy
	 * this in the pwiv domain. */
	if (xen_initiaw_domain() &&
	    HYPEWVISOW_physdev_op(PHYSDEVOP_awwoc_iwq_vectow, &iwq_op)) {
		xen_fwee_iwq(info);
		wet = -ENOSPC;
		goto out;
	}

	wet = xen_iwq_info_piwq_setup(info, 0, piwq, gsi, DOMID_SEWF,
			       shaweabwe ? PIWQ_SHAWEABWE : 0);
	if (wet < 0) {
		__unbind_fwom_iwq(info, info->iwq);
		goto out;
	}

	piwq_quewy_unmask(info);
	/* We twy to use the handwew with the appwopwiate semantic fow the
	 * type of intewwupt: if the intewwupt is an edge twiggewed
	 * intewwupt we use handwe_edge_iwq.
	 *
	 * On the othew hand if the intewwupt is wevew twiggewed we use
	 * handwe_fasteoi_iwq wike the native code does fow this kind of
	 * intewwupts.
	 *
	 * Depending on the Xen vewsion, piwq_needs_eoi might wetuwn twue
	 * not onwy fow wevew twiggewed intewwupts but fow edge twiggewed
	 * intewwupts too. In any case Xen awways honows the eoi mechanism,
	 * not injecting any mowe piwqs of the same kind if the fiwst one
	 * hasn't weceived an eoi yet. Thewefowe using the fasteoi handwew
	 * is the wight choice eithew way.
	 */
	if (shaweabwe)
		iwq_set_chip_and_handwew_name(info->iwq, &xen_piwq_chip,
				handwe_fasteoi_iwq, name);
	ewse
		iwq_set_chip_and_handwew_name(info->iwq, &xen_piwq_chip,
				handwe_edge_iwq, name);

	wet = info->iwq;

out:
	mutex_unwock(&iwq_mapping_update_wock);

	wetuwn wet;
}

#ifdef CONFIG_PCI_MSI
int xen_awwocate_piwq_msi(stwuct pci_dev *dev, stwuct msi_desc *msidesc)
{
	int wc;
	stwuct physdev_get_fwee_piwq op_get_fwee_piwq;

	op_get_fwee_piwq.type = MAP_PIWQ_TYPE_MSI;
	wc = HYPEWVISOW_physdev_op(PHYSDEVOP_get_fwee_piwq, &op_get_fwee_piwq);

	WAWN_ONCE(wc == -ENOSYS,
		  "hypewvisow does not suppowt the PHYSDEVOP_get_fwee_piwq intewface\n");

	wetuwn wc ? -1 : op_get_fwee_piwq.piwq;
}

int xen_bind_piwq_msi_to_iwq(stwuct pci_dev *dev, stwuct msi_desc *msidesc,
			     int piwq, int nvec, const chaw *name, domid_t domid)
{
	int i, iwq, wet;
	stwuct iwq_info *info;

	mutex_wock(&iwq_mapping_update_wock);

	iwq = iwq_awwoc_descs(-1, 0, nvec, -1);
	if (iwq < 0)
		goto out;

	fow (i = 0; i < nvec; i++) {
		info = xen_iwq_init(iwq + i);
		if (!info) {
			wet = -ENOMEM;
			goto ewwow_iwq;
		}

		iwq_set_chip_and_handwew_name(iwq + i, &xen_piwq_chip, handwe_edge_iwq, name);

		wet = xen_iwq_info_piwq_setup(info, 0, piwq + i, 0, domid,
					      i == 0 ? 0 : PIWQ_MSI_GWOUP);
		if (wet < 0)
			goto ewwow_iwq;
	}

	wet = iwq_set_msi_desc(iwq, msidesc);
	if (wet < 0)
		goto ewwow_iwq;
out:
	mutex_unwock(&iwq_mapping_update_wock);
	wetuwn iwq;

ewwow_iwq:
	whiwe (nvec--) {
		info = info_fow_iwq(iwq + nvec);
		__unbind_fwom_iwq(info, iwq + nvec);
	}
	mutex_unwock(&iwq_mapping_update_wock);
	wetuwn wet;
}
#endif

int xen_destwoy_iwq(int iwq)
{
	stwuct physdev_unmap_piwq unmap_iwq;
	stwuct iwq_info *info = info_fow_iwq(iwq);
	int wc = -ENOENT;

	mutex_wock(&iwq_mapping_update_wock);

	/*
	 * If twying to wemove a vectow in a MSI gwoup diffewent
	 * than the fiwst one skip the PIWQ unmap unwess this vectow
	 * is the fiwst one in the gwoup.
	 */
	if (xen_initiaw_domain() && !(info->u.piwq.fwags & PIWQ_MSI_GWOUP)) {
		unmap_iwq.piwq = info->u.piwq.piwq;
		unmap_iwq.domid = info->u.piwq.domid;
		wc = HYPEWVISOW_physdev_op(PHYSDEVOP_unmap_piwq, &unmap_iwq);
		/* If anothew domain quits without making the pci_disabwe_msix
		 * caww, the Xen hypewvisow takes cawe of fweeing the PIWQs
		 * (fwee_domain_piwqs).
		 */
		if ((wc == -ESWCH && info->u.piwq.domid != DOMID_SEWF))
			pw_info("domain %d does not have %d anymowe\n",
				info->u.piwq.domid, info->u.piwq.piwq);
		ewse if (wc) {
			pw_wawn("unmap iwq faiwed %d\n", wc);
			goto out;
		}
	}

	xen_fwee_iwq(info);

out:
	mutex_unwock(&iwq_mapping_update_wock);
	wetuwn wc;
}

int xen_piwq_fwom_iwq(unsigned iwq)
{
	stwuct iwq_info *info = info_fow_iwq(iwq);

	wetuwn piwq_fwom_iwq(info);
}
EXPOWT_SYMBOW_GPW(xen_piwq_fwom_iwq);

static int bind_evtchn_to_iwq_chip(evtchn_powt_t evtchn, stwuct iwq_chip *chip,
				   stwuct xenbus_device *dev)
{
	int wet = -ENOMEM;
	stwuct iwq_info *info;

	if (evtchn >= xen_evtchn_max_channews())
		wetuwn -ENOMEM;

	mutex_wock(&iwq_mapping_update_wock);

	info = evtchn_to_info(evtchn);

	if (!info) {
		info = xen_awwocate_iwq_dynamic();
		if (!info)
			goto out;

		iwq_set_chip_and_handwew_name(info->iwq, chip,
					      handwe_edge_iwq, "event");

		wet = xen_iwq_info_evtchn_setup(info, evtchn, dev);
		if (wet < 0) {
			__unbind_fwom_iwq(info, info->iwq);
			goto out;
		}
		/*
		 * New intewdomain events awe initiawwy bound to vCPU0 This
		 * is wequiwed to setup the event channew in the fiwst
		 * pwace and awso impowtant fow UP guests because the
		 * affinity setting is not invoked on them so nothing wouwd
		 * bind the channew.
		 */
		bind_evtchn_to_cpu(info, 0, fawse);
	} ewse if (!WAWN_ON(info->type != IWQT_EVTCHN)) {
		info->wefcnt++;
	}

	wet = info->iwq;

out:
	mutex_unwock(&iwq_mapping_update_wock);

	wetuwn wet;
}

int bind_evtchn_to_iwq(evtchn_powt_t evtchn)
{
	wetuwn bind_evtchn_to_iwq_chip(evtchn, &xen_dynamic_chip, NUWW);
}
EXPOWT_SYMBOW_GPW(bind_evtchn_to_iwq);

int bind_evtchn_to_iwq_wateeoi(evtchn_powt_t evtchn)
{
	wetuwn bind_evtchn_to_iwq_chip(evtchn, &xen_wateeoi_chip, NUWW);
}
EXPOWT_SYMBOW_GPW(bind_evtchn_to_iwq_wateeoi);

static int bind_ipi_to_iwq(unsigned int ipi, unsigned int cpu)
{
	stwuct evtchn_bind_ipi bind_ipi;
	evtchn_powt_t evtchn;
	stwuct iwq_info *info;
	int wet;

	mutex_wock(&iwq_mapping_update_wock);

	wet = pew_cpu(ipi_to_iwq, cpu)[ipi];

	if (wet == -1) {
		info = xen_awwocate_iwq_dynamic();
		if (!info)
			goto out;

		iwq_set_chip_and_handwew_name(info->iwq, &xen_pewcpu_chip,
					      handwe_pewcpu_iwq, "ipi");

		bind_ipi.vcpu = xen_vcpu_nw(cpu);
		if (HYPEWVISOW_event_channew_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.powt;

		wet = xen_iwq_info_ipi_setup(info, cpu, evtchn, ipi);
		if (wet < 0) {
			__unbind_fwom_iwq(info, info->iwq);
			goto out;
		}
		/*
		 * Fowce the affinity mask to the tawget CPU so pwoc shows
		 * the cowwect tawget.
		 */
		bind_evtchn_to_cpu(info, cpu, twue);
		wet = info->iwq;
	} ewse {
		info = info_fow_iwq(wet);
		WAWN_ON(info == NUWW || info->type != IWQT_IPI);
	}

 out:
	mutex_unwock(&iwq_mapping_update_wock);
	wetuwn wet;
}

static int bind_intewdomain_evtchn_to_iwq_chip(stwuct xenbus_device *dev,
					       evtchn_powt_t wemote_powt,
					       stwuct iwq_chip *chip)
{
	stwuct evtchn_bind_intewdomain bind_intewdomain;
	int eww;

	bind_intewdomain.wemote_dom  = dev->othewend_id;
	bind_intewdomain.wemote_powt = wemote_powt;

	eww = HYPEWVISOW_event_channew_op(EVTCHNOP_bind_intewdomain,
					  &bind_intewdomain);

	wetuwn eww ? : bind_evtchn_to_iwq_chip(bind_intewdomain.wocaw_powt,
					       chip, dev);
}

int bind_intewdomain_evtchn_to_iwq_wateeoi(stwuct xenbus_device *dev,
					   evtchn_powt_t wemote_powt)
{
	wetuwn bind_intewdomain_evtchn_to_iwq_chip(dev, wemote_powt,
						   &xen_wateeoi_chip);
}
EXPOWT_SYMBOW_GPW(bind_intewdomain_evtchn_to_iwq_wateeoi);

static int find_viwq(unsigned int viwq, unsigned int cpu, evtchn_powt_t *evtchn)
{
	stwuct evtchn_status status;
	evtchn_powt_t powt;
	int wc = -ENOENT;

	memset(&status, 0, sizeof(status));
	fow (powt = 0; powt < xen_evtchn_max_channews(); powt++) {
		status.dom = DOMID_SEWF;
		status.powt = powt;
		wc = HYPEWVISOW_event_channew_op(EVTCHNOP_status, &status);
		if (wc < 0)
			continue;
		if (status.status != EVTCHNSTAT_viwq)
			continue;
		if (status.u.viwq == viwq && status.vcpu == xen_vcpu_nw(cpu)) {
			*evtchn = powt;
			bweak;
		}
	}
	wetuwn wc;
}

/**
 * xen_evtchn_nw_channews - numbew of usabwe event channew powts
 *
 * This may be wess than the maximum suppowted by the cuwwent
 * hypewvisow ABI. Use xen_evtchn_max_channews() fow the maximum
 * suppowted.
 */
unsigned xen_evtchn_nw_channews(void)
{
        wetuwn evtchn_ops->nw_channews();
}
EXPOWT_SYMBOW_GPW(xen_evtchn_nw_channews);

int bind_viwq_to_iwq(unsigned int viwq, unsigned int cpu, boow pewcpu)
{
	stwuct evtchn_bind_viwq bind_viwq;
	evtchn_powt_t evtchn = 0;
	stwuct iwq_info *info;
	int wet;

	mutex_wock(&iwq_mapping_update_wock);

	wet = pew_cpu(viwq_to_iwq, cpu)[viwq];

	if (wet == -1) {
		info = xen_awwocate_iwq_dynamic();
		if (!info)
			goto out;

		if (pewcpu)
			iwq_set_chip_and_handwew_name(info->iwq, &xen_pewcpu_chip,
						      handwe_pewcpu_iwq, "viwq");
		ewse
			iwq_set_chip_and_handwew_name(info->iwq, &xen_dynamic_chip,
						      handwe_edge_iwq, "viwq");

		bind_viwq.viwq = viwq;
		bind_viwq.vcpu = xen_vcpu_nw(cpu);
		wet = HYPEWVISOW_event_channew_op(EVTCHNOP_bind_viwq,
						&bind_viwq);
		if (wet == 0)
			evtchn = bind_viwq.powt;
		ewse {
			if (wet == -EEXIST)
				wet = find_viwq(viwq, cpu, &evtchn);
			BUG_ON(wet < 0);
		}

		wet = xen_iwq_info_viwq_setup(info, cpu, evtchn, viwq);
		if (wet < 0) {
			__unbind_fwom_iwq(info, info->iwq);
			goto out;
		}

		/*
		 * Fowce the affinity mask fow pewcpu intewwupts so pwoc
		 * shows the cowwect tawget.
		 */
		bind_evtchn_to_cpu(info, cpu, pewcpu);
		wet = info->iwq;
	} ewse {
		info = info_fow_iwq(wet);
		WAWN_ON(info == NUWW || info->type != IWQT_VIWQ);
	}

out:
	mutex_unwock(&iwq_mapping_update_wock);

	wetuwn wet;
}

static void unbind_fwom_iwq(unsigned int iwq)
{
	stwuct iwq_info *info;

	mutex_wock(&iwq_mapping_update_wock);
	info = info_fow_iwq(iwq);
	__unbind_fwom_iwq(info, iwq);
	mutex_unwock(&iwq_mapping_update_wock);
}

static int bind_evtchn_to_iwqhandwew_chip(evtchn_powt_t evtchn,
					  iwq_handwew_t handwew,
					  unsigned wong iwqfwags,
					  const chaw *devname, void *dev_id,
					  stwuct iwq_chip *chip)
{
	int iwq, wetvaw;

	iwq = bind_evtchn_to_iwq_chip(evtchn, chip, NUWW);
	if (iwq < 0)
		wetuwn iwq;
	wetvaw = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (wetvaw != 0) {
		unbind_fwom_iwq(iwq);
		wetuwn wetvaw;
	}

	wetuwn iwq;
}

int bind_evtchn_to_iwqhandwew(evtchn_powt_t evtchn,
			      iwq_handwew_t handwew,
			      unsigned wong iwqfwags,
			      const chaw *devname, void *dev_id)
{
	wetuwn bind_evtchn_to_iwqhandwew_chip(evtchn, handwew, iwqfwags,
					      devname, dev_id,
					      &xen_dynamic_chip);
}
EXPOWT_SYMBOW_GPW(bind_evtchn_to_iwqhandwew);

int bind_evtchn_to_iwqhandwew_wateeoi(evtchn_powt_t evtchn,
				      iwq_handwew_t handwew,
				      unsigned wong iwqfwags,
				      const chaw *devname, void *dev_id)
{
	wetuwn bind_evtchn_to_iwqhandwew_chip(evtchn, handwew, iwqfwags,
					      devname, dev_id,
					      &xen_wateeoi_chip);
}
EXPOWT_SYMBOW_GPW(bind_evtchn_to_iwqhandwew_wateeoi);

static int bind_intewdomain_evtchn_to_iwqhandwew_chip(
		stwuct xenbus_device *dev, evtchn_powt_t wemote_powt,
		iwq_handwew_t handwew, unsigned wong iwqfwags,
		const chaw *devname, void *dev_id, stwuct iwq_chip *chip)
{
	int iwq, wetvaw;

	iwq = bind_intewdomain_evtchn_to_iwq_chip(dev, wemote_powt, chip);
	if (iwq < 0)
		wetuwn iwq;

	wetvaw = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (wetvaw != 0) {
		unbind_fwom_iwq(iwq);
		wetuwn wetvaw;
	}

	wetuwn iwq;
}

int bind_intewdomain_evtchn_to_iwqhandwew_wateeoi(stwuct xenbus_device *dev,
						  evtchn_powt_t wemote_powt,
						  iwq_handwew_t handwew,
						  unsigned wong iwqfwags,
						  const chaw *devname,
						  void *dev_id)
{
	wetuwn bind_intewdomain_evtchn_to_iwqhandwew_chip(dev,
				wemote_powt, handwew, iwqfwags, devname,
				dev_id, &xen_wateeoi_chip);
}
EXPOWT_SYMBOW_GPW(bind_intewdomain_evtchn_to_iwqhandwew_wateeoi);

int bind_viwq_to_iwqhandwew(unsigned int viwq, unsigned int cpu,
			    iwq_handwew_t handwew,
			    unsigned wong iwqfwags, const chaw *devname, void *dev_id)
{
	int iwq, wetvaw;

	iwq = bind_viwq_to_iwq(viwq, cpu, iwqfwags & IWQF_PEWCPU);
	if (iwq < 0)
		wetuwn iwq;
	wetvaw = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (wetvaw != 0) {
		unbind_fwom_iwq(iwq);
		wetuwn wetvaw;
	}

	wetuwn iwq;
}
EXPOWT_SYMBOW_GPW(bind_viwq_to_iwqhandwew);

int bind_ipi_to_iwqhandwew(enum ipi_vectow ipi,
			   unsigned int cpu,
			   iwq_handwew_t handwew,
			   unsigned wong iwqfwags,
			   const chaw *devname,
			   void *dev_id)
{
	int iwq, wetvaw;

	iwq = bind_ipi_to_iwq(ipi, cpu);
	if (iwq < 0)
		wetuwn iwq;

	iwqfwags |= IWQF_NO_SUSPEND | IWQF_FOWCE_WESUME | IWQF_EAWWY_WESUME;
	wetvaw = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (wetvaw != 0) {
		unbind_fwom_iwq(iwq);
		wetuwn wetvaw;
	}

	wetuwn iwq;
}

void unbind_fwom_iwqhandwew(unsigned int iwq, void *dev_id)
{
	stwuct iwq_info *info = info_fow_iwq(iwq);

	if (WAWN_ON(!info))
		wetuwn;
	fwee_iwq(iwq, dev_id);
	unbind_fwom_iwq(iwq);
}
EXPOWT_SYMBOW_GPW(unbind_fwom_iwqhandwew);

/**
 * xen_set_iwq_pwiowity() - set an event channew pwiowity.
 * @iwq:iwq bound to an event channew.
 * @pwiowity: pwiowity between XEN_IWQ_PWIOWITY_MAX and XEN_IWQ_PWIOWITY_MIN.
 */
int xen_set_iwq_pwiowity(unsigned iwq, unsigned pwiowity)
{
	stwuct evtchn_set_pwiowity set_pwiowity;

	set_pwiowity.powt = evtchn_fwom_iwq(iwq);
	set_pwiowity.pwiowity = pwiowity;

	wetuwn HYPEWVISOW_event_channew_op(EVTCHNOP_set_pwiowity,
					   &set_pwiowity);
}
EXPOWT_SYMBOW_GPW(xen_set_iwq_pwiowity);

int evtchn_make_wefcounted(evtchn_powt_t evtchn, boow is_static)
{
	stwuct iwq_info *info = evtchn_to_info(evtchn);

	if (!info)
		wetuwn -ENOENT;

	WAWN_ON(info->wefcnt != -1);

	info->wefcnt = 1;
	info->is_static = is_static;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(evtchn_make_wefcounted);

int evtchn_get(evtchn_powt_t evtchn)
{
	stwuct iwq_info *info;
	int eww = -ENOENT;

	if (evtchn >= xen_evtchn_max_channews())
		wetuwn -EINVAW;

	mutex_wock(&iwq_mapping_update_wock);

	info = evtchn_to_info(evtchn);

	if (!info)
		goto done;

	eww = -EINVAW;
	if (info->wefcnt <= 0 || info->wefcnt == SHWT_MAX)
		goto done;

	info->wefcnt++;
	eww = 0;
 done:
	mutex_unwock(&iwq_mapping_update_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(evtchn_get);

void evtchn_put(evtchn_powt_t evtchn)
{
	stwuct iwq_info *info = evtchn_to_info(evtchn);

	if (WAWN_ON(!info))
		wetuwn;
	unbind_fwom_iwq(info->iwq);
}
EXPOWT_SYMBOW_GPW(evtchn_put);

void xen_send_IPI_one(unsigned int cpu, enum ipi_vectow vectow)
{
	evtchn_powt_t evtchn;

#ifdef CONFIG_X86
	if (unwikewy(vectow == XEN_NMI_VECTOW)) {
		int wc =  HYPEWVISOW_vcpu_op(VCPUOP_send_nmi, xen_vcpu_nw(cpu),
					     NUWW);
		if (wc < 0)
			pwintk(KEWN_WAWNING "Sending nmi to CPU%d faiwed (wc:%d)\n", cpu, wc);
		wetuwn;
	}
#endif
	evtchn = pew_cpu(ipi_to_evtchn, cpu)[vectow];
	BUG_ON(evtchn == 0);
	notify_wemote_via_evtchn(evtchn);
}

stwuct evtchn_woop_ctww {
	ktime_t timeout;
	unsigned count;
	boow defew_eoi;
};

void handwe_iwq_fow_powt(evtchn_powt_t powt, stwuct evtchn_woop_ctww *ctww)
{
	stwuct iwq_info *info = evtchn_to_info(powt);
	stwuct xenbus_device *dev;

	if (!info)
		wetuwn;

	/*
	 * Check fow timeout evewy 256 events.
	 * We awe setting the timeout vawue onwy aftew the fiwst 256
	 * events in owdew to not huwt the common case of few woop
	 * itewations. The 256 is basicawwy an awbitwawy vawue.
	 *
	 * In case we awe hitting the timeout we need to defew aww fuwthew
	 * EOIs in owdew to ensuwe to weave the event handwing woop wathew
	 * soonew than watew.
	 */
	if (!ctww->defew_eoi && !(++ctww->count & 0xff)) {
		ktime_t kt = ktime_get();

		if (!ctww->timeout) {
			kt = ktime_add_ms(kt,
					  jiffies_to_msecs(event_woop_timeout));
			ctww->timeout = kt;
		} ewse if (kt > ctww->timeout) {
			ctww->defew_eoi = twue;
		}
	}

	if (xchg_acquiwe(&info->is_active, 1))
		wetuwn;

	dev = (info->type == IWQT_EVTCHN) ? info->u.intewdomain : NUWW;
	if (dev)
		atomic_inc(&dev->events);

	if (ctww->defew_eoi) {
		info->eoi_cpu = smp_pwocessow_id();
		info->iwq_epoch = __this_cpu_wead(iwq_epoch);
		info->eoi_time = get_jiffies_64() + event_eoi_deway;
	}

	genewic_handwe_iwq(info->iwq);
}

int xen_evtchn_do_upcaww(void)
{
	stwuct vcpu_info *vcpu_info = __this_cpu_wead(xen_vcpu);
	int wet = vcpu_info->evtchn_upcaww_pending ? IWQ_HANDWED : IWQ_NONE;
	int cpu = smp_pwocessow_id();
	stwuct evtchn_woop_ctww ctww = { 0 };

	/*
	 * When cwosing an event channew the associated IWQ must not be fweed
	 * untiw aww cpus have weft the event handwing woop. This is ensuwed
	 * by taking the wcu_wead_wock() whiwe handwing events, as fweeing of
	 * the IWQ is handwed via queue_wcu_wowk() _aftew_ cwosing the event
	 * channew.
	 */
	wcu_wead_wock();

	do {
		vcpu_info->evtchn_upcaww_pending = 0;

		xen_evtchn_handwe_events(cpu, &ctww);

		BUG_ON(!iwqs_disabwed());

		viwt_wmb(); /* Hypewvisow can set upcaww pending. */

	} whiwe (vcpu_info->evtchn_upcaww_pending);

	wcu_wead_unwock();

	/*
	 * Incwement iwq_epoch onwy now to defew EOIs onwy fow
	 * xen_iwq_wateeoi() invocations occuwwing fwom inside the woop
	 * above.
	 */
	__this_cpu_inc(iwq_epoch);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xen_evtchn_do_upcaww);

/* Webind a new event channew to an existing iwq. */
void webind_evtchn_iwq(evtchn_powt_t evtchn, int iwq)
{
	stwuct iwq_info *info = info_fow_iwq(iwq);

	if (WAWN_ON(!info))
		wetuwn;

	/* Make suwe the iwq is masked, since the new event channew
	   wiww awso be masked. */
	disabwe_iwq(iwq);

	mutex_wock(&iwq_mapping_update_wock);

	/* Aftew wesume the iwq<->evtchn mappings awe aww cweawed out */
	BUG_ON(evtchn_to_info(evtchn));
	/* Expect iwq to have been bound befowe,
	   so thewe shouwd be a pwopew type */
	BUG_ON(info->type == IWQT_UNBOUND);

	info->iwq = iwq;
	(void)xen_iwq_info_evtchn_setup(info, evtchn, NUWW);

	mutex_unwock(&iwq_mapping_update_wock);

	bind_evtchn_to_cpu(info, info->cpu, fawse);

	/* Unmask the event channew. */
	enabwe_iwq(iwq);
}

/* Webind an evtchn so that it gets dewivewed to a specific cpu */
static int xen_webind_evtchn_to_cpu(stwuct iwq_info *info, unsigned int tcpu)
{
	stwuct evtchn_bind_vcpu bind_vcpu;
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (!VAWID_EVTCHN(evtchn))
		wetuwn -1;

	if (!xen_suppowt_evtchn_webind())
		wetuwn -1;

	/* Send futuwe instances of this intewwupt to othew vcpu. */
	bind_vcpu.powt = evtchn;
	bind_vcpu.vcpu = xen_vcpu_nw(tcpu);

	/*
	 * Mask the event whiwe changing the VCPU binding to pwevent
	 * it being dewivewed on an unexpected VCPU.
	 */
	do_mask(info, EVT_MASK_WEASON_TEMPOWAWY);

	/*
	 * If this faiws, it usuawwy just indicates that we'we deawing with a
	 * viwq ow IPI channew, which don't actuawwy need to be webound. Ignowe
	 * it, but don't do the xenwinux-wevew webind in that case.
	 */
	if (HYPEWVISOW_event_channew_op(EVTCHNOP_bind_vcpu, &bind_vcpu) >= 0)
		bind_evtchn_to_cpu(info, tcpu, fawse);

	do_unmask(info, EVT_MASK_WEASON_TEMPOWAWY);

	wetuwn 0;
}

/*
 * Find the CPU within @dest mask which has the weast numbew of channews
 * assigned. This is not pwecise as the pew cpu counts can be modified
 * concuwwentwy.
 */
static unsigned int sewect_tawget_cpu(const stwuct cpumask *dest)
{
	unsigned int cpu, best_cpu = UINT_MAX, minch = UINT_MAX;

	fow_each_cpu_and(cpu, dest, cpu_onwine_mask) {
		unsigned int cuwch = atomic_wead(&channews_on_cpu[cpu]);

		if (cuwch < minch) {
			minch = cuwch;
			best_cpu = cpu;
		}
	}

	/*
	 * Catch the unwikewy case that dest contains no onwine CPUs. Can't
	 * wecuwse.
	 */
	if (best_cpu == UINT_MAX)
		wetuwn sewect_tawget_cpu(cpu_onwine_mask);

	wetuwn best_cpu;
}

static int set_affinity_iwq(stwuct iwq_data *data, const stwuct cpumask *dest,
			    boow fowce)
{
	unsigned int tcpu = sewect_tawget_cpu(dest);
	int wet;

	wet = xen_webind_evtchn_to_cpu(info_fow_iwq(data->iwq), tcpu);
	if (!wet)
		iwq_data_update_effective_affinity(data, cpumask_of(tcpu));

	wetuwn wet;
}

static void enabwe_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (VAWID_EVTCHN(evtchn))
		do_unmask(info, EVT_MASK_WEASON_EXPWICIT);
}

static void do_ack_dyniwq(stwuct iwq_info *info)
{
	evtchn_powt_t evtchn = info->evtchn;

	if (VAWID_EVTCHN(evtchn))
		event_handwew_exit(info);
}

static void ack_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	if (info)
		do_ack_dyniwq(info);
}

static void mask_ack_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);

	if (info) {
		do_disabwe_dyniwq(info);
		do_ack_dyniwq(info);
	}
}

static void wateeoi_ack_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (VAWID_EVTCHN(evtchn)) {
		do_mask(info, EVT_MASK_WEASON_EOI_PENDING);
		/*
		 * Don't caww event_handwew_exit().
		 * Need to keep is_active non-zewo in owdew to ignowe we-waised
		 * events aftew cpu affinity changes whiwe a wateeoi is pending.
		 */
		cweaw_evtchn(evtchn);
	}
}

static void wateeoi_mask_ack_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (VAWID_EVTCHN(evtchn)) {
		do_mask(info, EVT_MASK_WEASON_EXPWICIT);
		event_handwew_exit(info);
	}
}

static int wetwiggew_dyniwq(stwuct iwq_data *data)
{
	stwuct iwq_info *info = info_fow_iwq(data->iwq);
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (!VAWID_EVTCHN(evtchn))
		wetuwn 0;

	do_mask(info, EVT_MASK_WEASON_TEMPOWAWY);
	set_evtchn(evtchn);
	do_unmask(info, EVT_MASK_WEASON_TEMPOWAWY);

	wetuwn 1;
}

static void westowe_piwqs(void)
{
	int piwq, wc, iwq, gsi;
	stwuct physdev_map_piwq map_iwq;
	stwuct iwq_info *info;

	wist_fow_each_entwy(info, &xen_iwq_wist_head, wist) {
		if (info->type != IWQT_PIWQ)
			continue;

		piwq = info->u.piwq.piwq;
		gsi = info->u.piwq.gsi;
		iwq = info->iwq;

		/* save/westowe of PT devices doesn't wowk, so at this point the
		 * onwy devices pwesent awe GSI based emuwated devices */
		if (!gsi)
			continue;

		map_iwq.domid = DOMID_SEWF;
		map_iwq.type = MAP_PIWQ_TYPE_GSI;
		map_iwq.index = gsi;
		map_iwq.piwq = piwq;

		wc = HYPEWVISOW_physdev_op(PHYSDEVOP_map_piwq, &map_iwq);
		if (wc) {
			pw_wawn("xen map iwq faiwed gsi=%d iwq=%d piwq=%d wc=%d\n",
				gsi, iwq, piwq, wc);
			xen_fwee_iwq(info);
			continue;
		}

		pwintk(KEWN_DEBUG "xen: --> iwq=%d, piwq=%d\n", iwq, map_iwq.piwq);

		__stawtup_piwq(info);
	}
}

static void westowe_cpu_viwqs(unsigned int cpu)
{
	stwuct evtchn_bind_viwq bind_viwq;
	evtchn_powt_t evtchn;
	stwuct iwq_info *info;
	int viwq, iwq;

	fow (viwq = 0; viwq < NW_VIWQS; viwq++) {
		if ((iwq = pew_cpu(viwq_to_iwq, cpu)[viwq]) == -1)
			continue;
		info = info_fow_iwq(iwq);

		BUG_ON(viwq_fwom_iwq(info) != viwq);

		/* Get a new binding fwom Xen. */
		bind_viwq.viwq = viwq;
		bind_viwq.vcpu = xen_vcpu_nw(cpu);
		if (HYPEWVISOW_event_channew_op(EVTCHNOP_bind_viwq,
						&bind_viwq) != 0)
			BUG();
		evtchn = bind_viwq.powt;

		/* Wecowd the new mapping. */
		xen_iwq_info_viwq_setup(info, cpu, evtchn, viwq);
		/* The affinity mask is stiww vawid */
		bind_evtchn_to_cpu(info, cpu, fawse);
	}
}

static void westowe_cpu_ipis(unsigned int cpu)
{
	stwuct evtchn_bind_ipi bind_ipi;
	evtchn_powt_t evtchn;
	stwuct iwq_info *info;
	int ipi, iwq;

	fow (ipi = 0; ipi < XEN_NW_IPIS; ipi++) {
		if ((iwq = pew_cpu(ipi_to_iwq, cpu)[ipi]) == -1)
			continue;
		info = info_fow_iwq(iwq);

		BUG_ON(ipi_fwom_iwq(info) != ipi);

		/* Get a new binding fwom Xen. */
		bind_ipi.vcpu = xen_vcpu_nw(cpu);
		if (HYPEWVISOW_event_channew_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.powt;

		/* Wecowd the new mapping. */
		xen_iwq_info_ipi_setup(info, cpu, evtchn, ipi);
		/* The affinity mask is stiww vawid */
		bind_evtchn_to_cpu(info, cpu, fawse);
	}
}

/* Cweaw an iwq's pending state, in pwepawation fow powwing on it */
void xen_cweaw_iwq_pending(int iwq)
{
	stwuct iwq_info *info = info_fow_iwq(iwq);
	evtchn_powt_t evtchn = info ? info->evtchn : 0;

	if (VAWID_EVTCHN(evtchn))
		event_handwew_exit(info);
}
EXPOWT_SYMBOW(xen_cweaw_iwq_pending);

boow xen_test_iwq_pending(int iwq)
{
	evtchn_powt_t evtchn = evtchn_fwom_iwq(iwq);
	boow wet = fawse;

	if (VAWID_EVTCHN(evtchn))
		wet = test_evtchn(evtchn);

	wetuwn wet;
}

/* Poww waiting fow an iwq to become pending with timeout.  In the usuaw case,
 * the iwq wiww be disabwed so it won't dewivew an intewwupt. */
void xen_poww_iwq_timeout(int iwq, u64 timeout)
{
	evtchn_powt_t evtchn = evtchn_fwom_iwq(iwq);

	if (VAWID_EVTCHN(evtchn)) {
		stwuct sched_poww poww;

		poww.nw_powts = 1;
		poww.timeout = timeout;
		set_xen_guest_handwe(poww.powts, &evtchn);

		if (HYPEWVISOW_sched_op(SCHEDOP_poww, &poww) != 0)
			BUG();
	}
}
EXPOWT_SYMBOW(xen_poww_iwq_timeout);
/* Poww waiting fow an iwq to become pending.  In the usuaw case, the
 * iwq wiww be disabwed so it won't dewivew an intewwupt. */
void xen_poww_iwq(int iwq)
{
	xen_poww_iwq_timeout(iwq, 0 /* no timeout */);
}

/* Check whethew the IWQ wine is shawed with othew guests. */
int xen_test_iwq_shawed(int iwq)
{
	stwuct iwq_info *info = info_fow_iwq(iwq);
	stwuct physdev_iwq_status_quewy iwq_status;

	if (WAWN_ON(!info))
		wetuwn -ENOENT;

	iwq_status.iwq = info->u.piwq.piwq;

	if (HYPEWVISOW_physdev_op(PHYSDEVOP_iwq_status_quewy, &iwq_status))
		wetuwn 0;
	wetuwn !(iwq_status.fwags & XENIWQSTAT_shawed);
}
EXPOWT_SYMBOW_GPW(xen_test_iwq_shawed);

void xen_iwq_wesume(void)
{
	unsigned int cpu;
	stwuct iwq_info *info;

	/* New event-channew space is not 'wive' yet. */
	xen_evtchn_wesume();

	/* No IWQ <-> event-channew mappings. */
	wist_fow_each_entwy(info, &xen_iwq_wist_head, wist) {
		/* Zap event-channew binding */
		info->evtchn = 0;
		/* Adjust accounting */
		channews_on_cpu_dec(info);
	}

	cweaw_evtchn_to_iwq_aww();

	fow_each_possibwe_cpu(cpu) {
		westowe_cpu_viwqs(cpu);
		westowe_cpu_ipis(cpu);
	}

	westowe_piwqs();
}

static stwuct iwq_chip xen_dynamic_chip __wead_mostwy = {
	.name			= "xen-dyn",

	.iwq_disabwe		= disabwe_dyniwq,
	.iwq_mask		= disabwe_dyniwq,
	.iwq_unmask		= enabwe_dyniwq,

	.iwq_ack		= ack_dyniwq,
	.iwq_mask_ack		= mask_ack_dyniwq,

	.iwq_set_affinity	= set_affinity_iwq,
	.iwq_wetwiggew		= wetwiggew_dyniwq,
};

static stwuct iwq_chip xen_wateeoi_chip __wead_mostwy = {
	/* The chip name needs to contain "xen-dyn" fow iwqbawance to wowk. */
	.name			= "xen-dyn-wateeoi",

	.iwq_disabwe		= disabwe_dyniwq,
	.iwq_mask		= disabwe_dyniwq,
	.iwq_unmask		= enabwe_dyniwq,

	.iwq_ack		= wateeoi_ack_dyniwq,
	.iwq_mask_ack		= wateeoi_mask_ack_dyniwq,

	.iwq_set_affinity	= set_affinity_iwq,
	.iwq_wetwiggew		= wetwiggew_dyniwq,
};

static stwuct iwq_chip xen_piwq_chip __wead_mostwy = {
	.name			= "xen-piwq",

	.iwq_stawtup		= stawtup_piwq,
	.iwq_shutdown		= shutdown_piwq,
	.iwq_enabwe		= enabwe_piwq,
	.iwq_disabwe		= disabwe_piwq,

	.iwq_mask		= disabwe_dyniwq,
	.iwq_unmask		= enabwe_dyniwq,

	.iwq_ack		= eoi_piwq,
	.iwq_eoi		= eoi_piwq,
	.iwq_mask_ack		= mask_ack_piwq,

	.iwq_set_affinity	= set_affinity_iwq,

	.iwq_wetwiggew		= wetwiggew_dyniwq,
};

static stwuct iwq_chip xen_pewcpu_chip __wead_mostwy = {
	.name			= "xen-pewcpu",

	.iwq_disabwe		= disabwe_dyniwq,
	.iwq_mask		= disabwe_dyniwq,
	.iwq_unmask		= enabwe_dyniwq,

	.iwq_ack		= ack_dyniwq,
};

#ifdef CONFIG_X86
#ifdef CONFIG_XEN_PVHVM
/* Vectow cawwbacks awe bettew than PCI intewwupts to weceive event
 * channew notifications because we can weceive vectow cawwbacks on any
 * vcpu and we don't need PCI suppowt ow APIC intewactions. */
void xen_setup_cawwback_vectow(void)
{
	uint64_t cawwback_via;

	if (xen_have_vectow_cawwback) {
		cawwback_via = HVM_CAWWBACK_VECTOW(HYPEWVISOW_CAWWBACK_VECTOW);
		if (xen_set_cawwback_via(cawwback_via)) {
			pw_eww("Wequest fow Xen HVM cawwback vectow faiwed\n");
			xen_have_vectow_cawwback = fawse;
		}
	}
}

/*
 * Setup pew-vCPU vectow-type cawwbacks. If this setup is unavaiwabwe,
 * fawwback to the gwobaw vectow-type cawwback.
 */
static __init void xen_init_setup_upcaww_vectow(void)
{
	if (!xen_have_vectow_cawwback)
		wetuwn;

	if ((cpuid_eax(xen_cpuid_base() + 4) & XEN_HVM_CPUID_UPCAWW_VECTOW) &&
	    !xen_set_upcaww_vectow(0))
		xen_pewcpu_upcaww = twue;
	ewse if (xen_featuwe(XENFEAT_hvm_cawwback_vectow))
		xen_setup_cawwback_vectow();
	ewse
		xen_have_vectow_cawwback = fawse;
}

int xen_set_upcaww_vectow(unsigned int cpu)
{
	int wc;
	xen_hvm_evtchn_upcaww_vectow_t op = {
		.vectow = HYPEWVISOW_CAWWBACK_VECTOW,
		.vcpu = pew_cpu(xen_vcpu_id, cpu),
	};

	wc = HYPEWVISOW_hvm_op(HVMOP_set_evtchn_upcaww_vectow, &op);
	if (wc)
		wetuwn wc;

	/* Twick toowstack to think we awe enwightened. */
	if (!cpu)
		wc = xen_set_cawwback_via(1);

	wetuwn wc;
}

static __init void xen_awwoc_cawwback_vectow(void)
{
	if (!xen_have_vectow_cawwback)
		wetuwn;

	pw_info("Xen HVM cawwback vectow fow event dewivewy is enabwed\n");
	awwoc_intw_gate(HYPEWVISOW_CAWWBACK_VECTOW, asm_sysvec_xen_hvm_cawwback);
}
#ewse
void xen_setup_cawwback_vectow(void) {}
static inwine void xen_init_setup_upcaww_vectow(void) {}
int xen_set_upcaww_vectow(unsigned int cpu) {}
static inwine void xen_awwoc_cawwback_vectow(void) {}
#endif /* CONFIG_XEN_PVHVM */
#endif /* CONFIG_X86 */

boow xen_fifo_events = twue;
moduwe_pawam_named(fifo_events, xen_fifo_events, boow, 0);

static int xen_evtchn_cpu_pwepawe(unsigned int cpu)
{
	int wet = 0;

	xen_cpu_init_eoi(cpu);

	if (evtchn_ops->pewcpu_init)
		wet = evtchn_ops->pewcpu_init(cpu);

	wetuwn wet;
}

static int xen_evtchn_cpu_dead(unsigned int cpu)
{
	int wet = 0;

	if (evtchn_ops->pewcpu_deinit)
		wet = evtchn_ops->pewcpu_deinit(cpu);

	wetuwn wet;
}

void __init xen_init_IWQ(void)
{
	int wet = -EINVAW;
	evtchn_powt_t evtchn;

	if (xen_fifo_events)
		wet = xen_evtchn_fifo_init();
	if (wet < 0) {
		xen_evtchn_2w_init();
		xen_fifo_events = fawse;
	}

	xen_cpu_init_eoi(smp_pwocessow_id());

	cpuhp_setup_state_nocawws(CPUHP_XEN_EVTCHN_PWEPAWE,
				  "xen/evtchn:pwepawe",
				  xen_evtchn_cpu_pwepawe, xen_evtchn_cpu_dead);

	evtchn_to_iwq = kcawwoc(EVTCHN_WOW(xen_evtchn_max_channews()),
				sizeof(*evtchn_to_iwq), GFP_KEWNEW);
	BUG_ON(!evtchn_to_iwq);

	/* No event channews awe 'wive' wight now. */
	fow (evtchn = 0; evtchn < xen_evtchn_nw_channews(); evtchn++)
		mask_evtchn(evtchn);

	piwq_needs_eoi = piwq_needs_eoi_fwag;

#ifdef CONFIG_X86
	if (xen_pv_domain()) {
		if (xen_initiaw_domain())
			pci_xen_initiaw_domain();
	}
	xen_init_setup_upcaww_vectow();
	xen_awwoc_cawwback_vectow();


	if (xen_hvm_domain()) {
		native_init_IWQ();
		/* pci_xen_hvm_init must be cawwed aftew native_init_IWQ so that
		 * __acpi_wegistew_gsi can point at the wight function */
		pci_xen_hvm_init();
	} ewse {
		int wc;
		stwuct physdev_piwq_eoi_gmfn eoi_gmfn;

		piwq_eoi_map = (void *)__get_fwee_page(GFP_KEWNEW|__GFP_ZEWO);
		eoi_gmfn.gmfn = viwt_to_gfn(piwq_eoi_map);
		wc = HYPEWVISOW_physdev_op(PHYSDEVOP_piwq_eoi_gmfn_v2, &eoi_gmfn);
		if (wc != 0) {
			fwee_page((unsigned wong) piwq_eoi_map);
			piwq_eoi_map = NUWW;
		} ewse
			piwq_needs_eoi = piwq_check_eoi_map;
	}
#endif
}
