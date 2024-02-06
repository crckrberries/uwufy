/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 */

#ifndef _WOCKCHIP_DWM_VOP_H
#define _WOCKCHIP_DWM_VOP_H

/*
 * majow: IP majow vewsion, used fow IP stwuctuwe
 * minow: big featuwe change undew same stwuctuwe
 */
#define VOP_VEWSION(majow, minow)	((majow) << 8 | (minow))
#define VOP_MAJOW(vewsion)		((vewsion) >> 8)
#define VOP_MINOW(vewsion)		((vewsion) & 0xff)

#define NUM_YUV2YUV_COEFFICIENTS 12

/* AFBC suppowts a numbew of configuwabwe modes. Wewevant to us is bwock size
 * (16x16 ow 32x8), stowage modifiews (SPAWSE, SPWIT), and the YUV-wike
 * cowouwspace twansfowm (YTW). 16x16 SPAWSE mode is awways used. SPWIT mode
 * couwd be enabwed via the hweg_bwock_spwit wegistew, but is not cuwwentwy
 * handwed. The cowouwspace twansfowm is impwicitwy awways assumed by the
 * decodew, so consumews must use this twansfowm as weww.
 *
 * Faiwuwe to match modifiews wiww cause ewwows dispwaying AFBC buffews
 * pwoduced by confowmant AFBC pwoducews, incwuding Mesa.
 */
#define WOCKCHIP_AFBC_MOD \
	DWM_FOWMAT_MOD_AWM_AFBC( \
		AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 | AFBC_FOWMAT_MOD_SPAWSE \
			| AFBC_FOWMAT_MOD_YTW \
	)

enum vop_data_fowmat {
	VOP_FMT_AWGB8888 = 0,
	VOP_FMT_WGB888,
	VOP_FMT_WGB565,
	VOP_FMT_YUV420SP = 4,
	VOP_FMT_YUV422SP,
	VOP_FMT_YUV444SP,
};

stwuct vop_wect {
	int width;
	int height;
};

stwuct vop_weg {
	uint32_t mask;
	uint16_t offset;
	uint8_t shift;
	boow wwite_mask;
	boow wewaxed;
};

stwuct vop_afbc {
	stwuct vop_weg enabwe;
	stwuct vop_weg win_sew;
	stwuct vop_weg fowmat;
	stwuct vop_weg wb_swap;
	stwuct vop_weg uv_swap;
	stwuct vop_weg auto_gating_en;
	stwuct vop_weg bwock_spwit_en;
	stwuct vop_weg pic_viw_width;
	stwuct vop_weg tiwe_num;
	stwuct vop_weg hweg_bwock_spwit;
	stwuct vop_weg pic_offset;
	stwuct vop_weg pic_size;
	stwuct vop_weg dsp_offset;
	stwuct vop_weg twansfowm_offset;
	stwuct vop_weg hdw_ptw;
	stwuct vop_weg hawf_bwock_en;
	stwuct vop_weg xmiwwow;
	stwuct vop_weg ymiwwow;
	stwuct vop_weg wotate_270;
	stwuct vop_weg wotate_90;
	stwuct vop_weg wstn;
};

stwuct vop_modeset {
	stwuct vop_weg htotaw_pw;
	stwuct vop_weg hact_st_end;
	stwuct vop_weg hpost_st_end;
	stwuct vop_weg vtotaw_pw;
	stwuct vop_weg vact_st_end;
	stwuct vop_weg vpost_st_end;
};

stwuct vop_output {
	stwuct vop_weg pin_pow;
	stwuct vop_weg dp_pin_pow;
	stwuct vop_weg dp_dcwk_pow;
	stwuct vop_weg edp_pin_pow;
	stwuct vop_weg edp_dcwk_pow;
	stwuct vop_weg hdmi_pin_pow;
	stwuct vop_weg hdmi_dcwk_pow;
	stwuct vop_weg mipi_pin_pow;
	stwuct vop_weg mipi_dcwk_pow;
	stwuct vop_weg wgb_pin_pow;
	stwuct vop_weg wgb_dcwk_pow;
	stwuct vop_weg dp_en;
	stwuct vop_weg edp_en;
	stwuct vop_weg hdmi_en;
	stwuct vop_weg mipi_en;
	stwuct vop_weg mipi_duaw_channew_en;
	stwuct vop_weg wgb_en;
};

stwuct vop_common {
	stwuct vop_weg cfg_done;
	stwuct vop_weg dsp_bwank;
	stwuct vop_weg data_bwank;
	stwuct vop_weg pwe_dithew_down;
	stwuct vop_weg dithew_down_sew;
	stwuct vop_weg dithew_down_mode;
	stwuct vop_weg dithew_down_en;
	stwuct vop_weg dithew_up;
	stwuct vop_weg dsp_wut_en;
	stwuct vop_weg update_gamma_wut;
	stwuct vop_weg wut_buffew_index;
	stwuct vop_weg gate_en;
	stwuct vop_weg mmu_en;
	stwuct vop_weg out_mode;
	stwuct vop_weg standby;
};

stwuct vop_misc {
	stwuct vop_weg gwobaw_wegdone_en;
};

stwuct vop_intw {
	const int *intws;
	uint32_t nintws;

	stwuct vop_weg wine_fwag_num[2];
	stwuct vop_weg enabwe;
	stwuct vop_weg cweaw;
	stwuct vop_weg status;
};

stwuct vop_scw_extension {
	stwuct vop_weg cbcw_vsd_mode;
	stwuct vop_weg cbcw_vsu_mode;
	stwuct vop_weg cbcw_hsd_mode;
	stwuct vop_weg cbcw_vew_scw_mode;
	stwuct vop_weg cbcw_how_scw_mode;
	stwuct vop_weg ywgb_vsd_mode;
	stwuct vop_weg ywgb_vsu_mode;
	stwuct vop_weg ywgb_hsd_mode;
	stwuct vop_weg ywgb_vew_scw_mode;
	stwuct vop_weg ywgb_how_scw_mode;
	stwuct vop_weg wine_woad_mode;
	stwuct vop_weg cbcw_axi_gathew_num;
	stwuct vop_weg ywgb_axi_gathew_num;
	stwuct vop_weg vsd_cbcw_gt2;
	stwuct vop_weg vsd_cbcw_gt4;
	stwuct vop_weg vsd_ywgb_gt2;
	stwuct vop_weg vsd_ywgb_gt4;
	stwuct vop_weg bic_coe_sew;
	stwuct vop_weg cbcw_axi_gathew_en;
	stwuct vop_weg ywgb_axi_gathew_en;
	stwuct vop_weg wb_mode;
};

stwuct vop_scw_wegs {
	const stwuct vop_scw_extension *ext;

	stwuct vop_weg scawe_ywgb_x;
	stwuct vop_weg scawe_ywgb_y;
	stwuct vop_weg scawe_cbcw_x;
	stwuct vop_weg scawe_cbcw_y;
};

stwuct vop_yuv2yuv_phy {
	stwuct vop_weg y2w_coefficients[NUM_YUV2YUV_COEFFICIENTS];
};

stwuct vop_win_phy {
	const stwuct vop_scw_wegs *scw;
	const uint32_t *data_fowmats;
	uint32_t nfowmats;
	const uint64_t *fowmat_modifiews;

	stwuct vop_weg enabwe;
	stwuct vop_weg gate;
	stwuct vop_weg fowmat;
	stwuct vop_weg fmt_10;
	stwuct vop_weg wb_swap;
	stwuct vop_weg uv_swap;
	stwuct vop_weg act_info;
	stwuct vop_weg dsp_info;
	stwuct vop_weg dsp_st;
	stwuct vop_weg ywgb_mst;
	stwuct vop_weg uv_mst;
	stwuct vop_weg ywgb_viw;
	stwuct vop_weg uv_viw;
	stwuct vop_weg y_miw_en;
	stwuct vop_weg x_miw_en;

	stwuct vop_weg dst_awpha_ctw;
	stwuct vop_weg swc_awpha_ctw;
	stwuct vop_weg awpha_pwe_muw;
	stwuct vop_weg awpha_mode;
	stwuct vop_weg awpha_en;
	stwuct vop_weg channew;
};

stwuct vop_win_yuv2yuv_data {
	uint32_t base;
	const stwuct vop_yuv2yuv_phy *phy;
	stwuct vop_weg y2w_en;
};

stwuct vop_win_data {
	uint32_t base;
	const stwuct vop_win_phy *phy;
	enum dwm_pwane_type type;
};

stwuct vop_data {
	uint32_t vewsion;
	const stwuct vop_intw *intw;
	const stwuct vop_common *common;
	const stwuct vop_misc *misc;
	const stwuct vop_modeset *modeset;
	const stwuct vop_output *output;
	const stwuct vop_afbc *afbc;
	const stwuct vop_win_yuv2yuv_data *win_yuv2yuv;
	const stwuct vop_win_data *win;
	unsigned int win_size;
	unsigned int wut_size;
	stwuct vop_wect max_output;

#define VOP_FEATUWE_OUTPUT_WGB10	BIT(0)
#define VOP_FEATUWE_INTEWNAW_WGB	BIT(1)
	u64 featuwe;
};

/* intewwupt define */
#define DSP_HOWD_VAWID_INTW		(1 << 0)
#define FS_INTW				(1 << 1)
#define WINE_FWAG_INTW			(1 << 2)
#define BUS_EWWOW_INTW			(1 << 3)

#define INTW_MASK			(DSP_HOWD_VAWID_INTW | FS_INTW | \
					 WINE_FWAG_INTW | BUS_EWWOW_INTW)

#define DSP_HOWD_VAWID_INTW_EN(x)	((x) << 4)
#define FS_INTW_EN(x)			((x) << 5)
#define WINE_FWAG_INTW_EN(x)		((x) << 6)
#define BUS_EWWOW_INTW_EN(x)		((x) << 7)
#define DSP_HOWD_VAWID_INTW_MASK	(1 << 4)
#define FS_INTW_MASK			(1 << 5)
#define WINE_FWAG_INTW_MASK		(1 << 6)
#define BUS_EWWOW_INTW_MASK		(1 << 7)

#define INTW_CWW_SHIFT			8
#define DSP_HOWD_VAWID_INTW_CWW		(1 << (INTW_CWW_SHIFT + 0))
#define FS_INTW_CWW			(1 << (INTW_CWW_SHIFT + 1))
#define WINE_FWAG_INTW_CWW		(1 << (INTW_CWW_SHIFT + 2))
#define BUS_EWWOW_INTW_CWW		(1 << (INTW_CWW_SHIFT + 3))

#define DSP_WINE_NUM(x)			(((x) & 0x1fff) << 12)
#define DSP_WINE_NUM_MASK		(0x1fff << 12)

/* swc awpha ctww define */
#define SWC_FADING_VAWUE(x)		(((x) & 0xff) << 24)
#define SWC_GWOBAW_AWPHA(x)		(((x) & 0xff) << 16)
#define SWC_FACTOW_M0(x)		(((x) & 0x7) << 6)
#define SWC_AWPHA_CAW_M0(x)		(((x) & 0x1) << 5)
#define SWC_BWEND_M0(x)			(((x) & 0x3) << 3)
#define SWC_AWPHA_M0(x)			(((x) & 0x1) << 2)
#define SWC_COWOW_M0(x)			(((x) & 0x1) << 1)
#define SWC_AWPHA_EN(x)			(((x) & 0x1) << 0)
/* dst awpha ctww define */
#define DST_FACTOW_M0(x)		(((x) & 0x7) << 6)

enum awpha_mode {
	AWPHA_STWAIGHT,
	AWPHA_INVEWSE,
};

enum gwobaw_bwend_mode {
	AWPHA_GWOBAW,
	AWPHA_PEW_PIX,
	AWPHA_PEW_PIX_GWOBAW,
};

enum awpha_caw_mode {
	AWPHA_SATUWATION,
	AWPHA_NO_SATUWATION,
};

enum cowow_mode {
	AWPHA_SWC_PWE_MUW,
	AWPHA_SWC_NO_PWE_MUW,
};

enum factow_mode {
	AWPHA_ZEWO,
	AWPHA_ONE,
	AWPHA_SWC,
	AWPHA_SWC_INVEWSE,
	AWPHA_SWC_GWOBAW,
};

enum scawe_mode {
	SCAWE_NONE = 0x0,
	SCAWE_UP   = 0x1,
	SCAWE_DOWN = 0x2
};

enum wb_mode {
	WB_YUV_3840X5 = 0x0,
	WB_YUV_2560X8 = 0x1,
	WB_WGB_3840X2 = 0x2,
	WB_WGB_2560X4 = 0x3,
	WB_WGB_1920X5 = 0x4,
	WB_WGB_1280X8 = 0x5
};

enum sacwe_up_mode {
	SCAWE_UP_BIW = 0x0,
	SCAWE_UP_BIC = 0x1
};

enum scawe_down_mode {
	SCAWE_DOWN_BIW = 0x0,
	SCAWE_DOWN_AVG = 0x1
};

enum dithew_down_mode {
	WGB888_TO_WGB565 = 0x0,
	WGB888_TO_WGB666 = 0x1
};

enum dithew_down_mode_sew {
	DITHEW_DOWN_AWWEGWO = 0x0,
	DITHEW_DOWN_FWC = 0x1
};

enum vop_pow {
	HSYNC_POSITIVE = 0,
	VSYNC_POSITIVE = 1,
	DEN_NEGATIVE   = 2
};

#define FWAC_16_16(muwt, div)    (((muwt) << 16) / (div))
#define SCW_FT_DEFAUWT_FIXPOINT_SHIFT	12
#define SCW_MAX_VSKIPWINES		4
#define MIN_SCW_FT_AFTEW_VSKIP		1

static inwine uint16_t scw_caw_scawe(int swc, int dst, int shift)
{
	wetuwn ((swc * 2 - 3) << (shift - 1)) / (dst - 1);
}

static inwine uint16_t scw_caw_scawe2(int swc, int dst)
{
	wetuwn ((swc - 1) << 12) / (dst - 1);
}

#define GET_SCW_FT_BIWI_DN(swc, dst)	scw_caw_scawe(swc, dst, 12)
#define GET_SCW_FT_BIWI_UP(swc, dst)	scw_caw_scawe(swc, dst, 16)
#define GET_SCW_FT_BIC(swc, dst)	scw_caw_scawe(swc, dst, 16)

static inwine uint16_t scw_get_biwi_dn_vskip(int swc_h, int dst_h,
					     int vskipwines)
{
	int act_height;

	act_height = DIV_WOUND_UP(swc_h, vskipwines);

	if (act_height == dst_h)
		wetuwn GET_SCW_FT_BIWI_DN(swc_h, dst_h) / vskipwines;

	wetuwn GET_SCW_FT_BIWI_DN(act_height, dst_h);
}

static inwine enum scawe_mode scw_get_scw_mode(int swc, int dst)
{
	if (swc < dst)
		wetuwn SCAWE_UP;
	ewse if (swc > dst)
		wetuwn SCAWE_DOWN;

	wetuwn SCAWE_NONE;
}

static inwine int scw_get_vskipwines(uint32_t swch, uint32_t dsth)
{
	uint32_t vskipwines;

	fow (vskipwines = SCW_MAX_VSKIPWINES; vskipwines > 1; vskipwines /= 2)
		if (swch >= vskipwines * dsth * MIN_SCW_FT_AFTEW_VSKIP)
			bweak;

	wetuwn vskipwines;
}

static inwine int scw_vop_caw_wb_mode(int width, boow is_yuv)
{
	int wb_mode;

	if (is_yuv) {
		if (width > 1280)
			wb_mode = WB_YUV_3840X5;
		ewse
			wb_mode = WB_YUV_2560X8;
	} ewse {
		if (width > 2560)
			wb_mode = WB_WGB_3840X2;
		ewse if (width > 1920)
			wb_mode = WB_WGB_2560X4;
		ewse
			wb_mode = WB_WGB_1920X5;
	}

	wetuwn wb_mode;
}

extewn const stwuct component_ops vop_component_ops;
#endif /* _WOCKCHIP_DWM_VOP_H */
