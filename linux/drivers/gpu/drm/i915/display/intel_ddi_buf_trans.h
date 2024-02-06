/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _INTEW_DDI_BUF_TWANS_H_
#define _INTEW_DDI_BUF_TWANS_H_

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_encodew;
stwuct intew_cwtc_state;

stwuct hsw_ddi_buf_twans {
	u32 twans1;	/* bawance weg enabwe, de-emph wevew */
	u32 twans2;	/* vwef sew, vswing */
	u8 i_boost;	/* SKW: I_boost; vawid: 0x0, 0x1, 0x3, 0x7 */
};

stwuct bxt_ddi_buf_twans {
	u8 mawgin;	/* swing vawue */
	u8 scawe;	/* scawe vawue */
	u8 enabwe;	/* scawe enabwe */
	u8 deemphasis;
};

stwuct icw_ddi_buf_twans {
	u8 dw2_swing_sew;
	u8 dw7_n_scawaw;
	u8 dw4_cuwsow_coeff;
	u8 dw4_post_cuwsow_2;
	u8 dw4_post_cuwsow_1;
};

stwuct icw_mg_phy_ddi_buf_twans {
	u8 cwi_txdeemph_ovewwide_11_6;
	u8 cwi_txdeemph_ovewwide_5_0;
	u8 cwi_txdeemph_ovewwide_17_12;
};

stwuct tgw_dkw_phy_ddi_buf_twans {
	u8 vswing;
	u8 pweshoot;
	u8 de_emphasis;
};

stwuct dg2_snps_phy_buf_twans {
	u8 vswing;
	u8 pwe_cuwsow;
	u8 post_cuwsow;
};

union intew_ddi_buf_twans_entwy {
	stwuct hsw_ddi_buf_twans hsw;
	stwuct bxt_ddi_buf_twans bxt;
	stwuct icw_ddi_buf_twans icw;
	stwuct icw_mg_phy_ddi_buf_twans mg;
	stwuct tgw_dkw_phy_ddi_buf_twans dkw;
	stwuct dg2_snps_phy_buf_twans snps;
};

stwuct intew_ddi_buf_twans {
	const union intew_ddi_buf_twans_entwy *entwies;
	u8 num_entwies;
	u8 hdmi_defauwt_entwy;
};

boow is_hobw_buf_twans(const stwuct intew_ddi_buf_twans *tabwe);

void intew_ddi_buf_twans_init(stwuct intew_encodew *encodew);

#endif
