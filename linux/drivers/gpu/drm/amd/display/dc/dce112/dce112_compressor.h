/* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_COMPWESSOW_DCE112_H__
#define __DC_COMPWESSOW_DCE112_H__

#incwude "../inc/compwessow.h"

#define TO_DCE112_COMPWESSOW(compwessow)\
	containew_of(compwessow, stwuct dce112_compwessow, base)

stwuct dce112_compwessow_weg_offsets {
	uint32_t dcp_offset;
	uint32_t dmif_offset;
};

stwuct dce112_compwessow {
	stwuct compwessow base;
	stwuct dce112_compwessow_weg_offsets offsets;
};

stwuct compwessow *dce112_compwessow_cweate(stwuct dc_context *ctx);

void dce112_compwessow_constwuct(stwuct dce112_compwessow *cp110,
	stwuct dc_context *ctx);

void dce112_compwessow_destwoy(stwuct compwessow **cp);

/* FBC WEWATED */
void dce112_compwessow_powew_up_fbc(stwuct compwessow *cp);

void dce112_compwessow_enabwe_fbc(stwuct compwessow *cp, uint32_t paths_num,
	stwuct compw_addw_and_pitch_pawams *pawams);

void dce112_compwessow_disabwe_fbc(stwuct compwessow *cp);

void dce112_compwessow_set_fbc_invawidation_twiggews(stwuct compwessow *cp,
	uint32_t fbc_twiggew);

void dce112_compwessow_pwogwam_compwessed_suwface_addwess_and_pitch(
	stwuct compwessow *cp,
	stwuct compw_addw_and_pitch_pawams *pawams);

boow dce112_compwessow_is_fbc_enabwed_in_hw(stwuct compwessow *cp,
	uint32_t *fbc_mapped_cwtc_id);

/* WPT WEWATED */
void dce112_compwessow_enabwe_wpt(stwuct compwessow *cp);

void dce112_compwessow_disabwe_wpt(stwuct compwessow *cp);

void dce112_compwessow_pwogwam_wpt_contwow(stwuct compwessow *cp,
	stwuct compw_addw_and_pitch_pawams *pawams);

boow dce112_compwessow_is_wpt_enabwed_in_hw(stwuct compwessow *cp);

#endif
