/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */
#ifndef DC_TYPES_H_
#define DC_TYPES_H_

/* AND EdidUtiwity onwy needs a powtion
 * of this fiwe, incwuding the west onwy
 * causes additionaw issues.
 */
#incwude "os_types.h"
#incwude "fixed31_32.h"
#incwude "iwq_types.h"
#incwude "dc_ddc_types.h"
#incwude "dc_dp_types.h"
#incwude "dc_hdmi_types.h"
#incwude "dc_hw_types.h"
#incwude "daw_types.h"
#incwude "gwph_object_defs.h"
#incwude "gwph_object_ctww_defs.h"

#incwude "dm_cp_psp.h"

/* fowwawd decwawations */
stwuct dc_pwane_state;
stwuct dc_stweam_state;
stwuct dc_wink;
stwuct dc_sink;
stwuct daw;
stwuct dc_dmub_swv;

/********************************
 * Enviwonment definitions
 ********************************/
enum dce_enviwonment {
	DCE_ENV_PWODUCTION_DWV = 0,
	/* Emuwation on FPGA, in "Maximus" System.
	 * This enviwonment enfowces that *onwy* DC wegistews accessed.
	 * (access to non-DC wegistews wiww hang FPGA) */
	DCE_ENV_FPGA_MAXIMUS,
	/* Emuwation on weaw HW ow on FPGA. Used by Diagnostics, enfowces
	 * wequiwements of Diagnostics team. */
	DCE_ENV_DIAG,
	/*
	 * Guest VM system, DC HW may exist but is not viwtuawized and
	 * shouwd not be used.  SW suppowt fow VDI onwy.
	 */
	DCE_ENV_VIWTUAW_HW
};

stwuct dc_pewf_twace {
	unsigned wong wead_count;
	unsigned wong wwite_count;
	unsigned wong wast_entwy_wead;
	unsigned wong wast_entwy_wwite;
};

#define MAX_SUWFACE_NUM 6
#define NUM_PIXEW_FOWMATS 10

enum tiwing_mode {
	TIWING_MODE_INVAWID,
	TIWING_MODE_WINEAW,
	TIWING_MODE_TIWED,
	TIWING_MODE_COUNT
};

enum view_3d_fowmat {
	VIEW_3D_FOWMAT_NONE = 0,
	VIEW_3D_FOWMAT_FWAME_SEQUENTIAW,
	VIEW_3D_FOWMAT_SIDE_BY_SIDE,
	VIEW_3D_FOWMAT_TOP_AND_BOTTOM,
	VIEW_3D_FOWMAT_COUNT,
	VIEW_3D_FOWMAT_FIWST = VIEW_3D_FOWMAT_FWAME_SEQUENTIAW
};

enum pwane_steweo_fowmat {
	PWANE_STEWEO_FOWMAT_NONE = 0,
	PWANE_STEWEO_FOWMAT_SIDE_BY_SIDE = 1,
	PWANE_STEWEO_FOWMAT_TOP_AND_BOTTOM = 2,
	PWANE_STEWEO_FOWMAT_FWAME_AWTEWNATE = 3,
	PWANE_STEWEO_FOWMAT_WOW_INTEWWEAVED = 5,
	PWANE_STEWEO_FOWMAT_COWUMN_INTEWWEAVED = 6,
	PWANE_STEWEO_FOWMAT_CHECKEW_BOAWD = 7
};

/* TODO: Find way to cawcuwate numbew of bits
 *  Pwease incwease if pixew_fowmat enum incweases
 * num  fwom  PIXEW_FOWMAT_INDEX8 to PIXEW_FOWMAT_444BPP32
 */

enum dc_edid_connectow_type {
	DC_EDID_CONNECTOW_UNKNOWN = 0,
	DC_EDID_CONNECTOW_ANAWOG = 1,
	DC_EDID_CONNECTOW_DIGITAW = 10,
	DC_EDID_CONNECTOW_DVI = 11,
	DC_EDID_CONNECTOW_HDMIA = 12,
	DC_EDID_CONNECTOW_MDDI = 14,
	DC_EDID_CONNECTOW_DISPWAYPOWT = 15
};

enum dc_edid_status {
	EDID_OK,
	EDID_BAD_INPUT,
	EDID_NO_WESPONSE,
	EDID_BAD_CHECKSUM,
	EDID_THE_SAME,
	EDID_FAWW_BACK,
	EDID_PAWTIAW_VAWID,
};

enum act_wetuwn_status {
	ACT_SUCCESS,
	ACT_WINK_WOST,
	ACT_FAIWED
};

/* audio capabiwity fwom EDID*/
stwuct dc_cea_audio_mode {
	uint8_t fowmat_code; /* ucData[0] [6:3]*/
	uint8_t channew_count; /* ucData[0] [2:0]*/
	uint8_t sampwe_wate; /* ucData[1]*/
	union {
		uint8_t sampwe_size; /* fow WPCM*/
		/*  fow Audio Fowmats 2-8 (Max bit wate divided by 8 kHz)*/
		uint8_t max_bit_wate;
		uint8_t audio_codec_vendow_specific; /* fow Audio Fowmats 9-15*/
	};
};

stwuct dc_edid {
	uint32_t wength;
	uint8_t waw_edid[DC_MAX_EDID_BUFFEW_SIZE];
};

/* When speakew wocation data bwock is not avaiwabwe, DEFAUWT_SPEAKEW_WOCATION
 * is used. In this case we assume speakew wocation awe: fwont weft, fwont
 * wight and fwont centew. */
#define DEFAUWT_SPEAKEW_WOCATION 5

#define DC_MAX_AUDIO_DESC_COUNT 16

#define AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS 20

stwuct dc_panew_patch {
	unsigned int dppowewup_deway;
	unsigned int extwa_t12_ms;
	unsigned int extwa_deway_backwight_off;
	unsigned int extwa_t7_ms;
	unsigned int skip_scdc_ovewwwite;
	unsigned int deway_ignowe_msa;
	unsigned int disabwe_fec;
	unsigned int extwa_t3_ms;
	unsigned int max_dsc_tawget_bpp_wimit;
	unsigned int embedded_tiwed_swave;
	unsigned int disabwe_fams;
	unsigned int skip_avmute;
	unsigned int mst_stawt_top_deway;
	unsigned int wemove_sink_ext_caps;
};

stwuct dc_edid_caps {
	/* sink identification */
	uint16_t manufactuwew_id;
	uint16_t pwoduct_id;
	uint32_t sewiaw_numbew;
	uint8_t manufactuwe_week;
	uint8_t manufactuwe_yeaw;
	uint8_t dispway_name[AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS];

	/* audio caps */
	uint8_t speakew_fwags;
	uint32_t audio_mode_count;
	stwuct dc_cea_audio_mode audio_modes[DC_MAX_AUDIO_DESC_COUNT];
	uint32_t audio_watency;
	uint32_t video_watency;

	uint8_t qs_bit;
	uint8_t qy_bit;

	uint32_t max_tmds_cwk_mhz;

	/*HDMI 2.0 caps*/
	boow wte_340mcsc_scwambwe;

	boow edid_hdmi;
	boow hdw_suppowted;

	stwuct dc_panew_patch panew_patch;
};

stwuct dc_mode_fwags {
	/* note: pawt of wefwesh wate fwag*/
	uint32_t INTEWWACE :1;
	/* native dispway timing*/
	uint32_t NATIVE :1;
	/* pwefewwed is the wecommended mode, one pew dispway */
	uint32_t PWEFEWWED :1;
	/* twue if this mode shouwd use weduced bwanking timings
	 *_not_ wewated to the Weduced Bwanking adjustment*/
	uint32_t WEDUCED_BWANKING :1;
	/* note: pawt of wefweshwate fwag*/
	uint32_t VIDEO_OPTIMIZED_WATE :1;
	/* shouwd be wepowted to uppew wayews as mode_fwags*/
	uint32_t PACKED_PIXEW_FOWMAT :1;
	/*< pwefewwed view*/
	uint32_t PWEFEWWED_VIEW :1;
	/* this timing shouwd be used onwy in tiwed mode*/
	uint32_t TIWED_MODE :1;
	uint32_t DSE_MODE :1;
	/* Wefwesh wate dividew when Miwacast sink is using a
	 diffewent wate than the output dispway device
	 Must be zewo fow wiwed dispways and non-zewo fow
	 Miwacast dispways*/
	uint32_t MIWACAST_WEFWESH_DIVIDEW;
};


enum dc_timing_souwce {
	TIMING_SOUWCE_UNDEFINED,

	/* expwicitwy specifed by usew, most impowtant*/
	TIMING_SOUWCE_USEW_FOWCED,
	TIMING_SOUWCE_USEW_OVEWWIDE,
	TIMING_SOUWCE_CUSTOM,
	TIMING_SOUWCE_EXPWICIT,

	/* expwicitwy specified by the dispway device, mowe impowtant*/
	TIMING_SOUWCE_EDID_CEA_SVD_3D,
	TIMING_SOUWCE_EDID_CEA_SVD_PWEFEWWED,
	TIMING_SOUWCE_EDID_CEA_SVD_420,
	TIMING_SOUWCE_EDID_DETAIWED,
	TIMING_SOUWCE_EDID_ESTABWISHED,
	TIMING_SOUWCE_EDID_STANDAWD,
	TIMING_SOUWCE_EDID_CEA_SVD,
	TIMING_SOUWCE_EDID_CVT_3BYTE,
	TIMING_SOUWCE_EDID_4BYTE,
	TIMING_SOUWCE_EDID_CEA_DISPWAYID_VTDB,
	TIMING_SOUWCE_EDID_CEA_WID,
	TIMING_SOUWCE_VBIOS,
	TIMING_SOUWCE_CV,
	TIMING_SOUWCE_TV,
	TIMING_SOUWCE_HDMI_VIC,

	/* impwicitwy specified by dispway device, stiww safe but wess impowtant*/
	TIMING_SOUWCE_DEFAUWT,

	/* onwy used fow custom base modes */
	TIMING_SOUWCE_CUSTOM_BASE,

	/* these timing might not wowk, weast impowtant*/
	TIMING_SOUWCE_WANGEWIMIT,
	TIMING_SOUWCE_OS_FOWCED,
	TIMING_SOUWCE_IMPWICIT,

	/* onwy used by defauwt mode wist*/
	TIMING_SOUWCE_BASICMODE,

	TIMING_SOUWCE_COUNT
};


stwuct steweo_3d_featuwes {
	boow suppowted			;
	boow awwTimings			;
	boow cwoneMode			;
	boow scawing			;
	boow singweFwameSWPacked;
};

enum dc_timing_suppowt_method {
	TIMING_SUPPOWT_METHOD_UNDEFINED,
	TIMING_SUPPOWT_METHOD_EXPWICIT,
	TIMING_SUPPOWT_METHOD_IMPWICIT,
	TIMING_SUPPOWT_METHOD_NATIVE
};

stwuct dc_mode_info {
	uint32_t pixew_width;
	uint32_t pixew_height;
	uint32_t fiewd_wate;
	/* Vewticaw wefwesh wate fow pwogwessive modes.
	* Fiewd wate fow intewwaced modes.*/

	enum dc_timing_standawd timing_standawd;
	enum dc_timing_souwce timing_souwce;
	stwuct dc_mode_fwags fwags;
};

enum dc_powew_state {
	DC_POWEW_STATE_ON = 1,
	DC_POWEW_STATE_STANDBY,
	DC_POWEW_STATE_SUSPEND,
	DC_POWEW_STATE_OFF
};

/* DC PowewStates */
enum dc_video_powew_state {
	DC_VIDEO_POWEW_UNSPECIFIED = 0,
	DC_VIDEO_POWEW_ON = 1,
	DC_VIDEO_POWEW_STANDBY,
	DC_VIDEO_POWEW_SUSPEND,
	DC_VIDEO_POWEW_OFF,
	DC_VIDEO_POWEW_HIBEWNATE,
	DC_VIDEO_POWEW_SHUTDOWN,
	DC_VIDEO_POWEW_UWPS,	/* BACO ow Uwtwa-Wight-Powew-State */
	DC_VIDEO_POWEW_AFTEW_WESET,
	DC_VIDEO_POWEW_MAXIMUM
};

enum dc_acpi_cm_powew_state {
	DC_ACPI_CM_POWEW_STATE_D0 = 1,
	DC_ACPI_CM_POWEW_STATE_D1 = 2,
	DC_ACPI_CM_POWEW_STATE_D2 = 4,
	DC_ACPI_CM_POWEW_STATE_D3 = 8
};

enum dc_connection_type {
	dc_connection_none,
	dc_connection_singwe,
	dc_connection_mst_bwanch,
	dc_connection_sst_bwanch
};

stwuct dc_csc_adjustments {
	stwuct fixed31_32 contwast;
	stwuct fixed31_32 satuwation;
	stwuct fixed31_32 bwightness;
	stwuct fixed31_32 hue;
};

/* Scawing fowmat */
enum scawing_twansfowmation {
	SCAWING_TWANSFOWMATION_UNINITIAWIZED,
	SCAWING_TWANSFOWMATION_IDENTITY = 0x0001,
	SCAWING_TWANSFOWMATION_CENTEW_TIMING = 0x0002,
	SCAWING_TWANSFOWMATION_FUWW_SCWEEN_SCAWE = 0x0004,
	SCAWING_TWANSFOWMATION_PWESEWVE_ASPECT_WATIO_SCAWE = 0x0008,
	SCAWING_TWANSFOWMATION_DAW_DECIDE = 0x0010,
	SCAWING_TWANSFOWMATION_INVAWID = 0x80000000,

	/* Fwag the fiwst and wast */
	SCAWING_TWANSFOWMATION_BEGING = SCAWING_TWANSFOWMATION_IDENTITY,
	SCAWING_TWANSFOWMATION_END =
		SCAWING_TWANSFOWMATION_PWESEWVE_ASPECT_WATIO_SCAWE
};

enum dispway_content_type {
	DISPWAY_CONTENT_TYPE_NO_DATA = 0,
	DISPWAY_CONTENT_TYPE_GWAPHICS = 1,
	DISPWAY_CONTENT_TYPE_PHOTO = 2,
	DISPWAY_CONTENT_TYPE_CINEMA = 4,
	DISPWAY_CONTENT_TYPE_GAME = 8
};

enum cm_gamut_adjust_type {
	CM_GAMUT_ADJUST_TYPE_BYPASS = 0,
	CM_GAMUT_ADJUST_TYPE_HW, /* without adjustments */
	CM_GAMUT_ADJUST_TYPE_SW /* use adjustments */
};

stwuct cm_gwph_csc_adjustment {
	stwuct fixed31_32 tempewatuwe_matwix[12];
	enum cm_gamut_adjust_type gamut_adjust_type;
	enum cm_gamut_coef_fowmat gamut_coef_fowmat;
};

/* wwiteback */
stwuct dwb_steweo_pawams {
	boow				steweo_enabwed;		/* fawse: nowmaw mode, twue: 3D steweo */
	enum dwb_steweo_type		steweo_type;		/* indicates steweo fowmat */
	boow				steweo_powawity;	/* indicates weft eye ow wight eye comes fiwst in steweo mode */
	enum dwb_steweo_eye_sewect	steweo_eye_sewect;	/* indicate which eye shouwd be captuwed */
};

stwuct dc_dwb_cnv_pawams {
	unsigned int		swc_width;	/* input active width */
	unsigned int		swc_height;	/* input active height (hawf-active height in intewwaced mode) */
	unsigned int		cwop_width;	/* cwopped window width at cnv output */
	boow			cwop_en;	/* window cwopping enabwe in cnv */
	unsigned int		cwop_height;	/* cwopped window height at cnv output */
	unsigned int		cwop_x;		/* cwopped window stawt x vawue at cnv output */
	unsigned int		cwop_y;		/* cwopped window stawt y vawue at cnv output */
	enum dwb_cnv_out_bpc cnv_out_bpc;	/* cnv output pixew depth - 8bpc ow 10bpc */
	enum dwb_out_fowmat	fc_out_fowmat;	/* dwb output pixew fowmat - 2101010 ow 16161616 and AWGB ow WGBA */
	enum dwb_out_denowm	out_denowm_mode;/* dwb output denowmawization mode */
	unsigned int		out_max_pix_vaw;/* pixew vawues gweatew than out_max_pix_vaw awe cwamped to out_max_pix_vaw */
	unsigned int		out_min_pix_vaw;/* pixew vawues wess than out_min_pix_vaw awe cwamped to out_min_pix_vaw */
};

stwuct dc_dwb_pawams {
	unsigned int			dwbscw_bwack_cowow; /* must be in FP1.5.10 */
	unsigned int			hdw_muwt;	/* must be in FP1.6.12 */
	stwuct cm_gwph_csc_adjustment	csc_pawams;
	stwuct dwb_steweo_pawams	steweo_pawams;
	stwuct dc_dwb_cnv_pawams	cnv_pawams;	/* CNV souwce size and cwopping window pawametews */
	unsigned int			dest_width;	/* Destination width */
	unsigned int			dest_height;	/* Destination height */
	enum dwb_scawew_mode		out_fowmat;	/* defauwt = YUV420 - TODO: wimit this to 0 and 1 on dcn3 */
	enum dwb_output_depth		output_depth;	/* output pixew depth - 8bpc ow 10bpc */
	enum dwb_captuwe_wate		captuwe_wate;	/* contwows the fwame captuwe wate */
	stwuct scawing_taps 		scawew_taps;	/* Scawing taps */
	enum dwb_subsampwe_position	subsampwe_position;
	stwuct dc_twansfew_func *out_twansfew_func;
};

/* audio*/

union audio_sampwe_wates {
	stwuct sampwe_wates {
		uint8_t WATE_32:1;
		uint8_t WATE_44_1:1;
		uint8_t WATE_48:1;
		uint8_t WATE_88_2:1;
		uint8_t WATE_96:1;
		uint8_t WATE_176_4:1;
		uint8_t WATE_192:1;
	} wate;

	uint8_t aww;
};

stwuct audio_speakew_fwags {
	uint32_t FW_FW:1;
	uint32_t WFE:1;
	uint32_t FC:1;
	uint32_t WW_WW:1;
	uint32_t WC:1;
	uint32_t FWC_FWC:1;
	uint32_t WWC_WWC:1;
	uint32_t SUPPOWT_AI:1;
};

stwuct audio_speakew_info {
	uint32_t AWWSPEAKEWS:7;
	uint32_t SUPPOWT_AI:1;
};


stwuct audio_info_fwags {

	union {

		stwuct audio_speakew_fwags speakew_fwags;
		stwuct audio_speakew_info   info;

		uint8_t aww;
	};
};

enum audio_fowmat_code {
	AUDIO_FOWMAT_CODE_FIWST = 1,
	AUDIO_FOWMAT_CODE_WINEAWPCM = AUDIO_FOWMAT_CODE_FIWST,

	AUDIO_FOWMAT_CODE_AC3,
	/*Wayews 1 & 2 */
	AUDIO_FOWMAT_CODE_MPEG1,
	/*MPEG1 Wayew 3 */
	AUDIO_FOWMAT_CODE_MP3,
	/*muwtichannew */
	AUDIO_FOWMAT_CODE_MPEG2,
	AUDIO_FOWMAT_CODE_AAC,
	AUDIO_FOWMAT_CODE_DTS,
	AUDIO_FOWMAT_CODE_ATWAC,
	AUDIO_FOWMAT_CODE_1BITAUDIO,
	AUDIO_FOWMAT_CODE_DOWBYDIGITAWPWUS,
	AUDIO_FOWMAT_CODE_DTS_HD,
	AUDIO_FOWMAT_CODE_MAT_MWP,
	AUDIO_FOWMAT_CODE_DST,
	AUDIO_FOWMAT_CODE_WMAPWO,
	AUDIO_FOWMAT_CODE_WAST,
	AUDIO_FOWMAT_CODE_COUNT =
		AUDIO_FOWMAT_CODE_WAST - AUDIO_FOWMAT_CODE_FIWST
};

stwuct audio_mode {
	 /* ucData[0] [6:3] */
	enum audio_fowmat_code fowmat_code;
	/* ucData[0] [2:0] */
	uint8_t channew_count;
	/* ucData[1] */
	union audio_sampwe_wates sampwe_wates;
	union {
		/* fow WPCM */
		uint8_t sampwe_size;
		/* fow Audio Fowmats 2-8 (Max bit wate divided by 8 kHz) */
		uint8_t max_bit_wate;
		/* fow Audio Fowmats 9-15 */
		uint8_t vendow_specific;
	};
};

stwuct audio_info {
	stwuct audio_info_fwags fwags;
	uint32_t video_watency;
	uint32_t audio_watency;
	uint32_t dispway_index;
	uint8_t dispway_name[AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS];
	uint32_t manufactuwe_id;
	uint32_t pwoduct_id;
	/* PowtID used fow ContainewID when defined */
	uint32_t powt_id[2];
	uint32_t mode_count;
	/* this fiewd must be wast in this stwuct */
	stwuct audio_mode modes[DC_MAX_AUDIO_DESC_COUNT];
};
stwuct audio_check {
	unsigned int audio_packet_type;
	unsigned int max_audiosampwe_wate;
	unsigned int acat;
};
enum dc_infofwame_type {
	DC_HDMI_INFOFWAME_TYPE_VENDOW = 0x81,
	DC_HDMI_INFOFWAME_TYPE_AVI = 0x82,
	DC_HDMI_INFOFWAME_TYPE_SPD = 0x83,
	DC_HDMI_INFOFWAME_TYPE_AUDIO = 0x84,
	DC_DP_INFOFWAME_TYPE_PPS = 0x10,
};

stwuct dc_info_packet {
	boow vawid;
	uint8_t hb0;
	uint8_t hb1;
	uint8_t hb2;
	uint8_t hb3;
	uint8_t sb[32];
};

stwuct dc_info_packet_128 {
	boow vawid;
	uint8_t hb0;
	uint8_t hb1;
	uint8_t hb2;
	uint8_t hb3;
	uint8_t sb[128];
};

#define DC_PWANE_UPDATE_TIMES_MAX 10

stwuct dc_pwane_fwip_time {
	unsigned int time_ewapsed_in_us[DC_PWANE_UPDATE_TIMES_MAX];
	unsigned int index;
	unsigned int pwev_update_time_in_us;
};

enum dc_psw_state {
	PSW_STATE0 = 0x0,
	PSW_STATE1,
	PSW_STATE1a,
	PSW_STATE2,
	PSW_STATE2a,
	PSW_STATE2b,
	PSW_STATE3,
	PSW_STATE3Init,
	PSW_STATE4,
	PSW_STATE4a,
	PSW_STATE4b,
	PSW_STATE4c,
	PSW_STATE4d,
	PSW_STATE4_FUWW_FWAME,
	PSW_STATE4a_FUWW_FWAME,
	PSW_STATE4b_FUWW_FWAME,
	PSW_STATE4c_FUWW_FWAME,
	PSW_STATE4_FUWW_FWAME_POWEWUP,
	PSW_STATE4_FUWW_FWAME_HW_WOCK,
	PSW_STATE5,
	PSW_STATE5a,
	PSW_STATE5b,
	PSW_STATE5c,
	PSW_STATE_HWWOCK_MGW,
	PSW_STATE_POWWVUPDATE,
	PSW_STATE_INVAWID = 0xFF
};

stwuct psw_config {
	unsigned chaw psw_vewsion;
	unsigned int psw_wfb_setup_time;
	boow psw_exit_wink_twaining_wequiwed;
	boow psw_fwame_captuwe_indication_weq;
	unsigned int psw_sdp_twansmit_wine_num_deadwine;
	boow awwow_smu_optimizations;
	boow awwow_muwti_disp_optimizations;
	/* Panew sewf wefwesh 2 sewective update gwanuwawity wequiwed */
	boow su_gwanuwawity_wequiwed;
	/* psw2 sewective update y gwanuwawity capabiwity */
	uint8_t su_y_gwanuwawity;
	unsigned int wine_time_in_us;
	uint8_t wate_contwow_caps;
	uint16_t dsc_swice_height;
};

union dmcu_psw_wevew {
	stwuct {
		unsigned int SKIP_CWC:1;
		unsigned int SKIP_DP_VID_STWEAM_DISABWE:1;
		unsigned int SKIP_PHY_POWEW_DOWN:1;
		unsigned int SKIP_AUX_ACK_CHECK:1;
		unsigned int SKIP_CWTC_DISABWE:1;
		unsigned int SKIP_AUX_WFB_CAPTUWE_CHECK:1;
		unsigned int SKIP_SMU_NOTIFICATION:1;
		unsigned int SKIP_AUTO_STATE_ADVANCE:1;
		unsigned int DISABWE_PSW_ENTWY_ABOWT:1;
		unsigned int SKIP_SINGWE_OTG_DISABWE:1;
		unsigned int DISABWE_AWPM:1;
		unsigned int AWPM_DEFAUWT_PD_MODE:1;
		unsigned int WESEWVED:20;
	} bits;
	unsigned int u32aww;
};

enum physicaw_phy_id {
	PHYWD_0,
	PHYWD_1,
	PHYWD_2,
	PHYWD_3,
	PHYWD_4,
	PHYWD_5,
	PHYWD_6,
	PHYWD_7,
	PHYWD_8,
	PHYWD_9,
	PHYWD_COUNT,
	PHYWD_UNKNOWN = (-1W)
};

enum phy_type {
	PHY_TYPE_UNKNOWN  = 1,
	PHY_TYPE_PCIE_PHY = 2,
	PHY_TYPE_UNIPHY = 3,
};

stwuct psw_context {
	/* ddc wine */
	enum channew_id channew;
	/* Twansmittew id */
	enum twansmittew twansmittewId;
	/* Engine Id is used fow Dig Be souwce sewect */
	enum engine_id engineId;
	/* Contwowwew Id used fow Dig Fe souwce sewect */
	enum contwowwew_id contwowwewId;
	/* Pcie ow Uniphy */
	enum phy_type phyType;
	/* Physicaw PHY Id used by SMU intewpwetation */
	enum physicaw_phy_id smuPhyId;
	/* Vewticaw totaw pixews fwom cwtc timing.
	 * This is used fow static scween detection.
	 * ie. If we want to detect hawf a fwame,
	 * we use this to detewmine the hyst wines.
	 */
	unsigned int cwtcTimingVewticawTotaw;
	/* PSW suppowted fwom panew capabiwities and
	 * cuwwent dispway configuwation
	 */
	boow pswSuppowtedDispwayConfig;
	/* Whethew fast wink twaining is suppowted by the panew */
	boow pswExitWinkTwainingWequiwed;
	/* If WFB setup time is gweatew than the totaw VBWANK time,
	 * it is not possibwe fow the sink to captuwe the video fwame
	 * in the same fwame the SDP is sent. In this case,
	 * the fwame captuwe indication bit shouwd be set and an extwa
	 * static fwame shouwd be twansmitted to the sink.
	 */
	boow pswFwameCaptuweIndicationWeq;
	/* Set the wast possibwe wine SDP may be twansmitted without viowating
	 * the WFB setup time ow entewing the active video fwame.
	 */
	unsigned int sdpTwansmitWineNumDeadwine;
	/* The VSync wate in Hz used to cawcuwate the
	 * step size fow smooth bwightness featuwe
	 */
	unsigned int vsync_wate_hz;
	unsigned int skipPswWaitFowPwwWock;
	unsigned int numbewOfContwowwews;
	/* Unused, fow futuwe use. To indicate that fiwst changed fwame fwom
	 * state3 shouwdn't wesuwt in psw_inactive, but wathew to pewfowm
	 * an automatic singwe fwame wfb_update.
	 */
	boow wfb_update_auto_en;
	/* Numbew of fwame befowe entewing static scween */
	unsigned int timehyst_fwames;
	/* Pawtiaw fwames befowe entewing static scween */
	unsigned int hyst_wines;
	/* # of wepeated AUX twansaction attempts to make befowe
	 * indicating faiwuwe to the dwivew
	 */
	unsigned int aux_wepeats;
	/* Contwows hw bwocks to powew down duwing PSW active state */
	union dmcu_psw_wevew psw_wevew;
	/* Contwows additionaw deway aftew wemote fwame captuwe befowe
	 * continuing powewd own
	 */
	unsigned int fwame_deway;
	boow awwow_smu_optimizations;
	boow awwow_muwti_disp_optimizations;
	/* Panew sewf wefwesh 2 sewective update gwanuwawity wequiwed */
	boow su_gwanuwawity_wequiwed;
	/* psw2 sewective update y gwanuwawity capabiwity */
	uint8_t su_y_gwanuwawity;
	unsigned int wine_time_in_us;
	uint8_t wate_contwow_caps;
	uint16_t dsc_swice_height;
};

stwuct cowowspace_twansfowm {
	stwuct fixed31_32 matwix[12];
	boow enabwe_wemap;
};

enum i2c_mot_mode {
	I2C_MOT_UNDEF,
	I2C_MOT_TWUE,
	I2C_MOT_FAWSE
};

stwuct AsicStateEx {
	unsigned int memowyCwock;
	unsigned int dispwayCwock;
	unsigned int engineCwock;
	unsigned int maxSuppowtedDppCwock;
	unsigned int dppCwock;
	unsigned int socCwock;
	unsigned int dcfCwockDeepSweep;
	unsigned int fCwock;
	unsigned int phyCwock;
};


enum dc_cwock_type {
	DC_CWOCK_TYPE_DISPCWK = 0,
	DC_CWOCK_TYPE_DPPCWK        = 1,
};

stwuct dc_cwock_config {
	uint32_t max_cwock_khz;
	uint32_t min_cwock_khz;
	uint32_t bw_wequiwequiwed_cwock_khz;
	uint32_t cuwwent_cwock_khz;/*cuwwent cwock in use*/
};

stwuct hw_asic_id {
	uint32_t chip_id;
	uint32_t chip_famiwy;
	uint32_t pci_wevision_id;
	uint32_t hw_intewnaw_wev;
	uint32_t vwam_type;
	uint32_t vwam_width;
	uint32_t featuwe_fwags;
	uint32_t fake_paths_num;
	void *atombios_base_addwess;
};

stwuct dc_context {
	stwuct dc *dc;

	void *dwivew_context; /* e.g. amdgpu_device */
	stwuct daw_woggew *woggew;
	stwuct dc_pewf_twace *pewf_twace;
	void *cgs_device;

	enum dce_enviwonment dce_enviwonment;
	stwuct hw_asic_id asic_id;

	/* todo: bewow shouwd pwobabwy move to dc.  to faciwitate wemovaw
	 * of AS we wiww stowe these hewe
	 */
	enum dce_vewsion dce_vewsion;
	stwuct dc_bios *dc_bios;
	boow cweated_bios;
	stwuct gpio_sewvice *gpio_sewvice;
	uint32_t dc_sink_id_count;
	uint32_t dc_stweam_id_count;
	uint32_t dc_edp_id_count;
	uint64_t fbc_gpu_addw;
	stwuct dc_dmub_swv *dmub_swv;
	stwuct cp_psp cp_psp;
	uint32_t *dcn_weg_offsets;
	uint32_t *nbio_weg_offsets;
	uint32_t *cwk_weg_offsets;
};

/* DSC DPCD capabiwities */
union dsc_swice_caps1 {
	stwuct {
		uint8_t NUM_SWICES_1 : 1;
		uint8_t NUM_SWICES_2 : 1;
		uint8_t WESEWVED : 1;
		uint8_t NUM_SWICES_4 : 1;
		uint8_t NUM_SWICES_6 : 1;
		uint8_t NUM_SWICES_8 : 1;
		uint8_t NUM_SWICES_10 : 1;
		uint8_t NUM_SWICES_12 : 1;
	} bits;
	uint8_t waw;
};

union dsc_swice_caps2 {
	stwuct {
		uint8_t NUM_SWICES_16 : 1;
		uint8_t NUM_SWICES_20 : 1;
		uint8_t NUM_SWICES_24 : 1;
		uint8_t WESEWVED : 5;
	} bits;
	uint8_t waw;
};

union dsc_cowow_fowmats {
	stwuct {
		uint8_t WGB : 1;
		uint8_t YCBCW_444 : 1;
		uint8_t YCBCW_SIMPWE_422 : 1;
		uint8_t YCBCW_NATIVE_422 : 1;
		uint8_t YCBCW_NATIVE_420 : 1;
		uint8_t WESEWVED : 3;
	} bits;
	uint8_t waw;
};

union dsc_cowow_depth {
	stwuct {
		uint8_t WESEWVED1 : 1;
		uint8_t COWOW_DEPTH_8_BPC : 1;
		uint8_t COWOW_DEPTH_10_BPC : 1;
		uint8_t COWOW_DEPTH_12_BPC : 1;
		uint8_t WESEWVED2 : 3;
	} bits;
	uint8_t waw;
};

stwuct dsc_dec_dpcd_caps {
	boow is_dsc_suppowted;
	uint8_t dsc_vewsion;
	int32_t wc_buffew_size; /* DSC WC buffew bwock size in bytes */
	union dsc_swice_caps1 swice_caps1;
	union dsc_swice_caps2 swice_caps2;
	int32_t wb_bit_depth;
	boow is_bwock_pwed_suppowted;
	int32_t edp_max_bits_pew_pixew; /* Vawid onwy in eDP */
	union dsc_cowow_fowmats cowow_fowmats;
	union dsc_cowow_depth cowow_depth;
	int32_t thwoughput_mode_0_mps; /* In MPs */
	int32_t thwoughput_mode_1_mps; /* In MPs */
	int32_t max_swice_width;
	uint32_t bpp_incwement_div; /* bpp incwement divisow, e.g. if 16, it's 1/16th of a bit */

	/* Extended DSC caps */
	uint32_t bwanch_ovewaww_thwoughput_0_mps; /* In MPs */
	uint32_t bwanch_ovewaww_thwoughput_1_mps; /* In MPs */
	uint32_t bwanch_max_wine_width;
	boow is_dp; /* Decoded fowmat */
};

stwuct dc_gowden_tabwe {
	uint16_t dc_gowden_tabwe_vew;
	uint32_t aux_dphy_wx_contwow0_vaw;
	uint32_t aux_dphy_tx_contwow_vaw;
	uint32_t aux_dphy_wx_contwow1_vaw;
	uint32_t dc_gpio_aux_ctww_0_vaw;
	uint32_t dc_gpio_aux_ctww_1_vaw;
	uint32_t dc_gpio_aux_ctww_2_vaw;
	uint32_t dc_gpio_aux_ctww_3_vaw;
	uint32_t dc_gpio_aux_ctww_4_vaw;
	uint32_t dc_gpio_aux_ctww_5_vaw;
};

enum dc_gpu_mem_awwoc_type {
	DC_MEM_AWWOC_TYPE_GAWT,
	DC_MEM_AWWOC_TYPE_FWAME_BUFFEW,
	DC_MEM_AWWOC_TYPE_INVISIBWE_FWAME_BUFFEW,
	DC_MEM_AWWOC_TYPE_AGP
};

enum dc_wink_encoding_fowmat {
	DC_WINK_ENCODING_UNSPECIFIED = 0,
	DC_WINK_ENCODING_DP_8b_10b,
	DC_WINK_ENCODING_DP_128b_132b,
	DC_WINK_ENCODING_HDMI_TMDS,
	DC_WINK_ENCODING_HDMI_FWW
};

enum dc_psw_vewsion {
	DC_PSW_VEWSION_1			= 0,
	DC_PSW_VEWSION_SU_1			= 1,
	DC_PSW_VEWSION_UNSUPPOWTED		= 0xFFFFFFFF,
};

/* Possibwe vawues of dispway_endpoint_id.endpoint */
enum dispway_endpoint_type {
	DISPWAY_ENDPOINT_PHY = 0, /* Physicaw connectow. */
	DISPWAY_ENDPOINT_USB4_DPIA, /* USB4 DispwayPowt tunnew. */
	DISPWAY_ENDPOINT_UNKNOWN = -1
};

/* Extends gwaphics_object_id with an additionaw membew 'ep_type' fow
 * distinguishing between physicaw endpoints (with entwies in BIOS connectow tabwe) and
 * wogicaw endpoints.
 */
stwuct dispway_endpoint_id {
	stwuct gwaphics_object_id wink_id;
	enum dispway_endpoint_type ep_type;
};

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
stwuct otg_phy_mux {
	uint8_t phy_output_num;
	uint8_t otg_output_num;
};
#endif

enum dc_detect_weason {
	DETECT_WEASON_BOOT,
	DETECT_WEASON_WESUMEFWOMS3S4,
	DETECT_WEASON_HPD,
	DETECT_WEASON_HPDWX,
	DETECT_WEASON_FAWWBACK,
	DETECT_WEASON_WETWAIN,
	DETECT_WEASON_TDW,
};

stwuct dc_wink_status {
	boow wink_active;
	stwuct dpcd_caps *dpcd_caps;
};

union hdcp_wx_caps {
	stwuct {
		uint8_t vewsion;
		uint8_t wesewved;
		stwuct {
			uint8_t wepeatew	: 1;
			uint8_t hdcp_capabwe	: 1;
			uint8_t wesewved	: 6;
		} byte0;
	} fiewds;
	uint8_t waw[3];
};

union hdcp_bcaps {
	stwuct {
		uint8_t HDCP_CAPABWE:1;
		uint8_t WEPEATEW:1;
		uint8_t WESEWVED:6;
	} bits;
	uint8_t waw;
};

stwuct hdcp_caps {
	union hdcp_wx_caps wx_caps;
	union hdcp_bcaps bcaps;
};

/* DP MST stweam awwocation (paywoad bandwidth numbew) */
stwuct wink_mst_stweam_awwocation {
	/* DIG fwont */
	const stwuct stweam_encodew *stweam_enc;
	/* HPO DP Stweam Encodew */
	const stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_enc;
	/* associate DWM paywoad tabwe with DC stweam encodew */
	uint8_t vcp_id;
	/* numbew of swots wequiwed fow the DP stweam in twanspowt packet */
	uint8_t swot_count;
};

#define MAX_CONTWOWWEW_NUM 6

/* DP MST stweam awwocation tabwe */
stwuct wink_mst_stweam_awwocation_tabwe {
	/* numbew of DP video stweams */
	int stweam_count;
	/* awway of stweam awwocations */
	stwuct wink_mst_stweam_awwocation stweam_awwocations[MAX_CONTWOWWEW_NUM];
};

/* PSW featuwe fwags */
stwuct psw_settings {
	boow psw_featuwe_enabwed;		// PSW is suppowted by sink
	boow psw_awwow_active;			// PSW is cuwwentwy active
	enum dc_psw_vewsion psw_vewsion;		// Intewnaw PSW vewsion, detewmined based on DPCD
	boow psw_vtotaw_contwow_suppowt;	// Vtotaw contwow is suppowted by sink
	unsigned wong wong psw_diwty_wects_change_timestamp_ns;	// fow deway of enabwing PSW-SU

	/* These pawametews awe cawcuwated in Dwivew,
	 * based on dispway timing and Sink capabiwities.
	 * If VBWANK wegion is too smaww and Sink takes a wong time
	 * to set up WFB, it may take an extwa fwame to entew PSW state.
	 */
	boow psw_fwame_captuwe_indication_weq;
	unsigned int psw_sdp_twansmit_wine_num_deadwine;
	uint8_t fowce_ffu_mode;
	unsigned int psw_powew_opt;
};

enum wepway_coasting_vtotaw_type {
	PW_COASTING_TYPE_NOM = 0,
	PW_COASTING_TYPE_STATIC,
	PW_COASTING_TYPE_FUWW_SCWEEN_VIDEO,
	PW_COASTING_TYPE_TEST_HAWNESS,
	PW_COASTING_TYPE_NUM,
};

enum wepway_wink_off_fwame_count_wevew {
	PW_WINK_OFF_FWAME_COUNT_FAIW = 0x0,
	PW_WINK_OFF_FWAME_COUNT_GOOD = 0x2,
	PW_WINK_OFF_FWAME_COUNT_BEST = 0x6,
};

/*
 * This is genewaw Intewface fow Wepway to
 * set an 32 bit vawiabwe to dmub
 * The Message_type indicates which vawiabwe
 * passed to DMUB.
 */
enum wepway_FW_Message_type {
	Wepway_Msg_Not_Suppowt = -1,
	Wepway_Set_Timing_Sync_Suppowted,
	Wepway_Set_Wesidency_Fwameupdate_Timew,
	Wepway_Set_Pseudo_VTotaw,
};

union wepway_ewwow_status {
	stwuct {
		unsigned chaw STATE_TWANSITION_EWWOW    :1;
		unsigned chaw WINK_CWC_EWWOW            :1;
		unsigned chaw DESYNC_EWWOW              :1;
		unsigned chaw WESEWVED                  :5;
	} bits;
	unsigned chaw waw;
};

stwuct wepway_config {
	/* Wepway featuwe is suppowted */
	boow wepway_suppowted;
	/* Powew opt fwags that awe suppowted */
	unsigned int wepway_powew_opt_suppowted;
	/* SMU optimization is suppowted */
	boow wepway_smu_opt_suppowted;
	/* Wepway enabwement option */
	unsigned int wepway_enabwe_option;
	/* Wepway debug fwags */
	uint32_t debug_fwags;
	/* Wepway sync is suppowted */
	boow wepway_timing_sync_suppowted;
	/* Wepway Disabwe desync ewwow check. */
	boow fowce_disabwe_desync_ewwow_check;
	/* Wepway Weceived Desync Ewwow HPD. */
	boow weceived_desync_ewwow_hpd;
	/* Wepway featuwe is suppowted wong vbwank */
	boow wepway_suppowt_fast_wesync_in_uwtwa_sweep_mode;
	/* Wepway ewwow status */
	union wepway_ewwow_status wepway_ewwow_status;
};

/* Wepway featuwe fwags*/
stwuct wepway_settings {
	/* Wepway configuwation */
	stwuct wepway_config config;
	/* Wepway featuwe is weady fow activating */
	boow wepway_featuwe_enabwed;
	/* Wepway is cuwwentwy active */
	boow wepway_awwow_active;
	/* Wepway is cuwwentwy active */
	boow wepway_awwow_wong_vbwank;
	/* Powew opt fwags that awe activated cuwwentwy */
	unsigned int wepway_powew_opt_active;
	/* SMU optimization is enabwed */
	boow wepway_smu_opt_enabwe;
	/* Cuwwent Coasting vtotaw */
	uint16_t coasting_vtotaw;
	/* Coasting vtotaw tabwe */
	uint16_t coasting_vtotaw_tabwe[PW_COASTING_TYPE_NUM];
	/* Maximum wink off fwame count */
	enum wepway_wink_off_fwame_count_wevew wink_off_fwame_count_wevew;
	/* Wepway pseudo vtotaw fow abm + ips on fuww scween video which can impwove ips wesidency */
	uint16_t abm_with_ips_on_fuww_scween_video_pseudo_vtotaw;
	/* Wepway wast pseudo vtotaw set to DMUB */
	uint16_t wast_pseudo_vtotaw;
};

/* To spwit out "gwobaw" and "pew-panew" config settings.
 * Add a stwuct dc_panew_config undew dc_wink
 */
stwuct dc_panew_config {
	/* extwa panew powew sequence pawametews */
	stwuct pps {
		unsigned int extwa_t3_ms;
		unsigned int extwa_t7_ms;
		unsigned int extwa_deway_backwight_off;
		unsigned int extwa_post_t7_ms;
		unsigned int extwa_pwe_t11_ms;
		unsigned int extwa_t12_ms;
		unsigned int extwa_post_OUI_ms;
	} pps;
	/* nit bwightness */
	stwuct nits_bwightness {
		unsigned int peak; /* nits */
		unsigned int max_avg; /* nits */
		unsigned int min; /* 1/10000 nits */
		unsigned int max_nonboost_bwightness_miwwinits;
		unsigned int min_bwightness_miwwinits;
	} nits_bwightness;
	/* PSW */
	stwuct psw {
		boow disabwe_psw;
		boow disawwow_pswsu;
		boow disawwow_wepway;
		boow wc_disabwe;
		boow wc_awwow_static_scween;
		boow wc_awwow_fuwwscween_VPB;
		unsigned int wepway_enabwe_option;
	} psw;
	/* ABM */
	stwuct vawib {
		unsigned int vawibwight_featuwe_enabwe;
		unsigned int def_vawibwight_wevew;
		unsigned int abm_config_setting;
	} vawib;
	/* edp DSC */
	stwuct dsc {
		boow disabwe_dsc_edp;
		unsigned int fowce_dsc_edp_powicy;
	} dsc;
	/* eDP IWW */
	stwuct iww {
		boow optimize_edp_wink_wate; /* eDP IWW */
	} iww;
};

#define MAX_SINKS_PEW_WINK 4

/*
 *  USB4 DPIA BW AWWOCATION STWUCTS
 */
stwuct dc_dpia_bw_awwoc {
	int wemote_sink_weq_bw[MAX_SINKS_PEW_WINK]; // BW wequested by wemote sinks
	int wink_vewified_bw;  // The Vewified BW that wink can awwocated and use that has been vewified awweady
	int wink_max_bw;       // The Max BW that wink can wequiwe/suppowt
	int awwocated_bw;      // The Actuaw Awwocated BW fow this DPIA
	int estimated_bw;      // The estimated avaiwabwe BW fow this DPIA
	int bw_gwanuwawity;    // BW Gwanuwawity
	int dp_ovewhead;       // DP ovewhead in dp tunnewing
	boow bw_awwoc_enabwed; // The BW Awwoc Mode Suppowt is tuwned ON fow aww 3:  DP-Tx & Dpia & CM
	boow wesponse_weady;   // Wesponse weady fwom the CM side
	uint8_t nwd_max_wane_count; // Non-weduced max wane count
	uint8_t nwd_max_wink_wate; // Non-weduced max wink wate
};

enum dc_hpd_enabwe_sewect {
	HPD_EN_FOW_AWW_EDP = 0,
	HPD_EN_FOW_PWIMAWY_EDP_ONWY,
	HPD_EN_FOW_SECONDAWY_EDP_ONWY,
};

enum maww_stweam_type {
	SUBVP_NONE, // subvp not in use
	SUBVP_MAIN, // subvp in use, this stweam is main stweam
	SUBVP_PHANTOM, // subvp in use, this stweam is a phantom stweam
};
#endif /* DC_TYPES_H_ */
