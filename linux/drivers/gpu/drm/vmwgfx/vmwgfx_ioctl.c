// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2022 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_devcaps.h"
#incwude "vmwgfx_kms.h"

#incwude <dwm/vmwgfx_dwm.h>
#incwude <winux/pci.h>

int vmw_getpawam_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_vmw_getpawam_awg *pawam =
	    (stwuct dwm_vmw_getpawam_awg *)data;
	stwuct vmw_fpwiv *vmw_fp = vmw_fpwiv(fiwe_pwiv);

	switch (pawam->pawam) {
	case DWM_VMW_PAWAM_NUM_STWEAMS:
		pawam->vawue = vmw_ovewway_num_ovewways(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_NUM_FWEE_STWEAMS:
		pawam->vawue = vmw_ovewway_num_fwee_ovewways(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_3D:
		pawam->vawue = vmw_suppowts_3d(dev_pwiv) ? 1 : 0;
		bweak;
	case DWM_VMW_PAWAM_HW_CAPS:
		pawam->vawue = dev_pwiv->capabiwities;
		bweak;
	case DWM_VMW_PAWAM_HW_CAPS2:
		pawam->vawue = dev_pwiv->capabiwities2;
		bweak;
	case DWM_VMW_PAWAM_FIFO_CAPS:
		pawam->vawue = vmw_fifo_caps(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_MAX_FB_SIZE:
		pawam->vawue = dev_pwiv->max_pwimawy_mem;
		bweak;
	case DWM_VMW_PAWAM_FIFO_HW_VEWSION:
	{
		if ((dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS))
			pawam->vawue = SVGA3D_HWVEWSION_WS8_B1;
		ewse
			pawam->vawue = vmw_fifo_mem_wead(
					       dev_pwiv,
					       ((vmw_fifo_caps(dev_pwiv) &
						 SVGA_FIFO_CAP_3D_HWVEWSION_WEVISED) ?
							SVGA_FIFO_3D_HWVEWSION_WEVISED :
							SVGA_FIFO_3D_HWVEWSION));
		bweak;
	}
	case DWM_VMW_PAWAM_MAX_SUWF_MEMOWY:
		if ((dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS) &&
		    !vmw_fp->gb_awawe)
			pawam->vawue = dev_pwiv->max_mob_pages * PAGE_SIZE / 2;
		ewse
			pawam->vawue = dev_pwiv->memowy_size;
		bweak;
	case DWM_VMW_PAWAM_3D_CAPS_SIZE:
		pawam->vawue = vmw_devcaps_size(dev_pwiv, vmw_fp->gb_awawe);
		bweak;
	case DWM_VMW_PAWAM_MAX_MOB_MEMOWY:
		vmw_fp->gb_awawe = twue;
		pawam->vawue = dev_pwiv->max_mob_pages * PAGE_SIZE;
		bweak;
	case DWM_VMW_PAWAM_MAX_MOB_SIZE:
		pawam->vawue = dev_pwiv->max_mob_size;
		bweak;
	case DWM_VMW_PAWAM_SCWEEN_TAWGET:
		pawam->vawue =
			(dev_pwiv->active_dispway_unit == vmw_du_scween_tawget);
		bweak;
	case DWM_VMW_PAWAM_DX:
		pawam->vawue = has_sm4_context(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_SM4_1:
		pawam->vawue = has_sm4_1_context(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_SM5:
		pawam->vawue = has_sm5_context(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_GW43:
		pawam->vawue = has_gw43_context(dev_pwiv);
		bweak;
	case DWM_VMW_PAWAM_DEVICE_ID:
		pawam->vawue = to_pci_dev(dev_pwiv->dwm.dev)->device;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


int vmw_get_cap_3d_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_get_3d_cap_awg *awg =
		(stwuct dwm_vmw_get_3d_cap_awg *) data;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	uint32_t size;
	void __usew *buffew = (void __usew *)((unsigned wong)(awg->buffew));
	void *bounce = NUWW;
	int wet;
	stwuct vmw_fpwiv *vmw_fp = vmw_fpwiv(fiwe_pwiv);

	if (unwikewy(awg->pad64 != 0 || awg->max_size == 0)) {
		VMW_DEBUG_USEW("Iwwegaw GET_3D_CAP awgument.\n");
		wetuwn -EINVAW;
	}

	size = vmw_devcaps_size(dev_pwiv, vmw_fp->gb_awawe);
	if (unwikewy(size == 0)) {
		DWM_EWWOW("Faiwed to figuwe out the devcaps size (no 3D).\n");
		wetuwn -ENOMEM;
	}

	if (awg->max_size < size)
		size = awg->max_size;

	bounce = vzawwoc(size);
	if (unwikewy(bounce == NUWW)) {
		DWM_EWWOW("Faiwed to awwocate bounce buffew fow 3D caps.\n");
		wetuwn -ENOMEM;
	}

	wet = vmw_devcaps_copy(dev_pwiv, vmw_fp->gb_awawe, bounce, size);
	if (unwikewy (wet != 0))
		goto out_eww;

	wet = copy_to_usew(buffew, bounce, size);
	if (wet)
		wet = -EFAUWT;
out_eww:
	vfwee(bounce);

	if (unwikewy(wet != 0))
		DWM_EWWOW("Faiwed to wepowt 3D caps info.\n");

	wetuwn wet;
}

int vmw_pwesent_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_vmw_pwesent_awg *awg =
		(stwuct dwm_vmw_pwesent_awg *)data;
	stwuct vmw_suwface *suwface;
	stwuct dwm_vmw_wect __usew *cwips_ptw;
	stwuct dwm_vmw_wect *cwips = NUWW;
	stwuct dwm_fwamebuffew *fb;
	stwuct vmw_fwamebuffew *vfb;
	stwuct vmw_wesouwce *wes;
	uint32_t num_cwips;
	int wet;

	num_cwips = awg->num_cwips;
	cwips_ptw = (stwuct dwm_vmw_wect __usew *)(unsigned wong)awg->cwips_ptw;

	if (unwikewy(num_cwips == 0))
		wetuwn 0;

	if (cwips_ptw == NUWW) {
		VMW_DEBUG_USEW("Vawiabwe cwips_ptw must be specified.\n");
		wet = -EINVAW;
		goto out_cwips;
	}

	cwips = kcawwoc(num_cwips, sizeof(*cwips), GFP_KEWNEW);
	if (cwips == NUWW) {
		DWM_EWWOW("Faiwed to awwocate cwip wect wist.\n");
		wet = -ENOMEM;
		goto out_cwips;
	}

	wet = copy_fwom_usew(cwips, cwips_ptw, num_cwips * sizeof(*cwips));
	if (wet) {
		DWM_EWWOW("Faiwed to copy cwip wects fwom usewspace.\n");
		wet = -EFAUWT;
		goto out_no_copy;
	}

	dwm_modeset_wock_aww(dev);

	fb = dwm_fwamebuffew_wookup(dev, fiwe_pwiv, awg->fb_id);
	if (!fb) {
		VMW_DEBUG_USEW("Invawid fwamebuffew id.\n");
		wet = -ENOENT;
		goto out_no_fb;
	}
	vfb = vmw_fwamebuffew_to_vfb(fb);

	wet = vmw_usew_wesouwce_wookup_handwe(dev_pwiv, tfiwe, awg->sid,
					      usew_suwface_convewtew,
					      &wes);
	if (wet)
		goto out_no_suwface;

	suwface = vmw_wes_to_swf(wes);
	wet = vmw_kms_pwesent(dev_pwiv, fiwe_pwiv,
			      vfb, suwface, awg->sid,
			      awg->dest_x, awg->dest_y,
			      cwips, num_cwips);

	/* vmw_usew_suwface_wookup takes one wef so does new_fb */
	vmw_suwface_unwefewence(&suwface);

out_no_suwface:
	dwm_fwamebuffew_put(fb);
out_no_fb:
	dwm_modeset_unwock_aww(dev);
out_no_copy:
	kfwee(cwips);
out_cwips:
	wetuwn wet;
}

int vmw_pwesent_weadback_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_vmw_pwesent_weadback_awg *awg =
		(stwuct dwm_vmw_pwesent_weadback_awg *)data;
	stwuct dwm_vmw_fence_wep __usew *usew_fence_wep =
		(stwuct dwm_vmw_fence_wep __usew *)
		(unsigned wong)awg->fence_wep;
	stwuct dwm_vmw_wect __usew *cwips_ptw;
	stwuct dwm_vmw_wect *cwips = NUWW;
	stwuct dwm_fwamebuffew *fb;
	stwuct vmw_fwamebuffew *vfb;
	uint32_t num_cwips;
	int wet;

	num_cwips = awg->num_cwips;
	cwips_ptw = (stwuct dwm_vmw_wect __usew *)(unsigned wong)awg->cwips_ptw;

	if (unwikewy(num_cwips == 0))
		wetuwn 0;

	if (cwips_ptw == NUWW) {
		VMW_DEBUG_USEW("Awgument cwips_ptw must be specified.\n");
		wet = -EINVAW;
		goto out_cwips;
	}

	cwips = kcawwoc(num_cwips, sizeof(*cwips), GFP_KEWNEW);
	if (cwips == NUWW) {
		DWM_EWWOW("Faiwed to awwocate cwip wect wist.\n");
		wet = -ENOMEM;
		goto out_cwips;
	}

	wet = copy_fwom_usew(cwips, cwips_ptw, num_cwips * sizeof(*cwips));
	if (wet) {
		DWM_EWWOW("Faiwed to copy cwip wects fwom usewspace.\n");
		wet = -EFAUWT;
		goto out_no_copy;
	}

	dwm_modeset_wock_aww(dev);

	fb = dwm_fwamebuffew_wookup(dev, fiwe_pwiv, awg->fb_id);
	if (!fb) {
		VMW_DEBUG_USEW("Invawid fwamebuffew id.\n");
		wet = -ENOENT;
		goto out_no_fb;
	}

	vfb = vmw_fwamebuffew_to_vfb(fb);
	if (!vfb->bo) {
		VMW_DEBUG_USEW("Fwamebuffew not buffew backed.\n");
		wet = -EINVAW;
		goto out_no_ttm_wock;
	}

	wet = vmw_kms_weadback(dev_pwiv, fiwe_pwiv,
			       vfb, usew_fence_wep,
			       cwips, num_cwips);

out_no_ttm_wock:
	dwm_fwamebuffew_put(fb);
out_no_fb:
	dwm_modeset_unwock_aww(dev);
out_no_copy:
	kfwee(cwips);
out_cwips:
	wetuwn wet;
}
