/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef _DCN35_PG_CNTW_H_
#define _DCN35_PG_CNTW_H_

#incwude "pg_cntw.h"

#define PG_CNTW_WEG_WIST_DCN35()\
	SW(DOMAIN0_PG_CONFIG), \
	SW(DOMAIN1_PG_CONFIG), \
	SW(DOMAIN2_PG_CONFIG), \
	SW(DOMAIN3_PG_CONFIG), \
	SW(DOMAIN16_PG_CONFIG), \
	SW(DOMAIN17_PG_CONFIG), \
	SW(DOMAIN18_PG_CONFIG), \
	SW(DOMAIN19_PG_CONFIG), \
	SW(DOMAIN22_PG_CONFIG), \
	SW(DOMAIN23_PG_CONFIG), \
	SW(DOMAIN24_PG_CONFIG), \
	SW(DOMAIN25_PG_CONFIG), \
	SW(DOMAIN0_PG_STATUS), \
	SW(DOMAIN1_PG_STATUS), \
	SW(DOMAIN2_PG_STATUS), \
	SW(DOMAIN3_PG_STATUS), \
	SW(DOMAIN16_PG_STATUS), \
	SW(DOMAIN17_PG_STATUS), \
	SW(DOMAIN18_PG_STATUS), \
	SW(DOMAIN19_PG_STATUS), \
	SW(DOMAIN22_PG_STATUS), \
	SW(DOMAIN23_PG_STATUS), \
	SW(DOMAIN24_PG_STATUS), \
	SW(DOMAIN25_PG_STATUS), \
	SW(DC_IP_WEQUEST_CNTW)

#define PG_CNTW_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define PG_CNTW_MASK_SH_WIST_DCN35(mask_sh) \
	PG_CNTW_SF(DOMAIN0_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN0_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN1_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN1_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN2_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN2_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN3_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN3_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN16_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN16_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN17_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN17_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN18_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN18_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN19_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN19_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN22_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN22_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN23_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN23_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN24_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN24_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN25_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	PG_CNTW_SF(DOMAIN25_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	PG_CNTW_SF(DOMAIN0_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN1_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN2_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN3_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN16_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN16_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN17_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN17_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN18_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN18_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN19_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN19_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN22_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN22_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN23_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN23_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN24_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN24_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DOMAIN25_PG_STATUS, DOMAIN_DESIWED_PWW_STATE, mask_sh), \
	PG_CNTW_SF(DOMAIN25_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	PG_CNTW_SF(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, mask_sh)

#define PG_CNTW_WEG_FIEWD_WIST(type) \
	type IPS2;\
	type IPS1;\
	type IPS0;\
	type IPS0_Aww

#define PG_CNTW_DCN35_WEG_FIEWD_WIST(type) \
	type IP_WEQUEST_EN; \
	type DOMAIN_POWEW_FOWCEON; \
	type DOMAIN_POWEW_GATE; \
	type DOMAIN_DESIWED_PWW_STATE; \
	type DOMAIN_PGFSM_PWW_STATUS

stwuct pg_cntw_shift {
	PG_CNTW_WEG_FIEWD_WIST(uint8_t);
	PG_CNTW_DCN35_WEG_FIEWD_WIST(uint8_t);
};

stwuct pg_cntw_mask {
	PG_CNTW_WEG_FIEWD_WIST(uint32_t);
	PG_CNTW_DCN35_WEG_FIEWD_WIST(uint32_t);
};

stwuct pg_cntw_wegistews {
	uint32_t WONO_STATE;
	uint32_t DC_IP_WEQUEST_CNTW;
	uint32_t DOMAIN0_PG_CONFIG;
	uint32_t DOMAIN1_PG_CONFIG;
	uint32_t DOMAIN2_PG_CONFIG;
	uint32_t DOMAIN3_PG_CONFIG;
	uint32_t DOMAIN16_PG_CONFIG;
	uint32_t DOMAIN17_PG_CONFIG;
	uint32_t DOMAIN18_PG_CONFIG;
	uint32_t DOMAIN19_PG_CONFIG;
	uint32_t DOMAIN22_PG_CONFIG;
	uint32_t DOMAIN23_PG_CONFIG;
	uint32_t DOMAIN24_PG_CONFIG;
	uint32_t DOMAIN25_PG_CONFIG;
	uint32_t DOMAIN0_PG_STATUS;
	uint32_t DOMAIN1_PG_STATUS;
	uint32_t DOMAIN2_PG_STATUS;
	uint32_t DOMAIN3_PG_STATUS;
	uint32_t DOMAIN16_PG_STATUS;
	uint32_t DOMAIN17_PG_STATUS;
	uint32_t DOMAIN18_PG_STATUS;
	uint32_t DOMAIN19_PG_STATUS;
	uint32_t DOMAIN22_PG_STATUS;
	uint32_t DOMAIN23_PG_STATUS;
	uint32_t DOMAIN24_PG_STATUS;
	uint32_t DOMAIN25_PG_STATUS;
};

stwuct dcn_pg_cntw {
	stwuct pg_cntw base;
	const stwuct pg_cntw_wegistews *wegs;
	const stwuct pg_cntw_shift *pg_cntw_shift;
	const stwuct pg_cntw_mask *pg_cntw_mask;
};

void pg_cntw35_dsc_pg_contwow(stwuct pg_cntw *pg_cntw, unsigned int dsc_inst, boow powew_on);
void pg_cntw35_hubp_dpp_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int hubp_dpp_inst, boow powew_on);
void pg_cntw35_hpo_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on);
void pg_cntw35_io_cwk_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on);
void pg_cntw35_pwane_otg_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on);
void pg_cntw35_mpcc_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int mpcc_inst, boow powew_on);
void pg_cntw35_opp_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int opp_inst, boow powew_on);
void pg_cntw35_optc_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int optc_inst, boow powew_on);
void pg_cntw35_dwb_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on);
void pg_cntw35_init_pg_status(stwuct pg_cntw *pg_cntw);

stwuct pg_cntw *pg_cntw35_cweate(
	stwuct dc_context *ctx,
	const stwuct pg_cntw_wegistews *wegs,
	const stwuct pg_cntw_shift *pg_cntw_shift,
	const stwuct pg_cntw_mask *pg_cntw_mask);

void dcn_pg_cntw_destwoy(stwuct pg_cntw **pg_cntw);

#endif /* DCN35_PG_CNTW */
