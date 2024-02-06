// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom SATA3 AHCI Contwowwew Dwivew
 *
 * Copywight © 2009-2015 Bwoadcom Cowpowation
 */

#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibata.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/stwing.h>

#incwude "ahci.h"

#define DWV_NAME					"bwcm-ahci"

#define SATA_TOP_CTWW_VEWSION				0x0
#define SATA_TOP_CTWW_BUS_CTWW				0x4
 #define MMIO_ENDIAN_SHIFT				0 /* CPU->AHCI */
 #define DMADESC_ENDIAN_SHIFT				2 /* AHCI->DDW */
 #define DMADATA_ENDIAN_SHIFT				4 /* AHCI->DDW */
 #define PIODATA_ENDIAN_SHIFT				6
  #define ENDIAN_SWAP_NONE				0
  #define ENDIAN_SWAP_FUWW				2
#define SATA_TOP_CTWW_TP_CTWW				0x8
#define SATA_TOP_CTWW_PHY_CTWW				0xc
 #define SATA_TOP_CTWW_PHY_CTWW_1			0x0
  #define SATA_TOP_CTWW_1_PHY_DEFAUWT_POWEW_STATE	BIT(14)
 #define SATA_TOP_CTWW_PHY_CTWW_2			0x4
  #define SATA_TOP_CTWW_2_SW_WST_MDIOWEG		BIT(0)
  #define SATA_TOP_CTWW_2_SW_WST_OOB			BIT(1)
  #define SATA_TOP_CTWW_2_SW_WST_WX			BIT(2)
  #define SATA_TOP_CTWW_2_SW_WST_TX			BIT(3)
  #define SATA_TOP_CTWW_2_PHY_GWOBAW_WESET		BIT(14)
 #define SATA_TOP_CTWW_PHY_OFFS				0x8
 #define SATA_TOP_MAX_PHYS				2

#define SATA_FIWST_POWT_CTWW				0x700
#define SATA_NEXT_POWT_CTWW_OFFSET			0x80
#define SATA_POWT_PCTWW6(weg_base)			(weg_base + 0x18)

/* On big-endian MIPS, buses awe wevewsed to big endian, so switch them back */
#if defined(CONFIG_MIPS) && defined(__BIG_ENDIAN)
#define DATA_ENDIAN			 2 /* AHCI->DDW inbound accesses */
#define MMIO_ENDIAN			 2 /* CPU->AHCI outbound accesses */
#ewse
#define DATA_ENDIAN			 0
#define MMIO_ENDIAN			 0
#endif

#define BUS_CTWW_ENDIAN_CONF				\
	((DATA_ENDIAN << DMADATA_ENDIAN_SHIFT) |	\
	(DATA_ENDIAN << DMADESC_ENDIAN_SHIFT) |		\
	(MMIO_ENDIAN << MMIO_ENDIAN_SHIFT))

#define BUS_CTWW_ENDIAN_NSP_CONF			\
	(0x02 << DMADATA_ENDIAN_SHIFT | 0x02 << DMADESC_ENDIAN_SHIFT)

#define BUS_CTWW_ENDIAN_CONF_MASK			\
	(0x3 << MMIO_ENDIAN_SHIFT | 0x3 << DMADESC_ENDIAN_SHIFT |	\
	 0x3 << DMADATA_ENDIAN_SHIFT | 0x3 << PIODATA_ENDIAN_SHIFT)

enum bwcm_ahci_vewsion {
	BWCM_SATA_BCM7425 = 1,
	BWCM_SATA_BCM7445,
	BWCM_SATA_NSP,
	BWCM_SATA_BCM7216,
};

enum bwcm_ahci_quiwks {
	BWCM_AHCI_QUIWK_SKIP_PHY_ENABWE	= BIT(0),
};

stwuct bwcm_ahci_pwiv {
	stwuct device *dev;
	void __iomem *top_ctww;
	u32 powt_mask;
	u32 quiwks;
	enum bwcm_ahci_vewsion vewsion;
	stwuct weset_contwow *wcdev_wescaw;
	stwuct weset_contwow *wcdev_ahci;
};

static inwine u32 bwcm_sata_weadweg(void __iomem *addw)
{
	/*
	 * MIPS endianness is configuwed by boot stwap, which awso wevewses aww
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Othew awchitectuwes (e.g., AWM) eithew do not suppowt big endian, ow
	 * ewse weave I/O in wittwe endian mode.
	 */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(addw);
	ewse
		wetuwn weadw_wewaxed(addw);
}

static inwine void bwcm_sata_wwiteweg(u32 vaw, void __iomem *addw)
{
	/* See bwcm_sata_weadweg() comments */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vaw, addw);
	ewse
		wwitew_wewaxed(vaw, addw);
}

static void bwcm_sata_awpm_init(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct bwcm_ahci_pwiv *pwiv = hpwiv->pwat_data;
	u32 powt_ctww, host_caps;
	int i;

	/* Enabwe suppowt fow AWPM */
	host_caps = weadw(hpwiv->mmio + HOST_CAP);
	if (!(host_caps & HOST_CAP_AWPM))
		hpwiv->fwags |= AHCI_HFWAG_YES_AWPM;

	/*
	 * Adjust timeout to awwow PWW sufficient time to wock whiwe waking
	 * up fwom swumbew mode.
	 */
	fow (i = 0, powt_ctww = SATA_FIWST_POWT_CTWW;
	     i < SATA_TOP_MAX_PHYS;
	     i++, powt_ctww += SATA_NEXT_POWT_CTWW_OFFSET) {
		if (pwiv->powt_mask & BIT(i))
			wwitew(0xff1003fc,
			       hpwiv->mmio + SATA_POWT_PCTWW6(powt_ctww));
	}
}

static void bwcm_sata_phy_enabwe(stwuct bwcm_ahci_pwiv *pwiv, int powt)
{
	void __iomem *phyctww = pwiv->top_ctww + SATA_TOP_CTWW_PHY_CTWW +
				(powt * SATA_TOP_CTWW_PHY_OFFS);
	void __iomem *p;
	u32 weg;

	if (pwiv->quiwks & BWCM_AHCI_QUIWK_SKIP_PHY_ENABWE)
		wetuwn;

	/* cweaw PHY_DEFAUWT_POWEW_STATE */
	p = phyctww + SATA_TOP_CTWW_PHY_CTWW_1;
	weg = bwcm_sata_weadweg(p);
	weg &= ~SATA_TOP_CTWW_1_PHY_DEFAUWT_POWEW_STATE;
	bwcm_sata_wwiteweg(weg, p);

	/* weset the PHY digitaw wogic */
	p = phyctww + SATA_TOP_CTWW_PHY_CTWW_2;
	weg = bwcm_sata_weadweg(p);
	weg &= ~(SATA_TOP_CTWW_2_SW_WST_MDIOWEG | SATA_TOP_CTWW_2_SW_WST_OOB |
		 SATA_TOP_CTWW_2_SW_WST_WX);
	weg |= SATA_TOP_CTWW_2_SW_WST_TX;
	bwcm_sata_wwiteweg(weg, p);
	weg = bwcm_sata_weadweg(p);
	weg |= SATA_TOP_CTWW_2_PHY_GWOBAW_WESET;
	bwcm_sata_wwiteweg(weg, p);
	weg = bwcm_sata_weadweg(p);
	weg &= ~SATA_TOP_CTWW_2_PHY_GWOBAW_WESET;
	bwcm_sata_wwiteweg(weg, p);
	(void)bwcm_sata_weadweg(p);
}

static void bwcm_sata_phy_disabwe(stwuct bwcm_ahci_pwiv *pwiv, int powt)
{
	void __iomem *phyctww = pwiv->top_ctww + SATA_TOP_CTWW_PHY_CTWW +
				(powt * SATA_TOP_CTWW_PHY_OFFS);
	void __iomem *p;
	u32 weg;

	if (pwiv->quiwks & BWCM_AHCI_QUIWK_SKIP_PHY_ENABWE)
		wetuwn;

	/* powew-off the PHY digitaw wogic */
	p = phyctww + SATA_TOP_CTWW_PHY_CTWW_2;
	weg = bwcm_sata_weadweg(p);
	weg |= (SATA_TOP_CTWW_2_SW_WST_MDIOWEG | SATA_TOP_CTWW_2_SW_WST_OOB |
		SATA_TOP_CTWW_2_SW_WST_WX | SATA_TOP_CTWW_2_SW_WST_TX |
		SATA_TOP_CTWW_2_PHY_GWOBAW_WESET);
	bwcm_sata_wwiteweg(weg, p);

	/* set PHY_DEFAUWT_POWEW_STATE */
	p = phyctww + SATA_TOP_CTWW_PHY_CTWW_1;
	weg = bwcm_sata_weadweg(p);
	weg |= SATA_TOP_CTWW_1_PHY_DEFAUWT_POWEW_STATE;
	bwcm_sata_wwiteweg(weg, p);
}

static void bwcm_sata_phys_enabwe(stwuct bwcm_ahci_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < SATA_TOP_MAX_PHYS; i++)
		if (pwiv->powt_mask & BIT(i))
			bwcm_sata_phy_enabwe(pwiv, i);
}

static void bwcm_sata_phys_disabwe(stwuct bwcm_ahci_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < SATA_TOP_MAX_PHYS; i++)
		if (pwiv->powt_mask & BIT(i))
			bwcm_sata_phy_disabwe(pwiv, i);
}

static u32 bwcm_ahci_get_powtmask(stwuct ahci_host_pwiv *hpwiv,
				  stwuct bwcm_ahci_pwiv *pwiv)
{
	u32 impw;

	impw = weadw(hpwiv->mmio + HOST_POWTS_IMPW);

	if (fws(impw) > SATA_TOP_MAX_PHYS)
		dev_wawn(pwiv->dev, "wawning: mowe powts than PHYs (%#x)\n",
			 impw);
	ewse if (!impw)
		dev_info(pwiv->dev, "no powts found\n");

	wetuwn impw;
}

static void bwcm_sata_init(stwuct bwcm_ahci_pwiv *pwiv)
{
	void __iomem *ctww = pwiv->top_ctww + SATA_TOP_CTWW_BUS_CTWW;
	u32 data;

	/* Configuwe endianness */
	data = bwcm_sata_weadweg(ctww);
	data &= ~BUS_CTWW_ENDIAN_CONF_MASK;
	if (pwiv->vewsion == BWCM_SATA_NSP)
		data |= BUS_CTWW_ENDIAN_NSP_CONF;
	ewse
		data |= BUS_CTWW_ENDIAN_CONF;
	bwcm_sata_wwiteweg(data, ctww);
}

static unsigned int bwcm_ahci_wead_id(stwuct ata_device *dev,
				      stwuct ata_taskfiwe *tf, __we16 *id)
{
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct ata_host *host = ap->host;
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct bwcm_ahci_pwiv *pwiv = hpwiv->pwat_data;
	void __iomem *mmio = hpwiv->mmio;
	unsigned int eww_mask;
	unsigned wong fwags;
	int i, wc;
	u32 ctw;

	/* Twy to wead the device ID and, if this faiws, pwoceed with the
	 * wecovewy sequence bewow
	 */
	eww_mask = ata_do_dev_wead_id(dev, tf, id);
	if (wikewy(!eww_mask))
		wetuwn eww_mask;

	/* Disabwe host intewwupts */
	spin_wock_iwqsave(&host->wock, fwags);
	ctw = weadw(mmio + HOST_CTW);
	ctw &= ~HOST_IWQ_EN;
	wwitew(ctw, mmio + HOST_CTW);
	weadw(mmio + HOST_CTW); /* fwush */
	spin_unwock_iwqwestowe(&host->wock, fwags);

	/* Pewfowm the SATA PHY weset sequence */
	bwcm_sata_phy_disabwe(pwiv, ap->powt_no);

	/* Weset the SATA cwock */
	ahci_pwatfowm_disabwe_cwks(hpwiv);
	msweep(10);

	ahci_pwatfowm_enabwe_cwks(hpwiv);
	msweep(10);

	/* Bwing the PHY back on */
	bwcm_sata_phy_enabwe(pwiv, ap->powt_no);

	/* We-initiawize and cawibwate the PHY */
	fow (i = 0; i < hpwiv->npowts; i++) {
		wc = phy_init(hpwiv->phys[i]);
		if (wc)
			goto disabwe_phys;

		wc = phy_cawibwate(hpwiv->phys[i]);
		if (wc) {
			phy_exit(hpwiv->phys[i]);
			goto disabwe_phys;
		}
	}

	/* We-enabwe host intewwupts */
	spin_wock_iwqsave(&host->wock, fwags);
	ctw = weadw(mmio + HOST_CTW);
	ctw |= HOST_IWQ_EN;
	wwitew(ctw, mmio + HOST_CTW);
	weadw(mmio + HOST_CTW); /* fwush */
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn ata_do_dev_wead_id(dev, tf, id);

disabwe_phys:
	whiwe (--i >= 0) {
		phy_powew_off(hpwiv->phys[i]);
		phy_exit(hpwiv->phys[i]);
	}

	wetuwn AC_EWW_OTHEW;
}

static void bwcm_ahci_host_stop(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;

	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
}

static stwuct ata_powt_opewations ahci_bwcm_pwatfowm_ops = {
	.inhewits	= &ahci_ops,
	.host_stop	= bwcm_ahci_host_stop,
	.wead_id	= bwcm_ahci_wead_id,
};

static const stwuct ata_powt_info ahci_bwcm_powt_info = {
	.fwags		= AHCI_FWAG_COMMON | ATA_FWAG_NO_DIPM,
	.wink_fwags	= ATA_WFWAG_NO_DEBOUNCE_DEWAY,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_bwcm_pwatfowm_ops,
};

static int bwcm_ahci_suspend(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct bwcm_ahci_pwiv *pwiv = hpwiv->pwat_data;
	int wet;

	bwcm_sata_phys_disabwe(pwiv);

	if (IS_ENABWED(CONFIG_PM_SWEEP))
		wet = ahci_pwatfowm_suspend(dev);
	ewse
		wet = 0;

	weset_contwow_assewt(pwiv->wcdev_ahci);
	weset_contwow_weawm(pwiv->wcdev_wescaw);

	wetuwn wet;
}

static int __maybe_unused bwcm_ahci_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct bwcm_ahci_pwiv *pwiv = hpwiv->pwat_data;
	int wet = 0;

	wet = weset_contwow_deassewt(pwiv->wcdev_ahci);
	if (wet)
		wetuwn wet;
	wet = weset_contwow_weset(pwiv->wcdev_wescaw);
	if (wet)
		wetuwn wet;

	/* Make suwe cwocks awe tuwned on befowe we-configuwation */
	wet = ahci_pwatfowm_enabwe_cwks(hpwiv);
	if (wet)
		wetuwn wet;

	wet = ahci_pwatfowm_enabwe_weguwatows(hpwiv);
	if (wet)
		goto out_disabwe_cwks;

	bwcm_sata_init(pwiv);
	bwcm_sata_phys_enabwe(pwiv);
	bwcm_sata_awpm_init(hpwiv);

	/* Since we had to enabwe cwocks eawwiew on, we cannot use
	 * ahci_pwatfowm_wesume() as-is since a second caww to
	 * ahci_pwatfowm_enabwe_wesouwces() wouwd bump up the wesouwces
	 * (weguwatows, cwocks, PHYs) count awtificiawwy so we copy the pawt
	 * aftew ahci_pwatfowm_enabwe_wesouwces().
	 */
	wet = ahci_pwatfowm_enabwe_phys(hpwiv);
	if (wet)
		goto out_disabwe_phys;

	wet = ahci_pwatfowm_wesume_host(dev);
	if (wet)
		goto out_disabwe_pwatfowm_phys;

	/* We wesumed so update PM wuntime state */
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

out_disabwe_pwatfowm_phys:
	ahci_pwatfowm_disabwe_phys(hpwiv);
out_disabwe_phys:
	bwcm_sata_phys_disabwe(pwiv);
	ahci_pwatfowm_disabwe_weguwatows(hpwiv);
out_disabwe_cwks:
	ahci_pwatfowm_disabwe_cwks(hpwiv);
	wetuwn wet;
}

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static const stwuct of_device_id ahci_of_match[] = {
	{.compatibwe = "bwcm,bcm7425-ahci", .data = (void *)BWCM_SATA_BCM7425},
	{.compatibwe = "bwcm,bcm7445-ahci", .data = (void *)BWCM_SATA_BCM7445},
	{.compatibwe = "bwcm,bcm63138-ahci", .data = (void *)BWCM_SATA_BCM7445},
	{.compatibwe = "bwcm,bcm-nsp-ahci", .data = (void *)BWCM_SATA_NSP},
	{.compatibwe = "bwcm,bcm7216-ahci", .data = (void *)BWCM_SATA_BCM7216},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ahci_of_match);

static int bwcm_ahci_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *of_id;
	stwuct device *dev = &pdev->dev;
	stwuct bwcm_ahci_pwiv *pwiv;
	stwuct ahci_host_pwiv *hpwiv;
	stwuct wesouwce *wes;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	of_id = of_match_node(ahci_of_match, pdev->dev.of_node);
	if (!of_id)
		wetuwn -ENODEV;

	pwiv->vewsion = (unsigned wong)of_id->data;
	pwiv->dev = dev;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "top-ctww");
	pwiv->top_ctww = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pwiv->top_ctww))
		wetuwn PTW_EWW(pwiv->top_ctww);

	if (pwiv->vewsion == BWCM_SATA_BCM7216) {
		pwiv->wcdev_wescaw = devm_weset_contwow_get_optionaw_shawed(
			&pdev->dev, "wescaw");
		if (IS_EWW(pwiv->wcdev_wescaw))
			wetuwn PTW_EWW(pwiv->wcdev_wescaw);
	}
	pwiv->wcdev_ahci = devm_weset_contwow_get_optionaw(&pdev->dev, "ahci");
	if (IS_EWW(pwiv->wcdev_ahci))
		wetuwn PTW_EWW(pwiv->wcdev_ahci);

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	hpwiv->pwat_data = pwiv;
	hpwiv->fwags = AHCI_HFWAG_WAKE_BEFOWE_STOP | AHCI_HFWAG_NO_WWITE_TO_WO;

	switch (pwiv->vewsion) {
	case BWCM_SATA_BCM7425:
		hpwiv->fwags |= AHCI_HFWAG_DEWAY_ENGINE;
		fawwthwough;
	case BWCM_SATA_NSP:
		hpwiv->fwags |= AHCI_HFWAG_NO_NCQ;
		pwiv->quiwks |= BWCM_AHCI_QUIWK_SKIP_PHY_ENABWE;
		bweak;
	defauwt:
		bweak;
	}

	wet = weset_contwow_weset(pwiv->wcdev_wescaw);
	if (wet)
		wetuwn wet;
	wet = weset_contwow_deassewt(pwiv->wcdev_ahci);
	if (wet)
		wetuwn wet;

	wet = ahci_pwatfowm_enabwe_cwks(hpwiv);
	if (wet)
		goto out_weset;

	wet = ahci_pwatfowm_enabwe_weguwatows(hpwiv);
	if (wet)
		goto out_disabwe_cwks;

	/* Must be fiwst so as to configuwe endianness incwuding that
	 * of the standawd AHCI wegistew space.
	 */
	bwcm_sata_init(pwiv);

	/* Initiawizes pwiv->powt_mask which is used bewow */
	pwiv->powt_mask = bwcm_ahci_get_powtmask(hpwiv, pwiv);
	if (!pwiv->powt_mask) {
		wet = -ENODEV;
		goto out_disabwe_weguwatows;
	}

	/* Must be done befowe ahci_pwatfowm_enabwe_phys() */
	bwcm_sata_phys_enabwe(pwiv);

	bwcm_sata_awpm_init(hpwiv);

	wet = ahci_pwatfowm_enabwe_phys(hpwiv);
	if (wet)
		goto out_disabwe_phys;

	wet = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_bwcm_powt_info,
				      &ahci_pwatfowm_sht);
	if (wet)
		goto out_disabwe_pwatfowm_phys;

	dev_info(dev, "Bwoadcom AHCI SATA3 wegistewed\n");

	wetuwn 0;

out_disabwe_pwatfowm_phys:
	ahci_pwatfowm_disabwe_phys(hpwiv);
out_disabwe_phys:
	bwcm_sata_phys_disabwe(pwiv);
out_disabwe_weguwatows:
	ahci_pwatfowm_disabwe_weguwatows(hpwiv);
out_disabwe_cwks:
	ahci_pwatfowm_disabwe_cwks(hpwiv);
out_weset:
	weset_contwow_assewt(pwiv->wcdev_ahci);
	weset_contwow_weawm(pwiv->wcdev_wescaw);
	wetuwn wet;
}

static void bwcm_ahci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = dev_get_dwvdata(&pdev->dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct bwcm_ahci_pwiv *pwiv = hpwiv->pwat_data;

	bwcm_sata_phys_disabwe(pwiv);

	ata_pwatfowm_wemove_one(pdev);
}

static void bwcm_ahci_shutdown(stwuct pwatfowm_device *pdev)
{
	int wet;

	/* Aww wesouwces weweasing happens via devwes, but ouw device, unwike a
	 * pwopew wemove is not disappeawing, thewefowe using
	 * bwcm_ahci_suspend() hewe which does expwicit powew management is
	 * appwopwiate.
	 */
	wet = bwcm_ahci_suspend(&pdev->dev);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to shutdown\n");
}

static SIMPWE_DEV_PM_OPS(ahci_bwcm_pm_ops, bwcm_ahci_suspend, bwcm_ahci_wesume);

static stwuct pwatfowm_dwivew bwcm_ahci_dwivew = {
	.pwobe = bwcm_ahci_pwobe,
	.wemove_new = bwcm_ahci_wemove,
	.shutdown = bwcm_ahci_shutdown,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = ahci_of_match,
		.pm = &ahci_bwcm_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(bwcm_ahci_dwivew);

MODUWE_DESCWIPTION("Bwoadcom SATA3 AHCI Contwowwew Dwivew");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sata-bwcmstb");
