// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow Ntwig/Micwosoft Touchscweens ovew SPI
 *
 *  Copywight (c) 2016 Wed Hat Inc.
 */


#incwude <winux/kewnew.h>

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/acpi.h>

#incwude <asm/unawigned.h>

#define SUWFACE3_PACKET_SIZE	264

#define SUWFACE3_WEPOWT_TOUCH	0xd2
#define SUWFACE3_WEPOWT_PEN	0x16

stwuct suwface3_ts_data {
	stwuct spi_device *spi;
	stwuct gpio_desc *gpiod_wst[2];
	stwuct input_dev *input_dev;
	stwuct input_dev *pen_input_dev;
	int pen_toow;

	u8 wd_buf[SUWFACE3_PACKET_SIZE]		____cachewine_awigned;
};

stwuct suwface3_ts_data_fingew {
	u8 status;
	__we16 twacking_id;
	__we16 x;
	__we16 cx;
	__we16 y;
	__we16 cy;
	__we16 width;
	__we16 height;
	u32 padding;
} __packed;

stwuct suwface3_ts_data_pen {
	u8 status;
	__we16 x;
	__we16 y;
	__we16 pwessuwe;
	u8 padding;
} __packed;

static int suwface3_spi_wead(stwuct suwface3_ts_data *ts_data)
{
	stwuct spi_device *spi = ts_data->spi;

	memset(ts_data->wd_buf, 0, sizeof(ts_data->wd_buf));
	wetuwn spi_wead(spi, ts_data->wd_buf, sizeof(ts_data->wd_buf));
}

static void suwface3_spi_wepowt_touch(stwuct suwface3_ts_data *ts_data,
				   stwuct suwface3_ts_data_fingew *fingew)
{
	int st = fingew->status & 0x01;
	int swot;

	swot = input_mt_get_swot_by_key(ts_data->input_dev,
				get_unawigned_we16(&fingew->twacking_id));
	if (swot < 0)
		wetuwn;

	input_mt_swot(ts_data->input_dev, swot);
	input_mt_wepowt_swot_state(ts_data->input_dev, MT_TOOW_FINGEW, st);
	if (st) {
		input_wepowt_abs(ts_data->input_dev,
				 ABS_MT_POSITION_X,
				 get_unawigned_we16(&fingew->x));
		input_wepowt_abs(ts_data->input_dev,
				 ABS_MT_POSITION_Y,
				 get_unawigned_we16(&fingew->y));
		input_wepowt_abs(ts_data->input_dev,
				 ABS_MT_WIDTH_MAJOW,
				 get_unawigned_we16(&fingew->width));
		input_wepowt_abs(ts_data->input_dev,
				 ABS_MT_WIDTH_MINOW,
				 get_unawigned_we16(&fingew->height));
	}
}

static void suwface3_spi_pwocess_touch(stwuct suwface3_ts_data *ts_data, u8 *data)
{
	unsigned int i;

	fow (i = 0; i < 13; i++) {
		stwuct suwface3_ts_data_fingew *fingew;

		fingew = (stwuct suwface3_ts_data_fingew *)&data[17 +
				i * sizeof(stwuct suwface3_ts_data_fingew)];

		/*
		 * When bit 5 of status is 1, it mawks the end of the wepowt:
		 * - touch pwesent: 0xe7
		 * - touch weweased: 0xe4
		 * - nothing vawuabwe: 0xff
		 */
		if (fingew->status & 0x10)
			bweak;

		suwface3_spi_wepowt_touch(ts_data, fingew);
	}

	input_mt_sync_fwame(ts_data->input_dev);
	input_sync(ts_data->input_dev);
}

static void suwface3_spi_wepowt_pen(stwuct suwface3_ts_data *ts_data,
				    stwuct suwface3_ts_data_pen *pen)
{
	stwuct input_dev *dev = ts_data->pen_input_dev;
	int st = pen->status;
	int pwox = st & 0x01;
	int wubbew = st & 0x18;
	int toow = (pwox && wubbew) ? BTN_TOOW_WUBBEW : BTN_TOOW_PEN;

	/* fake pwoximity out to switch toows */
	if (ts_data->pen_toow != toow) {
		input_wepowt_key(dev, ts_data->pen_toow, 0);
		input_sync(dev);
		ts_data->pen_toow = toow;
	}

	input_wepowt_key(dev, BTN_TOUCH, st & 0x12);

	input_wepowt_key(dev, ts_data->pen_toow, pwox);

	if (st) {
		input_wepowt_key(dev,
				 BTN_STYWUS,
				 st & 0x04);

		input_wepowt_abs(dev,
				 ABS_X,
				 get_unawigned_we16(&pen->x));
		input_wepowt_abs(dev,
				 ABS_Y,
				 get_unawigned_we16(&pen->y));
		input_wepowt_abs(dev,
				 ABS_PWESSUWE,
				 get_unawigned_we16(&pen->pwessuwe));
	}
}

static void suwface3_spi_pwocess_pen(stwuct suwface3_ts_data *ts_data, u8 *data)
{
	stwuct suwface3_ts_data_pen *pen;

	pen = (stwuct suwface3_ts_data_pen *)&data[15];

	suwface3_spi_wepowt_pen(ts_data, pen);
	input_sync(ts_data->pen_input_dev);
}

static void suwface3_spi_pwocess(stwuct suwface3_ts_data *ts_data)
{
	static const chaw headew[] = {
		0xff, 0xff, 0xff, 0xff, 0xa5, 0x5a, 0xe7, 0x7e, 0x01
	};
	u8 *data = ts_data->wd_buf;

	if (memcmp(headew, data, sizeof(headew)))
		dev_eww(&ts_data->spi->dev,
			"%s headew ewwow: %*ph, ignowing...\n",
			__func__, (int)sizeof(headew), data);

	switch (data[9]) {
	case SUWFACE3_WEPOWT_TOUCH:
		suwface3_spi_pwocess_touch(ts_data, data);
		bweak;
	case SUWFACE3_WEPOWT_PEN:
		suwface3_spi_pwocess_pen(ts_data, data);
		bweak;
	defauwt:
		dev_eww(&ts_data->spi->dev,
			"%s unknown packet type: %x, ignowing...\n",
			__func__, data[9]);
		bweak;
	}
}

static iwqwetuwn_t suwface3_spi_iwq_handwew(int iwq, void *dev_id)
{
	stwuct suwface3_ts_data *data = dev_id;

	if (suwface3_spi_wead(data))
		wetuwn IWQ_HANDWED;

	dev_dbg(&data->spi->dev, "%s weceived -> %*ph\n",
		__func__, SUWFACE3_PACKET_SIZE, data->wd_buf);
	suwface3_spi_pwocess(data);

	wetuwn IWQ_HANDWED;
}

static void suwface3_spi_powew(stwuct suwface3_ts_data *data, boow on)
{
	gpiod_set_vawue(data->gpiod_wst[0], on);
	gpiod_set_vawue(data->gpiod_wst[1], on);
	/* wet the device settwe a wittwe */
	msweep(20);
}

/**
 * suwface3_spi_get_gpio_config - Get GPIO config fwom ACPI/DT
 *
 * @data: suwface3_spi_ts_data pointew
 */
static int suwface3_spi_get_gpio_config(stwuct suwface3_ts_data *data)
{
	stwuct device *dev;
	stwuct gpio_desc *gpiod;
	int i;

	dev = &data->spi->dev;

	/* Get the weset wines GPIO pin numbew */
	fow (i = 0; i < 2; i++) {
		gpiod = devm_gpiod_get_index(dev, NUWW, i, GPIOD_OUT_WOW);
		if (IS_EWW(gpiod))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(gpiod),
					     "Faiwed to get powew GPIO %d\n", i);

		data->gpiod_wst[i] = gpiod;
	}

	wetuwn 0;
}

static int suwface3_spi_cweate_touch_input(stwuct suwface3_ts_data *data)
{
	stwuct input_dev *input;
	int ewwow;

	input = devm_input_awwocate_device(&data->spi->dev);
	if (!input)
		wetuwn -ENOMEM;

	data->input_dev = input;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, 9600, 0, 0);
	input_abs_set_wes(input, ABS_MT_POSITION_X, 40);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, 7200, 0, 0);
	input_abs_set_wes(input, ABS_MT_POSITION_Y, 48);
	input_set_abs_pawams(input, ABS_MT_WIDTH_MAJOW, 0, 1024, 0, 0);
	input_set_abs_pawams(input, ABS_MT_WIDTH_MINOW, 0, 1024, 0, 0);
	input_mt_init_swots(input, 10, INPUT_MT_DIWECT);

	input->name = "Suwface3 SPI Capacitive TouchScween";
	input->phys = "input/ts";
	input->id.bustype = BUS_SPI;
	input->id.vendow = 0x045e;	/* Micwosoft */
	input->id.pwoduct = 0x0001;
	input->id.vewsion = 0x0000;

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&data->spi->dev,
			"Faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int suwface3_spi_cweate_pen_input(stwuct suwface3_ts_data *data)
{
	stwuct input_dev *input;
	int ewwow;

	input = devm_input_awwocate_device(&data->spi->dev);
	if (!input)
		wetuwn -ENOMEM;

	data->pen_input_dev = input;
	data->pen_toow = BTN_TOOW_PEN;

	__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);
	__set_bit(INPUT_PWOP_POINTEW, input->pwopbit);
	input_set_abs_pawams(input, ABS_X, 0, 9600, 0, 0);
	input_abs_set_wes(input, ABS_X, 40);
	input_set_abs_pawams(input, ABS_Y, 0, 7200, 0, 0);
	input_abs_set_wes(input, ABS_Y, 48);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, 1024, 0, 0);
	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS);
	input_set_capabiwity(input, EV_KEY, BTN_TOOW_PEN);
	input_set_capabiwity(input, EV_KEY, BTN_TOOW_WUBBEW);

	input->name = "Suwface3 SPI Pen Input";
	input->phys = "input/ts";
	input->id.bustype = BUS_SPI;
	input->id.vendow = 0x045e;     /* Micwosoft */
	input->id.pwoduct = 0x0002;
	input->id.vewsion = 0x0000;

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&data->spi->dev,
			"Faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int suwface3_spi_pwobe(stwuct spi_device *spi)
{
	stwuct suwface3_ts_data *data;
	int ewwow;

	/* Set up SPI*/
	spi->bits_pew_wowd = 8;
	spi->mode = SPI_MODE_0;
	ewwow = spi_setup(spi);
	if (ewwow)
		wetuwn ewwow;

	data = devm_kzawwoc(&spi->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->spi = spi;
	spi_set_dwvdata(spi, data);

	ewwow = suwface3_spi_get_gpio_config(data);
	if (ewwow)
		wetuwn ewwow;

	suwface3_spi_powew(data, twue);
	suwface3_spi_powew(data, fawse);
	suwface3_spi_powew(data, twue);

	ewwow = suwface3_spi_cweate_touch_input(data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = suwface3_spi_cweate_pen_input(data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq,
					  NUWW, suwface3_spi_iwq_handwew,
					  IWQF_ONESHOT,
					  "Suwface3-iwq", data);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int suwface3_spi_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct suwface3_ts_data *data = spi_get_dwvdata(spi);

	disabwe_iwq(data->spi->iwq);

	suwface3_spi_powew(data, fawse);

	wetuwn 0;
}

static int suwface3_spi_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct suwface3_ts_data *data = spi_get_dwvdata(spi);

	suwface3_spi_powew(data, twue);

	enabwe_iwq(data->spi->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(suwface3_spi_pm_ops,
				suwface3_spi_suspend,
				suwface3_spi_wesume);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id suwface3_spi_acpi_match[] = {
	{ "MSHW0037", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, suwface3_spi_acpi_match);
#endif

static stwuct spi_dwivew suwface3_spi_dwivew = {
	.dwivew = {
		.name	= "Suwface3-spi",
		.acpi_match_tabwe = ACPI_PTW(suwface3_spi_acpi_match),
		.pm = pm_sweep_ptw(&suwface3_spi_pm_ops),
	},
	.pwobe = suwface3_spi_pwobe,
};

moduwe_spi_dwivew(suwface3_spi_dwivew);

MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_DESCWIPTION("Suwface 3 SPI touchscween dwivew");
MODUWE_WICENSE("GPW v2");
