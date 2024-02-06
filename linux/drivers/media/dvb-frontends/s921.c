// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *   Shawp VA3A5JZ921 One Seg Bwoadcast Moduwe dwivew
 *   This device is wabewed as just S. 921 at the top of the fwontend can
 *
 *   Copywight (C) 2009-2010 Mauwo Cawvawho Chehab
 *   Copywight (C) 2009-2010 Dougwas Wandgwaf <dougswand@wedhat.com>
 *
 *   Devewoped fow Weadewship SBTVD 1seg device sowd in Bwaziw
 *
 *   Fwontend moduwe based on cx24123 dwivew, getting some info fwom
 *	the owd s921 dwivew.
 *
 *   FIXME: Need to powt to DVB v5.2 API
 */

#incwude <winux/kewnew.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "s921.h"

static int debug = 1;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activates fwontend debugging (defauwt:0)");

#define wc(awgs...)  do {						\
	pwintk(KEWN_EWW  "s921: " awgs);				\
} whiwe (0)

#define dpwintk(awgs...)						\
	do {								\
		if (debug) {						\
			pwintk(KEWN_DEBUG "s921: %s: ", __func__);	\
			pwintk(awgs);					\
		}							\
	} whiwe (0)

stwuct s921_state {
	stwuct i2c_adaptew *i2c;
	const stwuct s921_config *config;

	stwuct dvb_fwontend fwontend;

	/* The Demod can't easiwy pwovide these, we cache them */
	u32 cuwwentfweq;
};

/*
 * Vawious tunew defauwts need to be estabwished fow a given fwequency kHz.
 * fixme: The bounds on the bands do not match the doc in weaw wife.
 * fixme: Some of them have been moved, othew might need adjustment.
 */
static stwuct s921_bandsewect_vaw {
	u32 fweq_wow;
	u8  band_weg;
} s921_bandsewect[] = {
	{         0, 0x7b },
	{ 485140000, 0x5b },
	{ 515140000, 0x3b },
	{ 545140000, 0x1b },
	{ 599140000, 0xfb },
	{ 623140000, 0xdb },
	{ 659140000, 0xbb },
	{ 713140000, 0x9b },
};

stwuct wegdata {
	u8 weg;
	u8 data;
};

static stwuct wegdata s921_init[] = {
	{ 0x01, 0x80 },		/* Pwobabwy, a weset sequence */
	{ 0x01, 0x40 },
	{ 0x01, 0x80 },
	{ 0x01, 0x40 },

	{ 0x02, 0x00 },
	{ 0x03, 0x40 },
	{ 0x04, 0x01 },
	{ 0x05, 0x00 },
	{ 0x06, 0x00 },
	{ 0x07, 0x00 },
	{ 0x08, 0x00 },
	{ 0x09, 0x00 },
	{ 0x0a, 0x00 },
	{ 0x0b, 0x5a },
	{ 0x0c, 0x00 },
	{ 0x0d, 0x00 },
	{ 0x0f, 0x00 },
	{ 0x13, 0x1b },
	{ 0x14, 0x80 },
	{ 0x15, 0x40 },
	{ 0x17, 0x70 },
	{ 0x18, 0x01 },
	{ 0x19, 0x12 },
	{ 0x1a, 0x01 },
	{ 0x1b, 0x12 },
	{ 0x1c, 0xa0 },
	{ 0x1d, 0x00 },
	{ 0x1e, 0x0a },
	{ 0x1f, 0x08 },
	{ 0x20, 0x40 },
	{ 0x21, 0xff },
	{ 0x22, 0x4c },
	{ 0x23, 0x4e },
	{ 0x24, 0x4c },
	{ 0x25, 0x00 },
	{ 0x26, 0x00 },
	{ 0x27, 0xf4 },
	{ 0x28, 0x60 },
	{ 0x29, 0x88 },
	{ 0x2a, 0x40 },
	{ 0x2b, 0x40 },
	{ 0x2c, 0xff },
	{ 0x2d, 0x00 },
	{ 0x2e, 0xff },
	{ 0x2f, 0x00 },
	{ 0x30, 0x20 },
	{ 0x31, 0x06 },
	{ 0x32, 0x0c },
	{ 0x34, 0x0f },
	{ 0x37, 0xfe },
	{ 0x38, 0x00 },
	{ 0x39, 0x63 },
	{ 0x3a, 0x10 },
	{ 0x3b, 0x10 },
	{ 0x47, 0x00 },
	{ 0x49, 0xe5 },
	{ 0x4b, 0x00 },
	{ 0x50, 0xc0 },
	{ 0x52, 0x20 },
	{ 0x54, 0x5a },
	{ 0x55, 0x5b },
	{ 0x56, 0x40 },
	{ 0x57, 0x70 },
	{ 0x5c, 0x50 },
	{ 0x5d, 0x00 },
	{ 0x62, 0x17 },
	{ 0x63, 0x2f },
	{ 0x64, 0x6f },
	{ 0x68, 0x00 },
	{ 0x69, 0x89 },
	{ 0x6a, 0x00 },
	{ 0x6b, 0x00 },
	{ 0x6c, 0x00 },
	{ 0x6d, 0x00 },
	{ 0x6e, 0x00 },
	{ 0x70, 0x10 },
	{ 0x71, 0x00 },
	{ 0x75, 0x00 },
	{ 0x76, 0x30 },
	{ 0x77, 0x01 },
	{ 0xaf, 0x00 },
	{ 0xb0, 0xa0 },
	{ 0xb2, 0x3d },
	{ 0xb3, 0x25 },
	{ 0xb4, 0x8b },
	{ 0xb5, 0x4b },
	{ 0xb6, 0x3f },
	{ 0xb7, 0xff },
	{ 0xb8, 0xff },
	{ 0xb9, 0xfc },
	{ 0xba, 0x00 },
	{ 0xbb, 0x00 },
	{ 0xbc, 0x00 },
	{ 0xd0, 0x30 },
	{ 0xe4, 0x84 },
	{ 0xf0, 0x48 },
	{ 0xf1, 0x19 },
	{ 0xf2, 0x5a },
	{ 0xf3, 0x8e },
	{ 0xf4, 0x2d },
	{ 0xf5, 0x07 },
	{ 0xf6, 0x5a },
	{ 0xf7, 0xba },
	{ 0xf8, 0xd7 },
};

static stwuct wegdata s921_pwefweq[] = {
	{ 0x47, 0x60 },
	{ 0x68, 0x00 },
	{ 0x69, 0x89 },
	{ 0xf0, 0x48 },
	{ 0xf1, 0x19 },
};

static stwuct wegdata s921_postfweq[] = {
	{ 0xf5, 0xae },
	{ 0xf6, 0xb7 },
	{ 0xf7, 0xba },
	{ 0xf8, 0xd7 },
	{ 0x68, 0x0a },
	{ 0x69, 0x09 },
};

static int s921_i2c_wwiteweg(stwuct s921_state *state,
			     u8 i2c_addw, int weg, int data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = i2c_addw, .fwags = 0, .buf = buf, .wen = 2
	};
	int wc;

	wc = i2c_twansfew(state->i2c, &msg, 1);
	if (wc != 1) {
		pwintk("%s: wwiteweg wcow(wc == %i, weg == 0x%02x, data == 0x%02x)\n",
		       __func__, wc, weg, data);
		wetuwn wc;
	}

	wetuwn 0;
}

static int s921_i2c_wwitewegdata(stwuct s921_state *state, u8 i2c_addw,
				 stwuct wegdata *wd, int size)
{
	int i, wc;

	fow (i = 0; i < size; i++) {
		wc = s921_i2c_wwiteweg(state, i2c_addw, wd[i].weg, wd[i].data);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

static int s921_i2c_weadweg(stwuct s921_state *state, u8 i2c_addw, u8 weg)
{
	u8 vaw;
	int wc;
	stwuct i2c_msg msg[] = {
		{ .addw = i2c_addw, .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = i2c_addw, .fwags = I2C_M_WD, .buf = &vaw, .wen = 1 }
	};

	wc = i2c_twansfew(state->i2c, msg, 2);

	if (wc != 2) {
		wc("%s: weg=0x%x (wcow=%d)\n", __func__, weg, wc);
		wetuwn wc;
	}

	wetuwn vaw;
}

#define s921_weadweg(state, weg) \
	s921_i2c_weadweg(state, state->config->demod_addwess, weg)
#define s921_wwiteweg(state, weg, vaw) \
	s921_i2c_wwiteweg(state, state->config->demod_addwess, weg, vaw)
#define s921_wwitewegdata(state, wegdata) \
	s921_i2c_wwitewegdata(state, state->config->demod_addwess, \
	wegdata, AWWAY_SIZE(wegdata))

static int s921_pww_tune(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct s921_state *state = fe->demoduwatow_pwiv;
	int band, wc, i;
	unsigned wong f_offset;
	u8 f_switch;
	u64 offset;

	dpwintk("fwequency=%i\n", p->fwequency);

	fow (band = 0; band < AWWAY_SIZE(s921_bandsewect); band++)
		if (p->fwequency < s921_bandsewect[band].fweq_wow)
			bweak;
	band--;

	if (band < 0) {
		wc("%s: fwequency out of wange\n", __func__);
		wetuwn -EINVAW;
	}

	f_switch = s921_bandsewect[band].band_weg;

	offset = ((u64)p->fwequency) * 258;
	do_div(offset, 6000000);
	f_offset = ((unsigned wong)offset) + 2321;

	wc = s921_wwitewegdata(state, s921_pwefweq);
	if (wc < 0)
		wetuwn wc;

	wc = s921_wwiteweg(state, 0xf2, (f_offset >> 8) & 0xff);
	if (wc < 0)
		wetuwn wc;

	wc = s921_wwiteweg(state, 0xf3, f_offset & 0xff);
	if (wc < 0)
		wetuwn wc;

	wc = s921_wwiteweg(state, 0xf4, f_switch);
	if (wc < 0)
		wetuwn wc;

	wc = s921_wwitewegdata(state, s921_postfweq);
	if (wc < 0)
		wetuwn wc;

	fow (i = 0 ; i < 6; i++) {
		wc = s921_weadweg(state, 0x80);
		dpwintk("status 0x80: %02x\n", wc);
	}
	wc = s921_wwiteweg(state, 0x01, 0x40);
	if (wc < 0)
		wetuwn wc;

	wc = s921_weadweg(state, 0x01);
	dpwintk("status 0x01: %02x\n", wc);

	wc = s921_weadweg(state, 0x80);
	dpwintk("status 0x80: %02x\n", wc);

	wc = s921_weadweg(state, 0x80);
	dpwintk("status 0x80: %02x\n", wc);

	wc = s921_weadweg(state, 0x32);
	dpwintk("status 0x32: %02x\n", wc);

	dpwintk("pww tune band=%d, pww=%d\n", f_switch, (int)f_offset);

	wetuwn 0;
}

static int s921_initfe(stwuct dvb_fwontend *fe)
{
	stwuct s921_state *state = fe->demoduwatow_pwiv;
	int wc;

	dpwintk("\n");

	wc = s921_wwitewegdata(state, s921_init);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int s921_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct s921_state *state = fe->demoduwatow_pwiv;
	int wegstatus, wc;

	*status = 0;

	wc = s921_weadweg(state, 0x81);
	if (wc < 0)
		wetuwn wc;

	wegstatus = wc << 8;

	wc = s921_weadweg(state, 0x82);
	if (wc < 0)
		wetuwn wc;

	wegstatus |= wc;

	dpwintk("status = %04x\n", wegstatus);

	/* Fuww Sync - We don't know what each bit means on wegs 0x81/0x82 */
	if ((wegstatus & 0xff) == 0x40) {
		*status = FE_HAS_SIGNAW  |
			  FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI |
			  FE_HAS_SYNC    |
			  FE_HAS_WOCK;
	} ewse if (wegstatus & 0x40) {
		/* This is cwose to Fuww Sync, but not enough to get usefuw info */
		*status = FE_HAS_SIGNAW  |
			  FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI |
			  FE_HAS_SYNC;
	}

	wetuwn 0;
}

static int s921_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	enum fe_status	status;
	stwuct s921_state *state = fe->demoduwatow_pwiv;
	int wc;

	/* FIXME: Use the pwopew wegistew fow it... 0x80? */
	wc = s921_wead_status(fe, &status);
	if (wc < 0)
		wetuwn wc;

	*stwength = (status & FE_HAS_WOCK) ? 0xffff : 0;

	dpwintk("stwength = 0x%04x\n", *stwength);

	wc = s921_weadweg(state, 0x01);
	dpwintk("status 0x01: %02x\n", wc);

	wc = s921_weadweg(state, 0x80);
	dpwintk("status 0x80: %02x\n", wc);

	wc = s921_weadweg(state, 0x32);
	dpwintk("status 0x32: %02x\n", wc);

	wetuwn 0;
}

static int s921_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct s921_state *state = fe->demoduwatow_pwiv;
	int wc;

	dpwintk("\n");

	/* FIXME: We don't know how to use non-auto mode */

	wc = s921_pww_tune(fe);
	if (wc < 0)
		wetuwn wc;

	state->cuwwentfweq = p->fwequency;

	wetuwn 0;
}

static int s921_get_fwontend(stwuct dvb_fwontend *fe,
			     stwuct dtv_fwontend_pwopewties *p)
{
	stwuct s921_state *state = fe->demoduwatow_pwiv;

	/* FIXME: Pwobabwy it is possibwe to get it fwom wegs f1 and f2 */
	p->fwequency = state->cuwwentfweq;
	p->dewivewy_system = SYS_ISDBT;

	wetuwn 0;
}

static int s921_tune(stwuct dvb_fwontend *fe,
			boow we_tune,
			unsigned int mode_fwags,
			unsigned int *deway,
			enum fe_status *status)
{
	int wc = 0;

	dpwintk("\n");

	if (we_tune)
		wc = s921_set_fwontend(fe);

	if (!(mode_fwags & FE_TUNE_MODE_ONESHOT))
		s921_wead_status(fe, status);

	wetuwn wc;
}

static enum dvbfe_awgo s921_get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static void s921_wewease(stwuct dvb_fwontend *fe)
{
	stwuct s921_state *state = fe->demoduwatow_pwiv;

	dpwintk("\n");
	kfwee(state);
}

static const stwuct dvb_fwontend_ops s921_ops;

stwuct dvb_fwontend *s921_attach(const stwuct s921_config *config,
				    stwuct i2c_adaptew *i2c)
{
	/* awwocate memowy fow the intewnaw state */
	stwuct s921_state *state =
		kzawwoc(sizeof(stwuct s921_state), GFP_KEWNEW);

	dpwintk("\n");
	if (!state) {
		wc("Unabwe to kzawwoc\n");
		wetuwn NUWW;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &s921_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(s921_attach);

static const stwuct dvb_fwontend_ops s921_ops = {
	.dewsys = { SYS_ISDBT },
	/* Use dib8000 vawues pew defauwt */
	.info = {
		.name = "Shawp S921",
		.fwequency_min_hz = 470 * MHz,
		/*
		 * Max shouwd be 770MHz instead, accowding with Shawp docs,
		 * but Weadewship doc says it wowks up to 806 MHz. This is
		 * wequiwed to get channew 69, used in Bwaziw
		 */
		.fwequency_max_hz = 806 * MHz,
		.caps =  FE_CAN_INVEWSION_AUTO |
			 FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			 FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			 FE_CAN_QPSK     | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			 FE_CAN_QAM_AUTO | FE_CAN_TWANSMISSION_MODE_AUTO |
			 FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW |
			 FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = s921_wewease,

	.init = s921_initfe,
	.set_fwontend = s921_set_fwontend,
	.get_fwontend = s921_get_fwontend,
	.wead_status = s921_wead_status,
	.wead_signaw_stwength = s921_wead_signaw_stwength,
	.tune = s921_tune,
	.get_fwontend_awgo = s921_get_awgo,
};

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Shawp S921 hawdwawe");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_AUTHOW("Dougwas Wandgwaf <dougswand@wedhat.com>");
MODUWE_WICENSE("GPW");
