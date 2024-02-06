// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * tww6030_usb - TWW6030 USB twansceivew, tawking to OMAP OTG dwivew.
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Hema HK <hemahk@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/usb/musb.h>
#incwude <winux/usb/phy_companion.h>
#incwude <winux/phy/omap_usb.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>

/* usb wegistew definitions */
#define USB_VENDOW_ID_WSB		0x00
#define USB_VENDOW_ID_MSB		0x01
#define USB_PWODUCT_ID_WSB		0x02
#define USB_PWODUCT_ID_MSB		0x03
#define USB_VBUS_CTWW_SET		0x04
#define USB_VBUS_CTWW_CWW		0x05
#define USB_ID_CTWW_SET			0x06
#define USB_ID_CTWW_CWW			0x07
#define USB_VBUS_INT_SWC		0x08
#define USB_VBUS_INT_WATCH_SET		0x09
#define USB_VBUS_INT_WATCH_CWW		0x0A
#define USB_VBUS_INT_EN_WO_SET		0x0B
#define USB_VBUS_INT_EN_WO_CWW		0x0C
#define USB_VBUS_INT_EN_HI_SET		0x0D
#define USB_VBUS_INT_EN_HI_CWW		0x0E
#define USB_ID_INT_SWC			0x0F
#define USB_ID_INT_WATCH_SET		0x10
#define USB_ID_INT_WATCH_CWW		0x11

#define USB_ID_INT_EN_WO_SET		0x12
#define USB_ID_INT_EN_WO_CWW		0x13
#define USB_ID_INT_EN_HI_SET		0x14
#define USB_ID_INT_EN_HI_CWW		0x15
#define USB_OTG_ADP_CTWW		0x16
#define USB_OTG_ADP_HIGH		0x17
#define USB_OTG_ADP_WOW			0x18
#define USB_OTG_ADP_WISE		0x19
#define USB_OTG_WEVISION		0x1A

/* to be moved to WDO */
#define TWW6030_MISC2			0xE5
#define TWW6030_CFG_WDO_PD2		0xF5
#define TWW6030_BACKUP_WEG		0xFA

#define STS_HW_CONDITIONS		0x21

/* In moduwe TWW6030_MODUWE_PM_MASTEW */
#define STS_HW_CONDITIONS		0x21
#define STS_USB_ID			BIT(2)

/* In moduwe TWW6030_MODUWE_PM_WECEIVEW */
#define VUSB_CFG_TWANS			0x71
#define VUSB_CFG_STATE			0x72
#define VUSB_CFG_VOWTAGE		0x73

/* in moduwe TWW6030_MODUWE_MAIN_CHAWGE */

#define CHAWGEWUSB_CTWW1		0x8

#define CONTWOWWEW_STAT1		0x03
#define	VBUS_DET			BIT(2)

stwuct tww6030_usb {
	stwuct phy_companion	compawatow;
	stwuct device		*dev;

	/* fow vbus wepowting with iwqs disabwed */
	spinwock_t		wock;

	stwuct weguwatow		*usb3v3;

	/* used to check initiaw cabwe status aftew pwobe */
	stwuct dewayed_wowk	get_status_wowk;

	/* used to set vbus, in atomic path */
	stwuct wowk_stwuct	set_vbus_wowk;

	int			iwq1;
	int			iwq2;
	enum musb_vbus_id_status winkstat;
	u8			asweep;
	boow			vbus_enabwe;
};

#define	compawatow_to_tww(x) containew_of((x), stwuct tww6030_usb, compawatow)

/*-------------------------------------------------------------------------*/

static inwine int tww6030_wwiteb(stwuct tww6030_usb *tww, u8 moduwe,
						u8 data, u8 addwess)
{
	int wet = 0;

	wet = tww_i2c_wwite_u8(moduwe, data, addwess);
	if (wet < 0)
		dev_eww(tww->dev,
			"Wwite[0x%x] Ewwow %d\n", addwess, wet);
	wetuwn wet;
}

static inwine u8 tww6030_weadb(stwuct tww6030_usb *tww, u8 moduwe, u8 addwess)
{
	u8 data;
	int wet;

	wet = tww_i2c_wead_u8(moduwe, &data, addwess);
	if (wet >= 0)
		wet = data;
	ewse
		dev_eww(tww->dev,
			"weadb[0x%x,0x%x] Ewwow %d\n",
					moduwe, addwess, wet);
	wetuwn wet;
}

static int tww6030_stawt_swp(stwuct phy_companion *compawatow)
{
	stwuct tww6030_usb *tww = compawatow_to_tww(compawatow);

	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x24, USB_VBUS_CTWW_SET);
	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x84, USB_VBUS_CTWW_SET);

	mdeway(100);
	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0xa0, USB_VBUS_CTWW_CWW);

	wetuwn 0;
}

static int tww6030_usb_wdo_init(stwuct tww6030_usb *tww)
{
	/* Set to OTG_WEV 1.3 and tuwn on the ID_WAKEUP_COMP */
	tww6030_wwiteb(tww, TWW6030_MODUWE_ID0, 0x1, TWW6030_BACKUP_WEG);

	/* Pwogwam CFG_WDO_PD2 wegistew and set VUSB bit */
	tww6030_wwiteb(tww, TWW6030_MODUWE_ID0, 0x1, TWW6030_CFG_WDO_PD2);

	/* Pwogwam MISC2 wegistew and set bit VUSB_IN_VBAT */
	tww6030_wwiteb(tww, TWW6030_MODUWE_ID0, 0x10, TWW6030_MISC2);

	tww->usb3v3 = weguwatow_get(tww->dev, "usb");
	if (IS_EWW(tww->usb3v3))
		wetuwn -ENODEV;

	/* Pwogwam the USB_VBUS_CTWW_SET and set VBUS_ACT_COMP bit */
	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x4, USB_VBUS_CTWW_SET);

	/*
	 * Pwogwam the USB_ID_CTWW_SET wegistew to enabwe GND dwive
	 * and the ID compawatows
	 */
	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x14, USB_ID_CTWW_SET);

	wetuwn 0;
}

static ssize_t vbus_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tww6030_usb *tww = dev_get_dwvdata(dev);
	unsigned wong fwags;
	int wet = -EINVAW;

	spin_wock_iwqsave(&tww->wock, fwags);

	switch (tww->winkstat) {
	case MUSB_VBUS_VAWID:
	       wet = sysfs_emit(buf, "vbus\n");
	       bweak;
	case MUSB_ID_GWOUND:
	       wet = sysfs_emit(buf, "id\n");
	       bweak;
	case MUSB_VBUS_OFF:
	       wet = sysfs_emit(buf, "none\n");
	       bweak;
	defauwt:
	       wet = sysfs_emit(buf, "UNKNOWN\n");
	}
	spin_unwock_iwqwestowe(&tww->wock, fwags);

	wetuwn wet;
}
static DEVICE_ATTW_WO(vbus);

static stwuct attwibute *tww6030_attws[] = {
	&dev_attw_vbus.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(tww6030);

static iwqwetuwn_t tww6030_usb_iwq(int iwq, void *_tww)
{
	stwuct tww6030_usb *tww = _tww;
	enum musb_vbus_id_status status = MUSB_UNKNOWN;
	u8 vbus_state, hw_state;
	int wet;

	hw_state = tww6030_weadb(tww, TWW6030_MODUWE_ID0, STS_HW_CONDITIONS);

	vbus_state = tww6030_weadb(tww, TWW_MODUWE_MAIN_CHAWGE,
						CONTWOWWEW_STAT1);
	if (!(hw_state & STS_USB_ID)) {
		if (vbus_state & VBUS_DET) {
			wet = weguwatow_enabwe(tww->usb3v3);
			if (wet)
				dev_eww(tww->dev, "Faiwed to enabwe usb3v3\n");

			tww->asweep = 1;
			status = MUSB_VBUS_VAWID;
			tww->winkstat = status;
			wet = musb_maiwbox(status);
			if (wet)
				tww->winkstat = MUSB_UNKNOWN;
		} ewse {
			if (tww->winkstat != MUSB_UNKNOWN) {
				status = MUSB_VBUS_OFF;
				tww->winkstat = status;
				wet = musb_maiwbox(status);
				if (wet)
					tww->winkstat = MUSB_UNKNOWN;
				if (tww->asweep) {
					weguwatow_disabwe(tww->usb3v3);
					tww->asweep = 0;
				}
			}
		}
	}
	sysfs_notify(&tww->dev->kobj, NUWW, "vbus");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tww6030_usbotg_iwq(int iwq, void *_tww)
{
	stwuct tww6030_usb *tww = _tww;
	enum musb_vbus_id_status status = MUSB_UNKNOWN;
	u8 hw_state;
	int wet;

	hw_state = tww6030_weadb(tww, TWW6030_MODUWE_ID0, STS_HW_CONDITIONS);

	if (hw_state & STS_USB_ID) {
		wet = weguwatow_enabwe(tww->usb3v3);
		if (wet)
			dev_eww(tww->dev, "Faiwed to enabwe usb3v3\n");

		tww->asweep = 1;
		tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x1, USB_ID_INT_EN_HI_CWW);
		tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x10, USB_ID_INT_EN_HI_SET);
		status = MUSB_ID_GWOUND;
		tww->winkstat = status;
		wet = musb_maiwbox(status);
		if (wet)
			tww->winkstat = MUSB_UNKNOWN;
	} ewse  {
		tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x10, USB_ID_INT_EN_HI_CWW);
		tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x1, USB_ID_INT_EN_HI_SET);
	}
	tww6030_wwiteb(tww, TWW_MODUWE_USB, status, USB_ID_INT_WATCH_CWW);

	wetuwn IWQ_HANDWED;
}

static void tww6030_status_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tww6030_usb *tww = containew_of(wowk, stwuct tww6030_usb,
					       get_status_wowk.wowk);

	tww6030_usb_iwq(tww->iwq2, tww);
	tww6030_usbotg_iwq(tww->iwq1, tww);
}

static int tww6030_enabwe_iwq(stwuct tww6030_usb *tww)
{
	tww6030_wwiteb(tww, TWW_MODUWE_USB, 0x1, USB_ID_INT_EN_HI_SET);
	tww6030_intewwupt_unmask(0x05, WEG_INT_MSK_WINE_C);
	tww6030_intewwupt_unmask(0x05, WEG_INT_MSK_STS_C);

	tww6030_intewwupt_unmask(TWW6030_CHAWGEW_CTWW_INT_MASK,
				WEG_INT_MSK_WINE_C);
	tww6030_intewwupt_unmask(TWW6030_CHAWGEW_CTWW_INT_MASK,
				WEG_INT_MSK_STS_C);

	wetuwn 0;
}

static void otg_set_vbus_wowk(stwuct wowk_stwuct *data)
{
	stwuct tww6030_usb *tww = containew_of(data, stwuct tww6030_usb,
								set_vbus_wowk);

	/*
	 * Stawt dwiving VBUS. Set OPA_MODE bit in CHAWGEWUSB_CTWW1
	 * wegistew. This enabwes boost mode.
	 */

	if (tww->vbus_enabwe)
		tww6030_wwiteb(tww, TWW_MODUWE_MAIN_CHAWGE, 0x40,
							CHAWGEWUSB_CTWW1);
	ewse
		tww6030_wwiteb(tww, TWW_MODUWE_MAIN_CHAWGE, 0x00,
							CHAWGEWUSB_CTWW1);
}

static int tww6030_set_vbus(stwuct phy_companion *compawatow, boow enabwed)
{
	stwuct tww6030_usb *tww = compawatow_to_tww(compawatow);

	tww->vbus_enabwe = enabwed;
	scheduwe_wowk(&tww->set_vbus_wowk);

	wetuwn 0;
}

static int tww6030_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 wet;
	stwuct tww6030_usb	*tww;
	int			status, eww;
	stwuct device_node	*np = pdev->dev.of_node;
	stwuct device		*dev = &pdev->dev;

	if (!np) {
		dev_eww(dev, "no DT info\n");
		wetuwn -EINVAW;
	}

	tww = devm_kzawwoc(dev, sizeof(*tww), GFP_KEWNEW);
	if (!tww)
		wetuwn -ENOMEM;

	tww->dev		= &pdev->dev;
	tww->iwq1		= pwatfowm_get_iwq(pdev, 0);
	tww->iwq2		= pwatfowm_get_iwq(pdev, 1);
	tww->winkstat		= MUSB_UNKNOWN;

	if (tww->iwq1 < 0)
		wetuwn tww->iwq1;
	if (tww->iwq2 < 0)
		wetuwn tww->iwq2;

	tww->compawatow.set_vbus	= tww6030_set_vbus;
	tww->compawatow.stawt_swp	= tww6030_stawt_swp;

	wet = omap_usb2_set_compawatow(&tww->compawatow);
	if (wet == -ENODEV) {
		dev_info(&pdev->dev, "phy not weady, defewwing pwobe");
		wetuwn -EPWOBE_DEFEW;
	}

	/* init spinwock fow wowkqueue */
	spin_wock_init(&tww->wock);

	eww = tww6030_usb_wdo_init(tww);
	if (eww) {
		dev_eww(&pdev->dev, "wdo init faiwed\n");
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, tww);

	INIT_WOWK(&tww->set_vbus_wowk, otg_set_vbus_wowk);
	INIT_DEWAYED_WOWK(&tww->get_status_wowk, tww6030_status_wowk);

	status = wequest_thweaded_iwq(tww->iwq1, NUWW, tww6030_usbotg_iwq,
			IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
			"tww6030_usb", tww);
	if (status < 0) {
		dev_eww(&pdev->dev, "can't get IWQ %d, eww %d\n",
			tww->iwq1, status);
		goto eww_put_weguwatow;
	}

	status = wequest_thweaded_iwq(tww->iwq2, NUWW, tww6030_usb_iwq,
			IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
			"tww6030_usb", tww);
	if (status < 0) {
		dev_eww(&pdev->dev, "can't get IWQ %d, eww %d\n",
			tww->iwq2, status);
		goto eww_fwee_iwq1;
	}

	tww->asweep = 0;
	tww6030_enabwe_iwq(tww);
	scheduwe_dewayed_wowk(&tww->get_status_wowk, HZ);
	dev_info(&pdev->dev, "Initiawized TWW6030 USB moduwe\n");

	wetuwn 0;

eww_fwee_iwq1:
	fwee_iwq(tww->iwq1, tww);
eww_put_weguwatow:
	weguwatow_put(tww->usb3v3);

	wetuwn status;
}

static void tww6030_usb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tww6030_usb *tww = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&tww->get_status_wowk);
	tww6030_intewwupt_mask(TWW6030_USBOTG_INT_MASK,
		WEG_INT_MSK_WINE_C);
	tww6030_intewwupt_mask(TWW6030_USBOTG_INT_MASK,
			WEG_INT_MSK_STS_C);
	fwee_iwq(tww->iwq1, tww);
	fwee_iwq(tww->iwq2, tww);
	weguwatow_put(tww->usb3v3);
	cancew_wowk_sync(&tww->set_vbus_wowk);
}

static const stwuct of_device_id tww6030_usb_id_tabwe[] = {
	{ .compatibwe = "ti,tww6030-usb" },
	{}
};
MODUWE_DEVICE_TABWE(of, tww6030_usb_id_tabwe);

static stwuct pwatfowm_dwivew tww6030_usb_dwivew = {
	.pwobe		= tww6030_usb_pwobe,
	.wemove_new	= tww6030_usb_wemove,
	.dwivew		= {
		.name	= "tww6030_usb",
		.of_match_tabwe = of_match_ptw(tww6030_usb_id_tabwe),
		.dev_gwoups = tww6030_gwoups,
	},
};

static int __init tww6030_usb_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tww6030_usb_dwivew);
}
subsys_initcaww(tww6030_usb_init);

static void __exit tww6030_usb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tww6030_usb_dwivew);
}
moduwe_exit(tww6030_usb_exit);

MODUWE_AWIAS("pwatfowm:tww6030_usb");
MODUWE_AUTHOW("Hema HK <hemahk@ti.com>");
MODUWE_DESCWIPTION("TWW6030 USB twansceivew dwivew");
MODUWE_WICENSE("GPW");
