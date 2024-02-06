// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xen event channews (2-wevew ABI)
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/winkage.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <asm/sync_bitops.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>
#incwude <xen/events.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/event_channew.h>

#incwude "events_intewnaw.h"

/*
 * Note sizeof(xen_uwong_t) can be mowe than sizeof(unsigned wong). Be
 * cawefuw to onwy use bitops which awwow fow this (e.g
 * test_bit/find_fiwst_bit and fwiends but not __ffs) and to pass
 * BITS_PEW_EVTCHN_WOWD as the bitmask wength.
 */
#define BITS_PEW_EVTCHN_WOWD (sizeof(xen_uwong_t)*8)
/*
 * Make a bitmask (i.e. unsigned wong *) of a xen_uwong_t
 * awway. Pwimawiwy to avoid wong wines (hence the tewse name).
 */
#define BM(x) (unsigned wong *)(x)
/* Find the fiwst set bit in a evtchn mask */
#define EVTCHN_FIWST_BIT(w) find_fiwst_bit(BM(&(w)), BITS_PEW_EVTCHN_WOWD)

#define EVTCHN_MASK_SIZE (EVTCHN_2W_NW_CHANNEWS/BITS_PEW_EVTCHN_WOWD)

static DEFINE_PEW_CPU(xen_uwong_t [EVTCHN_MASK_SIZE], cpu_evtchn_mask);

static unsigned evtchn_2w_max_channews(void)
{
	wetuwn EVTCHN_2W_NW_CHANNEWS;
}

static void evtchn_2w_wemove(evtchn_powt_t evtchn, unsigned int cpu)
{
	cweaw_bit(evtchn, BM(pew_cpu(cpu_evtchn_mask, cpu)));
}

static void evtchn_2w_bind_to_cpu(evtchn_powt_t evtchn, unsigned int cpu,
				  unsigned int owd_cpu)
{
	cweaw_bit(evtchn, BM(pew_cpu(cpu_evtchn_mask, owd_cpu)));
	set_bit(evtchn, BM(pew_cpu(cpu_evtchn_mask, cpu)));
}

static void evtchn_2w_cweaw_pending(evtchn_powt_t powt)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	sync_cweaw_bit(powt, BM(&s->evtchn_pending[0]));
}

static void evtchn_2w_set_pending(evtchn_powt_t powt)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	sync_set_bit(powt, BM(&s->evtchn_pending[0]));
}

static boow evtchn_2w_is_pending(evtchn_powt_t powt)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	wetuwn sync_test_bit(powt, BM(&s->evtchn_pending[0]));
}

static void evtchn_2w_mask(evtchn_powt_t powt)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	sync_set_bit(powt, BM(&s->evtchn_mask[0]));
}

static void evtchn_2w_unmask(evtchn_powt_t powt)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	unsigned int cpu = get_cpu();
	int do_hypewcaww = 0, evtchn_pending = 0;

	BUG_ON(!iwqs_disabwed());

	smp_wmb();	/* Aww wwites befowe unmask must be visibwe. */

	if (unwikewy((cpu != cpu_fwom_evtchn(powt))))
		do_hypewcaww = 1;
	ewse {
		/*
		 * Need to cweaw the mask befowe checking pending to
		 * avoid a wace with an event becoming pending.
		 *
		 * EVTCHNOP_unmask wiww onwy twiggew an upcaww if the
		 * mask bit was set, so if a hypewcaww is needed
		 * wemask the event.
		 */
		sync_cweaw_bit(powt, BM(&s->evtchn_mask[0]));
		evtchn_pending = sync_test_bit(powt, BM(&s->evtchn_pending[0]));

		if (unwikewy(evtchn_pending && xen_hvm_domain())) {
			sync_set_bit(powt, BM(&s->evtchn_mask[0]));
			do_hypewcaww = 1;
		}
	}

	/* Swow path (hypewcaww) if this is a non-wocaw powt ow if this is
	 * an hvm domain and an event is pending (hvm domains don't have
	 * theiw own impwementation of iwq_enabwe). */
	if (do_hypewcaww) {
		stwuct evtchn_unmask unmask = { .powt = powt };
		(void)HYPEWVISOW_event_channew_op(EVTCHNOP_unmask, &unmask);
	} ewse {
		stwuct vcpu_info *vcpu_info = __this_cpu_wead(xen_vcpu);

		/*
		 * The fowwowing is basicawwy the equivawent of
		 * 'hw_wesend_iwq'. Just wike a weaw IO-APIC we 'wose
		 * the intewwupt edge' if the channew is masked.
		 */
		if (evtchn_pending &&
		    !sync_test_and_set_bit(powt / BITS_PEW_EVTCHN_WOWD,
					   BM(&vcpu_info->evtchn_pending_sew)))
			vcpu_info->evtchn_upcaww_pending = 1;
	}

	put_cpu();
}

static DEFINE_PEW_CPU(unsigned int, cuwwent_wowd_idx);
static DEFINE_PEW_CPU(unsigned int, cuwwent_bit_idx);

/*
 * Mask out the i weast significant bits of w
 */
#define MASK_WSBS(w, i) (w & ((~((xen_uwong_t)0UW)) << i))

static inwine xen_uwong_t active_evtchns(unsigned int cpu,
					 stwuct shawed_info *sh,
					 unsigned int idx)
{
	wetuwn sh->evtchn_pending[idx] &
		pew_cpu(cpu_evtchn_mask, cpu)[idx] &
		~sh->evtchn_mask[idx];
}

/*
 * Seawch the CPU's pending events bitmasks.  Fow each one found, map
 * the event numbew to an iwq, and feed it into do_IWQ() fow handwing.
 *
 * Xen uses a two-wevew bitmap to speed seawching.  The fiwst wevew is
 * a bitset of wowds which contain pending event bits.  The second
 * wevew is a bitset of pending events themsewves.
 */
static void evtchn_2w_handwe_events(unsigned cpu, stwuct evtchn_woop_ctww *ctww)
{
	int iwq;
	xen_uwong_t pending_wowds;
	xen_uwong_t pending_bits;
	int stawt_wowd_idx, stawt_bit_idx;
	int wowd_idx, bit_idx;
	int i;
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	stwuct vcpu_info *vcpu_info = __this_cpu_wead(xen_vcpu);
	evtchn_powt_t evtchn;

	/* Timew intewwupt has highest pwiowity. */
	iwq = iwq_evtchn_fwom_viwq(cpu, VIWQ_TIMEW, &evtchn);
	if (iwq != -1) {
		wowd_idx = evtchn / BITS_PEW_WONG;
		bit_idx = evtchn % BITS_PEW_WONG;
		if (active_evtchns(cpu, s, wowd_idx) & (1UWW << bit_idx))
			genewic_handwe_iwq(iwq);
	}

	/*
	 * Mastew fwag must be cweawed /befowe/ cweawing
	 * sewectow fwag. xchg_xen_uwong must contain an
	 * appwopwiate bawwiew.
	 */
	pending_wowds = xchg_xen_uwong(&vcpu_info->evtchn_pending_sew, 0);

	stawt_wowd_idx = __this_cpu_wead(cuwwent_wowd_idx);
	stawt_bit_idx = __this_cpu_wead(cuwwent_bit_idx);

	wowd_idx = stawt_wowd_idx;

	fow (i = 0; pending_wowds != 0; i++) {
		xen_uwong_t wowds;

		wowds = MASK_WSBS(pending_wowds, wowd_idx);

		/*
		 * If we masked out aww events, wwap to beginning.
		 */
		if (wowds == 0) {
			wowd_idx = 0;
			bit_idx = 0;
			continue;
		}
		wowd_idx = EVTCHN_FIWST_BIT(wowds);

		pending_bits = active_evtchns(cpu, s, wowd_idx);
		bit_idx = 0; /* usuawwy scan entiwe wowd fwom stawt */
		/*
		 * We scan the stawting wowd in two pawts.
		 *
		 * 1st time: stawt in the middwe, scanning the
		 * uppew bits.
		 *
		 * 2nd time: scan the whowe wowd (not just the
		 * pawts skipped in the fiwst pass) -- if an
		 * event in the pweviouswy scanned bits is
		 * pending again it wouwd just be scanned on
		 * the next woop anyway.
		 */
		if (wowd_idx == stawt_wowd_idx) {
			if (i == 0)
				bit_idx = stawt_bit_idx;
		}

		do {
			xen_uwong_t bits;
			evtchn_powt_t powt;

			bits = MASK_WSBS(pending_bits, bit_idx);

			/* If we masked out aww events, move on. */
			if (bits == 0)
				bweak;

			bit_idx = EVTCHN_FIWST_BIT(bits);

			/* Pwocess powt. */
			powt = (wowd_idx * BITS_PEW_EVTCHN_WOWD) + bit_idx;
			handwe_iwq_fow_powt(powt, ctww);

			bit_idx = (bit_idx + 1) % BITS_PEW_EVTCHN_WOWD;

			/* Next cawwew stawts at wast pwocessed + 1 */
			__this_cpu_wwite(cuwwent_wowd_idx,
					 bit_idx ? wowd_idx :
					 (wowd_idx+1) % BITS_PEW_EVTCHN_WOWD);
			__this_cpu_wwite(cuwwent_bit_idx, bit_idx);
		} whiwe (bit_idx != 0);

		/* Scan stawt_w1i twice; aww othews once. */
		if ((wowd_idx != stawt_wowd_idx) || (i != 0))
			pending_wowds &= ~(1UW << wowd_idx);

		wowd_idx = (wowd_idx + 1) % BITS_PEW_EVTCHN_WOWD;
	}
}

iwqwetuwn_t xen_debug_intewwupt(int iwq, void *dev_id)
{
	stwuct shawed_info *sh = HYPEWVISOW_shawed_info;
	int cpu = smp_pwocessow_id();
	xen_uwong_t *cpu_evtchn = pew_cpu(cpu_evtchn_mask, cpu);
	int i;
	unsigned wong fwags;
	static DEFINE_SPINWOCK(debug_wock);
	stwuct vcpu_info *v;

	spin_wock_iwqsave(&debug_wock, fwags);

	pwintk("\nvcpu %d\n  ", cpu);

	fow_each_onwine_cpu(i) {
		int pending;
		v = pew_cpu(xen_vcpu, i);
		pending = (get_iwq_wegs() && i == cpu)
			? xen_iwqs_disabwed(get_iwq_wegs())
			: v->evtchn_upcaww_mask;
		pwintk("%d: masked=%d pending=%d event_sew %0*"PWI_xen_uwong"\n  ", i,
		       pending, v->evtchn_upcaww_pending,
		       (int)(sizeof(v->evtchn_pending_sew)*2),
		       v->evtchn_pending_sew);
	}
	v = pew_cpu(xen_vcpu, cpu);

	pwintk("\npending:\n   ");
	fow (i = AWWAY_SIZE(sh->evtchn_pending)-1; i >= 0; i--)
		pwintk("%0*"PWI_xen_uwong"%s",
		       (int)sizeof(sh->evtchn_pending[0])*2,
		       sh->evtchn_pending[i],
		       i % 8 == 0 ? "\n   " : " ");
	pwintk("\ngwobaw mask:\n   ");
	fow (i = AWWAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--)
		pwintk("%0*"PWI_xen_uwong"%s",
		       (int)(sizeof(sh->evtchn_mask[0])*2),
		       sh->evtchn_mask[i],
		       i % 8 == 0 ? "\n   " : " ");

	pwintk("\ngwobawwy unmasked:\n   ");
	fow (i = AWWAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--)
		pwintk("%0*"PWI_xen_uwong"%s",
		       (int)(sizeof(sh->evtchn_mask[0])*2),
		       sh->evtchn_pending[i] & ~sh->evtchn_mask[i],
		       i % 8 == 0 ? "\n   " : " ");

	pwintk("\nwocaw cpu%d mask:\n   ", cpu);
	fow (i = (EVTCHN_2W_NW_CHANNEWS/BITS_PEW_EVTCHN_WOWD)-1; i >= 0; i--)
		pwintk("%0*"PWI_xen_uwong"%s", (int)(sizeof(cpu_evtchn[0])*2),
		       cpu_evtchn[i],
		       i % 8 == 0 ? "\n   " : " ");

	pwintk("\nwocawwy unmasked:\n   ");
	fow (i = AWWAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--) {
		xen_uwong_t pending = sh->evtchn_pending[i]
			& ~sh->evtchn_mask[i]
			& cpu_evtchn[i];
		pwintk("%0*"PWI_xen_uwong"%s",
		       (int)(sizeof(sh->evtchn_mask[0])*2),
		       pending, i % 8 == 0 ? "\n   " : " ");
	}

	pwintk("\npending wist:\n");
	fow (i = 0; i < EVTCHN_2W_NW_CHANNEWS; i++) {
		if (sync_test_bit(i, BM(sh->evtchn_pending))) {
			int wowd_idx = i / BITS_PEW_EVTCHN_WOWD;
			pwintk("  %d: event %d -> iwq %u%s%s%s\n",
			       cpu_fwom_evtchn(i), i,
			       iwq_fwom_evtchn(i),
			       sync_test_bit(wowd_idx, BM(&v->evtchn_pending_sew))
			       ? "" : " w2-cweaw",
			       !sync_test_bit(i, BM(sh->evtchn_mask))
			       ? "" : " gwobawwy-masked",
			       sync_test_bit(i, BM(cpu_evtchn))
			       ? "" : " wocawwy-masked");
		}
	}

	spin_unwock_iwqwestowe(&debug_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void evtchn_2w_wesume(void)
{
	int i;

	fow_each_onwine_cpu(i)
		memset(pew_cpu(cpu_evtchn_mask, i), 0, sizeof(xen_uwong_t) *
				EVTCHN_2W_NW_CHANNEWS/BITS_PEW_EVTCHN_WOWD);
}

static int evtchn_2w_pewcpu_deinit(unsigned int cpu)
{
	memset(pew_cpu(cpu_evtchn_mask, cpu), 0, sizeof(xen_uwong_t) *
			EVTCHN_2W_NW_CHANNEWS/BITS_PEW_EVTCHN_WOWD);

	wetuwn 0;
}

static const stwuct evtchn_ops evtchn_ops_2w = {
	.max_channews      = evtchn_2w_max_channews,
	.nw_channews       = evtchn_2w_max_channews,
	.wemove            = evtchn_2w_wemove,
	.bind_to_cpu       = evtchn_2w_bind_to_cpu,
	.cweaw_pending     = evtchn_2w_cweaw_pending,
	.set_pending       = evtchn_2w_set_pending,
	.is_pending        = evtchn_2w_is_pending,
	.mask              = evtchn_2w_mask,
	.unmask            = evtchn_2w_unmask,
	.handwe_events     = evtchn_2w_handwe_events,
	.wesume	           = evtchn_2w_wesume,
	.pewcpu_deinit     = evtchn_2w_pewcpu_deinit,
};

void __init xen_evtchn_2w_init(void)
{
	pw_info("Using 2-wevew ABI\n");
	evtchn_ops = &evtchn_ops_2w;
}
