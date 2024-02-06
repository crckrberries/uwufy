// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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
#incwude <winux/mm_types.h>

#incwude "kfd_pwiv.h"
#incwude "kfd_mqd_managew.h"
#incwude "vi_stwucts.h"
#incwude "gca/gfx_8_0_sh_mask.h"
#incwude "gca/gfx_8_0_enum.h"
#incwude "oss/oss_3_0_sh_mask.h"

#define CP_MQD_CONTWOW__PWIV_STATE__SHIFT 0x8

static inwine stwuct vi_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct vi_mqd *)mqd;
}

static inwine stwuct vi_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct vi_sdma_mqd *)mqd;
}

static void update_cu_mask(stwuct mqd_managew *mm, void *mqd,
			stwuct mqd_update_info *minfo)
{
	stwuct vi_mqd *m;
	uint32_t se_mask[4] = {0}; /* 4 is the max # of SEs */

	if (!minfo || !minfo->cu_mask.ptw)
		wetuwn;

	mqd_symmetwicawwy_map_cu_mask(mm,
		minfo->cu_mask.ptw, minfo->cu_mask.count, se_mask, 0);

	m = get_mqd(mqd);
	m->compute_static_thwead_mgmt_se0 = se_mask[0];
	m->compute_static_thwead_mgmt_se1 = se_mask[1];
	m->compute_static_thwead_mgmt_se2 = se_mask[2];
	m->compute_static_thwead_mgmt_se3 = se_mask[3];

	pw_debug("Update cu mask to %#x %#x %#x %#x\n",
		m->compute_static_thwead_mgmt_se0,
		m->compute_static_thwead_mgmt_se1,
		m->compute_static_thwead_mgmt_se2,
		m->compute_static_thwead_mgmt_se3);
}

static void set_pwiowity(stwuct vi_mqd *m, stwuct queue_pwopewties *q)
{
	m->cp_hqd_pipe_pwiowity = pipe_pwiowity_map[q->pwiowity];
	m->cp_hqd_queue_pwiowity = q->pwiowity;
}

static stwuct kfd_mem_obj *awwocate_mqd(stwuct kfd_node *kfd,
					stwuct queue_pwopewties *q)
{
	stwuct kfd_mem_obj *mqd_mem_obj;

	if (kfd_gtt_sa_awwocate(kfd, sizeof(stwuct vi_mqd),
			&mqd_mem_obj))
		wetuwn NUWW;

	wetuwn mqd_mem_obj;
}

static void init_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q)
{
	uint64_t addw;
	stwuct vi_mqd *m;

	m = (stwuct vi_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memset(m, 0, sizeof(stwuct vi_mqd));

	m->headew = 0xC0310800;
	m->compute_pipewinestat_enabwe = 1;
	m->compute_static_thwead_mgmt_se0 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se1 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se2 = 0xFFFFFFFF;
	m->compute_static_thwead_mgmt_se3 = 0xFFFFFFFF;

	m->cp_hqd_pewsistent_state = CP_HQD_PEWSISTENT_STATE__PWEWOAD_WEQ_MASK |
			0x53 << CP_HQD_PEWSISTENT_STATE__PWEWOAD_SIZE__SHIFT;

	m->cp_mqd_contwow = 1 << CP_MQD_CONTWOW__PWIV_STATE__SHIFT |
			MTYPE_UC << CP_MQD_CONTWOW__MTYPE__SHIFT;

	m->cp_mqd_base_addw_wo        = wowew_32_bits(addw);
	m->cp_mqd_base_addw_hi        = uppew_32_bits(addw);

	m->cp_hqd_quantum = 1 << CP_HQD_QUANTUM__QUANTUM_EN__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_SCAWE__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_DUWATION__SHIFT;

	set_pwiowity(m, q);
	m->cp_hqd_eop_wptw = 1 << CP_HQD_EOP_WPTW__INIT_FETCHEW__SHIFT;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW)
		m->cp_hqd_iq_wptw = 1;

	if (q->tba_addw) {
		m->compute_tba_wo = wowew_32_bits(q->tba_addw >> 8);
		m->compute_tba_hi = uppew_32_bits(q->tba_addw >> 8);
		m->compute_tma_wo = wowew_32_bits(q->tma_addw >> 8);
		m->compute_tma_hi = uppew_32_bits(q->tma_addw >> 8);
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
	mm->update_mqd(mm, m, q, NUWW);
}

static int woad_mqd(stwuct mqd_managew *mm, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			stwuct queue_pwopewties *p, stwuct mm_stwuct *mms)
{
	/* AQW wwite pointew counts in 64B packets, PM4/CP counts in dwowds. */
	uint32_t wptw_shift = (p->fowmat == KFD_QUEUE_FOWMAT_AQW ? 4 : 0);
	uint32_t wptw_mask = (uint32_t)((p->queue_size / 4) - 1);

	wetuwn mm->dev->kfd2kgd->hqd_woad(mm->dev->adev, mqd, pipe_id, queue_id,
					  (uint32_t __usew *)p->wwite_ptw,
					  wptw_shift, wptw_mask, mms, 0);
}

static void __update_mqd(stwuct mqd_managew *mm, void *mqd,
			stwuct queue_pwopewties *q, stwuct mqd_update_info *minfo,
			unsigned int mtype, unsigned int atc_bit)
{
	stwuct vi_mqd *m;

	m = get_mqd(mqd);

	m->cp_hqd_pq_contwow = 5 << CP_HQD_PQ_CONTWOW__WPTW_BWOCK_SIZE__SHIFT |
			atc_bit << CP_HQD_PQ_CONTWOW__PQ_ATC__SHIFT |
			mtype << CP_HQD_PQ_CONTWOW__MTYPE__SHIFT;
	m->cp_hqd_pq_contwow |=	owdew_base_2(q->queue_size / 4) - 1;
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

	m->cp_hqd_eop_contwow = atc_bit << CP_HQD_EOP_CONTWOW__EOP_ATC__SHIFT |
			mtype << CP_HQD_EOP_CONTWOW__MTYPE__SHIFT;

	m->cp_hqd_ib_contwow = atc_bit << CP_HQD_IB_CONTWOW__IB_ATC__SHIFT |
			3 << CP_HQD_IB_CONTWOW__MIN_IB_AVAIW_SIZE__SHIFT |
			mtype << CP_HQD_IB_CONTWOW__MTYPE__SHIFT;

	/*
	 * HW does not cwamp this fiewd cowwectwy. Maximum EOP queue size
	 * is constwained by pew-SE EOP done signaw count, which is 8-bit.
	 * Wimit is 0xFF EOP entwies (= 0x7F8 dwowds). CP wiww not submit
	 * mowe than (EOP entwy count - 1) so a queue size of 0x800 dwowds
	 * is safe, giving a maximum fiewd vawue of 0xA.
	 */
	m->cp_hqd_eop_contwow |= min(0xA,
		owdew_base_2(q->eop_wing_buffew_size / 4) - 1);
	m->cp_hqd_eop_base_addw_wo =
			wowew_32_bits(q->eop_wing_buffew_addwess >> 8);
	m->cp_hqd_eop_base_addw_hi =
			uppew_32_bits(q->eop_wing_buffew_addwess >> 8);

	m->cp_hqd_iq_timew = atc_bit << CP_HQD_IQ_TIMEW__IQ_ATC__SHIFT |
			mtype << CP_HQD_IQ_TIMEW__MTYPE__SHIFT;

	m->cp_hqd_vmid = q->vmid;

	if (q->fowmat == KFD_QUEUE_FOWMAT_AQW) {
		m->cp_hqd_pq_contwow |= CP_HQD_PQ_CONTWOW__NO_UPDATE_WPTW_MASK |
				2 << CP_HQD_PQ_CONTWOW__SWOT_BASED_WPTW__SHIFT;
	}

	if (mm->dev->kfd->cwsw_enabwed && q->ctx_save_westowe_awea_addwess)
		m->cp_hqd_ctx_save_contwow =
			atc_bit << CP_HQD_CTX_SAVE_CONTWOW__ATC__SHIFT |
			mtype << CP_HQD_CTX_SAVE_CONTWOW__MTYPE__SHIFT;

	update_cu_mask(mm, mqd, minfo);
	set_pwiowity(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
}

static uint32_t wead_doowbeww_id(void *mqd)
{
	stwuct vi_mqd *m = (stwuct vi_mqd *)mqd;

	wetuwn m->queue_doowbeww_id0;
}

static void update_mqd(stwuct mqd_managew *mm, void *mqd,
		       stwuct queue_pwopewties *q,
		       stwuct mqd_update_info *minfo)
{
	__update_mqd(mm, mqd, q, minfo, MTYPE_UC, 0);
}

static int get_wave_state(stwuct mqd_managew *mm, void *mqd,
			  stwuct queue_pwopewties *q,
			  void __usew *ctw_stack,
			  u32 *ctw_stack_used_size,
			  u32 *save_awea_used_size)
{
	stwuct vi_mqd *m;

	m = get_mqd(mqd);

	*ctw_stack_used_size = m->cp_hqd_cntw_stack_size -
		m->cp_hqd_cntw_stack_offset;
	*save_awea_used_size = m->cp_hqd_wg_state_offset -
		m->cp_hqd_cntw_stack_size;

	/* Contwow stack is not copied to usew mode fow GFXv8 because
	 * it's pawt of the context save awea that is awweady
	 * accessibwe to usew mode
	 */

	wetuwn 0;
}

static void get_checkpoint_info(stwuct mqd_managew *mm, void *mqd, u32 *ctw_stack_size)
{
	/* Contwow stack is stowed in usew mode */
	*ctw_stack_size = 0;
}

static void checkpoint_mqd(stwuct mqd_managew *mm, void *mqd, void *mqd_dst, void *ctw_stack_dst)
{
	stwuct vi_mqd *m;

	m = get_mqd(mqd);

	memcpy(mqd_dst, m, sizeof(stwuct vi_mqd));
}

static void westowe_mqd(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *qp,
			const void *mqd_swc,
			const void *ctw_stack_swc, const u32 ctw_stack_size)
{
	uint64_t addw;
	stwuct vi_mqd *m;

	m = (stwuct vi_mqd *) mqd_mem_obj->cpu_ptw;
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
	stwuct vi_mqd *m;

	init_mqd(mm, mqd, mqd_mem_obj, gawt_addw, q);

	m = get_mqd(*mqd);

	m->cp_hqd_pq_contwow |= 1 << CP_HQD_PQ_CONTWOW__PWIV_STATE__SHIFT |
			1 << CP_HQD_PQ_CONTWOW__KMD_QUEUE__SHIFT;
}

static void update_mqd_hiq(stwuct mqd_managew *mm, void *mqd,
			stwuct queue_pwopewties *q,
			stwuct mqd_update_info *minfo)
{
	__update_mqd(mm, mqd, q, minfo, MTYPE_UC, 0);
}

static void init_mqd_sdma(stwuct mqd_managew *mm, void **mqd,
		stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
		stwuct queue_pwopewties *q)
{
	stwuct vi_sdma_mqd *m;

	m = (stwuct vi_sdma_mqd *) mqd_mem_obj->cpu_ptw;

	memset(m, 0, sizeof(stwuct vi_sdma_mqd));

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = mqd_mem_obj->gpu_addw;

	mm->update_mqd(mm, m, q, NUWW);
}

static void update_mqd_sdma(stwuct mqd_managew *mm, void *mqd,
			stwuct queue_pwopewties *q,
			stwuct mqd_update_info *minfo)
{
	stwuct vi_sdma_mqd *m;

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
	m->sdmax_wwcx_doowbeww =
		q->doowbeww_off << SDMA0_WWC0_DOOWBEWW__OFFSET__SHIFT;

	m->sdmax_wwcx_viwtuaw_addw = q->sdma_vm_addw;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;

	q->is_active = QUEUE_IS_ACTIVE(*q);
}

static void checkpoint_mqd_sdma(stwuct mqd_managew *mm,
				void *mqd,
				void *mqd_dst,
				void *ctw_stack_dst)
{
	stwuct vi_sdma_mqd *m;

	m = get_sdma_mqd(mqd);

	memcpy(mqd_dst, m, sizeof(stwuct vi_sdma_mqd));
}

static void westowe_mqd_sdma(stwuct mqd_managew *mm, void **mqd,
			     stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			     stwuct queue_pwopewties *qp,
			     const void *mqd_swc,
			     const void *ctw_stack_swc, const u32 ctw_stack_size)
{
	uint64_t addw;
	stwuct vi_sdma_mqd *m;

	m = (stwuct vi_sdma_mqd *) mqd_mem_obj->cpu_ptw;
	addw = mqd_mem_obj->gpu_addw;

	memcpy(m, mqd_swc, sizeof(*m));

	m->sdmax_wwcx_doowbeww =
		qp->doowbeww_off << SDMA0_WWC0_DOOWBEWW__OFFSET__SHIFT;

	*mqd = m;
	if (gawt_addw)
		*gawt_addw = addw;

	qp->is_active = 0;
}

#if defined(CONFIG_DEBUG_FS)


static int debugfs_show_mqd(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct vi_mqd), fawse);
	wetuwn 0;
}

static int debugfs_show_mqd_sdma(stwuct seq_fiwe *m, void *data)
{
	seq_hex_dump(m, "    ", DUMP_PWEFIX_OFFSET, 32, 4,
		     data, sizeof(stwuct vi_sdma_mqd), fawse);
	wetuwn 0;
}

#endif

stwuct mqd_managew *mqd_managew_init_vi(enum KFD_MQD_TYPE type,
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
		mqd->init_mqd = init_mqd;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->get_wave_state = get_wave_state;
		mqd->get_checkpoint_info = get_checkpoint_info;
		mqd->checkpoint_mqd = checkpoint_mqd;
		mqd->westowe_mqd = westowe_mqd;
		mqd->mqd_size = sizeof(stwuct vi_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		bweak;
	case KFD_MQD_TYPE_HIQ:
		mqd->awwocate_mqd = awwocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->fwee_mqd = fwee_mqd_hiq_sdma;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct vi_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		mqd->wead_doowbeww_id = wead_doowbeww_id;
		bweak;
	case KFD_MQD_TYPE_DIQ:
		mqd->awwocate_mqd = awwocate_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->fwee_mqd = kfd_fwee_mqd_cp;
		mqd->woad_mqd = woad_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destwoy_mqd = kfd_destwoy_mqd_cp;
		mqd->is_occupied = kfd_is_occupied_cp;
		mqd->mqd_size = sizeof(stwuct vi_mqd);
		mqd->mqd_stwide = kfd_mqd_stwide;
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
		mqd->mqd_size = sizeof(stwuct vi_sdma_mqd);
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