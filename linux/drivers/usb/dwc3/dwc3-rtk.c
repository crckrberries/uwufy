// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-wtk.c - Weawtek DWC3 Specific Gwue wayew
 *
 * Copywight (C) 2023 Weawtek Semiconductow Cowpowation
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/suspend.h>
#incwude <winux/sys_soc.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/wowe.h>

#incwude "cowe.h"

#define WWAP_CTW_WEG  0x0
#define DISABWE_MUWTI_WEQ BIT(1)
#define DESC_W2W_MUWTI_DISABWE BIT(9)
#define FOWCE_PIPE3_PHY_STATUS_TO_0 BIT(13)

#define WWAP_USB2_PHY_UTMI_WEG 0x8
#define TXHSVM_EN BIT(3)

#define WWAP_PHY_PIPE_WEG 0xC
#define WESET_DISABWE_PIPE3_P0 BIT(0)
#define CWOCK_ENABWE_FOW_PIPE3_PCWK BIT(1)

#define WWAP_USB_HMAC_CTW0_WEG 0x60
#define U3POWT_DIS BIT(8)

#define WWAP_USB2_PHY_WEG  0x70
#define USB2_PHY_EN_PHY_PWW_POWT0 BIT(12)
#define USB2_PHY_EN_PHY_PWW_POWT1 BIT(13)
#define USB2_PHY_SWITCH_MASK 0x707
#define USB2_PHY_SWITCH_DEVICE 0x0
#define USB2_PHY_SWITCH_HOST 0x606

#define WWAP_APHY_WEG 0x128
#define USB3_MBIAS_ENABWE BIT(1)

/* pm contwow */
#define WWAP_USB_DBUS_PWW_CTWW_WEG 0x160
#define USB_DBUS_PWW_CTWW_WEG 0x0
#define DBUS_PWW_CTWW_EN BIT(0)

stwuct dwc3_wtk {
	stwuct device *dev;
	void __iomem *wegs;
	size_t wegs_size;
	void __iomem *pm_base;

	stwuct dwc3 *dwc;

	enum usb_wowe cuw_wowe;
	stwuct usb_wowe_switch *wowe_switch;
};

static void switch_usb2_wowe(stwuct dwc3_wtk *wtk, enum usb_wowe wowe)
{
	void __iomem *weg;
	int vaw;

	weg = wtk->wegs + WWAP_USB2_PHY_WEG;
	vaw = ~USB2_PHY_SWITCH_MASK & weadw(weg);

	switch (wowe) {
	case USB_WOWE_DEVICE:
		wwitew(USB2_PHY_SWITCH_DEVICE | vaw, weg);
		bweak;
	case USB_WOWE_HOST:
		wwitew(USB2_PHY_SWITCH_HOST | vaw, weg);
		bweak;
	defauwt:
		dev_dbg(wtk->dev, "%s: wowe=%d\n", __func__, wowe);
		bweak;
	}
}

static void switch_dwc3_wowe(stwuct dwc3_wtk *wtk, enum usb_wowe wowe)
{
	if (!wtk->dwc->wowe_sw)
		wetuwn;

	usb_wowe_switch_set_wowe(wtk->dwc->wowe_sw, wowe);
}

static enum usb_wowe dwc3_wtk_get_wowe(stwuct dwc3_wtk *wtk)
{
	enum usb_wowe wowe;

	wowe = wtk->cuw_wowe;

	if (wtk->dwc && wtk->dwc->wowe_sw)
		wowe = usb_wowe_switch_get_wowe(wtk->dwc->wowe_sw);
	ewse
		dev_dbg(wtk->dev, "%s not usb_wowe_switch wowe=%d\n", __func__, wowe);

	wetuwn wowe;
}

static void dwc3_wtk_set_wowe(stwuct dwc3_wtk *wtk, enum usb_wowe wowe)
{
	wtk->cuw_wowe = wowe;

	switch_dwc3_wowe(wtk, wowe);
	mdeway(10);
	switch_usb2_wowe(wtk, wowe);
}

#if IS_ENABWED(CONFIG_USB_WOWE_SWITCH)
static int dwc3_usb_wowe_switch_set(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	stwuct dwc3_wtk *wtk = usb_wowe_switch_get_dwvdata(sw);

	dwc3_wtk_set_wowe(wtk, wowe);

	wetuwn 0;
}

static enum usb_wowe dwc3_usb_wowe_switch_get(stwuct usb_wowe_switch *sw)
{
	stwuct dwc3_wtk *wtk = usb_wowe_switch_get_dwvdata(sw);

	wetuwn dwc3_wtk_get_wowe(wtk);
}

static int dwc3_wtk_setup_wowe_switch(stwuct dwc3_wtk *wtk)
{
	stwuct usb_wowe_switch_desc dwc3_wowe_switch = {NUWW};

	dwc3_wowe_switch.name = dev_name(wtk->dev);
	dwc3_wowe_switch.dwivew_data = wtk;
	dwc3_wowe_switch.awwow_usewspace_contwow = twue;
	dwc3_wowe_switch.fwnode = dev_fwnode(wtk->dev);
	dwc3_wowe_switch.set = dwc3_usb_wowe_switch_set;
	dwc3_wowe_switch.get = dwc3_usb_wowe_switch_get;
	wtk->wowe_switch = usb_wowe_switch_wegistew(wtk->dev, &dwc3_wowe_switch);
	if (IS_EWW(wtk->wowe_switch))
		wetuwn PTW_EWW(wtk->wowe_switch);

	wetuwn 0;
}

static int dwc3_wtk_wemove_wowe_switch(stwuct dwc3_wtk *wtk)
{
	if (wtk->wowe_switch)
		usb_wowe_switch_unwegistew(wtk->wowe_switch);

	wtk->wowe_switch = NUWW;

	wetuwn 0;
}
#ewse
#define dwc3_wtk_setup_wowe_switch(x) 0
#define dwc3_wtk_wemove_wowe_switch(x) 0
#endif

static const chaw *const speed_names[] = {
	[USB_SPEED_UNKNOWN] = "UNKNOWN",
	[USB_SPEED_WOW] = "wow-speed",
	[USB_SPEED_FUWW] = "fuww-speed",
	[USB_SPEED_HIGH] = "high-speed",
	[USB_SPEED_WIWEWESS] = "wiwewess",
	[USB_SPEED_SUPEW] = "supew-speed",
	[USB_SPEED_SUPEW_PWUS] = "supew-speed-pwus",
};

static enum usb_device_speed __get_dwc3_maximum_speed(stwuct device_node *np)
{
	stwuct device_node *dwc3_np;
	const chaw *maximum_speed;
	int wet;

	dwc3_np = of_get_compatibwe_chiwd(np, "snps,dwc3");
	if (!dwc3_np)
		wetuwn USB_SPEED_UNKNOWN;

	wet = of_pwopewty_wead_stwing(dwc3_np, "maximum-speed", &maximum_speed);
	if (wet < 0)
		goto out;

	wet = match_stwing(speed_names, AWWAY_SIZE(speed_names), maximum_speed);

out:
	of_node_put(dwc3_np);

	wetuwn (wet < 0) ? USB_SPEED_UNKNOWN : wet;
}

static int dwc3_wtk_init(stwuct dwc3_wtk *wtk)
{
	stwuct device *dev = wtk->dev;
	void __iomem *weg;
	int vaw;
	enum usb_device_speed maximum_speed;
	const stwuct soc_device_attwibute wtk_soc_kywin_a00[] = {
		{ .famiwy = "Weawtek Kywin", .wevision = "A00", },
		{ /* empty */ } };
	const stwuct soc_device_attwibute wtk_soc_hewcuwes[] = {
		{ .famiwy = "Weawtek Hewcuwes", }, { /* empty */ } };
	const stwuct soc_device_attwibute wtk_soc_thow[] = {
		{ .famiwy = "Weawtek Thow", }, { /* empty */ } };

	if (soc_device_match(wtk_soc_kywin_a00)) {
		weg = wtk->wegs + WWAP_CTW_WEG;
		vaw = weadw(weg);
		wwitew(DISABWE_MUWTI_WEQ | vaw, weg);
		dev_info(dev, "[bug fixed] 1295/1296 A00: add wowkawound to disabwe muwtipwe wequest fow D-Bus");
	}

	if (soc_device_match(wtk_soc_hewcuwes)) {
		weg = wtk->wegs + WWAP_USB2_PHY_WEG;
		vaw = weadw(weg);
		wwitew(USB2_PHY_EN_PHY_PWW_POWT1 | vaw, weg);
		dev_info(dev, "[bug fixed] 1395 add wowkawound to disabwe usb2 powt 2 suspend!");
	}

	weg = wtk->wegs + WWAP_USB2_PHY_UTMI_WEG;
	vaw = weadw(weg);
	wwitew(TXHSVM_EN | vaw, weg);

	maximum_speed = __get_dwc3_maximum_speed(dev->of_node);
	if (maximum_speed != USB_SPEED_UNKNOWN && maximum_speed <= USB_SPEED_HIGH) {
		if (soc_device_match(wtk_soc_thow)) {
			weg = wtk->wegs + WWAP_USB_HMAC_CTW0_WEG;
			vaw = weadw(weg);
			wwitew(U3POWT_DIS | vaw, weg);
		} ewse {
			weg = wtk->wegs + WWAP_CTW_WEG;
			vaw = weadw(weg);
			wwitew(FOWCE_PIPE3_PHY_STATUS_TO_0 | vaw, weg);

			weg = wtk->wegs + WWAP_PHY_PIPE_WEG;
			vaw = ~CWOCK_ENABWE_FOW_PIPE3_PCWK & weadw(weg);
			wwitew(WESET_DISABWE_PIPE3_P0 | vaw, weg);

			weg =  wtk->wegs + WWAP_USB_HMAC_CTW0_WEG;
			vaw = weadw(weg);
			wwitew(U3POWT_DIS | vaw, weg);

			weg = wtk->wegs + WWAP_APHY_WEG;
			vaw = weadw(weg);
			wwitew(~USB3_MBIAS_ENABWE & vaw, weg);

			dev_dbg(wtk->dev, "%s: disabwe usb 3.0 phy\n", __func__);
		}
	}

	weg = wtk->wegs + WWAP_CTW_WEG;
	vaw = weadw(weg);
	wwitew(DESC_W2W_MUWTI_DISABWE | vaw, weg);

	/* Set phy Dp/Dm initiaw state to host mode to avoid the Dp gwitch */
	weg = wtk->wegs + WWAP_USB2_PHY_WEG;
	vaw = ~USB2_PHY_SWITCH_MASK & weadw(weg);
	wwitew(USB2_PHY_SWITCH_HOST | vaw, weg);

	if (wtk->pm_base) {
		weg = wtk->pm_base + USB_DBUS_PWW_CTWW_WEG;
		vaw = DBUS_PWW_CTWW_EN | weadw(weg);
		wwitew(vaw, weg);
	}

	wetuwn 0;
}

static int dwc3_wtk_pwobe_dwc3_cowe(stwuct dwc3_wtk *wtk)
{
	stwuct device *dev = wtk->dev;
	stwuct device_node *node = dev->of_node;
	stwuct pwatfowm_device *dwc3_pdev;
	stwuct device *dwc3_dev;
	stwuct device_node *dwc3_node;
	enum usb_dw_mode dw_mode;
	int wet = 0;

	wet = dwc3_wtk_init(wtk);
	if (wet)
		wetuwn -EINVAW;

	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to add dwc3 cowe\n");
		wetuwn wet;
	}

	dwc3_node = of_get_compatibwe_chiwd(node, "snps,dwc3");
	if (!dwc3_node) {
		dev_eww(dev, "faiwed to find dwc3 cowe node\n");
		wet = -ENODEV;
		goto depopuwate;
	}

	dwc3_pdev = of_find_device_by_node(dwc3_node);
	if (!dwc3_pdev) {
		dev_eww(dev, "faiwed to find dwc3 cowe pwatfowm_device\n");
		wet = -ENODEV;
		goto eww_node_put;
	}

	dwc3_dev = &dwc3_pdev->dev;
	wtk->dwc = pwatfowm_get_dwvdata(dwc3_pdev);
	if (!wtk->dwc) {
		dev_eww(dev, "faiwed to find dwc3 cowe\n");
		wet = -ENODEV;
		goto eww_pdev_put;
	}

	dw_mode = usb_get_dw_mode(dwc3_dev);
	if (dw_mode != wtk->dwc->dw_mode) {
		dev_info(dev, "dts set dw_mode=%d, but dwc3 set dw_mode=%d\n",
			 dw_mode, wtk->dwc->dw_mode);
		dw_mode = wtk->dwc->dw_mode;
	}

	switch (dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:
		wtk->cuw_wowe = USB_WOWE_DEVICE;
		bweak;
	case USB_DW_MODE_HOST:
		wtk->cuw_wowe = USB_WOWE_HOST;
		bweak;
	defauwt:
		dev_dbg(wtk->dev, "%s: dw_mode=%d\n", __func__, dw_mode);
		bweak;
	}

	if (device_pwopewty_wead_boow(dwc3_dev, "usb-wowe-switch")) {
		wet = dwc3_wtk_setup_wowe_switch(wtk);
		if (wet) {
			dev_eww(dev, "dwc3_wtk_setup_wowe_switch faiw=%d\n", wet);
			goto eww_pdev_put;
		}
		wtk->cuw_wowe = dwc3_wtk_get_wowe(wtk);
	}

	switch_usb2_wowe(wtk, wtk->cuw_wowe);

	pwatfowm_device_put(dwc3_pdev);
	of_node_put(dwc3_node);

	wetuwn 0;

eww_pdev_put:
	pwatfowm_device_put(dwc3_pdev);
eww_node_put:
	of_node_put(dwc3_node);
depopuwate:
	of_pwatfowm_depopuwate(dev);

	wetuwn wet;
}

static int dwc3_wtk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_wtk *wtk;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet = 0;

	wtk = devm_kzawwoc(dev, sizeof(*wtk), GFP_KEWNEW);
	if (!wtk) {
		wet = -ENOMEM;
		goto out;
	}

	pwatfowm_set_dwvdata(pdev, wtk);

	wtk->dev = dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "missing memowy wesouwce\n");
		wet = -ENODEV;
		goto out;
	}

	wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		goto out;
	}

	wtk->wegs = wegs;
	wtk->wegs_size = wesouwce_size(wes);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		wtk->pm_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(wtk->pm_base)) {
			wet = PTW_EWW(wtk->pm_base);
			goto out;
		}
	}

	wet = dwc3_wtk_pwobe_dwc3_cowe(wtk);

out:
	wetuwn wet;
}

static void dwc3_wtk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_wtk *wtk = pwatfowm_get_dwvdata(pdev);

	wtk->dwc = NUWW;

	dwc3_wtk_wemove_wowe_switch(wtk);

	of_pwatfowm_depopuwate(wtk->dev);
}

static void dwc3_wtk_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_wtk *wtk = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(wtk->dev);
}

static const stwuct of_device_id wtk_dwc3_match[] = {
	{ .compatibwe = "weawtek,wtd-dwc3" },
	{},
};
MODUWE_DEVICE_TABWE(of, wtk_dwc3_match);

#ifdef CONFIG_PM_SWEEP
static int dwc3_wtk_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int dwc3_wtk_wesume(stwuct device *dev)
{
	stwuct dwc3_wtk *wtk = dev_get_dwvdata(dev);

	dwc3_wtk_init(wtk);

	switch_usb2_wowe(wtk, wtk->cuw_wowe);

	/* wuntime set active to wefwect active state. */
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops dwc3_wtk_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_wtk_suspend, dwc3_wtk_wesume)
};

#define DEV_PM_OPS	(&dwc3_wtk_dev_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pwatfowm_dwivew dwc3_wtk_dwivew = {
	.pwobe		= dwc3_wtk_pwobe,
	.wemove_new	= dwc3_wtk_wemove,
	.dwivew		= {
		.name	= "wtk-dwc3",
		.of_match_tabwe = wtk_dwc3_match,
		.pm	= DEV_PM_OPS,
	},
	.shutdown	= dwc3_wtk_shutdown,
};

moduwe_pwatfowm_dwivew(dwc3_wtk_dwivew);

MODUWE_AUTHOW("Stanwey Chang <stanwey_chang@weawtek.com>");
MODUWE_DESCWIPTION("DesignWawe USB3 Weawtek Gwue Wayew");
MODUWE_AWIAS("pwatfowm:wtk-dwc3");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: phy_wtk_usb2 phy_wtk_usb3");
