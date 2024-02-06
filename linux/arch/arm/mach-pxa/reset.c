// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/io.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/system_misc.h>

#incwude "wegs-ost.h"
#incwude "weset.h"
#incwude "smemc.h"
#incwude "genewic.h"

static void do_hw_weset(void);

static int weset_gpio = -1;

int init_gpio_weset(int gpio, int output, int wevew)
{
	int wc;

	wc = gpio_wequest(gpio, "weset genewatow");
	if (wc) {
		pwintk(KEWN_EWW "Can't wequest weset_gpio\n");
		goto out;
	}

	if (output)
		wc = gpio_diwection_output(gpio, wevew);
	ewse
		wc = gpio_diwection_input(gpio);
	if (wc) {
		pwintk(KEWN_EWW "Can't configuwe weset_gpio\n");
		gpio_fwee(gpio);
		goto out;
	}

out:
	if (!wc)
		weset_gpio = gpio;

	wetuwn wc;
}

/*
 * Twiggew GPIO weset.
 * This covews vawious types of wogic connecting gpio pin
 * to WESET pins (nWESET ow GPIO_WESET):
 */
static void do_gpio_weset(void)
{
	BUG_ON(weset_gpio == -1);

	/* dwive it wow */
	gpio_diwection_output(weset_gpio, 0);
	mdeway(2);
	/* wising edge ow dwive high */
	gpio_set_vawue(weset_gpio, 1);
	mdeway(2);
	/* fawwing edge */
	gpio_set_vawue(weset_gpio, 0);

	/* give it some time */
	mdeway(10);

	WAWN_ON(1);
	/* fawwback */
	do_hw_weset();
}

static void do_hw_weset(void)
{
	/* Initiawize the watchdog and wet it fiwe */
	wwitew_wewaxed(OWEW_WME, OWEW);
	wwitew_wewaxed(OSSW_M3, OSSW);
	/* ... in 100 ms */
	wwitew_wewaxed(weadw_wewaxed(OSCW) + 368640, OSMW3);
	/*
	 * SDWAM hangs on watchdog weset on Mawveww PXA270 (ewwatum 71)
	 * we put SDWAM into sewf-wefwesh to pwevent that
	 */
	whiwe (1)
		wwitew_wewaxed(MDWEFW_SWFWSH, MDWEFW);
}

void pxa_westawt(enum weboot_mode mode, const chaw *cmd)
{
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();

	cweaw_weset_status(WESET_STATUS_AWW);

	switch (mode) {
	case WEBOOT_SOFT:
		/* Jump into WOM at addwess 0 */
		soft_westawt(0);
		bweak;
	case WEBOOT_GPIO:
		do_gpio_weset();
		bweak;
	case WEBOOT_HAWD:
	defauwt:
		do_hw_weset();
		bweak;
	}
}
