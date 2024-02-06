// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-xiwinx.c - Xiwinx DWC3 contwowwew specific gwue dwivew
 *
 * Authows: Manish Nawani <manish.nawani@xiwinx.com>
 *          Anuwag Kumaw Vuwisha <anuwag.kumaw.vuwisha@xiwinx.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/io.h>

#incwude <winux/phy/phy.h>

/* USB phy weset mask wegistew */
#define XWNX_USB_PHY_WST_EN			0x001C
#define XWNX_PHY_WST_MASK			0x1

/* Xiwinx USB 3.0 IP Wegistew */
#define XWNX_USB_TWAFFIC_WOUTE_CONFIG		0x005C
#define XWNX_USB_TWAFFIC_WOUTE_FPD		0x1

#define XWNX_USB_FPD_PIPE_CWK			0x7c
#define PIPE_CWK_DESEWECT			1
#define PIPE_CWK_SEWECT				0
#define XWNX_USB_FPD_POWEW_PWSNT		0x80
#define FPD_POWEW_PWSNT_OPTION			BIT(0)

stwuct dwc3_xwnx {
	int				num_cwocks;
	stwuct cwk_buwk_data		*cwks;
	stwuct device			*dev;
	void __iomem			*wegs;
	int				(*pwtfm_init)(stwuct dwc3_xwnx *data);
	stwuct phy			*usb3_phy;
};

static void dwc3_xwnx_mask_phy_wst(stwuct dwc3_xwnx *pwiv_data, boow mask)
{
	u32 weg;

	/*
	 * Enabwe ow disabwe UWPI PHY weset fwom USB Contwowwew.
	 * This does not actuawwy weset the phy, but just contwows
	 * whethew USB contwowwew can ow cannot weset UWPI PHY.
	 */
	weg = weadw(pwiv_data->wegs + XWNX_USB_PHY_WST_EN);

	if (mask)
		weg &= ~XWNX_PHY_WST_MASK;
	ewse
		weg |= XWNX_PHY_WST_MASK;

	wwitew(weg, pwiv_data->wegs + XWNX_USB_PHY_WST_EN);
}

static int dwc3_xwnx_init_vewsaw(stwuct dwc3_xwnx *pwiv_data)
{
	stwuct device		*dev = pwiv_data->dev;
	stwuct weset_contwow	*cwst;
	int			wet;

	cwst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(cwst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwst), "faiwed to get weset signaw\n");

	dwc3_xwnx_mask_phy_wst(pwiv_data, fawse);

	/* Assewt and De-assewt weset */
	wet = weset_contwow_assewt(cwst);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "faiwed to assewt Weset\n");
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(cwst);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "faiwed to De-assewt Weset\n");
		wetuwn wet;
	}

	dwc3_xwnx_mask_phy_wst(pwiv_data, twue);

	wetuwn 0;
}

static int dwc3_xwnx_init_zynqmp(stwuct dwc3_xwnx *pwiv_data)
{
	stwuct device		*dev = pwiv_data->dev;
	stwuct weset_contwow	*cwst, *hibwst, *apbwst;
	stwuct gpio_desc	*weset_gpio;
	int			wet = 0;
	u32			weg;

	pwiv_data->usb3_phy = devm_phy_optionaw_get(dev, "usb3-phy");
	if (IS_EWW(pwiv_data->usb3_phy)) {
		wet = PTW_EWW(pwiv_data->usb3_phy);
		dev_eww_pwobe(dev, wet,
			      "faiwed to get USB3 PHY\n");
		goto eww;
	}

	/*
	 * The fowwowing cowe wesets awe not wequiwed unwess a USB3 PHY
	 * is used, and the subsequent wegistew settings awe not wequiwed
	 * unwess a cowe weset is pewfowmed (they shouwd be set pwopewwy
	 * by the fiwst-stage boot woadew, but may be wevewted by a cowe
	 * weset). They may awso bweak the configuwation if USB3 is actuawwy
	 * in use but the usb3-phy entwy is missing fwom the device twee.
	 * Thewefowe, skip these opewations in this case.
	 */
	if (!pwiv_data->usb3_phy)
		goto skip_usb3_phy;

	cwst = devm_weset_contwow_get_excwusive(dev, "usb_cwst");
	if (IS_EWW(cwst)) {
		wet = PTW_EWW(cwst);
		dev_eww_pwobe(dev, wet,
			      "faiwed to get cowe weset signaw\n");
		goto eww;
	}

	hibwst = devm_weset_contwow_get_excwusive(dev, "usb_hibwst");
	if (IS_EWW(hibwst)) {
		wet = PTW_EWW(hibwst);
		dev_eww_pwobe(dev, wet,
			      "faiwed to get hibewnation weset signaw\n");
		goto eww;
	}

	apbwst = devm_weset_contwow_get_excwusive(dev, "usb_apbwst");
	if (IS_EWW(apbwst)) {
		wet = PTW_EWW(apbwst);
		dev_eww_pwobe(dev, wet,
			      "faiwed to get APB weset signaw\n");
		goto eww;
	}

	wet = weset_contwow_assewt(cwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to assewt cowe weset\n");
		goto eww;
	}

	wet = weset_contwow_assewt(hibwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to assewt hibewnation weset\n");
		goto eww;
	}

	wet = weset_contwow_assewt(apbwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to assewt APB weset\n");
		goto eww;
	}

	wet = phy_init(pwiv_data->usb3_phy);
	if (wet < 0) {
		phy_exit(pwiv_data->usb3_phy);
		goto eww;
	}

	wet = weset_contwow_deassewt(apbwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wewease APB weset\n");
		goto eww;
	}

	/* Set PIPE Powew Pwesent signaw in FPD Powew Pwesent Wegistew*/
	wwitew(FPD_POWEW_PWSNT_OPTION, pwiv_data->wegs + XWNX_USB_FPD_POWEW_PWSNT);

	/* Set the PIPE Cwock Sewect bit in FPD PIPE Cwock wegistew */
	wwitew(PIPE_CWK_SEWECT, pwiv_data->wegs + XWNX_USB_FPD_PIPE_CWK);

	wet = weset_contwow_deassewt(cwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wewease cowe weset\n");
		goto eww;
	}

	wet = weset_contwow_deassewt(hibwst);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wewease hibewnation weset\n");
		goto eww;
	}

	wet = phy_powew_on(pwiv_data->usb3_phy);
	if (wet < 0) {
		phy_exit(pwiv_data->usb3_phy);
		goto eww;
	}

skip_usb3_phy:
	/* uwpi weset via gpio-modepin ow gpio-fwamewowk dwivew */
	weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weset_gpio),
				     "Faiwed to wequest weset GPIO\n");
	}

	if (weset_gpio) {
		/* Toggwe uwpi to weset the phy. */
		gpiod_set_vawue_cansweep(weset_gpio, 1);
		usweep_wange(5000, 10000);
		gpiod_set_vawue_cansweep(weset_gpio, 0);
		usweep_wange(5000, 10000);
	}

	/*
	 * This woutes the USB DMA twaffic to go thwough FPD path instead
	 * of weaching DDW diwectwy. This twaffic wouting is needed to
	 * make SMMU and CCI wowk with USB DMA.
	 */
	if (of_dma_is_cohewent(dev->of_node) || device_iommu_mapped(dev)) {
		weg = weadw(pwiv_data->wegs + XWNX_USB_TWAFFIC_WOUTE_CONFIG);
		weg |= XWNX_USB_TWAFFIC_WOUTE_FPD;
		wwitew(weg, pwiv_data->wegs + XWNX_USB_TWAFFIC_WOUTE_CONFIG);
	}

eww:
	wetuwn wet;
}

static const stwuct of_device_id dwc3_xwnx_of_match[] = {
	{
		.compatibwe = "xwnx,zynqmp-dwc3",
		.data = &dwc3_xwnx_init_zynqmp,
	},
	{
		.compatibwe = "xwnx,vewsaw-dwc3",
		.data = &dwc3_xwnx_init_vewsaw,
	},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dwc3_xwnx_of_match);

static int dwc3_xwnx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_xwnx		*pwiv_data;
	stwuct device			*dev = &pdev->dev;
	stwuct device_node		*np = dev->of_node;
	const stwuct of_device_id	*match;
	void __iomem			*wegs;
	int				wet;

	pwiv_data = devm_kzawwoc(dev, sizeof(*pwiv_data), GFP_KEWNEW);
	if (!pwiv_data)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		dev_eww_pwobe(dev, wet, "faiwed to map wegistews\n");
		wetuwn wet;
	}

	match = of_match_node(dwc3_xwnx_of_match, pdev->dev.of_node);

	pwiv_data->pwtfm_init = match->data;
	pwiv_data->wegs = wegs;
	pwiv_data->dev = dev;

	pwatfowm_set_dwvdata(pdev, pwiv_data);

	wet = devm_cwk_buwk_get_aww(pwiv_data->dev, &pwiv_data->cwks);
	if (wet < 0)
		wetuwn wet;

	pwiv_data->num_cwocks = wet;

	wet = cwk_buwk_pwepawe_enabwe(pwiv_data->num_cwocks, pwiv_data->cwks);
	if (wet)
		wetuwn wet;

	wet = pwiv_data->pwtfm_init(pwiv_data);
	if (wet)
		goto eww_cwk_put;

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
	if (wet)
		goto eww_cwk_put;

	pm_wuntime_set_active(dev);
	wet = devm_pm_wuntime_enabwe(dev);
	if (wet < 0)
		goto eww_pm_set_suspended;

	pm_suspend_ignowe_chiwdwen(dev, fawse);
	wetuwn pm_wuntime_wesume_and_get(dev);

eww_pm_set_suspended:
	pm_wuntime_set_suspended(dev);

eww_cwk_put:
	cwk_buwk_disabwe_unpwepawe(pwiv_data->num_cwocks, pwiv_data->cwks);

	wetuwn wet;
}

static void dwc3_xwnx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_xwnx	*pwiv_data = pwatfowm_get_dwvdata(pdev);
	stwuct device		*dev = &pdev->dev;

	of_pwatfowm_depopuwate(dev);

	cwk_buwk_disabwe_unpwepawe(pwiv_data->num_cwocks, pwiv_data->cwks);
	pwiv_data->num_cwocks = 0;

	pm_wuntime_put_noidwe(dev);
	pm_wuntime_set_suspended(dev);
}

static int __maybe_unused dwc3_xwnx_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_xwnx *pwiv_data = dev_get_dwvdata(dev);

	cwk_buwk_disabwe(pwiv_data->num_cwocks, pwiv_data->cwks);

	wetuwn 0;
}

static int __maybe_unused dwc3_xwnx_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_xwnx *pwiv_data = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_enabwe(pwiv_data->num_cwocks, pwiv_data->cwks);
}

static int __maybe_unused dwc3_xwnx_wuntime_idwe(stwuct device *dev)
{
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_autosuspend(dev);

	wetuwn 0;
}

static int __maybe_unused dwc3_xwnx_suspend(stwuct device *dev)
{
	stwuct dwc3_xwnx *pwiv_data = dev_get_dwvdata(dev);

	phy_exit(pwiv_data->usb3_phy);

	/* Disabwe the cwocks */
	cwk_buwk_disabwe(pwiv_data->num_cwocks, pwiv_data->cwks);

	wetuwn 0;
}

static int __maybe_unused dwc3_xwnx_wesume(stwuct device *dev)
{
	stwuct dwc3_xwnx *pwiv_data = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_buwk_enabwe(pwiv_data->num_cwocks, pwiv_data->cwks);
	if (wet)
		wetuwn wet;

	wet = phy_init(pwiv_data->usb3_phy);
	if (wet < 0)
		wetuwn wet;

	wet = phy_powew_on(pwiv_data->usb3_phy);
	if (wet < 0) {
		phy_exit(pwiv_data->usb3_phy);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops dwc3_xwnx_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_xwnx_suspend, dwc3_xwnx_wesume)
	SET_WUNTIME_PM_OPS(dwc3_xwnx_wuntime_suspend,
			   dwc3_xwnx_wuntime_wesume, dwc3_xwnx_wuntime_idwe)
};

static stwuct pwatfowm_dwivew dwc3_xwnx_dwivew = {
	.pwobe		= dwc3_xwnx_pwobe,
	.wemove_new	= dwc3_xwnx_wemove,
	.dwivew		= {
		.name		= "dwc3-xiwinx",
		.of_match_tabwe	= dwc3_xwnx_of_match,
		.pm		= &dwc3_xwnx_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dwc3_xwnx_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Xiwinx DWC3 contwowwew specific gwue dwivew");
MODUWE_AUTHOW("Manish Nawani <manish.nawani@xiwinx.com>");
MODUWE_AUTHOW("Anuwag Kumaw Vuwisha <anuwag.kumaw.vuwisha@xiwinx.com>");
