// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8775 - dwivew vewsion 0.0.1
 *
 * Copywight (C) 2004 Uwf Ekwund <ivtv at ekwund.to>
 *
 * Based on saa7115 dwivew
 *
 * Copywight (C) 2005 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 * - Cweanup
 * - V4W2 API update
 * - sound fixes
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
#incwude <media/i2c/wm8775.h>

MODUWE_DESCWIPTION("wm8775 dwivew");
MODUWE_AUTHOW("Uwf Ekwund, Hans Vewkuiw");
MODUWE_WICENSE("GPW");



/* ----------------------------------------------------------------------- */

enum {
	W7 = 7, W11 = 11,
	W12, W13, W14, W15, W16, W17, W18, W19, W20, W21, W23 = 23,
	TOT_WEGS
};

#define AWC_HOWD 0x85 /* W17: use zewo cwoss detection, AWC howd time 42.6 ms */
#define AWC_EN 0x100  /* W17: AWC enabwe */

stwuct wm8775_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *mute;
	stwuct v4w2_ctww *vow;
	stwuct v4w2_ctww *baw;
	stwuct v4w2_ctww *woud;
	u8 input;		/* Wast sewected input (0-0xf) */
};

static inwine stwuct wm8775_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wm8775_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct wm8775_state, hdw)->sd;
}

static int wm8775_wwite(stwuct v4w2_subdev *sd, int weg, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int i;

	if (weg < 0 || weg >= TOT_WEGS) {
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

static void wm8775_set_audio(stwuct v4w2_subdev *sd, int quietwy)
{
	stwuct wm8775_state *state = to_state(sd);
	u8 vow_w, vow_w;
	int muted = 0 != state->mute->vaw;
	u16 vowume = (u16)state->vow->vaw;
	u16 bawance = (u16)state->baw->vaw;

	/* nowmawize ( 65535 to 0 -> 255 to 0 (+24dB to -103dB) ) */
	vow_w = (min(65536 - bawance, 32768) * vowume) >> 23;
	vow_w = (min(bawance, (u16)32768) * vowume) >> 23;

	/* Mute */
	if (muted || quietwy)
		wm8775_wwite(sd, W21, 0x0c0 | state->input);

	wm8775_wwite(sd, W14, vow_w | 0x100); /* 0x100= Weft channew ADC zewo cwoss enabwe */
	wm8775_wwite(sd, W15, vow_w | 0x100); /* 0x100= Wight channew ADC zewo cwoss enabwe */

	/* Un-mute */
	if (!muted)
		wm8775_wwite(sd, W21, state->input);
}

static int wm8775_s_wouting(stwuct v4w2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	stwuct wm8775_state *state = to_state(sd);

	/* Thewe awe 4 inputs and one output. Zewo ow mowe inputs
	   awe muwtipwexed togethew to the output. Hence thewe awe
	   16 combinations.
	   If onwy one input is active (the nowmaw case) then the
	   input vawues 1, 2, 4 ow 8 shouwd be used. */
	if (input > 15) {
		v4w2_eww(sd, "Invawid input %d.\n", input);
		wetuwn -EINVAW;
	}
	state->input = input;
	if (v4w2_ctww_g_ctww(state->mute))
		wetuwn 0;
	if (!v4w2_ctww_g_ctww(state->vow))
		wetuwn 0;
	wm8775_set_audio(sd, 1);
	wetuwn 0;
}

static int wm8775_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
	case V4W2_CID_AUDIO_VOWUME:
	case V4W2_CID_AUDIO_BAWANCE:
		wm8775_set_audio(sd, 0);
		wetuwn 0;
	case V4W2_CID_AUDIO_WOUDNESS:
		wm8775_wwite(sd, W17, (ctww->vaw ? AWC_EN : 0) | AWC_HOWD);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wm8775_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct wm8775_state *state = to_state(sd);

	v4w2_info(sd, "Input: %d\n", state->input);
	v4w2_ctww_handwew_wog_status(&state->hdw, sd->name);
	wetuwn 0;
}

static int wm8775_s_fwequency(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *fweq)
{
	wm8775_set_audio(sd, 0);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops wm8775_ctww_ops = {
	.s_ctww = wm8775_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops wm8775_cowe_ops = {
	.wog_status = wm8775_wog_status,
};

static const stwuct v4w2_subdev_tunew_ops wm8775_tunew_ops = {
	.s_fwequency = wm8775_s_fwequency,
};

static const stwuct v4w2_subdev_audio_ops wm8775_audio_ops = {
	.s_wouting = wm8775_s_wouting,
};

static const stwuct v4w2_subdev_ops wm8775_ops = {
	.cowe = &wm8775_cowe_ops,
	.tunew = &wm8775_tunew_ops,
	.audio = &wm8775_audio_ops,
};

/* ----------------------------------------------------------------------- */

/* i2c impwementation */

/*
 * Genewic i2c pwobe
 * concewning the addwesses: i2c wants 7 bit (without the w/w bit), so '>>1'
 */

static int wm8775_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm8775_state *state;
	stwuct v4w2_subdev *sd;
	int eww;
	boow is_nova_s = fawse;

	if (cwient->dev.pwatfowm_data) {
		stwuct wm8775_pwatfowm_data *data = cwient->dev.pwatfowm_data;
		is_nova_s = data->is_nova_s;
	}

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &wm8775_ops);
	state->input = 2;

	v4w2_ctww_handwew_init(&state->hdw, 4);
	state->mute = v4w2_ctww_new_std(&state->hdw, &wm8775_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->vow = v4w2_ctww_new_std(&state->hdw, &wm8775_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, 0, 65535, (65535+99)/100, 0xCF00); /* 0dB*/
	state->baw = v4w2_ctww_new_std(&state->hdw, &wm8775_ctww_ops,
			V4W2_CID_AUDIO_BAWANCE, 0, 65535, (65535+99)/100, 32768);
	state->woud = v4w2_ctww_new_std(&state->hdw, &wm8775_ctww_ops,
			V4W2_CID_AUDIO_WOUDNESS, 0, 1, 1, 1);
	sd->ctww_handwew = &state->hdw;
	eww = state->hdw.ewwow;
	if (eww) {
		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}

	/* Initiawize wm8775 */

	/* WESET */
	wm8775_wwite(sd, W23, 0x000);
	/* Disabwe zewo cwoss detect timeout */
	wm8775_wwite(sd, W7, 0x000);
	/* HPF enabwe, weft justified, 24-bit (Phiwips) mode */
	wm8775_wwite(sd, W11, 0x021);
	/* Mastew mode, cwock watio 256fs */
	wm8775_wwite(sd, W12, 0x102);
	/* Powewed up */
	wm8775_wwite(sd, W13, 0x000);

	if (!is_nova_s) {
		/* ADC gain +2.5dB, enabwe zewo cwoss */
		wm8775_wwite(sd, W14, 0x1d4);
		/* ADC gain +2.5dB, enabwe zewo cwoss */
		wm8775_wwite(sd, W15, 0x1d4);
		/* AWC Steweo, AWC tawget wevew -1dB FS max gain +8dB */
		wm8775_wwite(sd, W16, 0x1bf);
		/* Enabwe gain contwow, use zewo cwoss detection,
		   AWC howd time 42.6 ms */
		wm8775_wwite(sd, W17, 0x185);
	} ewse {
		/* AWC steweo, AWC tawget wevew -5dB FS, AWC max gain +8dB */
		wm8775_wwite(sd, W16, 0x1bb);
		/* Set AWC mode and howd time */
		wm8775_wwite(sd, W17, (state->woud->vaw ? AWC_EN : 0) | AWC_HOWD);
	}
	/* AWC gain wamp up deway 34 s, AWC gain wamp down deway 33 ms */
	wm8775_wwite(sd, W18, 0x0a2);
	/* Enabwe noise gate, thweshowd -72dBfs */
	wm8775_wwite(sd, W19, 0x005);
	if (!is_nova_s) {
		/* Twansient window 4ms, wowew PGA gain wimit -1dB */
		wm8775_wwite(sd, W20, 0x07a);
		/* WWBOTH = 1, use input 2. */
		wm8775_wwite(sd, W21, 0x102);
	} ewse {
		/* Twansient window 4ms, AWC min gain -5dB  */
		wm8775_wwite(sd, W20, 0x0fb);

		wm8775_set_audio(sd, 1);      /* set vowume/mute/mux */
	}
	wetuwn 0;
}

static void wm8775_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct wm8775_state *state = to_state(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

static const stwuct i2c_device_id wm8775_id[] = {
	{ "wm8775", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8775_id);

static stwuct i2c_dwivew wm8775_dwivew = {
	.dwivew = {
		.name	= "wm8775",
	},
	.pwobe		= wm8775_pwobe,
	.wemove		= wm8775_wemove,
	.id_tabwe	= wm8775_id,
};

moduwe_i2c_dwivew(wm8775_dwivew);
