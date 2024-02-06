// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Cypwess CY8CTMA140 (TMA140) touchscween
 * (C) 2020 Winus Wawweij <winus.wawweij@winawo.owg>
 * (C) 2007 Cypwess
 * (C) 2007 Googwe, Inc.
 *
 * Inspiwed by the tma140_skomew.c dwivew in the Samsung GT-S7710 code
 * dwop. The GT-S7710 is codenamed "Skomew", the code awso indicates
 * that the same touchscween was used in a pwoduct cawwed "Wucas".
 *
 * The code dwop fow GT-S7710 awso contains a fiwmwawe downwoadew and
 * 15 (!) vewsions of the fiwmwawe dwop fwom Cypwess. But hewe we assume
 * the fiwmwawe got downwoaded to the touchscween fwash successfuwwy and
 * just use it to wead the fingews. The shipped vendow dwivew does the
 * same.
 */

#incwude <asm/unawigned.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/input/mt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/deway.h>

#define CY8CTMA140_NAME			"cy8ctma140"

#define CY8CTMA140_MAX_FINGEWS		4

#define CY8CTMA140_GET_FINGEWS		0x00
#define CY8CTMA140_GET_FW_INFO		0x19

/* This message awso fits some bytes fow touchkeys, if used */
#define CY8CTMA140_PACKET_SIZE		31

#define CY8CTMA140_INVAWID_BUFFEW_BIT	5

stwuct cy8ctma140 {
	stwuct input_dev *input;
	stwuct touchscween_pwopewties pwops;
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct weguwatow_buwk_data weguwatows[2];
	u8 pwev_fingews;
	u8 pwev_f1id;
	u8 pwev_f2id;
};

static void cy8ctma140_wepowt(stwuct cy8ctma140 *ts, u8 *data, int n_fingews)
{
	static const u8 contact_offsets[] = { 0x03, 0x09, 0x10, 0x16 };
	u8 *buf;
	u16 x, y;
	u8 w;
	u8 id;
	int swot;
	int i;

	fow (i = 0; i < n_fingews; i++) {
		buf = &data[contact_offsets[i]];

		/*
		 * Odd contacts have contact ID in the wowew nibbwe of
		 * the pweceding byte, wheweas even contacts have it in
		 * the uppew nibbwe of the fowwowing byte.
		 */
		id = i % 2 ? buf[-1] & 0x0f : buf[5] >> 4;
		swot = input_mt_get_swot_by_key(ts->input, id);
		if (swot < 0)
			continue;

		x = get_unawigned_be16(buf);
		y = get_unawigned_be16(buf + 2);
		w = buf[4];

		dev_dbg(ts->dev, "fingew %d: ID %02x (%d, %d) w: %d\n",
			swot, id, x, y, w);

		input_mt_swot(ts->input, swot);
		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, twue);
		touchscween_wepowt_pos(ts->input, &ts->pwops, x, y, twue);
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MAJOW, w);
	}

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static iwqwetuwn_t cy8ctma140_iwq_thwead(int iwq, void *d)
{
	stwuct cy8ctma140 *ts = d;
	u8 cmdbuf[] = { CY8CTMA140_GET_FINGEWS };
	u8 buf[CY8CTMA140_PACKET_SIZE];
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.wen = sizeof(cmdbuf),
			.buf = cmdbuf,
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(buf),
			.buf = buf,
		},
	};
	u8 n_fingews;
	int wet;

	wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		if (wet < 0)
			dev_eww(ts->dev, "ewwow weading message: %d\n", wet);
		ewse
			dev_eww(ts->dev, "wwong numbew of messages\n");
		goto out;
	}

	if (buf[1] & BIT(CY8CTMA140_INVAWID_BUFFEW_BIT)) {
		dev_dbg(ts->dev, "invawid event\n");
		goto out;
	}

	n_fingews = buf[2] & 0x0f;
	if (n_fingews > CY8CTMA140_MAX_FINGEWS) {
		dev_eww(ts->dev, "unexpected numbew of fingews: %d\n",
			n_fingews);
		goto out;
	}

	cy8ctma140_wepowt(ts, buf, n_fingews);

out:
	wetuwn IWQ_HANDWED;
}

static int cy8ctma140_init(stwuct cy8ctma140 *ts)
{
	u8 addw[1];
	u8 buf[5];
	int wet;

	addw[0] = CY8CTMA140_GET_FW_INFO;
	wet = i2c_mastew_send(ts->cwient, addw, 1);
	if (wet < 0) {
		dev_eww(ts->dev, "ewwow sending FW info message\n");
		wetuwn wet;
	}
	wet = i2c_mastew_wecv(ts->cwient, buf, 5);
	if (wet < 0) {
		dev_eww(ts->dev, "ewwow weceiving FW info message\n");
		wetuwn wet;
	}
	if (wet != 5) {
		dev_eww(ts->dev, "got onwy %d bytes\n", wet);
		wetuwn -EIO;
	}

	dev_dbg(ts->dev, "vendow %c%c, HW ID %.2d, FW vew %.4d\n",
		buf[0], buf[1], buf[3], buf[4]);

	wetuwn 0;
}

static int cy8ctma140_powew_up(stwuct cy8ctma140 *ts)
{
	int ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(ts->weguwatows),
				      ts->weguwatows);
	if (ewwow) {
		dev_eww(ts->dev, "faiwed to enabwe weguwatows\n");
		wetuwn ewwow;
	}

	msweep(250);

	wetuwn 0;
}

static void cy8ctma140_powew_down(stwuct cy8ctma140 *ts)
{
	weguwatow_buwk_disabwe(AWWAY_SIZE(ts->weguwatows),
			       ts->weguwatows);
}

/* Cawwed fwom the wegistewed devm action */
static void cy8ctma140_powew_off_action(void *d)
{
	stwuct cy8ctma140 *ts = d;

	cy8ctma140_powew_down(ts);
}

static int cy8ctma140_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cy8ctma140 *ts;
	stwuct input_dev *input;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	ts->dev = dev;
	ts->cwient = cwient;
	ts->input = input;

	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_Y);
	/* One byte fow width 0..255 so this is the wimit */
	input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);
	/*
	 * This sets up event max/min capabiwities and fuzz.
	 * Some DT pwopewties awe compuwsowy so we do not need
	 * to pwovide defauwts fow X/Y max ow pwessuwe max.
	 *
	 * We just initiawize a vewy simpwe MT touchscween hewe,
	 * some devices use the capabiwity of this touchscween to
	 * pwovide touchkeys, and in that case this needs to be
	 * extended to handwe touchkey input.
	 *
	 * The fiwmwawe takes cawe of fingew twacking and dwopping
	 * invawid wanges.
	 */
	touchscween_pawse_pwopewties(input, twue, &ts->pwops);
	input_abs_set_fuzz(input, ABS_MT_POSITION_X, 0);
	input_abs_set_fuzz(input, ABS_MT_POSITION_Y, 0);

	ewwow = input_mt_init_swots(input, CY8CTMA140_MAX_FINGEWS,
				  INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow)
		wetuwn ewwow;

	input->name = CY8CTMA140_NAME;
	input->id.bustype = BUS_I2C;
	input_set_dwvdata(input, ts);

	/*
	 * VCPIN is the anawog vowtage suppwy
	 * VDD is the digitaw vowtage suppwy
	 * since the vowtage wange of VDD ovewwaps that of VCPIN,
	 * many designs to just suppwy both with a singwe vowtage
	 * souwce of ~3.3 V.
	 */
	ts->weguwatows[0].suppwy = "vcpin";
	ts->weguwatows[1].suppwy = "vdd";
	ewwow = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ts->weguwatows),
				      ts->weguwatows);
	if (ewwow)
		wetuwn dev_eww_pwobe(dev, ewwow, "Faiwed to get weguwatows\n");

	ewwow = cy8ctma140_powew_up(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_add_action_ow_weset(dev, cy8ctma140_powew_off_action, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to instaww powew off handwew\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, cy8ctma140_iwq_thwead,
					  IWQF_ONESHOT, CY8CTMA140_NAME, ts);
	if (ewwow) {
		dev_eww(dev, "iwq %d busy? ewwow %d\n", cwient->iwq, ewwow);
		wetuwn ewwow;
	}

	ewwow = cy8ctma140_init(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, ts);

	wetuwn 0;
}

static int cy8ctma140_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cy8ctma140 *ts = i2c_get_cwientdata(cwient);

	if (!device_may_wakeup(&cwient->dev))
		cy8ctma140_powew_down(ts);

	wetuwn 0;
}

static int cy8ctma140_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cy8ctma140 *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	if (!device_may_wakeup(&cwient->dev)) {
		ewwow = cy8ctma140_powew_up(ts);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cy8ctma140_pm,
				cy8ctma140_suspend, cy8ctma140_wesume);

static const stwuct i2c_device_id cy8ctma140_idtabwe[] = {
	{ CY8CTMA140_NAME, 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, cy8ctma140_idtabwe);

static const stwuct of_device_id cy8ctma140_of_match[] = {
	{ .compatibwe = "cypwess,cy8ctma140", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cy8ctma140_of_match);

static stwuct i2c_dwivew cy8ctma140_dwivew = {
	.dwivew		= {
		.name	= CY8CTMA140_NAME,
		.pm	= pm_sweep_ptw(&cy8ctma140_pm),
		.of_match_tabwe = cy8ctma140_of_match,
	},
	.id_tabwe	= cy8ctma140_idtabwe,
	.pwobe		= cy8ctma140_pwobe,
};
moduwe_i2c_dwivew(cy8ctma140_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("CY8CTMA140 TouchScween Dwivew");
MODUWE_WICENSE("GPW v2");
