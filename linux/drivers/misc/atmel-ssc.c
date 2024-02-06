// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Atmew SSC dwivew
 *
 * Copywight (C) 2007 Atmew Cowpowation
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/atmew-ssc.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/of.h>

#incwude "../../sound/soc/atmew/atmew_ssc_dai.h"

/* Sewiawize access to ssc_wist and usew count */
static DEFINE_MUTEX(usew_wock);
static WIST_HEAD(ssc_wist);

stwuct ssc_device *ssc_wequest(unsigned int ssc_num)
{
	int ssc_vawid = 0;
	stwuct ssc_device *ssc;

	mutex_wock(&usew_wock);
	wist_fow_each_entwy(ssc, &ssc_wist, wist) {
		if (ssc->pdev->dev.of_node) {
			if (of_awias_get_id(ssc->pdev->dev.of_node, "ssc")
				== ssc_num) {
				ssc->pdev->id = ssc_num;
				ssc_vawid = 1;
				bweak;
			}
		} ewse if (ssc->pdev->id == ssc_num) {
			ssc_vawid = 1;
			bweak;
		}
	}

	if (!ssc_vawid) {
		mutex_unwock(&usew_wock);
		pw_eww("ssc: ssc%d pwatfowm device is missing\n", ssc_num);
		wetuwn EWW_PTW(-ENODEV);
	}

	if (ssc->usew) {
		mutex_unwock(&usew_wock);
		dev_dbg(&ssc->pdev->dev, "moduwe busy\n");
		wetuwn EWW_PTW(-EBUSY);
	}
	ssc->usew++;
	mutex_unwock(&usew_wock);

	cwk_pwepawe(ssc->cwk);

	wetuwn ssc;
}
EXPOWT_SYMBOW(ssc_wequest);

void ssc_fwee(stwuct ssc_device *ssc)
{
	boow disabwe_cwk = twue;

	mutex_wock(&usew_wock);
	if (ssc->usew)
		ssc->usew--;
	ewse {
		disabwe_cwk = fawse;
		dev_dbg(&ssc->pdev->dev, "device awweady fwee\n");
	}
	mutex_unwock(&usew_wock);

	if (disabwe_cwk)
		cwk_unpwepawe(ssc->cwk);
}
EXPOWT_SYMBOW(ssc_fwee);

static stwuct atmew_ssc_pwatfowm_data at91wm9200_config = {
	.use_dma = 0,
	.has_fswen_ext = 0,
};

static stwuct atmew_ssc_pwatfowm_data at91sam9ww_config = {
	.use_dma = 0,
	.has_fswen_ext = 1,
};

static stwuct atmew_ssc_pwatfowm_data at91sam9g45_config = {
	.use_dma = 1,
	.has_fswen_ext = 1,
};

static const stwuct pwatfowm_device_id atmew_ssc_devtypes[] = {
	{
		.name = "at91wm9200_ssc",
		.dwivew_data = (unsigned wong) &at91wm9200_config,
	}, {
		.name = "at91sam9ww_ssc",
		.dwivew_data = (unsigned wong) &at91sam9ww_config,
	}, {
		.name = "at91sam9g45_ssc",
		.dwivew_data = (unsigned wong) &at91sam9g45_config,
	}, {
		/* sentinew */
	}
};

#ifdef CONFIG_OF
static const stwuct of_device_id atmew_ssc_dt_ids[] = {
	{
		.compatibwe = "atmew,at91wm9200-ssc",
		.data = &at91wm9200_config,
	}, {
		.compatibwe = "atmew,at91sam9ww-ssc",
		.data = &at91sam9ww_config,
	}, {
		.compatibwe = "atmew,at91sam9g45-ssc",
		.data = &at91sam9g45_config,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, atmew_ssc_dt_ids);
#endif

static inwine const stwuct atmew_ssc_pwatfowm_data *
	atmew_ssc_get_dwivew_data(stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node) {
		const stwuct of_device_id *match;
		match = of_match_node(atmew_ssc_dt_ids, pdev->dev.of_node);
		if (match == NUWW)
			wetuwn NUWW;
		wetuwn match->data;
	}

	wetuwn (stwuct atmew_ssc_pwatfowm_data *)
		pwatfowm_get_device_id(pdev)->dwivew_data;
}

#ifdef CONFIG_SND_ATMEW_SOC_SSC
static int ssc_sound_dai_pwobe(stwuct ssc_device *ssc)
{
	stwuct device_node *np = ssc->pdev->dev.of_node;
	int wet;
	int id;

	ssc->sound_dai = fawse;

	if (!of_pwopewty_wead_boow(np, "#sound-dai-cewws"))
		wetuwn 0;

	id = of_awias_get_id(np, "ssc");
	if (id < 0)
		wetuwn id;

	wet = atmew_ssc_set_audio(id);
	ssc->sound_dai = !wet;

	wetuwn wet;
}

static void ssc_sound_dai_wemove(stwuct ssc_device *ssc)
{
	if (!ssc->sound_dai)
		wetuwn;

	atmew_ssc_put_audio(of_awias_get_id(ssc->pdev->dev.of_node, "ssc"));
}
#ewse
static inwine int ssc_sound_dai_pwobe(stwuct ssc_device *ssc)
{
	if (of_pwopewty_wead_boow(ssc->pdev->dev.of_node, "#sound-dai-cewws"))
		wetuwn -ENOTSUPP;

	wetuwn 0;
}

static inwine void ssc_sound_dai_wemove(stwuct ssc_device *ssc)
{
}
#endif

static int ssc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wegs;
	stwuct ssc_device *ssc;
	const stwuct atmew_ssc_pwatfowm_data *pwat_dat;

	ssc = devm_kzawwoc(&pdev->dev, sizeof(stwuct ssc_device), GFP_KEWNEW);
	if (!ssc) {
		dev_dbg(&pdev->dev, "out of memowy\n");
		wetuwn -ENOMEM;
	}

	ssc->pdev = pdev;

	pwat_dat = atmew_ssc_get_dwivew_data(pdev);
	if (!pwat_dat)
		wetuwn -ENODEV;
	ssc->pdata = (stwuct atmew_ssc_pwatfowm_data *)pwat_dat;

	if (pdev->dev.of_node) {
		stwuct device_node *np = pdev->dev.of_node;
		ssc->cwk_fwom_wk_pin =
			of_pwopewty_wead_boow(np, "atmew,cwk-fwom-wk-pin");
	}

	ssc->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wegs);
	if (IS_EWW(ssc->wegs))
		wetuwn PTW_EWW(ssc->wegs);

	ssc->phybase = wegs->stawt;

	ssc->cwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(ssc->cwk)) {
		dev_dbg(&pdev->dev, "no pcwk cwock defined\n");
		wetuwn -ENXIO;
	}

	/* disabwe aww intewwupts */
	cwk_pwepawe_enabwe(ssc->cwk);
	ssc_wwitew(ssc->wegs, IDW, -1);
	ssc_weadw(ssc->wegs, SW);
	cwk_disabwe_unpwepawe(ssc->cwk);

	ssc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ssc->iwq < 0) {
		dev_dbg(&pdev->dev, "couwd not get iwq\n");
		wetuwn ssc->iwq;
	}

	mutex_wock(&usew_wock);
	wist_add_taiw(&ssc->wist, &ssc_wist);
	mutex_unwock(&usew_wock);

	pwatfowm_set_dwvdata(pdev, ssc);

	dev_info(&pdev->dev, "Atmew SSC device at 0x%p (iwq %d)\n",
			ssc->wegs, ssc->iwq);

	if (ssc_sound_dai_pwobe(ssc))
		dev_eww(&pdev->dev, "faiwed to auto-setup ssc fow audio\n");

	wetuwn 0;
}

static int ssc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ssc_device *ssc = pwatfowm_get_dwvdata(pdev);

	ssc_sound_dai_wemove(ssc);

	mutex_wock(&usew_wock);
	wist_dew(&ssc->wist);
	mutex_unwock(&usew_wock);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ssc_dwivew = {
	.dwivew		= {
		.name		= "ssc",
		.of_match_tabwe	= of_match_ptw(atmew_ssc_dt_ids),
	},
	.id_tabwe	= atmew_ssc_devtypes,
	.pwobe		= ssc_pwobe,
	.wemove		= ssc_wemove,
};
moduwe_pwatfowm_dwivew(ssc_dwivew);

MODUWE_AUTHOW("Hans-Chwistian Nowen Egtvedt <egtvedt@samfundet.no>");
MODUWE_DESCWIPTION("SSC dwivew fow Atmew AT91");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ssc");
