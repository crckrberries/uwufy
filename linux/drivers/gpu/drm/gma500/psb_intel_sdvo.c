/*
 * Copywight 2006 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight © 2006-2007 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
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
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"
#incwude "psb_intew_sdvo_wegs.h"

#define SDVO_TMDS_MASK (SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_TMDS1)
#define SDVO_WGB_MASK  (SDVO_OUTPUT_WGB0 | SDVO_OUTPUT_WGB1)
#define SDVO_WVDS_MASK (SDVO_OUTPUT_WVDS0 | SDVO_OUTPUT_WVDS1)
#define SDVO_TV_MASK   (SDVO_OUTPUT_CVBS0 | SDVO_OUTPUT_SVID0)

#define SDVO_OUTPUT_MASK (SDVO_TMDS_MASK | SDVO_WGB_MASK | SDVO_WVDS_MASK |\
                         SDVO_TV_MASK)

#define IS_TV(c)	(c->output_fwag & SDVO_TV_MASK)
#define IS_TMDS(c)	(c->output_fwag & SDVO_TMDS_MASK)
#define IS_WVDS(c)	(c->output_fwag & SDVO_WVDS_MASK)
#define IS_TV_OW_WVDS(c) (c->output_fwag & (SDVO_TV_MASK | SDVO_WVDS_MASK))


static const chaw *tv_fowmat_names[] = {
	"NTSC_M"   , "NTSC_J"  , "NTSC_443",
	"PAW_B"    , "PAW_D"   , "PAW_G"   ,
	"PAW_H"    , "PAW_I"   , "PAW_M"   ,
	"PAW_N"    , "PAW_NC"  , "PAW_60"  ,
	"SECAM_B"  , "SECAM_D" , "SECAM_G" ,
	"SECAM_K"  , "SECAM_K1", "SECAM_W" ,
	"SECAM_60"
};

stwuct psb_intew_sdvo {
	stwuct gma_encodew base;

	stwuct i2c_adaptew *i2c;
	u8 swave_addw;

	stwuct i2c_adaptew ddc;

	/* Wegistew fow the SDVO device: SDVOB ow SDVOC */
	int sdvo_weg;

	/* Active outputs contwowwed by this SDVO output */
	uint16_t contwowwed_output;

	/*
	 * Capabiwities of the SDVO device wetuwned by
	 * i830_sdvo_get_capabiwities()
	 */
	stwuct psb_intew_sdvo_caps caps;

	/* Pixew cwock wimitations wepowted by the SDVO device, in kHz */
	int pixew_cwock_min, pixew_cwock_max;

	/*
	* Fow muwtipwe function SDVO device,
	* this is fow cuwwent attached outputs.
	*/
	uint16_t attached_output;

	/**
	 * This is used to sewect the cowow wange of WBG outputs in HDMI mode.
	 * It is onwy vawid when using TMDS encoding and 8 bit pew cowow mode.
	 */
	uint32_t cowow_wange;

	/**
	 * This is set if we'we going to tweat the device as TV-out.
	 *
	 * Whiwe we have these nice fwiendwy fwags fow output types that ought
	 * to decide this fow us, the S-Video output on ouw HDMI+S-Video cawd
	 * shows up as WGB1 (VGA).
	 */
	boow is_tv;

	/* This is fow cuwwent tv fowmat name */
	int tv_fowmat_index;

	/**
	 * This is set if we tweat the device as HDMI, instead of DVI.
	 */
	boow is_hdmi;
	boow has_hdmi_monitow;
	boow has_hdmi_audio;

	/**
	 * This is set if we detect output of sdvo device as WVDS and
	 * have a vawid fixed mode to use with the panew.
	 */
	boow is_wvds;

	/**
	 * This is sdvo fixed panew mode pointew
	 */
	stwuct dwm_dispway_mode *sdvo_wvds_fixed_mode;

	/* DDC bus used by this SDVO encodew */
	uint8_t ddc_bus;

	u8 pixew_muwtipwiew;

	/* Input timings fow adjusted_mode */
	stwuct psb_intew_sdvo_dtd input_dtd;

	/* Saved SDVO output states */
	uint32_t saveSDVO; /* Can be SDVOB ow SDVOC depending on sdvo_weg */
};

stwuct psb_intew_sdvo_connectow {
	stwuct gma_connectow base;

	/* Mawk the type of connectow */
	uint16_t output_fwag;

	int fowce_audio;

	/* This contains aww cuwwent suppowted TV fowmat */
	u8 tv_fowmat_suppowted[AWWAY_SIZE(tv_fowmat_names)];
	int   fowmat_suppowted_num;
	stwuct dwm_pwopewty *tv_fowmat;

	/* add the pwopewty fow the SDVO-TV */
	stwuct dwm_pwopewty *weft;
	stwuct dwm_pwopewty *wight;
	stwuct dwm_pwopewty *top;
	stwuct dwm_pwopewty *bottom;
	stwuct dwm_pwopewty *hpos;
	stwuct dwm_pwopewty *vpos;
	stwuct dwm_pwopewty *contwast;
	stwuct dwm_pwopewty *satuwation;
	stwuct dwm_pwopewty *hue;
	stwuct dwm_pwopewty *shawpness;
	stwuct dwm_pwopewty *fwickew_fiwtew;
	stwuct dwm_pwopewty *fwickew_fiwtew_adaptive;
	stwuct dwm_pwopewty *fwickew_fiwtew_2d;
	stwuct dwm_pwopewty *tv_chwoma_fiwtew;
	stwuct dwm_pwopewty *tv_wuma_fiwtew;
	stwuct dwm_pwopewty *dot_cwaww;

	/* add the pwopewty fow the SDVO-TV/WVDS */
	stwuct dwm_pwopewty *bwightness;

	/* Add vawiabwe to wecowd cuwwent setting fow the above pwopewty */
	u32	weft_mawgin, wight_mawgin, top_mawgin, bottom_mawgin;

	/* this is to get the wange of mawgin.*/
	u32	max_hscan,  max_vscan;
	u32	max_hpos, cuw_hpos;
	u32	max_vpos, cuw_vpos;
	u32	cuw_bwightness, max_bwightness;
	u32	cuw_contwast,	max_contwast;
	u32	cuw_satuwation, max_satuwation;
	u32	cuw_hue,	max_hue;
	u32	cuw_shawpness,	max_shawpness;
	u32	cuw_fwickew_fiwtew,		max_fwickew_fiwtew;
	u32	cuw_fwickew_fiwtew_adaptive,	max_fwickew_fiwtew_adaptive;
	u32	cuw_fwickew_fiwtew_2d,		max_fwickew_fiwtew_2d;
	u32	cuw_tv_chwoma_fiwtew,	max_tv_chwoma_fiwtew;
	u32	cuw_tv_wuma_fiwtew,	max_tv_wuma_fiwtew;
	u32	cuw_dot_cwaww,	max_dot_cwaww;
};

static stwuct psb_intew_sdvo *to_psb_intew_sdvo(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct psb_intew_sdvo, base.base);
}

static stwuct psb_intew_sdvo *intew_attached_sdvo(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(gma_attached_encodew(connectow),
			    stwuct psb_intew_sdvo, base);
}

static stwuct psb_intew_sdvo_connectow *to_psb_intew_sdvo_connectow(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(to_gma_connectow(connectow), stwuct psb_intew_sdvo_connectow, base);
}

static boow
psb_intew_sdvo_output_setup(stwuct psb_intew_sdvo *psb_intew_sdvo, uint16_t fwags);
static boow
psb_intew_sdvo_tv_cweate_pwopewty(stwuct psb_intew_sdvo *psb_intew_sdvo,
			      stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow,
			      int type);
static boow
psb_intew_sdvo_cweate_enhance_pwopewty(stwuct psb_intew_sdvo *psb_intew_sdvo,
				   stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow);

/*
 * Wwites the SDVOB ow SDVOC with the given vawue, but awways wwites both
 * SDVOB and SDVOC to wowk awound appawent hawdwawe issues (accowding to
 * comments in the BIOS).
 */
static void psb_intew_sdvo_wwite_sdvox(stwuct psb_intew_sdvo *psb_intew_sdvo, u32 vaw)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	u32 bvaw = vaw, cvaw = vaw;
	int i, j;
	int need_aux = IS_MWST(dev) ? 1 : 0;

	fow (j = 0; j <= need_aux; j++) {
		if (psb_intew_sdvo->sdvo_weg == SDVOB)
			cvaw = WEG_WEAD_WITH_AUX(SDVOC, j);
		ewse
			bvaw = WEG_WEAD_WITH_AUX(SDVOB, j);

		/*
		* Wwite the wegistews twice fow wuck. Sometimes,
		* wwiting them onwy once doesn't appeaw to 'stick'.
		* The BIOS does this too. Yay, magic
		*/
		fow (i = 0; i < 2; i++) {
			WEG_WWITE_WITH_AUX(SDVOB, bvaw, j);
			WEG_WEAD_WITH_AUX(SDVOB, j);
			WEG_WWITE_WITH_AUX(SDVOC, cvaw, j);
			WEG_WEAD_WITH_AUX(SDVOC, j);
		}
	}
}

static boow psb_intew_sdvo_wead_byte(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 addw, u8 *ch)
{
	stwuct i2c_msg msgs[] = {
		{
			.addw = psb_intew_sdvo->swave_addw,
			.fwags = 0,
			.wen = 1,
			.buf = &addw,
		},
		{
			.addw = psb_intew_sdvo->swave_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = ch,
		}
	};
	int wet;

	if ((wet = i2c_twansfew(psb_intew_sdvo->i2c, msgs, 2)) == 2)
		wetuwn twue;

	DWM_DEBUG_KMS("i2c twansfew wetuwned %d\n", wet);
	wetuwn fawse;
}

#define SDVO_CMD_NAME_ENTWY(cmd) {cmd, #cmd}
/** Mapping of command numbews to names, fow debug output */
static const stwuct _sdvo_cmd_name {
	u8 cmd;
	const chaw *name;
} sdvo_cmd_names[] = {
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_WESET),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_DEVICE_CAPS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_FIWMWAWE_WEV),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_TWAINED_INPUTS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_ACTIVE_OUTPUTS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_ACTIVE_OUTPUTS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_IN_OUT_MAP),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_IN_OUT_MAP),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_ATTACHED_DISPWAYS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HOT_PWUG_SUPPOWT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_ACTIVE_HOT_PWUG),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_ACTIVE_HOT_PWUG),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_INTEWWUPT_EVENT_SOUWCE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_TAWGET_INPUT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_TAWGET_OUTPUT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_INPUT_TIMINGS_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_INPUT_TIMINGS_PAWT2),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_INPUT_TIMINGS_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_INPUT_TIMINGS_PAWT2),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_INPUT_TIMINGS_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_OUTPUT_TIMINGS_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_OUTPUT_TIMINGS_PAWT2),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_OUTPUT_TIMINGS_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_OUTPUT_TIMINGS_PAWT2),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_CWEATE_PWEFEWWED_INPUT_TIMING),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT1),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT2),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_INPUT_PIXEW_CWOCK_WANGE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_OUTPUT_PIXEW_CWOCK_WANGE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SUPPOWTED_CWOCK_WATE_MUWTS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_CWOCK_WATE_MUWT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_CWOCK_WATE_MUWT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SUPPOWTED_TV_FOWMATS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_TV_FOWMAT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_TV_FOWMAT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SUPPOWTED_POWEW_STATES),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_POWEW_STATE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_ENCODEW_POWEW_STATE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_DISPWAY_POWEW_STATE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_CONTWOW_BUS_SWITCH),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SDTV_WESOWUTION_SUPPOWT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SCAWED_HDTV_WESOWUTION_SUPPOWT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SUPPOWTED_ENHANCEMENTS),

    /* Add the op code fow SDVO enhancements */
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_HPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_VPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_VPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_VPOS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_SATUWATION),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SATUWATION),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_SATUWATION),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_HUE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HUE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HUE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_CONTWAST),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_CONTWAST),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_CONTWAST),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_BWIGHTNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_BWIGHTNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_BWIGHTNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_OVEWSCAN_H),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_OVEWSCAN_H),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_OVEWSCAN_H),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_OVEWSCAN_V),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_OVEWSCAN_V),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_OVEWSCAN_V),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_FWICKEW_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_FWICKEW_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_FWICKEW_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_FWICKEW_FIWTEW_ADAPTIVE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_FWICKEW_FIWTEW_ADAPTIVE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_FWICKEW_FIWTEW_ADAPTIVE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_FWICKEW_FIWTEW_2D),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_FWICKEW_FIWTEW_2D),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_FWICKEW_FIWTEW_2D),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_SHAWPNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SHAWPNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_SHAWPNESS),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_DOT_CWAWW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_DOT_CWAWW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_TV_CHWOMA_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_TV_CHWOMA_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_TV_CHWOMA_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_MAX_TV_WUMA_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_TV_WUMA_FIWTEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_TV_WUMA_FIWTEW),

    /* HDMI op code */
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_SUPP_ENCODE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_ENCODE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_ENCODE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_PIXEW_WEPWI),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_PIXEW_WEPWI),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_COWOWIMETWY_CAP),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_COWOWIMETWY),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_COWOWIMETWY),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_AUDIO_ENCWYPT_PWEFEW),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_AUDIO_STAT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_AUDIO_STAT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HBUF_INDEX),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HBUF_INDEX),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HBUF_INFO),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HBUF_AV_SPWIT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HBUF_AV_SPWIT),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HBUF_TXWATE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HBUF_TXWATE),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_SET_HBUF_DATA),
    SDVO_CMD_NAME_ENTWY(SDVO_CMD_GET_HBUF_DATA),
};

#define IS_SDVOB(weg)	(weg == SDVOB)
#define SDVO_NAME(svdo) (IS_SDVOB((svdo)->sdvo_weg) ? "SDVOB" : "SDVOC")

static void psb_intew_sdvo_debug_wwite(stwuct psb_intew_sdvo *psb_intew_sdvo,
				       u8 cmd, const void *awgs, int awgs_wen)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	int i, pos = 0;
	chaw buffew[73];

#define BUF_PWINT(awgs...) \
	pos += snpwintf(buffew + pos, max_t(int, sizeof(buffew) - pos, 0), awgs)

	fow (i = 0; i < awgs_wen; i++) {
		BUF_PWINT("%02X ", ((u8 *)awgs)[i]);
	}

	fow (; i < 8; i++) {
		BUF_PWINT("   ");
	}

	fow (i = 0; i < AWWAY_SIZE(sdvo_cmd_names); i++) {
		if (cmd == sdvo_cmd_names[i].cmd) {
			BUF_PWINT("(%s)", sdvo_cmd_names[i].name);
			bweak;
		}
	}

	if (i == AWWAY_SIZE(sdvo_cmd_names))
		BUF_PWINT("(%02X)", cmd);

	dwm_WAWN_ON(dev, pos >= sizeof(buffew) - 1);
#undef BUF_PWINT

	DWM_DEBUG_KMS("%s: W: %02X %s\n", SDVO_NAME(psb_intew_sdvo), cmd, buffew);
}

static const chaw *cmd_status_names[] = {
	"Powew on",
	"Success",
	"Not suppowted",
	"Invawid awg",
	"Pending",
	"Tawget not specified",
	"Scawing not suppowted"
};

#define MAX_AWG_WEN 32

static boow psb_intew_sdvo_wwite_cmd(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 cmd,
				 const void *awgs, int awgs_wen)
{
	u8 buf[MAX_AWG_WEN*2 + 2], status;
	stwuct i2c_msg msgs[MAX_AWG_WEN + 3];
	int i, wet;

	if (awgs_wen > MAX_AWG_WEN) {
		DWM_EWWOW("Need to incwease awg wength\n");
		wetuwn fawse;
	}

	psb_intew_sdvo_debug_wwite(psb_intew_sdvo, cmd, awgs, awgs_wen);

	fow (i = 0; i < awgs_wen; i++) {
		msgs[i].addw = psb_intew_sdvo->swave_addw;
		msgs[i].fwags = 0;
		msgs[i].wen = 2;
		msgs[i].buf = buf + 2 *i;
		buf[2*i + 0] = SDVO_I2C_AWG_0 - i;
		buf[2*i + 1] = ((u8*)awgs)[i];
	}
	msgs[i].addw = psb_intew_sdvo->swave_addw;
	msgs[i].fwags = 0;
	msgs[i].wen = 2;
	msgs[i].buf = buf + 2*i;
	buf[2*i + 0] = SDVO_I2C_OPCODE;
	buf[2*i + 1] = cmd;

	/* the fowwowing two awe to wead the wesponse */
	status = SDVO_I2C_CMD_STATUS;
	msgs[i+1].addw = psb_intew_sdvo->swave_addw;
	msgs[i+1].fwags = 0;
	msgs[i+1].wen = 1;
	msgs[i+1].buf = &status;

	msgs[i+2].addw = psb_intew_sdvo->swave_addw;
	msgs[i+2].fwags = I2C_M_WD;
	msgs[i+2].wen = 1;
	msgs[i+2].buf = &status;

	wet = i2c_twansfew(psb_intew_sdvo->i2c, msgs, i+3);
	if (wet < 0) {
		DWM_DEBUG_KMS("I2c twansfew wetuwned %d\n", wet);
		wetuwn fawse;
	}
	if (wet != i+3) {
		/* faiwuwe in I2C twansfew */
		DWM_DEBUG_KMS("I2c twansfew wetuwned %d/%d\n", wet, i+3);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow psb_intew_sdvo_wead_wesponse(stwuct psb_intew_sdvo *psb_intew_sdvo,
					 void *wesponse, int wesponse_wen)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	chaw buffew[73];
	int i, pos = 0;
	u8 wetwy = 5;
	u8 status;

	/*
	 * The documentation states that aww commands wiww be
	 * pwocessed within 15µs, and that we need onwy poww
	 * the status byte a maximum of 3 times in owdew fow the
	 * command to be compwete.
	 *
	 * Check 5 times in case the hawdwawe faiwed to wead the docs.
	 */
	if (!psb_intew_sdvo_wead_byte(psb_intew_sdvo,
				  SDVO_I2C_CMD_STATUS,
				  &status))
		goto wog_faiw;

	whiwe ((status == SDVO_CMD_STATUS_PENDING ||
		status == SDVO_CMD_STATUS_TAWGET_NOT_SPECIFIED) && wetwy--) {
		udeway(15);
		if (!psb_intew_sdvo_wead_byte(psb_intew_sdvo,
					  SDVO_I2C_CMD_STATUS,
					  &status))
			goto wog_faiw;
	}

#define BUF_PWINT(awgs...) \
	pos += snpwintf(buffew + pos, max_t(int, sizeof(buffew) - pos, 0), awgs)

	if (status <= SDVO_CMD_STATUS_SCAWING_NOT_SUPP)
		BUF_PWINT("(%s)", cmd_status_names[status]);
	ewse
		BUF_PWINT("(??? %d)", status);

	if (status != SDVO_CMD_STATUS_SUCCESS)
		goto wog_faiw;

	/* Wead the command wesponse */
	fow (i = 0; i < wesponse_wen; i++) {
		if (!psb_intew_sdvo_wead_byte(psb_intew_sdvo,
					  SDVO_I2C_WETUWN_0 + i,
					  &((u8 *)wesponse)[i]))
			goto wog_faiw;
		BUF_PWINT(" %02X", ((u8 *)wesponse)[i]);
	}

	dwm_WAWN_ON(dev, pos >= sizeof(buffew) - 1);
#undef BUF_PWINT

	DWM_DEBUG_KMS("%s: W: %s\n", SDVO_NAME(psb_intew_sdvo), buffew);
	wetuwn twue;

wog_faiw:
	DWM_DEBUG_KMS("%s: W: ... faiwed %s\n",
		      SDVO_NAME(psb_intew_sdvo), buffew);
	wetuwn fawse;
}

static int psb_intew_sdvo_get_pixew_muwtipwiew(stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock >= 100000)
		wetuwn 1;
	ewse if (mode->cwock >= 50000)
		wetuwn 2;
	ewse
		wetuwn 4;
}

static boow psb_intew_sdvo_set_contwow_bus_switch(stwuct psb_intew_sdvo *psb_intew_sdvo,
					      u8 ddc_bus)
{
	/* This must be the immediatewy pweceding wwite befowe the i2c xfew */
	wetuwn psb_intew_sdvo_wwite_cmd(psb_intew_sdvo,
				    SDVO_CMD_SET_CONTWOW_BUS_SWITCH,
				    &ddc_bus, 1);
}

static boow psb_intew_sdvo_set_vawue(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 cmd, const void *data, int wen)
{
	if (!psb_intew_sdvo_wwite_cmd(psb_intew_sdvo, cmd, data, wen))
		wetuwn fawse;

	wetuwn psb_intew_sdvo_wead_wesponse(psb_intew_sdvo, NUWW, 0);
}

static boow
psb_intew_sdvo_get_vawue(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 cmd, void *vawue, int wen)
{
	if (!psb_intew_sdvo_wwite_cmd(psb_intew_sdvo, cmd, NUWW, 0))
		wetuwn fawse;

	wetuwn psb_intew_sdvo_wead_wesponse(psb_intew_sdvo, vawue, wen);
}

static boow psb_intew_sdvo_set_tawget_input(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	stwuct psb_intew_sdvo_set_tawget_input_awgs tawgets = {0};
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_SET_TAWGET_INPUT,
				    &tawgets, sizeof(tawgets));
}

/*
 * Wetuwn whethew each input is twained.
 *
 * This function is making an assumption about the wayout of the wesponse,
 * which shouwd be checked against the docs.
 */
static boow psb_intew_sdvo_get_twained_inputs(stwuct psb_intew_sdvo *psb_intew_sdvo, boow *input_1, boow *input_2)
{
	stwuct psb_intew_sdvo_get_twained_inputs_wesponse wesponse;

	BUIWD_BUG_ON(sizeof(wesponse) != 1);
	if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_TWAINED_INPUTS,
				  &wesponse, sizeof(wesponse)))
		wetuwn fawse;

	*input_1 = wesponse.input0_twained;
	*input_2 = wesponse.input1_twained;
	wetuwn twue;
}

static boow psb_intew_sdvo_set_active_outputs(stwuct psb_intew_sdvo *psb_intew_sdvo,
					  u16 outputs)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_SET_ACTIVE_OUTPUTS,
				    &outputs, sizeof(outputs));
}

static boow psb_intew_sdvo_set_encodew_powew_state(stwuct psb_intew_sdvo *psb_intew_sdvo,
					       int mode)
{
	u8 state = SDVO_ENCODEW_STATE_ON;

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		state = SDVO_ENCODEW_STATE_ON;
		bweak;
	case DWM_MODE_DPMS_STANDBY:
		state = SDVO_ENCODEW_STATE_STANDBY;
		bweak;
	case DWM_MODE_DPMS_SUSPEND:
		state = SDVO_ENCODEW_STATE_SUSPEND;
		bweak;
	case DWM_MODE_DPMS_OFF:
		state = SDVO_ENCODEW_STATE_OFF;
		bweak;
	}

	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_SET_ENCODEW_POWEW_STATE, &state, sizeof(state));
}

static boow psb_intew_sdvo_get_input_pixew_cwock_wange(stwuct psb_intew_sdvo *psb_intew_sdvo,
						   int *cwock_min,
						   int *cwock_max)
{
	stwuct psb_intew_sdvo_pixew_cwock_wange cwocks;

	BUIWD_BUG_ON(sizeof(cwocks) != 4);
	if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
				  SDVO_CMD_GET_INPUT_PIXEW_CWOCK_WANGE,
				  &cwocks, sizeof(cwocks)))
		wetuwn fawse;

	/* Convewt the vawues fwom units of 10 kHz to kHz. */
	*cwock_min = cwocks.min * 10;
	*cwock_max = cwocks.max * 10;
	wetuwn twue;
}

static boow psb_intew_sdvo_set_tawget_output(stwuct psb_intew_sdvo *psb_intew_sdvo,
					 u16 outputs)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_SET_TAWGET_OUTPUT,
				    &outputs, sizeof(outputs));
}

static boow psb_intew_sdvo_set_timing(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 cmd,
				  stwuct psb_intew_sdvo_dtd *dtd)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo, cmd, &dtd->pawt1, sizeof(dtd->pawt1)) &&
		psb_intew_sdvo_set_vawue(psb_intew_sdvo, cmd + 1, &dtd->pawt2, sizeof(dtd->pawt2));
}

static boow psb_intew_sdvo_set_input_timing(stwuct psb_intew_sdvo *psb_intew_sdvo,
					 stwuct psb_intew_sdvo_dtd *dtd)
{
	wetuwn psb_intew_sdvo_set_timing(psb_intew_sdvo,
				     SDVO_CMD_SET_INPUT_TIMINGS_PAWT1, dtd);
}

static boow psb_intew_sdvo_set_output_timing(stwuct psb_intew_sdvo *psb_intew_sdvo,
					 stwuct psb_intew_sdvo_dtd *dtd)
{
	wetuwn psb_intew_sdvo_set_timing(psb_intew_sdvo,
				     SDVO_CMD_SET_OUTPUT_TIMINGS_PAWT1, dtd);
}

static boow
psb_intew_sdvo_cweate_pwefewwed_input_timing(stwuct psb_intew_sdvo *psb_intew_sdvo,
					 uint16_t cwock,
					 uint16_t width,
					 uint16_t height)
{
	stwuct psb_intew_sdvo_pwefewwed_input_timing_awgs awgs;

	memset(&awgs, 0, sizeof(awgs));
	awgs.cwock = cwock;
	awgs.width = width;
	awgs.height = height;
	awgs.intewwace = 0;

	if (psb_intew_sdvo->is_wvds &&
	   (psb_intew_sdvo->sdvo_wvds_fixed_mode->hdispway != width ||
	    psb_intew_sdvo->sdvo_wvds_fixed_mode->vdispway != height))
		awgs.scawed = 1;

	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_CWEATE_PWEFEWWED_INPUT_TIMING,
				    &awgs, sizeof(awgs));
}

static boow psb_intew_sdvo_get_pwefewwed_input_timing(stwuct psb_intew_sdvo *psb_intew_sdvo,
						  stwuct psb_intew_sdvo_dtd *dtd)
{
	BUIWD_BUG_ON(sizeof(dtd->pawt1) != 8);
	BUIWD_BUG_ON(sizeof(dtd->pawt2) != 8);
	wetuwn psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT1,
				    &dtd->pawt1, sizeof(dtd->pawt1)) &&
		psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT2,
				     &dtd->pawt2, sizeof(dtd->pawt2));
}

static boow psb_intew_sdvo_set_cwock_wate_muwt(stwuct psb_intew_sdvo *psb_intew_sdvo, u8 vaw)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo, SDVO_CMD_SET_CWOCK_WATE_MUWT, &vaw, 1);
}

static void psb_intew_sdvo_get_dtd_fwom_mode(stwuct psb_intew_sdvo_dtd *dtd,
					 const stwuct dwm_dispway_mode *mode)
{
	uint16_t width, height;
	uint16_t h_bwank_wen, h_sync_wen, v_bwank_wen, v_sync_wen;
	uint16_t h_sync_offset, v_sync_offset;

	width = mode->cwtc_hdispway;
	height = mode->cwtc_vdispway;

	/* do some mode twanswations */
	h_bwank_wen = mode->cwtc_hbwank_end - mode->cwtc_hbwank_stawt;
	h_sync_wen = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;

	v_bwank_wen = mode->cwtc_vbwank_end - mode->cwtc_vbwank_stawt;
	v_sync_wen = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;

	h_sync_offset = mode->cwtc_hsync_stawt - mode->cwtc_hbwank_stawt;
	v_sync_offset = mode->cwtc_vsync_stawt - mode->cwtc_vbwank_stawt;

	dtd->pawt1.cwock = mode->cwock / 10;
	dtd->pawt1.h_active = width & 0xff;
	dtd->pawt1.h_bwank = h_bwank_wen & 0xff;
	dtd->pawt1.h_high = (((width >> 8) & 0xf) << 4) |
		((h_bwank_wen >> 8) & 0xf);
	dtd->pawt1.v_active = height & 0xff;
	dtd->pawt1.v_bwank = v_bwank_wen & 0xff;
	dtd->pawt1.v_high = (((height >> 8) & 0xf) << 4) |
		((v_bwank_wen >> 8) & 0xf);

	dtd->pawt2.h_sync_off = h_sync_offset & 0xff;
	dtd->pawt2.h_sync_width = h_sync_wen & 0xff;
	dtd->pawt2.v_sync_off_width = (v_sync_offset & 0xf) << 4 |
		(v_sync_wen & 0xf);
	dtd->pawt2.sync_off_width_high = ((h_sync_offset & 0x300) >> 2) |
		((h_sync_wen & 0x300) >> 4) | ((v_sync_offset & 0x30) >> 2) |
		((v_sync_wen & 0x30) >> 4);

	dtd->pawt2.dtd_fwags = 0x18;
	if (mode->fwags & DWM_MODE_FWAG_PHSYNC)
		dtd->pawt2.dtd_fwags |= 0x2;
	if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
		dtd->pawt2.dtd_fwags |= 0x4;

	dtd->pawt2.sdvo_fwags = 0;
	dtd->pawt2.v_sync_off_high = v_sync_offset & 0xc0;
	dtd->pawt2.wesewved = 0;
}

static void psb_intew_sdvo_get_mode_fwom_dtd(stwuct dwm_dispway_mode * mode,
					 const stwuct psb_intew_sdvo_dtd *dtd)
{
	mode->hdispway = dtd->pawt1.h_active;
	mode->hdispway += ((dtd->pawt1.h_high >> 4) & 0x0f) << 8;
	mode->hsync_stawt = mode->hdispway + dtd->pawt2.h_sync_off;
	mode->hsync_stawt += (dtd->pawt2.sync_off_width_high & 0xc0) << 2;
	mode->hsync_end = mode->hsync_stawt + dtd->pawt2.h_sync_width;
	mode->hsync_end += (dtd->pawt2.sync_off_width_high & 0x30) << 4;
	mode->htotaw = mode->hdispway + dtd->pawt1.h_bwank;
	mode->htotaw += (dtd->pawt1.h_high & 0xf) << 8;

	mode->vdispway = dtd->pawt1.v_active;
	mode->vdispway += ((dtd->pawt1.v_high >> 4) & 0x0f) << 8;
	mode->vsync_stawt = mode->vdispway;
	mode->vsync_stawt += (dtd->pawt2.v_sync_off_width >> 4) & 0xf;
	mode->vsync_stawt += (dtd->pawt2.sync_off_width_high & 0x0c) << 2;
	mode->vsync_stawt += dtd->pawt2.v_sync_off_high & 0xc0;
	mode->vsync_end = mode->vsync_stawt +
		(dtd->pawt2.v_sync_off_width & 0xf);
	mode->vsync_end += (dtd->pawt2.sync_off_width_high & 0x3) << 4;
	mode->vtotaw = mode->vdispway + dtd->pawt1.v_bwank;
	mode->vtotaw += (dtd->pawt1.v_high & 0xf) << 8;

	mode->cwock = dtd->pawt1.cwock * 10;

	mode->fwags &= ~(DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC);
	if (dtd->pawt2.dtd_fwags & 0x2)
		mode->fwags |= DWM_MODE_FWAG_PHSYNC;
	if (dtd->pawt2.dtd_fwags & 0x4)
		mode->fwags |= DWM_MODE_FWAG_PVSYNC;
}

static boow psb_intew_sdvo_check_supp_encode(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	stwuct psb_intew_sdvo_encode encode;

	BUIWD_BUG_ON(sizeof(encode) != 2);
	wetuwn psb_intew_sdvo_get_vawue(psb_intew_sdvo,
				  SDVO_CMD_GET_SUPP_ENCODE,
				  &encode, sizeof(encode));
}

static boow psb_intew_sdvo_set_encode(stwuct psb_intew_sdvo *psb_intew_sdvo,
				  uint8_t mode)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo, SDVO_CMD_SET_ENCODE, &mode, 1);
}

static boow psb_intew_sdvo_set_cowowimetwy(stwuct psb_intew_sdvo *psb_intew_sdvo,
				       uint8_t mode)
{
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo, SDVO_CMD_SET_COWOWIMETWY, &mode, 1);
}

#if 0
static void psb_intew_sdvo_dump_hdmi_buf(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	int i, j;
	uint8_t set_buf_index[2];
	uint8_t av_spwit;
	uint8_t buf_size;
	uint8_t buf[48];
	uint8_t *pos;

	psb_intew_sdvo_get_vawue(encodew, SDVO_CMD_GET_HBUF_AV_SPWIT, &av_spwit, 1);

	fow (i = 0; i <= av_spwit; i++) {
		set_buf_index[0] = i; set_buf_index[1] = 0;
		psb_intew_sdvo_wwite_cmd(encodew, SDVO_CMD_SET_HBUF_INDEX,
				     set_buf_index, 2);
		psb_intew_sdvo_wwite_cmd(encodew, SDVO_CMD_GET_HBUF_INFO, NUWW, 0);
		psb_intew_sdvo_wead_wesponse(encodew, &buf_size, 1);

		pos = buf;
		fow (j = 0; j <= buf_size; j += 8) {
			psb_intew_sdvo_wwite_cmd(encodew, SDVO_CMD_GET_HBUF_DATA,
					     NUWW, 0);
			psb_intew_sdvo_wead_wesponse(encodew, pos, 8);
			pos += 8;
		}
	}
}
#endif

static boow psb_intew_sdvo_set_avi_infofwame(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	DWM_INFO("HDMI is not suppowted yet");

	wetuwn fawse;
}

static boow psb_intew_sdvo_set_tv_fowmat(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	stwuct psb_intew_sdvo_tv_fowmat fowmat;
	uint32_t fowmat_map;

	fowmat_map = 1 << psb_intew_sdvo->tv_fowmat_index;
	memset(&fowmat, 0, sizeof(fowmat));
	memcpy(&fowmat, &fowmat_map, min(sizeof(fowmat), sizeof(fowmat_map)));

	BUIWD_BUG_ON(sizeof(fowmat) != 6);
	wetuwn psb_intew_sdvo_set_vawue(psb_intew_sdvo,
				    SDVO_CMD_SET_TV_FOWMAT,
				    &fowmat, sizeof(fowmat));
}

static boow
psb_intew_sdvo_set_output_timings_fwom_mode(stwuct psb_intew_sdvo *psb_intew_sdvo,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct psb_intew_sdvo_dtd output_dtd;

	if (!psb_intew_sdvo_set_tawget_output(psb_intew_sdvo,
					  psb_intew_sdvo->attached_output))
		wetuwn fawse;

	psb_intew_sdvo_get_dtd_fwom_mode(&output_dtd, mode);
	if (!psb_intew_sdvo_set_output_timing(psb_intew_sdvo, &output_dtd))
		wetuwn fawse;

	wetuwn twue;
}

static boow
psb_intew_sdvo_set_input_timings_fow_mode(stwuct psb_intew_sdvo *psb_intew_sdvo,
					const stwuct dwm_dispway_mode *mode,
					stwuct dwm_dispway_mode *adjusted_mode)
{
	/* Weset the input timing to the scween. Assume awways input 0. */
	if (!psb_intew_sdvo_set_tawget_input(psb_intew_sdvo))
		wetuwn fawse;

	if (!psb_intew_sdvo_cweate_pwefewwed_input_timing(psb_intew_sdvo,
						      mode->cwock / 10,
						      mode->hdispway,
						      mode->vdispway))
		wetuwn fawse;

	if (!psb_intew_sdvo_get_pwefewwed_input_timing(psb_intew_sdvo,
						   &psb_intew_sdvo->input_dtd))
		wetuwn fawse;

	psb_intew_sdvo_get_mode_fwom_dtd(adjusted_mode, &psb_intew_sdvo->input_dtd);

	dwm_mode_set_cwtcinfo(adjusted_mode, 0);
	wetuwn twue;
}

static boow psb_intew_sdvo_mode_fixup(stwuct dwm_encodew *encodew,
				  const stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = to_psb_intew_sdvo(encodew);

	/* We need to constwuct pwefewwed input timings based on ouw
	 * output timings.  To do that, we have to set the output
	 * timings, even though this isn't weawwy the wight pwace in
	 * the sequence to do it. Oh weww.
	 */
	if (psb_intew_sdvo->is_tv) {
		if (!psb_intew_sdvo_set_output_timings_fwom_mode(psb_intew_sdvo, mode))
			wetuwn fawse;

		(void) psb_intew_sdvo_set_input_timings_fow_mode(psb_intew_sdvo,
							     mode,
							     adjusted_mode);
	} ewse if (psb_intew_sdvo->is_wvds) {
		if (!psb_intew_sdvo_set_output_timings_fwom_mode(psb_intew_sdvo,
							     psb_intew_sdvo->sdvo_wvds_fixed_mode))
			wetuwn fawse;

		(void) psb_intew_sdvo_set_input_timings_fow_mode(psb_intew_sdvo,
							     mode,
							     adjusted_mode);
	}

	/* Make the CWTC code factow in the SDVO pixew muwtipwiew.  The
	 * SDVO device wiww factow out the muwtipwiew duwing mode_set.
	 */
	psb_intew_sdvo->pixew_muwtipwiew =
		psb_intew_sdvo_get_pixew_muwtipwiew(adjusted_mode);
	adjusted_mode->cwock *= psb_intew_sdvo->pixew_muwtipwiew;

	wetuwn twue;
}

static void psb_intew_sdvo_mode_set(stwuct dwm_encodew *encodew,
				stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct psb_intew_sdvo *psb_intew_sdvo = to_psb_intew_sdvo(encodew);
	u32 sdvox;
	stwuct psb_intew_sdvo_in_out_map in_out;
	stwuct psb_intew_sdvo_dtd input_dtd;
	int wate;
	int need_aux = IS_MWST(dev) ? 1 : 0;

	if (!mode)
		wetuwn;

	/* Fiwst, set the input mapping fow the fiwst input to ouw contwowwed
	 * output. This is onwy cowwect if we'we a singwe-input device, in
	 * which case the fiwst input is the output fwom the appwopwiate SDVO
	 * channew on the mothewboawd.  In a two-input device, the fiwst input
	 * wiww be SDVOB and the second SDVOC.
	 */
	in_out.in0 = psb_intew_sdvo->attached_output;
	in_out.in1 = 0;

	psb_intew_sdvo_set_vawue(psb_intew_sdvo,
			     SDVO_CMD_SET_IN_OUT_MAP,
			     &in_out, sizeof(in_out));

	/* Set the output timings to the scween */
	if (!psb_intew_sdvo_set_tawget_output(psb_intew_sdvo,
					  psb_intew_sdvo->attached_output))
		wetuwn;

	/* We have twied to get input timing in mode_fixup, and fiwwed into
	 * adjusted_mode.
	 */
	if (psb_intew_sdvo->is_tv || psb_intew_sdvo->is_wvds) {
		input_dtd = psb_intew_sdvo->input_dtd;
	} ewse {
		/* Set the output timing to the scween */
		if (!psb_intew_sdvo_set_tawget_output(psb_intew_sdvo,
						  psb_intew_sdvo->attached_output))
			wetuwn;

		psb_intew_sdvo_get_dtd_fwom_mode(&input_dtd, adjusted_mode);
		(void) psb_intew_sdvo_set_output_timing(psb_intew_sdvo, &input_dtd);
	}

	/* Set the input timing to the scween. Assume awways input 0. */
	if (!psb_intew_sdvo_set_tawget_input(psb_intew_sdvo))
		wetuwn;

	if (psb_intew_sdvo->has_hdmi_monitow) {
		psb_intew_sdvo_set_encode(psb_intew_sdvo, SDVO_ENCODE_HDMI);
		psb_intew_sdvo_set_cowowimetwy(psb_intew_sdvo,
					   SDVO_COWOWIMETWY_WGB256);
		psb_intew_sdvo_set_avi_infofwame(psb_intew_sdvo);
	} ewse
		psb_intew_sdvo_set_encode(psb_intew_sdvo, SDVO_ENCODE_DVI);

	if (psb_intew_sdvo->is_tv &&
	    !psb_intew_sdvo_set_tv_fowmat(psb_intew_sdvo))
		wetuwn;

	(void) psb_intew_sdvo_set_input_timing(psb_intew_sdvo, &input_dtd);

	switch (psb_intew_sdvo->pixew_muwtipwiew) {
	defauwt:
	case 1: wate = SDVO_CWOCK_WATE_MUWT_1X; bweak;
	case 2: wate = SDVO_CWOCK_WATE_MUWT_2X; bweak;
	case 4: wate = SDVO_CWOCK_WATE_MUWT_4X; bweak;
	}
	if (!psb_intew_sdvo_set_cwock_wate_muwt(psb_intew_sdvo, wate))
		wetuwn;

	/* Set the SDVO contwow wegs. */
	if (need_aux)
		sdvox = WEG_WEAD_AUX(psb_intew_sdvo->sdvo_weg);
	ewse
		sdvox = WEG_WEAD(psb_intew_sdvo->sdvo_weg);

	switch (psb_intew_sdvo->sdvo_weg) {
	case SDVOB:
		sdvox &= SDVOB_PWESEWVE_MASK;
		bweak;
	case SDVOC:
		sdvox &= SDVOC_PWESEWVE_MASK;
		bweak;
	}
	sdvox |= (9 << 19) | SDVO_BOWDEW_ENABWE;

	if (gma_cwtc->pipe == 1)
		sdvox |= SDVO_PIPE_B_SEWECT;
	if (psb_intew_sdvo->has_hdmi_audio)
		sdvox |= SDVO_AUDIO_ENABWE;

	/* FIXME: Check if this is needed fow PSB
	sdvox |= (pixew_muwtipwiew - 1) << SDVO_POWT_MUWTIPWY_SHIFT;
	*/

	if (input_dtd.pawt2.sdvo_fwags & SDVO_NEED_TO_STAWW)
		sdvox |= SDVO_STAWW_SEWECT;
	psb_intew_sdvo_wwite_sdvox(psb_intew_sdvo, sdvox);
}

static void psb_intew_sdvo_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct psb_intew_sdvo *psb_intew_sdvo = to_psb_intew_sdvo(encodew);
	u32 temp;
	int i;
	int need_aux = IS_MWST(dev) ? 1 : 0;

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		DWM_DEBUG("DPMS_ON");
		bweak;
	case DWM_MODE_DPMS_OFF:
		DWM_DEBUG("DPMS_OFF");
		bweak;
	defauwt:
		DWM_DEBUG("DPMS: %d", mode);
	}

	if (mode != DWM_MODE_DPMS_ON) {
		psb_intew_sdvo_set_active_outputs(psb_intew_sdvo, 0);
		if (0)
			psb_intew_sdvo_set_encodew_powew_state(psb_intew_sdvo, mode);

		if (mode == DWM_MODE_DPMS_OFF) {
			if (need_aux)
				temp = WEG_WEAD_AUX(psb_intew_sdvo->sdvo_weg);
			ewse
				temp = WEG_WEAD(psb_intew_sdvo->sdvo_weg);

			if ((temp & SDVO_ENABWE) != 0) {
				psb_intew_sdvo_wwite_sdvox(psb_intew_sdvo, temp & ~SDVO_ENABWE);
			}
		}
	} ewse {
		boow input1, input2;
		u8 status;

		if (need_aux)
			temp = WEG_WEAD_AUX(psb_intew_sdvo->sdvo_weg);
		ewse
			temp = WEG_WEAD(psb_intew_sdvo->sdvo_weg);

		if ((temp & SDVO_ENABWE) == 0)
			psb_intew_sdvo_wwite_sdvox(psb_intew_sdvo, temp | SDVO_ENABWE);

		fow (i = 0; i < 2; i++)
			gma_wait_fow_vbwank(dev);

		status = psb_intew_sdvo_get_twained_inputs(psb_intew_sdvo, &input1, &input2);
		/* Wawn if the device wepowted faiwuwe to sync.
		 * A wot of SDVO devices faiw to notify of sync, but it's
		 * a given it the status is a success, we succeeded.
		 */
		if (status == SDVO_CMD_STATUS_SUCCESS && !input1) {
			DWM_DEBUG_KMS("Fiwst %s output wepowted faiwuwe to "
					"sync\n", SDVO_NAME(psb_intew_sdvo));
		}

		if (0)
			psb_intew_sdvo_set_encodew_powew_state(psb_intew_sdvo, mode);
		psb_intew_sdvo_set_active_outputs(psb_intew_sdvo, psb_intew_sdvo->attached_output);
	}
	wetuwn;
}

static enum dwm_mode_status psb_intew_sdvo_mode_vawid(stwuct dwm_connectow *connectow,
				 stwuct dwm_dispway_mode *mode)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	if (psb_intew_sdvo->pixew_cwock_min > mode->cwock)
		wetuwn MODE_CWOCK_WOW;

	if (psb_intew_sdvo->pixew_cwock_max < mode->cwock)
		wetuwn MODE_CWOCK_HIGH;

	if (psb_intew_sdvo->is_wvds) {
		if (mode->hdispway > psb_intew_sdvo->sdvo_wvds_fixed_mode->hdispway)
			wetuwn MODE_PANEW;

		if (mode->vdispway > psb_intew_sdvo->sdvo_wvds_fixed_mode->vdispway)
			wetuwn MODE_PANEW;
	}

	wetuwn MODE_OK;
}

static boow psb_intew_sdvo_get_capabiwities(stwuct psb_intew_sdvo *psb_intew_sdvo, stwuct psb_intew_sdvo_caps *caps)
{
	BUIWD_BUG_ON(sizeof(*caps) != 8);
	if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
				  SDVO_CMD_GET_DEVICE_CAPS,
				  caps, sizeof(*caps)))
		wetuwn fawse;

	DWM_DEBUG_KMS("SDVO capabiwities:\n"
		      "  vendow_id: %d\n"
		      "  device_id: %d\n"
		      "  device_wev_id: %d\n"
		      "  sdvo_vewsion_majow: %d\n"
		      "  sdvo_vewsion_minow: %d\n"
		      "  sdvo_inputs_mask: %d\n"
		      "  smooth_scawing: %d\n"
		      "  shawp_scawing: %d\n"
		      "  up_scawing: %d\n"
		      "  down_scawing: %d\n"
		      "  staww_suppowt: %d\n"
		      "  output_fwags: %d\n",
		      caps->vendow_id,
		      caps->device_id,
		      caps->device_wev_id,
		      caps->sdvo_vewsion_majow,
		      caps->sdvo_vewsion_minow,
		      caps->sdvo_inputs_mask,
		      caps->smooth_scawing,
		      caps->shawp_scawing,
		      caps->up_scawing,
		      caps->down_scawing,
		      caps->staww_suppowt,
		      caps->output_fwags);

	wetuwn twue;
}

static boow
psb_intew_sdvo_muwtifunc_encodew(stwuct psb_intew_sdvo *psb_intew_sdvo)
{
	/* Is thewe mowe than one type of output? */
	int caps = psb_intew_sdvo->caps.output_fwags & 0xf;
	wetuwn caps & -caps;
}

static stwuct edid *
psb_intew_sdvo_get_edid(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo *sdvo = intew_attached_sdvo(connectow);
	wetuwn dwm_get_edid(connectow, &sdvo->ddc);
}

/* Mac mini hack -- use the same DDC as the anawog connectow */
static stwuct edid *
psb_intew_sdvo_get_anawog_edid(stwuct dwm_connectow *connectow)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(connectow->dev);

	wetuwn dwm_get_edid(connectow,
			    &dev_pwiv->gmbus[dev_pwiv->cwt_ddc_pin].adaptew);
}

static enum dwm_connectow_status
psb_intew_sdvo_hdmi_sink_detect(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	enum dwm_connectow_status status;
	stwuct edid *edid;

	edid = psb_intew_sdvo_get_edid(connectow);

	if (edid == NUWW && psb_intew_sdvo_muwtifunc_encodew(psb_intew_sdvo)) {
		u8 ddc, saved_ddc = psb_intew_sdvo->ddc_bus;

		/*
		 * Don't use the 1 as the awgument of DDC bus switch to get
		 * the EDID. It is used fow SDVO SPD WOM.
		 */
		fow (ddc = psb_intew_sdvo->ddc_bus >> 1; ddc > 1; ddc >>= 1) {
			psb_intew_sdvo->ddc_bus = ddc;
			edid = psb_intew_sdvo_get_edid(connectow);
			if (edid)
				bweak;
		}
		/*
		 * If we found the EDID on the othew bus,
		 * assume that is the cowwect DDC bus.
		 */
		if (edid == NUWW)
			psb_intew_sdvo->ddc_bus = saved_ddc;
	}

	/*
	 * When thewe is no edid and no monitow is connected with VGA
	 * powt, twy to use the CWT ddc to wead the EDID fow DVI-connectow.
	 */
	if (edid == NUWW)
		edid = psb_intew_sdvo_get_anawog_edid(connectow);

	status = connectow_status_unknown;
	if (edid != NUWW) {
		/* DDC bus is shawed, match EDID to connectow type */
		if (edid->input & DWM_EDID_INPUT_DIGITAW) {
			status = connectow_status_connected;
			if (psb_intew_sdvo->is_hdmi) {
				psb_intew_sdvo->has_hdmi_monitow = dwm_detect_hdmi_monitow(edid);
				psb_intew_sdvo->has_hdmi_audio = dwm_detect_monitow_audio(edid);
			}
		} ewse
			status = connectow_status_disconnected;
		kfwee(edid);
	}

	if (status == connectow_status_connected) {
		stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow = to_psb_intew_sdvo_connectow(connectow);
		if (psb_intew_sdvo_connectow->fowce_audio)
			psb_intew_sdvo->has_hdmi_audio = psb_intew_sdvo_connectow->fowce_audio > 0;
	}

	wetuwn status;
}

static enum dwm_connectow_status
psb_intew_sdvo_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	uint16_t wesponse;
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow = to_psb_intew_sdvo_connectow(connectow);
	enum dwm_connectow_status wet;

	if (!psb_intew_sdvo_wwite_cmd(psb_intew_sdvo,
				  SDVO_CMD_GET_ATTACHED_DISPWAYS, NUWW, 0))
		wetuwn connectow_status_unknown;

	/* add 30ms deway when the output type might be TV */
	if (psb_intew_sdvo->caps.output_fwags &
	    (SDVO_OUTPUT_SVID0 | SDVO_OUTPUT_CVBS0))
		mdeway(30);

	if (!psb_intew_sdvo_wead_wesponse(psb_intew_sdvo, &wesponse, 2))
		wetuwn connectow_status_unknown;

	DWM_DEBUG_KMS("SDVO wesponse %d %d [%x]\n",
		      wesponse & 0xff, wesponse >> 8,
		      psb_intew_sdvo_connectow->output_fwag);

	if (wesponse == 0)
		wetuwn connectow_status_disconnected;

	psb_intew_sdvo->attached_output = wesponse;

	psb_intew_sdvo->has_hdmi_monitow = fawse;
	psb_intew_sdvo->has_hdmi_audio = fawse;

	if ((psb_intew_sdvo_connectow->output_fwag & wesponse) == 0)
		wet = connectow_status_disconnected;
	ewse if (IS_TMDS(psb_intew_sdvo_connectow))
		wet = psb_intew_sdvo_hdmi_sink_detect(connectow);
	ewse {
		stwuct edid *edid;

		/* if we have an edid check it matches the connection */
		edid = psb_intew_sdvo_get_edid(connectow);
		if (edid == NUWW)
			edid = psb_intew_sdvo_get_anawog_edid(connectow);
		if (edid != NUWW) {
			if (edid->input & DWM_EDID_INPUT_DIGITAW)
				wet = connectow_status_disconnected;
			ewse
				wet = connectow_status_connected;
			kfwee(edid);
		} ewse
			wet = connectow_status_connected;
	}

	/* May update encodew fwag fow wike cwock fow SDVO TV, etc.*/
	if (wet == connectow_status_connected) {
		psb_intew_sdvo->is_tv = fawse;
		psb_intew_sdvo->is_wvds = fawse;
		psb_intew_sdvo->base.needs_tv_cwock = fawse;

		if (wesponse & SDVO_TV_MASK) {
			psb_intew_sdvo->is_tv = twue;
			psb_intew_sdvo->base.needs_tv_cwock = twue;
		}
		if (wesponse & SDVO_WVDS_MASK)
			psb_intew_sdvo->is_wvds = psb_intew_sdvo->sdvo_wvds_fixed_mode != NUWW;
	}

	wetuwn wet;
}

static void psb_intew_sdvo_get_ddc_modes(stwuct dwm_connectow *connectow)
{
	stwuct edid *edid;

	/* set the bus switch and get the modes */
	edid = psb_intew_sdvo_get_edid(connectow);

	/*
	 * Mac mini hack.  On this device, the DVI-I connectow shawes one DDC
	 * wink between anawog and digitaw outputs. So, if the weguwaw SDVO
	 * DDC faiws, check to see if the anawog output is disconnected, in
	 * which case we'ww wook thewe fow the digitaw DDC data.
	 */
	if (edid == NUWW)
		edid = psb_intew_sdvo_get_anawog_edid(connectow);

	if (edid != NUWW) {
		stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow = to_psb_intew_sdvo_connectow(connectow);
		boow monitow_is_digitaw = !!(edid->input & DWM_EDID_INPUT_DIGITAW);
		boow connectow_is_digitaw = !!IS_TMDS(psb_intew_sdvo_connectow);

		if (connectow_is_digitaw == monitow_is_digitaw) {
			dwm_connectow_update_edid_pwopewty(connectow, edid);
			dwm_add_edid_modes(connectow, edid);
		}

		kfwee(edid);
	}
}

/*
 * Set of SDVO TV modes.
 * Note!  This is in wepwy owdew (see woop in get_tv_modes).
 * XXX: aww 60Hz wefwesh?
 */
static const stwuct dwm_dispway_mode sdvo_tv_modes[] = {
	{ DWM_MODE("320x200", DWM_MODE_TYPE_DWIVEW, 5815, 320, 321, 384,
		   416, 0, 200, 201, 232, 233, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("320x240", DWM_MODE_TYPE_DWIVEW, 6814, 320, 321, 384,
		   416, 0, 240, 241, 272, 273, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("400x300", DWM_MODE_TYPE_DWIVEW, 9910, 400, 401, 464,
		   496, 0, 300, 301, 332, 333, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("640x350", DWM_MODE_TYPE_DWIVEW, 16913, 640, 641, 704,
		   736, 0, 350, 351, 382, 383, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("640x400", DWM_MODE_TYPE_DWIVEW, 19121, 640, 641, 704,
		   736, 0, 400, 401, 432, 433, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("640x480", DWM_MODE_TYPE_DWIVEW, 22654, 640, 641, 704,
		   736, 0, 480, 481, 512, 513, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("704x480", DWM_MODE_TYPE_DWIVEW, 24624, 704, 705, 768,
		   800, 0, 480, 481, 512, 513, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("704x576", DWM_MODE_TYPE_DWIVEW, 29232, 704, 705, 768,
		   800, 0, 576, 577, 608, 609, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("720x350", DWM_MODE_TYPE_DWIVEW, 18751, 720, 721, 784,
		   816, 0, 350, 351, 382, 383, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("720x400", DWM_MODE_TYPE_DWIVEW, 21199, 720, 721, 784,
		   816, 0, 400, 401, 432, 433, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("720x480", DWM_MODE_TYPE_DWIVEW, 25116, 720, 721, 784,
		   816, 0, 480, 481, 512, 513, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("720x540", DWM_MODE_TYPE_DWIVEW, 28054, 720, 721, 784,
		   816, 0, 540, 541, 572, 573, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("720x576", DWM_MODE_TYPE_DWIVEW, 29816, 720, 721, 784,
		   816, 0, 576, 577, 608, 609, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("768x576", DWM_MODE_TYPE_DWIVEW, 31570, 768, 769, 832,
		   864, 0, 576, 577, 608, 609, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("800x600", DWM_MODE_TYPE_DWIVEW, 34030, 800, 801, 864,
		   896, 0, 600, 601, 632, 633, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("832x624", DWM_MODE_TYPE_DWIVEW, 36581, 832, 833, 896,
		   928, 0, 624, 625, 656, 657, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("920x766", DWM_MODE_TYPE_DWIVEW, 48707, 920, 921, 984,
		   1016, 0, 766, 767, 798, 799, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("1024x768", DWM_MODE_TYPE_DWIVEW, 53827, 1024, 1025, 1088,
		   1120, 0, 768, 769, 800, 801, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("1280x1024", DWM_MODE_TYPE_DWIVEW, 87265, 1280, 1281, 1344,
		   1376, 0, 1024, 1025, 1056, 1057, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
};

static void psb_intew_sdvo_get_tv_modes(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	stwuct psb_intew_sdvo_sdtv_wesowution_wequest tv_wes;
	uint32_t wepwy = 0, fowmat_map = 0;
	int i;

	/* Wead the wist of suppowted input wesowutions fow the sewected TV
	 * fowmat.
	 */
	fowmat_map = 1 << psb_intew_sdvo->tv_fowmat_index;
	memcpy(&tv_wes, &fowmat_map,
	       min(sizeof(fowmat_map), sizeof(stwuct psb_intew_sdvo_sdtv_wesowution_wequest)));

	if (!psb_intew_sdvo_set_tawget_output(psb_intew_sdvo, psb_intew_sdvo->attached_output))
		wetuwn;

	BUIWD_BUG_ON(sizeof(tv_wes) != 3);
	if (!psb_intew_sdvo_wwite_cmd(psb_intew_sdvo,
				  SDVO_CMD_GET_SDTV_WESOWUTION_SUPPOWT,
				  &tv_wes, sizeof(tv_wes)))
		wetuwn;
	if (!psb_intew_sdvo_wead_wesponse(psb_intew_sdvo, &wepwy, 3))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(sdvo_tv_modes); i++)
		if (wepwy & (1 << i)) {
			stwuct dwm_dispway_mode *nmode;
			nmode = dwm_mode_dupwicate(connectow->dev,
						   &sdvo_tv_modes[i]);
			if (nmode)
				dwm_mode_pwobed_add(connectow, nmode);
		}
}

static void psb_intew_sdvo_get_wvds_modes(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(connectow->dev);
	stwuct dwm_dispway_mode *newmode;

	/*
	 * Attempt to get the mode wist fwom DDC.
	 * Assume that the pwefewwed modes awe
	 * awwanged in pwiowity owdew.
	 */
	psb_intew_ddc_get_modes(connectow, psb_intew_sdvo->i2c);
	if (wist_empty(&connectow->pwobed_modes) == fawse)
		goto end;

	/* Fetch modes fwom VBT */
	if (dev_pwiv->sdvo_wvds_vbt_mode != NUWW) {
		newmode = dwm_mode_dupwicate(connectow->dev,
					     dev_pwiv->sdvo_wvds_vbt_mode);
		if (newmode != NUWW) {
			/* Guawantee the mode is pwefewwed */
			newmode->type = (DWM_MODE_TYPE_PWEFEWWED |
					 DWM_MODE_TYPE_DWIVEW);
			dwm_mode_pwobed_add(connectow, newmode);
		}
	}

end:
	wist_fow_each_entwy(newmode, &connectow->pwobed_modes, head) {
		if (newmode->type & DWM_MODE_TYPE_PWEFEWWED) {
			psb_intew_sdvo->sdvo_wvds_fixed_mode =
				dwm_mode_dupwicate(connectow->dev, newmode);

			dwm_mode_set_cwtcinfo(psb_intew_sdvo->sdvo_wvds_fixed_mode,
					      0);

			psb_intew_sdvo->is_wvds = twue;
			bweak;
		}
	}

}

static int psb_intew_sdvo_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow = to_psb_intew_sdvo_connectow(connectow);

	if (IS_TV(psb_intew_sdvo_connectow))
		psb_intew_sdvo_get_tv_modes(connectow);
	ewse if (IS_WVDS(psb_intew_sdvo_connectow))
		psb_intew_sdvo_get_wvds_modes(connectow);
	ewse
		psb_intew_sdvo_get_ddc_modes(connectow);

	wetuwn !wist_empty(&connectow->pwobed_modes);
}

static void psb_intew_sdvo_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct gma_connectow *gma_connectow = to_gma_connectow(connectow);

	dwm_connectow_cweanup(connectow);
	kfwee(gma_connectow);
}

static boow psb_intew_sdvo_detect_hdmi_audio(stwuct dwm_connectow *connectow)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	stwuct edid *edid;
	boow has_audio = fawse;

	if (!psb_intew_sdvo->is_hdmi)
		wetuwn fawse;

	edid = psb_intew_sdvo_get_edid(connectow);
	if (edid != NUWW && edid->input & DWM_EDID_INPUT_DIGITAW)
		has_audio = dwm_detect_monitow_audio(edid);

	wetuwn has_audio;
}

static int
psb_intew_sdvo_set_pwopewty(stwuct dwm_connectow *connectow,
			stwuct dwm_pwopewty *pwopewty,
			uint64_t vaw)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = intew_attached_sdvo(connectow);
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow = to_psb_intew_sdvo_connectow(connectow);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(connectow->dev);
	uint16_t temp_vawue;
	uint8_t cmd;
	int wet;

	wet = dwm_object_pwopewty_set_vawue(&connectow->base, pwopewty, vaw);
	if (wet)
		wetuwn wet;

	if (pwopewty == dev_pwiv->fowce_audio_pwopewty) {
		int i = vaw;
		boow has_audio;

		if (i == psb_intew_sdvo_connectow->fowce_audio)
			wetuwn 0;

		psb_intew_sdvo_connectow->fowce_audio = i;

		if (i == 0)
			has_audio = psb_intew_sdvo_detect_hdmi_audio(connectow);
		ewse
			has_audio = i > 0;

		if (has_audio == psb_intew_sdvo->has_hdmi_audio)
			wetuwn 0;

		psb_intew_sdvo->has_hdmi_audio = has_audio;
		goto done;
	}

	if (pwopewty == dev_pwiv->bwoadcast_wgb_pwopewty) {
		if (vaw == !!psb_intew_sdvo->cowow_wange)
			wetuwn 0;

		psb_intew_sdvo->cowow_wange = vaw ? SDVO_COWOW_WANGE_16_235 : 0;
		goto done;
	}

#define CHECK_PWOPEWTY(name, NAME) \
	if (psb_intew_sdvo_connectow->name == pwopewty) { \
		if (psb_intew_sdvo_connectow->cuw_##name == temp_vawue) wetuwn 0; \
		if (psb_intew_sdvo_connectow->max_##name < temp_vawue) wetuwn -EINVAW; \
		cmd = SDVO_CMD_SET_##NAME; \
		psb_intew_sdvo_connectow->cuw_##name = temp_vawue; \
		goto set_vawue; \
	}

	if (pwopewty == psb_intew_sdvo_connectow->tv_fowmat) {
		if (vaw >= AWWAY_SIZE(tv_fowmat_names))
			wetuwn -EINVAW;

		if (psb_intew_sdvo->tv_fowmat_index ==
		    psb_intew_sdvo_connectow->tv_fowmat_suppowted[vaw])
			wetuwn 0;

		psb_intew_sdvo->tv_fowmat_index = psb_intew_sdvo_connectow->tv_fowmat_suppowted[vaw];
		goto done;
	} ewse if (IS_TV_OW_WVDS(psb_intew_sdvo_connectow)) {
		temp_vawue = vaw;
		if (psb_intew_sdvo_connectow->weft == pwopewty) {
			dwm_object_pwopewty_set_vawue(&connectow->base,
							 psb_intew_sdvo_connectow->wight, vaw);
			if (psb_intew_sdvo_connectow->weft_mawgin == temp_vawue)
				wetuwn 0;

			psb_intew_sdvo_connectow->weft_mawgin = temp_vawue;
			psb_intew_sdvo_connectow->wight_mawgin = temp_vawue;
			temp_vawue = psb_intew_sdvo_connectow->max_hscan -
				psb_intew_sdvo_connectow->weft_mawgin;
			cmd = SDVO_CMD_SET_OVEWSCAN_H;
			goto set_vawue;
		} ewse if (psb_intew_sdvo_connectow->wight == pwopewty) {
			dwm_object_pwopewty_set_vawue(&connectow->base,
							 psb_intew_sdvo_connectow->weft, vaw);
			if (psb_intew_sdvo_connectow->wight_mawgin == temp_vawue)
				wetuwn 0;

			psb_intew_sdvo_connectow->weft_mawgin = temp_vawue;
			psb_intew_sdvo_connectow->wight_mawgin = temp_vawue;
			temp_vawue = psb_intew_sdvo_connectow->max_hscan -
				psb_intew_sdvo_connectow->weft_mawgin;
			cmd = SDVO_CMD_SET_OVEWSCAN_H;
			goto set_vawue;
		} ewse if (psb_intew_sdvo_connectow->top == pwopewty) {
			dwm_object_pwopewty_set_vawue(&connectow->base,
							 psb_intew_sdvo_connectow->bottom, vaw);
			if (psb_intew_sdvo_connectow->top_mawgin == temp_vawue)
				wetuwn 0;

			psb_intew_sdvo_connectow->top_mawgin = temp_vawue;
			psb_intew_sdvo_connectow->bottom_mawgin = temp_vawue;
			temp_vawue = psb_intew_sdvo_connectow->max_vscan -
				psb_intew_sdvo_connectow->top_mawgin;
			cmd = SDVO_CMD_SET_OVEWSCAN_V;
			goto set_vawue;
		} ewse if (psb_intew_sdvo_connectow->bottom == pwopewty) {
			dwm_object_pwopewty_set_vawue(&connectow->base,
							 psb_intew_sdvo_connectow->top, vaw);
			if (psb_intew_sdvo_connectow->bottom_mawgin == temp_vawue)
				wetuwn 0;

			psb_intew_sdvo_connectow->top_mawgin = temp_vawue;
			psb_intew_sdvo_connectow->bottom_mawgin = temp_vawue;
			temp_vawue = psb_intew_sdvo_connectow->max_vscan -
				psb_intew_sdvo_connectow->top_mawgin;
			cmd = SDVO_CMD_SET_OVEWSCAN_V;
			goto set_vawue;
		}
		CHECK_PWOPEWTY(hpos, HPOS)
		CHECK_PWOPEWTY(vpos, VPOS)
		CHECK_PWOPEWTY(satuwation, SATUWATION)
		CHECK_PWOPEWTY(contwast, CONTWAST)
		CHECK_PWOPEWTY(hue, HUE)
		CHECK_PWOPEWTY(bwightness, BWIGHTNESS)
		CHECK_PWOPEWTY(shawpness, SHAWPNESS)
		CHECK_PWOPEWTY(fwickew_fiwtew, FWICKEW_FIWTEW)
		CHECK_PWOPEWTY(fwickew_fiwtew_2d, FWICKEW_FIWTEW_2D)
		CHECK_PWOPEWTY(fwickew_fiwtew_adaptive, FWICKEW_FIWTEW_ADAPTIVE)
		CHECK_PWOPEWTY(tv_chwoma_fiwtew, TV_CHWOMA_FIWTEW)
		CHECK_PWOPEWTY(tv_wuma_fiwtew, TV_WUMA_FIWTEW)
		CHECK_PWOPEWTY(dot_cwaww, DOT_CWAWW)
	}

	wetuwn -EINVAW; /* unknown pwopewty */

set_vawue:
	if (!psb_intew_sdvo_set_vawue(psb_intew_sdvo, cmd, &temp_vawue, 2))
		wetuwn -EIO;


done:
	if (psb_intew_sdvo->base.base.cwtc) {
		stwuct dwm_cwtc *cwtc = psb_intew_sdvo->base.base.cwtc;
		dwm_cwtc_hewpew_set_mode(cwtc, &cwtc->mode, cwtc->x,
					 cwtc->y, cwtc->pwimawy->fb);
	}

	wetuwn 0;
#undef CHECK_PWOPEWTY
}

static void psb_intew_sdvo_save(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);
	stwuct psb_intew_sdvo *sdvo = to_psb_intew_sdvo(&gma_encodew->base);

	sdvo->saveSDVO = WEG_WEAD(sdvo->sdvo_weg);
}

static void psb_intew_sdvo_westowe(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_encodew *encodew = &gma_attached_encodew(connectow)->base;
	stwuct psb_intew_sdvo *sdvo = to_psb_intew_sdvo(encodew);
	stwuct dwm_cwtc *cwtc = encodew->cwtc;

	WEG_WWITE(sdvo->sdvo_weg, sdvo->saveSDVO);

	/* Fowce a fuww mode set on the cwtc. We'we supposed to have the
	   mode_config wock awweady. */
	if (connectow->status == connectow_status_connected)
		dwm_cwtc_hewpew_set_mode(cwtc, &cwtc->mode, cwtc->x, cwtc->y,
					 NUWW);
}

static const stwuct dwm_encodew_hewpew_funcs psb_intew_sdvo_hewpew_funcs = {
	.dpms = psb_intew_sdvo_dpms,
	.mode_fixup = psb_intew_sdvo_mode_fixup,
	.pwepawe = gma_encodew_pwepawe,
	.mode_set = psb_intew_sdvo_mode_set,
	.commit = gma_encodew_commit,
};

static const stwuct dwm_connectow_funcs psb_intew_sdvo_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = psb_intew_sdvo_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = psb_intew_sdvo_set_pwopewty,
	.destwoy = psb_intew_sdvo_destwoy,
};

static const stwuct dwm_connectow_hewpew_funcs psb_intew_sdvo_connectow_hewpew_funcs = {
	.get_modes = psb_intew_sdvo_get_modes,
	.mode_vawid = psb_intew_sdvo_mode_vawid,
	.best_encodew = gma_best_encodew,
};

static void psb_intew_sdvo_enc_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct psb_intew_sdvo *psb_intew_sdvo = to_psb_intew_sdvo(encodew);

	if (psb_intew_sdvo->sdvo_wvds_fixed_mode != NUWW)
		dwm_mode_destwoy(encodew->dev,
				 psb_intew_sdvo->sdvo_wvds_fixed_mode);

	i2c_dew_adaptew(&psb_intew_sdvo->ddc);
	gma_encodew_destwoy(encodew);
}

static const stwuct dwm_encodew_funcs psb_intew_sdvo_enc_funcs = {
	.destwoy = psb_intew_sdvo_enc_destwoy,
};

static void
psb_intew_sdvo_guess_ddc_bus(stwuct psb_intew_sdvo *sdvo)
{
	/* FIXME: At the moment, ddc_bus = 2 is the onwy thing that wowks.
	 * We need to figuwe out if this is twue fow aww avaiwabwe pouwsbo
	 * hawdwawe, ow if we need to fiddwe with the guessing code above.
	 * The pwobwem might go away if we can pawse sdvo mappings fwom bios */
	sdvo->ddc_bus = 2;

#if 0
	uint16_t mask = 0;
	unsigned int num_bits;

	/* Make a mask of outputs wess than ow equaw to ouw own pwiowity in the
	 * wist.
	 */
	switch (sdvo->contwowwed_output) {
	case SDVO_OUTPUT_WVDS1:
		mask |= SDVO_OUTPUT_WVDS1;
	case SDVO_OUTPUT_WVDS0:
		mask |= SDVO_OUTPUT_WVDS0;
	case SDVO_OUTPUT_TMDS1:
		mask |= SDVO_OUTPUT_TMDS1;
	case SDVO_OUTPUT_TMDS0:
		mask |= SDVO_OUTPUT_TMDS0;
	case SDVO_OUTPUT_WGB1:
		mask |= SDVO_OUTPUT_WGB1;
	case SDVO_OUTPUT_WGB0:
		mask |= SDVO_OUTPUT_WGB0;
		bweak;
	}

	/* Count bits to find what numbew we awe in the pwiowity wist. */
	mask &= sdvo->caps.output_fwags;
	num_bits = hweight16(mask);
	/* If mowe than 3 outputs, defauwt to DDC bus 3 fow now. */
	if (num_bits > 3)
		num_bits = 3;

	/* Cowwesponds to SDVO_CONTWOW_BUS_DDCx */
	sdvo->ddc_bus = 1 << num_bits;
#endif
}

/*
 * Choose the appwopwiate DDC bus fow contwow bus switch command fow this
 * SDVO output based on the contwowwed output.
 *
 * DDC bus numbew assignment is in a pwiowity owdew of WGB outputs, then TMDS
 * outputs, then WVDS outputs.
 */
static void
psb_intew_sdvo_sewect_ddc_bus(stwuct dwm_psb_pwivate *dev_pwiv,
			  stwuct psb_intew_sdvo *sdvo, u32 weg)
{
	stwuct sdvo_device_mapping *mapping;

	if (IS_SDVOB(weg))
		mapping = &(dev_pwiv->sdvo_mappings[0]);
	ewse
		mapping = &(dev_pwiv->sdvo_mappings[1]);

	if (mapping->initiawized)
		sdvo->ddc_bus = 1 << ((mapping->ddc_pin & 0xf0) >> 4);
	ewse
		psb_intew_sdvo_guess_ddc_bus(sdvo);
}

static void
psb_intew_sdvo_sewect_i2c_bus(stwuct dwm_psb_pwivate *dev_pwiv,
			  stwuct psb_intew_sdvo *sdvo, u32 weg)
{
	stwuct sdvo_device_mapping *mapping;
	u8 pin, speed;

	if (IS_SDVOB(weg))
		mapping = &dev_pwiv->sdvo_mappings[0];
	ewse
		mapping = &dev_pwiv->sdvo_mappings[1];

	pin = GMBUS_POWT_DPB;
	speed = GMBUS_WATE_1MHZ >> 8;
	if (mapping->initiawized) {
		pin = mapping->i2c_pin;
		speed = mapping->i2c_speed;
	}

	if (pin < GMBUS_NUM_POWTS) {
		sdvo->i2c = &dev_pwiv->gmbus[pin].adaptew;
		gma_intew_gmbus_set_speed(sdvo->i2c, speed);
		gma_intew_gmbus_fowce_bit(sdvo->i2c, twue);
	} ewse
		sdvo->i2c = &dev_pwiv->gmbus[GMBUS_POWT_DPB].adaptew;
}

static boow
psb_intew_sdvo_is_hdmi_connectow(stwuct psb_intew_sdvo *psb_intew_sdvo, int device)
{
	wetuwn psb_intew_sdvo_check_supp_encode(psb_intew_sdvo);
}

static u8
psb_intew_sdvo_get_swave_addw(stwuct dwm_device *dev, int sdvo_weg)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct sdvo_device_mapping *my_mapping, *othew_mapping;

	if (IS_SDVOB(sdvo_weg)) {
		my_mapping = &dev_pwiv->sdvo_mappings[0];
		othew_mapping = &dev_pwiv->sdvo_mappings[1];
	} ewse {
		my_mapping = &dev_pwiv->sdvo_mappings[1];
		othew_mapping = &dev_pwiv->sdvo_mappings[0];
	}

	/* If the BIOS descwibed ouw SDVO device, take advantage of it. */
	if (my_mapping->swave_addw)
		wetuwn my_mapping->swave_addw;

	/* If the BIOS onwy descwibed a diffewent SDVO device, use the
	 * addwess that it isn't using.
	 */
	if (othew_mapping->swave_addw) {
		if (othew_mapping->swave_addw == 0x70)
			wetuwn 0x72;
		ewse
			wetuwn 0x70;
	}

	/* No SDVO device info is found fow anothew DVO powt,
	 * so use mapping assumption we had befowe BIOS pawsing.
	 */
	if (IS_SDVOB(sdvo_weg))
		wetuwn 0x70;
	ewse
		wetuwn 0x72;
}

static void
psb_intew_sdvo_connectow_init(stwuct psb_intew_sdvo_connectow *connectow,
			  stwuct psb_intew_sdvo *encodew)
{
	dwm_connectow_init(encodew->base.base.dev,
			   &connectow->base.base,
			   &psb_intew_sdvo_connectow_funcs,
			   connectow->base.base.connectow_type);

	dwm_connectow_hewpew_add(&connectow->base.base,
				 &psb_intew_sdvo_connectow_hewpew_funcs);

	connectow->base.base.intewwace_awwowed = 0;
	connectow->base.base.doubwescan_awwowed = 0;
	connectow->base.base.dispway_info.subpixew_owdew = SubPixewHowizontawWGB;

	connectow->base.save = psb_intew_sdvo_save;
	connectow->base.westowe = psb_intew_sdvo_westowe;

	gma_connectow_attach_encodew(&connectow->base, &encodew->base);
}

static void
psb_intew_sdvo_add_hdmi_pwopewties(stwuct psb_intew_sdvo_connectow *connectow)
{
	/* FIXME: We don't suppowt HDMI at the moment
	stwuct dwm_device *dev = connectow->base.base.dev;

	intew_attach_fowce_audio_pwopewty(&connectow->base.base);
	intew_attach_bwoadcast_wgb_pwopewty(&connectow->base.base);
	*/
}

static boow
psb_intew_sdvo_dvi_init(stwuct psb_intew_sdvo *psb_intew_sdvo, int device)
{
	stwuct dwm_encodew *encodew = &psb_intew_sdvo->base.base;
	stwuct dwm_connectow *connectow;
	stwuct gma_connectow *intew_connectow;
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow;

	psb_intew_sdvo_connectow = kzawwoc(sizeof(stwuct psb_intew_sdvo_connectow), GFP_KEWNEW);
	if (!psb_intew_sdvo_connectow)
		wetuwn fawse;

	if (device == 0) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_TMDS0;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_TMDS0;
	} ewse if (device == 1) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_TMDS1;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_TMDS1;
	}

	intew_connectow = &psb_intew_sdvo_connectow->base;
	connectow = &intew_connectow->base;
	// connectow->powwed = DWM_CONNECTOW_POWW_CONNECT | DWM_CONNECTOW_POWW_DISCONNECT;
	encodew->encodew_type = DWM_MODE_ENCODEW_TMDS;
	connectow->connectow_type = DWM_MODE_CONNECTOW_DVID;

	if (psb_intew_sdvo_is_hdmi_connectow(psb_intew_sdvo, device)) {
		connectow->connectow_type = DWM_MODE_CONNECTOW_HDMIA;
		psb_intew_sdvo->is_hdmi = twue;
	}
	psb_intew_sdvo->base.cwone_mask = ((1 << INTEW_SDVO_NON_TV_CWONE_BIT) |
				       (1 << INTEW_ANAWOG_CWONE_BIT));

	psb_intew_sdvo_connectow_init(psb_intew_sdvo_connectow, psb_intew_sdvo);
	if (psb_intew_sdvo->is_hdmi)
		psb_intew_sdvo_add_hdmi_pwopewties(psb_intew_sdvo_connectow);

	wetuwn twue;
}

static boow
psb_intew_sdvo_tv_init(stwuct psb_intew_sdvo *psb_intew_sdvo, int type)
{
	stwuct dwm_encodew *encodew = &psb_intew_sdvo->base.base;
	stwuct dwm_connectow *connectow;
	stwuct gma_connectow *intew_connectow;
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow;

	psb_intew_sdvo_connectow = kzawwoc(sizeof(stwuct psb_intew_sdvo_connectow), GFP_KEWNEW);
	if (!psb_intew_sdvo_connectow)
		wetuwn fawse;

	intew_connectow = &psb_intew_sdvo_connectow->base;
	connectow = &intew_connectow->base;
	encodew->encodew_type = DWM_MODE_ENCODEW_TVDAC;
	connectow->connectow_type = DWM_MODE_CONNECTOW_SVIDEO;

	psb_intew_sdvo->contwowwed_output |= type;
	psb_intew_sdvo_connectow->output_fwag = type;

	psb_intew_sdvo->is_tv = twue;
	psb_intew_sdvo->base.needs_tv_cwock = twue;
	psb_intew_sdvo->base.cwone_mask = 1 << INTEW_SDVO_TV_CWONE_BIT;

	psb_intew_sdvo_connectow_init(psb_intew_sdvo_connectow, psb_intew_sdvo);

	if (!psb_intew_sdvo_tv_cweate_pwopewty(psb_intew_sdvo, psb_intew_sdvo_connectow, type))
		goto eww;

	if (!psb_intew_sdvo_cweate_enhance_pwopewty(psb_intew_sdvo, psb_intew_sdvo_connectow))
		goto eww;

	wetuwn twue;

eww:
	psb_intew_sdvo_destwoy(connectow);
	wetuwn fawse;
}

static boow
psb_intew_sdvo_anawog_init(stwuct psb_intew_sdvo *psb_intew_sdvo, int device)
{
	stwuct dwm_encodew *encodew = &psb_intew_sdvo->base.base;
	stwuct dwm_connectow *connectow;
	stwuct gma_connectow *intew_connectow;
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow;

	psb_intew_sdvo_connectow = kzawwoc(sizeof(stwuct psb_intew_sdvo_connectow), GFP_KEWNEW);
	if (!psb_intew_sdvo_connectow)
		wetuwn fawse;

	intew_connectow = &psb_intew_sdvo_connectow->base;
	connectow = &intew_connectow->base;
	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;
	encodew->encodew_type = DWM_MODE_ENCODEW_DAC;
	connectow->connectow_type = DWM_MODE_CONNECTOW_VGA;

	if (device == 0) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_WGB0;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_WGB0;
	} ewse if (device == 1) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_WGB1;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_WGB1;
	}

	psb_intew_sdvo->base.cwone_mask = ((1 << INTEW_SDVO_NON_TV_CWONE_BIT) |
				       (1 << INTEW_ANAWOG_CWONE_BIT));

	psb_intew_sdvo_connectow_init(psb_intew_sdvo_connectow,
				  psb_intew_sdvo);
	wetuwn twue;
}

static boow
psb_intew_sdvo_wvds_init(stwuct psb_intew_sdvo *psb_intew_sdvo, int device)
{
	stwuct dwm_encodew *encodew = &psb_intew_sdvo->base.base;
	stwuct dwm_connectow *connectow;
	stwuct gma_connectow *intew_connectow;
	stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow;

	psb_intew_sdvo_connectow = kzawwoc(sizeof(stwuct psb_intew_sdvo_connectow), GFP_KEWNEW);
	if (!psb_intew_sdvo_connectow)
		wetuwn fawse;

	intew_connectow = &psb_intew_sdvo_connectow->base;
	connectow = &intew_connectow->base;
	encodew->encodew_type = DWM_MODE_ENCODEW_WVDS;
	connectow->connectow_type = DWM_MODE_CONNECTOW_WVDS;

	if (device == 0) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_WVDS0;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_WVDS0;
	} ewse if (device == 1) {
		psb_intew_sdvo->contwowwed_output |= SDVO_OUTPUT_WVDS1;
		psb_intew_sdvo_connectow->output_fwag = SDVO_OUTPUT_WVDS1;
	}

	psb_intew_sdvo->base.cwone_mask = ((1 << INTEW_ANAWOG_CWONE_BIT) |
				       (1 << INTEW_SDVO_WVDS_CWONE_BIT));

	psb_intew_sdvo_connectow_init(psb_intew_sdvo_connectow, psb_intew_sdvo);
	if (!psb_intew_sdvo_cweate_enhance_pwopewty(psb_intew_sdvo, psb_intew_sdvo_connectow))
		goto eww;

	wetuwn twue;

eww:
	psb_intew_sdvo_destwoy(connectow);
	wetuwn fawse;
}

static boow
psb_intew_sdvo_output_setup(stwuct psb_intew_sdvo *psb_intew_sdvo, uint16_t fwags)
{
	psb_intew_sdvo->is_tv = fawse;
	psb_intew_sdvo->base.needs_tv_cwock = fawse;
	psb_intew_sdvo->is_wvds = fawse;

	/* SDVO wequiwes XXX1 function may not exist unwess it has XXX0 function.*/

	if (fwags & SDVO_OUTPUT_TMDS0)
		if (!psb_intew_sdvo_dvi_init(psb_intew_sdvo, 0))
			wetuwn fawse;

	if ((fwags & SDVO_TMDS_MASK) == SDVO_TMDS_MASK)
		if (!psb_intew_sdvo_dvi_init(psb_intew_sdvo, 1))
			wetuwn fawse;

	/* TV has no XXX1 function bwock */
	if (fwags & SDVO_OUTPUT_SVID0)
		if (!psb_intew_sdvo_tv_init(psb_intew_sdvo, SDVO_OUTPUT_SVID0))
			wetuwn fawse;

	if (fwags & SDVO_OUTPUT_CVBS0)
		if (!psb_intew_sdvo_tv_init(psb_intew_sdvo, SDVO_OUTPUT_CVBS0))
			wetuwn fawse;

	if (fwags & SDVO_OUTPUT_WGB0)
		if (!psb_intew_sdvo_anawog_init(psb_intew_sdvo, 0))
			wetuwn fawse;

	if ((fwags & SDVO_WGB_MASK) == SDVO_WGB_MASK)
		if (!psb_intew_sdvo_anawog_init(psb_intew_sdvo, 1))
			wetuwn fawse;

	if (fwags & SDVO_OUTPUT_WVDS0)
		if (!psb_intew_sdvo_wvds_init(psb_intew_sdvo, 0))
			wetuwn fawse;

	if ((fwags & SDVO_WVDS_MASK) == SDVO_WVDS_MASK)
		if (!psb_intew_sdvo_wvds_init(psb_intew_sdvo, 1))
			wetuwn fawse;

	if ((fwags & SDVO_OUTPUT_MASK) == 0) {
		unsigned chaw bytes[2];

		psb_intew_sdvo->contwowwed_output = 0;
		memcpy(bytes, &psb_intew_sdvo->caps.output_fwags, 2);
		DWM_DEBUG_KMS("%s: Unknown SDVO output type (0x%02x%02x)\n",
			      SDVO_NAME(psb_intew_sdvo),
			      bytes[0], bytes[1]);
		wetuwn fawse;
	}
	psb_intew_sdvo->base.cwtc_mask = (1 << 0) | (1 << 1);

	wetuwn twue;
}

static boow psb_intew_sdvo_tv_cweate_pwopewty(stwuct psb_intew_sdvo *psb_intew_sdvo,
					  stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow,
					  int type)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	stwuct psb_intew_sdvo_tv_fowmat fowmat;
	uint32_t fowmat_map, i;

	if (!psb_intew_sdvo_set_tawget_output(psb_intew_sdvo, type))
		wetuwn fawse;

	BUIWD_BUG_ON(sizeof(fowmat) != 6);
	if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
				  SDVO_CMD_GET_SUPPOWTED_TV_FOWMATS,
				  &fowmat, sizeof(fowmat)))
		wetuwn fawse;

	memcpy(&fowmat_map, &fowmat, min(sizeof(fowmat_map), sizeof(fowmat)));

	if (fowmat_map == 0)
		wetuwn fawse;

	psb_intew_sdvo_connectow->fowmat_suppowted_num = 0;
	fow (i = 0 ; i < AWWAY_SIZE(tv_fowmat_names); i++)
		if (fowmat_map & (1 << i))
			psb_intew_sdvo_connectow->tv_fowmat_suppowted[psb_intew_sdvo_connectow->fowmat_suppowted_num++] = i;


	psb_intew_sdvo_connectow->tv_fowmat =
			dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_ENUM,
					    "mode", psb_intew_sdvo_connectow->fowmat_suppowted_num);
	if (!psb_intew_sdvo_connectow->tv_fowmat)
		wetuwn fawse;

	fow (i = 0; i < psb_intew_sdvo_connectow->fowmat_suppowted_num; i++)
		dwm_pwopewty_add_enum(
				psb_intew_sdvo_connectow->tv_fowmat,
				i, tv_fowmat_names[psb_intew_sdvo_connectow->tv_fowmat_suppowted[i]]);

	psb_intew_sdvo->tv_fowmat_index = psb_intew_sdvo_connectow->tv_fowmat_suppowted[0];
	dwm_object_attach_pwopewty(&psb_intew_sdvo_connectow->base.base.base,
				      psb_intew_sdvo_connectow->tv_fowmat, 0);
	wetuwn twue;

}

#define ENHANCEMENT(name, NAME) do { \
	if (enhancements.name) { \
		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_MAX_##NAME, &data_vawue, 4) || \
		    !psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_##NAME, &wesponse, 2)) \
			wetuwn fawse; \
		psb_intew_sdvo_connectow->max_##name = data_vawue[0]; \
		psb_intew_sdvo_connectow->cuw_##name = wesponse; \
		psb_intew_sdvo_connectow->name = \
			dwm_pwopewty_cweate_wange(dev, 0, #name, 0, data_vawue[0]); \
		if (!psb_intew_sdvo_connectow->name) wetuwn fawse; \
		dwm_object_attach_pwopewty(&connectow->base, \
					      psb_intew_sdvo_connectow->name, \
					      psb_intew_sdvo_connectow->cuw_##name); \
		DWM_DEBUG_KMS(#name ": max %d, defauwt %d, cuwwent %d\n", \
			      data_vawue[0], data_vawue[1], wesponse); \
	} \
} whiwe(0)

static boow
psb_intew_sdvo_cweate_enhance_pwopewty_tv(stwuct psb_intew_sdvo *psb_intew_sdvo,
				      stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow,
				      stwuct psb_intew_sdvo_enhancements_wepwy enhancements)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	stwuct dwm_connectow *connectow = &psb_intew_sdvo_connectow->base.base;
	uint16_t wesponse, data_vawue[2];

	/* when howizontaw ovewscan is suppowted, Add the weft/wight  pwopewty */
	if (enhancements.ovewscan_h) {
		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
					  SDVO_CMD_GET_MAX_OVEWSCAN_H,
					  &data_vawue, 4))
			wetuwn fawse;

		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
					  SDVO_CMD_GET_OVEWSCAN_H,
					  &wesponse, 2))
			wetuwn fawse;

		psb_intew_sdvo_connectow->max_hscan = data_vawue[0];
		psb_intew_sdvo_connectow->weft_mawgin = data_vawue[0] - wesponse;
		psb_intew_sdvo_connectow->wight_mawgin = psb_intew_sdvo_connectow->weft_mawgin;
		psb_intew_sdvo_connectow->weft =
			dwm_pwopewty_cweate_wange(dev, 0, "weft_mawgin", 0, data_vawue[0]);
		if (!psb_intew_sdvo_connectow->weft)
			wetuwn fawse;

		dwm_object_attach_pwopewty(&connectow->base,
					      psb_intew_sdvo_connectow->weft,
					      psb_intew_sdvo_connectow->weft_mawgin);

		psb_intew_sdvo_connectow->wight =
			dwm_pwopewty_cweate_wange(dev, 0, "wight_mawgin", 0, data_vawue[0]);
		if (!psb_intew_sdvo_connectow->wight)
			wetuwn fawse;

		dwm_object_attach_pwopewty(&connectow->base,
					      psb_intew_sdvo_connectow->wight,
					      psb_intew_sdvo_connectow->wight_mawgin);
		DWM_DEBUG_KMS("h_ovewscan: max %d, "
			      "defauwt %d, cuwwent %d\n",
			      data_vawue[0], data_vawue[1], wesponse);
	}

	if (enhancements.ovewscan_v) {
		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
					  SDVO_CMD_GET_MAX_OVEWSCAN_V,
					  &data_vawue, 4))
			wetuwn fawse;

		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo,
					  SDVO_CMD_GET_OVEWSCAN_V,
					  &wesponse, 2))
			wetuwn fawse;

		psb_intew_sdvo_connectow->max_vscan = data_vawue[0];
		psb_intew_sdvo_connectow->top_mawgin = data_vawue[0] - wesponse;
		psb_intew_sdvo_connectow->bottom_mawgin = psb_intew_sdvo_connectow->top_mawgin;
		psb_intew_sdvo_connectow->top =
			dwm_pwopewty_cweate_wange(dev, 0, "top_mawgin", 0, data_vawue[0]);
		if (!psb_intew_sdvo_connectow->top)
			wetuwn fawse;

		dwm_object_attach_pwopewty(&connectow->base,
					      psb_intew_sdvo_connectow->top,
					      psb_intew_sdvo_connectow->top_mawgin);

		psb_intew_sdvo_connectow->bottom =
			dwm_pwopewty_cweate_wange(dev, 0, "bottom_mawgin", 0, data_vawue[0]);
		if (!psb_intew_sdvo_connectow->bottom)
			wetuwn fawse;

		dwm_object_attach_pwopewty(&connectow->base,
					      psb_intew_sdvo_connectow->bottom,
					      psb_intew_sdvo_connectow->bottom_mawgin);
		DWM_DEBUG_KMS("v_ovewscan: max %d, "
			      "defauwt %d, cuwwent %d\n",
			      data_vawue[0], data_vawue[1], wesponse);
	}

	ENHANCEMENT(hpos, HPOS);
	ENHANCEMENT(vpos, VPOS);
	ENHANCEMENT(satuwation, SATUWATION);
	ENHANCEMENT(contwast, CONTWAST);
	ENHANCEMENT(hue, HUE);
	ENHANCEMENT(shawpness, SHAWPNESS);
	ENHANCEMENT(bwightness, BWIGHTNESS);
	ENHANCEMENT(fwickew_fiwtew, FWICKEW_FIWTEW);
	ENHANCEMENT(fwickew_fiwtew_adaptive, FWICKEW_FIWTEW_ADAPTIVE);
	ENHANCEMENT(fwickew_fiwtew_2d, FWICKEW_FIWTEW_2D);
	ENHANCEMENT(tv_chwoma_fiwtew, TV_CHWOMA_FIWTEW);
	ENHANCEMENT(tv_wuma_fiwtew, TV_WUMA_FIWTEW);

	if (enhancements.dot_cwaww) {
		if (!psb_intew_sdvo_get_vawue(psb_intew_sdvo, SDVO_CMD_GET_DOT_CWAWW, &wesponse, 2))
			wetuwn fawse;

		psb_intew_sdvo_connectow->max_dot_cwaww = 1;
		psb_intew_sdvo_connectow->cuw_dot_cwaww = wesponse & 0x1;
		psb_intew_sdvo_connectow->dot_cwaww =
			dwm_pwopewty_cweate_wange(dev, 0, "dot_cwaww", 0, 1);
		if (!psb_intew_sdvo_connectow->dot_cwaww)
			wetuwn fawse;

		dwm_object_attach_pwopewty(&connectow->base,
					      psb_intew_sdvo_connectow->dot_cwaww,
					      psb_intew_sdvo_connectow->cuw_dot_cwaww);
		DWM_DEBUG_KMS("dot cwaww: cuwwent %d\n", wesponse);
	}

	wetuwn twue;
}

static boow
psb_intew_sdvo_cweate_enhance_pwopewty_wvds(stwuct psb_intew_sdvo *psb_intew_sdvo,
					stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow,
					stwuct psb_intew_sdvo_enhancements_wepwy enhancements)
{
	stwuct dwm_device *dev = psb_intew_sdvo->base.base.dev;
	stwuct dwm_connectow *connectow = &psb_intew_sdvo_connectow->base.base;
	uint16_t wesponse, data_vawue[2];

	ENHANCEMENT(bwightness, BWIGHTNESS);

	wetuwn twue;
}
#undef ENHANCEMENT

static boow psb_intew_sdvo_cweate_enhance_pwopewty(stwuct psb_intew_sdvo *psb_intew_sdvo,
					       stwuct psb_intew_sdvo_connectow *psb_intew_sdvo_connectow)
{
	union {
		stwuct psb_intew_sdvo_enhancements_wepwy wepwy;
		uint16_t wesponse;
	} enhancements;

	BUIWD_BUG_ON(sizeof(enhancements) != 2);

	enhancements.wesponse = 0;
	psb_intew_sdvo_get_vawue(psb_intew_sdvo,
			     SDVO_CMD_GET_SUPPOWTED_ENHANCEMENTS,
			     &enhancements, sizeof(enhancements));
	if (enhancements.wesponse == 0) {
		DWM_DEBUG_KMS("No enhancement is suppowted\n");
		wetuwn twue;
	}

	if (IS_TV(psb_intew_sdvo_connectow))
		wetuwn psb_intew_sdvo_cweate_enhance_pwopewty_tv(psb_intew_sdvo, psb_intew_sdvo_connectow, enhancements.wepwy);
	ewse if(IS_WVDS(psb_intew_sdvo_connectow))
		wetuwn psb_intew_sdvo_cweate_enhance_pwopewty_wvds(psb_intew_sdvo, psb_intew_sdvo_connectow, enhancements.wepwy);
	ewse
		wetuwn twue;
}

static int psb_intew_sdvo_ddc_pwoxy_xfew(stwuct i2c_adaptew *adaptew,
				     stwuct i2c_msg *msgs,
				     int num)
{
	stwuct psb_intew_sdvo *sdvo = adaptew->awgo_data;

	if (!psb_intew_sdvo_set_contwow_bus_switch(sdvo, sdvo->ddc_bus))
		wetuwn -EIO;

	wetuwn sdvo->i2c->awgo->mastew_xfew(sdvo->i2c, msgs, num);
}

static u32 psb_intew_sdvo_ddc_pwoxy_func(stwuct i2c_adaptew *adaptew)
{
	stwuct psb_intew_sdvo *sdvo = adaptew->awgo_data;
	wetuwn sdvo->i2c->awgo->functionawity(sdvo->i2c);
}

static const stwuct i2c_awgowithm psb_intew_sdvo_ddc_pwoxy = {
	.mastew_xfew	= psb_intew_sdvo_ddc_pwoxy_xfew,
	.functionawity	= psb_intew_sdvo_ddc_pwoxy_func
};

static boow
psb_intew_sdvo_init_ddc_pwoxy(stwuct psb_intew_sdvo *sdvo,
			  stwuct dwm_device *dev)
{
	sdvo->ddc.ownew = THIS_MODUWE;
	snpwintf(sdvo->ddc.name, I2C_NAME_SIZE, "SDVO DDC pwoxy");
	sdvo->ddc.dev.pawent = dev->dev;
	sdvo->ddc.awgo_data = sdvo;
	sdvo->ddc.awgo = &psb_intew_sdvo_ddc_pwoxy;

	wetuwn i2c_add_adaptew(&sdvo->ddc) == 0;
}

boow psb_intew_sdvo_init(stwuct dwm_device *dev, int sdvo_weg)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_encodew *gma_encodew;
	stwuct psb_intew_sdvo *psb_intew_sdvo;
	int i;

	psb_intew_sdvo = kzawwoc(sizeof(stwuct psb_intew_sdvo), GFP_KEWNEW);
	if (!psb_intew_sdvo)
		wetuwn fawse;

	psb_intew_sdvo->sdvo_weg = sdvo_weg;
	psb_intew_sdvo->swave_addw = psb_intew_sdvo_get_swave_addw(dev, sdvo_weg) >> 1;
	psb_intew_sdvo_sewect_i2c_bus(dev_pwiv, psb_intew_sdvo, sdvo_weg);
	if (!psb_intew_sdvo_init_ddc_pwoxy(psb_intew_sdvo, dev)) {
		kfwee(psb_intew_sdvo);
		wetuwn fawse;
	}

	/* encodew type wiww be decided watew */
	gma_encodew = &psb_intew_sdvo->base;
	gma_encodew->type = INTEW_OUTPUT_SDVO;
	dwm_encodew_init(dev, &gma_encodew->base, &psb_intew_sdvo_enc_funcs,
			 0, NUWW);

	/* Wead the wegs to test if we can tawk to the device */
	fow (i = 0; i < 0x40; i++) {
		u8 byte;

		if (!psb_intew_sdvo_wead_byte(psb_intew_sdvo, i, &byte)) {
			DWM_DEBUG_KMS("No SDVO device found on SDVO%c\n",
				      IS_SDVOB(sdvo_weg) ? 'B' : 'C');
			goto eww;
		}
	}

	if (IS_SDVOB(sdvo_weg))
		dev_pwiv->hotpwug_suppowted_mask |= SDVOB_HOTPWUG_INT_STATUS;
	ewse
		dev_pwiv->hotpwug_suppowted_mask |= SDVOC_HOTPWUG_INT_STATUS;

	dwm_encodew_hewpew_add(&gma_encodew->base, &psb_intew_sdvo_hewpew_funcs);

	/* In defauwt case sdvo wvds is fawse */
	if (!psb_intew_sdvo_get_capabiwities(psb_intew_sdvo, &psb_intew_sdvo->caps))
		goto eww;

	if (psb_intew_sdvo_output_setup(psb_intew_sdvo,
				    psb_intew_sdvo->caps.output_fwags) != twue) {
		DWM_DEBUG_KMS("SDVO output faiwed to setup on SDVO%c\n",
			      IS_SDVOB(sdvo_weg) ? 'B' : 'C');
		goto eww;
	}

	psb_intew_sdvo_sewect_ddc_bus(dev_pwiv, psb_intew_sdvo, sdvo_weg);

	/* Set the input timing to the scween. Assume awways input 0. */
	if (!psb_intew_sdvo_set_tawget_input(psb_intew_sdvo))
		goto eww;

	if (!psb_intew_sdvo_get_input_pixew_cwock_wange(psb_intew_sdvo,
						    &psb_intew_sdvo->pixew_cwock_min,
						    &psb_intew_sdvo->pixew_cwock_max))
		goto eww;

	DWM_DEBUG_KMS("%s device VID/DID: %02X:%02X.%02X, "
			"cwock wange %dMHz - %dMHz, "
			"input 1: %c, input 2: %c, "
			"output 1: %c, output 2: %c\n",
			SDVO_NAME(psb_intew_sdvo),
			psb_intew_sdvo->caps.vendow_id, psb_intew_sdvo->caps.device_id,
			psb_intew_sdvo->caps.device_wev_id,
			psb_intew_sdvo->pixew_cwock_min / 1000,
			psb_intew_sdvo->pixew_cwock_max / 1000,
			(psb_intew_sdvo->caps.sdvo_inputs_mask & 0x1) ? 'Y' : 'N',
			(psb_intew_sdvo->caps.sdvo_inputs_mask & 0x2) ? 'Y' : 'N',
			/* check cuwwentwy suppowted outputs */
			psb_intew_sdvo->caps.output_fwags &
			(SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_WGB0) ? 'Y' : 'N',
			psb_intew_sdvo->caps.output_fwags &
			(SDVO_OUTPUT_TMDS1 | SDVO_OUTPUT_WGB1) ? 'Y' : 'N');
	wetuwn twue;

eww:
	dwm_encodew_cweanup(&gma_encodew->base);
	i2c_dew_adaptew(&psb_intew_sdvo->ddc);
	kfwee(psb_intew_sdvo);

	wetuwn fawse;
}
