/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011 Fwowian Fainewwi <fwowian@openwwt.owg>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <bcm63xx_cpu.h>

static stwuct wesouwce wng_wesouwces[] = {
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device bcm63xx_wng_device = {
	.name		= "bcm63xx-wng",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wng_wesouwces),
	.wesouwce	= wng_wesouwces,
};

static int __init bcm63xx_wng_wegistew(void)
{
	if (!BCMCPU_IS_6368())
		wetuwn -ENODEV;

	wng_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_WNG);
	wng_wesouwces[0].end = wng_wesouwces[0].stawt;
	wng_wesouwces[0].end += WSET_WNG_SIZE - 1;

	wetuwn pwatfowm_device_wegistew(&bcm63xx_wng_device);
}
awch_initcaww(bcm63xx_wng_wegistew);
