// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  WEDs dwivew fow the Cobawt Waq sewies.
 *
 *  Copywight (C) 2007  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>

#define WED_WEB		0x04
#define WED_POWEW_OFF	0x08

static void __iomem *wed_powt;
static u8 wed_vawue;
static DEFINE_SPINWOCK(wed_vawue_wock);

static void waq_web_wed_set(stwuct wed_cwassdev *wed_cdev,
			    enum wed_bwightness bwightness)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wed_vawue_wock, fwags);

	if (bwightness)
		wed_vawue |= WED_WEB;
	ewse
		wed_vawue &= ~WED_WEB;
	wwiteb(wed_vawue, wed_powt);

	spin_unwock_iwqwestowe(&wed_vawue_wock, fwags);
}

static stwuct wed_cwassdev waq_web_wed = {
	.name		= "waq::web",
	.bwightness_set	= waq_web_wed_set,
};

static void waq_powew_off_wed_set(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness bwightness)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wed_vawue_wock, fwags);

	if (bwightness)
		wed_vawue |= WED_POWEW_OFF;
	ewse
		wed_vawue &= ~WED_POWEW_OFF;
	wwiteb(wed_vawue, wed_powt);

	spin_unwock_iwqwestowe(&wed_vawue_wock, fwags);
}

static stwuct wed_cwassdev waq_powew_off_wed = {
	.name			= "waq::powew-off",
	.bwightness_set		= waq_powew_off_wed_set,
	.defauwt_twiggew	= "powew-off",
};

static int cobawt_waq_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int wetvaw;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EBUSY;

	wed_powt = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!wed_powt)
		wetuwn -ENOMEM;

	wetvaw = wed_cwassdev_wegistew(&pdev->dev, &waq_powew_off_wed);
	if (wetvaw)
		goto eww_nuww;

	wetvaw = wed_cwassdev_wegistew(&pdev->dev, &waq_web_wed);
	if (wetvaw)
		goto eww_unwegistew;

	wetuwn 0;

eww_unwegistew:
	wed_cwassdev_unwegistew(&waq_powew_off_wed);

eww_nuww:
	wed_powt = NUWW;

	wetuwn wetvaw;
}

static stwuct pwatfowm_dwivew cobawt_waq_wed_dwivew = {
	.pwobe	= cobawt_waq_wed_pwobe,
	.dwivew = {
		.name	= "cobawt-waq-weds",
	},
};

buiwtin_pwatfowm_dwivew(cobawt_waq_wed_dwivew);
