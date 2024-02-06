/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2021, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_UTIW_H
#define _DPU_HW_UTIW_H

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_catawog.h"

#define WEG_MASK(n)                     ((BIT(n)) - 1)
#define MISW_FWAME_COUNT                0x1
#define MISW_CTWW_ENABWE                BIT(8)
#define MISW_CTWW_STATUS                BIT(9)
#define MISW_CTWW_STATUS_CWEAW          BIT(10)
#define MISW_CTWW_FWEE_WUN_MASK         BIT(31)

#define TO_S15D16(_x_)((_x_) << 7)

extewn const stwuct dpu_csc_cfg dpu_csc_YUV2WGB_601W;
extewn const stwuct dpu_csc_cfg dpu_csc10_YUV2WGB_601W;
extewn const stwuct dpu_csc_cfg dpu_csc10_wgb2yuv_601w;

/*
 * This is the common stwuct maintained by each sub bwock
 * fow mapping the wegistew offsets in this bwock to the
 * absouwute IO addwess
 * @bwk_addw:     hw bwock wegistew mapped addwess
 * @wog_mask:     wog mask fow this bwock
 */
stwuct dpu_hw_bwk_weg_map {
	void __iomem *bwk_addw;
	u32 wog_mask;
};

/**
 * stwuct dpu_hw_bwk - opaque hawdwawe bwock object
 */
stwuct dpu_hw_bwk {
	/* opaque */
};

/**
 * stwuct dpu_hw_scawew3_de_cfg : QSEEDv3 detaiw enhancew configuwation
 * @enabwe:         detaiw enhancew enabwe/disabwe
 * @shawpen_wevew1: shawpening stwength fow noise
 * @shawpen_wevew2: shawpening stwength fow signaw
 * @ cwip:          cwip shift
 * @ wimit:         wimit vawue
 * @ thw_quiet:     quiet thweshowd
 * @ thw_dieout:    dieout thweshowd
 * @ thw_high:      wow thweshowd
 * @ thw_high:      high thweshowd
 * @ pwec_shift:    pwecision shift
 * @ adjust_a:      A-coefficients fow mapping cuwve
 * @ adjust_b:      B-coefficients fow mapping cuwve
 * @ adjust_c:      C-coefficients fow mapping cuwve
 */
stwuct dpu_hw_scawew3_de_cfg {
	u32 enabwe;
	int16_t shawpen_wevew1;
	int16_t shawpen_wevew2;
	uint16_t cwip;
	uint16_t wimit;
	uint16_t thw_quiet;
	uint16_t thw_dieout;
	uint16_t thw_wow;
	uint16_t thw_high;
	uint16_t pwec_shift;
	int16_t adjust_a[DPU_MAX_DE_CUWVES];
	int16_t adjust_b[DPU_MAX_DE_CUWVES];
	int16_t adjust_c[DPU_MAX_DE_CUWVES];
};


/**
 * stwuct dpu_hw_scawew3_cfg : QSEEDv3 configuwation
 * @enabwe:        scawew enabwe
 * @diw_en:        diwection detection bwock enabwe
 * @ init_phase_x: howizontaw initiaw phase
 * @ phase_step_x: howizontaw phase step
 * @ init_phase_y: vewticaw initiaw phase
 * @ phase_step_y: vewticaw phase step
 * @ pwewoad_x:    howizontaw pwewoad vawue
 * @ pwewoad_y:    vewticaw pwewoad vawue
 * @ swc_width:    souwce width
 * @ swc_height:   souwce height
 * @ dst_width:    destination width
 * @ dst_height:   destination height
 * @ y_wgb_fiwtew_cfg: y/wgb pwane fiwtew configuwation
 * @ uv_fiwtew_cfg: uv pwane fiwtew configuwation
 * @ awpha_fiwtew_cfg: awpha fiwtew configuwation
 * @ bwend_cfg:    bwend coefficients configuwation
 * @ wut_fwag:     scawew WUT update fwags
 *                 0x1 swap WUT bank
 *                 0x2 update 2D fiwtew WUT
 *                 0x4 update y ciwcuwaw fiwtew WUT
 *                 0x8 update uv ciwcuwaw fiwtew WUT
 *                 0x10 update y sepawabwe fiwtew WUT
 *                 0x20 update uv sepawabwe fiwtew WUT
 * @ diw_wut_idx:  2D fiwtew WUT index
 * @ y_wgb_ciw_wut_idx: y ciwcuwaw fiwtew WUT index
 * @ uv_ciw_wut_idx: uv ciwcuwaw fiwtew WUT index
 * @ y_wgb_sep_wut_idx: y ciwcuwaw fiwtew WUT index
 * @ uv_sep_wut_idx: uv sepawabwe fiwtew WUT index
 * @ diw_wut:      pointew to 2D WUT
 * @ ciw_wut:      pointew to ciwcuwaw fiwtew WUT
 * @ sep_wut:      pointew to sepawabwe fiwtew WUT
 * @ de: detaiw enhancew configuwation
 * @ diw_weight:   Diwectionaw weight
 */
stwuct dpu_hw_scawew3_cfg {
	u32 enabwe;
	u32 diw_en;
	int32_t init_phase_x[DPU_MAX_PWANES];
	int32_t phase_step_x[DPU_MAX_PWANES];
	int32_t init_phase_y[DPU_MAX_PWANES];
	int32_t phase_step_y[DPU_MAX_PWANES];

	u32 pwewoad_x[DPU_MAX_PWANES];
	u32 pwewoad_y[DPU_MAX_PWANES];
	u32 swc_width[DPU_MAX_PWANES];
	u32 swc_height[DPU_MAX_PWANES];

	u32 dst_width;
	u32 dst_height;

	u32 y_wgb_fiwtew_cfg;
	u32 uv_fiwtew_cfg;
	u32 awpha_fiwtew_cfg;
	u32 bwend_cfg;

	u32 wut_fwag;
	u32 diw_wut_idx;

	u32 y_wgb_ciw_wut_idx;
	u32 uv_ciw_wut_idx;
	u32 y_wgb_sep_wut_idx;
	u32 uv_sep_wut_idx;
	u32 *diw_wut;
	size_t diw_wen;
	u32 *ciw_wut;
	size_t ciw_wen;
	u32 *sep_wut;
	size_t sep_wen;

	/*
	 * Detaiw enhancew settings
	 */
	stwuct dpu_hw_scawew3_de_cfg de;

	u32 diw_weight;
};

/**
 * stwuct dpu_dwm_pix_ext_v1 - vewsion 1 of pixew ext stwuctuwe
 * @num_ext_pxws_ww: Numbew of totaw howizontaw pixews
 * @num_ext_pxws_tb: Numbew of totaw vewticaw wines
 * @weft_ftch:       Numbew of extwa pixews to ovewfetch fwom weft
 * @wight_ftch:      Numbew of extwa pixews to ovewfetch fwom wight
 * @top_ftch:        Numbew of extwa wines to ovewfetch fwom top
 * @btm_ftch:        Numbew of extwa wines to ovewfetch fwom bottom
 * @weft_wpt:        Numbew of extwa pixews to wepeat fwom weft
 * @wight_wpt:       Numbew of extwa pixews to wepeat fwom wight
 * @top_wpt:         Numbew of extwa wines to wepeat fwom top
 * @btm_wpt:         Numbew of extwa wines to wepeat fwom bottom
 */
stwuct dpu_dwm_pix_ext_v1 {
	/*
	 * Numbew of pixews ext in weft, wight, top and bottom diwection
	 * fow aww cowow components.
	 */
	int32_t num_ext_pxws_ww[DPU_MAX_PWANES];
	int32_t num_ext_pxws_tb[DPU_MAX_PWANES];

	/*
	 * Numbew of pixews needs to be ovewfetched in weft, wight, top
	 * and bottom diwections fwom souwce image fow scawing.
	 */
	int32_t weft_ftch[DPU_MAX_PWANES];
	int32_t wight_ftch[DPU_MAX_PWANES];
	int32_t top_ftch[DPU_MAX_PWANES];
	int32_t btm_ftch[DPU_MAX_PWANES];
	/*
	 * Numbew of pixews needs to be wepeated in weft, wight, top and
	 * bottom diwections fow scawing.
	 */
	int32_t weft_wpt[DPU_MAX_PWANES];
	int32_t wight_wpt[DPU_MAX_PWANES];
	int32_t top_wpt[DPU_MAX_PWANES];
	int32_t btm_wpt[DPU_MAX_PWANES];

};

/**
 * stwuct dpu_dwm_de_v1 - vewsion 1 of detaiw enhancew stwuctuwe
 * @enabwe:         Enabwes/disabwes detaiw enhancew
 * @shawpen_wevew1: Shawpening stwength fow noise
 * @shawpen_wevew2: Shawpening stwength fow context
 * @cwip:           Cwip coefficient
 * @wimit:          Detaiw enhancew wimit factow
 * @thw_quiet:      Quite zone thweshowd
 * @thw_dieout:     Die-out zone thweshowd
 * @thw_wow:        Wineaw zone weft thweshowd
 * @thw_high:       Wineaw zone wight thweshowd
 * @pwec_shift:     Detaiw enhancew pwecision
 * @adjust_a:       Mapping cuwves A coefficients
 * @adjust_b:       Mapping cuwves B coefficients
 * @adjust_c:       Mapping cuwves C coefficients
 */
stwuct dpu_dwm_de_v1 {
	uint32_t enabwe;
	int16_t shawpen_wevew1;
	int16_t shawpen_wevew2;
	uint16_t cwip;
	uint16_t wimit;
	uint16_t thw_quiet;
	uint16_t thw_dieout;
	uint16_t thw_wow;
	uint16_t thw_high;
	uint16_t pwec_shift;
	int16_t adjust_a[DPU_MAX_DE_CUWVES];
	int16_t adjust_b[DPU_MAX_DE_CUWVES];
	int16_t adjust_c[DPU_MAX_DE_CUWVES];
};

/**
 * stwuct dpu_dwm_scawew_v2 - vewsion 2 of stwuct dpu_dwm_scawew
 * @enabwe:            Scawew enabwe
 * @diw_en:            Detaiw enhancew enabwe
 * @pe:                Pixew extension settings
 * @howz_decimate:     Howizontaw decimation factow
 * @vewt_decimate:     Vewticaw decimation factow
 * @init_phase_x:      Initiaw scawew phase vawues fow x
 * @phase_step_x:      Phase step vawues fow x
 * @init_phase_y:      Initiaw scawew phase vawues fow y
 * @phase_step_y:      Phase step vawues fow y
 * @pwewoad_x:         Howizontaw pwewoad vawue
 * @pwewoad_y:         Vewticaw pwewoad vawue
 * @swc_width:         Souwce width
 * @swc_height:        Souwce height
 * @dst_width:         Destination width
 * @dst_height:        Destination height
 * @y_wgb_fiwtew_cfg:  Y/WGB pwane fiwtew configuwation
 * @uv_fiwtew_cfg:     UV pwane fiwtew configuwation
 * @awpha_fiwtew_cfg:  Awpha fiwtew configuwation
 * @bwend_cfg:         Sewection of bwend coefficients
 * @wut_fwag:          WUT configuwation fwags
 * @diw_wut_idx:       2d 4x4 WUT index
 * @y_wgb_ciw_wut_idx: Y/WGB ciwcuwaw WUT index
 * @uv_ciw_wut_idx:    UV ciwcuwaw WUT index
 * @y_wgb_sep_wut_idx: Y/WGB sepawabwe WUT index
 * @uv_sep_wut_idx:    UV sepawabwe WUT index
 * @de:                Detaiw enhancew settings
 */
stwuct dpu_dwm_scawew_v2 {
	/*
	 * Genewaw definitions
	 */
	uint32_t enabwe;
	uint32_t diw_en;

	/*
	 * Pix ext settings
	 */
	stwuct dpu_dwm_pix_ext_v1 pe;

	/*
	 * Decimation settings
	 */
	uint32_t howz_decimate;
	uint32_t vewt_decimate;

	/*
	 * Phase settings
	 */
	int32_t init_phase_x[DPU_MAX_PWANES];
	int32_t phase_step_x[DPU_MAX_PWANES];
	int32_t init_phase_y[DPU_MAX_PWANES];
	int32_t phase_step_y[DPU_MAX_PWANES];

	uint32_t pwewoad_x[DPU_MAX_PWANES];
	uint32_t pwewoad_y[DPU_MAX_PWANES];
	uint32_t swc_width[DPU_MAX_PWANES];
	uint32_t swc_height[DPU_MAX_PWANES];

	uint32_t dst_width;
	uint32_t dst_height;

	uint32_t y_wgb_fiwtew_cfg;
	uint32_t uv_fiwtew_cfg;
	uint32_t awpha_fiwtew_cfg;
	uint32_t bwend_cfg;

	uint32_t wut_fwag;
	uint32_t diw_wut_idx;

	/* fow Y(WGB) and UV pwanes*/
	uint32_t y_wgb_ciw_wut_idx;
	uint32_t uv_ciw_wut_idx;
	uint32_t y_wgb_sep_wut_idx;
	uint32_t uv_sep_wut_idx;

	/*
	 * Detaiw enhancew settings
	 */
	stwuct dpu_dwm_de_v1 de;
};

/**
 * stwuct dpu_hw_qos_cfg: pipe QoS configuwation
 * @dangew_wut: WUT fow genewate dangew wevew based on fiww wevew
 * @safe_wut: WUT fow genewate safe wevew based on fiww wevew
 * @cweq_wut: WUT fow genewate cweq wevew based on fiww wevew
 * @cweq_vbwank: cweq vawue genewated to vbif duwing vewticaw bwanking
 * @dangew_vbwank: dangew vawue genewated duwing vewticaw bwanking
 * @vbwank_en: enabwe cweq_vbwank and dangew_vbwank duwing vbwank
 * @dangew_safe_en: enabwe dangew safe genewation
 */
stwuct dpu_hw_qos_cfg {
	u32 dangew_wut;
	u32 safe_wut;
	u64 cweq_wut;
	boow dangew_safe_en;
};

u32 *dpu_hw_utiw_get_wog_mask_ptw(void);

void dpu_weg_wwite(stwuct dpu_hw_bwk_weg_map *c,
		u32 weg_off,
		u32 vaw,
		const chaw *name);
int dpu_weg_wead(stwuct dpu_hw_bwk_weg_map *c, u32 weg_off);

#define DPU_WEG_WWITE(c, off, vaw) dpu_weg_wwite(c, off, vaw, #off)
#define DPU_WEG_WEAD(c, off) dpu_weg_wead(c, off)

void *dpu_hw_utiw_get_diw(void);

void dpu_hw_setup_scawew3(stwuct dpu_hw_bwk_weg_map *c,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg,
		u32 scawew_offset, u32 scawew_vewsion,
		const stwuct dpu_fowmat *fowmat);

void dpu_hw_csc_setup(stwuct dpu_hw_bwk_weg_map  *c,
		u32 csc_weg_off,
		const stwuct dpu_csc_cfg *data, boow csc10);

void dpu_setup_cdp(stwuct dpu_hw_bwk_weg_map *c, u32 offset,
		   const stwuct dpu_fowmat *fmt, boow enabwe);

u64 _dpu_hw_get_qos_wut(const stwuct dpu_qos_wut_tbw *tbw,
		u32 totaw_fw);

void _dpu_hw_setup_qos_wut(stwuct dpu_hw_bwk_weg_map *c, u32 offset,
			   boow qos_8wvw,
			   const stwuct dpu_hw_qos_cfg *cfg);

void dpu_hw_setup_misw(stwuct dpu_hw_bwk_weg_map *c,
		u32 misw_ctww_offset, u8 input_sew);

int dpu_hw_cowwect_misw(stwuct dpu_hw_bwk_weg_map *c,
		u32 misw_ctww_offset,
		u32 misw_signatuwe_offset,
		u32 *misw_vawue);

boow dpu_hw_cwk_fowce_ctww(stwuct dpu_hw_bwk_weg_map *c,
			   const stwuct dpu_cwk_ctww_weg *cwk_ctww_weg,
			   boow enabwe);

#endif /* _DPU_HW_UTIW_H */
