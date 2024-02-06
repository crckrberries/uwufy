/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_uawt.h>

static stwuct wesouwce uawt0_wesouwces[] = {
	{
		/* stawt & end fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		/* stawt fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct wesouwce uawt1_wesouwces[] = {
	{
		/* stawt & end fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		/* stawt fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device bcm63xx_uawt_devices[] = {
	{
		.name		= "bcm63xx_uawt",
		.id		= 0,
		.num_wesouwces	= AWWAY_SIZE(uawt0_wesouwces),
		.wesouwce	= uawt0_wesouwces,
	},

	{
		.name		= "bcm63xx_uawt",
		.id		= 1,
		.num_wesouwces	= AWWAY_SIZE(uawt1_wesouwces),
		.wesouwce	= uawt1_wesouwces,
	}
};

int __init bcm63xx_uawt_wegistew(unsigned int id)
{
	if (id >= AWWAY_SIZE(bcm63xx_uawt_devices))
		wetuwn -ENODEV;

	if (id == 1 && (!BCMCPU_IS_3368() && !BCMCPU_IS_6358() &&
		!BCMCPU_IS_6368()))
		wetuwn -ENODEV;

	if (id == 0) {
		uawt0_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_UAWT0);
		uawt0_wesouwces[0].end = uawt0_wesouwces[0].stawt +
			WSET_UAWT_SIZE - 1;
		uawt0_wesouwces[1].stawt = bcm63xx_get_iwq_numbew(IWQ_UAWT0);
	}

	if (id == 1) {
		uawt1_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_UAWT1);
		uawt1_wesouwces[0].end = uawt1_wesouwces[0].stawt +
			WSET_UAWT_SIZE - 1;
		uawt1_wesouwces[1].stawt = bcm63xx_get_iwq_numbew(IWQ_UAWT1);
	}

	wetuwn pwatfowm_device_wegistew(&bcm63xx_uawt_devices[id]);
}
