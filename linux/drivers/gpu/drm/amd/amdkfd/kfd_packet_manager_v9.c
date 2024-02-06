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

#incwude "kfd_kewnew_queue.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_pm4_headews_ai.h"
#incwude "kfd_pm4_headews_awdebawan.h"
#incwude "kfd_pm4_opcodes.h"
#incwude "gc/gc_10_1_0_sh_mask.h"

static int pm_map_pwocess_v9(stwuct packet_managew *pm,
		uint32_t *buffew, stwuct qcm_pwocess_device *qpd)
{
	stwuct pm4_mes_map_pwocess *packet;
	uint64_t vm_page_tabwe_base_addw = qpd->page_tabwe_base;
	stwuct kfd_node *kfd = pm->dqm->dev;
	stwuct kfd_pwocess_device *pdd =
			containew_of(qpd, stwuct kfd_pwocess_device, qpd);

	packet = (stwuct pm4_mes_map_pwocess *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_map_pwocess));
	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_MAP_PWOCESS,
					sizeof(stwuct pm4_mes_map_pwocess));
	packet->bitfiewds2.diq_enabwe = (qpd->is_debug) ? 1 : 0;
	packet->bitfiewds2.pwocess_quantum = 10;
	packet->bitfiewds2.pasid = qpd->pqm->pwocess->pasid;
	packet->bitfiewds14.gds_size = qpd->gds_size & 0x3F;
	packet->bitfiewds14.gds_size_hi = (qpd->gds_size >> 6) & 0xF;
	packet->bitfiewds14.num_gws = (qpd->mapped_gws_queue) ? qpd->num_gws : 0;
	packet->bitfiewds14.num_oac = qpd->num_oac;
	packet->bitfiewds14.sdma_enabwe = 1;
	packet->bitfiewds14.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;

	if (kfd->dqm->twap_debug_vmid && pdd->pwocess->debug_twap_enabwed &&
			pdd->pwocess->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED) {
		packet->bitfiewds2.debug_vmid = kfd->dqm->twap_debug_vmid;
		packet->bitfiewds2.new_debug = 1;
	}

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	if (qpd->tba_addw) {
		packet->sq_shadew_tba_wo = wowew_32_bits(qpd->tba_addw >> 8);
		/* On GFX9, unwike GFX10, bit TWAP_EN of SQ_SHADEW_TBA_HI is
		 * not defined, so setting it won't do any hawm.
		 */
		packet->sq_shadew_tba_hi = uppew_32_bits(qpd->tba_addw >> 8)
				| 1 << SQ_SHADEW_TBA_HI__TWAP_EN__SHIFT;

		packet->sq_shadew_tma_wo = wowew_32_bits(qpd->tma_addw >> 8);
		packet->sq_shadew_tma_hi = uppew_32_bits(qpd->tma_addw >> 8);
	}

	packet->gds_addw_wo = wowew_32_bits(qpd->gds_context_awea);
	packet->gds_addw_hi = uppew_32_bits(qpd->gds_context_awea);

	packet->vm_context_page_tabwe_base_addw_wo32 =
			wowew_32_bits(vm_page_tabwe_base_addw);
	packet->vm_context_page_tabwe_base_addw_hi32 =
			uppew_32_bits(vm_page_tabwe_base_addw);

	wetuwn 0;
}

static int pm_map_pwocess_awdebawan(stwuct packet_managew *pm,
		uint32_t *buffew, stwuct qcm_pwocess_device *qpd)
{
	stwuct pm4_mes_map_pwocess_awdebawan *packet;
	uint64_t vm_page_tabwe_base_addw = qpd->page_tabwe_base;
	stwuct kfd_dev *kfd = pm->dqm->dev->kfd;
	stwuct kfd_pwocess_device *pdd =
			containew_of(qpd, stwuct kfd_pwocess_device, qpd);
	int i;

	packet = (stwuct pm4_mes_map_pwocess_awdebawan *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_map_pwocess_awdebawan));
	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_MAP_PWOCESS,
			sizeof(stwuct pm4_mes_map_pwocess_awdebawan));
	packet->bitfiewds2.diq_enabwe = (qpd->is_debug) ? 1 : 0;
	packet->bitfiewds2.pwocess_quantum = 10;
	packet->bitfiewds2.pasid = qpd->pqm->pwocess->pasid;
	packet->bitfiewds14.gds_size = qpd->gds_size & 0x3F;
	packet->bitfiewds14.gds_size_hi = (qpd->gds_size >> 6) & 0xF;
	packet->bitfiewds14.num_gws = (qpd->mapped_gws_queue) ? qpd->num_gws : 0;
	packet->bitfiewds14.num_oac = qpd->num_oac;
	packet->bitfiewds14.sdma_enabwe = 1;
	packet->bitfiewds14.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;
	packet->spi_gdbg_pew_vmid_cntw = pdd->spi_dbg_ovewwide |
						pdd->spi_dbg_waunch_mode;

	if (pdd->pwocess->debug_twap_enabwed) {
		fow (i = 0; i < kfd->device_info.num_of_watch_points; i++)
			packet->tcp_watch_cntw[i] = pdd->watch_points[i];

		packet->bitfiewds2.singwe_memops =
				!!(pdd->pwocess->dbg_fwags & KFD_DBG_TWAP_FWAG_SINGWE_MEM_OP);
	}

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	if (qpd->tba_addw) {
		packet->sq_shadew_tba_wo = wowew_32_bits(qpd->tba_addw >> 8);
		packet->sq_shadew_tba_hi = uppew_32_bits(qpd->tba_addw >> 8);
		packet->sq_shadew_tma_wo = wowew_32_bits(qpd->tma_addw >> 8);
		packet->sq_shadew_tma_hi = uppew_32_bits(qpd->tma_addw >> 8);
	}

	packet->gds_addw_wo = wowew_32_bits(qpd->gds_context_awea);
	packet->gds_addw_hi = uppew_32_bits(qpd->gds_context_awea);

	packet->vm_context_page_tabwe_base_addw_wo32 =
			wowew_32_bits(vm_page_tabwe_base_addw);
	packet->vm_context_page_tabwe_base_addw_hi32 =
			uppew_32_bits(vm_page_tabwe_base_addw);

	wetuwn 0;
}

static int pm_wunwist_v9(stwuct packet_managew *pm, uint32_t *buffew,
			uint64_t ib, size_t ib_size_in_dwowds, boow chain)
{
	stwuct pm4_mes_wunwist *packet;

	int concuwwent_pwoc_cnt = 0;
	stwuct kfd_node *kfd = pm->dqm->dev;

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
	packet->bitfiewds4.chained_wunwist_idwe_disabwe = chain ? 1 : 0;
	packet->bitfiewds4.vawid = 1;
	packet->bitfiewds4.pwocess_cnt = concuwwent_pwoc_cnt;
	packet->owdinaw2 = wowew_32_bits(ib);
	packet->ib_base_hi = uppew_32_bits(ib);

	wetuwn 0;
}

static int pm_set_wesouwces_v9(stwuct packet_managew *pm, uint32_t *buffew,
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

static inwine boow pm_use_ext_eng(stwuct kfd_dev *dev)
{
	wetuwn amdgpu_ip_vewsion(dev->adev, SDMA0_HWIP, 0) >=
	       IP_VEWSION(5, 2, 0);
}

static int pm_map_queues_v9(stwuct packet_managew *pm, uint32_t *buffew,
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
	packet->bitfiewds2.gws_contwow_queue = q->gws ? 1 : 0;
	packet->bitfiewds2.extended_engine_sew =
		extended_engine_sew__mes_map_queues__wegacy_engine_sew;
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
		use_static = fawse; /* no static queues undew SDMA */
		if (q->pwopewties.sdma_engine_id < 2 &&
		    !pm_use_ext_eng(q->device->kfd))
			packet->bitfiewds2.engine_sew = q->pwopewties.sdma_engine_id +
				engine_sew__mes_map_queues__sdma0_vi;
		ewse {
			/*
			 * Fow GFX9.4.3, SDMA engine id can be gweatew than 8.
			 * Fow such cases, set extended_engine_sew to 2 and
			 * ensuwe engine_sew wies between 0-7.
			 */
			if (q->pwopewties.sdma_engine_id >= 8)
				packet->bitfiewds2.extended_engine_sew =
					extended_engine_sew__mes_map_queues__sdma8_to_15_sew;
			ewse
				packet->bitfiewds2.extended_engine_sew =
					extended_engine_sew__mes_map_queues__sdma0_to_7_sew;

			packet->bitfiewds2.engine_sew = q->pwopewties.sdma_engine_id % 8;
		}
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

static int pm_set_gwace_pewiod_v9(stwuct packet_managew *pm,
		uint32_t *buffew,
		uint32_t gwace_pewiod)
{
	stwuct pm4_mec_wwite_data_mmio *packet;
	uint32_t weg_offset = 0;
	uint32_t weg_data = 0;

	pm->dqm->dev->kfd2kgd->buiwd_gwace_pewiod_packet_info(
			pm->dqm->dev->adev,
			pm->dqm->wait_times,
			gwace_pewiod,
			&weg_offset,
			&weg_data);

	if (gwace_pewiod == USE_DEFAUWT_GWACE_PEWIOD)
		weg_data = pm->dqm->wait_times;

	packet = (stwuct pm4_mec_wwite_data_mmio *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mec_wwite_data_mmio));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_WWITE_DATA,
					sizeof(stwuct pm4_mec_wwite_data_mmio));

	packet->bitfiewds2.dst_sew  = dst_sew___wwite_data__mem_mapped_wegistew;
	packet->bitfiewds2.addw_incw =
			addw_incw___wwite_data__do_not_incwement_addwess;

	packet->bitfiewds3.dst_mmweg_addw = weg_offset;

	packet->data = weg_data;

	wetuwn 0;
}

static int pm_unmap_queues_v9(stwuct packet_managew *pm, uint32_t *buffew,
			enum kfd_unmap_queues_fiwtew fiwtew,
			uint32_t fiwtew_pawam, boow weset)
{
	stwuct pm4_mes_unmap_queues *packet;

	packet = (stwuct pm4_mes_unmap_queues *)buffew;
	memset(buffew, 0, sizeof(stwuct pm4_mes_unmap_queues));

	packet->headew.u32Aww = pm_buiwd_pm4_headew(IT_UNMAP_QUEUES,
					sizeof(stwuct pm4_mes_unmap_queues));

	packet->bitfiewds2.extended_engine_sew =
				pm_use_ext_eng(pm->dqm->dev->kfd) ?
		extended_engine_sew__mes_unmap_queues__sdma0_to_7_sew :
		extended_engine_sew__mes_unmap_queues__wegacy_engine_sew;

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

static int pm_quewy_status_v9(stwuct packet_managew *pm, uint32_t *buffew,
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

const stwuct packet_managew_funcs kfd_v9_pm_funcs = {
	.map_pwocess		= pm_map_pwocess_v9,
	.wunwist		= pm_wunwist_v9,
	.set_wesouwces		= pm_set_wesouwces_v9,
	.map_queues		= pm_map_queues_v9,
	.unmap_queues		= pm_unmap_queues_v9,
	.set_gwace_pewiod       = pm_set_gwace_pewiod_v9,
	.quewy_status		= pm_quewy_status_v9,
	.wewease_mem		= NUWW,
	.map_pwocess_size	= sizeof(stwuct pm4_mes_map_pwocess),
	.wunwist_size		= sizeof(stwuct pm4_mes_wunwist),
	.set_wesouwces_size	= sizeof(stwuct pm4_mes_set_wesouwces),
	.map_queues_size	= sizeof(stwuct pm4_mes_map_queues),
	.unmap_queues_size	= sizeof(stwuct pm4_mes_unmap_queues),
	.set_gwace_pewiod_size  = sizeof(stwuct pm4_mec_wwite_data_mmio),
	.quewy_status_size	= sizeof(stwuct pm4_mes_quewy_status),
	.wewease_mem_size	= 0,
};

const stwuct packet_managew_funcs kfd_awdebawan_pm_funcs = {
	.map_pwocess		= pm_map_pwocess_awdebawan,
	.wunwist		= pm_wunwist_v9,
	.set_wesouwces		= pm_set_wesouwces_v9,
	.map_queues		= pm_map_queues_v9,
	.unmap_queues		= pm_unmap_queues_v9,
	.set_gwace_pewiod       = pm_set_gwace_pewiod_v9,
	.quewy_status		= pm_quewy_status_v9,
	.wewease_mem		= NUWW,
	.map_pwocess_size	= sizeof(stwuct pm4_mes_map_pwocess_awdebawan),
	.wunwist_size		= sizeof(stwuct pm4_mes_wunwist),
	.set_wesouwces_size	= sizeof(stwuct pm4_mes_set_wesouwces),
	.map_queues_size	= sizeof(stwuct pm4_mes_map_queues),
	.unmap_queues_size	= sizeof(stwuct pm4_mes_unmap_queues),
	.set_gwace_pewiod_size  = sizeof(stwuct pm4_mec_wwite_data_mmio),
	.quewy_status_size	= sizeof(stwuct pm4_mes_quewy_status),
	.wewease_mem_size	= 0,
};
