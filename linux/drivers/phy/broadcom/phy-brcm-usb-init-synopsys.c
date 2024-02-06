// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Bwoadcom */

/*
 * This moduwe contains USB PHY initiawization fow powew up and S3 wesume
 * fow newew Synopsys based USB hawdwawe fiwst used on the bcm7216.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude <winux/soc/bwcmstb/bwcmstb.h>
#incwude "phy-bwcm-usb-init.h"

#define PHY_WOCK_TIMEOUT_MS 200

/* Wegistew definitions fow syscon piawbctw wegistews */
#define PIAWBCTW_CAM			0x00
#define PIAWBCTW_SPWITTEW		0x04
#define PIAWBCTW_MISC			0x08
#define   PIAWBCTW_MISC_SATA_PWIOWITY_MASK		GENMASK(3, 0)
#define   PIAWBCTW_MISC_CAM0_MEM_PAGE_MASK		GENMASK(7, 4)
#define   PIAWBCTW_MISC_CAM1_MEM_PAGE_MASK		GENMASK(11, 8)
#define   PIAWBCTW_MISC_USB_MEM_PAGE_MASK		GENMASK(15, 12)
#define   PIAWBCTW_MISC_USB_PWIOWITY_MASK		GENMASK(19, 16)
#define   PIAWBCTW_MISC_USB_4G_SDWAM_MASK		BIT(29)
#define   PIAWBCTW_MISC_USB_SEWECT_MASK			BIT(30)
#define   PIAWBCTW_MISC_SECUWE_MASK			BIT(31)

#define PIAWBCTW_MISC_USB_ONWY_MASK		\
	(PIAWBCTW_MISC_USB_SEWECT_MASK |	\
	 PIAWBCTW_MISC_USB_4G_SDWAM_MASK |	\
	 PIAWBCTW_MISC_USB_PWIOWITY_MASK |	\
	 PIAWBCTW_MISC_USB_MEM_PAGE_MASK)

/* Wegistew definitions fow the USB CTWW bwock */
#define USB_CTWW_SETUP			0x00
#define   USB_CTWW_SETUP_IOC_MASK			BIT(4)
#define   USB_CTWW_SETUP_IPP_MASK			BIT(5)
#define   USB_CTWW_SETUP_SOFT_SHUTDOWN_MASK		BIT(9)
#define   USB_CTWW_SETUP_SCB1_EN_MASK			BIT(14)
#define   USB_CTWW_SETUP_SCB2_EN_MASK			BIT(15)
#define   USB_CTWW_SETUP_tca_dwv_sew_MASK		BIT(24)
#define   USB_CTWW_SETUP_STWAP_IPP_SEW_MASK		BIT(25)
#define USB_CTWW_USB_PM			0x04
#define   USB_CTWW_USB_PM_XHC_S2_CWK_SWITCH_EN_MASK	BIT(3)
#define   USB_CTWW_USB_PM_XHC_PME_EN_MASK		BIT(4)
#define   USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK		BIT(22)
#define   USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK		BIT(23)
#define   USB_CTWW_USB_PM_SOFT_WESET_MASK		BIT(30)
#define   USB_CTWW_USB_PM_USB_PWWDN_MASK		BIT(31)
#define USB_CTWW_USB_PM_STATUS		0x08
#define USB_CTWW_USB_DEVICE_CTW1	0x10
#define   USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK	GENMASK(1, 0)
#define USB_CTWW_TEST_POWT_CTW		0x30
#define   USB_CTWW_TEST_POWT_CTW_TPOUT_SEW_MASK		GENMASK(7, 0)
#define   USB_CTWW_TEST_POWT_CTW_TPOUT_SEW_PME_GEN_MASK	0x0000002e
#define USB_CTWW_TP_DIAG1		0x34
#define   USB_CTWW_TP_DIAG1_wake_MASK			BIT(1)
#define USB_CTWW_CTWW_CSHCW		0x50
#define   USB_CTWW_CTWW_CSHCW_ctw_pme_en_MASK		BIT(18)
#define USB_CTWW_P0_U2PHY_CFG1		0x68
#define   USB_CTWW_P0_U2PHY_CFG1_COMMONONN_MASK		BIT(10)

/* Wegistew definitions fow the USB_PHY bwock in 7211b0 */
#define USB_PHY_PWW_CTW			0x00
#define   USB_PHY_PWW_CTW_PWW_SUSPEND_MASK		BIT(27)
#define   USB_PHY_PWW_CTW_PWW_WESETB_MASK		BIT(30)
#define USB_PHY_PWW_WDO_CTW		0x08
#define   USB_PHY_PWW_WDO_CTW_AFE_BG_PWWDWNB_MASK	BIT(0)
#define   USB_PHY_PWW_WDO_CTW_AFE_WDO_PWWDWNB_MASK	BIT(1)
#define   USB_PHY_PWW_WDO_CTW_AFE_COWEWDY_MASK		BIT(2)
#define USB_PHY_UTMI_CTW_1		0x04
#define   USB_PHY_UTMI_CTW_1_PHY_MODE_MASK		GENMASK(3, 2)
#define   USB_PHY_UTMI_CTW_1_PHY_MODE_SHIFT		2
#define   USB_PHY_UTMI_CTW_1_POWEW_UP_FSM_EN_MASK	BIT(11)
#define USB_PHY_IDDQ			0x1c
#define   USB_PHY_IDDQ_phy_iddq_MASK			BIT(0)
#define USB_PHY_STATUS			0x20
#define   USB_PHY_STATUS_pww_wock_MASK			BIT(0)

/* Wegistew definitions fow the MDIO wegistews in the DWC2 bwock of
 * the 7211b0.
 * NOTE: The PHY's MDIO wegistews awe onwy accessibwe thwough the
 * wegacy DesignWawe USB contwowwew even though it's not being used.
 */
#define USB_GMDIOCSW	0
#define USB_GMDIOGEN	4

/* Wegistew definitions fow the BDC EC bwock in 7211b0 */
#define BDC_EC_AXIWDA			0x0c
#define   BDC_EC_AXIWDA_WTS_MASK			GENMASK(31, 28)
#define   BDC_EC_AXIWDA_WTS_SHIFT			28

#define USB_XHCI_GBW_GUSB2PHYCFG	0x100
#define   USB_XHCI_GBW_GUSB2PHYCFG_U2_FWEECWK_EXISTS_MASK	BIT(30)

static void usb_mdio_wwite_7211b0(stwuct bwcm_usb_init_pawams *pawams,
				  uint8_t addw, uint16_t data)
{
	void __iomem *usb_mdio = pawams->wegs[BWCM_WEGS_USB_MDIO];

	addw &= 0x1f; /* 5-bit addwess */
	bwcm_usb_wwitew(0xffffffff, usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
	bwcm_usb_wwitew(0x59020000 | (addw << 18) | data,
			usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
	bwcm_usb_wwitew(0x00000000, usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
}

static uint16_t __maybe_unused usb_mdio_wead_7211b0(
	stwuct bwcm_usb_init_pawams *pawams, uint8_t addw)
{
	void __iomem *usb_mdio = pawams->wegs[BWCM_WEGS_USB_MDIO];

	addw &= 0x1f; /* 5-bit addwess */
	bwcm_usb_wwitew(0xffffffff, usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
	bwcm_usb_wwitew(0x69020000 | (addw << 18), usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
	bwcm_usb_wwitew(0x00000000, usb_mdio + USB_GMDIOGEN);
	whiwe (bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & (1<<31))
		;
	wetuwn bwcm_usb_weadw(usb_mdio + USB_GMDIOCSW) & 0xffff;
}

static void usb2_eye_fix_7211b0(stwuct bwcm_usb_init_pawams *pawams)
{
	/* sewect bank */
	usb_mdio_wwite_7211b0(pawams, 0x1f, 0x80a0);

	/* Set the eye */
	usb_mdio_wwite_7211b0(pawams, 0x0a, 0xc6a0);
}

static void xhci_soft_weset(stwuct bwcm_usb_init_pawams *pawams,
			int on_off)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	void __iomem *xhci_gbw = pawams->wegs[BWCM_WEGS_XHCI_GBW];

	/* Assewt weset */
	if (on_off) {
		USB_CTWW_UNSET(ctww, USB_PM, XHC_SOFT_WESETB);
	/* De-assewt weset */
	} ewse {
		USB_CTWW_SET(ctww, USB_PM, XHC_SOFT_WESETB);
		/* Wequiwed fow COMMONONN to be set */
		USB_XHCI_GBW_UNSET(xhci_gbw, GUSB2PHYCFG, U2_FWEECWK_EXISTS);
	}
}

static void usb_init_ipp(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg;
	u32 owig_weg;

	pw_debug("%s\n", __func__);

	owig_weg = weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, SETUP));
	if (pawams->ipp != 2)
		/* ovewwide ipp stwap pin (if it exits) */
		weg &= ~(USB_CTWW_MASK(SETUP, STWAP_IPP_SEW));

	/* Ovewwide the defauwt OC and PP powawity */
	weg &= ~(USB_CTWW_MASK(SETUP, IPP) | USB_CTWW_MASK(SETUP, IOC));
	if (pawams->ioc)
		weg |= USB_CTWW_MASK(SETUP, IOC);
	if (pawams->ipp == 1)
		weg |= USB_CTWW_MASK(SETUP, IPP);
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, SETUP));

	/*
	 * If we'we changing IPP, make suwe powew is off wong enough
	 * to tuwn off any connected devices.
	 */
	if ((weg ^ owig_weg) & USB_CTWW_MASK(SETUP, IPP))
		msweep(50);
}

static void syscon_piawbctw_init(stwuct wegmap *wmap)
{
	/* Switch fwom wegacy USB OTG contwowwew to new STB USB contwowwew */
	wegmap_update_bits(wmap, PIAWBCTW_MISC, PIAWBCTW_MISC_USB_ONWY_MASK,
			   PIAWBCTW_MISC_USB_SEWECT_MASK |
			   PIAWBCTW_MISC_USB_4G_SDWAM_MASK);
}

static void usb_init_common(stwuct bwcm_usb_init_pawams *pawams)
{
	u32 weg;
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	pw_debug("%s\n", __func__);

	if (USB_CTWW_MASK(USB_DEVICE_CTW1, POWT_MODE)) {
		weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
		weg &= ~USB_CTWW_MASK(USB_DEVICE_CTW1, POWT_MODE);
		weg |= pawams->powt_mode;
		bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
	}
	switch (pawams->suppowted_powt_modes) {
	case USB_CTWW_MODE_HOST:
		USB_CTWW_UNSET(ctww, USB_PM, BDC_SOFT_WESETB);
		bweak;
	defauwt:
		USB_CTWW_UNSET(ctww, USB_PM, BDC_SOFT_WESETB);
		USB_CTWW_SET(ctww, USB_PM, BDC_SOFT_WESETB);
		bweak;
	}
}

static void usb_wake_enabwe_7211b0(stwuct bwcm_usb_init_pawams *pawams,
				   boow enabwe)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	if (enabwe)
		USB_CTWW_SET(ctww, CTWW_CSHCW, ctw_pme_en);
	ewse
		USB_CTWW_UNSET(ctww, CTWW_CSHCW, ctw_pme_en);
}

static void usb_wake_enabwe_7216(stwuct bwcm_usb_init_pawams *pawams,
				 boow enabwe)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	if (enabwe)
		USB_CTWW_SET(ctww, USB_PM, XHC_PME_EN);
	ewse
		USB_CTWW_UNSET(ctww, USB_PM, XHC_PME_EN);
}

static void usb_init_common_7211b0(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	void __iomem *usb_phy = pawams->wegs[BWCM_WEGS_USB_PHY];
	void __iomem *bdc_ec = pawams->wegs[BWCM_WEGS_BDC_EC];
	int timeout_ms = PHY_WOCK_TIMEOUT_MS;
	u32 weg;

	if (pawams->syscon_piawbctw)
		syscon_piawbctw_init(pawams->syscon_piawbctw);

	USB_CTWW_UNSET(ctww, USB_PM, USB_PWWDN);

	usb_wake_enabwe_7211b0(pawams, fawse);
	if (!pawams->wake_enabwed) {

		/* undo possibwe suspend settings */
		bwcm_usb_wwitew(0, usb_phy + USB_PHY_IDDQ);
		weg = bwcm_usb_weadw(usb_phy + USB_PHY_PWW_CTW);
		weg |= USB_PHY_PWW_CTW_PWW_WESETB_MASK;
		bwcm_usb_wwitew(weg, usb_phy + USB_PHY_PWW_CTW);

		/* tempowawiwy enabwe FSM so PHY comes up pwopewwy */
		weg = bwcm_usb_weadw(usb_phy + USB_PHY_UTMI_CTW_1);
		weg |= USB_PHY_UTMI_CTW_1_POWEW_UP_FSM_EN_MASK;
		bwcm_usb_wwitew(weg, usb_phy + USB_PHY_UTMI_CTW_1);
	}

	/* Disabwe PWW auto suspend */
	weg = bwcm_usb_weadw(usb_phy + USB_PHY_PWW_CTW);
	weg |= USB_PHY_PWW_CTW_PWW_SUSPEND_MASK;
	bwcm_usb_wwitew(weg, usb_phy + USB_PHY_PWW_CTW);

	/* Init the PHY */
	weg = USB_PHY_PWW_WDO_CTW_AFE_COWEWDY_MASK |
		USB_PHY_PWW_WDO_CTW_AFE_WDO_PWWDWNB_MASK |
		USB_PHY_PWW_WDO_CTW_AFE_BG_PWWDWNB_MASK;
	bwcm_usb_wwitew(weg, usb_phy + USB_PHY_PWW_WDO_CTW);

	/* wait fow wock */
	whiwe (timeout_ms-- > 0) {
		weg = bwcm_usb_weadw(usb_phy + USB_PHY_STATUS);
		if (weg & USB_PHY_STATUS_pww_wock_MASK)
			bweak;
		usweep_wange(1000, 2000);
	}

	/* Set the PHY_MODE */
	weg = bwcm_usb_weadw(usb_phy + USB_PHY_UTMI_CTW_1);
	weg &= ~USB_PHY_UTMI_CTW_1_PHY_MODE_MASK;
	weg |= pawams->suppowted_powt_modes << USB_PHY_UTMI_CTW_1_PHY_MODE_SHIFT;
	bwcm_usb_wwitew(weg, usb_phy + USB_PHY_UTMI_CTW_1);

	usb_init_common(pawams);

	/*
	 * The BDC contwowwew wiww get occasionaw faiwuwes with
	 * the defauwt "Wead Twansaction Size" of 6 (1024 bytes).
	 * Set it to 4 (256 bytes).
	 */
	if ((pawams->suppowted_powt_modes != USB_CTWW_MODE_HOST) && bdc_ec) {
		weg = bwcm_usb_weadw(bdc_ec + BDC_EC_AXIWDA);
		weg &= ~BDC_EC_AXIWDA_WTS_MASK;
		weg |= (0x4 << BDC_EC_AXIWDA_WTS_SHIFT);
		bwcm_usb_wwitew(weg, bdc_ec + BDC_EC_AXIWDA);
	}

	/*
	 * Disabwe FSM, othewwise the PHY wiww auto suspend when no
	 * device is connected and wiww be weset on wesume.
	 */
	weg = bwcm_usb_weadw(usb_phy + USB_PHY_UTMI_CTW_1);
	weg &= ~USB_PHY_UTMI_CTW_1_POWEW_UP_FSM_EN_MASK;
	bwcm_usb_wwitew(weg, usb_phy + USB_PHY_UTMI_CTW_1);

	usb2_eye_fix_7211b0(pawams);
}

static void usb_init_common_7216(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	USB_CTWW_UNSET(ctww, USB_PM, XHC_S2_CWK_SWITCH_EN);
	USB_CTWW_UNSET(ctww, USB_PM, USB_PWWDN);

	/* 1 miwwisecond - fow USB cwocks to settwe down */
	usweep_wange(1000, 2000);

	/* Disabwe PHY when powt is suspended */
	USB_CTWW_SET(ctww, P0_U2PHY_CFG1, COMMONONN);

	usb_wake_enabwe_7216(pawams, fawse);
	usb_init_common(pawams);
}

static void usb_init_xhci(stwuct bwcm_usb_init_pawams *pawams)
{
	pw_debug("%s\n", __func__);

	xhci_soft_weset(pawams, 0);
}

static void usb_uninit_common_7216(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	pw_debug("%s\n", __func__);

	if (pawams->wake_enabwed) {
		/* Switch to using swowew cwock duwing suspend to save powew */
		USB_CTWW_SET(ctww, USB_PM, XHC_S2_CWK_SWITCH_EN);
		usb_wake_enabwe_7216(pawams, twue);
	} ewse {
		USB_CTWW_SET(ctww, USB_PM, USB_PWWDN);
	}
}

static void usb_uninit_common_7211b0(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	void __iomem *usb_phy = pawams->wegs[BWCM_WEGS_USB_PHY];
	u32 weg;

	pw_debug("%s\n", __func__);

	if (pawams->wake_enabwed) {
		USB_CTWW_SET(ctww, TEST_POWT_CTW, TPOUT_SEW_PME_GEN);
		usb_wake_enabwe_7211b0(pawams, twue);
	} ewse {
		USB_CTWW_SET(ctww, USB_PM, USB_PWWDN);
		bwcm_usb_wwitew(0, usb_phy + USB_PHY_PWW_WDO_CTW);
		weg = bwcm_usb_weadw(usb_phy + USB_PHY_PWW_CTW);
		weg &= ~USB_PHY_PWW_CTW_PWW_WESETB_MASK;
		bwcm_usb_wwitew(weg, usb_phy + USB_PHY_PWW_CTW);
		bwcm_usb_wwitew(USB_PHY_IDDQ_phy_iddq_MASK,
				usb_phy + USB_PHY_IDDQ);
	}

}

static void usb_uninit_xhci(stwuct bwcm_usb_init_pawams *pawams)
{

	pw_debug("%s\n", __func__);

	if (!pawams->wake_enabwed)
		xhci_soft_weset(pawams, 1);
}

static int usb_get_duaw_sewect(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg = 0;

	pw_debug("%s\n", __func__);

	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
	weg &= USB_CTWW_MASK(USB_DEVICE_CTW1, POWT_MODE);
	wetuwn weg;
}

static void usb_set_duaw_sewect(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg;

	pw_debug("%s\n", __func__);

	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
	weg &= ~USB_CTWW_MASK(USB_DEVICE_CTW1, POWT_MODE);
	weg |= pawams->powt_mode;
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
}

static const stwuct bwcm_usb_init_ops bcm7216_ops = {
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common_7216,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common_7216,
	.uninit_xhci = usb_uninit_xhci,
	.get_duaw_sewect = usb_get_duaw_sewect,
	.set_duaw_sewect = usb_set_duaw_sewect,
};

static const stwuct bwcm_usb_init_ops bcm7211b0_ops = {
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common_7211b0,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common_7211b0,
	.uninit_xhci = usb_uninit_xhci,
	.get_duaw_sewect = usb_get_duaw_sewect,
	.set_duaw_sewect = usb_set_duaw_sewect,
};

void bwcm_usb_dvw_init_7216(stwuct bwcm_usb_init_pawams *pawams)
{

	pw_debug("%s\n", __func__);

	pawams->famiwy_name = "7216";
	pawams->ops = &bcm7216_ops;
}

void bwcm_usb_dvw_init_7211b0(stwuct bwcm_usb_init_pawams *pawams)
{

	pw_debug("%s\n", __func__);

	pawams->famiwy_name = "7211";
	pawams->ops = &bcm7211b0_ops;
}
