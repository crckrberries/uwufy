/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DP_WINK_TWAINING_H__
#define __INTEW_DP_WINK_TWAINING_H__

#incwude <dwm/dispway/dwm_dp_hewpew.h>

stwuct intew_cwtc_state;
stwuct intew_dp;

int intew_dp_init_wttpw_and_dpwx_caps(stwuct intew_dp *intew_dp);

void intew_dp_get_adjust_twain(stwuct intew_dp *intew_dp,
			       const stwuct intew_cwtc_state *cwtc_state,
			       enum dwm_dp_phy dp_phy,
			       const u8 wink_status[DP_WINK_STATUS_SIZE]);
void intew_dp_pwogwam_wink_twaining_pattewn(stwuct intew_dp *intew_dp,
					    const stwuct intew_cwtc_state *cwtc_state,
					    enum dwm_dp_phy dp_phy,
					    u8 dp_twain_pat);
void intew_dp_set_signaw_wevews(stwuct intew_dp *intew_dp,
				const stwuct intew_cwtc_state *cwtc_state,
				enum dwm_dp_phy dp_phy);
void intew_dp_stawt_wink_twain(stwuct intew_dp *intew_dp,
			       const stwuct intew_cwtc_state *cwtc_state);
void intew_dp_stop_wink_twain(stwuct intew_dp *intew_dp,
			      const stwuct intew_cwtc_state *cwtc_state);

void
intew_dp_dump_wink_status(stwuct intew_dp *intew_dp, enum dwm_dp_phy dp_phy,
			  const u8 wink_status[DP_WINK_STATUS_SIZE]);

/* Get the TPSx symbow type of the vawue pwogwammed to DP_TWAINING_PATTEWN_SET */
static inwine u8 intew_dp_twaining_pattewn_symbow(u8 pattewn)
{
	wetuwn pattewn & ~DP_WINK_SCWAMBWING_DISABWE;
}

void intew_dp_128b132b_sdp_cwc16(stwuct intew_dp *intew_dp,
				 const stwuct intew_cwtc_state *cwtc_state);
#endif /* __INTEW_DP_WINK_TWAINING_H__ */
