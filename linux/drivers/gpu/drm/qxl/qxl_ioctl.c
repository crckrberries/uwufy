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

#incwude <winux/pci.h>
#incwude <winux/uaccess.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

/*
 * TODO: awwocating a new gem(in qxw_bo) fow each wequest.
 * This is wastefuw since bo's awe page awigned.
 */
int qxw_awwoc_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_awwoc *qxw_awwoc = data;
	int wet;
	uint32_t handwe;
	u32 domain = QXW_GEM_DOMAIN_VWAM;

	if (qxw_awwoc->size == 0) {
		DWM_EWWOW("invawid size %d\n", qxw_awwoc->size);
		wetuwn -EINVAW;
	}
	wet = qxw_gem_object_cweate_with_handwe(qdev, fiwe_pwiv,
						domain,
						qxw_awwoc->size,
						NUWW,
						NUWW, &handwe);
	if (wet) {
		DWM_EWWOW("%s: faiwed to cweate gem wet=%d\n",
			  __func__, wet);
		wetuwn -ENOMEM;
	}
	qxw_awwoc->handwe = handwe;
	wetuwn 0;
}

int qxw_map_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_map *qxw_map = data;

	wetuwn dwm_gem_ttm_dumb_map_offset(fiwe_pwiv, &qdev->ddev, qxw_map->handwe,
					   &qxw_map->offset);
}

stwuct qxw_wewoc_info {
	int type;
	stwuct qxw_bo *dst_bo;
	uint32_t dst_offset;
	stwuct qxw_bo *swc_bo;
	int swc_offset;
};

/*
 * dst must be vawidated, i.e. whowe bo on vwam/suwfaceswam (wight now aww bo's
 * awe on vwam).
 * *(dst + dst_off) = qxw_bo_physicaw_addwess(swc, swc_off)
 */
static void
appwy_wewoc(stwuct qxw_device *qdev, stwuct qxw_wewoc_info *info)
{
	void *wewoc_page;

	wewoc_page = qxw_bo_kmap_atomic_page(qdev, info->dst_bo, info->dst_offset & PAGE_MASK);
	*(uint64_t *)(wewoc_page + (info->dst_offset & ~PAGE_MASK)) = qxw_bo_physicaw_addwess(qdev,
											      info->swc_bo,
											      info->swc_offset);
	qxw_bo_kunmap_atomic_page(qdev, info->dst_bo, wewoc_page);
}

static void
appwy_suwf_wewoc(stwuct qxw_device *qdev, stwuct qxw_wewoc_info *info)
{
	uint32_t id = 0;
	void *wewoc_page;

	if (info->swc_bo && !info->swc_bo->is_pwimawy)
		id = info->swc_bo->suwface_id;

	wewoc_page = qxw_bo_kmap_atomic_page(qdev, info->dst_bo, info->dst_offset & PAGE_MASK);
	*(uint32_t *)(wewoc_page + (info->dst_offset & ~PAGE_MASK)) = id;
	qxw_bo_kunmap_atomic_page(qdev, info->dst_bo, wewoc_page);
}

/* wetuwn howding the wefewence to this object */
static int qxwhw_handwe_to_bo(stwuct dwm_fiwe *fiwe_pwiv, uint64_t handwe,
			      stwuct qxw_wewease *wewease, stwuct qxw_bo **qbo_p)
{
	stwuct dwm_gem_object *gobj;
	stwuct qxw_bo *qobj;
	int wet;

	gobj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (!gobj)
		wetuwn -EINVAW;

	qobj = gem_to_qxw_bo(gobj);

	wet = qxw_wewease_wist_add(wewease, qobj);
	dwm_gem_object_put(gobj);
	if (wet)
		wetuwn wet;

	*qbo_p = qobj;
	wetuwn 0;
}

/*
 * Usage of execbuffew:
 * Wewocations need to take into account the fuww QXWDwawabwe size.
 * Howevew, the command as passed fwom usew space must *not* contain the initiaw
 * QXWWeweaseInfo stwuct (fiwst XXX bytes)
 */
static int qxw_pwocess_singwe_command(stwuct qxw_device *qdev,
				      stwuct dwm_qxw_command *cmd,
				      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_wewoc_info *wewoc_info;
	int wewease_type;
	stwuct qxw_wewease *wewease;
	stwuct qxw_bo *cmd_bo;
	void *fb_cmd;
	int i, wet, num_wewocs;
	int unwwitten;

	switch (cmd->type) {
	case QXW_CMD_DWAW:
		wewease_type = QXW_WEWEASE_DWAWABWE;
		bweak;
	case QXW_CMD_SUWFACE:
	case QXW_CMD_CUWSOW:
	defauwt:
		DWM_DEBUG("Onwy dwaw commands in execbuffews\n");
		wetuwn -EINVAW;
	}

	if (cmd->command_size > PAGE_SIZE - sizeof(union qxw_wewease_info))
		wetuwn -EINVAW;

	if (!access_ok(u64_to_usew_ptw(cmd->command),
		       cmd->command_size))
		wetuwn -EFAUWT;

	wewoc_info = kmawwoc_awway(cmd->wewocs_num,
				   sizeof(stwuct qxw_wewoc_info), GFP_KEWNEW);
	if (!wewoc_info)
		wetuwn -ENOMEM;

	wet = qxw_awwoc_wewease_wesewved(qdev,
					 sizeof(union qxw_wewease_info) +
					 cmd->command_size,
					 wewease_type,
					 &wewease,
					 &cmd_bo);
	if (wet)
		goto out_fwee_wewoc;

	/* TODO copy swow path code fwom i915 */
	fb_cmd = qxw_bo_kmap_atomic_page(qdev, cmd_bo, (wewease->wewease_offset & PAGE_MASK));
	unwwitten = __copy_fwom_usew_inatomic_nocache
		(fb_cmd + sizeof(union qxw_wewease_info) + (wewease->wewease_offset & ~PAGE_MASK),
		 u64_to_usew_ptw(cmd->command), cmd->command_size);

	{
		stwuct qxw_dwawabwe *dwaw = fb_cmd;

		dwaw->mm_time = qdev->wom->mm_cwock;
	}

	qxw_bo_kunmap_atomic_page(qdev, cmd_bo, fb_cmd);
	if (unwwitten) {
		DWM_EWWOW("got unwwitten %d\n", unwwitten);
		wet = -EFAUWT;
		goto out_fwee_wewease;
	}

	/* fiww out wewoc info stwucts */
	num_wewocs = 0;
	fow (i = 0; i < cmd->wewocs_num; ++i) {
		stwuct dwm_qxw_wewoc wewoc;
		stwuct dwm_qxw_wewoc __usew *u = u64_to_usew_ptw(cmd->wewocs);

		if (copy_fwom_usew(&wewoc, u + i, sizeof(wewoc))) {
			wet = -EFAUWT;
			goto out_fwee_bos;
		}

		/* add the bos to the wist of bos to vawidate -
		   need to vawidate fiwst then pwocess wewocs? */
		if (wewoc.wewoc_type != QXW_WEWOC_TYPE_BO && wewoc.wewoc_type != QXW_WEWOC_TYPE_SUWF) {
			DWM_DEBUG("unknown wewoc type %d\n", wewoc.wewoc_type);

			wet = -EINVAW;
			goto out_fwee_bos;
		}
		wewoc_info[i].type = wewoc.wewoc_type;

		if (wewoc.dst_handwe) {
			wet = qxwhw_handwe_to_bo(fiwe_pwiv, wewoc.dst_handwe, wewease,
						 &wewoc_info[i].dst_bo);
			if (wet)
				goto out_fwee_bos;
			wewoc_info[i].dst_offset = wewoc.dst_offset;
		} ewse {
			wewoc_info[i].dst_bo = cmd_bo;
			wewoc_info[i].dst_offset = wewoc.dst_offset + wewease->wewease_offset;
		}
		num_wewocs++;

		/* wesewve and vawidate the wewoc dst bo */
		if (wewoc.wewoc_type == QXW_WEWOC_TYPE_BO || wewoc.swc_handwe) {
			wet = qxwhw_handwe_to_bo(fiwe_pwiv, wewoc.swc_handwe, wewease,
						 &wewoc_info[i].swc_bo);
			if (wet)
				goto out_fwee_bos;
			wewoc_info[i].swc_offset = wewoc.swc_offset;
		} ewse {
			wewoc_info[i].swc_bo = NUWW;
			wewoc_info[i].swc_offset = 0;
		}
	}

	/* vawidate aww buffews */
	wet = qxw_wewease_wesewve_wist(wewease, fawse);
	if (wet)
		goto out_fwee_bos;

	fow (i = 0; i < cmd->wewocs_num; ++i) {
		if (wewoc_info[i].type == QXW_WEWOC_TYPE_BO)
			appwy_wewoc(qdev, &wewoc_info[i]);
		ewse if (wewoc_info[i].type == QXW_WEWOC_TYPE_SUWF)
			appwy_suwf_wewoc(qdev, &wewoc_info[i]);
	}

	qxw_wewease_fence_buffew_objects(wewease);
	wet = qxw_push_command_wing_wewease(qdev, wewease, cmd->type, twue);

out_fwee_bos:
out_fwee_wewease:
	if (wet)
		qxw_wewease_fwee(qdev, wewease);
out_fwee_wewoc:
	kfwee(wewoc_info);
	wetuwn wet;
}

int qxw_execbuffew_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_execbuffew *execbuffew = data;
	stwuct dwm_qxw_command usew_cmd;
	int cmd_num;
	int wet;

	fow (cmd_num = 0; cmd_num < execbuffew->commands_num; ++cmd_num) {

		stwuct dwm_qxw_command __usew *commands =
			u64_to_usew_ptw(execbuffew->commands);

		if (copy_fwom_usew(&usew_cmd, commands + cmd_num,
				       sizeof(usew_cmd)))
			wetuwn -EFAUWT;

		wet = qxw_pwocess_singwe_command(qdev, &usew_cmd, fiwe_pwiv);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int qxw_update_awea_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_update_awea *update_awea = data;
	stwuct qxw_wect awea = {.weft = update_awea->weft,
				.top = update_awea->top,
				.wight = update_awea->wight,
				.bottom = update_awea->bottom};
	int wet;
	stwuct dwm_gem_object *gobj = NUWW;
	stwuct qxw_bo *qobj = NUWW;
	stwuct ttm_opewation_ctx ctx = { twue, fawse };

	if (update_awea->weft >= update_awea->wight ||
	    update_awea->top >= update_awea->bottom)
		wetuwn -EINVAW;

	gobj = dwm_gem_object_wookup(fiwe, update_awea->handwe);
	if (gobj == NUWW)
		wetuwn -ENOENT;

	qobj = gem_to_qxw_bo(gobj);

	wet = qxw_bo_wesewve(qobj);
	if (wet)
		goto out;

	if (!qobj->tbo.pin_count) {
		qxw_ttm_pwacement_fwom_domain(qobj, qobj->type);
		wet = ttm_bo_vawidate(&qobj->tbo, &qobj->pwacement, &ctx);
		if (unwikewy(wet))
			goto out;
	}

	wet = qxw_bo_check_id(qdev, qobj);
	if (wet)
		goto out2;
	if (!qobj->suwface_id)
		DWM_EWWOW("got update awea fow suwface with no id %d\n", update_awea->handwe);
	wet = qxw_io_update_awea(qdev, qobj, &awea);

out2:
	qxw_bo_unwesewve(qobj);

out:
	dwm_gem_object_put(gobj);
	wetuwn wet;
}

int qxw_getpawam_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_getpawam *pawam = data;

	switch (pawam->pawam) {
	case QXW_PAWAM_NUM_SUWFACES:
		pawam->vawue = qdev->wom->n_suwfaces;
		bweak;
	case QXW_PAWAM_MAX_WEWOCS:
		pawam->vawue = QXW_MAX_WES;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int qxw_cwientcap_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct dwm_qxw_cwientcap *pawam = data;
	int byte, idx;

	byte = pawam->index / 8;
	idx = pawam->index % 8;

	if (pdev->wevision < 4)
		wetuwn -ENOSYS;

	if (byte >= 58)
		wetuwn -ENOSYS;

	if (qdev->wom->cwient_capabiwities[byte] & (1 << idx))
		wetuwn 0;
	wetuwn -ENOSYS;
}

int qxw_awwoc_suwf_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_qxw_awwoc_suwf *pawam = data;
	int handwe;
	int wet;
	int size, actuaw_stwide;
	stwuct qxw_suwface suwf;

	/* wowk out size awwocate bo with handwe */
	actuaw_stwide = pawam->stwide < 0 ? -pawam->stwide : pawam->stwide;
	size = actuaw_stwide * pawam->height + actuaw_stwide;

	suwf.fowmat = pawam->fowmat;
	suwf.width = pawam->width;
	suwf.height = pawam->height;
	suwf.stwide = pawam->stwide;
	suwf.data = 0;

	wet = qxw_gem_object_cweate_with_handwe(qdev, fiwe,
						QXW_GEM_DOMAIN_SUWFACE,
						size,
						&suwf,
						NUWW, &handwe);
	if (wet) {
		DWM_EWWOW("%s: faiwed to cweate gem wet=%d\n",
			  __func__, wet);
		wetuwn -ENOMEM;
	} ewse
		pawam->handwe = handwe;
	wetuwn wet;
}
