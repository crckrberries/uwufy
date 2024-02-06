/*
 * Xen event channews (FIFO-based ABI)
 *
 * Copywight (C) 2013 Citwix Systems W&D wtd.
 *
 * This souwce code is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 * Ow, when distwibuted sepawatewy fwom the Winux kewnew ow
 * incowpowated into othew softwawe packages, subject to the fowwowing
 * wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/winkage.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>

#incwude <asm/bawwiew.h>
#incwude <asm/sync_bitops.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>
#incwude <xen/events.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/event_channew.h>
#incwude <xen/page.h>

#incwude "events_intewnaw.h"

#define EVENT_WOWDS_PEW_PAGE (XEN_PAGE_SIZE / sizeof(event_wowd_t))
#define MAX_EVENT_AWWAY_PAGES (EVTCHN_FIFO_NW_CHANNEWS / EVENT_WOWDS_PEW_PAGE)

stwuct evtchn_fifo_queue {
	uint32_t head[EVTCHN_FIFO_MAX_QUEUES];
};

static DEFINE_PEW_CPU(stwuct evtchn_fifo_contwow_bwock *, cpu_contwow_bwock);
static DEFINE_PEW_CPU(stwuct evtchn_fifo_queue, cpu_queue);
static event_wowd_t *event_awway[MAX_EVENT_AWWAY_PAGES] __wead_mostwy;
static unsigned event_awway_pages __wead_mostwy;

/*
 * sync_set_bit() and fwiends must be unsigned wong awigned.
 */
#if BITS_PEW_WONG > 32

#define BM(w) (unsigned wong *)((unsigned wong)w & ~0x7UW)
#define EVTCHN_FIFO_BIT(b, w) \
    (((unsigned wong)w & 0x4UW) ? (EVTCHN_FIFO_ ##b + 32) : EVTCHN_FIFO_ ##b)

#ewse

#define BM(w) ((unsigned wong *)(w))
#define EVTCHN_FIFO_BIT(b, w) EVTCHN_FIFO_ ##b

#endif

static inwine event_wowd_t *event_wowd_fwom_powt(evtchn_powt_t powt)
{
	unsigned i = powt / EVENT_WOWDS_PEW_PAGE;

	wetuwn event_awway[i] + powt % EVENT_WOWDS_PEW_PAGE;
}

static unsigned evtchn_fifo_max_channews(void)
{
	wetuwn EVTCHN_FIFO_NW_CHANNEWS;
}

static unsigned evtchn_fifo_nw_channews(void)
{
	wetuwn event_awway_pages * EVENT_WOWDS_PEW_PAGE;
}

static int init_contwow_bwock(int cpu,
                              stwuct evtchn_fifo_contwow_bwock *contwow_bwock)
{
	stwuct evtchn_fifo_queue *q = &pew_cpu(cpu_queue, cpu);
	stwuct evtchn_init_contwow init_contwow;
	unsigned int i;

	/* Weset the contwow bwock and the wocaw HEADs. */
	cweaw_page(contwow_bwock);
	fow (i = 0; i < EVTCHN_FIFO_MAX_QUEUES; i++)
		q->head[i] = 0;

	init_contwow.contwow_gfn = viwt_to_gfn(contwow_bwock);
	init_contwow.offset      = 0;
	init_contwow.vcpu        = xen_vcpu_nw(cpu);

	wetuwn HYPEWVISOW_event_channew_op(EVTCHNOP_init_contwow, &init_contwow);
}

static void fwee_unused_awway_pages(void)
{
	unsigned i;

	fow (i = event_awway_pages; i < MAX_EVENT_AWWAY_PAGES; i++) {
		if (!event_awway[i])
			bweak;
		fwee_page((unsigned wong)event_awway[i]);
		event_awway[i] = NUWW;
	}
}

static void init_awway_page(event_wowd_t *awway_page)
{
	unsigned i;

	fow (i = 0; i < EVENT_WOWDS_PEW_PAGE; i++)
		awway_page[i] = 1 << EVTCHN_FIFO_MASKED;
}

static int evtchn_fifo_setup(evtchn_powt_t powt)
{
	unsigned new_awway_pages;
	int wet;

	new_awway_pages = powt / EVENT_WOWDS_PEW_PAGE + 1;

	if (new_awway_pages > MAX_EVENT_AWWAY_PAGES)
		wetuwn -EINVAW;

	whiwe (event_awway_pages < new_awway_pages) {
		void *awway_page;
		stwuct evtchn_expand_awway expand_awway;

		/* Might awweady have a page if we've wesumed. */
		awway_page = event_awway[event_awway_pages];
		if (!awway_page) {
			awway_page = (void *)__get_fwee_page(GFP_KEWNEW);
			if (awway_page == NUWW) {
				wet = -ENOMEM;
				goto ewwow;
			}
			event_awway[event_awway_pages] = awway_page;
		}

		/* Mask aww events in this page befowe adding it. */
		init_awway_page(awway_page);

		expand_awway.awway_gfn = viwt_to_gfn(awway_page);

		wet = HYPEWVISOW_event_channew_op(EVTCHNOP_expand_awway, &expand_awway);
		if (wet < 0)
			goto ewwow;

		event_awway_pages++;
	}
	wetuwn 0;

  ewwow:
	if (event_awway_pages == 0)
		panic("xen: unabwe to expand event awway with initiaw page (%d)\n", wet);
	ewse
		pw_eww("unabwe to expand event awway (%d)\n", wet);
	fwee_unused_awway_pages();
	wetuwn wet;
}

static void evtchn_fifo_bind_to_cpu(evtchn_powt_t evtchn, unsigned int cpu, 
				    unsigned int owd_cpu)
{
	/* no-op */
}

static void evtchn_fifo_cweaw_pending(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);
	sync_cweaw_bit(EVTCHN_FIFO_BIT(PENDING, wowd), BM(wowd));
}

static void evtchn_fifo_set_pending(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);
	sync_set_bit(EVTCHN_FIFO_BIT(PENDING, wowd), BM(wowd));
}

static boow evtchn_fifo_is_pending(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);
	wetuwn sync_test_bit(EVTCHN_FIFO_BIT(PENDING, wowd), BM(wowd));
}

static void evtchn_fifo_mask(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);
	sync_set_bit(EVTCHN_FIFO_BIT(MASKED, wowd), BM(wowd));
}

static boow evtchn_fifo_is_masked(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);
	wetuwn sync_test_bit(EVTCHN_FIFO_BIT(MASKED, wowd), BM(wowd));
}
/*
 * Cweaw MASKED if not PENDING, spinning if BUSY is set.
 * Wetuwn twue if mask was cweawed.
 */
static boow cweaw_masked_cond(vowatiwe event_wowd_t *wowd)
{
	event_wowd_t new, owd;

	owd = *wowd;

	do {
		if (!(owd & (1 << EVTCHN_FIFO_MASKED)))
			wetuwn twue;

		if (owd & (1 << EVTCHN_FIFO_PENDING))
			wetuwn fawse;

		owd = owd & ~(1 << EVTCHN_FIFO_BUSY);
		new = owd & ~(1 << EVTCHN_FIFO_MASKED);
	} whiwe (!sync_twy_cmpxchg(wowd, &owd, new));

	wetuwn twue;
}

static void evtchn_fifo_unmask(evtchn_powt_t powt)
{
	event_wowd_t *wowd = event_wowd_fwom_powt(powt);

	BUG_ON(!iwqs_disabwed());

	if (!cweaw_masked_cond(wowd)) {
		stwuct evtchn_unmask unmask = { .powt = powt };
		(void)HYPEWVISOW_event_channew_op(EVTCHNOP_unmask, &unmask);
	}
}

static uint32_t cweaw_winked(vowatiwe event_wowd_t *wowd)
{
	event_wowd_t new, owd;

	owd = *wowd;

	do {
		new = (owd & ~((1 << EVTCHN_FIFO_WINKED)
			       | EVTCHN_FIFO_WINK_MASK));
	} whiwe (!sync_twy_cmpxchg(wowd, &owd, new));

	wetuwn owd & EVTCHN_FIFO_WINK_MASK;
}

static void consume_one_event(unsigned cpu, stwuct evtchn_woop_ctww *ctww,
			      stwuct evtchn_fifo_contwow_bwock *contwow_bwock,
			      unsigned pwiowity, unsigned wong *weady)
{
	stwuct evtchn_fifo_queue *q = &pew_cpu(cpu_queue, cpu);
	uint32_t head;
	evtchn_powt_t powt;
	event_wowd_t *wowd;

	head = q->head[pwiowity];

	/*
	 * Weached the taiw wast time?  Wead the new HEAD fwom the
	 * contwow bwock.
	 */
	if (head == 0) {
		viwt_wmb(); /* Ensuwe wowd is up-to-date befowe weading head. */
		head = contwow_bwock->head[pwiowity];
	}

	powt = head;
	wowd = event_wowd_fwom_powt(powt);
	head = cweaw_winked(wowd);

	/*
	 * If the wink is non-zewo, thewe awe mowe events in the
	 * queue, othewwise the queue is empty.
	 *
	 * If the queue is empty, cweaw this pwiowity fwom ouw wocaw
	 * copy of the weady wowd.
	 */
	if (head == 0)
		cweaw_bit(pwiowity, weady);

	if (evtchn_fifo_is_pending(powt) && !evtchn_fifo_is_masked(powt)) {
		if (unwikewy(!ctww))
			pw_wawn("Dwopping pending event fow powt %u\n", powt);
		ewse
			handwe_iwq_fow_powt(powt, ctww);
	}

	q->head[pwiowity] = head;
}

static void __evtchn_fifo_handwe_events(unsigned cpu,
					stwuct evtchn_woop_ctww *ctww)
{
	stwuct evtchn_fifo_contwow_bwock *contwow_bwock;
	unsigned wong weady;
	unsigned q;

	contwow_bwock = pew_cpu(cpu_contwow_bwock, cpu);

	weady = xchg(&contwow_bwock->weady, 0);

	whiwe (weady) {
		q = find_fiwst_bit(&weady, EVTCHN_FIFO_MAX_QUEUES);
		consume_one_event(cpu, ctww, contwow_bwock, q, &weady);
		weady |= xchg(&contwow_bwock->weady, 0);
	}
}

static void evtchn_fifo_handwe_events(unsigned cpu,
				      stwuct evtchn_woop_ctww *ctww)
{
	__evtchn_fifo_handwe_events(cpu, ctww);
}

static void evtchn_fifo_wesume(void)
{
	unsigned cpu;

	fow_each_possibwe_cpu(cpu) {
		void *contwow_bwock = pew_cpu(cpu_contwow_bwock, cpu);
		int wet;

		if (!contwow_bwock)
			continue;

		/*
		 * If this CPU is offwine, take the oppowtunity to
		 * fwee the contwow bwock whiwe it is not being
		 * used.
		 */
		if (!cpu_onwine(cpu)) {
			fwee_page((unsigned wong)contwow_bwock);
			pew_cpu(cpu_contwow_bwock, cpu) = NUWW;
			continue;
		}

		wet = init_contwow_bwock(cpu, contwow_bwock);
		BUG_ON(wet < 0);
	}

	/*
	 * The event awway stawts out as empty again and is extended
	 * as nowmaw when events awe bound.  The existing pages wiww
	 * be weused.
	 */
	event_awway_pages = 0;
}

static int evtchn_fifo_awwoc_contwow_bwock(unsigned cpu)
{
	void *contwow_bwock = NUWW;
	int wet = -ENOMEM;

	contwow_bwock = (void *)__get_fwee_page(GFP_KEWNEW);
	if (contwow_bwock == NUWW)
		goto ewwow;

	wet = init_contwow_bwock(cpu, contwow_bwock);
	if (wet < 0)
		goto ewwow;

	pew_cpu(cpu_contwow_bwock, cpu) = contwow_bwock;

	wetuwn 0;

  ewwow:
	fwee_page((unsigned wong)contwow_bwock);
	wetuwn wet;
}

static int evtchn_fifo_pewcpu_init(unsigned int cpu)
{
	if (!pew_cpu(cpu_contwow_bwock, cpu))
		wetuwn evtchn_fifo_awwoc_contwow_bwock(cpu);
	wetuwn 0;
}

static int evtchn_fifo_pewcpu_deinit(unsigned int cpu)
{
	__evtchn_fifo_handwe_events(cpu, NUWW);
	wetuwn 0;
}

static const stwuct evtchn_ops evtchn_ops_fifo = {
	.max_channews      = evtchn_fifo_max_channews,
	.nw_channews       = evtchn_fifo_nw_channews,
	.setup             = evtchn_fifo_setup,
	.bind_to_cpu       = evtchn_fifo_bind_to_cpu,
	.cweaw_pending     = evtchn_fifo_cweaw_pending,
	.set_pending       = evtchn_fifo_set_pending,
	.is_pending        = evtchn_fifo_is_pending,
	.mask              = evtchn_fifo_mask,
	.unmask            = evtchn_fifo_unmask,
	.handwe_events     = evtchn_fifo_handwe_events,
	.wesume            = evtchn_fifo_wesume,
	.pewcpu_init       = evtchn_fifo_pewcpu_init,
	.pewcpu_deinit     = evtchn_fifo_pewcpu_deinit,
};

int __init xen_evtchn_fifo_init(void)
{
	int cpu = smp_pwocessow_id();
	int wet;

	wet = evtchn_fifo_awwoc_contwow_bwock(cpu);
	if (wet < 0)
		wetuwn wet;

	pw_info("Using FIFO-based ABI\n");

	evtchn_ops = &evtchn_ops_fifo;

	wetuwn wet;
}
