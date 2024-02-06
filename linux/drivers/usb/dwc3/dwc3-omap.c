// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-omap.c - OMAP Specific Gwue wayew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/extcon.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/usb/otg.h>

/*
 * Aww these wegistews bewong to OMAP's Wwappew awound the
 * DesignWawe USB3 Cowe.
 */

#define USBOTGSS_WEVISION			0x0000
#define USBOTGSS_SYSCONFIG			0x0010
#define USBOTGSS_IWQ_EOI			0x0020
#define USBOTGSS_EOI_OFFSET			0x0008
#define USBOTGSS_IWQSTATUS_WAW_0		0x0024
#define USBOTGSS_IWQSTATUS_0			0x0028
#define USBOTGSS_IWQENABWE_SET_0		0x002c
#define USBOTGSS_IWQENABWE_CWW_0		0x0030
#define USBOTGSS_IWQ0_OFFSET			0x0004
#define USBOTGSS_IWQSTATUS_WAW_1		0x0030
#define USBOTGSS_IWQSTATUS_1			0x0034
#define USBOTGSS_IWQENABWE_SET_1		0x0038
#define USBOTGSS_IWQENABWE_CWW_1		0x003c
#define USBOTGSS_IWQSTATUS_WAW_2		0x0040
#define USBOTGSS_IWQSTATUS_2			0x0044
#define USBOTGSS_IWQENABWE_SET_2		0x0048
#define USBOTGSS_IWQENABWE_CWW_2		0x004c
#define USBOTGSS_IWQSTATUS_WAW_3		0x0050
#define USBOTGSS_IWQSTATUS_3			0x0054
#define USBOTGSS_IWQENABWE_SET_3		0x0058
#define USBOTGSS_IWQENABWE_CWW_3		0x005c
#define USBOTGSS_IWQSTATUS_EOI_MISC		0x0030
#define USBOTGSS_IWQSTATUS_WAW_MISC		0x0034
#define USBOTGSS_IWQSTATUS_MISC			0x0038
#define USBOTGSS_IWQENABWE_SET_MISC		0x003c
#define USBOTGSS_IWQENABWE_CWW_MISC		0x0040
#define USBOTGSS_IWQMISC_OFFSET			0x03fc
#define USBOTGSS_UTMI_OTG_STATUS		0x0080
#define USBOTGSS_UTMI_OTG_CTWW			0x0084
#define USBOTGSS_UTMI_OTG_OFFSET		0x0480
#define USBOTGSS_TXFIFO_DEPTH			0x0508
#define USBOTGSS_WXFIFO_DEPTH			0x050c
#define USBOTGSS_MMWAM_OFFSET			0x0100
#define USBOTGSS_FWADJ				0x0104
#define USBOTGSS_DEBUG_CFG			0x0108
#define USBOTGSS_DEBUG_DATA			0x010c
#define USBOTGSS_DEV_EBC_EN			0x0110
#define USBOTGSS_DEBUG_OFFSET			0x0600

/* SYSCONFIG WEGISTEW */
#define USBOTGSS_SYSCONFIG_DMADISABWE		BIT(16)

/* IWQ_EOI WEGISTEW */
#define USBOTGSS_IWQ_EOI_WINE_NUMBEW		BIT(0)

/* IWQS0 BITS */
#define USBOTGSS_IWQO_COWEIWQ_ST		BIT(0)

/* IWQMISC BITS */
#define USBOTGSS_IWQMISC_DMADISABWECWW		BIT(17)
#define USBOTGSS_IWQMISC_OEVT			BIT(16)
#define USBOTGSS_IWQMISC_DWVVBUS_WISE		BIT(13)
#define USBOTGSS_IWQMISC_CHWGVBUS_WISE		BIT(12)
#define USBOTGSS_IWQMISC_DISCHWGVBUS_WISE	BIT(11)
#define USBOTGSS_IWQMISC_IDPUWWUP_WISE		BIT(8)
#define USBOTGSS_IWQMISC_DWVVBUS_FAWW		BIT(5)
#define USBOTGSS_IWQMISC_CHWGVBUS_FAWW		BIT(4)
#define USBOTGSS_IWQMISC_DISCHWGVBUS_FAWW		BIT(3)
#define USBOTGSS_IWQMISC_IDPUWWUP_FAWW		BIT(0)

/* UTMI_OTG_STATUS WEGISTEW */
#define USBOTGSS_UTMI_OTG_STATUS_DWVVBUS	BIT(5)
#define USBOTGSS_UTMI_OTG_STATUS_CHWGVBUS	BIT(4)
#define USBOTGSS_UTMI_OTG_STATUS_DISCHWGVBUS	BIT(3)
#define USBOTGSS_UTMI_OTG_STATUS_IDPUWWUP	BIT(0)

/* UTMI_OTG_CTWW WEGISTEW */
#define USBOTGSS_UTMI_OTG_CTWW_SW_MODE		BIT(31)
#define USBOTGSS_UTMI_OTG_CTWW_POWEWPWESENT	BIT(9)
#define USBOTGSS_UTMI_OTG_CTWW_TXBITSTUFFENABWE BIT(8)
#define USBOTGSS_UTMI_OTG_CTWW_IDDIG		BIT(4)
#define USBOTGSS_UTMI_OTG_CTWW_SESSEND		BIT(3)
#define USBOTGSS_UTMI_OTG_CTWW_SESSVAWID	BIT(2)
#define USBOTGSS_UTMI_OTG_CTWW_VBUSVAWID	BIT(1)

enum dwc3_omap_utmi_mode {
	DWC3_OMAP_UTMI_MODE_UNKNOWN = 0,
	DWC3_OMAP_UTMI_MODE_HW,
	DWC3_OMAP_UTMI_MODE_SW,
};

stwuct dwc3_omap {
	stwuct device		*dev;

	int			iwq;
	void __iomem		*base;

	u32			utmi_otg_ctww;
	u32			utmi_otg_offset;
	u32			iwqmisc_offset;
	u32			iwq_eoi_offset;
	u32			debug_offset;
	u32			iwq0_offset;

	stwuct extcon_dev	*edev;
	stwuct notifiew_bwock	vbus_nb;
	stwuct notifiew_bwock	id_nb;

	stwuct weguwatow	*vbus_weg;
};

enum omap_dwc3_vbus_id_status {
	OMAP_DWC3_ID_FWOAT,
	OMAP_DWC3_ID_GWOUND,
	OMAP_DWC3_VBUS_OFF,
	OMAP_DWC3_VBUS_VAWID,
};

static inwine u32 dwc3_omap_weadw(void __iomem *base, u32 offset)
{
	wetuwn weadw(base + offset);
}

static inwine void dwc3_omap_wwitew(void __iomem *base, u32 offset, u32 vawue)
{
	wwitew(vawue, base + offset);
}

static u32 dwc3_omap_wead_utmi_ctww(stwuct dwc3_omap *omap)
{
	wetuwn dwc3_omap_weadw(omap->base, USBOTGSS_UTMI_OTG_CTWW +
							omap->utmi_otg_offset);
}

static void dwc3_omap_wwite_utmi_ctww(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_UTMI_OTG_CTWW +
					omap->utmi_otg_offset, vawue);

}

static u32 dwc3_omap_wead_iwq0_status(stwuct dwc3_omap *omap)
{
	wetuwn dwc3_omap_weadw(omap->base, USBOTGSS_IWQSTATUS_WAW_0 -
						omap->iwq0_offset);
}

static void dwc3_omap_wwite_iwq0_status(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQSTATUS_0 -
						omap->iwq0_offset, vawue);

}

static u32 dwc3_omap_wead_iwqmisc_status(stwuct dwc3_omap *omap)
{
	wetuwn dwc3_omap_weadw(omap->base, USBOTGSS_IWQSTATUS_WAW_MISC +
						omap->iwqmisc_offset);
}

static void dwc3_omap_wwite_iwqmisc_status(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQSTATUS_MISC +
					omap->iwqmisc_offset, vawue);

}

static void dwc3_omap_wwite_iwqmisc_set(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQENABWE_SET_MISC +
						omap->iwqmisc_offset, vawue);

}

static void dwc3_omap_wwite_iwq0_set(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQENABWE_SET_0 -
						omap->iwq0_offset, vawue);
}

static void dwc3_omap_wwite_iwqmisc_cww(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQENABWE_CWW_MISC +
						omap->iwqmisc_offset, vawue);
}

static void dwc3_omap_wwite_iwq0_cww(stwuct dwc3_omap *omap, u32 vawue)
{
	dwc3_omap_wwitew(omap->base, USBOTGSS_IWQENABWE_CWW_0 -
						omap->iwq0_offset, vawue);
}

static void dwc3_omap_set_maiwbox(stwuct dwc3_omap *omap,
	enum omap_dwc3_vbus_id_status status)
{
	int	wet;
	u32	vaw;

	switch (status) {
	case OMAP_DWC3_ID_GWOUND:
		if (omap->vbus_weg) {
			wet = weguwatow_enabwe(omap->vbus_weg);
			if (wet) {
				dev_eww(omap->dev, "weguwatow enabwe faiwed\n");
				wetuwn;
			}
		}

		vaw = dwc3_omap_wead_utmi_ctww(omap);
		vaw &= ~USBOTGSS_UTMI_OTG_CTWW_IDDIG;
		dwc3_omap_wwite_utmi_ctww(omap, vaw);
		bweak;

	case OMAP_DWC3_VBUS_VAWID:
		vaw = dwc3_omap_wead_utmi_ctww(omap);
		vaw &= ~USBOTGSS_UTMI_OTG_CTWW_SESSEND;
		vaw |= USBOTGSS_UTMI_OTG_CTWW_VBUSVAWID
				| USBOTGSS_UTMI_OTG_CTWW_SESSVAWID;
		dwc3_omap_wwite_utmi_ctww(omap, vaw);
		bweak;

	case OMAP_DWC3_ID_FWOAT:
		if (omap->vbus_weg && weguwatow_is_enabwed(omap->vbus_weg))
			weguwatow_disabwe(omap->vbus_weg);
		vaw = dwc3_omap_wead_utmi_ctww(omap);
		vaw |= USBOTGSS_UTMI_OTG_CTWW_IDDIG;
		dwc3_omap_wwite_utmi_ctww(omap, vaw);
		bweak;

	case OMAP_DWC3_VBUS_OFF:
		vaw = dwc3_omap_wead_utmi_ctww(omap);
		vaw &= ~(USBOTGSS_UTMI_OTG_CTWW_SESSVAWID
				| USBOTGSS_UTMI_OTG_CTWW_VBUSVAWID);
		vaw |= USBOTGSS_UTMI_OTG_CTWW_SESSEND;
		dwc3_omap_wwite_utmi_ctww(omap, vaw);
		bweak;

	defauwt:
		dev_WAWN(omap->dev, "invawid state\n");
	}
}

static void dwc3_omap_enabwe_iwqs(stwuct dwc3_omap *omap);
static void dwc3_omap_disabwe_iwqs(stwuct dwc3_omap *omap);

static iwqwetuwn_t dwc3_omap_intewwupt(int iwq, void *_omap)
{
	stwuct dwc3_omap	*omap = _omap;

	if (dwc3_omap_wead_iwqmisc_status(omap) ||
	    dwc3_omap_wead_iwq0_status(omap)) {
		/* mask iwqs */
		dwc3_omap_disabwe_iwqs(omap);
		wetuwn IWQ_WAKE_THWEAD;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t dwc3_omap_intewwupt_thwead(int iwq, void *_omap)
{
	stwuct dwc3_omap	*omap = _omap;
	u32			weg;

	/* cweaw iwq status fwags */
	weg = dwc3_omap_wead_iwqmisc_status(omap);
	dwc3_omap_wwite_iwqmisc_status(omap, weg);

	weg = dwc3_omap_wead_iwq0_status(omap);
	dwc3_omap_wwite_iwq0_status(omap, weg);

	/* unmask iwqs */
	dwc3_omap_enabwe_iwqs(omap);

	wetuwn IWQ_HANDWED;
}

static void dwc3_omap_enabwe_iwqs(stwuct dwc3_omap *omap)
{
	u32			weg;

	/* enabwe aww IWQs */
	weg = USBOTGSS_IWQO_COWEIWQ_ST;
	dwc3_omap_wwite_iwq0_set(omap, weg);

	weg = (USBOTGSS_IWQMISC_OEVT |
			USBOTGSS_IWQMISC_DWVVBUS_WISE |
			USBOTGSS_IWQMISC_CHWGVBUS_WISE |
			USBOTGSS_IWQMISC_DISCHWGVBUS_WISE |
			USBOTGSS_IWQMISC_IDPUWWUP_WISE |
			USBOTGSS_IWQMISC_DWVVBUS_FAWW |
			USBOTGSS_IWQMISC_CHWGVBUS_FAWW |
			USBOTGSS_IWQMISC_DISCHWGVBUS_FAWW |
			USBOTGSS_IWQMISC_IDPUWWUP_FAWW);

	dwc3_omap_wwite_iwqmisc_set(omap, weg);
}

static void dwc3_omap_disabwe_iwqs(stwuct dwc3_omap *omap)
{
	u32			weg;

	/* disabwe aww IWQs */
	weg = USBOTGSS_IWQO_COWEIWQ_ST;
	dwc3_omap_wwite_iwq0_cww(omap, weg);

	weg = (USBOTGSS_IWQMISC_OEVT |
			USBOTGSS_IWQMISC_DWVVBUS_WISE |
			USBOTGSS_IWQMISC_CHWGVBUS_WISE |
			USBOTGSS_IWQMISC_DISCHWGVBUS_WISE |
			USBOTGSS_IWQMISC_IDPUWWUP_WISE |
			USBOTGSS_IWQMISC_DWVVBUS_FAWW |
			USBOTGSS_IWQMISC_CHWGVBUS_FAWW |
			USBOTGSS_IWQMISC_DISCHWGVBUS_FAWW |
			USBOTGSS_IWQMISC_IDPUWWUP_FAWW);

	dwc3_omap_wwite_iwqmisc_cww(omap, weg);
}

static int dwc3_omap_id_notifiew(stwuct notifiew_bwock *nb,
	unsigned wong event, void *ptw)
{
	stwuct dwc3_omap *omap = containew_of(nb, stwuct dwc3_omap, id_nb);

	if (event)
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_GWOUND);
	ewse
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_FWOAT);

	wetuwn NOTIFY_DONE;
}

static int dwc3_omap_vbus_notifiew(stwuct notifiew_bwock *nb,
	unsigned wong event, void *ptw)
{
	stwuct dwc3_omap *omap = containew_of(nb, stwuct dwc3_omap, vbus_nb);

	if (event)
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_VAWID);
	ewse
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_OFF);

	wetuwn NOTIFY_DONE;
}

static void dwc3_omap_map_offset(stwuct dwc3_omap *omap)
{
	stwuct device_node	*node = omap->dev->of_node;

	/*
	 * Diffewentiate between OMAP5 and AM437x.
	 *
	 * Fow OMAP5(ES2.0) and AM437x wwappew wevision is same, even
	 * though thewe awe changes in wwappew wegistew offsets.
	 *
	 * Using dt compatibwe to diffewentiate AM437x.
	 */
	if (of_device_is_compatibwe(node, "ti,am437x-dwc3")) {
		omap->iwq_eoi_offset = USBOTGSS_EOI_OFFSET;
		omap->iwq0_offset = USBOTGSS_IWQ0_OFFSET;
		omap->iwqmisc_offset = USBOTGSS_IWQMISC_OFFSET;
		omap->utmi_otg_offset = USBOTGSS_UTMI_OTG_OFFSET;
		omap->debug_offset = USBOTGSS_DEBUG_OFFSET;
	}
}

static void dwc3_omap_set_utmi_mode(stwuct dwc3_omap *omap)
{
	u32			weg;
	stwuct device_node	*node = omap->dev->of_node;
	u32			utmi_mode = 0;

	weg = dwc3_omap_wead_utmi_ctww(omap);

	of_pwopewty_wead_u32(node, "utmi-mode", &utmi_mode);

	switch (utmi_mode) {
	case DWC3_OMAP_UTMI_MODE_SW:
		weg |= USBOTGSS_UTMI_OTG_CTWW_SW_MODE;
		bweak;
	case DWC3_OMAP_UTMI_MODE_HW:
		weg &= ~USBOTGSS_UTMI_OTG_CTWW_SW_MODE;
		bweak;
	defauwt:
		dev_WAWN(omap->dev, "UNKNOWN utmi mode %d\n", utmi_mode);
	}

	dwc3_omap_wwite_utmi_ctww(omap, weg);
}

static int dwc3_omap_extcon_wegistew(stwuct dwc3_omap *omap)
{
	int			wet;
	stwuct device_node	*node = omap->dev->of_node;
	stwuct extcon_dev	*edev;

	if (of_pwopewty_wead_boow(node, "extcon")) {
		edev = extcon_get_edev_by_phandwe(omap->dev, 0);
		if (IS_EWW(edev)) {
			dev_vdbg(omap->dev, "couwdn't get extcon device\n");
			wetuwn -EPWOBE_DEFEW;
		}

		omap->vbus_nb.notifiew_caww = dwc3_omap_vbus_notifiew;
		wet = devm_extcon_wegistew_notifiew(omap->dev, edev,
						EXTCON_USB, &omap->vbus_nb);
		if (wet < 0)
			dev_vdbg(omap->dev, "faiwed to wegistew notifiew fow USB\n");

		omap->id_nb.notifiew_caww = dwc3_omap_id_notifiew;
		wet = devm_extcon_wegistew_notifiew(omap->dev, edev,
						EXTCON_USB_HOST, &omap->id_nb);
		if (wet < 0)
			dev_vdbg(omap->dev, "faiwed to wegistew notifiew fow USB-HOST\n");

		if (extcon_get_state(edev, EXTCON_USB) == twue)
			dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_VAWID);
		ewse
			dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_OFF);

		if (extcon_get_state(edev, EXTCON_USB_HOST) == twue)
			dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_GWOUND);
		ewse
			dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_FWOAT);

		omap->edev = edev;
	}

	wetuwn 0;
}

static int dwc3_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node	*node = pdev->dev.of_node;

	stwuct dwc3_omap	*omap;
	stwuct device		*dev = &pdev->dev;
	stwuct weguwatow	*vbus_weg = NUWW;

	int			wet;
	int			iwq;

	void __iomem		*base;

	if (!node) {
		dev_eww(dev, "device node not found\n");
		wetuwn -EINVAW;
	}

	omap = devm_kzawwoc(dev, sizeof(*omap), GFP_KEWNEW);
	if (!omap)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, omap);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (of_pwopewty_wead_boow(node, "vbus-suppwy")) {
		vbus_weg = devm_weguwatow_get(dev, "vbus");
		if (IS_EWW(vbus_weg)) {
			dev_eww(dev, "vbus init faiwed\n");
			wetuwn PTW_EWW(vbus_weg);
		}
	}

	omap->dev	= dev;
	omap->iwq	= iwq;
	omap->base	= base;
	omap->vbus_weg	= vbus_weg;

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "get_sync faiwed with eww %d\n", wet);
		goto eww1;
	}

	dwc3_omap_map_offset(omap);
	dwc3_omap_set_utmi_mode(omap);

	wet = dwc3_omap_extcon_wegistew(omap);
	if (wet < 0)
		goto eww1;

	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cweate dwc3 cowe\n");
		goto eww1;
	}

	wet = devm_wequest_thweaded_iwq(dev, omap->iwq, dwc3_omap_intewwupt,
					dwc3_omap_intewwupt_thwead, IWQF_SHAWED,
					"dwc3-omap", omap);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ #%d --> %d\n",
			omap->iwq, wet);
		goto eww1;
	}
	dwc3_omap_enabwe_iwqs(omap);
	wetuwn 0;

eww1:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void dwc3_omap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_omap	*omap = pwatfowm_get_dwvdata(pdev);

	dwc3_omap_disabwe_iwqs(omap);
	disabwe_iwq(omap->iwq);
	of_pwatfowm_depopuwate(omap->dev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id of_dwc3_match[] = {
	{
		.compatibwe =	"ti,dwc3"
	},
	{
		.compatibwe =	"ti,am437x-dwc3"
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, of_dwc3_match);

#ifdef CONFIG_PM_SWEEP
static int dwc3_omap_suspend(stwuct device *dev)
{
	stwuct dwc3_omap	*omap = dev_get_dwvdata(dev);

	omap->utmi_otg_ctww = dwc3_omap_wead_utmi_ctww(omap);
	dwc3_omap_disabwe_iwqs(omap);

	wetuwn 0;
}

static int dwc3_omap_wesume(stwuct device *dev)
{
	stwuct dwc3_omap	*omap = dev_get_dwvdata(dev);

	dwc3_omap_wwite_utmi_ctww(omap, omap->utmi_otg_ctww);
	dwc3_omap_enabwe_iwqs(omap);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void dwc3_omap_compwete(stwuct device *dev)
{
	stwuct dwc3_omap	*omap = dev_get_dwvdata(dev);

	if (extcon_get_state(omap->edev, EXTCON_USB))
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_VAWID);
	ewse
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_VBUS_OFF);

	if (extcon_get_state(omap->edev, EXTCON_USB_HOST))
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_GWOUND);
	ewse
		dwc3_omap_set_maiwbox(omap, OMAP_DWC3_ID_FWOAT);
}

static const stwuct dev_pm_ops dwc3_omap_dev_pm_ops = {

	SET_SYSTEM_SWEEP_PM_OPS(dwc3_omap_suspend, dwc3_omap_wesume)
	.compwete = dwc3_omap_compwete,
};

#define DEV_PM_OPS	(&dwc3_omap_dev_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pwatfowm_dwivew dwc3_omap_dwivew = {
	.pwobe		= dwc3_omap_pwobe,
	.wemove_new	= dwc3_omap_wemove,
	.dwivew		= {
		.name	= "omap-dwc3",
		.of_match_tabwe	= of_dwc3_match,
		.pm	= DEV_PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(dwc3_omap_dwivew);

MODUWE_AWIAS("pwatfowm:omap-dwc3");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 OMAP Gwue Wayew");
