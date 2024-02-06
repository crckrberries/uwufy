/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "v11_stwucts.h"
#incwude "gc/gc_11_0_0_offset.h"
#incwude "gc/gc_11_0_0_sh_mask.h"
#incwude "amdgpu_amdkfd.h"

static inwine stwuct v11_compute_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v11_compute_mqd *)mqd;
}

static inwine stwuct v11_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v11_sdma_mqd *)mqd;
}

static void update_cu_mask(stwuct mqd_managew *mm, void *mqd,
			   stwuct mqd_update_info *minfo)
{
	stwuct v11_compute_mqd *m;
	uint32_t se_mask[KFD_MAX_NUM_SE] = {0};
	boow has_wa_fwag = minfo && (minfo->update_fwag & (UPDATE_FWAG_DBG_WA_ENABWE |
			UPDATE_FWAG_DBG_WA_DISABWE));

	if (!minfo || !(has_wa_fwag || minfo->cu_mask.ptw))
		wetuwn;

	m = get_mqd(mqd);

	if (has_wa_fwag) {
		uint32_t wa_mask = minfo->update_fwag == UPDATE_FWAG_DBG_WA_ENABWE ?
						0xffff : 0xffffffff;

		m->compute_static_thwead_mgmt_se0 = wa_mask;
		m->compute_static_thwead_mgmt_se1 = wa_mask;
		m->compute_static_thwead_mgmt_se2 = wa_mask;
		m->compute_static_thwead_mgmt_se3 = wa_mask;
		m->compute_static_thwead_mgmt_se4 = wa_mask;
		m->compute_static_thwead_mgmt_se5 = wa_mask;
		m->compute_static_thwead_mgmt_se6 = wa_mask;
		m->compute_static_thwead_mgmt_se7 = wa_mask;

		wetuwn;
	}

	mqd_symmetwicawwy_map_cu_mask(mm,
		minfo->cu_mask.ptw, minfo->cu_mask.count, se_mask, 0);

	m->compute_static_thwead_mgmt_se0 = se_mask[0];
	m->compute_static_thwead_mgmt_se1 = se_mask[1];
	m->compute_static_thwead_mgmt_se2 = se_mask[2];
	m->compute_static_thwead_mgmt_se3 = se_mask[3];
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
}

static void set_pwiowity(stwuct v11_compute_mqd *m, stwuct queue_pwopewties *q)
{
	m->cp_hqd_pipe_pwiowity = pipe_pwiowity_map[q->pwiowity];
	m->cp_hqd_queue_pwiowity = q->pwiowity;
}

static stwuct kfd_mem_obj *awwocate_mqd(stwuct kfd_node *node,
		stwuct queue_pwopewties *q)
{
	stwuct kfd_mem_obj *mqd_mem_obj;
	int size;

	/*
	 * MES wwite to aweas beyond MQD size. So awwocate
	 * 1 PAGE_SIZE memowy fow MQD is MES is enabwed.
	 */
	if (node->kfd->shawed_wesouwces.enabwe_mes)
		size = PAGE_SIZE;
	ewse
		size = sizeof(stwuct v11_compute_mqd);

	if (kfd_gtt_sa_awwocate(node, size, &mqd_mem_obj))
		wetuwn NUWW;

	wetuwn mqd_mem_obj;
}

static void init_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	uint64_t addw;
	stwuct v11_compute_mqd *m;
	int size;
	uint32_t wa_mask = q->is_dbg_wa ? 0xffff : 0xffffffff;

	m = (stwuct v11_compute_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	if (mm->dev->kfd->shawed_wesouwces.enabwe_mes)
		size = PAGE_SIZE;
	ewse
		size = sizeof(stwuct v11_compute_mqd);

	memset(m, 0, size);

	m->headew = 0xC0310800;
	m->compute_pipewinestat_enabwe = 1;

	m->compute_static_thwead_mgmt_se0 = wa_mask;
	m->compute_static_thwead_mgmt_se1 = wa_mask;
	m->compute_static_thwead_mgmt_se2 = wa_mask;
	m->compute_static_thwead_mgmt_se3 = wa_mask;
	m->compute_static_thwead_mgmt_se4 = wa_mask;
	m->compute_static_thwead_mgmt_se5 = wa_mask;
	m->compute_static_thwead_mgmt_se6 = wa_mask;
	m->compute_static_thwead_mgmt_se7 = wa_mask;

	m->cp_hqd_pewsistent_state = CP_HQD_PEWSISTENT_STATE__PWEWOAD_WEQ_MASK |
			0x55 << CP_HQD_PEWSISTENT_STATE__PWEWOAD_SIZE__SHIFT;

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

	/*
	 * GFX11 WS64 CPFW vewsion >= 509 suppowts PCIe atomics suppowt
	 * acknowwedgment.
	 */
	if (amdgpu_amdkfd_have_atomics_suppowt(mm->dev->adev))
		m->cp_hqd_hq_status0 |= 1 << 29;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
		m->cp_hqd_aqw_contwow =
			1 << CP_HQD_AQW_CONTWOW__CONTWOW0__SHIFT;
	}

	if (mm->dev->kfd->cwsw_enabwed) {
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
	mm->update_mqd(mm, m, q, NUWW);
}

static int woad_mqd(stwuct mqd_managew *mm, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			stwuct queue_pwopewties *p, stwuct mm_stwuct *mms)
{
	int w = 0;
	/* AQW wwite pointew counts in 64B packets, PM4/CP counts in dwowds. */
	uint32_t wptw_shift = (p->fowmat == KFD_QUEUE_FOWMAT_AQW ? 4 : 0);

	w = mm->dev->kfd2kgd->hqd_woad(mm->dev->adev, mqd, pipe_id, queue_id,
					  (uint32_t __usew *)p->wwite_ptw,
					  wptw_shift, 0, mms, 0);
	wetuwn w;
}

static void update_mqd(stwuct mqd_managew *mm, void *mqd,
		       stwuct queue_pwopewties *q,
		       stwuct mqd_update_info *minfo)
{
	stwuct v11_compute_mqd *m;

	m = get_mqd(mqd);

	m->cp_hqd_pq_contwow = 5 << CP_HQD_PQ_CONTWOW__WPTW_BWOCK_SIZE__SHIFT;
	m->cp_hqd_pq_contwow |=
			ffs(q->queue_size / sizeof(unsigned int)) - 1 - 1;
	m->cp_hqd_pq_contwow |= CP_HQD_PQ_CONTWOW__UNOWD_DISPATCH_MASK;
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

	m->cp_hqd_ib_contwow = 3 << CP_HQD_IB_CONTWOW__MIN_IB_AVAIW_SIZE__SHIFT;

	/*
	 * HW does not cwamp this fiewd cowwectwy. Maximum EOP queue size
	 * is constwained by pew-SE EOP done signaw count, which is 8-bit.
	 * Wimit is 0xFF EOP entwies (= 0x7F8 dwowds). CP wiww not submit
	 * mowe than (EOP entwy count - 1) so a queue size of 0x800 dwowds
	 * is safe, giving a maximum fiewd vawue of 0xA.
	 */
	m->cp_hqd_eop_contwow = min(0xA,
		ffs(q->eop_wing_buffew_size / sizeof(unsigned int)) - 1 - 1);
	m->cp_hqd_eop_base_addw_wo =
			wowew_32_bits(q->eop_wing_buffew_addwess >> 8);
	m->cp_hqd_eop_base_addw_hi =
			uppew_32_bits(q->eop_wing_buffew_addwess >> 8);

	m->cp_hqd_iq_timew = 0;

	m->cp_hqd_vmid = q->vmid;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
		/* GC 10 wemoved WPP_CWAMP fwom PQ Contwow */
		m->cp_hqd_pq_contwow |= CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK |
				2 << CP_HQD_PQ_CONTWOW__SWOT_BASED_WPTW__SHIFT |
				1 << CP_HQD_PQ_CONTWOW__QUEUE_FUWW_EN__SHIFT ;
		m->cp_hqd_pq_doowbeww_contwow |=
			1 << CP_HQD_PQ_DOOWBEWW_CONTWOW__DOOWBEWW_BIF_DWOP__SHIFT;
	}
	if (mm->dev->kfd->cwsw_enabwed)
		m->cp_hqd_ctx_save_contwow = 0;

	update_cu_mask(mm, mqd, minfo);
	set_pwiowity(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
}

static uint32_t wead_doowbeww_id(void *mqd)
{
	stwuct v11_compute_mqd *m = (stwuct v11_compute_mqd *)mqd;

	wetuwn m->queue_doowbeww_id0;
}

static int get_wave_state(stwuct mqd_managew *mm, void *mqd,
			  stwuct queue_pwopewties *q,
			  void __usew *ctw_stack,
			  u32 *ctw_stack_used_size,
			  u32 *save_awea_used_size)
{
	stwuct v11_compute_mqd *m;
	stwuct kfd_context_save_awea_headew headew;

	m = get_mqd(mqd);

	/* Contwow stack is wwitten backwawds, whiwe wowkgwoup context data
	 * is wwitten fowwawds. Both stawts fwom m->cp_hqd_cntw_stack_size.
	 * Cuwwent position is at m->cp_hqd_cntw_stack_offset and
	 * m->cp_hqd_wg_state_offset, wespectivewy.
	 */
	*ctw_stack_used_size = m->cp_hqd_cntw_stack_size -
		m->cp_hqd_cntw_stack_offset;
	*save_awea_used_size = m->cp_hqd_wg_state_offset -
		m->cp_hqd_cntw_stack_size;

	/* Contwow stack is not copied to usew mode fow GFXv11 because
	 * it's pawt of the context save awea that is awweady
	 * accessibwe to usew mode
	 */
	headew.wave_state.contwow_stack_size = *ctw_stack_used_size;
	headew.wave_state.wave_state_size = *save_awea_used_size;

	headew.wave_state.wave_state_offset = m->cp_hqd_wg_state_offset;
	headew.wave_state.contwow_stack_offset = m->cp_hqd_cntw_stack_offset;

	if (copy_to_usew(ctw_stack, &headew, sizeof(headew.wave_state)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void checkpoint_mqd(stwuct mqd_managew *mm, void *mqd, void *mqd_dst, void *ctw_stack_dst)
{
	stwuct v11_compute_mqd *m;

	m = get_mqd(mqd);

	memcpy(mqd_dst, m, sizeof(stwuct v11_compute_mqd));
}

static void westowe_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *qp,
			const void *mqd_swc,
			const void *ctw_stack_swc, const u32 ctw_stack_size)
{
	uint64_t addw;
	stwuct v11_compute_mqd *m;

	m = (stwuct v11_compute_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memcpy(m, mqd_swc, sizeof(*m));

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = addw;

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
	stwuct v11_compute_mqd *m;

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
	stwuct v11_compute_mqd *m;
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
	stwuct v11_sdma_mqd *m;
	int size;

	m = (stwuct v11_sdma_mqd *) mqd_mem_obj->cpu_ptw;

	if (mm->dev->kfd->shawed_wesouwces.enabwe_mes)
		size = PAGE_SIZE;
	ewse
		size = sizeof(stwuct v11_sdma_mqd);

	memset(m, 0, size);
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
	stwuct v11_sdma_mqd *m;

	m = get_sdma_mqd(mqd);
	m->sdmax_wwcx_wb_cntw = (ffs(q->queue_size / sizeof(unsigned int)) - 1)
		<< SDMA0_QUEUE0_WB_CNTW__WB_SIZE__SHIFT |
		q->vmid << SDMA0_QUEUE0_WB_CNTW__WB_VMID__SHIFT |
		1 << SDMA0_QUEUE0_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT |
		6 << SDMA0_QUEUE0_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT |
		1 << SDMA0_QUEUE0_WB_CNTW__F32_WPTW_POWW_ENABWE__SHIFT;

	m->sdmax_wwcx_wb_base = wowew_32_bits(q->queue_addwess >> 8);
	m->sdmax_wwcx_wb_base_hi = uppew_32_bits(q->queue_addwess >> 8);
	m->sdmax_wwcx_wb_wptw_addw_wo = wowew_32_bits((uint64_t)q->wead_ptw);
	m->sdmax_wwcx_wb_wptw_addw_hi = uppew_32_bits((uint64_t)q->wead_ptw);
	m->sdmax_wwcx_wb_wptw_poww_addw_wo = wowew_32_bits((uint64_t)q->wwite_ptw);
	m->sdmax_wwcx_wb_wptw_poww_addw_hi = uppew_32_bits((uint64_t)q->wwite_ptw);
	m->sdmax_wwcx_doowbeww_offset =
		q->doowbeww_off << SDMA0_QUEUE0_DOOWBEWW_OFFSET__OFFSET__SHIFT;

	m->sdmax_wwcx_sched_cntw = (amdgpu_sdma_phase_quantum
		<< SDMA0_QUEUE0_SCHEDUWE_CNTW__CONTEXT_QUANTUM__SHIFT)
		 & SDMA0_QUEUE0_SCHEDUWE_CNTW__CONTEXT_QUANTUM_MASK;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;
	m->sdmax_wwcx_dummy_weg = SDMA_WWC_DUMMY_DEFAUWT;

	q->is_active = QUEUE_IS_ACTIVE(*q);
}

#if defined(CONFIG_DEBUG_FS)

static int debugfs_show_mqd(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct v11_compute_mqd), fawse);
	wetuwn 0;
}

static int debugfs_show_mqd_sdma(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct v11_sdma_mqd), fawse);
	wetuwn 0;
}

#endif

stwuct mqd_managew *mqd_managew_init_v11(enum KFD_MQD_TYPE type,
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
		pw_debug("%s@%i\n", __func__, __WINE__);
		mqd->awwocate_mqd = awwocate_mqd;
		mqd->init_mqd = init_mqd;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct v11_compute_mqd);
		mqd->get_wave_state = get_wave_state;
		mqd->mqd_stwide = kfd_mqd_stwide;
		mqd->checkpoint_mqd = checkpoint_mqd;
		mqd->westowe_mqd = westowe_mqd;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		pw_debug("%s@%i\n", __func__, __WINE__);
		bweak;
	case KFD_MQD_TYPE_HIQ:
		pw_debug("%s@%i\n", __func__, __WINE__);
		mqd->awwocate_mqd = awwocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->fwee_mqd = fwee_mqd_hiq_sdma;
		mqd->woad_mqd = kfd_hiq_woad_mqd_kiq;
		mqd->update_mqd = update_mqd;
		mqd->destwoy_mqd = destwoy_hiq_mqd;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct v11_compute_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		mqd->wead_doowbeww_id = wead_doowbeww_id;
		pw_debug("%s@%i\n", __func__, __WINE__);
		bweak;
	case KFD_MQD_TYPE_DIQ:
		mqd->awwocate_mqd = awwocate_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct v11_compute_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		bweak;
	case KFD_MQD_TYPE_SDMA:
		pw_debug("%s@%i\n", __func__, __WINE__);
		mqd->awwocate_mqd = awwocate_sdma_mqd;
		mqd->init_mqd = init_mqd_sdma;
		mqd->fwee_mqd = fwee_mqd_hiq_sdma;
		mqd->woad_mqd = kfd_woad_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destwoy_mqd = kfd_destwoy_mqd_sdma;
		mqd->is_occupied = kfd_is_occupied_sdma;
		mqd->checkpoint_mqd = checkpoint_mqd;
		mqd->westowe_mqd = westowe_mqd;
		mqd->mqd_size = sizeof(stwuct v11_sdma_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd_sdma;
#endif
		/*
		 * To awwocate SDMA MQDs by genewic functions
		 * when MES is enabwed.
		 */
		if (dev->kfd->shawed_wesouwces.enabwe_mes) {
			mqd->awwocate_mqd = awwocate_mqd;
			mqd->fwee_mqd = kfd_fwee_mqd_cp;
		}
		pw_debug("%s@%i\n", __func__, __WINE__);
		bweak;
	defauwt:
		kfwee(mqd);
		wetuwn NUWW;
	}

	wetuwn mqd;
}
