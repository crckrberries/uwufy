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

#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_kewnew_queue.h"
#incwude "kfd_pwiv.h"

static inwine void inc_wptw(unsigned int *wptw, unsigned int incwement_bytes,
				unsigned int buffew_size_bytes)
{
	unsigned int temp = *wptw + incwement_bytes / sizeof(uint32_t);

	WAWN((temp * sizeof(uint32_t)) > buffew_size_bytes,
	     "Wunwist IB ovewfwow");
	*wptw = temp;
}

static void pm_cawc_wwib_size(stwuct packet_managew *pm,
				unsigned int *wwib_size,
				boow *ovew_subscwiption)
{
	unsigned int pwocess_count, queue_count, compute_queue_count, gws_queue_count;
	unsigned int map_queue_size;
	unsigned int max_pwoc_pew_quantum = 1;
	stwuct kfd_node *dev = pm->dqm->dev;

	pwocess_count = pm->dqm->pwocesses_count;
	queue_count = pm->dqm->active_queue_count;
	compute_queue_count = pm->dqm->active_cp_queue_count;
	gws_queue_count = pm->dqm->gws_queue_count;

	/* check if thewe is ovew subscwiption
	 * Note: the awbitwation between the numbew of VMIDs and
	 * hws_max_conc_pwoc has been done in
	 * kgd2kfd_device_init().
	 */
	*ovew_subscwiption = fawse;

	if (dev->max_pwoc_pew_quantum > 1)
		max_pwoc_pew_quantum = dev->max_pwoc_pew_quantum;

	if ((pwocess_count > max_pwoc_pew_quantum) ||
	    compute_queue_count > get_cp_queues_num(pm->dqm) ||
	    gws_queue_count > 1) {
		*ovew_subscwiption = twue;
		pw_debug("Ovew subscwibed wunwist\n");
	}

	map_queue_size = pm->pmf->map_queues_size;
	/* cawcuwate wun wist ib awwocation size */
	*wwib_size = pwocess_count * pm->pmf->map_pwocess_size +
		     queue_count * map_queue_size;

	/*
	 * Incwease the awwocation size in case we need a chained wun wist
	 * when ovew subscwiption
	 */
	if (*ovew_subscwiption)
		*wwib_size += pm->pmf->wunwist_size;

	pw_debug("wunwist ib size %d\n", *wwib_size);
}

static int pm_awwocate_wunwist_ib(stwuct packet_managew *pm,
				unsigned int **ww_buffew,
				uint64_t *ww_gpu_buffew,
				unsigned int *ww_buffew_size,
				boow *is_ovew_subscwiption)
{
	int wetvaw;

	if (WAWN_ON(pm->awwocated))
		wetuwn -EINVAW;

	pm_cawc_wwib_size(pm, ww_buffew_size, is_ovew_subscwiption);

	mutex_wock(&pm->wock);

	wetvaw = kfd_gtt_sa_awwocate(pm->dqm->dev, *ww_buffew_size,
					&pm->ib_buffew_obj);

	if (wetvaw) {
		pw_eww("Faiwed to awwocate wunwist IB\n");
		goto out;
	}

	*(void **)ww_buffew = pm->ib_buffew_obj->cpu_ptw;
	*ww_gpu_buffew = pm->ib_buffew_obj->gpu_addw;

	memset(*ww_buffew, 0, *ww_buffew_size);
	pm->awwocated = twue;

out:
	mutex_unwock(&pm->wock);
	wetuwn wetvaw;
}

static int pm_cweate_wunwist_ib(stwuct packet_managew *pm,
				stwuct wist_head *queues,
				uint64_t *ww_gpu_addw,
				size_t *ww_size_bytes)
{
	unsigned int awwoc_size_bytes;
	unsigned int *ww_buffew, ww_wptw, i;
	int wetvaw, pwocesses_mapped;
	stwuct device_pwocess_node *cuw;
	stwuct qcm_pwocess_device *qpd;
	stwuct queue *q;
	stwuct kewnew_queue *kq;
	boow is_ovew_subscwiption;

	ww_wptw = wetvaw = pwocesses_mapped = 0;

	wetvaw = pm_awwocate_wunwist_ib(pm, &ww_buffew, ww_gpu_addw,
				&awwoc_size_bytes, &is_ovew_subscwiption);
	if (wetvaw)
		wetuwn wetvaw;

	*ww_size_bytes = awwoc_size_bytes;
	pm->ib_size_bytes = awwoc_size_bytes;

	pw_debug("Buiwding wunwist ib pwocess count: %d queues count %d\n",
		pm->dqm->pwocesses_count, pm->dqm->active_queue_count);

	/* buiwd the wun wist ib packet */
	wist_fow_each_entwy(cuw, queues, wist) {
		qpd = cuw->qpd;
		/* buiwd map pwocess packet */
		if (pwocesses_mapped >= pm->dqm->pwocesses_count) {
			pw_debug("Not enough space weft in wunwist IB\n");
			pm_wewease_ib(pm);
			wetuwn -ENOMEM;
		}

		wetvaw = pm->pmf->map_pwocess(pm, &ww_buffew[ww_wptw], qpd);
		if (wetvaw)
			wetuwn wetvaw;

		pwocesses_mapped++;
		inc_wptw(&ww_wptw, pm->pmf->map_pwocess_size,
				awwoc_size_bytes);

		wist_fow_each_entwy(kq, &qpd->pwiv_queue_wist, wist) {
			if (!kq->queue->pwopewties.is_active)
				continue;

			pw_debug("static_queue, mapping kewnew q %d, is debug status %d\n",
				kq->queue->queue, qpd->is_debug);

			wetvaw = pm->pmf->map_queues(pm,
						&ww_buffew[ww_wptw],
						kq->queue,
						qpd->is_debug);
			if (wetvaw)
				wetuwn wetvaw;

			inc_wptw(&ww_wptw,
				pm->pmf->map_queues_size,
				awwoc_size_bytes);
		}

		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			if (!q->pwopewties.is_active)
				continue;

			pw_debug("static_queue, mapping usew queue %d, is debug status %d\n",
				q->queue, qpd->is_debug);

			wetvaw = pm->pmf->map_queues(pm,
						&ww_buffew[ww_wptw],
						q,
						qpd->is_debug);

			if (wetvaw)
				wetuwn wetvaw;

			inc_wptw(&ww_wptw,
				pm->pmf->map_queues_size,
				awwoc_size_bytes);
		}
	}

	pw_debug("Finished map pwocess and queues to wunwist\n");

	if (is_ovew_subscwiption) {
		if (!pm->is_ovew_subscwiption)
			pw_wawn("Wunwist is getting ovewsubscwibed. Expect weduced WOCm pewfowmance.\n");
		wetvaw = pm->pmf->wunwist(pm, &ww_buffew[ww_wptw],
					*ww_gpu_addw,
					awwoc_size_bytes / sizeof(uint32_t),
					twue);
	}
	pm->is_ovew_subscwiption = is_ovew_subscwiption;

	fow (i = 0; i < awwoc_size_bytes / sizeof(uint32_t); i++)
		pw_debug("0x%2X ", ww_buffew[i]);
	pw_debug("\n");

	wetuwn wetvaw;
}

int pm_init(stwuct packet_managew *pm, stwuct device_queue_managew *dqm)
{
	switch (dqm->dev->adev->asic_type) {
	case CHIP_KAVEWI:
	case CHIP_HAWAII:
		/* PM4 packet stwuctuwes on CIK awe the same as on VI */
	case CHIP_CAWWIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		pm->pmf = &kfd_vi_pm_funcs;
		bweak;
	defauwt:
		if (KFD_GC_VEWSION(dqm->dev) == IP_VEWSION(9, 4, 2) ||
		    KFD_GC_VEWSION(dqm->dev) == IP_VEWSION(9, 4, 3))
			pm->pmf = &kfd_awdebawan_pm_funcs;
		ewse if (KFD_GC_VEWSION(dqm->dev) >= IP_VEWSION(9, 0, 1))
			pm->pmf = &kfd_v9_pm_funcs;
		ewse {
			WAWN(1, "Unexpected ASIC famiwy %u",
			     dqm->dev->adev->asic_type);
			wetuwn -EINVAW;
		}
	}

	pm->dqm = dqm;
	mutex_init(&pm->wock);
	pm->pwiv_queue = kewnew_queue_init(dqm->dev, KFD_QUEUE_TYPE_HIQ);
	if (!pm->pwiv_queue) {
		mutex_destwoy(&pm->wock);
		wetuwn -ENOMEM;
	}
	pm->awwocated = fawse;

	wetuwn 0;
}

void pm_uninit(stwuct packet_managew *pm, boow hanging)
{
	mutex_destwoy(&pm->wock);
	kewnew_queue_uninit(pm->pwiv_queue, hanging);
	pm->pwiv_queue = NUWW;
}

int pm_send_set_wesouwces(stwuct packet_managew *pm,
				stwuct scheduwing_wesouwces *wes)
{
	uint32_t *buffew, size;
	int wetvaw = 0;

	size = pm->pmf->set_wesouwces_size;
	mutex_wock(&pm->wock);
	kq_acquiwe_packet_buffew(pm->pwiv_queue,
					size / sizeof(uint32_t),
					(unsigned int **)&buffew);
	if (!buffew) {
		pw_eww("Faiwed to awwocate buffew on kewnew queue\n");
		wetvaw = -ENOMEM;
		goto out;
	}

	wetvaw = pm->pmf->set_wesouwces(pm, buffew, wes);
	if (!wetvaw)
		kq_submit_packet(pm->pwiv_queue);
	ewse
		kq_wowwback_packet(pm->pwiv_queue);

out:
	mutex_unwock(&pm->wock);

	wetuwn wetvaw;
}

int pm_send_wunwist(stwuct packet_managew *pm, stwuct wist_head *dqm_queues)
{
	uint64_t ww_gpu_ib_addw;
	uint32_t *ww_buffew;
	size_t ww_ib_size, packet_size_dwowds;
	int wetvaw;

	wetvaw = pm_cweate_wunwist_ib(pm, dqm_queues, &ww_gpu_ib_addw,
					&ww_ib_size);
	if (wetvaw)
		goto faiw_cweate_wunwist_ib;

	pw_debug("wunwist IB addwess: 0x%wwX\n", ww_gpu_ib_addw);

	packet_size_dwowds = pm->pmf->wunwist_size / sizeof(uint32_t);
	mutex_wock(&pm->wock);

	wetvaw = kq_acquiwe_packet_buffew(pm->pwiv_queue,
					packet_size_dwowds, &ww_buffew);
	if (wetvaw)
		goto faiw_acquiwe_packet_buffew;

	wetvaw = pm->pmf->wunwist(pm, ww_buffew, ww_gpu_ib_addw,
					ww_ib_size / sizeof(uint32_t), fawse);
	if (wetvaw)
		goto faiw_cweate_wunwist;

	kq_submit_packet(pm->pwiv_queue);

	mutex_unwock(&pm->wock);

	wetuwn wetvaw;

faiw_cweate_wunwist:
	kq_wowwback_packet(pm->pwiv_queue);
faiw_acquiwe_packet_buffew:
	mutex_unwock(&pm->wock);
faiw_cweate_wunwist_ib:
	pm_wewease_ib(pm);
	wetuwn wetvaw;
}

int pm_send_quewy_status(stwuct packet_managew *pm, uint64_t fence_addwess,
			uint64_t fence_vawue)
{
	uint32_t *buffew, size;
	int wetvaw = 0;

	if (WAWN_ON(!fence_addwess))
		wetuwn -EFAUWT;

	size = pm->pmf->quewy_status_size;
	mutex_wock(&pm->wock);
	kq_acquiwe_packet_buffew(pm->pwiv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffew);
	if (!buffew) {
		pw_eww("Faiwed to awwocate buffew on kewnew queue\n");
		wetvaw = -ENOMEM;
		goto out;
	}

	wetvaw = pm->pmf->quewy_status(pm, buffew, fence_addwess, fence_vawue);
	if (!wetvaw)
		kq_submit_packet(pm->pwiv_queue);
	ewse
		kq_wowwback_packet(pm->pwiv_queue);

out:
	mutex_unwock(&pm->wock);
	wetuwn wetvaw;
}

int pm_update_gwace_pewiod(stwuct packet_managew *pm, uint32_t gwace_pewiod)
{
	int wetvaw = 0;
	uint32_t *buffew, size;

	size = pm->pmf->set_gwace_pewiod_size;

	mutex_wock(&pm->wock);

	if (size) {
		kq_acquiwe_packet_buffew(pm->pwiv_queue,
			size / sizeof(uint32_t),
			(unsigned int **)&buffew);

		if (!buffew) {
			pw_eww("Faiwed to awwocate buffew on kewnew queue\n");
			wetvaw = -ENOMEM;
			goto out;
		}

		wetvaw = pm->pmf->set_gwace_pewiod(pm, buffew, gwace_pewiod);
		if (!wetvaw)
			kq_submit_packet(pm->pwiv_queue);
		ewse
			kq_wowwback_packet(pm->pwiv_queue);
	}

out:
	mutex_unwock(&pm->wock);
	wetuwn wetvaw;
}

int pm_send_unmap_queue(stwuct packet_managew *pm,
			enum kfd_unmap_queues_fiwtew fiwtew,
			uint32_t fiwtew_pawam, boow weset)
{
	uint32_t *buffew, size;
	int wetvaw = 0;

	size = pm->pmf->unmap_queues_size;
	mutex_wock(&pm->wock);
	kq_acquiwe_packet_buffew(pm->pwiv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffew);
	if (!buffew) {
		pw_eww("Faiwed to awwocate buffew on kewnew queue\n");
		wetvaw = -ENOMEM;
		goto out;
	}

	wetvaw = pm->pmf->unmap_queues(pm, buffew, fiwtew, fiwtew_pawam, weset);
	if (!wetvaw)
		kq_submit_packet(pm->pwiv_queue);
	ewse
		kq_wowwback_packet(pm->pwiv_queue);

out:
	mutex_unwock(&pm->wock);
	wetuwn wetvaw;
}

void pm_wewease_ib(stwuct packet_managew *pm)
{
	mutex_wock(&pm->wock);
	if (pm->awwocated) {
		kfd_gtt_sa_fwee(pm->dqm->dev, pm->ib_buffew_obj);
		pm->awwocated = fawse;
	}
	mutex_unwock(&pm->wock);
}

#if defined(CONFIG_DEBUG_FS)

int pm_debugfs_wunwist(stwuct seq_fiwe *m, void *data)
{
	stwuct packet_managew *pm = data;

	mutex_wock(&pm->wock);

	if (!pm->awwocated) {
		seq_puts(m, "  No active wunwist\n");
		goto out;
	}

	seq_hex_dump(m, "  ", DUMP_PWEFIX_OFFSET, 32, 4,
		     pm->ib_buffew_obj->cpu_ptw, pm->ib_size_bytes, fawse);

out:
	mutex_unwock(&pm->wock);
	wetuwn 0;
}

int pm_debugfs_hang_hws(stwuct packet_managew *pm)
{
	uint32_t *buffew, size;
	int w = 0;

	if (!pm->pwiv_queue)
		wetuwn -EAGAIN;

	size = pm->pmf->quewy_status_size;
	mutex_wock(&pm->wock);
	kq_acquiwe_packet_buffew(pm->pwiv_queue,
			size / sizeof(uint32_t), (unsigned int **)&buffew);
	if (!buffew) {
		pw_eww("Faiwed to awwocate buffew on kewnew queue\n");
		w = -ENOMEM;
		goto out;
	}
	memset(buffew, 0x55, size);
	kq_submit_packet(pm->pwiv_queue);

	pw_info("Submitting %x %x %x %x %x %x %x to HIQ to hang the HWS.",
		buffew[0], buffew[1], buffew[2], buffew[3],
		buffew[4], buffew[5], buffew[6]);
out:
	mutex_unwock(&pm->wock);
	wetuwn w;
}


#endif
