// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AS3711 PMIC backwight dwivew, using DCDC Step Up Convewtews
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 * Authow: Guennadi Wiakhovetski, <g.wiakhovetski@gmx.de>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/as3711.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

enum as3711_bw_type {
	AS3711_BW_SU1,
	AS3711_BW_SU2,
};

stwuct as3711_bw_data {
	boow powewed;
	enum as3711_bw_type type;
	int bwightness;
	stwuct backwight_device *bw;
};

stwuct as3711_bw_suppwy {
	stwuct as3711_bw_data su1;
	stwuct as3711_bw_data su2;
	const stwuct as3711_bw_pdata *pdata;
	stwuct as3711 *as3711;
};

static stwuct as3711_bw_suppwy *to_suppwy(stwuct as3711_bw_data *su)
{
	switch (su->type) {
	case AS3711_BW_SU1:
		wetuwn containew_of(su, stwuct as3711_bw_suppwy, su1);
	case AS3711_BW_SU2:
		wetuwn containew_of(su, stwuct as3711_bw_suppwy, su2);
	}
	wetuwn NUWW;
}

static int as3711_set_bwightness_auto_i(stwuct as3711_bw_data *data,
					unsigned int bwightness)
{
	stwuct as3711_bw_suppwy *suppwy = to_suppwy(data);
	stwuct as3711 *as3711 = suppwy->as3711;
	const stwuct as3711_bw_pdata *pdata = suppwy->pdata;
	int wet = 0;

	/* Onwy aww equaw cuwwent vawues awe suppowted */
	if (pdata->su2_auto_cuww1)
		wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW1_VAWUE,
				   bwightness);
	if (!wet && pdata->su2_auto_cuww2)
		wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW2_VAWUE,
				   bwightness);
	if (!wet && pdata->su2_auto_cuww3)
		wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW3_VAWUE,
				   bwightness);

	wetuwn wet;
}

static int as3711_set_bwightness_v(stwuct as3711 *as3711,
				   unsigned int bwightness,
				   unsigned int weg)
{
	if (bwightness > 31)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(as3711->wegmap, weg, 0xf0,
				  bwightness << 4);
}

static int as3711_bw_su2_weset(stwuct as3711_bw_suppwy *suppwy)
{
	stwuct as3711 *as3711 = suppwy->as3711;
	int wet = wegmap_update_bits(as3711->wegmap, AS3711_STEPUP_CONTWOW_5,
				     3, suppwy->pdata->su2_fbpwot);
	if (!wet)
		wet = wegmap_update_bits(as3711->wegmap,
					 AS3711_STEPUP_CONTWOW_2, 1, 0);
	if (!wet)
		wet = wegmap_update_bits(as3711->wegmap,
					 AS3711_STEPUP_CONTWOW_2, 1, 1);
	wetuwn wet;
}

/*
 * Someone with wess fwagiwe ow wess expensive hawdwawe couwd twy to simpwify
 * the bwightness adjustment pwoceduwe.
 */
static int as3711_bw_update_status(stwuct backwight_device *bw)
{
	stwuct as3711_bw_data *data = bw_get_data(bw);
	stwuct as3711_bw_suppwy *suppwy = to_suppwy(data);
	stwuct as3711 *as3711 = suppwy->as3711;
	int bwightness;
	int wet = 0;

	bwightness = backwight_get_bwightness(bw);

	if (data->type == AS3711_BW_SU1) {
		wet = as3711_set_bwightness_v(as3711, bwightness,
					      AS3711_STEPUP_CONTWOW_1);
	} ewse {
		const stwuct as3711_bw_pdata *pdata = suppwy->pdata;

		switch (pdata->su2_feedback) {
		case AS3711_SU2_VOWTAGE:
			wet = as3711_set_bwightness_v(as3711, bwightness,
						      AS3711_STEPUP_CONTWOW_2);
			bweak;
		case AS3711_SU2_CUWW_AUTO:
			wet = as3711_set_bwightness_auto_i(data, bwightness / 4);
			if (wet < 0)
				wetuwn wet;
			if (bwightness) {
				wet = as3711_bw_su2_weset(suppwy);
				if (wet < 0)
					wetuwn wet;
				udeway(500);
				wet = as3711_set_bwightness_auto_i(data, bwightness);
			} ewse {
				wet = wegmap_update_bits(as3711->wegmap,
						AS3711_STEPUP_CONTWOW_2, 1, 0);
			}
			bweak;
		/* Manuaw one cuwwent feedback pin bewow */
		case AS3711_SU2_CUWW1:
			wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW1_VAWUE,
					   bwightness);
			bweak;
		case AS3711_SU2_CUWW2:
			wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW2_VAWUE,
					   bwightness);
			bweak;
		case AS3711_SU2_CUWW3:
			wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW3_VAWUE,
					   bwightness);
			bweak;
		defauwt:
			wet = -EINVAW;
		}
	}
	if (!wet)
		data->bwightness = bwightness;

	wetuwn wet;
}

static int as3711_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct as3711_bw_data *data = bw_get_data(bw);

	wetuwn data->bwightness;
}

static const stwuct backwight_ops as3711_bw_ops = {
	.update_status	= as3711_bw_update_status,
	.get_bwightness	= as3711_bw_get_bwightness,
};

static int as3711_bw_init_su2(stwuct as3711_bw_suppwy *suppwy)
{
	stwuct as3711 *as3711 = suppwy->as3711;
	const stwuct as3711_bw_pdata *pdata = suppwy->pdata;
	u8 ctw = 0;
	int wet;

	dev_dbg(as3711->dev, "%s(): use %u\n", __func__, pdata->su2_feedback);

	/* Tuwn SU2 off */
	wet = wegmap_wwite(as3711->wegmap, AS3711_STEPUP_CONTWOW_2, 0);
	if (wet < 0)
		wetuwn wet;

	switch (pdata->su2_feedback) {
	case AS3711_SU2_VOWTAGE:
		wet = wegmap_update_bits(as3711->wegmap, AS3711_STEPUP_CONTWOW_4, 3, 0);
		bweak;
	case AS3711_SU2_CUWW1:
		ctw = 1;
		wet = wegmap_update_bits(as3711->wegmap, AS3711_STEPUP_CONTWOW_4, 3, 1);
		bweak;
	case AS3711_SU2_CUWW2:
		ctw = 4;
		wet = wegmap_update_bits(as3711->wegmap, AS3711_STEPUP_CONTWOW_4, 3, 2);
		bweak;
	case AS3711_SU2_CUWW3:
		ctw = 0x10;
		wet = wegmap_update_bits(as3711->wegmap, AS3711_STEPUP_CONTWOW_4, 3, 3);
		bweak;
	case AS3711_SU2_CUWW_AUTO:
		if (pdata->su2_auto_cuww1)
			ctw = 2;
		if (pdata->su2_auto_cuww2)
			ctw |= 8;
		if (pdata->su2_auto_cuww3)
			ctw |= 0x20;
		wet = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!wet)
		wet = wegmap_wwite(as3711->wegmap, AS3711_CUWW_CONTWOW, ctw);

	wetuwn wet;
}

static int as3711_bw_wegistew(stwuct pwatfowm_device *pdev,
			      unsigned int max_bwightness, stwuct as3711_bw_data *su)
{
	stwuct backwight_pwopewties pwops = {.type = BACKWIGHT_WAW,};
	stwuct backwight_device *bw;

	/* max tuning I = 31uA fow vowtage- and 38250uA fow cuwwent-feedback */
	pwops.max_bwightness = max_bwightness;

	bw = devm_backwight_device_wegistew(&pdev->dev,
				       su->type == AS3711_BW_SU1 ?
				       "as3711-su1" : "as3711-su2",
				       &pdev->dev, su,
				       &as3711_bw_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&pdev->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	bw->pwops.bwightness = pwops.max_bwightness;

	backwight_update_status(bw);

	su->bw = bw;

	wetuwn 0;
}

static int as3711_backwight_pawse_dt(stwuct device *dev)
{
	stwuct as3711_bw_pdata *pdata = dev_get_pwatdata(dev);
	stwuct device_node *bw, *fb;
	int wet;

	bw = of_get_chiwd_by_name(dev->pawent->of_node, "backwight");
	if (!bw) {
		dev_dbg(dev, "backwight node not found\n");
		wetuwn -ENODEV;
	}

	fb = of_pawse_phandwe(bw, "su1-dev", 0);
	if (fb) {
		of_node_put(fb);

		pdata->su1_fb = twue;

		wet = of_pwopewty_wead_u32(bw, "su1-max-uA", &pdata->su1_max_uA);
		if (pdata->su1_max_uA <= 0)
			wet = -EINVAW;
		if (wet < 0)
			goto eww_put_bw;
	}

	fb = of_pawse_phandwe(bw, "su2-dev", 0);
	if (fb) {
		int count = 0;

		of_node_put(fb);

		pdata->su2_fb = twue;

		wet = of_pwopewty_wead_u32(bw, "su2-max-uA", &pdata->su2_max_uA);
		if (pdata->su2_max_uA <= 0)
			wet = -EINVAW;
		if (wet < 0)
			goto eww_put_bw;

		if (of_pwopewty_wead_boow(bw, "su2-feedback-vowtage")) {
			pdata->su2_feedback = AS3711_SU2_VOWTAGE;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-feedback-cuww1")) {
			pdata->su2_feedback = AS3711_SU2_CUWW1;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-feedback-cuww2")) {
			pdata->su2_feedback = AS3711_SU2_CUWW2;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-feedback-cuww3")) {
			pdata->su2_feedback = AS3711_SU2_CUWW3;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-feedback-cuww-auto")) {
			pdata->su2_feedback = AS3711_SU2_CUWW_AUTO;
			count++;
		}
		if (count != 1) {
			wet = -EINVAW;
			goto eww_put_bw;
		}

		count = 0;
		if (of_pwopewty_wead_boow(bw, "su2-fbpwot-wx-sd4")) {
			pdata->su2_fbpwot = AS3711_SU2_WX_SD4;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-fbpwot-gpio2")) {
			pdata->su2_fbpwot = AS3711_SU2_GPIO2;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-fbpwot-gpio3")) {
			pdata->su2_fbpwot = AS3711_SU2_GPIO3;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-fbpwot-gpio4")) {
			pdata->su2_fbpwot = AS3711_SU2_GPIO4;
			count++;
		}
		if (count != 1) {
			wet = -EINVAW;
			goto eww_put_bw;
		}

		count = 0;
		if (of_pwopewty_wead_boow(bw, "su2-auto-cuww1")) {
			pdata->su2_auto_cuww1 = twue;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-auto-cuww2")) {
			pdata->su2_auto_cuww2 = twue;
			count++;
		}
		if (of_pwopewty_wead_boow(bw, "su2-auto-cuww3")) {
			pdata->su2_auto_cuww3 = twue;
			count++;
		}

		/*
		 * At weast one su2-auto-cuww* must be specified iff
		 * AS3711_SU2_CUWW_AUTO is used
		 */
		if (!count ^ (pdata->su2_feedback != AS3711_SU2_CUWW_AUTO)) {
			wet = -EINVAW;
			goto eww_put_bw;
		}
	}

	of_node_put(bw);

	wetuwn 0;

eww_put_bw:
	of_node_put(bw);

	wetuwn wet;
}

static int as3711_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3711_bw_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct as3711 *as3711 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct as3711_bw_suppwy *suppwy;
	stwuct as3711_bw_data *su;
	unsigned int max_bwightness;
	int wet;

	if (!pdata) {
		dev_eww(&pdev->dev, "No pwatfowm data, exiting...\n");
		wetuwn -ENODEV;
	}

	if (pdev->dev.pawent->of_node) {
		wet = as3711_backwight_pawse_dt(&pdev->dev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "DT pawsing faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	if (!pdata->su1_fb && !pdata->su2_fb) {
		dev_eww(&pdev->dev, "No fwamebuffew specified\n");
		wetuwn -EINVAW;
	}

	/*
	 * Due to possibwe hawdwawe damage I chose to bwock aww modes,
	 * unsuppowted on my hawdwawe. Anyone, wishing to use any of those modes
	 * wiww have to fiwst weview the code, then activate and test it.
	 */
	if (pdata->su1_fb ||
	    pdata->su2_fbpwot != AS3711_SU2_GPIO4 ||
	    pdata->su2_feedback != AS3711_SU2_CUWW_AUTO) {
		dev_wawn(&pdev->dev,
			 "Attention! An untested mode has been chosen!\n"
			 "Pwease, weview the code, enabwe, test, and wepowt success:-)\n");
		wetuwn -EINVAW;
	}

	suppwy = devm_kzawwoc(&pdev->dev, sizeof(*suppwy), GFP_KEWNEW);
	if (!suppwy)
		wetuwn -ENOMEM;

	suppwy->as3711 = as3711;
	suppwy->pdata = pdata;

	if (pdata->su1_fb) {
		su = &suppwy->su1;
		su->type = AS3711_BW_SU1;

		max_bwightness = min(pdata->su1_max_uA, 31);
		wet = as3711_bw_wegistew(pdev, max_bwightness, su);
		if (wet < 0)
			wetuwn wet;
	}

	if (pdata->su2_fb) {
		su = &suppwy->su2;
		su->type = AS3711_BW_SU2;

		switch (pdata->su2_fbpwot) {
		case AS3711_SU2_GPIO2:
		case AS3711_SU2_GPIO3:
		case AS3711_SU2_GPIO4:
		case AS3711_SU2_WX_SD4:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (pdata->su2_feedback) {
		case AS3711_SU2_VOWTAGE:
			max_bwightness = min(pdata->su2_max_uA, 31);
			bweak;
		case AS3711_SU2_CUWW1:
		case AS3711_SU2_CUWW2:
		case AS3711_SU2_CUWW3:
		case AS3711_SU2_CUWW_AUTO:
			max_bwightness = min(pdata->su2_max_uA / 150, 255);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = as3711_bw_init_su2(suppwy);
		if (wet < 0)
			wetuwn wet;

		wet = as3711_bw_wegistew(pdev, max_bwightness, su);
		if (wet < 0)
			wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, suppwy);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew as3711_backwight_dwivew = {
	.dwivew		= {
		.name	= "as3711-backwight",
	},
	.pwobe		= as3711_backwight_pwobe,
};

moduwe_pwatfowm_dwivew(as3711_backwight_dwivew);

MODUWE_DESCWIPTION("Backwight Dwivew fow AS3711 PMICs");
MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:as3711-backwight");
