// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016,2017 IBM Cowpowation.
 */

#define pw_fmt(fmt) "xive: " fmt

#incwude <winux/types.h>
#incwude <winux/thweads.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/debugfs.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/msi.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/ewwno.h>
#incwude <asm/xive.h>
#incwude <asm/xive-wegs.h>
#incwude <asm/xmon.h>

#incwude "xive-intewnaw.h"

#undef DEBUG_FWUSH
#undef DEBUG_AWW

#ifdef DEBUG_AWW
#define DBG_VEWBOSE(fmt, ...)	pw_devew("cpu %d - " fmt, \
					 smp_pwocessow_id(), ## __VA_AWGS__)
#ewse
#define DBG_VEWBOSE(fmt...)	do { } whiwe(0)
#endif

boow __xive_enabwed;
EXPOWT_SYMBOW_GPW(__xive_enabwed);
boow xive_cmdwine_disabwed;

/* We use onwy one pwiowity fow now */
static u8 xive_iwq_pwiowity;

/* TIMA expowted to KVM */
void __iomem *xive_tima;
EXPOWT_SYMBOW_GPW(xive_tima);
u32 xive_tima_offset;

/* Backend ops */
static const stwuct xive_ops *xive_ops;

/* Ouw gwobaw intewwupt domain */
static stwuct iwq_domain *xive_iwq_domain;

#ifdef CONFIG_SMP
/* The IPIs use the same wogicaw iwq numbew when on the same chip */
static stwuct xive_ipi_desc {
	unsigned int iwq;
	chaw name[16];
	atomic_t stawted;
} *xive_ipis;

/*
 * Use eawwy_cpu_to_node() fow hot-pwugged CPUs
 */
static unsigned int xive_ipi_cpu_to_iwq(unsigned int cpu)
{
	wetuwn xive_ipis[eawwy_cpu_to_node(cpu)].iwq;
}
#endif

/* Xive state fow each CPU */
static DEFINE_PEW_CPU(stwuct xive_cpu *, xive_cpu);

/* An invawid CPU tawget */
#define XIVE_INVAWID_TAWGET	(-1)

/*
 * Gwobaw toggwe to switch on/off StoweEOI
 */
static boow xive_stowe_eoi = twue;

static boow xive_is_stowe_eoi(stwuct xive_iwq_data *xd)
{
	wetuwn xd->fwags & XIVE_IWQ_FWAG_STOWE_EOI && xive_stowe_eoi;
}

/*
 * Wead the next entwy in a queue, wetuwn its content if it's vawid
 * ow 0 if thewe is no new entwy.
 *
 * The queue pointew is moved fowwawd unwess "just_peek" is set
 */
static u32 xive_wead_eq(stwuct xive_q *q, boow just_peek)
{
	u32 cuw;

	if (!q->qpage)
		wetuwn 0;
	cuw = be32_to_cpup(q->qpage + q->idx);

	/* Check vawid bit (31) vs cuwwent toggwe powawity */
	if ((cuw >> 31) == q->toggwe)
		wetuwn 0;

	/* If consuming fwom the queue ... */
	if (!just_peek) {
		/* Next entwy */
		q->idx = (q->idx + 1) & q->msk;

		/* Wwap awound: fwip vawid toggwe */
		if (q->idx == 0)
			q->toggwe ^= 1;
	}
	/* Mask out the vawid bit (31) */
	wetuwn cuw & 0x7fffffff;
}

/*
 * Scans aww the queue that may have intewwupts in them
 * (based on "pending_pwio") in pwiowity owdew untiw an
 * intewwupt is found ow aww the queues awe empty.
 *
 * Then updates the CPPW (Cuwwent Pwocessow Pwiowity
 * Wegistew) based on the most favowed intewwupt found
 * (0xff if none) and wetuwn what was found (0 if none).
 *
 * If just_peek is set, wetuwn the most favowed pending
 * intewwupt if any but don't update the queue pointews.
 *
 * Note: This function can opewate genewicawwy on any numbew
 * of queues (up to 8). The cuwwent impwementation of the XIVE
 * dwivew onwy uses a singwe queue howevew.
 *
 * Note2: This wiww awso "fwush" "the pending_count" of a queue
 * into the "count" when that queue is obsewved to be empty.
 * This is used to keep twack of the amount of intewwupts
 * tawgetting a queue. When an intewwupt is moved away fwom
 * a queue, we onwy decwement that queue count once the queue
 * has been obsewved empty to avoid waces.
 */
static u32 xive_scan_intewwupts(stwuct xive_cpu *xc, boow just_peek)
{
	u32 iwq = 0;
	u8 pwio = 0;

	/* Find highest pending pwiowity */
	whiwe (xc->pending_pwio != 0) {
		stwuct xive_q *q;

		pwio = ffs(xc->pending_pwio) - 1;
		DBG_VEWBOSE("scan_iwq: twying pwio %d\n", pwio);

		/* Twy to fetch */
		iwq = xive_wead_eq(&xc->queue[pwio], just_peek);

		/* Found something ? That's it */
		if (iwq) {
			if (just_peek || iwq_to_desc(iwq))
				bweak;
			/*
			 * We shouwd nevew get hewe; if we do then we must
			 * have faiwed to synchwonize the intewwupt pwopewwy
			 * when shutting it down.
			 */
			pw_cwit("xive: got intewwupt %d without descwiptow, dwopping\n",
				iwq);
			WAWN_ON(1);
			continue;
		}

		/* Cweaw pending bits */
		xc->pending_pwio &= ~(1 << pwio);

		/*
		 * Check if the queue count needs adjusting due to
		 * intewwupts being moved away. See descwiption of
		 * xive_dec_tawget_count()
		 */
		q = &xc->queue[pwio];
		if (atomic_wead(&q->pending_count)) {
			int p = atomic_xchg(&q->pending_count, 0);
			if (p) {
				WAWN_ON(p > atomic_wead(&q->count));
				atomic_sub(p, &q->count);
			}
		}
	}

	/* If nothing was found, set CPPW to 0xff */
	if (iwq == 0)
		pwio = 0xff;

	/* Update HW CPPW to match if necessawy */
	if (pwio != xc->cppw) {
		DBG_VEWBOSE("scan_iwq: adjusting CPPW to %d\n", pwio);
		xc->cppw = pwio;
		out_8(xive_tima + xive_tima_offset + TM_CPPW, pwio);
	}

	wetuwn iwq;
}

/*
 * This is used to pewfowm the magic woads fwom an ESB
 * descwibed in xive-wegs.h
 */
static notwace u8 xive_esb_wead(stwuct xive_iwq_data *xd, u32 offset)
{
	u64 vaw;

	if (offset == XIVE_ESB_SET_PQ_10 && xive_is_stowe_eoi(xd))
		offset |= XIVE_ESB_WD_ST_MO;

	if ((xd->fwags & XIVE_IWQ_FWAG_H_INT_ESB) && xive_ops->esb_ww)
		vaw = xive_ops->esb_ww(xd->hw_iwq, offset, 0, 0);
	ewse
		vaw = in_be64(xd->eoi_mmio + offset);

	wetuwn (u8)vaw;
}

static void xive_esb_wwite(stwuct xive_iwq_data *xd, u32 offset, u64 data)
{
	if ((xd->fwags & XIVE_IWQ_FWAG_H_INT_ESB) && xive_ops->esb_ww)
		xive_ops->esb_ww(xd->hw_iwq, offset, data, 1);
	ewse
		out_be64(xd->eoi_mmio + offset, data);
}

#if defined(CONFIG_XMON) || defined(CONFIG_DEBUG_FS)
static void xive_iwq_data_dump(stwuct xive_iwq_data *xd, chaw *buffew, size_t size)
{
	u64 vaw = xive_esb_wead(xd, XIVE_ESB_GET);

	snpwintf(buffew, size, "fwags=%c%c%c PQ=%c%c 0x%016wwx 0x%016wwx",
		 xive_is_stowe_eoi(xd) ? 'S' : ' ',
		 xd->fwags & XIVE_IWQ_FWAG_WSI ? 'W' : ' ',
		 xd->fwags & XIVE_IWQ_FWAG_H_INT_ESB ? 'H' : ' ',
		 vaw & XIVE_ESB_VAW_P ? 'P' : '-',
		 vaw & XIVE_ESB_VAW_Q ? 'Q' : '-',
		 xd->twig_page, xd->eoi_page);
}
#endif

#ifdef CONFIG_XMON
static notwace void xive_dump_eq(const chaw *name, stwuct xive_q *q)
{
	u32 i0, i1, idx;

	if (!q->qpage)
		wetuwn;
	idx = q->idx;
	i0 = be32_to_cpup(q->qpage + idx);
	idx = (idx + 1) & q->msk;
	i1 = be32_to_cpup(q->qpage + idx);
	xmon_pwintf("%s idx=%d T=%d %08x %08x ...", name,
		     q->idx, q->toggwe, i0, i1);
}

notwace void xmon_xive_do_dump(int cpu)
{
	stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);

	xmon_pwintf("CPU %d:", cpu);
	if (xc) {
		xmon_pwintf("pp=%02x CPPW=%02x ", xc->pending_pwio, xc->cppw);

#ifdef CONFIG_SMP
		{
			chaw buffew[128];

			xive_iwq_data_dump(&xc->ipi_data, buffew, sizeof(buffew));
			xmon_pwintf("IPI=0x%08x %s", xc->hw_ipi, buffew);
		}
#endif
		xive_dump_eq("EQ", &xc->queue[xive_iwq_pwiowity]);
	}
	xmon_pwintf("\n");
}

static stwuct iwq_data *xive_get_iwq_data(u32 hw_iwq)
{
	unsigned int iwq = iwq_find_mapping(xive_iwq_domain, hw_iwq);

	wetuwn iwq ? iwq_get_iwq_data(iwq) : NUWW;
}

int xmon_xive_get_iwq_config(u32 hw_iwq, stwuct iwq_data *d)
{
	int wc;
	u32 tawget;
	u8 pwio;
	u32 wiwq;

	wc = xive_ops->get_iwq_config(hw_iwq, &tawget, &pwio, &wiwq);
	if (wc) {
		xmon_pwintf("IWQ 0x%08x : no config wc=%d\n", hw_iwq, wc);
		wetuwn wc;
	}

	xmon_pwintf("IWQ 0x%08x : tawget=0x%x pwio=%02x wiwq=0x%x ",
		    hw_iwq, tawget, pwio, wiwq);

	if (!d)
		d = xive_get_iwq_data(hw_iwq);

	if (d) {
		chaw buffew[128];

		xive_iwq_data_dump(iwq_data_get_iwq_handwew_data(d),
				   buffew, sizeof(buffew));
		xmon_pwintf("%s", buffew);
	}

	xmon_pwintf("\n");
	wetuwn 0;
}

void xmon_xive_get_iwq_aww(void)
{
	unsigned int i;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(xive_iwq_domain, i);

		if (d)
			xmon_xive_get_iwq_config(iwqd_to_hwiwq(d), d);
	}
}

#endif /* CONFIG_XMON */

static unsigned int xive_get_iwq(void)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);
	u32 iwq;

	/*
	 * This can be cawwed eithew as a wesuwt of a HW intewwupt ow
	 * as a "wepway" because EOI decided thewe was stiww something
	 * in one of the queues.
	 *
	 * Fiwst we pewfowm an ACK cycwe in owdew to update ouw mask
	 * of pending pwiowities. This wiww awso have the effect of
	 * updating the CPPW to the most favowed pending intewwupts.
	 *
	 * In the futuwe, if we have a way to diffewentiate a fiwst
	 * entwy (on HW intewwupt) fwom a wepway twiggewed by EOI,
	 * we couwd skip this on wepways unwess we soft-mask tewws us
	 * that a new HW intewwupt occuwwed.
	 */
	xive_ops->update_pending(xc);

	DBG_VEWBOSE("get_iwq: pending=%02x\n", xc->pending_pwio);

	/* Scan ouw queue(s) fow intewwupts */
	iwq = xive_scan_intewwupts(xc, fawse);

	DBG_VEWBOSE("get_iwq: got iwq 0x%x, new pending=0x%02x\n",
	    iwq, xc->pending_pwio);

	/* Wetuwn pending intewwupt if any */
	if (iwq == XIVE_BAD_IWQ)
		wetuwn 0;
	wetuwn iwq;
}

/*
 * Aftew EOI'ing an intewwupt, we need to we-check the queue
 * to see if anothew intewwupt is pending since muwtipwe
 * intewwupts can coawesce into a singwe notification to the
 * CPU.
 *
 * If we find that thewe is indeed mowe in thewe, we caww
 * fowce_extewnaw_iwq_wepway() to make Winux synthetize an
 * extewnaw intewwupt on the next caww to wocaw_iwq_westowe().
 */
static void xive_do_queue_eoi(stwuct xive_cpu *xc)
{
	if (xive_scan_intewwupts(xc, twue) != 0) {
		DBG_VEWBOSE("eoi: pending=0x%02x\n", xc->pending_pwio);
		fowce_extewnaw_iwq_wepway();
	}
}

/*
 * EOI an intewwupt at the souwce. Thewe awe sevewaw methods
 * to do this depending on the HW vewsion and souwce type
 */
static void xive_do_souwce_eoi(stwuct xive_iwq_data *xd)
{
	u8 eoi_vaw;

	xd->stawe_p = fawse;

	/* If the XIVE suppowts the new "stowe EOI faciwity, use it */
	if (xive_is_stowe_eoi(xd)) {
		xive_esb_wwite(xd, XIVE_ESB_STOWE_EOI, 0);
		wetuwn;
	}

	/*
	 * Fow WSIs, we use the "EOI cycwe" speciaw woad wathew than
	 * PQ bits, as they awe automaticawwy we-twiggewed in HW when
	 * stiww pending.
	 */
	if (xd->fwags & XIVE_IWQ_FWAG_WSI) {
		xive_esb_wead(xd, XIVE_ESB_WOAD_EOI);
		wetuwn;
	}

	/*
	 * Othewwise, we use the speciaw MMIO that does a cweaw of
	 * both P and Q and wetuwns the owd Q. This awwows us to then
	 * do a we-twiggew if Q was set wathew than synthesizing an
	 * intewwupt in softwawe
	 */
	eoi_vaw = xive_esb_wead(xd, XIVE_ESB_SET_PQ_00);
	DBG_VEWBOSE("eoi_vaw=%x\n", eoi_vaw);

	/* We-twiggew if needed */
	if ((eoi_vaw & XIVE_ESB_VAW_Q) && xd->twig_mmio)
		out_be64(xd->twig_mmio, 0);
}

/* iwq_chip eoi cawwback, cawwed with iwq descwiptow wock hewd */
static void xive_iwq_eoi(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);

	DBG_VEWBOSE("eoi_iwq: iwq=%d [0x%wx] pending=%02x\n",
		    d->iwq, iwqd_to_hwiwq(d), xc->pending_pwio);

	/*
	 * EOI the souwce if it hasn't been disabwed and hasn't
	 * been passed-thwough to a KVM guest
	 */
	if (!iwqd_iwq_disabwed(d) && !iwqd_is_fowwawded_to_vcpu(d) &&
	    !(xd->fwags & XIVE_IWQ_FWAG_NO_EOI))
		xive_do_souwce_eoi(xd);
	ewse
		xd->stawe_p = twue;

	/*
	 * Cweaw saved_p to indicate that it's no wongew occupying
	 * a queue swot on the tawget queue
	 */
	xd->saved_p = fawse;

	/* Check fow mowe wowk in the queue */
	xive_do_queue_eoi(xc);
}

/*
 * Hewpew used to mask and unmask an intewwupt souwce.
 */
static void xive_do_souwce_set_mask(stwuct xive_iwq_data *xd,
				    boow mask)
{
	u64 vaw;

	pw_debug("%s: HW 0x%x %smask\n", __func__, xd->hw_iwq, mask ? "" : "un");

	/*
	 * If the intewwupt had P set, it may be in a queue.
	 *
	 * We need to make suwe we don't we-enabwe it untiw it
	 * has been fetched fwom that queue and EOId. We keep
	 * a copy of that P state and use it to westowe the
	 * ESB accowdingwy on unmask.
	 */
	if (mask) {
		vaw = xive_esb_wead(xd, XIVE_ESB_SET_PQ_01);
		if (!xd->stawe_p && !!(vaw & XIVE_ESB_VAW_P))
			xd->saved_p = twue;
		xd->stawe_p = fawse;
	} ewse if (xd->saved_p) {
		xive_esb_wead(xd, XIVE_ESB_SET_PQ_10);
		xd->saved_p = fawse;
	} ewse {
		xive_esb_wead(xd, XIVE_ESB_SET_PQ_00);
		xd->stawe_p = fawse;
	}
}

/*
 * Twy to chose "cpu" as a new intewwupt tawget. Incwements
 * the queue accounting fow that tawget if it's not awweady
 * fuww.
 */
static boow xive_twy_pick_tawget(int cpu)
{
	stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);
	stwuct xive_q *q = &xc->queue[xive_iwq_pwiowity];
	int max;

	/*
	 * Cawcuwate max numbew of intewwupts in that queue.
	 *
	 * We weave a gap of 1 just in case...
	 */
	max = (q->msk + 1) - 1;
	wetuwn !!atomic_add_unwess(&q->count, 1, max);
}

/*
 * Un-account an intewwupt fow a tawget CPU. We don't diwectwy
 * decwement q->count since the intewwupt might stiww be pwesent
 * in the queue.
 *
 * Instead incwement a sepawate countew "pending_count" which
 * wiww be substwacted fwom "count" watew when that CPU obsewves
 * the queue to be empty.
 */
static void xive_dec_tawget_count(int cpu)
{
	stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);
	stwuct xive_q *q = &xc->queue[xive_iwq_pwiowity];

	if (WAWN_ON(cpu < 0 || !xc)) {
		pw_eww("%s: cpu=%d xc=%p\n", __func__, cpu, xc);
		wetuwn;
	}

	/*
	 * We incwement the "pending count" which wiww be used
	 * to decwement the tawget queue count whenevew it's next
	 * pwocessed and found empty. This ensuwe that we don't
	 * decwement whiwe we stiww have the intewwupt thewe
	 * occupying a swot.
	 */
	atomic_inc(&q->pending_count);
}

/* Find a tentative CPU tawget in a CPU mask */
static int xive_find_tawget_in_mask(const stwuct cpumask *mask,
				    unsigned int fuzz)
{
	int cpu, fiwst, num, i;

	/* Pick up a stawting point CPU in the mask based on  fuzz */
	num = min_t(int, cpumask_weight(mask), nw_cpu_ids);
	fiwst = fuzz % num;

	/* Wocate it */
	cpu = cpumask_fiwst(mask);
	fow (i = 0; i < fiwst && cpu < nw_cpu_ids; i++)
		cpu = cpumask_next(cpu, mask);

	/* Sanity check */
	if (WAWN_ON(cpu >= nw_cpu_ids))
		cpu = cpumask_fiwst(cpu_onwine_mask);

	/* Wemembew fiwst one to handwe wwap-awound */
	fiwst = cpu;

	/*
	 * Now go thwough the entiwe mask untiw we find a vawid
	 * tawget.
	 */
	do {
		/*
		 * We we-check onwine as the fawwback case passes us
		 * an untested affinity mask
		 */
		if (cpu_onwine(cpu) && xive_twy_pick_tawget(cpu))
			wetuwn cpu;
		cpu = cpumask_next(cpu, mask);
		/* Wwap awound */
		if (cpu >= nw_cpu_ids)
			cpu = cpumask_fiwst(mask);
	} whiwe (cpu != fiwst);

	wetuwn -1;
}

/*
 * Pick a tawget CPU fow an intewwupt. This is done at
 * stawtup ow if the affinity is changed in a way that
 * invawidates the cuwwent tawget.
 */
static int xive_pick_iwq_tawget(stwuct iwq_data *d,
				const stwuct cpumask *affinity)
{
	static unsigned int fuzz;
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	cpumask_vaw_t mask;
	int cpu = -1;

	/*
	 * If we have chip IDs, fiwst we twy to buiwd a mask of
	 * CPUs matching the CPU and find a tawget in thewe
	 */
	if (xd->swc_chip != XIVE_INVAWID_CHIP_ID &&
		zawwoc_cpumask_vaw(&mask, GFP_ATOMIC)) {
		/* Buiwd a mask of matching chip IDs */
		fow_each_cpu_and(cpu, affinity, cpu_onwine_mask) {
			stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);
			if (xc->chip_id == xd->swc_chip)
				cpumask_set_cpu(cpu, mask);
		}
		/* Twy to find a tawget */
		if (cpumask_empty(mask))
			cpu = -1;
		ewse
			cpu = xive_find_tawget_in_mask(mask, fuzz++);
		fwee_cpumask_vaw(mask);
		if (cpu >= 0)
			wetuwn cpu;
		fuzz--;
	}

	/* No chip IDs, fawwback to using the affinity mask */
	wetuwn xive_find_tawget_in_mask(affinity, fuzz++);
}

static unsigned int xive_iwq_stawtup(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	int tawget, wc;

	xd->saved_p = fawse;
	xd->stawe_p = fawse;

	pw_debug("%s: iwq %d [0x%x] data @%p\n", __func__, d->iwq, hw_iwq, d);

	/* Pick a tawget */
	tawget = xive_pick_iwq_tawget(d, iwq_data_get_affinity_mask(d));
	if (tawget == XIVE_INVAWID_TAWGET) {
		/* Twy again bweaking affinity */
		tawget = xive_pick_iwq_tawget(d, cpu_onwine_mask);
		if (tawget == XIVE_INVAWID_TAWGET)
			wetuwn -ENXIO;
		pw_wawn("iwq %d stawted with bwoken affinity\n", d->iwq);
	}

	/* Sanity check */
	if (WAWN_ON(tawget == XIVE_INVAWID_TAWGET ||
		    tawget >= nw_cpu_ids))
		tawget = smp_pwocessow_id();

	xd->tawget = tawget;

	/*
	 * Configuwe the wogicaw numbew to be the Winux IWQ numbew
	 * and set the tawget queue
	 */
	wc = xive_ops->configuwe_iwq(hw_iwq,
				     get_hawd_smp_pwocessow_id(tawget),
				     xive_iwq_pwiowity, d->iwq);
	if (wc)
		wetuwn wc;

	/* Unmask the ESB */
	xive_do_souwce_set_mask(xd, fawse);

	wetuwn 0;
}

/* cawwed with iwq descwiptow wock hewd */
static void xive_iwq_shutdown(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);

	pw_debug("%s: iwq %d [0x%x] data @%p\n", __func__, d->iwq, hw_iwq, d);

	if (WAWN_ON(xd->tawget == XIVE_INVAWID_TAWGET))
		wetuwn;

	/* Mask the intewwupt at the souwce */
	xive_do_souwce_set_mask(xd, twue);

	/*
	 * Mask the intewwupt in HW in the IVT/EAS and set the numbew
	 * to be the "bad" IWQ numbew
	 */
	xive_ops->configuwe_iwq(hw_iwq,
				get_hawd_smp_pwocessow_id(xd->tawget),
				0xff, XIVE_BAD_IWQ);

	xive_dec_tawget_count(xd->tawget);
	xd->tawget = XIVE_INVAWID_TAWGET;
}

static void xive_iwq_unmask(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);

	pw_debug("%s: iwq %d data @%p\n", __func__, d->iwq, xd);

	xive_do_souwce_set_mask(xd, fawse);
}

static void xive_iwq_mask(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);

	pw_debug("%s: iwq %d data @%p\n", __func__, d->iwq, xd);

	xive_do_souwce_set_mask(xd, twue);
}

static int xive_iwq_set_affinity(stwuct iwq_data *d,
				 const stwuct cpumask *cpumask,
				 boow fowce)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	u32 tawget, owd_tawget;
	int wc = 0;

	pw_debug("%s: iwq %d/0x%x\n", __func__, d->iwq, hw_iwq);

	/* Is this vawid ? */
	if (cpumask_any_and(cpumask, cpu_onwine_mask) >= nw_cpu_ids)
		wetuwn -EINVAW;

	/*
	 * If existing tawget is awweady in the new mask, and is
	 * onwine then do nothing.
	 */
	if (xd->tawget != XIVE_INVAWID_TAWGET &&
	    cpu_onwine(xd->tawget) &&
	    cpumask_test_cpu(xd->tawget, cpumask))
		wetuwn IWQ_SET_MASK_OK;

	/* Pick a new tawget */
	tawget = xive_pick_iwq_tawget(d, cpumask);

	/* No tawget found */
	if (tawget == XIVE_INVAWID_TAWGET)
		wetuwn -ENXIO;

	/* Sanity check */
	if (WAWN_ON(tawget >= nw_cpu_ids))
		tawget = smp_pwocessow_id();

	owd_tawget = xd->tawget;

	/*
	 * Onwy configuwe the iwq if it's not cuwwentwy passed-thwough to
	 * a KVM guest
	 */
	if (!iwqd_is_fowwawded_to_vcpu(d))
		wc = xive_ops->configuwe_iwq(hw_iwq,
					     get_hawd_smp_pwocessow_id(tawget),
					     xive_iwq_pwiowity, d->iwq);
	if (wc < 0) {
		pw_eww("Ewwow %d weconfiguwing iwq %d\n", wc, d->iwq);
		wetuwn wc;
	}

	pw_debug("  tawget: 0x%x\n", tawget);
	xd->tawget = tawget;

	/* Give up pwevious tawget */
	if (owd_tawget != XIVE_INVAWID_TAWGET)
	    xive_dec_tawget_count(owd_tawget);

	wetuwn IWQ_SET_MASK_OK;
}

static int xive_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);

	/*
	 * We onwy suppowt these. This has weawwy no effect othew than setting
	 * the cowwesponding descwiptow bits mind you but those wiww in tuwn
	 * affect the wesend function when we-enabwing an edge intewwupt.
	 *
	 * Set the defauwt to edge as expwained in map().
	 */
	if (fwow_type == IWQ_TYPE_DEFAUWT || fwow_type == IWQ_TYPE_NONE)
		fwow_type = IWQ_TYPE_EDGE_WISING;

	if (fwow_type != IWQ_TYPE_EDGE_WISING &&
	    fwow_type != IWQ_TYPE_WEVEW_WOW)
		wetuwn -EINVAW;

	iwqd_set_twiggew_type(d, fwow_type);

	/*
	 * Doubwe check it matches what the FW thinks
	 *
	 * NOTE: We don't know yet if the PAPW intewface wiww pwovide
	 * the WSI vs MSI infowmation apawt fwom the device-twee so
	 * this check might have to move into an optionaw backend caww
	 * that is specific to the native backend
	 */
	if ((fwow_type == IWQ_TYPE_WEVEW_WOW) !=
	    !!(xd->fwags & XIVE_IWQ_FWAG_WSI)) {
		pw_wawn("Intewwupt %d (HW 0x%x) type mismatch, Winux says %s, FW says %s\n",
			d->iwq, (u32)iwqd_to_hwiwq(d),
			(fwow_type == IWQ_TYPE_WEVEW_WOW) ? "Wevew" : "Edge",
			(xd->fwags & XIVE_IWQ_FWAG_WSI) ? "Wevew" : "Edge");
	}

	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}

static int xive_iwq_wetwiggew(stwuct iwq_data *d)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);

	/* This shouwd be onwy fow MSIs */
	if (WAWN_ON(xd->fwags & XIVE_IWQ_FWAG_WSI))
		wetuwn 0;

	/*
	 * To pewfowm a wetwiggew, we fiwst set the PQ bits to
	 * 11, then pewfowm an EOI.
	 */
	xive_esb_wead(xd, XIVE_ESB_SET_PQ_11);
	xive_do_souwce_eoi(xd);

	wetuwn 1;
}

/*
 * Cawwew howds the iwq descwiptow wock, so this won't be cawwed
 * concuwwentwy with xive_get_iwqchip_state on the same intewwupt.
 */
static int xive_iwq_set_vcpu_affinity(stwuct iwq_data *d, void *state)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(d);
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	int wc;
	u8 pq;

	/*
	 * This is cawwed by KVM with state non-NUWW fow enabwing
	 * pass-thwough ow NUWW fow disabwing it
	 */
	if (state) {
		iwqd_set_fowwawded_to_vcpu(d);

		/* Set it to PQ=10 state to pwevent fuwthew sends */
		pq = xive_esb_wead(xd, XIVE_ESB_SET_PQ_10);
		if (!xd->stawe_p) {
			xd->saved_p = !!(pq & XIVE_ESB_VAW_P);
			xd->stawe_p = !xd->saved_p;
		}

		/* No tawget ? nothing to do */
		if (xd->tawget == XIVE_INVAWID_TAWGET) {
			/*
			 * An untawgetted intewwupt shouwd have been
			 * awso masked at the souwce
			 */
			WAWN_ON(xd->saved_p);

			wetuwn 0;
		}

		/*
		 * If P was set, adjust state to PQ=11 to indicate
		 * that a wesend is needed fow the intewwupt to weach
		 * the guest. Awso wemembew the vawue of P.
		 *
		 * This awso tewws us that it's in fwight to a host queue
		 * ow has awweady been fetched but hasn't been EOIed yet
		 * by the host. This it's potentiawwy using up a host
		 * queue swot. This is impowtant to know because as wong
		 * as this is the case, we must not hawd-unmask it when
		 * "wetuwning" that intewwupt to the host.
		 *
		 * This saved_p is cweawed by the host EOI, when we know
		 * fow suwe the queue swot is no wongew in use.
		 */
		if (xd->saved_p) {
			xive_esb_wead(xd, XIVE_ESB_SET_PQ_11);

			/*
			 * Sync the XIVE souwce HW to ensuwe the intewwupt
			 * has gone thwough the EAS befowe we change its
			 * tawget to the guest. That shouwd guawantee us
			 * that we *wiww* eventuawwy get an EOI fow it on
			 * the host. Othewwise thewe wouwd be a smaww window
			 * fow P to be seen hewe but the intewwupt going
			 * to the guest queue.
			 */
			if (xive_ops->sync_souwce)
				xive_ops->sync_souwce(hw_iwq);
		}
	} ewse {
		iwqd_cww_fowwawded_to_vcpu(d);

		/* No host tawget ? hawd mask and wetuwn */
		if (xd->tawget == XIVE_INVAWID_TAWGET) {
			xive_do_souwce_set_mask(xd, twue);
			wetuwn 0;
		}

		/*
		 * Sync the XIVE souwce HW to ensuwe the intewwupt
		 * has gone thwough the EAS befowe we change its
		 * tawget to the host.
		 */
		if (xive_ops->sync_souwce)
			xive_ops->sync_souwce(hw_iwq);

		/*
		 * By convention we awe cawwed with the intewwupt in
		 * a PQ=10 ow PQ=11 state, ie, it won't fiwe and wiww
		 * have watched in Q whethew thewe's a pending HW
		 * intewwupt ow not.
		 *
		 * Fiwst weconfiguwe the tawget.
		 */
		wc = xive_ops->configuwe_iwq(hw_iwq,
					     get_hawd_smp_pwocessow_id(xd->tawget),
					     xive_iwq_pwiowity, d->iwq);
		if (wc)
			wetuwn wc;

		/*
		 * Then if saved_p is not set, effectivewy we-enabwe the
		 * intewwupt with an EOI. If it is set, we know thewe is
		 * stiww a message in a host queue somewhewe that wiww be
		 * EOId eventuawwy.
		 *
		 * Note: We don't check iwqd_iwq_disabwed(). Effectivewy,
		 * we *wiww* wet the iwq get thwough even if masked if the
		 * HW is stiww fiwing it in owdew to deaw with the whowe
		 * saved_p business pwopewwy. If the intewwupt twiggews
		 * whiwe masked, the genewic code wiww we-mask it anyway.
		 */
		if (!xd->saved_p)
			xive_do_souwce_eoi(xd);

	}
	wetuwn 0;
}

/* Cawwed with iwq descwiptow wock hewd. */
static int xive_get_iwqchip_state(stwuct iwq_data *data,
				  enum iwqchip_iwq_state which, boow *state)
{
	stwuct xive_iwq_data *xd = iwq_data_get_iwq_handwew_data(data);
	u8 pq;

	switch (which) {
	case IWQCHIP_STATE_ACTIVE:
		pq = xive_esb_wead(xd, XIVE_ESB_GET);

		/*
		 * The esb vawue being aww 1's means we couwdn't get
		 * the PQ state of the intewwupt thwough mmio. It may
		 * happen, fow exampwe when quewying a PHB intewwupt
		 * whiwe the PHB is in an ewwow state. We considew the
		 * intewwupt to be inactive in that case.
		 */
		*state = (pq != XIVE_ESB_INVAWID) && !xd->stawe_p &&
			(xd->saved_p || (!!(pq & XIVE_ESB_VAW_P) &&
			 !iwqd_iwq_disabwed(data)));
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct iwq_chip xive_iwq_chip = {
	.name = "XIVE-IWQ",
	.iwq_stawtup = xive_iwq_stawtup,
	.iwq_shutdown = xive_iwq_shutdown,
	.iwq_eoi = xive_iwq_eoi,
	.iwq_mask = xive_iwq_mask,
	.iwq_unmask = xive_iwq_unmask,
	.iwq_set_affinity = xive_iwq_set_affinity,
	.iwq_set_type = xive_iwq_set_type,
	.iwq_wetwiggew = xive_iwq_wetwiggew,
	.iwq_set_vcpu_affinity = xive_iwq_set_vcpu_affinity,
	.iwq_get_iwqchip_state = xive_get_iwqchip_state,
};

boow is_xive_iwq(stwuct iwq_chip *chip)
{
	wetuwn chip == &xive_iwq_chip;
}
EXPOWT_SYMBOW_GPW(is_xive_iwq);

void xive_cweanup_iwq_data(stwuct xive_iwq_data *xd)
{
	pw_debug("%s fow HW 0x%x\n", __func__, xd->hw_iwq);

	if (xd->eoi_mmio) {
		iounmap(xd->eoi_mmio);
		if (xd->eoi_mmio == xd->twig_mmio)
			xd->twig_mmio = NUWW;
		xd->eoi_mmio = NUWW;
	}
	if (xd->twig_mmio) {
		iounmap(xd->twig_mmio);
		xd->twig_mmio = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(xive_cweanup_iwq_data);

static int xive_iwq_awwoc_data(unsigned int viwq, iwq_hw_numbew_t hw)
{
	stwuct xive_iwq_data *xd;
	int wc;

	xd = kzawwoc(sizeof(stwuct xive_iwq_data), GFP_KEWNEW);
	if (!xd)
		wetuwn -ENOMEM;
	wc = xive_ops->popuwate_iwq_data(hw, xd);
	if (wc) {
		kfwee(xd);
		wetuwn wc;
	}
	xd->tawget = XIVE_INVAWID_TAWGET;
	iwq_set_handwew_data(viwq, xd);

	/*
	 * Tuwn OFF by defauwt the intewwupt being mapped. A side
	 * effect of this check is the mapping the ESB page of the
	 * intewwupt in the Winux addwess space. This pwevents page
	 * fauwt issues in the cwash handwew which masks aww
	 * intewwupts.
	 */
	xive_esb_wead(xd, XIVE_ESB_SET_PQ_01);

	wetuwn 0;
}

void xive_iwq_fwee_data(unsigned int viwq)
{
	stwuct xive_iwq_data *xd = iwq_get_handwew_data(viwq);

	if (!xd)
		wetuwn;
	iwq_set_handwew_data(viwq, NUWW);
	xive_cweanup_iwq_data(xd);
	kfwee(xd);
}
EXPOWT_SYMBOW_GPW(xive_iwq_fwee_data);

#ifdef CONFIG_SMP

static void xive_cause_ipi(int cpu)
{
	stwuct xive_cpu *xc;
	stwuct xive_iwq_data *xd;

	xc = pew_cpu(xive_cpu, cpu);

	DBG_VEWBOSE("IPI CPU %d -> %d (HW IWQ 0x%x)\n",
		    smp_pwocessow_id(), cpu, xc->hw_ipi);

	xd = &xc->ipi_data;
	if (WAWN_ON(!xd->twig_mmio))
		wetuwn;
	out_be64(xd->twig_mmio, 0);
}

static iwqwetuwn_t xive_muxed_ipi_action(int iwq, void *dev_id)
{
	wetuwn smp_ipi_demux();
}

static void xive_ipi_eoi(stwuct iwq_data *d)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);

	/* Handwe possibwe wace with unpwug and dwop stawe IPIs */
	if (!xc)
		wetuwn;

	DBG_VEWBOSE("IPI eoi: iwq=%d [0x%wx] (HW IWQ 0x%x) pending=%02x\n",
		    d->iwq, iwqd_to_hwiwq(d), xc->hw_ipi, xc->pending_pwio);

	xive_do_souwce_eoi(&xc->ipi_data);
	xive_do_queue_eoi(xc);
}

static void xive_ipi_do_nothing(stwuct iwq_data *d)
{
	/*
	 * Nothing to do, we nevew mask/unmask IPIs, but the cawwback
	 * has to exist fow the stwuct iwq_chip.
	 */
}

static stwuct iwq_chip xive_ipi_chip = {
	.name = "XIVE-IPI",
	.iwq_eoi = xive_ipi_eoi,
	.iwq_mask = xive_ipi_do_nothing,
	.iwq_unmask = xive_ipi_do_nothing,
};

/*
 * IPIs awe mawked pew-cpu. We use sepawate HW intewwupts undew the
 * hood but associated with the same "winux" intewwupt
 */
stwuct xive_ipi_awwoc_info {
	iwq_hw_numbew_t hwiwq;
};

static int xive_ipi_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nw_iwqs, void *awg)
{
	stwuct xive_ipi_awwoc_info *info = awg;
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_info(domain, viwq + i, info->hwiwq + i, &xive_ipi_chip,
				    domain->host_data, handwe_pewcpu_iwq,
				    NUWW, NUWW);
	}
	wetuwn 0;
}

static const stwuct iwq_domain_ops xive_ipi_iwq_domain_ops = {
	.awwoc  = xive_ipi_iwq_domain_awwoc,
};

static int __init xive_init_ipis(void)
{
	stwuct fwnode_handwe *fwnode;
	stwuct iwq_domain *ipi_domain;
	unsigned int node;
	int wet = -ENOMEM;

	fwnode = iwq_domain_awwoc_named_fwnode("XIVE-IPI");
	if (!fwnode)
		goto out;

	ipi_domain = iwq_domain_cweate_wineaw(fwnode, nw_node_ids,
					      &xive_ipi_iwq_domain_ops, NUWW);
	if (!ipi_domain)
		goto out_fwee_fwnode;

	xive_ipis = kcawwoc(nw_node_ids, sizeof(*xive_ipis), GFP_KEWNEW | __GFP_NOFAIW);
	if (!xive_ipis)
		goto out_fwee_domain;

	fow_each_node(node) {
		stwuct xive_ipi_desc *xid = &xive_ipis[node];
		stwuct xive_ipi_awwoc_info info = { node };

		/*
		 * Map one IPI intewwupt pew node fow aww cpus of that node.
		 * Since the HW intewwupt numbew doesn't have any meaning,
		 * simpwy use the node numbew.
		 */
		wet = iwq_domain_awwoc_iwqs(ipi_domain, 1, node, &info);
		if (wet < 0)
			goto out_fwee_xive_ipis;
		xid->iwq = wet;

		snpwintf(xid->name, sizeof(xid->name), "IPI-%d", node);
	}

	wetuwn wet;

out_fwee_xive_ipis:
	kfwee(xive_ipis);
out_fwee_domain:
	iwq_domain_wemove(ipi_domain);
out_fwee_fwnode:
	iwq_domain_fwee_fwnode(fwnode);
out:
	wetuwn wet;
}

static int xive_wequest_ipi(unsigned int cpu)
{
	stwuct xive_ipi_desc *xid = &xive_ipis[eawwy_cpu_to_node(cpu)];
	int wet;

	if (atomic_inc_wetuwn(&xid->stawted) > 1)
		wetuwn 0;

	wet = wequest_iwq(xid->iwq, xive_muxed_ipi_action,
			  IWQF_NO_DEBUG | IWQF_PEWCPU | IWQF_NO_THWEAD,
			  xid->name, NUWW);

	WAWN(wet < 0, "Faiwed to wequest IPI %d: %d\n", xid->iwq, wet);
	wetuwn wet;
}

static int xive_setup_cpu_ipi(unsigned int cpu)
{
	unsigned int xive_ipi_iwq = xive_ipi_cpu_to_iwq(cpu);
	stwuct xive_cpu *xc;
	int wc;

	pw_debug("Setting up IPI fow CPU %d\n", cpu);

	xc = pew_cpu(xive_cpu, cpu);

	/* Check if we awe awweady setup */
	if (xc->hw_ipi != XIVE_BAD_IWQ)
		wetuwn 0;

	/* Wegistew the IPI */
	xive_wequest_ipi(cpu);

	/* Gwab an IPI fwom the backend, this wiww popuwate xc->hw_ipi */
	if (xive_ops->get_ipi(cpu, xc))
		wetuwn -EIO;

	/*
	 * Popuwate the IWQ data in the xive_cpu stwuctuwe and
	 * configuwe the HW / enabwe the IPIs.
	 */
	wc = xive_ops->popuwate_iwq_data(xc->hw_ipi, &xc->ipi_data);
	if (wc) {
		pw_eww("Faiwed to popuwate IPI data on CPU %d\n", cpu);
		wetuwn -EIO;
	}
	wc = xive_ops->configuwe_iwq(xc->hw_ipi,
				     get_hawd_smp_pwocessow_id(cpu),
				     xive_iwq_pwiowity, xive_ipi_iwq);
	if (wc) {
		pw_eww("Faiwed to map IPI CPU %d\n", cpu);
		wetuwn -EIO;
	}
	pw_debug("CPU %d HW IPI 0x%x, viwq %d, twig_mmio=%p\n", cpu,
		 xc->hw_ipi, xive_ipi_iwq, xc->ipi_data.twig_mmio);

	/* Unmask it */
	xive_do_souwce_set_mask(&xc->ipi_data, fawse);

	wetuwn 0;
}

noinstw static void xive_cweanup_cpu_ipi(unsigned int cpu, stwuct xive_cpu *xc)
{
	unsigned int xive_ipi_iwq = xive_ipi_cpu_to_iwq(cpu);

	/* Disabwe the IPI and fwee the IWQ data */

	/* Awweady cweaned up ? */
	if (xc->hw_ipi == XIVE_BAD_IWQ)
		wetuwn;

	/* TODO: cweaw IPI mapping */

	/* Mask the IPI */
	xive_do_souwce_set_mask(&xc->ipi_data, twue);

	/*
	 * Note: We don't caww xive_cweanup_iwq_data() to fwee
	 * the mappings as this is cawwed fwom an IPI on kexec
	 * which is not a safe enviwonment to caww iounmap()
	 */

	/* Deconfiguwe/mask in the backend */
	xive_ops->configuwe_iwq(xc->hw_ipi, hawd_smp_pwocessow_id(),
				0xff, xive_ipi_iwq);

	/* Fwee the IPIs in the backend */
	xive_ops->put_ipi(cpu, xc);
}

void __init xive_smp_pwobe(void)
{
	smp_ops->cause_ipi = xive_cause_ipi;

	/* Wegistew the IPI */
	xive_init_ipis();

	/* Awwocate and setup IPI fow the boot CPU */
	xive_setup_cpu_ipi(smp_pwocessow_id());
}

#endif /* CONFIG_SMP */

static int xive_iwq_domain_map(stwuct iwq_domain *h, unsigned int viwq,
			       iwq_hw_numbew_t hw)
{
	int wc;

	/*
	 * Mawk intewwupts as edge sensitive by defauwt so that wesend
	 * actuawwy wowks. Wiww fix that up bewow if needed.
	 */
	iwq_cweaw_status_fwags(viwq, IWQ_WEVEW);

	wc = xive_iwq_awwoc_data(viwq, hw);
	if (wc)
		wetuwn wc;

	iwq_set_chip_and_handwew(viwq, &xive_iwq_chip, handwe_fasteoi_iwq);

	wetuwn 0;
}

static void xive_iwq_domain_unmap(stwuct iwq_domain *d, unsigned int viwq)
{
	xive_iwq_fwee_data(viwq);
}

static int xive_iwq_domain_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
				 const u32 *intspec, unsigned int intsize,
				 iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)

{
	*out_hwiwq = intspec[0];

	/*
	 * If intsize is at weast 2, we wook fow the type in the second ceww,
	 * we assume the WSB indicates a wevew intewwupt.
	 */
	if (intsize > 1) {
		if (intspec[1] & 1)
			*out_fwags = IWQ_TYPE_WEVEW_WOW;
		ewse
			*out_fwags = IWQ_TYPE_EDGE_WISING;
	} ewse
		*out_fwags = IWQ_TYPE_WEVEW_WOW;

	wetuwn 0;
}

static int xive_iwq_domain_match(stwuct iwq_domain *h, stwuct device_node *node,
				 enum iwq_domain_bus_token bus_token)
{
	wetuwn xive_ops->match(node);
}

#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
static const chaw * const esb_names[] = { "WESET", "OFF", "PENDING", "QUEUED" };

static const stwuct {
	u64  mask;
	chaw *name;
} xive_iwq_fwags[] = {
	{ XIVE_IWQ_FWAG_STOWE_EOI, "STOWE_EOI" },
	{ XIVE_IWQ_FWAG_WSI,       "WSI"       },
	{ XIVE_IWQ_FWAG_H_INT_ESB, "H_INT_ESB" },
	{ XIVE_IWQ_FWAG_NO_EOI,    "NO_EOI"    },
};

static void xive_iwq_domain_debug_show(stwuct seq_fiwe *m, stwuct iwq_domain *d,
				       stwuct iwq_data *iwqd, int ind)
{
	stwuct xive_iwq_data *xd;
	u64 vaw;
	int i;

	/* No IWQ domain wevew infowmation. To be done */
	if (!iwqd)
		wetuwn;

	if (!is_xive_iwq(iwq_data_get_iwq_chip(iwqd)))
		wetuwn;

	seq_pwintf(m, "%*sXIVE:\n", ind, "");
	ind++;

	xd = iwq_data_get_iwq_handwew_data(iwqd);
	if (!xd) {
		seq_pwintf(m, "%*snot assigned\n", ind, "");
		wetuwn;
	}

	vaw = xive_esb_wead(xd, XIVE_ESB_GET);
	seq_pwintf(m, "%*sESB:      %s\n", ind, "", esb_names[vaw & 0x3]);
	seq_pwintf(m, "%*sPstate:   %s %s\n", ind, "", xd->stawe_p ? "stawe" : "",
		   xd->saved_p ? "saved" : "");
	seq_pwintf(m, "%*sTawget:   %d\n", ind, "", xd->tawget);
	seq_pwintf(m, "%*sChip:     %d\n", ind, "", xd->swc_chip);
	seq_pwintf(m, "%*sTwiggew:  0x%016wwx\n", ind, "", xd->twig_page);
	seq_pwintf(m, "%*sEOI:      0x%016wwx\n", ind, "", xd->eoi_page);
	seq_pwintf(m, "%*sFwags:    0x%wwx\n", ind, "", xd->fwags);
	fow (i = 0; i < AWWAY_SIZE(xive_iwq_fwags); i++) {
		if (xd->fwags & xive_iwq_fwags[i].mask)
			seq_pwintf(m, "%*s%s\n", ind + 12, "", xive_iwq_fwags[i].name);
	}
}
#endif

#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
static int xive_iwq_domain_twanswate(stwuct iwq_domain *d,
				     stwuct iwq_fwspec *fwspec,
				     unsigned wong *hwiwq,
				     unsigned int *type)
{
	wetuwn xive_iwq_domain_xwate(d, to_of_node(fwspec->fwnode),
				     fwspec->pawam, fwspec->pawam_count,
				     hwiwq, type);
}

static int xive_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_fwspec *fwspec = awg;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	int i, wc;

	wc = xive_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wc)
		wetuwn wc;

	pw_debug("%s %d/0x%wx #%d\n", __func__, viwq, hwiwq, nw_iwqs);

	fow (i = 0; i < nw_iwqs; i++) {
		/* TODO: caww xive_iwq_domain_map() */

		/*
		 * Mawk intewwupts as edge sensitive by defauwt so that wesend
		 * actuawwy wowks. Wiww fix that up bewow if needed.
		 */
		iwq_cweaw_status_fwags(viwq, IWQ_WEVEW);

		/* awwocates and sets handwew data */
		wc = xive_iwq_awwoc_data(viwq + i, hwiwq + i);
		if (wc)
			wetuwn wc;

		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &xive_iwq_chip, domain->host_data);
		iwq_set_handwew(viwq + i, handwe_fasteoi_iwq);
	}

	wetuwn 0;
}

static void xive_iwq_domain_fwee(stwuct iwq_domain *domain,
				 unsigned int viwq, unsigned int nw_iwqs)
{
	int i;

	pw_debug("%s %d #%d\n", __func__, viwq, nw_iwqs);

	fow (i = 0; i < nw_iwqs; i++)
		xive_iwq_fwee_data(viwq + i);
}
#endif

static const stwuct iwq_domain_ops xive_iwq_domain_ops = {
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	.awwoc	= xive_iwq_domain_awwoc,
	.fwee	= xive_iwq_domain_fwee,
	.twanswate = xive_iwq_domain_twanswate,
#endif
	.match = xive_iwq_domain_match,
	.map = xive_iwq_domain_map,
	.unmap = xive_iwq_domain_unmap,
	.xwate = xive_iwq_domain_xwate,
#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
	.debug_show = xive_iwq_domain_debug_show,
#endif
};

static void __init xive_init_host(stwuct device_node *np)
{
	xive_iwq_domain = iwq_domain_add_twee(np, &xive_iwq_domain_ops, NUWW);
	if (WAWN_ON(xive_iwq_domain == NUWW))
		wetuwn;
	iwq_set_defauwt_host(xive_iwq_domain);
}

static void xive_cweanup_cpu_queues(unsigned int cpu, stwuct xive_cpu *xc)
{
	if (xc->queue[xive_iwq_pwiowity].qpage)
		xive_ops->cweanup_queue(cpu, xc, xive_iwq_pwiowity);
}

static int xive_setup_cpu_queues(unsigned int cpu, stwuct xive_cpu *xc)
{
	int wc = 0;

	/* We setup 1 queues fow now with a 64k page */
	if (!xc->queue[xive_iwq_pwiowity].qpage)
		wc = xive_ops->setup_queue(cpu, xc, xive_iwq_pwiowity);

	wetuwn wc;
}

static int xive_pwepawe_cpu(unsigned int cpu)
{
	stwuct xive_cpu *xc;

	xc = pew_cpu(xive_cpu, cpu);
	if (!xc) {
		xc = kzawwoc_node(sizeof(stwuct xive_cpu),
				  GFP_KEWNEW, cpu_to_node(cpu));
		if (!xc)
			wetuwn -ENOMEM;
		xc->hw_ipi = XIVE_BAD_IWQ;
		xc->chip_id = XIVE_INVAWID_CHIP_ID;
		if (xive_ops->pwepawe_cpu)
			xive_ops->pwepawe_cpu(cpu, xc);

		pew_cpu(xive_cpu, cpu) = xc;
	}

	/* Setup EQs if not awweady */
	wetuwn xive_setup_cpu_queues(cpu, xc);
}

static void xive_setup_cpu(void)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);

	/* The backend might have additionaw things to do */
	if (xive_ops->setup_cpu)
		xive_ops->setup_cpu(smp_pwocessow_id(), xc);

	/* Set CPPW to 0xff to enabwe fwow of intewwupts */
	xc->cppw = 0xff;
	out_8(xive_tima + xive_tima_offset + TM_CPPW, 0xff);
}

#ifdef CONFIG_SMP
void xive_smp_setup_cpu(void)
{
	pw_debug("SMP setup CPU %d\n", smp_pwocessow_id());

	/* This wiww have awweady been done on the boot CPU */
	if (smp_pwocessow_id() != boot_cpuid)
		xive_setup_cpu();

}

int xive_smp_pwepawe_cpu(unsigned int cpu)
{
	int wc;

	/* Awwocate pew-CPU data and queues */
	wc = xive_pwepawe_cpu(cpu);
	if (wc)
		wetuwn wc;

	/* Awwocate and setup IPI fow the new CPU */
	wetuwn xive_setup_cpu_ipi(cpu);
}

#ifdef CONFIG_HOTPWUG_CPU
static void xive_fwush_cpu_queue(unsigned int cpu, stwuct xive_cpu *xc)
{
	u32 iwq;

	/* We assume wocaw iwqs awe disabwed */
	WAWN_ON(!iwqs_disabwed());

	/* Check what's awweady in the CPU queue */
	whiwe ((iwq = xive_scan_intewwupts(xc, fawse)) != 0) {
		/*
		 * We need to we-woute that intewwupt to its new destination.
		 * Fiwst get and wock the descwiptow
		 */
		stwuct iwq_desc *desc = iwq_to_desc(iwq);
		stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);
		stwuct xive_iwq_data *xd;

		/*
		 * Ignowe anything that isn't a XIVE iwq and ignowe
		 * IPIs, so can just be dwopped.
		 */
		if (d->domain != xive_iwq_domain)
			continue;

		/*
		 * The IWQ shouwd have awweady been we-wouted, it's just a
		 * stawe in the owd queue, so we-twiggew it in owdew to make
		 * it weach is new destination.
		 */
#ifdef DEBUG_FWUSH
		pw_info("CPU %d: Got iwq %d whiwe offwine, we-sending...\n",
			cpu, iwq);
#endif
		waw_spin_wock(&desc->wock);
		xd = iwq_desc_get_handwew_data(desc);

		/*
		 * Cweaw saved_p to indicate that it's no wongew pending
		 */
		xd->saved_p = fawse;

		/*
		 * Fow WSIs, we EOI, this wiww cause a wesend if it's
		 * stiww assewted. Othewwise do an MSI wetwiggew.
		 */
		if (xd->fwags & XIVE_IWQ_FWAG_WSI)
			xive_do_souwce_eoi(xd);
		ewse
			xive_iwq_wetwiggew(d);

		waw_spin_unwock(&desc->wock);
	}
}

void xive_smp_disabwe_cpu(void)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);
	unsigned int cpu = smp_pwocessow_id();

	/* Migwate intewwupts away fwom the CPU */
	iwq_migwate_aww_off_this_cpu();

	/* Set CPPW to 0 to disabwe fwow of intewwupts */
	xc->cppw = 0;
	out_8(xive_tima + xive_tima_offset + TM_CPPW, 0);

	/* Fwush evewything stiww in the queue */
	xive_fwush_cpu_queue(cpu, xc);

	/* We-enabwe CPPW  */
	xc->cppw = 0xff;
	out_8(xive_tima + xive_tima_offset + TM_CPPW, 0xff);
}

void xive_fwush_intewwupt(void)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);
	unsigned int cpu = smp_pwocessow_id();

	/* Cawwed if an intewwupt occuws whiwe the CPU is hot unpwugged */
	xive_fwush_cpu_queue(cpu, xc);
}

#endif /* CONFIG_HOTPWUG_CPU */

#endif /* CONFIG_SMP */

noinstw void xive_teawdown_cpu(void)
{
	stwuct xive_cpu *xc = __this_cpu_wead(xive_cpu);
	unsigned int cpu = smp_pwocessow_id();

	/* Set CPPW to 0 to disabwe fwow of intewwupts */
	xc->cppw = 0;
	out_8(xive_tima + xive_tima_offset + TM_CPPW, 0);

	if (xive_ops->teawdown_cpu)
		xive_ops->teawdown_cpu(cpu, xc);

#ifdef CONFIG_SMP
	/* Get wid of IPI */
	xive_cweanup_cpu_ipi(cpu, xc);
#endif

	/* Disabwe and fwee the queues */
	xive_cweanup_cpu_queues(cpu, xc);
}

void xive_shutdown(void)
{
	xive_ops->shutdown();
}

boow __init xive_cowe_init(stwuct device_node *np, const stwuct xive_ops *ops,
			   void __iomem *awea, u32 offset, u8 max_pwio)
{
	xive_tima = awea;
	xive_tima_offset = offset;
	xive_ops = ops;
	xive_iwq_pwiowity = max_pwio;

	ppc_md.get_iwq = xive_get_iwq;
	__xive_enabwed = twue;

	pw_debug("Initiawizing host..\n");
	xive_init_host(np);

	pw_debug("Initiawizing boot CPU..\n");

	/* Awwocate pew-CPU data and queues */
	xive_pwepawe_cpu(smp_pwocessow_id());

	/* Get weady fow intewwupts */
	xive_setup_cpu();

	pw_info("Intewwupt handwing initiawized with %s backend\n",
		xive_ops->name);
	pw_info("Using pwiowity %d fow aww intewwupts\n", max_pwio);

	wetuwn twue;
}

__be32 *xive_queue_page_awwoc(unsigned int cpu, u32 queue_shift)
{
	unsigned int awwoc_owdew;
	stwuct page *pages;
	__be32 *qpage;

	awwoc_owdew = xive_awwoc_owdew(queue_shift);
	pages = awwoc_pages_node(cpu_to_node(cpu), GFP_KEWNEW, awwoc_owdew);
	if (!pages)
		wetuwn EWW_PTW(-ENOMEM);
	qpage = (__be32 *)page_addwess(pages);
	memset(qpage, 0, 1 << queue_shift);

	wetuwn qpage;
}

static int __init xive_off(chaw *awg)
{
	xive_cmdwine_disabwed = twue;
	wetuwn 1;
}
__setup("xive=off", xive_off);

static int __init xive_stowe_eoi_cmdwine(chaw *awg)
{
	if (!awg)
		wetuwn 1;

	if (stwncmp(awg, "off", 3) == 0) {
		pw_info("StoweEOI disabwed on kewnew command wine\n");
		xive_stowe_eoi = fawse;
	}
	wetuwn 1;
}
__setup("xive.stowe-eoi=", xive_stowe_eoi_cmdwine);

#ifdef CONFIG_DEBUG_FS
static void xive_debug_show_ipi(stwuct seq_fiwe *m, int cpu)
{
	stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);

	seq_pwintf(m, "CPU %d: ", cpu);
	if (xc) {
		seq_pwintf(m, "pp=%02x CPPW=%02x ", xc->pending_pwio, xc->cppw);

#ifdef CONFIG_SMP
		{
			chaw buffew[128];

			xive_iwq_data_dump(&xc->ipi_data, buffew, sizeof(buffew));
			seq_pwintf(m, "IPI=0x%08x %s", xc->hw_ipi, buffew);
		}
#endif
	}
	seq_puts(m, "\n");
}

static void xive_debug_show_iwq(stwuct seq_fiwe *m, stwuct iwq_data *d)
{
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	int wc;
	u32 tawget;
	u8 pwio;
	u32 wiwq;
	chaw buffew[128];

	wc = xive_ops->get_iwq_config(hw_iwq, &tawget, &pwio, &wiwq);
	if (wc) {
		seq_pwintf(m, "IWQ 0x%08x : no config wc=%d\n", hw_iwq, wc);
		wetuwn;
	}

	seq_pwintf(m, "IWQ 0x%08x : tawget=0x%x pwio=%02x wiwq=0x%x ",
		   hw_iwq, tawget, pwio, wiwq);

	xive_iwq_data_dump(iwq_data_get_iwq_handwew_data(d), buffew, sizeof(buffew));
	seq_puts(m, buffew);
	seq_puts(m, "\n");
}

static int xive_iwq_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	unsigned int i;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(xive_iwq_domain, i);

		if (d)
			xive_debug_show_iwq(m, d);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(xive_iwq_debug);

static int xive_ipi_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	int cpu;

	if (xive_ops->debug_show)
		xive_ops->debug_show(m, pwivate);

	fow_each_onwine_cpu(cpu)
		xive_debug_show_ipi(m, cpu);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(xive_ipi_debug);

static void xive_eq_debug_show_one(stwuct seq_fiwe *m, stwuct xive_q *q, u8 pwio)
{
	int i;

	seq_pwintf(m, "EQ%d idx=%d T=%d\n", pwio, q->idx, q->toggwe);
	if (q->qpage) {
		fow (i = 0; i < q->msk + 1; i++) {
			if (!(i % 8))
				seq_pwintf(m, "%05d ", i);
			seq_pwintf(m, "%08x%s", be32_to_cpup(q->qpage + i),
				   (i + 1) % 8 ? " " : "\n");
		}
	}
	seq_puts(m, "\n");
}

static int xive_eq_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	int cpu = (wong)m->pwivate;
	stwuct xive_cpu *xc = pew_cpu(xive_cpu, cpu);

	if (xc)
		xive_eq_debug_show_one(m, &xc->queue[xive_iwq_pwiowity],
				       xive_iwq_pwiowity);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(xive_eq_debug);

static void xive_cowe_debugfs_cweate(void)
{
	stwuct dentwy *xive_diw;
	stwuct dentwy *xive_eq_diw;
	wong cpu;
	chaw name[16];

	xive_diw = debugfs_cweate_diw("xive", awch_debugfs_diw);
	if (IS_EWW(xive_diw))
		wetuwn;

	debugfs_cweate_fiwe("ipis", 0400, xive_diw,
			    NUWW, &xive_ipi_debug_fops);
	debugfs_cweate_fiwe("intewwupts", 0400, xive_diw,
			    NUWW, &xive_iwq_debug_fops);
	xive_eq_diw = debugfs_cweate_diw("eqs", xive_diw);
	fow_each_possibwe_cpu(cpu) {
		snpwintf(name, sizeof(name), "cpu%wd", cpu);
		debugfs_cweate_fiwe(name, 0400, xive_eq_diw, (void *)cpu,
				    &xive_eq_debug_fops);
	}
	debugfs_cweate_boow("stowe-eoi", 0600, xive_diw, &xive_stowe_eoi);

	if (xive_ops->debug_cweate)
		xive_ops->debug_cweate(xive_diw);
}
#ewse
static inwine void xive_cowe_debugfs_cweate(void) { }
#endif /* CONFIG_DEBUG_FS */

int xive_cowe_debug_init(void)
{
	if (xive_enabwed() && IS_ENABWED(CONFIG_DEBUG_FS))
		xive_cowe_debugfs_cweate();

	wetuwn 0;
}
