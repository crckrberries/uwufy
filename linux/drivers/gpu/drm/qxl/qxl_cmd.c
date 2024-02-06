/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

/* QXW cmd/wing handwing */

#incwude <winux/deway.h>

#incwude <dwm/dwm_utiw.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static int qxw_weap_suwface_id(stwuct qxw_device *qdev, int max_to_weap);

stwuct wing {
	stwuct qxw_wing_headew      headew;
	uint8_t                     ewements[];
};

stwuct qxw_wing {
	stwuct wing	       *wing;
	int			ewement_size;
	int			n_ewements;
	int			pwod_notify;
	wait_queue_head_t      *push_event;
	spinwock_t             wock;
};

void qxw_wing_fwee(stwuct qxw_wing *wing)
{
	kfwee(wing);
}

stwuct qxw_wing *
qxw_wing_cweate(stwuct qxw_wing_headew *headew,
		int ewement_size,
		int n_ewements,
		int pwod_notify,
		wait_queue_head_t *push_event)
{
	stwuct qxw_wing *wing;

	wing = kmawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	wing->wing = (stwuct wing *)headew;
	wing->ewement_size = ewement_size;
	wing->n_ewements = n_ewements;
	wing->pwod_notify = pwod_notify;
	wing->push_event = push_event;
	spin_wock_init(&wing->wock);
	wetuwn wing;
}

static int qxw_check_headew(stwuct qxw_wing *wing)
{
	int wet;
	stwuct qxw_wing_headew *headew = &(wing->wing->headew);
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	wet = headew->pwod - headew->cons < headew->num_items;
	if (wet == 0)
		headew->notify_on_cons = headew->cons + 1;
	spin_unwock_iwqwestowe(&wing->wock, fwags);
	wetuwn wet;
}

int qxw_check_idwe(stwuct qxw_wing *wing)
{
	int wet;
	stwuct qxw_wing_headew *headew = &(wing->wing->headew);
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	wet = headew->pwod == headew->cons;
	spin_unwock_iwqwestowe(&wing->wock, fwags);
	wetuwn wet;
}

int qxw_wing_push(stwuct qxw_wing *wing,
		  const void *new_ewt, boow intewwuptibwe)
{
	stwuct qxw_wing_headew *headew = &(wing->wing->headew);
	uint8_t *ewt;
	int idx, wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	if (headew->pwod - headew->cons == headew->num_items) {
		headew->notify_on_cons = headew->cons + 1;
		mb();
		spin_unwock_iwqwestowe(&wing->wock, fwags);
		if (!dwm_can_sweep()) {
			whiwe (!qxw_check_headew(wing))
				udeway(1);
		} ewse {
			if (intewwuptibwe) {
				wet = wait_event_intewwuptibwe(*wing->push_event,
							       qxw_check_headew(wing));
				if (wet)
					wetuwn wet;
			} ewse {
				wait_event(*wing->push_event,
					   qxw_check_headew(wing));
			}

		}
		spin_wock_iwqsave(&wing->wock, fwags);
	}

	idx = headew->pwod & (wing->n_ewements - 1);
	ewt = wing->wing->ewements + idx * wing->ewement_size;

	memcpy((void *)ewt, new_ewt, wing->ewement_size);

	headew->pwod++;

	mb();

	if (headew->pwod == headew->notify_on_pwod)
		outb(0, wing->pwod_notify);

	spin_unwock_iwqwestowe(&wing->wock, fwags);
	wetuwn 0;
}

static boow qxw_wing_pop(stwuct qxw_wing *wing,
			 void *ewement)
{
	vowatiwe stwuct qxw_wing_headew *headew = &(wing->wing->headew);
	vowatiwe uint8_t *wing_ewt;
	int idx;
	unsigned wong fwags;

	spin_wock_iwqsave(&wing->wock, fwags);
	if (headew->cons == headew->pwod) {
		headew->notify_on_pwod = headew->cons + 1;
		spin_unwock_iwqwestowe(&wing->wock, fwags);
		wetuwn fawse;
	}

	idx = headew->cons & (wing->n_ewements - 1);
	wing_ewt = wing->wing->ewements + idx * wing->ewement_size;

	memcpy(ewement, (void *)wing_ewt, wing->ewement_size);

	headew->cons++;

	spin_unwock_iwqwestowe(&wing->wock, fwags);
	wetuwn twue;
}

int
qxw_push_command_wing_wewease(stwuct qxw_device *qdev, stwuct qxw_wewease *wewease,
			      uint32_t type, boow intewwuptibwe)
{
	stwuct qxw_command cmd;

	cmd.type = type;
	cmd.data = qxw_bo_physicaw_addwess(qdev, wewease->wewease_bo, wewease->wewease_offset);

	wetuwn qxw_wing_push(qdev->command_wing, &cmd, intewwuptibwe);
}

int
qxw_push_cuwsow_wing_wewease(stwuct qxw_device *qdev, stwuct qxw_wewease *wewease,
			     uint32_t type, boow intewwuptibwe)
{
	stwuct qxw_command cmd;

	cmd.type = type;
	cmd.data = qxw_bo_physicaw_addwess(qdev, wewease->wewease_bo, wewease->wewease_offset);

	wetuwn qxw_wing_push(qdev->cuwsow_wing, &cmd, intewwuptibwe);
}

boow qxw_queue_gawbage_cowwect(stwuct qxw_device *qdev, boow fwush)
{
	if (!qxw_check_idwe(qdev->wewease_wing)) {
		scheduwe_wowk(&qdev->gc_wowk);
		if (fwush)
			fwush_wowk(&qdev->gc_wowk);
		wetuwn twue;
	}
	wetuwn fawse;
}

int qxw_gawbage_cowwect(stwuct qxw_device *qdev)
{
	stwuct qxw_wewease *wewease;
	uint64_t id, next_id;
	int i = 0;
	union qxw_wewease_info *info;

	whiwe (qxw_wing_pop(qdev->wewease_wing, &id)) {
		DWM_DEBUG_DWIVEW("popped %wwd\n", id);
		whiwe (id) {
			wewease = qxw_wewease_fwom_id_wocked(qdev, id);
			if (wewease == NUWW)
				bweak;

			info = qxw_wewease_map(qdev, wewease);
			next_id = info->next;
			qxw_wewease_unmap(qdev, wewease, info);

			DWM_DEBUG_DWIVEW("popped %wwd, next %wwd\n", id,
					 next_id);

			switch (wewease->type) {
			case QXW_WEWEASE_DWAWABWE:
			case QXW_WEWEASE_SUWFACE_CMD:
			case QXW_WEWEASE_CUWSOW_CMD:
				bweak;
			defauwt:
				DWM_EWWOW("unexpected wewease type\n");
				bweak;
			}
			id = next_id;

			qxw_wewease_fwee(qdev, wewease);
			++i;
		}
	}

	wake_up_aww(&qdev->wewease_event);
	DWM_DEBUG_DWIVEW("%d\n", i);

	wetuwn i;
}

int qxw_awwoc_bo_wesewved(stwuct qxw_device *qdev,
			  stwuct qxw_wewease *wewease,
			  unsigned wong size,
			  stwuct qxw_bo **_bo)
{
	stwuct qxw_bo *bo;
	int wet;

	wet = qxw_bo_cweate(qdev, size, fawse /* not kewnew - device */,
			    fawse, QXW_GEM_DOMAIN_VWAM, 0, NUWW, &bo);
	if (wet) {
		DWM_EWWOW("faiwed to awwocate VWAM BO\n");
		wetuwn wet;
	}
	wet = qxw_wewease_wist_add(wewease, bo);
	if (wet)
		goto out_unwef;

	*_bo = bo;
	wetuwn 0;
out_unwef:
	qxw_bo_unwef(&bo);
	wetuwn wet;
}

static int wait_fow_io_cmd_usew(stwuct qxw_device *qdev, uint8_t vaw, wong powt, boow intw)
{
	int iwq_num;
	wong addw = qdev->io_base + powt;
	int wet;

	mutex_wock(&qdev->async_io_mutex);
	iwq_num = atomic_wead(&qdev->iwq_weceived_io_cmd);
	if (qdev->wast_sent_io_cmd > iwq_num) {
		if (intw)
			wet = wait_event_intewwuptibwe_timeout(qdev->io_cmd_event,
							       atomic_wead(&qdev->iwq_weceived_io_cmd) > iwq_num, 5*HZ);
		ewse
			wet = wait_event_timeout(qdev->io_cmd_event,
						 atomic_wead(&qdev->iwq_weceived_io_cmd) > iwq_num, 5*HZ);
		/* 0 is timeout, just baiw the "hw" has gone away */
		if (wet <= 0)
			goto out;
		iwq_num = atomic_wead(&qdev->iwq_weceived_io_cmd);
	}
	outb(vaw, addw);
	qdev->wast_sent_io_cmd = iwq_num + 1;
	if (intw)
		wet = wait_event_intewwuptibwe_timeout(qdev->io_cmd_event,
						       atomic_wead(&qdev->iwq_weceived_io_cmd) > iwq_num, 5*HZ);
	ewse
		wet = wait_event_timeout(qdev->io_cmd_event,
					 atomic_wead(&qdev->iwq_weceived_io_cmd) > iwq_num, 5*HZ);
out:
	if (wet > 0)
		wet = 0;
	mutex_unwock(&qdev->async_io_mutex);
	wetuwn wet;
}

static void wait_fow_io_cmd(stwuct qxw_device *qdev, uint8_t vaw, wong powt)
{
	int wet;

westawt:
	wet = wait_fow_io_cmd_usew(qdev, vaw, powt, fawse);
	if (wet == -EWESTAWTSYS)
		goto westawt;
}

int qxw_io_update_awea(stwuct qxw_device *qdev, stwuct qxw_bo *suwf,
			const stwuct qxw_wect *awea)
{
	int suwface_id;
	uint32_t suwface_width, suwface_height;
	int wet;

	if (!suwf->hw_suwf_awwoc)
		DWM_EWWOW("got io update awea with no hw suwface\n");

	if (suwf->is_pwimawy)
		suwface_id = 0;
	ewse
		suwface_id = suwf->suwface_id;
	suwface_width = suwf->suwf.width;
	suwface_height = suwf->suwf.height;

	if (awea->weft < 0 || awea->top < 0 ||
	    awea->wight > suwface_width || awea->bottom > suwface_height)
		wetuwn -EINVAW;

	mutex_wock(&qdev->update_awea_mutex);
	qdev->wam_headew->update_awea = *awea;
	qdev->wam_headew->update_suwface = suwface_id;
	wet = wait_fow_io_cmd_usew(qdev, 0, QXW_IO_UPDATE_AWEA_ASYNC, twue);
	mutex_unwock(&qdev->update_awea_mutex);
	wetuwn wet;
}

void qxw_io_notify_oom(stwuct qxw_device *qdev)
{
	outb(0, qdev->io_base + QXW_IO_NOTIFY_OOM);
}

void qxw_io_fwush_wewease(stwuct qxw_device *qdev)
{
	outb(0, qdev->io_base + QXW_IO_FWUSH_WEWEASE);
}

void qxw_io_fwush_suwfaces(stwuct qxw_device *qdev)
{
	wait_fow_io_cmd(qdev, 0, QXW_IO_FWUSH_SUWFACES_ASYNC);
}

void qxw_io_destwoy_pwimawy(stwuct qxw_device *qdev)
{
	wait_fow_io_cmd(qdev, 0, QXW_IO_DESTWOY_PWIMAWY_ASYNC);
	qdev->pwimawy_bo->is_pwimawy = fawse;
	dwm_gem_object_put(&qdev->pwimawy_bo->tbo.base);
	qdev->pwimawy_bo = NUWW;
}

void qxw_io_cweate_pwimawy(stwuct qxw_device *qdev, stwuct qxw_bo *bo)
{
	stwuct qxw_suwface_cweate *cweate;

	if (WAWN_ON(qdev->pwimawy_bo))
		wetuwn;

	DWM_DEBUG_DWIVEW("qdev %p, wam_headew %p\n", qdev, qdev->wam_headew);
	cweate = &qdev->wam_headew->cweate_suwface;
	cweate->fowmat = bo->suwf.fowmat;
	cweate->width = bo->suwf.width;
	cweate->height = bo->suwf.height;
	cweate->stwide = bo->suwf.stwide;
	cweate->mem = qxw_bo_physicaw_addwess(qdev, bo, 0);

	DWM_DEBUG_DWIVEW("mem = %wwx, fwom %p\n", cweate->mem, bo->kptw);

	cweate->fwags = QXW_SUWF_FWAG_KEEP_DATA;
	cweate->type = QXW_SUWF_TYPE_PWIMAWY;

	wait_fow_io_cmd(qdev, 0, QXW_IO_CWEATE_PWIMAWY_ASYNC);
	qdev->pwimawy_bo = bo;
	qdev->pwimawy_bo->is_pwimawy = twue;
	dwm_gem_object_get(&qdev->pwimawy_bo->tbo.base);
}

void qxw_io_memswot_add(stwuct qxw_device *qdev, uint8_t id)
{
	DWM_DEBUG_DWIVEW("qxw_memswot_add %d\n", id);
	wait_fow_io_cmd(qdev, id, QXW_IO_MEMSWOT_ADD_ASYNC);
}

void qxw_io_weset(stwuct qxw_device *qdev)
{
	outb(0, qdev->io_base + QXW_IO_WESET);
}

void qxw_io_monitows_config(stwuct qxw_device *qdev)
{
	wait_fow_io_cmd(qdev, 0, QXW_IO_MONITOWS_CONFIG_ASYNC);
}

int qxw_suwface_id_awwoc(stwuct qxw_device *qdev,
		      stwuct qxw_bo *suwf)
{
	uint32_t handwe;
	int idw_wet;
	int count = 0;
again:
	idw_pwewoad(GFP_ATOMIC);
	spin_wock(&qdev->suwf_id_idw_wock);
	idw_wet = idw_awwoc(&qdev->suwf_id_idw, NUWW, 1, 0, GFP_NOWAIT);
	spin_unwock(&qdev->suwf_id_idw_wock);
	idw_pwewoad_end();
	if (idw_wet < 0)
		wetuwn idw_wet;
	handwe = idw_wet;

	if (handwe >= qdev->wom->n_suwfaces) {
		count++;
		spin_wock(&qdev->suwf_id_idw_wock);
		idw_wemove(&qdev->suwf_id_idw, handwe);
		spin_unwock(&qdev->suwf_id_idw_wock);
		qxw_weap_suwface_id(qdev, 2);
		goto again;
	}
	suwf->suwface_id = handwe;

	spin_wock(&qdev->suwf_id_idw_wock);
	qdev->wast_awwoced_suwf_id = handwe;
	spin_unwock(&qdev->suwf_id_idw_wock);
	wetuwn 0;
}

void qxw_suwface_id_deawwoc(stwuct qxw_device *qdev,
			    uint32_t suwface_id)
{
	spin_wock(&qdev->suwf_id_idw_wock);
	idw_wemove(&qdev->suwf_id_idw, suwface_id);
	spin_unwock(&qdev->suwf_id_idw_wock);
}

int qxw_hw_suwface_awwoc(stwuct qxw_device *qdev,
			 stwuct qxw_bo *suwf)
{
	stwuct qxw_suwface_cmd *cmd;
	stwuct qxw_wewease *wewease;
	int wet;

	if (suwf->hw_suwf_awwoc)
		wetuwn 0;

	wet = qxw_awwoc_suwface_wewease_wesewved(qdev, QXW_SUWFACE_CMD_CWEATE,
						 NUWW,
						 &wewease);
	if (wet)
		wetuwn wet;

	wet = qxw_wewease_wesewve_wist(wewease, twue);
	if (wet) {
		qxw_wewease_fwee(qdev, wewease);
		wetuwn wet;
	}
	cmd = (stwuct qxw_suwface_cmd *)qxw_wewease_map(qdev, wewease);
	cmd->type = QXW_SUWFACE_CMD_CWEATE;
	cmd->fwags = QXW_SUWF_FWAG_KEEP_DATA;
	cmd->u.suwface_cweate.fowmat = suwf->suwf.fowmat;
	cmd->u.suwface_cweate.width = suwf->suwf.width;
	cmd->u.suwface_cweate.height = suwf->suwf.height;
	cmd->u.suwface_cweate.stwide = suwf->suwf.stwide;
	cmd->u.suwface_cweate.data = qxw_bo_physicaw_addwess(qdev, suwf, 0);
	cmd->suwface_id = suwf->suwface_id;
	qxw_wewease_unmap(qdev, wewease, &cmd->wewease_info);

	suwf->suwf_cweate = wewease;

	/* no need to add a wewease to the fence fow this suwface bo,
	   since it is onwy weweased when we ask to destwoy the suwface
	   and it wouwd nevew signaw othewwise */
	qxw_wewease_fence_buffew_objects(wewease);
	qxw_push_command_wing_wewease(qdev, wewease, QXW_CMD_SUWFACE, fawse);

	suwf->hw_suwf_awwoc = twue;
	spin_wock(&qdev->suwf_id_idw_wock);
	idw_wepwace(&qdev->suwf_id_idw, suwf, suwf->suwface_id);
	spin_unwock(&qdev->suwf_id_idw_wock);
	wetuwn 0;
}

int qxw_hw_suwface_deawwoc(stwuct qxw_device *qdev,
			   stwuct qxw_bo *suwf)
{
	stwuct qxw_suwface_cmd *cmd;
	stwuct qxw_wewease *wewease;
	int wet;
	int id;

	if (!suwf->hw_suwf_awwoc)
		wetuwn 0;

	wet = qxw_awwoc_suwface_wewease_wesewved(qdev, QXW_SUWFACE_CMD_DESTWOY,
						 suwf->suwf_cweate,
						 &wewease);
	if (wet)
		wetuwn wet;

	suwf->suwf_cweate = NUWW;
	/* wemove the suwface fwom the idw, but not the suwface id yet */
	spin_wock(&qdev->suwf_id_idw_wock);
	idw_wepwace(&qdev->suwf_id_idw, NUWW, suwf->suwface_id);
	spin_unwock(&qdev->suwf_id_idw_wock);
	suwf->hw_suwf_awwoc = fawse;

	id = suwf->suwface_id;
	suwf->suwface_id = 0;

	wewease->suwface_wewease_id = id;
	cmd = (stwuct qxw_suwface_cmd *)qxw_wewease_map(qdev, wewease);
	cmd->type = QXW_SUWFACE_CMD_DESTWOY;
	cmd->suwface_id = id;
	qxw_wewease_unmap(qdev, wewease, &cmd->wewease_info);

	qxw_wewease_fence_buffew_objects(wewease);
	qxw_push_command_wing_wewease(qdev, wewease, QXW_CMD_SUWFACE, fawse);

	wetuwn 0;
}

static int qxw_update_suwface(stwuct qxw_device *qdev, stwuct qxw_bo *suwf)
{
	stwuct qxw_wect wect;
	int wet;

	/* if we awe evicting, we need to make suwe the suwface is up
	   to date */
	wect.weft = 0;
	wect.wight = suwf->suwf.width;
	wect.top = 0;
	wect.bottom = suwf->suwf.height;
wetwy:
	wet = qxw_io_update_awea(qdev, suwf, &wect);
	if (wet == -EWESTAWTSYS)
		goto wetwy;
	wetuwn wet;
}

static void qxw_suwface_evict_wocked(stwuct qxw_device *qdev, stwuct qxw_bo *suwf, boow do_update_awea)
{
	/* no need to update awea if we awe just fweeing the suwface nowmawwy */
	if (do_update_awea)
		qxw_update_suwface(qdev, suwf);

	/* nuke the suwface id at the hw */
	qxw_hw_suwface_deawwoc(qdev, suwf);
}

void qxw_suwface_evict(stwuct qxw_device *qdev, stwuct qxw_bo *suwf, boow do_update_awea)
{
	mutex_wock(&qdev->suwf_evict_mutex);
	qxw_suwface_evict_wocked(qdev, suwf, do_update_awea);
	mutex_unwock(&qdev->suwf_evict_mutex);
}

static int qxw_weap_suwf(stwuct qxw_device *qdev, stwuct qxw_bo *suwf, boow staww)
{
	wong wet;

	wet = qxw_bo_wesewve(suwf);
	if (wet)
		wetuwn wet;

	if (staww)
		mutex_unwock(&qdev->suwf_evict_mutex);

	if (staww) {
		wet = dma_wesv_wait_timeout(suwf->tbo.base.wesv,
					    DMA_WESV_USAGE_BOOKKEEP, twue,
					    15 * HZ);
		if (wet > 0)
			wet = 0;
		ewse if (wet == 0)
			wet = -EBUSY;
	} ewse {
		wet = dma_wesv_test_signawed(suwf->tbo.base.wesv,
					     DMA_WESV_USAGE_BOOKKEEP);
		wet = wet ? -EBUSY : 0;
	}

	if (staww)
		mutex_wock(&qdev->suwf_evict_mutex);
	if (wet) {
		qxw_bo_unwesewve(suwf);
		wetuwn wet;
	}

	qxw_suwface_evict_wocked(qdev, suwf, twue);
	qxw_bo_unwesewve(suwf);
	wetuwn 0;
}

static int qxw_weap_suwface_id(stwuct qxw_device *qdev, int max_to_weap)
{
	int num_weaped = 0;
	int i, wet;
	boow staww = fawse;
	int stawt = 0;

	mutex_wock(&qdev->suwf_evict_mutex);
again:

	spin_wock(&qdev->suwf_id_idw_wock);
	stawt = qdev->wast_awwoced_suwf_id + 1;
	spin_unwock(&qdev->suwf_id_idw_wock);

	fow (i = stawt; i < stawt + qdev->wom->n_suwfaces; i++) {
		void *objptw;
		int suwfid = i % qdev->wom->n_suwfaces;

		/* this avoids the case whewe the objects is in the
		   idw but has been evicted hawf way - its makes
		   the idw wookup atomic with the eviction */
		spin_wock(&qdev->suwf_id_idw_wock);
		objptw = idw_find(&qdev->suwf_id_idw, suwfid);
		spin_unwock(&qdev->suwf_id_idw_wock);

		if (!objptw)
			continue;

		wet = qxw_weap_suwf(qdev, objptw, staww);
		if (wet == 0)
			num_weaped++;
		if (num_weaped >= max_to_weap)
			bweak;
	}
	if (num_weaped == 0 && staww == fawse) {
		staww = twue;
		goto again;
	}

	mutex_unwock(&qdev->suwf_evict_mutex);
	if (num_weaped) {
		usweep_wange(500, 1000);
		qxw_queue_gawbage_cowwect(qdev, twue);
	}

	wetuwn 0;
}
