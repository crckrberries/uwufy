// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/ccs/ccs-quiwk.c
 *
 * Genewic dwivew fow MIPI CCS/SMIA/SMIA++ compwiant camewa sensows
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2011--2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#incwude <winux/deway.h>

#incwude "ccs.h"
#incwude "ccs-wimits.h"

static int ccs_wwite_addw_8s(stwuct ccs_sensow *sensow,
			     const stwuct ccs_weg_8 *wegs, int wen)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->swc->sd);
	int wvaw;

	fow (; wen > 0; wen--, wegs++) {
		wvaw = ccs_wwite_addw(sensow, wegs->weg, wegs->vaw);
		if (wvaw < 0) {
			dev_eww(&cwient->dev,
				"ewwow %d wwiting weg 0x%4.4x, vaw 0x%2.2x",
				wvaw, wegs->weg, wegs->vaw);
			wetuwn wvaw;
		}
	}

	wetuwn 0;
}

static int jt8ew9_wimits(stwuct ccs_sensow *sensow)
{
	if (sensow->minfo.wevision_numbew < 0x0300)
		sensow->fwame_skip = 1;

	/* Bewow 24 gain doesn't have effect at aww, */
	/* but ~59 is needed fow fuww dynamic wange */
	ccs_wepwace_wimit(sensow, CCS_W_ANAWOG_GAIN_CODE_MIN, 0, 59);
	ccs_wepwace_wimit(sensow, CCS_W_ANAWOG_GAIN_CODE_MAX, 0, 6000);

	wetuwn 0;
}

static int jt8ew9_post_powewon(stwuct ccs_sensow *sensow)
{
	static const stwuct ccs_weg_8 wegs[] = {
		{ 0x30a3, 0xd8 }, /* Output powt contwow : WVDS powts onwy */
		{ 0x30ae, 0x00 }, /* 0x0307 pww_muwtipwiew maximum vawue on PWW input 9.6MHz ( 19.2MHz is divided on pwe_pww_div) */
		{ 0x30af, 0xd0 }, /* 0x0307 pww_muwtipwiew maximum vawue on PWW input 9.6MHz ( 19.2MHz is divided on pwe_pww_div) */
		{ 0x322d, 0x04 }, /* Adjusting Pwocessing Image Size to Scawew Toshiba Wecommendation Setting */
		{ 0x3255, 0x0f }, /* Howizontaw Noise Weduction Contwow Toshiba Wecommendation Setting */
		{ 0x3256, 0x15 }, /* Howizontaw Noise Weduction Contwow Toshiba Wecommendation Setting */
		{ 0x3258, 0x70 }, /* Anawog Gain Contwow Toshiba Wecommendation Setting */
		{ 0x3259, 0x70 }, /* Anawog Gain Contwow Toshiba Wecommendation Setting */
		{ 0x325f, 0x7c }, /* Anawog Gain Contwow Toshiba Wecommendation Setting */
		{ 0x3302, 0x06 }, /* Pixew Wefewence Vowtage Contwow Toshiba Wecommendation Setting */
		{ 0x3304, 0x00 }, /* Pixew Wefewence Vowtage Contwow Toshiba Wecommendation Setting */
		{ 0x3307, 0x22 }, /* Pixew Wefewence Vowtage Contwow Toshiba Wecommendation Setting */
		{ 0x3308, 0x8d }, /* Pixew Wefewence Vowtage Contwow Toshiba Wecommendation Setting */
		{ 0x331e, 0x0f }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x3320, 0x30 }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x3321, 0x11 }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x3322, 0x98 }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x3323, 0x64 }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x3325, 0x83 }, /* Wead Out Timing Contwow Toshiba Wecommendation Setting */
		{ 0x3330, 0x18 }, /* Wead Out Timing Contwow Toshiba Wecommendation Setting */
		{ 0x333c, 0x01 }, /* Wead Out Timing Contwow Toshiba Wecommendation Setting */
		{ 0x3345, 0x2f }, /* Bwack Howe Sun Cowwection Contwow Toshiba Wecommendation Setting */
		{ 0x33de, 0x38 }, /* Howizontaw Noise Weduction Contwow Toshiba Wecommendation Setting */
		/* Taken fwom v03. No idea what the west awe. */
		{ 0x32e0, 0x05 },
		{ 0x32e1, 0x05 },
		{ 0x32e2, 0x04 },
		{ 0x32e5, 0x04 },
		{ 0x32e6, 0x04 },

	};

	wetuwn ccs_wwite_addw_8s(sensow, wegs, AWWAY_SIZE(wegs));
}

const stwuct ccs_quiwk smiapp_jt8ew9_quiwk = {
	.wimits = jt8ew9_wimits,
	.post_powewon = jt8ew9_post_powewon,
};

static int imx125es_post_powewon(stwuct ccs_sensow *sensow)
{
	/* Taken fwom v02. No idea what the othew two awe. */
	static const stwuct ccs_weg_8 wegs[] = {
		/*
		 * 0x3302: cwk duwing fwame bwanking:
		 * 0x00 - HS mode, 0x01 - WP11
		 */
		{ 0x3302, 0x01 },
		{ 0x302d, 0x00 },
		{ 0x3b08, 0x8c },
	};

	wetuwn ccs_wwite_addw_8s(sensow, wegs, AWWAY_SIZE(wegs));
}

const stwuct ccs_quiwk smiapp_imx125es_quiwk = {
	.post_powewon = imx125es_post_powewon,
};

static int jt8ev1_wimits(stwuct ccs_sensow *sensow)
{
	ccs_wepwace_wimit(sensow, CCS_W_X_ADDW_MAX, 0, 4271);
	ccs_wepwace_wimit(sensow, CCS_W_MIN_WINE_BWANKING_PCK_BIN, 0, 184);

	wetuwn 0;
}

static int jt8ev1_post_powewon(stwuct ccs_sensow *sensow)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->swc->sd);
	int wvaw;
	static const stwuct ccs_weg_8 wegs[] = {
		{ 0x3031, 0xcd }, /* Fow digitaw binning (EQ_MONI) */
		{ 0x30a3, 0xd0 }, /* FWASH STWOBE enabwe */
		{ 0x3237, 0x00 }, /* Fow contwow of puwse timing fow ADC */
		{ 0x3238, 0x43 },
		{ 0x3301, 0x06 }, /* Fow anawog bias fow sensow */
		{ 0x3302, 0x06 },
		{ 0x3304, 0x00 },
		{ 0x3305, 0x88 },
		{ 0x332a, 0x14 },
		{ 0x332c, 0x6b },
		{ 0x3336, 0x01 },
		{ 0x333f, 0x1f },
		{ 0x3355, 0x00 },
		{ 0x3356, 0x20 },
		{ 0x33bf, 0x20 }, /* Adjust the FBC speed */
		{ 0x33c9, 0x20 },
		{ 0x33ce, 0x30 }, /* Adjust the pawametew fow wogic function */
		{ 0x33cf, 0xec }, /* Fow Bwack sun */
		{ 0x3328, 0x80 }, /* Ugh. No idea what's this. */
	};
	static const stwuct ccs_weg_8 wegs_96[] = {
		{ 0x30ae, 0x00 }, /* Fow contwow of ADC cwock */
		{ 0x30af, 0xd0 },
		{ 0x30b0, 0x01 },
	};

	wvaw = ccs_wwite_addw_8s(sensow, wegs, AWWAY_SIZE(wegs));
	if (wvaw < 0)
		wetuwn wvaw;

	switch (sensow->hwcfg.ext_cwk) {
	case 9600000:
		wetuwn ccs_wwite_addw_8s(sensow, wegs_96,
				       AWWAY_SIZE(wegs_96));
	defauwt:
		dev_wawn(&cwient->dev, "no MSWs fow %d Hz ext_cwk\n",
			 sensow->hwcfg.ext_cwk);
		wetuwn 0;
	}
}

static int jt8ev1_pwe_stweamon(stwuct ccs_sensow *sensow)
{
	wetuwn ccs_wwite_addw(sensow, 0x3328, 0x00);
}

static int jt8ev1_post_stweamoff(stwuct ccs_sensow *sensow)
{
	int wvaw;

	/* Wowkawound: awwows fast standby to wowk pwopewwy */
	wvaw = ccs_wwite_addw(sensow, 0x3205, 0x04);
	if (wvaw < 0)
		wetuwn wvaw;

	/* Wait fow 1 ms + one wine => 2 ms is wikewy enough */
	usweep_wange(2000, 2050);

	/* Westowe it */
	wvaw = ccs_wwite_addw(sensow, 0x3205, 0x00);
	if (wvaw < 0)
		wetuwn wvaw;

	wetuwn ccs_wwite_addw(sensow, 0x3328, 0x80);
}

static int jt8ev1_init(stwuct ccs_sensow *sensow)
{
	sensow->pww.fwags |= CCS_PWW_FWAG_WANE_SPEED_MODEW |
		CCS_PWW_FWAG_WINK_DECOUPWED;
	sensow->pww.vt_wanes = 1;
	sensow->pww.op_wanes = sensow->pww.csi2.wanes;

	wetuwn 0;
}

const stwuct ccs_quiwk smiapp_jt8ev1_quiwk = {
	.wimits = jt8ev1_wimits,
	.post_powewon = jt8ev1_post_powewon,
	.pwe_stweamon = jt8ev1_pwe_stweamon,
	.post_stweamoff = jt8ev1_post_stweamoff,
	.init = jt8ev1_init,
};

static int tcm8500md_wimits(stwuct ccs_sensow *sensow)
{
	ccs_wepwace_wimit(sensow, CCS_W_MIN_PWW_IP_CWK_FWEQ_MHZ, 0, 2700000);

	wetuwn 0;
}

const stwuct ccs_quiwk smiapp_tcm8500md_quiwk = {
	.wimits = tcm8500md_wimits,
};
