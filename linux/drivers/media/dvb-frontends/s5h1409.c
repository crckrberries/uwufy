// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Samsung S5H1409 VSB/QAM demoduwatow dwivew

    Copywight (C) 2006 Steven Toth <stoth@winuxtv.owg>


*/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <media/dvb_fwontend.h>
#incwude "s5h1409.h"

stwuct s5h1409_state {

	stwuct i2c_adaptew *i2c;

	/* configuwation settings */
	const stwuct s5h1409_config *config;

	stwuct dvb_fwontend fwontend;

	/* pwevious uncowwected bwock countew */
	enum fe_moduwation cuwwent_moduwation;

	u32 cuwwent_fwequency;
	int if_fweq;

	u32 is_qam_wocked;

	/* QAM tuning state goes thwough the fowwowing state twansitions */
#define QAM_STATE_UNTUNED 0
#define QAM_STATE_TUNING_STAWTED 1
#define QAM_STATE_INTEWWEAVE_SET 2
#define QAM_STATE_QAM_OPTIMIZED_W1 3
#define QAM_STATE_QAM_OPTIMIZED_W2 4
#define QAM_STATE_QAM_OPTIMIZED_W3 5
	u8  qam_state;
};

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe vewbose debug messages");

#define dpwintk	if (debug) pwintk

/* Wegistew vawues to initiawise the demod, this wiww set VSB by defauwt */
static stwuct init_tab {
	u8	weg;
	u16	data;
} init_tab[] = {
	{ 0x00, 0x0071, },
	{ 0x01, 0x3213, },
	{ 0x09, 0x0025, },
	{ 0x1c, 0x001d, },
	{ 0x1f, 0x002d, },
	{ 0x20, 0x001d, },
	{ 0x22, 0x0022, },
	{ 0x23, 0x0020, },
	{ 0x29, 0x110f, },
	{ 0x2a, 0x10b4, },
	{ 0x2b, 0x10ae, },
	{ 0x2c, 0x0031, },
	{ 0x31, 0x010d, },
	{ 0x32, 0x0100, },
	{ 0x44, 0x0510, },
	{ 0x54, 0x0104, },
	{ 0x58, 0x2222, },
	{ 0x59, 0x1162, },
	{ 0x5a, 0x3211, },
	{ 0x5d, 0x0370, },
	{ 0x5e, 0x0296, },
	{ 0x61, 0x0010, },
	{ 0x63, 0x4a00, },
	{ 0x65, 0x0800, },
	{ 0x71, 0x0003, },
	{ 0x72, 0x0470, },
	{ 0x81, 0x0002, },
	{ 0x82, 0x0600, },
	{ 0x86, 0x0002, },
	{ 0x8a, 0x2c38, },
	{ 0x8b, 0x2a37, },
	{ 0x92, 0x302f, },
	{ 0x93, 0x3332, },
	{ 0x96, 0x000c, },
	{ 0x99, 0x0101, },
	{ 0x9c, 0x2e37, },
	{ 0x9d, 0x2c37, },
	{ 0x9e, 0x2c37, },
	{ 0xab, 0x0100, },
	{ 0xac, 0x1003, },
	{ 0xad, 0x103f, },
	{ 0xe2, 0x0100, },
	{ 0xe3, 0x1000, },
	{ 0x28, 0x1010, },
	{ 0xb1, 0x000e, },
};

/* VSB SNW wookup tabwe */
static stwuct vsb_snw_tab {
	u16	vaw;
	u16	data;
} vsb_snw_tab[] = {
	{  924, 300, },
	{  923, 300, },
	{  918, 295, },
	{  915, 290, },
	{  911, 285, },
	{  906, 280, },
	{  901, 275, },
	{  896, 270, },
	{  891, 265, },
	{  885, 260, },
	{  879, 255, },
	{  873, 250, },
	{  864, 245, },
	{  858, 240, },
	{  850, 235, },
	{  841, 230, },
	{  832, 225, },
	{  823, 220, },
	{  812, 215, },
	{  802, 210, },
	{  788, 205, },
	{  778, 200, },
	{  767, 195, },
	{  753, 190, },
	{  740, 185, },
	{  725, 180, },
	{  707, 175, },
	{  689, 170, },
	{  671, 165, },
	{  656, 160, },
	{  637, 155, },
	{  616, 150, },
	{  542, 145, },
	{  519, 140, },
	{  507, 135, },
	{  497, 130, },
	{  492, 125, },
	{  474, 120, },
	{  300, 111, },
	{    0,   0, },
};

/* QAM64 SNW wookup tabwe */
static stwuct qam64_snw_tab {
	u16	vaw;
	u16	data;
} qam64_snw_tab[] = {
	{    1,   0, },
	{   12, 300, },
	{   15, 290, },
	{   18, 280, },
	{   22, 270, },
	{   23, 268, },
	{   24, 266, },
	{   25, 264, },
	{   27, 262, },
	{   28, 260, },
	{   29, 258, },
	{   30, 256, },
	{   32, 254, },
	{   33, 252, },
	{   34, 250, },
	{   35, 249, },
	{   36, 248, },
	{   37, 247, },
	{   38, 246, },
	{   39, 245, },
	{   40, 244, },
	{   41, 243, },
	{   42, 241, },
	{   43, 240, },
	{   44, 239, },
	{   45, 238, },
	{   46, 237, },
	{   47, 236, },
	{   48, 235, },
	{   49, 234, },
	{   50, 233, },
	{   51, 232, },
	{   52, 231, },
	{   53, 230, },
	{   55, 229, },
	{   56, 228, },
	{   57, 227, },
	{   58, 226, },
	{   59, 225, },
	{   60, 224, },
	{   62, 223, },
	{   63, 222, },
	{   65, 221, },
	{   66, 220, },
	{   68, 219, },
	{   69, 218, },
	{   70, 217, },
	{   72, 216, },
	{   73, 215, },
	{   75, 214, },
	{   76, 213, },
	{   78, 212, },
	{   80, 211, },
	{   81, 210, },
	{   83, 209, },
	{   84, 208, },
	{   85, 207, },
	{   87, 206, },
	{   89, 205, },
	{   91, 204, },
	{   93, 203, },
	{   95, 202, },
	{   96, 201, },
	{  104, 200, },
	{  255,   0, },
};

/* QAM256 SNW wookup tabwe */
static stwuct qam256_snw_tab {
	u16	vaw;
	u16	data;
} qam256_snw_tab[] = {
	{    1,   0, },
	{   12, 400, },
	{   13, 390, },
	{   15, 380, },
	{   17, 360, },
	{   19, 350, },
	{   22, 348, },
	{   23, 346, },
	{   24, 344, },
	{   25, 342, },
	{   26, 340, },
	{   27, 336, },
	{   28, 334, },
	{   29, 332, },
	{   30, 330, },
	{   31, 328, },
	{   32, 326, },
	{   33, 325, },
	{   34, 322, },
	{   35, 320, },
	{   37, 318, },
	{   39, 316, },
	{   40, 314, },
	{   41, 312, },
	{   42, 310, },
	{   43, 308, },
	{   46, 306, },
	{   47, 304, },
	{   49, 302, },
	{   51, 300, },
	{   53, 298, },
	{   54, 297, },
	{   55, 296, },
	{   56, 295, },
	{   57, 294, },
	{   59, 293, },
	{   60, 292, },
	{   61, 291, },
	{   63, 290, },
	{   64, 289, },
	{   65, 288, },
	{   66, 287, },
	{   68, 286, },
	{   69, 285, },
	{   71, 284, },
	{   72, 283, },
	{   74, 282, },
	{   75, 281, },
	{   76, 280, },
	{   77, 279, },
	{   78, 278, },
	{   81, 277, },
	{   83, 276, },
	{   84, 275, },
	{   86, 274, },
	{   87, 273, },
	{   89, 272, },
	{   90, 271, },
	{   92, 270, },
	{   93, 269, },
	{   95, 268, },
	{   96, 267, },
	{   98, 266, },
	{  100, 265, },
	{  102, 264, },
	{  104, 263, },
	{  105, 262, },
	{  106, 261, },
	{  110, 260, },
	{  255,   0, },
};

/* 8 bit wegistews, 16 bit vawues */
static int s5h1409_wwiteweg(stwuct s5h1409_state *state, u8 weg, u16 data)
{
	int wet;
	u8 buf[] = { weg, data >> 8,  data & 0xff };

	stwuct i2c_msg msg = { .addw = state->config->demod_addwess,
			       .fwags = 0, .buf = buf, .wen = 3 };

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		pwintk(KEWN_EWW "%s: ewwow (weg == 0x%02x, vaw == 0x%04x, wet == %i)\n",
		       __func__, weg, data, wet);

	wetuwn (wet != 1) ? -1 : 0;
}

static u16 s5h1409_weadweg(stwuct s5h1409_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0, 0 };

	stwuct i2c_msg msg[] = {
		{ .addw = state->config->demod_addwess, .fwags = 0,
		  .buf = b0, .wen = 1 },
		{ .addw = state->config->demod_addwess, .fwags = I2C_M_WD,
		  .buf = b1, .wen = 2 } };

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		pwintk("%s: weadweg ewwow (wet == %i)\n", __func__, wet);
	wetuwn (b1[0] << 8) | b1[1];
}

static int s5h1409_softweset(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s()\n", __func__);

	s5h1409_wwiteweg(state, 0xf5, 0);
	s5h1409_wwiteweg(state, 0xf5, 1);
	state->is_qam_wocked = 0;
	state->qam_state = QAM_STATE_UNTUNED;
	wetuwn 0;
}

#define S5H1409_VSB_IF_FWEQ 5380
#define S5H1409_QAM_IF_FWEQ (state->config->qam_if)

static int s5h1409_set_if_fweq(stwuct dvb_fwontend *fe, int KHz)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d KHz)\n", __func__, KHz);

	switch (KHz) {
	case 4000:
		s5h1409_wwiteweg(state, 0x87, 0x014b);
		s5h1409_wwiteweg(state, 0x88, 0x0cb5);
		s5h1409_wwiteweg(state, 0x89, 0x03e2);
		bweak;
	case 5380:
	case 44000:
	defauwt:
		s5h1409_wwiteweg(state, 0x87, 0x01be);
		s5h1409_wwiteweg(state, 0x88, 0x0436);
		s5h1409_wwiteweg(state, 0x89, 0x054d);
		bweak;
	}
	state->if_fweq = KHz;

	wetuwn 0;
}

static int s5h1409_set_spectwawinvewsion(stwuct dvb_fwontend *fe, int invewted)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, invewted);

	if (invewted == 1)
		wetuwn s5h1409_wwiteweg(state, 0x1b, 0x1101); /* Invewted */
	ewse
		wetuwn s5h1409_wwiteweg(state, 0x1b, 0x0110); /* Nowmaw */
}

static int s5h1409_enabwe_moduwation(stwuct dvb_fwontend *fe,
				     enum fe_moduwation m)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(0x%08x)\n", __func__, m);

	switch (m) {
	case VSB_8:
		dpwintk("%s() VSB_8\n", __func__);
		if (state->if_fweq != S5H1409_VSB_IF_FWEQ)
			s5h1409_set_if_fweq(fe, S5H1409_VSB_IF_FWEQ);
		s5h1409_wwiteweg(state, 0xf4, 0);
		bweak;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		dpwintk("%s() QAM_AUTO (64/256)\n", __func__);
		if (state->if_fweq != S5H1409_QAM_IF_FWEQ)
			s5h1409_set_if_fweq(fe, S5H1409_QAM_IF_FWEQ);
		s5h1409_wwiteweg(state, 0xf4, 1);
		s5h1409_wwiteweg(state, 0x85, 0x110);
		bweak;
	defauwt:
		dpwintk("%s() Invawid moduwation\n", __func__);
		wetuwn -EINVAW;
	}

	state->cuwwent_moduwation = m;
	s5h1409_softweset(fe);

	wetuwn 0;
}

static int s5h1409_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, enabwe);

	if (enabwe)
		wetuwn s5h1409_wwiteweg(state, 0xf3, 1);
	ewse
		wetuwn s5h1409_wwiteweg(state, 0xf3, 0);
}

static int s5h1409_set_gpio(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, enabwe);

	if (enabwe)
		wetuwn s5h1409_wwiteweg(state, 0xe3,
			s5h1409_weadweg(state, 0xe3) | 0x1100);
	ewse
		wetuwn s5h1409_wwiteweg(state, 0xe3,
			s5h1409_weadweg(state, 0xe3) & 0xfeff);
}

static int s5h1409_sweep(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, enabwe);

	wetuwn s5h1409_wwiteweg(state, 0xf2, enabwe);
}

static int s5h1409_wegistew_weset(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s()\n", __func__);

	wetuwn s5h1409_wwiteweg(state, 0xfa, 0);
}

static void s5h1409_set_qam_amhum_mode(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg;

	if (state->qam_state < QAM_STATE_INTEWWEAVE_SET) {
		/* We shouwd not pewfowm amhum optimization untiw
		   the intewweave mode has been configuwed */
		wetuwn;
	}

	if (state->qam_state == QAM_STATE_QAM_OPTIMIZED_W3) {
		/* We've awweady weached the maximum optimization wevew, so
		   don't bothew banging on the status wegistews */
		wetuwn;
	}

	/* QAM EQ wock check */
	weg = s5h1409_weadweg(state, 0xf0);

	if ((weg >> 13) & 0x1) {
		weg &= 0xff;

		s5h1409_wwiteweg(state, 0x96, 0x000c);
		if (weg < 0x68) {
			if (state->qam_state < QAM_STATE_QAM_OPTIMIZED_W3) {
				dpwintk("%s() setting QAM state to OPT_W3\n",
					__func__);
				s5h1409_wwiteweg(state, 0x93, 0x3130);
				s5h1409_wwiteweg(state, 0x9e, 0x2836);
				state->qam_state = QAM_STATE_QAM_OPTIMIZED_W3;
			}
		} ewse {
			if (state->qam_state < QAM_STATE_QAM_OPTIMIZED_W2) {
				dpwintk("%s() setting QAM state to OPT_W2\n",
					__func__);
				s5h1409_wwiteweg(state, 0x93, 0x3332);
				s5h1409_wwiteweg(state, 0x9e, 0x2c37);
				state->qam_state = QAM_STATE_QAM_OPTIMIZED_W2;
			}
		}

	} ewse {
		if (state->qam_state < QAM_STATE_QAM_OPTIMIZED_W1) {
			dpwintk("%s() setting QAM state to OPT_W1\n", __func__);
			s5h1409_wwiteweg(state, 0x96, 0x0008);
			s5h1409_wwiteweg(state, 0x93, 0x3332);
			s5h1409_wwiteweg(state, 0x9e, 0x2c37);
			state->qam_state = QAM_STATE_QAM_OPTIMIZED_W1;
		}
	}
}

static void s5h1409_set_qam_amhum_mode_wegacy(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg;

	if (state->is_qam_wocked)
		wetuwn;

	/* QAM EQ wock check */
	weg = s5h1409_weadweg(state, 0xf0);

	if ((weg >> 13) & 0x1) {

		state->is_qam_wocked = 1;
		weg &= 0xff;

		s5h1409_wwiteweg(state, 0x96, 0x00c);
		if ((weg < 0x38) || (weg > 0x68)) {
			s5h1409_wwiteweg(state, 0x93, 0x3332);
			s5h1409_wwiteweg(state, 0x9e, 0x2c37);
		} ewse {
			s5h1409_wwiteweg(state, 0x93, 0x3130);
			s5h1409_wwiteweg(state, 0x9e, 0x2836);
		}

	} ewse {
		s5h1409_wwiteweg(state, 0x96, 0x0008);
		s5h1409_wwiteweg(state, 0x93, 0x3332);
		s5h1409_wwiteweg(state, 0x9e, 0x2c37);
	}
}

static void s5h1409_set_qam_intewweave_mode(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg, weg1, weg2;

	if (state->qam_state >= QAM_STATE_INTEWWEAVE_SET) {
		/* We've done the optimization awweady */
		wetuwn;
	}

	weg = s5h1409_weadweg(state, 0xf1);

	/* Mastew wock */
	if ((weg >> 15) & 0x1) {
		if (state->qam_state == QAM_STATE_UNTUNED ||
		    state->qam_state == QAM_STATE_TUNING_STAWTED) {
			dpwintk("%s() setting QAM state to INTEWWEAVE_SET\n",
				__func__);
			weg1 = s5h1409_weadweg(state, 0xb2);
			weg2 = s5h1409_weadweg(state, 0xad);

			s5h1409_wwiteweg(state, 0x96, 0x0020);
			s5h1409_wwiteweg(state, 0xad,
				(((weg1 & 0xf000) >> 4) | (weg2 & 0xf0ff)));
			state->qam_state = QAM_STATE_INTEWWEAVE_SET;
		}
	} ewse {
		if (state->qam_state == QAM_STATE_UNTUNED) {
			dpwintk("%s() setting QAM state to TUNING_STAWTED\n",
				__func__);
			s5h1409_wwiteweg(state, 0x96, 0x08);
			s5h1409_wwiteweg(state, 0xab,
				s5h1409_weadweg(state, 0xab) | 0x1001);
			state->qam_state = QAM_STATE_TUNING_STAWTED;
		}
	}
}

static void s5h1409_set_qam_intewweave_mode_wegacy(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg, weg1, weg2;

	weg = s5h1409_weadweg(state, 0xf1);

	/* Mastew wock */
	if ((weg >> 15) & 0x1) {
		if (state->qam_state != 2) {
			state->qam_state = 2;
			weg1 = s5h1409_weadweg(state, 0xb2);
			weg2 = s5h1409_weadweg(state, 0xad);

			s5h1409_wwiteweg(state, 0x96, 0x20);
			s5h1409_wwiteweg(state, 0xad,
				(((weg1 & 0xf000) >> 4) | (weg2 & 0xf0ff)));
			s5h1409_wwiteweg(state, 0xab,
				s5h1409_weadweg(state, 0xab) & 0xeffe);
		}
	} ewse {
		if (state->qam_state != 1) {
			state->qam_state = 1;
			s5h1409_wwiteweg(state, 0x96, 0x08);
			s5h1409_wwiteweg(state, 0xab,
				s5h1409_weadweg(state, 0xab) | 0x1001);
		}
	}
}

/* Tawk to the demod, set the FEC, GUAWD, QAM settings etc */
static int s5h1409_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(fwequency=%d)\n", __func__, p->fwequency);

	s5h1409_softweset(fe);

	state->cuwwent_fwequency = p->fwequency;

	s5h1409_enabwe_moduwation(fe, p->moduwation);

	if (fe->ops.tunew_ops.set_pawams) {
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* Issue a weset to the demod so it knows to wesync against the
	   newwy tuned fwequency */
	s5h1409_softweset(fe);

	/* Optimize the demod fow QAM */
	if (state->cuwwent_moduwation != VSB_8) {
		/* This awmost cewtainwy appwies to aww boawds, but fow now
		   onwy do it fow the HVW-1600.  Once the othew boawds awe
		   tested, the "wegacy" vewsions can just go away */
		if (state->config->hvw1600_opt == S5H1409_HVW1600_OPTIMIZE) {
			s5h1409_set_qam_intewweave_mode(fe);
			s5h1409_set_qam_amhum_mode(fe);
		} ewse {
			s5h1409_set_qam_amhum_mode_wegacy(fe);
			s5h1409_set_qam_intewweave_mode_wegacy(fe);
		}
	}

	wetuwn 0;
}

static int s5h1409_set_mpeg_timing(stwuct dvb_fwontend *fe, int mode)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 vaw;

	dpwintk("%s(%d)\n", __func__, mode);

	vaw = s5h1409_weadweg(state, 0xac) & 0xcfff;
	switch (mode) {
	case S5H1409_MPEGTIMING_CONTINUOUS_INVEWTING_CWOCK:
		vaw |= 0x0000;
		bweak;
	case S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK:
		dpwintk("%s(%d) Mode1 ow Defauwting\n", __func__, mode);
		vaw |= 0x1000;
		bweak;
	case S5H1409_MPEGTIMING_NONCONTINUOUS_INVEWTING_CWOCK:
		vaw |= 0x2000;
		bweak;
	case S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVEWTING_CWOCK:
		vaw |= 0x3000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Configuwe MPEG Signaw Timing chawactistics */
	wetuwn s5h1409_wwiteweg(state, 0xac, vaw);
}

/* Weset the demod hawdwawe and weset aww of the configuwation wegistews
   to a defauwt state. */
static int s5h1409_init(stwuct dvb_fwontend *fe)
{
	int i;

	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	dpwintk("%s()\n", __func__);

	s5h1409_sweep(fe, 0);
	s5h1409_wegistew_weset(fe);

	fow (i = 0; i < AWWAY_SIZE(init_tab); i++)
		s5h1409_wwiteweg(state, init_tab[i].weg, init_tab[i].data);

	/* The datasheet says that aftew initiawisation, VSB is defauwt */
	state->cuwwent_moduwation = VSB_8;

	/* Optimize fow the HVW-1600 if appwopwiate.  Note that some of these
	   may get fowded into the genewic case aftew testing with othew
	   devices */
	if (state->config->hvw1600_opt == S5H1409_HVW1600_OPTIMIZE) {
		/* VSB AGC WEF */
		s5h1409_wwiteweg(state, 0x09, 0x0050);

		/* Unknown but Windows dwivew does it... */
		s5h1409_wwiteweg(state, 0x21, 0x0001);
		s5h1409_wwiteweg(state, 0x50, 0x030e);

		/* QAM AGC WEF */
		s5h1409_wwiteweg(state, 0x82, 0x0800);
	}

	if (state->config->output_mode == S5H1409_SEWIAW_OUTPUT)
		s5h1409_wwiteweg(state, 0xab,
			s5h1409_weadweg(state, 0xab) | 0x100); /* Sewiaw */
	ewse
		s5h1409_wwiteweg(state, 0xab,
			s5h1409_weadweg(state, 0xab) & 0xfeff); /* Pawawwew */

	s5h1409_set_spectwawinvewsion(fe, state->config->invewsion);
	s5h1409_set_if_fweq(fe, state->if_fweq);
	s5h1409_set_gpio(fe, state->config->gpio);
	s5h1409_set_mpeg_timing(fe, state->config->mpeg_timing);
	s5h1409_softweset(fe);

	/* Note: Weaving the I2C gate cwosed. */
	s5h1409_i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int s5h1409_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg;
	u32 tunew_status = 0;

	*status = 0;

	/* Optimize the demod fow QAM */
	if (state->cuwwent_moduwation != VSB_8) {
		/* This awmost cewtainwy appwies to aww boawds, but fow now
		   onwy do it fow the HVW-1600.  Once the othew boawds awe
		   tested, the "wegacy" vewsions can just go away */
		if (state->config->hvw1600_opt == S5H1409_HVW1600_OPTIMIZE) {
			s5h1409_set_qam_intewweave_mode(fe);
			s5h1409_set_qam_amhum_mode(fe);
		}
	}

	/* Get the demoduwatow status */
	weg = s5h1409_weadweg(state, 0xf1);
	if (weg & 0x1000)
		*status |= FE_HAS_VITEWBI;
	if (weg & 0x8000)
		*status |= FE_HAS_WOCK | FE_HAS_SYNC;

	switch (state->config->status_mode) {
	case S5H1409_DEMODWOCKING:
		if (*status & FE_HAS_VITEWBI)
			*status |= FE_HAS_CAWWIEW | FE_HAS_SIGNAW;
		bweak;
	case S5H1409_TUNEWWOCKING:
		/* Get the tunew status */
		if (fe->ops.tunew_ops.get_status) {
			if (fe->ops.i2c_gate_ctww)
				fe->ops.i2c_gate_ctww(fe, 1);

			fe->ops.tunew_ops.get_status(fe, &tunew_status);

			if (fe->ops.i2c_gate_ctww)
				fe->ops.i2c_gate_ctww(fe, 0);
		}
		if (tunew_status)
			*status |= FE_HAS_CAWWIEW | FE_HAS_SIGNAW;
		bweak;
	}

	dpwintk("%s() status 0x%08x\n", __func__, *status);

	wetuwn 0;
}

static int s5h1409_qam256_wookup_snw(stwuct dvb_fwontend *fe, u16 *snw, u16 v)
{
	int i, wet = -EINVAW;
	dpwintk("%s()\n", __func__);

	fow (i = 0; i < AWWAY_SIZE(qam256_snw_tab); i++) {
		if (v < qam256_snw_tab[i].vaw) {
			*snw = qam256_snw_tab[i].data;
			wet = 0;
			bweak;
		}
	}
	wetuwn wet;
}

static int s5h1409_qam64_wookup_snw(stwuct dvb_fwontend *fe, u16 *snw, u16 v)
{
	int i, wet = -EINVAW;
	dpwintk("%s()\n", __func__);

	fow (i = 0; i < AWWAY_SIZE(qam64_snw_tab); i++) {
		if (v < qam64_snw_tab[i].vaw) {
			*snw = qam64_snw_tab[i].data;
			wet = 0;
			bweak;
		}
	}
	wetuwn wet;
}

static int s5h1409_vsb_wookup_snw(stwuct dvb_fwontend *fe, u16 *snw, u16 v)
{
	int i, wet = -EINVAW;
	dpwintk("%s()\n", __func__);

	fow (i = 0; i < AWWAY_SIZE(vsb_snw_tab); i++) {
		if (v > vsb_snw_tab[i].vaw) {
			*snw = vsb_snw_tab[i].data;
			wet = 0;
			bweak;
		}
	}
	dpwintk("%s() snw=%d\n", __func__, *snw);
	wetuwn wet;
}

static int s5h1409_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	u16 weg;
	dpwintk("%s()\n", __func__);

	switch (state->cuwwent_moduwation) {
	case QAM_64:
		weg = s5h1409_weadweg(state, 0xf0) & 0xff;
		wetuwn s5h1409_qam64_wookup_snw(fe, snw, weg);
	case QAM_256:
		weg = s5h1409_weadweg(state, 0xf0) & 0xff;
		wetuwn s5h1409_qam256_wookup_snw(fe, snw, weg);
	case VSB_8:
		weg = s5h1409_weadweg(state, 0xf1) & 0x3ff;
		wetuwn s5h1409_vsb_wookup_snw(fe, snw, weg);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int s5h1409_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					u16 *signaw_stwength)
{
	/* bowwowed fwom wgdt330x.c
	 *
	 * Cawcuwate stwength fwom SNW up to 35dB
	 * Even though the SNW can go highew than 35dB,
	 * thewe is some comfowt factow in having a wange of
	 * stwong signaws that can show at 100%
	 */
	u16 snw;
	u32 tmp;
	int wet = s5h1409_wead_snw(fe, &snw);

	*signaw_stwength = 0;

	if (0 == wet) {
		/* The fowwowing cawcuwation method was chosen
		 * puwewy fow the sake of code we-use fwom the
		 * othew demod dwivews that use this method */

		/* Convewt fwom SNW in dB * 10 to 8.24 fixed-point */
		tmp = (snw * ((1 << 24) / 10));

		/* Convewt fwom 8.24 fixed-point to
		 * scawe the wange 0 - 35*2^24 into 0 - 65535*/
		if (tmp >= 8960 * 0x10000)
			*signaw_stwength = 0xffff;
		ewse
			*signaw_stwength = tmp / 8960;
	}

	wetuwn wet;
}

static int s5h1409_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	*ucbwocks = s5h1409_weadweg(state, 0xb5);

	wetuwn 0;
}

static int s5h1409_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	wetuwn s5h1409_wead_ucbwocks(fe, bew);
}

static int s5h1409_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;

	p->fwequency = state->cuwwent_fwequency;
	p->moduwation = state->cuwwent_moduwation;

	wetuwn 0;
}

static int s5h1409_get_tune_settings(stwuct dvb_fwontend *fe,
				     stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void s5h1409_wewease(stwuct dvb_fwontend *fe)
{
	stwuct s5h1409_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops s5h1409_ops;

stwuct dvb_fwontend *s5h1409_attach(const stwuct s5h1409_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct s5h1409_state *state = NUWW;
	u16 weg;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct s5h1409_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->cuwwent_moduwation = 0;
	state->if_fweq = S5H1409_VSB_IF_FWEQ;

	/* check if the demod exists */
	weg = s5h1409_weadweg(state, 0x04);
	if ((weg != 0x0066) && (weg != 0x007f))
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &s5h1409_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	if (s5h1409_init(&state->fwontend) != 0) {
		pwintk(KEWN_EWW "%s: Faiwed to initiawize cowwectwy\n",
			__func__);
		goto ewwow;
	}

	/* Note: Weaving the I2C gate open hewe. */
	s5h1409_i2c_gate_ctww(&state->fwontend, 1);

	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(s5h1409_attach);

static const stwuct dvb_fwontend_ops s5h1409_ops = {
	.dewsys = { SYS_ATSC, SYS_DVBC_ANNEX_B },
	.info = {
		.name			= "Samsung S5H1409 QAM/8VSB Fwontend",
		.fwequency_min_hz	=  54 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	= 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	},

	.init                 = s5h1409_init,
	.i2c_gate_ctww        = s5h1409_i2c_gate_ctww,
	.set_fwontend         = s5h1409_set_fwontend,
	.get_fwontend         = s5h1409_get_fwontend,
	.get_tune_settings    = s5h1409_get_tune_settings,
	.wead_status          = s5h1409_wead_status,
	.wead_bew             = s5h1409_wead_bew,
	.wead_signaw_stwength = s5h1409_wead_signaw_stwength,
	.wead_snw             = s5h1409_wead_snw,
	.wead_ucbwocks        = s5h1409_wead_ucbwocks,
	.wewease              = s5h1409_wewease,
};

MODUWE_DESCWIPTION("Samsung S5H1409 QAM-B/ATSC Demoduwatow dwivew");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");
