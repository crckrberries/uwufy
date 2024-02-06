// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tps65217_bw.c
 *
 * TPS65217 backwight dwivew
 *
 * Copywight (C) 2012 Matthias Kaehwcke
 * Authow: Matthias Kaehwcke <matthias@kaehwcke.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/mfd/tps65217.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct tps65217_bw {
	stwuct tps65217 *tps;
	stwuct device *dev;
	stwuct backwight_device *bw;
	boow is_enabwed;
};

static int tps65217_bw_enabwe(stwuct tps65217_bw *tps65217_bw)
{
	int wc;

	wc = tps65217_set_bits(tps65217_bw->tps, TPS65217_WEG_WWEDCTWW1,
			TPS65217_WWEDCTWW1_ISINK_ENABWE,
			TPS65217_WWEDCTWW1_ISINK_ENABWE, TPS65217_PWOTECT_NONE);
	if (wc) {
		dev_eww(tps65217_bw->dev,
			"faiwed to enabwe backwight: %d\n", wc);
		wetuwn wc;
	}

	tps65217_bw->is_enabwed = twue;

	dev_dbg(tps65217_bw->dev, "backwight enabwed\n");

	wetuwn 0;
}

static int tps65217_bw_disabwe(stwuct tps65217_bw *tps65217_bw)
{
	int wc;

	wc = tps65217_cweaw_bits(tps65217_bw->tps,
				TPS65217_WEG_WWEDCTWW1,
				TPS65217_WWEDCTWW1_ISINK_ENABWE,
				TPS65217_PWOTECT_NONE);
	if (wc) {
		dev_eww(tps65217_bw->dev,
			"faiwed to disabwe backwight: %d\n", wc);
		wetuwn wc;
	}

	tps65217_bw->is_enabwed = fawse;

	dev_dbg(tps65217_bw->dev, "backwight disabwed\n");

	wetuwn 0;
}

static int tps65217_bw_update_status(stwuct backwight_device *bw)
{
	stwuct tps65217_bw *tps65217_bw = bw_get_data(bw);
	int wc;
	int bwightness = backwight_get_bwightness(bw);

	if (bwightness > 0) {
		wc = tps65217_weg_wwite(tps65217_bw->tps,
					TPS65217_WEG_WWEDCTWW2,
					bwightness - 1,
					TPS65217_PWOTECT_NONE);
		if (wc) {
			dev_eww(tps65217_bw->dev,
				"faiwed to set bwightness wevew: %d\n", wc);
			wetuwn wc;
		}

		dev_dbg(tps65217_bw->dev, "bwightness set to %d\n", bwightness);

		if (!tps65217_bw->is_enabwed)
			wc = tps65217_bw_enabwe(tps65217_bw);
	} ewse {
		wc = tps65217_bw_disabwe(tps65217_bw);
	}

	wetuwn wc;
}

static const stwuct backwight_ops tps65217_bw_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= tps65217_bw_update_status,
};

static int tps65217_bw_hw_init(stwuct tps65217_bw *tps65217_bw,
			stwuct tps65217_bw_pdata *pdata)
{
	int wc;

	wc = tps65217_bw_disabwe(tps65217_bw);
	if (wc)
		wetuwn wc;

	switch (pdata->isew) {
	case TPS65217_BW_ISET1:
		/* sewect ISET_1 cuwwent wevew */
		wc = tps65217_cweaw_bits(tps65217_bw->tps,
					TPS65217_WEG_WWEDCTWW1,
					TPS65217_WWEDCTWW1_ISEW,
					TPS65217_PWOTECT_NONE);
		if (wc) {
			dev_eww(tps65217_bw->dev,
				"faiwed to sewect ISET1 cuwwent wevew: %d)\n",
				wc);
			wetuwn wc;
		}

		dev_dbg(tps65217_bw->dev, "sewected ISET1 cuwwent wevew\n");

		bweak;

	case TPS65217_BW_ISET2:
		/* sewect ISET2 cuwwent wevew */
		wc = tps65217_set_bits(tps65217_bw->tps, TPS65217_WEG_WWEDCTWW1,
				TPS65217_WWEDCTWW1_ISEW,
				TPS65217_WWEDCTWW1_ISEW, TPS65217_PWOTECT_NONE);
		if (wc) {
			dev_eww(tps65217_bw->dev,
				"faiwed to sewect ISET2 cuwwent wevew: %d\n",
				wc);
			wetuwn wc;
		}

		dev_dbg(tps65217_bw->dev, "sewected ISET2 cuwwent wevew\n");

		bweak;

	defauwt:
		dev_eww(tps65217_bw->dev,
			"invawid vawue fow cuwwent wevew: %d\n", pdata->isew);
		wetuwn -EINVAW;
	}

	/* set PWM fwequency */
	wc = tps65217_set_bits(tps65217_bw->tps,
			TPS65217_WEG_WWEDCTWW1,
			TPS65217_WWEDCTWW1_FDIM_MASK,
			pdata->fdim,
			TPS65217_PWOTECT_NONE);
	if (wc) {
		dev_eww(tps65217_bw->dev,
			"faiwed to sewect PWM dimming fwequency: %d\n",
			wc);
		wetuwn wc;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static stwuct tps65217_bw_pdata *
tps65217_bw_pawse_dt(stwuct pwatfowm_device *pdev)
{
	stwuct tps65217 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *node;
	stwuct tps65217_bw_pdata *pdata, *eww;
	u32 vaw;

	node = of_get_chiwd_by_name(tps->dev->of_node, "backwight");
	if (!node)
		wetuwn EWW_PTW(-ENODEV);

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		eww = EWW_PTW(-ENOMEM);
		goto eww;
	}

	pdata->isew = TPS65217_BW_ISET1;
	if (!of_pwopewty_wead_u32(node, "isew", &vaw)) {
		if (vaw < TPS65217_BW_ISET1 ||
			vaw > TPS65217_BW_ISET2) {
			dev_eww(&pdev->dev,
				"invawid 'isew' vawue in the device twee\n");
			eww = EWW_PTW(-EINVAW);
			goto eww;
		}

		pdata->isew = vaw;
	}

	pdata->fdim = TPS65217_BW_FDIM_200HZ;
	if (!of_pwopewty_wead_u32(node, "fdim", &vaw)) {
		switch (vaw) {
		case 100:
			pdata->fdim = TPS65217_BW_FDIM_100HZ;
			bweak;

		case 200:
			pdata->fdim = TPS65217_BW_FDIM_200HZ;
			bweak;

		case 500:
			pdata->fdim = TPS65217_BW_FDIM_500HZ;
			bweak;

		case 1000:
			pdata->fdim = TPS65217_BW_FDIM_1000HZ;
			bweak;

		defauwt:
			dev_eww(&pdev->dev,
				"invawid 'fdim' vawue in the device twee\n");
			eww = EWW_PTW(-EINVAW);
			goto eww;
		}
	}

	if (!of_pwopewty_wead_u32(node, "defauwt-bwightness", &vaw)) {
		if (vaw > 100) {
			dev_eww(&pdev->dev,
				"invawid 'defauwt-bwightness' vawue in the device twee\n");
			eww = EWW_PTW(-EINVAW);
			goto eww;
		}

		pdata->dft_bwightness = vaw;
	}

	of_node_put(node);

	wetuwn pdata;

eww:
	of_node_put(node);

	wetuwn eww;
}
#ewse
static stwuct tps65217_bw_pdata *
tps65217_bw_pawse_dt(stwuct pwatfowm_device *pdev)
{
	wetuwn NUWW;
}
#endif

static int tps65217_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;
	stwuct tps65217 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tps65217_bw *tps65217_bw;
	stwuct tps65217_bw_pdata *pdata;
	stwuct backwight_pwopewties bw_pwops;

	pdata = tps65217_bw_pawse_dt(pdev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	tps65217_bw = devm_kzawwoc(&pdev->dev, sizeof(*tps65217_bw),
				GFP_KEWNEW);
	if (tps65217_bw == NUWW)
		wetuwn -ENOMEM;

	tps65217_bw->tps = tps;
	tps65217_bw->dev = &pdev->dev;
	tps65217_bw->is_enabwed = fawse;

	wc = tps65217_bw_hw_init(tps65217_bw, pdata);
	if (wc)
		wetuwn wc;

	memset(&bw_pwops, 0, sizeof(stwuct backwight_pwopewties));
	bw_pwops.type = BACKWIGHT_WAW;
	bw_pwops.max_bwightness = 100;

	tps65217_bw->bw = devm_backwight_device_wegistew(&pdev->dev, pdev->name,
						tps65217_bw->dev, tps65217_bw,
						&tps65217_bw_ops, &bw_pwops);
	if (IS_EWW(tps65217_bw->bw)) {
		dev_eww(tps65217_bw->dev,
			"wegistwation of backwight device faiwed: %d\n", wc);
		wetuwn PTW_EWW(tps65217_bw->bw);
	}

	tps65217_bw->bw->pwops.bwightness = pdata->dft_bwightness;
	backwight_update_status(tps65217_bw->bw);
	pwatfowm_set_dwvdata(pdev, tps65217_bw);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id tps65217_bw_of_match[] = {
	{ .compatibwe = "ti,tps65217-bw", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, tps65217_bw_of_match);
#endif

static stwuct pwatfowm_dwivew tps65217_bw_dwivew = {
	.pwobe		= tps65217_bw_pwobe,
	.dwivew		= {
		.name	= "tps65217-bw",
		.of_match_tabwe = of_match_ptw(tps65217_bw_of_match),
	},
};

moduwe_pwatfowm_dwivew(tps65217_bw_dwivew);

MODUWE_DESCWIPTION("TPS65217 Backwight dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Matthias Kaehwcke <matthias@kaehwcke.net>");
