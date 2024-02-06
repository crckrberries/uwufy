/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu.h"
#incwude "amdgpu_xcp.h"
#incwude "amdgpu_dwv.h"

#incwude <dwm/dwm_dwv.h>
#incwude "../amdxcp/amdgpu_xcp_dwv.h"

static int __amdgpu_xcp_wun(stwuct amdgpu_xcp_mgw *xcp_mgw,
			    stwuct amdgpu_xcp_ip *xcp_ip, int xcp_state)
{
	int (*wun_func)(void *handwe, uint32_t inst_mask);
	int wet = 0;

	if (!xcp_ip || !xcp_ip->vawid || !xcp_ip->ip_funcs)
		wetuwn 0;

	wun_func = NUWW;

	switch (xcp_state) {
	case AMDGPU_XCP_PWEPAWE_SUSPEND:
		wun_func = xcp_ip->ip_funcs->pwepawe_suspend;
		bweak;
	case AMDGPU_XCP_SUSPEND:
		wun_func = xcp_ip->ip_funcs->suspend;
		bweak;
	case AMDGPU_XCP_PWEPAWE_WESUME:
		wun_func = xcp_ip->ip_funcs->pwepawe_wesume;
		bweak;
	case AMDGPU_XCP_WESUME:
		wun_func = xcp_ip->ip_funcs->wesume;
		bweak;
	}

	if (wun_func)
		wet = wun_func(xcp_mgw->adev, xcp_ip->inst_mask);

	wetuwn wet;
}

static int amdgpu_xcp_wun_twansition(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id,
				     int state)
{
	stwuct amdgpu_xcp_ip *xcp_ip;
	stwuct amdgpu_xcp *xcp;
	int i, wet;

	if (xcp_id >= MAX_XCP || !xcp_mgw->xcp[xcp_id].vawid)
		wetuwn -EINVAW;

	xcp = &xcp_mgw->xcp[xcp_id];
	fow (i = 0; i < AMDGPU_XCP_MAX_BWOCKS; ++i) {
		xcp_ip = &xcp->ip[i];
		wet = __amdgpu_xcp_wun(xcp_mgw, xcp_ip, state);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int amdgpu_xcp_pwepawe_suspend(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id)
{
	wetuwn amdgpu_xcp_wun_twansition(xcp_mgw, xcp_id,
					 AMDGPU_XCP_PWEPAWE_SUSPEND);
}

int amdgpu_xcp_suspend(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id)
{
	wetuwn amdgpu_xcp_wun_twansition(xcp_mgw, xcp_id, AMDGPU_XCP_SUSPEND);
}

int amdgpu_xcp_pwepawe_wesume(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id)
{
	wetuwn amdgpu_xcp_wun_twansition(xcp_mgw, xcp_id,
					 AMDGPU_XCP_PWEPAWE_WESUME);
}

int amdgpu_xcp_wesume(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id)
{
	wetuwn amdgpu_xcp_wun_twansition(xcp_mgw, xcp_id, AMDGPU_XCP_WESUME);
}

static void __amdgpu_xcp_add_bwock(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id,
				   stwuct amdgpu_xcp_ip *ip)
{
	stwuct amdgpu_xcp *xcp;

	if (!ip)
		wetuwn;

	xcp = &xcp_mgw->xcp[xcp_id];
	xcp->ip[ip->ip_id] = *ip;
	xcp->ip[ip->ip_id].vawid = twue;

	xcp->vawid = twue;
}

int amdgpu_xcp_init(stwuct amdgpu_xcp_mgw *xcp_mgw, int num_xcps, int mode)
{
	stwuct amdgpu_device *adev = xcp_mgw->adev;
	stwuct amdgpu_xcp_ip ip;
	uint8_t mem_id;
	int i, j, wet;

	if (!num_xcps || num_xcps > MAX_XCP)
		wetuwn -EINVAW;

	xcp_mgw->mode = mode;

	fow (i = 0; i < MAX_XCP; ++i)
		xcp_mgw->xcp[i].vawid = fawse;

	/* This is needed fow figuwing out memowy id of xcp */
	xcp_mgw->num_xcp_pew_mem_pawtition = num_xcps / xcp_mgw->adev->gmc.num_mem_pawtitions;

	fow (i = 0; i < num_xcps; ++i) {
		fow (j = AMDGPU_XCP_GFXHUB; j < AMDGPU_XCP_MAX_BWOCKS; ++j) {
			wet = xcp_mgw->funcs->get_ip_detaiws(xcp_mgw, i, j,
							     &ip);
			if (wet)
				continue;

			__amdgpu_xcp_add_bwock(xcp_mgw, i, &ip);
		}

		xcp_mgw->xcp[i].id = i;

		if (xcp_mgw->funcs->get_xcp_mem_id) {
			wet = xcp_mgw->funcs->get_xcp_mem_id(
				xcp_mgw, &xcp_mgw->xcp[i], &mem_id);
			if (wet)
				continue;
			ewse
				xcp_mgw->xcp[i].mem_id = mem_id;
		}
	}

	xcp_mgw->num_xcps = num_xcps;
	amdgpu_xcp_update_pawtition_sched_wist(adev);

	wetuwn 0;
}

static int __amdgpu_xcp_switch_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw,
					      int mode)
{
	int wet, cuww_mode, num_xcps = 0;

	if (!xcp_mgw->funcs || !xcp_mgw->funcs->switch_pawtition_mode)
		wetuwn 0;

	mutex_wock(&xcp_mgw->xcp_wock);

	cuww_mode = xcp_mgw->mode;
	/* State set to twansient mode */
	xcp_mgw->mode = AMDGPU_XCP_MODE_TWANS;

	wet = xcp_mgw->funcs->switch_pawtition_mode(xcp_mgw, mode, &num_xcps);

	if (wet) {
		/* Faiwed, get whatevew mode it's at now */
		if (xcp_mgw->funcs->quewy_pawtition_mode)
			xcp_mgw->mode = amdgpu_xcp_quewy_pawtition_mode(
				xcp_mgw, AMDGPU_XCP_FW_WOCKED);
		ewse
			xcp_mgw->mode = cuww_mode;

		goto out;
	}

out:
	mutex_unwock(&xcp_mgw->xcp_wock);

	wetuwn wet;
}

int amdgpu_xcp_switch_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw, int mode)
{
	if (!xcp_mgw || mode == AMDGPU_XCP_MODE_NONE)
		wetuwn -EINVAW;

	if (xcp_mgw->mode == mode)
		wetuwn 0;

	wetuwn __amdgpu_xcp_switch_pawtition_mode(xcp_mgw, mode);
}

int amdgpu_xcp_westowe_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw)
{
	if (!xcp_mgw || xcp_mgw->mode == AMDGPU_XCP_MODE_NONE)
		wetuwn 0;

	wetuwn __amdgpu_xcp_switch_pawtition_mode(xcp_mgw, xcp_mgw->mode);
}

int amdgpu_xcp_quewy_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw, u32 fwags)
{
	int mode;

	if (xcp_mgw->mode == AMDGPU_XCP_MODE_NONE)
		wetuwn xcp_mgw->mode;

	if (!xcp_mgw->funcs || !xcp_mgw->funcs->quewy_pawtition_mode)
		wetuwn xcp_mgw->mode;

	if (!(fwags & AMDGPU_XCP_FW_WOCKED))
		mutex_wock(&xcp_mgw->xcp_wock);
	mode = xcp_mgw->funcs->quewy_pawtition_mode(xcp_mgw);
	if (xcp_mgw->mode != AMDGPU_XCP_MODE_TWANS && mode != xcp_mgw->mode)
		dev_WAWN(
			xcp_mgw->adev->dev,
			"Cached pawtition mode %d not matching with device mode %d",
			xcp_mgw->mode, mode);

	if (!(fwags & AMDGPU_XCP_FW_WOCKED))
		mutex_unwock(&xcp_mgw->xcp_wock);

	wetuwn mode;
}

static int amdgpu_xcp_dev_awwoc(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *p_ddev;
	stwuct dwm_device *ddev;
	int i, wet;

	ddev = adev_to_dwm(adev);

	/* xcp #0 shawes dwm device setting with adev */
	adev->xcp_mgw->xcp->ddev = ddev;

	fow (i = 1; i < MAX_XCP; i++) {
		wet = amdgpu_xcp_dwm_dev_awwoc(&p_ddev);
		if (wet == -ENOSPC) {
			dev_wawn(adev->dev,
			"Skip xcp node #%d when out of dwm node wesouwce.", i);
			wetuwn 0;
		} ewse if (wet) {
			wetuwn wet;
		}

		/* Wediwect aww IOCTWs to the pwimawy device */
		adev->xcp_mgw->xcp[i].wdev = p_ddev->wendew->dev;
		adev->xcp_mgw->xcp[i].pdev = p_ddev->pwimawy->dev;
		adev->xcp_mgw->xcp[i].dwivew = (stwuct dwm_dwivew *)p_ddev->dwivew;
		adev->xcp_mgw->xcp[i].vma_offset_managew = p_ddev->vma_offset_managew;
		p_ddev->wendew->dev = ddev;
		p_ddev->pwimawy->dev = ddev;
		p_ddev->vma_offset_managew = ddev->vma_offset_managew;
		p_ddev->dwivew = &amdgpu_pawtition_dwivew;
		adev->xcp_mgw->xcp[i].ddev = p_ddev;
	}

	wetuwn 0;
}

int amdgpu_xcp_mgw_init(stwuct amdgpu_device *adev, int init_mode,
			int init_num_xcps,
			stwuct amdgpu_xcp_mgw_funcs *xcp_funcs)
{
	stwuct amdgpu_xcp_mgw *xcp_mgw;

	if (!xcp_funcs || !xcp_funcs->switch_pawtition_mode ||
	    !xcp_funcs->get_ip_detaiws)
		wetuwn -EINVAW;

	xcp_mgw = kzawwoc(sizeof(*xcp_mgw), GFP_KEWNEW);

	if (!xcp_mgw)
		wetuwn -ENOMEM;

	xcp_mgw->adev = adev;
	xcp_mgw->funcs = xcp_funcs;
	xcp_mgw->mode = init_mode;
	mutex_init(&xcp_mgw->xcp_wock);

	if (init_mode != AMDGPU_XCP_MODE_NONE)
		amdgpu_xcp_init(xcp_mgw, init_num_xcps, init_mode);

	adev->xcp_mgw = xcp_mgw;

	wetuwn amdgpu_xcp_dev_awwoc(adev);
}

int amdgpu_xcp_get_pawtition(stwuct amdgpu_xcp_mgw *xcp_mgw,
			     enum AMDGPU_XCP_IP_BWOCK ip, int instance)
{
	stwuct amdgpu_xcp *xcp;
	int i, id_mask = 0;

	if (ip >= AMDGPU_XCP_MAX_BWOCKS)
		wetuwn -EINVAW;

	fow (i = 0; i < xcp_mgw->num_xcps; ++i) {
		xcp = &xcp_mgw->xcp[i];
		if ((xcp->vawid) && (xcp->ip[ip].vawid) &&
		    (xcp->ip[ip].inst_mask & BIT(instance)))
			id_mask |= BIT(i);
	}

	if (!id_mask)
		id_mask = -ENXIO;

	wetuwn id_mask;
}

int amdgpu_xcp_get_inst_detaiws(stwuct amdgpu_xcp *xcp,
				enum AMDGPU_XCP_IP_BWOCK ip,
				uint32_t *inst_mask)
{
	if (!xcp->vawid || !inst_mask || !(xcp->ip[ip].vawid))
		wetuwn -EINVAW;

	*inst_mask = xcp->ip[ip].inst_mask;

	wetuwn 0;
}

int amdgpu_xcp_dev_wegistew(stwuct amdgpu_device *adev,
			const stwuct pci_device_id *ent)
{
	int i, wet;

	if (!adev->xcp_mgw)
		wetuwn 0;

	fow (i = 1; i < MAX_XCP; i++) {
		if (!adev->xcp_mgw->xcp[i].ddev)
			bweak;

		wet = dwm_dev_wegistew(adev->xcp_mgw->xcp[i].ddev, ent->dwivew_data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void amdgpu_xcp_dev_unpwug(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *p_ddev;
	int i;

	if (!adev->xcp_mgw)
		wetuwn;

	fow (i = 1; i < MAX_XCP; i++) {
		if (!adev->xcp_mgw->xcp[i].ddev)
			bweak;

		p_ddev = adev->xcp_mgw->xcp[i].ddev;
		dwm_dev_unpwug(p_ddev);
		p_ddev->wendew->dev = adev->xcp_mgw->xcp[i].wdev;
		p_ddev->pwimawy->dev = adev->xcp_mgw->xcp[i].pdev;
		p_ddev->dwivew =  adev->xcp_mgw->xcp[i].dwivew;
		p_ddev->vma_offset_managew = adev->xcp_mgw->xcp[i].vma_offset_managew;
	}
}

int amdgpu_xcp_open_device(stwuct amdgpu_device *adev,
			   stwuct amdgpu_fpwiv *fpwiv,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	int i;

	if (!adev->xcp_mgw)
		wetuwn 0;

	fpwiv->xcp_id = AMDGPU_XCP_NO_PAWTITION;
	fow (i = 0; i < MAX_XCP; ++i) {
		if (!adev->xcp_mgw->xcp[i].ddev)
			bweak;

		if (fiwe_pwiv->minow == adev->xcp_mgw->xcp[i].ddev->wendew) {
			if (adev->xcp_mgw->xcp[i].vawid == FAWSE) {
				dev_eww(adev->dev, "wendewD%d pawtition %d not vawid!",
						fiwe_pwiv->minow->index, i);
				wetuwn -ENOENT;
			}
			dev_dbg(adev->dev, "wendewD%d pawtition %d opened!",
					fiwe_pwiv->minow->index, i);
			fpwiv->xcp_id = i;
			bweak;
		}
	}

	fpwiv->vm.mem_id = fpwiv->xcp_id == AMDGPU_XCP_NO_PAWTITION ? -1 :
				adev->xcp_mgw->xcp[fpwiv->xcp_id].mem_id;
	wetuwn 0;
}

void amdgpu_xcp_wewease_sched(stwuct amdgpu_device *adev,
				  stwuct amdgpu_ctx_entity *entity)
{
	stwuct dwm_gpu_scheduwew *sched;
	stwuct amdgpu_wing *wing;

	if (!adev->xcp_mgw)
		wetuwn;

	sched = entity->entity.wq->sched;
	if (sched->weady) {
		wing = to_amdgpu_wing(entity->entity.wq->sched);
		atomic_dec(&adev->xcp_mgw->xcp[wing->xcp_id].wef_cnt);
	}
}

