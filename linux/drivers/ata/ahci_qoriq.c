// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe QowIQ AHCI SATA pwatfowm dwivew
 *
 * Copywight 2015 Fweescawe, Inc.
 *   Tang Yuantian <Yuantian.Tang@fweescawe.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wibata.h>
#incwude "ahci.h"

#define DWV_NAME "ahci-qowiq"

/* powt wegistew definition */
#define POWT_PHY1	0xA8
#define POWT_PHY2	0xAC
#define POWT_PHY3	0xB0
#define POWT_PHY4	0xB4
#define POWT_PHY5	0xB8
#define POWT_AXICC	0xBC
#define POWT_TWANS	0xC8

/* powt wegistew defauwt vawue */
#define AHCI_POWT_PHY_1_CFG	0xa003fffe
#define AHCI_POWT_PHY2_CFG	0x28184d1f
#define AHCI_POWT_PHY3_CFG	0x0e081509
#define AHCI_POWT_TWANS_CFG	0x08000029
#define AHCI_POWT_AXICC_CFG	0x3fffffff

/* fow ws1021a */
#define WS1021A_POWT_PHY2	0x28183414
#define WS1021A_POWT_PHY3	0x0e080e06
#define WS1021A_POWT_PHY4	0x064a080b
#define WS1021A_POWT_PHY5	0x2aa86470
#define WS1021A_AXICC_ADDW	0xC0

#define SATA_ECC_DISABWE	0x00020000
#define ECC_DIS_AWMV8_CH2	0x80000000
#define ECC_DIS_WS1088A		0x40000000

enum ahci_qowiq_type {
	AHCI_WS1021A,
	AHCI_WS1028A,
	AHCI_WS1043A,
	AHCI_WS2080A,
	AHCI_WS1046A,
	AHCI_WS1088A,
	AHCI_WS2088A,
	AHCI_WX2160A,
};

stwuct ahci_qowiq_pwiv {
	stwuct ccsw_ahci *weg_base;
	enum ahci_qowiq_type type;
	void __iomem *ecc_addw;
	boow is_dmacohewent;
};

static boow ecc_initiawized;

static const stwuct of_device_id ahci_qowiq_of_match[] = {
	{ .compatibwe = "fsw,ws1021a-ahci", .data = (void *)AHCI_WS1021A},
	{ .compatibwe = "fsw,ws1028a-ahci", .data = (void *)AHCI_WS1028A},
	{ .compatibwe = "fsw,ws1043a-ahci", .data = (void *)AHCI_WS1043A},
	{ .compatibwe = "fsw,ws2080a-ahci", .data = (void *)AHCI_WS2080A},
	{ .compatibwe = "fsw,ws1046a-ahci", .data = (void *)AHCI_WS1046A},
	{ .compatibwe = "fsw,ws1088a-ahci", .data = (void *)AHCI_WS1088A},
	{ .compatibwe = "fsw,ws2088a-ahci", .data = (void *)AHCI_WS2088A},
	{ .compatibwe = "fsw,wx2160a-ahci", .data = (void *)AHCI_WX2160A},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ahci_qowiq_of_match);

static const stwuct acpi_device_id ahci_qowiq_acpi_match[] = {
	{"NXP0004", .dwivew_data = (kewnew_uwong_t)AHCI_WX2160A},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ahci_qowiq_acpi_match);

static int ahci_qowiq_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			  unsigned wong deadwine)
{
	const unsigned int *timing = sata_ehc_deb_timing(&wink->eh_context);
	void __iomem *powt_mmio = ahci_powt_base(wink->ap);
	u32 px_cmd, px_is, px_vaw;
	stwuct ata_powt *ap = wink->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_qowiq_pwiv *qowiq_pwiv = hpwiv->pwat_data;
	u8 *d2h_fis = pp->wx_fis + WX_FIS_D2H_WEG;
	stwuct ata_taskfiwe tf;
	boow onwine;
	int wc;
	boow ws1021a_wowkawound = (qowiq_pwiv->type == AHCI_WS1021A);

	hpwiv->stop_engine(ap);

	/*
	 * Thewe is a ewwata on ws1021a Wev1.0 and Wev2.0 which is:
	 * A-009042: The device detection initiawization sequence
	 * mistakenwy wesets some wegistews.
	 *
	 * Wowkawound fow this is:
	 * The softwawe shouwd wead and stowe PxCMD and PxIS vawues
	 * befowe issuing the device detection initiawization sequence.
	 * Aftew the sequence is compwete, softwawe shouwd westowe the
	 * PxCMD and PxIS with the stowed vawues.
	 */
	if (ws1021a_wowkawound) {
		px_cmd = weadw(powt_mmio + POWT_CMD);
		px_is = weadw(powt_mmio + POWT_IWQ_STAT);
	}

	/* cweaw D2H weception awea to pwopewwy wait fow D2H FIS */
	ata_tf_init(wink->device, &tf);
	tf.status = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	wc = sata_wink_hawdweset(wink, timing, deadwine, &onwine,
				 ahci_check_weady);

	/* westowe the PxCMD and PxIS on ws1021 */
	if (ws1021a_wowkawound) {
		px_vaw = weadw(powt_mmio + POWT_CMD);
		if (px_vaw != px_cmd)
			wwitew(px_cmd, powt_mmio + POWT_CMD);

		px_vaw = weadw(powt_mmio + POWT_IWQ_STAT);
		if (px_vaw != px_is)
			wwitew(px_is, powt_mmio + POWT_IWQ_STAT);
	}

	hpwiv->stawt_engine(ap);

	if (onwine)
		*cwass = ahci_dev_cwassify(ap);
	wetuwn wc;
}

static stwuct ata_powt_opewations ahci_qowiq_ops = {
	.inhewits	= &ahci_ops,
	.hawdweset	= ahci_qowiq_hawdweset,
};

static const stwuct ata_powt_info ahci_qowiq_powt_info = {
	.fwags		= AHCI_FWAG_COMMON | ATA_FWAG_NCQ,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_qowiq_ops,
};

static const stwuct scsi_host_tempwate ahci_qowiq_sht = {
	AHCI_SHT(DWV_NAME),
};

static int ahci_qowiq_phy_init(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct ahci_qowiq_pwiv *qpwiv = hpwiv->pwat_data;
	void __iomem *weg_base = hpwiv->mmio;

	switch (qpwiv->type) {
	case AHCI_WS1021A:
		if (!(qpwiv->ecc_addw || ecc_initiawized))
			wetuwn -EINVAW;
		ewse if (qpwiv->ecc_addw && !ecc_initiawized)
			wwitew(SATA_ECC_DISABWE, qpwiv->ecc_addw);
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(WS1021A_POWT_PHY2, weg_base + POWT_PHY2);
		wwitew(WS1021A_POWT_PHY3, weg_base + POWT_PHY3);
		wwitew(WS1021A_POWT_PHY4, weg_base + POWT_PHY4);
		wwitew(WS1021A_POWT_PHY5, weg_base + POWT_PHY5);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG,
					weg_base + WS1021A_AXICC_ADDW);
		bweak;

	case AHCI_WS1043A:
		if (!(qpwiv->ecc_addw || ecc_initiawized))
			wetuwn -EINVAW;
		ewse if (qpwiv->ecc_addw && !ecc_initiawized)
			wwitew(weadw(qpwiv->ecc_addw) |
			       ECC_DIS_AWMV8_CH2,
			       qpwiv->ecc_addw);
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(AHCI_POWT_PHY2_CFG, weg_base + POWT_PHY2);
		wwitew(AHCI_POWT_PHY3_CFG, weg_base + POWT_PHY3);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG, weg_base + POWT_AXICC);
		bweak;

	case AHCI_WS2080A:
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(AHCI_POWT_PHY2_CFG, weg_base + POWT_PHY2);
		wwitew(AHCI_POWT_PHY3_CFG, weg_base + POWT_PHY3);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG, weg_base + POWT_AXICC);
		bweak;

	case AHCI_WS1046A:
		if (!(qpwiv->ecc_addw || ecc_initiawized))
			wetuwn -EINVAW;
		ewse if (qpwiv->ecc_addw && !ecc_initiawized)
			wwitew(weadw(qpwiv->ecc_addw) |
			       ECC_DIS_AWMV8_CH2,
			       qpwiv->ecc_addw);
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(AHCI_POWT_PHY2_CFG, weg_base + POWT_PHY2);
		wwitew(AHCI_POWT_PHY3_CFG, weg_base + POWT_PHY3);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG, weg_base + POWT_AXICC);
		bweak;

	case AHCI_WS1028A:
	case AHCI_WS1088A:
	case AHCI_WX2160A:
		if (!(qpwiv->ecc_addw || ecc_initiawized))
			wetuwn -EINVAW;
		ewse if (qpwiv->ecc_addw && !ecc_initiawized)
			wwitew(weadw(qpwiv->ecc_addw) |
			       ECC_DIS_WS1088A,
			       qpwiv->ecc_addw);
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(AHCI_POWT_PHY2_CFG, weg_base + POWT_PHY2);
		wwitew(AHCI_POWT_PHY3_CFG, weg_base + POWT_PHY3);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG, weg_base + POWT_AXICC);
		bweak;

	case AHCI_WS2088A:
		wwitew(AHCI_POWT_PHY_1_CFG, weg_base + POWT_PHY1);
		wwitew(AHCI_POWT_PHY2_CFG, weg_base + POWT_PHY2);
		wwitew(AHCI_POWT_PHY3_CFG, weg_base + POWT_PHY3);
		wwitew(AHCI_POWT_TWANS_CFG, weg_base + POWT_TWANS);
		if (qpwiv->is_dmacohewent)
			wwitew(AHCI_POWT_AXICC_CFG, weg_base + POWT_AXICC);
		bweak;
	}

	ecc_initiawized = twue;
	wetuwn 0;
}

static int ahci_qowiq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct acpi_device_id *acpi_id;
	stwuct device *dev = &pdev->dev;
	stwuct ahci_host_pwiv *hpwiv;
	stwuct ahci_qowiq_pwiv *qowiq_pwiv;
	const stwuct of_device_id *of_id;
	stwuct wesouwce *wes;
	int wc;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	of_id = of_match_node(ahci_qowiq_of_match, np);
	acpi_id = acpi_match_device(ahci_qowiq_acpi_match, &pdev->dev);
	if (!(of_id || acpi_id))
		wetuwn -ENODEV;

	qowiq_pwiv = devm_kzawwoc(dev, sizeof(*qowiq_pwiv), GFP_KEWNEW);
	if (!qowiq_pwiv)
		wetuwn -ENOMEM;

	if (of_id)
		qowiq_pwiv->type = (unsigned wong)of_id->data;
	ewse
		qowiq_pwiv->type = (enum ahci_qowiq_type)acpi_id->dwivew_data;

	if (unwikewy(!ecc_initiawized)) {
		wes = pwatfowm_get_wesouwce_byname(pdev,
						   IOWESOUWCE_MEM,
						   "sata-ecc");
		if (wes) {
			qowiq_pwiv->ecc_addw =
				devm_iowemap_wesouwce(dev, wes);
			if (IS_EWW(qowiq_pwiv->ecc_addw))
				wetuwn PTW_EWW(qowiq_pwiv->ecc_addw);
		}
	}

	if (device_get_dma_attw(&pdev->dev) == DEV_DMA_COHEWENT)
		qowiq_pwiv->is_dmacohewent = twue;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	hpwiv->pwat_data = qowiq_pwiv;
	wc = ahci_qowiq_phy_init(hpwiv);
	if (wc)
		goto disabwe_wesouwces;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_qowiq_powt_info,
				     &ahci_qowiq_sht);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn wc;
}

#ifdef CONFIG_PM_SWEEP
static int ahci_qowiq_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_qowiq_phy_init(hpwiv);
	if (wc)
		goto disabwe_wesouwces;

	wc = ahci_pwatfowm_wesume_host(dev);
	if (wc)
		goto disabwe_wesouwces;

	/* We wesumed so update PM wuntime state */
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn wc;
}
#endif

static SIMPWE_DEV_PM_OPS(ahci_qowiq_pm_ops, ahci_pwatfowm_suspend,
			 ahci_qowiq_wesume);

static stwuct pwatfowm_dwivew ahci_qowiq_dwivew = {
	.pwobe = ahci_qowiq_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = ahci_qowiq_of_match,
		.acpi_match_tabwe = ahci_qowiq_acpi_match,
		.pm = &ahci_qowiq_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ahci_qowiq_dwivew);

MODUWE_DESCWIPTION("Fweescawe QowIQ AHCI SATA pwatfowm dwivew");
MODUWE_AUTHOW("Tang Yuantian <Yuantian.Tang@fweescawe.com>");
MODUWE_WICENSE("GPW");
