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

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_twace.h"

#incwude "gc/gc_10_1_0_offset.h"
#incwude "gc/gc_10_1_0_sh_mask.h"
#incwude "ivswcid/sdma0/iwqswcs_sdma0_5_0.h"
#incwude "ivswcid/sdma1/iwqswcs_sdma1_5_0.h"

#incwude "soc15_common.h"
#incwude "soc15.h"
#incwude "navi10_sdma_pkt_open.h"
#incwude "nbio_v2_3.h"
#incwude "sdma_common.h"
#incwude "sdma_v5_0.h"

MODUWE_FIWMWAWE("amdgpu/navi10_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/navi10_sdma1.bin");

MODUWE_FIWMWAWE("amdgpu/navi14_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/navi14_sdma1.bin");

MODUWE_FIWMWAWE("amdgpu/navi12_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/navi12_sdma1.bin");

MODUWE_FIWMWAWE("amdgpu/cyan_skiwwfish2_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/cyan_skiwwfish2_sdma1.bin");

#define SDMA1_WEG_OFFSET 0x600
#define SDMA0_HYP_DEC_WEG_STAWT 0x5880
#define SDMA0_HYP_DEC_WEG_END 0x5893
#define SDMA1_HYP_DEC_WEG_OFFSET 0x20

static void sdma_v5_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void sdma_v5_0_set_buffew_funcs(stwuct amdgpu_device *adev);
static void sdma_v5_0_set_vm_pte_funcs(stwuct amdgpu_device *adev);
static void sdma_v5_0_set_iwq_funcs(stwuct amdgpu_device *adev);

static const stwuct soc15_weg_gowden gowden_settings_sdma_5[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_CHICKEN_BITS, 0xffbf1f0f, 0x03ab0107),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_UTCW1_PAGE, 0x00ffffff, 0x000c5c00),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_CHICKEN_BITS, 0xffbf1f0f, 0x03ab0107),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_UTCW1_PAGE, 0x00ffffff, 0x000c5c00)
};

static const stwuct soc15_weg_gowden gowden_settings_sdma_5_swiov[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
};

static const stwuct soc15_weg_gowden gowden_settings_sdma_nv10[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0x0000fff0, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0x0000fff0, 0x00403000),
};

static const stwuct soc15_weg_gowden gowden_settings_sdma_nv14[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
};

static const stwuct soc15_weg_gowden gowden_settings_sdma_nv12[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GB_ADDW_CONFIG, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GB_ADDW_CONFIG_WEAD, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GB_ADDW_CONFIG, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GB_ADDW_CONFIG_WEAD, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
};

static const stwuct soc15_weg_gowden gowden_settings_sdma_cyan_skiwwfish[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_CHICKEN_BITS, 0xffbf1f0f, 0x03ab0107),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GB_ADDW_CONFIG, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GB_ADDW_CONFIG_WEAD, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA0_UTCW1_PAGE, 0x007fffff, 0x004c5c00),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_CHICKEN_BITS, 0xffbf1f0f, 0x03ab0107),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GB_ADDW_CONFIG, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GB_ADDW_CONFIG_WEAD, 0x001877ff, 0x00000044),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_GFX_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_PAGE_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC0_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC1_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC2_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC3_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC4_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC5_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC6_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_WWC7_WB_WPTW_POWW_CNTW, 0xfffffff7, 0x00403000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, mmSDMA1_UTCW1_PAGE, 0x007fffff, 0x004c5c00)
};

static u32 sdma_v5_0_get_weg_offset(stwuct amdgpu_device *adev, u32 instance, u32 intewnaw_offset)
{
	u32 base;

	if (intewnaw_offset >= SDMA0_HYP_DEC_WEG_STAWT &&
	    intewnaw_offset <= SDMA0_HYP_DEC_WEG_END) {
		base = adev->weg_offset[GC_HWIP][0][1];
		if (instance == 1)
			intewnaw_offset += SDMA1_HYP_DEC_WEG_OFFSET;
	} ewse {
		base = adev->weg_offset[GC_HWIP][0][0];
		if (instance == 1)
			intewnaw_offset += SDMA1_WEG_OFFSET;
	}

	wetuwn base + intewnaw_offset;
}

static void sdma_v5_0_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0)) {
	case IP_VEWSION(5, 0, 0):
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_5,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_5));
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_nv10,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_nv10));
		bweak;
	case IP_VEWSION(5, 0, 2):
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_5,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_5));
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_nv14,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_nv14));
		bweak;
	case IP_VEWSION(5, 0, 5):
		if (amdgpu_swiov_vf(adev))
			soc15_pwogwam_wegistew_sequence(adev,
							gowden_settings_sdma_5_swiov,
							(const u32)AWWAY_SIZE(gowden_settings_sdma_5_swiov));
		ewse
			soc15_pwogwam_wegistew_sequence(adev,
							gowden_settings_sdma_5,
							(const u32)AWWAY_SIZE(gowden_settings_sdma_5));
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_nv12,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_nv12));
		bweak;
	case IP_VEWSION(5, 0, 1):
		soc15_pwogwam_wegistew_sequence(adev,
						gowden_settings_sdma_cyan_skiwwfish,
						(const u32)AWWAY_SIZE(gowden_settings_sdma_cyan_skiwwfish));
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * sdma_v5_0_init_micwocode - woad ucode images fwom disk
 *
 * @adev: amdgpu_device pointew
 *
 * Use the fiwmwawe intewface to woad the ucode images into
 * the dwivew (not woaded into hw).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */

// emuwation onwy, won't wowk on weaw chip
// navi10 weaw chip need to use PSP to woad fiwmwawe
static int sdma_v5_0_init_micwocode(stwuct amdgpu_device *adev)
{
	int wet, i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wet = amdgpu_sdma_init_micwocode(adev, i, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static unsigned sdma_v5_0_wing_init_cond_exec(stwuct amdgpu_wing *wing)
{
	unsigned wet;

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_COND_EXE));
	amdgpu_wing_wwite(wing, wowew_32_bits(wing->cond_exe_gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(wing->cond_exe_gpu_addw));
	amdgpu_wing_wwite(wing, 1);
	wet = wing->wptw & wing->buf_mask;/* this is the offset we need patch watew */
	amdgpu_wing_wwite(wing, 0x55aa55aa);/* insewt dummy hewe and patch it watew */

	wetuwn wet;
}

static void sdma_v5_0_wing_patch_cond_exec(stwuct amdgpu_wing *wing,
					   unsigned offset)
{
	unsigned cuw;

	BUG_ON(offset > wing->buf_mask);
	BUG_ON(wing->wing[offset] != 0x55aa55aa);

	cuw = (wing->wptw - 1) & wing->buf_mask;
	if (cuw > offset)
		wing->wing[offset] = cuw - offset;
	ewse
		wing->wing[offset] = (wing->buf_mask + 1) - offset + cuw;
}

/**
 * sdma_v5_0_wing_get_wptw - get the cuwwent wead pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (NAVI10+).
 */
static uint64_t sdma_v5_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	u64 *wptw;

	/* XXX check if swapping is necessawy on BE */
	wptw = (u64 *)wing->wptw_cpu_addw;

	DWM_DEBUG("wptw befowe shift == 0x%016wwx\n", *wptw);
	wetuwn ((*wptw) >> 2);
}

/**
 * sdma_v5_0_wing_get_wptw - get the cuwwent wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (NAVI10+).
 */
static uint64_t sdma_v5_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u64 wptw;

	if (wing->use_doowbeww) {
		/* XXX check if swapping is necessawy on BE */
		wptw = WEAD_ONCE(*((u64 *)wing->wptw_cpu_addw));
		DWM_DEBUG("wptw/doowbeww befowe shift == 0x%016wwx\n", wptw);
	} ewse {
		wptw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, wing->me, mmSDMA0_GFX_WB_WPTW_HI));
		wptw = wptw << 32;
		wptw |= WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, wing->me, mmSDMA0_GFX_WB_WPTW));
		DWM_DEBUG("wptw befowe shift [%i] wptw == 0x%016wwx\n", wing->me, wptw);
	}

	wetuwn wptw >> 2;
}

/**
 * sdma_v5_0_wing_set_wptw - commit the wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Wwite the wptw back to the hawdwawe (NAVI10+).
 */
static void sdma_v5_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t *wptw_saved;
	uint32_t *is_queue_unmap;
	uint64_t aggwegated_db_index;
	uint32_t mqd_size = adev->mqds[AMDGPU_HW_IP_DMA].mqd_size;

	DWM_DEBUG("Setting wwite pointew\n");
	if (wing->is_mes_queue) {
		wptw_saved = (uint32_t *)(wing->mqd_ptw + mqd_size);
		is_queue_unmap = (uint32_t *)(wing->mqd_ptw + mqd_size +
					      sizeof(uint32_t));
		aggwegated_db_index =
			amdgpu_mes_get_aggwegated_doowbeww_index(adev,
			AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW);

		atomic64_set((atomic64_t *)wing->wptw_cpu_addw,
			     wing->wptw << 2);
		*wptw_saved = wing->wptw << 2;
		if (*is_queue_unmap) {
			WDOOWBEWW64(aggwegated_db_index, wing->wptw << 2);
			DWM_DEBUG("cawwing WDOOWBEWW64(0x%08x, 0x%016wwx)\n",
					wing->doowbeww_index, wing->wptw << 2);
			WDOOWBEWW64(wing->doowbeww_index, wing->wptw << 2);
		} ewse {
			DWM_DEBUG("cawwing WDOOWBEWW64(0x%08x, 0x%016wwx)\n",
					wing->doowbeww_index, wing->wptw << 2);
			WDOOWBEWW64(wing->doowbeww_index, wing->wptw << 2);

			if (*is_queue_unmap)
				WDOOWBEWW64(aggwegated_db_index,
					    wing->wptw << 2);
		}
	} ewse {
		if (wing->use_doowbeww) {
			DWM_DEBUG("Using doowbeww -- "
				  "wptw_offs == 0x%08x "
				  "wowew_32_bits(wing->wptw) << 2 == 0x%08x "
				  "uppew_32_bits(wing->wptw) << 2 == 0x%08x\n",
				  wing->wptw_offs,
				  wowew_32_bits(wing->wptw << 2),
				  uppew_32_bits(wing->wptw << 2));
			/* XXX check if swapping is necessawy on BE */
			atomic64_set((atomic64_t *)wing->wptw_cpu_addw,
				     wing->wptw << 2);
			DWM_DEBUG("cawwing WDOOWBEWW64(0x%08x, 0x%016wwx)\n",
				  wing->doowbeww_index, wing->wptw << 2);
			WDOOWBEWW64(wing->doowbeww_index, wing->wptw << 2);
		} ewse {
			DWM_DEBUG("Not using doowbeww -- "
				  "mmSDMA%i_GFX_WB_WPTW == 0x%08x "
				  "mmSDMA%i_GFX_WB_WPTW_HI == 0x%08x\n",
				  wing->me,
				  wowew_32_bits(wing->wptw << 2),
				  wing->me,
				  uppew_32_bits(wing->wptw << 2));
			WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev,
					     wing->me, mmSDMA0_GFX_WB_WPTW),
					wowew_32_bits(wing->wptw << 2));
			WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev,
					     wing->me, mmSDMA0_GFX_WB_WPTW_HI),
					uppew_32_bits(wing->wptw << 2));
		}
	}
}

static void sdma_v5_0_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	stwuct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_fwom_wing(wing);
	int i;

	fow (i = 0; i < count; i++)
		if (sdma && sdma->buwst_nop && (i == 0))
			amdgpu_wing_wwite(wing, wing->funcs->nop |
				SDMA_PKT_NOP_HEADEW_COUNT(count - 1));
		ewse
			amdgpu_wing_wwite(wing, wing->funcs->nop);
}

/**
 * sdma_v5_0_wing_emit_ib - Scheduwe an IB on the DMA engine
 *
 * @wing: amdgpu wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: IB object to scheduwe
 * @fwags: unused
 *
 * Scheduwe an IB in the DMA wing (NAVI10).
 */
static void sdma_v5_0_wing_emit_ib(stwuct amdgpu_wing *wing,
				   stwuct amdgpu_job *job,
				   stwuct amdgpu_ib *ib,
				   uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	uint64_t csa_mc_addw = amdgpu_sdma_get_csa_mc_addw(wing, vmid);

	/* An IB packet must end on a 8 DW boundawy--the next dwowd
	 * must be on a 8-dwowd boundawy. Ouw IB packet bewow is 6
	 * dwowds wong, thus add x numbew of NOPs, such that, in
	 * moduwaw awithmetic,
	 * wptw + 6 + x = 8k, k >= 0, which in C is,
	 * (wptw + 6 + x) % 8 = 0.
	 * The expwession bewow, is a sowution of x.
	 */
	sdma_v5_0_wing_insewt_nop(wing, (2 - wowew_32_bits(wing->wptw)) & 7);

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_INDIWECT) |
			  SDMA_PKT_INDIWECT_HEADEW_VMID(vmid & 0xf));
	/* base must be 32 byte awigned */
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw) & 0xffffffe0);
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
	amdgpu_wing_wwite(wing, wowew_32_bits(csa_mc_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(csa_mc_addw));
}

/**
 * sdma_v5_0_wing_emit_mem_sync - fwush the IB by gwaphics cache winse
 *
 * @wing: amdgpu wing pointew
 *
 * fwush the IB by gwaphics cache winse.
 */
static void sdma_v5_0_wing_emit_mem_sync(stwuct amdgpu_wing *wing)
{
	uint32_t gcw_cntw = SDMA_GCW_GW2_INV | SDMA_GCW_GW2_WB | SDMA_GCW_GWM_INV |
			    SDMA_GCW_GW1_INV | SDMA_GCW_GWV_INV | SDMA_GCW_GWK_INV |
			    SDMA_GCW_GWI_INV(1);

	/* fwush entiwe cache W0/W1/W2, this can be optimized by pewfowmance wequiwement */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_GCW_WEQ));
	amdgpu_wing_wwite(wing, SDMA_PKT_GCW_WEQ_PAYWOAD1_BASE_VA_31_7(0));
	amdgpu_wing_wwite(wing, SDMA_PKT_GCW_WEQ_PAYWOAD2_GCW_CONTWOW_15_0(gcw_cntw) |
			  SDMA_PKT_GCW_WEQ_PAYWOAD2_BASE_VA_47_32(0));
	amdgpu_wing_wwite(wing, SDMA_PKT_GCW_WEQ_PAYWOAD3_WIMIT_VA_31_7(0) |
			  SDMA_PKT_GCW_WEQ_PAYWOAD3_GCW_CONTWOW_18_16(gcw_cntw >> 16));
	amdgpu_wing_wwite(wing, SDMA_PKT_GCW_WEQ_PAYWOAD4_WIMIT_VA_47_32(0) |
			  SDMA_PKT_GCW_WEQ_PAYWOAD4_VMID(0));
}

/**
 * sdma_v5_0_wing_emit_hdp_fwush - emit an hdp fwush on the DMA wing
 *
 * @wing: amdgpu wing pointew
 *
 * Emit an hdp fwush packet on the wequested DMA wing.
 */
static void sdma_v5_0_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 wef_and_mask = 0;
	const stwuct nbio_hdp_fwush_weg *nbio_hf_weg = adev->nbio.hdp_fwush_weg;

	if (wing->me == 0)
		wef_and_mask = nbio_hf_weg->wef_and_mask_sdma0;
	ewse
		wef_and_mask = nbio_hf_weg->wef_and_mask_sdma1;

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_POWW_WEGMEM) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(1) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(3)); /* == */
	amdgpu_wing_wwite(wing, (adev->nbio.funcs->get_hdp_fwush_done_offset(adev)) << 2);
	amdgpu_wing_wwite(wing, (adev->nbio.funcs->get_hdp_fwush_weq_offset(adev)) << 2);
	amdgpu_wing_wwite(wing, wef_and_mask); /* wefewence */
	amdgpu_wing_wwite(wing, wef_and_mask); /* mask */
	amdgpu_wing_wwite(wing, SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(0xfff) |
			  SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(10)); /* wetwy count, poww intewvaw */
}

/**
 * sdma_v5_0_wing_emit_fence - emit a fence on the DMA wing
 *
 * @wing: amdgpu wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (NAVI10).
 */
static void sdma_v5_0_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				      unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	/* wwite the fence */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_FENCE) |
			  SDMA_PKT_FENCE_HEADEW_MTYPE(0x3)); /* Ucached(UC) */
	/* zewo in fiwst two bits */
	BUG_ON(addw & 0x3);
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));

	/* optionawwy wwite high bits as weww */
	if (wwite64bit) {
		addw += 4;
		amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_FENCE) |
				  SDMA_PKT_FENCE_HEADEW_MTYPE(0x3));
		/* zewo in fiwst two bits */
		BUG_ON(addw & 0x3);
		amdgpu_wing_wwite(wing, wowew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(seq));
	}

	if (fwags & AMDGPU_FENCE_FWAG_INT) {
		uint32_t ctx = wing->is_mes_queue ?
			(wing->hw_queue_id | AMDGPU_FENCE_MES_QUEUE_FWAG) : 0;
		/* genewate an intewwupt */
		amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_TWAP));
		amdgpu_wing_wwite(wing, SDMA_PKT_TWAP_INT_CONTEXT_INT_CONTEXT(ctx));
	}
}


/**
 * sdma_v5_0_gfx_stop - stop the gfx async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the gfx async dma wing buffews (NAVI10).
 */
static void sdma_v5_0_gfx_stop(stwuct amdgpu_device *adev)
{
	u32 wb_cntw, ib_cntw;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wb_cntw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_CNTW));
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_ENABWE, 0);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_CNTW), wb_cntw);
		ib_cntw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_IB_CNTW));
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_ENABWE, 0);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_IB_CNTW), ib_cntw);
	}
}

/**
 * sdma_v5_0_wwc_stop - stop the compute async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the compute async dma queues (NAVI10).
 */
static void sdma_v5_0_wwc_stop(stwuct amdgpu_device *adev)
{
	/* XXX todo */
}

/**
 * sdma_v5_0_ctx_switch_enabwe - stop the async dma engines context switch
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs context switch.
 *
 * Hawt ow unhawt the async dma engines context switch (NAVI10).
 */
static void sdma_v5_0_ctx_switch_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 f32_cntw = 0, phase_quantum = 0;
	int i;

	if (amdgpu_sdma_phase_quantum) {
		unsigned vawue = amdgpu_sdma_phase_quantum;
		unsigned unit = 0;

		whiwe (vawue > (SDMA0_PHASE0_QUANTUM__VAWUE_MASK >>
				SDMA0_PHASE0_QUANTUM__VAWUE__SHIFT)) {
			vawue = (vawue + 1) >> 1;
			unit++;
		}
		if (unit > (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
			    SDMA0_PHASE0_QUANTUM__UNIT__SHIFT)) {
			vawue = (SDMA0_PHASE0_QUANTUM__VAWUE_MASK >>
				 SDMA0_PHASE0_QUANTUM__VAWUE__SHIFT);
			unit = (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
				SDMA0_PHASE0_QUANTUM__UNIT__SHIFT);
			WAWN_ONCE(1,
			"cwamping sdma_phase_quantum to %uK cwock cycwes\n",
				  vawue << unit);
		}
		phase_quantum =
			vawue << SDMA0_PHASE0_QUANTUM__VAWUE__SHIFT |
			unit  << SDMA0_PHASE0_QUANTUM__UNIT__SHIFT;
	}

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (!amdgpu_swiov_vf(adev)) {
			f32_cntw = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CNTW));
			f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_CNTW,
						 AUTO_CTXSW_ENABWE, enabwe ? 1 : 0);
		}

		if (enabwe && amdgpu_sdma_phase_quantum) {
			WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_PHASE0_QUANTUM),
			       phase_quantum);
			WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_PHASE1_QUANTUM),
			       phase_quantum);
			WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_PHASE2_QUANTUM),
			       phase_quantum);
		}
		if (!amdgpu_swiov_vf(adev))
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CNTW), f32_cntw);
	}

}

/**
 * sdma_v5_0_enabwe - stop the async dma engines
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs.
 *
 * Hawt ow unhawt the async dma engines (NAVI10).
 */
static void sdma_v5_0_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 f32_cntw;
	int i;

	if (!enabwe) {
		sdma_v5_0_gfx_stop(adev);
		sdma_v5_0_wwc_stop(adev);
	}

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntw = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_F32_CNTW));
		f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_F32_CNTW, HAWT, enabwe ? 0 : 1);
		WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_F32_CNTW), f32_cntw);
	}
}

/**
 * sdma_v5_0_gfx_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the gfx DMA wing buffews and enabwe them (NAVI10).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v5_0_gfx_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 wb_cntw, ib_cntw;
	u32 wb_bufsz;
	u32 doowbeww;
	u32 doowbeww_offset;
	u32 temp;
	u32 wptw_poww_cntw;
	u64 wptw_gpu_addw;
	int i, w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;

		if (!amdgpu_swiov_vf(adev))
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_SEM_WAIT_FAIW_TIMEW_CNTW), 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_CNTW));
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_SIZE, wb_bufsz);
#ifdef __BIG_ENDIAN
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_SWAP_ENABWE, 1);
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW,
					WPTW_WWITEBACK_SWAP_ENABWE, 1);
#endif
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_CNTW), wb_cntw);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW), 0);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_HI), 0);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW), 0);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_HI), 0);

		/* setup the wptw shadow powwing */
		wptw_gpu_addw = wing->wptw_gpu_addw;
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_POWW_ADDW_WO),
		       wowew_32_bits(wptw_gpu_addw));
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_POWW_ADDW_HI),
		       uppew_32_bits(wptw_gpu_addw));
		wptw_poww_cntw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i,
							 mmSDMA0_GFX_WB_WPTW_POWW_CNTW));
		wptw_poww_cntw = WEG_SET_FIEWD(wptw_poww_cntw,
					       SDMA0_GFX_WB_WPTW_POWW_CNTW,
					       F32_POWW_ENABWE, 1);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_POWW_CNTW),
		       wptw_poww_cntw);

		/* set the wb addwess whethew it's enabwed ow not */
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_ADDW_HI),
		       uppew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFF);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_ADDW_WO),
		       wowew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFC);

		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WPTW_WWITEBACK_ENABWE, 1);

		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_BASE),
		       wing->gpu_addw >> 8);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_BASE_HI),
		       wing->gpu_addw >> 40);

		wing->wptw = 0;

		/* befowe pwogwaming wptw to a wess vawue, need set minow_ptw_update fiwst */
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_MINOW_PTW_UPDATE), 1);

		if (!amdgpu_swiov_vf(adev)) { /* onwy bawe-metaw use wegistew wwite fow wptw */
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW),
			       wowew_32_bits(wing->wptw << 2));
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_WPTW_HI),
			       uppew_32_bits(wing->wptw << 2));
		}

		doowbeww = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_DOOWBEWW));
		doowbeww_offset = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i,
						mmSDMA0_GFX_DOOWBEWW_OFFSET));

		if (wing->use_doowbeww) {
			doowbeww = WEG_SET_FIEWD(doowbeww, SDMA0_GFX_DOOWBEWW, ENABWE, 1);
			doowbeww_offset = WEG_SET_FIEWD(doowbeww_offset, SDMA0_GFX_DOOWBEWW_OFFSET,
					OFFSET, wing->doowbeww_index);
		} ewse {
			doowbeww = WEG_SET_FIEWD(doowbeww, SDMA0_GFX_DOOWBEWW, ENABWE, 0);
		}
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_DOOWBEWW), doowbeww);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_DOOWBEWW_OFFSET),
		       doowbeww_offset);

		adev->nbio.funcs->sdma_doowbeww_wange(adev, i, wing->use_doowbeww,
						      wing->doowbeww_index, 20);

		if (amdgpu_swiov_vf(adev))
			sdma_v5_0_wing_set_wptw(wing);

		/* set minow_ptw_update to 0 aftew wptw pwogwamed */
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_MINOW_PTW_UPDATE), 0);

		if (!amdgpu_swiov_vf(adev)) {
			/* set utc w1 enabwe fwag awways to 1 */
			temp = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CNTW));
			temp = WEG_SET_FIEWD(temp, SDMA0_CNTW, UTC_W1_ENABWE, 1);

			/* enabwe MCBP */
			temp = WEG_SET_FIEWD(temp, SDMA0_CNTW, MIDCMD_PWEEMPT_ENABWE, 1);
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CNTW), temp);

			/* Set up WESP_MODE to non-copy addwesses */
			temp = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UTCW1_CNTW));
			temp = WEG_SET_FIEWD(temp, SDMA0_UTCW1_CNTW, WESP_MODE, 3);
			temp = WEG_SET_FIEWD(temp, SDMA0_UTCW1_CNTW, WEDO_DEWAY, 9);
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UTCW1_CNTW), temp);

			/* pwogwam defauwt cache wead and wwite powicy */
			temp = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UTCW1_PAGE));
			/* cwean wead powicy and wwite powicy bits */
			temp &= 0xFF0FFF;
			temp |= ((CACHE_WEAD_POWICY_W2__DEFAUWT << 12) | (CACHE_WWITE_POWICY_W2__DEFAUWT << 14));
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UTCW1_PAGE), temp);
		}

		if (!amdgpu_swiov_vf(adev)) {
			/* unhawt engine */
			temp = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_F32_CNTW));
			temp = WEG_SET_FIEWD(temp, SDMA0_F32_CNTW, HAWT, 0);
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_F32_CNTW), temp);
		}

		/* enabwe DMA WB */
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_ENABWE, 1);
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_WB_CNTW), wb_cntw);

		ib_cntw = WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_IB_CNTW));
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_ENABWE, 1);
#ifdef __BIG_ENDIAN
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_SWAP_ENABWE, 1);
#endif
		/* enabwe DMA IBs */
		WWEG32_SOC15_IP(GC, sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_GFX_IB_CNTW), ib_cntw);

		if (amdgpu_swiov_vf(adev)) { /* bawe-metaw sequence doesn't need bewow to wines */
			sdma_v5_0_ctx_switch_enabwe(adev, twue);
			sdma_v5_0_enabwe(adev, twue);
		}

		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * sdma_v5_0_wwc_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the compute DMA queues and enabwe them (NAVI10).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v5_0_wwc_wesume(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}

/**
 * sdma_v5_0_woad_micwocode - woad the sDMA ME ucode
 *
 * @adev: amdgpu_device pointew
 *
 * Woads the sDMA0/1 ucode.
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int sdma_v5_0_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct sdma_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data;
	u32 fw_size;
	int i, j;

	/* hawt the MEs */
	sdma_v5_0_enabwe(adev, fawse);

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (!adev->sdma.instance[i].fw)
			wetuwn -EINVAW;

		hdw = (const stwuct sdma_fiwmwawe_headew_v1_0 *)adev->sdma.instance[i].fw->data;
		amdgpu_ucode_pwint_sdma_hdw(&hdw->headew);
		fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;

		fw_data = (const __we32 *)
			(adev->sdma.instance[i].fw->data +
				we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));

		WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UCODE_ADDW), 0);

		fow (j = 0; j < fw_size; j++) {
			if (amdgpu_emu_mode == 1 && j % 500 == 0)
				msweep(1);
			WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UCODE_DATA), we32_to_cpup(fw_data++));
		}

		WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_UCODE_ADDW), adev->sdma.instance[i].fw_vewsion);
	}

	wetuwn 0;
}

/**
 * sdma_v5_0_stawt - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the DMA engines and enabwe them (NAVI10).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v5_0_stawt(stwuct amdgpu_device *adev)
{
	int w = 0;

	if (amdgpu_swiov_vf(adev)) {
		sdma_v5_0_ctx_switch_enabwe(adev, fawse);
		sdma_v5_0_enabwe(adev, fawse);

		/* set WB wegistews */
		w = sdma_v5_0_gfx_wesume(adev);
		wetuwn w;
	}

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT) {
		w = sdma_v5_0_woad_micwocode(adev);
		if (w)
			wetuwn w;
	}

	/* unhawt the MEs */
	sdma_v5_0_enabwe(adev, twue);
	/* enabwe sdma wing pweemption */
	sdma_v5_0_ctx_switch_enabwe(adev, twue);

	/* stawt the gfx wings and wwc compute queues */
	w = sdma_v5_0_gfx_wesume(adev);
	if (w)
		wetuwn w;
	w = sdma_v5_0_wwc_wesume(adev);

	wetuwn w;
}

static int sdma_v5_0_mqd_init(stwuct amdgpu_device *adev, void *mqd,
			      stwuct amdgpu_mqd_pwop *pwop)
{
	stwuct v10_sdma_mqd *m = mqd;
	uint64_t wb_gpu_addw;

	m->sdmax_wwcx_wb_cntw =
		owdew_base_2(pwop->queue_size / 4) << SDMA0_WWC0_WB_CNTW__WB_SIZE__SHIFT |
		1 << SDMA0_WWC0_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT |
		6 << SDMA0_WWC0_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT |
		1 << SDMA0_WWC0_WB_CNTW__WB_PWIV__SHIFT;

	m->sdmax_wwcx_wb_base = wowew_32_bits(pwop->hqd_base_gpu_addw >> 8);
	m->sdmax_wwcx_wb_base_hi = uppew_32_bits(pwop->hqd_base_gpu_addw >> 8);

	m->sdmax_wwcx_wb_wptw_poww_cntw = WWEG32(sdma_v5_0_get_weg_offset(adev, 0,
						  mmSDMA0_GFX_WB_WPTW_POWW_CNTW));

	wb_gpu_addw = pwop->wptw_gpu_addw;
	m->sdmax_wwcx_wb_wptw_poww_addw_wo = wowew_32_bits(wb_gpu_addw);
	m->sdmax_wwcx_wb_wptw_poww_addw_hi = uppew_32_bits(wb_gpu_addw);

	wb_gpu_addw = pwop->wptw_gpu_addw;
	m->sdmax_wwcx_wb_wptw_addw_wo = wowew_32_bits(wb_gpu_addw);
	m->sdmax_wwcx_wb_wptw_addw_hi = uppew_32_bits(wb_gpu_addw);

	m->sdmax_wwcx_ib_cntw = WWEG32(sdma_v5_0_get_weg_offset(adev, 0,
							mmSDMA0_GFX_IB_CNTW));

	m->sdmax_wwcx_doowbeww_offset =
		pwop->doowbeww_index << SDMA0_WWC0_DOOWBEWW_OFFSET__OFFSET__SHIFT;

	m->sdmax_wwcx_doowbeww = WEG_SET_FIEWD(0, SDMA0_WWC0_DOOWBEWW, ENABWE, 1);

	wetuwn 0;
}

static void sdma_v5_0_set_mqd_funcs(stwuct amdgpu_device *adev)
{
	adev->mqds[AMDGPU_HW_IP_DMA].mqd_size = sizeof(stwuct v10_sdma_mqd);
	adev->mqds[AMDGPU_HW_IP_DMA].init_mqd = sdma_v5_0_mqd_init;
}

/**
 * sdma_v5_0_wing_test_wing - simpwe async dma engine test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (NAVI10).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v5_0_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned i;
	unsigned index;
	int w;
	u32 tmp;
	u64 gpu_addw;
	vowatiwe uint32_t *cpu_ptw = NUWW;

	tmp = 0xCAFEDEAD;

	if (wing->is_mes_queue) {
		uint32_t offset = 0;
		offset = amdgpu_mes_ctx_get_offs(wing,
					 AMDGPU_MES_CTX_PADDING_OFFS);
		gpu_addw = amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset);
		cpu_ptw = amdgpu_mes_ctx_get_offs_cpu_addw(wing, offset);
		*cpu_ptw = tmp;
	} ewse {
		w = amdgpu_device_wb_get(adev, &index);
		if (w) {
			dev_eww(adev->dev, "(%d) faiwed to awwocate wb swot\n", w);
			wetuwn w;
		}

		gpu_addw = adev->wb.gpu_addw + (index * 4);
		adev->wb.wb[index] = cpu_to_we32(tmp);
	}

	w = amdgpu_wing_awwoc(wing, 20);
	if (w) {
		DWM_EWWOW("amdgpu: dma faiwed to wock wing %d (%d).\n", wing->idx, w);
		amdgpu_device_wb_fwee(adev, index);
		wetuwn w;
	}

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
			  SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW));
	amdgpu_wing_wwite(wing, wowew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, SDMA_PKT_WWITE_UNTIWED_DW_3_COUNT(0));
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (wing->is_mes_queue)
			tmp = we32_to_cpu(*cpu_ptw);
		ewse
			tmp = we32_to_cpu(adev->wb.wb[index]);
		if (tmp == 0xDEADBEEF)
			bweak;
		if (amdgpu_emu_mode == 1)
			msweep(1);
		ewse
			udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	if (!wing->is_mes_queue)
		amdgpu_device_wb_fwee(adev, index);

	wetuwn w;
}

/**
 * sdma_v5_0_wing_test_ib - test an IB on the DMA engine
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Test a simpwe IB in the DMA wing (NAVI10).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int sdma_v5_0_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;
	unsigned index;
	wong w;
	u32 tmp = 0;
	u64 gpu_addw;
	vowatiwe uint32_t *cpu_ptw = NUWW;

	tmp = 0xCAFEDEAD;
	memset(&ib, 0, sizeof(ib));

	if (wing->is_mes_queue) {
		uint32_t offset = 0;
		offset = amdgpu_mes_ctx_get_offs(wing, AMDGPU_MES_CTX_IB_OFFS);
		ib.gpu_addw = amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset);
		ib.ptw = (void *)amdgpu_mes_ctx_get_offs_cpu_addw(wing, offset);

		offset = amdgpu_mes_ctx_get_offs(wing,
					 AMDGPU_MES_CTX_PADDING_OFFS);
		gpu_addw = amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset);
		cpu_ptw = amdgpu_mes_ctx_get_offs_cpu_addw(wing, offset);
		*cpu_ptw = tmp;
	} ewse {
		w = amdgpu_device_wb_get(adev, &index);
		if (w) {
			dev_eww(adev->dev, "(%wd) faiwed to awwocate wb swot\n", w);
			wetuwn w;
		}

		gpu_addw = adev->wb.gpu_addw + (index * 4);
		adev->wb.wb[index] = cpu_to_we32(tmp);

		w = amdgpu_ib_get(adev, NUWW, 256,
					AMDGPU_IB_POOW_DIWECT, &ib);
		if (w) {
			DWM_EWWOW("amdgpu: faiwed to get ib (%wd).\n", w);
			goto eww0;
		}
	}

	ib.ptw[0] = SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw);
	ib.ptw[3] = SDMA_PKT_WWITE_UNTIWED_DW_3_COUNT(0);
	ib.ptw[4] = 0xDEADBEEF;
	ib.ptw[5] = SDMA_PKT_NOP_HEADEW_OP(SDMA_OP_NOP);
	ib.ptw[6] = SDMA_PKT_NOP_HEADEW_OP(SDMA_OP_NOP);
	ib.ptw[7] = SDMA_PKT_NOP_HEADEW_OP(SDMA_OP_NOP);
	ib.wength_dw = 8;

	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto eww1;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		DWM_EWWOW("amdgpu: IB test timed out\n");
		w = -ETIMEDOUT;
		goto eww1;
	} ewse if (w < 0) {
		DWM_EWWOW("amdgpu: fence wait faiwed (%wd).\n", w);
		goto eww1;
	}

	if (wing->is_mes_queue)
		tmp = we32_to_cpu(*cpu_ptw);
	ewse
		tmp = we32_to_cpu(adev->wb.wb[index]);

	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

eww1:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
eww0:
	if (!wing->is_mes_queue)
		amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}


/**
 * sdma_v5_0_vm_copy_pte - update PTEs by copying them fwom the GAWT
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using sDMA (NAVI10).
 */
static void sdma_v5_0_vm_copy_pte(stwuct amdgpu_ib *ib,
				  uint64_t pe, uint64_t swc,
				  unsigned count)
{
	unsigned bytes = count * 8;

	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_COPY_WINEAW);
	ib->ptw[ib->wength_dw++] = bytes - 1;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);

}

/**
 * sdma_v5_0_vm_wwite_pte - update PTEs by wwiting them manuawwy
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @vawue: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 *
 * Update PTEs by wwiting them manuawwy using sDMA (NAVI10).
 */
static void sdma_v5_0_vm_wwite_pte(stwuct amdgpu_ib *ib, uint64_t pe,
				   uint64_t vawue, unsigned count,
				   uint32_t incw)
{
	unsigned ndw = count * 2;

	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = ndw - 1;
	fow (; ndw > 0; ndw -= 2) {
		ib->ptw[ib->wength_dw++] = wowew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		vawue += incw;
	}
}

/**
 * sdma_v5_0_vm_set_pte_pde - update the page tabwes using sDMA
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update the page tabwes using sDMA (NAVI10).
 */
static void sdma_v5_0_vm_set_pte_pde(stwuct amdgpu_ib *ib,
				     uint64_t pe,
				     uint64_t addw, unsigned count,
				     uint32_t incw, uint64_t fwags)
{
	/* fow physicawwy contiguous pages (vwam) */
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_PTEPDE);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe); /* dst addw */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(fwags); /* mask */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(fwags);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(addw); /* vawue */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = incw; /* incwement size */
	ib->ptw[ib->wength_dw++] = 0;
	ib->ptw[ib->wength_dw++] = count - 1; /* numbew of entwies */
}

/**
 * sdma_v5_0_wing_pad_ib - pad the IB
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @ib: indiwect buffew to fiww with padding
 *
 * Pad the IB with NOPs to a boundawy muwtipwe of 8.
 */
static void sdma_v5_0_wing_pad_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_fwom_wing(wing);
	u32 pad_count;
	int i;

	pad_count = (-ib->wength_dw) & 0x7;
	fow (i = 0; i < pad_count; i++)
		if (sdma && sdma->buwst_nop && (i == 0))
			ib->ptw[ib->wength_dw++] =
				SDMA_PKT_HEADEW_OP(SDMA_OP_NOP) |
				SDMA_PKT_NOP_HEADEW_COUNT(pad_count - 1);
		ewse
			ib->ptw[ib->wength_dw++] =
				SDMA_PKT_HEADEW_OP(SDMA_OP_NOP);
}


/**
 * sdma_v5_0_wing_emit_pipewine_sync - sync the pipewine
 *
 * @wing: amdgpu_wing pointew
 *
 * Make suwe aww pwevious opewations awe compweted (CIK).
 */
static void sdma_v5_0_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	/* wait fow idwe */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_POWW_WEGMEM) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(0) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(3) | /* equaw */
			  SDMA_PKT_POWW_WEGMEM_HEADEW_MEM_POWW(1));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xffffffff);
	amdgpu_wing_wwite(wing, seq); /* wefewence */
	amdgpu_wing_wwite(wing, 0xffffffff); /* mask */
	amdgpu_wing_wwite(wing, SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(0xfff) |
			  SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(4)); /* wetwy count, poww intewvaw */
}


/**
 * sdma_v5_0_wing_emit_vm_fwush - vm fwush using sDMA
 *
 * @wing: amdgpu_wing pointew
 * @vmid: vmid numbew to use
 * @pd_addw: addwess
 *
 * Update the page tabwe base and fwush the VM TWB
 * using sDMA (NAVI10).
 */
static void sdma_v5_0_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					 unsigned vmid, uint64_t pd_addw)
{
	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);
}

static void sdma_v5_0_wing_emit_wweg(stwuct amdgpu_wing *wing,
				     uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_SWBM_WWITE) |
			  SDMA_PKT_SWBM_WWITE_HEADEW_BYTE_EN(0xf));
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, vaw);
}

static void sdma_v5_0_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
					 uint32_t vaw, uint32_t mask)
{
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_POWW_WEGMEM) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(0) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(3)); /* equaw */
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, vaw); /* wefewence */
	amdgpu_wing_wwite(wing, mask); /* mask */
	amdgpu_wing_wwite(wing, SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(0xfff) |
			  SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(10));
}

static void sdma_v5_0_wing_emit_weg_wwite_weg_wait(stwuct amdgpu_wing *wing,
						   uint32_t weg0, uint32_t weg1,
						   uint32_t wef, uint32_t mask)
{
	amdgpu_wing_emit_wweg(wing, weg0, wef);
	/* wait fow a cycwe to weset vm_inv_eng*_ack */
	amdgpu_wing_emit_weg_wait(wing, weg0, 0, 0);
	amdgpu_wing_emit_weg_wait(wing, weg1, mask, mask);
}

static int sdma_v5_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = sdma_v5_0_init_micwocode(adev);
	if (w)
		wetuwn w;

	sdma_v5_0_set_wing_funcs(adev);
	sdma_v5_0_set_buffew_funcs(adev);
	sdma_v5_0_set_vm_pte_funcs(adev);
	sdma_v5_0_set_iwq_funcs(adev);
	sdma_v5_0_set_mqd_funcs(adev);

	wetuwn 0;
}


static int sdma_v5_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* SDMA twap event */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_SDMA0,
			      SDMA0_5_0__SWCID__SDMA_TWAP,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	/* SDMA twap event */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_SDMA1,
			      SDMA1_5_0__SWCID__SDMA_TWAP,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		wing->wing_obj = NUWW;
		wing->use_doowbeww = twue;

		DWM_DEBUG("SDMA %d use_doowbeww being set to: [%s]\n", i,
				wing->use_doowbeww?"twue":"fawse");

		wing->doowbeww_index = (i == 0) ?
			(adev->doowbeww_index.sdma_engine[0] << 1) //get DWOWD offset
			: (adev->doowbeww_index.sdma_engine[1] << 1); // get DWOWD offset

		wing->vm_hub = AMDGPU_GFXHUB(0);
		spwintf(wing->name, "sdma%d", i);
		w = amdgpu_wing_init(adev, wing, 1024, &adev->sdma.twap_iwq,
				     (i == 0) ? AMDGPU_SDMA_IWQ_INSTANCE0 :
				     AMDGPU_SDMA_IWQ_INSTANCE1,
				     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;
	}

	wetuwn w;
}

static int sdma_v5_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_wing_fini(&adev->sdma.instance[i].wing);

	amdgpu_sdma_destwoy_inst_ctx(adev, fawse);

	wetuwn 0;
}

static int sdma_v5_0_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	sdma_v5_0_init_gowden_wegistews(adev);

	w = sdma_v5_0_stawt(adev);

	wetuwn w;
}

static int sdma_v5_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	sdma_v5_0_ctx_switch_enabwe(adev, fawse);
	sdma_v5_0_enabwe(adev, fawse);

	wetuwn 0;
}

static int sdma_v5_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn sdma_v5_0_hw_fini(adev);
}

static int sdma_v5_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn sdma_v5_0_hw_init(adev);
}

static boow sdma_v5_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		u32 tmp = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_STATUS_WEG));

		if (!(tmp & SDMA0_STATUS_WEG__IDWE_MASK))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int sdma_v5_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	u32 sdma0, sdma1;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		sdma0 = WWEG32(sdma_v5_0_get_weg_offset(adev, 0, mmSDMA0_STATUS_WEG));
		sdma1 = WWEG32(sdma_v5_0_get_weg_offset(adev, 1, mmSDMA0_STATUS_WEG));

		if (sdma0 & sdma1 & SDMA0_STATUS_WEG__IDWE_MASK)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int sdma_v5_0_soft_weset(void *handwe)
{
	/* todo */

	wetuwn 0;
}

static int sdma_v5_0_wing_pweempt_ib(stwuct amdgpu_wing *wing)
{
	int i, w = 0;
	stwuct amdgpu_device *adev = wing->adev;
	u32 index = 0;
	u64 sdma_gfx_pweempt;

	amdgpu_sdma_get_index_fwom_wing(wing, &index);
	if (index == 0)
		sdma_gfx_pweempt = mmSDMA0_GFX_PWEEMPT;
	ewse
		sdma_gfx_pweempt = mmSDMA1_GFX_PWEEMPT;

	/* assewt pweemption condition */
	amdgpu_wing_set_pweempt_cond_exec(wing, fawse);

	/* emit the twaiwing fence */
	wing->twaiw_seq += 1;
	amdgpu_wing_awwoc(wing, 10);
	sdma_v5_0_wing_emit_fence(wing, wing->twaiw_fence_gpu_addw,
				  wing->twaiw_seq, 0);
	amdgpu_wing_commit(wing);

	/* assewt IB pweemption */
	WWEG32(sdma_gfx_pweempt, 1);

	/* poww the twaiwing fence */
	fow (i = 0; i < adev->usec_timeout; i++) {
		if (wing->twaiw_seq ==
		    we32_to_cpu(*(wing->twaiw_fence_cpu_addw)))
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout) {
		w = -EINVAW;
		DWM_EWWOW("wing %d faiwed to be pweempted\n", wing->idx);
	}

	/* deassewt IB pweemption */
	WWEG32(sdma_gfx_pweempt, 0);

	/* deassewt the pweemption condition */
	amdgpu_wing_set_pweempt_cond_exec(wing, twue);
	wetuwn w;
}

static int sdma_v5_0_set_twap_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	u32 sdma_cntw;

	if (!amdgpu_swiov_vf(adev)) {
		u32 weg_offset = (type == AMDGPU_SDMA_IWQ_INSTANCE0) ?
			sdma_v5_0_get_weg_offset(adev, 0, mmSDMA0_CNTW) :
			sdma_v5_0_get_weg_offset(adev, 1, mmSDMA0_CNTW);

		sdma_cntw = WWEG32(weg_offset);
		sdma_cntw = WEG_SET_FIEWD(sdma_cntw, SDMA0_CNTW, TWAP_ENABWE,
					  state == AMDGPU_IWQ_STATE_ENABWE ? 1 : 0);
		WWEG32(weg_offset, sdma_cntw);
	}

	wetuwn 0;
}

static int sdma_v5_0_pwocess_twap_iwq(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t mes_queue_id = entwy->swc_data[0];

	DWM_DEBUG("IH: SDMA twap\n");

	if (adev->enabwe_mes && (mes_queue_id & AMDGPU_FENCE_MES_QUEUE_FWAG)) {
		stwuct amdgpu_mes_queue *queue;

		mes_queue_id &= AMDGPU_FENCE_MES_QUEUE_ID_MASK;

		spin_wock(&adev->mes.queue_id_wock);
		queue = idw_find(&adev->mes.queue_id_idw, mes_queue_id);
		if (queue) {
			DWM_DEBUG("pwocess smda queue id = %d\n", mes_queue_id);
			amdgpu_fence_pwocess(queue->wing);
		}
		spin_unwock(&adev->mes.queue_id_wock);
		wetuwn 0;
	}

	switch (entwy->cwient_id) {
	case SOC15_IH_CWIENTID_SDMA0:
		switch (entwy->wing_id) {
		case 0:
			amdgpu_fence_pwocess(&adev->sdma.instance[0].wing);
			bweak;
		case 1:
			/* XXX compute */
			bweak;
		case 2:
			/* XXX compute */
			bweak;
		case 3:
			/* XXX page queue*/
			bweak;
		}
		bweak;
	case SOC15_IH_CWIENTID_SDMA1:
		switch (entwy->wing_id) {
		case 0:
			amdgpu_fence_pwocess(&adev->sdma.instance[1].wing);
			bweak;
		case 1:
			/* XXX compute */
			bweak;
		case 2:
			/* XXX compute */
			bweak;
		case 3:
			/* XXX page queue*/
			bweak;
		}
		bweak;
	}
	wetuwn 0;
}

static int sdma_v5_0_pwocess_iwwegaw_inst_iwq(stwuct amdgpu_device *adev,
					      stwuct amdgpu_iwq_swc *souwce,
					      stwuct amdgpu_iv_entwy *entwy)
{
	wetuwn 0;
}

static void sdma_v5_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t data, def;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_MGCG)) {
			/* Enabwe sdma cwock gating */
			def = data = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CWK_CTWW));
			data &= ~(SDMA0_CWK_CTWW__SOFT_OVEWWIDE7_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE6_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE5_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE4_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE3_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE2_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE1_MASK |
				  SDMA0_CWK_CTWW__SOFT_OVEWWIDE0_MASK);
			if (def != data)
				WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CWK_CTWW), data);
		} ewse {
			/* Disabwe sdma cwock gating */
			def = data = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CWK_CTWW));
			data |= (SDMA0_CWK_CTWW__SOFT_OVEWWIDE7_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE6_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE5_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE4_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE3_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE2_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE1_MASK |
				 SDMA0_CWK_CTWW__SOFT_OVEWWIDE0_MASK);
			if (def != data)
				WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_CWK_CTWW), data);
		}
	}
}

static void sdma_v5_0_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t data, def;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_WS)) {
			/* Enabwe sdma mem wight sweep */
			def = data = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_POWEW_CNTW));
			data |= SDMA0_POWEW_CNTW__MEM_POWEW_OVEWWIDE_MASK;
			if (def != data)
				WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_POWEW_CNTW), data);

		} ewse {
			/* Disabwe sdma mem wight sweep */
			def = data = WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_POWEW_CNTW));
			data &= ~SDMA0_POWEW_CNTW__MEM_POWEW_OVEWWIDE_MASK;
			if (def != data)
				WWEG32(sdma_v5_0_get_weg_offset(adev, i, mmSDMA0_POWEW_CNTW), data);

		}
	}
}

static int sdma_v5_0_set_cwockgating_state(void *handwe,
					   enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0)) {
	case IP_VEWSION(5, 0, 0):
	case IP_VEWSION(5, 0, 2):
	case IP_VEWSION(5, 0, 5):
		sdma_v5_0_update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		sdma_v5_0_update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sdma_v5_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static void sdma_v5_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	/* AMD_CG_SUPPOWT_SDMA_MGCG */
	data = WWEG32(sdma_v5_0_get_weg_offset(adev, 0, mmSDMA0_CWK_CTWW));
	if (!(data & SDMA0_CWK_CTWW__SOFT_OVEWWIDE7_MASK))
		*fwags |= AMD_CG_SUPPOWT_SDMA_MGCG;

	/* AMD_CG_SUPPOWT_SDMA_WS */
	data = WWEG32(sdma_v5_0_get_weg_offset(adev, 0, mmSDMA0_POWEW_CNTW));
	if (data & SDMA0_POWEW_CNTW__MEM_POWEW_OVEWWIDE_MASK)
		*fwags |= AMD_CG_SUPPOWT_SDMA_WS;
}

const stwuct amd_ip_funcs sdma_v5_0_ip_funcs = {
	.name = "sdma_v5_0",
	.eawwy_init = sdma_v5_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = sdma_v5_0_sw_init,
	.sw_fini = sdma_v5_0_sw_fini,
	.hw_init = sdma_v5_0_hw_init,
	.hw_fini = sdma_v5_0_hw_fini,
	.suspend = sdma_v5_0_suspend,
	.wesume = sdma_v5_0_wesume,
	.is_idwe = sdma_v5_0_is_idwe,
	.wait_fow_idwe = sdma_v5_0_wait_fow_idwe,
	.soft_weset = sdma_v5_0_soft_weset,
	.set_cwockgating_state = sdma_v5_0_set_cwockgating_state,
	.set_powewgating_state = sdma_v5_0_set_powewgating_state,
	.get_cwockgating_state = sdma_v5_0_get_cwockgating_state,
};

static const stwuct amdgpu_wing_funcs sdma_v5_0_wing_funcs = {
	.type = AMDGPU_WING_TYPE_SDMA,
	.awign_mask = 0xf,
	.nop = SDMA_PKT_NOP_HEADEW_OP(SDMA_OP_NOP),
	.suppowt_64bit_ptws = twue,
	.secuwe_submission_suppowted = twue,
	.get_wptw = sdma_v5_0_wing_get_wptw,
	.get_wptw = sdma_v5_0_wing_get_wptw,
	.set_wptw = sdma_v5_0_wing_set_wptw,
	.emit_fwame_size =
		5 + /* sdma_v5_0_wing_init_cond_exec */
		6 + /* sdma_v5_0_wing_emit_hdp_fwush */
		3 + /* hdp_invawidate */
		6 + /* sdma_v5_0_wing_emit_pipewine_sync */
		/* sdma_v5_0_wing_emit_vm_fwush */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 6 * 2 +
		10 + 10 + 10, /* sdma_v5_0_wing_emit_fence x3 fow usew fence, vm fence */
	.emit_ib_size = 5 + 7 + 6, /* sdma_v5_0_wing_emit_ib */
	.emit_ib = sdma_v5_0_wing_emit_ib,
	.emit_mem_sync = sdma_v5_0_wing_emit_mem_sync,
	.emit_fence = sdma_v5_0_wing_emit_fence,
	.emit_pipewine_sync = sdma_v5_0_wing_emit_pipewine_sync,
	.emit_vm_fwush = sdma_v5_0_wing_emit_vm_fwush,
	.emit_hdp_fwush = sdma_v5_0_wing_emit_hdp_fwush,
	.test_wing = sdma_v5_0_wing_test_wing,
	.test_ib = sdma_v5_0_wing_test_ib,
	.insewt_nop = sdma_v5_0_wing_insewt_nop,
	.pad_ib = sdma_v5_0_wing_pad_ib,
	.emit_wweg = sdma_v5_0_wing_emit_wweg,
	.emit_weg_wait = sdma_v5_0_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = sdma_v5_0_wing_emit_weg_wwite_weg_wait,
	.init_cond_exec = sdma_v5_0_wing_init_cond_exec,
	.patch_cond_exec = sdma_v5_0_wing_patch_cond_exec,
	.pweempt_ib = sdma_v5_0_wing_pweempt_ib,
};

static void sdma_v5_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->sdma.instance[i].wing.funcs = &sdma_v5_0_wing_funcs;
		adev->sdma.instance[i].wing.me = i;
	}
}

static const stwuct amdgpu_iwq_swc_funcs sdma_v5_0_twap_iwq_funcs = {
	.set = sdma_v5_0_set_twap_iwq_state,
	.pwocess = sdma_v5_0_pwocess_twap_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs sdma_v5_0_iwwegaw_inst_iwq_funcs = {
	.pwocess = sdma_v5_0_pwocess_iwwegaw_inst_iwq,
};

static void sdma_v5_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->sdma.twap_iwq.num_types = AMDGPU_SDMA_IWQ_INSTANCE0 +
					adev->sdma.num_instances;
	adev->sdma.twap_iwq.funcs = &sdma_v5_0_twap_iwq_funcs;
	adev->sdma.iwwegaw_inst_iwq.funcs = &sdma_v5_0_iwwegaw_inst_iwq_funcs;
}

/**
 * sdma_v5_0_emit_copy_buffew - copy buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 * @tmz: if a secuwe copy shouwd be used
 *
 * Copy GPU buffews using the DMA engine (NAVI10).
 * Used by the amdgpu ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
static void sdma_v5_0_emit_copy_buffew(stwuct amdgpu_ib *ib,
				       uint64_t swc_offset,
				       uint64_t dst_offset,
				       uint32_t byte_count,
				       boow tmz)
{
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_COPY_WINEAW) |
		SDMA_PKT_COPY_WINEAW_HEADEW_TMZ(tmz ? 1 : 0);
	ib->ptw[ib->wength_dw++] = byte_count - 1;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
}

/**
 * sdma_v5_0_emit_fiww_buffew - fiww buffew using the sDMA engine
 *
 * @ib: indiwect buffew to fiww
 * @swc_data: vawue to wwite to buffew
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 *
 * Fiww GPU buffews using the DMA engine (NAVI10).
 */
static void sdma_v5_0_emit_fiww_buffew(stwuct amdgpu_ib *ib,
				       uint32_t swc_data,
				       uint64_t dst_offset,
				       uint32_t byte_count)
{
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_CONST_FIWW);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = swc_data;
	ib->ptw[ib->wength_dw++] = byte_count - 1;
}

static const stwuct amdgpu_buffew_funcs sdma_v5_0_buffew_funcs = {
	.copy_max_bytes = 0x400000,
	.copy_num_dw = 7,
	.emit_copy_buffew = sdma_v5_0_emit_copy_buffew,

	.fiww_max_bytes = 0x400000,
	.fiww_num_dw = 5,
	.emit_fiww_buffew = sdma_v5_0_emit_fiww_buffew,
};

static void sdma_v5_0_set_buffew_funcs(stwuct amdgpu_device *adev)
{
	if (adev->mman.buffew_funcs == NUWW) {
		adev->mman.buffew_funcs = &sdma_v5_0_buffew_funcs;
		adev->mman.buffew_funcs_wing = &adev->sdma.instance[0].wing;
	}
}

static const stwuct amdgpu_vm_pte_funcs sdma_v5_0_vm_pte_funcs = {
	.copy_pte_num_dw = 7,
	.copy_pte = sdma_v5_0_vm_copy_pte,
	.wwite_pte = sdma_v5_0_vm_wwite_pte,
	.set_pte_pde = sdma_v5_0_vm_set_pte_pde,
};

static void sdma_v5_0_set_vm_pte_funcs(stwuct amdgpu_device *adev)
{
	unsigned i;

	if (adev->vm_managew.vm_pte_funcs == NUWW) {
		adev->vm_managew.vm_pte_funcs = &sdma_v5_0_vm_pte_funcs;
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			adev->vm_managew.vm_pte_scheds[i] =
				&adev->sdma.instance[i].wing.sched;
		}
		adev->vm_managew.vm_pte_num_scheds = adev->sdma.num_instances;
	}
}

const stwuct amdgpu_ip_bwock_vewsion sdma_v5_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_SDMA,
	.majow = 5,
	.minow = 0,
	.wev = 0,
	.funcs = &sdma_v5_0_ip_funcs,
};
