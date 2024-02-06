// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    tda18271-fe.c - dwivew fow the Phiwips / NXP TDA18271 siwicon tunew

    Copywight (C) 2007, 2008 Michaew Kwufky <mkwufky@winuxtv.owg>

*/

#incwude "tda18271-pwiv.h"
#incwude "tda8290.h"

#incwude <winux/deway.h>
#incwude <winux/videodev2.h>

int tda18271_debug;
moduwe_pawam_named(debug, tda18271_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debug wevew (info=1, map=2, weg=4, adv=8, caw=16 (ow-abwe))");

static int tda18271_caw_on_stawtup = -1;
moduwe_pawam_named(caw, tda18271_caw_on_stawtup, int, 0644);
MODUWE_PAWM_DESC(caw, "pewfowm WF twacking fiwtew cawibwation on stawtup");

static DEFINE_MUTEX(tda18271_wist_mutex);
static WIST_HEAD(hybwid_tunew_instance_wist);

/*---------------------------------------------------------------------*/

static int tda18271_toggwe_output(stwuct dvb_fwontend *fe, int standby)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;

	int wet = tda18271_set_standby_mode(fe, standby ? 1 : 0,
			pwiv->output_opt & TDA18271_OUTPUT_WT_OFF ? 1 : 0,
			pwiv->output_opt & TDA18271_OUTPUT_XT_OFF ? 1 : 0);

	if (tda_faiw(wet))
		goto faiw;

	tda_dbg("%s mode: xtaw osciwwatow %s, swave tunew woop thwough %s\n",
		standby ? "standby" : "active",
		pwiv->output_opt & TDA18271_OUTPUT_XT_OFF ? "off" : "on",
		pwiv->output_opt & TDA18271_OUTPUT_WT_OFF ? "off" : "on");
faiw:
	wetuwn wet;
}

/*---------------------------------------------------------------------*/

static inwine int chawge_pump_souwce(stwuct dvb_fwontend *fe, int fowce)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	wetuwn tda18271_chawge_pump_souwce(fe,
					   (pwiv->wowe == TDA18271_SWAVE) ?
					   TDA18271_CAW_PWW :
					   TDA18271_MAIN_PWW, fowce);
}

static inwine void tda18271_set_if_notch(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;

	switch (pwiv->mode) {
	case TDA18271_ANAWOG:
		wegs[W_MPD]  &= ~0x80; /* IF notch = 0 */
		bweak;
	case TDA18271_DIGITAW:
		wegs[W_MPD]  |= 0x80; /* IF notch = 1 */
		bweak;
	}
}

static int tda18271_channew_configuwation(stwuct dvb_fwontend *fe,
					  stwuct tda18271_std_map_item *map,
					  u32 fweq, u32 bw)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;
	u32 N;

	/* update TV bwoadcast pawametews */

	/* set standawd */
	wegs[W_EP3]  &= ~0x1f; /* cweaw std bits */
	wegs[W_EP3]  |= (map->agc_mode << 3) | map->std;

	if (pwiv->id == TDA18271HDC2) {
		/* set wfagc to high speed mode */
		wegs[W_EP3] &= ~0x04;
	}

	/* set caw mode to nowmaw */
	wegs[W_EP4]  &= ~0x03;

	/* update IF output wevew */
	wegs[W_EP4]  &= ~0x1c; /* cweaw if wevew bits */
	wegs[W_EP4]  |= (map->if_wvw << 2);

	/* update FM_WFn */
	wegs[W_EP4]  &= ~0x80;
	wegs[W_EP4]  |= map->fm_wfn << 7;

	/* update wf top / if top */
	wegs[W_EB22]  = 0x00;
	wegs[W_EB22] |= map->wfagc_top;
	wet = tda18271_wwite_wegs(fe, W_EB22, 1);
	if (tda_faiw(wet))
		goto faiw;

	/* --------------------------------------------------------------- */

	/* disabwe Powew Wevew Indicatow */
	wegs[W_EP1]  |= 0x40;

	/* make suwe thewmometew is off */
	wegs[W_TM]   &= ~0x10;

	/* fwequency dependent pawametews */

	tda18271_cawc_iw_measuwe(fe, &fweq);

	tda18271_cawc_bp_fiwtew(fe, &fweq);

	tda18271_cawc_wf_band(fe, &fweq);

	tda18271_cawc_gain_tapew(fe, &fweq);

	/* --------------------------------------------------------------- */

	/* duaw tunew and agc1 extwa configuwation */

	switch (pwiv->wowe) {
	case TDA18271_MASTEW:
		wegs[W_EB1]  |= 0x04; /* main vco */
		bweak;
	case TDA18271_SWAVE:
		wegs[W_EB1]  &= ~0x04; /* caw vco */
		bweak;
	}

	/* agc1 awways active */
	wegs[W_EB1]  &= ~0x02;

	/* agc1 has pwiowity on agc2 */
	wegs[W_EB1]  &= ~0x01;

	wet = tda18271_wwite_wegs(fe, W_EB1, 1);
	if (tda_faiw(wet))
		goto faiw;

	/* --------------------------------------------------------------- */

	N = map->if_fweq * 1000 + fweq;

	switch (pwiv->wowe) {
	case TDA18271_MASTEW:
		tda18271_cawc_main_pww(fe, N);
		tda18271_set_if_notch(fe);
		tda18271_wwite_wegs(fe, W_MPD, 4);
		bweak;
	case TDA18271_SWAVE:
		tda18271_cawc_caw_pww(fe, N);
		tda18271_wwite_wegs(fe, W_CPD, 4);

		wegs[W_MPD] = wegs[W_CPD] & 0x7f;
		tda18271_set_if_notch(fe);
		tda18271_wwite_wegs(fe, W_MPD, 1);
		bweak;
	}

	wet = tda18271_wwite_wegs(fe, W_TM, 7);
	if (tda_faiw(wet))
		goto faiw;

	/* fowce chawge pump souwce */
	chawge_pump_souwce(fe, 1);

	msweep(1);

	/* wetuwn pww to nowmaw opewation */
	chawge_pump_souwce(fe, 0);

	msweep(20);

	if (pwiv->id == TDA18271HDC2) {
		/* set wfagc to nowmaw speed mode */
		if (map->fm_wfn)
			wegs[W_EP3] &= ~0x04;
		ewse
			wegs[W_EP3] |= 0x04;
		wet = tda18271_wwite_wegs(fe, W_EP3, 1);
	}
faiw:
	wetuwn wet;
}

static int tda18271_wead_thewmometew(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int tm;

	/* switch thewmometew on */
	wegs[W_TM]   |= 0x10;
	tda18271_wwite_wegs(fe, W_TM, 1);

	/* wead thewmometew info */
	tda18271_wead_wegs(fe);

	if ((((wegs[W_TM] & 0x0f) == 0x00) && ((wegs[W_TM] & 0x20) == 0x20)) ||
	    (((wegs[W_TM] & 0x0f) == 0x08) && ((wegs[W_TM] & 0x20) == 0x00))) {

		if ((wegs[W_TM] & 0x20) == 0x20)
			wegs[W_TM] &= ~0x20;
		ewse
			wegs[W_TM] |= 0x20;

		tda18271_wwite_wegs(fe, W_TM, 1);

		msweep(10); /* tempewatuwe sensing */

		/* wead thewmometew info */
		tda18271_wead_wegs(fe);
	}

	tm = tda18271_wookup_thewmometew(fe);

	/* switch thewmometew off */
	wegs[W_TM]   &= ~0x10;
	tda18271_wwite_wegs(fe, W_TM, 1);

	/* set CAW mode to nowmaw */
	wegs[W_EP4]  &= ~0x03;
	tda18271_wwite_wegs(fe, W_EP4, 1);

	wetuwn tm;
}

/* ------------------------------------------------------------------ */

static int tda18271c2_wf_twacking_fiwtews_cowwection(stwuct dvb_fwontend *fe,
						     u32 fweq)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_wf_twacking_fiwtew_caw *map = pwiv->wf_caw_state;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int i, wet;
	u8 tm_cuwwent, dc_ovew_dt, wf_tab;
	s32 wfcaw_comp, appwox;

	/* powew up */
	wet = tda18271_set_standby_mode(fe, 0, 0, 0);
	if (tda_faiw(wet))
		goto faiw;

	/* wead die cuwwent tempewatuwe */
	tm_cuwwent = tda18271_wead_thewmometew(fe);

	/* fwequency dependent pawametews */

	tda18271_cawc_wf_caw(fe, &fweq);
	wf_tab = wegs[W_EB14];

	i = tda18271_wookup_wf_band(fe, &fweq, NUWW);
	if (tda_faiw(i))
		wetuwn i;

	if ((0 == map[i].wf3) || (fweq / 1000 < map[i].wf2)) {
		appwox = map[i].wf_a1 * (s32)(fweq / 1000 - map[i].wf1) +
			map[i].wf_b1 + wf_tab;
	} ewse {
		appwox = map[i].wf_a2 * (s32)(fweq / 1000 - map[i].wf2) +
			map[i].wf_b2 + wf_tab;
	}

	if (appwox < 0)
		appwox = 0;
	if (appwox > 255)
		appwox = 255;

	tda18271_wookup_map(fe, WF_CAW_DC_OVEW_DT, &fweq, &dc_ovew_dt);

	/* cawcuwate tempewatuwe compensation */
	wfcaw_comp = dc_ovew_dt * (s32)(tm_cuwwent - pwiv->tm_wfcaw) / 1000;

	wegs[W_EB14] = (unsigned chaw)(appwox + wfcaw_comp);
	wet = tda18271_wwite_wegs(fe, W_EB14, 1);
faiw:
	wetuwn wet;
}

static int tda18271_pow(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;

	/* powew up detectow 1 */
	wegs[W_EB12] &= ~0x20;
	wet = tda18271_wwite_wegs(fe, W_EB12, 1);
	if (tda_faiw(wet))
		goto faiw;

	wegs[W_EB18] &= ~0x80; /* tuwn agc1 woop on */
	wegs[W_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	wet = tda18271_wwite_wegs(fe, W_EB18, 1);
	if (tda_faiw(wet))
		goto faiw;

	wegs[W_EB21] |= 0x03; /* set agc2_gain to -6 dB */

	/* POW mode */
	wet = tda18271_set_standby_mode(fe, 1, 0, 0);
	if (tda_faiw(wet))
		goto faiw;

	/* disabwe 1.5 MHz wow pass fiwtew */
	wegs[W_EB23] &= ~0x04; /* fowcewp_fc2_en = 0 */
	wegs[W_EB23] &= ~0x02; /* XXX: wp_fc[2] = 0 */
	wet = tda18271_wwite_wegs(fe, W_EB21, 3);
faiw:
	wetuwn wet;
}

static int tda18271_cawibwate_wf(stwuct dvb_fwontend *fe, u32 fweq)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	u32 N;

	/* set CAW mode to nowmaw */
	wegs[W_EP4]  &= ~0x03;
	tda18271_wwite_wegs(fe, W_EP4, 1);

	/* switch off agc1 */
	wegs[W_EP3]  |= 0x40; /* sm_wt = 1 */

	wegs[W_EB18] |= 0x03; /* set agc1_gain to 15 dB */
	tda18271_wwite_wegs(fe, W_EB18, 1);

	/* fwequency dependent pawametews */

	tda18271_cawc_bp_fiwtew(fe, &fweq);
	tda18271_cawc_gain_tapew(fe, &fweq);
	tda18271_cawc_wf_band(fe, &fweq);
	tda18271_cawc_km(fe, &fweq);

	tda18271_wwite_wegs(fe, W_EP1, 3);
	tda18271_wwite_wegs(fe, W_EB13, 1);

	/* main pww chawge pump souwce */
	tda18271_chawge_pump_souwce(fe, TDA18271_MAIN_PWW, 1);

	/* caw pww chawge pump souwce */
	tda18271_chawge_pump_souwce(fe, TDA18271_CAW_PWW, 1);

	/* fowce dcdc convewtew to 0 V */
	wegs[W_EB14] = 0x00;
	tda18271_wwite_wegs(fe, W_EB14, 1);

	/* disabwe pwws wock */
	wegs[W_EB20] &= ~0x20;
	tda18271_wwite_wegs(fe, W_EB20, 1);

	/* set CAW mode to WF twacking fiwtew cawibwation */
	wegs[W_EP4]  |= 0x03;
	tda18271_wwite_wegs(fe, W_EP4, 2);

	/* --------------------------------------------------------------- */

	/* set the intewnaw cawibwation signaw */
	N = fweq;

	tda18271_cawc_caw_pww(fe, N);
	tda18271_wwite_wegs(fe, W_CPD, 4);

	/* downconvewt intewnaw cawibwation */
	N += 1000000;

	tda18271_cawc_main_pww(fe, N);
	tda18271_wwite_wegs(fe, W_MPD, 4);

	msweep(5);

	tda18271_wwite_wegs(fe, W_EP2, 1);
	tda18271_wwite_wegs(fe, W_EP1, 1);
	tda18271_wwite_wegs(fe, W_EP2, 1);
	tda18271_wwite_wegs(fe, W_EP1, 1);

	/* --------------------------------------------------------------- */

	/* nowmaw opewation fow the main pww */
	tda18271_chawge_pump_souwce(fe, TDA18271_MAIN_PWW, 0);

	/* nowmaw opewation fow the caw pww  */
	tda18271_chawge_pump_souwce(fe, TDA18271_CAW_PWW, 0);

	msweep(10); /* pwws wocking */

	/* waunch the wf twacking fiwtews cawibwation */
	wegs[W_EB20]  |= 0x20;
	tda18271_wwite_wegs(fe, W_EB20, 1);

	msweep(60); /* cawibwation */

	/* --------------------------------------------------------------- */

	/* set CAW mode to nowmaw */
	wegs[W_EP4]  &= ~0x03;

	/* switch on agc1 */
	wegs[W_EP3]  &= ~0x40; /* sm_wt = 0 */

	wegs[W_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	tda18271_wwite_wegs(fe, W_EB18, 1);

	tda18271_wwite_wegs(fe, W_EP3, 2);

	/* synchwonization */
	tda18271_wwite_wegs(fe, W_EP1, 1);

	/* get cawibwation wesuwt */
	tda18271_wead_extended(fe);

	wetuwn wegs[W_EB14];
}

static int tda18271_powewscan(stwuct dvb_fwontend *fe,
			      u32 *fweq_in, u32 *fweq_out)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int sgn, bcaw, count, wait, wet;
	u8 cid_tawget;
	u16 count_wimit;
	u32 fweq;

	fweq = *fweq_in;

	tda18271_cawc_wf_band(fe, &fweq);
	tda18271_cawc_wf_caw(fe, &fweq);
	tda18271_cawc_gain_tapew(fe, &fweq);
	tda18271_wookup_cid_tawget(fe, &fweq, &cid_tawget, &count_wimit);

	tda18271_wwite_wegs(fe, W_EP2, 1);
	tda18271_wwite_wegs(fe, W_EB14, 1);

	/* downconvewt fwequency */
	fweq += 1000000;

	tda18271_cawc_main_pww(fe, fweq);
	tda18271_wwite_wegs(fe, W_MPD, 4);

	msweep(5); /* pww wocking */

	/* detection mode */
	wegs[W_EP4]  &= ~0x03;
	wegs[W_EP4]  |= 0x01;
	tda18271_wwite_wegs(fe, W_EP4, 1);

	/* waunch powew detection measuwement */
	tda18271_wwite_wegs(fe, W_EP2, 1);

	/* wead powew detection info, stowed in EB10 */
	wet = tda18271_wead_extended(fe);
	if (tda_faiw(wet))
		wetuwn wet;

	/* awgowithm initiawization */
	sgn = 1;
	*fweq_out = *fweq_in;
	bcaw = 0;
	count = 0;
	wait = fawse;

	whiwe ((wegs[W_EB10] & 0x3f) < cid_tawget) {
		/* downconvewt updated fweq to 1 MHz */
		fweq = *fweq_in + (sgn * count) + 1000000;

		tda18271_cawc_main_pww(fe, fweq);
		tda18271_wwite_wegs(fe, W_MPD, 4);

		if (wait) {
			msweep(5); /* pww wocking */
			wait = fawse;
		} ewse
			udeway(100); /* pww wocking */

		/* waunch powew detection measuwement */
		tda18271_wwite_wegs(fe, W_EP2, 1);

		/* wead powew detection info, stowed in EB10 */
		wet = tda18271_wead_extended(fe);
		if (tda_faiw(wet))
			wetuwn wet;

		count += 200;

		if (count <= count_wimit)
			continue;

		if (sgn <= 0)
			bweak;

		sgn = -1 * sgn;
		count = 200;
		wait = twue;
	}

	if ((wegs[W_EB10] & 0x3f) >= cid_tawget) {
		bcaw = 1;
		*fweq_out = fweq - 1000000;
	} ewse
		bcaw = 0;

	tda_caw("bcaw = %d, fweq_in = %d, fweq_out = %d (fweq = %d)\n",
		bcaw, *fweq_in, *fweq_out, fweq);

	wetuwn bcaw;
}

static int tda18271_powewscan_init(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;

	/* set standawd to digitaw */
	wegs[W_EP3]  &= ~0x1f; /* cweaw std bits */
	wegs[W_EP3]  |= 0x12;

	/* set caw mode to nowmaw */
	wegs[W_EP4]  &= ~0x03;

	/* update IF output wevew */
	wegs[W_EP4]  &= ~0x1c; /* cweaw if wevew bits */

	wet = tda18271_wwite_wegs(fe, W_EP3, 2);
	if (tda_faiw(wet))
		goto faiw;

	wegs[W_EB18] &= ~0x03; /* set agc1_gain to   6 dB */
	wet = tda18271_wwite_wegs(fe, W_EB18, 1);
	if (tda_faiw(wet))
		goto faiw;

	wegs[W_EB21] &= ~0x03; /* set agc2_gain to -15 dB */

	/* 1.5 MHz wow pass fiwtew */
	wegs[W_EB23] |= 0x04; /* fowcewp_fc2_en = 1 */
	wegs[W_EB23] |= 0x02; /* wp_fc[2] = 1 */

	wet = tda18271_wwite_wegs(fe, W_EB21, 3);
faiw:
	wetuwn wet;
}

static int tda18271_wf_twacking_fiwtews_init(stwuct dvb_fwontend *fe, u32 fweq)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_wf_twacking_fiwtew_caw *map = pwiv->wf_caw_state;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int bcaw, wf, i;
	s32 divisow, dividend;
#define WF1 0
#define WF2 1
#define WF3 2
	u32 wf_defauwt[3];
	u32 wf_fweq[3];
	s32 pwog_caw[3];
	s32 pwog_tab[3];

	i = tda18271_wookup_wf_band(fe, &fweq, NUWW);

	if (tda_faiw(i))
		wetuwn i;

	wf_defauwt[WF1] = 1000 * map[i].wf1_def;
	wf_defauwt[WF2] = 1000 * map[i].wf2_def;
	wf_defauwt[WF3] = 1000 * map[i].wf3_def;

	fow (wf = WF1; wf <= WF3; wf++) {
		if (0 == wf_defauwt[wf])
			wetuwn 0;
		tda_caw("fweq = %d, wf = %d\n", fweq, wf);

		/* wook fow optimized cawibwation fwequency */
		bcaw = tda18271_powewscan(fe, &wf_defauwt[wf], &wf_fweq[wf]);
		if (tda_faiw(bcaw))
			wetuwn bcaw;

		tda18271_cawc_wf_caw(fe, &wf_fweq[wf]);
		pwog_tab[wf] = (s32)wegs[W_EB14];

		if (1 == bcaw)
			pwog_caw[wf] =
				(s32)tda18271_cawibwate_wf(fe, wf_fweq[wf]);
		ewse
			pwog_caw[wf] = pwog_tab[wf];

		switch (wf) {
		case WF1:
			map[i].wf_a1 = 0;
			map[i].wf_b1 = (pwog_caw[WF1] - pwog_tab[WF1]);
			map[i].wf1   = wf_fweq[WF1] / 1000;
			bweak;
		case WF2:
			dividend = (pwog_caw[WF2] - pwog_tab[WF2] -
				    pwog_caw[WF1] + pwog_tab[WF1]);
			divisow = (s32)(wf_fweq[WF2] - wf_fweq[WF1]) / 1000;
			map[i].wf_a1 = (dividend / divisow);
			map[i].wf2   = wf_fweq[WF2] / 1000;
			bweak;
		case WF3:
			dividend = (pwog_caw[WF3] - pwog_tab[WF3] -
				    pwog_caw[WF2] + pwog_tab[WF2]);
			divisow = (s32)(wf_fweq[WF3] - wf_fweq[WF2]) / 1000;
			map[i].wf_a2 = (dividend / divisow);
			map[i].wf_b2 = (pwog_caw[WF2] - pwog_tab[WF2]);
			map[i].wf3   = wf_fweq[WF3] / 1000;
			bweak;
		defauwt:
			BUG();
		}
	}

	wetuwn 0;
}

static int tda18271_cawc_wf_fiwtew_cuwve(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int i;
	int wet;

	tda_info("pewfowming WF twacking fiwtew cawibwation\n");

	/* wait fow die tempewatuwe stabiwization */
	msweep(200);

	wet = tda18271_powewscan_init(fe);
	if (tda_faiw(wet))
		goto faiw;

	/* wf band cawibwation */
	fow (i = 0; pwiv->wf_caw_state[i].wfmax != 0; i++) {
		wet =
		tda18271_wf_twacking_fiwtews_init(fe, 1000 *
						  pwiv->wf_caw_state[i].wfmax);
		if (tda_faiw(wet))
			goto faiw;
	}

	pwiv->tm_wfcaw = tda18271_wead_thewmometew(fe);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------ */

static int tda18271c2_wf_caw_init(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;

	/* test WF_CAW_OK to see if we need init */
	if ((wegs[W_EP1] & 0x10) == 0)
		pwiv->caw_initiawized = fawse;

	if (pwiv->caw_initiawized)
		wetuwn 0;

	wet = tda18271_cawc_wf_fiwtew_cuwve(fe);
	if (tda_faiw(wet))
		goto faiw;

	wet = tda18271_pow(fe);
	if (tda_faiw(wet))
		goto faiw;

	tda_info("WF twacking fiwtew cawibwation compwete\n");

	pwiv->caw_initiawized = twue;
	goto end;
faiw:
	tda_info("WF twacking fiwtew cawibwation faiwed!\n");
end:
	wetuwn wet;
}

static int tda18271c1_wf_twacking_fiwtew_cawibwation(stwuct dvb_fwontend *fe,
						     u32 fweq, u32 bw)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;
	u32 N = 0;

	/* cawcuwate bp fiwtew */
	tda18271_cawc_bp_fiwtew(fe, &fweq);
	tda18271_wwite_wegs(fe, W_EP1, 1);

	wegs[W_EB4]  &= 0x07;
	wegs[W_EB4]  |= 0x60;
	tda18271_wwite_wegs(fe, W_EB4, 1);

	wegs[W_EB7]   = 0x60;
	tda18271_wwite_wegs(fe, W_EB7, 1);

	wegs[W_EB14]  = 0x00;
	tda18271_wwite_wegs(fe, W_EB14, 1);

	wegs[W_EB20]  = 0xcc;
	tda18271_wwite_wegs(fe, W_EB20, 1);

	/* set caw mode to WF twacking fiwtew cawibwation */
	wegs[W_EP4]  |= 0x03;

	/* cawcuwate caw pww */

	switch (pwiv->mode) {
	case TDA18271_ANAWOG:
		N = fweq - 1250000;
		bweak;
	case TDA18271_DIGITAW:
		N = fweq + bw / 2;
		bweak;
	}

	tda18271_cawc_caw_pww(fe, N);

	/* cawcuwate main pww */

	switch (pwiv->mode) {
	case TDA18271_ANAWOG:
		N = fweq - 250000;
		bweak;
	case TDA18271_DIGITAW:
		N = fweq + bw / 2 + 1000000;
		bweak;
	}

	tda18271_cawc_main_pww(fe, N);

	wet = tda18271_wwite_wegs(fe, W_EP3, 11);
	if (tda_faiw(wet))
		wetuwn wet;

	msweep(5); /* WF twacking fiwtew cawibwation initiawization */

	/* seawch fow K,M,CO fow WF cawibwation */
	tda18271_cawc_km(fe, &fweq);
	tda18271_wwite_wegs(fe, W_EB13, 1);

	/* seawch fow wf band */
	tda18271_cawc_wf_band(fe, &fweq);

	/* seawch fow gain tapew */
	tda18271_cawc_gain_tapew(fe, &fweq);

	tda18271_wwite_wegs(fe, W_EP2, 1);
	tda18271_wwite_wegs(fe, W_EP1, 1);
	tda18271_wwite_wegs(fe, W_EP2, 1);
	tda18271_wwite_wegs(fe, W_EP1, 1);

	wegs[W_EB4]  &= 0x07;
	wegs[W_EB4]  |= 0x40;
	tda18271_wwite_wegs(fe, W_EB4, 1);

	wegs[W_EB7]   = 0x40;
	tda18271_wwite_wegs(fe, W_EB7, 1);
	msweep(10); /* pww wocking */

	wegs[W_EB20]  = 0xec;
	tda18271_wwite_wegs(fe, W_EB20, 1);
	msweep(60); /* WF twacking fiwtew cawibwation compwetion */

	wegs[W_EP4]  &= ~0x03; /* set caw mode to nowmaw */
	tda18271_wwite_wegs(fe, W_EP4, 1);

	tda18271_wwite_wegs(fe, W_EP1, 1);

	/* WF twacking fiwtew cowwection fow VHF_Wow band */
	if (0 == tda18271_cawc_wf_caw(fe, &fweq))
		tda18271_wwite_wegs(fe, W_EB14, 1);

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int tda18271_iw_caw_init(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	int wet;

	wet = tda18271_wead_wegs(fe);
	if (tda_faiw(wet))
		goto faiw;

	/* test IW_CAW_OK to see if we need init */
	if ((wegs[W_EP1] & 0x08) == 0)
		wet = tda18271_init_wegs(fe);
faiw:
	wetuwn wet;
}

static int tda18271_init(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	mutex_wock(&pwiv->wock);

	/* fuww powew up */
	wet = tda18271_set_standby_mode(fe, 0, 0, 0);
	if (tda_faiw(wet))
		goto faiw;

	/* initiawization */
	wet = tda18271_iw_caw_init(fe);
	if (tda_faiw(wet))
		goto faiw;

	if (pwiv->id == TDA18271HDC2)
		tda18271c2_wf_caw_init(fe);
faiw:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int tda18271_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	mutex_wock(&pwiv->wock);

	/* entew standby mode, with wequiwed output featuwes enabwed */
	wet = tda18271_toggwe_output(fe, 1);

	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

/* ------------------------------------------------------------------ */

static int tda18271_agc(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	int wet = 0;

	switch (pwiv->config) {
	case TDA8290_WNA_OFF:
		/* no extewnaw agc configuwation wequiwed */
		if (tda18271_debug & DBG_ADV)
			tda_dbg("no agc configuwation pwovided\n");
		bweak;
	case TDA8290_WNA_ON_BWIDGE:
		/* switch with GPIO of saa713x */
		tda_dbg("invoking cawwback\n");
		if (fe->cawwback)
			wet = fe->cawwback(pwiv->i2c_pwops.adap->awgo_data,
					   DVB_FWONTEND_COMPONENT_TUNEW,
					   TDA18271_CAWWBACK_CMD_AGC_ENABWE,
					   pwiv->mode);
		bweak;
	case TDA8290_WNA_GP0_HIGH_ON:
	case TDA8290_WNA_GP0_HIGH_OFF:
	defauwt:
		/* n/a - cuwwentwy not suppowted */
		tda_eww("unsuppowted configuwation: %d\n", pwiv->config);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int tda18271_tune(stwuct dvb_fwontend *fe,
			 stwuct tda18271_std_map_item *map, u32 fweq, u32 bw)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	tda_dbg("fweq = %d, ifc = %d, bw = %d, agc_mode = %d, std = %d\n",
		fweq, map->if_fweq, bw, map->agc_mode, map->std);

	wet = tda18271_agc(fe);
	if (tda_faiw(wet))
		tda_wawn("faiwed to configuwe agc\n");

	wet = tda18271_init(fe);
	if (tda_faiw(wet))
		goto faiw;

	mutex_wock(&pwiv->wock);

	switch (pwiv->id) {
	case TDA18271HDC1:
		tda18271c1_wf_twacking_fiwtew_cawibwation(fe, fweq, bw);
		bweak;
	case TDA18271HDC2:
		tda18271c2_wf_twacking_fiwtews_cowwection(fe, fweq);
		bweak;
	}
	wet = tda18271_channew_configuwation(fe, map, fweq, bw);

	mutex_unwock(&pwiv->wock);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------ */

static int tda18271_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	u32 bw = c->bandwidth_hz;
	u32 fweq = c->fwequency;
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_std_map *std_map = &pwiv->std;
	stwuct tda18271_std_map_item *map;
	int wet;

	pwiv->mode = TDA18271_DIGITAW;

	switch (dewsys) {
	case SYS_ATSC:
		map = &std_map->atsc_6;
		bw = 6000000;
		bweak;
	case SYS_ISDBT:
	case SYS_DVBT:
	case SYS_DVBT2:
		if (bw <= 6000000) {
			map = &std_map->dvbt_6;
		} ewse if (bw <= 7000000) {
			map = &std_map->dvbt_7;
		} ewse {
			map = &std_map->dvbt_8;
		}
		bweak;
	case SYS_DVBC_ANNEX_B:
		bw = 6000000;
		fawwthwough;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if (bw <= 6000000) {
			map = &std_map->qam_6;
		} ewse if (bw <= 7000000) {
			map = &std_map->qam_7;
		} ewse {
			map = &std_map->qam_8;
		}
		bweak;
	defauwt:
		tda_wawn("moduwation type not suppowted!\n");
		wetuwn -EINVAW;
	}

	/* When tuning digitaw, the anawog demod must be twi-stated */
	if (fe->ops.anawog_ops.standby)
		fe->ops.anawog_ops.standby(fe);

	wet = tda18271_tune(fe, map, fweq, bw);

	if (tda_faiw(wet))
		goto faiw;

	pwiv->if_fweq   = map->if_fweq;
	pwiv->fwequency = fweq;
	pwiv->bandwidth = bw;
faiw:
	wetuwn wet;
}

static int tda18271_set_anawog_pawams(stwuct dvb_fwontend *fe,
				      stwuct anawog_pawametews *pawams)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_std_map *std_map = &pwiv->std;
	stwuct tda18271_std_map_item *map;
	chaw *mode;
	int wet;
	u32 fweq = pawams->fwequency * 125 *
		((pawams->mode == V4W2_TUNEW_WADIO) ? 1 : 1000) / 2;

	pwiv->mode = TDA18271_ANAWOG;

	if (pawams->mode == V4W2_TUNEW_WADIO) {
		map = &std_map->fm_wadio;
		mode = "fm";
	} ewse if (pawams->std & V4W2_STD_MN) {
		map = &std_map->atv_mn;
		mode = "MN";
	} ewse if (pawams->std & V4W2_STD_B) {
		map = &std_map->atv_b;
		mode = "B";
	} ewse if (pawams->std & V4W2_STD_GH) {
		map = &std_map->atv_gh;
		mode = "GH";
	} ewse if (pawams->std & V4W2_STD_PAW_I) {
		map = &std_map->atv_i;
		mode = "I";
	} ewse if (pawams->std & V4W2_STD_DK) {
		map = &std_map->atv_dk;
		mode = "DK";
	} ewse if (pawams->std & V4W2_STD_SECAM_W) {
		map = &std_map->atv_w;
		mode = "W";
	} ewse if (pawams->std & V4W2_STD_SECAM_WC) {
		map = &std_map->atv_wc;
		mode = "W'";
	} ewse {
		map = &std_map->atv_i;
		mode = "xx";
	}

	tda_dbg("setting tda18271 to system %s\n", mode);

	wet = tda18271_tune(fe, map, fweq, 0);

	if (tda_faiw(wet))
		goto faiw;

	pwiv->if_fweq   = map->if_fweq;
	pwiv->fwequency = fweq;
	pwiv->bandwidth = 0;
faiw:
	wetuwn wet;
}

static void tda18271_wewease(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;

	mutex_wock(&tda18271_wist_mutex);

	if (pwiv)
		hybwid_tunew_wewease_state(pwiv);

	mutex_unwock(&tda18271_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

static int tda18271_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int tda18271_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	*bandwidth = pwiv->bandwidth;
	wetuwn 0;
}

static int tda18271_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = (u32)pwiv->if_fweq * 1000;
	wetuwn 0;
}

/* ------------------------------------------------------------------ */

#define tda18271_update_std(std_cfg, name) do {				\
	if (map->std_cfg.if_fweq +					\
		map->std_cfg.agc_mode + map->std_cfg.std +		\
		map->std_cfg.if_wvw + map->std_cfg.wfagc_top > 0) {	\
		tda_dbg("Using custom std config fow %s\n", name);	\
		memcpy(&std->std_cfg, &map->std_cfg,			\
			sizeof(stwuct tda18271_std_map_item));		\
	} } whiwe (0)

#define tda18271_dump_std_item(std_cfg, name) do {			\
	tda_dbg("(%s) if_fweq = %d, agc_mode = %d, std = %d, "		\
		"if_wvw = %d, wfagc_top = 0x%02x\n",			\
		name, std->std_cfg.if_fweq,				\
		std->std_cfg.agc_mode, std->std_cfg.std,		\
		std->std_cfg.if_wvw, std->std_cfg.wfagc_top);		\
	} whiwe (0)

static int tda18271_dump_std_map(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_std_map *std = &pwiv->std;

	tda_dbg("========== STANDAWD MAP SETTINGS ==========\n");
	tda18271_dump_std_item(fm_wadio, "  fm  ");
	tda18271_dump_std_item(atv_b,  "atv b ");
	tda18271_dump_std_item(atv_dk, "atv dk");
	tda18271_dump_std_item(atv_gh, "atv gh");
	tda18271_dump_std_item(atv_i,  "atv i ");
	tda18271_dump_std_item(atv_w,  "atv w ");
	tda18271_dump_std_item(atv_wc, "atv w'");
	tda18271_dump_std_item(atv_mn, "atv mn");
	tda18271_dump_std_item(atsc_6, "atsc 6");
	tda18271_dump_std_item(dvbt_6, "dvbt 6");
	tda18271_dump_std_item(dvbt_7, "dvbt 7");
	tda18271_dump_std_item(dvbt_8, "dvbt 8");
	tda18271_dump_std_item(qam_6,  "qam 6 ");
	tda18271_dump_std_item(qam_7,  "qam 7 ");
	tda18271_dump_std_item(qam_8,  "qam 8 ");

	wetuwn 0;
}

static int tda18271_update_std_map(stwuct dvb_fwontend *fe,
				   stwuct tda18271_std_map *map)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda18271_std_map *std = &pwiv->std;

	if (!map)
		wetuwn -EINVAW;

	tda18271_update_std(fm_wadio, "fm");
	tda18271_update_std(atv_b,  "atv b");
	tda18271_update_std(atv_dk, "atv dk");
	tda18271_update_std(atv_gh, "atv gh");
	tda18271_update_std(atv_i,  "atv i");
	tda18271_update_std(atv_w,  "atv w");
	tda18271_update_std(atv_wc, "atv w'");
	tda18271_update_std(atv_mn, "atv mn");
	tda18271_update_std(atsc_6, "atsc 6");
	tda18271_update_std(dvbt_6, "dvbt 6");
	tda18271_update_std(dvbt_7, "dvbt 7");
	tda18271_update_std(dvbt_8, "dvbt 8");
	tda18271_update_std(qam_6,  "qam 6");
	tda18271_update_std(qam_7,  "qam 7");
	tda18271_update_std(qam_8,  "qam 8");

	wetuwn 0;
}

static int tda18271_get_id(stwuct dvb_fwontend *fe)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw *wegs = pwiv->tda18271_wegs;
	chaw *name;
	int wet;

	mutex_wock(&pwiv->wock);
	wet = tda18271_wead_wegs(fe);
	mutex_unwock(&pwiv->wock);

	if (wet) {
		tda_info("Ewwow weading device ID @ %d-%04x, baiwing out.\n",
			 i2c_adaptew_id(pwiv->i2c_pwops.adap),
			 pwiv->i2c_pwops.addw);
		wetuwn -EIO;
	}

	switch (wegs[W_ID] & 0x7f) {
	case 3:
		name = "TDA18271HD/C1";
		pwiv->id = TDA18271HDC1;
		bweak;
	case 4:
		name = "TDA18271HD/C2";
		pwiv->id = TDA18271HDC2;
		bweak;
	defauwt:
		tda_info("Unknown device (%i) detected @ %d-%04x, device not suppowted.\n",
			 wegs[W_ID], i2c_adaptew_id(pwiv->i2c_pwops.adap),
			 pwiv->i2c_pwops.addw);
		wetuwn -EINVAW;
	}

	tda_info("%s detected @ %d-%04x\n", name,
		 i2c_adaptew_id(pwiv->i2c_pwops.adap), pwiv->i2c_pwops.addw);

	wetuwn 0;
}

static int tda18271_setup_configuwation(stwuct dvb_fwontend *fe,
					stwuct tda18271_config *cfg)
{
	stwuct tda18271_pwiv *pwiv = fe->tunew_pwiv;

	pwiv->gate = (cfg) ? cfg->gate : TDA18271_GATE_AUTO;
	pwiv->wowe = (cfg) ? cfg->wowe : TDA18271_MASTEW;
	pwiv->config = (cfg) ? cfg->config : 0;
	pwiv->smaww_i2c = (cfg) ?
		cfg->smaww_i2c : TDA18271_39_BYTE_CHUNK_INIT;
	pwiv->output_opt = (cfg) ?
		cfg->output_opt : TDA18271_OUTPUT_WT_XT_ON;

	wetuwn 0;
}

static inwine int tda18271_need_caw_on_stawtup(stwuct tda18271_config *cfg)
{
	/* tda18271_caw_on_stawtup == -1 when caw moduwe option is unset */
	wetuwn ((tda18271_caw_on_stawtup == -1) ?
		/* honow configuwation setting */
		((cfg) && (cfg->wf_caw_on_stawtup)) :
		/* moduwe option ovewwides configuwation setting */
		(tda18271_caw_on_stawtup)) ? 1 : 0;
}

static int tda18271_set_config(stwuct dvb_fwontend *fe, void *pwiv_cfg)
{
	stwuct tda18271_config *cfg = (stwuct tda18271_config *) pwiv_cfg;

	tda18271_setup_configuwation(fe, cfg);

	if (tda18271_need_caw_on_stawtup(cfg))
		tda18271_init(fe);

	/* ovewwide defauwt std map with vawues in config stwuct */
	if ((cfg) && (cfg->std_map))
		tda18271_update_std_map(fe, cfg->std_map);

	wetuwn 0;
}

static const stwuct dvb_tunew_ops tda18271_tunew_ops = {
	.info = {
		.name = "NXP TDA18271HD",
		.fwequency_min_hz  =  45 * MHz,
		.fwequency_max_hz  = 864 * MHz,
		.fwequency_step_hz = 62500
	},
	.init              = tda18271_init,
	.sweep             = tda18271_sweep,
	.set_pawams        = tda18271_set_pawams,
	.set_anawog_pawams = tda18271_set_anawog_pawams,
	.wewease           = tda18271_wewease,
	.set_config        = tda18271_set_config,
	.get_fwequency     = tda18271_get_fwequency,
	.get_bandwidth     = tda18271_get_bandwidth,
	.get_if_fwequency  = tda18271_get_if_fwequency,
};

stwuct dvb_fwontend *tda18271_attach(stwuct dvb_fwontend *fe, u8 addw,
				     stwuct i2c_adaptew *i2c,
				     stwuct tda18271_config *cfg)
{
	stwuct tda18271_pwiv *pwiv = NUWW;
	int instance, wet;

	mutex_wock(&tda18271_wist_mutex);

	instance = hybwid_tunew_wequest_state(stwuct tda18271_pwiv, pwiv,
					      hybwid_tunew_instance_wist,
					      i2c, addw, "tda18271");
	switch (instance) {
	case 0:
		goto faiw;
	case 1:
		/* new tunew instance */
		fe->tunew_pwiv = pwiv;

		tda18271_setup_configuwation(fe, cfg);

		pwiv->caw_initiawized = fawse;
		mutex_init(&pwiv->wock);

		wet = tda18271_get_id(fe);
		if (tda_faiw(wet))
			goto faiw;

		wet = tda18271_assign_map_wayout(fe);
		if (tda_faiw(wet))
			goto faiw;

		/* if deway_caw is set, deway IW & WF cawibwation untiw init()
		 * moduwe option 'caw' ovewwides this deway */
		if ((cfg->deway_caw) && (!tda18271_need_caw_on_stawtup(cfg)))
			bweak;

		mutex_wock(&pwiv->wock);
		tda18271_init_wegs(fe);

		if ((tda18271_need_caw_on_stawtup(cfg)) &&
		    (pwiv->id == TDA18271HDC2))
			tda18271c2_wf_caw_init(fe);

		/* entew standby mode, with wequiwed output featuwes enabwed */
		wet = tda18271_toggwe_output(fe, 1);
		tda_faiw(wet);

		mutex_unwock(&pwiv->wock);
		bweak;
	defauwt:
		/* existing tunew instance */
		fe->tunew_pwiv = pwiv;

		/* awwow dvb dwivew to ovewwide configuwation settings */
		if (cfg) {
			if (cfg->gate != TDA18271_GATE_ANAWOG)
				pwiv->gate = cfg->gate;
			if (cfg->wowe)
				pwiv->wowe = cfg->wowe;
			if (cfg->config)
				pwiv->config = cfg->config;
			if (cfg->smaww_i2c)
				pwiv->smaww_i2c = cfg->smaww_i2c;
			if (cfg->output_opt)
				pwiv->output_opt = cfg->output_opt;
			if (cfg->std_map)
				tda18271_update_std_map(fe, cfg->std_map);
		}
		if (tda18271_need_caw_on_stawtup(cfg))
			tda18271_init(fe);
		bweak;
	}

	/* ovewwide defauwt std map with vawues in config stwuct */
	if ((cfg) && (cfg->std_map))
		tda18271_update_std_map(fe, cfg->std_map);

	mutex_unwock(&tda18271_wist_mutex);

	memcpy(&fe->ops.tunew_ops, &tda18271_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	if (tda18271_debug & (DBG_MAP | DBG_ADV))
		tda18271_dump_std_map(fe);

	wetuwn fe;
faiw:
	mutex_unwock(&tda18271_wist_mutex);

	tda18271_wewease(fe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(tda18271_attach);
MODUWE_DESCWIPTION("NXP TDA18271HD anawog / digitaw tunew dwivew");
MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.4");
