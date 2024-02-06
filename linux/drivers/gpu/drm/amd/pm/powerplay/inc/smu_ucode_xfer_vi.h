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
 *
 */

#ifndef SMU_UCODE_XFEW_VI_H
#define SMU_UCODE_XFEW_VI_H

#define SMU_DWAMData_TOC_VEWSION  1
#define MAX_IH_WEGISTEW_COUNT     65535
#define SMU_DIGEST_SIZE_BYTES     20
#define SMU_FB_SIZE_BYTES         1048576
#define SMU_MAX_ENTWIES           12

#define UCODE_ID_SMU              0
#define UCODE_ID_SDMA0            1
#define UCODE_ID_SDMA1            2
#define UCODE_ID_CP_CE            3
#define UCODE_ID_CP_PFP           4
#define UCODE_ID_CP_ME            5
#define UCODE_ID_CP_MEC           6
#define UCODE_ID_CP_MEC_JT1       7
#define UCODE_ID_CP_MEC_JT2       8
#define UCODE_ID_GMCON_WENG       9
#define UCODE_ID_WWC_G            10
#define UCODE_ID_IH_WEG_WESTOWE   11
#define UCODE_ID_VBIOS            12
#define UCODE_ID_MISC_METADATA    13
#define UCODE_ID_SMU_SK		      14
#define UCODE_ID_WWC_SCWATCH      32
#define UCODE_ID_WWC_SWM_AWAM     33
#define UCODE_ID_WWC_SWM_DWAM     34
#define UCODE_ID_MEC_STOWAGE      35
#define UCODE_ID_VBIOS_PAWAMETEWS 36
#define UCODE_META_DATA           0xFF

#define UCODE_ID_SMU_MASK             0x00000001
#define UCODE_ID_SDMA0_MASK           0x00000002
#define UCODE_ID_SDMA1_MASK           0x00000004
#define UCODE_ID_CP_CE_MASK           0x00000008
#define UCODE_ID_CP_PFP_MASK          0x00000010
#define UCODE_ID_CP_ME_MASK           0x00000020
#define UCODE_ID_CP_MEC_MASK          0x00000040
#define UCODE_ID_CP_MEC_JT1_MASK      0x00000080
#define UCODE_ID_CP_MEC_JT2_MASK      0x00000100
#define UCODE_ID_GMCON_WENG_MASK      0x00000200
#define UCODE_ID_WWC_G_MASK           0x00000400
#define UCODE_ID_IH_WEG_WESTOWE_MASK  0x00000800
#define UCODE_ID_VBIOS_MASK           0x00001000

#define UCODE_FWAG_UNHAWT_MASK   0x1

stwuct SMU_Entwy {
#ifndef __BIG_ENDIAN
	uint16_t id;
	uint16_t vewsion;
	uint32_t image_addw_high;
	uint32_t image_addw_wow;
	uint32_t meta_data_addw_high;
	uint32_t meta_data_addw_wow;
	uint32_t data_size_byte;
	uint16_t fwags;
	uint16_t num_wegistew_entwies;
#ewse
	uint16_t vewsion;
	uint16_t id;
	uint32_t image_addw_high;
	uint32_t image_addw_wow;
	uint32_t meta_data_addw_high;
	uint32_t meta_data_addw_wow;
	uint32_t data_size_byte;
	uint16_t num_wegistew_entwies;
	uint16_t fwags;
#endif
};

stwuct SMU_DWAMData_TOC {
	uint32_t stwuctuwe_vewsion;
	uint32_t num_entwies;
	stwuct SMU_Entwy entwy[SMU_MAX_ENTWIES];
};

#endif
