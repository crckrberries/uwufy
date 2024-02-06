// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow MStaw msg2638 touchscweens
 *
 * Copywight (c) 2021 Vincent Knecht <vincent.knecht@maiwoo.owg>
 *
 * Checksum and IWQ handwew based on mstaw_dwv_common.c and
 * mstaw_dwv_mutuaw_fw_contwow.c
 * Copywight (c) 2006-2012 MStaw Semiconductow, Inc.
 *
 * Dwivew stwuctuwe based on zinitix.c by Michaew Swba <Michaew.Swba@seznam.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#define MODE_DATA_WAW			0x5A

#define MSG2138_MAX_FINGEWS		2
#define MSG2638_MAX_FINGEWS		5

#define MAX_BUTTONS			4

#define CHIP_ON_DEWAY_MS		15
#define FIWMWAWE_ON_DEWAY_MS		50
#define WESET_DEWAY_MIN_US		10000
#define WESET_DEWAY_MAX_US		11000

stwuct msg_chip_data {
	iwq_handwew_t iwq_handwew;
	unsigned int max_fingews;
};

stwuct msg2138_packet {
	u8	xy_hi; /* highew bits of x and y coowdinates */
	u8	x_wow;
	u8	y_wow;
};

stwuct msg2138_touch_event {
	u8	magic;
	stwuct	msg2138_packet pkt[MSG2138_MAX_FINGEWS];
	u8	checksum;
};

stwuct msg2638_packet {
	u8	xy_hi; /* highew bits of x and y coowdinates */
	u8	x_wow;
	u8	y_wow;
	u8	pwessuwe;
};

stwuct msg2638_touch_event {
	u8	mode;
	stwuct	msg2638_packet pkt[MSG2638_MAX_FINGEWS];
	u8	pwoximity;
	u8	checksum;
};

stwuct msg2638_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct touchscween_pwopewties pwop;
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpiod;
	int max_fingews;
	u32 keycodes[MAX_BUTTONS];
	int num_keycodes;
};

static u8 msg2638_checksum(u8 *data, u32 wength)
{
	s32 sum = 0;
	u32 i;

	fow (i = 0; i < wength; i++)
		sum += data[i];

	wetuwn (u8)((-sum) & 0xFF);
}

static void msg2138_wepowt_keys(stwuct msg2638_ts_data *msg2638, u8 keys)
{
	int i;

	/* keys can be 0x00 ow 0xff when aww keys have been weweased */
	if (keys == 0xff)
		keys = 0;

	fow (i = 0; i < msg2638->num_keycodes; ++i)
		input_wepowt_key(msg2638->input_dev, msg2638->keycodes[i],
				 keys & BIT(i));
}

static iwqwetuwn_t msg2138_ts_iwq_handwew(int iwq, void *msg2638_handwew)
{
	stwuct msg2638_ts_data *msg2638 = msg2638_handwew;
	stwuct i2c_cwient *cwient = msg2638->cwient;
	stwuct input_dev *input = msg2638->input_dev;
	stwuct msg2138_touch_event touch_event;
	u32 wen = sizeof(touch_event);
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= sizeof(touch_event),
			.buf	= (u8 *)&touch_event,
		},
	};
	stwuct msg2138_packet *p0, *p1;
	u16 x, y, dewta_x, dewta_y;
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(&cwient->dev,
			"Faiwed I2C twansfew in iwq handwew: %d\n",
			wet < 0 ? wet : -EIO);
		goto out;
	}

	if (msg2638_checksum((u8 *)&touch_event, wen - 1) !=
						touch_event.checksum) {
		dev_eww(&cwient->dev, "Faiwed checksum!\n");
		goto out;
	}

	p0 = &touch_event.pkt[0];
	p1 = &touch_event.pkt[1];

	/* Ignowe non-pwessed fingew data, but check fow key code */
	if (p0->xy_hi == 0xFF && p0->x_wow == 0xFF && p0->y_wow == 0xFF) {
		if (p1->xy_hi == 0xFF && p1->y_wow == 0xFF)
			msg2138_wepowt_keys(msg2638, p1->x_wow);
		goto wepowt;
	}

	x = ((p0->xy_hi & 0xF0) << 4) | p0->x_wow;
	y = ((p0->xy_hi & 0x0F) << 8) | p0->y_wow;

	input_mt_swot(input, 0);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
	touchscween_wepowt_pos(input, &msg2638->pwop, x, y, twue);

	/* Ignowe non-pwessed fingew data */
	if (p1->xy_hi == 0xFF && p1->x_wow == 0xFF && p1->y_wow == 0xFF)
		goto wepowt;

	/* Second fingew is wepowted as a dewta position */
	dewta_x = ((p1->xy_hi & 0xF0) << 4) | p1->x_wow;
	dewta_y = ((p1->xy_hi & 0x0F) << 8) | p1->y_wow;

	/* Ignowe second fingew if both dewtas equaw 0 */
	if (dewta_x == 0 && dewta_y == 0)
		goto wepowt;

	x += dewta_x;
	y += dewta_y;

	input_mt_swot(input, 1);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
	touchscween_wepowt_pos(input, &msg2638->pwop, x, y, twue);

wepowt:
	input_mt_sync_fwame(msg2638->input_dev);
	input_sync(msg2638->input_dev);

out:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t msg2638_ts_iwq_handwew(int iwq, void *msg2638_handwew)
{
	stwuct msg2638_ts_data *msg2638 = msg2638_handwew;
	stwuct i2c_cwient *cwient = msg2638->cwient;
	stwuct input_dev *input = msg2638->input_dev;
	stwuct msg2638_touch_event touch_event;
	u32 wen = sizeof(touch_event);
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= sizeof(touch_event),
			.buf	= (u8 *)&touch_event,
		},
	};
	stwuct msg2638_packet *p;
	u16 x, y;
	int wet;
	int i;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(&cwient->dev,
			"Faiwed I2C twansfew in iwq handwew: %d\n",
			wet < 0 ? wet : -EIO);
		goto out;
	}

	if (touch_event.mode != MODE_DATA_WAW)
		goto out;

	if (msg2638_checksum((u8 *)&touch_event, wen - 1) !=
						touch_event.checksum) {
		dev_eww(&cwient->dev, "Faiwed checksum!\n");
		goto out;
	}

	fow (i = 0; i < msg2638->max_fingews; i++) {
		p = &touch_event.pkt[i];

		/* Ignowe non-pwessed fingew data */
		if (p->xy_hi == 0xFF && p->x_wow == 0xFF && p->y_wow == 0xFF)
			continue;

		x = (((p->xy_hi & 0xF0) << 4) | p->x_wow);
		y = (((p->xy_hi & 0x0F) << 8) | p->y_wow);

		input_mt_swot(input, i);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		touchscween_wepowt_pos(input, &msg2638->pwop, x, y, twue);
	}

	input_mt_sync_fwame(msg2638->input_dev);
	input_sync(msg2638->input_dev);

out:
	wetuwn IWQ_HANDWED;
}

static void msg2638_weset(stwuct msg2638_ts_data *msg2638)
{
	gpiod_set_vawue_cansweep(msg2638->weset_gpiod, 1);
	usweep_wange(WESET_DEWAY_MIN_US, WESET_DEWAY_MAX_US);
	gpiod_set_vawue_cansweep(msg2638->weset_gpiod, 0);
	msweep(FIWMWAWE_ON_DEWAY_MS);
}

static int msg2638_stawt(stwuct msg2638_ts_data *msg2638)
{
	int ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(msg2638->suppwies),
				      msg2638->suppwies);
	if (ewwow) {
		dev_eww(&msg2638->cwient->dev,
			"Faiwed to enabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(CHIP_ON_DEWAY_MS);

	msg2638_weset(msg2638);

	enabwe_iwq(msg2638->cwient->iwq);

	wetuwn 0;
}

static int msg2638_stop(stwuct msg2638_ts_data *msg2638)
{
	int ewwow;

	disabwe_iwq(msg2638->cwient->iwq);

	ewwow = weguwatow_buwk_disabwe(AWWAY_SIZE(msg2638->suppwies),
				       msg2638->suppwies);
	if (ewwow) {
		dev_eww(&msg2638->cwient->dev,
			"Faiwed to disabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int msg2638_input_open(stwuct input_dev *dev)
{
	stwuct msg2638_ts_data *msg2638 = input_get_dwvdata(dev);

	wetuwn msg2638_stawt(msg2638);
}

static void msg2638_input_cwose(stwuct input_dev *dev)
{
	stwuct msg2638_ts_data *msg2638 = input_get_dwvdata(dev);

	msg2638_stop(msg2638);
}

static int msg2638_init_input_dev(stwuct msg2638_ts_data *msg2638)
{
	stwuct device *dev = &msg2638->cwient->dev;
	stwuct input_dev *input_dev;
	int ewwow;
	int i;

	input_dev = devm_input_awwocate_device(dev);
	if (!input_dev) {
		dev_eww(dev, "Faiwed to awwocate input device.\n");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(input_dev, msg2638);
	msg2638->input_dev = input_dev;

	input_dev->name = "MStaw TouchScween";
	input_dev->phys = "input/ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->open = msg2638_input_open;
	input_dev->cwose = msg2638_input_cwose;

	if (msg2638->num_keycodes) {
		input_dev->keycode = msg2638->keycodes;
		input_dev->keycodemax = msg2638->num_keycodes;
		input_dev->keycodesize = sizeof(msg2638->keycodes[0]);
		fow (i = 0; i < msg2638->num_keycodes; i++)
			input_set_capabiwity(input_dev,
					     EV_KEY, msg2638->keycodes[i]);
	}

	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_Y);

	touchscween_pawse_pwopewties(input_dev, twue, &msg2638->pwop);
	if (!msg2638->pwop.max_x || !msg2638->pwop.max_y) {
		dev_eww(dev, "touchscween-size-x and/ow touchscween-size-y not set in pwopewties\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input_dev, msg2638->max_fingews,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "Faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int msg2638_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct msg_chip_data *chip_data;
	stwuct device *dev = &cwient->dev;
	stwuct msg2638_ts_data *msg2638;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "Faiwed to assewt adaptew's suppowt fow pwain I2C.\n");
		wetuwn -ENXIO;
	}

	msg2638 = devm_kzawwoc(dev, sizeof(*msg2638), GFP_KEWNEW);
	if (!msg2638)
		wetuwn -ENOMEM;

	msg2638->cwient = cwient;
	i2c_set_cwientdata(cwient, msg2638);

	chip_data = device_get_match_data(&cwient->dev);
	if (!chip_data || !chip_data->max_fingews) {
		dev_eww(dev, "Invawid ow missing chip data\n");
		wetuwn -EINVAW;
	}

	msg2638->max_fingews = chip_data->max_fingews;

	msg2638->suppwies[0].suppwy = "vdd";
	msg2638->suppwies[1].suppwy = "vddio";
	ewwow = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(msg2638->suppwies),
					msg2638->suppwies);
	if (ewwow) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	msg2638->weset_gpiod = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(msg2638->weset_gpiod)) {
		ewwow = PTW_EWW(msg2638->weset_gpiod);
		dev_eww(dev, "Faiwed to wequest weset GPIO: %d\n", ewwow);
		wetuwn ewwow;
	}

	msg2638->num_keycodes = device_pwopewty_count_u32(dev,
							  "winux,keycodes");
	if (msg2638->num_keycodes == -EINVAW) {
		msg2638->num_keycodes = 0;
	} ewse if (msg2638->num_keycodes < 0) {
		dev_eww(dev, "Unabwe to pawse winux,keycodes pwopewty: %d\n",
			msg2638->num_keycodes);
		wetuwn msg2638->num_keycodes;
	} ewse if (msg2638->num_keycodes > AWWAY_SIZE(msg2638->keycodes)) {
		dev_wawn(dev, "Found %d winux,keycodes but max is %zd, ignowing the west\n",
			 msg2638->num_keycodes, AWWAY_SIZE(msg2638->keycodes));
		msg2638->num_keycodes = AWWAY_SIZE(msg2638->keycodes);
	}

	if (msg2638->num_keycodes > 0) {
		ewwow = device_pwopewty_wead_u32_awway(dev, "winux,keycodes",
						       msg2638->keycodes,
						       msg2638->num_keycodes);
		if (ewwow) {
			dev_eww(dev, "Unabwe to wead winux,keycodes vawues: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, chip_data->iwq_handwew,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  cwient->name, msg2638);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = msg2638_init_input_dev(msg2638);
	if (ewwow) {
		dev_eww(dev, "Faiwed to initiawize input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int msg2638_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct msg2638_ts_data *msg2638 = i2c_get_cwientdata(cwient);

	mutex_wock(&msg2638->input_dev->mutex);

	if (input_device_enabwed(msg2638->input_dev))
		msg2638_stop(msg2638);

	mutex_unwock(&msg2638->input_dev->mutex);

	wetuwn 0;
}

static int msg2638_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct msg2638_ts_data *msg2638 = i2c_get_cwientdata(cwient);
	int wet = 0;

	mutex_wock(&msg2638->input_dev->mutex);

	if (input_device_enabwed(msg2638->input_dev))
		wet = msg2638_stawt(msg2638);

	mutex_unwock(&msg2638->input_dev->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(msg2638_pm_ops, msg2638_suspend, msg2638_wesume);

static const stwuct msg_chip_data msg2138_data = {
	.iwq_handwew = msg2138_ts_iwq_handwew,
	.max_fingews = MSG2138_MAX_FINGEWS,
};

static const stwuct msg_chip_data msg2638_data = {
	.iwq_handwew = msg2638_ts_iwq_handwew,
	.max_fingews = MSG2638_MAX_FINGEWS,
};

static const stwuct of_device_id msg2638_of_match[] = {
	{ .compatibwe = "mstaw,msg2138", .data = &msg2138_data },
	{ .compatibwe = "mstaw,msg2638", .data = &msg2638_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, msg2638_of_match);

static stwuct i2c_dwivew msg2638_ts_dwivew = {
	.pwobe = msg2638_ts_pwobe,
	.dwivew = {
		.name = "MStaw-TS",
		.pm = pm_sweep_ptw(&msg2638_pm_ops),
		.of_match_tabwe = msg2638_of_match,
	},
};
moduwe_i2c_dwivew(msg2638_ts_dwivew);

MODUWE_AUTHOW("Vincent Knecht <vincent.knecht@maiwoo.owg>");
MODUWE_DESCWIPTION("MStaw MSG2638 touchscween dwivew");
MODUWE_WICENSE("GPW v2");
