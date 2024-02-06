// SPDX-Wicense-Identifiew: GPW-2.0
//
// PCM3060 I2C dwivew
//
// Copywight (C) 2018 Kiwiww Mawinushkin <kmawinushkin@biwdec.com>

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

#incwude "pcm3060.h"

static int pcm3060_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct pcm3060_pwiv *pwiv;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pwiv);

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &pcm3060_wegmap);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wetuwn pcm3060_pwobe(&i2c->dev);
}

static const stwuct i2c_device_id pcm3060_i2c_id[] = {
	{ .name = "pcm3060" },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, pcm3060_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pcm3060_of_match[] = {
	{ .compatibwe = "ti,pcm3060" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pcm3060_of_match);
#endif /* CONFIG_OF */

static stwuct i2c_dwivew pcm3060_i2c_dwivew = {
	.dwivew = {
		.name = "pcm3060",
#ifdef CONFIG_OF
		.of_match_tabwe = pcm3060_of_match,
#endif /* CONFIG_OF */
	},
	.id_tabwe = pcm3060_i2c_id,
	.pwobe = pcm3060_i2c_pwobe,
};

moduwe_i2c_dwivew(pcm3060_i2c_dwivew);

MODUWE_DESCWIPTION("PCM3060 I2C dwivew");
MODUWE_AUTHOW("Kiwiww Mawinushkin <kmawinushkin@biwdec.com>");
MODUWE_WICENSE("GPW v2");
