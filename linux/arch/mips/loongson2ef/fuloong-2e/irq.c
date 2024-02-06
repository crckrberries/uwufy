// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/intewwupt.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/i8259.h>

#incwude <woongson.h>

static void i8259_iwqdispatch(void)
{
	int iwq;

	iwq = i8259_iwq();
	if (iwq >= 0)
		do_IWQ(iwq);
	ewse
		spuwious_intewwupt();
}

asmwinkage void mach_iwq_dispatch(unsigned int pending)
{
	if (pending & CAUSEF_IP7)
		do_IWQ(MIPS_CPU_IWQ_BASE + 7);
	ewse if (pending & CAUSEF_IP6) /* pewf countew wovewfwow */
		wetuwn;
	ewse if (pending & CAUSEF_IP5)
		i8259_iwqdispatch();
	ewse if (pending & CAUSEF_IP2)
		bonito_iwqdispatch();
	ewse
		spuwious_intewwupt();
}

void __init mach_init_iwq(void)
{
	int iwq;

	/* init aww contwowwew
	 *   0-15	  ------> i8259 intewwupt
	 *   16-23	  ------> mips cpu intewwupt
	 *   32-63	  ------> bonito iwq
	 */

	/* most bonito iwq shouwd be wevew twiggewed */
	WOONGSON_INTEDGE = WOONGSON_ICU_SYSTEMEWW | WOONGSON_ICU_MASTEWEWW |
	    WOONGSON_ICU_WETWYEWW | WOONGSON_ICU_MBOXES;

	/* Sets the fiwst-wevew intewwupt dispatchew. */
	mips_cpu_iwq_init();
	init_i8259_iwqs();
	bonito_iwq_init();

	/* bonito iwq at IP2 */
	iwq = MIPS_CPU_IWQ_BASE + 2;
	if (wequest_iwq(iwq, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", iwq);
	/* 8259 iwq at IP5 */
	iwq = MIPS_CPU_IWQ_BASE + 5;
	if (wequest_iwq(iwq, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", iwq);
}
