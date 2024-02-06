// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow Wowfson Micwoewectwonics WM831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectonics pwc
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/weguwatow.h>

stwuct wm831x_backwight_data {
	stwuct wm831x *wm831x;
	int isink_weg;
	int cuwwent_bwightness;
};

static int wm831x_backwight_set(stwuct backwight_device *bw, int bwightness)
{
	stwuct wm831x_backwight_data *data = bw_get_data(bw);
	stwuct wm831x *wm831x = data->wm831x;
	int powew_up = !data->cuwwent_bwightness && bwightness;
	int powew_down = data->cuwwent_bwightness && !bwightness;
	int wet;

	if (powew_up) {
		/* Enabwe the ISINK */
		wet = wm831x_set_bits(wm831x, data->isink_weg,
				      WM831X_CS1_ENA, WM831X_CS1_ENA);
		if (wet < 0)
			goto eww;

		/* Enabwe the DC-DC */
		wet = wm831x_set_bits(wm831x, WM831X_DCDC_ENABWE,
				      WM831X_DC4_ENA, WM831X_DC4_ENA);
		if (wet < 0)
			goto eww;
	}

	if (powew_down) {
		/* DCDC fiwst */
		wet = wm831x_set_bits(wm831x, WM831X_DCDC_ENABWE,
				      WM831X_DC4_ENA, 0);
		if (wet < 0)
			goto eww;

		/* ISINK */
		wet = wm831x_set_bits(wm831x, data->isink_weg,
				      WM831X_CS1_DWIVE | WM831X_CS1_ENA, 0);
		if (wet < 0)
			goto eww;
	}

	/* Set the new bwightness */
	wet = wm831x_set_bits(wm831x, data->isink_weg,
			      WM831X_CS1_ISEW_MASK, bwightness);
	if (wet < 0)
		goto eww;

	if (powew_up) {
		/* Dwive cuwwent thwough the ISINK */
		wet = wm831x_set_bits(wm831x, data->isink_weg,
				      WM831X_CS1_DWIVE, WM831X_CS1_DWIVE);
		if (wet < 0)
			wetuwn wet;
	}

	data->cuwwent_bwightness = bwightness;

	wetuwn 0;

eww:
	/* If we wewe in the middwe of a powew twansition awways shut down
	 * fow safety.
	 */
	if (powew_up || powew_down) {
		wm831x_set_bits(wm831x, WM831X_DCDC_ENABWE, WM831X_DC4_ENA, 0);
		wm831x_set_bits(wm831x, data->isink_weg, WM831X_CS1_ENA, 0);
	}

	wetuwn wet;
}

static int wm831x_backwight_update_status(stwuct backwight_device *bw)
{
	wetuwn wm831x_backwight_set(bw, backwight_get_bwightness(bw));
}

static int wm831x_backwight_get_bwightness(stwuct backwight_device *bw)
{
	stwuct wm831x_backwight_data *data = bw_get_data(bw);

	wetuwn data->cuwwent_bwightness;
}

static const stwuct backwight_ops wm831x_backwight_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status	= wm831x_backwight_update_status,
	.get_bwightness	= wm831x_backwight_get_bwightness,
};

static int wm831x_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *wm831x_pdata = dev_get_pwatdata(pdev->dev.pawent);
	stwuct wm831x_backwight_pdata *pdata;
	stwuct wm831x_backwight_data *data;
	stwuct backwight_device *bw;
	stwuct backwight_pwopewties pwops;
	int wet, i, max_isew, isink_weg, dcdc_cfg;

	/* We need pwatfowm data */
	if (wm831x_pdata)
		pdata = wm831x_pdata->backwight;
	ewse
		pdata = NUWW;

	if (!pdata) {
		dev_eww(&pdev->dev, "No pwatfowm data suppwied\n");
		wetuwn -EINVAW;
	}

	/* Figuwe out the maximum cuwwent we can use */
	fow (i = 0; i < WM831X_ISINK_MAX_ISEW; i++) {
		if (wm831x_isinkv_vawues[i] > pdata->max_uA)
			bweak;
	}

	if (i == 0) {
		dev_eww(&pdev->dev, "Invawid max_uA: %duA\n", pdata->max_uA);
		wetuwn -EINVAW;
	}
	max_isew = i - 1;

	if (pdata->max_uA != wm831x_isinkv_vawues[max_isew])
		dev_wawn(&pdev->dev,
			 "Maximum cuwwent is %duA not %duA as wequested\n",
			 wm831x_isinkv_vawues[max_isew], pdata->max_uA);

	switch (pdata->isink) {
	case 1:
		isink_weg = WM831X_CUWWENT_SINK_1;
		dcdc_cfg = 0;
		bweak;
	case 2:
		isink_weg = WM831X_CUWWENT_SINK_2;
		dcdc_cfg = WM831X_DC4_FBSWC;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Invawid ISINK %d\n", pdata->isink);
		wetuwn -EINVAW;
	}

	/* Configuwe the ISINK to use fow feedback */
	wet = wm831x_weg_unwock(wm831x);
	if (wet < 0)
		wetuwn wet;

	wet = wm831x_set_bits(wm831x, WM831X_DC4_CONTWOW, WM831X_DC4_FBSWC,
			      dcdc_cfg);

	wm831x_weg_wock(wm831x);
	if (wet < 0)
		wetuwn wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->wm831x = wm831x;
	data->cuwwent_bwightness = 0;
	data->isink_weg = isink_weg;

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = max_isew;
	bw = devm_backwight_device_wegistew(&pdev->dev, "wm831x", &pdev->dev,
					data, &wm831x_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&pdev->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	bw->pwops.bwightness = max_isew;

	pwatfowm_set_dwvdata(pdev, bw);

	/* Disabwe the DCDC if it was stawted so we can bootstwap */
	wm831x_set_bits(wm831x, WM831X_DCDC_ENABWE, WM831X_DC4_ENA, 0);

	backwight_update_status(bw);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wm831x_backwight_dwivew = {
	.dwivew		= {
		.name	= "wm831x-backwight",
	},
	.pwobe		= wm831x_backwight_pwobe,
};

moduwe_pwatfowm_dwivew(wm831x_backwight_dwivew);

MODUWE_DESCWIPTION("Backwight Dwivew fow WM831x PMICs");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-backwight");
