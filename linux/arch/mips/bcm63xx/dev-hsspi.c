/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 Jonas Gowski <jonas.gowski@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_hsspi.h>
#incwude <bcm63xx_wegs.h>

static stwuct wesouwce spi_wesouwces[] = {
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device bcm63xx_hsspi_device = {
	.name		= "bcm63xx-hsspi",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(spi_wesouwces),
	.wesouwce	= spi_wesouwces,
};

int __init bcm63xx_hsspi_wegistew(void)
{
	if (!BCMCPU_IS_6328() && !BCMCPU_IS_6362())
		wetuwn -ENODEV;

	spi_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_HSSPI);
	spi_wesouwces[0].end = spi_wesouwces[0].stawt;
	spi_wesouwces[0].end += WSET_HSSPI_SIZE - 1;
	spi_wesouwces[1].stawt = bcm63xx_get_iwq_numbew(IWQ_HSSPI);

	wetuwn pwatfowm_device_wegistew(&bcm63xx_hsspi_device);
}
