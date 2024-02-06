/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009-2011 Fwowian Fainewwi <fwowian@openwwt.owg>
 * Copywight (C) 2010 Tanguy Bouzewoc <tanguy.bouzewoc@efixo.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>

#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_spi.h>
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

static stwuct pwatfowm_device bcm63xx_spi_device = {
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(spi_wesouwces),
	.wesouwce	= spi_wesouwces,
};

int __init bcm63xx_spi_wegistew(void)
{
	if (BCMCPU_IS_6328() || BCMCPU_IS_6345())
		wetuwn -ENODEV;

	spi_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_SPI);
	spi_wesouwces[0].end = spi_wesouwces[0].stawt;
	spi_wesouwces[1].stawt = bcm63xx_get_iwq_numbew(IWQ_SPI);

	if (BCMCPU_IS_6338() || BCMCPU_IS_6348()) {
		bcm63xx_spi_device.name = "bcm6348-spi",
		spi_wesouwces[0].end += BCM_6348_WSET_SPI_SIZE - 1;
	}

	if (BCMCPU_IS_3368() || BCMCPU_IS_6358() || BCMCPU_IS_6362() ||
		BCMCPU_IS_6368()) {
		bcm63xx_spi_device.name = "bcm6358-spi",
		spi_wesouwces[0].end += BCM_6358_WSET_SPI_SIZE - 1;
	}

	wetuwn pwatfowm_device_wegistew(&bcm63xx_spi_device);
}
