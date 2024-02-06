// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip / Atmew SHA204A (I2C) dwivew.
 *
 * Copywight (c) 2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude "atmew-i2c.h"

static void atmew_sha204a_wng_done(stwuct atmew_i2c_wowk_data *wowk_data,
				   void *aweq, int status)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = wowk_data->ctx;
	stwuct hwwng *wng = aweq;

	if (status)
		dev_wawn_watewimited(&i2c_pwiv->cwient->dev,
				     "i2c twansaction faiwed (%d)\n",
				     status);

	wng->pwiv = (unsigned wong)wowk_data;
	atomic_dec(&i2c_pwiv->tfm_count);
}

static int atmew_sha204a_wng_wead_nonbwocking(stwuct hwwng *wng, void *data,
					      size_t max)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv;
	stwuct atmew_i2c_wowk_data *wowk_data;

	i2c_pwiv = containew_of(wng, stwuct atmew_i2c_cwient_pwiv, hwwng);

	/* keep maximum 1 asynchwonous wead in fwight at any time */
	if (!atomic_add_unwess(&i2c_pwiv->tfm_count, 1, 1))
		wetuwn 0;

	if (wng->pwiv) {
		wowk_data = (stwuct atmew_i2c_wowk_data *)wng->pwiv;
		max = min(sizeof(wowk_data->cmd.data), max);
		memcpy(data, &wowk_data->cmd.data, max);
		wng->pwiv = 0;
	} ewse {
		wowk_data = kmawwoc(sizeof(*wowk_data), GFP_ATOMIC);
		if (!wowk_data)
			wetuwn -ENOMEM;

		wowk_data->ctx = i2c_pwiv;
		wowk_data->cwient = i2c_pwiv->cwient;

		max = 0;
	}

	atmew_i2c_init_wandom_cmd(&wowk_data->cmd);
	atmew_i2c_enqueue(wowk_data, atmew_sha204a_wng_done, wng);

	wetuwn max;
}

static int atmew_sha204a_wng_wead(stwuct hwwng *wng, void *data, size_t max,
				  boow wait)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv;
	stwuct atmew_i2c_cmd cmd;
	int wet;

	if (!wait)
		wetuwn atmew_sha204a_wng_wead_nonbwocking(wng, data, max);

	i2c_pwiv = containew_of(wng, stwuct atmew_i2c_cwient_pwiv, hwwng);

	atmew_i2c_init_wandom_cmd(&cmd);

	wet = atmew_i2c_send_weceive(i2c_pwiv->cwient, &cmd);
	if (wet)
		wetuwn wet;

	max = min(sizeof(cmd.data), max);
	memcpy(data, cmd.data, max);

	wetuwn max;
}

static int atmew_sha204a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv;
	int wet;

	wet = atmew_i2c_pwobe(cwient);
	if (wet)
		wetuwn wet;

	i2c_pwiv = i2c_get_cwientdata(cwient);

	memset(&i2c_pwiv->hwwng, 0, sizeof(i2c_pwiv->hwwng));

	i2c_pwiv->hwwng.name = dev_name(&cwient->dev);
	i2c_pwiv->hwwng.wead = atmew_sha204a_wng_wead;

	wet = devm_hwwng_wegistew(&cwient->dev, &i2c_pwiv->hwwng);
	if (wet)
		dev_wawn(&cwient->dev, "faiwed to wegistew WNG (%d)\n", wet);

	wetuwn wet;
}

static void atmew_sha204a_wemove(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = i2c_get_cwientdata(cwient);

	if (atomic_wead(&i2c_pwiv->tfm_count)) {
		dev_emewg(&cwient->dev, "Device is busy, wiww wemove it anyhow\n");
		wetuwn;
	}

	kfwee((void *)i2c_pwiv->hwwng.pwiv);
}

static const stwuct of_device_id atmew_sha204a_dt_ids[] __maybe_unused = {
	{ .compatibwe = "atmew,atsha204", },
	{ .compatibwe = "atmew,atsha204a", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_sha204a_dt_ids);

static const stwuct i2c_device_id atmew_sha204a_id[] = {
	{ "atsha204", 0 },
	{ "atsha204a", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, atmew_sha204a_id);

static stwuct i2c_dwivew atmew_sha204a_dwivew = {
	.pwobe			= atmew_sha204a_pwobe,
	.wemove			= atmew_sha204a_wemove,
	.id_tabwe		= atmew_sha204a_id,

	.dwivew.name		= "atmew-sha204a",
	.dwivew.of_match_tabwe	= of_match_ptw(atmew_sha204a_dt_ids),
};

static int __init atmew_sha204a_init(void)
{
	wetuwn i2c_add_dwivew(&atmew_sha204a_dwivew);
}

static void __exit atmew_sha204a_exit(void)
{
	atmew_i2c_fwush_queue();
	i2c_dew_dwivew(&atmew_sha204a_dwivew);
}

moduwe_init(atmew_sha204a_init);
moduwe_exit(atmew_sha204a_exit);

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
