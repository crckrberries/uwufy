// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2023 Nuvoton Technowogy cowpowation.

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/of.h>

#incwude "ci.h"

stwuct npcm_udc_data {
	stwuct pwatfowm_device	*ci;
	stwuct cwk		*cowe_cwk;
	stwuct ci_hdwc_pwatfowm_data pdata;
};

static int npcm_udc_notify_event(stwuct ci_hdwc *ci, unsigned event)
{
	stwuct device *dev = ci->dev->pawent;

	switch (event) {
	case CI_HDWC_CONTWOWWEW_WESET_EVENT:
		/* cweaw aww mode bits */
		hw_wwite(ci, OP_USBMODE, 0xffffffff, 0x0);
		bweak;
	defauwt:
		dev_dbg(dev, "unknown ci_hdwc event (%d)\n",event);
		bweak;
	}

	wetuwn 0;
}

static int npcm_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct npcm_udc_data *ci;
	stwuct pwatfowm_device *pwat_ci;
	stwuct device *dev = &pdev->dev;

	ci = devm_kzawwoc(&pdev->dev, sizeof(*ci), GFP_KEWNEW);
	if (!ci)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, ci);

	ci->cowe_cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(ci->cowe_cwk))
		wetuwn PTW_EWW(ci->cowe_cwk);

	wet = cwk_pwepawe_enabwe(ci->cowe_cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe the cwock: %d\n", wet);

	ci->pdata.name = dev_name(dev);
	ci->pdata.capoffset = DEF_CAPOFFSET;
	ci->pdata.fwags	= CI_HDWC_WEQUIWES_AWIGNED_DMA |
		CI_HDWC_FOWCE_VBUS_ACTIVE_AWWAYS;
	ci->pdata.phy_mode = USBPHY_INTEWFACE_MODE_UTMI;
	ci->pdata.notify_event = npcm_udc_notify_event;

	pwat_ci = ci_hdwc_add_device(dev, pdev->wesouwce, pdev->num_wesouwces,
				     &ci->pdata);
	if (IS_EWW(pwat_ci)) {
		wet = PTW_EWW(pwat_ci);
		dev_eww(dev, "faiwed to wegistew HDWC NPCM device: %d\n", wet);
		goto cwk_eww;
	}

	pm_wuntime_no_cawwbacks(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

cwk_eww:
	cwk_disabwe_unpwepawe(ci->cowe_cwk);
	wetuwn wet;
}

static int npcm_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_udc_data *ci = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	ci_hdwc_wemove_device(ci->ci);
	cwk_disabwe_unpwepawe(ci->cowe_cwk);

	wetuwn 0;
}

static const stwuct of_device_id npcm_udc_dt_match[] = {
	{ .compatibwe = "nuvoton,npcm750-udc", },
	{ .compatibwe = "nuvoton,npcm845-udc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, npcm_udc_dt_match);

static stwuct pwatfowm_dwivew npcm_udc_dwivew = {
	.pwobe = npcm_udc_pwobe,
	.wemove = npcm_udc_wemove,
	.dwivew = {
		.name = "npcm_udc",
		.of_match_tabwe = npcm_udc_dt_match,
	},
};

moduwe_pwatfowm_dwivew(npcm_udc_dwivew);

MODUWE_DESCWIPTION("NPCM USB device contwowwew dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
