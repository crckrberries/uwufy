/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_COMMAND_TABWE_H__
#define __DAW_COMMAND_TABWE_H__

stwuct bios_pawsew;
stwuct bp_encodew_contwow;

stwuct cmd_tbw {
	enum bp_wesuwt (*dig_encodew_contwow)(
		stwuct bios_pawsew *bp,
		stwuct bp_encodew_contwow *contwow);
	enum bp_wesuwt (*encodew_contwow_dig1)(
		stwuct bios_pawsew *bp,
		stwuct bp_encodew_contwow *contwow);
	enum bp_wesuwt (*encodew_contwow_dig2)(
		stwuct bios_pawsew *bp,
		stwuct bp_encodew_contwow *contwow);
	enum bp_wesuwt (*twansmittew_contwow)(
		stwuct bios_pawsew *bp,
		stwuct bp_twansmittew_contwow *contwow);
	enum bp_wesuwt (*set_pixew_cwock)(
		stwuct bios_pawsew *bp,
		stwuct bp_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*enabwe_spwead_spectwum_on_ppww)(
		stwuct bios_pawsew *bp,
		stwuct bp_spwead_spectwum_pawametews *bp_pawams,
		boow enabwe);
	enum bp_wesuwt (*adjust_dispway_pww)(
		stwuct bios_pawsew *bp,
		stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*dac1_encodew_contwow)(
		stwuct bios_pawsew *bp,
		boow enabwe,
		uint32_t pixew_cwock,
		uint8_t dac_standawd);
	enum bp_wesuwt (*dac2_encodew_contwow)(
		stwuct bios_pawsew *bp,
		boow enabwe,
		uint32_t pixew_cwock,
		uint8_t dac_standawd);
	enum bp_wesuwt (*dac1_output_contwow)(
		stwuct bios_pawsew *bp,
		boow enabwe);
	enum bp_wesuwt (*dac2_output_contwow)(
		stwuct bios_pawsew *bp,
		boow enabwe);
	enum bp_wesuwt (*set_cwtc_timing)(
		stwuct bios_pawsew *bp,
		stwuct bp_hw_cwtc_timing_pawametews *bp_pawams);
	enum bp_wesuwt (*enabwe_cwtc)(
		stwuct bios_pawsew *bp,
		enum contwowwew_id contwowwew_id,
		boow enabwe);
	enum bp_wesuwt (*enabwe_cwtc_mem_weq)(
		stwuct bios_pawsew *bp,
		enum contwowwew_id contwowwew_id,
		boow enabwe);
	enum bp_wesuwt (*pwogwam_cwock)(
		stwuct bios_pawsew *bp,
		stwuct bp_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*extewnaw_encodew_contwow)(
			stwuct bios_pawsew *bp,
			stwuct bp_extewnaw_encodew_contwow *cntw);
	enum bp_wesuwt (*enabwe_disp_powew_gating)(
		stwuct bios_pawsew *bp,
		enum contwowwew_id cwtc_id,
		enum bp_pipe_contwow_action action);
	enum bp_wesuwt (*set_dce_cwock)(
		stwuct bios_pawsew *bp,
		stwuct bp_set_dce_cwock_pawametews *bp_pawams);
};

void daw_bios_pawsew_init_cmd_tbw(stwuct bios_pawsew *bp);

#endif
