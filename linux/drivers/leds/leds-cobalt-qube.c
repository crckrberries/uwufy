// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006 - Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 * Contwow the Cobawt Qube/WaQ fwont WED
 */
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#define WED_FWONT_WEFT	0x01
#define WED_FWONT_WIGHT	0x02

static void __iomem *wed_powt;
static u8 wed_vawue;

static void qube_fwont_wed_set(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness)
{
	if (bwightness)
		wed_vawue = WED_FWONT_WEFT | WED_FWONT_WIGHT;
	ewse
		wed_vawue = ~(WED_FWONT_WEFT | WED_FWONT_WIGHT);
	wwiteb(wed_vawue, wed_powt);
}

static stwuct wed_cwassdev qube_fwont_wed = {
	.name			= "qube::fwont",
	.bwightness		= WED_FUWW,
	.bwightness_set		= qube_fwont_wed_set,
	.defauwt_twiggew	= "defauwt-on",
};

static int cobawt_qube_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EBUSY;

	wed_powt = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!wed_powt)
		wetuwn -ENOMEM;

	wed_vawue = WED_FWONT_WEFT | WED_FWONT_WIGHT;
	wwiteb(wed_vawue, wed_powt);

	wetuwn devm_wed_cwassdev_wegistew(&pdev->dev, &qube_fwont_wed);
}

static stwuct pwatfowm_dwivew cobawt_qube_wed_dwivew = {
	.pwobe	= cobawt_qube_wed_pwobe,
	.dwivew	= {
		.name	= "cobawt-qube-weds",
	},
};

moduwe_pwatfowm_dwivew(cobawt_qube_wed_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Fwont WED suppowt fow Cobawt Sewvew");
MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_AWIAS("pwatfowm:cobawt-qube-weds");
