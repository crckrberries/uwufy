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
#incwude <winux/pci.h>

#incwude <dwm/dwm_cache.h>
#incwude "amdgpu.h"
#incwude "gmc_v8_0.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_gem.h"

#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "oss/oss_3_0_d.h"
#incwude "oss/oss_3_0_sh_mask.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#incwude "vid.h"
#incwude "vi.h"

#incwude "amdgpu_atombios.h"

#incwude "ivswcid/ivswcid_viswands30.h"

static void gmc_v8_0_set_gmc_funcs(stwuct amdgpu_device *adev);
static void gmc_v8_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int gmc_v8_0_wait_fow_idwe(void *handwe);

MODUWE_FIWMWAWE("amdgpu/tonga_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_32_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_k_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_k_mc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_k_mc.bin");

static const u32 gowden_settings_tonga_a11[] = {
	mmMC_AWB_WTM_GWPWT_WD, 0x00000003, 0x00000000,
	mmMC_HUB_WDWEQ_DMIF_WIMIT, 0x0000007f, 0x00000028,
	mmMC_HUB_WDP_UMC, 0x00007fb6, 0x00000991,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 tonga_mgcg_cgcg_init[] = {
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104
};

static const u32 gowden_settings_fiji_a10[] = {
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 fiji_mgcg_cgcg_init[] = {
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104
};

static const u32 gowden_settings_powawis11_a11[] = {
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff
};

static const u32 gowden_settings_powawis10_a11[] = {
	mmMC_AWB_WTM_GWPWT_WD, 0x00000003, 0x00000000,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff
};

static const u32 cz_mgcg_cgcg_init[] = {
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104
};

static const u32 stoney_mgcg_cgcg_init[] = {
	mmATC_MISC_CG, 0xffffffff, 0x000c0200,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104
};

static const u32 gowden_settings_stoney_common[] = {
	mmMC_HUB_WDWEQ_UVD, MC_HUB_WDWEQ_UVD__PWESCAWE_MASK, 0x00000004,
	mmMC_WD_GWP_OTH, MC_WD_GWP_OTH__UVD_MASK, 0x00600000
};

static void gmc_v8_0_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							fiji_mgcg_cgcg_init,
							AWWAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_fiji_a10,
							AWWAY_SIZE(gowden_settings_fiji_a10));
		bweak;
	case CHIP_TONGA:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tonga_mgcg_cgcg_init,
							AWWAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_tonga_a11,
							AWWAY_SIZE(gowden_settings_tonga_a11));
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_powawis11_a11,
							AWWAY_SIZE(gowden_settings_powawis11_a11));
		bweak;
	case CHIP_POWAWIS10:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_powawis10_a11,
							AWWAY_SIZE(gowden_settings_powawis10_a11));
		bweak;
	case CHIP_CAWWIZO:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							cz_mgcg_cgcg_init,
							AWWAY_SIZE(cz_mgcg_cgcg_init));
		bweak;
	case CHIP_STONEY:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							stoney_mgcg_cgcg_init,
							AWWAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_stoney_common,
							AWWAY_SIZE(gowden_settings_stoney_common));
		bweak;
	defauwt:
		bweak;
	}
}

static void gmc_v8_0_mc_stop(stwuct amdgpu_device *adev)
{
	u32 bwackout;

	gmc_v8_0_wait_fow_idwe(adev);

	bwackout = WWEG32(mmMC_SHAWED_BWACKOUT_CNTW);
	if (WEG_GET_FIEWD(bwackout, MC_SHAWED_BWACKOUT_CNTW, BWACKOUT_MODE) != 1) {
		/* Bwock CPU access */
		WWEG32(mmBIF_FB_EN, 0);
		/* bwackout the MC */
		bwackout = WEG_SET_FIEWD(bwackout,
					 MC_SHAWED_BWACKOUT_CNTW, BWACKOUT_MODE, 1);
		WWEG32(mmMC_SHAWED_BWACKOUT_CNTW, bwackout);
	}
	/* wait fow the MC to settwe */
	udeway(100);
}

static void gmc_v8_0_mc_wesume(stwuct amdgpu_device *adev)
{
	u32 tmp;

	/* unbwackout the MC */
	tmp = WWEG32(mmMC_SHAWED_BWACKOUT_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MC_SHAWED_BWACKOUT_CNTW, BWACKOUT_MODE, 0);
	WWEG32(mmMC_SHAWED_BWACKOUT_CNTW, tmp);
	/* awwow CPU access */
	tmp = WEG_SET_FIEWD(0, BIF_FB_EN, FB_WEAD_EN, 1);
	tmp = WEG_SET_FIEWD(tmp, BIF_FB_EN, FB_WWITE_EN, 1);
	WWEG32(mmBIF_FB_EN, tmp);
}

/**
 * gmc_v8_0_init_micwocode - woad ucode images fwom disk
 *
 * @adev: amdgpu_device pointew
 *
 * Use the fiwmwawe intewface to woad the ucode images into
 * the dwivew (not woaded into hw).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int gmc_v8_0_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[30];
	int eww;

	DWM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TONGA:
		chip_name = "tonga";
		bweak;
	case CHIP_POWAWIS11:
		if (ASICID_IS_P21(adev->pdev->device, adev->pdev->wevision) ||
		    ASICID_IS_P31(adev->pdev->device, adev->pdev->wevision))
			chip_name = "powawis11_k";
		ewse
			chip_name = "powawis11";
		bweak;
	case CHIP_POWAWIS10:
		if (ASICID_IS_P30(adev->pdev->device, adev->pdev->wevision))
			chip_name = "powawis10_k";
		ewse
			chip_name = "powawis10";
		bweak;
	case CHIP_POWAWIS12:
		if (ASICID_IS_P23(adev->pdev->device, adev->pdev->wevision)) {
			chip_name = "powawis12_k";
		} ewse {
			WWEG32(mmMC_SEQ_IO_DEBUG_INDEX, ixMC_IO_DEBUG_UP_159);
			/* Powawis12 32bit ASIC needs a speciaw MC fiwmwawe */
			if (WWEG32(mmMC_SEQ_IO_DEBUG_DATA) == 0x05b4dc40)
				chip_name = "powawis12_32";
			ewse
				chip_name = "powawis12";
		}
		bweak;
	case CHIP_FIJI:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
	case CHIP_VEGAM:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mc.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gmc.fw, fw_name);
	if (eww) {
		pw_eww("mc: Faiwed to woad fiwmwawe \"%s\"\n", fw_name);
		amdgpu_ucode_wewease(&adev->gmc.fw);
	}
	wetuwn eww;
}

/**
 * gmc_v8_0_tonga_mc_woad_micwocode - woad tonga MC ucode into the hw
 *
 * @adev: amdgpu_device pointew
 *
 * Woad the GDDW MC ucode into the hw (VI).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int gmc_v8_0_tonga_mc_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct mc_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data = NUWW;
	const __we32 *io_mc_wegs = NUWW;
	u32 wunning;
	int i, ucode_size, wegs_size;

	/* Skip MC ucode woading on SW-IOV capabwe boawds.
	 * vbios does this fow us in asic_init in that case.
	 * Skip MC ucode woading on VF, because hypewvisow wiww do that
	 * fow this adaptow.
	 */
	if (amdgpu_swiov_bios(adev))
		wetuwn 0;

	if (!adev->gmc.fw)
		wetuwn -EINVAW;

	hdw = (const stwuct mc_fiwmwawe_headew_v1_0 *)adev->gmc.fw->data;
	amdgpu_ucode_pwint_mc_hdw(&hdw->headew);

	adev->gmc.fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
	wegs_size = we32_to_cpu(hdw->io_debug_size_bytes) / (4 * 2);
	io_mc_wegs = (const __we32 *)
		(adev->gmc.fw->data + we32_to_cpu(hdw->io_debug_awway_offset_bytes));
	ucode_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
	fw_data = (const __we32 *)
		(adev->gmc.fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));

	wunning = WEG_GET_FIEWD(WWEG32(mmMC_SEQ_SUP_CNTW), MC_SEQ_SUP_CNTW, WUN);

	if (wunning == 0) {
		/* weset the engine and set to wwitabwe */
		WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000008);
		WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000010);

		/* woad mc io wegs */
		fow (i = 0; i < wegs_size; i++) {
			WWEG32(mmMC_SEQ_IO_DEBUG_INDEX, we32_to_cpup(io_mc_wegs++));
			WWEG32(mmMC_SEQ_IO_DEBUG_DATA, we32_to_cpup(io_mc_wegs++));
		}
		/* woad the MC ucode */
		fow (i = 0; i < ucode_size; i++)
			WWEG32(mmMC_SEQ_SUP_PGM, we32_to_cpup(fw_data++));

		/* put the engine back into the active state */
		WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000008);
		WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000004);
		WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000001);

		/* wait fow twaining to compwete */
		fow (i = 0; i < adev->usec_timeout; i++) {
			if (WEG_GET_FIEWD(WWEG32(mmMC_SEQ_TWAIN_WAKEUP_CNTW),
					  MC_SEQ_TWAIN_WAKEUP_CNTW, TWAIN_DONE_D0))
				bweak;
			udeway(1);
		}
		fow (i = 0; i < adev->usec_timeout; i++) {
			if (WEG_GET_FIEWD(WWEG32(mmMC_SEQ_TWAIN_WAKEUP_CNTW),
					  MC_SEQ_TWAIN_WAKEUP_CNTW, TWAIN_DONE_D1))
				bweak;
			udeway(1);
		}
	}

	wetuwn 0;
}

static int gmc_v8_0_powawis_mc_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct mc_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data = NUWW;
	const __we32 *io_mc_wegs = NUWW;
	u32 data;
	int i, ucode_size, wegs_size;

	/* Skip MC ucode woading on SW-IOV capabwe boawds.
	 * vbios does this fow us in asic_init in that case.
	 * Skip MC ucode woading on VF, because hypewvisow wiww do that
	 * fow this adaptow.
	 */
	if (amdgpu_swiov_bios(adev))
		wetuwn 0;

	if (!adev->gmc.fw)
		wetuwn -EINVAW;

	hdw = (const stwuct mc_fiwmwawe_headew_v1_0 *)adev->gmc.fw->data;
	amdgpu_ucode_pwint_mc_hdw(&hdw->headew);

	adev->gmc.fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
	wegs_size = we32_to_cpu(hdw->io_debug_size_bytes) / (4 * 2);
	io_mc_wegs = (const __we32 *)
		(adev->gmc.fw->data + we32_to_cpu(hdw->io_debug_awway_offset_bytes));
	ucode_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
	fw_data = (const __we32 *)
		(adev->gmc.fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));

	data = WWEG32(mmMC_SEQ_MISC0);
	data &= ~(0x40);
	WWEG32(mmMC_SEQ_MISC0, data);

	/* woad mc io wegs */
	fow (i = 0; i < wegs_size; i++) {
		WWEG32(mmMC_SEQ_IO_DEBUG_INDEX, we32_to_cpup(io_mc_wegs++));
		WWEG32(mmMC_SEQ_IO_DEBUG_DATA, we32_to_cpup(io_mc_wegs++));
	}

	WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000008);
	WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000010);

	/* woad the MC ucode */
	fow (i = 0; i < ucode_size; i++)
		WWEG32(mmMC_SEQ_SUP_PGM, we32_to_cpup(fw_data++));

	/* put the engine back into the active state */
	WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000008);
	WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000004);
	WWEG32(mmMC_SEQ_SUP_CNTW, 0x00000001);

	/* wait fow twaining to compwete */
	fow (i = 0; i < adev->usec_timeout; i++) {
		data = WWEG32(mmMC_SEQ_MISC0);
		if (data & 0x80)
			bweak;
		udeway(1);
	}

	wetuwn 0;
}

static void gmc_v8_0_vwam_gtt_wocation(stwuct amdgpu_device *adev,
				       stwuct amdgpu_gmc *mc)
{
	u64 base = 0;

	if (!amdgpu_swiov_vf(adev))
		base = WWEG32(mmMC_VM_FB_WOCATION) & 0xFFFF;
	base <<= 24;

	amdgpu_gmc_set_agp_defauwt(adev, mc);
	amdgpu_gmc_vwam_wocation(adev, mc, base);
	amdgpu_gmc_gawt_wocation(adev, mc, AMDGPU_GAWT_PWACEMENT_BEST_FIT);
}

/**
 * gmc_v8_0_mc_pwogwam - pwogwam the GPU memowy contwowwew
 *
 * @adev: amdgpu_device pointew
 *
 * Set the wocation of vwam, gawt, and AGP in the GPU's
 * physicaw addwess space (VI).
 */
static void gmc_v8_0_mc_pwogwam(stwuct amdgpu_device *adev)
{
	u32 tmp;
	int i, j;

	/* Initiawize HDP */
	fow (i = 0, j = 0; i < 32; i++, j += 0x6) {
		WWEG32((0xb05 + j), 0x00000000);
		WWEG32((0xb06 + j), 0x00000000);
		WWEG32((0xb07 + j), 0x00000000);
		WWEG32((0xb08 + j), 0x00000000);
		WWEG32((0xb09 + j), 0x00000000);
	}
	WWEG32(mmHDP_WEG_COHEWENCY_FWUSH_CNTW, 0);

	if (gmc_v8_0_wait_fow_idwe((void *)adev))
		dev_wawn(adev->dev, "Wait fow MC idwe timedout !\n");

	if (adev->mode_info.num_cwtc) {
		/* Wockout access thwough VGA apewtuwe*/
		tmp = WWEG32(mmVGA_HDP_CONTWOW);
		tmp = WEG_SET_FIEWD(tmp, VGA_HDP_CONTWOW, VGA_MEMOWY_DISABWE, 1);
		WWEG32(mmVGA_HDP_CONTWOW, tmp);

		/* disabwe VGA wendew */
		tmp = WWEG32(mmVGA_WENDEW_CONTWOW);
		tmp = WEG_SET_FIEWD(tmp, VGA_WENDEW_CONTWOW, VGA_VSTATUS_CNTW, 0);
		WWEG32(mmVGA_WENDEW_CONTWOW, tmp);
	}
	/* Update configuwation */
	WWEG32(mmMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
	       adev->gmc.vwam_stawt >> 12);
	WWEG32(mmMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
	       adev->gmc.vwam_end >> 12);
	WWEG32(mmMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW,
	       adev->mem_scwatch.gpu_addw >> 12);

	if (amdgpu_swiov_vf(adev)) {
		tmp = ((adev->gmc.vwam_end >> 24) & 0xFFFF) << 16;
		tmp |= ((adev->gmc.vwam_stawt >> 24) & 0xFFFF);
		WWEG32(mmMC_VM_FB_WOCATION, tmp);
		/* XXX doubwe check these! */
		WWEG32(mmHDP_NONSUWFACE_BASE, (adev->gmc.vwam_stawt >> 8));
		WWEG32(mmHDP_NONSUWFACE_INFO, (2 << 7) | (1 << 30));
		WWEG32(mmHDP_NONSUWFACE_SIZE, 0x3FFFFFFF);
	}

	WWEG32(mmMC_VM_AGP_BASE, 0);
	WWEG32(mmMC_VM_AGP_TOP, adev->gmc.agp_end >> 22);
	WWEG32(mmMC_VM_AGP_BOT, adev->gmc.agp_stawt >> 22);
	if (gmc_v8_0_wait_fow_idwe((void *)adev))
		dev_wawn(adev->dev, "Wait fow MC idwe timedout !\n");

	WWEG32(mmBIF_FB_EN, BIF_FB_EN__FB_WEAD_EN_MASK | BIF_FB_EN__FB_WWITE_EN_MASK);

	tmp = WWEG32(mmHDP_MISC_CNTW);
	tmp = WEG_SET_FIEWD(tmp, HDP_MISC_CNTW, FWUSH_INVAWIDATE_CACHE, 0);
	WWEG32(mmHDP_MISC_CNTW, tmp);

	tmp = WWEG32(mmHDP_HOST_PATH_CNTW);
	WWEG32(mmHDP_HOST_PATH_CNTW, tmp);
}

/**
 * gmc_v8_0_mc_init - initiawize the memowy contwowwew dwivew pawams
 *
 * @adev: amdgpu_device pointew
 *
 * Wook up the amount of vwam, vwam width, and decide how to pwace
 * vwam and gawt within the GPU's physicaw addwess space (VI).
 * Wetuwns 0 fow success.
 */
static int gmc_v8_0_mc_init(stwuct amdgpu_device *adev)
{
	int w;
	u32 tmp;

	adev->gmc.vwam_width = amdgpu_atombios_get_vwam_width(adev);
	if (!adev->gmc.vwam_width) {
		int chansize, numchan;

		/* Get VWAM infowmations */
		tmp = WWEG32(mmMC_AWB_WAMCFG);
		if (WEG_GET_FIEWD(tmp, MC_AWB_WAMCFG, CHANSIZE))
			chansize = 64;
		ewse
			chansize = 32;

		tmp = WWEG32(mmMC_SHAWED_CHMAP);
		switch (WEG_GET_FIEWD(tmp, MC_SHAWED_CHMAP, NOOFCHAN)) {
		case 0:
		defauwt:
			numchan = 1;
			bweak;
		case 1:
			numchan = 2;
			bweak;
		case 2:
			numchan = 4;
			bweak;
		case 3:
			numchan = 8;
			bweak;
		case 4:
			numchan = 3;
			bweak;
		case 5:
			numchan = 6;
			bweak;
		case 6:
			numchan = 10;
			bweak;
		case 7:
			numchan = 12;
			bweak;
		case 8:
			numchan = 16;
			bweak;
		}
		adev->gmc.vwam_width = numchan * chansize;
	}
	/* size in MB on si */
	tmp = WWEG32(mmCONFIG_MEMSIZE);
	/* some boawds may have gawbage in the uppew 16 bits */
	if (tmp & 0xffff0000) {
		DWM_INFO("Pwobabwe bad vwam size: 0x%08x\n", tmp);
		if (tmp & 0xffff)
			tmp &= 0xffff;
	}
	adev->gmc.mc_vwam_size = tmp * 1024UWW * 1024UWW;
	adev->gmc.weaw_vwam_size = adev->gmc.mc_vwam_size;

	if (!(adev->fwags & AMD_IS_APU)) {
		w = amdgpu_device_wesize_fb_baw(adev);
		if (w)
			wetuwn w;
	}
	adev->gmc.apew_base = pci_wesouwce_stawt(adev->pdev, 0);
	adev->gmc.apew_size = pci_wesouwce_wen(adev->pdev, 0);

#ifdef CONFIG_X86_64
	if ((adev->fwags & AMD_IS_APU) && !amdgpu_passthwough(adev)) {
		adev->gmc.apew_base = ((u64)WWEG32(mmMC_VM_FB_OFFSET)) << 22;
		adev->gmc.apew_size = adev->gmc.weaw_vwam_size;
	}
#endif

	adev->gmc.visibwe_vwam_size = adev->gmc.apew_size;

	/* set the gawt size */
	if (amdgpu_gawt_size == -1) {
		switch (adev->asic_type) {
		case CHIP_POWAWIS10: /* aww engines suppowt GPUVM */
		case CHIP_POWAWIS11: /* aww engines suppowt GPUVM */
		case CHIP_POWAWIS12: /* aww engines suppowt GPUVM */
		case CHIP_VEGAM:     /* aww engines suppowt GPUVM */
		defauwt:
			adev->gmc.gawt_size = 256UWW << 20;
			bweak;
		case CHIP_TONGA:   /* UVD, VCE do not suppowt GPUVM */
		case CHIP_FIJI:    /* UVD, VCE do not suppowt GPUVM */
		case CHIP_CAWWIZO: /* UVD, VCE do not suppowt GPUVM, DCE SG suppowt */
		case CHIP_STONEY:  /* UVD does not suppowt GPUVM, DCE SG suppowt */
			adev->gmc.gawt_size = 1024UWW << 20;
			bweak;
		}
	} ewse {
		adev->gmc.gawt_size = (u64)amdgpu_gawt_size << 20;
	}

	adev->gmc.gawt_size += adev->pm.smu_pwv_buffew_size;
	gmc_v8_0_vwam_gtt_wocation(adev, &adev->gmc);

	wetuwn 0;
}

/**
 * gmc_v8_0_fwush_gpu_twb_pasid - twb fwush via pasid
 *
 * @adev: amdgpu_device pointew
 * @pasid: pasid to be fwush
 * @fwush_type: type of fwush
 * @aww_hub: fwush aww hubs
 * @inst: is used to sewect which instance of KIQ to use fow the invawidation
 *
 * Fwush the TWB fow the wequested pasid.
 */
static void gmc_v8_0_fwush_gpu_twb_pasid(stwuct amdgpu_device *adev,
					 uint16_t pasid, uint32_t fwush_type,
					 boow aww_hub, uint32_t inst)
{
	u32 mask = 0x0;
	int vmid;

	fow (vmid = 1; vmid < 16; vmid++) {
		u32 tmp = WWEG32(mmATC_VMID0_PASID_MAPPING + vmid);

		if ((tmp & ATC_VMID0_PASID_MAPPING__VAWID_MASK) &&
		    (tmp & ATC_VMID0_PASID_MAPPING__PASID_MASK) == pasid)
			mask |= 1 << vmid;
	}

	WWEG32(mmVM_INVAWIDATE_WEQUEST, mask);
	WWEG32(mmVM_INVAWIDATE_WESPONSE);
}

/*
 * GAWT
 * VMID 0 is the physicaw GPU addwesses as used by the kewnew.
 * VMIDs 1-15 awe used fow usewspace cwients and awe handwed
 * by the amdgpu vm/hsa code.
 */

/**
 * gmc_v8_0_fwush_gpu_twb - gawt twb fwush cawwback
 *
 * @adev: amdgpu_device pointew
 * @vmid: vm instance to fwush
 * @vmhub: which hub to fwush
 * @fwush_type: type of fwush
 *
 * Fwush the TWB fow the wequested page tabwe (VI).
 */
static void gmc_v8_0_fwush_gpu_twb(stwuct amdgpu_device *adev, uint32_t vmid,
					uint32_t vmhub, uint32_t fwush_type)
{
	/* bits 0-15 awe the VM contexts0-15 */
	WWEG32(mmVM_INVAWIDATE_WEQUEST, 1 << vmid);
}

static uint64_t gmc_v8_0_emit_fwush_gpu_twb(stwuct amdgpu_wing *wing,
					    unsigned int vmid, uint64_t pd_addw)
{
	uint32_t weg;

	if (vmid < 8)
		weg = mmVM_CONTEXT0_PAGE_TABWE_BASE_ADDW + vmid;
	ewse
		weg = mmVM_CONTEXT8_PAGE_TABWE_BASE_ADDW + vmid - 8;
	amdgpu_wing_emit_wweg(wing, weg, pd_addw >> 12);

	/* bits 0-15 awe the VM contexts0-15 */
	amdgpu_wing_emit_wweg(wing, mmVM_INVAWIDATE_WEQUEST, 1 << vmid);

	wetuwn pd_addw;
}

static void gmc_v8_0_emit_pasid_mapping(stwuct amdgpu_wing *wing, unsigned int vmid,
					unsigned int pasid)
{
	amdgpu_wing_emit_wweg(wing, mmIH_VMID_0_WUT + vmid, pasid);
}

/*
 * PTE fowmat on VI:
 * 63:40 wesewved
 * 39:12 4k physicaw page base addwess
 * 11:7 fwagment
 * 6 wwite
 * 5 wead
 * 4 exe
 * 3 wesewved
 * 2 snooped
 * 1 system
 * 0 vawid
 *
 * PDE fowmat on VI:
 * 63:59 bwock fwagment size
 * 58:40 wesewved
 * 39:1 physicaw base addwess of PTE
 * bits 5:1 must be 0.
 * 0 vawid
 */

static void gmc_v8_0_get_vm_pde(stwuct amdgpu_device *adev, int wevew,
				uint64_t *addw, uint64_t *fwags)
{
	BUG_ON(*addw & 0xFFFFFF0000000FFFUWW);
}

static void gmc_v8_0_get_vm_pte(stwuct amdgpu_device *adev,
				stwuct amdgpu_bo_va_mapping *mapping,
				uint64_t *fwags)
{
	*fwags &= ~AMDGPU_PTE_EXECUTABWE;
	*fwags |= mapping->fwags & AMDGPU_PTE_EXECUTABWE;
	*fwags &= ~AMDGPU_PTE_PWT;
}

/**
 * gmc_v8_0_set_fauwt_enabwe_defauwt - update VM fauwt handwing
 *
 * @adev: amdgpu_device pointew
 * @vawue: twue wediwects VM fauwts to the defauwt page
 */
static void gmc_v8_0_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev,
					      boow vawue)
{
	u32 tmp;

	tmp = WWEG32(mmVM_CONTEXT1_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
			    EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	WWEG32(mmVM_CONTEXT1_CNTW, tmp);
}

/**
 * gmc_v8_0_set_pwt() - set PWT VM fauwt
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe VM fauwt handwing fow PWT
 */
static void gmc_v8_0_set_pwt(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 tmp;

	if (enabwe && !adev->gmc.pwt_wawning) {
		dev_wawn(adev->dev, "Disabwing VM fauwts because of PWT wequest!\n");
		adev->gmc.pwt_wawning = twue;
	}

	tmp = WWEG32(mmVM_PWT_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    CB_DISABWE_WEAD_FAUWT_ON_UNMAPPED_ACCESS, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    CB_DISABWE_WWITE_FAUWT_ON_UNMAPPED_ACCESS, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    TC_DISABWE_WEAD_FAUWT_ON_UNMAPPED_ACCESS, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    TC_DISABWE_WWITE_FAUWT_ON_UNMAPPED_ACCESS, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    W2_CACHE_STOWE_INVAWID_ENTWIES, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    W1_TWB_STOWE_INVAWID_ENTWIES, enabwe);
	tmp = WEG_SET_FIEWD(tmp, VM_PWT_CNTW,
			    MASK_PDE0_FAUWT, enabwe);
	WWEG32(mmVM_PWT_CNTW, tmp);

	if (enabwe) {
		uint32_t wow = AMDGPU_VA_WESEWVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT;
		uint32_t high = adev->vm_managew.max_pfn -
			(AMDGPU_VA_WESEWVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT);

		WWEG32(mmVM_PWT_APEWTUWE0_WOW_ADDW, wow);
		WWEG32(mmVM_PWT_APEWTUWE1_WOW_ADDW, wow);
		WWEG32(mmVM_PWT_APEWTUWE2_WOW_ADDW, wow);
		WWEG32(mmVM_PWT_APEWTUWE3_WOW_ADDW, wow);
		WWEG32(mmVM_PWT_APEWTUWE0_HIGH_ADDW, high);
		WWEG32(mmVM_PWT_APEWTUWE1_HIGH_ADDW, high);
		WWEG32(mmVM_PWT_APEWTUWE2_HIGH_ADDW, high);
		WWEG32(mmVM_PWT_APEWTUWE3_HIGH_ADDW, high);
	} ewse {
		WWEG32(mmVM_PWT_APEWTUWE0_WOW_ADDW, 0xfffffff);
		WWEG32(mmVM_PWT_APEWTUWE1_WOW_ADDW, 0xfffffff);
		WWEG32(mmVM_PWT_APEWTUWE2_WOW_ADDW, 0xfffffff);
		WWEG32(mmVM_PWT_APEWTUWE3_WOW_ADDW, 0xfffffff);
		WWEG32(mmVM_PWT_APEWTUWE0_HIGH_ADDW, 0x0);
		WWEG32(mmVM_PWT_APEWTUWE1_HIGH_ADDW, 0x0);
		WWEG32(mmVM_PWT_APEWTUWE2_HIGH_ADDW, 0x0);
		WWEG32(mmVM_PWT_APEWTUWE3_HIGH_ADDW, 0x0);
	}
}

/**
 * gmc_v8_0_gawt_enabwe - gawt enabwe
 *
 * @adev: amdgpu_device pointew
 *
 * This sets up the TWBs, pwogwams the page tabwes fow VMID0,
 * sets up the hw fow VMIDs 1-15 which awe awwocated on
 * demand, and sets up the gwobaw wocations fow the WDS, GDS,
 * and GPUVM fow FSA64 cwients (VI).
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
static int gmc_v8_0_gawt_enabwe(stwuct amdgpu_device *adev)
{
	uint64_t tabwe_addw;
	u32 tmp, fiewd;
	int i;

	if (adev->gawt.bo == NUWW) {
		dev_eww(adev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	amdgpu_gtt_mgw_wecovew(&adev->mman.gtt_mgw);
	tabwe_addw = amdgpu_bo_gpu_offset(adev->gawt.bo);

	/* Setup TWB contwow */
	tmp = WWEG32(mmMC_VM_MX_W1_TWB_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 1);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_FWAGMENT_PWOCESSING, 1);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, SYSTEM_ACCESS_MODE, 3);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_ADVANCED_DWIVEW_MODEW, 1);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, SYSTEM_APEWTUWE_UNMAPPED_ACCESS, 0);
	WWEG32(mmMC_VM_MX_W1_TWB_CNTW, tmp);
	/* Setup W2 cache */
	tmp = WWEG32(mmVM_W2_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, EFFECTIVE_W2_QUEUE_SIZE, 7);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_DEFAUWT_PAGE_OUT_TO_SYSTEM_MEMOWY, 1);
	WWEG32(mmVM_W2_CNTW, tmp);
	tmp = WWEG32(mmVM_W2_CNTW2);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_W2_CACHE, 1);
	WWEG32(mmVM_W2_CNTW2, tmp);

	fiewd = adev->vm_managew.fwagment_size;
	tmp = WWEG32(mmVM_W2_CNTW3);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3, W2_CACHE_BIGK_ASSOCIATIVITY, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3, BANK_SEWECT, fiewd);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3, W2_CACHE_BIGK_FWAGMENT_SIZE, fiewd);
	WWEG32(mmVM_W2_CNTW3, tmp);
	/* XXX: set to enabwe PTE/PDE in system memowy */
	tmp = WWEG32(mmVM_W2_CNTW4);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PDE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PDE_WEQUEST_SHAWED, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PDE_WEQUEST_SNOOP, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PTE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PTE_WEQUEST_SHAWED, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT0_PTE_WEQUEST_SNOOP, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PDE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PDE_WEQUEST_SHAWED, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PDE_WEQUEST_SNOOP, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PTE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PTE_WEQUEST_SHAWED, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_CONTEXT1_PTE_WEQUEST_SNOOP, 0);
	WWEG32(mmVM_W2_CNTW4, tmp);
	/* setup context0 */
	WWEG32(mmVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW, adev->gmc.gawt_stawt >> 12);
	WWEG32(mmVM_CONTEXT0_PAGE_TABWE_END_ADDW, adev->gmc.gawt_end >> 12);
	WWEG32(mmVM_CONTEXT0_PAGE_TABWE_BASE_ADDW, tabwe_addw >> 12);
	WWEG32(mmVM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW,
			(u32)(adev->dummy_page_addw >> 12));
	WWEG32(mmVM_CONTEXT0_CNTW2, 0);
	tmp = WWEG32(mmVM_CONTEXT0_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, ENABWE_CONTEXT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, PAGE_TABWE_DEPTH, 0);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	WWEG32(mmVM_CONTEXT0_CNTW, tmp);

	WWEG32(mmVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW, 0);
	WWEG32(mmVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW, 0);
	WWEG32(mmVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET, 0);

	/* empty context1-15 */
	/* FIXME stawt with 4G, once using 2 wevew pt switch to fuww
	 * vm size space
	 */
	/* set vm size, must be a muwtipwe of 4 */
	WWEG32(mmVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW, 0);
	WWEG32(mmVM_CONTEXT1_PAGE_TABWE_END_ADDW, adev->vm_managew.max_pfn - 1);
	fow (i = 1; i < AMDGPU_NUM_VMID; i++) {
		if (i < 8)
			WWEG32(mmVM_CONTEXT0_PAGE_TABWE_BASE_ADDW + i,
			       tabwe_addw >> 12);
		ewse
			WWEG32(mmVM_CONTEXT8_PAGE_TABWE_BASE_ADDW + i - 8,
			       tabwe_addw >> 12);
	}

	/* enabwe context1-15 */
	WWEG32(mmVM_CONTEXT1_PWOTECTION_FAUWT_DEFAUWT_ADDW,
	       (u32)(adev->dummy_page_addw >> 12));
	WWEG32(mmVM_CONTEXT1_CNTW2, 4);
	tmp = WWEG32(mmVM_CONTEXT1_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, ENABWE_CONTEXT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, PAGE_TABWE_DEPTH, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
	tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, PAGE_TABWE_BWOCK_SIZE,
			    adev->vm_managew.bwock_size - 9);
	WWEG32(mmVM_CONTEXT1_CNTW, tmp);
	if (amdgpu_vm_fauwt_stop == AMDGPU_VM_FAUWT_STOP_AWWAYS)
		gmc_v8_0_set_fauwt_enabwe_defauwt(adev, fawse);
	ewse
		gmc_v8_0_set_fauwt_enabwe_defauwt(adev, twue);

	gmc_v8_0_fwush_gpu_twb(adev, 0, 0, 0);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned int)(adev->gmc.gawt_size >> 20),
		 (unsigned wong wong)tabwe_addw);
	wetuwn 0;
}

static int gmc_v8_0_gawt_init(stwuct amdgpu_device *adev)
{
	int w;

	if (adev->gawt.bo) {
		WAWN(1, "W600 PCIE GAWT awweady initiawized\n");
		wetuwn 0;
	}
	/* Initiawize common gawt stwuctuwe */
	w = amdgpu_gawt_init(adev);
	if (w)
		wetuwn w;
	adev->gawt.tabwe_size = adev->gawt.num_gpu_pages * 8;
	adev->gawt.gawt_pte_fwags = AMDGPU_PTE_EXECUTABWE;
	wetuwn amdgpu_gawt_tabwe_vwam_awwoc(adev);
}

/**
 * gmc_v8_0_gawt_disabwe - gawt disabwe
 *
 * @adev: amdgpu_device pointew
 *
 * This disabwes aww VM page tabwe (VI).
 */
static void gmc_v8_0_gawt_disabwe(stwuct amdgpu_device *adev)
{
	u32 tmp;

	/* Disabwe aww tabwes */
	WWEG32(mmVM_CONTEXT0_CNTW, 0);
	WWEG32(mmVM_CONTEXT1_CNTW, 0);
	/* Setup TWB contwow */
	tmp = WWEG32(mmMC_VM_MX_W1_TWB_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 0);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_FWAGMENT_PWOCESSING, 0);
	tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_ADVANCED_DWIVEW_MODEW, 0);
	WWEG32(mmMC_VM_MX_W1_TWB_CNTW, tmp);
	/* Setup W2 cache */
	tmp = WWEG32(mmVM_W2_CNTW);
	tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE, 0);
	WWEG32(mmVM_W2_CNTW, tmp);
	WWEG32(mmVM_W2_CNTW2, 0);
}

/**
 * gmc_v8_0_vm_decode_fauwt - pwint human weadabwe fauwt info
 *
 * @adev: amdgpu_device pointew
 * @status: VM_CONTEXT1_PWOTECTION_FAUWT_STATUS wegistew vawue
 * @addw: VM_CONTEXT1_PWOTECTION_FAUWT_ADDW wegistew vawue
 * @mc_cwient: VM_CONTEXT1_PWOTECTION_FAUWT_MCCWIENT wegistew vawue
 * @pasid: debug wogging onwy - no functionaw use
 *
 * Pwint human weadabwe fauwt infowmation (VI).
 */
static void gmc_v8_0_vm_decode_fauwt(stwuct amdgpu_device *adev, u32 status,
				     u32 addw, u32 mc_cwient, unsigned int pasid)
{
	u32 vmid = WEG_GET_FIEWD(status, VM_CONTEXT1_PWOTECTION_FAUWT_STATUS, VMID);
	u32 pwotections = WEG_GET_FIEWD(status, VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
					PWOTECTIONS);
	chaw bwock[5] = { mc_cwient >> 24, (mc_cwient >> 16) & 0xff,
		(mc_cwient >> 8) & 0xff, mc_cwient & 0xff, 0 };
	u32 mc_id;

	mc_id = WEG_GET_FIEWD(status, VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
			      MEMOWY_CWIENT_ID);

	dev_eww(adev->dev, "VM fauwt (0x%02x, vmid %d, pasid %d) at page %u, %s fwom '%s' (0x%08x) (%d)\n",
	       pwotections, vmid, pasid, addw,
	       WEG_GET_FIEWD(status, VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
			     MEMOWY_CWIENT_WW) ?
	       "wwite" : "wead", bwock, mc_cwient, mc_id);
}

static int gmc_v8_0_convewt_vwam_type(int mc_seq_vwam_type)
{
	switch (mc_seq_vwam_type) {
	case MC_SEQ_MISC0__MT__GDDW1:
		wetuwn AMDGPU_VWAM_TYPE_GDDW1;
	case MC_SEQ_MISC0__MT__DDW2:
		wetuwn AMDGPU_VWAM_TYPE_DDW2;
	case MC_SEQ_MISC0__MT__GDDW3:
		wetuwn AMDGPU_VWAM_TYPE_GDDW3;
	case MC_SEQ_MISC0__MT__GDDW4:
		wetuwn AMDGPU_VWAM_TYPE_GDDW4;
	case MC_SEQ_MISC0__MT__GDDW5:
		wetuwn AMDGPU_VWAM_TYPE_GDDW5;
	case MC_SEQ_MISC0__MT__HBM:
		wetuwn AMDGPU_VWAM_TYPE_HBM;
	case MC_SEQ_MISC0__MT__DDW3:
		wetuwn AMDGPU_VWAM_TYPE_DDW3;
	defauwt:
		wetuwn AMDGPU_VWAM_TYPE_UNKNOWN;
	}
}

static int gmc_v8_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	gmc_v8_0_set_gmc_funcs(adev);
	gmc_v8_0_set_iwq_funcs(adev);

	adev->gmc.shawed_apewtuwe_stawt = 0x2000000000000000UWW;
	adev->gmc.shawed_apewtuwe_end =
		adev->gmc.shawed_apewtuwe_stawt + (4UWW << 30) - 1;
	adev->gmc.pwivate_apewtuwe_stawt =
		adev->gmc.shawed_apewtuwe_end + 1;
	adev->gmc.pwivate_apewtuwe_end =
		adev->gmc.pwivate_apewtuwe_stawt + (4UWW << 30) - 1;
	adev->gmc.nowetwy_fwags = AMDGPU_VM_NOWETWY_FWAGS_TF;

	wetuwn 0;
}

static int gmc_v8_0_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_vm_fauwt_stop != AMDGPU_VM_FAUWT_STOP_AWWAYS)
		wetuwn amdgpu_iwq_get(adev, &adev->gmc.vm_fauwt, 0);
	ewse
		wetuwn 0;
}

static unsigned int gmc_v8_0_get_vbios_fb_size(stwuct amdgpu_device *adev)
{
	u32 d1vga_contwow = WWEG32(mmD1VGA_CONTWOW);
	unsigned int size;

	if (WEG_GET_FIEWD(d1vga_contwow, D1VGA_CONTWOW, D1VGA_MODE_ENABWE)) {
		size = AMDGPU_VBIOS_VGA_AWWOCATION;
	} ewse {
		u32 viewpowt = WWEG32(mmVIEWPOWT_SIZE);

		size = (WEG_GET_FIEWD(viewpowt, VIEWPOWT_SIZE, VIEWPOWT_HEIGHT) *
			WEG_GET_FIEWD(viewpowt, VIEWPOWT_SIZE, VIEWPOWT_WIDTH) *
			4);
	}

	wetuwn size;
}

#define mmMC_SEQ_MISC0_FIJI 0xA71

static int gmc_v8_0_sw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	set_bit(AMDGPU_GFXHUB(0), adev->vmhubs_mask);

	if (adev->fwags & AMD_IS_APU) {
		adev->gmc.vwam_type = AMDGPU_VWAM_TYPE_UNKNOWN;
	} ewse {
		u32 tmp;

		if ((adev->asic_type == CHIP_FIJI) ||
		    (adev->asic_type == CHIP_VEGAM))
			tmp = WWEG32(mmMC_SEQ_MISC0_FIJI);
		ewse
			tmp = WWEG32(mmMC_SEQ_MISC0);
		tmp &= MC_SEQ_MISC0__MT__MASK;
		adev->gmc.vwam_type = gmc_v8_0_convewt_vwam_type(tmp);
	}

	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_GFX_PAGE_INV_FAUWT, &adev->gmc.vm_fauwt);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_GFX_MEM_PWOT_FAUWT, &adev->gmc.vm_fauwt);
	if (w)
		wetuwn w;

	/* Adjust VM size hewe.
	 * Cuwwentwy set to 4GB ((1 << 20) 4k pages).
	 * Max GPUVM size fow cayman and SI is 40 bits.
	 */
	amdgpu_vm_adjust_size(adev, 64, 9, 1, 40);

	/* Set the intewnaw MC addwess mask
	 * This is the max addwess of the GPU's
	 * intewnaw addwess space.
	 */
	adev->gmc.mc_mask = 0xffffffffffUWW; /* 40 bit MC */

	w = dma_set_mask_and_cohewent(adev->dev, DMA_BIT_MASK(40));
	if (w) {
		pw_wawn("No suitabwe DMA avaiwabwe\n");
		wetuwn w;
	}
	adev->need_swiotwb = dwm_need_swiotwb(40);

	w = gmc_v8_0_init_micwocode(adev);
	if (w) {
		DWM_EWWOW("Faiwed to woad mc fiwmwawe!\n");
		wetuwn w;
	}

	w = gmc_v8_0_mc_init(adev);
	if (w)
		wetuwn w;

	amdgpu_gmc_get_vbios_awwocations(adev);

	/* Memowy managew */
	w = amdgpu_bo_init(adev);
	if (w)
		wetuwn w;

	w = gmc_v8_0_gawt_init(adev);
	if (w)
		wetuwn w;

	/*
	 * numbew of VMs
	 * VMID 0 is wesewved fow System
	 * amdgpu gwaphics/compute wiww use VMIDs 1-7
	 * amdkfd wiww use VMIDs 8-15
	 */
	adev->vm_managew.fiwst_kfd_vmid = 8;
	amdgpu_vm_managew_init(adev);

	/* base offset of vwam pages */
	if (adev->fwags & AMD_IS_APU) {
		u64 tmp = WWEG32(mmMC_VM_FB_OFFSET);

		tmp <<= 22;
		adev->vm_managew.vwam_base_offset = tmp;
	} ewse {
		adev->vm_managew.vwam_base_offset = 0;
	}

	adev->gmc.vm_fauwt_info = kmawwoc(sizeof(stwuct kfd_vm_fauwt_info),
					GFP_KEWNEW);
	if (!adev->gmc.vm_fauwt_info)
		wetuwn -ENOMEM;
	atomic_set(&adev->gmc.vm_fauwt_info_updated, 0);

	wetuwn 0;
}

static int gmc_v8_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_gem_fowce_wewease(adev);
	amdgpu_vm_managew_fini(adev);
	kfwee(adev->gmc.vm_fauwt_info);
	amdgpu_gawt_tabwe_vwam_fwee(adev);
	amdgpu_bo_fini(adev);
	amdgpu_ucode_wewease(&adev->gmc.fw);

	wetuwn 0;
}

static int gmc_v8_0_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	gmc_v8_0_init_gowden_wegistews(adev);

	gmc_v8_0_mc_pwogwam(adev);

	if (adev->asic_type == CHIP_TONGA) {
		w = gmc_v8_0_tonga_mc_woad_micwocode(adev);
		if (w) {
			DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
			wetuwn w;
		}
	} ewse if (adev->asic_type == CHIP_POWAWIS11 ||
			adev->asic_type == CHIP_POWAWIS10 ||
			adev->asic_type == CHIP_POWAWIS12) {
		w = gmc_v8_0_powawis_mc_woad_micwocode(adev);
		if (w) {
			DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
			wetuwn w;
		}
	}

	w = gmc_v8_0_gawt_enabwe(adev);
	if (w)
		wetuwn w;

	if (amdgpu_emu_mode == 1)
		wetuwn amdgpu_gmc_vwam_checking(adev);

	wetuwn 0;
}

static int gmc_v8_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_put(adev, &adev->gmc.vm_fauwt, 0);
	gmc_v8_0_gawt_disabwe(adev);

	wetuwn 0;
}

static int gmc_v8_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	gmc_v8_0_hw_fini(adev);

	wetuwn 0;
}

static int gmc_v8_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = gmc_v8_0_hw_init(adev);
	if (w)
		wetuwn w;

	amdgpu_vmid_weset_aww(adev);

	wetuwn 0;
}

static boow gmc_v8_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (tmp & (SWBM_STATUS__MCB_BUSY_MASK | SWBM_STATUS__MCB_NON_DISPWAY_BUSY_MASK |
		   SWBM_STATUS__MCC_BUSY_MASK | SWBM_STATUS__MCD_BUSY_MASK | SWBM_STATUS__VMC_BUSY_MASK))
		wetuwn fawse;

	wetuwn twue;
}

static int gmc_v8_0_wait_fow_idwe(void *handwe)
{
	unsigned int i;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(mmSWBM_STATUS) & (SWBM_STATUS__MCB_BUSY_MASK |
					       SWBM_STATUS__MCB_NON_DISPWAY_BUSY_MASK |
					       SWBM_STATUS__MCC_BUSY_MASK |
					       SWBM_STATUS__MCD_BUSY_MASK |
					       SWBM_STATUS__VMC_BUSY_MASK |
					       SWBM_STATUS__VMC1_BUSY_MASK);
		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;

}

static boow gmc_v8_0_check_soft_weset(void *handwe)
{
	u32 swbm_soft_weset = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (tmp & SWBM_STATUS__VMC_BUSY_MASK)
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
						SWBM_SOFT_WESET, SOFT_WESET_VMC, 1);

	if (tmp & (SWBM_STATUS__MCB_BUSY_MASK | SWBM_STATUS__MCB_NON_DISPWAY_BUSY_MASK |
		   SWBM_STATUS__MCC_BUSY_MASK | SWBM_STATUS__MCD_BUSY_MASK)) {
		if (!(adev->fwags & AMD_IS_APU))
			swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
							SWBM_SOFT_WESET, SOFT_WESET_MC, 1);
	}

	if (swbm_soft_weset) {
		adev->gmc.swbm_soft_weset = swbm_soft_weset;
		wetuwn twue;
	}

	adev->gmc.swbm_soft_weset = 0;

	wetuwn fawse;
}

static int gmc_v8_0_pwe_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->gmc.swbm_soft_weset)
		wetuwn 0;

	gmc_v8_0_mc_stop(adev);
	if (gmc_v8_0_wait_fow_idwe(adev))
		dev_wawn(adev->dev, "Wait fow GMC idwe timed out !\n");

	wetuwn 0;
}

static int gmc_v8_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset;

	if (!adev->gmc.swbm_soft_weset)
		wetuwn 0;
	swbm_soft_weset = adev->gmc.swbm_soft_weset;

	if (swbm_soft_weset) {
		u32 tmp;

		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int gmc_v8_0_post_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->gmc.swbm_soft_weset)
		wetuwn 0;

	gmc_v8_0_mc_wesume(adev);
	wetuwn 0;
}

static int gmc_v8_0_vm_fauwt_intewwupt_state(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *swc,
					     unsigned int type,
					     enum amdgpu_intewwupt_state state)
{
	u32 tmp;
	u32 bits = (VM_CONTEXT1_CNTW__WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		    VM_CONTEXT1_CNTW__EXECUTE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK);

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		/* system context */
		tmp = WWEG32(mmVM_CONTEXT0_CNTW);
		tmp &= ~bits;
		WWEG32(mmVM_CONTEXT0_CNTW, tmp);
		/* VMs */
		tmp = WWEG32(mmVM_CONTEXT1_CNTW);
		tmp &= ~bits;
		WWEG32(mmVM_CONTEXT1_CNTW, tmp);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		/* system context */
		tmp = WWEG32(mmVM_CONTEXT0_CNTW);
		tmp |= bits;
		WWEG32(mmVM_CONTEXT0_CNTW, tmp);
		/* VMs */
		tmp = WWEG32(mmVM_CONTEXT1_CNTW);
		tmp |= bits;
		WWEG32(mmVM_CONTEXT1_CNTW, tmp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int gmc_v8_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	u32 addw, status, mc_cwient, vmid;

	if (amdgpu_swiov_vf(adev)) {
		dev_eww(adev->dev, "GPU fauwt detected: %d 0x%08x\n",
			entwy->swc_id, entwy->swc_data[0]);
		dev_eww(adev->dev, " Can't decode VM fauwt info hewe on SWIOV VF\n");
		wetuwn 0;
	}

	addw = WWEG32(mmVM_CONTEXT1_PWOTECTION_FAUWT_ADDW);
	status = WWEG32(mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS);
	mc_cwient = WWEG32(mmVM_CONTEXT1_PWOTECTION_FAUWT_MCCWIENT);
	/* weset addw and status */
	WWEG32_P(mmVM_CONTEXT1_CNTW2, 1, ~1);

	if (!addw && !status)
		wetuwn 0;

	amdgpu_vm_update_fauwt_cache(adev, entwy->pasid,
				     ((u64)addw) << AMDGPU_GPU_PAGE_SHIFT, status, AMDGPU_GFXHUB(0));

	if (amdgpu_vm_fauwt_stop == AMDGPU_VM_FAUWT_STOP_FIWST)
		gmc_v8_0_set_fauwt_enabwe_defauwt(adev, fawse);

	if (pwintk_watewimit()) {
		stwuct amdgpu_task_info task_info;

		memset(&task_info, 0, sizeof(stwuct amdgpu_task_info));
		amdgpu_vm_get_task_info(adev, entwy->pasid, &task_info);

		dev_eww(adev->dev, "GPU fauwt detected: %d 0x%08x fow pwocess %s pid %d thwead %s pid %d\n",
			entwy->swc_id, entwy->swc_data[0], task_info.pwocess_name,
			task_info.tgid, task_info.task_name, task_info.pid);
		dev_eww(adev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_ADDW   0x%08X\n",
			addw);
		dev_eww(adev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_STATUS 0x%08X\n",
			status);
		gmc_v8_0_vm_decode_fauwt(adev, status, addw, mc_cwient,
					 entwy->pasid);
	}

	vmid = WEG_GET_FIEWD(status, VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
			     VMID);
	if (amdgpu_amdkfd_is_kfd_vmid(adev, vmid)
		&& !atomic_wead(&adev->gmc.vm_fauwt_info_updated)) {
		stwuct kfd_vm_fauwt_info *info = adev->gmc.vm_fauwt_info;
		u32 pwotections = WEG_GET_FIEWD(status,
					VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
					PWOTECTIONS);

		info->vmid = vmid;
		info->mc_id = WEG_GET_FIEWD(status,
					    VM_CONTEXT1_PWOTECTION_FAUWT_STATUS,
					    MEMOWY_CWIENT_ID);
		info->status = status;
		info->page_addw = addw;
		info->pwot_vawid = pwotections & 0x7 ? twue : fawse;
		info->pwot_wead = pwotections & 0x8 ? twue : fawse;
		info->pwot_wwite = pwotections & 0x10 ? twue : fawse;
		info->pwot_exec = pwotections & 0x20 ? twue : fawse;
		mb();
		atomic_set(&adev->gmc.vm_fauwt_info_updated, 1);
	}

	wetuwn 0;
}

static void fiji_update_mc_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						     boow enabwe)
{
	uint32_t data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_MC_MGCG)) {
		data = WWEG32(mmMC_HUB_MISC_HUB_CG);
		data |= MC_HUB_MISC_HUB_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_HUB_CG, data);

		data = WWEG32(mmMC_HUB_MISC_SIP_CG);
		data |= MC_HUB_MISC_SIP_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_SIP_CG, data);

		data = WWEG32(mmMC_HUB_MISC_VM_CG);
		data |= MC_HUB_MISC_VM_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_VM_CG, data);

		data = WWEG32(mmMC_XPB_CWK_GAT);
		data |= MC_XPB_CWK_GAT__ENABWE_MASK;
		WWEG32(mmMC_XPB_CWK_GAT, data);

		data = WWEG32(mmATC_MISC_CG);
		data |= ATC_MISC_CG__ENABWE_MASK;
		WWEG32(mmATC_MISC_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WW_CG);
		data |= MC_CITF_MISC_WW_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WW_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WD_CG);
		data |= MC_CITF_MISC_WD_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WD_CG, data);

		data = WWEG32(mmMC_CITF_MISC_VM_CG);
		data |= MC_CITF_MISC_VM_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_VM_CG, data);

		data = WWEG32(mmVM_W2_CG);
		data |= VM_W2_CG__ENABWE_MASK;
		WWEG32(mmVM_W2_CG, data);
	} ewse {
		data = WWEG32(mmMC_HUB_MISC_HUB_CG);
		data &= ~MC_HUB_MISC_HUB_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_HUB_CG, data);

		data = WWEG32(mmMC_HUB_MISC_SIP_CG);
		data &= ~MC_HUB_MISC_SIP_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_SIP_CG, data);

		data = WWEG32(mmMC_HUB_MISC_VM_CG);
		data &= ~MC_HUB_MISC_VM_CG__ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_VM_CG, data);

		data = WWEG32(mmMC_XPB_CWK_GAT);
		data &= ~MC_XPB_CWK_GAT__ENABWE_MASK;
		WWEG32(mmMC_XPB_CWK_GAT, data);

		data = WWEG32(mmATC_MISC_CG);
		data &= ~ATC_MISC_CG__ENABWE_MASK;
		WWEG32(mmATC_MISC_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WW_CG);
		data &= ~MC_CITF_MISC_WW_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WW_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WD_CG);
		data &= ~MC_CITF_MISC_WD_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WD_CG, data);

		data = WWEG32(mmMC_CITF_MISC_VM_CG);
		data &= ~MC_CITF_MISC_VM_CG__ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_VM_CG, data);

		data = WWEG32(mmVM_W2_CG);
		data &= ~VM_W2_CG__ENABWE_MASK;
		WWEG32(mmVM_W2_CG, data);
	}
}

static void fiji_update_mc_wight_sweep(stwuct amdgpu_device *adev,
				       boow enabwe)
{
	uint32_t data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_MC_WS)) {
		data = WWEG32(mmMC_HUB_MISC_HUB_CG);
		data |= MC_HUB_MISC_HUB_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_HUB_CG, data);

		data = WWEG32(mmMC_HUB_MISC_SIP_CG);
		data |= MC_HUB_MISC_SIP_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_SIP_CG, data);

		data = WWEG32(mmMC_HUB_MISC_VM_CG);
		data |= MC_HUB_MISC_VM_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_VM_CG, data);

		data = WWEG32(mmMC_XPB_CWK_GAT);
		data |= MC_XPB_CWK_GAT__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_XPB_CWK_GAT, data);

		data = WWEG32(mmATC_MISC_CG);
		data |= ATC_MISC_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmATC_MISC_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WW_CG);
		data |= MC_CITF_MISC_WW_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WW_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WD_CG);
		data |= MC_CITF_MISC_WD_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WD_CG, data);

		data = WWEG32(mmMC_CITF_MISC_VM_CG);
		data |= MC_CITF_MISC_VM_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_VM_CG, data);

		data = WWEG32(mmVM_W2_CG);
		data |= VM_W2_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmVM_W2_CG, data);
	} ewse {
		data = WWEG32(mmMC_HUB_MISC_HUB_CG);
		data &= ~MC_HUB_MISC_HUB_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_HUB_CG, data);

		data = WWEG32(mmMC_HUB_MISC_SIP_CG);
		data &= ~MC_HUB_MISC_SIP_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_SIP_CG, data);

		data = WWEG32(mmMC_HUB_MISC_VM_CG);
		data &= ~MC_HUB_MISC_VM_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_HUB_MISC_VM_CG, data);

		data = WWEG32(mmMC_XPB_CWK_GAT);
		data &= ~MC_XPB_CWK_GAT__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_XPB_CWK_GAT, data);

		data = WWEG32(mmATC_MISC_CG);
		data &= ~ATC_MISC_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmATC_MISC_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WW_CG);
		data &= ~MC_CITF_MISC_WW_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WW_CG, data);

		data = WWEG32(mmMC_CITF_MISC_WD_CG);
		data &= ~MC_CITF_MISC_WD_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_WD_CG, data);

		data = WWEG32(mmMC_CITF_MISC_VM_CG);
		data &= ~MC_CITF_MISC_VM_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmMC_CITF_MISC_VM_CG, data);

		data = WWEG32(mmVM_W2_CG);
		data &= ~VM_W2_CG__MEM_WS_ENABWE_MASK;
		WWEG32(mmVM_W2_CG, data);
	}
}

static int gmc_v8_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (adev->asic_type) {
	case CHIP_FIJI:
		fiji_update_mc_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		fiji_update_mc_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int gmc_v8_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static void gmc_v8_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	/* AMD_CG_SUPPOWT_MC_MGCG */
	data = WWEG32(mmMC_HUB_MISC_HUB_CG);
	if (data & MC_HUB_MISC_HUB_CG__ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_MC_MGCG;

	/* AMD_CG_SUPPOWT_MC_WS */
	if (data & MC_HUB_MISC_HUB_CG__MEM_WS_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_MC_WS;
}

static const stwuct amd_ip_funcs gmc_v8_0_ip_funcs = {
	.name = "gmc_v8_0",
	.eawwy_init = gmc_v8_0_eawwy_init,
	.wate_init = gmc_v8_0_wate_init,
	.sw_init = gmc_v8_0_sw_init,
	.sw_fini = gmc_v8_0_sw_fini,
	.hw_init = gmc_v8_0_hw_init,
	.hw_fini = gmc_v8_0_hw_fini,
	.suspend = gmc_v8_0_suspend,
	.wesume = gmc_v8_0_wesume,
	.is_idwe = gmc_v8_0_is_idwe,
	.wait_fow_idwe = gmc_v8_0_wait_fow_idwe,
	.check_soft_weset = gmc_v8_0_check_soft_weset,
	.pwe_soft_weset = gmc_v8_0_pwe_soft_weset,
	.soft_weset = gmc_v8_0_soft_weset,
	.post_soft_weset = gmc_v8_0_post_soft_weset,
	.set_cwockgating_state = gmc_v8_0_set_cwockgating_state,
	.set_powewgating_state = gmc_v8_0_set_powewgating_state,
	.get_cwockgating_state = gmc_v8_0_get_cwockgating_state,
};

static const stwuct amdgpu_gmc_funcs gmc_v8_0_gmc_funcs = {
	.fwush_gpu_twb = gmc_v8_0_fwush_gpu_twb,
	.fwush_gpu_twb_pasid = gmc_v8_0_fwush_gpu_twb_pasid,
	.emit_fwush_gpu_twb = gmc_v8_0_emit_fwush_gpu_twb,
	.emit_pasid_mapping = gmc_v8_0_emit_pasid_mapping,
	.set_pwt = gmc_v8_0_set_pwt,
	.get_vm_pde = gmc_v8_0_get_vm_pde,
	.get_vm_pte = gmc_v8_0_get_vm_pte,
	.get_vbios_fb_size = gmc_v8_0_get_vbios_fb_size,
};

static const stwuct amdgpu_iwq_swc_funcs gmc_v8_0_iwq_funcs = {
	.set = gmc_v8_0_vm_fauwt_intewwupt_state,
	.pwocess = gmc_v8_0_pwocess_intewwupt,
};

static void gmc_v8_0_set_gmc_funcs(stwuct amdgpu_device *adev)
{
	adev->gmc.gmc_funcs = &gmc_v8_0_gmc_funcs;
}

static void gmc_v8_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->gmc.vm_fauwt.num_types = 1;
	adev->gmc.vm_fauwt.funcs = &gmc_v8_0_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion gmc_v8_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GMC,
	.majow = 8,
	.minow = 0,
	.wev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion gmc_v8_1_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GMC,
	.majow = 8,
	.minow = 1,
	.wev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion gmc_v8_5_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GMC,
	.majow = 8,
	.minow = 5,
	.wev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
};
