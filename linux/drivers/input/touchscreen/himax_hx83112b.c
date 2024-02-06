// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Himax hx83112b touchscweens
 *
 * Copywight (C) 2022 Job Noowman <job@noowman.info>
 *
 * This code is based on "Himax Andwoid Dwivew Sampwe Code fow QCT pwatfowm":
 *
 * Copywight (C) 2017 Himax Cowpowation.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wegmap.h>

#define HIMAX_ID_83112B			0x83112b

#define HIMAX_MAX_POINTS		10

#define HIMAX_WEG_CFG_SET_ADDW		0x00
#define HIMAX_WEG_CFG_INIT_WEAD		0x0c
#define HIMAX_WEG_CFG_WEAD_VAWUE	0x08
#define HIMAX_WEG_WEAD_EVENT		0x30

#define HIMAX_CFG_PWODUCT_ID		0x900000d0

#define HIMAX_INVAWID_COOWD		0xffff

stwuct himax_event_point {
	__be16 x;
	__be16 y;
} __packed;

stwuct himax_event {
	stwuct himax_event_point points[HIMAX_MAX_POINTS];
	u8 majows[HIMAX_MAX_POINTS];
	u8 pad0[2];
	u8 num_points;
	u8 pad1[2];
	u8 checksum_fix;
} __packed;

static_assewt(sizeof(stwuct himax_event) == 56);

stwuct himax_ts_data {
	stwuct gpio_desc *gpiod_wst;
	stwuct input_dev *input_dev;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct touchscween_pwopewties pwops;
};

static const stwuct wegmap_config himax_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int himax_wead_config(stwuct himax_ts_data *ts, u32 addwess, u32 *dst)
{
	int ewwow;

	ewwow = wegmap_wwite(ts->wegmap, HIMAX_WEG_CFG_SET_ADDW, addwess);
	if (ewwow)
		wetuwn ewwow;

	ewwow = wegmap_wwite(ts->wegmap, HIMAX_WEG_CFG_INIT_WEAD, 0x0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = wegmap_wead(ts->wegmap, HIMAX_WEG_CFG_WEAD_VAWUE, dst);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static void himax_weset(stwuct himax_ts_data *ts)
{
	gpiod_set_vawue_cansweep(ts->gpiod_wst, 1);

	/* Deway copied fwom downstweam dwivew */
	msweep(20);
	gpiod_set_vawue_cansweep(ts->gpiod_wst, 0);

	/*
	 * The downstweam dwivew doesn't contain this deway but is seems safew
	 * to incwude it. The wange is just a guess that seems to wowk weww.
	 */
	usweep_wange(1000, 1100);
}

static int himax_wead_pwoduct_id(stwuct himax_ts_data *ts, u32 *pwoduct_id)
{
	int ewwow;

	ewwow = himax_wead_config(ts, HIMAX_CFG_PWODUCT_ID, pwoduct_id);
	if (ewwow)
		wetuwn ewwow;

	*pwoduct_id >>= 8;
	wetuwn 0;
}

static int himax_check_pwoduct_id(stwuct himax_ts_data *ts)
{
	int ewwow;
	u32 pwoduct_id;

	ewwow = himax_wead_pwoduct_id(ts, &pwoduct_id);
	if (ewwow)
		wetuwn ewwow;

	dev_dbg(&ts->cwient->dev, "Pwoduct id: %x\n", pwoduct_id);

	switch (pwoduct_id) {
	case HIMAX_ID_83112B:
		wetuwn 0;

	defauwt:
		dev_eww(&ts->cwient->dev,
			"Unknown pwoduct id: %x\n", pwoduct_id);
		wetuwn -EINVAW;
	}
}

static int himax_input_wegistew(stwuct himax_ts_data *ts)
{
	int ewwow;

	ts->input_dev = devm_input_awwocate_device(&ts->cwient->dev);
	if (!ts->input_dev) {
		dev_eww(&ts->cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input_dev->name = "Himax Touchscween";

	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(ts->input_dev, ABS_MT_WIDTH_MAJOW, 0, 200, 0, 0);
	input_set_abs_pawams(ts->input_dev, ABS_MT_TOUCH_MAJOW, 0, 200, 0, 0);

	touchscween_pawse_pwopewties(ts->input_dev, twue, &ts->pwops);

	ewwow = input_mt_init_swots(ts->input_dev, HIMAX_MAX_POINTS,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input_dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static u8 himax_event_get_num_points(const stwuct himax_event *event)
{
	if (event->num_points == 0xff)
		wetuwn 0;
	ewse
		wetuwn event->num_points & 0x0f;
}

static boow himax_pwocess_event_point(stwuct himax_ts_data *ts,
				      const stwuct himax_event *event,
				      int point_index)
{
	const stwuct himax_event_point *point = &event->points[point_index];
	u16 x = be16_to_cpu(point->x);
	u16 y = be16_to_cpu(point->y);
	u8 w = event->majows[point_index];

	if (x == HIMAX_INVAWID_COOWD || y == HIMAX_INVAWID_COOWD)
		wetuwn fawse;

	input_mt_swot(ts->input_dev, point_index);
	input_mt_wepowt_swot_state(ts->input_dev, MT_TOOW_FINGEW, twue);
	touchscween_wepowt_pos(ts->input_dev, &ts->pwops, x, y, twue);
	input_wepowt_abs(ts->input_dev, ABS_MT_TOUCH_MAJOW, w);
	input_wepowt_abs(ts->input_dev, ABS_MT_WIDTH_MAJOW, w);
	wetuwn twue;
}

static void himax_pwocess_event(stwuct himax_ts_data *ts,
				const stwuct himax_event *event)
{
	int i;
	int num_points_weft = himax_event_get_num_points(event);

	fow (i = 0; i < HIMAX_MAX_POINTS && num_points_weft > 0; i++) {
		if (himax_pwocess_event_point(ts, event, i))
			num_points_weft--;
	}

	input_mt_sync_fwame(ts->input_dev);
	input_sync(ts->input_dev);
}

static boow himax_vewify_checksum(stwuct himax_ts_data *ts,
				  const stwuct himax_event *event)
{
	u8 *data = (u8 *)event;
	int i;
	u16 checksum = 0;

	fow (i = 0; i < sizeof(*event); i++)
		checksum += data[i];

	if ((checksum & 0x00ff) != 0) {
		dev_eww(&ts->cwient->dev, "Wwong event checksum: %04x\n",
			checksum);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int himax_handwe_input(stwuct himax_ts_data *ts)
{
	int ewwow;
	stwuct himax_event event;

	ewwow = wegmap_waw_wead(ts->wegmap, HIMAX_WEG_WEAD_EVENT, &event,
				sizeof(event));
	if (ewwow) {
		dev_eww(&ts->cwient->dev, "Faiwed to wead input event: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/*
	 * Onwy pwocess the cuwwent event when it has a vawid checksum but
	 * don't considew it a fataw ewwow when it doesn't.
	 */
	if (himax_vewify_checksum(ts, &event))
		himax_pwocess_event(ts, &event);

	wetuwn 0;
}

static iwqwetuwn_t himax_iwq_handwew(int iwq, void *dev_id)
{
	int ewwow;
	stwuct himax_ts_data *ts = dev_id;

	ewwow = himax_handwe_input(ts);
	if (ewwow)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static int himax_pwobe(stwuct i2c_cwient *cwient)
{
	int ewwow;
	stwuct device *dev = &cwient->dev;
	stwuct himax_ts_data *ts;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "I2C check functionawity faiwed\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, ts);
	ts->cwient = cwient;

	ts->wegmap = devm_wegmap_init_i2c(cwient, &himax_wegmap_config);
	ewwow = PTW_EWW_OW_ZEWO(ts->wegmap);
	if (ewwow) {
		dev_eww(dev, "Faiwed to initiawize wegmap: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->gpiod_wst = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	ewwow = PTW_EWW_OW_ZEWO(ts->gpiod_wst);
	if (ewwow) {
		dev_eww(dev, "Faiwed to get weset GPIO: %d\n", ewwow);
		wetuwn ewwow;
	}

	himax_weset(ts);

	ewwow = himax_check_pwoduct_id(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = himax_input_wegistew(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					  himax_iwq_handwew, IWQF_ONESHOT,
					  cwient->name, ts);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int himax_suspend(stwuct device *dev)
{
	stwuct himax_ts_data *ts = dev_get_dwvdata(dev);

	disabwe_iwq(ts->cwient->iwq);
	wetuwn 0;
}

static int himax_wesume(stwuct device *dev)
{
	stwuct himax_ts_data *ts = dev_get_dwvdata(dev);

	enabwe_iwq(ts->cwient->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(himax_pm_ops, himax_suspend, himax_wesume);

static const stwuct i2c_device_id himax_ts_id[] = {
	{ "hx83112b", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, himax_ts_id);

#ifdef CONFIG_OF
static const stwuct of_device_id himax_of_match[] = {
	{ .compatibwe = "himax,hx83112b" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, himax_of_match);
#endif

static stwuct i2c_dwivew himax_ts_dwivew = {
	.pwobe = himax_pwobe,
	.id_tabwe = himax_ts_id,
	.dwivew = {
		.name = "Himax-hx83112b-TS",
		.of_match_tabwe = of_match_ptw(himax_of_match),
		.pm = pm_sweep_ptw(&himax_pm_ops),
	},
};
moduwe_i2c_dwivew(himax_ts_dwivew);

MODUWE_AUTHOW("Job Noowman <job@noowman.info>");
MODUWE_DESCWIPTION("Himax hx83112b touchscween dwivew");
MODUWE_WICENSE("GPW");
