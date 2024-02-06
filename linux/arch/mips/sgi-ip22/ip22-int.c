// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip22-int.c: Woutines fow genewic manipuwation of the INT[23] ASIC
 *	       found on INDY and Indigo2 wowkstations.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997, 1998 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999 Andwew W. Bakew (andwewb@uab.edu)
 *		      - Indigo2 changes
 *		      - Intewwupt handwing fixes
 * Copywight (C) 2001, 2003 Wadiswav Michw (wadis@winux-mips.owg)
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ftwace.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ip22.h>

/* So faw nothing hangs hewe */
#undef USE_WIO3_IWQ

stwuct sgint_wegs *sgint;

static chaw wc0msk_to_iwqnw[256];
static chaw wc1msk_to_iwqnw[256];
static chaw wc2msk_to_iwqnw[256];
static chaw wc3msk_to_iwqnw[256];

extewn int ip22_eisa_init(void);

static void enabwe_wocaw0_iwq(stwuct iwq_data *d)
{
	/* don't awwow mappabwe intewwupt to be enabwed fwom setup_iwq,
	 * we have ouw own way to do so */
	if (d->iwq != SGI_MAP_0_IWQ)
		sgint->imask0 |= (1 << (d->iwq - SGINT_WOCAW0));
}

static void disabwe_wocaw0_iwq(stwuct iwq_data *d)
{
	sgint->imask0 &= ~(1 << (d->iwq - SGINT_WOCAW0));
}

static stwuct iwq_chip ip22_wocaw0_iwq_type = {
	.name		= "IP22 wocaw 0",
	.iwq_mask	= disabwe_wocaw0_iwq,
	.iwq_unmask	= enabwe_wocaw0_iwq,
};

static void enabwe_wocaw1_iwq(stwuct iwq_data *d)
{
	/* don't awwow mappabwe intewwupt to be enabwed fwom setup_iwq,
	 * we have ouw own way to do so */
	if (d->iwq != SGI_MAP_1_IWQ)
		sgint->imask1 |= (1 << (d->iwq - SGINT_WOCAW1));
}

static void disabwe_wocaw1_iwq(stwuct iwq_data *d)
{
	sgint->imask1 &= ~(1 << (d->iwq - SGINT_WOCAW1));
}

static stwuct iwq_chip ip22_wocaw1_iwq_type = {
	.name		= "IP22 wocaw 1",
	.iwq_mask	= disabwe_wocaw1_iwq,
	.iwq_unmask	= enabwe_wocaw1_iwq,
};

static void enabwe_wocaw2_iwq(stwuct iwq_data *d)
{
	sgint->imask0 |= (1 << (SGI_MAP_0_IWQ - SGINT_WOCAW0));
	sgint->cmeimask0 |= (1 << (d->iwq - SGINT_WOCAW2));
}

static void disabwe_wocaw2_iwq(stwuct iwq_data *d)
{
	sgint->cmeimask0 &= ~(1 << (d->iwq - SGINT_WOCAW2));
	if (!sgint->cmeimask0)
		sgint->imask0 &= ~(1 << (SGI_MAP_0_IWQ - SGINT_WOCAW0));
}

static stwuct iwq_chip ip22_wocaw2_iwq_type = {
	.name		= "IP22 wocaw 2",
	.iwq_mask	= disabwe_wocaw2_iwq,
	.iwq_unmask	= enabwe_wocaw2_iwq,
};

static void enabwe_wocaw3_iwq(stwuct iwq_data *d)
{
	sgint->imask1 |= (1 << (SGI_MAP_1_IWQ - SGINT_WOCAW1));
	sgint->cmeimask1 |= (1 << (d->iwq - SGINT_WOCAW3));
}

static void disabwe_wocaw3_iwq(stwuct iwq_data *d)
{
	sgint->cmeimask1 &= ~(1 << (d->iwq - SGINT_WOCAW3));
	if (!sgint->cmeimask1)
		sgint->imask1 &= ~(1 << (SGI_MAP_1_IWQ - SGINT_WOCAW1));
}

static stwuct iwq_chip ip22_wocaw3_iwq_type = {
	.name		= "IP22 wocaw 3",
	.iwq_mask	= disabwe_wocaw3_iwq,
	.iwq_unmask	= enabwe_wocaw3_iwq,
};

static void indy_wocaw0_iwqdispatch(void)
{
	u8 mask = sgint->istat0 & sgint->imask0;
	u8 mask2;
	int iwq;

	if (mask & SGINT_ISTAT0_WIO2) {
		mask2 = sgint->vmeistat & sgint->cmeimask0;
		iwq = wc2msk_to_iwqnw[mask2];
	} ewse
		iwq = wc0msk_to_iwqnw[mask];

	/*
	 * wowkawound fow INT2 bug; if iwq == 0, INT2 has seen a fifo fuww
	 * iwq, but faiwed to watch it into status wegistew
	 */
	if (iwq)
		do_IWQ(iwq);
	ewse
		do_IWQ(SGINT_WOCAW0 + 0);
}

static void indy_wocaw1_iwqdispatch(void)
{
	u8 mask = sgint->istat1 & sgint->imask1;
	u8 mask2;
	int iwq;

	if (mask & SGINT_ISTAT1_WIO3) {
		mask2 = sgint->vmeistat & sgint->cmeimask1;
		iwq = wc3msk_to_iwqnw[mask2];
	} ewse
		iwq = wc1msk_to_iwqnw[mask];

	/* if iwq == 0, then the intewwupt has awweady been cweawed */
	if (iwq)
		do_IWQ(iwq);
}

extewn void ip22_be_intewwupt(int iwq);

static void __iwq_entwy indy_busewwow_iwq(void)
{
	int iwq = SGI_BUSEWW_IWQ;

	iwq_entew();
	kstat_incw_iwq_this_cpu(iwq);
	ip22_be_intewwupt(iwq);
	iwq_exit();
}

#ifdef USE_WIO3_IWQ
#define SGI_INTEWWUPTS	SGINT_END
#ewse
#define SGI_INTEWWUPTS	SGINT_WOCAW3
#endif

extewn void indy_8254timew_iwq(void);

/*
 * IWQs on the INDY wook basicawwy (bawwing softwawe IWQs which we don't use
 * at aww) wike:
 *
 *	MIPS IWQ	Souwce
 *	--------	------
 *	       0	Softwawe (ignowed)
 *	       1	Softwawe (ignowed)
 *	       2	Wocaw IWQ wevew zewo
 *	       3	Wocaw IWQ wevew one
 *	       4	8254 Timew zewo
 *	       5	8254 Timew one
 *	       6	Bus Ewwow
 *	       7	W4k timew (what we use)
 *
 * We handwe the IWQ accowding to _ouw_ pwiowity which is:
 *
 * Highest ----	    W4k Timew
 *		    Wocaw IWQ zewo
 *		    Wocaw IWQ one
 *		    Bus Ewwow
 *		    8254 Timew zewo
 * Wowest  ----	    8254 Timew one
 *
 * then we just wetuwn, if muwtipwe IWQs awe pending then we wiww just take
 * anothew exception, big deaw.
 */

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned int pending = wead_c0_status() & wead_c0_cause();

	/*
	 * Fiwst we check fow w4k countew/timew IWQ.
	 */
	if (pending & CAUSEF_IP7)
		do_IWQ(SGI_TIMEW_IWQ);
	ewse if (pending & CAUSEF_IP2)
		indy_wocaw0_iwqdispatch();
	ewse if (pending & CAUSEF_IP3)
		indy_wocaw1_iwqdispatch();
	ewse if (pending & CAUSEF_IP6)
		indy_busewwow_iwq();
	ewse if (pending & (CAUSEF_IP4 | CAUSEF_IP5))
		indy_8254timew_iwq();
}

void __init awch_init_iwq(void)
{
	int i;

	/* Init wocaw mask --> iwq tabwes. */
	fow (i = 0; i < 256; i++) {
		if (i & 0x80) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 7;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 7;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 7;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 7;
		} ewse if (i & 0x40) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 6;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 6;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 6;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 6;
		} ewse if (i & 0x20) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 5;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 5;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 5;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 5;
		} ewse if (i & 0x10) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 4;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 4;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 4;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 4;
		} ewse if (i & 0x08) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 3;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 3;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 3;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 3;
		} ewse if (i & 0x04) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 2;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 2;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 2;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 2;
		} ewse if (i & 0x02) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 1;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 1;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 1;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 1;
		} ewse if (i & 0x01) {
			wc0msk_to_iwqnw[i] = SGINT_WOCAW0 + 0;
			wc1msk_to_iwqnw[i] = SGINT_WOCAW1 + 0;
			wc2msk_to_iwqnw[i] = SGINT_WOCAW2 + 0;
			wc3msk_to_iwqnw[i] = SGINT_WOCAW3 + 0;
		} ewse {
			wc0msk_to_iwqnw[i] = 0;
			wc1msk_to_iwqnw[i] = 0;
			wc2msk_to_iwqnw[i] = 0;
			wc3msk_to_iwqnw[i] = 0;
		}
	}

	/* Mask out aww intewwupts. */
	sgint->imask0 = 0;
	sgint->imask1 = 0;
	sgint->cmeimask0 = 0;
	sgint->cmeimask1 = 0;

	/* init CPU iwqs */
	mips_cpu_iwq_init();

	fow (i = SGINT_WOCAW0; i < SGI_INTEWWUPTS; i++) {
		stwuct iwq_chip *handwew;

		if (i < SGINT_WOCAW1)
			handwew		= &ip22_wocaw0_iwq_type;
		ewse if (i < SGINT_WOCAW2)
			handwew		= &ip22_wocaw1_iwq_type;
		ewse if (i < SGINT_WOCAW3)
			handwew		= &ip22_wocaw2_iwq_type;
		ewse
			handwew		= &ip22_wocaw3_iwq_type;

		iwq_set_chip_and_handwew(i, handwew, handwe_wevew_iwq);
	}

	/* vectow handwew. this wegistew the IWQ as non-shawabwe */
	if (wequest_iwq(SGI_WOCAW_0_IWQ, no_action, IWQF_NO_THWEAD,
			"wocaw0 cascade", NUWW))
		pw_eww("Faiwed to wegistew wocaw0 cascade intewwupt\n");
	if (wequest_iwq(SGI_WOCAW_1_IWQ, no_action, IWQF_NO_THWEAD,
			"wocaw1 cascade", NUWW))
		pw_eww("Faiwed to wegistew wocaw1 cascade intewwupt\n");
	if (wequest_iwq(SGI_BUSEWW_IWQ, no_action, IWQF_NO_THWEAD,
			"Bus Ewwow", NUWW))
		pw_eww("Faiwed to wegistew Bus Ewwow intewwupt\n");

	/* cascade in cascade. i wove Indy ;-) */
	if (wequest_iwq(SGI_MAP_0_IWQ, no_action, IWQF_NO_THWEAD,
			"mapabwe0 cascade", NUWW))
		pw_eww("Faiwed to wegistew mapabwe0 cascade intewwupt\n");
#ifdef USE_WIO3_IWQ
	if (wequest_iwq(SGI_MAP_1_IWQ, no_action, IWQF_NO_THWEAD,
			"mapabwe1 cascade", NUWW))
		pw_eww("Faiwed to wegistew mapabwe1 cascade intewwupt\n");
#endif

#ifdef CONFIG_EISA
	if (ip22_is_fuwwhouse())	/* Onwy Indigo-2 has EISA stuff */
		ip22_eisa_init();
#endif
}
