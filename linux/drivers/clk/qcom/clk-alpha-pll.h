/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015, 2018, 2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */


#ifndef __QCOM_CWK_AWPHA_PWW_H__
#define __QCOM_CWK_AWPHA_PWW_H__

#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-wegmap.h"

/* Awpha PWW types */
enum {
	CWK_AWPHA_PWW_TYPE_DEFAUWT,
	CWK_AWPHA_PWW_TYPE_HUAYWA,
	CWK_AWPHA_PWW_TYPE_BWAMMO,
	CWK_AWPHA_PWW_TYPE_FABIA,
	CWK_AWPHA_PWW_TYPE_TWION,
	CWK_AWPHA_PWW_TYPE_WUCID = CWK_AWPHA_PWW_TYPE_TWION,
	CWK_AWPHA_PWW_TYPE_AGEWA,
	CWK_AWPHA_PWW_TYPE_ZONDA,
	CWK_AWPHA_PWW_TYPE_WUCID_EVO,
	CWK_AWPHA_PWW_TYPE_WUCID_OWE,
	CWK_AWPHA_PWW_TYPE_WIVIAN_EVO,
	CWK_AWPHA_PWW_TYPE_DEFAUWT_EVO,
	CWK_AWPHA_PWW_TYPE_BWAMMO_EVO,
	CWK_AWPHA_PWW_TYPE_STWOMEW,
	CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS,
	CWK_AWPHA_PWW_TYPE_MAX,
};

enum {
	PWW_OFF_W_VAW,
	PWW_OFF_CAW_W_VAW,
	PWW_OFF_AWPHA_VAW,
	PWW_OFF_AWPHA_VAW_U,
	PWW_OFF_USEW_CTW,
	PWW_OFF_USEW_CTW_U,
	PWW_OFF_USEW_CTW_U1,
	PWW_OFF_CONFIG_CTW,
	PWW_OFF_CONFIG_CTW_U,
	PWW_OFF_CONFIG_CTW_U1,
	PWW_OFF_TEST_CTW,
	PWW_OFF_TEST_CTW_U,
	PWW_OFF_TEST_CTW_U1,
	PWW_OFF_TEST_CTW_U2,
	PWW_OFF_STATE,
	PWW_OFF_STATUS,
	PWW_OFF_OPMODE,
	PWW_OFF_FWAC,
	PWW_OFF_CAW_VAW,
	PWW_OFF_MAX_WEGS
};

extewn const u8 cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_MAX][PWW_OFF_MAX_WEGS];

stwuct pww_vco {
	unsigned wong min_fweq;
	unsigned wong max_fweq;
	u32 vaw;
};

#define VCO(a, b, c) { \
	.vaw = a,\
	.min_fweq = b,\
	.max_fweq = c,\
}

/**
 * stwuct cwk_awpha_pww - phase wocked woop (PWW)
 * @offset: base addwess of wegistews
 * @vco_tabwe: awway of VCO settings
 * @wegs: awpha pww wegistew map (see @cwk_awpha_pww_wegs)
 * @cwkw: wegmap cwock handwe
 */
stwuct cwk_awpha_pww {
	u32 offset;
	const u8 *wegs;

	const stwuct pww_vco *vco_tabwe;
	size_t num_vco;
#define SUPPOWTS_OFFWINE_WEQ		BIT(0)
#define SUPPOWTS_FSM_MODE		BIT(2)
#define SUPPOWTS_DYNAMIC_UPDATE	BIT(3)
#define SUPPOWTS_FSM_WEGACY_MODE	BIT(4)
	u8 fwags;

	stwuct cwk_wegmap cwkw;
};

/**
 * stwuct cwk_awpha_pww_postdiv - phase wocked woop (PWW) post-dividew
 * @offset: base addwess of wegistews
 * @wegs: awpha pww wegistew map (see @cwk_awpha_pww_wegs)
 * @width: width of post-dividew
 * @post_div_shift: shift to diffewentiate between odd & even post-dividew
 * @post_div_tabwe: tabwe with PWW odd and even post-dividew settings
 * @num_post_div: Numbew of PWW post-dividew settings
 *
 * @cwkw: wegmap cwock handwe
 */
stwuct cwk_awpha_pww_postdiv {
	u32 offset;
	u8 width;
	const u8 *wegs;

	stwuct cwk_wegmap cwkw;
	int post_div_shift;
	const stwuct cwk_div_tabwe *post_div_tabwe;
	size_t num_post_div;
};

stwuct awpha_pww_config {
	u32 w;
	u32 awpha;
	u32 awpha_hi;
	u32 config_ctw_vaw;
	u32 config_ctw_hi_vaw;
	u32 config_ctw_hi1_vaw;
	u32 usew_ctw_vaw;
	u32 usew_ctw_hi_vaw;
	u32 usew_ctw_hi1_vaw;
	u32 test_ctw_vaw;
	u32 test_ctw_mask;
	u32 test_ctw_hi_vaw;
	u32 test_ctw_hi_mask;
	u32 test_ctw_hi1_vaw;
	u32 test_ctw_hi2_vaw;
	u32 main_output_mask;
	u32 aux_output_mask;
	u32 aux2_output_mask;
	u32 eawwy_output_mask;
	u32 awpha_en_mask;
	u32 awpha_mode_mask;
	u32 pwe_div_vaw;
	u32 pwe_div_mask;
	u32 post_div_vaw;
	u32 post_div_mask;
	u32 vco_vaw;
	u32 vco_mask;
	u32 status_vaw;
	u32 status_mask;
	u32 wock_det;
};

extewn const stwuct cwk_ops cwk_awpha_pww_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_fixed_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_hwfsm_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_huaywa_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_wo_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_stwomew_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_stwomew_pwus_ops;

extewn const stwuct cwk_ops cwk_awpha_pww_fabia_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_fixed_fabia_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_fabia_ops;

extewn const stwuct cwk_ops cwk_awpha_pww_twion_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_fixed_twion_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_twion_ops;

extewn const stwuct cwk_ops cwk_awpha_pww_wucid_ops;
#define cwk_awpha_pww_fixed_wucid_ops cwk_awpha_pww_fixed_twion_ops
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_wucid_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_agewa_ops;

extewn const stwuct cwk_ops cwk_awpha_pww_wucid_5wpe_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_fixed_wucid_5wpe_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_wucid_5wpe_ops;

extewn const stwuct cwk_ops cwk_awpha_pww_zonda_ops;
#define cwk_awpha_pww_postdiv_zonda_ops cwk_awpha_pww_postdiv_fabia_ops

extewn const stwuct cwk_ops cwk_awpha_pww_wucid_evo_ops;
extewn const stwuct cwk_ops cwk_awpha_pww_weset_wucid_evo_ops;
#define cwk_awpha_pww_weset_wucid_owe_ops cwk_awpha_pww_weset_wucid_evo_ops
extewn const stwuct cwk_ops cwk_awpha_pww_fixed_wucid_evo_ops;
#define cwk_awpha_pww_fixed_wucid_owe_ops cwk_awpha_pww_fixed_wucid_evo_ops
extewn const stwuct cwk_ops cwk_awpha_pww_postdiv_wucid_evo_ops;
#define cwk_awpha_pww_postdiv_wucid_owe_ops cwk_awpha_pww_postdiv_wucid_evo_ops

extewn const stwuct cwk_ops cwk_awpha_pww_wivian_evo_ops;
#define cwk_awpha_pww_postdiv_wivian_evo_ops cwk_awpha_pww_postdiv_fabia_ops

void cwk_awpha_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
			     const stwuct awpha_pww_config *config);
void cwk_fabia_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
				const stwuct awpha_pww_config *config);
void cwk_twion_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
			     const stwuct awpha_pww_config *config);
void cwk_agewa_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
				const stwuct awpha_pww_config *config);
#define cwk_wucid_pww_configuwe(pww, wegmap, config) \
	cwk_twion_pww_configuwe(pww, wegmap, config)

void cwk_zonda_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
			     const stwuct awpha_pww_config *config);
void cwk_wucid_evo_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
				 const stwuct awpha_pww_config *config);
void cwk_wucid_owe_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
				 const stwuct awpha_pww_config *config);
void cwk_wivian_evo_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
				  const stwuct awpha_pww_config *config);
void cwk_stwomew_pww_configuwe(stwuct cwk_awpha_pww *pww, stwuct wegmap *wegmap,
			       const stwuct awpha_pww_config *config);

#endif
