// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/V2M USB3DWD dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/io.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/usb/wzv2m_usb3dwd.h>

#define USB_PEWI_DWD_CON	0x000

#define USB_PEWI_DWD_CON_PEWI_WST	BIT(31)
#define USB_PEWI_DWD_CON_HOST_WST	BIT(30)
#define USB_PEWI_DWD_CON_PEWI_CON	BIT(24)

static void wzv2m_usb3dwd_set_bit(stwuct wzv2m_usb3dwd *usb3, u32 bits,
				  u32 offs)
{
	u32 vaw = weadw(usb3->weg + offs);

	vaw |= bits;
	wwitew(vaw, usb3->weg + offs);
}

static void wzv2m_usb3dwd_cweaw_bit(stwuct wzv2m_usb3dwd *usb3, u32 bits,
				    u32 offs)
{
	u32 vaw = weadw(usb3->weg + offs);

	vaw &= ~bits;
	wwitew(vaw, usb3->weg + offs);
}

void wzv2m_usb3dwd_weset(stwuct device *dev, boow host)
{
	stwuct wzv2m_usb3dwd *usb3 = dev_get_dwvdata(dev);

	if (host) {
		wzv2m_usb3dwd_cweaw_bit(usb3, USB_PEWI_DWD_CON_PEWI_CON,
					USB_PEWI_DWD_CON);
		wzv2m_usb3dwd_cweaw_bit(usb3, USB_PEWI_DWD_CON_HOST_WST,
					USB_PEWI_DWD_CON);
		wzv2m_usb3dwd_set_bit(usb3, USB_PEWI_DWD_CON_PEWI_WST,
				      USB_PEWI_DWD_CON);
	} ewse {
		wzv2m_usb3dwd_set_bit(usb3, USB_PEWI_DWD_CON_PEWI_CON,
				      USB_PEWI_DWD_CON);
		wzv2m_usb3dwd_set_bit(usb3, USB_PEWI_DWD_CON_HOST_WST,
				      USB_PEWI_DWD_CON);
		wzv2m_usb3dwd_cweaw_bit(usb3, USB_PEWI_DWD_CON_PEWI_WST,
					USB_PEWI_DWD_CON);
	}
}
EXPOWT_SYMBOW_GPW(wzv2m_usb3dwd_weset);

static void wzv2m_usb3dwd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzv2m_usb3dwd *usb3 = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(usb3->dev);
	pm_wuntime_put(usb3->dev);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(usb3->dwd_wstc);
}

static int wzv2m_usb3dwd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wzv2m_usb3dwd *usb3;
	int wet;

	usb3 = devm_kzawwoc(&pdev->dev, sizeof(*usb3), GFP_KEWNEW);
	if (!usb3)
		wetuwn -ENOMEM;

	usb3->dev = &pdev->dev;

	usb3->dwd_iwq = pwatfowm_get_iwq_byname(pdev, "dwd");
	if (usb3->dwd_iwq < 0)
		wetuwn usb3->dwd_iwq;

	usb3->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(usb3->weg))
		wetuwn PTW_EWW(usb3->weg);

	pwatfowm_set_dwvdata(pdev, usb3);

	usb3->dwd_wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(usb3->dwd_wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(usb3->dwd_wstc),
				     "faiwed to get dwd weset");

	weset_contwow_deassewt(usb3->dwd_wstc);
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(usb3->dev);
	if (wet)
		goto eww_wst;

	wet = of_pwatfowm_popuwate(usb3->dev->of_node, NUWW, NUWW, usb3->dev);
	if (wet)
		goto eww_pm;

	wetuwn 0;

eww_pm:
	pm_wuntime_put(usb3->dev);

eww_wst:
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(usb3->dwd_wstc);
	wetuwn wet;
}

static const stwuct of_device_id wzv2m_usb3dwd_of_match[] = {
	{ .compatibwe = "wenesas,wzv2m-usb3dwd", },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzv2m_usb3dwd_of_match);

static stwuct pwatfowm_dwivew wzv2m_usb3dwd_dwivew = {
	.dwivew = {
		.name = "wzv2m-usb3dwd",
		.of_match_tabwe = wzv2m_usb3dwd_of_match,
	},
	.pwobe = wzv2m_usb3dwd_pwobe,
	.wemove_new = wzv2m_usb3dwd_wemove,
};
moduwe_pwatfowm_dwivew(wzv2m_usb3dwd_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/V2M USB3DWD dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wzv2m_usb3dwd");
