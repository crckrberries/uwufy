// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Montage Technowogy DS3000 - DVBS/S2 Demoduwatow dwivew
    Copywight (C) 2009-2012 Konstantin Dimitwov <kosio.dimitwov@gmaiw.com>

    Copywight (C) 2009-2012 TuwboSight.com

 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>

#incwude <media/dvb_fwontend.h>
#incwude "ts2020.h"
#incwude "ds3000.h"

static int debug;

#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(awgs); \
	} whiwe (0)

/* as of Mawch 2009 cuwwent DS3000 fiwmwawe vewsion is 1.78 */
/* DS3000 FW v1.78 MD5: a32d17910c4f370073f9346e71d34b80 */
#define DS3000_DEFAUWT_FIWMWAWE "dvb-fe-ds3000.fw"

#define DS3000_SAMPWE_WATE 96000 /* in kHz */

/* Wegistew vawues to initiawise the demod in DVB-S mode */
static u8 ds3000_dvbs_init_tab[] = {
	0x23, 0x05,
	0x08, 0x03,
	0x0c, 0x00,
	0x21, 0x54,
	0x25, 0x82,
	0x27, 0x31,
	0x30, 0x08,
	0x31, 0x40,
	0x32, 0x32,
	0x33, 0x35,
	0x35, 0xff,
	0x3a, 0x00,
	0x37, 0x10,
	0x38, 0x10,
	0x39, 0x02,
	0x42, 0x60,
	0x4a, 0x40,
	0x4b, 0x04,
	0x4d, 0x91,
	0x5d, 0xc8,
	0x50, 0x77,
	0x51, 0x77,
	0x52, 0x36,
	0x53, 0x36,
	0x56, 0x01,
	0x63, 0x43,
	0x64, 0x30,
	0x65, 0x40,
	0x68, 0x26,
	0x69, 0x4c,
	0x70, 0x20,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x40,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x60,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x80,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0xa0,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x1f,
	0x76, 0x00,
	0x77, 0xd1,
	0x78, 0x0c,
	0x79, 0x80,
	0x7f, 0x04,
	0x7c, 0x00,
	0x80, 0x86,
	0x81, 0xa6,
	0x85, 0x04,
	0xcd, 0xf4,
	0x90, 0x33,
	0xa0, 0x44,
	0xc0, 0x18,
	0xc3, 0x10,
	0xc4, 0x08,
	0xc5, 0x80,
	0xc6, 0x80,
	0xc7, 0x0a,
	0xc8, 0x1a,
	0xc9, 0x80,
	0xfe, 0x92,
	0xe0, 0xf8,
	0xe6, 0x8b,
	0xd0, 0x40,
	0xf8, 0x20,
	0xfa, 0x0f,
	0xfd, 0x20,
	0xad, 0x20,
	0xae, 0x07,
	0xb8, 0x00,
};

/* Wegistew vawues to initiawise the demod in DVB-S2 mode */
static u8 ds3000_dvbs2_init_tab[] = {
	0x23, 0x0f,
	0x08, 0x07,
	0x0c, 0x00,
	0x21, 0x54,
	0x25, 0x82,
	0x27, 0x31,
	0x30, 0x08,
	0x31, 0x32,
	0x32, 0x32,
	0x33, 0x35,
	0x35, 0xff,
	0x3a, 0x00,
	0x37, 0x10,
	0x38, 0x10,
	0x39, 0x02,
	0x42, 0x60,
	0x4a, 0x80,
	0x4b, 0x04,
	0x4d, 0x81,
	0x5d, 0x88,
	0x50, 0x36,
	0x51, 0x36,
	0x52, 0x36,
	0x53, 0x36,
	0x63, 0x60,
	0x64, 0x10,
	0x65, 0x10,
	0x68, 0x04,
	0x69, 0x29,
	0x70, 0x20,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x40,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x60,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x80,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0xa0,
	0x71, 0x70,
	0x72, 0x04,
	0x73, 0x00,
	0x70, 0x1f,
	0xa0, 0x44,
	0xc0, 0x08,
	0xc1, 0x10,
	0xc2, 0x08,
	0xc3, 0x10,
	0xc4, 0x08,
	0xc5, 0xf0,
	0xc6, 0xf0,
	0xc7, 0x0a,
	0xc8, 0x1a,
	0xc9, 0x80,
	0xca, 0x23,
	0xcb, 0x24,
	0xce, 0x74,
	0x90, 0x03,
	0x76, 0x80,
	0x77, 0x42,
	0x78, 0x0a,
	0x79, 0x80,
	0xad, 0x40,
	0xae, 0x07,
	0x7f, 0xd4,
	0x7c, 0x00,
	0x80, 0xa8,
	0x81, 0xda,
	0x7c, 0x01,
	0x80, 0xda,
	0x81, 0xec,
	0x7c, 0x02,
	0x80, 0xca,
	0x81, 0xeb,
	0x7c, 0x03,
	0x80, 0xba,
	0x81, 0xdb,
	0x85, 0x08,
	0x86, 0x00,
	0x87, 0x02,
	0x89, 0x80,
	0x8b, 0x44,
	0x8c, 0xaa,
	0x8a, 0x10,
	0xba, 0x00,
	0xf5, 0x04,
	0xfe, 0x44,
	0xd2, 0x32,
	0xb8, 0x00,
};

stwuct ds3000_state {
	stwuct i2c_adaptew *i2c;
	const stwuct ds3000_config *config;
	stwuct dvb_fwontend fwontend;
	/* pwevious uncowwected bwock countew fow DVB-S2 */
	u16 pwevUCBS2;
};

static int ds3000_wwiteweg(stwuct ds3000_state *state, int weg, int data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess,
		.fwags = 0, .buf = buf, .wen = 2 };
	int eww;

	dpwintk("%s: wwite weg 0x%02x, vawue 0x%02x\n", __func__, weg, data);

	eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk(KEWN_EWW "%s: wwiteweg ewwow(eww == %i, weg == 0x%02x, vawue == 0x%02x)\n",
		       __func__, eww, weg, data);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int ds3000_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;

	if (enabwe)
		ds3000_wwiteweg(state, 0x03, 0x12);
	ewse
		ds3000_wwiteweg(state, 0x03, 0x02);

	wetuwn 0;
}

/* I2C wwite fow 8k fiwmwawe woad */
static int ds3000_wwiteFW(stwuct ds3000_state *state, int weg,
				const u8 *data, u16 wen)
{
	int i, wet = 0;
	stwuct i2c_msg msg;
	u8 *buf;

	buf = kmawwoc(33, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	*(buf) = weg;

	msg.addw = state->config->demod_addwess;
	msg.fwags = 0;
	msg.buf = buf;
	msg.wen = 33;

	fow (i = 0; i < wen; i += 32) {
		memcpy(buf + 1, data + i, 32);

		dpwintk("%s: wwite weg 0x%02x, wen = %d\n", __func__, weg, wen);

		wet = i2c_twansfew(state->i2c, &msg, 1);
		if (wet != 1) {
			pwintk(KEWN_EWW "%s: wwite ewwow(eww == %i, weg == 0x%02x\n",
			       __func__, wet, weg);
			wet = -EWEMOTEIO;
			goto ewwow;
		}
	}
	wet = 0;

ewwow:
	kfwee(buf);

	wetuwn wet;
}

static int ds3000_weadweg(stwuct ds3000_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{
			.addw = state->config->demod_addwess,
			.fwags = 0,
			.buf = b0,
			.wen = 1
		}, {
			.addw = state->config->demod_addwess,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 1
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		pwintk(KEWN_EWW "%s: weg=0x%x(ewwow=%d)\n", __func__, weg, wet);
		wetuwn wet;
	}

	dpwintk("%s: wead weg 0x%02x, vawue 0x%02x\n", __func__, weg, b1[0]);

	wetuwn b1[0];
}

static int ds3000_woad_fiwmwawe(stwuct dvb_fwontend *fe,
					const stwuct fiwmwawe *fw);

static int ds3000_fiwmwawe_ondemand(stwuct dvb_fwontend *fe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	int wet = 0;

	dpwintk("%s()\n", __func__);

	wet = ds3000_weadweg(state, 0xb2);
	if (wet < 0)
		wetuwn wet;

	/* Woad fiwmwawe */
	/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
	pwintk(KEWN_INFO "%s: Waiting fow fiwmwawe upwoad (%s)...\n", __func__,
				DS3000_DEFAUWT_FIWMWAWE);
	wet = wequest_fiwmwawe(&fw, DS3000_DEFAUWT_FIWMWAWE,
				state->i2c->dev.pawent);
	pwintk(KEWN_INFO "%s: Waiting fow fiwmwawe upwoad(2)...\n", __func__);
	if (wet) {
		pwintk(KEWN_EWW "%s: No fiwmwawe upwoaded (timeout ow fiwe not found?)\n",
		       __func__);
		wetuwn wet;
	}

	wet = ds3000_woad_fiwmwawe(fe, fw);
	if (wet)
		pwintk("%s: Wwiting fiwmwawe to device faiwed\n", __func__);

	wewease_fiwmwawe(fw);

	dpwintk("%s: Fiwmwawe upwoad %s\n", __func__,
			wet == 0 ? "compwete" : "faiwed");

	wetuwn wet;
}

static int ds3000_woad_fiwmwawe(stwuct dvb_fwontend *fe,
					const stwuct fiwmwawe *fw)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	int wet = 0;

	dpwintk("%s\n", __func__);
	dpwintk("Fiwmwawe is %zu bytes (%02x %02x .. %02x %02x)\n",
			fw->size,
			fw->data[0],
			fw->data[1],
			fw->data[fw->size - 2],
			fw->data[fw->size - 1]);

	/* Begin the fiwmwawe woad pwocess */
	ds3000_wwiteweg(state, 0xb2, 0x01);
	/* wwite the entiwe fiwmwawe */
	wet = ds3000_wwiteFW(state, 0xb0, fw->data, fw->size);
	ds3000_wwiteweg(state, 0xb2, 0x00);

	wetuwn wet;
}

static int ds3000_set_vowtage(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	u8 data;

	dpwintk("%s(%d)\n", __func__, vowtage);

	data = ds3000_weadweg(state, 0xa2);
	data |= 0x03; /* bit0 V/H, bit1 off/on */

	switch (vowtage) {
	case SEC_VOWTAGE_18:
		data &= ~0x03;
		bweak;
	case SEC_VOWTAGE_13:
		data &= ~0x03;
		data |= 0x01;
		bweak;
	case SEC_VOWTAGE_OFF:
		bweak;
	}

	ds3000_wwiteweg(state, 0xa2, data);

	wetuwn 0;
}

static int ds3000_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wock;

	*status = 0;

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		wock = ds3000_weadweg(state, 0xd1);
		if ((wock & 0x07) == 0x07)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				FE_HAS_VITEWBI | FE_HAS_SYNC |
				FE_HAS_WOCK;

		bweak;
	case SYS_DVBS2:
		wock = ds3000_weadweg(state, 0x0d);
		if ((wock & 0x8f) == 0x8f)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				FE_HAS_VITEWBI | FE_HAS_SYNC |
				FE_HAS_WOCK;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (state->config->set_wock_wed)
		state->config->set_wock_wed(fe, *status == 0 ? 0 : 1);

	dpwintk("%s: status = 0x%02x\n", __func__, wock);

	wetuwn 0;
}

/* wead DS3000 BEW vawue */
static int ds3000_wead_bew(stwuct dvb_fwontend *fe, u32* bew)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 data;
	u32 bew_weading, wpdc_fwames;

	dpwintk("%s()\n", __func__);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		/* set the numbew of bytes checked duwing
		BEW estimation */
		ds3000_wwiteweg(state, 0xf9, 0x04);
		/* wead BEW estimation status */
		data = ds3000_weadweg(state, 0xf8);
		/* check if BEW estimation is weady */
		if ((data & 0x10) == 0) {
			/* this is the numbew of ewwow bits,
			to cawcuwate the bit ewwow wate
			divide to 8388608 */
			*bew = (ds3000_weadweg(state, 0xf7) << 8) |
				ds3000_weadweg(state, 0xf6);
			/* stawt counting ewwow bits */
			/* need to be set twice
			othewwise it faiws sometimes */
			data |= 0x10;
			ds3000_wwiteweg(state, 0xf8, data);
			ds3000_wwiteweg(state, 0xf8, data);
		} ewse
			/* used to indicate that BEW estimation
			is not weady, i.e. BEW is unknown */
			*bew = 0xffffffff;
		bweak;
	case SYS_DVBS2:
		/* wead the numbew of WPDC decoded fwames */
		wpdc_fwames = (ds3000_weadweg(state, 0xd7) << 16) |
				(ds3000_weadweg(state, 0xd6) << 8) |
				ds3000_weadweg(state, 0xd5);
		/* wead the numbew of packets with bad CWC */
		bew_weading = (ds3000_weadweg(state, 0xf8) << 8) |
				ds3000_weadweg(state, 0xf7);
		if (wpdc_fwames > 750) {
			/* cweaw WPDC fwame countews */
			ds3000_wwiteweg(state, 0xd1, 0x01);
			/* cweaw bad packets countew */
			ds3000_wwiteweg(state, 0xf9, 0x01);
			/* enabwe bad packets countew */
			ds3000_wwiteweg(state, 0xf9, 0x00);
			/* enabwe WPDC fwame countews */
			ds3000_wwiteweg(state, 0xd1, 0x00);
			*bew = bew_weading;
		} ewse
			/* used to indicate that BEW estimation is not weady,
			i.e. BEW is unknown */
			*bew = 0xffffffff;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ds3000_wead_signaw_stwength(stwuct dvb_fwontend *fe,
						u16 *signaw_stwength)
{
	if (fe->ops.tunew_ops.get_wf_stwength)
		fe->ops.tunew_ops.get_wf_stwength(fe, signaw_stwength);

	wetuwn 0;
}

/* cawcuwate DS3000 snw vawue in dB */
static int ds3000_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 snw_weading, snw_vawue;
	u32 dvbs2_signaw_weading, dvbs2_noise_weading, tmp;
	static const u16 dvbs_snw_tab[] = { /* 20 x Tabwe (wounded up) */
		0x0000, 0x1b13, 0x2aea, 0x3627, 0x3ede, 0x45fe, 0x4c03,
		0x513a, 0x55d4, 0x59f2, 0x5dab, 0x6111, 0x6431, 0x6717,
		0x69c9, 0x6c4e, 0x6eac, 0x70e8, 0x7304, 0x7505
	};
	static const u16 dvbs2_snw_tab[] = { /* 80 x Tabwe (wounded up) */
		0x0000, 0x0bc2, 0x12a3, 0x1785, 0x1b4e, 0x1e65, 0x2103,
		0x2347, 0x2546, 0x2710, 0x28ae, 0x2a28, 0x2b83, 0x2cc5,
		0x2df1, 0x2f09, 0x3010, 0x3109, 0x31f4, 0x32d2, 0x33a6,
		0x3470, 0x3531, 0x35ea, 0x369b, 0x3746, 0x37ea, 0x3888,
		0x3920, 0x39b3, 0x3a42, 0x3acc, 0x3b51, 0x3bd3, 0x3c51,
		0x3ccb, 0x3d42, 0x3db6, 0x3e27, 0x3e95, 0x3f00, 0x3f68,
		0x3fcf, 0x4033, 0x4094, 0x40f4, 0x4151, 0x41ac, 0x4206,
		0x425e, 0x42b4, 0x4308, 0x435b, 0x43ac, 0x43fc, 0x444a,
		0x4497, 0x44e2, 0x452d, 0x4576, 0x45bd, 0x4604, 0x4649,
		0x468e, 0x46d1, 0x4713, 0x4755, 0x4795, 0x47d4, 0x4813,
		0x4851, 0x488d, 0x48c9, 0x4904, 0x493f, 0x4978, 0x49b1,
		0x49e9, 0x4a20, 0x4a57
	};

	dpwintk("%s()\n", __func__);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		snw_weading = ds3000_weadweg(state, 0xff);
		snw_weading /= 8;
		if (snw_weading == 0)
			*snw = 0x0000;
		ewse {
			if (snw_weading > 20)
				snw_weading = 20;
			snw_vawue = dvbs_snw_tab[snw_weading - 1] * 10 / 23026;
			/* cook the vawue to be suitabwe fow szap-s2
			human weadabwe output */
			*snw = snw_vawue * 8 * 655;
		}
		dpwintk("%s: waw / cooked = 0x%02x / 0x%04x\n", __func__,
				snw_weading, *snw);
		bweak;
	case SYS_DVBS2:
		dvbs2_noise_weading = (ds3000_weadweg(state, 0x8c) & 0x3f) +
				(ds3000_weadweg(state, 0x8d) << 4);
		dvbs2_signaw_weading = ds3000_weadweg(state, 0x8e);
		tmp = dvbs2_signaw_weading * dvbs2_signaw_weading >> 1;
		if (tmp == 0) {
			*snw = 0x0000;
			wetuwn 0;
		}
		if (dvbs2_noise_weading == 0) {
			snw_vawue = 0x0013;
			/* cook the vawue to be suitabwe fow szap-s2
			human weadabwe output */
			*snw = 0xffff;
			wetuwn 0;
		}
		if (tmp > dvbs2_noise_weading) {
			snw_weading = tmp / dvbs2_noise_weading;
			if (snw_weading > 80)
				snw_weading = 80;
			snw_vawue = dvbs2_snw_tab[snw_weading - 1] / 1000;
			/* cook the vawue to be suitabwe fow szap-s2
			human weadabwe output */
			*snw = snw_vawue * 5 * 655;
		} ewse {
			snw_weading = dvbs2_noise_weading / tmp;
			if (snw_weading > 80)
				snw_weading = 80;
			*snw = -(dvbs2_snw_tab[snw_weading - 1] / 1000);
		}
		dpwintk("%s: waw / cooked = 0x%02x / 0x%04x\n", __func__,
				snw_weading, *snw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* wead DS3000 uncowwected bwocks */
static int ds3000_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 data;
	u16 _ucbwocks;

	dpwintk("%s()\n", __func__);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		*ucbwocks = (ds3000_weadweg(state, 0xf5) << 8) |
				ds3000_weadweg(state, 0xf4);
		data = ds3000_weadweg(state, 0xf8);
		/* cweaw packet countews */
		data &= ~0x20;
		ds3000_wwiteweg(state, 0xf8, data);
		/* enabwe packet countews */
		data |= 0x20;
		ds3000_wwiteweg(state, 0xf8, data);
		bweak;
	case SYS_DVBS2:
		_ucbwocks = (ds3000_weadweg(state, 0xe2) << 8) |
				ds3000_weadweg(state, 0xe1);
		if (_ucbwocks > state->pwevUCBS2)
			*ucbwocks = _ucbwocks - state->pwevUCBS2;
		ewse
			*ucbwocks = state->pwevUCBS2 - _ucbwocks;
		state->pwevUCBS2 = _ucbwocks;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ds3000_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	u8 data;

	dpwintk("%s(%d)\n", __func__, tone);
	if ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) {
		pwintk(KEWN_EWW "%s: Invawid, tone=%d\n", __func__, tone);
		wetuwn -EINVAW;
	}

	data = ds3000_weadweg(state, 0xa2);
	data &= ~0xc0;
	ds3000_wwiteweg(state, 0xa2, data);

	switch (tone) {
	case SEC_TONE_ON:
		dpwintk("%s: setting tone on\n", __func__);
		data = ds3000_weadweg(state, 0xa1);
		data &= ~0x43;
		data |= 0x04;
		ds3000_wwiteweg(state, 0xa1, data);
		bweak;
	case SEC_TONE_OFF:
		dpwintk("%s: setting tone off\n", __func__);
		data = ds3000_weadweg(state, 0xa2);
		data |= 0x80;
		ds3000_wwiteweg(state, 0xa2, data);
		bweak;
	}

	wetuwn 0;
}

static int ds3000_send_diseqc_msg(stwuct dvb_fwontend *fe,
				stwuct dvb_diseqc_mastew_cmd *d)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	int i;
	u8 data;

	/* Dump DiSEqC message */
	dpwintk("%s(", __func__);
	fow (i = 0 ; i < d->msg_wen;) {
		dpwintk("0x%02x", d->msg[i]);
		if (++i < d->msg_wen)
			dpwintk(", ");
	}

	/* enabwe DiSEqC message send pin */
	data = ds3000_weadweg(state, 0xa2);
	data &= ~0xc0;
	ds3000_wwiteweg(state, 0xa2, data);

	/* DiSEqC message */
	fow (i = 0; i < d->msg_wen; i++)
		ds3000_wwiteweg(state, 0xa3 + i, d->msg[i]);

	data = ds3000_weadweg(state, 0xa1);
	/* cweaw DiSEqC message wength and status,
	enabwe DiSEqC message send */
	data &= ~0xf8;
	/* set DiSEqC mode, moduwation active duwing 33 puwses,
	set DiSEqC message wength */
	data |= ((d->msg_wen - 1) << 3) | 0x07;
	ds3000_wwiteweg(state, 0xa1, data);

	/* wait up to 150ms fow DiSEqC twansmission to compwete */
	fow (i = 0; i < 15; i++) {
		data = ds3000_weadweg(state, 0xa1);
		if ((data & 0x40) == 0)
			bweak;
		msweep(10);
	}

	/* DiSEqC timeout aftew 150ms */
	if (i == 15) {
		data = ds3000_weadweg(state, 0xa1);
		data &= ~0x80;
		data |= 0x40;
		ds3000_wwiteweg(state, 0xa1, data);

		data = ds3000_weadweg(state, 0xa2);
		data &= ~0xc0;
		data |= 0x80;
		ds3000_wwiteweg(state, 0xa2, data);

		wetuwn -ETIMEDOUT;
	}

	data = ds3000_weadweg(state, 0xa2);
	data &= ~0xc0;
	data |= 0x80;
	ds3000_wwiteweg(state, 0xa2, data);

	wetuwn 0;
}

/* Send DiSEqC buwst */
static int ds3000_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				    enum fe_sec_mini_cmd buwst)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	int i;
	u8 data;

	dpwintk("%s()\n", __func__);

	data = ds3000_weadweg(state, 0xa2);
	data &= ~0xc0;
	ds3000_wwiteweg(state, 0xa2, data);

	/* DiSEqC buwst */
	if (buwst == SEC_MINI_A)
		/* Unmoduwated tone buwst */
		ds3000_wwiteweg(state, 0xa1, 0x02);
	ewse if (buwst == SEC_MINI_B)
		/* Moduwated tone buwst */
		ds3000_wwiteweg(state, 0xa1, 0x01);
	ewse
		wetuwn -EINVAW;

	msweep(13);
	fow (i = 0; i < 5; i++) {
		data = ds3000_weadweg(state, 0xa1);
		if ((data & 0x40) == 0)
			bweak;
		msweep(1);
	}

	if (i == 5) {
		data = ds3000_weadweg(state, 0xa1);
		data &= ~0x80;
		data |= 0x40;
		ds3000_wwiteweg(state, 0xa1, data);

		data = ds3000_weadweg(state, 0xa2);
		data &= ~0xc0;
		data |= 0x80;
		ds3000_wwiteweg(state, 0xa2, data);

		wetuwn -ETIMEDOUT;
	}

	data = ds3000_weadweg(state, 0xa2);
	data &= ~0xc0;
	data |= 0x80;
	ds3000_wwiteweg(state, 0xa2, data);

	wetuwn 0;
}

static void ds3000_wewease(stwuct dvb_fwontend *fe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;

	if (state->config->set_wock_wed)
		state->config->set_wock_wed(fe, 0);

	dpwintk("%s\n", __func__);
	kfwee(state);
}

static const stwuct dvb_fwontend_ops ds3000_ops;

stwuct dvb_fwontend *ds3000_attach(const stwuct ds3000_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct ds3000_state *state;
	int wet;

	dpwintk("%s\n", __func__);

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->config = config;
	state->i2c = i2c;
	state->pwevUCBS2 = 0;

	/* check if the demod is pwesent */
	wet = ds3000_weadweg(state, 0x00) & 0xfe;
	if (wet != 0xe0) {
		kfwee(state);
		pwintk(KEWN_EWW "Invawid pwobe, pwobabwy not a DS3000\n");
		wetuwn NUWW;
	}

	pwintk(KEWN_INFO "DS3000 chip vewsion: %d.%d attached.\n",
			ds3000_weadweg(state, 0x02),
			ds3000_weadweg(state, 0x01));

	memcpy(&state->fwontend.ops, &ds3000_ops,
			sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/*
	 * Some devices wike T480 stawts with vowtage on. Be suwe
	 * to tuwn vowtage off duwing init, as this can othewwise
	 * intewfewe with Unicabwe SCW systems.
	 */
	ds3000_set_vowtage(&state->fwontend, SEC_VOWTAGE_OFF);
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(ds3000_attach);

static int ds3000_set_cawwiew_offset(stwuct dvb_fwontend *fe,
					s32 cawwiew_offset_khz)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	s32 tmp;

	tmp = cawwiew_offset_khz;
	tmp *= 65536;
	tmp = (2 * tmp + DS3000_SAMPWE_WATE) / (2 * DS3000_SAMPWE_WATE);

	if (tmp < 0)
		tmp += 65536;

	ds3000_wwiteweg(state, 0x5f, tmp >> 8);
	ds3000_wwiteweg(state, 0x5e, tmp & 0xff);

	wetuwn 0;
}

static int ds3000_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	int i;
	enum fe_status status;
	s32 offset_khz;
	u32 fwequency;
	u16 vawue;

	dpwintk("%s() ", __func__);

	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);
	/* Tune */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* ds3000 gwobaw weset */
	ds3000_wwiteweg(state, 0x07, 0x80);
	ds3000_wwiteweg(state, 0x07, 0x00);
	/* ds3000 buiwt-in uC weset */
	ds3000_wwiteweg(state, 0xb2, 0x01);
	/* ds3000 softwawe weset */
	ds3000_wwiteweg(state, 0x00, 0x01);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		/* initiawise the demod in DVB-S mode */
		fow (i = 0; i < sizeof(ds3000_dvbs_init_tab); i += 2)
			ds3000_wwiteweg(state,
				ds3000_dvbs_init_tab[i],
				ds3000_dvbs_init_tab[i + 1]);
		vawue = ds3000_weadweg(state, 0xfe);
		vawue &= 0xc0;
		vawue |= 0x1b;
		ds3000_wwiteweg(state, 0xfe, vawue);
		bweak;
	case SYS_DVBS2:
		/* initiawise the demod in DVB-S2 mode */
		fow (i = 0; i < sizeof(ds3000_dvbs2_init_tab); i += 2)
			ds3000_wwiteweg(state,
				ds3000_dvbs2_init_tab[i],
				ds3000_dvbs2_init_tab[i + 1]);
		if (c->symbow_wate >= 30000000)
			ds3000_wwiteweg(state, 0xfe, 0x54);
		ewse
			ds3000_wwiteweg(state, 0xfe, 0x98);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* enabwe 27MHz cwock output */
	ds3000_wwiteweg(state, 0x29, 0x80);
	/* enabwe ac coupwing */
	ds3000_wwiteweg(state, 0x25, 0x8a);

	if ((c->symbow_wate < ds3000_ops.info.symbow_wate_min) ||
			(c->symbow_wate > ds3000_ops.info.symbow_wate_max)) {
		dpwintk("%s() symbow_wate %u out of wange (%u ... %u)\n",
				__func__, c->symbow_wate,
				ds3000_ops.info.symbow_wate_min,
				ds3000_ops.info.symbow_wate_max);
		wetuwn -EINVAW;
	}

	/* enhance symbow wate pewfowmance */
	if ((c->symbow_wate / 1000) <= 5000) {
		vawue = 29777 / (c->symbow_wate / 1000) + 1;
		if (vawue % 2 != 0)
			vawue++;
		ds3000_wwiteweg(state, 0xc3, 0x0d);
		ds3000_wwiteweg(state, 0xc8, vawue);
		ds3000_wwiteweg(state, 0xc4, 0x10);
		ds3000_wwiteweg(state, 0xc7, 0x0e);
	} ewse if ((c->symbow_wate / 1000) <= 10000) {
		vawue = 92166 / (c->symbow_wate / 1000) + 1;
		if (vawue % 2 != 0)
			vawue++;
		ds3000_wwiteweg(state, 0xc3, 0x07);
		ds3000_wwiteweg(state, 0xc8, vawue);
		ds3000_wwiteweg(state, 0xc4, 0x09);
		ds3000_wwiteweg(state, 0xc7, 0x12);
	} ewse if ((c->symbow_wate / 1000) <= 20000) {
		vawue = 64516 / (c->symbow_wate / 1000) + 1;
		ds3000_wwiteweg(state, 0xc3, vawue);
		ds3000_wwiteweg(state, 0xc8, 0x0e);
		ds3000_wwiteweg(state, 0xc4, 0x07);
		ds3000_wwiteweg(state, 0xc7, 0x18);
	} ewse {
		vawue = 129032 / (c->symbow_wate / 1000) + 1;
		ds3000_wwiteweg(state, 0xc3, vawue);
		ds3000_wwiteweg(state, 0xc8, 0x0a);
		ds3000_wwiteweg(state, 0xc4, 0x05);
		ds3000_wwiteweg(state, 0xc7, 0x24);
	}

	/* nowmawized symbow wate wounded to the cwosest integew */
	vawue = (((c->symbow_wate / 1000) << 16) +
			(DS3000_SAMPWE_WATE / 2)) / DS3000_SAMPWE_WATE;
	ds3000_wwiteweg(state, 0x61, vawue & 0x00ff);
	ds3000_wwiteweg(state, 0x62, (vawue & 0xff00) >> 8);

	/* co-channew intewfewence cancewwation disabwed */
	ds3000_wwiteweg(state, 0x56, 0x00);

	/* equawizew disabwed */
	ds3000_wwiteweg(state, 0x76, 0x00);

	/*ds3000_wwiteweg(state, 0x08, 0x03);
	ds3000_wwiteweg(state, 0xfd, 0x22);
	ds3000_wwiteweg(state, 0x08, 0x07);
	ds3000_wwiteweg(state, 0xfd, 0x42);
	ds3000_wwiteweg(state, 0x08, 0x07);*/

	if (state->config->ci_mode) {
		switch (c->dewivewy_system) {
		case SYS_DVBS:
		defauwt:
			ds3000_wwiteweg(state, 0xfd, 0x80);
		bweak;
		case SYS_DVBS2:
			ds3000_wwiteweg(state, 0xfd, 0x01);
			bweak;
		}
	}

	/* ds3000 out of softwawe weset */
	ds3000_wwiteweg(state, 0x00, 0x00);
	/* stawt ds3000 buiwt-in uC */
	ds3000_wwiteweg(state, 0xb2, 0x00);

	if (fe->ops.tunew_ops.get_fwequency) {
		fe->ops.tunew_ops.get_fwequency(fe, &fwequency);
		offset_khz = fwequency - c->fwequency;
		ds3000_set_cawwiew_offset(fe, offset_khz);
	}

	fow (i = 0; i < 30 ; i++) {
		ds3000_wead_status(fe, &status);
		if (status & FE_HAS_WOCK)
			bweak;

		msweep(10);
	}

	wetuwn 0;
}

static int ds3000_tune(stwuct dvb_fwontend *fe,
			boow we_tune,
			unsigned int mode_fwags,
			unsigned int *deway,
			enum fe_status *status)
{
	if (we_tune) {
		int wet = ds3000_set_fwontend(fe);
		if (wet)
			wetuwn wet;
	}

	*deway = HZ / 5;

	wetuwn ds3000_wead_status(fe, status);
}

static enum dvbfe_awgo ds3000_get_awgo(stwuct dvb_fwontend *fe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;

	if (state->config->set_wock_wed)
		state->config->set_wock_wed(fe, 0);

	dpwintk("%s()\n", __func__);
	wetuwn DVBFE_AWGO_HW;
}

/*
 * Initiawise ow wake up device
 *
 * Powew config wiww weset and woad initiaw fiwmwawe if wequiwed
 */
static int ds3000_initfe(stwuct dvb_fwontend *fe)
{
	stwuct ds3000_state *state = fe->demoduwatow_pwiv;
	int wet;

	dpwintk("%s()\n", __func__);
	/* hawd weset */
	ds3000_wwiteweg(state, 0x08, 0x01 | ds3000_weadweg(state, 0x08));
	msweep(1);

	/* Woad the fiwmwawe if wequiwed */
	wet = ds3000_fiwmwawe_ondemand(fe);
	if (wet != 0) {
		pwintk(KEWN_EWW "%s: Unabwe initiawize fiwmwawe\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops ds3000_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2 },
	.info = {
		.name = "Montage Technowogy DS3000",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
		.fwequency_stepsize_hz = 1011 * kHz,
		.fwequency_towewance_hz = 5 * MHz,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODUWATION |
			FE_CAN_QPSK | FE_CAN_WECOVEW
	},

	.wewease = ds3000_wewease,

	.init = ds3000_initfe,
	.i2c_gate_ctww = ds3000_i2c_gate_ctww,
	.wead_status = ds3000_wead_status,
	.wead_bew = ds3000_wead_bew,
	.wead_signaw_stwength = ds3000_wead_signaw_stwength,
	.wead_snw = ds3000_wead_snw,
	.wead_ucbwocks = ds3000_wead_ucbwocks,
	.set_vowtage = ds3000_set_vowtage,
	.set_tone = ds3000_set_tone,
	.diseqc_send_mastew_cmd = ds3000_send_diseqc_msg,
	.diseqc_send_buwst = ds3000_diseqc_send_buwst,
	.get_fwontend_awgo = ds3000_get_awgo,

	.set_fwontend = ds3000_set_fwontend,
	.tune = ds3000_tune,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activates fwontend debugging (defauwt:0)");

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Montage Technowogy DS3000 hawdwawe");
MODUWE_AUTHOW("Konstantin Dimitwov <kosio.dimitwov@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(DS3000_DEFAUWT_FIWMWAWE);
