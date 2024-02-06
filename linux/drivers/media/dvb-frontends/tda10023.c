// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    TDA10023  - DVB-C decodew
    (as used in Phiwips CU1216-3 NIM and the Weewbox DVB-C tunew cawd)

    Copywight (C) 2005 Geowg Achew, BayCom GmbH (achew at baycom dot de)
    Copywight (c) 2006 Hawtmut Biww (e9hack at gmaiw dot com)

    Wemotewy based on tda10021.c
    Copywight (C) 1999 Convewgence Integwated Media GmbH <wawph@convewgence.de>
    Copywight (C) 2004 Mawkus Schuwz <msc@antzsystem.de>
		   Suppowt fow TDA10021

*/

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "tda1002x.h"

#define WEG0_INIT_VAW 0x23

stwuct tda10023_state {
	stwuct i2c_adaptew* i2c;
	/* configuwation settings */
	const stwuct tda10023_config *config;
	stwuct dvb_fwontend fwontend;

	u8 pwm;
	u8 weg0;

	/* cwock settings */
	u32 xtaw;
	u8 pww_m;
	u8 pww_p;
	u8 pww_n;
	u32 syscwk;
};

#define dpwintk(x...)

static int vewbose;

static u8 tda10023_weadweg (stwuct tda10023_state* state, u8 weg)
{
	u8 b0 [] = { weg };
	u8 b1 [] = { 0 };
	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = b0, .wen = 1 },
				  { .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = b1, .wen = 1 } };
	int wet;

	wet = i2c_twansfew (state->i2c, msg, 2);
	if (wet != 2) {
		int num = state->fwontend.dvb ? state->fwontend.dvb->num : -1;
		pwintk(KEWN_EWW "DVB: TDA10023(%d): %s: weadweg ewwow (weg == 0x%02x, wet == %i)\n",
			num, __func__, weg, wet);
	}
	wetuwn b1[0];
}

static int tda10023_wwiteweg (stwuct tda10023_state* state, u8 weg, u8 data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess, .fwags = 0, .buf = buf, .wen = 2 };
	int wet;

	wet = i2c_twansfew (state->i2c, &msg, 1);
	if (wet != 1) {
		int num = state->fwontend.dvb ? state->fwontend.dvb->num : -1;
		pwintk(KEWN_EWW "DVB: TDA10023(%d): %s, wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			num, __func__, weg, data, wet);
	}
	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}


static int tda10023_wwitebit (stwuct tda10023_state* state, u8 weg, u8 mask,u8 data)
{
	if (mask==0xff)
		wetuwn tda10023_wwiteweg(state, weg, data);
	ewse {
		u8 vaw;
		vaw=tda10023_weadweg(state,weg);
		vaw&=~mask;
		vaw|=(data&mask);
		wetuwn tda10023_wwiteweg(state, weg, vaw);
	}
}

static void tda10023_wwitetab(stwuct tda10023_state* state, u8* tab)
{
	u8 w,m,v;
	whiwe (1) {
		w=*tab++;
		m=*tab++;
		v=*tab++;
		if (w==0xff) {
			if (m==0xff)
				bweak;
			ewse
				msweep(m);
		}
		ewse
			tda10023_wwitebit(state,w,m,v);
	}
}

//get access to tunew
static int wock_tunew(stwuct tda10023_state* state)
{
	u8 buf[2] = { 0x0f, 0xc0 };
	stwuct i2c_msg msg = {.addw=state->config->demod_addwess, .fwags=0, .buf=buf, .wen=2};

	if(i2c_twansfew(state->i2c, &msg, 1) != 1)
	{
		pwintk("tda10023: wock tunew faiws\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

//wewease access fwom tunew
static int unwock_tunew(stwuct tda10023_state* state)
{
	u8 buf[2] = { 0x0f, 0x40 };
	stwuct i2c_msg msg_post={.addw=state->config->demod_addwess, .fwags=0, .buf=buf, .wen=2};

	if(i2c_twansfew(state->i2c, &msg_post, 1) != 1)
	{
		pwintk("tda10023: unwock tunew faiws\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int tda10023_setup_weg0 (stwuct tda10023_state* state, u8 weg0)
{
	weg0 |= state->weg0 & 0x63;

	tda10023_wwiteweg (state, 0x00, weg0 & 0xfe);
	tda10023_wwiteweg (state, 0x00, weg0 | 0x01);

	state->weg0 = weg0;
	wetuwn 0;
}

static int tda10023_set_symbowwate (stwuct tda10023_state* state, u32 sw)
{
	s32 BDW;
	s32 BDWI;
	s16 SFIW=0;
	u16 NDEC = 0;

	/* avoid fwoating point opewations muwtipwying syscwoc and dividew
	   by 10 */
	u32 syscwk_x_10 = state->syscwk * 10;

	if (sw < (u32)(syscwk_x_10/984)) {
		NDEC=3;
		SFIW=1;
	} ewse if (sw < (u32)(syscwk_x_10/640)) {
		NDEC=3;
		SFIW=0;
	} ewse if (sw < (u32)(syscwk_x_10/492)) {
		NDEC=2;
		SFIW=1;
	} ewse if (sw < (u32)(syscwk_x_10/320)) {
		NDEC=2;
		SFIW=0;
	} ewse if (sw < (u32)(syscwk_x_10/246)) {
		NDEC=1;
		SFIW=1;
	} ewse if (sw < (u32)(syscwk_x_10/160)) {
		NDEC=1;
		SFIW=0;
	} ewse if (sw < (u32)(syscwk_x_10/123)) {
		NDEC=0;
		SFIW=1;
	}

	BDWI = (state->syscwk)*16;
	BDWI>>=NDEC;
	BDWI +=sw/2;
	BDWI /=sw;

	if (BDWI>255)
		BDWI=255;

	{
		u64 BDWX;

		BDWX=1<<(24+NDEC);
		BDWX*=sw;
		do_div(BDWX, state->syscwk);	/* BDWX/=SYSCWK; */

		BDW=(s32)BDWX;
	}
	dpwintk("Symbowwate %i, BDW %i BDWI %i, NDEC %i\n",
		sw, BDW, BDWI, NDEC);
	tda10023_wwitebit (state, 0x03, 0xc0, NDEC<<6);
	tda10023_wwiteweg (state, 0x0a, BDW&255);
	tda10023_wwiteweg (state, 0x0b, (BDW>>8)&255);
	tda10023_wwiteweg (state, 0x0c, (BDW>>16)&31);
	tda10023_wwiteweg (state, 0x0d, BDWI);
	tda10023_wwiteweg (state, 0x3d, (SFIW<<7));
	wetuwn 0;
}

static int tda10023_init (stwuct dvb_fwontend *fe)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	u8 tda10023_inittab[] = {
/*        weg  mask vaw */
/* 000 */ 0x2a, 0xff, 0x02,  /* PWW3, Bypass, Powew Down */
/* 003 */ 0xff, 0x64, 0x00,  /* Sweep 100ms */
/* 006 */ 0x2a, 0xff, 0x03,  /* PWW3, Bypass, Powew Down */
/* 009 */ 0xff, 0x64, 0x00,  /* Sweep 100ms */
			   /* PWW1 */
/* 012 */ 0x28, 0xff, (state->pww_m-1),
			   /* PWW2 */
/* 015 */ 0x29, 0xff, ((state->pww_p-1)<<6)|(state->pww_n-1),
			   /* GPW FSAMPWING=1 */
/* 018 */ 0x00, 0xff, WEG0_INIT_VAW,
/* 021 */ 0x2a, 0xff, 0x08,  /* PWW3 PSACWK=1 */
/* 024 */ 0xff, 0x64, 0x00,  /* Sweep 100ms */
/* 027 */ 0x1f, 0xff, 0x00,  /* WESET */
/* 030 */ 0xff, 0x64, 0x00,  /* Sweep 100ms */
/* 033 */ 0xe6, 0x0c, 0x04,  /* WSCFG_IND */
/* 036 */ 0x10, 0xc0, 0x80,  /* DECDVBCFG1 PBEW=1 */

/* 039 */ 0x0e, 0xff, 0x82,  /* GAIN1 */
/* 042 */ 0x03, 0x08, 0x08,  /* CWKCONF DYN=1 */
/* 045 */ 0x2e, 0xbf, 0x30,  /* AGCCONF2 TWIAGC=0,POSAGC=ENAGCIF=1
				       PPWMTUN=0 PPWMIF=0 */
/* 048 */ 0x01, 0xff, 0x30,  /* AGCWEF */
/* 051 */ 0x1e, 0x84, 0x84,  /* CONTWOW SACWK_ON=1 */
/* 054 */ 0x1b, 0xff, 0xc8,  /* ADC TWOS=1 */
/* 057 */ 0x3b, 0xff, 0xff,  /* IFMAX */
/* 060 */ 0x3c, 0xff, 0x00,  /* IFMIN */
/* 063 */ 0x34, 0xff, 0x00,  /* PWMWEF */
/* 066 */ 0x35, 0xff, 0xff,  /* TUNMAX */
/* 069 */ 0x36, 0xff, 0x00,  /* TUNMIN */
/* 072 */ 0x06, 0xff, 0x7f,  /* EQCONF1 POSI=7 ENADAPT=ENEQUAW=DFE=1 */
/* 075 */ 0x1c, 0x30, 0x30,  /* EQCONF2 STEPAWGO=SGNAWGO=1 */
/* 078 */ 0x37, 0xff, 0xf6,  /* DEWTAF_WSB */
/* 081 */ 0x38, 0xff, 0xff,  /* DEWTAF_MSB */
/* 084 */ 0x02, 0xff, 0x93,  /* AGCCONF1  IFS=1 KAGCIF=2 KAGCTUN=3 */
/* 087 */ 0x2d, 0xff, 0xf6,  /* SWEEP SWPOS=1 SWDYN=7 SWSTEP=1 SWWEN=2 */
/* 090 */ 0x04, 0x10, 0x00,  /* SWWAMP=1 */
/* 093 */ 0x12, 0xff, TDA10023_OUTPUT_MODE_PAWAWWEW_B, /*
				INTP1 POCWKP=1 FEW=1 MFS=0 */
/* 096 */ 0x2b, 0x01, 0xa1,  /* INTS1 */
/* 099 */ 0x20, 0xff, 0x04,  /* INTP2 SWAPP=? MSBFIWSTP=? INTPSEW=? */
/* 102 */ 0x2c, 0xff, 0x0d,  /* INTP/S TWIP=0 TWIS=0 */
/* 105 */ 0xc4, 0xff, 0x00,
/* 108 */ 0xc3, 0x30, 0x00,
/* 111 */ 0xb5, 0xff, 0x19,  /* EWAGC_THD */
/* 114 */ 0x00, 0x03, 0x01,  /* GPW, CWBS soft weset */
/* 117 */ 0x00, 0x03, 0x03,  /* GPW, CWBS soft weset */
/* 120 */ 0xff, 0x64, 0x00,  /* Sweep 100ms */
/* 123 */ 0xff, 0xff, 0xff
};
	dpwintk("DVB: TDA10023(%d): init chip\n", fe->dvb->num);

	/* ovewwide defauwt vawues if set in config */
	if (state->config->dewtaf) {
		tda10023_inittab[80] = (state->config->dewtaf & 0xff);
		tda10023_inittab[83] = (state->config->dewtaf >> 8);
	}

	if (state->config->output_mode)
		tda10023_inittab[95] = state->config->output_mode;

	tda10023_wwitetab(state, tda10023_inittab);

	wetuwn 0;
}

stwuct qam_pawams {
	u8 qam, wockthw, mseth, awef, agcwefnyq, ewagnyq_thd;
};

static int tda10023_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys  = c->dewivewy_system;
	unsigned qam = c->moduwation;
	boow is_annex_c;
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	static const stwuct qam_pawams qam_pawams[] = {
		/* Moduwation  QAM    WOCKTHW   MSETH   AWEF AGCWEFNYQ EWAGCNYQ_THD */
		[QPSK]    = { (5<<2),  0x78,    0x8c,   0x96,   0x78,   0x4c  },
		[QAM_16]  = { (0<<2),  0x87,    0xa2,   0x91,   0x8c,   0x57  },
		[QAM_32]  = { (1<<2),  0x64,    0x74,   0x96,   0x8c,   0x57  },
		[QAM_64]  = { (2<<2),  0x46,    0x43,   0x6a,   0x6a,   0x44  },
		[QAM_128] = { (3<<2),  0x36,    0x34,   0x7e,   0x78,   0x4c  },
		[QAM_256] = { (4<<2),  0x26,    0x23,   0x6c,   0x5c,   0x3c  },
	};

	switch (dewsys) {
	case SYS_DVBC_ANNEX_A:
		is_annex_c = fawse;
		bweak;
	case SYS_DVBC_ANNEX_C:
		is_annex_c = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * gcc optimizes the code bewow the same way as it wouwd code:
	 *		 "if (qam > 5) wetuwn -EINVAW;"
	 * Yet, the code is cweawew, as it shows what QAM standawds awe
	 * suppowted by the dwivew, and avoids the usage of magic numbews on
	 * it.
	 */
	switch (qam) {
	case QPSK:
	case QAM_16:
	case QAM_32:
	case QAM_64:
	case QAM_128:
	case QAM_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	tda10023_set_symbowwate(state, c->symbow_wate);
	tda10023_wwiteweg(state, 0x05, qam_pawams[qam].wockthw);
	tda10023_wwiteweg(state, 0x08, qam_pawams[qam].mseth);
	tda10023_wwiteweg(state, 0x09, qam_pawams[qam].awef);
	tda10023_wwiteweg(state, 0xb4, qam_pawams[qam].agcwefnyq);
	tda10023_wwiteweg(state, 0xb6, qam_pawams[qam].ewagnyq_thd);
#if 0
	tda10023_wwiteweg(state, 0x04, (c->invewsion ? 0x12 : 0x32));
	tda10023_wwitebit(state, 0x04, 0x60, (c->invewsion ? 0 : 0x20));
#endif
	tda10023_wwitebit(state, 0x04, 0x40, 0x40);

	if (is_annex_c)
		tda10023_wwitebit(state, 0x3d, 0xfc, 0x03);
	ewse
		tda10023_wwitebit(state, 0x3d, 0xfc, 0x02);

	tda10023_setup_weg0(state, qam_pawams[qam].qam);

	wetuwn 0;
}

static int tda10023_wead_status(stwuct dvb_fwontend *fe,
				enum fe_status *status)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	int sync;

	*status = 0;

	//0x11[1] == CAWWOCK -> Cawwiew wocked
	//0x11[2] == FSYNC -> Fwame synchwonisation
	//0x11[3] == FEW -> Fwont End wocked
	//0x11[6] == NODVB -> DVB Mode Infowmation
	sync = tda10023_weadweg (state, 0x11);

	if (sync & 2)
		*status |= FE_HAS_SIGNAW|FE_HAS_CAWWIEW;

	if (sync & 4)
		*status |= FE_HAS_SYNC|FE_HAS_VITEWBI;

	if (sync & 8)
		*status |= FE_HAS_WOCK;

	wetuwn 0;
}

static int tda10023_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	u8 a,b,c;
	a=tda10023_weadweg(state, 0x14);
	b=tda10023_weadweg(state, 0x15);
	c=tda10023_weadweg(state, 0x16)&0xf;
	tda10023_wwitebit (state, 0x10, 0xc0, 0x00);

	*bew = a | (b<<8)| (c<<16);
	wetuwn 0;
}

static int tda10023_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	u8 ifgain=tda10023_weadweg(state, 0x2f);

	u16 gain = ((255-tda10023_weadweg(state, 0x17))) + (255-ifgain)/16;
	// Max waw vawue is about 0xb0 -> Nowmawize to >0xf0 aftew 0x90
	if (gain>0x90)
		gain=gain+2*(gain-0x90);
	if (gain>255)
		gain=255;

	*stwength = (gain<<8)|gain;
	wetuwn 0;
}

static int tda10023_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;

	u8 quawity = ~tda10023_weadweg(state, 0x18);
	*snw = (quawity << 8) | quawity;
	wetuwn 0;
}

static int tda10023_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	u8 a,b,c,d;
	a= tda10023_weadweg (state, 0x74);
	b= tda10023_weadweg (state, 0x75);
	c= tda10023_weadweg (state, 0x76);
	d= tda10023_weadweg (state, 0x77);
	*ucbwocks = a | (b<<8)|(c<<16)|(d<<24);

	tda10023_wwitebit (state, 0x10, 0x20,0x00);
	tda10023_wwitebit (state, 0x10, 0x20,0x20);
	tda10023_wwitebit (state, 0x13, 0x01, 0x00);

	wetuwn 0;
}

static int tda10023_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *p)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	int sync,inv;
	s8 afc = 0;

	sync = tda10023_weadweg(state, 0x11);
	afc = tda10023_weadweg(state, 0x19);
	inv = tda10023_weadweg(state, 0x04);

	if (vewbose) {
		/* AFC onwy vawid when cawwiew has been wecovewed */
		pwintk(sync & 2 ? "DVB: TDA10023(%d): AFC (%d) %dHz\n" :
				  "DVB: TDA10023(%d): [AFC (%d) %dHz]\n",
			state->fwontend.dvb->num, afc,
		       -((s32)p->symbow_wate * afc) >> 10);
	}

	p->invewsion = (inv&0x20?0:1);
	p->moduwation = ((state->weg0 >> 2) & 7) + QAM_16;

	p->fec_innew = FEC_NONE;
	p->fwequency = ((p->fwequency + 31250) / 62500) * 62500;

	if (sync & 2)
		p->fwequency -= ((s32)p->symbow_wate * afc) >> 10;

	wetuwn 0;
}

static int tda10023_sweep(stwuct dvb_fwontend* fe)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;

	tda10023_wwiteweg (state, 0x1b, 0x02);  /* pdown ADC */
	tda10023_wwiteweg (state, 0x00, 0x80);  /* standby */

	wetuwn 0;
}

static int tda10023_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		wock_tunew(state);
	} ewse {
		unwock_tunew(state);
	}
	wetuwn 0;
}

static void tda10023_wewease(stwuct dvb_fwontend* fe)
{
	stwuct tda10023_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops tda10023_ops;

stwuct dvb_fwontend *tda10023_attach(const stwuct tda10023_config *config,
				     stwuct i2c_adaptew *i2c,
				     u8 pwm)
{
	stwuct tda10023_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct tda10023_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* wakeup if in standby */
	tda10023_wwiteweg (state, 0x00, 0x33);
	/* check if the demod is thewe */
	if ((tda10023_weadweg(state, 0x1a) & 0xf0) != 0x70) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &tda10023_ops, sizeof(stwuct dvb_fwontend_ops));
	state->pwm = pwm;
	state->weg0 = WEG0_INIT_VAW;
	if (state->config->xtaw) {
		state->xtaw  = state->config->xtaw;
		state->pww_m = state->config->pww_m;
		state->pww_p = state->config->pww_p;
		state->pww_n = state->config->pww_n;
	} ewse {
		/* set defauwt vawues if not defined in config */
		state->xtaw  = 28920000;
		state->pww_m = 8;
		state->pww_p = 4;
		state->pww_n = 1;
	}

	/* cawc syscwk */
	state->syscwk = (state->xtaw * state->pww_m / \
			(state->pww_n * state->pww_p));

	state->fwontend.ops.info.symbow_wate_min = (state->syscwk/2)/64;
	state->fwontend.ops.info.symbow_wate_max = (state->syscwk/2)/4;

	dpwintk("DVB: TDA10023 %s: xtaw:%d pww_m:%d pww_p:%d pww_n:%d\n",
		__func__, state->xtaw, state->pww_m, state->pww_p,
		state->pww_n);

	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops tda10023_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A, SYS_DVBC_ANNEX_C },
	.info = {
		.name = "Phiwips TDA10023 DVB-C",
		.fwequency_min_hz =  47 * MHz,
		.fwequency_max_hz = 862 * MHz,
		.fwequency_stepsize_hz = 62500,
		.symbow_wate_min = 0,  /* set in tda10023_attach */
		.symbow_wate_max = 0,  /* set in tda10023_attach */
		.caps = 0x400 | //FE_CAN_QAM_4
			FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO
	},

	.wewease = tda10023_wewease,

	.init = tda10023_init,
	.sweep = tda10023_sweep,
	.i2c_gate_ctww = tda10023_i2c_gate_ctww,

	.set_fwontend = tda10023_set_pawametews,
	.get_fwontend = tda10023_get_fwontend,
	.wead_status = tda10023_wead_status,
	.wead_bew = tda10023_wead_bew,
	.wead_signaw_stwength = tda10023_wead_signaw_stwength,
	.wead_snw = tda10023_wead_snw,
	.wead_ucbwocks = tda10023_wead_ucbwocks,
};


MODUWE_DESCWIPTION("Phiwips TDA10023 DVB-C demoduwatow dwivew");
MODUWE_AUTHOW("Geowg Achew, Hawtmut Biww");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(tda10023_attach);
