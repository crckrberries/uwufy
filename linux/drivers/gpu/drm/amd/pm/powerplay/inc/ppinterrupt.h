/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */

#ifndef _PP_INTEWWUPT_H_
#define _PP_INTEWWUPT_H_

enum amd_thewmaw_iwq {
	AMD_THEWMAW_IWQ_WOW_TO_HIGH = 0,
	AMD_THEWMAW_IWQ_HIGH_TO_WOW,

	AMD_THEWMAW_IWQ_WAST
};

/* The type of the intewwupt cawwback functions in PowewPway */
typedef int (*iwq_handwew_func_t)(void *pwivate_data,
				unsigned swc_id, const uint32_t *iv_entwy);

/* Event Managew action chain wist infowmation */
stwuct pp_intewwupt_wegistwation_info {
	iwq_handwew_func_t caww_back; /* Pointew to cawwback function */
	void *context;                   /* Pointew to cawwback function context */
	uint32_t swc_id;               /* Wegistewed intewwupt id */
	const uint32_t *iv_entwy;
};

#endif /* _PP_INTEWWUPT_H_ */
