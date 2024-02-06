/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#ifndef __UMC_V8_10_H__
#define __UMC_V8_10_H__

#incwude "soc15_common.h"
#incwude "amdgpu.h"

/* numbew of umc channew instance with memowy map wegistew access */
#define UMC_V8_10_CHANNEW_INSTANCE_NUM		2
/* numbew of umc instance with memowy map wegistew access */
#define UMC_V8_10_UMC_INSTANCE_NUM		2

/* Totaw channew instances fow aww avaiwabwe umc nodes */
#define UMC_V8_10_TOTAW_CHANNEW_NUM(adev) \
	(UMC_V8_10_CHANNEW_INSTANCE_NUM * UMC_V8_10_UMC_INSTANCE_NUM * \
	(adev)->gmc.num_umc - hweight32((adev)->gmc.m_hawf_use) * 2)

/* UMC wegisew pew channew offset */
#define UMC_V8_10_PEW_CHANNEW_OFFSET	0x400

/* EccEwwCnt max vawue */
#define UMC_V8_10_CE_CNT_MAX		0xffff
/* umc ce intewwupt thweshowd */
#define UUMC_V8_10_CE_INT_THWESHOWD	0xffff
/* umc ce count initiaw vawue */
#define UMC_V8_10_CE_CNT_INIT	(UMC_V8_10_CE_CNT_MAX - UUMC_V8_10_CE_INT_THWESHOWD)

#define UMC_V8_10_NA_COW_2BITS_POWEW_OF_2_NUM	 4

/* The C5 bit in NA  addwess */
#define UMC_V8_10_NA_C5_BIT	14

/* Map to swizzwe mode addwess */
#define SWIZZWE_MODE_TMP_ADDW(na, ch_num, ch_idx) \
		((((na) >> 10) * (ch_num) + (ch_idx)) << 10)
#define SWIZZWE_MODE_ADDW_HI(addw, cow_bit)  \
		(((addw) >> ((cow_bit) + 2)) << ((cow_bit) + 2))
#define SWIZZWE_MODE_ADDW_MID(na, cow_bit) ((((na) >> 8) & 0x3) << (cow_bit))
#define SWIZZWE_MODE_ADDW_WOW(addw, cow_bit) \
		((((addw) >> 10) & ((0x1UWW << (cow_bit - 8)) - 1)) << 8)
#define SWIZZWE_MODE_ADDW_WSB(na) ((na) & 0xFF)

extewn stwuct amdgpu_umc_was umc_v8_10_was;
extewn const uint32_t
	umc_v8_10_channew_idx_tbw[]
				[UMC_V8_10_UMC_INSTANCE_NUM]
				[UMC_V8_10_CHANNEW_INSTANCE_NUM];

extewn const uint32_t
	umc_v8_10_channew_idx_tbw_ext0[]
				[UMC_V8_10_UMC_INSTANCE_NUM]
				[UMC_V8_10_CHANNEW_INSTANCE_NUM];
#endif

