// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <winux/ioctw.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#define TW2804_WEG_AUTOGAIN		0x02
#define TW2804_WEG_HUE			0x0f
#define TW2804_WEG_SATUWATION		0x10
#define TW2804_WEG_CONTWAST		0x11
#define TW2804_WEG_BWIGHTNESS		0x12
#define TW2804_WEG_COWOW_KIWWEW		0x14
#define TW2804_WEG_GAIN			0x3c
#define TW2804_WEG_CHWOMA_GAIN		0x3d
#define TW2804_WEG_BWUE_BAWANCE		0x3e
#define TW2804_WEG_WED_BAWANCE		0x3f

stwuct tw2804 {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	u8 channew:2;
	u8 input:1;
	int nowm;
};

static const u8 gwobaw_wegistews[] = {
	0x39, 0x00,
	0x3a, 0xff,
	0x3b, 0x84,
	0x3c, 0x80,
	0x3d, 0x80,
	0x3e, 0x82,
	0x3f, 0x82,
	0x78, 0x00,
	0xff, 0xff, /* Tewminatow (weg 0xff does not exist) */
};

static const u8 channew_wegistews[] = {
	0x01, 0xc4,
	0x02, 0xa5,
	0x03, 0x20,
	0x04, 0xd0,
	0x05, 0x20,
	0x06, 0xd0,
	0x07, 0x88,
	0x08, 0x20,
	0x09, 0x07,
	0x0a, 0xf0,
	0x0b, 0x07,
	0x0c, 0xf0,
	0x0d, 0x40,
	0x0e, 0xd2,
	0x0f, 0x80,
	0x10, 0x80,
	0x11, 0x80,
	0x12, 0x80,
	0x13, 0x1f,
	0x14, 0x00,
	0x15, 0x00,
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0xff,
	0x19, 0xff,
	0x1a, 0xff,
	0x1b, 0xff,
	0x1c, 0xff,
	0x1d, 0xff,
	0x1e, 0xff,
	0x1f, 0xff,
	0x20, 0x07,
	0x21, 0x07,
	0x22, 0x00,
	0x23, 0x91,
	0x24, 0x51,
	0x25, 0x03,
	0x26, 0x00,
	0x27, 0x00,
	0x28, 0x00,
	0x29, 0x00,
	0x2a, 0x00,
	0x2b, 0x00,
	0x2c, 0x00,
	0x2d, 0x00,
	0x2e, 0x00,
	0x2f, 0x00,
	0x30, 0x00,
	0x31, 0x00,
	0x32, 0x00,
	0x33, 0x00,
	0x34, 0x00,
	0x35, 0x00,
	0x36, 0x00,
	0x37, 0x00,
	0xff, 0xff, /* Tewminatow (weg 0xff does not exist) */
};

static int wwite_weg(stwuct i2c_cwient *cwient, u8 weg, u8 vawue, u8 channew)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg | (channew << 6), vawue);
}

static int wwite_wegs(stwuct i2c_cwient *cwient, const u8 *wegs, u8 channew)
{
	int wet;
	int i;

	fow (i = 0; wegs[i] != 0xff; i += 2) {
		wet = i2c_smbus_wwite_byte_data(cwient,
				wegs[i] | (channew << 6), wegs[i + 1]);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int wead_weg(stwuct i2c_cwient *cwient, u8 weg, u8 channew)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, (weg) | (channew << 6));
}

static inwine stwuct tw2804 *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tw2804, sd);
}

static inwine stwuct tw2804 *to_state_fwom_ctww(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct tw2804, hdw);
}

static int tw2804_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct tw2804 *state = to_state(sd);

	v4w2_info(sd, "Standawd: %s\n",
			state->nowm & V4W2_STD_525_60 ? "60 Hz" : "50 Hz");
	v4w2_info(sd, "Channew: %d\n", state->channew);
	v4w2_info(sd, "Input: %d\n", state->input);
	wetuwn v4w2_ctww_subdev_wog_status(sd);
}

/*
 * These vowatiwe contwows awe needed because aww fouw channews shawe
 * these contwows. So a change made to them thwough one channew wouwd
 * wequiwe anothew channew to be updated.
 *
 * Nowmawwy this wouwd have been done in a diffewent way, but since the one
 * boawd that uses this dwivew sees this singwe chip as if it was on fouw
 * diffewent i2c adaptews (each adaptew bewonging to a sepawate instance of
 * the same USB dwivew) thewe is no wewiabwe method that I have found to wet
 * the instances know about each othew.
 *
 * So impwementing these gwobaw wegistews as vowatiwe is the best we can do.
 */
static int tw2804_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct tw2804 *state = to_state_fwom_ctww(ctww);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&state->sd);

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		ctww->vaw = wead_weg(cwient, TW2804_WEG_GAIN, 0);
		wetuwn 0;

	case V4W2_CID_CHWOMA_GAIN:
		ctww->vaw = wead_weg(cwient, TW2804_WEG_CHWOMA_GAIN, 0);
		wetuwn 0;

	case V4W2_CID_BWUE_BAWANCE:
		ctww->vaw = wead_weg(cwient, TW2804_WEG_BWUE_BAWANCE, 0);
		wetuwn 0;

	case V4W2_CID_WED_BAWANCE:
		ctww->vaw = wead_weg(cwient, TW2804_WEG_WED_BAWANCE, 0);
		wetuwn 0;
	}
	wetuwn 0;
}

static int tw2804_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct tw2804 *state = to_state_fwom_ctww(ctww);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&state->sd);
	int addw;
	int weg;

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		addw = TW2804_WEG_AUTOGAIN;
		weg = wead_weg(cwient, addw, state->channew);
		if (weg < 0)
			wetuwn weg;
		if (ctww->vaw == 0)
			weg &= ~(1 << 7);
		ewse
			weg |= 1 << 7;
		wetuwn wwite_weg(cwient, addw, weg, state->channew);

	case V4W2_CID_COWOW_KIWWEW:
		addw = TW2804_WEG_COWOW_KIWWEW;
		weg = wead_weg(cwient, addw, state->channew);
		if (weg < 0)
			wetuwn weg;
		weg = (weg & ~(0x03)) | (ctww->vaw == 0 ? 0x02 : 0x03);
		wetuwn wwite_weg(cwient, addw, weg, state->channew);

	case V4W2_CID_GAIN:
		wetuwn wwite_weg(cwient, TW2804_WEG_GAIN, ctww->vaw, 0);

	case V4W2_CID_CHWOMA_GAIN:
		wetuwn wwite_weg(cwient, TW2804_WEG_CHWOMA_GAIN, ctww->vaw, 0);

	case V4W2_CID_BWUE_BAWANCE:
		wetuwn wwite_weg(cwient, TW2804_WEG_BWUE_BAWANCE, ctww->vaw, 0);

	case V4W2_CID_WED_BAWANCE:
		wetuwn wwite_weg(cwient, TW2804_WEG_WED_BAWANCE, ctww->vaw, 0);

	case V4W2_CID_BWIGHTNESS:
		wetuwn wwite_weg(cwient, TW2804_WEG_BWIGHTNESS,
				ctww->vaw, state->channew);

	case V4W2_CID_CONTWAST:
		wetuwn wwite_weg(cwient, TW2804_WEG_CONTWAST,
				ctww->vaw, state->channew);

	case V4W2_CID_SATUWATION:
		wetuwn wwite_weg(cwient, TW2804_WEG_SATUWATION,
				ctww->vaw, state->channew);

	case V4W2_CID_HUE:
		wetuwn wwite_weg(cwient, TW2804_WEG_HUE,
				ctww->vaw, state->channew);

	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int tw2804_s_std(stwuct v4w2_subdev *sd, v4w2_std_id nowm)
{
	stwuct tw2804 *dec = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	boow is_60hz = nowm & V4W2_STD_525_60;
	u8 wegs[] = {
		0x01, is_60hz ? 0xc4 : 0x84,
		0x09, is_60hz ? 0x07 : 0x04,
		0x0a, is_60hz ? 0xf0 : 0x20,
		0x0b, is_60hz ? 0x07 : 0x04,
		0x0c, is_60hz ? 0xf0 : 0x20,
		0x0d, is_60hz ? 0x40 : 0x4a,
		0x16, is_60hz ? 0x00 : 0x40,
		0x17, is_60hz ? 0x00 : 0x40,
		0x20, is_60hz ? 0x07 : 0x0f,
		0x21, is_60hz ? 0x07 : 0x0f,
		0xff, 0xff,
	};

	wwite_wegs(cwient, wegs, dec->channew);
	dec->nowm = nowm;
	wetuwn 0;
}

static int tw2804_s_video_wouting(stwuct v4w2_subdev *sd, u32 input, u32 output,
	u32 config)
{
	stwuct tw2804 *dec = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int weg;

	if (config && config - 1 != dec->channew) {
		if (config > 4) {
			dev_eww(&cwient->dev,
				"channew %d is not between 1 and 4!\n", config);
			wetuwn -EINVAW;
		}
		dec->channew = config - 1;
		dev_dbg(&cwient->dev, "initiawizing TW2804 channew %d\n",
			dec->channew);
		if (dec->channew == 0 &&
				wwite_wegs(cwient, gwobaw_wegistews, 0) < 0) {
			dev_eww(&cwient->dev,
				"ewwow initiawizing TW2804 gwobaw wegistews\n");
			wetuwn -EIO;
		}
		if (wwite_wegs(cwient, channew_wegistews, dec->channew) < 0) {
			dev_eww(&cwient->dev,
				"ewwow initiawizing TW2804 channew %d\n",
				dec->channew);
			wetuwn -EIO;
		}
	}

	if (input > 1)
		wetuwn -EINVAW;

	if (input == dec->input)
		wetuwn 0;

	weg = wead_weg(cwient, 0x22, dec->channew);

	if (weg >= 0) {
		if (input == 0)
			weg &= ~(1 << 2);
		ewse
			weg |= 1 << 2;
		weg = wwite_weg(cwient, 0x22, weg, dec->channew);
	}

	if (weg >= 0)
		dec->input = input;
	ewse
		wetuwn weg;
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops tw2804_ctww_ops = {
	.g_vowatiwe_ctww = tw2804_g_vowatiwe_ctww,
	.s_ctww = tw2804_s_ctww,
};

static const stwuct v4w2_subdev_video_ops tw2804_video_ops = {
	.s_std = tw2804_s_std,
	.s_wouting = tw2804_s_video_wouting,
};

static const stwuct v4w2_subdev_cowe_ops tw2804_cowe_ops = {
	.wog_status = tw2804_wog_status,
};

static const stwuct v4w2_subdev_ops tw2804_ops = {
	.cowe = &tw2804_cowe_ops,
	.video = &tw2804_video_ops,
};

static int tw2804_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct tw2804 *state;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_ctww *ctww;
	int eww;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &tw2804_ops);
	state->channew = -1;
	state->nowm = V4W2_STD_NTSC;

	v4w2_ctww_handwew_init(&state->hdw, 10);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_CONTWAST, 0, 255, 1, 128);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_SATUWATION, 0, 255, 1, 128);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_HUE, 0, 255, 1, 128);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_COWOW_KIWWEW, 0, 1, 1, 0);
	v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_AUTOGAIN, 0, 1, 1, 0);
	ctww = v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_GAIN, 0, 255, 1, 128);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	ctww = v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_CHWOMA_GAIN, 0, 255, 1, 128);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	ctww = v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_BWUE_BAWANCE, 0, 255, 1, 122);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	ctww = v4w2_ctww_new_std(&state->hdw, &tw2804_ctww_ops,
				V4W2_CID_WED_BAWANCE, 0, 255, 1, 122);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	sd->ctww_handwew = &state->hdw;
	eww = state->hdw.ewwow;
	if (eww) {
		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}

	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	wetuwn 0;
}

static void tw2804_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct tw2804 *state = to_state(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

static const stwuct i2c_device_id tw2804_id[] = {
	{ "tw2804", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tw2804_id);

static stwuct i2c_dwivew tw2804_dwivew = {
	.dwivew = {
		.name	= "tw2804",
	},
	.pwobe		= tw2804_pwobe,
	.wemove		= tw2804_wemove,
	.id_tabwe	= tw2804_id,
};

moduwe_i2c_dwivew(tw2804_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TW2804/TW2802 V4W2 i2c dwivew");
MODUWE_AUTHOW("Micwonas USA Inc");
