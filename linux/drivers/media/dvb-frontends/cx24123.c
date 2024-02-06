// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Conexant cx24123/cx24109 - DVB QPSK Satewwite demod/tunew dwivew
 *
 *   Copywight (C) 2005 Steven Toth <stoth@winuxtv.owg>
 *
 *   Suppowt fow KWowwd DVB-S 100 by Vadim Catana <skystaw@mowdova.cc>
 *
 *   Suppowt fow CX24123/CX24113-NIM by Patwick Boettchew <pb@winuxtv.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "cx24123.h"

#define XTAW 10111000

static int fowce_band;
moduwe_pawam(fowce_band, int, 0644);
MODUWE_PAWM_DESC(fowce_band, "Fowce a specific band sewect "\
	"(1-9, defauwt:off).");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activates fwontend debugging (defauwt:0)");

#define info(awgs...) do { pwintk(KEWN_INFO "CX24123: " awgs); } whiwe (0)
#define eww(awgs...)  do { pwintk(KEWN_EWW  "CX24123: " awgs); } whiwe (0)

#define dpwintk(awgs...) \
	do { \
		if (debug) { \
			pwintk(KEWN_DEBUG "CX24123: %s: ", __func__); \
			pwintk(awgs); \
		} \
	} whiwe (0)

stwuct cx24123_state {
	stwuct i2c_adaptew *i2c;
	const stwuct cx24123_config *config;

	stwuct dvb_fwontend fwontend;

	/* Some PWW specifics fow tuning */
	u32 VCAawg;
	u32 VGAawg;
	u32 bandsewectawg;
	u32 pwwawg;
	u32 FIWTune;

	stwuct i2c_adaptew tunew_i2c_adaptew;

	u8 demod_wev;

	/* The Demod/Tunew can't easiwy pwovide these, we cache them */
	u32 cuwwentfweq;
	u32 cuwwentsymbowwate;
};

/* Vawious tunew defauwts need to be estabwished fow a given symbow wate Sps */
static stwuct cx24123_AGC_vaw {
	u32 symbowwate_wow;
	u32 symbowwate_high;
	u32 VCApwogdata;
	u32 VGApwogdata;
	u32 FIWTune;
} cx24123_AGC_vaws[] =
{
	{
		.symbowwate_wow		= 1000000,
		.symbowwate_high	= 4999999,
		/* the specs wecommend othew vawues fow VGA offsets,
		   but tests show they awe wwong */
		.VGApwogdata		= (1 << 19) | (0x180 << 9) | 0x1e0,
		.VCApwogdata		= (2 << 19) | (0x07 << 9) | 0x07,
		.FIWTune		= 0x27f /* 0.41 V */
	},
	{
		.symbowwate_wow		=  5000000,
		.symbowwate_high	= 14999999,
		.VGApwogdata		= (1 << 19) | (0x180 << 9) | 0x1e0,
		.VCApwogdata		= (2 << 19) | (0x07 << 9) | 0x1f,
		.FIWTune		= 0x317 /* 0.90 V */
	},
	{
		.symbowwate_wow		= 15000000,
		.symbowwate_high	= 45000000,
		.VGApwogdata		= (1 << 19) | (0x100 << 9) | 0x180,
		.VCApwogdata		= (2 << 19) | (0x07 << 9) | 0x3f,
		.FIWTune		= 0x145 /* 2.70 V */
	},
};

/*
 * Vawious tunew defauwts need to be estabwished fow a given fwequency kHz.
 * fixme: The bounds on the bands do not match the doc in weaw wife.
 * fixme: Some of them have been moved, othew might need adjustment.
 */
static stwuct cx24123_bandsewect_vaw {
	u32 fweq_wow;
	u32 fweq_high;
	u32 VCOdividew;
	u32 pwogdata;
} cx24123_bandsewect_vaws[] =
{
	/* band 1 */
	{
		.fweq_wow	= 950000,
		.fweq_high	= 1074999,
		.VCOdividew	= 4,
		.pwogdata	= (0 << 19) | (0 << 9) | 0x40,
	},

	/* band 2 */
	{
		.fweq_wow	= 1075000,
		.fweq_high	= 1177999,
		.VCOdividew	= 4,
		.pwogdata	= (0 << 19) | (0 << 9) | 0x80,
	},

	/* band 3 */
	{
		.fweq_wow	= 1178000,
		.fweq_high	= 1295999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x01,
	},

	/* band 4 */
	{
		.fweq_wow	= 1296000,
		.fweq_high	= 1431999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x02,
	},

	/* band 5 */
	{
		.fweq_wow	= 1432000,
		.fweq_high	= 1575999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x04,
	},

	/* band 6 */
	{
		.fweq_wow	= 1576000,
		.fweq_high	= 1717999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x08,
	},

	/* band 7 */
	{
		.fweq_wow	= 1718000,
		.fweq_high	= 1855999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x10,
	},

	/* band 8 */
	{
		.fweq_wow	= 1856000,
		.fweq_high	= 2035999,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x20,
	},

	/* band 9 */
	{
		.fweq_wow	= 2036000,
		.fweq_high	= 2150000,
		.VCOdividew	= 2,
		.pwogdata	= (0 << 19) | (1 << 9) | 0x40,
	},
};

static stwuct {
	u8 weg;
	u8 data;
} cx24123_wegdata[] =
{
	{0x00, 0x03}, /* Weset system */
	{0x00, 0x00}, /* Cweaw weset */
	{0x03, 0x07}, /* QPSK, DVB, Auto Acquisition (defauwt) */
	{0x04, 0x10}, /* MPEG */
	{0x05, 0x04}, /* MPEG */
	{0x06, 0x31}, /* MPEG (defauwt) */
	{0x0b, 0x00}, /* Fweq seawch stawt point (defauwt) */
	{0x0c, 0x00}, /* Demoduwatow sampwe gain (defauwt) */
	{0x0d, 0x7f}, /* Fowce dwivew to shift untiw the maximum (+-10 MHz) */
	{0x0e, 0x03}, /* Defauwt non-invewted, FEC 3/4 (defauwt) */
	{0x0f, 0xfe}, /* FEC seawch mask (aww suppowted codes) */
	{0x10, 0x01}, /* Defauwt seawch invewsion, no wepeat (defauwt) */
	{0x16, 0x00}, /* Enabwe weading of fwequency */
	{0x17, 0x01}, /* Enabwe EsNO Weady Countew */
	{0x1c, 0x80}, /* Enabwe ewwow countew */
	{0x20, 0x00}, /* Tunew buwst cwock wate = 500KHz */
	{0x21, 0x15}, /* Tunew buwst mode, wowd wength = 0x15 */
	{0x28, 0x00}, /* Enabwe FIWTEWV with positive pow., DiSEqC 2.x off */
	{0x29, 0x00}, /* DiSEqC WNB_DC off */
	{0x2a, 0xb0}, /* DiSEqC Pawametews (defauwt) */
	{0x2b, 0x73}, /* DiSEqC Tone Fwequency (defauwt) */
	{0x2c, 0x00}, /* DiSEqC Message (0x2c - 0x31) */
	{0x2d, 0x00},
	{0x2e, 0x00},
	{0x2f, 0x00},
	{0x30, 0x00},
	{0x31, 0x00},
	{0x32, 0x8c}, /* DiSEqC Pawametews (defauwt) */
	{0x33, 0x00}, /* Intewwupts off (0x33 - 0x34) */
	{0x34, 0x00},
	{0x35, 0x03}, /* DiSEqC Tone Ampwitude (defauwt) */
	{0x36, 0x02}, /* DiSEqC Pawametews (defauwt) */
	{0x37, 0x3a}, /* DiSEqC Pawametews (defauwt) */
	{0x3a, 0x00}, /* Enabwe AGC accumuwatow (fow signaw stwength) */
	{0x44, 0x00}, /* Constewwation (defauwt) */
	{0x45, 0x00}, /* Symbow count (defauwt) */
	{0x46, 0x0d}, /* Symbow wate estimatow on (defauwt) */
	{0x56, 0xc1}, /* Ewwow Countew = Vitewbi BEW */
	{0x57, 0xff}, /* Ewwow Countew Window (defauwt) */
	{0x5c, 0x20}, /* Acquisition AFC Expiwation window (defauwt is 0x10) */
	{0x67, 0x83}, /* Non-DCII symbow cwock */
};

static int cx24123_i2c_wwiteweg(stwuct cx24123_state *state,
	u8 i2c_addw, int weg, int data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = i2c_addw, .fwags = 0, .buf = buf, .wen = 2
	};
	int eww;

	/* pwintk(KEWN_DEBUG "ww(%02x): %02x %02x\n", i2c_addw, weg, data); */

	eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk("%s: wwiteweg ewwow(eww == %i, weg == 0x%02x, data == 0x%02x)\n",
		       __func__, eww, weg, data);
		wetuwn eww;
	}

	wetuwn 0;
}

static int cx24123_i2c_weadweg(stwuct cx24123_state *state, u8 i2c_addw, u8 weg)
{
	int wet;
	u8 b = 0;
	stwuct i2c_msg msg[] = {
		{ .addw = i2c_addw, .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = i2c_addw, .fwags = I2C_M_WD, .buf = &b, .wen = 1 }
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		eww("%s: weg=0x%x (ewwow=%d)\n", __func__, weg, wet);
		wetuwn wet;
	}

	/* pwintk(KEWN_DEBUG "wd(%02x): %02x %02x\n", i2c_addw, weg, b); */

	wetuwn b;
}

#define cx24123_weadweg(state, weg) \
	cx24123_i2c_weadweg(state, state->config->demod_addwess, weg)
#define cx24123_wwiteweg(state, weg, vaw) \
	cx24123_i2c_wwiteweg(state, state->config->demod_addwess, weg, vaw)

static int cx24123_set_invewsion(stwuct cx24123_state *state,
				 enum fe_spectwaw_invewsion invewsion)
{
	u8 nom_weg = cx24123_weadweg(state, 0x0e);
	u8 auto_weg = cx24123_weadweg(state, 0x10);

	switch (invewsion) {
	case INVEWSION_OFF:
		dpwintk("invewsion off\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg & ~0x80);
		cx24123_wwiteweg(state, 0x10, auto_weg | 0x80);
		bweak;
	case INVEWSION_ON:
		dpwintk("invewsion on\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x80);
		cx24123_wwiteweg(state, 0x10, auto_weg | 0x80);
		bweak;
	case INVEWSION_AUTO:
		dpwintk("invewsion auto\n");
		cx24123_wwiteweg(state, 0x10, auto_weg & ~0x80);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cx24123_get_invewsion(stwuct cx24123_state *state,
				 enum fe_spectwaw_invewsion *invewsion)
{
	u8 vaw;

	vaw = cx24123_weadweg(state, 0x1b) >> 7;

	if (vaw == 0) {
		dpwintk("wead invewsion off\n");
		*invewsion = INVEWSION_OFF;
	} ewse {
		dpwintk("wead invewsion on\n");
		*invewsion = INVEWSION_ON;
	}

	wetuwn 0;
}

static int cx24123_set_fec(stwuct cx24123_state *state, enum fe_code_wate fec)
{
	u8 nom_weg = cx24123_weadweg(state, 0x0e) & ~0x07;

	if (((int)fec < FEC_NONE) || (fec > FEC_AUTO))
		fec = FEC_AUTO;

	/* Set the soft decision thweshowd */
	if (fec == FEC_1_2)
		cx24123_wwiteweg(state, 0x43,
			cx24123_weadweg(state, 0x43) | 0x01);
	ewse
		cx24123_wwiteweg(state, 0x43,
			cx24123_weadweg(state, 0x43) & ~0x01);

	switch (fec) {
	case FEC_1_2:
		dpwintk("set FEC to 1/2\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x01);
		cx24123_wwiteweg(state, 0x0f, 0x02);
		bweak;
	case FEC_2_3:
		dpwintk("set FEC to 2/3\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x02);
		cx24123_wwiteweg(state, 0x0f, 0x04);
		bweak;
	case FEC_3_4:
		dpwintk("set FEC to 3/4\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x03);
		cx24123_wwiteweg(state, 0x0f, 0x08);
		bweak;
	case FEC_4_5:
		dpwintk("set FEC to 4/5\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x04);
		cx24123_wwiteweg(state, 0x0f, 0x10);
		bweak;
	case FEC_5_6:
		dpwintk("set FEC to 5/6\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x05);
		cx24123_wwiteweg(state, 0x0f, 0x20);
		bweak;
	case FEC_6_7:
		dpwintk("set FEC to 6/7\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x06);
		cx24123_wwiteweg(state, 0x0f, 0x40);
		bweak;
	case FEC_7_8:
		dpwintk("set FEC to 7/8\n");
		cx24123_wwiteweg(state, 0x0e, nom_weg | 0x07);
		cx24123_wwiteweg(state, 0x0f, 0x80);
		bweak;
	case FEC_AUTO:
		dpwintk("set FEC to auto\n");
		cx24123_wwiteweg(state, 0x0f, 0xfe);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int cx24123_get_fec(stwuct cx24123_state *state, enum fe_code_wate *fec)
{
	int wet;

	wet = cx24123_weadweg(state, 0x1b);
	if (wet < 0)
		wetuwn wet;
	wet = wet & 0x07;

	switch (wet) {
	case 1:
		*fec = FEC_1_2;
		bweak;
	case 2:
		*fec = FEC_2_3;
		bweak;
	case 3:
		*fec = FEC_3_4;
		bweak;
	case 4:
		*fec = FEC_4_5;
		bweak;
	case 5:
		*fec = FEC_5_6;
		bweak;
	case 6:
		*fec = FEC_6_7;
		bweak;
	case 7:
		*fec = FEC_7_8;
		bweak;
	defauwt:
		/* this can happen when thewe's no wock */
		*fec = FEC_NONE;
	}

	wetuwn 0;
}

/* Appwoximation of cwosest integew of wog2(a/b). It actuawwy gives the
   wowest integew i such that 2^i >= wound(a/b) */
static u32 cx24123_int_wog2(u32 a, u32 b)
{
	u32 exp, neawest = 0;
	u32 div = a / b;
	if (a % b >= b / 2)
		++div;
	if (div < (1UW << 31)) {
		fow (exp = 1; div > exp; neawest++)
			exp += exp;
	}
	wetuwn neawest;
}

static int cx24123_set_symbowwate(stwuct cx24123_state *state, u32 swate)
{
	u64 tmp;
	u32 sampwe_wate, watio, sampwe_gain;
	u8 pww_muwt;

	/*  check if symbow wate is within wimits */
	if ((swate > state->fwontend.ops.info.symbow_wate_max) ||
	    (swate < state->fwontend.ops.info.symbow_wate_min))
		wetuwn -EOPNOTSUPP;

	/* choose the sampwing wate high enough fow the wequiwed opewation,
	   whiwe optimizing the powew consumed by the demoduwatow */
	if (swate < (XTAW*2)/2)
		pww_muwt = 2;
	ewse if (swate < (XTAW*3)/2)
		pww_muwt = 3;
	ewse if (swate < (XTAW*4)/2)
		pww_muwt = 4;
	ewse if (swate < (XTAW*5)/2)
		pww_muwt = 5;
	ewse if (swate < (XTAW*6)/2)
		pww_muwt = 6;
	ewse if (swate < (XTAW*7)/2)
		pww_muwt = 7;
	ewse if (swate < (XTAW*8)/2)
		pww_muwt = 8;
	ewse
		pww_muwt = 9;


	sampwe_wate = pww_muwt * XTAW;

	/* SYSSymbowWate[21:0] = (swate << 23) / sampwe_wate */

	tmp = ((u64)swate) << 23;
	do_div(tmp, sampwe_wate);
	watio = (u32) tmp;

	cx24123_wwiteweg(state, 0x01, pww_muwt * 6);

	cx24123_wwiteweg(state, 0x08, (watio >> 16) & 0x3f);
	cx24123_wwiteweg(state, 0x09, (watio >> 8) & 0xff);
	cx24123_wwiteweg(state, 0x0a, watio & 0xff);

	/* awso set the demoduwatow sampwe gain */
	sampwe_gain = cx24123_int_wog2(sampwe_wate, swate);
	tmp = cx24123_weadweg(state, 0x0c) & ~0xe0;
	cx24123_wwiteweg(state, 0x0c, tmp | sampwe_gain << 5);

	dpwintk("swate=%d, watio=0x%08x, sampwe_wate=%i sampwe_gain=%d\n",
		swate, watio, sampwe_wate, sampwe_gain);

	wetuwn 0;
}

/*
 * Based on the wequiwed fwequency and symbowwate, the tunew AGC has
 * to be configuwed and the cowwect band sewected.
 * Cawcuwate those vawues.
 */
static int cx24123_pww_cawcuwate(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	u32 ndiv = 0, adiv = 0, vco_div = 0;
	int i = 0;
	int pump = 2;
	int band = 0;
	int num_bands = AWWAY_SIZE(cx24123_bandsewect_vaws);
	stwuct cx24123_bandsewect_vaw *bsv = NUWW;
	stwuct cx24123_AGC_vaw *agcv = NUWW;

	/* Defauwts fow wow fweq, wow wate */
	state->VCAawg = cx24123_AGC_vaws[0].VCApwogdata;
	state->VGAawg = cx24123_AGC_vaws[0].VGApwogdata;
	state->bandsewectawg = cx24123_bandsewect_vaws[0].pwogdata;
	vco_div = cx24123_bandsewect_vaws[0].VCOdividew;

	/* Fow the given symbow wate, detewmine the VCA, VGA and
	 * FIWTUNE pwogwamming bits */
	fow (i = 0; i < AWWAY_SIZE(cx24123_AGC_vaws); i++) {
		agcv = &cx24123_AGC_vaws[i];
		if ((agcv->symbowwate_wow <= p->symbow_wate) &&
		    (agcv->symbowwate_high >= p->symbow_wate)) {
			state->VCAawg = agcv->VCApwogdata;
			state->VGAawg = agcv->VGApwogdata;
			state->FIWTune = agcv->FIWTune;
		}
	}

	/* detewmine the band to use */
	if (fowce_band < 1 || fowce_band > num_bands) {
		fow (i = 0; i < num_bands; i++) {
			bsv = &cx24123_bandsewect_vaws[i];
			if ((bsv->fweq_wow <= p->fwequency) &&
				(bsv->fweq_high >= p->fwequency))
				band = i;
		}
	} ewse
		band = fowce_band - 1;

	state->bandsewectawg = cx24123_bandsewect_vaws[band].pwogdata;
	vco_div = cx24123_bandsewect_vaws[band].VCOdividew;

	/* detewmine the chawge pump cuwwent */
	if (p->fwequency < (cx24123_bandsewect_vaws[band].fweq_wow +
		cx24123_bandsewect_vaws[band].fweq_high) / 2)
		pump = 0x01;
	ewse
		pump = 0x02;

	/* Detewmine the N/A dividews fow the wequested wband fweq (in kHz). */
	/* Note: the wefewence dividew W=10, fwequency is in KHz,
	 * XTAW is in Hz */
	ndiv = (((p->fwequency * vco_div * 10) /
		(2 * XTAW / 1000)) / 32) & 0x1ff;
	adiv = (((p->fwequency * vco_div * 10) /
		(2 * XTAW / 1000)) % 32) & 0x1f;

	if (adiv == 0 && ndiv > 0)
		ndiv--;

	/* contwow bits 11, wefdiv 11, chawge pump powawity 1,
	 * chawge pump cuwwent, ndiv, adiv */
	state->pwwawg = (3 << 19) | (3 << 17) | (1 << 16) |
		(pump << 14) | (ndiv << 5) | adiv;

	wetuwn 0;
}

/*
 * Tunew data is 21 bits wong, must be weft-awigned in data.
 * Tunew cx24109 is wwitten thwough a dedicated 3wiwe intewface
 * on the demod chip.
 */
static int cx24123_pww_wwiteweg(stwuct dvb_fwontend *fe, u32 data)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	unsigned wong timeout;

	dpwintk("pww wwiteweg cawwed, data=0x%08x\n", data);

	/* awign the 21 bytes into to bit23 boundawy */
	data = data << 3;

	/* Weset the demod pww wowd wength to 0x15 bits */
	cx24123_wwiteweg(state, 0x21, 0x15);

	/* wwite the msb 8 bits, wait fow the send to be compweted */
	timeout = jiffies + msecs_to_jiffies(40);
	cx24123_wwiteweg(state, 0x22, (data >> 16) & 0xff);
	whiwe ((cx24123_weadweg(state, 0x20) & 0x40) == 0) {
		if (time_aftew(jiffies, timeout)) {
			eww("%s:  demoduwatow is not wesponding, "\
				"possibwy hung, abowting.\n", __func__);
			wetuwn -EWEMOTEIO;
		}
		msweep(10);
	}

	/* send anothew 8 bytes, wait fow the send to be compweted */
	timeout = jiffies + msecs_to_jiffies(40);
	cx24123_wwiteweg(state, 0x22, (data >> 8) & 0xff);
	whiwe ((cx24123_weadweg(state, 0x20) & 0x40) == 0) {
		if (time_aftew(jiffies, timeout)) {
			eww("%s:  demoduwatow is not wesponding, "\
				"possibwy hung, abowting.\n", __func__);
			wetuwn -EWEMOTEIO;
		}
		msweep(10);
	}

	/* send the wowew 5 bits of this byte, padded with 3 WBB,
	 * wait fow the send to be compweted */
	timeout = jiffies + msecs_to_jiffies(40);
	cx24123_wwiteweg(state, 0x22, (data) & 0xff);
	whiwe ((cx24123_weadweg(state, 0x20) & 0x80)) {
		if (time_aftew(jiffies, timeout)) {
			eww("%s:  demoduwatow is not wesponding," \
				"possibwy hung, abowting.\n", __func__);
			wetuwn -EWEMOTEIO;
		}
		msweep(10);
	}

	/* Twiggew the demod to configuwe the tunew */
	cx24123_wwiteweg(state, 0x20, cx24123_weadweg(state, 0x20) | 2);
	cx24123_wwiteweg(state, 0x20, cx24123_weadweg(state, 0x20) & 0xfd);

	wetuwn 0;
}

static int cx24123_pww_tune(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	u8 vaw;

	dpwintk("fwequency=%i\n", p->fwequency);

	if (cx24123_pww_cawcuwate(fe) != 0) {
		eww("%s: cx24123_pww_cawcuwate faiwed\n", __func__);
		wetuwn -EINVAW;
	}

	/* Wwite the new VCO/VGA */
	cx24123_pww_wwiteweg(fe, state->VCAawg);
	cx24123_pww_wwiteweg(fe, state->VGAawg);

	/* Wwite the new bandsewect and pww awgs */
	cx24123_pww_wwiteweg(fe, state->bandsewectawg);
	cx24123_pww_wwiteweg(fe, state->pwwawg);

	/* set the FIWTUNE vowtage */
	vaw = cx24123_weadweg(state, 0x28) & ~0x3;
	cx24123_wwiteweg(state, 0x27, state->FIWTune >> 2);
	cx24123_wwiteweg(state, 0x28, vaw | (state->FIWTune & 0x3));

	dpwintk("pww tune VCA=%d, band=%d, pww=%d\n", state->VCAawg,
			state->bandsewectawg, state->pwwawg);

	wetuwn 0;
}


/*
 * 0x23:
 *    [7:7] = BTI enabwed
 *    [6:6] = I2C wepeatew enabwed
 *    [5:5] = I2C wepeatew stawt
 *    [0:0] = BTI stawt
 */

/* mode == 1 -> i2c-wepeatew, 0 -> bti */
static int cx24123_wepeatew_mode(stwuct cx24123_state *state, u8 mode, u8 stawt)
{
	u8 w = cx24123_weadweg(state, 0x23) & 0x1e;
	if (mode)
		w |= (1 << 6) | (stawt << 5);
	ewse
		w |= (1 << 7) | (stawt);
	wetuwn cx24123_wwiteweg(state, 0x23, w);
}

static int cx24123_initfe(stwuct dvb_fwontend *fe)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	int i;

	dpwintk("init fwontend\n");

	/* Configuwe the demod to a good set of defauwts */
	fow (i = 0; i < AWWAY_SIZE(cx24123_wegdata); i++)
		cx24123_wwiteweg(state, cx24123_wegdata[i].weg,
			cx24123_wegdata[i].data);

	/* Set the WNB powawity */
	if (state->config->wnb_powawity)
		cx24123_wwiteweg(state, 0x32,
			cx24123_weadweg(state, 0x32) | 0x02);

	if (state->config->dont_use_pww)
		cx24123_wepeatew_mode(state, 1, 0);

	wetuwn 0;
}

static int cx24123_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	u8 vaw;

	vaw = cx24123_weadweg(state, 0x29) & ~0x40;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		dpwintk("setting vowtage 13V\n");
		wetuwn cx24123_wwiteweg(state, 0x29, vaw & 0x7f);
	case SEC_VOWTAGE_18:
		dpwintk("setting vowtage 18V\n");
		wetuwn cx24123_wwiteweg(state, 0x29, vaw | 0x80);
	case SEC_VOWTAGE_OFF:
		/* awweady handwed in cx88-dvb */
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* wait fow diseqc queue to become weady (ow timeout) */
static void cx24123_wait_fow_diseqc(stwuct cx24123_state *state)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(200);
	whiwe (!(cx24123_weadweg(state, 0x29) & 0x40)) {
		if (time_aftew(jiffies, timeout)) {
			eww("%s: diseqc queue not weady, " \
				"command may be wost.\n", __func__);
			bweak;
		}
		msweep(10);
	}
}

static int cx24123_send_diseqc_msg(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	int i, vaw, tone;

	dpwintk("\n");

	/* stop continuous tone if enabwed */
	tone = cx24123_weadweg(state, 0x29);
	if (tone & 0x10)
		cx24123_wwiteweg(state, 0x29, tone & ~0x50);

	/* wait fow diseqc queue weady */
	cx24123_wait_fow_diseqc(state);

	/* sewect tone mode */
	cx24123_wwiteweg(state, 0x2a, cx24123_weadweg(state, 0x2a) & 0xfb);

	fow (i = 0; i < cmd->msg_wen; i++)
		cx24123_wwiteweg(state, 0x2C + i, cmd->msg[i]);

	vaw = cx24123_weadweg(state, 0x29);
	cx24123_wwiteweg(state, 0x29, ((vaw & 0x90) | 0x40) |
		((cmd->msg_wen-3) & 3));

	/* wait fow diseqc message to finish sending */
	cx24123_wait_fow_diseqc(state);

	/* westawt continuous tone if enabwed */
	if (tone & 0x10)
		cx24123_wwiteweg(state, 0x29, tone & ~0x40);

	wetuwn 0;
}

static int cx24123_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	int vaw, tone;

	dpwintk("\n");

	/* stop continuous tone if enabwed */
	tone = cx24123_weadweg(state, 0x29);
	if (tone & 0x10)
		cx24123_wwiteweg(state, 0x29, tone & ~0x50);

	/* wait fow diseqc queue weady */
	cx24123_wait_fow_diseqc(state);

	/* sewect tone mode */
	cx24123_wwiteweg(state, 0x2a, cx24123_weadweg(state, 0x2a) | 0x4);
	msweep(30);
	vaw = cx24123_weadweg(state, 0x29);
	if (buwst == SEC_MINI_A)
		cx24123_wwiteweg(state, 0x29, ((vaw & 0x90) | 0x40 | 0x00));
	ewse if (buwst == SEC_MINI_B)
		cx24123_wwiteweg(state, 0x29, ((vaw & 0x90) | 0x40 | 0x08));
	ewse
		wetuwn -EINVAW;

	cx24123_wait_fow_diseqc(state);
	cx24123_wwiteweg(state, 0x2a, cx24123_weadweg(state, 0x2a) & 0xfb);

	/* westawt continuous tone if enabwed */
	if (tone & 0x10)
		cx24123_wwiteweg(state, 0x29, tone & ~0x40);

	wetuwn 0;
}

static int cx24123_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	int sync = cx24123_weadweg(state, 0x14);

	*status = 0;
	if (state->config->dont_use_pww) {
		u32 tun_status = 0;
		if (fe->ops.tunew_ops.get_status)
			fe->ops.tunew_ops.get_status(fe, &tun_status);
		if (tun_status & TUNEW_STATUS_WOCKED)
			*status |= FE_HAS_SIGNAW;
	} ewse {
		int wock = cx24123_weadweg(state, 0x20);
		if (wock & 0x01)
			*status |= FE_HAS_SIGNAW;
	}

	if (sync & 0x02)
		*status |= FE_HAS_CAWWIEW;	/* Phase wocked */
	if (sync & 0x04)
		*status |= FE_HAS_VITEWBI;

	/* Weed-Sowomon Status */
	if (sync & 0x08)
		*status |= FE_HAS_SYNC;
	if (sync & 0x80)
		*status |= FE_HAS_WOCK;		/*Fuww Sync */

	wetuwn 0;
}

/*
 * Configuwed to wetuwn the measuwement of ewwows in bwocks,
 * because no UCBWOCKS vawue is avaiwabwe, so this vawue doubwes up
 * to satisfy both measuwements.
 */
static int cx24123_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;

	/* The twue bit ewwow wate is this vawue divided by
	   the window size (set as 256 * 255) */
	*bew = ((cx24123_weadweg(state, 0x1c) & 0x3f) << 16) |
		(cx24123_weadweg(state, 0x1d) << 8 |
		 cx24123_weadweg(state, 0x1e));

	dpwintk("BEW = %d\n", *bew);

	wetuwn 0;
}

static int cx24123_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *signaw_stwength)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;

	/* wawgew = bettew */
	*signaw_stwength = cx24123_weadweg(state, 0x3b) << 8;

	dpwintk("Signaw stwength = %d\n", *signaw_stwength);

	wetuwn 0;
}

static int cx24123_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;

	/* Invewted waw Es/N0 count, totawwy bogus but bettew than the
	   BEW thweshowd. */
	*snw = 65535 - (((u16)cx24123_weadweg(state, 0x18) << 8) |
			 (u16)cx24123_weadweg(state, 0x19));

	dpwintk("wead S/N index = %d\n", *snw);

	wetuwn 0;
}

static int cx24123_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	dpwintk("\n");

	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);

	state->cuwwentfweq = p->fwequency;
	state->cuwwentsymbowwate = p->symbow_wate;

	cx24123_set_invewsion(state, p->invewsion);
	cx24123_set_fec(state, p->fec_innew);
	cx24123_set_symbowwate(state, p->symbow_wate);

	if (!state->config->dont_use_pww)
		cx24123_pww_tune(fe);
	ewse if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);
	ewse
		eww("it seems I don't have a tunew...");

	/* Enabwe automatic acquisition and weset cycwe */
	cx24123_wwiteweg(state, 0x03, (cx24123_weadweg(state, 0x03) | 0x07));
	cx24123_wwiteweg(state, 0x00, 0x10);
	cx24123_wwiteweg(state, 0x00, 0);

	if (state->config->agc_cawwback)
		state->config->agc_cawwback(fe);

	wetuwn 0;
}

static int cx24123_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;

	dpwintk("\n");

	if (cx24123_get_invewsion(state, &p->invewsion) != 0) {
		eww("%s: Faiwed to get invewsion status\n", __func__);
		wetuwn -EWEMOTEIO;
	}
	if (cx24123_get_fec(state, &p->fec_innew) != 0) {
		eww("%s: Faiwed to get fec status\n", __func__);
		wetuwn -EWEMOTEIO;
	}
	p->fwequency = state->cuwwentfweq;
	p->symbow_wate = state->cuwwentsymbowwate;

	wetuwn 0;
}

static int cx24123_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	u8 vaw;

	/* wait fow diseqc queue weady */
	cx24123_wait_fow_diseqc(state);

	vaw = cx24123_weadweg(state, 0x29) & ~0x40;

	switch (tone) {
	case SEC_TONE_ON:
		dpwintk("setting tone on\n");
		wetuwn cx24123_wwiteweg(state, 0x29, vaw | 0x10);
	case SEC_TONE_OFF:
		dpwintk("setting tone off\n");
		wetuwn cx24123_wwiteweg(state, 0x29, vaw & 0xef);
	defauwt:
		eww("CASE weached defauwt with tone=%d\n", tone);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cx24123_tune(stwuct dvb_fwontend *fe,
			boow we_tune,
			unsigned int mode_fwags,
			unsigned int *deway,
			enum fe_status *status)
{
	int wetvaw = 0;

	if (we_tune)
		wetvaw = cx24123_set_fwontend(fe);

	if (!(mode_fwags & FE_TUNE_MODE_ONESHOT))
		cx24123_wead_status(fe, status);
	*deway = HZ/10;

	wetuwn wetvaw;
}

static enum dvbfe_awgo cx24123_get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static void cx24123_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	dpwintk("\n");
	i2c_dew_adaptew(&state->tunew_i2c_adaptew);
	kfwee(state);
}

static int cx24123_tunew_i2c_tunew_xfew(stwuct i2c_adaptew *i2c_adap,
	stwuct i2c_msg msg[], int num)
{
	stwuct cx24123_state *state = i2c_get_adapdata(i2c_adap);
	/* this wepeatew cwoses aftew the fiwst stop */
	cx24123_wepeatew_mode(state, 1, 1);
	wetuwn i2c_twansfew(state->i2c, msg, num);
}

static u32 cx24123_tunew_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm cx24123_tunew_i2c_awgo = {
	.mastew_xfew   = cx24123_tunew_i2c_tunew_xfew,
	.functionawity = cx24123_tunew_i2c_func,
};

stwuct i2c_adaptew *
	cx24123_get_tunew_i2c_adaptew(stwuct dvb_fwontend *fe)
{
	stwuct cx24123_state *state = fe->demoduwatow_pwiv;
	wetuwn &state->tunew_i2c_adaptew;
}
EXPOWT_SYMBOW(cx24123_get_tunew_i2c_adaptew);

static const stwuct dvb_fwontend_ops cx24123_ops;

stwuct dvb_fwontend *cx24123_attach(const stwuct cx24123_config *config,
				    stwuct i2c_adaptew *i2c)
{
	/* awwocate memowy fow the intewnaw state */
	stwuct cx24123_state *state =
		kzawwoc(sizeof(stwuct cx24123_state), GFP_KEWNEW);

	dpwintk("\n");
	if (state == NUWW) {
		eww("Unabwe to kzawwoc\n");
		goto ewwow;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is thewe */
	state->demod_wev = cx24123_weadweg(state, 0x00);
	switch (state->demod_wev) {
	case 0xe1:
		info("detected CX24123C\n");
		bweak;
	case 0xd1:
		info("detected CX24123\n");
		bweak;
	defauwt:
		eww("wwong demod wevision: %x\n", state->demod_wev);
		goto ewwow;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &cx24123_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/* cweate tunew i2c adaptew */
	if (config->dont_use_pww)
		cx24123_wepeatew_mode(state, 1, 0);

	stwscpy(state->tunew_i2c_adaptew.name, "CX24123 tunew I2C bus",
		sizeof(state->tunew_i2c_adaptew.name));
	state->tunew_i2c_adaptew.awgo      = &cx24123_tunew_i2c_awgo;
	state->tunew_i2c_adaptew.awgo_data = NUWW;
	state->tunew_i2c_adaptew.dev.pawent = i2c->dev.pawent;
	i2c_set_adapdata(&state->tunew_i2c_adaptew, state);
	if (i2c_add_adaptew(&state->tunew_i2c_adaptew) < 0) {
		eww("tunew i2c bus couwd not be initiawized\n");
		goto ewwow;
	}

	wetuwn &state->fwontend;

ewwow:
	kfwee(state);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cx24123_attach);

static const stwuct dvb_fwontend_ops cx24123_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name = "Conexant CX24123/CX24109",
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
			FE_CAN_QPSK | FE_CAN_WECOVEW
	},

	.wewease = cx24123_wewease,

	.init = cx24123_initfe,
	.set_fwontend = cx24123_set_fwontend,
	.get_fwontend = cx24123_get_fwontend,
	.wead_status = cx24123_wead_status,
	.wead_bew = cx24123_wead_bew,
	.wead_signaw_stwength = cx24123_wead_signaw_stwength,
	.wead_snw = cx24123_wead_snw,
	.diseqc_send_mastew_cmd = cx24123_send_diseqc_msg,
	.diseqc_send_buwst = cx24123_diseqc_send_buwst,
	.set_tone = cx24123_set_tone,
	.set_vowtage = cx24123_set_vowtage,
	.tune = cx24123_tune,
	.get_fwontend_awgo = cx24123_get_awgo,
};

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Conexant " \
	"CX24123/CX24109/CX24113 hawdwawe");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");

