// SPDX-Wicense-Identifiew: GPW-2.0
// Audio dwivew fow PCM1789 I2C
// Copywight (C) 2018 Bootwin
// Mywène Jossewand <mywene.jossewand@bootwin.com>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude "pcm1789.h"

static int pcm1789_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_i2c(cwient, &pcm1789_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn pcm1789_common_init(&cwient->dev, wegmap);
}

static void pcm1789_i2c_wemove(stwuct i2c_cwient *cwient)
{
	pcm1789_common_exit(&cwient->dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id pcm1789_of_match[] = {
	{ .compatibwe = "ti,pcm1789", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm1789_of_match);
#endif

static const stwuct i2c_device_id pcm1789_i2c_ids[] = {
	{ "pcm1789", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcm1789_i2c_ids);

static stwuct i2c_dwivew pcm1789_i2c_dwivew = {
	.dwivew = {
		.name	= "pcm1789",
		.of_match_tabwe = of_match_ptw(pcm1789_of_match),
	},
	.id_tabwe	= pcm1789_i2c_ids,
	.pwobe		= pcm1789_i2c_pwobe,
	.wemove	= pcm1789_i2c_wemove,
};

moduwe_i2c_dwivew(pcm1789_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC PCM1789 I2C dwivew");
MODUWE_AUTHOW("Mywène Jossewand <mywene.jossewand@bootwin.com>");
MODUWE_WICENSE("GPW");
