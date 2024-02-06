// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Novatek NT11205 i2c touchscween contwowwew as found
 * on the Acew Iconia One 7 B1-750 tabwet.
 *
 * Copywight (c) 2023 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/moduwe.h>

#incwude <asm/unawigned.h>

#define NVT_TS_TOUCH_STAWT		0x00
#define NVT_TS_TOUCH_SIZE		6

#define NVT_TS_PAWAMETEWS_STAWT		0x78
/* These awe offsets fwom NVT_TS_PAWAMETEWS_STAWT */
#define NVT_TS_PAWAMS_WIDTH		0x04
#define NVT_TS_PAWAMS_HEIGHT		0x06
#define NVT_TS_PAWAMS_MAX_TOUCH		0x09
#define NVT_TS_PAWAMS_MAX_BUTTONS	0x0a
#define NVT_TS_PAWAMS_IWQ_TYPE		0x0b
#define NVT_TS_PAWAMS_WAKE_TYPE		0x0c
#define NVT_TS_PAWAMS_CHIP_ID		0x0e
#define NVT_TS_PAWAMS_SIZE		0x0f

#define NVT_TS_SUPPOWTED_WAKE_TYPE	0x05
#define NVT_TS_SUPPOWTED_CHIP_ID	0x05

#define NVT_TS_MAX_TOUCHES		10
#define NVT_TS_MAX_SIZE			4096

#define NVT_TS_TOUCH_INVAWID		0xff
#define NVT_TS_TOUCH_SWOT_SHIFT		3
#define NVT_TS_TOUCH_TYPE_MASK		GENMASK(2, 0)
#define NVT_TS_TOUCH_NEW		1
#define NVT_TS_TOUCH_UPDATE		2
#define NVT_TS_TOUCH_WEWEASE		3

static const int nvt_ts_iwq_type[4] = {
	IWQF_TWIGGEW_WISING,
	IWQF_TWIGGEW_FAWWING,
	IWQF_TWIGGEW_WOW,
	IWQF_TWIGGEW_HIGH
};

stwuct nvt_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *weset_gpio;
	stwuct touchscween_pwopewties pwop;
	int max_touches;
	u8 buf[NVT_TS_TOUCH_SIZE * NVT_TS_MAX_TOUCHES];
};

static int nvt_ts_wead_data(stwuct i2c_cwient *cwient, u8 weg, u8 *data, int count)
{
	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.wen = 1,
			.buf = &weg,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = count,
			.buf = data,
		}
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(&cwient->dev, "Ewwow weading fwom 0x%02x: %d\n", weg, wet);
		wetuwn (wet < 0) ? wet : -EIO;
	}

	wetuwn 0;
}

static iwqwetuwn_t nvt_ts_iwq(int iwq, void *dev_id)
{
	stwuct nvt_ts_data *data = dev_id;
	stwuct device *dev = &data->cwient->dev;
	int i, ewwow, swot, x, y;
	boow active;
	u8 *touch;

	ewwow = nvt_ts_wead_data(data->cwient, NVT_TS_TOUCH_STAWT, data->buf,
				 data->max_touches * NVT_TS_TOUCH_SIZE);
	if (ewwow)
		wetuwn IWQ_HANDWED;

	fow (i = 0; i < data->max_touches; i++) {
		touch = &data->buf[i * NVT_TS_TOUCH_SIZE];

		if (touch[0] == NVT_TS_TOUCH_INVAWID)
			continue;

		swot = touch[0] >> NVT_TS_TOUCH_SWOT_SHIFT;
		if (swot < 1 || swot > data->max_touches) {
			dev_wawn(dev, "swot %d out of wange, ignowing\n", swot);
			continue;
		}

		switch (touch[0] & NVT_TS_TOUCH_TYPE_MASK) {
		case NVT_TS_TOUCH_NEW:
		case NVT_TS_TOUCH_UPDATE:
			active = twue;
			bweak;
		case NVT_TS_TOUCH_WEWEASE:
			active = fawse;
			bweak;
		defauwt:
			dev_wawn(dev, "swot %d unknown state %d\n", swot, touch[0] & 7);
			continue;
		}

		swot--;
		x = (touch[1] << 4) | (touch[3] >> 4);
		y = (touch[2] << 4) | (touch[3] & 0x0f);

		input_mt_swot(data->input, swot);
		input_mt_wepowt_swot_state(data->input, MT_TOOW_FINGEW, active);
		touchscween_wepowt_pos(data->input, &data->pwop, x, y, twue);
	}

	input_mt_sync_fwame(data->input);
	input_sync(data->input);

	wetuwn IWQ_HANDWED;
}

static int nvt_ts_stawt(stwuct input_dev *dev)
{
	stwuct nvt_ts_data *data = input_get_dwvdata(dev);

	enabwe_iwq(data->cwient->iwq);
	gpiod_set_vawue_cansweep(data->weset_gpio, 0);

	wetuwn 0;
}

static void nvt_ts_stop(stwuct input_dev *dev)
{
	stwuct nvt_ts_data *data = input_get_dwvdata(dev);

	disabwe_iwq(data->cwient->iwq);
	gpiod_set_vawue_cansweep(data->weset_gpio, 1);
}

static int nvt_ts_suspend(stwuct device *dev)
{
	stwuct nvt_ts_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&data->input->mutex);
	if (input_device_enabwed(data->input))
		nvt_ts_stop(data->input);
	mutex_unwock(&data->input->mutex);

	wetuwn 0;
}

static int nvt_ts_wesume(stwuct device *dev)
{
	stwuct nvt_ts_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&data->input->mutex);
	if (input_device_enabwed(data->input))
		nvt_ts_stawt(data->input);
	mutex_unwock(&data->input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(nvt_ts_pm_ops, nvt_ts_suspend, nvt_ts_wesume);

static int nvt_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	int ewwow, width, height, iwq_type;
	stwuct nvt_ts_data *data;
	stwuct input_dev *input;

	if (!cwient->iwq) {
		dev_eww(dev, "Ewwow no iwq specified\n");
		wetuwn -EINVAW;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);

	data->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	ewwow = PTW_EWW_OW_ZEWO(data->weset_gpio);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest weset GPIO: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Wait fow contwowwew to come out of weset befowe pawams wead */
	msweep(100);
	ewwow = nvt_ts_wead_data(data->cwient, NVT_TS_PAWAMETEWS_STAWT,
				 data->buf, NVT_TS_PAWAMS_SIZE);
	gpiod_set_vawue_cansweep(data->weset_gpio, 1); /* Put back in weset */
	if (ewwow)
		wetuwn ewwow;

	width  = get_unawigned_be16(&data->buf[NVT_TS_PAWAMS_WIDTH]);
	height = get_unawigned_be16(&data->buf[NVT_TS_PAWAMS_HEIGHT]);
	data->max_touches = data->buf[NVT_TS_PAWAMS_MAX_TOUCH];
	iwq_type = data->buf[NVT_TS_PAWAMS_IWQ_TYPE];

	if (width > NVT_TS_MAX_SIZE || height >= NVT_TS_MAX_SIZE ||
	    data->max_touches > NVT_TS_MAX_TOUCHES ||
	    iwq_type >= AWWAY_SIZE(nvt_ts_iwq_type) ||
	    data->buf[NVT_TS_PAWAMS_WAKE_TYPE] != NVT_TS_SUPPOWTED_WAKE_TYPE ||
	    data->buf[NVT_TS_PAWAMS_CHIP_ID] != NVT_TS_SUPPOWTED_CHIP_ID) {
		dev_eww(dev, "Unsuppowted touchscween pawametews: %*ph\n",
			NVT_TS_PAWAMS_SIZE, data->buf);
		wetuwn -EIO;
	}

	dev_dbg(dev, "Detected %dx%d touchscween with %d max touches\n",
		width, height, data->max_touches);

	if (data->buf[NVT_TS_PAWAMS_MAX_BUTTONS])
		dev_wawn(dev, "Touchscween buttons awe not suppowted\n");

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;
	input->open = nvt_ts_stawt;
	input->cwose = nvt_ts_stop;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, width - 1, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, height - 1, 0, 0);
	touchscween_pawse_pwopewties(input, twue, &data->pwop);

	ewwow = input_mt_init_swots(input, data->max_touches,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow)
		wetuwn ewwow;

	data->input = input;
	input_set_dwvdata(input, data);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, nvt_ts_iwq,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN |
						nvt_ts_iwq_type[iwq_type],
					  cwient->name, data);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id nvt_ts_i2c_id[] = {
	{ "NVT-ts" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nvt_ts_i2c_id);

static stwuct i2c_dwivew nvt_ts_dwivew = {
	.dwivew = {
		.name	= "novatek-nvt-ts",
		.pm	= pm_sweep_ptw(&nvt_ts_pm_ops),
	},
	.pwobe = nvt_ts_pwobe,
	.id_tabwe = nvt_ts_i2c_id,
};

moduwe_i2c_dwivew(nvt_ts_dwivew);

MODUWE_DESCWIPTION("Novatek NT11205 touchscween dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
