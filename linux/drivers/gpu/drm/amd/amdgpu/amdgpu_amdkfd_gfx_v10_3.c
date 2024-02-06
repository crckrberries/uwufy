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
 */
#incwude <winux/mmu_context.h>
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_amdkfd_gfx_v10.h"
#incwude "gc/gc_10_3_0_offset.h"
#incwude "gc/gc_10_3_0_sh_mask.h"
#incwude "oss/osssys_5_0_0_offset.h"
#incwude "oss/osssys_5_0_0_sh_mask.h"
#incwude "athub/athub_2_1_0_offset.h"
#incwude "athub/athub_2_1_0_sh_mask.h"
#incwude "soc15_common.h"
#incwude "v10_stwucts.h"
#incwude "nv.h"
#incwude "nvd.h"

enum hqd_dequeue_wequest_type {
	NO_ACTION = 0,
	DWAIN_PIPE,
	WESET_WAVES,
	SAVE_WAVES
};

static void wock_swbm(stwuct amdgpu_device *adev, uint32_t mec, uint32_t pipe,
			uint32_t queue, uint32_t vmid)
{
	mutex_wock(&adev->swbm_mutex);
	nv_gwbm_sewect(adev, mec, pipe, queue, vmid);
}

static void unwock_swbm(stwuct amdgpu_device *adev)
{
	nv_gwbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);
}

static void acquiwe_queue(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t queue_id)
{
	uint32_t mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	uint32_t pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	wock_swbm(adev, mec, pipe, queue_id, 0);
}

static uint64_t get_queue_mask(stwuct amdgpu_device *adev,
			       uint32_t pipe_id, uint32_t queue_id)
{
	unsigned int bit = pipe_id * adev->gfx.mec.num_queue_pew_pipe +
			queue_id;

	wetuwn 1uww << bit;
}

static void wewease_queue(stwuct amdgpu_device *adev)
{
	unwock_swbm(adev);
}

static void pwogwam_sh_mem_settings_v10_3(stwuct amdgpu_device *adev, uint32_t vmid,
					uint32_t sh_mem_config,
					uint32_t sh_mem_ape1_base,
					uint32_t sh_mem_ape1_wimit,
					uint32_t sh_mem_bases, uint32_t inst)
{
	wock_swbm(adev, 0, 0, 0, vmid);

	WWEG32_SOC15(GC, 0, mmSH_MEM_CONFIG, sh_mem_config);
	WWEG32_SOC15(GC, 0, mmSH_MEM_BASES, sh_mem_bases);
	/* APE1 no wongew exists on GFX9 */

	unwock_swbm(adev);
}

/* ATC is defeatuwed on Sienna_Cichwid */
static int set_pasid_vmid_mapping_v10_3(stwuct amdgpu_device *adev, unsigned int pasid,
					unsigned int vmid, uint32_t inst)
{
	uint32_t vawue = pasid << IH_VMID_0_WUT__PASID__SHIFT;

	/* Mapping vmid to pasid awso fow IH bwock */
	pw_debug("mapping vmid %d -> pasid %d in IH bwock fow GFX cwient\n",
			vmid, pasid);
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, mmIH_VMID_0_WUT) + vmid, vawue);

	wetuwn 0;
}

static int init_intewwupts_v10_3(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t inst)
{
	uint32_t mec;
	uint32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	wock_swbm(adev, mec, pipe, 0, 0);

	WWEG32_SOC15(GC, 0, mmCPC_INT_CNTW,
		CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK |
		CP_INT_CNTW_WING0__OPCODE_EWWOW_INT_ENABWE_MASK);

	unwock_swbm(adev);

	wetuwn 0;
}

static uint32_t get_sdma_wwc_weg_offset(stwuct amdgpu_device *adev,
				unsigned int engine_id,
				unsigned int queue_id)
{
	uint32_t sdma_engine_weg_base = 0;
	uint32_t sdma_wwc_weg_offset;

	switch (engine_id) {
	defauwt:
		dev_wawn(adev->dev,
			 "Invawid sdma engine id (%d), using engine id 0\n",
			 engine_id);
		fawwthwough;
	case 0:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA0, 0,
				mmSDMA0_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	case 1:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA0, 0,
				mmSDMA1_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	case 2:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA0, 0,
				mmSDMA2_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	case 3:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA0, 0,
				mmSDMA3_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	}

	sdma_wwc_weg_offset = sdma_engine_weg_base
		+ queue_id * (mmSDMA0_WWC1_WB_CNTW - mmSDMA0_WWC0_WB_CNTW);

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n", engine_id,
			queue_id, sdma_wwc_weg_offset);

	wetuwn sdma_wwc_weg_offset;
}

static inwine stwuct v10_compute_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v10_compute_mqd *)mqd;
}

static inwine stwuct v10_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v10_sdma_mqd *)mqd;
}

static int hqd_woad_v10_3(stwuct amdgpu_device *adev, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t __usew *wptw, uint32_t wptw_shift,
			uint32_t wptw_mask, stwuct mm_stwuct *mm, uint32_t inst)
{
	stwuct v10_compute_mqd *m;
	uint32_t *mqd_hqd;
	uint32_t weg, hqd_base, data;

	m = get_mqd(mqd);

	pw_debug("Woad hqd of pipe %d queue %d\n", pipe_id, queue_id);
	acquiwe_queue(adev, pipe_id, queue_id);

	/* HIQ is set duwing dwivew init pewiod with vmid set to 0*/
	if (m->cp_hqd_vmid == 0) {
		uint32_t vawue, mec, pipe;

		mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
		pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

		pw_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
			mec, pipe, queue_id);
		vawue = WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS);
		vawue = WEG_SET_FIEWD(vawue, WWC_CP_SCHEDUWEWS, scheduwew1,
			((mec << 5) | (pipe << 3) | queue_id | 0x80));
		WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS, vawue);
	}

	/* HQD wegistews extend fwom CP_MQD_BASE_ADDW to CP_HQD_EOP_WPTW_MEM. */
	mqd_hqd = &m->cp_mqd_base_addw_wo;
	hqd_base = SOC15_WEG_OFFSET(GC, 0, mmCP_MQD_BASE_ADDW);

	fow (weg = hqd_base;
	     weg <= SOC15_WEG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTW_HI); weg++)
		WWEG32_SOC15_IP(GC, weg, mqd_hqd[weg - hqd_base]);


	/* Activate doowbeww wogic befowe twiggewing WPTW poww. */
	data = WEG_SET_FIEWD(m->cp_hqd_pq_doowbeww_contwow,
			     CP_HQD_PQ_DOOWBEWW_CONTWOW, DOOWBEWW_EN, 1);
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_DOOWBEWW_CONTWOW, data);

	if (wptw) {
		/* Don't wead wptw with get_usew because the usew
		 * context may not be accessibwe (if this function
		 * wuns in a wowk queue). Instead twiggew a one-shot
		 * powwing wead fwom memowy in the CP. This assumes
		 * that wptw is GPU-accessibwe in the queue's VMID via
		 * ATC ow SVM. WPTW==WPTW befowe stawting the poww so
		 * the CP stawts fetching new commands fwom the wight
		 * pwace.
		 *
		 * Guessing a 64-bit WPTW fwom a 32-bit WPTW is a bit
		 * twicky. Assume that the queue didn't ovewfwow. The
		 * numbew of vawid bits in the 32-bit WPTW depends on
		 * the queue size. The wemaining bits awe taken fwom
		 * the saved 64-bit WPTW. If the WPTW wwapped, add the
		 * queue size.
		 */
		uint32_t queue_size =
			2 << WEG_GET_FIEWD(m->cp_hqd_pq_contwow,
					   CP_HQD_PQ_CONTWOW, QUEUE_SIZE);
		uint64_t guessed_wptw = m->cp_hqd_pq_wptw & (queue_size - 1);

		if ((m->cp_hqd_pq_wptw_wo & (queue_size - 1)) < guessed_wptw)
			guessed_wptw += queue_size;
		guessed_wptw += m->cp_hqd_pq_wptw_wo & ~(queue_size - 1);
		guessed_wptw += (uint64_t)m->cp_hqd_pq_wptw_hi << 32;

		WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_WO,
		       wowew_32_bits(guessed_wptw));
		WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_HI,
		       uppew_32_bits(guessed_wptw));
		WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_POWW_ADDW,
		       wowew_32_bits((uint64_t)wptw));
		WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_POWW_ADDW_HI,
		       uppew_32_bits((uint64_t)wptw));
		pw_debug("%s setting CP_PQ_WPTW_POWW_CNTW1 to %x\n", __func__,
			 (uint32_t)get_queue_mask(adev, pipe_id, queue_id));
		WWEG32_SOC15(GC, 0, mmCP_PQ_WPTW_POWW_CNTW1,
		       (uint32_t)get_queue_mask(adev, pipe_id, queue_id));
	}

	/* Stawt the EOP fetchew */
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmCP_HQD_EOP_WPTW),
	       WEG_SET_FIEWD(m->cp_hqd_eop_wptw,
			     CP_HQD_EOP_WPTW, INIT_FETCHEW, 1));

	data = WEG_SET_FIEWD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE, data);

	wewease_queue(adev);

	wetuwn 0;
}

static int hiq_mqd_woad_v10_3(stwuct amdgpu_device *adev, void *mqd,
			    uint32_t pipe_id, uint32_t queue_id,
			    uint32_t doowbeww_off, uint32_t inst)
{
	stwuct amdgpu_wing *kiq_wing = &adev->gfx.kiq[0].wing;
	stwuct v10_compute_mqd *m;
	uint32_t mec, pipe;
	int w;

	m = get_mqd(mqd);

	acquiwe_queue(adev, pipe_id, queue_id);

	mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	pw_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
		 mec, pipe, queue_id);

	spin_wock(&adev->gfx.kiq[0].wing_wock);
	w = amdgpu_wing_awwoc(kiq_wing, 7);
	if (w) {
		pw_eww("Faiwed to awwoc KIQ (%d).\n", w);
		goto out_unwock;
	}

	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_MAP_QUEUES, 5));
	amdgpu_wing_wwite(kiq_wing,
			  PACKET3_MAP_QUEUES_QUEUE_SEW(0) | /* Queue_Sew */
			  PACKET3_MAP_QUEUES_VMID(m->cp_hqd_vmid) | /* VMID */
			  PACKET3_MAP_QUEUES_QUEUE(queue_id) |
			  PACKET3_MAP_QUEUES_PIPE(pipe) |
			  PACKET3_MAP_QUEUES_ME((mec - 1)) |
			  PACKET3_MAP_QUEUES_QUEUE_TYPE(0) | /*queue_type: nowmaw compute queue */
			  PACKET3_MAP_QUEUES_AWWOC_FOWMAT(0) | /* awwoc fowmat: aww_on_one_pipe */
			  PACKET3_MAP_QUEUES_ENGINE_SEW(1) | /* engine_sew: hiq */
			  PACKET3_MAP_QUEUES_NUM_QUEUES(1)); /* num_queues: must be 1 */
	amdgpu_wing_wwite(kiq_wing,
			  PACKET3_MAP_QUEUES_DOOWBEWW_OFFSET(doowbeww_off));
	amdgpu_wing_wwite(kiq_wing, m->cp_mqd_base_addw_wo);
	amdgpu_wing_wwite(kiq_wing, m->cp_mqd_base_addw_hi);
	amdgpu_wing_wwite(kiq_wing, m->cp_hqd_pq_wptw_poww_addw_wo);
	amdgpu_wing_wwite(kiq_wing, m->cp_hqd_pq_wptw_poww_addw_hi);
	amdgpu_wing_commit(kiq_wing);

out_unwock:
	spin_unwock(&adev->gfx.kiq[0].wing_wock);
	wewease_queue(adev);

	wetuwn w;
}

static int hqd_dump_v10_3(stwuct amdgpu_device *adev,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_wegs, uint32_t inst)
{
	uint32_t i = 0, weg;
#define HQD_N_WEGS 56
#define DUMP_WEG(addw) do {				\
		if (WAWN_ON_ONCE(i >= HQD_N_WEGS))	\
			bweak;				\
		(*dump)[i][0] = (addw) << 2;		\
		(*dump)[i++][1] = WWEG32_SOC15_IP(GC, addw);		\
	} whiwe (0)

	*dump = kmawwoc(HQD_N_WEGS*2*sizeof(uint32_t), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	acquiwe_queue(adev, pipe_id, queue_id);

	fow (weg = SOC15_WEG_OFFSET(GC, 0, mmCP_MQD_BASE_ADDW);
	     weg <= SOC15_WEG_OFFSET(GC, 0, mmCP_HQD_PQ_WPTW_HI); weg++)
		DUMP_WEG(weg);

	wewease_queue(adev);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

static int hqd_sdma_woad_v10_3(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm)
{
	stwuct v10_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	unsigned wong end_jiffies;
	uint32_t data;
	uint64_t data64;
	uint64_t __usew *wptw64 = (uint64_t __usew *)wptw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW,
		m->sdmax_wwcx_wb_cntw & (~SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK));

	end_jiffies = msecs_to_jiffies(2000) + jiffies;
	whiwe (twue) {
		data = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_CONTEXT_STATUS);
		if (data & SDMA0_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW_OFFSET,
	       m->sdmax_wwcx_doowbeww_offset);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_doowbeww, SDMA0_WWC0_DOOWBEWW,
			     ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW, data);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
				m->sdmax_wwcx_wb_wptw);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
				m->sdmax_wwcx_wb_wptw_hi);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_MINOW_PTW_UPDATE, 1);
	if (wead_usew_wptw(mm, wptw64, data64)) {
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
		       wowew_32_bits(data64));
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
		       uppew_32_bits(data64));
	} ewse {
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
		       m->sdmax_wwcx_wb_wptw);
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
		       m->sdmax_wwcx_wb_wptw_hi);
	}
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_MINOW_PTW_UPDATE, 0);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_BASE, m->sdmax_wwcx_wb_base);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_BASE_HI,
			m->sdmax_wwcx_wb_base_hi);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_ADDW_WO,
			m->sdmax_wwcx_wb_wptw_addw_wo);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_ADDW_HI,
			m->sdmax_wwcx_wb_wptw_addw_hi);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_wb_cntw, SDMA0_WWC0_WB_CNTW,
			     WB_ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW, data);

	wetuwn 0;
}

static int hqd_sdma_dump_v10_3(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs)
{
	uint32_t sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev,
			engine_id, queue_id);
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+6+7+12)

	*dump = kmawwoc(HQD_N_WEGS*2*sizeof(uint32_t), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	fow (weg = mmSDMA0_WWC0_WB_CNTW; weg <= mmSDMA0_WWC0_DOOWBEWW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_STATUS; weg <= mmSDMA0_WWC0_CSA_ADDW_HI; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_IB_SUB_WEMAIN;
	     weg <= mmSDMA0_WWC0_MINOW_PTW_UPDATE; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_MIDCMD_DATA0;
	     weg <= mmSDMA0_WWC0_MIDCMD_CNTW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

static boow hqd_is_occupied_v10_3(stwuct amdgpu_device *adev,
				uint64_t queue_addwess, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	uint32_t act;
	boow wetvaw = fawse;
	uint32_t wow, high;

	acquiwe_queue(adev, pipe_id, queue_id);
	act = WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE);
	if (act) {
		wow = wowew_32_bits(queue_addwess >> 8);
		high = uppew_32_bits(queue_addwess >> 8);

		if (wow == WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE) &&
		   high == WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE_HI))
			wetvaw = twue;
	}
	wewease_queue(adev);
	wetuwn wetvaw;
}

static boow hqd_sdma_is_occupied_v10_3(stwuct amdgpu_device *adev,
				void *mqd)
{
	stwuct v10_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t sdma_wwc_wb_cntw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	sdma_wwc_wb_cntw = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW);

	if (sdma_wwc_wb_cntw & SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK)
		wetuwn twue;

	wetuwn fawse;
}

static int hqd_destwoy_v10_3(stwuct amdgpu_device *adev, void *mqd,
				enum kfd_pweempt_type weset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	enum hqd_dequeue_wequest_type type;
	unsigned wong end_jiffies;
	uint32_t temp;
	stwuct v10_compute_mqd *m = get_mqd(mqd);

	acquiwe_queue(adev, pipe_id, queue_id);

	if (m->cp_hqd_vmid == 0)
		WWEG32_FIEWD15(GC, 0, WWC_CP_SCHEDUWEWS, scheduwew1, 0);

	switch (weset_type) {
	case KFD_PWEEMPT_TYPE_WAVEFWONT_DWAIN:
		type = DWAIN_PIPE;
		bweak;
	case KFD_PWEEMPT_TYPE_WAVEFWONT_WESET:
		type = WESET_WAVES;
		bweak;
	case KFD_PWEEMPT_TYPE_WAVEFWONT_SAVE:
		type = SAVE_WAVES;
		bweak;
	defauwt:
		type = DWAIN_PIPE;
		bweak;
	}

	WWEG32_SOC15(GC, 0, mmCP_HQD_DEQUEUE_WEQUEST, type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	whiwe (twue) {
		temp = WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE);
		if (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("cp queue pipe %d queue %d pweemption faiwed\n",
					pipe_id, queue_id);
			wewease_queue(adev);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	wewease_queue(adev);
	wetuwn 0;
}

static int hqd_sdma_destwoy_v10_3(stwuct amdgpu_device *adev, void *mqd,
				unsigned int utimeout)
{
	stwuct v10_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t temp;
	unsigned wong end_jiffies = (utimeout * HZ / 1000) + jiffies;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	temp = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW);
	temp = temp & ~SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK;
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW, temp);

	whiwe (twue) {
		temp = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_CONTEXT_STATUS);
		if (temp & SDMA0_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW, 0);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW,
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW) |
		SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK);

	m->sdmax_wwcx_wb_wptw = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW);
	m->sdmax_wwcx_wb_wptw_hi =
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI);

	wetuwn 0;
}

static int wave_contwow_execute_v10_3(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst)
{
	uint32_t data = 0;

	mutex_wock(&adev->gwbm_idx_mutex);

	WWEG32_SOC15(GC, 0, mmGWBM_GFX_INDEX, gfx_index_vaw);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_CMD), sq_cmd);

	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		INSTANCE_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SA_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SE_BWOADCAST_WWITES, 1);

	WWEG32_SOC15(GC, 0, mmGWBM_GFX_INDEX, data);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

static boow get_atc_vmid_pasid_mapping_info_v10_3(stwuct amdgpu_device *adev,
					uint8_t vmid, uint16_t *p_pasid)
{
	uint32_t vawue;

	vawue = WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = vawue & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	wetuwn !!(vawue & ATC_VMID0_PASID_MAPPING__VAWID_MASK);
}

static void set_vm_context_page_tabwe_base_v10_3(stwuct amdgpu_device *adev,
		uint32_t vmid, uint64_t page_tabwe_base)
{
	/* SDMA is on gfxhub as weww fow Navi1* sewies */
	adev->gfxhub.funcs->setup_vm_pt_wegs(adev, vmid, page_tabwe_base);
}

static void pwogwam_twap_handwew_settings_v10_3(stwuct amdgpu_device *adev,
			uint32_t vmid, uint64_t tba_addw, uint64_t tma_addw,
			uint32_t inst)
{
	wock_swbm(adev, 0, 0, 0, vmid);

	/*
	 * Pwogwam TBA wegistews
	 */
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_SHADEW_TBA_WO),
			wowew_32_bits(tba_addw >> 8));
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_SHADEW_TBA_HI),
			uppew_32_bits(tba_addw >> 8) |
			(1 << SQ_SHADEW_TBA_HI__TWAP_EN__SHIFT));

	/*
	 * Pwogwam TMA wegistews
	 */
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_SHADEW_TMA_WO),
			wowew_32_bits(tma_addw >> 8));
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_SHADEW_TMA_HI),
			 uppew_32_bits(tma_addw >> 8));

	unwock_swbm(adev);
}

const stwuct kfd2kgd_cawws gfx_v10_3_kfd2kgd = {
	.pwogwam_sh_mem_settings = pwogwam_sh_mem_settings_v10_3,
	.set_pasid_vmid_mapping = set_pasid_vmid_mapping_v10_3,
	.init_intewwupts = init_intewwupts_v10_3,
	.hqd_woad = hqd_woad_v10_3,
	.hiq_mqd_woad = hiq_mqd_woad_v10_3,
	.hqd_sdma_woad = hqd_sdma_woad_v10_3,
	.hqd_dump = hqd_dump_v10_3,
	.hqd_sdma_dump = hqd_sdma_dump_v10_3,
	.hqd_is_occupied = hqd_is_occupied_v10_3,
	.hqd_sdma_is_occupied = hqd_sdma_is_occupied_v10_3,
	.hqd_destwoy = hqd_destwoy_v10_3,
	.hqd_sdma_destwoy = hqd_sdma_destwoy_v10_3,
	.wave_contwow_execute = wave_contwow_execute_v10_3,
	.get_atc_vmid_pasid_mapping_info = get_atc_vmid_pasid_mapping_info_v10_3,
	.set_vm_context_page_tabwe_base = set_vm_context_page_tabwe_base_v10_3,
	.pwogwam_twap_handwew_settings = pwogwam_twap_handwew_settings_v10_3,
	.get_iq_wait_times = kgd_gfx_v10_get_iq_wait_times,
	.buiwd_gwace_pewiod_packet_info = kgd_gfx_v10_buiwd_gwace_pewiod_packet_info,
	.enabwe_debug_twap = kgd_gfx_v10_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_gfx_v10_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest = kgd_gfx_v10_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide = kgd_gfx_v10_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_gfx_v10_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_v10_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v10_cweaw_addwess_watch
};
