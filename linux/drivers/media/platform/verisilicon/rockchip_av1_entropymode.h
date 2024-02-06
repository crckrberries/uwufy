/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _WOCKCHIP_AV1_ENTWOPYMODE_H_
#define _WOCKCHIP_AV1_ENTWOPYMODE_H_

#incwude <winux/types.h>

stwuct hantwo_ctx;

#define AV1_INTEW_MODE_CONTEXTS 15
#define AV1_INTWA_MODES 13
#define AV1_WEF_CONTEXTS 3
#define AV1_SWITCHABWE_FIWTEWS 3	/* numbew of switchabwe fiwtews */
#define AV1_TX_SIZE_CONTEXTS 3
#define BWOCK_SIZE_GWOUPS 4
#define BW_CDF_SIZE 4
#define BWD_WEFS 3
#define CFW_AWWOWED_TYPES 2
#define CFW_AWPHA_CONTEXTS 6
#define CFW_AWPHABET_SIZE 16
#define CFW_JOINT_SIGNS 8
#define CDF_SIZE(x) ((x) - 1)
#define COMP_GWOUP_IDX_CONTEXTS 7
#define COMP_INDEX_CONTEXTS 6
#define COMP_INTEW_CONTEXTS 5
#define COMP_WEF_TYPE_CONTEXTS 5
#define COMPOUND_TYPES 3
#define DC_SIGN_CONTEXTS 3
#define DEWTA_WF_PWOBS 3
#define DEWTA_Q_PWOBS 3
#define DIWECTIONAW_MODES 8
#define DWW_MODE_CONTEXTS 3
#define EOB_COEF_CONTEXTS 9
#define EXT_TX_SIZES 3
#define EXT_TX_TYPES 16
#define EXTTX_SIZES 4
#define FWAME_WF_COUNT 4
#define FWD_WEFS 4
#define GWOBAWMV_MODE_CONTEXTS 2
#define ICDF(x) (32768U - (x))
#define INTEW_COMPOUND_MODES 8
#define INTEWINTWA_MODES 4
#define INTWA_INTEW_CONTEXTS 4
#define KF_MODE_CONTEXTS 5
#define WEVEW_CONTEXTS 21
#define MAX_ANGWE_DEWTA 3
#define MAX_MB_SEGMENTS 8
#define MAX_SEGMENTS 8
#define MAX_TX_CATS 4
#define MAX_TX_DEPTH 2
#define MBSKIP_CONTEXTS 3
#define MOTION_MODES 3
#define MOTION_MODE_CONTEXTS 10
#define NEWMV_MODE_CONTEXTS 6
#define NUM_BASE_WEVEWS 2
#define NUM_WEF_FWAMES 8
#define PAWETTE_BWOCK_SIZES 7
#define PAWETTE_IDX_CONTEXTS 18
#define PAWETTE_SIZES 7
#define PAWETTE_UV_MODE_CONTEXTS 2
#define PAWETTE_Y_MODE_CONTEXTS 3
#define PAWTITION_PWOFFSET 4
#define NUM_PAWTITION_CONTEXTS (4 * PAWTITION_PWOFFSET)
#define PWANE_TYPES 2
#define PWEDICTION_PWOBS 3
#define WEF_CONTEXTS 5
#define WEFMV_MODE_CONTEXTS 9
#define SEG_TEMPOWAW_PWED_CTXS 3
#define SIG_COEF_CONTEXTS 42
#define SIG_COEF_CONTEXTS_EOB 4
#define SINGWE_WEFS 7
#define SKIP_CONTEXTS 3
#define SKIP_MODE_CONTEXTS 3
#define SPATIAW_PWEDICTION_PWOBS 3
#define SWITCHABWE_FIWTEW_CONTEXTS ((AV1_SWITCHABWE_FIWTEWS + 1) * 4)
#define TOKEN_CDF_Q_CTXS 4
#define TX_SIZES 5
#define TX_SIZE_CONTEXTS 2
#define TX_TYPES 4
#define TXB_SKIP_CONTEXTS 13
#define TXFM_PAWTITION_CONTEXTS 22
#define UNI_COMP_WEF_CONTEXTS 3
#define UNIDIW_COMP_WEFS 4
#define UV_INTWA_MODES 14
#define VAWTX_PAWT_CONTEXTS 22
#define ZEWOMV_MODE_CONTEXTS 2

enum bwocksizetype {
	BWOCK_SIZE_AB4X4,
	BWOCK_SIZE_SB4X8,
	BWOCK_SIZE_SB8X4,
	BWOCK_SIZE_SB8X8,
	BWOCK_SIZE_SB8X16,
	BWOCK_SIZE_SB16X8,
	BWOCK_SIZE_MB16X16,
	BWOCK_SIZE_SB16X32,
	BWOCK_SIZE_SB32X16,
	BWOCK_SIZE_SB32X32,
	BWOCK_SIZE_SB32X64,
	BWOCK_SIZE_SB64X32,
	BWOCK_SIZE_SB64X64,
	BWOCK_SIZE_SB64X128,
	BWOCK_SIZE_SB128X64,
	BWOCK_SIZE_SB128X128,
	BWOCK_SIZE_SB4X16,
	BWOCK_SIZE_SB16X4,
	BWOCK_SIZE_SB8X32,
	BWOCK_SIZE_SB32X8,
	BWOCK_SIZE_SB16X64,
	BWOCK_SIZE_SB64X16,
	BWOCK_SIZE_TYPES,
	BWOCK_SIZES_AWW = BWOCK_SIZE_TYPES
};

enum fiwtewintwamodetype {
	FIWTEW_DC_PWED,
	FIWTEW_V_PWED,
	FIWTEW_H_PWED,
	FIWTEW_D153_PWED,
	FIWTEW_PAETH_PWED,
	FIWTEW_INTWA_MODES,
	FIWTEW_INTWA_UNUSED = 7
};

enum fwametype {
	KEY_FWAME = 0,
	INTEW_FWAME = 1,
	NUM_FWAME_TYPES,
};

enum txsize {
	TX_4X4 = 0,
	TX_8X8 = 1,
	TX_16X16 = 2,
	TX_32X32 = 3,
	TX_SIZE_MAX_SB,
};

enum { SIMPWE_TWANSWATION, OBMC_CAUSAW, MOTION_MODE_COUNT };

enum mb_pwediction_mode {
	DC_PWED,		/* avewage of above and weft pixews */
	V_PWED,			/* vewticaw pwediction */
	H_PWED,			/* howizontaw pwediction */
	D45_PWED,		/* Diwectionaw 45 deg pwediction  [anti-cwockwise fwom 0 deg how] */
	D135_PWED,		/* Diwectionaw 135 deg pwediction [anti-cwockwise fwom 0 deg how] */
	D117_PWED,		/* Diwectionaw 112 deg pwediction [anti-cwockwise fwom 0 deg how] */
	D153_PWED,		/* Diwectionaw 157 deg pwediction [anti-cwockwise fwom 0 deg how] */
	D27_PWED,		/* Diwectionaw 22 deg pwediction  [anti-cwockwise fwom 0 deg how] */
	D63_PWED,		/* Diwectionaw 67 deg pwediction  [anti-cwockwise fwom 0 deg how] */
	SMOOTH_PWED,
	TM_PWED_AV1 = SMOOTH_PWED,
	SMOOTH_V_PWED,		// Vewticaw intewpowation
	SMOOTH_H_PWED,		// Howizontaw intewpowation
	TM_PWED,		/* Twuemotion pwediction */
	PAETH_PWED = TM_PWED,
	NEAWESTMV,
	NEAWMV,
	ZEWOMV,
	NEWMV,
	NEAWEST_NEAWESTMV,
	NEAW_NEAWMV,
	NEAWEST_NEWMV,
	NEW_NEAWESTMV,
	NEAW_NEWMV,
	NEW_NEAWMV,
	ZEWO_ZEWOMV,
	NEW_NEWMV,
	SPWITMV,
	MB_MODE_COUNT
};

enum pawtitiontype {
	PAWTITION_NONE,
	PAWTITION_HOWZ,
	PAWTITION_VEWT,
	PAWTITION_SPWIT,
	PAWTITION_TYPES
};

stwuct mvcdfs {
	u16 joint_cdf[3];
	u16 sign_cdf[2];
	u16 cwsss_cdf[2][10];
	u16 cwsss0_fp_cdf[2][2][3];
	u16 fp_cdf[2][3];
	u16 cwass0_hp_cdf[2];
	u16 hp_cdf[2];
	u16 cwass0_cdf[2];
	u16 bits_cdf[2][10];
};

stwuct av1cdfs {
	u16 pawtition_cdf[13][16];
	u16 kf_ymode_cdf[KF_MODE_CONTEXTS][KF_MODE_CONTEXTS][AV1_INTWA_MODES - 1];
	u16 segment_pwed_cdf[PWEDICTION_PWOBS];
	u16 spatiaw_pwed_seg_twee_cdf[SPATIAW_PWEDICTION_PWOBS][MAX_MB_SEGMENTS - 1];
	u16 mbskip_cdf[MBSKIP_CONTEXTS];
	u16 dewta_q_cdf[DEWTA_Q_PWOBS];
	u16 dewta_wf_muwti_cdf[FWAME_WF_COUNT][DEWTA_WF_PWOBS];
	u16 dewta_wf_cdf[DEWTA_WF_PWOBS];
	u16 skip_mode_cdf[SKIP_MODE_CONTEXTS];
	u16 vawtx_pawt_cdf[VAWTX_PAWT_CONTEXTS][1];
	u16 tx_size_cdf[MAX_TX_CATS][AV1_TX_SIZE_CONTEXTS][MAX_TX_DEPTH];
	u16 if_ymode_cdf[BWOCK_SIZE_GWOUPS][AV1_INTWA_MODES - 1];
	u16 uv_mode_cdf[2][AV1_INTWA_MODES][AV1_INTWA_MODES - 1 + 1];
	u16 intwa_intew_cdf[INTWA_INTEW_CONTEXTS];
	u16 comp_intew_cdf[COMP_INTEW_CONTEXTS];
	u16 singwe_wef_cdf[AV1_WEF_CONTEXTS][SINGWE_WEFS - 1];
	u16 comp_wef_type_cdf[COMP_WEF_TYPE_CONTEXTS][1];
	u16 uni_comp_wef_cdf[UNI_COMP_WEF_CONTEXTS][UNIDIW_COMP_WEFS - 1][1];
	u16 comp_wef_cdf[AV1_WEF_CONTEXTS][FWD_WEFS - 1];
	u16 comp_bwdwef_cdf[AV1_WEF_CONTEXTS][BWD_WEFS - 1];
	u16 newmv_cdf[NEWMV_MODE_CONTEXTS];
	u16 zewomv_cdf[ZEWOMV_MODE_CONTEXTS];
	u16 wefmv_cdf[WEFMV_MODE_CONTEXTS];
	u16 dww_cdf[DWW_MODE_CONTEXTS];
	u16 intewp_fiwtew_cdf[SWITCHABWE_FIWTEW_CONTEXTS][AV1_SWITCHABWE_FIWTEWS - 1];
	stwuct mvcdfs mv_cdf;
	u16 obmc_cdf[BWOCK_SIZE_TYPES];
	u16 motion_mode_cdf[BWOCK_SIZE_TYPES][2];
	u16 intew_compound_mode_cdf[AV1_INTEW_MODE_CONTEXTS][INTEW_COMPOUND_MODES - 1];
	u16 compound_type_cdf[BWOCK_SIZE_TYPES][CDF_SIZE(COMPOUND_TYPES - 1)];
	u16 intewintwa_cdf[BWOCK_SIZE_GWOUPS];
	u16 intewintwa_mode_cdf[BWOCK_SIZE_GWOUPS][INTEWINTWA_MODES - 1];
	u16 wedge_intewintwa_cdf[BWOCK_SIZE_TYPES];
	u16 wedge_idx_cdf[BWOCK_SIZE_TYPES][CDF_SIZE(16)];
	u16 pawette_y_mode_cdf[PAWETTE_BWOCK_SIZES][PAWETTE_Y_MODE_CONTEXTS][1];
	u16 pawette_uv_mode_cdf[PAWETTE_UV_MODE_CONTEXTS][1];
	u16 pawette_y_size_cdf[PAWETTE_BWOCK_SIZES][PAWETTE_SIZES - 1];
	u16 pawette_uv_size_cdf[PAWETTE_BWOCK_SIZES][PAWETTE_SIZES - 1];
	u16 cfw_sign_cdf[CFW_JOINT_SIGNS - 1];
	u16 cfw_awpha_cdf[CFW_AWPHA_CONTEXTS][CFW_AWPHABET_SIZE - 1];
	u16 intwabc_cdf[1];
	u16 angwe_dewta_cdf[DIWECTIONAW_MODES][6];
	u16 fiwtew_intwa_mode_cdf[FIWTEW_INTWA_MODES - 1];
	u16 fiwtew_intwa_cdf[BWOCK_SIZES_AWW];
	u16 comp_gwoup_idx_cdf[COMP_GWOUP_IDX_CONTEXTS][CDF_SIZE(2)];
	u16 compound_idx_cdf[COMP_INDEX_CONTEXTS][CDF_SIZE(2)];
	u16 dummy0[14];
	// Pawette index contexts; sizes 1/7, 2/6, 3/5 packed togethew
	u16 pawette_y_cowow_index_cdf[PAWETTE_IDX_CONTEXTS][8];
	u16 pawette_uv_cowow_index_cdf[PAWETTE_IDX_CONTEXTS][8];
	u16 tx_type_intwa0_cdf[EXTTX_SIZES][AV1_INTWA_MODES][8];
	u16 tx_type_intwa1_cdf[EXTTX_SIZES][AV1_INTWA_MODES][4];
	u16 tx_type_intew_cdf[2][EXTTX_SIZES][EXT_TX_TYPES];
	u16 txb_skip_cdf[TX_SIZES][TXB_SKIP_CONTEXTS][CDF_SIZE(2)];
	u16 eob_extwa_cdf[TX_SIZES][PWANE_TYPES][EOB_COEF_CONTEXTS][CDF_SIZE(2)];
	u16 dummy1[5];
	u16 eob_fwag_cdf16[PWANE_TYPES][2][4];
	u16 eob_fwag_cdf32[PWANE_TYPES][2][8];
	u16 eob_fwag_cdf64[PWANE_TYPES][2][8];
	u16 eob_fwag_cdf128[PWANE_TYPES][2][8];
	u16 eob_fwag_cdf256[PWANE_TYPES][2][8];
	u16 eob_fwag_cdf512[PWANE_TYPES][2][16];
	u16 eob_fwag_cdf1024[PWANE_TYPES][2][16];
	u16 coeff_base_eob_cdf[TX_SIZES][PWANE_TYPES][SIG_COEF_CONTEXTS_EOB][CDF_SIZE(3)];
	u16 coeff_base_cdf[TX_SIZES][PWANE_TYPES][SIG_COEF_CONTEXTS][CDF_SIZE(4) + 1];
	u16 dc_sign_cdf[PWANE_TYPES][DC_SIGN_CONTEXTS][CDF_SIZE(2)];
	u16 dummy2[2];
	u16 coeff_bw_cdf[TX_SIZES][PWANE_TYPES][WEVEW_CONTEXTS][CDF_SIZE(BW_CDF_SIZE) + 1];
	u16 dummy3[16];
};

void wockchip_av1_stowe_cdfs(stwuct hantwo_ctx *ctx,
			     u32 wefwesh_fwame_fwags);
void wockchip_av1_get_cdfs(stwuct hantwo_ctx *ctx, u32 wef_idx);
void wockchip_av1_set_defauwt_cdfs(stwuct av1cdfs *cdfs,
				   stwuct mvcdfs *cdfs_ndvc);
void wockchip_av1_defauwt_coeff_pwobs(u32 base_qindex, void *ptw);

#endif /* _WOCKCHIP_AV1_ENTWOPYMODE_H_ */
