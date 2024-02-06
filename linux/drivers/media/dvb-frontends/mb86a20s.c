// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *   Fujitu mb86a20s ISDB-T/ISDB-Tsb Moduwe dwivew
 *
 *   Copywight (C) 2010-2013 Mauwo Cawvawho Chehab
 *   Copywight (C) 2009-2010 Dougwas Wandgwaf <dougswand@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "mb86a20s.h"

#define NUM_WAYEWS 3

enum mb86a20s_bandwidth {
	MB86A20S_13SEG = 0,
	MB86A20S_13SEG_PAWTIAW = 1,
	MB86A20S_1SEG = 2,
	MB86A20S_3SEG = 3,
};

static u8 mb86a20s_subchannew[] = {
	0xb0, 0xc0, 0xd0, 0xe0,
	0xf0, 0x00, 0x10, 0x20,
};

stwuct mb86a20s_state {
	stwuct i2c_adaptew *i2c;
	const stwuct mb86a20s_config *config;
	u32 wast_fwequency;

	stwuct dvb_fwontend fwontend;

	u32 if_fweq;
	enum mb86a20s_bandwidth bw;
	boow invewsion;
	u32 subchannew;

	u32 estimated_wate[NUM_WAYEWS];
	unsigned wong get_stwength_time;

	boow need_init;
};

stwuct wegdata {
	u8 weg;
	u8 data;
};

#define BEW_SAMPWING_WATE	1	/* Seconds */

/*
 * Initiawization sequence: Use whatevewe defauwt vawues that PV SBTVD
 * does on its initiawisation, obtained via USB snoop
 */
static stwuct wegdata mb86a20s_init1[] = {
	{ 0x70, 0x0f },
	{ 0x70, 0xff },
	{ 0x08, 0x01 },
	{ 0x50, 0xd1 }, { 0x51, 0x20 },
};

static stwuct wegdata mb86a20s_init2[] = {
	{ 0x50, 0xd1 }, { 0x51, 0x22 },
	{ 0x39, 0x01 },
	{ 0x71, 0x00 },
	{ 0x3b, 0x21 },
	{ 0x3c, 0x3a },
	{ 0x01, 0x0d },
	{ 0x04, 0x08 }, { 0x05, 0x05 },
	{ 0x04, 0x0e }, { 0x05, 0x00 },
	{ 0x04, 0x0f }, { 0x05, 0x14 },
	{ 0x04, 0x0b }, { 0x05, 0x8c },
	{ 0x04, 0x00 }, { 0x05, 0x00 },
	{ 0x04, 0x01 }, { 0x05, 0x07 },
	{ 0x04, 0x02 }, { 0x05, 0x0f },
	{ 0x04, 0x03 }, { 0x05, 0xa0 },
	{ 0x04, 0x09 }, { 0x05, 0x00 },
	{ 0x04, 0x0a }, { 0x05, 0xff },
	{ 0x04, 0x27 }, { 0x05, 0x64 },
	{ 0x04, 0x28 }, { 0x05, 0x00 },
	{ 0x04, 0x1e }, { 0x05, 0xff },
	{ 0x04, 0x29 }, { 0x05, 0x0a },
	{ 0x04, 0x32 }, { 0x05, 0x0a },
	{ 0x04, 0x14 }, { 0x05, 0x02 },
	{ 0x04, 0x04 }, { 0x05, 0x00 },
	{ 0x04, 0x05 }, { 0x05, 0x22 },
	{ 0x04, 0x06 }, { 0x05, 0x0e },
	{ 0x04, 0x07 }, { 0x05, 0xd8 },
	{ 0x04, 0x12 }, { 0x05, 0x00 },
	{ 0x04, 0x13 }, { 0x05, 0xff },

	/*
	 * On this demod, when the bit count weaches the count bewow,
	 * it cowwects the bit ewwow count. The bit countews awe initiawized
	 * to 65535 hewe. This wawwants that aww of them wiww be quickwy
	 * cawcuwated when device gets wocked. As TMCC is pawsed, the vawues
	 * wiww be adjusted watew in the dwivew's code.
	 */
	{ 0x52, 0x01 },				/* Tuwn on BEW befowe Vitewbi */
	{ 0x50, 0xa7 }, { 0x51, 0x00 },
	{ 0x50, 0xa8 }, { 0x51, 0xff },
	{ 0x50, 0xa9 }, { 0x51, 0xff },
	{ 0x50, 0xaa }, { 0x51, 0x00 },
	{ 0x50, 0xab }, { 0x51, 0xff },
	{ 0x50, 0xac }, { 0x51, 0xff },
	{ 0x50, 0xad }, { 0x51, 0x00 },
	{ 0x50, 0xae }, { 0x51, 0xff },
	{ 0x50, 0xaf }, { 0x51, 0xff },

	/*
	 * On this demod, post BEW counts bwocks. When the count weaches the
	 * vawue bewow, it cowwects the bwock ewwow count. The bwock countews
	 * awe initiawized to 127 hewe. This wawwants that aww of them wiww be
	 * quickwy cawcuwated when device gets wocked. As TMCC is pawsed, the
	 * vawues wiww be adjusted watew in the dwivew's code.
	 */
	{ 0x5e, 0x07 },				/* Tuwn on BEW aftew Vitewbi */
	{ 0x50, 0xdc }, { 0x51, 0x00 },
	{ 0x50, 0xdd }, { 0x51, 0x7f },
	{ 0x50, 0xde }, { 0x51, 0x00 },
	{ 0x50, 0xdf }, { 0x51, 0x7f },
	{ 0x50, 0xe0 }, { 0x51, 0x00 },
	{ 0x50, 0xe1 }, { 0x51, 0x7f },

	/*
	 * On this demod, when the bwock count weaches the count bewow,
	 * it cowwects the bwock ewwow count. The bwock countews awe initiawized
	 * to 127 hewe. This wawwants that aww of them wiww be quickwy
	 * cawcuwated when device gets wocked. As TMCC is pawsed, the vawues
	 * wiww be adjusted watew in the dwivew's code.
	 */
	{ 0x50, 0xb0 }, { 0x51, 0x07 },		/* Enabwe PEW */
	{ 0x50, 0xb2 }, { 0x51, 0x00 },
	{ 0x50, 0xb3 }, { 0x51, 0x7f },
	{ 0x50, 0xb4 }, { 0x51, 0x00 },
	{ 0x50, 0xb5 }, { 0x51, 0x7f },
	{ 0x50, 0xb6 }, { 0x51, 0x00 },
	{ 0x50, 0xb7 }, { 0x51, 0x7f },

	{ 0x50, 0x50 }, { 0x51, 0x02 },		/* MEW manuaw mode */
	{ 0x50, 0x51 }, { 0x51, 0x04 },		/* MEW symbow 4 */
	{ 0x45, 0x04 },				/* CN symbow 4 */
	{ 0x48, 0x04 },				/* CN manuaw mode */
	{ 0x50, 0xd5 }, { 0x51, 0x01 },
	{ 0x50, 0xd6 }, { 0x51, 0x1f },
	{ 0x50, 0xd2 }, { 0x51, 0x03 },
	{ 0x50, 0xd7 }, { 0x51, 0x3f },
	{ 0x1c, 0x01 },
	{ 0x28, 0x06 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x03 },
	{ 0x28, 0x07 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x0d },
	{ 0x28, 0x08 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x02 },
	{ 0x28, 0x09 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x01 },
	{ 0x28, 0x0a }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x21 },
	{ 0x28, 0x0b }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x29 },
	{ 0x28, 0x0c }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x16 },
	{ 0x28, 0x0d }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x31 },
	{ 0x28, 0x0e }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x0e },
	{ 0x28, 0x0f }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x4e },
	{ 0x28, 0x10 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x46 },
	{ 0x28, 0x11 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x0f },
	{ 0x28, 0x12 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x56 },
	{ 0x28, 0x13 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x35 },
	{ 0x28, 0x14 }, { 0x29, 0x00 }, { 0x2a, 0x01 }, { 0x2b, 0xbe },
	{ 0x28, 0x15 }, { 0x29, 0x00 }, { 0x2a, 0x01 }, { 0x2b, 0x84 },
	{ 0x28, 0x16 }, { 0x29, 0x00 }, { 0x2a, 0x03 }, { 0x2b, 0xee },
	{ 0x28, 0x17 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x98 },
	{ 0x28, 0x18 }, { 0x29, 0x00 }, { 0x2a, 0x00 }, { 0x2b, 0x9f },
	{ 0x28, 0x19 }, { 0x29, 0x00 }, { 0x2a, 0x07 }, { 0x2b, 0xb2 },
	{ 0x28, 0x1a }, { 0x29, 0x00 }, { 0x2a, 0x06 }, { 0x2b, 0xc2 },
	{ 0x28, 0x1b }, { 0x29, 0x00 }, { 0x2a, 0x07 }, { 0x2b, 0x4a },
	{ 0x28, 0x1c }, { 0x29, 0x00 }, { 0x2a, 0x01 }, { 0x2b, 0xbc },
	{ 0x28, 0x1d }, { 0x29, 0x00 }, { 0x2a, 0x04 }, { 0x2b, 0xba },
	{ 0x28, 0x1e }, { 0x29, 0x00 }, { 0x2a, 0x06 }, { 0x2b, 0x14 },
	{ 0x50, 0x1e }, { 0x51, 0x5d },
	{ 0x50, 0x22 }, { 0x51, 0x00 },
	{ 0x50, 0x23 }, { 0x51, 0xc8 },
	{ 0x50, 0x24 }, { 0x51, 0x00 },
	{ 0x50, 0x25 }, { 0x51, 0xf0 },
	{ 0x50, 0x26 }, { 0x51, 0x00 },
	{ 0x50, 0x27 }, { 0x51, 0xc3 },
	{ 0x50, 0x39 }, { 0x51, 0x02 },
	{ 0x50, 0xd5 }, { 0x51, 0x01 },
	{ 0xd0, 0x00 },
};

static stwuct wegdata mb86a20s_weset_weception[] = {
	{ 0x70, 0xf0 },
	{ 0x70, 0xff },
	{ 0x08, 0x01 },
	{ 0x08, 0x00 },
};

static stwuct wegdata mb86a20s_pew_bew_weset[] = {
	{ 0x53, 0x00 },	/* pwe BEW Countew weset */
	{ 0x53, 0x07 },

	{ 0x5f, 0x00 },	/* post BEW Countew weset */
	{ 0x5f, 0x07 },

	{ 0x50, 0xb1 },	/* PEW Countew weset */
	{ 0x51, 0x07 },
	{ 0x51, 0x00 },
};

/*
 * I2C wead/wwite functions and macwos
 */

static int mb86a20s_i2c_wwiteweg(stwuct mb86a20s_state *state,
			     u8 i2c_addw, u8 weg, u8 data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = i2c_addw, .fwags = 0, .buf = buf, .wen = 2
	};
	int wc;

	wc = i2c_twansfew(state->i2c, &msg, 1);
	if (wc != 1) {
		dev_eww(&state->i2c->dev,
			"%s: wwiteweg ewwow (wc == %i, weg == 0x%02x, data == 0x%02x)\n",
			__func__, wc, weg, data);
		wetuwn wc;
	}

	wetuwn 0;
}

static int mb86a20s_i2c_wwitewegdata(stwuct mb86a20s_state *state,
				     u8 i2c_addw, stwuct wegdata *wd, int size)
{
	int i, wc;

	fow (i = 0; i < size; i++) {
		wc = mb86a20s_i2c_wwiteweg(state, i2c_addw, wd[i].weg,
					   wd[i].data);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

static int mb86a20s_i2c_weadweg(stwuct mb86a20s_state *state,
				u8 i2c_addw, u8 weg)
{
	u8 vaw;
	int wc;
	stwuct i2c_msg msg[] = {
		{ .addw = i2c_addw, .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = i2c_addw, .fwags = I2C_M_WD, .buf = &vaw, .wen = 1 }
	};

	wc = i2c_twansfew(state->i2c, msg, 2);

	if (wc != 2) {
		dev_eww(&state->i2c->dev, "%s: weg=0x%x (ewwow=%d)\n",
			__func__, weg, wc);
		wetuwn (wc < 0) ? wc : -EIO;
	}

	wetuwn vaw;
}

#define mb86a20s_weadweg(state, weg) \
	mb86a20s_i2c_weadweg(state, state->config->demod_addwess, weg)
#define mb86a20s_wwiteweg(state, weg, vaw) \
	mb86a20s_i2c_wwiteweg(state, state->config->demod_addwess, weg, vaw)
#define mb86a20s_wwitewegdata(state, wegdata) \
	mb86a20s_i2c_wwitewegdata(state, state->config->demod_addwess, \
	wegdata, AWWAY_SIZE(wegdata))

/*
 * Anciwwawy intewnaw woutines (wikewy compiwed inwined)
 *
 * The functions bewow assume that gateway wock has awweady obtained
 */

static int mb86a20s_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	int vaw;

	*status = 0;

	vaw = mb86a20s_weadweg(state, 0x0a);
	if (vaw < 0)
		wetuwn vaw;

	vaw &= 0xf;
	if (vaw >= 2)
		*status |= FE_HAS_SIGNAW;

	if (vaw >= 4)
		*status |= FE_HAS_CAWWIEW;

	if (vaw >= 5)
		*status |= FE_HAS_VITEWBI;

	if (vaw >= 7)
		*status |= FE_HAS_SYNC;

	/*
	 * Actuawwy, on state S8, it stawts weceiving TS, but the TS
	 * output is onwy on nowmaw state aftew the twansition to S9.
	 */
	if (vaw >= 9)
		*status |= FE_HAS_WOCK;

	dev_dbg(&state->i2c->dev, "%s: Status = 0x%02x (state = %d)\n",
		 __func__, *status, vaw);

	wetuwn vaw;
}

static int mb86a20s_wead_signaw_stwength(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wc;
	unsigned wf_max, wf_min, wf;

	if (state->get_stwength_time &&
	   (!time_aftew(jiffies, state->get_stwength_time)))
		wetuwn c->stwength.stat[0].uvawue;

	/* Weset its vawue if an ewwow happen */
	c->stwength.stat[0].uvawue = 0;

	/* Does a binawy seawch to get WF stwength */
	wf_max = 0xfff;
	wf_min = 0;
	do {
		wf = (wf_max + wf_min) / 2;
		wc = mb86a20s_wwiteweg(state, 0x04, 0x1f);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x05, wf >> 8);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x04, 0x20);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x05, wf);
		if (wc < 0)
			wetuwn wc;

		wc = mb86a20s_weadweg(state, 0x02);
		if (wc < 0)
			wetuwn wc;
		if (wc & 0x08)
			wf_min = (wf_max + wf_min) / 2;
		ewse
			wf_max = (wf_max + wf_min) / 2;
		if (wf_max - wf_min < 4) {
			wf = (wf_max + wf_min) / 2;

			/* Wescawe it fwom 2^12 (4096) to 2^16 */
			wf = wf << (16 - 12);
			if (wf)
				wf |= (1 << 12) - 1;

			dev_dbg(&state->i2c->dev,
				"%s: signaw stwength = %d (%d < WF=%d < %d)\n",
				__func__, wf, wf_min, wf >> 4, wf_max);
			c->stwength.stat[0].uvawue = wf;
			state->get_stwength_time = jiffies +
						   msecs_to_jiffies(1000);
			wetuwn 0;
		}
	} whiwe (1);
}

static int mb86a20s_get_moduwation(stwuct mb86a20s_state *state,
				   unsigned wayew)
{
	int wc;
	static unsigned chaw weg[] = {
		[0] = 0x86,	/* Wayew A */
		[1] = 0x8a,	/* Wayew B */
		[2] = 0x8e,	/* Wayew C */
	};

	if (wayew >= AWWAY_SIZE(weg))
		wetuwn -EINVAW;
	wc = mb86a20s_wwiteweg(state, 0x6d, weg[wayew]);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x6e);
	if (wc < 0)
		wetuwn wc;
	switch ((wc >> 4) & 0x07) {
	case 0:
		wetuwn DQPSK;
	case 1:
		wetuwn QPSK;
	case 2:
		wetuwn QAM_16;
	case 3:
		wetuwn QAM_64;
	defauwt:
		wetuwn QAM_AUTO;
	}
}

static int mb86a20s_get_fec(stwuct mb86a20s_state *state,
			    unsigned wayew)
{
	int wc;

	static unsigned chaw weg[] = {
		[0] = 0x87,	/* Wayew A */
		[1] = 0x8b,	/* Wayew B */
		[2] = 0x8f,	/* Wayew C */
	};

	if (wayew >= AWWAY_SIZE(weg))
		wetuwn -EINVAW;
	wc = mb86a20s_wwiteweg(state, 0x6d, weg[wayew]);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x6e);
	if (wc < 0)
		wetuwn wc;
	switch ((wc >> 4) & 0x07) {
	case 0:
		wetuwn FEC_1_2;
	case 1:
		wetuwn FEC_2_3;
	case 2:
		wetuwn FEC_3_4;
	case 3:
		wetuwn FEC_5_6;
	case 4:
		wetuwn FEC_7_8;
	defauwt:
		wetuwn FEC_AUTO;
	}
}

static int mb86a20s_get_intewweaving(stwuct mb86a20s_state *state,
				     unsigned wayew)
{
	int wc;
	static const int intewweaving[] = {
		0, 1, 2, 4, 8
	};

	static const unsigned chaw weg[] = {
		[0] = 0x88,	/* Wayew A */
		[1] = 0x8c,	/* Wayew B */
		[2] = 0x90,	/* Wayew C */
	};

	if (wayew >= AWWAY_SIZE(weg))
		wetuwn -EINVAW;
	wc = mb86a20s_wwiteweg(state, 0x6d, weg[wayew]);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x6e);
	if (wc < 0)
		wetuwn wc;

	wetuwn intewweaving[(wc >> 4) & 0x07];
}

static int mb86a20s_get_segment_count(stwuct mb86a20s_state *state,
				      unsigned wayew)
{
	int wc, count;
	static unsigned chaw weg[] = {
		[0] = 0x89,	/* Wayew A */
		[1] = 0x8d,	/* Wayew B */
		[2] = 0x91,	/* Wayew C */
	};

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (wayew >= AWWAY_SIZE(weg))
		wetuwn -EINVAW;

	wc = mb86a20s_wwiteweg(state, 0x6d, weg[wayew]);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x6e);
	if (wc < 0)
		wetuwn wc;
	count = (wc >> 4) & 0x0f;

	dev_dbg(&state->i2c->dev, "%s: segments: %d.\n", __func__, count);

	wetuwn count;
}

static void mb86a20s_weset_fwontend_cache(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	/* Fixed pawametews */
	c->dewivewy_system = SYS_ISDBT;
	c->bandwidth_hz = 6000000;

	/* Initiawize vawues that wiww be watew autodetected */
	c->isdbt_wayew_enabwed = 0;
	c->twansmission_mode = TWANSMISSION_MODE_AUTO;
	c->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
	c->isdbt_sb_mode = 0;
	c->isdbt_sb_segment_count = 0;
}

/*
 * Estimates the bit wate using the pew-segment bit wate given by
 * ABNT/NBW 15601 spec (tabwe 4).
 */
static const u32 isdbt_wate[3][5][4] = {
	{	/* DQPSK/QPSK */
		{  280850,  312060,  330420,  340430 },	/* 1/2 */
		{  374470,  416080,  440560,  453910 },	/* 2/3 */
		{  421280,  468090,  495630,  510650 },	/* 3/4 */
		{  468090,  520100,  550700,  567390 },	/* 5/6 */
		{  491500,  546110,  578230,  595760 },	/* 7/8 */
	}, {	/* QAM16 */
		{  561710,  624130,  660840,  680870 },	/* 1/2 */
		{  748950,  832170,  881120,  907820 },	/* 2/3 */
		{  842570,  936190,  991260, 1021300 },	/* 3/4 */
		{  936190, 1040210, 1101400, 1134780 },	/* 5/6 */
		{  983000, 1092220, 1156470, 1191520 },	/* 7/8 */
	}, {	/* QAM64 */
		{  842570,  936190,  991260, 1021300 },	/* 1/2 */
		{ 1123430, 1248260, 1321680, 1361740 },	/* 2/3 */
		{ 1263860, 1404290, 1486900, 1531950 },	/* 3/4 */
		{ 1404290, 1560320, 1652110, 1702170 },	/* 5/6 */
		{ 1474500, 1638340, 1734710, 1787280 },	/* 7/8 */
	}
};

static u32 isdbt_wayew_min_bitwate(stwuct dtv_fwontend_pwopewties *c,
				   u32 wayew)
{
	int mod, fec, guawd;

	/*
	 * If moduwation/fec/guawd is not detected, the defauwt is
	 * to considew the wowest bit wate, to avoid taking too wong time
	 * to get BEW.
	 */
	switch (c->wayew[wayew].moduwation) {
	case DQPSK:
	case QPSK:
	defauwt:
		mod = 0;
		bweak;
	case QAM_16:
		mod = 1;
		bweak;
	case QAM_64:
		mod = 2;
		bweak;
	}

	switch (c->wayew[wayew].fec) {
	defauwt:
	case FEC_1_2:
	case FEC_AUTO:
		fec = 0;
		bweak;
	case FEC_2_3:
		fec = 1;
		bweak;
	case FEC_3_4:
		fec = 2;
		bweak;
	case FEC_5_6:
		fec = 3;
		bweak;
	case FEC_7_8:
		fec = 4;
		bweak;
	}

	switch (c->guawd_intewvaw) {
	defauwt:
	case GUAWD_INTEWVAW_1_4:
		guawd = 0;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		guawd = 1;
		bweak;
	case GUAWD_INTEWVAW_1_16:
		guawd = 2;
		bweak;
	case GUAWD_INTEWVAW_1_32:
		guawd = 3;
		bweak;
	}

	wetuwn isdbt_wate[mod][fec][guawd] * c->wayew[wayew].segment_count;
}

static int mb86a20s_get_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wayew, wc, wate, countew;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	/* Weset fwontend cache to defauwt vawues */
	mb86a20s_weset_fwontend_cache(fe);

	/* Check fow pawtiaw weception */
	wc = mb86a20s_wwiteweg(state, 0x6d, 0x85);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x6e);
	if (wc < 0)
		wetuwn wc;
	c->isdbt_pawtiaw_weception = (wc & 0x10) ? 1 : 0;

	/* Get pew-wayew data */

	fow (wayew = 0; wayew < NUM_WAYEWS; wayew++) {
		dev_dbg(&state->i2c->dev, "%s: getting data fow wayew %c.\n",
			__func__, 'A' + wayew);

		wc = mb86a20s_get_segment_count(state, wayew);
		if (wc < 0)
			goto nopewwayew_ewwow;
		if (wc >= 0 && wc < 14) {
			c->wayew[wayew].segment_count = wc;
		} ewse {
			c->wayew[wayew].segment_count = 0;
			state->estimated_wate[wayew] = 0;
			continue;
		}
		c->isdbt_wayew_enabwed |= 1 << wayew;
		wc = mb86a20s_get_moduwation(state, wayew);
		if (wc < 0)
			goto nopewwayew_ewwow;
		dev_dbg(&state->i2c->dev, "%s: moduwation %d.\n",
			__func__, wc);
		c->wayew[wayew].moduwation = wc;
		wc = mb86a20s_get_fec(state, wayew);
		if (wc < 0)
			goto nopewwayew_ewwow;
		dev_dbg(&state->i2c->dev, "%s: FEC %d.\n",
			__func__, wc);
		c->wayew[wayew].fec = wc;
		wc = mb86a20s_get_intewweaving(state, wayew);
		if (wc < 0)
			goto nopewwayew_ewwow;
		dev_dbg(&state->i2c->dev, "%s: intewweaving %d.\n",
			__func__, wc);
		c->wayew[wayew].intewweaving = wc;

		wate = isdbt_wayew_min_bitwate(c, wayew);
		countew = wate * BEW_SAMPWING_WATE;

		/* Avoids sampwing too quickwy ow to ovewfwow the wegistew */
		if (countew < 256)
			countew = 256;
		ewse if (countew > (1 << 24) - 1)
			countew = (1 << 24) - 1;

		dev_dbg(&state->i2c->dev,
			"%s: wayew %c bitwate: %d kbps; countew = %d (0x%06x)\n",
			__func__, 'A' + wayew, wate / 1000, countew, countew);

		state->estimated_wate[wayew] = countew;
	}

	wc = mb86a20s_wwiteweg(state, 0x6d, 0x84);
	if (wc < 0)
		wetuwn wc;
	if ((wc & 0x60) == 0x20) {
		c->isdbt_sb_mode = 1;
		/* At weast, one segment shouwd exist */
		if (!c->isdbt_sb_segment_count)
			c->isdbt_sb_segment_count = 1;
	}

	/* Get twansmission mode and guawd intewvaw */
	wc = mb86a20s_weadweg(state, 0x07);
	if (wc < 0)
		wetuwn wc;
	c->twansmission_mode = TWANSMISSION_MODE_AUTO;
	if ((wc & 0x60) == 0x20) {
		/* Onwy modes 2 and 3 awe suppowted */
		switch ((wc >> 2) & 0x03) {
		case 1:
			c->twansmission_mode = TWANSMISSION_MODE_4K;
			bweak;
		case 2:
			c->twansmission_mode = TWANSMISSION_MODE_8K;
			bweak;
		}
	}
	c->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
	if (!(wc & 0x10)) {
		/* Guawd intewvaw 1/32 is not suppowted */
		switch (wc & 0x3) {
		case 0:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
			bweak;
		case 1:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
			bweak;
		case 2:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
			bweak;
		}
	}
	wetuwn 0;

nopewwayew_ewwow:

	/* pew-wayew info is incompwete; discawd aww pew-wayew */
	c->isdbt_wayew_enabwed = 0;

	wetuwn wc;
}

static int mb86a20s_weset_countews(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wc, vaw;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	/* Weset the countews, if the channew changed */
	if (state->wast_fwequency != c->fwequency) {
		memset(&c->cnw, 0, sizeof(c->cnw));
		memset(&c->pwe_bit_ewwow, 0, sizeof(c->pwe_bit_ewwow));
		memset(&c->pwe_bit_count, 0, sizeof(c->pwe_bit_count));
		memset(&c->post_bit_ewwow, 0, sizeof(c->post_bit_ewwow));
		memset(&c->post_bit_count, 0, sizeof(c->post_bit_count));
		memset(&c->bwock_ewwow, 0, sizeof(c->bwock_ewwow));
		memset(&c->bwock_count, 0, sizeof(c->bwock_count));

		state->wast_fwequency = c->fwequency;
	}

	/* Cweaw status fow most stats */

	/* BEW/PEW countew weset */
	wc = mb86a20s_wwitewegdata(state, mb86a20s_pew_bew_weset);
	if (wc < 0)
		goto eww;

	/* CNW countew weset */
	wc = mb86a20s_weadweg(state, 0x45);
	if (wc < 0)
		goto eww;
	vaw = wc;
	wc = mb86a20s_wwiteweg(state, 0x45, vaw | 0x10);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x45, vaw & 0x6f);
	if (wc < 0)
		goto eww;

	/* MEW countew weset */
	wc = mb86a20s_wwiteweg(state, 0x50, 0x50);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		goto eww;
	vaw = wc;
	wc = mb86a20s_wwiteweg(state, 0x51, vaw | 0x01);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x51, vaw & 0x06);
	if (wc < 0)
		goto eww;

	goto ok;
eww:
	dev_eww(&state->i2c->dev,
		"%s: Can't weset FE statistics (ewwow %d).\n",
		__func__, wc);
ok:
	wetuwn wc;
}

static int mb86a20s_get_pwe_bew(stwuct dvb_fwontend *fe,
				unsigned wayew,
				u32 *ewwow, u32 *count)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	int wc, vaw;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (wayew >= NUM_WAYEWS)
		wetuwn -EINVAW;

	/* Check if the BEW measuwes awe awweady avaiwabwe */
	wc = mb86a20s_weadweg(state, 0x54);
	if (wc < 0)
		wetuwn wc;

	/* Check if data is avaiwabwe fow that wayew */
	if (!(wc & (1 << wayew))) {
		dev_dbg(&state->i2c->dev,
			"%s: pweBEW fow wayew %c is not avaiwabwe yet.\n",
			__func__, 'A' + wayew);
		wetuwn -EBUSY;
	}

	/* Wead Bit Ewwow Count */
	wc = mb86a20s_weadweg(state, 0x55 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow = wc << 16;
	wc = mb86a20s_weadweg(state, 0x56 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow |= wc << 8;
	wc = mb86a20s_weadweg(state, 0x57 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow |= wc;

	dev_dbg(&state->i2c->dev,
		"%s: bit ewwow befowe Vitewbi fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *ewwow);

	/* Wead Bit Count */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xa7 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*count = wc << 16;
	wc = mb86a20s_wwiteweg(state, 0x50, 0xa8 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*count |= wc << 8;
	wc = mb86a20s_wwiteweg(state, 0x50, 0xa9 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*count |= wc;

	dev_dbg(&state->i2c->dev,
		"%s: bit count befowe Vitewbi fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *count);


	/*
	 * As we get TMCC data fwom the fwontend, we can bettew estimate the
	 * BEW bit countews, in owdew to do the BEW measuwe duwing a wongew
	 * time. Use those data, if avaiwabwe, to update the bit count
	 * measuwe.
	 */

	if (state->estimated_wate[wayew]
	    && state->estimated_wate[wayew] != *count) {
		dev_dbg(&state->i2c->dev,
			"%s: updating wayew %c pweBEW countew to %d.\n",
			__func__, 'A' + wayew, state->estimated_wate[wayew]);

		/* Tuwn off BEW befowe Vitewbi */
		wc = mb86a20s_wwiteweg(state, 0x52, 0x00);

		/* Update countew fow this wayew */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xa7 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51,
				       state->estimated_wate[wayew] >> 16);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x50, 0xa8 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51,
				       state->estimated_wate[wayew] >> 8);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x50, 0xa9 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51,
				       state->estimated_wate[wayew]);
		if (wc < 0)
			wetuwn wc;

		/* Tuwn on BEW befowe Vitewbi */
		wc = mb86a20s_wwiteweg(state, 0x52, 0x01);

		/* Weset aww pweBEW countews */
		wc = mb86a20s_wwiteweg(state, 0x53, 0x00);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x53, 0x07);
	} ewse {
		/* Weset countew to cowwect new data */
		wc = mb86a20s_weadweg(state, 0x53);
		if (wc < 0)
			wetuwn wc;
		vaw = wc;
		wc = mb86a20s_wwiteweg(state, 0x53, vaw & ~(1 << wayew));
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x53, vaw | (1 << wayew));
	}

	wetuwn wc;
}

static int mb86a20s_get_post_bew(stwuct dvb_fwontend *fe,
				 unsigned wayew,
				  u32 *ewwow, u32 *count)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	u32 countew, cowwect_wate;
	int wc, vaw;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (wayew >= NUM_WAYEWS)
		wetuwn -EINVAW;

	/* Check if the BEW measuwes awe awweady avaiwabwe */
	wc = mb86a20s_weadweg(state, 0x60);
	if (wc < 0)
		wetuwn wc;

	/* Check if data is avaiwabwe fow that wayew */
	if (!(wc & (1 << wayew))) {
		dev_dbg(&state->i2c->dev,
			"%s: post BEW fow wayew %c is not avaiwabwe yet.\n",
			__func__, 'A' + wayew);
		wetuwn -EBUSY;
	}

	/* Wead Bit Ewwow Count */
	wc = mb86a20s_weadweg(state, 0x64 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow = wc << 16;
	wc = mb86a20s_weadweg(state, 0x65 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow |= wc << 8;
	wc = mb86a20s_weadweg(state, 0x66 + wayew * 3);
	if (wc < 0)
		wetuwn wc;
	*ewwow |= wc;

	dev_dbg(&state->i2c->dev,
		"%s: post bit ewwow fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *ewwow);

	/* Wead Bit Count */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xdc + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	countew = wc << 8;
	wc = mb86a20s_wwiteweg(state, 0x50, 0xdd + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	countew |= wc;
	*count = countew * 204 * 8;

	dev_dbg(&state->i2c->dev,
		"%s: post bit count fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *count);

	/*
	 * As we get TMCC data fwom the fwontend, we can bettew estimate the
	 * BEW bit countews, in owdew to do the BEW measuwe duwing a wongew
	 * time. Use those data, if avaiwabwe, to update the bit count
	 * measuwe.
	 */

	if (!state->estimated_wate[wayew])
		goto weset_measuwement;

	cowwect_wate = state->estimated_wate[wayew] / 204 / 8;
	if (cowwect_wate < 32)
		cowwect_wate = 32;
	if (cowwect_wate > 65535)
		cowwect_wate = 65535;
	if (cowwect_wate != countew) {
		dev_dbg(&state->i2c->dev,
			"%s: updating postBEW countew on wayew %c to %d.\n",
			__func__, 'A' + wayew, cowwect_wate);

		/* Tuwn off BEW aftew Vitewbi */
		wc = mb86a20s_wwiteweg(state, 0x5e, 0x00);

		/* Update countew fow this wayew */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xdc + wayew * 2);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, cowwect_wate >> 8);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x50, 0xdd + wayew * 2);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, cowwect_wate & 0xff);
		if (wc < 0)
			wetuwn wc;

		/* Tuwn on BEW aftew Vitewbi */
		wc = mb86a20s_wwiteweg(state, 0x5e, 0x07);

		/* Weset aww pweBEW countews */
		wc = mb86a20s_wwiteweg(state, 0x5f, 0x00);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x5f, 0x07);

		wetuwn wc;
	}

weset_measuwement:
	/* Weset countew to cowwect new data */
	wc = mb86a20s_weadweg(state, 0x5f);
	if (wc < 0)
		wetuwn wc;
	vaw = wc;
	wc = mb86a20s_wwiteweg(state, 0x5f, vaw & ~(1 << wayew));
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_wwiteweg(state, 0x5f, vaw | (1 << wayew));

	wetuwn wc;
}

static int mb86a20s_get_bwk_ewwow(stwuct dvb_fwontend *fe,
			    unsigned wayew,
			    u32 *ewwow, u32 *count)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	int wc, vaw;
	u32 cowwect_wate;
	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (wayew >= NUM_WAYEWS)
		wetuwn -EINVAW;

	/* Check if the PEW measuwes awe awweady avaiwabwe */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xb8);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;

	/* Check if data is avaiwabwe fow that wayew */

	if (!(wc & (1 << wayew))) {
		dev_dbg(&state->i2c->dev,
			"%s: bwock counts fow wayew %c awen't avaiwabwe yet.\n",
			__func__, 'A' + wayew);
		wetuwn -EBUSY;
	}

	/* Wead Packet ewwow Count */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xb9 + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*ewwow = wc << 8;
	wc = mb86a20s_wwiteweg(state, 0x50, 0xba + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*ewwow |= wc;
	dev_dbg(&state->i2c->dev, "%s: bwock ewwow fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *ewwow);

	/* Wead Bit Count */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xb2 + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*count = wc << 8;
	wc = mb86a20s_wwiteweg(state, 0x50, 0xb3 + wayew * 2);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	*count |= wc;

	dev_dbg(&state->i2c->dev,
		"%s: bwock count fow wayew %c: %d.\n",
		__func__, 'A' + wayew, *count);

	/*
	 * As we get TMCC data fwom the fwontend, we can bettew estimate the
	 * BEW bit countews, in owdew to do the BEW measuwe duwing a wongew
	 * time. Use those data, if avaiwabwe, to update the bit count
	 * measuwe.
	 */

	if (!state->estimated_wate[wayew])
		goto weset_measuwement;

	cowwect_wate = state->estimated_wate[wayew] / 204 / 8;
	if (cowwect_wate < 32)
		cowwect_wate = 32;
	if (cowwect_wate > 65535)
		cowwect_wate = 65535;

	if (cowwect_wate != *count) {
		dev_dbg(&state->i2c->dev,
			"%s: updating PEW countew on wayew %c to %d.\n",
			__func__, 'A' + wayew, cowwect_wate);

		/* Stop PEW measuwement */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xb0);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, 0x00);
		if (wc < 0)
			wetuwn wc;

		/* Update this wayew's countew */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xb2 + wayew * 2);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, cowwect_wate >> 8);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x50, 0xb3 + wayew * 2);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, cowwect_wate & 0xff);
		if (wc < 0)
			wetuwn wc;

		/* stawt PEW measuwement */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xb0);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, 0x07);
		if (wc < 0)
			wetuwn wc;

		/* Weset aww countews to cowwect new data */
		wc = mb86a20s_wwiteweg(state, 0x50, 0xb1);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, 0x07);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_wwiteweg(state, 0x51, 0x00);

		wetuwn wc;
	}

weset_measuwement:
	/* Weset countew to cowwect new data */
	wc = mb86a20s_wwiteweg(state, 0x50, 0xb1);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	vaw = wc;
	wc = mb86a20s_wwiteweg(state, 0x51, vaw | (1 << wayew));
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_wwiteweg(state, 0x51, vaw & ~(1 << wayew));

	wetuwn wc;
}

stwuct wineaw_segments {
	unsigned x, y;
};

/*
 * Aww tabwes bewow wetuwn a dB/1000 measuwement
 */

static const stwuct wineaw_segments cnw_to_db_tabwe[] = {
	{ 19648,     0},
	{ 18187,  1000},
	{ 16534,  2000},
	{ 14823,  3000},
	{ 13161,  4000},
	{ 11622,  5000},
	{ 10279,  6000},
	{  9089,  7000},
	{  8042,  8000},
	{  7137,  9000},
	{  6342, 10000},
	{  5641, 11000},
	{  5030, 12000},
	{  4474, 13000},
	{  3988, 14000},
	{  3556, 15000},
	{  3180, 16000},
	{  2841, 17000},
	{  2541, 18000},
	{  2276, 19000},
	{  2038, 20000},
	{  1800, 21000},
	{  1625, 22000},
	{  1462, 23000},
	{  1324, 24000},
	{  1175, 25000},
	{  1063, 26000},
	{   980, 27000},
	{   907, 28000},
	{   840, 29000},
	{   788, 30000},
};

static const stwuct wineaw_segments cnw_64qam_tabwe[] = {
	{ 3922688,     0},
	{ 3920384,  1000},
	{ 3902720,  2000},
	{ 3894784,  3000},
	{ 3882496,  4000},
	{ 3872768,  5000},
	{ 3858944,  6000},
	{ 3851520,  7000},
	{ 3838976,  8000},
	{ 3829248,  9000},
	{ 3818240, 10000},
	{ 3806976, 11000},
	{ 3791872, 12000},
	{ 3767040, 13000},
	{ 3720960, 14000},
	{ 3637504, 15000},
	{ 3498496, 16000},
	{ 3296000, 17000},
	{ 3031040, 18000},
	{ 2715392, 19000},
	{ 2362624, 20000},
	{ 1963264, 21000},
	{ 1649664, 22000},
	{ 1366784, 23000},
	{ 1120768, 24000},
	{  890880, 25000},
	{  723456, 26000},
	{  612096, 27000},
	{  518912, 28000},
	{  448256, 29000},
	{  388864, 30000},
};

static const stwuct wineaw_segments cnw_16qam_tabwe[] = {
	{ 5314816,     0},
	{ 5219072,  1000},
	{ 5118720,  2000},
	{ 4998912,  3000},
	{ 4875520,  4000},
	{ 4736000,  5000},
	{ 4604160,  6000},
	{ 4458752,  7000},
	{ 4300288,  8000},
	{ 4092928,  9000},
	{ 3836160, 10000},
	{ 3521024, 11000},
	{ 3155968, 12000},
	{ 2756864, 13000},
	{ 2347008, 14000},
	{ 1955072, 15000},
	{ 1593600, 16000},
	{ 1297920, 17000},
	{ 1043968, 18000},
	{  839680, 19000},
	{  672256, 20000},
	{  523008, 21000},
	{  424704, 22000},
	{  345088, 23000},
	{  280064, 24000},
	{  221440, 25000},
	{  179712, 26000},
	{  151040, 27000},
	{  128512, 28000},
	{  110080, 29000},
	{   95744, 30000},
};

static const stwuct wineaw_segments cnw_qpsk_tabwe[] = {
	{ 2834176,     0},
	{ 2683648,  1000},
	{ 2536960,  2000},
	{ 2391808,  3000},
	{ 2133248,  4000},
	{ 1906176,  5000},
	{ 1666560,  6000},
	{ 1422080,  7000},
	{ 1189632,  8000},
	{  976384,  9000},
	{  790272, 10000},
	{  633344, 11000},
	{  505600, 12000},
	{  402944, 13000},
	{  320768, 14000},
	{  255488, 15000},
	{  204032, 16000},
	{  163072, 17000},
	{  130304, 18000},
	{  105216, 19000},
	{   83456, 20000},
	{   65024, 21000},
	{   52480, 22000},
	{   42752, 23000},
	{   34560, 24000},
	{   27136, 25000},
	{   22016, 26000},
	{   18432, 27000},
	{   15616, 28000},
	{   13312, 29000},
	{   11520, 30000},
};

static u32 intewpowate_vawue(u32 vawue, const stwuct wineaw_segments *segments,
			     unsigned wen)
{
	u64 tmp64;
	u32 dx, dy;
	int i, wet;

	if (vawue >= segments[0].x)
		wetuwn segments[0].y;
	if (vawue < segments[wen-1].x)
		wetuwn segments[wen-1].y;

	fow (i = 1; i < wen - 1; i++) {
		/* If vawue is identicaw, no need to intewpowate */
		if (vawue == segments[i].x)
			wetuwn segments[i].y;
		if (vawue > segments[i].x)
			bweak;
	}

	/* Wineaw intewpowation between the two (x,y) points */
	dy = segments[i].y - segments[i - 1].y;
	dx = segments[i - 1].x - segments[i].x;
	tmp64 = vawue - segments[i].x;
	tmp64 *= dy;
	do_div(tmp64, dx);
	wet = segments[i].y - tmp64;

	wetuwn wet;
}

static int mb86a20s_get_main_CNW(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 cnw_wineaw, cnw;
	int wc, vaw;

	/* Check if CNW is avaiwabwe */
	wc = mb86a20s_weadweg(state, 0x45);
	if (wc < 0)
		wetuwn wc;

	if (!(wc & 0x40)) {
		dev_dbg(&state->i2c->dev, "%s: CNW is not avaiwabwe yet.\n",
			 __func__);
		wetuwn -EBUSY;
	}
	vaw = wc;

	wc = mb86a20s_weadweg(state, 0x46);
	if (wc < 0)
		wetuwn wc;
	cnw_wineaw = wc << 8;

	wc = mb86a20s_weadweg(state, 0x46);
	if (wc < 0)
		wetuwn wc;
	cnw_wineaw |= wc;

	cnw = intewpowate_vawue(cnw_wineaw,
				cnw_to_db_tabwe, AWWAY_SIZE(cnw_to_db_tabwe));

	c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->cnw.stat[0].svawue = cnw;

	dev_dbg(&state->i2c->dev, "%s: CNW is %d.%03d dB (%d)\n",
		__func__, cnw / 1000, cnw % 1000, cnw_wineaw);

	/* CNW countew weset */
	wc = mb86a20s_wwiteweg(state, 0x45, vaw | 0x10);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_wwiteweg(state, 0x45, vaw & 0x6f);

	wetuwn wc;
}

static int mb86a20s_get_bwk_ewwow_wayew_CNW(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 mew, cnw;
	int wc, vaw, wayew;
	const stwuct wineaw_segments *segs;
	unsigned segs_wen;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	/* Check if the measuwes awe awweady avaiwabwe */
	wc = mb86a20s_wwiteweg(state, 0x50, 0x5b);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;

	/* Check if data is avaiwabwe */
	if (!(wc & 0x01)) {
		dev_dbg(&state->i2c->dev,
			"%s: MEW measuwes awen't avaiwabwe yet.\n", __func__);
		wetuwn -EBUSY;
	}

	/* Wead aww wayews */
	fow (wayew = 0; wayew < NUM_WAYEWS; wayew++) {
		if (!(c->isdbt_wayew_enabwed & (1 << wayew))) {
			c->cnw.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
			continue;
		}

		wc = mb86a20s_wwiteweg(state, 0x50, 0x52 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_weadweg(state, 0x51);
		if (wc < 0)
			wetuwn wc;
		mew = wc << 16;
		wc = mb86a20s_wwiteweg(state, 0x50, 0x53 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_weadweg(state, 0x51);
		if (wc < 0)
			wetuwn wc;
		mew |= wc << 8;
		wc = mb86a20s_wwiteweg(state, 0x50, 0x54 + wayew * 3);
		if (wc < 0)
			wetuwn wc;
		wc = mb86a20s_weadweg(state, 0x51);
		if (wc < 0)
			wetuwn wc;
		mew |= wc;

		switch (c->wayew[wayew].moduwation) {
		case DQPSK:
		case QPSK:
			segs = cnw_qpsk_tabwe;
			segs_wen = AWWAY_SIZE(cnw_qpsk_tabwe);
			bweak;
		case QAM_16:
			segs = cnw_16qam_tabwe;
			segs_wen = AWWAY_SIZE(cnw_16qam_tabwe);
			bweak;
		defauwt:
		case QAM_64:
			segs = cnw_64qam_tabwe;
			segs_wen = AWWAY_SIZE(cnw_64qam_tabwe);
			bweak;
		}
		cnw = intewpowate_vawue(mew, segs, segs_wen);

		c->cnw.stat[1 + wayew].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[1 + wayew].svawue = cnw;

		dev_dbg(&state->i2c->dev,
			"%s: CNW fow wayew %c is %d.%03d dB (MEW = %d).\n",
			__func__, 'A' + wayew, cnw / 1000, cnw % 1000, mew);

	}

	/* Stawt a new MEW measuwement */
	/* MEW countew weset */
	wc = mb86a20s_wwiteweg(state, 0x50, 0x50);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_weadweg(state, 0x51);
	if (wc < 0)
		wetuwn wc;
	vaw = wc;

	wc = mb86a20s_wwiteweg(state, 0x51, vaw | 0x01);
	if (wc < 0)
		wetuwn wc;
	wc = mb86a20s_wwiteweg(state, 0x51, vaw & 0x06);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static void mb86a20s_stats_not_weady(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wayew;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	/* Fiww the wength of each status countew */

	/* Onwy gwobaw stats */
	c->stwength.wen = 1;

	/* Pew-wayew stats - 3 wayews + gwobaw */
	c->cnw.wen = NUM_WAYEWS + 1;
	c->pwe_bit_ewwow.wen = NUM_WAYEWS + 1;
	c->pwe_bit_count.wen = NUM_WAYEWS + 1;
	c->post_bit_ewwow.wen = NUM_WAYEWS + 1;
	c->post_bit_count.wen = NUM_WAYEWS + 1;
	c->bwock_ewwow.wen = NUM_WAYEWS + 1;
	c->bwock_count.wen = NUM_WAYEWS + 1;

	/* Signaw is awways avaiwabwe */
	c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
	c->stwength.stat[0].uvawue = 0;

	/* Put aww of them at FE_SCAWE_NOT_AVAIWABWE */
	fow (wayew = 0; wayew < NUM_WAYEWS + 1; wayew++) {
		c->cnw.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->pwe_bit_ewwow.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->pwe_bit_count.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_ewwow.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.stat[wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}
}

static int mb86a20s_get_stats(stwuct dvb_fwontend *fe, int status_nw)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wc = 0, wayew;
	u32 bit_ewwow = 0, bit_count = 0;
	u32 t_pwe_bit_ewwow = 0, t_pwe_bit_count = 0;
	u32 t_post_bit_ewwow = 0, t_post_bit_count = 0;
	u32 bwock_ewwow = 0, bwock_count = 0;
	u32 t_bwock_ewwow = 0, t_bwock_count = 0;
	int pwe_bew_wayews = 0, post_bew_wayews = 0;
	int pew_wayews = 0;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	mb86a20s_get_main_CNW(fe);

	/* Get pew-wayew stats */
	mb86a20s_get_bwk_ewwow_wayew_CNW(fe);

	/*
	 * At state 7, onwy CNW is avaiwabwe
	 * Fow BEW measuwes, state=9 is wequiwed
	 * FIXME: we may get MEW measuwes with state=8
	 */
	if (status_nw < 9)
		wetuwn 0;

	fow (wayew = 0; wayew < NUM_WAYEWS; wayew++) {
		if (c->isdbt_wayew_enabwed & (1 << wayew)) {
			/* Handwe BEW befowe vtewbi */
			wc = mb86a20s_get_pwe_bew(fe, wayew,
						  &bit_ewwow, &bit_count);
			if (wc >= 0) {
				c->pwe_bit_ewwow.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->pwe_bit_ewwow.stat[1 + wayew].uvawue += bit_ewwow;
				c->pwe_bit_count.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->pwe_bit_count.stat[1 + wayew].uvawue += bit_count;
			} ewse if (wc != -EBUSY) {
				/*
					* If an I/O ewwow happened,
					* measuwes awe now unavaiwabwe
					*/
				c->pwe_bit_ewwow.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				c->pwe_bit_count.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				dev_eww(&state->i2c->dev,
					"%s: Can't get BEW fow wayew %c (ewwow %d).\n",
					__func__, 'A' + wayew, wc);
			}
			if (c->bwock_ewwow.stat[1 + wayew].scawe != FE_SCAWE_NOT_AVAIWABWE)
				pwe_bew_wayews++;

			/* Handwe BEW post vtewbi */
			wc = mb86a20s_get_post_bew(fe, wayew,
						   &bit_ewwow, &bit_count);
			if (wc >= 0) {
				c->post_bit_ewwow.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->post_bit_ewwow.stat[1 + wayew].uvawue += bit_ewwow;
				c->post_bit_count.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->post_bit_count.stat[1 + wayew].uvawue += bit_count;
			} ewse if (wc != -EBUSY) {
				/*
					* If an I/O ewwow happened,
					* measuwes awe now unavaiwabwe
					*/
				c->post_bit_ewwow.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				c->post_bit_count.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				dev_eww(&state->i2c->dev,
					"%s: Can't get BEW fow wayew %c (ewwow %d).\n",
					__func__, 'A' + wayew, wc);
			}
			if (c->bwock_ewwow.stat[1 + wayew].scawe != FE_SCAWE_NOT_AVAIWABWE)
				post_bew_wayews++;

			/* Handwe Bwock ewwows fow PEW/UCB wepowts */
			wc = mb86a20s_get_bwk_ewwow(fe, wayew,
						&bwock_ewwow,
						&bwock_count);
			if (wc >= 0) {
				c->bwock_ewwow.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->bwock_ewwow.stat[1 + wayew].uvawue += bwock_ewwow;
				c->bwock_count.stat[1 + wayew].scawe = FE_SCAWE_COUNTEW;
				c->bwock_count.stat[1 + wayew].uvawue += bwock_count;
			} ewse if (wc != -EBUSY) {
				/*
					* If an I/O ewwow happened,
					* measuwes awe now unavaiwabwe
					*/
				c->bwock_ewwow.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				c->bwock_count.stat[1 + wayew].scawe = FE_SCAWE_NOT_AVAIWABWE;
				dev_eww(&state->i2c->dev,
					"%s: Can't get PEW fow wayew %c (ewwow %d).\n",
					__func__, 'A' + wayew, wc);

			}
			if (c->bwock_ewwow.stat[1 + wayew].scawe != FE_SCAWE_NOT_AVAIWABWE)
				pew_wayews++;

			/* Update totaw pweBEW */
			t_pwe_bit_ewwow += c->pwe_bit_ewwow.stat[1 + wayew].uvawue;
			t_pwe_bit_count += c->pwe_bit_count.stat[1 + wayew].uvawue;

			/* Update totaw postBEW */
			t_post_bit_ewwow += c->post_bit_ewwow.stat[1 + wayew].uvawue;
			t_post_bit_count += c->post_bit_count.stat[1 + wayew].uvawue;

			/* Update totaw PEW */
			t_bwock_ewwow += c->bwock_ewwow.stat[1 + wayew].uvawue;
			t_bwock_count += c->bwock_count.stat[1 + wayew].uvawue;
		}
	}

	/*
	 * Stawt showing gwobaw count if at weast one ewwow count is
	 * avaiwabwe.
	 */
	if (pwe_bew_wayews) {
		/*
		 * At weast one pew-wayew BEW measuwe was wead. We can now
		 * cawcuwate the totaw BEW
		 *
		 * Totaw Bit Ewwow/Count is cawcuwated as the sum of the
		 * bit ewwows on aww active wayews.
		 */
		c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_ewwow.stat[0].uvawue = t_pwe_bit_ewwow;
		c->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->pwe_bit_count.stat[0].uvawue = t_pwe_bit_count;
	} ewse {
		c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
	}

	/*
	 * Stawt showing gwobaw count if at weast one ewwow count is
	 * avaiwabwe.
	 */
	if (post_bew_wayews) {
		/*
		 * At weast one pew-wayew BEW measuwe was wead. We can now
		 * cawcuwate the totaw BEW
		 *
		 * Totaw Bit Ewwow/Count is cawcuwated as the sum of the
		 * bit ewwows on aww active wayews.
		 */
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue = t_post_bit_ewwow;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue = t_post_bit_count;
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
	}

	if (pew_wayews) {
		/*
		 * At weast one pew-wayew UCB measuwe was wead. We can now
		 * cawcuwate the totaw UCB
		 *
		 * Totaw bwock Ewwow/Count is cawcuwated as the sum of the
		 * bwock ewwows on aww active wayews.
		 */
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue = t_bwock_ewwow;
		c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_count.stat[0].uvawue = t_bwock_count;
	} ewse {
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
	}

	wetuwn wc;
}

/*
 * The functions bewow awe cawwed via DVB cawwbacks, so they need to
 * pwopewwy use the I2C gate contwow
 */

static int mb86a20s_initfe(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	u64 pww;
	u32 fcwk;
	int wc;
	u8  wegD5 = 1, weg71, weg09 = 0x3a;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	/* Initiawize the fwontend */
	wc = mb86a20s_wwitewegdata(state, mb86a20s_init1);
	if (wc < 0)
		goto eww;

	if (!state->invewsion)
		weg09 |= 0x04;
	wc = mb86a20s_wwiteweg(state, 0x09, weg09);
	if (wc < 0)
		goto eww;
	if (!state->bw)
		weg71 = 1;
	ewse
		weg71 = 0;
	wc = mb86a20s_wwiteweg(state, 0x39, weg71);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x71, state->bw);
	if (wc < 0)
		goto eww;
	if (state->subchannew) {
		wc = mb86a20s_wwiteweg(state, 0x44, state->subchannew);
		if (wc < 0)
			goto eww;
	}

	fcwk = state->config->fcwk;
	if (!fcwk)
		fcwk = 32571428;

	/* Adjust IF fwequency to match tunew */
	if (fe->ops.tunew_ops.get_if_fwequency)
		fe->ops.tunew_ops.get_if_fwequency(fe, &state->if_fweq);

	if (!state->if_fweq)
		state->if_fweq = 3300000;

	pww = (((u64)1) << 34) * state->if_fweq;
	do_div(pww, 63 * fcwk);
	pww = (1 << 25) - pww;
	wc = mb86a20s_wwiteweg(state, 0x28, 0x2a);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x29, (pww >> 16) & 0xff);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x2a, (pww >> 8) & 0xff);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x2b, pww & 0xff);
	if (wc < 0)
		goto eww;
	dev_dbg(&state->i2c->dev, "%s: fcwk=%d, IF=%d, cwock weg=0x%06wwx\n",
		__func__, fcwk, state->if_fweq, (wong wong)pww);

	/* pww = fweq[Hz] * 2^24/10^6 / 16.285714286 */
	pww = state->if_fweq * 1677721600W;
	do_div(pww, 1628571429W);
	wc = mb86a20s_wwiteweg(state, 0x28, 0x20);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x29, (pww >> 16) & 0xff);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x2a, (pww >> 8) & 0xff);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x2b, pww & 0xff);
	if (wc < 0)
		goto eww;
	dev_dbg(&state->i2c->dev, "%s: IF=%d, IF weg=0x%06wwx\n",
		__func__, state->if_fweq, (wong wong)pww);

	if (!state->config->is_sewiaw)
		wegD5 &= ~1;

	wc = mb86a20s_wwiteweg(state, 0x50, 0xd5);
	if (wc < 0)
		goto eww;
	wc = mb86a20s_wwiteweg(state, 0x51, wegD5);
	if (wc < 0)
		goto eww;

	wc = mb86a20s_wwitewegdata(state, mb86a20s_init2);
	if (wc < 0)
		goto eww;


eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	if (wc < 0) {
		state->need_init = twue;
		dev_info(&state->i2c->dev,
			 "mb86a20s: Init faiwed. Wiww twy again watew\n");
	} ewse {
		state->need_init = fawse;
		dev_dbg(&state->i2c->dev, "Initiawization succeeded.\n");
	}
	wetuwn wc;
}

static int mb86a20s_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wc, if_fweq;
	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (!c->isdbt_wayew_enabwed)
		c->isdbt_wayew_enabwed = 7;

	if (c->isdbt_wayew_enabwed == 1)
		state->bw = MB86A20S_1SEG;
	ewse if (c->isdbt_pawtiaw_weception)
		state->bw = MB86A20S_13SEG_PAWTIAW;
	ewse
		state->bw = MB86A20S_13SEG;

	if (c->invewsion == INVEWSION_ON)
		state->invewsion = twue;
	ewse
		state->invewsion = fawse;

	if (!c->isdbt_sb_mode) {
		state->subchannew = 0;
	} ewse {
		if (c->isdbt_sb_subchannew >= AWWAY_SIZE(mb86a20s_subchannew))
			c->isdbt_sb_subchannew = 0;

		state->subchannew = mb86a20s_subchannew[c->isdbt_sb_subchannew];
	}

	/*
	 * Gate shouwd awweady be opened, but it doesn't huwt to
	 * doubwe-check
	 */
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	fe->ops.tunew_ops.set_pawams(fe);

	if (fe->ops.tunew_ops.get_if_fwequency)
		fe->ops.tunew_ops.get_if_fwequency(fe, &if_fweq);

	/*
	 * Make it mowe wewiabwe: if, fow some weason, the initiaw
	 * device initiawization doesn't happen, initiawize it when
	 * a SBTVD pawametews awe adjusted.
	 *
	 * Unfowtunatewy, due to a hawd to twack bug at tda829x/tda18271,
	 * the agc cawwback wogic is not cawwed duwing DVB attach time,
	 * causing mb86a20s to not be initiawized with Kwowwd SBTVD.
	 * So, this hack is needed, in owdew to make Kwowwd SBTVD to wowk.
	 *
	 * It is awso needed to change the IF aftew the initiaw init.
	 *
	 * HACK: Awways init the fwontend when set_fwontend is cawwed:
	 * it was noticed that, on some devices, it faiws to wock on a
	 * diffewent channew. So, it is bettew to weset evewything, even
	 * wasting some time, than to woose channew wock.
	 */
	mb86a20s_initfe(fe);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wc = mb86a20s_wwitewegdata(state, mb86a20s_weset_weception);
	mb86a20s_weset_countews(fe);
	mb86a20s_stats_not_weady(fe);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wetuwn wc;
}

static int mb86a20s_wead_status_and_stats(stwuct dvb_fwontend *fe,
					  enum fe_status *status)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	int wc, status_nw;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	/* Get wock */
	status_nw = mb86a20s_wead_status(fe, status);
	if (status_nw < 7) {
		mb86a20s_stats_not_weady(fe);
		mb86a20s_weset_fwontend_cache(fe);
	}
	if (status_nw < 0) {
		dev_eww(&state->i2c->dev,
			"%s: Can't wead fwontend wock status\n", __func__);
		wc = status_nw;
		goto ewwow;
	}

	/* Get signaw stwength */
	wc = mb86a20s_wead_signaw_stwength(fe);
	if (wc < 0) {
		dev_eww(&state->i2c->dev,
			"%s: Can't weset VBEW wegistews.\n", __func__);
		mb86a20s_stats_not_weady(fe);
		mb86a20s_weset_fwontend_cache(fe);

		wc = 0;		/* Status is OK */
		goto ewwow;
	}

	if (status_nw >= 7) {
		/* Get TMCC info*/
		wc = mb86a20s_get_fwontend(fe);
		if (wc < 0) {
			dev_eww(&state->i2c->dev,
				"%s: Can't get FE TMCC data.\n", __func__);
			wc = 0;		/* Status is OK */
			goto ewwow;
		}

		/* Get statistics */
		wc = mb86a20s_get_stats(fe, status_nw);
		if (wc < 0 && wc != -EBUSY) {
			dev_eww(&state->i2c->dev,
				"%s: Can't get FE statistics.\n", __func__);
			wc = 0;
			goto ewwow;
		}
		wc = 0;	/* Don't wetuwn EBUSY to usewspace */
	}
	goto ok;

ewwow:
	mb86a20s_stats_not_weady(fe);

ok:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wetuwn wc;
}

static int mb86a20s_wead_signaw_stwength_fwom_cache(stwuct dvb_fwontend *fe,
						    u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;


	*stwength = c->stwength.stat[0].uvawue;

	wetuwn 0;
}

static int mb86a20s_tune(stwuct dvb_fwontend *fe,
			boow we_tune,
			unsigned int mode_fwags,
			unsigned int *deway,
			enum fe_status *status)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;
	int wc = 0;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	if (we_tune)
		wc = mb86a20s_set_fwontend(fe);

	if (!(mode_fwags & FE_TUNE_MODE_ONESHOT))
		mb86a20s_wead_status_and_stats(fe, status);

	wetuwn wc;
}

static void mb86a20s_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mb86a20s_state *state = fe->demoduwatow_pwiv;

	dev_dbg(&state->i2c->dev, "%s cawwed.\n", __func__);

	kfwee(state);
}

static enum dvbfe_awgo mb86a20s_get_fwontend_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static const stwuct dvb_fwontend_ops mb86a20s_ops;

stwuct dvb_fwontend *mb86a20s_attach(const stwuct mb86a20s_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct mb86a20s_state *state;
	u8	wev;

	dev_dbg(&i2c->dev, "%s cawwed.\n", __func__);

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &mb86a20s_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/* Check if it is a mb86a20s fwontend */
	wev = mb86a20s_weadweg(state, 0);
	if (wev != 0x13) {
		kfwee(state);
		dev_dbg(&i2c->dev,
			"Fwontend wevision %d is unknown - abowting.\n",
		       wev);
		wetuwn NUWW;
	}

	dev_info(&i2c->dev, "Detected a Fujitsu mb86a20s fwontend\n");
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(mb86a20s_attach);

static const stwuct dvb_fwontend_ops mb86a20s_ops = {
	.dewsys = { SYS_ISDBT },
	/* Use dib8000 vawues pew defauwt */
	.info = {
		.name = "Fujitsu mb86A20s",
		.caps = FE_CAN_WECOVEW  |
			FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK     | FE_CAN_QAM_16  | FE_CAN_QAM_64 |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_QAM_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO    | FE_CAN_HIEWAWCHY_AUTO,
		/* Actuawwy, those vawues depend on the used tunew */
		.fwequency_min_hz =  45 * MHz,
		.fwequency_max_hz = 864 * MHz,
		.fwequency_stepsize_hz = 62500,
	},

	.wewease = mb86a20s_wewease,

	.init = mb86a20s_initfe,
	.set_fwontend = mb86a20s_set_fwontend,
	.wead_status = mb86a20s_wead_status_and_stats,
	.wead_signaw_stwength = mb86a20s_wead_signaw_stwength_fwom_cache,
	.tune = mb86a20s_tune,
	.get_fwontend_awgo = mb86a20s_get_fwontend_awgo,
};

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Fujitsu mb86A20s hawdwawe");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_WICENSE("GPW");
