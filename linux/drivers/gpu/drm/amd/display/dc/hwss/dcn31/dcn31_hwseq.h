/*
* Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCN31_H__
#define __DC_HWSS_DCN31_H__

#incwude "hw_sequencew_pwivate.h"

stwuct dc;

void dcn31_init_hw(stwuct dc *dc);

void dcn31_dsc_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst,
		boow powew_on);

void dcn31_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe);

void dcn31_update_info_fwame(stwuct pipe_ctx *pipe_ctx);

void dcn31_z10_westowe(const stwuct dc *dc);
void dcn31_z10_save_init(stwuct dc *dc);

void dcn31_hubp_pg_contwow(stwuct dce_hwseq *hws, unsigned int hubp_inst, boow powew_on);
int dcn31_init_sys_ctx(stwuct dce_hwseq *hws, stwuct dc *dc, stwuct dc_phy_addw_space_config *pa_config);
void dcn31_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context);
boow dcn31_is_abm_suppowted(stwuct dc *dc,
		stwuct dc_state *context, stwuct dc_stweam_state *stweam);
void dcn31_init_pipes(stwuct dc *dc, stwuct dc_state *context);
void dcn31_setup_hpo_hw_contwow(const stwuct dce_hwseq *hws, boow enabwe);

#endif /* __DC_HWSS_DCN31_H__ */
