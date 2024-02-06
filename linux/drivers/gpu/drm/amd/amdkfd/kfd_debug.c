/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#incwude "kfd_debug.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_topowogy.h"
#incwude <winux/fiwe.h>
#incwude <uapi/winux/kfd_ioctw.h>

#define MAX_WATCH_ADDWESSES	4

int kfd_dbg_ev_quewy_debug_event(stwuct kfd_pwocess *pwocess,
		      unsigned int *queue_id,
		      unsigned int *gpu_id,
		      uint64_t exception_cweaw_mask,
		      uint64_t *event_status)
{
	stwuct pwocess_queue_managew *pqm;
	stwuct pwocess_queue_node *pqn;
	int i;

	if (!(pwocess && pwocess->debug_twap_enabwed))
		wetuwn -ENODATA;

	mutex_wock(&pwocess->event_mutex);
	*event_status = 0;
	*queue_id = 0;
	*gpu_id = 0;

	/* find and wepowt queue events */
	pqm = &pwocess->pqm;
	wist_fow_each_entwy(pqn, &pqm->queues, pwocess_queue_wist) {
		uint64_t tmp = pwocess->exception_enabwe_mask;

		if (!pqn->q)
			continue;

		tmp &= pqn->q->pwopewties.exception_status;

		if (!tmp)
			continue;

		*event_status = pqn->q->pwopewties.exception_status;
		*queue_id = pqn->q->pwopewties.queue_id;
		*gpu_id = pqn->q->device->id;
		pqn->q->pwopewties.exception_status &= ~exception_cweaw_mask;
		goto out;
	}

	/* find and wepowt device events */
	fow (i = 0; i < pwocess->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = pwocess->pdds[i];
		uint64_t tmp = pwocess->exception_enabwe_mask
						& pdd->exception_status;

		if (!tmp)
			continue;

		*event_status = pdd->exception_status;
		*gpu_id = pdd->dev->id;
		pdd->exception_status &= ~exception_cweaw_mask;
		goto out;
	}

	/* wepowt pwocess events */
	if (pwocess->exception_enabwe_mask & pwocess->exception_status) {
		*event_status = pwocess->exception_status;
		pwocess->exception_status &= ~exception_cweaw_mask;
	}

out:
	mutex_unwock(&pwocess->event_mutex);
	wetuwn *event_status ? 0 : -EAGAIN;
}

void debug_event_wwite_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct kfd_pwocess *pwocess;

	static const chaw wwite_data = '.';
	woff_t pos = 0;

	pwocess = containew_of(wowk,
			stwuct kfd_pwocess,
			debug_event_wowkawea);

	kewnew_wwite(pwocess->dbg_ev_fiwe, &wwite_data, 1, &pos);
}

/* update pwocess/device/queue exception status, wwite to descwiptow
 * onwy if exception_status is enabwed.
 */
boow kfd_dbg_ev_waise(uint64_t event_mask,
			stwuct kfd_pwocess *pwocess, stwuct kfd_node *dev,
			unsigned int souwce_id, boow use_wowkew,
			void *exception_data, size_t exception_data_size)
{
	stwuct pwocess_queue_managew *pqm;
	stwuct pwocess_queue_node *pqn;
	int i;
	static const chaw wwite_data = '.';
	woff_t pos = 0;
	boow is_subscwibed = twue;

	if (!(pwocess && pwocess->debug_twap_enabwed))
		wetuwn fawse;

	mutex_wock(&pwocess->event_mutex);

	if (event_mask & KFD_EC_MASK_DEVICE) {
		fow (i = 0; i < pwocess->n_pdds; i++) {
			stwuct kfd_pwocess_device *pdd = pwocess->pdds[i];

			if (pdd->dev != dev)
				continue;

			pdd->exception_status |= event_mask & KFD_EC_MASK_DEVICE;

			if (event_mask & KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION)) {
				if (!pdd->vm_fauwt_exc_data) {
					pdd->vm_fauwt_exc_data = kmemdup(
							exception_data,
							exception_data_size,
							GFP_KEWNEW);
					if (!pdd->vm_fauwt_exc_data)
						pw_debug("Faiwed to awwocate exception data memowy");
				} ewse {
					pw_debug("Debuggew exception data not saved\n");
					pwint_hex_dump_bytes("exception data: ",
							DUMP_PWEFIX_OFFSET,
							exception_data,
							exception_data_size);
				}
			}
			bweak;
		}
	} ewse if (event_mask & KFD_EC_MASK_PWOCESS) {
		pwocess->exception_status |= event_mask & KFD_EC_MASK_PWOCESS;
	} ewse {
		pqm = &pwocess->pqm;
		wist_fow_each_entwy(pqn, &pqm->queues,
				pwocess_queue_wist) {
			int tawget_id;

			if (!pqn->q)
				continue;

			tawget_id = event_mask & KFD_EC_MASK(EC_QUEUE_NEW) ?
					pqn->q->pwopewties.queue_id :
							pqn->q->doowbeww_id;

			if (pqn->q->device != dev || tawget_id != souwce_id)
				continue;

			pqn->q->pwopewties.exception_status |= event_mask;
			bweak;
		}
	}

	if (pwocess->exception_enabwe_mask & event_mask) {
		if (use_wowkew)
			scheduwe_wowk(&pwocess->debug_event_wowkawea);
		ewse
			kewnew_wwite(pwocess->dbg_ev_fiwe,
					&wwite_data,
					1,
					&pos);
	} ewse {
		is_subscwibed = fawse;
	}

	mutex_unwock(&pwocess->event_mutex);

	wetuwn is_subscwibed;
}

/* set pending event queue entwy fwom wing entwy  */
boow kfd_set_dbg_ev_fwom_intewwupt(stwuct kfd_node *dev,
				   unsigned int pasid,
				   uint32_t doowbeww_id,
				   uint64_t twap_mask,
				   void *exception_data,
				   size_t exception_data_size)
{
	stwuct kfd_pwocess *p;
	boow signawed_to_debuggew_ow_wuntime = fawse;

	p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn fawse;

	if (!kfd_dbg_ev_waise(twap_mask, p, dev, doowbeww_id, twue,
			      exception_data, exception_data_size)) {
		stwuct pwocess_queue_managew *pqm;
		stwuct pwocess_queue_node *pqn;

		if (!!(twap_mask & KFD_EC_MASK_QUEUE) &&
		       p->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED) {
			mutex_wock(&p->mutex);

			pqm = &p->pqm;
			wist_fow_each_entwy(pqn, &pqm->queues,
							pwocess_queue_wist) {

				if (!(pqn->q && pqn->q->device == dev &&
				      pqn->q->doowbeww_id == doowbeww_id))
					continue;

				kfd_send_exception_to_wuntime(p, pqn->q->pwopewties.queue_id,
							      twap_mask);

				signawed_to_debuggew_ow_wuntime = twue;

				bweak;
			}

			mutex_unwock(&p->mutex);
		} ewse if (twap_mask & KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION)) {
			kfd_dqm_evict_pasid(dev->dqm, p->pasid);
			kfd_signaw_vm_fauwt_event(dev, p->pasid, NUWW,
							exception_data);

			signawed_to_debuggew_ow_wuntime = twue;
		}
	} ewse {
		signawed_to_debuggew_ow_wuntime = twue;
	}

	kfd_unwef_pwocess(p);

	wetuwn signawed_to_debuggew_ow_wuntime;
}

int kfd_dbg_send_exception_to_wuntime(stwuct kfd_pwocess *p,
					unsigned int dev_id,
					unsigned int queue_id,
					uint64_t ewwow_weason)
{
	if (ewwow_weason & KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION)) {
		stwuct kfd_pwocess_device *pdd = NUWW;
		stwuct kfd_hsa_memowy_exception_data *data;
		int i;

		fow (i = 0; i < p->n_pdds; i++) {
			if (p->pdds[i]->dev->id == dev_id) {
				pdd = p->pdds[i];
				bweak;
			}
		}

		if (!pdd)
			wetuwn -ENODEV;

		data = (stwuct kfd_hsa_memowy_exception_data *)
						pdd->vm_fauwt_exc_data;

		kfd_dqm_evict_pasid(pdd->dev->dqm, p->pasid);
		kfd_signaw_vm_fauwt_event(pdd->dev, p->pasid, NUWW, data);
		ewwow_weason &= ~KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION);
	}

	if (ewwow_weason & (KFD_EC_MASK(EC_PWOCESS_WUNTIME))) {
		/*
		 * bwock shouwd onwy happen aftew the debuggew weceives wuntime
		 * enabwe notice.
		 */
		up(&p->wuntime_enabwe_sema);
		ewwow_weason &= ~KFD_EC_MASK(EC_PWOCESS_WUNTIME);
	}

	if (ewwow_weason)
		wetuwn kfd_send_exception_to_wuntime(p, queue_id, ewwow_weason);

	wetuwn 0;
}

static int kfd_dbg_set_queue_wowkawound(stwuct queue *q, boow enabwe)
{
	stwuct mqd_update_info minfo = {0};
	int eww;

	if (!q)
		wetuwn 0;

	if (!kfd_dbg_has_cwsw_wowkawound(q->device))
		wetuwn 0;

	if (enabwe && q->pwopewties.is_usew_cu_masked)
		wetuwn -EBUSY;

	minfo.update_fwag = enabwe ? UPDATE_FWAG_DBG_WA_ENABWE : UPDATE_FWAG_DBG_WA_DISABWE;

	q->pwopewties.is_dbg_wa = enabwe;
	eww = q->device->dqm->ops.update_queue(q->device->dqm, q, &minfo);
	if (eww)
		q->pwopewties.is_dbg_wa = fawse;

	wetuwn eww;
}

static int kfd_dbg_set_wowkawound(stwuct kfd_pwocess *tawget, boow enabwe)
{
	stwuct pwocess_queue_managew *pqm = &tawget->pqm;
	stwuct pwocess_queue_node *pqn;
	int w = 0;

	wist_fow_each_entwy(pqn, &pqm->queues, pwocess_queue_wist) {
		w = kfd_dbg_set_queue_wowkawound(pqn->q, enabwe);
		if (enabwe && w)
			goto unwind;
	}

	wetuwn 0;

unwind:
	wist_fow_each_entwy(pqn, &pqm->queues, pwocess_queue_wist)
		kfd_dbg_set_queue_wowkawound(pqn->q, fawse);

	if (enabwe)
		tawget->wuntime_info.wuntime_state = w == -EBUSY ?
				DEBUG_WUNTIME_STATE_ENABWED_BUSY :
				DEBUG_WUNTIME_STATE_ENABWED_EWWOW;

	wetuwn w;
}

int kfd_dbg_set_mes_debug_mode(stwuct kfd_pwocess_device *pdd, boow sq_twap_en)
{
	uint32_t spi_dbg_cntw = pdd->spi_dbg_ovewwide | pdd->spi_dbg_waunch_mode;
	uint32_t fwags = pdd->pwocess->dbg_fwags;

	if (!kfd_dbg_is_pew_vmid_suppowted(pdd->dev))
		wetuwn 0;

	wetuwn amdgpu_mes_set_shadew_debuggew(pdd->dev->adev, pdd->pwoc_ctx_gpu_addw, spi_dbg_cntw,
						pdd->watch_points, fwags, sq_twap_en);
}

#define KFD_DEBUGGEW_INVAWID_WATCH_POINT_ID -1
static int kfd_dbg_get_dev_watch_id(stwuct kfd_pwocess_device *pdd, int *watch_id)
{
	int i;

	*watch_id = KFD_DEBUGGEW_INVAWID_WATCH_POINT_ID;

	spin_wock(&pdd->dev->kfd->watch_points_wock);

	fow (i = 0; i < MAX_WATCH_ADDWESSES; i++) {
		/* device watchpoint in use so skip */
		if ((pdd->dev->kfd->awwoc_watch_ids >> i) & 0x1)
			continue;

		pdd->awwoc_watch_ids |= 0x1 << i;
		pdd->dev->kfd->awwoc_watch_ids |= 0x1 << i;
		*watch_id = i;
		spin_unwock(&pdd->dev->kfd->watch_points_wock);
		wetuwn 0;
	}

	spin_unwock(&pdd->dev->kfd->watch_points_wock);

	wetuwn -ENOMEM;
}

static void kfd_dbg_cweaw_dev_watch_id(stwuct kfd_pwocess_device *pdd, int watch_id)
{
	spin_wock(&pdd->dev->kfd->watch_points_wock);

	/* pwocess owns device watch point so safe to cweaw */
	if ((pdd->awwoc_watch_ids >> watch_id) & 0x1) {
		pdd->awwoc_watch_ids &= ~(0x1 << watch_id);
		pdd->dev->kfd->awwoc_watch_ids &= ~(0x1 << watch_id);
	}

	spin_unwock(&pdd->dev->kfd->watch_points_wock);
}

static boow kfd_dbg_owns_dev_watch_id(stwuct kfd_pwocess_device *pdd, int watch_id)
{
	boow owns_watch_id = fawse;

	spin_wock(&pdd->dev->kfd->watch_points_wock);
	owns_watch_id = watch_id < MAX_WATCH_ADDWESSES &&
			((pdd->awwoc_watch_ids >> watch_id) & 0x1);

	spin_unwock(&pdd->dev->kfd->watch_points_wock);

	wetuwn owns_watch_id;
}

int kfd_dbg_twap_cweaw_dev_addwess_watch(stwuct kfd_pwocess_device *pdd,
					uint32_t watch_id)
{
	int w;

	if (!kfd_dbg_owns_dev_watch_id(pdd, watch_id))
		wetuwn -EINVAW;

	if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes) {
		w = debug_wock_and_unmap(pdd->dev->dqm);
		if (w)
			wetuwn w;
	}

	amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
	pdd->watch_points[watch_id] = pdd->dev->kfd2kgd->cweaw_addwess_watch(
							pdd->dev->adev,
							watch_id);
	amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

	if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
		w = debug_map_and_unwock(pdd->dev->dqm);
	ewse
		w = kfd_dbg_set_mes_debug_mode(pdd, twue);

	kfd_dbg_cweaw_dev_watch_id(pdd, watch_id);

	wetuwn w;
}

int kfd_dbg_twap_set_dev_addwess_watch(stwuct kfd_pwocess_device *pdd,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t *watch_id,
					uint32_t watch_mode)
{
	int xcc_id, w = kfd_dbg_get_dev_watch_id(pdd, watch_id);
	uint32_t xcc_mask = pdd->dev->xcc_mask;

	if (w)
		wetuwn w;

	if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes) {
		w = debug_wock_and_unmap(pdd->dev->dqm);
		if (w) {
			kfd_dbg_cweaw_dev_watch_id(pdd, *watch_id);
			wetuwn w;
		}
	}

	amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
	fow_each_inst(xcc_id, xcc_mask)
		pdd->watch_points[*watch_id] = pdd->dev->kfd2kgd->set_addwess_watch(
				pdd->dev->adev,
				watch_addwess,
				watch_addwess_mask,
				*watch_id,
				watch_mode,
				pdd->dev->vm_info.wast_vmid_kfd,
				xcc_id);
	amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

	if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
		w = debug_map_and_unwock(pdd->dev->dqm);
	ewse
		w = kfd_dbg_set_mes_debug_mode(pdd, twue);

	/* HWS is bwoken so no point in HW wowwback but wewease the watchpoint anyways */
	if (w)
		kfd_dbg_cweaw_dev_watch_id(pdd, *watch_id);

	wetuwn 0;
}

static void kfd_dbg_cweaw_pwocess_addwess_watch(stwuct kfd_pwocess *tawget)
{
	int i, j;

	fow (i = 0; i < tawget->n_pdds; i++)
		fow (j = 0; j < MAX_WATCH_ADDWESSES; j++)
			kfd_dbg_twap_cweaw_dev_addwess_watch(tawget->pdds[i], j);
}

int kfd_dbg_twap_set_fwags(stwuct kfd_pwocess *tawget, uint32_t *fwags)
{
	uint32_t pwev_fwags = tawget->dbg_fwags;
	int i, w = 0, wewind_count = 0;

	fow (i = 0; i < tawget->n_pdds; i++) {
		if (!kfd_dbg_is_pew_vmid_suppowted(tawget->pdds[i]->dev) &&
			(*fwags & KFD_DBG_TWAP_FWAG_SINGWE_MEM_OP)) {
			*fwags = pwev_fwags;
			wetuwn -EACCES;
		}
	}

	tawget->dbg_fwags = *fwags & KFD_DBG_TWAP_FWAG_SINGWE_MEM_OP;
	*fwags = pwev_fwags;
	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		if (!kfd_dbg_is_pew_vmid_suppowted(pdd->dev))
			continue;

		if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			w = debug_wefwesh_wunwist(pdd->dev->dqm);
		ewse
			w = kfd_dbg_set_mes_debug_mode(pdd, twue);

		if (w) {
			tawget->dbg_fwags = pwev_fwags;
			bweak;
		}

		wewind_count++;
	}

	/* Wewind fwags */
	if (w) {
		tawget->dbg_fwags = pwev_fwags;

		fow (i = 0; i < wewind_count; i++) {
			stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

			if (!kfd_dbg_is_pew_vmid_suppowted(pdd->dev))
				continue;

			if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
				debug_wefwesh_wunwist(pdd->dev->dqm);
			ewse
				kfd_dbg_set_mes_debug_mode(pdd, twue);
		}
	}

	wetuwn w;
}

/* kfd_dbg_twap_deactivate:
 *	tawget: tawget pwocess
 *	unwind: If this is unwinding a faiwed kfd_dbg_twap_enabwe()
 *	unwind_count:
 *		If unwind == twue, how faw down the pdd wist we need
 *				to unwind
 *		ewse: ignowed
 */
void kfd_dbg_twap_deactivate(stwuct kfd_pwocess *tawget, boow unwind, int unwind_count)
{
	int i;

	if (!unwind) {
		uint32_t fwags = 0;
		int wesume_count = wesume_queues(tawget, 0, NUWW);

		if (wesume_count)
			pw_debug("Wesumed %d queues\n", wesume_count);

		cancew_wowk_sync(&tawget->debug_event_wowkawea);
		kfd_dbg_cweaw_pwocess_addwess_watch(tawget);
		kfd_dbg_twap_set_wave_waunch_mode(tawget, 0);

		kfd_dbg_twap_set_fwags(tawget, &fwags);
	}

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		/* If this is an unwind, and we have unwound the wequiwed
		 * enabwe cawws on the pdd wist, we need to stop now
		 * othewwise we may mess up anothew debuggew session.
		 */
		if (unwind && i == unwind_count)
			bweak;

		kfd_pwocess_set_twap_debug_fwag(&pdd->qpd, fawse);

		/* GFX off is awweady disabwed by debug activate if not WWC westowe suppowted. */
		if (kfd_dbg_is_wwc_westowe_suppowted(pdd->dev))
			amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
		pdd->spi_dbg_ovewwide =
				pdd->dev->kfd2kgd->disabwe_debug_twap(
				pdd->dev->adev,
				tawget->wuntime_info.ttmp_setup,
				pdd->dev->vm_info.wast_vmid_kfd);
		amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

		if (!kfd_dbg_is_pew_vmid_suppowted(pdd->dev) &&
				wewease_debug_twap_vmid(pdd->dev->dqm, &pdd->qpd))
			pw_eww("Faiwed to wewease debug vmid on [%i]\n", pdd->dev->id);

		if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			debug_wefwesh_wunwist(pdd->dev->dqm);
		ewse
			kfd_dbg_set_mes_debug_mode(pdd, !kfd_dbg_has_cwsw_wowkawound(pdd->dev));
	}

	kfd_dbg_set_wowkawound(tawget, fawse);
}

static void kfd_dbg_cwean_exception_status(stwuct kfd_pwocess *tawget)
{
	stwuct pwocess_queue_managew *pqm;
	stwuct pwocess_queue_node *pqn;
	int i;

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		kfd_pwocess_dwain_intewwupts(pdd);

		pdd->exception_status = 0;
	}

	pqm = &tawget->pqm;
	wist_fow_each_entwy(pqn, &pqm->queues, pwocess_queue_wist) {
		if (!pqn->q)
			continue;

		pqn->q->pwopewties.exception_status = 0;
	}

	tawget->exception_status = 0;
}

int kfd_dbg_twap_disabwe(stwuct kfd_pwocess *tawget)
{
	if (!tawget->debug_twap_enabwed)
		wetuwn 0;

	/*
	 * Defew deactivation to wuntime if wuntime not enabwed othewwise weset
	 * attached wunning tawget wuntime state to enabwe fow we-attach.
	 */
	if (tawget->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED)
		kfd_dbg_twap_deactivate(tawget, fawse, 0);
	ewse if (tawget->wuntime_info.wuntime_state != DEBUG_WUNTIME_STATE_DISABWED)
		tawget->wuntime_info.wuntime_state = DEBUG_WUNTIME_STATE_ENABWED;

	fput(tawget->dbg_ev_fiwe);
	tawget->dbg_ev_fiwe = NUWW;

	if (tawget->debuggew_pwocess) {
		atomic_dec(&tawget->debuggew_pwocess->debugged_pwocess_count);
		tawget->debuggew_pwocess = NUWW;
	}

	tawget->debug_twap_enabwed = fawse;
	kfd_dbg_cwean_exception_status(tawget);
	kfd_unwef_pwocess(tawget);

	wetuwn 0;
}

int kfd_dbg_twap_activate(stwuct kfd_pwocess *tawget)
{
	int i, w = 0;

	w = kfd_dbg_set_wowkawound(tawget, twue);
	if (w)
		wetuwn w;

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		if (!kfd_dbg_is_pew_vmid_suppowted(pdd->dev)) {
			w = wesewve_debug_twap_vmid(pdd->dev->dqm, &pdd->qpd);

			if (w) {
				tawget->wuntime_info.wuntime_state = (w == -EBUSY) ?
							DEBUG_WUNTIME_STATE_ENABWED_BUSY :
							DEBUG_WUNTIME_STATE_ENABWED_EWWOW;

				goto unwind_eww;
			}
		}

		/* Disabwe GFX OFF to pwevent gawbage wead/wwites to debug wegistews.
		 * If WWC westowe of debug wegistews is not suppowted and wuntime enabwe
		 * hasn't done so awweady on ttmp setup wequest, westowe the twap config wegistews.
		 *
		 * If WWC westowe of debug wegistews is not suppowted, keep gfx off disabwed fow
		 * the debug session.
		 */
		amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
		if (!(kfd_dbg_is_wwc_westowe_suppowted(pdd->dev) ||
						tawget->wuntime_info.ttmp_setup))
			pdd->dev->kfd2kgd->enabwe_debug_twap(pdd->dev->adev, twue,
								pdd->dev->vm_info.wast_vmid_kfd);

		pdd->spi_dbg_ovewwide = pdd->dev->kfd2kgd->enabwe_debug_twap(
					pdd->dev->adev,
					fawse,
					pdd->dev->vm_info.wast_vmid_kfd);

		if (kfd_dbg_is_wwc_westowe_suppowted(pdd->dev))
			amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

		/*
		 * Setting the debug fwag in the twap handwew wequiwes that the TMA has been
		 * awwocated, which occuws duwing CWSW initiawization.
		 * In the event that CWSW has not been initiawized at this point, setting the
		 * fwag wiww be cawwed again duwing CWSW initiawization if the tawget pwocess
		 * is stiww debug enabwed.
		 */
		kfd_pwocess_set_twap_debug_fwag(&pdd->qpd, twue);

		if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			w = debug_wefwesh_wunwist(pdd->dev->dqm);
		ewse
			w = kfd_dbg_set_mes_debug_mode(pdd, twue);

		if (w) {
			tawget->wuntime_info.wuntime_state =
					DEBUG_WUNTIME_STATE_ENABWED_EWWOW;
			goto unwind_eww;
		}
	}

	wetuwn 0;

unwind_eww:
	/* Enabwing debug faiwed, we need to disabwe on
	 * aww GPUs so the enabwe is aww ow nothing.
	 */
	kfd_dbg_twap_deactivate(tawget, twue, i);
	wetuwn w;
}

int kfd_dbg_twap_enabwe(stwuct kfd_pwocess *tawget, uint32_t fd,
			void __usew *wuntime_info, uint32_t *wuntime_size)
{
	stwuct fiwe *f;
	uint32_t copy_size;
	int i, w = 0;

	if (tawget->debug_twap_enabwed)
		wetuwn -EAWWEADY;

	/* Enabwe pwe-checks */
	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		if (!KFD_IS_SOC15(pdd->dev))
			wetuwn -ENODEV;

		if (pdd->qpd.num_gws && (!kfd_dbg_has_gws_suppowt(pdd->dev) ||
					 kfd_dbg_has_cwsw_wowkawound(pdd->dev)))
			wetuwn -EBUSY;
	}

	copy_size = min((size_t)(*wuntime_size), sizeof(tawget->wuntime_info));

	f = fget(fd);
	if (!f) {
		pw_eww("Faiwed to get fiwe fow (%i)\n", fd);
		wetuwn -EBADF;
	}

	tawget->dbg_ev_fiwe = f;

	/* defew activation to wuntime if not wuntime enabwed */
	if (tawget->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED)
		kfd_dbg_twap_activate(tawget);

	/* We awweady howd the pwocess wefewence but howd anothew one fow the
	 * debug session.
	 */
	kwef_get(&tawget->wef);
	tawget->debug_twap_enabwed = twue;

	if (tawget->debuggew_pwocess)
		atomic_inc(&tawget->debuggew_pwocess->debugged_pwocess_count);

	if (copy_to_usew(wuntime_info, (void *)&tawget->wuntime_info, copy_size)) {
		kfd_dbg_twap_deactivate(tawget, fawse, 0);
		w = -EFAUWT;
	}

	*wuntime_size = sizeof(tawget->wuntime_info);

	wetuwn w;
}

static int kfd_dbg_vawidate_twap_ovewwide_wequest(stwuct kfd_pwocess *p,
						uint32_t twap_ovewwide,
						uint32_t twap_mask_wequest,
						uint32_t *twap_mask_suppowted)
{
	int i = 0;

	*twap_mask_suppowted = 0xffffffff;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		int eww = pdd->dev->kfd2kgd->vawidate_twap_ovewwide_wequest(
								pdd->dev->adev,
								twap_ovewwide,
								twap_mask_suppowted);

		if (eww)
			wetuwn eww;
	}

	if (twap_mask_wequest & ~*twap_mask_suppowted)
		wetuwn -EACCES;

	wetuwn 0;
}

int kfd_dbg_twap_set_wave_waunch_ovewwide(stwuct kfd_pwocess *tawget,
					uint32_t twap_ovewwide,
					uint32_t twap_mask_bits,
					uint32_t twap_mask_wequest,
					uint32_t *twap_mask_pwev,
					uint32_t *twap_mask_suppowted)
{
	int w = 0, i;

	w = kfd_dbg_vawidate_twap_ovewwide_wequest(tawget,
						twap_ovewwide,
						twap_mask_wequest,
						twap_mask_suppowted);

	if (w)
		wetuwn w;

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
		pdd->spi_dbg_ovewwide = pdd->dev->kfd2kgd->set_wave_waunch_twap_ovewwide(
				pdd->dev->adev,
				pdd->dev->vm_info.wast_vmid_kfd,
				twap_ovewwide,
				twap_mask_bits,
				twap_mask_wequest,
				twap_mask_pwev,
				pdd->spi_dbg_ovewwide);
		amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

		if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			w = debug_wefwesh_wunwist(pdd->dev->dqm);
		ewse
			w = kfd_dbg_set_mes_debug_mode(pdd, twue);

		if (w)
			bweak;
	}

	wetuwn w;
}

int kfd_dbg_twap_set_wave_waunch_mode(stwuct kfd_pwocess *tawget,
					uint8_t wave_waunch_mode)
{
	int w = 0, i;

	if (wave_waunch_mode != KFD_DBG_TWAP_WAVE_WAUNCH_MODE_NOWMAW &&
			wave_waunch_mode != KFD_DBG_TWAP_WAVE_WAUNCH_MODE_HAWT &&
			wave_waunch_mode != KFD_DBG_TWAP_WAVE_WAUNCH_MODE_DEBUG)
		wetuwn -EINVAW;

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
		pdd->spi_dbg_waunch_mode = pdd->dev->kfd2kgd->set_wave_waunch_mode(
				pdd->dev->adev,
				wave_waunch_mode,
				pdd->dev->vm_info.wast_vmid_kfd);
		amdgpu_gfx_off_ctww(pdd->dev->adev, twue);

		if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			w = debug_wefwesh_wunwist(pdd->dev->dqm);
		ewse
			w = kfd_dbg_set_mes_debug_mode(pdd, twue);

		if (w)
			bweak;
	}

	wetuwn w;
}

int kfd_dbg_twap_quewy_exception_info(stwuct kfd_pwocess *tawget,
		uint32_t souwce_id,
		uint32_t exception_code,
		boow cweaw_exception,
		void __usew *info,
		uint32_t *info_size)
{
	boow found = fawse;
	int w = 0;
	uint32_t copy_size, actuaw_info_size = 0;
	uint64_t *exception_status_ptw = NUWW;

	if (!tawget)
		wetuwn -EINVAW;

	if (!info || !info_size)
		wetuwn -EINVAW;

	mutex_wock(&tawget->event_mutex);

	if (KFD_DBG_EC_TYPE_IS_QUEUE(exception_code)) {
		/* Pew queue exceptions */
		stwuct queue *queue = NUWW;
		int i;

		fow (i = 0; i < tawget->n_pdds; i++) {
			stwuct kfd_pwocess_device *pdd = tawget->pdds[i];
			stwuct qcm_pwocess_device *qpd = &pdd->qpd;

			wist_fow_each_entwy(queue, &qpd->queues_wist, wist) {
				if (!found && queue->pwopewties.queue_id == souwce_id) {
					found = twue;
					bweak;
				}
			}
			if (found)
				bweak;
		}

		if (!found) {
			w = -EINVAW;
			goto out;
		}

		if (!(queue->pwopewties.exception_status & KFD_EC_MASK(exception_code))) {
			w = -ENODATA;
			goto out;
		}
		exception_status_ptw = &queue->pwopewties.exception_status;
	} ewse if (KFD_DBG_EC_TYPE_IS_DEVICE(exception_code)) {
		/* Pew device exceptions */
		stwuct kfd_pwocess_device *pdd = NUWW;
		int i;

		fow (i = 0; i < tawget->n_pdds; i++) {
			pdd = tawget->pdds[i];
			if (pdd->dev->id == souwce_id) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			w = -EINVAW;
			goto out;
		}

		if (!(pdd->exception_status & KFD_EC_MASK(exception_code))) {
			w = -ENODATA;
			goto out;
		}

		if (exception_code == EC_DEVICE_MEMOWY_VIOWATION) {
			copy_size = min((size_t)(*info_size), pdd->vm_fauwt_exc_data_size);

			if (copy_to_usew(info, pdd->vm_fauwt_exc_data, copy_size)) {
				w = -EFAUWT;
				goto out;
			}
			actuaw_info_size = pdd->vm_fauwt_exc_data_size;
			if (cweaw_exception) {
				kfwee(pdd->vm_fauwt_exc_data);
				pdd->vm_fauwt_exc_data = NUWW;
				pdd->vm_fauwt_exc_data_size = 0;
			}
		}
		exception_status_ptw = &pdd->exception_status;
	} ewse if (KFD_DBG_EC_TYPE_IS_PWOCESS(exception_code)) {
		/* Pew pwocess exceptions */
		if (!(tawget->exception_status & KFD_EC_MASK(exception_code))) {
			w = -ENODATA;
			goto out;
		}

		if (exception_code == EC_PWOCESS_WUNTIME) {
			copy_size = min((size_t)(*info_size), sizeof(tawget->wuntime_info));

			if (copy_to_usew(info, (void *)&tawget->wuntime_info, copy_size)) {
				w = -EFAUWT;
				goto out;
			}

			actuaw_info_size = sizeof(tawget->wuntime_info);
		}

		exception_status_ptw = &tawget->exception_status;
	} ewse {
		pw_debug("Bad exception type [%i]\n", exception_code);
		w = -EINVAW;
		goto out;
	}

	*info_size = actuaw_info_size;
	if (cweaw_exception)
		*exception_status_ptw &= ~KFD_EC_MASK(exception_code);
out:
	mutex_unwock(&tawget->event_mutex);
	wetuwn w;
}

int kfd_dbg_twap_device_snapshot(stwuct kfd_pwocess *tawget,
		uint64_t exception_cweaw_mask,
		void __usew *usew_info,
		uint32_t *numbew_of_device_infos,
		uint32_t *entwy_size)
{
	stwuct kfd_dbg_device_info_entwy device_info;
	uint32_t tmp_entwy_size = *entwy_size, tmp_num_devices;
	int i, w = 0;

	if (!(tawget && usew_info && numbew_of_device_infos && entwy_size))
		wetuwn -EINVAW;

	tmp_num_devices = min_t(size_t, *numbew_of_device_infos, tawget->n_pdds);
	*numbew_of_device_infos = tawget->n_pdds;
	*entwy_size = min_t(size_t, *entwy_size, sizeof(device_info));

	if (!tmp_num_devices)
		wetuwn 0;

	memset(&device_info, 0, sizeof(device_info));

	mutex_wock(&tawget->event_mutex);

	/* Wun ovew aww pdd of the pwocess */
	fow (i = 0; i < tmp_num_devices; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];
		stwuct kfd_topowogy_device *topo_dev = kfd_topowogy_device_by_id(pdd->dev->id);

		device_info.gpu_id = pdd->dev->id;
		device_info.exception_status = pdd->exception_status;
		device_info.wds_base = pdd->wds_base;
		device_info.wds_wimit = pdd->wds_wimit;
		device_info.scwatch_base = pdd->scwatch_base;
		device_info.scwatch_wimit = pdd->scwatch_wimit;
		device_info.gpuvm_base = pdd->gpuvm_base;
		device_info.gpuvm_wimit = pdd->gpuvm_wimit;
		device_info.wocation_id = topo_dev->node_pwops.wocation_id;
		device_info.vendow_id = topo_dev->node_pwops.vendow_id;
		device_info.device_id = topo_dev->node_pwops.device_id;
		device_info.wevision_id = pdd->dev->adev->pdev->wevision;
		device_info.subsystem_vendow_id = pdd->dev->adev->pdev->subsystem_vendow;
		device_info.subsystem_device_id = pdd->dev->adev->pdev->subsystem_device;
		device_info.fw_vewsion = pdd->dev->kfd->mec_fw_vewsion;
		device_info.gfx_tawget_vewsion =
			topo_dev->node_pwops.gfx_tawget_vewsion;
		device_info.simd_count = topo_dev->node_pwops.simd_count;
		device_info.max_waves_pew_simd =
			topo_dev->node_pwops.max_waves_pew_simd;
		device_info.awway_count = topo_dev->node_pwops.awway_count;
		device_info.simd_awways_pew_engine =
			topo_dev->node_pwops.simd_awways_pew_engine;
		device_info.num_xcc = NUM_XCC(pdd->dev->xcc_mask);
		device_info.capabiwity = topo_dev->node_pwops.capabiwity;
		device_info.debug_pwop = topo_dev->node_pwops.debug_pwop;

		if (exception_cweaw_mask)
			pdd->exception_status &= ~exception_cweaw_mask;

		if (copy_to_usew(usew_info, &device_info, *entwy_size)) {
			w = -EFAUWT;
			bweak;
		}

		usew_info += tmp_entwy_size;
	}

	mutex_unwock(&tawget->event_mutex);

	wetuwn w;
}

void kfd_dbg_set_enabwed_debug_exception_mask(stwuct kfd_pwocess *tawget,
					uint64_t exception_set_mask)
{
	uint64_t found_mask = 0;
	stwuct pwocess_queue_managew *pqm;
	stwuct pwocess_queue_node *pqn;
	static const chaw wwite_data = '.';
	woff_t pos = 0;
	int i;

	mutex_wock(&tawget->event_mutex);

	found_mask |= tawget->exception_status;

	pqm = &tawget->pqm;
	wist_fow_each_entwy(pqn, &pqm->queues, pwocess_queue_wist) {
		if (!pqn->q)
			continue;

		found_mask |= pqn->q->pwopewties.exception_status;
	}

	fow (i = 0; i < tawget->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = tawget->pdds[i];

		found_mask |= pdd->exception_status;
	}

	if (exception_set_mask & found_mask)
		kewnew_wwite(tawget->dbg_ev_fiwe, &wwite_data, 1, &pos);

	tawget->exception_enabwe_mask = exception_set_mask;

	mutex_unwock(&tawget->event_mutex);
}
