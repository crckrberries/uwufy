/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_twace.h"
#incwude "cikd.h"
#incwude "cik.h"

#incwude "bif/bif_4_1_d.h"
#incwude "bif/bif_4_1_sh_mask.h"

#incwude "gca/gfx_7_2_d.h"
#incwude "gca/gfx_7_2_enum.h"
#incwude "gca/gfx_7_2_sh_mask.h"

#incwude "gmc/gmc_7_1_d.h"
#incwude "gmc/gmc_7_1_sh_mask.h"

#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"

static const u32 sdma_offsets[SDMA_MAX_INSTANCE] =
{
	SDMA0_WEGISTEW_OFFSET,
	SDMA1_WEGISTEW_OFFSET
};

static void cik_sdma_set_wing_funcs(stwuct amdgpu_device *adev);
static void cik_sdma_set_iwq_funcs(stwuct amdgpu_device *adev);
static void cik_sdma_set_buffew_funcs(stwuct amdgpu_device *adev);
static void cik_sdma_set_vm_pte_funcs(stwuct amdgpu_device *adev);
static int cik_sdma_soft_weset(void *handwe);

MODUWE_FIWMWAWE("amdgpu/bonaiwe_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_sdma1.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_sdma1.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/kavewi_sdma1.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/kabini_sdma1.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_sdma.bin");
MODUWE_FIWMWAWE("amdgpu/muwwins_sdma1.bin");

u32 amdgpu_cik_gpu_check_soft_weset(stwuct amdgpu_device *adev);


static void cik_sdma_fwee_micwocode(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ucode_wewease(&adev->sdma.instance[i].fw);
}

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

/**
 * cik_sdma_init_micwocode - woad ucode images fwom disk
 *
 * @adev: amdgpu_device pointew
 *
 * Use the fiwmwawe intewface to woad the ucode images into
 * the dwivew (not woaded into hw).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int cik_sdma_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[30];
	int eww = 0, i;

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
	}
out:
	if (eww) {
		pw_eww("cik_sdma: Faiwed to woad fiwmwawe \"%s\"\n", fw_name);
		fow (i = 0; i < adev->sdma.num_instances; i++)
			amdgpu_ucode_wewease(&adev->sdma.instance[i].fw);
	}
	wetuwn eww;
}

/**
 * cik_sdma_wing_get_wptw - get the cuwwent wead pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (CIK+).
 */
static uint64_t cik_sdma_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	u32 wptw;

	wptw = *wing->wptw_cpu_addw;

	wetuwn (wptw & 0x3fffc) >> 2;
}

/**
 * cik_sdma_wing_get_wptw - get the cuwwent wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (CIK+).
 */
static uint64_t cik_sdma_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn (WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[wing->me]) & 0x3fffc) >> 2;
}

/**
 * cik_sdma_wing_set_wptw - commit the wwite pointew
 *
 * @wing: amdgpu wing pointew
 *
 * Wwite the wptw back to the hawdwawe (CIK+).
 */
static void cik_sdma_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[wing->me],
	       (wing->wptw << 2) & 0x3fffc);
}

static void cik_sdma_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	stwuct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_fwom_wing(wing);
	int i;

	fow (i = 0; i < count; i++)
		if (sdma && sdma->buwst_nop && (i == 0))
			amdgpu_wing_wwite(wing, wing->funcs->nop |
					  SDMA_NOP_COUNT(count - 1));
		ewse
			amdgpu_wing_wwite(wing, wing->funcs->nop);
}

/**
 * cik_sdma_wing_emit_ib - Scheduwe an IB on the DMA engine
 *
 * @wing: amdgpu wing pointew
 * @job: job to wetwive vmid fwom
 * @ib: IB object to scheduwe
 * @fwags: unused
 *
 * Scheduwe an IB in the DMA wing (CIK).
 */
static void cik_sdma_wing_emit_ib(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job,
				  stwuct amdgpu_ib *ib,
				  uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 extwa_bits = vmid & 0xf;

	/* IB packet must end on a 8 DW boundawy */
	cik_sdma_wing_insewt_nop(wing, (4 - wowew_32_bits(wing->wptw)) & 7);

	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_INDIWECT_BUFFEW, 0, extwa_bits));
	amdgpu_wing_wwite(wing, ib->gpu_addw & 0xffffffe0); /* base must be 32 byte awigned */
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xffffffff);
	amdgpu_wing_wwite(wing, ib->wength_dw);

}

/**
 * cik_sdma_wing_emit_hdp_fwush - emit an hdp fwush on the DMA wing
 *
 * @wing: amdgpu wing pointew
 *
 * Emit an hdp fwush packet on the wequested DMA wing.
 */
static void cik_sdma_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	u32 extwa_bits = (SDMA_POWW_WEG_MEM_EXTWA_OP(1) |
			  SDMA_POWW_WEG_MEM_EXTWA_FUNC(3)); /* == */
	u32 wef_and_mask;

	if (wing->me == 0)
		wef_and_mask = GPU_HDP_FWUSH_DONE__SDMA0_MASK;
	ewse
		wef_and_mask = GPU_HDP_FWUSH_DONE__SDMA1_MASK;

	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_POWW_WEG_MEM, 0, extwa_bits));
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_DONE << 2);
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_WEQ << 2);
	amdgpu_wing_wwite(wing, wef_and_mask); /* wefewence */
	amdgpu_wing_wwite(wing, wef_and_mask); /* mask */
	amdgpu_wing_wwite(wing, (0xfff << 16) | 10); /* wetwy count, poww intewvaw */
}

/**
 * cik_sdma_wing_emit_fence - emit a fence on the DMA wing
 *
 * @wing: amdgpu wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (CIK).
 */
static void cik_sdma_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				     unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	/* wwite the fence */
	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_FENCE, 0, 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));

	/* optionawwy wwite high bits as weww */
	if (wwite64bit) {
		addw += 4;
		amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_FENCE, 0, 0));
		amdgpu_wing_wwite(wing, wowew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(addw));
		amdgpu_wing_wwite(wing, uppew_32_bits(seq));
	}

	/* genewate an intewwupt */
	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_TWAP, 0, 0));
}

/**
 * cik_sdma_gfx_stop - stop the gfx async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the gfx async dma wing buffews (CIK).
 */
static void cik_sdma_gfx_stop(stwuct amdgpu_device *adev)
{
	u32 wb_cntw;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wb_cntw = WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i]);
		wb_cntw &= ~SDMA0_GFX_WB_CNTW__WB_ENABWE_MASK;
		WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i], wb_cntw);
		WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i], 0);
	}
}

/**
 * cik_sdma_wwc_stop - stop the compute async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Stop the compute async dma queues (CIK).
 */
static void cik_sdma_wwc_stop(stwuct amdgpu_device *adev)
{
	/* XXX todo */
}

/**
 * cik_ctx_switch_enabwe - stop the async dma engines context switch
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs context switch.
 *
 * Hawt ow unhawt the async dma engines context switch (VI).
 */
static void cik_ctx_switch_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 f32_cntw, phase_quantum = 0;
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
		f32_cntw = WWEG32(mmSDMA0_CNTW + sdma_offsets[i]);
		if (enabwe) {
			f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_CNTW,
					AUTO_CTXSW_ENABWE, 1);
			if (amdgpu_sdma_phase_quantum) {
				WWEG32(mmSDMA0_PHASE0_QUANTUM + sdma_offsets[i],
				       phase_quantum);
				WWEG32(mmSDMA0_PHASE1_QUANTUM + sdma_offsets[i],
				       phase_quantum);
			}
		} ewse {
			f32_cntw = WEG_SET_FIEWD(f32_cntw, SDMA0_CNTW,
					AUTO_CTXSW_ENABWE, 0);
		}

		WWEG32(mmSDMA0_CNTW + sdma_offsets[i], f32_cntw);
	}
}

/**
 * cik_sdma_enabwe - stop the async dma engines
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs.
 *
 * Hawt ow unhawt the async dma engines (CIK).
 */
static void cik_sdma_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 me_cntw;
	int i;

	if (!enabwe) {
		cik_sdma_gfx_stop(adev);
		cik_sdma_wwc_stop(adev);
	}

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		me_cntw = WWEG32(mmSDMA0_F32_CNTW + sdma_offsets[i]);
		if (enabwe)
			me_cntw &= ~SDMA0_F32_CNTW__HAWT_MASK;
		ewse
			me_cntw |= SDMA0_F32_CNTW__HAWT_MASK;
		WWEG32(mmSDMA0_F32_CNTW + sdma_offsets[i], me_cntw);
	}
}

/**
 * cik_sdma_gfx_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the gfx DMA wing buffews and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_gfx_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 wb_cntw, ib_cntw;
	u32 wb_bufsz;
	int i, j, w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;

		mutex_wock(&adev->swbm_mutex);
		fow (j = 0; j < 16; j++) {
			cik_swbm_sewect(adev, 0, 0, 0, j);
			/* SDMA GFX */
			WWEG32(mmSDMA0_GFX_VIWTUAW_ADDW + sdma_offsets[i], 0);
			WWEG32(mmSDMA0_GFX_APE1_CNTW + sdma_offsets[i], 0);
			/* XXX SDMA WWC - todo */
		}
		cik_swbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);

		WWEG32(mmSDMA0_TIWING_CONFIG + sdma_offsets[i],
		       adev->gfx.config.gb_addw_config & 0x70);

		WWEG32(mmSDMA0_SEM_INCOMPWETE_TIMEW_CNTW + sdma_offsets[i], 0);
		WWEG32(mmSDMA0_SEM_WAIT_FAIW_TIMEW_CNTW + sdma_offsets[i], 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = wb_bufsz << 1;
#ifdef __BIG_ENDIAN
		wb_cntw |= SDMA0_GFX_WB_CNTW__WB_SWAP_ENABWE_MASK |
			SDMA0_GFX_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK;
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
		       ((wing->wptw_gpu_addw) & 0xFFFFFFFC));

		wb_cntw |= SDMA0_GFX_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK;

		WWEG32(mmSDMA0_GFX_WB_BASE + sdma_offsets[i], wing->gpu_addw >> 8);
		WWEG32(mmSDMA0_GFX_WB_BASE_HI + sdma_offsets[i], wing->gpu_addw >> 40);

		wing->wptw = 0;
		WWEG32(mmSDMA0_GFX_WB_WPTW + sdma_offsets[i], wing->wptw << 2);

		/* enabwe DMA WB */
		WWEG32(mmSDMA0_GFX_WB_CNTW + sdma_offsets[i],
		       wb_cntw | SDMA0_GFX_WB_CNTW__WB_ENABWE_MASK);

		ib_cntw = SDMA0_GFX_IB_CNTW__IB_ENABWE_MASK;
#ifdef __BIG_ENDIAN
		ib_cntw |= SDMA0_GFX_IB_CNTW__IB_SWAP_ENABWE_MASK;
#endif
		/* enabwe DMA IBs */
		WWEG32(mmSDMA0_GFX_IB_CNTW + sdma_offsets[i], ib_cntw);
	}

	cik_sdma_enabwe(adev, twue);

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * cik_sdma_wwc_wesume - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the compute DMA queues and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_wwc_wesume(stwuct amdgpu_device *adev)
{
	/* XXX todo */
	wetuwn 0;
}

/**
 * cik_sdma_woad_micwocode - woad the sDMA ME ucode
 *
 * @adev: amdgpu_device pointew
 *
 * Woads the sDMA0/1 ucode.
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int cik_sdma_woad_micwocode(stwuct amdgpu_device *adev)
{
	const stwuct sdma_fiwmwawe_headew_v1_0 *hdw;
	const __we32 *fw_data;
	u32 fw_size;
	int i, j;

	/* hawt the MEs */
	cik_sdma_enabwe(adev, fawse);

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (!adev->sdma.instance[i].fw)
			wetuwn -EINVAW;
		hdw = (const stwuct sdma_fiwmwawe_headew_v1_0 *)adev->sdma.instance[i].fw->data;
		amdgpu_ucode_pwint_sdma_hdw(&hdw->headew);
		fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
		adev->sdma.instance[i].fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
		adev->sdma.instance[i].featuwe_vewsion = we32_to_cpu(hdw->ucode_featuwe_vewsion);
		if (adev->sdma.instance[i].featuwe_vewsion >= 20)
			adev->sdma.instance[i].buwst_nop = twue;
		fw_data = (const __we32 *)
			(adev->sdma.instance[i].fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
		WWEG32(mmSDMA0_UCODE_ADDW + sdma_offsets[i], 0);
		fow (j = 0; j < fw_size; j++)
			WWEG32(mmSDMA0_UCODE_DATA + sdma_offsets[i], we32_to_cpup(fw_data++));
		WWEG32(mmSDMA0_UCODE_ADDW + sdma_offsets[i], adev->sdma.instance[i].fw_vewsion);
	}

	wetuwn 0;
}

/**
 * cik_sdma_stawt - setup and stawt the async dma engines
 *
 * @adev: amdgpu_device pointew
 *
 * Set up the DMA engines and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_stawt(stwuct amdgpu_device *adev)
{
	int w;

	w = cik_sdma_woad_micwocode(adev);
	if (w)
		wetuwn w;

	/* hawt the engine befowe pwogwaming */
	cik_sdma_enabwe(adev, fawse);
	/* enabwe sdma wing pweemption */
	cik_ctx_switch_enabwe(adev, twue);

	/* stawt the gfx wings and wwc compute queues */
	w = cik_sdma_gfx_wesume(adev);
	if (w)
		wetuwn w;
	w = cik_sdma_wwc_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

/**
 * cik_sdma_wing_test_wing - simpwe async dma engine test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_wing_test_wing(stwuct amdgpu_wing *wing)
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

	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_WWITE, SDMA_WWITE_SUB_OPCODE_WINEAW, 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, 1); /* numbew of DWs to fowwow */
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
 * cik_sdma_wing_test_ib - test an IB on the DMA engine
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Test a simpwe IB in the DMA wing (CIK).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int cik_sdma_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
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

	ib.ptw[0] = SDMA_PACKET(SDMA_OPCODE_WWITE,
				SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw);
	ib.ptw[3] = 1;
	ib.ptw[4] = 0xDEADBEEF;
	ib.wength_dw = 5;
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
 * cik_sdma_vm_copy_pte - update PTEs by copying them fwom the GAWT
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using sDMA (CIK).
 */
static void cik_sdma_vm_copy_pte(stwuct amdgpu_ib *ib,
				 uint64_t pe, uint64_t swc,
				 unsigned count)
{
	unsigned bytes = count * 8;

	ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY,
		SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
	ib->ptw[ib->wength_dw++] = bytes;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
}

/**
 * cik_sdma_vm_wwite_pte - update PTEs by wwiting them manuawwy
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @vawue: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 *
 * Update PTEs by wwiting them manuawwy using sDMA (CIK).
 */
static void cik_sdma_vm_wwite_pte(stwuct amdgpu_ib *ib, uint64_t pe,
				  uint64_t vawue, unsigned count,
				  uint32_t incw)
{
	unsigned ndw = count * 2;

	ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_WWITE,
		SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = ndw;
	fow (; ndw > 0; ndw -= 2) {
		ib->ptw[ib->wength_dw++] = wowew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		vawue += incw;
	}
}

/**
 * cik_sdma_vm_set_pte_pde - update the page tabwes using sDMA
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
static void cik_sdma_vm_set_pte_pde(stwuct amdgpu_ib *ib, uint64_t pe,
				    uint64_t addw, unsigned count,
				    uint32_t incw, uint64_t fwags)
{
	/* fow physicawwy contiguous pages (vwam) */
	ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_GENEWATE_PTE_PDE, 0, 0);
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
 * cik_sdma_wing_pad_ib - pad the IB to the wequiwed numbew of dw
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @ib: indiwect buffew to fiww with padding
 *
 */
static void cik_sdma_wing_pad_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_fwom_wing(wing);
	u32 pad_count;
	int i;

	pad_count = (-ib->wength_dw) & 7;
	fow (i = 0; i < pad_count; i++)
		if (sdma && sdma->buwst_nop && (i == 0))
			ib->ptw[ib->wength_dw++] =
					SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0) |
					SDMA_NOP_COUNT(pad_count - 1);
		ewse
			ib->ptw[ib->wength_dw++] =
					SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0);
}

/**
 * cik_sdma_wing_emit_pipewine_sync - sync the pipewine
 *
 * @wing: amdgpu_wing pointew
 *
 * Make suwe aww pwevious opewations awe compweted (CIK).
 */
static void cik_sdma_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	/* wait fow idwe */
	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_POWW_WEG_MEM, 0,
					    SDMA_POWW_WEG_MEM_EXTWA_OP(0) |
					    SDMA_POWW_WEG_MEM_EXTWA_FUNC(3) | /* equaw */
					    SDMA_POWW_WEG_MEM_EXTWA_M));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xffffffff);
	amdgpu_wing_wwite(wing, seq); /* wefewence */
	amdgpu_wing_wwite(wing, 0xffffffff); /* mask */
	amdgpu_wing_wwite(wing, (0xfff << 16) | 4); /* wetwy count, poww intewvaw */
}

/**
 * cik_sdma_wing_emit_vm_fwush - cik vm fwush using sDMA
 *
 * @wing: amdgpu_wing pointew
 * @vmid: vmid numbew to use
 * @pd_addw: addwess
 *
 * Update the page tabwe base and fwush the VM TWB
 * using sDMA (CIK).
 */
static void cik_sdma_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					unsigned vmid, uint64_t pd_addw)
{
	u32 extwa_bits = (SDMA_POWW_WEG_MEM_EXTWA_OP(0) |
			  SDMA_POWW_WEG_MEM_EXTWA_FUNC(0)); /* awways */

	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_POWW_WEG_MEM, 0, extwa_bits));
	amdgpu_wing_wwite(wing, mmVM_INVAWIDATE_WEQUEST << 2);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, 0); /* wefewence */
	amdgpu_wing_wwite(wing, 0); /* mask */
	amdgpu_wing_wwite(wing, (0xfff << 16) | 10); /* wetwy count, poww intewvaw */
}

static void cik_sdma_wing_emit_wweg(stwuct amdgpu_wing *wing,
				    uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, vaw);
}

static void cik_enabwe_sdma_mgcg(stwuct amdgpu_device *adev,
				 boow enabwe)
{
	u32 owig, data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_MGCG)) {
		WWEG32(mmSDMA0_CWK_CTWW + SDMA0_WEGISTEW_OFFSET, 0x00000100);
		WWEG32(mmSDMA0_CWK_CTWW + SDMA1_WEGISTEW_OFFSET, 0x00000100);
	} ewse {
		owig = data = WWEG32(mmSDMA0_CWK_CTWW + SDMA0_WEGISTEW_OFFSET);
		data |= 0xff000000;
		if (data != owig)
			WWEG32(mmSDMA0_CWK_CTWW + SDMA0_WEGISTEW_OFFSET, data);

		owig = data = WWEG32(mmSDMA0_CWK_CTWW + SDMA1_WEGISTEW_OFFSET);
		data |= 0xff000000;
		if (data != owig)
			WWEG32(mmSDMA0_CWK_CTWW + SDMA1_WEGISTEW_OFFSET, data);
	}
}

static void cik_enabwe_sdma_mgws(stwuct amdgpu_device *adev,
				 boow enabwe)
{
	u32 owig, data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_WS)) {
		owig = data = WWEG32(mmSDMA0_POWEW_CNTW + SDMA0_WEGISTEW_OFFSET);
		data |= 0x100;
		if (owig != data)
			WWEG32(mmSDMA0_POWEW_CNTW + SDMA0_WEGISTEW_OFFSET, data);

		owig = data = WWEG32(mmSDMA0_POWEW_CNTW + SDMA1_WEGISTEW_OFFSET);
		data |= 0x100;
		if (owig != data)
			WWEG32(mmSDMA0_POWEW_CNTW + SDMA1_WEGISTEW_OFFSET, data);
	} ewse {
		owig = data = WWEG32(mmSDMA0_POWEW_CNTW + SDMA0_WEGISTEW_OFFSET);
		data &= ~0x100;
		if (owig != data)
			WWEG32(mmSDMA0_POWEW_CNTW + SDMA0_WEGISTEW_OFFSET, data);

		owig = data = WWEG32(mmSDMA0_POWEW_CNTW + SDMA1_WEGISTEW_OFFSET);
		data &= ~0x100;
		if (owig != data)
			WWEG32(mmSDMA0_POWEW_CNTW + SDMA1_WEGISTEW_OFFSET, data);
	}
}

static int cik_sdma_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	adev->sdma.num_instances = SDMA_MAX_INSTANCE;

	w = cik_sdma_init_micwocode(adev);
	if (w)
		wetuwn w;

	cik_sdma_set_wing_funcs(adev);
	cik_sdma_set_iwq_funcs(adev);
	cik_sdma_set_buffew_funcs(adev);
	cik_sdma_set_vm_pte_funcs(adev);

	wetuwn 0;
}

static int cik_sdma_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w, i;

	/* SDMA twap event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 224,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	/* SDMA Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 241,
			      &adev->sdma.iwwegaw_inst_iwq);
	if (w)
		wetuwn w;

	/* SDMA Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 247,
			      &adev->sdma.iwwegaw_inst_iwq);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		wing->wing_obj = NUWW;
		spwintf(wing->name, "sdma%d", i);
		w = amdgpu_wing_init(adev, wing, 1024,
				     &adev->sdma.twap_iwq,
				     (i == 0) ? AMDGPU_SDMA_IWQ_INSTANCE0 :
				     AMDGPU_SDMA_IWQ_INSTANCE1,
				     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;
	}

	wetuwn w;
}

static int cik_sdma_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_wing_fini(&adev->sdma.instance[i].wing);

	cik_sdma_fwee_micwocode(adev);
	wetuwn 0;
}

static int cik_sdma_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = cik_sdma_stawt(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int cik_sdma_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cik_ctx_switch_enabwe(adev, fawse);
	cik_sdma_enabwe(adev, fawse);

	wetuwn 0;
}

static int cik_sdma_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn cik_sdma_hw_fini(adev);
}

static int cik_sdma_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cik_sdma_soft_weset(handwe);

	wetuwn cik_sdma_hw_init(adev);
}

static boow cik_sdma_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS2);

	if (tmp & (SWBM_STATUS2__SDMA_BUSY_MASK |
				SWBM_STATUS2__SDMA1_BUSY_MASK))
	    wetuwn fawse;

	wetuwn twue;
}

static int cik_sdma_wait_fow_idwe(void *handwe)
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

static int cik_sdma_soft_weset(void *handwe)
{
	u32 swbm_soft_weset = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp;

	/* sdma0 */
	tmp = WWEG32(mmSDMA0_F32_CNTW + SDMA0_WEGISTEW_OFFSET);
	tmp |= SDMA0_F32_CNTW__HAWT_MASK;
	WWEG32(mmSDMA0_F32_CNTW + SDMA0_WEGISTEW_OFFSET, tmp);
	swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_SDMA_MASK;

	/* sdma1 */
	tmp = WWEG32(mmSDMA0_F32_CNTW + SDMA1_WEGISTEW_OFFSET);
	tmp |= SDMA0_F32_CNTW__HAWT_MASK;
	WWEG32(mmSDMA0_F32_CNTW + SDMA1_WEGISTEW_OFFSET, tmp);
	swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_SDMA1_MASK;

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

static int cik_sdma_set_twap_iwq_state(stwuct amdgpu_device *adev,
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
			sdma_cntw &= ~SDMA0_CNTW__TWAP_ENABWE_MASK;
			WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA0_WEGISTEW_OFFSET);
			sdma_cntw |= SDMA0_CNTW__TWAP_ENABWE_MASK;
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
			sdma_cntw &= ~SDMA0_CNTW__TWAP_ENABWE_MASK;
			WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(mmSDMA0_CNTW + SDMA1_WEGISTEW_OFFSET);
			sdma_cntw |= SDMA0_CNTW__TWAP_ENABWE_MASK;
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

static int cik_sdma_pwocess_twap_iwq(stwuct amdgpu_device *adev,
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

static int cik_sdma_pwocess_iwwegaw_inst_iwq(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *souwce,
					     stwuct amdgpu_iv_entwy *entwy)
{
	u8 instance_id;

	DWM_EWWOW("Iwwegaw instwuction in SDMA command stweam\n");
	instance_id = (entwy->wing_id & 0x3) >> 0;
	dwm_sched_fauwt(&adev->sdma.instance[instance_id].wing.sched);
	wetuwn 0;
}

static int cik_sdma_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	boow gate = fawse;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == AMD_CG_STATE_GATE)
		gate = twue;

	cik_enabwe_sdma_mgcg(adev, gate);
	cik_enabwe_sdma_mgws(adev, gate);

	wetuwn 0;
}

static int cik_sdma_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs cik_sdma_ip_funcs = {
	.name = "cik_sdma",
	.eawwy_init = cik_sdma_eawwy_init,
	.wate_init = NUWW,
	.sw_init = cik_sdma_sw_init,
	.sw_fini = cik_sdma_sw_fini,
	.hw_init = cik_sdma_hw_init,
	.hw_fini = cik_sdma_hw_fini,
	.suspend = cik_sdma_suspend,
	.wesume = cik_sdma_wesume,
	.is_idwe = cik_sdma_is_idwe,
	.wait_fow_idwe = cik_sdma_wait_fow_idwe,
	.soft_weset = cik_sdma_soft_weset,
	.set_cwockgating_state = cik_sdma_set_cwockgating_state,
	.set_powewgating_state = cik_sdma_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs cik_sdma_wing_funcs = {
	.type = AMDGPU_WING_TYPE_SDMA,
	.awign_mask = 0xf,
	.nop = SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = cik_sdma_wing_get_wptw,
	.get_wptw = cik_sdma_wing_get_wptw,
	.set_wptw = cik_sdma_wing_set_wptw,
	.emit_fwame_size =
		6 + /* cik_sdma_wing_emit_hdp_fwush */
		3 + /* hdp invawidate */
		6 + /* cik_sdma_wing_emit_pipewine_sync */
		CIK_FWUSH_GPU_TWB_NUM_WWEG * 3 + 6 + /* cik_sdma_wing_emit_vm_fwush */
		9 + 9 + 9, /* cik_sdma_wing_emit_fence x3 fow usew fence, vm fence */
	.emit_ib_size = 7 + 4, /* cik_sdma_wing_emit_ib */
	.emit_ib = cik_sdma_wing_emit_ib,
	.emit_fence = cik_sdma_wing_emit_fence,
	.emit_pipewine_sync = cik_sdma_wing_emit_pipewine_sync,
	.emit_vm_fwush = cik_sdma_wing_emit_vm_fwush,
	.emit_hdp_fwush = cik_sdma_wing_emit_hdp_fwush,
	.test_wing = cik_sdma_wing_test_wing,
	.test_ib = cik_sdma_wing_test_ib,
	.insewt_nop = cik_sdma_wing_insewt_nop,
	.pad_ib = cik_sdma_wing_pad_ib,
	.emit_wweg = cik_sdma_wing_emit_wweg,
};

static void cik_sdma_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->sdma.instance[i].wing.funcs = &cik_sdma_wing_funcs;
		adev->sdma.instance[i].wing.me = i;
	}
}

static const stwuct amdgpu_iwq_swc_funcs cik_sdma_twap_iwq_funcs = {
	.set = cik_sdma_set_twap_iwq_state,
	.pwocess = cik_sdma_pwocess_twap_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs cik_sdma_iwwegaw_inst_iwq_funcs = {
	.pwocess = cik_sdma_pwocess_iwwegaw_inst_iwq,
};

static void cik_sdma_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->sdma.twap_iwq.num_types = AMDGPU_SDMA_IWQ_WAST;
	adev->sdma.twap_iwq.funcs = &cik_sdma_twap_iwq_funcs;
	adev->sdma.iwwegaw_inst_iwq.funcs = &cik_sdma_iwwegaw_inst_iwq_funcs;
}

/**
 * cik_sdma_emit_copy_buffew - copy buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 * @tmz: is this a secuwe opewation
 *
 * Copy GPU buffews using the DMA engine (CIK).
 * Used by the amdgpu ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
static void cik_sdma_emit_copy_buffew(stwuct amdgpu_ib *ib,
				      uint64_t swc_offset,
				      uint64_t dst_offset,
				      uint32_t byte_count,
				      boow tmz)
{
	ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY, SDMA_COPY_SUB_OPCODE_WINEAW, 0);
	ib->ptw[ib->wength_dw++] = byte_count;
	ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
}

/**
 * cik_sdma_emit_fiww_buffew - fiww buffew using the sDMA engine
 *
 * @ib: indiwect buffew to fiww
 * @swc_data: vawue to wwite to buffew
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 *
 * Fiww GPU buffews using the DMA engine (CIK).
 */
static void cik_sdma_emit_fiww_buffew(stwuct amdgpu_ib *ib,
				      uint32_t swc_data,
				      uint64_t dst_offset,
				      uint32_t byte_count)
{
	ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_CONSTANT_FIWW, 0, 0);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = swc_data;
	ib->ptw[ib->wength_dw++] = byte_count;
}

static const stwuct amdgpu_buffew_funcs cik_sdma_buffew_funcs = {
	.copy_max_bytes = 0x1fffff,
	.copy_num_dw = 7,
	.emit_copy_buffew = cik_sdma_emit_copy_buffew,

	.fiww_max_bytes = 0x1fffff,
	.fiww_num_dw = 5,
	.emit_fiww_buffew = cik_sdma_emit_fiww_buffew,
};

static void cik_sdma_set_buffew_funcs(stwuct amdgpu_device *adev)
{
	adev->mman.buffew_funcs = &cik_sdma_buffew_funcs;
	adev->mman.buffew_funcs_wing = &adev->sdma.instance[0].wing;
}

static const stwuct amdgpu_vm_pte_funcs cik_sdma_vm_pte_funcs = {
	.copy_pte_num_dw = 7,
	.copy_pte = cik_sdma_vm_copy_pte,

	.wwite_pte = cik_sdma_vm_wwite_pte,
	.set_pte_pde = cik_sdma_vm_set_pte_pde,
};

static void cik_sdma_set_vm_pte_funcs(stwuct amdgpu_device *adev)
{
	unsigned i;

	adev->vm_managew.vm_pte_funcs = &cik_sdma_vm_pte_funcs;
	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->vm_managew.vm_pte_scheds[i] =
			&adev->sdma.instance[i].wing.sched;
	}
	adev->vm_managew.vm_pte_num_scheds = adev->sdma.num_instances;
}

const stwuct amdgpu_ip_bwock_vewsion cik_sdma_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_SDMA,
	.majow = 2,
	.minow = 0,
	.wev = 0,
	.funcs = &cik_sdma_ip_funcs,
};
