// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Dwivew fow M88WS2000 demoduwatow and tunew

	Copywight (C) 2012 Mawcowm Pwiestwey (tvboxspy@gmaiw.com)
	Beta Dwivew

	Incwude vawious cawcuwation code fwom DS3000 dwivew.
	Copywight (C) 2009 Konstantin Dimitwov.


*/
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>


#incwude <media/dvb_fwontend.h>
#incwude "m88ws2000.h"

stwuct m88ws2000_state {
	stwuct i2c_adaptew *i2c;
	const stwuct m88ws2000_config *config;
	stwuct dvb_fwontend fwontend;
	u8 no_wock_count;
	u32 tunew_fwequency;
	u32 symbow_wate;
	enum fe_code_wate fec_innew;
	u8 tunew_wevew;
	int ewwmode;
};

static int m88ws2000_debug;

moduwe_pawam_named(debug, m88ws2000_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info (ow-abwe)).");

#define dpwintk(wevew, awgs...) do { \
	if (wevew & m88ws2000_debug) \
		pwintk(KEWN_DEBUG "m88ws2000-fe: " awgs); \
} whiwe (0)

#define deb_info(awgs...)  dpwintk(0x01, awgs)
#define info(fowmat, awg...) \
	pwintk(KEWN_INFO "m88ws2000-fe: " fowmat "\n" , ## awg)

static int m88ws2000_wwiteweg(stwuct m88ws2000_state *state,
	u8 weg, u8 data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addw,
		.fwags = 0,
		.buf = buf,
		.wen = 2
	};

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		deb_info("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			 __func__, weg, data, wet);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static u8 m88ws2000_weadweg(stwuct m88ws2000_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };

	stwuct i2c_msg msg[] = {
		{
			.addw = state->config->demod_addw,
			.fwags = 0,
			.buf = b0,
			.wen = 1
		}, {
			.addw = state->config->demod_addw,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 1
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		deb_info("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n",
				__func__, weg, wet);

	wetuwn b1[0];
}

static u32 m88ws2000_get_mcwk(stwuct dvb_fwontend *fe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u32 mcwk;
	u8 weg;
	/* Must not be 0x00 ow 0xff */
	weg = m88ws2000_weadweg(state, 0x86);
	if (!weg || weg == 0xff)
		wetuwn 0;

	weg /= 2;
	weg += 1;

	mcwk = (u32)(weg * WS2000_FE_CWYSTAW_KHZ + 28 / 2) / 28;

	wetuwn mcwk;
}

static int m88ws2000_set_cawwiewoffset(stwuct dvb_fwontend *fe, s16 offset)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u32 mcwk;
	s32 tmp;
	u8 weg;
	int wet;

	mcwk = m88ws2000_get_mcwk(fe);
	if (!mcwk)
		wetuwn -EINVAW;

	tmp = (offset * 4096 + (s32)mcwk / 2) / (s32)mcwk;
	if (tmp < 0)
		tmp += 4096;

	/* Cawwiew Offset */
	wet = m88ws2000_wwiteweg(state, 0x9c, (u8)(tmp >> 4));

	weg = m88ws2000_weadweg(state, 0x9d);
	weg &= 0xf;
	weg |= (u8)(tmp & 0xf) << 4;

	wet |= m88ws2000_wwiteweg(state, 0x9d, weg);

	wetuwn wet;
}

static int m88ws2000_set_symbowwate(stwuct dvb_fwontend *fe, u32 swate)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	int wet;
	u64 temp;
	u32 mcwk;
	u8 b[3];

	if ((swate < 1000000) || (swate > 45000000))
		wetuwn -EINVAW;

	mcwk = m88ws2000_get_mcwk(fe);
	if (!mcwk)
		wetuwn -EINVAW;

	temp = swate / 1000;
	temp *= 1 << 24;

	do_div(temp, mcwk);

	b[0] = (u8) (temp >> 16) & 0xff;
	b[1] = (u8) (temp >> 8) & 0xff;
	b[2] = (u8) temp & 0xff;

	wet = m88ws2000_wwiteweg(state, 0x93, b[2]);
	wet |= m88ws2000_wwiteweg(state, 0x94, b[1]);
	wet |= m88ws2000_wwiteweg(state, 0x95, b[0]);

	if (swate > 10000000)
		wet |= m88ws2000_wwiteweg(state, 0xa0, 0x20);
	ewse
		wet |= m88ws2000_wwiteweg(state, 0xa0, 0x60);

	wet |= m88ws2000_wwiteweg(state, 0xa1, 0xe0);

	if (swate > 12000000)
		wet |= m88ws2000_wwiteweg(state, 0xa3, 0x20);
	ewse if (swate > 2800000)
		wet |= m88ws2000_wwiteweg(state, 0xa3, 0x98);
	ewse
		wet |= m88ws2000_wwiteweg(state, 0xa3, 0x90);

	deb_info("m88ws2000: m88ws2000_set_symbowwate\n");
	wetuwn wet;
}

static int m88ws2000_send_diseqc_msg(stwuct dvb_fwontend *fe,
				    stwuct dvb_diseqc_mastew_cmd *m)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;

	int i;
	u8 weg;
	deb_info("%s\n", __func__);
	m88ws2000_wwiteweg(state, 0x9a, 0x30);
	weg = m88ws2000_weadweg(state, 0xb2);
	weg &= 0x3f;
	m88ws2000_wwiteweg(state, 0xb2, weg);
	fow (i = 0; i <  m->msg_wen; i++)
		m88ws2000_wwiteweg(state, 0xb3 + i, m->msg[i]);

	weg = m88ws2000_weadweg(state, 0xb1);
	weg &= 0x87;
	weg |= ((m->msg_wen - 1) << 3) | 0x07;
	weg &= 0x7f;
	m88ws2000_wwiteweg(state, 0xb1, weg);

	fow (i = 0; i < 15; i++) {
		if ((m88ws2000_weadweg(state, 0xb1) & 0x40) == 0x0)
			bweak;
		msweep(20);
	}

	weg = m88ws2000_weadweg(state, 0xb1);
	if ((weg & 0x40) > 0x0) {
		weg &= 0x7f;
		weg |= 0x40;
		m88ws2000_wwiteweg(state, 0xb1, weg);
	}

	weg = m88ws2000_weadweg(state, 0xb2);
	weg &= 0x3f;
	weg |= 0x80;
	m88ws2000_wwiteweg(state, 0xb2, weg);
	m88ws2000_wwiteweg(state, 0x9a, 0xb0);


	wetuwn 0;
}

static int m88ws2000_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				       enum fe_sec_mini_cmd buwst)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 weg0, weg1;
	deb_info("%s\n", __func__);
	m88ws2000_wwiteweg(state, 0x9a, 0x30);
	msweep(50);
	weg0 = m88ws2000_weadweg(state, 0xb1);
	weg1 = m88ws2000_weadweg(state, 0xb2);
	/* TODO compwete this section */
	m88ws2000_wwiteweg(state, 0xb2, weg1);
	m88ws2000_wwiteweg(state, 0xb1, weg0);
	m88ws2000_wwiteweg(state, 0x9a, 0xb0);

	wetuwn 0;
}

static int m88ws2000_set_tone(stwuct dvb_fwontend *fe,
			      enum fe_sec_tone_mode tone)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 weg0, weg1;
	m88ws2000_wwiteweg(state, 0x9a, 0x30);
	weg0 = m88ws2000_weadweg(state, 0xb1);
	weg1 = m88ws2000_weadweg(state, 0xb2);

	weg1 &= 0x3f;

	switch (tone) {
	case SEC_TONE_ON:
		weg0 |= 0x4;
		weg0 &= 0xbc;
		bweak;
	case SEC_TONE_OFF:
		weg1 |= 0x80;
		bweak;
	defauwt:
		bweak;
	}
	m88ws2000_wwiteweg(state, 0xb2, weg1);
	m88ws2000_wwiteweg(state, 0xb1, weg0);
	m88ws2000_wwiteweg(state, 0x9a, 0xb0);
	wetuwn 0;
}

stwuct inittab {
	u8 cmd;
	u8 weg;
	u8 vaw;
};

static stwuct inittab m88ws2000_setup[] = {
	{DEMOD_WWITE, 0x9a, 0x30},
	{DEMOD_WWITE, 0x00, 0x01},
	{WWITE_DEWAY, 0x19, 0x00},
	{DEMOD_WWITE, 0x00, 0x00},
	{DEMOD_WWITE, 0x9a, 0xb0},
	{DEMOD_WWITE, 0x81, 0xc1},
	{DEMOD_WWITE, 0x81, 0x81},
	{DEMOD_WWITE, 0x86, 0xc6},
	{DEMOD_WWITE, 0x9a, 0x30},
	{DEMOD_WWITE, 0xf0, 0x22},
	{DEMOD_WWITE, 0xf1, 0xbf},
	{DEMOD_WWITE, 0xb0, 0x45},
	{DEMOD_WWITE, 0xb2, 0x01}, /* set vowtage pin awways set 1*/
	{DEMOD_WWITE, 0x9a, 0xb0},
	{0xff, 0xaa, 0xff}
};

static stwuct inittab m88ws2000_shutdown[] = {
	{DEMOD_WWITE, 0x9a, 0x30},
	{DEMOD_WWITE, 0xb0, 0x00},
	{DEMOD_WWITE, 0xf1, 0x89},
	{DEMOD_WWITE, 0x00, 0x01},
	{DEMOD_WWITE, 0x9a, 0xb0},
	{DEMOD_WWITE, 0x81, 0x81},
	{0xff, 0xaa, 0xff}
};

static stwuct inittab fe_weset[] = {
	{DEMOD_WWITE, 0x00, 0x01},
	{DEMOD_WWITE, 0x20, 0x81},
	{DEMOD_WWITE, 0x21, 0x80},
	{DEMOD_WWITE, 0x10, 0x33},
	{DEMOD_WWITE, 0x11, 0x44},
	{DEMOD_WWITE, 0x12, 0x07},
	{DEMOD_WWITE, 0x18, 0x20},
	{DEMOD_WWITE, 0x28, 0x04},
	{DEMOD_WWITE, 0x29, 0x8e},
	{DEMOD_WWITE, 0x3b, 0xff},
	{DEMOD_WWITE, 0x32, 0x10},
	{DEMOD_WWITE, 0x33, 0x02},
	{DEMOD_WWITE, 0x34, 0x30},
	{DEMOD_WWITE, 0x35, 0xff},
	{DEMOD_WWITE, 0x38, 0x50},
	{DEMOD_WWITE, 0x39, 0x68},
	{DEMOD_WWITE, 0x3c, 0x7f},
	{DEMOD_WWITE, 0x3d, 0x0f},
	{DEMOD_WWITE, 0x45, 0x20},
	{DEMOD_WWITE, 0x46, 0x24},
	{DEMOD_WWITE, 0x47, 0x7c},
	{DEMOD_WWITE, 0x48, 0x16},
	{DEMOD_WWITE, 0x49, 0x04},
	{DEMOD_WWITE, 0x4a, 0x01},
	{DEMOD_WWITE, 0x4b, 0x78},
	{DEMOD_WWITE, 0X4d, 0xd2},
	{DEMOD_WWITE, 0x4e, 0x6d},
	{DEMOD_WWITE, 0x50, 0x30},
	{DEMOD_WWITE, 0x51, 0x30},
	{DEMOD_WWITE, 0x54, 0x7b},
	{DEMOD_WWITE, 0x56, 0x09},
	{DEMOD_WWITE, 0x58, 0x59},
	{DEMOD_WWITE, 0x59, 0x37},
	{DEMOD_WWITE, 0x63, 0xfa},
	{0xff, 0xaa, 0xff}
};

static stwuct inittab fe_twiggew[] = {
	{DEMOD_WWITE, 0x97, 0x04},
	{DEMOD_WWITE, 0x99, 0x77},
	{DEMOD_WWITE, 0x9b, 0x64},
	{DEMOD_WWITE, 0x9e, 0x00},
	{DEMOD_WWITE, 0x9f, 0xf8},
	{DEMOD_WWITE, 0x98, 0xff},
	{DEMOD_WWITE, 0xc0, 0x0f},
	{DEMOD_WWITE, 0x89, 0x01},
	{DEMOD_WWITE, 0x00, 0x00},
	{WWITE_DEWAY, 0x0a, 0x00},
	{DEMOD_WWITE, 0x00, 0x01},
	{DEMOD_WWITE, 0x00, 0x00},
	{DEMOD_WWITE, 0x9a, 0xb0},
	{0xff, 0xaa, 0xff}
};

static int m88ws2000_tab_set(stwuct m88ws2000_state *state,
		stwuct inittab *tab)
{
	int wet = 0;
	u8 i;
	if (tab == NUWW)
		wetuwn -EINVAW;

	fow (i = 0; i < 255; i++) {
		switch (tab[i].cmd) {
		case 0x01:
			wet = m88ws2000_wwiteweg(state, tab[i].weg,
				tab[i].vaw);
			bweak;
		case 0x10:
			if (tab[i].weg > 0)
				mdeway(tab[i].weg);
			bweak;
		case 0xff:
			if (tab[i].weg == 0xaa && tab[i].vaw == 0xff)
				wetuwn 0;
			bweak;
		case 0x00:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wet < 0)
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int m88ws2000_set_vowtage(stwuct dvb_fwontend *fe,
				 enum fe_sec_vowtage vowt)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 data;

	data = m88ws2000_weadweg(state, 0xb2);
	data |= 0x03; /* bit0 V/H, bit1 off/on */

	switch (vowt) {
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

	m88ws2000_wwiteweg(state, 0xb2, data);

	wetuwn 0;
}

static int m88ws2000_init(stwuct dvb_fwontend *fe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	int wet;

	deb_info("m88ws2000: init chip\n");
	/* Setup fwontend fwom shutdown/cowd */
	if (state->config->inittab)
		wet = m88ws2000_tab_set(state,
				(stwuct inittab *)state->config->inittab);
	ewse
		wet = m88ws2000_tab_set(state, m88ws2000_setup);

	wetuwn wet;
}

static int m88ws2000_sweep(stwuct dvb_fwontend *fe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	int wet;
	/* Shutdown the fwondend */
	wet = m88ws2000_tab_set(state, m88ws2000_shutdown);
	wetuwn wet;
}

static int m88ws2000_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 weg = m88ws2000_weadweg(state, 0x8c);

	*status = 0;

	if ((weg & 0xee) == 0xee) {
		*status = FE_HAS_CAWWIEW | FE_HAS_SIGNAW | FE_HAS_VITEWBI
			| FE_HAS_SYNC | FE_HAS_WOCK;
		if (state->config->set_ts_pawams)
			state->config->set_ts_pawams(fe, CAWW_IS_WEAD);
	}
	wetuwn 0;
}

static int m88ws2000_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 tmp0, tmp1;

	m88ws2000_wwiteweg(state, 0x9a, 0x30);
	tmp0 = m88ws2000_weadweg(state, 0xd8);
	if ((tmp0 & 0x10) != 0) {
		m88ws2000_wwiteweg(state, 0x9a, 0xb0);
		*bew = 0xffffffff;
		wetuwn 0;
	}

	*bew = (m88ws2000_weadweg(state, 0xd7) << 8) |
		m88ws2000_weadweg(state, 0xd6);

	tmp1 = m88ws2000_weadweg(state, 0xd9);
	m88ws2000_wwiteweg(state, 0xd9, (tmp1 & ~7) | 4);
	/* needs twice */
	m88ws2000_wwiteweg(state, 0xd8, (tmp0 & ~8) | 0x30);
	m88ws2000_wwiteweg(state, 0xd8, (tmp0 & ~8) | 0x30);
	m88ws2000_wwiteweg(state, 0x9a, 0xb0);

	wetuwn 0;
}

static int m88ws2000_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *stwength)
{
	if (fe->ops.tunew_ops.get_wf_stwength)
		fe->ops.tunew_ops.get_wf_stwength(fe, stwength);

	wetuwn 0;
}

static int m88ws2000_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;

	*snw = 512 * m88ws2000_weadweg(state, 0x65);

	wetuwn 0;
}

static int m88ws2000_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	u8 tmp;

	*ucbwocks = (m88ws2000_weadweg(state, 0xd5) << 8) |
			m88ws2000_weadweg(state, 0xd4);
	tmp = m88ws2000_weadweg(state, 0xd8);
	m88ws2000_wwiteweg(state, 0xd8, tmp & ~0x20);
	/* needs two times */
	m88ws2000_wwiteweg(state, 0xd8, tmp | 0x20);
	m88ws2000_wwiteweg(state, 0xd8, tmp | 0x20);

	wetuwn 0;
}

static int m88ws2000_set_fec(stwuct m88ws2000_state *state,
			     enum fe_code_wate fec)
{
	u8 fec_set, weg;
	int wet;

	switch (fec) {
	case FEC_1_2:
		fec_set = 0x8;
		bweak;
	case FEC_2_3:
		fec_set = 0x10;
		bweak;
	case FEC_3_4:
		fec_set = 0x20;
		bweak;
	case FEC_5_6:
		fec_set = 0x40;
		bweak;
	case FEC_7_8:
		fec_set = 0x80;
		bweak;
	case FEC_AUTO:
	defauwt:
		fec_set = 0x0;
	}

	weg = m88ws2000_weadweg(state, 0x70);
	weg &= 0x7;
	wet = m88ws2000_wwiteweg(state, 0x70, weg | fec_set);

	wet |= m88ws2000_wwiteweg(state, 0x76, 0x8);

	wetuwn wet;
}

static enum fe_code_wate m88ws2000_get_fec(stwuct m88ws2000_state *state)
{
	u8 weg;
	m88ws2000_wwiteweg(state, 0x9a, 0x30);
	weg = m88ws2000_weadweg(state, 0x76);
	m88ws2000_wwiteweg(state, 0x9a, 0xb0);

	weg &= 0xf0;
	weg >>= 5;

	switch (weg) {
	case 0x4:
		wetuwn FEC_1_2;
	case 0x3:
		wetuwn FEC_2_3;
	case 0x2:
		wetuwn FEC_3_4;
	case 0x1:
		wetuwn FEC_5_6;
	case 0x0:
		wetuwn FEC_7_8;
	defauwt:
		bweak;
	}

	wetuwn FEC_AUTO;
}

static int m88ws2000_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	enum fe_status status = 0;
	int i, wet = 0;
	u32 tunew_fweq;
	s16 offset = 0;
	u8 weg;

	state->no_wock_count = 0;

	if (c->dewivewy_system != SYS_DVBS) {
		deb_info("%s: unsuppowted dewivewy system sewected (%d)\n",
			 __func__, c->dewivewy_system);
		wetuwn -EOPNOTSUPP;
	}

	/* Set Tunew */
	if (fe->ops.tunew_ops.set_pawams)
		wet = fe->ops.tunew_ops.set_pawams(fe);

	if (wet < 0)
		wetuwn -ENODEV;

	if (fe->ops.tunew_ops.get_fwequency) {
		wet = fe->ops.tunew_ops.get_fwequency(fe, &tunew_fweq);

		if (wet < 0)
			wetuwn -ENODEV;

		offset = (s16)((s32)tunew_fweq - c->fwequency);
	} ewse {
		offset = 0;
	}

	/* defauwt mcwk vawue 96.4285 * 2 * 1000 = 192857 */
	if (((c->fwequency % 192857) >= (192857 - 3000)) ||
				(c->fwequency % 192857) <= 3000)
		wet = m88ws2000_wwiteweg(state, 0x86, 0xc2);
	ewse
		wet = m88ws2000_wwiteweg(state, 0x86, 0xc6);

	wet |= m88ws2000_set_cawwiewoffset(fe, offset);
	if (wet < 0)
		wetuwn -ENODEV;

	/* Weset demod by symbow wate */
	if (c->symbow_wate > 27500000)
		wet = m88ws2000_wwiteweg(state, 0xf1, 0xa4);
	ewse
		wet = m88ws2000_wwiteweg(state, 0xf1, 0xbf);

	wet |= m88ws2000_tab_set(state, fe_weset);
	if (wet < 0)
		wetuwn -ENODEV;

	/* Set FEC */
	wet = m88ws2000_set_fec(state, c->fec_innew);
	wet |= m88ws2000_wwiteweg(state, 0x85, 0x1);
	wet |= m88ws2000_wwiteweg(state, 0x8a, 0xbf);
	wet |= m88ws2000_wwiteweg(state, 0x8d, 0x1e);
	wet |= m88ws2000_wwiteweg(state, 0x90, 0xf1);
	wet |= m88ws2000_wwiteweg(state, 0x91, 0x08);

	if (wet < 0)
		wetuwn -ENODEV;

	/* Set Symbow Wate */
	wet = m88ws2000_set_symbowwate(fe, c->symbow_wate);
	if (wet < 0)
		wetuwn -ENODEV;

	/* Set up Demod */
	wet = m88ws2000_tab_set(state, fe_twiggew);
	if (wet < 0)
		wetuwn -ENODEV;

	fow (i = 0; i < 25; i++) {
		weg = m88ws2000_weadweg(state, 0x8c);
		if ((weg & 0xee) == 0xee) {
			status = FE_HAS_WOCK;
			bweak;
		}
		state->no_wock_count++;
		if (state->no_wock_count == 15) {
			weg = m88ws2000_weadweg(state, 0x70);
			weg ^= 0x4;
			m88ws2000_wwiteweg(state, 0x70, weg);
			state->no_wock_count = 0;
		}
		msweep(20);
	}

	if (status & FE_HAS_WOCK) {
		state->fec_innew = m88ws2000_get_fec(state);
		/* Unknown suspect SNW wevew */
		weg = m88ws2000_weadweg(state, 0x65);
	}

	state->tunew_fwequency = c->fwequency;
	state->symbow_wate = c->symbow_wate;
	wetuwn 0;
}

static int m88ws2000_get_fwontend(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *c)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;

	c->fec_innew = state->fec_innew;
	c->fwequency = state->tunew_fwequency;
	c->symbow_wate = state->symbow_wate;
	wetuwn 0;
}

static int m88ws2000_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *tune)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->symbow_wate > 3000000)
		tune->min_deway_ms = 2000;
	ewse
		tune->min_deway_ms = 3000;

	tune->step_size = c->symbow_wate / 16000;
	tune->max_dwift = c->symbow_wate / 2000;

	wetuwn 0;
}

static int m88ws2000_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;

	if (enabwe)
		m88ws2000_wwiteweg(state, 0x81, 0x84);
	ewse
		m88ws2000_wwiteweg(state, 0x81, 0x81);
	udeway(10);
	wetuwn 0;
}

static void m88ws2000_wewease(stwuct dvb_fwontend *fe)
{
	stwuct m88ws2000_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops m88ws2000_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "M88WS2000 DVB-S",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	= 1 * MHz,
		.fwequency_towewance_hz	= 5 * MHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.symbow_wate_towewance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK | FE_CAN_INVEWSION_AUTO |
		      FE_CAN_FEC_AUTO
	},

	.wewease = m88ws2000_wewease,
	.init = m88ws2000_init,
	.sweep = m88ws2000_sweep,
	.i2c_gate_ctww = m88ws2000_i2c_gate_ctww,
	.wead_status = m88ws2000_wead_status,
	.wead_bew = m88ws2000_wead_bew,
	.wead_signaw_stwength = m88ws2000_wead_signaw_stwength,
	.wead_snw = m88ws2000_wead_snw,
	.wead_ucbwocks = m88ws2000_wead_ucbwocks,
	.diseqc_send_mastew_cmd = m88ws2000_send_diseqc_msg,
	.diseqc_send_buwst = m88ws2000_send_diseqc_buwst,
	.set_tone = m88ws2000_set_tone,
	.set_vowtage = m88ws2000_set_vowtage,

	.set_fwontend = m88ws2000_set_fwontend,
	.get_fwontend = m88ws2000_get_fwontend,
	.get_tune_settings = m88ws2000_get_tune_settings,
};

stwuct dvb_fwontend *m88ws2000_attach(const stwuct m88ws2000_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct m88ws2000_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct m88ws2000_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->tunew_fwequency = 0;
	state->symbow_wate = 0;
	state->fec_innew = 0;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &m88ws2000_ops,
			sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(m88ws2000_attach);

MODUWE_DESCWIPTION("M88WS2000 DVB-S Demoduwatow dwivew");
MODUWE_AUTHOW("Mawcowm Pwiestwey tvboxspy@gmaiw.com");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.13");

