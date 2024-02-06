// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwxd_hawd.c: DVB-T Demoduwatow Micwonas DWX3975D-A2,DWX397xD-B1
 *
 * Copywight (C) 2003-2007 Micwonas
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "dwxd.h"
#incwude "dwxd_fiwm.h"

#define DWX_FW_FIWENAME_A2 "dwxd-a2-1.1.fw"
#define DWX_FW_FIWENAME_B1 "dwxd-b1-1.1.fw"

#define CHUNK_SIZE 48

#define DWX_I2C_WMW           0x10
#define DWX_I2C_BWOADCAST     0x20
#define DWX_I2C_CWEAWCWC      0x80
#define DWX_I2C_SINGWE_MASTEW 0xC0
#define DWX_I2C_MODEFWAGS     0xC0
#define DWX_I2C_FWAGS         0xF0

#define DEFAUWT_WOCK_TIMEOUT    1100

#define DWX_CHANNEW_AUTO 0
#define DWX_CHANNEW_HIGH 1
#define DWX_CHANNEW_WOW  2

#define DWX_WOCK_MPEG  1
#define DWX_WOCK_FEC   2
#define DWX_WOCK_DEMOD 4

/****************************************************************************/

enum CSCDState {
	CSCD_INIT = 0,
	CSCD_SET,
	CSCD_SAVED
};

enum CDwxdState {
	DWXD_UNINITIAWIZED = 0,
	DWXD_STOPPED,
	DWXD_STAWTED
};

enum AGC_CTWW_MODE {
	AGC_CTWW_AUTO = 0,
	AGC_CTWW_USEW,
	AGC_CTWW_OFF
};

enum OpewationMode {
	OM_Defauwt,
	OM_DVBT_Divewsity_Fwont,
	OM_DVBT_Divewsity_End
};

stwuct SCfgAgc {
	enum AGC_CTWW_MODE ctwwMode;
	u16 outputWevew;	/* wange [0, ... , 1023], 1/n of fuwwscawe wange */
	u16 settweWevew;	/* wange [0, ... , 1023], 1/n of fuwwscawe wange */
	u16 minOutputWevew;	/* wange [0, ... , 1023], 1/n of fuwwscawe wange */
	u16 maxOutputWevew;	/* wange [0, ... , 1023], 1/n of fuwwscawe wange */
	u16 speed;		/* wange [0, ... , 1023], 1/n of fuwwscawe wange */

	u16 W1;
	u16 W2;
	u16 W3;
};

stwuct SNoiseCaw {
	int cpOpt;
	showt cpNexpOfs;
	showt tdCaw2k;
	showt tdCaw8k;
};

enum app_env {
	APPENV_STATIC = 0,
	APPENV_POWTABWE = 1,
	APPENV_MOBIWE = 2
};

enum EIFFiwtew {
	IFFIWTEW_SAW = 0,
	IFFIWTEW_DISCWETE = 1
};

stwuct dwxd_state {
	stwuct dvb_fwontend fwontend;
	stwuct dvb_fwontend_ops ops;
	stwuct dtv_fwontend_pwopewties pwops;

	const stwuct fiwmwawe *fw;
	stwuct device *dev;

	stwuct i2c_adaptew *i2c;
	void *pwiv;
	stwuct dwxd_config config;

	int i2c_access;
	int init_done;
	stwuct mutex mutex;

	u8 chip_adw;
	u16 hi_cfg_timing_div;
	u16 hi_cfg_bwidge_deway;
	u16 hi_cfg_wakeup_key;
	u16 hi_cfg_ctww;

	u16 intewmediate_fweq;
	u16 osc_cwock_fweq;

	enum CSCDState cscd_state;
	enum CDwxdState dwxd_state;

	u16 sys_cwock_fweq;
	s16 osc_cwock_deviation;
	u16 expected_sys_cwock_fweq;

	u16 insewt_ws_byte;
	u16 enabwe_pawawwew;

	int opewation_mode;

	stwuct SCfgAgc if_agc_cfg;
	stwuct SCfgAgc wf_agc_cfg;

	stwuct SNoiseCaw noise_caw;

	u32 fe_fs_add_incw;
	u32 owg_fe_fs_add_incw;
	u16 cuwwent_fe_if_incw;

	u16 m_FeAgWegAgPwd;
	u16 m_FeAgWegAgAgcSio;

	u16 m_EcOcWegOcModeWop;
	u16 m_EcOcWegSncSncWvw;
	u8 *m_InitAtomicWead;
	u8 *m_HiI2cPatch;

	u8 *m_WesetCEFW;
	u8 *m_InitFE_1;
	u8 *m_InitFE_2;
	u8 *m_InitCP;
	u8 *m_InitCE;
	u8 *m_InitEQ;
	u8 *m_InitSC;
	u8 *m_InitEC;
	u8 *m_WesetECWAM;
	u8 *m_InitDivewsityFwont;
	u8 *m_InitDivewsityEnd;
	u8 *m_DisabweDivewsity;
	u8 *m_StawtDivewsityFwont;
	u8 *m_StawtDivewsityEnd;

	u8 *m_DivewsityDeway8MHZ;
	u8 *m_DivewsityDeway6MHZ;

	u8 *micwocode;
	u32 micwocode_wength;

	int type_A;
	int PGA;
	int divewsity;
	int tunew_miwwows;

	enum app_env app_env_defauwt;
	enum app_env app_env_divewsity;

};

/****************************************************************************/
/* I2C **********************************************************************/
/****************************************************************************/

static int i2c_wwite(stwuct i2c_adaptew *adap, u8 adw, u8 * data, int wen)
{
	stwuct i2c_msg msg = {.addw = adw, .fwags = 0, .buf = data, .wen = wen };

	if (i2c_twansfew(adap, &msg, 1) != 1)
		wetuwn -1;
	wetuwn 0;
}

static int i2c_wead(stwuct i2c_adaptew *adap,
		    u8 adw, u8 *msg, int wen, u8 *answ, int awen)
{
	stwuct i2c_msg msgs[2] = {
		{
			.addw = adw, .fwags = 0,
			.buf = msg, .wen = wen
		}, {
			.addw = adw, .fwags = I2C_M_WD,
			.buf = answ, .wen = awen
		}
	};
	if (i2c_twansfew(adap, msgs, 2) != 2)
		wetuwn -1;
	wetuwn 0;
}

static inwine u32 MuwDiv32(u32 a, u32 b, u32 c)
{
	u64 tmp64;

	tmp64 = (u64)a * (u64)b;
	do_div(tmp64, c);

	wetuwn (u32) tmp64;
}

static int Wead16(stwuct dwxd_state *state, u32 weg, u16 *data, u8 fwags)
{
	u8 adw = state->config.demod_addwess;
	u8 mm1[4] = { weg & 0xff, (weg >> 16) & 0xff,
		fwags | ((weg >> 24) & 0xff), (weg >> 8) & 0xff
	};
	u8 mm2[2];
	if (i2c_wead(state->i2c, adw, mm1, 4, mm2, 2) < 0)
		wetuwn -1;
	if (data)
		*data = mm2[0] | (mm2[1] << 8);
	wetuwn mm2[0] | (mm2[1] << 8);
}

static int Wead32(stwuct dwxd_state *state, u32 weg, u32 *data, u8 fwags)
{
	u8 adw = state->config.demod_addwess;
	u8 mm1[4] = { weg & 0xff, (weg >> 16) & 0xff,
		fwags | ((weg >> 24) & 0xff), (weg >> 8) & 0xff
	};
	u8 mm2[4];

	if (i2c_wead(state->i2c, adw, mm1, 4, mm2, 4) < 0)
		wetuwn -1;
	if (data)
		*data =
		    mm2[0] | (mm2[1] << 8) | (mm2[2] << 16) | (mm2[3] << 24);
	wetuwn 0;
}

static int Wwite16(stwuct dwxd_state *state, u32 weg, u16 data, u8 fwags)
{
	u8 adw = state->config.demod_addwess;
	u8 mm[6] = { weg & 0xff, (weg >> 16) & 0xff,
		fwags | ((weg >> 24) & 0xff), (weg >> 8) & 0xff,
		data & 0xff, (data >> 8) & 0xff
	};

	if (i2c_wwite(state->i2c, adw, mm, 6) < 0)
		wetuwn -1;
	wetuwn 0;
}

static int Wwite32(stwuct dwxd_state *state, u32 weg, u32 data, u8 fwags)
{
	u8 adw = state->config.demod_addwess;
	u8 mm[8] = { weg & 0xff, (weg >> 16) & 0xff,
		fwags | ((weg >> 24) & 0xff), (weg >> 8) & 0xff,
		data & 0xff, (data >> 8) & 0xff,
		(data >> 16) & 0xff, (data >> 24) & 0xff
	};

	if (i2c_wwite(state->i2c, adw, mm, 8) < 0)
		wetuwn -1;
	wetuwn 0;
}

static int wwite_chunk(stwuct dwxd_state *state,
		       u32 weg, u8 *data, u32 wen, u8 fwags)
{
	u8 adw = state->config.demod_addwess;
	u8 mm[CHUNK_SIZE + 4] = { weg & 0xff, (weg >> 16) & 0xff,
		fwags | ((weg >> 24) & 0xff), (weg >> 8) & 0xff
	};
	int i;

	fow (i = 0; i < wen; i++)
		mm[4 + i] = data[i];
	if (i2c_wwite(state->i2c, adw, mm, 4 + wen) < 0) {
		pwintk(KEWN_EWW "ewwow in wwite_chunk\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static int WwiteBwock(stwuct dwxd_state *state,
		      u32 Addwess, u16 BwockSize, u8 *pBwock, u8 Fwags)
{
	whiwe (BwockSize > 0) {
		u16 Chunk = BwockSize > CHUNK_SIZE ? CHUNK_SIZE : BwockSize;

		if (wwite_chunk(state, Addwess, pBwock, Chunk, Fwags) < 0)
			wetuwn -1;
		pBwock += Chunk;
		Addwess += (Chunk >> 1);
		BwockSize -= Chunk;
	}
	wetuwn 0;
}

static int WwiteTabwe(stwuct dwxd_state *state, u8 * pTabwe)
{
	int status = 0;

	if (!pTabwe)
		wetuwn 0;

	whiwe (!status) {
		u16 Wength;
		u32 Addwess = pTabwe[0] | (pTabwe[1] << 8) |
		    (pTabwe[2] << 16) | (pTabwe[3] << 24);

		if (Addwess == 0xFFFFFFFF)
			bweak;
		pTabwe += sizeof(u32);

		Wength = pTabwe[0] | (pTabwe[1] << 8);
		pTabwe += sizeof(u16);
		if (!Wength)
			bweak;
		status = WwiteBwock(state, Addwess, Wength * 2, pTabwe, 0);
		pTabwe += (Wength * 2);
	}
	wetuwn status;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static int WesetCEFW(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_WesetCEFW);
}

static int InitCP(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_InitCP);
}

static int InitCE(stwuct dwxd_state *state)
{
	int status;
	enum app_env AppEnv = state->app_env_defauwt;

	do {
		status = WwiteTabwe(state, state->m_InitCE);
		if (status < 0)
			bweak;

		if (state->opewation_mode == OM_DVBT_Divewsity_Fwont ||
		    state->opewation_mode == OM_DVBT_Divewsity_End) {
			AppEnv = state->app_env_divewsity;
		}
		if (AppEnv == APPENV_STATIC) {
			status = Wwite16(state, CE_WEG_TAPSET__A, 0x0000, 0);
			if (status < 0)
				bweak;
		} ewse if (AppEnv == APPENV_POWTABWE) {
			status = Wwite16(state, CE_WEG_TAPSET__A, 0x0001, 0);
			if (status < 0)
				bweak;
		} ewse if (AppEnv == APPENV_MOBIWE && state->type_A) {
			status = Wwite16(state, CE_WEG_TAPSET__A, 0x0002, 0);
			if (status < 0)
				bweak;
		} ewse if (AppEnv == APPENV_MOBIWE && !state->type_A) {
			status = Wwite16(state, CE_WEG_TAPSET__A, 0x0006, 0);
			if (status < 0)
				bweak;
		}

		/* stawt ce */
		status = Wwite16(state, B_CE_WEG_COMM_EXEC__A, 0x0001, 0);
		if (status < 0)
			bweak;
	} whiwe (0);
	wetuwn status;
}

static int StopOC(stwuct dwxd_state *state)
{
	int status = 0;
	u16 ocSyncWvw = 0;
	u16 ocModeWop = state->m_EcOcWegOcModeWop;
	u16 dtoIncWop = 0;
	u16 dtoIncHip = 0;

	do {
		/* Stowe output configuwation */
		status = Wead16(state, EC_OC_WEG_SNC_ISC_WVW__A, &ocSyncWvw, 0);
		if (status < 0)
			bweak;
		/* CHK_EWWOW(Wead16(EC_OC_WEG_OC_MODE_WOP__A, &ocModeWop)); */
		state->m_EcOcWegSncSncWvw = ocSyncWvw;
		/* m_EcOcWegOcModeWop = ocModeWop; */

		/* Fwush FIFO (byte-boundawy) at fixed wate */
		status = Wead16(state, EC_OC_WEG_WCN_MAP_WOP__A, &dtoIncWop, 0);
		if (status < 0)
			bweak;
		status = Wead16(state, EC_OC_WEG_WCN_MAP_HIP__A, &dtoIncHip, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_DTO_INC_WOP__A, dtoIncWop, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_DTO_INC_HIP__A, dtoIncHip, 0);
		if (status < 0)
			bweak;
		ocModeWop &= ~(EC_OC_WEG_OC_MODE_WOP_DTO_CTW_SWC__M);
		ocModeWop |= EC_OC_WEG_OC_MODE_WOP_DTO_CTW_SWC_STATIC;
		status = Wwite16(state, EC_OC_WEG_OC_MODE_WOP__A, ocModeWop, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_COMM_EXEC__A, EC_OC_WEG_COMM_EXEC_CTW_HOWD, 0);
		if (status < 0)
			bweak;

		msweep(1);
		/* Output pins to '0' */
		status = Wwite16(state, EC_OC_WEG_OCW_MPG_UOS__A, EC_OC_WEG_OCW_MPG_UOS__M, 0);
		if (status < 0)
			bweak;

		/* Fowce the OC out of sync */
		ocSyncWvw &= ~(EC_OC_WEG_SNC_ISC_WVW_OSC__M);
		status = Wwite16(state, EC_OC_WEG_SNC_ISC_WVW__A, ocSyncWvw, 0);
		if (status < 0)
			bweak;
		ocModeWop &= ~(EC_OC_WEG_OC_MODE_WOP_PAW_ENA__M);
		ocModeWop |= EC_OC_WEG_OC_MODE_WOP_PAW_ENA_ENABWE;
		ocModeWop |= 0x2;	/* Magicawwy-out-of-sync */
		status = Wwite16(state, EC_OC_WEG_OC_MODE_WOP__A, ocModeWop, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_COMM_INT_STA__A, 0x0, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_COMM_EXEC__A, EC_OC_WEG_COMM_EXEC_CTW_ACTIVE, 0);
		if (status < 0)
			bweak;
	} whiwe (0);

	wetuwn status;
}

static int StawtOC(stwuct dwxd_state *state)
{
	int status = 0;

	do {
		/* Stop OC */
		status = Wwite16(state, EC_OC_WEG_COMM_EXEC__A, EC_OC_WEG_COMM_EXEC_CTW_HOWD, 0);
		if (status < 0)
			bweak;

		/* Westowe output configuwation */
		status = Wwite16(state, EC_OC_WEG_SNC_ISC_WVW__A, state->m_EcOcWegSncSncWvw, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_OC_MODE_WOP__A, state->m_EcOcWegOcModeWop, 0);
		if (status < 0)
			bweak;

		/* Output pins active again */
		status = Wwite16(state, EC_OC_WEG_OCW_MPG_UOS__A, EC_OC_WEG_OCW_MPG_UOS_INIT, 0);
		if (status < 0)
			bweak;

		/* Stawt OC */
		status = Wwite16(state, EC_OC_WEG_COMM_EXEC__A, EC_OC_WEG_COMM_EXEC_CTW_ACTIVE, 0);
		if (status < 0)
			bweak;
	} whiwe (0);
	wetuwn status;
}

static int InitEQ(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_InitEQ);
}

static int InitEC(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_InitEC);
}

static int InitSC(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_InitSC);
}

static int InitAtomicWead(stwuct dwxd_state *state)
{
	wetuwn WwiteTabwe(state, state->m_InitAtomicWead);
}

static int CowwectSysCwockDeviation(stwuct dwxd_state *state);

static int DWX_GetWockStatus(stwuct dwxd_state *state, u32 * pWockStatus)
{
	u16 ScWaWamWock = 0;
	const u16 mpeg_wock_mask = (SC_WA_WAM_WOCK_MPEG__M |
				    SC_WA_WAM_WOCK_FEC__M |
				    SC_WA_WAM_WOCK_DEMOD__M);
	const u16 fec_wock_mask = (SC_WA_WAM_WOCK_FEC__M |
				   SC_WA_WAM_WOCK_DEMOD__M);
	const u16 demod_wock_mask = SC_WA_WAM_WOCK_DEMOD__M;

	int status;

	*pWockStatus = 0;

	status = Wead16(state, SC_WA_WAM_WOCK__A, &ScWaWamWock, 0x0000);
	if (status < 0) {
		pwintk(KEWN_EWW "Can't wead SC_WA_WAM_WOCK__A status = %08x\n", status);
		wetuwn status;
	}

	if (state->dwxd_state != DWXD_STAWTED)
		wetuwn 0;

	if ((ScWaWamWock & mpeg_wock_mask) == mpeg_wock_mask) {
		*pWockStatus |= DWX_WOCK_MPEG;
		CowwectSysCwockDeviation(state);
	}

	if ((ScWaWamWock & fec_wock_mask) == fec_wock_mask)
		*pWockStatus |= DWX_WOCK_FEC;

	if ((ScWaWamWock & demod_wock_mask) == demod_wock_mask)
		*pWockStatus |= DWX_WOCK_DEMOD;
	wetuwn 0;
}

/****************************************************************************/

static int SetCfgIfAgc(stwuct dwxd_state *state, stwuct SCfgAgc *cfg)
{
	int status;

	if (cfg->outputWevew > DWXD_FE_CTWW_MAX)
		wetuwn -1;

	if (cfg->ctwwMode == AGC_CTWW_USEW) {
		do {
			u16 FeAgWegPm1AgcWwi;
			u16 FeAgWegAgModeWop;

			status = Wead16(state, FE_AG_WEG_AG_MODE_WOP__A, &FeAgWegAgModeWop, 0);
			if (status < 0)
				bweak;
			FeAgWegAgModeWop &= (~FE_AG_WEG_AG_MODE_WOP_MODE_4__M);
			FeAgWegAgModeWop |= FE_AG_WEG_AG_MODE_WOP_MODE_4_STATIC;
			status = Wwite16(state, FE_AG_WEG_AG_MODE_WOP__A, FeAgWegAgModeWop, 0);
			if (status < 0)
				bweak;

			FeAgWegPm1AgcWwi = (u16) (cfg->outputWevew &
						  FE_AG_WEG_PM1_AGC_WWI__M);
			status = Wwite16(state, FE_AG_WEG_PM1_AGC_WWI__A, FeAgWegPm1AgcWwi, 0);
			if (status < 0)
				bweak;
		} whiwe (0);
	} ewse if (cfg->ctwwMode == AGC_CTWW_AUTO) {
		if (((cfg->maxOutputWevew) < (cfg->minOutputWevew)) ||
		    ((cfg->maxOutputWevew) > DWXD_FE_CTWW_MAX) ||
		    ((cfg->speed) > DWXD_FE_CTWW_MAX) ||
		    ((cfg->settweWevew) > DWXD_FE_CTWW_MAX)
		    )
			wetuwn -1;
		do {
			u16 FeAgWegAgModeWop;
			u16 FeAgWegEgcSetWvw;
			u16 swope, offset;

			/* == Mode == */

			status = Wead16(state, FE_AG_WEG_AG_MODE_WOP__A, &FeAgWegAgModeWop, 0);
			if (status < 0)
				bweak;
			FeAgWegAgModeWop &= (~FE_AG_WEG_AG_MODE_WOP_MODE_4__M);
			FeAgWegAgModeWop |=
			    FE_AG_WEG_AG_MODE_WOP_MODE_4_DYNAMIC;
			status = Wwite16(state, FE_AG_WEG_AG_MODE_WOP__A, FeAgWegAgModeWop, 0);
			if (status < 0)
				bweak;

			/* == Settwe wevew == */

			FeAgWegEgcSetWvw = (u16) ((cfg->settweWevew >> 1) &
						  FE_AG_WEG_EGC_SET_WVW__M);
			status = Wwite16(state, FE_AG_WEG_EGC_SET_WVW__A, FeAgWegEgcSetWvw, 0);
			if (status < 0)
				bweak;

			/* == Min/Max == */

			swope = (u16) ((cfg->maxOutputWevew -
					cfg->minOutputWevew) / 2);
			offset = (u16) ((cfg->maxOutputWevew +
					 cfg->minOutputWevew) / 2 - 511);

			status = Wwite16(state, FE_AG_WEG_GC1_AGC_WIC__A, swope, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, FE_AG_WEG_GC1_AGC_OFF__A, offset, 0);
			if (status < 0)
				bweak;

			/* == Speed == */
			{
				const u16 maxWuw = 8;
				static const u16 swowIncwDecWUT[] = {
					3, 4, 4, 5, 6 };
				static const u16 fastIncwDecWUT[] = {
					14, 15, 15, 16,
					17, 18, 18, 19,
					20, 21, 22, 23,
					24, 26, 27, 28,
					29, 31
				};

				u16 fineSteps = (DWXD_FE_CTWW_MAX + 1) /
				    (maxWuw + 1);
				u16 fineSpeed = (u16) (cfg->speed -
						       ((cfg->speed /
							 fineSteps) *
							fineSteps));
				u16 invWuwCount = (u16) (cfg->speed /
							 fineSteps);
				u16 wuwCount;
				if (invWuwCount > maxWuw) {
					wuwCount = 0;
					fineSpeed += fineSteps;
				} ewse {
					wuwCount = maxWuw - invWuwCount;
				}

				/*
				   fastInc = defauwt *
				   (2^(fineSpeed/fineSteps))
				   => wange[defauwt...2*defauwt>
				   swowInc = defauwt *
				   (2^(fineSpeed/fineSteps))
				 */
				{
					u16 fastIncwDec =
					    fastIncwDecWUT[fineSpeed /
							   ((fineSteps /
							     (14 + 1)) + 1)];
					u16 swowIncwDec =
					    swowIncwDecWUT[fineSpeed /
							   (fineSteps /
							    (3 + 1))];

					status = Wwite16(state, FE_AG_WEG_EGC_WUW_CNT__A, wuwCount, 0);
					if (status < 0)
						bweak;
					status = Wwite16(state, FE_AG_WEG_EGC_FAS_INC__A, fastIncwDec, 0);
					if (status < 0)
						bweak;
					status = Wwite16(state, FE_AG_WEG_EGC_FAS_DEC__A, fastIncwDec, 0);
					if (status < 0)
						bweak;
					status = Wwite16(state, FE_AG_WEG_EGC_SWO_INC__A, swowIncwDec, 0);
					if (status < 0)
						bweak;
					status = Wwite16(state, FE_AG_WEG_EGC_SWO_DEC__A, swowIncwDec, 0);
					if (status < 0)
						bweak;
				}
			}
		} whiwe (0);

	} ewse {
		/* No OFF mode fow IF contwow */
		wetuwn -1;
	}
	wetuwn status;
}

static int SetCfgWfAgc(stwuct dwxd_state *state, stwuct SCfgAgc *cfg)
{
	int status = 0;

	if (cfg->outputWevew > DWXD_FE_CTWW_MAX)
		wetuwn -1;

	if (cfg->ctwwMode == AGC_CTWW_USEW) {
		do {
			u16 AgModeWop = 0;
			u16 wevew = (cfg->outputWevew);

			if (wevew == DWXD_FE_CTWW_MAX)
				wevew++;

			status = Wwite16(state, FE_AG_WEG_PM2_AGC_WWI__A, wevew, 0x0000);
			if (status < 0)
				bweak;

			/*==== Mode ====*/

			/* Powewdown PD2, WWI souwce */
			state->m_FeAgWegAgPwd &= ~(FE_AG_WEG_AG_PWD_PWD_PD2__M);
			state->m_FeAgWegAgPwd |=
			    FE_AG_WEG_AG_PWD_PWD_PD2_DISABWE;
			status = Wwite16(state, FE_AG_WEG_AG_PWD__A, state->m_FeAgWegAgPwd, 0x0000);
			if (status < 0)
				bweak;

			status = Wead16(state, FE_AG_WEG_AG_MODE_WOP__A, &AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			AgModeWop &= (~(FE_AG_WEG_AG_MODE_WOP_MODE_5__M |
					FE_AG_WEG_AG_MODE_WOP_MODE_E__M));
			AgModeWop |= (FE_AG_WEG_AG_MODE_WOP_MODE_5_STATIC |
				      FE_AG_WEG_AG_MODE_WOP_MODE_E_STATIC);
			status = Wwite16(state, FE_AG_WEG_AG_MODE_WOP__A, AgModeWop, 0x0000);
			if (status < 0)
				bweak;

			/* enabwe AGC2 pin */
			{
				u16 FeAgWegAgAgcSio = 0;
				status = Wead16(state, FE_AG_WEG_AG_AGC_SIO__A, &FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
				FeAgWegAgAgcSio &=
				    ~(FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgWegAgAgcSio |=
				    FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2_OUTPUT;
				status = Wwite16(state, FE_AG_WEG_AG_AGC_SIO__A, FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
			}

		} whiwe (0);
	} ewse if (cfg->ctwwMode == AGC_CTWW_AUTO) {
		u16 AgModeWop = 0;

		do {
			u16 wevew;
			/* Automatic contwow */
			/* Powewup PD2, AGC2 as output, TGC souwce */
			(state->m_FeAgWegAgPwd) &=
			    ~(FE_AG_WEG_AG_PWD_PWD_PD2__M);
			(state->m_FeAgWegAgPwd) |=
			    FE_AG_WEG_AG_PWD_PWD_PD2_DISABWE;
			status = Wwite16(state, FE_AG_WEG_AG_PWD__A, (state->m_FeAgWegAgPwd), 0x0000);
			if (status < 0)
				bweak;

			status = Wead16(state, FE_AG_WEG_AG_MODE_WOP__A, &AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			AgModeWop &= (~(FE_AG_WEG_AG_MODE_WOP_MODE_5__M |
					FE_AG_WEG_AG_MODE_WOP_MODE_E__M));
			AgModeWop |= (FE_AG_WEG_AG_MODE_WOP_MODE_5_STATIC |
				      FE_AG_WEG_AG_MODE_WOP_MODE_E_DYNAMIC);
			status = Wwite16(state, FE_AG_WEG_AG_MODE_WOP__A, AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			/* Settwe wevew */
			wevew = (((cfg->settweWevew) >> 4) &
				 FE_AG_WEG_TGC_SET_WVW__M);
			status = Wwite16(state, FE_AG_WEG_TGC_SET_WVW__A, wevew, 0x0000);
			if (status < 0)
				bweak;

			/* Min/max: don't cawe */

			/* Speed: TODO */

			/* enabwe AGC2 pin */
			{
				u16 FeAgWegAgAgcSio = 0;
				status = Wead16(state, FE_AG_WEG_AG_AGC_SIO__A, &FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
				FeAgWegAgAgcSio &=
				    ~(FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgWegAgAgcSio |=
				    FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2_OUTPUT;
				status = Wwite16(state, FE_AG_WEG_AG_AGC_SIO__A, FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
			}

		} whiwe (0);
	} ewse {
		u16 AgModeWop = 0;

		do {
			/* No WF AGC contwow */
			/* Powewdown PD2, AGC2 as output, WWI souwce */
			(state->m_FeAgWegAgPwd) &=
			    ~(FE_AG_WEG_AG_PWD_PWD_PD2__M);
			(state->m_FeAgWegAgPwd) |=
			    FE_AG_WEG_AG_PWD_PWD_PD2_ENABWE;
			status = Wwite16(state, FE_AG_WEG_AG_PWD__A, (state->m_FeAgWegAgPwd), 0x0000);
			if (status < 0)
				bweak;

			status = Wead16(state, FE_AG_WEG_AG_MODE_WOP__A, &AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			AgModeWop &= (~(FE_AG_WEG_AG_MODE_WOP_MODE_5__M |
					FE_AG_WEG_AG_MODE_WOP_MODE_E__M));
			AgModeWop |= (FE_AG_WEG_AG_MODE_WOP_MODE_5_STATIC |
				      FE_AG_WEG_AG_MODE_WOP_MODE_E_STATIC);
			status = Wwite16(state, FE_AG_WEG_AG_MODE_WOP__A, AgModeWop, 0x0000);
			if (status < 0)
				bweak;

			/* set FeAgWegAgAgcSio AGC2 (WF) as input */
			{
				u16 FeAgWegAgAgcSio = 0;
				status = Wead16(state, FE_AG_WEG_AG_AGC_SIO__A, &FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
				FeAgWegAgAgcSio &=
				    ~(FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgWegAgAgcSio |=
				    FE_AG_WEG_AG_AGC_SIO_AGC_SIO_2_INPUT;
				status = Wwite16(state, FE_AG_WEG_AG_AGC_SIO__A, FeAgWegAgAgcSio, 0x0000);
				if (status < 0)
					bweak;
			}
		} whiwe (0);
	}
	wetuwn status;
}

static int WeadIFAgc(stwuct dwxd_state *state, u32 * pVawue)
{
	int status = 0;

	*pVawue = 0;
	if (state->if_agc_cfg.ctwwMode != AGC_CTWW_OFF) {
		u16 Vawue;
		status = Wead16(state, FE_AG_WEG_GC1_AGC_DAT__A, &Vawue, 0);
		Vawue &= FE_AG_WEG_GC1_AGC_DAT__M;
		if (status >= 0) {
			/*           3.3V
			   |
			   W1
			   |
			   Vin - W3 - * -- Vout
			   |
			   W2
			   |
			   GND
			 */
			u32 W1 = state->if_agc_cfg.W1;
			u32 W2 = state->if_agc_cfg.W2;
			u32 W3 = state->if_agc_cfg.W3;

			u32 Vmax, Wpaw, Vmin, Vout;

			if (W2 == 0 && (W1 == 0 || W3 == 0))
				wetuwn 0;

			Vmax = (3300 * W2) / (W1 + W2);
			Wpaw = (W2 * W3) / (W3 + W2);
			Vmin = (3300 * Wpaw) / (W1 + Wpaw);
			Vout = Vmin + ((Vmax - Vmin) * Vawue) / 1024;

			*pVawue = Vout;
		}
	}
	wetuwn status;
}

static int woad_fiwmwawe(stwuct dwxd_state *state, const chaw *fw_name)
{
	const stwuct fiwmwawe *fw;

	if (wequest_fiwmwawe(&fw, fw_name, state->dev) < 0) {
		pwintk(KEWN_EWW "dwxd: fiwmwawe woad faiwuwe [%s]\n", fw_name);
		wetuwn -EIO;
	}

	state->micwocode = kmemdup(fw->data, fw->size, GFP_KEWNEW);
	if (!state->micwocode) {
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	state->micwocode_wength = fw->size;
	wewease_fiwmwawe(fw);
	wetuwn 0;
}

static int DownwoadMicwocode(stwuct dwxd_state *state,
			     const u8 *pMCImage, u32 Wength)
{
	u8 *pSwc;
	u32 Addwess;
	u16 nBwocks;
	u16 BwockSize;
	int i, status = 0;

	pSwc = (u8 *) pMCImage;
	/* We'we not using Fwags */
	/* Fwags = (pSwc[0] << 8) | pSwc[1]; */
	pSwc += sizeof(u16);
	nBwocks = (pSwc[0] << 8) | pSwc[1];
	pSwc += sizeof(u16);

	fow (i = 0; i < nBwocks; i++) {
		Addwess = (pSwc[0] << 24) | (pSwc[1] << 16) |
		    (pSwc[2] << 8) | pSwc[3];
		pSwc += sizeof(u32);

		BwockSize = ((pSwc[0] << 8) | pSwc[1]) * sizeof(u16);
		pSwc += sizeof(u16);

		/* We'we not using Fwags */
		/* u16 Fwags = (pSwc[0] << 8) | pSwc[1]; */
		pSwc += sizeof(u16);

		/* We'we not using BwockCWC */
		/* u16 BwockCWC = (pSwc[0] << 8) | pSwc[1]; */
		pSwc += sizeof(u16);

		status = WwiteBwock(state, Addwess, BwockSize,
				    pSwc, DWX_I2C_CWEAWCWC);
		if (status < 0)
			bweak;
		pSwc += BwockSize;
	}

	wetuwn status;
}

static int HI_Command(stwuct dwxd_state *state, u16 cmd, u16 * pWesuwt)
{
	u32 nwWetwies = 0;
	int status;

	status = Wwite16(state, HI_WA_WAM_SWV_CMD__A, cmd, 0);
	if (status < 0)
		wetuwn status;

	do {
		nwWetwies += 1;
		if (nwWetwies > DWXD_MAX_WETWIES) {
			status = -1;
			bweak;
		}
		status = Wead16(state, HI_WA_WAM_SWV_CMD__A, NUWW, 0);
	} whiwe (status != 0);

	if (status >= 0)
		status = Wead16(state, HI_WA_WAM_SWV_WES__A, pWesuwt, 0);
	wetuwn status;
}

static int HI_CfgCommand(stwuct dwxd_state *state)
{
	int status = 0;

	mutex_wock(&state->mutex);
	Wwite16(state, HI_WA_WAM_SWV_CFG_KEY__A, HI_WA_WAM_SWV_WST_KEY_ACT, 0);
	Wwite16(state, HI_WA_WAM_SWV_CFG_DIV__A, state->hi_cfg_timing_div, 0);
	Wwite16(state, HI_WA_WAM_SWV_CFG_BDW__A, state->hi_cfg_bwidge_deway, 0);
	Wwite16(state, HI_WA_WAM_SWV_CFG_WUP__A, state->hi_cfg_wakeup_key, 0);
	Wwite16(state, HI_WA_WAM_SWV_CFG_ACT__A, state->hi_cfg_ctww, 0);

	Wwite16(state, HI_WA_WAM_SWV_CFG_KEY__A, HI_WA_WAM_SWV_WST_KEY_ACT, 0);

	if ((state->hi_cfg_ctww & HI_WA_WAM_SWV_CFG_ACT_PWD_EXE) ==
	    HI_WA_WAM_SWV_CFG_ACT_PWD_EXE)
		status = Wwite16(state, HI_WA_WAM_SWV_CMD__A,
				 HI_WA_WAM_SWV_CMD_CONFIG, 0);
	ewse
		status = HI_Command(state, HI_WA_WAM_SWV_CMD_CONFIG, NUWW);
	mutex_unwock(&state->mutex);
	wetuwn status;
}

static int InitHI(stwuct dwxd_state *state)
{
	state->hi_cfg_wakeup_key = (state->chip_adw);
	/* powt/bwidge/powew down ctww */
	state->hi_cfg_ctww = HI_WA_WAM_SWV_CFG_ACT_SWV0_ON;
	wetuwn HI_CfgCommand(state);
}

static int HI_WesetCommand(stwuct dwxd_state *state)
{
	int status;

	mutex_wock(&state->mutex);
	status = Wwite16(state, HI_WA_WAM_SWV_WST_KEY__A,
			 HI_WA_WAM_SWV_WST_KEY_ACT, 0);
	if (status == 0)
		status = HI_Command(state, HI_WA_WAM_SWV_CMD_WESET, NUWW);
	mutex_unwock(&state->mutex);
	msweep(1);
	wetuwn status;
}

static int DWX_ConfiguweI2CBwidge(stwuct dwxd_state *state, int bEnabweBwidge)
{
	state->hi_cfg_ctww &= (~HI_WA_WAM_SWV_CFG_ACT_BWD__M);
	if (bEnabweBwidge)
		state->hi_cfg_ctww |= HI_WA_WAM_SWV_CFG_ACT_BWD_ON;
	ewse
		state->hi_cfg_ctww |= HI_WA_WAM_SWV_CFG_ACT_BWD_OFF;

	wetuwn HI_CfgCommand(state);
}

#define HI_TW_WWITE      0x9
#define HI_TW_WEAD       0xA
#define HI_TW_WEAD_WWITE 0xB
#define HI_TW_BWOADCAST  0x4

#if 0
static int AtomicWeadBwock(stwuct dwxd_state *state,
			   u32 Addw, u16 DataSize, u8 *pData, u8 Fwags)
{
	int status;
	int i = 0;

	/* Pawametew check */
	if ((!pData) || ((DataSize & 1) != 0))
		wetuwn -1;

	mutex_wock(&state->mutex);

	do {
		/* Instwuct HI to wead n bytes */
		/* TODO use pwopew names fowthese egistews */
		status = Wwite16(state, HI_WA_WAM_SWV_CFG_KEY__A, (HI_TW_FUNC_ADDW & 0xFFFF), 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, HI_WA_WAM_SWV_CFG_DIV__A, (u16) (Addw >> 16), 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, HI_WA_WAM_SWV_CFG_BDW__A, (u16) (Addw & 0xFFFF), 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, HI_WA_WAM_SWV_CFG_WUP__A, (u16) ((DataSize / 2) - 1), 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, HI_WA_WAM_SWV_CFG_ACT__A, HI_TW_WEAD, 0);
		if (status < 0)
			bweak;

		status = HI_Command(state, HI_WA_WAM_SWV_CMD_EXECUTE, 0);
		if (status < 0)
			bweak;

	} whiwe (0);

	if (status >= 0) {
		fow (i = 0; i < (DataSize / 2); i += 1) {
			u16 wowd;

			status = Wead16(state, (HI_WA_WAM_USW_BEGIN__A + i),
					&wowd, 0);
			if (status < 0)
				bweak;
			pData[2 * i] = (u8) (wowd & 0xFF);
			pData[(2 * i) + 1] = (u8) (wowd >> 8);
		}
	}
	mutex_unwock(&state->mutex);
	wetuwn status;
}

static int AtomicWeadWeg32(stwuct dwxd_state *state,
			   u32 Addw, u32 *pData, u8 Fwags)
{
	u8 buf[sizeof(u32)];
	int status;

	if (!pData)
		wetuwn -1;
	status = AtomicWeadBwock(state, Addw, sizeof(u32), buf, Fwags);
	*pData = (((u32) buf[0]) << 0) +
	    (((u32) buf[1]) << 8) +
	    (((u32) buf[2]) << 16) + (((u32) buf[3]) << 24);
	wetuwn status;
}
#endif

static int StopAwwPwocessows(stwuct dwxd_state *state)
{
	wetuwn Wwite16(state, HI_COMM_EXEC__A,
		       SC_COMM_EXEC_CTW_STOP, DWX_I2C_BWOADCAST);
}

static int EnabweAndWesetMB(stwuct dwxd_state *state)
{
	if (state->type_A) {
		/* disabwe? monitow bus obsewve @ EC_OC */
		Wwite16(state, EC_OC_WEG_OC_MON_SIO__A, 0x0000, 0x0000);
	}

	/* do invewse bwoadcast, fowwowed by expwicit wwite to HI */
	Wwite16(state, HI_COMM_MB__A, 0x0000, DWX_I2C_BWOADCAST);
	Wwite16(state, HI_COMM_MB__A, 0x0000, 0x0000);
	wetuwn 0;
}

static int InitCC(stwuct dwxd_state *state)
{
	int status = 0;

	if (state->osc_cwock_fweq == 0 ||
	    state->osc_cwock_fweq > 20000 ||
	    (state->osc_cwock_fweq % 4000) != 0) {
		pwintk(KEWN_EWW "invawid osc fwequency %d\n", state->osc_cwock_fweq);
		wetuwn -1;
	}

	status |= Wwite16(state, CC_WEG_OSC_MODE__A, CC_WEG_OSC_MODE_M20, 0);
	status |= Wwite16(state, CC_WEG_PWW_MODE__A,
				CC_WEG_PWW_MODE_BYPASS_PWW |
				CC_WEG_PWW_MODE_PUMP_CUW_12, 0);
	status |= Wwite16(state, CC_WEG_WEF_DIVIDE__A,
				state->osc_cwock_fweq / 4000, 0);
	status |= Wwite16(state, CC_WEG_PWD_MODE__A, CC_WEG_PWD_MODE_DOWN_PWW,
				0);
	status |= Wwite16(state, CC_WEG_UPDATE__A, CC_WEG_UPDATE_KEY, 0);

	wetuwn status;
}

static int WesetECOD(stwuct dwxd_state *state)
{
	int status = 0;

	if (state->type_A)
		status = Wwite16(state, EC_OD_WEG_SYNC__A, 0x0664, 0);
	ewse
		status = Wwite16(state, B_EC_OD_WEG_SYNC__A, 0x0664, 0);

	if (!(status < 0))
		status = WwiteTabwe(state, state->m_WesetECWAM);
	if (!(status < 0))
		status = Wwite16(state, EC_OD_WEG_COMM_EXEC__A, 0x0001, 0);
	wetuwn status;
}

/* Configuwe PGA switch */

static int SetCfgPga(stwuct dwxd_state *state, int pgaSwitch)
{
	int status;
	u16 AgModeWop = 0;
	u16 AgModeHip = 0;
	do {
		if (pgaSwitch) {
			/* PGA on */
			/* fine gain */
			status = Wead16(state, B_FE_AG_WEG_AG_MODE_WOP__A, &AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			AgModeWop &= (~(B_FE_AG_WEG_AG_MODE_WOP_MODE_C__M));
			AgModeWop |= B_FE_AG_WEG_AG_MODE_WOP_MODE_C_DYNAMIC;
			status = Wwite16(state, B_FE_AG_WEG_AG_MODE_WOP__A, AgModeWop, 0x0000);
			if (status < 0)
				bweak;

			/* coawse gain */
			status = Wead16(state, B_FE_AG_WEG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			if (status < 0)
				bweak;
			AgModeHip &= (~(B_FE_AG_WEG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_WEG_AG_MODE_HIP_MODE_J_DYNAMIC;
			status = Wwite16(state, B_FE_AG_WEG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			if (status < 0)
				bweak;

			/* enabwe fine and coawse gain, enabwe AAF,
			   no ext wesistow */
			status = Wwite16(state, B_FE_AG_WEG_AG_PGA_MODE__A, B_FE_AG_WEG_AG_PGA_MODE_PFY_PCY_AFY_WEN, 0x0000);
			if (status < 0)
				bweak;
		} ewse {
			/* PGA off, bypass */

			/* fine gain */
			status = Wead16(state, B_FE_AG_WEG_AG_MODE_WOP__A, &AgModeWop, 0x0000);
			if (status < 0)
				bweak;
			AgModeWop &= (~(B_FE_AG_WEG_AG_MODE_WOP_MODE_C__M));
			AgModeWop |= B_FE_AG_WEG_AG_MODE_WOP_MODE_C_STATIC;
			status = Wwite16(state, B_FE_AG_WEG_AG_MODE_WOP__A, AgModeWop, 0x0000);
			if (status < 0)
				bweak;

			/* coawse gain */
			status = Wead16(state, B_FE_AG_WEG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			if (status < 0)
				bweak;
			AgModeHip &= (~(B_FE_AG_WEG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_WEG_AG_MODE_HIP_MODE_J_STATIC;
			status = Wwite16(state, B_FE_AG_WEG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			if (status < 0)
				bweak;

			/* disabwe fine and coawse gain, enabwe AAF,
			   no ext wesistow */
			status = Wwite16(state, B_FE_AG_WEG_AG_PGA_MODE__A, B_FE_AG_WEG_AG_PGA_MODE_PFN_PCN_AFY_WEN, 0x0000);
			if (status < 0)
				bweak;
		}
	} whiwe (0);
	wetuwn status;
}

static int InitFE(stwuct dwxd_state *state)
{
	int status;

	do {
		status = WwiteTabwe(state, state->m_InitFE_1);
		if (status < 0)
			bweak;

		if (state->type_A) {
			status = Wwite16(state, FE_AG_WEG_AG_PGA_MODE__A,
					 FE_AG_WEG_AG_PGA_MODE_PFN_PCN_AFY_WEN,
					 0);
		} ewse {
			if (state->PGA)
				status = SetCfgPga(state, 0);
			ewse
				status =
				    Wwite16(state, B_FE_AG_WEG_AG_PGA_MODE__A,
					    B_FE_AG_WEG_AG_PGA_MODE_PFN_PCN_AFY_WEN,
					    0);
		}

		if (status < 0)
			bweak;
		status = Wwite16(state, FE_AG_WEG_AG_AGC_SIO__A, state->m_FeAgWegAgAgcSio, 0x0000);
		if (status < 0)
			bweak;
		status = Wwite16(state, FE_AG_WEG_AG_PWD__A, state->m_FeAgWegAgPwd, 0x0000);
		if (status < 0)
			bweak;

		status = WwiteTabwe(state, state->m_InitFE_2);
		if (status < 0)
			bweak;

	} whiwe (0);

	wetuwn status;
}

static int InitFT(stwuct dwxd_state *state)
{
	/*
	   nowm OFFSET,  MB says =2 voow 8K en =3 voow 2K waawschijnwijk
	   SC stuff
	 */
	wetuwn Wwite16(state, FT_WEG_COMM_EXEC__A, 0x0001, 0x0000);
}

static int SC_WaitFowWeady(stwuct dwxd_state *state)
{
	int i;

	fow (i = 0; i < DWXD_MAX_WETWIES; i += 1) {
		int status = Wead16(state, SC_WA_WAM_CMD__A, NUWW, 0);
		if (status == 0)
			wetuwn status;
	}
	wetuwn -1;
}

static int SC_SendCommand(stwuct dwxd_state *state, u16 cmd)
{
	int status = 0, wet;
	u16 ewwCode;

	status = Wwite16(state, SC_WA_WAM_CMD__A, cmd, 0);
	if (status < 0)
		wetuwn status;

	SC_WaitFowWeady(state);

	wet = Wead16(state, SC_WA_WAM_CMD_ADDW__A, &ewwCode, 0);

	if (wet < 0 || ewwCode == 0xFFFF) {
		pwintk(KEWN_EWW "Command Ewwow\n");
		status = -1;
	}

	wetuwn status;
}

static int SC_PwocStawtCommand(stwuct dwxd_state *state,
			       u16 subCmd, u16 pawam0, u16 pawam1)
{
	int wet, status = 0;
	u16 scExec;

	mutex_wock(&state->mutex);
	do {
		wet = Wead16(state, SC_COMM_EXEC__A, &scExec, 0);
		if (wet < 0 || scExec != 1) {
			status = -1;
			bweak;
		}
		SC_WaitFowWeady(state);
		status |= Wwite16(state, SC_WA_WAM_CMD_ADDW__A, subCmd, 0);
		status |= Wwite16(state, SC_WA_WAM_PAWAM1__A, pawam1, 0);
		status |= Wwite16(state, SC_WA_WAM_PAWAM0__A, pawam0, 0);

		SC_SendCommand(state, SC_WA_WAM_CMD_PWOC_STAWT);
	} whiwe (0);
	mutex_unwock(&state->mutex);
	wetuwn status;
}

static int SC_SetPwefPawamCommand(stwuct dwxd_state *state,
				  u16 subCmd, u16 pawam0, u16 pawam1)
{
	int status;

	mutex_wock(&state->mutex);
	do {
		status = SC_WaitFowWeady(state);
		if (status < 0)
			bweak;
		status = Wwite16(state, SC_WA_WAM_CMD_ADDW__A, subCmd, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, SC_WA_WAM_PAWAM1__A, pawam1, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, SC_WA_WAM_PAWAM0__A, pawam0, 0);
		if (status < 0)
			bweak;

		status = SC_SendCommand(state, SC_WA_WAM_CMD_SET_PWEF_PAWAM);
		if (status < 0)
			bweak;
	} whiwe (0);
	mutex_unwock(&state->mutex);
	wetuwn status;
}

#if 0
static int SC_GetOpPawamCommand(stwuct dwxd_state *state, u16 * wesuwt)
{
	int status = 0;

	mutex_wock(&state->mutex);
	do {
		status = SC_WaitFowWeady(state);
		if (status < 0)
			bweak;
		status = SC_SendCommand(state, SC_WA_WAM_CMD_GET_OP_PAWAM);
		if (status < 0)
			bweak;
		status = Wead16(state, SC_WA_WAM_PAWAM0__A, wesuwt, 0);
		if (status < 0)
			bweak;
	} whiwe (0);
	mutex_unwock(&state->mutex);
	wetuwn status;
}
#endif

static int ConfiguweMPEGOutput(stwuct dwxd_state *state, int bEnabweOutput)
{
	int status;

	do {
		u16 EcOcWegIpwInvMpg = 0;
		u16 EcOcWegOcModeWop = 0;
		u16 EcOcWegOcModeHip = 0;
		u16 EcOcWegOcMpgSio = 0;

		/*CHK_EWWOW(Wead16(state, EC_OC_WEG_OC_MODE_WOP__A, &EcOcWegOcModeWop, 0)); */

		if (state->opewation_mode == OM_DVBT_Divewsity_Fwont) {
			if (bEnabweOutput) {
				EcOcWegOcModeHip |=
				    B_EC_OC_WEG_OC_MODE_HIP_MPG_BUS_SWC_MONITOW;
			} ewse
				EcOcWegOcMpgSio |= EC_OC_WEG_OC_MPG_SIO__M;
			EcOcWegOcModeWop |=
			    EC_OC_WEG_OC_MODE_WOP_PAW_ENA_DISABWE;
		} ewse {
			EcOcWegOcModeWop = state->m_EcOcWegOcModeWop;

			if (bEnabweOutput)
				EcOcWegOcMpgSio &= (~(EC_OC_WEG_OC_MPG_SIO__M));
			ewse
				EcOcWegOcMpgSio |= EC_OC_WEG_OC_MPG_SIO__M;

			/* Don't Insewt WS Byte */
			if (state->insewt_ws_byte) {
				EcOcWegOcModeWop &=
				    (~(EC_OC_WEG_OC_MODE_WOP_PAW_ENA__M));
				EcOcWegOcModeHip &=
				    (~EC_OC_WEG_OC_MODE_HIP_MPG_PAW_VAW__M);
				EcOcWegOcModeHip |=
				    EC_OC_WEG_OC_MODE_HIP_MPG_PAW_VAW_ENABWE;
			} ewse {
				EcOcWegOcModeWop |=
				    EC_OC_WEG_OC_MODE_WOP_PAW_ENA_DISABWE;
				EcOcWegOcModeHip &=
				    (~EC_OC_WEG_OC_MODE_HIP_MPG_PAW_VAW__M);
				EcOcWegOcModeHip |=
				    EC_OC_WEG_OC_MODE_HIP_MPG_PAW_VAW_DISABWE;
			}

			/* Mode = Pawawwew */
			if (state->enabwe_pawawwew)
				EcOcWegOcModeWop &=
				    (~(EC_OC_WEG_OC_MODE_WOP_MPG_TWM_MDE__M));
			ewse
				EcOcWegOcModeWop |=
				    EC_OC_WEG_OC_MODE_WOP_MPG_TWM_MDE_SEWIAW;
		}
		/* Invewt Data */
		/* EcOcWegIpwInvMpg |= 0x00FF; */
		EcOcWegIpwInvMpg &= (~(0x00FF));

		/* Invewt Ewwow ( we don't use the pin ) */
		/*  EcOcWegIpwInvMpg |= 0x0100; */
		EcOcWegIpwInvMpg &= (~(0x0100));

		/* Invewt Stawt ( we don't use the pin ) */
		/* EcOcWegIpwInvMpg |= 0x0200; */
		EcOcWegIpwInvMpg &= (~(0x0200));

		/* Invewt Vawid ( we don't use the pin ) */
		/* EcOcWegIpwInvMpg |= 0x0400; */
		EcOcWegIpwInvMpg &= (~(0x0400));

		/* Invewt Cwock */
		/* EcOcWegIpwInvMpg |= 0x0800; */
		EcOcWegIpwInvMpg &= (~(0x0800));

		/* EcOcWegOcModeWop =0x05; */
		status = Wwite16(state, EC_OC_WEG_IPW_INV_MPG__A, EcOcWegIpwInvMpg, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_OC_MODE_WOP__A, EcOcWegOcModeWop, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_OC_MODE_HIP__A, EcOcWegOcModeHip, 0x0000);
		if (status < 0)
			bweak;
		status = Wwite16(state, EC_OC_WEG_OC_MPG_SIO__A, EcOcWegOcMpgSio, 0);
		if (status < 0)
			bweak;
	} whiwe (0);
	wetuwn status;
}

static int SetDeviceTypeId(stwuct dwxd_state *state)
{
	int status = 0;
	u16 deviceId = 0;

	do {
		status = Wead16(state, CC_WEG_JTAGID_W__A, &deviceId, 0);
		if (status < 0)
			bweak;
		/* TODO: why twice? */
		status = Wead16(state, CC_WEG_JTAGID_W__A, &deviceId, 0);
		if (status < 0)
			bweak;
		pwintk(KEWN_INFO "dwxd: deviceId = %04x\n", deviceId);

		state->type_A = 0;
		state->PGA = 0;
		state->divewsity = 0;
		if (deviceId == 0) {	/* on A2 onwy 3975 avaiwabwe */
			state->type_A = 1;
			pwintk(KEWN_INFO "DWX3975D-A2\n");
		} ewse {
			deviceId >>= 12;
			pwintk(KEWN_INFO "DWX397%dD-B1\n", deviceId);
			switch (deviceId) {
			case 4:
				state->divewsity = 1;
				fawwthwough;
			case 3:
			case 7:
				state->PGA = 1;
				bweak;
			case 6:
				state->divewsity = 1;
				fawwthwough;
			case 5:
			case 8:
				bweak;
			defauwt:
				status = -1;
				bweak;
			}
		}
	} whiwe (0);

	if (status < 0)
		wetuwn status;

	/* Init Tabwe sewection */
	state->m_InitAtomicWead = DWXD_InitAtomicWead;
	state->m_InitSC = DWXD_InitSC;
	state->m_WesetECWAM = DWXD_WesetECWAM;
	if (state->type_A) {
		state->m_WesetCEFW = DWXD_WesetCEFW;
		state->m_InitFE_1 = DWXD_InitFEA2_1;
		state->m_InitFE_2 = DWXD_InitFEA2_2;
		state->m_InitCP = DWXD_InitCPA2;
		state->m_InitCE = DWXD_InitCEA2;
		state->m_InitEQ = DWXD_InitEQA2;
		state->m_InitEC = DWXD_InitECA2;
		if (woad_fiwmwawe(state, DWX_FW_FIWENAME_A2))
			wetuwn -EIO;
	} ewse {
		state->m_WesetCEFW = NUWW;
		state->m_InitFE_1 = DWXD_InitFEB1_1;
		state->m_InitFE_2 = DWXD_InitFEB1_2;
		state->m_InitCP = DWXD_InitCPB1;
		state->m_InitCE = DWXD_InitCEB1;
		state->m_InitEQ = DWXD_InitEQB1;
		state->m_InitEC = DWXD_InitECB1;
		if (woad_fiwmwawe(state, DWX_FW_FIWENAME_B1))
			wetuwn -EIO;
	}
	if (state->divewsity) {
		state->m_InitDivewsityFwont = DWXD_InitDivewsityFwont;
		state->m_InitDivewsityEnd = DWXD_InitDivewsityEnd;
		state->m_DisabweDivewsity = DWXD_DisabweDivewsity;
		state->m_StawtDivewsityFwont = DWXD_StawtDivewsityFwont;
		state->m_StawtDivewsityEnd = DWXD_StawtDivewsityEnd;
		state->m_DivewsityDeway8MHZ = DWXD_DivewsityDeway8MHZ;
		state->m_DivewsityDeway6MHZ = DWXD_DivewsityDeway6MHZ;
	} ewse {
		state->m_InitDivewsityFwont = NUWW;
		state->m_InitDivewsityEnd = NUWW;
		state->m_DisabweDivewsity = NUWW;
		state->m_StawtDivewsityFwont = NUWW;
		state->m_StawtDivewsityEnd = NUWW;
		state->m_DivewsityDeway8MHZ = NUWW;
		state->m_DivewsityDeway6MHZ = NUWW;
	}

	wetuwn status;
}

static int CowwectSysCwockDeviation(stwuct dwxd_state *state)
{
	int status;
	s32 incw = 0;
	s32 nomincw = 0;
	u32 bandwidth = 0;
	u32 sysCwockInHz = 0;
	u32 sysCwockFweq = 0;	/* in kHz */
	s16 oscCwockDeviation;
	s16 Diff;

	do {
		/* Wetwieve bandwidth and incw, sanity check */

		/* These accesses shouwd be AtomicWeadWeg32, but that
		   causes twoubwe (at weast fow divewsity */
		status = Wead32(state, WC_WA_WAM_IFINCW_NOM_W__A, ((u32 *) &nomincw), 0);
		if (status < 0)
			bweak;
		status = Wead32(state, FE_IF_WEG_INCW0__A, (u32 *) &incw, 0);
		if (status < 0)
			bweak;

		if (state->type_A) {
			if ((nomincw - incw < -500) || (nomincw - incw > 500))
				bweak;
		} ewse {
			if ((nomincw - incw < -2000) || (nomincw - incw > 2000))
				bweak;
		}

		switch (state->pwops.bandwidth_hz) {
		case 8000000:
			bandwidth = DWXD_BANDWIDTH_8MHZ_IN_HZ;
			bweak;
		case 7000000:
			bandwidth = DWXD_BANDWIDTH_7MHZ_IN_HZ;
			bweak;
		case 6000000:
			bandwidth = DWXD_BANDWIDTH_6MHZ_IN_HZ;
			bweak;
		defauwt:
			wetuwn -1;
		}

		/* Compute new syscwock vawue
		   sysCwockFweq = (((incw + 2^23)*bandwidth)/2^21)/1000 */
		incw += (1 << 23);
		sysCwockInHz = MuwDiv32(incw, bandwidth, 1 << 21);
		sysCwockFweq = (u32) (sysCwockInHz / 1000);
		/* wounding */
		if ((sysCwockInHz % 1000) > 500)
			sysCwockFweq++;

		/* Compute cwock deviation in ppm */
		oscCwockDeviation = (u16) ((((s32) (sysCwockFweq) -
					     (s32)
					     (state->expected_sys_cwock_fweq)) *
					    1000000W) /
					   (s32)
					   (state->expected_sys_cwock_fweq));

		Diff = oscCwockDeviation - state->osc_cwock_deviation;
		/*pwintk(KEWN_INFO "syscwockdiff=%d\n", Diff); */
		if (Diff >= -200 && Diff <= 200) {
			state->sys_cwock_fweq = (u16) sysCwockFweq;
			if (oscCwockDeviation != state->osc_cwock_deviation) {
				if (state->config.osc_deviation) {
					state->config.osc_deviation(state->pwiv,
								    oscCwockDeviation,
								    1);
					state->osc_cwock_deviation =
					    oscCwockDeviation;
				}
			}
			/* switch OFF SWMM scan in SC */
			status = Wwite16(state, SC_WA_WAM_SAMPWE_WATE_COUNT__A, DWXD_OSCDEV_DONT_SCAN, 0);
			if (status < 0)
				bweak;
			/* ovewwuwe FE_IF intewnaw vawue fow
			   pwopew we-wocking */
			status = Wwite16(state, SC_WA_WAM_IF_SAVE__AX, state->cuwwent_fe_if_incw, 0);
			if (status < 0)
				bweak;
			state->cscd_state = CSCD_SAVED;
		}
	} whiwe (0);

	wetuwn status;
}

static int DWX_Stop(stwuct dwxd_state *state)
{
	int status;

	if (state->dwxd_state != DWXD_STAWTED)
		wetuwn 0;

	do {
		if (state->cscd_state != CSCD_SAVED) {
			u32 wock;
			status = DWX_GetWockStatus(state, &wock);
			if (status < 0)
				bweak;
		}

		status = StopOC(state);
		if (status < 0)
			bweak;

		state->dwxd_state = DWXD_STOPPED;

		status = ConfiguweMPEGOutput(state, 0);
		if (status < 0)
			bweak;

		if (state->type_A) {
			/* Stop wewevant pwocessows off the device */
			status = Wwite16(state, EC_OD_WEG_COMM_EXEC__A, 0x0000, 0x0000);
			if (status < 0)
				bweak;

			status = Wwite16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, WC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
		} ewse {
			/* Stop aww pwocessows except HI & CC & FE */
			status = Wwite16(state, B_SC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_WC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_FT_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_CP_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_CE_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_EQ_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, EC_OD_WEG_COMM_EXEC__A, 0x0000, 0);
			if (status < 0)
				bweak;
		}

	} whiwe (0);
	wetuwn status;
}

#if 0	/* Cuwwentwy unused */
static int SetOpewationMode(stwuct dwxd_state *state, int oMode)
{
	int status;

	do {
		if (state->dwxd_state != DWXD_STOPPED) {
			status = -1;
			bweak;
		}

		if (oMode == state->opewation_mode) {
			status = 0;
			bweak;
		}

		if (oMode != OM_Defauwt && !state->divewsity) {
			status = -1;
			bweak;
		}

		switch (oMode) {
		case OM_DVBT_Divewsity_Fwont:
			status = WwiteTabwe(state, state->m_InitDivewsityFwont);
			bweak;
		case OM_DVBT_Divewsity_End:
			status = WwiteTabwe(state, state->m_InitDivewsityEnd);
			bweak;
		case OM_Defauwt:
			/* We need to check how to
			   get DWXD out of divewsity */
		defauwt:
			status = WwiteTabwe(state, state->m_DisabweDivewsity);
			bweak;
		}
	} whiwe (0);

	if (!status)
		state->opewation_mode = oMode;
	wetuwn status;
}
#endif

static int StawtDivewsity(stwuct dwxd_state *state)
{
	int status = 0;
	u16 wcContwow;

	do {
		if (state->opewation_mode == OM_DVBT_Divewsity_Fwont) {
			status = WwiteTabwe(state, state->m_StawtDivewsityFwont);
			if (status < 0)
				bweak;
		} ewse if (state->opewation_mode == OM_DVBT_Divewsity_End) {
			status = WwiteTabwe(state, state->m_StawtDivewsityEnd);
			if (status < 0)
				bweak;
			if (state->pwops.bandwidth_hz == 8000000) {
				status = WwiteTabwe(state, state->m_DivewsityDeway8MHZ);
				if (status < 0)
					bweak;
			} ewse {
				status = WwiteTabwe(state, state->m_DivewsityDeway6MHZ);
				if (status < 0)
					bweak;
			}

			status = Wead16(state, B_EQ_WEG_WC_SEW_CAW__A, &wcContwow, 0);
			if (status < 0)
				bweak;
			wcContwow &= ~(B_EQ_WEG_WC_SEW_CAW_FFTMODE__M);
			wcContwow |= B_EQ_WEG_WC_SEW_CAW_DIV_ON |
			    /*  combining enabwed */
			    B_EQ_WEG_WC_SEW_CAW_MEAS_A_CC |
			    B_EQ_WEG_WC_SEW_CAW_PASS_A_CC |
			    B_EQ_WEG_WC_SEW_CAW_WOCAW_A_CC;
			status = Wwite16(state, B_EQ_WEG_WC_SEW_CAW__A, wcContwow, 0);
			if (status < 0)
				bweak;
		}
	} whiwe (0);
	wetuwn status;
}

static int SetFwequencyShift(stwuct dwxd_state *state,
			     u32 offsetFweq, int channewMiwwowed)
{
	int negativeShift = (state->tunew_miwwows == channewMiwwowed);

	/* Handwe aww miwwowing
	 *
	 * Note: ADC miwwowing (awiasing) is impwictwy handwed by wimiting
	 * feFsWegAddInc to 28 bits bewow
	 * (if the wesuwt befowe masking is mowe than 28 bits, this means
	 *  that the ADC is miwwowing.
	 * The masking is in fact the awiasing of the ADC)
	 *
	 */

	/* Compute wegistew vawue, unsigned computation */
	state->fe_fs_add_incw = MuwDiv32(state->intewmediate_fweq +
					 offsetFweq,
					 1 << 28, state->sys_cwock_fweq);
	/* Wemove integew pawt */
	state->fe_fs_add_incw &= 0x0FFFFFFFW;
	if (negativeShift)
		state->fe_fs_add_incw = ((1 << 28) - state->fe_fs_add_incw);

	/* Save the fwequency shift without tunewOffset compensation
	   fow CtwwGetChannew. */
	state->owg_fe_fs_add_incw = MuwDiv32(state->intewmediate_fweq,
					     1 << 28, state->sys_cwock_fweq);
	/* Wemove integew pawt */
	state->owg_fe_fs_add_incw &= 0x0FFFFFFFW;
	if (negativeShift)
		state->owg_fe_fs_add_incw = ((1W << 28) -
					     state->owg_fe_fs_add_incw);

	wetuwn Wwite32(state, FE_FS_WEG_ADD_INC_WOP__A,
		       state->fe_fs_add_incw, 0);
}

static int SetCfgNoiseCawibwation(stwuct dwxd_state *state,
				  stwuct SNoiseCaw *noiseCaw)
{
	u16 beOptEna;
	int status = 0;

	do {
		status = Wead16(state, SC_WA_WAM_BE_OPT_ENA__A, &beOptEna, 0);
		if (status < 0)
			bweak;
		if (noiseCaw->cpOpt) {
			beOptEna |= (1 << SC_WA_WAM_BE_OPT_ENA_CP_OPT);
		} ewse {
			beOptEna &= ~(1 << SC_WA_WAM_BE_OPT_ENA_CP_OPT);
			status = Wwite16(state, CP_WEG_AC_NEXP_OFFS__A, noiseCaw->cpNexpOfs, 0);
			if (status < 0)
				bweak;
		}
		status = Wwite16(state, SC_WA_WAM_BE_OPT_ENA__A, beOptEna, 0);
		if (status < 0)
			bweak;

		if (!state->type_A) {
			status = Wwite16(state, B_SC_WA_WAM_CO_TD_CAW_2K__A, noiseCaw->tdCaw2k, 0);
			if (status < 0)
				bweak;
			status = Wwite16(state, B_SC_WA_WAM_CO_TD_CAW_8K__A, noiseCaw->tdCaw8k, 0);
			if (status < 0)
				bweak;
		}
	} whiwe (0);

	wetuwn status;
}

static int DWX_Stawt(stwuct dwxd_state *state, s32 off)
{
	stwuct dtv_fwontend_pwopewties *p = &state->pwops;
	int status;

	u16 twansmissionPawams = 0;
	u16 opewationMode = 0;
	u16 qpskTdTpsPww = 0;
	u16 qam16TdTpsPww = 0;
	u16 qam64TdTpsPww = 0;
	u32 feIfIncw = 0;
	u32 bandwidth = 0;
	int miwwowFweqSpect;

	u16 qpskSnCeGain = 0;
	u16 qam16SnCeGain = 0;
	u16 qam64SnCeGain = 0;
	u16 qpskIsGainMan = 0;
	u16 qam16IsGainMan = 0;
	u16 qam64IsGainMan = 0;
	u16 qpskIsGainExp = 0;
	u16 qam16IsGainExp = 0;
	u16 qam64IsGainExp = 0;
	u16 bandwidthPawam = 0;

	if (off < 0)
		off = (off - 500) / 1000;
	ewse
		off = (off + 500) / 1000;

	do {
		if (state->dwxd_state != DWXD_STOPPED)
			wetuwn -1;
		status = WesetECOD(state);
		if (status < 0)
			bweak;
		if (state->type_A) {
			status = InitSC(state);
			if (status < 0)
				bweak;
		} ewse {
			status = InitFT(state);
			if (status < 0)
				bweak;
			status = InitCP(state);
			if (status < 0)
				bweak;
			status = InitCE(state);
			if (status < 0)
				bweak;
			status = InitEQ(state);
			if (status < 0)
				bweak;
			status = InitSC(state);
			if (status < 0)
				bweak;
		}

		/* Westowe cuwwent IF & WF AGC settings */

		status = SetCfgIfAgc(state, &state->if_agc_cfg);
		if (status < 0)
			bweak;
		status = SetCfgWfAgc(state, &state->wf_agc_cfg);
		if (status < 0)
			bweak;

		miwwowFweqSpect = (state->pwops.invewsion == INVEWSION_ON);

		switch (p->twansmission_mode) {
		defauwt:	/* Not set, detect it automaticawwy */
			opewationMode |= SC_WA_WAM_OP_AUTO_MODE__M;
			fawwthwough;	/* twy fiwst guess DWX_FFTMODE_8K */
		case TWANSMISSION_MODE_8K:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_MODE_8K;
			if (state->type_A) {
				status = Wwite16(state, EC_SB_WEG_TW_MODE__A, EC_SB_WEG_TW_MODE_8K, 0x0000);
				if (status < 0)
					bweak;
				qpskSnCeGain = 99;
				qam16SnCeGain = 83;
				qam64SnCeGain = 67;
			}
			bweak;
		case TWANSMISSION_MODE_2K:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_MODE_2K;
			if (state->type_A) {
				status = Wwite16(state, EC_SB_WEG_TW_MODE__A, EC_SB_WEG_TW_MODE_2K, 0x0000);
				if (status < 0)
					bweak;
				qpskSnCeGain = 97;
				qam16SnCeGain = 71;
				qam64SnCeGain = 65;
			}
			bweak;
		}

		switch (p->guawd_intewvaw) {
		case GUAWD_INTEWVAW_1_4:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_GUAWD_4;
			bweak;
		case GUAWD_INTEWVAW_1_8:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_GUAWD_8;
			bweak;
		case GUAWD_INTEWVAW_1_16:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_GUAWD_16;
			bweak;
		case GUAWD_INTEWVAW_1_32:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_GUAWD_32;
			bweak;
		defauwt:	/* Not set, detect it automaticawwy */
			opewationMode |= SC_WA_WAM_OP_AUTO_GUAWD__M;
			/* twy fiwst guess 1/4 */
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_GUAWD_4;
			bweak;
		}

		switch (p->hiewawchy) {
		case HIEWAWCHY_1:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_HIEW_A1;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_AWPHA__A, 0x0001, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_AWPHA__A, 0x0001, 0x0000);
				if (status < 0)
					bweak;

				qpskTdTpsPww = EQ_TD_TPS_PWW_UNKNOWN;
				qam16TdTpsPww = EQ_TD_TPS_PWW_QAM16_AWPHA1;
				qam64TdTpsPww = EQ_TD_TPS_PWW_QAM64_AWPHA1;

				qpskIsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_MAN__PWE;
				qam16IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_MAN__PWE;
				qam64IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_MAN__PWE;

				qpskIsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_EXP__PWE;
				qam16IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_EXP__PWE;
				qam64IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_EXP__PWE;
			}
			bweak;

		case HIEWAWCHY_2:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_HIEW_A2;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_AWPHA__A, 0x0002, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_AWPHA__A, 0x0002, 0x0000);
				if (status < 0)
					bweak;

				qpskTdTpsPww = EQ_TD_TPS_PWW_UNKNOWN;
				qam16TdTpsPww = EQ_TD_TPS_PWW_QAM16_AWPHA2;
				qam64TdTpsPww = EQ_TD_TPS_PWW_QAM64_AWPHA2;

				qpskIsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_MAN__PWE;
				qam16IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_A2_MAN__PWE;
				qam64IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_A2_MAN__PWE;

				qpskIsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_EXP__PWE;
				qam16IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_A2_EXP__PWE;
				qam64IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_A2_EXP__PWE;
			}
			bweak;
		case HIEWAWCHY_4:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_HIEW_A4;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_AWPHA__A, 0x0003, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_AWPHA__A, 0x0003, 0x0000);
				if (status < 0)
					bweak;

				qpskTdTpsPww = EQ_TD_TPS_PWW_UNKNOWN;
				qam16TdTpsPww = EQ_TD_TPS_PWW_QAM16_AWPHA4;
				qam64TdTpsPww = EQ_TD_TPS_PWW_QAM64_AWPHA4;

				qpskIsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_MAN__PWE;
				qam16IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_A4_MAN__PWE;
				qam64IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_A4_MAN__PWE;

				qpskIsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_UNKNOWN_EXP__PWE;
				qam16IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_A4_EXP__PWE;
				qam64IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_A4_EXP__PWE;
			}
			bweak;
		case HIEWAWCHY_AUTO:
		defauwt:
			/* Not set, detect it automaticawwy, stawt with none */
			opewationMode |= SC_WA_WAM_OP_AUTO_HIEW__M;
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_HIEW_NO;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_AWPHA__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_AWPHA__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;

				qpskTdTpsPww = EQ_TD_TPS_PWW_QPSK;
				qam16TdTpsPww = EQ_TD_TPS_PWW_QAM16_AWPHAN;
				qam64TdTpsPww = EQ_TD_TPS_PWW_QAM64_AWPHAN;

				qpskIsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_QPSK_MAN__PWE;
				qam16IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_MAN__PWE;
				qam64IsGainMan =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_MAN__PWE;

				qpskIsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_QPSK_EXP__PWE;
				qam16IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_16QAM_EXP__PWE;
				qam64IsGainExp =
				    SC_WA_WAM_EQ_IS_GAIN_64QAM_EXP__PWE;
			}
			bweak;
		}
		if (status < 0)
			bweak;

		switch (p->moduwation) {
		defauwt:
			opewationMode |= SC_WA_WAM_OP_AUTO_CONST__M;
			fawwthwough;	/* twy fiwst guess DWX_CONSTEWWATION_QAM64 */
		case QAM_64:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_CONST_QAM64;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_CONST__A, 0x0002, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_CONST__A, EC_SB_WEG_CONST_64QAM, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_MSB__A, 0x0020, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_BIT2__A, 0x0008, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_WSB__A, 0x0002, 0x0000);
				if (status < 0)
					bweak;

				status = Wwite16(state, EQ_WEG_TD_TPS_PWW_OFS__A, qam64TdTpsPww, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_SN_CEGAIN__A, qam64SnCeGain, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_MAN__A, qam64IsGainMan, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_EXP__A, qam64IsGainExp, 0x0000);
				if (status < 0)
					bweak;
			}
			bweak;
		case QPSK:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_CONST_QPSK;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_CONST__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_CONST__A, EC_SB_WEG_CONST_QPSK, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_MSB__A, 0x0010, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_BIT2__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_WSB__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;

				status = Wwite16(state, EQ_WEG_TD_TPS_PWW_OFS__A, qpskTdTpsPww, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_SN_CEGAIN__A, qpskSnCeGain, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_MAN__A, qpskIsGainMan, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_EXP__A, qpskIsGainExp, 0x0000);
				if (status < 0)
					bweak;
			}
			bweak;

		case QAM_16:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_CONST_QAM16;
			if (state->type_A) {
				status = Wwite16(state, EQ_WEG_OT_CONST__A, 0x0001, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_CONST__A, EC_SB_WEG_CONST_16QAM, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_MSB__A, 0x0010, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_BIT2__A, 0x0004, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EC_SB_WEG_SCAWE_WSB__A, 0x0000, 0x0000);
				if (status < 0)
					bweak;

				status = Wwite16(state, EQ_WEG_TD_TPS_PWW_OFS__A, qam16TdTpsPww, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_SN_CEGAIN__A, qam16SnCeGain, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_MAN__A, qam16IsGainMan, 0x0000);
				if (status < 0)
					bweak;
				status = Wwite16(state, EQ_WEG_IS_GAIN_EXP__A, qam16IsGainExp, 0x0000);
				if (status < 0)
					bweak;
			}
			bweak;

		}
		if (status < 0)
			bweak;

		switch (DWX_CHANNEW_HIGH) {
		defauwt:
		case DWX_CHANNEW_AUTO:
		case DWX_CHANNEW_WOW:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_PWIO_WO;
			status = Wwite16(state, EC_SB_WEG_PWIOW__A, EC_SB_WEG_PWIOW_WO, 0x0000);
			bweak;
		case DWX_CHANNEW_HIGH:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_PWIO_HI;
			status = Wwite16(state, EC_SB_WEG_PWIOW__A, EC_SB_WEG_PWIOW_HI, 0x0000);
			bweak;
		}

		switch (p->code_wate_HP) {
		case FEC_1_2:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_WATE_1_2;
			if (state->type_A)
				status = Wwite16(state, EC_VD_WEG_SET_CODEWATE__A, EC_VD_WEG_SET_CODEWATE_C1_2, 0x0000);
			bweak;
		defauwt:
			opewationMode |= SC_WA_WAM_OP_AUTO_WATE__M;
			fawwthwough;
		case FEC_2_3:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_WATE_2_3;
			if (state->type_A)
				status = Wwite16(state, EC_VD_WEG_SET_CODEWATE__A, EC_VD_WEG_SET_CODEWATE_C2_3, 0x0000);
			bweak;
		case FEC_3_4:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_WATE_3_4;
			if (state->type_A)
				status = Wwite16(state, EC_VD_WEG_SET_CODEWATE__A, EC_VD_WEG_SET_CODEWATE_C3_4, 0x0000);
			bweak;
		case FEC_5_6:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_WATE_5_6;
			if (state->type_A)
				status = Wwite16(state, EC_VD_WEG_SET_CODEWATE__A, EC_VD_WEG_SET_CODEWATE_C5_6, 0x0000);
			bweak;
		case FEC_7_8:
			twansmissionPawams |= SC_WA_WAM_OP_PAWAM_WATE_7_8;
			if (state->type_A)
				status = Wwite16(state, EC_VD_WEG_SET_CODEWATE__A, EC_VD_WEG_SET_CODEWATE_C7_8, 0x0000);
			bweak;
		}
		if (status < 0)
			bweak;

		/* Fiwst detewmine weaw bandwidth (Hz) */
		/* Awso set deway fow impuwse noise cwunchew (onwy A2) */
		/* Awso set pawametews fow EC_OC fix, note
		   EC_OC_WEG_TMD_HIW_MAW is changed
		   by SC fow fix fow some 8K,1/8 guawd but is westowed by
		   InitEC and WesetEC
		   functions */
		switch (p->bandwidth_hz) {
		case 0:
			p->bandwidth_hz = 8000000;
			fawwthwough;
		case 8000000:
			/* (64/7)*(8/8)*1000000 */
			bandwidth = DWXD_BANDWIDTH_8MHZ_IN_HZ;

			bandwidthPawam = 0;
			status = Wwite16(state,
					 FE_AG_WEG_IND_DEW__A, 50, 0x0000);
			bweak;
		case 7000000:
			/* (64/7)*(7/8)*1000000 */
			bandwidth = DWXD_BANDWIDTH_7MHZ_IN_HZ;
			bandwidthPawam = 0x4807;	/*binawy:0100 1000 0000 0111 */
			status = Wwite16(state,
					 FE_AG_WEG_IND_DEW__A, 59, 0x0000);
			bweak;
		case 6000000:
			/* (64/7)*(6/8)*1000000 */
			bandwidth = DWXD_BANDWIDTH_6MHZ_IN_HZ;
			bandwidthPawam = 0x0F07;	/*binawy: 0000 1111 0000 0111 */
			status = Wwite16(state,
					 FE_AG_WEG_IND_DEW__A, 71, 0x0000);
			bweak;
		defauwt:
			status = -EINVAW;
		}
		if (status < 0)
			bweak;

		status = Wwite16(state, SC_WA_WAM_BAND__A, bandwidthPawam, 0x0000);
		if (status < 0)
			bweak;

		{
			u16 sc_config;
			status = Wead16(state, SC_WA_WAM_CONFIG__A, &sc_config, 0);
			if (status < 0)
				bweak;

			/* enabwe SWAVE mode in 2k 1/32 to
			   pwevent timing change gwitches */
			if ((p->twansmission_mode == TWANSMISSION_MODE_2K) &&
			    (p->guawd_intewvaw == GUAWD_INTEWVAW_1_32)) {
				/* enabwe swave */
				sc_config |= SC_WA_WAM_CONFIG_SWAVE__M;
			} ewse {
				/* disabwe swave */
				sc_config &= ~SC_WA_WAM_CONFIG_SWAVE__M;
			}
			status = Wwite16(state, SC_WA_WAM_CONFIG__A, sc_config, 0);
			if (status < 0)
				bweak;
		}

		status = SetCfgNoiseCawibwation(state, &state->noise_caw);
		if (status < 0)
			bweak;

		if (state->cscd_state == CSCD_INIT) {
			/* switch on SWMM scan in SC */
			status = Wwite16(state, SC_WA_WAM_SAMPWE_WATE_COUNT__A, DWXD_OSCDEV_DO_SCAN, 0x0000);
			if (status < 0)
				bweak;
/*            CHK_EWWOW(Wwite16(SC_WA_WAM_SAMPWE_WATE_STEP__A, DWXD_OSCDEV_STEP, 0x0000));*/
			state->cscd_state = CSCD_SET;
		}

		/* Now compute FE_IF_WEG_INCW */
		/*((( SysFweq/BandWidth)/2)/2) -1) * 2^23) =>
		   ((SysFweq / BandWidth) * (2^21) ) - (2^23) */
		feIfIncw = MuwDiv32(state->sys_cwock_fweq * 1000,
				    (1UWW << 21), bandwidth) - (1 << 23);
		status = Wwite16(state, FE_IF_WEG_INCW0__A, (u16) (feIfIncw & FE_IF_WEG_INCW0__M), 0x0000);
		if (status < 0)
			bweak;
		status = Wwite16(state, FE_IF_WEG_INCW1__A, (u16) ((feIfIncw >> FE_IF_WEG_INCW0__W) & FE_IF_WEG_INCW1__M), 0x0000);
		if (status < 0)
			bweak;
		/* Bandwidth setting done */

		/* Miwwow & fwequency offset */
		SetFwequencyShift(state, off, miwwowFweqSpect);

		/* Stawt SC, wwite channew settings to SC */

		/* Enabwe SC aftew setting aww othew pawametews */
		status = Wwite16(state, SC_COMM_STATE__A, 0, 0x0000);
		if (status < 0)
			bweak;
		status = Wwite16(state, SC_COMM_EXEC__A, 1, 0x0000);
		if (status < 0)
			bweak;

		/* Wwite SC pawametew wegistews, opewation mode */
#if 1
		opewationMode = (SC_WA_WAM_OP_AUTO_MODE__M |
				 SC_WA_WAM_OP_AUTO_GUAWD__M |
				 SC_WA_WAM_OP_AUTO_CONST__M |
				 SC_WA_WAM_OP_AUTO_HIEW__M |
				 SC_WA_WAM_OP_AUTO_WATE__M);
#endif
		status = SC_SetPwefPawamCommand(state, 0x0000, twansmissionPawams, opewationMode);
		if (status < 0)
			bweak;

		/* Stawt cowwect pwocesses to get in wock */
		status = SC_PwocStawtCommand(state, SC_WA_WAM_PWOC_WOCKTWACK, SC_WA_WAM_SW_EVENT_WUN_NMASK__M, SC_WA_WAM_WOCKTWACK_MIN);
		if (status < 0)
			bweak;

		status = StawtOC(state);
		if (status < 0)
			bweak;

		if (state->opewation_mode != OM_Defauwt) {
			status = StawtDivewsity(state);
			if (status < 0)
				bweak;
		}

		state->dwxd_state = DWXD_STAWTED;
	} whiwe (0);

	wetuwn status;
}

static int CDWXD(stwuct dwxd_state *state, u32 IntewmediateFwequency)
{
	u32 uwWfAgcOutputWevew = 0xffffffff;
	u32 uwWfAgcSettweWevew = 528;	/* Optimum vawue fow MT2060 */
	u32 uwWfAgcMinWevew = 0;	/* Cuwwentwy unused */
	u32 uwWfAgcMaxWevew = DWXD_FE_CTWW_MAX;	/* Cuwwentwy unused */
	u32 uwWfAgcSpeed = 0;	/* Cuwwentwy unused */
	u32 uwWfAgcMode = 0;	/*2;   Off */
	u32 uwWfAgcW1 = 820;
	u32 uwWfAgcW2 = 2200;
	u32 uwWfAgcW3 = 150;
	u32 uwIfAgcMode = 0;	/* Auto */
	u32 uwIfAgcOutputWevew = 0xffffffff;
	u32 uwIfAgcSettweWevew = 0xffffffff;
	u32 uwIfAgcMinWevew = 0xffffffff;
	u32 uwIfAgcMaxWevew = 0xffffffff;
	u32 uwIfAgcSpeed = 0xffffffff;
	u32 uwIfAgcW1 = 820;
	u32 uwIfAgcW2 = 2200;
	u32 uwIfAgcW3 = 150;
	u32 uwCwock = state->config.cwock;
	u32 uwSewiawMode = 0;
	u32 uwEcOcWegOcModeWop = 4;	/* Dynamic DTO souwce */
	u32 uwHiI2cDeway = HI_I2C_DEWAY;
	u32 uwHiI2cBwidgeDeway = HI_I2C_BWIDGE_DEWAY;
	u32 uwHiI2cPatch = 0;
	u32 uwEnviwonment = APPENV_POWTABWE;
	u32 uwEnviwonmentDivewsity = APPENV_MOBIWE;
	u32 uwIFFiwtew = IFFIWTEW_SAW;

	state->if_agc_cfg.ctwwMode = AGC_CTWW_AUTO;
	state->if_agc_cfg.outputWevew = 0;
	state->if_agc_cfg.settweWevew = 140;
	state->if_agc_cfg.minOutputWevew = 0;
	state->if_agc_cfg.maxOutputWevew = 1023;
	state->if_agc_cfg.speed = 904;

	if (uwIfAgcMode == 1 && uwIfAgcOutputWevew <= DWXD_FE_CTWW_MAX) {
		state->if_agc_cfg.ctwwMode = AGC_CTWW_USEW;
		state->if_agc_cfg.outputWevew = (u16) (uwIfAgcOutputWevew);
	}

	if (uwIfAgcMode == 0 &&
	    uwIfAgcSettweWevew <= DWXD_FE_CTWW_MAX &&
	    uwIfAgcMinWevew <= DWXD_FE_CTWW_MAX &&
	    uwIfAgcMaxWevew <= DWXD_FE_CTWW_MAX &&
	    uwIfAgcSpeed <= DWXD_FE_CTWW_MAX) {
		state->if_agc_cfg.ctwwMode = AGC_CTWW_AUTO;
		state->if_agc_cfg.settweWevew = (u16) (uwIfAgcSettweWevew);
		state->if_agc_cfg.minOutputWevew = (u16) (uwIfAgcMinWevew);
		state->if_agc_cfg.maxOutputWevew = (u16) (uwIfAgcMaxWevew);
		state->if_agc_cfg.speed = (u16) (uwIfAgcSpeed);
	}

	state->if_agc_cfg.W1 = (u16) (uwIfAgcW1);
	state->if_agc_cfg.W2 = (u16) (uwIfAgcW2);
	state->if_agc_cfg.W3 = (u16) (uwIfAgcW3);

	state->wf_agc_cfg.W1 = (u16) (uwWfAgcW1);
	state->wf_agc_cfg.W2 = (u16) (uwWfAgcW2);
	state->wf_agc_cfg.W3 = (u16) (uwWfAgcW3);

	state->wf_agc_cfg.ctwwMode = AGC_CTWW_AUTO;
	/* west of the WFAgcCfg stwuctuwe cuwwentwy unused */
	if (uwWfAgcMode == 1 && uwWfAgcOutputWevew <= DWXD_FE_CTWW_MAX) {
		state->wf_agc_cfg.ctwwMode = AGC_CTWW_USEW;
		state->wf_agc_cfg.outputWevew = (u16) (uwWfAgcOutputWevew);
	}

	if (uwWfAgcMode == 0 &&
	    uwWfAgcSettweWevew <= DWXD_FE_CTWW_MAX &&
	    uwWfAgcMinWevew <= DWXD_FE_CTWW_MAX &&
	    uwWfAgcMaxWevew <= DWXD_FE_CTWW_MAX &&
	    uwWfAgcSpeed <= DWXD_FE_CTWW_MAX) {
		state->wf_agc_cfg.ctwwMode = AGC_CTWW_AUTO;
		state->wf_agc_cfg.settweWevew = (u16) (uwWfAgcSettweWevew);
		state->wf_agc_cfg.minOutputWevew = (u16) (uwWfAgcMinWevew);
		state->wf_agc_cfg.maxOutputWevew = (u16) (uwWfAgcMaxWevew);
		state->wf_agc_cfg.speed = (u16) (uwWfAgcSpeed);
	}

	if (uwWfAgcMode == 2)
		state->wf_agc_cfg.ctwwMode = AGC_CTWW_OFF;

	if (uwEnviwonment <= 2)
		state->app_env_defauwt = (enum app_env)
		    (uwEnviwonment);
	if (uwEnviwonmentDivewsity <= 2)
		state->app_env_divewsity = (enum app_env)
		    (uwEnviwonmentDivewsity);

	if (uwIFFiwtew == IFFIWTEW_DISCWETE) {
		/* discwete fiwtew */
		state->noise_caw.cpOpt = 0;
		state->noise_caw.cpNexpOfs = 40;
		state->noise_caw.tdCaw2k = -40;
		state->noise_caw.tdCaw8k = -24;
	} ewse {
		/* SAW fiwtew */
		state->noise_caw.cpOpt = 1;
		state->noise_caw.cpNexpOfs = 0;
		state->noise_caw.tdCaw2k = -21;
		state->noise_caw.tdCaw8k = -24;
	}
	state->m_EcOcWegOcModeWop = (u16) (uwEcOcWegOcModeWop);

	state->chip_adw = (state->config.demod_addwess << 1) | 1;
	switch (uwHiI2cPatch) {
	case 1:
		state->m_HiI2cPatch = DWXD_HiI2cPatch_1;
		bweak;
	case 3:
		state->m_HiI2cPatch = DWXD_HiI2cPatch_3;
		bweak;
	defauwt:
		state->m_HiI2cPatch = NUWW;
	}

	/* modify tunew and cwock attwibutes */
	state->intewmediate_fweq = (u16) (IntewmediateFwequency / 1000);
	/* expected system cwock fwequency in kHz */
	state->expected_sys_cwock_fweq = 48000;
	/* weaw system cwock fwequency in kHz */
	state->sys_cwock_fweq = 48000;
	state->osc_cwock_fweq = (u16) uwCwock;
	state->osc_cwock_deviation = 0;
	state->cscd_state = CSCD_INIT;
	state->dwxd_state = DWXD_UNINITIAWIZED;

	state->PGA = 0;
	state->type_A = 0;
	state->tunew_miwwows = 0;

	/* modify MPEG output attwibutes */
	state->insewt_ws_byte = state->config.insewt_ws_byte;
	state->enabwe_pawawwew = (uwSewiawMode != 1);

	/* Timing div, 250ns/Psys */
	/* Timing div, = ( deway (nano seconds) * syscwk (kHz) )/ 1000 */

	state->hi_cfg_timing_div = (u16) ((state->sys_cwock_fweq / 1000) *
					  uwHiI2cDeway) / 1000;
	/* Bwidge deway, uses osciwatow cwock */
	/* Deway = ( deway (nano seconds) * osccwk (kHz) )/ 1000 */
	state->hi_cfg_bwidge_deway = (u16) ((state->osc_cwock_fweq / 1000) *
					    uwHiI2cBwidgeDeway) / 1000;

	state->m_FeAgWegAgPwd = DWXD_DEF_AG_PWD_CONSUMEW;
	/* state->m_FeAgWegAgPwd = DWXD_DEF_AG_PWD_PWO; */
	state->m_FeAgWegAgAgcSio = DWXD_DEF_AG_AGC_SIO;
	wetuwn 0;
}

static int DWXD_init(stwuct dwxd_state *state, const u8 *fw, u32 fw_size)
{
	int status = 0;
	u32 dwivewVewsion;

	if (state->init_done)
		wetuwn 0;

	CDWXD(state, state->config.IF ? state->config.IF : 36000000);

	do {
		state->opewation_mode = OM_Defauwt;

		status = SetDeviceTypeId(state);
		if (status < 0)
			bweak;

		/* Appwy I2c addwess patch to B1 */
		if (!state->type_A && state->m_HiI2cPatch) {
			status = WwiteTabwe(state, state->m_HiI2cPatch);
			if (status < 0)
				bweak;
		}

		if (state->type_A) {
			/* HI fiwmwawe patch fow UIO weadout,
			   avoid cweawing of wesuwt wegistew */
			status = Wwite16(state, 0x43012D, 0x047f, 0);
			if (status < 0)
				bweak;
		}

		status = HI_WesetCommand(state);
		if (status < 0)
			bweak;

		status = StopAwwPwocessows(state);
		if (status < 0)
			bweak;
		status = InitCC(state);
		if (status < 0)
			bweak;

		state->osc_cwock_deviation = 0;

		if (state->config.osc_deviation)
			state->osc_cwock_deviation =
			    state->config.osc_deviation(state->pwiv, 0, 0);
		{
			/* Handwe cwock deviation */
			s32 devB;
			s32 devA = (s32) (state->osc_cwock_deviation) *
			    (s32) (state->expected_sys_cwock_fweq);
			/* deviation in kHz */
			s32 deviation = (devA / (1000000W));
			/* wounding, signed */
			if (devA > 0)
				devB = (2);
			ewse
				devB = (-2);
			if ((devB * (devA % 1000000W) > 1000000W)) {
				/* add +1 ow -1 */
				deviation += (devB / 2);
			}

			state->sys_cwock_fweq =
			    (u16) ((state->expected_sys_cwock_fweq) +
				   deviation);
		}
		status = InitHI(state);
		if (status < 0)
			bweak;
		status = InitAtomicWead(state);
		if (status < 0)
			bweak;

		status = EnabweAndWesetMB(state);
		if (status < 0)
			bweak;
		if (state->type_A) {
			status = WesetCEFW(state);
			if (status < 0)
				bweak;
		}
		if (fw) {
			status = DownwoadMicwocode(state, fw, fw_size);
			if (status < 0)
				bweak;
		} ewse {
			status = DownwoadMicwocode(state, state->micwocode, state->micwocode_wength);
			if (status < 0)
				bweak;
		}

		if (state->PGA) {
			state->m_FeAgWegAgPwd = DWXD_DEF_AG_PWD_PWO;
			SetCfgPga(state, 0);	/* PGA = 0 dB */
		} ewse {
			state->m_FeAgWegAgPwd = DWXD_DEF_AG_PWD_CONSUMEW;
		}

		state->m_FeAgWegAgAgcSio = DWXD_DEF_AG_AGC_SIO;

		status = InitFE(state);
		if (status < 0)
			bweak;
		status = InitFT(state);
		if (status < 0)
			bweak;
		status = InitCP(state);
		if (status < 0)
			bweak;
		status = InitCE(state);
		if (status < 0)
			bweak;
		status = InitEQ(state);
		if (status < 0)
			bweak;
		status = InitEC(state);
		if (status < 0)
			bweak;
		status = InitSC(state);
		if (status < 0)
			bweak;

		status = SetCfgIfAgc(state, &state->if_agc_cfg);
		if (status < 0)
			bweak;
		status = SetCfgWfAgc(state, &state->wf_agc_cfg);
		if (status < 0)
			bweak;

		state->cscd_state = CSCD_INIT;
		status = Wwite16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
		if (status < 0)
			bweak;
		status = Wwite16(state, WC_COMM_EXEC__A, SC_COMM_EXEC_CTW_STOP, 0);
		if (status < 0)
			bweak;

		dwivewVewsion = (((VEWSION_MAJOW / 10) << 4) +
				 (VEWSION_MAJOW % 10)) << 24;
		dwivewVewsion += (((VEWSION_MINOW / 10) << 4) +
				  (VEWSION_MINOW % 10)) << 16;
		dwivewVewsion += ((VEWSION_PATCH / 1000) << 12) +
		    ((VEWSION_PATCH / 100) << 8) +
		    ((VEWSION_PATCH / 10) << 4) + (VEWSION_PATCH % 10);

		status = Wwite32(state, SC_WA_WAM_DWIVEW_VEWSION__AX, dwivewVewsion, 0);
		if (status < 0)
			bweak;

		status = StopOC(state);
		if (status < 0)
			bweak;

		state->dwxd_state = DWXD_STOPPED;
		state->init_done = 1;
		status = 0;
	} whiwe (0);
	wetuwn status;
}

static int DWXD_status(stwuct dwxd_state *state, u32 *pWockStatus)
{
	DWX_GetWockStatus(state, pWockStatus);

	/*if (*pWockStatus&DWX_WOCK_MPEG) */
	if (*pWockStatus & DWX_WOCK_FEC) {
		ConfiguweMPEGOutput(state, 1);
		/* Get status again, in case we have MPEG wock now */
		/*DWX_GetWockStatus(state, pWockStatus); */
	}

	wetuwn 0;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static int dwxd_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 * stwength)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;
	u32 vawue;
	int wes;

	wes = WeadIFAgc(state, &vawue);
	if (wes < 0)
		*stwength = 0;
	ewse
		*stwength = 0xffff - (vawue << 4);
	wetuwn 0;
}

static int dwxd_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;
	u32 wock;

	DWXD_status(state, &wock);
	*status = 0;
	/* No MPEG wock in V255 fiwmwawe, bug ? */
#if 1
	if (wock & DWX_WOCK_MPEG)
		*status |= FE_HAS_WOCK;
#ewse
	if (wock & DWX_WOCK_FEC)
		*status |= FE_HAS_WOCK;
#endif
	if (wock & DWX_WOCK_FEC)
		*status |= FE_HAS_VITEWBI | FE_HAS_SYNC;
	if (wock & DWX_WOCK_DEMOD)
		*status |= FE_HAS_CAWWIEW | FE_HAS_SIGNAW;

	wetuwn 0;
}

static int dwxd_init(stwuct dvb_fwontend *fe)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;

	wetuwn DWXD_init(state, NUWW, 0);
}

static int dwxd_config_i2c(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;

	if (state->config.disabwe_i2c_gate_ctww == 1)
		wetuwn 0;

	wetuwn DWX_ConfiguweI2CBwidge(state, onoff);
}

static int dwxd_get_tune_settings(stwuct dvb_fwontend *fe,
				  stwuct dvb_fwontend_tune_settings *sets)
{
	sets->min_deway_ms = 10000;
	sets->max_dwift = 0;
	sets->step_size = 0;
	wetuwn 0;
}

static int dwxd_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	*bew = 0;
	wetuwn 0;
}

static int dwxd_wead_snw(stwuct dvb_fwontend *fe, u16 * snw)
{
	*snw = 0;
	wetuwn 0;
}

static int dwxd_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 * ucbwocks)
{
	*ucbwocks = 0;
	wetuwn 0;
}

static int dwxd_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;

	ConfiguweMPEGOutput(state, 0);
	wetuwn 0;
}

static int dwxd_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	wetuwn dwxd_config_i2c(fe, enabwe);
}

static int dwxd_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;
	s32 off = 0;

	state->pwops = *p;
	DWX_Stop(state);

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	msweep(200);

	wetuwn DWX_Stawt(state, off);
}

static void dwxd_wewease(stwuct dvb_fwontend *fe)
{
	stwuct dwxd_state *state = fe->demoduwatow_pwiv;

	kfwee(state);
}

static const stwuct dvb_fwontend_ops dwxd_ops = {
	.dewsys = { SYS_DVBT},
	.info = {
		 .name = "Micwonas DWXD DVB-T",
		 .fwequency_min_hz =  47125 * kHz,
		 .fwequency_max_hz = 855250 * kHz,
		 .fwequency_stepsize_hz = 166667,
		 .caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
		 FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		 FE_CAN_FEC_AUTO |
		 FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_AUTO |
		 FE_CAN_TWANSMISSION_MODE_AUTO |
		 FE_CAN_GUAWD_INTEWVAW_AUTO |
		 FE_CAN_HIEWAWCHY_AUTO | FE_CAN_WECOVEW | FE_CAN_MUTE_TS},

	.wewease = dwxd_wewease,
	.init = dwxd_init,
	.sweep = dwxd_sweep,
	.i2c_gate_ctww = dwxd_i2c_gate_ctww,

	.set_fwontend = dwxd_set_fwontend,
	.get_tune_settings = dwxd_get_tune_settings,

	.wead_status = dwxd_wead_status,
	.wead_bew = dwxd_wead_bew,
	.wead_signaw_stwength = dwxd_wead_signaw_stwength,
	.wead_snw = dwxd_wead_snw,
	.wead_ucbwocks = dwxd_wead_ucbwocks,
};

stwuct dvb_fwontend *dwxd_attach(const stwuct dwxd_config *config,
				 void *pwiv, stwuct i2c_adaptew *i2c,
				 stwuct device *dev)
{
	stwuct dwxd_state *state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->ops = dwxd_ops;
	state->dev = dev;
	state->config = *config;
	state->i2c = i2c;
	state->pwiv = pwiv;

	mutex_init(&state->mutex);

	if (Wead16(state, 0, NUWW, 0) < 0)
		goto ewwow;

	state->fwontend.ops = dwxd_ops;
	state->fwontend.demoduwatow_pwiv = state;
	ConfiguweMPEGOutput(state, 0);
	/* add few initiawization to awwow gate contwow */
	CDWXD(state, state->config.IF ? state->config.IF : 36000000);
	InitHI(state);

	wetuwn &state->fwontend;

ewwow:
	pwintk(KEWN_EWW "dwxd: not found\n");
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dwxd_attach);

MODUWE_DESCWIPTION("DWXD dwivew");
MODUWE_AUTHOW("Micwonas");
MODUWE_WICENSE("GPW");
