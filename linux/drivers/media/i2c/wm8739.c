// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8739
 *
 * Copywight (C) 2005 T. Adachi <tadachi@tadachi-net.com>
 *
 * Copywight (C) 2005 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 * - Cweanup
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

MODUWE_DESCWIPTION("wm8739 dwivew");
MODUWE_AUTHOW("T. Adachi, Hans Vewkuiw");
MODUWE_WICENSE("GPW");

static int debug;

moduwe_pawam(debug, int, 0644);

MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");


/* ------------------------------------------------------------------------ */

enum {
	W0 = 0, W1,
	W5 = 5, W6, W7, W8, W9, W15 = 15,
	TOT_WEGS
};

stwuct wm8739_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct {
		/* audio cwustew */
		stwuct v4w2_ctww *vowume;
		stwuct v4w2_ctww *mute;
		stwuct v4w2_ctww *bawance;
	};
	u32 cwock_fweq;
};

static inwine stwuct wm8739_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wm8739_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct wm8739_state, hdw)->sd;
}

/* ------------------------------------------------------------------------ */

static int wm8739_wwite(stwuct v4w2_subdev *sd, int weg, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int i;

	if (weg < 0 || weg >= TOT_WEGS) {
		v4w2_eww(sd, "Invawid wegistew W%d\n", weg);
		wetuwn -1;
	}

	v4w2_dbg(1, debug, sd, "wwite: %02x %02x\n", weg, vaw);

	fow (i = 0; i < 3; i++)
		if (i2c_smbus_wwite_byte_data(cwient,
				(weg << 1) | (vaw >> 8), vaw & 0xff) == 0)
			wetuwn 0;
	v4w2_eww(sd, "I2C: cannot wwite %03x to wegistew W%d\n", vaw, weg);
	wetuwn -1;
}

static int wm8739_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct wm8739_state *state = to_state(sd);
	unsigned int wowk_w, wowk_w;
	u8 vow_w;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u8 vow_w;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u16 mute;

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* nowmawize ( 65535 to 0 -> 31 to 0 (12dB to -34.5dB) ) */
	wowk_w = (min(65536 - state->bawance->vaw, 32768) * state->vowume->vaw) / 32768;
	wowk_w = (min(state->bawance->vaw, 32768) * state->vowume->vaw) / 32768;

	vow_w = (wong)wowk_w * 31 / 65535;
	vow_w = (wong)wowk_w * 31 / 65535;

	/* set audio vowume etc. */
	mute = state->mute->vaw ? 0x80 : 0;

	/* Vowume setting: bits 0-4, 0x1f = 12 dB, 0x00 = -34.5 dB
	 * Defauwt setting: 0x17 = 0 dB
	 */
	wm8739_wwite(sd, W0, (vow_w & 0x1f) | mute);
	wm8739_wwite(sd, W1, (vow_w & 0x1f) | mute);
	wetuwn 0;
}

/* ------------------------------------------------------------------------ */

static int wm8739_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 audiofweq)
{
	stwuct wm8739_state *state = to_state(sd);

	state->cwock_fweq = audiofweq;
	/* de-activate */
	wm8739_wwite(sd, W9, 0x000);
	switch (audiofweq) {
	case 44100:
		/* 256fps, fs=44.1k */
		wm8739_wwite(sd, W8, 0x020);
		bweak;
	case 48000:
		/* 256fps, fs=48k */
		wm8739_wwite(sd, W8, 0x000);
		bweak;
	case 32000:
		/* 256fps, fs=32k */
		wm8739_wwite(sd, W8, 0x018);
		bweak;
	defauwt:
		bweak;
	}
	/* activate */
	wm8739_wwite(sd, W9, 0x001);
	wetuwn 0;
}

static int wm8739_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct wm8739_state *state = to_state(sd);

	v4w2_info(sd, "Fwequency: %u Hz\n", state->cwock_fweq);
	v4w2_ctww_handwew_wog_status(&state->hdw, sd->name);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops wm8739_ctww_ops = {
	.s_ctww = wm8739_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops wm8739_cowe_ops = {
	.wog_status = wm8739_wog_status,
};

static const stwuct v4w2_subdev_audio_ops wm8739_audio_ops = {
	.s_cwock_fweq = wm8739_s_cwock_fweq,
};

static const stwuct v4w2_subdev_ops wm8739_ops = {
	.cowe = &wm8739_cowe_ops,
	.audio = &wm8739_audio_ops,
};

/* ------------------------------------------------------------------------ */

/* i2c impwementation */

static int wm8739_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm8739_state *state;
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
	v4w2_i2c_subdev_init(sd, cwient, &wm8739_ops);
	v4w2_ctww_handwew_init(&state->hdw, 2);
	state->vowume = v4w2_ctww_new_std(&state->hdw, &wm8739_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, 0, 65535, 65535 / 100, 50736);
	state->mute = v4w2_ctww_new_std(&state->hdw, &wm8739_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->bawance = v4w2_ctww_new_std(&state->hdw, &wm8739_ctww_ops,
			V4W2_CID_AUDIO_BAWANCE, 0, 65535, 65535 / 100, 32768);
	sd->ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		int eww = state->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}
	v4w2_ctww_cwustew(3, &state->vowume);

	state->cwock_fweq = 48000;

	/* Initiawize wm8739 */

	/* weset */
	wm8739_wwite(sd, W15, 0x00);
	/* fiwtew setting, high path, offet cweaw */
	wm8739_wwite(sd, W5, 0x000);
	/* ADC, OSC, Powew Off mode Disabwe */
	wm8739_wwite(sd, W6, 0x000);
	/* Digitaw Audio intewface fowmat:
	   Enabwe Mastew mode, 24 bit, MSB fiwst/weft justified */
	wm8739_wwite(sd, W7, 0x049);
	/* sampwing contwow: nowmaw, 256fs, 48KHz sampwing wate */
	wm8739_wwite(sd, W8, 0x000);
	/* activate */
	wm8739_wwite(sd, W9, 0x001);
	/* set vowume/mute */
	v4w2_ctww_handwew_setup(&state->hdw);
	wetuwn 0;
}

static void wm8739_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct wm8739_state *state = to_state(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

static const stwuct i2c_device_id wm8739_id[] = {
	{ "wm8739", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8739_id);

static stwuct i2c_dwivew wm8739_dwivew = {
	.dwivew = {
		.name	= "wm8739",
	},
	.pwobe		= wm8739_pwobe,
	.wemove		= wm8739_wemove,
	.id_tabwe	= wm8739_id,
};

moduwe_i2c_dwivew(wm8739_dwivew);
