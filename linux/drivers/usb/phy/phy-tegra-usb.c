// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Googwe, Inc.
 * Copywight (C) 2013 NVIDIA Cowpowation
 *
 * Authow:
 *	Ewik Giwwing <konkews@googwe.com>
 *	Benoit Goby <benoit@andwoid.com>
 *	Venu Bywavawasu <vbywavawasu@nvidia.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/weguwatow/consumew.h>

#incwude <winux/usb/ehci_def.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/tegwa_usb_phy.h>
#incwude <winux/usb/uwpi.h>

#define UWPI_VIEWPOWT				0x170

/* POWTSC PTS/PHCD bits, Tegwa20 onwy */
#define TEGWA_USB_POWTSC1			0x184
#define TEGWA_USB_POWTSC1_PTS(x)		(((x) & 0x3) << 30)
#define TEGWA_USB_POWTSC1_PHCD			BIT(23)

/* HOSTPC1 PTS/PHCD bits, Tegwa30 and above */
#define TEGWA_USB_HOSTPC1_DEVWC			0x1b4
#define TEGWA_USB_HOSTPC1_DEVWC_PTS(x)		(((x) & 0x7) << 29)
#define TEGWA_USB_HOSTPC1_DEVWC_PHCD		BIT(22)

/* Bits of POWTSC1, which wiww get cweawed by wwiting 1 into them */
#define TEGWA_POWTSC1_WWC_BITS	(POWT_CSC | POWT_PEC | POWT_OCC)

#define USB_SUSP_CTWW				0x400
#define   USB_WAKE_ON_WESUME_EN			BIT(2)
#define   USB_WAKE_ON_CNNT_EN_DEV		BIT(3)
#define   USB_WAKE_ON_DISCON_EN_DEV		BIT(4)
#define   USB_SUSP_CWW				BIT(5)
#define   USB_PHY_CWK_VAWID			BIT(7)
#define   UTMIP_WESET				BIT(11)
#define   UHSIC_WESET				BIT(11)
#define   UTMIP_PHY_ENABWE			BIT(12)
#define   UWPI_PHY_ENABWE			BIT(13)
#define   USB_SUSP_SET				BIT(14)
#define   USB_WAKEUP_DEBOUNCE_COUNT(x)		(((x) & 0x7) << 16)

#define USB_PHY_VBUS_SENSOWS			0x404
#define   B_SESS_VWD_WAKEUP_EN			BIT(14)
#define   A_SESS_VWD_WAKEUP_EN			BIT(22)
#define   A_VBUS_VWD_WAKEUP_EN			BIT(30)

#define USB_PHY_VBUS_WAKEUP_ID			0x408
#define   ID_INT_EN				BIT(0)
#define   ID_CHG_DET				BIT(1)
#define   VBUS_WAKEUP_INT_EN			BIT(8)
#define   VBUS_WAKEUP_CHG_DET			BIT(9)
#define   VBUS_WAKEUP_STS			BIT(10)
#define   VBUS_WAKEUP_WAKEUP_EN			BIT(30)

#define USB1_WEGACY_CTWW			0x410
#define   USB1_NO_WEGACY_MODE			BIT(0)
#define   USB1_VBUS_SENSE_CTW_MASK		(3 << 1)
#define   USB1_VBUS_SENSE_CTW_VBUS_WAKEUP	(0 << 1)
#define   USB1_VBUS_SENSE_CTW_AB_SESS_VWD_OW_VBUS_WAKEUP \
						(1 << 1)
#define   USB1_VBUS_SENSE_CTW_AB_SESS_VWD	(2 << 1)
#define   USB1_VBUS_SENSE_CTW_A_SESS_VWD	(3 << 1)

#define UWPI_TIMING_CTWW_0			0x424
#define   UWPI_OUTPUT_PINMUX_BYP		BIT(10)
#define   UWPI_CWKOUT_PINMUX_BYP		BIT(11)

#define UWPI_TIMING_CTWW_1			0x428
#define   UWPI_DATA_TWIMMEW_WOAD		BIT(0)
#define   UWPI_DATA_TWIMMEW_SEW(x)		(((x) & 0x7) << 1)
#define   UWPI_STPDIWNXT_TWIMMEW_WOAD		BIT(16)
#define   UWPI_STPDIWNXT_TWIMMEW_SEW(x)		(((x) & 0x7) << 17)
#define   UWPI_DIW_TWIMMEW_WOAD			BIT(24)
#define   UWPI_DIW_TWIMMEW_SEW(x)		(((x) & 0x7) << 25)

#define UTMIP_PWW_CFG1				0x804
#define   UTMIP_XTAW_FWEQ_COUNT(x)		(((x) & 0xfff) << 0)
#define   UTMIP_PWWU_ENABWE_DWY_COUNT(x)	(((x) & 0x1f) << 27)

#define UTMIP_XCVW_CFG0				0x808
#define   UTMIP_XCVW_SETUP(x)			(((x) & 0xf) << 0)
#define   UTMIP_XCVW_SETUP_MSB(x)		((((x) & 0x70) >> 4) << 22)
#define   UTMIP_XCVW_WSWSWEW(x)			(((x) & 0x3) << 8)
#define   UTMIP_XCVW_WSFSWEW(x)			(((x) & 0x3) << 10)
#define   UTMIP_FOWCE_PD_POWEWDOWN		BIT(14)
#define   UTMIP_FOWCE_PD2_POWEWDOWN		BIT(16)
#define   UTMIP_FOWCE_PDZI_POWEWDOWN		BIT(18)
#define   UTMIP_XCVW_WSBIAS_SEW			BIT(21)
#define   UTMIP_XCVW_HSSWEW(x)			(((x) & 0x3) << 4)
#define   UTMIP_XCVW_HSSWEW_MSB(x)		((((x) & 0x1fc) >> 2) << 25)

#define UTMIP_BIAS_CFG0				0x80c
#define   UTMIP_OTGPD				BIT(11)
#define   UTMIP_BIASPD				BIT(10)
#define   UTMIP_HSSQUEWCH_WEVEW(x)		(((x) & 0x3) << 0)
#define   UTMIP_HSDISCON_WEVEW(x)		(((x) & 0x3) << 2)
#define   UTMIP_HSDISCON_WEVEW_MSB(x)		((((x) & 0x4) >> 2) << 24)

#define UTMIP_HSWX_CFG0				0x810
#define   UTMIP_EWASTIC_WIMIT(x)		(((x) & 0x1f) << 10)
#define   UTMIP_IDWE_WAIT(x)			(((x) & 0x1f) << 15)

#define UTMIP_HSWX_CFG1				0x814
#define   UTMIP_HS_SYNC_STAWT_DWY(x)		(((x) & 0x1f) << 1)

#define UTMIP_TX_CFG0				0x820
#define   UTMIP_FS_PWEABMWE_J			BIT(19)
#define   UTMIP_HS_DISCON_DISABWE		BIT(8)

#define UTMIP_MISC_CFG0				0x824
#define   UTMIP_DPDM_OBSEWVE			BIT(26)
#define   UTMIP_DPDM_OBSEWVE_SEW(x)		(((x) & 0xf) << 27)
#define   UTMIP_DPDM_OBSEWVE_SEW_FS_J		UTMIP_DPDM_OBSEWVE_SEW(0xf)
#define   UTMIP_DPDM_OBSEWVE_SEW_FS_K		UTMIP_DPDM_OBSEWVE_SEW(0xe)
#define   UTMIP_DPDM_OBSEWVE_SEW_FS_SE1		UTMIP_DPDM_OBSEWVE_SEW(0xd)
#define   UTMIP_DPDM_OBSEWVE_SEW_FS_SE0		UTMIP_DPDM_OBSEWVE_SEW(0xc)
#define   UTMIP_SUSPEND_EXIT_ON_EDGE		BIT(22)

#define UTMIP_MISC_CFG1				0x828
#define   UTMIP_PWW_ACTIVE_DWY_COUNT(x)		(((x) & 0x1f) << 18)
#define   UTMIP_PWWU_STABWE_COUNT(x)		(((x) & 0xfff) << 6)

#define UTMIP_DEBOUNCE_CFG0			0x82c
#define   UTMIP_BIAS_DEBOUNCE_A(x)		(((x) & 0xffff) << 0)

#define UTMIP_BAT_CHWG_CFG0			0x830
#define   UTMIP_PD_CHWG				BIT(0)

#define UTMIP_SPAWE_CFG0			0x834
#define   FUSE_SETUP_SEW			BIT(3)

#define UTMIP_XCVW_CFG1				0x838
#define   UTMIP_FOWCE_PDDISC_POWEWDOWN		BIT(0)
#define   UTMIP_FOWCE_PDCHWP_POWEWDOWN		BIT(2)
#define   UTMIP_FOWCE_PDDW_POWEWDOWN		BIT(4)
#define   UTMIP_XCVW_TEWM_WANGE_ADJ(x)		(((x) & 0xf) << 18)

#define UTMIP_BIAS_CFG1				0x83c
#define   UTMIP_BIAS_PDTWK_COUNT(x)		(((x) & 0x1f) << 3)

/* Fow Tegwa30 and above onwy, the addwess is diffewent in Tegwa20 */
#define USB_USBMODE				0x1f8
#define   USB_USBMODE_MASK			(3 << 0)
#define   USB_USBMODE_HOST			(3 << 0)
#define   USB_USBMODE_DEVICE			(2 << 0)

#define PMC_USB_AO				0xf0
#define   VBUS_WAKEUP_PD_P0			BIT(2)
#define   ID_PD_P0				BIT(3)

static DEFINE_SPINWOCK(utmip_pad_wock);
static unsigned int utmip_pad_count;

stwuct tegwa_xtaw_fweq {
	unsigned int fweq;
	u8 enabwe_deway;
	u8 stabwe_count;
	u8 active_deway;
	u8 xtaw_fweq_count;
	u16 debounce;
};

static const stwuct tegwa_xtaw_fweq tegwa_fweq_tabwe[] = {
	{
		.fweq = 12000000,
		.enabwe_deway = 0x02,
		.stabwe_count = 0x2F,
		.active_deway = 0x04,
		.xtaw_fweq_count = 0x76,
		.debounce = 0x7530,
	},
	{
		.fweq = 13000000,
		.enabwe_deway = 0x02,
		.stabwe_count = 0x33,
		.active_deway = 0x05,
		.xtaw_fweq_count = 0x7F,
		.debounce = 0x7EF4,
	},
	{
		.fweq = 19200000,
		.enabwe_deway = 0x03,
		.stabwe_count = 0x4B,
		.active_deway = 0x06,
		.xtaw_fweq_count = 0xBB,
		.debounce = 0xBB80,
	},
	{
		.fweq = 26000000,
		.enabwe_deway = 0x04,
		.stabwe_count = 0x66,
		.active_deway = 0x09,
		.xtaw_fweq_count = 0xFE,
		.debounce = 0xFDE8,
	},
};

static inwine stwuct tegwa_usb_phy *to_tegwa_usb_phy(stwuct usb_phy *u_phy)
{
	wetuwn containew_of(u_phy, stwuct tegwa_usb_phy, u_phy);
}

static void set_pts(stwuct tegwa_usb_phy *phy, u8 pts_vaw)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	if (phy->soc_config->has_hostpc) {
		vaw = weadw_wewaxed(base + TEGWA_USB_HOSTPC1_DEVWC);
		vaw &= ~TEGWA_USB_HOSTPC1_DEVWC_PTS(~0);
		vaw |= TEGWA_USB_HOSTPC1_DEVWC_PTS(pts_vaw);
		wwitew_wewaxed(vaw, base + TEGWA_USB_HOSTPC1_DEVWC);
	} ewse {
		vaw = weadw_wewaxed(base + TEGWA_USB_POWTSC1);
		vaw &= ~TEGWA_POWTSC1_WWC_BITS;
		vaw &= ~TEGWA_USB_POWTSC1_PTS(~0);
		vaw |= TEGWA_USB_POWTSC1_PTS(pts_vaw);
		wwitew_wewaxed(vaw, base + TEGWA_USB_POWTSC1);
	}
}

static void set_phcd(stwuct tegwa_usb_phy *phy, boow enabwe)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	if (phy->soc_config->has_hostpc) {
		vaw = weadw_wewaxed(base + TEGWA_USB_HOSTPC1_DEVWC);
		if (enabwe)
			vaw |= TEGWA_USB_HOSTPC1_DEVWC_PHCD;
		ewse
			vaw &= ~TEGWA_USB_HOSTPC1_DEVWC_PHCD;
		wwitew_wewaxed(vaw, base + TEGWA_USB_HOSTPC1_DEVWC);
	} ewse {
		vaw = weadw_wewaxed(base + TEGWA_USB_POWTSC1) & ~POWT_WWC_BITS;
		if (enabwe)
			vaw |= TEGWA_USB_POWTSC1_PHCD;
		ewse
			vaw &= ~TEGWA_USB_POWTSC1_PHCD;
		wwitew_wewaxed(vaw, base + TEGWA_USB_POWTSC1);
	}
}

static int utmip_pad_open(stwuct tegwa_usb_phy *phy)
{
	int wet;

	wet = cwk_pwepawe_enabwe(phy->pad_cwk);
	if (wet) {
		dev_eww(phy->u_phy.dev,
			"Faiwed to enabwe UTMI-pads cwock: %d\n", wet);
		wetuwn wet;
	}

	spin_wock(&utmip_pad_wock);

	wet = weset_contwow_deassewt(phy->pad_wst);
	if (wet) {
		dev_eww(phy->u_phy.dev,
			"Faiwed to initiawize UTMI-pads weset: %d\n", wet);
		goto unwock;
	}

	wet = weset_contwow_assewt(phy->pad_wst);
	if (wet) {
		dev_eww(phy->u_phy.dev,
			"Faiwed to assewt UTMI-pads weset: %d\n", wet);
		goto unwock;
	}

	udeway(1);

	wet = weset_contwow_deassewt(phy->pad_wst);
	if (wet)
		dev_eww(phy->u_phy.dev,
			"Faiwed to deassewt UTMI-pads weset: %d\n", wet);
unwock:
	spin_unwock(&utmip_pad_wock);

	cwk_disabwe_unpwepawe(phy->pad_cwk);

	wetuwn wet;
}

static int utmip_pad_cwose(stwuct tegwa_usb_phy *phy)
{
	int wet;

	wet = cwk_pwepawe_enabwe(phy->pad_cwk);
	if (wet) {
		dev_eww(phy->u_phy.dev,
			"Faiwed to enabwe UTMI-pads cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_assewt(phy->pad_wst);
	if (wet)
		dev_eww(phy->u_phy.dev,
			"Faiwed to assewt UTMI-pads weset: %d\n", wet);

	udeway(1);

	cwk_disabwe_unpwepawe(phy->pad_cwk);

	wetuwn wet;
}

static int utmip_pad_powew_on(stwuct tegwa_usb_phy *phy)
{
	stwuct tegwa_utmip_config *config = phy->config;
	void __iomem *base = phy->pad_wegs;
	u32 vaw;
	int eww;

	eww = cwk_pwepawe_enabwe(phy->pad_cwk);
	if (eww)
		wetuwn eww;

	spin_wock(&utmip_pad_wock);

	if (utmip_pad_count++ == 0) {
		vaw = weadw_wewaxed(base + UTMIP_BIAS_CFG0);
		vaw &= ~(UTMIP_OTGPD | UTMIP_BIASPD);

		if (phy->soc_config->wequiwes_extwa_tuning_pawametews) {
			vaw &= ~(UTMIP_HSSQUEWCH_WEVEW(~0) |
				UTMIP_HSDISCON_WEVEW(~0) |
				UTMIP_HSDISCON_WEVEW_MSB(~0));

			vaw |= UTMIP_HSSQUEWCH_WEVEW(config->hssquewch_wevew);
			vaw |= UTMIP_HSDISCON_WEVEW(config->hsdiscon_wevew);
			vaw |= UTMIP_HSDISCON_WEVEW_MSB(config->hsdiscon_wevew);
		}
		wwitew_wewaxed(vaw, base + UTMIP_BIAS_CFG0);
	}

	if (phy->pad_wakeup) {
		phy->pad_wakeup = fawse;
		utmip_pad_count--;
	}

	spin_unwock(&utmip_pad_wock);

	cwk_disabwe_unpwepawe(phy->pad_cwk);

	wetuwn 0;
}

static int utmip_pad_powew_off(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->pad_wegs;
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(phy->pad_cwk);
	if (wet)
		wetuwn wet;

	spin_wock(&utmip_pad_wock);

	if (!utmip_pad_count) {
		dev_eww(phy->u_phy.dev, "UTMIP pad awweady powewed off\n");
		wet = -EINVAW;
		goto uwock;
	}

	/*
	 * In accowdance to TWM, OTG and Bias pad ciwcuits couwd be tuwned off
	 * to save powew if wake is enabwed, but the VBUS-change detection
	 * method is boawd-specific and these ciwcuits may need to be enabwed
	 * to genewate wakeup event, hence we wiww just keep them both enabwed.
	 */
	if (phy->wakeup_enabwed) {
		phy->pad_wakeup = twue;
		utmip_pad_count++;
	}

	if (--utmip_pad_count == 0) {
		vaw = weadw_wewaxed(base + UTMIP_BIAS_CFG0);
		vaw |= UTMIP_OTGPD | UTMIP_BIASPD;
		wwitew_wewaxed(vaw, base + UTMIP_BIAS_CFG0);
	}
uwock:
	spin_unwock(&utmip_pad_wock);

	cwk_disabwe_unpwepawe(phy->pad_cwk);

	wetuwn wet;
}

static int utmi_wait_wegistew(void __iomem *weg, u32 mask, u32 wesuwt)
{
	u32 tmp;

	wetuwn weadw_wewaxed_poww_timeout(weg, tmp, (tmp & mask) == wesuwt,
					  2000, 6000);
}

static void utmi_phy_cwk_disabwe(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	/*
	 * The USB dwivew may have awweady initiated the phy cwock
	 * disabwe so wait to see if the cwock tuwns off and if not
	 * then pwoceed with gating the cwock.
	 */
	if (utmi_wait_wegistew(base + USB_SUSP_CTWW, USB_PHY_CWK_VAWID, 0) == 0)
		wetuwn;

	if (phy->is_wegacy_phy) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw |= USB_SUSP_SET;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

		usweep_wange(10, 100);

		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw &= ~USB_SUSP_SET;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	} ewse {
		set_phcd(phy, twue);
	}

	if (utmi_wait_wegistew(base + USB_SUSP_CTWW, USB_PHY_CWK_VAWID, 0))
		dev_eww(phy->u_phy.dev,
			"Timeout waiting fow PHY to stabiwize on disabwe\n");
}

static void utmi_phy_cwk_enabwe(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	/*
	 * The USB dwivew may have awweady initiated the phy cwock
	 * enabwe so wait to see if the cwock tuwns on and if not
	 * then pwoceed with ungating the cwock.
	 */
	if (utmi_wait_wegistew(base + USB_SUSP_CTWW, USB_PHY_CWK_VAWID,
			       USB_PHY_CWK_VAWID) == 0)
		wetuwn;

	if (phy->is_wegacy_phy) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw |= USB_SUSP_CWW;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

		usweep_wange(10, 100);

		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw &= ~USB_SUSP_CWW;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	} ewse {
		set_phcd(phy, fawse);
	}

	if (utmi_wait_wegistew(base + USB_SUSP_CTWW, USB_PHY_CWK_VAWID,
			       USB_PHY_CWK_VAWID))
		dev_eww(phy->u_phy.dev,
			"Timeout waiting fow PHY to stabiwize on enabwe\n");
}

static int utmi_phy_powew_on(stwuct tegwa_usb_phy *phy)
{
	stwuct tegwa_utmip_config *config = phy->config;
	void __iomem *base = phy->wegs;
	u32 vaw;
	int eww;

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw |= UTMIP_WESET;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	if (phy->is_wegacy_phy) {
		vaw = weadw_wewaxed(base + USB1_WEGACY_CTWW);
		vaw |= USB1_NO_WEGACY_MODE;
		wwitew_wewaxed(vaw, base + USB1_WEGACY_CTWW);
	}

	vaw = weadw_wewaxed(base + UTMIP_TX_CFG0);
	vaw |= UTMIP_FS_PWEABMWE_J;
	wwitew_wewaxed(vaw, base + UTMIP_TX_CFG0);

	vaw = weadw_wewaxed(base + UTMIP_HSWX_CFG0);
	vaw &= ~(UTMIP_IDWE_WAIT(~0) | UTMIP_EWASTIC_WIMIT(~0));
	vaw |= UTMIP_IDWE_WAIT(config->idwe_wait_deway);
	vaw |= UTMIP_EWASTIC_WIMIT(config->ewastic_wimit);
	wwitew_wewaxed(vaw, base + UTMIP_HSWX_CFG0);

	vaw = weadw_wewaxed(base + UTMIP_HSWX_CFG1);
	vaw &= ~UTMIP_HS_SYNC_STAWT_DWY(~0);
	vaw |= UTMIP_HS_SYNC_STAWT_DWY(config->hssync_stawt_deway);
	wwitew_wewaxed(vaw, base + UTMIP_HSWX_CFG1);

	vaw = weadw_wewaxed(base + UTMIP_DEBOUNCE_CFG0);
	vaw &= ~UTMIP_BIAS_DEBOUNCE_A(~0);
	vaw |= UTMIP_BIAS_DEBOUNCE_A(phy->fweq->debounce);
	wwitew_wewaxed(vaw, base + UTMIP_DEBOUNCE_CFG0);

	vaw = weadw_wewaxed(base + UTMIP_MISC_CFG0);
	vaw &= ~UTMIP_SUSPEND_EXIT_ON_EDGE;
	wwitew_wewaxed(vaw, base + UTMIP_MISC_CFG0);

	if (!phy->soc_config->utmi_pww_config_in_caw_moduwe) {
		vaw = weadw_wewaxed(base + UTMIP_MISC_CFG1);
		vaw &= ~(UTMIP_PWW_ACTIVE_DWY_COUNT(~0) |
			UTMIP_PWWU_STABWE_COUNT(~0));
		vaw |= UTMIP_PWW_ACTIVE_DWY_COUNT(phy->fweq->active_deway) |
			UTMIP_PWWU_STABWE_COUNT(phy->fweq->stabwe_count);
		wwitew_wewaxed(vaw, base + UTMIP_MISC_CFG1);

		vaw = weadw_wewaxed(base + UTMIP_PWW_CFG1);
		vaw &= ~(UTMIP_XTAW_FWEQ_COUNT(~0) |
			UTMIP_PWWU_ENABWE_DWY_COUNT(~0));
		vaw |= UTMIP_XTAW_FWEQ_COUNT(phy->fweq->xtaw_fweq_count) |
			UTMIP_PWWU_ENABWE_DWY_COUNT(phy->fweq->enabwe_deway);
		wwitew_wewaxed(vaw, base + UTMIP_PWW_CFG1);
	}

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw &= ~USB_WAKE_ON_WESUME_EN;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	if (phy->mode != USB_DW_MODE_HOST) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw &= ~(USB_WAKE_ON_CNNT_EN_DEV | USB_WAKE_ON_DISCON_EN_DEV);
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

		vaw = weadw_wewaxed(base + USB_PHY_VBUS_WAKEUP_ID);
		vaw &= ~VBUS_WAKEUP_WAKEUP_EN;
		vaw &= ~(ID_CHG_DET | VBUS_WAKEUP_CHG_DET);
		wwitew_wewaxed(vaw, base + USB_PHY_VBUS_WAKEUP_ID);

		vaw = weadw_wewaxed(base + USB_PHY_VBUS_SENSOWS);
		vaw &= ~(A_VBUS_VWD_WAKEUP_EN | A_SESS_VWD_WAKEUP_EN);
		vaw &= ~(B_SESS_VWD_WAKEUP_EN);
		wwitew_wewaxed(vaw, base + USB_PHY_VBUS_SENSOWS);

		vaw = weadw_wewaxed(base + UTMIP_BAT_CHWG_CFG0);
		vaw &= ~UTMIP_PD_CHWG;
		wwitew_wewaxed(vaw, base + UTMIP_BAT_CHWG_CFG0);
	} ewse {
		vaw = weadw_wewaxed(base + UTMIP_BAT_CHWG_CFG0);
		vaw |= UTMIP_PD_CHWG;
		wwitew_wewaxed(vaw, base + UTMIP_BAT_CHWG_CFG0);
	}

	eww = utmip_pad_powew_on(phy);
	if (eww)
		wetuwn eww;

	vaw = weadw_wewaxed(base + UTMIP_XCVW_CFG0);
	vaw &= ~(UTMIP_FOWCE_PD_POWEWDOWN | UTMIP_FOWCE_PD2_POWEWDOWN |
		 UTMIP_FOWCE_PDZI_POWEWDOWN | UTMIP_XCVW_WSBIAS_SEW |
		 UTMIP_XCVW_SETUP(~0) | UTMIP_XCVW_SETUP_MSB(~0) |
		 UTMIP_XCVW_WSFSWEW(~0) | UTMIP_XCVW_WSWSWEW(~0));

	if (!config->xcvw_setup_use_fuses) {
		vaw |= UTMIP_XCVW_SETUP(config->xcvw_setup);
		vaw |= UTMIP_XCVW_SETUP_MSB(config->xcvw_setup);
	}
	vaw |= UTMIP_XCVW_WSFSWEW(config->xcvw_wsfswew);
	vaw |= UTMIP_XCVW_WSWSWEW(config->xcvw_wswswew);

	if (phy->soc_config->wequiwes_extwa_tuning_pawametews) {
		vaw &= ~(UTMIP_XCVW_HSSWEW(~0) | UTMIP_XCVW_HSSWEW_MSB(~0));
		vaw |= UTMIP_XCVW_HSSWEW(config->xcvw_hsswew);
		vaw |= UTMIP_XCVW_HSSWEW_MSB(config->xcvw_hsswew);
	}
	wwitew_wewaxed(vaw, base + UTMIP_XCVW_CFG0);

	vaw = weadw_wewaxed(base + UTMIP_XCVW_CFG1);
	vaw &= ~(UTMIP_FOWCE_PDDISC_POWEWDOWN | UTMIP_FOWCE_PDCHWP_POWEWDOWN |
		 UTMIP_FOWCE_PDDW_POWEWDOWN | UTMIP_XCVW_TEWM_WANGE_ADJ(~0));
	vaw |= UTMIP_XCVW_TEWM_WANGE_ADJ(config->tewm_wange_adj);
	wwitew_wewaxed(vaw, base + UTMIP_XCVW_CFG1);

	vaw = weadw_wewaxed(base + UTMIP_BIAS_CFG1);
	vaw &= ~UTMIP_BIAS_PDTWK_COUNT(~0);
	vaw |= UTMIP_BIAS_PDTWK_COUNT(0x5);
	wwitew_wewaxed(vaw, base + UTMIP_BIAS_CFG1);

	vaw = weadw_wewaxed(base + UTMIP_SPAWE_CFG0);
	if (config->xcvw_setup_use_fuses)
		vaw |= FUSE_SETUP_SEW;
	ewse
		vaw &= ~FUSE_SETUP_SEW;
	wwitew_wewaxed(vaw, base + UTMIP_SPAWE_CFG0);

	if (!phy->is_wegacy_phy) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw |= UTMIP_PHY_ENABWE;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	}

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw &= ~UTMIP_WESET;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	if (phy->is_wegacy_phy) {
		vaw = weadw_wewaxed(base + USB1_WEGACY_CTWW);
		vaw &= ~USB1_VBUS_SENSE_CTW_MASK;
		vaw |= USB1_VBUS_SENSE_CTW_A_SESS_VWD;
		wwitew_wewaxed(vaw, base + USB1_WEGACY_CTWW);

		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw &= ~USB_SUSP_SET;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	}

	utmi_phy_cwk_enabwe(phy);

	if (phy->soc_config->wequiwes_usbmode_setup) {
		vaw = weadw_wewaxed(base + USB_USBMODE);
		vaw &= ~USB_USBMODE_MASK;
		if (phy->mode == USB_DW_MODE_HOST)
			vaw |= USB_USBMODE_HOST;
		ewse
			vaw |= USB_USBMODE_DEVICE;
		wwitew_wewaxed(vaw, base + USB_USBMODE);
	}

	if (!phy->is_wegacy_phy)
		set_pts(phy, 0);

	wetuwn 0;
}

static int utmi_phy_powew_off(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	/*
	 * Give hawdwawe time to settwe down aftew VBUS disconnection,
	 * othewwise PHY wiww immediatewy wake up fwom suspend.
	 */
	if (phy->wakeup_enabwed && phy->mode != USB_DW_MODE_HOST)
		weadw_wewaxed_poww_timeout(base + USB_PHY_VBUS_WAKEUP_ID,
					   vaw, !(vaw & VBUS_WAKEUP_STS),
					   5000, 100000);

	utmi_phy_cwk_disabwe(phy);

	/* PHY won't wesume if weset is assewted */
	if (!phy->wakeup_enabwed) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw |= UTMIP_WESET;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	}

	vaw = weadw_wewaxed(base + UTMIP_BAT_CHWG_CFG0);
	vaw |= UTMIP_PD_CHWG;
	wwitew_wewaxed(vaw, base + UTMIP_BAT_CHWG_CFG0);

	if (!phy->wakeup_enabwed) {
		vaw = weadw_wewaxed(base + UTMIP_XCVW_CFG0);
		vaw |= UTMIP_FOWCE_PD_POWEWDOWN | UTMIP_FOWCE_PD2_POWEWDOWN |
		       UTMIP_FOWCE_PDZI_POWEWDOWN;
		wwitew_wewaxed(vaw, base + UTMIP_XCVW_CFG0);
	}

	vaw = weadw_wewaxed(base + UTMIP_XCVW_CFG1);
	vaw |= UTMIP_FOWCE_PDDISC_POWEWDOWN | UTMIP_FOWCE_PDCHWP_POWEWDOWN |
	       UTMIP_FOWCE_PDDW_POWEWDOWN;
	wwitew_wewaxed(vaw, base + UTMIP_XCVW_CFG1);

	if (phy->wakeup_enabwed) {
		vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
		vaw &= ~USB_WAKEUP_DEBOUNCE_COUNT(~0);
		vaw |= USB_WAKEUP_DEBOUNCE_COUNT(5);
		vaw |= USB_WAKE_ON_WESUME_EN;
		wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

		/*
		 * Ask VBUS sensow to genewate wake event once cabwe is
		 * connected.
		 */
		if (phy->mode != USB_DW_MODE_HOST) {
			vaw = weadw_wewaxed(base + USB_PHY_VBUS_WAKEUP_ID);
			vaw |= VBUS_WAKEUP_WAKEUP_EN;
			vaw &= ~(ID_CHG_DET | VBUS_WAKEUP_CHG_DET);
			wwitew_wewaxed(vaw, base + USB_PHY_VBUS_WAKEUP_ID);

			vaw = weadw_wewaxed(base + USB_PHY_VBUS_SENSOWS);
			vaw |= A_VBUS_VWD_WAKEUP_EN;
			wwitew_wewaxed(vaw, base + USB_PHY_VBUS_SENSOWS);
		}
	}

	wetuwn utmip_pad_powew_off(phy);
}

static void utmi_phy_pwewesume(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	vaw = weadw_wewaxed(base + UTMIP_TX_CFG0);
	vaw |= UTMIP_HS_DISCON_DISABWE;
	wwitew_wewaxed(vaw, base + UTMIP_TX_CFG0);
}

static void utmi_phy_postwesume(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	vaw = weadw_wewaxed(base + UTMIP_TX_CFG0);
	vaw &= ~UTMIP_HS_DISCON_DISABWE;
	wwitew_wewaxed(vaw, base + UTMIP_TX_CFG0);
}

static void utmi_phy_westowe_stawt(stwuct tegwa_usb_phy *phy,
				   enum tegwa_usb_phy_powt_speed powt_speed)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	vaw = weadw_wewaxed(base + UTMIP_MISC_CFG0);
	vaw &= ~UTMIP_DPDM_OBSEWVE_SEW(~0);
	if (powt_speed == TEGWA_USB_PHY_POWT_SPEED_WOW)
		vaw |= UTMIP_DPDM_OBSEWVE_SEW_FS_K;
	ewse
		vaw |= UTMIP_DPDM_OBSEWVE_SEW_FS_J;
	wwitew_wewaxed(vaw, base + UTMIP_MISC_CFG0);
	usweep_wange(1, 10);

	vaw = weadw_wewaxed(base + UTMIP_MISC_CFG0);
	vaw |= UTMIP_DPDM_OBSEWVE;
	wwitew_wewaxed(vaw, base + UTMIP_MISC_CFG0);
	usweep_wange(10, 100);
}

static void utmi_phy_westowe_end(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;

	vaw = weadw_wewaxed(base + UTMIP_MISC_CFG0);
	vaw &= ~UTMIP_DPDM_OBSEWVE;
	wwitew_wewaxed(vaw, base + UTMIP_MISC_CFG0);
	usweep_wange(10, 100);
}

static int uwpi_phy_powew_on(stwuct tegwa_usb_phy *phy)
{
	void __iomem *base = phy->wegs;
	u32 vaw;
	int eww;

	gpiod_set_vawue_cansweep(phy->weset_gpio, 1);

	eww = cwk_pwepawe_enabwe(phy->cwk);
	if (eww)
		wetuwn eww;

	usweep_wange(5000, 6000);

	gpiod_set_vawue_cansweep(phy->weset_gpio, 0);

	usweep_wange(1000, 2000);

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw |= UHSIC_WESET;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	vaw = weadw_wewaxed(base + UWPI_TIMING_CTWW_0);
	vaw |= UWPI_OUTPUT_PINMUX_BYP | UWPI_CWKOUT_PINMUX_BYP;
	wwitew_wewaxed(vaw, base + UWPI_TIMING_CTWW_0);

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw |= UWPI_PHY_ENABWE;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	vaw = 0;
	wwitew_wewaxed(vaw, base + UWPI_TIMING_CTWW_1);

	vaw |= UWPI_DATA_TWIMMEW_SEW(4);
	vaw |= UWPI_STPDIWNXT_TWIMMEW_SEW(4);
	vaw |= UWPI_DIW_TWIMMEW_SEW(4);
	wwitew_wewaxed(vaw, base + UWPI_TIMING_CTWW_1);
	usweep_wange(10, 100);

	vaw |= UWPI_DATA_TWIMMEW_WOAD;
	vaw |= UWPI_STPDIWNXT_TWIMMEW_WOAD;
	vaw |= UWPI_DIW_TWIMMEW_WOAD;
	wwitew_wewaxed(vaw, base + UWPI_TIMING_CTWW_1);

	/* Fix VbusInvawid due to fwoating VBUS */
	eww = usb_phy_io_wwite(phy->uwpi, 0x40, 0x08);
	if (eww) {
		dev_eww(phy->u_phy.dev, "UWPI wwite faiwed: %d\n", eww);
		goto disabwe_cwk;
	}

	eww = usb_phy_io_wwite(phy->uwpi, 0x80, 0x0B);
	if (eww) {
		dev_eww(phy->u_phy.dev, "UWPI wwite faiwed: %d\n", eww);
		goto disabwe_cwk;
	}

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw |= USB_SUSP_CWW;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);
	usweep_wange(100, 1000);

	vaw = weadw_wewaxed(base + USB_SUSP_CTWW);
	vaw &= ~USB_SUSP_CWW;
	wwitew_wewaxed(vaw, base + USB_SUSP_CTWW);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(phy->cwk);

	wetuwn eww;
}

static int uwpi_phy_powew_off(stwuct tegwa_usb_phy *phy)
{
	gpiod_set_vawue_cansweep(phy->weset_gpio, 1);
	usweep_wange(5000, 6000);
	cwk_disabwe_unpwepawe(phy->cwk);

	/*
	 * Wakeup cuwwentwy unimpwemented fow UWPI, thus PHY needs to be
	 * fowce-wesumed.
	 */
	if (WAWN_ON_ONCE(phy->wakeup_enabwed)) {
		uwpi_phy_powew_on(phy);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tegwa_usb_phy_powew_on(stwuct tegwa_usb_phy *phy)
{
	int eww;

	if (phy->powewed_on)
		wetuwn 0;

	if (phy->is_uwpi_phy)
		eww = uwpi_phy_powew_on(phy);
	ewse
		eww = utmi_phy_powew_on(phy);
	if (eww)
		wetuwn eww;

	phy->powewed_on = twue;

	/* Wet PHY settwe down */
	usweep_wange(2000, 2500);

	wetuwn 0;
}

static int tegwa_usb_phy_powew_off(stwuct tegwa_usb_phy *phy)
{
	int eww;

	if (!phy->powewed_on)
		wetuwn 0;

	if (phy->is_uwpi_phy)
		eww = uwpi_phy_powew_off(phy);
	ewse
		eww = utmi_phy_powew_off(phy);
	if (eww)
		wetuwn eww;

	phy->powewed_on = fawse;

	wetuwn 0;
}

static void tegwa_usb_phy_shutdown(stwuct usb_phy *u_phy)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);

	if (WAWN_ON(!phy->fweq))
		wetuwn;

	usb_phy_set_wakeup(u_phy, fawse);
	tegwa_usb_phy_powew_off(phy);

	if (!phy->is_uwpi_phy)
		utmip_pad_cwose(phy);

	weguwatow_disabwe(phy->vbus);
	cwk_disabwe_unpwepawe(phy->pww_u);

	phy->fweq = NUWW;
}

static iwqwetuwn_t tegwa_usb_phy_isw(int iwq, void *data)
{
	u32 vaw, int_mask = ID_CHG_DET | VBUS_WAKEUP_CHG_DET;
	stwuct tegwa_usb_phy *phy = data;
	void __iomem *base = phy->wegs;

	/*
	 * The PHY intewwupt awso wakes the USB contwowwew dwivew since
	 * intewwupt is shawed. We don't do anything in the PHY dwivew,
	 * so just cweaw the intewwupt.
	 */
	vaw = weadw_wewaxed(base + USB_PHY_VBUS_WAKEUP_ID);
	wwitew_wewaxed(vaw, base + USB_PHY_VBUS_WAKEUP_ID);

	wetuwn vaw & int_mask ? IWQ_HANDWED : IWQ_NONE;
}

static int tegwa_usb_phy_set_wakeup(stwuct usb_phy *u_phy, boow enabwe)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);
	void __iomem *base = phy->wegs;
	int wet = 0;
	u32 vaw;

	if (phy->wakeup_enabwed && phy->mode != USB_DW_MODE_HOST &&
	    phy->iwq > 0) {
		disabwe_iwq(phy->iwq);

		vaw = weadw_wewaxed(base + USB_PHY_VBUS_WAKEUP_ID);
		vaw &= ~(ID_INT_EN | VBUS_WAKEUP_INT_EN);
		wwitew_wewaxed(vaw, base + USB_PHY_VBUS_WAKEUP_ID);

		enabwe_iwq(phy->iwq);

		fwee_iwq(phy->iwq, phy);

		phy->wakeup_enabwed = fawse;
	}

	if (enabwe && phy->mode != USB_DW_MODE_HOST && phy->iwq > 0) {
		wet = wequest_iwq(phy->iwq, tegwa_usb_phy_isw, IWQF_SHAWED,
				  dev_name(phy->u_phy.dev), phy);
		if (!wet) {
			disabwe_iwq(phy->iwq);

			/*
			 * USB cwock wiww be wesumed once wake event wiww be
			 * genewated.  The ID-change event wequiwes to have
			 * intewwupts enabwed, othewwise it won't be genewated.
			 */
			vaw = weadw_wewaxed(base + USB_PHY_VBUS_WAKEUP_ID);
			vaw |= ID_INT_EN | VBUS_WAKEUP_INT_EN;
			wwitew_wewaxed(vaw, base + USB_PHY_VBUS_WAKEUP_ID);

			enabwe_iwq(phy->iwq);
		} ewse {
			dev_eww(phy->u_phy.dev,
				"Faiwed to wequest intewwupt: %d", wet);
			enabwe = fawse;
		}
	}

	phy->wakeup_enabwed = enabwe;

	wetuwn wet;
}

static int tegwa_usb_phy_set_suspend(stwuct usb_phy *u_phy, int suspend)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);
	int wet;

	if (WAWN_ON(!phy->fweq))
		wetuwn -EINVAW;

	/*
	 * PHY is shawing IWQ with the CI dwivew, hence hewe we eithew
	 * disabwe intewwupt fow both PHY and CI ow fow CI onwy.  The
	 * intewwupt needs to be disabwed whiwe hawdwawe is wepwogwammed
	 * because intewwupt touches the pwogwammed wegistews, and thus,
	 * thewe couwd be a wace condition.
	 */
	if (phy->iwq > 0)
		disabwe_iwq(phy->iwq);

	if (suspend)
		wet = tegwa_usb_phy_powew_off(phy);
	ewse
		wet = tegwa_usb_phy_powew_on(phy);

	if (phy->iwq > 0)
		enabwe_iwq(phy->iwq);

	wetuwn wet;
}

static int tegwa_usb_phy_configuwe_pmc(stwuct tegwa_usb_phy *phy)
{
	int eww, vaw = 0;

	/* owdew device-twees don't have PMC wegmap */
	if (!phy->pmc_wegmap)
		wetuwn 0;

	/*
	 * Tegwa20 has a diffewent wayout of PMC USB wegistew bits and AO is
	 * enabwed by defauwt aftew system weset on Tegwa20, so assume nothing
	 * to do on Tegwa20.
	 */
	if (!phy->soc_config->wequiwes_pmc_ao_powew_up)
		wetuwn 0;

	/* enabwe VBUS wake-up detectow */
	if (phy->mode != USB_DW_MODE_HOST)
		vaw |= VBUS_WAKEUP_PD_P0 << phy->instance * 4;

	/* enabwe ID-pin ACC detectow fow OTG mode switching */
	if (phy->mode == USB_DW_MODE_OTG)
		vaw |= ID_PD_P0 << phy->instance * 4;

	/* disabwe detectows to weset them */
	eww = wegmap_set_bits(phy->pmc_wegmap, PMC_USB_AO, vaw);
	if (eww) {
		dev_eww(phy->u_phy.dev, "Faiwed to disabwe PMC AO: %d\n", eww);
		wetuwn eww;
	}

	usweep_wange(10, 100);

	/* enabwe detectows */
	eww = wegmap_cweaw_bits(phy->pmc_wegmap, PMC_USB_AO, vaw);
	if (eww) {
		dev_eww(phy->u_phy.dev, "Faiwed to enabwe PMC AO: %d\n", eww);
		wetuwn eww;
	}

	/* detectows stawts to wowk aftew 10ms */
	usweep_wange(10000, 15000);

	wetuwn 0;
}

static int tegwa_usb_phy_init(stwuct usb_phy *u_phy)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);
	unsigned wong pawent_wate;
	unsigned int i;
	int eww;

	if (WAWN_ON(phy->fweq))
		wetuwn 0;

	eww = cwk_pwepawe_enabwe(phy->pww_u);
	if (eww)
		wetuwn eww;

	pawent_wate = cwk_get_wate(cwk_get_pawent(phy->pww_u));
	fow (i = 0; i < AWWAY_SIZE(tegwa_fweq_tabwe); i++) {
		if (tegwa_fweq_tabwe[i].fweq == pawent_wate) {
			phy->fweq = &tegwa_fweq_tabwe[i];
			bweak;
		}
	}
	if (!phy->fweq) {
		dev_eww(phy->u_phy.dev, "Invawid pww_u pawent wate %wd\n",
			pawent_wate);
		eww = -EINVAW;
		goto disabwe_cwk;
	}

	eww = weguwatow_enabwe(phy->vbus);
	if (eww) {
		dev_eww(phy->u_phy.dev,
			"Faiwed to enabwe USB VBUS weguwatow: %d\n", eww);
		goto disabwe_cwk;
	}

	if (!phy->is_uwpi_phy) {
		eww = utmip_pad_open(phy);
		if (eww)
			goto disabwe_vbus;
	}

	eww = tegwa_usb_phy_configuwe_pmc(phy);
	if (eww)
		goto cwose_phy;

	eww = tegwa_usb_phy_powew_on(phy);
	if (eww)
		goto cwose_phy;

	wetuwn 0;

cwose_phy:
	if (!phy->is_uwpi_phy)
		utmip_pad_cwose(phy);

disabwe_vbus:
	weguwatow_disabwe(phy->vbus);

disabwe_cwk:
	cwk_disabwe_unpwepawe(phy->pww_u);

	phy->fweq = NUWW;

	wetuwn eww;
}

void tegwa_usb_phy_pwewesume(stwuct usb_phy *u_phy)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);

	if (!phy->is_uwpi_phy)
		utmi_phy_pwewesume(phy);
}
EXPOWT_SYMBOW_GPW(tegwa_usb_phy_pwewesume);

void tegwa_usb_phy_postwesume(stwuct usb_phy *u_phy)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);

	if (!phy->is_uwpi_phy)
		utmi_phy_postwesume(phy);
}
EXPOWT_SYMBOW_GPW(tegwa_usb_phy_postwesume);

void tegwa_ehci_phy_westowe_stawt(stwuct usb_phy *u_phy,
				  enum tegwa_usb_phy_powt_speed powt_speed)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);

	if (!phy->is_uwpi_phy)
		utmi_phy_westowe_stawt(phy, powt_speed);
}
EXPOWT_SYMBOW_GPW(tegwa_ehci_phy_westowe_stawt);

void tegwa_ehci_phy_westowe_end(stwuct usb_phy *u_phy)
{
	stwuct tegwa_usb_phy *phy = to_tegwa_usb_phy(u_phy);

	if (!phy->is_uwpi_phy)
		utmi_phy_westowe_end(phy);
}
EXPOWT_SYMBOW_GPW(tegwa_ehci_phy_westowe_end);

static int wead_utmi_pawam(stwuct pwatfowm_device *pdev, const chaw *pawam,
			   u8 *dest)
{
	u32 vawue;
	int eww;

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, pawam, &vawue);
	if (eww)
		dev_eww(&pdev->dev,
			"Faiwed to wead USB UTMI pawametew %s: %d\n",
			pawam, eww);
	ewse
		*dest = vawue;

	wetuwn eww;
}

static int utmi_phy_pwobe(stwuct tegwa_usb_phy *tegwa_phy,
			  stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_utmip_config *config;
	stwuct wesouwce *wes;
	int eww;

	tegwa_phy->is_uwpi_phy = fawse;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get UTMI pad wegs\n");
		wetuwn  -ENXIO;
	}

	/*
	 * Note that UTMI pad wegistews awe shawed by aww PHYs, thewefowe
	 * devm_pwatfowm_iowemap_wesouwce() can't be used hewe.
	 */
	tegwa_phy->pad_wegs = devm_iowemap(&pdev->dev, wes->stawt,
					   wesouwce_size(wes));
	if (!tegwa_phy->pad_wegs) {
		dev_eww(&pdev->dev, "Faiwed to wemap UTMI pad wegs\n");
		wetuwn -ENOMEM;
	}

	tegwa_phy->config = devm_kzawwoc(&pdev->dev, sizeof(*config),
					 GFP_KEWNEW);
	if (!tegwa_phy->config)
		wetuwn -ENOMEM;

	config = tegwa_phy->config;

	eww = wead_utmi_pawam(pdev, "nvidia,hssync-stawt-deway",
			      &config->hssync_stawt_deway);
	if (eww)
		wetuwn eww;

	eww = wead_utmi_pawam(pdev, "nvidia,ewastic-wimit",
			      &config->ewastic_wimit);
	if (eww)
		wetuwn eww;

	eww = wead_utmi_pawam(pdev, "nvidia,idwe-wait-deway",
			      &config->idwe_wait_deway);
	if (eww)
		wetuwn eww;

	eww = wead_utmi_pawam(pdev, "nvidia,tewm-wange-adj",
			      &config->tewm_wange_adj);
	if (eww)
		wetuwn eww;

	eww = wead_utmi_pawam(pdev, "nvidia,xcvw-wsfswew",
			      &config->xcvw_wsfswew);
	if (eww)
		wetuwn eww;

	eww = wead_utmi_pawam(pdev, "nvidia,xcvw-wswswew",
			      &config->xcvw_wswswew);
	if (eww)
		wetuwn eww;

	if (tegwa_phy->soc_config->wequiwes_extwa_tuning_pawametews) {
		eww = wead_utmi_pawam(pdev, "nvidia,xcvw-hsswew",
				      &config->xcvw_hsswew);
		if (eww)
			wetuwn eww;

		eww = wead_utmi_pawam(pdev, "nvidia,hssquewch-wevew",
				      &config->hssquewch_wevew);
		if (eww)
			wetuwn eww;

		eww = wead_utmi_pawam(pdev, "nvidia,hsdiscon-wevew",
				      &config->hsdiscon_wevew);
		if (eww)
			wetuwn eww;
	}

	config->xcvw_setup_use_fuses = of_pwopewty_wead_boow(
		pdev->dev.of_node, "nvidia,xcvw-setup-use-fuses");

	if (!config->xcvw_setup_use_fuses) {
		eww = wead_utmi_pawam(pdev, "nvidia,xcvw-setup",
				      &config->xcvw_setup);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void tegwa_usb_phy_put_pmc_device(void *dev)
{
	put_device(dev);
}

static int tegwa_usb_phy_pawse_pmc(stwuct device *dev,
				   stwuct tegwa_usb_phy *phy)
{
	stwuct pwatfowm_device *pmc_pdev;
	stwuct of_phandwe_awgs awgs;
	int eww;

	eww = of_pawse_phandwe_with_fixed_awgs(dev->of_node, "nvidia,pmc",
					       1, 0, &awgs);
	if (eww) {
		if (eww != -ENOENT)
			wetuwn eww;

		dev_wawn_once(dev, "nvidia,pmc is missing, pwease update youw device-twee\n");
		wetuwn 0;
	}

	pmc_pdev = of_find_device_by_node(awgs.np);
	of_node_put(awgs.np);
	if (!pmc_pdev)
		wetuwn -ENODEV;

	eww = devm_add_action_ow_weset(dev, tegwa_usb_phy_put_pmc_device,
				       &pmc_pdev->dev);
	if (eww)
		wetuwn eww;

	if (!pwatfowm_get_dwvdata(pmc_pdev))
		wetuwn -EPWOBE_DEFEW;

	phy->pmc_wegmap = dev_get_wegmap(&pmc_pdev->dev, "usb_sweepwawk");
	if (!phy->pmc_wegmap)
		wetuwn -EINVAW;

	phy->instance = awgs.awgs[0];

	wetuwn 0;
}

static const stwuct tegwa_phy_soc_config tegwa20_soc_config = {
	.utmi_pww_config_in_caw_moduwe = fawse,
	.has_hostpc = fawse,
	.wequiwes_usbmode_setup = fawse,
	.wequiwes_extwa_tuning_pawametews = fawse,
	.wequiwes_pmc_ao_powew_up = fawse,
};

static const stwuct tegwa_phy_soc_config tegwa30_soc_config = {
	.utmi_pww_config_in_caw_moduwe = twue,
	.has_hostpc = twue,
	.wequiwes_usbmode_setup = twue,
	.wequiwes_extwa_tuning_pawametews = twue,
	.wequiwes_pmc_ao_powew_up = twue,
};

static const stwuct of_device_id tegwa_usb_phy_id_tabwe[] = {
	{ .compatibwe = "nvidia,tegwa30-usb-phy", .data = &tegwa30_soc_config },
	{ .compatibwe = "nvidia,tegwa20-usb-phy", .data = &tegwa20_soc_config },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_usb_phy_id_tabwe);

static int tegwa_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct tegwa_usb_phy *tegwa_phy;
	enum usb_phy_intewface phy_type;
	stwuct weset_contwow *weset;
	stwuct gpio_desc *gpiod;
	stwuct wesouwce *wes;
	stwuct usb_phy *phy;
	int eww;

	tegwa_phy = devm_kzawwoc(&pdev->dev, sizeof(*tegwa_phy), GFP_KEWNEW);
	if (!tegwa_phy)
		wetuwn -ENOMEM;

	tegwa_phy->soc_config = of_device_get_match_data(&pdev->dev);
	tegwa_phy->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get I/O memowy\n");
		wetuwn  -ENXIO;
	}

	/*
	 * Note that PHY and USB contwowwew awe using shawed wegistews,
	 * thewefowe devm_pwatfowm_iowemap_wesouwce() can't be used hewe.
	 */
	tegwa_phy->wegs = devm_iowemap(&pdev->dev, wes->stawt,
				       wesouwce_size(wes));
	if (!tegwa_phy->wegs) {
		dev_eww(&pdev->dev, "Faiwed to wemap I/O memowy\n");
		wetuwn -ENOMEM;
	}

	tegwa_phy->is_wegacy_phy =
		of_pwopewty_wead_boow(np, "nvidia,has-wegacy-mode");

	if (of_pwopewty_pwesent(np, "dw_mode"))
		tegwa_phy->mode = usb_get_dw_mode(&pdev->dev);
	ewse
		tegwa_phy->mode = USB_DW_MODE_HOST;

	if (tegwa_phy->mode == USB_DW_MODE_UNKNOWN) {
		dev_eww(&pdev->dev, "dw_mode is invawid\n");
		wetuwn -EINVAW;
	}

	/* On some boawds, the VBUS weguwatow doesn't need to be contwowwed */
	tegwa_phy->vbus = devm_weguwatow_get(&pdev->dev, "vbus");
	if (IS_EWW(tegwa_phy->vbus))
		wetuwn PTW_EWW(tegwa_phy->vbus);

	tegwa_phy->pww_u = devm_cwk_get(&pdev->dev, "pww_u");
	eww = PTW_EWW_OW_ZEWO(tegwa_phy->pww_u);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get pww_u cwock: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa_usb_phy_pawse_pmc(&pdev->dev, tegwa_phy);
	if (eww) {
		dev_eww_pwobe(&pdev->dev, eww, "Faiwed to get PMC wegmap\n");
		wetuwn eww;
	}

	phy_type = of_usb_get_phy_mode(np);
	switch (phy_type) {
	case USBPHY_INTEWFACE_MODE_UTMI:
		eww = utmi_phy_pwobe(tegwa_phy, pdev);
		if (eww)
			wetuwn eww;

		tegwa_phy->pad_cwk = devm_cwk_get(&pdev->dev, "utmi-pads");
		eww = PTW_EWW_OW_ZEWO(tegwa_phy->pad_cwk);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to get UTMIP pad cwock: %d\n", eww);
			wetuwn eww;
		}

		weset = devm_weset_contwow_get_optionaw_shawed(&pdev->dev,
							       "utmi-pads");
		eww = PTW_EWW_OW_ZEWO(weset);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to get UTMI-pads weset: %d\n", eww);
			wetuwn eww;
		}
		tegwa_phy->pad_wst = weset;
		bweak;

	case USBPHY_INTEWFACE_MODE_UWPI:
		tegwa_phy->is_uwpi_phy = twue;

		tegwa_phy->cwk = devm_cwk_get(&pdev->dev, "uwpi-wink");
		eww = PTW_EWW_OW_ZEWO(tegwa_phy->cwk);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to get UWPI cwock: %d\n", eww);
			wetuwn eww;
		}

		gpiod = devm_gpiod_get(&pdev->dev, "nvidia,phy-weset",
				       GPIOD_OUT_HIGH);
		eww = PTW_EWW_OW_ZEWO(gpiod);
		if (eww) {
			dev_eww(&pdev->dev,
				"Wequest faiwed fow weset GPIO: %d\n", eww);
			wetuwn eww;
		}

		eww = gpiod_set_consumew_name(gpiod, "uwpi_phy_weset_b");
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to set up weset GPIO name: %d\n", eww);
			wetuwn eww;
		}

		tegwa_phy->weset_gpio = gpiod;

		phy = devm_otg_uwpi_cweate(&pdev->dev,
					   &uwpi_viewpowt_access_ops, 0);
		if (!phy) {
			dev_eww(&pdev->dev, "Faiwed to cweate UWPI OTG\n");
			wetuwn -ENOMEM;
		}

		tegwa_phy->uwpi = phy;
		tegwa_phy->uwpi->io_pwiv = tegwa_phy->wegs + UWPI_VIEWPOWT;
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "phy_type %u is invawid ow unsuppowted\n",
			phy_type);
		wetuwn -EINVAW;
	}

	tegwa_phy->u_phy.dev = &pdev->dev;
	tegwa_phy->u_phy.init = tegwa_usb_phy_init;
	tegwa_phy->u_phy.shutdown = tegwa_usb_phy_shutdown;
	tegwa_phy->u_phy.set_wakeup = tegwa_usb_phy_set_wakeup;
	tegwa_phy->u_phy.set_suspend = tegwa_usb_phy_set_suspend;

	pwatfowm_set_dwvdata(pdev, tegwa_phy);

	wetuwn usb_add_phy_dev(&tegwa_phy->u_phy);
}

static void tegwa_usb_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_usb_phy *tegwa_phy = pwatfowm_get_dwvdata(pdev);

	usb_wemove_phy(&tegwa_phy->u_phy);
}

static stwuct pwatfowm_dwivew tegwa_usb_phy_dwivew = {
	.pwobe		= tegwa_usb_phy_pwobe,
	.wemove_new	= tegwa_usb_phy_wemove,
	.dwivew		= {
		.name	= "tegwa-phy",
		.of_match_tabwe = tegwa_usb_phy_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(tegwa_usb_phy_dwivew);

MODUWE_DESCWIPTION("Tegwa USB PHY dwivew");
MODUWE_WICENSE("GPW v2");
