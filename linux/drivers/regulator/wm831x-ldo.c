// SPDX-Wicense-Identifiew: GPW-2.0+
//
// wm831x-wdo.c  --  WDO dwivew fow the WM831x sewies
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
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/weguwatow.h>
#incwude <winux/mfd/wm831x/pdata.h>

#define WM831X_WDO_MAX_NAME 9

#define WM831X_WDO_CONTWOW       0
#define WM831X_WDO_ON_CONTWOW    1
#define WM831X_WDO_SWEEP_CONTWOW 2

#define WM831X_AWIVE_WDO_ON_CONTWOW    0
#define WM831X_AWIVE_WDO_SWEEP_CONTWOW 1

stwuct wm831x_wdo {
	chaw name[WM831X_WDO_MAX_NAME];
	chaw suppwy_name[WM831X_WDO_MAX_NAME];
	stwuct weguwatow_desc desc;
	int base;
	stwuct wm831x *wm831x;
	stwuct weguwatow_dev *weguwatow;
};

/*
 * Shawed
 */

static iwqwetuwn_t wm831x_wdo_uv_iwq(int iwq, void *data)
{
	stwuct wm831x_wdo *wdo = data;

	weguwatow_notifiew_caww_chain(wdo->weguwatow,
				      WEGUWATOW_EVENT_UNDEW_VOWTAGE,
				      NUWW);

	wetuwn IWQ_HANDWED;
}

/*
 * Genewaw puwpose WDOs
 */

static const stwuct wineaw_wange wm831x_gp_wdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0, 14, 50000),
	WEGUWATOW_WINEAW_WANGE(1700000, 15, 31, 100000),
};

static int wm831x_gp_wdo_set_suspend_vowtage(stwuct weguwatow_dev *wdev,
					     int uV)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int sew, weg = wdo->base + WM831X_WDO_SWEEP_CONTWOW;

	sew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_WDO1_ON_VSEW_MASK, sew);
}

static unsigned int wm831x_gp_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int ctww_weg = wdo->base + WM831X_WDO_CONTWOW;
	int on_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	int wet;

	wet = wm831x_weg_wead(wm831x, on_weg);
	if (wet < 0)
		wetuwn wet;

	if (!(wet & WM831X_WDO1_ON_MODE))
		wetuwn WEGUWATOW_MODE_NOWMAW;

	wet = wm831x_weg_wead(wm831x, ctww_weg);
	if (wet < 0)
		wetuwn wet;

	if (wet & WM831X_WDO1_WP_MODE)
		wetuwn WEGUWATOW_MODE_STANDBY;
	ewse
		wetuwn WEGUWATOW_MODE_IDWE;
}

static int wm831x_gp_wdo_set_mode(stwuct weguwatow_dev *wdev,
				  unsigned int mode)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int ctww_weg = wdo->base + WM831X_WDO_CONTWOW;
	int on_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	int wet;


	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		wet = wm831x_set_bits(wm831x, on_weg,
				      WM831X_WDO1_ON_MODE, 0);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case WEGUWATOW_MODE_IDWE:
		wet = wm831x_set_bits(wm831x, ctww_weg,
				      WM831X_WDO1_WP_MODE, 0);
		if (wet < 0)
			wetuwn wet;

		wet = wm831x_set_bits(wm831x, on_weg,
				      WM831X_WDO1_ON_MODE,
				      WM831X_WDO1_ON_MODE);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case WEGUWATOW_MODE_STANDBY:
		wet = wm831x_set_bits(wm831x, ctww_weg,
				      WM831X_WDO1_WP_MODE,
				      WM831X_WDO1_WP_MODE);
		if (wet < 0)
			wetuwn wet;

		wet = wm831x_set_bits(wm831x, on_weg,
				      WM831X_WDO1_ON_MODE,
				      WM831X_WDO1_ON_MODE);
		if (wet < 0)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm831x_gp_wdo_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int mask = 1 << wdev_get_id(wdev);
	int wet;

	/* Is the weguwatow on? */
	wet = wm831x_weg_wead(wm831x, WM831X_WDO_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & mask))
		wetuwn WEGUWATOW_STATUS_OFF;

	/* Is it wepowting undew vowtage? */
	wet = wm831x_weg_wead(wm831x, WM831X_WDO_UV_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (wet & mask)
		wetuwn WEGUWATOW_STATUS_EWWOW;

	wet = wm831x_gp_wdo_get_mode(wdev);
	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn weguwatow_mode_to_status(wet);
}

static unsigned int wm831x_gp_wdo_get_optimum_mode(stwuct weguwatow_dev *wdev,
						   int input_uV,
						   int output_uV, int woad_uA)
{
	if (woad_uA < 20000)
		wetuwn WEGUWATOW_MODE_STANDBY;
	if (woad_uA < 50000)
		wetuwn WEGUWATOW_MODE_IDWE;
	wetuwn WEGUWATOW_MODE_NOWMAW;
}


static const stwuct weguwatow_ops wm831x_gp_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_suspend_vowtage = wm831x_gp_wdo_set_suspend_vowtage,
	.get_mode = wm831x_gp_wdo_get_mode,
	.set_mode = wm831x_gp_wdo_set_mode,
	.get_status = wm831x_gp_wdo_get_status,
	.get_optimum_mode = wm831x_gp_wdo_get_optimum_mode,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = weguwatow_set_bypass_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static int wm831x_gp_wdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id;
	stwuct wm831x_wdo *wdo;
	stwuct wesouwce *wes;
	int wet, iwq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	ewse
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Pwobing WDO%d\n", id + 1);

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	wdo->base = wes->stawt;

	snpwintf(wdo->name, sizeof(wdo->name), "WDO%d", id + 1);
	wdo->desc.name = wdo->name;

	snpwintf(wdo->suppwy_name, sizeof(wdo->suppwy_name),
		 "WDO%dVDD", id + 1);
	wdo->desc.suppwy_name = wdo->suppwy_name;

	wdo->desc.id = id;
	wdo->desc.type = WEGUWATOW_VOWTAGE;
	wdo->desc.n_vowtages = 32;
	wdo->desc.ops = &wm831x_gp_wdo_ops;
	wdo->desc.ownew = THIS_MODUWE;
	wdo->desc.vsew_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	wdo->desc.vsew_mask = WM831X_WDO1_ON_VSEW_MASK;
	wdo->desc.enabwe_weg = WM831X_WDO_ENABWE;
	wdo->desc.enabwe_mask = 1 << id;
	wdo->desc.bypass_weg = wdo->base;
	wdo->desc.bypass_mask = WM831X_WDO1_SWI;
	wdo->desc.wineaw_wanges = wm831x_gp_wdo_wanges;
	wdo->desc.n_wineaw_wanges = AWWAY_SIZE(wm831x_gp_wdo_wanges);

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->wdo[id];
	config.dwivew_data = wdo;
	config.wegmap = wm831x->wegmap;

	wdo->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &wdo->desc,
						 &config);
	if (IS_EWW(wdo->weguwatow)) {
		wet = PTW_EWW(wdo->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew WDO%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "UV"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_wdo_uv_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					wdo->name,
					wdo);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest UV IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_gp_wdo_dwivew = {
	.pwobe = wm831x_gp_wdo_pwobe,
	.dwivew		= {
		.name	= "wm831x-wdo",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

/*
 * Anawogue WDOs
 */

static const stwuct wineaw_wange wm831x_awdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 12, 50000),
	WEGUWATOW_WINEAW_WANGE(1700000, 13, 31, 100000),
};

static int wm831x_awdo_set_suspend_vowtage(stwuct weguwatow_dev *wdev,
					     int uV)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int sew, weg = wdo->base + WM831X_WDO_SWEEP_CONTWOW;

	sew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_WDO7_ON_VSEW_MASK, sew);
}

static unsigned int wm831x_awdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int on_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	int wet;

	wet = wm831x_weg_wead(wm831x, on_weg);
	if (wet < 0)
		wetuwn 0;

	if (wet & WM831X_WDO7_ON_MODE)
		wetuwn WEGUWATOW_MODE_IDWE;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wm831x_awdo_set_mode(stwuct weguwatow_dev *wdev,
				  unsigned int mode)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int on_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	int wet;


	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		wet = wm831x_set_bits(wm831x, on_weg, WM831X_WDO7_ON_MODE, 0);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case WEGUWATOW_MODE_IDWE:
		wet = wm831x_set_bits(wm831x, on_weg, WM831X_WDO7_ON_MODE,
				      WM831X_WDO7_ON_MODE);
		if (wet < 0)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm831x_awdo_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int mask = 1 << wdev_get_id(wdev);
	int wet;

	/* Is the weguwatow on? */
	wet = wm831x_weg_wead(wm831x, WM831X_WDO_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & mask))
		wetuwn WEGUWATOW_STATUS_OFF;

	/* Is it wepowting undew vowtage? */
	wet = wm831x_weg_wead(wm831x, WM831X_WDO_UV_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (wet & mask)
		wetuwn WEGUWATOW_STATUS_EWWOW;

	wet = wm831x_awdo_get_mode(wdev);
	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn weguwatow_mode_to_status(wet);
}

static const stwuct weguwatow_ops wm831x_awdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_suspend_vowtage = wm831x_awdo_set_suspend_vowtage,
	.get_mode = wm831x_awdo_get_mode,
	.set_mode = wm831x_awdo_set_mode,
	.get_status = wm831x_awdo_get_status,
	.set_bypass = weguwatow_set_bypass_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static int wm831x_awdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id;
	stwuct wm831x_wdo *wdo;
	stwuct wesouwce *wes;
	int wet, iwq;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	ewse
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Pwobing WDO%d\n", id + 1);

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	wdo->base = wes->stawt;

	snpwintf(wdo->name, sizeof(wdo->name), "WDO%d", id + 1);
	wdo->desc.name = wdo->name;

	snpwintf(wdo->suppwy_name, sizeof(wdo->suppwy_name),
		 "WDO%dVDD", id + 1);
	wdo->desc.suppwy_name = wdo->suppwy_name;

	wdo->desc.id = id;
	wdo->desc.type = WEGUWATOW_VOWTAGE;
	wdo->desc.n_vowtages = 32;
	wdo->desc.wineaw_wanges = wm831x_awdo_wanges;
	wdo->desc.n_wineaw_wanges = AWWAY_SIZE(wm831x_awdo_wanges);
	wdo->desc.ops = &wm831x_awdo_ops;
	wdo->desc.ownew = THIS_MODUWE;
	wdo->desc.vsew_weg = wdo->base + WM831X_WDO_ON_CONTWOW;
	wdo->desc.vsew_mask = WM831X_WDO7_ON_VSEW_MASK;
	wdo->desc.enabwe_weg = WM831X_WDO_ENABWE;
	wdo->desc.enabwe_mask = 1 << id;
	wdo->desc.bypass_weg = wdo->base;
	wdo->desc.bypass_mask = WM831X_WDO7_SWI;

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->wdo[id];
	config.dwivew_data = wdo;
	config.wegmap = wm831x->wegmap;

	wdo->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &wdo->desc,
						 &config);
	if (IS_EWW(wdo->weguwatow)) {
		wet = PTW_EWW(wdo->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew WDO%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "UV"));
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					wm831x_wdo_uv_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					wdo->name, wdo);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest UV IWQ %d: %d\n",
			iwq, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_awdo_dwivew = {
	.pwobe = wm831x_awdo_pwobe,
	.dwivew		= {
		.name	= "wm831x-awdo",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

/*
 * Awive WDO
 */

#define WM831X_AWIVE_WDO_MAX_SEWECTOW 0xf

static int wm831x_awive_wdo_set_suspend_vowtage(stwuct weguwatow_dev *wdev,
					     int uV)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int sew, weg = wdo->base + WM831X_AWIVE_WDO_SWEEP_CONTWOW;

	sew = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	wetuwn wm831x_set_bits(wm831x, weg, WM831X_WDO11_ON_VSEW_MASK, sew);
}

static int wm831x_awive_wdo_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct wm831x_wdo *wdo = wdev_get_dwvdata(wdev);
	stwuct wm831x *wm831x = wdo->wm831x;
	int mask = 1 << wdev_get_id(wdev);
	int wet;

	/* Is the weguwatow on? */
	wet = wm831x_weg_wead(wm831x, WM831X_WDO_STATUS);
	if (wet < 0)
		wetuwn wet;
	if (wet & mask)
		wetuwn WEGUWATOW_STATUS_ON;
	ewse
		wetuwn WEGUWATOW_STATUS_OFF;
}

static const stwuct weguwatow_ops wm831x_awive_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_suspend_vowtage = wm831x_awive_wdo_set_suspend_vowtage,
	.get_status = wm831x_awive_wdo_get_status,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static int wm831x_awive_wdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(wm831x->dev);
	stwuct weguwatow_config config = { };
	int id;
	stwuct wm831x_wdo *wdo;
	stwuct wesouwce *wes;
	int wet;

	if (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	ewse
		id = 0;
	id = pdev->id - id;


	dev_dbg(&pdev->dev, "Pwobing WDO%d\n", id + 1);

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wm831x = wm831x;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "No WEG wesouwce\n");
		wet = -EINVAW;
		goto eww;
	}
	wdo->base = wes->stawt;

	snpwintf(wdo->name, sizeof(wdo->name), "WDO%d", id + 1);
	wdo->desc.name = wdo->name;

	snpwintf(wdo->suppwy_name, sizeof(wdo->suppwy_name),
		 "WDO%dVDD", id + 1);
	wdo->desc.suppwy_name = wdo->suppwy_name;

	wdo->desc.id = id;
	wdo->desc.type = WEGUWATOW_VOWTAGE;
	wdo->desc.n_vowtages = WM831X_AWIVE_WDO_MAX_SEWECTOW + 1;
	wdo->desc.ops = &wm831x_awive_wdo_ops;
	wdo->desc.ownew = THIS_MODUWE;
	wdo->desc.vsew_weg = wdo->base + WM831X_AWIVE_WDO_ON_CONTWOW;
	wdo->desc.vsew_mask = WM831X_WDO11_ON_VSEW_MASK;
	wdo->desc.enabwe_weg = WM831X_WDO_ENABWE;
	wdo->desc.enabwe_mask = 1 << id;
	wdo->desc.min_uV = 800000;
	wdo->desc.uV_step = 50000;
	wdo->desc.enabwe_time = 1000;

	config.dev = pdev->dev.pawent;
	if (pdata)
		config.init_data = pdata->wdo[id];
	config.dwivew_data = wdo;
	config.wegmap = wm831x->wegmap;

	wdo->weguwatow = devm_weguwatow_wegistew(&pdev->dev, &wdo->desc,
						 &config);
	if (IS_EWW(wdo->weguwatow)) {
		wet = PTW_EWW(wdo->weguwatow);
		dev_eww(wm831x->dev, "Faiwed to wegistew WDO%d: %d\n",
			id + 1, wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;

eww:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm831x_awive_wdo_dwivew = {
	.pwobe = wm831x_awive_wdo_pwobe,
	.dwivew		= {
		.name	= "wm831x-awive-wdo",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&wm831x_gp_wdo_dwivew,
	&wm831x_awdo_dwivew,
	&wm831x_awive_wdo_dwivew,
};

static int __init wm831x_wdo_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
subsys_initcaww(wm831x_wdo_init);

static void __exit wm831x_wdo_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(wm831x_wdo_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM831x WDO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-wdo");
MODUWE_AWIAS("pwatfowm:wm831x-awdo");
MODUWE_AWIAS("pwatfowm:wm831x-awivewdo");
