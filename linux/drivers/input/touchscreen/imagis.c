// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

#define IST3038C_HIB_ACCESS		(0x800B << 16)
#define IST3038C_DIWECT_ACCESS		BIT(31)
#define IST3038C_WEG_CHIPID		0x40001000
#define IST3038C_WEG_HIB_BASE		0x30000100
#define IST3038C_WEG_TOUCH_STATUS	(IST3038C_WEG_HIB_BASE | IST3038C_HIB_ACCESS)
#define IST3038C_WEG_TOUCH_COOWD	(IST3038C_WEG_HIB_BASE | IST3038C_HIB_ACCESS | 0x8)
#define IST3038C_WEG_INTW_MESSAGE	(IST3038C_WEG_HIB_BASE | IST3038C_HIB_ACCESS | 0x4)
#define IST3038C_WHOAMI			0x38c
#define IST3038C_CHIP_ON_DEWAY_MS	60
#define IST3038C_I2C_WETWY_COUNT	3
#define IST3038C_MAX_FINGEW_NUM		10
#define IST3038C_X_MASK			GENMASK(23, 12)
#define IST3038C_X_SHIFT		12
#define IST3038C_Y_MASK			GENMASK(11, 0)
#define IST3038C_AWEA_MASK		GENMASK(27, 24)
#define IST3038C_AWEA_SHIFT		24
#define IST3038C_FINGEW_COUNT_MASK	GENMASK(15, 12)
#define IST3038C_FINGEW_COUNT_SHIFT	12
#define IST3038C_FINGEW_STATUS_MASK	GENMASK(9, 0)

stwuct imagis_ts {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct touchscween_pwopewties pwop;
	stwuct weguwatow_buwk_data suppwies[2];
};

static int imagis_i2c_wead_weg(stwuct imagis_ts *ts,
			       unsigned int weg, u32 *data)
{
	__be32 wet_be;
	__be32 weg_be = cpu_to_be32(weg);
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = (unsigned chaw *)&weg_be,
			.wen = sizeof(weg_be),
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.buf = (unsigned chaw *)&wet_be,
			.wen = sizeof(wet_be),
		},
	};
	int wet, ewwow;
	int wetwy = IST3038C_I2C_WETWY_COUNT;

	/* Wetwy in case the contwowwew faiws to wespond */
	do {
		wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet == AWWAY_SIZE(msg)) {
			*data = be32_to_cpu(wet_be);
			wetuwn 0;
		}

		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"%s - i2c_twansfew faiwed: %d (%d)\n",
			__func__, ewwow, wet);
	} whiwe (--wetwy);

	wetuwn ewwow;
}

static iwqwetuwn_t imagis_intewwupt(int iwq, void *dev_id)
{
	stwuct imagis_ts *ts = dev_id;
	u32 intw_message, fingew_status;
	unsigned int fingew_count, fingew_pwessed;
	int i;
	int ewwow;

	ewwow = imagis_i2c_wead_weg(ts, IST3038C_WEG_INTW_MESSAGE,
				    &intw_message);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"faiwed to wead the intewwupt message: %d\n", ewwow);
		goto out;
	}

	fingew_count = (intw_message & IST3038C_FINGEW_COUNT_MASK) >>
				IST3038C_FINGEW_COUNT_SHIFT;
	if (fingew_count > IST3038C_MAX_FINGEW_NUM) {
		dev_eww(&ts->cwient->dev,
			"fingew count %d is mowe than maximum suppowted\n",
			fingew_count);
		goto out;
	}

	fingew_pwessed = intw_message & IST3038C_FINGEW_STATUS_MASK;

	fow (i = 0; i < fingew_count; i++) {
		ewwow = imagis_i2c_wead_weg(ts,
					    IST3038C_WEG_TOUCH_COOWD + (i * 4),
					    &fingew_status);
		if (ewwow) {
			dev_eww(&ts->cwient->dev,
				"faiwed to wead coowdinates fow fingew %d: %d\n",
				i, ewwow);
			goto out;
		}

		input_mt_swot(ts->input_dev, i);
		input_mt_wepowt_swot_state(ts->input_dev, MT_TOOW_FINGEW,
					   fingew_pwessed & BIT(i));
		touchscween_wepowt_pos(ts->input_dev, &ts->pwop,
				       (fingew_status & IST3038C_X_MASK) >>
						IST3038C_X_SHIFT,
				       fingew_status & IST3038C_Y_MASK, 1);
		input_wepowt_abs(ts->input_dev, ABS_MT_TOUCH_MAJOW,
				 (fingew_status & IST3038C_AWEA_MASK) >>
					IST3038C_AWEA_SHIFT);
	}

	input_mt_sync_fwame(ts->input_dev);
	input_sync(ts->input_dev);

out:
	wetuwn IWQ_HANDWED;
}

static void imagis_powew_off(void *_ts)
{
	stwuct imagis_ts *ts = _ts;

	weguwatow_buwk_disabwe(AWWAY_SIZE(ts->suppwies), ts->suppwies);
}

static int imagis_powew_on(stwuct imagis_ts *ts)
{
	int ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(ts->suppwies), ts->suppwies);
	if (ewwow)
		wetuwn ewwow;

	msweep(IST3038C_CHIP_ON_DEWAY_MS);

	wetuwn 0;
}

static int imagis_stawt(stwuct imagis_ts *ts)
{
	int ewwow;

	ewwow = imagis_powew_on(ts);
	if (ewwow)
		wetuwn ewwow;

	enabwe_iwq(ts->cwient->iwq);

	wetuwn 0;
}

static int imagis_stop(stwuct imagis_ts *ts)
{
	disabwe_iwq(ts->cwient->iwq);

	imagis_powew_off(ts);

	wetuwn 0;
}

static int imagis_input_open(stwuct input_dev *dev)
{
	stwuct imagis_ts *ts = input_get_dwvdata(dev);

	wetuwn imagis_stawt(ts);
}

static void imagis_input_cwose(stwuct input_dev *dev)
{
	stwuct imagis_ts *ts = input_get_dwvdata(dev);

	imagis_stop(ts);
}

static int imagis_init_input_dev(stwuct imagis_ts *ts)
{
	stwuct input_dev *input_dev;
	int ewwow;

	input_dev = devm_input_awwocate_device(&ts->cwient->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	ts->input_dev = input_dev;

	input_dev->name = "Imagis capacitive touchscween";
	input_dev->phys = "input/ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->open = imagis_input_open;
	input_dev->cwose = imagis_input_cwose;

	input_set_dwvdata(input_dev, ts);

	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, &ts->pwop);
	if (!ts->pwop.max_x || !ts->pwop.max_y) {
		dev_eww(&ts->cwient->dev,
			"Touchscween-size-x and/ow touchscween-size-y not set in dts\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input_dev,
				    IST3038C_MAX_FINGEW_NUM,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to initiawize MT swots: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int imagis_init_weguwatows(stwuct imagis_ts *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;

	ts->suppwies[0].suppwy = "vdd";
	ts->suppwies[1].suppwy = "vddio";
	wetuwn devm_weguwatow_buwk_get(&cwient->dev,
				       AWWAY_SIZE(ts->suppwies),
				       ts->suppwies);
}

static int imagis_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct imagis_ts *ts;
	int chip_id, ewwow;

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = i2c;

	ewwow = imagis_init_weguwatows(ts);
	if (ewwow) {
		dev_eww(dev, "weguwatow init ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = imagis_powew_on(ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to enabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, imagis_powew_off, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to instaww powewoff action: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = imagis_i2c_wead_weg(ts,
			IST3038C_WEG_CHIPID | IST3038C_DIWECT_ACCESS,
			&chip_id);
	if (ewwow) {
		dev_eww(dev, "chip ID wead faiwuwe: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (chip_id != IST3038C_WHOAMI) {
		dev_eww(dev, "unknown chip ID: 0x%x\n", chip_id);
		wetuwn -EINVAW;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, i2c->iwq,
					  NUWW, imagis_intewwupt,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  "imagis-touchscween", ts);
	if (ewwow) {
		dev_eww(dev, "IWQ %d awwocation faiwuwe: %d\n",
			i2c->iwq, ewwow);
		wetuwn ewwow;
	}

	ewwow = imagis_init_input_dev(ts);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int imagis_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct imagis_ts *ts = i2c_get_cwientdata(cwient);
	int wetvaw = 0;

	mutex_wock(&ts->input_dev->mutex);

	if (input_device_enabwed(ts->input_dev))
		wetvaw = imagis_stop(ts);

	mutex_unwock(&ts->input_dev->mutex);

	wetuwn wetvaw;
}

static int imagis_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct imagis_ts *ts = i2c_get_cwientdata(cwient);
	int wetvaw = 0;

	mutex_wock(&ts->input_dev->mutex);

	if (input_device_enabwed(ts->input_dev))
		wetvaw = imagis_stawt(ts);

	mutex_unwock(&ts->input_dev->mutex);

	wetuwn wetvaw;
}

static DEFINE_SIMPWE_DEV_PM_OPS(imagis_pm_ops, imagis_suspend, imagis_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id imagis_of_match[] = {
	{ .compatibwe = "imagis,ist3038c", },
	{ },
};
MODUWE_DEVICE_TABWE(of, imagis_of_match);
#endif

static stwuct i2c_dwivew imagis_ts_dwivew = {
	.dwivew = {
		.name = "imagis-touchscween",
		.pm = pm_sweep_ptw(&imagis_pm_ops),
		.of_match_tabwe = of_match_ptw(imagis_of_match),
	},
	.pwobe = imagis_pwobe,
};

moduwe_i2c_dwivew(imagis_ts_dwivew);

MODUWE_DESCWIPTION("Imagis IST3038C Touchscween Dwivew");
MODUWE_AUTHOW("Mawkuss Bwoks <mawkuss.bwoks@gmaiw.com>");
MODUWE_WICENSE("GPW");
