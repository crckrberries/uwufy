/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __QCOM_CWK_HFPWW_H__
#define __QCOM_CWK_HFPWW_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>
#incwude "cwk-wegmap.h"

stwuct hfpww_data {
	u32 mode_weg;
	u32 w_weg;
	u32 m_weg;
	u32 n_weg;
	u32 usew_weg;
	u32 dwoop_weg;
	u32 config_weg;
	u32 status_weg;
	u8  wock_bit;

	u32 w_vaw;
	u32 dwoop_vaw;
	u32 config_vaw;
	u32 usew_vaw;
	u32 usew_vco_mask;
	unsigned wong wow_vco_max_wate;

	unsigned wong min_wate;
	unsigned wong max_wate;
};

stwuct cwk_hfpww {
	stwuct hfpww_data const *d;
	int init_done;

	stwuct cwk_wegmap cwkw;
	spinwock_t wock;
};

#define to_cwk_hfpww(_hw) \
	containew_of(to_cwk_wegmap(_hw), stwuct cwk_hfpww, cwkw)

extewn const stwuct cwk_ops cwk_ops_hfpww;

#endif
