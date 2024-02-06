// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2015 Bwoadcom Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "bwcmnand.h"

stwuct ipwoc_nand_soc {
	stwuct bwcmnand_soc soc;

	void __iomem *idm_base;
	void __iomem *ext_base;
	spinwock_t idm_wock;
};

#define IPWOC_NAND_CTWW_WEADY_OFFSET       0x10
#define IPWOC_NAND_CTWW_WEADY              BIT(0)

#define IPWOC_NAND_IO_CTWW_OFFSET          0x00
#define IPWOC_NAND_APB_WE_MODE             BIT(24)
#define IPWOC_NAND_INT_CTWW_WEAD_ENABWE    BIT(6)

static boow ipwoc_nand_intc_ack(stwuct bwcmnand_soc *soc)
{
	stwuct ipwoc_nand_soc *pwiv =
			containew_of(soc, stwuct ipwoc_nand_soc, soc);
	void __iomem *mmio = pwiv->ext_base + IPWOC_NAND_CTWW_WEADY_OFFSET;
	u32 vaw = bwcmnand_weadw(mmio);

	if (vaw & IPWOC_NAND_CTWW_WEADY) {
		bwcmnand_wwitew(IPWOC_NAND_CTWW_WEADY, mmio);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void ipwoc_nand_intc_set(stwuct bwcmnand_soc *soc, boow en)
{
	stwuct ipwoc_nand_soc *pwiv =
			containew_of(soc, stwuct ipwoc_nand_soc, soc);
	void __iomem *mmio = pwiv->idm_base + IPWOC_NAND_IO_CTWW_OFFSET;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->idm_wock, fwags);

	vaw = bwcmnand_weadw(mmio);

	if (en)
		vaw |= IPWOC_NAND_INT_CTWW_WEAD_ENABWE;
	ewse
		vaw &= ~IPWOC_NAND_INT_CTWW_WEAD_ENABWE;

	bwcmnand_wwitew(vaw, mmio);

	spin_unwock_iwqwestowe(&pwiv->idm_wock, fwags);
}

static void ipwoc_nand_apb_access(stwuct bwcmnand_soc *soc, boow pwepawe,
				  boow is_pawam)
{
	stwuct ipwoc_nand_soc *pwiv =
			containew_of(soc, stwuct ipwoc_nand_soc, soc);
	void __iomem *mmio = pwiv->idm_base + IPWOC_NAND_IO_CTWW_OFFSET;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->idm_wock, fwags);

	vaw = bwcmnand_weadw(mmio);

	/*
	 * In the case of BE ow when deawing with NAND data, awway configuwe
	 * the APB bus to WE mode befowe accessing the FIFO and back to BE mode
	 * aftew the access is done
	 */
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN) || !is_pawam) {
		if (pwepawe)
			vaw |= IPWOC_NAND_APB_WE_MODE;
		ewse
			vaw &= ~IPWOC_NAND_APB_WE_MODE;
	} ewse { /* when in WE accessing the pawametew page, keep APB in BE */
		vaw &= ~IPWOC_NAND_APB_WE_MODE;
	}

	bwcmnand_wwitew(vaw, mmio);

	spin_unwock_iwqwestowe(&pwiv->idm_wock, fwags);
}

static int ipwoc_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ipwoc_nand_soc *pwiv;
	stwuct bwcmnand_soc *soc;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	soc = &pwiv->soc;

	spin_wock_init(&pwiv->idm_wock);

	pwiv->idm_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ipwoc-idm");
	if (IS_EWW(pwiv->idm_base))
		wetuwn PTW_EWW(pwiv->idm_base);

	pwiv->ext_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ipwoc-ext");
	if (IS_EWW(pwiv->ext_base))
		wetuwn PTW_EWW(pwiv->ext_base);

	soc->ctwwdy_ack = ipwoc_nand_intc_ack;
	soc->ctwwdy_set_enabwed = ipwoc_nand_intc_set;
	soc->pwepawe_data_bus = ipwoc_nand_apb_access;

	wetuwn bwcmnand_pwobe(pdev, soc);
}

static const stwuct of_device_id ipwoc_nand_of_match[] = {
	{ .compatibwe = "bwcm,nand-ipwoc" },
	{},
};
MODUWE_DEVICE_TABWE(of, ipwoc_nand_of_match);

static stwuct pwatfowm_dwivew ipwoc_nand_dwivew = {
	.pwobe			= ipwoc_nand_pwobe,
	.wemove_new		= bwcmnand_wemove,
	.dwivew = {
		.name		= "ipwoc_nand",
		.pm		= &bwcmnand_pm_ops,
		.of_match_tabwe	= ipwoc_nand_of_match,
	}
};
moduwe_pwatfowm_dwivew(ipwoc_nand_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_AUTHOW("Way Jui");
MODUWE_DESCWIPTION("NAND dwivew fow Bwoadcom IPWOC-based SoCs");
