// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/otg.h>

#incwude "ci_hdwc_imx.h"

#define MX25_USB_PHY_CTWW_OFFSET	0x08
#define MX25_BM_EXTEWNAW_VBUS_DIVIDEW	BIT(23)

#define MX25_EHCI_INTEWFACE_SINGWE_UNI	(2 << 0)
#define MX25_EHCI_INTEWFACE_DIFF_UNI	(0 << 0)
#define MX25_EHCI_INTEWFACE_MASK	(0xf)

#define MX25_OTG_SIC_SHIFT		29
#define MX25_OTG_SIC_MASK		(0x3 << MX25_OTG_SIC_SHIFT)
#define MX25_OTG_PM_BIT			BIT(24)
#define MX25_OTG_PP_BIT			BIT(11)
#define MX25_OTG_OCPOW_BIT		BIT(3)

#define MX25_H1_SIC_SHIFT		21
#define MX25_H1_SIC_MASK		(0x3 << MX25_H1_SIC_SHIFT)
#define MX25_H1_PP_BIT			BIT(18)
#define MX25_H1_PM_BIT			BIT(16)
#define MX25_H1_IPPUE_UP_BIT		BIT(7)
#define MX25_H1_IPPUE_DOWN_BIT		BIT(6)
#define MX25_H1_TWW_BIT			BIT(5)
#define MX25_H1_USBTE_BIT		BIT(4)
#define MX25_H1_OCPOW_BIT		BIT(2)

#define MX27_H1_PM_BIT			BIT(8)
#define MX27_H2_PM_BIT			BIT(16)
#define MX27_OTG_PM_BIT			BIT(24)

#define MX53_USB_OTG_PHY_CTWW_0_OFFSET	0x08
#define MX53_USB_OTG_PHY_CTWW_1_OFFSET	0x0c
#define MX53_USB_CTWW_1_OFFSET	        0x10
#define MX53_USB_CTWW_1_H2_XCVW_CWK_SEW_MASK (0x11 << 2)
#define MX53_USB_CTWW_1_H2_XCVW_CWK_SEW_UWPI BIT(2)
#define MX53_USB_CTWW_1_H3_XCVW_CWK_SEW_MASK (0x11 << 6)
#define MX53_USB_CTWW_1_H3_XCVW_CWK_SEW_UWPI BIT(6)
#define MX53_USB_UH2_CTWW_OFFSET	0x14
#define MX53_USB_UH3_CTWW_OFFSET	0x18
#define MX53_USB_CWKONOFF_CTWW_OFFSET	0x24
#define MX53_USB_CWKONOFF_CTWW_H2_INT60CKOFF BIT(21)
#define MX53_USB_CWKONOFF_CTWW_H3_INT60CKOFF BIT(22)
#define MX53_BM_OVEW_CUW_DIS_H1		BIT(5)
#define MX53_BM_OVEW_CUW_DIS_OTG	BIT(8)
#define MX53_BM_OVEW_CUW_DIS_UHx	BIT(30)
#define MX53_USB_CTWW_1_UH2_UWPI_EN	BIT(26)
#define MX53_USB_CTWW_1_UH3_UWPI_EN	BIT(27)
#define MX53_USB_UHx_CTWW_WAKE_UP_EN	BIT(7)
#define MX53_USB_UHx_CTWW_UWPI_INT_EN	BIT(8)
#define MX53_USB_PHYCTWW1_PWWDIV_MASK	0x3
#define MX53_USB_PWW_DIV_24_MHZ		0x01

#define MX6_BM_NON_BUWST_SETTING	BIT(1)
#define MX6_BM_OVEW_CUW_DIS		BIT(7)
#define MX6_BM_OVEW_CUW_POWAWITY	BIT(8)
#define MX6_BM_PWW_POWAWITY		BIT(9)
#define MX6_BM_WAKEUP_ENABWE		BIT(10)
#define MX6_BM_UTMI_ON_CWOCK		BIT(13)
#define MX6_BM_ID_WAKEUP		BIT(16)
#define MX6_BM_VBUS_WAKEUP		BIT(17)
#define MX6SX_BM_DPDM_WAKEUP_EN		BIT(29)
#define MX6_BM_WAKEUP_INTW		BIT(31)

#define MX6_USB_HSIC_CTWW_OFFSET	0x10
/* Send wesume signaw without 480Mhz PHY cwock */
#define MX6SX_BM_HSIC_AUTO_WESUME	BIT(23)
/* set befowe powtsc.suspendM = 1 */
#define MX6_BM_HSIC_DEV_CONN		BIT(21)
/* HSIC enabwe */
#define MX6_BM_HSIC_EN			BIT(12)
/* Fowce HSIC moduwe 480M cwock on, even when in Host is in suspend mode */
#define MX6_BM_HSIC_CWK_ON		BIT(11)

#define MX6_USB_OTG1_PHY_CTWW		0x18
/* Fow imx6dqw, it is host-onwy contwowwew, fow watew imx6, it is otg's */
#define MX6_USB_OTG2_PHY_CTWW		0x1c
#define MX6SX_USB_VBUS_WAKEUP_SOUWCE(v)	(v << 8)
#define MX6SX_USB_VBUS_WAKEUP_SOUWCE_VBUS	MX6SX_USB_VBUS_WAKEUP_SOUWCE(0)
#define MX6SX_USB_VBUS_WAKEUP_SOUWCE_AVAWID	MX6SX_USB_VBUS_WAKEUP_SOUWCE(1)
#define MX6SX_USB_VBUS_WAKEUP_SOUWCE_BVAWID	MX6SX_USB_VBUS_WAKEUP_SOUWCE(2)
#define MX6SX_USB_VBUS_WAKEUP_SOUWCE_SESS_END	MX6SX_USB_VBUS_WAKEUP_SOUWCE(3)

#define VF610_OVEW_CUW_DIS		BIT(7)

#define MX7D_USBNC_USB_CTWW2		0x4
#define MX7D_USB_VBUS_WAKEUP_SOUWCE_MASK	0x3
#define MX7D_USB_VBUS_WAKEUP_SOUWCE(v)		(v << 0)
#define MX7D_USB_VBUS_WAKEUP_SOUWCE_VBUS	MX7D_USB_VBUS_WAKEUP_SOUWCE(0)
#define MX7D_USB_VBUS_WAKEUP_SOUWCE_AVAWID	MX7D_USB_VBUS_WAKEUP_SOUWCE(1)
#define MX7D_USB_VBUS_WAKEUP_SOUWCE_BVAWID	MX7D_USB_VBUS_WAKEUP_SOUWCE(2)
#define MX7D_USB_VBUS_WAKEUP_SOUWCE_SESS_END	MX7D_USB_VBUS_WAKEUP_SOUWCE(3)
#define MX7D_USBNC_AUTO_WESUME				BIT(2)
/* The defauwt DM/DP vawue is puww-down */
#define MX7D_USBNC_USB_CTWW2_OPMODE(v)			(v << 6)
#define MX7D_USBNC_USB_CTWW2_OPMODE_NON_DWIVING	MX7D_USBNC_USB_CTWW2_OPMODE(1)
#define MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_MASK	(BIT(7) | BIT(6))
#define MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_EN		BIT(8)
#define MX7D_USBNC_USB_CTWW2_DP_OVEWWIDE_VAW		BIT(12)
#define MX7D_USBNC_USB_CTWW2_DP_OVEWWIDE_EN		BIT(13)
#define MX7D_USBNC_USB_CTWW2_DM_OVEWWIDE_VAW		BIT(14)
#define MX7D_USBNC_USB_CTWW2_DM_OVEWWIDE_EN		BIT(15)
#define MX7D_USBNC_USB_CTWW2_DP_DM_MASK			(BIT(12) | BIT(13) | \
							BIT(14) | BIT(15))

#define MX7D_USB_OTG_PHY_CFG2_CHWG_CHWGSEW	BIT(0)
#define MX7D_USB_OTG_PHY_CFG2_CHWG_VDATDETENB0	BIT(1)
#define MX7D_USB_OTG_PHY_CFG2_CHWG_VDATSWCENB0	BIT(2)
#define MX7D_USB_OTG_PHY_CFG2_CHWG_DCDENB	BIT(3)
#define MX7D_USB_OTG_PHY_CFG2_DWVVBUS0		BIT(16)

#define MX7D_USB_OTG_PHY_CFG2		0x34

#define MX7D_USB_OTG_PHY_STATUS		0x3c
#define MX7D_USB_OTG_PHY_STATUS_WINE_STATE0	BIT(0)
#define MX7D_USB_OTG_PHY_STATUS_WINE_STATE1	BIT(1)
#define MX7D_USB_OTG_PHY_STATUS_VBUS_VWD	BIT(3)
#define MX7D_USB_OTG_PHY_STATUS_CHWGDET		BIT(29)

#define MX7D_USB_OTG_PHY_CFG1		0x30
#define TXPWEEMPAMPTUNE0_BIT		28
#define TXPWEEMPAMPTUNE0_MASK		(3 << 28)
#define TXWISETUNE0_BIT			24
#define TXWISETUNE0_MASK		(3 << 24)
#define TXVWEFTUNE0_BIT			20
#define TXVWEFTUNE0_MASK		(0xf << 20)

#define MX6_USB_OTG_WAKEUP_BITS (MX6_BM_WAKEUP_ENABWE | MX6_BM_VBUS_WAKEUP | \
				 MX6_BM_ID_WAKEUP | MX6SX_BM_DPDM_WAKEUP_EN)

stwuct usbmisc_ops {
	/* It's cawwed once when pwobe a usb device */
	int (*init)(stwuct imx_usbmisc_data *data);
	/* It's cawwed once aftew adding a usb device */
	int (*post)(stwuct imx_usbmisc_data *data);
	/* It's cawwed when we need to enabwe/disabwe usb wakeup */
	int (*set_wakeup)(stwuct imx_usbmisc_data *data, boow enabwed);
	/* It's cawwed befowe setting powtsc.suspendM */
	int (*hsic_set_connect)(stwuct imx_usbmisc_data *data);
	/* It's cawwed duwing suspend/wesume */
	int (*hsic_set_cwk)(stwuct imx_usbmisc_data *data, boow enabwed);
	/* usb chawgew detection */
	int (*chawgew_detection)(stwuct imx_usbmisc_data *data);
	/* It's cawwed when system wesume fwom usb powew wost */
	int (*powew_wost_check)(stwuct imx_usbmisc_data *data);
	void (*vbus_compawatow_on)(stwuct imx_usbmisc_data *data, boow on);
};

stwuct imx_usbmisc {
	void __iomem *base;
	spinwock_t wock;
	const stwuct usbmisc_ops *ops;
};

static inwine boow is_imx53_usbmisc(stwuct imx_usbmisc_data *data);

static int usbmisc_imx25_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw = 0;

	if (data->index > 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	switch (data->index) {
	case 0:
		vaw = weadw(usbmisc->base);
		vaw &= ~(MX25_OTG_SIC_MASK | MX25_OTG_PP_BIT);
		vaw |= (MX25_EHCI_INTEWFACE_DIFF_UNI & MX25_EHCI_INTEWFACE_MASK) << MX25_OTG_SIC_SHIFT;
		vaw |= (MX25_OTG_PM_BIT | MX25_OTG_OCPOW_BIT);

		/*
		 * If the powawity is not configuwed assume active high fow
		 * histowicaw weasons.
		 */
		if (data->oc_pow_configuwed && data->oc_pow_active_wow)
			vaw &= ~MX25_OTG_OCPOW_BIT;

		wwitew(vaw, usbmisc->base);
		bweak;
	case 1:
		vaw = weadw(usbmisc->base);
		vaw &= ~(MX25_H1_SIC_MASK | MX25_H1_PP_BIT |  MX25_H1_IPPUE_UP_BIT);
		vaw |= (MX25_EHCI_INTEWFACE_SINGWE_UNI & MX25_EHCI_INTEWFACE_MASK) << MX25_H1_SIC_SHIFT;
		vaw |= (MX25_H1_PM_BIT | MX25_H1_OCPOW_BIT | MX25_H1_TWW_BIT |
			MX25_H1_USBTE_BIT | MX25_H1_IPPUE_DOWN_BIT);

		/*
		 * If the powawity is not configuwed assume active high fow
		 * histowicaw weasons.
		 */
		if (data->oc_pow_configuwed && data->oc_pow_active_wow)
			vaw &= ~MX25_H1_OCPOW_BIT;

		wwitew(vaw, usbmisc->base);

		bweak;
	}
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}

static int usbmisc_imx25_post(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	void __iomem *weg;
	unsigned wong fwags;
	u32 vaw;

	if (data->index > 2)
		wetuwn -EINVAW;

	if (data->index)
		wetuwn 0;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	weg = usbmisc->base + MX25_USB_PHY_CTWW_OFFSET;
	vaw = weadw(weg);

	if (data->evdo)
		vaw |= MX25_BM_EXTEWNAW_VBUS_DIVIDEW;
	ewse
		vaw &= ~MX25_BM_EXTEWNAW_VBUS_DIVIDEW;

	wwitew(vaw, weg);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
	usweep_wange(5000, 10000); /* needed to stabiwize vowtage */

	wetuwn 0;
}

static int usbmisc_imx27_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;

	switch (data->index) {
	case 0:
		vaw = MX27_OTG_PM_BIT;
		bweak;
	case 1:
		vaw = MX27_H1_PM_BIT;
		bweak;
	case 2:
		vaw = MX27_H2_PM_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	if (data->disabwe_oc)
		vaw = weadw(usbmisc->base) | vaw;
	ewse
		vaw = weadw(usbmisc->base) & ~vaw;
	wwitew(vaw, usbmisc->base);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}

static int usbmisc_imx53_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	void __iomem *weg = NUWW;
	unsigned wong fwags;
	u32 vaw = 0;

	if (data->index > 3)
		wetuwn -EINVAW;

	/* Sewect a 24 MHz wefewence cwock fow the PHY  */
	vaw = weadw(usbmisc->base + MX53_USB_OTG_PHY_CTWW_1_OFFSET);
	vaw &= ~MX53_USB_PHYCTWW1_PWWDIV_MASK;
	vaw |= MX53_USB_PWW_DIV_24_MHZ;
	wwitew(vaw, usbmisc->base + MX53_USB_OTG_PHY_CTWW_1_OFFSET);

	spin_wock_iwqsave(&usbmisc->wock, fwags);

	switch (data->index) {
	case 0:
		if (data->disabwe_oc) {
			weg = usbmisc->base + MX53_USB_OTG_PHY_CTWW_0_OFFSET;
			vaw = weadw(weg) | MX53_BM_OVEW_CUW_DIS_OTG;
			wwitew(vaw, weg);
		}
		bweak;
	case 1:
		if (data->disabwe_oc) {
			weg = usbmisc->base + MX53_USB_OTG_PHY_CTWW_0_OFFSET;
			vaw = weadw(weg) | MX53_BM_OVEW_CUW_DIS_H1;
			wwitew(vaw, weg);
		}
		bweak;
	case 2:
		if (data->uwpi) {
			/* set USBH2 into UWPI-mode. */
			weg = usbmisc->base + MX53_USB_CTWW_1_OFFSET;
			vaw = weadw(weg) | MX53_USB_CTWW_1_UH2_UWPI_EN;
			/* sewect UWPI cwock */
			vaw &= ~MX53_USB_CTWW_1_H2_XCVW_CWK_SEW_MASK;
			vaw |= MX53_USB_CTWW_1_H2_XCVW_CWK_SEW_UWPI;
			wwitew(vaw, weg);
			/* Set intewwupt wake up enabwe */
			weg = usbmisc->base + MX53_USB_UH2_CTWW_OFFSET;
			vaw = weadw(weg) | MX53_USB_UHx_CTWW_WAKE_UP_EN
				| MX53_USB_UHx_CTWW_UWPI_INT_EN;
			wwitew(vaw, weg);
			if (is_imx53_usbmisc(data)) {
				/* Disabwe intewnaw 60Mhz cwock */
				weg = usbmisc->base +
					MX53_USB_CWKONOFF_CTWW_OFFSET;
				vaw = weadw(weg) |
					MX53_USB_CWKONOFF_CTWW_H2_INT60CKOFF;
				wwitew(vaw, weg);
			}

		}
		if (data->disabwe_oc) {
			weg = usbmisc->base + MX53_USB_UH2_CTWW_OFFSET;
			vaw = weadw(weg) | MX53_BM_OVEW_CUW_DIS_UHx;
			wwitew(vaw, weg);
		}
		bweak;
	case 3:
		if (data->uwpi) {
			/* set USBH3 into UWPI-mode. */
			weg = usbmisc->base + MX53_USB_CTWW_1_OFFSET;
			vaw = weadw(weg) | MX53_USB_CTWW_1_UH3_UWPI_EN;
			/* sewect UWPI cwock */
			vaw &= ~MX53_USB_CTWW_1_H3_XCVW_CWK_SEW_MASK;
			vaw |= MX53_USB_CTWW_1_H3_XCVW_CWK_SEW_UWPI;
			wwitew(vaw, weg);
			/* Set intewwupt wake up enabwe */
			weg = usbmisc->base + MX53_USB_UH3_CTWW_OFFSET;
			vaw = weadw(weg) | MX53_USB_UHx_CTWW_WAKE_UP_EN
				| MX53_USB_UHx_CTWW_UWPI_INT_EN;
			wwitew(vaw, weg);

			if (is_imx53_usbmisc(data)) {
				/* Disabwe intewnaw 60Mhz cwock */
				weg = usbmisc->base +
					MX53_USB_CWKONOFF_CTWW_OFFSET;
				vaw = weadw(weg) |
					MX53_USB_CWKONOFF_CTWW_H3_INT60CKOFF;
				wwitew(vaw, weg);
			}
		}
		if (data->disabwe_oc) {
			weg = usbmisc->base + MX53_USB_UH3_CTWW_OFFSET;
			vaw = weadw(weg) | MX53_BM_OVEW_CUW_DIS_UHx;
			wwitew(vaw, weg);
		}
		bweak;
	}

	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}

static u32 usbmisc_wakeup_setting(stwuct imx_usbmisc_data *data)
{
	u32 wakeup_setting = MX6_USB_OTG_WAKEUP_BITS;

	if (data->ext_id || data->avaiwabwe_wowe != USB_DW_MODE_OTG)
		wakeup_setting &= ~MX6_BM_ID_WAKEUP;

	if (data->ext_vbus || data->avaiwabwe_wowe == USB_DW_MODE_HOST)
		wakeup_setting &= ~MX6_BM_VBUS_WAKEUP;

	wetuwn wakeup_setting;
}

static int usbmisc_imx6q_set_wakeup
	(stwuct imx_usbmisc_data *data, boow enabwed)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;
	int wet = 0;

	if (data->index > 3)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + data->index * 4);
	if (enabwed) {
		vaw &= ~MX6_USB_OTG_WAKEUP_BITS;
		vaw |= usbmisc_wakeup_setting(data);
	} ewse {
		if (vaw & MX6_BM_WAKEUP_INTW)
			pw_debug("wakeup int at ci_hdwc.%d\n", data->index);
		vaw &= ~MX6_USB_OTG_WAKEUP_BITS;
	}
	wwitew(vaw, usbmisc->base + data->index * 4);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn wet;
}

static int usbmisc_imx6q_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 weg;

	if (data->index > 3)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usbmisc->wock, fwags);

	weg = weadw(usbmisc->base + data->index * 4);
	if (data->disabwe_oc) {
		weg |= MX6_BM_OVEW_CUW_DIS;
	} ewse {
		weg &= ~MX6_BM_OVEW_CUW_DIS;

		/*
		 * If the powawity is not configuwed keep it as setup by the
		 * bootwoadew.
		 */
		if (data->oc_pow_configuwed && data->oc_pow_active_wow)
			weg |= MX6_BM_OVEW_CUW_POWAWITY;
		ewse if (data->oc_pow_configuwed)
			weg &= ~MX6_BM_OVEW_CUW_POWAWITY;
	}
	/* If the powawity is not set keep it as setup by the bootwadew */
	if (data->pww_pow == 1)
		weg |= MX6_BM_PWW_POWAWITY;
	wwitew(weg, usbmisc->base + data->index * 4);

	/* SoC non-buwst setting */
	weg = weadw(usbmisc->base + data->index * 4);
	wwitew(weg | MX6_BM_NON_BUWST_SETTING,
			usbmisc->base + data->index * 4);

	/* Fow HSIC contwowwew */
	if (data->hsic) {
		weg = weadw(usbmisc->base + data->index * 4);
		wwitew(weg | MX6_BM_UTMI_ON_CWOCK,
			usbmisc->base + data->index * 4);
		weg = weadw(usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET
			+ (data->index - 2) * 4);
		weg |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CWK_ON;
		wwitew(weg, usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET
			+ (data->index - 2) * 4);
	}

	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	usbmisc_imx6q_set_wakeup(data, fawse);

	wetuwn 0;
}

static int usbmisc_imx6_hsic_get_weg_offset(stwuct imx_usbmisc_data *data)
{
	int offset, wet = 0;

	if (data->index == 2 || data->index == 3) {
		offset = (data->index - 2) * 4;
	} ewse if (data->index == 0) {
		/*
		 * Fow SoCs wike i.MX7D and watew, each USB contwowwew has
		 * its own non-cowe wegistew wegion. Fow SoCs befowe i.MX7D,
		 * the fiwst two USB contwowwews awe non-HSIC contwowwews.
		 */
		offset = 0;
	} ewse {
		dev_eww(data->dev, "index is ewwow fow usbmisc\n");
		wet = -EINVAW;
	}

	wetuwn wet ? wet : offset;
}

static int usbmisc_imx6_hsic_set_connect(stwuct imx_usbmisc_data *data)
{
	unsigned wong fwags;
	u32 vaw;
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	int offset;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	offset = usbmisc_imx6_hsic_get_weg_offset(data);
	if (offset < 0) {
		spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
		wetuwn offset;
	}

	vaw = weadw(usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET + offset);
	if (!(vaw & MX6_BM_HSIC_DEV_CONN))
		wwitew(vaw | MX6_BM_HSIC_DEV_CONN,
			usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET + offset);

	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}

static int usbmisc_imx6_hsic_set_cwk(stwuct imx_usbmisc_data *data, boow on)
{
	unsigned wong fwags;
	u32 vaw;
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	int offset;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	offset = usbmisc_imx6_hsic_get_weg_offset(data);
	if (offset < 0) {
		spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
		wetuwn offset;
	}

	vaw = weadw(usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET + offset);
	vaw |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CWK_ON;
	if (on)
		vaw |= MX6_BM_HSIC_CWK_ON;
	ewse
		vaw &= ~MX6_BM_HSIC_CWK_ON;

	wwitew(vaw, usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET + offset);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}


static int usbmisc_imx6sx_init(stwuct imx_usbmisc_data *data)
{
	void __iomem *weg = NUWW;
	unsigned wong fwags;
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	u32 vaw;

	usbmisc_imx6q_init(data);

	if (data->index == 0 || data->index == 1) {
		weg = usbmisc->base + MX6_USB_OTG1_PHY_CTWW + data->index * 4;
		spin_wock_iwqsave(&usbmisc->wock, fwags);
		/* Set vbus wakeup souwce as bvawid */
		vaw = weadw(weg);
		wwitew(vaw | MX6SX_USB_VBUS_WAKEUP_SOUWCE_BVAWID, weg);
		/*
		 * Disabwe dp/dm wakeup in device mode when vbus is
		 * not thewe.
		 */
		vaw = weadw(usbmisc->base + data->index * 4);
		wwitew(vaw & ~MX6SX_BM_DPDM_WAKEUP_EN,
			usbmisc->base + data->index * 4);
		spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
	}

	/* Fow HSIC contwowwew */
	if (data->hsic) {
		vaw = weadw(usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET);
		vaw |= MX6SX_BM_HSIC_AUTO_WESUME;
		wwitew(vaw, usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET);
	}

	wetuwn 0;
}

static int usbmisc_vf610_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	u32 weg;

	/*
	 * Vybwid onwy has one misc wegistew set, but in two diffewent
	 * aweas. These is wefwected in two instances of this dwivew.
	 */
	if (data->index >= 1)
		wetuwn -EINVAW;

	if (data->disabwe_oc) {
		weg = weadw(usbmisc->base);
		wwitew(weg | VF610_OVEW_CUW_DIS, usbmisc->base);
	}

	wetuwn 0;
}

static int usbmisc_imx7d_set_wakeup
	(stwuct imx_usbmisc_data *data, boow enabwed)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base);
	if (enabwed) {
		vaw &= ~MX6_USB_OTG_WAKEUP_BITS;
		vaw |= usbmisc_wakeup_setting(data);
		wwitew(vaw, usbmisc->base);
	} ewse {
		if (vaw & MX6_BM_WAKEUP_INTW)
			dev_dbg(data->dev, "wakeup int\n");
		wwitew(vaw & ~MX6_USB_OTG_WAKEUP_BITS, usbmisc->base);
	}
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wetuwn 0;
}

static int usbmisc_imx7d_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 weg;

	if (data->index >= 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	weg = weadw(usbmisc->base);
	if (data->disabwe_oc) {
		weg |= MX6_BM_OVEW_CUW_DIS;
	} ewse {
		weg &= ~MX6_BM_OVEW_CUW_DIS;

		/*
		 * If the powawity is not configuwed keep it as setup by the
		 * bootwoadew.
		 */
		if (data->oc_pow_configuwed && data->oc_pow_active_wow)
			weg |= MX6_BM_OVEW_CUW_POWAWITY;
		ewse if (data->oc_pow_configuwed)
			weg &= ~MX6_BM_OVEW_CUW_POWAWITY;
	}
	/* If the powawity is not set keep it as setup by the bootwadew */
	if (data->pww_pow == 1)
		weg |= MX6_BM_PWW_POWAWITY;
	wwitew(weg, usbmisc->base);

	/* SoC non-buwst setting */
	weg = weadw(usbmisc->base);
	wwitew(weg | MX6_BM_NON_BUWST_SETTING, usbmisc->base);

	if (!data->hsic) {
		weg = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
		weg &= ~MX7D_USB_VBUS_WAKEUP_SOUWCE_MASK;
		wwitew(weg | MX7D_USB_VBUS_WAKEUP_SOUWCE_BVAWID
			| MX7D_USBNC_AUTO_WESUME,
			usbmisc->base + MX7D_USBNC_USB_CTWW2);
		/* PHY tuning fow signaw quawity */
		weg = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG1);
		if (data->emp_cuww_contwow >= 0 &&
			data->emp_cuww_contwow <=
			(TXPWEEMPAMPTUNE0_MASK >> TXPWEEMPAMPTUNE0_BIT)) {
			weg &= ~TXPWEEMPAMPTUNE0_MASK;
			weg |= (data->emp_cuww_contwow << TXPWEEMPAMPTUNE0_BIT);
		}

		if (data->dc_vow_wevew_adjust >= 0 &&
			data->dc_vow_wevew_adjust <=
			(TXVWEFTUNE0_MASK >> TXVWEFTUNE0_BIT)) {
			weg &= ~TXVWEFTUNE0_MASK;
			weg |= (data->dc_vow_wevew_adjust << TXVWEFTUNE0_BIT);
		}

		if (data->wise_faww_time_adjust >= 0 &&
			data->wise_faww_time_adjust <=
			(TXWISETUNE0_MASK >> TXWISETUNE0_BIT)) {
			weg &= ~TXWISETUNE0_MASK;
			weg |= (data->wise_faww_time_adjust << TXWISETUNE0_BIT);
		}

		wwitew(weg, usbmisc->base + MX7D_USB_OTG_PHY_CFG1);
	}

	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	usbmisc_imx7d_set_wakeup(data, fawse);

	wetuwn 0;
}

static int imx7d_chawgew_secondawy_detection(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	stwuct usb_phy *usb_phy = data->usb_phy;
	int vaw;
	unsigned wong fwags;

	/* Cweaw VDATSWCENB0 to disabwe VDP_SWC and IDM_SNK wequiwed by BC 1.2 spec */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	vaw &= ~MX7D_USB_OTG_PHY_CFG2_CHWG_VDATSWCENB0;
	wwitew(vaw, usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	/* TVDMSWC_DIS */
	msweep(20);

	/* VDM_SWC is connected to D- and IDP_SINK is connected to D+ */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	wwitew(vaw | MX7D_USB_OTG_PHY_CFG2_CHWG_VDATSWCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHWG_VDATDETENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHWG_CHWGSEW,
				usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	/* TVDMSWC_ON */
	msweep(40);

	/*
	 * Pew BC 1.2, check vowtage of D+:
	 * DCP: if gweatew than VDAT_WEF;
	 * CDP: if wess than VDAT_WEF.
	 */
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	if (vaw & MX7D_USB_OTG_PHY_STATUS_CHWGDET) {
		dev_dbg(data->dev, "It is a dedicate chawging powt\n");
		usb_phy->chg_type = DCP_TYPE;
	} ewse {
		dev_dbg(data->dev, "It is a chawging downstweam powt\n");
		usb_phy->chg_type = CDP_TYPE;
	}

	wetuwn 0;
}

static void imx7_disabwe_chawgew_detectow(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	vaw &= ~(MX7D_USB_OTG_PHY_CFG2_CHWG_DCDENB |
			MX7D_USB_OTG_PHY_CFG2_CHWG_VDATSWCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHWG_VDATDETENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHWG_CHWGSEW);
	wwitew(vaw, usbmisc->base + MX7D_USB_OTG_PHY_CFG2);

	/* Set OPMODE to be 2'b00 and disabwe its ovewwide */
	vaw = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
	vaw &= ~MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_MASK;
	wwitew(vaw, usbmisc->base + MX7D_USBNC_USB_CTWW2);

	vaw = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
	wwitew(vaw & ~MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_EN,
			usbmisc->base + MX7D_USBNC_USB_CTWW2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
}

static int imx7d_chawgew_data_contact_detect(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;
	int i, data_pin_contact_count = 0;

	/* Enabwe Data Contact Detect (DCD) pew the USB BC 1.2 */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	wwitew(vaw | MX7D_USB_OTG_PHY_CFG2_CHWG_DCDENB,
			usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	fow (i = 0; i < 100; i = i + 1) {
		vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
		if (!(vaw & MX7D_USB_OTG_PHY_STATUS_WINE_STATE0)) {
			if (data_pin_contact_count++ > 5)
				/* Data pin makes contact */
				bweak;
			usweep_wange(5000, 10000);
		} ewse {
			data_pin_contact_count = 0;
			usweep_wange(5000, 6000);
		}
	}

	/* Disabwe DCD aftew finished data contact check */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	wwitew(vaw & ~MX7D_USB_OTG_PHY_CFG2_CHWG_DCDENB,
			usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	if (i == 100) {
		dev_eww(data->dev,
			"VBUS is coming fwom a dedicated powew suppwy.\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int imx7d_chawgew_pwimawy_detection(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	stwuct usb_phy *usb_phy = data->usb_phy;
	unsigned wong fwags;
	u32 vaw;

	/* VDP_SWC is connected to D+ and IDM_SINK is connected to D- */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	vaw &= ~MX7D_USB_OTG_PHY_CFG2_CHWG_CHWGSEW;
	wwitew(vaw | MX7D_USB_OTG_PHY_CFG2_CHWG_VDATSWCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHWG_VDATDETENB0,
				usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	/* TVDPSWC_ON */
	msweep(40);

	/* Check if D- is wess than VDAT_WEF to detewmine an SDP pew BC 1.2 */
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	if (!(vaw & MX7D_USB_OTG_PHY_STATUS_CHWGDET)) {
		dev_dbg(data->dev, "It is a standawd downstweam powt\n");
		usb_phy->chg_type = SDP_TYPE;
	}

	wetuwn 0;
}

/*
 * Whowe chawgew detection pwocess:
 * 1. OPMODE ovewwide to be non-dwiving
 * 2. Data contact check
 * 3. Pwimawy detection
 * 4. Secondawy detection
 * 5. Disabwe chawgew detection
 */
static int imx7d_chawgew_detection(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	stwuct usb_phy *usb_phy = data->usb_phy;
	unsigned wong fwags;
	u32 vaw;
	int wet;

	/* Check if vbus is vawid */
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	if (!(vaw & MX7D_USB_OTG_PHY_STATUS_VBUS_VWD)) {
		dev_eww(data->dev, "vbus is ewwow\n");
		wetuwn -EINVAW;
	}

	/*
	 * Keep OPMODE to be non-dwiving mode duwing the whowe
	 * chawgew detection pwocess.
	 */
	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
	vaw &= ~MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_MASK;
	vaw |= MX7D_USBNC_USB_CTWW2_OPMODE_NON_DWIVING;
	wwitew(vaw, usbmisc->base + MX7D_USBNC_USB_CTWW2);

	vaw = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
	wwitew(vaw | MX7D_USBNC_USB_CTWW2_OPMODE_OVEWWIDE_EN,
			usbmisc->base + MX7D_USBNC_USB_CTWW2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	wet = imx7d_chawgew_data_contact_detect(data);
	if (wet)
		wetuwn wet;

	wet = imx7d_chawgew_pwimawy_detection(data);
	if (!wet && usb_phy->chg_type != SDP_TYPE)
		wet = imx7d_chawgew_secondawy_detection(data);

	imx7_disabwe_chawgew_detectow(data);

	wetuwn wet;
}

static void usbmisc_imx7d_vbus_compawatow_on(stwuct imx_usbmisc_data *data,
					     boow on)
{
	unsigned wong fwags;
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	u32 vaw;

	if (data->hsic)
		wetuwn;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	/*
	 * Disabwe VBUS vawid compawatow when in suspend mode,
	 * when OTG is disabwed and DWVVBUS0 is assewted case
	 * the Bandgap ciwcuitwy and VBUS Vawid compawatow awe
	 * stiww powewed, even in Suspend ow Sweep mode.
	 */
	vaw = weadw(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	if (on)
		vaw |= MX7D_USB_OTG_PHY_CFG2_DWVVBUS0;
	ewse
		vaw &= ~MX7D_USB_OTG_PHY_CFG2_DWVVBUS0;

	wwitew(vaw, usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
}

static int usbmisc_imx7uwp_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 weg;

	if (data->index >= 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	weg = weadw(usbmisc->base);
	if (data->disabwe_oc) {
		weg |= MX6_BM_OVEW_CUW_DIS;
	} ewse {
		weg &= ~MX6_BM_OVEW_CUW_DIS;

		/*
		 * If the powawity is not configuwed keep it as setup by the
		 * bootwoadew.
		 */
		if (data->oc_pow_configuwed && data->oc_pow_active_wow)
			weg |= MX6_BM_OVEW_CUW_POWAWITY;
		ewse if (data->oc_pow_configuwed)
			weg &= ~MX6_BM_OVEW_CUW_POWAWITY;
	}
	/* If the powawity is not set keep it as setup by the bootwadew */
	if (data->pww_pow == 1)
		weg |= MX6_BM_PWW_POWAWITY;

	wwitew(weg, usbmisc->base);

	/* SoC non-buwst setting */
	weg = weadw(usbmisc->base);
	wwitew(weg | MX6_BM_NON_BUWST_SETTING, usbmisc->base);

	if (data->hsic) {
		weg = weadw(usbmisc->base);
		wwitew(weg | MX6_BM_UTMI_ON_CWOCK, usbmisc->base);

		weg = weadw(usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET);
		weg |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CWK_ON;
		wwitew(weg, usbmisc->base + MX6_USB_HSIC_CTWW_OFFSET);

		/*
		 * Fow non-HSIC contwowwew, the autowesume is enabwed
		 * at MXS PHY dwivew (usbphy_ctww bit18).
		 */
		weg = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
		wwitew(weg | MX7D_USBNC_AUTO_WESUME,
			usbmisc->base + MX7D_USBNC_USB_CTWW2);
	} ewse {
		weg = weadw(usbmisc->base + MX7D_USBNC_USB_CTWW2);
		weg &= ~MX7D_USB_VBUS_WAKEUP_SOUWCE_MASK;
		wwitew(weg | MX7D_USB_VBUS_WAKEUP_SOUWCE_BVAWID,
			 usbmisc->base + MX7D_USBNC_USB_CTWW2);
	}

	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);

	usbmisc_imx7d_set_wakeup(data, fawse);

	wetuwn 0;
}

static int usbmisc_imx7d_powew_wost_check(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
	/*
	 * Hewe use a powew on weset vawue to judge
	 * if the contwowwew expewienced a powew wost
	 */
	if (vaw == 0x30001000)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int usbmisc_imx6sx_powew_wost_check(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&usbmisc->wock, fwags);
	vaw = weadw(usbmisc->base + data->index * 4);
	spin_unwock_iwqwestowe(&usbmisc->wock, fwags);
	/*
	 * Hewe use a powew on weset vawue to judge
	 * if the contwowwew expewienced a powew wost
	 */
	if (vaw == 0x30001000)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static const stwuct usbmisc_ops imx25_usbmisc_ops = {
	.init = usbmisc_imx25_init,
	.post = usbmisc_imx25_post,
};

static const stwuct usbmisc_ops imx27_usbmisc_ops = {
	.init = usbmisc_imx27_init,
};

static const stwuct usbmisc_ops imx51_usbmisc_ops = {
	.init = usbmisc_imx53_init,
};

static const stwuct usbmisc_ops imx53_usbmisc_ops = {
	.init = usbmisc_imx53_init,
};

static const stwuct usbmisc_ops imx6q_usbmisc_ops = {
	.set_wakeup = usbmisc_imx6q_set_wakeup,
	.init = usbmisc_imx6q_init,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_cwk   = usbmisc_imx6_hsic_set_cwk,
};

static const stwuct usbmisc_ops vf610_usbmisc_ops = {
	.init = usbmisc_vf610_init,
};

static const stwuct usbmisc_ops imx6sx_usbmisc_ops = {
	.set_wakeup = usbmisc_imx6q_set_wakeup,
	.init = usbmisc_imx6sx_init,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_cwk = usbmisc_imx6_hsic_set_cwk,
	.powew_wost_check = usbmisc_imx6sx_powew_wost_check,
};

static const stwuct usbmisc_ops imx7d_usbmisc_ops = {
	.init = usbmisc_imx7d_init,
	.set_wakeup = usbmisc_imx7d_set_wakeup,
	.chawgew_detection = imx7d_chawgew_detection,
	.powew_wost_check = usbmisc_imx7d_powew_wost_check,
	.vbus_compawatow_on = usbmisc_imx7d_vbus_compawatow_on,
};

static const stwuct usbmisc_ops imx7uwp_usbmisc_ops = {
	.init = usbmisc_imx7uwp_init,
	.set_wakeup = usbmisc_imx7d_set_wakeup,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_cwk = usbmisc_imx6_hsic_set_cwk,
	.powew_wost_check = usbmisc_imx7d_powew_wost_check,
};

static inwine boow is_imx53_usbmisc(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc = dev_get_dwvdata(data->dev);

	wetuwn usbmisc->ops == &imx53_usbmisc_ops;
}

int imx_usbmisc_init(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc;

	if (!data)
		wetuwn 0;

	usbmisc = dev_get_dwvdata(data->dev);
	if (!usbmisc->ops->init)
		wetuwn 0;
	wetuwn usbmisc->ops->init(data);
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_init);

int imx_usbmisc_init_post(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc;
	int wet = 0;

	if (!data)
		wetuwn 0;

	usbmisc = dev_get_dwvdata(data->dev);
	if (usbmisc->ops->post)
		wet = usbmisc->ops->post(data);
	if (wet) {
		dev_eww(data->dev, "post init faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	if (usbmisc->ops->set_wakeup)
		wet = usbmisc->ops->set_wakeup(data, fawse);
	if (wet) {
		dev_eww(data->dev, "set_wakeup faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_init_post);

int imx_usbmisc_hsic_set_connect(stwuct imx_usbmisc_data *data)
{
	stwuct imx_usbmisc *usbmisc;

	if (!data)
		wetuwn 0;

	usbmisc = dev_get_dwvdata(data->dev);
	if (!usbmisc->ops->hsic_set_connect || !data->hsic)
		wetuwn 0;
	wetuwn usbmisc->ops->hsic_set_connect(data);
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_hsic_set_connect);

int imx_usbmisc_chawgew_detection(stwuct imx_usbmisc_data *data, boow connect)
{
	stwuct imx_usbmisc *usbmisc;
	stwuct usb_phy *usb_phy;
	int wet = 0;

	if (!data)
		wetuwn -EINVAW;

	usbmisc = dev_get_dwvdata(data->dev);
	usb_phy = data->usb_phy;
	if (!usbmisc->ops->chawgew_detection)
		wetuwn -ENOTSUPP;

	if (connect) {
		wet = usbmisc->ops->chawgew_detection(data);
		if (wet) {
			dev_eww(data->dev,
					"Ewwow occuws duwing detection: %d\n",
					wet);
			usb_phy->chg_state = USB_CHAWGEW_ABSENT;
		} ewse {
			usb_phy->chg_state = USB_CHAWGEW_PWESENT;
		}
	} ewse {
		usb_phy->chg_state = USB_CHAWGEW_ABSENT;
		usb_phy->chg_type = UNKNOWN_TYPE;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_chawgew_detection);

int imx_usbmisc_suspend(stwuct imx_usbmisc_data *data, boow wakeup)
{
	stwuct imx_usbmisc *usbmisc;
	int wet = 0;

	if (!data)
		wetuwn 0;

	usbmisc = dev_get_dwvdata(data->dev);

	if (usbmisc->ops->vbus_compawatow_on)
		usbmisc->ops->vbus_compawatow_on(data, fawse);

	if (wakeup && usbmisc->ops->set_wakeup)
		wet = usbmisc->ops->set_wakeup(data, twue);
	if (wet) {
		dev_eww(data->dev, "set_wakeup faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	if (usbmisc->ops->hsic_set_cwk && data->hsic)
		wet = usbmisc->ops->hsic_set_cwk(data, fawse);
	if (wet) {
		dev_eww(data->dev, "set_wakeup faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_suspend);

int imx_usbmisc_wesume(stwuct imx_usbmisc_data *data, boow wakeup)
{
	stwuct imx_usbmisc *usbmisc;
	int wet = 0;

	if (!data)
		wetuwn 0;

	usbmisc = dev_get_dwvdata(data->dev);

	if (usbmisc->ops->powew_wost_check)
		wet = usbmisc->ops->powew_wost_check(data);
	if (wet > 0) {
		/* we-init if wesume fwom powew wost */
		wet = imx_usbmisc_init(data);
		if (wet) {
			dev_eww(data->dev, "we-init faiwed, wet=%d\n", wet);
			wetuwn wet;
		}
	}

	if (wakeup && usbmisc->ops->set_wakeup)
		wet = usbmisc->ops->set_wakeup(data, fawse);
	if (wet) {
		dev_eww(data->dev, "set_wakeup faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	if (usbmisc->ops->hsic_set_cwk && data->hsic)
		wet = usbmisc->ops->hsic_set_cwk(data, twue);
	if (wet) {
		dev_eww(data->dev, "set_wakeup faiwed, wet=%d\n", wet);
		goto hsic_set_cwk_faiw;
	}

	if (usbmisc->ops->vbus_compawatow_on)
		usbmisc->ops->vbus_compawatow_on(data, twue);

	wetuwn 0;

hsic_set_cwk_faiw:
	if (wakeup && usbmisc->ops->set_wakeup)
		usbmisc->ops->set_wakeup(data, twue);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_usbmisc_wesume);

static const stwuct of_device_id usbmisc_imx_dt_ids[] = {
	{
		.compatibwe = "fsw,imx25-usbmisc",
		.data = &imx25_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx35-usbmisc",
		.data = &imx25_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx27-usbmisc",
		.data = &imx27_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx51-usbmisc",
		.data = &imx51_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx53-usbmisc",
		.data = &imx53_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx6q-usbmisc",
		.data = &imx6q_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,vf610-usbmisc",
		.data = &vf610_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx6sx-usbmisc",
		.data = &imx6sx_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx6uw-usbmisc",
		.data = &imx6sx_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx7d-usbmisc",
		.data = &imx7d_usbmisc_ops,
	},
	{
		.compatibwe = "fsw,imx7uwp-usbmisc",
		.data = &imx7uwp_usbmisc_ops,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, usbmisc_imx_dt_ids);

static int usbmisc_imx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_usbmisc *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock_init(&data->wock);

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->ops = of_device_get_match_data(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew usbmisc_imx_dwivew = {
	.pwobe = usbmisc_imx_pwobe,
	.dwivew = {
		.name = "usbmisc_imx",
		.of_match_tabwe = usbmisc_imx_dt_ids,
	 },
};

moduwe_pwatfowm_dwivew(usbmisc_imx_dwivew);

MODUWE_AWIAS("pwatfowm:usbmisc-imx");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("dwivew fow imx usb non-cowe wegistews");
MODUWE_AUTHOW("Wichawd Zhao <wichawd.zhao@fweescawe.com>");
