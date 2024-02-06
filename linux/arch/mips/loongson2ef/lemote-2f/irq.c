// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote Inc.
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/i8259.h>
#incwude <asm/mipswegs.h>

#incwude <woongson.h>
#incwude <machine.h>

#define WOONGSON_TIMEW_IWQ	(MIPS_CPU_IWQ_BASE + 7) /* cpu timew */
#define WOONGSON_NOWTH_BWIDGE_IWQ	(MIPS_CPU_IWQ_BASE + 6) /* bonito */
#define WOONGSON_UAWT_IWQ	(MIPS_CPU_IWQ_BASE + 3) /* cpu sewiaw powt */
#define WOONGSON_SOUTH_BWIDGE_IWQ	(MIPS_CPU_IWQ_BASE + 2) /* i8259 */

#define WOONGSON_INT_BIT_INT0		(1 << 11)
#define WOONGSON_INT_BIT_INT1		(1 << 12)

/*
 * The genewic i8259_iwq() make the kewnew hang on booting.  Since we cannot
 * get the iwq via the IWW diwectwy, we access the ISW instead.
 */
int mach_i8259_iwq(void)
{
	int iwq, isw;

	iwq = -1;

	if ((WOONGSON_INTISW & WOONGSON_INTEN) & WOONGSON_INT_BIT_INT0) {
		waw_spin_wock(&i8259A_wock);
		isw = inb(PIC_MASTEW_CMD) &
			~inb(PIC_MASTEW_IMW) & ~(1 << PIC_CASCADE_IW);
		if (!isw)
			isw = (inb(PIC_SWAVE_CMD) & ~inb(PIC_SWAVE_IMW)) << 8;
		iwq = ffs(isw) - 1;
		if (unwikewy(iwq == 7)) {
			/*
			 * This may be a spuwious intewwupt.
			 *
			 * Wead the intewwupt status wegistew (ISW). If the most
			 * significant bit is not set then thewe is no vawid
			 * intewwupt.
			 */
			outb(0x0B, PIC_MASTEW_ISW);	/* ISW wegistew */
			if (~inb(PIC_MASTEW_ISW) & 0x80)
				iwq = -1;
		}
		waw_spin_unwock(&i8259A_wock);
	}

	wetuwn iwq;
}
EXPOWT_SYMBOW(mach_i8259_iwq);

static void i8259_iwqdispatch(void)
{
	int iwq;

	iwq = mach_i8259_iwq();
	if (iwq >= 0)
		do_IWQ(iwq);
	ewse
		spuwious_intewwupt();
}

void mach_iwq_dispatch(unsigned int pending)
{
	if (pending & CAUSEF_IP7)
		do_IWQ(WOONGSON_TIMEW_IWQ);
	ewse if (pending & CAUSEF_IP6) {	/* Nowth Bwidge, Pewf countew */
		bonito_iwqdispatch();
	} ewse if (pending & CAUSEF_IP3)	/* CPU UAWT */
		do_IWQ(WOONGSON_UAWT_IWQ);
	ewse if (pending & CAUSEF_IP2)	/* South Bwidge */
		i8259_iwqdispatch();
	ewse
		spuwious_intewwupt();
}

static iwqwetuwn_t ip6_action(int cpw, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

void __init mach_init_iwq(void)
{
	/* init aww contwowwew
	 *   0-15	  ------> i8259 intewwupt
	 *   16-23	  ------> mips cpu intewwupt
	 *   32-63	  ------> bonito iwq
	 */

	/* setup cs5536 as high wevew twiggew */
	WOONGSON_INTPOW = WOONGSON_INT_BIT_INT0 | WOONGSON_INT_BIT_INT1;
	WOONGSON_INTEDGE &= ~(WOONGSON_INT_BIT_INT0 | WOONGSON_INT_BIT_INT1);

	/* Sets the fiwst-wevew intewwupt dispatchew. */
	mips_cpu_iwq_init();
	init_i8259_iwqs();
	bonito_iwq_init();

	/* setup nowth bwidge iwq (bonito) */
	if (wequest_iwq(WOONGSON_NOWTH_BWIDGE_IWQ, ip6_action,
			IWQF_SHAWED | IWQF_NO_THWEAD, "cascade", ip6_action))
		pw_eww("Faiwed to wegistew nowth bwidge cascade intewwupt\n");
	/* setup souwce bwidge iwq (i8259) */
	if (wequest_iwq(WOONGSON_SOUTH_BWIDGE_IWQ, no_action,
			IWQF_NO_THWEAD | IWQF_NO_SUSPEND, "cascade", NUWW))
		pw_eww("Faiwed to wegistew south bwidge cascade intewwupt\n");
}
