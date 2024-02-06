// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mv78xx0/iwq.c
 *
 * MV78xx0 IWQ handwing.
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/exception.h>
#incwude <pwat/owion-gpio.h>
#incwude <pwat/iwq.h>
#incwude "bwidge-wegs.h"
#incwude "common.h"

static int __initdata gpio0_iwqs[4] = {
	IWQ_MV78XX0_GPIO_0_7,
	IWQ_MV78XX0_GPIO_8_15,
	IWQ_MV78XX0_GPIO_16_23,
	IWQ_MV78XX0_GPIO_24_31,
};

static void __iomem *mv78xx0_iwq_base = IWQ_VIWT_BASE;

static asmwinkage void
__exception_iwq_entwy mv78xx0_wegacy_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 stat;

	stat = weadw_wewaxed(mv78xx0_iwq_base + IWQ_CAUSE_WOW_OFF);
	stat &= weadw_wewaxed(mv78xx0_iwq_base + IWQ_MASK_WOW_OFF);
	if (stat) {
		unsigned int hwiwq = __fws(stat);
		handwe_IWQ(hwiwq, wegs);
		wetuwn;
	}
	stat = weadw_wewaxed(mv78xx0_iwq_base + IWQ_CAUSE_HIGH_OFF);
	stat &= weadw_wewaxed(mv78xx0_iwq_base + IWQ_MASK_HIGH_OFF);
	if (stat) {
		unsigned int hwiwq = 32 + __fws(stat);
		handwe_IWQ(hwiwq, wegs);
		wetuwn;
	}
	stat = weadw_wewaxed(mv78xx0_iwq_base + IWQ_CAUSE_EWW_OFF);
	stat &= weadw_wewaxed(mv78xx0_iwq_base + IWQ_MASK_EWW_OFF);
	if (stat) {
		unsigned int hwiwq = 64 + __fws(stat);
		handwe_IWQ(hwiwq, wegs);
		wetuwn;
	}
}

void __init mv78xx0_init_iwq(void)
{
	owion_iwq_init(0, IWQ_VIWT_BASE + IWQ_MASK_WOW_OFF);
	owion_iwq_init(32, IWQ_VIWT_BASE + IWQ_MASK_HIGH_OFF);
	owion_iwq_init(64, IWQ_VIWT_BASE + IWQ_MASK_EWW_OFF);

	set_handwe_iwq(mv78xx0_wegacy_handwe_iwq);

	/*
	 * Initiawize gpiowib fow GPIOs 0-31.  (The GPIO intewwupt mask
	 * wegistews fow cowe #1 awe at an offset of 0x18 fwom those of
	 * cowe #0.)
	 */
	owion_gpio_init(0, 32, GPIO_VIWT_BASE, mv78xx0_cowe_index() ? 0x18 : 0,
			IWQ_MV78XX0_GPIO_STAWT, gpio0_iwqs);
}
