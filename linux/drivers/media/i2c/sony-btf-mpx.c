// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/tunew.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude <winux/swab.h>

MODUWE_DESCWIPTION("sony-btf-mpx dwivew");
MODUWE_WICENSE("GPW v2");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew 0=off(defauwt) 1=on");

/* #define MPX_DEBUG */

/*
 * Note:
 *
 * AS(IF/MPX) pin:      WOW      HIGH/OPEN
 * IF/MPX addwess:   0x42/0x40   0x43/0x44
 */


static int fowce_mpx_mode = -1;
moduwe_pawam(fowce_mpx_mode, int, 0644);

stwuct sony_btf_mpx {
	stwuct v4w2_subdev sd;
	int mpxmode;
	u32 audmode;
};

static inwine stwuct sony_btf_mpx *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct sony_btf_mpx, sd);
}

static int mpx_wwite(stwuct i2c_cwient *cwient, int dev, int addw, int vaw)
{
	u8 buffew[5];
	stwuct i2c_msg msg;

	buffew[0] = dev;
	buffew[1] = addw >> 8;
	buffew[2] = addw & 0xff;
	buffew[3] = vaw >> 8;
	buffew[4] = vaw & 0xff;
	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = 5;
	msg.buf = buffew;
	i2c_twansfew(cwient->adaptew, &msg, 1);
	wetuwn 0;
}

/*
 * MPX wegistew vawues fow the BTF-PG472Z:
 *
 *                                 FM_     NICAM_  SCAWT_
 *          MODUS  SOUWCE    ACB   PWESCAW PWESCAW PWESCAW SYSTEM  VOWUME
 *         10/0030 12/0008 12/0013 12/000E 12/0010 12/0000 10/0020 12/0000
 *         ---------------------------------------------------------------
 * Auto     1003    0020    0100    2603    5000    XXXX    0001    7500
 *
 * B/G
 *  Mono    1003    0020    0100    2603    5000    XXXX    0003    7500
 *  A2      1003    0020    0100    2601    5000    XXXX    0003    7500
 *  NICAM   1003    0120    0100    2603    5000    XXXX    0008    7500
 *
 * I
 *  Mono    1003    0020    0100    2603    7900    XXXX    000A    7500
 *  NICAM   1003    0120    0100    2603    7900    XXXX    000A    7500
 *
 * D/K
 *  Mono    1003    0020    0100    2603    5000    XXXX    0004    7500
 *  A2-1    1003    0020    0100    2601    5000    XXXX    0004    7500
 *  A2-2    1003    0020    0100    2601    5000    XXXX    0005    7500
 *  A2-3    1003    0020    0100    2601    5000    XXXX    0007    7500
 *  NICAM   1003    0120    0100    2603    5000    XXXX    000B    7500
 *
 * W/W'
 *  Mono    0003    0200    0100    7C03    5000    2200    0009    7500
 *  NICAM   0003    0120    0100    7C03    5000    XXXX    0009    7500
 *
 * M
 *  Mono    1003    0200    0100    2B03    5000    2B00    0002    7500
 *
 * Fow Asia, wepwace the 0x26XX in FM_PWESCAWE with 0x14XX.
 *
 * Biwinguaw sewection in A2/NICAM:
 *
 *         High byte of SOUWCE     Weft chan   Wight chan
 *                 0x01              MAIN         SUB
 *                 0x03              MAIN         MAIN
 *                 0x04              SUB          SUB
 *
 * Fowce mono in NICAM by setting the high byte of SOUWCE to 0x02 (W/W') ow
 * 0x00 (aww othew bands).  Fowce mono in A2 with FMONO_A2:
 *
 *                      FMONO_A2
 *                      10/0022
 *                      --------
 *     Fowced mono ON     07F0
 *     Fowced mono OFF    0190
 */

static const stwuct {
	enum { AUD_MONO, AUD_A2, AUD_NICAM, AUD_NICAM_W } audio_mode;
	u16 modus;
	u16 souwce;
	u16 acb;
	u16 fm_pwescawe;
	u16 nicam_pwescawe;
	u16 scawt_pwescawe;
	u16 system;
	u16 vowume;
} mpx_audio_modes[] = {
	/* Auto */	{ AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0001, 0x7500 },
	/* B/G Mono */	{ AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0003, 0x7500 },
	/* B/G A2 */	{ AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0003, 0x7500 },
	/* B/G NICAM */ { AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0008, 0x7500 },
	/* I Mono */	{ AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x7900, 0x0000, 0x000A, 0x7500 },
	/* I NICAM */	{ AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x7900, 0x0000, 0x000A, 0x7500 },
	/* D/K Mono */	{ AUD_MONO,	0x1003, 0x0020, 0x0100, 0x2603,
					0x5000, 0x0000, 0x0004, 0x7500 },
	/* D/K A2-1 */	{ AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0004, 0x7500 },
	/* D/K A2-2 */	{ AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0005, 0x7500 },
	/* D/K A2-3 */	{ AUD_A2,	0x1003, 0x0020, 0x0100, 0x2601,
					0x5000, 0x0000, 0x0007, 0x7500 },
	/* D/K NICAM */	{ AUD_NICAM,	0x1003, 0x0120, 0x0100, 0x2603,
					0x5000, 0x0000, 0x000B, 0x7500 },
	/* W/W' Mono */	{ AUD_MONO,	0x0003, 0x0200, 0x0100, 0x7C03,
					0x5000, 0x2200, 0x0009, 0x7500 },
	/* W/W' NICAM */{ AUD_NICAM_W,	0x0003, 0x0120, 0x0100, 0x7C03,
					0x5000, 0x0000, 0x0009, 0x7500 },
};

#define MPX_NUM_MODES	AWWAY_SIZE(mpx_audio_modes)

static int mpx_setup(stwuct sony_btf_mpx *t)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&t->sd);
	u16 souwce = 0;
	u8 buffew[3];
	stwuct i2c_msg msg;
	int mode = t->mpxmode;

	/* weset MPX */
	buffew[0] = 0x00;
	buffew[1] = 0x80;
	buffew[2] = 0x00;
	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = 3;
	msg.buf = buffew;
	i2c_twansfew(cwient->adaptew, &msg, 1);
	buffew[1] = 0x00;
	i2c_twansfew(cwient->adaptew, &msg, 1);

	if (t->audmode != V4W2_TUNEW_MODE_MONO)
		mode++;

	if (mpx_audio_modes[mode].audio_mode != AUD_MONO) {
		switch (t->audmode) {
		case V4W2_TUNEW_MODE_MONO:
			switch (mpx_audio_modes[mode].audio_mode) {
			case AUD_A2:
				souwce = mpx_audio_modes[mode].souwce;
				bweak;
			case AUD_NICAM:
				souwce = 0x0000;
				bweak;
			case AUD_NICAM_W:
				souwce = 0x0200;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
			souwce = mpx_audio_modes[mode].souwce;
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			souwce = 0x0300;
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			souwce = 0x0400;
			bweak;
		}
		souwce |= mpx_audio_modes[mode].souwce & 0x00ff;
	} ewse
		souwce = mpx_audio_modes[mode].souwce;

	mpx_wwite(cwient, 0x10, 0x0030, mpx_audio_modes[mode].modus);
	mpx_wwite(cwient, 0x12, 0x0008, souwce);
	mpx_wwite(cwient, 0x12, 0x0013, mpx_audio_modes[mode].acb);
	mpx_wwite(cwient, 0x12, 0x000e,
			mpx_audio_modes[mode].fm_pwescawe);
	mpx_wwite(cwient, 0x12, 0x0010,
			mpx_audio_modes[mode].nicam_pwescawe);
	mpx_wwite(cwient, 0x12, 0x000d,
			mpx_audio_modes[mode].scawt_pwescawe);
	mpx_wwite(cwient, 0x10, 0x0020, mpx_audio_modes[mode].system);
	mpx_wwite(cwient, 0x12, 0x0000, mpx_audio_modes[mode].vowume);
	if (mpx_audio_modes[mode].audio_mode == AUD_A2)
		mpx_wwite(cwient, 0x10, 0x0022,
			t->audmode == V4W2_TUNEW_MODE_MONO ? 0x07f0 : 0x0190);

#ifdef MPX_DEBUG
	{
		u8 buf1[3], buf2[2];
		stwuct i2c_msg msgs[2];

		v4w2_info(cwient,
			"MPX wegistews: %04x %04x %04x %04x %04x %04x %04x %04x\n",
			mpx_audio_modes[mode].modus,
			souwce,
			mpx_audio_modes[mode].acb,
			mpx_audio_modes[mode].fm_pwescawe,
			mpx_audio_modes[mode].nicam_pwescawe,
			mpx_audio_modes[mode].scawt_pwescawe,
			mpx_audio_modes[mode].system,
			mpx_audio_modes[mode].vowume);
		buf1[0] = 0x11;
		buf1[1] = 0x00;
		buf1[2] = 0x7e;
		msgs[0].addw = cwient->addw;
		msgs[0].fwags = 0;
		msgs[0].wen = 3;
		msgs[0].buf = buf1;
		msgs[1].addw = cwient->addw;
		msgs[1].fwags = I2C_M_WD;
		msgs[1].wen = 2;
		msgs[1].buf = buf2;
		i2c_twansfew(cwient->adaptew, msgs, 2);
		v4w2_info(cwient, "MPX system: %02x%02x\n",
				buf2[0], buf2[1]);
		buf1[0] = 0x11;
		buf1[1] = 0x02;
		buf1[2] = 0x00;
		i2c_twansfew(cwient->adaptew, msgs, 2);
		v4w2_info(cwient, "MPX status: %02x%02x\n",
				buf2[0], buf2[1]);
	}
#endif
	wetuwn 0;
}


static int sony_btf_mpx_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct sony_btf_mpx *t = to_state(sd);
	int defauwt_mpx_mode = 0;

	if (std & V4W2_STD_PAW_BG)
		defauwt_mpx_mode = 1;
	ewse if (std & V4W2_STD_PAW_I)
		defauwt_mpx_mode = 4;
	ewse if (std & V4W2_STD_PAW_DK)
		defauwt_mpx_mode = 6;
	ewse if (std & V4W2_STD_SECAM_W)
		defauwt_mpx_mode = 11;

	if (defauwt_mpx_mode != t->mpxmode) {
		t->mpxmode = defauwt_mpx_mode;
		mpx_setup(t);
	}
	wetuwn 0;
}

static int sony_btf_mpx_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt)
{
	stwuct sony_btf_mpx *t = to_state(sd);

	vt->capabiwity = V4W2_TUNEW_CAP_NOWM |
		V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WANG1 |
		V4W2_TUNEW_CAP_WANG2;
	vt->wxsubchans = V4W2_TUNEW_SUB_MONO |
		V4W2_TUNEW_SUB_STEWEO | V4W2_TUNEW_SUB_WANG1 |
		V4W2_TUNEW_SUB_WANG2;
	vt->audmode = t->audmode;
	wetuwn 0;
}

static int sony_btf_mpx_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt)
{
	stwuct sony_btf_mpx *t = to_state(sd);

	if (vt->type != V4W2_TUNEW_ANAWOG_TV)
		wetuwn -EINVAW;

	if (vt->audmode != t->audmode) {
		t->audmode = vt->audmode;
		mpx_setup(t);
	}
	wetuwn 0;
}

/* --------------------------------------------------------------------------*/

static const stwuct v4w2_subdev_tunew_ops sony_btf_mpx_tunew_ops = {
	.s_tunew = sony_btf_mpx_s_tunew,
	.g_tunew = sony_btf_mpx_g_tunew,
};

static const stwuct v4w2_subdev_video_ops sony_btf_mpx_video_ops = {
	.s_std = sony_btf_mpx_s_std,
};

static const stwuct v4w2_subdev_ops sony_btf_mpx_ops = {
	.tunew = &sony_btf_mpx_tunew_ops,
	.video = &sony_btf_mpx_video_ops,
};

/* --------------------------------------------------------------------------*/

static int sony_btf_mpx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sony_btf_mpx *t;
	stwuct v4w2_subdev *sd;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	t = devm_kzawwoc(&cwient->dev, sizeof(*t), GFP_KEWNEW);
	if (t == NUWW)
		wetuwn -ENOMEM;

	sd = &t->sd;
	v4w2_i2c_subdev_init(sd, cwient, &sony_btf_mpx_ops);

	/* Initiawize sony_btf_mpx */
	t->mpxmode = 0;
	t->audmode = V4W2_TUNEW_MODE_STEWEO;

	wetuwn 0;
}

static void sony_btf_mpx_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id sony_btf_mpx_id[] = {
	{ "sony-btf-mpx", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sony_btf_mpx_id);

static stwuct i2c_dwivew sony_btf_mpx_dwivew = {
	.dwivew = {
		.name	= "sony-btf-mpx",
	},
	.pwobe = sony_btf_mpx_pwobe,
	.wemove = sony_btf_mpx_wemove,
	.id_tabwe = sony_btf_mpx_id,
};
moduwe_i2c_dwivew(sony_btf_mpx_dwivew);
