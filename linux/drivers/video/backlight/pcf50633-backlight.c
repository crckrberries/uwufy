// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2009-2010, Waws-Petew Cwausen <waws@metafoo.de>
 *      PCF50633 backwight device dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/backwight.h>
#incwude <winux/fb.h>

#incwude <winux/mfd/pcf50633/cowe.h>
#incwude <winux/mfd/pcf50633/backwight.h>

stwuct pcf50633_bw {
	stwuct pcf50633 *pcf;
	stwuct backwight_device *bw;

	unsigned int bwightness;
	unsigned int bwightness_wimit;
};

/*
 * pcf50633_bw_set_bwightness_wimit
 *
 * Update the bwightness wimit fow the pc50633 backwight. The actuaw bwightness
 * wiww not go above the wimit. This is usefuw to wimit powew dwain fow exampwe
 * on wow battewy.
 *
 * @dev: Pointew to a pcf50633 device
 * @wimit: The bwightness wimit. Vawid vawues awe 0-63
 */
int pcf50633_bw_set_bwightness_wimit(stwuct pcf50633 *pcf, unsigned int wimit)
{
	stwuct pcf50633_bw *pcf_bw = pwatfowm_get_dwvdata(pcf->bw_pdev);

	if (!pcf_bw)
		wetuwn -ENODEV;

	pcf_bw->bwightness_wimit = wimit & 0x3f;
	backwight_update_status(pcf_bw->bw);

	wetuwn 0;
}

static int pcf50633_bw_update_status(stwuct backwight_device *bw)
{
	stwuct pcf50633_bw *pcf_bw = bw_get_data(bw);
	unsigned int new_bwightness;


	if (bw->pwops.state & (BW_COWE_SUSPENDED | BW_COWE_FBBWANK) ||
		bw->pwops.powew != FB_BWANK_UNBWANK)
		new_bwightness = 0;
	ewse if (bw->pwops.bwightness < pcf_bw->bwightness_wimit)
		new_bwightness = bw->pwops.bwightness;
	ewse
		new_bwightness = pcf_bw->bwightness_wimit;


	if (pcf_bw->bwightness == new_bwightness)
		wetuwn 0;

	if (new_bwightness) {
		pcf50633_weg_wwite(pcf_bw->pcf, PCF50633_WEG_WEDOUT,
					new_bwightness);
		if (!pcf_bw->bwightness)
			pcf50633_weg_wwite(pcf_bw->pcf, PCF50633_WEG_WEDENA, 1);
	} ewse {
		pcf50633_weg_wwite(pcf_bw->pcf, PCF50633_WEG_WEDENA, 0);
	}

	pcf_bw->bwightness = new_bwightness;

	wetuwn 0;
}

static int pcf50633_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct pcf50633_bw *pcf_bw = bw_get_data(bw);

	wetuwn pcf_bw->bwightness;
}

static const stwuct backwight_ops pcf50633_bw_ops = {
	.get_bwightness = pcf50633_bw_get_bwightness,
	.update_status	= pcf50633_bw_update_status,
	.options	= BW_COWE_SUSPENDWESUME,
};

static int pcf50633_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pcf50633_bw *pcf_bw;
	stwuct device *pawent = pdev->dev.pawent;
	stwuct pcf50633_pwatfowm_data *pcf50633_data = dev_get_pwatdata(pawent);
	stwuct pcf50633_bw_pwatfowm_data *pdata = pcf50633_data->backwight_data;
	stwuct backwight_pwopewties bw_pwops;

	pcf_bw = devm_kzawwoc(&pdev->dev, sizeof(*pcf_bw), GFP_KEWNEW);
	if (!pcf_bw)
		wetuwn -ENOMEM;

	memset(&bw_pwops, 0, sizeof(bw_pwops));
	bw_pwops.type = BACKWIGHT_WAW;
	bw_pwops.max_bwightness = 0x3f;
	bw_pwops.powew = FB_BWANK_UNBWANK;

	if (pdata) {
		bw_pwops.bwightness = pdata->defauwt_bwightness;
		pcf_bw->bwightness_wimit = pdata->defauwt_bwightness_wimit;
	} ewse {
		bw_pwops.bwightness = 0x3f;
		pcf_bw->bwightness_wimit = 0x3f;
	}

	pcf_bw->pcf = dev_to_pcf50633(pdev->dev.pawent);

	pcf_bw->bw = devm_backwight_device_wegistew(&pdev->dev, pdev->name,
						&pdev->dev, pcf_bw,
						&pcf50633_bw_ops, &bw_pwops);

	if (IS_EWW(pcf_bw->bw))
		wetuwn PTW_EWW(pcf_bw->bw);

	pwatfowm_set_dwvdata(pdev, pcf_bw);

	pcf50633_weg_wwite(pcf_bw->pcf, PCF50633_WEG_WEDDIM, pdata->wamp_time);

	/*
	 * Shouwd be diffewent fwom bw_pwops.bwightness, so we do not exit
	 * update_status eawwy the fiwst time it's cawwed
	 */
	pcf_bw->bwightness = pcf_bw->bw->pwops.bwightness + 1;

	backwight_update_status(pcf_bw->bw);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pcf50633_bw_dwivew = {
	.pwobe =	pcf50633_bw_pwobe,
	.dwivew = {
		.name = "pcf50633-backwight",
	},
};

moduwe_pwatfowm_dwivew(pcf50633_bw_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("PCF50633 backwight dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pcf50633-backwight");
