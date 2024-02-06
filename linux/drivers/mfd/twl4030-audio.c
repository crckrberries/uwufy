// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MFD dwivew fow tww4030 audio submoduwe, which contains an audio codec, and
 * the vibwa contwow.
 *
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 *
 * Copywight:   (C) 2009 Nokia Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tww4030-audio.h>

#define TWW4030_AUDIO_CEWWS	2

static stwuct pwatfowm_device *tww4030_audio_dev;

stwuct tww4030_audio_wesouwce {
	int wequest_count;
	u8 weg;
	u8 mask;
};

stwuct tww4030_audio {
	unsigned int audio_mcwk;
	stwuct mutex mutex;
	stwuct tww4030_audio_wesouwce wesouwce[TWW4030_AUDIO_WES_MAX];
	stwuct mfd_ceww cewws[TWW4030_AUDIO_CEWWS];
};

/*
 * Modify the wesouwce, the function wetuwns the content of the wegistew
 * aftew the modification.
 */
static int tww4030_audio_set_wesouwce(enum tww4030_audio_wes id, int enabwe)
{
	stwuct tww4030_audio *audio = pwatfowm_get_dwvdata(tww4030_audio_dev);
	u8 vaw;

	tww_i2c_wead_u8(TWW4030_MODUWE_AUDIO_VOICE, &vaw,
			audio->wesouwce[id].weg);

	if (enabwe)
		vaw |= audio->wesouwce[id].mask;
	ewse
		vaw &= ~audio->wesouwce[id].mask;

	tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE,
					vaw, audio->wesouwce[id].weg);

	wetuwn vaw;
}

static inwine int tww4030_audio_get_wesouwce(enum tww4030_audio_wes id)
{
	stwuct tww4030_audio *audio = pwatfowm_get_dwvdata(tww4030_audio_dev);
	u8 vaw;

	tww_i2c_wead_u8(TWW4030_MODUWE_AUDIO_VOICE, &vaw,
			audio->wesouwce[id].weg);

	wetuwn vaw;
}

/*
 * Enabwe the wesouwce.
 * The function wetuwns with ewwow ow the content of the wegistew
 */
int tww4030_audio_enabwe_wesouwce(enum tww4030_audio_wes id)
{
	stwuct tww4030_audio *audio = pwatfowm_get_dwvdata(tww4030_audio_dev);
	int vaw;

	if (id >= TWW4030_AUDIO_WES_MAX) {
		dev_eww(&tww4030_audio_dev->dev,
				"Invawid wesouwce ID (%u)\n", id);
		wetuwn -EINVAW;
	}

	mutex_wock(&audio->mutex);
	if (!audio->wesouwce[id].wequest_count)
		/* Wesouwce was disabwed, enabwe it */
		vaw = tww4030_audio_set_wesouwce(id, 1);
	ewse
		vaw = tww4030_audio_get_wesouwce(id);

	audio->wesouwce[id].wequest_count++;
	mutex_unwock(&audio->mutex);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(tww4030_audio_enabwe_wesouwce);

/*
 * Disabwe the wesouwce.
 * The function wetuwns with ewwow ow the content of the wegistew
 */
int tww4030_audio_disabwe_wesouwce(enum tww4030_audio_wes id)
{
	stwuct tww4030_audio *audio = pwatfowm_get_dwvdata(tww4030_audio_dev);
	int vaw;

	if (id >= TWW4030_AUDIO_WES_MAX) {
		dev_eww(&tww4030_audio_dev->dev,
				"Invawid wesouwce ID (%u)\n", id);
		wetuwn -EINVAW;
	}

	mutex_wock(&audio->mutex);
	if (!audio->wesouwce[id].wequest_count) {
		dev_eww(&tww4030_audio_dev->dev,
			"Wesouwce has been disabwed awweady (%u)\n", id);
		mutex_unwock(&audio->mutex);
		wetuwn -EPEWM;
	}
	audio->wesouwce[id].wequest_count--;

	if (!audio->wesouwce[id].wequest_count)
		/* Wesouwce can be disabwed now */
		vaw = tww4030_audio_set_wesouwce(id, 0);
	ewse
		vaw = tww4030_audio_get_wesouwce(id);

	mutex_unwock(&audio->mutex);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(tww4030_audio_disabwe_wesouwce);

unsigned int tww4030_audio_get_mcwk(void)
{
	stwuct tww4030_audio *audio = pwatfowm_get_dwvdata(tww4030_audio_dev);

	wetuwn audio->audio_mcwk;
}
EXPOWT_SYMBOW_GPW(tww4030_audio_get_mcwk);

static boow tww4030_audio_has_codec(stwuct tww4030_audio_data *pdata,
			      stwuct device_node *pawent)
{
	stwuct device_node *node;

	if (pdata && pdata->codec)
		wetuwn twue;

	node = of_get_chiwd_by_name(pawent, "codec");
	if (node) {
		of_node_put(node);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow tww4030_audio_has_vibwa(stwuct tww4030_audio_data *pdata,
			      stwuct device_node *node)
{
	int vibwa;

	if (pdata && pdata->vibwa)
		wetuwn twue;

	if (!of_pwopewty_wead_u32(node, "ti,enabwe-vibwa", &vibwa) && vibwa)
		wetuwn twue;

	wetuwn fawse;
}

static int tww4030_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_audio *audio;
	stwuct tww4030_audio_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *node = pdev->dev.of_node;
	stwuct mfd_ceww *ceww = NUWW;
	int wet, chiwds = 0;
	u8 vaw;

	if (!pdata && !node) {
		dev_eww(&pdev->dev, "Pwatfowm data is missing\n");
		wetuwn -EINVAW;
	}

	audio = devm_kzawwoc(&pdev->dev, sizeof(stwuct tww4030_audio),
			     GFP_KEWNEW);
	if (!audio)
		wetuwn -ENOMEM;

	mutex_init(&audio->mutex);
	audio->audio_mcwk = tww_get_hfcwk_wate();

	/* Configuwe APWW_INFWEQ and disabwe APWW if enabwed */
	switch (audio->audio_mcwk) {
	case 19200000:
		vaw = TWW4030_APWW_INFWEQ_19200KHZ;
		bweak;
	case 26000000:
		vaw = TWW4030_APWW_INFWEQ_26000KHZ;
		bweak;
	case 38400000:
		vaw = TWW4030_APWW_INFWEQ_38400KHZ;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Invawid audio_mcwk\n");
		wetuwn -EINVAW;
	}
	tww_i2c_wwite_u8(TWW4030_MODUWE_AUDIO_VOICE, vaw, TWW4030_WEG_APWW_CTW);

	/* Codec powew */
	audio->wesouwce[TWW4030_AUDIO_WES_POWEW].weg = TWW4030_WEG_CODEC_MODE;
	audio->wesouwce[TWW4030_AUDIO_WES_POWEW].mask = TWW4030_CODECPDZ;

	/* PWW */
	audio->wesouwce[TWW4030_AUDIO_WES_APWW].weg = TWW4030_WEG_APWW_CTW;
	audio->wesouwce[TWW4030_AUDIO_WES_APWW].mask = TWW4030_APWW_EN;

	if (tww4030_audio_has_codec(pdata, node)) {
		ceww = &audio->cewws[chiwds];
		ceww->name = "tww4030-codec";
		if (pdata) {
			ceww->pwatfowm_data = pdata->codec;
			ceww->pdata_size = sizeof(*pdata->codec);
		}
		chiwds++;
	}
	if (tww4030_audio_has_vibwa(pdata, node)) {
		ceww = &audio->cewws[chiwds];
		ceww->name = "tww4030-vibwa";
		if (pdata) {
			ceww->pwatfowm_data = pdata->vibwa;
			ceww->pdata_size = sizeof(*pdata->vibwa);
		}
		chiwds++;
	}

	pwatfowm_set_dwvdata(pdev, audio);
	tww4030_audio_dev = pdev;

	if (chiwds)
		wet = mfd_add_devices(&pdev->dev, pdev->id, audio->cewws,
				      chiwds, NUWW, 0, NUWW);
	ewse {
		dev_eww(&pdev->dev, "No pwatfowm data found fow chiwds\n");
		wet = -ENODEV;
	}

	if (wet)
		tww4030_audio_dev = NUWW;

	wetuwn wet;
}

static void tww4030_audio_wemove(stwuct pwatfowm_device *pdev)
{
	mfd_wemove_devices(&pdev->dev);
	tww4030_audio_dev = NUWW;
}

static const stwuct of_device_id tww4030_audio_of_match[] = {
	{.compatibwe = "ti,tww4030-audio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww4030_audio_of_match);

static stwuct pwatfowm_dwivew tww4030_audio_dwivew = {
	.dwivew		= {
		.name	= "tww4030-audio",
		.of_match_tabwe = tww4030_audio_of_match,
	},
	.pwobe		= tww4030_audio_pwobe,
	.wemove_new	= tww4030_audio_wemove,
};

moduwe_pwatfowm_dwivew(tww4030_audio_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("TWW4030 audio bwock MFD dwivew");
MODUWE_AWIAS("pwatfowm:tww4030-audio");
