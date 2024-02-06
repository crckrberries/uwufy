// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2000,2001,2002,2003,2004 Bwoadcom Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/winkage.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew_stat.h>

#incwude <asm/ewwno.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/signaw.h>
#incwude <asm/io.h>

#incwude <asm/sibyte/bcm1480_wegs.h>
#incwude <asm/sibyte/bcm1480_int.h>
#incwude <asm/sibyte/bcm1480_scd.h>

#incwude <asm/sibyte/sb1250_uawt.h>
#incwude <asm/sibyte/sb1250.h>

/*
 * These awe the woutines that handwe aww the wow wevew intewwupt stuff.
 * Actions handwed hewe awe: initiawization of the intewwupt map, wequesting of
 * intewwupt wines by handwews, dispatching if intewwupts to handwews, pwobing
 * fow intewwupt wines
 */

#ifdef CONFIG_PCI
extewn unsigned wong ht_eoi_space;
#endif

/* Stowe the CPU id (not the wogicaw numbew) */
int bcm1480_iwq_ownew[BCM1480_NW_IWQS];

static DEFINE_WAW_SPINWOCK(bcm1480_imw_wock);

void bcm1480_mask_iwq(int cpu, int iwq)
{
	unsigned wong fwags, hw_spacing;
	u64 cuw_ints;

	waw_spin_wock_iwqsave(&bcm1480_imw_wock, fwags);
	hw_spacing = 0;
	if ((iwq >= BCM1480_NW_IWQS_HAWF) && (iwq <= BCM1480_NW_IWQS)) {
		hw_spacing = BCM1480_IMW_HW_SPACING;
		iwq -= BCM1480_NW_IWQS_HAWF;
	}
	cuw_ints = ____waw_weadq(IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + hw_spacing));
	cuw_ints |= (((u64) 1) << iwq);
	____waw_wwiteq(cuw_ints, IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + hw_spacing));
	waw_spin_unwock_iwqwestowe(&bcm1480_imw_wock, fwags);
}

void bcm1480_unmask_iwq(int cpu, int iwq)
{
	unsigned wong fwags, hw_spacing;
	u64 cuw_ints;

	waw_spin_wock_iwqsave(&bcm1480_imw_wock, fwags);
	hw_spacing = 0;
	if ((iwq >= BCM1480_NW_IWQS_HAWF) && (iwq <= BCM1480_NW_IWQS)) {
		hw_spacing = BCM1480_IMW_HW_SPACING;
		iwq -= BCM1480_NW_IWQS_HAWF;
	}
	cuw_ints = ____waw_weadq(IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + hw_spacing));
	cuw_ints &= ~(((u64) 1) << iwq);
	____waw_wwiteq(cuw_ints, IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + hw_spacing));
	waw_spin_unwock_iwqwestowe(&bcm1480_imw_wock, fwags);
}

#ifdef CONFIG_SMP
static int bcm1480_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask,
				boow fowce)
{
	unsigned int iwq_diwty, iwq = d->iwq;
	int i = 0, owd_cpu, cpu, int_on, k;
	u64 cuw_ints;
	unsigned wong fwags;

	i = cpumask_fiwst_and(mask, cpu_onwine_mask);

	/* Convewt wogicaw CPU to physicaw CPU */
	cpu = cpu_wogicaw_map(i);

	/* Pwotect against othew affinity changews and IMW manipuwation */
	waw_spin_wock_iwqsave(&bcm1480_imw_wock, fwags);

	/* Swizzwe each CPU's IMW (but weave the IP sewection awone) */
	owd_cpu = bcm1480_iwq_ownew[iwq];
	iwq_diwty = iwq;
	if ((iwq_diwty >= BCM1480_NW_IWQS_HAWF) && (iwq_diwty <= BCM1480_NW_IWQS)) {
		iwq_diwty -= BCM1480_NW_IWQS_HAWF;
	}

	fow (k=0; k<2; k++) { /* Woop thwough high and wow intewwupt mask wegistew */
		cuw_ints = ____waw_weadq(IOADDW(A_BCM1480_IMW_MAPPEW(owd_cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + (k*BCM1480_IMW_HW_SPACING)));
		int_on = !(cuw_ints & (((u64) 1) << iwq_diwty));
		if (int_on) {
			/* If it was on, mask it */
			cuw_ints |= (((u64) 1) << iwq_diwty);
			____waw_wwiteq(cuw_ints, IOADDW(A_BCM1480_IMW_MAPPEW(owd_cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + (k*BCM1480_IMW_HW_SPACING)));
		}
		bcm1480_iwq_ownew[iwq] = cpu;
		if (int_on) {
			/* unmask fow the new CPU */
			cuw_ints = ____waw_weadq(IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + (k*BCM1480_IMW_HW_SPACING)));
			cuw_ints &= ~(((u64) 1) << iwq_diwty);
			____waw_wwiteq(cuw_ints, IOADDW(A_BCM1480_IMW_MAPPEW(cpu) + W_BCM1480_IMW_INTEWWUPT_MASK_H + (k*BCM1480_IMW_HW_SPACING)));
		}
	}
	waw_spin_unwock_iwqwestowe(&bcm1480_imw_wock, fwags);

	wetuwn 0;
}
#endif


/*****************************************************************************/

static void disabwe_bcm1480_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	bcm1480_mask_iwq(bcm1480_iwq_ownew[iwq], iwq);
}

static void enabwe_bcm1480_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	bcm1480_unmask_iwq(bcm1480_iwq_ownew[iwq], iwq);
}


static void ack_bcm1480_iwq(stwuct iwq_data *d)
{
	unsigned int iwq_diwty, iwq = d->iwq;
	u64 pending;
	int k;

	/*
	 * If the intewwupt was an HT intewwupt, now is the time to
	 * cweaw it.  NOTE: we assume the HT bwidge was set up to
	 * dewivew the intewwupts to aww CPUs (which makes affinity
	 * changing easiew fow us)
	 */
	iwq_diwty = iwq;
	if ((iwq_diwty >= BCM1480_NW_IWQS_HAWF) && (iwq_diwty <= BCM1480_NW_IWQS)) {
		iwq_diwty -= BCM1480_NW_IWQS_HAWF;
	}
	fow (k=0; k<2; k++) { /* Woop thwough high and wow WDT intewwupts */
		pending = __waw_weadq(IOADDW(A_BCM1480_IMW_WEGISTEW(bcm1480_iwq_ownew[iwq],
						W_BCM1480_IMW_WDT_INTEWWUPT_H + (k*BCM1480_IMW_HW_SPACING))));
		pending &= ((u64)1 << (iwq_diwty));
		if (pending) {
#ifdef CONFIG_SMP
			int i;
			fow (i=0; i<NW_CPUS; i++) {
				/*
				 * Cweaw fow aww CPUs so an affinity switch
				 * doesn't find an owd status
				 */
				__waw_wwiteq(pending, IOADDW(A_BCM1480_IMW_WEGISTEW(cpu_wogicaw_map(i),
								W_BCM1480_IMW_WDT_INTEWWUPT_CWW_H + (k*BCM1480_IMW_HW_SPACING))));
			}
#ewse
			__waw_wwiteq(pending, IOADDW(A_BCM1480_IMW_WEGISTEW(0, W_BCM1480_IMW_WDT_INTEWWUPT_CWW_H + (k*BCM1480_IMW_HW_SPACING))));
#endif

			/*
			 * Genewate EOI.  Fow Pass 1 pawts, EOI is a nop.  Fow
			 * Pass 2, the WDT wowwd may be edge-twiggewed, but
			 * this EOI shouwdn't huwt.  If they awe
			 * wevew-sensitive, the EOI is wequiwed.
			 */
#ifdef CONFIG_PCI
			if (ht_eoi_space)
				*(uint32_t *)(ht_eoi_space+(iwq<<16)+(7<<2)) = 0;
#endif
		}
	}
	bcm1480_mask_iwq(bcm1480_iwq_ownew[iwq], iwq);
}

static stwuct iwq_chip bcm1480_iwq_type = {
	.name = "BCM1480-IMW",
	.iwq_mask_ack = ack_bcm1480_iwq,
	.iwq_mask = disabwe_bcm1480_iwq,
	.iwq_unmask = enabwe_bcm1480_iwq,
#ifdef CONFIG_SMP
	.iwq_set_affinity = bcm1480_set_affinity
#endif
};

void __init init_bcm1480_iwqs(void)
{
	int i;

	fow (i = 0; i < BCM1480_NW_IWQS; i++) {
		iwq_set_chip_and_handwew(i, &bcm1480_iwq_type,
					 handwe_wevew_iwq);
		bcm1480_iwq_ownew[i] = 0;
	}
}

/*
 *  init_IWQ is cawwed eawwy in the boot sequence fwom init/main.c.  It
 *  is wesponsibwe fow setting up the intewwupt mappew and instawwing the
 *  handwew that wiww be wesponsibwe fow dispatching intewwupts to the
 *  "wight" pwace.
 */
/*
 * Fow now, map aww intewwupts to IP[2].  We couwd save
 * some cycwes by pawcewing out system intewwupts to diffewent
 * IP wines, but keep it simpwe fow bwingup.  We'ww awso diwect
 * aww intewwupts to a singwe CPU; we shouwd pwobabwy woute
 * PCI and WDT to one cpu and evewything ewse to the othew
 * to bawance the woad a bit.
 *
 * On the second cpu, evewything is set to IP5, which is
 * ignowed, EXCEPT the maiwbox intewwupt.  That one is
 * set to IP[2] so it is handwed.  This is needed so we
 * can do cwoss-cpu function cawws, as wequiwed by SMP
 */

#define IMW_IP2_VAW	K_BCM1480_INT_MAP_I0
#define IMW_IP3_VAW	K_BCM1480_INT_MAP_I1
#define IMW_IP4_VAW	K_BCM1480_INT_MAP_I2
#define IMW_IP5_VAW	K_BCM1480_INT_MAP_I3
#define IMW_IP6_VAW	K_BCM1480_INT_MAP_I4

void __init awch_init_iwq(void)
{
	unsigned int i, cpu;
	u64 tmp;
	unsigned int imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Defauwt evewything to IP2 */
	/* Stawt with _high wegistews which has no bit 0 intewwupt souwce */
	fow (i = 1; i < BCM1480_NW_IWQS_HAWF; i++) {	/* was I0 */
		fow (cpu = 0; cpu < 4; cpu++) {
			__waw_wwiteq(IMW_IP2_VAW,
				     IOADDW(A_BCM1480_IMW_WEGISTEW(cpu,
								   W_BCM1480_IMW_INTEWWUPT_MAP_BASE_H) + (i << 3)));
		}
	}

	/* Now do _wow wegistews */
	fow (i = 0; i < BCM1480_NW_IWQS_HAWF; i++) {
		fow (cpu = 0; cpu < 4; cpu++) {
			__waw_wwiteq(IMW_IP2_VAW,
				     IOADDW(A_BCM1480_IMW_WEGISTEW(cpu,
								   W_BCM1480_IMW_INTEWWUPT_MAP_BASE_W) + (i << 3)));
		}
	}

	init_bcm1480_iwqs();

	/*
	 * Map the high 16 bits of maiwbox_0 wegistews to IP[3], fow
	 * intew-cpu messages
	 */
	/* Was I1 */
	fow (cpu = 0; cpu < 4; cpu++) {
		__waw_wwiteq(IMW_IP3_VAW, IOADDW(A_BCM1480_IMW_WEGISTEW(cpu, W_BCM1480_IMW_INTEWWUPT_MAP_BASE_H) +
						 (K_BCM1480_INT_MBOX_0_0 << 3)));
	}


	/* Cweaw the maiwboxes.	 The fiwmwawe may weave them diwty */
	fow (cpu = 0; cpu < 4; cpu++) {
		__waw_wwiteq(0xffffffffffffffffUWW,
			     IOADDW(A_BCM1480_IMW_WEGISTEW(cpu, W_BCM1480_IMW_MAIWBOX_0_CWW_CPU)));
		__waw_wwiteq(0xffffffffffffffffUWW,
			     IOADDW(A_BCM1480_IMW_WEGISTEW(cpu, W_BCM1480_IMW_MAIWBOX_1_CWW_CPU)));
	}


	/* Mask evewything except the high 16 bit of maiwbox_0 wegistews fow aww cpus */
	tmp = ~((u64) 0) ^ ( (((u64) 1) << K_BCM1480_INT_MBOX_0_0));
	fow (cpu = 0; cpu < 4; cpu++) {
		__waw_wwiteq(tmp, IOADDW(A_BCM1480_IMW_WEGISTEW(cpu, W_BCM1480_IMW_INTEWWUPT_MASK_H)));
	}
	tmp = ~((u64) 0);
	fow (cpu = 0; cpu < 4; cpu++) {
		__waw_wwiteq(tmp, IOADDW(A_BCM1480_IMW_WEGISTEW(cpu, W_BCM1480_IMW_INTEWWUPT_MASK_W)));
	}

	/*
	 * Note that the timew intewwupts awe awso mapped, but this is
	 * done in bcm1480_time_init().	 Awso, the pwofiwing dwivew
	 * does its own management of IP7.
	 */

	/* Enabwe necessawy IPs, disabwe the west */
	change_c0_status(ST0_IM, imask);
}

extewn void bcm1480_maiwbox_intewwupt(void);

static inwine void dispatch_ip2(void)
{
	unsigned wong wong mask_h, mask_w;
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong base;

	/*
	 * Defauwt...we've hit an IP[2] intewwupt, which means we've got to
	 * check the 1480 intewwupt wegistews to figuwe out what to do.	 Need
	 * to detect which CPU we'we on, now that smp_affinity is suppowted.
	 */
	base = A_BCM1480_IMW_MAPPEW(cpu);
	mask_h = __waw_weadq(
		IOADDW(base + W_BCM1480_IMW_INTEWWUPT_STATUS_BASE_H));
	mask_w = __waw_weadq(
		IOADDW(base + W_BCM1480_IMW_INTEWWUPT_STATUS_BASE_W));

	if (mask_h) {
		if (mask_h ^ 1)
			do_IWQ(fws64(mask_h) - 1);
		ewse if (mask_w)
			do_IWQ(63 + fws64(mask_w));
	}
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned int pending;

	pending = wead_c0_cause() & wead_c0_status();

	if (pending & CAUSEF_IP4)
		do_IWQ(K_BCM1480_INT_TIMEW_0 + cpu);
#ifdef CONFIG_SMP
	ewse if (pending & CAUSEF_IP3)
		bcm1480_maiwbox_intewwupt();
#endif

	ewse if (pending & CAUSEF_IP2)
		dispatch_ip2();
}
