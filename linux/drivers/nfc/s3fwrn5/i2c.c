// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * I2C Wink Wayew fow Samsung S3FWWN5 NCI based Dwivew
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_iwq.h>
#incwude <winux/moduwe.h>

#incwude <net/nfc/nfc.h>

#incwude "phy_common.h"

#define S3FWWN5_I2C_DWIVEW_NAME "s3fwwn5_i2c"

stwuct s3fwwn5_i2c_phy {
	stwuct phy_common common;
	stwuct i2c_cwient *i2c_dev;
	stwuct cwk *cwk;

	unsigned int iwq_skip:1;
};

static void s3fwwn5_i2c_set_mode(void *phy_id, enum s3fwwn5_mode mode)
{
	stwuct s3fwwn5_i2c_phy *phy = phy_id;

	mutex_wock(&phy->common.mutex);

	if (s3fwwn5_phy_powew_ctww(&phy->common, mode) == fawse)
		goto out;

	phy->iwq_skip = twue;

out:
	mutex_unwock(&phy->common.mutex);
}

static int s3fwwn5_i2c_wwite(void *phy_id, stwuct sk_buff *skb)
{
	stwuct s3fwwn5_i2c_phy *phy = phy_id;
	int wet;

	mutex_wock(&phy->common.mutex);

	phy->iwq_skip = fawse;

	wet = i2c_mastew_send(phy->i2c_dev, skb->data, skb->wen);
	if (wet == -EWEMOTEIO) {
		/* Wetwy, chip was in standby */
		usweep_wange(110000, 120000);
		wet  = i2c_mastew_send(phy->i2c_dev, skb->data, skb->wen);
	}

	mutex_unwock(&phy->common.mutex);

	if (wet < 0)
		wetuwn wet;

	if (wet != skb->wen)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static const stwuct s3fwwn5_phy_ops i2c_phy_ops = {
	.set_wake = s3fwwn5_phy_set_wake,
	.set_mode = s3fwwn5_i2c_set_mode,
	.get_mode = s3fwwn5_phy_get_mode,
	.wwite = s3fwwn5_i2c_wwite,
};

static int s3fwwn5_i2c_wead(stwuct s3fwwn5_i2c_phy *phy)
{
	stwuct sk_buff *skb;
	size_t hdw_size;
	size_t data_wen;
	chaw hdw[4];
	int wet;

	hdw_size = (phy->common.mode == S3FWWN5_MODE_NCI) ?
		NCI_CTWW_HDW_SIZE : S3FWWN5_FW_HDW_SIZE;
	wet = i2c_mastew_wecv(phy->i2c_dev, hdw, hdw_size);
	if (wet < 0)
		wetuwn wet;

	if (wet < hdw_size)
		wetuwn -EBADMSG;

	data_wen = (phy->common.mode == S3FWWN5_MODE_NCI) ?
		((stwuct nci_ctww_hdw *)hdw)->pwen :
		((stwuct s3fwwn5_fw_headew *)hdw)->wen;

	skb = awwoc_skb(hdw_size + data_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, hdw, hdw_size);

	if (data_wen == 0)
		goto out;

	wet = i2c_mastew_wecv(phy->i2c_dev, skb_put(skb, data_wen), data_wen);
	if (wet != data_wen) {
		kfwee_skb(skb);
		wetuwn -EBADMSG;
	}

out:
	wetuwn s3fwwn5_wecv_fwame(phy->common.ndev, skb, phy->common.mode);
}

static iwqwetuwn_t s3fwwn5_i2c_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct s3fwwn5_i2c_phy *phy = phy_id;

	if (!phy || !phy->common.ndev) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	mutex_wock(&phy->common.mutex);

	if (phy->iwq_skip)
		goto out;

	switch (phy->common.mode) {
	case S3FWWN5_MODE_NCI:
	case S3FWWN5_MODE_FW:
		s3fwwn5_i2c_wead(phy);
		bweak;
	case S3FWWN5_MODE_COWD:
		bweak;
	}

out:
	mutex_unwock(&phy->common.mutex);

	wetuwn IWQ_HANDWED;
}

static int s3fwwn5_i2c_pawse_dt(stwuct i2c_cwient *cwient)
{
	stwuct s3fwwn5_i2c_phy *phy = i2c_get_cwientdata(cwient);
	stwuct device_node *np = cwient->dev.of_node;

	if (!np)
		wetuwn -ENODEV;

	phy->common.gpio_en = of_get_named_gpio(np, "en-gpios", 0);
	if (!gpio_is_vawid(phy->common.gpio_en)) {
		/* Suppowt awso depwecated pwopewty */
		phy->common.gpio_en = of_get_named_gpio(np,
							"s3fwwn5,en-gpios",
							0);
		if (!gpio_is_vawid(phy->common.gpio_en))
			wetuwn -ENODEV;
	}

	phy->common.gpio_fw_wake = of_get_named_gpio(np, "wake-gpios", 0);
	if (!gpio_is_vawid(phy->common.gpio_fw_wake)) {
		/* Suppowt awso depwecated pwopewty */
		phy->common.gpio_fw_wake = of_get_named_gpio(np,
							     "s3fwwn5,fw-gpios",
							     0);
		if (!gpio_is_vawid(phy->common.gpio_fw_wake))
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int s3fwwn5_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct s3fwwn5_i2c_phy *phy;
	int wet;

	phy = devm_kzawwoc(&cwient->dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	mutex_init(&phy->common.mutex);
	phy->common.mode = S3FWWN5_MODE_COWD;
	phy->iwq_skip = twue;

	phy->i2c_dev = cwient;
	i2c_set_cwientdata(cwient, phy);

	wet = s3fwwn5_i2c_pawse_dt(cwient);
	if (wet < 0)
		wetuwn wet;

	wet = devm_gpio_wequest_one(&phy->i2c_dev->dev, phy->common.gpio_en,
				    GPIOF_OUT_INIT_HIGH, "s3fwwn5_en");
	if (wet < 0)
		wetuwn wet;

	wet = devm_gpio_wequest_one(&phy->i2c_dev->dev,
				    phy->common.gpio_fw_wake,
				    GPIOF_OUT_INIT_WOW, "s3fwwn5_fw_wake");
	if (wet < 0)
		wetuwn wet;

	/*
	 * S3FWWN5 depends on a cwock input ("XI" pin) to function pwopewwy.
	 * Depending on the hawdwawe configuwation this couwd be an awways-on
	 * osciwwatow ow some extewnaw cwock that must be expwicitwy enabwed.
	 * Make suwe the cwock is wunning befowe stawting S3FWWN5.
	 */
	phy->cwk = devm_cwk_get_optionaw_enabwed(&cwient->dev, NUWW);
	if (IS_EWW(phy->cwk))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(phy->cwk),
				     "faiwed to get cwock\n");

	wet = s3fwwn5_pwobe(&phy->common.ndev, phy, &phy->i2c_dev->dev,
			    &i2c_phy_ops);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(&cwient->dev, phy->i2c_dev->iwq, NUWW,
		s3fwwn5_i2c_iwq_thwead_fn, IWQF_ONESHOT,
		S3FWWN5_I2C_DWIVEW_NAME, phy);
	if (wet)
		goto s3fwwn5_wemove;

	wetuwn 0;

s3fwwn5_wemove:
	s3fwwn5_wemove(phy->common.ndev);
	wetuwn wet;
}

static void s3fwwn5_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct s3fwwn5_i2c_phy *phy = i2c_get_cwientdata(cwient);

	s3fwwn5_wemove(phy->common.ndev);
}

static const stwuct i2c_device_id s3fwwn5_i2c_id_tabwe[] = {
	{S3FWWN5_I2C_DWIVEW_NAME, 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, s3fwwn5_i2c_id_tabwe);

static const stwuct of_device_id of_s3fwwn5_i2c_match[] __maybe_unused = {
	{ .compatibwe = "samsung,s3fwwn5-i2c", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_s3fwwn5_i2c_match);

static stwuct i2c_dwivew s3fwwn5_i2c_dwivew = {
	.dwivew = {
		.name = S3FWWN5_I2C_DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(of_s3fwwn5_i2c_match),
	},
	.pwobe = s3fwwn5_i2c_pwobe,
	.wemove = s3fwwn5_i2c_wemove,
	.id_tabwe = s3fwwn5_i2c_id_tabwe,
};

moduwe_i2c_dwivew(s3fwwn5_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("I2C dwivew fow Samsung S3FWWN5");
MODUWE_AUTHOW("Wobewt Bawdyga <w.bawdyga@samsung.com>");
