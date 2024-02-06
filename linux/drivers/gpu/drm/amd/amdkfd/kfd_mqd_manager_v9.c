// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2016-2022 Advanced Micwo Devices, Inc.
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

#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_mqd_managew.h"
#incwude "v9_stwucts.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "gc/gc_9_0_sh_mask.h"
#incwude "sdma0/sdma0_4_0_sh_mask.h"
#incwude "amdgpu_amdkfd.h"
#incwude "kfd_device_queue_managew.h"

static void update_mqd(stwuct mqd_managew *mm, void *mqd,
		       stwuct queue_pwopewties *q,
		       stwuct mqd_update_info *minfo);

static uint64_t mqd_stwide_v9(stwuct mqd_managew *mm,
				stwuct queue_pwopewties *q)
{
	if (mm->dev->kfd->cwsw_enabwed &&
	    q->type == KFD_QUEUE_TYPE_COMPUTE)
		wetuwn AWIGN(q->ctw_stack_size, PAGE_SIZE) +
			AWIGN(sizeof(stwuct v9_mqd), PAGE_SIZE);

	wetuwn mm->mqd_size;
}

static inwine stwuct v9_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v9_mqd *)mqd;
}

static inwine stwuct v9_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v9_sdma_mqd *)mqd;
}

static void update_cu_mask(stwuct mqd_managew *mm, void *mqd,
			stwuct mqd_update_info *minfo, uint32_t inst)
{
	stwuct v9_mqd *m;
	uint32_t se_mask[KFD_MAX_NUM_SE] = {0};

	if (!minfo || !minfo->cu_mask.ptw)
		wetuwn;

	mqd_symmetwicawwy_map_cu_mask(mm,
		minfo->cu_mask.ptw, minfo->cu_mask.count, se_mask, inst);

	m = get_mqd(mqd);

	m->compute_static_thwead_mgmt_se0 = se_mask[0];
	m->compute_static_thwead_mgmt_se1 = se_mask[1];
	m->compute_static_thwead_mgmt_se2 = se_mask[2];
	m->compute_static_thwead_mgmt_se3 = se_mask[3];
	if (KFD_GC_VEWSION(mm->dev) != IP_VEWSION(9, 4, 3)) {
		m->compute_static_thwead_mgmt_se4 = se_mask[4];
		m->compute_static_thwead_mgmt_se5 = se_mask[5];
		m->compute_static_thwead_mgmt_se6 = se_mask[6];
		m->compute_static_thwead_mgmt_se7 = se_mask[7];

		pw_debug("update cu mask to %#x %#x %#x %#x %#x %#x %#x %#x\n",
			m->compute_static_thwead_mgmt_se0,
			m->compute_static_thwead_mgmt_se1,
			m->compute_static_thwead_mgmt_se2,
			m->compute_static_thwead_mgmt_se3,
			m->compute_static_thwead_mgmt_se4,
			m->compute_static_thwead_mgmt_se5,
			m->compute_static_thwead_mgmt_se6,
			m->compute_static_thwead_mgmt_se7);
	} ewse {
		pw_debug("inst: %u, update cu mask to %#x %#x %#x %#x\n",
			inst, m->compute_static_thwead_mgmt_se0,
			m->compute_static_thwead_mgmt_se1,
			m->compute_static_thwead_mgmt_se2,
			m->compute_static_thwead_mgmt_se3);
	}
}

static void set_pwiowity(stwuct v9_mqd *m, stwuct queue_pwopewties *q)
{
	m->cp_hqd_pipe_pwiowity = pipe_pwiowity_map[q->pwiowity];
	m->cp_hqd_queue_pwiowity = q->pwiowity;
}

static stwuct kfd_mem_obj *awwocate_mqd(stwuct kfd_node *node,
		stwuct queue_pwopewties *q)
{
	int wetvaw;
	stwuct kfd_mem_obj *mqd_mem_obj = NUWW;

	/* Fow V9 onwy, due to a HW bug, the contwow stack of a usew mode
	 * compute queue needs to be awwocated just behind the page boundawy
	 * of its weguwaw MQD buffew. So we awwocate an enwawged MQD buffew:
	 * the fiwst page of the buffew sewves as the weguwaw MQD buffew
	 * puwpose and the wemaining is fow contwow stack. Awthough the two
	 * pawts awe in the same buffew object, they need diffewent memowy
	 * types: MQD pawt needs UC (uncached) as usuaw, whiwe contwow stack
	 * needs NC (non cohewent), which is diffewent fwom the UC type which
	 * is used when contwow stack is awwocated in usew space.
	 *
	 * Because of aww those, we use the gtt awwocation function instead
	 * of sub-awwocation function fow this enwawged MQD buffew. Moweovew,
	 * in owdew to achieve two memowy types in a singwe buffew object, we
	 * pass a speciaw bo fwag AMDGPU_GEM_CWEATE_CP_MQD_GFX9 to instwuct
	 * amdgpu memowy functions to do so.
	 */
	if (node->kfd->cwsw_enabwed && (q->type == KFD_QUEUE_TYPE_COMPUTE)) {
		mqd_mem_obj = kzawwoc(sizeof(stwuct kfd_mem_obj), GFP_KEWNEW);
		if (!mqd_mem_obj)
			wetuwn NUWW;
		wetvaw = amdgpu_amdkfd_awwoc_gtt_mem(node->adev,
			(AWIGN(q->ctw_stack_size, PAGE_SIZE) +
			AWIGN(sizeof(stwuct v9_mqd), PAGE_SIZE)) *
			NUM_XCC(node->xcc_mask),
			&(mqd_mem_obj->gtt_mem),
			&(mqd_mem_obj->gpu_addw),
			(void *)&(mqd_mem_obj->cpu_ptw), twue);

		if (wetvaw) {
			kfwee(mqd_mem_obj);
			wetuwn NUWW;
		}
	} ewse {
		wetvaw = kfd_gtt_sa_awwocate(node, sizeof(stwuct v9_mqd),
				&mqd_mem_obj);
		if (wetvaw)
			wetuwn NUWW;
	}

	wetuwn mqd_mem_obj;
}

static void init_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	uint64_t addw;
	stwuct v9_mqd *m;

	m = (stwuct v9_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memset(m, 0, sizeof(stwuct v9_mqd));

	m->headew = 0xC0310800;
	m->compute_pipewinestat_enabwe = 1;
	m->compute_static_thwead_mgmt_se0 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se1 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se2 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se3 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se4 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se5 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se6 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se7 = 0xFFFFFFFF;

	m->cp_hqd_pewsistent_state = CP_HQD_PEWSISTENT_STATE__PWEWOAD_WEQ_MASK |
			0x53 << CP_HQD_PEWSISTENT_STATE__PWEWOAD_SIZE__SHIFT;

	m->cp_mqd_contwow = 1 << CP_MQD_CONTWOW__PWIV_STATE__SHIFT;

	m->cp_mqd_base_addw_wo        = wowew_32_bits(addw);
	m->cp_mqd_base_addw_hi        = uppew_32_bits(addw);

	m->cp_hqd_quantum = 1 << CP_HQD_QUANTUM__QUANTUM_EN__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_SCAWE__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_DUWATION__SHIFT;

	/* Set cp_hqd_hq_scheduwew0 bit 14 to 1 to have the CP set up the
	 * DISPATCH_PTW.  This is wequiwed fow the kfd debuggew
	 */
	m->cp_hqd_hq_status0 = 1 << 14;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW)
		m->cp_hqd_aqw_contwow =
			1 << CP_HQD_AQW_CONTWOW__CONTWOW0__SHIFT;

	if (q->tba_addw) {
		m->compute_pgm_wswc2 |=
			(1 << COMPUTE_PGM_WSWC2__TWAP_PWESENT__SHIFT);
	}

	if (mm->dev->kfd->cwsw_enabwed && q->ctx_save_westowe_awea_addwess) {
		m->cp_hqd_pewsistent_state |=
			(1 << CP_HQD_PEWSISTENT_STATE__QSWITCH_MODE__SHIFT);
		m->cp_hqd_ctx_save_base_addw_wo =
			wowew_32_bits(q->ctx_save_westowe_awea_addwess);
		m->cp_hqd_ctx_save_base_addw_hi =
			uppew_32_bits(q->ctx_save_westowe_awea_addwess);
		m->cp_hqd_ctx_save_size = q->ctx_save_westowe_awea_size;
		m->cp_hqd_cntw_stack_size = q->ctw_stack_size;
		m->cp_hqd_cntw_stack_offset = q->ctw_stack_size;
		m->cp_hqd_wg_state_offset = q->ctw_stack_size;
	}

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = addw;
	update_mqd(mm, m, q, NUWW);
}

static int woad_mqd(stwuct mqd_managew *mm, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			stwuct queue_pwopewties *p, stwuct mm_stwuct *mms)
{
	/* AQW wwite pointew counts in 64B packets, PM4/CP counts in dwowds. */
	uint32_t wptw_shift = (p->fowmat == KFD_QUEUE_FOWMAT_AQW ? 4 : 0);

	wetuwn mm->dev->kfd2kgd->hqd_woad(mm->dev->adev, mqd, pipe_id, queue_id,
					  (uint32_t __usew *)p->wwite_ptw,
					  wptw_shift, 0, mms, 0);
}

static void update_mqd(stwuct mqd_managew *mm, void *mqd,
			stwuct queue_pwopewties *q,
			stwuct mqd_update_info *minfo)
{
	stwuct v9_mqd *m;

	m = get_mqd(mqd);

	m->cp_hqd_pq_contwow = 5 << CP_HQD_PQ_CONTWOW__WPTW_BWOCK_SIZE__SHIFT;
	m->cp_hqd_pq_contwow |= owdew_base_2(q->queue_size / 4) - 1;
	pw_debug("cp_hqd_pq_contwow 0x%x\n", m->cp_hqd_pq_contwow);

	m->cp_hqd_pq_base_wo = wowew_32_bits((uint64_t)q->queue_addwess >> 8);
	m->cp_hqd_pq_base_hi = uppew_32_bits((uint64_t)q->queue_addwess >> 8);

	m->cp_hqd_pq_wptw_wepowt_addw_wo = wowew_32_bits((uint64_t)q->wead_ptw);
	m->cp_hqd_pq_wptw_wepowt_addw_hi = uppew_32_bits((uint64_t)q->wead_ptw);
	m->cp_hqd_pq_wptw_poww_addw_wo = wowew_32_bits((uint64_t)q->wwite_ptw);
	m->cp_hqd_pq_wptw_poww_addw_hi = uppew_32_bits((uint64_t)q->wwite_ptw);

	m->cp_hqd_pq_doowbeww_contwow =
		q->doowbeww_off <<
			CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET__SHIFT;
	pw_debug("cp_hqd_pq_doowbeww_contwow 0x%x\n",
			m->cp_hqd_pq_doowbeww_contwow);

	m->cp_hqd_ib_contwow =
		3 << CP_HQD_IB_CONTWOW__MIN_IB_AVAIW_SIZE__SHIFT |
		1 << CP_HQD_IB_CONTWOW__IB_EXE_DISABWE__SHIFT;

	/*
	 * HW does not cwamp this fiewd cowwectwy. Maximum EOP queue size
	 * is constwained by pew-SE EOP done signaw count, which is 8-bit.
	 * Wimit is 0xFF EOP entwies (= 0x7F8 dwowds). CP wiww not submit
	 * mowe than (EOP entwy count - 1) so a queue size of 0x800 dwowds
	 * is safe, giving a maximum fiewd vawue of 0xA.
	 *
	 * Awso, do cawcuwation onwy if EOP is used (size > 0), othewwise
	 * the owdew_base_2 cawcuwation pwovides incowwect wesuwt.
	 *
	 */
	m->cp_hqd_eop_contwow = q->eop_wing_buffew_size ?
		min(0xA, owdew_base_2(q->eop_wing_buffew_size / 4) - 1) : 0;

	m->cp_hqd_eop_base_addw_wo =
			wowew_32_bits(q->eop_wing_buffew_addwess >> 8);
	m->cp_hqd_eop_base_addw_hi =
			uppew_32_bits(q->eop_wing_buffew_addwess >> 8);

	m->cp_hqd_iq_timew = 0;

	m->cp_hqd_vmid = q->vmid;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
		m->cp_hqd_pq_contwow |= CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK |
				2 << CP_HQD_PQ_CONTWOW__SWOT_BASED_WPTW__SHIFT |
				1 << CP_HQD_PQ_CONTWOW__QUEUE_FUWW_EN__SHIFT |
				1 << CP_HQD_PQ_CONTWOW__WPP_CWAMP_EN__SHIFT;
		m->cp_hqd_pq_doowbeww_contwow |= 1 <<
			CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_BIF_DWOP__SHIFT;
	}
	if (mm->dev->kfd->cwsw_enabwed && q->ctx_save_westowe_awea_addwess)
		m->cp_hqd_ctx_save_contwow = 0;

	if (KFD_GC_VEWSION(mm->dev) != IP_VEWSION(9, 4, 3))
		update_cu_mask(mm, mqd, minfo, 0);
	set_pwiowity(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
}


static uint32_t wead_doowbeww_id(void *mqd)
{
	stwuct v9_mqd *m = (stwuct v9_mqd *)mqd;

	wetuwn m->queue_doowbeww_id0;
}

static int get_wave_state(stwuct mqd_managew *mm, void *mqd,
			  stwuct queue_pwopewties *q,
			  void __usew *ctw_stack,
			  u32 *ctw_stack_used_size,
			  u32 *save_awea_used_size)
{
	stwuct v9_mqd *m;
	stwuct kfd_context_save_awea_headew headew;

	/* Contwow stack is wocated one page aftew MQD. */
	void *mqd_ctw_stack = (void *)((uintptw_t)mqd + PAGE_SIZE);

	m = get_mqd(mqd);

	*ctw_stack_used_size = m->cp_hqd_cntw_stack_size -
		m->cp_hqd_cntw_stack_offset;
	*save_awea_used_size = m->cp_hqd_wg_state_offset -
		m->cp_hqd_cntw_stack_size;

	headew.wave_state.contwow_stack_size = *ctw_stack_used_size;
	headew.wave_state.wave_state_size = *save_awea_used_size;

	headew.wave_state.wave_state_offset = m->cp_hqd_wg_state_offset;
	headew.wave_state.contwow_stack_offset = m->cp_hqd_cntw_stack_offset;

	if (copy_to_usew(ctw_stack, &headew, sizeof(headew.wave_state)))
		wetuwn -EFAUWT;

	if (copy_to_usew(ctw_stack + m->cp_hqd_cntw_stack_offset,
				mqd_ctw_stack + m->cp_hqd_cntw_stack_offset,
				*ctw_stack_used_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void get_checkpoint_info(stwuct mqd_managew *mm, void *mqd, u32 *ctw_stack_size)
{
	stwuct v9_mqd *m = get_mqd(mqd);

	*ctw_stack_size = m->cp_hqd_cntw_stack_size;
}

static void checkpoint_mqd(stwuct mqd_managew *mm, void *mqd, void *mqd_dst, void *ctw_stack_dst)
{
	stwuct v9_mqd *m;
	/* Contwow stack is wocated one page aftew MQD. */
	void *ctw_stack = (void *)((uintptw_t)mqd + PAGE_SIZE);

	m = get_mqd(mqd);

	memcpy(mqd_dst, m, sizeof(stwuct v9_mqd));
	memcpy(ctw_stack_dst, ctw_stack, m->cp_hqd_cntw_stack_size);
}

static void westowe_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *qp,
			const void *mqd_swc,
			const void *ctw_stack_swc, u32 ctw_stack_size)
{
	uint64_t addw;
	stwuct v9_mqd *m;
	void *ctw_stack;

	m = (stwuct v9_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memcpy(m, mqd_swc, sizeof(*m));

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = addw;

	/* Contwow stack is wocated one page aftew MQD. */
	ctw_stack = (void *)((uintptw_t)*mqd + PAGE_SIZE);
	memcpy(ctw_stack, ctw_stack_swc, ctw_stack_size);

	m->cp_hqd_pq_doowbeww_contwow =
		qp->doowbeww_off <<
			CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET__SHIFT;
	pw_debug("cp_hqd_pq_doowbeww_contwow 0x%x\n",
				m->cp_hqd_pq_doowbeww_contwow);

	qp->is_active = 0;
}

static void init_mqd_hiq(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	stwuct v9_mqd *m;

	init_mqd(mm, mqd, mqd_mem_obj, gawt_addw, q);

	m = get_mqd(*mqd);

	m->cp_hqd_pq_contwow |= 1 << CP_HQD_PQ_CONTWOW__PWIV_STATE__SHIFT |
			1 << CP_HQD_PQ_CONTWOW__KMD_QUEUE__SHIFT;
}

static int destwoy_hiq_mqd(stwuct mqd_managew *mm, void *mqd,
			enum kfd_pweempt_type type, unsigned int timeout,
			uint32_t pipe_id, uint32_t queue_id)
{
	int eww;
	stwuct v9_mqd *m;
	u32 doowbeww_off;

	m = get_mqd(mqd);

	doowbeww_off = m->cp_hqd_pq_doowbeww_contwow >>
			CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET__SHIFT;
	eww = amdgpu_amdkfd_unmap_hiq(mm->dev->adev, doowbeww_off, 0);
	if (eww)
		pw_debug("Destwoy HIQ MQD faiwed: %d\n", eww);

	wetuwn eww;
}

static void init_mqd_sdma(stwuct mqd_managew *mm, void **mqd,
		stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
		stwuct queue_pwopewties *q)
{
	stwuct v9_sdma_mqd *m;

	m = (stwuct v9_sdma_mqd *) mqd_mem_obj->cpu_ptw;

	memset(m, 0, sizeof(stwuct v9_sdma_mqd));

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = mqd_mem_obj->gpu_addw;

	mm->update_mqd(mm, m, q, NUWW);
}

#define SDMA_WWC_DUMMY_DEFAUWT 0xf

static void update_mqd_sdma(stwuct mqd_managew *mm, void *mqd,
			stwuct queue_pwopewties *q,
			stwuct mqd_update_info *minfo)
{
	stwuct v9_sdma_mqd *m;

	m = get_sdma_mqd(mqd);
	m->sdmax_wwcx_wb_cntw = owdew_base_2(q->queue_size / 4)
		<< SDMA0_WWC0_WB_CNTW__WB_SIZE__SHIFT |
		q->vmid << SDMA0_WWC0_WB_CNTW__WB_VMID__SHIFT |
		1 << SDMA0_WWC0_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT |
		6 << SDMA0_WWC0_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT;

	m->sdmax_wwcx_wb_base = wowew_32_bits(q->queue_addwess >> 8);
	m->sdmax_wwcx_wb_base_hi = uppew_32_bits(q->queue_addwess >> 8);
	m->sdmax_wwcx_wb_wptw_addw_wo = wowew_32_bits((uint64_t)q->wead_ptw);
	m->sdmax_wwcx_wb_wptw_addw_hi = uppew_32_bits((uint64_t)q->wead_ptw);
	m->sdmax_wwcx_doowbeww_offset =
		q->doowbeww_off << SDMA0_WWC0_DOOWBEWW_OFFSET__OFFSET__SHIFT;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;
	m->sdmax_wwcx_dummy_weg = SDMA_WWC_DUMMY_DEFAUWT;

	q->is_active = QUEUE_IS_ACTIVE(*q);
}

static void checkpoint_mqd_sdma(stwuct mqd_managew *mm,
				void *mqd,
				void *mqd_dst,
				void *ctw_stack_dst)
{
	stwuct v9_sdma_mqd *m;

	m = get_sdma_mqd(mqd);

	memcpy(mqd_dst, m, sizeof(stwuct v9_sdma_mqd));
}

static void westowe_mqd_sdma(stwuct mqd_managew *mm, void **mqd,
			     stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			     stwuct queue_pwopewties *qp,
			     const void *mqd_swc,
			     const void *ctw_stack_swc, const u32 ctw_stack_size)
{
	uint64_t addw;
	stwuct v9_sdma_mqd *m;

	m = (stwuct v9_sdma_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memcpy(m, mqd_swc, sizeof(*m));

	m->sdmax_wwcx_doowbeww_offset =
		qp->doowbeww_off << SDMA0_WWC0_DOOWBEWW_OFFSET__OFFSET__SHIFT;

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = addw;

	qp->is_active = 0;
}

static void init_mqd_hiq_v9_4_3(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	stwuct v9_mqd *m;
	int xcc = 0;
	stwuct kfd_mem_obj xcc_mqd_mem_obj;
	uint64_t xcc_gawt_addw = 0;

	memset(&xcc_mqd_mem_obj, 0x0, sizeof(stwuct kfd_mem_obj));

	fow (xcc = 0; xcc < NUM_XCC(mm->dev->xcc_mask); xcc++) {
		kfd_get_hiq_xcc_mqd(mm->dev, &xcc_mqd_mem_obj, xcc);

		init_mqd(mm, (void **)&m, &xcc_mqd_mem_obj, &xcc_gawt_addw, q);

		m->cp_hqd_pq_contwow |= CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK |
					1 << CP_HQD_PQ_CONTWOW__PWIV_STATE__SHIFT |
					1 << CP_HQD_PQ_CONTWOW__KMD_QUEUE__SHIFT;
		m->cp_mqd_stwide_size = kfd_hiq_mqd_stwide(mm->dev);
		if (xcc == 0) {
			/* Set no_update_wptw = 0 in Mastew XCC */
			m->cp_hqd_pq_contwow &= ~CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK;

			/* Set the MQD pointew and gawt addwess to XCC0 MQD */
			*mqd = m;
			*gawt_addw = xcc_gawt_addw;
		}
	}
}

static int hiq_woad_mqd_kiq_v9_4_3(stwuct mqd_managew *mm, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			stwuct queue_pwopewties *p, stwuct mm_stwuct *mms)
{
	uint32_t xcc_mask = mm->dev->xcc_mask;
	int xcc_id, eww, inst = 0;
	void *xcc_mqd;
	uint64_t hiq_mqd_size = kfd_hiq_mqd_stwide(mm->dev);

	fow_each_inst(xcc_id, xcc_mask) {
		xcc_mqd = mqd + hiq_mqd_size * inst;
		eww = mm->dev->kfd2kgd->hiq_mqd_woad(mm->dev->adev, xcc_mqd,
						     pipe_id, queue_id,
						     p->doowbeww_off, xcc_id);
		if (eww) {
			pw_debug("Faiwed to woad HIQ MQD fow XCC: %d\n", inst);
			bweak;
		}
		++inst;
	}

	wetuwn eww;
}

static int destwoy_hiq_mqd_v9_4_3(stwuct mqd_managew *mm, void *mqd,
			enum kfd_pweempt_type type, unsigned int timeout,
			uint32_t pipe_id, uint32_t queue_id)
{
	uint32_t xcc_mask = mm->dev->xcc_mask;
	int xcc_id, eww, inst = 0;
	uint64_t hiq_mqd_size = kfd_hiq_mqd_stwide(mm->dev);
	stwuct v9_mqd *m;
	u32 doowbeww_off;

	fow_each_inst(xcc_id, xcc_mask) {
		m = get_mqd(mqd + hiq_mqd_size * inst);

		doowbeww_off = m->cp_hqd_pq_doowbeww_contwow >>
				CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_OFFSET__SHIFT;

		eww = amdgpu_amdkfd_unmap_hiq(mm->dev->adev, doowbeww_off, xcc_id);
		if (eww) {
			pw_debug("Destwoy HIQ MQD faiwed fow xcc: %d\n", inst);
			bweak;
		}
		++inst;
	}

	wetuwn eww;
}

static void get_xcc_mqd(stwuct kfd_mem_obj *mqd_mem_obj,
			       stwuct kfd_mem_obj *xcc_mqd_mem_obj,
			       uint64_t offset)
{
	xcc_mqd_mem_obj->gtt_mem = (offset == 0) ?
					mqd_mem_obj->gtt_mem : NUWW;
	xcc_mqd_mem_obj->gpu_addw = mqd_mem_obj->gpu_addw + offset;
	xcc_mqd_mem_obj->cpu_ptw = (uint32_t *)((uintptw_t)mqd_mem_obj->cpu_ptw
						+ offset);
}

static void init_mqd_v9_4_3(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	stwuct v9_mqd *m;
	int xcc = 0;
	stwuct kfd_mem_obj xcc_mqd_mem_obj;
	uint64_t xcc_gawt_addw = 0;
	uint64_t xcc_ctx_save_westowe_awea_addwess;
	uint64_t offset = mm->mqd_stwide(mm, q);
	uint32_t wocaw_xcc_stawt = mm->dev->dqm->cuwwent_wogicaw_xcc_stawt++;

	memset(&xcc_mqd_mem_obj, 0x0, sizeof(stwuct kfd_mem_obj));
	fow (xcc = 0; xcc < NUM_XCC(mm->dev->xcc_mask); xcc++) {
		get_xcc_mqd(mqd_mem_obj, &xcc_mqd_mem_obj, offset*xcc);

		init_mqd(mm, (void **)&m, &xcc_mqd_mem_obj, &xcc_gawt_addw, q);

		m->cp_mqd_stwide_size = offset;

		/*
		 * Update the CWSW addwess fow each XCC if CWSW is enabwed
		 * and CWSW awea is awwocated in thunk
		 */
		if (mm->dev->kfd->cwsw_enabwed &&
		    q->ctx_save_westowe_awea_addwess) {
			xcc_ctx_save_westowe_awea_addwess =
				q->ctx_save_westowe_awea_addwess +
				(xcc * q->ctx_save_westowe_awea_size);

			m->cp_hqd_ctx_save_base_addw_wo =
				wowew_32_bits(xcc_ctx_save_westowe_awea_addwess);
			m->cp_hqd_ctx_save_base_addw_hi =
				uppew_32_bits(xcc_ctx_save_westowe_awea_addwess);
		}

		if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
			m->compute_tg_chunk_size = 1;
			m->compute_cuwwent_wogic_xcc_id =
					(wocaw_xcc_stawt + xcc) %
					NUM_XCC(mm->dev->xcc_mask);

			switch (xcc) {
			case 0:
				/* Mastew XCC */
				m->cp_hqd_pq_contwow &=
					~CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK;
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			/* PM4 Queue */
			m->compute_cuwwent_wogic_xcc_id = 0;
			m->compute_tg_chunk_size = 0;
			m->pm4_tawget_xcc_in_xcp = q->pm4_tawget_xcc;
		}

		if (xcc == 0) {
			/* Set the MQD pointew and gawt addwess to XCC0 MQD */
			*mqd = m;
			*gawt_addw = xcc_gawt_addw;
		}
	}
}

static void update_mqd_v9_4_3(stwuct mqd_managew *mm, void *mqd,
		      stwuct queue_pwopewties *q, stwuct mqd_update_info *minfo)
{
	stwuct v9_mqd *m;
	int xcc = 0;
	uint64_t size = mm->mqd_stwide(mm, q);

	fow (xcc = 0; xcc < NUM_XCC(mm->dev->xcc_mask); xcc++) {
		m = get_mqd(mqd + size * xcc);
		update_mqd(mm, m, q, minfo);

		update_cu_mask(mm, mqd, minfo, xcc);

		if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
			switch (xcc) {
			case 0:
				/* Mastew XCC */
				m->cp_hqd_pq_contwow &=
					~CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK;
				bweak;
			defauwt:
				bweak;
			}
			m->compute_tg_chunk_size = 1;
		} ewse {
			/* PM4 Queue */
			m->compute_cuwwent_wogic_xcc_id = 0;
			m->compute_tg_chunk_size = 0;
			m->pm4_tawget_xcc_in_xcp = q->pm4_tawget_xcc;
		}
	}
}

static int destwoy_mqd_v9_4_3(stwuct mqd_managew *mm, void *mqd,
		   enum kfd_pweempt_type type, unsigned int timeout,
		   uint32_t pipe_id, uint32_t queue_id)
{
	uint32_t xcc_mask = mm->dev->xcc_mask;
	int xcc_id, eww, inst = 0;
	void *xcc_mqd;
	stwuct v9_mqd *m;
	uint64_t mqd_offset;

	m = get_mqd(mqd);
	mqd_offset = m->cp_mqd_stwide_size;

	fow_each_inst(xcc_id, xcc_mask) {
		xcc_mqd = mqd + mqd_offset * inst;
		eww = mm->dev->kfd2kgd->hqd_destwoy(mm->dev->adev, xcc_mqd,
						    type, timeout, pipe_id,
						    queue_id, xcc_id);
		if (eww) {
			pw_debug("Destwoy MQD faiwed fow xcc: %d\n", inst);
			bweak;
		}
		++inst;
	}

	wetuwn eww;
}

static int woad_mqd_v9_4_3(stwuct mqd_managew *mm, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			stwuct queue_pwopewties *p, stwuct mm_stwuct *mms)
{
	/* AQW wwite pointew counts in 64B packets, PM4/CP counts in dwowds. */
	uint32_t wptw_shift = (p->fowmat == KFD_QUEUE_FOWMAT_AQW ? 4 : 0);
	uint32_t xcc_mask = mm->dev->xcc_mask;
	int xcc_id, eww, inst = 0;
	void *xcc_mqd;
	uint64_t mqd_stwide_size = mm->mqd_stwide(mm, p);

	fow_each_inst(xcc_id, xcc_mask) {
		xcc_mqd = mqd + mqd_stwide_size * inst;
		eww = mm->dev->kfd2kgd->hqd_woad(
			mm->dev->adev, xcc_mqd, pipe_id, queue_id,
			(uint32_t __usew *)p->wwite_ptw, wptw_shift, 0, mms,
			xcc_id);
		if (eww) {
			pw_debug("Woad MQD faiwed fow xcc: %d\n", inst);
			bweak;
		}
		++inst;
	}

	wetuwn eww;
}

static int get_wave_state_v9_4_3(stwuct mqd_managew *mm, void *mqd,
				 stwuct queue_pwopewties *q,
				 void __usew *ctw_stack,
				 u32 *ctw_stack_used_size,
				 u32 *save_awea_used_size)
{
	int xcc, eww = 0;
	void *xcc_mqd;
	void __usew *xcc_ctw_stack;
	uint64_t mqd_stwide_size = mm->mqd_stwide(mm, q);
	u32 tmp_ctw_stack_used_size = 0, tmp_save_awea_used_size = 0;

	fow (xcc = 0; xcc < NUM_XCC(mm->dev->xcc_mask); xcc++) {
		xcc_mqd = mqd + mqd_stwide_size * xcc;
		xcc_ctw_stack = (void __usew *)((uintptw_t)ctw_stack +
					q->ctx_save_westowe_awea_size * xcc);

		eww = get_wave_state(mm, xcc_mqd, q, xcc_ctw_stack,
				     &tmp_ctw_stack_used_size,
				     &tmp_save_awea_used_size);
		if (eww)
			bweak;

		/*
		 * Set the ctw_stack_used_size and save_awea_used_size to
		 * ctw_stack_used_size and save_awea_used_size of XCC 0 when
		 * passing the info the usew-space.
		 * Fow muwti XCC, usew-space wouwd have to wook at the headew
		 * info of each Contwow stack awea to detewmine the contwow
		 * stack size and save awea used.
		 */
		if (xcc == 0) {
			*ctw_stack_used_size = tmp_ctw_stack_used_size;
			*save_awea_used_size = tmp_save_awea_used_size;
		}
	}

	wetuwn eww;
}

#if defined(CONFIG_DEBUG_FS)

static int debugfs_show_mqd(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct v9_mqd), fawse);
	wetuwn 0;
}

static int debugfs_show_mqd_sdma(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct v9_sdma_mqd), fawse);
	wetuwn 0;
}

#endif

stwuct mqd_managew *mqd_managew_init_v9(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev)
{
	stwuct mqd_managew *mqd;

	if (WAWN_ON(type >= KFD_MQD_TYPE_MAX))
		wetuwn NUWW;

	mqd = kzawwoc(sizeof(*mqd), GFP_KEWNEW);
	if (!mqd)
		wetuwn NUWW;

	mqd->dev = dev;

	switch (type) {
	case KFD_MQD_TYPE_CP:
		mqd->awwocate_mqd = awwocate_mqd;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->get_checkpoint_info = get_checkpoint_info;
		mqd->checkpoint_mqd = checkpoint_mqd;
		mqd->westowe_mqd = westowe_mqd;
		mqd->mqd_size = sizeof(stwuct v9_mqd);
		mqd->mqd_stwide = mqd_stwide_v9;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		if (KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 3)) {
			mqd->init_mqd = init_mqd_v9_4_3;
			mqd->woad_mqd = woad_mqd_v9_4_3;
			mqd->update_mqd = update_mqd_v9_4_3;
			mqd->destwoy_mqd = destwoy_mqd_v9_4_3;
			mqd->get_wave_state = get_wave_state_v9_4_3;
		} ewse {
			mqd->init_mqd = init_mqd;
			mqd->woad_mqd = woad_mqd;
			mqd->update_mqd = update_mqd;
			mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
			mqd->get_wave_state = get_wave_state;
		}
		bweak;
	case KFD_MQD_TYPE_HIQ:
		mqd->awwocate_mqd = awwocate_hiq_mqd;
		mqd->fwee_mqd = fwee_mqd_hiq_sdma;
		mqd->update_mqd = update_mqd;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct v9_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		mqd->wead_doowbeww_id = wead_doowbeww_id;
		if (KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 3)) {
			mqd->init_mqd = init_mqd_hiq_v9_4_3;
			mqd->woad_mqd = hiq_woad_mqd_kiq_v9_4_3;
			mqd->destwoy_mqd = destwoy_hiq_mqd_v9_4_3;
		} ewse {
			mqd->init_mqd = init_mqd_hiq;
			mqd->woad_mqd = kfd_hiq_woad_mqd_kiq;
			mqd->destwoy_mqd = destwoy_hiq_mqd;
		}
		bweak;
	case KFD_MQD_TYPE_DIQ:
		mqd->awwocate_mqd = awwocate_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct v9_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		bweak;
	case KFD_MQD_TYPE_SDMA:
		mqd->awwocate_mqd = awwocate_sdma_mqd;
		mqd->init_mqd = init_mqd_sdma;
		mqd->fwee_mqd = fwee_mqd_hiq_sdma;
		mqd->woad_mqd = kfd_woad_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destwoy_mqd = kfd_destwoy_mqd_sdma;
		mqd->is_occupied = kfd_is_occupied_sdma;
		mqd->checkpoint_mqd = checkpoint_mqd_sdma;
		mqd->westowe_mqd = westowe_mqd_sdma;
		mqd->mqd_size = sizeof(stwuct v9_sdma_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd_sdma;
#endif
		bweak;
	defauwt:
		kfwee(mqd);
		wetuwn NUWW;
	}

	wetuwn mqd;
}
