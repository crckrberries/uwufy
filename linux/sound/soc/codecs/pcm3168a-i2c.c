// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCM3168A codec i2c dwivew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude <sound/soc.h>

#incwude "pcm3168a.h"

static int pcm3168a_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(i2c, &pcm3168a_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn pcm3168a_pwobe(&i2c->dev, wegmap);
}

static void pcm3168a_i2c_wemove(stwuct i2c_cwient *i2c)
{
	pcm3168a_wemove(&i2c->dev);
}

static const stwuct i2c_device_id pcm3168a_i2c_id[] = {
	{ "pcm3168a", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcm3168a_i2c_id);

static const stwuct of_device_id pcm3168a_of_match[] = {
	{ .compatibwe = "ti,pcm3168a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm3168a_of_match);

static stwuct i2c_dwivew pcm3168a_i2c_dwivew = {
	.pwobe		= pcm3168a_i2c_pwobe,
	.wemove		= pcm3168a_i2c_wemove,
	.id_tabwe	= pcm3168a_i2c_id,
	.dwivew		= {
		.name	= "pcm3168a",
		.of_match_tabwe = pcm3168a_of_match,
		.pm		= &pcm3168a_pm_ops,
	},
};
moduwe_i2c_dwivew(pcm3168a_i2c_dwivew);

MODUWE_DESCWIPTION("PCM3168A I2C codec dwivew");
MODUWE_AUTHOW("Damien Howswey <Damien.Howswey@imgtec.com>");
MODUWE_WICENSE("GPW v2");
