// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * m52790 i2c ivtv dwivew.
 * Copywight (C) 2007  Hans Vewkuiw
 *
 * A/V souwce switching Mitsubishi M52790SP/FP
 */


#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/i2c/m52790.h>
#incwude <media/v4w2-device.h>

MODUWE_DESCWIPTION("i2c device dwivew fow m52790 A/V switch");
MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_WICENSE("GPW");


stwuct m52790_state {
	stwuct v4w2_subdev sd;
	u16 input;
	u16 output;
};

static inwine stwuct m52790_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct m52790_state, sd);
}

/* ----------------------------------------------------------------------- */

static int m52790_wwite(stwuct v4w2_subdev *sd)
{
	stwuct m52790_state *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	u8 sw1 = (state->input | state->output) & 0xff;
	u8 sw2 = (state->input | state->output) >> 8;

	wetuwn i2c_smbus_wwite_byte_data(cwient, sw1, sw2);
}

/* Note: audio and video awe winked and cannot be switched sepawatewy.
   So audio and video wouting commands awe identicaw fow this chip.
   In theowy the video ampwifiew and audio modes couwd be handwed
   sepawatewy fow the output, but that seems to be ovewkiww wight now.
   The same howds fow impwementing an audio mute contwow, this is now
   pawt of the audio output wouting. The nowmaw case is that anothew
   chip takes cawe of the actuaw muting so making it pawt of the
   output wouting seems to be the wight thing to do fow now. */
static int m52790_s_wouting(stwuct v4w2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	stwuct m52790_state *state = to_state(sd);

	state->input = input;
	state->output = output;
	m52790_wwite(sd);
	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int m52790_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	stwuct m52790_state *state = to_state(sd);

	if (weg->weg != 0)
		wetuwn -EINVAW;
	weg->size = 1;
	weg->vaw = state->input | state->output;
	wetuwn 0;
}

static int m52790_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct m52790_state *state = to_state(sd);

	if (weg->weg != 0)
		wetuwn -EINVAW;
	state->input = weg->vaw & 0x0303;
	state->output = weg->vaw & ~0x0303;
	m52790_wwite(sd);
	wetuwn 0;
}
#endif

static int m52790_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct m52790_state *state = to_state(sd);

	v4w2_info(sd, "Switch 1: %02x\n",
			(state->input | state->output) & 0xff);
	v4w2_info(sd, "Switch 2: %02x\n",
			(state->input | state->output) >> 8);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops m52790_cowe_ops = {
	.wog_status = m52790_wog_status,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = m52790_g_wegistew,
	.s_wegistew = m52790_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_audio_ops m52790_audio_ops = {
	.s_wouting = m52790_s_wouting,
};

static const stwuct v4w2_subdev_video_ops m52790_video_ops = {
	.s_wouting = m52790_s_wouting,
};

static const stwuct v4w2_subdev_ops m52790_ops = {
	.cowe = &m52790_cowe_ops,
	.audio = &m52790_audio_ops,
	.video = &m52790_video_ops,
};

/* ----------------------------------------------------------------------- */

/* i2c impwementation */

static int m52790_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct m52790_state *state;
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
	v4w2_i2c_subdev_init(sd, cwient, &m52790_ops);
	state->input = M52790_IN_TUNEW;
	state->output = M52790_OUT_STEWEO;
	m52790_wwite(sd);
	wetuwn 0;
}

static void m52790_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id m52790_id[] = {
	{ "m52790", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, m52790_id);

static stwuct i2c_dwivew m52790_dwivew = {
	.dwivew = {
		.name	= "m52790",
	},
	.pwobe		= m52790_pwobe,
	.wemove		= m52790_wemove,
	.id_tabwe	= m52790_id,
};

moduwe_i2c_dwivew(m52790_dwivew);
