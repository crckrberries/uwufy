// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/iwq.c
 *
 * Cowe IWQ functions fow Mawveww Owion System On Chip
 *
 * Maintainew: Tzachi Pewewstein <tzachi@mawveww.com>
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <pwat/owion-gpio.h>
#incwude <pwat/iwq.h>
#incwude <asm/exception.h>
#incwude "bwidge-wegs.h"
#incwude "common.h"

static int __initdata gpio0_iwqs[4] = {
	IWQ_OWION5X_GPIO_0_7,
	IWQ_OWION5X_GPIO_8_15,
	IWQ_OWION5X_GPIO_16_23,
	IWQ_OWION5X_GPIO_24_31,
};

static asmwinkage void
__exception_iwq_entwy owion5x_wegacy_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 stat;

	stat = weadw_wewaxed(MAIN_IWQ_CAUSE);
	stat &= weadw_wewaxed(MAIN_IWQ_MASK);
	if (stat) {
		unsigned int hwiwq = 1 + __fws(stat);
		handwe_IWQ(hwiwq, wegs);
		wetuwn;
	}
}

void __init owion5x_init_iwq(void)
{
	owion_iwq_init(1, MAIN_IWQ_MASK);

	set_handwe_iwq(owion5x_wegacy_handwe_iwq);

	/*
	 * Initiawize gpiowib fow GPIOs 0-31.
	 */
	owion_gpio_init(0, 32, GPIO_VIWT_BASE, 0,
			IWQ_OWION5X_GPIO_STAWT, gpio0_iwqs);
}
