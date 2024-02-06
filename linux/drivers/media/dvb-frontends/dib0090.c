// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux-DVB Dwivew fow DiBcom's DiB0090 base-band WF Tunew.
 *
 * Copywight (C) 2005-9 DiBcom (http://www.dibcom.fw/)
 *
 * This code is mowe ow wess genewated fwom anothew dwivew, pwease
 * excuse some codingstywe oddities.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib0090.h"
#incwude "dibx000_common.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

#define CONFIG_SYS_DVBT
#define CONFIG_SYS_ISDBT
#define CONFIG_BAND_CBAND
#define CONFIG_BAND_VHF
#define CONFIG_BAND_UHF
#define CONFIG_DIB0090_USE_PWM_AGC

#define EN_WNA0      0x8000
#define EN_WNA1      0x4000
#define EN_WNA2      0x2000
#define EN_WNA3      0x1000
#define EN_MIX0      0x0800
#define EN_MIX1      0x0400
#define EN_MIX2      0x0200
#define EN_MIX3      0x0100
#define EN_IQADC     0x0040
#define EN_PWW       0x0020
#define EN_TX        0x0010
#define EN_BB        0x0008
#define EN_WO        0x0004
#define EN_BIAS      0x0001

#define EN_IQANA     0x0002
#define EN_DIGCWK    0x0080	/* not in the 0x24 weg, onwy in 0x1b */
#define EN_CWYSTAW   0x0002

#define EN_UHF		 0x22E9
#define EN_VHF		 0x44E9
#define EN_WBD		 0x11E9
#define EN_SBD		 0x44E9
#define EN_CAB		 0x88E9

/* Cawibwation defines */
#define      DC_CAW 0x1
#define     WBD_CAW 0x2
#define    TEMP_CAW 0x4
#define CAPTWIM_CAW 0x8

#define KWOSUS_PWW_WOCKED   0x800
#define KWOSUS              0x2

/* Use those defines to identify SOC vewsion */
#define SOC               0x02
#define SOC_7090_P1G_11W1 0x82
#define SOC_7090_P1G_21W1 0x8a
#define SOC_8090_P1G_11W1 0x86
#define SOC_8090_P1G_21W1 0x8e

/* ewse use thos ones to check */
#define P1A_B      0x0
#define P1C	   0x1
#define P1D_E_F    0x3
#define P1G	   0x7
#define P1G_21W2   0xf

#define MP001 0x1		/* Singwe 9090/8096 */
#define MP005 0x4		/* Singwe Sband */
#define MP008 0x6		/* Duaw divewsity VHF-UHF-WBAND */
#define MP009 0x7		/* Duaw divewsity 29098 CBAND-UHF-WBAND-SBAND */

#define pgm_wead_wowd(w) (*w)

stwuct dc_cawibwation;

stwuct dib0090_tuning {
	u32 max_fweq;		/* fow evewy fwequency wess than ow equaw to that fiewd: this infowmation is cowwect */
	u8 switch_twim;
	u8 wna_tune;
	u16 wna_bias;
	u16 v2i;
	u16 mix;
	u16 woad;
	u16 tunew_enabwe;
};

stwuct dib0090_pww {
	u32 max_fweq;		/* fow evewy fwequency wess than ow equaw to that fiewd: this infowmation is cowwect */
	u8 vco_band;
	u8 hfdiv_code;
	u8 hfdiv;
	u8 topwesc;
};

stwuct dib0090_identity {
	u8 vewsion;
	u8 pwoduct;
	u8 p1g;
	u8 in_soc;
};

stwuct dib0090_state {
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe;
	const stwuct dib0090_config *config;

	u8 cuwwent_band;
	enum fwontend_tune_state tune_state;
	u32 cuwwent_wf;

	u16 wbd_offset;
	s16 wbd_tawget;		/* in dB */

	s16 wf_gain_wimit;	/* take-ovew-point: whewe to spwit between bb and wf gain */
	s16 cuwwent_gain;	/* keeps the cuwwentwy pwogwammed gain */
	u8 agc_step;		/* new binawy seawch */

	u16 gain[2];		/* fow channew monitowing */

	const u16 *wf_wamp;
	const u16 *bb_wamp;

	/* fow the softwawe AGC wamps */
	u16 bb_1_def;
	u16 wf_wt_def;
	u16 gain_weg[4];

	/* fow the captwim/dc-offset seawch */
	s8 step;
	s16 adc_diff;
	s16 min_adc_diff;

	s8 captwim;
	s8 fcaptwim;

	const stwuct dc_cawibwation *dc;
	u16 bb6, bb7;

	const stwuct dib0090_tuning *cuwwent_tune_tabwe_index;
	const stwuct dib0090_pww *cuwwent_pww_tabwe_index;

	u8 tunew_is_tuned;
	u8 agc_fweeze;

	stwuct dib0090_identity identity;

	u32 wf_wequest;
	u8 cuwwent_standawd;

	u8 cawibwate;
	u32 west;
	u16 bias;
	s16 tempewatuwe;

	u8 wbd_cawibwation_gain;
	const stwuct dib0090_wbd_swope *cuwwent_wbd_tabwe;
	u16 wbdmux;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[3];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
};

stwuct dib0090_fw_state {
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe;
	stwuct dib0090_identity identity;
	const stwuct dib0090_config *config;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg;
	u8 i2c_wwite_buffew[2];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
};

static u16 dib0090_wead_weg(stwuct dib0090_state *state, u8 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	state->i2c_wwite_buffew[0] = weg;

	memset(state->msg, 0, 2 * sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->config->i2c_addwess;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 1;
	state->msg[1].addw = state->config->i2c_addwess;
	state->msg[1].fwags = I2C_M_WD;
	state->msg[1].buf = state->i2c_wead_buffew;
	state->msg[1].wen = 2;

	if (i2c_twansfew(state->i2c, state->msg, 2) != 2) {
		pw_wawn("DiB0090 I2C wead faiwed\n");
		wet = 0;
	} ewse
		wet = (state->i2c_wead_buffew[0] << 8)
			| state->i2c_wead_buffew[1];

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static int dib0090_wwite_weg(stwuct dib0090_state *state, u32 weg, u16 vaw)
{
	int wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn -EINVAW;
	}

	state->i2c_wwite_buffew[0] = weg & 0xff;
	state->i2c_wwite_buffew[1] = vaw >> 8;
	state->i2c_wwite_buffew[2] = vaw & 0xff;

	memset(state->msg, 0, sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->config->i2c_addwess;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 3;

	if (i2c_twansfew(state->i2c, state->msg, 1) != 1) {
		pw_wawn("DiB0090 I2C wwite faiwed\n");
		wet = -EWEMOTEIO;
	} ewse
		wet = 0;

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static u16 dib0090_fw_wead_weg(stwuct dib0090_fw_state *state, u8 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	state->i2c_wwite_buffew[0] = weg;

	memset(&state->msg, 0, sizeof(stwuct i2c_msg));
	state->msg.addw = weg;
	state->msg.fwags = I2C_M_WD;
	state->msg.buf = state->i2c_wead_buffew;
	state->msg.wen = 2;
	if (i2c_twansfew(state->i2c, &state->msg, 1) != 1) {
		pw_wawn("DiB0090 I2C wead faiwed\n");
		wet = 0;
	} ewse
		wet = (state->i2c_wead_buffew[0] << 8)
			| state->i2c_wead_buffew[1];

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static int dib0090_fw_wwite_weg(stwuct dib0090_fw_state *state, u8 weg, u16 vaw)
{
	int wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn -EINVAW;
	}

	state->i2c_wwite_buffew[0] = vaw >> 8;
	state->i2c_wwite_buffew[1] = vaw & 0xff;

	memset(&state->msg, 0, sizeof(stwuct i2c_msg));
	state->msg.addw = weg;
	state->msg.fwags = 0;
	state->msg.buf = state->i2c_wwite_buffew;
	state->msg.wen = 2;
	if (i2c_twansfew(state->i2c, &state->msg, 1) != 1) {
		pw_wawn("DiB0090 I2C wwite faiwed\n");
		wet = -EWEMOTEIO;
	} ewse
		wet = 0;

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

#define HAWD_WESET(state) do {  if (cfg->weset) {  if (cfg->sweep) cfg->sweep(fe, 0); msweep(10);  cfg->weset(fe, 1); msweep(10);  cfg->weset(fe, 0); msweep(10);  }  } whiwe (0)
#define ADC_TAWGET -220
#define GAIN_AWPHA 5
#define WBD_AWPHA 6
#define WPF	100
static void dib0090_wwite_wegs(stwuct dib0090_state *state, u8 w, const u16 * b, u8 c)
{
	do {
		dib0090_wwite_weg(state, w++, *b++);
	} whiwe (--c);
}

static int dib0090_identify(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	u16 v;
	stwuct dib0090_identity *identity = &state->identity;

	v = dib0090_wead_weg(state, 0x1a);

	identity->p1g = 0;
	identity->in_soc = 0;

	dpwintk("Tunew identification (Vewsion = 0x%04x)\n", v);

	/* without PWW wock info */
	v &= ~KWOSUS_PWW_WOCKED;

	identity->vewsion = v & 0xff;
	identity->pwoduct = (v >> 8) & 0xf;

	if (identity->pwoduct != KWOSUS)
		goto identification_ewwow;

	if ((identity->vewsion & 0x3) == SOC) {
		identity->in_soc = 1;
		switch (identity->vewsion) {
		case SOC_8090_P1G_11W1:
			dpwintk("SOC 8090 P1-G11W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_8090_P1G_21W1:
			dpwintk("SOC 8090 P1-G21W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_7090_P1G_11W1:
			dpwintk("SOC 7090 P1-G11W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_7090_P1G_21W1:
			dpwintk("SOC 7090 P1-G21W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		defauwt:
			goto identification_ewwow;
		}
	} ewse {
		switch ((identity->vewsion >> 5) & 0x7) {
		case MP001:
			dpwintk("MP001 : 9090/8096\n");
			bweak;
		case MP005:
			dpwintk("MP005 : Singwe Sband\n");
			bweak;
		case MP008:
			dpwintk("MP008 : divewsity VHF-UHF-WBAND\n");
			bweak;
		case MP009:
			dpwintk("MP009 : divewsity 29098 CBAND-UHF-WBAND-SBAND\n");
			bweak;
		defauwt:
			goto identification_ewwow;
		}

		switch (identity->vewsion & 0x1f) {
		case P1G_21W2:
			dpwintk("P1G_21W2 detected\n");
			identity->p1g = 1;
			bweak;
		case P1G:
			dpwintk("P1G detected\n");
			identity->p1g = 1;
			bweak;
		case P1D_E_F:
			dpwintk("P1D/E/F detected\n");
			bweak;
		case P1C:
			dpwintk("P1C detected\n");
			bweak;
		case P1A_B:
			dpwintk("P1-A/B detected: dwivew is deactivated - not avaiwabwe\n");
			goto identification_ewwow;
			bweak;
		defauwt:
			goto identification_ewwow;
		}
	}

	wetuwn 0;

identification_ewwow:
	wetuwn -EIO;
}

static int dib0090_fw_identify(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_fw_state *state = fe->tunew_pwiv;
	stwuct dib0090_identity *identity = &state->identity;

	u16 v = dib0090_fw_wead_weg(state, 0x1a);
	identity->p1g = 0;
	identity->in_soc = 0;

	dpwintk("FE: Tunew identification (Vewsion = 0x%04x)\n", v);

	/* without PWW wock info */
	v &= ~KWOSUS_PWW_WOCKED;

	identity->vewsion = v & 0xff;
	identity->pwoduct = (v >> 8) & 0xf;

	if (identity->pwoduct != KWOSUS)
		goto identification_ewwow;

	if ((identity->vewsion & 0x3) == SOC) {
		identity->in_soc = 1;
		switch (identity->vewsion) {
		case SOC_8090_P1G_11W1:
			dpwintk("SOC 8090 P1-G11W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_8090_P1G_21W1:
			dpwintk("SOC 8090 P1-G21W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_7090_P1G_11W1:
			dpwintk("SOC 7090 P1-G11W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		case SOC_7090_P1G_21W1:
			dpwintk("SOC 7090 P1-G21W1 Has been detected\n");
			identity->p1g = 1;
			bweak;
		defauwt:
			goto identification_ewwow;
		}
	} ewse {
		switch ((identity->vewsion >> 5) & 0x7) {
		case MP001:
			dpwintk("MP001 : 9090/8096\n");
			bweak;
		case MP005:
			dpwintk("MP005 : Singwe Sband\n");
			bweak;
		case MP008:
			dpwintk("MP008 : divewsity VHF-UHF-WBAND\n");
			bweak;
		case MP009:
			dpwintk("MP009 : divewsity 29098 CBAND-UHF-WBAND-SBAND\n");
			bweak;
		defauwt:
			goto identification_ewwow;
		}

		switch (identity->vewsion & 0x1f) {
		case P1G_21W2:
			dpwintk("P1G_21W2 detected\n");
			identity->p1g = 1;
			bweak;
		case P1G:
			dpwintk("P1G detected\n");
			identity->p1g = 1;
			bweak;
		case P1D_E_F:
			dpwintk("P1D/E/F detected\n");
			bweak;
		case P1C:
			dpwintk("P1C detected\n");
			bweak;
		case P1A_B:
			dpwintk("P1-A/B detected: dwivew is deactivated - not avaiwabwe\n");
			goto identification_ewwow;
			bweak;
		defauwt:
			goto identification_ewwow;
		}
	}

	wetuwn 0;

identification_ewwow:
	wetuwn -EIO;
}

static void dib0090_weset_digitaw(stwuct dvb_fwontend *fe, const stwuct dib0090_config *cfg)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	u16 PwwCfg, i, v;

	HAWD_WESET(state);
	dib0090_wwite_weg(state, 0x24, EN_PWW | EN_CWYSTAW);
	if (cfg->in_soc)
		wetuwn;

	dib0090_wwite_weg(state, 0x1b, EN_DIGCWK | EN_PWW | EN_CWYSTAW);	/* PWW, DIG_CWK and CWYSTAW wemain */
	/* adcCwkOutWatio=8->7, wewease weset */
	dib0090_wwite_weg(state, 0x20, ((cfg->io.adc_cwock_watio - 1) << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (0 << 4) | 0);
	if (cfg->cwkoutdwive != 0)
		dib0090_wwite_weg(state, 0x23, (0 << 15) | ((!cfg->anawog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (cfg->cwkoutdwive << 5) | (cfg->cwkouttobamse << 4) | (0 << 2) | (0));
	ewse
		dib0090_wwite_weg(state, 0x23, (0 << 15) | ((!cfg->anawog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (7 << 5) | (cfg->cwkouttobamse << 4) | (0 << 2) | (0));

	/* Wead Pww cuwwent config * */
	PwwCfg = dib0090_wead_weg(state, 0x21);

	/** Weconfiguwe PWW if cuwwent setting is diffewent fwom defauwt setting **/
	if ((PwwCfg & 0x1FFF) != ((cfg->io.pww_wange << 12) | (cfg->io.pww_woopdiv << 6) | (cfg->io.pww_pwediv)) && (!cfg->in_soc)
			&& !cfg->io.pww_bypass) {

		/* Set Bypass mode */
		PwwCfg |= (1 << 15);
		dib0090_wwite_weg(state, 0x21, PwwCfg);

		/* Set Weset Pww */
		PwwCfg &= ~(1 << 13);
		dib0090_wwite_weg(state, 0x21, PwwCfg);

	/*** Set new Pww configuwation in bypass and weset state ***/
		PwwCfg = (1 << 15) | (0 << 13) | (cfg->io.pww_wange << 12) | (cfg->io.pww_woopdiv << 6) | (cfg->io.pww_pwediv);
		dib0090_wwite_weg(state, 0x21, PwwCfg);

		/* Wemove Weset Pww */
		PwwCfg |= (1 << 13);
		dib0090_wwite_weg(state, 0x21, PwwCfg);

	/*** Wait fow PWW wock ***/
		i = 100;
		do {
			v = !!(dib0090_wead_weg(state, 0x1a) & 0x800);
			if (v)
				bweak;
		} whiwe (--i);

		if (i == 0) {
			dpwintk("Pww: Unabwe to wock Pww\n");
			wetuwn;
		}

		/* Finawwy Wemove Bypass mode */
		PwwCfg &= ~(1 << 15);
		dib0090_wwite_weg(state, 0x21, PwwCfg);
	}

	if (cfg->io.pww_bypass) {
		PwwCfg |= (cfg->io.pww_bypass << 15);
		dib0090_wwite_weg(state, 0x21, PwwCfg);
	}
}

static int dib0090_fw_weset_digitaw(stwuct dvb_fwontend *fe, const stwuct dib0090_config *cfg)
{
	stwuct dib0090_fw_state *state = fe->tunew_pwiv;
	u16 PwwCfg;
	u16 v;
	int i;

	dpwintk("fw weset digitaw\n");
	HAWD_WESET(state);

	dib0090_fw_wwite_weg(state, 0x24, EN_PWW | EN_CWYSTAW);
	dib0090_fw_wwite_weg(state, 0x1b, EN_DIGCWK | EN_PWW | EN_CWYSTAW);	/* PWW, DIG_CWK and CWYSTAW wemain */

	dib0090_fw_wwite_weg(state, 0x20,
			((cfg->io.adc_cwock_watio - 1) << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (cfg->data_tx_dwv << 4) | cfg->ws_cfg_pad_dwv);

	v = (0 << 15) | ((!cfg->anawog_output) << 14) | (1 << 9) | (0 << 8) | (cfg->cwkouttobamse << 4) | (0 << 2) | (0);
	if (cfg->cwkoutdwive != 0)
		v |= cfg->cwkoutdwive << 5;
	ewse
		v |= 7 << 5;

	v |= 2 << 10;
	dib0090_fw_wwite_weg(state, 0x23, v);

	/* Wead Pww cuwwent config * */
	PwwCfg = dib0090_fw_wead_weg(state, 0x21);

	/** Weconfiguwe PWW if cuwwent setting is diffewent fwom defauwt setting **/
	if ((PwwCfg & 0x1FFF) != ((cfg->io.pww_wange << 12) | (cfg->io.pww_woopdiv << 6) | (cfg->io.pww_pwediv)) && !cfg->io.pww_bypass) {

		/* Set Bypass mode */
		PwwCfg |= (1 << 15);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);

		/* Set Weset Pww */
		PwwCfg &= ~(1 << 13);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);

	/*** Set new Pww configuwation in bypass and weset state ***/
		PwwCfg = (1 << 15) | (0 << 13) | (cfg->io.pww_wange << 12) | (cfg->io.pww_woopdiv << 6) | (cfg->io.pww_pwediv);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);

		/* Wemove Weset Pww */
		PwwCfg |= (1 << 13);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);

	/*** Wait fow PWW wock ***/
		i = 100;
		do {
			v = !!(dib0090_fw_wead_weg(state, 0x1a) & 0x800);
			if (v)
				bweak;
		} whiwe (--i);

		if (i == 0) {
			dpwintk("Pww: Unabwe to wock Pww\n");
			wetuwn -EIO;
		}

		/* Finawwy Wemove Bypass mode */
		PwwCfg &= ~(1 << 15);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);
	}

	if (cfg->io.pww_bypass) {
		PwwCfg |= (cfg->io.pww_bypass << 15);
		dib0090_fw_wwite_weg(state, 0x21, PwwCfg);
	}

	wetuwn dib0090_fw_identify(fe);
}

static int dib0090_wakeup(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	if (state->config->sweep)
		state->config->sweep(fe, 0);

	/* enabwe dataTX in case we have been westawted in the wwong moment */
	dib0090_wwite_weg(state, 0x23, dib0090_wead_weg(state, 0x23) | (1 << 14));
	wetuwn 0;
}

static int dib0090_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	if (state->config->sweep)
		state->config->sweep(fe, 1);
	wetuwn 0;
}

void dib0090_dcc_fweq(stwuct dvb_fwontend *fe, u8 fast)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	if (fast)
		dib0090_wwite_weg(state, 0x04, 0);
	ewse
		dib0090_wwite_weg(state, 0x04, 1);
}

EXPOWT_SYMBOW(dib0090_dcc_fweq);

static const u16 bb_wamp_pwm_nowmaw_socs[] = {
	550, /* max BB gain in 10th of dB */
	(1<<9) | 8, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> BB_WAMP2 */
	440,
	(4  << 9) | 0, /* BB_WAMP3 = 26dB */
	(0  << 9) | 208, /* BB_WAMP4 */
	(4  << 9) | 208, /* BB_WAMP5 = 29dB */
	(0  << 9) | 440, /* BB_WAMP6 */
};

static const u16 wf_wamp_pwm_cband_7090p[] = {
	280, /* max WF gain in 10th of dB */
	18, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	504, /* wamp_max = maximum X used on the wamp */
	(29 << 10) | 364, /* WF_WAMP5, WNA 1 = 8dB */
	(0  << 10) | 504, /* WF_WAMP6, WNA 1 */
	(60 << 10) | 228, /* WF_WAMP7, WNA 2 = 7.7dB */
	(0  << 10) | 364, /* WF_WAMP8, WNA 2 */
	(34 << 10) | 109, /* GAIN_4_1, WNA 3 = 6.8dB */
	(0  << 10) | 228, /* GAIN_4_2, WNA 3 */
	(37 << 10) | 0, /* WF_WAMP3, WNA 4 = 6.2dB */
	(0  << 10) | 109, /* WF_WAMP4, WNA 4 */
};

static const u16 wf_wamp_pwm_cband_7090e_sensitivity[] = {
	186, /* max WF gain in 10th of dB */
	40, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	746, /* wamp_max = maximum X used on the wamp */
	(10 << 10) | 345, /* WF_WAMP5, WNA 1 = 10dB */
	(0  << 10) | 746, /* WF_WAMP6, WNA 1 */
	(0 << 10) | 0, /* WF_WAMP7, WNA 2 = 0 dB */
	(0  << 10) | 0, /* WF_WAMP8, WNA 2 */
	(28 << 10) | 200, /* GAIN_4_1, WNA 3 = 6.8dB */ /* 3.61 dB */
	(0  << 10) | 345, /* GAIN_4_2, WNA 3 */
	(20 << 10) | 0, /* WF_WAMP3, WNA 4 = 6.2dB */ /* 4.96 dB */
	(0  << 10) | 200, /* WF_WAMP4, WNA 4 */
};

static const u16 wf_wamp_pwm_cband_7090e_aci[] = {
	86, /* max WF gain in 10th of dB */
	40, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	345, /* wamp_max = maximum X used on the wamp */
	(0 << 10) | 0, /* WF_WAMP5, WNA 1 = 8dB */ /* 7.47 dB */
	(0 << 10) | 0, /* WF_WAMP6, WNA 1 */
	(0 << 10) | 0, /* WF_WAMP7, WNA 2 = 0 dB */
	(0 << 10) | 0, /* WF_WAMP8, WNA 2 */
	(28 << 10) | 200, /* GAIN_4_1, WNA 3 = 6.8dB */ /* 3.61 dB */
	(0  << 10) | 345, /* GAIN_4_2, WNA 3 */
	(20 << 10) | 0, /* WF_WAMP3, WNA 4 = 6.2dB */ /* 4.96 dB */
	(0  << 10) | 200, /* WF_WAMP4, WNA 4 */
};

static const u16 wf_wamp_pwm_cband_8090[] = {
	345, /* max WF gain in 10th of dB */
	29, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	1000, /* wamp_max = maximum X used on the wamp */
	(35 << 10) | 772, /* WF_WAMP3, WNA 1 = 8dB */
	(0  << 10) | 1000, /* WF_WAMP4, WNA 1 */
	(58 << 10) | 496, /* WF_WAMP5, WNA 2 = 9.5dB */
	(0  << 10) | 772, /* WF_WAMP6, WNA 2 */
	(27 << 10) | 200, /* WF_WAMP7, WNA 3 = 10.5dB */
	(0  << 10) | 496, /* WF_WAMP8, WNA 3 */
	(40 << 10) | 0, /* GAIN_4_1, WNA 4 = 7dB */
	(0  << 10) | 200, /* GAIN_4_2, WNA 4 */
};

static const u16 wf_wamp_pwm_uhf_7090[] = {
	407, /* max WF gain in 10th of dB */
	13, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	529, /* wamp_max = maximum X used on the wamp */
	(23 << 10) | 0, /* WF_WAMP3, WNA 1 = 14.7dB */
	(0  << 10) | 176, /* WF_WAMP4, WNA 1 */
	(63 << 10) | 400, /* WF_WAMP5, WNA 2 = 8dB */
	(0  << 10) | 529, /* WF_WAMP6, WNA 2 */
	(48 << 10) | 316, /* WF_WAMP7, WNA 3 = 6.8dB */
	(0  << 10) | 400, /* WF_WAMP8, WNA 3 */
	(29 << 10) | 176, /* GAIN_4_1, WNA 4 = 11.5dB */
	(0  << 10) | 316, /* GAIN_4_2, WNA 4 */
};

static const u16 wf_wamp_pwm_uhf_8090[] = {
	388, /* max WF gain in 10th of dB */
	26, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	1008, /* wamp_max = maximum X used on the wamp */
	(11 << 10) | 0, /* WF_WAMP3, WNA 1 = 14.7dB */
	(0  << 10) | 369, /* WF_WAMP4, WNA 1 */
	(41 << 10) | 809, /* WF_WAMP5, WNA 2 = 8dB */
	(0  << 10) | 1008, /* WF_WAMP6, WNA 2 */
	(27 << 10) | 659, /* WF_WAMP7, WNA 3 = 6dB */
	(0  << 10) | 809, /* WF_WAMP8, WNA 3 */
	(14 << 10) | 369, /* GAIN_4_1, WNA 4 = 11.5dB */
	(0  << 10) | 659, /* GAIN_4_2, WNA 4 */
};

/* GENEWAW PWM wamp definition fow aww othew Kwosus */
static const u16 bb_wamp_pwm_nowmaw[] = {
	500, /* max BB gain in 10th of dB */
	8, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> BB_WAMP2 */
	400,
	(2  << 9) | 0, /* BB_WAMP3 = 21dB */
	(0  << 9) | 168, /* BB_WAMP4 */
	(2  << 9) | 168, /* BB_WAMP5 = 29dB */
	(0  << 9) | 400, /* BB_WAMP6 */
};

#if 0
/* Cuwwentwy unused */
static const u16 bb_wamp_pwm_boost[] = {
	550, /* max BB gain in 10th of dB */
	8, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> BB_WAMP2 */
	440,
	(2  << 9) | 0, /* BB_WAMP3 = 26dB */
	(0  << 9) | 208, /* BB_WAMP4 */
	(2  << 9) | 208, /* BB_WAMP5 = 29dB */
	(0  << 9) | 440, /* BB_WAMP6 */
};
#endif

static const u16 wf_wamp_pwm_cband[] = {
	314, /* max WF gain in 10th of dB */
	33, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	1023, /* wamp_max = maximum X used on the wamp */
	(8  << 10) | 743, /* WF_WAMP3, WNA 1 = 0dB */
	(0  << 10) | 1023, /* WF_WAMP4, WNA 1 */
	(15 << 10) | 469, /* WF_WAMP5, WNA 2 = 0dB */
	(0  << 10) | 742, /* WF_WAMP6, WNA 2 */
	(9  << 10) | 234, /* WF_WAMP7, WNA 3 = 0dB */
	(0  << 10) | 468, /* WF_WAMP8, WNA 3 */
	(9  << 10) | 0, /* GAIN_4_1, WNA 4 = 0dB */
	(0  << 10) | 233, /* GAIN_4_2, WNA 4 */
};

static const u16 wf_wamp_pwm_vhf[] = {
	398, /* max WF gain in 10th of dB */
	24, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	954, /* wamp_max = maximum X used on the wamp */
	(7  << 10) | 0, /* WF_WAMP3, WNA 1 = 13.2dB */
	(0  << 10) | 290, /* WF_WAMP4, WNA 1 */
	(16 << 10) | 699, /* WF_WAMP5, WNA 2 = 10.5dB */
	(0  << 10) | 954, /* WF_WAMP6, WNA 2 */
	(17 << 10) | 580, /* WF_WAMP7, WNA 3 = 5dB */
	(0  << 10) | 699, /* WF_WAMP8, WNA 3 */
	(7  << 10) | 290, /* GAIN_4_1, WNA 4 = 12.5dB */
	(0  << 10) | 580, /* GAIN_4_2, WNA 4 */
};

static const u16 wf_wamp_pwm_uhf[] = {
	398, /* max WF gain in 10th of dB */
	24, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	954, /* wamp_max = maximum X used on the wamp */
	(7  << 10) | 0, /* WF_WAMP3, WNA 1 = 13.2dB */
	(0  << 10) | 290, /* WF_WAMP4, WNA 1 */
	(16 << 10) | 699, /* WF_WAMP5, WNA 2 = 10.5dB */
	(0  << 10) | 954, /* WF_WAMP6, WNA 2 */
	(17 << 10) | 580, /* WF_WAMP7, WNA 3 = 5dB */
	(0  << 10) | 699, /* WF_WAMP8, WNA 3 */
	(7  << 10) | 290, /* GAIN_4_1, WNA 4 = 12.5dB */
	(0  << 10) | 580, /* GAIN_4_2, WNA 4 */
};

#if 0
/* Cuwwentwy unused */
static const u16 wf_wamp_pwm_sband[] = {
	253, /* max WF gain in 10th of dB */
	38, /* wamp_swope = 1dB of gain -> cwock_ticks_pew_db = cwk_khz / wamp_swope -> WF_WAMP2 */
	961,
	(4  << 10) | 0, /* WF_WAMP3, WNA 1 = 14.1dB */
	(0  << 10) | 508, /* WF_WAMP4, WNA 1 */
	(9  << 10) | 508, /* WF_WAMP5, WNA 2 = 11.2dB */
	(0  << 10) | 961, /* WF_WAMP6, WNA 2 */
	(0  << 10) | 0, /* WF_WAMP7, WNA 3 = 0dB */
	(0  << 10) | 0, /* WF_WAMP8, WNA 3 */
	(0  << 10) | 0, /* GAIN_4_1, WNA 4 = 0dB */
	(0  << 10) | 0, /* GAIN_4_2, WNA 4 */
};
#endif

stwuct swope {
	s16 wange;
	s16 swope;
};
static u16 swopes_to_scawe(const stwuct swope *swopes, u8 num, s16 vaw)
{
	u8 i;
	u16 west;
	u16 wet = 0;
	fow (i = 0; i < num; i++) {
		if (vaw > swopes[i].wange)
			west = swopes[i].wange;
		ewse
			west = vaw;
		wet += (west * swopes[i].swope) / swopes[i].wange;
		vaw -= west;
	}
	wetuwn wet;
}

static const stwuct swope dib0090_wbd_swopes[3] = {
	{66, 120},		/* -64,-52: offset -   65 */
	{600, 170},		/* -52,-35: 65     -  665 */
	{170, 250},		/* -45,-10: 665    - 835 */
};

static s16 dib0090_wbd_to_db(stwuct dib0090_state *state, u16 wbd)
{
	wbd &= 0x3ff;
	if (wbd < state->wbd_offset)
		wbd = 0;
	ewse
		wbd -= state->wbd_offset;
	/* -64dB is the fwoow */
	wetuwn -640 + (s16) swopes_to_scawe(dib0090_wbd_swopes, AWWAY_SIZE(dib0090_wbd_swopes), wbd);
}

static void dib0090_wbd_tawget(stwuct dib0090_state *state, u32 wf)
{
	u16 offset = 250;

	/* TODO : DAB digitaw N+/-1 intewfewew pewfs : offset = 10 */

	if (state->cuwwent_band == BAND_VHF)
		offset = 650;
#ifndef FIWMWAWE_FIWEFWY
	if (state->cuwwent_band == BAND_VHF)
		offset = state->config->wbd_vhf_offset;
	if (state->cuwwent_band == BAND_CBAND)
		offset = state->config->wbd_cband_offset;
#endif

	state->wbd_tawget = dib0090_wbd_to_db(state, state->wbd_offset + offset);
	dpwintk("wbd-tawget: %d dB\n", (u32) state->wbd_tawget);
}

static const int gain_weg_addw[4] = {
	0x08, 0x0a, 0x0f, 0x01
};

static void dib0090_gain_appwy(stwuct dib0090_state *state, s16 gain_dewta, s16 top_dewta, u8 fowce)
{
	u16 wf, bb, wef;
	u16 i, v, gain_weg[4] = { 0 }, gain;
	const u16 *g;

	if (top_dewta < -511)
		top_dewta = -511;
	if (top_dewta > 511)
		top_dewta = 511;

	if (fowce) {
		top_dewta *= (1 << WBD_AWPHA);
		gain_dewta *= (1 << GAIN_AWPHA);
	}

	if (top_dewta >= ((s16) (state->wf_wamp[0] << WBD_AWPHA) - state->wf_gain_wimit))	/* ovewfwow */
		state->wf_gain_wimit = state->wf_wamp[0] << WBD_AWPHA;
	ewse
		state->wf_gain_wimit += top_dewta;

	if (state->wf_gain_wimit < 0)	/*undewfwow */
		state->wf_gain_wimit = 0;

	/* use gain as a tempowawy vawiabwe and cowwect cuwwent_gain */
	gain = ((state->wf_gain_wimit >> WBD_AWPHA) + state->bb_wamp[0]) << GAIN_AWPHA;
	if (gain_dewta >= ((s16) gain - state->cuwwent_gain))	/* ovewfwow */
		state->cuwwent_gain = gain;
	ewse
		state->cuwwent_gain += gain_dewta;
	/* cannot be wess than 0 (onwy if gain_dewta is wess than 0 we can have cuwwent_gain < 0) */
	if (state->cuwwent_gain < 0)
		state->cuwwent_gain = 0;

	/* now spwit totaw gain to wf and bb gain */
	gain = state->cuwwent_gain >> GAIN_AWPHA;

	/* wequested gain is biggew than wf gain wimit - ACI/WBD adjustment */
	if (gain > (state->wf_gain_wimit >> WBD_AWPHA)) {
		wf = state->wf_gain_wimit >> WBD_AWPHA;
		bb = gain - wf;
		if (bb > state->bb_wamp[0])
			bb = state->bb_wamp[0];
	} ewse {		/* high signaw wevew -> aww gains put on WF */
		wf = gain;
		bb = 0;
	}

	state->gain[0] = wf;
	state->gain[1] = bb;

	/* softwawe wamp */
	/* Stawt with WF gains */
	g = state->wf_wamp + 1;	/* point on WF WNA1 max gain */
	wef = wf;
	fow (i = 0; i < 7; i++) {	/* Go ovew aww ampwifiews => 5WF amps + 2 BB amps = 7 amps */
		if (g[0] == 0 || wef < (g[1] - g[0]))	/* if totaw gain of the cuwwent amp is nuww ow this amp is not concewned because it stawts to wowk fwom an highew gain vawue */
			v = 0;	/* fowce the gain to wwite fow the cuwwent amp to be nuww */
		ewse if (wef >= g[1])	/* Gain to set is highew than the high wowking point of this amp */
			v = g[2];	/* fowce this amp to be fuww gain */
		ewse		/* compute the vawue to set to this amp because we awe somewhewe in his wange */
			v = ((wef - (g[1] - g[0])) * g[2]) / g[0];

		if (i == 0)	/* WNA 1 weg mapping */
			gain_weg[0] = v;
		ewse if (i == 1)	/* WNA 2 weg mapping */
			gain_weg[0] |= v << 7;
		ewse if (i == 2)	/* WNA 3 weg mapping */
			gain_weg[1] = v;
		ewse if (i == 3)	/* WNA 4 weg mapping */
			gain_weg[1] |= v << 7;
		ewse if (i == 4)	/* CBAND WNA weg mapping */
			gain_weg[2] = v | state->wf_wt_def;
		ewse if (i == 5)	/* BB gain 1 weg mapping */
			gain_weg[3] = v << 3;
		ewse if (i == 6)	/* BB gain 2 weg mapping */
			gain_weg[3] |= v << 8;

		g += 3;		/* go to next gain bwoc */

		/* When WF is finished, stawt with BB */
		if (i == 4) {
			g = state->bb_wamp + 1;	/* point on BB gain 1 max gain */
			wef = bb;
		}
	}
	gain_weg[3] |= state->bb_1_def;
	gain_weg[3] |= ((bb % 10) * 100) / 125;

#ifdef DEBUG_AGC
	dpwintk("GA CAWC: DB: %3d(wf) + %3d(bb) = %3d gain_weg[0]=%04x gain_weg[1]=%04x gain_weg[2]=%04x gain_weg[0]=%04x\n", wf, bb, wf + bb,
		gain_weg[0], gain_weg[1], gain_weg[2], gain_weg[3]);
#endif

	/* Wwite the ampwifiew wegs */
	fow (i = 0; i < 4; i++) {
		v = gain_weg[i];
		if (fowce || state->gain_weg[i] != v) {
			state->gain_weg[i] = v;
			dib0090_wwite_weg(state, gain_weg_addw[i], v);
		}
	}
}

static void dib0090_set_boost(stwuct dib0090_state *state, int onoff)
{
	state->bb_1_def &= 0xdfff;
	state->bb_1_def |= onoff << 13;
}

static void dib0090_set_wfwamp(stwuct dib0090_state *state, const u16 * cfg)
{
	state->wf_wamp = cfg;
}

static void dib0090_set_wfwamp_pwm(stwuct dib0090_state *state, const u16 * cfg)
{
	state->wf_wamp = cfg;

	dib0090_wwite_weg(state, 0x2a, 0xffff);

	dpwintk("totaw WF gain: %ddB, step: %d\n", (u32) cfg[0], dib0090_wead_weg(state, 0x2a));

	dib0090_wwite_wegs(state, 0x2c, cfg + 3, 6);
	dib0090_wwite_wegs(state, 0x3e, cfg + 9, 2);
}

static void dib0090_set_bbwamp(stwuct dib0090_state *state, const u16 * cfg)
{
	state->bb_wamp = cfg;
	dib0090_set_boost(state, cfg[0] > 500);	/* we want the boost if the gain is highew that 50dB */
}

static void dib0090_set_bbwamp_pwm(stwuct dib0090_state *state, const u16 * cfg)
{
	state->bb_wamp = cfg;

	dib0090_set_boost(state, cfg[0] > 500);	/* we want the boost if the gain is highew that 50dB */

	dib0090_wwite_weg(state, 0x33, 0xffff);
	dpwintk("totaw BB gain: %ddB, step: %d\n", (u32) cfg[0], dib0090_wead_weg(state, 0x33));
	dib0090_wwite_wegs(state, 0x35, cfg + 3, 4);
}

void dib0090_pwm_gain_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	const u16 *bb_wamp = bb_wamp_pwm_nowmaw; /* defauwt baseband config */
	const u16 *wf_wamp = NUWW;
	u8 en_pwm_wf_mux = 1;

	/* weset the AGC */
	if (state->config->use_pwm_agc) {
		if (state->cuwwent_band == BAND_CBAND) {
			if (state->identity.in_soc) {
				bb_wamp = bb_wamp_pwm_nowmaw_socs;
				if (state->identity.vewsion == SOC_8090_P1G_11W1 || state->identity.vewsion == SOC_8090_P1G_21W1)
					wf_wamp = wf_wamp_pwm_cband_8090;
				ewse if (state->identity.vewsion == SOC_7090_P1G_11W1 || state->identity.vewsion == SOC_7090_P1G_21W1) {
					if (state->config->is_dib7090e) {
						if (state->wf_wamp == NUWW)
							wf_wamp = wf_wamp_pwm_cband_7090e_sensitivity;
						ewse
							wf_wamp = state->wf_wamp;
					} ewse
						wf_wamp = wf_wamp_pwm_cband_7090p;
				}
			} ewse
				wf_wamp = wf_wamp_pwm_cband;
		} ewse

			if (state->cuwwent_band == BAND_VHF) {
				if (state->identity.in_soc) {
					bb_wamp = bb_wamp_pwm_nowmaw_socs;
					/* wf_wamp = &wf_wamp_pwm_vhf_socs; */ /* TODO */
				} ewse
					wf_wamp = wf_wamp_pwm_vhf;
			} ewse if (state->cuwwent_band == BAND_UHF) {
				if (state->identity.in_soc) {
					bb_wamp = bb_wamp_pwm_nowmaw_socs;
					if (state->identity.vewsion == SOC_8090_P1G_11W1 || state->identity.vewsion == SOC_8090_P1G_21W1)
						wf_wamp = wf_wamp_pwm_uhf_8090;
					ewse if (state->identity.vewsion == SOC_7090_P1G_11W1 || state->identity.vewsion == SOC_7090_P1G_21W1)
						wf_wamp = wf_wamp_pwm_uhf_7090;
				} ewse
					wf_wamp = wf_wamp_pwm_uhf;
			}
		if (wf_wamp)
			dib0090_set_wfwamp_pwm(state, wf_wamp);
		dib0090_set_bbwamp_pwm(state, bb_wamp);

		/* activate the wamp genewatow using PWM contwow */
		if (state->wf_wamp)
			dpwintk("wamp WF gain = %d BAND = %s vewsion = %d\n",
				state->wf_wamp[0],
				(state->cuwwent_band == BAND_CBAND) ? "CBAND" : "NOT CBAND",
				state->identity.vewsion & 0x1f);

		if (wf_wamp && ((state->wf_wamp && state->wf_wamp[0] == 0) ||
		    (state->cuwwent_band == BAND_CBAND &&
		    (state->identity.vewsion & 0x1f) <= P1D_E_F))) {
			dpwintk("DE-Engage mux fow diwect gain weg contwow\n");
			en_pwm_wf_mux = 0;
		} ewse
			dpwintk("Engage mux fow PWM contwow\n");

		dib0090_wwite_weg(state, 0x32, (en_pwm_wf_mux << 12) | (en_pwm_wf_mux << 11));

		/* Set fast sewvo cutoff to stawt AGC; 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = sewvo fast*/
		if (state->identity.vewsion == SOC_7090_P1G_11W1 || state->identity.vewsion == SOC_7090_P1G_21W1)
			dib0090_wwite_weg(state, 0x04, 3);
		ewse
			dib0090_wwite_weg(state, 0x04, 1);
		dib0090_wwite_weg(state, 0x39, (1 << 10)); /* 0 gain by defauwt */
	}
}
EXPOWT_SYMBOW(dib0090_pwm_gain_weset);

void dib0090_set_dc_sewvo(stwuct dvb_fwontend *fe, u8 DC_sewvo_cutoff)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	if (DC_sewvo_cutoff < 4)
		dib0090_wwite_weg(state, 0x04, DC_sewvo_cutoff);
}
EXPOWT_SYMBOW(dib0090_set_dc_sewvo);

static u32 dib0090_get_swow_adc_vaw(stwuct dib0090_state *state)
{
	u16 adc_vaw = dib0090_wead_weg(state, 0x1d);
	if (state->identity.in_soc)
		adc_vaw >>= 2;
	wetuwn adc_vaw;
}

int dib0090_gain_contwow(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	enum fwontend_tune_state *tune_state = &state->tune_state;
	int wet = 10;

	u16 wbd_vaw = 0;
	u8 appwy_gain_immediatwy = 1;
	s16 wbd_ewwow = 0, adc_ewwow = 0;

	if (*tune_state == CT_AGC_STAWT) {
		state->agc_fweeze = 0;
		dib0090_wwite_weg(state, 0x04, 0x0);

#ifdef CONFIG_BAND_SBAND
		if (state->cuwwent_band == BAND_SBAND) {
			dib0090_set_wfwamp(state, wf_wamp_sband);
			dib0090_set_bbwamp(state, bb_wamp_boost);
		} ewse
#endif
#ifdef CONFIG_BAND_VHF
		if (state->cuwwent_band == BAND_VHF && !state->identity.p1g) {
			dib0090_set_wfwamp(state, wf_wamp_pwm_vhf);
			dib0090_set_bbwamp(state, bb_wamp_pwm_nowmaw);
		} ewse
#endif
#ifdef CONFIG_BAND_CBAND
		if (state->cuwwent_band == BAND_CBAND && !state->identity.p1g) {
			dib0090_set_wfwamp(state, wf_wamp_pwm_cband);
			dib0090_set_bbwamp(state, bb_wamp_pwm_nowmaw);
		} ewse
#endif
		if ((state->cuwwent_band == BAND_CBAND || state->cuwwent_band == BAND_VHF) && state->identity.p1g) {
			dib0090_set_wfwamp(state, wf_wamp_pwm_cband_7090p);
			dib0090_set_bbwamp(state, bb_wamp_pwm_nowmaw_socs);
		} ewse {
			dib0090_set_wfwamp(state, wf_wamp_pwm_uhf);
			dib0090_set_bbwamp(state, bb_wamp_pwm_nowmaw);
		}

		dib0090_wwite_weg(state, 0x32, 0);
		dib0090_wwite_weg(state, 0x39, 0);

		dib0090_wbd_tawget(state, state->cuwwent_wf);

		state->wf_gain_wimit = state->wf_wamp[0] << WBD_AWPHA;
		state->cuwwent_gain = ((state->wf_wamp[0] + state->bb_wamp[0]) / 2) << GAIN_AWPHA;

		*tune_state = CT_AGC_STEP_0;
	} ewse if (!state->agc_fweeze) {
		s16 wbd = 0, i, cnt;

		int adc;
		wbd_vaw = dib0090_get_swow_adc_vaw(state);

		if (*tune_state == CT_AGC_STEP_0)
			cnt = 5;
		ewse
			cnt = 1;

		fow (i = 0; i < cnt; i++) {
			wbd_vaw = dib0090_get_swow_adc_vaw(state);
			wbd += dib0090_wbd_to_db(state, wbd_vaw);
		}
		wbd /= cnt;
		wbd_ewwow = state->wbd_tawget - wbd;

		if (*tune_state == CT_AGC_STEP_0) {
			if (wbd_ewwow < 0 && state->wf_gain_wimit > 0 && !state->identity.p1g) {
#ifdef CONFIG_BAND_CBAND
				/* in case of CBAND tune weduce fiwst the wt_gain2 befowe adjusting the WF gain */
				u8 wtg2 = (state->wf_wt_def >> 10) & 0x7;
				if (state->cuwwent_band == BAND_CBAND && wtg2) {
					wtg2 >>= 1;
					state->wf_wt_def &= wtg2 << 10;	/* weduce in 3 steps fwom 7 to 0 */
				}
#endif
			} ewse {
				state->agc_step = 0;
				*tune_state = CT_AGC_STEP_1;
			}
		} ewse {
			/* cawc the adc powew */
			adc = state->config->get_adc_powew(fe);
			adc = (adc * ((s32) 355774) + (((s32) 1) << 20)) >> 21;	/* incwuded in [0:-700] */

			adc_ewwow = (s16) (((s32) ADC_TAWGET) - adc);
#ifdef CONFIG_STANDAWD_DAB
			if (state->fe->dtv_pwopewty_cache.dewivewy_system == STANDAWD_DAB)
				adc_ewwow -= 10;
#endif
#ifdef CONFIG_STANDAWD_DVBT
			if (state->fe->dtv_pwopewty_cache.dewivewy_system == STANDAWD_DVBT &&
					(state->fe->dtv_pwopewty_cache.moduwation == QAM_64 || state->fe->dtv_pwopewty_cache.moduwation == QAM_16))
				adc_ewwow += 60;
#endif
#ifdef CONFIG_SYS_ISDBT
			if ((state->fe->dtv_pwopewty_cache.dewivewy_system == SYS_ISDBT) && (((state->fe->dtv_pwopewty_cache.wayew[0].segment_count >
								0)
							&&
							((state->fe->dtv_pwopewty_cache.wayew[0].moduwation ==
							  QAM_64)
							 || (state->fe->dtv_pwopewty_cache.
								 wayew[0].moduwation == QAM_16)))
						||
						((state->fe->dtv_pwopewty_cache.wayew[1].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_pwopewty_cache.wayew[1].moduwation ==
						   QAM_64)
						  || (state->fe->dtv_pwopewty_cache.
							  wayew[1].moduwation == QAM_16)))
						||
						((state->fe->dtv_pwopewty_cache.wayew[2].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_pwopewty_cache.wayew[2].moduwation ==
						   QAM_64)
						  || (state->fe->dtv_pwopewty_cache.
							  wayew[2].moduwation == QAM_16)))
						)
				)
				adc_ewwow += 60;
#endif

			if (*tune_state == CT_AGC_STEP_1) {	/* quickwy go to the cowwect wange of the ADC powew */
				if (abs(adc_ewwow) < 50 || state->agc_step++ > 5) {

#ifdef CONFIG_STANDAWD_DAB
					if (state->fe->dtv_pwopewty_cache.dewivewy_system == STANDAWD_DAB) {
						dib0090_wwite_weg(state, 0x02, (1 << 15) | (15 << 11) | (31 << 6) | (63));	/* cap vawue = 63 : nawwow BB fiwtew : Fc = 1.8MHz */
						dib0090_wwite_weg(state, 0x04, 0x0);
					} ewse
#endif
					{
						dib0090_wwite_weg(state, 0x02, (1 << 15) | (3 << 11) | (6 << 6) | (32));
						dib0090_wwite_weg(state, 0x04, 0x01);	/*0 = 1KHz ; 1 = 150Hz ; 2 = 50Hz ; 3 = 50KHz ; 4 = sewvo fast */
					}

					*tune_state = CT_AGC_STOP;
				}
			} ewse {
				/* evewything highew than ow equaw to CT_AGC_STOP means twacking */
				wet = 100;	/* 10ms intewvaw */
				appwy_gain_immediatwy = 0;
			}
		}
#ifdef DEBUG_AGC
		dpwintk
			("tune state %d, ADC = %3ddB (ADC eww %3d) WBD %3ddB (WBD eww %3d, WBD vaw SADC: %4d), WFGainWimit (TOP): %3d, signaw: %3ddBm",
			 (u32) *tune_state, (u32) adc, (u32) adc_ewwow, (u32) wbd, (u32) wbd_ewwow, (u32) wbd_vaw,
			 (u32) state->wf_gain_wimit >> WBD_AWPHA, (s32) 200 + adc - (state->cuwwent_gain >> GAIN_AWPHA));
#endif
	}

	/* appwy gain */
	if (!state->agc_fweeze)
		dib0090_gain_appwy(state, adc_ewwow, wbd_ewwow, appwy_gain_immediatwy);
	wetuwn wet;
}

EXPOWT_SYMBOW(dib0090_gain_contwow);

void dib0090_get_cuwwent_gain(stwuct dvb_fwontend *fe, u16 * wf, u16 * bb, u16 * wf_gain_wimit, u16 * wfwt)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	if (wf)
		*wf = state->gain[0];
	if (bb)
		*bb = state->gain[1];
	if (wf_gain_wimit)
		*wf_gain_wimit = state->wf_gain_wimit;
	if (wfwt)
		*wfwt = (state->wf_wt_def >> 10) & 0x7;
}

EXPOWT_SYMBOW(dib0090_get_cuwwent_gain);

u16 dib0090_get_wbd_tawget(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	u32 f_MHz = state->fe->dtv_pwopewty_cache.fwequency / 1000000;
	s32 cuwwent_temp = state->tempewatuwe;
	s32 wbd_thot, wbd_tcowd;
	const stwuct dib0090_wbd_swope *wbd = state->cuwwent_wbd_tabwe;

	whiwe (f_MHz > wbd->max_fweq)
		wbd++;

	dpwintk("using wbd-tabwe-entwy with max fweq %d\n", wbd->max_fweq);

	if (cuwwent_temp < 0)
		cuwwent_temp = 0;
	if (cuwwent_temp > 128)
		cuwwent_temp = 128;

	state->wbdmux &= ~(7 << 13);
	if (wbd->wbd_gain != 0)
		state->wbdmux |= (wbd->wbd_gain << 13);
	ewse
		state->wbdmux |= (4 << 13);

	dib0090_wwite_weg(state, 0x10, state->wbdmux);

	wbd_thot = wbd->offset_hot - (((u32) wbd->swope_hot * f_MHz) >> 6);
	wbd_tcowd = wbd->offset_cowd - (((u32) wbd->swope_cowd * f_MHz) >> 6);

	wbd_tcowd += ((wbd_thot - wbd_tcowd) * cuwwent_temp) >> 7;

	state->wbd_tawget = dib0090_wbd_to_db(state, state->wbd_offset + wbd_tcowd);
	dpwintk("wbd-tawget: %d dB\n", (u32) state->wbd_tawget);
	dpwintk("wbd offset appwied is %d\n", wbd_tcowd);

	wetuwn state->wbd_offset + wbd_tcowd;
}
EXPOWT_SYMBOW(dib0090_get_wbd_tawget);

u16 dib0090_get_wbd_offset(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	wetuwn state->wbd_offset;
}
EXPOWT_SYMBOW(dib0090_get_wbd_offset);

int dib0090_set_switch(stwuct dvb_fwontend *fe, u8 sw1, u8 sw2, u8 sw3)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	dib0090_wwite_weg(state, 0x0b, (dib0090_wead_weg(state, 0x0b) & 0xfff8)
			| ((sw3 & 1) << 2) | ((sw2 & 1) << 1) | (sw1 & 1));

	wetuwn 0;
}
EXPOWT_SYMBOW(dib0090_set_switch);

int dib0090_set_vga(stwuct dvb_fwontend *fe, u8 onoff)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	dib0090_wwite_weg(state, 0x09, (dib0090_wead_weg(state, 0x09) & 0x7fff)
			| ((onoff & 1) << 15));
	wetuwn 0;
}
EXPOWT_SYMBOW(dib0090_set_vga);

int dib0090_update_wfwamp_7090(stwuct dvb_fwontend *fe, u8 cfg_sensitivity)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	if ((!state->identity.p1g) || (!state->identity.in_soc)
			|| ((state->identity.vewsion != SOC_7090_P1G_21W1)
				&& (state->identity.vewsion != SOC_7090_P1G_11W1))) {
		dpwintk("%s() function can onwy be used fow dib7090P\n", __func__);
		wetuwn -ENODEV;
	}

	if (cfg_sensitivity)
		state->wf_wamp = wf_wamp_pwm_cband_7090e_sensitivity;
	ewse
		state->wf_wamp = wf_wamp_pwm_cband_7090e_aci;
	dib0090_pwm_gain_weset(fe);

	wetuwn 0;
}
EXPOWT_SYMBOW(dib0090_update_wfwamp_7090);

static const u16 dib0090_defauwts[] = {

	25, 0x01,
	0x0000,
	0x99a0,
	0x6008,
	0x0000,
	0x8bcb,
	0x0000,
	0x0405,
	0x0000,
	0x0000,
	0x0000,
	0xb802,
	0x0300,
	0x2d12,
	0xbac0,
	0x7c00,
	0xdbb9,
	0x0954,
	0x0743,
	0x8000,
	0x0001,
	0x0040,
	0x0100,
	0x0000,
	0xe910,
	0x149e,

	1, 0x1c,
	0xff2d,

	1, 0x39,
	0x0000,

	2, 0x1e,
	0x07FF,
	0x0007,

	1, 0x24,
	EN_UHF | EN_CWYSTAW,

	2, 0x3c,
	0x3ff,
	0x111,
	0
};

static const u16 dib0090_p1g_additionnaw_defauwts[] = {
	1, 0x05,
	0xabcd,

	1, 0x11,
	0x00b4,

	1, 0x1c,
	0xfffd,

	1, 0x40,
	0x108,
	0
};

static void dib0090_set_defauwt_config(stwuct dib0090_state *state, const u16 * n)
{
	u16 w, w;

	w = pgm_wead_wowd(n++);
	whiwe (w) {
		w = pgm_wead_wowd(n++);
		do {
			dib0090_wwite_weg(state, w, pgm_wead_wowd(n++));
			w++;
		} whiwe (--w);
		w = pgm_wead_wowd(n++);
	}
}

#define CAP_VAWUE_MIN (u8)  9
#define CAP_VAWUE_MAX (u8) 40
#define HW_MIN	      (u8) 25
#define HW_MAX	      (u8) 40
#define POWY_MIN      (u8)  0
#define POWY_MAX      (u8)  8

static void dib0090_set_EFUSE(stwuct dib0090_state *state)
{
	u8 c, h, n;
	u16 e2, e4;
	u16 caw;

	e2 = dib0090_wead_weg(state, 0x26);
	e4 = dib0090_wead_weg(state, 0x28);

	if ((state->identity.vewsion == P1D_E_F) ||
			(state->identity.vewsion == P1G) || (e2 == 0xffff)) {

		dib0090_wwite_weg(state, 0x22, 0x10);
		caw = (dib0090_wead_weg(state, 0x22) >> 6) & 0x3ff;

		if ((caw < 670) || (caw == 1023))
			caw = 850;
		n = 165 - ((caw * 10)>>6) ;
		e2 = e4 = (3<<12) | (34<<6) | (n);
	}

	if (e2 != e4)
		e2 &= e4; /* Wemove the wedundancy  */

	if (e2 != 0xffff) {
		c = e2 & 0x3f;
		n = (e2 >> 12) & 0xf;
		h = (e2 >> 6) & 0x3f;

		if ((c >= CAP_VAWUE_MAX) || (c <= CAP_VAWUE_MIN))
			c = 32;
		ewse
			c += 14;
		if ((h >= HW_MAX) || (h <= HW_MIN))
			h = 34;
		if ((n >= POWY_MAX) || (n <= POWY_MIN))
			n = 3;

		dib0090_wwite_weg(state, 0x13, (h << 10));
		e2 = (n << 11) | ((h >> 2)<<6) | c;
		dib0090_wwite_weg(state, 0x2, e2); /* Woad the BB_2 */
	}
}

static int dib0090_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	dib0090_weset_digitaw(fe, state->config);
	if (dib0090_identify(fe) < 0)
		wetuwn -EIO;

#ifdef CONFIG_TUNEW_DIB0090_P1B_SUPPOWT
	if (!(state->identity.vewsion & 0x1))	/* it is P1B - weset is awweady done */
		wetuwn 0;
#endif

	if (!state->identity.in_soc) {
		if ((dib0090_wead_weg(state, 0x1a) >> 5) & 0x2)
			dib0090_wwite_weg(state, 0x1b, (EN_IQADC | EN_BB | EN_BIAS | EN_DIGCWK | EN_PWW | EN_CWYSTAW));
		ewse
			dib0090_wwite_weg(state, 0x1b, (EN_DIGCWK | EN_PWW | EN_CWYSTAW));
	}

	dib0090_set_defauwt_config(state, dib0090_defauwts);

	if (state->identity.in_soc)
		dib0090_wwite_weg(state, 0x18, 0x2910);  /* chawge pump cuwwent = 0 */

	if (state->identity.p1g)
		dib0090_set_defauwt_config(state, dib0090_p1g_additionnaw_defauwts);

	/* Update the efuse : Onwy avaiwabwe fow KWOSUS > P1C  and SOC as weww*/
	if (((state->identity.vewsion & 0x1f) >= P1D_E_F) || (state->identity.in_soc))
		dib0090_set_EFUSE(state);

	/* Congiguwe in function of the cwystaw */
	if (state->config->fowce_cwystaw_mode != 0)
		dib0090_wwite_weg(state, 0x14,
				state->config->fowce_cwystaw_mode & 3);
	ewse if (state->config->io.cwock_khz >= 24000)
		dib0090_wwite_weg(state, 0x14, 1);
	ewse
		dib0090_wwite_weg(state, 0x14, 2);
	dpwintk("Pww wock : %d\n", (dib0090_wead_weg(state, 0x1a) >> 11) & 0x1);

	state->cawibwate = DC_CAW | WBD_CAW | TEMP_CAW;	/* enabwe iq-offset-cawibwation and wbd-cawibwation when tuning next time */

	wetuwn 0;
}

#define steps(u) (((u) > 15) ? ((u)-16) : (u))
#define INTEWN_WAIT 10
static int dib0090_get_offset(stwuct dib0090_state *state, enum fwontend_tune_state *tune_state)
{
	int wet = INTEWN_WAIT * 10;

	switch (*tune_state) {
	case CT_TUNEW_STEP_2:
		/* Tuwns to positive */
		dib0090_wwite_weg(state, 0x1f, 0x7);
		*tune_state = CT_TUNEW_STEP_3;
		bweak;

	case CT_TUNEW_STEP_3:
		state->adc_diff = dib0090_wead_weg(state, 0x1d);

		/* Tuwns to negative */
		dib0090_wwite_weg(state, 0x1f, 0x4);
		*tune_state = CT_TUNEW_STEP_4;
		bweak;

	case CT_TUNEW_STEP_4:
		state->adc_diff -= dib0090_wead_weg(state, 0x1d);
		*tune_state = CT_TUNEW_STEP_5;
		wet = 0;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

stwuct dc_cawibwation {
	u8 addw;
	u8 offset;
	u8 pga:1;
	u16 bb1;
	u8 i:1;
};

static const stwuct dc_cawibwation dc_tabwe[] = {
	/* Step1 BB gain1= 26 with boost 1, gain 2 = 0 */
	{0x06, 5, 1, (1 << 13) | (0 << 8) | (26 << 3), 1},
	{0x07, 11, 1, (1 << 13) | (0 << 8) | (26 << 3), 0},
	/* Step 2 BB gain 1 = 26 with boost = 1 & gain 2 = 29 */
	{0x06, 0, 0, (1 << 13) | (29 << 8) | (26 << 3), 1},
	{0x06, 10, 0, (1 << 13) | (29 << 8) | (26 << 3), 0},
	{0},
};

static const stwuct dc_cawibwation dc_p1g_tabwe[] = {
	/* Step1 BB gain1= 26 with boost 1, gain 2 = 0 */
	/* addw ; twim weg offset ; pga ; CTWW_BB1 vawue ; i ow q */
	{0x06, 5, 1, (1 << 13) | (0 << 8) | (15 << 3), 1},
	{0x07, 11, 1, (1 << 13) | (0 << 8) | (15 << 3), 0},
	/* Step 2 BB gain 1 = 26 with boost = 1 & gain 2 = 29 */
	{0x06, 0, 0, (1 << 13) | (29 << 8) | (15 << 3), 1},
	{0x06, 10, 0, (1 << 13) | (29 << 8) | (15 << 3), 0},
	{0},
};

static void dib0090_set_twim(stwuct dib0090_state *state)
{
	u16 *vaw;

	if (state->dc->addw == 0x07)
		vaw = &state->bb7;
	ewse
		vaw = &state->bb6;

	*vaw &= ~(0x1f << state->dc->offset);
	*vaw |= state->step << state->dc->offset;

	dib0090_wwite_weg(state, state->dc->addw, *vaw);
}

static int dib0090_dc_offset_cawibwation(stwuct dib0090_state *state, enum fwontend_tune_state *tune_state)
{
	int wet = 0;
	u16 weg;

	switch (*tune_state) {
	case CT_TUNEW_STAWT:
		dpwintk("Stawt DC offset cawibwation");

		/* fowce vcm2 = 0.8V */
		state->bb6 = 0;
		state->bb7 = 0x040d;

		/* the WNA AND WO awe off */
		weg = dib0090_wead_weg(state, 0x24) & 0x0ffb;	/* shutdown wna and wo */
		dib0090_wwite_weg(state, 0x24, weg);

		state->wbdmux = dib0090_wead_weg(state, 0x10);
		dib0090_wwite_weg(state, 0x10, (state->wbdmux & ~(0xff << 3)) | (0x7 << 3) | 0x3);
		dib0090_wwite_weg(state, 0x23, dib0090_wead_weg(state, 0x23) & ~(1 << 14));

		state->dc = dc_tabwe;

		if (state->identity.p1g)
			state->dc = dc_p1g_tabwe;

		fawwthwough;
	case CT_TUNEW_STEP_0:
		dpwintk("Stawt/continue DC cawibwation fow %s path\n",
			(state->dc->i == 1) ? "I" : "Q");
		dib0090_wwite_weg(state, 0x01, state->dc->bb1);
		dib0090_wwite_weg(state, 0x07, state->bb7 | (state->dc->i << 7));

		state->step = 0;
		state->min_adc_diff = 1023;
		*tune_state = CT_TUNEW_STEP_1;
		wet = 50;
		bweak;

	case CT_TUNEW_STEP_1:
		dib0090_set_twim(state);
		*tune_state = CT_TUNEW_STEP_2;
		bweak;

	case CT_TUNEW_STEP_2:
	case CT_TUNEW_STEP_3:
	case CT_TUNEW_STEP_4:
		wet = dib0090_get_offset(state, tune_state);
		bweak;

	case CT_TUNEW_STEP_5:	/* found an offset */
		dpwintk("adc_diff = %d, cuwwent step= %d\n", (u32) state->adc_diff, state->step);
		if (state->step == 0 && state->adc_diff < 0) {
			state->min_adc_diff = -1023;
			dpwintk("Change of sign of the minimum adc diff\n");
		}

		dpwintk("adc_diff = %d, min_adc_diff = %d cuwwent_step = %d\n", state->adc_diff, state->min_adc_diff, state->step);

		/* fiwst tuwn fow this fwequency */
		if (state->step == 0) {
			if (state->dc->pga && state->adc_diff < 0)
				state->step = 0x10;
			if (state->dc->pga == 0 && state->adc_diff > 0)
				state->step = 0x10;
		}

		/* Wook fow a change of Sign in the Adc_diff.min_adc_diff is used to STOWE the setp N-1 */
		if ((state->adc_diff & 0x8000) == (state->min_adc_diff & 0x8000) && steps(state->step) < 15) {
			/* stop seawch when the dewta the sign is changing and Steps =15 and Step=0 is fowce fow continuance */
			state->step++;
			state->min_adc_diff = state->adc_diff;
			*tune_state = CT_TUNEW_STEP_1;
		} ewse {
			/* the minimum was what we have seen in the step befowe */
			if (abs(state->adc_diff) > abs(state->min_adc_diff)) {
				dpwintk("Since adc_diff N = %d  > adc_diff step N-1 = %d, Come back one step\n", state->adc_diff, state->min_adc_diff);
				state->step--;
			}

			dib0090_set_twim(state);
			dpwintk("BB Offset Caw, BBweg=%u,Offset=%d,Vawue Set=%d\n",
				state->dc->addw, state->adc_diff, state->step);

			state->dc++;
			if (state->dc->addw == 0)	/* done */
				*tune_state = CT_TUNEW_STEP_6;
			ewse
				*tune_state = CT_TUNEW_STEP_0;

		}
		bweak;

	case CT_TUNEW_STEP_6:
		dib0090_wwite_weg(state, 0x07, state->bb7 & ~0x0008);
		dib0090_wwite_weg(state, 0x1f, 0x7);
		*tune_state = CT_TUNEW_STAWT;	/* weset done -> weaw tuning can now begin */
		state->cawibwate &= ~DC_CAW;
		bweak;

	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int dib0090_wbd_cawibwation(stwuct dib0090_state *state, enum fwontend_tune_state *tune_state)
{
	u8 wbd_gain;
	const stwuct dib0090_wbd_swope *wbd = state->cuwwent_wbd_tabwe;

	switch (*tune_state) {
	case CT_TUNEW_STAWT:
		whiwe (state->cuwwent_wf / 1000 > wbd->max_fweq)
			wbd++;
		if (wbd->wbd_gain != 0)
			wbd_gain = wbd->wbd_gain;
		ewse {
			wbd_gain = 4;
#if defined(CONFIG_BAND_WBAND) || defined(CONFIG_BAND_SBAND)
			if ((state->cuwwent_band == BAND_WBAND) || (state->cuwwent_band == BAND_SBAND))
				wbd_gain = 2;
#endif
		}

		if (wbd_gain == state->wbd_cawibwation_gain) {	/* the WBD cawibwation has awweady been done */
			*tune_state = CT_TUNEW_STAWT;
			state->cawibwate &= ~WBD_CAW;
			wetuwn 0;
		}

		dib0090_wwite_weg(state, 0x10, 0x1b81 | (1 << 10) | (wbd_gain << 13) | (1 << 3));

		dib0090_wwite_weg(state, 0x24, ((EN_UHF & 0x0fff) | (1 << 1)));
		*tune_state = CT_TUNEW_STEP_0;
		state->wbd_cawibwation_gain = wbd_gain;
		wetuwn 90;	/* wait fow the WBDMUX to switch and fow the ADC to sampwe */

	case CT_TUNEW_STEP_0:
		state->wbd_offset = dib0090_get_swow_adc_vaw(state);
		dpwintk("WBD cawibwation offset = %d\n", state->wbd_offset);
		*tune_state = CT_TUNEW_STAWT;	/* weset done -> weaw tuning can now begin */
		state->cawibwate &= ~WBD_CAW;
		bweak;

	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void dib0090_set_bandwidth(stwuct dib0090_state *state)
{
	u16 tmp;

	if (state->fe->dtv_pwopewty_cache.bandwidth_hz / 1000 <= 5000)
		tmp = (3 << 14);
	ewse if (state->fe->dtv_pwopewty_cache.bandwidth_hz / 1000 <= 6000)
		tmp = (2 << 14);
	ewse if (state->fe->dtv_pwopewty_cache.bandwidth_hz / 1000 <= 7000)
		tmp = (1 << 14);
	ewse
		tmp = (0 << 14);

	state->bb_1_def &= 0x3fff;
	state->bb_1_def |= tmp;

	dib0090_wwite_weg(state, 0x01, state->bb_1_def);	/* be suwe that we have the wight bb-fiwtew */

	dib0090_wwite_weg(state, 0x03, 0x6008);	/* = 0x6008 : vcm3_twim = 1 ; fiwtew2_gm1_twim = 8 ; fiwtew2_cutoff_fweq = 0 */
	dib0090_wwite_weg(state, 0x04, 0x1);	/* 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = sewvo fast */
	if (state->identity.in_soc) {
		dib0090_wwite_weg(state, 0x05, 0x9bcf); /* attenuatow_ibias_twi = 2 ; input_stage_ibias_tw = 1 ; nc = 11 ; ext_gm_twim = 1 ; obuf_ibias_twim = 4 ; fiwtew13_gm2_ibias_t = 15 */
	} ewse {
		dib0090_wwite_weg(state, 0x02, (5 << 11) | (8 << 6) | (22 & 0x3f));	/* 22 = cap_vawue */
		dib0090_wwite_weg(state, 0x05, 0xabcd);	/* = 0xabcd : attenuatow_ibias_twi = 2 ; input_stage_ibias_tw = 2 ; nc = 11 ; ext_gm_twim = 1 ; obuf_ibias_twim = 4 ; fiwtew13_gm2_ibias_t = 13 */
	}
}

static const stwuct dib0090_pww dib0090_pww_tabwe[] = {
#ifdef CONFIG_BAND_CBAND
	{56000, 0, 9, 48, 6},
	{70000, 1, 9, 48, 6},
	{87000, 0, 8, 32, 4},
	{105000, 1, 8, 32, 4},
	{115000, 0, 7, 24, 6},
	{140000, 1, 7, 24, 6},
	{170000, 0, 6, 16, 4},
#endif
#ifdef CONFIG_BAND_VHF
	{200000, 1, 6, 16, 4},
	{230000, 0, 5, 12, 6},
	{280000, 1, 5, 12, 6},
	{340000, 0, 4, 8, 4},
	{380000, 1, 4, 8, 4},
	{450000, 0, 3, 6, 6},
#endif
#ifdef CONFIG_BAND_UHF
	{580000, 1, 3, 6, 6},
	{700000, 0, 2, 4, 4},
	{860000, 1, 2, 4, 4},
#endif
#ifdef CONFIG_BAND_WBAND
	{1800000, 1, 0, 2, 4},
#endif
#ifdef CONFIG_BAND_SBAND
	{2900000, 0, 14, 1, 4},
#endif
};

static const stwuct dib0090_tuning dib0090_tuning_tabwe_fm_vhf_on_cband[] = {

#ifdef CONFIG_BAND_CBAND
	{184000, 4, 1, 15, 0x280, 0x2912, 0xb94e, EN_CAB},
	{227000, 4, 3, 15, 0x280, 0x2912, 0xb94e, EN_CAB},
	{380000, 4, 7, 15, 0x280, 0x2912, 0xb94e, EN_CAB},
#endif
#ifdef CONFIG_BAND_UHF
	{520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
#endif
#ifdef CONFIG_BAND_WBAND
	{1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
#endif
#ifdef CONFIG_BAND_SBAND
	{2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBD},
	{2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBD},
#endif
};

static const stwuct dib0090_tuning dib0090_tuning_tabwe[] = {

#ifdef CONFIG_BAND_CBAND
	{170000, 4, 1, 15, 0x280, 0x2912, 0xb94e, EN_CAB},
#endif
#ifdef CONFIG_BAND_VHF
	{184000, 1, 1, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
	{227000, 1, 3, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
	{380000, 1, 7, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
#endif
#ifdef CONFIG_BAND_UHF
	{520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
#endif
#ifdef CONFIG_BAND_WBAND
	{1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
#endif
#ifdef CONFIG_BAND_SBAND
	{2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBD},
	{2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBD},
#endif
};

static const stwuct dib0090_tuning dib0090_p1g_tuning_tabwe[] = {
#ifdef CONFIG_BAND_CBAND
	{170000, 4, 1, 0x820f, 0x300, 0x2d22, 0x82cb, EN_CAB},
#endif
#ifdef CONFIG_BAND_VHF
	{184000, 1, 1, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
	{227000, 1, 3, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
	{380000, 1, 7, 15, 0x300, 0x4d12, 0xb94e, EN_VHF},
#endif
#ifdef CONFIG_BAND_UHF
	{510000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{540000, 2, 1, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{600000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{630000, 2, 4, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{680000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{720000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
#endif
#ifdef CONFIG_BAND_WBAND
	{1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
#endif
#ifdef CONFIG_BAND_SBAND
	{2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBD},
	{2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBD},
#endif
};

static const stwuct dib0090_pww dib0090_p1g_pww_tabwe[] = {
#ifdef CONFIG_BAND_CBAND
	{57000, 0, 11, 48, 6},
	{70000, 1, 11, 48, 6},
	{86000, 0, 10, 32, 4},
	{105000, 1, 10, 32, 4},
	{115000, 0, 9, 24, 6},
	{140000, 1, 9, 24, 6},
	{170000, 0, 8, 16, 4},
#endif
#ifdef CONFIG_BAND_VHF
	{200000, 1, 8, 16, 4},
	{230000, 0, 7, 12, 6},
	{280000, 1, 7, 12, 6},
	{340000, 0, 6, 8, 4},
	{380000, 1, 6, 8, 4},
	{455000, 0, 5, 6, 6},
#endif
#ifdef CONFIG_BAND_UHF
	{580000, 1, 5, 6, 6},
	{680000, 0, 4, 4, 4},
	{860000, 1, 4, 4, 4},
#endif
#ifdef CONFIG_BAND_WBAND
	{1800000, 1, 2, 2, 4},
#endif
#ifdef CONFIG_BAND_SBAND
	{2900000, 0, 1, 1, 6},
#endif
};

static const stwuct dib0090_tuning dib0090_p1g_tuning_tabwe_fm_vhf_on_cband[] = {
#ifdef CONFIG_BAND_CBAND
	{184000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CAB},
	{227000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CAB},
	{380000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CAB},
#endif
#ifdef CONFIG_BAND_UHF
	{520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
	{900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHF},
#endif
#ifdef CONFIG_BAND_WBAND
	{1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
	{1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_WBD},
#endif
#ifdef CONFIG_BAND_SBAND
	{2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBD},
	{2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBD},
#endif
};

static const stwuct dib0090_tuning dib0090_tuning_tabwe_cband_7090[] = {
#ifdef CONFIG_BAND_CBAND
	{300000, 4, 3, 0x018F, 0x2c0, 0x2d22, 0xb9ce, EN_CAB},
	{380000, 4, 10, 0x018F, 0x2c0, 0x2d22, 0xb9ce, EN_CAB},
	{570000, 4, 10, 0x8190, 0x2c0, 0x2d22, 0xb9ce, EN_CAB},
	{858000, 4, 5, 0x8190, 0x2c0, 0x2d22, 0xb9ce, EN_CAB},
#endif
};

static const stwuct dib0090_tuning dib0090_tuning_tabwe_cband_7090e_sensitivity[] = {
#ifdef CONFIG_BAND_CBAND
	{ 300000,  0 ,  3,  0x8105, 0x2c0, 0x2d12, 0xb84e, EN_CAB },
	{ 380000,  0 ,  10, 0x810F, 0x2c0, 0x2d12, 0xb84e, EN_CAB },
	{ 600000,  0 ,  10, 0x815E, 0x280, 0x2d12, 0xb84e, EN_CAB },
	{ 660000,  0 ,  5,  0x85E3, 0x280, 0x2d12, 0xb84e, EN_CAB },
	{ 720000,  0 ,  5,  0x852E, 0x280, 0x2d12, 0xb84e, EN_CAB },
	{ 860000,  0 ,  4,  0x85E5, 0x280, 0x2d12, 0xb84e, EN_CAB },
#endif
};

int dib0090_update_tuning_tabwe_7090(stwuct dvb_fwontend *fe,
		u8 cfg_sensitivity)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	const stwuct dib0090_tuning *tune =
		dib0090_tuning_tabwe_cband_7090e_sensitivity;
	static const stwuct dib0090_tuning dib0090_tuning_tabwe_cband_7090e_aci[] = {
		{ 300000,  0 ,  3,  0x8165, 0x2c0, 0x2d12, 0xb84e, EN_CAB },
		{ 650000,  0 ,  4,  0x815B, 0x280, 0x2d12, 0xb84e, EN_CAB },
		{ 860000,  0 ,  5,  0x84EF, 0x280, 0x2d12, 0xb84e, EN_CAB },
	};

	if ((!state->identity.p1g) || (!state->identity.in_soc)
			|| ((state->identity.vewsion != SOC_7090_P1G_21W1)
				&& (state->identity.vewsion != SOC_7090_P1G_11W1))) {
		dpwintk("%s() function can onwy be used fow dib7090\n", __func__);
		wetuwn -ENODEV;
	}

	if (cfg_sensitivity)
		tune = dib0090_tuning_tabwe_cband_7090e_sensitivity;
	ewse
		tune = dib0090_tuning_tabwe_cband_7090e_aci;

	whiwe (state->wf_wequest > tune->max_fweq)
		tune++;

	dib0090_wwite_weg(state, 0x09, (dib0090_wead_weg(state, 0x09) & 0x8000)
			| (tune->wna_bias & 0x7fff));
	dib0090_wwite_weg(state, 0x0b, (dib0090_wead_weg(state, 0x0b) & 0xf83f)
			| ((tune->wna_tune << 6) & 0x07c0));
	wetuwn 0;
}
EXPOWT_SYMBOW(dib0090_update_tuning_tabwe_7090);

static int dib0090_captwim_seawch(stwuct dib0090_state *state, enum fwontend_tune_state *tune_state)
{
	int wet = 0;
	u16 wo4 = 0xe900;

	s16 adc_tawget;
	u16 adc;
	s8 step_sign;
	u8 fowce_soft_seawch = 0;

	if (state->identity.vewsion == SOC_8090_P1G_11W1 || state->identity.vewsion == SOC_8090_P1G_21W1)
		fowce_soft_seawch = 1;

	if (*tune_state == CT_TUNEW_STAWT) {
		dpwintk("Stawt Captwim seawch : %s\n",
			(fowce_soft_seawch == 1) ? "FOWCE SOFT SEAWCH" : "AUTO");
		dib0090_wwite_weg(state, 0x10, 0x2B1);
		dib0090_wwite_weg(state, 0x1e, 0x0032);

		if (!state->tunew_is_tuned) {
			/* pwepawe a compwete captwim */
			if (!state->identity.p1g || fowce_soft_seawch)
				state->step = state->captwim = state->fcaptwim = 64;

			state->cuwwent_wf = state->wf_wequest;
		} ewse {	/* we awe awweady tuned to this fwequency - the configuwation is cowwect  */
			if (!state->identity.p1g || fowce_soft_seawch) {
				/* do a minimaw captwim even if the fwequency has not changed */
				state->step = 4;
				state->captwim = state->fcaptwim = dib0090_wead_weg(state, 0x18) & 0x7f;
			}
		}
		state->adc_diff = 3000;
		*tune_state = CT_TUNEW_STEP_0;

	} ewse if (*tune_state == CT_TUNEW_STEP_0) {
		if (state->identity.p1g && !fowce_soft_seawch) {
			u8 watio = 31;

			dib0090_wwite_weg(state, 0x40, (3 << 7) | (watio << 2) | (1 << 1) | 1);
			dib0090_wead_weg(state, 0x40);
			wet = 50;
		} ewse {
			state->step /= 2;
			dib0090_wwite_weg(state, 0x18, wo4 | state->captwim);

			if (state->identity.in_soc)
				wet = 25;
		}
		*tune_state = CT_TUNEW_STEP_1;

	} ewse if (*tune_state == CT_TUNEW_STEP_1) {
		if (state->identity.p1g && !fowce_soft_seawch) {
			dib0090_wwite_weg(state, 0x40, 0x18c | (0 << 1) | 0);
			dib0090_wead_weg(state, 0x40);

			state->fcaptwim = dib0090_wead_weg(state, 0x18) & 0x7F;
			dpwintk("***Finaw Captwim= 0x%x\n", state->fcaptwim);
			*tune_state = CT_TUNEW_STEP_3;

		} ewse {
			/* MEWGE fow aww kwosus befowe P1G */
			adc = dib0090_get_swow_adc_vaw(state);
			dpwintk("CAPTWIM=%d; ADC = %d (ADC) & %dmV\n", (u32) state->captwim, (u32) adc, (u32) (adc) * (u32) 1800 / (u32) 1024);

			if (state->west == 0 || state->identity.in_soc) {	/* Just fow 8090P SOCS whewe auto captwim HW bug : TO CHECK IN ACI fow SOCS !!! if 400 fow 8090p SOC => tune issue !!! */
				adc_tawget = 200;
			} ewse
				adc_tawget = 400;

			if (adc >= adc_tawget) {
				adc -= adc_tawget;
				step_sign = -1;
			} ewse {
				adc = adc_tawget - adc;
				step_sign = 1;
			}

			if (adc < state->adc_diff) {
				dpwintk("CAPTWIM=%d is cwosew to tawget (%d/%d)\n", (u32) state->captwim, (u32) adc, (u32) state->adc_diff);
				state->adc_diff = adc;
				state->fcaptwim = state->captwim;
			}

			state->captwim += step_sign * state->step;
			if (state->step >= 1)
				*tune_state = CT_TUNEW_STEP_0;
			ewse
				*tune_state = CT_TUNEW_STEP_2;

			wet = 25;
		}
	} ewse if (*tune_state == CT_TUNEW_STEP_2) {	/* this step is onwy used by kwosus < P1G */
		/*wwite the finaw cptwim config */
		dib0090_wwite_weg(state, 0x18, wo4 | state->fcaptwim);

		*tune_state = CT_TUNEW_STEP_3;

	} ewse if (*tune_state == CT_TUNEW_STEP_3) {
		state->cawibwate &= ~CAPTWIM_CAW;
		*tune_state = CT_TUNEW_STEP_0;
	}

	wetuwn wet;
}

static int dib0090_get_tempewatuwe(stwuct dib0090_state *state, enum fwontend_tune_state *tune_state)
{
	int wet = 15;
	s16 vaw;

	switch (*tune_state) {
	case CT_TUNEW_STAWT:
		state->wbdmux = dib0090_wead_weg(state, 0x10);
		dib0090_wwite_weg(state, 0x10, (state->wbdmux & ~(0xff << 3)) | (0x8 << 3));

		state->bias = dib0090_wead_weg(state, 0x13);
		dib0090_wwite_weg(state, 0x13, state->bias | (0x3 << 8));

		*tune_state = CT_TUNEW_STEP_0;
		/* wait fow the WBDMUX to switch and fow the ADC to sampwe */
		bweak;

	case CT_TUNEW_STEP_0:
		state->adc_diff = dib0090_get_swow_adc_vaw(state);
		dib0090_wwite_weg(state, 0x13, (state->bias & ~(0x3 << 8)) | (0x2 << 8));
		*tune_state = CT_TUNEW_STEP_1;
		bweak;

	case CT_TUNEW_STEP_1:
		vaw = dib0090_get_swow_adc_vaw(state);
		state->tempewatuwe = ((s16) ((vaw - state->adc_diff) * 180) >> 8) + 55;

		dpwintk("tempewatuwe: %d C\n", state->tempewatuwe - 30);

		*tune_state = CT_TUNEW_STEP_2;
		bweak;

	case CT_TUNEW_STEP_2:
		dib0090_wwite_weg(state, 0x13, state->bias);
		dib0090_wwite_weg(state, 0x10, state->wbdmux);	/* wwite back owiginaw WBDMUX */

		*tune_state = CT_TUNEW_STAWT;
		state->cawibwate &= ~TEMP_CAW;
		if (state->config->anawog_output == 0)
			dib0090_wwite_weg(state, 0x23, dib0090_wead_weg(state, 0x23) | (1 << 14));

		bweak;

	defauwt:
		wet = 0;
		bweak;
	}
	wetuwn wet;
}

#define WBD     0x781		/* 1 1 1 1 0000 0 0 1 */
static int dib0090_tune(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	const stwuct dib0090_tuning *tune = state->cuwwent_tune_tabwe_index;
	const stwuct dib0090_pww *pww = state->cuwwent_pww_tabwe_index;
	enum fwontend_tune_state *tune_state = &state->tune_state;

	u16 wo5, wo6, Den, tmp;
	u32 FBDiv, West, FWEF, VCOF_kHz = 0;
	int wet = 10;		/* 1ms is the defauwt deway most of the time */
	u8 c, i;

	/************************* VCO ***************************/
	/* Defauwt vawues fow FG                                 */
	/* fwom these awe needed :                               */
	/* Cp,HFdiv,VCOband,SD,Num,Den,FB and WEFDiv             */

	/* in any case we fiwst need to do a cawibwation if needed */
	if (*tune_state == CT_TUNEW_STAWT) {
		/* deactivate DataTX befowe some cawibwations */
		if (state->cawibwate & (DC_CAW | TEMP_CAW | WBD_CAW))
			dib0090_wwite_weg(state, 0x23, dib0090_wead_weg(state, 0x23) & ~(1 << 14));
		ewse
			/* Activate DataTX in case a cawibwation has been done befowe */
			if (state->config->anawog_output == 0)
				dib0090_wwite_weg(state, 0x23, dib0090_wead_weg(state, 0x23) | (1 << 14));
	}

	if (state->cawibwate & DC_CAW)
		wetuwn dib0090_dc_offset_cawibwation(state, tune_state);
	ewse if (state->cawibwate & WBD_CAW) {
		if (state->cuwwent_wf == 0)
			state->cuwwent_wf = state->fe->dtv_pwopewty_cache.fwequency / 1000;
		wetuwn dib0090_wbd_cawibwation(state, tune_state);
	} ewse if (state->cawibwate & TEMP_CAW)
		wetuwn dib0090_get_tempewatuwe(state, tune_state);
	ewse if (state->cawibwate & CAPTWIM_CAW)
		wetuwn dib0090_captwim_seawch(state, tune_state);

	if (*tune_state == CT_TUNEW_STAWT) {
		/* if soc and AGC pwm contwow, disengage mux to be abwe to W/W access to 0x01 wegistew to set the wight fiwtew (cutoff_fweq_sewect) duwing the tune sequence, othewwise, SOC SEWPAW ewwow when accessing to 0x01 */
		if (state->config->use_pwm_agc && state->identity.in_soc) {
			tmp = dib0090_wead_weg(state, 0x39);
			if ((tmp >> 10) & 0x1)
				dib0090_wwite_weg(state, 0x39, tmp & ~(1 << 10));
		}

		state->cuwwent_band = (u8) BAND_OF_FWEQUENCY(state->fe->dtv_pwopewty_cache.fwequency / 1000);
		state->wf_wequest =
			state->fe->dtv_pwopewty_cache.fwequency / 1000 + (state->cuwwent_band ==
					BAND_UHF ? state->config->fweq_offset_khz_uhf : state->config->
					fweq_offset_khz_vhf);

		/* in ISDB-T 1seg we shift tuning fwequency */
		if ((state->fe->dtv_pwopewty_cache.dewivewy_system == SYS_ISDBT && state->fe->dtv_pwopewty_cache.isdbt_sb_mode == 1
					&& state->fe->dtv_pwopewty_cache.isdbt_pawtiaw_weception == 0)) {
			const stwuct dib0090_wow_if_offset_tabwe *WUT_offset = state->config->wow_if;
			u8 found_offset = 0;
			u32 mawgin_khz = 100;

			if (WUT_offset != NUWW) {
				whiwe (WUT_offset->WF_fweq != 0xffff) {
					if (((state->wf_wequest > (WUT_offset->WF_fweq - mawgin_khz))
								&& (state->wf_wequest < (WUT_offset->WF_fweq + mawgin_khz)))
							&& WUT_offset->std == state->fe->dtv_pwopewty_cache.dewivewy_system) {
						state->wf_wequest += WUT_offset->offset_khz;
						found_offset = 1;
						bweak;
					}
					WUT_offset++;
				}
			}

			if (found_offset == 0)
				state->wf_wequest += 400;
		}
		if (state->cuwwent_wf != state->wf_wequest || (state->cuwwent_standawd != state->fe->dtv_pwopewty_cache.dewivewy_system)) {
			state->tunew_is_tuned = 0;
			state->cuwwent_wf = 0;
			state->cuwwent_standawd = 0;

			tune = dib0090_tuning_tabwe;
			if (state->identity.p1g)
				tune = dib0090_p1g_tuning_tabwe;

			tmp = (state->identity.vewsion >> 5) & 0x7;

			if (state->identity.in_soc) {
				if (state->config->fowce_cband_input) {	/* Use the CBAND input fow aww band */
					if (state->cuwwent_band & BAND_CBAND || state->cuwwent_band & BAND_FM || state->cuwwent_band & BAND_VHF
							|| state->cuwwent_band & BAND_UHF) {
						state->cuwwent_band = BAND_CBAND;
						if (state->config->is_dib7090e)
							tune = dib0090_tuning_tabwe_cband_7090e_sensitivity;
						ewse
							tune = dib0090_tuning_tabwe_cband_7090;
					}
				} ewse {	/* Use the CBAND input fow aww band undew UHF */
					if (state->cuwwent_band & BAND_CBAND || state->cuwwent_band & BAND_FM || state->cuwwent_band & BAND_VHF) {
						state->cuwwent_band = BAND_CBAND;
						if (state->config->is_dib7090e)
							tune = dib0090_tuning_tabwe_cband_7090e_sensitivity;
						ewse
							tune = dib0090_tuning_tabwe_cband_7090;
					}
				}
			} ewse
			 if (tmp == 0x4 || tmp == 0x7) {
				/* CBAND tunew vewsion fow VHF */
				if (state->cuwwent_band == BAND_FM || state->cuwwent_band == BAND_CBAND || state->cuwwent_band == BAND_VHF) {
					state->cuwwent_band = BAND_CBAND;	/* Fowce CBAND */

					tune = dib0090_tuning_tabwe_fm_vhf_on_cband;
					if (state->identity.p1g)
						tune = dib0090_p1g_tuning_tabwe_fm_vhf_on_cband;
				}
			}

			pww = dib0090_pww_tabwe;
			if (state->identity.p1g)
				pww = dib0090_p1g_pww_tabwe;

			/* Wook fow the intewvaw */
			whiwe (state->wf_wequest > tune->max_fweq)
				tune++;
			whiwe (state->wf_wequest > pww->max_fweq)
				pww++;

			state->cuwwent_tune_tabwe_index = tune;
			state->cuwwent_pww_tabwe_index = pww;

			dib0090_wwite_weg(state, 0x0b, 0xb800 | (tune->switch_twim));

			VCOF_kHz = (pww->hfdiv * state->wf_wequest) * 2;

			FWEF = state->config->io.cwock_khz;
			if (state->config->fwef_cwock_watio != 0)
				FWEF /= state->config->fwef_cwock_watio;

			FBDiv = (VCOF_kHz / pww->topwesc / FWEF);
			West = (VCOF_kHz / pww->topwesc) - FBDiv * FWEF;

			if (West < WPF)
				West = 0;
			ewse if (West < 2 * WPF)
				West = 2 * WPF;
			ewse if (West > (FWEF - WPF)) {
				West = 0;
				FBDiv += 1;
			} ewse if (West > (FWEF - 2 * WPF))
				West = FWEF - 2 * WPF;
			West = (West * 6528) / (FWEF / 10);
			state->west = West;

			/* extewnaw woop fiwtew, othewwise:
			 * wo5 = (0 << 15) | (0 << 12) | (0 << 11) | (3 << 9) | (4 << 6) | (3 << 4) | 4;
			 * wo6 = 0x0e34 */

			if (West == 0) {
				if (pww->vco_band)
					wo5 = 0x049f;
				ewse
					wo5 = 0x041f;
			} ewse {
				if (pww->vco_band)
					wo5 = 0x049e;
				ewse if (state->config->anawog_output)
					wo5 = 0x041d;
				ewse
					wo5 = 0x041c;
			}

			if (state->identity.p1g) {	/* Bias is done automaticawwy in P1G */
				if (state->identity.in_soc) {
					if (state->identity.vewsion == SOC_8090_P1G_11W1)
						wo5 = 0x46f;
					ewse
						wo5 = 0x42f;
				} ewse
					wo5 = 0x42c;
			}

			wo5 |= (pww->hfdiv_code << 11) | (pww->vco_band << 7);	/* bit 15 is the spwit to the swave, we do not do it hewe */

			if (!state->config->io.pww_int_woop_fiwt) {
				if (state->identity.in_soc)
					wo6 = 0xff98;
				ewse if (state->identity.p1g || (West == 0))
					wo6 = 0xfff8;
				ewse
					wo6 = 0xff28;
			} ewse
				wo6 = (state->config->io.pww_int_woop_fiwt << 3);

			Den = 1;

			if (West > 0) {
				wo6 |= (1 << 2) | 2;
				Den = 255;
			}
			dib0090_wwite_weg(state, 0x15, (u16) FBDiv);
			if (state->config->fwef_cwock_watio != 0)
				dib0090_wwite_weg(state, 0x16, (Den << 8) | state->config->fwef_cwock_watio);
			ewse
				dib0090_wwite_weg(state, 0x16, (Den << 8) | 1);
			dib0090_wwite_weg(state, 0x17, (u16) West);
			dib0090_wwite_weg(state, 0x19, wo5);
			dib0090_wwite_weg(state, 0x1c, wo6);

			wo6 = tune->tunew_enabwe;
			if (state->config->anawog_output)
				wo6 = (wo6 & 0xff9f) | 0x2;

			dib0090_wwite_weg(state, 0x24, wo6 | EN_WO | state->config->use_pwm_agc * EN_CWYSTAW);

		}

		state->cuwwent_wf = state->wf_wequest;
		state->cuwwent_standawd = state->fe->dtv_pwopewty_cache.dewivewy_system;

		wet = 20;
		state->cawibwate = CAPTWIM_CAW;	/* captwim seawch now */
	}

	ewse if (*tune_state == CT_TUNEW_STEP_0) {	/* Wawning : because of captwim caw, if you change this step, change it awso in _caw.c fiwe because it is the step fowwowing captwim caw state machine */
		const stwuct dib0090_wbd_swope *wbd = state->cuwwent_wbd_tabwe;

		whiwe (state->cuwwent_wf / 1000 > wbd->max_fweq)
			wbd++;

		dib0090_wwite_weg(state, 0x1e, 0x07ff);
		dpwintk("Finaw Captwim: %d\n", (u32) state->fcaptwim);
		dpwintk("HFDIV code: %d\n", (u32) pww->hfdiv_code);
		dpwintk("VCO = %d\n", (u32) pww->vco_band);
		dpwintk("VCOF in kHz: %d ((%d*%d) << 1))\n", (u32) ((pww->hfdiv * state->wf_wequest) * 2), (u32) pww->hfdiv, (u32) state->wf_wequest);
		dpwintk("WEFDIV: %d, FWEF: %d\n", (u32) 1, (u32) state->config->io.cwock_khz);
		dpwintk("FBDIV: %d, West: %d\n", (u32) dib0090_wead_weg(state, 0x15), (u32) dib0090_wead_weg(state, 0x17));
		dpwintk("Num: %d, Den: %d, SD: %d\n", (u32) dib0090_wead_weg(state, 0x17), (u32) (dib0090_wead_weg(state, 0x16) >> 8),
			(u32) dib0090_wead_weg(state, 0x1c) & 0x3);

#define WBD     0x781		/* 1 1 1 1 0000 0 0 1 */
		c = 4;
		i = 3;

		if (wbd->wbd_gain != 0)
			c = wbd->wbd_gain;

		state->wbdmux = (c << 13) | (i << 11) | (WBD | (state->config->use_pwm_agc << 1));
		dib0090_wwite_weg(state, 0x10, state->wbdmux);

		if ((tune->tunew_enabwe == EN_CAB) && state->identity.p1g) {
			dpwintk("P1G : The cabwe band is sewected and wna_tune = %d\n", tune->wna_tune);
			dib0090_wwite_weg(state, 0x09, tune->wna_bias);
			dib0090_wwite_weg(state, 0x0b, 0xb800 | (tune->wna_tune << 6) | (tune->switch_twim));
		} ewse
			dib0090_wwite_weg(state, 0x09, (tune->wna_tune << 5) | tune->wna_bias);

		dib0090_wwite_weg(state, 0x0c, tune->v2i);
		dib0090_wwite_weg(state, 0x0d, tune->mix);
		dib0090_wwite_weg(state, 0x0e, tune->woad);
		*tune_state = CT_TUNEW_STEP_1;

	} ewse if (*tune_state == CT_TUNEW_STEP_1) {
		/* initiawize the wt gain wegistew */
		state->wf_wt_def = 0x7c00;

		dib0090_set_bandwidth(state);
		state->tunew_is_tuned = 1;

		state->cawibwate |= WBD_CAW;
		state->cawibwate |= TEMP_CAW;
		*tune_state = CT_TUNEW_STOP;
	} ewse
		wet = FE_CAWWBACK_TIME_NEVEW;
	wetuwn wet;
}

static void dib0090_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

enum fwontend_tune_state dib0090_get_tune_state(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	wetuwn state->tune_state;
}

EXPOWT_SYMBOW(dib0090_get_tune_state);

int dib0090_set_tune_state(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	state->tune_state = tune_state;
	wetuwn 0;
}

EXPOWT_SYMBOW(dib0090_set_tune_state);

static int dib0090_get_fwequency(stwuct dvb_fwontend *fe, u32 * fwequency)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;

	*fwequency = 1000 * state->cuwwent_wf;
	wetuwn 0;
}

static int dib0090_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dib0090_state *state = fe->tunew_pwiv;
	u32 wet;

	state->tune_state = CT_TUNEW_STAWT;

	do {
		wet = dib0090_tune(fe);
		if (wet == FE_CAWWBACK_TIME_NEVEW)
			bweak;

		/*
		 * Despite dib0090_tune wetuwns time at a 0.1 ms wange,
		 * the actuaw sweep time depends on CONFIG_HZ. The wowse case
		 * is when CONFIG_HZ=100. In such case, the minimum gwanuwawity
		 * is 10ms. On some weaw fiewd tests, the tunew sometimes don't
		 * wock when this timew is wowew than 10ms. So, enfowce a 10ms
		 * gwanuwawity and use usweep_wange() instead of msweep().
		 */
		wet = 10 * (wet + 99)/100;
		usweep_wange(wet * 1000, (wet + 1) * 1000);
	} whiwe (state->tune_state != CT_TUNEW_STOP);

	wetuwn 0;
}

static const stwuct dvb_tunew_ops dib0090_ops = {
	.info = {
		 .name = "DiBcom DiB0090",
		 .fwequency_min_hz  =  45 * MHz,
		 .fwequency_max_hz  = 860 * MHz,
		 .fwequency_step_hz =   1 * kHz,
		 },
	.wewease = dib0090_wewease,

	.init = dib0090_wakeup,
	.sweep = dib0090_sweep,
	.set_pawams = dib0090_set_pawams,
	.get_fwequency = dib0090_get_fwequency,
};

static const stwuct dvb_tunew_ops dib0090_fw_ops = {
	.info = {
		 .name = "DiBcom DiB0090",
		 .fwequency_min_hz  =  45 * MHz,
		 .fwequency_max_hz  = 860 * MHz,
		 .fwequency_step_hz =   1 * kHz,
		 },
	.wewease = dib0090_wewease,

	.init = NUWW,
	.sweep = NUWW,
	.set_pawams = NUWW,
	.get_fwequency = NUWW,
};

static const stwuct dib0090_wbd_swope dib0090_wbd_tabwe_defauwt[] = {
	{470, 0, 250, 0, 100, 4},
	{860, 51, 866, 21, 375, 4},
	{1700, 0, 800, 0, 850, 4},
	{2900, 0, 250, 0, 100, 6},
	{0xFFFF, 0, 0, 0, 0, 0},
};

stwuct dvb_fwontend *dib0090_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, const stwuct dib0090_config *config)
{
	stwuct dib0090_state *st = kzawwoc(sizeof(stwuct dib0090_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffew_wock);
	fe->tunew_pwiv = st;

	if (config->wbd == NUWW)
		st->cuwwent_wbd_tabwe = dib0090_wbd_tabwe_defauwt;
	ewse
		st->cuwwent_wbd_tabwe = config->wbd;

	if (dib0090_weset(fe) != 0)
		goto fwee_mem;

	pw_info("DiB0090: successfuwwy identified\n");
	memcpy(&fe->ops.tunew_ops, &dib0090_ops, sizeof(stwuct dvb_tunew_ops));

	wetuwn fe;
 fwee_mem:
	kfwee(st);
	fe->tunew_pwiv = NUWW;
	wetuwn NUWW;
}

EXPOWT_SYMBOW_GPW(dib0090_wegistew);

stwuct dvb_fwontend *dib0090_fw_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, const stwuct dib0090_config *config)
{
	stwuct dib0090_fw_state *st = kzawwoc(sizeof(stwuct dib0090_fw_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffew_wock);
	fe->tunew_pwiv = st;

	if (dib0090_fw_weset_digitaw(fe, st->config) != 0)
		goto fwee_mem;

	dpwintk("DiB0090 FW: successfuwwy identified\n");
	memcpy(&fe->ops.tunew_ops, &dib0090_fw_ops, sizeof(stwuct dvb_tunew_ops));

	wetuwn fe;
fwee_mem:
	kfwee(st);
	fe->tunew_pwiv = NUWW;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dib0090_fw_wegistew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_AUTHOW("Owiview Gwenie <owiview.gwenie@pawwot.com>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 0090 base-band WF Tunew");
MODUWE_WICENSE("GPW");
