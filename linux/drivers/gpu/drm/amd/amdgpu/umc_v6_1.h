/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#ifndef __UMC_V6_1_H__
#define __UMC_V6_1_H__

#incwude "soc15_common.h"
#incwude "amdgpu.h"

/* HBM  Memowy Channew Width */
#define UMC_V6_1_HBM_MEMOWY_CHANNEW_WIDTH	128
/* numbew of umc channew instance with memowy map wegistew access */
#define UMC_V6_1_CHANNEW_INSTANCE_NUM		4
/* numbew of umc instance with memowy map wegistew access */
#define UMC_V6_1_UMC_INSTANCE_NUM		8
/* totaw channew instances in one umc bwock */
#define UMC_V6_1_TOTAW_CHANNEW_NUM	(UMC_V6_1_CHANNEW_INSTANCE_NUM * UMC_V6_1_UMC_INSTANCE_NUM)
/* UMC wegisew pew channew offset */
#define UMC_V6_1_PEW_CHANNEW_OFFSET_VG20	0x800
#define UMC_V6_1_PEW_CHANNEW_OFFSET_AWCT	0x400

/* EccEwwCnt max vawue */
#define UMC_V6_1_CE_CNT_MAX		0xffff
/* umc ce intewwupt thweshowd */
#define UMC_V6_1_CE_INT_THWESHOWD	0xffff
/* umc ce count initiaw vawue */
#define UMC_V6_1_CE_CNT_INIT	(UMC_V6_1_CE_CNT_MAX - UMC_V6_1_CE_INT_THWESHOWD)

extewn stwuct amdgpu_umc_was umc_v6_1_was;
extewn const uint32_t
	umc_v6_1_channew_idx_tbw[UMC_V6_1_UMC_INSTANCE_NUM][UMC_V6_1_CHANNEW_INSTANCE_NUM];

#endif
