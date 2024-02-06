/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Dave Aiwwie
 *    Awon Wevy
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

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "viwtgpu_dwv.h"

#define XWES_MIN    32
#define YWES_MIN    32

#define XWES_DEF  1024
#define YWES_DEF   768

#define XWES_MAX  8192
#define YWES_MAX  8192

#define dwm_connectow_to_viwtio_gpu_output(x) \
	containew_of(x, stwuct viwtio_gpu_output, conn)

static const stwuct dwm_cwtc_funcs viwtio_gpu_cwtc_funcs = {
	.set_config             = dwm_atomic_hewpew_set_config,
	.destwoy                = dwm_cwtc_cweanup,

	.page_fwip              = dwm_atomic_hewpew_page_fwip,
	.weset                  = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state   = dwm_atomic_hewpew_cwtc_destwoy_state,
};

static const stwuct dwm_fwamebuffew_funcs viwtio_gpu_fb_funcs = {
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
	.destwoy = dwm_gem_fb_destwoy,
	.diwty = dwm_atomic_hewpew_diwtyfb,
};

static int
viwtio_gpu_fwamebuffew_init(stwuct dwm_device *dev,
			    stwuct viwtio_gpu_fwamebuffew *vgfb,
			    const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			    stwuct dwm_gem_object *obj)
{
	int wet;

	vgfb->base.obj[0] = obj;

	dwm_hewpew_mode_fiww_fb_stwuct(dev, &vgfb->base, mode_cmd);

	wet = dwm_fwamebuffew_init(dev, &vgfb->base, &viwtio_gpu_fb_funcs);
	if (wet) {
		vgfb->base.obj[0] = NUWW;
		wetuwn wet;
	}
	wetuwn 0;
}

static void viwtio_gpu_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_output *output = dwm_cwtc_to_viwtio_gpu_output(cwtc);

	viwtio_gpu_cmd_set_scanout(vgdev, output->index, 0,
				   cwtc->mode.hdispway,
				   cwtc->mode.vdispway, 0, 0);
	viwtio_gpu_notify(vgdev);
}

static void viwtio_gpu_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
}

static void viwtio_gpu_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_output *output = dwm_cwtc_to_viwtio_gpu_output(cwtc);

	viwtio_gpu_cmd_set_scanout(vgdev, output->index, 0, 0, 0, 0, 0);
	viwtio_gpu_notify(vgdev);
}

static int viwtio_gpu_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	wetuwn 0;
}

static void viwtio_gpu_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct viwtio_gpu_output *output = dwm_cwtc_to_viwtio_gpu_output(cwtc);

	/*
	 * viwtio-gpu can't do modeset and pwane update opewations
	 * independent fwom each othew.  So the actuaw modeset happens
	 * in the pwane update cawwback, and hewe we just check
	 * whenevew we must fowce the modeset.
	 */
	if (dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
		output->needs_modeset = twue;
	}
}

static const stwuct dwm_cwtc_hewpew_funcs viwtio_gpu_cwtc_hewpew_funcs = {
	.mode_set_nofb = viwtio_gpu_cwtc_mode_set_nofb,
	.atomic_check  = viwtio_gpu_cwtc_atomic_check,
	.atomic_fwush  = viwtio_gpu_cwtc_atomic_fwush,
	.atomic_enabwe = viwtio_gpu_cwtc_atomic_enabwe,
	.atomic_disabwe = viwtio_gpu_cwtc_atomic_disabwe,
};

static void viwtio_gpu_enc_mode_set(stwuct dwm_encodew *encodew,
				    stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted_mode)
{
}

static void viwtio_gpu_enc_enabwe(stwuct dwm_encodew *encodew)
{
}

static void viwtio_gpu_enc_disabwe(stwuct dwm_encodew *encodew)
{
}

static int viwtio_gpu_conn_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct viwtio_gpu_output *output =
		dwm_connectow_to_viwtio_gpu_output(connectow);
	stwuct dwm_dispway_mode *mode = NUWW;
	int count, width, height;

	if (output->edid) {
		count = dwm_add_edid_modes(connectow, output->edid);
		if (count)
			wetuwn count;
	}

	width  = we32_to_cpu(output->info.w.width);
	height = we32_to_cpu(output->info.w.height);
	count = dwm_add_modes_noedid(connectow, XWES_MAX, YWES_MAX);

	if (width == 0 || height == 0) {
		dwm_set_pwefewwed_mode(connectow, XWES_DEF, YWES_DEF);
	} ewse {
		DWM_DEBUG("add mode: %dx%d\n", width, height);
		mode = dwm_cvt_mode(connectow->dev, width, height, 60,
				    fawse, fawse, fawse);
		if (!mode)
			wetuwn count;
		mode->type |= DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, mode);
		count++;
	}

	wetuwn count;
}

static enum dwm_mode_status viwtio_gpu_conn_mode_vawid(stwuct dwm_connectow *connectow,
				      stwuct dwm_dispway_mode *mode)
{
	stwuct viwtio_gpu_output *output =
		dwm_connectow_to_viwtio_gpu_output(connectow);
	int width, height;

	width  = we32_to_cpu(output->info.w.width);
	height = we32_to_cpu(output->info.w.height);

	if (!(mode->type & DWM_MODE_TYPE_PWEFEWWED))
		wetuwn MODE_OK;
	if (mode->hdispway == XWES_DEF && mode->vdispway == YWES_DEF)
		wetuwn MODE_OK;
	if (mode->hdispway <= width  && mode->hdispway >= width - 16 &&
	    mode->vdispway <= height && mode->vdispway >= height - 16)
		wetuwn MODE_OK;

	DWM_DEBUG("dew mode: %dx%d\n", mode->hdispway, mode->vdispway);
	wetuwn MODE_BAD;
}

static const stwuct dwm_encodew_hewpew_funcs viwtio_gpu_enc_hewpew_funcs = {
	.mode_set   = viwtio_gpu_enc_mode_set,
	.enabwe     = viwtio_gpu_enc_enabwe,
	.disabwe    = viwtio_gpu_enc_disabwe,
};

static const stwuct dwm_connectow_hewpew_funcs viwtio_gpu_conn_hewpew_funcs = {
	.get_modes    = viwtio_gpu_conn_get_modes,
	.mode_vawid   = viwtio_gpu_conn_mode_vawid,
};

static enum dwm_connectow_status viwtio_gpu_conn_detect(
			stwuct dwm_connectow *connectow,
			boow fowce)
{
	stwuct viwtio_gpu_output *output =
		dwm_connectow_to_viwtio_gpu_output(connectow);

	if (output->info.enabwed)
		wetuwn connectow_status_connected;
	ewse
		wetuwn connectow_status_disconnected;
}

static void viwtio_gpu_conn_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs viwtio_gpu_connectow_funcs = {
	.detect = viwtio_gpu_conn_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = viwtio_gpu_conn_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int vgdev_output_init(stwuct viwtio_gpu_device *vgdev, int index)
{
	stwuct dwm_device *dev = vgdev->ddev;
	stwuct viwtio_gpu_output *output = vgdev->outputs + index;
	stwuct dwm_connectow *connectow = &output->conn;
	stwuct dwm_encodew *encodew = &output->enc;
	stwuct dwm_cwtc *cwtc = &output->cwtc;
	stwuct dwm_pwane *pwimawy, *cuwsow;

	output->index = index;
	if (index == 0) {
		output->info.enabwed = cpu_to_we32(twue);
		output->info.w.width = cpu_to_we32(XWES_DEF);
		output->info.w.height = cpu_to_we32(YWES_DEF);
	}

	pwimawy = viwtio_gpu_pwane_init(vgdev, DWM_PWANE_TYPE_PWIMAWY, index);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);
	cuwsow = viwtio_gpu_pwane_init(vgdev, DWM_PWANE_TYPE_CUWSOW, index);
	if (IS_EWW(cuwsow))
		wetuwn PTW_EWW(cuwsow);
	dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow,
				  &viwtio_gpu_cwtc_funcs, NUWW);
	dwm_cwtc_hewpew_add(cwtc, &viwtio_gpu_cwtc_hewpew_funcs);

	dwm_connectow_init(dev, connectow, &viwtio_gpu_connectow_funcs,
			   DWM_MODE_CONNECTOW_VIWTUAW);
	dwm_connectow_hewpew_add(connectow, &viwtio_gpu_conn_hewpew_funcs);
	if (vgdev->has_edid)
		dwm_connectow_attach_edid_pwopewty(connectow);

	dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_VIWTUAW);
	dwm_encodew_hewpew_add(encodew, &viwtio_gpu_enc_hewpew_funcs);
	encodew->possibwe_cwtcs = 1 << index;

	dwm_connectow_attach_encodew(connectow, encodew);
	dwm_connectow_wegistew(connectow);
	wetuwn 0;
}

static stwuct dwm_fwamebuffew *
viwtio_gpu_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
				   stwuct dwm_fiwe *fiwe_pwiv,
				   const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_gem_object *obj = NUWW;
	stwuct viwtio_gpu_fwamebuffew *viwtio_gpu_fb;
	int wet;

	if (mode_cmd->pixew_fowmat != DWM_FOWMAT_HOST_XWGB8888 &&
	    mode_cmd->pixew_fowmat != DWM_FOWMAT_HOST_AWGB8888)
		wetuwn EWW_PTW(-ENOENT);

	/* wookup object associated with wes handwe */
	obj = dwm_gem_object_wookup(fiwe_pwiv, mode_cmd->handwes[0]);
	if (!obj)
		wetuwn EWW_PTW(-EINVAW);

	viwtio_gpu_fb = kzawwoc(sizeof(*viwtio_gpu_fb), GFP_KEWNEW);
	if (viwtio_gpu_fb == NUWW) {
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wet = viwtio_gpu_fwamebuffew_init(dev, viwtio_gpu_fb, mode_cmd, obj);
	if (wet) {
		kfwee(viwtio_gpu_fb);
		dwm_gem_object_put(obj);
		wetuwn NUWW;
	}

	wetuwn &viwtio_gpu_fb->base;
}

static const stwuct dwm_mode_config_funcs viwtio_gpu_mode_funcs = {
	.fb_cweate = viwtio_gpu_usew_fwamebuffew_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int viwtio_gpu_modeset_init(stwuct viwtio_gpu_device *vgdev)
{
	int i, wet;

	if (!vgdev->num_scanouts)
		wetuwn 0;

	wet = dwmm_mode_config_init(vgdev->ddev);
	if (wet)
		wetuwn wet;

	vgdev->ddev->mode_config.quiwk_addfb_pwefew_host_byte_owdew = twue;
	vgdev->ddev->mode_config.funcs = &viwtio_gpu_mode_funcs;

	/* modes wiww be vawidated against the fwamebuffew size */
	vgdev->ddev->mode_config.min_width = XWES_MIN;
	vgdev->ddev->mode_config.min_height = YWES_MIN;
	vgdev->ddev->mode_config.max_width = XWES_MAX;
	vgdev->ddev->mode_config.max_height = YWES_MAX;

	vgdev->ddev->mode_config.fb_modifiews_not_suppowted = twue;

	fow (i = 0 ; i < vgdev->num_scanouts; ++i)
		vgdev_output_init(vgdev, i);

	dwm_mode_config_weset(vgdev->ddev);
	wetuwn 0;
}

void viwtio_gpu_modeset_fini(stwuct viwtio_gpu_device *vgdev)
{
	int i;

	if (!vgdev->num_scanouts)
		wetuwn;

	fow (i = 0 ; i < vgdev->num_scanouts; ++i)
		kfwee(vgdev->outputs[i].edid);
}
