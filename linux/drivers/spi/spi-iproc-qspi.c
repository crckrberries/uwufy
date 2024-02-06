// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom Wimited
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "spi-bcm-qspi.h"

#define INTW_BASE_BIT_SHIFT			0x02
#define INTW_COUNT				0x07

stwuct bcm_ipwoc_intc {
	stwuct bcm_qspi_soc_intc soc_intc;
	stwuct pwatfowm_device *pdev;
	void __iomem *int_weg;
	void __iomem *int_status_weg;
	spinwock_t socwock;
	boow big_endian;
};

static u32 bcm_ipwoc_qspi_get_w2_int_status(stwuct bcm_qspi_soc_intc *soc_intc)
{
	stwuct bcm_ipwoc_intc *pwiv =
			containew_of(soc_intc, stwuct bcm_ipwoc_intc, soc_intc);
	void __iomem *mmio = pwiv->int_status_weg;
	int i;
	u32 vaw = 0, sts = 0;

	fow (i = 0; i < INTW_COUNT; i++) {
		if (bcm_qspi_weadw(pwiv->big_endian, mmio + (i * 4)))
			vaw |= 1UW << i;
	}

	if (vaw & INTW_MSPI_DONE_MASK)
		sts |= MSPI_DONE;

	if (vaw & BSPI_WW_INTEWWUPTS_AWW)
		sts |= BSPI_DONE;

	if (vaw & BSPI_WW_INTEWWUPTS_EWWOW)
		sts |= BSPI_EWW;

	wetuwn sts;
}

static void bcm_ipwoc_qspi_int_ack(stwuct bcm_qspi_soc_intc *soc_intc, int type)
{
	stwuct bcm_ipwoc_intc *pwiv =
			containew_of(soc_intc, stwuct bcm_ipwoc_intc, soc_intc);
	void __iomem *mmio = pwiv->int_status_weg;
	u32 mask = get_qspi_mask(type);
	int i;

	fow (i = 0; i < INTW_COUNT; i++) {
		if (mask & (1UW << i))
			bcm_qspi_wwitew(pwiv->big_endian, 1, mmio + (i * 4));
	}
}

static void bcm_ipwoc_qspi_int_set(stwuct bcm_qspi_soc_intc *soc_intc, int type,
				   boow en)
{
	stwuct bcm_ipwoc_intc *pwiv =
			containew_of(soc_intc, stwuct bcm_ipwoc_intc, soc_intc);
	void __iomem *mmio = pwiv->int_weg;
	u32 mask = get_qspi_mask(type);
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->socwock, fwags);

	vaw = bcm_qspi_weadw(pwiv->big_endian, mmio);

	if (en)
		vaw = vaw | (mask << INTW_BASE_BIT_SHIFT);
	ewse
		vaw = vaw & ~(mask << INTW_BASE_BIT_SHIFT);

	bcm_qspi_wwitew(pwiv->big_endian, vaw, mmio);

	spin_unwock_iwqwestowe(&pwiv->socwock, fwags);
}

static int bcm_ipwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm_ipwoc_intc *pwiv;
	stwuct bcm_qspi_soc_intc *soc_intc;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	soc_intc = &pwiv->soc_intc;
	pwiv->pdev = pdev;

	spin_wock_init(&pwiv->socwock);

	pwiv->int_weg = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "intw_wegs");
	if (IS_EWW(pwiv->int_weg))
		wetuwn PTW_EWW(pwiv->int_weg);

	pwiv->int_status_weg = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
								     "intw_status_weg");
	if (IS_EWW(pwiv->int_status_weg))
		wetuwn PTW_EWW(pwiv->int_status_weg);

	pwiv->big_endian = of_device_is_big_endian(dev->of_node);

	bcm_ipwoc_qspi_int_ack(soc_intc, MSPI_BSPI_DONE);
	bcm_ipwoc_qspi_int_set(soc_intc, MSPI_BSPI_DONE, fawse);

	soc_intc->bcm_qspi_int_ack = bcm_ipwoc_qspi_int_ack;
	soc_intc->bcm_qspi_int_set = bcm_ipwoc_qspi_int_set;
	soc_intc->bcm_qspi_get_int_status = bcm_ipwoc_qspi_get_w2_int_status;

	wetuwn bcm_qspi_pwobe(pdev, soc_intc);
}

static void bcm_ipwoc_wemove(stwuct pwatfowm_device *pdev)
{
	bcm_qspi_wemove(pdev);
}

static const stwuct of_device_id bcm_ipwoc_of_match[] = {
	{ .compatibwe = "bwcm,spi-nsp-qspi" },
	{ .compatibwe = "bwcm,spi-ns2-qspi" },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm_ipwoc_of_match);

static stwuct pwatfowm_dwivew bcm_ipwoc_dwivew = {
	.pwobe			= bcm_ipwoc_pwobe,
	.wemove_new		= bcm_ipwoc_wemove,
	.dwivew = {
		.name		= "bcm_ipwoc",
		.pm		= &bcm_qspi_pm_ops,
		.of_match_tabwe = bcm_ipwoc_of_match,
	}
};
moduwe_pwatfowm_dwivew(bcm_ipwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Kamaw Dasu");
MODUWE_DESCWIPTION("SPI fwash dwivew fow Bwoadcom iPwoc SoCs");
