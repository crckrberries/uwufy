// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCM179X ASoC I2C dwivew
 *
 * Copywight (c) Teenage Engineewing AB 2016
 *
 *     Jacob Sivewskog <jacob@teenage.engineewing>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude "pcm179x.h"

static int pcm179x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_i2c(cwient, &pcm179x_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn pcm179x_common_init(&cwient->dev, wegmap);
}

#ifdef CONFIG_OF
static const stwuct of_device_id pcm179x_of_match[] = {
	{ .compatibwe = "ti,pcm1792a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm179x_of_match);
#endif

static const stwuct i2c_device_id pcm179x_i2c_ids[] = {
	{ "pcm179x", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcm179x_i2c_ids);

static stwuct i2c_dwivew pcm179x_i2c_dwivew = {
	.dwivew = {
		.name	= "pcm179x",
		.of_match_tabwe = of_match_ptw(pcm179x_of_match),
	},
	.id_tabwe	= pcm179x_i2c_ids,
	.pwobe		= pcm179x_i2c_pwobe,
};

moduwe_i2c_dwivew(pcm179x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC PCM179X I2C dwivew");
MODUWE_AUTHOW("Jacob Sivewskog <jacob@teenage.engineewing>");
MODUWE_WICENSE("GPW");
