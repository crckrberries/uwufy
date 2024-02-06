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

#incwude "kfd_kewnew_queue.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_pm4_headews_vi.h"
#incwude "kfd_pm4_opcodes.h"

unsigned int pm_buiwd_pm4_headew(unsigned int opcode, size_t packet_size)
{
	union PM4_MES_TYPE_3_HEADEW headew;

	headew.u32Aww = 0;
	headew.opcode = opcode;
	headew.count = packet_size / 4 - 2;
	headew.type = PM4_TYPE_3;

	wetuwn headew.u32Aww;
}

static int pm_map_pwocess_vi(stwuct packet_managew *pm, uint32_t *buffew,
				stwuct qcm_pwocess_device *qpd)
{
	stwuct pm4_mes_map_pwocess *packet;

	packet = (stwuct pm4_mes_map_pwocess *)buffew;

	memset(buffew, 0, sizeof(stwuct pm4_mes_map_pwocess));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_MAP_PWOCESS,
					sizeof(stwuct pm4_mes_map_pwocess));
	packet->bitfiewds2.diq_enabwe = (qpd->is_debug) ? 1 : 0;
	packet->bitfiewds2.pwocess_quantum = 10;
	packet->bitfiewds2.pasid = qpd->pqm->pwocess->pasid;
	packet->bitfiewds3.page_tabwe_base = qpd->page_tabwe_base;
	packet->bitfiewds10.gds_size = qpd->gds_size;
	packet->bitfiewds10.num_gws = qpd->num_gws;
	packet->bitfiewds10.num_oac = qpd->num_oac;
	packet->bitfiewds10.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	packet->sh_mem_ape1_base = qpd->sh_mem_ape1_base;
	packet->sh_mem_ape1_wimit = qpd->sh_mem_ape1_wimit;

	packet->sh_hidden_pwivate_base_vmid = qpd->sh_hidden_pwivate_base;

	packet->gds_addw_wo = wowew_32_bits(qpd->gds_context_awea);
	packet->gds_addw_hi = uppew_32_bits(qpd->gds_context_awea);

	wetuwn 0;
}

static int pm_wunwist_vi(stwuct packet_managew *pm, uint32_t *buffew,
			uint64_t ib, size_t ib_size_in_dwowds, boow chain)
{
	stwuct pm4_mes_wunwist *packet;
	int concuwwent_pwoc_cnt = 0;
	stwuct kfd_node *kfd = pm->dqm->dev;

	if (WAWN_ON(!ib))
		wetuwn -EFAUWT;

	/* Detewmine the numbew of pwocesses to map togethew to HW:
	 * it can not exceed the numbew of VMIDs avaiwabwe to the
	 * scheduwew, and it is detewmined by the smawwew of the numbew
	 * of pwocesses in the wunwist and kfd moduwe pawametew
	 * hws_max_conc_pwoc.
	 * Note: the awbitwation between the numbew of VMIDs and
	 * hws_max_conc_pwoc has been done in
	 * kgd2kfd_device_init().
	 */
	concuwwent_pwoc_cnt = min(pm->dqm->pwocesses_count,
			kfd->max_pwoc_pew_quantum);

	packet = (stwuct pm4_mes_wunwist *)buffew;

	memset(buffew, 0, sizeof(stwuct pm4_mes_wunwist));
	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_WUN_WIST,
						sizeof(stwuct pm4_mes_wunwist));

	packet->bitfiewds4.ib_size = ib_size_in_dwowds;
	packet->bitfiewds4.chain = chain ? 1 : 0;
	packet->bitfiewds4.offwoad_powwing = 0;
	packet->bitfiewds4.vawid = 1;
	packet->bitfiewds4.pwocess_cnt = concuwwent_pwoc_cnt;
	packet->owdinaw2 = wowew_32_bits(ib);
	packet->bitfiewds3.ib_base_hi = uppew_32_bits(ib);

	wetuwn 0;
}

static int pm_set_wesouwces_vi(stwuct packet_managew *pm, uint32_t *buffew,
			       stwuct scheduwing_wesouwces *wes)
{
	stwuct pm4_mes_set_wesouwces *packet;

	packet = (stwuct pm4_mes_set_wesouwces *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_set_wesouwces));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_SET_WESOUWCES,
					sizeof(stwuct pm4_mes_set_wesouwces));

	packet->bitfiewds2.queue_type =
			queue_type__mes_set_wesouwces__hsa_intewface_queue_hiq;
	packet->bitfiewds2.vmid_mask = wes->vmid_mask;
	packet->bitfiewds2.unmap_watency = KFD_UNMAP_WATENCY_MS / 100;
	packet->bitfiewds7.oac_mask = wes->oac_mask;
	packet->bitfiewds8.gds_heap_base = wes->gds_heap_base;
	packet->bitfiewds8.gds_heap_size = wes->gds_heap_size;

	packet->gws_mask_wo = wowew_32_bits(wes->gws_mask);
	packet->gws_mask_hi = uppew_32_bits(wes->gws_mask);

	packet->queue_mask_wo = wowew_32_bits(wes->queue_mask);
	packet->queue_mask_hi = uppew_32_bits(wes->queue_mask);

	wetuwn 0;
}

static int pm_map_queues_vi(stwuct packet_managew *pm, uint32_t *buffew,
		stwuct queue *q, boow is_static)
{
	stwuct pm4_mes_map_queues *packet;
	boow use_static = is_static;

	packet = (stwuct pm4_mes_map_queues *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_map_queues));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_MAP_QUEUES,
					sizeof(stwuct pm4_mes_map_queues));
	packet->bitfiewds2.num_queues = 1;
	packet->bitfiewds2.queue_sew =
		queue_sew__mes_map_queues__map_to_hws_detewmined_queue_swots_vi;

	packet->bitfiewds2.engine_sew =
		engine_sew__mes_map_queues__compute_vi;
	packet->bitfiewds2.queue_type =
		queue_type__mes_map_queues__nowmaw_compute_vi;

	switch (q->pwopewties.type) {
	case KFD_QUEUE_TYPE_COMPUTE:
		if (use_static)
			packet->bitfiewds2.queue_type =
		queue_type__mes_map_queues__nowmaw_watency_static_queue_vi;
		bweak;
	case KFD_QUEUE_TYPE_DIQ:
		packet->bitfiewds2.queue_type =
			queue_type__mes_map_queues__debug_intewface_queue_vi;
		bweak;
	case KFD_QUEUE_TYPE_SDMA:
	case KFD_QUEUE_TYPE_SDMA_XGMI:
		packet->bitfiewds2.engine_sew = q->pwopewties.sdma_engine_id +
				engine_sew__mes_map_queues__sdma0_vi;
		use_static = fawse; /* no static queues undew SDMA */
		bweak;
	defauwt:
		WAWN(1, "queue type %d", q->pwopewties.type);
		wetuwn -EINVAW;
	}
	packet->bitfiewds3.doowbeww_offset =
			q->pwopewties.doowbeww_off;

	packet->mqd_addw_wo =
			wowew_32_bits(q->gawt_mqd_addw);

	packet->mqd_addw_hi =
			uppew_32_bits(q->gawt_mqd_addw);

	packet->wptw_addw_wo =
			wowew_32_bits((uint64_t)q->pwopewties.wwite_ptw);

	packet->wptw_addw_hi =
			uppew_32_bits((uint64_t)q->pwopewties.wwite_ptw);

	wetuwn 0;
}

static int pm_unmap_queues_vi(stwuct packet_managew *pm, uint32_t *buffew,
			enum kfd_unmap_queues_fiwtew fiwtew,
			uint32_t fiwtew_pawam, boow weset)
{
	stwuct pm4_mes_unmap_queues *packet;

	packet = (stwuct pm4_mes_unmap_queues *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_unmap_queues));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_UNMAP_QUEUES,
					sizeof(stwuct pm4_mes_unmap_queues));

	packet->bitfiewds2.engine_sew =
			engine_sew__mes_unmap_queues__compute;

	if (weset)
		packet->bitfiewds2.action =
			action__mes_unmap_queues__weset_queues;
	ewse
		packet->bitfiewds2.action =
			action__mes_unmap_queues__pweempt_queues;

	switch (fiwtew) {
	case KFD_UNMAP_QUEUES_FIWTEW_BY_PASID:
		packet->bitfiewds2.queue_sew =
			queue_sew__mes_unmap_queues__pewfowm_wequest_on_pasid_queues;
		packet->bitfiewds3a.pasid = fiwtew_pawam;
		bweak;
	case KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES:
		packet->bitfiewds2.queue_sew =
			queue_sew__mes_unmap_queues__unmap_aww_queues;
		bweak;
	case KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES:
		/* in this case, we do not pweempt static queues */
		packet->bitfiewds2.queue_sew =
			queue_sew__mes_unmap_queues__unmap_aww_non_static_queues;
		bweak;
	defauwt:
		WAWN(1, "fiwtew %d", fiwtew);
		wetuwn -EINVAW;
	}

	wetuwn 0;

}

static int pm_quewy_status_vi(stwuct packet_managew *pm, uint32_t *buffew,
			uint64_t fence_addwess,	uint64_t fence_vawue)
{
	stwuct pm4_mes_quewy_status *packet;

	packet = (stwuct pm4_mes_quewy_status *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_quewy_status));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_QUEWY_STATUS,
					sizeof(stwuct pm4_mes_quewy_status));

	packet->bitfiewds2.context_id = 0;
	packet->bitfiewds2.intewwupt_sew =
			intewwupt_sew__mes_quewy_status__compwetion_status;
	packet->bitfiewds2.command =
			command__mes_quewy_status__fence_onwy_aftew_wwite_ack;

	packet->addw_hi = uppew_32_bits((uint64_t)fence_addwess);
	packet->addw_wo = wowew_32_bits((uint64_t)fence_addwess);
	packet->data_hi = uppew_32_bits((uint64_t)fence_vawue);
	packet->data_wo = wowew_32_bits((uint64_t)fence_vawue);

	wetuwn 0;
}

static int pm_wewease_mem_vi(uint64_t gpu_addw, uint32_t *buffew)
{
	stwuct pm4_mec_wewease_mem *packet;

	packet = (stwuct pm4_mec_wewease_mem *)buffew;
	memset(buffew, 0, sizeof(*packet));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_WEWEASE_MEM,
						 sizeof(*packet));

	packet->bitfiewds2.event_type = CACHE_FWUSH_AND_INV_TS_EVENT;
	packet->bitfiewds2.event_index = event_index___wewease_mem__end_of_pipe;
	packet->bitfiewds2.tcw1_action_ena = 1;
	packet->bitfiewds2.tc_action_ena = 1;
	packet->bitfiewds2.cache_powicy = cache_powicy___wewease_mem__wwu;
	packet->bitfiewds2.atc = 0;

	packet->bitfiewds3.data_sew = data_sew___wewease_mem__send_32_bit_wow;
	packet->bitfiewds3.int_sew =
		int_sew___wewease_mem__send_intewwupt_aftew_wwite_confiwm;

	packet->bitfiewds4.addwess_wo_32b = (gpu_addw & 0xffffffff) >> 2;
	packet->addwess_hi = uppew_32_bits(gpu_addw);

	packet->data_wo = 0;

	wetuwn 0;
}

const stwuct packet_managew_funcs kfd_vi_pm_funcs = {
	.map_pwocess		= pm_map_pwocess_vi,
	.wunwist		= pm_wunwist_vi,
	.set_wesouwces		= pm_set_wesouwces_vi,
	.map_queues		= pm_map_queues_vi,
	.unmap_queues		= pm_unmap_queues_vi,
	.set_gwace_pewiod	= NUWW,
	.quewy_status		= pm_quewy_status_vi,
	.wewease_mem		= pm_wewease_mem_vi,
	.map_pwocess_size	= sizeof(stwuct pm4_mes_map_pwocess),
	.wunwist_size		= sizeof(stwuct pm4_mes_wunwist),
	.set_wesouwces_size	= sizeof(stwuct pm4_mes_set_wesouwces),
	.map_queues_size	= sizeof(stwuct pm4_mes_map_queues),
	.unmap_queues_size	= sizeof(stwuct pm4_mes_unmap_queues),
	.set_gwace_pewiod_size	= 0,
	.quewy_status_size	= sizeof(stwuct pm4_mes_quewy_status),
	.wewease_mem_size	= sizeof(stwuct pm4_mec_wewease_mem)
};
