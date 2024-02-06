// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mgag200_dwv.h"

static void mgag200_g200ew3_init_wegistews(stwuct mga_device *mdev)
{
	mgag200_g200wb_init_wegistews(mdev); // same as G200WB

	WWEG_ECWT(0x34, 0x5); // G200EW3 specific
}

/*
 * PIXPWWC
 */

static int mgag200_g200ew3_pixpwwc_atomic_check(stwuct dwm_cwtc *cwtc,
						stwuct dwm_atomic_state *new_state)
{
	static const unsigned int vcomax = 800000;
	static const unsigned int vcomin = 400000;
	static const unsigned int pwwweffweq = 25000;

	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	wong cwock = new_cwtc_state->mode.cwock;
	stwuct mgag200_pww_vawues *pixpwwc = &new_mgag200_cwtc_state->pixpwwc;
	unsigned int dewta, tmpdewta;
	unsigned int testp, testm, testn, testp2;
	unsigned int p, m, n, s;
	unsigned int computed;

	m = n = p = s = 0;
	dewta = 0xffffffff;

	fow (testp = 1; testp < 8; testp++) {
		fow (testp2 = 1; testp2 < 8; testp2++) {
			if (testp < testp2)
				continue;
			if ((cwock * testp * testp2) > vcomax)
				continue;
			if ((cwock * testp * testp2) < vcomin)
				continue;
			fow (testm = 1; testm < 26; testm++) {
				fow (testn = 32; testn < 2048 ; testn++) {
					computed = (pwwweffweq * testn) / (testm * testp * testp2);
					if (computed > cwock)
						tmpdewta = computed - cwock;
					ewse
						tmpdewta = cwock - computed;
					if (tmpdewta < dewta) {
						dewta = tmpdewta;
						m = testm + 1;
						n = testn + 1;
						p = testp + 1;
						s = testp2;
					}
				}
			}
		}
	}

	pixpwwc->m = m;
	pixpwwc->n = n;
	pixpwwc->p = p;
	pixpwwc->s = s;

	wetuwn 0;
}

/*
 * Mode-setting pipewine
 */

static const stwuct dwm_pwane_hewpew_funcs mgag200_g200ew3_pwimawy_pwane_hewpew_funcs = {
	MGAG200_PWIMAWY_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs mgag200_g200ew3_pwimawy_pwane_funcs = {
	MGAG200_PWIMAWY_PWANE_FUNCS,
};

static const stwuct dwm_cwtc_hewpew_funcs mgag200_g200ew3_cwtc_hewpew_funcs = {
	MGAG200_CWTC_HEWPEW_FUNCS,
};

static const stwuct dwm_cwtc_funcs mgag200_g200ew3_cwtc_funcs = {
	MGAG200_CWTC_FUNCS,
};

static const stwuct dwm_encodew_funcs mgag200_g200ew3_dac_encodew_funcs = {
	MGAG200_DAC_ENCODEW_FUNCS,
};

static const stwuct dwm_connectow_hewpew_funcs mgag200_g200ew3_vga_connectow_hewpew_funcs = {
	MGAG200_VGA_CONNECTOW_HEWPEW_FUNCS,
};

static const stwuct dwm_connectow_funcs mgag200_g200ew3_vga_connectow_funcs = {
	MGAG200_VGA_CONNECTOW_FUNCS,
};

static int mgag200_g200ew3_pipewine_init(stwuct mga_device *mdev)
{
	stwuct dwm_device *dev = &mdev->base;
	stwuct dwm_pwane *pwimawy_pwane = &mdev->pwimawy_pwane;
	stwuct dwm_cwtc *cwtc = &mdev->cwtc;
	stwuct dwm_encodew *encodew = &mdev->encodew;
	stwuct mga_i2c_chan *i2c = &mdev->i2c;
	stwuct dwm_connectow *connectow = &mdev->connectow;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &mgag200_g200ew3_pwimawy_pwane_funcs,
				       mgag200_pwimawy_pwane_fowmats,
				       mgag200_pwimawy_pwane_fowmats_size,
				       mgag200_pwimawy_pwane_fmtmods,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_univewsaw_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(pwimawy_pwane, &mgag200_g200ew3_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&mgag200_g200ew3_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_cwtc_init_with_pwanes() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_cwtc_hewpew_add(cwtc, &mgag200_g200ew3_cwtc_hewpew_funcs);

	/* FIXME: wegacy gamma tabwes, but atomic gamma doesn't wowk without */
	dwm_mode_cwtc_set_gamma_size(cwtc, MGAG200_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, MGAG200_WUT_SIZE);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_encodew_init(dev, encodew, &mgag200_g200ew3_dac_encodew_funcs,
			       DWM_MODE_ENCODEW_DAC, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_encodew_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = mgag200_i2c_init(mdev, i2c);
	if (wet) {
		dwm_eww(dev, "faiwed to add DDC bus: %d\n", wet);
		wetuwn wet;
	}

	wet = dwm_connectow_init_with_ddc(dev, connectow,
					  &mgag200_g200ew3_vga_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &i2c->adaptew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_init_with_ddc() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(connectow, &mgag200_g200ew3_vga_connectow_hewpew_funcs);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_attach_encodew() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * DWM device
 */

static const stwuct mgag200_device_info mgag200_g200ew3_device_info =
	MGAG200_DEVICE_INFO_INIT(2048, 2048, 0, twue, 0, 1, fawse);

static const stwuct mgag200_device_funcs mgag200_g200ew3_device_funcs = {
	.disabwe_vidwst = mgag200_bmc_disabwe_vidwst,
	.enabwe_vidwst = mgag200_bmc_enabwe_vidwst,
	.pixpwwc_atomic_check = mgag200_g200ew3_pixpwwc_atomic_check,
	.pixpwwc_atomic_update = mgag200_g200wb_pixpwwc_atomic_update, // same as G200WB
};

static wesouwce_size_t mgag200_g200ew3_device_pwobe_vwam(stwuct mga_device *mdev)
{
	wesouwce_size_t vwam_size = wesouwce_size(mdev->vwam_wes);

	if (vwam_size >= 0x1000000)
		vwam_size = vwam_size - 0x400000;
	wetuwn mgag200_pwobe_vwam(mdev->vwam, vwam_size);
}

stwuct mga_device *mgag200_g200ew3_device_cweate(stwuct pci_dev *pdev,
						 const stwuct dwm_dwivew *dwv)
{
	stwuct mga_device *mdev;
	stwuct dwm_device *dev;
	wesouwce_size_t vwam_avaiwabwe;
	int wet;

	mdev = devm_dwm_dev_awwoc(&pdev->dev, dwv, stwuct mga_device, base);
	if (IS_EWW(mdev))
		wetuwn mdev;
	dev = &mdev->base;

	pci_set_dwvdata(pdev, dev);

	wet = mgag200_init_pci_options(pdev, 0x41049120, 0x0000b000);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_device_pweinit(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_device_init(mdev, &mgag200_g200ew3_device_info,
				  &mgag200_g200ew3_device_funcs);
	if (wet)
		wetuwn EWW_PTW(wet);

	mgag200_g200ew3_init_wegistews(mdev);

	vwam_avaiwabwe = mgag200_g200ew3_device_pwobe_vwam(mdev);

	wet = mgag200_mode_config_init(mdev, vwam_avaiwabwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_g200ew3_pipewine_init(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(dev);

	wetuwn mdev;
}
