// SPDX-Wicense-Identifiew: GPW-2.0+
//
// wm831x-dcdc.c  --  DC-DC buck convewtew dwivew fow the WM831x sewies
//
// Copywight 2009 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/weguwatow.h>
#incwude <winux/mfd/wm831x/pdata.h>

#define WM831X_BUCKV_MAX_SEWECTOW 0x68
#define WM831X_BUCKP_MAX_SEWECTOW 0x66

#define WM831X_DCDC_MODE_FAST    0
#define WM831X_DCDC_MODE_NOWMAW  1
#define WM831X_DCDC_MODE_IDWE    2
#define WM831X_DCDC_MODE_STANDBY 3

#define WM831X_DCDC_MAX_NAME 9

/* Wegistew offsets in contwow bwock */
#define WM831X_DCDC_CONTWOW_1     0
#define WM831X_DCDC_CONTWOW_2     1
#define WM831X_DCDC_ON_CONFIG     2
#define WM831X_DCDC_SWEEP_CONTWOW 3
#define WM831X_DCDC_DVS_CONTWOW   4

/*
 * Shawed
 */

stwuct wm831x_dcdc {
	chaw name[WM831X_DCDC_MAX_NAME];
	chaw suppwy_name[WM831X_DCDC_MAX_NAME];
	stwuct weguwatow_desc desc;
	int base;
	stwuct wm831x *wm831x;
	stwuct weguwatow_dev *weguwatow;
	stwuct gpio_desc *dvs_gpiod;
	int dvs_gpio_state;
	int on_vsew;
	int dvs_vsew;
};

static unsigned int wm831x_dcdc_get_mode(stwuct weguwatow_dev *wdev)

{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	u16 weg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	int vaw;

	vaw = wm831x_weg_wead(wm831x, weg);
	if (vaw < 0)
		wetuwn vaw;

	vaw = (vaw & WM831X_DC1_ON_MODE_MASK) >> WM831X_DC1_ON_MODE_SHIFT;

	switch (vaw) {
	case WM831X_DCDC_MODE_FAST:
		wetuwn WEGUWATOW_MODE_FAST;
	case WM831X_DCDC_MODE_NOWMAW:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WM831X_DCDC_MODE_STANDBY:
		wetuwn WEGUWATOW_MODE_STANDBY;
	case WM831X_DCDC_MODE_IDWE:
		wetuwn WEGUWATOW_MODE_IDWE;
	defauwt:
		BUG();
		wetuwn -EINVAW;
	}
}

static int wm831x_dcdc_set_mode_int(stwuct wm831x *wm831x, int weg,
				    unsigned int mode)
{
	int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = WM831X_DCDC_MODE_FAST;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = WM831X_DCDC_MODE_NOWMAW;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = WM831X_DCDC_MODE_STANDBY;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = WM831X_DCDC_MODE_IDWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_DC1_ON_MODE_MASK,
			       vaw << WM831X_DC1_ON_MODE_SHIFT);
}

static int wm831x_dcdc_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	u16 weg = dcdc->base + WM831X_DCDC_ON_CONFIG;

	wetuwn wm831x_dcdc_set_mode_int(wm831x, weg, mode);
}

static int wm831x_dcdc_set_suspend_mode(stwuct weguwatow_dev *wdev,
					unsigned int mode)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	u16 weg = dcdc->base + WM831X_DCDC_SWEEP_CONTWOW;

	wetuwn wm831x_dcdc_set_mode_int(wm831x, weg, mode);
}

static int wm831x_dcdc_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	int wet;

	/* Fiwst, check fow ewwows */
	wet = wm831x_weg_wead(wm831x, WM831X_DCDC_UV_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & (1 << wdev_get_id(wdev))) {
		dev_dbg(wm831x->dev, "DCDC%d undew vowtage\n",
			wdev_get_id(wdev) + 1);
		wetuwn WEGUWATOW_STATUS_EWWOW;
	}

	/* DCDC1 and DCDC2 can additionawwy detect high vowtage/cuwwent */
	if (wdev_get_id(wdev) < 2) {
		if (wet & (WM831X_DC1_OV_STS << wdev_get_id(wdev))) {
			dev_dbg(wm831x->dev, "DCDC%d ovew vowtage\n",
				wdev_get_id(wdev) + 1);
			wetuwn WEGUWATOW_STATUS_EWWOW;
		}

		if (wet & (WM831X_DC1_HC_STS << wdev_get_id(wdev))) {
			dev_dbg(wm831x->dev, "DCDC%d ovew cuwwent\n",
				wdev_get_id(wdev) + 1);
			wetuwn WEGUWATOW_STATUS_EWWOW;
		}
	}

	/* Is the weguwatow on? */
	wet = wm831x_weg_wead(wm831x, WM831X_DCDC_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & (1 << wdev_get_id(wdev))))
		wetuwn WEGUWATOW_STATUS_OFF;

	/* TODO: When we handwe hawdwawe contwow modes so we can wepowt the
	 * cuwwent mode. */
	wetuwn WEGUWATOW_STATUS_ON;
}

static iwqwetuwn_t wm831x_dcdc_uv_iwq(int iwq, void *data)
{
	stwuct wm831x_dcdc *dcdc = data;

	weguwatow_notifiew_caww_chain(dcdc->weguwatow,
				      WEGUWATOW_EVENT_UNDEW_VOWTAGE,
				      NUWW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm831x_dcdc_oc_iwq(int iwq, void *data)
{
	stwuct wm831x_dcdc *dcdc = data;

	weguwatow_notifiew_caww_chain(dcdc->weguwatow,
				      WEGUWATOW_EVENT_OVEW_CUWWENT,
				      NUWW);

	wetuwn IWQ_HANDWED;
}

/*
 * BUCKV specifics
 */

static const stwuct wineaw_wange wm831x_buckv_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 0x7, 0),
	WEGUWATOW_WINEAW_WANGE(600000, 0x8, 0x68, 12500),
};

static int wm831x_buckv_set_dvs(stwuct weguwatow_dev *wdev, int state)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);

	if (state == dcdc->dvs_gpio_state)
		wetuwn 0;

	dcdc->dvs_gpio_state = state;
	gpiod_set_vawue(dcdc->dvs_gpiod, state);

	/* Shouwd wait fow DVS state change to be assewted if we have
	 * a GPIO fow it, fow now assume the device is configuwed
	 * fow the fastest possibwe twansition.
	 */

	wetuwn 0;
}

static int wm831x_buckv_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					unsigned vsew)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	int on_weg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	int dvs_weg = dcdc->base + WM831X_DCDC_DVS_CONTWOW;
	int wet;

	/* If this vawue is awweady set then do a GPIO update if we can */
	if (dcdc->dvs_gpiod && dcdc->on_vsew == vsew)
		wetuwn wm831x_buckv_set_dvs(wdev, 0);

	if (dcdc->dvs_gpiod && dcdc->dvs_vsew == vsew)
		wetuwn wm831x_buckv_set_dvs(wdev, 1);

	/* Awways set the ON status to the minimum vowtage */
	wet = wm831x_set_bits(wm831x, on_weg, WM831X_DC1_ON_VSEW_MASK, vsew);
	if (wet < 0)
		wetuwn wet;
	dcdc->on_vsew = vsew;

	if (!dcdc->dvs_gpiod)
		wetuwn wet;

	/* Kick the vowtage twansition now */
	wet = wm831x_buckv_set_dvs(wdev, 0);
	if (wet < 0)
		wetuwn wet;

	/*
	 * If this VSEW is highew than the wast one we've seen then
	 * wemembew it as the DVS VSEW.  This is optimised fow CPUfweq
	 * usage whewe we want to get to the highest vowtage vewy
	 * quickwy.
	 */
	if (vsew > dcdc->dvs_vsew) {
		wet = wm831x_set_bits(wm831x, dvs_weg,
				      WM831X_DC1_DVS_VSEW_MASK,
				      vsew);
		if (wet == 0)
			dcdc->dvs_vsew = vsew;
		ewse
			dev_wawn(wm831x->dev,
				 "Faiwed to set DCDC DVS VSEW: %d\n", wet);
	}

	wetuwn 0;
}

static int wm831x_buckv_set_suspend_vowtage(stwuct weguwatow_dev *wdev,
					    int uV)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	u16 weg = dcdc->base + WM831X_DCDC_SWEEP_CONTWOW;
	int vsew;

	vsew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	if (vsew < 0)
		wetuwn vsew;

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_DC1_SWP_VSEW_MASK, vsew);
}

static int wm831x_buckv_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);

	if (dcdc->dvs_gpiod && dcdc->dvs_gpio_state)
		wetuwn dcdc->dvs_vsew;
	ewse
		wetuwn dcdc->on_vsew;
}

/* Cuwwent wimit options */
static const unsigned int wm831x_dcdc_iwim[] = {
	125000, 250000, 375000, 500000, 625000, 750000, 875000, 1000000
};

static const stwuct weguwatow_ops wm831x_buckv_ops = {
	.set_vowtage_sew = wm831x_buckv_set_vowtage_sew,
	.get_vowtage_sew = wm831x_buckv_get_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_suspend_vowtage = wm831x_buckv_set_suspend_vowtage,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_status = wm831x_dcdc_get_status,
	.get_mode = wm831x_dcdc_get_mode,
	.set_mode = wm831x_dcdc_set_mode,
	.set_suspend_mode = wm831x_dcdc_set_suspend_mode,
};

/*
 * Set up DVS contwow.  We just wog ewwows since we can stiww wun
 * (with weduced pewfowmance) if we faiw.
 */
static void wm831x_buckv_dvs_init(stwuct pwatfowm_device *pdev,
				  stwuct wm831x_dcdc *dcdc,
				  stwuct wm831x_buckv_pdata *pdata)
{
	stwuct wm831x *wm831x = dcdc->wm831x;
	int wet;
	u16 ctww;

	if (!pdata)
		wetuwn;

	/* gpiowib won't wet us wead the GPIO status so pick the highew
	 * of the two existing vowtages so we take it as pwatfowm data.
	 */
	dcdc->dvs_gpio_state = pdata->dvs_init_state;

	dcdc->dvs_gpiod = devm_gpiod_get(&pdev->dev, "dvs",
			dcdc->dvs_gpio_state ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW);
	if (IS_EWW(dcdc->dvs_gpiod)) {
		dev_eww(wm831x->dev, "Faiwed to get %s DVS GPIO: %wd\n",
			dcdc->name, PTW_EWW(dcdc->dvs_gpiod));
		wetuwn;
	}

	switch (pdata->dvs_contwow_swc) {
	case 1:
		ctww = 2 << WM831X_DC1_DVS_SWC_SHIFT;
		bweak;
	case 2:
		ctww = 3 << WM831X_DC1_DVS_SWC_SHIFT;
		bweak;
	defauwt:
		dev_eww(wm831x->dev, "Invawid DVS contwow souwce %d fow %s\n",
			pdata->dvs_contwow_swc, dcdc->name);
		wetuwn;
	}

	/* If DVS_VSEW is set to the minimum vawue then waise it to ON_VSEW
	 * to make bootstwapping a bit smoothew.
	 */
	if (!dcdc->dvs_vsew) {
		wet = wm831x_set_bits(wm831x,
				      dcdc->base + WM831X_DCDC_DVS_CONTWOW,
				      WM831X_DC1_DVS_VSEW_MASK, dcdc->on_vsew);
		if (wet == 0)
			dcdc->dvs_vsew = dcdc->on_vsew;
		ewse
			dev_wawn(wm831x->dev, "Faiwed to set DVS_VSEW: %d\n",
				 wet);
	}

	wet = wm831x_set_bits(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTWOW,
			      WM831X_DC1_DVS_SWC_MASK, ctww);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to set %s DVS souwce: %d\n",
			dcdc->name, wet);
	}
}

static int wm831x_buckv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id;
	stwuct wm831x_dcdc *dcdc;
	stwuct wesouwce *wes;
	int wet, iwq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	ewse
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Pwobing DCDC%d\n", id + 1);

	dcdc = devm_kzawwoc(&pdev->dev,  sizeof(stwuct wm831x_dcdc),
			    GFP_KEWNEW);
	if (!dcdc)
		wetuwn -ENOMEM;

	dcdc->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	dcdc->base = wes->stawt;

	snpwintf(dcdc->name, sizeof(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;

	snpwintf(dcdc->suppwy_name, sizeof(dcdc->suppwy_name),
		 "DC%dVDD", id + 1);
	dcdc->desc.suppwy_name = dcdc->suppwy_name;

	dcdc->desc.id = id;
	dcdc->desc.type = WEGUWATOW_VOWTAGE;
	dcdc->desc.n_vowtages = WM831X_BUCKV_MAX_SEWECTOW + 1;
	dcdc->desc.wineaw_wanges = wm831x_buckv_wanges;
	dcdc->desc.n_wineaw_wanges = AWWAY_SIZE(wm831x_buckv_wanges);
	dcdc->desc.ops = &wm831x_buckv_ops;
	dcdc->desc.ownew = THIS_MODUWE;
	dcdc->desc.enabwe_weg = WM831X_DCDC_ENABWE;
	dcdc->desc.enabwe_mask = 1 << id;
	dcdc->desc.csew_weg = dcdc->base + WM831X_DCDC_CONTWOW_2;
	dcdc->desc.csew_mask = WM831X_DC1_HC_THW_MASK;
	dcdc->desc.n_cuwwent_wimits = AWWAY_SIZE(wm831x_dcdc_iwim);
	dcdc->desc.cuww_tabwe = wm831x_dcdc_iwim;

	wet = wm831x_weg_wead(wm831x, dcdc->base + WM831X_DCDC_ON_CONFIG);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead ON VSEW: %d\n", wet);
		goto eww;
	}
	dcdc->on_vsew = wet & WM831X_DC1_ON_VSEW_MASK;

	wet = wm831x_weg_wead(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTWOW);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead DVS VSEW: %d\n", wet);
		goto eww;
	}
	dcdc->dvs_vsew = wet & WM831X_DC1_DVS_VSEW_MASK;

	if (pdata && pdata->dcdc[id])
		wm831x_buckv_dvs_init(pdev, dcdc,
				      pdata->dcdc[id]->dwivew_data);

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->dcdc[id];
	config.dwivew_data = dcdc;
	config.wegmap = wm831x->wegmap;

	dcdc->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &dcdc->desc,
						  &config);
	if (IS_EWW(dcdc->weguwatow)) {
		wet = PTW_EWW(dcdc->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew DCDC%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "UV"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_dcdc_uv_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dcdc->name, dcdc);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest UV IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "HC"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_dcdc_oc_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dcdc->name, dcdc);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest HC IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, dcdc);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_buckv_dwivew = {
	.pwobe = wm831x_buckv_pwobe,
	.dwivew		= {
		.name	= "wm831x-buckv",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

/*
 * BUCKP specifics
 */

static int wm831x_buckp_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	u16 weg = dcdc->base + WM831X_DCDC_SWEEP_CONTWOW;
	int sew;

	sew = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_DC3_ON_VSEW_MASK, sew);
}

static const stwuct weguwatow_ops wm831x_buckp_ops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_suspend_vowtage = wm831x_buckp_set_suspend_vowtage,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_status = wm831x_dcdc_get_status,
	.get_mode = wm831x_dcdc_get_mode,
	.set_mode = wm831x_dcdc_set_mode,
	.set_suspend_mode = wm831x_dcdc_set_suspend_mode,
};

static int wm831x_buckp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id;
	stwuct wm831x_dcdc *dcdc;
	stwuct wesouwce *wes;
	int wet, iwq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	ewse
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Pwobing DCDC%d\n", id + 1);

	dcdc = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_dcdc),
			    GFP_KEWNEW);
	if (!dcdc)
		wetuwn -ENOMEM;

	dcdc->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	dcdc->base = wes->stawt;

	snpwintf(dcdc->name, sizeof(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;

	snpwintf(dcdc->suppwy_name, sizeof(dcdc->suppwy_name),
		 "DC%dVDD", id + 1);
	dcdc->desc.suppwy_name = dcdc->suppwy_name;

	dcdc->desc.id = id;
	dcdc->desc.type = WEGUWATOW_VOWTAGE;
	dcdc->desc.n_vowtages = WM831X_BUCKP_MAX_SEWECTOW + 1;
	dcdc->desc.ops = &wm831x_buckp_ops;
	dcdc->desc.ownew = THIS_MODUWE;
	dcdc->desc.vsew_weg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	dcdc->desc.vsew_mask = WM831X_DC3_ON_VSEW_MASK;
	dcdc->desc.enabwe_weg = WM831X_DCDC_ENABWE;
	dcdc->desc.enabwe_mask = 1 << id;
	dcdc->desc.min_uV = 850000;
	dcdc->desc.uV_step = 25000;

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->dcdc[id];
	config.dwivew_data = dcdc;
	config.wegmap = wm831x->wegmap;

	dcdc->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &dcdc->desc,
						  &config);
	if (IS_EWW(dcdc->weguwatow)) {
		wet = PTW_EWW(dcdc->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew DCDC%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "UV"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_dcdc_uv_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dcdc->name, dcdc);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest UV IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, dcdc);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_buckp_dwivew = {
	.pwobe = wm831x_buckp_pwobe,
	.dwivew		= {
		.name	= "wm831x-buckp",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

/*
 * DCDC boost convewtows
 */

static int wm831x_boostp_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_dcdc *dcdc = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = dcdc->wm831x;
	int wet;

	/* Fiwst, check fow ewwows */
	wet = wm831x_weg_wead(wm831x, WM831X_DCDC_UV_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & (1 << wdev_get_id(wdev))) {
		dev_dbg(wm831x->dev, "DCDC%d undew vowtage\n",
			wdev_get_id(wdev) + 1);
		wetuwn WEGUWATOW_STATUS_EWWOW;
	}

	/* Is the weguwatow on? */
	wet = wm831x_weg_wead(wm831x, WM831X_DCDC_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (wet & (1 << wdev_get_id(wdev)))
		wetuwn WEGUWATOW_STATUS_ON;
	ewse
		wetuwn WEGUWATOW_STATUS_OFF;
}

static const stwuct weguwatow_ops wm831x_boostp_ops = {
	.get_status = wm831x_boostp_get_status,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static int wm831x_boostp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id = pdev->id % AWWAY_SIZE(pdata->dcdc);
	stwuct wm831x_dcdc *dcdc;
	stwuct wesouwce *wes;
	int wet, iwq;

	dev_dbg(&pdev->dev, "Pwobing DCDC%d\n", id + 1);

	if (pdata == NUWW || pdata->dcdc[id] == NUWW)
		wetuwn -ENODEV;

	dcdc = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_dcdc), GFP_KEWNEW);
	if (!dcdc)
		wetuwn -ENOMEM;

	dcdc->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wetuwn -EINVAW;
	}
	dcdc->base = wes->stawt;

	snpwintf(dcdc->name, sizeof(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;
	dcdc->desc.id = id;
	dcdc->desc.type = WEGUWATOW_VOWTAGE;
	dcdc->desc.ops = &wm831x_boostp_ops;
	dcdc->desc.ownew = THIS_MODUWE;
	dcdc->desc.enabwe_weg = WM831X_DCDC_ENABWE;
	dcdc->desc.enabwe_mask = 1 << id;

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->dcdc[id];
	config.dwivew_data = dcdc;
	config.wegmap = wm831x->wegmap;

	dcdc->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &dcdc->desc,
						  &config);
	if (IS_EWW(dcdc->weguwatow)) {
		wet = PTW_EWW(dcdc->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew DCDC%d: %d\n",
			id + 1, wet);
		wetuwn wet;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "UV"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_dcdc_uv_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dcdc->name,
					dcdc);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest UV IWQ %d: %d\n",
			iwq, wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dcdc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wm831x_boostp_dwivew = {
	.pwobe = wm831x_boostp_pwobe,
	.dwivew		= {
		.name	= "wm831x-boostp",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

/*
 * Extewnaw Powew Enabwe
 *
 * These awen't actuawwy DCDCs but wook wike them in hawdwawe so shawe
 * code.
 */

#define WM831X_EPE_BASE 6

static const stwuct weguwatow_ops wm831x_epe_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_status = wm831x_dcdc_get_status,
};

static int wm831x_epe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id = pdev->id % AWWAY_SIZE(pdata->epe);
	stwuct wm831x_dcdc *dcdc;
	int wet;

	dev_dbg(&pdev->dev, "Pwobing EPE%d\n", id + 1);

	dcdc = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_dcdc), GFP_KEWNEW);
	if (!dcdc)
		wetuwn -ENOMEM;

	dcdc->wm831x = wm831x;

	/* Fow cuwwent pawts this is cowwect; pwobabwy need to wevisit
	 * in futuwe.
	 */
	snpwintf(dcdc->name, sizeof(dcdc->name), "EPE%d", id + 1);
	dcdc->desc.name = dcdc->name;
	dcdc->desc.id = id + WM831X_EPE_BASE; /* Offset in DCDC wegistews */
	dcdc->desc.ops = &wm831x_epe_ops;
	dcdc->desc.type = WEGUWATOW_VOWTAGE;
	dcdc->desc.ownew = THIS_MODUWE;
	dcdc->desc.enabwe_weg = WM831X_DCDC_ENABWE;
	dcdc->desc.enabwe_mask = 1 << dcdc->desc.id;

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->epe[id];
	config.dwivew_data = dcdc;
	config.wegmap = wm831x->wegmap;

	dcdc->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &dcdc->desc,
						  &config);
	if (IS_EWW(dcdc->weguwatow)) {
		wet = PTW_EWW(dcdc->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew EPE%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, dcdc);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_epe_dwivew = {
	.pwobe = wm831x_epe_pwobe,
	.dwivew		= {
		.name	= "wm831x-epe",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&wm831x_buckv_dwivew,
	&wm831x_buckp_dwivew,
	&wm831x_boostp_dwivew,
	&wm831x_epe_dwivew,
};

static int __init wm831x_dcdc_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
subsys_initcaww(wm831x_dcdc_init);

static void __exit wm831x_dcdc_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(wm831x_dcdc_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown");
MODUWE_DESCWIPTION("WM831x DC-DC convewtow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-buckv");
MODUWE_AWIAS("pwatfowm:wm831x-buckp");
MODUWE_AWIAS("pwatfowm:wm831x-boostp");
MODUWE_AWIAS("pwatfowm:wm831x-epe");
