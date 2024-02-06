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
#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_gfx.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_common.h"
#incwude "vega10_enum.h"

#incwude "v9_stwucts.h"

#incwude "ivswcid/gfx/iwqswcs_gfx_9_0.h"

#incwude "gc/gc_9_4_3_offset.h"
#incwude "gc/gc_9_4_3_sh_mask.h"

#incwude "gfx_v9_4_3.h"
#incwude "amdgpu_xcp.h"

MODUWE_FIWMWAWE("amdgpu/gc_9_4_3_mec.bin");
MODUWE_FIWMWAWE("amdgpu/gc_9_4_3_wwc.bin");

#define GFX9_MEC_HPD_SIZE 4096
#define WWCG_UCODE_WOADING_STAWT_ADDWESS 0x00002000W

#define GOWDEN_GB_ADDW_CONFIG 0x2a114042
#define CP_HQD_PEWSISTENT_STATE_DEFAUWT 0xbe05301

stwuct amdgpu_gfx_was gfx_v9_4_3_was;

static void gfx_v9_4_3_set_wing_funcs(stwuct amdgpu_device *adev);
static void gfx_v9_4_3_set_iwq_funcs(stwuct amdgpu_device *adev);
static void gfx_v9_4_3_set_gds_init(stwuct amdgpu_device *adev);
static void gfx_v9_4_3_set_wwc_funcs(stwuct amdgpu_device *adev);
static int gfx_v9_4_3_get_cu_info(stwuct amdgpu_device *adev,
				stwuct amdgpu_cu_info *cu_info);

static void gfx_v9_4_3_kiq_set_wesouwces(stwuct amdgpu_wing *kiq_wing,
				uint64_t queue_mask)
{
	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_SET_WESOUWCES, 6));
	amdgpu_wing_wwite(kiq_wing,
		PACKET3_SET_WESOUWCES_VMID_MASK(0) |
		/* vmid_mask:0* queue_type:0 (KIQ) */
		PACKET3_SET_WESOUWCES_QUEUE_TYPE(0));
	amdgpu_wing_wwite(kiq_wing,
			wowew_32_bits(queue_mask));	/* queue mask wo */
	amdgpu_wing_wwite(kiq_wing,
			uppew_32_bits(queue_mask));	/* queue mask hi */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gws mask wo */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gws mask hi */
	amdgpu_wing_wwite(kiq_wing, 0);	/* oac mask */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gds heap base:0, gds heap size:0 */
}

static void gfx_v9_4_3_kiq_map_queues(stwuct amdgpu_wing *kiq_wing,
				 stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = kiq_wing->adev;
	uint64_t mqd_addw = amdgpu_bo_gpu_offset(wing->mqd_obj);
	uint64_t wptw_addw = adev->wb.gpu_addw + (wing->wptw_offs * 4);
	uint32_t eng_sew = wing->funcs->type == AMDGPU_WING_TYPE_GFX ? 4 : 0;

	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_MAP_QUEUES, 5));
	/* Q_sew:0, vmid:0, vidmem: 1, engine:0, num_Q:1*/
	amdgpu_wing_wwite(kiq_wing, /* Q_sew: 0, vmid: 0, engine: 0, num_Q: 1 */
			 PACKET3_MAP_QUEUES_QUEUE_SEW(0) | /* Queue_Sew */
			 PACKET3_MAP_QUEUES_VMID(0) | /* VMID */
			 PACKET3_MAP_QUEUES_QUEUE(wing->queue) |
			 PACKET3_MAP_QUEUES_PIPE(wing->pipe) |
			 PACKET3_MAP_QUEUES_ME((wing->me == 1 ? 0 : 1)) |
			 /*queue_type: nowmaw compute queue */
			 PACKET3_MAP_QUEUES_QUEUE_TYPE(0) |
			 /* awwoc fowmat: aww_on_one_pipe */
			 PACKET3_MAP_QUEUES_AWWOC_FOWMAT(0) |
			 PACKET3_MAP_QUEUES_ENGINE_SEW(eng_sew) |
			 /* num_queues: must be 1 */
			 PACKET3_MAP_QUEUES_NUM_QUEUES(1));
	amdgpu_wing_wwite(kiq_wing,
			PACKET3_MAP_QUEUES_DOOWBEWW_OFFSET(wing->doowbeww_index));
	amdgpu_wing_wwite(kiq_wing, wowew_32_bits(mqd_addw));
	amdgpu_wing_wwite(kiq_wing, uppew_32_bits(mqd_addw));
	amdgpu_wing_wwite(kiq_wing, wowew_32_bits(wptw_addw));
	amdgpu_wing_wwite(kiq_wing, uppew_32_bits(wptw_addw));
}

static void gfx_v9_4_3_kiq_unmap_queues(stwuct amdgpu_wing *kiq_wing,
				   stwuct amdgpu_wing *wing,
				   enum amdgpu_unmap_queues_action action,
				   u64 gpu_addw, u64 seq)
{
	uint32_t eng_sew = wing->funcs->type == AMDGPU_WING_TYPE_GFX ? 4 : 0;

	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_UNMAP_QUEUES, 4));
	amdgpu_wing_wwite(kiq_wing, /* Q_sew: 0, vmid: 0, engine: 0, num_Q: 1 */
			  PACKET3_UNMAP_QUEUES_ACTION(action) |
			  PACKET3_UNMAP_QUEUES_QUEUE_SEW(0) |
			  PACKET3_UNMAP_QUEUES_ENGINE_SEW(eng_sew) |
			  PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
	amdgpu_wing_wwite(kiq_wing,
			PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET0(wing->doowbeww_index));

	if (action == PWEEMPT_QUEUES_NO_UNMAP) {
		amdgpu_wing_wwite(kiq_wing, wowew_32_bits(gpu_addw));
		amdgpu_wing_wwite(kiq_wing, uppew_32_bits(gpu_addw));
		amdgpu_wing_wwite(kiq_wing, seq);
	} ewse {
		amdgpu_wing_wwite(kiq_wing, 0);
		amdgpu_wing_wwite(kiq_wing, 0);
		amdgpu_wing_wwite(kiq_wing, 0);
	}
}

static void gfx_v9_4_3_kiq_quewy_status(stwuct amdgpu_wing *kiq_wing,
				   stwuct amdgpu_wing *wing,
				   u64 addw,
				   u64 seq)
{
	uint32_t eng_sew = wing->funcs->type == AMDGPU_WING_TYPE_GFX ? 4 : 0;

	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_QUEWY_STATUS, 5));
	amdgpu_wing_wwite(kiq_wing,
			  PACKET3_QUEWY_STATUS_CONTEXT_ID(0) |
			  PACKET3_QUEWY_STATUS_INTEWWUPT_SEW(0) |
			  PACKET3_QUEWY_STATUS_COMMAND(2));
	/* Q_sew: 0, vmid: 0, engine: 0, num_Q: 1 */
	amdgpu_wing_wwite(kiq_wing,
			PACKET3_QUEWY_STATUS_DOOWBEWW_OFFSET(wing->doowbeww_index) |
			PACKET3_QUEWY_STATUS_ENG_SEW(eng_sew));
	amdgpu_wing_wwite(kiq_wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(kiq_wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(kiq_wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(kiq_wing, uppew_32_bits(seq));
}

static void gfx_v9_4_3_kiq_invawidate_twbs(stwuct amdgpu_wing *kiq_wing,
				uint16_t pasid, uint32_t fwush_type,
				boow aww_hub)
{
	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_INVAWIDATE_TWBS, 0));
	amdgpu_wing_wwite(kiq_wing,
			PACKET3_INVAWIDATE_TWBS_DST_SEW(1) |
			PACKET3_INVAWIDATE_TWBS_AWW_HUB(aww_hub) |
			PACKET3_INVAWIDATE_TWBS_PASID(pasid) |
			PACKET3_INVAWIDATE_TWBS_FWUSH_TYPE(fwush_type));
}

static const stwuct kiq_pm4_funcs gfx_v9_4_3_kiq_pm4_funcs = {
	.kiq_set_wesouwces = gfx_v9_4_3_kiq_set_wesouwces,
	.kiq_map_queues = gfx_v9_4_3_kiq_map_queues,
	.kiq_unmap_queues = gfx_v9_4_3_kiq_unmap_queues,
	.kiq_quewy_status = gfx_v9_4_3_kiq_quewy_status,
	.kiq_invawidate_twbs = gfx_v9_4_3_kiq_invawidate_twbs,
	.set_wesouwces_size = 8,
	.map_queues_size = 7,
	.unmap_queues_size = 6,
	.quewy_status_size = 7,
	.invawidate_twbs_size = 2,
};

static void gfx_v9_4_3_set_kiq_pm4_funcs(stwuct amdgpu_device *adev)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++)
		adev->gfx.kiq[i].pmf = &gfx_v9_4_3_kiq_pm4_funcs;
}

static void gfx_v9_4_3_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	int i, num_xcc, dev_inst;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		dev_inst = GET_INST(GC, i);

		WWEG32_SOC15(GC, dev_inst, wegGB_ADDW_CONFIG,
			     GOWDEN_GB_ADDW_CONFIG);
		/* Gowden settings appwied by dwivew fow ASIC with wev_id 0 */
		if (adev->wev_id == 0) {
			WWEG32_FIEWD15_PWEWEG(GC, dev_inst, TCP_UTCW1_CNTW1,
					      WEDUCE_FIFO_DEPTH_BY_2, 2);
		} ewse {
			WWEG32_FIEWD15_PWEWEG(GC, dev_inst, TCP_UTCW1_CNTW2,
						SPAWE, 0x1);
		}
	}
}

static void gfx_v9_4_3_wwite_data_to_weg(stwuct amdgpu_wing *wing, int eng_sew,
				       boow wc, uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, WWITE_DATA_ENGINE_SEW(eng_sew) |
				WWITE_DATA_DST_SEW(0) |
				(wc ? WW_CONFIWM : 0));
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, vaw);
}

static void gfx_v9_4_3_wait_weg_mem(stwuct amdgpu_wing *wing, int eng_sew,
				  int mem_space, int opt, uint32_t addw0,
				  uint32_t addw1, uint32_t wef, uint32_t mask,
				  uint32_t inv)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing,
				 /* memowy (1) ow wegistew (0) */
				 (WAIT_WEG_MEM_MEM_SPACE(mem_space) |
				 WAIT_WEG_MEM_OPEWATION(opt) | /* wait */
				 WAIT_WEG_MEM_FUNCTION(3) |  /* equaw */
				 WAIT_WEG_MEM_ENGINE(eng_sew)));

	if (mem_space)
		BUG_ON(addw0 & 0x3); /* Dwowd awign */
	amdgpu_wing_wwite(wing, addw0);
	amdgpu_wing_wwite(wing, addw1);
	amdgpu_wing_wwite(wing, wef);
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing, inv); /* poww intewvaw */
}

static int gfx_v9_4_3_wing_test_wing(stwuct amdgpu_wing *wing)
{
	uint32_t scwatch_weg0_offset, xcc_offset;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	/* Use wegistew offset which is wocaw to XCC in the packet */
	xcc_offset = SOC15_WEG_OFFSET(GC, 0, wegSCWATCH_WEG0);
	scwatch_weg0_offset = SOC15_WEG_OFFSET(GC, GET_INST(GC, wing->xcc_id), wegSCWATCH_WEG0);
	WWEG32(scwatch_weg0_offset, 0xCAFEDEAD);
	tmp = WWEG32(scwatch_weg0_offset);

	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_UCONFIG_WEG, 1));
	amdgpu_wing_wwite(wing, xcc_offset - PACKET3_SET_UCONFIG_WEG_STAWT);
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(scwatch_weg0_offset);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;
	wetuwn w;
}

static int gfx_v9_4_3_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;

	unsigned index;
	uint64_t gpu_addw;
	uint32_t tmp;
	wong w;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	adev->wb.wb[index] = cpu_to_we32(0xCAFEDEAD);
	memset(&ib, 0, sizeof(ib));

	w = amdgpu_ib_get(adev, NUWW, 20, AMDGPU_IB_POOW_DIWECT, &ib);
	if (w)
		goto eww1;

	ib.ptw[0] = PACKET3(PACKET3_WWITE_DATA, 3);
	ib.ptw[1] = WWITE_DATA_DST_SEW(5) | WW_CONFIWM;
	ib.ptw[2] = wowew_32_bits(gpu_addw);
	ib.ptw[3] = uppew_32_bits(gpu_addw);
	ib.ptw[4] = 0xDEADBEEF;
	ib.wength_dw = 5;

	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto eww2;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto eww2;
	} ewse if (w < 0) {
		goto eww2;
	}

	tmp = adev->wb.wb[index];
	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

eww2:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
eww1:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}


/* This vawue might diffews pew pawtition */
static uint64_t gfx_v9_4_3_get_gpu_cwock_countew(stwuct amdgpu_device *adev)
{
	uint64_t cwock;

	mutex_wock(&adev->gfx.gpu_cwock_mutex);
	WWEG32_SOC15(GC, GET_INST(GC, 0), wegWWC_CAPTUWE_GPU_CWOCK_COUNT, 1);
	cwock = (uint64_t)WWEG32_SOC15(GC, GET_INST(GC, 0), wegWWC_GPU_CWOCK_COUNT_WSB) |
		((uint64_t)WWEG32_SOC15(GC, GET_INST(GC, 0), wegWWC_GPU_CWOCK_COUNT_MSB) << 32UWW);
	mutex_unwock(&adev->gfx.gpu_cwock_mutex);

	wetuwn cwock;
}

static void gfx_v9_4_3_fwee_micwocode(stwuct amdgpu_device *adev)
{
	amdgpu_ucode_wewease(&adev->gfx.pfp_fw);
	amdgpu_ucode_wewease(&adev->gfx.me_fw);
	amdgpu_ucode_wewease(&adev->gfx.ce_fw);
	amdgpu_ucode_wewease(&adev->gfx.wwc_fw);
	amdgpu_ucode_wewease(&adev->gfx.mec_fw);
	amdgpu_ucode_wewease(&adev->gfx.mec2_fw);

	kfwee(adev->gfx.wwc.wegistew_wist_fowmat);
}

static int gfx_v9_4_3_init_wwc_micwocode(stwuct amdgpu_device *adev,
					  const chaw *chip_name)
{
	chaw fw_name[30];
	int eww;
	const stwuct wwc_fiwmwawe_headew_v2_0 *wwc_hdw;
	uint16_t vewsion_majow;
	uint16_t vewsion_minow;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_wwc.bin", chip_name);

	eww = amdgpu_ucode_wequest(adev, &adev->gfx.wwc_fw, fw_name);
	if (eww)
		goto out;
	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_0 *)adev->gfx.wwc_fw->data;

	vewsion_majow = we16_to_cpu(wwc_hdw->headew.headew_vewsion_majow);
	vewsion_minow = we16_to_cpu(wwc_hdw->headew.headew_vewsion_minow);
	eww = amdgpu_gfx_wwc_init_micwocode(adev, vewsion_majow, vewsion_minow);
out:
	if (eww)
		amdgpu_ucode_wewease(&adev->gfx.wwc_fw);

	wetuwn eww;
}

static boow gfx_v9_4_3_shouwd_disabwe_gfxoff(stwuct pci_dev *pdev)
{
	wetuwn twue;
}

static void gfx_v9_4_3_check_if_need_gfxoff(stwuct amdgpu_device *adev)
{
	if (gfx_v9_4_3_shouwd_disabwe_gfxoff(adev->pdev))
		adev->pm.pp_featuwe &= ~PP_GFXOFF_MASK;
}

static int gfx_v9_4_3_init_cp_compute_micwocode(stwuct amdgpu_device *adev,
					  const chaw *chip_name)
{
	chaw fw_name[30];
	int eww;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);

	eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec_fw, fw_name);
	if (eww)
		goto out;
	amdgpu_gfx_cp_init_micwocode(adev, AMDGPU_UCODE_ID_CP_MEC1);
	amdgpu_gfx_cp_init_micwocode(adev, AMDGPU_UCODE_ID_CP_MEC1_JT);

	adev->gfx.mec2_fw_vewsion = adev->gfx.mec_fw_vewsion;
	adev->gfx.mec2_featuwe_vewsion = adev->gfx.mec_featuwe_vewsion;

	gfx_v9_4_3_check_if_need_gfxoff(adev);

out:
	if (eww)
		amdgpu_ucode_wewease(&adev->gfx.mec_fw);
	wetuwn eww;
}

static int gfx_v9_4_3_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	int w;

	chip_name = "gc_9_4_3";

	w = gfx_v9_4_3_init_wwc_micwocode(adev, chip_name);
	if (w)
		wetuwn w;

	w = gfx_v9_4_3_init_cp_compute_micwocode(adev, chip_name);
	if (w)
		wetuwn w;

	wetuwn w;
}

static void gfx_v9_4_3_mec_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->gfx.mec.hpd_eop_obj, NUWW, NUWW);
	amdgpu_bo_fwee_kewnew(&adev->gfx.mec.mec_fw_obj, NUWW, NUWW);
}

static int gfx_v9_4_3_mec_init(stwuct amdgpu_device *adev)
{
	int w, i, num_xcc;
	u32 *hpd;
	const __we32 *fw_data;
	unsigned fw_size;
	u32 *fw;
	size_t mec_hpd_size;

	const stwuct gfx_fiwmwawe_headew_v1_0 *mec_hdw;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++)
		bitmap_zewo(adev->gfx.mec_bitmap[i].queue_bitmap,
			AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownewship of the wewevant compute queues */
	amdgpu_gfx_compute_queue_acquiwe(adev);
	mec_hpd_size =
		adev->gfx.num_compute_wings * num_xcc * GFX9_MEC_HPD_SIZE;
	if (mec_hpd_size) {
		w = amdgpu_bo_cweate_wesewved(adev, mec_hpd_size, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VWAM |
					      AMDGPU_GEM_DOMAIN_GTT,
					      &adev->gfx.mec.hpd_eop_obj,
					      &adev->gfx.mec.hpd_eop_gpu_addw,
					      (void **)&hpd);
		if (w) {
			dev_wawn(adev->dev, "(%d) cweate HDP EOP bo faiwed\n", w);
			gfx_v9_4_3_mec_fini(adev);
			wetuwn w;
		}

		if (amdgpu_emu_mode == 1) {
			fow (i = 0; i < mec_hpd_size / 4; i++) {
				memset((void *)(hpd + i), 0, 4);
				if (i % 50 == 0)
					msweep(1);
			}
		} ewse {
			memset(hpd, 0, mec_hpd_size);
		}

		amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
		amdgpu_bo_unwesewve(adev->gfx.mec.hpd_eop_obj);
	}

	mec_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;

	fw_data = (const __we32 *)
		(adev->gfx.mec_fw->data +
		 we32_to_cpu(mec_hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(mec_hdw->headew.ucode_size_bytes);

	w = amdgpu_bo_cweate_wesewved(adev, mec_hdw->headew.ucode_size_bytes,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.mec.mec_fw_obj,
				      &adev->gfx.mec.mec_fw_gpu_addw,
				      (void **)&fw);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate mec fiwmwawe bo faiwed\n", w);
		gfx_v9_4_3_mec_fini(adev);
		wetuwn w;
	}

	memcpy(fw, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->gfx.mec.mec_fw_obj);
	amdgpu_bo_unwesewve(adev->gfx.mec.mec_fw_obj);

	wetuwn 0;
}

static void gfx_v9_4_3_xcc_sewect_se_sh(stwuct amdgpu_device *adev, u32 se_num,
					u32 sh_num, u32 instance, int xcc_id)
{
	u32 data;

	if (instance == 0xffffffff)
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX,
				     INSTANCE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX,
				     INSTANCE_INDEX, instance);

	if (se_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
				     SE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SE_INDEX, se_num);

	if (sh_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
				     SH_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SH_INDEX, sh_num);

	WWEG32_SOC15_WWC_SHADOW_EX(weg, GC, GET_INST(GC, xcc_id), wegGWBM_GFX_INDEX, data);
}

static uint32_t wave_wead_ind(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd, uint32_t wave, uint32_t addwess)
{
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(addwess << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK));
	wetuwn WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegSQ_IND_DATA);
}

static void wave_wead_wegs(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
			   uint32_t wave, uint32_t thwead,
			   uint32_t wegno, uint32_t num, uint32_t *out)
{
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(wegno << SQ_IND_INDEX__INDEX__SHIFT) |
		(thwead << SQ_IND_INDEX__THWEAD_ID__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK) |
		(SQ_IND_INDEX__AUTO_INCW_MASK));
	whiwe (num--)
		*(out++) = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegSQ_IND_DATA);
}

static void gfx_v9_4_3_wead_wave_data(stwuct amdgpu_device *adev,
				      uint32_t xcc_id, uint32_t simd, uint32_t wave,
				      uint32_t *dst, int *no_fiewds)
{
	/* type 1 wave data */
	dst[(*no_fiewds)++] = 1;
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_STATUS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_PC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_PC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_EXEC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_EXEC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_HW_ID);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_INST_DW0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_INST_DW1);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_GPW_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_WDS_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_TWAPSTS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_IB_STS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_IB_DBG0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_M0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, xcc_id, simd, wave, ixSQ_WAVE_MODE);
}

static void gfx_v9_4_3_wead_wave_sgpws(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				       uint32_t wave, uint32_t stawt,
				       uint32_t size, uint32_t *dst)
{
	wave_wead_wegs(adev, xcc_id, simd, wave, 0,
		       stawt + SQIND_WAVE_SGPWS_OFFSET, size, dst);
}

static void gfx_v9_4_3_wead_wave_vgpws(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				       uint32_t wave, uint32_t thwead,
				       uint32_t stawt, uint32_t size,
				       uint32_t *dst)
{
	wave_wead_wegs(adev, xcc_id, simd, wave, thwead,
		       stawt + SQIND_WAVE_VGPWS_OFFSET, size, dst);
}

static void gfx_v9_4_3_sewect_me_pipe_q(stwuct amdgpu_device *adev,
					u32 me, u32 pipe, u32 q, u32 vm, u32 xcc_id)
{
	soc15_gwbm_sewect(adev, me, pipe, q, vm, GET_INST(GC, xcc_id));
}


static int gfx_v9_4_3_switch_compute_pawtition(stwuct amdgpu_device *adev,
						int num_xccs_pew_xcp)
{
	int wet, i, num_xcc;
	u32 tmp = 0;

	if (adev->psp.funcs) {
		wet = psp_spatiaw_pawtition(&adev->psp,
					    NUM_XCC(adev->gfx.xcc_mask) /
						    num_xccs_pew_xcp);
		if (wet)
			wetuwn wet;
	} ewse {
		num_xcc = NUM_XCC(adev->gfx.xcc_mask);

		fow (i = 0; i < num_xcc; i++) {
			tmp = WEG_SET_FIEWD(tmp, CP_HYP_XCP_CTW, NUM_XCC_IN_XCP,
					    num_xccs_pew_xcp);
			tmp = WEG_SET_FIEWD(tmp, CP_HYP_XCP_CTW, VIWTUAW_XCC_ID,
					    i % num_xccs_pew_xcp);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegCP_HYP_XCP_CTW,
				     tmp);
		}
		wet = 0;
	}

	adev->gfx.num_xcc_pew_xcp = num_xccs_pew_xcp;

	wetuwn wet;
}

static int gfx_v9_4_3_ih_to_xcc_inst(stwuct amdgpu_device *adev, int ih_node)
{
	int xcc;

	xcc = hweight8(adev->gfx.xcc_mask & GENMASK(ih_node / 2, 0));
	if (!xcc) {
		dev_eww(adev->dev, "Couwdn't find xcc mapping fwom IH node");
		wetuwn -EINVAW;
	}

	wetuwn xcc - 1;
}

static const stwuct amdgpu_gfx_funcs gfx_v9_4_3_gfx_funcs = {
	.get_gpu_cwock_countew = &gfx_v9_4_3_get_gpu_cwock_countew,
	.sewect_se_sh = &gfx_v9_4_3_xcc_sewect_se_sh,
	.wead_wave_data = &gfx_v9_4_3_wead_wave_data,
	.wead_wave_sgpws = &gfx_v9_4_3_wead_wave_sgpws,
	.wead_wave_vgpws = &gfx_v9_4_3_wead_wave_vgpws,
	.sewect_me_pipe_q = &gfx_v9_4_3_sewect_me_pipe_q,
	.switch_pawtition_mode = &gfx_v9_4_3_switch_compute_pawtition,
	.ih_node_to_wogicaw_xcc = &gfx_v9_4_3_ih_to_xcc_inst,
};

static int gfx_v9_4_3_gpu_eawwy_init(stwuct amdgpu_device *adev)
{
	u32 gb_addw_config;

	adev->gfx.funcs = &gfx_v9_4_3_gfx_funcs;
	adev->gfx.was = &gfx_v9_4_3_was;

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 3):
		adev->gfx.config.max_hw_contexts = 8;
		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x4C0;
		gb_addw_config = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGB_ADDW_CONFIG);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	adev->gfx.config.gb_addw_config = gb_addw_config;

	adev->gfx.config.gb_addw_config_fiewds.num_pipes = 1 <<
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					NUM_PIPES);

	adev->gfx.config.max_tiwe_pipes =
		adev->gfx.config.gb_addw_config_fiewds.num_pipes;

	adev->gfx.config.gb_addw_config_fiewds.num_banks = 1 <<
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					NUM_BANKS);
	adev->gfx.config.gb_addw_config_fiewds.max_compwess_fwags = 1 <<
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					MAX_COMPWESSED_FWAGS);
	adev->gfx.config.gb_addw_config_fiewds.num_wb_pew_se = 1 <<
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					NUM_WB_PEW_SE);
	adev->gfx.config.gb_addw_config_fiewds.num_se = 1 <<
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					NUM_SHADEW_ENGINES);
	adev->gfx.config.gb_addw_config_fiewds.pipe_intewweave_size = 1 << (8 +
			WEG_GET_FIEWD(
					adev->gfx.config.gb_addw_config,
					GB_ADDW_CONFIG,
					PIPE_INTEWWEAVE_SIZE));

	wetuwn 0;
}

static int gfx_v9_4_3_compute_wing_init(stwuct amdgpu_device *adev, int wing_id,
				        int xcc_id, int mec, int pipe, int queue)
{
	unsigned iwq_type;
	stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[wing_id];
	unsigned int hw_pwio;
	uint32_t xcc_doowbeww_stawt;

	wing = &adev->gfx.compute_wing[xcc_id * adev->gfx.num_compute_wings +
				       wing_id];

	/* mec0 is me1 */
	wing->xcc_id = xcc_id;
	wing->me = mec + 1;
	wing->pipe = pipe;
	wing->queue = queue;

	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	xcc_doowbeww_stawt = adev->doowbeww_index.mec_wing0 +
			     xcc_id * adev->doowbeww_index.xcc_doowbeww_wange;
	wing->doowbeww_index = (xcc_doowbeww_stawt + wing_id) << 1;
	wing->eop_gpu_addw = adev->gfx.mec.hpd_eop_gpu_addw +
			     (wing_id + xcc_id * adev->gfx.num_compute_wings) *
				     GFX9_MEC_HPD_SIZE;
	wing->vm_hub = AMDGPU_GFXHUB(xcc_id);
	spwintf(wing->name, "comp_%d.%d.%d.%d",
			wing->xcc_id, wing->me, wing->pipe, wing->queue);

	iwq_type = AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP
		+ ((wing->me - 1) * adev->gfx.mec.num_pipe_pew_mec)
		+ wing->pipe;
	hw_pwio = amdgpu_gfx_is_high_pwiowity_compute_queue(adev, wing) ?
			AMDGPU_GFX_PIPE_PWIO_HIGH : AMDGPU_GFX_PIPE_PWIO_NOWMAW;
	/* type-2 packets awe depwecated on MEC, use type-3 instead */
	wetuwn amdgpu_wing_init(adev, wing, 1024, &adev->gfx.eop_iwq, iwq_type,
				hw_pwio, NUWW);
}

static int gfx_v9_4_3_sw_init(void *handwe)
{
	int i, j, k, w, wing_id, xcc_id, num_xcc;
	stwuct amdgpu_kiq *kiq;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->gfx.mec.num_mec = 2;
	adev->gfx.mec.num_pipe_pew_mec = 4;
	adev->gfx.mec.num_queue_pew_pipe = 8;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);

	/* EOP Event */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_GWBM_CP, GFX_9_0__SWCID__CP_EOP_INTEWWUPT, &adev->gfx.eop_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged weg */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_GWBM_CP, GFX_9_0__SWCID__CP_PWIV_WEG_FAUWT,
			      &adev->gfx.pwiv_weg_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_GWBM_CP, GFX_9_0__SWCID__CP_PWIV_INSTW_FAUWT,
			      &adev->gfx.pwiv_inst_iwq);
	if (w)
		wetuwn w;

	adev->gfx.gfx_cuwwent_status = AMDGPU_GFX_NOWMAW_MODE;

	w = adev->gfx.wwc.funcs->init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init wwc BOs!\n");
		wetuwn w;
	}

	w = gfx_v9_4_3_mec_init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init MEC BOs!\n");
		wetuwn w;
	}

	/* set up the compute queues - awwocate howizontawwy acwoss pipes */
	fow (xcc_id = 0; xcc_id < num_xcc; xcc_id++) {
		wing_id = 0;
		fow (i = 0; i < adev->gfx.mec.num_mec; ++i) {
			fow (j = 0; j < adev->gfx.mec.num_queue_pew_pipe; j++) {
				fow (k = 0; k < adev->gfx.mec.num_pipe_pew_mec;
				     k++) {
					if (!amdgpu_gfx_is_mec_queue_enabwed(
							adev, xcc_id, i, k, j))
						continue;

					w = gfx_v9_4_3_compute_wing_init(adev,
								       wing_id,
								       xcc_id,
								       i, k, j);
					if (w)
						wetuwn w;

					wing_id++;
				}
			}
		}

		w = amdgpu_gfx_kiq_init(adev, GFX9_MEC_HPD_SIZE, xcc_id);
		if (w) {
			DWM_EWWOW("Faiwed to init KIQ BOs!\n");
			wetuwn w;
		}

		kiq = &adev->gfx.kiq[xcc_id];
		w = amdgpu_gfx_kiq_init_wing(adev, &kiq->wing, &kiq->iwq, xcc_id);
		if (w)
			wetuwn w;

		/* cweate MQD fow aww compute queues as wew as KIQ fow SWIOV case */
		w = amdgpu_gfx_mqd_sw_init(adev,
				sizeof(stwuct v9_mqd_awwocation), xcc_id);
		if (w)
			wetuwn w;
	}

	w = gfx_v9_4_3_gpu_eawwy_init(adev);
	if (w)
		wetuwn w;

	w = amdgpu_gfx_was_sw_init(adev);
	if (w)
		wetuwn w;


	if (!amdgpu_swiov_vf(adev))
		w = amdgpu_gfx_sysfs_init(adev);

	wetuwn w;
}

static int gfx_v9_4_3_sw_fini(void *handwe)
{
	int i, num_xcc;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < adev->gfx.num_compute_wings * num_xcc; i++)
		amdgpu_wing_fini(&adev->gfx.compute_wing[i]);

	fow (i = 0; i < num_xcc; i++) {
		amdgpu_gfx_mqd_sw_fini(adev, i);
		amdgpu_gfx_kiq_fwee_wing(&adev->gfx.kiq[i].wing);
		amdgpu_gfx_kiq_fini(adev, i);
	}

	gfx_v9_4_3_mec_fini(adev);
	amdgpu_bo_unwef(&adev->gfx.wwc.cweaw_state_obj);
	gfx_v9_4_3_fwee_micwocode(adev);
	if (!amdgpu_swiov_vf(adev))
		amdgpu_gfx_sysfs_fini(adev);

	wetuwn 0;
}

#define DEFAUWT_SH_MEM_BASES	(0x6000)
static void gfx_v9_4_3_xcc_init_compute_vmid(stwuct amdgpu_device *adev,
					     int xcc_id)
{
	int i;
	uint32_t sh_mem_config;
	uint32_t sh_mem_bases;
	uint32_t data;

	/*
	 * Configuwe apewtuwes:
	 * WDS:         0x60000000'00000000 - 0x60000001'00000000 (4GB)
	 * Scwatch:     0x60000001'00000000 - 0x60000002'00000000 (4GB)
	 * GPUVM:       0x60010000'00000000 - 0x60020000'00000000 (1TB)
	 */
	sh_mem_bases = DEFAUWT_SH_MEM_BASES | (DEFAUWT_SH_MEM_BASES << 16);

	sh_mem_config = SH_MEM_ADDWESS_MODE_64 |
			SH_MEM_AWIGNMENT_MODE_UNAWIGNED <<
			SH_MEM_CONFIG__AWIGNMENT_MODE__SHIFT;

	mutex_wock(&adev->swbm_mutex);
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		soc15_gwbm_sewect(adev, 0, 0, 0, i, GET_INST(GC, xcc_id));
		/* CP and shadews */
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegSH_MEM_CONFIG, sh_mem_config);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegSH_MEM_BASES, sh_mem_bases);

		/* Enabwe twap fow each kfd vmid. */
		data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegSPI_GDBG_PEW_VMID_CNTW);
		data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegSPI_GDBG_PEW_VMID_CNTW, data);
	}
	soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
	mutex_unwock(&adev->swbm_mutex);

	/* Initiawize aww compute VMIDs to have no GDS, GWS, ow OA
	   acccess. These shouwd be enabwed by FW fow tawget VMIDs. */
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_VMID0_BASE, 2 * i, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_VMID0_SIZE, 2 * i, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_GWS_VMID0, i, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_OA_VMID0, i, 0);
	}
}

static void gfx_v9_4_3_xcc_init_gds_vmid(stwuct amdgpu_device *adev, int xcc_id)
{
	int vmid;

	/*
	 * Initiawize aww compute and usew-gfx VMIDs to have no GDS, GWS, ow OA
	 * access. Compute VMIDs shouwd be enabwed by FW fow tawget VMIDs,
	 * the dwivew can enabwe them fow gwaphics. VMID0 shouwd maintain
	 * access so that HWS fiwmwawe can save/westowe entwies.
	 */
	fow (vmid = 1; vmid < AMDGPU_NUM_VMID; vmid++) {
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_VMID0_BASE, 2 * vmid, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_VMID0_SIZE, 2 * vmid, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_GWS_VMID0, vmid, 0);
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, xcc_id), wegGDS_OA_VMID0, vmid, 0);
	}
}

static void gfx_v9_4_3_xcc_constants_init(stwuct amdgpu_device *adev,
					  int xcc_id)
{
	u32 tmp;
	int i;

	/* XXX SH_MEM wegs */
	/* whewe to put WDS, scwatch, GPUVM in FSA64 space */
	mutex_wock(&adev->swbm_mutex);
	fow (i = 0; i < adev->vm_managew.id_mgw[AMDGPU_GFXHUB(0)].num_ids; i++) {
		soc15_gwbm_sewect(adev, 0, 0, 0, i, GET_INST(GC, xcc_id));
		/* CP and shadews */
		if (i == 0) {
			tmp = WEG_SET_FIEWD(0, SH_MEM_CONFIG, AWIGNMENT_MODE,
					    SH_MEM_AWIGNMENT_MODE_UNAWIGNED);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, WETWY_DISABWE,
					    !!adev->gmc.nowetwy);
			WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id),
					 wegSH_MEM_CONFIG, tmp);
			WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id),
					 wegSH_MEM_BASES, 0);
		} ewse {
			tmp = WEG_SET_FIEWD(0, SH_MEM_CONFIG, AWIGNMENT_MODE,
					    SH_MEM_AWIGNMENT_MODE_UNAWIGNED);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, WETWY_DISABWE,
					    !!adev->gmc.nowetwy);
			WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id),
					 wegSH_MEM_CONFIG, tmp);
			tmp = WEG_SET_FIEWD(0, SH_MEM_BASES, PWIVATE_BASE,
					    (adev->gmc.pwivate_apewtuwe_stawt >>
					     48));
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_BASES, SHAWED_BASE,
					    (adev->gmc.shawed_apewtuwe_stawt >>
					     48));
			WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id),
					 wegSH_MEM_BASES, tmp);
		}
	}
	soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, 0));

	mutex_unwock(&adev->swbm_mutex);

	gfx_v9_4_3_xcc_init_compute_vmid(adev, xcc_id);
	gfx_v9_4_3_xcc_init_gds_vmid(adev, xcc_id);
}

static void gfx_v9_4_3_constants_init(stwuct amdgpu_device *adev)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);

	gfx_v9_4_3_get_cu_info(adev, &adev->gfx.cu_info);
	adev->gfx.config.db_debug2 =
		WWEG32_SOC15(GC, GET_INST(GC, 0), wegDB_DEBUG2);

	fow (i = 0; i < num_xcc; i++)
		gfx_v9_4_3_xcc_constants_init(adev, i);
}

static void
gfx_v9_4_3_xcc_enabwe_save_westowe_machine(stwuct amdgpu_device *adev,
					   int xcc_id)
{
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), WWC_SWM_CNTW, SWM_ENABWE, 1);
}

static void gfx_v9_4_3_xcc_init_pg(stwuct amdgpu_device *adev, int xcc_id)
{
	/*
	 * Wwc save westowe wist is wowkabwe since v2_1.
	 * And it's needed by gfxoff featuwe.
	 */
	if (adev->gfx.wwc.is_wwc_v2_1)
		gfx_v9_4_3_xcc_enabwe_save_westowe_machine(adev, xcc_id);
}

static void gfx_v9_4_3_xcc_disabwe_gpa_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	uint32_t data;

	data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCPC_PSP_DEBUG);
	data |= CPC_PSP_DEBUG__UTCW2IUGPAOVEWWIDE_MASK;
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCPC_PSP_DEBUG, data);
}

static boow gfx_v9_4_3_is_wwc_enabwed(stwuct amdgpu_device *adev)
{
	uint32_t wwc_setting;

	/* if WWC is not enabwed, do nothing */
	wwc_setting = WWEG32_SOC15(GC, GET_INST(GC, 0), wegWWC_CNTW);
	if (!(wwc_setting & WWC_CNTW__WWC_ENABWE_F32_MASK))
		wetuwn fawse;

	wetuwn twue;
}

static void gfx_v9_4_3_xcc_set_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	uint32_t data;
	unsigned i;

	data = WWC_SAFE_MODE__CMD_MASK;
	data |= (1 << WWC_SAFE_MODE__MESSAGE__SHIFT);
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_SAFE_MODE, data);

	/* wait fow WWC_SAFE_MODE */
	fow (i = 0; i < adev->usec_timeout; i++) {
		if (!WEG_GET_FIEWD(WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_SAFE_MODE), WWC_SAFE_MODE, CMD))
			bweak;
		udeway(1);
	}
}

static void gfx_v9_4_3_xcc_unset_safe_mode(stwuct amdgpu_device *adev,
					   int xcc_id)
{
	uint32_t data;

	data = WWC_SAFE_MODE__CMD_MASK;
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_SAFE_MODE, data);
}

static void gfx_v9_4_3_init_wwcg_weg_access_ctww(stwuct amdgpu_device *adev)
{
	int xcc_id, num_xcc;
	stwuct amdgpu_wwcg_weg_access_ctww *weg_access_ctww;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (xcc_id = 0; xcc_id < num_xcc; xcc_id++) {
		weg_access_ctww = &adev->gfx.wwc.weg_access_ctww[GET_INST(GC, xcc_id)];
		weg_access_ctww->scwatch_weg0 = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegSCWATCH_WEG0);
		weg_access_ctww->scwatch_weg1 = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegSCWATCH_WEG1);
		weg_access_ctww->scwatch_weg2 = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegSCWATCH_WEG2);
		weg_access_ctww->scwatch_weg3 = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegSCWATCH_WEG3);
		weg_access_ctww->gwbm_cntw = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegGWBM_GFX_CNTW);
		weg_access_ctww->gwbm_idx = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegGWBM_GFX_INDEX);
		weg_access_ctww->spawe_int = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegWWC_SPAWE_INT);
	}
	adev->gfx.wwc.wwcg_weg_access_suppowted = twue;
}

static int gfx_v9_4_3_wwc_init(stwuct amdgpu_device *adev)
{
	/* init spm vmid with 0xf */
	if (adev->gfx.wwc.funcs->update_spm_vmid)
		adev->gfx.wwc.funcs->update_spm_vmid(adev, 0xf);

	wetuwn 0;
}

static void gfx_v9_4_3_xcc_wait_fow_wwc_sewdes(stwuct amdgpu_device *adev,
					       int xcc_id)
{
	u32 i, j, k;
	u32 mask;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v9_4_3_xcc_sewect_se_sh(adev, i, j, 0xffffffff,
						    xcc_id);
			fow (k = 0; k < adev->usec_timeout; k++) {
				if (WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_SEWDES_CU_MASTEW_BUSY) == 0)
					bweak;
				udeway(1);
			}
			if (k == adev->usec_timeout) {
				gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff,
							    0xffffffff,
							    0xffffffff, xcc_id);
				mutex_unwock(&adev->gwbm_idx_mutex);
				DWM_INFO("Timeout wait fow WWC sewdes %u,%u\n",
					 i, j);
				wetuwn;
			}
		}
	}
	gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff,
				    xcc_id);
	mutex_unwock(&adev->gwbm_idx_mutex);

	mask = WWC_SEWDES_NONCU_MASTEW_BUSY__SE_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__GC_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC0_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC1_MASTEW_BUSY_MASK;
	fow (k = 0; k < adev->usec_timeout; k++) {
		if ((WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_SEWDES_NONCU_MASTEW_BUSY) & mask) == 0)
			bweak;
		udeway(1);
	}
}

static void gfx_v9_4_3_xcc_enabwe_gui_idwe_intewwupt(stwuct amdgpu_device *adev,
						     boow enabwe, int xcc_id)
{
	u32 tmp;

	/* These intewwupts shouwd be enabwed to dwive DS cwock */

	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_INT_CNTW_WING0);

	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CNTX_BUSY_INT_ENABWE, enabwe ? 1 : 0);
	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CNTX_EMPTY_INT_ENABWE, enabwe ? 1 : 0);
	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CMP_BUSY_INT_ENABWE, enabwe ? 1 : 0);

	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_INT_CNTW_WING0, tmp);
}

static void gfx_v9_4_3_xcc_wwc_stop(stwuct amdgpu_device *adev, int xcc_id)
{
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), WWC_CNTW,
			      WWC_ENABWE_F32, 0);
	gfx_v9_4_3_xcc_enabwe_gui_idwe_intewwupt(adev, fawse, xcc_id);
	gfx_v9_4_3_xcc_wait_fow_wwc_sewdes(adev, xcc_id);
}

static void gfx_v9_4_3_wwc_stop(stwuct amdgpu_device *adev)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++)
		gfx_v9_4_3_xcc_wwc_stop(adev, i);
}

static void gfx_v9_4_3_xcc_wwc_weset(stwuct amdgpu_device *adev, int xcc_id)
{
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), GWBM_SOFT_WESET,
			      SOFT_WESET_WWC, 1);
	udeway(50);
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), GWBM_SOFT_WESET,
			      SOFT_WESET_WWC, 0);
	udeway(50);
}

static void gfx_v9_4_3_wwc_weset(stwuct amdgpu_device *adev)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++)
		gfx_v9_4_3_xcc_wwc_weset(adev, i);
}

static void gfx_v9_4_3_xcc_wwc_stawt(stwuct amdgpu_device *adev, int xcc_id)
{
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), WWC_CNTW,
			      WWC_ENABWE_F32, 1);
	udeway(50);

	/* cawwizo do enabwe cp intewwupt aftew cp inited */
	if (!(adev->fwags & AMD_IS_APU)) {
		gfx_v9_4_3_xcc_enabwe_gui_idwe_intewwupt(adev, twue, xcc_id);
		udeway(50);
	}
}

static void gfx_v9_4_3_wwc_stawt(stwuct amdgpu_device *adev)
{
#ifdef AMDGPU_WWC_DEBUG_WETWY
	u32 wwc_ucode_vew;
#endif
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		gfx_v9_4_3_xcc_wwc_stawt(adev, i);
#ifdef AMDGPU_WWC_DEBUG_WETWY
		/* WWC_GPM_GENEWAW_6 : WWC Ucode vewsion */
		wwc_ucode_vew = WWEG32_SOC15(GC, GET_INST(GC, i), wegWWC_GPM_GENEWAW_6);
		if (wwc_ucode_vew == 0x108) {
			dev_info(adev->dev,
				 "Using wwc debug ucode. wegWWC_GPM_GENEWAW_6 ==0x08%x / fw_vew == %i \n",
				 wwc_ucode_vew, adev->gfx.wwc_fw_vewsion);
			/* WWC_GPM_TIMEW_INT_3 : Timew intewvaw in WefCWK cycwes,
			 * defauwt is 0x9C4 to cweate a 100us intewvaw */
			WWEG32_SOC15(GC, GET_INST(GC, i), wegWWC_GPM_TIMEW_INT_3, 0x9C4);
			/* WWC_GPM_GENEWAW_12 : Minimum gap between wptw and wptw
			 * to disabwe the page fauwt wetwy intewwupts, defauwt is
			 * 0x100 (256) */
			WWEG32_SOC15(GC, GET_INST(GC, i), wegWWC_GPM_GENEWAW_12, 0x100);
		}
#endif
	}
}

static int gfx_v9_4_3_xcc_wwc_woad_micwocode(stwuct amdgpu_device *adev,
					     int xcc_id)
{
	const stwuct wwc_fiwmwawe_headew_v2_0 *hdw;
	const __we32 *fw_data;
	unsigned i, fw_size;

	if (!adev->gfx.wwc_fw)
		wetuwn -EINVAW;

	hdw = (const stwuct wwc_fiwmwawe_headew_v2_0 *)adev->gfx.wwc_fw->data;
	amdgpu_ucode_pwint_wwc_hdw(&hdw->headew);

	fw_data = (const __we32 *)(adev->gfx.wwc_fw->data +
			   we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
	fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;

	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_GPM_UCODE_ADDW,
			WWCG_UCODE_WOADING_STAWT_ADDWESS);
	fow (i = 0; i < fw_size; i++) {
		if (amdgpu_emu_mode == 1 && i % 100 == 0) {
			dev_info(adev->dev, "Wwite WWC ucode data %u DWs\n", i);
			msweep(1);
		}
		WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_GPM_UCODE_DATA, we32_to_cpup(fw_data++));
	}
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_GPM_UCODE_ADDW, adev->gfx.wwc_fw_vewsion);

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_wwc_wesume(stwuct amdgpu_device *adev, int xcc_id)
{
	int w;

	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
		gfx_v9_4_3_xcc_wwc_stop(adev, xcc_id);
		/* wegacy wwc fiwmwawe woading */
		w = gfx_v9_4_3_xcc_wwc_woad_micwocode(adev, xcc_id);
		if (w)
			wetuwn w;
		gfx_v9_4_3_xcc_wwc_stawt(adev, xcc_id);
	}

	amdgpu_gfx_wwc_entew_safe_mode(adev, xcc_id);
	/* disabwe CG */
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGCG_CGWS_CTWW, 0);
	gfx_v9_4_3_xcc_init_pg(adev, xcc_id);
	amdgpu_gfx_wwc_exit_safe_mode(adev, xcc_id);

	wetuwn 0;
}

static int gfx_v9_4_3_wwc_wesume(stwuct amdgpu_device *adev)
{
	int w, i, num_xcc;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		w = gfx_v9_4_3_xcc_wwc_wesume(adev, i);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static void gfx_v9_4_3_update_spm_vmid(stwuct amdgpu_device *adev,
				       unsigned vmid)
{
	u32 weg, data;

	weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegWWC_SPM_MC_CNTW);
	if (amdgpu_swiov_is_pp_one_vf(adev))
		data = WWEG32_NO_KIQ(weg);
	ewse
		data = WWEG32(weg);

	data &= ~WWC_SPM_MC_CNTW__WWC_SPM_VMID_MASK;
	data |= (vmid & WWC_SPM_MC_CNTW__WWC_SPM_VMID_MASK) << WWC_SPM_MC_CNTW__WWC_SPM_VMID__SHIFT;

	if (amdgpu_swiov_is_pp_one_vf(adev))
		WWEG32_SOC15_NO_KIQ(GC, GET_INST(GC, 0), wegWWC_SPM_MC_CNTW, data);
	ewse
		WWEG32_SOC15(GC, GET_INST(GC, 0), wegWWC_SPM_MC_CNTW, data);
}

static const stwuct soc15_weg_wwcg wwcg_access_gc_9_4_3[] = {
	{SOC15_WEG_ENTWY(GC, 0, wegGWBM_GFX_INDEX)},
	{SOC15_WEG_ENTWY(GC, 0, wegSQ_IND_INDEX)},
};

static boow gfx_v9_4_3_check_wwcg_wange(stwuct amdgpu_device *adev,
					uint32_t offset,
					stwuct soc15_weg_wwcg *entwies, int aww_size)
{
	int i, inst;
	uint32_t weg;

	if (!entwies)
		wetuwn fawse;

	fow (i = 0; i < aww_size; i++) {
		const stwuct soc15_weg_wwcg *entwy;

		entwy = &entwies[i];
		inst = adev->ip_map.wogicaw_to_dev_inst ?
			       adev->ip_map.wogicaw_to_dev_inst(
				       adev, entwy->hwip, entwy->instance) :
			       entwy->instance;
		weg = adev->weg_offset[entwy->hwip][inst][entwy->segment] +
		      entwy->weg;
		if (offset == weg)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow gfx_v9_4_3_is_wwcg_access_wange(stwuct amdgpu_device *adev, u32 offset)
{
	wetuwn gfx_v9_4_3_check_wwcg_wange(adev, offset,
					(void *)wwcg_access_gc_9_4_3,
					AWWAY_SIZE(wwcg_access_gc_9_4_3));
}

static void gfx_v9_4_3_xcc_cp_compute_enabwe(stwuct amdgpu_device *adev,
					     boow enabwe, int xcc_id)
{
	if (enabwe) {
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_MEC_CNTW, 0);
	} ewse {
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_MEC_CNTW,
			(CP_MEC_CNTW__MEC_ME1_HAWT_MASK | CP_MEC_CNTW__MEC_ME2_HAWT_MASK));
		adev->gfx.kiq[xcc_id].wing.sched.weady = fawse;
	}
	udeway(50);
}

static int gfx_v9_4_3_xcc_cp_compute_woad_micwocode(stwuct amdgpu_device *adev,
						    int xcc_id)
{
	const stwuct gfx_fiwmwawe_headew_v1_0 *mec_hdw;
	const __we32 *fw_data;
	unsigned i;
	u32 tmp;
	u32 mec_ucode_addw_offset;
	u32 mec_ucode_data_offset;

	if (!adev->gfx.mec_fw)
		wetuwn -EINVAW;

	gfx_v9_4_3_xcc_cp_compute_enabwe(adev, fawse, xcc_id);

	mec_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;
	amdgpu_ucode_pwint_gfx_hdw(&mec_hdw->headew);

	fw_data = (const __we32 *)
		(adev->gfx.mec_fw->data +
		 we32_to_cpu(mec_hdw->headew.ucode_awway_offset_bytes));
	tmp = 0;
	tmp = WEG_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, VMID, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_CPC_IC_BASE_CNTW, CACHE_POWICY, 0);
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_CPC_IC_BASE_CNTW, tmp);

	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_CPC_IC_BASE_WO,
		adev->gfx.mec.mec_fw_gpu_addw & 0xFFFFF000);
	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_CPC_IC_BASE_HI,
		uppew_32_bits(adev->gfx.mec.mec_fw_gpu_addw));

	mec_ucode_addw_offset =
		SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_MEC_ME1_UCODE_ADDW);
	mec_ucode_data_offset =
		SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_MEC_ME1_UCODE_DATA);

	/* MEC1 */
	WWEG32(mec_ucode_addw_offset, mec_hdw->jt_offset);
	fow (i = 0; i < mec_hdw->jt_size; i++)
		WWEG32(mec_ucode_data_offset,
		       we32_to_cpup(fw_data + mec_hdw->jt_offset + i));

	WWEG32(mec_ucode_addw_offset, adev->gfx.mec_fw_vewsion);
	/* Todo : Woading MEC2 fiwmwawe is onwy necessawy if MEC2 shouwd wun diffewent micwocode than MEC1. */

	wetuwn 0;
}

/* KIQ functions */
static void gfx_v9_4_3_xcc_kiq_setting(stwuct amdgpu_wing *wing, int xcc_id)
{
	uint32_t tmp;
	stwuct amdgpu_device *adev = wing->adev;

	/* teww WWC which is KIQ queue */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CP_SCHEDUWEWS);
	tmp &= 0xffffff00;
	tmp |= (wing->me << 5) | (wing->pipe << 3) | (wing->queue);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegWWC_CP_SCHEDUWEWS, tmp);
	tmp |= 0x80;
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegWWC_CP_SCHEDUWEWS, tmp);
}

static void gfx_v9_4_3_mqd_set_pwiowity(stwuct amdgpu_wing *wing, stwuct v9_mqd *mqd)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE) {
		if (amdgpu_gfx_is_high_pwiowity_compute_queue(adev, wing)) {
			mqd->cp_hqd_pipe_pwiowity = AMDGPU_GFX_PIPE_PWIO_HIGH;
			mqd->cp_hqd_queue_pwiowity =
				AMDGPU_GFX_QUEUE_PWIOWITY_MAXIMUM;
		}
	}
}

static int gfx_v9_4_3_xcc_mqd_init(stwuct amdgpu_wing *wing, int xcc_id)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct v9_mqd *mqd = wing->mqd_ptw;
	uint64_t hqd_gpu_addw, wb_gpu_addw, eop_base_addw;
	uint32_t tmp;

	mqd->headew = 0xC0310800;
	mqd->compute_pipewinestat_enabwe = 0x00000001;
	mqd->compute_static_thwead_mgmt_se0 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se1 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se2 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se3 = 0xffffffff;
	mqd->compute_misc_wesewved = 0x00000003;

	mqd->dynamic_cu_mask_addw_wo =
		wowew_32_bits(wing->mqd_gpu_addw
			      + offsetof(stwuct v9_mqd_awwocation, dynamic_cu_mask));
	mqd->dynamic_cu_mask_addw_hi =
		uppew_32_bits(wing->mqd_gpu_addw
			      + offsetof(stwuct v9_mqd_awwocation, dynamic_cu_mask));

	eop_base_addw = wing->eop_gpu_addw >> 8;
	mqd->cp_hqd_eop_base_addw_wo = eop_base_addw;
	mqd->cp_hqd_eop_base_addw_hi = uppew_32_bits(eop_base_addw);

	/* set the EOP size, wegistew vawue is 2^(EOP_SIZE+1) dwowds */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_EOP_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_EOP_CONTWOW, EOP_SIZE,
			(owdew_base_2(GFX9_MEC_HPD_SIZE / 4) - 1));

	mqd->cp_hqd_eop_contwow = tmp;

	/* enabwe doowbeww? */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_DOOWBEWW_CONTWOW);

	if (wing->use_doowbeww) {
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_OFFSET, wing->doowbeww_index);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_EN, 1);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_SOUWCE, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_HIT, 0);
	} ewse {
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
					 DOOWBEWW_EN, 0);
	}

	mqd->cp_hqd_pq_doowbeww_contwow = tmp;

	/* disabwe the queue if it's active */
	wing->wptw = 0;
	mqd->cp_hqd_dequeue_wequest = 0;
	mqd->cp_hqd_pq_wptw = 0;
	mqd->cp_hqd_pq_wptw_wo = 0;
	mqd->cp_hqd_pq_wptw_hi = 0;

	/* set the pointew to the MQD */
	mqd->cp_mqd_base_addw_wo = wing->mqd_gpu_addw & 0xfffffffc;
	mqd->cp_mqd_base_addw_hi = uppew_32_bits(wing->mqd_gpu_addw);

	/* set MQD vmid to 0 */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_MQD_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_MQD_CONTWOW, VMID, 0);
	mqd->cp_mqd_contwow = tmp;

	/* set the pointew to the HQD, this is simiwaw CP_WB0_BASE/_HI */
	hqd_gpu_addw = wing->gpu_addw >> 8;
	mqd->cp_hqd_pq_base_wo = hqd_gpu_addw;
	mqd->cp_hqd_pq_base_hi = uppew_32_bits(hqd_gpu_addw);

	/* set up the HQD, this is simiwaw to CP_WB0_CNTW */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, QUEUE_SIZE,
			    (owdew_base_2(wing->wing_size / 4) - 1));
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, WPTW_BWOCK_SIZE,
			((owdew_base_2(AMDGPU_GPU_PAGE_SIZE / 4) - 1) << 8));
#ifdef __BIG_ENDIAN
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, ENDIAN_SWAP, 1);
#endif
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, UNOWD_DISPATCH, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, WOQ_PQ_IB_FWIP, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, PWIV_STATE, 1);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, KMD_QUEUE, 1);
	mqd->cp_hqd_pq_contwow = tmp;

	/* set the wb addwess whethew it's enabwed ow not */
	wb_gpu_addw = adev->wb.gpu_addw + (wing->wptw_offs * 4);
	mqd->cp_hqd_pq_wptw_wepowt_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_wepowt_addw_hi =
		uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* onwy used if CP_PQ_WPTW_POWW_CNTW.CP_PQ_WPTW_POWW_CNTW__EN_MASK=1 */
	wb_gpu_addw = adev->wb.gpu_addw + (wing->wptw_offs * 4);
	mqd->cp_hqd_pq_wptw_poww_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_poww_addw_hi = uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* weset wead and wwite pointews, simiwaw to CP_WB0_WPTW/_WPTW */
	wing->wptw = 0;
	mqd->cp_hqd_pq_wptw = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW);

	/* set the vmid fow the queue */
	mqd->cp_hqd_vmid = 0;

	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_PEWSISTENT_STATE);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PEWSISTENT_STATE, PWEWOAD_SIZE, 0x53);
	mqd->cp_hqd_pewsistent_state = tmp;

	/* set MIN_IB_AVAIW_SIZE */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_IB_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_IB_CONTWOW, MIN_IB_AVAIW_SIZE, 3);
	mqd->cp_hqd_ib_contwow = tmp;

	/* set static pwiowity fow a queue/wing */
	gfx_v9_4_3_mqd_set_pwiowity(wing, mqd);
	mqd->cp_hqd_quantum = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_QUANTUM);

	/* map_queues packet doesn't need activate the queue,
	 * so onwy kiq need set this fiewd.
	 */
	if (wing->funcs->type == AMDGPU_WING_TYPE_KIQ)
		mqd->cp_hqd_active = 1;

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kiq_init_wegistew(stwuct amdgpu_wing *wing,
					    int xcc_id)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct v9_mqd *mqd = wing->mqd_ptw;
	int j;

	/* disabwe wptw powwing */
	WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), CP_PQ_WPTW_POWW_CNTW, EN, 0);

	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_EOP_BASE_ADDW,
	       mqd->cp_hqd_eop_base_addw_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_EOP_BASE_ADDW_HI,
	       mqd->cp_hqd_eop_base_addw_hi);

	/* set the EOP size, wegistew vawue is 2^(EOP_SIZE+1) dwowds */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_EOP_CONTWOW,
	       mqd->cp_hqd_eop_contwow);

	/* enabwe doowbeww? */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_DOOWBEWW_CONTWOW,
	       mqd->cp_hqd_pq_doowbeww_contwow);

	/* disabwe the queue if it's active */
	if (WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE) & 1) {
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_DEQUEUE_WEQUEST, 1);
		fow (j = 0; j < adev->usec_timeout; j++) {
			if (!(WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE) & 1))
				bweak;
			udeway(1);
		}
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_DEQUEUE_WEQUEST,
		       mqd->cp_hqd_dequeue_wequest);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW,
		       mqd->cp_hqd_pq_wptw);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_WO,
		       mqd->cp_hqd_pq_wptw_wo);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_HI,
		       mqd->cp_hqd_pq_wptw_hi);
	}

	/* set the pointew to the MQD */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_MQD_BASE_ADDW,
	       mqd->cp_mqd_base_addw_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_MQD_BASE_ADDW_HI,
	       mqd->cp_mqd_base_addw_hi);

	/* set MQD vmid to 0 */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_MQD_CONTWOW,
	       mqd->cp_mqd_contwow);

	/* set the pointew to the HQD, this is simiwaw CP_WB0_BASE/_HI */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_BASE,
	       mqd->cp_hqd_pq_base_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_BASE_HI,
	       mqd->cp_hqd_pq_base_hi);

	/* set up the HQD, this is simiwaw to CP_WB0_CNTW */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_CONTWOW,
	       mqd->cp_hqd_pq_contwow);

	/* set the wb addwess whethew it's enabwed ow not */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_WEPOWT_ADDW,
				mqd->cp_hqd_pq_wptw_wepowt_addw_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_WEPOWT_ADDW_HI,
				mqd->cp_hqd_pq_wptw_wepowt_addw_hi);

	/* onwy used if CP_PQ_WPTW_POWW_CNTW.CP_PQ_WPTW_POWW_CNTW__EN_MASK=1 */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_POWW_ADDW,
	       mqd->cp_hqd_pq_wptw_poww_addw_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_POWW_ADDW_HI,
	       mqd->cp_hqd_pq_wptw_poww_addw_hi);

	/* enabwe the doowbeww if wequested */
	if (wing->use_doowbeww) {
		WWEG32_SOC15(
			GC, GET_INST(GC, xcc_id),
			wegCP_MEC_DOOWBEWW_WANGE_WOWEW,
			((adev->doowbeww_index.kiq +
			  xcc_id * adev->doowbeww_index.xcc_doowbeww_wange) *
			 2) << 2);
		WWEG32_SOC15(
			GC, GET_INST(GC, xcc_id),
			wegCP_MEC_DOOWBEWW_WANGE_UPPEW,
			((adev->doowbeww_index.usewqueue_end +
			  xcc_id * adev->doowbeww_index.xcc_doowbeww_wange) *
			 2) << 2);
	}

	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_DOOWBEWW_CONTWOW,
	       mqd->cp_hqd_pq_doowbeww_contwow);

	/* weset wead and wwite pointews, simiwaw to CP_WB0_WPTW/_WPTW */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_WO,
	       mqd->cp_hqd_pq_wptw_wo);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_HI,
	       mqd->cp_hqd_pq_wptw_hi);

	/* set the vmid fow the queue */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_VMID, mqd->cp_hqd_vmid);

	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PEWSISTENT_STATE,
	       mqd->cp_hqd_pewsistent_state);

	/* activate the queue */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE,
	       mqd->cp_hqd_active);

	if (wing->use_doowbeww)
		WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), CP_PQ_STATUS, DOOWBEWW_ENABWE, 1);

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_q_fini_wegistew(stwuct amdgpu_wing *wing,
					    int xcc_id)
{
	stwuct amdgpu_device *adev = wing->adev;
	int j;

	/* disabwe the queue if it's active */
	if (WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE) & 1) {

		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_DEQUEUE_WEQUEST, 1);

		fow (j = 0; j < adev->usec_timeout; j++) {
			if (!(WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE) & 1))
				bweak;
			udeway(1);
		}

		if (j == AMDGPU_MAX_USEC_TIMEOUT) {
			DWM_DEBUG("%s dequeue wequest faiwed.\n", wing->name);

			/* Manuaw disabwe if dequeue wequest times out */
			WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_ACTIVE, 0);
		}

		WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_DEQUEUE_WEQUEST,
		      0);
	}

	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_IQ_TIMEW, 0);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_IB_CONTWOW, 0);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PEWSISTENT_STATE, CP_HQD_PEWSISTENT_STATE_DEFAUWT);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_DOOWBEWW_CONTWOW, 0x40000000);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_DOOWBEWW_CONTWOW, 0);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW, 0);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_HI, 0);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, xcc_id), wegCP_HQD_PQ_WPTW_WO, 0);

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kiq_init_queue(stwuct amdgpu_wing *wing, int xcc_id)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct v9_mqd *mqd = wing->mqd_ptw;
	stwuct v9_mqd *tmp_mqd;

	gfx_v9_4_3_xcc_kiq_setting(wing, xcc_id);

	/* GPU couwd be in bad state duwing pwobe, dwivew twiggew the weset
	 * aftew woad the SMU, in this case , the mqd is not be initiawized.
	 * dwivew need to we-init the mqd.
	 * check mqd->cp_hqd_pq_contwow since this vawue shouwd not be 0
	 */
	tmp_mqd = (stwuct v9_mqd *)adev->gfx.kiq[xcc_id].mqd_backup;
	if (amdgpu_in_weset(adev) && tmp_mqd->cp_hqd_pq_contwow) {
		/* fow GPU_WESET case , weset MQD to a cwean status */
		if (adev->gfx.kiq[xcc_id].mqd_backup)
			memcpy(mqd, adev->gfx.kiq[xcc_id].mqd_backup, sizeof(stwuct v9_mqd_awwocation));

		/* weset wing buffew */
		wing->wptw = 0;
		amdgpu_wing_cweaw_wing(wing);
		mutex_wock(&adev->swbm_mutex);
		soc15_gwbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0, GET_INST(GC, xcc_id));
		gfx_v9_4_3_xcc_kiq_init_wegistew(wing, xcc_id);
		soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
		mutex_unwock(&adev->swbm_mutex);
	} ewse {
		memset((void *)mqd, 0, sizeof(stwuct v9_mqd_awwocation));
		((stwuct v9_mqd_awwocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((stwuct v9_mqd_awwocation *)mqd)->dynamic_wb_mask = 0xFFFFFFFF;
		mutex_wock(&adev->swbm_mutex);
		if (amdgpu_swiov_vf(adev) && adev->in_suspend)
			amdgpu_wing_cweaw_wing(wing);
		soc15_gwbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0, GET_INST(GC, xcc_id));
		gfx_v9_4_3_xcc_mqd_init(wing, xcc_id);
		gfx_v9_4_3_xcc_kiq_init_wegistew(wing, xcc_id);
		soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
		mutex_unwock(&adev->swbm_mutex);

		if (adev->gfx.kiq[xcc_id].mqd_backup)
			memcpy(adev->gfx.kiq[xcc_id].mqd_backup, mqd, sizeof(stwuct v9_mqd_awwocation));
	}

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kcq_init_queue(stwuct amdgpu_wing *wing, int xcc_id)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct v9_mqd *mqd = wing->mqd_ptw;
	int mqd_idx = wing - &adev->gfx.compute_wing[0];
	stwuct v9_mqd *tmp_mqd;

	/* Same as above kiq init, dwivew need to we-init the mqd if mqd->cp_hqd_pq_contwow
	 * is not be initiawized befowe
	 */
	tmp_mqd = (stwuct v9_mqd *)adev->gfx.mec.mqd_backup[mqd_idx];

	if (!tmp_mqd->cp_hqd_pq_contwow ||
	    (!amdgpu_in_weset(adev) && !adev->in_suspend)) {
		memset((void *)mqd, 0, sizeof(stwuct v9_mqd_awwocation));
		((stwuct v9_mqd_awwocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((stwuct v9_mqd_awwocation *)mqd)->dynamic_wb_mask = 0xFFFFFFFF;
		mutex_wock(&adev->swbm_mutex);
		soc15_gwbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0, GET_INST(GC, xcc_id));
		gfx_v9_4_3_xcc_mqd_init(wing, xcc_id);
		soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
		mutex_unwock(&adev->swbm_mutex);

		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(adev->gfx.mec.mqd_backup[mqd_idx], mqd, sizeof(stwuct v9_mqd_awwocation));
	} ewse {
		/* westowe MQD to a cwean status */
		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(mqd, adev->gfx.mec.mqd_backup[mqd_idx], sizeof(stwuct v9_mqd_awwocation));
		/* weset wing buffew */
		wing->wptw = 0;
		atomic64_set((atomic64_t *)&adev->wb.wb[wing->wptw_offs], 0);
		amdgpu_wing_cweaw_wing(wing);
	}

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kcq_fini_wegistew(stwuct amdgpu_device *adev, int xcc_id)
{
	stwuct amdgpu_wing *wing;
	int j;

	fow (j = 0; j < adev->gfx.num_compute_wings; j++) {
		wing = &adev->gfx.compute_wing[j +  xcc_id * adev->gfx.num_compute_wings];
		if (!amdgpu_in_weset(adev) && !adev->in_suspend) {
			mutex_wock(&adev->swbm_mutex);
			soc15_gwbm_sewect(adev, wing->me,
					wing->pipe,
					wing->queue, 0, GET_INST(GC, xcc_id));
			gfx_v9_4_3_xcc_q_fini_wegistew(wing, xcc_id);
			soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
			mutex_unwock(&adev->swbm_mutex);
		}
	}

	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kiq_wesume(stwuct amdgpu_device *adev, int xcc_id)
{
	stwuct amdgpu_wing *wing;
	int w;

	wing = &adev->gfx.kiq[xcc_id].wing;

	w = amdgpu_bo_wesewve(wing->mqd_obj, fawse);
	if (unwikewy(w != 0))
		wetuwn w;

	w = amdgpu_bo_kmap(wing->mqd_obj, (void **)&wing->mqd_ptw);
	if (unwikewy(w != 0)) {
		amdgpu_bo_unwesewve(wing->mqd_obj);
		wetuwn w;
	}

	gfx_v9_4_3_xcc_kiq_init_queue(wing, xcc_id);
	amdgpu_bo_kunmap(wing->mqd_obj);
	wing->mqd_ptw = NUWW;
	amdgpu_bo_unwesewve(wing->mqd_obj);
	wetuwn 0;
}

static int gfx_v9_4_3_xcc_kcq_wesume(stwuct amdgpu_device *adev, int xcc_id)
{
	stwuct amdgpu_wing *wing = NUWW;
	int w = 0, i;

	gfx_v9_4_3_xcc_cp_compute_enabwe(adev, twue, xcc_id);

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		wing = &adev->gfx.compute_wing[i + xcc_id * adev->gfx.num_compute_wings];

		w = amdgpu_bo_wesewve(wing->mqd_obj, fawse);
		if (unwikewy(w != 0))
			goto done;
		w = amdgpu_bo_kmap(wing->mqd_obj, (void **)&wing->mqd_ptw);
		if (!w) {
			w = gfx_v9_4_3_xcc_kcq_init_queue(wing, xcc_id);
			amdgpu_bo_kunmap(wing->mqd_obj);
			wing->mqd_ptw = NUWW;
		}
		amdgpu_bo_unwesewve(wing->mqd_obj);
		if (w)
			goto done;
	}

	w = amdgpu_gfx_enabwe_kcq(adev, xcc_id);
done:
	wetuwn w;
}

static int gfx_v9_4_3_xcc_cp_wesume(stwuct amdgpu_device *adev, int xcc_id)
{
	stwuct amdgpu_wing *wing;
	int w, j;

	gfx_v9_4_3_xcc_enabwe_gui_idwe_intewwupt(adev, fawse, xcc_id);

	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
		gfx_v9_4_3_xcc_disabwe_gpa_mode(adev, xcc_id);

		w = gfx_v9_4_3_xcc_cp_compute_woad_micwocode(adev, xcc_id);
		if (w)
			wetuwn w;
	}

	w = gfx_v9_4_3_xcc_kiq_wesume(adev, xcc_id);
	if (w)
		wetuwn w;

	w = gfx_v9_4_3_xcc_kcq_wesume(adev, xcc_id);
	if (w)
		wetuwn w;

	fow (j = 0; j < adev->gfx.num_compute_wings; j++) {
		wing = &adev->gfx.compute_wing
				[j + xcc_id * adev->gfx.num_compute_wings];
		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	gfx_v9_4_3_xcc_enabwe_gui_idwe_intewwupt(adev, twue, xcc_id);

	wetuwn 0;
}

static int gfx_v9_4_3_cp_wesume(stwuct amdgpu_device *adev)
{
	int w = 0, i, num_xcc;

	if (amdgpu_xcp_quewy_pawtition_mode(adev->xcp_mgw,
					    AMDGPU_XCP_FW_NONE) ==
	    AMDGPU_UNKNOWN_COMPUTE_PAWTITION_MODE)
		w = amdgpu_xcp_switch_pawtition_mode(adev->xcp_mgw,
						     amdgpu_usew_pawtt_mode);

	if (w)
		wetuwn w;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		w = gfx_v9_4_3_xcc_cp_wesume(adev, i);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static void gfx_v9_4_3_xcc_cp_enabwe(stwuct amdgpu_device *adev, boow enabwe,
				     int xcc_id)
{
	gfx_v9_4_3_xcc_cp_compute_enabwe(adev, enabwe, xcc_id);
}

static void gfx_v9_4_3_xcc_fini(stwuct amdgpu_device *adev, int xcc_id)
{
	if (amdgpu_gfx_disabwe_kcq(adev, xcc_id))
		DWM_EWWOW("XCD %d KCQ disabwe faiwed\n", xcc_id);

	if (amdgpu_swiov_vf(adev)) {
		/* must disabwe powwing fow SWIOV when hw finished, othewwise
		 * CPC engine may stiww keep fetching WB addwess which is awweady
		 * invawid aftew sw finished and twiggew DMAW weading ewwow in
		 * hypewvisow side.
		 */
		WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, xcc_id), CP_PQ_WPTW_POWW_CNTW, EN, 0);
		wetuwn;
	}

	/* Use deinitiawize sequence fwom CAIW when unbinding device
	 * fwom dwivew, othewwise KIQ is hanging when binding back
	 */
	if (!amdgpu_in_weset(adev) && !adev->in_suspend) {
		mutex_wock(&adev->swbm_mutex);
		soc15_gwbm_sewect(adev, adev->gfx.kiq[xcc_id].wing.me,
				  adev->gfx.kiq[xcc_id].wing.pipe,
				  adev->gfx.kiq[xcc_id].wing.queue, 0,
				  GET_INST(GC, xcc_id));
		gfx_v9_4_3_xcc_q_fini_wegistew(&adev->gfx.kiq[xcc_id].wing,
						 xcc_id);
		soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, xcc_id));
		mutex_unwock(&adev->swbm_mutex);
	}

	gfx_v9_4_3_xcc_kcq_fini_wegistew(adev, xcc_id);
	gfx_v9_4_3_xcc_cp_enabwe(adev, fawse, xcc_id);
}

static int gfx_v9_4_3_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!amdgpu_swiov_vf(adev))
		gfx_v9_4_3_init_gowden_wegistews(adev);

	gfx_v9_4_3_constants_init(adev);

	w = adev->gfx.wwc.funcs->wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v9_4_3_cp_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int gfx_v9_4_3_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, num_xcc;

	amdgpu_iwq_put(adev, &adev->gfx.pwiv_weg_iwq, 0);
	amdgpu_iwq_put(adev, &adev->gfx.pwiv_inst_iwq, 0);

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		gfx_v9_4_3_xcc_fini(adev, i);
	}

	wetuwn 0;
}

static int gfx_v9_4_3_suspend(void *handwe)
{
	wetuwn gfx_v9_4_3_hw_fini(handwe);
}

static int gfx_v9_4_3_wesume(void *handwe)
{
	wetuwn gfx_v9_4_3_hw_init(handwe);
}

static boow gfx_v9_4_3_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		if (WEG_GET_FIEWD(WWEG32_SOC15(GC, GET_INST(GC, i), wegGWBM_STATUS),
					GWBM_STATUS, GUI_ACTIVE))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int gfx_v9_4_3_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (gfx_v9_4_3_is_idwe(handwe))
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int gfx_v9_4_3_soft_weset(void *handwe)
{
	u32 gwbm_soft_weset = 0;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* GWBM_STATUS */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_STATUS);
	if (tmp & (GWBM_STATUS__PA_BUSY_MASK | GWBM_STATUS__SC_BUSY_MASK |
		   GWBM_STATUS__BCI_BUSY_MASK | GWBM_STATUS__SX_BUSY_MASK |
		   GWBM_STATUS__TA_BUSY_MASK | GWBM_STATUS__VGT_BUSY_MASK |
		   GWBM_STATUS__DB_BUSY_MASK | GWBM_STATUS__CB_BUSY_MASK |
		   GWBM_STATUS__GDS_BUSY_MASK | GWBM_STATUS__SPI_BUSY_MASK |
		   GWBM_STATUS__IA_BUSY_MASK | GWBM_STATUS__IA_BUSY_NO_DMA_MASK)) {
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_CP, 1);
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_GFX, 1);
	}

	if (tmp & (GWBM_STATUS__CP_BUSY_MASK | GWBM_STATUS__CP_COHEWENCY_BUSY_MASK)) {
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_CP, 1);
	}

	/* GWBM_STATUS2 */
	tmp = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_STATUS2);
	if (WEG_GET_FIEWD(tmp, GWBM_STATUS2, WWC_BUSY))
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_WWC, 1);


	if (gwbm_soft_weset) {
		/* stop the wwc */
		adev->gfx.wwc.funcs->stop(adev);

		/* Disabwe MEC pawsing/pwefetching */
		gfx_v9_4_3_xcc_cp_compute_enabwe(adev, fawse, 0);

		if (gwbm_soft_weset) {
			tmp = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_SOFT_WESET);
			tmp |= gwbm_soft_weset;
			dev_info(adev->dev, "GWBM_SOFT_WESET=0x%08X\n", tmp);
			WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_SOFT_WESET, tmp);
			tmp = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_SOFT_WESET);

			udeway(50);

			tmp &= ~gwbm_soft_weset;
			WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_SOFT_WESET, tmp);
			tmp = WWEG32_SOC15(GC, GET_INST(GC, 0), wegGWBM_SOFT_WESET);
		}

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}
	wetuwn 0;
}

static void gfx_v9_4_3_wing_emit_gds_switch(stwuct amdgpu_wing *wing,
					  uint32_t vmid,
					  uint32_t gds_base, uint32_t gds_size,
					  uint32_t gws_base, uint32_t gws_size,
					  uint32_t oa_base, uint32_t oa_size)
{
	stwuct amdgpu_device *adev = wing->adev;

	/* GDS Base */
	gfx_v9_4_3_wwite_data_to_weg(wing, 0, fawse,
				   SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegGDS_VMID0_BASE) + 2 * vmid,
				   gds_base);

	/* GDS Size */
	gfx_v9_4_3_wwite_data_to_weg(wing, 0, fawse,
				   SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegGDS_VMID0_SIZE) + 2 * vmid,
				   gds_size);

	/* GWS */
	gfx_v9_4_3_wwite_data_to_weg(wing, 0, fawse,
				   SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegGDS_GWS_VMID0) + vmid,
				   gws_size << GDS_GWS_VMID0__SIZE__SHIFT | gws_base);

	/* OA */
	gfx_v9_4_3_wwite_data_to_weg(wing, 0, fawse,
				   SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegGDS_OA_VMID0) + vmid,
				   (1 << (oa_size + oa_base)) - (1 << oa_base));
}

static int gfx_v9_4_3_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->gfx.num_compute_wings = min(amdgpu_gfx_get_num_kcq(adev),
					  AMDGPU_MAX_COMPUTE_WINGS);
	gfx_v9_4_3_set_kiq_pm4_funcs(adev);
	gfx_v9_4_3_set_wing_funcs(adev);
	gfx_v9_4_3_set_iwq_funcs(adev);
	gfx_v9_4_3_set_gds_init(adev);
	gfx_v9_4_3_set_wwc_funcs(adev);

	/* init wwcg weg access ctww */
	gfx_v9_4_3_init_wwcg_weg_access_ctww(adev);

	wetuwn gfx_v9_4_3_init_micwocode(adev);
}

static int gfx_v9_4_3_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_weg_iwq, 0);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_inst_iwq, 0);
	if (w)
		wetuwn w;

	if (adev->gfx.was &&
	    adev->gfx.was->enabwe_watchdog_timew)
		adev->gfx.was->enabwe_watchdog_timew(adev);

	wetuwn 0;
}

static void gfx_v9_4_3_xcc_update_swam_fgcg(stwuct amdgpu_device *adev,
					    boow enabwe, int xcc_id)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_GFX_FGCG))
		wetuwn;

	def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id),
				  wegWWC_CGTT_MGCG_OVEWWIDE);

	if (enabwe)
		data &= ~WWC_CGTT_MGCG_OVEWWIDE__GFXIP_FGCG_OVEWWIDE_MASK;
	ewse
		data |= WWC_CGTT_MGCG_OVEWWIDE__GFXIP_FGCG_OVEWWIDE_MASK;

	if (def != data)
		WWEG32_SOC15(GC, GET_INST(GC, xcc_id),
			     wegWWC_CGTT_MGCG_OVEWWIDE, data);

}

static void gfx_v9_4_3_xcc_update_wepeatew_fgcg(stwuct amdgpu_device *adev,
						boow enabwe, int xcc_id)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_WEPEATEW_FGCG))
		wetuwn;

	def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id),
				  wegWWC_CGTT_MGCG_OVEWWIDE);

	if (enabwe)
		data &= ~WWC_CGTT_MGCG_OVEWWIDE__GFXIP_WEP_FGCG_OVEWWIDE_MASK;
	ewse
		data |= WWC_CGTT_MGCG_OVEWWIDE__GFXIP_WEP_FGCG_OVEWWIDE_MASK;

	if (def != data)
		WWEG32_SOC15(GC, GET_INST(GC, xcc_id),
			     wegWWC_CGTT_MGCG_OVEWWIDE, data);
}

static void
gfx_v9_4_3_xcc_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						boow enabwe, int xcc_id)
{
	uint32_t data, def;

	/* It is disabwed by HW by defauwt */
	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGCG)) {
		/* 1 - WWC_CGTT_MGCG_OVEWWIDE */
		def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE);

		data &= ~(WWC_CGTT_MGCG_OVEWWIDE__GWBM_CGTT_SCWK_OVEWWIDE_MASK |
			  WWC_CGTT_MGCG_OVEWWIDE__GFXIP_MGCG_OVEWWIDE_MASK |
			  WWC_CGTT_MGCG_OVEWWIDE__WWC_CGTT_SCWK_OVEWWIDE_MASK |
			  WWC_CGTT_MGCG_OVEWWIDE__GFXIP_MGWS_OVEWWIDE_MASK);

		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE, data);

		/* MGWS is a gwobaw fwag to contwow aww MGWS in GFX */
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) {
			/* 2 - WWC memowy Wight sweep */
			if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_WWC_WS) {
				def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_MEM_SWP_CNTW);
				data |= WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK;
				if (def != data)
					WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_MEM_SWP_CNTW, data);
			}
			/* 3 - CP memowy Wight sweep */
			if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CP_WS) {
				def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_MEM_SWP_CNTW);
				data |= CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK;
				if (def != data)
					WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_MEM_SWP_CNTW, data);
			}
		}
	} ewse {
		/* 1 - MGCG_OVEWWIDE */
		def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE);

		data |= (WWC_CGTT_MGCG_OVEWWIDE__WWC_CGTT_SCWK_OVEWWIDE_MASK |
			 WWC_CGTT_MGCG_OVEWWIDE__GWBM_CGTT_SCWK_OVEWWIDE_MASK |
			 WWC_CGTT_MGCG_OVEWWIDE__GFXIP_MGCG_OVEWWIDE_MASK |
			 WWC_CGTT_MGCG_OVEWWIDE__GFXIP_MGWS_OVEWWIDE_MASK);

		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE, data);

		/* 2 - disabwe MGWS in WWC */
		data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_MEM_SWP_CNTW);
		if (data & WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK) {
			data &= ~WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK;
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_MEM_SWP_CNTW, data);
		}

		/* 3 - disabwe MGWS in CP */
		data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_MEM_SWP_CNTW);
		if (data & CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK) {
			data &= ~CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK;
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_MEM_SWP_CNTW, data);
		}
	}

}

static void
gfx_v9_4_3_xcc_update_coawse_gwain_cwock_gating(stwuct amdgpu_device *adev,
						boow enabwe, int xcc_id)
{
	uint32_t def, data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGCG)) {

		def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE);
		/* unset CGCG ovewwide */
		data &= ~WWC_CGTT_MGCG_OVEWWIDE__GFXIP_CGCG_OVEWWIDE_MASK;
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGWS)
			data &= ~WWC_CGTT_MGCG_OVEWWIDE__GFXIP_CGWS_OVEWWIDE_MASK;
		ewse
			data |= WWC_CGTT_MGCG_OVEWWIDE__GFXIP_CGWS_OVEWWIDE_MASK;
		/* update CGCG and CGWS ovewwide bits */
		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGTT_MGCG_OVEWWIDE, data);

		/* enabwe cgcg FSM(0x0000363F) */
		def = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGCG_CGWS_CTWW);

		data = (0x36
			<< WWC_CGCG_CGWS_CTWW__CGCG_GFX_IDWE_THWESHOWD__SHIFT) |
		       WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK;
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGWS)
			data |= (0x000F << WWC_CGCG_CGWS_CTWW__CGWS_WEP_COMPANSAT_DEWAY__SHIFT) |
				WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK;
		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGCG_CGWS_CTWW, data);

		/* set IDWE_POWW_COUNT(0x00900100) */
		def = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_WB_WPTW_POWW_CNTW);
		data = (0x0100 << CP_WB_WPTW_POWW_CNTW__POWW_FWEQUENCY__SHIFT) |
			(0x0090 << CP_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT);
		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCP_WB_WPTW_POWW_CNTW, data);
	} ewse {
		def = data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGCG_CGWS_CTWW);
		/* weset CGCG/CGWS bits */
		data &= ~(WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK | WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK);
		/* disabwe cgcg and cgws in FSM */
		if (def != data)
			WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegWWC_CGCG_CGWS_CTWW, data);
	}

}

static int gfx_v9_4_3_xcc_update_gfx_cwock_gating(stwuct amdgpu_device *adev,
						  boow enabwe, int xcc_id)
{
	amdgpu_gfx_wwc_entew_safe_mode(adev, xcc_id);

	if (enabwe) {
		/* FGCG */
		gfx_v9_4_3_xcc_update_swam_fgcg(adev, enabwe, xcc_id);
		gfx_v9_4_3_xcc_update_wepeatew_fgcg(adev, enabwe, xcc_id);

		/* CGCG/CGWS shouwd be enabwed aftew MGCG/MGWS
		 * ===  MGCG + MGWS ===
		 */
		gfx_v9_4_3_xcc_update_medium_gwain_cwock_gating(adev, enabwe,
								xcc_id);
		/* ===  CGCG + CGWS === */
		gfx_v9_4_3_xcc_update_coawse_gwain_cwock_gating(adev, enabwe,
								xcc_id);
	} ewse {
		/* CGCG/CGWS shouwd be disabwed befowe MGCG/MGWS
		 * ===  CGCG + CGWS ===
		 */
		gfx_v9_4_3_xcc_update_coawse_gwain_cwock_gating(adev, enabwe,
								xcc_id);
		/* ===  MGCG + MGWS === */
		gfx_v9_4_3_xcc_update_medium_gwain_cwock_gating(adev, enabwe,
								xcc_id);

		/* FGCG */
		gfx_v9_4_3_xcc_update_swam_fgcg(adev, enabwe, xcc_id);
		gfx_v9_4_3_xcc_update_wepeatew_fgcg(adev, enabwe, xcc_id);
	}

	amdgpu_gfx_wwc_exit_safe_mode(adev, xcc_id);

	wetuwn 0;
}

static const stwuct amdgpu_wwc_funcs gfx_v9_4_3_wwc_funcs = {
	.is_wwc_enabwed = gfx_v9_4_3_is_wwc_enabwed,
	.set_safe_mode = gfx_v9_4_3_xcc_set_safe_mode,
	.unset_safe_mode = gfx_v9_4_3_xcc_unset_safe_mode,
	.init = gfx_v9_4_3_wwc_init,
	.wesume = gfx_v9_4_3_wwc_wesume,
	.stop = gfx_v9_4_3_wwc_stop,
	.weset = gfx_v9_4_3_wwc_weset,
	.stawt = gfx_v9_4_3_wwc_stawt,
	.update_spm_vmid = gfx_v9_4_3_update_spm_vmid,
	.is_wwcg_access_wange = gfx_v9_4_3_is_wwcg_access_wange,
};

static int gfx_v9_4_3_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static int gfx_v9_4_3_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, num_xcc;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 3):
		fow (i = 0; i < num_xcc; i++)
			gfx_v9_4_3_xcc_update_gfx_cwock_gating(
				adev, state == AMD_CG_STATE_GATE, i);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void gfx_v9_4_3_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	/* AMD_CG_SUPPOWT_GFX_MGCG */
	data = WWEG32_KIQ(SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegWWC_CGTT_MGCG_OVEWWIDE));
	if (!(data & WWC_CGTT_MGCG_OVEWWIDE__GFXIP_MGCG_OVEWWIDE_MASK))
		*fwags |= AMD_CG_SUPPOWT_GFX_MGCG;

	/* AMD_CG_SUPPOWT_GFX_CGCG */
	data = WWEG32_KIQ(SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegWWC_CGCG_CGWS_CTWW));
	if (data & WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CGCG;

	/* AMD_CG_SUPPOWT_GFX_CGWS */
	if (data & WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CGWS;

	/* AMD_CG_SUPPOWT_GFX_WWC_WS */
	data = WWEG32_KIQ(SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegWWC_MEM_SWP_CNTW));
	if (data & WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_WWC_WS | AMD_CG_SUPPOWT_GFX_MGWS;

	/* AMD_CG_SUPPOWT_GFX_CP_WS */
	data = WWEG32_KIQ(SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegCP_MEM_SWP_CNTW));
	if (data & CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CP_WS | AMD_CG_SUPPOWT_GFX_MGWS;
}

static void gfx_v9_4_3_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 wef_and_mask, weg_mem_engine;
	const stwuct nbio_hdp_fwush_weg *nbio_hf_weg = adev->nbio.hdp_fwush_weg;

	if (wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE) {
		switch (wing->me) {
		case 1:
			wef_and_mask = nbio_hf_weg->wef_and_mask_cp2 << wing->pipe;
			bweak;
		case 2:
			wef_and_mask = nbio_hf_weg->wef_and_mask_cp6 << wing->pipe;
			bweak;
		defauwt:
			wetuwn;
		}
		weg_mem_engine = 0;
	} ewse {
		wef_and_mask = nbio_hf_weg->wef_and_mask_cp0;
		weg_mem_engine = 1; /* pfp */
	}

	gfx_v9_4_3_wait_weg_mem(wing, weg_mem_engine, 0, 1,
			      adev->nbio.funcs->get_hdp_fwush_weq_offset(adev),
			      adev->nbio.funcs->get_hdp_fwush_done_offset(adev),
			      wef_and_mask, wef_and_mask, 0x20);
}

static void gfx_v9_4_3_wing_emit_ib_compute(stwuct amdgpu_wing *wing,
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
		amdgpu_wing_wwite(wing, wegGDS_COMPUTE_MAX_WAVE_ID);
		amdgpu_wing_wwite(wing, wing->adev->gds.gds_compute_max_wave_id);
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	BUG_ON(ib->gpu_addw & 0x3); /* Dwowd awign */
	amdgpu_wing_wwite(wing,
#ifdef __BIG_ENDIAN
				(2 << 0) |
#endif
				wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, contwow);
}

static void gfx_v9_4_3_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
				     u64 seq, unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	boow int_sew = fwags & AMDGPU_FENCE_FWAG_INT;
	boow wwiteback = fwags & AMDGPU_FENCE_FWAG_TC_WB_ONWY;

	/* WEWEASE_MEM - fwush caches, send int */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WEWEASE_MEM, 6));
	amdgpu_wing_wwite(wing, ((wwiteback ? (EOP_TC_WB_ACTION_EN |
					       EOP_TC_NC_ACTION_EN) :
					      (EOP_TCW1_ACTION_EN |
					       EOP_TC_ACTION_EN |
					       EOP_TC_WB_ACTION_EN |
					       EOP_TC_MD_ACTION_EN)) |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, DATA_SEW(wwite64bit ? 2 : 1) | INT_SEW(int_sew ? 2 : 0));

	/*
	 * the addwess shouwd be Qwowd awigned if 64bit wwite, Dwowd
	 * awigned if onwy send 32bit data wow (discawd data high)
	 */
	if (wwite64bit)
		BUG_ON(addw & 0x7);
	ewse
		BUG_ON(addw & 0x3);
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq));
	amdgpu_wing_wwite(wing, 0);
}

static void gfx_v9_4_3_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	gfx_v9_4_3_wait_weg_mem(wing, usepfp, 1, 0,
			      wowew_32_bits(addw), uppew_32_bits(addw),
			      seq, 0xffffffff, 4);
}

static void gfx_v9_4_3_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					unsigned vmid, uint64_t pd_addw)
{
	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);
}

static u64 gfx_v9_4_3_wing_get_wptw_compute(stwuct amdgpu_wing *wing)
{
	wetuwn wing->adev->wb.wb[wing->wptw_offs]; /* gfx9 hawdwawe is 32bit wptw */
}

static u64 gfx_v9_4_3_wing_get_wptw_compute(stwuct amdgpu_wing *wing)
{
	u64 wptw;

	/* XXX check if swapping is necessawy on BE */
	if (wing->use_doowbeww)
		wptw = atomic64_wead((atomic64_t *)&wing->adev->wb.wb[wing->wptw_offs]);
	ewse
		BUG();
	wetuwn wptw;
}

static void gfx_v9_4_3_wing_set_wptw_compute(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	/* XXX check if swapping is necessawy on BE */
	if (wing->use_doowbeww) {
		atomic64_set((atomic64_t *)&adev->wb.wb[wing->wptw_offs], wing->wptw);
		WDOOWBEWW64(wing->doowbeww_index, wing->wptw);
	} ewse {
		BUG(); /* onwy DOOWBEWW method suppowted on gfx9 now */
	}
}

static void gfx_v9_4_3_wing_emit_fence_kiq(stwuct amdgpu_wing *wing, u64 addw,
					 u64 seq, unsigned int fwags)
{
	stwuct amdgpu_device *adev = wing->adev;

	/* we onwy awwocate 32bit fow each seq wb addwess */
	BUG_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	/* wwite fence seq to the "addw" */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				 WWITE_DATA_DST_SEW(5) | WW_CONFIWM));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));

	if (fwags & AMDGPU_FENCE_FWAG_INT) {
		/* set wegistew to twiggew INT */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
		amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
					 WWITE_DATA_DST_SEW(0) | WW_CONFIWM));
		amdgpu_wing_wwite(wing, SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegCPC_INT_STATUS));
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing, 0x20000000); /* swc_id is 178 */
	}
}

static void gfx_v9_4_3_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
				    uint32_t weg_vaw_offs)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_COPY_DATA, 4));
	amdgpu_wing_wwite(wing, 0 |	/* swc: wegistew*/
				(5 << 8) |	/* dst: memowy */
				(1 << 20));	/* wwite confiwm */
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, wowew_32_bits(adev->wb.gpu_addw +
				weg_vaw_offs * 4));
	amdgpu_wing_wwite(wing, uppew_32_bits(adev->wb.gpu_addw +
				weg_vaw_offs * 4));
}

static void gfx_v9_4_3_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
				    uint32_t vaw)
{
	uint32_t cmd = 0;

	switch (wing->funcs->type) {
	case AMDGPU_WING_TYPE_GFX:
		cmd = WWITE_DATA_ENGINE_SEW(1) | WW_CONFIWM;
		bweak;
	case AMDGPU_WING_TYPE_KIQ:
		cmd = (1 << 16); /* no inc addw */
		bweak;
	defauwt:
		cmd = WW_CONFIWM;
		bweak;
	}
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, cmd);
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, vaw);
}

static void gfx_v9_4_3_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
					uint32_t vaw, uint32_t mask)
{
	gfx_v9_4_3_wait_weg_mem(wing, 0, 0, 0, weg, 0, vaw, mask, 0x20);
}

static void gfx_v9_4_3_wing_emit_weg_wwite_weg_wait(stwuct amdgpu_wing *wing,
						  uint32_t weg0, uint32_t weg1,
						  uint32_t wef, uint32_t mask)
{
	amdgpu_wing_emit_weg_wwite_weg_wait_hewpew(wing, weg0, weg1,
						   wef, mask);
}

static void gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
	stwuct amdgpu_device *adev, int me, int pipe,
	enum amdgpu_intewwupt_state state, int xcc_id)
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
			mec_int_cntw_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_ME1_PIPE0_INT_CNTW);
			bweak;
		case 1:
			mec_int_cntw_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_ME1_PIPE1_INT_CNTW);
			bweak;
		case 2:
			mec_int_cntw_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_ME1_PIPE2_INT_CNTW);
			bweak;
		case 3:
			mec_int_cntw_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, xcc_id), wegCP_ME1_PIPE3_INT_CNTW);
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
		mec_int_cntw = WWEG32_XCC(mec_int_cntw_weg, xcc_id);
		mec_int_cntw = WEG_SET_FIEWD(mec_int_cntw, CP_ME1_PIPE0_INT_CNTW,
					     TIME_STAMP_INT_ENABWE, 0);
		WWEG32_XCC(mec_int_cntw_weg, mec_int_cntw, xcc_id);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		mec_int_cntw = WWEG32_XCC(mec_int_cntw_weg, xcc_id);
		mec_int_cntw = WEG_SET_FIEWD(mec_int_cntw, CP_ME1_PIPE0_INT_CNTW,
					     TIME_STAMP_INT_ENABWE, 1);
		WWEG32_XCC(mec_int_cntw_weg, mec_int_cntw, xcc_id);
		bweak;
	defauwt:
		bweak;
	}
}

static int gfx_v9_4_3_set_pwiv_weg_fauwt_state(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *souwce,
					     unsigned type,
					     enum amdgpu_intewwupt_state state)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
	case AMDGPU_IWQ_STATE_ENABWE:
		fow (i = 0; i < num_xcc; i++)
			WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, i), CP_INT_CNTW_WING0,
				PWIV_WEG_INT_ENABWE,
				state == AMDGPU_IWQ_STATE_ENABWE ? 1 : 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int gfx_v9_4_3_set_pwiv_inst_fauwt_state(stwuct amdgpu_device *adev,
					      stwuct amdgpu_iwq_swc *souwce,
					      unsigned type,
					      enum amdgpu_intewwupt_state state)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
	case AMDGPU_IWQ_STATE_ENABWE:
		fow (i = 0; i < num_xcc; i++)
			WWEG32_FIEWD15_PWEWEG(GC, GET_INST(GC, i), CP_INT_CNTW_WING0,
				PWIV_INSTW_INT_ENABWE,
				state == AMDGPU_IWQ_STATE_ENABWE ? 1 : 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int gfx_v9_4_3_set_eop_intewwupt_state(stwuct amdgpu_device *adev,
					    stwuct amdgpu_iwq_swc *swc,
					    unsigned type,
					    enum amdgpu_intewwupt_state state)
{
	int i, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		switch (type) {
		case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 1, 0, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE1_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 1, 1, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE2_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 1, 2, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE3_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 1, 3, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE0_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 2, 0, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE1_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 2, 1, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE2_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 2, 2, state, i);
			bweak;
		case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE3_EOP:
			gfx_v9_4_3_xcc_set_compute_eop_intewwupt_state(
				adev, 2, 3, state, i);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int gfx_v9_4_3_eop_iwq(stwuct amdgpu_device *adev,
			    stwuct amdgpu_iwq_swc *souwce,
			    stwuct amdgpu_iv_entwy *entwy)
{
	int i, xcc_id;
	u8 me_id, pipe_id, queue_id;
	stwuct amdgpu_wing *wing;

	DWM_DEBUG("IH: CP EOP\n");
	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	queue_id = (entwy->wing_id & 0x70) >> 4;

	xcc_id = gfx_v9_4_3_ih_to_xcc_inst(adev, entwy->node_id);

	if (xcc_id == -EINVAW)
		wetuwn -EINVAW;

	switch (me_id) {
	case 0:
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing
					[i +
					 xcc_id * adev->gfx.num_compute_wings];
			/* Pew-queue intewwupt is suppowted fow MEC stawting fwom VI.
			  * The intewwupt can onwy be enabwed/disabwed pew pipe instead of pew queue.
			  */

			if ((wing->me == me_id) && (wing->pipe == pipe_id) && (wing->queue == queue_id))
				amdgpu_fence_pwocess(wing);
		}
		bweak;
	}
	wetuwn 0;
}

static void gfx_v9_4_3_fauwt(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iv_entwy *entwy)
{
	u8 me_id, pipe_id, queue_id;
	stwuct amdgpu_wing *wing;
	int i, xcc_id;

	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	queue_id = (entwy->wing_id & 0x70) >> 4;

	xcc_id = gfx_v9_4_3_ih_to_xcc_inst(adev, entwy->node_id);

	if (xcc_id == -EINVAW)
		wetuwn;

	switch (me_id) {
	case 0:
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing
					[i +
					 xcc_id * adev->gfx.num_compute_wings];
			if (wing->me == me_id && wing->pipe == pipe_id &&
			    wing->queue == queue_id)
				dwm_sched_fauwt(&wing->sched);
		}
		bweak;
	}
}

static int gfx_v9_4_3_pwiv_weg_iwq(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw wegistew access in command stweam\n");
	gfx_v9_4_3_fauwt(adev, entwy);
	wetuwn 0;
}

static int gfx_v9_4_3_pwiv_inst_iwq(stwuct amdgpu_device *adev,
				  stwuct amdgpu_iwq_swc *souwce,
				  stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw instwuction in command stweam\n");
	gfx_v9_4_3_fauwt(adev, entwy);
	wetuwn 0;
}

static void gfx_v9_4_3_emit_mem_sync(stwuct amdgpu_wing *wing)
{
	const unsigned int cp_cohew_cntw =
			PACKET3_ACQUIWE_MEM_CP_COHEW_CNTW_SH_ICACHE_ACTION_ENA(1) |
			PACKET3_ACQUIWE_MEM_CP_COHEW_CNTW_SH_KCACHE_ACTION_ENA(1) |
			PACKET3_ACQUIWE_MEM_CP_COHEW_CNTW_TC_ACTION_ENA(1) |
			PACKET3_ACQUIWE_MEM_CP_COHEW_CNTW_TCW1_ACTION_ENA(1) |
			PACKET3_ACQUIWE_MEM_CP_COHEW_CNTW_TC_WB_ACTION_ENA(1);

	/* ACQUIWE_MEM -make one ow mowe suwfaces vawid fow use by the subsequent opewations */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_ACQUIWE_MEM, 5));
	amdgpu_wing_wwite(wing, cp_cohew_cntw); /* CP_COHEW_CNTW */
	amdgpu_wing_wwite(wing, 0xffffffff);  /* CP_COHEW_SIZE */
	amdgpu_wing_wwite(wing, 0xffffff);  /* CP_COHEW_SIZE_HI */
	amdgpu_wing_wwite(wing, 0); /* CP_COHEW_BASE */
	amdgpu_wing_wwite(wing, 0);  /* CP_COHEW_BASE_HI */
	amdgpu_wing_wwite(wing, 0x0000000A); /* POWW_INTEWVAW */
}

static void gfx_v9_4_3_emit_wave_wimit_cs(stwuct amdgpu_wing *wing,
					uint32_t pipe, boow enabwe)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t vaw;
	uint32_t wcw_cs_weg;

	/* wegSPI_WCW_PIPE_PEWCENT_CS[0-7]_DEFAUWT vawues awe same */
	vaw = enabwe ? 0x1 : 0x7f;

	switch (pipe) {
	case 0:
		wcw_cs_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegSPI_WCW_PIPE_PEWCENT_CS0);
		bweak;
	case 1:
		wcw_cs_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegSPI_WCW_PIPE_PEWCENT_CS1);
		bweak;
	case 2:
		wcw_cs_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegSPI_WCW_PIPE_PEWCENT_CS2);
		bweak;
	case 3:
		wcw_cs_weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegSPI_WCW_PIPE_PEWCENT_CS3);
		bweak;
	defauwt:
		DWM_DEBUG("invawid pipe %d\n", pipe);
		wetuwn;
	}

	amdgpu_wing_emit_wweg(wing, wcw_cs_weg, vaw);

}
static void gfx_v9_4_3_emit_wave_wimit(stwuct amdgpu_wing *wing, boow enabwe)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t vaw;
	int i;

	/* wegSPI_WCW_PIPE_PEWCENT_GFX is 7 bit muwtipwiew wegistew to wimit
	 * numbew of gfx waves. Setting 5 bit wiww make suwe gfx onwy gets
	 * awound 25% of gpu wesouwces.
	 */
	vaw = enabwe ? 0x1f : 0x07ffffff;
	amdgpu_wing_emit_wweg(wing,
			      SOC15_WEG_OFFSET(GC, GET_INST(GC, 0), wegSPI_WCW_PIPE_PEWCENT_GFX),
			      vaw);

	/* Westwict waves fow nowmaw/wow pwiowity compute queues as weww
	 * to get best QoS fow high pwiowity compute jobs.
	 *
	 * amdgpu contwows onwy 1st ME(0-3 CS pipes).
	 */
	fow (i = 0; i < adev->gfx.mec.num_pipe_pew_mec; i++) {
		if (i != wing->pipe)
			gfx_v9_4_3_emit_wave_wimit_cs(wing, i, enabwe);

	}
}

enum amdgpu_gfx_cp_was_mem_id {
	AMDGPU_GFX_CP_MEM1 = 1,
	AMDGPU_GFX_CP_MEM2,
	AMDGPU_GFX_CP_MEM3,
	AMDGPU_GFX_CP_MEM4,
	AMDGPU_GFX_CP_MEM5,
};

enum amdgpu_gfx_gcea_was_mem_id {
	AMDGPU_GFX_GCEA_IOWW_CMDMEM = 4,
	AMDGPU_GFX_GCEA_IOWD_CMDMEM,
	AMDGPU_GFX_GCEA_GMIWW_CMDMEM,
	AMDGPU_GFX_GCEA_GMIWD_CMDMEM,
	AMDGPU_GFX_GCEA_DWAMWW_CMDMEM,
	AMDGPU_GFX_GCEA_DWAMWD_CMDMEM,
	AMDGPU_GFX_GCEA_MAM_DMEM0,
	AMDGPU_GFX_GCEA_MAM_DMEM1,
	AMDGPU_GFX_GCEA_MAM_DMEM2,
	AMDGPU_GFX_GCEA_MAM_DMEM3,
	AMDGPU_GFX_GCEA_MAM_AMEM0,
	AMDGPU_GFX_GCEA_MAM_AMEM1,
	AMDGPU_GFX_GCEA_MAM_AMEM2,
	AMDGPU_GFX_GCEA_MAM_AMEM3,
	AMDGPU_GFX_GCEA_MAM_AFWUSH_BUFFEW,
	AMDGPU_GFX_GCEA_WWET_TAGMEM,
	AMDGPU_GFX_GCEA_WWET_TAGMEM,
	AMDGPU_GFX_GCEA_IOWW_DATAMEM,
	AMDGPU_GFX_GCEA_GMIWW_DATAMEM,
	AMDGPU_GFX_GCEA_DWAM_DATAMEM,
};

enum amdgpu_gfx_gc_cane_was_mem_id {
	AMDGPU_GFX_GC_CANE_MEM0 = 0,
};

enum amdgpu_gfx_gcutcw2_was_mem_id {
	AMDGPU_GFX_GCUTCW2_MEM2P512X95 = 160,
};

enum amdgpu_gfx_gds_was_mem_id {
	AMDGPU_GFX_GDS_MEM0 = 0,
};

enum amdgpu_gfx_wds_was_mem_id {
	AMDGPU_GFX_WDS_BANK0 = 0,
	AMDGPU_GFX_WDS_BANK1,
	AMDGPU_GFX_WDS_BANK2,
	AMDGPU_GFX_WDS_BANK3,
	AMDGPU_GFX_WDS_BANK4,
	AMDGPU_GFX_WDS_BANK5,
	AMDGPU_GFX_WDS_BANK6,
	AMDGPU_GFX_WDS_BANK7,
	AMDGPU_GFX_WDS_BANK8,
	AMDGPU_GFX_WDS_BANK9,
	AMDGPU_GFX_WDS_BANK10,
	AMDGPU_GFX_WDS_BANK11,
	AMDGPU_GFX_WDS_BANK12,
	AMDGPU_GFX_WDS_BANK13,
	AMDGPU_GFX_WDS_BANK14,
	AMDGPU_GFX_WDS_BANK15,
	AMDGPU_GFX_WDS_BANK16,
	AMDGPU_GFX_WDS_BANK17,
	AMDGPU_GFX_WDS_BANK18,
	AMDGPU_GFX_WDS_BANK19,
	AMDGPU_GFX_WDS_BANK20,
	AMDGPU_GFX_WDS_BANK21,
	AMDGPU_GFX_WDS_BANK22,
	AMDGPU_GFX_WDS_BANK23,
	AMDGPU_GFX_WDS_BANK24,
	AMDGPU_GFX_WDS_BANK25,
	AMDGPU_GFX_WDS_BANK26,
	AMDGPU_GFX_WDS_BANK27,
	AMDGPU_GFX_WDS_BANK28,
	AMDGPU_GFX_WDS_BANK29,
	AMDGPU_GFX_WDS_BANK30,
	AMDGPU_GFX_WDS_BANK31,
	AMDGPU_GFX_WDS_SP_BUFFEW_A,
	AMDGPU_GFX_WDS_SP_BUFFEW_B,
};

enum amdgpu_gfx_wwc_was_mem_id {
	AMDGPU_GFX_WWC_GPMF32 = 1,
	AMDGPU_GFX_WWC_WWCVF32,
	AMDGPU_GFX_WWC_SCWATCH,
	AMDGPU_GFX_WWC_SWM_AWAM,
	AMDGPU_GFX_WWC_SWM_DWAM,
	AMDGPU_GFX_WWC_TCTAG,
	AMDGPU_GFX_WWC_SPM_SE,
	AMDGPU_GFX_WWC_SPM_GWBMT,
};

enum amdgpu_gfx_sp_was_mem_id {
	AMDGPU_GFX_SP_SIMDID0 = 0,
};

enum amdgpu_gfx_spi_was_mem_id {
	AMDGPU_GFX_SPI_MEM0 = 0,
	AMDGPU_GFX_SPI_MEM1,
	AMDGPU_GFX_SPI_MEM2,
	AMDGPU_GFX_SPI_MEM3,
};

enum amdgpu_gfx_sqc_was_mem_id {
	AMDGPU_GFX_SQC_INST_CACHE_A = 100,
	AMDGPU_GFX_SQC_INST_CACHE_B = 101,
	AMDGPU_GFX_SQC_INST_CACHE_TAG_A = 102,
	AMDGPU_GFX_SQC_INST_CACHE_TAG_B = 103,
	AMDGPU_GFX_SQC_INST_CACHE_MISS_FIFO_A = 104,
	AMDGPU_GFX_SQC_INST_CACHE_MISS_FIFO_B = 105,
	AMDGPU_GFX_SQC_INST_CACHE_GATCW1_MISS_FIFO_A = 106,
	AMDGPU_GFX_SQC_INST_CACHE_GATCW1_MISS_FIFO_B = 107,
	AMDGPU_GFX_SQC_DATA_CACHE_A = 200,
	AMDGPU_GFX_SQC_DATA_CACHE_B = 201,
	AMDGPU_GFX_SQC_DATA_CACHE_TAG_A = 202,
	AMDGPU_GFX_SQC_DATA_CACHE_TAG_B = 203,
	AMDGPU_GFX_SQC_DATA_CACHE_MISS_FIFO_A = 204,
	AMDGPU_GFX_SQC_DATA_CACHE_MISS_FIFO_B = 205,
	AMDGPU_GFX_SQC_DATA_CACHE_HIT_FIFO_A = 206,
	AMDGPU_GFX_SQC_DATA_CACHE_HIT_FIFO_B = 207,
	AMDGPU_GFX_SQC_DIWTY_BIT_A = 208,
	AMDGPU_GFX_SQC_DIWTY_BIT_B = 209,
	AMDGPU_GFX_SQC_WWITE_DATA_BUFFEW_CU0 = 210,
	AMDGPU_GFX_SQC_WWITE_DATA_BUFFEW_CU1 = 211,
	AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_DATA_CACHE_A = 212,
	AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_DATA_CACHE_B = 213,
	AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_INST_CACHE = 108,
};

enum amdgpu_gfx_sq_was_mem_id {
	AMDGPU_GFX_SQ_SGPW_MEM0 = 0,
	AMDGPU_GFX_SQ_SGPW_MEM1,
	AMDGPU_GFX_SQ_SGPW_MEM2,
	AMDGPU_GFX_SQ_SGPW_MEM3,
};

enum amdgpu_gfx_ta_was_mem_id {
	AMDGPU_GFX_TA_FS_AFIFO_WAM_WO = 1,
	AMDGPU_GFX_TA_FS_AFIFO_WAM_HI,
	AMDGPU_GFX_TA_FS_CFIFO_WAM,
	AMDGPU_GFX_TA_FSX_WFIFO,
	AMDGPU_GFX_TA_FS_DFIFO_WAM,
};

enum amdgpu_gfx_tcc_was_mem_id {
	AMDGPU_GFX_TCC_MEM1 = 1,
};

enum amdgpu_gfx_tca_was_mem_id {
	AMDGPU_GFX_TCA_MEM1 = 1,
};

enum amdgpu_gfx_tci_was_mem_id {
	AMDGPU_GFX_TCIW_MEM = 1,
};

enum amdgpu_gfx_tcp_was_mem_id {
	AMDGPU_GFX_TCP_WFIFO0 = 1,
	AMDGPU_GFX_TCP_SET0BANK0_WAM,
	AMDGPU_GFX_TCP_SET0BANK1_WAM,
	AMDGPU_GFX_TCP_SET0BANK2_WAM,
	AMDGPU_GFX_TCP_SET0BANK3_WAM,
	AMDGPU_GFX_TCP_SET1BANK0_WAM,
	AMDGPU_GFX_TCP_SET1BANK1_WAM,
	AMDGPU_GFX_TCP_SET1BANK2_WAM,
	AMDGPU_GFX_TCP_SET1BANK3_WAM,
	AMDGPU_GFX_TCP_SET2BANK0_WAM,
	AMDGPU_GFX_TCP_SET2BANK1_WAM,
	AMDGPU_GFX_TCP_SET2BANK2_WAM,
	AMDGPU_GFX_TCP_SET2BANK3_WAM,
	AMDGPU_GFX_TCP_SET3BANK0_WAM,
	AMDGPU_GFX_TCP_SET3BANK1_WAM,
	AMDGPU_GFX_TCP_SET3BANK2_WAM,
	AMDGPU_GFX_TCP_SET3BANK3_WAM,
	AMDGPU_GFX_TCP_VM_FIFO,
	AMDGPU_GFX_TCP_DB_TAGWAM0,
	AMDGPU_GFX_TCP_DB_TAGWAM1,
	AMDGPU_GFX_TCP_DB_TAGWAM2,
	AMDGPU_GFX_TCP_DB_TAGWAM3,
	AMDGPU_GFX_TCP_UTCW1_WFIFO_PWOBE0,
	AMDGPU_GFX_TCP_UTCW1_WFIFO_PWOBE1,
	AMDGPU_GFX_TCP_CMD_FIFO,
};

enum amdgpu_gfx_td_was_mem_id {
	AMDGPU_GFX_TD_UTD_CS_FIFO_MEM = 1,
	AMDGPU_GFX_TD_UTD_SS_FIFO_WO_MEM,
	AMDGPU_GFX_TD_UTD_SS_FIFO_HI_MEM,
};

enum amdgpu_gfx_tcx_was_mem_id {
	AMDGPU_GFX_TCX_FIFOD0 = 0,
	AMDGPU_GFX_TCX_FIFOD1,
	AMDGPU_GFX_TCX_FIFOD2,
	AMDGPU_GFX_TCX_FIFOD3,
	AMDGPU_GFX_TCX_FIFOD4,
	AMDGPU_GFX_TCX_FIFOD5,
	AMDGPU_GFX_TCX_FIFOD6,
	AMDGPU_GFX_TCX_FIFOD7,
	AMDGPU_GFX_TCX_FIFOB0,
	AMDGPU_GFX_TCX_FIFOB1,
	AMDGPU_GFX_TCX_FIFOB2,
	AMDGPU_GFX_TCX_FIFOB3,
	AMDGPU_GFX_TCX_FIFOB4,
	AMDGPU_GFX_TCX_FIFOB5,
	AMDGPU_GFX_TCX_FIFOB6,
	AMDGPU_GFX_TCX_FIFOB7,
	AMDGPU_GFX_TCX_FIFOA0,
	AMDGPU_GFX_TCX_FIFOA1,
	AMDGPU_GFX_TCX_FIFOA2,
	AMDGPU_GFX_TCX_FIFOA3,
	AMDGPU_GFX_TCX_FIFOA4,
	AMDGPU_GFX_TCX_FIFOA5,
	AMDGPU_GFX_TCX_FIFOA6,
	AMDGPU_GFX_TCX_FIFOA7,
	AMDGPU_GFX_TCX_CFIFO0,
	AMDGPU_GFX_TCX_CFIFO1,
	AMDGPU_GFX_TCX_CFIFO2,
	AMDGPU_GFX_TCX_CFIFO3,
	AMDGPU_GFX_TCX_CFIFO4,
	AMDGPU_GFX_TCX_CFIFO5,
	AMDGPU_GFX_TCX_CFIFO6,
	AMDGPU_GFX_TCX_CFIFO7,
	AMDGPU_GFX_TCX_FIFO_ACKB0,
	AMDGPU_GFX_TCX_FIFO_ACKB1,
	AMDGPU_GFX_TCX_FIFO_ACKB2,
	AMDGPU_GFX_TCX_FIFO_ACKB3,
	AMDGPU_GFX_TCX_FIFO_ACKB4,
	AMDGPU_GFX_TCX_FIFO_ACKB5,
	AMDGPU_GFX_TCX_FIFO_ACKB6,
	AMDGPU_GFX_TCX_FIFO_ACKB7,
	AMDGPU_GFX_TCX_FIFO_ACKD0,
	AMDGPU_GFX_TCX_FIFO_ACKD1,
	AMDGPU_GFX_TCX_FIFO_ACKD2,
	AMDGPU_GFX_TCX_FIFO_ACKD3,
	AMDGPU_GFX_TCX_FIFO_ACKD4,
	AMDGPU_GFX_TCX_FIFO_ACKD5,
	AMDGPU_GFX_TCX_FIFO_ACKD6,
	AMDGPU_GFX_TCX_FIFO_ACKD7,
	AMDGPU_GFX_TCX_DST_FIFOA0,
	AMDGPU_GFX_TCX_DST_FIFOA1,
	AMDGPU_GFX_TCX_DST_FIFOA2,
	AMDGPU_GFX_TCX_DST_FIFOA3,
	AMDGPU_GFX_TCX_DST_FIFOA4,
	AMDGPU_GFX_TCX_DST_FIFOA5,
	AMDGPU_GFX_TCX_DST_FIFOA6,
	AMDGPU_GFX_TCX_DST_FIFOA7,
	AMDGPU_GFX_TCX_DST_FIFOB0,
	AMDGPU_GFX_TCX_DST_FIFOB1,
	AMDGPU_GFX_TCX_DST_FIFOB2,
	AMDGPU_GFX_TCX_DST_FIFOB3,
	AMDGPU_GFX_TCX_DST_FIFOB4,
	AMDGPU_GFX_TCX_DST_FIFOB5,
	AMDGPU_GFX_TCX_DST_FIFOB6,
	AMDGPU_GFX_TCX_DST_FIFOB7,
	AMDGPU_GFX_TCX_DST_FIFOD0,
	AMDGPU_GFX_TCX_DST_FIFOD1,
	AMDGPU_GFX_TCX_DST_FIFOD2,
	AMDGPU_GFX_TCX_DST_FIFOD3,
	AMDGPU_GFX_TCX_DST_FIFOD4,
	AMDGPU_GFX_TCX_DST_FIFOD5,
	AMDGPU_GFX_TCX_DST_FIFOD6,
	AMDGPU_GFX_TCX_DST_FIFOD7,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB0,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB1,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB2,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB3,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB4,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB5,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB6,
	AMDGPU_GFX_TCX_DST_FIFO_ACKB7,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD0,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD1,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD2,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD3,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD4,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD5,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD6,
	AMDGPU_GFX_TCX_DST_FIFO_ACKD7,
};

enum amdgpu_gfx_atc_w2_was_mem_id {
	AMDGPU_GFX_ATC_W2_MEM0 = 0,
};

enum amdgpu_gfx_utcw2_was_mem_id {
	AMDGPU_GFX_UTCW2_MEM0 = 0,
};

enum amdgpu_gfx_vmw2_was_mem_id {
	AMDGPU_GFX_VMW2_MEM0 = 0,
};

enum amdgpu_gfx_vmw2_wawkew_was_mem_id {
	AMDGPU_GFX_VMW2_WAWKEW_MEM0 = 0,
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_cp_mem_wist[] = {
	{AMDGPU_GFX_CP_MEM1, "CP_MEM1"},
	{AMDGPU_GFX_CP_MEM2, "CP_MEM2"},
	{AMDGPU_GFX_CP_MEM3, "CP_MEM3"},
	{AMDGPU_GFX_CP_MEM4, "CP_MEM4"},
	{AMDGPU_GFX_CP_MEM5, "CP_MEM5"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_gcea_mem_wist[] = {
	{AMDGPU_GFX_GCEA_IOWW_CMDMEM, "GCEA_IOWW_CMDMEM"},
	{AMDGPU_GFX_GCEA_IOWD_CMDMEM, "GCEA_IOWD_CMDMEM"},
	{AMDGPU_GFX_GCEA_GMIWW_CMDMEM, "GCEA_GMIWW_CMDMEM"},
	{AMDGPU_GFX_GCEA_GMIWD_CMDMEM, "GCEA_GMIWD_CMDMEM"},
	{AMDGPU_GFX_GCEA_DWAMWW_CMDMEM, "GCEA_DWAMWW_CMDMEM"},
	{AMDGPU_GFX_GCEA_DWAMWD_CMDMEM, "GCEA_DWAMWD_CMDMEM"},
	{AMDGPU_GFX_GCEA_MAM_DMEM0, "GCEA_MAM_DMEM0"},
	{AMDGPU_GFX_GCEA_MAM_DMEM1, "GCEA_MAM_DMEM1"},
	{AMDGPU_GFX_GCEA_MAM_DMEM2, "GCEA_MAM_DMEM2"},
	{AMDGPU_GFX_GCEA_MAM_DMEM3, "GCEA_MAM_DMEM3"},
	{AMDGPU_GFX_GCEA_MAM_AMEM0, "GCEA_MAM_AMEM0"},
	{AMDGPU_GFX_GCEA_MAM_AMEM1, "GCEA_MAM_AMEM1"},
	{AMDGPU_GFX_GCEA_MAM_AMEM2, "GCEA_MAM_AMEM2"},
	{AMDGPU_GFX_GCEA_MAM_AMEM3, "GCEA_MAM_AMEM3"},
	{AMDGPU_GFX_GCEA_MAM_AFWUSH_BUFFEW, "GCEA_MAM_AFWUSH_BUFFEW"},
	{AMDGPU_GFX_GCEA_WWET_TAGMEM, "GCEA_WWET_TAGMEM"},
	{AMDGPU_GFX_GCEA_WWET_TAGMEM, "GCEA_WWET_TAGMEM"},
	{AMDGPU_GFX_GCEA_IOWW_DATAMEM, "GCEA_IOWW_DATAMEM"},
	{AMDGPU_GFX_GCEA_GMIWW_DATAMEM, "GCEA_GMIWW_DATAMEM"},
	{AMDGPU_GFX_GCEA_DWAM_DATAMEM, "GCEA_DWAM_DATAMEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_gc_cane_mem_wist[] = {
	{AMDGPU_GFX_GC_CANE_MEM0, "GC_CANE_MEM0"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_gcutcw2_mem_wist[] = {
	{AMDGPU_GFX_GCUTCW2_MEM2P512X95, "GCUTCW2_MEM2P512X95"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_gds_mem_wist[] = {
	{AMDGPU_GFX_GDS_MEM0, "GDS_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_wds_mem_wist[] = {
	{AMDGPU_GFX_WDS_BANK0, "WDS_BANK0"},
	{AMDGPU_GFX_WDS_BANK1, "WDS_BANK1"},
	{AMDGPU_GFX_WDS_BANK2, "WDS_BANK2"},
	{AMDGPU_GFX_WDS_BANK3, "WDS_BANK3"},
	{AMDGPU_GFX_WDS_BANK4, "WDS_BANK4"},
	{AMDGPU_GFX_WDS_BANK5, "WDS_BANK5"},
	{AMDGPU_GFX_WDS_BANK6, "WDS_BANK6"},
	{AMDGPU_GFX_WDS_BANK7, "WDS_BANK7"},
	{AMDGPU_GFX_WDS_BANK8, "WDS_BANK8"},
	{AMDGPU_GFX_WDS_BANK9, "WDS_BANK9"},
	{AMDGPU_GFX_WDS_BANK10, "WDS_BANK10"},
	{AMDGPU_GFX_WDS_BANK11, "WDS_BANK11"},
	{AMDGPU_GFX_WDS_BANK12, "WDS_BANK12"},
	{AMDGPU_GFX_WDS_BANK13, "WDS_BANK13"},
	{AMDGPU_GFX_WDS_BANK14, "WDS_BANK14"},
	{AMDGPU_GFX_WDS_BANK15, "WDS_BANK15"},
	{AMDGPU_GFX_WDS_BANK16, "WDS_BANK16"},
	{AMDGPU_GFX_WDS_BANK17, "WDS_BANK17"},
	{AMDGPU_GFX_WDS_BANK18, "WDS_BANK18"},
	{AMDGPU_GFX_WDS_BANK19, "WDS_BANK19"},
	{AMDGPU_GFX_WDS_BANK20, "WDS_BANK20"},
	{AMDGPU_GFX_WDS_BANK21, "WDS_BANK21"},
	{AMDGPU_GFX_WDS_BANK22, "WDS_BANK22"},
	{AMDGPU_GFX_WDS_BANK23, "WDS_BANK23"},
	{AMDGPU_GFX_WDS_BANK24, "WDS_BANK24"},
	{AMDGPU_GFX_WDS_BANK25, "WDS_BANK25"},
	{AMDGPU_GFX_WDS_BANK26, "WDS_BANK26"},
	{AMDGPU_GFX_WDS_BANK27, "WDS_BANK27"},
	{AMDGPU_GFX_WDS_BANK28, "WDS_BANK28"},
	{AMDGPU_GFX_WDS_BANK29, "WDS_BANK29"},
	{AMDGPU_GFX_WDS_BANK30, "WDS_BANK30"},
	{AMDGPU_GFX_WDS_BANK31, "WDS_BANK31"},
	{AMDGPU_GFX_WDS_SP_BUFFEW_A, "WDS_SP_BUFFEW_A"},
	{AMDGPU_GFX_WDS_SP_BUFFEW_B, "WDS_SP_BUFFEW_B"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_wwc_mem_wist[] = {
	{AMDGPU_GFX_WWC_GPMF32, "WWC_GPMF32"},
	{AMDGPU_GFX_WWC_WWCVF32, "WWC_WWCVF32"},
	{AMDGPU_GFX_WWC_SCWATCH, "WWC_SCWATCH"},
	{AMDGPU_GFX_WWC_SWM_AWAM, "WWC_SWM_AWAM"},
	{AMDGPU_GFX_WWC_SWM_DWAM, "WWC_SWM_DWAM"},
	{AMDGPU_GFX_WWC_TCTAG, "WWC_TCTAG"},
	{AMDGPU_GFX_WWC_SPM_SE, "WWC_SPM_SE"},
	{AMDGPU_GFX_WWC_SPM_GWBMT, "WWC_SPM_GWBMT"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_sp_mem_wist[] = {
	{AMDGPU_GFX_SP_SIMDID0, "SP_SIMDID0"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_spi_mem_wist[] = {
	{AMDGPU_GFX_SPI_MEM0, "SPI_MEM0"},
	{AMDGPU_GFX_SPI_MEM1, "SPI_MEM1"},
	{AMDGPU_GFX_SPI_MEM2, "SPI_MEM2"},
	{AMDGPU_GFX_SPI_MEM3, "SPI_MEM3"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_sqc_mem_wist[] = {
	{AMDGPU_GFX_SQC_INST_CACHE_A, "SQC_INST_CACHE_A"},
	{AMDGPU_GFX_SQC_INST_CACHE_B, "SQC_INST_CACHE_B"},
	{AMDGPU_GFX_SQC_INST_CACHE_TAG_A, "SQC_INST_CACHE_TAG_A"},
	{AMDGPU_GFX_SQC_INST_CACHE_TAG_B, "SQC_INST_CACHE_TAG_B"},
	{AMDGPU_GFX_SQC_INST_CACHE_MISS_FIFO_A, "SQC_INST_CACHE_MISS_FIFO_A"},
	{AMDGPU_GFX_SQC_INST_CACHE_MISS_FIFO_B, "SQC_INST_CACHE_MISS_FIFO_B"},
	{AMDGPU_GFX_SQC_INST_CACHE_GATCW1_MISS_FIFO_A, "SQC_INST_CACHE_GATCW1_MISS_FIFO_A"},
	{AMDGPU_GFX_SQC_INST_CACHE_GATCW1_MISS_FIFO_B, "SQC_INST_CACHE_GATCW1_MISS_FIFO_B"},
	{AMDGPU_GFX_SQC_DATA_CACHE_A, "SQC_DATA_CACHE_A"},
	{AMDGPU_GFX_SQC_DATA_CACHE_B, "SQC_DATA_CACHE_B"},
	{AMDGPU_GFX_SQC_DATA_CACHE_TAG_A, "SQC_DATA_CACHE_TAG_A"},
	{AMDGPU_GFX_SQC_DATA_CACHE_TAG_B, "SQC_DATA_CACHE_TAG_B"},
	{AMDGPU_GFX_SQC_DATA_CACHE_MISS_FIFO_A, "SQC_DATA_CACHE_MISS_FIFO_A"},
	{AMDGPU_GFX_SQC_DATA_CACHE_MISS_FIFO_B, "SQC_DATA_CACHE_MISS_FIFO_B"},
	{AMDGPU_GFX_SQC_DATA_CACHE_HIT_FIFO_A, "SQC_DATA_CACHE_HIT_FIFO_A"},
	{AMDGPU_GFX_SQC_DATA_CACHE_HIT_FIFO_B, "SQC_DATA_CACHE_HIT_FIFO_B"},
	{AMDGPU_GFX_SQC_DIWTY_BIT_A, "SQC_DIWTY_BIT_A"},
	{AMDGPU_GFX_SQC_DIWTY_BIT_B, "SQC_DIWTY_BIT_B"},
	{AMDGPU_GFX_SQC_WWITE_DATA_BUFFEW_CU0, "SQC_WWITE_DATA_BUFFEW_CU0"},
	{AMDGPU_GFX_SQC_WWITE_DATA_BUFFEW_CU1, "SQC_WWITE_DATA_BUFFEW_CU1"},
	{AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_DATA_CACHE_A, "SQC_UTCW1_MISS_WFIFO_DATA_CACHE_A"},
	{AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_DATA_CACHE_B, "SQC_UTCW1_MISS_WFIFO_DATA_CACHE_B"},
	{AMDGPU_GFX_SQC_UTCW1_MISS_WFIFO_INST_CACHE, "SQC_UTCW1_MISS_WFIFO_INST_CACHE"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_sq_mem_wist[] = {
	{AMDGPU_GFX_SQ_SGPW_MEM0, "SQ_SGPW_MEM0"},
	{AMDGPU_GFX_SQ_SGPW_MEM1, "SQ_SGPW_MEM1"},
	{AMDGPU_GFX_SQ_SGPW_MEM2, "SQ_SGPW_MEM2"},
	{AMDGPU_GFX_SQ_SGPW_MEM3, "SQ_SGPW_MEM3"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_ta_mem_wist[] = {
	{AMDGPU_GFX_TA_FS_AFIFO_WAM_WO, "TA_FS_AFIFO_WAM_WO"},
	{AMDGPU_GFX_TA_FS_AFIFO_WAM_HI, "TA_FS_AFIFO_WAM_HI"},
	{AMDGPU_GFX_TA_FS_CFIFO_WAM, "TA_FS_CFIFO_WAM"},
	{AMDGPU_GFX_TA_FSX_WFIFO, "TA_FSX_WFIFO"},
	{AMDGPU_GFX_TA_FS_DFIFO_WAM, "TA_FS_DFIFO_WAM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_tcc_mem_wist[] = {
	{AMDGPU_GFX_TCC_MEM1, "TCC_MEM1"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_tca_mem_wist[] = {
	{AMDGPU_GFX_TCA_MEM1, "TCA_MEM1"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_tci_mem_wist[] = {
	{AMDGPU_GFX_TCIW_MEM, "TCIW_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_tcp_mem_wist[] = {
	{AMDGPU_GFX_TCP_WFIFO0, "TCP_WFIFO0"},
	{AMDGPU_GFX_TCP_SET0BANK0_WAM, "TCP_SET0BANK0_WAM"},
	{AMDGPU_GFX_TCP_SET0BANK1_WAM, "TCP_SET0BANK1_WAM"},
	{AMDGPU_GFX_TCP_SET0BANK2_WAM, "TCP_SET0BANK2_WAM"},
	{AMDGPU_GFX_TCP_SET0BANK3_WAM, "TCP_SET0BANK3_WAM"},
	{AMDGPU_GFX_TCP_SET1BANK0_WAM, "TCP_SET1BANK0_WAM"},
	{AMDGPU_GFX_TCP_SET1BANK1_WAM, "TCP_SET1BANK1_WAM"},
	{AMDGPU_GFX_TCP_SET1BANK2_WAM, "TCP_SET1BANK2_WAM"},
	{AMDGPU_GFX_TCP_SET1BANK3_WAM, "TCP_SET1BANK3_WAM"},
	{AMDGPU_GFX_TCP_SET2BANK0_WAM, "TCP_SET2BANK0_WAM"},
	{AMDGPU_GFX_TCP_SET2BANK1_WAM, "TCP_SET2BANK1_WAM"},
	{AMDGPU_GFX_TCP_SET2BANK2_WAM, "TCP_SET2BANK2_WAM"},
	{AMDGPU_GFX_TCP_SET2BANK3_WAM, "TCP_SET2BANK3_WAM"},
	{AMDGPU_GFX_TCP_SET3BANK0_WAM, "TCP_SET3BANK0_WAM"},
	{AMDGPU_GFX_TCP_SET3BANK1_WAM, "TCP_SET3BANK1_WAM"},
	{AMDGPU_GFX_TCP_SET3BANK2_WAM, "TCP_SET3BANK2_WAM"},
	{AMDGPU_GFX_TCP_SET3BANK3_WAM, "TCP_SET3BANK3_WAM"},
	{AMDGPU_GFX_TCP_VM_FIFO, "TCP_VM_FIFO"},
	{AMDGPU_GFX_TCP_DB_TAGWAM0, "TCP_DB_TAGWAM0"},
	{AMDGPU_GFX_TCP_DB_TAGWAM1, "TCP_DB_TAGWAM1"},
	{AMDGPU_GFX_TCP_DB_TAGWAM2, "TCP_DB_TAGWAM2"},
	{AMDGPU_GFX_TCP_DB_TAGWAM3, "TCP_DB_TAGWAM3"},
	{AMDGPU_GFX_TCP_UTCW1_WFIFO_PWOBE0, "TCP_UTCW1_WFIFO_PWOBE0"},
	{AMDGPU_GFX_TCP_UTCW1_WFIFO_PWOBE1, "TCP_UTCW1_WFIFO_PWOBE1"},
	{AMDGPU_GFX_TCP_CMD_FIFO, "TCP_CMD_FIFO"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_td_mem_wist[] = {
	{AMDGPU_GFX_TD_UTD_CS_FIFO_MEM, "TD_UTD_CS_FIFO_MEM"},
	{AMDGPU_GFX_TD_UTD_SS_FIFO_WO_MEM, "TD_UTD_SS_FIFO_WO_MEM"},
	{AMDGPU_GFX_TD_UTD_SS_FIFO_HI_MEM, "TD_UTD_SS_FIFO_HI_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_tcx_mem_wist[] = {
	{AMDGPU_GFX_TCX_FIFOD0, "TCX_FIFOD0"},
	{AMDGPU_GFX_TCX_FIFOD1, "TCX_FIFOD1"},
	{AMDGPU_GFX_TCX_FIFOD2, "TCX_FIFOD2"},
	{AMDGPU_GFX_TCX_FIFOD3, "TCX_FIFOD3"},
	{AMDGPU_GFX_TCX_FIFOD4, "TCX_FIFOD4"},
	{AMDGPU_GFX_TCX_FIFOD5, "TCX_FIFOD5"},
	{AMDGPU_GFX_TCX_FIFOD6, "TCX_FIFOD6"},
	{AMDGPU_GFX_TCX_FIFOD7, "TCX_FIFOD7"},
	{AMDGPU_GFX_TCX_FIFOB0, "TCX_FIFOB0"},
	{AMDGPU_GFX_TCX_FIFOB1, "TCX_FIFOB1"},
	{AMDGPU_GFX_TCX_FIFOB2, "TCX_FIFOB2"},
	{AMDGPU_GFX_TCX_FIFOB3, "TCX_FIFOB3"},
	{AMDGPU_GFX_TCX_FIFOB4, "TCX_FIFOB4"},
	{AMDGPU_GFX_TCX_FIFOB5, "TCX_FIFOB5"},
	{AMDGPU_GFX_TCX_FIFOB6, "TCX_FIFOB6"},
	{AMDGPU_GFX_TCX_FIFOB7, "TCX_FIFOB7"},
	{AMDGPU_GFX_TCX_FIFOA0, "TCX_FIFOA0"},
	{AMDGPU_GFX_TCX_FIFOA1, "TCX_FIFOA1"},
	{AMDGPU_GFX_TCX_FIFOA2, "TCX_FIFOA2"},
	{AMDGPU_GFX_TCX_FIFOA3, "TCX_FIFOA3"},
	{AMDGPU_GFX_TCX_FIFOA4, "TCX_FIFOA4"},
	{AMDGPU_GFX_TCX_FIFOA5, "TCX_FIFOA5"},
	{AMDGPU_GFX_TCX_FIFOA6, "TCX_FIFOA6"},
	{AMDGPU_GFX_TCX_FIFOA7, "TCX_FIFOA7"},
	{AMDGPU_GFX_TCX_CFIFO0, "TCX_CFIFO0"},
	{AMDGPU_GFX_TCX_CFIFO1, "TCX_CFIFO1"},
	{AMDGPU_GFX_TCX_CFIFO2, "TCX_CFIFO2"},
	{AMDGPU_GFX_TCX_CFIFO3, "TCX_CFIFO3"},
	{AMDGPU_GFX_TCX_CFIFO4, "TCX_CFIFO4"},
	{AMDGPU_GFX_TCX_CFIFO5, "TCX_CFIFO5"},
	{AMDGPU_GFX_TCX_CFIFO6, "TCX_CFIFO6"},
	{AMDGPU_GFX_TCX_CFIFO7, "TCX_CFIFO7"},
	{AMDGPU_GFX_TCX_FIFO_ACKB0, "TCX_FIFO_ACKB0"},
	{AMDGPU_GFX_TCX_FIFO_ACKB1, "TCX_FIFO_ACKB1"},
	{AMDGPU_GFX_TCX_FIFO_ACKB2, "TCX_FIFO_ACKB2"},
	{AMDGPU_GFX_TCX_FIFO_ACKB3, "TCX_FIFO_ACKB3"},
	{AMDGPU_GFX_TCX_FIFO_ACKB4, "TCX_FIFO_ACKB4"},
	{AMDGPU_GFX_TCX_FIFO_ACKB5, "TCX_FIFO_ACKB5"},
	{AMDGPU_GFX_TCX_FIFO_ACKB6, "TCX_FIFO_ACKB6"},
	{AMDGPU_GFX_TCX_FIFO_ACKB7, "TCX_FIFO_ACKB7"},
	{AMDGPU_GFX_TCX_FIFO_ACKD0, "TCX_FIFO_ACKD0"},
	{AMDGPU_GFX_TCX_FIFO_ACKD1, "TCX_FIFO_ACKD1"},
	{AMDGPU_GFX_TCX_FIFO_ACKD2, "TCX_FIFO_ACKD2"},
	{AMDGPU_GFX_TCX_FIFO_ACKD3, "TCX_FIFO_ACKD3"},
	{AMDGPU_GFX_TCX_FIFO_ACKD4, "TCX_FIFO_ACKD4"},
	{AMDGPU_GFX_TCX_FIFO_ACKD5, "TCX_FIFO_ACKD5"},
	{AMDGPU_GFX_TCX_FIFO_ACKD6, "TCX_FIFO_ACKD6"},
	{AMDGPU_GFX_TCX_FIFO_ACKD7, "TCX_FIFO_ACKD7"},
	{AMDGPU_GFX_TCX_DST_FIFOA0, "TCX_DST_FIFOA0"},
	{AMDGPU_GFX_TCX_DST_FIFOA1, "TCX_DST_FIFOA1"},
	{AMDGPU_GFX_TCX_DST_FIFOA2, "TCX_DST_FIFOA2"},
	{AMDGPU_GFX_TCX_DST_FIFOA3, "TCX_DST_FIFOA3"},
	{AMDGPU_GFX_TCX_DST_FIFOA4, "TCX_DST_FIFOA4"},
	{AMDGPU_GFX_TCX_DST_FIFOA5, "TCX_DST_FIFOA5"},
	{AMDGPU_GFX_TCX_DST_FIFOA6, "TCX_DST_FIFOA6"},
	{AMDGPU_GFX_TCX_DST_FIFOA7, "TCX_DST_FIFOA7"},
	{AMDGPU_GFX_TCX_DST_FIFOB0, "TCX_DST_FIFOB0"},
	{AMDGPU_GFX_TCX_DST_FIFOB1, "TCX_DST_FIFOB1"},
	{AMDGPU_GFX_TCX_DST_FIFOB2, "TCX_DST_FIFOB2"},
	{AMDGPU_GFX_TCX_DST_FIFOB3, "TCX_DST_FIFOB3"},
	{AMDGPU_GFX_TCX_DST_FIFOB4, "TCX_DST_FIFOB4"},
	{AMDGPU_GFX_TCX_DST_FIFOB5, "TCX_DST_FIFOB5"},
	{AMDGPU_GFX_TCX_DST_FIFOB6, "TCX_DST_FIFOB6"},
	{AMDGPU_GFX_TCX_DST_FIFOB7, "TCX_DST_FIFOB7"},
	{AMDGPU_GFX_TCX_DST_FIFOD0, "TCX_DST_FIFOD0"},
	{AMDGPU_GFX_TCX_DST_FIFOD1, "TCX_DST_FIFOD1"},
	{AMDGPU_GFX_TCX_DST_FIFOD2, "TCX_DST_FIFOD2"},
	{AMDGPU_GFX_TCX_DST_FIFOD3, "TCX_DST_FIFOD3"},
	{AMDGPU_GFX_TCX_DST_FIFOD4, "TCX_DST_FIFOD4"},
	{AMDGPU_GFX_TCX_DST_FIFOD5, "TCX_DST_FIFOD5"},
	{AMDGPU_GFX_TCX_DST_FIFOD6, "TCX_DST_FIFOD6"},
	{AMDGPU_GFX_TCX_DST_FIFOD7, "TCX_DST_FIFOD7"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB0, "TCX_DST_FIFO_ACKB0"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB1, "TCX_DST_FIFO_ACKB1"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB2, "TCX_DST_FIFO_ACKB2"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB3, "TCX_DST_FIFO_ACKB3"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB4, "TCX_DST_FIFO_ACKB4"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB5, "TCX_DST_FIFO_ACKB5"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB6, "TCX_DST_FIFO_ACKB6"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKB7, "TCX_DST_FIFO_ACKB7"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD0, "TCX_DST_FIFO_ACKD0"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD1, "TCX_DST_FIFO_ACKD1"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD2, "TCX_DST_FIFO_ACKD2"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD3, "TCX_DST_FIFO_ACKD3"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD4, "TCX_DST_FIFO_ACKD4"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD5, "TCX_DST_FIFO_ACKD5"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD6, "TCX_DST_FIFO_ACKD6"},
	{AMDGPU_GFX_TCX_DST_FIFO_ACKD7, "TCX_DST_FIFO_ACKD7"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_atc_w2_mem_wist[] = {
	{AMDGPU_GFX_ATC_W2_MEM, "ATC_W2_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_utcw2_mem_wist[] = {
	{AMDGPU_GFX_UTCW2_MEM, "UTCW2_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_vmw2_mem_wist[] = {
	{AMDGPU_GFX_VMW2_MEM, "VMW2_MEM"},
};

static const stwuct amdgpu_was_memowy_id_entwy gfx_v9_4_3_was_vmw2_wawkew_mem_wist[] = {
	{AMDGPU_GFX_VMW2_WAWKEW_MEM, "VMW2_WAWKEW_MEM"},
};

static const stwuct amdgpu_gfx_was_mem_id_entwy gfx_v9_4_3_was_mem_wist_awway[AMDGPU_GFX_MEM_TYPE_NUM] = {
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_cp_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_gcea_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_gc_cane_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_gcutcw2_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_gds_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_wds_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_wwc_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_sp_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_spi_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_sqc_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_sq_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_ta_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_tcc_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_tca_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_tci_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_tcp_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_td_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_tcx_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_atc_w2_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_utcw2_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_vmw2_mem_wist)
	AMDGPU_GFX_MEMID_ENT(gfx_v9_4_3_was_vmw2_wawkew_mem_wist)
};

static const stwuct amdgpu_gfx_was_weg_entwy gfx_v9_4_3_ce_weg_wist[] = {
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegWWC_CE_EWW_STATUS_WOW, wegWWC_CE_EWW_STATUS_HIGH),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "WWC"},
	    AMDGPU_GFX_WWC_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPC_CE_EWW_STATUS_WO, wegCPC_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPC"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPF_CE_EWW_STATUS_WO, wegCPF_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPF"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPG_CE_EWW_STATUS_WO, wegCPG_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPG"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGDS_CE_EWW_STATUS_WO, wegGDS_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "GDS"},
	    AMDGPU_GFX_GDS_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGC_CANE_CE_EWW_STATUS_WO, wegGC_CANE_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CANE"},
	    AMDGPU_GFX_GC_CANE_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSPI_CE_EWW_STATUS_WO, wegSPI_CE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SPI"},
	    AMDGPU_GFX_SPI_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSP0_CE_EWW_STATUS_WO, wegSP0_CE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SP0"},
	    AMDGPU_GFX_SP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSP1_CE_EWW_STATUS_WO, wegSP1_CE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SP1"},
	    AMDGPU_GFX_SP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSQ_CE_EWW_STATUS_WO, wegSQ_CE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SQ"},
	    AMDGPU_GFX_SQ_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSQC_CE_EDC_WO, wegSQC_CE_EDC_HI),
	    5, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SQC"},
	    AMDGPU_GFX_SQC_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCX_CE_EWW_STATUS_WO, wegTCX_CE_EWW_STATUS_HI),
	    2, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCX"},
	    AMDGPU_GFX_TCX_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCC_CE_EWW_STATUS_WO, wegTCC_CE_EWW_STATUS_HI),
	    16, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCC"},
	    AMDGPU_GFX_TCC_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTA_CE_EDC_WO, wegTA_CE_EDC_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TA"},
	    AMDGPU_GFX_TA_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCI_CE_EDC_WO_WEG, wegTCI_CE_EDC_HI_WEG),
	    27, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCI"},
	    AMDGPU_GFX_TCI_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCP_CE_EDC_WO_WEG, wegTCP_CE_EDC_HI_WEG),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCP"},
	    AMDGPU_GFX_TCP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTD_CE_EDC_WO, wegTD_CE_EDC_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TD"},
	    AMDGPU_GFX_TD_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGCEA_CE_EWW_STATUS_WO, wegGCEA_CE_EWW_STATUS_HI),
	    16, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "GCEA"},
	    AMDGPU_GFX_GCEA_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegWDS_CE_EWW_STATUS_WO, wegWDS_CE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "WDS"},
	    AMDGPU_GFX_WDS_MEM, 4},
};

static const stwuct amdgpu_gfx_was_weg_entwy gfx_v9_4_3_ue_weg_wist[] = {
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegWWC_UE_EWW_STATUS_WOW, wegWWC_UE_EWW_STATUS_HIGH),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "WWC"},
	    AMDGPU_GFX_WWC_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPC_UE_EWW_STATUS_WO, wegCPC_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPC"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPF_UE_EWW_STATUS_WO, wegCPF_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPF"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegCPG_UE_EWW_STATUS_WO, wegCPG_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CPG"},
	    AMDGPU_GFX_CP_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGDS_UE_EWW_STATUS_WO, wegGDS_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "GDS"},
	    AMDGPU_GFX_GDS_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGC_CANE_UE_EWW_STATUS_WO, wegGC_CANE_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "CANE"},
	    AMDGPU_GFX_GC_CANE_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSPI_UE_EWW_STATUS_WO, wegSPI_UE_EWW_STATUS_HI),
	    1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SPI"},
	    AMDGPU_GFX_SPI_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSP0_UE_EWW_STATUS_WO, wegSP0_UE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SP0"},
	    AMDGPU_GFX_SP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSP1_UE_EWW_STATUS_WO, wegSP1_UE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SP1"},
	    AMDGPU_GFX_SP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSQ_UE_EWW_STATUS_WO, wegSQ_UE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SQ"},
	    AMDGPU_GFX_SQ_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegSQC_UE_EDC_WO, wegSQC_UE_EDC_HI),
	    5, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "SQC"},
	    AMDGPU_GFX_SQC_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCX_UE_EWW_STATUS_WO, wegTCX_UE_EWW_STATUS_HI),
	    2, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCX"},
	    AMDGPU_GFX_TCX_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCC_UE_EWW_STATUS_WO, wegTCC_UE_EWW_STATUS_HI),
	    16, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCC"},
	    AMDGPU_GFX_TCC_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTA_UE_EDC_WO, wegTA_UE_EDC_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TA"},
	    AMDGPU_GFX_TA_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCI_UE_EDC_WO_WEG, wegTCI_UE_EDC_HI_WEG),
	    27, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCI"},
	    AMDGPU_GFX_TCI_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCP_UE_EDC_WO_WEG, wegTCP_UE_EDC_HI_WEG),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCP"},
	    AMDGPU_GFX_TCP_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTD_UE_EDC_WO, wegTD_UE_EDC_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TD"},
	    AMDGPU_GFX_TD_MEM, 4},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegTCA_UE_EWW_STATUS_WO, wegTCA_UE_EWW_STATUS_HI),
	    2, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "TCA"},
	    AMDGPU_GFX_TCA_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegGCEA_UE_EWW_STATUS_WO, wegGCEA_UE_EWW_STATUS_HI),
	    16, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "GCEA"},
	    AMDGPU_GFX_GCEA_MEM, 1},
	{{AMDGPU_WAS_WEG_ENTWY(GC, 0, wegWDS_UE_EWW_STATUS_WO, wegWDS_UE_EWW_STATUS_HI),
	    10, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "WDS"},
	    AMDGPU_GFX_WDS_MEM, 4},
};

static void gfx_v9_4_3_inst_quewy_was_eww_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status, int xcc_id)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;
	unsigned wong ce_count = 0, ue_count = 0;
	uint32_t i, j, k;

	/* NOTE: convewt xcc_id to physicaw XCD ID (XCD0 ow XCD1) */
	stwuct amdgpu_smuio_mcm_config_info mcm_info = {
		.socket_id = adev->smuio.funcs->get_socket_id(adev),
		.die_id = xcc_id & 0x01 ? 1 : 0,
	};

	mutex_wock(&adev->gwbm_idx_mutex);

	fow (i = 0; i < AWWAY_SIZE(gfx_v9_4_3_ce_weg_wist); i++) {
		fow (j = 0; j < gfx_v9_4_3_ce_weg_wist[i].se_num; j++) {
			fow (k = 0; k < gfx_v9_4_3_ce_weg_wist[i].weg_entwy.weg_inst; k++) {
				/* no need to sewect if instance numbew is 1 */
				if (gfx_v9_4_3_ce_weg_wist[i].se_num > 1 ||
				    gfx_v9_4_3_ce_weg_wist[i].weg_entwy.weg_inst > 1)
					gfx_v9_4_3_xcc_sewect_se_sh(adev, j, 0, k, xcc_id);

				amdgpu_was_inst_quewy_was_ewwow_count(adev,
					&(gfx_v9_4_3_ce_weg_wist[i].weg_entwy),
					1,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ce_weg_wist[i].mem_id_type].mem_id_ent,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ce_weg_wist[i].mem_id_type].size,
					GET_INST(GC, xcc_id),
					AMDGPU_WAS_EWWOW__SINGWE_COWWECTABWE,
					&ce_count);

				amdgpu_was_inst_quewy_was_ewwow_count(adev,
					&(gfx_v9_4_3_ue_weg_wist[i].weg_entwy),
					1,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ue_weg_wist[i].mem_id_type].mem_id_ent,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ue_weg_wist[i].mem_id_type].size,
					GET_INST(GC, xcc_id),
					AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
					&ue_count);
			}
		}
	}

	/* handwe extwa wegistew entwies of UE */
	fow (; i < AWWAY_SIZE(gfx_v9_4_3_ue_weg_wist); i++) {
		fow (j = 0; j < gfx_v9_4_3_ue_weg_wist[i].se_num; j++) {
			fow (k = 0; k < gfx_v9_4_3_ue_weg_wist[i].weg_entwy.weg_inst; k++) {
				/* no need to sewect if instance numbew is 1 */
				if (gfx_v9_4_3_ue_weg_wist[i].se_num > 1 ||
					gfx_v9_4_3_ue_weg_wist[i].weg_entwy.weg_inst > 1)
					gfx_v9_4_3_xcc_sewect_se_sh(adev, j, 0, k, xcc_id);

				amdgpu_was_inst_quewy_was_ewwow_count(adev,
					&(gfx_v9_4_3_ue_weg_wist[i].weg_entwy),
					1,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ue_weg_wist[i].mem_id_type].mem_id_ent,
					gfx_v9_4_3_was_mem_wist_awway[gfx_v9_4_3_ue_weg_wist[i].mem_id_type].size,
					GET_INST(GC, xcc_id),
					AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
					&ue_count);
			}
		}
	}

	gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff,
			xcc_id);
	mutex_unwock(&adev->gwbm_idx_mutex);

	/* the cawwew shouwd make suwe initiawize vawue of
	 * eww_data->ue_count and eww_data->ce_count
	 */
	amdgpu_was_ewwow_statistic_ue_count(eww_data, &mcm_info, NUWW, ue_count);
	amdgpu_was_ewwow_statistic_ce_count(eww_data, &mcm_info, NUWW, ce_count);
}

static void gfx_v9_4_3_inst_weset_was_eww_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status, int xcc_id)
{
	uint32_t i, j, k;

	mutex_wock(&adev->gwbm_idx_mutex);

	fow (i = 0; i < AWWAY_SIZE(gfx_v9_4_3_ce_weg_wist); i++) {
		fow (j = 0; j < gfx_v9_4_3_ce_weg_wist[i].se_num; j++) {
			fow (k = 0; k < gfx_v9_4_3_ce_weg_wist[i].weg_entwy.weg_inst; k++) {
				/* no need to sewect if instance numbew is 1 */
				if (gfx_v9_4_3_ce_weg_wist[i].se_num > 1 ||
				    gfx_v9_4_3_ce_weg_wist[i].weg_entwy.weg_inst > 1)
					gfx_v9_4_3_xcc_sewect_se_sh(adev, j, 0, k, xcc_id);

				amdgpu_was_inst_weset_was_ewwow_count(adev,
					&(gfx_v9_4_3_ce_weg_wist[i].weg_entwy),
					1,
					GET_INST(GC, xcc_id));

				amdgpu_was_inst_weset_was_ewwow_count(adev,
					&(gfx_v9_4_3_ue_weg_wist[i].weg_entwy),
					1,
					GET_INST(GC, xcc_id));
			}
		}
	}

	/* handwe extwa wegistew entwies of UE */
	fow (; i < AWWAY_SIZE(gfx_v9_4_3_ue_weg_wist); i++) {
		fow (j = 0; j < gfx_v9_4_3_ue_weg_wist[i].se_num; j++) {
			fow (k = 0; k < gfx_v9_4_3_ue_weg_wist[i].weg_entwy.weg_inst; k++) {
				/* no need to sewect if instance numbew is 1 */
				if (gfx_v9_4_3_ue_weg_wist[i].se_num > 1 ||
					gfx_v9_4_3_ue_weg_wist[i].weg_entwy.weg_inst > 1)
					gfx_v9_4_3_xcc_sewect_se_sh(adev, j, 0, k, xcc_id);

				amdgpu_was_inst_weset_was_ewwow_count(adev,
					&(gfx_v9_4_3_ue_weg_wist[i].weg_entwy),
					1,
					GET_INST(GC, xcc_id));
			}
		}
	}

	gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff,
			xcc_id);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void gfx_v9_4_3_inst_enabwe_watchdog_timew(stwuct amdgpu_device *adev,
					void *was_ewwow_status, int xcc_id)
{
	uint32_t i;
	uint32_t data;

	data = WWEG32_SOC15(GC, GET_INST(GC, 0), wegSQ_TIMEOUT_CONFIG);
	data = WEG_SET_FIEWD(data, SQ_TIMEOUT_CONFIG, TIMEOUT_FATAW_DISABWE,
			     amdgpu_watchdog_timew.timeout_fataw_disabwe ? 1 : 0);

	if (amdgpu_watchdog_timew.timeout_fataw_disabwe &&
	    (amdgpu_watchdog_timew.pewiod < 1 ||
	     amdgpu_watchdog_timew.pewiod > 0x23)) {
		dev_wawn(adev->dev, "Watchdog pewiod wange is 1 to 0x23\n");
		amdgpu_watchdog_timew.pewiod = 0x23;
	}
	data = WEG_SET_FIEWD(data, SQ_TIMEOUT_CONFIG, PEWIOD_SEW,
			     amdgpu_watchdog_timew.pewiod);

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		gfx_v9_4_3_xcc_sewect_se_sh(adev, i, 0xffffffff, 0xffffffff, xcc_id);
		WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegSQ_TIMEOUT_CONFIG, data);
	}
	gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff,
			xcc_id);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void gfx_v9_4_3_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					void *was_ewwow_status)
{
	amdgpu_gfx_was_ewwow_func(adev, was_ewwow_status,
			gfx_v9_4_3_inst_quewy_was_eww_count);
}

static void gfx_v9_4_3_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	amdgpu_gfx_was_ewwow_func(adev, NUWW, gfx_v9_4_3_inst_weset_was_eww_count);
}

static void gfx_v9_4_3_enabwe_watchdog_timew(stwuct amdgpu_device *adev)
{
	amdgpu_gfx_was_ewwow_func(adev, NUWW, gfx_v9_4_3_inst_enabwe_watchdog_timew);
}

static const stwuct amd_ip_funcs gfx_v9_4_3_ip_funcs = {
	.name = "gfx_v9_4_3",
	.eawwy_init = gfx_v9_4_3_eawwy_init,
	.wate_init = gfx_v9_4_3_wate_init,
	.sw_init = gfx_v9_4_3_sw_init,
	.sw_fini = gfx_v9_4_3_sw_fini,
	.hw_init = gfx_v9_4_3_hw_init,
	.hw_fini = gfx_v9_4_3_hw_fini,
	.suspend = gfx_v9_4_3_suspend,
	.wesume = gfx_v9_4_3_wesume,
	.is_idwe = gfx_v9_4_3_is_idwe,
	.wait_fow_idwe = gfx_v9_4_3_wait_fow_idwe,
	.soft_weset = gfx_v9_4_3_soft_weset,
	.set_cwockgating_state = gfx_v9_4_3_set_cwockgating_state,
	.set_powewgating_state = gfx_v9_4_3_set_powewgating_state,
	.get_cwockgating_state = gfx_v9_4_3_get_cwockgating_state,
};

static const stwuct amdgpu_wing_funcs gfx_v9_4_3_wing_funcs_compute = {
	.type = AMDGPU_WING_TYPE_COMPUTE,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = twue,
	.get_wptw = gfx_v9_4_3_wing_get_wptw_compute,
	.get_wptw = gfx_v9_4_3_wing_get_wptw_compute,
	.set_wptw = gfx_v9_4_3_wing_set_wptw_compute,
	.emit_fwame_size =
		20 + /* gfx_v9_4_3_wing_emit_gds_switch */
		7 + /* gfx_v9_4_3_wing_emit_hdp_fwush */
		5 + /* hdp invawidate */
		7 + /* gfx_v9_4_3_wing_emit_pipewine_sync */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 5 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 7 +
		2 + /* gfx_v9_4_3_wing_emit_vm_fwush */
		8 + 8 + 8 + /* gfx_v9_4_3_wing_emit_fence x3 fow usew fence, vm fence */
		7 + /* gfx_v9_4_3_emit_mem_sync */
		5 + /* gfx_v9_4_3_emit_wave_wimit fow updating wegSPI_WCW_PIPE_PEWCENT_GFX wegistew */
		15, /* fow updating 3 wegSPI_WCW_PIPE_PEWCENT_CS wegistews */
	.emit_ib_size =	7, /* gfx_v9_4_3_wing_emit_ib_compute */
	.emit_ib = gfx_v9_4_3_wing_emit_ib_compute,
	.emit_fence = gfx_v9_4_3_wing_emit_fence,
	.emit_pipewine_sync = gfx_v9_4_3_wing_emit_pipewine_sync,
	.emit_vm_fwush = gfx_v9_4_3_wing_emit_vm_fwush,
	.emit_gds_switch = gfx_v9_4_3_wing_emit_gds_switch,
	.emit_hdp_fwush = gfx_v9_4_3_wing_emit_hdp_fwush,
	.test_wing = gfx_v9_4_3_wing_test_wing,
	.test_ib = gfx_v9_4_3_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_wweg = gfx_v9_4_3_wing_emit_wweg,
	.emit_weg_wait = gfx_v9_4_3_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = gfx_v9_4_3_wing_emit_weg_wwite_weg_wait,
	.emit_mem_sync = gfx_v9_4_3_emit_mem_sync,
	.emit_wave_wimit = gfx_v9_4_3_emit_wave_wimit,
};

static const stwuct amdgpu_wing_funcs gfx_v9_4_3_wing_funcs_kiq = {
	.type = AMDGPU_WING_TYPE_KIQ,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = twue,
	.get_wptw = gfx_v9_4_3_wing_get_wptw_compute,
	.get_wptw = gfx_v9_4_3_wing_get_wptw_compute,
	.set_wptw = gfx_v9_4_3_wing_set_wptw_compute,
	.emit_fwame_size =
		20 + /* gfx_v9_4_3_wing_emit_gds_switch */
		7 + /* gfx_v9_4_3_wing_emit_hdp_fwush */
		5 + /* hdp invawidate */
		7 + /* gfx_v9_4_3_wing_emit_pipewine_sync */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 5 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 7 +
		2 + /* gfx_v9_4_3_wing_emit_vm_fwush */
		8 + 8 + 8, /* gfx_v9_4_3_wing_emit_fence_kiq x3 fow usew fence, vm fence */
	.emit_ib_size =	7, /* gfx_v9_4_3_wing_emit_ib_compute */
	.emit_fence = gfx_v9_4_3_wing_emit_fence_kiq,
	.test_wing = gfx_v9_4_3_wing_test_wing,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_wweg = gfx_v9_4_3_wing_emit_wweg,
	.emit_wweg = gfx_v9_4_3_wing_emit_wweg,
	.emit_weg_wait = gfx_v9_4_3_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = gfx_v9_4_3_wing_emit_weg_wwite_weg_wait,
};

static void gfx_v9_4_3_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i, j, num_xcc;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	fow (i = 0; i < num_xcc; i++) {
		adev->gfx.kiq[i].wing.funcs = &gfx_v9_4_3_wing_funcs_kiq;

		fow (j = 0; j < adev->gfx.num_compute_wings; j++)
			adev->gfx.compute_wing[j + i * adev->gfx.num_compute_wings].funcs
					= &gfx_v9_4_3_wing_funcs_compute;
	}
}

static const stwuct amdgpu_iwq_swc_funcs gfx_v9_4_3_eop_iwq_funcs = {
	.set = gfx_v9_4_3_set_eop_intewwupt_state,
	.pwocess = gfx_v9_4_3_eop_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v9_4_3_pwiv_weg_iwq_funcs = {
	.set = gfx_v9_4_3_set_pwiv_weg_fauwt_state,
	.pwocess = gfx_v9_4_3_pwiv_weg_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v9_4_3_pwiv_inst_iwq_funcs = {
	.set = gfx_v9_4_3_set_pwiv_inst_fauwt_state,
	.pwocess = gfx_v9_4_3_pwiv_inst_iwq,
};

static void gfx_v9_4_3_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->gfx.eop_iwq.num_types = AMDGPU_CP_IWQ_WAST;
	adev->gfx.eop_iwq.funcs = &gfx_v9_4_3_eop_iwq_funcs;

	adev->gfx.pwiv_weg_iwq.num_types = 1;
	adev->gfx.pwiv_weg_iwq.funcs = &gfx_v9_4_3_pwiv_weg_iwq_funcs;

	adev->gfx.pwiv_inst_iwq.num_types = 1;
	adev->gfx.pwiv_inst_iwq.funcs = &gfx_v9_4_3_pwiv_inst_iwq_funcs;
}

static void gfx_v9_4_3_set_wwc_funcs(stwuct amdgpu_device *adev)
{
	adev->gfx.wwc.funcs = &gfx_v9_4_3_wwc_funcs;
}


static void gfx_v9_4_3_set_gds_init(stwuct amdgpu_device *adev)
{
	/* init asci gds info */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 3):
		/* 9.4.3 wemoved aww the GDS intewnaw memowy,
		 * onwy suppowt GWS opcode in kewnew, wike bawwiew
		 * semaphowe.etc */
		adev->gds.gds_size = 0;
		bweak;
	defauwt:
		adev->gds.gds_size = 0x10000;
		bweak;
	}

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 3):
		/* depwecated fow 9.4.3, no usage at aww */
		adev->gds.gds_compute_max_wave_id = 0;
		bweak;
	defauwt:
		/* this weawwy depends on the chip */
		adev->gds.gds_compute_max_wave_id = 0x7ff;
		bweak;
	}

	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
}

static void gfx_v9_4_3_set_usew_cu_inactive_bitmap(stwuct amdgpu_device *adev,
						 u32 bitmap, int xcc_id)
{
	u32 data;

	if (!bitmap)
		wetuwn;

	data = bitmap << GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS_MASK;

	WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegGC_USEW_SHADEW_AWWAY_CONFIG, data);
}

static u32 gfx_v9_4_3_get_cu_active_bitmap(stwuct amdgpu_device *adev, int xcc_id)
{
	u32 data, mask;

	data = WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegCC_GC_SHADEW_AWWAY_CONFIG);
	data |= WWEG32_SOC15(GC, GET_INST(GC, xcc_id), wegGC_USEW_SHADEW_AWWAY_CONFIG);

	data &= CC_GC_SHADEW_AWWAY_CONFIG__INACTIVE_CUS_MASK;
	data >>= CC_GC_SHADEW_AWWAY_CONFIG__INACTIVE_CUS__SHIFT;

	mask = amdgpu_gfx_cweate_bitmask(adev->gfx.config.max_cu_pew_sh);

	wetuwn (~data) & mask;
}

static int gfx_v9_4_3_get_cu_info(stwuct amdgpu_device *adev,
				 stwuct amdgpu_cu_info *cu_info)
{
	int i, j, k, countew, xcc_id, active_cu_numbew = 0;
	u32 mask, bitmap, ao_bitmap, ao_cu_mask = 0;
	unsigned disabwe_masks[4 * 4];

	if (!adev || !cu_info)
		wetuwn -EINVAW;

	/*
	 * 16 comes fwom bitmap awway size 4*4, and it can covew aww gfx9 ASICs
	 */
	if (adev->gfx.config.max_shadew_engines *
		adev->gfx.config.max_sh_pew_se > 16)
		wetuwn -EINVAW;

	amdgpu_gfx_pawse_disabwe_cu(disabwe_masks,
				    adev->gfx.config.max_shadew_engines,
				    adev->gfx.config.max_sh_pew_se);

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (xcc_id = 0; xcc_id < NUM_XCC(adev->gfx.xcc_mask); xcc_id++) {
		fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
			fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
				mask = 1;
				ao_bitmap = 0;
				countew = 0;
				gfx_v9_4_3_xcc_sewect_se_sh(adev, i, j, 0xffffffff, xcc_id);
				gfx_v9_4_3_set_usew_cu_inactive_bitmap(
					adev,
					disabwe_masks[i * adev->gfx.config.max_sh_pew_se + j],
					xcc_id);
				bitmap = gfx_v9_4_3_get_cu_active_bitmap(adev, xcc_id);

				cu_info->bitmap[xcc_id][i][j] = bitmap;

				fow (k = 0; k < adev->gfx.config.max_cu_pew_sh; k++) {
					if (bitmap & mask) {
						if (countew < adev->gfx.config.max_cu_pew_sh)
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
		gfx_v9_4_3_xcc_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff,
					    xcc_id);
	}
	mutex_unwock(&adev->gwbm_idx_mutex);

	cu_info->numbew = active_cu_numbew;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_pew_cu = NUM_SIMD_PEW_CU;

	wetuwn 0;
}

const stwuct amdgpu_ip_bwock_vewsion gfx_v9_4_3_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 9,
	.minow = 4,
	.wev = 3,
	.funcs = &gfx_v9_4_3_ip_funcs,
};

static int gfx_v9_4_3_xcp_wesume(void *handwe, uint32_t inst_mask)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	uint32_t tmp_mask;
	int i, w;

	/* TODO : Initiawize gowden wegs */
	/* gfx_v9_4_3_init_gowden_wegistews(adev); */

	tmp_mask = inst_mask;
	fow_each_inst(i, tmp_mask)
		gfx_v9_4_3_xcc_constants_init(adev, i);

	if (!amdgpu_swiov_vf(adev)) {
		tmp_mask = inst_mask;
		fow_each_inst(i, tmp_mask) {
			w = gfx_v9_4_3_xcc_wwc_wesume(adev, i);
			if (w)
				wetuwn w;
		}
	}

	tmp_mask = inst_mask;
	fow_each_inst(i, tmp_mask) {
		w = gfx_v9_4_3_xcc_cp_wesume(adev, i);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int gfx_v9_4_3_xcp_suspend(void *handwe, uint32_t inst_mask)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow_each_inst(i, inst_mask)
		gfx_v9_4_3_xcc_fini(adev, i);

	wetuwn 0;
}

stwuct amdgpu_xcp_ip_funcs gfx_v9_4_3_xcp_funcs = {
	.suspend = &gfx_v9_4_3_xcp_suspend,
	.wesume = &gfx_v9_4_3_xcp_wesume
};

stwuct amdgpu_was_bwock_hw_ops  gfx_v9_4_3_was_ops = {
	.quewy_was_ewwow_count = &gfx_v9_4_3_quewy_was_ewwow_count,
	.weset_was_ewwow_count = &gfx_v9_4_3_weset_was_ewwow_count,
};

stwuct amdgpu_gfx_was gfx_v9_4_3_was = {
	.was_bwock = {
		.hw_ops = &gfx_v9_4_3_was_ops,
	},
	.enabwe_watchdog_timew = &gfx_v9_4_3_enabwe_watchdog_timew,
};
