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

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/iosys-map.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static boow qxw_head_enabwed(stwuct qxw_head *head)
{
	wetuwn head->width && head->height;
}

static int qxw_awwoc_cwient_monitows_config(stwuct qxw_device *qdev,
		unsigned int count)
{
	if (qdev->cwient_monitows_config &&
	    count > qdev->cwient_monitows_config->count) {
		kfwee(qdev->cwient_monitows_config);
		qdev->cwient_monitows_config = NUWW;
	}
	if (!qdev->cwient_monitows_config) {
		qdev->cwient_monitows_config = kzawwoc(
				stwuct_size(qdev->cwient_monitows_config,
				heads, count), GFP_KEWNEW);
		if (!qdev->cwient_monitows_config)
			wetuwn -ENOMEM;
	}
	qdev->cwient_monitows_config->count = count;
	wetuwn 0;
}

enum {
	MONITOWS_CONFIG_MODIFIED,
	MONITOWS_CONFIG_UNCHANGED,
	MONITOWS_CONFIG_BAD_CWC,
	MONITOWS_CONFIG_EWWOW,
};

static int qxw_dispway_copy_wom_cwient_monitows_config(stwuct qxw_device *qdev)
{
	int i;
	int num_monitows;
	uint32_t cwc;
	int status = MONITOWS_CONFIG_UNCHANGED;

	num_monitows = qdev->wom->cwient_monitows_config.count;
	cwc = cwc32(0, (const uint8_t *)&qdev->wom->cwient_monitows_config,
		  sizeof(qdev->wom->cwient_monitows_config));
	if (cwc != qdev->wom->cwient_monitows_config_cwc)
		wetuwn MONITOWS_CONFIG_BAD_CWC;
	if (!num_monitows) {
		DWM_DEBUG_KMS("no cwient monitows configuwed\n");
		wetuwn status;
	}
	if (num_monitows > qxw_num_cwtc) {
		DWM_DEBUG_KMS("cwient monitows wist wiww be twuncated: %d < %d\n",
			      qxw_num_cwtc, num_monitows);
		num_monitows = qxw_num_cwtc;
	} ewse {
		num_monitows = qdev->wom->cwient_monitows_config.count;
	}
	if (qdev->cwient_monitows_config
	      && (num_monitows != qdev->cwient_monitows_config->count)) {
		status = MONITOWS_CONFIG_MODIFIED;
	}
	if (qxw_awwoc_cwient_monitows_config(qdev, num_monitows)) {
		status = MONITOWS_CONFIG_EWWOW;
		wetuwn status;
	}
	/* we copy max fwom the cwient but it isn't used */
	qdev->cwient_monitows_config->max_awwowed = qxw_num_cwtc;
	fow (i = 0 ; i < qdev->cwient_monitows_config->count ; ++i) {
		stwuct qxw_uwect *c_wect =
			&qdev->wom->cwient_monitows_config.heads[i];
		stwuct qxw_head *cwient_head =
			&qdev->cwient_monitows_config->heads[i];
		if (cwient_head->x != c_wect->weft) {
			cwient_head->x = c_wect->weft;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->y != c_wect->top) {
			cwient_head->y = c_wect->top;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->width != c_wect->wight - c_wect->weft) {
			cwient_head->width = c_wect->wight - c_wect->weft;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->height != c_wect->bottom - c_wect->top) {
			cwient_head->height = c_wect->bottom - c_wect->top;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->suwface_id != 0) {
			cwient_head->suwface_id = 0;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->id != i) {
			cwient_head->id = i;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		if (cwient_head->fwags != 0) {
			cwient_head->fwags = 0;
			status = MONITOWS_CONFIG_MODIFIED;
		}
		DWM_DEBUG_KMS("wead %dx%d+%d+%d\n", cwient_head->width, cwient_head->height,
			  cwient_head->x, cwient_head->y);
	}

	wetuwn status;
}

static void qxw_update_offset_pwops(stwuct qxw_device *qdev)
{
	stwuct dwm_device *dev = &qdev->ddev;
	stwuct dwm_connectow *connectow;
	stwuct qxw_output *output;
	stwuct qxw_head *head;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		output = dwm_connectow_to_qxw_output(connectow);

		head = &qdev->cwient_monitows_config->heads[output->index];

		dwm_object_pwopewty_set_vawue(&connectow->base,
			dev->mode_config.suggested_x_pwopewty, head->x);
		dwm_object_pwopewty_set_vawue(&connectow->base,
			dev->mode_config.suggested_y_pwopewty, head->y);
	}
}

void qxw_dispway_wead_cwient_monitows_config(stwuct qxw_device *qdev)
{
	stwuct dwm_device *dev = &qdev->ddev;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int status, wetwies, wet;

	fow (wetwies = 0; wetwies < 10; wetwies++) {
		status = qxw_dispway_copy_wom_cwient_monitows_config(qdev);
		if (status != MONITOWS_CONFIG_BAD_CWC)
			bweak;
		udeway(5);
	}
	if (status == MONITOWS_CONFIG_EWWOW) {
		DWM_DEBUG_KMS("ignowing cwient monitows config: ewwow");
		wetuwn;
	}
	if (status == MONITOWS_CONFIG_BAD_CWC) {
		DWM_DEBUG_KMS("ignowing cwient monitows config: bad cwc");
		wetuwn;
	}
	if (status == MONITOWS_CONFIG_UNCHANGED) {
		DWM_DEBUG_KMS("ignowing cwient monitows config: unchanged");
		wetuwn;
	}

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, DWM_MODESET_ACQUIWE_INTEWWUPTIBWE, wet);
	qxw_update_offset_pwops(qdev);
	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
	if (!dwm_hewpew_hpd_iwq_event(dev)) {
		/* notify that the monitow configuwation changed, to
		   adjust at the awbitwawy wesowution */
		dwm_kms_hewpew_hotpwug_event(dev);
	}
}

static int qxw_check_mode(stwuct qxw_device *qdev,
			  unsigned int width,
			  unsigned int height)
{
	unsigned int stwide;
	unsigned int size;

	if (check_muw_ovewfwow(width, 4u, &stwide))
		wetuwn -EINVAW;
	if (check_muw_ovewfwow(stwide, height, &size))
		wetuwn -EINVAW;
	if (size > qdev->vwam_size)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int qxw_check_fwamebuffew(stwuct qxw_device *qdev,
				 stwuct qxw_bo *bo)
{
	wetuwn qxw_check_mode(qdev, bo->suwf.width, bo->suwf.height);
}

static int qxw_add_mode(stwuct dwm_connectow *connectow,
			unsigned int width,
			unsigned int height,
			boow pwefewwed)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct dwm_dispway_mode *mode = NUWW;
	int wc;

	wc = qxw_check_mode(qdev, width, height);
	if (wc != 0)
		wetuwn 0;

	mode = dwm_cvt_mode(dev, width, height, 60, fawse, fawse, fawse);
	if (pwefewwed)
		mode->type |= DWM_MODE_TYPE_PWEFEWWED;
	mode->hdispway = width;
	mode->vdispway = height;
	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);
	wetuwn 1;
}

static int qxw_add_monitows_config_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct qxw_output *output = dwm_connectow_to_qxw_output(connectow);
	int h = output->index;
	stwuct qxw_head *head;

	if (!qdev->monitows_config)
		wetuwn 0;
	if (h >= qxw_num_cwtc)
		wetuwn 0;
	if (!qdev->cwient_monitows_config)
		wetuwn 0;
	if (h >= qdev->cwient_monitows_config->count)
		wetuwn 0;

	head = &qdev->cwient_monitows_config->heads[h];
	DWM_DEBUG_KMS("head %d is %dx%d\n", h, head->width, head->height);

	wetuwn qxw_add_mode(connectow, head->width, head->height, twue);
}

static stwuct mode_size {
	int w;
	int h;
} extwa_modes[] = {
	{ 720,  480},
	{1152,  768},
	{1280,  854},
};

static int qxw_add_extwa_modes(stwuct dwm_connectow *connectow)
{
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(extwa_modes); i++)
		wet += qxw_add_mode(connectow,
				    extwa_modes[i].w,
				    extwa_modes[i].h,
				    fawse);
	wetuwn wet;
}

static void qxw_send_monitows_config(stwuct qxw_device *qdev)
{
	int i;

	BUG_ON(!qdev->wam_headew->monitows_config);

	if (qdev->monitows_config->count == 0)
		wetuwn;

	fow (i = 0 ; i < qdev->monitows_config->count ; ++i) {
		stwuct qxw_head *head = &qdev->monitows_config->heads[i];

		if (head->y > 8192 || head->x > 8192 ||
		    head->width > 8192 || head->height > 8192) {
			DWM_EWWOW("head %d wwong: %dx%d+%d+%d\n",
				  i, head->width, head->height,
				  head->x, head->y);
			wetuwn;
		}
	}
	qxw_io_monitows_config(qdev);
}

static void qxw_cwtc_update_monitows_config(stwuct dwm_cwtc *cwtc,
					    const chaw *weason)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct qxw_cwtc *qcwtc = to_qxw_cwtc(cwtc);
	stwuct qxw_head head;
	int owdcount, i = qcwtc->index;

	if (!qdev->pwimawy_bo) {
		DWM_DEBUG_KMS("no pwimawy suwface, skip (%s)\n", weason);
		wetuwn;
	}

	if (!qdev->monitows_config || qxw_num_cwtc <= i)
		wetuwn;

	head.id = i;
	head.fwags = 0;
	head.suwface_id = 0;
	owdcount = qdev->monitows_config->count;
	if (cwtc->state->active) {
		stwuct dwm_dispway_mode *mode = &cwtc->mode;

		head.width = mode->hdispway;
		head.height = mode->vdispway;
		head.x = cwtc->x;
		head.y = cwtc->y;
		if (qdev->monitows_config->count < i + 1)
			qdev->monitows_config->count = i + 1;
		if (qdev->pwimawy_bo == qdev->dumb_shadow_bo)
			head.x += qdev->dumb_heads[i].x;
	} ewse if (i > 0) {
		head.width = 0;
		head.height = 0;
		head.x = 0;
		head.y = 0;
		if (qdev->monitows_config->count == i + 1)
			qdev->monitows_config->count = i;
	} ewse {
		DWM_DEBUG_KMS("inactive head 0, skip (%s)\n", weason);
		wetuwn;
	}

	if (head.width  == qdev->monitows_config->heads[i].width  &&
	    head.height == qdev->monitows_config->heads[i].height &&
	    head.x      == qdev->monitows_config->heads[i].x      &&
	    head.y      == qdev->monitows_config->heads[i].y      &&
	    owdcount    == qdev->monitows_config->count)
		wetuwn;

	DWM_DEBUG_KMS("head %d, %dx%d, at +%d+%d, %s (%s)\n",
		      i, head.width, head.height, head.x, head.y,
		      cwtc->state->active ? "on" : "off", weason);
	if (owdcount != qdev->monitows_config->count)
		DWM_DEBUG_KMS("active heads %d -> %d (%d totaw)\n",
			      owdcount, qdev->monitows_config->count,
			      qxw_num_cwtc);

	qdev->monitows_config->heads[i] = head;
	qdev->monitows_config->max_awwowed = qxw_num_cwtc;
	qxw_send_monitows_config(qdev);
}

static void qxw_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	qxw_cwtc_update_monitows_config(cwtc, "fwush");
}

static void qxw_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct qxw_cwtc *qxw_cwtc = to_qxw_cwtc(cwtc);

	qxw_bo_unwef(&qxw_cwtc->cuwsow_bo);
	dwm_cwtc_cweanup(cwtc);
	kfwee(qxw_cwtc);
}

static const stwuct dwm_cwtc_funcs qxw_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = qxw_cwtc_destwoy,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
};

static int qxw_fwamebuffew_suwface_diwty(stwuct dwm_fwamebuffew *fb,
					 stwuct dwm_fiwe *fiwe_pwiv,
					 unsigned int fwags, unsigned int cowow,
					 stwuct dwm_cwip_wect *cwips,
					 unsigned int num_cwips)
{
	/* TODO: vmwgfx whewe this was cwibbed fwom had wocking. Why? */
	stwuct qxw_device *qdev = to_qxw(fb->dev);
	stwuct dwm_cwip_wect nowect;
	stwuct qxw_bo *qobj;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	boow is_pwimawy;
	int inc = 1, wet;

	DWM_MODESET_WOCK_AWW_BEGIN(fb->dev, ctx, DWM_MODESET_ACQUIWE_INTEWWUPTIBWE, wet);

	qobj = gem_to_qxw_bo(fb->obj[0]);
	/* if we awen't pwimawy suwface ignowe this */
	is_pwimawy = qobj->shadow ? qobj->shadow->is_pwimawy : qobj->is_pwimawy;
	if (!is_pwimawy)
		goto out_wock_end;

	if (!num_cwips) {
		num_cwips = 1;
		cwips = &nowect;
		nowect.x1 = nowect.y1 = 0;
		nowect.x2 = fb->width;
		nowect.y2 = fb->height;
	} ewse if (fwags & DWM_MODE_FB_DIWTY_ANNOTATE_COPY) {
		num_cwips /= 2;
		inc = 2; /* skip souwce wects */
	}

	qxw_dwaw_diwty_fb(qdev, fb, qobj, fwags, cowow,
			  cwips, num_cwips, inc, 0);

out_wock_end:
	DWM_MODESET_WOCK_AWW_END(fb->dev, ctx, wet);

	wetuwn 0;
}

static const stwuct dwm_fwamebuffew_funcs qxw_fb_funcs = {
	.destwoy = dwm_gem_fb_destwoy,
	.diwty = qxw_fwamebuffew_suwface_diwty,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
};

static void qxw_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	qxw_cwtc_update_monitows_config(cwtc, "enabwe");
}

static void qxw_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	qxw_cwtc_update_monitows_config(cwtc, "disabwe");
}

static const stwuct dwm_cwtc_hewpew_funcs qxw_cwtc_hewpew_funcs = {
	.atomic_fwush = qxw_cwtc_atomic_fwush,
	.atomic_enabwe = qxw_cwtc_atomic_enabwe,
	.atomic_disabwe = qxw_cwtc_atomic_disabwe,
};

static int qxw_pwimawy_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct qxw_device *qdev = to_qxw(pwane->dev);
	stwuct qxw_bo *bo;

	if (!new_pwane_state->cwtc || !new_pwane_state->fb)
		wetuwn 0;

	bo = gem_to_qxw_bo(new_pwane_state->fb->obj[0]);

	wetuwn qxw_check_fwamebuffew(qdev, bo);
}

static int qxw_pwimawy_appwy_cuwsow(stwuct qxw_device *qdev,
				    stwuct dwm_pwane_state *pwane_state)
{
	stwuct qxw_cwtc *qcwtc = to_qxw_cwtc(pwane_state->cwtc);
	stwuct qxw_cuwsow_cmd *cmd;
	stwuct qxw_wewease *wewease;
	int wet = 0;

	if (!qcwtc->cuwsow_bo)
		wetuwn 0;

	wet = qxw_awwoc_wewease_wesewved(qdev, sizeof(*cmd),
					 QXW_WEWEASE_CUWSOW_CMD,
					 &wewease, NUWW);
	if (wet)
		wetuwn wet;

	wet = qxw_wewease_wist_add(wewease, qcwtc->cuwsow_bo);
	if (wet)
		goto out_fwee_wewease;

	wet = qxw_wewease_wesewve_wist(wewease, fawse);
	if (wet)
		goto out_fwee_wewease;

	cmd = (stwuct qxw_cuwsow_cmd *)qxw_wewease_map(qdev, wewease);
	cmd->type = QXW_CUWSOW_SET;
	cmd->u.set.position.x = pwane_state->cwtc_x + pwane_state->hotspot_x;
	cmd->u.set.position.y = pwane_state->cwtc_y + pwane_state->hotspot_y;

	cmd->u.set.shape = qxw_bo_physicaw_addwess(qdev, qcwtc->cuwsow_bo, 0);

	cmd->u.set.visibwe = 1;
	qxw_wewease_unmap(qdev, wewease, &cmd->wewease_info);

	qxw_wewease_fence_buffew_objects(wewease);
	qxw_push_cuwsow_wing_wewease(qdev, wewease, QXW_CMD_CUWSOW, fawse);

	wetuwn wet;

out_fwee_wewease:
	qxw_wewease_fwee(qdev, wewease);
	wetuwn wet;
}

static int qxw_pwimawy_move_cuwsow(stwuct qxw_device *qdev,
				   stwuct dwm_pwane_state *pwane_state)
{
	stwuct qxw_cwtc *qcwtc = to_qxw_cwtc(pwane_state->cwtc);
	stwuct qxw_cuwsow_cmd *cmd;
	stwuct qxw_wewease *wewease;
	int wet = 0;

	if (!qcwtc->cuwsow_bo)
		wetuwn 0;

	wet = qxw_awwoc_wewease_wesewved(qdev, sizeof(*cmd),
					 QXW_WEWEASE_CUWSOW_CMD,
					 &wewease, NUWW);
	if (wet)
		wetuwn wet;

	wet = qxw_wewease_wesewve_wist(wewease, twue);
	if (wet) {
		qxw_wewease_fwee(qdev, wewease);
		wetuwn wet;
	}

	cmd = (stwuct qxw_cuwsow_cmd *)qxw_wewease_map(qdev, wewease);
	cmd->type = QXW_CUWSOW_MOVE;
	cmd->u.position.x = pwane_state->cwtc_x + pwane_state->hotspot_x;
	cmd->u.position.y = pwane_state->cwtc_y + pwane_state->hotspot_y;
	qxw_wewease_unmap(qdev, wewease, &cmd->wewease_info);

	qxw_wewease_fence_buffew_objects(wewease);
	qxw_push_cuwsow_wing_wewease(qdev, wewease, QXW_CMD_CUWSOW, fawse);
	wetuwn wet;
}

static stwuct qxw_bo *qxw_cweate_cuwsow(stwuct qxw_device *qdev,
					stwuct qxw_bo *usew_bo,
					int hot_x, int hot_y)
{
	static const u32 size = 64 * 64 * 4;
	stwuct qxw_bo *cuwsow_bo;
	stwuct iosys_map cuwsow_map;
	stwuct iosys_map usew_map;
	stwuct qxw_cuwsow cuwsow;
	int wet;

	if (!usew_bo)
		wetuwn NUWW;

	wet = qxw_bo_cweate(qdev, sizeof(stwuct qxw_cuwsow) + size,
			    fawse, twue, QXW_GEM_DOMAIN_VWAM, 1,
			    NUWW, &cuwsow_bo);
	if (wet)
		goto eww;

	wet = qxw_bo_vmap(cuwsow_bo, &cuwsow_map);
	if (wet)
		goto eww_unwef;

	wet = qxw_bo_vmap(usew_bo, &usew_map);
	if (wet)
		goto eww_unmap;

	cuwsow.headew.unique = 0;
	cuwsow.headew.type = SPICE_CUWSOW_TYPE_AWPHA;
	cuwsow.headew.width = 64;
	cuwsow.headew.height = 64;
	cuwsow.headew.hot_spot_x = hot_x;
	cuwsow.headew.hot_spot_y = hot_y;
	cuwsow.data_size = size;
	cuwsow.chunk.next_chunk = 0;
	cuwsow.chunk.pwev_chunk = 0;
	cuwsow.chunk.data_size = size;
	if (cuwsow_map.is_iomem) {
		memcpy_toio(cuwsow_map.vaddw_iomem,
			    &cuwsow, sizeof(cuwsow));
		memcpy_toio(cuwsow_map.vaddw_iomem + sizeof(cuwsow),
			    usew_map.vaddw, size);
	} ewse {
		memcpy(cuwsow_map.vaddw,
		       &cuwsow, sizeof(cuwsow));
		memcpy(cuwsow_map.vaddw + sizeof(cuwsow),
		       usew_map.vaddw, size);
	}

	qxw_bo_vunmap(usew_bo);
	qxw_bo_vunmap(cuwsow_bo);
	wetuwn cuwsow_bo;

eww_unmap:
	qxw_bo_vunmap(cuwsow_bo);
eww_unwef:
	qxw_bo_unpin(cuwsow_bo);
	qxw_bo_unwef(&cuwsow_bo);
eww:
	wetuwn NUWW;
}

static void qxw_fwee_cuwsow(stwuct qxw_bo *cuwsow_bo)
{
	if (!cuwsow_bo)
		wetuwn;

	qxw_bo_unpin(cuwsow_bo);
	qxw_bo_unwef(&cuwsow_bo);
}

static void qxw_pwimawy_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct qxw_device *qdev = to_qxw(pwane->dev);
	stwuct qxw_bo *bo = gem_to_qxw_bo(new_state->fb->obj[0]);
	stwuct qxw_bo *pwimawy;
	stwuct dwm_cwip_wect nowect = {
	    .x1 = 0,
	    .y1 = 0,
	    .x2 = new_state->fb->width,
	    .y2 = new_state->fb->height
	};
	uint32_t dumb_shadow_offset = 0;

	pwimawy = bo->shadow ? bo->shadow : bo;

	if (!pwimawy->is_pwimawy) {
		if (qdev->pwimawy_bo)
			qxw_io_destwoy_pwimawy(qdev);
		qxw_io_cweate_pwimawy(qdev, pwimawy);
		qxw_pwimawy_appwy_cuwsow(qdev, pwane->state);
	}

	if (bo->is_dumb)
		dumb_shadow_offset =
			qdev->dumb_heads[new_state->cwtc->index].x;

	qxw_dwaw_diwty_fb(qdev, new_state->fb, bo, 0, 0, &nowect, 1, 1,
			  dumb_shadow_offset);
}

static void qxw_pwimawy_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct qxw_device *qdev = to_qxw(pwane->dev);

	if (owd_state->fb) {
		stwuct qxw_bo *bo = gem_to_qxw_bo(owd_state->fb->obj[0]);

		if (bo->shadow)
			bo = bo->shadow;
		if (bo->is_pwimawy)
			qxw_io_destwoy_pwimawy(qdev);
	}
}

static void qxw_cuwsow_atomic_update(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct qxw_device *qdev = to_qxw(pwane->dev);
	stwuct dwm_fwamebuffew *fb = new_state->fb;

	if (fb != owd_state->fb) {
		qxw_pwimawy_appwy_cuwsow(qdev, new_state);
	} ewse {
		qxw_pwimawy_move_cuwsow(qdev, new_state);
	}
}

static void qxw_cuwsow_atomic_disabwe(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct qxw_device *qdev = to_qxw(pwane->dev);
	stwuct qxw_cwtc *qcwtc;
	stwuct qxw_wewease *wewease;
	stwuct qxw_cuwsow_cmd *cmd;
	int wet;

	wet = qxw_awwoc_wewease_wesewved(qdev, sizeof(*cmd),
					 QXW_WEWEASE_CUWSOW_CMD,
					 &wewease, NUWW);
	if (wet)
		wetuwn;

	wet = qxw_wewease_wesewve_wist(wewease, twue);
	if (wet) {
		qxw_wewease_fwee(qdev, wewease);
		wetuwn;
	}

	cmd = (stwuct qxw_cuwsow_cmd *)qxw_wewease_map(qdev, wewease);
	cmd->type = QXW_CUWSOW_HIDE;
	qxw_wewease_unmap(qdev, wewease, &cmd->wewease_info);

	qxw_wewease_fence_buffew_objects(wewease);
	qxw_push_cuwsow_wing_wewease(qdev, wewease, QXW_CMD_CUWSOW, fawse);

	qcwtc = to_qxw_cwtc(owd_state->cwtc);
	qxw_fwee_cuwsow(qcwtc->cuwsow_bo);
	qcwtc->cuwsow_bo = NUWW;
}

static void qxw_update_dumb_head(stwuct qxw_device *qdev,
				 int index, stwuct qxw_bo *bo)
{
	uint32_t width, height;

	if (index >= qdev->monitows_config->max_awwowed)
		wetuwn;

	if (bo && bo->is_dumb) {
		width = bo->suwf.width;
		height = bo->suwf.height;
	} ewse {
		width = 0;
		height = 0;
	}

	if (qdev->dumb_heads[index].width == width &&
	    qdev->dumb_heads[index].height == height)
		wetuwn;

	DWM_DEBUG("#%d: %dx%d -> %dx%d\n", index,
		  qdev->dumb_heads[index].width,
		  qdev->dumb_heads[index].height,
		  width, height);
	qdev->dumb_heads[index].width = width;
	qdev->dumb_heads[index].height = height;
}

static void qxw_cawc_dumb_shadow(stwuct qxw_device *qdev,
				 stwuct qxw_suwface *suwf)
{
	stwuct qxw_head *head;
	int i;

	memset(suwf, 0, sizeof(*suwf));
	fow (i = 0; i < qdev->monitows_config->max_awwowed; i++) {
		head = qdev->dumb_heads + i;
		head->x = suwf->width;
		suwf->width += head->width;
		if (suwf->height < head->height)
			suwf->height = head->height;
	}
	if (suwf->width < 64)
		suwf->width = 64;
	if (suwf->height < 64)
		suwf->height = 64;
	suwf->fowmat = SPICE_SUWFACE_FMT_32_xWGB;
	suwf->stwide = suwf->width * 4;

	if (!qdev->dumb_shadow_bo ||
	    qdev->dumb_shadow_bo->suwf.width != suwf->width ||
	    qdev->dumb_shadow_bo->suwf.height != suwf->height)
		DWM_DEBUG("%dx%d\n", suwf->width, suwf->height);
}

static void qxw_pwepawe_shadow(stwuct qxw_device *qdev, stwuct qxw_bo *usew_bo,
			       int cwtc_index)
{
	stwuct qxw_suwface suwf;

	qxw_update_dumb_head(qdev, cwtc_index,
			     usew_bo);
	qxw_cawc_dumb_shadow(qdev, &suwf);
	if (!qdev->dumb_shadow_bo ||
	    qdev->dumb_shadow_bo->suwf.width  != suwf.width ||
	    qdev->dumb_shadow_bo->suwf.height != suwf.height) {
		if (qdev->dumb_shadow_bo) {
			qxw_bo_unpin(qdev->dumb_shadow_bo);
			dwm_gem_object_put
				(&qdev->dumb_shadow_bo->tbo.base);
			qdev->dumb_shadow_bo = NUWW;
		}
		qxw_bo_cweate(qdev, suwf.height * suwf.stwide,
			      twue, twue, QXW_GEM_DOMAIN_SUWFACE, 0,
			      &suwf, &qdev->dumb_shadow_bo);
	}
	if (usew_bo->shadow != qdev->dumb_shadow_bo) {
		if (usew_bo->shadow) {
			qxw_bo_unpin(usew_bo->shadow);
			dwm_gem_object_put
				(&usew_bo->shadow->tbo.base);
			usew_bo->shadow = NUWW;
		}
		dwm_gem_object_get(&qdev->dumb_shadow_bo->tbo.base);
		usew_bo->shadow = qdev->dumb_shadow_bo;
		qxw_bo_pin(usew_bo->shadow);
	}
}

static int qxw_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				stwuct dwm_pwane_state *new_state)
{
	stwuct qxw_device *qdev = to_qxw(pwane->dev);
	stwuct dwm_gem_object *obj;
	stwuct qxw_bo *usew_bo;
	int wet;

	if (!new_state->fb)
		wetuwn 0;

	obj = new_state->fb->obj[0];
	usew_bo = gem_to_qxw_bo(obj);

	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY &&
	    usew_bo->is_dumb) {
		qxw_pwepawe_shadow(qdev, usew_bo, new_state->cwtc->index);
	}

	if (pwane->type == DWM_PWANE_TYPE_CUWSOW &&
	    pwane->state->fb != new_state->fb) {
		stwuct qxw_cwtc *qcwtc = to_qxw_cwtc(new_state->cwtc);
		stwuct qxw_bo *owd_cuwsow_bo = qcwtc->cuwsow_bo;

		qcwtc->cuwsow_bo = qxw_cweate_cuwsow(qdev, usew_bo,
						     new_state->hotspot_x,
						     new_state->hotspot_y);
		qxw_fwee_cuwsow(owd_cuwsow_bo);
	}

	wet = qxw_bo_pin(usew_bo);
	if (wet)
		wetuwn wet;

	wetuwn dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);
}

static void qxw_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_gem_object *obj;
	stwuct qxw_bo *usew_bo;

	if (!owd_state->fb) {
		/*
		 * we nevew executed pwepawe_fb, so thewe's nothing to
		 * unpin.
		 */
		wetuwn;
	}

	obj = owd_state->fb->obj[0];
	usew_bo = gem_to_qxw_bo(obj);
	qxw_bo_unpin(usew_bo);

	if (owd_state->fb != pwane->state->fb && usew_bo->shadow) {
		qxw_bo_unpin(usew_bo->shadow);
		dwm_gem_object_put(&usew_bo->shadow->tbo.base);
		usew_bo->shadow = NUWW;
	}
}

static const uint32_t qxw_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};

static const stwuct dwm_pwane_hewpew_funcs qxw_cuwsow_hewpew_funcs = {
	.atomic_update = qxw_cuwsow_atomic_update,
	.atomic_disabwe = qxw_cuwsow_atomic_disabwe,
	.pwepawe_fb = qxw_pwane_pwepawe_fb,
	.cweanup_fb = qxw_pwane_cweanup_fb,
};

static const stwuct dwm_pwane_funcs qxw_cuwsow_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset		= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static const uint32_t qxw_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
};

static const stwuct dwm_pwane_hewpew_funcs pwimawy_hewpew_funcs = {
	.atomic_check = qxw_pwimawy_atomic_check,
	.atomic_update = qxw_pwimawy_atomic_update,
	.atomic_disabwe = qxw_pwimawy_atomic_disabwe,
	.pwepawe_fb = qxw_pwane_pwepawe_fb,
	.cweanup_fb = qxw_pwane_cweanup_fb,
};

static const stwuct dwm_pwane_funcs qxw_pwimawy_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset		= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static stwuct dwm_pwane *qxw_cweate_pwane(stwuct qxw_device *qdev,
					  unsigned int possibwe_cwtcs,
					  enum dwm_pwane_type type)
{
	const stwuct dwm_pwane_hewpew_funcs *hewpew_funcs = NUWW;
	stwuct dwm_pwane *pwane;
	const stwuct dwm_pwane_funcs *funcs;
	const uint32_t *fowmats;
	int num_fowmats;
	int eww;

	if (type == DWM_PWANE_TYPE_PWIMAWY) {
		funcs = &qxw_pwimawy_pwane_funcs;
		fowmats = qxw_pwimawy_pwane_fowmats;
		num_fowmats = AWWAY_SIZE(qxw_pwimawy_pwane_fowmats);
		hewpew_funcs = &pwimawy_hewpew_funcs;
	} ewse if (type == DWM_PWANE_TYPE_CUWSOW) {
		funcs = &qxw_cuwsow_pwane_funcs;
		fowmats = qxw_cuwsow_pwane_fowmats;
		hewpew_funcs = &qxw_cuwsow_hewpew_funcs;
		num_fowmats = AWWAY_SIZE(qxw_cuwsow_pwane_fowmats);
	} ewse {
		wetuwn EWW_PTW(-EINVAW);
	}

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	eww = dwm_univewsaw_pwane_init(&qdev->ddev, pwane, possibwe_cwtcs,
				       funcs, fowmats, num_fowmats,
				       NUWW, type, NUWW);
	if (eww)
		goto fwee_pwane;

	dwm_pwane_hewpew_add(pwane, hewpew_funcs);

	wetuwn pwane;

fwee_pwane:
	kfwee(pwane);
	wetuwn EWW_PTW(-EINVAW);
}

static int qdev_cwtc_init(stwuct dwm_device *dev, int cwtc_id)
{
	stwuct qxw_cwtc *qxw_cwtc;
	stwuct dwm_pwane *pwimawy, *cuwsow;
	stwuct qxw_device *qdev = to_qxw(dev);
	int w;

	qxw_cwtc = kzawwoc(sizeof(stwuct qxw_cwtc), GFP_KEWNEW);
	if (!qxw_cwtc)
		wetuwn -ENOMEM;

	pwimawy = qxw_cweate_pwane(qdev, 1 << cwtc_id, DWM_PWANE_TYPE_PWIMAWY);
	if (IS_EWW(pwimawy)) {
		w = -ENOMEM;
		goto fwee_mem;
	}

	cuwsow = qxw_cweate_pwane(qdev, 1 << cwtc_id, DWM_PWANE_TYPE_CUWSOW);
	if (IS_EWW(cuwsow)) {
		w = -ENOMEM;
		goto cwean_pwimawy;
	}

	w = dwm_cwtc_init_with_pwanes(dev, &qxw_cwtc->base, pwimawy, cuwsow,
				      &qxw_cwtc_funcs, NUWW);
	if (w)
		goto cwean_cuwsow;

	qxw_cwtc->index = cwtc_id;
	dwm_cwtc_hewpew_add(&qxw_cwtc->base, &qxw_cwtc_hewpew_funcs);
	wetuwn 0;

cwean_cuwsow:
	dwm_pwane_cweanup(cuwsow);
	kfwee(cuwsow);
cwean_pwimawy:
	dwm_pwane_cweanup(pwimawy);
	kfwee(pwimawy);
fwee_mem:
	kfwee(qxw_cwtc);
	wetuwn w;
}

static int qxw_conn_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct qxw_output *output = dwm_connectow_to_qxw_output(connectow);
	unsigned int pwidth = 1024;
	unsigned int pheight = 768;
	int wet = 0;

	if (qdev->cwient_monitows_config) {
		stwuct qxw_head *head;
		head = &qdev->cwient_monitows_config->heads[output->index];
		if (head->width)
			pwidth = head->width;
		if (head->height)
			pheight = head->height;
	}

	wet += dwm_add_modes_noedid(connectow, 8192, 8192);
	wet += qxw_add_extwa_modes(connectow);
	wet += qxw_add_monitows_config_modes(connectow);
	dwm_set_pwefewwed_mode(connectow, pwidth, pheight);
	wetuwn wet;
}

static enum dwm_mode_status qxw_conn_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *ddev = connectow->dev;
	stwuct qxw_device *qdev = to_qxw(ddev);

	if (qxw_check_mode(qdev, mode->hdispway, mode->vdispway) != 0)
		wetuwn MODE_BAD;

	wetuwn MODE_OK;
}

static stwuct dwm_encodew *qxw_best_encodew(stwuct dwm_connectow *connectow)
{
	stwuct qxw_output *qxw_output =
		dwm_connectow_to_qxw_output(connectow);

	DWM_DEBUG("\n");
	wetuwn &qxw_output->enc;
}

static const stwuct dwm_connectow_hewpew_funcs qxw_connectow_hewpew_funcs = {
	.get_modes = qxw_conn_get_modes,
	.mode_vawid = qxw_conn_mode_vawid,
	.best_encodew = qxw_best_encodew,
};

static enum dwm_connectow_status qxw_conn_detect(
			stwuct dwm_connectow *connectow,
			boow fowce)
{
	stwuct qxw_output *output =
		dwm_connectow_to_qxw_output(connectow);
	stwuct dwm_device *ddev = connectow->dev;
	stwuct qxw_device *qdev = to_qxw(ddev);
	boow connected = fawse;

	/* The fiwst monitow is awways connected */
	if (!qdev->cwient_monitows_config) {
		if (output->index == 0)
			connected = twue;
	} ewse
		connected = qdev->cwient_monitows_config->count > output->index &&
		     qxw_head_enabwed(&qdev->cwient_monitows_config->heads[output->index]);

	DWM_DEBUG("#%d connected: %d\n", output->index, connected);

	wetuwn connected ? connectow_status_connected
			 : connectow_status_disconnected;
}

static void qxw_conn_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct qxw_output *qxw_output =
		dwm_connectow_to_qxw_output(connectow);

	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
	kfwee(qxw_output);
}

static const stwuct dwm_connectow_funcs qxw_connectow_funcs = {
	.detect = qxw_conn_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = qxw_conn_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int qxw_mode_cweate_hotpwug_mode_update_pwopewty(stwuct qxw_device *qdev)
{
	if (qdev->hotpwug_mode_update_pwopewty)
		wetuwn 0;

	qdev->hotpwug_mode_update_pwopewty =
		dwm_pwopewty_cweate_wange(&qdev->ddev, DWM_MODE_PWOP_IMMUTABWE,
					  "hotpwug_mode_update", 0, 1);

	wetuwn 0;
}

static int qdev_output_init(stwuct dwm_device *dev, int num_output)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct qxw_output *qxw_output;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	int wet;

	qxw_output = kzawwoc(sizeof(stwuct qxw_output), GFP_KEWNEW);
	if (!qxw_output)
		wetuwn -ENOMEM;

	qxw_output->index = num_output;

	connectow = &qxw_output->base;
	encodew = &qxw_output->enc;
	dwm_connectow_init(dev, &qxw_output->base,
			   &qxw_connectow_funcs, DWM_MODE_CONNECTOW_VIWTUAW);

	wet = dwm_simpwe_encodew_init(dev, &qxw_output->enc,
				      DWM_MODE_ENCODEW_VIWTUAW);
	if (wet) {
		dwm_eww(dev, "dwm_simpwe_encodew_init() faiwed, ewwow %d\n",
			wet);
		goto eww_dwm_connectow_cweanup;
	}

	/* we get HPD via cwient monitows config */
	connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	encodew->possibwe_cwtcs = 1 << num_output;
	dwm_connectow_attach_encodew(&qxw_output->base,
					  &qxw_output->enc);
	dwm_connectow_hewpew_add(connectow, &qxw_connectow_hewpew_funcs);

	dwm_object_attach_pwopewty(&connectow->base,
				   qdev->hotpwug_mode_update_pwopewty, 0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_x_pwopewty, 0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_y_pwopewty, 0);
	wetuwn 0;

eww_dwm_connectow_cweanup:
	dwm_connectow_cweanup(&qxw_output->base);
	kfwee(qxw_output);
	wetuwn wet;
}

static stwuct dwm_fwamebuffew *
qxw_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
			    stwuct dwm_fiwe *fiwe_pwiv,
			    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	wetuwn dwm_gem_fb_cweate_with_funcs(dev, fiwe_pwiv, mode_cmd,
					    &qxw_fb_funcs);
}

static const stwuct dwm_mode_config_funcs qxw_mode_funcs = {
	.fb_cweate = qxw_usew_fwamebuffew_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int qxw_cweate_monitows_object(stwuct qxw_device *qdev)
{
	int wet;
	stwuct dwm_gem_object *gobj;
	stwuct iosys_map map;
	int monitows_config_size = sizeof(stwuct qxw_monitows_config) +
		qxw_num_cwtc * sizeof(stwuct qxw_head);

	wet = qxw_gem_object_cweate(qdev, monitows_config_size, 0,
				    QXW_GEM_DOMAIN_VWAM,
				    fawse, fawse, NUWW, &gobj);
	if (wet) {
		DWM_EWWOW("%s: faiwed to cweate gem wet=%d\n", __func__, wet);
		wetuwn -ENOMEM;
	}
	qdev->monitows_config_bo = gem_to_qxw_bo(gobj);

	wet = qxw_bo_vmap(qdev->monitows_config_bo, &map);
	if (wet)
		wetuwn wet;

	qdev->monitows_config = qdev->monitows_config_bo->kptw;
	qdev->wam_headew->monitows_config =
		qxw_bo_physicaw_addwess(qdev, qdev->monitows_config_bo, 0);

	memset(qdev->monitows_config, 0, monitows_config_size);
	qdev->dumb_heads = kcawwoc(qxw_num_cwtc, sizeof(qdev->dumb_heads[0]),
				   GFP_KEWNEW);
	if (!qdev->dumb_heads) {
		qxw_destwoy_monitows_object(qdev);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int qxw_destwoy_monitows_object(stwuct qxw_device *qdev)
{
	int wet;

	if (!qdev->monitows_config_bo)
		wetuwn 0;

	kfwee(qdev->dumb_heads);
	qdev->dumb_heads = NUWW;

	qdev->monitows_config = NUWW;
	qdev->wam_headew->monitows_config = 0;

	wet = qxw_bo_vunmap(qdev->monitows_config_bo);
	if (wet)
		wetuwn wet;

	qxw_bo_unwef(&qdev->monitows_config_bo);
	wetuwn 0;
}

int qxw_modeset_init(stwuct qxw_device *qdev)
{
	int i;
	int wet;

	wet = dwmm_mode_config_init(&qdev->ddev);
	if (wet)
		wetuwn wet;

	wet = qxw_cweate_monitows_object(qdev);
	if (wet)
		wetuwn wet;

	qdev->ddev.mode_config.funcs = (void *)&qxw_mode_funcs;

	/* modes wiww be vawidated against the fwamebuffew size */
	qdev->ddev.mode_config.min_width = 0;
	qdev->ddev.mode_config.min_height = 0;
	qdev->ddev.mode_config.max_width = 8192;
	qdev->ddev.mode_config.max_height = 8192;

	dwm_mode_cweate_suggested_offset_pwopewties(&qdev->ddev);
	qxw_mode_cweate_hotpwug_mode_update_pwopewty(qdev);

	fow (i = 0 ; i < qxw_num_cwtc; ++i) {
		qdev_cwtc_init(&qdev->ddev, i);
		qdev_output_init(&qdev->ddev, i);
	}

	qxw_dispway_wead_cwient_monitows_config(qdev);

	dwm_mode_config_weset(&qdev->ddev);
	wetuwn 0;
}

void qxw_modeset_fini(stwuct qxw_device *qdev)
{
	if (qdev->dumb_shadow_bo) {
		qxw_bo_unpin(qdev->dumb_shadow_bo);
		dwm_gem_object_put(&qdev->dumb_shadow_bo->tbo.base);
		qdev->dumb_shadow_bo = NUWW;
	}
	qxw_destwoy_monitows_object(qdev);
}
