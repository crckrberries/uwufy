// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Fujitsu MB86A16 DVB-S/DSS DC Weceivew dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "mb86a16.h"
#incwude "mb86a16_pwiv.h"

static unsigned int vewbose = 5;
moduwe_pawam(vewbose, int, 0644);

stwuct mb86a16_state {
	stwuct i2c_adaptew		*i2c_adap;
	const stwuct mb86a16_config	*config;
	stwuct dvb_fwontend		fwontend;

	/* tuning pawametews */
	int				fwequency;
	int				swate;

	/* Intewnaw stuff */
	int				mastew_cwk;
	int				deci;
	int				csew;
	int				wsew;
};

#define MB86A16_EWWOW		0
#define MB86A16_NOTICE		1
#define MB86A16_INFO		2
#define MB86A16_DEBUG		3

#define dpwintk(x, y, z, fowmat, awg...) do {						\
	if (z) {									\
		if	((x > MB86A16_EWWOW) && (x > y))				\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__, ##awg);		\
		ewse if ((x > MB86A16_NOTICE) && (x > y))				\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__, ##awg);	\
		ewse if ((x > MB86A16_INFO) && (x > y))					\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__, ##awg);		\
		ewse if ((x > MB86A16_DEBUG) && (x > y))				\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__, ##awg);		\
	} ewse {									\
		if (x > y)								\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe (0)

#define TWACE_IN	dpwintk(vewbose, MB86A16_DEBUG, 1, "-->()")
#define TWACE_OUT	dpwintk(vewbose, MB86A16_DEBUG, 1, "()-->")

static int mb86a16_wwite(stwuct mb86a16_state *state, u8 weg, u8 vaw)
{
	int wet;
	u8 buf[] = { weg, vaw };

	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = 2
	};

	dpwintk(vewbose, MB86A16_DEBUG, 1,
		"wwiting to [0x%02x],Weg[0x%02x],Data[0x%02x]",
		state->config->demod_addwess, buf[0], buf[1]);

	wet = i2c_twansfew(state->i2c_adap, &msg, 1);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static int mb86a16_wead(stwuct mb86a16_state *state, u8 weg, u8 *vaw)
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
	wet = i2c_twansfew(state->i2c_adap, msg, 2);
	if (wet != 2) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "wead ewwow(weg=0x%02x, wet=%i)",
			weg, wet);

		if (wet < 0)
			wetuwn wet;
		wetuwn -EWEMOTEIO;
	}
	*vaw = b1[0];

	wetuwn wet;
}

static int CNTM_set(stwuct mb86a16_state *state,
		    unsigned chaw timint1,
		    unsigned chaw timint2,
		    unsigned chaw cnext)
{
	unsigned chaw vaw;

	vaw = (timint1 << 4) | (timint2 << 2) | cnext;
	if (mb86a16_wwite(state, MB86A16_CNTMW, vaw) < 0)
		goto eww;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int smwt_set(stwuct mb86a16_state *state, int wate)
{
	int tmp ;
	int m ;
	unsigned chaw STOFS0, STOFS1;

	m = 1 << state->deci;
	tmp = (8192 * state->mastew_cwk - 2 * m * wate * 8192 + state->mastew_cwk / 2) / state->mastew_cwk;

	STOFS0 = tmp & 0x0ff;
	STOFS1 = (tmp & 0xf00) >> 8;

	if (mb86a16_wwite(state, MB86A16_SWATE1, (state->deci << 2) |
				       (state->csew << 1) |
					state->wsew) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_SWATE2, STOFS0) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_SWATE3, STOFS1) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -1;
}

static int swst(stwuct mb86a16_state *state)
{
	if (mb86a16_wwite(state, MB86A16_WESET, 0x04) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;

}

static int afcex_data_set(stwuct mb86a16_state *state,
			  unsigned chaw AFCEX_W,
			  unsigned chaw AFCEX_H)
{
	if (mb86a16_wwite(state, MB86A16_AFCEXW, AFCEX_W) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_AFCEXH, AFCEX_H) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");

	wetuwn -1;
}

static int afcofs_data_set(stwuct mb86a16_state *state,
			   unsigned chaw AFCEX_W,
			   unsigned chaw AFCEX_H)
{
	if (mb86a16_wwite(state, 0x58, AFCEX_W) < 0)
		goto eww;
	if (mb86a16_wwite(state, 0x59, AFCEX_H) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int stwp_set(stwuct mb86a16_state *state,
		    unsigned chaw STWAS,
		    unsigned chaw STWBS)
{
	if (mb86a16_wwite(state, MB86A16_STWFIWTCOEF1, (STWBS << 3) | (STWAS)) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int Vi_set(stwuct mb86a16_state *state, unsigned chaw ETH, unsigned chaw VIA)
{
	if (mb86a16_wwite(state, MB86A16_VISET2, 0x04) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_VISET3, 0xf5) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int initiaw_set(stwuct mb86a16_state *state)
{
	if (stwp_set(state, 5, 7))
		goto eww;

	udeway(100);
	if (afcex_data_set(state, 0, 0))
		goto eww;

	udeway(100);
	if (afcofs_data_set(state, 0, 0))
		goto eww;

	udeway(100);
	if (mb86a16_wwite(state, MB86A16_CWWFIWTCOEF1, 0x16) < 0)
		goto eww;
	if (mb86a16_wwite(state, 0x2f, 0x21) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_VIMAG, 0x38) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_FAGCS1, 0x00) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_FAGCS2, 0x1c) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_FAGCS3, 0x20) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_FAGCS4, 0x1e) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_FAGCS5, 0x23) < 0)
		goto eww;
	if (mb86a16_wwite(state, 0x54, 0xff) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_TSOUT, 0x00) < 0)
		goto eww;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int S01T_set(stwuct mb86a16_state *state,
		    unsigned chaw s1t,
		    unsigned s0t)
{
	if (mb86a16_wwite(state, 0x33, (s1t << 3) | s0t) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}


static int EN_set(stwuct mb86a16_state *state,
		  int cwen,
		  int afcen)
{
	unsigned chaw vaw;

	vaw = 0x7a | (cwen << 7) | (afcen << 2);
	if (mb86a16_wwite(state, 0x49, vaw) < 0)
		goto eww;

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int AFCEXEN_set(stwuct mb86a16_state *state,
		       int afcexen,
		       int smwt)
{
	unsigned chaw AFCA ;

	if (smwt > 18875)
		AFCA = 4;
	ewse if (smwt > 9375)
		AFCA = 3;
	ewse if (smwt > 2250)
		AFCA = 2;
	ewse
		AFCA = 1;

	if (mb86a16_wwite(state, 0x2a, 0x02 | (afcexen << 5) | (AFCA << 2)) < 0)
		goto eww;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int DAGC_data_set(stwuct mb86a16_state *state,
			 unsigned chaw DAGCA,
			 unsigned chaw DAGCW)
{
	if (mb86a16_wwite(state, 0x2d, (DAGCA << 3) | DAGCW) < 0)
		goto eww;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static void smwt_info_get(stwuct mb86a16_state *state, int wate)
{
	if (wate >= 37501) {
		state->deci = 0; state->csew = 0; state->wsew = 0;
	} ewse if (wate >= 30001) {
		state->deci = 0; state->csew = 0; state->wsew = 1;
	} ewse if (wate >= 26251) {
		state->deci = 0; state->csew = 1; state->wsew = 0;
	} ewse if (wate >= 22501) {
		state->deci = 0; state->csew = 1; state->wsew = 1;
	} ewse if (wate >= 18751) {
		state->deci = 1; state->csew = 0; state->wsew = 0;
	} ewse if (wate >= 15001) {
		state->deci = 1; state->csew = 0; state->wsew = 1;
	} ewse if (wate >= 13126) {
		state->deci = 1; state->csew = 1; state->wsew = 0;
	} ewse if (wate >= 11251) {
		state->deci = 1; state->csew = 1; state->wsew = 1;
	} ewse if (wate >= 9376) {
		state->deci = 2; state->csew = 0; state->wsew = 0;
	} ewse if (wate >= 7501) {
		state->deci = 2; state->csew = 0; state->wsew = 1;
	} ewse if (wate >= 6563) {
		state->deci = 2; state->csew = 1; state->wsew = 0;
	} ewse if (wate >= 5626) {
		state->deci = 2; state->csew = 1; state->wsew = 1;
	} ewse if (wate >= 4688) {
		state->deci = 3; state->csew = 0; state->wsew = 0;
	} ewse if (wate >= 3751) {
		state->deci = 3; state->csew = 0; state->wsew = 1;
	} ewse if (wate >= 3282) {
		state->deci = 3; state->csew = 1; state->wsew = 0;
	} ewse if (wate >= 2814) {
		state->deci = 3; state->csew = 1; state->wsew = 1;
	} ewse if (wate >= 2344) {
		state->deci = 4; state->csew = 0; state->wsew = 0;
	} ewse if (wate >= 1876) {
		state->deci = 4; state->csew = 0; state->wsew = 1;
	} ewse if (wate >= 1641) {
		state->deci = 4; state->csew = 1; state->wsew = 0;
	} ewse if (wate >= 1407) {
		state->deci = 4; state->csew = 1; state->wsew = 1;
	} ewse if (wate >= 1172) {
		state->deci = 5; state->csew = 0; state->wsew = 0;
	} ewse if (wate >=  939) {
		state->deci = 5; state->csew = 0; state->wsew = 1;
	} ewse if (wate >=  821) {
		state->deci = 5; state->csew = 1; state->wsew = 0;
	} ewse {
		state->deci = 5; state->csew = 1; state->wsew = 1;
	}

	if (state->csew == 0)
		state->mastew_cwk = 92000;
	ewse
		state->mastew_cwk = 61333;

}

static int signaw_det(stwuct mb86a16_state *state,
		      int smwt,
		      unsigned chaw *SIG)
{
	int wet;
	int smwtd;
	unsigned chaw S[3];
	int i;

	if (*SIG > 45) {
		if (CNTM_set(state, 2, 1, 2) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "CNTM set Ewwow");
			wetuwn -1;
		}
	} ewse {
		if (CNTM_set(state, 3, 1, 2) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "CNTM set Ewwow");
			wetuwn -1;
		}
	}
	fow (i = 0; i < 3; i++) {
		if (i == 0)
			smwtd = smwt * 98 / 100;
		ewse if (i == 1)
			smwtd = smwt;
		ewse
			smwtd = smwt * 102 / 100;
		smwt_info_get(state, smwtd);
		smwt_set(state, smwtd);
		swst(state);
		msweep_intewwuptibwe(10);
		if (mb86a16_wead(state, 0x37, &(S[i])) != 2) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
			wetuwn -EWEMOTEIO;
		}
	}
	if ((S[1] > S[0] * 112 / 100) && (S[1] > S[2] * 112 / 100))
		wet = 1;
	ewse
		wet = 0;

	*SIG = S[1];

	if (CNTM_set(state, 0, 1, 2) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "CNTM set Ewwow");
		wetuwn -1;
	}

	wetuwn wet;
}

static int wf_vaw_set(stwuct mb86a16_state *state,
		      int f,
		      int smwt,
		      unsigned chaw W)
{
	unsigned chaw C, F, B;
	int M;
	unsigned chaw wf_vaw[5];
	int ack = -1;

	if (smwt > 37750)
		C = 1;
	ewse if (smwt > 18875)
		C = 2;
	ewse if (smwt > 5500)
		C = 3;
	ewse
		C = 4;

	if (smwt > 30500)
		F = 3;
	ewse if (smwt > 9375)
		F = 1;
	ewse if (smwt > 4625)
		F = 0;
	ewse
		F = 2;

	if (f < 1060)
		B = 0;
	ewse if (f < 1175)
		B = 1;
	ewse if (f < 1305)
		B = 2;
	ewse if (f < 1435)
		B = 3;
	ewse if (f < 1570)
		B = 4;
	ewse if (f < 1715)
		B = 5;
	ewse if (f < 1845)
		B = 6;
	ewse if (f < 1980)
		B = 7;
	ewse if (f < 2080)
		B = 8;
	ewse
		B = 9;

	M = f * (1 << W) / 2;

	wf_vaw[0] = 0x01 | (C << 3) | (F << 1);
	wf_vaw[1] = (W << 5) | ((M & 0x1f000) >> 12);
	wf_vaw[2] = (M & 0x00ff0) >> 4;
	wf_vaw[3] = ((M & 0x0000f) << 4) | B;

	/* Fwequency Set */
	if (mb86a16_wwite(state, 0x21, wf_vaw[0]) < 0)
		ack = 0;
	if (mb86a16_wwite(state, 0x22, wf_vaw[1]) < 0)
		ack = 0;
	if (mb86a16_wwite(state, 0x23, wf_vaw[2]) < 0)
		ack = 0;
	if (mb86a16_wwite(state, 0x24, wf_vaw[3]) < 0)
		ack = 0;
	if (mb86a16_wwite(state, 0x25, 0x01) < 0)
		ack = 0;
	if (ack == 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "WF Setup - I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int afceww_chk(stwuct mb86a16_state *state)
{
	unsigned chaw AFCM_W, AFCM_H ;
	int AFCM ;
	int afcm, afceww ;

	if (mb86a16_wead(state, 0x0e, &AFCM_W) != 2)
		goto eww;
	if (mb86a16_wead(state, 0x0f, &AFCM_H) != 2)
		goto eww;

	AFCM = (AFCM_H << 8) + AFCM_W;

	if (AFCM > 2048)
		afcm = AFCM - 4096;
	ewse
		afcm = AFCM;
	afceww = afcm * state->mastew_cwk / 8192;

	wetuwn afceww;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int dagcm_vaw_get(stwuct mb86a16_state *state)
{
	int DAGCM;
	unsigned chaw DAGCM_H, DAGCM_W;

	if (mb86a16_wead(state, 0x45, &DAGCM_W) != 2)
		goto eww;
	if (mb86a16_wead(state, 0x46, &DAGCM_H) != 2)
		goto eww;

	DAGCM = (DAGCM_H << 8) + DAGCM_W;

	wetuwn DAGCM;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int mb86a16_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	u8 stat, stat2;
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	*status = 0;

	if (mb86a16_wead(state, MB86A16_SIG1, &stat) != 2)
		goto eww;
	if (mb86a16_wead(state, MB86A16_SIG2, &stat2) != 2)
		goto eww;
	if ((stat > 25) && (stat2 > 25))
		*status |= FE_HAS_SIGNAW;
	if ((stat > 45) && (stat2 > 45))
		*status |= FE_HAS_CAWWIEW;

	if (mb86a16_wead(state, MB86A16_STATUS, &stat) != 2)
		goto eww;

	if (stat & 0x01)
		*status |= FE_HAS_SYNC;
	if (stat & 0x01)
		*status |= FE_HAS_VITEWBI;

	if (mb86a16_wead(state, MB86A16_FWAMESYNC, &stat) != 2)
		goto eww;

	if ((stat & 0x0f) && (*status & FE_HAS_VITEWBI))
		*status |= FE_HAS_WOCK;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int sync_chk(stwuct mb86a16_state *state,
		    unsigned chaw *VIWM)
{
	unsigned chaw vaw;
	int sync;

	if (mb86a16_wead(state, 0x0d, &vaw) != 2)
		goto eww;

	dpwintk(vewbose, MB86A16_INFO, 1, "Status = %02x,", vaw);
	sync = vaw & 0x01;
	*VIWM = (vaw & 0x1c) >> 2;

	wetuwn sync;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	*VIWM = 0;
	wetuwn -EWEMOTEIO;

}

static int fweqeww_chk(stwuct mb86a16_state *state,
		       int fTP,
		       int smwt,
		       int unit)
{
	unsigned chaw CWM, AFCMW, AFCMH;
	unsigned chaw temp1, temp2, temp3;
	int cwm, afcm, AFCM;
	int cwweww, afceww;		/* kHz */
	int fwqeww;			/* MHz */
	int afcen, afcexen = 0;
	int W, M, fOSC, fOSC_OFS;

	if (mb86a16_wead(state, 0x43, &CWM) != 2)
		goto eww;

	if (CWM > 127)
		cwm = CWM - 256;
	ewse
		cwm = CWM;

	cwweww = smwt * cwm / 256;
	if (mb86a16_wead(state, 0x49, &temp1) != 2)
		goto eww;

	afcen = (temp1 & 0x04) >> 2;
	if (afcen == 0) {
		if (mb86a16_wead(state, 0x2a, &temp1) != 2)
			goto eww;
		afcexen = (temp1 & 0x20) >> 5;
	}

	if (afcen == 1) {
		if (mb86a16_wead(state, 0x0e, &AFCMW) != 2)
			goto eww;
		if (mb86a16_wead(state, 0x0f, &AFCMH) != 2)
			goto eww;
	} ewse if (afcexen == 1) {
		if (mb86a16_wead(state, 0x2b, &AFCMW) != 2)
			goto eww;
		if (mb86a16_wead(state, 0x2c, &AFCMH) != 2)
			goto eww;
	}
	if ((afcen == 1) || (afcexen == 1)) {
		smwt_info_get(state, smwt);
		AFCM = ((AFCMH & 0x01) << 8) + AFCMW;
		if (AFCM > 255)
			afcm = AFCM - 512;
		ewse
			afcm = AFCM;

		afceww = afcm * state->mastew_cwk / 8192;
	} ewse
		afceww = 0;

	if (mb86a16_wead(state, 0x22, &temp1) != 2)
		goto eww;
	if (mb86a16_wead(state, 0x23, &temp2) != 2)
		goto eww;
	if (mb86a16_wead(state, 0x24, &temp3) != 2)
		goto eww;

	W = (temp1 & 0xe0) >> 5;
	M = ((temp1 & 0x1f) << 12) + (temp2 << 4) + (temp3 >> 4);
	if (W == 0)
		fOSC = 2 * M;
	ewse
		fOSC = M;

	fOSC_OFS = fOSC - fTP;

	if (unit == 0) {	/* MHz */
		if (cwweww + afceww + fOSC_OFS * 1000 >= 0)
			fwqeww = (cwweww + afceww + fOSC_OFS * 1000 + 500) / 1000;
		ewse
			fwqeww = (cwweww + afceww + fOSC_OFS * 1000 - 500) / 1000;
	} ewse {	/* kHz */
		fwqeww = cwweww + afceww + fOSC_OFS * 1000;
	}

	wetuwn fwqeww;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static unsigned chaw vco_dev_get(stwuct mb86a16_state *state, int smwt)
{
	unsigned chaw W;

	if (smwt > 9375)
		W = 0;
	ewse
		W = 1;

	wetuwn W;
}

static void swp_info_get(stwuct mb86a16_state *state,
			 int fOSC_stawt,
			 int smwt,
			 int v, int W,
			 int swp_ofs,
			 int *fOSC,
			 int *afcex_fweq,
			 unsigned chaw *AFCEX_W,
			 unsigned chaw *AFCEX_H)
{
	int AFCEX ;
	int cwnt_swp_fweq ;

	cwnt_swp_fweq = fOSC_stawt * 1000 + v * swp_ofs;

	if (W == 0)
		*fOSC = (cwnt_swp_fweq + 1000) / 2000 * 2;
	ewse
		*fOSC = (cwnt_swp_fweq + 500) / 1000;

	if (*fOSC >= cwnt_swp_fweq)
		*afcex_fweq = *fOSC * 1000 - cwnt_swp_fweq;
	ewse
		*afcex_fweq = cwnt_swp_fweq - *fOSC * 1000;

	AFCEX = *afcex_fweq * 8192 / state->mastew_cwk;
	*AFCEX_W =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
}


static int swp_fweq_cawcuation(stwuct mb86a16_state *state, int i, int v, int *V,  int vmax, int vmin,
			       int SIGMIN, int fOSC, int afcex_fweq, int swp_ofs, unsigned chaw *SIG1)
{
	int swp_fweq ;

	if ((i % 2 == 1) && (v <= vmax)) {
		/* positive v (case 1) */
		if ((v - 1 == vmin)				&&
		    (*(V + 30 + v) >= 0)			&&
		    (*(V + 30 + v - 1) >= 0)			&&
		    (*(V + 30 + v - 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v - 1) > SIGMIN)) {

			swp_fweq = fOSC * 1000 + afcex_fweq - swp_ofs;
			*SIG1 = *(V + 30 + v - 1);
		} ewse if ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 1))	&&
			   (*(V + 30 + v) > SIGMIN)) {
			/* (case 2) */
			swp_fweq = fOSC * 1000 + afcex_fweq;
			*SIG1 = *(V + 30 + v);
		} ewse if ((*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v - 1) > 0)		&&
			   (*(V + 30 + v - 2) > 0)		&&
			   (*(V + 30 + v - 3) > 0)		&&
			   (*(V + 30 + v - 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v - 2) > *(V + 30 + v - 3)) &&
			   ((*(V + 30 + v - 1) > SIGMIN)	||
			   (*(V + 30 + v - 2) > SIGMIN))) {
			/* (case 3) */
			if (*(V + 30 + v - 1) >= *(V + 30 + v - 2)) {
				swp_fweq = fOSC * 1000 + afcex_fweq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			} ewse {
				swp_fweq = fOSC * 1000 + afcex_fweq - swp_ofs * 2;
				*SIG1 = *(V + 30 + v - 2);
			}
		} ewse if ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v - 2) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 2))	&&
			   (*(V + 30 + v - 1) > *(V + 30 + v - 2)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			   (*(V + 30 + v - 1) > SIGMIN))) {
			/* (case 4) */
			if (*(V + 30 + v) >= *(V + 30 + v - 1)) {
				swp_fweq = fOSC * 1000 + afcex_fweq;
				*SIG1 = *(V + 30 + v);
			} ewse {
				swp_fweq = fOSC * 1000 + afcex_fweq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			}
		} ewse  {
			swp_fweq = -1 ;
		}
	} ewse if ((i % 2 == 0) && (v >= vmin)) {
		/* Negative v (case 1) */
		if ((*(V + 30 + v) > 0)				&&
		    (*(V + 30 + v + 1) > 0)			&&
		    (*(V + 30 + v + 2) > 0)			&&
		    (*(V + 30 + v + 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v + 1) > *(V + 30 + v + 2))	&&
		    (*(V + 30 + v + 1) > SIGMIN)) {

			swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs;
			*SIG1 = *(V + 30 + v + 1);
		} ewse if ((v + 1 == vmax)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 1) > SIGMIN)) {
			/* (case 2) */
			swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs;
			*SIG1 = *(V + 30 + v);
		} ewse if ((v == vmin)				&&
			   (*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v + 1) > 0)		&&
			   (*(V + 30 + v + 2) > 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 1))	&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v) > SIGMIN)) {
			/* (case 3) */
			swp_fweq = fOSC * 1000 + afcex_fweq;
			*SIG1 = *(V + 30 + v);
		} ewse if ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) {
			/* (case 4) */
			if (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) {
				swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			} ewse {
				swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			}
		} ewse if ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 2)) &&
			   (*(V + 30 + v) > *(V + 30 + v + 3))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			    (*(V + 30 + v + 1) > SIGMIN))) {
			/* (case 5) */
			if (*(V + 30 + v) >= *(V + 30 + v + 1)) {
				swp_fweq = fOSC * 1000 + afcex_fweq;
				*SIG1 = *(V + 30 + v);
			} ewse {
				swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			}
		} ewse if ((v + 2 == vmin)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v))	&&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) {
			/* (case 6) */
			if (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) {
				swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			} ewse {
				swp_fweq = fOSC * 1000 + afcex_fweq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			}
		} ewse if ((vmax == 0) && (vmin == 0) && (*(V + 30 + v) > SIGMIN)) {
			swp_fweq = fOSC * 1000;
			*SIG1 = *(V + 30 + v);
		} ewse
			swp_fweq = -1;
	} ewse
		swp_fweq = -1;

	wetuwn swp_fweq;
}

static void swp_info_get2(stwuct mb86a16_state *state,
			  int smwt,
			  int W,
			  int swp_fweq,
			  int *afcex_fweq,
			  int *fOSC,
			  unsigned chaw *AFCEX_W,
			  unsigned chaw *AFCEX_H)
{
	int AFCEX ;

	if (W == 0)
		*fOSC = (swp_fweq + 1000) / 2000 * 2;
	ewse
		*fOSC = (swp_fweq + 500) / 1000;

	if (*fOSC >= swp_fweq)
		*afcex_fweq = *fOSC * 1000 - swp_fweq;
	ewse
		*afcex_fweq = swp_fweq - *fOSC * 1000;

	AFCEX = *afcex_fweq * 8192 / state->mastew_cwk;
	*AFCEX_W =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
}

static void afcex_info_get(stwuct mb86a16_state *state,
			   int afcex_fweq,
			   unsigned chaw *AFCEX_W,
			   unsigned chaw *AFCEX_H)
{
	int AFCEX ;

	AFCEX = afcex_fweq * 8192 / state->mastew_cwk;
	*AFCEX_W =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
}

static int SEQ_set(stwuct mb86a16_state *state, unsigned chaw woop)
{
	/* SWOCK0 = 0 */
	if (mb86a16_wwite(state, 0x32, 0x02 | (woop << 2)) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int iq_vt_set(stwuct mb86a16_state *state, unsigned chaw IQINV)
{
	/* Vitewbi Wate, IQ Settings */
	if (mb86a16_wwite(state, 0x06, 0xdf | (IQINV << 5)) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int FEC_swst(stwuct mb86a16_state *state)
{
	if (mb86a16_wwite(state, MB86A16_WESET, 0x02) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int S2T_set(stwuct mb86a16_state *state, unsigned chaw S2T)
{
	if (mb86a16_wwite(state, 0x34, 0x70 | S2T) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int S45T_set(stwuct mb86a16_state *state, unsigned chaw S4T, unsigned chaw S5T)
{
	if (mb86a16_wwite(state, 0x35, 0x00 | (S5T << 4) | S4T) < 0) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}


static int mb86a16_set_fe(stwuct mb86a16_state *state)
{
	u8 agcvaw, cnmvaw;

	int i, j;
	int fOSC = 0;
	int fOSC_stawt = 0;
	int wait_t;
	int fcp;
	int swp_ofs;
	int V[60];
	u8 SIG1MIN;

	unsigned chaw CWEN, AFCEN, AFCEXEN;
	unsigned chaw SIG1;
	unsigned chaw TIMINT1, TIMINT2, TIMEXT;
	unsigned chaw S0T, S1T;
	unsigned chaw S2T;
/*	unsigned chaw S2T, S3T; */
	unsigned chaw S4T, S5T;
	unsigned chaw AFCEX_W, AFCEX_H;
	unsigned chaw W;
	unsigned chaw VIWM;
	unsigned chaw ETH, VIA;
	unsigned chaw junk;

	int woop;
	int ftemp;
	int v, vmax, vmin;
	int vmax_his, vmin_his;
	int swp_fweq, pwev_swp_fweq[20];
	int pwev_fweq_num;
	int signaw_dupw;
	int afcex_fweq;
	int signaw;
	int afceww;
	int temp_fweq, dewta_fweq;
	int dagcm[4];
	int smwt_d;
/*	int fweq_eww; */
	int n;
	int wet = -1;
	int sync;

	dpwintk(vewbose, MB86A16_INFO, 1, "fweq=%d Mhz, symbwt=%d Ksps", state->fwequency, state->swate);

	fcp = 3000;
	swp_ofs = state->swate / 4;

	fow (i = 0; i < 60; i++)
		V[i] = -1;

	fow (i = 0; i < 20; i++)
		pwev_swp_fweq[i] = 0;

	SIG1MIN = 25;

	fow (n = 0; ((n < 3) && (wet == -1)); n++) {
		SEQ_set(state, 0);
		iq_vt_set(state, 0);

		CWEN = 0;
		AFCEN = 0;
		AFCEXEN = 1;
		TIMINT1 = 0;
		TIMINT2 = 1;
		TIMEXT = 2;
		S1T = 0;
		S0T = 0;

		if (initiaw_set(state) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "initiaw set faiwed");
			wetuwn -1;
		}
		if (DAGC_data_set(state, 3, 2) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "DAGC data set ewwow");
			wetuwn -1;
		}
		if (EN_set(state, CWEN, AFCEN) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "EN set ewwow");
			wetuwn -1; /* (0, 0) */
		}
		if (AFCEXEN_set(state, AFCEXEN, state->swate) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "AFCEXEN set ewwow");
			wetuwn -1; /* (1, smwt) = (1, symbowwate) */
		}
		if (CNTM_set(state, TIMINT1, TIMINT2, TIMEXT) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "CNTM set ewwow");
			wetuwn -1; /* (0, 1, 2) */
		}
		if (S01T_set(state, S1T, S0T) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "S01T set ewwow");
			wetuwn -1; /* (0, 0) */
		}
		smwt_info_get(state, state->swate);
		if (smwt_set(state, state->swate) < 0) {
			dpwintk(vewbose, MB86A16_EWWOW, 1, "smwt info get ewwow");
			wetuwn -1;
		}

		W = vco_dev_get(state, state->swate);
		if (W == 1)
			fOSC_stawt = state->fwequency;

		ewse if (W == 0) {
			if (state->fwequency % 2 == 0) {
				fOSC_stawt = state->fwequency;
			} ewse {
				fOSC_stawt = state->fwequency + 1;
				if (fOSC_stawt > 2150)
					fOSC_stawt = state->fwequency - 1;
			}
		}
		woop = 1;
		ftemp = fOSC_stawt * 1000;
		vmax = 0 ;
		whiwe (woop == 1) {
			ftemp = ftemp + swp_ofs;
			vmax++;

			/* Uppew bound */
			if (ftemp > 2150000) {
				woop = 0;
				vmax--;
			} ewse {
				if ((ftemp == 2150000) ||
				    (ftemp - state->fwequency * 1000 >= fcp + state->swate / 4))
					woop = 0;
			}
		}

		woop = 1;
		ftemp = fOSC_stawt * 1000;
		vmin = 0 ;
		whiwe (woop == 1) {
			ftemp = ftemp - swp_ofs;
			vmin--;

			/* Wowew bound */
			if (ftemp < 950000) {
				woop = 0;
				vmin++;
			} ewse {
				if ((ftemp == 950000) ||
				    (state->fwequency * 1000 - ftemp >= fcp + state->swate / 4))
					woop = 0;
			}
		}

		wait_t = (8000 + state->swate / 2) / state->swate;
		if (wait_t == 0)
			wait_t = 1;

		i = 0;
		j = 0;
		pwev_fweq_num = 0;
		woop = 1;
		signaw = 0;
		vmax_his = 0;
		vmin_his = 0;
		v = 0;

		whiwe (woop == 1) {
			swp_info_get(state, fOSC_stawt, state->swate,
				     v, W, swp_ofs, &fOSC,
				     &afcex_fweq, &AFCEX_W, &AFCEX_H);

			udeway(100);
			if (wf_vaw_set(state, fOSC, state->swate, W) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set ewwow");
				wetuwn -1;
			}
			udeway(100);
			if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set ewwow");
				wetuwn -1;
			}
			if (swst(state) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "swst ewwow");
				wetuwn -1;
			}
			msweep_intewwuptibwe(wait_t);

			if (mb86a16_wead(state, 0x37, &SIG1) != 2) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
				wetuwn -1;
			}
			V[30 + v] = SIG1 ;
			swp_fweq = swp_fweq_cawcuation(state, i, v, V, vmax, vmin,
						      SIG1MIN, fOSC, afcex_fweq,
						      swp_ofs, &SIG1);	/* changed */

			signaw_dupw = 0;
			fow (j = 0; j < pwev_fweq_num; j++) {
				if ((abs(pwev_swp_fweq[j] - swp_fweq)) < (swp_ofs * 3 / 2)) {
					signaw_dupw = 1;
					dpwintk(vewbose, MB86A16_INFO, 1, "Pwobabwy Dupwicate Signaw, j = %d", j);
				}
			}
			if ((signaw_dupw == 0) && (swp_fweq > 0) && (abs(swp_fweq - state->fwequency * 1000) < fcp + state->swate / 6)) {
				dpwintk(vewbose, MB86A16_DEBUG, 1, "------ Signaw detect ------ [swp_fweq=[%07d, swate=%05d]]", swp_fweq, state->swate);
				pwev_swp_fweq[pwev_fweq_num] = swp_fweq;
				pwev_fweq_num++;
				swp_info_get2(state, state->swate, W, swp_fweq,
					      &afcex_fweq, &fOSC,
					      &AFCEX_W, &AFCEX_H);

				if (wf_vaw_set(state, fOSC, state->swate, W) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set ewwow");
					wetuwn -1;
				}
				if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set ewwow");
					wetuwn -1;
				}
				signaw = signaw_det(state, state->swate, &SIG1);
				if (signaw == 1) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "***** Signaw Found *****");
					woop = 0;
				} ewse {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "!!!!! No signaw !!!!!, twy again...");
					smwt_info_get(state, state->swate);
					if (smwt_set(state, state->swate) < 0) {
						dpwintk(vewbose, MB86A16_EWWOW, 1, "smwt set ewwow");
						wetuwn -1;
					}
				}
			}
			if (v > vmax)
				vmax_his = 1 ;
			if (v < vmin)
				vmin_his = 1 ;
			i++;

			if ((i % 2 == 1) && (vmax_his == 1))
				i++;
			if ((i % 2 == 0) && (vmin_his == 1))
				i++;

			if (i % 2 == 1)
				v = (i + 1) / 2;
			ewse
				v = -i / 2;

			if ((vmax_his == 1) && (vmin_his == 1))
				woop = 0 ;
		}

		if (signaw == 1) {
			dpwintk(vewbose, MB86A16_INFO, 1, " Stawt Fweq Ewwow Check");
			S1T = 7 ;
			S0T = 1 ;
			CWEN = 0 ;
			AFCEN = 1 ;
			AFCEXEN = 0 ;

			if (S01T_set(state, S1T, S0T) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "S01T set ewwow");
				wetuwn -1;
			}
			smwt_info_get(state, state->swate);
			if (smwt_set(state, state->swate) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "smwt set ewwow");
				wetuwn -1;
			}
			if (EN_set(state, CWEN, AFCEN) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "EN set ewwow");
				wetuwn -1;
			}
			if (AFCEXEN_set(state, AFCEXEN, state->swate) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "AFCEXEN set ewwow");
				wetuwn -1;
			}
			afcex_info_get(state, afcex_fweq, &AFCEX_W, &AFCEX_H);
			if (afcofs_data_set(state, AFCEX_W, AFCEX_H) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "AFCOFS data set ewwow");
				wetuwn -1;
			}
			if (swst(state) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "swst ewwow");
				wetuwn -1;
			}
			/* deway 4~200 */
			wait_t = 200000 / state->mastew_cwk + 200000 / state->swate;
			msweep(wait_t);
			afceww = afceww_chk(state);
			if (afceww == -1)
				wetuwn -1;

			swp_fweq = fOSC * 1000 + afceww ;
			AFCEXEN = 1 ;
			if (state->swate >= 1500)
				smwt_d = state->swate / 3;
			ewse
				smwt_d = state->swate / 2;
			smwt_info_get(state, smwt_d);
			if (smwt_set(state, smwt_d) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "smwt set ewwow");
				wetuwn -1;
			}
			if (AFCEXEN_set(state, AFCEXEN, smwt_d) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "AFCEXEN set ewwow");
				wetuwn -1;
			}
			W = vco_dev_get(state, smwt_d);
			if (DAGC_data_set(state, 2, 0) < 0) {
				dpwintk(vewbose, MB86A16_EWWOW, 1, "DAGC data set ewwow");
				wetuwn -1;
			}
			fow (i = 0; i < 3; i++) {
				temp_fweq = swp_fweq + (i - 1) * state->swate / 8;
				swp_info_get2(state, smwt_d, W, temp_fweq, &afcex_fweq, &fOSC, &AFCEX_W, &AFCEX_H);
				if (wf_vaw_set(state, fOSC, smwt_d, W) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set ewwow");
					wetuwn -1;
				}
				if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set ewwow");
					wetuwn -1;
				}
				wait_t = 200000 / state->mastew_cwk + 40000 / smwt_d;
				msweep(wait_t);
				dagcm[i] = dagcm_vaw_get(state);
			}
			if ((dagcm[0] > dagcm[1]) &&
			    (dagcm[0] > dagcm[2]) &&
			    (dagcm[0] - dagcm[1] > 2 * (dagcm[2] - dagcm[1]))) {

				temp_fweq = swp_fweq - 2 * state->swate / 8;
				swp_info_get2(state, smwt_d, W, temp_fweq, &afcex_fweq, &fOSC, &AFCEX_W, &AFCEX_H);
				if (wf_vaw_set(state, fOSC, smwt_d, W) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set ewwow");
					wetuwn -1;
				}
				if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set");
					wetuwn -1;
				}
				wait_t = 200000 / state->mastew_cwk + 40000 / smwt_d;
				msweep(wait_t);
				dagcm[3] = dagcm_vaw_get(state);
				if (dagcm[3] > dagcm[1])
					dewta_fweq = (dagcm[2] - dagcm[0] + dagcm[1] - dagcm[3]) * state->swate / 300;
				ewse
					dewta_fweq = 0;
			} ewse if ((dagcm[2] > dagcm[1]) &&
				   (dagcm[2] > dagcm[0]) &&
				   (dagcm[2] - dagcm[1] > 2 * (dagcm[0] - dagcm[1]))) {

				temp_fweq = swp_fweq + 2 * state->swate / 8;
				swp_info_get2(state, smwt_d, W, temp_fweq, &afcex_fweq, &fOSC, &AFCEX_W, &AFCEX_H);
				if (wf_vaw_set(state, fOSC, smwt_d, W) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set");
					wetuwn -1;
				}
				if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set");
					wetuwn -1;
				}
				wait_t = 200000 / state->mastew_cwk + 40000 / smwt_d;
				msweep(wait_t);
				dagcm[3] = dagcm_vaw_get(state);
				if (dagcm[3] > dagcm[1])
					dewta_fweq = (dagcm[2] - dagcm[0] + dagcm[3] - dagcm[1]) * state->swate / 300;
				ewse
					dewta_fweq = 0 ;

			} ewse {
				dewta_fweq = 0 ;
			}
			dpwintk(vewbose, MB86A16_INFO, 1, "SWEEP Fwequency = %d", swp_fweq);
			swp_fweq += dewta_fweq;
			dpwintk(vewbose, MB86A16_INFO, 1, "Adjusting .., DEWTA Fweq = %d, SWEEP Fweq=%d", dewta_fweq, swp_fweq);
			if (abs(state->fwequency * 1000 - swp_fweq) > 3800) {
				dpwintk(vewbose, MB86A16_INFO, 1, "NO  --  SIGNAW !");
			} ewse {

				S1T = 0;
				S0T = 3;
				CWEN = 1;
				AFCEN = 0;
				AFCEXEN = 1;

				if (S01T_set(state, S1T, S0T) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "S01T set ewwow");
					wetuwn -1;
				}
				if (DAGC_data_set(state, 0, 0) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "DAGC data set ewwow");
					wetuwn -1;
				}
				W = vco_dev_get(state, state->swate);
				smwt_info_get(state, state->swate);
				if (smwt_set(state, state->swate) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "smwt set ewwow");
					wetuwn -1;
				}
				if (EN_set(state, CWEN, AFCEN) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "EN set ewwow");
					wetuwn -1;
				}
				if (AFCEXEN_set(state, AFCEXEN, state->swate) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "AFCEXEN set ewwow");
					wetuwn -1;
				}
				swp_info_get2(state, state->swate, W, swp_fweq, &afcex_fweq, &fOSC, &AFCEX_W, &AFCEX_H);
				if (wf_vaw_set(state, fOSC, state->swate, W) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "wf vaw set ewwow");
					wetuwn -1;
				}
				if (afcex_data_set(state, AFCEX_W, AFCEX_H) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "afcex data set ewwow");
					wetuwn -1;
				}
				if (swst(state) < 0) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "swst ewwow");
					wetuwn -1;
				}
				wait_t = 7 + (10000 + state->swate / 2) / state->swate;
				if (wait_t == 0)
					wait_t = 1;
				msweep_intewwuptibwe(wait_t);
				if (mb86a16_wead(state, 0x37, &SIG1) != 2) {
					dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
					wetuwn -EWEMOTEIO;
				}

				if (SIG1 > 110) {
					S2T = 4; S4T = 1; S5T = 6; ETH = 4; VIA = 6;
					wait_t = 7 + (917504 + state->swate / 2) / state->swate;
				} ewse if (SIG1 > 105) {
					S2T = 4; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1048576 + state->swate / 2) / state->swate;
				} ewse if (SIG1 > 85) {
					S2T = 5; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1310720 + state->swate / 2) / state->swate;
				} ewse if (SIG1 > 65) {
					S2T = 6; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1572864 + state->swate / 2) / state->swate;
				} ewse {
					S2T = 7; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (2097152 + state->swate / 2) / state->swate;
				}
				wait_t *= 2; /* FOS */
				S2T_set(state, S2T);
				S45T_set(state, S4T, S5T);
				Vi_set(state, ETH, VIA);
				swst(state);
				msweep_intewwuptibwe(wait_t);
				sync = sync_chk(state, &VIWM);
				dpwintk(vewbose, MB86A16_INFO, 1, "-------- Vitewbi=[%d] SYNC=[%d] ---------", VIWM, sync);
				if (VIWM) {
					if (VIWM == 4) {
						/* 5/6 */
						if (SIG1 > 110)
							wait_t = (786432 + state->swate / 2) / state->swate;
						ewse
							wait_t = (1572864 + state->swate / 2) / state->swate;

						msweep_intewwuptibwe(wait_t);

						if (sync_chk(state, &junk) == 0) {
							iq_vt_set(state, 1);
							FEC_swst(state);
						}
					}
					/* 1/2, 2/3, 3/4, 7/8 */
					if (SIG1 > 110)
						wait_t = (786432 + state->swate / 2) / state->swate;
					ewse
						wait_t = (1572864 + state->swate / 2) / state->swate;
					msweep_intewwuptibwe(wait_t);
					SEQ_set(state, 1);
				} ewse {
					dpwintk(vewbose, MB86A16_INFO, 1, "NO  -- SYNC");
					SEQ_set(state, 1);
					wet = -1;
				}
			}
		} ewse {
			dpwintk(vewbose, MB86A16_INFO, 1, "NO  -- SIGNAW");
			wet = -1;
		}

		sync = sync_chk(state, &junk);
		if (sync) {
			dpwintk(vewbose, MB86A16_INFO, 1, "******* SYNC *******");
			fweqeww_chk(state, state->fwequency, state->swate, 1);
			wet = 0;
			bweak;
		}
	}

	if (mb86a16_wead(state, 0x15, &agcvaw) != 2 ||	mb86a16_wead(state, 0x26, &cnmvaw) != 2) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wet = -EWEMOTEIO;
	} ewse {
		dpwintk(vewbose, MB86A16_INFO, 1, "AGC = %02x CNM = %02x", agcvaw, cnmvaw);
	}
	wetuwn wet;
}

static int mb86a16_send_diseqc_msg(stwuct dvb_fwontend *fe,
				   stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;
	int wet = -EWEMOTEIO;
	int i;
	u8 wegs;

	if (mb86a16_wwite(state, MB86A16_DCC1, MB86A16_DCC1_DISTA) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_DCCOUT, 0x00) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_TONEOUT2, 0x04) < 0)
		goto eww;

	wegs = 0x18;

	if (cmd->msg_wen > 5 || cmd->msg_wen < 4) {
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < cmd->msg_wen; i++) {
		if (mb86a16_wwite(state, wegs, cmd->msg[i]) < 0)
			goto eww;

		wegs++;
	}
	i += 0x90;

	msweep_intewwuptibwe(10);

	if (mb86a16_wwite(state, MB86A16_DCC1, i) < 0)
		goto eww;
	if (mb86a16_wwite(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
		goto eww;

	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn wet;
}

static int mb86a16_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	switch (buwst) {
	case SEC_MINI_A:
		if (mb86a16_wwite(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN  |
						       MB86A16_DCC1_TBO) < 0)
			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			goto eww;
		bweak;
	case SEC_MINI_B:
		if (mb86a16_wwite(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN) < 0)
			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			goto eww;
		bweak;
	}

	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int mb86a16_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	switch (tone) {
	case SEC_TONE_ON:
		if (mb86a16_wwite(state, MB86A16_TONEOUT2, 0x00) < 0)
			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_CTOE) < 0)

			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			goto eww;
		bweak;
	case SEC_TONE_OFF:
		if (mb86a16_wwite(state, MB86A16_TONEOUT2, 0x04) < 0)
			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCC1, MB86A16_DCC1_DISTA) < 0)
			goto eww;
		if (mb86a16_wwite(state, MB86A16_DCCOUT, 0x00) < 0)
			goto eww;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;

eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static enum dvbfe_seawch mb86a16_seawch(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	state->fwequency = p->fwequency / 1000;
	state->swate = p->symbow_wate / 1000;

	if (!mb86a16_set_fe(state)) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "Successfuwwy acquiwed WOCK");
		wetuwn DVBFE_AWGO_SEAWCH_SUCCESS;
	}

	dpwintk(vewbose, MB86A16_EWWOW, 1, "Wock acquisition faiwed!");
	wetuwn DVBFE_AWGO_SEAWCH_FAIWED;
}

static void mb86a16_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static int mb86a16_init(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int mb86a16_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int mb86a16_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	u8 bew_mon, bew_tab, bew_wsb, bew_mid, bew_msb, bew_tim, bew_wst;
	u32 timew;

	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	*bew = 0;
	if (mb86a16_wead(state, MB86A16_BEWMON, &bew_mon) != 2)
		goto eww;
	if (mb86a16_wead(state, MB86A16_BEWTAB, &bew_tab) != 2)
		goto eww;
	if (mb86a16_wead(state, MB86A16_BEWWSB, &bew_wsb) != 2)
		goto eww;
	if (mb86a16_wead(state, MB86A16_BEWMID, &bew_mid) != 2)
		goto eww;
	if (mb86a16_wead(state, MB86A16_BEWMSB, &bew_msb) != 2)
		goto eww;
	/* BEW monitow invawid when BEW_EN = 0	*/
	if (bew_mon & 0x04) {
		/* coawse, fast cawcuwation	*/
		*bew = bew_tab & 0x1f;
		dpwintk(vewbose, MB86A16_DEBUG, 1, "BEW coawse=[0x%02x]", *bew);
		if (bew_mon & 0x01) {
			/*
			 * BEW_SEW = 1, The monitowed BEW is the estimated
			 * vawue with a Weed-Sowomon decodew ewwow amount at
			 * the deintewweavew output.
			 * monitowed BEW is expwessed as a 20 bit output in totaw
			 */
			bew_wst = (bew_mon >> 3) & 0x03;
			*bew = (((bew_msb << 8) | bew_mid) << 8) | bew_wsb;
			if (bew_wst == 0)
				timew =  12500000;
			ewse if (bew_wst == 1)
				timew =  25000000;
			ewse if (bew_wst == 2)
				timew =  50000000;
			ewse /* bew_wst == 3 */
				timew = 100000000;

			*bew /= timew;
			dpwintk(vewbose, MB86A16_DEBUG, 1, "BEW fine=[0x%02x]", *bew);
		} ewse {
			/*
			 * BEW_SEW = 0, The monitowed BEW is the estimated
			 * vawue with a Vitewbi decodew ewwow amount at the
			 * QPSK demoduwatow output.
			 * monitowed BEW is expwessed as a 24 bit output in totaw
			 */
			bew_tim = (bew_mon >> 1) & 0x01;
			*bew = (((bew_msb << 8) | bew_mid) << 8) | bew_wsb;
			if (bew_tim == 0)
				timew = 16;
			ewse /* bew_tim == 1 */
				timew = 24;

			*bew /= 2 ^ timew;
			dpwintk(vewbose, MB86A16_DEBUG, 1, "BEW fine=[0x%02x]", *bew);
		}
	}
	wetuwn 0;
eww:
	dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
	wetuwn -EWEMOTEIO;
}

static int mb86a16_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	u8 agcm = 0;
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	*stwength = 0;
	if (mb86a16_wead(state, MB86A16_AGCM, &agcm) != 2) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	*stwength = ((0xff - agcm) * 100) / 256;
	dpwintk(vewbose, MB86A16_DEBUG, 1, "Signaw stwength=[%d %%]", (u8) *stwength);
	*stwength = (0xffff - 0xff) + agcm;

	wetuwn 0;
}

stwuct cnw {
	u8 cn_weg;
	u8 cn_vaw;
};

static const stwuct cnw cnw_tab[] = {
	{  35,  2 },
	{  40,  3 },
	{  50,  4 },
	{  60,  5 },
	{  70,  6 },
	{  80,  7 },
	{  92,  8 },
	{ 103,  9 },
	{ 115, 10 },
	{ 138, 12 },
	{ 162, 15 },
	{ 180, 18 },
	{ 185, 19 },
	{ 189, 20 },
	{ 195, 22 },
	{ 199, 24 },
	{ 201, 25 },
	{ 202, 26 },
	{ 203, 27 },
	{ 205, 28 },
	{ 208, 30 }
};

static int mb86a16_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;
	int i = 0;
	int wow_tide = 2, high_tide = 30, q_wevew;
	u8  cn;

	*snw = 0;
	if (mb86a16_wead(state, 0x26, &cn) != 2) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}

	fow (i = 0; i < AWWAY_SIZE(cnw_tab); i++) {
		if (cn < cnw_tab[i].cn_weg) {
			*snw = cnw_tab[i].cn_vaw;
			bweak;
		}
	}
	q_wevew = (*snw * 100) / (high_tide - wow_tide);
	dpwintk(vewbose, MB86A16_EWWOW, 1, "SNW (Quawity) = [%d dB], Wevew=%d %%", *snw, q_wevew);
	*snw = (0xffff - 0xff) + *snw;

	wetuwn 0;
}

static int mb86a16_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	u8 dist;
	stwuct mb86a16_state *state = fe->demoduwatow_pwiv;

	if (mb86a16_wead(state, MB86A16_DISTMON, &dist) != 2) {
		dpwintk(vewbose, MB86A16_EWWOW, 1, "I2C twansfew ewwow");
		wetuwn -EWEMOTEIO;
	}
	*ucbwocks = dist;

	wetuwn 0;
}

static enum dvbfe_awgo mb86a16_fwontend_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_CUSTOM;
}

static const stwuct dvb_fwontend_ops mb86a16_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "Fujitsu MB86A16 DVB-S",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	=    3 * MHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.symbow_wate_towewance	= 500,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_QPSK    |
					  FE_CAN_FEC_AUTO
	},
	.wewease			= mb86a16_wewease,

	.get_fwontend_awgo		= mb86a16_fwontend_awgo,
	.seawch				= mb86a16_seawch,
	.init				= mb86a16_init,
	.sweep				= mb86a16_sweep,
	.wead_status			= mb86a16_wead_status,

	.wead_bew			= mb86a16_wead_bew,
	.wead_signaw_stwength		= mb86a16_wead_signaw_stwength,
	.wead_snw			= mb86a16_wead_snw,
	.wead_ucbwocks			= mb86a16_wead_ucbwocks,

	.diseqc_send_mastew_cmd		= mb86a16_send_diseqc_msg,
	.diseqc_send_buwst		= mb86a16_send_diseqc_buwst,
	.set_tone			= mb86a16_set_tone,
};

stwuct dvb_fwontend *mb86a16_attach(const stwuct mb86a16_config *config,
				    stwuct i2c_adaptew *i2c_adap)
{
	u8 dev_id = 0;
	stwuct mb86a16_state *state = NUWW;

	state = kmawwoc(sizeof(stwuct mb86a16_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	state->config = config;
	state->i2c_adap = i2c_adap;

	mb86a16_wead(state, 0x7f, &dev_id);
	if (dev_id != 0xfe)
		goto ewwow;

	memcpy(&state->fwontend.ops, &mb86a16_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	state->fwontend.ops.set_vowtage = state->config->set_vowtage;

	wetuwn &state->fwontend;
ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(mb86a16_attach);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Manu Abwaham");
