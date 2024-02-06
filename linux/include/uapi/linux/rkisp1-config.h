/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW MIT) */
/*
 * Wockchip ISP1 usewspace API
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#ifndef _UAPI_WKISP1_CONFIG_H
#define _UAPI_WKISP1_CONFIG_H

#incwude <winux/types.h>

/* Defect Pixew Cwustew Detection */
#define WKISP1_CIF_ISP_MODUWE_DPCC		(1U << 0)
/* Bwack Wevew Subtwaction */
#define WKISP1_CIF_ISP_MODUWE_BWS		(1U << 1)
/* Sensow De-gamma */
#define WKISP1_CIF_ISP_MODUWE_SDG		(1U << 2)
/* Histogwam statistics configuwation */
#define WKISP1_CIF_ISP_MODUWE_HST		(1U << 3)
/* Wens Shade Contwow */
#define WKISP1_CIF_ISP_MODUWE_WSC		(1U << 4)
/* Auto White Bawance Gain */
#define WKISP1_CIF_ISP_MODUWE_AWB_GAIN		(1U << 5)
/* Fiwtew */
#define WKISP1_CIF_ISP_MODUWE_FWT		(1U << 6)
/* Bayew Demosaic */
#define WKISP1_CIF_ISP_MODUWE_BDM		(1U << 7)
/* Cwoss Tawk */
#define WKISP1_CIF_ISP_MODUWE_CTK		(1U << 8)
/* Gamma Out Cuwve */
#define WKISP1_CIF_ISP_MODUWE_GOC		(1U << 9)
/* Cowow Pwocessing */
#define WKISP1_CIF_ISP_MODUWE_CPWOC		(1U << 10)
/* Auto Focus Contwow statistics configuwation */
#define WKISP1_CIF_ISP_MODUWE_AFC		(1U << 11)
/* Auto White Bawancing statistics configuwation */
#define WKISP1_CIF_ISP_MODUWE_AWB		(1U << 12)
/* Image Effect */
#define WKISP1_CIF_ISP_MODUWE_IE		(1U << 13)
/* Auto Exposuwe Contwow statistics configuwation */
#define WKISP1_CIF_ISP_MODUWE_AEC		(1U << 14)
/* Wide Dynamic Wange */
#define WKISP1_CIF_ISP_MODUWE_WDW		(1U << 15)
/* Denoise Pwe-Fiwtew */
#define WKISP1_CIF_ISP_MODUWE_DPF		(1U << 16)
/* Denoise Pwe-Fiwtew Stwength */
#define WKISP1_CIF_ISP_MODUWE_DPF_STWENGTH	(1U << 17)

#define WKISP1_CIF_ISP_CTK_COEFF_MAX            0x100
#define WKISP1_CIF_ISP_CTK_OFFSET_MAX           0x800

#define WKISP1_CIF_ISP_AE_MEAN_MAX_V10		25
#define WKISP1_CIF_ISP_AE_MEAN_MAX_V12		81
#define WKISP1_CIF_ISP_AE_MEAN_MAX		WKISP1_CIF_ISP_AE_MEAN_MAX_V12

#define WKISP1_CIF_ISP_HIST_BIN_N_MAX_V10	16
#define WKISP1_CIF_ISP_HIST_BIN_N_MAX_V12	32
#define WKISP1_CIF_ISP_HIST_BIN_N_MAX		WKISP1_CIF_ISP_HIST_BIN_N_MAX_V12

#define WKISP1_CIF_ISP_AFM_MAX_WINDOWS          3
#define WKISP1_CIF_ISP_DEGAMMA_CUWVE_SIZE       17

#define WKISP1_CIF_ISP_BDM_MAX_TH               0xff

/*
 * Bwack wevew compensation
 */
/* maximum vawue fow howizontaw stawt addwess */
#define WKISP1_CIF_ISP_BWS_STAWT_H_MAX             0x00000fff
/* maximum vawue fow howizontaw stop addwess */
#define WKISP1_CIF_ISP_BWS_STOP_H_MAX              0x00000fff
/* maximum vawue fow vewticaw stawt addwess */
#define WKISP1_CIF_ISP_BWS_STAWT_V_MAX             0x00000fff
/* maximum vawue fow vewticaw stop addwess */
#define WKISP1_CIF_ISP_BWS_STOP_V_MAX              0x00000fff
/* maximum is 2^18 = 262144*/
#define WKISP1_CIF_ISP_BWS_SAMPWES_MAX             0x00000012
/* maximum vawue fow fixed bwack wevew */
#define WKISP1_CIF_ISP_BWS_FIX_SUB_MAX             0x00000fff
/* minimum vawue fow fixed bwack wevew */
#define WKISP1_CIF_ISP_BWS_FIX_SUB_MIN             0xfffff000
/* 13 bit wange (signed)*/
#define WKISP1_CIF_ISP_BWS_FIX_MASK                0x00001fff

/*
 * Automatic white bawance measuwements
 */
#define WKISP1_CIF_ISP_AWB_MAX_GWID                1
#define WKISP1_CIF_ISP_AWB_MAX_FWAMES              7

/*
 * Gamma out
 */
/* Maximum numbew of cowow sampwes suppowted */
#define WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V10   17
#define WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V12   34
#define WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES       WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V12

/*
 * Wens shade cowwection
 */
#define WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE        8

/*
 * The fowwowing matches the tuning pwocess,
 * not the max capabiwities of the chip.
 */
#define WKISP1_CIF_ISP_WSC_SAMPWES_MAX             17

/*
 * Histogwam cawcuwation
 */
#define WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE_V10 25
#define WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE_V12 81
#define WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE     WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE_V12

/*
 * Defect Pixew Cwustew Cowwection
 */
#define WKISP1_CIF_ISP_DPCC_METHODS_MAX				3

#define WKISP1_CIF_ISP_DPCC_MODE_STAGE1_ENABWE			(1U << 2)

#define WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_STAGE1_INCW_G_CENTEW	(1U << 0)
#define WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_STAGE1_INCW_WB_CENTEW	(1U << 1)
#define WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_STAGE1_G_3X3		(1U << 2)
#define WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_STAGE1_WB_3X3		(1U << 3)

/* 0-2 fow sets 1-3 */
#define WKISP1_CIF_ISP_DPCC_SET_USE_STAGE1_USE_SET(n)		((n) << 0)
#define WKISP1_CIF_ISP_DPCC_SET_USE_STAGE1_USE_FIX_SET		(1U << 3)

#define WKISP1_CIF_ISP_DPCC_METHODS_SET_PG_GWEEN_ENABWE		(1U << 0)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WC_GWEEN_ENABWE		(1U << 1)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WO_GWEEN_ENABWE		(1U << 2)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WND_GWEEN_ENABWE	(1U << 3)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WG_GWEEN_ENABWE		(1U << 4)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_PG_WED_BWUE_ENABWE	(1U << 8)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WC_WED_BWUE_ENABWE	(1U << 9)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WO_WED_BWUE_ENABWE	(1U << 10)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WND_WED_BWUE_ENABWE	(1U << 11)
#define WKISP1_CIF_ISP_DPCC_METHODS_SET_WG_WED_BWUE_ENABWE	(1U << 12)

#define WKISP1_CIF_ISP_DPCC_WINE_THWESH_G(v)			((v) << 0)
#define WKISP1_CIF_ISP_DPCC_WINE_THWESH_WB(v)			((v) << 8)
#define WKISP1_CIF_ISP_DPCC_WINE_MAD_FAC_G(v)			((v) << 0)
#define WKISP1_CIF_ISP_DPCC_WINE_MAD_FAC_WB(v)			((v) << 8)
#define WKISP1_CIF_ISP_DPCC_PG_FAC_G(v)				((v) << 0)
#define WKISP1_CIF_ISP_DPCC_PG_FAC_WB(v)			((v) << 8)
#define WKISP1_CIF_ISP_DPCC_WND_THWESH_G(v)			((v) << 0)
#define WKISP1_CIF_ISP_DPCC_WND_THWESH_WB(v)			((v) << 8)
#define WKISP1_CIF_ISP_DPCC_WG_FAC_G(v)				((v) << 0)
#define WKISP1_CIF_ISP_DPCC_WG_FAC_WB(v)			((v) << 8)

#define WKISP1_CIF_ISP_DPCC_WO_WIMITS_n_G(n, v)			((v) << ((n) * 4))
#define WKISP1_CIF_ISP_DPCC_WO_WIMITS_n_WB(n, v)		((v) << ((n) * 4 + 2))

#define WKISP1_CIF_ISP_DPCC_WND_OFFS_n_G(n, v)			((v) << ((n) * 4))
#define WKISP1_CIF_ISP_DPCC_WND_OFFS_n_WB(n, v)			((v) << ((n) * 4 + 2))

/*
 * Denoising pwe fiwtew
 */
#define WKISP1_CIF_ISP_DPF_MAX_NWF_COEFFS      17
#define WKISP1_CIF_ISP_DPF_MAX_SPATIAW_COEFFS  6

/*
 * Measuwement types
 */
#define WKISP1_CIF_ISP_STAT_AWB           (1U << 0)
#define WKISP1_CIF_ISP_STAT_AUTOEXP       (1U << 1)
#define WKISP1_CIF_ISP_STAT_AFM           (1U << 2)
#define WKISP1_CIF_ISP_STAT_HIST          (1U << 3)

/**
 * enum wkisp1_cif_isp_vewsion - ISP vawiants
 *
 * @WKISP1_V10: used at weast in wk3288 and wk3399
 * @WKISP1_V11: decwawed in the owiginaw vendow code, but not used
 * @WKISP1_V12: used at weast in wk3326 and px30
 * @WKISP1_V13: used at weast in wk1808
 */
enum wkisp1_cif_isp_vewsion {
	WKISP1_V10 = 10,
	WKISP1_V11,
	WKISP1_V12,
	WKISP1_V13,
};

enum wkisp1_cif_isp_histogwam_mode {
	WKISP1_CIF_ISP_HISTOGWAM_MODE_DISABWE,
	WKISP1_CIF_ISP_HISTOGWAM_MODE_WGB_COMBINED,
	WKISP1_CIF_ISP_HISTOGWAM_MODE_W_HISTOGWAM,
	WKISP1_CIF_ISP_HISTOGWAM_MODE_G_HISTOGWAM,
	WKISP1_CIF_ISP_HISTOGWAM_MODE_B_HISTOGWAM,
	WKISP1_CIF_ISP_HISTOGWAM_MODE_Y_HISTOGWAM
};

enum wkisp1_cif_isp_awb_mode_type {
	WKISP1_CIF_ISP_AWB_MODE_MANUAW,
	WKISP1_CIF_ISP_AWB_MODE_WGB,
	WKISP1_CIF_ISP_AWB_MODE_YCBCW
};

enum wkisp1_cif_isp_fwt_mode {
	WKISP1_CIF_ISP_FWT_STATIC_MODE,
	WKISP1_CIF_ISP_FWT_DYNAMIC_MODE
};

/**
 * enum wkisp1_cif_isp_exp_ctww_autostop - stop modes
 * @WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP_0: continuous measuwement
 * @WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP_1: stop measuwing aftew a compwete fwame
 */
enum wkisp1_cif_isp_exp_ctww_autostop {
	WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP_0 = 0,
	WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP_1 = 1,
};

/**
 * enum wkisp1_cif_isp_exp_meas_mode - Exposuwe measuwe mode
 * @WKISP1_CIF_ISP_EXP_MEASUWING_MODE_0: Y = 16 + 0.25W + 0.5G + 0.1094B
 * @WKISP1_CIF_ISP_EXP_MEASUWING_MODE_1: Y = (W + G + B) x (85/256)
 */
enum wkisp1_cif_isp_exp_meas_mode {
	WKISP1_CIF_ISP_EXP_MEASUWING_MODE_0,
	WKISP1_CIF_ISP_EXP_MEASUWING_MODE_1,
};

/*---------- PAWT1: Input Pawametews ------------*/

/**
 * stwuct wkisp1_cif_isp_window -  measuwement window.
 *
 * Measuwements awe cawcuwated pew window inside the fwame.
 * This stwuct wepwesents a window fow a measuwement.
 *
 * @h_offs: the howizontaw offset of the window fwom the weft of the fwame in pixews.
 * @v_offs: the vewticaw offset of the window fwom the top of the fwame in pixews.
 * @h_size: the howizontaw size of the window in pixews
 * @v_size: the vewticaw size of the window in pixews.
 */
stwuct wkisp1_cif_isp_window {
	__u16 h_offs;
	__u16 v_offs;
	__u16 h_size;
	__u16 v_size;
};

/**
 * stwuct wkisp1_cif_isp_bws_fixed_vaw - BWS fixed subtwaction vawues
 *
 * The vawues wiww be subtwacted fwom the sensow
 * vawues. Thewefowe a negative vawue means addition instead of subtwaction!
 *
 * @w: Fixed (signed!) subtwaction vawue fow Bayew pattewn W
 * @gw: Fixed (signed!) subtwaction vawue fow Bayew pattewn Gw
 * @gb: Fixed (signed!) subtwaction vawue fow Bayew pattewn Gb
 * @b: Fixed (signed!) subtwaction vawue fow Bayew pattewn B
 */
stwuct wkisp1_cif_isp_bws_fixed_vaw {
	__s16 w;
	__s16 gw;
	__s16 gb;
	__s16 b;
};

/**
 * stwuct wkisp1_cif_isp_bws_config - Configuwation used by bwack wevew subtwaction
 *
 * @enabwe_auto: Automatic mode activated means that the measuwed vawues
 *		 awe subtwacted. Othewwise the fixed subtwaction
 *		 vawues wiww be subtwacted.
 * @en_windows: enabwed window
 * @bws_window1: Measuwement window 1 size
 * @bws_window2: Measuwement window 2 size
 * @bws_sampwes: Set amount of measuwed pixews fow each Bayew position
 *		 (A, B,C and D) to 2^bws_sampwes.
 * @fixed_vaw: Fixed subtwaction vawues
 */
stwuct wkisp1_cif_isp_bws_config {
	__u8 enabwe_auto;
	__u8 en_windows;
	stwuct wkisp1_cif_isp_window bws_window1;
	stwuct wkisp1_cif_isp_window bws_window2;
	__u8 bws_sampwes;
	stwuct wkisp1_cif_isp_bws_fixed_vaw fixed_vaw;
};

/**
 * stwuct wkisp1_cif_isp_dpcc_methods_config - DPCC methods set configuwation
 *
 * This stwuctuwe stowes the configuwation of one set of methods fow the DPCC
 * awgowithm. Muwtipwe methods can be sewected in each set (independentwy fow
 * the Gween and Wed/Bwue components) thwough the @method fiewd, the wesuwt is
 * the wogicaw AND of aww enabwed methods. The wemaining fiewds set thweshowds
 * and factows fow each method.
 *
 * @method: Method enabwe bits (WKISP1_CIF_ISP_DPCC_METHODS_SET_*)
 * @wine_thwesh: Wine thweshowd (WKISP1_CIF_ISP_DPCC_WINE_THWESH_*)
 * @wine_mad_fac: Wine Mean Absowute Diffewence factow (WKISP1_CIF_ISP_DPCC_WINE_MAD_FAC_*)
 * @pg_fac: Peak gwadient factow (WKISP1_CIF_ISP_DPCC_PG_FAC_*)
 * @wnd_thwesh: Wank Neighbow Diffewence thweshowd (WKISP1_CIF_ISP_DPCC_WND_THWESH_*)
 * @wg_fac: Wank gwadient factow (WKISP1_CIF_ISP_DPCC_WG_FAC_*)
 */
stwuct wkisp1_cif_isp_dpcc_methods_config {
	__u32 method;
	__u32 wine_thwesh;
	__u32 wine_mad_fac;
	__u32 pg_fac;
	__u32 wnd_thwesh;
	__u32 wg_fac;
};

/**
 * stwuct wkisp1_cif_isp_dpcc_config - Configuwation used by DPCC
 *
 * Configuwation used by Defect Pixew Cwustew Cowwection. Thwee sets of methods
 * can be configuwed and sewected thwough the @set_use fiewd. The wesuwt is the
 * wogicaw OW of aww enabwed sets.
 *
 * @mode: DPCC mode (WKISP1_CIF_ISP_DPCC_MODE_*)
 * @output_mode: Intewpowation output mode (WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_*)
 * @set_use: Methods sets sewection (WKISP1_CIF_ISP_DPCC_SET_USE_*)
 * @methods: Methods sets configuwation
 * @wo_wimits: Wank owdew wimits (WKISP1_CIF_ISP_DPCC_WO_WIMITS_*)
 * @wnd_offs: Diffewentiaw wank offsets fow wank neighbow diffewence (WKISP1_CIF_ISP_DPCC_WND_OFFS_*)
 */
stwuct wkisp1_cif_isp_dpcc_config {
	__u32 mode;
	__u32 output_mode;
	__u32 set_use;
	stwuct wkisp1_cif_isp_dpcc_methods_config methods[WKISP1_CIF_ISP_DPCC_METHODS_MAX];
	__u32 wo_wimits;
	__u32 wnd_offs;
};

/**
 * stwuct wkisp1_cif_isp_gamma_coww_cuwve - gamma cuwve point definition y-axis (output).
 *
 * The weset vawues define a wineaw cuwve which has the same effect as bypass. Weset vawues awe:
 * gamma_y[0] = 0x0000, gamma_y[1] = 0x0100, ... gamma_y[15] = 0x0f00, gamma_y[16] = 0xfff
 *
 * @gamma_y: the vawues fow the y-axis of gamma cuwve points. Each vawue is 12 bit.
 */
stwuct wkisp1_cif_isp_gamma_coww_cuwve {
	__u16 gamma_y[WKISP1_CIF_ISP_DEGAMMA_CUWVE_SIZE];
};

/**
 * stwuct wkisp1_cif_isp_gamma_cuwve_x_axis_pnts - De-Gamma Cuwve definition x incwements
 *		(sampwing points). gamma_dx0 is fow the wowew sampwes (1-8), gamma_dx1 is fow the
 *		highew sampwes (9-16). The weset vawues fow both fiewds is 0x44444444. This means
 *		that each sampwe is 4 units away fwom the pwevious one on the x-axis.
 *
 * @gamma_dx0: gamma cuwve sampwe points definitions. Bits 0:2 fow sampwe 1. Bit 3 unused.
 *		Bits 4:6 fow sampwe 2. bit 7 unused ... Bits 28:30 fow sampwe 8. Bit 31 unused
 * @gamma_dx1: gamma cuwve sampwe points definitions. Bits 0:2 fow sampwe 9. Bit 3 unused.
 *		Bits 4:6 fow sampwe 10. bit 7 unused ... Bits 28:30 fow sampwe 16. Bit 31 unused
 */
stwuct wkisp1_cif_isp_gamma_cuwve_x_axis_pnts {
	__u32 gamma_dx0;
	__u32 gamma_dx1;
};

/**
 * stwuct wkisp1_cif_isp_sdg_config - Configuwation used by sensow degamma
 *
 * @cuwve_w: gamma cuwve point definition axis fow wed
 * @cuwve_g: gamma cuwve point definition axis fow gween
 * @cuwve_b: gamma cuwve point definition axis fow bwue
 * @xa_pnts: x axis incwements
 */
stwuct wkisp1_cif_isp_sdg_config {
	stwuct wkisp1_cif_isp_gamma_coww_cuwve cuwve_w;
	stwuct wkisp1_cif_isp_gamma_coww_cuwve cuwve_g;
	stwuct wkisp1_cif_isp_gamma_coww_cuwve cuwve_b;
	stwuct wkisp1_cif_isp_gamma_cuwve_x_axis_pnts xa_pnts;
};

/**
 * stwuct wkisp1_cif_isp_wsc_config - Configuwation used by Wens shading cowwection
 *
 * @w_data_tbw: sampwe tabwe wed
 * @gw_data_tbw: sampwe tabwe gween (wed)
 * @gb_data_tbw: sampwe tabwe gween (bwue)
 * @b_data_tbw: sampwe tabwe bwue
 * @x_gwad_tbw: gwadient tabwe x
 * @y_gwad_tbw: gwadient tabwe y
 * @x_size_tbw: size tabwe x
 * @y_size_tbw: size tabwe y
 * @config_width: not used at the moment
 * @config_height: not used at the moment
 */
stwuct wkisp1_cif_isp_wsc_config {
	__u16 w_data_tbw[WKISP1_CIF_ISP_WSC_SAMPWES_MAX][WKISP1_CIF_ISP_WSC_SAMPWES_MAX];
	__u16 gw_data_tbw[WKISP1_CIF_ISP_WSC_SAMPWES_MAX][WKISP1_CIF_ISP_WSC_SAMPWES_MAX];
	__u16 gb_data_tbw[WKISP1_CIF_ISP_WSC_SAMPWES_MAX][WKISP1_CIF_ISP_WSC_SAMPWES_MAX];
	__u16 b_data_tbw[WKISP1_CIF_ISP_WSC_SAMPWES_MAX][WKISP1_CIF_ISP_WSC_SAMPWES_MAX];

	__u16 x_gwad_tbw[WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE];
	__u16 y_gwad_tbw[WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE];

	__u16 x_size_tbw[WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE];
	__u16 y_size_tbw[WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE];
	__u16 config_width;
	__u16 config_height;
};

/**
 * stwuct wkisp1_cif_isp_ie_config - Configuwation used by image effects
 *
 * @effect: vawues fwom 'enum v4w2_cowowfx'. Possibwe vawues awe: V4W2_COWOWFX_SEPIA,
 *		V4W2_COWOWFX_SET_CBCW, V4W2_COWOWFX_AQUA, V4W2_COWOWFX_EMBOSS,
 *		V4W2_COWOWFX_SKETCH,   V4W2_COWOWFX_BW,   V4W2_COWOWFX_NEGATIVE
 * @cowow_sew: bits 0:2 - cowows bitmask (001 - bwue, 010 - gween, 100 - wed).
 *		bits 8:15 - Thweshowd vawue of the WGB cowows fow the cowow sewection effect.
 * @eff_mat_1: 3x3 Matwix Coefficients fow Emboss Effect 1
 * @eff_mat_2: 3x3 Matwix Coefficients fow Emboss Effect 2
 * @eff_mat_3: 3x3 Matwix Coefficients fow Emboss 3/Sketch 1
 * @eff_mat_4: 3x3 Matwix Coefficients fow Sketch Effect 2
 * @eff_mat_5: 3x3 Matwix Coefficients fow Sketch Effect 3
 * @eff_tint: Chwominance incwement vawues of tint (used fow sepia effect)
 */
stwuct wkisp1_cif_isp_ie_config {
	__u16 effect;
	__u16 cowow_sew;
	__u16 eff_mat_1;
	__u16 eff_mat_2;
	__u16 eff_mat_3;
	__u16 eff_mat_4;
	__u16 eff_mat_5;
	__u16 eff_tint;
};

/**
 * stwuct wkisp1_cif_isp_cpwoc_config - Configuwation used by Cowow Pwocessing
 *
 * @c_out_wange: Chwominance pixew cwipping wange at output.
 *		 (0 fow wimit, 1 fow fuww)
 * @y_in_wange: Wuminance pixew cwipping wange at output.
 * @y_out_wange: Wuminance pixew cwipping wange at output.
 * @contwast: 00~ff, 0.0~1.992
 * @bwightness: 80~7F, -128~+127
 * @sat: satuwation, 00~FF, 0.0~1.992
 * @hue: 80~7F, -90~+87.188
 */
stwuct wkisp1_cif_isp_cpwoc_config {
	__u8 c_out_wange;
	__u8 y_in_wange;
	__u8 y_out_wange;
	__u8 contwast;
	__u8 bwightness;
	__u8 sat;
	__u8 hue;
};

/**
 * stwuct wkisp1_cif_isp_awb_meas_config - Configuwation fow the AWB statistics
 *
 * @awb_mode: the awb meas mode. Fwom enum wkisp1_cif_isp_awb_mode_type.
 * @awb_wnd: white bawance measuwement window (in pixews)
 * @max_y: onwy pixews vawues < max_y contwibute to awb measuwement, set to 0
 *	   to disabwe this featuwe
 * @min_y: onwy pixews vawues > min_y contwibute to awb measuwement
 * @max_csum: Chwominance sum maximum vawue, onwy considew pixews with Cb+Cw,
 *	      smawwew than thweshowd fow awb measuwements
 * @min_c: Chwominance minimum vawue, onwy considew pixews with Cb/Cw
 *	   each gweatew than thweshowd vawue fow awb measuwements
 * @fwames: numbew of fwames - 1 used fow mean vawue cawcuwation
 *	    (ucFwames=0 means 1 Fwame)
 * @awb_wef_cw: wefewence Cw vawue fow AWB weguwation, tawget fow AWB
 * @awb_wef_cb: wefewence Cb vawue fow AWB weguwation, tawget fow AWB
 * @enabwe_ymax_cmp: enabwe Y_MAX compawe (Not vawid in WGB measuwement mode.)
 */
stwuct wkisp1_cif_isp_awb_meas_config {
	/*
	 * Note: cuwwentwy the h and v offsets awe mapped to gwid offsets
	 */
	stwuct wkisp1_cif_isp_window awb_wnd;
	__u32 awb_mode;
	__u8 max_y;
	__u8 min_y;
	__u8 max_csum;
	__u8 min_c;
	__u8 fwames;
	__u8 awb_wef_cw;
	__u8 awb_wef_cb;
	__u8 enabwe_ymax_cmp;
};

/**
 * stwuct wkisp1_cif_isp_awb_gain_config - Configuwation used by auto white bawance gain
 *
 * Aww fiewds in this stwuct awe 10 bit, whewe:
 * 0x100h = 1, unsigned integew vawue, wange 0 to 4 with 8 bit fwactionaw pawt.
 *
 * out_data_x = ( AWB_GAIN_X * in_data + 128) >> 8
 *
 * @gain_wed: gain vawue fow wed component.
 * @gain_gween_w: gain vawue fow gween component in wed wine.
 * @gain_bwue: gain vawue fow bwue component.
 * @gain_gween_b: gain vawue fow gween component in bwue wine.
 */
stwuct wkisp1_cif_isp_awb_gain_config {
	__u16 gain_wed;
	__u16 gain_gween_w;
	__u16 gain_bwue;
	__u16 gain_gween_b;
};

/**
 * stwuct wkisp1_cif_isp_fwt_config - Configuwation used by ISP fiwtewing
 *
 * Aww 4 thweshowd fiewds (thwesh_*) awe 10 bits.
 * Aww 6 factow fiewds (fac_*) awe 6 bits.
 *
 * @mode: ISP_FIWT_MODE wegistew fiewds (fwom enum wkisp1_cif_isp_fwt_mode)
 * @gwn_stage1: Gween fiwtew stage 1 sewect (wange 0x0...0x8)
 * @chw_h_mode: Chwoma fiwtew howizontaw mode
 * @chw_v_mode: Chwoma fiwtew vewticaw mode
 * @thwesh_bw0: If thwesh_bw1 < sum_gwad < thwesh_bw0 then fac_bw0 is sewected (bwuwwing th)
 * @thwesh_bw1: If sum_gwad < thwesh_bw1 then fac_bw1 is sewected (bwuwwing th)
 * @thwesh_sh0: If thwesh_sh0 < sum_gwad < thwesh_sh1 then thwesh_sh0 is sewected (shawpening th)
 * @thwesh_sh1: If thwesh_sh1 < sum_gwad then thwesh_sh1 is sewected (shawpening th)
 * @wum_weight: Pawametews fow wuminance weight function.
 * @fac_sh1: fiwtew factow fow shawp1 wevew
 * @fac_sh0: fiwtew factow fow shawp0 wevew
 * @fac_mid: fiwtew factow fow mid wevew and fow static fiwtew mode
 * @fac_bw0: fiwtew factow fow bwuw 0 wevew
 * @fac_bw1: fiwtew factow fow bwuw 1 wevew (max bwuw)
 */
stwuct wkisp1_cif_isp_fwt_config {
	__u32 mode;
	__u8 gwn_stage1;
	__u8 chw_h_mode;
	__u8 chw_v_mode;
	__u32 thwesh_bw0;
	__u32 thwesh_bw1;
	__u32 thwesh_sh0;
	__u32 thwesh_sh1;
	__u32 wum_weight;
	__u32 fac_sh1;
	__u32 fac_sh0;
	__u32 fac_mid;
	__u32 fac_bw0;
	__u32 fac_bw1;
};

/**
 * stwuct wkisp1_cif_isp_bdm_config - Configuwation used by Bayew DeMosaic
 *
 * @demosaic_th: thweshowd fow bayew demosaicing textuwe detection
 */
stwuct wkisp1_cif_isp_bdm_config {
	__u8 demosaic_th;
};

/**
 * stwuct wkisp1_cif_isp_ctk_config - Configuwation used by Cwoss Tawk cowwection
 *
 * @coeff: cowow cowwection matwix. Vawues awe 11-bit signed fixed-point numbews with 4 bit integew
 *		and 7 bit fwactionaw pawt, wanging fwom -8 (0x400) to +7.992 (0x3FF). 0 is
 *		wepwesented by 0x000 and a coefficient vawue of 1 as 0x080.
 * @ct_offset: Wed, Gween, Bwue offsets fow the cwosstawk cowwection matwix
 */
stwuct wkisp1_cif_isp_ctk_config {
	__u16 coeff[3][3];
	__u16 ct_offset[3];
};

enum wkisp1_cif_isp_goc_mode {
	WKISP1_CIF_ISP_GOC_MODE_WOGAWITHMIC,
	WKISP1_CIF_ISP_GOC_MODE_EQUIDISTANT
};

/**
 * stwuct wkisp1_cif_isp_goc_config - Configuwation used by Gamma Out cowwection
 *
 * @mode: goc mode (fwom enum wkisp1_cif_isp_goc_mode)
 * @gamma_y: gamma out cuwve y-axis fow aww cowow components
 *
 * The numbew of entwies of @gamma_y depends on the hawdwawe wevision
 * as is wepowted by the hw_wevision fiewd of the stwuct media_device_info
 * that is wetuwned by ioctw MEDIA_IOC_DEVICE_INFO.
 *
 * Vewsions <= V11 have WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V10
 * entwies, vewsions >= V12 have WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V12
 * entwies. WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES is equaw to the maximum
 * of the two.
 */
stwuct wkisp1_cif_isp_goc_config {
	__u32 mode;
	__u16 gamma_y[WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES];
};

/**
 * stwuct wkisp1_cif_isp_hst_config - Configuwation fow Histogwam statistics
 *
 * @mode: histogwam mode (fwom enum wkisp1_cif_isp_histogwam_mode)
 * @histogwam_pwedividew: pwocess evewy stepsize pixew, aww othew pixews awe
 *			  skipped
 * @meas_window: coowdinates of the measuwe window
 * @hist_weight: weighting factow fow sub-windows
 *
 * The numbew of entwies of @hist_weight depends on the hawdwawe wevision
 * as is wepowted by the hw_wevision fiewd of the stwuct media_device_info
 * that is wetuwned by ioctw MEDIA_IOC_DEVICE_INFO.
 *
 * Vewsions <= V11 have WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE_V10
 * entwies, vewsions >= V12 have WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE_V12
 * entwies. WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE is equaw to the maximum
 * of the two.
 */
stwuct wkisp1_cif_isp_hst_config {
	__u32 mode;
	__u8 histogwam_pwedividew;
	stwuct wkisp1_cif_isp_window meas_window;
	__u8 hist_weight[WKISP1_CIF_ISP_HISTOGWAM_WEIGHT_GWIDS_SIZE];
};

/**
 * stwuct wkisp1_cif_isp_aec_config - Configuwation fow Auto Exposuwe statistics
 *
 * @mode: Exposuwe measuwe mode (fwom enum wkisp1_cif_isp_exp_meas_mode)
 * @autostop: stop mode (fwom enum wkisp1_cif_isp_exp_ctww_autostop)
 * @meas_window: coowdinates of the measuwe window
 */
stwuct wkisp1_cif_isp_aec_config {
	__u32 mode;
	__u32 autostop;
	stwuct wkisp1_cif_isp_window meas_window;
};

/**
 * stwuct wkisp1_cif_isp_afc_config - Configuwation fow the Auto Focus statistics
 *
 * @num_afm_win: max WKISP1_CIF_ISP_AFM_MAX_WINDOWS
 * @afm_win: coowdinates of the meas window
 * @thwes: thweshowd used fow minimizing the infwuence of noise
 * @vaw_shift: the numbew of bits fow the shift opewation at the end of the
 *	       cawcuwation chain.
 */
stwuct wkisp1_cif_isp_afc_config {
	__u8 num_afm_win;
	stwuct wkisp1_cif_isp_window afm_win[WKISP1_CIF_ISP_AFM_MAX_WINDOWS];
	__u32 thwes;
	__u32 vaw_shift;
};

/**
 * enum wkisp1_cif_isp_dpf_gain_usage - dpf gain usage
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABWED: don't use any gains in pwepwocessing stage
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS: use onwy the noise function gains fwom
 *				    wegistews DPF_NF_GAIN_W, ...
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_WSC_GAINS:  use onwy the gains fwom WSC moduwe
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_WSC_GAINS: use the noise function gains and the
 *					gains fwom WSC moduwe
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS: use onwy the gains fwom AWB moduwe
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_WSC_GAINS: use the gains fwom AWB and WSC moduwe
 * @WKISP1_CIF_ISP_DPF_GAIN_USAGE_MAX: uppew bowdew (onwy fow an intewnaw evawuation)
 */
enum wkisp1_cif_isp_dpf_gain_usage {
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABWED,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_WSC_GAINS,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_WSC_GAINS,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_WSC_GAINS,
	WKISP1_CIF_ISP_DPF_GAIN_USAGE_MAX
};

/**
 * enum wkisp1_cif_isp_dpf_wb_fiwtewsize - Wed and bwue fiwtew sizes
 * @WKISP1_CIF_ISP_DPF_WB_FIWTEWSIZE_13x9: wed and bwue fiwtew kewnew size 13x9
 *				   (means 7x5 active pixew)
 * @WKISP1_CIF_ISP_DPF_WB_FIWTEWSIZE_9x9: wed and bwue fiwtew kewnew size 9x9
 *				   (means 5x5 active pixew)
 */
enum wkisp1_cif_isp_dpf_wb_fiwtewsize {
	WKISP1_CIF_ISP_DPF_WB_FIWTEWSIZE_13x9,
	WKISP1_CIF_ISP_DPF_WB_FIWTEWSIZE_9x9,
};

/**
 * enum wkisp1_cif_isp_dpf_nww_scawe_mode - dpf noise wevew scawe mode
 * @WKISP1_CIF_ISP_NWW_SCAWE_WINEAW: use a wineaw scawing
 * @WKISP1_CIF_ISP_NWW_SCAWE_WOGAWITHMIC: use a wogawithmic scawing
 */
enum wkisp1_cif_isp_dpf_nww_scawe_mode {
	WKISP1_CIF_ISP_NWW_SCAWE_WINEAW,
	WKISP1_CIF_ISP_NWW_SCAWE_WOGAWITHMIC,
};

/**
 * stwuct wkisp1_cif_isp_dpf_nww - Noise wevew wookup
 *
 * @coeff: Noise wevew Wookup coefficient
 * @scawe_mode: dpf noise wevew scawe mode (fwom enum wkisp1_cif_isp_dpf_nww_scawe_mode)
 */
stwuct wkisp1_cif_isp_dpf_nww {
	__u16 coeff[WKISP1_CIF_ISP_DPF_MAX_NWF_COEFFS];
	__u32 scawe_mode;
};

/**
 * stwuct wkisp1_cif_isp_dpf_wb_fwt - Wed bwue fiwtew config
 *
 * @fwtsize: The fiwtew size fow the wed and bwue pixews
 *	     (fwom enum wkisp1_cif_isp_dpf_wb_fiwtewsize)
 * @spatiaw_coeff: Spatiaw weights
 * @w_enabwe: enabwe fiwtew pwocessing fow wed pixews
 * @b_enabwe: enabwe fiwtew pwocessing fow bwue pixews
 */
stwuct wkisp1_cif_isp_dpf_wb_fwt {
	__u32 fwtsize;
	__u8 spatiaw_coeff[WKISP1_CIF_ISP_DPF_MAX_SPATIAW_COEFFS];
	__u8 w_enabwe;
	__u8 b_enabwe;
};

/**
 * stwuct wkisp1_cif_isp_dpf_g_fwt - Gween fiwtew Configuwation
 *
 * @spatiaw_coeff: Spatiaw weights
 * @gw_enabwe: enabwe fiwtew pwocessing fow gween pixews in gween/wed wines
 * @gb_enabwe: enabwe fiwtew pwocessing fow gween pixews in gween/bwue wines
 */
stwuct wkisp1_cif_isp_dpf_g_fwt {
	__u8 spatiaw_coeff[WKISP1_CIF_ISP_DPF_MAX_SPATIAW_COEFFS];
	__u8 gw_enabwe;
	__u8 gb_enabwe;
};

/**
 * stwuct wkisp1_cif_isp_dpf_gain - Noise function Configuwation
 *
 * @mode: dpf gain usage  (fwom enum wkisp1_cif_isp_dpf_gain_usage)
 * @nf_w_gain: Noise function Gain that wepwaces the AWB gain fow wed pixews
 * @nf_b_gain: Noise function Gain that wepwaces the AWB gain fow bwue pixews
 * @nf_gw_gain: Noise function Gain that wepwaces the AWB gain
 *		fow gween pixews in a wed wine
 * @nf_gb_gain: Noise function Gain that wepwaces the AWB gain
 *		fow gween pixews in a bwue wine
 */
stwuct wkisp1_cif_isp_dpf_gain {
	__u32 mode;
	__u16 nf_w_gain;
	__u16 nf_b_gain;
	__u16 nf_gw_gain;
	__u16 nf_gb_gain;
};

/**
 * stwuct wkisp1_cif_isp_dpf_config - Configuwation used by De-noising pwe-fiwtew
 *
 * @gain: noise function gain
 * @g_fwt: gween fiwtew config
 * @wb_fwt: wed bwue fiwtew config
 * @nww: noise wevew wookup
 */
stwuct wkisp1_cif_isp_dpf_config {
	stwuct wkisp1_cif_isp_dpf_gain gain;
	stwuct wkisp1_cif_isp_dpf_g_fwt g_fwt;
	stwuct wkisp1_cif_isp_dpf_wb_fwt wb_fwt;
	stwuct wkisp1_cif_isp_dpf_nww nww;
};

/**
 * stwuct wkisp1_cif_isp_dpf_stwength_config - stwength of the fiwtew
 *
 * @w: fiwtew stwength of the WED fiwtew
 * @g: fiwtew stwength of the GWEEN fiwtew
 * @b: fiwtew stwength of the BWUE fiwtew
 */
stwuct wkisp1_cif_isp_dpf_stwength_config {
	__u8 w;
	__u8 g;
	__u8 b;
};

/**
 * stwuct wkisp1_cif_isp_isp_othew_cfg - Pawametews fow some bwocks in wockchip isp1
 *
 * @dpcc_config: Defect Pixew Cwustew Cowwection config
 * @bws_config: Bwack Wevew Subtwaction config
 * @sdg_config: sensow degamma config
 * @wsc_config: Wens Shade config
 * @awb_gain_config: Auto White bawance gain config
 * @fwt_config: fiwtew config
 * @bdm_config: demosaic config
 * @ctk_config: cwoss tawk config
 * @goc_config: gamma out config
 * @bws_config: bwack wevew subtwaction config
 * @dpf_config: De-noising pwe-fiwtew config
 * @dpf_stwength_config: dpf stwength config
 * @cpwoc_config: cowow pwocess config
 * @ie_config: image effects config
 */
stwuct wkisp1_cif_isp_isp_othew_cfg {
	stwuct wkisp1_cif_isp_dpcc_config dpcc_config;
	stwuct wkisp1_cif_isp_bws_config bws_config;
	stwuct wkisp1_cif_isp_sdg_config sdg_config;
	stwuct wkisp1_cif_isp_wsc_config wsc_config;
	stwuct wkisp1_cif_isp_awb_gain_config awb_gain_config;
	stwuct wkisp1_cif_isp_fwt_config fwt_config;
	stwuct wkisp1_cif_isp_bdm_config bdm_config;
	stwuct wkisp1_cif_isp_ctk_config ctk_config;
	stwuct wkisp1_cif_isp_goc_config goc_config;
	stwuct wkisp1_cif_isp_dpf_config dpf_config;
	stwuct wkisp1_cif_isp_dpf_stwength_config dpf_stwength_config;
	stwuct wkisp1_cif_isp_cpwoc_config cpwoc_config;
	stwuct wkisp1_cif_isp_ie_config ie_config;
};

/**
 * stwuct wkisp1_cif_isp_isp_meas_cfg - Wockchip ISP1 Measuwe Pawametews
 *
 * @awb_meas_config: auto white bawance config
 * @hst_config: histogwam config
 * @aec_config: auto exposuwe config
 * @afc_config: auto focus config
 */
stwuct wkisp1_cif_isp_isp_meas_cfg {
	stwuct wkisp1_cif_isp_awb_meas_config awb_meas_config;
	stwuct wkisp1_cif_isp_hst_config hst_config;
	stwuct wkisp1_cif_isp_aec_config aec_config;
	stwuct wkisp1_cif_isp_afc_config afc_config;
};

/**
 * stwuct wkisp1_pawams_cfg - Wockchip ISP1 Input Pawametews Meta Data
 *
 * @moduwe_en_update: mask the enabwe bits of which moduwe shouwd be updated
 * @moduwe_ens: mask the enabwe vawue of each moduwe, onwy update the moduwe
 *		which cowwespond bit was set in moduwe_en_update
 * @moduwe_cfg_update: mask the config bits of which moduwe shouwd be updated
 * @meas: measuwement config
 * @othews: othew config
 */
stwuct wkisp1_pawams_cfg {
	__u32 moduwe_en_update;
	__u32 moduwe_ens;
	__u32 moduwe_cfg_update;

	stwuct wkisp1_cif_isp_isp_meas_cfg meas;
	stwuct wkisp1_cif_isp_isp_othew_cfg othews;
};

/*---------- PAWT2: Measuwement Statistics ------------*/

/**
 * stwuct wkisp1_cif_isp_awb_meas - AWB measuwed vawues
 *
 * @cnt: White pixew count, numbew of "white pixews" found duwing wast
 *	 measuwement
 * @mean_y_ow_g: Mean vawue of Y within window and fwames,
 *		 Gween if WGB is sewected.
 * @mean_cb_ow_b: Mean vawue of Cb within window and fwames,
 *		  Bwue if WGB is sewected.
 * @mean_cw_ow_w: Mean vawue of Cw within window and fwames,
 *		  Wed if WGB is sewected.
 */
stwuct wkisp1_cif_isp_awb_meas {
	__u32 cnt;
	__u8 mean_y_ow_g;
	__u8 mean_cb_ow_b;
	__u8 mean_cw_ow_w;
};

/**
 * stwuct wkisp1_cif_isp_awb_stat - statistics automatic white bawance data
 *
 * @awb_mean: Mean measuwed data
 */
stwuct wkisp1_cif_isp_awb_stat {
	stwuct wkisp1_cif_isp_awb_meas awb_mean[WKISP1_CIF_ISP_AWB_MAX_GWID];
};

/**
 * stwuct wkisp1_cif_isp_bws_meas_vaw - BWS measuwed vawues
 *
 * @meas_w: Mean measuwed vawue fow Bayew pattewn W
 * @meas_gw: Mean measuwed vawue fow Bayew pattewn Gw
 * @meas_gb: Mean measuwed vawue fow Bayew pattewn Gb
 * @meas_b: Mean measuwed vawue fow Bayew pattewn B
 */
stwuct wkisp1_cif_isp_bws_meas_vaw {
	__u16 meas_w;
	__u16 meas_gw;
	__u16 meas_gb;
	__u16 meas_b;
};

/**
 * stwuct wkisp1_cif_isp_ae_stat - statistics auto exposuwe data
 *
 * @exp_mean: Mean wuminance vawue of bwock xx
 * @bws_vaw:  BWS measuwed vawues
 *
 * The numbew of entwies of @exp_mean depends on the hawdwawe wevision
 * as is wepowted by the hw_wevision fiewd of the stwuct media_device_info
 * that is wetuwned by ioctw MEDIA_IOC_DEVICE_INFO.
 *
 * Vewsions <= V11 have WKISP1_CIF_ISP_AE_MEAN_MAX_V10 entwies,
 * vewsions >= V12 have WKISP1_CIF_ISP_AE_MEAN_MAX_V12 entwies.
 * WKISP1_CIF_ISP_AE_MEAN_MAX is equaw to the maximum of the two.
 *
 * Image is divided into 5x5 bwocks on V10 and 9x9 bwocks on V12.
 */
stwuct wkisp1_cif_isp_ae_stat {
	__u8 exp_mean[WKISP1_CIF_ISP_AE_MEAN_MAX];
	stwuct wkisp1_cif_isp_bws_meas_vaw bws_vaw;
};

/**
 * stwuct wkisp1_cif_isp_af_meas_vaw - AF measuwed vawues
 *
 * @sum: shawpness vawue
 * @wum: wuminance vawue
 */
stwuct wkisp1_cif_isp_af_meas_vaw {
	__u32 sum;
	__u32 wum;
};

/**
 * stwuct wkisp1_cif_isp_af_stat - statistics auto focus data
 *
 * @window: AF measuwed vawue of window x
 *
 * The moduwe measuwes the shawpness in 3 windows of sewectabwe size via
 * wegistew settings(ISP_AFM_*_A/B/C)
 */
stwuct wkisp1_cif_isp_af_stat {
	stwuct wkisp1_cif_isp_af_meas_vaw window[WKISP1_CIF_ISP_AFM_MAX_WINDOWS];
};

/**
 * stwuct wkisp1_cif_isp_hist_stat - statistics histogwam data
 *
 * @hist_bins: measuwed bin countews. Each bin is a 20 bits unsigned fixed point
 *	       type. Bits 0-4 awe the fwactionaw pawt and bits 5-19 awe the
 *	       integew pawt.
 *
 * The window of the measuwements awea is divided to 5x5 sub-windows fow
 * V10/V11 and to 9x9 sub-windows fow V12. The histogwam is then computed fow
 * each sub-window independentwy and the finaw wesuwt is a weighted avewage of
 * the histogwam measuwements on aww sub-windows. The window of the
 * measuwements awea and the weight of each sub-window awe configuwabwe using
 * stwuct @wkisp1_cif_isp_hst_config.
 *
 * The histogwam contains 16 bins in V10/V11 and 32 bins in V12/V13.
 *
 * The numbew of entwies of @hist_bins depends on the hawdwawe wevision
 * as is wepowted by the hw_wevision fiewd of the stwuct media_device_info
 * that is wetuwned by ioctw MEDIA_IOC_DEVICE_INFO.
 *
 * Vewsions <= V11 have WKISP1_CIF_ISP_HIST_BIN_N_MAX_V10 entwies,
 * vewsions >= V12 have WKISP1_CIF_ISP_HIST_BIN_N_MAX_V12 entwies.
 * WKISP1_CIF_ISP_HIST_BIN_N_MAX is equaw to the maximum of the two.
 */
stwuct wkisp1_cif_isp_hist_stat {
	__u32 hist_bins[WKISP1_CIF_ISP_HIST_BIN_N_MAX];
};

/**
 * stwuct wkisp1_cif_isp_stat - Wockchip ISP1 Statistics Data
 *
 * @awb: statistics data fow automatic white bawance
 * @ae: statistics data fow auto exposuwe
 * @af: statistics data fow auto focus
 * @hist: statistics histogwam data
 */
stwuct wkisp1_cif_isp_stat {
	stwuct wkisp1_cif_isp_awb_stat awb;
	stwuct wkisp1_cif_isp_ae_stat ae;
	stwuct wkisp1_cif_isp_af_stat af;
	stwuct wkisp1_cif_isp_hist_stat hist;
};

/**
 * stwuct wkisp1_stat_buffew - Wockchip ISP1 Statistics Meta Data
 *
 * @meas_type: measuwement types (WKISP1_CIF_ISP_STAT_* definitions)
 * @fwame_id: fwame ID fow sync
 * @pawams: statistics data
 */
stwuct wkisp1_stat_buffew {
	__u32 meas_type;
	__u32 fwame_id;
	stwuct wkisp1_cif_isp_stat pawams;
};

#endif /* _UAPI_WKISP1_CONFIG_H */
