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
 */

#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "gfx_v8_0.h"
#incwude "gca/gfx_8_0_sh_mask.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_enum.h"
#incwude "oss/oss_3_0_sh_mask.h"
#incwude "oss/oss_3_0_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"
#incwude "gmc/gmc_8_1_d.h"
#incwude "vi_stwucts.h"
#incwude "vid.h"

enum hqd_dequeue_wequest_type {
	NO_ACTION = 0,
	DWAIN_PIPE,
	WESET_WAVES
};

static void wock_swbm(stwuct amdgpu_device *adev, uint32_t mec, uint32_t pipe,
			uint32_t queue, uint32_t vmid)
{
	uint32_t vawue = PIPEID(pipe) | MEID(mec) | VMID(vmid) | QUEUEID(queue);

	mutex_wock(&adev->swbm_mutex);
	WWEG32(mmSWBM_GFX_CNTW, vawue);
}

static void unwock_swbm(stwuct amdgpu_device *adev)
{
	WWEG32(mmSWBM_GFX_CNTW, 0);
	mutex_unwock(&adev->swbm_mutex);
}

static void acquiwe_queue(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t queue_id)
{
	uint32_t mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	uint32_t pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	wock_swbm(adev, mec, pipe, queue_id, 0);
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

	WWEG32(mmSH_MEM_CONFIG, sh_mem_config);
	WWEG32(mmSH_MEM_APE1_BASE, sh_mem_ape1_base);
	WWEG32(mmSH_MEM_APE1_WIMIT, sh_mem_ape1_wimit);
	WWEG32(mmSH_MEM_BASES, sh_mem_bases);

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

	WWEG32(mmATC_VMID0_PASID_MAPPING + vmid, pasid_mapping);

	whiwe (!(WWEG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS) & (1U << vmid)))
		cpu_wewax();
	WWEG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS, 1U << vmid);

	/* Mapping vmid to pasid awso fow IH bwock */
	WWEG32(mmIH_VMID_0_WUT + vmid, pasid_mapping);

	wetuwn 0;
}

static int kgd_init_intewwupts(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t inst)
{
	uint32_t mec;
	uint32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

	wock_swbm(adev, mec, pipe, 0, 0);

	WWEG32(mmCPC_INT_CNTW, CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK |
			CP_INT_CNTW_WING0__OPCODE_EWWOW_INT_ENABWE_MASK);

	unwock_swbm(adev);

	wetuwn 0;
}

static inwine uint32_t get_sdma_wwc_weg_offset(stwuct vi_sdma_mqd *m)
{
	uint32_t wetvaw;

	wetvaw = m->sdma_engine_id * SDMA1_WEGISTEW_OFFSET +
		m->sdma_queue_id * KFD_VI_SDMA_QUEUE_OFFSET;

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n",
			m->sdma_engine_id, m->sdma_queue_id, wetvaw);

	wetuwn wetvaw;
}

static inwine stwuct vi_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct vi_mqd *)mqd;
}

static inwine stwuct vi_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct vi_sdma_mqd *)mqd;
}

static int kgd_hqd_woad(stwuct amdgpu_device *adev, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t __usew *wptw, uint32_t wptw_shift,
			uint32_t wptw_mask, stwuct mm_stwuct *mm, uint32_t inst)
{
	stwuct vi_mqd *m;
	uint32_t *mqd_hqd;
	uint32_t weg, wptw_vaw, data;
	boow vawid_wptw = fawse;

	m = get_mqd(mqd);

	acquiwe_queue(adev, pipe_id, queue_id);

	/* HIQ is set duwing dwivew init pewiod with vmid set to 0*/
	if (m->cp_hqd_vmid == 0) {
		uint32_t vawue, mec, pipe;

		mec = (pipe_id / adev->gfx.mec.num_pipe_pew_mec) + 1;
		pipe = (pipe_id % adev->gfx.mec.num_pipe_pew_mec);

		pw_debug("kfd: set HIQ, mec:%d, pipe:%d, queue:%d.\n",
			mec, pipe, queue_id);
		vawue = WWEG32(mmWWC_CP_SCHEDUWEWS);
		vawue = WEG_SET_FIEWD(vawue, WWC_CP_SCHEDUWEWS, scheduwew1,
			((mec << 5) | (pipe << 3) | queue_id | 0x80));
		WWEG32(mmWWC_CP_SCHEDUWEWS, vawue);
	}

	/* HQD wegistews extend fwom CP_MQD_BASE_ADDW to CP_HQD_EOP_WPTW_MEM. */
	mqd_hqd = &m->cp_mqd_base_addw_wo;

	fow (weg = mmCP_MQD_BASE_ADDW; weg <= mmCP_HQD_EOP_CONTWOW; weg++)
		WWEG32(weg, mqd_hqd[weg - mmCP_MQD_BASE_ADDW]);

	/* Tonga ewwata: EOP WPTW/WPTW shouwd be weft unmodified.
	 * This is safe since EOP WPTW==WPTW fow any inactive HQD
	 * on ASICs that do not suppowt context-save.
	 * EOP wwites/weads can stawt anywhewe in the wing.
	 */
	if (adev->asic_type != CHIP_TONGA) {
		WWEG32(mmCP_HQD_EOP_WPTW, m->cp_hqd_eop_wptw);
		WWEG32(mmCP_HQD_EOP_WPTW, m->cp_hqd_eop_wptw);
		WWEG32(mmCP_HQD_EOP_WPTW_MEM, m->cp_hqd_eop_wptw_mem);
	}

	fow (weg = mmCP_HQD_EOP_EVENTS; weg <= mmCP_HQD_EWWOW; weg++)
		WWEG32(weg, mqd_hqd[weg - mmCP_MQD_BASE_ADDW]);

	/* Copy usewspace wwite pointew vawue to wegistew.
	 * Activate doowbeww wogic to monitow subsequent changes.
	 */
	data = WEG_SET_FIEWD(m->cp_hqd_pq_doowbeww_contwow,
			     CP_HQD_PQ_DOOWBEWW_CONTWOW, DOOWBEWW_EN, 1);
	WWEG32(mmCP_HQD_PQ_DOOWBEWW_CONTWOW, data);

	/* wead_usew_ptw may take the mm->mmap_wock.
	 * wewease swbm_mutex to avoid ciwcuwaw dependency between
	 * swbm_mutex->mmap_wock->wesewvation_ww_cwass_mutex->swbm_mutex.
	 */
	wewease_queue(adev);
	vawid_wptw = wead_usew_wptw(mm, wptw, wptw_vaw);
	acquiwe_queue(adev, pipe_id, queue_id);
	if (vawid_wptw)
		WWEG32(mmCP_HQD_PQ_WPTW, (wptw_vaw << wptw_shift) & wptw_mask);

	data = WEG_SET_FIEWD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WWEG32(mmCP_HQD_ACTIVE, data);

	wewease_queue(adev);

	wetuwn 0;
}

static int kgd_hqd_dump(stwuct amdgpu_device *adev,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_wegs, uint32_t inst)
{
	uint32_t i = 0, weg;
#define HQD_N_WEGS (54+4)
#define DUMP_WEG(addw) do {				\
		if (WAWN_ON_ONCE(i >= HQD_N_WEGS))	\
			bweak;				\
		(*dump)[i][0] = (addw) << 2;		\
		(*dump)[i++][1] = WWEG32(addw);		\
	} whiwe (0)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	acquiwe_queue(adev, pipe_id, queue_id);

	DUMP_WEG(mmCOMPUTE_STATIC_THWEAD_MGMT_SE0);
	DUMP_WEG(mmCOMPUTE_STATIC_THWEAD_MGMT_SE1);
	DUMP_WEG(mmCOMPUTE_STATIC_THWEAD_MGMT_SE2);
	DUMP_WEG(mmCOMPUTE_STATIC_THWEAD_MGMT_SE3);

	fow (weg = mmCP_MQD_BASE_ADDW; weg <= mmCP_HQD_EOP_DONES; weg++)
		DUMP_WEG(weg);

	wewease_queue(adev);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

static int kgd_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm)
{
	stwuct vi_sdma_mqd *m;
	unsigned wong end_jiffies;
	uint32_t sdma_wwc_weg_offset;
	uint32_t data;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(m);
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

	data = WEG_SET_FIEWD(m->sdmax_wwcx_doowbeww, SDMA0_WWC0_DOOWBEWW,
			     ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW, data);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
				m->sdmax_wwcx_wb_wptw);

	if (wead_usew_wptw(mm, wptw, data))
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW, data);
	ewse
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
		       m->sdmax_wwcx_wb_wptw);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_VIWTUAW_ADDW,
				m->sdmax_wwcx_viwtuaw_addw);
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
	uint32_t sdma_offset = engine_id * SDMA1_WEGISTEW_OFFSET +
		queue_id * KFD_VI_SDMA_QUEUE_OFFSET;
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+4+2+3+7)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	fow (weg = mmSDMA0_WWC0_WB_CNTW; weg <= mmSDMA0_WWC0_DOOWBEWW; weg++)
		DUMP_WEG(sdma_offset + weg);
	fow (weg = mmSDMA0_WWC0_VIWTUAW_ADDW; weg <= mmSDMA0_WWC0_WATEWMAWK;
	     weg++)
		DUMP_WEG(sdma_offset + weg);
	fow (weg = mmSDMA0_WWC0_CSA_ADDW_WO; weg <= mmSDMA0_WWC0_CSA_ADDW_HI;
	     weg++)
		DUMP_WEG(sdma_offset + weg);
	fow (weg = mmSDMA0_WWC0_IB_SUB_WEMAIN; weg <= mmSDMA0_WWC0_DUMMY_WEG;
	     weg++)
		DUMP_WEG(sdma_offset + weg);
	fow (weg = mmSDMA0_WWC0_MIDCMD_DATA0; weg <= mmSDMA0_WWC0_MIDCMD_CNTW;
	     weg++)
		DUMP_WEG(sdma_offset + weg);

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
	act = WWEG32(mmCP_HQD_ACTIVE);
	if (act) {
		wow = wowew_32_bits(queue_addwess >> 8);
		high = uppew_32_bits(queue_addwess >> 8);

		if (wow == WWEG32(mmCP_HQD_PQ_BASE) &&
				high == WWEG32(mmCP_HQD_PQ_BASE_HI))
			wetvaw = twue;
	}
	wewease_queue(adev);
	wetuwn wetvaw;
}

static boow kgd_hqd_sdma_is_occupied(stwuct amdgpu_device *adev, void *mqd)
{
	stwuct vi_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t sdma_wwc_wb_cntw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(m);

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
	uint32_t temp;
	enum hqd_dequeue_wequest_type type;
	unsigned wong fwags, end_jiffies;
	int wetwy;
	stwuct vi_mqd *m = get_mqd(mqd);

	if (amdgpu_in_weset(adev))
		wetuwn -EIO;

	acquiwe_queue(adev, pipe_id, queue_id);

	if (m->cp_hqd_vmid == 0)
		WWEG32_FIEWD(WWC_CP_SCHEDUWEWS, scheduwew1, 0);

	switch (weset_type) {
	case KFD_PWEEMPT_TYPE_WAVEFWONT_DWAIN:
		type = DWAIN_PIPE;
		bweak;
	case KFD_PWEEMPT_TYPE_WAVEFWONT_WESET:
		type = WESET_WAVES;
		bweak;
	defauwt:
		type = DWAIN_PIPE;
		bweak;
	}

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

	WWEG32(mmCP_HQD_DEQUEUE_WEQUEST, type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	whiwe (twue) {
		temp = WWEG32(mmCP_HQD_ACTIVE);
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
	stwuct vi_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t temp;
	unsigned wong end_jiffies = (utimeout * HZ / 1000) + jiffies;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(m);

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

	wetuwn 0;
}

static boow get_atc_vmid_pasid_mapping_info(stwuct amdgpu_device *adev,
					uint8_t vmid, uint16_t *p_pasid)
{
	uint32_t vawue;

	vawue = WWEG32(mmATC_VMID0_PASID_MAPPING + vmid);
	*p_pasid = vawue & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	wetuwn !!(vawue & ATC_VMID0_PASID_MAPPING__VAWID_MASK);
}

static int kgd_wave_contwow_execute(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst)
{
	uint32_t data = 0;

	mutex_wock(&adev->gwbm_idx_mutex);

	WWEG32(mmGWBM_GFX_INDEX, gfx_index_vaw);
	WWEG32(mmSQ_CMD, sq_cmd);

	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		INSTANCE_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SH_BWOADCAST_WWITES, 1);
	data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX,
		SE_BWOADCAST_WWITES, 1);

	WWEG32(mmGWBM_GFX_INDEX, data);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

static void set_scwatch_backing_va(stwuct amdgpu_device *adev,
					uint64_t va, uint32_t vmid)
{
	wock_swbm(adev, 0, 0, 0, vmid);
	WWEG32(mmSH_HIDDEN_PWIVATE_BASE_VMID, va);
	unwock_swbm(adev);
}

static void set_vm_context_page_tabwe_base(stwuct amdgpu_device *adev,
		uint32_t vmid, uint64_t page_tabwe_base)
{
	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pw_eww("twying to set page tabwe base fow wwong VMID\n");
		wetuwn;
	}
	WWEG32(mmVM_CONTEXT8_PAGE_TABWE_BASE_ADDW + vmid - 8,
			wowew_32_bits(page_tabwe_base));
}

const stwuct kfd2kgd_cawws gfx_v8_kfd2kgd = {
	.pwogwam_sh_mem_settings = kgd_pwogwam_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_set_pasid_vmid_mapping,
	.init_intewwupts = kgd_init_intewwupts,
	.hqd_woad = kgd_hqd_woad,
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
	.set_scwatch_backing_va = set_scwatch_backing_va,
	.set_vm_context_page_tabwe_base = set_vm_context_page_tabwe_base,
};
