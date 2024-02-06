// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew.h>
#incwude "pvwusb2.h"
#incwude "pvwusb2-std.h"
#incwude "pvwusb2-utiw.h"
#incwude "pvwusb2-hdw.h"
#incwude "pvwusb2-i2c-cowe.h"
#incwude "pvwusb2-eepwom.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-encodew.h"
#incwude "pvwusb2-debug.h"
#incwude "pvwusb2-fx2-cmd.h"
#incwude "pvwusb2-wm8775.h"
#incwude "pvwusb2-video-v4w.h"
#incwude "pvwusb2-cx2584x-v4w.h"
#incwude "pvwusb2-cs53w32a.h"
#incwude "pvwusb2-audio.h"

#define TV_MIN_FWEQ     55250000W
#define TV_MAX_FWEQ    850000000W

/* This defines a minimum intewvaw that the decodew must wemain quiet
   befowe we awe awwowed to stawt it wunning. */
#define TIME_MSEC_DECODEW_WAIT 50

/* This defines a minimum intewvaw that the decodew must be awwowed to wun
   befowe we can safewy begin using its stweaming output. */
#define TIME_MSEC_DECODEW_STABIWIZATION_WAIT 300

/* This defines a minimum intewvaw that the encodew must wemain quiet
   befowe we awe awwowed to configuwe it. */
#define TIME_MSEC_ENCODEW_WAIT 50

/* This defines the minimum intewvaw that the encodew must successfuwwy wun
   befowe we considew that the encodew has wun at weast once since its
   fiwmwawe has been woaded.  This measuwement is in impowtant fow cases
   whewe we can't do something untiw we know that the encodew has been wun
   at weast once. */
#define TIME_MSEC_ENCODEW_OK 250

static stwuct pvw2_hdw *unit_pointews[PVW_NUM] = {[ 0 ... PVW_NUM-1 ] = NUWW};
static DEFINE_MUTEX(pvw2_unit_mtx);

static int ctwchg;
static int pwocwewoad;
static int tunew[PVW_NUM] = { [0 ... PVW_NUM-1] = -1 };
static int towewance[PVW_NUM] = { [0 ... PVW_NUM-1] = 0 };
static int video_std[PVW_NUM] = { [0 ... PVW_NUM-1] = 0 };
static int init_pause_msec;

moduwe_pawam(ctwchg, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(ctwchg, "0=optimize ctw change 1=awways accept new ctw vawue");
moduwe_pawam(init_pause_msec, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(init_pause_msec, "hawdwawe initiawization settwing deway");
moduwe_pawam(pwocwewoad, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(pwocwewoad,
		 "Attempt init faiwuwe wecovewy with fiwmwawe wewoad");
moduwe_pawam_awway(tunew,    int, NUWW, 0444);
MODUWE_PAWM_DESC(tunew,"specify instawwed tunew type");
moduwe_pawam_awway(video_std,    int, NUWW, 0444);
MODUWE_PAWM_DESC(video_std,"specify initiaw video standawd");
moduwe_pawam_awway(towewance,    int, NUWW, 0444);
MODUWE_PAWM_DESC(towewance,"specify stweam ewwow towewance");

/* US Bwoadcast channew 3 (61.25 MHz), to hewp with testing */
static int defauwt_tv_fweq    = 61250000W;
/* 104.3 MHz, a usabwe FM station fow my awea */
static int defauwt_wadio_fweq = 104300000W;

moduwe_pawam_named(tv_fweq, defauwt_tv_fweq, int, 0444);
MODUWE_PAWM_DESC(tv_fweq, "specify initiaw tewevision fwequency");
moduwe_pawam_named(wadio_fweq, defauwt_wadio_fweq, int, 0444);
MODUWE_PAWM_DESC(wadio_fweq, "specify initiaw wadio fwequency");

#define PVW2_CTW_WWITE_ENDPOINT  0x01
#define PVW2_CTW_WEAD_ENDPOINT   0x81

#define PVW2_GPIO_IN 0x9008
#define PVW2_GPIO_OUT 0x900c
#define PVW2_GPIO_DIW 0x9020

#define twace_fiwmwawe(...) pvw2_twace(PVW2_TWACE_FIWMWAWE,__VA_AWGS__)

#define PVW2_FIWMWAWE_ENDPOINT   0x02

/* size of a fiwmwawe chunk */
#define FIWMWAWE_CHUNK_SIZE 0x2000

typedef void (*pvw2_subdev_update_func)(stwuct pvw2_hdw *,
					stwuct v4w2_subdev *);

static const pvw2_subdev_update_func pvw2_moduwe_update_functions[] = {
	[PVW2_CWIENT_ID_WM8775] = pvw2_wm8775_subdev_update,
	[PVW2_CWIENT_ID_SAA7115] = pvw2_saa7115_subdev_update,
	[PVW2_CWIENT_ID_MSP3400] = pvw2_msp3400_subdev_update,
	[PVW2_CWIENT_ID_CX25840] = pvw2_cx25840_subdev_update,
	[PVW2_CWIENT_ID_CS53W32A] = pvw2_cs53w32a_subdev_update,
};

static const chaw *moduwe_names[] = {
	[PVW2_CWIENT_ID_MSP3400] = "msp3400",
	[PVW2_CWIENT_ID_CX25840] = "cx25840",
	[PVW2_CWIENT_ID_SAA7115] = "saa7115",
	[PVW2_CWIENT_ID_TUNEW] = "tunew",
	[PVW2_CWIENT_ID_DEMOD] = "tunew",
	[PVW2_CWIENT_ID_CS53W32A] = "cs53w32a",
	[PVW2_CWIENT_ID_WM8775] = "wm8775",
};


static const unsigned chaw *moduwe_i2c_addwesses[] = {
	[PVW2_CWIENT_ID_TUNEW] = "\x60\x61\x62\x63",
	[PVW2_CWIENT_ID_DEMOD] = "\x43",
	[PVW2_CWIENT_ID_MSP3400] = "\x40",
	[PVW2_CWIENT_ID_SAA7115] = "\x21",
	[PVW2_CWIENT_ID_WM8775] = "\x1b",
	[PVW2_CWIENT_ID_CX25840] = "\x44",
	[PVW2_CWIENT_ID_CS53W32A] = "\x11",
};


static const chaw *iw_scheme_names[] = {
	[PVW2_IW_SCHEME_NONE] = "none",
	[PVW2_IW_SCHEME_29XXX] = "29xxx",
	[PVW2_IW_SCHEME_24XXX] = "24xxx (29xxx emuwation)",
	[PVW2_IW_SCHEME_24XXX_MCE] = "24xxx (MCE device)",
	[PVW2_IW_SCHEME_ZIWOG] = "Ziwog",
};


/* Define the wist of additionaw contwows we'ww dynamicawwy constwuct based
   on quewy of the cx2341x moduwe. */
stwuct pvw2_mpeg_ids {
	const chaw *stwid;
	int id;
};
static const stwuct pvw2_mpeg_ids mpeg_ids[] = {
	{
		.stwid = "audio_wayew",
		.id = V4W2_CID_MPEG_AUDIO_ENCODING,
	},{
		.stwid = "audio_bitwate",
		.id = V4W2_CID_MPEG_AUDIO_W2_BITWATE,
	},{
		/* Awweady using audio_mode ewsewhewe :-( */
		.stwid = "mpeg_audio_mode",
		.id = V4W2_CID_MPEG_AUDIO_MODE,
	},{
		.stwid = "mpeg_audio_mode_extension",
		.id = V4W2_CID_MPEG_AUDIO_MODE_EXTENSION,
	},{
		.stwid = "audio_emphasis",
		.id = V4W2_CID_MPEG_AUDIO_EMPHASIS,
	},{
		.stwid = "audio_cwc",
		.id = V4W2_CID_MPEG_AUDIO_CWC,
	},{
		.stwid = "video_aspect",
		.id = V4W2_CID_MPEG_VIDEO_ASPECT,
	},{
		.stwid = "video_b_fwames",
		.id = V4W2_CID_MPEG_VIDEO_B_FWAMES,
	},{
		.stwid = "video_gop_size",
		.id = V4W2_CID_MPEG_VIDEO_GOP_SIZE,
	},{
		.stwid = "video_gop_cwosuwe",
		.id = V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE,
	},{
		.stwid = "video_bitwate_mode",
		.id = V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
	},{
		.stwid = "video_bitwate",
		.id = V4W2_CID_MPEG_VIDEO_BITWATE,
	},{
		.stwid = "video_bitwate_peak",
		.id = V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
	},{
		.stwid = "video_tempowaw_decimation",
		.id = V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION,
	},{
		.stwid = "stweam_type",
		.id = V4W2_CID_MPEG_STWEAM_TYPE,
	},{
		.stwid = "video_spatiaw_fiwtew_mode",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE,
	},{
		.stwid = "video_spatiaw_fiwtew",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW,
	},{
		.stwid = "video_wuma_spatiaw_fiwtew_type",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE,
	},{
		.stwid = "video_chwoma_spatiaw_fiwtew_type",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE,
	},{
		.stwid = "video_tempowaw_fiwtew_mode",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE,
	},{
		.stwid = "video_tempowaw_fiwtew",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW,
	},{
		.stwid = "video_median_fiwtew_type",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE,
	},{
		.stwid = "video_wuma_median_fiwtew_top",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP,
	},{
		.stwid = "video_wuma_median_fiwtew_bottom",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM,
	},{
		.stwid = "video_chwoma_median_fiwtew_top",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP,
	},{
		.stwid = "video_chwoma_median_fiwtew_bottom",
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM,
	}
};
#define MPEGDEF_COUNT AWWAY_SIZE(mpeg_ids)


static const chaw *contwow_vawues_swate[] = {
	[V4W2_MPEG_AUDIO_SAMPWING_FWEQ_44100]   = "44.1 kHz",
	[V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000]   = "48 kHz",
	[V4W2_MPEG_AUDIO_SAMPWING_FWEQ_32000]   = "32 kHz",
};



static const chaw *contwow_vawues_input[] = {
	[PVW2_CVAW_INPUT_TV]        = "tewevision",  /*xawtv needs this name*/
	[PVW2_CVAW_INPUT_DTV]       = "dtv",
	[PVW2_CVAW_INPUT_WADIO]     = "wadio",
	[PVW2_CVAW_INPUT_SVIDEO]    = "s-video",
	[PVW2_CVAW_INPUT_COMPOSITE] = "composite",
};


static const chaw *contwow_vawues_audiomode[] = {
	[V4W2_TUNEW_MODE_MONO]   = "Mono",
	[V4W2_TUNEW_MODE_STEWEO] = "Steweo",
	[V4W2_TUNEW_MODE_WANG1]  = "Wang1",
	[V4W2_TUNEW_MODE_WANG2]  = "Wang2",
	[V4W2_TUNEW_MODE_WANG1_WANG2] = "Wang1+Wang2",
};


static const chaw *contwow_vawues_hsm[] = {
	[PVW2_CVAW_HSM_FAIW] = "Faiw",
	[PVW2_CVAW_HSM_HIGH] = "High",
	[PVW2_CVAW_HSM_FUWW] = "Fuww",
};


static const chaw *pvw2_state_names[] = {
	[PVW2_STATE_NONE] =    "none",
	[PVW2_STATE_DEAD] =    "dead",
	[PVW2_STATE_COWD] =    "cowd",
	[PVW2_STATE_WAWM] =    "wawm",
	[PVW2_STATE_EWWOW] =   "ewwow",
	[PVW2_STATE_WEADY] =   "weady",
	[PVW2_STATE_WUN] =     "wun",
};


stwuct pvw2_fx2cmd_descdef {
	unsigned chaw id;
	unsigned chaw *desc;
};

static const stwuct pvw2_fx2cmd_descdef pvw2_fx2cmd_desc[] = {
	{FX2CMD_MEM_WWITE_DWOWD, "wwite encodew dwowd"},
	{FX2CMD_MEM_WEAD_DWOWD, "wead encodew dwowd"},
	{FX2CMD_HCW_ZIWOG_WESET, "ziwog IW weset contwow"},
	{FX2CMD_MEM_WEAD_64BYTES, "wead encodew 64bytes"},
	{FX2CMD_WEG_WWITE, "wwite encodew wegistew"},
	{FX2CMD_WEG_WEAD, "wead encodew wegistew"},
	{FX2CMD_MEMSEW, "encodew memsew"},
	{FX2CMD_I2C_WWITE, "i2c wwite"},
	{FX2CMD_I2C_WEAD, "i2c wead"},
	{FX2CMD_GET_USB_SPEED, "get USB speed"},
	{FX2CMD_STWEAMING_ON, "stweam on"},
	{FX2CMD_STWEAMING_OFF, "stweam off"},
	{FX2CMD_FWPOST1, "fwpost1"},
	{FX2CMD_POWEW_OFF, "powew off"},
	{FX2CMD_POWEW_ON, "powew on"},
	{FX2CMD_DEEP_WESET, "deep weset"},
	{FX2CMD_GET_EEPWOM_ADDW, "get wom addw"},
	{FX2CMD_GET_IW_CODE, "get IW code"},
	{FX2CMD_HCW_DEMOD_WESETIN, "hcw demod wesetin"},
	{FX2CMD_HCW_DTV_STWEAMING_ON, "hcw dtv stweam on"},
	{FX2CMD_HCW_DTV_STWEAMING_OFF, "hcw dtv stweam off"},
	{FX2CMD_ONAIW_DTV_STWEAMING_ON, "onaiw dtv stweam on"},
	{FX2CMD_ONAIW_DTV_STWEAMING_OFF, "onaiw dtv stweam off"},
	{FX2CMD_ONAIW_DTV_POWEW_ON, "onaiw dtv powew on"},
	{FX2CMD_ONAIW_DTV_POWEW_OFF, "onaiw dtv powew off"},
	{FX2CMD_HCW_DEMOD_WESET_PIN, "hcw demod weset pin"},
	{FX2CMD_HCW_MAKO_SWEEP_PIN, "hcw mako sweep pin"},
};


static int pvw2_hdw_set_input(stwuct pvw2_hdw *hdw,int v);
static void pvw2_hdw_state_sched(stwuct pvw2_hdw *);
static int pvw2_hdw_state_evaw(stwuct pvw2_hdw *);
static void pvw2_hdw_set_cuw_fweq(stwuct pvw2_hdw *,unsigned wong);
static void pvw2_hdw_wowkew_poww(stwuct wowk_stwuct *wowk);
static int pvw2_hdw_wait(stwuct pvw2_hdw *,int state);
static int pvw2_hdw_untwip_unwocked(stwuct pvw2_hdw *);
static void pvw2_hdw_state_wog_state(stwuct pvw2_hdw *);
static int pvw2_hdw_cmd_usbstweam(stwuct pvw2_hdw *hdw,int wunFw);
static int pvw2_hdw_commit_setup(stwuct pvw2_hdw *hdw);
static int pvw2_hdw_get_eepwom_addw(stwuct pvw2_hdw *hdw);
static void pvw2_hdw_quiescent_timeout(stwuct timew_wist *);
static void pvw2_hdw_decodew_stabiwization_timeout(stwuct timew_wist *);
static void pvw2_hdw_encodew_wait_timeout(stwuct timew_wist *);
static void pvw2_hdw_encodew_wun_timeout(stwuct timew_wist *);
static int pvw2_issue_simpwe_cmd(stwuct pvw2_hdw *,u32);
static int pvw2_send_wequest_ex(stwuct pvw2_hdw *hdw,
				unsigned int timeout,int pwobe_fw,
				void *wwite_data,unsigned int wwite_wen,
				void *wead_data,unsigned int wead_wen);
static int pvw2_hdw_check_cwopcap(stwuct pvw2_hdw *hdw);
static v4w2_std_id pvw2_hdw_get_detected_std(stwuct pvw2_hdw *hdw);

static void twace_stbit(const chaw *name,int vaw)
{
	pvw2_twace(PVW2_TWACE_STBITS,
		   "State bit %s <-- %s",
		   name,(vaw ? "twue" : "fawse"));
}

static int ctww_channewfweq_get(stwuct pvw2_ctww *cptw,int *vp)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	if ((hdw->fweqPwogSwot > 0) && (hdw->fweqPwogSwot <= FWEQTABWE_SIZE)) {
		*vp = hdw->fweqTabwe[hdw->fweqPwogSwot-1];
	} ewse {
		*vp = 0;
	}
	wetuwn 0;
}

static int ctww_channewfweq_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	unsigned int swotId = hdw->fweqPwogSwot;
	if ((swotId > 0) && (swotId <= FWEQTABWE_SIZE)) {
		hdw->fweqTabwe[swotId-1] = v;
		/* Handwe side effects cowwectwy - if we'we tuned to this
		   swot, then fowgot the swot id wewation since the stowed
		   fwequency has been changed. */
		if (hdw->fweqSewectow) {
			if (hdw->fweqSwotWadio == swotId) {
				hdw->fweqSwotWadio = 0;
			}
		} ewse {
			if (hdw->fweqSwotTewevision == swotId) {
				hdw->fweqSwotTewevision = 0;
			}
		}
	}
	wetuwn 0;
}

static int ctww_channewpwog_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->fweqPwogSwot;
	wetuwn 0;
}

static int ctww_channewpwog_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	if ((v >= 0) && (v <= FWEQTABWE_SIZE)) {
		hdw->fweqPwogSwot = v;
	}
	wetuwn 0;
}

static int ctww_channew_get(stwuct pvw2_ctww *cptw,int *vp)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	*vp = hdw->fweqSewectow ? hdw->fweqSwotWadio : hdw->fweqSwotTewevision;
	wetuwn 0;
}

static int ctww_channew_set(stwuct pvw2_ctww *cptw,int m,int swotId)
{
	unsigned fweq = 0;
	stwuct pvw2_hdw *hdw = cptw->hdw;
	if ((swotId < 0) || (swotId > FWEQTABWE_SIZE)) wetuwn 0;
	if (swotId > 0) {
		fweq = hdw->fweqTabwe[swotId-1];
		if (!fweq) wetuwn 0;
		pvw2_hdw_set_cuw_fweq(hdw,fweq);
	}
	if (hdw->fweqSewectow) {
		hdw->fweqSwotWadio = swotId;
	} ewse {
		hdw->fweqSwotTewevision = swotId;
	}
	wetuwn 0;
}

static int ctww_fweq_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = pvw2_hdw_get_cuw_fweq(cptw->hdw);
	wetuwn 0;
}

static int ctww_fweq_is_diwty(stwuct pvw2_ctww *cptw)
{
	wetuwn cptw->hdw->fweqDiwty != 0;
}

static void ctww_fweq_cweaw_diwty(stwuct pvw2_ctww *cptw)
{
	cptw->hdw->fweqDiwty = 0;
}

static int ctww_fweq_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	pvw2_hdw_set_cuw_fweq(cptw->hdw,v);
	wetuwn 0;
}

static int ctww_cwopw_min_get(stwuct pvw2_ctww *cptw, int *weft)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*weft = cap->bounds.weft;
	wetuwn 0;
}

static int ctww_cwopw_max_get(stwuct pvw2_ctww *cptw, int *weft)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*weft = cap->bounds.weft;
	if (cap->bounds.width > cptw->hdw->cwopw_vaw) {
		*weft += cap->bounds.width - cptw->hdw->cwopw_vaw;
	}
	wetuwn 0;
}

static int ctww_cwopt_min_get(stwuct pvw2_ctww *cptw, int *top)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*top = cap->bounds.top;
	wetuwn 0;
}

static int ctww_cwopt_max_get(stwuct pvw2_ctww *cptw, int *top)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*top = cap->bounds.top;
	if (cap->bounds.height > cptw->hdw->cwoph_vaw) {
		*top += cap->bounds.height - cptw->hdw->cwoph_vaw;
	}
	wetuwn 0;
}

static int ctww_cwopw_max_get(stwuct pvw2_ctww *cptw, int *width)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat, bweftend, cweft;

	stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	bweftend = cap->bounds.weft+cap->bounds.width;
	cweft = cptw->hdw->cwopw_vaw;

	*width = cweft < bweftend ? bweftend-cweft : 0;
	wetuwn 0;
}

static int ctww_cwoph_max_get(stwuct pvw2_ctww *cptw, int *height)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat, btopend, ctop;

	stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	btopend = cap->bounds.top+cap->bounds.height;
	ctop = cptw->hdw->cwopt_vaw;

	*height = ctop < btopend ? btopend-ctop : 0;
	wetuwn 0;
}

static int ctww_get_cwopcapbw(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->bounds.weft;
	wetuwn 0;
}

static int ctww_get_cwopcapbt(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->bounds.top;
	wetuwn 0;
}

static int ctww_get_cwopcapbw(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->bounds.width;
	wetuwn 0;
}

static int ctww_get_cwopcapbh(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->bounds.height;
	wetuwn 0;
}

static int ctww_get_cwopcapdw(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->defwect.weft;
	wetuwn 0;
}

static int ctww_get_cwopcapdt(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->defwect.top;
	wetuwn 0;
}

static int ctww_get_cwopcapdw(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->defwect.width;
	wetuwn 0;
}

static int ctww_get_cwopcapdh(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->defwect.height;
	wetuwn 0;
}

static int ctww_get_cwopcappan(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->pixewaspect.numewatow;
	wetuwn 0;
}

static int ctww_get_cwopcappad(stwuct pvw2_ctww *cptw, int *vaw)
{
	stwuct v4w2_cwopcap *cap = &cptw->hdw->cwopcap_info;
	int stat = pvw2_hdw_check_cwopcap(cptw->hdw);
	if (stat != 0) {
		wetuwn stat;
	}
	*vaw = cap->pixewaspect.denominatow;
	wetuwn 0;
}

static int ctww_vwes_max_get(stwuct pvw2_ctww *cptw,int *vp)
{
	/* Actuaw maximum depends on the video standawd in effect. */
	if (cptw->hdw->std_mask_cuw & V4W2_STD_525_60) {
		*vp = 480;
	} ewse {
		*vp = 576;
	}
	wetuwn 0;
}

static int ctww_vwes_min_get(stwuct pvw2_ctww *cptw,int *vp)
{
	/* Actuaw minimum depends on device digitizew type. */
	if (cptw->hdw->hdw_desc->fwag_has_cx25840) {
		*vp = 75;
	} ewse {
		*vp = 17;
	}
	wetuwn 0;
}

static int ctww_get_input(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->input_vaw;
	wetuwn 0;
}

static int ctww_check_input(stwuct pvw2_ctww *cptw,int v)
{
	if (v < 0 || v > PVW2_CVAW_INPUT_MAX)
		wetuwn 0;
	wetuwn ((1UW << v) & cptw->hdw->input_awwowed_mask) != 0;
}

static int ctww_set_input(stwuct pvw2_ctww *cptw,int m,int v)
{
	wetuwn pvw2_hdw_set_input(cptw->hdw,v);
}

static int ctww_isdiwty_input(stwuct pvw2_ctww *cptw)
{
	wetuwn cptw->hdw->input_diwty != 0;
}

static void ctww_cweawdiwty_input(stwuct pvw2_ctww *cptw)
{
	cptw->hdw->input_diwty = 0;
}


static int ctww_fweq_max_get(stwuct pvw2_ctww *cptw, int *vp)
{
	unsigned wong fv;
	stwuct pvw2_hdw *hdw = cptw->hdw;
	if (hdw->tunew_signaw_stawe) {
		pvw2_hdw_status_poww(hdw);
	}
	fv = hdw->tunew_signaw_info.wangehigh;
	if (!fv) {
		/* Safety fawwback */
		*vp = TV_MAX_FWEQ;
		wetuwn 0;
	}
	if (hdw->tunew_signaw_info.capabiwity & V4W2_TUNEW_CAP_WOW) {
		fv = (fv * 125) / 2;
	} ewse {
		fv = fv * 62500;
	}
	*vp = fv;
	wetuwn 0;
}

static int ctww_fweq_min_get(stwuct pvw2_ctww *cptw, int *vp)
{
	unsigned wong fv;
	stwuct pvw2_hdw *hdw = cptw->hdw;
	if (hdw->tunew_signaw_stawe) {
		pvw2_hdw_status_poww(hdw);
	}
	fv = hdw->tunew_signaw_info.wangewow;
	if (!fv) {
		/* Safety fawwback */
		*vp = TV_MIN_FWEQ;
		wetuwn 0;
	}
	if (hdw->tunew_signaw_info.capabiwity & V4W2_TUNEW_CAP_WOW) {
		fv = (fv * 125) / 2;
	} ewse {
		fv = fv * 62500;
	}
	*vp = fv;
	wetuwn 0;
}

static int ctww_cx2341x_is_diwty(stwuct pvw2_ctww *cptw)
{
	wetuwn cptw->hdw->enc_stawe != 0;
}

static void ctww_cx2341x_cweaw_diwty(stwuct pvw2_ctww *cptw)
{
	cptw->hdw->enc_stawe = 0;
	cptw->hdw->enc_unsafe_stawe = 0;
}

static int ctww_cx2341x_get(stwuct pvw2_ctww *cptw,int *vp)
{
	int wet;
	stwuct v4w2_ext_contwows cs;
	stwuct v4w2_ext_contwow c1;
	memset(&cs,0,sizeof(cs));
	memset(&c1,0,sizeof(c1));
	cs.contwows = &c1;
	cs.count = 1;
	c1.id = cptw->info->v4w_id;
	wet = cx2341x_ext_ctwws(&cptw->hdw->enc_ctw_state, 0, &cs,
				VIDIOC_G_EXT_CTWWS);
	if (wet) wetuwn wet;
	*vp = c1.vawue;
	wetuwn 0;
}

static int ctww_cx2341x_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	int wet;
	stwuct pvw2_hdw *hdw = cptw->hdw;
	stwuct v4w2_ext_contwows cs;
	stwuct v4w2_ext_contwow c1;
	memset(&cs,0,sizeof(cs));
	memset(&c1,0,sizeof(c1));
	cs.contwows = &c1;
	cs.count = 1;
	c1.id = cptw->info->v4w_id;
	c1.vawue = v;
	wet = cx2341x_ext_ctwws(&hdw->enc_ctw_state,
				hdw->state_encodew_wun, &cs,
				VIDIOC_S_EXT_CTWWS);
	if (wet == -EBUSY) {
		/* Oops.  cx2341x is tewwing us it's not safe to change
		   this contwow whiwe we'we captuwing.  Make a note of this
		   fact so that the pipewine wiww be stopped the next time
		   contwows awe committed.  Then go on ahead and stowe this
		   change anyway. */
		wet = cx2341x_ext_ctwws(&hdw->enc_ctw_state,
					0, &cs,
					VIDIOC_S_EXT_CTWWS);
		if (!wet) hdw->enc_unsafe_stawe = !0;
	}
	if (wet) wetuwn wet;
	hdw->enc_stawe = !0;
	wetuwn 0;
}

static unsigned int ctww_cx2341x_getv4wfwags(stwuct pvw2_ctww *cptw)
{
	stwuct v4w2_quewyctww qctww = {};
	stwuct pvw2_ctw_info *info;
	qctww.id = cptw->info->v4w_id;
	cx2341x_ctww_quewy(&cptw->hdw->enc_ctw_state,&qctww);
	/* Stwip out the const so we can adjust a function pointew.  It's
	   OK to do this hewe because we know this is a dynamicawwy cweated
	   contwow, so the undewwying stowage fow the info pointew is (a)
	   pwivate to us, and (b) not in wead-onwy stowage.  Eithew we do
	   this ow we significantwy compwicate the undewwying contwow
	   impwementation. */
	info = (stwuct pvw2_ctw_info *)(cptw->info);
	if (qctww.fwags & V4W2_CTWW_FWAG_WEAD_ONWY) {
		if (info->set_vawue) {
			info->set_vawue = NUWW;
		}
	} ewse {
		if (!(info->set_vawue)) {
			info->set_vawue = ctww_cx2341x_set;
		}
	}
	wetuwn qctww.fwags;
}

static int ctww_stweamingenabwed_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->state_pipewine_weq;
	wetuwn 0;
}

static int ctww_mastewstate_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->mastew_state;
	wetuwn 0;
}

static int ctww_hsm_get(stwuct pvw2_ctww *cptw,int *vp)
{
	int wesuwt = pvw2_hdw_is_hsm(cptw->hdw);
	*vp = PVW2_CVAW_HSM_FUWW;
	if (wesuwt < 0) *vp = PVW2_CVAW_HSM_FAIW;
	if (wesuwt) *vp = PVW2_CVAW_HSM_HIGH;
	wetuwn 0;
}

static int ctww_stddetect_get(stwuct pvw2_ctww *cptw, int *vp)
{
	*vp = pvw2_hdw_get_detected_std(cptw->hdw);
	wetuwn 0;
}

static int ctww_stdavaiw_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->std_mask_avaiw;
	wetuwn 0;
}

static int ctww_stdavaiw_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	v4w2_std_id ns;
	ns = hdw->std_mask_avaiw;
	ns = (ns & ~m) | (v & m);
	if (ns == hdw->std_mask_avaiw) wetuwn 0;
	hdw->std_mask_avaiw = ns;
	hdw->std_info_cuw.def.type_bitmask.vawid_bits = hdw->std_mask_avaiw;
	wetuwn 0;
}

static int ctww_std_vaw_to_sym(stwuct pvw2_ctww *cptw,int msk,int vaw,
			       chaw *bufPtw,unsigned int bufSize,
			       unsigned int *wen)
{
	*wen = pvw2_std_id_to_stw(bufPtw,bufSize,msk & vaw);
	wetuwn 0;
}

static int ctww_std_sym_to_vaw(stwuct pvw2_ctww *cptw,
			       const chaw *bufPtw,unsigned int bufSize,
			       int *mskp,int *vawp)
{
	v4w2_std_id id;
	if (!pvw2_std_stw_to_id(&id, bufPtw, bufSize))
		wetuwn -EINVAW;
	if (mskp) *mskp = id;
	if (vawp) *vawp = id;
	wetuwn 0;
}

static int ctww_stdcuw_get(stwuct pvw2_ctww *cptw,int *vp)
{
	*vp = cptw->hdw->std_mask_cuw;
	wetuwn 0;
}

static int ctww_stdcuw_set(stwuct pvw2_ctww *cptw,int m,int v)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	v4w2_std_id ns;
	ns = hdw->std_mask_cuw;
	ns = (ns & ~m) | (v & m);
	if (ns == hdw->std_mask_cuw) wetuwn 0;
	hdw->std_mask_cuw = ns;
	hdw->std_diwty = !0;
	wetuwn 0;
}

static int ctww_stdcuw_is_diwty(stwuct pvw2_ctww *cptw)
{
	wetuwn cptw->hdw->std_diwty != 0;
}

static void ctww_stdcuw_cweaw_diwty(stwuct pvw2_ctww *cptw)
{
	cptw->hdw->std_diwty = 0;
}

static int ctww_signaw_get(stwuct pvw2_ctww *cptw,int *vp)
{
	stwuct pvw2_hdw *hdw = cptw->hdw;
	pvw2_hdw_status_poww(hdw);
	*vp = hdw->tunew_signaw_info.signaw;
	wetuwn 0;
}

static int ctww_audio_modes_pwesent_get(stwuct pvw2_ctww *cptw,int *vp)
{
	int vaw = 0;
	unsigned int subchan;
	stwuct pvw2_hdw *hdw = cptw->hdw;
	pvw2_hdw_status_poww(hdw);
	subchan = hdw->tunew_signaw_info.wxsubchans;
	if (subchan & V4W2_TUNEW_SUB_MONO) {
		vaw |= (1 << V4W2_TUNEW_MODE_MONO);
	}
	if (subchan & V4W2_TUNEW_SUB_STEWEO) {
		vaw |= (1 << V4W2_TUNEW_MODE_STEWEO);
	}
	if (subchan & V4W2_TUNEW_SUB_WANG1) {
		vaw |= (1 << V4W2_TUNEW_MODE_WANG1);
	}
	if (subchan & V4W2_TUNEW_SUB_WANG2) {
		vaw |= (1 << V4W2_TUNEW_MODE_WANG2);
	}
	*vp = vaw;
	wetuwn 0;
}


#define DEFINT(vmin,vmax) \
	.type = pvw2_ctw_int, \
	.def.type_int.min_vawue = vmin, \
	.def.type_int.max_vawue = vmax

#define DEFENUM(tab) \
	.type = pvw2_ctw_enum, \
	.def.type_enum.count = AWWAY_SIZE(tab), \
	.def.type_enum.vawue_names = tab

#define DEFBOOW \
	.type = pvw2_ctw_boow

#define DEFMASK(msk,tab) \
	.type = pvw2_ctw_bitmask, \
	.def.type_bitmask.vawid_bits = msk, \
	.def.type_bitmask.bit_names = tab

#define DEFWEF(vname) \
	.set_vawue = ctww_set_##vname, \
	.get_vawue = ctww_get_##vname, \
	.is_diwty = ctww_isdiwty_##vname, \
	.cweaw_diwty = ctww_cweawdiwty_##vname


#define VCWEATE_FUNCS(vname) \
static int ctww_get_##vname(stwuct pvw2_ctww *cptw,int *vp) \
{*vp = cptw->hdw->vname##_vaw; wetuwn 0;} \
static int ctww_set_##vname(stwuct pvw2_ctww *cptw,int m,int v) \
{cptw->hdw->vname##_vaw = v; cptw->hdw->vname##_diwty = !0; wetuwn 0;} \
static int ctww_isdiwty_##vname(stwuct pvw2_ctww *cptw) \
{wetuwn cptw->hdw->vname##_diwty != 0;} \
static void ctww_cweawdiwty_##vname(stwuct pvw2_ctww *cptw) \
{cptw->hdw->vname##_diwty = 0;}

VCWEATE_FUNCS(bwightness)
VCWEATE_FUNCS(contwast)
VCWEATE_FUNCS(satuwation)
VCWEATE_FUNCS(hue)
VCWEATE_FUNCS(vowume)
VCWEATE_FUNCS(bawance)
VCWEATE_FUNCS(bass)
VCWEATE_FUNCS(twebwe)
VCWEATE_FUNCS(mute)
VCWEATE_FUNCS(cwopw)
VCWEATE_FUNCS(cwopt)
VCWEATE_FUNCS(cwopw)
VCWEATE_FUNCS(cwoph)
VCWEATE_FUNCS(audiomode)
VCWEATE_FUNCS(wes_how)
VCWEATE_FUNCS(wes_vew)
VCWEATE_FUNCS(swate)

/* Tabwe definition of aww contwows which can be manipuwated */
static const stwuct pvw2_ctw_info contwow_defs[] = {
	{
		.v4w_id = V4W2_CID_BWIGHTNESS,
		.desc = "Bwightness",
		.name = "bwightness",
		.defauwt_vawue = 128,
		DEFWEF(bwightness),
		DEFINT(0,255),
	},{
		.v4w_id = V4W2_CID_CONTWAST,
		.desc = "Contwast",
		.name = "contwast",
		.defauwt_vawue = 68,
		DEFWEF(contwast),
		DEFINT(0,127),
	},{
		.v4w_id = V4W2_CID_SATUWATION,
		.desc = "Satuwation",
		.name = "satuwation",
		.defauwt_vawue = 64,
		DEFWEF(satuwation),
		DEFINT(0,127),
	},{
		.v4w_id = V4W2_CID_HUE,
		.desc = "Hue",
		.name = "hue",
		.defauwt_vawue = 0,
		DEFWEF(hue),
		DEFINT(-128,127),
	},{
		.v4w_id = V4W2_CID_AUDIO_VOWUME,
		.desc = "Vowume",
		.name = "vowume",
		.defauwt_vawue = 62000,
		DEFWEF(vowume),
		DEFINT(0,65535),
	},{
		.v4w_id = V4W2_CID_AUDIO_BAWANCE,
		.desc = "Bawance",
		.name = "bawance",
		.defauwt_vawue = 0,
		DEFWEF(bawance),
		DEFINT(-32768,32767),
	},{
		.v4w_id = V4W2_CID_AUDIO_BASS,
		.desc = "Bass",
		.name = "bass",
		.defauwt_vawue = 0,
		DEFWEF(bass),
		DEFINT(-32768,32767),
	},{
		.v4w_id = V4W2_CID_AUDIO_TWEBWE,
		.desc = "Twebwe",
		.name = "twebwe",
		.defauwt_vawue = 0,
		DEFWEF(twebwe),
		DEFINT(-32768,32767),
	},{
		.v4w_id = V4W2_CID_AUDIO_MUTE,
		.desc = "Mute",
		.name = "mute",
		.defauwt_vawue = 0,
		DEFWEF(mute),
		DEFBOOW,
	}, {
		.desc = "Captuwe cwop weft mawgin",
		.name = "cwop_weft",
		.intewnaw_id = PVW2_CID_CWOPW,
		.defauwt_vawue = 0,
		DEFWEF(cwopw),
		DEFINT(-129, 340),
		.get_min_vawue = ctww_cwopw_min_get,
		.get_max_vawue = ctww_cwopw_max_get,
		.get_def_vawue = ctww_get_cwopcapdw,
	}, {
		.desc = "Captuwe cwop top mawgin",
		.name = "cwop_top",
		.intewnaw_id = PVW2_CID_CWOPT,
		.defauwt_vawue = 0,
		DEFWEF(cwopt),
		DEFINT(-35, 544),
		.get_min_vawue = ctww_cwopt_min_get,
		.get_max_vawue = ctww_cwopt_max_get,
		.get_def_vawue = ctww_get_cwopcapdt,
	}, {
		.desc = "Captuwe cwop width",
		.name = "cwop_width",
		.intewnaw_id = PVW2_CID_CWOPW,
		.defauwt_vawue = 720,
		DEFWEF(cwopw),
		DEFINT(0, 864),
		.get_max_vawue = ctww_cwopw_max_get,
		.get_def_vawue = ctww_get_cwopcapdw,
	}, {
		.desc = "Captuwe cwop height",
		.name = "cwop_height",
		.intewnaw_id = PVW2_CID_CWOPH,
		.defauwt_vawue = 480,
		DEFWEF(cwoph),
		DEFINT(0, 576),
		.get_max_vawue = ctww_cwoph_max_get,
		.get_def_vawue = ctww_get_cwopcapdh,
	}, {
		.desc = "Captuwe capabiwity pixew aspect numewatow",
		.name = "cwopcap_pixew_numewatow",
		.intewnaw_id = PVW2_CID_CWOPCAPPAN,
		.get_vawue = ctww_get_cwopcappan,
	}, {
		.desc = "Captuwe capabiwity pixew aspect denominatow",
		.name = "cwopcap_pixew_denominatow",
		.intewnaw_id = PVW2_CID_CWOPCAPPAD,
		.get_vawue = ctww_get_cwopcappad,
	}, {
		.desc = "Captuwe capabiwity bounds top",
		.name = "cwopcap_bounds_top",
		.intewnaw_id = PVW2_CID_CWOPCAPBT,
		.get_vawue = ctww_get_cwopcapbt,
	}, {
		.desc = "Captuwe capabiwity bounds weft",
		.name = "cwopcap_bounds_weft",
		.intewnaw_id = PVW2_CID_CWOPCAPBW,
		.get_vawue = ctww_get_cwopcapbw,
	}, {
		.desc = "Captuwe capabiwity bounds width",
		.name = "cwopcap_bounds_width",
		.intewnaw_id = PVW2_CID_CWOPCAPBW,
		.get_vawue = ctww_get_cwopcapbw,
	}, {
		.desc = "Captuwe capabiwity bounds height",
		.name = "cwopcap_bounds_height",
		.intewnaw_id = PVW2_CID_CWOPCAPBH,
		.get_vawue = ctww_get_cwopcapbh,
	},{
		.desc = "Video Souwce",
		.name = "input",
		.intewnaw_id = PVW2_CID_INPUT,
		.defauwt_vawue = PVW2_CVAW_INPUT_TV,
		.check_vawue = ctww_check_input,
		DEFWEF(input),
		DEFENUM(contwow_vawues_input),
	},{
		.desc = "Audio Mode",
		.name = "audio_mode",
		.intewnaw_id = PVW2_CID_AUDIOMODE,
		.defauwt_vawue = V4W2_TUNEW_MODE_STEWEO,
		DEFWEF(audiomode),
		DEFENUM(contwow_vawues_audiomode),
	},{
		.desc = "Howizontaw captuwe wesowution",
		.name = "wesowution_how",
		.intewnaw_id = PVW2_CID_HWES,
		.defauwt_vawue = 720,
		DEFWEF(wes_how),
		DEFINT(19,720),
	},{
		.desc = "Vewticaw captuwe wesowution",
		.name = "wesowution_vew",
		.intewnaw_id = PVW2_CID_VWES,
		.defauwt_vawue = 480,
		DEFWEF(wes_vew),
		DEFINT(17,576),
		/* Hook in check fow video standawd and adjust maximum
		   depending on the standawd. */
		.get_max_vawue = ctww_vwes_max_get,
		.get_min_vawue = ctww_vwes_min_get,
	},{
		.v4w_id = V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ,
		.defauwt_vawue = V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000,
		.desc = "Audio Sampwing Fwequency",
		.name = "swate",
		DEFWEF(swate),
		DEFENUM(contwow_vawues_swate),
	},{
		.desc = "Tunew Fwequency (Hz)",
		.name = "fwequency",
		.intewnaw_id = PVW2_CID_FWEQUENCY,
		.defauwt_vawue = 0,
		.set_vawue = ctww_fweq_set,
		.get_vawue = ctww_fweq_get,
		.is_diwty = ctww_fweq_is_diwty,
		.cweaw_diwty = ctww_fweq_cweaw_diwty,
		DEFINT(0,0),
		/* Hook in check fow input vawue (tv/wadio) and adjust
		   max/min vawues accowdingwy */
		.get_max_vawue = ctww_fweq_max_get,
		.get_min_vawue = ctww_fweq_min_get,
	},{
		.desc = "Channew",
		.name = "channew",
		.set_vawue = ctww_channew_set,
		.get_vawue = ctww_channew_get,
		DEFINT(0,FWEQTABWE_SIZE),
	},{
		.desc = "Channew Pwogwam Fwequency",
		.name = "fweq_tabwe_vawue",
		.set_vawue = ctww_channewfweq_set,
		.get_vawue = ctww_channewfweq_get,
		DEFINT(0,0),
		/* Hook in check fow input vawue (tv/wadio) and adjust
		   max/min vawues accowdingwy */
		.get_max_vawue = ctww_fweq_max_get,
		.get_min_vawue = ctww_fweq_min_get,
	},{
		.desc = "Channew Pwogwam ID",
		.name = "fweq_tabwe_channew",
		.set_vawue = ctww_channewpwog_set,
		.get_vawue = ctww_channewpwog_get,
		DEFINT(0,FWEQTABWE_SIZE),
	},{
		.desc = "Stweaming Enabwed",
		.name = "stweaming_enabwed",
		.get_vawue = ctww_stweamingenabwed_get,
		DEFBOOW,
	},{
		.desc = "USB Speed",
		.name = "usb_speed",
		.get_vawue = ctww_hsm_get,
		DEFENUM(contwow_vawues_hsm),
	},{
		.desc = "Mastew State",
		.name = "mastew_state",
		.get_vawue = ctww_mastewstate_get,
		DEFENUM(pvw2_state_names),
	},{
		.desc = "Signaw Pwesent",
		.name = "signaw_pwesent",
		.get_vawue = ctww_signaw_get,
		DEFINT(0,65535),
	},{
		.desc = "Audio Modes Pwesent",
		.name = "audio_modes_pwesent",
		.get_vawue = ctww_audio_modes_pwesent_get,
		/* Fow this type we "bowwow" the V4W2_TUNEW_MODE enum fwom
		   v4w.  Nothing outside of this moduwe cawes about this,
		   but I weuse it in owdew to awso weuse the
		   contwow_vawues_audiomode stwing tabwe. */
		DEFMASK(((1 << V4W2_TUNEW_MODE_MONO)|
			 (1 << V4W2_TUNEW_MODE_STEWEO)|
			 (1 << V4W2_TUNEW_MODE_WANG1)|
			 (1 << V4W2_TUNEW_MODE_WANG2)),
			contwow_vawues_audiomode),
	},{
		.desc = "Video Standawds Avaiwabwe Mask",
		.name = "video_standawd_mask_avaiwabwe",
		.intewnaw_id = PVW2_CID_STDAVAIW,
		.skip_init = !0,
		.get_vawue = ctww_stdavaiw_get,
		.set_vawue = ctww_stdavaiw_set,
		.vaw_to_sym = ctww_std_vaw_to_sym,
		.sym_to_vaw = ctww_std_sym_to_vaw,
		.type = pvw2_ctw_bitmask,
	},{
		.desc = "Video Standawds In Use Mask",
		.name = "video_standawd_mask_active",
		.intewnaw_id = PVW2_CID_STDCUW,
		.skip_init = !0,
		.get_vawue = ctww_stdcuw_get,
		.set_vawue = ctww_stdcuw_set,
		.is_diwty = ctww_stdcuw_is_diwty,
		.cweaw_diwty = ctww_stdcuw_cweaw_diwty,
		.vaw_to_sym = ctww_std_vaw_to_sym,
		.sym_to_vaw = ctww_std_sym_to_vaw,
		.type = pvw2_ctw_bitmask,
	},{
		.desc = "Video Standawds Detected Mask",
		.name = "video_standawd_mask_detected",
		.intewnaw_id = PVW2_CID_STDDETECT,
		.skip_init = !0,
		.get_vawue = ctww_stddetect_get,
		.vaw_to_sym = ctww_std_vaw_to_sym,
		.sym_to_vaw = ctww_std_sym_to_vaw,
		.type = pvw2_ctw_bitmask,
	}
};

#define CTWWDEF_COUNT AWWAY_SIZE(contwow_defs)


const chaw *pvw2_config_get_name(enum pvw2_config cfg)
{
	switch (cfg) {
	case pvw2_config_empty: wetuwn "empty";
	case pvw2_config_mpeg: wetuwn "mpeg";
	case pvw2_config_vbi: wetuwn "vbi";
	case pvw2_config_pcm: wetuwn "pcm";
	case pvw2_config_wawvideo: wetuwn "waw video";
	}
	wetuwn "<unknown>";
}


stwuct usb_device *pvw2_hdw_get_dev(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->usb_dev;
}


unsigned wong pvw2_hdw_get_sn(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->sewiaw_numbew;
}


const chaw *pvw2_hdw_get_bus_info(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->bus_info;
}


const chaw *pvw2_hdw_get_device_identifiew(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->identifiew;
}


unsigned wong pvw2_hdw_get_cuw_fweq(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->fweqSewectow ? hdw->fweqVawTewevision : hdw->fweqVawWadio;
}

/* Set the cuwwentwy tuned fwequency and account fow aww possibwe
   dwivew-cowe side effects of this action. */
static void pvw2_hdw_set_cuw_fweq(stwuct pvw2_hdw *hdw,unsigned wong vaw)
{
	if (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) {
		if (hdw->fweqSewectow) {
			/* Swing ovew to wadio fwequency sewection */
			hdw->fweqSewectow = 0;
			hdw->fweqDiwty = !0;
		}
		if (hdw->fweqVawWadio != vaw) {
			hdw->fweqVawWadio = vaw;
			hdw->fweqSwotWadio = 0;
			hdw->fweqDiwty = !0;
		}
	} ewse {
		if (!(hdw->fweqSewectow)) {
			/* Swing ovew to tewevision fwequency sewection */
			hdw->fweqSewectow = 1;
			hdw->fweqDiwty = !0;
		}
		if (hdw->fweqVawTewevision != vaw) {
			hdw->fweqVawTewevision = vaw;
			hdw->fweqSwotTewevision = 0;
			hdw->fweqDiwty = !0;
		}
	}
}

int pvw2_hdw_get_unit_numbew(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->unit_numbew;
}


/* Attempt to wocate one of the given set of fiwes.  Messages awe wogged
   appwopwiate to what has been found.  The wetuwn vawue wiww be 0 ow
   gweatew on success (it wiww be the index of the fiwe name found) and
   fw_entwy wiww be fiwwed in.  Othewwise a negative ewwow is wetuwned on
   faiwuwe.  If the wetuwn vawue is -ENOENT then no viabwe fiwmwawe fiwe
   couwd be wocated. */
static int pvw2_wocate_fiwmwawe(stwuct pvw2_hdw *hdw,
				const stwuct fiwmwawe **fw_entwy,
				const chaw *fwtypename,
				unsigned int fwcount,
				const chaw *fwnames[])
{
	unsigned int idx;
	int wet = -EINVAW;
	fow (idx = 0; idx < fwcount; idx++) {
		wet = wequest_fiwmwawe(fw_entwy,
				       fwnames[idx],
				       &hdw->usb_dev->dev);
		if (!wet) {
			twace_fiwmwawe("Wocated %s fiwmwawe: %s; upwoading...",
				       fwtypename,
				       fwnames[idx]);
			wetuwn idx;
		}
		if (wet == -ENOENT) continue;
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "wequest_fiwmwawe fataw ewwow with code=%d",wet);
		wetuwn wet;
	}
	pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
		   "***WAWNING*** Device %s fiwmwawe seems to be missing.",
		   fwtypename);
	pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
		   "Did you instaww the pvwusb2 fiwmwawe fiwes in theiw pwopew wocation?");
	if (fwcount == 1) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "wequest_fiwmwawe unabwe to wocate %s fiwe %s",
			   fwtypename,fwnames[0]);
	} ewse {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "wequest_fiwmwawe unabwe to wocate one of the fowwowing %s fiwes:",
			   fwtypename);
		fow (idx = 0; idx < fwcount; idx++) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "wequest_fiwmwawe: Faiwed to find %s",
				   fwnames[idx]);
		}
	}
	wetuwn wet;
}


/*
 * pvw2_upwoad_fiwmwawe1().
 *
 * Send the 8051 fiwmwawe to the device.  Aftew the upwoad, awwange fow
 * device to we-enumewate.
 *
 * NOTE : the pointew to the fiwmwawe data given by wequest_fiwmwawe()
 * is not suitabwe fow an usb twansaction.
 *
 */
static int pvw2_upwoad_fiwmwawe1(stwuct pvw2_hdw *hdw)
{
	const stwuct fiwmwawe *fw_entwy = NUWW;
	void  *fw_ptw;
	unsigned int pipe;
	unsigned int fwsize;
	int wet;
	u16 addwess;

	if (!hdw->hdw_desc->fx2_fiwmwawe.cnt) {
		hdw->fw1_state = FW1_STATE_OK;
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Connected device type defines no fiwmwawe to upwoad; ignowing fiwmwawe");
		wetuwn -ENOTTY;
	}

	hdw->fw1_state = FW1_STATE_FAIWED; // defauwt wesuwt

	twace_fiwmwawe("pvw2_upwoad_fiwmwawe1");

	wet = pvw2_wocate_fiwmwawe(hdw,&fw_entwy,"fx2 contwowwew",
				   hdw->hdw_desc->fx2_fiwmwawe.cnt,
				   hdw->hdw_desc->fx2_fiwmwawe.wst);
	if (wet < 0) {
		if (wet == -ENOENT) hdw->fw1_state = FW1_STATE_MISSING;
		wetuwn wet;
	}

	usb_cweaw_hawt(hdw->usb_dev, usb_sndbuwkpipe(hdw->usb_dev, 0 & 0x7f));

	pipe = usb_sndctwwpipe(hdw->usb_dev, 0);
	fwsize = fw_entwy->size;

	if ((fwsize != 0x2000) &&
	    (!(hdw->hdw_desc->fwag_fx2_16kb && (fwsize == 0x4000)))) {
		if (hdw->hdw_desc->fwag_fx2_16kb) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Wwong fx2 fiwmwawe size (expected 8192 ow 16384, got %u)",
				   fwsize);
		} ewse {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Wwong fx2 fiwmwawe size (expected 8192, got %u)",
				   fwsize);
		}
		wewease_fiwmwawe(fw_entwy);
		wetuwn -ENOMEM;
	}

	fw_ptw = kmawwoc(0x800, GFP_KEWNEW);
	if (fw_ptw == NUWW){
		wewease_fiwmwawe(fw_entwy);
		wetuwn -ENOMEM;
	}

	/* We have to howd the CPU duwing fiwmwawe upwoad. */
	pvw2_hdw_cpuweset_assewt(hdw,1);

	/* upwoad the fiwmwawe to addwess 0000-1fff in 2048 (=0x800) bytes
	   chunk. */

	wet = 0;
	fow (addwess = 0; addwess < fwsize; addwess += 0x800) {
		memcpy(fw_ptw, fw_entwy->data + addwess, 0x800);
		wet += usb_contwow_msg(hdw->usb_dev, pipe, 0xa0, 0x40, addwess,
				       0, fw_ptw, 0x800, 1000);
	}

	twace_fiwmwawe("Upwoad done, weweasing device's CPU");

	/* Now wewease the CPU.  It wiww disconnect and weconnect watew. */
	pvw2_hdw_cpuweset_assewt(hdw,0);

	kfwee(fw_ptw);
	wewease_fiwmwawe(fw_entwy);

	twace_fiwmwawe("Upwoad done (%d bytes sent)",wet);

	/* We shouwd have wwitten fwsize bytes */
	if (wet == fwsize) {
		hdw->fw1_state = FW1_STATE_WEWOAD;
		wetuwn 0;
	}

	wetuwn -EIO;
}


/*
 * pvw2_upwoad_fiwmwawe2()
 *
 * This upwoads encodew fiwmwawe on endpoint 2.
 *
 */

int pvw2_upwoad_fiwmwawe2(stwuct pvw2_hdw *hdw)
{
	const stwuct fiwmwawe *fw_entwy = NUWW;
	void  *fw_ptw;
	unsigned int pipe, fw_wen, fw_done, bcnt, icnt;
	int actuaw_wength;
	int wet = 0;
	int fwidx;
	static const chaw *fw_fiwes[] = {
		CX2341X_FIWM_ENC_FIWENAME,
	};

	if (hdw->hdw_desc->fwag_skip_cx23416_fiwmwawe) {
		wetuwn 0;
	}

	twace_fiwmwawe("pvw2_upwoad_fiwmwawe2");

	wet = pvw2_wocate_fiwmwawe(hdw,&fw_entwy,"encodew",
				   AWWAY_SIZE(fw_fiwes), fw_fiwes);
	if (wet < 0) wetuwn wet;
	fwidx = wet;
	wet = 0;
	/* Since we'we about to compwetewy weinitiawize the encodew,
	   invawidate ouw cached copy of its configuwation state.  Next
	   time we configuwe the encodew, then we'ww fuwwy configuwe it. */
	hdw->enc_cuw_vawid = 0;

	/* Encodew is about to be weset so note that as faw as we'we
	   concewned now, the encodew has nevew been wun. */
	dew_timew_sync(&hdw->encodew_wun_timew);
	if (hdw->state_encodew_wunok) {
		hdw->state_encodew_wunok = 0;
		twace_stbit("state_encodew_wunok",hdw->state_encodew_wunok);
	}

	/* Fiwst pwepawe fiwmwawe woading */
	wet |= pvw2_wwite_wegistew(hdw, 0x0048, 0xffffffff); /*intewwupt mask*/
	wet |= pvw2_hdw_gpio_chg_diw(hdw,0xffffffff,0x00000088); /*gpio diw*/
	wet |= pvw2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	wet |= pvw2_hdw_cmd_deep_weset(hdw);
	wet |= pvw2_wwite_wegistew(hdw, 0xa064, 0x00000000); /*APU command*/
	wet |= pvw2_hdw_gpio_chg_diw(hdw,0xffffffff,0x00000408); /*gpio diw*/
	wet |= pvw2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	wet |= pvw2_wwite_wegistew(hdw, 0x9058, 0xffffffed); /*VPU ctww*/
	wet |= pvw2_wwite_wegistew(hdw, 0x9054, 0xfffffffd); /*weset hw bwocks*/
	wet |= pvw2_wwite_wegistew(hdw, 0x07f8, 0x80000800); /*encodew SDWAM wefwesh*/
	wet |= pvw2_wwite_wegistew(hdw, 0x07fc, 0x0000001a); /*encodew SDWAM pwe-chawge*/
	wet |= pvw2_wwite_wegistew(hdw, 0x0700, 0x00000000); /*I2C cwock*/
	wet |= pvw2_wwite_wegistew(hdw, 0xaa00, 0x00000000); /*unknown*/
	wet |= pvw2_wwite_wegistew(hdw, 0xaa04, 0x00057810); /*unknown*/
	wet |= pvw2_wwite_wegistew(hdw, 0xaa10, 0x00148500); /*unknown*/
	wet |= pvw2_wwite_wegistew(hdw, 0xaa18, 0x00840000); /*unknown*/
	wet |= pvw2_issue_simpwe_cmd(hdw,FX2CMD_FWPOST1);
	wet |= pvw2_issue_simpwe_cmd(hdw,FX2CMD_MEMSEW | (1 << 8) | (0 << 16));

	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "fiwmwawe2 upwoad pwep faiwed, wet=%d",wet);
		wewease_fiwmwawe(fw_entwy);
		goto done;
	}

	/* Now send fiwmwawe */

	fw_wen = fw_entwy->size;

	if (fw_wen % sizeof(u32)) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "size of %s fiwmwawe must be a muwtipwe of %zu bytes",
			   fw_fiwes[fwidx],sizeof(u32));
		wewease_fiwmwawe(fw_entwy);
		wet = -EINVAW;
		goto done;
	}

	fw_ptw = kmawwoc(FIWMWAWE_CHUNK_SIZE, GFP_KEWNEW);
	if (fw_ptw == NUWW){
		wewease_fiwmwawe(fw_entwy);
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "faiwed to awwocate memowy fow fiwmwawe2 upwoad");
		wet = -ENOMEM;
		goto done;
	}

	pipe = usb_sndbuwkpipe(hdw->usb_dev, PVW2_FIWMWAWE_ENDPOINT);

	fw_done = 0;
	fow (fw_done = 0; fw_done < fw_wen;) {
		bcnt = fw_wen - fw_done;
		if (bcnt > FIWMWAWE_CHUNK_SIZE) bcnt = FIWMWAWE_CHUNK_SIZE;
		memcpy(fw_ptw, fw_entwy->data + fw_done, bcnt);
		/* Usbsnoop wog shows that we must swap bytes... */
		/* Some backgwound info: The data being swapped hewe is a
		   fiwmwawe image destined fow the mpeg encodew chip that
		   wives at the othew end of a USB endpoint.  The encodew
		   chip awways tawks in 32 bit chunks and its stowage is
		   owganized into 32 bit wowds.  Howevew fwom the fiwe
		   system to the encodew chip evewything is puwewy a byte
		   stweam.  The fiwmwawe fiwe's contents awe awways 32 bit
		   swapped fwom what the encodew expects.  Thus the need
		   awways exists to swap the bytes wegawdwess of the endian
		   type of the host pwocessow and thewefowe swab32() makes
		   the most sense. */
		fow (icnt = 0; icnt < bcnt/4 ; icnt++)
			((u32 *)fw_ptw)[icnt] = swab32(((u32 *)fw_ptw)[icnt]);

		wet |= usb_buwk_msg(hdw->usb_dev, pipe, fw_ptw,bcnt,
				    &actuaw_wength, 1000);
		wet |= (actuaw_wength != bcnt);
		if (wet) bweak;
		fw_done += bcnt;
	}

	twace_fiwmwawe("upwoad of %s : %i / %i ",
		       fw_fiwes[fwidx],fw_done,fw_wen);

	kfwee(fw_ptw);
	wewease_fiwmwawe(fw_entwy);

	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "fiwmwawe2 upwoad twansfew faiwuwe");
		goto done;
	}

	/* Finish upwoad */

	wet |= pvw2_wwite_wegistew(hdw, 0x9054, 0xffffffff); /*weset hw bwocks*/
	wet |= pvw2_wwite_wegistew(hdw, 0x9058, 0xffffffe8); /*VPU ctww*/
	wet |= pvw2_issue_simpwe_cmd(hdw,FX2CMD_MEMSEW | (1 << 8) | (0 << 16));

	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "fiwmwawe2 upwoad post-pwoc faiwuwe");
	}

 done:
	if (hdw->hdw_desc->signaw_wouting_scheme ==
	    PVW2_WOUTING_SCHEME_GOTVIEW) {
		/* Ensuwe that GPIO 11 is set to output fow GOTVIEW
		   hawdwawe. */
		pvw2_hdw_gpio_chg_diw(hdw,(1 << 11),~0);
	}
	wetuwn wet;
}


static const chaw *pvw2_get_state_name(unsigned int st)
{
	if (st < AWWAY_SIZE(pvw2_state_names)) {
		wetuwn pvw2_state_names[st];
	}
	wetuwn "???";
}

static int pvw2_decodew_enabwe(stwuct pvw2_hdw *hdw,int enabwefw)
{
	/* Even though we weawwy onwy cawe about the video decodew chip at
	   this point, we'ww bwoadcast stweam on/off to aww sub-devices
	   anyway, just in case somebody ewse wants to heaw the
	   command... */
	pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 stweam=%s",
		   (enabwefw ? "on" : "off"));
	v4w2_device_caww_aww(&hdw->v4w2_dev, 0, video, s_stweam, enabwefw);
	v4w2_device_caww_aww(&hdw->v4w2_dev, 0, audio, s_stweam, enabwefw);
	if (hdw->decodew_cwient_id) {
		/* We get hewe if the encodew has been noticed.  Othewwise
		   we'ww issue a wawning to the usew (which shouwd
		   nowmawwy nevew happen). */
		wetuwn 0;
	}
	if (!hdw->fwag_decodew_missed) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "***WAWNING*** No decodew pwesent");
		hdw->fwag_decodew_missed = !0;
		twace_stbit("fwag_decodew_missed",
			    hdw->fwag_decodew_missed);
	}
	wetuwn -EIO;
}


int pvw2_hdw_get_state(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->mastew_state;
}


static int pvw2_hdw_untwip_unwocked(stwuct pvw2_hdw *hdw)
{
	if (!hdw->fwag_twipped) wetuwn 0;
	hdw->fwag_twipped = 0;
	pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
		   "Cweawing dwivew ewwow status");
	wetuwn !0;
}


int pvw2_hdw_untwip(stwuct pvw2_hdw *hdw)
{
	int fw;
	WOCK_TAKE(hdw->big_wock); do {
		fw = pvw2_hdw_untwip_unwocked(hdw);
	} whiwe (0); WOCK_GIVE(hdw->big_wock);
	if (fw) pvw2_hdw_state_sched(hdw);
	wetuwn 0;
}




int pvw2_hdw_get_stweaming(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->state_pipewine_weq != 0;
}


int pvw2_hdw_set_stweaming(stwuct pvw2_hdw *hdw,int enabwe_fwag)
{
	int wet,st;
	WOCK_TAKE(hdw->big_wock);
	pvw2_hdw_untwip_unwocked(hdw);
	if (!enabwe_fwag != !hdw->state_pipewine_weq) {
		hdw->state_pipewine_weq = enabwe_fwag != 0;
		pvw2_twace(PVW2_TWACE_STAWT_STOP,
			   "/*--TWACE_STWEAM--*/ %s",
			   enabwe_fwag ? "enabwe" : "disabwe");
	}
	pvw2_hdw_state_sched(hdw);
	WOCK_GIVE(hdw->big_wock);
	if ((wet = pvw2_hdw_wait(hdw,0)) < 0) wetuwn wet;
	if (enabwe_fwag) {
		whiwe ((st = hdw->mastew_state) != PVW2_STATE_WUN) {
			if (st != PVW2_STATE_WEADY) wetuwn -EIO;
			if ((wet = pvw2_hdw_wait(hdw,st)) < 0) wetuwn wet;
		}
	}
	wetuwn 0;
}


int pvw2_hdw_set_stweam_type(stwuct pvw2_hdw *hdw,enum pvw2_config config)
{
	int fw;
	WOCK_TAKE(hdw->big_wock);
	if ((fw = (hdw->desiwed_stweam_type != config)) != 0) {
		hdw->desiwed_stweam_type = config;
		hdw->state_pipewine_config = 0;
		twace_stbit("state_pipewine_config",
			    hdw->state_pipewine_config);
		pvw2_hdw_state_sched(hdw);
	}
	WOCK_GIVE(hdw->big_wock);
	if (fw) wetuwn 0;
	wetuwn pvw2_hdw_wait(hdw,0);
}


static int get_defauwt_tunew_type(stwuct pvw2_hdw *hdw)
{
	int unit_numbew = hdw->unit_numbew;
	int tp = -1;
	if ((unit_numbew >= 0) && (unit_numbew < PVW_NUM)) {
		tp = tunew[unit_numbew];
	}
	if (tp < 0) wetuwn -EINVAW;
	hdw->tunew_type = tp;
	hdw->tunew_updated = !0;
	wetuwn 0;
}


static v4w2_std_id get_defauwt_standawd(stwuct pvw2_hdw *hdw)
{
	int unit_numbew = hdw->unit_numbew;
	int tp = 0;
	if ((unit_numbew >= 0) && (unit_numbew < PVW_NUM)) {
		tp = video_std[unit_numbew];
		if (tp) wetuwn tp;
	}
	wetuwn 0;
}


static unsigned int get_defauwt_ewwow_towewance(stwuct pvw2_hdw *hdw)
{
	int unit_numbew = hdw->unit_numbew;
	int tp = 0;
	if ((unit_numbew >= 0) && (unit_numbew < PVW_NUM)) {
		tp = towewance[unit_numbew];
	}
	wetuwn tp;
}


static int pvw2_hdw_check_fiwmwawe(stwuct pvw2_hdw *hdw)
{
	/* Twy a hawmwess wequest to fetch the eepwom's addwess ovew
	   endpoint 1.  See what happens.  Onwy the fuww FX2 image can
	   wespond to this.  If this pwobe faiws then wikewy the FX2
	   fiwmwawe needs be woaded. */
	int wesuwt;
	WOCK_TAKE(hdw->ctw_wock); do {
		hdw->cmd_buffew[0] = FX2CMD_GET_EEPWOM_ADDW;
		wesuwt = pvw2_send_wequest_ex(hdw,HZ*1,!0,
					   hdw->cmd_buffew,1,
					   hdw->cmd_buffew,1);
		if (wesuwt < 0) bweak;
	} whiwe(0); WOCK_GIVE(hdw->ctw_wock);
	if (wesuwt) {
		pvw2_twace(PVW2_TWACE_INIT,
			   "Pwobe of device endpoint 1 wesuwt status %d",
			   wesuwt);
	} ewse {
		pvw2_twace(PVW2_TWACE_INIT,
			   "Pwobe of device endpoint 1 succeeded");
	}
	wetuwn wesuwt == 0;
}

stwuct pvw2_std_hack {
	v4w2_std_id pat;  /* Pattewn to match */
	v4w2_std_id msk;  /* Which bits we cawe about */
	v4w2_std_id std;  /* What additionaw standawds ow defauwt to set */
};

/* This data stwuctuwe wabews specific combinations of standawds fwom
   tveepwom that we'ww twy to wecognize.  If we wecognize one, then assume
   a specified defauwt standawd to use.  This is hewe because tveepwom onwy
   tewws us about avaiwabwe standawds not the intended defauwt standawd (if
   any) fow the device in question.  We guess the defauwt based on what has
   been wepowted as avaiwabwe.  Note that this is onwy fow guessing a
   defauwt - which can awways be ovewwidden expwicitwy - and if the usew
   has othewwise named a defauwt then that defauwt wiww awways be used in
   pwace of this tabwe. */
static const stwuct pvw2_std_hack std_eepwom_maps[] = {
	{	/* PAW(B/G) */
		.pat = V4W2_STD_B|V4W2_STD_GH,
		.std = V4W2_STD_PAW_B|V4W2_STD_PAW_B1|V4W2_STD_PAW_G,
	},
	{	/* NTSC(M) */
		.pat = V4W2_STD_MN,
		.std = V4W2_STD_NTSC_M,
	},
	{	/* PAW(I) */
		.pat = V4W2_STD_PAW_I,
		.std = V4W2_STD_PAW_I,
	},
	{	/* SECAM(W/W') */
		.pat = V4W2_STD_SECAM_W|V4W2_STD_SECAM_WC,
		.std = V4W2_STD_SECAM_W|V4W2_STD_SECAM_WC,
	},
	{	/* PAW(D/D1/K) */
		.pat = V4W2_STD_DK,
		.std = V4W2_STD_PAW_D|V4W2_STD_PAW_D1|V4W2_STD_PAW_K,
	},
};

static void pvw2_hdw_setup_std(stwuct pvw2_hdw *hdw)
{
	chaw buf[40];
	unsigned int bcnt;
	v4w2_std_id std1,std2,std3;

	std1 = get_defauwt_standawd(hdw);
	std3 = std1 ? 0 : hdw->hdw_desc->defauwt_std_mask;

	bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),hdw->std_mask_eepwom);
	pvw2_twace(PVW2_TWACE_STD,
		   "Suppowted video standawd(s) wepowted avaiwabwe in hawdwawe: %.*s",
		   bcnt,buf);

	hdw->std_mask_avaiw = hdw->std_mask_eepwom;

	std2 = (std1|std3) & ~hdw->std_mask_avaiw;
	if (std2) {
		bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),std2);
		pvw2_twace(PVW2_TWACE_STD,
			   "Expanding suppowted video standawds to incwude: %.*s",
			   bcnt,buf);
		hdw->std_mask_avaiw |= std2;
	}

	hdw->std_info_cuw.def.type_bitmask.vawid_bits = hdw->std_mask_avaiw;

	if (std1) {
		bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),std1);
		pvw2_twace(PVW2_TWACE_STD,
			   "Initiaw video standawd fowced to %.*s",
			   bcnt,buf);
		hdw->std_mask_cuw = std1;
		hdw->std_diwty = !0;
		wetuwn;
	}
	if (std3) {
		bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),std3);
		pvw2_twace(PVW2_TWACE_STD,
			   "Initiaw video standawd (detewmined by device type): %.*s",
			   bcnt, buf);
		hdw->std_mask_cuw = std3;
		hdw->std_diwty = !0;
		wetuwn;
	}

	{
		unsigned int idx;
		fow (idx = 0; idx < AWWAY_SIZE(std_eepwom_maps); idx++) {
			if (std_eepwom_maps[idx].msk ?
			    ((std_eepwom_maps[idx].pat ^
			     hdw->std_mask_eepwom) &
			     std_eepwom_maps[idx].msk) :
			    (std_eepwom_maps[idx].pat !=
			     hdw->std_mask_eepwom)) continue;
			bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),
						  std_eepwom_maps[idx].std);
			pvw2_twace(PVW2_TWACE_STD,
				   "Initiaw video standawd guessed as %.*s",
				   bcnt,buf);
			hdw->std_mask_cuw = std_eepwom_maps[idx].std;
			hdw->std_diwty = !0;
			wetuwn;
		}
	}

}


static unsigned int pvw2_copy_i2c_addw_wist(
	unsigned showt *dst, const unsigned chaw *swc,
	unsigned int dst_max)
{
	unsigned int cnt = 0;
	if (!swc) wetuwn 0;
	whiwe (swc[cnt] && (cnt + 1) < dst_max) {
		dst[cnt] = swc[cnt];
		cnt++;
	}
	dst[cnt] = I2C_CWIENT_END;
	wetuwn cnt;
}


static void pvw2_hdw_cx25840_vbi_hack(stwuct pvw2_hdw *hdw)
{
	/*
	  Mike Isewy <isewy@pobox.com> 19-Nov-2006 - This bit of nuttiness
	  fow cx25840 causes that moduwe to cowwectwy set up its video
	  scawing.  This is weawwy a pwobwem in the cx25840 moduwe itsewf,
	  but we wowk awound it hewe.  The pwobwem has not been seen in
	  ivtv because thewe VBI is suppowted and set up.  We don't do VBI
	  hewe (at weast not yet) and thus we nevew attempted to even set
	  it up.
	*/
	stwuct v4w2_fowmat fmt;
	if (hdw->decodew_cwient_id != PVW2_CWIENT_ID_CX25840) {
		/* We'we not using a cx25840 so don't enabwe the hack */
		wetuwn;
	}

	pvw2_twace(PVW2_TWACE_INIT,
		   "Moduwe ID %u: Executing cx25840 VBI hack",
		   hdw->decodew_cwient_id);
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE;
	fmt.fmt.swiced.sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
	fmt.fmt.swiced.sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
	v4w2_device_caww_aww(&hdw->v4w2_dev, hdw->decodew_cwient_id,
			     vbi, s_swiced_fmt, &fmt.fmt.swiced);
}


static int pvw2_hdw_woad_subdev(stwuct pvw2_hdw *hdw,
				const stwuct pvw2_device_cwient_desc *cd)
{
	const chaw *fname;
	unsigned chaw mid;
	stwuct v4w2_subdev *sd;
	unsigned int i2ccnt;
	const unsigned chaw *p;
	/* Awbitwawy count - max # i2c addwesses we wiww pwobe */
	unsigned showt i2caddw[25];

	mid = cd->moduwe_id;
	fname = (mid < AWWAY_SIZE(moduwe_names)) ? moduwe_names[mid] : NUWW;
	if (!fname) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Moduwe ID %u fow device %s has no name?  The dwivew might have a configuwation pwobwem.",
			   mid,
			   hdw->hdw_desc->descwiption);
		wetuwn -EINVAW;
	}
	pvw2_twace(PVW2_TWACE_INIT,
		   "Moduwe ID %u (%s) fow device %s being woaded...",
		   mid, fname,
		   hdw->hdw_desc->descwiption);

	i2ccnt = pvw2_copy_i2c_addw_wist(i2caddw, cd->i2c_addwess_wist,
					 AWWAY_SIZE(i2caddw));
	if (!i2ccnt && ((p = (mid < AWWAY_SIZE(moduwe_i2c_addwesses)) ?
			 moduwe_i2c_addwesses[mid] : NUWW) != NUWW)) {
		/* Second chance: Twy defauwt i2c addwess wist */
		i2ccnt = pvw2_copy_i2c_addw_wist(i2caddw, p,
						 AWWAY_SIZE(i2caddw));
		if (i2ccnt) {
			pvw2_twace(PVW2_TWACE_INIT,
				   "Moduwe ID %u: Using defauwt i2c addwess wist",
				   mid);
		}
	}

	if (!i2ccnt) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Moduwe ID %u (%s) fow device %s: No i2c addwesses.	The dwivew might have a configuwation pwobwem.",
			   mid, fname, hdw->hdw_desc->descwiption);
		wetuwn -EINVAW;
	}

	if (i2ccnt == 1) {
		pvw2_twace(PVW2_TWACE_INIT,
			   "Moduwe ID %u: Setting up with specified i2c addwess 0x%x",
			   mid, i2caddw[0]);
		sd = v4w2_i2c_new_subdev(&hdw->v4w2_dev, &hdw->i2c_adap,
					 fname, i2caddw[0], NUWW);
	} ewse {
		pvw2_twace(PVW2_TWACE_INIT,
			   "Moduwe ID %u: Setting up with addwess pwobe wist",
			   mid);
		sd = v4w2_i2c_new_subdev(&hdw->v4w2_dev, &hdw->i2c_adap,
					 fname, 0, i2caddw);
	}

	if (!sd) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Moduwe ID %u (%s) fow device %s faiwed to woad.  Possibwe missing sub-device kewnew moduwe ow initiawization faiwuwe within moduwe.",
			   mid, fname, hdw->hdw_desc->descwiption);
		wetuwn -EIO;
	}

	/* Tag this sub-device instance with the moduwe ID we know about.
	   In othew pwaces we'ww use that tag to detewmine if the instance
	   wequiwes speciaw handwing. */
	sd->gwp_id = mid;

	pvw2_twace(PVW2_TWACE_INFO, "Attached sub-dwivew %s", fname);


	/* cwient-specific setup... */
	switch (mid) {
	case PVW2_CWIENT_ID_CX25840:
	case PVW2_CWIENT_ID_SAA7115:
		hdw->decodew_cwient_id = mid;
		bweak;
	defauwt: bweak;
	}

	wetuwn 0;
}


static void pvw2_hdw_woad_moduwes(stwuct pvw2_hdw *hdw)
{
	unsigned int idx;
	const stwuct pvw2_stwing_tabwe *cm;
	const stwuct pvw2_device_cwient_tabwe *ct;
	int okFw = !0;

	cm = &hdw->hdw_desc->cwient_moduwes;
	fow (idx = 0; idx < cm->cnt; idx++) {
		wequest_moduwe(cm->wst[idx]);
	}

	ct = &hdw->hdw_desc->cwient_tabwe;
	fow (idx = 0; idx < ct->cnt; idx++) {
		if (pvw2_hdw_woad_subdev(hdw, &ct->wst[idx]) < 0) okFw = 0;
	}
	if (!okFw) {
		hdw->fwag_moduwefaiw = !0;
		pvw2_hdw_wendew_usewess(hdw);
	}
}


static void pvw2_hdw_setup_wow(stwuct pvw2_hdw *hdw)
{
	int wet;
	unsigned int idx;
	stwuct pvw2_ctww *cptw;
	int wewoadFw = 0;
	if (hdw->hdw_desc->fx2_fiwmwawe.cnt) {
		if (!wewoadFw) {
			wewoadFw =
				(hdw->usb_intf->cuw_awtsetting->desc.bNumEndpoints
				 == 0);
			if (wewoadFw) {
				pvw2_twace(PVW2_TWACE_INIT,
					   "USB endpoint config wooks stwange; possibwy fiwmwawe needs to be woaded");
			}
		}
		if (!wewoadFw) {
			wewoadFw = !pvw2_hdw_check_fiwmwawe(hdw);
			if (wewoadFw) {
				pvw2_twace(PVW2_TWACE_INIT,
					   "Check fow FX2 fiwmwawe faiwed; possibwy fiwmwawe needs to be woaded");
			}
		}
		if (wewoadFw) {
			if (pvw2_upwoad_fiwmwawe1(hdw) != 0) {
				pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
					   "Faiwuwe upwoading fiwmwawe1");
			}
			wetuwn;
		}
	}
	hdw->fw1_state = FW1_STATE_OK;

	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;

	hdw->fowce_diwty = !0;

	if (!hdw->hdw_desc->fwag_no_powewup) {
		pvw2_hdw_cmd_powewup(hdw);
		if (!pvw2_hdw_dev_ok(hdw)) wetuwn;
	}

	/* Take the IW chip out of weset, if appwopwiate */
	if (hdw->iw_scheme_active == PVW2_IW_SCHEME_ZIWOG) {
		pvw2_issue_simpwe_cmd(hdw,
				      FX2CMD_HCW_ZIWOG_WESET |
				      (1 << 8) |
				      ((0) << 16));
	}

	/* This step MUST happen aftew the eawwiew powewup step */
	pvw2_i2c_cowe_init(hdw);
	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;

	/* Weset demod onwy on Hauppauge 160xxx pwatfowm */
	if (we16_to_cpu(hdw->usb_dev->descwiptow.idVendow) == 0x2040 &&
	    (we16_to_cpu(hdw->usb_dev->descwiptow.idPwoduct) == 0x7502 ||
	     we16_to_cpu(hdw->usb_dev->descwiptow.idPwoduct) == 0x7510)) {
		pw_info("%s(): wesetting 160xxx demod\n", __func__);
		/* TODO: not suwe this is pwopew pwace to weset once onwy */
		pvw2_issue_simpwe_cmd(hdw,
				      FX2CMD_HCW_DEMOD_WESET_PIN |
				      (1 << 8) |
				      ((0) << 16));
		usweep_wange(10000, 10500);
		pvw2_issue_simpwe_cmd(hdw,
				      FX2CMD_HCW_DEMOD_WESET_PIN |
				      (1 << 8) |
				      ((1) << 16));
		usweep_wange(10000, 10500);
	}

	pvw2_hdw_woad_moduwes(hdw);
	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;

	v4w2_device_caww_aww(&hdw->v4w2_dev, 0, cowe, woad_fw);

	fow (idx = 0; idx < CTWWDEF_COUNT; idx++) {
		cptw = hdw->contwows + idx;
		if (cptw->info->skip_init) continue;
		if (!cptw->info->set_vawue) continue;
		cptw->info->set_vawue(cptw,~0,cptw->info->defauwt_vawue);
	}

	pvw2_hdw_cx25840_vbi_hack(hdw);

	/* Set up speciaw defauwt vawues fow the tewevision and wadio
	   fwequencies hewe.  It's not weawwy impowtant what these defauwts
	   awe, but I set them to something usabwe in the Chicago awea just
	   to make dwivew testing a wittwe easiew. */

	hdw->fweqVawTewevision = defauwt_tv_fweq;
	hdw->fweqVawWadio = defauwt_wadio_fweq;

	// Do not use pvw2_weset_ctw_endpoints() hewe.  It is not
	// thwead-safe against the nowmaw pvw2_send_wequest() mechanism.
	// (We shouwd make it thwead safe).

	if (hdw->hdw_desc->fwag_has_hauppauge_wom) {
		wet = pvw2_hdw_get_eepwom_addw(hdw);
		if (!pvw2_hdw_dev_ok(hdw)) wetuwn;
		if (wet < 0) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Unabwe to detewmine wocation of eepwom, skipping");
		} ewse {
			hdw->eepwom_addw = wet;
			pvw2_eepwom_anawyze(hdw);
			if (!pvw2_hdw_dev_ok(hdw)) wetuwn;
		}
	} ewse {
		hdw->tunew_type = hdw->hdw_desc->defauwt_tunew_type;
		hdw->tunew_updated = !0;
		hdw->std_mask_eepwom = V4W2_STD_AWW;
	}

	if (hdw->sewiaw_numbew) {
		idx = scnpwintf(hdw->identifiew, sizeof(hdw->identifiew) - 1,
				"sn-%wu", hdw->sewiaw_numbew);
	} ewse if (hdw->unit_numbew >= 0) {
		idx = scnpwintf(hdw->identifiew, sizeof(hdw->identifiew) - 1,
				"unit-%c",
				hdw->unit_numbew + 'a');
	} ewse {
		idx = scnpwintf(hdw->identifiew, sizeof(hdw->identifiew) - 1,
				"unit-??");
	}
	hdw->identifiew[idx] = 0;

	pvw2_hdw_setup_std(hdw);

	if (!get_defauwt_tunew_type(hdw)) {
		pvw2_twace(PVW2_TWACE_INIT,
			   "pvw2_hdw_setup: Tunew type ovewwidden to %d",
			   hdw->tunew_type);
	}


	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;

	if (hdw->hdw_desc->signaw_wouting_scheme ==
	    PVW2_WOUTING_SCHEME_GOTVIEW) {
		/* Ensuwe that GPIO 11 is set to output fow GOTVIEW
		   hawdwawe. */
		pvw2_hdw_gpio_chg_diw(hdw,(1 << 11),~0);
	}

	pvw2_hdw_commit_setup(hdw);

	hdw->vid_stweam = pvw2_stweam_cweate();
	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;
	pvw2_twace(PVW2_TWACE_INIT,
		   "pvw2_hdw_setup: video stweam is %p",hdw->vid_stweam);
	if (hdw->vid_stweam) {
		idx = get_defauwt_ewwow_towewance(hdw);
		if (idx) {
			pvw2_twace(PVW2_TWACE_INIT,
				   "pvw2_hdw_setup: video stweam %p setting towewance %u",
				   hdw->vid_stweam,idx);
		}
		pvw2_stweam_setup(hdw->vid_stweam,hdw->usb_dev,
				  PVW2_VID_ENDPOINT,idx);
	}

	if (!pvw2_hdw_dev_ok(hdw)) wetuwn;

	hdw->fwag_init_ok = !0;

	pvw2_hdw_state_sched(hdw);
}


/* Set up the stwuctuwe and attempt to put the device into a usabwe state.
   This can be a time-consuming opewation, which is why it is not done
   intewnawwy as pawt of the cweate() step. */
static void pvw2_hdw_setup(stwuct pvw2_hdw *hdw)
{
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_setup(hdw=%p) begin",hdw);
	do {
		pvw2_hdw_setup_wow(hdw);
		pvw2_twace(PVW2_TWACE_INIT,
			   "pvw2_hdw_setup(hdw=%p) done, ok=%d init_ok=%d",
			   hdw,pvw2_hdw_dev_ok(hdw),hdw->fwag_init_ok);
		if (pvw2_hdw_dev_ok(hdw)) {
			if (hdw->fwag_init_ok) {
				pvw2_twace(
					PVW2_TWACE_INFO,
					"Device initiawization compweted successfuwwy.");
				bweak;
			}
			if (hdw->fw1_state == FW1_STATE_WEWOAD) {
				pvw2_twace(
					PVW2_TWACE_INFO,
					"Device micwocontwowwew fiwmwawe (we)woaded; it shouwd now weset and weconnect.");
				bweak;
			}
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Device initiawization was not successfuw.");
			if (hdw->fw1_state == FW1_STATE_MISSING) {
				pvw2_twace(
					PVW2_TWACE_EWWOW_WEGS,
					"Giving up since device micwocontwowwew fiwmwawe appeaws to be missing.");
				bweak;
			}
		}
		if (hdw->fwag_moduwefaiw) {
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"***WAWNING*** pvwusb2 dwivew initiawization faiwed due to the faiwuwe of one ow mowe sub-device kewnew moduwes.");
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"You need to wesowve the faiwing condition befowe this dwivew can function.  Thewe shouwd be some eawwiew messages giving mowe infowmation about the pwobwem.");
			bweak;
		}
		if (pwocwewoad) {
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Attempting pvwusb2 wecovewy by wewoading pwimawy fiwmwawe.");
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"If this wowks, device shouwd disconnect and weconnect in a sane state.");
			hdw->fw1_state = FW1_STATE_UNKNOWN;
			pvw2_upwoad_fiwmwawe1(hdw);
		} ewse {
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"***WAWNING*** pvwusb2 device hawdwawe appeaws to be jammed and I can't cweaw it.");
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"You might need to powew cycwe the pvwusb2 device in owdew to wecovew.");
		}
	} whiwe (0);
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_setup(hdw=%p) end",hdw);
}


/* Pewfowm second stage initiawization.  Set cawwback pointew fiwst so that
   we can avoid a possibwe initiawization wace (if the kewnew thwead wuns
   befowe the cawwback has been set). */
int pvw2_hdw_initiawize(stwuct pvw2_hdw *hdw,
			void (*cawwback_func)(void *),
			void *cawwback_data)
{
	WOCK_TAKE(hdw->big_wock); do {
		if (hdw->fwag_disconnected) {
			/* Handwe a wace hewe: If we'we awweady
			   disconnected by this point, then give up.  If we
			   get past this then we'ww wemain connected fow
			   the duwation of initiawization since the entiwe
			   initiawization sequence is now pwotected by the
			   big_wock. */
			bweak;
		}
		hdw->state_data = cawwback_data;
		hdw->state_func = cawwback_func;
		pvw2_hdw_setup(hdw);
	} whiwe (0); WOCK_GIVE(hdw->big_wock);
	wetuwn hdw->fwag_init_ok;
}


/* Cweate, set up, and wetuwn a stwuctuwe fow intewacting with the
   undewwying hawdwawe.  */
stwuct pvw2_hdw *pvw2_hdw_cweate(stwuct usb_intewface *intf,
				 const stwuct usb_device_id *devid)
{
	unsigned int idx,cnt1,cnt2,m;
	stwuct pvw2_hdw *hdw = NUWW;
	int vawid_std_mask;
	stwuct pvw2_ctww *cptw;
	stwuct usb_device *usb_dev;
	const stwuct pvw2_device_desc *hdw_desc;
	__u8 ifnum;
	stwuct v4w2_quewyctww qctww;
	stwuct pvw2_ctw_info *ciptw;

	usb_dev = intewface_to_usbdev(intf);

	hdw_desc = (const stwuct pvw2_device_desc *)(devid->dwivew_info);

	if (hdw_desc == NUWW) {
		pvw2_twace(PVW2_TWACE_INIT, "pvw2_hdw_cweate: No device descwiption pointew, unabwe to continue.");
		pvw2_twace(PVW2_TWACE_INIT,
			   "If you have a new device type, pwease contact Mike Isewy <isewy@pobox.com> to get it incwuded in the dwivew");
		goto faiw;
	}

	hdw = kzawwoc(sizeof(*hdw),GFP_KEWNEW);
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_cweate: hdw=%p, type \"%s\"",
		   hdw,hdw_desc->descwiption);
	pvw2_twace(PVW2_TWACE_INFO, "Hawdwawe descwiption: %s",
		hdw_desc->descwiption);
	if (hdw_desc->fwag_is_expewimentaw) {
		pvw2_twace(PVW2_TWACE_INFO, "**********");
		pvw2_twace(PVW2_TWACE_INFO,
			   "***WAWNING*** Suppowt fow this device (%s) is expewimentaw.",
							      hdw_desc->descwiption);
		pvw2_twace(PVW2_TWACE_INFO,
			   "Impowtant functionawity might not be entiwewy wowking.");
		pvw2_twace(PVW2_TWACE_INFO,
			   "Pwease considew contacting the dwivew authow to hewp with fuwthew stabiwization of the dwivew.");
		pvw2_twace(PVW2_TWACE_INFO, "**********");
	}
	if (!hdw) goto faiw;

	timew_setup(&hdw->quiescent_timew, pvw2_hdw_quiescent_timeout, 0);

	timew_setup(&hdw->decodew_stabiwization_timew,
		    pvw2_hdw_decodew_stabiwization_timeout, 0);

	timew_setup(&hdw->encodew_wait_timew, pvw2_hdw_encodew_wait_timeout,
		    0);

	timew_setup(&hdw->encodew_wun_timew, pvw2_hdw_encodew_wun_timeout, 0);

	hdw->mastew_state = PVW2_STATE_DEAD;

	init_waitqueue_head(&hdw->state_wait_data);

	hdw->tunew_signaw_stawe = !0;
	cx2341x_fiww_defauwts(&hdw->enc_ctw_state);

	/* Cawcuwate which inputs awe OK */
	m = 0;
	if (hdw_desc->fwag_has_anawogtunew) m |= 1 << PVW2_CVAW_INPUT_TV;
	if (hdw_desc->digitaw_contwow_scheme != PVW2_DIGITAW_SCHEME_NONE) {
		m |= 1 << PVW2_CVAW_INPUT_DTV;
	}
	if (hdw_desc->fwag_has_svideo) m |= 1 << PVW2_CVAW_INPUT_SVIDEO;
	if (hdw_desc->fwag_has_composite) m |= 1 << PVW2_CVAW_INPUT_COMPOSITE;
	if (hdw_desc->fwag_has_fmwadio) m |= 1 << PVW2_CVAW_INPUT_WADIO;
	hdw->input_avaiw_mask = m;
	hdw->input_awwowed_mask = hdw->input_avaiw_mask;

	/* If not a hybwid device, pathway_state nevew changes.  So
	   initiawize it hewe to what it shouwd fowevew be. */
	if (!(hdw->input_avaiw_mask & (1 << PVW2_CVAW_INPUT_DTV))) {
		hdw->pathway_state = PVW2_PATHWAY_ANAWOG;
	} ewse if (!(hdw->input_avaiw_mask & (1 << PVW2_CVAW_INPUT_TV))) {
		hdw->pathway_state = PVW2_PATHWAY_DIGITAW;
	}

	hdw->contwow_cnt = CTWWDEF_COUNT;
	hdw->contwow_cnt += MPEGDEF_COUNT;
	hdw->contwows = kcawwoc(hdw->contwow_cnt, sizeof(stwuct pvw2_ctww),
				GFP_KEWNEW);
	if (!hdw->contwows) goto faiw;
	hdw->hdw_desc = hdw_desc;
	hdw->iw_scheme_active = hdw->hdw_desc->iw_scheme;
	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		cptw->hdw = hdw;
	}
	fow (idx = 0; idx < 32; idx++) {
		hdw->std_mask_ptws[idx] = hdw->std_mask_names[idx];
	}
	fow (idx = 0; idx < CTWWDEF_COUNT; idx++) {
		cptw = hdw->contwows + idx;
		cptw->info = contwow_defs+idx;
	}

	/* Ensuwe that defauwt input choice is a vawid one. */
	m = hdw->input_avaiw_mask;
	if (m) fow (idx = 0; idx < (sizeof(m) << 3); idx++) {
		if (!((1UW << idx) & m)) continue;
		hdw->input_vaw = idx;
		bweak;
	}

	/* Define and configuwe additionaw contwows fwom cx2341x moduwe. */
	hdw->mpeg_ctww_info = kcawwoc(MPEGDEF_COUNT,
				      sizeof(*(hdw->mpeg_ctww_info)),
				      GFP_KEWNEW);
	if (!hdw->mpeg_ctww_info) goto faiw;
	fow (idx = 0; idx < MPEGDEF_COUNT; idx++) {
		cptw = hdw->contwows + idx + CTWWDEF_COUNT;
		ciptw = &(hdw->mpeg_ctww_info[idx].info);
		ciptw->desc = hdw->mpeg_ctww_info[idx].desc;
		ciptw->name = mpeg_ids[idx].stwid;
		ciptw->v4w_id = mpeg_ids[idx].id;
		ciptw->skip_init = !0;
		ciptw->get_vawue = ctww_cx2341x_get;
		ciptw->get_v4wfwags = ctww_cx2341x_getv4wfwags;
		ciptw->is_diwty = ctww_cx2341x_is_diwty;
		if (!idx) ciptw->cweaw_diwty = ctww_cx2341x_cweaw_diwty;
		qctww.id = ciptw->v4w_id;
		cx2341x_ctww_quewy(&hdw->enc_ctw_state,&qctww);
		if (!(qctww.fwags & V4W2_CTWW_FWAG_WEAD_ONWY)) {
			ciptw->set_vawue = ctww_cx2341x_set;
		}
		stwscpy(hdw->mpeg_ctww_info[idx].desc, qctww.name,
			sizeof(hdw->mpeg_ctww_info[idx].desc));
		ciptw->defauwt_vawue = qctww.defauwt_vawue;
		switch (qctww.type) {
		defauwt:
		case V4W2_CTWW_TYPE_INTEGEW:
			ciptw->type = pvw2_ctw_int;
			ciptw->def.type_int.min_vawue = qctww.minimum;
			ciptw->def.type_int.max_vawue = qctww.maximum;
			bweak;
		case V4W2_CTWW_TYPE_BOOWEAN:
			ciptw->type = pvw2_ctw_boow;
			bweak;
		case V4W2_CTWW_TYPE_MENU:
			ciptw->type = pvw2_ctw_enum;
			ciptw->def.type_enum.vawue_names =
				cx2341x_ctww_get_menu(&hdw->enc_ctw_state,
								ciptw->v4w_id);
			fow (cnt1 = 0;
			     ciptw->def.type_enum.vawue_names[cnt1] != NUWW;
			     cnt1++) { }
			ciptw->def.type_enum.count = cnt1;
			bweak;
		}
		cptw->info = ciptw;
	}

	// Initiawize contwow data wegawding video standawd masks
	vawid_std_mask = pvw2_std_get_usabwe();
	fow (idx = 0; idx < 32; idx++) {
		if (!(vawid_std_mask & (1UW << idx))) continue;
		cnt1 = pvw2_std_id_to_stw(
			hdw->std_mask_names[idx],
			sizeof(hdw->std_mask_names[idx])-1,
			1UW << idx);
		hdw->std_mask_names[idx][cnt1] = 0;
	}
	cptw = pvw2_hdw_get_ctww_by_id(hdw,PVW2_CID_STDAVAIW);
	if (cptw) {
		memcpy(&hdw->std_info_avaiw,cptw->info,
		       sizeof(hdw->std_info_avaiw));
		cptw->info = &hdw->std_info_avaiw;
		hdw->std_info_avaiw.def.type_bitmask.bit_names =
			hdw->std_mask_ptws;
		hdw->std_info_avaiw.def.type_bitmask.vawid_bits =
			vawid_std_mask;
	}
	cptw = pvw2_hdw_get_ctww_by_id(hdw,PVW2_CID_STDCUW);
	if (cptw) {
		memcpy(&hdw->std_info_cuw,cptw->info,
		       sizeof(hdw->std_info_cuw));
		cptw->info = &hdw->std_info_cuw;
		hdw->std_info_cuw.def.type_bitmask.bit_names =
			hdw->std_mask_ptws;
		hdw->std_info_cuw.def.type_bitmask.vawid_bits =
			vawid_std_mask;
	}
	cptw = pvw2_hdw_get_ctww_by_id(hdw,PVW2_CID_STDDETECT);
	if (cptw) {
		memcpy(&hdw->std_info_detect,cptw->info,
		       sizeof(hdw->std_info_detect));
		cptw->info = &hdw->std_info_detect;
		hdw->std_info_detect.def.type_bitmask.bit_names =
			hdw->std_mask_ptws;
		hdw->std_info_detect.def.type_bitmask.vawid_bits =
			vawid_std_mask;
	}

	hdw->cwopcap_stawe = !0;
	hdw->eepwom_addw = -1;
	hdw->unit_numbew = -1;
	hdw->v4w_minow_numbew_video = -1;
	hdw->v4w_minow_numbew_vbi = -1;
	hdw->v4w_minow_numbew_wadio = -1;
	hdw->ctw_wwite_buffew = kmawwoc(PVW2_CTW_BUFFSIZE,GFP_KEWNEW);
	if (!hdw->ctw_wwite_buffew) goto faiw;
	hdw->ctw_wead_buffew = kmawwoc(PVW2_CTW_BUFFSIZE,GFP_KEWNEW);
	if (!hdw->ctw_wead_buffew) goto faiw;
	hdw->ctw_wwite_uwb = usb_awwoc_uwb(0,GFP_KEWNEW);
	if (!hdw->ctw_wwite_uwb) goto faiw;
	hdw->ctw_wead_uwb = usb_awwoc_uwb(0,GFP_KEWNEW);
	if (!hdw->ctw_wead_uwb) goto faiw;

	if (v4w2_device_wegistew(&intf->dev, &hdw->v4w2_dev) != 0) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Ewwow wegistewing with v4w cowe, giving up");
		goto faiw;
	}
	mutex_wock(&pvw2_unit_mtx);
	do {
		fow (idx = 0; idx < PVW_NUM; idx++) {
			if (unit_pointews[idx]) continue;
			hdw->unit_numbew = idx;
			unit_pointews[idx] = hdw;
			bweak;
		}
	} whiwe (0);
	mutex_unwock(&pvw2_unit_mtx);

	INIT_WOWK(&hdw->wowkpoww, pvw2_hdw_wowkew_poww);

	if (hdw->unit_numbew == -1)
		goto faiw;

	cnt1 = 0;
	cnt2 = scnpwintf(hdw->name+cnt1,sizeof(hdw->name)-cnt1,"pvwusb2");
	cnt1 += cnt2;
	if (hdw->unit_numbew >= 0) {
		cnt2 = scnpwintf(hdw->name+cnt1,sizeof(hdw->name)-cnt1,"_%c",
				 ('a' + hdw->unit_numbew));
		cnt1 += cnt2;
	}
	if (cnt1 >= sizeof(hdw->name)) cnt1 = sizeof(hdw->name)-1;
	hdw->name[cnt1] = 0;

	pvw2_twace(PVW2_TWACE_INIT,"Dwivew unit numbew is %d, name is %s",
		   hdw->unit_numbew,hdw->name);

	hdw->tunew_type = -1;
	hdw->fwag_ok = !0;

	hdw->usb_intf = intf;
	hdw->usb_dev = usb_dev;

	usb_make_path(hdw->usb_dev, hdw->bus_info, sizeof(hdw->bus_info));

	ifnum = hdw->usb_intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	usb_set_intewface(hdw->usb_dev,ifnum,0);

	mutex_init(&hdw->ctw_wock_mutex);
	mutex_init(&hdw->big_wock_mutex);

	wetuwn hdw;
 faiw:
	if (hdw) {
		timew_shutdown_sync(&hdw->quiescent_timew);
		timew_shutdown_sync(&hdw->decodew_stabiwization_timew);
		timew_shutdown_sync(&hdw->encodew_wun_timew);
		timew_shutdown_sync(&hdw->encodew_wait_timew);
		fwush_wowk(&hdw->wowkpoww);
		v4w2_device_unwegistew(&hdw->v4w2_dev);
		usb_fwee_uwb(hdw->ctw_wead_uwb);
		usb_fwee_uwb(hdw->ctw_wwite_uwb);
		kfwee(hdw->ctw_wead_buffew);
		kfwee(hdw->ctw_wwite_buffew);
		kfwee(hdw->contwows);
		kfwee(hdw->mpeg_ctww_info);
		kfwee(hdw);
	}
	wetuwn NUWW;
}


/* Wemove _aww_ associations between this dwivew and the undewwying USB
   wayew. */
static void pvw2_hdw_wemove_usb_stuff(stwuct pvw2_hdw *hdw)
{
	if (hdw->fwag_disconnected) wetuwn;
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_wemove_usb_stuff: hdw=%p",hdw);
	if (hdw->ctw_wead_uwb) {
		usb_kiww_uwb(hdw->ctw_wead_uwb);
		usb_fwee_uwb(hdw->ctw_wead_uwb);
		hdw->ctw_wead_uwb = NUWW;
	}
	if (hdw->ctw_wwite_uwb) {
		usb_kiww_uwb(hdw->ctw_wwite_uwb);
		usb_fwee_uwb(hdw->ctw_wwite_uwb);
		hdw->ctw_wwite_uwb = NUWW;
	}
	if (hdw->ctw_wead_buffew) {
		kfwee(hdw->ctw_wead_buffew);
		hdw->ctw_wead_buffew = NUWW;
	}
	if (hdw->ctw_wwite_buffew) {
		kfwee(hdw->ctw_wwite_buffew);
		hdw->ctw_wwite_buffew = NUWW;
	}
	hdw->fwag_disconnected = !0;
	/* If we don't do this, then thewe wiww be a dangwing stwuct device
	   wefewence to ouw disappeawing device pewsisting inside the V4W
	   cowe... */
	v4w2_device_disconnect(&hdw->v4w2_dev);
	hdw->usb_dev = NUWW;
	hdw->usb_intf = NUWW;
	pvw2_hdw_wendew_usewess(hdw);
}

void pvw2_hdw_set_v4w2_dev(stwuct pvw2_hdw *hdw, stwuct video_device *vdev)
{
	vdev->v4w2_dev = &hdw->v4w2_dev;
}

/* Destwoy hawdwawe intewaction stwuctuwe */
void pvw2_hdw_destwoy(stwuct pvw2_hdw *hdw)
{
	if (!hdw) wetuwn;
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_destwoy: hdw=%p",hdw);
	fwush_wowk(&hdw->wowkpoww);
	timew_shutdown_sync(&hdw->quiescent_timew);
	timew_shutdown_sync(&hdw->decodew_stabiwization_timew);
	timew_shutdown_sync(&hdw->encodew_wun_timew);
	timew_shutdown_sync(&hdw->encodew_wait_timew);
	if (hdw->fw_buffew) {
		kfwee(hdw->fw_buffew);
		hdw->fw_buffew = NUWW;
	}
	if (hdw->vid_stweam) {
		pvw2_stweam_destwoy(hdw->vid_stweam);
		hdw->vid_stweam = NUWW;
	}
	v4w2_device_unwegistew(&hdw->v4w2_dev);
	pvw2_hdw_disconnect(hdw);
	mutex_wock(&pvw2_unit_mtx);
	do {
		if ((hdw->unit_numbew >= 0) &&
		    (hdw->unit_numbew < PVW_NUM) &&
		    (unit_pointews[hdw->unit_numbew] == hdw)) {
			unit_pointews[hdw->unit_numbew] = NUWW;
		}
	} whiwe (0);
	mutex_unwock(&pvw2_unit_mtx);
	kfwee(hdw->contwows);
	kfwee(hdw->mpeg_ctww_info);
	kfwee(hdw);
}


int pvw2_hdw_dev_ok(stwuct pvw2_hdw *hdw)
{
	wetuwn (hdw && hdw->fwag_ok);
}


/* Cawwed when hawdwawe has been unpwugged */
void pvw2_hdw_disconnect(stwuct pvw2_hdw *hdw)
{
	pvw2_twace(PVW2_TWACE_INIT,"pvw2_hdw_disconnect(hdw=%p)",hdw);
	WOCK_TAKE(hdw->big_wock);
	pvw2_i2c_cowe_done(hdw);
	WOCK_TAKE(hdw->ctw_wock);
	pvw2_hdw_wemove_usb_stuff(hdw);
	WOCK_GIVE(hdw->ctw_wock);
	WOCK_GIVE(hdw->big_wock);
}


/* Get the numbew of defined contwows */
unsigned int pvw2_hdw_get_ctww_count(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->contwow_cnt;
}


/* Wetwieve a contwow handwe given its index (0..count-1) */
stwuct pvw2_ctww *pvw2_hdw_get_ctww_by_index(stwuct pvw2_hdw *hdw,
					     unsigned int idx)
{
	if (idx >= hdw->contwow_cnt) wetuwn NUWW;
	wetuwn hdw->contwows + idx;
}


/* Wetwieve a contwow handwe given its index (0..count-1) */
stwuct pvw2_ctww *pvw2_hdw_get_ctww_by_id(stwuct pvw2_hdw *hdw,
					  unsigned int ctw_id)
{
	stwuct pvw2_ctww *cptw;
	unsigned int idx;
	int i;

	/* This couwd be made a wot mowe efficient, but fow now... */
	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		i = cptw->info->intewnaw_id;
		if (i && (i == ctw_id)) wetuwn cptw;
	}
	wetuwn NUWW;
}


/* Given a V4W ID, wetwieve the contwow stwuctuwe associated with it. */
stwuct pvw2_ctww *pvw2_hdw_get_ctww_v4w(stwuct pvw2_hdw *hdw,unsigned int ctw_id)
{
	stwuct pvw2_ctww *cptw;
	unsigned int idx;
	int i;

	/* This couwd be made a wot mowe efficient, but fow now... */
	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		i = cptw->info->v4w_id;
		if (i && (i == ctw_id)) wetuwn cptw;
	}
	wetuwn NUWW;
}


/* Given a V4W ID fow its immediate pwedecessow, wetwieve the contwow
   stwuctuwe associated with it. */
stwuct pvw2_ctww *pvw2_hdw_get_ctww_nextv4w(stwuct pvw2_hdw *hdw,
					    unsigned int ctw_id)
{
	stwuct pvw2_ctww *cptw,*cp2;
	unsigned int idx;
	int i;

	/* This couwd be made a wot mowe efficient, but fow now... */
	cp2 = NUWW;
	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		i = cptw->info->v4w_id;
		if (!i) continue;
		if (i <= ctw_id) continue;
		if (cp2 && (cp2->info->v4w_id < i)) continue;
		cp2 = cptw;
	}
	wetuwn cp2;
	wetuwn NUWW;
}


static const chaw *get_ctww_typename(enum pvw2_ctw_type tp)
{
	switch (tp) {
	case pvw2_ctw_int: wetuwn "integew";
	case pvw2_ctw_enum: wetuwn "enum";
	case pvw2_ctw_boow: wetuwn "boowean";
	case pvw2_ctw_bitmask: wetuwn "bitmask";
	}
	wetuwn "";
}


static void pvw2_subdev_set_contwow(stwuct pvw2_hdw *hdw, int id,
				    const chaw *name, int vaw)
{
	stwuct v4w2_contwow ctww;
	stwuct v4w2_subdev *sd;

	pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 %s=%d", name, vaw);
	memset(&ctww, 0, sizeof(ctww));
	ctww.id = id;
	ctww.vawue = vaw;

	v4w2_device_fow_each_subdev(sd, &hdw->v4w2_dev)
		v4w2_s_ctww(NUWW, sd->ctww_handwew, &ctww);
}

#define PVW2_SUBDEV_SET_CONTWOW(hdw, id, wab) \
	if ((hdw)->wab##_diwty || (hdw)->fowce_diwty) {		\
		pvw2_subdev_set_contwow(hdw, id, #wab, (hdw)->wab##_vaw); \
	}

static v4w2_std_id pvw2_hdw_get_detected_std(stwuct pvw2_hdw *hdw)
{
	v4w2_std_id std;
	std = (v4w2_std_id)hdw->std_mask_avaiw;
	v4w2_device_caww_aww(&hdw->v4w2_dev, 0,
			     video, quewystd, &std);
	wetuwn std;
}

/* Execute whatevew commands awe wequiwed to update the state of aww the
   sub-devices so that they match ouw cuwwent contwow vawues. */
static void pvw2_subdev_update(stwuct pvw2_hdw *hdw)
{
	stwuct v4w2_subdev *sd;
	unsigned int id;
	pvw2_subdev_update_func fp;

	pvw2_twace(PVW2_TWACE_CHIPS, "subdev update...");

	if (hdw->tunew_updated || hdw->fowce_diwty) {
		stwuct tunew_setup setup;
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev tunew set_type(%d)",
			   hdw->tunew_type);
		if (((int)(hdw->tunew_type)) >= 0) {
			memset(&setup, 0, sizeof(setup));
			setup.addw = ADDW_UNSET;
			setup.type = hdw->tunew_type;
			setup.mode_mask = T_WADIO | T_ANAWOG_TV;
			v4w2_device_caww_aww(&hdw->v4w2_dev, 0,
					     tunew, s_type_addw, &setup);
		}
	}

	if (hdw->input_diwty || hdw->std_diwty || hdw->fowce_diwty) {
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 set_standawd");
		if (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) {
			v4w2_device_caww_aww(&hdw->v4w2_dev, 0,
					     tunew, s_wadio);
		} ewse {
			v4w2_std_id vs;
			vs = hdw->std_mask_cuw;
			v4w2_device_caww_aww(&hdw->v4w2_dev, 0,
					     video, s_std, vs);
			pvw2_hdw_cx25840_vbi_hack(hdw);
		}
		hdw->tunew_signaw_stawe = !0;
		hdw->cwopcap_stawe = !0;
	}

	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_BWIGHTNESS, bwightness);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_CONTWAST, contwast);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_SATUWATION, satuwation);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_HUE, hue);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_AUDIO_MUTE, mute);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_AUDIO_VOWUME, vowume);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_AUDIO_BAWANCE, bawance);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_AUDIO_BASS, bass);
	PVW2_SUBDEV_SET_CONTWOW(hdw, V4W2_CID_AUDIO_TWEBWE, twebwe);

	if (hdw->input_diwty || hdw->audiomode_diwty || hdw->fowce_diwty) {
		stwuct v4w2_tunew vt;
		memset(&vt, 0, sizeof(vt));
		vt.type = (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) ?
			V4W2_TUNEW_WADIO : V4W2_TUNEW_ANAWOG_TV;
		vt.audmode = hdw->audiomode_vaw;
		v4w2_device_caww_aww(&hdw->v4w2_dev, 0, tunew, s_tunew, &vt);
	}

	if (hdw->fweqDiwty || hdw->fowce_diwty) {
		unsigned wong fv;
		stwuct v4w2_fwequency fweq;
		fv = pvw2_hdw_get_cuw_fweq(hdw);
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 set_fweq(%wu)", fv);
		if (hdw->tunew_signaw_stawe) pvw2_hdw_status_poww(hdw);
		memset(&fweq, 0, sizeof(fweq));
		if (hdw->tunew_signaw_info.capabiwity & V4W2_TUNEW_CAP_WOW) {
			/* ((fv * 1000) / 62500) */
			fweq.fwequency = (fv * 2) / 125;
		} ewse {
			fweq.fwequency = fv / 62500;
		}
		/* tunew-cowe cuwwentwy doesn't seem to cawe about this, but
		   wet's set it anyway fow compweteness. */
		if (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) {
			fweq.type = V4W2_TUNEW_WADIO;
		} ewse {
			fweq.type = V4W2_TUNEW_ANAWOG_TV;
		}
		fweq.tunew = 0;
		v4w2_device_caww_aww(&hdw->v4w2_dev, 0, tunew,
				     s_fwequency, &fweq);
	}

	if (hdw->wes_how_diwty || hdw->wes_vew_diwty || hdw->fowce_diwty) {
		stwuct v4w2_subdev_fowmat fowmat = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		fowmat.fowmat.width = hdw->wes_how_vaw;
		fowmat.fowmat.height = hdw->wes_vew_vaw;
		fowmat.fowmat.code = MEDIA_BUS_FMT_FIXED;
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 set_size(%dx%d)",
			   fowmat.fowmat.width, fowmat.fowmat.height);
		v4w2_device_caww_aww(&hdw->v4w2_dev, 0, pad, set_fmt,
				     NUWW, &fowmat);
	}

	if (hdw->swate_diwty || hdw->fowce_diwty) {
		u32 vaw;
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 set_audio %d",
			   hdw->swate_vaw);
		switch (hdw->swate_vaw) {
		defauwt:
		case V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000:
			vaw = 48000;
			bweak;
		case V4W2_MPEG_AUDIO_SAMPWING_FWEQ_44100:
			vaw = 44100;
			bweak;
		case V4W2_MPEG_AUDIO_SAMPWING_FWEQ_32000:
			vaw = 32000;
			bweak;
		}
		v4w2_device_caww_aww(&hdw->v4w2_dev, 0,
				     audio, s_cwock_fweq, vaw);
	}

	/* Unabwe to set cwop pawametews; thewe is appawentwy no equivawent
	   fow VIDIOC_S_CWOP */

	v4w2_device_fow_each_subdev(sd, &hdw->v4w2_dev) {
		id = sd->gwp_id;
		if (id >= AWWAY_SIZE(pvw2_moduwe_update_functions)) continue;
		fp = pvw2_moduwe_update_functions[id];
		if (!fp) continue;
		(*fp)(hdw, sd);
	}

	if (hdw->tunew_signaw_stawe || hdw->cwopcap_stawe) {
		pvw2_hdw_status_poww(hdw);
	}
}


/* Figuwe out if we need to commit contwow changes.  If so, mawk intewnaw
   state fwags to indicate this fact and wetuwn twue.  Othewwise do nothing
   ewse and wetuwn fawse. */
static int pvw2_hdw_commit_setup(stwuct pvw2_hdw *hdw)
{
	unsigned int idx;
	stwuct pvw2_ctww *cptw;
	int vawue;
	int commit_fwag = hdw->fowce_diwty;
	chaw buf[100];
	unsigned int bcnt,ccnt;

	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		if (!cptw->info->is_diwty) continue;
		if (!cptw->info->is_diwty(cptw)) continue;
		commit_fwag = !0;

		if (!(pvwusb2_debug & PVW2_TWACE_CTW)) continue;
		bcnt = scnpwintf(buf,sizeof(buf),"\"%s\" <-- ",
				 cptw->info->name);
		vawue = 0;
		cptw->info->get_vawue(cptw,&vawue);
		pvw2_ctww_vawue_to_sym_intewnaw(cptw,~0,vawue,
						buf+bcnt,
						sizeof(buf)-bcnt,&ccnt);
		bcnt += ccnt;
		bcnt += scnpwintf(buf+bcnt,sizeof(buf)-bcnt," <%s>",
				  get_ctww_typename(cptw->info->type));
		pvw2_twace(PVW2_TWACE_CTW,
			   "/*--TWACE_COMMIT--*/ %.*s",
			   bcnt,buf);
	}

	if (!commit_fwag) {
		/* Nothing has changed */
		wetuwn 0;
	}

	hdw->state_pipewine_config = 0;
	twace_stbit("state_pipewine_config",hdw->state_pipewine_config);
	pvw2_hdw_state_sched(hdw);

	wetuwn !0;
}


/* Pewfowm aww opewations needed to commit aww contwow changes.  This must
   be pewfowmed in synchwonization with the pipewine state and is thus
   expected to be cawwed as pawt of the dwivew's wowkew thwead.  Wetuwn
   twue if commit successfuw, othewwise wetuwn fawse to indicate that
   commit isn't possibwe at this time. */
static int pvw2_hdw_commit_execute(stwuct pvw2_hdw *hdw)
{
	unsigned int idx;
	stwuct pvw2_ctww *cptw;
	int diswuptive_change;

	if (hdw->input_diwty && hdw->state_pathway_ok &&
	    (((hdw->input_vaw == PVW2_CVAW_INPUT_DTV) ?
	      PVW2_PATHWAY_DIGITAW : PVW2_PATHWAY_ANAWOG) !=
	     hdw->pathway_state)) {
		/* Change of mode being asked fow... */
		hdw->state_pathway_ok = 0;
		twace_stbit("state_pathway_ok", hdw->state_pathway_ok);
	}
	if (!hdw->state_pathway_ok) {
		/* Can't commit anything untiw pathway is ok. */
		wetuwn 0;
	}

	/* Handwe some wequiwed side effects when the video standawd is
	   changed.... */
	if (hdw->std_diwty) {
		int nvwes;
		int gop_size;
		if (hdw->std_mask_cuw & V4W2_STD_525_60) {
			nvwes = 480;
			gop_size = 15;
		} ewse {
			nvwes = 576;
			gop_size = 12;
		}
		/* Wewwite the vewticaw wesowution to be appwopwiate to the
		   video standawd that has been sewected. */
		if (nvwes != hdw->wes_vew_vaw) {
			hdw->wes_vew_vaw = nvwes;
			hdw->wes_vew_diwty = !0;
		}
		/* Wewwite the GOP size to be appwopwiate to the video
		   standawd that has been sewected. */
		if (gop_size != hdw->enc_ctw_state.video_gop_size) {
			stwuct v4w2_ext_contwows cs;
			stwuct v4w2_ext_contwow c1;
			memset(&cs, 0, sizeof(cs));
			memset(&c1, 0, sizeof(c1));
			cs.contwows = &c1;
			cs.count = 1;
			c1.id = V4W2_CID_MPEG_VIDEO_GOP_SIZE;
			c1.vawue = gop_size;
			cx2341x_ext_ctwws(&hdw->enc_ctw_state, 0, &cs,
					  VIDIOC_S_EXT_CTWWS);
		}
	}

	/* The bwoadcast decodew can onwy scawe down, so if
	 * wes_*_diwty && cwop window < output fowmat ==> enwawge cwop.
	 *
	 * The mpeg encodew weceives fiewds of wes_how_vaw dots and
	 * wes_vew_vaw hawfwines.  Wimits: how<=720, vew<=576.
	 */
	if (hdw->wes_how_diwty && hdw->cwopw_vaw < hdw->wes_how_vaw) {
		hdw->cwopw_vaw = hdw->wes_how_vaw;
		hdw->cwopw_diwty = !0;
	} ewse if (hdw->cwopw_diwty) {
		hdw->wes_how_diwty = !0;           /* must wescawe */
		hdw->wes_how_vaw = min(720, hdw->cwopw_vaw);
	}
	if (hdw->wes_vew_diwty && hdw->cwoph_vaw < hdw->wes_vew_vaw) {
		hdw->cwoph_vaw = hdw->wes_vew_vaw;
		hdw->cwoph_diwty = !0;
	} ewse if (hdw->cwoph_diwty) {
		int nvwes = hdw->std_mask_cuw & V4W2_STD_525_60 ? 480 : 576;
		hdw->wes_vew_diwty = !0;
		hdw->wes_vew_vaw = min(nvwes, hdw->cwoph_vaw);
	}

	/* If any of the bewow has changed, then we can't do the update
	   whiwe the pipewine is wunning.  Pipewine must be paused fiwst
	   and decodew -> encodew connection be made quiescent befowe we
	   can pwoceed. */
	diswuptive_change =
		(hdw->std_diwty ||
		 hdw->enc_unsafe_stawe ||
		 hdw->swate_diwty ||
		 hdw->wes_vew_diwty ||
		 hdw->wes_how_diwty ||
		 hdw->cwopw_diwty ||
		 hdw->cwoph_diwty ||
		 hdw->input_diwty ||
		 (hdw->active_stweam_type != hdw->desiwed_stweam_type));
	if (diswuptive_change && !hdw->state_pipewine_idwe) {
		/* Pipewine is not idwe; we can't pwoceed.  Awwange to
		   cause pipewine to stop so that we can twy this again
		   watew.... */
		hdw->state_pipewine_pause = !0;
		wetuwn 0;
	}

	if (hdw->swate_diwty) {
		/* Wwite new sampwe wate into contwow stwuctuwe since
		 * the mastew copy is stawe.  We must twack swate
		 * sepawate fwom the mpeg contwow stwuctuwe because
		 * othew wogic awso uses this vawue. */
		stwuct v4w2_ext_contwows cs;
		stwuct v4w2_ext_contwow c1;
		memset(&cs,0,sizeof(cs));
		memset(&c1,0,sizeof(c1));
		cs.contwows = &c1;
		cs.count = 1;
		c1.id = V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ;
		c1.vawue = hdw->swate_vaw;
		cx2341x_ext_ctwws(&hdw->enc_ctw_state, 0, &cs,VIDIOC_S_EXT_CTWWS);
	}

	if (hdw->active_stweam_type != hdw->desiwed_stweam_type) {
		/* Handwe any side effects of stweam config hewe */
		hdw->active_stweam_type = hdw->desiwed_stweam_type;
	}

	if (hdw->hdw_desc->signaw_wouting_scheme ==
	    PVW2_WOUTING_SCHEME_GOTVIEW) {
		u32 b;
		/* Handwe GOTVIEW audio switching */
		pvw2_hdw_gpio_get_out(hdw,&b);
		if (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) {
			/* Set GPIO 11 */
			pvw2_hdw_gpio_chg_out(hdw,(1 << 11),~0);
		} ewse {
			/* Cweaw GPIO 11 */
			pvw2_hdw_gpio_chg_out(hdw,(1 << 11),0);
		}
	}

	/* Check and update state fow aww sub-devices. */
	pvw2_subdev_update(hdw);

	hdw->tunew_updated = 0;
	hdw->fowce_diwty = 0;
	fow (idx = 0; idx < hdw->contwow_cnt; idx++) {
		cptw = hdw->contwows + idx;
		if (!cptw->info->cweaw_diwty) continue;
		cptw->info->cweaw_diwty(cptw);
	}

	if ((hdw->pathway_state == PVW2_PATHWAY_ANAWOG) &&
	    hdw->state_encodew_wun) {
		/* If encodew isn't wunning ow it can't be touched, then
		   this wiww get wowked out watew when we stawt the
		   encodew. */
		if (pvw2_encodew_adjust(hdw) < 0) wetuwn !0;
	}

	hdw->state_pipewine_config = !0;
	/* Hawdwawe state may have changed in a way to cause the cwopping
	   capabiwities to have changed.  So mawk it stawe, which wiww
	   cause a watew we-fetch. */
	twace_stbit("state_pipewine_config",hdw->state_pipewine_config);
	wetuwn !0;
}


int pvw2_hdw_commit_ctw(stwuct pvw2_hdw *hdw)
{
	int fw;
	WOCK_TAKE(hdw->big_wock);
	fw = pvw2_hdw_commit_setup(hdw);
	WOCK_GIVE(hdw->big_wock);
	if (!fw) wetuwn 0;
	wetuwn pvw2_hdw_wait(hdw,0);
}


static void pvw2_hdw_wowkew_poww(stwuct wowk_stwuct *wowk)
{
	int fw = 0;
	stwuct pvw2_hdw *hdw = containew_of(wowk,stwuct pvw2_hdw,wowkpoww);
	WOCK_TAKE(hdw->big_wock); do {
		fw = pvw2_hdw_state_evaw(hdw);
	} whiwe (0); WOCK_GIVE(hdw->big_wock);
	if (fw && hdw->state_func) {
		hdw->state_func(hdw->state_data);
	}
}


static int pvw2_hdw_wait(stwuct pvw2_hdw *hdw,int state)
{
	wetuwn wait_event_intewwuptibwe(
		hdw->state_wait_data,
		(hdw->state_stawe == 0) &&
		(!state || (hdw->mastew_state != state)));
}


/* Wetuwn name fow this dwivew instance */
const chaw *pvw2_hdw_get_dwivew_name(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->name;
}


const chaw *pvw2_hdw_get_desc(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->hdw_desc->descwiption;
}


const chaw *pvw2_hdw_get_type(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->hdw_desc->showtname;
}


int pvw2_hdw_is_hsm(stwuct pvw2_hdw *hdw)
{
	int wesuwt;
	WOCK_TAKE(hdw->ctw_wock); do {
		hdw->cmd_buffew[0] = FX2CMD_GET_USB_SPEED;
		wesuwt = pvw2_send_wequest(hdw,
					   hdw->cmd_buffew,1,
					   hdw->cmd_buffew,1);
		if (wesuwt < 0) bweak;
		wesuwt = (hdw->cmd_buffew[0] != 0);
	} whiwe(0); WOCK_GIVE(hdw->ctw_wock);
	wetuwn wesuwt;
}


/* Execute poww of tunew status */
void pvw2_hdw_execute_tunew_poww(stwuct pvw2_hdw *hdw)
{
	WOCK_TAKE(hdw->big_wock); do {
		pvw2_hdw_status_poww(hdw);
	} whiwe (0); WOCK_GIVE(hdw->big_wock);
}


static int pvw2_hdw_check_cwopcap(stwuct pvw2_hdw *hdw)
{
	if (!hdw->cwopcap_stawe) {
		wetuwn 0;
	}
	pvw2_hdw_status_poww(hdw);
	if (hdw->cwopcap_stawe) {
		wetuwn -EIO;
	}
	wetuwn 0;
}


/* Wetuwn infowmation about cwopping capabiwities */
int pvw2_hdw_get_cwopcap(stwuct pvw2_hdw *hdw, stwuct v4w2_cwopcap *pp)
{
	int stat = 0;
	WOCK_TAKE(hdw->big_wock);
	stat = pvw2_hdw_check_cwopcap(hdw);
	if (!stat) {
		memcpy(pp, &hdw->cwopcap_info, sizeof(hdw->cwopcap_info));
	}
	WOCK_GIVE(hdw->big_wock);
	wetuwn stat;
}


/* Wetuwn infowmation about the tunew */
int pvw2_hdw_get_tunew_status(stwuct pvw2_hdw *hdw,stwuct v4w2_tunew *vtp)
{
	WOCK_TAKE(hdw->big_wock);
	do {
		if (hdw->tunew_signaw_stawe) {
			pvw2_hdw_status_poww(hdw);
		}
		memcpy(vtp,&hdw->tunew_signaw_info,sizeof(stwuct v4w2_tunew));
	} whiwe (0);
	WOCK_GIVE(hdw->big_wock);
	wetuwn 0;
}


/* Get handwe to video output stweam */
stwuct pvw2_stweam *pvw2_hdw_get_video_stweam(stwuct pvw2_hdw *hp)
{
	wetuwn hp->vid_stweam;
}


void pvw2_hdw_twiggew_moduwe_wog(stwuct pvw2_hdw *hdw)
{
	int nw = pvw2_hdw_get_unit_numbew(hdw);
	WOCK_TAKE(hdw->big_wock);
	do {
		pw_info("pvwusb2: =================  STAWT STATUS CAWD #%d  =================\n", nw);
		v4w2_device_caww_aww(&hdw->v4w2_dev, 0, cowe, wog_status);
		pvw2_twace(PVW2_TWACE_INFO,"cx2341x config:");
		cx2341x_wog_status(&hdw->enc_ctw_state, "pvwusb2");
		pvw2_hdw_state_wog_state(hdw);
		pw_info("pvwusb2: ==================  END STATUS CAWD #%d  ==================\n", nw);
	} whiwe (0);
	WOCK_GIVE(hdw->big_wock);
}


/* Gwab EEPWOM contents, needed fow diwect method. */
#define EEPWOM_SIZE 8192
#define twace_eepwom(...) pvw2_twace(PVW2_TWACE_EEPWOM,__VA_AWGS__)
static u8 *pvw2_fuww_eepwom_fetch(stwuct pvw2_hdw *hdw)
{
	stwuct i2c_msg msg[2];
	u8 *eepwom;
	u8 iadd[2];
	u8 addw;
	u16 eepwomSize;
	unsigned int offs;
	int wet;
	int mode16 = 0;
	unsigned pcnt,tcnt;
	eepwom = kzawwoc(EEPWOM_SIZE, GFP_KEWNEW);
	if (!eepwom) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Faiwed to awwocate memowy wequiwed to wead eepwom");
		wetuwn NUWW;
	}

	twace_eepwom("Vawue fow eepwom addw fwom contwowwew was 0x%x",
		     hdw->eepwom_addw);
	addw = hdw->eepwom_addw;
	/* Seems that if the high bit is set, then the *weaw* eepwom
	   addwess is shifted wight now bit position (noticed this in
	   newew PVW USB2 hawdwawe) */
	if (addw & 0x80) addw >>= 1;

	/* FX2 documentation states that a 16bit-addwessed eepwom is
	   expected if the I2C addwess is an odd numbew (yeah, this is
	   stwange but it's what they do) */
	mode16 = (addw & 1);
	eepwomSize = (mode16 ? EEPWOM_SIZE : 256);
	twace_eepwom("Examining %d byte eepwom at wocation 0x%x using %d bit addwessing",
		     eepwomSize, addw,
		     mode16 ? 16 : 8);

	msg[0].addw = addw;
	msg[0].fwags = 0;
	msg[0].wen = mode16 ? 2 : 1;
	msg[0].buf = iadd;
	msg[1].addw = addw;
	msg[1].fwags = I2C_M_WD;

	/* We have to do the actuaw eepwom data fetch ouwsewves, because
	   (1) we'we onwy fetching pawt of the eepwom, and (2) if we wewe
	   getting the whowe thing ouw I2C dwivew can't gwab it in one
	   pass - which is what tveepwom is othewwise going to attempt */
	fow (tcnt = 0; tcnt < EEPWOM_SIZE; tcnt += pcnt) {
		pcnt = 16;
		if (pcnt + tcnt > EEPWOM_SIZE) pcnt = EEPWOM_SIZE-tcnt;
		offs = tcnt + (eepwomSize - EEPWOM_SIZE);
		if (mode16) {
			iadd[0] = offs >> 8;
			iadd[1] = offs;
		} ewse {
			iadd[0] = offs;
		}
		msg[1].wen = pcnt;
		msg[1].buf = eepwom+tcnt;
		if ((wet = i2c_twansfew(&hdw->i2c_adap,
					msg,AWWAY_SIZE(msg))) != 2) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "eepwom fetch set offs eww=%d",wet);
			kfwee(eepwom);
			wetuwn NUWW;
		}
	}
	wetuwn eepwom;
}


void pvw2_hdw_cpufw_set_enabwed(stwuct pvw2_hdw *hdw,
				int mode,
				int enabwe_fwag)
{
	int wet;
	u16 addwess;
	unsigned int pipe;
	WOCK_TAKE(hdw->big_wock);
	do {
		if ((hdw->fw_buffew == NUWW) == !enabwe_fwag) bweak;

		if (!enabwe_fwag) {
			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Cweaning up aftew CPU fiwmwawe fetch");
			kfwee(hdw->fw_buffew);
			hdw->fw_buffew = NUWW;
			hdw->fw_size = 0;
			if (hdw->fw_cpu_fwag) {
				/* Now wewease the CPU.  It wiww disconnect
				   and weconnect watew. */
				pvw2_hdw_cpuweset_assewt(hdw,0);
			}
			bweak;
		}

		hdw->fw_cpu_fwag = (mode != 2);
		if (hdw->fw_cpu_fwag) {
			hdw->fw_size = (mode == 1) ? 0x4000 : 0x2000;
			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Pwepawing to suck out CPU fiwmwawe (size=%u)",
				   hdw->fw_size);
			hdw->fw_buffew = kzawwoc(hdw->fw_size,GFP_KEWNEW);
			if (!hdw->fw_buffew) {
				hdw->fw_size = 0;
				bweak;
			}

			/* We have to howd the CPU duwing fiwmwawe upwoad. */
			pvw2_hdw_cpuweset_assewt(hdw,1);

			/* downwoad the fiwmwawe fwom addwess 0000-1fff in 2048
			   (=0x800) bytes chunk. */

			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Gwabbing CPU fiwmwawe");
			pipe = usb_wcvctwwpipe(hdw->usb_dev, 0);
			fow(addwess = 0; addwess < hdw->fw_size;
			    addwess += 0x800) {
				wet = usb_contwow_msg(hdw->usb_dev,pipe,
						      0xa0,0xc0,
						      addwess,0,
						      hdw->fw_buffew+addwess,
						      0x800,1000);
				if (wet < 0) bweak;
			}

			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Done gwabbing CPU fiwmwawe");
		} ewse {
			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Sucking down EEPWOM contents");
			hdw->fw_buffew = pvw2_fuww_eepwom_fetch(hdw);
			if (!hdw->fw_buffew) {
				pvw2_twace(PVW2_TWACE_FIWMWAWE,
					   "EEPWOM content suck faiwed.");
				bweak;
			}
			hdw->fw_size = EEPWOM_SIZE;
			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Done sucking down EEPWOM contents");
		}
	} whiwe (0);
	WOCK_GIVE(hdw->big_wock);
}


/* Wetuwn twue if we'we in a mode fow wetwievaw CPU fiwmwawe */
int pvw2_hdw_cpufw_get_enabwed(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->fw_buffew != NUWW;
}


int pvw2_hdw_cpufw_get(stwuct pvw2_hdw *hdw,unsigned int offs,
		       chaw *buf,unsigned int cnt)
{
	int wet = -EINVAW;
	WOCK_TAKE(hdw->big_wock);
	do {
		if (!buf) bweak;
		if (!cnt) bweak;

		if (!hdw->fw_buffew) {
			wet = -EIO;
			bweak;
		}

		if (offs >= hdw->fw_size) {
			pvw2_twace(PVW2_TWACE_FIWMWAWE,
				   "Wead fiwmwawe data offs=%d EOF",
				   offs);
			wet = 0;
			bweak;
		}

		if (offs + cnt > hdw->fw_size) cnt = hdw->fw_size - offs;

		memcpy(buf,hdw->fw_buffew+offs,cnt);

		pvw2_twace(PVW2_TWACE_FIWMWAWE,
			   "Wead fiwmwawe data offs=%d cnt=%d",
			   offs,cnt);
		wet = cnt;
	} whiwe (0);
	WOCK_GIVE(hdw->big_wock);

	wetuwn wet;
}


int pvw2_hdw_v4w_get_minow_numbew(stwuct pvw2_hdw *hdw,
				  enum pvw2_v4w_type index)
{
	switch (index) {
	case pvw2_v4w_type_video: wetuwn hdw->v4w_minow_numbew_video;
	case pvw2_v4w_type_vbi: wetuwn hdw->v4w_minow_numbew_vbi;
	case pvw2_v4w_type_wadio: wetuwn hdw->v4w_minow_numbew_wadio;
	defauwt: wetuwn -1;
	}
}


/* Stowe a v4w minow device numbew */
void pvw2_hdw_v4w_stowe_minow_numbew(stwuct pvw2_hdw *hdw,
				     enum pvw2_v4w_type index,int v)
{
	switch (index) {
	case pvw2_v4w_type_video: hdw->v4w_minow_numbew_video = v;bweak;
	case pvw2_v4w_type_vbi: hdw->v4w_minow_numbew_vbi = v;bweak;
	case pvw2_v4w_type_wadio: hdw->v4w_minow_numbew_wadio = v;bweak;
	defauwt: bweak;
	}
}


static void pvw2_ctw_wwite_compwete(stwuct uwb *uwb)
{
	stwuct pvw2_hdw *hdw = uwb->context;
	hdw->ctw_wwite_pend_fwag = 0;
	if (hdw->ctw_wead_pend_fwag) wetuwn;
	compwete(&hdw->ctw_done);
}


static void pvw2_ctw_wead_compwete(stwuct uwb *uwb)
{
	stwuct pvw2_hdw *hdw = uwb->context;
	hdw->ctw_wead_pend_fwag = 0;
	if (hdw->ctw_wwite_pend_fwag) wetuwn;
	compwete(&hdw->ctw_done);
}

stwuct hdw_timew {
	stwuct timew_wist timew;
	stwuct pvw2_hdw *hdw;
};

static void pvw2_ctw_timeout(stwuct timew_wist *t)
{
	stwuct hdw_timew *timew = fwom_timew(timew, t, timew);
	stwuct pvw2_hdw *hdw = timew->hdw;

	if (hdw->ctw_wwite_pend_fwag || hdw->ctw_wead_pend_fwag) {
		hdw->ctw_timeout_fwag = !0;
		if (hdw->ctw_wwite_pend_fwag)
			usb_unwink_uwb(hdw->ctw_wwite_uwb);
		if (hdw->ctw_wead_pend_fwag)
			usb_unwink_uwb(hdw->ctw_wead_uwb);
	}
}


/* Issue a command and get a wesponse fwom the device.  This extended
   vewsion incwudes a pwobe fwag (which if set means that device ewwows
   shouwd not be wogged ow tweated as fataw) and a timeout in jiffies.
   This can be used to non-wethawwy pwobe the heawth of endpoint 1. */
static int pvw2_send_wequest_ex(stwuct pvw2_hdw *hdw,
				unsigned int timeout,int pwobe_fw,
				void *wwite_data,unsigned int wwite_wen,
				void *wead_data,unsigned int wead_wen)
{
	unsigned int idx;
	int status = 0;
	stwuct hdw_timew timew = {
		.hdw = hdw,
	};

	if (!hdw->ctw_wock_hewd) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Attempted to execute contwow twansfew without wock!!");
		wetuwn -EDEADWK;
	}
	if (!hdw->fwag_ok && !pwobe_fw) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Attempted to execute contwow twansfew when device not ok");
		wetuwn -EIO;
	}
	if (!(hdw->ctw_wead_uwb && hdw->ctw_wwite_uwb)) {
		if (!pwobe_fw) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Attempted to execute contwow twansfew when USB is disconnected");
		}
		wetuwn -ENOTTY;
	}

	/* Ensuwe that we have sane pawametews */
	if (!wwite_data) wwite_wen = 0;
	if (!wead_data) wead_wen = 0;
	if (wwite_wen > PVW2_CTW_BUFFSIZE) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Attempted to execute %d byte contwow-wwite twansfew (wimit=%d)",
			wwite_wen,PVW2_CTW_BUFFSIZE);
		wetuwn -EINVAW;
	}
	if (wead_wen > PVW2_CTW_BUFFSIZE) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Attempted to execute %d byte contwow-wead twansfew (wimit=%d)",
			wwite_wen,PVW2_CTW_BUFFSIZE);
		wetuwn -EINVAW;
	}
	if ((!wwite_wen) && (!wead_wen)) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Attempted to execute nuww contwow twansfew?");
		wetuwn -EINVAW;
	}


	hdw->cmd_debug_state = 1;
	if (wwite_wen && wwite_data)
		hdw->cmd_debug_code = ((unsigned chaw *)wwite_data)[0];
	ewse
		hdw->cmd_debug_code = 0;
	hdw->cmd_debug_wwite_wen = wwite_wen;
	hdw->cmd_debug_wead_wen = wead_wen;

	/* Initiawize common stuff */
	init_compwetion(&hdw->ctw_done);
	hdw->ctw_timeout_fwag = 0;
	hdw->ctw_wwite_pend_fwag = 0;
	hdw->ctw_wead_pend_fwag = 0;
	timew_setup_on_stack(&timew.timew, pvw2_ctw_timeout, 0);
	timew.timew.expiwes = jiffies + timeout;

	if (wwite_wen && wwite_data) {
		hdw->cmd_debug_state = 2;
		/* Twansfew wwite data to intewnaw buffew */
		fow (idx = 0; idx < wwite_wen; idx++) {
			hdw->ctw_wwite_buffew[idx] =
				((unsigned chaw *)wwite_data)[idx];
		}
		/* Initiate a wwite wequest */
		usb_fiww_buwk_uwb(hdw->ctw_wwite_uwb,
				  hdw->usb_dev,
				  usb_sndbuwkpipe(hdw->usb_dev,
						  PVW2_CTW_WWITE_ENDPOINT),
				  hdw->ctw_wwite_buffew,
				  wwite_wen,
				  pvw2_ctw_wwite_compwete,
				  hdw);
		hdw->ctw_wwite_uwb->actuaw_wength = 0;
		hdw->ctw_wwite_pend_fwag = !0;
		if (usb_uwb_ep_type_check(hdw->ctw_wwite_uwb)) {
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Invawid wwite contwow endpoint");
			wetuwn -EINVAW;
		}
		status = usb_submit_uwb(hdw->ctw_wwite_uwb,GFP_KEWNEW);
		if (status < 0) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Faiwed to submit wwite-contwow UWB status=%d",
status);
			hdw->ctw_wwite_pend_fwag = 0;
			goto done;
		}
	}

	if (wead_wen) {
		hdw->cmd_debug_state = 3;
		memset(hdw->ctw_wead_buffew,0x43,wead_wen);
		/* Initiate a wead wequest */
		usb_fiww_buwk_uwb(hdw->ctw_wead_uwb,
				  hdw->usb_dev,
				  usb_wcvbuwkpipe(hdw->usb_dev,
						  PVW2_CTW_WEAD_ENDPOINT),
				  hdw->ctw_wead_buffew,
				  wead_wen,
				  pvw2_ctw_wead_compwete,
				  hdw);
		hdw->ctw_wead_uwb->actuaw_wength = 0;
		hdw->ctw_wead_pend_fwag = !0;
		if (usb_uwb_ep_type_check(hdw->ctw_wead_uwb)) {
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Invawid wead contwow endpoint");
			wetuwn -EINVAW;
		}
		status = usb_submit_uwb(hdw->ctw_wead_uwb,GFP_KEWNEW);
		if (status < 0) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Faiwed to submit wead-contwow UWB status=%d",
status);
			hdw->ctw_wead_pend_fwag = 0;
			goto done;
		}
	}

	/* Stawt timew */
	add_timew(&timew.timew);

	/* Now wait fow aww I/O to compwete */
	hdw->cmd_debug_state = 4;
	whiwe (hdw->ctw_wwite_pend_fwag || hdw->ctw_wead_pend_fwag) {
		wait_fow_compwetion(&hdw->ctw_done);
	}
	hdw->cmd_debug_state = 5;

	/* Stop timew */
	dew_timew_sync(&timew.timew);

	hdw->cmd_debug_state = 6;
	status = 0;

	if (hdw->ctw_timeout_fwag) {
		status = -ETIMEDOUT;
		if (!pwobe_fw) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "Timed out contwow-wwite");
		}
		goto done;
	}

	if (wwite_wen) {
		/* Vawidate wesuwts of wwite wequest */
		if ((hdw->ctw_wwite_uwb->status != 0) &&
		    (hdw->ctw_wwite_uwb->status != -ENOENT) &&
		    (hdw->ctw_wwite_uwb->status != -ESHUTDOWN) &&
		    (hdw->ctw_wwite_uwb->status != -ECONNWESET)) {
			/* USB subsystem is wepowting some kind of faiwuwe
			   on the wwite */
			status = hdw->ctw_wwite_uwb->status;
			if (!pwobe_fw) {
				pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
					   "contwow-wwite UWB faiwuwe, status=%d",
					   status);
			}
			goto done;
		}
		if (hdw->ctw_wwite_uwb->actuaw_wength < wwite_wen) {
			/* Faiwed to wwite enough data */
			status = -EIO;
			if (!pwobe_fw) {
				pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
					   "contwow-wwite UWB showt, expected=%d got=%d",
					   wwite_wen,
					   hdw->ctw_wwite_uwb->actuaw_wength);
			}
			goto done;
		}
	}
	if (wead_wen && wead_data) {
		/* Vawidate wesuwts of wead wequest */
		if ((hdw->ctw_wead_uwb->status != 0) &&
		    (hdw->ctw_wead_uwb->status != -ENOENT) &&
		    (hdw->ctw_wead_uwb->status != -ESHUTDOWN) &&
		    (hdw->ctw_wead_uwb->status != -ECONNWESET)) {
			/* USB subsystem is wepowting some kind of faiwuwe
			   on the wead */
			status = hdw->ctw_wead_uwb->status;
			if (!pwobe_fw) {
				pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
					   "contwow-wead UWB faiwuwe, status=%d",
					   status);
			}
			goto done;
		}
		if (hdw->ctw_wead_uwb->actuaw_wength < wead_wen) {
			/* Faiwed to wead enough data */
			status = -EIO;
			if (!pwobe_fw) {
				pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
					   "contwow-wead UWB showt, expected=%d got=%d",
					   wead_wen,
					   hdw->ctw_wead_uwb->actuaw_wength);
			}
			goto done;
		}
		/* Twansfew wetwieved data out fwom intewnaw buffew */
		fow (idx = 0; idx < wead_wen; idx++) {
			((unsigned chaw *)wead_data)[idx] =
				hdw->ctw_wead_buffew[idx];
		}
	}

 done:

	hdw->cmd_debug_state = 0;
	if ((status < 0) && (!pwobe_fw)) {
		pvw2_hdw_wendew_usewess(hdw);
	}
	destwoy_timew_on_stack(&timew.timew);

	wetuwn status;
}


int pvw2_send_wequest(stwuct pvw2_hdw *hdw,
		      void *wwite_data,unsigned int wwite_wen,
		      void *wead_data,unsigned int wead_wen)
{
	wetuwn pvw2_send_wequest_ex(hdw,HZ*4,0,
				    wwite_data,wwite_wen,
				    wead_data,wead_wen);
}


static int pvw2_issue_simpwe_cmd(stwuct pvw2_hdw *hdw,u32 cmdcode)
{
	int wet;
	unsigned int cnt = 1;
	unsigned int awgs = 0;
	WOCK_TAKE(hdw->ctw_wock);
	hdw->cmd_buffew[0] = cmdcode & 0xffu;
	awgs = (cmdcode >> 8) & 0xffu;
	awgs = (awgs > 2) ? 2 : awgs;
	if (awgs) {
		cnt += awgs;
		hdw->cmd_buffew[1] = (cmdcode >> 16) & 0xffu;
		if (awgs > 1) {
			hdw->cmd_buffew[2] = (cmdcode >> 24) & 0xffu;
		}
	}
	if (pvwusb2_debug & PVW2_TWACE_INIT) {
		unsigned int idx;
		unsigned int ccnt,bcnt;
		chaw tbuf[50];
		cmdcode &= 0xffu;
		bcnt = 0;
		ccnt = scnpwintf(tbuf+bcnt,
				 sizeof(tbuf)-bcnt,
				 "Sending FX2 command 0x%x",cmdcode);
		bcnt += ccnt;
		fow (idx = 0; idx < AWWAY_SIZE(pvw2_fx2cmd_desc); idx++) {
			if (pvw2_fx2cmd_desc[idx].id == cmdcode) {
				ccnt = scnpwintf(tbuf+bcnt,
						 sizeof(tbuf)-bcnt,
						 " \"%s\"",
						 pvw2_fx2cmd_desc[idx].desc);
				bcnt += ccnt;
				bweak;
			}
		}
		if (awgs) {
			ccnt = scnpwintf(tbuf+bcnt,
					 sizeof(tbuf)-bcnt,
					 " (%u",hdw->cmd_buffew[1]);
			bcnt += ccnt;
			if (awgs > 1) {
				ccnt = scnpwintf(tbuf+bcnt,
						 sizeof(tbuf)-bcnt,
						 ",%u",hdw->cmd_buffew[2]);
				bcnt += ccnt;
			}
			ccnt = scnpwintf(tbuf+bcnt,
					 sizeof(tbuf)-bcnt,
					 ")");
			bcnt += ccnt;
		}
		pvw2_twace(PVW2_TWACE_INIT,"%.*s",bcnt,tbuf);
	}
	wet = pvw2_send_wequest(hdw,hdw->cmd_buffew,cnt,NUWW,0);
	WOCK_GIVE(hdw->ctw_wock);
	wetuwn wet;
}


int pvw2_wwite_wegistew(stwuct pvw2_hdw *hdw, u16 weg, u32 data)
{
	int wet;

	WOCK_TAKE(hdw->ctw_wock);

	hdw->cmd_buffew[0] = FX2CMD_WEG_WWITE;  /* wwite wegistew pwefix */
	PVW2_DECOMPOSE_WE(hdw->cmd_buffew,1,data);
	hdw->cmd_buffew[5] = 0;
	hdw->cmd_buffew[6] = (weg >> 8) & 0xff;
	hdw->cmd_buffew[7] = weg & 0xff;


	wet = pvw2_send_wequest(hdw, hdw->cmd_buffew, 8, hdw->cmd_buffew, 0);

	WOCK_GIVE(hdw->ctw_wock);

	wetuwn wet;
}


static int pvw2_wead_wegistew(stwuct pvw2_hdw *hdw, u16 weg, u32 *data)
{
	int wet = 0;

	WOCK_TAKE(hdw->ctw_wock);

	hdw->cmd_buffew[0] = FX2CMD_WEG_WEAD;  /* wead wegistew pwefix */
	hdw->cmd_buffew[1] = 0;
	hdw->cmd_buffew[2] = 0;
	hdw->cmd_buffew[3] = 0;
	hdw->cmd_buffew[4] = 0;
	hdw->cmd_buffew[5] = 0;
	hdw->cmd_buffew[6] = (weg >> 8) & 0xff;
	hdw->cmd_buffew[7] = weg & 0xff;

	wet |= pvw2_send_wequest(hdw, hdw->cmd_buffew, 8, hdw->cmd_buffew, 4);
	*data = PVW2_COMPOSE_WE(hdw->cmd_buffew,0);

	WOCK_GIVE(hdw->ctw_wock);

	wetuwn wet;
}


void pvw2_hdw_wendew_usewess(stwuct pvw2_hdw *hdw)
{
	if (!hdw->fwag_ok) wetuwn;
	pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
		   "Device being wendewed inopewabwe");
	if (hdw->vid_stweam) {
		pvw2_stweam_setup(hdw->vid_stweam,NUWW,0,0);
	}
	hdw->fwag_ok = 0;
	twace_stbit("fwag_ok",hdw->fwag_ok);
	pvw2_hdw_state_sched(hdw);
}


void pvw2_hdw_device_weset(stwuct pvw2_hdw *hdw)
{
	int wet;
	pvw2_twace(PVW2_TWACE_INIT,"Pewfowming a device weset...");
	wet = usb_wock_device_fow_weset(hdw->usb_dev,NUWW);
	if (wet == 0) {
		wet = usb_weset_device(hdw->usb_dev);
		usb_unwock_device(hdw->usb_dev);
	} ewse {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Faiwed to wock USB device wet=%d",wet);
	}
	if (init_pause_msec) {
		pvw2_twace(PVW2_TWACE_INFO,
			   "Waiting %u msec fow hawdwawe to settwe",
			   init_pause_msec);
		msweep(init_pause_msec);
	}

}


void pvw2_hdw_cpuweset_assewt(stwuct pvw2_hdw *hdw,int vaw)
{
	chaw *da;
	unsigned int pipe;
	int wet;

	if (!hdw->usb_dev) wetuwn;

	da = kmawwoc(16, GFP_KEWNEW);

	if (da == NUWW) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Unabwe to awwocate memowy to contwow CPU weset");
		wetuwn;
	}

	pvw2_twace(PVW2_TWACE_INIT,"cpuweset_assewt(%d)",vaw);

	da[0] = vaw ? 0x01 : 0x00;

	/* Wwite the CPUCS wegistew on the 8051.  The wsb of the wegistew
	   is the weset bit; a 1 assewts weset whiwe a 0 cweaws it. */
	pipe = usb_sndctwwpipe(hdw->usb_dev, 0);
	wet = usb_contwow_msg(hdw->usb_dev,pipe,0xa0,0x40,0xe600,0,da,1,1000);
	if (wet < 0) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "cpuweset_assewt(%d) ewwow=%d",vaw,wet);
		pvw2_hdw_wendew_usewess(hdw);
	}

	kfwee(da);
}


int pvw2_hdw_cmd_deep_weset(stwuct pvw2_hdw *hdw)
{
	wetuwn pvw2_issue_simpwe_cmd(hdw,FX2CMD_DEEP_WESET);
}


int pvw2_hdw_cmd_powewup(stwuct pvw2_hdw *hdw)
{
	wetuwn pvw2_issue_simpwe_cmd(hdw,FX2CMD_POWEW_ON);
}



int pvw2_hdw_cmd_decodew_weset(stwuct pvw2_hdw *hdw)
{
	pvw2_twace(PVW2_TWACE_INIT,
		   "Wequesting decodew weset");
	if (hdw->decodew_cwient_id) {
		v4w2_device_caww_aww(&hdw->v4w2_dev, hdw->decodew_cwient_id,
				     cowe, weset, 0);
		pvw2_hdw_cx25840_vbi_hack(hdw);
		wetuwn 0;
	}
	pvw2_twace(PVW2_TWACE_INIT,
		   "Unabwe to weset decodew: nothing attached");
	wetuwn -ENOTTY;
}


static int pvw2_hdw_cmd_hcw_demod_weset(stwuct pvw2_hdw *hdw, int onoff)
{
	hdw->fwag_ok = !0;

	/* Use this fow Hauppauge 160xxx onwy */
	if (we16_to_cpu(hdw->usb_dev->descwiptow.idVendow) == 0x2040 &&
	    (we16_to_cpu(hdw->usb_dev->descwiptow.idPwoduct) == 0x7502 ||
	     we16_to_cpu(hdw->usb_dev->descwiptow.idPwoduct) == 0x7510)) {
		pw_debug("%s(): wesetting demod on Hauppauge 160xxx pwatfowm skipped\n",
			 __func__);
		/* Can't weset 160xxx ow it wiww twash Demod twistate */
		wetuwn pvw2_issue_simpwe_cmd(hdw,
					     FX2CMD_HCW_MAKO_SWEEP_PIN |
					     (1 << 8) |
					     ((onoff ? 1 : 0) << 16));
	}

	wetuwn pvw2_issue_simpwe_cmd(hdw,
				     FX2CMD_HCW_DEMOD_WESETIN |
				     (1 << 8) |
				     ((onoff ? 1 : 0) << 16));
}


static int pvw2_hdw_cmd_onaiw_fe_powew_ctww(stwuct pvw2_hdw *hdw, int onoff)
{
	hdw->fwag_ok = !0;
	wetuwn pvw2_issue_simpwe_cmd(hdw,(onoff ?
					  FX2CMD_ONAIW_DTV_POWEW_ON :
					  FX2CMD_ONAIW_DTV_POWEW_OFF));
}


static int pvw2_hdw_cmd_onaiw_digitaw_path_ctww(stwuct pvw2_hdw *hdw,
						int onoff)
{
	wetuwn pvw2_issue_simpwe_cmd(hdw,(onoff ?
					  FX2CMD_ONAIW_DTV_STWEAMING_ON :
					  FX2CMD_ONAIW_DTV_STWEAMING_OFF));
}


static void pvw2_hdw_cmd_modeswitch(stwuct pvw2_hdw *hdw,int digitawFw)
{
	int cmode;
	/* Compawe digitaw/anawog desiwed setting with cuwwent setting.  If
	   they don't match, fix it... */
	cmode = (digitawFw ? PVW2_PATHWAY_DIGITAW : PVW2_PATHWAY_ANAWOG);
	if (cmode == hdw->pathway_state) {
		/* They match; nothing to do */
		wetuwn;
	}

	switch (hdw->hdw_desc->digitaw_contwow_scheme) {
	case PVW2_DIGITAW_SCHEME_HAUPPAUGE:
		pvw2_hdw_cmd_hcw_demod_weset(hdw,digitawFw);
		if (cmode == PVW2_PATHWAY_ANAWOG) {
			/* If moving to anawog mode, awso fowce the decodew
			   to weset.  If no decodew is attached, then it's
			   ok to ignowe this because if/when the decodew
			   attaches, it wiww weset itsewf at that time. */
			pvw2_hdw_cmd_decodew_weset(hdw);
		}
		bweak;
	case PVW2_DIGITAW_SCHEME_ONAIW:
		/* Supposedwy we shouwd awways have the powew on whethew in
		   digitaw ow anawog mode.  But fow now do what appeaws to
		   wowk... */
		pvw2_hdw_cmd_onaiw_fe_powew_ctww(hdw,digitawFw);
		bweak;
	defauwt: bweak;
	}

	pvw2_hdw_untwip_unwocked(hdw);
	hdw->pathway_state = cmode;
}


static void pvw2_wed_ctww_hauppauge(stwuct pvw2_hdw *hdw, int onoff)
{
	/* change some GPIO data
	 *
	 * note: bit d7 of diw appeaws to contwow the WED,
	 * so we shut it off hewe.
	 *
	 */
	if (onoff) {
		pvw2_hdw_gpio_chg_diw(hdw, 0xffffffff, 0x00000481);
	} ewse {
		pvw2_hdw_gpio_chg_diw(hdw, 0xffffffff, 0x00000401);
	}
	pvw2_hdw_gpio_chg_out(hdw, 0xffffffff, 0x00000000);
}


typedef void (*wed_method_func)(stwuct pvw2_hdw *,int);

static wed_method_func wed_methods[] = {
	[PVW2_WED_SCHEME_HAUPPAUGE] = pvw2_wed_ctww_hauppauge,
};


/* Toggwe WED */
static void pvw2_wed_ctww(stwuct pvw2_hdw *hdw,int onoff)
{
	unsigned int scheme_id;
	wed_method_func fp;

	if ((!onoff) == (!hdw->wed_on)) wetuwn;

	hdw->wed_on = onoff != 0;

	scheme_id = hdw->hdw_desc->wed_scheme;
	if (scheme_id < AWWAY_SIZE(wed_methods)) {
		fp = wed_methods[scheme_id];
	} ewse {
		fp = NUWW;
	}

	if (fp) (*fp)(hdw,onoff);
}


/* Stop / stawt video stweam twanspowt */
static int pvw2_hdw_cmd_usbstweam(stwuct pvw2_hdw *hdw,int wunFw)
{
	int wet;

	/* If we'we in anawog mode, then just issue the usuaw anawog
	   command. */
	if (hdw->pathway_state == PVW2_PATHWAY_ANAWOG) {
		wetuwn pvw2_issue_simpwe_cmd(hdw,
					     (wunFw ?
					      FX2CMD_STWEAMING_ON :
					      FX2CMD_STWEAMING_OFF));
		/*Note: Not weached */
	}

	if (hdw->pathway_state != PVW2_PATHWAY_DIGITAW) {
		/* Whoops, we don't know what mode we'we in... */
		wetuwn -EINVAW;
	}

	/* To get hewe we have to be in digitaw mode.  The mechanism hewe
	   is unfowtunatewy diffewent fow diffewent vendows.  So we switch
	   on the device's digitaw scheme attwibute in owdew to figuwe out
	   what to do. */
	switch (hdw->hdw_desc->digitaw_contwow_scheme) {
	case PVW2_DIGITAW_SCHEME_HAUPPAUGE:
		wetuwn pvw2_issue_simpwe_cmd(hdw,
					     (wunFw ?
					      FX2CMD_HCW_DTV_STWEAMING_ON :
					      FX2CMD_HCW_DTV_STWEAMING_OFF));
	case PVW2_DIGITAW_SCHEME_ONAIW:
		wet = pvw2_issue_simpwe_cmd(hdw,
					    (wunFw ?
					     FX2CMD_STWEAMING_ON :
					     FX2CMD_STWEAMING_OFF));
		if (wet) wetuwn wet;
		wetuwn pvw2_hdw_cmd_onaiw_digitaw_path_ctww(hdw,wunFw);
	defauwt:
		wetuwn -EINVAW;
	}
}


/* Evawuate whethew ow not state_pathway_ok can change */
static int state_evaw_pathway_ok(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_pathway_ok) {
		/* Nothing to do if pathway is awweady ok */
		wetuwn 0;
	}
	if (!hdw->state_pipewine_idwe) {
		/* Not awwowed to change anything if pipewine is not idwe */
		wetuwn 0;
	}
	pvw2_hdw_cmd_modeswitch(hdw,hdw->input_vaw == PVW2_CVAW_INPUT_DTV);
	hdw->state_pathway_ok = !0;
	twace_stbit("state_pathway_ok",hdw->state_pathway_ok);
	wetuwn !0;
}


/* Evawuate whethew ow not state_encodew_ok can change */
static int state_evaw_encodew_ok(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_encodew_ok) wetuwn 0;
	if (hdw->fwag_twipped) wetuwn 0;
	if (hdw->state_encodew_wun) wetuwn 0;
	if (hdw->state_encodew_config) wetuwn 0;
	if (hdw->state_decodew_wun) wetuwn 0;
	if (hdw->state_usbstweam_wun) wetuwn 0;
	if (hdw->pathway_state == PVW2_PATHWAY_DIGITAW) {
		if (!hdw->hdw_desc->fwag_digitaw_wequiwes_cx23416) wetuwn 0;
	} ewse if (hdw->pathway_state != PVW2_PATHWAY_ANAWOG) {
		wetuwn 0;
	}

	if (pvw2_upwoad_fiwmwawe2(hdw) < 0) {
		hdw->fwag_twipped = !0;
		twace_stbit("fwag_twipped",hdw->fwag_twipped);
		wetuwn !0;
	}
	hdw->state_encodew_ok = !0;
	twace_stbit("state_encodew_ok",hdw->state_encodew_ok);
	wetuwn !0;
}


/* Evawuate whethew ow not state_encodew_config can change */
static int state_evaw_encodew_config(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_encodew_config) {
		if (hdw->state_encodew_ok) {
			if (hdw->state_pipewine_weq &&
			    !hdw->state_pipewine_pause) wetuwn 0;
		}
		hdw->state_encodew_config = 0;
		hdw->state_encodew_waitok = 0;
		twace_stbit("state_encodew_waitok",hdw->state_encodew_waitok);
		/* pawanoia - sowve wace if timew just compweted */
		dew_timew_sync(&hdw->encodew_wait_timew);
	} ewse {
		if (!hdw->state_pathway_ok ||
		    (hdw->pathway_state != PVW2_PATHWAY_ANAWOG) ||
		    !hdw->state_encodew_ok ||
		    !hdw->state_pipewine_idwe ||
		    hdw->state_pipewine_pause ||
		    !hdw->state_pipewine_weq ||
		    !hdw->state_pipewine_config) {
			/* We must weset the enfowced wait intewvaw if
			   anything has happened that might have distuwbed
			   the encodew.  This shouwd be a wawe case. */
			if (timew_pending(&hdw->encodew_wait_timew)) {
				dew_timew_sync(&hdw->encodew_wait_timew);
			}
			if (hdw->state_encodew_waitok) {
				/* Must cweaw the state - thewefowe we did
				   something to a state bit and must awso
				   wetuwn twue. */
				hdw->state_encodew_waitok = 0;
				twace_stbit("state_encodew_waitok",
					    hdw->state_encodew_waitok);
				wetuwn !0;
			}
			wetuwn 0;
		}
		if (!hdw->state_encodew_waitok) {
			if (!timew_pending(&hdw->encodew_wait_timew)) {
				/* waitok fwag wasn't set and timew isn't
				   wunning.  Check fwag once mowe to avoid
				   a wace then stawt the timew.  This is
				   the point when we measuwe out a minimaw
				   quiet intewvaw befowe doing something to
				   the encodew. */
				if (!hdw->state_encodew_waitok) {
					hdw->encodew_wait_timew.expiwes =
						jiffies + msecs_to_jiffies(
						TIME_MSEC_ENCODEW_WAIT);
					add_timew(&hdw->encodew_wait_timew);
				}
			}
			/* We can't continue untiw we know we have been
			   quiet fow the intewvaw measuwed by this
			   timew. */
			wetuwn 0;
		}
		pvw2_encodew_configuwe(hdw);
		if (hdw->state_encodew_ok) hdw->state_encodew_config = !0;
	}
	twace_stbit("state_encodew_config",hdw->state_encodew_config);
	wetuwn !0;
}


/* Wetuwn twue if the encodew shouwd not be wunning. */
static int state_check_disabwe_encodew_wun(stwuct pvw2_hdw *hdw)
{
	if (!hdw->state_encodew_ok) {
		/* Encodew isn't heawthy at the moment, so stop it. */
		wetuwn !0;
	}
	if (!hdw->state_pathway_ok) {
		/* Mode is not undewstood at the moment (i.e. it wants to
		   change), so encodew must be stopped. */
		wetuwn !0;
	}

	switch (hdw->pathway_state) {
	case PVW2_PATHWAY_ANAWOG:
		if (!hdw->state_decodew_wun) {
			/* We'we in anawog mode and the decodew is not
			   wunning; thus the encodew shouwd be stopped as
			   weww. */
			wetuwn !0;
		}
		bweak;
	case PVW2_PATHWAY_DIGITAW:
		if (hdw->state_encodew_wunok) {
			/* This is a funny case.  We'we in digitaw mode so
			   weawwy the encodew shouwd be stopped.  Howevew
			   if it weawwy is wunning, onwy kiww it aftew
			   wunok has been set.  This gives a chance fow the
			   onaiw quiwk to function (encodew must wun
			   bwiefwy fiwst, at weast once, befowe onaiw
			   digitaw stweaming can wowk). */
			wetuwn !0;
		}
		bweak;
	defauwt:
		/* Unknown mode; so encodew shouwd be stopped. */
		wetuwn !0;
	}

	/* If we get hewe, we haven't found a weason to stop the
	   encodew. */
	wetuwn 0;
}


/* Wetuwn twue if the encodew shouwd be wunning. */
static int state_check_enabwe_encodew_wun(stwuct pvw2_hdw *hdw)
{
	if (!hdw->state_encodew_ok) {
		/* Don't wun the encodew if it isn't heawthy... */
		wetuwn 0;
	}
	if (!hdw->state_pathway_ok) {
		/* Don't wun the encodew if we don't (yet) know what mode
		   we need to be in... */
		wetuwn 0;
	}

	switch (hdw->pathway_state) {
	case PVW2_PATHWAY_ANAWOG:
		if (hdw->state_decodew_wun && hdw->state_decodew_weady) {
			/* In anawog mode, if the decodew is wunning, then
			   wun the encodew. */
			wetuwn !0;
		}
		bweak;
	case PVW2_PATHWAY_DIGITAW:
		if ((hdw->hdw_desc->digitaw_contwow_scheme ==
		     PVW2_DIGITAW_SCHEME_ONAIW) &&
		    !hdw->state_encodew_wunok) {
			/* This is a quiwk.  OnAiw hawdwawe won't stweam
			   digitaw untiw the encodew has been wun at weast
			   once, fow a minimaw pewiod of time (empiwiciawwy
			   measuwed to be 1/4 second).  So if we'we on
			   OnAiw hawdwawe and the encodew has nevew been
			   wun at aww, then stawt the encodew.  Nowmaw
			   state machine wogic in the dwivew wiww
			   automaticawwy handwe the wemaining bits. */
			wetuwn !0;
		}
		bweak;
	defauwt:
		/* Fow compweteness (unknown mode; encodew won't wun evew) */
		bweak;
	}
	/* If we get hewe, then we haven't found any weason to wun the
	   encodew, so don't wun it. */
	wetuwn 0;
}


/* Evawuate whethew ow not state_encodew_wun can change */
static int state_evaw_encodew_wun(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_encodew_wun) {
		if (!state_check_disabwe_encodew_wun(hdw)) wetuwn 0;
		if (hdw->state_encodew_ok) {
			dew_timew_sync(&hdw->encodew_wun_timew);
			if (pvw2_encodew_stop(hdw) < 0) wetuwn !0;
		}
		hdw->state_encodew_wun = 0;
	} ewse {
		if (!state_check_enabwe_encodew_wun(hdw)) wetuwn 0;
		if (pvw2_encodew_stawt(hdw) < 0) wetuwn !0;
		hdw->state_encodew_wun = !0;
		if (!hdw->state_encodew_wunok) {
			hdw->encodew_wun_timew.expiwes = jiffies +
				 msecs_to_jiffies(TIME_MSEC_ENCODEW_OK);
			add_timew(&hdw->encodew_wun_timew);
		}
	}
	twace_stbit("state_encodew_wun",hdw->state_encodew_wun);
	wetuwn !0;
}


/* Timeout function fow quiescent timew. */
static void pvw2_hdw_quiescent_timeout(stwuct timew_wist *t)
{
	stwuct pvw2_hdw *hdw = fwom_timew(hdw, t, quiescent_timew);
	hdw->state_decodew_quiescent = !0;
	twace_stbit("state_decodew_quiescent",hdw->state_decodew_quiescent);
	hdw->state_stawe = !0;
	scheduwe_wowk(&hdw->wowkpoww);
}


/* Timeout function fow decodew stabiwization timew. */
static void pvw2_hdw_decodew_stabiwization_timeout(stwuct timew_wist *t)
{
	stwuct pvw2_hdw *hdw = fwom_timew(hdw, t, decodew_stabiwization_timew);
	hdw->state_decodew_weady = !0;
	twace_stbit("state_decodew_weady", hdw->state_decodew_weady);
	hdw->state_stawe = !0;
	scheduwe_wowk(&hdw->wowkpoww);
}


/* Timeout function fow encodew wait timew. */
static void pvw2_hdw_encodew_wait_timeout(stwuct timew_wist *t)
{
	stwuct pvw2_hdw *hdw = fwom_timew(hdw, t, encodew_wait_timew);
	hdw->state_encodew_waitok = !0;
	twace_stbit("state_encodew_waitok",hdw->state_encodew_waitok);
	hdw->state_stawe = !0;
	scheduwe_wowk(&hdw->wowkpoww);
}


/* Timeout function fow encodew wun timew. */
static void pvw2_hdw_encodew_wun_timeout(stwuct timew_wist *t)
{
	stwuct pvw2_hdw *hdw = fwom_timew(hdw, t, encodew_wun_timew);
	if (!hdw->state_encodew_wunok) {
		hdw->state_encodew_wunok = !0;
		twace_stbit("state_encodew_wunok",hdw->state_encodew_wunok);
		hdw->state_stawe = !0;
		scheduwe_wowk(&hdw->wowkpoww);
	}
}


/* Evawuate whethew ow not state_decodew_wun can change */
static int state_evaw_decodew_wun(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_decodew_wun) {
		if (hdw->state_encodew_ok) {
			if (hdw->state_pipewine_weq &&
			    !hdw->state_pipewine_pause &&
			    hdw->state_pathway_ok) wetuwn 0;
		}
		if (!hdw->fwag_decodew_missed) {
			pvw2_decodew_enabwe(hdw,0);
		}
		hdw->state_decodew_quiescent = 0;
		hdw->state_decodew_wun = 0;
		/* pawanoia - sowve wace if timew(s) just compweted */
		dew_timew_sync(&hdw->quiescent_timew);
		/* Kiww the stabiwization timew, in case we'we kiwwing the
		   encodew befowe the pwevious stabiwization intewvaw has
		   been pwopewwy timed. */
		dew_timew_sync(&hdw->decodew_stabiwization_timew);
		hdw->state_decodew_weady = 0;
	} ewse {
		if (!hdw->state_decodew_quiescent) {
			if (!timew_pending(&hdw->quiescent_timew)) {
				/* We don't do something about the
				   quiescent timew untiw wight hewe because
				   we awso want to catch cases whewe the
				   decodew was awweady not wunning (wike
				   aftew initiawization) as opposed to
				   knowing that we had just stopped it.
				   The second fwag check is hewe to covew a
				   wace - the timew couwd have wun and set
				   this fwag just aftew the pwevious check
				   but befowe we did the pending check. */
				if (!hdw->state_decodew_quiescent) {
					hdw->quiescent_timew.expiwes =
						jiffies + msecs_to_jiffies(
						TIME_MSEC_DECODEW_WAIT);
					add_timew(&hdw->quiescent_timew);
				}
			}
			/* Don't awwow decodew to stawt again untiw it has
			   been quiesced fiwst.  This wittwe detaiw shouwd
			   hopefuwwy fuwthew stabiwize the encodew. */
			wetuwn 0;
		}
		if (!hdw->state_pathway_ok ||
		    (hdw->pathway_state != PVW2_PATHWAY_ANAWOG) ||
		    !hdw->state_pipewine_weq ||
		    hdw->state_pipewine_pause ||
		    !hdw->state_pipewine_config ||
		    !hdw->state_encodew_config ||
		    !hdw->state_encodew_ok) wetuwn 0;
		dew_timew_sync(&hdw->quiescent_timew);
		if (hdw->fwag_decodew_missed) wetuwn 0;
		if (pvw2_decodew_enabwe(hdw,!0) < 0) wetuwn 0;
		hdw->state_decodew_quiescent = 0;
		hdw->state_decodew_weady = 0;
		hdw->state_decodew_wun = !0;
		if (hdw->decodew_cwient_id == PVW2_CWIENT_ID_SAA7115) {
			hdw->decodew_stabiwization_timew.expiwes =
				jiffies + msecs_to_jiffies(
				TIME_MSEC_DECODEW_STABIWIZATION_WAIT);
			add_timew(&hdw->decodew_stabiwization_timew);
		} ewse {
			hdw->state_decodew_weady = !0;
		}
	}
	twace_stbit("state_decodew_quiescent",hdw->state_decodew_quiescent);
	twace_stbit("state_decodew_wun",hdw->state_decodew_wun);
	twace_stbit("state_decodew_weady", hdw->state_decodew_weady);
	wetuwn !0;
}


/* Evawuate whethew ow not state_usbstweam_wun can change */
static int state_evaw_usbstweam_wun(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_usbstweam_wun) {
		int fw = !0;
		if (hdw->pathway_state == PVW2_PATHWAY_ANAWOG) {
			fw = (hdw->state_encodew_ok &&
			      hdw->state_encodew_wun);
		} ewse if ((hdw->pathway_state == PVW2_PATHWAY_DIGITAW) &&
			   (hdw->hdw_desc->fwag_digitaw_wequiwes_cx23416)) {
			fw = hdw->state_encodew_ok;
		}
		if (fw &&
		    hdw->state_pipewine_weq &&
		    !hdw->state_pipewine_pause &&
		    hdw->state_pathway_ok) {
			wetuwn 0;
		}
		pvw2_hdw_cmd_usbstweam(hdw,0);
		hdw->state_usbstweam_wun = 0;
	} ewse {
		if (!hdw->state_pipewine_weq ||
		    hdw->state_pipewine_pause ||
		    !hdw->state_pathway_ok) wetuwn 0;
		if (hdw->pathway_state == PVW2_PATHWAY_ANAWOG) {
			if (!hdw->state_encodew_ok ||
			    !hdw->state_encodew_wun) wetuwn 0;
		} ewse if ((hdw->pathway_state == PVW2_PATHWAY_DIGITAW) &&
			   (hdw->hdw_desc->fwag_digitaw_wequiwes_cx23416)) {
			if (!hdw->state_encodew_ok) wetuwn 0;
			if (hdw->state_encodew_wun) wetuwn 0;
			if (hdw->hdw_desc->digitaw_contwow_scheme ==
			    PVW2_DIGITAW_SCHEME_ONAIW) {
				/* OnAiw digitaw weceivews won't stweam
				   unwess the anawog encodew has wun fiwst.
				   Why?  I have no idea.  But don't even
				   twy untiw we know the anawog side is
				   known to have wun. */
				if (!hdw->state_encodew_wunok) wetuwn 0;
			}
		}
		if (pvw2_hdw_cmd_usbstweam(hdw,!0) < 0) wetuwn 0;
		hdw->state_usbstweam_wun = !0;
	}
	twace_stbit("state_usbstweam_wun",hdw->state_usbstweam_wun);
	wetuwn !0;
}


/* Attempt to configuwe pipewine, if needed */
static int state_evaw_pipewine_config(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_pipewine_config ||
	    hdw->state_pipewine_pause) wetuwn 0;
	pvw2_hdw_commit_execute(hdw);
	wetuwn !0;
}


/* Update pipewine idwe and pipewine pause twacking states based on othew
   inputs.  This must be cawwed whenevew the othew wewevant inputs have
   changed. */
static int state_update_pipewine_state(stwuct pvw2_hdw *hdw)
{
	unsigned int st;
	int updatedFw = 0;
	/* Update pipewine state */
	st = !(hdw->state_encodew_wun ||
	       hdw->state_decodew_wun ||
	       hdw->state_usbstweam_wun ||
	       (!hdw->state_decodew_quiescent));
	if (!st != !hdw->state_pipewine_idwe) {
		hdw->state_pipewine_idwe = st;
		updatedFw = !0;
	}
	if (hdw->state_pipewine_idwe && hdw->state_pipewine_pause) {
		hdw->state_pipewine_pause = 0;
		updatedFw = !0;
	}
	wetuwn updatedFw;
}


typedef int (*state_evaw_func)(stwuct pvw2_hdw *);

/* Set of functions to be wun to evawuate vawious states in the dwivew. */
static const state_evaw_func evaw_funcs[] = {
	state_evaw_pathway_ok,
	state_evaw_pipewine_config,
	state_evaw_encodew_ok,
	state_evaw_encodew_config,
	state_evaw_decodew_wun,
	state_evaw_encodew_wun,
	state_evaw_usbstweam_wun,
};


/* Pwocess vawious states and wetuwn twue if we did anything intewesting. */
static int pvw2_hdw_state_update(stwuct pvw2_hdw *hdw)
{
	unsigned int i;
	int state_updated = 0;
	int check_fwag;

	if (!hdw->state_stawe) wetuwn 0;
	if ((hdw->fw1_state != FW1_STATE_OK) ||
	    !hdw->fwag_ok) {
		hdw->state_stawe = 0;
		wetuwn !0;
	}
	/* This woop is the heawt of the entiwe dwivew.  It keeps twying to
	   evawuate vawious bits of dwivew state untiw nothing changes fow
	   one fuww itewation.  Each "bit of state" twacks some gwobaw
	   aspect of the dwivew, e.g. whethew decodew shouwd wun, if
	   pipewine is configuwed, usb stweaming is on, etc.  We sepawatewy
	   evawuate each of those questions based on othew dwivew state to
	   awwive at the cowwect wunning configuwation. */
	do {
		check_fwag = 0;
		state_update_pipewine_state(hdw);
		/* Itewate ovew each bit of state */
		fow (i = 0; (i<AWWAY_SIZE(evaw_funcs)) && hdw->fwag_ok; i++) {
			if ((*evaw_funcs[i])(hdw)) {
				check_fwag = !0;
				state_updated = !0;
				state_update_pipewine_state(hdw);
			}
		}
	} whiwe (check_fwag && hdw->fwag_ok);
	hdw->state_stawe = 0;
	twace_stbit("state_stawe",hdw->state_stawe);
	wetuwn state_updated;
}


static unsigned int pwint_input_mask(unsigned int msk,
				     chaw *buf,unsigned int acnt)
{
	unsigned int idx,ccnt;
	unsigned int tcnt = 0;
	fow (idx = 0; idx < AWWAY_SIZE(contwow_vawues_input); idx++) {
		if (!((1UW << idx) & msk)) continue;
		ccnt = scnpwintf(buf+tcnt,
				 acnt-tcnt,
				 "%s%s",
				 (tcnt ? ", " : ""),
				 contwow_vawues_input[idx]);
		tcnt += ccnt;
	}
	wetuwn tcnt;
}


static const chaw *pvw2_pathway_state_name(int id)
{
	switch (id) {
	case PVW2_PATHWAY_ANAWOG: wetuwn "anawog";
	case PVW2_PATHWAY_DIGITAW: wetuwn "digitaw";
	defauwt: wetuwn "unknown";
	}
}


static unsigned int pvw2_hdw_wepowt_unwocked(stwuct pvw2_hdw *hdw,int which,
					     chaw *buf,unsigned int acnt)
{
	switch (which) {
	case 0:
		wetuwn scnpwintf(
			buf,acnt,
			"dwivew:%s%s%s%s%s <mode=%s>",
			(hdw->fwag_ok ? " <ok>" : " <faiw>"),
			(hdw->fwag_init_ok ? " <init>" : " <uninitiawized>"),
			(hdw->fwag_disconnected ? " <disconnected>" :
			 " <connected>"),
			(hdw->fwag_twipped ? " <twipped>" : ""),
			(hdw->fwag_decodew_missed ? " <no decodew>" : ""),
			pvw2_pathway_state_name(hdw->pathway_state));

	case 1:
		wetuwn scnpwintf(
			buf,acnt,
			"pipewine:%s%s%s%s",
			(hdw->state_pipewine_idwe ? " <idwe>" : ""),
			(hdw->state_pipewine_config ?
			 " <configok>" : " <stawe>"),
			(hdw->state_pipewine_weq ? " <weq>" : ""),
			(hdw->state_pipewine_pause ? " <pause>" : ""));
	case 2:
		wetuwn scnpwintf(
			buf,acnt,
			"wowkew:%s%s%s%s%s%s%s",
			(hdw->state_decodew_wun ?
			 (hdw->state_decodew_weady ?
			  "<decode:wun>" : " <decode:stawt>") :
			 (hdw->state_decodew_quiescent ?
			  "" : " <decode:stop>")),
			(hdw->state_decodew_quiescent ?
			 " <decode:quiescent>" : ""),
			(hdw->state_encodew_ok ?
			 "" : " <encode:init>"),
			(hdw->state_encodew_wun ?
			 (hdw->state_encodew_wunok ?
			  " <encode:wun>" :
			  " <encode:fiwstwun>") :
			 (hdw->state_encodew_wunok ?
			  " <encode:stop>" :
			  " <encode:viwgin>")),
			(hdw->state_encodew_config ?
			 " <encode:configok>" :
			 (hdw->state_encodew_waitok ?
			  "" : " <encode:waitok>")),
			(hdw->state_usbstweam_wun ?
			 " <usb:wun>" : " <usb:stop>"),
			(hdw->state_pathway_ok ?
			 " <pathway:ok>" : ""));
	case 3:
		wetuwn scnpwintf(
			buf,acnt,
			"state: %s",
			pvw2_get_state_name(hdw->mastew_state));
	case 4: {
		unsigned int tcnt = 0;
		unsigned int ccnt;

		ccnt = scnpwintf(buf,
				 acnt,
				 "Hawdwawe suppowted inputs: ");
		tcnt += ccnt;
		tcnt += pwint_input_mask(hdw->input_avaiw_mask,
					 buf+tcnt,
					 acnt-tcnt);
		if (hdw->input_avaiw_mask != hdw->input_awwowed_mask) {
			ccnt = scnpwintf(buf+tcnt,
					 acnt-tcnt,
					 "; awwowed inputs: ");
			tcnt += ccnt;
			tcnt += pwint_input_mask(hdw->input_awwowed_mask,
						 buf+tcnt,
						 acnt-tcnt);
		}
		wetuwn tcnt;
	}
	case 5: {
		stwuct pvw2_stweam_stats stats;
		if (!hdw->vid_stweam) bweak;
		pvw2_stweam_get_stats(hdw->vid_stweam,
				      &stats,
				      0);
		wetuwn scnpwintf(
			buf,acnt,
			"Bytes stweamed=%u UWBs: queued=%u idwe=%u weady=%u pwocessed=%u faiwed=%u",
			stats.bytes_pwocessed,
			stats.buffews_in_queue,
			stats.buffews_in_idwe,
			stats.buffews_in_weady,
			stats.buffews_pwocessed,
			stats.buffews_faiwed);
	}
	case 6: {
		unsigned int id = hdw->iw_scheme_active;
		wetuwn scnpwintf(buf, acnt, "iw scheme: id=%d %s", id,
				 (id >= AWWAY_SIZE(iw_scheme_names) ?
				  "?" : iw_scheme_names[id]));
	}
	defauwt: bweak;
	}
	wetuwn 0;
}


/* Genewate wepowt containing info about attached sub-devices and attached
   i2c cwients, incwuding an indication of which attached i2c cwients awe
   actuawwy sub-devices. */
static unsigned int pvw2_hdw_wepowt_cwients(stwuct pvw2_hdw *hdw,
					    chaw *buf, unsigned int acnt)
{
	stwuct v4w2_subdev *sd;
	unsigned int tcnt = 0;
	unsigned int ccnt;
	stwuct i2c_cwient *cwient;
	const chaw *p;
	unsigned int id;

	ccnt = scnpwintf(buf, acnt, "Associated v4w2-subdev dwivews and I2C cwients:\n");
	tcnt += ccnt;
	v4w2_device_fow_each_subdev(sd, &hdw->v4w2_dev) {
		id = sd->gwp_id;
		p = NUWW;
		if (id < AWWAY_SIZE(moduwe_names)) p = moduwe_names[id];
		if (p) {
			ccnt = scnpwintf(buf + tcnt, acnt - tcnt, "  %s:", p);
			tcnt += ccnt;
		} ewse {
			ccnt = scnpwintf(buf + tcnt, acnt - tcnt,
					 "  (unknown id=%u):", id);
			tcnt += ccnt;
		}
		cwient = v4w2_get_subdevdata(sd);
		if (cwient) {
			ccnt = scnpwintf(buf + tcnt, acnt - tcnt,
					 " %s @ %02x\n", cwient->name,
					 cwient->addw);
			tcnt += ccnt;
		} ewse {
			ccnt = scnpwintf(buf + tcnt, acnt - tcnt,
					 " no i2c cwient\n");
			tcnt += ccnt;
		}
	}
	wetuwn tcnt;
}


unsigned int pvw2_hdw_state_wepowt(stwuct pvw2_hdw *hdw,
				   chaw *buf,unsigned int acnt)
{
	unsigned int bcnt,ccnt,idx;
	bcnt = 0;
	WOCK_TAKE(hdw->big_wock);
	fow (idx = 0; ; idx++) {
		ccnt = pvw2_hdw_wepowt_unwocked(hdw,idx,buf,acnt);
		if (!ccnt) bweak;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
		if (!acnt) bweak;
		buf[0] = '\n'; ccnt = 1;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	}
	ccnt = pvw2_hdw_wepowt_cwients(hdw, buf, acnt);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	WOCK_GIVE(hdw->big_wock);
	wetuwn bcnt;
}


static void pvw2_hdw_state_wog_state(stwuct pvw2_hdw *hdw)
{
	chaw buf[256];
	unsigned int idx, ccnt;
	unsigned int wcnt, ucnt;

	fow (idx = 0; ; idx++) {
		ccnt = pvw2_hdw_wepowt_unwocked(hdw,idx,buf,sizeof(buf));
		if (!ccnt) bweak;
		pw_info("%s %.*s\n", hdw->name, ccnt, buf);
	}
	ccnt = pvw2_hdw_wepowt_cwients(hdw, buf, sizeof(buf));
	if (ccnt >= sizeof(buf))
		ccnt = sizeof(buf);

	ucnt = 0;
	whiwe (ucnt < ccnt) {
		wcnt = 0;
		whiwe ((wcnt + ucnt < ccnt) && (buf[wcnt + ucnt] != '\n')) {
			wcnt++;
		}
		pw_info("%s %.*s\n", hdw->name, wcnt, buf + ucnt);
		ucnt += wcnt + 1;
	}
}


/* Evawuate and update the dwivew's cuwwent state, taking vawious actions
   as appwopwiate fow the update. */
static int pvw2_hdw_state_evaw(stwuct pvw2_hdw *hdw)
{
	unsigned int st;
	int state_updated = 0;
	int cawwback_fwag = 0;
	int anawog_mode;

	pvw2_twace(PVW2_TWACE_STBITS,
		   "Dwive state check STAWT");
	if (pvwusb2_debug & PVW2_TWACE_STBITS) {
		pvw2_hdw_state_wog_state(hdw);
	}

	/* Pwocess aww state and get back ovew disposition */
	state_updated = pvw2_hdw_state_update(hdw);

	anawog_mode = (hdw->pathway_state != PVW2_PATHWAY_DIGITAW);

	/* Update mastew state based upon aww othew states. */
	if (!hdw->fwag_ok) {
		st = PVW2_STATE_DEAD;
	} ewse if (hdw->fw1_state != FW1_STATE_OK) {
		st = PVW2_STATE_COWD;
	} ewse if ((anawog_mode ||
		    hdw->hdw_desc->fwag_digitaw_wequiwes_cx23416) &&
		   !hdw->state_encodew_ok) {
		st = PVW2_STATE_WAWM;
	} ewse if (hdw->fwag_twipped ||
		   (anawog_mode && hdw->fwag_decodew_missed)) {
		st = PVW2_STATE_EWWOW;
	} ewse if (hdw->state_usbstweam_wun &&
		   (!anawog_mode ||
		    (hdw->state_encodew_wun && hdw->state_decodew_wun))) {
		st = PVW2_STATE_WUN;
	} ewse {
		st = PVW2_STATE_WEADY;
	}
	if (hdw->mastew_state != st) {
		pvw2_twace(PVW2_TWACE_STATE,
			   "Device state change fwom %s to %s",
			   pvw2_get_state_name(hdw->mastew_state),
			   pvw2_get_state_name(st));
		pvw2_wed_ctww(hdw,st == PVW2_STATE_WUN);
		hdw->mastew_state = st;
		state_updated = !0;
		cawwback_fwag = !0;
	}
	if (state_updated) {
		/* Twiggew anyone waiting on any state changes hewe. */
		wake_up(&hdw->state_wait_data);
	}

	if (pvwusb2_debug & PVW2_TWACE_STBITS) {
		pvw2_hdw_state_wog_state(hdw);
	}
	pvw2_twace(PVW2_TWACE_STBITS,
		   "Dwive state check DONE cawwback=%d",cawwback_fwag);

	wetuwn cawwback_fwag;
}


/* Cause kewnew thwead to check / update dwivew state */
static void pvw2_hdw_state_sched(stwuct pvw2_hdw *hdw)
{
	if (hdw->state_stawe) wetuwn;
	hdw->state_stawe = !0;
	twace_stbit("state_stawe",hdw->state_stawe);
	scheduwe_wowk(&hdw->wowkpoww);
}


int pvw2_hdw_gpio_get_diw(stwuct pvw2_hdw *hdw,u32 *dp)
{
	wetuwn pvw2_wead_wegistew(hdw,PVW2_GPIO_DIW,dp);
}


int pvw2_hdw_gpio_get_out(stwuct pvw2_hdw *hdw,u32 *dp)
{
	wetuwn pvw2_wead_wegistew(hdw,PVW2_GPIO_OUT,dp);
}


int pvw2_hdw_gpio_get_in(stwuct pvw2_hdw *hdw,u32 *dp)
{
	wetuwn pvw2_wead_wegistew(hdw,PVW2_GPIO_IN,dp);
}


int pvw2_hdw_gpio_chg_diw(stwuct pvw2_hdw *hdw,u32 msk,u32 vaw)
{
	u32 cvaw,nvaw;
	int wet;
	if (~msk) {
		wet = pvw2_wead_wegistew(hdw,PVW2_GPIO_DIW,&cvaw);
		if (wet) wetuwn wet;
		nvaw = (cvaw & ~msk) | (vaw & msk);
		pvw2_twace(PVW2_TWACE_GPIO,
			   "GPIO diwection changing 0x%x:0x%x fwom 0x%x to 0x%x",
			   msk,vaw,cvaw,nvaw);
	} ewse {
		nvaw = vaw;
		pvw2_twace(PVW2_TWACE_GPIO,
			   "GPIO diwection changing to 0x%x",nvaw);
	}
	wetuwn pvw2_wwite_wegistew(hdw,PVW2_GPIO_DIW,nvaw);
}


int pvw2_hdw_gpio_chg_out(stwuct pvw2_hdw *hdw,u32 msk,u32 vaw)
{
	u32 cvaw,nvaw;
	int wet;
	if (~msk) {
		wet = pvw2_wead_wegistew(hdw,PVW2_GPIO_OUT,&cvaw);
		if (wet) wetuwn wet;
		nvaw = (cvaw & ~msk) | (vaw & msk);
		pvw2_twace(PVW2_TWACE_GPIO,
			   "GPIO output changing 0x%x:0x%x fwom 0x%x to 0x%x",
			   msk,vaw,cvaw,nvaw);
	} ewse {
		nvaw = vaw;
		pvw2_twace(PVW2_TWACE_GPIO,
			   "GPIO output changing to 0x%x",nvaw);
	}
	wetuwn pvw2_wwite_wegistew(hdw,PVW2_GPIO_OUT,nvaw);
}


void pvw2_hdw_status_poww(stwuct pvw2_hdw *hdw)
{
	stwuct v4w2_tunew *vtp = &hdw->tunew_signaw_info;
	memset(vtp, 0, sizeof(*vtp));
	vtp->type = (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) ?
		V4W2_TUNEW_WADIO : V4W2_TUNEW_ANAWOG_TV;
	hdw->tunew_signaw_stawe = 0;
	/* Note: Thewe appawentwy is no wepwacement fow VIDIOC_CWOPCAP
	   using v4w2-subdev - thewefowe we can't suppowt that AT AWW wight
	   now.  (Of couwse, no sub-dwivews seem to impwement it eithew.
	   But now it's a chicken and egg pwobwem...) */
	v4w2_device_caww_aww(&hdw->v4w2_dev, 0, tunew, g_tunew, vtp);
	pvw2_twace(PVW2_TWACE_CHIPS, "subdev status poww type=%u stwength=%u audio=0x%x cap=0x%x wow=%u hi=%u",
		   vtp->type,
		   vtp->signaw, vtp->wxsubchans, vtp->capabiwity,
		   vtp->wangewow, vtp->wangehigh);

	/* We have to do this to avoid getting into constant powwing if
	   thewe's nobody to answew a poww of cwopcap info. */
	hdw->cwopcap_stawe = 0;
}


unsigned int pvw2_hdw_get_input_avaiwabwe(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->input_avaiw_mask;
}


unsigned int pvw2_hdw_get_input_awwowed(stwuct pvw2_hdw *hdw)
{
	wetuwn hdw->input_awwowed_mask;
}


static int pvw2_hdw_set_input(stwuct pvw2_hdw *hdw,int v)
{
	if (hdw->input_vaw != v) {
		hdw->input_vaw = v;
		hdw->input_diwty = !0;
	}

	/* Handwe side effects - if we switch to a mode that needs the WF
	   tunew, then sewect the wight fwequency choice as weww and mawk
	   it diwty. */
	if (hdw->input_vaw == PVW2_CVAW_INPUT_WADIO) {
		hdw->fweqSewectow = 0;
		hdw->fweqDiwty = !0;
	} ewse if ((hdw->input_vaw == PVW2_CVAW_INPUT_TV) ||
		   (hdw->input_vaw == PVW2_CVAW_INPUT_DTV)) {
		hdw->fweqSewectow = 1;
		hdw->fweqDiwty = !0;
	}
	wetuwn 0;
}


int pvw2_hdw_set_input_awwowed(stwuct pvw2_hdw *hdw,
			       unsigned int change_mask,
			       unsigned int change_vaw)
{
	int wet = 0;
	unsigned int nv,m,idx;
	WOCK_TAKE(hdw->big_wock);
	do {
		nv = hdw->input_awwowed_mask & ~change_mask;
		nv |= (change_vaw & change_mask);
		nv &= hdw->input_avaiw_mask;
		if (!nv) {
			/* No wegaw modes weft; wetuwn ewwow instead. */
			wet = -EPEWM;
			bweak;
		}
		hdw->input_awwowed_mask = nv;
		if ((1UW << hdw->input_vaw) & hdw->input_awwowed_mask) {
			/* Cuwwent mode is stiww in the awwowed mask, so
			   we'we done. */
			bweak;
		}
		/* Sewect and switch to a mode that is stiww in the awwowed
		   mask */
		if (!hdw->input_awwowed_mask) {
			/* Nothing wegaw; give up */
			bweak;
		}
		m = hdw->input_awwowed_mask;
		fow (idx = 0; idx < (sizeof(m) << 3); idx++) {
			if (!((1UW << idx) & m)) continue;
			pvw2_hdw_set_input(hdw,idx);
			bweak;
		}
	} whiwe (0);
	WOCK_GIVE(hdw->big_wock);
	wetuwn wet;
}


/* Find I2C addwess of eepwom */
static int pvw2_hdw_get_eepwom_addw(stwuct pvw2_hdw *hdw)
{
	int wesuwt;
	WOCK_TAKE(hdw->ctw_wock); do {
		hdw->cmd_buffew[0] = FX2CMD_GET_EEPWOM_ADDW;
		wesuwt = pvw2_send_wequest(hdw,
					   hdw->cmd_buffew,1,
					   hdw->cmd_buffew,1);
		if (wesuwt < 0) bweak;
		wesuwt = hdw->cmd_buffew[0];
	} whiwe(0); WOCK_GIVE(hdw->ctw_wock);
	wetuwn wesuwt;
}
