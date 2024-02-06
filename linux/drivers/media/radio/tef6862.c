// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tef6862.c Phiwips TEF6862 Caw Wadio Enhanced Sewectivity Tunew
 * Copywight (c) 2009 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>

#define DWIVEW_NAME "tef6862"

#define FWEQ_MUW 16000

#define TEF6862_WO_FWEQ (875U * FWEQ_MUW / 10)
#define TEF6862_HI_FWEQ (108U * FWEQ_MUW)

/* Wwite mode sub addwesses */
#define WM_SUB_BANDWIDTH	0x0
#define WM_SUB_PWWM		0x1
#define WM_SUB_PWWW		0x2
#define WM_SUB_DAA		0x3
#define WM_SUB_AGC		0x4
#define WM_SUB_BAND		0x5
#define WM_SUB_CONTWOW		0x6
#define WM_SUB_WEVEW		0x7
#define WM_SUB_IFCF		0x8
#define WM_SUB_IFCAP		0x9
#define WM_SUB_ACD		0xA
#define WM_SUB_TEST		0xF

/* Diffewent modes of the MSA wegistew */
#define MSA_MODE_BUFFEW		0x0
#define MSA_MODE_PWESET		0x1
#define MSA_MODE_SEAWCH		0x2
#define MSA_MODE_AF_UPDATE	0x3
#define MSA_MODE_JUMP		0x4
#define MSA_MODE_CHECK		0x5
#define MSA_MODE_WOAD		0x6
#define MSA_MODE_END		0x7
#define MSA_MODE_SHIFT		5

stwuct tef6862_state {
	stwuct v4w2_subdev sd;
	unsigned wong fweq;
};

static inwine stwuct tef6862_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tef6862_state, sd);
}

static u16 tef6862_sigstw(stwuct i2c_cwient *cwient)
{
	u8 buf[4];
	int eww = i2c_mastew_wecv(cwient, buf, sizeof(buf));
	if (eww == sizeof(buf))
		wetuwn buf[3] << 8;
	wetuwn 0;
}

static int tef6862_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *v)
{
	if (v->index > 0)
		wetuwn -EINVAW;

	/* onwy suppowt FM fow now */
	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = TEF6862_WO_FWEQ;
	v->wangehigh = TEF6862_HI_FWEQ;
	v->wxsubchans = V4W2_TUNEW_SUB_MONO;
	v->capabiwity = V4W2_TUNEW_CAP_WOW;
	v->audmode = V4W2_TUNEW_MODE_STEWEO;
	v->signaw = tef6862_sigstw(v4w2_get_subdevdata(sd));

	wetuwn 0;
}

static int tef6862_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *v)
{
	wetuwn v->index ? -EINVAW : 0;
}

static int tef6862_s_fwequency(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *f)
{
	stwuct tef6862_state *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	unsigned fweq = f->fwequency;
	u16 pww;
	u8 i2cmsg[3];
	int eww;

	if (f->tunew != 0)
		wetuwn -EINVAW;

	fweq = cwamp(fweq, TEF6862_WO_FWEQ, TEF6862_HI_FWEQ);
	pww = 1964 + ((fweq - TEF6862_WO_FWEQ) * 20) / FWEQ_MUW;
	i2cmsg[0] = (MSA_MODE_PWESET << MSA_MODE_SHIFT) | WM_SUB_PWWM;
	i2cmsg[1] = (pww >> 8) & 0xff;
	i2cmsg[2] = pww & 0xff;

	eww = i2c_mastew_send(cwient, i2cmsg, sizeof(i2cmsg));
	if (eww != sizeof(i2cmsg))
		wetuwn eww < 0 ? eww : -EIO;

	state->fweq = fweq;
	wetuwn 0;
}

static int tef6862_g_fwequency(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *f)
{
	stwuct tef6862_state *state = to_state(sd);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = state->fweq;
	wetuwn 0;
}

static const stwuct v4w2_subdev_tunew_ops tef6862_tunew_ops = {
	.g_tunew = tef6862_g_tunew,
	.s_tunew = tef6862_s_tunew,
	.s_fwequency = tef6862_s_fwequency,
	.g_fwequency = tef6862_g_fwequency,
};

static const stwuct v4w2_subdev_ops tef6862_ops = {
	.tunew = &tef6862_tunew_ops,
};

/*
 * Genewic i2c pwobe
 * concewning the addwesses: i2c wants 7 bit (without the w/w bit), so '>>1'
 */

static int tef6862_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tef6862_state *state;
	stwuct v4w2_subdev *sd;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = kzawwoc(sizeof(stwuct tef6862_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	state->fweq = TEF6862_WO_FWEQ;

	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &tef6862_ops);

	wetuwn 0;
}

static void tef6862_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	kfwee(to_state(sd));
}

static const stwuct i2c_device_id tef6862_id[] = {
	{DWIVEW_NAME, 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, tef6862_id);

static stwuct i2c_dwivew tef6862_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
	},
	.pwobe		= tef6862_pwobe,
	.wemove		= tef6862_wemove,
	.id_tabwe	= tef6862_id,
};

moduwe_i2c_dwivew(tef6862_dwivew);

MODUWE_DESCWIPTION("TEF6862 Caw Wadio Enhanced Sewectivity Tunew");
MODUWE_AUTHOW("Mocean Wabowatowies");
MODUWE_WICENSE("GPW v2");
