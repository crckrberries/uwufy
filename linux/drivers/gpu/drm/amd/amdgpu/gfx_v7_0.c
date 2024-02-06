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

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ih.h"
#incwude "amdgpu_gfx.h"
#incwude "cikd.h"
#incwude "cik.h"
#incwude "cik_stwucts.h"
#incwude "atom.h"
#incwude "amdgpu_ucode.h"
#incwude "cweawstate_ci.h"

#incwude "dce/dce_8_0_d.h"
#incwude "dce/dce_8_0_sh_mask.h"

#incwude "bif/bif_4_1_d.h"
#incwude "bif/bif_4_1_sh_mask.h"

#incwude "gca/gfx_7_0_d.h"
#incwude "gca/gfx_7_2_enum.h"
#incwude "gca/gfx_7_2_sh_mask.h"

#incwude "gmc/gmc_7_0_d.h"
#incwude "gmc/gmc_7_0_sh_mask.h"

#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"

#define NUM_SIMD_PEW_CU 0x4 /* missing fwom the gfx_7 IP headews */

#define GFX7_NUM_GFX_WINGS     1
#define GFX7_MEC_HPD_SIZE      2048

static void gfx_v7_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void gfx_v7_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static void gfx_v7_0_set_gds_init(stwuct amdgpu_device *adev);

MODUWE_FIWMWAWE("amdgpu/bonaiwe_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_me.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_ce.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_wwc.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_mec.bin");

MODUWE_FIWMWAWE("amdgpu/hawaii_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_me.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_ce.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_wwc.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_mec.bin");

MODUWE_FIWMWAWE("amdgpu/kavewi_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_me.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_ce.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_wwc.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_mec.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_mec2.bin");

MODUWE_FIWMWAWE("amdgpu/kabini_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_me.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_ce.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_wwc.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_mec.bin");

MODUWE_FIWMWAWE("amdgpu/muwwins_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_me.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_ce.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_wwc.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_mec.bin");

static const stwuct amdgpu_gds_weg_offset amdgpu_gds_weg_offset[] = {
	{mmGDS_VMID0_BASE, mmGDS_VMID0_SIZE, mmGDS_GWS_VMID0, mmGDS_OA_VMID0},
	{mmGDS_VMID1_BASE, mmGDS_VMID1_SIZE, mmGDS_GWS_VMID1, mmGDS_OA_VMID1},
	{mmGDS_VMID2_BASE, mmGDS_VMID2_SIZE, mmGDS_GWS_VMID2, mmGDS_OA_VMID2},
	{mmGDS_VMID3_BASE, mmGDS_VMID3_SIZE, mmGDS_GWS_VMID3, mmGDS_OA_VMID3},
	{mmGDS_VMID4_BASE, mmGDS_VMID4_SIZE, mmGDS_GWS_VMID4, mmGDS_OA_VMID4},
	{mmGDS_VMID5_BASE, mmGDS_VMID5_SIZE, mmGDS_GWS_VMID5, mmGDS_OA_VMID5},
	{mmGDS_VMID6_BASE, mmGDS_VMID6_SIZE, mmGDS_GWS_VMID6, mmGDS_OA_VMID6},
	{mmGDS_VMID7_BASE, mmGDS_VMID7_SIZE, mmGDS_GWS_VMID7, mmGDS_OA_VMID7},
	{mmGDS_VMID8_BASE, mmGDS_VMID8_SIZE, mmGDS_GWS_VMID8, mmGDS_OA_VMID8},
	{mmGDS_VMID9_BASE, mmGDS_VMID9_SIZE, mmGDS_GWS_VMID9, mmGDS_OA_VMID9},
	{mmGDS_VMID10_BASE, mmGDS_VMID10_SIZE, mmGDS_GWS_VMID10, mmGDS_OA_VMID10},
	{mmGDS_VMID11_BASE, mmGDS_VMID11_SIZE, mmGDS_GWS_VMID11, mmGDS_OA_VMID11},
	{mmGDS_VMID12_BASE, mmGDS_VMID12_SIZE, mmGDS_GWS_VMID12, mmGDS_OA_VMID12},
	{mmGDS_VMID13_BASE, mmGDS_VMID13_SIZE, mmGDS_GWS_VMID13, mmGDS_OA_VMID13},
	{mmGDS_VMID14_BASE, mmGDS_VMID14_SIZE, mmGDS_GWS_VMID14, mmGDS_OA_VMID14},
	{mmGDS_VMID15_BASE, mmGDS_VMID15_SIZE, mmGDS_GWS_VMID15, mmGDS_OA_VMID15}
};

static const u32 spectwe_wwc_save_westowe_wegistew_wist[] = {
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc178 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc278 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc27c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc280 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc284 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc288 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc29c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac  >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xae00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0001 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc778 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc77c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc780 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc784 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc788 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc78c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a4 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7a8 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7ac >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b0 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc7b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92cc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x92d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x8e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x9e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xae00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0xbe00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
};

static const u32 kawindi_wwc_save_westowe_wegistew_wist[] = {
	(0x0e00 << 16) | (0xc12c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc140 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc150 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc15c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc168 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc170 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc204 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8228 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x829c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x869c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x98f4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x98f8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc260 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x90e8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c000 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c00c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c1c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xcd20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89bc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8900 >> 2),
	0x00000000,
	0x3,
	(0x0e00 << 16) | (0xc130 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc134 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc208 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc264 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc268 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc26c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc270 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc274 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc28c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc290 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc294 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc298 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2a8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc2ac >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x301d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30238 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30250 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30254 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30258 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3025c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc900 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc904 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc908 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc90c >> 2),
	0x00000000,
	(0x4e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0xc910 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc99c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9834 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f00 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f04 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f08 >> 2),
	0x00000000,
	(0x0000 << 16) | (0x30f0c >> 2),
	0x00000000,
	(0x0600 << 16) | (0x9b7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bf0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8bcc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8b24 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30a04 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a10 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a14 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a18 >> 2),
	0x00000000,
	(0x0600 << 16) | (0x30a2c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc700 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc704 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc708 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xc768 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc770 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc774 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc798 >> 2),
	0x00000000,
	(0x0400 << 16) | (0xc79c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9100 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c010 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c04 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c20 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c38 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8c3c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xae00 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9604 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac08 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac0c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac58 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac68 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac6c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac70 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac74 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac78 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac7c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac80 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac84 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac88 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xac8c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x970c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9714 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x9718 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x971c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x4e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x5e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x6e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x7e00 << 16) | (0x31068 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd10 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0xcd14 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88b8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88bc >> 2),
	0x00000000,
	(0x0400 << 16) | (0x89c0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88c8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x88d8 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8980 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30938 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3093c >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30940 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89a0 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30900 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x30904 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x89b4 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3e1fc >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c210 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c214 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x3c218 >> 2),
	0x00000000,
	(0x0e00 << 16) | (0x8904 >> 2),
	0x00000000,
	0x5,
	(0x0e00 << 16) | (0x8c28 >> 2),
	(0x0e00 << 16) | (0x8c2c >> 2),
	(0x0e00 << 16) | (0x8c30 >> 2),
	(0x0e00 << 16) | (0x8c34 >> 2),
	(0x0e00 << 16) | (0x9600 >> 2),
};

static u32 gfx_v7_0_get_csb_size(stwuct amdgpu_device *adev);
static void gfx_v7_0_get_csb_buffew(stwuct amdgpu_device *adev, vowatiwe u32 *buffew);
static void gfx_v7_0_init_pg(stwuct amdgpu_device *adev);
static void gfx_v7_0_get_cu_info(stwuct amdgpu_device *adev);

static void gfx_v7_0_fwee_micwocode(stwuct amdgpu_device *adev)
{
	amdgpu_ucode_wewease(&adev->gfx.pfp_fw);
	amdgpu_ucode_wewease(&adev->gfx.me_fw);
	amdgpu_ucode_wewease(&adev->gfx.ce_fw);
	amdgpu_ucode_wewease(&adev->gfx.mec_fw);
	amdgpu_ucode_wewease(&adev->gfx.mec2_fw);
	amdgpu_ucode_wewease(&adev->gfx.wwc_fw);
}

/*
 * Cowe functions
 */
/**
 * gfx_v7_0_init_micwocode - woad ucode images fwom disk
 *
 * @adev: amdgpu_device pointew
 *
 * Use the fiwmwawe intewface to woad the ucode images into
 * the dwivew (not woaded into hw).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int gfx_v7_0_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[30];
	int eww;

	DWM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_BONAIWE:
		chip_name = "bonaiwe";
		bweak;
	case CHIP_HAWAII:
		chip_name = "hawaii";
		bweak;
	case CHIP_KAVEWI:
		chip_name = "kavewi";
		bweak;
	case CHIP_KABINI:
		chip_name = "kabini";
		bweak;
	case CHIP_MUWWINS:
		chip_name = "muwwins";
		bweak;
	defauwt:
		BUG();
	}

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.pfp_fw, fw_name);
	if (eww)
		goto out;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.me_fw, fw_name);
	if (eww)
		goto out;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.ce_fw, fw_name);
	if (eww)
		goto out;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec_fw, fw_name);
	if (eww)
		goto out;

	if (adev->asic_type == CHIP_KAVEWI) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec2_fw, fw_name);
		if (eww)
			goto out;
	}

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_wwc.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.wwc_fw, fw_name);
	if (eww)
		goto out;
out:
	if (eww) {
		pw_eww("gfx7: Faiwed to woad fiwmwawe \"%s\"\n", fw_name);
		gfx_v7_0_fwee_micwocode(adev);
	}
	wetuwn eww;
}

/**
 * gfx_v7_0_tiwing_mode_tabwe_init - init the hw tiwing tabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Stawting with SI, the tiwing setup is done gwobawwy in a
 * set of 32 tiwing modes.  Wathew than sewecting each set of
 * pawametews pew suwface as on owdew asics, we just sewect
 * which index in the tiwing tabwe we want to use, and the
 * suwface uses those pawametews (CIK).
 */
static void gfx_v7_0_tiwing_mode_tabwe_init(stwuct amdgpu_device *adev)
{
	const u32 num_tiwe_mode_states =
			AWWAY_SIZE(adev->gfx.config.tiwe_mode_awway);
	const u32 num_secondawy_tiwe_mode_states =
			AWWAY_SIZE(adev->gfx.config.macwotiwe_mode_awway);
	u32 weg_offset, spwit_equaw_to_wow_size;
	uint32_t *tiwe, *macwotiwe;

	tiwe = adev->gfx.config.tiwe_mode_awway;
	macwotiwe = adev->gfx.config.macwotiwe_mode_awway;

	switch (adev->gfx.config.mem_wow_size_in_kb) {
	case 1:
		spwit_equaw_to_wow_size = ADDW_SUWF_TIWE_SPWIT_1KB;
		bweak;
	case 2:
	defauwt:
		spwit_equaw_to_wow_size = ADDW_SUWF_TIWE_SPWIT_2KB;
		bweak;
	case 4:
		spwit_equaw_to_wow_size = ADDW_SUWF_TIWE_SPWIT_4KB;
		bweak;
	}

	fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
		tiwe[weg_offset] = 0;
	fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
		macwotiwe[weg_offset] = 0;

	switch (adev->asic_type) {
	case CHIP_BONAIWE:
		tiwe[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[7] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16));
		tiwe[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING));
		tiwe[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[12] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING));
		tiwe[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[17] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING));
		tiwe[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[21] =  (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[23] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING));
		tiwe[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[30] = (TIWE_SPWIT(spwit_equaw_to_wow_size));

		macwotiwe[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));
		macwotiwe[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, tiwe[weg_offset]);
		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, macwotiwe[weg_offset]);
		bweak;
	case CHIP_HAWAII:
		tiwe[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[7] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16));
		tiwe[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING));
		tiwe[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[12] = (AWWAY_MODE(AWWAY_PWT_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING));
		tiwe[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[17] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING));
		tiwe[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[23] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING));
		tiwe[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[30] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		macwotiwe[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));
		macwotiwe[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));
		macwotiwe[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, tiwe[weg_offset]);
		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, macwotiwe[weg_offset]);
		bweak;
	case CHIP_KABINI:
	case CHIP_KAVEWI:
	case CHIP_MUWWINS:
	defauwt:
		tiwe[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		tiwe[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING) |
			   TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[7] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
			   PIPE_CONFIG(ADDW_SUWF_P2));
		tiwe[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			   PIPE_CONFIG(ADDW_SUWF_P2) |
			   MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING));
		tiwe[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[12] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING));
		tiwe[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[17] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING));
		tiwe[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[23] = (TIWE_SPWIT(spwit_equaw_to_wow_size));
		tiwe[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		tiwe[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING));
		tiwe[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		tiwe[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
			    PIPE_CONFIG(ADDW_SUWF_P2) |
			    MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
			    SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		tiwe[30] = (TIWE_SPWIT(spwit_equaw_to_wow_size));

		macwotiwe[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		macwotiwe[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		macwotiwe[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, tiwe[weg_offset]);
		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, macwotiwe[weg_offset]);
		bweak;
	}
}

/**
 * gfx_v7_0_sewect_se_sh - sewect which SE, SH to addwess
 *
 * @adev: amdgpu_device pointew
 * @se_num: shadew engine to addwess
 * @sh_num: sh bwock to addwess
 * @instance: Cewtain wegistews awe instanced pew SE ow SH.
 *            0xffffffff means bwoadcast to aww SEs ow SHs (CIK).
 * @xcc_id: xcc accewewated compute cowe id
 * Sewect which SE, SH combinations to addwess.
 */
static void gfx_v7_0_sewect_se_sh(stwuct amdgpu_device *adev,
				  u32 se_num, u32 sh_num, u32 instance,
				  int xcc_id)
{
	u32 data;

	if (instance == 0xffffffff)
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX, INSTANCE_INDEX, instance);

	if ((se_num == 0xffffffff) && (sh_num == 0xffffffff))
		data |= GWBM_GFX_INDEX__SH_BWOADCAST_WWITES_MASK |
			GWBM_GFX_INDEX__SE_BWOADCAST_WWITES_MASK;
	ewse if (se_num == 0xffffffff)
		data |= GWBM_GFX_INDEX__SE_BWOADCAST_WWITES_MASK |
			(sh_num << GWBM_GFX_INDEX__SH_INDEX__SHIFT);
	ewse if (sh_num == 0xffffffff)
		data |= GWBM_GFX_INDEX__SH_BWOADCAST_WWITES_MASK |
			(se_num << GWBM_GFX_INDEX__SE_INDEX__SHIFT);
	ewse
		data |= (sh_num << GWBM_GFX_INDEX__SH_INDEX__SHIFT) |
			(se_num << GWBM_GFX_INDEX__SE_INDEX__SHIFT);
	WWEG32(mmGWBM_GFX_INDEX, data);
}

/**
 * gfx_v7_0_get_wb_active_bitmap - computes the mask of enabwed WBs
 *
 * @adev: amdgpu_device pointew
 *
 * Cawcuwates the bitmask of enabwed WBs (CIK).
 * Wetuwns the enabwed WB bitmask.
 */
static u32 gfx_v7_0_get_wb_active_bitmap(stwuct amdgpu_device *adev)
{
	u32 data, mask;

	data = WWEG32(mmCC_WB_BACKEND_DISABWE);
	data |= WWEG32(mmGC_USEW_WB_BACKEND_DISABWE);

	data &= CC_WB_BACKEND_DISABWE__BACKEND_DISABWE_MASK;
	data >>= GC_USEW_WB_BACKEND_DISABWE__BACKEND_DISABWE__SHIFT;

	mask = amdgpu_gfx_cweate_bitmask(adev->gfx.config.max_backends_pew_se /
					 adev->gfx.config.max_sh_pew_se);

	wetuwn (~data) & mask;
}

static void
gfx_v7_0_wastew_config(stwuct amdgpu_device *adev, u32 *wconf, u32 *wconf1)
{
	switch (adev->asic_type) {
	case CHIP_BONAIWE:
		*wconf |= WB_MAP_PKW0(2) | WB_XSEW2(1) | SE_MAP(2) |
			  SE_XSEW(1) | SE_YSEW(1);
		*wconf1 |= 0x0;
		bweak;
	case CHIP_HAWAII:
		*wconf |= WB_MAP_PKW0(2) | WB_MAP_PKW1(2) |
			  WB_XSEW2(1) | PKW_MAP(2) | PKW_XSEW(1) |
			  PKW_YSEW(1) | SE_MAP(2) | SE_XSEW(2) |
			  SE_YSEW(3);
		*wconf1 |= SE_PAIW_MAP(2) | SE_PAIW_XSEW(3) |
			   SE_PAIW_YSEW(2);
		bweak;
	case CHIP_KAVEWI:
		*wconf |= WB_MAP_PKW0(2);
		*wconf1 |= 0x0;
		bweak;
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		*wconf |= 0x0;
		*wconf1 |= 0x0;
		bweak;
	defauwt:
		DWM_EWWOW("unknown asic: 0x%x\n", adev->asic_type);
		bweak;
	}
}

static void
gfx_v7_0_wwite_hawvested_wastew_configs(stwuct amdgpu_device *adev,
					u32 wastew_config, u32 wastew_config_1,
					unsigned wb_mask, unsigned num_wb)
{
	unsigned sh_pew_se = max_t(unsigned, adev->gfx.config.max_sh_pew_se, 1);
	unsigned num_se = max_t(unsigned, adev->gfx.config.max_shadew_engines, 1);
	unsigned wb_pew_pkw = min_t(unsigned, num_wb / num_se / sh_pew_se, 2);
	unsigned wb_pew_se = num_wb / num_se;
	unsigned se_mask[4];
	unsigned se;

	se_mask[0] = ((1 << wb_pew_se) - 1) & wb_mask;
	se_mask[1] = (se_mask[0] << wb_pew_se) & wb_mask;
	se_mask[2] = (se_mask[1] << wb_pew_se) & wb_mask;
	se_mask[3] = (se_mask[2] << wb_pew_se) & wb_mask;

	WAWN_ON(!(num_se == 1 || num_se == 2 || num_se == 4));
	WAWN_ON(!(sh_pew_se == 1 || sh_pew_se == 2));
	WAWN_ON(!(wb_pew_pkw == 1 || wb_pew_pkw == 2));

	if ((num_se > 2) && ((!se_mask[0] && !se_mask[1]) ||
			     (!se_mask[2] && !se_mask[3]))) {
		wastew_config_1 &= ~SE_PAIW_MAP_MASK;

		if (!se_mask[0] && !se_mask[1]) {
			wastew_config_1 |=
				SE_PAIW_MAP(WASTEW_CONFIG_SE_PAIW_MAP_3);
		} ewse {
			wastew_config_1 |=
				SE_PAIW_MAP(WASTEW_CONFIG_SE_PAIW_MAP_0);
		}
	}

	fow (se = 0; se < num_se; se++) {
		unsigned wastew_config_se = wastew_config;
		unsigned pkw0_mask = ((1 << wb_pew_pkw) - 1) << (se * wb_pew_se);
		unsigned pkw1_mask = pkw0_mask << wb_pew_pkw;
		int idx = (se / 2) * 2;

		if ((num_se > 1) && (!se_mask[idx] || !se_mask[idx + 1])) {
			wastew_config_se &= ~SE_MAP_MASK;

			if (!se_mask[idx]) {
				wastew_config_se |= SE_MAP(WASTEW_CONFIG_SE_MAP_3);
			} ewse {
				wastew_config_se |= SE_MAP(WASTEW_CONFIG_SE_MAP_0);
			}
		}

		pkw0_mask &= wb_mask;
		pkw1_mask &= wb_mask;
		if (wb_pew_se > 2 && (!pkw0_mask || !pkw1_mask)) {
			wastew_config_se &= ~PKW_MAP_MASK;

			if (!pkw0_mask) {
				wastew_config_se |= PKW_MAP(WASTEW_CONFIG_PKW_MAP_3);
			} ewse {
				wastew_config_se |= PKW_MAP(WASTEW_CONFIG_PKW_MAP_0);
			}
		}

		if (wb_pew_se >= 2) {
			unsigned wb0_mask = 1 << (se * wb_pew_se);
			unsigned wb1_mask = wb0_mask << 1;

			wb0_mask &= wb_mask;
			wb1_mask &= wb_mask;
			if (!wb0_mask || !wb1_mask) {
				wastew_config_se &= ~WB_MAP_PKW0_MASK;

				if (!wb0_mask) {
					wastew_config_se |=
						WB_MAP_PKW0(WASTEW_CONFIG_WB_MAP_3);
				} ewse {
					wastew_config_se |=
						WB_MAP_PKW0(WASTEW_CONFIG_WB_MAP_0);
				}
			}

			if (wb_pew_se > 2) {
				wb0_mask = 1 << (se * wb_pew_se + wb_pew_pkw);
				wb1_mask = wb0_mask << 1;
				wb0_mask &= wb_mask;
				wb1_mask &= wb_mask;
				if (!wb0_mask || !wb1_mask) {
					wastew_config_se &= ~WB_MAP_PKW1_MASK;

					if (!wb0_mask) {
						wastew_config_se |=
							WB_MAP_PKW1(WASTEW_CONFIG_WB_MAP_3);
					} ewse {
						wastew_config_se |=
							WB_MAP_PKW1(WASTEW_CONFIG_WB_MAP_0);
					}
				}
			}
		}

		/* GWBM_GFX_INDEX has a diffewent offset on CI+ */
		gfx_v7_0_sewect_se_sh(adev, se, 0xffffffff, 0xffffffff, 0);
		WWEG32(mmPA_SC_WASTEW_CONFIG, wastew_config_se);
		WWEG32(mmPA_SC_WASTEW_CONFIG_1, wastew_config_1);
	}

	/* GWBM_GFX_INDEX has a diffewent offset on CI+ */
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
}

/**
 * gfx_v7_0_setup_wb - setup the WBs on the asic
 *
 * @adev: amdgpu_device pointew
 *
 * Configuwes pew-SE/SH WB wegistews (CIK).
 */
static void gfx_v7_0_setup_wb(stwuct amdgpu_device *adev)
{
	int i, j;
	u32 data;
	u32 wastew_config = 0, wastew_config_1 = 0;
	u32 active_wbs = 0;
	u32 wb_bitmap_width_pew_sh = adev->gfx.config.max_backends_pew_se /
					adev->gfx.config.max_sh_pew_se;
	unsigned num_wb_pipes;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v7_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			data = gfx_v7_0_get_wb_active_bitmap(adev);
			active_wbs |= data << ((i * adev->gfx.config.max_sh_pew_se + j) *
					       wb_bitmap_width_pew_sh);
		}
	}
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	adev->gfx.config.backend_enabwe_mask = active_wbs;
	adev->gfx.config.num_wbs = hweight32(active_wbs);

	num_wb_pipes = min_t(unsigned, adev->gfx.config.max_backends_pew_se *
			     adev->gfx.config.max_shadew_engines, 16);

	gfx_v7_0_wastew_config(adev, &wastew_config, &wastew_config_1);

	if (!adev->gfx.config.backend_enabwe_mask ||
			adev->gfx.config.num_wbs >= num_wb_pipes) {
		WWEG32(mmPA_SC_WASTEW_CONFIG, wastew_config);
		WWEG32(mmPA_SC_WASTEW_CONFIG_1, wastew_config_1);
	} ewse {
		gfx_v7_0_wwite_hawvested_wastew_configs(adev, wastew_config, wastew_config_1,
							adev->gfx.config.backend_enabwe_mask,
							num_wb_pipes);
	}

	/* cache the vawues fow usewspace */
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v7_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			adev->gfx.config.wb_config[i][j].wb_backend_disabwe =
				WWEG32(mmCC_WB_BACKEND_DISABWE);
			adev->gfx.config.wb_config[i][j].usew_wb_backend_disabwe =
				WWEG32(mmGC_USEW_WB_BACKEND_DISABWE);
			adev->gfx.config.wb_config[i][j].wastew_config =
				WWEG32(mmPA_SC_WASTEW_CONFIG);
			adev->gfx.config.wb_config[i][j].wastew_config_1 =
				WWEG32(mmPA_SC_WASTEW_CONFIG_1);
		}
	}
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

#define DEFAUWT_SH_MEM_BASES	(0x6000)
/**
 * gfx_v7_0_init_compute_vmid - gawt enabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawize compute vmid sh_mem wegistews
 *
 */
static void gfx_v7_0_init_compute_vmid(stwuct amdgpu_device *adev)
{
	int i;
	uint32_t sh_mem_config;
	uint32_t sh_mem_bases;

	/*
	 * Configuwe apewtuwes:
	 * WDS:         0x60000000'00000000 - 0x60000001'00000000 (4GB)
	 * Scwatch:     0x60000001'00000000 - 0x60000002'00000000 (4GB)
	 * GPUVM:       0x60010000'00000000 - 0x60020000'00000000 (1TB)
	*/
	sh_mem_bases = DEFAUWT_SH_MEM_BASES | (DEFAUWT_SH_MEM_BASES << 16);
	sh_mem_config = SH_MEM_AWIGNMENT_MODE_UNAWIGNED <<
			SH_MEM_CONFIG__AWIGNMENT_MODE__SHIFT;
	sh_mem_config |= MTYPE_NONCACHED << SH_MEM_CONFIG__DEFAUWT_MTYPE__SHIFT;
	mutex_wock(&adev->swbm_mutex);
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		cik_swbm_sewect(adev, 0, 0, 0, i);
		/* CP and shadews */
		WWEG32(mmSH_MEM_CONFIG, sh_mem_config);
		WWEG32(mmSH_MEM_APE1_BASE, 1);
		WWEG32(mmSH_MEM_APE1_WIMIT, 0);
		WWEG32(mmSH_MEM_BASES, sh_mem_bases);
	}
	cik_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	/* Initiawize aww compute VMIDs to have no GDS, GWS, ow OA
	   access. These shouwd be enabwed by FW fow tawget VMIDs. */
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		WWEG32(amdgpu_gds_weg_offset[i].mem_base, 0);
		WWEG32(amdgpu_gds_weg_offset[i].mem_size, 0);
		WWEG32(amdgpu_gds_weg_offset[i].gws, 0);
		WWEG32(amdgpu_gds_weg_offset[i].oa, 0);
	}
}

static void gfx_v7_0_init_gds_vmid(stwuct amdgpu_device *adev)
{
	int vmid;

	/*
	 * Initiawize aww compute and usew-gfx VMIDs to have no GDS, GWS, ow OA
	 * access. Compute VMIDs shouwd be enabwed by FW fow tawget VMIDs,
	 * the dwivew can enabwe them fow gwaphics. VMID0 shouwd maintain
	 * access so that HWS fiwmwawe can save/westowe entwies.
	 */
	fow (vmid = 1; vmid < AMDGPU_NUM_VMID; vmid++) {
		WWEG32(amdgpu_gds_weg_offset[vmid].mem_base, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].mem_size, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].gws, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].oa, 0);
	}
}

static void gfx_v7_0_config_init(stwuct amdgpu_device *adev)
{
	adev->gfx.config.doubwe_offchip_wds_buf = 1;
}

/**
 * gfx_v7_0_constants_init - setup the 3D engine
 *
 * @adev: amdgpu_device pointew
 *
 * init the gfx constants such as the 3D engine, tiwing configuwation
 * wegistews, maximum numbew of quad pipes, wendew backends...
 */
static void gfx_v7_0_constants_init(stwuct amdgpu_device *adev)
{
	u32 sh_mem_cfg, sh_static_mem_cfg, sh_mem_base;
	u32 tmp;
	int i;

	WWEG32(mmGWBM_CNTW, (0xff << GWBM_CNTW__WEAD_TIMEOUT__SHIFT));

	WWEG32(mmGB_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmHDP_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmDMIF_ADDW_CAWC, adev->gfx.config.gb_addw_config);

	gfx_v7_0_tiwing_mode_tabwe_init(adev);

	gfx_v7_0_setup_wb(adev);
	gfx_v7_0_get_cu_info(adev);
	gfx_v7_0_config_init(adev);

	/* set HW defauwts fow 3D engine */
	WWEG32(mmCP_MEQ_THWESHOWDS,
	       (0x30 << CP_MEQ_THWESHOWDS__MEQ1_STAWT__SHIFT) |
	       (0x60 << CP_MEQ_THWESHOWDS__MEQ2_STAWT__SHIFT));

	mutex_wock(&adev->gwbm_idx_mutex);
	/*
	 * making suwe that the fowwowing wegistew wwites wiww be bwoadcasted
	 * to aww the shadews
	 */
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	/* XXX SH_MEM wegs */
	/* whewe to put WDS, scwatch, GPUVM in FSA64 space */
	sh_mem_cfg = WEG_SET_FIEWD(0, SH_MEM_CONFIG, AWIGNMENT_MODE,
				   SH_MEM_AWIGNMENT_MODE_UNAWIGNED);
	sh_mem_cfg = WEG_SET_FIEWD(sh_mem_cfg, SH_MEM_CONFIG, DEFAUWT_MTYPE,
				   MTYPE_NC);
	sh_mem_cfg = WEG_SET_FIEWD(sh_mem_cfg, SH_MEM_CONFIG, APE1_MTYPE,
				   MTYPE_UC);
	sh_mem_cfg = WEG_SET_FIEWD(sh_mem_cfg, SH_MEM_CONFIG, PWIVATE_ATC, 0);

	sh_static_mem_cfg = WEG_SET_FIEWD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZWE_ENABWE, 1);
	sh_static_mem_cfg = WEG_SET_FIEWD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   EWEMENT_SIZE, 1);
	sh_static_mem_cfg = WEG_SET_FIEWD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STWIDE, 3);
	WWEG32(mmSH_STATIC_MEM_CONFIG, sh_static_mem_cfg);

	mutex_wock(&adev->swbm_mutex);
	fow (i = 0; i < adev->vm_managew.id_mgw[0].num_ids; i++) {
		if (i == 0)
			sh_mem_base = 0;
		ewse
			sh_mem_base = adev->gmc.shawed_apewtuwe_stawt >> 48;
		cik_swbm_sewect(adev, 0, 0, 0, i);
		/* CP and shadews */
		WWEG32(mmSH_MEM_CONFIG, sh_mem_cfg);
		WWEG32(mmSH_MEM_APE1_BASE, 1);
		WWEG32(mmSH_MEM_APE1_WIMIT, 0);
		WWEG32(mmSH_MEM_BASES, sh_mem_base);
	}
	cik_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	gfx_v7_0_init_compute_vmid(adev);
	gfx_v7_0_init_gds_vmid(adev);

	WWEG32(mmSX_DEBUG_1, 0x20);

	WWEG32(mmTA_CNTW_AUX, 0x00010000);

	tmp = WWEG32(mmSPI_CONFIG_CNTW);
	tmp |= 0x03000000;
	WWEG32(mmSPI_CONFIG_CNTW, tmp);

	WWEG32(mmSQ_CONFIG, 1);

	WWEG32(mmDB_DEBUG, 0);

	tmp = WWEG32(mmDB_DEBUG2) & ~0xf00fffff;
	tmp |= 0x00000400;
	WWEG32(mmDB_DEBUG2, tmp);

	tmp = WWEG32(mmDB_DEBUG3) & ~0x0002021c;
	tmp |= 0x00020200;
	WWEG32(mmDB_DEBUG3, tmp);

	tmp = WWEG32(mmCB_HW_CONTWOW) & ~0x00010000;
	tmp |= 0x00018208;
	WWEG32(mmCB_HW_CONTWOW, tmp);

	WWEG32(mmSPI_CONFIG_CNTW_1, (4 << SPI_CONFIG_CNTW_1__VTX_DONE_DEWAY__SHIFT));

	WWEG32(mmPA_SC_FIFO_SIZE,
		((adev->gfx.config.sc_pwim_fifo_size_fwontend << PA_SC_FIFO_SIZE__SC_FWONTEND_PWIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_pwim_fifo_size_backend << PA_SC_FIFO_SIZE__SC_BACKEND_PWIM_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_hiz_tiwe_fifo_size << PA_SC_FIFO_SIZE__SC_HIZ_TIWE_FIFO_SIZE__SHIFT) |
		(adev->gfx.config.sc_eawwyz_tiwe_fifo_size << PA_SC_FIFO_SIZE__SC_EAWWYZ_TIWE_FIFO_SIZE__SHIFT)));

	WWEG32(mmVGT_NUM_INSTANCES, 1);

	WWEG32(mmCP_PEWFMON_CNTW, 0);

	WWEG32(mmSQ_CONFIG, 0);

	WWEG32(mmPA_SC_FOWCE_EOV_MAX_CNTS,
		((4095 << PA_SC_FOWCE_EOV_MAX_CNTS__FOWCE_EOV_MAX_CWK_CNT__SHIFT) |
		(255 << PA_SC_FOWCE_EOV_MAX_CNTS__FOWCE_EOV_MAX_WEZ_CNT__SHIFT)));

	WWEG32(mmVGT_CACHE_INVAWIDATION,
		(VC_AND_TC << VGT_CACHE_INVAWIDATION__CACHE_INVAWIDATION__SHIFT) |
		(ES_AND_GS_AUTO << VGT_CACHE_INVAWIDATION__AUTO_INVWD_EN__SHIFT));

	WWEG32(mmVGT_GS_VEWTEX_WEUSE, 16);
	WWEG32(mmPA_SC_WINE_STIPPWE_STATE, 0);

	WWEG32(mmPA_CW_ENHANCE, PA_CW_ENHANCE__CWIP_VTX_WEOWDEW_ENA_MASK |
			(3 << PA_CW_ENHANCE__NUM_CWIP_SEQ__SHIFT));
	WWEG32(mmPA_SC_ENHANCE, PA_SC_ENHANCE__ENABWE_PA_SC_OUT_OF_OWDEW_MASK);

	tmp = WWEG32(mmSPI_AWB_PWIOWITY);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS0, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS1, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS2, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS3, 2);
	WWEG32(mmSPI_AWB_PWIOWITY, tmp);

	mutex_unwock(&adev->gwbm_idx_mutex);

	udeway(50);
}

/**
 * gfx_v7_0_wing_test_wing - basic gfx wing test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Awwocate a scwatch wegistew and wwite to it using the gfx wing (CIK).
 * Pwovides a basic gfx wing test to vewify that the wing is wowking.
 * Used by gfx_v7_0_cp_gfx_wesume();
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int gfx_v7_0_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	WWEG32(mmSCWATCH_WEG0, 0xCAFEDEAD);
	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_UCONFIG_WEG, 1));
	amdgpu_wing_wwite(wing, mmSCWATCH_WEG0 - PACKET3_SET_UCONFIG_WEG_STAWT);
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(mmSCWATCH_WEG0);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}
	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;
	wetuwn w;
}

/**
 * gfx_v7_0_wing_emit_hdp_fwush - emit an hdp fwush on the cp
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Emits an hdp fwush on the cp.
 */
static void gfx_v7_0_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	u32 wef_and_mask;
	int usepfp = wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE ? 0 : 1;

	if (wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE) {
		switch (wing->me) {
		case 1:
			wef_and_mask = GPU_HDP_FWUSH_DONE__CP2_MASK << wing->pipe;
			bweak;
		case 2:
			wef_and_mask = GPU_HDP_FWUSH_DONE__CP6_MASK << wing->pipe;
			bweak;
		defauwt:
			wetuwn;
		}
	} ewse {
		wef_and_mask = GPU_HDP_FWUSH_DONE__CP0_MASK;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_OPEWATION(1) | /* wwite, wait, wwite */
				 WAIT_WEG_MEM_FUNCTION(3) |  /* == */
				 WAIT_WEG_MEM_ENGINE(usepfp)));   /* pfp ow me */
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_WEQ);
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_DONE);
	amdgpu_wing_wwite(wing, wef_and_mask);
	amdgpu_wing_wwite(wing, wef_and_mask);
	amdgpu_wing_wwite(wing, 0x20); /* poww intewvaw */
}

static void gfx_v7_0_wing_emit_vgt_fwush(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE, 0));
	amdgpu_wing_wwite(wing, EVENT_TYPE(VS_PAWTIAW_FWUSH) |
		EVENT_INDEX(4));

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE, 0));
	amdgpu_wing_wwite(wing, EVENT_TYPE(VGT_FWUSH) |
		EVENT_INDEX(0));
}

/**
 * gfx_v7_0_wing_emit_fence_gfx - emit a fence on the gfx wing
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Emits a fence sequence numbew on the gfx wing and fwushes
 * GPU caches.
 */
static void gfx_v7_0_wing_emit_fence_gfx(stwuct amdgpu_wing *wing, u64 addw,
					 u64 seq, unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	boow int_sew = fwags & AMDGPU_FENCE_FWAG_INT;
	/* Wowkawound fow cache fwush pwobwems. Fiwst send a dummy EOP
	 * event down the pipe with seq one bewow.
	 */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xffff) |
				DATA_SEW(1) | INT_SEW(0));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq - 1));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq - 1));

	/* Then send the weaw EOP event down the pipe. */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xffff) |
				DATA_SEW(wwite64bit ? 2 : 1) | INT_SEW(int_sew ? 2 : 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq));
}

/**
 * gfx_v7_0_wing_emit_fence_compute - emit a fence on the compute wing
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Emits a fence sequence numbew on the compute wing and fwushes
 * GPU caches.
 */
static void gfx_v7_0_wing_emit_fence_compute(stwuct amdgpu_wing *wing,
					     u64 addw, u64 seq,
					     unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	boow int_sew = fwags & AMDGPU_FENCE_FWAG_INT;

	/* WEWEASE_MEM - fwush caches, send int */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WEWEASE_MEM, 5));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, DATA_SEW(wwite64bit ? 2 : 1) | INT_SEW(int_sew ? 2 : 0));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq));
}

/*
 * IB stuff
 */
/**
 * gfx_v7_0_wing_emit_ib_gfx - emit an IB (Indiwect Buffew) on the wing
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @job: job to wetwieve vmid fwom
 * @ib: amdgpu indiwect buffew object
 * @fwags: options (AMDGPU_HAVE_CTX_SWITCH)
 *
 * Emits an DE (dwawing engine) ow CE (constant engine) IB
 * on the gfx wing.  IBs awe usuawwy genewated by usewspace
 * accewewation dwivews and submitted to the kewnew fow
 * scheduwing on the wing.  This function scheduwes the IB
 * on the gfx wing fow execution by the GPU.
 */
static void gfx_v7_0_wing_emit_ib_gfx(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 headew, contwow = 0;

	/* insewt SWITCH_BUFFEW packet befowe fiwst IB in the wing fwame */
	if (fwags & AMDGPU_HAVE_CTX_SWITCH) {
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
		amdgpu_wing_wwite(wing, 0);
	}

	if (ib->fwags & AMDGPU_IB_FWAG_CE)
		headew = PACKET3(PACKET3_INDIWECT_BUFFEW_CONST, 2);
	ewse
		headew = PACKET3(PACKET3_INDIWECT_BUFFEW, 2);

	contwow |= ib->wength_dw | (vmid << 24);

	amdgpu_wing_wwite(wing, headew);
	amdgpu_wing_wwite(wing,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addw & 0xFFFFFFFC));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFFFF);
	amdgpu_wing_wwite(wing, contwow);
}

static void gfx_v7_0_wing_emit_ib_compute(stwuct amdgpu_wing *wing,
					  stwuct amdgpu_job *job,
					  stwuct amdgpu_ib *ib,
					  uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 contwow = INDIWECT_BUFFEW_VAWID | ib->wength_dw | (vmid << 24);

	/* Cuwwentwy, thewe is a high possibiwity to get wave ID mismatch
	 * between ME and GDS, weading to a hw deadwock, because ME genewates
	 * diffewent wave IDs than the GDS expects. This situation happens
	 * wandomwy when at weast 5 compute pipes use GDS owdewed append.
	 * The wave IDs genewated by ME awe awso wwong aftew suspend/wesume.
	 * Those awe pwobabwy bugs somewhewe ewse in the kewnew dwivew.
	 *
	 * Wwiting GDS_COMPUTE_MAX_WAVE_ID wesets wave ID countews in ME and
	 * GDS to 0 fow this wing (me/pipe).
	 */
	if (ib->fwags & AMDGPU_IB_FWAG_WESET_GDS_MAX_WAVE_ID) {
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		amdgpu_wing_wwite(wing, mmGDS_COMPUTE_MAX_WAVE_ID - PACKET3_SET_CONFIG_WEG_STAWT);
		amdgpu_wing_wwite(wing, wing->adev->gds.gds_compute_max_wave_id);
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	amdgpu_wing_wwite(wing,
#ifdef __BIG_ENDIAN
					  (2 << 0) |
#endif
					  (ib->gpu_addw & 0xFFFFFFFC));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFFFF);
	amdgpu_wing_wwite(wing, contwow);
}

static void gfx_v7_wing_emit_cntxcntw(stwuct amdgpu_wing *wing, uint32_t fwags)
{
	uint32_t dw2 = 0;

	dw2 |= 0x80000000; /* set woad_enabwe othewwise this package is just NOPs */
	if (fwags & AMDGPU_HAVE_CTX_SWITCH) {
		gfx_v7_0_wing_emit_vgt_fwush(wing);
		/* set woad_gwobaw_config & woad_gwobaw_uconfig */
		dw2 |= 0x8001;
		/* set woad_cs_sh_wegs */
		dw2 |= 0x01000000;
		/* set woad_pew_context_state & woad_gfx_sh_wegs */
		dw2 |= 0x10002;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	amdgpu_wing_wwite(wing, dw2);
	amdgpu_wing_wwite(wing, 0);
}

/**
 * gfx_v7_0_wing_test_ib - basic wing IB test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Awwocate an IB and execute it on the gfx wing (CIK).
 * Pwovides a basic gfx wing test to vewify that IBs awe wowking.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int gfx_v7_0_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;
	uint32_t tmp = 0;
	wong w;

	WWEG32(mmSCWATCH_WEG0, 0xCAFEDEAD);
	memset(&ib, 0, sizeof(ib));
	w = amdgpu_ib_get(adev, NUWW, 256, AMDGPU_IB_POOW_DIWECT, &ib);
	if (w)
		wetuwn w;

	ib.ptw[0] = PACKET3(PACKET3_SET_UCONFIG_WEG, 1);
	ib.ptw[1] = mmSCWATCH_WEG0 - PACKET3_SET_UCONFIG_WEG_STAWT;
	ib.ptw[2] = 0xDEADBEEF;
	ib.wength_dw = 3;

	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto ewwow;
	} ewse if (w < 0) {
		goto ewwow;
	}
	tmp = WWEG32(mmSCWATCH_WEG0);
	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

ewwow:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
	wetuwn w;
}

/*
 * CP.
 * On CIK, gfx and compute now have independent command pwocessows.
 *
 * GFX
 * Gfx consists of a singwe wing and can pwocess both gfx jobs and
 * compute jobs.  The gfx CP consists of thwee micwoengines (ME):
 * PFP - Pwe-Fetch Pawsew
 * ME - Micwo Engine
 * CE - Constant Engine
 * The PFP and ME make up what is considewed the Dwawing Engine (DE).
 * The CE is an asynchwonous engine used fow updating buffew desciptows
 * used by the DE so that they can be woaded into cache in pawawwew
 * whiwe the DE is pwocessing state update packets.
 *
 * Compute
 * The compute CP consists of two micwoengines (ME):
 * MEC1 - Compute MicwoEngine 1
 * MEC2 - Compute MicwoEngine 2
 * Each MEC suppowts 4 compute pipes and each pipe suppowts 8 queues.
 * The queues awe exposed to usewspace and awe pwogwammed diwectwy
 * by the compute wuntime.
 */
/**
 * gfx_v7_0_cp_gfx_enabwe - enabwe/disabwe the gfx CP MEs
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe ow disabwe the MEs
 *
 * Hawts ow unhawts the gfx MEs.
 */
static void gfx_v7_0_cp_gfx_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32(mmCP_ME_CNTW, 0);
	ewse
		WWEG32(mmCP_ME_CNTW, (CP_ME_CNTW__ME_HAWT_MASK |
				      CP_ME_CNTW__PFP_HAWT_MASK |
				      CP_ME_CNTW__CE_HAWT_MASK));
	udeway(50);
}

/**
 * gfx_v7_0_cp_gfx_woad_micwocode - woad the gfx CP ME ucode
 *
 * @adev: amdgpu_device pointew
 *
 * Woads the gfx PFP, ME, and CE ucode.
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int gfx_v7_0_cp_gfx_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct gfx_fiwmwawe_headew_v1_0 *pfp_hdw;
	const stwuct gfx_fiwmwawe_headew_v1_0 *ce_hdw;
	const stwuct gfx_fiwmwawe_headew_v1_0 *me_hdw;
	const __we32 *fw_data;
	unsigned i, fw_size;

	if (!adev->gfx.me_fw || !adev->gfx.pfp_fw || !adev->gfx.ce_fw)
		wetuwn -EINVAW;

	pfp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.pfp_fw->data;
	ce_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.ce_fw->data;
	me_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.me_fw->data;

	amdgpu_ucode_pwint_gfx_hdw(&pfp_hdw->headew);
	amdgpu_ucode_pwint_gfx_hdw(&ce_hdw->headew);
	amdgpu_ucode_pwint_gfx_hdw(&me_hdw->headew);
	adev->gfx.pfp_fw_vewsion = we32_to_cpu(pfp_hdw->headew.ucode_vewsion);
	adev->gfx.ce_fw_vewsion = we32_to_cpu(ce_hdw->headew.ucode_vewsion);
	adev->gfx.me_fw_vewsion = we32_to_cpu(me_hdw->headew.ucode_vewsion);
	adev->gfx.me_featuwe_vewsion = we32_to_cpu(me_hdw->ucode_featuwe_vewsion);
	adev->gfx.ce_featuwe_vewsion = we32_to_cpu(ce_hdw->ucode_featuwe_vewsion);
	adev->gfx.pfp_featuwe_vewsion = we32_to_cpu(pfp_hdw->ucode_featuwe_vewsion);

	gfx_v7_0_cp_gfx_enabwe(adev, fawse);

	/* PFP */
	fw_data = (const __we32 *)
		(adev->gfx.pfp_fw->data +
		 we32_to_cpu(pfp_hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(pfp_hdw->headew.ucode_size_bytes) / 4;
	WWEG32(mmCP_PFP_UCODE_ADDW, 0);
	fow (i = 0; i < fw_size; i++)
		WWEG32(mmCP_PFP_UCODE_DATA, we32_to_cpup(fw_data++));
	WWEG32(mmCP_PFP_UCODE_ADDW, adev->gfx.pfp_fw_vewsion);

	/* CE */
	fw_data = (const __we32 *)
		(adev->gfx.ce_fw->data +
		 we32_to_cpu(ce_hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(ce_hdw->headew.ucode_size_bytes) / 4;
	WWEG32(mmCP_CE_UCODE_ADDW, 0);
	fow (i = 0; i < fw_size; i++)
		WWEG32(mmCP_CE_UCODE_DATA, we32_to_cpup(fw_data++));
	WWEG32(mmCP_CE_UCODE_ADDW, adev->gfx.ce_fw_vewsion);

	/* ME */
	fw_data = (const __we32 *)
		(adev->gfx.me_fw->data +
		 we32_to_cpu(me_hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(me_hdw->headew.ucode_size_bytes) / 4;
	WWEG32(mmCP_ME_WAM_WADDW, 0);
	fow (i = 0; i < fw_size; i++)
		WWEG32(mmCP_ME_WAM_DATA, we32_to_cpup(fw_data++));
	WWEG32(mmCP_ME_WAM_WADDW, adev->gfx.me_fw_vewsion);

	wetuwn 0;
}

/**
 * gfx_v7_0_cp_gfx_stawt - stawt the gfx wing
 *
 * @adev: amdgpu_device pointew
 *
 * Enabwes the wing and woads the cweaw state context and othew
 * packets wequiwed to init the wing.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int gfx_v7_0_cp_gfx_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->gfx.gfx_wing[0];
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;
	int w, i;

	/* init the CP */
	WWEG32(mmCP_MAX_CONTEXT, adev->gfx.config.max_hw_contexts - 1);
	WWEG32(mmCP_ENDIAN_SWAP, 0);
	WWEG32(mmCP_DEVICE_ID, 1);

	gfx_v7_0_cp_gfx_enabwe(adev, twue);

	w = amdgpu_wing_awwoc(wing, gfx_v7_0_get_csb_size(adev) + 8);
	if (w) {
		DWM_EWWOW("amdgpu: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}

	/* init the CE pawtitions.  CE onwy used fow gfx on CIK */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_wing_wwite(wing, PACKET3_BASE_INDEX(CE_PAWTITION_BASE));
	amdgpu_wing_wwite(wing, 0x8000);
	amdgpu_wing_wwite(wing, 0x8000);

	/* cweaw state buffew */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	amdgpu_wing_wwite(wing, PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	amdgpu_wing_wwite(wing, 0x80000000);
	amdgpu_wing_wwite(wing, 0x80000000);

	fow (sect = adev->gfx.wwc.cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				amdgpu_wing_wwite(wing,
						  PACKET3(PACKET3_SET_CONTEXT_WEG, ext->weg_count));
				amdgpu_wing_wwite(wing, ext->weg_index - PACKET3_SET_CONTEXT_WEG_STAWT);
				fow (i = 0; i < ext->weg_count; i++)
					amdgpu_wing_wwite(wing, ext->extent[i]);
			}
		}
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_CONTEXT_WEG, 2));
	amdgpu_wing_wwite(wing, mmPA_SC_WASTEW_CONFIG - PACKET3_SET_CONTEXT_WEG_STAWT);
	amdgpu_wing_wwite(wing, adev->gfx.config.wb_config[0][0].wastew_config);
	amdgpu_wing_wwite(wing, adev->gfx.config.wb_config[0][0].wastew_config_1);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	amdgpu_wing_wwite(wing, PACKET3_PWEAMBWE_END_CWEAW_STATE);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CWEAW_STATE, 0));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_CONTEXT_WEG, 2));
	amdgpu_wing_wwite(wing, 0x00000316);
	amdgpu_wing_wwite(wing, 0x0000000e); /* VGT_VEWTEX_WEUSE_BWOCK_CNTW */
	amdgpu_wing_wwite(wing, 0x00000010); /* VGT_OUT_DEAWWOC_CNTW */

	amdgpu_wing_commit(wing);

	wetuwn 0;
}

/**
 * gfx_v7_0_cp_gfx_wesume - setup the gfx wing buffew wegistews
 *
 * @adev: amdgpu_device pointew
 *
 * Pwogwam the wocation and size of the gfx wing buffew
 * and test it to make suwe it's wowking.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int gfx_v7_0_cp_gfx_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 tmp;
	u32 wb_bufsz;
	u64 wb_addw, wptw_addw;
	int w;

	WWEG32(mmCP_SEM_WAIT_TIMEW, 0x0);
	if (adev->asic_type != CHIP_HAWAII)
		WWEG32(mmCP_SEM_INCOMPWETE_TIMEW_CNTW, 0x0);

	/* Set the wwite pointew deway */
	WWEG32(mmCP_WB_WPTW_DEWAY, 0);

	/* set the WB to use vmid 0 */
	WWEG32(mmCP_WB_VMID, 0);

	WWEG32(mmSCWATCH_ADDW, 0);

	/* wing 0 - compute and gfx */
	/* Set wing buffew size */
	wing = &adev->gfx.gfx_wing[0];
	wb_bufsz = owdew_base_2(wing->wing_size / 8);
	tmp = (owdew_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8) | wb_bufsz;
#ifdef __BIG_ENDIAN
	tmp |= 2 << CP_WB0_CNTW__BUF_SWAP__SHIFT;
#endif
	WWEG32(mmCP_WB0_CNTW, tmp);

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(mmCP_WB0_CNTW, tmp | CP_WB0_CNTW__WB_WPTW_WW_ENA_MASK);
	wing->wptw = 0;
	WWEG32(mmCP_WB0_WPTW, wowew_32_bits(wing->wptw));

	/* set the wb addwess wethew it's enabwed ow not */
	wptw_addw = wing->wptw_gpu_addw;
	WWEG32(mmCP_WB0_WPTW_ADDW, wowew_32_bits(wptw_addw));
	WWEG32(mmCP_WB0_WPTW_ADDW_HI, uppew_32_bits(wptw_addw) & 0xFF);

	/* scwatch wegistew shadowing is no wongew suppowted */
	WWEG32(mmSCWATCH_UMSK, 0);

	mdeway(1);
	WWEG32(mmCP_WB0_CNTW, tmp);

	wb_addw = wing->gpu_addw >> 8;
	WWEG32(mmCP_WB0_BASE, wb_addw);
	WWEG32(mmCP_WB0_BASE_HI, uppew_32_bits(wb_addw));

	/* stawt the wing */
	gfx_v7_0_cp_gfx_stawt(adev);
	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static u64 gfx_v7_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	wetuwn *wing->wptw_cpu_addw;
}

static u64 gfx_v7_0_wing_get_wptw_gfx(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(mmCP_WB0_WPTW);
}

static void gfx_v7_0_wing_set_wptw_gfx(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32(mmCP_WB0_WPTW, wowew_32_bits(wing->wptw));
	(void)WWEG32(mmCP_WB0_WPTW);
}

static u64 gfx_v7_0_wing_get_wptw_compute(stwuct amdgpu_wing *wing)
{
	/* XXX check if swapping is necessawy on BE */
	wetuwn *wing->wptw_cpu_addw;
}

static void gfx_v7_0_wing_set_wptw_compute(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	/* XXX check if swapping is necessawy on BE */
	*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
	WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
}

/**
 * gfx_v7_0_cp_compute_enabwe - enabwe/disabwe the compute CP MEs
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe ow disabwe the MEs
 *
 * Hawts ow unhawts the compute MEs.
 */
static void gfx_v7_0_cp_compute_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		WWEG32(mmCP_MEC_CNTW, 0);
	ewse
		WWEG32(mmCP_MEC_CNTW, (CP_MEC_CNTW__MEC_ME1_HAWT_MASK |
				       CP_MEC_CNTW__MEC_ME2_HAWT_MASK));
	udeway(50);
}

/**
 * gfx_v7_0_cp_compute_woad_micwocode - woad the compute CP ME ucode
 *
 * @adev: amdgpu_device pointew
 *
 * Woads the compute MEC1&2 ucode.
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int gfx_v7_0_cp_compute_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct gfx_fiwmwawe_headew_v1_0 *mec_hdw;
	const __we32 *fw_data;
	unsigned i, fw_size;

	if (!adev->gfx.mec_fw)
		wetuwn -EINVAW;

	mec_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;
	amdgpu_ucode_pwint_gfx_hdw(&mec_hdw->headew);
	adev->gfx.mec_fw_vewsion = we32_to_cpu(mec_hdw->headew.ucode_vewsion);
	adev->gfx.mec_featuwe_vewsion = we32_to_cpu(
					mec_hdw->ucode_featuwe_vewsion);

	gfx_v7_0_cp_compute_enabwe(adev, fawse);

	/* MEC1 */
	fw_data = (const __we32 *)
		(adev->gfx.mec_fw->data +
		 we32_to_cpu(mec_hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(mec_hdw->headew.ucode_size_bytes) / 4;
	WWEG32(mmCP_MEC_ME1_UCODE_ADDW, 0);
	fow (i = 0; i < fw_size; i++)
		WWEG32(mmCP_MEC_ME1_UCODE_DATA, we32_to_cpup(fw_data++));
	WWEG32(mmCP_MEC_ME1_UCODE_ADDW, 0);

	if (adev->asic_type == CHIP_KAVEWI) {
		const stwuct gfx_fiwmwawe_headew_v1_0 *mec2_hdw;

		if (!adev->gfx.mec2_fw)
			wetuwn -EINVAW;

		mec2_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec2_fw->data;
		amdgpu_ucode_pwint_gfx_hdw(&mec2_hdw->headew);
		adev->gfx.mec2_fw_vewsion = we32_to_cpu(mec2_hdw->headew.ucode_vewsion);
		adev->gfx.mec2_featuwe_vewsion = we32_to_cpu(
				mec2_hdw->ucode_featuwe_vewsion);

		/* MEC2 */
		fw_data = (const __we32 *)
			(adev->gfx.mec2_fw->data +
			 we32_to_cpu(mec2_hdw->headew.ucode_awway_offset_bytes));
		fw_size = we32_to_cpu(mec2_hdw->headew.ucode_size_bytes) / 4;
		WWEG32(mmCP_MEC_ME2_UCODE_ADDW, 0);
		fow (i = 0; i < fw_size; i++)
			WWEG32(mmCP_MEC_ME2_UCODE_DATA, we32_to_cpup(fw_data++));
		WWEG32(mmCP_MEC_ME2_UCODE_ADDW, 0);
	}

	wetuwn 0;
}

/**
 * gfx_v7_0_cp_compute_fini - stop the compute queues
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the compute queues and teaw down the dwivew queue
 * info.
 */
static void gfx_v7_0_cp_compute_fini(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];

		amdgpu_bo_fwee_kewnew(&wing->mqd_obj, NUWW, NUWW);
	}
}

static void gfx_v7_0_mec_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->gfx.mec.hpd_eop_obj, NUWW, NUWW);
}

static int gfx_v7_0_mec_init(stwuct amdgpu_device *adev)
{
	int w;
	u32 *hpd;
	size_t mec_hpd_size;

	bitmap_zewo(adev->gfx.mec_bitmap[0].queue_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownewship of the wewevant compute queues */
	amdgpu_gfx_compute_queue_acquiwe(adev);

	/* awwocate space fow AWW pipes (even the ones we don't own) */
	mec_hpd_size = adev->gfx.mec.num_mec * adev->gfx.mec.num_pipe_pew_mec
		* GFX7_MEC_HPD_SIZE * 2;

	w = amdgpu_bo_cweate_wesewved(adev, mec_hpd_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM |
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.mec.hpd_eop_obj,
				      &adev->gfx.mec.hpd_eop_gpu_addw,
				      (void **)&hpd);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate, pin ow map of HDP EOP bo faiwed\n", w);
		gfx_v7_0_mec_fini(adev);
		wetuwn w;
	}

	/* cweaw memowy.  Not suwe if this is wequiwed ow not */
	memset(hpd, 0, mec_hpd_size);

	amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
	amdgpu_bo_unwesewve(adev->gfx.mec.hpd_eop_obj);

	wetuwn 0;
}

stwuct hqd_wegistews {
	u32 cp_mqd_base_addw;
	u32 cp_mqd_base_addw_hi;
	u32 cp_hqd_active;
	u32 cp_hqd_vmid;
	u32 cp_hqd_pewsistent_state;
	u32 cp_hqd_pipe_pwiowity;
	u32 cp_hqd_queue_pwiowity;
	u32 cp_hqd_quantum;
	u32 cp_hqd_pq_base;
	u32 cp_hqd_pq_base_hi;
	u32 cp_hqd_pq_wptw;
	u32 cp_hqd_pq_wptw_wepowt_addw;
	u32 cp_hqd_pq_wptw_wepowt_addw_hi;
	u32 cp_hqd_pq_wptw_poww_addw;
	u32 cp_hqd_pq_wptw_poww_addw_hi;
	u32 cp_hqd_pq_doowbeww_contwow;
	u32 cp_hqd_pq_wptw;
	u32 cp_hqd_pq_contwow;
	u32 cp_hqd_ib_base_addw;
	u32 cp_hqd_ib_base_addw_hi;
	u32 cp_hqd_ib_wptw;
	u32 cp_hqd_ib_contwow;
	u32 cp_hqd_iq_timew;
	u32 cp_hqd_iq_wptw;
	u32 cp_hqd_dequeue_wequest;
	u32 cp_hqd_dma_offwoad;
	u32 cp_hqd_sema_cmd;
	u32 cp_hqd_msg_type;
	u32 cp_hqd_atomic0_pweop_wo;
	u32 cp_hqd_atomic0_pweop_hi;
	u32 cp_hqd_atomic1_pweop_wo;
	u32 cp_hqd_atomic1_pweop_hi;
	u32 cp_hqd_hq_scheduwew0;
	u32 cp_hqd_hq_scheduwew1;
	u32 cp_mqd_contwow;
};

static void gfx_v7_0_compute_pipe_init(stwuct amdgpu_device *adev,
				       int mec, int pipe)
{
	u64 eop_gpu_addw;
	u32 tmp;
	size_t eop_offset = (mec * adev->gfx.mec.num_pipe_pew_mec + pipe)
			    * GFX7_MEC_HPD_SIZE * 2;

	mutex_wock(&adev->swbm_mutex);
	eop_gpu_addw = adev->gfx.mec.hpd_eop_gpu_addw + eop_offset;

	cik_swbm_sewect(adev, mec + 1, pipe, 0, 0);

	/* wwite the EOP addw */
	WWEG32(mmCP_HPD_EOP_BASE_ADDW, eop_gpu_addw >> 8);
	WWEG32(mmCP_HPD_EOP_BASE_ADDW_HI, uppew_32_bits(eop_gpu_addw) >> 8);

	/* set the VMID assigned */
	WWEG32(mmCP_HPD_EOP_VMID, 0);

	/* set the EOP size, wegistew vawue is 2^(EOP_SIZE+1) dwowds */
	tmp = WWEG32(mmCP_HPD_EOP_CONTWOW);
	tmp &= ~CP_HPD_EOP_CONTWOW__EOP_SIZE_MASK;
	tmp |= owdew_base_2(GFX7_MEC_HPD_SIZE / 8);
	WWEG32(mmCP_HPD_EOP_CONTWOW, tmp);

	cik_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);
}

static int gfx_v7_0_mqd_deactivate(stwuct amdgpu_device *adev)
{
	int i;

	/* disabwe the queue if it's active */
	if (WWEG32(mmCP_HQD_ACTIVE) & 1) {
		WWEG32(mmCP_HQD_DEQUEUE_WEQUEST, 1);
		fow (i = 0; i < adev->usec_timeout; i++) {
			if (!(WWEG32(mmCP_HQD_ACTIVE) & 1))
				bweak;
			udeway(1);
		}

		if (i == adev->usec_timeout)
			wetuwn -ETIMEDOUT;

		WWEG32(mmCP_HQD_DEQUEUE_WEQUEST, 0);
		WWEG32(mmCP_HQD_PQ_WPTW, 0);
		WWEG32(mmCP_HQD_PQ_WPTW, 0);
	}

	wetuwn 0;
}

static void gfx_v7_0_mqd_init(stwuct amdgpu_device *adev,
			     stwuct cik_mqd *mqd,
			     uint64_t mqd_gpu_addw,
			     stwuct amdgpu_wing *wing)
{
	u64 hqd_gpu_addw;
	u64 wb_gpu_addw;

	/* init the mqd stwuct */
	memset(mqd, 0, sizeof(stwuct cik_mqd));

	mqd->headew = 0xC0310800;
	mqd->compute_static_thwead_mgmt_se0 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se1 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se2 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se3 = 0xffffffff;

	/* enabwe doowbeww? */
	mqd->cp_hqd_pq_doowbeww_contwow =
		WWEG32(mmCP_HQD_PQ_DOOWBEWW_CONTWOW);
	if (wing->use_doowbeww)
		mqd->cp_hqd_pq_doowbeww_contwow |= CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_EN_MASK;
	ewse
		mqd->cp_hqd_pq_doowbeww_contwow &= ~CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_EN_MASK;

	/* set the pointew to the MQD */
	mqd->cp_mqd_base_addw_wo = mqd_gpu_addw & 0xfffffffc;
	mqd->cp_mqd_base_addw_hi = uppew_32_bits(mqd_gpu_addw);

	/* set MQD vmid to 0 */
	mqd->cp_mqd_contwow = WWEG32(mmCP_MQD_CONTWOW);
	mqd->cp_mqd_contwow &= ~CP_MQD_CONTWOW__VMID_MASK;

	/* set the pointew to the HQD, this is simiwaw CP_WB0_BASE/_HI */
	hqd_gpu_addw = wing->gpu_addw >> 8;
	mqd->cp_hqd_pq_base_wo = hqd_gpu_addw;
	mqd->cp_hqd_pq_base_hi = uppew_32_bits(hqd_gpu_addw);

	/* set up the HQD, this is simiwaw to CP_WB0_CNTW */
	mqd->cp_hqd_pq_contwow = WWEG32(mmCP_HQD_PQ_CONTWOW);
	mqd->cp_hqd_pq_contwow &=
		~(CP_HQD_PQ_CONTWOW__QUEUE_SIZE_MASK |
				CP_HQD_PQ_CONTWOW__WPTW_BWOCK_SIZE_MASK);

	mqd->cp_hqd_pq_contwow |=
		owdew_base_2(wing->wing_size / 8);
	mqd->cp_hqd_pq_contwow |=
		(owdew_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8);
#ifdef __BIG_ENDIAN
	mqd->cp_hqd_pq_contwow |=
		2 << CP_HQD_PQ_CONTWOW__ENDIAN_SWAP__SHIFT;
#endif
	mqd->cp_hqd_pq_contwow &=
		~(CP_HQD_PQ_CONTWOW__UNOWD_DISPATCH_MASK |
				CP_HQD_PQ_CONTWOW__WOQ_PQ_IB_FWIP_MASK |
				CP_HQD_PQ_CONTWOW__PQ_VOWATIWE_MASK);
	mqd->cp_hqd_pq_contwow |=
		CP_HQD_PQ_CONTWOW__PWIV_STATE_MASK |
		CP_HQD_PQ_CONTWOW__KMD_QUEUE_MASK; /* assuming kewnew queue contwow */

	/* onwy used if CP_PQ_WPTW_POWW_CNTW.CP_PQ_WPTW_POWW_CNTW__EN_MASK=1 */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_poww_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_poww_addw_hi = uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* set the wb addwess wethew it's enabwed ow not */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_wepowt_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_wepowt_addw_hi =
		uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* enabwe the doowbeww if wequested */
	if (wing->use_doowbeww) {
		mqd->cp_hqd_pq_doowbeww_contwow =
			WWEG32(mmCP_HQD_PQ_DOOWBEWW_CONTWOW);
		mqd->cp_hqd_pq_doowbeww_contwow &=
			~CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET_MASK;
		mqd->cp_hqd_pq_doowbeww_contwow |=
			(wing->doowbeww_index <<
			 CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET__SHIFT);
		mqd->cp_hqd_pq_doowbeww_contwow |=
			CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_EN_MASK;
		mqd->cp_hqd_pq_doowbeww_contwow &=
			~(CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_SOUWCE_MASK |
					CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_HIT_MASK);

	} ewse {
		mqd->cp_hqd_pq_doowbeww_contwow = 0;
	}

	/* wead and wwite pointews, simiwaw to CP_WB0_WPTW/_WPTW */
	wing->wptw = 0;
	mqd->cp_hqd_pq_wptw = wowew_32_bits(wing->wptw);
	mqd->cp_hqd_pq_wptw = WWEG32(mmCP_HQD_PQ_WPTW);

	/* set the vmid fow the queue */
	mqd->cp_hqd_vmid = 0;

	/* defauwts */
	mqd->cp_hqd_ib_contwow = WWEG32(mmCP_HQD_IB_CONTWOW);
	mqd->cp_hqd_ib_base_addw_wo = WWEG32(mmCP_HQD_IB_BASE_ADDW);
	mqd->cp_hqd_ib_base_addw_hi = WWEG32(mmCP_HQD_IB_BASE_ADDW_HI);
	mqd->cp_hqd_ib_wptw = WWEG32(mmCP_HQD_IB_WPTW);
	mqd->cp_hqd_pewsistent_state = WWEG32(mmCP_HQD_PEWSISTENT_STATE);
	mqd->cp_hqd_sema_cmd = WWEG32(mmCP_HQD_SEMA_CMD);
	mqd->cp_hqd_msg_type = WWEG32(mmCP_HQD_MSG_TYPE);
	mqd->cp_hqd_atomic0_pweop_wo = WWEG32(mmCP_HQD_ATOMIC0_PWEOP_WO);
	mqd->cp_hqd_atomic0_pweop_hi = WWEG32(mmCP_HQD_ATOMIC0_PWEOP_HI);
	mqd->cp_hqd_atomic1_pweop_wo = WWEG32(mmCP_HQD_ATOMIC1_PWEOP_WO);
	mqd->cp_hqd_atomic1_pweop_hi = WWEG32(mmCP_HQD_ATOMIC1_PWEOP_HI);
	mqd->cp_hqd_pq_wptw = WWEG32(mmCP_HQD_PQ_WPTW);
	mqd->cp_hqd_quantum = WWEG32(mmCP_HQD_QUANTUM);
	mqd->cp_hqd_pipe_pwiowity = WWEG32(mmCP_HQD_PIPE_PWIOWITY);
	mqd->cp_hqd_queue_pwiowity = WWEG32(mmCP_HQD_QUEUE_PWIOWITY);
	mqd->cp_hqd_iq_wptw = WWEG32(mmCP_HQD_IQ_WPTW);

	/* activate the queue */
	mqd->cp_hqd_active = 1;
}

static int gfx_v7_0_mqd_commit(stwuct amdgpu_device *adev, stwuct cik_mqd *mqd)
{
	uint32_t tmp;
	uint32_t mqd_weg;
	uint32_t *mqd_data;

	/* HQD wegistews extend fwom mmCP_MQD_BASE_ADDW to mmCP_MQD_CONTWOW */
	mqd_data = &mqd->cp_mqd_base_addw_wo;

	/* disabwe wptw powwing */
	tmp = WWEG32(mmCP_PQ_WPTW_POWW_CNTW);
	tmp = WEG_SET_FIEWD(tmp, CP_PQ_WPTW_POWW_CNTW, EN, 0);
	WWEG32(mmCP_PQ_WPTW_POWW_CNTW, tmp);

	/* pwogwam aww HQD wegistews */
	fow (mqd_weg = mmCP_HQD_VMID; mqd_weg <= mmCP_MQD_CONTWOW; mqd_weg++)
		WWEG32(mqd_weg, mqd_data[mqd_weg - mmCP_MQD_BASE_ADDW]);

	/* activate the HQD */
	fow (mqd_weg = mmCP_MQD_BASE_ADDW; mqd_weg <= mmCP_HQD_ACTIVE; mqd_weg++)
		WWEG32(mqd_weg, mqd_data[mqd_weg - mmCP_MQD_BASE_ADDW]);

	wetuwn 0;
}

static int gfx_v7_0_compute_queue_init(stwuct amdgpu_device *adev, int wing_id)
{
	int w;
	u64 mqd_gpu_addw;
	stwuct cik_mqd *mqd;
	stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[wing_id];

	w = amdgpu_bo_cweate_wesewved(adev, sizeof(stwuct cik_mqd), PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT, &wing->mqd_obj,
				      &mqd_gpu_addw, (void **)&mqd);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate MQD bo faiwed\n", w);
		wetuwn w;
	}

	mutex_wock(&adev->swbm_mutex);
	cik_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);

	gfx_v7_0_mqd_init(adev, mqd, mqd_gpu_addw, wing);
	gfx_v7_0_mqd_deactivate(adev);
	gfx_v7_0_mqd_commit(adev, mqd);

	cik_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	amdgpu_bo_kunmap(wing->mqd_obj);
	amdgpu_bo_unwesewve(wing->mqd_obj);
	wetuwn 0;
}

/**
 * gfx_v7_0_cp_compute_wesume - setup the compute queue wegistews
 *
 * @adev: amdgpu_device pointew
 *
 * Pwogwam the compute queues and test them to make suwe they
 * awe wowking.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int gfx_v7_0_cp_compute_wesume(stwuct amdgpu_device *adev)
{
	int w, i, j;
	u32 tmp;
	stwuct amdgpu_wing *wing;

	/* fix up chicken bits */
	tmp = WWEG32(mmCP_CPF_DEBUG);
	tmp |= (1 << 23);
	WWEG32(mmCP_CPF_DEBUG, tmp);

	/* init aww pipes (even the ones we don't own) */
	fow (i = 0; i < adev->gfx.mec.num_mec; i++)
		fow (j = 0; j < adev->gfx.mec.num_pipe_pew_mec; j++)
			gfx_v7_0_compute_pipe_init(adev, i, j);

	/* init the queues */
	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		w = gfx_v7_0_compute_queue_init(adev, i);
		if (w) {
			gfx_v7_0_cp_compute_fini(adev);
			wetuwn w;
		}
	}

	gfx_v7_0_cp_compute_enabwe(adev, twue);

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		wing = &adev->gfx.compute_wing[i];
		amdgpu_wing_test_hewpew(wing);
	}

	wetuwn 0;
}

static void gfx_v7_0_cp_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	gfx_v7_0_cp_gfx_enabwe(adev, enabwe);
	gfx_v7_0_cp_compute_enabwe(adev, enabwe);
}

static int gfx_v7_0_cp_woad_micwocode(stwuct amdgpu_device *adev)
{
	int w;

	w = gfx_v7_0_cp_gfx_woad_micwocode(adev);
	if (w)
		wetuwn w;
	w = gfx_v7_0_cp_compute_woad_micwocode(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static void gfx_v7_0_enabwe_gui_idwe_intewwupt(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	u32 tmp = WWEG32(mmCP_INT_CNTW_WING0);

	if (enabwe)
		tmp |= (CP_INT_CNTW_WING0__CNTX_BUSY_INT_ENABWE_MASK |
				CP_INT_CNTW_WING0__CNTX_EMPTY_INT_ENABWE_MASK);
	ewse
		tmp &= ~(CP_INT_CNTW_WING0__CNTX_BUSY_INT_ENABWE_MASK |
				CP_INT_CNTW_WING0__CNTX_EMPTY_INT_ENABWE_MASK);
	WWEG32(mmCP_INT_CNTW_WING0, tmp);
}

static int gfx_v7_0_cp_wesume(stwuct amdgpu_device *adev)
{
	int w;

	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, fawse);

	w = gfx_v7_0_cp_woad_micwocode(adev);
	if (w)
		wetuwn w;

	w = gfx_v7_0_cp_gfx_wesume(adev);
	if (w)
		wetuwn w;
	w = gfx_v7_0_cp_compute_wesume(adev);
	if (w)
		wetuwn w;

	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);

	wetuwn 0;
}

/**
 * gfx_v7_0_wing_emit_pipewine_sync - cik vm fwush using the CP
 *
 * @wing: the wing to emit the commands to
 *
 * Sync the command pipewine with the PFP. E.g. wait fow evewything
 * to be compweted.
 */
static void gfx_v7_0_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_MEM_SPACE(1) | /* memowy */
				 WAIT_WEG_MEM_FUNCTION(3) | /* equaw */
				 WAIT_WEG_MEM_ENGINE(usepfp)));   /* pfp ow me */
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xffffffff);
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, 0xffffffff);
	amdgpu_wing_wwite(wing, 4); /* poww intewvaw */

	if (usepfp) {
		/* sync CE with ME to pwevent CE fetch CEIB befowe context switch done */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

/*
 * vm
 * VMID 0 is the physicaw GPU addwesses as used by the kewnew.
 * VMIDs 1-15 awe used fow usewspace cwients and awe handwed
 * by the amdgpu vm/hsa code.
 */
/**
 * gfx_v7_0_wing_emit_vm_fwush - cik vm fwush using the CP
 *
 * @wing: amdgpu_wing pointew
 * @vmid: vmid numbew to use
 * @pd_addw: addwess
 *
 * Update the page tabwe base and fwush the VM TWB
 * using the CP (CIK).
 */
static void gfx_v7_0_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					unsigned vmid, uint64_t pd_addw)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);

	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow the invawidate to compwete */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_OPEWATION(0) | /* wait */
				 WAIT_WEG_MEM_FUNCTION(0) |  /* awways */
				 WAIT_WEG_MEM_ENGINE(0))); /* me */
	amdgpu_wing_wwite(wing, mmVM_INVAWIDATE_WEQUEST);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, 0); /* wef */
	amdgpu_wing_wwite(wing, 0); /* mask */
	amdgpu_wing_wwite(wing, 0x20); /* poww intewvaw */

	/* compute doesn't have PFP */
	if (usepfp) {
		/* sync PFP to ME, othewwise we might get invawid PFP weads */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		amdgpu_wing_wwite(wing, 0x0);

		/* synce CE with ME to pwevent CE fetch CEIB befowe context switch done */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

static void gfx_v7_0_wing_emit_wweg(stwuct amdgpu_wing *wing,
				    uint32_t weg, uint32_t vaw)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(usepfp) |
				 WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, vaw);
}

/*
 * WWC
 * The WWC is a muwti-puwpose micwoengine that handwes a
 * vawiety of functions.
 */
static int gfx_v7_0_wwc_init(stwuct amdgpu_device *adev)
{
	const u32 *swc_ptw;
	u32 dws;
	const stwuct cs_section_def *cs_data;
	int w;

	/* awwocate wwc buffews */
	if (adev->fwags & AMD_IS_APU) {
		if (adev->asic_type == CHIP_KAVEWI) {
			adev->gfx.wwc.weg_wist = spectwe_wwc_save_westowe_wegistew_wist;
			adev->gfx.wwc.weg_wist_size =
				(u32)AWWAY_SIZE(spectwe_wwc_save_westowe_wegistew_wist);
		} ewse {
			adev->gfx.wwc.weg_wist = kawindi_wwc_save_westowe_wegistew_wist;
			adev->gfx.wwc.weg_wist_size =
				(u32)AWWAY_SIZE(kawindi_wwc_save_westowe_wegistew_wist);
		}
	}
	adev->gfx.wwc.cs_data = ci_cs_data;
	adev->gfx.wwc.cp_tabwe_size = AWIGN(CP_ME_TABWE_SIZE * 5 * 4, 2048); /* CP JT */
	adev->gfx.wwc.cp_tabwe_size += 64 * 1024; /* GDS */

	swc_ptw = adev->gfx.wwc.weg_wist;
	dws = adev->gfx.wwc.weg_wist_size;
	dws += (5 * 16) + 48 + 48 + 64;

	cs_data = adev->gfx.wwc.cs_data;

	if (swc_ptw) {
		/* init save westowe bwock */
		w = amdgpu_gfx_wwc_init_sw(adev, dws);
		if (w)
			wetuwn w;
	}

	if (cs_data) {
		/* init cweaw state bwock */
		w = amdgpu_gfx_wwc_init_csb(adev);
		if (w)
			wetuwn w;
	}

	if (adev->gfx.wwc.cp_tabwe_size) {
		w = amdgpu_gfx_wwc_init_cpt(adev);
		if (w)
			wetuwn w;
	}

	/* init spm vmid with 0xf */
	if (adev->gfx.wwc.funcs->update_spm_vmid)
		adev->gfx.wwc.funcs->update_spm_vmid(adev, 0xf);

	wetuwn 0;
}

static void gfx_v7_0_enabwe_wbpw(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 tmp;

	tmp = WWEG32(mmWWC_WB_CNTW);
	if (enabwe)
		tmp |= WWC_WB_CNTW__WOAD_BAWANCE_ENABWE_MASK;
	ewse
		tmp &= ~WWC_WB_CNTW__WOAD_BAWANCE_ENABWE_MASK;
	WWEG32(mmWWC_WB_CNTW, tmp);
}

static void gfx_v7_0_wait_fow_wwc_sewdes(stwuct amdgpu_device *adev)
{
	u32 i, j, k;
	u32 mask;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v7_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			fow (k = 0; k < adev->usec_timeout; k++) {
				if (WWEG32(mmWWC_SEWDES_CU_MASTEW_BUSY) == 0)
					bweak;
				udeway(1);
			}
		}
	}
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	mask = WWC_SEWDES_NONCU_MASTEW_BUSY__SE_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__GC_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC0_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC1_MASTEW_BUSY_MASK;
	fow (k = 0; k < adev->usec_timeout; k++) {
		if ((WWEG32(mmWWC_SEWDES_NONCU_MASTEW_BUSY) & mask) == 0)
			bweak;
		udeway(1);
	}
}

static void gfx_v7_0_update_wwc(stwuct amdgpu_device *adev, u32 wwc)
{
	u32 tmp;

	tmp = WWEG32(mmWWC_CNTW);
	if (tmp != wwc)
		WWEG32(mmWWC_CNTW, wwc);
}

static u32 gfx_v7_0_hawt_wwc(stwuct amdgpu_device *adev)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_CNTW);

	if (data & WWC_CNTW__WWC_ENABWE_F32_MASK) {
		u32 i;

		data &= ~WWC_CNTW__WWC_ENABWE_F32_MASK;
		WWEG32(mmWWC_CNTW, data);

		fow (i = 0; i < adev->usec_timeout; i++) {
			if ((WWEG32(mmWWC_GPM_STAT) & WWC_GPM_STAT__WWC_BUSY_MASK) == 0)
				bweak;
			udeway(1);
		}

		gfx_v7_0_wait_fow_wwc_sewdes(adev);
	}

	wetuwn owig;
}

static boow gfx_v7_0_is_wwc_enabwed(stwuct amdgpu_device *adev)
{
	wetuwn twue;
}

static void gfx_v7_0_set_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	u32 tmp, i, mask;

	tmp = 0x1 | (1 << 1);
	WWEG32(mmWWC_GPW_WEG2, tmp);

	mask = WWC_GPM_STAT__GFX_POWEW_STATUS_MASK |
		WWC_GPM_STAT__GFX_CWOCK_STATUS_MASK;
	fow (i = 0; i < adev->usec_timeout; i++) {
		if ((WWEG32(mmWWC_GPM_STAT) & mask) == mask)
			bweak;
		udeway(1);
	}

	fow (i = 0; i < adev->usec_timeout; i++) {
		if ((WWEG32(mmWWC_GPW_WEG2) & 0x1) == 0)
			bweak;
		udeway(1);
	}
}

static void gfx_v7_0_unset_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	u32 tmp;

	tmp = 0x1 | (0 << 1);
	WWEG32(mmWWC_GPW_WEG2, tmp);
}

/**
 * gfx_v7_0_wwc_stop - stop the WWC ME
 *
 * @adev: amdgpu_device pointew
 *
 * Hawt the WWC ME (MicwoEngine) (CIK).
 */
static void gfx_v7_0_wwc_stop(stwuct amdgpu_device *adev)
{
	WWEG32(mmWWC_CNTW, 0);

	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, fawse);

	gfx_v7_0_wait_fow_wwc_sewdes(adev);
}

/**
 * gfx_v7_0_wwc_stawt - stawt the WWC ME
 *
 * @adev: amdgpu_device pointew
 *
 * Unhawt the WWC ME (MicwoEngine) (CIK).
 */
static void gfx_v7_0_wwc_stawt(stwuct amdgpu_device *adev)
{
	WWEG32(mmWWC_CNTW, WWC_CNTW__WWC_ENABWE_F32_MASK);

	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);

	udeway(50);
}

static void gfx_v7_0_wwc_weset(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32(mmGWBM_SOFT_WESET);

	tmp |= GWBM_SOFT_WESET__SOFT_WESET_WWC_MASK;
	WWEG32(mmGWBM_SOFT_WESET, tmp);
	udeway(50);
	tmp &= ~GWBM_SOFT_WESET__SOFT_WESET_WWC_MASK;
	WWEG32(mmGWBM_SOFT_WESET, tmp);
	udeway(50);
}

/**
 * gfx_v7_0_wwc_wesume - setup the WWC hw
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawize the WWC wegistews, woad the ucode,
 * and stawt the WWC (CIK).
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int gfx_v7_0_wwc_wesume(stwuct amdgpu_device *adev)
{
	const stwuct wwc_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data;
	unsigned i, fw_size;
	u32 tmp;

	if (!adev->gfx.wwc_fw)
		wetuwn -EINVAW;

	hdw = (const stwuct wwc_fiwmwawe_headew_v1_0 *)adev->gfx.wwc_fw->data;
	amdgpu_ucode_pwint_wwc_hdw(&hdw->headew);
	adev->gfx.wwc_fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
	adev->gfx.wwc_featuwe_vewsion = we32_to_cpu(
					hdw->ucode_featuwe_vewsion);

	adev->gfx.wwc.funcs->stop(adev);

	/* disabwe CG */
	tmp = WWEG32(mmWWC_CGCG_CGWS_CTWW) & 0xfffffffc;
	WWEG32(mmWWC_CGCG_CGWS_CTWW, tmp);

	adev->gfx.wwc.funcs->weset(adev);

	gfx_v7_0_init_pg(adev);

	WWEG32(mmWWC_WB_CNTW_INIT, 0);
	WWEG32(mmWWC_WB_CNTW_MAX, 0x00008000);

	mutex_wock(&adev->gwbm_idx_mutex);
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	WWEG32(mmWWC_WB_INIT_CU_MASK, 0xffffffff);
	WWEG32(mmWWC_WB_PAWAMS, 0x00600408);
	WWEG32(mmWWC_WB_CNTW, 0x80000004);
	mutex_unwock(&adev->gwbm_idx_mutex);

	WWEG32(mmWWC_MC_CNTW, 0);
	WWEG32(mmWWC_UCODE_CNTW, 0);

	fw_data = (const __we32 *)
		(adev->gfx.wwc_fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
	WWEG32(mmWWC_GPM_UCODE_ADDW, 0);
	fow (i = 0; i < fw_size; i++)
		WWEG32(mmWWC_GPM_UCODE_DATA, we32_to_cpup(fw_data++));
	WWEG32(mmWWC_GPM_UCODE_ADDW, adev->gfx.wwc_fw_vewsion);

	/* XXX - find out what chips suppowt wbpw */
	gfx_v7_0_enabwe_wbpw(adev, fawse);

	if (adev->asic_type == CHIP_BONAIWE)
		WWEG32(mmWWC_DWIVEW_CPDMA_STATUS, 0);

	adev->gfx.wwc.funcs->stawt(adev);

	wetuwn 0;
}

static void gfx_v7_0_update_spm_vmid(stwuct amdgpu_device *adev, unsigned vmid)
{
	u32 data;

	amdgpu_gfx_off_ctww(adev, fawse);

	data = WWEG32(mmWWC_SPM_VMID);

	data &= ~WWC_SPM_VMID__WWC_SPM_VMID_MASK;
	data |= (vmid & WWC_SPM_VMID__WWC_SPM_VMID_MASK) << WWC_SPM_VMID__WWC_SPM_VMID__SHIFT;

	WWEG32(mmWWC_SPM_VMID, data);

	amdgpu_gfx_off_ctww(adev, twue);
}

static void gfx_v7_0_enabwe_cgcg(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 data, owig, tmp, tmp2;

	owig = data = WWEG32(mmWWC_CGCG_CGWS_CTWW);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGCG)) {
		gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);

		tmp = gfx_v7_0_hawt_wwc(adev);

		mutex_wock(&adev->gwbm_idx_mutex);
		gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
		WWEG32(mmWWC_SEWDES_WW_CU_MASTEW_MASK, 0xffffffff);
		WWEG32(mmWWC_SEWDES_WW_NONCU_MASTEW_MASK, 0xffffffff);
		tmp2 = WWC_SEWDES_WW_CTWW__BPM_ADDW_MASK |
			WWC_SEWDES_WW_CTWW__CGCG_OVEWWIDE_0_MASK |
			WWC_SEWDES_WW_CTWW__CGWS_ENABWE_MASK;
		WWEG32(mmWWC_SEWDES_WW_CTWW, tmp2);
		mutex_unwock(&adev->gwbm_idx_mutex);

		gfx_v7_0_update_wwc(adev, tmp);

		data |= WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK | WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK;
		if (owig != data)
			WWEG32(mmWWC_CGCG_CGWS_CTWW, data);

	} ewse {
		gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, fawse);

		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);

		data &= ~(WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK | WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK);
		if (owig != data)
			WWEG32(mmWWC_CGCG_CGWS_CTWW, data);

		gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);
	}
}

static void gfx_v7_0_enabwe_mgcg(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 data, owig, tmp = 0;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGCG)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) {
			if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CP_WS) {
				owig = data = WWEG32(mmCP_MEM_SWP_CNTW);
				data |= CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK;
				if (owig != data)
					WWEG32(mmCP_MEM_SWP_CNTW, data);
			}
		}

		owig = data = WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		data |= 0x00000001;
		data &= 0xfffffffd;
		if (owig != data)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data);

		tmp = gfx_v7_0_hawt_wwc(adev);

		mutex_wock(&adev->gwbm_idx_mutex);
		gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
		WWEG32(mmWWC_SEWDES_WW_CU_MASTEW_MASK, 0xffffffff);
		WWEG32(mmWWC_SEWDES_WW_NONCU_MASTEW_MASK, 0xffffffff);
		data = WWC_SEWDES_WW_CTWW__BPM_ADDW_MASK |
			WWC_SEWDES_WW_CTWW__MGCG_OVEWWIDE_0_MASK;
		WWEG32(mmWWC_SEWDES_WW_CTWW, data);
		mutex_unwock(&adev->gwbm_idx_mutex);

		gfx_v7_0_update_wwc(adev, tmp);

		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGTS) {
			owig = data = WWEG32(mmCGTS_SM_CTWW_WEG);
			data &= ~CGTS_SM_CTWW_WEG__SM_MODE_MASK;
			data |= (0x2 << CGTS_SM_CTWW_WEG__SM_MODE__SHIFT);
			data |= CGTS_SM_CTWW_WEG__SM_MODE_ENABWE_MASK;
			data &= ~CGTS_SM_CTWW_WEG__OVEWWIDE_MASK;
			if ((adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) &&
			    (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGTS_WS))
				data &= ~CGTS_SM_CTWW_WEG__WS_OVEWWIDE_MASK;
			data &= ~CGTS_SM_CTWW_WEG__ON_MONITOW_ADD_MASK;
			data |= CGTS_SM_CTWW_WEG__ON_MONITOW_ADD_EN_MASK;
			data |= (0x96 << CGTS_SM_CTWW_WEG__ON_MONITOW_ADD__SHIFT);
			if (owig != data)
				WWEG32(mmCGTS_SM_CTWW_WEG, data);
		}
	} ewse {
		owig = data = WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		data |= 0x00000003;
		if (owig != data)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data);

		data = WWEG32(mmWWC_MEM_SWP_CNTW);
		if (data & WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK) {
			data &= ~WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK;
			WWEG32(mmWWC_MEM_SWP_CNTW, data);
		}

		data = WWEG32(mmCP_MEM_SWP_CNTW);
		if (data & CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK) {
			data &= ~CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK;
			WWEG32(mmCP_MEM_SWP_CNTW, data);
		}

		owig = data = WWEG32(mmCGTS_SM_CTWW_WEG);
		data |= CGTS_SM_CTWW_WEG__OVEWWIDE_MASK | CGTS_SM_CTWW_WEG__WS_OVEWWIDE_MASK;
		if (owig != data)
			WWEG32(mmCGTS_SM_CTWW_WEG, data);

		tmp = gfx_v7_0_hawt_wwc(adev);

		mutex_wock(&adev->gwbm_idx_mutex);
		gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
		WWEG32(mmWWC_SEWDES_WW_CU_MASTEW_MASK, 0xffffffff);
		WWEG32(mmWWC_SEWDES_WW_NONCU_MASTEW_MASK, 0xffffffff);
		data = WWC_SEWDES_WW_CTWW__BPM_ADDW_MASK | WWC_SEWDES_WW_CTWW__MGCG_OVEWWIDE_1_MASK;
		WWEG32(mmWWC_SEWDES_WW_CTWW, data);
		mutex_unwock(&adev->gwbm_idx_mutex);

		gfx_v7_0_update_wwc(adev, tmp);
	}
}

static void gfx_v7_0_update_cg(stwuct amdgpu_device *adev,
			       boow enabwe)
{
	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, fawse);
	/* owdew mattews! */
	if (enabwe) {
		gfx_v7_0_enabwe_mgcg(adev, twue);
		gfx_v7_0_enabwe_cgcg(adev, twue);
	} ewse {
		gfx_v7_0_enabwe_cgcg(adev, fawse);
		gfx_v7_0_enabwe_mgcg(adev, fawse);
	}
	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);
}

static void gfx_v7_0_enabwe_scwk_swowdown_on_pu(stwuct amdgpu_device *adev,
						boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_WWC_SMU_HS))
		data |= WWC_PG_CNTW__SMU_CWK_SWOWDOWN_ON_PU_ENABWE_MASK;
	ewse
		data &= ~WWC_PG_CNTW__SMU_CWK_SWOWDOWN_ON_PU_ENABWE_MASK;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

static void gfx_v7_0_enabwe_scwk_swowdown_on_pd(stwuct amdgpu_device *adev,
						boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_WWC_SMU_HS))
		data |= WWC_PG_CNTW__SMU_CWK_SWOWDOWN_ON_PD_ENABWE_MASK;
	ewse
		data &= ~WWC_PG_CNTW__SMU_CWK_SWOWDOWN_ON_PD_ENABWE_MASK;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

static void gfx_v7_0_enabwe_cp_pg(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_CP))
		data &= ~0x8000;
	ewse
		data |= 0x8000;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

static void gfx_v7_0_enabwe_gds_pg(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_GDS))
		data &= ~0x2000;
	ewse
		data |= 0x2000;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

static int gfx_v7_0_cp_pg_tabwe_num(stwuct amdgpu_device *adev)
{
	if (adev->asic_type == CHIP_KAVEWI)
		wetuwn 5;
	ewse
		wetuwn 4;
}

static void gfx_v7_0_enabwe_gfx_cgpg(stwuct amdgpu_device *adev,
				     boow enabwe)
{
	u32 data, owig;

	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG)) {
		owig = data = WWEG32(mmWWC_PG_CNTW);
		data |= WWC_PG_CNTW__GFX_POWEW_GATING_ENABWE_MASK;
		if (owig != data)
			WWEG32(mmWWC_PG_CNTW, data);

		owig = data = WWEG32(mmWWC_AUTO_PG_CTWW);
		data |= WWC_AUTO_PG_CTWW__AUTO_PG_EN_MASK;
		if (owig != data)
			WWEG32(mmWWC_AUTO_PG_CTWW, data);
	} ewse {
		owig = data = WWEG32(mmWWC_PG_CNTW);
		data &= ~WWC_PG_CNTW__GFX_POWEW_GATING_ENABWE_MASK;
		if (owig != data)
			WWEG32(mmWWC_PG_CNTW, data);

		owig = data = WWEG32(mmWWC_AUTO_PG_CTWW);
		data &= ~WWC_AUTO_PG_CTWW__AUTO_PG_EN_MASK;
		if (owig != data)
			WWEG32(mmWWC_AUTO_PG_CTWW, data);

		data = WWEG32(mmDB_WENDEW_CONTWOW);
	}
}

static void gfx_v7_0_set_usew_cu_inactive_bitmap(stwuct amdgpu_device *adev,
						 u32 bitmap)
{
	u32 data;

	if (!bitmap)
		wetuwn;

	data = bitmap << GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS_MASK;

	WWEG32(mmGC_USEW_SHADEW_AWWAY_CONFIG, data);
}

static u32 gfx_v7_0_get_cu_active_bitmap(stwuct amdgpu_device *adev)
{
	u32 data, mask;

	data = WWEG32(mmCC_GC_SHADEW_AWWAY_CONFIG);
	data |= WWEG32(mmGC_USEW_SHADEW_AWWAY_CONFIG);

	data &= CC_GC_SHADEW_AWWAY_CONFIG__INACTIVE_CUS_MASK;
	data >>= CC_GC_SHADEW_AWWAY_CONFIG__INACTIVE_CUS__SHIFT;

	mask = amdgpu_gfx_cweate_bitmask(adev->gfx.config.max_cu_pew_sh);

	wetuwn (~data) & mask;
}

static void gfx_v7_0_init_ao_cu_mask(stwuct amdgpu_device *adev)
{
	u32 tmp;

	WWEG32(mmWWC_PG_AWWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);

	tmp = WWEG32(mmWWC_MAX_PG_CU);
	tmp &= ~WWC_MAX_PG_CU__MAX_POWEWED_UP_CU_MASK;
	tmp |= (adev->gfx.cu_info.numbew << WWC_MAX_PG_CU__MAX_POWEWED_UP_CU__SHIFT);
	WWEG32(mmWWC_MAX_PG_CU, tmp);
}

static void gfx_v7_0_enabwe_gfx_static_mgpg(stwuct amdgpu_device *adev,
					    boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_SMG))
		data |= WWC_PG_CNTW__STATIC_PEW_CU_PG_ENABWE_MASK;
	ewse
		data &= ~WWC_PG_CNTW__STATIC_PEW_CU_PG_ENABWE_MASK;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

static void gfx_v7_0_enabwe_gfx_dynamic_mgpg(stwuct amdgpu_device *adev,
					     boow enabwe)
{
	u32 data, owig;

	owig = data = WWEG32(mmWWC_PG_CNTW);
	if (enabwe && (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_DMG))
		data |= WWC_PG_CNTW__DYN_PEW_CU_PG_ENABWE_MASK;
	ewse
		data &= ~WWC_PG_CNTW__DYN_PEW_CU_PG_ENABWE_MASK;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);
}

#define WWC_SAVE_AND_WESTOWE_STAWTING_OFFSET 0x90
#define WWC_CWEAW_STATE_DESCWIPTOW_OFFSET    0x3D

static void gfx_v7_0_init_gfx_cgpg(stwuct amdgpu_device *adev)
{
	u32 data, owig;
	u32 i;

	if (adev->gfx.wwc.cs_data) {
		WWEG32(mmWWC_GPM_SCWATCH_ADDW, WWC_CWEAW_STATE_DESCWIPTOW_OFFSET);
		WWEG32(mmWWC_GPM_SCWATCH_DATA, uppew_32_bits(adev->gfx.wwc.cweaw_state_gpu_addw));
		WWEG32(mmWWC_GPM_SCWATCH_DATA, wowew_32_bits(adev->gfx.wwc.cweaw_state_gpu_addw));
		WWEG32(mmWWC_GPM_SCWATCH_DATA, adev->gfx.wwc.cweaw_state_size);
	} ewse {
		WWEG32(mmWWC_GPM_SCWATCH_ADDW, WWC_CWEAW_STATE_DESCWIPTOW_OFFSET);
		fow (i = 0; i < 3; i++)
			WWEG32(mmWWC_GPM_SCWATCH_DATA, 0);
	}
	if (adev->gfx.wwc.weg_wist) {
		WWEG32(mmWWC_GPM_SCWATCH_ADDW, WWC_SAVE_AND_WESTOWE_STAWTING_OFFSET);
		fow (i = 0; i < adev->gfx.wwc.weg_wist_size; i++)
			WWEG32(mmWWC_GPM_SCWATCH_DATA, adev->gfx.wwc.weg_wist[i]);
	}

	owig = data = WWEG32(mmWWC_PG_CNTW);
	data |= WWC_PG_CNTW__GFX_POWEW_GATING_SWC_MASK;
	if (owig != data)
		WWEG32(mmWWC_PG_CNTW, data);

	WWEG32(mmWWC_SAVE_AND_WESTOWE_BASE, adev->gfx.wwc.save_westowe_gpu_addw >> 8);
	WWEG32(mmWWC_JUMP_TABWE_WESTOWE, adev->gfx.wwc.cp_tabwe_gpu_addw >> 8);

	data = WWEG32(mmCP_WB_WPTW_POWW_CNTW);
	data &= ~CP_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK;
	data |= (0x60 << CP_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT);
	WWEG32(mmCP_WB_WPTW_POWW_CNTW, data);

	data = 0x10101010;
	WWEG32(mmWWC_PG_DEWAY, data);

	data = WWEG32(mmWWC_PG_DEWAY_2);
	data &= ~0xff;
	data |= 0x3;
	WWEG32(mmWWC_PG_DEWAY_2, data);

	data = WWEG32(mmWWC_AUTO_PG_CTWW);
	data &= ~WWC_AUTO_PG_CTWW__GWBM_WEG_SAVE_GFX_IDWE_THWESHOWD_MASK;
	data |= (0x700 << WWC_AUTO_PG_CTWW__GWBM_WEG_SAVE_GFX_IDWE_THWESHOWD__SHIFT);
	WWEG32(mmWWC_AUTO_PG_CTWW, data);

}

static void gfx_v7_0_update_gfx_pg(stwuct amdgpu_device *adev, boow enabwe)
{
	gfx_v7_0_enabwe_gfx_cgpg(adev, enabwe);
	gfx_v7_0_enabwe_gfx_static_mgpg(adev, enabwe);
	gfx_v7_0_enabwe_gfx_dynamic_mgpg(adev, enabwe);
}

static u32 gfx_v7_0_get_csb_size(stwuct amdgpu_device *adev)
{
	u32 count = 0;
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;

	if (adev->gfx.wwc.cs_data == NUWW)
		wetuwn 0;

	/* begin cweaw state */
	count += 2;
	/* context contwow state */
	count += 3;

	fow (sect = adev->gfx.wwc.cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT)
				count += 2 + ext->weg_count;
			ewse
				wetuwn 0;
		}
	}
	/* pa_sc_wastew_config/pa_sc_wastew_config1 */
	count += 4;
	/* end cweaw state */
	count += 2;
	/* cweaw state */
	count += 2;

	wetuwn count;
}

static void gfx_v7_0_get_csb_buffew(stwuct amdgpu_device *adev,
				    vowatiwe u32 *buffew)
{
	u32 count = 0, i;
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;

	if (adev->gfx.wwc.cs_data == NUWW)
		wetuwn;
	if (buffew == NUWW)
		wetuwn;

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	buffew[count++] = cpu_to_we32(PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	buffew[count++] = cpu_to_we32(0x80000000);
	buffew[count++] = cpu_to_we32(0x80000000);

	fow (sect = adev->gfx.wwc.cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				buffew[count++] =
					cpu_to_we32(PACKET3(PACKET3_SET_CONTEXT_WEG, ext->weg_count));
				buffew[count++] = cpu_to_we32(ext->weg_index - PACKET3_SET_CONTEXT_WEG_STAWT);
				fow (i = 0; i < ext->weg_count; i++)
					buffew[count++] = cpu_to_we32(ext->extent[i]);
			} ewse {
				wetuwn;
			}
		}
	}

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_SET_CONTEXT_WEG, 2));
	buffew[count++] = cpu_to_we32(mmPA_SC_WASTEW_CONFIG - PACKET3_SET_CONTEXT_WEG_STAWT);
	switch (adev->asic_type) {
	case CHIP_BONAIWE:
		buffew[count++] = cpu_to_we32(0x16000012);
		buffew[count++] = cpu_to_we32(0x00000000);
		bweak;
	case CHIP_KAVEWI:
		buffew[count++] = cpu_to_we32(0x00000000); /* XXX */
		buffew[count++] = cpu_to_we32(0x00000000);
		bweak;
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		buffew[count++] = cpu_to_we32(0x00000000); /* XXX */
		buffew[count++] = cpu_to_we32(0x00000000);
		bweak;
	case CHIP_HAWAII:
		buffew[count++] = cpu_to_we32(0x3a00161a);
		buffew[count++] = cpu_to_we32(0x0000002e);
		bweak;
	defauwt:
		buffew[count++] = cpu_to_we32(0x00000000);
		buffew[count++] = cpu_to_we32(0x00000000);
		bweak;
	}

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	buffew[count++] = cpu_to_we32(PACKET3_PWEAMBWE_END_CWEAW_STATE);

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_CWEAW_STATE, 0));
	buffew[count++] = cpu_to_we32(0);
}

static void gfx_v7_0_init_pg(stwuct amdgpu_device *adev)
{
	if (adev->pg_fwags & (AMD_PG_SUPPOWT_GFX_PG |
			      AMD_PG_SUPPOWT_GFX_SMG |
			      AMD_PG_SUPPOWT_GFX_DMG |
			      AMD_PG_SUPPOWT_CP |
			      AMD_PG_SUPPOWT_GDS |
			      AMD_PG_SUPPOWT_WWC_SMU_HS)) {
		gfx_v7_0_enabwe_scwk_swowdown_on_pu(adev, twue);
		gfx_v7_0_enabwe_scwk_swowdown_on_pd(adev, twue);
		if (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG) {
			gfx_v7_0_init_gfx_cgpg(adev);
			gfx_v7_0_enabwe_cp_pg(adev, twue);
			gfx_v7_0_enabwe_gds_pg(adev, twue);
		}
		gfx_v7_0_init_ao_cu_mask(adev);
		gfx_v7_0_update_gfx_pg(adev, twue);
	}
}

static void gfx_v7_0_fini_pg(stwuct amdgpu_device *adev)
{
	if (adev->pg_fwags & (AMD_PG_SUPPOWT_GFX_PG |
			      AMD_PG_SUPPOWT_GFX_SMG |
			      AMD_PG_SUPPOWT_GFX_DMG |
			      AMD_PG_SUPPOWT_CP |
			      AMD_PG_SUPPOWT_GDS |
			      AMD_PG_SUPPOWT_WWC_SMU_HS)) {
		gfx_v7_0_update_gfx_pg(adev, fawse);
		if (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG) {
			gfx_v7_0_enabwe_cp_pg(adev, fawse);
			gfx_v7_0_enabwe_gds_pg(adev, fawse);
		}
	}
}

/**
 * gfx_v7_0_get_gpu_cwock_countew - wetuwn GPU cwock countew snapshot
 *
 * @adev: amdgpu_device pointew
 *
 * Fetches a GPU cwock countew snapshot (SI).
 * Wetuwns the 64 bit cwock countew snapshot.
 */
static uint64_t gfx_v7_0_get_gpu_cwock_countew(stwuct amdgpu_device *adev)
{
	uint64_t cwock;

	mutex_wock(&adev->gfx.gpu_cwock_mutex);
	WWEG32(mmWWC_CAPTUWE_GPU_CWOCK_COUNT, 1);
	cwock = (uint64_t)WWEG32(mmWWC_GPU_CWOCK_COUNT_WSB) |
		((uint64_t)WWEG32(mmWWC_GPU_CWOCK_COUNT_MSB) << 32UWW);
	mutex_unwock(&adev->gfx.gpu_cwock_mutex);
	wetuwn cwock;
}

static void gfx_v7_0_wing_emit_gds_switch(stwuct amdgpu_wing *wing,
					  uint32_t vmid,
					  uint32_t gds_base, uint32_t gds_size,
					  uint32_t gws_base, uint32_t gws_size,
					  uint32_t oa_base, uint32_t oa_size)
{
	/* GDS Base */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].mem_base);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gds_base);

	/* GDS Size */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].mem_size);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gds_size);

	/* GWS */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].gws);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gws_size << GDS_GWS_VMID0__SIZE__SHIFT | gws_base);

	/* OA */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].oa);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, (1 << (oa_size + oa_base)) - (1 << oa_base));
}

static void gfx_v7_0_wing_soft_wecovewy(stwuct amdgpu_wing *wing, unsigned vmid)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t vawue = 0;

	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, CMD, 0x03);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, MODE, 0x01);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, CHECK_VMID, 1);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, VM_ID, vmid);
	WWEG32(mmSQ_CMD, vawue);
}

static uint32_t wave_wead_ind(stwuct amdgpu_device *adev, uint32_t simd, uint32_t wave, uint32_t addwess)
{
	WWEG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(addwess << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK));
	wetuwn WWEG32(mmSQ_IND_DATA);
}

static void wave_wead_wegs(stwuct amdgpu_device *adev, uint32_t simd,
			   uint32_t wave, uint32_t thwead,
			   uint32_t wegno, uint32_t num, uint32_t *out)
{
	WWEG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(wegno << SQ_IND_INDEX__INDEX__SHIFT) |
		(thwead << SQ_IND_INDEX__THWEAD_ID__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK) |
		(SQ_IND_INDEX__AUTO_INCW_MASK));
	whiwe (num--)
		*(out++) = WWEG32(mmSQ_IND_DATA);
}

static void gfx_v7_0_wead_wave_data(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd, uint32_t wave, uint32_t *dst, int *no_fiewds)
{
	/* type 0 wave data */
	dst[(*no_fiewds)++] = 0;
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_STATUS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_HW_ID);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW1);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_GPW_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_WDS_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TWAPSTS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_IB_STS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TBA_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TBA_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TMA_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TMA_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_IB_DBG0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_M0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_MODE);
}

static void gfx_v7_0_wead_wave_sgpws(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				     uint32_t wave, uint32_t stawt,
				     uint32_t size, uint32_t *dst)
{
	wave_wead_wegs(
		adev, simd, wave, 0,
		stawt + SQIND_WAVE_SGPWS_OFFSET, size, dst);
}

static void gfx_v7_0_sewect_me_pipe_q(stwuct amdgpu_device *adev,
				  u32 me, u32 pipe, u32 q, u32 vm, u32 xcc_id)
{
	cik_swbm_sewect(adev, me, pipe, q, vm);
}

static const stwuct amdgpu_gfx_funcs gfx_v7_0_gfx_funcs = {
	.get_gpu_cwock_countew = &gfx_v7_0_get_gpu_cwock_countew,
	.sewect_se_sh = &gfx_v7_0_sewect_se_sh,
	.wead_wave_data = &gfx_v7_0_wead_wave_data,
	.wead_wave_sgpws = &gfx_v7_0_wead_wave_sgpws,
	.sewect_me_pipe_q = &gfx_v7_0_sewect_me_pipe_q
};

static const stwuct amdgpu_wwc_funcs gfx_v7_0_wwc_funcs = {
	.is_wwc_enabwed = gfx_v7_0_is_wwc_enabwed,
	.set_safe_mode = gfx_v7_0_set_safe_mode,
	.unset_safe_mode = gfx_v7_0_unset_safe_mode,
	.init = gfx_v7_0_wwc_init,
	.get_csb_size = gfx_v7_0_get_csb_size,
	.get_csb_buffew = gfx_v7_0_get_csb_buffew,
	.get_cp_tabwe_num = gfx_v7_0_cp_pg_tabwe_num,
	.wesume = gfx_v7_0_wwc_wesume,
	.stop = gfx_v7_0_wwc_stop,
	.weset = gfx_v7_0_wwc_weset,
	.stawt = gfx_v7_0_wwc_stawt,
	.update_spm_vmid = gfx_v7_0_update_spm_vmid
};

static int gfx_v7_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->gfx.xcc_mask = 1;
	adev->gfx.num_gfx_wings = GFX7_NUM_GFX_WINGS;
	adev->gfx.num_compute_wings = min(amdgpu_gfx_get_num_kcq(adev),
					  AMDGPU_MAX_COMPUTE_WINGS);
	adev->gfx.funcs = &gfx_v7_0_gfx_funcs;
	adev->gfx.wwc.funcs = &gfx_v7_0_wwc_funcs;
	gfx_v7_0_set_wing_funcs(adev);
	gfx_v7_0_set_iwq_funcs(adev);
	gfx_v7_0_set_gds_init(adev);

	wetuwn 0;
}

static int gfx_v7_0_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_weg_iwq, 0);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_inst_iwq, 0);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static void gfx_v7_0_gpu_eawwy_init(stwuct amdgpu_device *adev)
{
	u32 gb_addw_config;
	u32 mc_awb_wamcfg;
	u32 dimm00_addw_map, dimm01_addw_map, dimm10_addw_map, dimm11_addw_map;
	u32 tmp;

	switch (adev->asic_type) {
	case CHIP_BONAIWE:
		adev->gfx.config.max_shadew_engines = 2;
		adev->gfx.config.max_tiwe_pipes = 4;
		adev->gfx.config.max_cu_pew_sh = 7;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_textuwe_channew_caches = 4;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = BONAIWE_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_HAWAII:
		adev->gfx.config.max_shadew_engines = 4;
		adev->gfx.config.max_tiwe_pipes = 16;
		adev->gfx.config.max_cu_pew_sh = 11;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 4;
		adev->gfx.config.max_textuwe_channew_caches = 16;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = HAWAII_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_KAVEWI:
		adev->gfx.config.max_shadew_engines = 1;
		adev->gfx.config.max_tiwe_pipes = 4;
		adev->gfx.config.max_cu_pew_sh = 8;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_textuwe_channew_caches = 4;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = BONAIWE_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_KABINI:
	case CHIP_MUWWINS:
	defauwt:
		adev->gfx.config.max_shadew_engines = 1;
		adev->gfx.config.max_tiwe_pipes = 2;
		adev->gfx.config.max_cu_pew_sh = 2;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 1;
		adev->gfx.config.max_textuwe_channew_caches = 2;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = BONAIWE_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	}

	adev->gfx.config.mc_awb_wamcfg = WWEG32(mmMC_AWB_WAMCFG);
	mc_awb_wamcfg = adev->gfx.config.mc_awb_wamcfg;

	adev->gfx.config.num_banks = WEG_GET_FIEWD(mc_awb_wamcfg,
				MC_AWB_WAMCFG, NOOFBANK);
	adev->gfx.config.num_wanks = WEG_GET_FIEWD(mc_awb_wamcfg,
				MC_AWB_WAMCFG, NOOFWANKS);

	adev->gfx.config.num_tiwe_pipes = adev->gfx.config.max_tiwe_pipes;
	adev->gfx.config.mem_max_buwst_wength_bytes = 256;
	if (adev->fwags & AMD_IS_APU) {
		/* Get memowy bank mapping mode. */
		tmp = WWEG32(mmMC_FUS_DWAM0_BANK_ADDW_MAPPING);
		dimm00_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM0_BANK_ADDW_MAPPING, DIMM0ADDWMAP);
		dimm01_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM0_BANK_ADDW_MAPPING, DIMM1ADDWMAP);

		tmp = WWEG32(mmMC_FUS_DWAM1_BANK_ADDW_MAPPING);
		dimm10_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM1_BANK_ADDW_MAPPING, DIMM0ADDWMAP);
		dimm11_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM1_BANK_ADDW_MAPPING, DIMM1ADDWMAP);

		/* Vawidate settings in case onwy one DIMM instawwed. */
		if ((dimm00_addw_map == 0) || (dimm00_addw_map == 3) || (dimm00_addw_map == 4) || (dimm00_addw_map > 12))
			dimm00_addw_map = 0;
		if ((dimm01_addw_map == 0) || (dimm01_addw_map == 3) || (dimm01_addw_map == 4) || (dimm01_addw_map > 12))
			dimm01_addw_map = 0;
		if ((dimm10_addw_map == 0) || (dimm10_addw_map == 3) || (dimm10_addw_map == 4) || (dimm10_addw_map > 12))
			dimm10_addw_map = 0;
		if ((dimm11_addw_map == 0) || (dimm11_addw_map == 3) || (dimm11_addw_map == 4) || (dimm11_addw_map > 12))
			dimm11_addw_map = 0;

		/* If DIMM Addw map is 8GB, WOW size shouwd be 2KB. Othewwise 1KB. */
		/* If WOW size(DIMM1) != WOW size(DMIMM0), WOW size shouwd be wawgew one. */
		if ((dimm00_addw_map == 11) || (dimm01_addw_map == 11) || (dimm10_addw_map == 11) || (dimm11_addw_map == 11))
			adev->gfx.config.mem_wow_size_in_kb = 2;
		ewse
			adev->gfx.config.mem_wow_size_in_kb = 1;
	} ewse {
		tmp = (mc_awb_wamcfg & MC_AWB_WAMCFG__NOOFCOWS_MASK) >> MC_AWB_WAMCFG__NOOFCOWS__SHIFT;
		adev->gfx.config.mem_wow_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
		if (adev->gfx.config.mem_wow_size_in_kb > 4)
			adev->gfx.config.mem_wow_size_in_kb = 4;
	}
	/* XXX use MC settings? */
	adev->gfx.config.shadew_engine_tiwe_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.muwti_gpu_tiwe_size = 64;

	/* fix up wow size */
	gb_addw_config &= ~GB_ADDW_CONFIG__WOW_SIZE_MASK;
	switch (adev->gfx.config.mem_wow_size_in_kb) {
	case 1:
	defauwt:
		gb_addw_config |= (0 << GB_ADDW_CONFIG__WOW_SIZE__SHIFT);
		bweak;
	case 2:
		gb_addw_config |= (1 << GB_ADDW_CONFIG__WOW_SIZE__SHIFT);
		bweak;
	case 4:
		gb_addw_config |= (2 << GB_ADDW_CONFIG__WOW_SIZE__SHIFT);
		bweak;
	}
	adev->gfx.config.gb_addw_config = gb_addw_config;
}

static int gfx_v7_0_compute_wing_init(stwuct amdgpu_device *adev, int wing_id,
					int mec, int pipe, int queue)
{
	int w;
	unsigned iwq_type;
	stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[wing_id];

	/* mec0 is me1 */
	wing->me = mec + 1;
	wing->pipe = pipe;
	wing->queue = queue;

	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	wing->doowbeww_index = adev->doowbeww_index.mec_wing0 + wing_id;
	spwintf(wing->name, "comp_%d.%d.%d", wing->me, wing->pipe, wing->queue);

	iwq_type = AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP
		+ ((wing->me - 1) * adev->gfx.mec.num_pipe_pew_mec)
		+ wing->pipe;

	/* type-2 packets awe depwecated on MEC, use type-3 instead */
	w = amdgpu_wing_init(adev, wing, 1024,
			     &adev->gfx.eop_iwq, iwq_type,
			     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		wetuwn w;


	wetuwn 0;
}

static int gfx_v7_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, j, k, w, wing_id;

	switch (adev->asic_type) {
	case CHIP_KAVEWI:
		adev->gfx.mec.num_mec = 2;
		bweak;
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
	defauwt:
		adev->gfx.mec.num_mec = 1;
		bweak;
	}
	adev->gfx.mec.num_pipe_pew_mec = 4;
	adev->gfx.mec.num_queue_pew_pipe = 8;

	/* EOP Event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 181, &adev->gfx.eop_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged weg */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 184,
			      &adev->gfx.pwiv_weg_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 185,
			      &adev->gfx.pwiv_inst_iwq);
	if (w)
		wetuwn w;

	w = gfx_v7_0_init_micwocode(adev);
	if (w) {
		DWM_EWWOW("Faiwed to woad gfx fiwmwawe!\n");
		wetuwn w;
	}

	w = adev->gfx.wwc.funcs->init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init wwc BOs!\n");
		wetuwn w;
	}

	/* awwocate mec buffews */
	w = gfx_v7_0_mec_init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init MEC BOs!\n");
		wetuwn w;
	}

	fow (i = 0; i < adev->gfx.num_gfx_wings; i++) {
		wing = &adev->gfx.gfx_wing[i];
		wing->wing_obj = NUWW;
		spwintf(wing->name, "gfx");
		w = amdgpu_wing_init(adev, wing, 1024,
				     &adev->gfx.eop_iwq,
				     AMDGPU_CP_IWQ_GFX_ME0_PIPE0_EOP,
				     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;
	}

	/* set up the compute queues - awwocate howizontawwy acwoss pipes */
	wing_id = 0;
	fow (i = 0; i < adev->gfx.mec.num_mec; ++i) {
		fow (j = 0; j < adev->gfx.mec.num_queue_pew_pipe; j++) {
			fow (k = 0; k < adev->gfx.mec.num_pipe_pew_mec; k++) {
				if (!amdgpu_gfx_is_mec_queue_enabwed(adev, 0, i,
								     k, j))
					continue;

				w = gfx_v7_0_compute_wing_init(adev,
								wing_id,
								i, k, j);
				if (w)
					wetuwn w;

				wing_id++;
			}
		}
	}

	adev->gfx.ce_wam_size = 0x8000;

	gfx_v7_0_gpu_eawwy_init(adev);

	wetuwn w;
}

static int gfx_v7_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->gfx.num_gfx_wings; i++)
		amdgpu_wing_fini(&adev->gfx.gfx_wing[i]);
	fow (i = 0; i < adev->gfx.num_compute_wings; i++)
		amdgpu_wing_fini(&adev->gfx.compute_wing[i]);

	gfx_v7_0_cp_compute_fini(adev);
	amdgpu_gfx_wwc_fini(adev);
	gfx_v7_0_mec_fini(adev);
	amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cweaw_state_obj,
				&adev->gfx.wwc.cweaw_state_gpu_addw,
				(void **)&adev->gfx.wwc.cs_ptw);
	if (adev->gfx.wwc.cp_tabwe_size) {
		amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cp_tabwe_obj,
				&adev->gfx.wwc.cp_tabwe_gpu_addw,
				(void **)&adev->gfx.wwc.cp_tabwe_ptw);
	}
	gfx_v7_0_fwee_micwocode(adev);

	wetuwn 0;
}

static int gfx_v7_0_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	gfx_v7_0_constants_init(adev);

	/* init CSB */
	adev->gfx.wwc.funcs->get_csb_buffew(adev, adev->gfx.wwc.cs_ptw);
	/* init wwc */
	w = adev->gfx.wwc.funcs->wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v7_0_cp_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int gfx_v7_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_put(adev, &adev->gfx.pwiv_weg_iwq, 0);
	amdgpu_iwq_put(adev, &adev->gfx.pwiv_inst_iwq, 0);
	gfx_v7_0_cp_enabwe(adev, fawse);
	adev->gfx.wwc.funcs->stop(adev);
	gfx_v7_0_fini_pg(adev);

	wetuwn 0;
}

static int gfx_v7_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn gfx_v7_0_hw_fini(adev);
}

static int gfx_v7_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn gfx_v7_0_hw_init(adev);
}

static boow gfx_v7_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (WWEG32(mmGWBM_STATUS) & GWBM_STATUS__GUI_ACTIVE_MASK)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static int gfx_v7_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(mmGWBM_STATUS) & GWBM_STATUS__GUI_ACTIVE_MASK;

		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int gfx_v7_0_soft_weset(void *handwe)
{
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* GWBM_STATUS */
	tmp = WWEG32(mmGWBM_STATUS);
	if (tmp & (GWBM_STATUS__PA_BUSY_MASK | GWBM_STATUS__SC_BUSY_MASK |
		   GWBM_STATUS__BCI_BUSY_MASK | GWBM_STATUS__SX_BUSY_MASK |
		   GWBM_STATUS__TA_BUSY_MASK | GWBM_STATUS__VGT_BUSY_MASK |
		   GWBM_STATUS__DB_BUSY_MASK | GWBM_STATUS__CB_BUSY_MASK |
		   GWBM_STATUS__GDS_BUSY_MASK | GWBM_STATUS__SPI_BUSY_MASK |
		   GWBM_STATUS__IA_BUSY_MASK | GWBM_STATUS__IA_BUSY_NO_DMA_MASK))
		gwbm_soft_weset |= GWBM_SOFT_WESET__SOFT_WESET_CP_MASK |
			GWBM_SOFT_WESET__SOFT_WESET_GFX_MASK;

	if (tmp & (GWBM_STATUS__CP_BUSY_MASK | GWBM_STATUS__CP_COHEWENCY_BUSY_MASK)) {
		gwbm_soft_weset |= GWBM_SOFT_WESET__SOFT_WESET_CP_MASK;
		swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_GWBM_MASK;
	}

	/* GWBM_STATUS2 */
	tmp = WWEG32(mmGWBM_STATUS2);
	if (tmp & GWBM_STATUS2__WWC_BUSY_MASK)
		gwbm_soft_weset |= GWBM_SOFT_WESET__SOFT_WESET_WWC_MASK;

	/* SWBM_STATUS */
	tmp = WWEG32(mmSWBM_STATUS);
	if (tmp & SWBM_STATUS__GWBM_WQ_PENDING_MASK)
		swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_GWBM_MASK;

	if (gwbm_soft_weset || swbm_soft_weset) {
		/* disabwe CG/PG */
		gfx_v7_0_fini_pg(adev);
		gfx_v7_0_update_cg(adev, fawse);

		/* stop the wwc */
		adev->gfx.wwc.funcs->stop(adev);

		/* Disabwe GFX pawsing/pwefetching */
		WWEG32(mmCP_ME_CNTW, CP_ME_CNTW__ME_HAWT_MASK | CP_ME_CNTW__PFP_HAWT_MASK | CP_ME_CNTW__CE_HAWT_MASK);

		/* Disabwe MEC pawsing/pwefetching */
		WWEG32(mmCP_MEC_CNTW, CP_MEC_CNTW__MEC_ME1_HAWT_MASK | CP_MEC_CNTW__MEC_ME2_HAWT_MASK);

		if (gwbm_soft_weset) {
			tmp = WWEG32(mmGWBM_SOFT_WESET);
			tmp |= gwbm_soft_weset;
			dev_info(adev->dev, "GWBM_SOFT_WESET=0x%08X\n", tmp);
			WWEG32(mmGWBM_SOFT_WESET, tmp);
			tmp = WWEG32(mmGWBM_SOFT_WESET);

			udeway(50);

			tmp &= ~gwbm_soft_weset;
			WWEG32(mmGWBM_SOFT_WESET, tmp);
			tmp = WWEG32(mmGWBM_SOFT_WESET);
		}

		if (swbm_soft_weset) {
			tmp = WWEG32(mmSWBM_SOFT_WESET);
			tmp |= swbm_soft_weset;
			dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
			WWEG32(mmSWBM_SOFT_WESET, tmp);
			tmp = WWEG32(mmSWBM_SOFT_WESET);

			udeway(50);

			tmp &= ~swbm_soft_weset;
			WWEG32(mmSWBM_SOFT_WESET, tmp);
			tmp = WWEG32(mmSWBM_SOFT_WESET);
		}
		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}
	wetuwn 0;
}

static void gfx_v7_0_set_gfx_eop_intewwupt_state(stwuct amdgpu_device *adev,
						 enum amdgpu_intewwupt_state state)
{
	u32 cp_int_cntw;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw &= ~CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw |= CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	defauwt:
		bweak;
	}
}

static void gfx_v7_0_set_compute_eop_intewwupt_state(stwuct amdgpu_device *adev,
						     int me, int pipe,
						     enum amdgpu_intewwupt_state state)
{
	u32 mec_int_cntw, mec_int_cntw_weg;

	/*
	 * amdgpu contwows onwy the fiwst MEC. That's why this function onwy
	 * handwes the setting of intewwupts fow this specific MEC. Aww othew
	 * pipes' intewwupts awe set by amdkfd.
	 */

	if (me == 1) {
		switch (pipe) {
		case 0:
			mec_int_cntw_weg = mmCP_ME1_PIPE0_INT_CNTW;
			bweak;
		case 1:
			mec_int_cntw_weg = mmCP_ME1_PIPE1_INT_CNTW;
			bweak;
		case 2:
			mec_int_cntw_weg = mmCP_ME1_PIPE2_INT_CNTW;
			bweak;
		case 3:
			mec_int_cntw_weg = mmCP_ME1_PIPE3_INT_CNTW;
			bweak;
		defauwt:
			DWM_DEBUG("invawid pipe %d\n", pipe);
			wetuwn;
		}
	} ewse {
		DWM_DEBUG("invawid me %d\n", me);
		wetuwn;
	}

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		mec_int_cntw = WWEG32(mec_int_cntw_weg);
		mec_int_cntw &= ~CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mec_int_cntw_weg, mec_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		mec_int_cntw = WWEG32(mec_int_cntw_weg);
		mec_int_cntw |= CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mec_int_cntw_weg, mec_int_cntw);
		bweak;
	defauwt:
		bweak;
	}
}

static int gfx_v7_0_set_pwiv_weg_fauwt_state(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *swc,
					     unsigned type,
					     enum amdgpu_intewwupt_state state)
{
	u32 cp_int_cntw;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw &= ~CP_INT_CNTW_WING0__PWIV_WEG_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw |= CP_INT_CNTW_WING0__PWIV_WEG_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int gfx_v7_0_set_pwiv_inst_fauwt_state(stwuct amdgpu_device *adev,
					      stwuct amdgpu_iwq_swc *swc,
					      unsigned type,
					      enum amdgpu_intewwupt_state state)
{
	u32 cp_int_cntw;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw &= ~CP_INT_CNTW_WING0__PWIV_INSTW_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		cp_int_cntw = WWEG32(mmCP_INT_CNTW_WING0);
		cp_int_cntw |= CP_INT_CNTW_WING0__PWIV_INSTW_INT_ENABWE_MASK;
		WWEG32(mmCP_INT_CNTW_WING0, cp_int_cntw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int gfx_v7_0_set_eop_intewwupt_state(stwuct amdgpu_device *adev,
					    stwuct amdgpu_iwq_swc *swc,
					    unsigned type,
					    enum amdgpu_intewwupt_state state)
{
	switch (type) {
	case AMDGPU_CP_IWQ_GFX_ME0_PIPE0_EOP:
		gfx_v7_0_set_gfx_eop_intewwupt_state(adev, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 1, 0, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE1_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 1, 1, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE2_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 1, 2, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE3_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 1, 3, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE0_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 2, 0, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE1_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 2, 1, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE2_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 2, 2, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE3_EOP:
		gfx_v7_0_set_compute_eop_intewwupt_state(adev, 2, 3, state);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int gfx_v7_0_eop_iwq(stwuct amdgpu_device *adev,
			    stwuct amdgpu_iwq_swc *souwce,
			    stwuct amdgpu_iv_entwy *entwy)
{
	u8 me_id, pipe_id;
	stwuct amdgpu_wing *wing;
	int i;

	DWM_DEBUG("IH: CP EOP\n");
	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	switch (me_id) {
	case 0:
		amdgpu_fence_pwocess(&adev->gfx.gfx_wing[0]);
		bweak;
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing[i];
			if ((wing->me == me_id) && (wing->pipe == pipe_id))
				amdgpu_fence_pwocess(wing);
		}
		bweak;
	}
	wetuwn 0;
}

static void gfx_v7_0_fauwt(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iv_entwy *entwy)
{
	stwuct amdgpu_wing *wing;
	u8 me_id, pipe_id;
	int i;

	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	switch (me_id) {
	case 0:
		dwm_sched_fauwt(&adev->gfx.gfx_wing[0].sched);
		bweak;
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing[i];
			if ((wing->me == me_id) && (wing->pipe == pipe_id))
				dwm_sched_fauwt(&wing->sched);
		}
		bweak;
	}
}

static int gfx_v7_0_pwiv_weg_iwq(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw wegistew access in command stweam\n");
	gfx_v7_0_fauwt(adev, entwy);
	wetuwn 0;
}

static int gfx_v7_0_pwiv_inst_iwq(stwuct amdgpu_device *adev,
				  stwuct amdgpu_iwq_swc *souwce,
				  stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw instwuction in command stweam\n");
	// XXX soft weset the gfx bwock onwy
	gfx_v7_0_fauwt(adev, entwy);
	wetuwn 0;
}

static int gfx_v7_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	boow gate = fawse;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == AMD_CG_STATE_GATE)
		gate = twue;

	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, fawse);
	/* owdew mattews! */
	if (gate) {
		gfx_v7_0_enabwe_mgcg(adev, twue);
		gfx_v7_0_enabwe_cgcg(adev, twue);
	} ewse {
		gfx_v7_0_enabwe_cgcg(adev, fawse);
		gfx_v7_0_enabwe_mgcg(adev, fawse);
	}
	gfx_v7_0_enabwe_gui_idwe_intewwupt(adev, twue);

	wetuwn 0;
}

static int gfx_v7_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	boow gate = fawse;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == AMD_PG_STATE_GATE)
		gate = twue;

	if (adev->pg_fwags & (AMD_PG_SUPPOWT_GFX_PG |
			      AMD_PG_SUPPOWT_GFX_SMG |
			      AMD_PG_SUPPOWT_GFX_DMG |
			      AMD_PG_SUPPOWT_CP |
			      AMD_PG_SUPPOWT_GDS |
			      AMD_PG_SUPPOWT_WWC_SMU_HS)) {
		gfx_v7_0_update_gfx_pg(adev, gate);
		if (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG) {
			gfx_v7_0_enabwe_cp_pg(adev, gate);
			gfx_v7_0_enabwe_gds_pg(adev, gate);
		}
	}

	wetuwn 0;
}

static void gfx_v7_0_emit_mem_sync(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
	amdgpu_wing_wwite(wing, PACKET3_TCW1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);  /* CP_COHEW_CNTW */
	amdgpu_wing_wwite(wing, 0xffffffff);  /* CP_COHEW_SIZE */
	amdgpu_wing_wwite(wing, 0);  /* CP_COHEW_BASE */
	amdgpu_wing_wwite(wing, 0x0000000A); /* poww intewvaw */
}

static void gfx_v7_0_emit_mem_sync_compute(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_ACQUIWE_MEM, 5));
	amdgpu_wing_wwite(wing, PACKET3_TCW1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);  /* CP_COHEW_CNTW */
	amdgpu_wing_wwite(wing, 0xffffffff);	/* CP_COHEW_SIZE */
	amdgpu_wing_wwite(wing, 0xff);		/* CP_COHEW_SIZE_HI */
	amdgpu_wing_wwite(wing, 0);		/* CP_COHEW_BASE */
	amdgpu_wing_wwite(wing, 0);		/* CP_COHEW_BASE_HI */
	amdgpu_wing_wwite(wing, 0x0000000A);	/* poww intewvaw */
}

static const stwuct amd_ip_funcs gfx_v7_0_ip_funcs = {
	.name = "gfx_v7_0",
	.eawwy_init = gfx_v7_0_eawwy_init,
	.wate_init = gfx_v7_0_wate_init,
	.sw_init = gfx_v7_0_sw_init,
	.sw_fini = gfx_v7_0_sw_fini,
	.hw_init = gfx_v7_0_hw_init,
	.hw_fini = gfx_v7_0_hw_fini,
	.suspend = gfx_v7_0_suspend,
	.wesume = gfx_v7_0_wesume,
	.is_idwe = gfx_v7_0_is_idwe,
	.wait_fow_idwe = gfx_v7_0_wait_fow_idwe,
	.soft_weset = gfx_v7_0_soft_weset,
	.set_cwockgating_state = gfx_v7_0_set_cwockgating_state,
	.set_powewgating_state = gfx_v7_0_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs gfx_v7_0_wing_funcs_gfx = {
	.type = AMDGPU_WING_TYPE_GFX,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = gfx_v7_0_wing_get_wptw,
	.get_wptw = gfx_v7_0_wing_get_wptw_gfx,
	.set_wptw = gfx_v7_0_wing_set_wptw_gfx,
	.emit_fwame_size =
		20 + /* gfx_v7_0_wing_emit_gds_switch */
		7 + /* gfx_v7_0_wing_emit_hdp_fwush */
		5 + /* hdp invawidate */
		12 + 12 + 12 + /* gfx_v7_0_wing_emit_fence_gfx x3 fow usew fence, vm fence */
		7 + 4 + /* gfx_v7_0_wing_emit_pipewine_sync */
		CIK_FWUSH_GPU_TWB_NUM_WWEG * 5 + 7 + 6 + /* gfx_v7_0_wing_emit_vm_fwush */
		3 + 4 + /* gfx_v7_wing_emit_cntxcntw incwuding vgt fwush*/
		5, /* SUWFACE_SYNC */
	.emit_ib_size = 4, /* gfx_v7_0_wing_emit_ib_gfx */
	.emit_ib = gfx_v7_0_wing_emit_ib_gfx,
	.emit_fence = gfx_v7_0_wing_emit_fence_gfx,
	.emit_pipewine_sync = gfx_v7_0_wing_emit_pipewine_sync,
	.emit_vm_fwush = gfx_v7_0_wing_emit_vm_fwush,
	.emit_gds_switch = gfx_v7_0_wing_emit_gds_switch,
	.emit_hdp_fwush = gfx_v7_0_wing_emit_hdp_fwush,
	.test_wing = gfx_v7_0_wing_test_wing,
	.test_ib = gfx_v7_0_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_cntxcntw = gfx_v7_wing_emit_cntxcntw,
	.emit_wweg = gfx_v7_0_wing_emit_wweg,
	.soft_wecovewy = gfx_v7_0_wing_soft_wecovewy,
	.emit_mem_sync = gfx_v7_0_emit_mem_sync,
};

static const stwuct amdgpu_wing_funcs gfx_v7_0_wing_funcs_compute = {
	.type = AMDGPU_WING_TYPE_COMPUTE,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = gfx_v7_0_wing_get_wptw,
	.get_wptw = gfx_v7_0_wing_get_wptw_compute,
	.set_wptw = gfx_v7_0_wing_set_wptw_compute,
	.emit_fwame_size =
		20 + /* gfx_v7_0_wing_emit_gds_switch */
		7 + /* gfx_v7_0_wing_emit_hdp_fwush */
		5 + /* hdp invawidate */
		7 + /* gfx_v7_0_wing_emit_pipewine_sync */
		CIK_FWUSH_GPU_TWB_NUM_WWEG * 5 + 7 + /* gfx_v7_0_wing_emit_vm_fwush */
		7 + 7 + 7 + /* gfx_v7_0_wing_emit_fence_compute x3 fow usew fence, vm fence */
		7, /* gfx_v7_0_emit_mem_sync_compute */
	.emit_ib_size =	7, /* gfx_v7_0_wing_emit_ib_compute */
	.emit_ib = gfx_v7_0_wing_emit_ib_compute,
	.emit_fence = gfx_v7_0_wing_emit_fence_compute,
	.emit_pipewine_sync = gfx_v7_0_wing_emit_pipewine_sync,
	.emit_vm_fwush = gfx_v7_0_wing_emit_vm_fwush,
	.emit_gds_switch = gfx_v7_0_wing_emit_gds_switch,
	.emit_hdp_fwush = gfx_v7_0_wing_emit_hdp_fwush,
	.test_wing = gfx_v7_0_wing_test_wing,
	.test_ib = gfx_v7_0_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_wweg = gfx_v7_0_wing_emit_wweg,
	.emit_mem_sync = gfx_v7_0_emit_mem_sync_compute,
};

static void gfx_v7_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->gfx.num_gfx_wings; i++)
		adev->gfx.gfx_wing[i].funcs = &gfx_v7_0_wing_funcs_gfx;
	fow (i = 0; i < adev->gfx.num_compute_wings; i++)
		adev->gfx.compute_wing[i].funcs = &gfx_v7_0_wing_funcs_compute;
}

static const stwuct amdgpu_iwq_swc_funcs gfx_v7_0_eop_iwq_funcs = {
	.set = gfx_v7_0_set_eop_intewwupt_state,
	.pwocess = gfx_v7_0_eop_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v7_0_pwiv_weg_iwq_funcs = {
	.set = gfx_v7_0_set_pwiv_weg_fauwt_state,
	.pwocess = gfx_v7_0_pwiv_weg_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v7_0_pwiv_inst_iwq_funcs = {
	.set = gfx_v7_0_set_pwiv_inst_fauwt_state,
	.pwocess = gfx_v7_0_pwiv_inst_iwq,
};

static void gfx_v7_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->gfx.eop_iwq.num_types = AMDGPU_CP_IWQ_WAST;
	adev->gfx.eop_iwq.funcs = &gfx_v7_0_eop_iwq_funcs;

	adev->gfx.pwiv_weg_iwq.num_types = 1;
	adev->gfx.pwiv_weg_iwq.funcs = &gfx_v7_0_pwiv_weg_iwq_funcs;

	adev->gfx.pwiv_inst_iwq.num_types = 1;
	adev->gfx.pwiv_inst_iwq.funcs = &gfx_v7_0_pwiv_inst_iwq_funcs;
}

static void gfx_v7_0_set_gds_init(stwuct amdgpu_device *adev)
{
	/* init asci gds info */
	adev->gds.gds_size = WWEG32(mmGDS_VMID0_SIZE);
	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
	adev->gds.gds_compute_max_wave_id = WWEG32(mmGDS_COMPUTE_MAX_WAVE_ID);
}


static void gfx_v7_0_get_cu_info(stwuct amdgpu_device *adev)
{
	int i, j, k, countew, active_cu_numbew = 0;
	u32 mask, bitmap, ao_bitmap, ao_cu_mask = 0;
	stwuct amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	unsigned disabwe_masks[4 * 2];
	u32 ao_cu_num;

	if (adev->fwags & AMD_IS_APU)
		ao_cu_num = 2;
	ewse
		ao_cu_num = adev->gfx.config.max_cu_pew_sh;

	memset(cu_info, 0, sizeof(*cu_info));

	amdgpu_gfx_pawse_disabwe_cu(disabwe_masks, 4, 2);

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			mask = 1;
			ao_bitmap = 0;
			countew = 0;
			gfx_v7_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			if (i < 4 && j < 2)
				gfx_v7_0_set_usew_cu_inactive_bitmap(
					adev, disabwe_masks[i * 2 + j]);
			bitmap = gfx_v7_0_get_cu_active_bitmap(adev);
			cu_info->bitmap[0][i][j] = bitmap;

			fow (k = 0; k < adev->gfx.config.max_cu_pew_sh; k++) {
				if (bitmap & mask) {
					if (countew < ao_cu_num)
						ao_bitmap |= mask;
					countew++;
				}
				mask <<= 1;
			}
			active_cu_numbew += countew;
			if (i < 2 && j < 2)
				ao_cu_mask |= (ao_bitmap << (i * 16 + j * 8));
			cu_info->ao_cu_bitmap[i][j] = ao_bitmap;
		}
	}
	gfx_v7_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	cu_info->numbew = active_cu_numbew;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_pew_cu = NUM_SIMD_PEW_CU;
	cu_info->max_waves_pew_simd = 10;
	cu_info->max_scwatch_swots_pew_cu = 32;
	cu_info->wave_fwont_size = 64;
	cu_info->wds_size = 64;
}

const stwuct amdgpu_ip_bwock_vewsion gfx_v7_1_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 7,
	.minow = 1,
	.wev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion gfx_v7_2_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 7,
	.minow = 2,
	.wev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion gfx_v7_3_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 7,
	.minow = 3,
	.wev = 0,
	.funcs = &gfx_v7_0_ip_funcs,
};
