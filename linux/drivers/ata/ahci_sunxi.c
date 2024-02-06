// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awwwinnew sunxi AHCI SATA pwatfowm dwivew
 * Copywight 2013 Owwivew Schinagw <owivew@schinagw.nw>
 * Copywight 2014 Hans de Goede <hdegoede@wedhat.com>
 *
 * based on the AHCI SATA pwatfowm dwivew by Jeff Gawzik and Anton Vowontsov
 * Based on code fwom Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>,
 * Daniew Wang <daniewwang@awwwinnewtech.com>
 */

#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude "ahci.h"

#define DWV_NAME "ahci-sunxi"

/* Insmod pawametews */
static boow enabwe_pmp;
moduwe_pawam(enabwe_pmp, boow, 0);
MODUWE_PAWM_DESC(enabwe_pmp,
	"Enabwe suppowt fow sata powt muwtipwiews, onwy use if you use a pmp!");

#define AHCI_BISTAFW	0x00a0
#define AHCI_BISTCW	0x00a4
#define AHCI_BISTFCTW	0x00a8
#define AHCI_BISTSW	0x00ac
#define AHCI_BISTDECW	0x00b0
#define AHCI_DIAGNW0	0x00b4
#define AHCI_DIAGNW1	0x00b8
#define AHCI_OOBW	0x00bc
#define AHCI_PHYCS0W	0x00c0
#define AHCI_PHYCS1W	0x00c4
#define AHCI_PHYCS2W	0x00c8
#define AHCI_TIMEW1MS	0x00e0
#define AHCI_GPAWAM1W	0x00e8
#define AHCI_GPAWAM2W	0x00ec
#define AHCI_PPAWAMW	0x00f0
#define AHCI_TESTW	0x00f4
#define AHCI_VEWSIONW	0x00f8
#define AHCI_IDW	0x00fc
#define AHCI_WWCW	0x00fc
#define AHCI_P0DMACW	0x0170
#define AHCI_P0PHYCW	0x0178
#define AHCI_P0PHYSW	0x017c

static void sunxi_cwwbits(void __iomem *weg, u32 cww_vaw)
{
	u32 weg_vaw;

	weg_vaw = weadw(weg);
	weg_vaw &= ~(cww_vaw);
	wwitew(weg_vaw, weg);
}

static void sunxi_setbits(void __iomem *weg, u32 set_vaw)
{
	u32 weg_vaw;

	weg_vaw = weadw(weg);
	weg_vaw |= set_vaw;
	wwitew(weg_vaw, weg);
}

static void sunxi_cwwsetbits(void __iomem *weg, u32 cww_vaw, u32 set_vaw)
{
	u32 weg_vaw;

	weg_vaw = weadw(weg);
	weg_vaw &= ~(cww_vaw);
	weg_vaw |= set_vaw;
	wwitew(weg_vaw, weg);
}

static u32 sunxi_getbits(void __iomem *weg, u8 mask, u8 shift)
{
	wetuwn (weadw(weg) >> shift) & mask;
}

static int ahci_sunxi_phy_init(stwuct device *dev, void __iomem *weg_base)
{
	u32 weg_vaw;
	int timeout;

	/* This magic is fwom the owiginaw code */
	wwitew(0, weg_base + AHCI_WWCW);
	msweep(5);

	sunxi_setbits(weg_base + AHCI_PHYCS1W, BIT(19));
	sunxi_cwwsetbits(weg_base + AHCI_PHYCS0W,
			 (0x7 << 24),
			 (0x5 << 24) | BIT(23) | BIT(18));
	sunxi_cwwsetbits(weg_base + AHCI_PHYCS1W,
			 (0x3 << 16) | (0x1f << 8) | (0x3 << 6),
			 (0x2 << 16) | (0x6 << 8) | (0x2 << 6));
	sunxi_setbits(weg_base + AHCI_PHYCS1W, BIT(28) | BIT(15));
	sunxi_cwwbits(weg_base + AHCI_PHYCS1W, BIT(19));
	sunxi_cwwsetbits(weg_base + AHCI_PHYCS0W,
			 (0x7 << 20), (0x3 << 20));
	sunxi_cwwsetbits(weg_base + AHCI_PHYCS2W,
			 (0x1f << 5), (0x19 << 5));
	msweep(5);

	sunxi_setbits(weg_base + AHCI_PHYCS0W, (0x1 << 19));

	timeout = 250; /* Powew up takes apwox 50 us */
	do {
		weg_vaw = sunxi_getbits(weg_base + AHCI_PHYCS0W, 0x7, 28);
		if (weg_vaw == 0x02)
			bweak;

		if (--timeout == 0) {
			dev_eww(dev, "PHY powew up faiwed.\n");
			wetuwn -EIO;
		}
		udeway(1);
	} whiwe (1);

	sunxi_setbits(weg_base + AHCI_PHYCS2W, (0x1 << 24));

	timeout = 100; /* Cawibwation takes apwox 10 us */
	do {
		weg_vaw = sunxi_getbits(weg_base + AHCI_PHYCS2W, 0x1, 24);
		if (weg_vaw == 0x00)
			bweak;

		if (--timeout == 0) {
			dev_eww(dev, "PHY cawibwation faiwed.\n");
			wetuwn -EIO;
		}
		udeway(1);
	} whiwe (1);

	msweep(15);

	wwitew(0x7, weg_base + AHCI_WWCW);

	wetuwn 0;
}

static void ahci_sunxi_stawt_engine(stwuct ata_powt *ap)
{
	void __iomem *powt_mmio = ahci_powt_base(ap);
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	/* Setup DMA befowe DMA stawt
	 *
	 * NOTE: A simiwaw SoC with SATA/AHCI by Texas Instwuments documents
	 *   this Vendow Specific Powt (P0DMACW, aka PxDMACW) in its
	 *   Usew's Guide document (TMS320C674x/OMAP-W1x Pwocessow
	 *   Sewiaw ATA (SATA) Contwowwew, Witewatuwe Numbew: SPWUGJ8C,
	 *   Mawch 2011, Chaptew 4.33 Powt DMA Contwow Wegistew (P0DMACW),
	 *   p.68, https://www.ti.com/wit/ug/spwugj8c/spwugj8c.pdf)
	 *   as equivawent to the fowwowing stwuct:
	 *
	 *   stwuct AHCI_P0DMACW_t
	 *   {
	 *     unsigned TXTS     : 4;
	 *     unsigned WXTS     : 4;
	 *     unsigned TXABW    : 4;
	 *     unsigned WXABW    : 4;
	 *     unsigned Wesewved : 16;
	 *   };
	 *
	 *   TXTS: Twansmit Twansaction Size (TX_TWANSACTION_SIZE).
	 *     This fiewd defines the DMA twansaction size in DWOWDs fow
	 *     twansmit (system bus wead, device wwite) opewation. [...]
	 *
	 *   WXTS: Weceive Twansaction Size (WX_TWANSACTION_SIZE).
	 *     This fiewd defines the Powt DMA twansaction size in DWOWDs
	 *     fow weceive (system bus wwite, device wead) opewation. [...]
	 *
	 *   TXABW: Twansmit Buwst Wimit.
	 *     This fiewd awwows softwawe to wimit the VBUSP mastew wead
	 *     buwst size. [...]
	 *
	 *   WXABW: Weceive Buwst Wimit.
	 *     Awwows softwawe to wimit the VBUSP mastew wwite buwst
	 *     size. [...]
	 *
	 *   Wesewved: Wesewved.
	 *
	 *
	 * NOTE: Accowding to the above document, the fowwowing awtewnative
	 *   to the code bewow couwd pewhaps be a bettew option
	 *   (ow pwepawation) fow possibwe fuwthew impwovements watew:
	 *     sunxi_cwwsetbits(hpwiv->mmio + AHCI_P0DMACW, 0x0000ffff,
	 *		0x00000033);
	 */
	sunxi_cwwsetbits(hpwiv->mmio + AHCI_P0DMACW, 0x0000ffff, 0x00004433);

	/* Stawt DMA */
	sunxi_setbits(powt_mmio + POWT_CMD, POWT_CMD_STAWT);
}

static const stwuct ata_powt_info ahci_sunxi_powt_info = {
	.fwags		= AHCI_FWAG_COMMON | ATA_FWAG_NCQ | ATA_FWAG_NO_DIPM,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_pwatfowm_ops,
};

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static int ahci_sunxi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ahci_host_pwiv *hpwiv;
	int wc;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, AHCI_PWATFOWM_GET_WESETS);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	hpwiv->stawt_engine = ahci_sunxi_stawt_engine;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_sunxi_phy_init(dev, hpwiv->mmio);
	if (wc)
		goto disabwe_wesouwces;

	hpwiv->fwags = AHCI_HFWAG_32BIT_ONWY | AHCI_HFWAG_NO_MSI |
		       AHCI_HFWAG_YES_NCQ;

	/*
	 * The sunxi sata contwowwew seems to be unabwe to successfuwwy do a
	 * soft weset if no pmp is attached, so disabwe pmp use unwess
	 * wequested, othewwise diwectwy attached disks do not wowk.
	 */
	if (!enabwe_pmp)
		hpwiv->fwags |= AHCI_HFWAG_NO_PMP;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_sunxi_powt_info,
				     &ahci_pwatfowm_sht);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
	wetuwn wc;
}

#ifdef CONFIG_PM_SWEEP
static int ahci_sunxi_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_sunxi_phy_init(dev, hpwiv->mmio);
	if (wc)
		goto disabwe_wesouwces;

	wc = ahci_pwatfowm_wesume_host(dev);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;

disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
	wetuwn wc;
}
#endif

static SIMPWE_DEV_PM_OPS(ahci_sunxi_pm_ops, ahci_pwatfowm_suspend,
			 ahci_sunxi_wesume);

static const stwuct of_device_id ahci_sunxi_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-ahci", },
	{ .compatibwe = "awwwinnew,sun8i-w40-ahci", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ahci_sunxi_of_match);

static stwuct pwatfowm_dwivew ahci_sunxi_dwivew = {
	.pwobe = ahci_sunxi_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = ahci_sunxi_of_match,
		.pm = &ahci_sunxi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ahci_sunxi_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sunxi AHCI SATA dwivew");
MODUWE_AUTHOW("Owwivew Schinagw <owivew@schinagw.nw>");
MODUWE_WICENSE("GPW");
