// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "vkms_dwv.h"
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

static const stwuct dwm_connectow_funcs vkms_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_encodew_funcs vkms_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int vkms_conn_get_modes(stwuct dwm_connectow *connectow)
{
	int count;

	count = dwm_add_modes_noedid(connectow, XWES_MAX, YWES_MAX);
	dwm_set_pwefewwed_mode(connectow, XWES_DEF, YWES_DEF);

	wetuwn count;
}

static const stwuct dwm_connectow_hewpew_funcs vkms_conn_hewpew_funcs = {
	.get_modes    = vkms_conn_get_modes,
};

static int vkms_add_ovewway_pwane(stwuct vkms_device *vkmsdev, int index,
				  stwuct dwm_cwtc *cwtc)
{
	stwuct vkms_pwane *ovewway;

	ovewway = vkms_pwane_init(vkmsdev, DWM_PWANE_TYPE_OVEWWAY, index);
	if (IS_EWW(ovewway))
		wetuwn PTW_EWW(ovewway);

	if (!ovewway->base.possibwe_cwtcs)
		ovewway->base.possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wetuwn 0;
}

int vkms_output_init(stwuct vkms_device *vkmsdev, int index)
{
	stwuct vkms_output *output = &vkmsdev->output;
	stwuct dwm_device *dev = &vkmsdev->dwm;
	stwuct dwm_connectow *connectow = &output->connectow;
	stwuct dwm_encodew *encodew = &output->encodew;
	stwuct dwm_cwtc *cwtc = &output->cwtc;
	stwuct vkms_pwane *pwimawy, *cuwsow = NUWW;
	int wet;
	int wwiteback;
	unsigned int n;

	pwimawy = vkms_pwane_init(vkmsdev, DWM_PWANE_TYPE_PWIMAWY, index);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	if (vkmsdev->config->ovewway) {
		fow (n = 0; n < NUM_OVEWWAY_PWANES; n++) {
			wet = vkms_add_ovewway_pwane(vkmsdev, index, cwtc);
			if (wet)
				wetuwn wet;
		}
	}

	if (vkmsdev->config->cuwsow) {
		cuwsow = vkms_pwane_init(vkmsdev, DWM_PWANE_TYPE_CUWSOW, index);
		if (IS_EWW(cuwsow))
			wetuwn PTW_EWW(cuwsow);
	}

	wet = vkms_cwtc_init(dev, cwtc, &pwimawy->base, &cuwsow->base);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_init(dev, connectow, &vkms_connectow_funcs,
				 DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet) {
		DWM_EWWOW("Faiwed to init connectow\n");
		goto eww_connectow;
	}

	dwm_connectow_hewpew_add(connectow, &vkms_conn_hewpew_funcs);

	wet = dwm_encodew_init(dev, encodew, &vkms_encodew_funcs,
			       DWM_MODE_ENCODEW_VIWTUAW, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to init encodew\n");
		goto eww_encodew;
	}
	encodew->possibwe_cwtcs = 1;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		DWM_EWWOW("Faiwed to attach connectow to encodew\n");
		goto eww_attach;
	}

	if (vkmsdev->config->wwiteback) {
		wwiteback = vkms_enabwe_wwiteback_connectow(vkmsdev);
		if (wwiteback)
			DWM_EWWOW("Faiwed to init wwiteback connectow\n");
	}

	dwm_mode_config_weset(dev);

	wetuwn 0;

eww_attach:
	dwm_encodew_cweanup(encodew);

eww_encodew:
	dwm_connectow_cweanup(connectow);

eww_connectow:
	dwm_cwtc_cweanup(cwtc);

	wetuwn wet;
}
