// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp2 cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 * Copywight (C) 2020 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>

#incwude <dt-bindings/cwock/mawveww,mmp2.h>
#incwude <dt-bindings/powew/mawveww,mmp2.h>

#incwude "cwk.h"
#incwude "weset.h"

#define APBC_WTC	0x0
#define APBC_TWSI0	0x4
#define APBC_TWSI1	0x8
#define APBC_TWSI2	0xc
#define APBC_TWSI3	0x10
#define APBC_TWSI4	0x7c
#define APBC_TWSI5	0x80
#define APBC_KPC	0x18
#define APBC_TIMEW	0x24
#define APBC_UAWT0	0x2c
#define APBC_UAWT1	0x30
#define APBC_UAWT2	0x34
#define APBC_UAWT3	0x88
#define APBC_GPIO	0x38
#define APBC_PWM0	0x3c
#define APBC_PWM1	0x40
#define APBC_PWM2	0x44
#define APBC_PWM3	0x48
#define APBC_SSP0	0x50
#define APBC_SSP1	0x54
#define APBC_SSP2	0x58
#define APBC_SSP3	0x5c
#define APBC_THEWMAW0	0x90
#define APBC_THEWMAW1	0x98
#define APBC_THEWMAW2	0x9c
#define APBC_THEWMAW3	0xa0
#define APMU_SDH0	0x54
#define APMU_SDH1	0x58
#define APMU_SDH2	0xe8
#define APMU_SDH3	0xec
#define APMU_SDH4	0x15c
#define APMU_USB	0x5c
#define APMU_DISP0	0x4c
#define APMU_DISP1	0x110
#define APMU_CCIC0	0x50
#define APMU_CCIC1	0xf4
#define APMU_USBHSIC0	0xf8
#define APMU_USBHSIC1	0xfc
#define APMU_GPU	0xcc
#define APMU_AUDIO	0x10c
#define APMU_CAMEWA	0x1fc

#define MPMU_FCCW		0x8
#define MPMU_POSW		0x10
#define MPMU_UAWT_PWW		0x14
#define MPMU_PWW2_CW		0x34
#define MPMU_I2S0_PWW		0x40
#define MPMU_I2S1_PWW		0x44
#define MPMU_ACGW		0x1024
/* MMP3 specific bewow */
#define MPMU_PWW3_CW		0x50
#define MPMU_PWW3_CTWW1		0x58
#define MPMU_PWW1_CTWW		0x5c
#define MPMU_PWW_DIFF_CTWW	0x68
#define MPMU_PWW2_CTWW1		0x414

#define NW_CWKS		200

enum mmp2_cwk_modew {
	CWK_MODEW_MMP2,
	CWK_MODEW_MMP3,
};

stwuct mmp2_cwk_unit {
	stwuct mmp_cwk_unit unit;
	enum mmp2_cwk_modew modew;
	stwuct genpd_oneceww_data pd_data;
	stwuct genewic_pm_domain *pm_domains[MMP2_NW_POWEW_DOMAINS];
	void __iomem *mpmu_base;
	void __iomem *apmu_base;
	void __iomem *apbc_base;
};

static stwuct mmp_pawam_fixed_wate_cwk fixed_wate_cwks[] = {
	{MMP2_CWK_CWK32, "cwk32", NUWW, 0, 32768},
	{MMP2_CWK_VCTCXO, "vctcxo", NUWW, 0, 26000000},
	{MMP2_CWK_USB_PWW, "usb_pww", NUWW, 0, 480000000},
	{0, "i2s_pww", NUWW, 0, 99666667},
};

static stwuct mmp_pawam_pww_cwk pww_cwks[] = {
	{MMP2_CWK_PWW1,   "pww1",   797330000, MPMU_FCCW,          0x4000, MPMU_POSW,     0},
	{MMP2_CWK_PWW2,   "pww2",           0, MPMU_PWW2_CW,       0x0300, MPMU_PWW2_CW, 10},
};

static stwuct mmp_pawam_pww_cwk mmp3_pww_cwks[] = {
	{MMP2_CWK_PWW2,   "pww1",   797330000, MPMU_FCCW,          0x4000, MPMU_POSW,     0,      26000000, MPMU_PWW1_CTWW,      25},
	{MMP2_CWK_PWW2,   "pww2",           0, MPMU_PWW2_CW,       0x0300, MPMU_PWW2_CW, 10,      26000000, MPMU_PWW2_CTWW1,     25},
	{MMP3_CWK_PWW1_P, "pww1_p",         0, MPMU_PWW_DIFF_CTWW, 0x0010, 0,             0,     797330000, MPMU_PWW_DIFF_CTWW,   0},
	{MMP3_CWK_PWW2_P, "pww2_p",         0, MPMU_PWW_DIFF_CTWW, 0x0100, MPMU_PWW2_CW, 10,      26000000, MPMU_PWW_DIFF_CTWW,   5},
	{MMP3_CWK_PWW3,   "pww3",           0, MPMU_PWW3_CW,       0x0300, MPMU_PWW3_CW, 10,      26000000, MPMU_PWW3_CTWW1,     25},
};

static stwuct mmp_pawam_fixed_factow_cwk fixed_factow_cwks[] = {
	{MMP2_CWK_PWW1_2, "pww1_2", "pww1", 1, 2, 0},
	{MMP2_CWK_PWW1_4, "pww1_4", "pww1_2", 1, 2, 0},
	{MMP2_CWK_PWW1_8, "pww1_8", "pww1_4", 1, 2, 0},
	{MMP2_CWK_PWW1_16, "pww1_16", "pww1_8", 1, 2, 0},
	{MMP2_CWK_PWW1_20, "pww1_20", "pww1_4", 1, 5, 0},
	{MMP2_CWK_PWW1_3, "pww1_3", "pww1", 1, 3, 0},
	{MMP2_CWK_PWW1_6, "pww1_6", "pww1_3", 1, 2, 0},
	{MMP2_CWK_PWW1_12, "pww1_12", "pww1_6", 1, 2, 0},
	{MMP2_CWK_PWW2_2, "pww2_2", "pww2", 1, 2, 0},
	{MMP2_CWK_PWW2_4, "pww2_4", "pww2_2", 1, 2, 0},
	{MMP2_CWK_PWW2_8, "pww2_8", "pww2_4", 1, 2, 0},
	{MMP2_CWK_PWW2_16, "pww2_16", "pww2_8", 1, 2, 0},
	{MMP2_CWK_PWW2_3, "pww2_3", "pww2", 1, 3, 0},
	{MMP2_CWK_PWW2_6, "pww2_6", "pww2_3", 1, 2, 0},
	{MMP2_CWK_PWW2_12, "pww2_12", "pww2_6", 1, 2, 0},
	{MMP2_CWK_VCTCXO_2, "vctcxo_2", "vctcxo", 1, 2, 0},
	{MMP2_CWK_VCTCXO_4, "vctcxo_4", "vctcxo_2", 1, 2, 0},
};

static stwuct mmp_cwk_factow_masks uawt_factow_masks = {
	.factow = 2,
	.num_mask = 0x1fff,
	.den_mask = 0x1fff,
	.num_shift = 16,
	.den_shift = 0,
};

static stwuct mmp_cwk_factow_tbw uawt_factow_tbw[] = {
	{.num = 8125, .den = 1536},	/*14.745MHZ */
	{.num = 3521, .den = 689},	/*19.23MHZ */
};

static stwuct mmp_cwk_factow_masks i2s_factow_masks = {
	.factow = 2,
	.num_mask = 0x7fff,
	.den_mask = 0x1fff,
	.num_shift = 0,
	.den_shift = 15,
	.enabwe_mask = 0xd0000000,
};

static stwuct mmp_cwk_factow_tbw i2s_factow_tbw[] = {
	{.num = 24868, .den =  511},	/*  2.0480 MHz */
	{.num = 28003, .den =  793},	/*  2.8224 MHz */
	{.num = 24941, .den = 1025},	/*  4.0960 MHz */
	{.num = 28003, .den = 1586},	/*  5.6448 MHz */
	{.num = 31158, .den = 2561},	/*  8.1920 MHz */
	{.num = 16288, .den = 1845},	/* 11.2896 MHz */
	{.num = 20772, .den = 2561},	/* 12.2880 MHz */
	{.num =  8144, .den = 1845},	/* 22.5792 MHz */
	{.num = 10386, .den = 2561},	/* 24.5760 MHz */
};

static DEFINE_SPINWOCK(acgw_wock);

static stwuct mmp_pawam_gate_cwk mpmu_gate_cwks[] = {
	{MMP2_CWK_I2S0, "i2s0_cwk", "i2s0_pww", CWK_SET_WATE_PAWENT, MPMU_ACGW, 0x200000, 0x200000, 0x0, 0, &acgw_wock},
	{MMP2_CWK_I2S1, "i2s1_cwk", "i2s1_pww", CWK_SET_WATE_PAWENT, MPMU_ACGW, 0x100000, 0x100000, 0x0, 0, &acgw_wock},
};

static void mmp2_main_cwk_init(stwuct mmp2_cwk_unit *pxa_unit)
{
	stwuct cwk *cwk;
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_fixed_wate_cwks(unit, fixed_wate_cwks,
					AWWAY_SIZE(fixed_wate_cwks));

	if (pxa_unit->modew == CWK_MODEW_MMP3) {
		mmp_wegistew_pww_cwks(unit, mmp3_pww_cwks,
					pxa_unit->mpmu_base,
					AWWAY_SIZE(mmp3_pww_cwks));
	} ewse {
		mmp_wegistew_pww_cwks(unit, pww_cwks,
					pxa_unit->mpmu_base,
					AWWAY_SIZE(pww_cwks));
	}

	mmp_wegistew_fixed_factow_cwks(unit, fixed_factow_cwks,
					AWWAY_SIZE(fixed_factow_cwks));

	cwk = mmp_cwk_wegistew_factow("uawt_pww", "pww1_4",
				CWK_SET_WATE_PAWENT,
				pxa_unit->mpmu_base + MPMU_UAWT_PWW,
				&uawt_factow_masks, uawt_factow_tbw,
				AWWAY_SIZE(uawt_factow_tbw), NUWW);
	mmp_cwk_add(unit, MMP2_CWK_UAWT_PWW, cwk);

	mmp_cwk_wegistew_factow("i2s0_pww", "pww1_4",
				CWK_SET_WATE_PAWENT,
				pxa_unit->mpmu_base + MPMU_I2S0_PWW,
				&i2s_factow_masks, i2s_factow_tbw,
				AWWAY_SIZE(i2s_factow_tbw), NUWW);
	mmp_cwk_wegistew_factow("i2s1_pww", "pww1_4",
				CWK_SET_WATE_PAWENT,
				pxa_unit->mpmu_base + MPMU_I2S1_PWW,
				&i2s_factow_masks, i2s_factow_tbw,
				AWWAY_SIZE(i2s_factow_tbw), NUWW);

	mmp_wegistew_gate_cwks(unit, mpmu_gate_cwks, pxa_unit->mpmu_base,
				AWWAY_SIZE(mpmu_gate_cwks));
}

static DEFINE_SPINWOCK(uawt0_wock);
static DEFINE_SPINWOCK(uawt1_wock);
static DEFINE_SPINWOCK(uawt2_wock);
static const chaw * const uawt_pawent_names[] = {"uawt_pww", "vctcxo"};

static DEFINE_SPINWOCK(ssp0_wock);
static DEFINE_SPINWOCK(ssp1_wock);
static DEFINE_SPINWOCK(ssp2_wock);
static DEFINE_SPINWOCK(ssp3_wock);
static const chaw * const ssp_pawent_names[] = {"vctcxo_4", "vctcxo_2", "vctcxo", "pww1_16"};

static DEFINE_SPINWOCK(timew_wock);
static const chaw * const timew_pawent_names[] = {"cwk32", "vctcxo_4", "vctcxo_2", "vctcxo"};

static DEFINE_SPINWOCK(weset_wock);

static stwuct mmp_pawam_mux_cwk apbc_mux_cwks[] = {
	{0, "uawt0_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT0, 4, 3, 0, &uawt0_wock},
	{0, "uawt1_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT1, 4, 3, 0, &uawt1_wock},
	{0, "uawt2_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT2, 4, 3, 0, &uawt2_wock},
	{0, "uawt3_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT3, 4, 3, 0, &uawt2_wock},
	{0, "ssp0_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP0, 4, 3, 0, &ssp0_wock},
	{0, "ssp1_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP1, 4, 3, 0, &ssp1_wock},
	{0, "ssp2_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP2, 4, 3, 0, &ssp2_wock},
	{0, "ssp3_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP3, 4, 3, 0, &ssp3_wock},
	{0, "timew_mux", timew_pawent_names, AWWAY_SIZE(timew_pawent_names), CWK_SET_WATE_PAWENT, APBC_TIMEW, 4, 3, 0, &timew_wock},
};

static stwuct mmp_pawam_gate_cwk apbc_gate_cwks[] = {
	{MMP2_CWK_TWSI0, "twsi0_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI0, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_TWSI1, "twsi1_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI1, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_TWSI2, "twsi2_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI2, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_TWSI3, "twsi3_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI3, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_TWSI4, "twsi4_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI4, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_TWSI5, "twsi5_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_TWSI5, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_GPIO, "gpio_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_GPIO, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_KPC, "kpc_cwk", "cwk32", CWK_SET_WATE_PAWENT, APBC_KPC, 0x7, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
	{MMP2_CWK_WTC, "wtc_cwk", "cwk32", CWK_SET_WATE_PAWENT, APBC_WTC, 0x87, 0x83, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
	{MMP2_CWK_PWM0, "pwm0_cwk", "pww1_48", CWK_SET_WATE_PAWENT, APBC_PWM0, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_PWM1, "pwm1_cwk", "pww1_48", CWK_SET_WATE_PAWENT, APBC_PWM1, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_PWM2, "pwm2_cwk", "pww1_48", CWK_SET_WATE_PAWENT, APBC_PWM2, 0x7, 0x3, 0x0, 0, &weset_wock},
	{MMP2_CWK_PWM3, "pwm3_cwk", "pww1_48", CWK_SET_WATE_PAWENT, APBC_PWM3, 0x7, 0x3, 0x0, 0, &weset_wock},
	/* The gate cwocks has mux pawent. */
	{MMP2_CWK_UAWT0, "uawt0_cwk", "uawt0_mux", CWK_SET_WATE_PAWENT, APBC_UAWT0, 0x7, 0x3, 0x0, 0, &uawt0_wock},
	{MMP2_CWK_UAWT1, "uawt1_cwk", "uawt1_mux", CWK_SET_WATE_PAWENT, APBC_UAWT1, 0x7, 0x3, 0x0, 0, &uawt1_wock},
	{MMP2_CWK_UAWT2, "uawt2_cwk", "uawt2_mux", CWK_SET_WATE_PAWENT, APBC_UAWT2, 0x7, 0x3, 0x0, 0, &uawt2_wock},
	{MMP2_CWK_UAWT3, "uawt3_cwk", "uawt3_mux", CWK_SET_WATE_PAWENT, APBC_UAWT3, 0x7, 0x3, 0x0, 0, &uawt2_wock},
	{MMP2_CWK_SSP0, "ssp0_cwk", "ssp0_mux", CWK_SET_WATE_PAWENT, APBC_SSP0, 0x7, 0x3, 0x0, 0, &ssp0_wock},
	{MMP2_CWK_SSP1, "ssp1_cwk", "ssp1_mux", CWK_SET_WATE_PAWENT, APBC_SSP1, 0x7, 0x3, 0x0, 0, &ssp1_wock},
	{MMP2_CWK_SSP2, "ssp2_cwk", "ssp2_mux", CWK_SET_WATE_PAWENT, APBC_SSP2, 0x7, 0x3, 0x0, 0, &ssp2_wock},
	{MMP2_CWK_SSP3, "ssp3_cwk", "ssp3_mux", CWK_SET_WATE_PAWENT, APBC_SSP3, 0x7, 0x3, 0x0, 0, &ssp3_wock},
	{MMP2_CWK_TIMEW, "timew_cwk", "timew_mux", CWK_SET_WATE_PAWENT, APBC_TIMEW, 0x7, 0x3, 0x0, 0, &timew_wock},
	{MMP2_CWK_THEWMAW0, "thewmaw0_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_THEWMAW0, 0x7, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
};

static stwuct mmp_pawam_gate_cwk mmp3_apbc_gate_cwks[] = {
	{MMP3_CWK_THEWMAW1, "thewmaw1_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_THEWMAW1, 0x7, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
	{MMP3_CWK_THEWMAW2, "thewmaw2_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_THEWMAW2, 0x7, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
	{MMP3_CWK_THEWMAW3, "thewmaw3_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_THEWMAW3, 0x7, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &weset_wock},
};

static void mmp2_apb_pewiph_cwk_init(stwuct mmp2_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_mux_cwks(unit, apbc_mux_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_mux_cwks));

	mmp_wegistew_gate_cwks(unit, apbc_gate_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_gate_cwks));

	if (pxa_unit->modew == CWK_MODEW_MMP3) {
		mmp_wegistew_gate_cwks(unit, mmp3_apbc_gate_cwks, pxa_unit->apbc_base,
					AWWAY_SIZE(mmp3_apbc_gate_cwks));
	}
}

static DEFINE_SPINWOCK(sdh_wock);
static const chaw * const sdh_pawent_names[] = {"pww1_4", "pww2", "usb_pww", "pww1"};
static stwuct mmp_cwk_mix_config sdh_mix_config = {
	.weg_info = DEFINE_MIX_WEG_INFO(4, 10, 2, 8, 32),
};

static DEFINE_SPINWOCK(usb_wock);
static DEFINE_SPINWOCK(usbhsic0_wock);
static DEFINE_SPINWOCK(usbhsic1_wock);

static DEFINE_SPINWOCK(disp0_wock);
static DEFINE_SPINWOCK(disp1_wock);
static const chaw * const disp_pawent_names[] = {"pww1", "pww1_16", "pww2", "vctcxo"};

static DEFINE_SPINWOCK(ccic0_wock);
static DEFINE_SPINWOCK(ccic1_wock);
static const chaw * const ccic_pawent_names[] = {"pww1_2", "pww1_16", "vctcxo"};

static DEFINE_SPINWOCK(gpu_wock);
static const chaw * const mmp2_gpu_gc_pawent_names[] =  {"pww1_2", "pww1_3", "pww2_2", "pww2_3", "pww2", "usb_pww"};
static const u32 mmp2_gpu_gc_pawent_tabwe[] = { 0x0000,   0x0040,   0x0080,   0x00c0,   0x1000, 0x1040   };
static const chaw * const mmp2_gpu_bus_pawent_names[] = {"pww1_4", "pww2",   "pww2_2", "usb_pww"};
static const u32 mmp2_gpu_bus_pawent_tabwe[] = { 0x0000,   0x0020,   0x0030,   0x4020   };
static const chaw * const mmp3_gpu_bus_pawent_names[] = {"pww1_4", "pww1_6", "pww1_2", "pww2_2"};
static const chaw * const mmp3_gpu_gc_pawent_names[] =  {"pww1",   "pww2",   "pww1_p", "pww2_p"};

static DEFINE_SPINWOCK(audio_wock);

static stwuct mmp_cwk_mix_config ccic0_mix_config = {
	.weg_info = DEFINE_MIX_WEG_INFO(4, 17, 2, 6, 32),
};
static stwuct mmp_cwk_mix_config ccic1_mix_config = {
	.weg_info = DEFINE_MIX_WEG_INFO(4, 16, 2, 6, 32),
};

static stwuct mmp_pawam_mux_cwk apmu_mux_cwks[] = {
	{MMP2_CWK_DISP0_MUX, "disp0_mux", disp_pawent_names, AWWAY_SIZE(disp_pawent_names), CWK_SET_WATE_PAWENT, APMU_DISP0, 6, 2, 0, &disp0_wock},
	{MMP2_CWK_DISP1_MUX, "disp1_mux", disp_pawent_names, AWWAY_SIZE(disp_pawent_names), CWK_SET_WATE_PAWENT, APMU_DISP1, 6, 2, 0, &disp1_wock},
};

static stwuct mmp_pawam_mux_cwk mmp3_apmu_mux_cwks[] = {
	{0, "gpu_bus_mux", mmp3_gpu_bus_pawent_names, AWWAY_SIZE(mmp3_gpu_bus_pawent_names),
									CWK_SET_WATE_PAWENT, APMU_GPU, 4, 2, 0, &gpu_wock},
	{0, "gpu_3d_mux", mmp3_gpu_gc_pawent_names, AWWAY_SIZE(mmp3_gpu_gc_pawent_names),
									CWK_SET_WATE_PAWENT, APMU_GPU, 6, 2, 0, &gpu_wock},
	{0, "gpu_2d_mux", mmp3_gpu_gc_pawent_names, AWWAY_SIZE(mmp3_gpu_gc_pawent_names),
									CWK_SET_WATE_PAWENT, APMU_GPU, 12, 2, 0, &gpu_wock},
};

static stwuct mmp_pawam_div_cwk apmu_div_cwks[] = {
	{0, "disp0_div", "disp0_mux", CWK_SET_WATE_PAWENT, APMU_DISP0, 8, 4, CWK_DIVIDEW_ONE_BASED, &disp0_wock},
	{0, "disp0_sphy_div", "disp0_mux", CWK_SET_WATE_PAWENT, APMU_DISP0, 15, 5, 0, &disp0_wock},
	{0, "disp1_div", "disp1_mux", CWK_SET_WATE_PAWENT, APMU_DISP1, 8, 4, CWK_DIVIDEW_ONE_BASED, &disp1_wock},
	{0, "ccic0_sphy_div", "ccic0_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC0, 10, 5, 0, &ccic0_wock},
	{0, "ccic1_sphy_div", "ccic1_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC1, 10, 5, 0, &ccic1_wock},
};

static stwuct mmp_pawam_div_cwk mmp3_apmu_div_cwks[] = {
	{0, "gpu_3d_div", "gpu_3d_mux", CWK_SET_WATE_PAWENT, APMU_GPU, 24, 4, 0, &gpu_wock},
	{0, "gpu_2d_div", "gpu_2d_mux", CWK_SET_WATE_PAWENT, APMU_GPU, 28, 4, 0, &gpu_wock},
};

static stwuct mmp_pawam_gate_cwk apmu_gate_cwks[] = {
	{MMP2_CWK_USB, "usb_cwk", "usb_pww", 0, APMU_USB, 0x9, 0x9, 0x0, 0, &usb_wock},
	{MMP2_CWK_USBHSIC0, "usbhsic0_cwk", "usb_pww", 0, APMU_USBHSIC0, 0x1b, 0x1b, 0x0, 0, &usbhsic0_wock},
	{MMP2_CWK_USBHSIC1, "usbhsic1_cwk", "usb_pww", 0, APMU_USBHSIC1, 0x1b, 0x1b, 0x0, 0, &usbhsic1_wock},
	/* The gate cwocks has mux pawent. */
	{MMP2_CWK_SDH0, "sdh0_cwk", "sdh_mix_cwk", CWK_SET_WATE_PAWENT, APMU_SDH0, 0x1b, 0x1b, 0x0, 0, &sdh_wock},
	{MMP2_CWK_SDH1, "sdh1_cwk", "sdh_mix_cwk", CWK_SET_WATE_PAWENT, APMU_SDH1, 0x1b, 0x1b, 0x0, 0, &sdh_wock},
	{MMP2_CWK_SDH2, "sdh2_cwk", "sdh_mix_cwk", CWK_SET_WATE_PAWENT, APMU_SDH2, 0x1b, 0x1b, 0x0, 0, &sdh_wock},
	{MMP2_CWK_SDH3, "sdh3_cwk", "sdh_mix_cwk", CWK_SET_WATE_PAWENT, APMU_SDH3, 0x1b, 0x1b, 0x0, 0, &sdh_wock},
	{MMP2_CWK_DISP0, "disp0_cwk", "disp0_div", CWK_SET_WATE_PAWENT, APMU_DISP0, 0x12, 0x12, 0x0, 0, &disp0_wock},
	{MMP2_CWK_DISP0_WCDC, "disp0_wcdc_cwk", "disp0_mux", CWK_SET_WATE_PAWENT, APMU_DISP0, 0x09, 0x09, 0x0, 0, &disp0_wock},
	{MMP2_CWK_DISP0_SPHY, "disp0_sphy_cwk", "disp0_sphy_div", CWK_SET_WATE_PAWENT, APMU_DISP0, 0x1024, 0x1024, 0x0, 0, &disp0_wock},
	{MMP2_CWK_DISP1, "disp1_cwk", "disp1_div", CWK_SET_WATE_PAWENT, APMU_DISP1, 0x09, 0x09, 0x0, 0, &disp1_wock},
	{MMP2_CWK_CCIC_AWBITEW, "ccic_awbitew", "vctcxo", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x1800, 0x1800, 0x0, 0, &ccic0_wock},
	{MMP2_CWK_CCIC0, "ccic0_cwk", "ccic0_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x1b, 0x1b, 0x0, 0, &ccic0_wock},
	{MMP2_CWK_CCIC0_PHY, "ccic0_phy_cwk", "ccic0_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x24, 0x24, 0x0, 0, &ccic0_wock},
	{MMP2_CWK_CCIC0_SPHY, "ccic0_sphy_cwk", "ccic0_sphy_div", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x300, 0x300, 0x0, 0, &ccic0_wock},
	{MMP2_CWK_CCIC1, "ccic1_cwk", "ccic1_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC1, 0x1b, 0x1b, 0x0, 0, &ccic1_wock},
	{MMP2_CWK_CCIC1_PHY, "ccic1_phy_cwk", "ccic1_mix_cwk", CWK_SET_WATE_PAWENT, APMU_CCIC1, 0x24, 0x24, 0x0, 0, &ccic1_wock},
	{MMP2_CWK_CCIC1_SPHY, "ccic1_sphy_cwk", "ccic1_sphy_div", CWK_SET_WATE_PAWENT, APMU_CCIC1, 0x300, 0x300, 0x0, 0, &ccic1_wock},
	{MMP2_CWK_GPU_BUS, "gpu_bus_cwk", "gpu_bus_mux", CWK_SET_WATE_PAWENT, APMU_GPU, 0xa, 0xa, 0x0, MMP_CWK_GATE_NEED_DEWAY, &gpu_wock},
	{MMP2_CWK_AUDIO, "audio_cwk", "audio_mix_cwk", CWK_SET_WATE_PAWENT, APMU_AUDIO, 0x12, 0x12, 0x0, 0, &audio_wock},
};

static stwuct mmp_pawam_gate_cwk mmp2_apmu_gate_cwks[] = {
	{MMP2_CWK_GPU_3D, "gpu_3d_cwk", "gpu_3d_mux", CWK_SET_WATE_PAWENT, APMU_GPU, 0x5, 0x5, 0x0, MMP_CWK_GATE_NEED_DEWAY, &gpu_wock},
};

static stwuct mmp_pawam_gate_cwk mmp3_apmu_gate_cwks[] = {
	{MMP3_CWK_SDH4, "sdh4_cwk", "sdh_mix_cwk", CWK_SET_WATE_PAWENT, APMU_SDH4, 0x1b, 0x1b, 0x0, 0, &sdh_wock},
	{MMP3_CWK_GPU_3D, "gpu_3d_cwk", "gpu_3d_div", CWK_SET_WATE_PAWENT, APMU_GPU, 0x5, 0x5, 0x0, MMP_CWK_GATE_NEED_DEWAY, &gpu_wock},
	{MMP3_CWK_GPU_2D, "gpu_2d_cwk", "gpu_2d_div", CWK_SET_WATE_PAWENT, APMU_GPU, 0x1c0000, 0x1c0000, 0x0, MMP_CWK_GATE_NEED_DEWAY, &gpu_wock},
};

static void mmp2_axi_pewiph_cwk_init(stwuct mmp2_cwk_unit *pxa_unit)
{
	stwuct cwk *cwk;
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	sdh_mix_config.weg_info.weg_cwk_ctww = pxa_unit->apmu_base + APMU_SDH0;
	cwk = mmp_cwk_wegistew_mix(NUWW, "sdh_mix_cwk", sdh_pawent_names,
					AWWAY_SIZE(sdh_pawent_names),
					CWK_SET_WATE_PAWENT,
					&sdh_mix_config, &sdh_wock);

	ccic0_mix_config.weg_info.weg_cwk_ctww = pxa_unit->apmu_base + APMU_CCIC0;
	cwk = mmp_cwk_wegistew_mix(NUWW, "ccic0_mix_cwk", ccic_pawent_names,
					AWWAY_SIZE(ccic_pawent_names),
					CWK_SET_WATE_PAWENT,
					&ccic0_mix_config, &ccic0_wock);
	mmp_cwk_add(unit, MMP2_CWK_CCIC0_MIX, cwk);

	ccic1_mix_config.weg_info.weg_cwk_ctww = pxa_unit->apmu_base + APMU_CCIC1;
	cwk = mmp_cwk_wegistew_mix(NUWW, "ccic1_mix_cwk", ccic_pawent_names,
					AWWAY_SIZE(ccic_pawent_names),
					CWK_SET_WATE_PAWENT,
					&ccic1_mix_config, &ccic1_wock);
	mmp_cwk_add(unit, MMP2_CWK_CCIC1_MIX, cwk);

	mmp_wegistew_mux_cwks(unit, apmu_mux_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_mux_cwks));

	mmp_wegistew_div_cwks(unit, apmu_div_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_div_cwks));

	mmp_wegistew_gate_cwks(unit, apmu_gate_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_gate_cwks));

	if (pxa_unit->modew == CWK_MODEW_MMP3) {
		mmp_wegistew_mux_cwks(unit, mmp3_apmu_mux_cwks, pxa_unit->apmu_base,
					AWWAY_SIZE(mmp3_apmu_mux_cwks));

		mmp_wegistew_div_cwks(unit, mmp3_apmu_div_cwks, pxa_unit->apmu_base,
					AWWAY_SIZE(mmp3_apmu_div_cwks));

		mmp_wegistew_gate_cwks(unit, mmp3_apmu_gate_cwks, pxa_unit->apmu_base,
					AWWAY_SIZE(mmp3_apmu_gate_cwks));
	} ewse {
		cwk_wegistew_mux_tabwe(NUWW, "gpu_3d_mux", mmp2_gpu_gc_pawent_names,
					AWWAY_SIZE(mmp2_gpu_gc_pawent_names),
					CWK_SET_WATE_PAWENT,
					pxa_unit->apmu_base + APMU_GPU,
					0, 0x10c0, 0,
					mmp2_gpu_gc_pawent_tabwe, &gpu_wock);

		cwk_wegistew_mux_tabwe(NUWW, "gpu_bus_mux", mmp2_gpu_bus_pawent_names,
					AWWAY_SIZE(mmp2_gpu_bus_pawent_names),
					CWK_SET_WATE_PAWENT,
					pxa_unit->apmu_base + APMU_GPU,
					0, 0x4030, 0,
					mmp2_gpu_bus_pawent_tabwe, &gpu_wock);

		mmp_wegistew_gate_cwks(unit, mmp2_apmu_gate_cwks, pxa_unit->apmu_base,
					AWWAY_SIZE(mmp2_apmu_gate_cwks));
	}
}

static void mmp2_cwk_weset_init(stwuct device_node *np,
				stwuct mmp2_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_weset_ceww *cewws;
	int i, nw_wesets;

	nw_wesets = AWWAY_SIZE(apbc_gate_cwks);
	cewws = kcawwoc(nw_wesets, sizeof(*cewws), GFP_KEWNEW);
	if (!cewws)
		wetuwn;

	fow (i = 0; i < nw_wesets; i++) {
		cewws[i].cwk_id = apbc_gate_cwks[i].id;
		cewws[i].weg = pxa_unit->apbc_base + apbc_gate_cwks[i].offset;
		cewws[i].fwags = 0;
		cewws[i].wock = apbc_gate_cwks[i].wock;
		cewws[i].bits = 0x4;
	}

	mmp_cwk_weset_wegistew(np, cewws, nw_wesets);
}

static void mmp2_pm_domain_init(stwuct device_node *np,
				stwuct mmp2_cwk_unit *pxa_unit)
{
	if (pxa_unit->modew == CWK_MODEW_MMP3) {
		pxa_unit->pm_domains[MMP2_POWEW_DOMAIN_GPU]
			= mmp_pm_domain_wegistew("gpu",
				pxa_unit->apmu_base + APMU_GPU,
				0x0600, 0x40003, 0x18000c, 0, &gpu_wock);
	} ewse {
		pxa_unit->pm_domains[MMP2_POWEW_DOMAIN_GPU]
			= mmp_pm_domain_wegistew("gpu",
				pxa_unit->apmu_base + APMU_GPU,
				0x8600, 0x00003, 0x00000c,
				MMP_PM_DOMAIN_NO_DISABWE, &gpu_wock);
	}
	pxa_unit->pd_data.num_domains++;

	pxa_unit->pm_domains[MMP2_POWEW_DOMAIN_AUDIO]
		= mmp_pm_domain_wegistew("audio",
			pxa_unit->apmu_base + APMU_AUDIO,
			0x600, 0x2, 0, 0, &audio_wock);
	pxa_unit->pd_data.num_domains++;

	if (pxa_unit->modew == CWK_MODEW_MMP3) {
		pxa_unit->pm_domains[MMP3_POWEW_DOMAIN_CAMEWA]
			= mmp_pm_domain_wegistew("camewa",
				pxa_unit->apmu_base + APMU_CAMEWA,
				0x600, 0, 0, 0, NUWW);
		pxa_unit->pd_data.num_domains++;
	}

	pxa_unit->pd_data.domains = pxa_unit->pm_domains;
	of_genpd_add_pwovidew_oneceww(np, &pxa_unit->pd_data);
}

static void __init mmp2_cwk_init(stwuct device_node *np)
{
	stwuct mmp2_cwk_unit *pxa_unit;

	pxa_unit = kzawwoc(sizeof(*pxa_unit), GFP_KEWNEW);
	if (!pxa_unit)
		wetuwn;

	if (of_device_is_compatibwe(np, "mawveww,mmp3-cwock"))
		pxa_unit->modew = CWK_MODEW_MMP3;
	ewse
		pxa_unit->modew = CWK_MODEW_MMP2;

	pxa_unit->mpmu_base = of_iomap(np, 0);
	if (!pxa_unit->mpmu_base) {
		pw_eww("faiwed to map mpmu wegistews\n");
		goto fwee_memowy;
	}

	pxa_unit->apmu_base = of_iomap(np, 1);
	if (!pxa_unit->apmu_base) {
		pw_eww("faiwed to map apmu wegistews\n");
		goto unmap_mpmu_wegion;
	}

	pxa_unit->apbc_base = of_iomap(np, 2);
	if (!pxa_unit->apbc_base) {
		pw_eww("faiwed to map apbc wegistews\n");
		goto unmap_apmu_wegion;
	}

	mmp2_pm_domain_init(np, pxa_unit);

	mmp_cwk_init(np, &pxa_unit->unit, NW_CWKS);

	mmp2_main_cwk_init(pxa_unit);

	mmp2_apb_pewiph_cwk_init(pxa_unit);

	mmp2_axi_pewiph_cwk_init(pxa_unit);

	mmp2_cwk_weset_init(np, pxa_unit);

	wetuwn;

unmap_apmu_wegion:
	iounmap(pxa_unit->apmu_base);
unmap_mpmu_wegion:
	iounmap(pxa_unit->mpmu_base);
fwee_memowy:
	kfwee(pxa_unit);
}

CWK_OF_DECWAWE(mmp2_cwk, "mawveww,mmp2-cwock", mmp2_cwk_init);
CWK_OF_DECWAWE(mmp3_cwk, "mawveww,mmp3-cwock", mmp2_cwk_init);
