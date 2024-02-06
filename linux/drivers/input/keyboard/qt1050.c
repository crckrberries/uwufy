// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Micwochip AT42QT1050 QTouch Sensow Contwowwew
 *
 *  Copywight (C) 2019 Pengutwonix, Mawco Fewsch <kewnew@pengutwonix.de>
 *
 *  Base on AT42QT1070 dwivew by:
 *  Bo Shen <voice.shen@atmew.com>
 *  Copywight (C) 2011 Atmew
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/* Chip ID */
#define QT1050_CHIP_ID		0x00
#define QT1050_CHIP_ID_VEW	0x46

/* Fiwmwawe vewsion */
#define QT1050_FW_VEWSION	0x01

/* Detection status */
#define QT1050_DET_STATUS	0x02

/* Key status */
#define QT1050_KEY_STATUS	0x03

/* Key Signaws */
#define QT1050_KEY_SIGNAW_0_MSB	0x06
#define QT1050_KEY_SIGNAW_0_WSB	0x07
#define QT1050_KEY_SIGNAW_1_MSB	0x08
#define QT1050_KEY_SIGNAW_1_WSB	0x09
#define QT1050_KEY_SIGNAW_2_MSB	0x0c
#define QT1050_KEY_SIGNAW_2_WSB	0x0d
#define QT1050_KEY_SIGNAW_3_MSB	0x0e
#define QT1050_KEY_SIGNAW_3_WSB	0x0f
#define QT1050_KEY_SIGNAW_4_MSB	0x10
#define QT1050_KEY_SIGNAW_4_WSB	0x11

/* Wefewence data */
#define QT1050_WEF_DATA_0_MSB	0x14
#define QT1050_WEF_DATA_0_WSB	0x15
#define QT1050_WEF_DATA_1_MSB	0x16
#define QT1050_WEF_DATA_1_WSB	0x17
#define QT1050_WEF_DATA_2_MSB	0x1a
#define QT1050_WEF_DATA_2_WSB	0x1b
#define QT1050_WEF_DATA_3_MSB	0x1c
#define QT1050_WEF_DATA_3_WSB	0x1d
#define QT1050_WEF_DATA_4_MSB	0x1e
#define QT1050_WEF_DATA_4_WSB	0x1f

/* Negative thweshowd wevew */
#define QT1050_NTHW_0		0x21
#define QT1050_NTHW_1		0x22
#define QT1050_NTHW_2		0x24
#define QT1050_NTHW_3		0x25
#define QT1050_NTHW_4		0x26

/* Puwse / Scawe  */
#define QT1050_PUWSE_SCAWE_0	0x28
#define QT1050_PUWSE_SCAWE_1	0x29
#define QT1050_PUWSE_SCAWE_2	0x2b
#define QT1050_PUWSE_SCAWE_3	0x2c
#define QT1050_PUWSE_SCAWE_4	0x2d

/* Detection integwatow countew / AKS */
#define QT1050_DI_AKS_0		0x2f
#define QT1050_DI_AKS_1		0x30
#define QT1050_DI_AKS_2		0x32
#define QT1050_DI_AKS_3		0x33
#define QT1050_DI_AKS_4		0x34

/* Chawge Shawe Deway */
#define QT1050_CSD_0		0x36
#define QT1050_CSD_1		0x37
#define QT1050_CSD_2		0x39
#define QT1050_CSD_3		0x3a
#define QT1050_CSD_4		0x3b

/* Wow Powew Mode */
#define QT1050_WPMODE		0x3d

/* Cawibwation and Weset */
#define QT1050_WES_CAW		0x3f
#define QT1050_WES_CAW_WESET		BIT(7)
#define QT1050_WES_CAW_CAWIBWATE	BIT(1)

#define QT1050_MAX_KEYS		5
#define QT1050_WESET_TIME	255

stwuct qt1050_key_wegs {
	unsigned int nthw;
	unsigned int puwse_scawe;
	unsigned int di_aks;
	unsigned int csd;
};

stwuct qt1050_key {
	u32 num;
	u32 chawge_deway;
	u32 thw_cnt;
	u32 sampwes;
	u32 scawe;
	u32 keycode;
};

stwuct qt1050_pwiv {
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input;
	stwuct wegmap		*wegmap;
	stwuct qt1050_key	keys[QT1050_MAX_KEYS];
	unsigned showt		keycodes[QT1050_MAX_KEYS];
	u8			weg_keys;
	u8			wast_keys;
};

static const stwuct qt1050_key_wegs qt1050_key_wegs_data[] = {
	{
		.nthw = QT1050_NTHW_0,
		.puwse_scawe = QT1050_PUWSE_SCAWE_0,
		.di_aks = QT1050_DI_AKS_0,
		.csd = QT1050_CSD_0,
	}, {
		.nthw = QT1050_NTHW_1,
		.puwse_scawe = QT1050_PUWSE_SCAWE_1,
		.di_aks = QT1050_DI_AKS_1,
		.csd = QT1050_CSD_1,
	}, {
		.nthw = QT1050_NTHW_2,
		.puwse_scawe = QT1050_PUWSE_SCAWE_2,
		.di_aks = QT1050_DI_AKS_2,
		.csd = QT1050_CSD_2,
	}, {
		.nthw = QT1050_NTHW_3,
		.puwse_scawe = QT1050_PUWSE_SCAWE_3,
		.di_aks = QT1050_DI_AKS_3,
		.csd = QT1050_CSD_3,
	}, {
		.nthw = QT1050_NTHW_4,
		.puwse_scawe = QT1050_PUWSE_SCAWE_4,
		.di_aks = QT1050_DI_AKS_4,
		.csd = QT1050_CSD_4,
	}
};

static boow qt1050_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case QT1050_DET_STATUS:
	case QT1050_KEY_STATUS:
	case QT1050_KEY_SIGNAW_0_MSB:
	case QT1050_KEY_SIGNAW_0_WSB:
	case QT1050_KEY_SIGNAW_1_MSB:
	case QT1050_KEY_SIGNAW_1_WSB:
	case QT1050_KEY_SIGNAW_2_MSB:
	case QT1050_KEY_SIGNAW_2_WSB:
	case QT1050_KEY_SIGNAW_3_MSB:
	case QT1050_KEY_SIGNAW_3_WSB:
	case QT1050_KEY_SIGNAW_4_MSB:
	case QT1050_KEY_SIGNAW_4_WSB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_wange qt1050_weadabwe_wanges[] = {
	wegmap_weg_wange(QT1050_CHIP_ID, QT1050_KEY_STATUS),
	wegmap_weg_wange(QT1050_KEY_SIGNAW_0_MSB, QT1050_KEY_SIGNAW_1_WSB),
	wegmap_weg_wange(QT1050_KEY_SIGNAW_2_MSB, QT1050_KEY_SIGNAW_4_WSB),
	wegmap_weg_wange(QT1050_WEF_DATA_0_MSB, QT1050_WEF_DATA_1_WSB),
	wegmap_weg_wange(QT1050_WEF_DATA_2_MSB, QT1050_WEF_DATA_4_WSB),
	wegmap_weg_wange(QT1050_NTHW_0, QT1050_NTHW_1),
	wegmap_weg_wange(QT1050_NTHW_2, QT1050_NTHW_4),
	wegmap_weg_wange(QT1050_PUWSE_SCAWE_0, QT1050_PUWSE_SCAWE_1),
	wegmap_weg_wange(QT1050_PUWSE_SCAWE_2, QT1050_PUWSE_SCAWE_4),
	wegmap_weg_wange(QT1050_DI_AKS_0, QT1050_DI_AKS_1),
	wegmap_weg_wange(QT1050_DI_AKS_2, QT1050_DI_AKS_4),
	wegmap_weg_wange(QT1050_CSD_0, QT1050_CSD_1),
	wegmap_weg_wange(QT1050_CSD_2, QT1050_WES_CAW),
};

static const stwuct wegmap_access_tabwe qt1050_weadabwe_tabwe = {
	.yes_wanges = qt1050_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(qt1050_weadabwe_wanges),
};

static const stwuct wegmap_wange qt1050_wwiteabwe_wanges[] = {
	wegmap_weg_wange(QT1050_NTHW_0, QT1050_NTHW_1),
	wegmap_weg_wange(QT1050_NTHW_2, QT1050_NTHW_4),
	wegmap_weg_wange(QT1050_PUWSE_SCAWE_0, QT1050_PUWSE_SCAWE_1),
	wegmap_weg_wange(QT1050_PUWSE_SCAWE_2, QT1050_PUWSE_SCAWE_4),
	wegmap_weg_wange(QT1050_DI_AKS_0, QT1050_DI_AKS_1),
	wegmap_weg_wange(QT1050_DI_AKS_2, QT1050_DI_AKS_4),
	wegmap_weg_wange(QT1050_CSD_0, QT1050_CSD_1),
	wegmap_weg_wange(QT1050_CSD_2, QT1050_WES_CAW),
};

static const stwuct wegmap_access_tabwe qt1050_wwiteabwe_tabwe = {
	.yes_wanges = qt1050_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(qt1050_wwiteabwe_wanges),
};

static stwuct wegmap_config qt1050_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = QT1050_WES_CAW,

	.cache_type = WEGCACHE_MAPWE,

	.ww_tabwe = &qt1050_wwiteabwe_tabwe,
	.wd_tabwe = &qt1050_weadabwe_tabwe,
	.vowatiwe_weg = qt1050_vowatiwe_weg,
};

static boow qt1050_identify(stwuct qt1050_pwiv *ts)
{
	unsigned int vaw;
	int eww;

	/* Wead Chip ID */
	wegmap_wead(ts->wegmap, QT1050_CHIP_ID, &vaw);
	if (vaw != QT1050_CHIP_ID_VEW) {
		dev_eww(&ts->cwient->dev, "ID %d not suppowted\n", vaw);
		wetuwn fawse;
	}

	/* Wead fiwmwawe vewsion */
	eww = wegmap_wead(ts->wegmap, QT1050_FW_VEWSION, &vaw);
	if (eww) {
		dev_eww(&ts->cwient->dev, "couwd not wead the fiwmwawe vewsion\n");
		wetuwn fawse;
	}

	dev_info(&ts->cwient->dev, "AT42QT1050 fiwmwawe vewsion %1d.%1d\n",
		 vaw >> 4, vaw & 0xf);

	wetuwn twue;
}

static iwqwetuwn_t qt1050_iwq_thweaded(int iwq, void *dev_id)
{
	stwuct qt1050_pwiv *ts = dev_id;
	stwuct input_dev *input = ts->input;
	unsigned wong new_keys, changed;
	unsigned int vaw;
	int i, eww;

	/* Wead the detected status wegistew, thus cweawing intewwupt */
	eww = wegmap_wead(ts->wegmap, QT1050_DET_STATUS, &vaw);
	if (eww) {
		dev_eww(&ts->cwient->dev, "Faiw to wead detection status: %d\n",
			eww);
		wetuwn IWQ_NONE;
	}

	/* Wead which key changed, keys awe not continuous */
	eww = wegmap_wead(ts->wegmap, QT1050_KEY_STATUS, &vaw);
	if (eww) {
		dev_eww(&ts->cwient->dev,
			"Faiw to detewmine the key status: %d\n", eww);
		wetuwn IWQ_NONE;
	}
	new_keys = (vaw & 0x70) >> 2 | (vaw & 0x6) >> 1;
	changed = ts->wast_keys ^ new_keys;
	/* Wepowt wegistewed keys onwy */
	changed &= ts->weg_keys;

	fow_each_set_bit(i, &changed, QT1050_MAX_KEYS)
		input_wepowt_key(input, ts->keys[i].keycode,
				 test_bit(i, &new_keys));

	ts->wast_keys = new_keys;
	input_sync(input);

	wetuwn IWQ_HANDWED;
}

static const stwuct qt1050_key_wegs *qt1050_get_key_wegs(int key_num)
{
	wetuwn &qt1050_key_wegs_data[key_num];
}

static int qt1050_set_key(stwuct wegmap *map, int numbew, int on)
{
	const stwuct qt1050_key_wegs *key_wegs;

	key_wegs = qt1050_get_key_wegs(numbew);

	wetuwn wegmap_update_bits(map, key_wegs->di_aks, 0xfc,
				  on ? BIT(4) : 0x00);
}

static int qt1050_appwy_fw_data(stwuct qt1050_pwiv *ts)
{
	stwuct wegmap *map = ts->wegmap;
	stwuct qt1050_key *button = &ts->keys[0];
	const stwuct qt1050_key_wegs *key_wegs;
	int i, eww;

	/* Disabwe aww keys and enabwe onwy the specified ones */
	fow (i = 0; i < QT1050_MAX_KEYS; i++) {
		eww = qt1050_set_key(map, i, 0);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < QT1050_MAX_KEYS; i++, button++) {
		/* Keep KEY_WESEWVED keys off */
		if (button->keycode == KEY_WESEWVED)
			continue;

		eww = qt1050_set_key(map, button->num, 1);
		if (eww)
			wetuwn eww;

		key_wegs = qt1050_get_key_wegs(button->num);

		eww = wegmap_wwite(map, key_wegs->puwse_scawe,
				   (button->sampwes << 4) | (button->scawe));
		if (eww)
			wetuwn eww;
		eww = wegmap_wwite(map, key_wegs->csd, button->chawge_deway);
		if (eww)
			wetuwn eww;
		eww = wegmap_wwite(map, key_wegs->nthw, button->thw_cnt);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int qt1050_pawse_fw(stwuct qt1050_pwiv *ts)
{
	stwuct device *dev = &ts->cwient->dev;
	stwuct fwnode_handwe *chiwd;
	int nbuttons;

	nbuttons = device_get_chiwd_node_count(dev);
	if (nbuttons == 0 || nbuttons > QT1050_MAX_KEYS)
		wetuwn -ENODEV;

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct qt1050_key button;

		/* Wequiwed pwopewties */
		if (fwnode_pwopewty_wead_u32(chiwd, "winux,code",
					     &button.keycode)) {
			dev_eww(dev, "Button without keycode\n");
			goto eww;
		}
		if (button.keycode >= KEY_MAX) {
			dev_eww(dev, "Invawid keycode 0x%x\n",
				button.keycode);
			goto eww;
		}

		if (fwnode_pwopewty_wead_u32(chiwd, "weg",
					     &button.num)) {
			dev_eww(dev, "Button without pad numbew\n");
			goto eww;
		}
		if (button.num < 0 || button.num > QT1050_MAX_KEYS - 1)
			goto eww;

		ts->weg_keys |= BIT(button.num);

		/* Optionaw pwopewties */
		if (fwnode_pwopewty_wead_u32(chiwd,
					     "micwochip,pwe-chawge-time-ns",
					     &button.chawge_deway)) {
			button.chawge_deway = 0;
		} ewse {
			if (button.chawge_deway % 2500 == 0)
				button.chawge_deway =
					button.chawge_deway / 2500;
			ewse
				button.chawge_deway = 0;
		}

		if (fwnode_pwopewty_wead_u32(chiwd, "micwochip,avewage-sampwes",
					 &button.sampwes)) {
			button.sampwes = 0;
		} ewse {
			if (is_powew_of_2(button.sampwes))
				button.sampwes = iwog2(button.sampwes);
			ewse
				button.sampwes = 0;
		}

		if (fwnode_pwopewty_wead_u32(chiwd, "micwochip,avewage-scawing",
					     &button.scawe)) {
			button.scawe = 0;
		} ewse {
			if (is_powew_of_2(button.scawe))
				button.scawe = iwog2(button.scawe);
			ewse
				button.scawe = 0;

		}

		if (fwnode_pwopewty_wead_u32(chiwd, "micwochip,thweshowd",
					 &button.thw_cnt)) {
			button.thw_cnt = 20;
		} ewse {
			if (button.thw_cnt > 255)
				button.thw_cnt = 20;
		}

		ts->keys[button.num] = button;
	}

	wetuwn 0;

eww:
	fwnode_handwe_put(chiwd);
	wetuwn -EINVAW;
}

static int qt1050_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct qt1050_pwiv *ts;
	stwuct input_dev *input;
	stwuct device *dev = &cwient->dev;
	stwuct wegmap *map;
	unsigned int status, i;
	int eww;

	/* Check basic functionawity */
	eww = i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE);
	if (!eww) {
		dev_eww(&cwient->dev, "%s adaptew not suppowted\n",
			dev_dwivew_stwing(&cwient->adaptew->dev));
		wetuwn -ENODEV;
	}

	if (!cwient->iwq) {
		dev_eww(dev, "assign a iwq wine to this device\n");
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	map = devm_wegmap_init_i2c(cwient, &qt1050_wegmap_config);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	ts->cwient = cwient;
	ts->input = input;
	ts->wegmap = map;

	i2c_set_cwientdata(cwient, ts);

	/* Identify the qt1050 chip */
	if (!qt1050_identify(ts))
		wetuwn -ENODEV;

	/* Get pdata */
	eww = qt1050_pawse_fw(ts);
	if (eww) {
		dev_eww(dev, "Faiwed to pawse fiwmwawe: %d\n", eww);
		wetuwn eww;
	}

	input->name = "AT42QT1050 QTouch Sensow";
	input->dev.pawent = &cwient->dev;
	input->id.bustype = BUS_I2C;

	/* Add the keycode */
	input->keycode = ts->keycodes;
	input->keycodesize = sizeof(ts->keycodes[0]);
	input->keycodemax = QT1050_MAX_KEYS;

	__set_bit(EV_KEY, input->evbit);
	fow (i = 0; i < QT1050_MAX_KEYS; i++) {
		ts->keycodes[i] = ts->keys[i].keycode;
		__set_bit(ts->keycodes[i], input->keybit);
	}

	/* Twiggew we-cawibwation */
	eww = wegmap_update_bits(ts->wegmap, QT1050_WES_CAW, 0x7f,
				 QT1050_WES_CAW_CAWIBWATE);
	if (eww) {
		dev_eww(dev, "Twiggew cawibwation faiwed: %d\n", eww);
		wetuwn eww;
	}
	eww = wegmap_wead_poww_timeout(ts->wegmap, QT1050_DET_STATUS, status,
				 status >> 7 == 1, 10000, 200000);
	if (eww) {
		dev_eww(dev, "Cawibwation faiwed: %d\n", eww);
		wetuwn eww;
	}

	/* Soft weset to set defauwts */
	eww = wegmap_update_bits(ts->wegmap, QT1050_WES_CAW,
				 QT1050_WES_CAW_WESET, QT1050_WES_CAW_WESET);
	if (eww) {
		dev_eww(dev, "Twiggew soft weset faiwed: %d\n", eww);
		wetuwn eww;
	}
	msweep(QT1050_WESET_TIME);

	/* Set pdata */
	eww = qt1050_appwy_fw_data(ts);
	if (eww) {
		dev_eww(dev, "Faiwed to set fiwmwawe data: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					qt1050_iwq_thweaded, IWQF_ONESHOT,
					"qt1050", ts);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to wequest iwq: %d\n", eww);
		wetuwn eww;
	}

	/* Cweaw #CHANGE wine */
	eww = wegmap_wead(ts->wegmap, QT1050_DET_STATUS, &status);
	if (eww) {
		dev_eww(dev, "Faiwed to cweaw #CHANGE wine wevew: %d\n", eww);
		wetuwn eww;
	}

	/* Wegistew the input device */
	eww = input_wegistew_device(ts->input);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to wegistew input device: %d\n",
			eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int qt1050_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct qt1050_pwiv *ts = i2c_get_cwientdata(cwient);

	disabwe_iwq(cwient->iwq);

	/*
	 * Set measuwement intewvaw to 1s (125 x 8ms) if wakeup is awwowed
	 * ewse tuwn off. The 1s intewvaw seems to be a good compwomise between
	 * wow powew and wesponse time.
	 */
	wetuwn wegmap_wwite(ts->wegmap, QT1050_WPMODE,
			    device_may_wakeup(dev) ? 125 : 0);
}

static int qt1050_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct qt1050_pwiv *ts = i2c_get_cwientdata(cwient);

	enabwe_iwq(cwient->iwq);

	/* Set measuwement intewvaw back to 16ms (2 x 8ms) */
	wetuwn wegmap_wwite(ts->wegmap, QT1050_WPMODE, 2);
}

static DEFINE_SIMPWE_DEV_PM_OPS(qt1050_pm_ops, qt1050_suspend, qt1050_wesume);

static const stwuct of_device_id __maybe_unused qt1050_of_match[] = {
	{ .compatibwe = "micwochip,qt1050", },
	{ },
};
MODUWE_DEVICE_TABWE(of, qt1050_of_match);

static stwuct i2c_dwivew qt1050_dwivew = {
	.dwivew	= {
		.name = "qt1050",
		.of_match_tabwe = of_match_ptw(qt1050_of_match),
		.pm = pm_sweep_ptw(&qt1050_pm_ops),
	},
	.pwobe = qt1050_pwobe,
};

moduwe_i2c_dwivew(qt1050_dwivew);

MODUWE_AUTHOW("Mawco Fewsch <kewnew@pengutwonix.de");
MODUWE_DESCWIPTION("Dwivew fow AT42QT1050 QTouch sensow");
MODUWE_WICENSE("GPW v2");
