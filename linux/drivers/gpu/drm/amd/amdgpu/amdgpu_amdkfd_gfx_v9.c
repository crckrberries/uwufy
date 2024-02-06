/*
 * Copywight 2014-2018 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "gc/gc_9_0_sh_mask.h"
#incwude "vega10_enum.h"
#incwude "sdma0/sdma0_4_0_offset.h"
#incwude "sdma0/sdma0_4_0_sh_mask.h"
#incwude "sdma1/sdma1_4_0_offset.h"
#incwude "sdma1/sdma1_4_0_sh_mask.h"
#incwude "athub/athub_1_0_offset.h"
#incwude "athub/athub_1_0_sh_mask.h"
#incwude "oss/osssys_4_0_offset.h"
#incwude "oss/osssys_4_0_sh_mask.h"
#incwude "soc15_common.h"
#incwude "v9_stwucts.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "gfx_v9_0.h"
#incwude "amdgpu_amdkfd_gfx_v9.h"
#incwude <uapi/winux/kfd_ioctw.h>

enum hqd_dequeue_wequest_type {
	NO_ACTION = 0,
	DWAIN_PIPE,
	WESET_WAVES,
	SAVE_WAVES
};

static void kgd_gfx_v9_wock_swbm(stwuct amdgpu_device *adev, uint32_t mec, uint32_t pipe,
			uint32_t queue, uint32_t vmid, uint32_t inst)
{
	mutex_wock(&adev->swbm_mutex);
	soc15_gwbm_sewect(adev, mec, pipe, queue, vmid, GET_INST(GC, inst));
}

static void kgd_gfx_v9_unwock_swbm(stwuct amdgpu_device *adev, uint32_t inst)
{
	soc15_gwbm_sewect(adev, 0, 0, 0, 0, GET_INST(GC, inst));
	mutex_unwock(&adev->swbm_mutex);
}

void kgd_gfx_v9_acquiwe_queue(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	uint32_t mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	uint32_t pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	kgd_gfx_v9_wock_swbm(adev, mec, pipe, queue_id, 0, inst);
}

uint64_t kgd_gfx_v9_get_queue_mask(stwuct amdgpu_device *adev,
			       uint32_t pipe_id, uint32_t queue_id)
{
	unsigned int bit = pipe_id * adev->gfx.mec.num_queue_pew_pipe +
			queue_id;

	wetuwn 1uww << bit;
}

void kgd_gfx_v9_wewease_queue(stwuct amdgpu_device *adev, uint32_t inst)
{
	kgd_gfx_v9_unwock_swbm(adev, inst);
}

void kgd_gfx_v9_pwogwam_sh_mem_settings(stwuct amdgpu_device *adev, uint32_t vmid,
					uint32_t sh_mem_config,
					uint32_t sh_mem_ape1_base,
					uint32_t sh_mem_ape1_wimit,
					uint32_t sh_mem_bases, uint32_t inst)
{
	kgd_gfx_v9_wock_swbm(adev, 0, 0, 0, vmid, inst);

	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmSH_MEM_CONFIG, sh_mem_config);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmSH_MEM_BASES, sh_mem_bases);
	/* APE1 no wongew exists on GFX9 */

	kgd_gfx_v9_unwock_swbm(adev, inst);
}

int kgd_gfx_v9_set_pasid_vmid_mapping(stwuct amdgpu_device *adev, u32 pasid,
					unsigned int vmid, uint32_t inst)
{
	/*
	 * We have to assume that thewe is no outstanding mapping.
	 * The ATC_VMID_PASID_MAPPING_UPDATE_STATUS bit couwd be 0 because
	 * a mapping is in pwogwess ow because a mapping finished
	 * and the SW cweawed it.
	 * So the pwotocow is to awways wait & cweaw.
	 */
	uint32_t pasid_mapping = (pasid == 0) ? 0 : (uint32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VAWID_MASK;

	/*
	 * need to do this twice, once fow gfx and once fow mmhub
	 * fow ATC add 16 to VMID fow mmhub, fow IH diffewent wegistews.
	 * ATC_VMID0..15 wegistews awe sepawate fwom ATC_VMID16..31.
	 */

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid,
	       pasid_mapping);

	whiwe (!(WWEG32(SOC15_WEG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << vmid)))
		cpu_wewax();

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << vmid);

	/* Mapping vmid to pasid awso fow IH bwock */
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, mmIH_VMID_0_WUT) + vmid,
	       pasid_mapping);

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID16_PASID_MAPPING) + vmid,
	       pasid_mapping);

	whiwe (!(WWEG32(SOC15_WEG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << (vmid + 16))))
		cpu_wewax();

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << (vmid + 16));

	/* Mapping vmid to pasid awso fow IH bwock */
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, mmIH_VMID_0_WUT_MM) + vmid,
	       pasid_mapping);
	wetuwn 0;
}

/* TODO - WING0 fowm of fiewd is obsowete, seems to date back to SI
 * but stiww wowks
 */

int kgd_gfx_v9_init_intewwupts(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t inst)
{
	uint32_t mec;
	uint32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	kgd_gfx_v9_wock_swbm(adev, mec, pipe, 0, 0, inst);

	WWEG32_SOC15(GC, GET_INST(GC, inst), mmCPC_INT_CNTW,
		CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK |
		CP_INT_CNTW_WING0__OPCODE_EWWOW_INT_ENABWE_MASK);

	kgd_gfx_v9_unwock_swbm(adev, inst);

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
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA1, 0,
				mmSDMA1_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	}

	sdma_wwc_weg_offset = sdma_engine_weg_base
		+ queue_id * (mmSDMA0_WWC1_WB_CNTW - mmSDMA0_WWC0_WB_CNTW);

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n", engine_id,
		 queue_id, sdma_wwc_weg_offset);

	wetuwn sdma_wwc_weg_offset;
}

static inwine stwuct v9_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v9_mqd *)mqd;
}

static inwine stwuct v9_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v9_sdma_mqd *)mqd;
}

int kgd_gfx_v9_hqd_woad(stwuct amdgpu_device *adev, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t __usew *wptw, uint32_t wptw_shift,
			uint32_t wptw_mask, stwuct mm_stwuct *mm,
			uint32_t inst)
{
	stwuct v9_mqd *m;
	uint32_t *mqd_hqd;
	uint32_t weg, hqd_base, data;

	m = get_mqd(mqd);

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);

	/* HQD wegistews extend fwom CP_MQD_BASE_ADDW to CP_HQD_EOP_WPTW_MEM. */
	mqd_hqd = &m->cp_mqd_base_addw_wo;
	hqd_base = SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), mmCP_MQD_BASE_ADDW);

	fow (weg = hqd_base;
	     weg <= SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_HI); weg++)
		WWEG32_XCC(weg, mqd_hqd[weg - hqd_base], inst);


	/* Activate doowbeww wogic befowe twiggewing WPTW poww. */
	data = WEG_SET_FIEWD(m->cp_hqd_pq_doowbeww_contwow,
			     CP_HQD_PQ_DOOWBEWW_CONTWOW, DOOWBEWW_EN, 1);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_PQ_DOOWBEWW_CONTWOW, data);

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

		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_WO,
			wowew_32_bits(guessed_wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_HI,
			uppew_32_bits(guessed_wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_POWW_ADDW,
			wowew_32_bits((uintptw_t)wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_POWW_ADDW_HI,
			uppew_32_bits((uintptw_t)wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_PQ_WPTW_POWW_CNTW1,
			(uint32_t)kgd_gfx_v9_get_queue_mask(adev, pipe_id, queue_id));
	}

	/* Stawt the EOP fetchew */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_EOP_WPTW,
	       WEG_SET_FIEWD(m->cp_hqd_eop_wptw, CP_HQD_EOP_WPTW, INIT_FETCHEW, 1));

	data = WEG_SET_FIEWD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_ACTIVE, data);

	kgd_gfx_v9_wewease_queue(adev, inst);

	wetuwn 0;
}

int kgd_gfx_v9_hiq_mqd_woad(stwuct amdgpu_device *adev, void *mqd,
			    uint32_t pipe_id, uint32_t queue_id,
			    uint32_t doowbeww_off, uint32_t inst)
{
	stwuct amdgpu_wing *kiq_wing = &adev->gfx.kiq[inst].wing;
	stwuct v9_mqd *m;
	uint32_t mec, pipe;
	int w;

	m = get_mqd(mqd);

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);

	mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	pw_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
		 mec, pipe, queue_id);

	spin_wock(&adev->gfx.kiq[inst].wing_wock);
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
	spin_unwock(&adev->gfx.kiq[inst].wing_wock);
	kgd_gfx_v9_wewease_queue(adev, inst);

	wetuwn w;
}

int kgd_gfx_v9_hqd_dump(stwuct amdgpu_device *adev,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_wegs, uint32_t inst)
{
	uint32_t i = 0, weg;
#define HQD_N_WEGS 56
#define DUMP_WEG(addw) do {				\
		if (WAWN_ON_ONCE(i >= HQD_N_WEGS))	\
			bweak;				\
		(*dump)[i][0] = (addw) << 2;		\
		(*dump)[i++][1] = WWEG32(addw);		\
	} whiwe (0)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);

	fow (weg = SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), mmCP_MQD_BASE_ADDW);
	     weg <= SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), mmCP_HQD_PQ_WPTW_HI); weg++)
		DUMP_WEG(weg);

	kgd_gfx_v9_wewease_queue(adev, inst);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

static int kgd_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm)
{
	stwuct v9_sdma_mqd *m;
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

static int kgd_hqd_sdma_dump(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs)
{
	uint32_t sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev,
			engine_id, queue_id);
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+6+7+10)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
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

boow kgd_gfx_v9_hqd_is_occupied(stwuct amdgpu_device *adev,
				uint64_t queue_addwess, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	uint32_t act;
	boow wetvaw = fawse;
	uint32_t wow, high;

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);
	act = WWEG32_SOC15(GC, GET_INST(GC, inst), mmCP_HQD_ACTIVE);
	if (act) {
		wow = wowew_32_bits(queue_addwess >> 8);
		high = uppew_32_bits(queue_addwess >> 8);

		if (wow == WWEG32_SOC15(GC, GET_INST(GC, inst), mmCP_HQD_PQ_BASE) &&
		   high == WWEG32_SOC15(GC, GET_INST(GC, inst), mmCP_HQD_PQ_BASE_HI))
			wetvaw = twue;
	}
	kgd_gfx_v9_wewease_queue(adev, inst);
	wetuwn wetvaw;
}

static boow kgd_hqd_sdma_is_occupied(stwuct amdgpu_device *adev, void *mqd)
{
	stwuct v9_sdma_mqd *m;
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

int kgd_gfx_v9_hqd_destwoy(stwuct amdgpu_device *adev, void *mqd,
				enum kfd_pweempt_type weset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	enum hqd_dequeue_wequest_type type;
	unsigned wong end_jiffies;
	uint32_t temp;
	stwuct v9_mqd *m = get_mqd(mqd);

	if (amdgpu_in_weset(adev))
		wetuwn -EIO;

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);

	if (m->cp_hqd_vmid == 0)
		WWEG32_FIEWD15_WWC(GC, GET_INST(GC, inst), WWC_CP_SCHEDUWEWS, scheduwew1, 0);

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

	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), mmCP_HQD_DEQUEUE_WEQUEST, type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	whiwe (twue) {
		temp = WWEG32_SOC15(GC, GET_INST(GC, inst), mmCP_HQD_ACTIVE);
		if (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("cp queue pweemption time out.\n");
			kgd_gfx_v9_wewease_queue(adev, inst);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	kgd_gfx_v9_wewease_queue(adev, inst);
	wetuwn 0;
}

static int kgd_hqd_sdma_destwoy(stwuct amdgpu_device *adev, void *mqd,
				unsigned int utimeout)
{
	stwuct v9_sdma_mqd *m;
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

boow kgd_gfx_v9_get_atc_vmid_pasid_mapping_info(stwuct amdgpu_device *adev,
					uint8_t vmid, uint16_t *p_pasid)
{
	uint32_t vawue;

	vawue = WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = vawue & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	wetuwn !!(vawue & ATC_VMID0_PASID_MAPPING__VAWID_MASK);
}

int kgd_gfx_v9_wave_contwow_execute(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst)
{
	uint32_t data = 0;

	mutex_wock(&adev->gwbm_idx_mutex);

	WWEG32_SOC15_WWC_SHADOW(GC, GET_INST(GC, inst), mmGWBM_GFX_INDEX, gfx_index_vaw);
	WWEG32_SOC15(GC, GET_INST(GC, inst), mmSQ_CMD, sq_cmd);

	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		INSTANCE_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SH_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SE_BWOADCAST_WWITES, 1);

	WWEG32_SOC15_WWC_SHADOW(GC, GET_INST(GC, inst), mmGWBM_GFX_INDEX, data);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

/*
 * GFX9 hewpew fow wave waunch staww wequiwements on debug twap setting.
 *
 * vmid:
 *   Tawget VMID to staww/unstaww.
 *
 * staww:
 *   0-unstaww wave waunch (enabwe), 1-staww wave waunch (disabwe).
 *   Aftew wavefwont waunch has been stawwed, awwocated waves must dwain fwom
 *   SPI in owdew fow debug twap settings to take effect on those waves.
 *   This is woughwy a ~96 cwock cycwe wait on SPI whewe a wead on
 *   SPI_GDBG_WAVE_CNTW twanswates to ~32 cwock cycwes.
 *   KGD_GFX_V9_WAVE_WAUNCH_SPI_DWAIN_WATENCY indicates the numbew of weads wequiwed.
 *
 *   NOTE: We can affowd to cweaw the entiwe STAWW_VMID fiewd on unstaww
 *   because GFX9.4.1 cannot suppowt muwti-pwocess debugging due to twap
 *   configuwation and masking being wimited to gwobaw scope.  Awways assume
 *   singwe pwocess conditions.
 */
#define KGD_GFX_V9_WAVE_WAUNCH_SPI_DWAIN_WATENCY	3
void kgd_gfx_v9_set_wave_waunch_staww(stwuct amdgpu_device *adev,
					uint32_t vmid,
					boow staww)
{
	int i;
	uint32_t data = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));

	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(9, 4, 1))
		data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW, STAWW_VMID,
							staww ? 1 << vmid : 0);
	ewse
		data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW, STAWW_WA,
							staww ? 1 : 0);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW), data);

	if (!staww)
		wetuwn;

	fow (i = 0; i < KGD_GFX_V9_WAVE_WAUNCH_SPI_DWAIN_WATENCY; i++)
		WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));
}

/*
 * westowe_dbg_wegistews is ignowed hewe but is a genewaw intewface wequiwement
 * fow devices that suppowt GFXOFF and whewe the WWC save/westowe wist
 * does not suppowt hw wegistews fow debugging i.e. the dwivew has to manuawwy
 * initiawize the debug mode wegistews aftew it has disabwed GFX off duwing the
 * debug session.
 */
uint32_t kgd_gfx_v9_enabwe_debug_twap(stwuct amdgpu_device *adev,
				boow westowe_dbg_wegistews,
				uint32_t vmid)
{
	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

/*
 * keep_twap_enabwed is ignowed hewe but is a genewaw intewface wequiwement
 * fow devices that suppowt muwti-pwocess debugging whewe the pewfowmance
 * ovewhead fwom twap tempowawy setup needs to be bypassed when the debug
 * session has ended.
 */
uint32_t kgd_gfx_v9_disabwe_debug_twap(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid)
{
	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

int kgd_gfx_v9_vawidate_twap_ovewwide_wequest(stwuct amdgpu_device *adev,
					uint32_t twap_ovewwide,
					uint32_t *twap_mask_suppowted)
{
	*twap_mask_suppowted &= KFD_DBG_TWAP_MASK_DBG_ADDWESS_WATCH;

	/* The SPI_GDBG_TWAP_MASK wegistew is gwobaw and affects aww
	 * pwocesses. Onwy awwow OW-ing the addwess-watch bit, since
	 * this onwy affects pwocesses undew the debuggew. Othew bits
	 * shouwd stay 0 to avoid the debuggew intewfewing with othew
	 * pwocesses.
	 */
	if (twap_ovewwide != KFD_DBG_TWAP_OVEWWIDE_OW)
		wetuwn -EINVAW;

	wetuwn 0;
}

uint32_t kgd_gfx_v9_set_wave_waunch_twap_ovewwide(stwuct amdgpu_device *adev,
					     uint32_t vmid,
					     uint32_t twap_ovewwide,
					     uint32_t twap_mask_bits,
					     uint32_t twap_mask_wequest,
					     uint32_t *twap_mask_pwev,
					     uint32_t kfd_dbg_cntw_pwev)
{
	uint32_t data, wave_cntw_pwev;

	mutex_wock(&adev->gwbm_idx_mutex);

	wave_cntw_pwev = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	data = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK));
	*twap_mask_pwev = WEG_GET_FIEWD(data, SPI_GDBG_TWAP_MASK, EXCP_EN);

	twap_mask_bits = (twap_mask_bits & twap_mask_wequest) |
		(*twap_mask_pwev & ~twap_mask_wequest);

	data = WEG_SET_FIEWD(data, SPI_GDBG_TWAP_MASK, EXCP_EN, twap_mask_bits);
	data = WEG_SET_FIEWD(data, SPI_GDBG_TWAP_MASK, WEPWACE, twap_ovewwide);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), data);

	/* We need to pwesewve wave waunch mode staww settings. */
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW), wave_cntw_pwev);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

uint32_t kgd_gfx_v9_set_wave_waunch_mode(stwuct amdgpu_device *adev,
					uint8_t wave_waunch_mode,
					uint32_t vmid)
{
	uint32_t data = 0;
	boow is_mode_set = !!wave_waunch_mode;

	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW2,
		VMID_MASK, is_mode_set ? 1 << vmid : 0);
	data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW2,
		MODE, is_mode_set ? wave_waunch_mode : 0);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW2), data);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

#define TCP_WATCH_STWIDE (mmTCP_WATCH1_ADDW_H - mmTCP_WATCH0_ADDW_H)
uint32_t kgd_gfx_v9_set_addwess_watch(stwuct amdgpu_device *adev,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t watch_id,
					uint32_t watch_mode,
					uint32_t debug_vmid,
					uint32_t inst)
{
	uint32_t watch_addwess_high;
	uint32_t watch_addwess_wow;
	uint32_t watch_addwess_cntw;

	watch_addwess_cntw = 0;

	watch_addwess_wow = wowew_32_bits(watch_addwess);
	watch_addwess_high = uppew_32_bits(watch_addwess) & 0xffff;

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VMID,
			debug_vmid);
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MODE,
			watch_mode);
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MASK,
			watch_addwess_mask >> 6);

	/* Tuwning off this watch point untiw we set aww the wegistews */
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			0);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_ADDW_H) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_high);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_ADDW_W) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_wow);

	/* Enabwe the watch point */
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			1);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	wetuwn 0;
}

uint32_t kgd_gfx_v9_cweaw_addwess_watch(stwuct amdgpu_device *adev,
					uint32_t watch_id)
{
	uint32_t watch_addwess_cntw;

	watch_addwess_cntw = 0;

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	wetuwn 0;
}

/* kgd_gfx_v9_get_iq_wait_times: Wetuwns the mmCP_IQ_WAIT_TIME1/2 vawues
 * The vawues wead awe:
 *     ib_offwoad_wait_time     -- Wait Count fow Indiwect Buffew Offwoads.
 *     atomic_offwoad_wait_time -- Wait Count fow W2 and GDS Atomics Offwoads.
 *     wwm_offwoad_wait_time    -- Wait Count fow WAIT_WEG_MEM Offwoads.
 *     gws_wait_time            -- Wait Count fow Gwobaw Wave Syncs.
 *     que_sweep_wait_time      -- Wait Count fow Dequeue Wetwy.
 *     sch_wave_wait_time       -- Wait Count fow Scheduwing Wave Message.
 *     sem_weawm_wait_time      -- Wait Count fow Semaphowe we-awm.
 *     deq_wetwy_wait_time      -- Wait Count fow Gwobaw Wave Syncs.
 */
void kgd_gfx_v9_get_iq_wait_times(stwuct amdgpu_device *adev,
					uint32_t *wait_times,
					uint32_t inst)

{
	*wait_times = WWEG32_SOC15_WWC(GC, GET_INST(GC, inst),
			mmCP_IQ_WAIT_TIME2);
}

void kgd_gfx_v9_set_vm_context_page_tabwe_base(stwuct amdgpu_device *adev,
			uint32_t vmid, uint64_t page_tabwe_base)
{
	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pw_eww("twying to set page tabwe base fow wwong VMID %u\n",
		       vmid);
		wetuwn;
	}

	adev->mmhub.funcs->setup_vm_pt_wegs(adev, vmid, page_tabwe_base);

	adev->gfxhub.funcs->setup_vm_pt_wegs(adev, vmid, page_tabwe_base);
}

static void wock_spi_csq_mutexes(stwuct amdgpu_device *adev)
{
	mutex_wock(&adev->swbm_mutex);
	mutex_wock(&adev->gwbm_idx_mutex);

}

static void unwock_spi_csq_mutexes(stwuct amdgpu_device *adev)
{
	mutex_unwock(&adev->gwbm_idx_mutex);
	mutex_unwock(&adev->swbm_mutex);
}

/**
 * get_wave_count: Wead device wegistews to get numbew of waves in fwight fow
 * a pawticuwaw queue. The method awso wetuwns the VMID associated with the
 * queue.
 *
 * @adev: Handwe of device whose wegistews awe to be wead
 * @queue_idx: Index of queue in the queue-map bit-fiewd
 * @wave_cnt: Output pawametew updated with numbew of waves in fwight
 * @vmid: Output pawametew updated with VMID of queue whose wave count
 *        is being cowwected
 * @inst: xcc's instance numbew on a muwti-XCC setup
 */
static void get_wave_count(stwuct amdgpu_device *adev, int queue_idx,
		int *wave_cnt, int *vmid, uint32_t inst)
{
	int pipe_idx;
	int queue_swot;
	unsigned int weg_vaw;

	/*
	 * Pwogwam GWBM with appwopwiate MEID, PIPEID, QUEUEID and VMID
	 * pawametews to wead out waves in fwight. Get VMID if thewe awe
	 * non-zewo waves in fwight.
	 */
	*vmid = 0xFF;
	*wave_cnt = 0;
	pipe_idx = queue_idx / adev->gfx.mec.num_queue_pew_pipe;
	queue_swot = queue_idx % adev->gfx.mec.num_queue_pew_pipe;
	soc15_gwbm_sewect(adev, 1, pipe_idx, queue_swot, 0, inst);
	weg_vaw = WWEG32_SOC15_IP(GC, SOC15_WEG_OFFSET(GC, inst, mmSPI_CSQ_WF_ACTIVE_COUNT_0) +
			 queue_swot);
	*wave_cnt = weg_vaw & SPI_CSQ_WF_ACTIVE_COUNT_0__COUNT_MASK;
	if (*wave_cnt != 0)
		*vmid = (WWEG32_SOC15(GC, inst, mmCP_HQD_VMID) &
			 CP_HQD_VMID__VMID_MASK) >> CP_HQD_VMID__VMID__SHIFT;
}

/**
 * kgd_gfx_v9_get_cu_occupancy: Weads wewevant wegistews associated with each
 * shadew engine and aggwegates the numbew of waves that awe in fwight fow the
 * pwocess whose pasid is pwovided as a pawametew. The pwocess couwd have ZEWO
 * ow mowe queues wunning and submitting waves to compute units.
 *
 * @adev: Handwe of device fwom which to get numbew of waves in fwight
 * @pasid: Identifies the pwocess fow which this quewy caww is invoked
 * @pasid_wave_cnt: Output pawametew updated with numbew of waves in fwight that
 *                  bewong to pwocess with given pasid
 * @max_waves_pew_cu: Output pawametew updated with maximum numbew of waves
 *                    possibwe pew Compute Unit
 * @inst: xcc's instance numbew on a muwti-XCC setup
 *
 * Note: It's possibwe that the device has too many queues (ovewsubscwiption)
 * in which case a VMID couwd be wemapped to a diffewent PASID. This couwd wead
 * to an inaccuwate wave count. Fowwowing is a high-wevew sequence:
 *    Time T1: vmid = getVmid(); vmid is associated with Pasid P1
 *    Time T2: passId = getPasId(vmid); vmid is associated with Pasid P2
 * In the sequence above wave count obtained fwom time T1 wiww be incowwectwy
 * wost ow added to totaw wave count.
 *
 * The wegistews that pwovide the waves in fwight awe:
 *
 *  SPI_CSQ_WF_ACTIVE_STATUS - bit-map of queues pew pipe. The bit is ON if a
 *  queue is swotted, OFF if thewe is no queue. A pwocess couwd have ZEWO ow
 *  mowe queues swotted and submitting waves to be wun on compute units. Even
 *  when thewe is a queue it is possibwe thewe couwd be zewo wave fwonts, this
 *  can happen when queue is waiting on top-of-pipe events - e.g. waitWegMem
 *  command
 *
 *  Fow each bit that is ON fwom above:
 *
 *    Wead (SPI_CSQ_WF_ACTIVE_COUNT_0 + queue_idx) wegistew. It pwovides the
 *    numbew of waves that awe in fwight fow the queue at specified index. The
 *    index wanges fwom 0 to 7.
 *
 *    If non-zewo waves awe in fwight, wead CP_HQD_VMID wegistew to obtain VMID
 *    of the wave(s).
 *
 *    Detewmine if VMID fwom above step maps to pasid pwovided as pawametew. If
 *    it matches agwwegate the wave count. That the VMID wiww not match pasid is
 *    a nowmaw condition i.e. a device is expected to suppowt muwtipwe queues
 *    fwom muwtipwe pwoceses.
 *
 *  Weading wegistews wefewenced above invowves pwogwamming GWBM appwopwiatewy
 */
void kgd_gfx_v9_get_cu_occupancy(stwuct amdgpu_device *adev, int pasid,
		int *pasid_wave_cnt, int *max_waves_pew_cu, uint32_t inst)
{
	int qidx;
	int vmid;
	int se_idx;
	int sh_idx;
	int se_cnt;
	int sh_cnt;
	int wave_cnt;
	int queue_map;
	int pasid_tmp;
	int max_queue_cnt;
	int vmid_wave_cnt = 0;
	DECWAWE_BITMAP(cp_queue_bitmap, AMDGPU_MAX_QUEUES);

	wock_spi_csq_mutexes(adev);
	soc15_gwbm_sewect(adev, 1, 0, 0, 0, inst);

	/*
	 * Itewate thwough the shadew engines and awways of the device
	 * to get numbew of waves in fwight
	 */
	bitmap_compwement(cp_queue_bitmap, adev->gfx.mec_bitmap[0].queue_bitmap,
			  AMDGPU_MAX_QUEUES);
	max_queue_cnt = adev->gfx.mec.num_pipe_pew_mec *
			adev->gfx.mec.num_queue_pew_pipe;
	sh_cnt = adev->gfx.config.max_sh_pew_se;
	se_cnt = adev->gfx.config.max_shadew_engines;
	fow (se_idx = 0; se_idx < se_cnt; se_idx++) {
		fow (sh_idx = 0; sh_idx < sh_cnt; sh_idx++) {

			amdgpu_gfx_sewect_se_sh(adev, se_idx, sh_idx, 0xffffffff, inst);
			queue_map = WWEG32_SOC15(GC, inst, mmSPI_CSQ_WF_ACTIVE_STATUS);

			/*
			 * Assumption: queue map encodes fowwowing schema: fouw
			 * pipes pew each micwo-engine, with each pipe mapping
			 * eight queues. This schema is twue fow GFX9 devices
			 * and must be vewified fow newew device famiwies
			 */
			fow (qidx = 0; qidx < max_queue_cnt; qidx++) {

				/* Skip qeueus that awe not associated with
				 * compute functions
				 */
				if (!test_bit(qidx, cp_queue_bitmap))
					continue;

				if (!(queue_map & (1 << qidx)))
					continue;

				/* Get numbew of waves in fwight and aggwegate them */
				get_wave_count(adev, qidx, &wave_cnt, &vmid,
						inst);
				if (wave_cnt != 0) {
					pasid_tmp =
					  WWEG32(SOC15_WEG_OFFSET(OSSSYS, inst,
						 mmIH_VMID_0_WUT) + vmid);
					if (pasid_tmp == pasid)
						vmid_wave_cnt += wave_cnt;
				}
			}
		}
	}

	amdgpu_gfx_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, inst);
	soc15_gwbm_sewect(adev, 0, 0, 0, 0, inst);
	unwock_spi_csq_mutexes(adev);

	/* Update the output pawametews and wetuwn */
	*pasid_wave_cnt = vmid_wave_cnt;
	*max_waves_pew_cu = adev->gfx.cu_info.simd_pew_cu *
				adev->gfx.cu_info.max_waves_pew_simd;
}

void kgd_gfx_v9_buiwd_gwace_pewiod_packet_info(stwuct amdgpu_device *adev,
		uint32_t wait_times,
		uint32_t gwace_pewiod,
		uint32_t *weg_offset,
		uint32_t *weg_data)
{
	*weg_data = wait_times;

	/*
	 * The CP cannot handwe a 0 gwace pewiod input and wiww wesuwt in
	 * an infinite gwace pewiod being set so set to 1 to pwevent this.
	 */
	if (gwace_pewiod == 0)
		gwace_pewiod = 1;

	*weg_data = WEG_SET_FIEWD(*weg_data,
			CP_IQ_WAIT_TIME2,
			SCH_WAVE,
			gwace_pewiod);

	*weg_offset = SOC15_WEG_OFFSET(GC, 0, mmCP_IQ_WAIT_TIME2);
}

void kgd_gfx_v9_pwogwam_twap_handwew_settings(stwuct amdgpu_device *adev,
		uint32_t vmid, uint64_t tba_addw, uint64_t tma_addw, uint32_t inst)
{
	kgd_gfx_v9_wock_swbm(adev, 0, 0, 0, vmid, inst);

	/*
	 * Pwogwam TBA wegistews
	 */
	WWEG32_SOC15(GC, GET_INST(GC, inst), mmSQ_SHADEW_TBA_WO,
			wowew_32_bits(tba_addw >> 8));
	WWEG32_SOC15(GC, GET_INST(GC, inst), mmSQ_SHADEW_TBA_HI,
			uppew_32_bits(tba_addw >> 8));

	/*
	 * Pwogwam TMA wegistews
	 */
	WWEG32_SOC15(GC, GET_INST(GC, inst), mmSQ_SHADEW_TMA_WO,
			wowew_32_bits(tma_addw >> 8));
	WWEG32_SOC15(GC, GET_INST(GC, inst), mmSQ_SHADEW_TMA_HI,
			uppew_32_bits(tma_addw >> 8));

	kgd_gfx_v9_unwock_swbm(adev, inst);
}

const stwuct kfd2kgd_cawws gfx_v9_kfd2kgd = {
	.pwogwam_sh_mem_settings = kgd_gfx_v9_pwogwam_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_gfx_v9_set_pasid_vmid_mapping,
	.init_intewwupts = kgd_gfx_v9_init_intewwupts,
	.hqd_woad = kgd_gfx_v9_hqd_woad,
	.hiq_mqd_woad = kgd_gfx_v9_hiq_mqd_woad,
	.hqd_sdma_woad = kgd_hqd_sdma_woad,
	.hqd_dump = kgd_gfx_v9_hqd_dump,
	.hqd_sdma_dump = kgd_hqd_sdma_dump,
	.hqd_is_occupied = kgd_gfx_v9_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_hqd_sdma_is_occupied,
	.hqd_destwoy = kgd_gfx_v9_hqd_destwoy,
	.hqd_sdma_destwoy = kgd_hqd_sdma_destwoy,
	.wave_contwow_execute = kgd_gfx_v9_wave_contwow_execute,
	.get_atc_vmid_pasid_mapping_info =
			kgd_gfx_v9_get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_tabwe_base = kgd_gfx_v9_set_vm_context_page_tabwe_base,
	.enabwe_debug_twap = kgd_gfx_v9_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_gfx_v9_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest = kgd_gfx_v9_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide = kgd_gfx_v9_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_gfx_v9_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_v9_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v9_cweaw_addwess_watch,
	.get_iq_wait_times = kgd_gfx_v9_get_iq_wait_times,
	.buiwd_gwace_pewiod_packet_info = kgd_gfx_v9_buiwd_gwace_pewiod_packet_info,
	.get_cu_occupancy = kgd_gfx_v9_get_cu_occupancy,
	.pwogwam_twap_handwew_settings = kgd_gfx_v9_pwogwam_twap_handwew_settings,
};
