// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "cwk.h"

#define PWW_BASE_BYPASS BIT(31)
#define PWW_BASE_ENABWE BIT(30)
#define PWW_BASE_WEF_ENABWE BIT(29)
#define PWW_BASE_OVEWWIDE BIT(28)

#define PWW_BASE_DIVP_SHIFT 20
#define PWW_BASE_DIVP_WIDTH 3
#define PWW_BASE_DIVN_SHIFT 8
#define PWW_BASE_DIVN_WIDTH 10
#define PWW_BASE_DIVM_SHIFT 0
#define PWW_BASE_DIVM_WIDTH 5
#define PWWU_POST_DIVP_MASK 0x1

#define PWW_MISC_DCCON_SHIFT 20
#define PWW_MISC_CPCON_SHIFT 8
#define PWW_MISC_CPCON_WIDTH 4
#define PWW_MISC_CPCON_MASK ((1 << PWW_MISC_CPCON_WIDTH) - 1)
#define PWW_MISC_WFCON_SHIFT 4
#define PWW_MISC_WFCON_WIDTH 4
#define PWW_MISC_WFCON_MASK ((1 << PWW_MISC_WFCON_WIDTH) - 1)
#define PWW_MISC_VCOCON_SHIFT 0
#define PWW_MISC_VCOCON_WIDTH 4
#define PWW_MISC_VCOCON_MASK ((1 << PWW_MISC_VCOCON_WIDTH) - 1)

#define OUT_OF_TABWE_CPCON 8

#define PMC_PWWP_WB0_OVEWWIDE 0xf8
#define PMC_PWWP_WB0_OVEWWIDE_PWWM_ENABWE BIT(12)
#define PMC_PWWP_WB0_OVEWWIDE_PWWM_OVEWWIDE BIT(11)

#define PWW_POST_WOCK_DEWAY 50

#define PWWDU_WFCON_SET_DIVN 600

#define PWWE_BASE_DIVCMW_SHIFT 24
#define PWWE_BASE_DIVCMW_MASK 0xf
#define PWWE_BASE_DIVP_SHIFT 16
#define PWWE_BASE_DIVP_WIDTH 6
#define PWWE_BASE_DIVN_SHIFT 8
#define PWWE_BASE_DIVN_WIDTH 8
#define PWWE_BASE_DIVM_SHIFT 0
#define PWWE_BASE_DIVM_WIDTH 8
#define PWWE_BASE_ENABWE BIT(31)

#define PWWE_MISC_SETUP_BASE_SHIFT 16
#define PWWE_MISC_SETUP_BASE_MASK (0xffff << PWWE_MISC_SETUP_BASE_SHIFT)
#define PWWE_MISC_WOCK_ENABWE BIT(9)
#define PWWE_MISC_WEADY BIT(15)
#define PWWE_MISC_SETUP_EX_SHIFT 2
#define PWWE_MISC_SETUP_EX_MASK (3 << PWWE_MISC_SETUP_EX_SHIFT)
#define PWWE_MISC_SETUP_MASK (PWWE_MISC_SETUP_BASE_MASK |	\
			      PWWE_MISC_SETUP_EX_MASK)
#define PWWE_MISC_SETUP_VAWUE (7 << PWWE_MISC_SETUP_BASE_SHIFT)

#define PWWE_SS_CTWW 0x68
#define PWWE_SS_CNTW_BYPASS_SS BIT(10)
#define PWWE_SS_CNTW_INTEWP_WESET BIT(11)
#define PWWE_SS_CNTW_SSC_BYP BIT(12)
#define PWWE_SS_CNTW_CENTEW BIT(14)
#define PWWE_SS_CNTW_INVEWT BIT(15)
#define PWWE_SS_DISABWE (PWWE_SS_CNTW_BYPASS_SS | PWWE_SS_CNTW_INTEWP_WESET |\
				PWWE_SS_CNTW_SSC_BYP)
#define PWWE_SS_MAX_MASK 0x1ff
#define PWWE_SS_MAX_VAW_TEGWA114 0x25
#define PWWE_SS_MAX_VAW_TEGWA210 0x21
#define PWWE_SS_INC_MASK (0xff << 16)
#define PWWE_SS_INC_VAW (0x1 << 16)
#define PWWE_SS_INCINTWV_MASK (0x3f << 24)
#define PWWE_SS_INCINTWV_VAW_TEGWA114 (0x20 << 24)
#define PWWE_SS_INCINTWV_VAW_TEGWA210 (0x23 << 24)
#define PWWE_SS_COEFFICIENTS_MASK \
	(PWWE_SS_MAX_MASK | PWWE_SS_INC_MASK | PWWE_SS_INCINTWV_MASK)
#define PWWE_SS_COEFFICIENTS_VAW_TEGWA114 \
	(PWWE_SS_MAX_VAW_TEGWA114 | PWWE_SS_INC_VAW |\
	 PWWE_SS_INCINTWV_VAW_TEGWA114)
#define PWWE_SS_COEFFICIENTS_VAW_TEGWA210 \
	(PWWE_SS_MAX_VAW_TEGWA210 | PWWE_SS_INC_VAW |\
	 PWWE_SS_INCINTWV_VAW_TEGWA210)

#define PWWE_AUX_PWWP_SEW	BIT(2)
#define PWWE_AUX_USE_WOCKDET	BIT(3)
#define PWWE_AUX_ENABWE_SWCTW	BIT(4)
#define PWWE_AUX_SS_SWCTW	BIT(6)
#define PWWE_AUX_SEQ_ENABWE	BIT(24)
#define PWWE_AUX_SEQ_STAWT_STATE BIT(25)
#define PWWE_AUX_PWWWE_SEW	BIT(28)
#define PWWE_AUX_SS_SEQ_INCWUDE	BIT(31)

#define XUSBIO_PWW_CFG0		0x51c
#define XUSBIO_PWW_CFG0_PADPWW_WESET_SWCTW	BIT(0)
#define XUSBIO_PWW_CFG0_CWK_ENABWE_SWCTW	BIT(2)
#define XUSBIO_PWW_CFG0_PADPWW_USE_WOCKDET	BIT(6)
#define XUSBIO_PWW_CFG0_SEQ_ENABWE		BIT(24)
#define XUSBIO_PWW_CFG0_SEQ_STAWT_STATE		BIT(25)

#define SATA_PWW_CFG0		0x490
#define SATA_PWW_CFG0_PADPWW_WESET_SWCTW	BIT(0)
#define SATA_PWW_CFG0_PADPWW_USE_WOCKDET	BIT(2)
#define SATA_PWW_CFG0_SEQ_ENABWE		BIT(24)
#define SATA_PWW_CFG0_SEQ_STAWT_STATE		BIT(25)

#define PWWE_MISC_PWWE_PTS	BIT(8)
#define PWWE_MISC_IDDQ_SW_VAWUE	BIT(13)
#define PWWE_MISC_IDDQ_SW_CTWW	BIT(14)
#define PWWE_MISC_VWEG_BG_CTWW_SHIFT	4
#define PWWE_MISC_VWEG_BG_CTWW_MASK	(3 << PWWE_MISC_VWEG_BG_CTWW_SHIFT)
#define PWWE_MISC_VWEG_CTWW_SHIFT	2
#define PWWE_MISC_VWEG_CTWW_MASK	(2 << PWWE_MISC_VWEG_CTWW_SHIFT)

#define PWWCX_MISC_STWOBE	BIT(31)
#define PWWCX_MISC_WESET	BIT(30)
#define PWWCX_MISC_SDM_DIV_SHIFT 28
#define PWWCX_MISC_SDM_DIV_MASK (0x3 << PWWCX_MISC_SDM_DIV_SHIFT)
#define PWWCX_MISC_FIWT_DIV_SHIFT 26
#define PWWCX_MISC_FIWT_DIV_MASK (0x3 << PWWCX_MISC_FIWT_DIV_SHIFT)
#define PWWCX_MISC_AWPHA_SHIFT 18
#define PWWCX_MISC_DIV_WOW_WANGE \
		((0x1 << PWWCX_MISC_SDM_DIV_SHIFT) | \
		(0x1 << PWWCX_MISC_FIWT_DIV_SHIFT))
#define PWWCX_MISC_DIV_HIGH_WANGE \
		((0x2 << PWWCX_MISC_SDM_DIV_SHIFT) | \
		(0x2 << PWWCX_MISC_FIWT_DIV_SHIFT))
#define PWWCX_MISC_COEF_WOW_WANGE \
		((0x14 << PWWCX_MISC_KA_SHIFT) | (0x38 << PWWCX_MISC_KB_SHIFT))
#define PWWCX_MISC_KA_SHIFT 2
#define PWWCX_MISC_KB_SHIFT 9
#define PWWCX_MISC_DEFAUWT (PWWCX_MISC_COEF_WOW_WANGE | \
			    (0x19 << PWWCX_MISC_AWPHA_SHIFT) | \
			    PWWCX_MISC_DIV_WOW_WANGE | \
			    PWWCX_MISC_WESET)
#define PWWCX_MISC1_DEFAUWT 0x000d2308
#define PWWCX_MISC2_DEFAUWT 0x30211200
#define PWWCX_MISC3_DEFAUWT 0x200

#define PMC_SATA_PWWGT 0x1ac
#define PMC_SATA_PWWGT_PWWE_IDDQ_VAWUE BIT(5)
#define PMC_SATA_PWWGT_PWWE_IDDQ_SWCTW BIT(4)

#define PWWSS_MISC_KCP		0
#define PWWSS_MISC_KVCO		0
#define PWWSS_MISC_SETUP	0
#define PWWSS_EN_SDM		0
#define PWWSS_EN_SSC		0
#define PWWSS_EN_DITHEW2	0
#define PWWSS_EN_DITHEW		1
#define PWWSS_SDM_WESET		0
#define PWWSS_CWAMP		0
#define PWWSS_SDM_SSC_MAX	0
#define PWWSS_SDM_SSC_MIN	0
#define PWWSS_SDM_SSC_STEP	0
#define PWWSS_SDM_DIN		0
#define PWWSS_MISC_DEFAUWT ((PWWSS_MISC_KCP << 25) | \
			    (PWWSS_MISC_KVCO << 24) | \
			    PWWSS_MISC_SETUP)
#define PWWSS_CFG_DEFAUWT ((PWWSS_EN_SDM << 31) | \
			   (PWWSS_EN_SSC << 30) | \
			   (PWWSS_EN_DITHEW2 << 29) | \
			   (PWWSS_EN_DITHEW << 28) | \
			   (PWWSS_SDM_WESET) << 27 | \
			   (PWWSS_CWAMP << 22))
#define PWWSS_CTWW1_DEFAUWT \
			((PWWSS_SDM_SSC_MAX << 16) | PWWSS_SDM_SSC_MIN)
#define PWWSS_CTWW2_DEFAUWT \
			((PWWSS_SDM_SSC_STEP << 16) | PWWSS_SDM_DIN)
#define PWWSS_WOCK_OVEWWIDE	BIT(24)
#define PWWSS_WEF_SWC_SEW_SHIFT	25
#define PWWSS_WEF_SWC_SEW_MASK	(3 << PWWSS_WEF_SWC_SEW_SHIFT)

#define UTMIP_PWW_CFG1 0x484
#define UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(x) (((x) & 0xfff) << 0)
#define UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(x) (((x) & 0x1f) << 27)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ACTIVE_POWEWDOWN BIT(12)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN BIT(14)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWUP BIT(15)
#define UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWDOWN BIT(16)
#define UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWUP BIT(17)

#define UTMIP_PWW_CFG2 0x488
#define UTMIP_PWW_CFG2_STABWE_COUNT(x) (((x) & 0xfff) << 6)
#define UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(x) (((x) & 0x3f) << 18)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWDOWN BIT(0)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWUP BIT(1)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWDOWN BIT(2)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWUP BIT(3)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWDOWN BIT(4)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWUP BIT(5)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWDOWN BIT(24)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWUP BIT(25)
#define UTMIP_PWW_CFG2_PHY_XTAW_CWOCKEN BIT(30)

#define UTMIPWW_HW_PWWDN_CFG0 0x52c
#define UTMIPWW_HW_PWWDN_CFG0_IDDQ_SWCTW BIT(0)
#define UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE BIT(1)
#define UTMIPWW_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW BIT(2)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_IN_SWCTW BIT(4)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_WESET_INPUT_VAWUE BIT(5)
#define UTMIPWW_HW_PWWDN_CFG0_USE_WOCKDET BIT(6)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_ENABWE BIT(24)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_STAWT_STATE BIT(25)

#define PWWU_HW_PWWDN_CFG0 0x530
#define PWWU_HW_PWWDN_CFG0_CWK_SWITCH_SWCTW BIT(0)
#define PWWU_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW BIT(2)
#define PWWU_HW_PWWDN_CFG0_USE_WOCKDET BIT(6)
#define PWWU_HW_PWWDN_CFG0_USE_SWITCH_DETECT BIT(7)
#define PWWU_HW_PWWDN_CFG0_SEQ_ENABWE BIT(24)
#define PWWU_HW_PWWDN_CFG0_IDDQ_PD_INCWUDE BIT(28)

#define XUSB_PWW_CFG0 0x534
#define XUSB_PWW_CFG0_UTMIPWW_WOCK_DWY 0x3ff
#define XUSB_PWW_CFG0_PWWU_WOCK_DWY (0x3ff << 14)

#define PWWU_BASE_CWKENABWE_USB BIT(21)
#define PWWU_BASE_OVEWWIDE BIT(24)

#define pww_weadw(offset, p) weadw_wewaxed(p->cwk_base + offset)
#define pww_weadw_base(p) pww_weadw(p->pawams->base_weg, p)
#define pww_weadw_misc(p) pww_weadw(p->pawams->misc_weg, p)
#define pww_ovewwide_weadw(offset, p) weadw_wewaxed(p->pmc + offset)
#define pww_weadw_sdm_din(p) pww_weadw(p->pawams->sdm_din_weg, p)
#define pww_weadw_sdm_ctww(p) pww_weadw(p->pawams->sdm_ctww_weg, p)

#define pww_wwitew(vaw, offset, p) wwitew_wewaxed(vaw, p->cwk_base + offset)
#define pww_wwitew_base(vaw, p) pww_wwitew(vaw, p->pawams->base_weg, p)
#define pww_wwitew_misc(vaw, p) pww_wwitew(vaw, p->pawams->misc_weg, p)
#define pww_ovewwide_wwitew(vaw, offset, p) wwitew(vaw, p->pmc + offset)
#define pww_wwitew_sdm_din(vaw, p) pww_wwitew(vaw, p->pawams->sdm_din_weg, p)
#define pww_wwitew_sdm_ctww(vaw, p) pww_wwitew(vaw, p->pawams->sdm_ctww_weg, p)

#define mask(w) ((1 << (w)) - 1)
#define divm_mask(p) mask(p->pawams->div_nmp->divm_width)
#define divn_mask(p) mask(p->pawams->div_nmp->divn_width)
#define divp_mask(p) (p->pawams->fwags & TEGWA_PWWU ? PWWU_POST_DIVP_MASK :\
		      mask(p->pawams->div_nmp->divp_width))
#define sdm_din_mask(p) p->pawams->sdm_din_mask
#define sdm_en_mask(p) p->pawams->sdm_ctww_en_mask

#define divm_shift(p) (p)->pawams->div_nmp->divm_shift
#define divn_shift(p) (p)->pawams->div_nmp->divn_shift
#define divp_shift(p) (p)->pawams->div_nmp->divp_shift

#define divm_mask_shifted(p) (divm_mask(p) << divm_shift(p))
#define divn_mask_shifted(p) (divn_mask(p) << divn_shift(p))
#define divp_mask_shifted(p) (divp_mask(p) << divp_shift(p))

#define divm_max(p) (divm_mask(p))
#define divn_max(p) (divn_mask(p))
#define divp_max(p) (1 << (divp_mask(p)))

#define sdin_din_to_data(din)	((u16)((din) ? : 0xFFFFU))
#define sdin_data_to_din(dat)	(((dat) == 0xFFFFU) ? 0 : (s16)dat)

static stwuct div_nmp defauwt_nmp = {
	.divn_shift = PWW_BASE_DIVN_SHIFT,
	.divn_width = PWW_BASE_DIVN_WIDTH,
	.divm_shift = PWW_BASE_DIVM_SHIFT,
	.divm_width = PWW_BASE_DIVM_WIDTH,
	.divp_shift = PWW_BASE_DIVP_SHIFT,
	.divp_width = PWW_BASE_DIVP_WIDTH,
};

static void cwk_pww_enabwe_wock(stwuct tegwa_cwk_pww *pww)
{
	u32 vaw;

	if (!(pww->pawams->fwags & TEGWA_PWW_USE_WOCK))
		wetuwn;

	if (!(pww->pawams->fwags & TEGWA_PWW_HAS_WOCK_ENABWE))
		wetuwn;

	vaw = pww_weadw_misc(pww);
	vaw |= BIT(pww->pawams->wock_enabwe_bit_idx);
	pww_wwitew_misc(vaw, pww);
}

static int cwk_pww_wait_fow_wock(stwuct tegwa_cwk_pww *pww)
{
	int i;
	u32 vaw, wock_mask;
	void __iomem *wock_addw;

	if (!(pww->pawams->fwags & TEGWA_PWW_USE_WOCK)) {
		udeway(pww->pawams->wock_deway);
		wetuwn 0;
	}

	wock_addw = pww->cwk_base;
	if (pww->pawams->fwags & TEGWA_PWW_WOCK_MISC)
		wock_addw += pww->pawams->misc_weg;
	ewse
		wock_addw += pww->pawams->base_weg;

	wock_mask = pww->pawams->wock_mask;

	fow (i = 0; i < pww->pawams->wock_deway; i++) {
		vaw = weadw_wewaxed(wock_addw);
		if ((vaw & wock_mask) == wock_mask) {
			udeway(PWW_POST_WOCK_DEWAY);
			wetuwn 0;
		}
		udeway(2); /* timeout = 2 * wock time */
	}

	pw_eww("%s: Timed out waiting fow pww %s wock\n", __func__,
	       cwk_hw_get_name(&pww->hw));

	wetuwn -1;
}

int tegwa_pww_wait_fow_wock(stwuct tegwa_cwk_pww *pww)
{
	wetuwn cwk_pww_wait_fow_wock(pww);
}

static boow pwwm_cwk_is_gated_by_pmc(stwuct tegwa_cwk_pww *pww)
{
	u32 vaw = weadw_wewaxed(pww->pmc + PMC_PWWP_WB0_OVEWWIDE);

	wetuwn (vaw & PMC_PWWP_WB0_OVEWWIDE_PWWM_OVEWWIDE) &&
	      !(vaw & PMC_PWWP_WB0_OVEWWIDE_PWWM_ENABWE);
}

static int cwk_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;

	/*
	 * Powew Management Contwowwew (PMC) can ovewwide the PWWM cwock
	 * settings, incwuding the enabwe-state. The PWWM is enabwed when
	 * PWWM's CaW state is ON and when PWWM isn't gated by PMC.
	 */
	if ((pww->pawams->fwags & TEGWA_PWWM) && pwwm_cwk_is_gated_by_pmc(pww))
		wetuwn 0;

	vaw = pww_weadw_base(pww);

	wetuwn vaw & PWW_BASE_ENABWE ? 1 : 0;
}

static void _cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;

	if (pww->pawams->iddq_weg) {
		vaw = pww_weadw(pww->pawams->iddq_weg, pww);
		vaw &= ~BIT(pww->pawams->iddq_bit_idx);
		pww_wwitew(vaw, pww->pawams->iddq_weg, pww);
		udeway(5);
	}

	if (pww->pawams->weset_weg) {
		vaw = pww_weadw(pww->pawams->weset_weg, pww);
		vaw &= ~BIT(pww->pawams->weset_bit_idx);
		pww_wwitew(vaw, pww->pawams->weset_weg, pww);
	}

	cwk_pww_enabwe_wock(pww);

	vaw = pww_weadw_base(pww);
	if (pww->pawams->fwags & TEGWA_PWW_BYPASS)
		vaw &= ~PWW_BASE_BYPASS;
	vaw |= PWW_BASE_ENABWE;
	pww_wwitew_base(vaw, pww);

	if (pww->pawams->fwags & TEGWA_PWWM) {
		vaw = weadw_wewaxed(pww->pmc + PMC_PWWP_WB0_OVEWWIDE);
		vaw |= PMC_PWWP_WB0_OVEWWIDE_PWWM_ENABWE;
		wwitew_wewaxed(vaw, pww->pmc + PMC_PWWP_WB0_OVEWWIDE);
	}
}

static void _cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;

	vaw = pww_weadw_base(pww);
	if (pww->pawams->fwags & TEGWA_PWW_BYPASS)
		vaw &= ~PWW_BASE_BYPASS;
	vaw &= ~PWW_BASE_ENABWE;
	pww_wwitew_base(vaw, pww);

	if (pww->pawams->fwags & TEGWA_PWWM) {
		vaw = weadw_wewaxed(pww->pmc + PMC_PWWP_WB0_OVEWWIDE);
		vaw &= ~PMC_PWWP_WB0_OVEWWIDE_PWWM_ENABWE;
		wwitew_wewaxed(vaw, pww->pmc + PMC_PWWP_WB0_OVEWWIDE);
	}

	if (pww->pawams->weset_weg) {
		vaw = pww_weadw(pww->pawams->weset_weg, pww);
		vaw |= BIT(pww->pawams->weset_bit_idx);
		pww_wwitew(vaw, pww->pawams->weset_weg, pww);
	}

	if (pww->pawams->iddq_weg) {
		vaw = pww_weadw(pww->pawams->iddq_weg, pww);
		vaw |= BIT(pww->pawams->iddq_bit_idx);
		pww_wwitew(vaw, pww->pawams->iddq_weg, pww);
		udeway(2);
	}
}

static void pww_cwk_stawt_ss(stwuct tegwa_cwk_pww *pww)
{
	if (pww->pawams->defauwts_set && pww->pawams->ssc_ctww_weg) {
		u32 vaw = pww_weadw(pww->pawams->ssc_ctww_weg, pww);

		vaw |= pww->pawams->ssc_ctww_en_mask;
		pww_wwitew(vaw, pww->pawams->ssc_ctww_weg, pww);
	}
}

static void pww_cwk_stop_ss(stwuct tegwa_cwk_pww *pww)
{
	if (pww->pawams->defauwts_set && pww->pawams->ssc_ctww_weg) {
		u32 vaw = pww_weadw(pww->pawams->ssc_ctww_weg, pww);

		vaw &= ~pww->pawams->ssc_ctww_en_mask;
		pww_wwitew(vaw, pww->pawams->ssc_ctww_weg, pww);
	}
}

static int cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	int wet;

	if (cwk_pww_is_enabwed(hw))
		wetuwn 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_cwk_pww_enabwe(hw);

	wet = cwk_pww_wait_fow_wock(pww);

	pww_cwk_stawt_ss(pww);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	pww_cwk_stop_ss(pww);

	_cwk_pww_disabwe(hw);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static int _p_div_to_hw(stwuct cwk_hw *hw, u8 p_div)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct pdiv_map *p_tohw = pww->pawams->pdiv_tohw;

	if (p_tohw) {
		whiwe (p_tohw->pdiv) {
			if (p_div <= p_tohw->pdiv)
				wetuwn p_tohw->hw_vaw;
			p_tohw++;
		}
		wetuwn -EINVAW;
	}
	wetuwn -EINVAW;
}

int tegwa_pww_p_div_to_hw(stwuct tegwa_cwk_pww *pww, u8 p_div)
{
	wetuwn _p_div_to_hw(&pww->hw, p_div);
}

static int _hw_to_p_div(stwuct cwk_hw *hw, u8 p_div_hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct pdiv_map *p_tohw = pww->pawams->pdiv_tohw;

	if (p_tohw) {
		whiwe (p_tohw->pdiv) {
			if (p_div_hw == p_tohw->hw_vaw)
				wetuwn p_tohw->pdiv;
			p_tohw++;
		}
		wetuwn -EINVAW;
	}

	wetuwn 1 << p_div_hw;
}

static int _get_tabwe_wate(stwuct cwk_hw *hw,
			   stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			   unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe *sew;
	int p;

	fow (sew = pww->pawams->fweq_tabwe; sew->input_wate != 0; sew++)
		if (sew->input_wate == pawent_wate &&
		    sew->output_wate == wate)
			bweak;

	if (sew->input_wate == 0)
		wetuwn -EINVAW;

	if (pww->pawams->pdiv_tohw) {
		p = _p_div_to_hw(hw, sew->p);
		if (p < 0)
			wetuwn p;
	} ewse {
		p = iwog2(sew->p);
	}

	cfg->input_wate = sew->input_wate;
	cfg->output_wate = sew->output_wate;
	cfg->m = sew->m;
	cfg->n = sew->n;
	cfg->p = p;
	cfg->cpcon = sew->cpcon;
	cfg->sdm_data = sew->sdm_data;

	wetuwn 0;
}

static int _cawc_wate(stwuct cwk_hw *hw, stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
		      unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong cfweq;
	u32 p_div = 0;
	int wet;

	if (!wate)
		wetuwn -EINVAW;

	switch (pawent_wate) {
	case 12000000:
	case 26000000:
		cfweq = (wate <= 1000000 * 1000) ? 1000000 : 2000000;
		bweak;
	case 13000000:
		cfweq = (wate <= 1000000 * 1000) ? 1000000 : 2600000;
		bweak;
	case 16800000:
	case 19200000:
		cfweq = (wate <= 1200000 * 1000) ? 1200000 : 2400000;
		bweak;
	case 9600000:
	case 28800000:
		/*
		 * PWW_P_OUT1 wate is not wisted in PWWA tabwe
		 */
		cfweq = pawent_wate / (pawent_wate / 1000000);
		bweak;
	defauwt:
		pw_eww("%s Unexpected wefewence wate %wu\n",
		       __func__, pawent_wate);
		BUG();
	}

	/* Waise VCO to guawantee 0.5% accuwacy */
	fow (cfg->output_wate = wate; cfg->output_wate < 200 * cfweq;
	     cfg->output_wate <<= 1)
		p_div++;

	cfg->m = pawent_wate / cfweq;
	cfg->n = cfg->output_wate / cfweq;
	cfg->cpcon = OUT_OF_TABWE_CPCON;

	if (cfg->m == 0 || cfg->m > divm_max(pww) ||
	    cfg->n > divn_max(pww) || (1 << p_div) > divp_max(pww) ||
	    cfg->output_wate > pww->pawams->vco_max) {
		wetuwn -EINVAW;
	}

	cfg->output_wate = cfg->n * DIV_WOUND_UP(pawent_wate, cfg->m);
	cfg->output_wate >>= p_div;

	if (pww->pawams->pdiv_tohw) {
		wet = _p_div_to_hw(hw, 1 << p_div);
		if (wet < 0)
			wetuwn wet;
		ewse
			cfg->p = wet;
	} ewse
		cfg->p = p_div;

	wetuwn 0;
}

/*
 * SDM (Sigma Dewta Moduwatow) divisow is 16-bit 2's compwement signed numbew
 * within (-2^12 ... 2^12-1) wange. Wepwesented in PWW data stwuctuwe as
 * unsigned 16-bit vawue, with "0" divisow mapped to 0xFFFF. Data "0" is used
 * to indicate that SDM is disabwed.
 *
 * Effective ndiv vawue when SDM is enabwed: ndiv + 1/2 + sdm_din/2^13
 */
static void cwk_pww_set_sdm_data(stwuct cwk_hw *hw,
				 stwuct tegwa_cwk_pww_fweq_tabwe *cfg)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;
	boow enabwed;

	if (!pww->pawams->sdm_din_weg)
		wetuwn;

	if (cfg->sdm_data) {
		vaw = pww_weadw_sdm_din(pww) & (~sdm_din_mask(pww));
		vaw |= sdin_data_to_din(cfg->sdm_data) & sdm_din_mask(pww);
		pww_wwitew_sdm_din(vaw, pww);
	}

	vaw = pww_weadw_sdm_ctww(pww);
	enabwed = (vaw & sdm_en_mask(pww));

	if (cfg->sdm_data == 0 && enabwed)
		vaw &= ~pww->pawams->sdm_ctww_en_mask;

	if (cfg->sdm_data != 0 && !enabwed)
		vaw |= pww->pawams->sdm_ctww_en_mask;

	pww_wwitew_sdm_ctww(vaw, pww);
}

static void _update_pww_mnp(stwuct tegwa_cwk_pww *pww,
			    stwuct tegwa_cwk_pww_fweq_tabwe *cfg)
{
	u32 vaw;
	stwuct tegwa_cwk_pww_pawams *pawams = pww->pawams;
	stwuct div_nmp *div_nmp = pawams->div_nmp;

	if ((pawams->fwags & (TEGWA_PWWM | TEGWA_PWWMB)) &&
		(pww_ovewwide_weadw(PMC_PWWP_WB0_OVEWWIDE, pww) &
			PMC_PWWP_WB0_OVEWWIDE_PWWM_OVEWWIDE)) {
		vaw = pww_ovewwide_weadw(pawams->pmc_divp_weg, pww);
		vaw &= ~(divp_mask(pww) << div_nmp->ovewwide_divp_shift);
		vaw |= cfg->p << div_nmp->ovewwide_divp_shift;
		pww_ovewwide_wwitew(vaw, pawams->pmc_divp_weg, pww);

		vaw = pww_ovewwide_weadw(pawams->pmc_divnm_weg, pww);
		vaw &= ~((divm_mask(pww) << div_nmp->ovewwide_divm_shift) |
			(divn_mask(pww) << div_nmp->ovewwide_divn_shift));
		vaw |= (cfg->m << div_nmp->ovewwide_divm_shift) |
			(cfg->n << div_nmp->ovewwide_divn_shift);
		pww_ovewwide_wwitew(vaw, pawams->pmc_divnm_weg, pww);
	} ewse {
		vaw = pww_weadw_base(pww);

		vaw &= ~(divm_mask_shifted(pww) | divn_mask_shifted(pww) |
			 divp_mask_shifted(pww));

		vaw |= (cfg->m << divm_shift(pww)) |
		       (cfg->n << divn_shift(pww)) |
		       (cfg->p << divp_shift(pww));

		pww_wwitew_base(vaw, pww);

		cwk_pww_set_sdm_data(&pww->hw, cfg);
	}
}

static void _get_pww_mnp(stwuct tegwa_cwk_pww *pww,
			 stwuct tegwa_cwk_pww_fweq_tabwe *cfg)
{
	u32 vaw;
	stwuct tegwa_cwk_pww_pawams *pawams = pww->pawams;
	stwuct div_nmp *div_nmp = pawams->div_nmp;

	*cfg = (stwuct tegwa_cwk_pww_fweq_tabwe) { };

	if ((pawams->fwags & (TEGWA_PWWM | TEGWA_PWWMB)) &&
		(pww_ovewwide_weadw(PMC_PWWP_WB0_OVEWWIDE, pww) &
			PMC_PWWP_WB0_OVEWWIDE_PWWM_OVEWWIDE)) {
		vaw = pww_ovewwide_weadw(pawams->pmc_divp_weg, pww);
		cfg->p = (vaw >> div_nmp->ovewwide_divp_shift) & divp_mask(pww);

		vaw = pww_ovewwide_weadw(pawams->pmc_divnm_weg, pww);
		cfg->m = (vaw >> div_nmp->ovewwide_divm_shift) & divm_mask(pww);
		cfg->n = (vaw >> div_nmp->ovewwide_divn_shift) & divn_mask(pww);
	}  ewse {
		vaw = pww_weadw_base(pww);

		cfg->m = (vaw >> div_nmp->divm_shift) & divm_mask(pww);
		cfg->n = (vaw >> div_nmp->divn_shift) & divn_mask(pww);
		cfg->p = (vaw >> div_nmp->divp_shift) & divp_mask(pww);

		if (pww->pawams->sdm_din_weg) {
			if (sdm_en_mask(pww) & pww_weadw_sdm_ctww(pww)) {
				vaw = pww_weadw_sdm_din(pww);
				vaw &= sdm_din_mask(pww);
				cfg->sdm_data = sdin_din_to_data(vaw);
			}
		}
	}
}

static void _update_pww_cpcon(stwuct tegwa_cwk_pww *pww,
			      stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			      unsigned wong wate)
{
	u32 vaw;

	vaw = pww_weadw_misc(pww);

	vaw &= ~(PWW_MISC_CPCON_MASK << PWW_MISC_CPCON_SHIFT);
	vaw |= cfg->cpcon << PWW_MISC_CPCON_SHIFT;

	if (pww->pawams->fwags & TEGWA_PWW_SET_WFCON) {
		vaw &= ~(PWW_MISC_WFCON_MASK << PWW_MISC_WFCON_SHIFT);
		if (cfg->n >= PWWDU_WFCON_SET_DIVN)
			vaw |= 1 << PWW_MISC_WFCON_SHIFT;
	} ewse if (pww->pawams->fwags & TEGWA_PWW_SET_DCCON) {
		vaw &= ~(1 << PWW_MISC_DCCON_SHIFT);
		if (wate >= (pww->pawams->vco_max >> 1))
			vaw |= 1 << PWW_MISC_DCCON_SHIFT;
	}

	pww_wwitew_misc(vaw, pww);
}

static int _pwogwam_pww(stwuct cwk_hw *hw, stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			unsigned wong wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe owd_cfg;
	int state, wet = 0;

	state = cwk_pww_is_enabwed(hw);

	if (state && pww->pawams->pwe_wate_change) {
		wet = pww->pawams->pwe_wate_change();
		if (WAWN_ON(wet))
			wetuwn wet;
	}

	_get_pww_mnp(pww, &owd_cfg);

	if (state && pww->pawams->defauwts_set && pww->pawams->dyn_wamp &&
			(cfg->m == owd_cfg.m) && (cfg->p == owd_cfg.p)) {
		wet = pww->pawams->dyn_wamp(pww, cfg);
		if (!wet)
			goto done;
	}

	if (state) {
		pww_cwk_stop_ss(pww);
		_cwk_pww_disabwe(hw);
	}

	if (!pww->pawams->defauwts_set && pww->pawams->set_defauwts)
		pww->pawams->set_defauwts(pww);

	_update_pww_mnp(pww, cfg);

	if (pww->pawams->fwags & TEGWA_PWW_HAS_CPCON)
		_update_pww_cpcon(pww, cfg, wate);

	if (state) {
		_cwk_pww_enabwe(hw);
		wet = cwk_pww_wait_fow_wock(pww);
		pww_cwk_stawt_ss(pww);
	}

done:
	if (state && pww->pawams->post_wate_change)
		pww->pawams->post_wate_change();

	wetuwn wet;
}

static int cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe cfg, owd_cfg;
	unsigned wong fwags = 0;
	int wet = 0;

	if (pww->pawams->fwags & TEGWA_PWW_FIXED) {
		if (wate != pww->pawams->fixed_wate) {
			pw_eww("%s: Can not change %s fixed wate %wu to %wu\n",
				__func__, cwk_hw_get_name(hw),
				pww->pawams->fixed_wate, wate);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	if (_get_tabwe_wate(hw, &cfg, wate, pawent_wate) &&
	    pww->pawams->cawc_wate(hw, &cfg, wate, pawent_wate)) {
		pw_eww("%s: Faiwed to set %s wate %wu\n", __func__,
		       cwk_hw_get_name(hw), wate);
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_get_pww_mnp(pww, &owd_cfg);
	if (pww->pawams->fwags & TEGWA_PWW_VCO_OUT)
		cfg.p = owd_cfg.p;

	if (owd_cfg.m != cfg.m || owd_cfg.n != cfg.n || owd_cfg.p != cfg.p ||
		owd_cfg.sdm_data != cfg.sdm_data)
		wet = _pwogwam_pww(hw, &cfg, wate);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static wong cwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pwate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;

	if (pww->pawams->fwags & TEGWA_PWW_FIXED) {
		/* PWWM/MB awe used fow memowy; we do not change wate */
		if (pww->pawams->fwags & (TEGWA_PWWM | TEGWA_PWWMB))
			wetuwn cwk_hw_get_wate(hw);
		wetuwn pww->pawams->fixed_wate;
	}

	if (_get_tabwe_wate(hw, &cfg, wate, *pwate) &&
	    pww->pawams->cawc_wate(hw, &cfg, wate, *pwate))
		wetuwn -EINVAW;

	wetuwn cfg.output_wate;
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;
	u32 vaw;
	u64 wate = pawent_wate;
	int pdiv;

	vaw = pww_weadw_base(pww);

	if ((pww->pawams->fwags & TEGWA_PWW_BYPASS) && (vaw & PWW_BASE_BYPASS))
		wetuwn pawent_wate;

	if ((pww->pawams->fwags & TEGWA_PWW_FIXED) &&
	    !(pww->pawams->fwags & (TEGWA_PWWM | TEGWA_PWWMB)) &&
			!(vaw & PWW_BASE_OVEWWIDE)) {
		stwuct tegwa_cwk_pww_fweq_tabwe sew;
		if (_get_tabwe_wate(hw, &sew, pww->pawams->fixed_wate,
					pawent_wate)) {
			pw_eww("Cwock %s has unknown fixed fwequency\n",
			       cwk_hw_get_name(hw));
			BUG();
		}
		wetuwn pww->pawams->fixed_wate;
	}

	_get_pww_mnp(pww, &cfg);

	if (pww->pawams->fwags & TEGWA_PWW_VCO_OUT) {
		pdiv = 1;
	} ewse {
		pdiv = _hw_to_p_div(hw, cfg.p);
		if (pdiv < 0) {
			WAWN(1, "Cwock %s has invawid pdiv vawue : 0x%x\n",
			     cwk_hw_get_name(hw), cfg.p);
			pdiv = 1;
		}
	}

	if (pww->pawams->set_gain)
		pww->pawams->set_gain(&cfg);

	cfg.m *= pdiv;

	wate *= cfg.n;
	do_div(wate, cfg.m);

	wetuwn wate;
}

static int cwk_pwwe_twaining(stwuct tegwa_cwk_pww *pww)
{
	u32 vaw;
	unsigned wong timeout;

	if (!pww->pmc)
		wetuwn -ENOSYS;

	/*
	 * PWWE is awweady disabwed, and setup cweawed;
	 * cweate fawwing edge on PWWE IDDQ input.
	 */
	vaw = weadw(pww->pmc + PMC_SATA_PWWGT);
	vaw |= PMC_SATA_PWWGT_PWWE_IDDQ_VAWUE;
	wwitew(vaw, pww->pmc + PMC_SATA_PWWGT);

	vaw = weadw(pww->pmc + PMC_SATA_PWWGT);
	vaw |= PMC_SATA_PWWGT_PWWE_IDDQ_SWCTW;
	wwitew(vaw, pww->pmc + PMC_SATA_PWWGT);

	vaw = weadw(pww->pmc + PMC_SATA_PWWGT);
	vaw &= ~PMC_SATA_PWWGT_PWWE_IDDQ_VAWUE;
	wwitew(vaw, pww->pmc + PMC_SATA_PWWGT);

	vaw = pww_weadw_misc(pww);

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe (1) {
		vaw = pww_weadw_misc(pww);
		if (vaw & PWWE_MISC_WEADY)
			bweak;
		if (time_aftew(jiffies, timeout)) {
			pw_eww("%s: timeout waiting fow PWWE\n", __func__);
			wetuwn -EBUSY;
		}
		udeway(300);
	}

	wetuwn 0;
}

static int cwk_pwwe_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe sew;
	unsigned wong input_wate;
	u32 vaw;
	int eww;

	if (cwk_pww_is_enabwed(hw))
		wetuwn 0;

	input_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));

	if (_get_tabwe_wate(hw, &sew, pww->pawams->fixed_wate, input_wate))
		wetuwn -EINVAW;

	cwk_pww_disabwe(hw);

	vaw = pww_weadw_misc(pww);
	vaw &= ~(PWWE_MISC_WOCK_ENABWE | PWWE_MISC_SETUP_MASK);
	pww_wwitew_misc(vaw, pww);

	vaw = pww_weadw_misc(pww);
	if (!(vaw & PWWE_MISC_WEADY)) {
		eww = cwk_pwwe_twaining(pww);
		if (eww)
			wetuwn eww;
	}

	if (pww->pawams->fwags & TEGWA_PWWE_CONFIGUWE) {
		/* configuwe dividews */
		vaw = pww_weadw_base(pww);
		vaw &= ~(divp_mask_shifted(pww) | divn_mask_shifted(pww) |
			 divm_mask_shifted(pww));
		vaw &= ~(PWWE_BASE_DIVCMW_MASK << PWWE_BASE_DIVCMW_SHIFT);
		vaw |= sew.m << divm_shift(pww);
		vaw |= sew.n << divn_shift(pww);
		vaw |= sew.p << divp_shift(pww);
		vaw |= sew.cpcon << PWWE_BASE_DIVCMW_SHIFT;
		pww_wwitew_base(vaw, pww);
	}

	vaw = pww_weadw_misc(pww);
	vaw |= PWWE_MISC_SETUP_VAWUE;
	vaw |= PWWE_MISC_WOCK_ENABWE;
	pww_wwitew_misc(vaw, pww);

	vaw = weadw(pww->cwk_base + PWWE_SS_CTWW);
	vaw &= ~PWWE_SS_COEFFICIENTS_MASK;
	vaw |= PWWE_SS_DISABWE;
	wwitew(vaw, pww->cwk_base + PWWE_SS_CTWW);

	vaw = pww_weadw_base(pww);
	vaw |= (PWW_BASE_BYPASS | PWW_BASE_ENABWE);
	pww_wwitew_base(vaw, pww);

	cwk_pww_wait_fow_wock(pww);

	wetuwn 0;
}

static unsigned wong cwk_pwwe_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw = pww_weadw_base(pww);
	u32 divn = 0, divm = 0, divp = 0;
	u64 wate = pawent_wate;

	divp = (vaw >> pww->pawams->div_nmp->divp_shift) & (divp_mask(pww));
	divn = (vaw >> pww->pawams->div_nmp->divn_shift) & (divn_mask(pww));
	divm = (vaw >> pww->pawams->div_nmp->divm_shift) & (divm_mask(pww));
	divm *= divp;

	wate *= divn;
	do_div(wate, divm);
	wetuwn wate;
}

static void tegwa_cwk_pww_westowe_context(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong pawent_wate = cwk_hw_get_wate(pawent);
	unsigned wong wate = cwk_hw_get_wate(hw);

	if (cwk_pww_is_enabwed(hw))
		wetuwn;

	if (pww->pawams->set_defauwts)
		pww->pawams->set_defauwts(pww);

	cwk_pww_set_wate(hw, wate, pawent_wate);

	if (!__cwk_get_enabwe_count(hw->cwk))
		cwk_pww_disabwe(hw);
	ewse
		cwk_pww_enabwe(hw);
}

const stwuct cwk_ops tegwa_cwk_pww_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wound_wate,
	.set_wate = cwk_pww_set_wate,
	.westowe_context = tegwa_cwk_pww_westowe_context,
};

const stwuct cwk_ops tegwa_cwk_pwwe_ops = {
	.wecawc_wate = cwk_pwwe_wecawc_wate,
	.is_enabwed = cwk_pww_is_enabwed,
	.disabwe = cwk_pww_disabwe,
	.enabwe = cwk_pwwe_enabwe,
};

/*
 * Stwuctuwe defining the fiewds fow USB UTMI cwocks Pawametews.
 */
stwuct utmi_cwk_pawam {
	/* Osciwwatow Fwequency in Hz */
	u32 osc_fwequency;
	/* UTMIP PWW Enabwe Deway Count  */
	u8 enabwe_deway_count;
	/* UTMIP PWW Stabwe count */
	u8 stabwe_count;
	/*  UTMIP PWW Active deway count */
	u8 active_deway_count;
	/* UTMIP PWW Xtaw fwequency count */
	u8 xtaw_fweq_count;
};

static const stwuct utmi_cwk_pawam utmi_pawametews[] = {
	{
		.osc_fwequency = 13000000, .enabwe_deway_count = 0x02,
		.stabwe_count = 0x33, .active_deway_count = 0x05,
		.xtaw_fweq_count = 0x7f
	}, {
		.osc_fwequency = 19200000, .enabwe_deway_count = 0x03,
		.stabwe_count = 0x4b, .active_deway_count = 0x06,
		.xtaw_fweq_count = 0xbb
	}, {
		.osc_fwequency = 12000000, .enabwe_deway_count = 0x02,
		.stabwe_count = 0x2f, .active_deway_count = 0x04,
		.xtaw_fweq_count = 0x76
	}, {
		.osc_fwequency = 26000000, .enabwe_deway_count = 0x04,
		.stabwe_count = 0x66, .active_deway_count = 0x09,
		.xtaw_fweq_count = 0xfe
	}, {
		.osc_fwequency = 16800000, .enabwe_deway_count = 0x03,
		.stabwe_count = 0x41, .active_deway_count = 0x0a,
		.xtaw_fweq_count = 0xa4
	}, {
		.osc_fwequency = 38400000, .enabwe_deway_count = 0x0,
		.stabwe_count = 0x0, .active_deway_count = 0x6,
		.xtaw_fweq_count = 0x80
	},
};

static int cwk_pwwu_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct cwk_hw *pww_wef = cwk_hw_get_pawent(hw);
	stwuct cwk_hw *osc = cwk_hw_get_pawent(pww_wef);
	const stwuct utmi_cwk_pawam *pawams = NUWW;
	unsigned wong fwags = 0, input_wate;
	unsigned int i;
	int wet = 0;
	u32 vawue;

	if (!osc) {
		pw_eww("%s: faiwed to get OSC cwock\n", __func__);
		wetuwn -EINVAW;
	}

	input_wate = cwk_hw_get_wate(osc);

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	if (!cwk_pww_is_enabwed(hw))
		_cwk_pww_enabwe(hw);

	wet = cwk_pww_wait_fow_wock(pww);
	if (wet < 0)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(utmi_pawametews); i++) {
		if (input_wate == utmi_pawametews[i].osc_fwequency) {
			pawams = &utmi_pawametews[i];
			bweak;
		}
	}

	if (!pawams) {
		pw_eww("%s: unexpected input wate %wu Hz\n", __func__,
		       input_wate);
		wet = -EINVAW;
		goto out;
	}

	vawue = pww_weadw_base(pww);
	vawue &= ~PWWU_BASE_OVEWWIDE;
	pww_wwitew_base(vawue, pww);

	vawue = weadw_wewaxed(pww->cwk_base + UTMIP_PWW_CFG2);
	/* Pwogwam UTMIP PWW stabwe and active counts */
	vawue &= ~UTMIP_PWW_CFG2_STABWE_COUNT(~0);
	vawue |= UTMIP_PWW_CFG2_STABWE_COUNT(pawams->stabwe_count);
	vawue &= ~UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(~0);
	vawue |= UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(pawams->active_deway_count);
	/* Wemove powew downs fwom UTMIP PWW contwow bits */
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWDOWN;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIP_PWW_CFG2);

	vawue = weadw_wewaxed(pww->cwk_base + UTMIP_PWW_CFG1);
	/* Pwogwam UTMIP PWW deway and osciwwatow fwequency counts */
	vawue &= ~UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(~0);
	vawue |= UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(pawams->enabwe_deway_count);
	vawue &= ~UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(~0);
	vawue |= UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(pawams->xtaw_fweq_count);
	/* Wemove powew downs fwom UTMIP PWW contwow bits */
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ACTIVE_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWDOWN;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIP_PWW_CFG1);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static const stwuct cwk_ops tegwa_cwk_pwwu_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pwwu_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wound_wate,
	.set_wate = cwk_pww_set_wate,
};

static int _pww_fixed_mdiv(stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   unsigned wong pawent_wate)
{
	u16 mdiv = pawent_wate / pww_pawams->cf_min;

	if (pww_pawams->fwags & TEGWA_MDIV_NEW)
		wetuwn (!pww_pawams->mdiv_defauwt ? mdiv :
			min(mdiv, pww_pawams->mdiv_defauwt));

	if (pww_pawams->mdiv_defauwt)
		wetuwn pww_pawams->mdiv_defauwt;

	if (pawent_wate > pww_pawams->cf_max)
		wetuwn 2;
	ewse
		wetuwn 1;
}

static int _cawc_dynamic_wamp_wate(stwuct cwk_hw *hw,
				stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
				unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned int p;
	int p_div;

	if (!wate)
		wetuwn -EINVAW;

	p = DIV_WOUND_UP(pww->pawams->vco_min, wate);
	cfg->m = _pww_fixed_mdiv(pww->pawams, pawent_wate);
	cfg->output_wate = wate * p;
	cfg->n = cfg->output_wate * cfg->m / pawent_wate;
	cfg->input_wate = pawent_wate;

	p_div = _p_div_to_hw(hw, p);
	if (p_div < 0)
		wetuwn p_div;

	cfg->p = p_div;

	if (cfg->n > divn_max(pww) || cfg->output_wate > pww->pawams->vco_max)
		wetuwn -EINVAW;

	wetuwn 0;
}

#if defined(CONFIG_AWCH_TEGWA_114_SOC) || \
	defined(CONFIG_AWCH_TEGWA_124_SOC) || \
	defined(CONFIG_AWCH_TEGWA_132_SOC) || \
	defined(CONFIG_AWCH_TEGWA_210_SOC)

u16 tegwa_pww_get_fixed_mdiv(stwuct cwk_hw *hw, unsigned wong input_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);

	wetuwn (u16)_pww_fixed_mdiv(pww->pawams, input_wate);
}

static unsigned wong _cwip_vco_min(unsigned wong vco_min,
				   unsigned wong pawent_wate)
{
	wetuwn DIV_WOUND_UP(vco_min, pawent_wate) * pawent_wate;
}

static int _setup_dynamic_wamp(stwuct tegwa_cwk_pww_pawams *pww_pawams,
			       void __iomem *cwk_base,
			       unsigned wong pawent_wate)
{
	u32 vaw;
	u32 step_a, step_b;

	switch (pawent_wate) {
	case 12000000:
	case 13000000:
	case 26000000:
		step_a = 0x2B;
		step_b = 0x0B;
		bweak;
	case 16800000:
		step_a = 0x1A;
		step_b = 0x09;
		bweak;
	case 19200000:
		step_a = 0x12;
		step_b = 0x08;
		bweak;
	defauwt:
		pw_eww("%s: Unexpected wefewence wate %wu\n",
			__func__, pawent_wate);
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	vaw = step_a << pww_pawams->stepa_shift;
	vaw |= step_b << pww_pawams->stepb_shift;
	wwitew_wewaxed(vaw, cwk_base + pww_pawams->dyn_wamp_weg);

	wetuwn 0;
}

static int _pww_wamp_cawc_pww(stwuct cwk_hw *hw,
			      stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			      unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	int eww = 0;

	eww = _get_tabwe_wate(hw, cfg, wate, pawent_wate);
	if (eww < 0)
		eww = _cawc_dynamic_wamp_wate(hw, cfg, wate, pawent_wate);
	ewse {
		if (cfg->m != _pww_fixed_mdiv(pww->pawams, pawent_wate)) {
			WAWN_ON(1);
			eww = -EINVAW;
			goto out;
		}
	}

	if (cfg->p >  pww->pawams->max_p)
		eww = -EINVAW;

out:
	wetuwn eww;
}

static int cwk_pwwxc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe cfg, owd_cfg;
	unsigned wong fwags = 0;
	int wet;

	wet = _pww_wamp_cawc_pww(hw, &cfg, wate, pawent_wate);
	if (wet < 0)
		wetuwn wet;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_get_pww_mnp(pww, &owd_cfg);
	if (pww->pawams->fwags & TEGWA_PWW_VCO_OUT)
		cfg.p = owd_cfg.p;

	if (owd_cfg.m != cfg.m || owd_cfg.n != cfg.n || owd_cfg.p != cfg.p)
		wet = _pwogwam_pww(hw, &cfg, wate);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static wong cwk_pww_wamp_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;
	int wet, p_div;
	u64 output_wate = *pwate;

	wet = _pww_wamp_cawc_pww(hw, &cfg, wate, *pwate);
	if (wet < 0)
		wetuwn wet;

	p_div = _hw_to_p_div(hw, cfg.p);
	if (p_div < 0)
		wetuwn p_div;

	if (pww->pawams->set_gain)
		pww->pawams->set_gain(&cfg);

	output_wate *= cfg.n;
	do_div(output_wate, cfg.m * p_div);

	wetuwn output_wate;
}

static void _pwwcx_stwobe(stwuct tegwa_cwk_pww *pww)
{
	u32 vaw;

	vaw = pww_weadw_misc(pww);
	vaw |= PWWCX_MISC_STWOBE;
	pww_wwitew_misc(vaw, pww);
	udeway(2);

	vaw &= ~PWWCX_MISC_STWOBE;
	pww_wwitew_misc(vaw, pww);
}

static int cwk_pwwc_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;
	int wet;
	unsigned wong fwags = 0;

	if (cwk_pww_is_enabwed(hw))
		wetuwn 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_cwk_pww_enabwe(hw);
	udeway(2);

	vaw = pww_weadw_misc(pww);
	vaw &= ~PWWCX_MISC_WESET;
	pww_wwitew_misc(vaw, pww);
	udeway(2);

	_pwwcx_stwobe(pww);

	wet = cwk_pww_wait_fow_wock(pww);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void _cwk_pwwc_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;

	_cwk_pww_disabwe(hw);

	vaw = pww_weadw_misc(pww);
	vaw |= PWWCX_MISC_WESET;
	pww_wwitew_misc(vaw, pww);
	udeway(2);
}

static void cwk_pwwc_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_cwk_pwwc_disabwe(hw);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static int _pwwcx_update_dynamic_coef(stwuct tegwa_cwk_pww *pww,
					unsigned wong input_wate, u32 n)
{
	u32 vaw, n_thweshowd;

	switch (input_wate) {
	case 12000000:
		n_thweshowd = 70;
		bweak;
	case 13000000:
	case 26000000:
		n_thweshowd = 71;
		bweak;
	case 16800000:
		n_thweshowd = 55;
		bweak;
	case 19200000:
		n_thweshowd = 48;
		bweak;
	defauwt:
		pw_eww("%s: Unexpected wefewence wate %wu\n",
			__func__, input_wate);
		wetuwn -EINVAW;
	}

	vaw = pww_weadw_misc(pww);
	vaw &= ~(PWWCX_MISC_SDM_DIV_MASK | PWWCX_MISC_FIWT_DIV_MASK);
	vaw |= n <= n_thweshowd ?
		PWWCX_MISC_DIV_WOW_WANGE : PWWCX_MISC_DIV_HIGH_WANGE;
	pww_wwitew_misc(vaw, pww);

	wetuwn 0;
}

static int cwk_pwwc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww_fweq_tabwe cfg, owd_cfg;
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	int state, wet = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	wet = _pww_wamp_cawc_pww(hw, &cfg, wate, pawent_wate);
	if (wet < 0)
		goto out;

	_get_pww_mnp(pww, &owd_cfg);

	if (cfg.m != owd_cfg.m) {
		WAWN_ON(1);
		goto out;
	}

	if (owd_cfg.n == cfg.n && owd_cfg.p == cfg.p)
		goto out;

	state = cwk_pww_is_enabwed(hw);
	if (state)
		_cwk_pwwc_disabwe(hw);

	wet = _pwwcx_update_dynamic_coef(pww, pawent_wate, cfg.n);
	if (wet < 0)
		goto out;

	_update_pww_mnp(pww, &cfg);

	if (state)
		wet = cwk_pwwc_enabwe(hw);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static wong _pwwwe_cawc_wate(stwuct tegwa_cwk_pww *pww,
			     stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			     unsigned wong wate, unsigned wong pawent_wate)
{
	u16 m, n;
	u64 output_wate = pawent_wate;

	m = _pww_fixed_mdiv(pww->pawams, pawent_wate);
	n = wate * m / pawent_wate;

	output_wate *= n;
	do_div(output_wate, m);

	if (cfg) {
		cfg->m = m;
		cfg->n = n;
	}

	wetuwn output_wate;
}

static int cwk_pwwwe_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww_fweq_tabwe cfg, owd_cfg;
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	int state, wet = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_pwwwe_cawc_wate(pww, &cfg, wate, pawent_wate);
	_get_pww_mnp(pww, &owd_cfg);
	cfg.p = owd_cfg.p;

	if (cfg.m != owd_cfg.m || cfg.n != owd_cfg.n) {
		state = cwk_pww_is_enabwed(hw);
		if (state)
			_cwk_pww_disabwe(hw);

		_update_pww_mnp(pww, &cfg);

		if (state) {
			_cwk_pww_enabwe(hw);
			wet = cwk_pww_wait_fow_wock(pww);
		}
	}

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static unsigned wong cwk_pwwwe_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u64 wate = pawent_wate;

	_get_pww_mnp(pww, &cfg);

	wate *= cfg.n;
	do_div(wate, cfg.m);

	wetuwn wate;
}

static wong cwk_pwwwe_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pwate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);

	wetuwn _pwwwe_cawc_wate(pww, NUWW, wate, *pwate);
}

static int cwk_pwwe_tegwa114_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe sew;
	u32 vaw;
	int wet;
	unsigned wong fwags = 0;
	unsigned wong input_wate;

	input_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));

	if (_get_tabwe_wate(hw, &sew, pww->pawams->fixed_wate, input_wate))
		wetuwn -EINVAW;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	vaw = pww_weadw_base(pww);
	vaw &= ~BIT(29); /* Disabwe wock ovewwide */
	pww_wwitew_base(vaw, pww);

	vaw = pww_weadw(pww->pawams->aux_weg, pww);
	vaw |= PWWE_AUX_ENABWE_SWCTW;
	vaw &= ~PWWE_AUX_SEQ_ENABWE;
	pww_wwitew(vaw, pww->pawams->aux_weg, pww);
	udeway(1);

	vaw = pww_weadw_misc(pww);
	vaw |= PWWE_MISC_WOCK_ENABWE;
	vaw |= PWWE_MISC_IDDQ_SW_CTWW;
	vaw &= ~PWWE_MISC_IDDQ_SW_VAWUE;
	vaw |= PWWE_MISC_PWWE_PTS;
	vaw &= ~(PWWE_MISC_VWEG_BG_CTWW_MASK | PWWE_MISC_VWEG_CTWW_MASK);
	pww_wwitew_misc(vaw, pww);
	udeway(5);

	vaw = pww_weadw(PWWE_SS_CTWW, pww);
	vaw |= PWWE_SS_DISABWE;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);

	vaw = pww_weadw_base(pww);
	vaw &= ~(divp_mask_shifted(pww) | divn_mask_shifted(pww) |
		 divm_mask_shifted(pww));
	vaw &= ~(PWWE_BASE_DIVCMW_MASK << PWWE_BASE_DIVCMW_SHIFT);
	vaw |= sew.m << divm_shift(pww);
	vaw |= sew.n << divn_shift(pww);
	vaw |= sew.cpcon << PWWE_BASE_DIVCMW_SHIFT;
	pww_wwitew_base(vaw, pww);
	udeway(1);

	_cwk_pww_enabwe(hw);
	wet = cwk_pww_wait_fow_wock(pww);

	if (wet < 0)
		goto out;

	vaw = pww_weadw(PWWE_SS_CTWW, pww);
	vaw &= ~(PWWE_SS_CNTW_CENTEW | PWWE_SS_CNTW_INVEWT);
	vaw &= ~PWWE_SS_COEFFICIENTS_MASK;
	vaw |= PWWE_SS_COEFFICIENTS_VAW_TEGWA114;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	vaw &= ~(PWWE_SS_CNTW_SSC_BYP | PWWE_SS_CNTW_BYPASS_SS);
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	udeway(1);
	vaw &= ~PWWE_SS_CNTW_INTEWP_WESET;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	udeway(1);

	/* Enabwe HW contwow of XUSB bwick PWW */
	vaw = pww_weadw_misc(pww);
	vaw &= ~PWWE_MISC_IDDQ_SW_CTWW;
	pww_wwitew_misc(vaw, pww);

	vaw = pww_weadw(pww->pawams->aux_weg, pww);
	vaw |= (PWWE_AUX_USE_WOCKDET | PWWE_AUX_SEQ_STAWT_STATE);
	vaw &= ~(PWWE_AUX_ENABWE_SWCTW | PWWE_AUX_SS_SWCTW);
	pww_wwitew(vaw, pww->pawams->aux_weg, pww);
	udeway(1);
	vaw |= PWWE_AUX_SEQ_ENABWE;
	pww_wwitew(vaw, pww->pawams->aux_weg, pww);

	vaw = pww_weadw(XUSBIO_PWW_CFG0, pww);
	vaw |= (XUSBIO_PWW_CFG0_PADPWW_USE_WOCKDET |
		XUSBIO_PWW_CFG0_SEQ_STAWT_STATE);
	vaw &= ~(XUSBIO_PWW_CFG0_CWK_ENABWE_SWCTW |
		 XUSBIO_PWW_CFG0_PADPWW_WESET_SWCTW);
	pww_wwitew(vaw, XUSBIO_PWW_CFG0, pww);
	udeway(1);
	vaw |= XUSBIO_PWW_CFG0_SEQ_ENABWE;
	pww_wwitew(vaw, XUSBIO_PWW_CFG0, pww);

	/* Enabwe HW contwow of SATA PWW */
	vaw = pww_weadw(SATA_PWW_CFG0, pww);
	vaw &= ~SATA_PWW_CFG0_PADPWW_WESET_SWCTW;
	vaw |= SATA_PWW_CFG0_PADPWW_USE_WOCKDET;
	vaw |= SATA_PWW_CFG0_SEQ_STAWT_STATE;
	pww_wwitew(vaw, SATA_PWW_CFG0, pww);

	udeway(1);

	vaw = pww_weadw(SATA_PWW_CFG0, pww);
	vaw |= SATA_PWW_CFG0_SEQ_ENABWE;
	pww_wwitew(vaw, SATA_PWW_CFG0, pww);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void cwk_pwwe_tegwa114_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	_cwk_pww_disabwe(hw);

	vaw = pww_weadw_misc(pww);
	vaw |= PWWE_MISC_IDDQ_SW_CTWW | PWWE_MISC_IDDQ_SW_VAWUE;
	pww_wwitew_misc(vaw, pww);
	udeway(1);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static int cwk_pwwu_tegwa114_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct utmi_cwk_pawam *pawams = NUWW;
	stwuct cwk *osc = __cwk_wookup("osc");
	unsigned wong fwags = 0, input_wate;
	unsigned int i;
	int wet = 0;
	u32 vawue;

	if (!osc) {
		pw_eww("%s: faiwed to get OSC cwock\n", __func__);
		wetuwn -EINVAW;
	}

	input_wate = cwk_hw_get_wate(__cwk_get_hw(osc));

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	if (!cwk_pww_is_enabwed(hw))
		_cwk_pww_enabwe(hw);

	wet = cwk_pww_wait_fow_wock(pww);
	if (wet < 0)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(utmi_pawametews); i++) {
		if (input_wate == utmi_pawametews[i].osc_fwequency) {
			pawams = &utmi_pawametews[i];
			bweak;
		}
	}

	if (!pawams) {
		pw_eww("%s: unexpected input wate %wu Hz\n", __func__,
		       input_wate);
		wet = -EINVAW;
		goto out;
	}

	vawue = pww_weadw_base(pww);
	vawue &= ~PWWU_BASE_OVEWWIDE;
	pww_wwitew_base(vawue, pww);

	vawue = weadw_wewaxed(pww->cwk_base + UTMIP_PWW_CFG2);
	/* Pwogwam UTMIP PWW stabwe and active counts */
	vawue &= ~UTMIP_PWW_CFG2_STABWE_COUNT(~0);
	vawue |= UTMIP_PWW_CFG2_STABWE_COUNT(pawams->stabwe_count);
	vawue &= ~UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(~0);
	vawue |= UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(pawams->active_deway_count);
	/* Wemove powew downs fwom UTMIP PWW contwow bits */
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWDOWN;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIP_PWW_CFG2);

	vawue = weadw_wewaxed(pww->cwk_base + UTMIP_PWW_CFG1);
	/* Pwogwam UTMIP PWW deway and osciwwatow fwequency counts */
	vawue &= ~UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(~0);
	vawue |= UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(pawams->enabwe_deway_count);
	vawue &= ~UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(~0);
	vawue |= UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(pawams->xtaw_fweq_count);
	/* Wemove powew downs fwom UTMIP PWW contwow bits */
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ACTIVE_POWEWDOWN;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWUP;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWDOWN;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIP_PWW_CFG1);

	/* Setup HW contwow of UTMIPWW */
	vawue = weadw_wewaxed(pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	vawue |= UTMIPWW_HW_PWWDN_CFG0_USE_WOCKDET;
	vawue &= ~UTMIPWW_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW;
	vawue |= UTMIPWW_HW_PWWDN_CFG0_SEQ_STAWT_STATE;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);

	vawue = weadw_wewaxed(pww->cwk_base + UTMIP_PWW_CFG1);
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWUP;
	vawue &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIP_PWW_CFG1);

	udeway(1);

	/*
	 * Setup SW ovewwide of UTMIPWW assuming USB2.0 powts awe assigned
	 * to USB2
	 */
	vawue = weadw_wewaxed(pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	vawue |= UTMIPWW_HW_PWWDN_CFG0_IDDQ_SWCTW;
	vawue &= ~UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);

	udeway(1);

	/* Enabwe HW contwow of UTMIPWW */
	vawue = weadw_wewaxed(pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	vawue |= UTMIPWW_HW_PWWDN_CFG0_SEQ_ENABWE;
	wwitew_wewaxed(vawue, pww->cwk_base + UTMIPWW_HW_PWWDN_CFG0);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void _cwk_pwwe_tegwa_init_pawent(stwuct tegwa_cwk_pww *pww)
{
	u32 vaw, vaw_aux;

	/* ensuwe pawent is set to pww_wef */
	vaw = pww_weadw_base(pww);
	vaw_aux = pww_weadw(pww->pawams->aux_weg, pww);

	if (vaw & PWW_BASE_ENABWE) {
		if ((vaw_aux & PWWE_AUX_PWWWE_SEW) ||
		    (vaw_aux & PWWE_AUX_PWWP_SEW))
			WAWN(1, "pww_e enabwed with unsuppowted pawent %s\n",
			     (vaw_aux & PWWE_AUX_PWWP_SEW) ? "pwwp_out0" :
			     "pww_we_vco");
	} ewse {
		vaw_aux &= ~(PWWE_AUX_PWWWE_SEW | PWWE_AUX_PWWP_SEW);
		pww_wwitew(vaw_aux, pww->pawams->aux_weg, pww);
		fence_udeway(1, pww->cwk_base);
	}
}
#endif

static stwuct tegwa_cwk_pww *_tegwa_init_pww(void __iomem *cwk_base,
		void __iomem *pmc, stwuct tegwa_cwk_pww_pawams *pww_pawams,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->cwk_base = cwk_base;
	pww->pmc = pmc;

	pww->pawams = pww_pawams;
	pww->wock = wock;

	if (!pww_pawams->div_nmp)
		pww_pawams->div_nmp = &defauwt_nmp;

	wetuwn pww;
}

static stwuct cwk *_tegwa_cwk_wegistew_pww(stwuct tegwa_cwk_pww *pww,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		const stwuct cwk_ops *ops)
{
	stwuct cwk_init_data init;

	init.name = name;
	init.ops = ops;
	init.fwags = fwags;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	/* Defauwt to _cawc_wate if unspecified */
	if (!pww->pawams->cawc_wate) {
		if (pww->pawams->fwags & TEGWA_PWWM)
			pww->pawams->cawc_wate = _cawc_dynamic_wamp_wate;
		ewse
			pww->pawams->cawc_wate = _cawc_wate;
	}

	if (pww->pawams->set_defauwts)
		pww->pawams->set_defauwts(pww);

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	pww->hw.init = &init;

	wetuwn tegwa_cwk_dev_wegistew(&pww->hw);
}

stwuct cwk *tegwa_cwk_wegistew_pww(const chaw *name, const chaw *pawent_name,
		void __iomem *cwk_base, void __iomem *pmc,
		unsigned wong fwags, stwuct tegwa_cwk_pww_pawams *pww_pawams,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;

	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pww_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

static stwuct div_nmp pww_e_nmp = {
	.divn_shift = PWWE_BASE_DIVN_SHIFT,
	.divn_width = PWWE_BASE_DIVN_WIDTH,
	.divm_shift = PWWE_BASE_DIVM_SHIFT,
	.divm_width = PWWE_BASE_DIVM_WIDTH,
	.divp_shift = PWWE_BASE_DIVP_SHIFT,
	.divp_width = PWWE_BASE_DIVP_WIDTH,
};

stwuct cwk *tegwa_cwk_wegistew_pwwe(const chaw *name, const chaw *pawent_name,
		void __iomem *cwk_base, void __iomem *pmc,
		unsigned wong fwags, stwuct tegwa_cwk_pww_pawams *pww_pawams,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;

	if (!pww_pawams->div_nmp)
		pww_pawams->div_nmp = &pww_e_nmp;

	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwe_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwu(const chaw *name, const chaw *pawent_name,
		void __iomem *cwk_base, unsigned wong fwags,
		stwuct tegwa_cwk_pww_pawams *pww_pawams, spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->fwags |= TEGWA_PWWU;

	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwu_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

#if defined(CONFIG_AWCH_TEGWA_114_SOC) || \
	defined(CONFIG_AWCH_TEGWA_124_SOC) || \
	defined(CONFIG_AWCH_TEGWA_132_SOC) || \
	defined(CONFIG_AWCH_TEGWA_210_SOC)
static const stwuct cwk_ops tegwa_cwk_pwwxc_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wamp_wound_wate,
	.set_wate = cwk_pwwxc_set_wate,
};

static const stwuct cwk_ops tegwa_cwk_pwwc_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pwwc_enabwe,
	.disabwe = cwk_pwwc_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wamp_wound_wate,
	.set_wate = cwk_pwwc_set_wate,
};

static const stwuct cwk_ops tegwa_cwk_pwwwe_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pwwwe_wecawc_wate,
	.wound_wate = cwk_pwwwe_wound_wate,
	.set_wate = cwk_pwwwe_set_wate,
};

static const stwuct cwk_ops tegwa_cwk_pwwe_tegwa114_ops = {
	.is_enabwed =  cwk_pww_is_enabwed,
	.enabwe = cwk_pwwe_tegwa114_enabwe,
	.disabwe = cwk_pwwe_tegwa114_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
};

static const stwuct cwk_ops tegwa_cwk_pwwu_tegwa114_ops = {
	.is_enabwed =  cwk_pww_is_enabwed,
	.enabwe = cwk_pwwu_tegwa114_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
};

stwuct cwk *tegwa_cwk_wegistew_pwwxc(const chaw *name, const chaw *pawent_name,
			  void __iomem *cwk_base, void __iomem *pmc,
			  unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk, *pawent;
	unsigned wong pawent_wate;
	u32 vaw, vaw_iddq;

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			pawent_name, name);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!pww_pawams->pdiv_tohw)
		wetuwn EWW_PTW(-EINVAW);

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	/*
	 * If the pww has a set_defauwts cawwback, it wiww take cawe of
	 * configuwing dynamic wamping and setting IDDQ in that path.
	 */
	if (!pww_pawams->set_defauwts) {
		int eww;

		eww = _setup_dynamic_wamp(pww_pawams, cwk_base, pawent_wate);
		if (eww)
			wetuwn EWW_PTW(eww);

		vaw = weadw_wewaxed(cwk_base + pww_pawams->base_weg);
		vaw_iddq = weadw_wewaxed(cwk_base + pww_pawams->iddq_weg);

		if (vaw & PWW_BASE_ENABWE)
			WAWN_ON(vaw_iddq & BIT(pww_pawams->iddq_bit_idx));
		ewse {
			vaw_iddq |= BIT(pww_pawams->iddq_bit_idx);
			wwitew_wewaxed(vaw_iddq,
				       cwk_base + pww_pawams->iddq_weg);
		}
	}

	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwxc_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwwe(const chaw *name, const chaw *pawent_name,
			  void __iomem *cwk_base, void __iomem *pmc,
			  unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock, unsigned wong pawent_wate)
{
	u32 vaw;
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	/* pwogwam minimum wate by defauwt */

	vaw = pww_weadw_base(pww);
	if (vaw & PWW_BASE_ENABWE)
		WAWN_ON(weadw_wewaxed(cwk_base + pww_pawams->iddq_weg) &
				BIT(pww_pawams->iddq_bit_idx));
	ewse {
		int m;

		m = _pww_fixed_mdiv(pww_pawams, pawent_wate);
		vaw = m << divm_shift(pww);
		vaw |= (pww_pawams->vco_min / pawent_wate) << divn_shift(pww);
		pww_wwitew_base(vaw, pww);
	}

	/* disabwe wock ovewwide */

	vaw = pww_weadw_misc(pww);
	vaw &= ~BIT(29);
	pww_wwitew_misc(vaw, pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwwe_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwm(const chaw *name, const chaw *pawent_name,
			  void __iomem *cwk_base, void __iomem *pmc,
			  unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk, *pawent;
	unsigned wong pawent_wate;

	if (!pww_pawams->pdiv_tohw)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			pawent_name, name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;
	pww_pawams->fwags |= TEGWA_PWWM;
	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pww_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwc(const chaw *name, const chaw *pawent_name,
			  void __iomem *cwk_base, void __iomem *pmc,
			  unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock)
{
	stwuct cwk *pawent, *cwk;
	const stwuct pdiv_map *p_tohw = pww_pawams->pdiv_tohw;
	stwuct tegwa_cwk_pww *pww;
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;
	unsigned wong pawent_wate;

	if (!p_tohw)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			pawent_name, name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;
	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	/*
	 * Most of PWWC wegistew fiewds awe shadowed, and can not be wead
	 * diwectwy fwom PWW h/w. Hence, actuaw PWWC boot state is unknown.
	 * Initiawize PWW to defauwt state: disabwed, weset; shadow wegistews
	 * woaded with defauwt pawametews; dividews awe pweset fow hawf of
	 * minimum VCO wate (the wattew assuwed that shadowed dividew settings
	 * awe within suppowted wange).
	 */

	cfg.m = _pww_fixed_mdiv(pww_pawams, pawent_wate);
	cfg.n = cfg.m * pww_pawams->vco_min / pawent_wate;

	whiwe (p_tohw->pdiv) {
		if (p_tohw->pdiv == 2) {
			cfg.p = p_tohw->hw_vaw;
			bweak;
		}
		p_tohw++;
	}

	if (!p_tohw->pdiv) {
		WAWN_ON(1);
		wetuwn EWW_PTW(-EINVAW);
	}

	pww_wwitew_base(0, pww);
	_update_pww_mnp(pww, &cfg);

	pww_wwitew_misc(PWWCX_MISC_DEFAUWT, pww);
	pww_wwitew(PWWCX_MISC1_DEFAUWT, pww_pawams->ext_misc_weg[0], pww);
	pww_wwitew(PWWCX_MISC2_DEFAUWT, pww_pawams->ext_misc_weg[1], pww);
	pww_wwitew(PWWCX_MISC3_DEFAUWT, pww_pawams->ext_misc_weg[2], pww);

	_pwwcx_update_dynamic_coef(pww, pawent_wate, cfg.n);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwc_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwe_tegwa114(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	_cwk_pwwe_tegwa_init_pawent(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwe_tegwa114_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *
tegwa_cwk_wegistew_pwwu_tegwa114(const chaw *name, const chaw *pawent_name,
				 void __iomem *cwk_base, unsigned wong fwags,
				 stwuct tegwa_cwk_pww_pawams *pww_pawams,
				 spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->fwags |= TEGWA_PWWU;

	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwu_tegwa114_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}
#endif

#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC) || defined(CONFIG_AWCH_TEGWA_210_SOC)
static const stwuct cwk_ops tegwa_cwk_pwwss_ops = {
	.is_enabwed = cwk_pww_is_enabwed,
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wamp_wound_wate,
	.set_wate = cwk_pwwxc_set_wate,
	.westowe_context = tegwa_cwk_pww_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_pwwss(const chaw *name, const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk, *pawent;
	stwuct tegwa_cwk_pww_fweq_tabwe cfg;
	unsigned wong pawent_wate;
	u32 vaw, vaw_iddq;
	int i;

	if (!pww_pawams->div_nmp)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			pawent_name, name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	vaw = pww_weadw_base(pww);
	vaw &= ~PWWSS_WEF_SWC_SEW_MASK;
	pww_wwitew_base(vaw, pww);

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	/* initiawize PWW to minimum wate */

	cfg.m = _pww_fixed_mdiv(pww_pawams, pawent_wate);
	cfg.n = cfg.m * pww_pawams->vco_min / pawent_wate;

	fow (i = 0; pww_pawams->pdiv_tohw[i].pdiv; i++)
		;
	if (!i) {
		kfwee(pww);
		wetuwn EWW_PTW(-EINVAW);
	}

	cfg.p = pww_pawams->pdiv_tohw[i-1].hw_vaw;

	_update_pww_mnp(pww, &cfg);

	pww_wwitew_misc(PWWSS_MISC_DEFAUWT, pww);
	pww_wwitew(PWWSS_CFG_DEFAUWT, pww_pawams->ext_misc_weg[0], pww);
	pww_wwitew(PWWSS_CTWW1_DEFAUWT, pww_pawams->ext_misc_weg[1], pww);
	pww_wwitew(PWWSS_CTWW1_DEFAUWT, pww_pawams->ext_misc_weg[2], pww);

	vaw = pww_weadw_base(pww);
	vaw_iddq = weadw_wewaxed(cwk_base + pww_pawams->iddq_weg);
	if (vaw & PWW_BASE_ENABWE) {
		if (vaw_iddq & BIT(pww_pawams->iddq_bit_idx)) {
			WAWN(1, "%s is on but IDDQ set\n", name);
			kfwee(pww);
			wetuwn EWW_PTW(-EINVAW);
		}
	} ewse {
		vaw_iddq |= BIT(pww_pawams->iddq_bit_idx);
		wwitew_wewaxed(vaw_iddq, cwk_base + pww_pawams->iddq_weg);
	}

	vaw &= ~PWWSS_WOCK_OVEWWIDE;
	pww_wwitew_base(vaw, pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
					&tegwa_cwk_pwwss_ops);

	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}
#endif

#if defined(CONFIG_AWCH_TEGWA_210_SOC)
stwuct cwk *tegwa_cwk_wegistew_pwwwe_tegwa210(const chaw *name,
			  const chaw *pawent_name, void __iomem *cwk_base,
			  void __iomem *pmc, unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock, unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pww_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

static int cwk_pwwe_tegwa210_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	u32 vaw;

	vaw = pww_weadw_base(pww);

	wetuwn vaw & PWWE_BASE_ENABWE ? 1 : 0;
}

static int cwk_pwwe_tegwa210_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_fweq_tabwe sew;
	u32 vaw;
	int wet = 0;
	unsigned wong fwags = 0;
	unsigned wong input_wate;

	if (cwk_pwwe_tegwa210_is_enabwed(hw))
		wetuwn 0;

	input_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));

	if (_get_tabwe_wate(hw, &sew, pww->pawams->fixed_wate, input_wate))
		wetuwn -EINVAW;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	vaw = pww_weadw(pww->pawams->aux_weg, pww);
	if (vaw & PWWE_AUX_SEQ_ENABWE)
		goto out;

	vaw = pww_weadw_base(pww);
	vaw &= ~BIT(30); /* Disabwe wock ovewwide */
	pww_wwitew_base(vaw, pww);

	vaw = pww_weadw_misc(pww);
	vaw |= PWWE_MISC_WOCK_ENABWE;
	vaw |= PWWE_MISC_IDDQ_SW_CTWW;
	vaw &= ~PWWE_MISC_IDDQ_SW_VAWUE;
	vaw |= PWWE_MISC_PWWE_PTS;
	vaw &= ~(PWWE_MISC_VWEG_BG_CTWW_MASK | PWWE_MISC_VWEG_CTWW_MASK);
	pww_wwitew_misc(vaw, pww);
	udeway(5);

	vaw = pww_weadw(PWWE_SS_CTWW, pww);
	vaw |= PWWE_SS_DISABWE;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);

	vaw = pww_weadw_base(pww);
	vaw &= ~(divp_mask_shifted(pww) | divn_mask_shifted(pww) |
		 divm_mask_shifted(pww));
	vaw &= ~(PWWE_BASE_DIVCMW_MASK << PWWE_BASE_DIVCMW_SHIFT);
	vaw |= sew.m << divm_shift(pww);
	vaw |= sew.n << divn_shift(pww);
	vaw |= sew.cpcon << PWWE_BASE_DIVCMW_SHIFT;
	pww_wwitew_base(vaw, pww);
	udeway(1);

	vaw = pww_weadw_base(pww);
	vaw |= PWWE_BASE_ENABWE;
	pww_wwitew_base(vaw, pww);

	wet = cwk_pww_wait_fow_wock(pww);

	if (wet < 0)
		goto out;

	vaw = pww_weadw(PWWE_SS_CTWW, pww);
	vaw &= ~(PWWE_SS_CNTW_CENTEW | PWWE_SS_CNTW_INVEWT);
	vaw &= ~PWWE_SS_COEFFICIENTS_MASK;
	vaw |= PWWE_SS_COEFFICIENTS_VAW_TEGWA210;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	vaw &= ~(PWWE_SS_CNTW_SSC_BYP | PWWE_SS_CNTW_BYPASS_SS);
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	udeway(1);
	vaw &= ~PWWE_SS_CNTW_INTEWP_WESET;
	pww_wwitew(vaw, PWWE_SS_CTWW, pww);
	udeway(1);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void cwk_pwwe_tegwa210_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	/* If PWWE HW sequencew is enabwed, SW shouwd not disabwe PWWE */
	vaw = pww_weadw(pww->pawams->aux_weg, pww);
	if (vaw & PWWE_AUX_SEQ_ENABWE)
		goto out;

	vaw = pww_weadw_base(pww);
	vaw &= ~PWWE_BASE_ENABWE;
	pww_wwitew_base(vaw, pww);

	vaw = pww_weadw(pww->pawams->aux_weg, pww);
	vaw |= PWWE_AUX_ENABWE_SWCTW | PWWE_AUX_SS_SWCTW;
	pww_wwitew(vaw, pww->pawams->aux_weg, pww);

	vaw = pww_weadw_misc(pww);
	vaw |= PWWE_MISC_IDDQ_SW_CTWW | PWWE_MISC_IDDQ_SW_VAWUE;
	pww_wwitew_misc(vaw, pww);
	udeway(1);

out:
	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static void tegwa_cwk_pwwe_t210_westowe_context(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);

	_cwk_pwwe_tegwa_init_pawent(pww);
}

static const stwuct cwk_ops tegwa_cwk_pwwe_tegwa210_ops = {
	.is_enabwed =  cwk_pwwe_tegwa210_is_enabwed,
	.enabwe = cwk_pwwe_tegwa210_enabwe,
	.disabwe = cwk_pwwe_tegwa210_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.westowe_context = tegwa_cwk_pwwe_t210_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_pwwe_tegwa210(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk;

	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	_cwk_pwwe_tegwa_init_pawent(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pwwe_tegwa210_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwc_tegwa210(const chaw *name,
			const chaw *pawent_name, void __iomem *cwk_base,
			void __iomem *pmc, unsigned wong fwags,
			stwuct tegwa_cwk_pww_pawams *pww_pawams,
			spinwock_t *wock)
{
	stwuct cwk *pawent, *cwk;
	const stwuct pdiv_map *p_tohw = pww_pawams->pdiv_tohw;
	stwuct tegwa_cwk_pww *pww;
	unsigned wong pawent_wate;

	if (!p_tohw)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			name, pawent_name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;
	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pww_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwss_tegwa210(const chaw *name,
				const chaw *pawent_name, void __iomem *cwk_base,
				unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk, *pawent;
	unsigned wong pawent_wate;
	u32 vaw;

	if (!pww_pawams->div_nmp)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			name, pawent_name);
		wetuwn EWW_PTW(-EINVAW);
	}

	vaw = weadw_wewaxed(cwk_base + pww_pawams->base_weg);
	if (vaw & PWWSS_WEF_SWC_SEW_MASK) {
		WAWN(1, "not suppowted wefewence cwock fow %s\n", name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;
	pww = _tegwa_init_pww(cwk_base, NUWW, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
					&tegwa_cwk_pww_ops);

	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_pwwmb(const chaw *name, const chaw *pawent_name,
			  void __iomem *cwk_base, void __iomem *pmc,
			  unsigned wong fwags,
			  stwuct tegwa_cwk_pww_pawams *pww_pawams,
			  spinwock_t *wock)
{
	stwuct tegwa_cwk_pww *pww;
	stwuct cwk *cwk, *pawent;
	unsigned wong pawent_wate;

	if (!pww_pawams->pdiv_tohw)
		wetuwn EWW_PTW(-EINVAW);

	pawent = __cwk_wookup(pawent_name);
	if (!pawent) {
		WAWN(1, "pawent cwk %s of %s must be wegistewed fiwst\n",
			pawent_name, name);
		wetuwn EWW_PTW(-EINVAW);
	}

	pawent_wate = cwk_get_wate(pawent);

	pww_pawams->vco_min = _cwip_vco_min(pww_pawams->vco_min, pawent_wate);

	if (pww_pawams->adjust_vco)
		pww_pawams->vco_min = pww_pawams->adjust_vco(pww_pawams,
							     pawent_wate);

	pww_pawams->fwags |= TEGWA_PWW_BYPASS;
	pww_pawams->fwags |= TEGWA_PWWMB;
	pww = _tegwa_init_pww(cwk_base, pmc, pww_pawams, wock);
	if (IS_EWW(pww))
		wetuwn EWW_CAST(pww);

	cwk = _tegwa_cwk_wegistew_pww(pww, name, pawent_name, fwags,
				      &tegwa_cwk_pww_ops);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

#endif
