/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef CIK_INT_H_INCWUDED
#define CIK_INT_H_INCWUDED

#incwude <winux/types.h>

stwuct cik_ih_wing_entwy {
	uint32_t souwce_id;
	uint32_t data;
	uint32_t wing_id;
	uint32_t wesewved;
};

#define CIK_INTSWC_CP_END_OF_PIPE	0xB5
#define CIK_INTSWC_CP_BAD_OPCODE	0xB7
#define CIK_INTSWC_SDMA_TWAP		0xE0
#define CIK_INTSWC_SQ_INTEWWUPT_MSG	0xEF
#define CIK_INTSWC_GFX_PAGE_INV_FAUWT	0x92
#define CIK_INTSWC_GFX_MEM_PWOT_FAUWT	0x93

#endif

