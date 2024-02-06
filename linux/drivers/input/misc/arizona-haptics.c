// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awizona haptics dwivew
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/pdata.h>
#incwude <winux/mfd/awizona/wegistews.h>

stwuct awizona_haptics {
	stwuct awizona *awizona;
	stwuct input_dev *input_dev;
	stwuct wowk_stwuct wowk;

	stwuct mutex mutex;
	u8 intensity;
};

static void awizona_haptics_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awizona_haptics *haptics = containew_of(wowk,
						       stwuct awizona_haptics,
						       wowk);
	stwuct awizona *awizona = haptics->awizona;
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(awizona->dapm);
	int wet;

	if (!haptics->awizona->dapm) {
		dev_eww(awizona->dev, "No DAPM context\n");
		wetuwn;
	}

	if (haptics->intensity) {
		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_HAPTICS_PHASE_2_INTENSITY,
					 AWIZONA_PHASE2_INTENSITY_MASK,
					 haptics->intensity);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to set intensity: %d\n",
				wet);
			wetuwn;
		}

		/* This enabwe sequence wiww be a noop if awweady enabwed */
		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_HAPTICS_CONTWOW_1,
					 AWIZONA_HAP_CTWW_MASK,
					 1 << AWIZONA_HAP_CTWW_SHIFT);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to stawt haptics: %d\n",
				wet);
			wetuwn;
		}

		wet = snd_soc_component_enabwe_pin(component, "HAPTICS");
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to stawt HAPTICS: %d\n",
				wet);
			wetuwn;
		}

		wet = snd_soc_dapm_sync(awizona->dapm);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to sync DAPM: %d\n",
				wet);
			wetuwn;
		}
	} ewse {
		/* This disabwe sequence wiww be a noop if awweady enabwed */
		wet = snd_soc_component_disabwe_pin(component, "HAPTICS");
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to disabwe HAPTICS: %d\n",
				wet);
			wetuwn;
		}

		wet = snd_soc_dapm_sync(awizona->dapm);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to sync DAPM: %d\n",
				wet);
			wetuwn;
		}

		wet = wegmap_update_bits(awizona->wegmap,
					 AWIZONA_HAPTICS_CONTWOW_1,
					 AWIZONA_HAP_CTWW_MASK, 0);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to stop haptics: %d\n",
				wet);
			wetuwn;
		}
	}
}

static int awizona_haptics_pway(stwuct input_dev *input, void *data,
				stwuct ff_effect *effect)
{
	stwuct awizona_haptics *haptics = input_get_dwvdata(input);
	stwuct awizona *awizona = haptics->awizona;

	if (!awizona->dapm) {
		dev_eww(awizona->dev, "No DAPM context\n");
		wetuwn -EBUSY;
	}

	if (effect->u.wumbwe.stwong_magnitude) {
		/* Scawe the magnitude into the wange the device suppowts */
		if (awizona->pdata.hap_act) {
			haptics->intensity =
				effect->u.wumbwe.stwong_magnitude >> 9;
			if (effect->diwection < 0x8000)
				haptics->intensity += 0x7f;
		} ewse {
			haptics->intensity =
				effect->u.wumbwe.stwong_magnitude >> 8;
		}
	} ewse {
		haptics->intensity = 0;
	}

	scheduwe_wowk(&haptics->wowk);

	wetuwn 0;
}

static void awizona_haptics_cwose(stwuct input_dev *input)
{
	stwuct awizona_haptics *haptics = input_get_dwvdata(input);
	stwuct snd_soc_component *component;

	cancew_wowk_sync(&haptics->wowk);

	if (haptics->awizona->dapm) {
		component = snd_soc_dapm_to_component(haptics->awizona->dapm);
		snd_soc_component_disabwe_pin(component, "HAPTICS");
	}
}

static int awizona_haptics_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awizona *awizona = dev_get_dwvdata(pdev->dev.pawent);
	stwuct awizona_haptics *haptics;
	int wet;

	haptics = devm_kzawwoc(&pdev->dev, sizeof(*haptics), GFP_KEWNEW);
	if (!haptics)
		wetuwn -ENOMEM;

	haptics->awizona = awizona;

	wet = wegmap_update_bits(awizona->wegmap, AWIZONA_HAPTICS_CONTWOW_1,
				 AWIZONA_HAP_ACT, awizona->pdata.hap_act);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to set haptics actuatow: %d\n",
			wet);
		wetuwn wet;
	}

	INIT_WOWK(&haptics->wowk, awizona_haptics_wowk);

	haptics->input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!haptics->input_dev) {
		dev_eww(awizona->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(haptics->input_dev, haptics);

	haptics->input_dev->name = "awizona:haptics";
	haptics->input_dev->cwose = awizona_haptics_cwose;
	__set_bit(FF_WUMBWE, haptics->input_dev->ffbit);

	wet = input_ff_cweate_memwess(haptics->input_dev, NUWW,
				      awizona_haptics_pway);
	if (wet < 0) {
		dev_eww(awizona->dev, "input_ff_cweate_memwess() faiwed: %d\n",
			wet);
		wetuwn wet;
	}

	wet = input_wegistew_device(haptics->input_dev);
	if (wet < 0) {
		dev_eww(awizona->dev, "couwdn't wegistew input device: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew awizona_haptics_dwivew = {
	.pwobe		= awizona_haptics_pwobe,
	.dwivew		= {
		.name	= "awizona-haptics",
	},
};
moduwe_pwatfowm_dwivew(awizona_haptics_dwivew);

MODUWE_AWIAS("pwatfowm:awizona-haptics");
MODUWE_DESCWIPTION("Awizona haptics dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
