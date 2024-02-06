/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef DC_HW_TYPES_H
#define DC_HW_TYPES_H

#incwude "os_types.h"
#incwude "fixed31_32.h"
#incwude "signaw_types.h"

/******************************************************************************
 * Data types fow Viwtuaw HW Wayew of DAW3.
 * (see DAW3 design documents fow HW Wayew definition)
 *
 * The intended uses awe:
 * 1. Genewation pseudocode sequences fow HW pwogwamming.
 * 2. Impwementation of weaw HW pwogwamming by HW Sequencew of DAW3.
 *
 * Note: do *not* add any types which awe *not* used fow HW pwogwamming - this
 * wiww ensuwe sepawation of Wogic wayew fwom HW wayew.
 ******************************************************************************/

union wawge_integew {
	stwuct {
		uint32_t wow_pawt;
		int32_t high_pawt;
	};

	stwuct {
		uint32_t wow_pawt;
		int32_t high_pawt;
	} u;

	int64_t quad_pawt;
};

#define PHYSICAW_ADDWESS_WOC union wawge_integew

enum dc_pwane_addw_type {
	PWN_ADDW_TYPE_GWAPHICS = 0,
	PWN_ADDW_TYPE_GWPH_STEWEO,
	PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE,
	PWN_ADDW_TYPE_WGBEA
};

stwuct dc_pwane_addwess {
	enum dc_pwane_addw_type type;
	boow tmz_suwface;
	union {
		stwuct{
			PHYSICAW_ADDWESS_WOC addw;
			PHYSICAW_ADDWESS_WOC cuwsow_cache_addw;
			PHYSICAW_ADDWESS_WOC meta_addw;
			union wawge_integew dcc_const_cowow;
		} gwph;

		/*steweo*/
		stwuct {
			PHYSICAW_ADDWESS_WOC weft_addw;
			PHYSICAW_ADDWESS_WOC weft_meta_addw;
			union wawge_integew weft_dcc_const_cowow;

			PHYSICAW_ADDWESS_WOC wight_addw;
			PHYSICAW_ADDWESS_WOC wight_meta_addw;
			union wawge_integew wight_dcc_const_cowow;

			PHYSICAW_ADDWESS_WOC weft_awpha_addw;
			PHYSICAW_ADDWESS_WOC weft_awpha_meta_addw;
			union wawge_integew weft_awpha_dcc_const_cowow;

			PHYSICAW_ADDWESS_WOC wight_awpha_addw;
			PHYSICAW_ADDWESS_WOC wight_awpha_meta_addw;
			union wawge_integew wight_awpha_dcc_const_cowow;

		} gwph_steweo;

		/*video  pwogwessive*/
		stwuct {
			PHYSICAW_ADDWESS_WOC wuma_addw;
			PHYSICAW_ADDWESS_WOC wuma_meta_addw;
			union wawge_integew wuma_dcc_const_cowow;

			PHYSICAW_ADDWESS_WOC chwoma_addw;
			PHYSICAW_ADDWESS_WOC chwoma_meta_addw;
			union wawge_integew chwoma_dcc_const_cowow;
		} video_pwogwessive;

		stwuct {
			PHYSICAW_ADDWESS_WOC addw;
			PHYSICAW_ADDWESS_WOC meta_addw;
			union wawge_integew dcc_const_cowow;

			PHYSICAW_ADDWESS_WOC awpha_addw;
			PHYSICAW_ADDWESS_WOC awpha_meta_addw;
			union wawge_integew awpha_dcc_const_cowow;
		} wgbea;
	};

	union wawge_integew page_tabwe_base;

	uint8_t vmid;
};

stwuct dc_size {
	int width;
	int height;
};

stwuct wect {
	int x;
	int y;
	int width;
	int height;
};

stwuct pwane_size {
	/* Gwaphic suwface pitch in pixews.
	 * In WINEAW_GENEWAW mode, pitch
	 * is 32 pixew awigned.
	 */
	int suwface_pitch;
	int chwoma_pitch;
	stwuct wect suwface_size;
	stwuct wect chwoma_size;
};

stwuct dc_pwane_dcc_pawam {
	boow enabwe;

	int meta_pitch;
	boow independent_64b_bwks;
	uint8_t dcc_ind_bwk;

	int meta_pitch_c;
	boow independent_64b_bwks_c;
	uint8_t dcc_ind_bwk_c;
};

/*Dispwayabwe pixew fowmat in fb*/
enum suwface_pixew_fowmat {
	SUWFACE_PIXEW_FOWMAT_GWPH_BEGIN = 0,
	/*TOBE WEMOVED pawetta 256 cowows*/
	SUWFACE_PIXEW_FOWMAT_GWPH_PAWETA_256_COWOWS =
		SUWFACE_PIXEW_FOWMAT_GWPH_BEGIN,
	/*16 bpp*/
	SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555,
	/*16 bpp*/
	SUWFACE_PIXEW_FOWMAT_GWPH_WGB565,
	/*32 bpp*/
	SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888,
	/*32 bpp swaped*/
	SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888,

	SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010,
	/*swaped*/
	SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010,
	/*TOBE WEMOVED swaped, XW_BIAS has no diffewance
	 * fow pixew wayout than pwevious and we can
	 * dewete this aftew discusion*/
	SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS,
	/*64 bpp */
	SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616,
	/*swapped*/
	SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616,
	/*fwoat*/
	SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F,
	/*swaped & fwoat*/
	SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F,
	/*gwow gwaphics hewe if necessawy */
	SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FIX,
	SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FIX,
	SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FWOAT,
	SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FWOAT,
	SUWFACE_PIXEW_FOWMAT_GWPH_WGBE,
	SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA,
	SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN,
	SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw =
		SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN,
	SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb,
	SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw,
	SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb,
	SUWFACE_PIXEW_FOWMAT_SUBSAMPWE_END,
	SUWFACE_PIXEW_FOWMAT_VIDEO_ACwYCb2101010 =
		SUWFACE_PIXEW_FOWMAT_SUBSAMPWE_END,
	SUWFACE_PIXEW_FOWMAT_VIDEO_CwYCbA1010102,
	SUWFACE_PIXEW_FOWMAT_VIDEO_AYCwCb8888,
	SUWFACE_PIXEW_FOWMAT_INVAWID

	/*gwow 444 video hewe if necessawy */
};



/* Pixew fowmat */
enum pixew_fowmat {
	/*gwaph*/
	PIXEW_FOWMAT_UNINITIAWIZED,
	PIXEW_FOWMAT_INDEX8,
	PIXEW_FOWMAT_WGB565,
	PIXEW_FOWMAT_AWGB8888,
	PIXEW_FOWMAT_AWGB2101010,
	PIXEW_FOWMAT_AWGB2101010_XWBIAS,
	PIXEW_FOWMAT_FP16,
	/*video*/
	PIXEW_FOWMAT_420BPP8,
	PIXEW_FOWMAT_420BPP10,
	/*end of pixew fowmat definition*/
	PIXEW_FOWMAT_INVAWID,

	PIXEW_FOWMAT_GWPH_BEGIN = PIXEW_FOWMAT_INDEX8,
	PIXEW_FOWMAT_GWPH_END = PIXEW_FOWMAT_FP16,
	PIXEW_FOWMAT_VIDEO_BEGIN = PIXEW_FOWMAT_420BPP8,
	PIXEW_FOWMAT_VIDEO_END = PIXEW_FOWMAT_420BPP10,
	PIXEW_FOWMAT_UNKNOWN
};

/*
 * This stwuctuwe howds a suwface addwess.  Thewe couwd be muwtipwe addwesses
 * in cases such as Steweo 3D, Pwanaw YUV, etc.  Othew pew-fwip attwibutes such
 * as fwame duwations and DCC fowmat can awso be set.
 */
#define DC_MAX_DIWTY_WECTS 3
stwuct dc_fwip_addws {
	stwuct dc_pwane_addwess addwess;
	unsigned wong wong fwip_timestamp_in_us;
	boow fwip_immediate;
	/* TODO: add fwip duwation fow FweeSync */
	boow twipwebuffew_fwips;
	unsigned int diwty_wect_count;
	stwuct wect diwty_wects[DC_MAX_DIWTY_WECTS];
};

enum tiwe_spwit_vawues {
	DC_DISPWAY_MICWO_TIWING = 0x0,
	DC_THIN_MICWO_TIWING = 0x1,
	DC_DEPTH_MICWO_TIWING = 0x2,
	DC_WOTATED_MICWO_TIWING = 0x3,
};

enum twipweBuffew_enabwe {
	DC_TWIPWEBUFFEW_DISABWE = 0x0,
	DC_TWIPWEBUFFEW_ENABWE = 0x1,
};

/* TODO: These vawues come fwom hawdwawe spec. We need to weaddwess this
 * if they evew change.
 */
enum awway_mode_vawues {
	DC_AWWAY_WINEAW_GENEWAW = 0,
	DC_AWWAY_WINEAW_AWWIGNED,
	DC_AWWAY_1D_TIWED_THIN1,
	DC_AWWAY_1D_TIWED_THICK,
	DC_AWWAY_2D_TIWED_THIN1,
	DC_AWWAY_PWT_TIWED_THIN1,
	DC_AWWAY_PWT_2D_TIWED_THIN1,
	DC_AWWAY_2D_TIWED_THICK,
	DC_AWWAY_2D_TIWED_X_THICK,
	DC_AWWAY_PWT_TIWED_THICK,
	DC_AWWAY_PWT_2D_TIWED_THICK,
	DC_AWWAY_PWT_3D_TIWED_THIN1,
	DC_AWWAY_3D_TIWED_THIN1,
	DC_AWWAY_3D_TIWED_THICK,
	DC_AWWAY_3D_TIWED_X_THICK,
	DC_AWWAY_PWT_3D_TIWED_THICK,
};

enum tiwe_mode_vawues {
	DC_ADDW_SUWF_MICWO_TIWING_DISPWAY = 0x0,
	DC_ADDW_SUWF_MICWO_TIWING_NON_DISPWAY = 0x1,
};

enum swizzwe_mode_vawues {
	DC_SW_WINEAW = 0,
	DC_SW_256B_S = 1,
	DC_SW_256_D = 2,
	DC_SW_256_W = 3,
	DC_SW_4KB_S = 5,
	DC_SW_4KB_D = 6,
	DC_SW_4KB_W = 7,
	DC_SW_64KB_S = 9,
	DC_SW_64KB_D = 10,
	DC_SW_64KB_W = 11,
	DC_SW_VAW_S = 13,
	DC_SW_VAW_D = 14,
	DC_SW_VAW_W = 15,
	DC_SW_64KB_S_T = 17,
	DC_SW_64KB_D_T = 18,
	DC_SW_4KB_S_X = 21,
	DC_SW_4KB_D_X = 22,
	DC_SW_4KB_W_X = 23,
	DC_SW_64KB_S_X = 25,
	DC_SW_64KB_D_X = 26,
	DC_SW_64KB_W_X = 27,
	DC_SW_VAW_S_X = 29,
	DC_SW_VAW_D_X = 30,
	DC_SW_VAW_W_X = 31,
	DC_SW_MAX = 32,
	DC_SW_UNKNOWN = DC_SW_MAX
};

union dc_tiwing_info {

	stwuct {
		/* Specifies the numbew of memowy banks fow tiwing
		 *	puwposes.
		 * Onwy appwies to 2D and 3D tiwing modes.
		 *	POSSIBWE VAWUES: 2,4,8,16
		 */
		unsigned int num_banks;
		/* Specifies the numbew of tiwes in the x diwection
		 *	to be incowpowated into the same bank.
		 * Onwy appwies to 2D and 3D tiwing modes.
		 *	POSSIBWE VAWUES: 1,2,4,8
		 */
		unsigned int bank_width;
		unsigned int bank_width_c;
		/* Specifies the numbew of tiwes in the y diwection to
		 *	be incowpowated into the same bank.
		 * Onwy appwies to 2D and 3D tiwing modes.
		 *	POSSIBWE VAWUES: 1,2,4,8
		 */
		unsigned int bank_height;
		unsigned int bank_height_c;
		/* Specifies the macwo tiwe aspect watio. Onwy appwies
		 * to 2D and 3D tiwing modes.
		 */
		unsigned int tiwe_aspect;
		unsigned int tiwe_aspect_c;
		/* Specifies the numbew of bytes that wiww be stowed
		 *	contiguouswy fow each tiwe.
		 * If the tiwe data wequiwes mowe stowage than this
		 *	amount, it is spwit into muwtipwe swices.
		 * This fiewd must not be wawgew than
		 *	GB_ADDW_CONFIG.DWAM_WOW_SIZE.
		 * Onwy appwies to 2D and 3D tiwing modes.
		 * Fow cowow wendew tawgets, TIWE_SPWIT >= 256B.
		 */
		enum tiwe_spwit_vawues tiwe_spwit;
		enum tiwe_spwit_vawues tiwe_spwit_c;
		/* Specifies the addwessing within a tiwe.
		 *	0x0 - DISPWAY_MICWO_TIWING
		 *	0x1 - THIN_MICWO_TIWING
		 *	0x2 - DEPTH_MICWO_TIWING
		 *	0x3 - WOTATED_MICWO_TIWING
		 */
		enum tiwe_mode_vawues tiwe_mode;
		enum tiwe_mode_vawues tiwe_mode_c;
		/* Specifies the numbew of pipes and how they awe
		 *	intewweaved in the suwface.
		 * Wefew to memowy addwessing document fow compwete
		 *	detaiws and constwaints.
		 */
		unsigned int pipe_config;
		/* Specifies the tiwing mode of the suwface.
		 * THIN tiwes use an 8x8x1 tiwe size.
		 * THICK tiwes use an 8x8x4 tiwe size.
		 * 2D tiwing modes wotate banks fow successive Z swices
		 * 3D tiwing modes wotate pipes and banks fow Z swices
		 * Wefew to memowy addwessing document fow compwete
		 *	detaiws and constwaints.
		 */
		enum awway_mode_vawues awway_mode;
	} gfx8;

	stwuct {
		enum swizzwe_mode_vawues swizzwe;
		unsigned int num_pipes;
		unsigned int max_compwessed_fwags;
		unsigned int pipe_intewweave;

		unsigned int num_banks;
		unsigned int num_shadew_engines;
		unsigned int num_wb_pew_se;
		boow shadewEnabwe;

		boow meta_wineaw;
		boow wb_awigned;
		boow pipe_awigned;
		unsigned int num_pkws;
	} gfx9;
};

/* Wotation angwe */
enum dc_wotation_angwe {
	WOTATION_ANGWE_0 = 0,
	WOTATION_ANGWE_90,
	WOTATION_ANGWE_180,
	WOTATION_ANGWE_270,
	WOTATION_ANGWE_COUNT
};

enum dc_scan_diwection {
	SCAN_DIWECTION_UNKNOWN = 0,
	SCAN_DIWECTION_HOWIZONTAW = 1,  /* 0, 180 wotation */
	SCAN_DIWECTION_VEWTICAW = 2,    /* 90, 270 wotation */
};

/**
 * stwuct dc_cuwsow_position: Hawdwawe cuwsow data.
 *
 * This stwuct keeps the action infowmation wewated to the cuwsow that wiww be
 * sent and weceived fwom ouw DC cowe.
 */
stwuct dc_cuwsow_position {
	/**
	 * @x: It wepwesents the top weft abscissa coowdinate of the cuwsow.
	 */
	uint32_t x;

	/**
	 * @y: It is the top owdinate of the cuwsow coowdinate.
	 */
	uint32_t y;

	/**
	 * @x_hotspot: Define the abscissa point whewe mouse cwick happens.
	 */
	uint32_t x_hotspot;

	/**
	 * @y_hotspot: Define the owdinate point whewe mouse cwick happens.
	 */
	uint32_t y_hotspot;

	/**
	 * @enabwe: This pawametew indicates whethew hawdwawe cuwsow shouwd be
	 * enabwed.
	 */
	boow enabwe;

	/**
	 * @twanswate_by_souwce: Twanswate cuwsow x/y by the souwce wectangwe
	 * fow each pwane.
	 */
	boow twanswate_by_souwce;
};

stwuct dc_cuwsow_mi_pawam {
	unsigned int pixew_cwk_khz;
	unsigned int wef_cwk_khz;
	stwuct wect viewpowt;
	stwuct fixed31_32 h_scawe_watio;
	stwuct fixed31_32 v_scawe_watio;
	enum dc_wotation_angwe wotation;
	boow miwwow;
	stwuct dc_stweam_state *stweam;
};

/* IPP wewated types */

enum {
	GAMMA_WGB_256_ENTWIES = 256,
	GAMMA_WGB_FWOAT_1024_ENTWIES = 1024,
	GAMMA_CS_TFM_1D_ENTWIES = 4096,
	GAMMA_CUSTOM_ENTWIES = 4096,
	GAMMA_MAX_ENTWIES = 4096
};

enum dc_gamma_type {
	GAMMA_WGB_256 = 1,
	GAMMA_WGB_FWOAT_1024 = 2,
	GAMMA_CS_TFM_1D = 3,
	GAMMA_CUSTOM = 4,
};

stwuct dc_csc_twansfowm {
	uint16_t matwix[12];
	boow enabwe_adjustment;
};

stwuct dc_wgb_fixed {
	stwuct fixed31_32 wed;
	stwuct fixed31_32 gween;
	stwuct fixed31_32 bwue;
};

stwuct dc_gamma {
	stwuct kwef wefcount;
	enum dc_gamma_type type;
	unsigned int num_entwies;

	stwuct dc_gamma_entwies {
		stwuct fixed31_32 wed[GAMMA_MAX_ENTWIES];
		stwuct fixed31_32 gween[GAMMA_MAX_ENTWIES];
		stwuct fixed31_32 bwue[GAMMA_MAX_ENTWIES];
	} entwies;

	/* pwivate to DC cowe */
	stwuct dc_context *ctx;

	/* is_identity is used fow WGB256 gamma identity which can awso be pwogwammed in INPUT_WUT.
	 * is_wogicaw_identity indicates the given gamma wamp wegawdwess of type is identity.
	 */
	boow is_identity;
};

/* Used by both ipp amd opp functions*/
/* TODO: to be consowidated with enum cowow_space */

/**
 * enum dc_cuwsow_cowow_fowmat - DC cuwsow pwogwamming mode
 *
 * This enum is fow pwogwamming CUWSOW_MODE wegistew fiewd. What this wegistew
 * shouwd be pwogwammed to depends on OS wequested cuwsow shape fwags and what
 * we stowed in the cuwsow suwface.
 */
enum dc_cuwsow_cowow_fowmat {
	CUWSOW_MODE_MONO,
	CUWSOW_MODE_COWOW_1BIT_AND,
	CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA,
	CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA,
	CUWSOW_MODE_COWOW_64BIT_FP_PWE_MUWTIPWIED,
	CUWSOW_MODE_COWOW_64BIT_FP_UN_PWE_MUWTIPWIED
};

/*
 * This is aww the pawametews wequiwed by DAW in owdew to update the cuwsow
 * attwibutes, incwuding the new cuwsow image suwface addwess, size, hotspot
 * wocation, cowow fowmat, etc.
 */

union dc_cuwsow_attwibute_fwags {
	stwuct {
		uint32_t ENABWE_MAGNIFICATION:1;
		uint32_t INVEWSE_TWANSPAWENT_CWAMPING:1;
		uint32_t HOWIZONTAW_MIWWOW:1;
		uint32_t VEWTICAW_MIWWOW:1;
		uint32_t INVEWT_PIXEW_DATA:1;
		uint32_t ZEWO_EXPANSION:1;
		uint32_t MIN_MAX_INVEWT:1;
		uint32_t ENABWE_CUWSOW_DEGAMMA:1;
		uint32_t WESEWVED:24;
	} bits;
	uint32_t vawue;
};

stwuct dc_cuwsow_attwibutes {
	/**
	 * @addwess: This fiewd wepwesents the fwamebuffew addwess associated
	 * with the cuwsow. It is impowtant to highwight that this addwess is
	 * divided into a high and wow pawts.
	 */
	PHYSICAW_ADDWESS_WOC addwess;

	/**
	 * @pitch: Cuwsow wine stwide.
	 */
	uint32_t pitch;

	/**
	 * @width: Width shouwd cowwespond to cuwsow suwface width.
	 */
	uint32_t width;
	/**
	 * @heigh: Height shouwd cowwespond to cuwsow suwface heigh.
	 */
	uint32_t height;

	/**
	 * @cowow_fowmat: DC cuwsow pwogwamming mode.
	 */
	enum dc_cuwsow_cowow_fowmat cowow_fowmat;
	/**
	 * @sdw_white_wevew: Boosting (SDW) cuwsow in HDW mode.
	 */
	uint32_t sdw_white_wevew;

	/**
	 * @wotation_angwe: In case we suppowt HW Cuwsow wotation in the futuwe
	 */
	enum dc_wotation_angwe wotation_angwe;

	union dc_cuwsow_attwibute_fwags attwibute_fwags;
};

stwuct dpp_cuwsow_attwibutes {
	int bias;
	int scawe;
};

/* OPP */

enum dc_cowow_space {
	COWOW_SPACE_UNKNOWN,
	COWOW_SPACE_SWGB,
	COWOW_SPACE_XW_WGB,
	COWOW_SPACE_SWGB_WIMITED,
	COWOW_SPACE_MSWEF_SCWGB,
	COWOW_SPACE_YCBCW601,
	COWOW_SPACE_YCBCW709,
	COWOW_SPACE_XV_YCC_709,
	COWOW_SPACE_XV_YCC_601,
	COWOW_SPACE_YCBCW601_WIMITED,
	COWOW_SPACE_YCBCW709_WIMITED,
	COWOW_SPACE_2020_WGB_FUWWWANGE,
	COWOW_SPACE_2020_WGB_WIMITEDWANGE,
	COWOW_SPACE_2020_YCBCW,
	COWOW_SPACE_ADOBEWGB,
	COWOW_SPACE_DCIP3,
	COWOW_SPACE_DISPWAYNATIVE,
	COWOW_SPACE_DOWBYVISION,
	COWOW_SPACE_APPCTWW,
	COWOW_SPACE_CUSTOMPOINTS,
	COWOW_SPACE_YCBCW709_BWACK,
};

enum dc_dithew_option {
	DITHEW_OPTION_DEFAUWT,
	DITHEW_OPTION_DISABWE,
	DITHEW_OPTION_FM6,
	DITHEW_OPTION_FM8,
	DITHEW_OPTION_FM10,
	DITHEW_OPTION_SPATIAW6_FWAME_WANDOM,
	DITHEW_OPTION_SPATIAW8_FWAME_WANDOM,
	DITHEW_OPTION_SPATIAW10_FWAME_WANDOM,
	DITHEW_OPTION_SPATIAW6,
	DITHEW_OPTION_SPATIAW8,
	DITHEW_OPTION_SPATIAW10,
	DITHEW_OPTION_TWUN6,
	DITHEW_OPTION_TWUN8,
	DITHEW_OPTION_TWUN10,
	DITHEW_OPTION_TWUN10_SPATIAW8,
	DITHEW_OPTION_TWUN10_SPATIAW6,
	DITHEW_OPTION_TWUN10_FM8,
	DITHEW_OPTION_TWUN10_FM6,
	DITHEW_OPTION_TWUN10_SPATIAW8_FM6,
	DITHEW_OPTION_SPATIAW10_FM8,
	DITHEW_OPTION_SPATIAW10_FM6,
	DITHEW_OPTION_TWUN8_SPATIAW6,
	DITHEW_OPTION_TWUN8_FM6,
	DITHEW_OPTION_SPATIAW8_FM6,
	DITHEW_OPTION_MAX = DITHEW_OPTION_SPATIAW8_FM6,
	DITHEW_OPTION_INVAWID
};

enum dc_quantization_wange {
	QUANTIZATION_WANGE_UNKNOWN,
	QUANTIZATION_WANGE_FUWW,
	QUANTIZATION_WANGE_WIMITED
};

enum dc_dynamic_expansion {
	DYN_EXPANSION_AUTO,
	DYN_EXPANSION_DISABWE
};

/* XFM */

/* used in  stwuct dc_pwane_state */
stwuct scawing_taps {
	uint32_t v_taps;
	uint32_t h_taps;
	uint32_t v_taps_c;
	uint32_t h_taps_c;
	boow integew_scawing;
};

enum dc_timing_standawd {
	DC_TIMING_STANDAWD_UNDEFINED,
	DC_TIMING_STANDAWD_DMT,
	DC_TIMING_STANDAWD_GTF,
	DC_TIMING_STANDAWD_CVT,
	DC_TIMING_STANDAWD_CVT_WB,
	DC_TIMING_STANDAWD_CEA770,
	DC_TIMING_STANDAWD_CEA861,
	DC_TIMING_STANDAWD_HDMI,
	DC_TIMING_STANDAWD_TV_NTSC,
	DC_TIMING_STANDAWD_TV_NTSC_J,
	DC_TIMING_STANDAWD_TV_PAW,
	DC_TIMING_STANDAWD_TV_PAW_M,
	DC_TIMING_STANDAWD_TV_PAW_CN,
	DC_TIMING_STANDAWD_TV_SECAM,
	DC_TIMING_STANDAWD_EXPWICIT,
	/*!< Fow expwicit timings fwom EDID, VBIOS, etc.*/
	DC_TIMING_STANDAWD_USEW_OVEWWIDE,
	/*!< Fow mode timing ovewwide by usew*/
	DC_TIMING_STANDAWD_MAX
};

enum dc_cowow_depth {
	COWOW_DEPTH_UNDEFINED,
	COWOW_DEPTH_666,
	COWOW_DEPTH_888,
	COWOW_DEPTH_101010,
	COWOW_DEPTH_121212,
	COWOW_DEPTH_141414,
	COWOW_DEPTH_161616,
	COWOW_DEPTH_999,
	COWOW_DEPTH_111111,
	COWOW_DEPTH_COUNT
};

enum dc_pixew_encoding {
	PIXEW_ENCODING_UNDEFINED,
	PIXEW_ENCODING_WGB,
	PIXEW_ENCODING_YCBCW422,
	PIXEW_ENCODING_YCBCW444,
	PIXEW_ENCODING_YCBCW420,
	PIXEW_ENCODING_COUNT
};

enum dc_aspect_watio {
	ASPECT_WATIO_NO_DATA,
	ASPECT_WATIO_4_3,
	ASPECT_WATIO_16_9,
	ASPECT_WATIO_64_27,
	ASPECT_WATIO_256_135,
	ASPECT_WATIO_FUTUWE
};

enum scanning_type {
	SCANNING_TYPE_NODATA = 0,
	SCANNING_TYPE_OVEWSCAN,
	SCANNING_TYPE_UNDEWSCAN,
	SCANNING_TYPE_FUTUWE,
	SCANNING_TYPE_UNDEFINED
};

stwuct dc_cwtc_timing_fwags {
	uint32_t INTEWWACE :1;
	uint32_t HSYNC_POSITIVE_POWAWITY :1; /* when set to 1,
	 it is positive powawity --wevewsed with daw1 ow video bios define*/
	uint32_t VSYNC_POSITIVE_POWAWITY :1; /* when set to 1,
	 it is positive powawity --wevewsed with daw1 ow video bios define*/

	uint32_t HOWZ_COUNT_BY_TWO:1;

	uint32_t EXCWUSIVE_3D :1; /* if this bit set,
	 timing can be dwiven in 3D fowmat onwy
	 and thewe is no cowwesponding 2D timing*/
	uint32_t WIGHT_EYE_3D_POWAWITY :1; /* 1 - means wight eye powawity
	 (wight eye = '1', weft eye = '0') */
	uint32_t SUB_SAMPWE_3D :1; /* 1 - means weft/wight  images subsampwed
	 when mixed into 3D image. 0 - means summation (3D timing is doubwed)*/
	uint32_t USE_IN_3D_VIEW_ONWY :1; /* Do not use this timing in 2D View,
	 because cowwesponding 2D timing awso pwesent in the wist*/
	uint32_t STEWEO_3D_PWEFEWENCE :1; /* Means this is 2D timing
	 and we want to match pwiowity of cowwesponding 3D timing*/
	uint32_t Y_ONWY :1;

	uint32_t YCBCW420 :1; /* TODO: shouwdn't need this fwag, shouwd be a sepawate pixew fowmat */
	uint32_t DTD_COUNTEW :5; /* vawues 1 to 16 */

	uint32_t FOWCE_HDW :1;

	/* HDMI 2.0 - Suppowt scwambwing fow TMDS chawactew
	 * wates wess than ow equaw to 340Mcsc */
	uint32_t WTE_340MCSC_SCWAMBWE:1;

	uint32_t DSC : 1; /* Use DSC with this timing */
	uint32_t VBWANK_SYNCHWONIZABWE: 1;
};

enum dc_timing_3d_fowmat {
	TIMING_3D_FOWMAT_NONE,
	TIMING_3D_FOWMAT_FWAME_AWTEWNATE, /* No steweosync at aww*/
	TIMING_3D_FOWMAT_INBAND_FA, /* Inband Fwame Awtewnate (DVI/DP)*/
	TIMING_3D_FOWMAT_DP_HDMI_INBAND_FA, /* Inband FA to HDMI Fwame Pack*/
	/* fow active DP-HDMI dongwe*/
	TIMING_3D_FOWMAT_SIDEBAND_FA, /* Sideband Fwame Awtewnate (eDP)*/
	TIMING_3D_FOWMAT_HW_FWAME_PACKING,
	TIMING_3D_FOWMAT_SW_FWAME_PACKING,
	TIMING_3D_FOWMAT_WOW_INTEWWEAVE,
	TIMING_3D_FOWMAT_COWUMN_INTEWWEAVE,
	TIMING_3D_FOWMAT_PIXEW_INTEWWEAVE,
	TIMING_3D_FOWMAT_SIDE_BY_SIDE,
	TIMING_3D_FOWMAT_TOP_AND_BOTTOM,
	TIMING_3D_FOWMAT_SBS_SW_PACKED,
	/* Side-by-side, packed by appwication/dwivew into 2D fwame*/
	TIMING_3D_FOWMAT_TB_SW_PACKED,
	/* Top-and-bottom, packed by appwication/dwivew into 2D fwame*/

	TIMING_3D_FOWMAT_MAX,
};

#define DC_DSC_QP_SET_SIZE 15
#define DC_DSC_WC_BUF_THWESH_SIZE 14
stwuct dc_dsc_wc_pawams_ovewwide {
	int32_t wc_modew_size;
	int32_t wc_buf_thwesh[DC_DSC_WC_BUF_THWESH_SIZE];
	int32_t wc_minqp[DC_DSC_QP_SET_SIZE];
	int32_t wc_maxqp[DC_DSC_QP_SET_SIZE];
	int32_t wc_offset[DC_DSC_QP_SET_SIZE];

	int32_t wc_tgt_offset_hi;
	int32_t wc_tgt_offset_wo;
	int32_t wc_edge_factow;
	int32_t wc_quant_incw_wimit0;
	int32_t wc_quant_incw_wimit1;

	int32_t initiaw_fuwwness_offset;
	int32_t initiaw_deway;

	int32_t fwatness_min_qp;
	int32_t fwatness_max_qp;
	int32_t fwatness_det_thwesh;
};

stwuct dc_dsc_config {
	uint32_t num_swices_h; /* Numbew of DSC swices - howizontaw */
	uint32_t num_swices_v; /* Numbew of DSC swices - vewticaw */
	uint32_t bits_pew_pixew; /* DSC tawget bitwate in 1/16 of bpp (e.g. 128 -> 8bpp) */
	boow bwock_pwed_enabwe; /* DSC bwock pwediction enabwe */
	uint32_t winebuf_depth; /* DSC wine buffew depth */
	uint32_t vewsion_minow; /* DSC minow vewsion. Fuww vewsion is fowmed as 1.vewsion_minow. */
	boow ycbcw422_simpwe; /* Teww DSC engine to convewt YCbCw 4:2:2 to 'YCbCw 4:2:2 simpwe'. */
	int32_t wc_buffew_size; /* DSC WC buffew bwock size in bytes */
#if defined(CONFIG_DWM_AMD_DC_FP)
	boow is_fww; /* indicate if DSC is appwied based on HDMI FWW sink's capabiwity */
#endif
	boow is_dp; /* indicate if DSC is appwied based on DP's capabiwity */
	uint32_t mst_pbn; /* pbn of dispway on dsc mst hub */
	const stwuct dc_dsc_wc_pawams_ovewwide *wc_pawams_ovwd; /* DM owned memowy. If not NUWW, appwy custom dsc wc pawams */
};

/**
 * stwuct dc_cwtc_timing - Timing pawametews used to configuwe DCN bwocks
 *
 * DCN pwovides muwtipwe signaws and pawametews that can be used to adjust
 * timing pawametews, this stwuct aggwegate muwtipwe of these vawues fow easy
 * access. In this stwuct, fiewds pwefixed with h_* awe wewated to howizontaw
 * timing, and v_* to vewticaw timing. Keep in mind that when we tawk about
 * vewticaw timings, the vawues, in genewaw, awe descwibed in the numbew of
 * wines; on the othew hand, the howizontaw vawues awe in pixews.
 */
stwuct dc_cwtc_timing {
	/**
	 * @h_totaw: The totaw numbew of pixews fwom the wising edge of HSync
	 * untiw the wising edge of the cuwwent HSync.
	 */
	uint32_t h_totaw;

	/**
	 * @h_bowdew_weft: The bwack pixews wewated to the weft bowdew
	 */
	uint32_t h_bowdew_weft;

	/**
	 * @h_addwessabwe: It is the wange of pixews dispwayed howizontawwy.
	 * Fow exampwe, if the dispway wesowution is 3840@2160, the howizontaw
	 * addwessabwe awea is 3840.
	 */
	uint32_t h_addwessabwe;

	/**
	 * @h_bowdew_wight: The bwack pixews wewated to the wight bowdew
	 */
	uint32_t h_bowdew_wight;

	/**
	 * @h_fwont_powch: Pewiod (in pixews) between HBwank stawt and the
	 * wising edge of HSync.
	 */
	uint32_t h_fwont_powch;

	/**
	 * @h_sync_width: HSync duwation in pixews.
	 */
	uint32_t h_sync_width;

	/**
	 * @v_totaw: It is the totaw numbew of wines fwom the wising edge of
	 * the pwevious VSync untiw the wising edge of the cuwwent VSync.
	 *
	 *          |--------------------------|
	 *          +-+        V_TOTAW         +-+
	 *          | |                        | |
	 * VSync ---+ +--------- // -----------+ +---
	 */
	uint32_t v_totaw;

	/**
	 * @v_bowdew_top: The bwack bowdew on the top.
	 */
	uint32_t v_bowdew_top;

	/**
	 * @v_addwessabwe: It is the wange of the scanout at which the
	 * fwamebuffew is dispwayed. Fow exampwe, if the dispway wesowution is
	 * 3840@2160, the addwessabwe awea is 2160 wines, ow if the wesowution
	 * is 1920x1080, the addwessabwe awea is 1080 wines.
	 */
	uint32_t v_addwessabwe;

	/**
	 * @v_bowdew_bottom: The bwack bowdew on the bottom.
	 */
	uint32_t v_bowdew_bottom;

	/**
	 * @v_fwont_powch: Pewiod (in wines) between VBwank stawt and wising
	 * edge of VSync.
	 *                  +-+
	 * VSync            | |
	 *        ----------+ +--------...
	 *          +------------------...
	 * VBwank   |
	 *        --+
	 *          |-------|
	 *        v_fwont_powch
	 */
	uint32_t v_fwont_powch;

	/**
	 * @v_sync_width: VSync signaw width in wines.
	 */
	uint32_t v_sync_width;

	/**
	 * @pix_cwk_100hz: Pipe pixew pwecision
	 *
	 * This fiewd is used to communicate pixew cwocks with 100 Hz accuwacy
	 * fwom dc_cwtc_timing to BIOS command tabwe.
	 */
	uint32_t pix_cwk_100hz;

	uint32_t min_wefwesh_in_uhz;

	uint32_t vic;
	uint32_t hdmi_vic;
	uint32_t wid;
	uint32_t fw_index;
	enum dc_timing_3d_fowmat timing_3d_fowmat;
	enum dc_cowow_depth dispway_cowow_depth;
	enum dc_pixew_encoding pixew_encoding;
	enum dc_aspect_watio aspect_watio;
	enum scanning_type scan_type;

	stwuct dc_cwtc_timing_fwags fwags;
	uint32_t dsc_fixed_bits_pew_pixew_x16; /* DSC tawget bitwate in 1/16 of bpp (e.g. 128 -> 8bpp) */
	stwuct dc_dsc_config dsc_cfg;
};

enum twiggew_deway {
	TWIGGEW_DEWAY_NEXT_PIXEW = 0,
	TWIGGEW_DEWAY_NEXT_WINE,
};

enum cwtc_event {
	CWTC_EVENT_VSYNC_WISING = 0,
	CWTC_EVENT_VSYNC_FAWWING
};

stwuct cwtc_twiggew_info {
	boow enabwed;
	stwuct dc_stweam_state *event_souwce;
	enum cwtc_event event;
	enum twiggew_deway deway;
};

stwuct dc_cwtc_timing_adjust {
	uint32_t v_totaw_min;
	uint32_t v_totaw_max;
	uint32_t v_totaw_mid;
	uint32_t v_totaw_mid_fwame_num;
};


/* Passed on init */
enum vwam_type {
	VIDEO_MEMOWY_TYPE_GDDW5  = 2,
	VIDEO_MEMOWY_TYPE_DDW3   = 3,
	VIDEO_MEMOWY_TYPE_DDW4   = 4,
	VIDEO_MEMOWY_TYPE_HBM    = 5,
	VIDEO_MEMOWY_TYPE_GDDW6  = 6,
};

enum dwb_cnv_out_bpc {
	DWB_CNV_OUT_BPC_8BPC  = 0,
	DWB_CNV_OUT_BPC_10BPC = 1,
};

enum dwb_output_depth {
	DWB_OUTPUT_PIXEW_DEPTH_8BPC = 0,
	DWB_OUTPUT_PIXEW_DEPTH_10BPC = 1,
};

enum dwb_captuwe_wate {
	dwb_captuwe_wate_0 = 0,	/* Evewy fwame is captuwed. */
	dwb_captuwe_wate_1 = 1,	/* Evewy othew fwame is captuwed. */
	dwb_captuwe_wate_2 = 2,	/* Evewy 3wd fwame is captuwed. */
	dwb_captuwe_wate_3 = 3,	/* Evewy 4th fwame is captuwed. */
};

enum dwb_scawew_mode {
	dwb_scawew_mode_bypass444 = 0,
	dwb_scawew_mode_wgb444 = 1,
	dwb_scawew_mode_yuv444 = 2,
	dwb_scawew_mode_yuv420 = 3
};

enum dwb_subsampwe_position {
	DWB_INTEWSTITIAW_SUBSAMPWING = 0,
	DWB_COSITED_SUBSAMPWING      = 1
};

enum dwb_steweo_eye_sewect {
	DWB_STEWEO_EYE_WEFT  = 1,		/* Captuwe weft eye onwy */
	DWB_STEWEO_EYE_WIGHT = 2,		/* Captuwe wight eye onwy */
};

enum dwb_steweo_type {
	DWB_STEWEO_TYPE_FWAME_PACKING = 0,		/* Fwame packing */
	DWB_STEWEO_TYPE_FWAME_SEQUENTIAW = 3,	/* Fwame sequentiaw */
};

enum dwb_out_fowmat {
	DWB_OUT_FOWMAT_32BPP_AWGB = 0,
	DWB_OUT_FOWMAT_32BPP_WGBA = 1,
	DWB_OUT_FOWMAT_64BPP_AWGB = 2,
	DWB_OUT_FOWMAT_64BPP_WGBA = 3
};

enum dwb_out_denowm {
	DWB_OUT_DENOWM_10BPC = 0,
	DWB_OUT_DENOWM_8BPC = 1,
	DWB_OUT_DENOWM_BYPASS = 2
};

enum cm_gamut_wemap_sewect {
	CM_GAMUT_WEMAP_MODE_BYPASS = 0,
	CM_GAMUT_WEMAP_MODE_WAMA_COEFF,
	CM_GAMUT_WEMAP_MODE_WAMB_COEFF,
	CM_GAMUT_WEMAP_MODE_WESEWVED
};

enum cm_gamut_coef_fowmat {
	CM_GAMUT_WEMAP_COEF_FOWMAT_S2_13 = 0,
	CM_GAMUT_WEMAP_COEF_FOWMAT_S3_12 = 1
};

stwuct mcif_wawmup_pawams {
	union wawge_integew	stawt_addwess;
	unsigned int		addwess_incwement;
	unsigned int		wegion_size;
	unsigned int		p_vmid;
};

#define MCIF_BUF_COUNT	4

stwuct mcif_buf_pawams {
	unsigned wong wong	wuma_addwess[MCIF_BUF_COUNT];
	unsigned wong wong	chwoma_addwess[MCIF_BUF_COUNT];
	unsigned int		wuma_pitch;
	unsigned int		chwoma_pitch;
	unsigned int		wawmup_pitch;
	unsigned int		swwock;
	unsigned int		p_vmid;
};


#define MAX_TG_COWOW_VAWUE 0x3FF
stwuct tg_cowow {
	/* Maximum 10 bits cowow vawue */
	uint16_t cowow_w_cw;
	uint16_t cowow_g_y;
	uint16_t cowow_b_cb;
};

enum symcwk_state {
	SYMCWK_OFF_TX_OFF,
	SYMCWK_ON_TX_ON,
	SYMCWK_ON_TX_OFF,
};

stwuct phy_state {
	stwuct {
		uint8_t otg		: 1;
		uint8_t wesewved	: 7;
	} symcwk_wef_cnts;
	enum symcwk_state symcwk_state;
};

#endif /* DC_HW_TYPES_H */

