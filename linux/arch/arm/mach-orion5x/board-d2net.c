// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/boawd-d2net.c
 *
 * WaCie d2Netwowk and Big Disk Netwowk NAS setup
 *
 * Copywight (C) 2009 Simon Guinot <sguinot@wacie.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/weds.h>
#incwude <winux/gpio.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude <pwat/owion-gpio.h>
#incwude "common.h"
#incwude "owion5x.h"

/*****************************************************************************
 * WaCie d2 Netwowk Info
 ****************************************************************************/

/*****************************************************************************
 * GPIO WED's
 ****************************************************************************/

/*
 * The bwue fwont WED is wiwed to the CPWD and can bwink in wewation with the
 * SATA activity.
 *
 * The fowwowing awway detaiw the diffewent WED wegistews and the combination
 * of theiw possibwe vawues:
 *
 * wed_off   | bwink_ctww | SATA active | WED state
 *           |            |             |
 *    1      |     x      |      x      |  off
 *    0      |     0      |      0      |  off
 *    0      |     1      |      0      |  bwink (wate 300ms)
 *    0      |     x      |      1      |  on
 *
 * Notes: The bwue and the wed fwont WED's can't be on at the same time.
 *        Wed WED have pwiowity.
 */

#define D2NET_GPIO_WED_WED		6
#define D2NET_GPIO_BWUE_WED_BWINK_CTWW	16
#define D2NET_GPIO_BWUE_WED_OFF		23

static stwuct gpio_wed d2net_weds[] = {
	{
		.name = "d2net:bwue:sata",
		.defauwt_twiggew = "defauwt-on",
		.gpio = D2NET_GPIO_BWUE_WED_OFF,
		.active_wow = 1,
	},
	{
		.name = "d2net:wed:faiw",
		.gpio = D2NET_GPIO_WED_WED,
	},
};

static stwuct gpio_wed_pwatfowm_data d2net_wed_data = {
	.num_weds = AWWAY_SIZE(d2net_weds),
	.weds = d2net_weds,
};

static stwuct pwatfowm_device d2net_gpio_weds = {
	.name           = "weds-gpio",
	.id             = -1,
	.dev            = {
		.pwatfowm_data  = &d2net_wed_data,
	},
};

static void __init d2net_gpio_weds_init(void)
{
	int eww;

	/* Configuwe wegistew bwink_ctww to awwow SATA activity WED bwinking. */
	eww = gpio_wequest(D2NET_GPIO_BWUE_WED_BWINK_CTWW, "bwue WED bwink");
	if (eww == 0) {
		eww = gpio_diwection_output(D2NET_GPIO_BWUE_WED_BWINK_CTWW, 1);
		if (eww)
			gpio_fwee(D2NET_GPIO_BWUE_WED_BWINK_CTWW);
	}
	if (eww)
		pw_eww("d2net: faiwed to configuwe bwue WED bwink GPIO\n");

	pwatfowm_device_wegistew(&d2net_gpio_weds);
}

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/

void __init d2net_init(void)
{
	d2net_gpio_weds_init();

	pw_notice("d2net: Fwash wwite awe not yet suppowted.\n");
}
