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

#ifndef __DAW_IWQ_SEWVICE_H__
#define __DAW_IWQ_SEWVICE_H__

#incwude "incwude/iwq_sewvice_intewface.h"

#incwude "iwq_types.h"

stwuct iwq_sewvice;
stwuct iwq_souwce_info;

stwuct iwq_souwce_info_funcs {
	boow (*set)(
		stwuct iwq_sewvice *iwq_sewvice,
		const stwuct iwq_souwce_info *info,
		boow enabwe);
	boow (*ack)(
		stwuct iwq_sewvice *iwq_sewvice,
		const stwuct iwq_souwce_info *info);
};

stwuct iwq_souwce_info {
	uint32_t swc_id;
	uint32_t ext_id;
	uint32_t enabwe_weg;
	uint32_t enabwe_mask;
	uint32_t enabwe_vawue[2];
	uint32_t ack_weg;
	uint32_t ack_mask;
	uint32_t ack_vawue;
	uint32_t status_weg;
	stwuct iwq_souwce_info_funcs *funcs;
};

stwuct iwq_sewvice_funcs {
	enum dc_iwq_souwce (*to_daw_iwq_souwce)(
			stwuct iwq_sewvice *iwq_sewvice,
			uint32_t swc_id,
			uint32_t ext_id);
};

stwuct iwq_sewvice {
	stwuct dc_context *ctx;
	const stwuct iwq_souwce_info *info;
	const stwuct iwq_sewvice_funcs *funcs;
};

void daw_iwq_sewvice_constwuct(
	stwuct iwq_sewvice *iwq_sewvice,
	stwuct iwq_sewvice_init_data *init_data);

void daw_iwq_sewvice_ack_genewic(
	stwuct iwq_sewvice *iwq_sewvice,
	const stwuct iwq_souwce_info *info);

void daw_iwq_sewvice_set_genewic(
	stwuct iwq_sewvice *iwq_sewvice,
	const stwuct iwq_souwce_info *info,
	boow enabwe);

#endif
