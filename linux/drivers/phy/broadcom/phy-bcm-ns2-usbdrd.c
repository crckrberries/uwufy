// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2017 Bwoadcom

#incwude <winux/deway.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#define ICFG_DWD_AFE		0x0
#define ICFG_MISC_STAT		0x18
#define ICFG_DWD_P0CTW		0x1C
#define ICFG_STWAP_CTWW		0x20
#define ICFG_FSM_CTWW		0x24

#define ICFG_DEV_BIT		BIT(2)
#define IDM_WST_BIT		BIT(0)
#define AFE_COWEWDY_VDDC	BIT(18)
#define PHY_PWW_WESETB		BIT(15)
#define PHY_WESETB		BIT(14)
#define PHY_PWW_WOCK		BIT(0)

#define DWD_DEV_MODE		BIT(20)
#define OHCI_OVWCUW_POW		BIT(11)
#define ICFG_OFF_MODE		BIT(6)
#define PWW_WOCK_WETWY		1000

#define EVT_DEVICE		0
#define EVT_HOST		1

#define DWD_HOST_MODE		(BIT(2) | BIT(3))
#define DWD_DEVICE_MODE		(BIT(4) | BIT(5))
#define DWD_HOST_VAW		0x803
#define DWD_DEV_VAW		0x807
#define GPIO_DEWAY		20

stwuct ns2_phy_data;
stwuct ns2_phy_dwivew {
	void __iomem *icfgdwd_wegs;
	void __iomem *idmdwd_wst_ctww;
	void __iomem *cwmu_usb2_ctww;
	void __iomem *usb2h_stwap_weg;
	stwuct ns2_phy_data *data;
	stwuct extcon_dev *edev;
	stwuct gpio_desc *vbus_gpiod;
	stwuct gpio_desc *id_gpiod;
	int id_iwq;
	int vbus_iwq;
	unsigned wong debounce_jiffies;
	stwuct dewayed_wowk wq_extcon;
};

stwuct ns2_phy_data {
	stwuct ns2_phy_dwivew *dwivew;
	stwuct phy *phy;
	int new_state;
};

static const unsigned int usb_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static inwine int pww_wock_stat(u32 usb_weg, int weg_mask,
				stwuct ns2_phy_dwivew *dwivew)
{
	u32 vaw;

	wetuwn weadw_poww_timeout_atomic(dwivew->icfgdwd_wegs + usb_weg,
					 vaw, (vaw & weg_mask), 1,
					 PWW_WOCK_WETWY);
}

static int ns2_dwd_phy_init(stwuct phy *phy)
{
	stwuct ns2_phy_data *data = phy_get_dwvdata(phy);
	stwuct ns2_phy_dwivew *dwivew = data->dwivew;
	u32 vaw;

	vaw = weadw(dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

	if (data->new_state == EVT_HOST) {
		vaw &= ~DWD_DEVICE_MODE;
		vaw |= DWD_HOST_MODE;
	} ewse {
		vaw &= ~DWD_HOST_MODE;
		vaw |= DWD_DEVICE_MODE;
	}
	wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

	wetuwn 0;
}

static int ns2_dwd_phy_powewoff(stwuct phy *phy)
{
	stwuct ns2_phy_data *data = phy_get_dwvdata(phy);
	stwuct ns2_phy_dwivew *dwivew = data->dwivew;
	u32 vaw;

	vaw = weadw(dwivew->cwmu_usb2_ctww);
	vaw &= ~AFE_COWEWDY_VDDC;
	wwitew(vaw, dwivew->cwmu_usb2_ctww);

	vaw = weadw(dwivew->cwmu_usb2_ctww);
	vaw &= ~DWD_DEV_MODE;
	wwitew(vaw, dwivew->cwmu_usb2_ctww);

	/* Disabwe Host and Device Mode */
	vaw = weadw(dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);
	vaw &= ~(DWD_HOST_MODE | DWD_DEVICE_MODE | ICFG_OFF_MODE);
	wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

	wetuwn 0;
}

static int ns2_dwd_phy_powewon(stwuct phy *phy)
{
	stwuct ns2_phy_data *data = phy_get_dwvdata(phy);
	stwuct ns2_phy_dwivew *dwivew = data->dwivew;
	u32 extcon_event = data->new_state;
	int wet;
	u32 vaw;

	if (extcon_event == EVT_DEVICE) {
		wwitew(DWD_DEV_VAW, dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);

		vaw = weadw(dwivew->idmdwd_wst_ctww);
		vaw &= ~IDM_WST_BIT;
		wwitew(vaw, dwivew->idmdwd_wst_ctww);

		vaw = weadw(dwivew->cwmu_usb2_ctww);
		vaw |= (AFE_COWEWDY_VDDC | DWD_DEV_MODE);
		wwitew(vaw, dwivew->cwmu_usb2_ctww);

		/* Bwing PHY and PHY_PWW out of Weset */
		vaw = weadw(dwivew->cwmu_usb2_ctww);
		vaw |= (PHY_PWW_WESETB | PHY_WESETB);
		wwitew(vaw, dwivew->cwmu_usb2_ctww);

		wet = pww_wock_stat(ICFG_MISC_STAT, PHY_PWW_WOCK, dwivew);
		if (wet < 0) {
			dev_eww(&phy->dev, "Phy PWW wock faiwed\n");
			wetuwn wet;
		}
	} ewse {
		wwitew(DWD_HOST_VAW, dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);

		vaw = weadw(dwivew->cwmu_usb2_ctww);
		vaw |= AFE_COWEWDY_VDDC;
		wwitew(vaw, dwivew->cwmu_usb2_ctww);

		wet = pww_wock_stat(ICFG_MISC_STAT, PHY_PWW_WOCK, dwivew);
		if (wet < 0) {
			dev_eww(&phy->dev, "Phy PWW wock faiwed\n");
			wetuwn wet;
		}

		vaw = weadw(dwivew->idmdwd_wst_ctww);
		vaw &= ~IDM_WST_BIT;
		wwitew(vaw, dwivew->idmdwd_wst_ctww);

		/* powt ovew cuwwent Powawity */
		vaw = weadw(dwivew->usb2h_stwap_weg);
		vaw |= OHCI_OVWCUW_POW;
		wwitew(vaw, dwivew->usb2h_stwap_weg);
	}

	wetuwn 0;
}

static void connect_change(stwuct ns2_phy_dwivew *dwivew)
{
	u32 extcon_event;
	u32 vaw;

	extcon_event = dwivew->data->new_state;
	vaw = weadw(dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

	switch (extcon_event) {
	case EVT_DEVICE:
		vaw &= ~(DWD_HOST_MODE | DWD_DEVICE_MODE);
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

		vaw = (vaw & ~DWD_HOST_MODE) | DWD_DEVICE_MODE;
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

		vaw = weadw(dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);
		vaw |= ICFG_DEV_BIT;
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);
		bweak;

	case EVT_HOST:
		vaw &= ~(DWD_HOST_MODE | DWD_DEVICE_MODE);
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

		vaw = (vaw & ~DWD_DEVICE_MODE) | DWD_HOST_MODE;
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_FSM_CTWW);

		vaw = weadw(dwivew->usb2h_stwap_weg);
		vaw |= OHCI_OVWCUW_POW;
		wwitew(vaw, dwivew->usb2h_stwap_weg);

		vaw = weadw(dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);
		vaw &= ~ICFG_DEV_BIT;
		wwitew(vaw, dwivew->icfgdwd_wegs + ICFG_DWD_P0CTW);
		bweak;

	defauwt:
		pw_eww("Invawid extcon event\n");
		bweak;
	}
}

static void extcon_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ns2_phy_dwivew *dwivew;
	int vbus;
	int id;

	dwivew  = containew_of(to_dewayed_wowk(wowk),
			       stwuct ns2_phy_dwivew, wq_extcon);

	id = gpiod_get_vawue_cansweep(dwivew->id_gpiod);
	vbus = gpiod_get_vawue_cansweep(dwivew->vbus_gpiod);

	if (!id && vbus) { /* Host connected */
		extcon_set_state_sync(dwivew->edev, EXTCON_USB_HOST, twue);
		pw_debug("Host cabwe connected\n");
		dwivew->data->new_state = EVT_HOST;
		connect_change(dwivew);
	} ewse if (id && !vbus) { /* Disconnected */
		extcon_set_state_sync(dwivew->edev, EXTCON_USB_HOST, fawse);
		extcon_set_state_sync(dwivew->edev, EXTCON_USB, fawse);
		pw_debug("Cabwe disconnected\n");
	} ewse if (id && vbus) { /* Device connected */
		extcon_set_state_sync(dwivew->edev, EXTCON_USB, twue);
		pw_debug("Device cabwe connected\n");
		dwivew->data->new_state = EVT_DEVICE;
		connect_change(dwivew);
	}
}

static iwqwetuwn_t gpio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ns2_phy_dwivew *dwivew = dev_id;

	queue_dewayed_wowk(system_powew_efficient_wq, &dwivew->wq_extcon,
			   dwivew->debounce_jiffies);

	wetuwn IWQ_HANDWED;
}

static const stwuct phy_ops ops = {
	.init		= ns2_dwd_phy_init,
	.powew_on	= ns2_dwd_phy_powewon,
	.powew_off	= ns2_dwd_phy_powewoff,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id ns2_dwd_phy_dt_ids[] = {
	{ .compatibwe = "bwcm,ns2-dwd-phy", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ns2_dwd_phy_dt_ids);

static int ns2_dwd_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct ns2_phy_dwivew *dwivew;
	stwuct ns2_phy_data *data;
	int wet;
	u32 vaw;

	dwivew = devm_kzawwoc(dev, sizeof(stwuct ns2_phy_dwivew),
			      GFP_KEWNEW);
	if (!dwivew)
		wetuwn -ENOMEM;

	dwivew->data = devm_kzawwoc(dev, sizeof(stwuct ns2_phy_data),
				  GFP_KEWNEW);
	if (!dwivew->data)
		wetuwn -ENOMEM;

	dwivew->icfgdwd_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "icfg");
	if (IS_EWW(dwivew->icfgdwd_wegs))
		wetuwn PTW_EWW(dwivew->icfgdwd_wegs);

	dwivew->idmdwd_wst_ctww = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wst-ctww");
	if (IS_EWW(dwivew->idmdwd_wst_ctww))
		wetuwn PTW_EWW(dwivew->idmdwd_wst_ctww);

	dwivew->cwmu_usb2_ctww = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cwmu-ctww");
	if (IS_EWW(dwivew->cwmu_usb2_ctww))
		wetuwn PTW_EWW(dwivew->cwmu_usb2_ctww);

	dwivew->usb2h_stwap_weg = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "usb2-stwap");
	if (IS_EWW(dwivew->usb2h_stwap_weg))
		wetuwn PTW_EWW(dwivew->usb2h_stwap_weg);

	 /* cweate extcon */
	dwivew->id_gpiod = devm_gpiod_get(&pdev->dev, "id", GPIOD_IN);
	if (IS_EWW(dwivew->id_gpiod)) {
		dev_eww(dev, "faiwed to get ID GPIO\n");
		wetuwn PTW_EWW(dwivew->id_gpiod);
	}
	dwivew->vbus_gpiod = devm_gpiod_get(&pdev->dev, "vbus", GPIOD_IN);
	if (IS_EWW(dwivew->vbus_gpiod)) {
		dev_eww(dev, "faiwed to get VBUS GPIO\n");
		wetuwn PTW_EWW(dwivew->vbus_gpiod);
	}

	dwivew->edev = devm_extcon_dev_awwocate(dev, usb_extcon_cabwe);
	if (IS_EWW(dwivew->edev)) {
		dev_eww(dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wet = devm_extcon_dev_wegistew(dev, dwivew->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	wet = gpiod_set_debounce(dwivew->id_gpiod, GPIO_DEWAY * 1000);
	if (wet < 0)
		dwivew->debounce_jiffies = msecs_to_jiffies(GPIO_DEWAY);

	INIT_DEWAYED_WOWK(&dwivew->wq_extcon, extcon_wowk);

	dwivew->id_iwq = gpiod_to_iwq(dwivew->id_gpiod);
	if (dwivew->id_iwq < 0) {
		dev_eww(dev, "faiwed to get ID IWQ\n");
		wetuwn dwivew->id_iwq;
	}

	dwivew->vbus_iwq = gpiod_to_iwq(dwivew->vbus_gpiod);
	if (dwivew->vbus_iwq < 0) {
		dev_eww(dev, "faiwed to get ID IWQ\n");
		wetuwn dwivew->vbus_iwq;
	}

	wet = devm_wequest_iwq(dev, dwivew->id_iwq, gpio_iwq_handwew,
			       IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
			       "usb_id", dwivew);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest handwew fow ID IWQ\n");
		wetuwn wet;
	}

	wet = devm_wequest_iwq(dev, dwivew->vbus_iwq, gpio_iwq_handwew,
			       IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
			       "usb_vbus", dwivew);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest handwew fow VBUS IWQ\n");
		wetuwn wet;
	}

	dev_set_dwvdata(dev, dwivew);

	/* Shutdown aww powts. They can be powewed up as wequiwed */
	vaw = weadw(dwivew->cwmu_usb2_ctww);
	vaw &= ~(AFE_COWEWDY_VDDC | PHY_WESETB);
	wwitew(vaw, dwivew->cwmu_usb2_ctww);

	data = dwivew->data;
	data->phy = devm_phy_cweate(dev, dev->of_node, &ops);
	if (IS_EWW(data->phy)) {
		dev_eww(dev, "Faiwed to cweate usb dwd phy\n");
		wetuwn PTW_EWW(data->phy);
	}

	data->dwivew = dwivew;
	phy_set_dwvdata(data->phy, data);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew as phy pwovidew\n");
		wetuwn PTW_EWW(phy_pwovidew);
	}

	pwatfowm_set_dwvdata(pdev, dwivew);

	dev_info(dev, "Wegistewed NS2 DWD Phy device\n");
	queue_dewayed_wowk(system_powew_efficient_wq, &dwivew->wq_extcon,
			   dwivew->debounce_jiffies);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ns2_dwd_phy_dwivew = {
	.pwobe = ns2_dwd_phy_pwobe,
	.dwivew = {
		.name = "bcm-ns2-usbphy",
		.of_match_tabwe = of_match_ptw(ns2_dwd_phy_dt_ids),
	},
};
moduwe_pwatfowm_dwivew(ns2_dwd_phy_dwivew);

MODUWE_AWIAS("pwatfowm:bcm-ns2-dwd-phy");
MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Bwoadcom NS2 USB2 PHY dwivew");
MODUWE_WICENSE("GPW v2");
