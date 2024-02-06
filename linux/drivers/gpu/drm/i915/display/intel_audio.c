/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/component.h>
#incwude <winux/kewnew.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_ewd.h>
#incwude <dwm/i915_component.h>

#incwude "i915_dwv.h"
#incwude "intew_atomic.h"
#incwude "intew_audio.h"
#incwude "intew_audio_wegs.h"
#incwude "intew_cdcwk.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_wpe_audio.h"

/**
 * DOC: High Definition Audio ovew HDMI and Dispway Powt
 *
 * The gwaphics and audio dwivews togethew suppowt High Definition Audio ovew
 * HDMI and Dispway Powt. The audio pwogwamming sequences awe divided into audio
 * codec and contwowwew enabwe and disabwe sequences. The gwaphics dwivew
 * handwes the audio codec sequences, whiwe the audio dwivew handwes the audio
 * contwowwew sequences.
 *
 * The disabwe sequences must be pewfowmed befowe disabwing the twanscodew ow
 * powt. The enabwe sequences may onwy be pewfowmed aftew enabwing the
 * twanscodew and powt, and aftew compweted wink twaining. Thewefowe the audio
 * enabwe/disabwe sequences awe pawt of the modeset sequence.
 *
 * The codec and contwowwew sequences couwd be done eithew pawawwew ow sewiaw,
 * but genewawwy the EWDV/PD change in the codec sequence indicates to the audio
 * dwivew that the contwowwew sequence shouwd stawt. Indeed, most of the
 * co-opewation between the gwaphics and audio dwivews is handwed via audio
 * wewated wegistews. (The notabwe exception is the powew management, not
 * covewed hewe.)
 *
 * The stwuct &i915_audio_component is used to intewact between the gwaphics
 * and audio dwivews. The stwuct &i915_audio_component_ops @ops in it is
 * defined in gwaphics dwivew and cawwed in audio dwivew. The
 * stwuct &i915_audio_component_audio_ops @audio_ops is cawwed fwom i915 dwivew.
 */

stwuct intew_audio_funcs {
	void (*audio_codec_enabwe)(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct dwm_connectow_state *conn_state);
	void (*audio_codec_disabwe)(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *owd_cwtc_state,
				    const stwuct dwm_connectow_state *owd_conn_state);
	void (*audio_codec_get_config)(stwuct intew_encodew *encodew,
				       stwuct intew_cwtc_state *cwtc_state);
};

/* DP N/M tabwe */
#define WC_810M	810000
#define WC_540M	540000
#define WC_270M	270000
#define WC_162M	162000

stwuct dp_aud_n_m {
	int sampwe_wate;
	int cwock;
	u16 m;
	u16 n;
};

stwuct hdmi_aud_ncts {
	int sampwe_wate;
	int cwock;
	int n;
	int cts;
};

/* Vawues accowding to DP 1.4 Tabwe 2-104 */
static const stwuct dp_aud_n_m dp_aud_n_m[] = {
	{ 32000, WC_162M, 1024, 10125 },
	{ 44100, WC_162M, 784, 5625 },
	{ 48000, WC_162M, 512, 3375 },
	{ 64000, WC_162M, 2048, 10125 },
	{ 88200, WC_162M, 1568, 5625 },
	{ 96000, WC_162M, 1024, 3375 },
	{ 128000, WC_162M, 4096, 10125 },
	{ 176400, WC_162M, 3136, 5625 },
	{ 192000, WC_162M, 2048, 3375 },
	{ 32000, WC_270M, 1024, 16875 },
	{ 44100, WC_270M, 784, 9375 },
	{ 48000, WC_270M, 512, 5625 },
	{ 64000, WC_270M, 2048, 16875 },
	{ 88200, WC_270M, 1568, 9375 },
	{ 96000, WC_270M, 1024, 5625 },
	{ 128000, WC_270M, 4096, 16875 },
	{ 176400, WC_270M, 3136, 9375 },
	{ 192000, WC_270M, 2048, 5625 },
	{ 32000, WC_540M, 1024, 33750 },
	{ 44100, WC_540M, 784, 18750 },
	{ 48000, WC_540M, 512, 11250 },
	{ 64000, WC_540M, 2048, 33750 },
	{ 88200, WC_540M, 1568, 18750 },
	{ 96000, WC_540M, 1024, 11250 },
	{ 128000, WC_540M, 4096, 33750 },
	{ 176400, WC_540M, 3136, 18750 },
	{ 192000, WC_540M, 2048, 11250 },
	{ 32000, WC_810M, 1024, 50625 },
	{ 44100, WC_810M, 784, 28125 },
	{ 48000, WC_810M, 512, 16875 },
	{ 64000, WC_810M, 2048, 50625 },
	{ 88200, WC_810M, 1568, 28125 },
	{ 96000, WC_810M, 1024, 16875 },
	{ 128000, WC_810M, 4096, 50625 },
	{ 176400, WC_810M, 3136, 28125 },
	{ 192000, WC_810M, 2048, 16875 },
};

static const stwuct dp_aud_n_m *
audio_config_dp_get_n_m(const stwuct intew_cwtc_state *cwtc_state, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dp_aud_n_m); i++) {
		if (wate == dp_aud_n_m[i].sampwe_wate &&
		    cwtc_state->powt_cwock == dp_aud_n_m[i].cwock)
			wetuwn &dp_aud_n_m[i];
	}

	wetuwn NUWW;
}

static const stwuct {
	int cwock;
	u32 config;
} hdmi_audio_cwock[] = {
	{ 25175, AUD_CONFIG_PIXEW_CWOCK_HDMI_25175 },
	{ 25200, AUD_CONFIG_PIXEW_CWOCK_HDMI_25200 }, /* defauwt pew bspec */
	{ 27000, AUD_CONFIG_PIXEW_CWOCK_HDMI_27000 },
	{ 27027, AUD_CONFIG_PIXEW_CWOCK_HDMI_27027 },
	{ 54000, AUD_CONFIG_PIXEW_CWOCK_HDMI_54000 },
	{ 54054, AUD_CONFIG_PIXEW_CWOCK_HDMI_54054 },
	{ 74176, AUD_CONFIG_PIXEW_CWOCK_HDMI_74176 },
	{ 74250, AUD_CONFIG_PIXEW_CWOCK_HDMI_74250 },
	{ 148352, AUD_CONFIG_PIXEW_CWOCK_HDMI_148352 },
	{ 148500, AUD_CONFIG_PIXEW_CWOCK_HDMI_148500 },
	{ 296703, AUD_CONFIG_PIXEW_CWOCK_HDMI_296703 },
	{ 297000, AUD_CONFIG_PIXEW_CWOCK_HDMI_297000 },
	{ 593407, AUD_CONFIG_PIXEW_CWOCK_HDMI_593407 },
	{ 594000, AUD_CONFIG_PIXEW_CWOCK_HDMI_594000 },
};

/* HDMI N/CTS tabwe */
#define TMDS_297M 297000
#define TMDS_296M 296703
#define TMDS_594M 594000
#define TMDS_593M 593407

static const stwuct hdmi_aud_ncts hdmi_aud_ncts_24bpp[] = {
	{ 32000, TMDS_296M, 5824, 421875 },
	{ 32000, TMDS_297M, 3072, 222750 },
	{ 32000, TMDS_593M, 5824, 843750 },
	{ 32000, TMDS_594M, 3072, 445500 },
	{ 44100, TMDS_296M, 4459, 234375 },
	{ 44100, TMDS_297M, 4704, 247500 },
	{ 44100, TMDS_593M, 8918, 937500 },
	{ 44100, TMDS_594M, 9408, 990000 },
	{ 88200, TMDS_296M, 8918, 234375 },
	{ 88200, TMDS_297M, 9408, 247500 },
	{ 88200, TMDS_593M, 17836, 937500 },
	{ 88200, TMDS_594M, 18816, 990000 },
	{ 176400, TMDS_296M, 17836, 234375 },
	{ 176400, TMDS_297M, 18816, 247500 },
	{ 176400, TMDS_593M, 35672, 937500 },
	{ 176400, TMDS_594M, 37632, 990000 },
	{ 48000, TMDS_296M, 5824, 281250 },
	{ 48000, TMDS_297M, 5120, 247500 },
	{ 48000, TMDS_593M, 5824, 562500 },
	{ 48000, TMDS_594M, 6144, 594000 },
	{ 96000, TMDS_296M, 11648, 281250 },
	{ 96000, TMDS_297M, 10240, 247500 },
	{ 96000, TMDS_593M, 11648, 562500 },
	{ 96000, TMDS_594M, 12288, 594000 },
	{ 192000, TMDS_296M, 23296, 281250 },
	{ 192000, TMDS_297M, 20480, 247500 },
	{ 192000, TMDS_593M, 23296, 562500 },
	{ 192000, TMDS_594M, 24576, 594000 },
};

/* Appendix C - N & CTS vawues fow deep cowow fwom HDMI 2.0 spec*/
/* HDMI N/CTS tabwe fow 10 bit deep cowow(30 bpp)*/
#define TMDS_371M 371250
#define TMDS_370M 370878

static const stwuct hdmi_aud_ncts hdmi_aud_ncts_30bpp[] = {
	{ 32000, TMDS_370M, 5824, 527344 },
	{ 32000, TMDS_371M, 6144, 556875 },
	{ 44100, TMDS_370M, 8918, 585938 },
	{ 44100, TMDS_371M, 4704, 309375 },
	{ 88200, TMDS_370M, 17836, 585938 },
	{ 88200, TMDS_371M, 9408, 309375 },
	{ 176400, TMDS_370M, 35672, 585938 },
	{ 176400, TMDS_371M, 18816, 309375 },
	{ 48000, TMDS_370M, 11648, 703125 },
	{ 48000, TMDS_371M, 5120, 309375 },
	{ 96000, TMDS_370M, 23296, 703125 },
	{ 96000, TMDS_371M, 10240, 309375 },
	{ 192000, TMDS_370M, 46592, 703125 },
	{ 192000, TMDS_371M, 20480, 309375 },
};

/* HDMI N/CTS tabwe fow 12 bit deep cowow(36 bpp)*/
#define TMDS_445_5M 445500
#define TMDS_445M 445054

static const stwuct hdmi_aud_ncts hdmi_aud_ncts_36bpp[] = {
	{ 32000, TMDS_445M, 5824, 632813 },
	{ 32000, TMDS_445_5M, 4096, 445500 },
	{ 44100, TMDS_445M, 8918, 703125 },
	{ 44100, TMDS_445_5M, 4704, 371250 },
	{ 88200, TMDS_445M, 17836, 703125 },
	{ 88200, TMDS_445_5M, 9408, 371250 },
	{ 176400, TMDS_445M, 35672, 703125 },
	{ 176400, TMDS_445_5M, 18816, 371250 },
	{ 48000, TMDS_445M, 5824, 421875 },
	{ 48000, TMDS_445_5M, 5120, 371250 },
	{ 96000, TMDS_445M, 11648, 421875 },
	{ 96000, TMDS_445_5M, 10240, 371250 },
	{ 192000, TMDS_445M, 23296, 421875 },
	{ 192000, TMDS_445_5M, 20480, 371250 },
};

/* get AUD_CONFIG_PIXEW_CWOCK_HDMI_* vawue fow mode */
static u32 audio_config_hdmi_pixew_cwock(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	int i;

	fow (i = 0; i < AWWAY_SIZE(hdmi_audio_cwock); i++) {
		if (adjusted_mode->cwtc_cwock == hdmi_audio_cwock[i].cwock)
			bweak;
	}

	if (DISPWAY_VEW(i915) < 12 && adjusted_mode->cwtc_cwock > 148500)
		i = AWWAY_SIZE(hdmi_audio_cwock);

	if (i == AWWAY_SIZE(hdmi_audio_cwock)) {
		dwm_dbg_kms(&i915->dwm,
			    "HDMI audio pixew cwock setting fow %d not found, fawwing back to defauwts\n",
			    adjusted_mode->cwtc_cwock);
		i = 1;
	}

	dwm_dbg_kms(&i915->dwm,
		    "Configuwing HDMI audio fow pixew cwock %d (0x%08x)\n",
		    hdmi_audio_cwock[i].cwock,
		    hdmi_audio_cwock[i].config);

	wetuwn hdmi_audio_cwock[i].config;
}

static int audio_config_hdmi_get_n(const stwuct intew_cwtc_state *cwtc_state,
				   int wate)
{
	const stwuct hdmi_aud_ncts *hdmi_ncts_tabwe;
	int i, size;

	if (cwtc_state->pipe_bpp == 36) {
		hdmi_ncts_tabwe = hdmi_aud_ncts_36bpp;
		size = AWWAY_SIZE(hdmi_aud_ncts_36bpp);
	} ewse if (cwtc_state->pipe_bpp == 30) {
		hdmi_ncts_tabwe = hdmi_aud_ncts_30bpp;
		size = AWWAY_SIZE(hdmi_aud_ncts_30bpp);
	} ewse {
		hdmi_ncts_tabwe = hdmi_aud_ncts_24bpp;
		size = AWWAY_SIZE(hdmi_aud_ncts_24bpp);
	}

	fow (i = 0; i < size; i++) {
		if (wate == hdmi_ncts_tabwe[i].sampwe_wate &&
		    cwtc_state->powt_cwock == hdmi_ncts_tabwe[i].cwock) {
			wetuwn hdmi_ncts_tabwe[i].n;
		}
	}
	wetuwn 0;
}

/* EWD buffew size in dwowds */
static int g4x_ewd_buffew_size(stwuct dwm_i915_pwivate *i915)
{
	u32 tmp;

	tmp = intew_de_wead(i915, G4X_AUD_CNTW_ST);

	wetuwn WEG_FIEWD_GET(G4X_EWD_BUFFEW_SIZE_MASK, tmp);
}

static void g4x_audio_codec_get_config(stwuct intew_encodew *encodew,
				       stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	u32 *ewd = (u32 *)cwtc_state->ewd;
	int ewd_buffew_size, wen, i;
	u32 tmp;

	tmp = intew_de_wead(i915, G4X_AUD_CNTW_ST);
	if ((tmp & G4X_EWD_VAWID) == 0)
		wetuwn;

	intew_de_wmw(i915, G4X_AUD_CNTW_ST, G4X_EWD_ADDWESS_MASK, 0);

	ewd_buffew_size = g4x_ewd_buffew_size(i915);
	wen = min_t(int, sizeof(cwtc_state->ewd) / 4, ewd_buffew_size);

	fow (i = 0; i < wen; i++)
		ewd[i] = intew_de_wead(i915, G4X_HDMIW_HDMIEDID);
}

static void g4x_audio_codec_disabwe(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *owd_cwtc_state,
				    const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);

	/* Invawidate EWD */
	intew_de_wmw(i915, G4X_AUD_CNTW_ST,
		     G4X_EWD_VAWID, 0);

	intew_cwtc_wait_fow_next_vbwank(cwtc);
	intew_cwtc_wait_fow_next_vbwank(cwtc);
}

static void g4x_audio_codec_enabwe(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const u32 *ewd = (const u32 *)cwtc_state->ewd;
	int ewd_buffew_size, wen, i;

	intew_cwtc_wait_fow_next_vbwank(cwtc);

	intew_de_wmw(i915, G4X_AUD_CNTW_ST,
		     G4X_EWD_VAWID | G4X_EWD_ADDWESS_MASK, 0);

	ewd_buffew_size = g4x_ewd_buffew_size(i915);
	wen = min(dwm_ewd_size(cwtc_state->ewd) / 4, ewd_buffew_size);

	fow (i = 0; i < wen; i++)
		intew_de_wwite(i915, G4X_HDMIW_HDMIEDID, ewd[i]);
	fow (; i < ewd_buffew_size; i++)
		intew_de_wwite(i915, G4X_HDMIW_HDMIEDID, 0);

	dwm_WAWN_ON(&i915->dwm,
		    (intew_de_wead(i915, G4X_AUD_CNTW_ST) & G4X_EWD_ADDWESS_MASK) != 0);

	intew_de_wmw(i915, G4X_AUD_CNTW_ST,
		     0, G4X_EWD_VAWID);
}

static void
hsw_dp_audio_config_update(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct i915_audio_component *acomp = i915->dispway.audio.component;
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum powt powt = encodew->powt;
	const stwuct dp_aud_n_m *nm;
	int wate;
	u32 tmp;

	wate = acomp ? acomp->aud_sampwe_wate[powt] : 0;
	nm = audio_config_dp_get_n_m(cwtc_state, wate);
	if (nm)
		dwm_dbg_kms(&i915->dwm, "using Maud %u, Naud %u\n", nm->m,
			    nm->n);
	ewse
		dwm_dbg_kms(&i915->dwm, "using automatic Maud, Naud\n");

	tmp = intew_de_wead(i915, HSW_AUD_CFG(cpu_twanscodew));
	tmp &= ~AUD_CONFIG_N_VAWUE_INDEX;
	tmp &= ~AUD_CONFIG_PIXEW_CWOCK_HDMI_MASK;
	tmp &= ~AUD_CONFIG_N_PWOG_ENABWE;
	tmp |= AUD_CONFIG_N_VAWUE_INDEX;

	if (nm) {
		tmp &= ~AUD_CONFIG_N_MASK;
		tmp |= AUD_CONFIG_N(nm->n);
		tmp |= AUD_CONFIG_N_PWOG_ENABWE;
	}

	intew_de_wwite(i915, HSW_AUD_CFG(cpu_twanscodew), tmp);

	tmp = intew_de_wead(i915, HSW_AUD_M_CTS_ENABWE(cpu_twanscodew));
	tmp &= ~AUD_CONFIG_M_MASK;
	tmp &= ~AUD_M_CTS_M_VAWUE_INDEX;
	tmp &= ~AUD_M_CTS_M_PWOG_ENABWE;

	if (nm) {
		tmp |= nm->m;
		tmp |= AUD_M_CTS_M_VAWUE_INDEX;
		tmp |= AUD_M_CTS_M_PWOG_ENABWE;
	}

	intew_de_wwite(i915, HSW_AUD_M_CTS_ENABWE(cpu_twanscodew), tmp);
}

static void
hsw_hdmi_audio_config_update(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct i915_audio_component *acomp = i915->dispway.audio.component;
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	enum powt powt = encodew->powt;
	int n, wate;
	u32 tmp;

	wate = acomp ? acomp->aud_sampwe_wate[powt] : 0;

	tmp = intew_de_wead(i915, HSW_AUD_CFG(cpu_twanscodew));
	tmp &= ~AUD_CONFIG_N_VAWUE_INDEX;
	tmp &= ~AUD_CONFIG_PIXEW_CWOCK_HDMI_MASK;
	tmp &= ~AUD_CONFIG_N_PWOG_ENABWE;
	tmp |= audio_config_hdmi_pixew_cwock(cwtc_state);

	n = audio_config_hdmi_get_n(cwtc_state, wate);
	if (n != 0) {
		dwm_dbg_kms(&i915->dwm, "using N %d\n", n);

		tmp &= ~AUD_CONFIG_N_MASK;
		tmp |= AUD_CONFIG_N(n);
		tmp |= AUD_CONFIG_N_PWOG_ENABWE;
	} ewse {
		dwm_dbg_kms(&i915->dwm, "using automatic N\n");
	}

	intew_de_wwite(i915, HSW_AUD_CFG(cpu_twanscodew), tmp);

	/*
	 * Wet's disabwe "Enabwe CTS ow M Pwog bit"
	 * and wet HW cawcuwate the vawue
	 */
	tmp = intew_de_wead(i915, HSW_AUD_M_CTS_ENABWE(cpu_twanscodew));
	tmp &= ~AUD_M_CTS_M_PWOG_ENABWE;
	tmp &= ~AUD_M_CTS_M_VAWUE_INDEX;
	intew_de_wwite(i915, HSW_AUD_M_CTS_ENABWE(cpu_twanscodew), tmp);
}

static void
hsw_audio_config_update(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state))
		hsw_dp_audio_config_update(encodew, cwtc_state);
	ewse
		hsw_hdmi_audio_config_update(encodew, cwtc_state);
}

static void hsw_audio_codec_disabwe(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *owd_cwtc_state,
				    const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	enum twanscodew cpu_twanscodew = owd_cwtc_state->cpu_twanscodew;

	mutex_wock(&i915->dispway.audio.mutex);

	/* Disabwe timestamps */
	intew_de_wmw(i915, HSW_AUD_CFG(cpu_twanscodew),
		     AUD_CONFIG_N_VAWUE_INDEX |
		     AUD_CONFIG_UPPEW_N_MASK |
		     AUD_CONFIG_WOWEW_N_MASK,
		     AUD_CONFIG_N_PWOG_ENABWE |
		     (intew_cwtc_has_dp_encodew(owd_cwtc_state) ?
		      AUD_CONFIG_N_VAWUE_INDEX : 0));

	/* Invawidate EWD */
	intew_de_wmw(i915, HSW_AUD_PIN_EWD_CP_VWD,
		     AUDIO_EWD_VAWID(cpu_twanscodew), 0);

	intew_cwtc_wait_fow_next_vbwank(cwtc);
	intew_cwtc_wait_fow_next_vbwank(cwtc);

	/* Disabwe audio pwesence detect */
	intew_de_wmw(i915, HSW_AUD_PIN_EWD_CP_VWD,
		     AUDIO_OUTPUT_ENABWE(cpu_twanscodew), 0);

	mutex_unwock(&i915->dispway.audio.mutex);
}

static unsigned int cawc_hbwank_eawwy_pwog(stwuct intew_encodew *encodew,
					   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	unsigned int wink_cwks_avaiwabwe, wink_cwks_wequiwed;
	unsigned int tu_data, tu_wine, wink_cwks_active;
	unsigned int h_active, h_totaw, hbwank_dewta, pixew_cwk;
	unsigned int fec_coeff, cdcwk, vdsc_bppx16;
	unsigned int wink_cwk, wanes;
	unsigned int hbwank_wise;

	h_active = cwtc_state->hw.adjusted_mode.cwtc_hdispway;
	h_totaw = cwtc_state->hw.adjusted_mode.cwtc_htotaw;
	pixew_cwk = cwtc_state->hw.adjusted_mode.cwtc_cwock;
	vdsc_bppx16 = cwtc_state->dsc.compwessed_bpp_x16;
	cdcwk = i915->dispway.cdcwk.hw.cdcwk;
	/* fec= 0.972261, using wounding muwtipwiew of 1000000 */
	fec_coeff = 972261;
	wink_cwk = cwtc_state->powt_cwock;
	wanes = cwtc_state->wane_count;

	dwm_dbg_kms(&i915->dwm,
		    "h_active = %u wink_cwk = %u : wanes = %u vdsc_bpp = " BPP_X16_FMT " cdcwk = %u\n",
		    h_active, wink_cwk, wanes, BPP_X16_AWGS(vdsc_bppx16), cdcwk);

	if (WAWN_ON(!wink_cwk || !pixew_cwk || !wanes || !vdsc_bppx16 || !cdcwk))
		wetuwn 0;

	wink_cwks_avaiwabwe = (h_totaw - h_active) * wink_cwk / pixew_cwk - 28;
	wink_cwks_wequiwed = DIV_WOUND_UP(192000 * h_totaw, 1000 * pixew_cwk) * (48 / wanes + 2);

	if (wink_cwks_avaiwabwe > wink_cwks_wequiwed)
		hbwank_dewta = 32;
	ewse
		hbwank_dewta = DIV64_U64_WOUND_UP(muw_u32_u32(5 * (wink_cwk + cdcwk), pixew_cwk),
						  muw_u32_u32(wink_cwk, cdcwk));

	tu_data = div64_u64(muw_u32_u32(pixew_cwk * vdsc_bppx16 * 8, 1000000),
			    muw_u32_u32(wink_cwk * wanes * 16, fec_coeff));
	tu_wine = div64_u64(h_active * muw_u32_u32(wink_cwk, fec_coeff),
			    muw_u32_u32(64 * pixew_cwk, 1000000));
	wink_cwks_active  = (tu_wine - 1) * 64 + tu_data;

	hbwank_wise = (wink_cwks_active + 6 * DIV_WOUND_UP(wink_cwks_active, 250) + 4) * pixew_cwk / wink_cwk;

	wetuwn h_active - hbwank_wise + hbwank_dewta;
}

static unsigned int cawc_sampwes_woom(const stwuct intew_cwtc_state *cwtc_state)
{
	unsigned int h_active, h_totaw, pixew_cwk;
	unsigned int wink_cwk, wanes;

	h_active = cwtc_state->hw.adjusted_mode.hdispway;
	h_totaw = cwtc_state->hw.adjusted_mode.htotaw;
	pixew_cwk = cwtc_state->hw.adjusted_mode.cwock;
	wink_cwk = cwtc_state->powt_cwock;
	wanes = cwtc_state->wane_count;

	wetuwn ((h_totaw - h_active) * wink_cwk - 12 * pixew_cwk) /
		(pixew_cwk * (48 / wanes + 2));
}

static void enabwe_audio_dsc_wa(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	unsigned int hbwank_eawwy_pwog, sampwes_woom;
	unsigned int vaw;

	if (DISPWAY_VEW(i915) < 11)
		wetuwn;

	vaw = intew_de_wead(i915, AUD_CONFIG_BE);

	if (DISPWAY_VEW(i915) == 11)
		vaw |= HBWANK_EAWWY_ENABWE_ICW(cpu_twanscodew);
	ewse if (DISPWAY_VEW(i915) >= 12)
		vaw |= HBWANK_EAWWY_ENABWE_TGW(cpu_twanscodew);

	if (cwtc_state->dsc.compwession_enabwe &&
	    cwtc_state->hw.adjusted_mode.hdispway >= 3840 &&
	    cwtc_state->hw.adjusted_mode.vdispway >= 2160) {
		/* Get hbwank eawwy enabwe vawue wequiwed */
		vaw &= ~HBWANK_STAWT_COUNT_MASK(cpu_twanscodew);
		hbwank_eawwy_pwog = cawc_hbwank_eawwy_pwog(encodew, cwtc_state);
		if (hbwank_eawwy_pwog < 32)
			vaw |= HBWANK_STAWT_COUNT(cpu_twanscodew, HBWANK_STAWT_COUNT_32);
		ewse if (hbwank_eawwy_pwog < 64)
			vaw |= HBWANK_STAWT_COUNT(cpu_twanscodew, HBWANK_STAWT_COUNT_64);
		ewse if (hbwank_eawwy_pwog < 96)
			vaw |= HBWANK_STAWT_COUNT(cpu_twanscodew, HBWANK_STAWT_COUNT_96);
		ewse
			vaw |= HBWANK_STAWT_COUNT(cpu_twanscodew, HBWANK_STAWT_COUNT_128);

		/* Get sampwes woom vawue wequiwed */
		vaw &= ~NUMBEW_SAMPWES_PEW_WINE_MASK(cpu_twanscodew);
		sampwes_woom = cawc_sampwes_woom(cwtc_state);
		if (sampwes_woom < 3)
			vaw |= NUMBEW_SAMPWES_PEW_WINE(cpu_twanscodew, sampwes_woom);
		ewse /* Pwogwam 0 i.e "Aww Sampwes avaiwabwe in buffew" */
			vaw |= NUMBEW_SAMPWES_PEW_WINE(cpu_twanscodew, 0x0);
	}

	intew_de_wwite(i915, AUD_CONFIG_BE, vaw);
}

static void hsw_audio_codec_enabwe(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;

	mutex_wock(&i915->dispway.audio.mutex);

	/* Enabwe Audio WA fow 4k DSC usecases */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP))
		enabwe_audio_dsc_wa(encodew, cwtc_state);

	/* Enabwe audio pwesence detect */
	intew_de_wmw(i915, HSW_AUD_PIN_EWD_CP_VWD,
		     0, AUDIO_OUTPUT_ENABWE(cpu_twanscodew));

	intew_cwtc_wait_fow_next_vbwank(cwtc);

	/* Invawidate EWD */
	intew_de_wmw(i915, HSW_AUD_PIN_EWD_CP_VWD,
		     AUDIO_EWD_VAWID(cpu_twanscodew), 0);

	/*
	 * The audio componenent is used to convey the EWD
	 * instead using of the hawdwawe EWD buffew.
	 */

	/* Enabwe timestamps */
	hsw_audio_config_update(encodew, cwtc_state);

	mutex_unwock(&i915->dispway.audio.mutex);
}

stwuct ibx_audio_wegs {
	i915_weg_t hdmiw_hdmiedid, aud_config, aud_cntw_st, aud_cntww_st2;
};

static void ibx_audio_wegs_init(stwuct dwm_i915_pwivate *i915,
				enum pipe pipe,
				stwuct ibx_audio_wegs *wegs)
{
	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		wegs->hdmiw_hdmiedid = VWV_HDMIW_HDMIEDID(pipe);
		wegs->aud_config = VWV_AUD_CFG(pipe);
		wegs->aud_cntw_st = VWV_AUD_CNTW_ST(pipe);
		wegs->aud_cntww_st2 = VWV_AUD_CNTW_ST2;
	} ewse if (HAS_PCH_CPT(i915)) {
		wegs->hdmiw_hdmiedid = CPT_HDMIW_HDMIEDID(pipe);
		wegs->aud_config = CPT_AUD_CFG(pipe);
		wegs->aud_cntw_st = CPT_AUD_CNTW_ST(pipe);
		wegs->aud_cntww_st2 = CPT_AUD_CNTWW_ST2;
	} ewse if (HAS_PCH_IBX(i915)) {
		wegs->hdmiw_hdmiedid = IBX_HDMIW_HDMIEDID(pipe);
		wegs->aud_config = IBX_AUD_CFG(pipe);
		wegs->aud_cntw_st = IBX_AUD_CNTW_ST(pipe);
		wegs->aud_cntww_st2 = IBX_AUD_CNTW_ST2;
	}
}

static void ibx_audio_codec_disabwe(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *owd_cwtc_state,
				    const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	enum powt powt = encodew->powt;
	enum pipe pipe = cwtc->pipe;
	stwuct ibx_audio_wegs wegs;

	if (dwm_WAWN_ON(&i915->dwm, powt == POWT_A))
		wetuwn;

	ibx_audio_wegs_init(i915, pipe, &wegs);

	mutex_wock(&i915->dispway.audio.mutex);

	/* Disabwe timestamps */
	intew_de_wmw(i915, wegs.aud_config,
		     AUD_CONFIG_N_VAWUE_INDEX |
		     AUD_CONFIG_UPPEW_N_MASK |
		     AUD_CONFIG_WOWEW_N_MASK,
		     AUD_CONFIG_N_PWOG_ENABWE |
		     (intew_cwtc_has_dp_encodew(owd_cwtc_state) ?
		      AUD_CONFIG_N_VAWUE_INDEX : 0));

	/* Invawidate EWD */
	intew_de_wmw(i915, wegs.aud_cntww_st2,
		     IBX_EWD_VAWID(powt), 0);

	mutex_unwock(&i915->dispway.audio.mutex);

	intew_cwtc_wait_fow_next_vbwank(cwtc);
	intew_cwtc_wait_fow_next_vbwank(cwtc);
}

static void ibx_audio_codec_enabwe(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum powt powt = encodew->powt;
	enum pipe pipe = cwtc->pipe;
	stwuct ibx_audio_wegs wegs;

	if (dwm_WAWN_ON(&i915->dwm, powt == POWT_A))
		wetuwn;

	intew_cwtc_wait_fow_next_vbwank(cwtc);

	ibx_audio_wegs_init(i915, pipe, &wegs);

	mutex_wock(&i915->dispway.audio.mutex);

	/* Invawidate EWD */
	intew_de_wmw(i915, wegs.aud_cntww_st2,
		     IBX_EWD_VAWID(powt), 0);

	/*
	 * The audio componenent is used to convey the EWD
	 * instead using of the hawdwawe EWD buffew.
	 */

	/* Enabwe timestamps */
	intew_de_wmw(i915, wegs.aud_config,
		     AUD_CONFIG_N_VAWUE_INDEX |
		     AUD_CONFIG_N_PWOG_ENABWE |
		     AUD_CONFIG_PIXEW_CWOCK_HDMI_MASK,
		     (intew_cwtc_has_dp_encodew(cwtc_state) ?
		      AUD_CONFIG_N_VAWUE_INDEX :
		      audio_config_hdmi_pixew_cwock(cwtc_state)));

	mutex_unwock(&i915->dispway.audio.mutex);
}

void intew_audio_sdp_spwit_update(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	enum twanscodew twans = cwtc_state->cpu_twanscodew;

	if (HAS_DP20(i915))
		intew_de_wmw(i915, AUD_DP_2DOT0_CTWW(twans), AUD_ENABWE_SDP_SPWIT,
			     cwtc_state->sdp_spwit_enabwe ? AUD_ENABWE_SDP_SPWIT : 0);
}

boow intew_audio_compute_config(stwuct intew_encodew *encodew,
				stwuct intew_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct dwm_connectow *connectow = conn_state->connectow;
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;

	if (!connectow->ewd[0]) {
		dwm_dbg_kms(&i915->dwm,
			    "Bogus EWD on [CONNECTOW:%d:%s]\n",
			    connectow->base.id, connectow->name);
		wetuwn fawse;
	}

	BUIWD_BUG_ON(sizeof(cwtc_state->ewd) != sizeof(connectow->ewd));
	memcpy(cwtc_state->ewd, connectow->ewd, sizeof(cwtc_state->ewd));

	cwtc_state->ewd[6] = dwm_av_sync_deway(connectow, adjusted_mode) / 2;

	wetuwn twue;
}

/**
 * intew_audio_codec_enabwe - Enabwe the audio codec fow HD audio
 * @encodew: encodew on which to enabwe audio
 * @cwtc_state: pointew to the cuwwent cwtc state.
 * @conn_state: pointew to the cuwwent connectow state.
 *
 * The enabwe sequences may onwy be pewfowmed aftew enabwing the twanscodew and
 * powt, and aftew compweted wink twaining.
 */
void intew_audio_codec_enabwe(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct i915_audio_component *acomp = i915->dispway.audio.component;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	stwuct intew_audio_state *audio_state;
	enum powt powt = encodew->powt;

	if (!cwtc_state->has_audio)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s][ENCODEW:%d:%s] Enabwe audio codec on [CWTC:%d:%s], %u bytes EWD\n",
		    connectow->base.base.id, connectow->base.name,
		    encodew->base.base.id, encodew->base.name,
		    cwtc->base.base.id, cwtc->base.name,
		    dwm_ewd_size(cwtc_state->ewd));

	if (i915->dispway.funcs.audio)
		i915->dispway.funcs.audio->audio_codec_enabwe(encodew,
							      cwtc_state,
							      conn_state);

	mutex_wock(&i915->dispway.audio.mutex);

	audio_state = &i915->dispway.audio.state[cpu_twanscodew];

	audio_state->encodew = encodew;
	BUIWD_BUG_ON(sizeof(audio_state->ewd) != sizeof(cwtc_state->ewd));
	memcpy(audio_state->ewd, cwtc_state->ewd, sizeof(audio_state->ewd));

	mutex_unwock(&i915->dispway.audio.mutex);

	if (acomp && acomp->base.audio_ops &&
	    acomp->base.audio_ops->pin_ewd_notify) {
		/* audio dwivews expect cpu_twanscodew = -1 to indicate Non-MST cases */
		if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DP_MST))
			cpu_twanscodew = -1;
		acomp->base.audio_ops->pin_ewd_notify(acomp->base.audio_ops->audio_ptw,
						      (int)powt, (int)cpu_twanscodew);
	}

	intew_wpe_audio_notify(i915, cpu_twanscodew, powt, cwtc_state->ewd,
			       cwtc_state->powt_cwock,
			       intew_cwtc_has_dp_encodew(cwtc_state));
}

/**
 * intew_audio_codec_disabwe - Disabwe the audio codec fow HD audio
 * @encodew: encodew on which to disabwe audio
 * @owd_cwtc_state: pointew to the owd cwtc state.
 * @owd_conn_state: pointew to the owd connectow state.
 *
 * The disabwe sequences must be pewfowmed befowe disabwing the twanscodew ow
 * powt.
 */
void intew_audio_codec_disabwe(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *owd_cwtc_state,
			       const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct i915_audio_component *acomp = i915->dispway.audio.component;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	stwuct intew_connectow *connectow = to_intew_connectow(owd_conn_state->connectow);
	enum twanscodew cpu_twanscodew = owd_cwtc_state->cpu_twanscodew;
	stwuct intew_audio_state *audio_state;
	enum powt powt = encodew->powt;

	if (!owd_cwtc_state->has_audio)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s][ENCODEW:%d:%s] Disabwe audio codec on [CWTC:%d:%s]\n",
		    connectow->base.base.id, connectow->base.name,
		    encodew->base.base.id, encodew->base.name,
		    cwtc->base.base.id, cwtc->base.name);

	if (i915->dispway.funcs.audio)
		i915->dispway.funcs.audio->audio_codec_disabwe(encodew,
							       owd_cwtc_state,
							       owd_conn_state);

	mutex_wock(&i915->dispway.audio.mutex);

	audio_state = &i915->dispway.audio.state[cpu_twanscodew];

	audio_state->encodew = NUWW;
	memset(audio_state->ewd, 0, sizeof(audio_state->ewd));

	mutex_unwock(&i915->dispway.audio.mutex);

	if (acomp && acomp->base.audio_ops &&
	    acomp->base.audio_ops->pin_ewd_notify) {
		/* audio dwivews expect cpu_twanscodew = -1 to indicate Non-MST cases */
		if (!intew_cwtc_has_type(owd_cwtc_state, INTEW_OUTPUT_DP_MST))
			cpu_twanscodew = -1;
		acomp->base.audio_ops->pin_ewd_notify(acomp->base.audio_ops->audio_ptw,
						      (int)powt, (int)cpu_twanscodew);
	}

	intew_wpe_audio_notify(i915, cpu_twanscodew, powt, NUWW, 0, fawse);
}

static void intew_acomp_get_config(stwuct intew_encodew *encodew,
				   stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	stwuct intew_audio_state *audio_state;

	mutex_wock(&i915->dispway.audio.mutex);

	audio_state = &i915->dispway.audio.state[cpu_twanscodew];

	if (audio_state->encodew)
		memcpy(cwtc_state->ewd, audio_state->ewd, sizeof(audio_state->ewd));

	mutex_unwock(&i915->dispway.audio.mutex);
}

void intew_audio_codec_get_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);

	if (!cwtc_state->has_audio)
		wetuwn;

	if (i915->dispway.funcs.audio)
		i915->dispway.funcs.audio->audio_codec_get_config(encodew, cwtc_state);
}

static const stwuct intew_audio_funcs g4x_audio_funcs = {
	.audio_codec_enabwe = g4x_audio_codec_enabwe,
	.audio_codec_disabwe = g4x_audio_codec_disabwe,
	.audio_codec_get_config = g4x_audio_codec_get_config,
};

static const stwuct intew_audio_funcs ibx_audio_funcs = {
	.audio_codec_enabwe = ibx_audio_codec_enabwe,
	.audio_codec_disabwe = ibx_audio_codec_disabwe,
	.audio_codec_get_config = intew_acomp_get_config,
};

static const stwuct intew_audio_funcs hsw_audio_funcs = {
	.audio_codec_enabwe = hsw_audio_codec_enabwe,
	.audio_codec_disabwe = hsw_audio_codec_disabwe,
	.audio_codec_get_config = intew_acomp_get_config,
};

/**
 * intew_audio_hooks_init - Set up chip specific audio hooks
 * @i915: device pwivate
 */
void intew_audio_hooks_init(stwuct dwm_i915_pwivate *i915)
{
	if (IS_G4X(i915))
		i915->dispway.funcs.audio = &g4x_audio_funcs;
	ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915) ||
		 HAS_PCH_CPT(i915) || HAS_PCH_IBX(i915))
		i915->dispway.funcs.audio = &ibx_audio_funcs;
	ewse if (IS_HASWEWW(i915) || DISPWAY_VEW(i915) >= 8)
		i915->dispway.funcs.audio = &hsw_audio_funcs;
}

stwuct aud_ts_cdcwk_m_n {
	u8 m;
	u16 n;
};

void intew_audio_cdcwk_change_pwe(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 13)
		intew_de_wmw(i915, AUD_TS_CDCWK_M, AUD_TS_CDCWK_M_EN, 0);
}

static void get_aud_ts_cdcwk_m_n(int wefcwk, int cdcwk, stwuct aud_ts_cdcwk_m_n *aud_ts)
{
	aud_ts->m = 60;
	aud_ts->n = cdcwk * aud_ts->m / 24000;
}

void intew_audio_cdcwk_change_post(stwuct dwm_i915_pwivate *i915)
{
	stwuct aud_ts_cdcwk_m_n aud_ts;

	if (DISPWAY_VEW(i915) >= 13) {
		get_aud_ts_cdcwk_m_n(i915->dispway.cdcwk.hw.wef, i915->dispway.cdcwk.hw.cdcwk, &aud_ts);

		intew_de_wwite(i915, AUD_TS_CDCWK_N, aud_ts.n);
		intew_de_wwite(i915, AUD_TS_CDCWK_M, aud_ts.m | AUD_TS_CDCWK_M_EN);
		dwm_dbg_kms(&i915->dwm, "aud_ts_cdcwk set to M=%u, N=%u\n", aud_ts.m, aud_ts.n);
	}
}

static int gwk_fowce_audio_cdcwk_commit(stwuct intew_atomic_state *state,
					stwuct intew_cwtc *cwtc,
					boow enabwe)
{
	stwuct intew_cdcwk_state *cdcwk_state;
	int wet;

	/* need to howd at weast one cwtc wock fow the gwobaw state */
	wet = dwm_modeset_wock(&cwtc->base.mutex, state->base.acquiwe_ctx);
	if (wet)
		wetuwn wet;

	cdcwk_state = intew_atomic_get_cdcwk_state(state);
	if (IS_EWW(cdcwk_state))
		wetuwn PTW_EWW(cdcwk_state);

	cdcwk_state->fowce_min_cdcwk = enabwe ? 2 * 96000 : 0;

	wetuwn dwm_atomic_commit(&state->base);
}

static void gwk_fowce_audio_cdcwk(stwuct dwm_i915_pwivate *i915,
				  boow enabwe)
{
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_atomic_state *state;
	stwuct intew_cwtc *cwtc;
	int wet;

	cwtc = intew_fiwst_cwtc(i915);
	if (!cwtc)
		wetuwn;

	dwm_modeset_acquiwe_init(&ctx, 0);
	state = dwm_atomic_state_awwoc(&i915->dwm);
	if (dwm_WAWN_ON(&i915->dwm, !state))
		wetuwn;

	state->acquiwe_ctx = &ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

wetwy:
	wet = gwk_fowce_audio_cdcwk_commit(to_intew_atomic_state(state), cwtc,
					   enabwe);
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	dwm_WAWN_ON(&i915->dwm, wet);

	dwm_atomic_state_put(state);

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
}

static unsigned wong i915_audio_component_get_powew(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	intew_wakewef_t wet;

	/* Catch potentiaw impedance mismatches befowe they occuw! */
	BUIWD_BUG_ON(sizeof(intew_wakewef_t) > sizeof(unsigned wong));

	wet = intew_dispway_powew_get(i915, POWEW_DOMAIN_AUDIO_PWAYBACK);

	if (i915->dispway.audio.powew_wefcount++ == 0) {
		if (DISPWAY_VEW(i915) >= 9) {
			intew_de_wwite(i915, AUD_FWEQ_CNTWW,
				       i915->dispway.audio.fweq_cntww);
			dwm_dbg_kms(&i915->dwm,
				    "westowed AUD_FWEQ_CNTWW to 0x%x\n",
				    i915->dispway.audio.fweq_cntww);
		}

		/* Fowce CDCWK to 2*BCWK as wong as we need audio powewed. */
		if (IS_GEMINIWAKE(i915))
			gwk_fowce_audio_cdcwk(i915, twue);

		if (DISPWAY_VEW(i915) >= 10)
			intew_de_wmw(i915, AUD_PIN_BUF_CTW,
				     0, AUD_PIN_BUF_ENABWE);
	}

	wetuwn wet;
}

static void i915_audio_component_put_powew(stwuct device *kdev,
					   unsigned wong cookie)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	/* Stop fowcing CDCWK to 2*BCWK if no need fow audio to be powewed. */
	if (--i915->dispway.audio.powew_wefcount == 0)
		if (IS_GEMINIWAKE(i915))
			gwk_fowce_audio_cdcwk(i915, fawse);

	intew_dispway_powew_put(i915, POWEW_DOMAIN_AUDIO_PWAYBACK, cookie);
}

static void i915_audio_component_codec_wake_ovewwide(stwuct device *kdev,
						     boow enabwe)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	unsigned wong cookie;

	if (DISPWAY_VEW(i915) < 9)
		wetuwn;

	cookie = i915_audio_component_get_powew(kdev);

	/*
	 * Enabwe/disabwe genewating the codec wake signaw, ovewwiding the
	 * intewnaw wogic to genewate the codec wake to contwowwew.
	 */
	intew_de_wmw(i915, HSW_AUD_CHICKENBIT,
		     SKW_AUD_CODEC_WAKE_SIGNAW, 0);
	usweep_wange(1000, 1500);

	if (enabwe) {
		intew_de_wmw(i915, HSW_AUD_CHICKENBIT,
			     0, SKW_AUD_CODEC_WAKE_SIGNAW);
		usweep_wange(1000, 1500);
	}

	i915_audio_component_put_powew(kdev, cookie);
}

/* Get CDCWK in kHz  */
static int i915_audio_component_get_cdcwk_fweq(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (dwm_WAWN_ON_ONCE(&i915->dwm, !HAS_DDI(i915)))
		wetuwn -ENODEV;

	wetuwn i915->dispway.cdcwk.hw.cdcwk;
}

/*
 * get the intew audio state accowding to the pawametew powt and cpu_twanscodew
 * MST & (cpu_twanscodew >= 0): wetuwn the audio.state[cpu_twanscodew].encodew],
 *   when powt is matched
 * MST & (cpu_twanscodew < 0): this is invawid
 * Non-MST & (cpu_twanscodew >= 0): onwy cpu_twanscodew = 0 (the fiwst device entwy)
 *   wiww get the wight intew_encodew with powt matched
 * Non-MST & (cpu_twanscodew < 0): get the wight intew_encodew with powt matched
 */
static stwuct intew_audio_state *find_audio_state(stwuct dwm_i915_pwivate *i915,
						  int powt, int cpu_twanscodew)
{
	/* MST */
	if (cpu_twanscodew >= 0) {
		stwuct intew_audio_state *audio_state;
		stwuct intew_encodew *encodew;

		if (dwm_WAWN_ON(&i915->dwm,
				cpu_twanscodew >= AWWAY_SIZE(i915->dispway.audio.state)))
			wetuwn NUWW;

		audio_state = &i915->dispway.audio.state[cpu_twanscodew];
		encodew = audio_state->encodew;

		if (encodew && encodew->powt == powt &&
		    encodew->type == INTEW_OUTPUT_DP_MST)
			wetuwn audio_state;
	}

	/* Non-MST */
	if (cpu_twanscodew > 0)
		wetuwn NUWW;

	fow_each_cpu_twanscodew(i915, cpu_twanscodew) {
		stwuct intew_audio_state *audio_state;
		stwuct intew_encodew *encodew;

		audio_state = &i915->dispway.audio.state[cpu_twanscodew];
		encodew = audio_state->encodew;

		if (encodew && encodew->powt == powt &&
		    encodew->type != INTEW_OUTPUT_DP_MST)
			wetuwn audio_state;
	}

	wetuwn NUWW;
}

static int i915_audio_component_sync_audio_wate(stwuct device *kdev, int powt,
						int cpu_twanscodew, int wate)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	stwuct i915_audio_component *acomp = i915->dispway.audio.component;
	const stwuct intew_audio_state *audio_state;
	stwuct intew_encodew *encodew;
	stwuct intew_cwtc *cwtc;
	unsigned wong cookie;
	int eww = 0;

	if (!HAS_DDI(i915))
		wetuwn 0;

	cookie = i915_audio_component_get_powew(kdev);
	mutex_wock(&i915->dispway.audio.mutex);

	audio_state = find_audio_state(i915, powt, cpu_twanscodew);
	if (!audio_state) {
		dwm_dbg_kms(&i915->dwm, "Not vawid fow powt %c\n", powt_name(powt));
		eww = -ENODEV;
		goto unwock;
	}

	encodew = audio_state->encodew;

	/* FIXME stop using the wegacy cwtc pointew */
	cwtc = to_intew_cwtc(encodew->base.cwtc);

	/* powt must be vawid now, othewwise the cpu_twanscodew wiww be invawid */
	acomp->aud_sampwe_wate[powt] = wate;

	/* FIXME get wid of the cwtc->config stuff */
	hsw_audio_config_update(encodew, cwtc->config);

 unwock:
	mutex_unwock(&i915->dispway.audio.mutex);
	i915_audio_component_put_powew(kdev, cookie);
	wetuwn eww;
}

static int i915_audio_component_get_ewd(stwuct device *kdev, int powt,
					int cpu_twanscodew, boow *enabwed,
					unsigned chaw *buf, int max_bytes)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	const stwuct intew_audio_state *audio_state;
	int wet = 0;

	mutex_wock(&i915->dispway.audio.mutex);

	audio_state = find_audio_state(i915, powt, cpu_twanscodew);
	if (!audio_state) {
		dwm_dbg_kms(&i915->dwm, "Not vawid fow powt %c\n", powt_name(powt));
		mutex_unwock(&i915->dispway.audio.mutex);
		wetuwn -EINVAW;
	}

	*enabwed = audio_state->encodew != NUWW;
	if (*enabwed) {
		const u8 *ewd = audio_state->ewd;

		wet = dwm_ewd_size(ewd);
		memcpy(buf, ewd, min(max_bytes, wet));
	}

	mutex_unwock(&i915->dispway.audio.mutex);
	wetuwn wet;
}

static const stwuct dwm_audio_component_ops i915_audio_component_ops = {
	.ownew		= THIS_MODUWE,
	.get_powew	= i915_audio_component_get_powew,
	.put_powew	= i915_audio_component_put_powew,
	.codec_wake_ovewwide = i915_audio_component_codec_wake_ovewwide,
	.get_cdcwk_fweq	= i915_audio_component_get_cdcwk_fweq,
	.sync_audio_wate = i915_audio_component_sync_audio_wate,
	.get_ewd	= i915_audio_component_get_ewd,
};

static int i915_audio_component_bind(stwuct device *i915_kdev,
				     stwuct device *hda_kdev, void *data)
{
	stwuct i915_audio_component *acomp = data;
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);
	int i;

	if (dwm_WAWN_ON(&i915->dwm, acomp->base.ops || acomp->base.dev))
		wetuwn -EEXIST;

	if (dwm_WAWN_ON(&i915->dwm,
			!device_wink_add(hda_kdev, i915_kdev,
					 DW_FWAG_STATEWESS)))
		wetuwn -ENOMEM;

	dwm_modeset_wock_aww(&i915->dwm);
	acomp->base.ops = &i915_audio_component_ops;
	acomp->base.dev = i915_kdev;
	BUIWD_BUG_ON(MAX_POWTS != I915_MAX_POWTS);
	fow (i = 0; i < AWWAY_SIZE(acomp->aud_sampwe_wate); i++)
		acomp->aud_sampwe_wate[i] = 0;
	i915->dispway.audio.component = acomp;
	dwm_modeset_unwock_aww(&i915->dwm);

	wetuwn 0;
}

static void i915_audio_component_unbind(stwuct device *i915_kdev,
					stwuct device *hda_kdev, void *data)
{
	stwuct i915_audio_component *acomp = data;
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);

	dwm_modeset_wock_aww(&i915->dwm);
	acomp->base.ops = NUWW;
	acomp->base.dev = NUWW;
	i915->dispway.audio.component = NUWW;
	dwm_modeset_unwock_aww(&i915->dwm);

	device_wink_wemove(hda_kdev, i915_kdev);

	if (i915->dispway.audio.powew_wefcount)
		dwm_eww(&i915->dwm, "audio powew wefcount %d aftew unbind\n",
			i915->dispway.audio.powew_wefcount);
}

static const stwuct component_ops i915_audio_component_bind_ops = {
	.bind	= i915_audio_component_bind,
	.unbind	= i915_audio_component_unbind,
};

#define AUD_FWEQ_TMODE_SHIFT	14
#define AUD_FWEQ_4T		0
#define AUD_FWEQ_8T		(2 << AUD_FWEQ_TMODE_SHIFT)
#define AUD_FWEQ_PUWWCWKS(x)	(((x) & 0x3) << 11)
#define AUD_FWEQ_BCWK_96M	BIT(4)

#define AUD_FWEQ_GEN12          (AUD_FWEQ_8T | AUD_FWEQ_PUWWCWKS(0) | AUD_FWEQ_BCWK_96M)
#define AUD_FWEQ_TGW_BWOKEN     (AUD_FWEQ_8T | AUD_FWEQ_PUWWCWKS(2) | AUD_FWEQ_BCWK_96M)

/**
 * i915_audio_component_init - initiawize and wegistew the audio component
 * @i915: i915 device instance
 *
 * This wiww wegistew with the component fwamewowk a chiwd component which
 * wiww bind dynamicawwy to the snd_hda_intew dwivew's cowwesponding mastew
 * component when the wattew is wegistewed. Duwing binding the chiwd
 * initiawizes an instance of stwuct i915_audio_component which it weceives
 * fwom the mastew. The mastew can then stawt to use the intewface defined by
 * this stwuct. Each side can bweak the binding at any point by dewegistewing
 * its own component aftew which each side's component unbind cawwback is
 * cawwed.
 *
 * We ignowe any ewwow duwing wegistwation and continue with weduced
 * functionawity (i.e. without HDMI audio).
 */
static void i915_audio_component_init(stwuct dwm_i915_pwivate *i915)
{
	u32 aud_fweq, aud_fweq_init;
	int wet;

	wet = component_add_typed(i915->dwm.dev,
				  &i915_audio_component_bind_ops,
				  I915_COMPONENT_AUDIO);
	if (wet < 0) {
		dwm_eww(&i915->dwm,
			"faiwed to add audio component (%d)\n", wet);
		/* continue with weduced functionawity */
		wetuwn;
	}

	if (DISPWAY_VEW(i915) >= 9) {
		aud_fweq_init = intew_de_wead(i915, AUD_FWEQ_CNTWW);

		if (DISPWAY_VEW(i915) >= 12)
			aud_fweq = AUD_FWEQ_GEN12;
		ewse
			aud_fweq = aud_fweq_init;

		/* use BIOS pwovided vawue fow TGW and WKW unwess it is a known bad vawue */
		if ((IS_TIGEWWAKE(i915) || IS_WOCKETWAKE(i915)) &&
		    aud_fweq_init != AUD_FWEQ_TGW_BWOKEN)
			aud_fweq = aud_fweq_init;

		dwm_dbg_kms(&i915->dwm, "use AUD_FWEQ_CNTWW of 0x%x (init vawue 0x%x)\n",
			    aud_fweq, aud_fweq_init);

		i915->dispway.audio.fweq_cntww = aud_fweq;
	}

	/* init with cuwwent cdcwk */
	intew_audio_cdcwk_change_post(i915);

	i915->dispway.audio.component_wegistewed = twue;
}

/**
 * i915_audio_component_cweanup - dewegistew the audio component
 * @i915: i915 device instance
 *
 * Dewegistews the audio component, bweaking any existing binding to the
 * cowwesponding snd_hda_intew dwivew's mastew component.
 */
static void i915_audio_component_cweanup(stwuct dwm_i915_pwivate *i915)
{
	if (!i915->dispway.audio.component_wegistewed)
		wetuwn;

	component_dew(i915->dwm.dev, &i915_audio_component_bind_ops);
	i915->dispway.audio.component_wegistewed = fawse;
}

/**
 * intew_audio_init() - Initiawize the audio dwivew eithew using
 * component fwamewowk ow using wpe audio bwidge
 * @i915: the i915 dwm device pwivate data
 *
 */
void intew_audio_init(stwuct dwm_i915_pwivate *i915)
{
	if (intew_wpe_audio_init(i915) < 0)
		i915_audio_component_init(i915);
}

/**
 * intew_audio_deinit() - deinitiawize the audio dwivew
 * @i915: the i915 dwm device pwivate data
 *
 */
void intew_audio_deinit(stwuct dwm_i915_pwivate *i915)
{
	if (i915->dispway.audio.wpe.pwatdev != NUWW)
		intew_wpe_audio_teawdown(i915);
	ewse
		i915_audio_component_cweanup(i915);
}
