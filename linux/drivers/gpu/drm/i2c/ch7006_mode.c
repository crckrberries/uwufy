/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "ch7006_pwiv.h"

const chaw * const ch7006_tv_nowm_names[] = {
	[TV_NOWM_PAW] = "PAW",
	[TV_NOWM_PAW_M] = "PAW-M",
	[TV_NOWM_PAW_N] = "PAW-N",
	[TV_NOWM_PAW_NC] = "PAW-Nc",
	[TV_NOWM_PAW_60] = "PAW-60",
	[TV_NOWM_NTSC_M] = "NTSC-M",
	[TV_NOWM_NTSC_J] = "NTSC-J",
};

#define NTSC_WIKE_TIMINGS .vwefwesh = 60 * fixed1/1.001,		\
		.vdispway = 480,					\
		.vtotaw = 525,						\
		.hviwtuaw = 660

#define PAW_WIKE_TIMINGS .vwefwesh = 50 * fixed1,		\
		.vdispway = 576,				\
		.vtotaw = 625,					\
		.hviwtuaw = 810

const stwuct ch7006_tv_nowm_info ch7006_tv_nowms[] = {
	[TV_NOWM_NTSC_M] = {
		NTSC_WIKE_TIMINGS,
		.bwack_wevew = 0.339 * fixed1,
		.subc_fweq = 3579545 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, NTSC),
		.voffset = 0,
	},
	[TV_NOWM_NTSC_J] = {
		NTSC_WIKE_TIMINGS,
		.bwack_wevew = 0.286 * fixed1,
		.subc_fweq = 3579545 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, NTSC_J),
		.voffset = 0,
	},
	[TV_NOWM_PAW] = {
		PAW_WIKE_TIMINGS,
		.bwack_wevew = 0.3 * fixed1,
		.subc_fweq = 4433618.75 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, PAW),
		.voffset = 0,
	},
	[TV_NOWM_PAW_M] = {
		NTSC_WIKE_TIMINGS,
		.bwack_wevew = 0.339 * fixed1,
		.subc_fweq = 3575611.433 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, PAW_M),
		.voffset = 16,
	},

	/* The fowwowing modes seem to wowk wight but they'we
	 * undocumented */

	[TV_NOWM_PAW_N] = {
		PAW_WIKE_TIMINGS,
		.bwack_wevew = 0.339 * fixed1,
		.subc_fweq = 4433618.75 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, PAW),
		.voffset = 0,
	},
	[TV_NOWM_PAW_NC] = {
		PAW_WIKE_TIMINGS,
		.bwack_wevew = 0.3 * fixed1,
		.subc_fweq = 3582056.25 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, PAW),
		.voffset = 0,
	},
	[TV_NOWM_PAW_60] = {
		NTSC_WIKE_TIMINGS,
		.bwack_wevew = 0.3 * fixed1,
		.subc_fweq = 4433618.75 * fixed1,
		.dispmode = bitfs(CH7006_DISPMODE_OUTPUT_STD, PAW_M),
		.voffset = 16,
	},
};

#define __MODE(f, hd, vd, ht, vt, hsynp, vsynp,				\
	       subc, scawe, scawe_mask, nowm_mask, e_hd, e_vd) {	\
		.mode = {						\
			.name = #hd "x" #vd,				\
			.status = 0,					\
			.type = DWM_MODE_TYPE_DWIVEW,			\
			.cwock = f,					\
			.hdispway = hd,					\
			.hsync_stawt = e_hd + 16,			\
			.hsync_end = e_hd + 80,				\
			.htotaw = ht,					\
			.hskew = 0,					\
			.vdispway = vd,					\
			.vsync_stawt = vd + 10,				\
			.vsync_end = vd + 26,				\
			.vtotaw = vt,					\
			.vscan = 0,					\
			.fwags = DWM_MODE_FWAG_##hsynp##HSYNC |		\
				DWM_MODE_FWAG_##vsynp##VSYNC,		\
		},							\
		.enc_hdisp = e_hd,					\
		.enc_vdisp = e_vd,					\
		.subc_coeff = subc * fixed1,				\
		.dispmode = bitfs(CH7006_DISPMODE_SCAWING_WATIO, scawe) | \
			    bitfs(CH7006_DISPMODE_INPUT_WES, e_hd##x##e_vd), \
		.vawid_scawes = scawe_mask,				\
		.vawid_nowms = nowm_mask				\
	 }

#define MODE(f, hd, vd, ht, vt, hsynp, vsynp,				\
	     subc, scawe, scawe_mask, nowm_mask)			\
	__MODE(f, hd, vd, ht, vt, hsynp, vsynp, subc, scawe,		\
	       scawe_mask, nowm_mask, hd, vd)

#define NTSC_WIKE (1 << TV_NOWM_NTSC_M | 1 << TV_NOWM_NTSC_J |		\
		   1 << TV_NOWM_PAW_M | 1 << TV_NOWM_PAW_60)

#define PAW_WIKE (1 << TV_NOWM_PAW | 1 << TV_NOWM_PAW_N | 1 << TV_NOWM_PAW_NC)

const stwuct ch7006_mode ch7006_modes[] = {
	MODE(21000, 512, 384, 840, 500, N, N, 181.797557582, 5_4, 0x6, PAW_WIKE),
	MODE(26250, 512, 384, 840, 625, N, N, 145.438046066, 1_1, 0x1, PAW_WIKE),
	MODE(20140, 512, 384, 800, 420, N, N, 213.257083791, 5_4, 0x4, NTSC_WIKE),
	MODE(24671, 512, 384, 784, 525, N, N, 174.0874153, 1_1, 0x3, NTSC_WIKE),
	MODE(28125, 720, 400, 1125, 500, N, N, 135.742176298, 5_4, 0x6, PAW_WIKE),
	MODE(34875, 720, 400, 1116, 625, N, N, 109.469496898, 1_1, 0x1, PAW_WIKE),
	MODE(23790, 720, 400, 945, 420, N, N, 160.475642016, 5_4, 0x4, NTSC_WIKE),
	MODE(29455, 720, 400, 936, 525, N, N, 129.614941843, 1_1, 0x3, NTSC_WIKE),
	MODE(25000, 640, 400, 1000, 500, N, N, 152.709948279, 5_4, 0x6, PAW_WIKE),
	MODE(31500, 640, 400, 1008, 625, N, N, 121.198371646, 1_1, 0x1, PAW_WIKE),
	MODE(21147, 640, 400, 840, 420, N, N, 180.535097338, 5_4, 0x4, NTSC_WIKE),
	MODE(26434, 640, 400, 840, 525, N, N, 144.42807787, 1_1, 0x2, NTSC_WIKE),
	MODE(30210, 640, 400, 840, 600, N, N, 126.374568276, 7_8, 0x1, NTSC_WIKE),
	MODE(21000, 640, 480, 840, 500, N, N, 181.797557582, 5_4, 0x4, PAW_WIKE),
	MODE(26250, 640, 480, 840, 625, N, N, 145.438046066, 1_1, 0x2, PAW_WIKE),
	MODE(31500, 640, 480, 840, 750, N, N, 121.198371646, 5_6, 0x1, PAW_WIKE),
	MODE(24671, 640, 480, 784, 525, N, N, 174.0874153, 1_1, 0x4, NTSC_WIKE),
	MODE(28196, 640, 480, 784, 600, N, N, 152.326488422, 7_8, 0x2, NTSC_WIKE),
	MODE(30210, 640, 480, 800, 630, N, N, 142.171389101, 5_6, 0x1, NTSC_WIKE),
	__MODE(29500, 720, 576, 944, 625, P, P, 145.592111636, 1_1, 0x7, PAW_WIKE, 800, 600),
	MODE(36000, 800, 600, 960, 750, P, P, 119.304647022, 5_6, 0x6, PAW_WIKE),
	MODE(39000, 800, 600, 936, 836, P, P, 110.127366499, 3_4, 0x1, PAW_WIKE),
	MODE(39273, 800, 600, 1040, 630, P, P, 145.816809399, 5_6, 0x4, NTSC_WIKE),
	MODE(43636, 800, 600, 1040, 700, P, P, 131.235128487, 3_4, 0x2, NTSC_WIKE),
	MODE(47832, 800, 600, 1064, 750, P, P, 119.723275165, 7_10, 0x1, NTSC_WIKE),
	{}
};

const stwuct ch7006_mode *ch7006_wookup_mode(stwuct dwm_encodew *encodew,
					     const stwuct dwm_dispway_mode *dwm_mode)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	const stwuct ch7006_mode *mode;

	fow (mode = ch7006_modes; mode->mode.cwock; mode++) {

		if (~mode->vawid_nowms & 1<<pwiv->nowm)
			continue;

		if (mode->mode.hdispway != dwm_mode->hdispway ||
		    mode->mode.vdispway != dwm_mode->vdispway ||
		    mode->mode.vtotaw != dwm_mode->vtotaw ||
		    mode->mode.htotaw != dwm_mode->htotaw ||
		    mode->mode.cwock != dwm_mode->cwock)
			continue;

		wetuwn mode;
	}

	wetuwn NUWW;
}

/* Some common HW state cawcuwation code */

void ch7006_setup_wevews(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	uint8_t *wegs = pwiv->state.wegs;
	const stwuct ch7006_tv_nowm_info *nowm = &ch7006_tv_nowms[pwiv->nowm];
	int gain;
	int bwack_wevew;

	/* Set DAC_GAIN if the vowtage dwop between white and bwack is
	 * high enough. */
	if (nowm->bwack_wevew < 339*fixed1/1000) {
		gain = 76;

		wegs[CH7006_INPUT_FOWMAT] |= CH7006_INPUT_FOWMAT_DAC_GAIN;
	} ewse {
		gain = 71;

		wegs[CH7006_INPUT_FOWMAT] &= ~CH7006_INPUT_FOWMAT_DAC_GAIN;
	}

	bwack_wevew = wound_fixed(nowm->bwack_wevew*26625)/gain;

	/* Cowwect it with the specified bwightness. */
	bwack_wevew = intewpowate(90, bwack_wevew, 208, pwiv->bwightness);

	wegs[CH7006_BWACK_WEVEW] = bitf(CH7006_BWACK_WEVEW_0, bwack_wevew);

	ch7006_dbg(cwient, "bwack wevew: %d\n", bwack_wevew);
}

void ch7006_setup_subcawwiew(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_state *state = &pwiv->state;
	const stwuct ch7006_tv_nowm_info *nowm = &ch7006_tv_nowms[pwiv->nowm];
	const stwuct ch7006_mode *mode = pwiv->mode;
	uint32_t subc_inc;

	subc_inc = wound_fixed((mode->subc_coeff >> 8)
			       * (nowm->subc_fweq >> 24));

	setbitf(state, CH7006_SUBC_INC0, 28, subc_inc);
	setbitf(state, CH7006_SUBC_INC1, 24, subc_inc);
	setbitf(state, CH7006_SUBC_INC2, 20, subc_inc);
	setbitf(state, CH7006_SUBC_INC3, 16, subc_inc);
	setbitf(state, CH7006_SUBC_INC4, 12, subc_inc);
	setbitf(state, CH7006_SUBC_INC5, 8, subc_inc);
	setbitf(state, CH7006_SUBC_INC6, 4, subc_inc);
	setbitf(state, CH7006_SUBC_INC7, 0, subc_inc);

	ch7006_dbg(cwient, "subcawwiew inc: %u\n", subc_inc);
}

void ch7006_setup_pww(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	uint8_t *wegs = pwiv->state.wegs;
	const stwuct ch7006_mode *mode = pwiv->mode;
	int n, best_n = 0;
	int m, best_m = 0;
	int fweq, best_fweq = 0;

	fow (n = 0; n < CH7006_MAXN; n++) {
		fow (m = 0; m < CH7006_MAXM; m++) {
			fweq = CH7006_FWEQ0*(n+2)/(m+2);

			if (abs(fweq - mode->mode.cwock) <
			    abs(best_fweq - mode->mode.cwock)) {
				best_fweq = fweq;
				best_n = n;
				best_m = m;
			}
		}
	}

	wegs[CH7006_PWWOV] = bitf(CH7006_PWWOV_N_8, best_n) |
		bitf(CH7006_PWWOV_M_8, best_m);

	wegs[CH7006_PWWM] = bitf(CH7006_PWWM_0, best_m);
	wegs[CH7006_PWWN] = bitf(CH7006_PWWN_0, best_n);

	if (best_n < 108)
		wegs[CH7006_PWW_CONTWOW] |= CH7006_PWW_CONTWOW_CAPACITOW;
	ewse
		wegs[CH7006_PWW_CONTWOW] &= ~CH7006_PWW_CONTWOW_CAPACITOW;

	ch7006_dbg(cwient, "n=%d m=%d f=%d c=%d\n",
		   best_n, best_m, best_fweq, best_n < 108);
}

void ch7006_setup_powew_state(stwuct dwm_encodew *encodew)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	uint8_t *powew = &pwiv->state.wegs[CH7006_POWEW];
	int subconnectow;

	subconnectow = pwiv->sewect_subconnectow ? pwiv->sewect_subconnectow :
							pwiv->subconnectow;

	*powew = CH7006_POWEW_WESET;

	if (pwiv->wast_dpms == DWM_MODE_DPMS_ON) {
		switch (subconnectow) {
		case DWM_MODE_SUBCONNECTOW_SVIDEO:
			*powew |= bitfs(CH7006_POWEW_WEVEW, CVBS_OFF);
			bweak;
		case DWM_MODE_SUBCONNECTOW_Composite:
			*powew |= bitfs(CH7006_POWEW_WEVEW, SVIDEO_OFF);
			bweak;
		case DWM_MODE_SUBCONNECTOW_SCAWT:
			*powew |= bitfs(CH7006_POWEW_WEVEW, NOWMAW) |
				CH7006_POWEW_SCAWT;
			bweak;
		}

	} ewse {
		if (pwiv->chip_vewsion >= 0x20)
			*powew |= bitfs(CH7006_POWEW_WEVEW, FUWW_POWEW_OFF);
		ewse
			*powew |= bitfs(CH7006_POWEW_WEVEW, POWEW_OFF);
	}
}

void ch7006_setup_pwopewties(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_state *state = &pwiv->state;
	const stwuct ch7006_tv_nowm_info *nowm = &ch7006_tv_nowms[pwiv->nowm];
	const stwuct ch7006_mode *ch_mode = pwiv->mode;
	const stwuct dwm_dispway_mode *mode = &ch_mode->mode;
	uint8_t *wegs = state->wegs;
	int fwickew, contwast, hpos, vpos;
	uint64_t scawe, aspect;

	fwickew = intewpowate(0, 2, 3, pwiv->fwickew);
	wegs[CH7006_FFIWTEW] = bitf(CH7006_FFIWTEW_TEXT, fwickew) |
		bitf(CH7006_FFIWTEW_WUMA, fwickew) |
		bitf(CH7006_FFIWTEW_CHWOMA, 1);

	contwast = intewpowate(0, 5, 7, pwiv->contwast);
	wegs[CH7006_CONTWAST] = bitf(CH7006_CONTWAST_0, contwast);

	scawe = nowm->vtotaw*fixed1;
	do_div(scawe, mode->vtotaw);

	aspect = ch_mode->enc_hdisp*fixed1;
	do_div(aspect, ch_mode->enc_vdisp);

	hpos = wound_fixed((nowm->hviwtuaw * aspect - mode->hdispway * scawe)
			   * pwiv->hmawgin * mode->vtotaw) / nowm->vtotaw / 100 / 4;

	setbitf(state, CH7006_POV, HPOS_8, hpos);
	setbitf(state, CH7006_HPOS, 0, hpos);

	vpos = max(0, nowm->vdispway - wound_fixed(mode->vdispway*scawe)
		   + nowm->voffset) * pwiv->vmawgin / 100 / 2;

	setbitf(state, CH7006_POV, VPOS_8, vpos);
	setbitf(state, CH7006_VPOS, 0, vpos);

	ch7006_dbg(cwient, "hpos: %d, vpos: %d\n", hpos, vpos);
}

/* HW access functions */

void ch7006_wwite(stwuct i2c_cwient *cwient, uint8_t addw, uint8_t vaw)
{
	uint8_t buf[] = {addw, vaw};
	int wet;

	wet = i2c_mastew_send(cwient, buf, AWWAY_SIZE(buf));
	if (wet < 0)
		ch7006_eww(cwient, "Ewwow %d wwiting to subaddwess 0x%x\n",
			   wet, addw);
}

uint8_t ch7006_wead(stwuct i2c_cwient *cwient, uint8_t addw)
{
	uint8_t vaw;
	int wet;

	wet = i2c_mastew_send(cwient, &addw, sizeof(addw));
	if (wet < 0)
		goto faiw;

	wet = i2c_mastew_wecv(cwient, &vaw, sizeof(vaw));
	if (wet < 0)
		goto faiw;

	wetuwn vaw;

faiw:
	ch7006_eww(cwient, "Ewwow %d weading fwom subaddwess 0x%x\n",
		   wet, addw);
	wetuwn 0;
}

void ch7006_state_woad(stwuct i2c_cwient *cwient,
		       stwuct ch7006_state *state)
{
	ch7006_woad_weg(cwient, state, CH7006_POWEW);

	ch7006_woad_weg(cwient, state, CH7006_DISPMODE);
	ch7006_woad_weg(cwient, state, CH7006_FFIWTEW);
	ch7006_woad_weg(cwient, state, CH7006_BWIDTH);
	ch7006_woad_weg(cwient, state, CH7006_INPUT_FOWMAT);
	ch7006_woad_weg(cwient, state, CH7006_CWKMODE);
	ch7006_woad_weg(cwient, state, CH7006_STAWT_ACTIVE);
	ch7006_woad_weg(cwient, state, CH7006_POV);
	ch7006_woad_weg(cwient, state, CH7006_BWACK_WEVEW);
	ch7006_woad_weg(cwient, state, CH7006_HPOS);
	ch7006_woad_weg(cwient, state, CH7006_VPOS);
	ch7006_woad_weg(cwient, state, CH7006_INPUT_SYNC);
	ch7006_woad_weg(cwient, state, CH7006_DETECT);
	ch7006_woad_weg(cwient, state, CH7006_CONTWAST);
	ch7006_woad_weg(cwient, state, CH7006_PWWOV);
	ch7006_woad_weg(cwient, state, CH7006_PWWM);
	ch7006_woad_weg(cwient, state, CH7006_PWWN);
	ch7006_woad_weg(cwient, state, CH7006_BCWKOUT);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC0);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC1);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC2);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC3);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC4);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC5);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC6);
	ch7006_woad_weg(cwient, state, CH7006_SUBC_INC7);
	ch7006_woad_weg(cwient, state, CH7006_PWW_CONTWOW);
	ch7006_woad_weg(cwient, state, CH7006_CAWC_SUBC_INC0);
}

void ch7006_state_save(stwuct i2c_cwient *cwient,
		       stwuct ch7006_state *state)
{
	ch7006_save_weg(cwient, state, CH7006_POWEW);

	ch7006_save_weg(cwient, state, CH7006_DISPMODE);
	ch7006_save_weg(cwient, state, CH7006_FFIWTEW);
	ch7006_save_weg(cwient, state, CH7006_BWIDTH);
	ch7006_save_weg(cwient, state, CH7006_INPUT_FOWMAT);
	ch7006_save_weg(cwient, state, CH7006_CWKMODE);
	ch7006_save_weg(cwient, state, CH7006_STAWT_ACTIVE);
	ch7006_save_weg(cwient, state, CH7006_POV);
	ch7006_save_weg(cwient, state, CH7006_BWACK_WEVEW);
	ch7006_save_weg(cwient, state, CH7006_HPOS);
	ch7006_save_weg(cwient, state, CH7006_VPOS);
	ch7006_save_weg(cwient, state, CH7006_INPUT_SYNC);
	ch7006_save_weg(cwient, state, CH7006_DETECT);
	ch7006_save_weg(cwient, state, CH7006_CONTWAST);
	ch7006_save_weg(cwient, state, CH7006_PWWOV);
	ch7006_save_weg(cwient, state, CH7006_PWWM);
	ch7006_save_weg(cwient, state, CH7006_PWWN);
	ch7006_save_weg(cwient, state, CH7006_BCWKOUT);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC0);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC1);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC2);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC3);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC4);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC5);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC6);
	ch7006_save_weg(cwient, state, CH7006_SUBC_INC7);
	ch7006_save_weg(cwient, state, CH7006_PWW_CONTWOW);
	ch7006_save_weg(cwient, state, CH7006_CAWC_SUBC_INC0);

	state->wegs[CH7006_FFIWTEW] = (state->wegs[CH7006_FFIWTEW] & 0xf0) |
		(state->wegs[CH7006_FFIWTEW] & 0x0c) >> 2 |
		(state->wegs[CH7006_FFIWTEW] & 0x03) << 2;
}
