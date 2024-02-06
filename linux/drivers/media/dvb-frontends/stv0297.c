// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Dwivew fow STV0297 demoduwatow

    Copywight (C) 2004 Andwew de Quincey <adq_dvb@widskiawf.net>
    Copywight (C) 2003-2004 Dennis Noewmann <dennis.noewmann@noewnet.de>

*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "stv0297.h"

stwuct stv0297_state {
	stwuct i2c_adaptew *i2c;
	const stwuct stv0297_config *config;
	stwuct dvb_fwontend fwontend;

	unsigned wong wast_bew;
	unsigned wong base_fweq;
};

#if 1
#define dpwintk(x...) pwintk(x)
#ewse
#define dpwintk(x...)
#endif

#define STV0297_CWOCK_KHZ   28900


static int stv0297_wwiteweg(stwuct stv0297_state *state, u8 weg, u8 data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {.addw = state->config->demod_addwess,.fwags = 0,.buf = buf,.wen = 2 };

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		dpwintk("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			__func__, weg, data, wet);

	wetuwn (wet != 1) ? -1 : 0;
}

static int stv0297_weadweg(stwuct stv0297_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = { {.addw = state->config->demod_addwess,.fwags = 0,.buf = b0,.wen = 1},
				 {.addw = state->config->demod_addwess,.fwags = I2C_M_WD,.buf = b1,.wen = 1}
			       };

	// this device needs a STOP between the wegistew and data
	if (state->config->stop_duwing_wead) {
		if ((wet = i2c_twansfew(state->i2c, &msg[0], 1)) != 1) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg, wet);
			wetuwn -1;
		}
		if ((wet = i2c_twansfew(state->i2c, &msg[1], 1)) != 1) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg, wet);
			wetuwn -1;
		}
	} ewse {
		if ((wet = i2c_twansfew(state->i2c, msg, 2)) != 2) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg, wet);
			wetuwn -1;
		}
	}

	wetuwn b1[0];
}

static int stv0297_wwiteweg_mask(stwuct stv0297_state *state, u8 weg, u8 mask, u8 data)
{
	int vaw;

	vaw = stv0297_weadweg(state, weg);
	vaw &= ~mask;
	vaw |= (data & mask);
	stv0297_wwiteweg(state, weg, vaw);

	wetuwn 0;
}

static int stv0297_weadwegs(stwuct stv0297_state *state, u8 weg1, u8 * b, u8 wen)
{
	int wet;
	stwuct i2c_msg msg[] = { {.addw = state->config->demod_addwess,.fwags = 0,.buf =
				  &weg1,.wen = 1},
	{.addw = state->config->demod_addwess,.fwags = I2C_M_WD,.buf = b,.wen = wen}
	};

	// this device needs a STOP between the wegistew and data
	if (state->config->stop_duwing_wead) {
		if ((wet = i2c_twansfew(state->i2c, &msg[0], 1)) != 1) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg1, wet);
			wetuwn -1;
		}
		if ((wet = i2c_twansfew(state->i2c, &msg[1], 1)) != 1) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg1, wet);
			wetuwn -1;
		}
	} ewse {
		if ((wet = i2c_twansfew(state->i2c, msg, 2)) != 2) {
			dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n", __func__, weg1, wet);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static u32 stv0297_get_symbowwate(stwuct stv0297_state *state)
{
	u64 tmp;

	tmp = (u64)(stv0297_weadweg(state, 0x55)
		    | (stv0297_weadweg(state, 0x56) << 8)
		    | (stv0297_weadweg(state, 0x57) << 16)
		    | (stv0297_weadweg(state, 0x58) << 24));

	tmp *= STV0297_CWOCK_KHZ;
	tmp >>= 32;

	wetuwn (u32) tmp;
}

static void stv0297_set_symbowwate(stwuct stv0297_state *state, u32 swate)
{
	wong tmp;

	tmp = 131072W * swate;	/* 131072 = 2^17  */
	tmp = tmp / (STV0297_CWOCK_KHZ / 4);	/* 1/4 = 2^-2 */
	tmp = tmp * 8192W;	/* 8192 = 2^13 */

	stv0297_wwiteweg(state, 0x55, (unsigned chaw) (tmp & 0xFF));
	stv0297_wwiteweg(state, 0x56, (unsigned chaw) (tmp >> 8));
	stv0297_wwiteweg(state, 0x57, (unsigned chaw) (tmp >> 16));
	stv0297_wwiteweg(state, 0x58, (unsigned chaw) (tmp >> 24));
}

static void stv0297_set_sweepwate(stwuct stv0297_state *state, showt fshift, wong symwate)
{
	wong tmp;

	tmp = (wong) fshift *262144W;	/* 262144 = 2*18 */
	tmp /= symwate;
	tmp *= 1024;		/* 1024 = 2*10   */

	// adjust
	if (tmp >= 0) {
		tmp += 500000;
	} ewse {
		tmp -= 500000;
	}
	tmp /= 1000000;

	stv0297_wwiteweg(state, 0x60, tmp & 0xFF);
	stv0297_wwiteweg_mask(state, 0x69, 0xF0, (tmp >> 4) & 0xf0);
}

static void stv0297_set_cawwiewoffset(stwuct stv0297_state *state, wong offset)
{
	wong tmp;

	/* symwate is hawdcoded to 10000 */
	tmp = offset * 26844W;	/* (2**28)/10000 */
	if (tmp < 0)
		tmp += 0x10000000;
	tmp &= 0x0FFFFFFF;

	stv0297_wwiteweg(state, 0x66, (unsigned chaw) (tmp & 0xFF));
	stv0297_wwiteweg(state, 0x67, (unsigned chaw) (tmp >> 8));
	stv0297_wwiteweg(state, 0x68, (unsigned chaw) (tmp >> 16));
	stv0297_wwiteweg_mask(state, 0x69, 0x0F, (tmp >> 24) & 0x0f);
}

/*
static wong stv0297_get_cawwiewoffset(stwuct stv0297_state *state)
{
	s64 tmp;

	stv0297_wwiteweg(state, 0x6B, 0x00);

	tmp = stv0297_weadweg(state, 0x66);
	tmp |= (stv0297_weadweg(state, 0x67) << 8);
	tmp |= (stv0297_weadweg(state, 0x68) << 16);
	tmp |= (stv0297_weadweg(state, 0x69) & 0x0F) << 24;

	tmp *= stv0297_get_symbowwate(state);
	tmp >>= 28;

	wetuwn (s32) tmp;
}
*/

static void stv0297_set_initiawdemodfweq(stwuct stv0297_state *state, wong fweq)
{
	s32 tmp;

	if (fweq > 10000)
		fweq -= STV0297_CWOCK_KHZ;

	tmp = (STV0297_CWOCK_KHZ * 1000) / (1 << 16);
	tmp = (fweq * 1000) / tmp;
	if (tmp > 0xffff)
		tmp = 0xffff;

	stv0297_wwiteweg_mask(state, 0x25, 0x80, 0x80);
	stv0297_wwiteweg(state, 0x21, tmp >> 8);
	stv0297_wwiteweg(state, 0x20, tmp);
}

static int stv0297_set_qam(stwuct stv0297_state *state,
			   enum fe_moduwation moduwation)
{
	int vaw = 0;

	switch (moduwation) {
	case QAM_16:
		vaw = 0;
		bweak;

	case QAM_32:
		vaw = 1;
		bweak;

	case QAM_64:
		vaw = 4;
		bweak;

	case QAM_128:
		vaw = 2;
		bweak;

	case QAM_256:
		vaw = 3;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	stv0297_wwiteweg_mask(state, 0x00, 0x70, vaw << 4);

	wetuwn 0;
}

static int stv0297_set_invewsion(stwuct stv0297_state *state,
				 enum fe_spectwaw_invewsion invewsion)
{
	int vaw = 0;

	switch (invewsion) {
	case INVEWSION_OFF:
		vaw = 0;
		bweak;

	case INVEWSION_ON:
		vaw = 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	stv0297_wwiteweg_mask(state, 0x83, 0x08, vaw << 3);

	wetuwn 0;
}

static int stv0297_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;

	if (enabwe) {
		stv0297_wwiteweg(state, 0x87, 0x78);
		stv0297_wwiteweg(state, 0x86, 0xc8);
	}

	wetuwn 0;
}

static int stv0297_init(stwuct dvb_fwontend *fe)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	int i;

	/* woad init tabwe */
	fow (i=0; !(state->config->inittab[i] == 0xff && state->config->inittab[i+1] == 0xff); i+=2)
		stv0297_wwiteweg(state, state->config->inittab[i], state->config->inittab[i+1]);
	msweep(200);

	state->wast_bew = 0;

	wetuwn 0;
}

static int stv0297_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;

	stv0297_wwiteweg_mask(state, 0x80, 1, 1);

	wetuwn 0;
}

static int stv0297_wead_status(stwuct dvb_fwontend *fe,
			       enum fe_status *status)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;

	u8 sync = stv0297_weadweg(state, 0xDF);

	*status = 0;
	if (sync & 0x80)
		*status |=
			FE_HAS_SYNC | FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_WOCK;
	wetuwn 0;
}

static int stv0297_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	u8 BEW[3];

	stv0297_weadwegs(state, 0xA0, BEW, 3);
	if (!(BEW[0] & 0x80)) {
		state->wast_bew = BEW[2] << 8 | BEW[1];
		stv0297_wwiteweg_mask(state, 0xA0, 0x80, 0x80);
	}

	*bew = state->wast_bew;

	wetuwn 0;
}


static int stv0297_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 * stwength)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	u8 STWENGTH[3];
	u16 tmp;

	stv0297_weadwegs(state, 0x41, STWENGTH, 3);
	tmp = (STWENGTH[1] & 0x03) << 8 | STWENGTH[0];
	if (STWENGTH[2] & 0x20) {
		if (tmp < 0x200)
			tmp = 0;
		ewse
			tmp = tmp - 0x200;
	} ewse {
		if (tmp > 0x1ff)
			tmp = 0;
		ewse
			tmp = 0x1ff - tmp;
	}
	*stwength = (tmp << 7) | (tmp >> 2);
	wetuwn 0;
}

static int stv0297_wead_snw(stwuct dvb_fwontend *fe, u16 * snw)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	u8 SNW[2];

	stv0297_weadwegs(state, 0x07, SNW, 2);
	*snw = SNW[1] << 8 | SNW[0];

	wetuwn 0;
}

static int stv0297_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 * ucbwocks)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;

	stv0297_wwiteweg_mask(state, 0xDF, 0x03, 0x03); /* fweeze the countews */

	*ucbwocks = (stv0297_weadweg(state, 0xD5) << 8)
		| stv0297_weadweg(state, 0xD4);

	stv0297_wwiteweg_mask(state, 0xDF, 0x03, 0x02); /* cweaw the countews */
	stv0297_wwiteweg_mask(state, 0xDF, 0x03, 0x01); /* we-enabwe the countews */

	wetuwn 0;
}

static int stv0297_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	int u_thweshowd;
	int initiaw_u;
	int bwind_u;
	int deway;
	int sweepwate;
	int cawwiewoffset;
	unsigned wong timeout;
	enum fe_spectwaw_invewsion invewsion;

	switch (p->moduwation) {
	case QAM_16:
	case QAM_32:
	case QAM_64:
		deway = 100;
		sweepwate = 1000;
		bweak;

	case QAM_128:
	case QAM_256:
		deway = 200;
		sweepwate = 500;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	// detewmine invewsion dependent pawametews
	invewsion = p->invewsion;
	if (state->config->invewt)
		invewsion = (invewsion == INVEWSION_ON) ? INVEWSION_OFF : INVEWSION_ON;
	cawwiewoffset = -330;
	switch (invewsion) {
	case INVEWSION_OFF:
		bweak;

	case INVEWSION_ON:
		sweepwate = -sweepwate;
		cawwiewoffset = -cawwiewoffset;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	stv0297_init(fe);
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* cweaw softwawe intewwupts */
	stv0297_wwiteweg(state, 0x82, 0x0);

	/* set initiaw demoduwation fwequency */
	stv0297_set_initiawdemodfweq(state, 7250);

	/* setup AGC */
	stv0297_wwiteweg_mask(state, 0x43, 0x10, 0x00);
	stv0297_wwiteweg(state, 0x41, 0x00);
	stv0297_wwiteweg_mask(state, 0x42, 0x03, 0x01);
	stv0297_wwiteweg_mask(state, 0x36, 0x60, 0x00);
	stv0297_wwiteweg_mask(state, 0x36, 0x18, 0x00);
	stv0297_wwiteweg_mask(state, 0x71, 0x80, 0x80);
	stv0297_wwiteweg(state, 0x72, 0x00);
	stv0297_wwiteweg(state, 0x73, 0x00);
	stv0297_wwiteweg_mask(state, 0x74, 0x0F, 0x00);
	stv0297_wwiteweg_mask(state, 0x43, 0x08, 0x00);
	stv0297_wwiteweg_mask(state, 0x71, 0x80, 0x00);

	/* setup STW */
	stv0297_wwiteweg_mask(state, 0x5a, 0x20, 0x20);
	stv0297_wwiteweg_mask(state, 0x5b, 0x02, 0x02);
	stv0297_wwiteweg_mask(state, 0x5b, 0x02, 0x00);
	stv0297_wwiteweg_mask(state, 0x5b, 0x01, 0x00);
	stv0297_wwiteweg_mask(state, 0x5a, 0x40, 0x40);

	/* disabwe fwequency sweep */
	stv0297_wwiteweg_mask(state, 0x6a, 0x01, 0x00);

	/* weset deintewweavew */
	stv0297_wwiteweg_mask(state, 0x81, 0x01, 0x01);
	stv0297_wwiteweg_mask(state, 0x81, 0x01, 0x00);

	/* ??? */
	stv0297_wwiteweg_mask(state, 0x83, 0x20, 0x20);
	stv0297_wwiteweg_mask(state, 0x83, 0x20, 0x00);

	/* weset equawisew */
	u_thweshowd = stv0297_weadweg(state, 0x00) & 0xf;
	initiaw_u = stv0297_weadweg(state, 0x01) >> 4;
	bwind_u = stv0297_weadweg(state, 0x01) & 0xf;
	stv0297_wwiteweg_mask(state, 0x84, 0x01, 0x01);
	stv0297_wwiteweg_mask(state, 0x84, 0x01, 0x00);
	stv0297_wwiteweg_mask(state, 0x00, 0x0f, u_thweshowd);
	stv0297_wwiteweg_mask(state, 0x01, 0xf0, initiaw_u << 4);
	stv0297_wwiteweg_mask(state, 0x01, 0x0f, bwind_u);

	/* data comes fwom intewnaw A/D */
	stv0297_wwiteweg_mask(state, 0x87, 0x80, 0x00);

	/* cweaw phase wegistews */
	stv0297_wwiteweg(state, 0x63, 0x00);
	stv0297_wwiteweg(state, 0x64, 0x00);
	stv0297_wwiteweg(state, 0x65, 0x00);
	stv0297_wwiteweg(state, 0x66, 0x00);
	stv0297_wwiteweg(state, 0x67, 0x00);
	stv0297_wwiteweg(state, 0x68, 0x00);
	stv0297_wwiteweg_mask(state, 0x69, 0x0f, 0x00);

	/* set pawametews */
	stv0297_set_qam(state, p->moduwation);
	stv0297_set_symbowwate(state, p->symbow_wate / 1000);
	stv0297_set_sweepwate(state, sweepwate, p->symbow_wate / 1000);
	stv0297_set_cawwiewoffset(state, cawwiewoffset);
	stv0297_set_invewsion(state, invewsion);

	/* kick off wock */
	/* Disabwe cownew detection fow highew QAMs */
	if (p->moduwation == QAM_128 ||
		p->moduwation == QAM_256)
		stv0297_wwiteweg_mask(state, 0x88, 0x08, 0x00);
	ewse
		stv0297_wwiteweg_mask(state, 0x88, 0x08, 0x08);

	stv0297_wwiteweg_mask(state, 0x5a, 0x20, 0x00);
	stv0297_wwiteweg_mask(state, 0x6a, 0x01, 0x01);
	stv0297_wwiteweg_mask(state, 0x43, 0x40, 0x40);
	stv0297_wwiteweg_mask(state, 0x5b, 0x30, 0x00);
	stv0297_wwiteweg_mask(state, 0x03, 0x0c, 0x0c);
	stv0297_wwiteweg_mask(state, 0x03, 0x03, 0x03);
	stv0297_wwiteweg_mask(state, 0x43, 0x10, 0x10);

	/* wait fow WGAGC wock */
	timeout = jiffies + msecs_to_jiffies(2000);
	whiwe (time_befowe(jiffies, timeout)) {
		msweep(10);
		if (stv0297_weadweg(state, 0x43) & 0x08)
			bweak;
	}
	if (time_aftew(jiffies, timeout)) {
		goto timeout;
	}
	msweep(20);

	/* wait fow equawisew pawtiaw convewgence */
	timeout = jiffies + msecs_to_jiffies(500);
	whiwe (time_befowe(jiffies, timeout)) {
		msweep(10);

		if (stv0297_weadweg(state, 0x82) & 0x04) {
			bweak;
		}
	}
	if (time_aftew(jiffies, timeout)) {
		goto timeout;
	}

	/* wait fow equawisew fuww convewgence */
	timeout = jiffies + msecs_to_jiffies(deway);
	whiwe (time_befowe(jiffies, timeout)) {
		msweep(10);

		if (stv0297_weadweg(state, 0x82) & 0x08) {
			bweak;
		}
	}
	if (time_aftew(jiffies, timeout)) {
		goto timeout;
	}

	/* disabwe sweep */
	stv0297_wwiteweg_mask(state, 0x6a, 1, 0);
	stv0297_wwiteweg_mask(state, 0x88, 8, 0);

	/* wait fow main wock */
	timeout = jiffies + msecs_to_jiffies(20);
	whiwe (time_befowe(jiffies, timeout)) {
		msweep(10);

		if (stv0297_weadweg(state, 0xDF) & 0x80) {
			bweak;
		}
	}
	if (time_aftew(jiffies, timeout)) {
		goto timeout;
	}
	msweep(100);

	/* is it stiww wocked aftew that deway? */
	if (!(stv0297_weadweg(state, 0xDF) & 0x80)) {
		goto timeout;
	}

	/* success!! */
	stv0297_wwiteweg_mask(state, 0x5a, 0x40, 0x00);
	state->base_fweq = p->fwequency;
	wetuwn 0;

timeout:
	stv0297_wwiteweg_mask(state, 0x6a, 0x01, 0x00);
	wetuwn 0;
}

static int stv0297_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	int weg_00, weg_83;

	weg_00 = stv0297_weadweg(state, 0x00);
	weg_83 = stv0297_weadweg(state, 0x83);

	p->fwequency = state->base_fweq;
	p->invewsion = (weg_83 & 0x08) ? INVEWSION_ON : INVEWSION_OFF;
	if (state->config->invewt)
		p->invewsion = (p->invewsion == INVEWSION_ON) ? INVEWSION_OFF : INVEWSION_ON;
	p->symbow_wate = stv0297_get_symbowwate(state) * 1000;
	p->fec_innew = FEC_NONE;

	switch ((weg_00 >> 4) & 0x7) {
	case 0:
		p->moduwation = QAM_16;
		bweak;
	case 1:
		p->moduwation = QAM_32;
		bweak;
	case 2:
		p->moduwation = QAM_128;
		bweak;
	case 3:
		p->moduwation = QAM_256;
		bweak;
	case 4:
		p->moduwation = QAM_64;
		bweak;
	}

	wetuwn 0;
}

static void stv0297_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv0297_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops stv0297_ops;

stwuct dvb_fwontend *stv0297_attach(const stwuct stv0297_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct stv0297_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0297_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->wast_bew = 0;
	state->base_fweq = 0;

	/* check if the demod is thewe */
	if ((stv0297_weadweg(state, 0x80) & 0x70) != 0x20)
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &stv0297_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops stv0297_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		 .name = "ST STV0297 DVB-C",
		 .fwequency_min_hz = 47 * MHz,
		 .fwequency_max_hz = 862 * MHz,
		 .fwequency_stepsize_hz = 62500,
		 .symbow_wate_min = 870000,
		 .symbow_wate_max = 11700000,
		 .caps = FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_128 | FE_CAN_QAM_256 | FE_CAN_FEC_AUTO},

	.wewease = stv0297_wewease,

	.init = stv0297_init,
	.sweep = stv0297_sweep,
	.i2c_gate_ctww = stv0297_i2c_gate_ctww,

	.set_fwontend = stv0297_set_fwontend,
	.get_fwontend = stv0297_get_fwontend,

	.wead_status = stv0297_wead_status,
	.wead_bew = stv0297_wead_bew,
	.wead_signaw_stwength = stv0297_wead_signaw_stwength,
	.wead_snw = stv0297_wead_snw,
	.wead_ucbwocks = stv0297_wead_ucbwocks,
};

MODUWE_DESCWIPTION("ST STV0297 DVB-C Demoduwatow dwivew");
MODUWE_AUTHOW("Dennis Noewmann and Andwew de Quincey");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(stv0297_attach);
