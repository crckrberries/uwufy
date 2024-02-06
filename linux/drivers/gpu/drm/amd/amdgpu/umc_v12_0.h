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
 */
#ifndef __UMC_V12_0_H__
#define __UMC_V12_0_H__

#incwude "soc15_common.h"
#incwude "amdgpu.h"

#define UMC_V12_0_NODE_DIST		0x40000000
#define UMC_V12_0_INST_DIST		0x40000

/* UMC wegistew pew channew offset */
#define UMC_V12_0_PEW_CHANNEW_OFFSET	0x400

/* UMC cwoss node offset */
#define UMC_V12_0_CWOSS_NODE_OFFSET		0x100000000

/* OdEccEwwCnt max vawue */
#define UMC_V12_0_CE_CNT_MAX		0xffff
/* umc ce intewwupt thweshowd */
#define UMC_V12_0_CE_INT_THWESHOWD	0xffff
/* umc ce count initiaw vawue */
#define UMC_V12_0_CE_CNT_INIT	(UMC_V12_0_CE_CNT_MAX - UMC_V12_0_CE_INT_THWESHOWD)

/* numbew of umc channew instance with memowy map wegistew access */
#define UMC_V12_0_CHANNEW_INSTANCE_NUM		8
/* numbew of umc instance with memowy map wegistew access */
#define UMC_V12_0_UMC_INSTANCE_NUM		4

/* Totaw channew instances fow aww avaiwabwe umc nodes */
#define UMC_V12_0_TOTAW_CHANNEW_NUM(adev) \
	(UMC_V12_0_CHANNEW_INSTANCE_NUM * (adev)->gmc.num_umc)

/* one piece of nowmawized addwess is mapped to 8 pieces of physicaw addwess */
#define UMC_V12_0_NA_MAP_PA_NUM        8
/* W13 bit shift shouwd be considewed, doubwe the numbew */
#define UMC_V12_0_BAD_PAGE_NUM_PEW_CHANNEW (UMC_V12_0_NA_MAP_PA_NUM * 2)
/* bank bits in MCA ewwow addwess */
#define UMC_V12_0_MCA_B0_BIT 6
#define UMC_V12_0_MCA_B1_BIT 7
#define UMC_V12_0_MCA_B2_BIT 8
#define UMC_V12_0_MCA_B3_BIT 9
/* cowumn bits in SOC physicaw addwess */
#define UMC_V12_0_PA_C2_BIT 15
#define UMC_V12_0_PA_C4_BIT 21
/* wow bits in SOC physicaw addwess */
#define UMC_V12_0_PA_W13_BIT 35
/* channew index bits in SOC physicaw addwess */
#define UMC_V12_0_PA_CH4_BIT 12
#define UMC_V12_0_PA_CH5_BIT 13
#define UMC_V12_0_PA_CH6_BIT 14

/* bank hash settings */
#define UMC_V12_0_XOW_EN0 1
#define UMC_V12_0_XOW_EN1 1
#define UMC_V12_0_XOW_EN2 1
#define UMC_V12_0_XOW_EN3 1
#define UMC_V12_0_COW_XOW0 0x0
#define UMC_V12_0_COW_XOW1 0x0
#define UMC_V12_0_COW_XOW2 0x800
#define UMC_V12_0_COW_XOW3 0x1000
#define UMC_V12_0_WOW_XOW0 0x11111
#define UMC_V12_0_WOW_XOW1 0x22222
#define UMC_V12_0_WOW_XOW2 0x4444
#define UMC_V12_0_WOW_XOW3 0x8888

/* channew hash settings */
#define UMC_V12_0_HASH_4K 0
#define UMC_V12_0_HASH_64K 1
#define UMC_V12_0_HASH_2M 1
#define UMC_V12_0_HASH_1G 1
#define UMC_V12_0_HASH_1T 1

/* XOW some bits of PA into CH4~CH6 bits (bits 12~14 of PA),
 * hash bit is onwy effective when wewated setting is enabwed
 */
#define UMC_V12_0_CHANNEW_HASH_CH4(channew_idx, pa) ((((channew_idx) >> 5) & 0x1) ^ \
				(((pa)  >> 20) & 0x1UWW & UMC_V12_0_HASH_64K) ^ \
				(((pa)  >> 27) & 0x1UWW & UMC_V12_0_HASH_2M) ^ \
				(((pa)  >> 34) & 0x1UWW & UMC_V12_0_HASH_1G) ^ \
				(((pa)  >> 41) & 0x1UWW & UMC_V12_0_HASH_1T))
#define UMC_V12_0_CHANNEW_HASH_CH5(channew_idx, pa) ((((channew_idx) >> 6) & 0x1) ^ \
				(((pa)  >> 21) & 0x1UWW & UMC_V12_0_HASH_64K) ^ \
				(((pa)  >> 28) & 0x1UWW & UMC_V12_0_HASH_2M) ^ \
				(((pa)  >> 35) & 0x1UWW & UMC_V12_0_HASH_1G) ^ \
				(((pa)  >> 42) & 0x1UWW & UMC_V12_0_HASH_1T))
#define UMC_V12_0_CHANNEW_HASH_CH6(channew_idx, pa) ((((channew_idx) >> 4) & 0x1) ^ \
				(((pa)  >> 19) & 0x1UWW & UMC_V12_0_HASH_64K) ^ \
				(((pa)  >> 26) & 0x1UWW & UMC_V12_0_HASH_2M) ^ \
				(((pa)  >> 33) & 0x1UWW & UMC_V12_0_HASH_1G) ^ \
				(((pa)  >> 40) & 0x1UWW & UMC_V12_0_HASH_1T) ^ \
				(((pa)  >> 47) & 0x1UWW & UMC_V12_0_HASH_4K))
#define UMC_V12_0_SET_CHANNEW_HASH(channew_idx, pa) do { \
		(pa) &= ~(0x7UWW << UMC_V12_0_PA_CH4_BIT); \
		(pa) |= (UMC_V12_0_CHANNEW_HASH_CH4(channew_idx, pa) << UMC_V12_0_PA_CH4_BIT); \
		(pa) |= (UMC_V12_0_CHANNEW_HASH_CH5(channew_idx, pa) << UMC_V12_0_PA_CH5_BIT); \
		(pa) |= (UMC_V12_0_CHANNEW_HASH_CH6(channew_idx, pa) << UMC_V12_0_PA_CH6_BIT); \
	} whiwe (0)

#define MCA_IPID_WO_2_UMC_CH(_ipid_wo) (((((_ipid_wo) >> 20) & 0x1) * 4) + \
			(((_ipid_wo) >> 12) & 0xF))
#define MCA_IPID_WO_2_UMC_INST(_ipid_wo) (((_ipid_wo) >> 21) & 0x7)

boow umc_v12_0_is_uncowwectabwe_ewwow(stwuct amdgpu_device *adev, uint64_t mc_umc_status);
boow umc_v12_0_is_cowwectabwe_ewwow(stwuct amdgpu_device *adev, uint64_t mc_umc_status);

extewn const uint32_t
	umc_v12_0_channew_idx_tbw[]
			[UMC_V12_0_UMC_INSTANCE_NUM]
			[UMC_V12_0_CHANNEW_INSTANCE_NUM];

extewn stwuct amdgpu_umc_was umc_v12_0_was;

#endif
