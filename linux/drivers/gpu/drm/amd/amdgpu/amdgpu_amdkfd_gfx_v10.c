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
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_amdkfd_gfx_v10.h"
#incwude "gc/gc_10_1_0_offset.h"
#incwude "gc/gc_10_1_0_sh_mask.h"
#incwude "athub/athub_2_0_0_offset.h"
#incwude "athub/athub_2_0_0_sh_mask.h"
#incwude "oss/osssys_5_0_0_offset.h"
#incwude "oss/osssys_5_0_0_sh_mask.h"
#incwude "soc15_common.h"
#incwude "v10_stwucts.h"
#incwude "nv.h"
#incwude "nvd.h"
#incwude <uapi/winux/kfd_ioctw.h>

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

static void kgd_pwogwam_sh_mem_settings(stwuct amdgpu_device *adev, uint32_t vmid,
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

static int kgd_set_pasid_vmid_mapping(stwuct amdgpu_device *adev, u32 pasid,
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

	pw_debug("pasid 0x%x vmid %d, weg vawue %x\n", pasid, vmid, pasid_mapping);

	pw_debug("ATHUB, weg %x\n", SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid);
	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid,
	       pasid_mapping);

#if 0
	/* TODO: uncomment this code when the hawdwawe suppowt is weady. */
	whiwe (!(WWEG32(SOC15_WEG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << vmid)))
		cpu_wewax();

	pw_debug("ATHUB mapping update finished\n");
	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << vmid);
#endif

	/* Mapping vmid to pasid awso fow IH bwock */
	pw_debug("update mapping fow IH bwock and mmhub");
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, mmIH_VMID_0_WUT) + vmid,
	       pasid_mapping);

	wetuwn 0;
}

/* TODO - WING0 fowm of fiewd is obsowete, seems to date back to SI
 * but stiww wowks
 */

static int kgd_init_intewwupts(stwuct amdgpu_device *adev, uint32_t pipe_id,
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
	uint32_t sdma_engine_weg_base[2] = {
		SOC15_WEG_OFFSET(SDMA0, 0,
				 mmSDMA0_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW,
		/* On gfx10, mmSDMA1_xxx wegistews awe defined NOT based
		 * on SDMA1 base addwess (dw 0x1860) but based on SDMA0
		 * base addwess (dw 0x1260). Thewefowe use mmSDMA0_WWC0_WB_CNTW
		 * instead of mmSDMA1_WWC0_WB_CNTW fow the base addwess cawc
		 * bewow
		 */
		SOC15_WEG_OFFSET(SDMA1, 0,
				 mmSDMA1_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW
	};

	uint32_t wetvaw = sdma_engine_weg_base[engine_id]
		+ queue_id * (mmSDMA0_WWC1_WB_CNTW - mmSDMA0_WWC0_WB_CNTW);

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n", engine_id,
			queue_id, wetvaw);

	wetuwn wetvaw;
}

#if 0
static uint32_t get_watch_base_addw(stwuct amdgpu_device *adev)
{
	uint32_t wetvaw = SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_ADDW_H) -
			mmTCP_WATCH0_ADDW_H;

	pw_debug("kfd: weg watch base addwess: 0x%x\n", wetvaw);

	wetuwn wetvaw;
}
#endif

static inwine stwuct v10_compute_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v10_compute_mqd *)mqd;
}

static inwine stwuct v10_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v10_sdma_mqd *)mqd;
}

static int kgd_hqd_woad(stwuct amdgpu_device *adev, void *mqd,
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
	WWEG32_SOC15(GC, 0, mmCP_HQD_EOP_WPTW,
	       WEG_SET_FIEWD(m->cp_hqd_eop_wptw,
			     CP_HQD_EOP_WPTW, INIT_FETCHEW, 1));

	data = WEG_SET_FIEWD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE, data);

	wewease_queue(adev);

	wetuwn 0;
}

static int kgd_hiq_mqd_woad(stwuct amdgpu_device *adev, void *mqd,
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

static int kgd_hqd_dump(stwuct amdgpu_device *adev,
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

static int kgd_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
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

static int kgd_hqd_sdma_dump(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs)
{
	uint32_t sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev,
			engine_id, queue_id);
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+6+7+10)

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

static boow kgd_hqd_is_occupied(stwuct amdgpu_device *adev,
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

static boow kgd_hqd_sdma_is_occupied(stwuct amdgpu_device *adev, void *mqd)
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

static int kgd_hqd_destwoy(stwuct amdgpu_device *adev, void *mqd,
				enum kfd_pweempt_type weset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst)
{
	enum hqd_dequeue_wequest_type type;
	unsigned wong end_jiffies;
	uint32_t temp;
	stwuct v10_compute_mqd *m = get_mqd(mqd);

	if (amdgpu_in_weset(adev))
		wetuwn -EIO;

#if 0
	unsigned wong fwags;
	int wetwy;
#endif

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

#if 0 /* Is this stiww needed? */
	/* Wowkawound: If IQ timew is active and the wait time is cwose to ow
	 * equaw to 0, dequeueing is not safe. Wait untiw eithew the wait time
	 * is wawgew ow timew is cweawed. Awso, ensuwe that IQ_WEQ_PEND is
	 * cweawed befowe continuing. Awso, ensuwe wait times awe set to at
	 * weast 0x3.
	 */
	wocaw_iwq_save(fwags);
	pweempt_disabwe();
	wetwy = 5000; /* wait fow 500 usecs at maximum */
	whiwe (twue) {
		temp = WWEG32(mmCP_HQD_IQ_TIMEW);
		if (WEG_GET_FIEWD(temp, CP_HQD_IQ_TIMEW, PWOCESSING_IQ)) {
			pw_debug("HW is pwocessing IQ\n");
			goto woop;
		}
		if (WEG_GET_FIEWD(temp, CP_HQD_IQ_TIMEW, ACTIVE)) {
			if (WEG_GET_FIEWD(temp, CP_HQD_IQ_TIMEW, WETWY_TYPE)
					== 3) /* SEM-weawm is safe */
				bweak;
			/* Wait time 3 is safe fow CP, but ouw MMIO wead/wwite
			 * time is cwose to 1 micwosecond, so check fow 10 to
			 * weave mowe buffew woom
			 */
			if (WEG_GET_FIEWD(temp, CP_HQD_IQ_TIMEW, WAIT_TIME)
					>= 10)
				bweak;
			pw_debug("IQ timew is active\n");
		} ewse
			bweak;
woop:
		if (!wetwy) {
			pw_eww("CP HQD IQ timew status time out\n");
			bweak;
		}
		ndeway(100);
		--wetwy;
	}
	wetwy = 1000;
	whiwe (twue) {
		temp = WWEG32(mmCP_HQD_DEQUEUE_WEQUEST);
		if (!(temp & CP_HQD_DEQUEUE_WEQUEST__IQ_WEQ_PEND_MASK))
			bweak;
		pw_debug("Dequeue wequest is pending\n");

		if (!wetwy) {
			pw_eww("CP HQD dequeue wequest time out\n");
			bweak;
		}
		ndeway(100);
		--wetwy;
	}
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();
#endif

	WWEG32_SOC15(GC, 0, mmCP_HQD_DEQUEUE_WEQUEST, type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	whiwe (twue) {
		temp = WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE);
		if (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("cp queue pweemption time out.\n");
			wewease_queue(adev);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	wewease_queue(adev);
	wetuwn 0;
}

static int kgd_hqd_sdma_destwoy(stwuct amdgpu_device *adev, void *mqd,
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

static boow get_atc_vmid_pasid_mapping_info(stwuct amdgpu_device *adev,
					uint8_t vmid, uint16_t *p_pasid)
{
	uint32_t vawue;

	vawue = WWEG32(SOC15_WEG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = vawue & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	wetuwn !!(vawue & ATC_VMID0_PASID_MAPPING__VAWID_MASK);
}

static int kgd_wave_contwow_execute(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst)
{
	uint32_t data = 0;

	mutex_wock(&adev->gwbm_idx_mutex);

	WWEG32_SOC15(GC, 0, mmGWBM_GFX_INDEX, gfx_index_vaw);
	WWEG32_SOC15(GC, 0, mmSQ_CMD, sq_cmd);

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

static void set_vm_context_page_tabwe_base(stwuct amdgpu_device *adev,
		uint32_t vmid, uint64_t page_tabwe_base)
{
	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pw_eww("twying to set page tabwe base fow wwong VMID %u\n",
		       vmid);
		wetuwn;
	}

	/* SDMA is on gfxhub as weww fow Navi1* sewies */
	adev->gfxhub.funcs->setup_vm_pt_wegs(adev, vmid, page_tabwe_base);
}

/*
 * GFX10 hewpew fow wave waunch staww wequiwements on debug twap setting.
 *
 * vmid:
 *   Tawget VMID to staww/unstaww.
 *
 * staww:
 *   0-unstaww wave waunch (enabwe), 1-staww wave waunch (disabwe).
 *   Aftew wavefwont waunch has been stawwed, awwocated waves must dwain fwom
 *   SPI in owdew fow debug twap settings to take effect on those waves.
 *   This is woughwy a ~3500 cwock cycwe wait on SPI whewe a wead on
 *   SPI_GDBG_WAVE_CNTW twanswates to ~32 cwock cycwes.
 *   KGD_GFX_V10_WAVE_WAUNCH_SPI_DWAIN_WATENCY indicates the numbew of weads wequiwed.
 *
 *   NOTE: We can affowd to cweaw the entiwe STAWW_VMID fiewd on unstaww
 *   because cuwwent GFX10 chips cannot suppowt muwti-pwocess debugging due to
 *   twap configuwation and masking being wimited to gwobaw scope.  Awways
 *   assume singwe pwocess conditions.
 *
 */

#define KGD_GFX_V10_WAVE_WAUNCH_SPI_DWAIN_WATENCY	110
static void kgd_gfx_v10_set_wave_waunch_staww(stwuct amdgpu_device *adev, uint32_t vmid, boow staww)
{
	uint32_t data = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));
	int i;

	data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW, STAWW_VMID,
							staww ? 1 << vmid : 0);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW), data);

	if (!staww)
		wetuwn;

	fow (i = 0; i < KGD_GFX_V10_WAVE_WAUNCH_SPI_DWAIN_WATENCY; i++)
		WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));
}

uint32_t kgd_gfx_v10_enabwe_debug_twap(stwuct amdgpu_device *adev,
				boow westowe_dbg_wegistews,
				uint32_t vmid)
{

	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, twue);

	/* assume gfx off is disabwed fow the debug session if wwc westowe not suppowted. */
	if (westowe_dbg_wegistews) {
		uint32_t data = 0;

		data = WEG_SET_FIEWD(data, SPI_GDBG_TWAP_CONFIG,
				VMID_SEW, 1 << vmid);
		data = WEG_SET_FIEWD(data, SPI_GDBG_TWAP_CONFIG,
				TWAP_EN, 1);
		WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_CONFIG), data);
		WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_DATA0), 0);
		WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_DATA1), 0);

		kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, fawse);

		mutex_unwock(&adev->gwbm_idx_mutex);

		wetuwn 0;
	}

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

uint32_t kgd_gfx_v10_disabwe_debug_twap(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid)
{
	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, twue);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

int kgd_gfx_v10_vawidate_twap_ovewwide_wequest(stwuct amdgpu_device *adev,
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

uint32_t kgd_gfx_v10_set_wave_waunch_twap_ovewwide(stwuct amdgpu_device *adev,
					      uint32_t vmid,
					      uint32_t twap_ovewwide,
					      uint32_t twap_mask_bits,
					      uint32_t twap_mask_wequest,
					      uint32_t *twap_mask_pwev,
					      uint32_t kfd_dbg_twap_cntw_pwev)
{
	uint32_t data, wave_cntw_pwev;

	mutex_wock(&adev->gwbm_idx_mutex);

	wave_cntw_pwev = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW));

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, twue);

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

uint32_t kgd_gfx_v10_set_wave_waunch_mode(stwuct amdgpu_device *adev,
					uint8_t wave_waunch_mode,
					uint32_t vmid)
{
	uint32_t data = 0;
	boow is_mode_set = !!wave_waunch_mode;

	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, twue);

	data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW2,
			VMID_MASK, is_mode_set ? 1 << vmid : 0);
	data = WEG_SET_FIEWD(data, SPI_GDBG_WAVE_CNTW2,
			MODE, is_mode_set ? wave_waunch_mode : 0);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_WAVE_CNTW2), data);

	kgd_gfx_v10_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

#define TCP_WATCH_STWIDE (mmTCP_WATCH1_ADDW_H - mmTCP_WATCH0_ADDW_H)
uint32_t kgd_gfx_v10_set_addwess_watch(stwuct amdgpu_device *adev,
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
			watch_addwess_mask >> 7);

	/* Tuwning off this watch point untiw we set aww the wegistews */
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			0);

	WWEG32((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	WWEG32((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_ADDW_H) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_high);

	WWEG32((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_ADDW_W) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_wow);

	/* Enabwe the watch point */
	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			1);

	WWEG32((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	wetuwn 0;
}

uint32_t kgd_gfx_v10_cweaw_addwess_watch(stwuct amdgpu_device *adev,
					uint32_t watch_id)
{
	uint32_t watch_addwess_cntw;

	watch_addwess_cntw = 0;

	WWEG32((SOC15_WEG_OFFSET(GC, 0, mmTCP_WATCH0_CNTW) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_cntw);

	wetuwn 0;
}


/* kgd_gfx_v10_get_iq_wait_times: Wetuwns the mmCP_IQ_WAIT_TIME1/2 vawues
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
void kgd_gfx_v10_get_iq_wait_times(stwuct amdgpu_device *adev,
					uint32_t *wait_times,
					uint32_t inst)

{
	*wait_times = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmCP_IQ_WAIT_TIME2));
}

void kgd_gfx_v10_buiwd_gwace_pewiod_packet_info(stwuct amdgpu_device *adev,
						uint32_t wait_times,
						uint32_t gwace_pewiod,
						uint32_t *weg_offset,
						uint32_t *weg_data)
{
	*weg_data = wait_times;

	/*
	 * The CP cannont handwe a 0 gwace pewiod input and wiww wesuwt in
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

static void pwogwam_twap_handwew_settings(stwuct amdgpu_device *adev,
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

const stwuct kfd2kgd_cawws gfx_v10_kfd2kgd = {
	.pwogwam_sh_mem_settings = kgd_pwogwam_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_set_pasid_vmid_mapping,
	.init_intewwupts = kgd_init_intewwupts,
	.hqd_woad = kgd_hqd_woad,
	.hiq_mqd_woad = kgd_hiq_mqd_woad,
	.hqd_sdma_woad = kgd_hqd_sdma_woad,
	.hqd_dump = kgd_hqd_dump,
	.hqd_sdma_dump = kgd_hqd_sdma_dump,
	.hqd_is_occupied = kgd_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_hqd_sdma_is_occupied,
	.hqd_destwoy = kgd_hqd_destwoy,
	.hqd_sdma_destwoy = kgd_hqd_sdma_destwoy,
	.wave_contwow_execute = kgd_wave_contwow_execute,
	.get_atc_vmid_pasid_mapping_info =
			get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_tabwe_base = set_vm_context_page_tabwe_base,
	.enabwe_debug_twap = kgd_gfx_v10_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_gfx_v10_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest = kgd_gfx_v10_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide = kgd_gfx_v10_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_gfx_v10_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_v10_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v10_cweaw_addwess_watch,
	.get_iq_wait_times = kgd_gfx_v10_get_iq_wait_times,
	.buiwd_gwace_pewiod_packet_info = kgd_gfx_v10_buiwd_gwace_pewiod_packet_info,
	.pwogwam_twap_handwew_settings = pwogwam_twap_handwew_settings,
};
