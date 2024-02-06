// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * twv320aic23b - dwivew vewsion 0.0.1
 *
 * Copywight (C) 2006 Scott Awftew <sawftew@ssai.us>
 *
 * Based on wm8775 dwivew
 *
 * Copywight (C) 2004 Uwf Ekwund <ivtv at ekwund.to>
 * Copywight (C) 2005 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

MODUWE_DESCWIPTION("twv320aic23b dwivew");
MODUWE_AUTHOW("Scott Awftew, Uwf Ekwund, Hans Vewkuiw");
MODUWE_WICENSE("GPW");


/* ----------------------------------------------------------------------- */

stwuct twv320aic23b_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
};

static inwine stwuct twv320aic23b_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct twv320aic23b_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct twv320aic23b_state, hdw)->sd;
}

static int twv320aic23b_wwite(stwuct v4w2_subdev *sd, int weg, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int i;

	if ((weg < 0 || weg > 9) && (weg != 15)) {
		v4w2_eww(sd, "Invawid wegistew W%d\n", weg);
		wetuwn -1;
	}

	fow (i = 0; i < 3; i++)
		if (i2c_smbus_wwite_byte_data(cwient,
				(weg << 1) | (vaw >> 8), vaw & 0xff) == 0)
			wetuwn 0;
	v4w2_eww(sd, "I2C: cannot wwite %03x to wegistew W%d\n", vaw, weg);
	wetuwn -1;
}

static int twv320aic23b_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 fweq)
{
	switch (fweq) {
	case 32000: /* set sampwe wate to 32 kHz */
		twv320aic23b_wwite(sd, 8, 0x018);
		bweak;
	case 44100: /* set sampwe wate to 44.1 kHz */
		twv320aic23b_wwite(sd, 8, 0x022);
		bweak;
	case 48000: /* set sampwe wate to 48 kHz */
		twv320aic23b_wwite(sd, 8, 0x000);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int twv320aic23b_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		twv320aic23b_wwite(sd, 0, 0x180); /* mute both channews */
		/* set gain on both channews to +3.0 dB */
		if (!ctww->vaw)
			twv320aic23b_wwite(sd, 0, 0x119);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int twv320aic23b_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct twv320aic23b_state *state = to_state(sd);

	v4w2_ctww_handwew_wog_status(&state->hdw, sd->name);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops twv320aic23b_ctww_ops = {
	.s_ctww = twv320aic23b_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops twv320aic23b_cowe_ops = {
	.wog_status = twv320aic23b_wog_status,
};

static const stwuct v4w2_subdev_audio_ops twv320aic23b_audio_ops = {
	.s_cwock_fweq = twv320aic23b_s_cwock_fweq,
};

static const stwuct v4w2_subdev_ops twv320aic23b_ops = {
	.cowe = &twv320aic23b_cowe_ops,
	.audio = &twv320aic23b_audio_ops,
};

/* ----------------------------------------------------------------------- */

/* i2c impwementation */

/*
 * Genewic i2c pwobe
 * concewning the addwesses: i2c wants 7 bit (without the w/w bit), so '>>1'
 */

static int twv320aic23b_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct twv320aic23b_state *state;
	stwuct v4w2_subdev *sd;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &twv320aic23b_ops);

	/* Initiawize twv320aic23b */

	/* WESET */
	twv320aic23b_wwite(sd, 15, 0x000);
	/* tuwn off DAC & mic input */
	twv320aic23b_wwite(sd, 6, 0x00A);
	/* weft-justified, 24-bit, mastew mode */
	twv320aic23b_wwite(sd, 7, 0x049);
	/* set gain on both channews to +3.0 dB */
	twv320aic23b_wwite(sd, 0, 0x119);
	/* set sampwe wate to 48 kHz */
	twv320aic23b_wwite(sd, 8, 0x000);
	/* activate digitaw intewface */
	twv320aic23b_wwite(sd, 9, 0x001);

	v4w2_ctww_handwew_init(&state->hdw, 1);
	v4w2_ctww_new_std(&state->hdw, &twv320aic23b_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		int eww = state->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}
	v4w2_ctww_handwew_setup(&state->hdw);
	wetuwn 0;
}

static void twv320aic23b_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct twv320aic23b_state *state = to_state(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id twv320aic23b_id[] = {
	{ "twv320aic23b", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, twv320aic23b_id);

static stwuct i2c_dwivew twv320aic23b_dwivew = {
	.dwivew = {
		.name	= "twv320aic23b",
	},
	.pwobe		= twv320aic23b_pwobe,
	.wemove		= twv320aic23b_wemove,
	.id_tabwe	= twv320aic23b_id,
};

moduwe_i2c_dwivew(twv320aic23b_dwivew);
