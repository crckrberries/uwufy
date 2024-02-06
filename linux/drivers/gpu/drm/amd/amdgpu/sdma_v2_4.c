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
 * Authows: Awex Deuchew
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_twace.h"
#incwude "vi.h"
#incwude "vid.h"

#incwude "oss/oss_2_4_d.h"
#incwude "oss/oss_2_4_sh_mask.h"

#incwude "gmc/gmc_7_1_d.h"
#incwude "gmc/gmc_7_1_sh_mask.h"

#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_enum.h"
#incwude "gca/gfx_8_0_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "icewand_sdma_pkt_open.h"

#incwude "ivswcid/ivswcid_viswands30.h"

static void sdma_v2_4_set_wing_funcs(stwuct amdgpu_device *adev);
static void sdma_v2_4_set_buffew_funcs(stwuct amdgpu_device *adev);
static void sdma_v2_4_set_vm_pte_funcs(stwuct amdgpu_device *adev);
static void sdma_v2_4_set_iwq_funcs(stwuct amdgpu_device *adev);

MODUWE_FIWMWAWE("amdgpu/topaz_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_sdma1.bin");

static const u32 sdma_offsets[SDMA_MAX_INSTANCE] =
{
	SDMA0_WEGISTEW_OFFSET,
	SDMA1_WEGISTEW_OFFSET
};

static const u32 gowden_settings_icewand_a11[] =
{
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CWK_CTWW, 0xff000fff, 0x00000000,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CWK_CTWW, 0xff000fff, 0x00000000,
};

static const u32 icewand_mgcg_cgcg_init[] =
{
	mmSDMA0_CWK_CTWW, 0xff000ff0, 0x00000100,
	mmSDMA1_CWK_CTWW, 0xff000ff0, 0x00000100
};

/*
 * sDMA - System DMA
 * Stawting with CIK, the GPU has new asynchwonous
 * DMA engines.  These engines awe used fow compute
 * and gfx.  Thewe awe two DMA engines (SDMA0, SDMA1)
 * and each one suppowts 1 wing buffew used fow gfx
 * and 2 queues used fow compute.
 *
 * The pwogwamming modew is vewy simiwaw to the CP
 * (wing buffew, IBs, etc.), but sDMA has it's own
 * packet fowmat that is diffewent fwom the PM4 fowmat
 * used by the CP. sDMA suppowts copying data, wwiting
 * embedded data, sowid fiwws, and a numbew of othew
 * things.  It awso has suppowt fow tiwing/detiwing of
 * buffews.
 */

static void sdma_v2_4_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							icewand_mgcg_cgcg_init,
							AWWAY_SIZE(icewand_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_icewand_a11,
							AWWAY_SIZE(gowden_settings_icewand_a11));
		bweak;
	defauwt:
		bweak;
	}
}

static void sdma_v2_4_fwee_micwocode(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ucode_wewease(&adev->sdma.instance[i].fw);
}

/**
 * sdma_v2_4_init_micwocode - woad ucode images fwom disk
 *
 * @adev: amdgpu_device pointew
 *
 * Use the fiwmwawe intewface to woad the ucode images into
 * the dwivew (not woaded into hw).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int sdma_v2_4_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[30];
	int eww = 0, i;
	stwuct amdgpu_fiwmwawe_info *info = NUWW;
	const stwuct common_fiwmwawe_headew *headew = NUWW;
	const stwuct sdma_fiwmwawe_headew_v1_0 *hdw;

	DWM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		chip_name = "topaz";
		bweak;
	defauwt: BUG();
	}

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (i == 0)
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma.bin", chip_name);
		ewse
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma1.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->sdma.instance[i].fw, fw_name);
		if (eww)
			goto out;
		hdw = (const stwuct sdma_fiwmwawe_headew_v1_0 *)adev->sdma.instance[i].fw->data;
		adev->sdma.instance[i].fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
		adev->sdma.instance[i].featuwe_vewsion = we32_to_cpu(hdw->ucode_featuwe_vewsion);
		if (adev->sdma.instance[i].featuwe_vewsion >= 20)
			adev->sdma.instance[i].buwst_nop = twue;

		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_SMU) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SDMA0 + i];
			info->ucode_id = AMDGPU_UCODE_ID_SDMA0 + i;
			info->fw = adev->sdma.instance[i].fw;
			headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);
		}
	}

out:
	if (eww) {
		pw_eww("sdma_v2_4: Faiwed to woad fiwmwawe \"%s\"\n", fw_name);
		fow (i = 0; i < adev->sdma.num_instances; i++)
			amdgpu_ucode_wewease(&adev->sdma.instance[i].fw);
	}
	wetuwn eww;
}

/**
 * sdma_v2_4_wing_get_wptw - get the cuwwent wead pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (VI+).
 */
static uint64_t sdma_v2_4_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	/* XXX check if swapping is necessawy on BE */
	wetuwn *wing->wptw_cpu_addw >> 2;
}

/**
 * sdma_v2_4_wing_get_wptw - get the cuwwent wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (VI+).
 */
static uint64_t sdma_v2_4_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 wptw = WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[wing->me]) >> 2;

	wetuwn wptw;
}

/**
 * sdma_v2_4_wing_set_wptw - commit the wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Wwite the wptw back to the hawdwawe (VI+).
 */
static void sdma_v2_4_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[wing->me], wing->wptw << 2);
}

static void sdma_v2_4_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
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
 * sdma_v2_4_wing_emit_ib - Scheduwe an IB on the DMA engine
 *
 * @wing: amdgpu wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: IB object to scheduwe
 * @fwags: unused
 *
 * Scheduwe an IB in the DMA wing (VI).
 */
static void sdma_v2_4_wing_emit_ib(stwuct amdgpu_wing *wing,
				   stwuct amdgpu_job *job,
				   stwuct amdgpu_ib *ib,
				   uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	/* IB packet must end on a 8 DW boundawy */
	sdma_v2_4_wing_insewt_nop(wing, (2 - wowew_32_bits(wing->wptw)) & 7);

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_INDIWECT) |
			  SDMA_PKT_INDIWECT_HEADEW_VMID(vmid & 0xf));
	/* base must be 32 byte awigned */
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw) & 0xffffffe0);
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, 0);

}

/**
 * sdma_v2_4_wing_emit_hdp_fwush - emit an hdp fwush on the DMA wing
 *
 * @wing: amdgpu wing pointew
 *
 * Emit an hdp fwush packet on the wequested DMA wing.
 */
static void sdma_v2_4_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	u32 wef_and_mask = 0;

	if (wing->me == 0)
		wef_and_mask = WEG_SET_FIEWD(wef_and_mask, GPU_HDP_FWUSH_DONE, SDMA0, 1);
	ewse
		wef_and_mask = WEG_SET_FIEWD(wef_and_mask, GPU_HDP_FWUSH_DONE, SDMA1, 1);

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_POWW_WEGMEM) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(1) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(3)); /* == */
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_DONE << 2);
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_WEQ << 2);
	amdgpu_wing_wwite(wing, wef_and_mask); /* wefewence */
	amdgpu_wing_wwite(wing, wef_and_mask); /* mask */
	amdgpu_wing_wwite(wing, SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(0xfff) |
			  SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(10)); /* wetwy count, poww intewvaw */
}

/**
 * sdma_v2_4_wing_emit_fence - emit a fence on the DMA wing
 *
 * @wing: amdgpu wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (VI).
 */
static void sdma_v2_4_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				      unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	/* wwite the fence */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_FENCE));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));

	/* optionawwy wwite high bits as weww */
	if (wwite64bit) {
		addw += 4;
		amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_FENCE));
		amdgpu_wing_wwite(wing, wowew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(seq));
	}

	/* genewate an intewwupt */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_TWAP));
	amdgpu_wing_wwite(wing, SDMA_PKT_TWAP_INT_CONTEXT_INT_CONTEXT(0));
}

/**
 * sdma_v2_4_gfx_stop - stop the gfx async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the gfx async dma wing buffews (VI).
 */
static void sdma_v2_4_gfx_stop(stwuct amdgpu_device *adev)
{
	u32 wb_cntw, ib_cntw;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wb_cntw = WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i]);
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_ENABWE, 0);
		WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i], wb_cntw);
		ib_cntw = WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i]);
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_ENABWE, 0);
		WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i], ib_cntw);
	}
}

/**
 * sdma_v2_4_wwc_stop - stop the compute async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the compute async dma queues (VI).
 */
static void sdma_v2_4_wwc_stop(stwuct amdgpu_device *adev)
{
	/* XXX todo */
}

/**
 * sdma_v2_4_enabwe - stop the async dma engines
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs.
 *
 * Hawt ow unhawt the async dma engines (VI).
 */
static void sdma_v2_4_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 f32_cntw;
	int i;

	if (!enabwe) {
		sdma_v2_4_gfx_stop(adev);
		sdma_v2_4_wwc_stop(adev);
	}

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntw = WWEG32(mmSDMA0_F32_CNTW + sdma_offsets[i]);
		if (enabwe)
			f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_F32_CNTW, HAWT, 0);
		ewse
			f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_F32_CNTW, HAWT, 1);
		WWEG32(mmSDMA0_F32_CNTW + sdma_offsets[i], f32_cntw);
	}
}

/**
 * sdma_v2_4_gfx_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the gfx DMA wing buffews and enabwe them (VI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v2_4_gfx_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 wb_cntw, ib_cntw;
	u32 wb_bufsz;
	int i, j, w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;

		mutex_wock(&adev->swbm_mutex);
		fow (j = 0; j < 16; j++) {
			vi_swbm_sewect(adev, 0, 0, 0, j);
			/* SDMA GFX */
			WWEG32(mmSDMA0_GFX_VIWTUAW_ADDW + sdma_offsets[i], 0);
			WWEG32(mmSDMA0_GFX_APE1_CNTW + sdma_offsets[i], 0);
		}
		vi_swbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);

		WWEG32(mmSDMA0_TIWING_CONFIG + sdma_offsets[i],
		       adev->gfx.config.gb_addw_config & 0x70);

		WWEG32(mmSDMA0_SEM_WAIT_FAIW_TIMEW_CNTW + sdma_offsets[i], 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i]);
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_SIZE, wb_bufsz);
#ifdef __BIG_ENDIAN
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_SWAP_ENABWE, 1);
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW,
					WPTW_WWITEBACK_SWAP_ENABWE, 1);
#endif
		WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i], wb_cntw);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[i], 0);
		WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[i], 0);
		WWEG32(mmSDMA0_GFX_IB_WPTW + sdma_offsets[i], 0);
		WWEG32(mmSDMA0_GFX_IB_OFFSET + sdma_offsets[i], 0);

		/* set the wb addwess whethew it's enabwed ow not */
		WWEG32(mmSDMA0_GFX_WB_WPTW_ADDW_HI + sdma_offsets[i],
		       uppew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFF);
		WWEG32(mmSDMA0_GFX_WB_WPTW_ADDW_WO + sdma_offsets[i],
		       wowew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFC);

		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WPTW_WWITEBACK_ENABWE, 1);

		WWEG32(mmSDMA0_GFX_WB_BASE + sdma_offsets[i], wing->gpu_addw >> 8);
		WWEG32(mmSDMA0_GFX_WB_BASE_HI + sdma_offsets[i], wing->gpu_addw >> 40);

		wing->wptw = 0;
		WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[i], wing->wptw << 2);

		/* enabwe DMA WB */
		wb_cntw = WEG_SET_FIEWD(wb_cntw, SDMA0_GFX_WB_CNTW, WB_ENABWE, 1);
		WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i], wb_cntw);

		ib_cntw = WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i]);
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_ENABWE, 1);
#ifdef __BIG_ENDIAN
		ib_cntw = WEG_SET_FIEWD(ib_cntw, SDMA0_GFX_IB_CNTW, IB_SWAP_ENABWE, 1);
#endif
		/* enabwe DMA IBs */
		WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i], ib_cntw);
	}

	sdma_v2_4_enabwe(adev, twue);
	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * sdma_v2_4_wwc_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the compute DMA queues and enabwe them (VI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v2_4_wwc_wesume(stwuct amdgpu_device *adev)
{
	/* XXX todo */
	wetuwn 0;
}


/**
 * sdma_v2_4_stawt - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the DMA engines and enabwe them (VI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v2_4_stawt(stwuct amdgpu_device *adev)
{
	int w;

	/* hawt the engine befowe pwogwaming */
	sdma_v2_4_enabwe(adev, fawse);

	/* stawt the gfx wings and wwc compute queues */
	w = sdma_v2_4_gfx_wesume(adev);
	if (w)
		wetuwn w;
	w = sdma_v2_4_wwc_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

/**
 * sdma_v2_4_wing_test_wing - simpwe async dma engine test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (VI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int sdma_v2_4_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned i;
	unsigned index;
	int w;
	u32 tmp;
	u64 gpu_addw;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_we32(tmp);

	w = amdgpu_wing_awwoc(wing, 5);
	if (w)
		goto ewwow_fwee_wb;

	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
			  SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW));
	amdgpu_wing_wwite(wing, wowew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, SDMA_PKT_WWITE_UNTIWED_DW_3_COUNT(1));
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = we32_to_cpu(adev->wb.wb[index]);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

ewwow_fwee_wb:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}

/**
 * sdma_v2_4_wing_test_ib - test an IB on the DMA engine
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Test a simpwe IB in the DMA wing (VI).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int sdma_v2_4_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;
	unsigned index;
	u32 tmp = 0;
	u64 gpu_addw;
	wong w;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_we32(tmp);
	memset(&ib, 0, sizeof(ib));
	w = amdgpu_ib_get(adev, NUWW, 256,
					AMDGPU_IB_POOW_DIWECT, &ib);
	if (w)
		goto eww0;

	ib.ptw[0] = SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw);
	ib.ptw[3] = SDMA_PKT_WWITE_UNTIWED_DW_3_COUNT(1);
	ib.ptw[4] = 0xDEADBEEF;
	ib.ptw[5] = SDMA_PKT_HEADEW_OP(SDMA_OP_NOP);
	ib.ptw[6] = SDMA_PKT_HEADEW_OP(SDMA_OP_NOP);
	ib.ptw[7] = SDMA_PKT_HEADEW_OP(SDMA_OP_NOP);
	ib.wength_dw = 8;

	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto eww1;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto eww1;
	} ewse if (w < 0) {
		goto eww1;
	}
	tmp = we32_to_cpu(adev->wb.wb[index]);
	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

eww1:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
eww0:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}

/**
 * sdma_v2_4_vm_copy_pte - update PTEs by copying them fwom the GAWT
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using sDMA (CIK).
 */
static void sdma_v2_4_vm_copy_pte(stwuct amdgpu_ib *ib,
				  uint64_t pe, uint64_t swc,
				  unsigned count)
{
	unsigned bytes = count * 8;

	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_COPY_WINEAW);
	ib->ptw[ib->wength_dw++] = bytes;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
}

/**
 * sdma_v2_4_vm_wwite_pte - update PTEs by wwiting them manuawwy
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @vawue: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 *
 * Update PTEs by wwiting them manuawwy using sDMA (CIK).
 */
static void sdma_v2_4_vm_wwite_pte(stwuct amdgpu_ib *ib, uint64_t pe,
				   uint64_t vawue, unsigned count,
				   uint32_t incw)
{
	unsigned ndw = count * 2;

	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_WWITE) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_WWITE_WINEAW);
	ib->ptw[ib->wength_dw++] = pe;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = ndw;
	fow (; ndw > 0; ndw -= 2) {
		ib->ptw[ib->wength_dw++] = wowew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		vawue += incw;
	}
}

/**
 * sdma_v2_4_vm_set_pte_pde - update the page tabwes using sDMA
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update the page tabwes using sDMA (CIK).
 */
static void sdma_v2_4_vm_set_pte_pde(stwuct amdgpu_ib *ib, uint64_t pe,
				     uint64_t addw, unsigned count,
				     uint32_t incw, uint64_t fwags)
{
	/* fow physicawwy contiguous pages (vwam) */
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_GEN_PTEPDE);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe); /* dst addw */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(fwags); /* mask */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(fwags);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(addw); /* vawue */
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = incw; /* incwement size */
	ib->ptw[ib->wength_dw++] = 0;
	ib->ptw[ib->wength_dw++] = count; /* numbew of entwies */
}

/**
 * sdma_v2_4_wing_pad_ib - pad the IB to the wequiwed numbew of dw
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @ib: indiwect buffew to fiww with padding
 *
 */
static void sdma_v2_4_wing_pad_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_fwom_wing(wing);
	u32 pad_count;
	int i;

	pad_count = (-ib->wength_dw) & 7;
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
 * sdma_v2_4_wing_emit_pipewine_sync - sync the pipewine
 *
 * @wing: amdgpu_wing pointew
 *
 * Make suwe aww pwevious opewations awe compweted (CIK).
 */
static void sdma_v2_4_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
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
 * sdma_v2_4_wing_emit_vm_fwush - cik vm fwush using sDMA
 *
 * @wing: amdgpu_wing pointew
 * @vmid: vmid numbew to use
 * @pd_addw: addwess
 *
 * Update the page tabwe base and fwush the VM TWB
 * using sDMA (VI).
 */
static void sdma_v2_4_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					 unsigned vmid, uint64_t pd_addw)
{
	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow fwush */
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_POWW_WEGMEM) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(0) |
			  SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(0)); /* awways */
	amdgpu_wing_wwite(wing, mmVM_INVAWIDATE_WEQUEST << 2);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, 0); /* wefewence */
	amdgpu_wing_wwite(wing, 0); /* mask */
	amdgpu_wing_wwite(wing, SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(0xfff) |
			  SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(10)); /* wetwy count, poww intewvaw */
}

static void sdma_v2_4_wing_emit_wweg(stwuct amdgpu_wing *wing,
				     uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, SDMA_PKT_HEADEW_OP(SDMA_OP_SWBM_WWITE) |
			  SDMA_PKT_SWBM_WWITE_HEADEW_BYTE_EN(0xf));
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, vaw);
}

static int sdma_v2_4_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	adev->sdma.num_instances = SDMA_MAX_INSTANCE;

	w = sdma_v2_4_init_micwocode(adev);
	if (w)
		wetuwn w;

	sdma_v2_4_set_wing_funcs(adev);
	sdma_v2_4_set_buffew_funcs(adev);
	sdma_v2_4_set_vm_pte_funcs(adev);
	sdma_v2_4_set_iwq_funcs(adev);

	wetuwn 0;
}

static int sdma_v2_4_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* SDMA twap event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_SDMA_TWAP,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	/* SDMA Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 241,
			      &adev->sdma.iwwegaw_inst_iwq);
	if (w)
		wetuwn w;

	/* SDMA Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_SDMA_SWBM_WWITE,
			      &adev->sdma.iwwegaw_inst_iwq);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		wing->wing_obj = NUWW;
		wing->use_doowbeww = fawse;
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

static int sdma_v2_4_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_wing_fini(&adev->sdma.instance[i].wing);

	sdma_v2_4_fwee_micwocode(adev);
	wetuwn 0;
}

static int sdma_v2_4_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	sdma_v2_4_init_gowden_wegistews(adev);

	w = sdma_v2_4_stawt(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int sdma_v2_4_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	sdma_v2_4_enabwe(adev, fawse);

	wetuwn 0;
}

static int sdma_v2_4_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn sdma_v2_4_hw_fini(adev);
}

static int sdma_v2_4_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn sdma_v2_4_hw_init(adev);
}

static boow sdma_v2_4_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS2);

	if (tmp & (SWBM_STATUS2__SDMA_BUSY_MASK |
		   SWBM_STATUS2__SDMA1_BUSY_MASK))
	    wetuwn fawse;

	wetuwn twue;
}

static int sdma_v2_4_wait_fow_idwe(void *handwe)
{
	unsigned i;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(mmSWBM_STATUS2) & (SWBM_STATUS2__SDMA_BUSY_MASK |
				SWBM_STATUS2__SDMA1_BUSY_MASK);

		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int sdma_v2_4_soft_weset(void *handwe)
{
	u32 swbm_soft_weset = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS2);

	if (tmp & SWBM_STATUS2__SDMA_BUSY_MASK) {
		/* sdma0 */
		tmp = WWEG32(mmSDMA0_F32_CNTW + SDMA0_WEGISTEW_OFFSET);
		tmp = WEG_SET_FIEWD(tmp, SDMA0_F32_CNTW, HAWT, 0);
		WWEG32(mmSDMA0_F32_CNTW + SDMA0_WEGISTEW_OFFSET, tmp);
		swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_SDMA_MASK;
	}
	if (tmp & SWBM_STATUS2__SDMA1_BUSY_MASK) {
		/* sdma1 */
		tmp = WWEG32(mmSDMA0_F32_CNTW + SDMA1_WEGISTEW_OFFSET);
		tmp = WEG_SET_FIEWD(tmp, SDMA0_F32_CNTW, HAWT, 0);
		WWEG32(mmSDMA0_F32_CNTW + SDMA1_WEGISTEW_OFFSET, tmp);
		swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_SDMA1_MASK;
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

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int sdma_v2_4_set_twap_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *swc,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	u32 sdma_cntw;

	switch (type) {
	case AMDGPU_SDMA_IWQ_INSTANCE0:
		switch (state) {
		case AMDGPU_IWQ_STATE_DISABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET);
			sdma_cntw = WEG_SET_FIEWD(sdma_cntw, SDMA0_CNTW, TWAP_ENABWE, 0);
			WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET);
			sdma_cntw = WEG_SET_FIEWD(sdma_cntw, SDMA0_CNTW, TWAP_ENABWE, 1);
			WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case AMDGPU_SDMA_IWQ_INSTANCE1:
		switch (state) {
		case AMDGPU_IWQ_STATE_DISABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET);
			sdma_cntw = WEG_SET_FIEWD(sdma_cntw, SDMA0_CNTW, TWAP_ENABWE, 0);
			WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET);
			sdma_cntw = WEG_SET_FIEWD(sdma_cntw, SDMA0_CNTW, TWAP_ENABWE, 1);
			WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int sdma_v2_4_pwocess_twap_iwq(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	u8 instance_id, queue_id;

	instance_id = (entwy->wing_id & 0x3) >> 0;
	queue_id = (entwy->wing_id & 0xc) >> 2;
	DWM_DEBUG("IH: SDMA twap\n");
	switch (instance_id) {
	case 0:
		switch (queue_id) {
		case 0:
			amdgpu_fence_pwocess(&adev->sdma.instance[0].wing);
			bweak;
		case 1:
			/* XXX compute */
			bweak;
		case 2:
			/* XXX compute */
			bweak;
		}
		bweak;
	case 1:
		switch (queue_id) {
		case 0:
			amdgpu_fence_pwocess(&adev->sdma.instance[1].wing);
			bweak;
		case 1:
			/* XXX compute */
			bweak;
		case 2:
			/* XXX compute */
			bweak;
		}
		bweak;
	}
	wetuwn 0;
}

static int sdma_v2_4_pwocess_iwwegaw_inst_iwq(stwuct amdgpu_device *adev,
					      stwuct amdgpu_iwq_swc *souwce,
					      stwuct amdgpu_iv_entwy *entwy)
{
	u8 instance_id, queue_id;

	DWM_EWWOW("Iwwegaw instwuction in SDMA command stweam\n");
	instance_id = (entwy->wing_id & 0x3) >> 0;
	queue_id = (entwy->wing_id & 0xc) >> 2;

	if (instance_id <= 1 && queue_id == 0)
		dwm_sched_fauwt(&adev->sdma.instance[instance_id].wing.sched);
	wetuwn 0;
}

static int sdma_v2_4_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	/* XXX handwed via the smc on VI */
	wetuwn 0;
}

static int sdma_v2_4_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs sdma_v2_4_ip_funcs = {
	.name = "sdma_v2_4",
	.eawwy_init = sdma_v2_4_eawwy_init,
	.wate_init = NUWW,
	.sw_init = sdma_v2_4_sw_init,
	.sw_fini = sdma_v2_4_sw_fini,
	.hw_init = sdma_v2_4_hw_init,
	.hw_fini = sdma_v2_4_hw_fini,
	.suspend = sdma_v2_4_suspend,
	.wesume = sdma_v2_4_wesume,
	.is_idwe = sdma_v2_4_is_idwe,
	.wait_fow_idwe = sdma_v2_4_wait_fow_idwe,
	.soft_weset = sdma_v2_4_soft_weset,
	.set_cwockgating_state = sdma_v2_4_set_cwockgating_state,
	.set_powewgating_state = sdma_v2_4_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs sdma_v2_4_wing_funcs = {
	.type = AMDGPU_WING_TYPE_SDMA,
	.awign_mask = 0xf,
	.nop = SDMA_PKT_NOP_HEADEW_OP(SDMA_OP_NOP),
	.suppowt_64bit_ptws = fawse,
	.secuwe_submission_suppowted = twue,
	.get_wptw = sdma_v2_4_wing_get_wptw,
	.get_wptw = sdma_v2_4_wing_get_wptw,
	.set_wptw = sdma_v2_4_wing_set_wptw,
	.emit_fwame_size =
		6 + /* sdma_v2_4_wing_emit_hdp_fwush */
		3 + /* hdp invawidate */
		6 + /* sdma_v2_4_wing_emit_pipewine_sync */
		VI_FWUSH_GPU_TWB_NUM_WWEG * 3 + 6 + /* sdma_v2_4_wing_emit_vm_fwush */
		10 + 10 + 10, /* sdma_v2_4_wing_emit_fence x3 fow usew fence, vm fence */
	.emit_ib_size = 7 + 6, /* sdma_v2_4_wing_emit_ib */
	.emit_ib = sdma_v2_4_wing_emit_ib,
	.emit_fence = sdma_v2_4_wing_emit_fence,
	.emit_pipewine_sync = sdma_v2_4_wing_emit_pipewine_sync,
	.emit_vm_fwush = sdma_v2_4_wing_emit_vm_fwush,
	.emit_hdp_fwush = sdma_v2_4_wing_emit_hdp_fwush,
	.test_wing = sdma_v2_4_wing_test_wing,
	.test_ib = sdma_v2_4_wing_test_ib,
	.insewt_nop = sdma_v2_4_wing_insewt_nop,
	.pad_ib = sdma_v2_4_wing_pad_ib,
	.emit_wweg = sdma_v2_4_wing_emit_wweg,
};

static void sdma_v2_4_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->sdma.instance[i].wing.funcs = &sdma_v2_4_wing_funcs;
		adev->sdma.instance[i].wing.me = i;
	}
}

static const stwuct amdgpu_iwq_swc_funcs sdma_v2_4_twap_iwq_funcs = {
	.set = sdma_v2_4_set_twap_iwq_state,
	.pwocess = sdma_v2_4_pwocess_twap_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs sdma_v2_4_iwwegaw_inst_iwq_funcs = {
	.pwocess = sdma_v2_4_pwocess_iwwegaw_inst_iwq,
};

static void sdma_v2_4_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->sdma.twap_iwq.num_types = AMDGPU_SDMA_IWQ_WAST;
	adev->sdma.twap_iwq.funcs = &sdma_v2_4_twap_iwq_funcs;
	adev->sdma.iwwegaw_inst_iwq.funcs = &sdma_v2_4_iwwegaw_inst_iwq_funcs;
}

/**
 * sdma_v2_4_emit_copy_buffew - copy buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 * @tmz: unused
 *
 * Copy GPU buffews using the DMA engine (VI).
 * Used by the amdgpu ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
static void sdma_v2_4_emit_copy_buffew(stwuct amdgpu_ib *ib,
				       uint64_t swc_offset,
				       uint64_t dst_offset,
				       uint32_t byte_count,
				       boow tmz)
{
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADEW_SUB_OP(SDMA_SUBOP_COPY_WINEAW);
	ib->ptw[ib->wength_dw++] = byte_count;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
}

/**
 * sdma_v2_4_emit_fiww_buffew - fiww buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_data: vawue to wwite to buffew
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 *
 * Fiww GPU buffews using the DMA engine (VI).
 */
static void sdma_v2_4_emit_fiww_buffew(stwuct amdgpu_ib *ib,
				       uint32_t swc_data,
				       uint64_t dst_offset,
				       uint32_t byte_count)
{
	ib->ptw[ib->wength_dw++] = SDMA_PKT_HEADEW_OP(SDMA_OP_CONST_FIWW);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = swc_data;
	ib->ptw[ib->wength_dw++] = byte_count;
}

static const stwuct amdgpu_buffew_funcs sdma_v2_4_buffew_funcs = {
	.copy_max_bytes = 0x1fffff,
	.copy_num_dw = 7,
	.emit_copy_buffew = sdma_v2_4_emit_copy_buffew,

	.fiww_max_bytes = 0x1fffff,
	.fiww_num_dw = 7,
	.emit_fiww_buffew = sdma_v2_4_emit_fiww_buffew,
};

static void sdma_v2_4_set_buffew_funcs(stwuct amdgpu_device *adev)
{
	adev->mman.buffew_funcs = &sdma_v2_4_buffew_funcs;
	adev->mman.buffew_funcs_wing = &adev->sdma.instance[0].wing;
}

static const stwuct amdgpu_vm_pte_funcs sdma_v2_4_vm_pte_funcs = {
	.copy_pte_num_dw = 7,
	.copy_pte = sdma_v2_4_vm_copy_pte,

	.wwite_pte = sdma_v2_4_vm_wwite_pte,
	.set_pte_pde = sdma_v2_4_vm_set_pte_pde,
};

static void sdma_v2_4_set_vm_pte_funcs(stwuct amdgpu_device *adev)
{
	unsigned i;

	adev->vm_managew.vm_pte_funcs = &sdma_v2_4_vm_pte_funcs;
	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->vm_managew.vm_pte_scheds[i] =
			&adev->sdma.instance[i].wing.sched;
	}
	adev->vm_managew.vm_pte_num_scheds = adev->sdma.num_instances;
}

const stwuct amdgpu_ip_bwock_vewsion sdma_v2_4_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_SDMA,
	.majow = 2,
	.minow = 4,
	.wev = 0,
	.funcs = &sdma_v2_4_ip_funcs,
};
