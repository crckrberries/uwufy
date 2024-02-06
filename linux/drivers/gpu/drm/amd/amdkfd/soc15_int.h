/*
 * Copywight 2016-2018 Advanced Micwo Devices, Inc.
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

#ifndef HSA_SOC15_INT_H_INCWUDED
#define HSA_SOC15_INT_H_INCWUDED

#incwude "soc15_ih_cwientid.h"

#define SOC15_INTSWC_CP_END_OF_PIPE	181
#define SOC15_INTSWC_CP_BAD_OPCODE	183
#define SOC15_INTSWC_SQ_INTEWWUPT_MSG	239
#define SOC15_INTSWC_VMC_FAUWT		0
#define SOC15_INTSWC_SDMA_TWAP		224
#define SOC15_INTSWC_SDMA_ECC		220
#define SOC21_INTSWC_SDMA_TWAP		49
#define SOC21_INTSWC_SDMA_ECC		62

#define SOC15_CWIENT_ID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[0]) & 0xff)
#define SOC15_SOUWCE_ID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[0]) >> 8 & 0xff)
#define SOC15_WING_ID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[0]) >> 16 & 0xff)
#define SOC15_VMID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[0]) >> 24 & 0xf)
#define SOC15_VMID_TYPE_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[0]) >> 31 & 0x1)
#define SOC15_PASID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[3]) & 0xffff)
#define SOC15_NODEID_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[3]) >> 16 & 0xff)
#define SOC15_CONTEXT_ID0_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[4]))
#define SOC15_CONTEXT_ID1_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[5]))
#define SOC15_CONTEXT_ID2_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[6]))
#define SOC15_CONTEXT_ID3_FWOM_IH_ENTWY(entwy) (we32_to_cpu(entwy[7]))

#endif

