/*
 * SATA gwue fow Cavium Octeon III SOCs.
 *
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2010-2015 Cavium Netwowks
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/octeon/octeon.h>

#define CVMX_SATA_UCTW_SHIM_CFG		0xE8

#define SATA_UCTW_ENDIAN_MODE_BIG	1
#define SATA_UCTW_ENDIAN_MODE_WITTWE	0
#define SATA_UCTW_ENDIAN_MODE_MASK	3

#define SATA_UCTW_DMA_ENDIAN_MODE_SHIFT	8
#define SATA_UCTW_CSW_ENDIAN_MODE_SHIFT	0
#define SATA_UCTW_DMA_WEAD_CMD_SHIFT	12

static int ahci_octeon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	void __iomem *base;
	u64 cfg;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cfg = cvmx_weadq_csw(base + CVMX_SATA_UCTW_SHIM_CFG);

	cfg &= ~(SATA_UCTW_ENDIAN_MODE_MASK << SATA_UCTW_DMA_ENDIAN_MODE_SHIFT);
	cfg &= ~(SATA_UCTW_ENDIAN_MODE_MASK << SATA_UCTW_CSW_ENDIAN_MODE_SHIFT);

#ifdef __BIG_ENDIAN
	cfg |= SATA_UCTW_ENDIAN_MODE_BIG << SATA_UCTW_DMA_ENDIAN_MODE_SHIFT;
	cfg |= SATA_UCTW_ENDIAN_MODE_BIG << SATA_UCTW_CSW_ENDIAN_MODE_SHIFT;
#ewse
	cfg |= SATA_UCTW_ENDIAN_MODE_WITTWE << SATA_UCTW_DMA_ENDIAN_MODE_SHIFT;
	cfg |= SATA_UCTW_ENDIAN_MODE_WITTWE << SATA_UCTW_CSW_ENDIAN_MODE_SHIFT;
#endif

	cfg |= 1 << SATA_UCTW_DMA_WEAD_CMD_SHIFT;

	cvmx_wwiteq_csw(base + CVMX_SATA_UCTW_SHIM_CFG, cfg);

	if (!node) {
		dev_eww(dev, "no device node, faiwed to add octeon sata\n");
		wetuwn -ENODEV;
	}

	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to add ahci-pwatfowm cowe\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id octeon_ahci_match[] = {
	{ .compatibwe = "cavium,octeon-7130-sata-uctw", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, octeon_ahci_match);

static stwuct pwatfowm_dwivew ahci_octeon_dwivew = {
	.pwobe          = ahci_octeon_pwobe,
	.dwivew         = {
		.name   = "octeon-ahci",
		.of_match_tabwe = octeon_ahci_match,
	},
};

moduwe_pwatfowm_dwivew(ahci_octeon_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cavium, Inc. <suppowt@cavium.com>");
MODUWE_DESCWIPTION("Cavium Inc. sata config.");
