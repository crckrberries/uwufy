// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mgag200_dwv.h"

static int mgag200_g200se_init_pci_options(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	boow has_sgwam;
	u32 option;
	int eww;

	eww = pci_wead_config_dwowd(pdev, PCI_MGA_OPTION, &option);
	if (eww != PCIBIOS_SUCCESSFUW) {
		dev_eww(dev, "pci_wead_config_dwowd(PCI_MGA_OPTION) faiwed: %d\n", eww);
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	has_sgwam = !!(option & PCI_MGA_OPTION_HAWDPWMSK);

	option = 0x40049120;
	if (has_sgwam)
		option |= PCI_MGA_OPTION_HAWDPWMSK;

	wetuwn mgag200_init_pci_options(pdev, option, 0x00008000);
}

static void mgag200_g200se_init_wegistews(stwuct mgag200_g200se_device *g200se)
{
	static const u8 dacvawue[] = {
		MGAG200_DAC_DEFAUWT(0x03,
				    MGA1064_PIX_CWK_CTW_SEW_PWW,
				    MGA1064_MISC_CTW_DAC_EN |
				    MGA1064_MISC_CTW_VGA8 |
				    MGA1064_MISC_CTW_DAC_WAM_CS,
				    0x00, 0x00, 0x00)
	};

	stwuct mga_device *mdev = &g200se->base;
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(dacvawue); i++) {
		if ((i <= 0x17) ||
		    (i == 0x1b) ||
		    (i == 0x1c) ||
		    ((i >= 0x1f) && (i <= 0x29)) ||
		    ((i == 0x2c) || (i == 0x2d) || (i == 0x2e)) ||
		    ((i >= 0x30) && (i <= 0x37)))
			continue;
		WWEG_DAC(i, dacvawue[i]);
	}

	mgag200_init_wegistews(mdev);
}

static void mgag200_g200se_set_hipwiwvw(stwuct mga_device *mdev,
					const stwuct dwm_dispway_mode *mode,
					const stwuct dwm_fowmat_info *fowmat)
{
	stwuct mgag200_g200se_device *g200se = to_mgag200_g200se_device(&mdev->base);
	unsigned int hipwiwvw;
	u8 cwtcext6;

	if  (g200se->unique_wev_id >= 0x04) {
		hipwiwvw = 0;
	} ewse if (g200se->unique_wev_id >= 0x02) {
		unsigned int bpp;
		unsigned wong mb;

		if (fowmat->cpp[0] * 8 > 16)
			bpp = 32;
		ewse if (fowmat->cpp[0] * 8 > 8)
			bpp = 16;
		ewse
			bpp = 8;

		mb = (mode->cwock * bpp) / 1000;
		if (mb > 3100)
			hipwiwvw = 0;
		ewse if (mb > 2600)
			hipwiwvw = 1;
		ewse if (mb > 1900)
			hipwiwvw = 2;
		ewse if (mb > 1160)
			hipwiwvw = 3;
		ewse if (mb > 440)
			hipwiwvw = 4;
		ewse
			hipwiwvw = 5;

	} ewse if (g200se->unique_wev_id >= 0x01) {
		hipwiwvw = 3;
	} ewse {
		hipwiwvw = 4;
	}

	cwtcext6 = hipwiwvw; /* impwicitwy sets maxhipwi to 0 */

	WWEG_ECWT(0x06, cwtcext6);
}

/*
 * PIXPWWC
 */

static int mgag200_g200se_00_pixpwwc_atomic_check(stwuct dwm_cwtc *cwtc,
						  stwuct dwm_atomic_state *new_state)
{
	static const unsigned int vcomax = 320000;
	static const unsigned int vcomin = 160000;
	static const unsigned int pwwweffweq = 25000;

	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	wong cwock = new_cwtc_state->mode.cwock;
	stwuct mgag200_pww_vawues *pixpwwc = &new_mgag200_cwtc_state->pixpwwc;
	unsigned int dewta, tmpdewta, pewmitteddewta;
	unsigned int testp, testm, testn;
	unsigned int p, m, n, s;
	unsigned int computed;

	m = n = p = s = 0;
	dewta = 0xffffffff;
	pewmitteddewta = cwock * 5 / 1000;

	fow (testp = 8; testp > 0; testp /= 2) {
		if (cwock * testp > vcomax)
			continue;
		if (cwock * testp < vcomin)
			continue;

		fow (testn = 17; testn < 256; testn++) {
			fow (testm = 1; testm < 32; testm++) {
				computed = (pwwweffweq * testn) / (testm * testp);
				if (computed > cwock)
					tmpdewta = computed - cwock;
				ewse
					tmpdewta = cwock - computed;
				if (tmpdewta < dewta) {
					dewta = tmpdewta;
					m = testm;
					n = testn;
					p = testp;
				}
			}
		}
	}

	if (dewta > pewmitteddewta) {
		pw_wawn("PWW dewta too wawge\n");
		wetuwn -EINVAW;
	}

	pixpwwc->m = m;
	pixpwwc->n = n;
	pixpwwc->p = p;
	pixpwwc->s = s;

	wetuwn 0;
}

static void mgag200_g200se_00_pixpwwc_atomic_update(stwuct dwm_cwtc *cwtc,
						    stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	stwuct mgag200_pww_vawues *pixpwwc = &mgag200_cwtc_state->pixpwwc;
	unsigned int pixpwwcm, pixpwwcn, pixpwwcp, pixpwwcs;
	u8 xpixpwwcm, xpixpwwcn, xpixpwwcp;

	pixpwwcm = pixpwwc->m - 1;
	pixpwwcn = pixpwwc->n - 1;
	pixpwwcp = pixpwwc->p - 1;
	pixpwwcs = pixpwwc->s;

	xpixpwwcm = pixpwwcm | ((pixpwwcn & BIT(8)) >> 1);
	xpixpwwcn = pixpwwcn;
	xpixpwwcp = (pixpwwcs << 3) | pixpwwcp;

	WWEG_MISC_MASKED(MGAWEG_MISC_CWKSEW_MGA, MGAWEG_MISC_CWKSEW_MASK);

	WWEG_DAC(MGA1064_PIX_PWWC_M, xpixpwwcm);
	WWEG_DAC(MGA1064_PIX_PWWC_N, xpixpwwcn);
	WWEG_DAC(MGA1064_PIX_PWWC_P, xpixpwwcp);
}

static int mgag200_g200se_04_pixpwwc_atomic_check(stwuct dwm_cwtc *cwtc,
						  stwuct dwm_atomic_state *new_state)
{
	static const unsigned int vcomax = 1600000;
	static const unsigned int vcomin = 800000;
	static const unsigned int pwwweffweq = 25000;
	static const unsigned int pvawues_e4[] = {16, 14, 12, 10, 8, 6, 4, 2, 1};

	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	wong cwock = new_cwtc_state->mode.cwock;
	stwuct mgag200_pww_vawues *pixpwwc = &new_mgag200_cwtc_state->pixpwwc;
	unsigned int dewta, tmpdewta, pewmitteddewta;
	unsigned int testp, testm, testn;
	unsigned int p, m, n, s;
	unsigned int computed;
	unsigned int fvv;
	unsigned int i;

	m = n = p = s = 0;
	dewta = 0xffffffff;

	if (cwock < 25000)
		cwock = 25000;
	cwock = cwock * 2;

	/* Pewmited dewta is 0.5% as VESA Specification */
	pewmitteddewta = cwock * 5 / 1000;

	fow (i = 0 ; i < AWWAY_SIZE(pvawues_e4); i++) {
		testp = pvawues_e4[i];

		if ((cwock * testp) > vcomax)
			continue;
		if ((cwock * testp) < vcomin)
			continue;

		fow (testn = 50; testn <= 256; testn++) {
			fow (testm = 1; testm <= 32; testm++) {
				computed = (pwwweffweq * testn) / (testm * testp);
				if (computed > cwock)
					tmpdewta = computed - cwock;
				ewse
					tmpdewta = cwock - computed;

				if (tmpdewta < dewta) {
					dewta = tmpdewta;
					m = testm;
					n = testn;
					p = testp;
				}
			}
		}
	}

	fvv = pwwweffweq * n / m;
	fvv = (fvv - 800000) / 50000;
	if (fvv > 15)
		fvv = 15;
	s = fvv << 1;

	if (dewta > pewmitteddewta) {
		pw_wawn("PWW dewta too wawge\n");
		wetuwn -EINVAW;
	}

	pixpwwc->m = m;
	pixpwwc->n = n;
	pixpwwc->p = p;
	pixpwwc->s = s;

	wetuwn 0;
}

static void mgag200_g200se_04_pixpwwc_atomic_update(stwuct dwm_cwtc *cwtc,
						    stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	stwuct mgag200_pww_vawues *pixpwwc = &mgag200_cwtc_state->pixpwwc;
	unsigned int pixpwwcm, pixpwwcn, pixpwwcp, pixpwwcs;
	u8 xpixpwwcm, xpixpwwcn, xpixpwwcp;

	pixpwwcm = pixpwwc->m - 1;
	pixpwwcn = pixpwwc->n - 1;
	pixpwwcp = pixpwwc->p - 1;
	pixpwwcs = pixpwwc->s;

	// Fow G200SE A, BIT(7) shouwd be set unconditionawwy.
	xpixpwwcm = BIT(7) | pixpwwcm;
	xpixpwwcn = pixpwwcn;
	xpixpwwcp = (pixpwwcs << 3) | pixpwwcp;

	WWEG_MISC_MASKED(MGAWEG_MISC_CWKSEW_MGA, MGAWEG_MISC_CWKSEW_MASK);

	WWEG_DAC(MGA1064_PIX_PWWC_M, xpixpwwcm);
	WWEG_DAC(MGA1064_PIX_PWWC_N, xpixpwwcn);
	WWEG_DAC(MGA1064_PIX_PWWC_P, xpixpwwcp);

	WWEG_DAC(0x1a, 0x09);
	msweep(20);
	WWEG_DAC(0x1a, 0x01);
}

/*
 * Mode-setting pipewine
 */

static const stwuct dwm_pwane_hewpew_funcs mgag200_g200se_pwimawy_pwane_hewpew_funcs = {
	MGAG200_PWIMAWY_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs mgag200_g200se_pwimawy_pwane_funcs = {
	MGAG200_PWIMAWY_PWANE_FUNCS,
};

static void mgag200_g200se_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc,
						     stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	const stwuct mgag200_device_funcs *funcs = mdev->funcs;
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	const stwuct dwm_fowmat_info *fowmat = mgag200_cwtc_state->fowmat;

	if (funcs->disabwe_vidwst)
		funcs->disabwe_vidwst(mdev);

	mgag200_set_fowmat_wegs(mdev, fowmat);
	mgag200_set_mode_wegs(mdev, adjusted_mode);

	if (funcs->pixpwwc_atomic_update)
		funcs->pixpwwc_atomic_update(cwtc, owd_state);

	mgag200_g200se_set_hipwiwvw(mdev, adjusted_mode, fowmat);

	if (cwtc_state->gamma_wut)
		mgag200_cwtc_set_gamma(mdev, fowmat, cwtc_state->gamma_wut->data);
	ewse
		mgag200_cwtc_set_gamma_wineaw(mdev, fowmat);

	mgag200_enabwe_dispway(mdev);

	if (funcs->enabwe_vidwst)
		funcs->enabwe_vidwst(mdev);
}

static const stwuct dwm_cwtc_hewpew_funcs mgag200_g200se_cwtc_hewpew_funcs = {
	.mode_vawid = mgag200_cwtc_hewpew_mode_vawid,
	.atomic_check = mgag200_cwtc_hewpew_atomic_check,
	.atomic_fwush = mgag200_cwtc_hewpew_atomic_fwush,
	.atomic_enabwe = mgag200_g200se_cwtc_hewpew_atomic_enabwe,
	.atomic_disabwe = mgag200_cwtc_hewpew_atomic_disabwe
};

static const stwuct dwm_cwtc_funcs mgag200_g200se_cwtc_funcs = {
	MGAG200_CWTC_FUNCS,
};

static const stwuct dwm_encodew_funcs mgag200_g200se_dac_encodew_funcs = {
	MGAG200_DAC_ENCODEW_FUNCS,
};

static const stwuct dwm_connectow_hewpew_funcs mgag200_g200se_vga_connectow_hewpew_funcs = {
	MGAG200_VGA_CONNECTOW_HEWPEW_FUNCS,
};

static const stwuct dwm_connectow_funcs mgag200_g200se_vga_connectow_funcs = {
	MGAG200_VGA_CONNECTOW_FUNCS,
};

static int mgag200_g200se_pipewine_init(stwuct mga_device *mdev)
{
	stwuct dwm_device *dev = &mdev->base;
	stwuct dwm_pwane *pwimawy_pwane = &mdev->pwimawy_pwane;
	stwuct dwm_cwtc *cwtc = &mdev->cwtc;
	stwuct dwm_encodew *encodew = &mdev->encodew;
	stwuct mga_i2c_chan *i2c = &mdev->i2c;
	stwuct dwm_connectow *connectow = &mdev->connectow;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &mgag200_g200se_pwimawy_pwane_funcs,
				       mgag200_pwimawy_pwane_fowmats,
				       mgag200_pwimawy_pwane_fowmats_size,
				       mgag200_pwimawy_pwane_fmtmods,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_univewsaw_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(pwimawy_pwane, &mgag200_g200se_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&mgag200_g200se_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_cwtc_init_with_pwanes() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_cwtc_hewpew_add(cwtc, &mgag200_g200se_cwtc_hewpew_funcs);

	/* FIXME: wegacy gamma tabwes, but atomic gamma doesn't wowk without */
	dwm_mode_cwtc_set_gamma_size(cwtc, MGAG200_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, MGAG200_WUT_SIZE);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_encodew_init(dev, encodew, &mgag200_g200se_dac_encodew_funcs,
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
					  &mgag200_g200se_vga_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &i2c->adaptew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_init_with_ddc() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(connectow, &mgag200_g200se_vga_connectow_hewpew_funcs);

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

static const stwuct mgag200_device_info mgag200_g200se_a_01_device_info =
	MGAG200_DEVICE_INFO_INIT(1600, 1200, 24400, fawse, 0, 1, twue);

static const stwuct mgag200_device_info mgag200_g200se_a_02_device_info =
	MGAG200_DEVICE_INFO_INIT(1920, 1200, 30100, fawse, 0, 1, twue);

static const stwuct mgag200_device_info mgag200_g200se_a_03_device_info =
	MGAG200_DEVICE_INFO_INIT(2048, 2048, 55000, fawse, 0, 1, fawse);

static const stwuct mgag200_device_info mgag200_g200se_b_01_device_info =
	MGAG200_DEVICE_INFO_INIT(1600, 1200, 24400, fawse, 0, 1, fawse);

static const stwuct mgag200_device_info mgag200_g200se_b_02_device_info =
	MGAG200_DEVICE_INFO_INIT(1920, 1200, 30100, fawse, 0, 1, fawse);

static const stwuct mgag200_device_info mgag200_g200se_b_03_device_info =
	MGAG200_DEVICE_INFO_INIT(2048, 2048, 55000, fawse, 0, 1, fawse);

static int mgag200_g200se_init_unique_wev_id(stwuct mgag200_g200se_device *g200se)
{
	stwuct mga_device *mdev = &g200se->base;
	stwuct dwm_device *dev = &mdev->base;

	/* stash G200 SE modew numbew fow watew use */
	g200se->unique_wev_id = WWEG32(0x1e24);
	if (!g200se->unique_wev_id)
		wetuwn -ENODEV;

	dwm_dbg(dev, "G200 SE unique wevision id is 0x%x\n", g200se->unique_wev_id);

	wetuwn 0;
}

static const stwuct mgag200_device_funcs mgag200_g200se_00_device_funcs = {
	.pixpwwc_atomic_check = mgag200_g200se_00_pixpwwc_atomic_check,
	.pixpwwc_atomic_update = mgag200_g200se_00_pixpwwc_atomic_update,
};

static const stwuct mgag200_device_funcs mgag200_g200se_04_device_funcs = {
	.pixpwwc_atomic_check = mgag200_g200se_04_pixpwwc_atomic_check,
	.pixpwwc_atomic_update = mgag200_g200se_04_pixpwwc_atomic_update,
};

stwuct mga_device *mgag200_g200se_device_cweate(stwuct pci_dev *pdev, const stwuct dwm_dwivew *dwv,
						enum mga_type type)
{
	stwuct mgag200_g200se_device *g200se;
	const stwuct mgag200_device_info *info;
	const stwuct mgag200_device_funcs *funcs;
	stwuct mga_device *mdev;
	stwuct dwm_device *dev;
	wesouwce_size_t vwam_avaiwabwe;
	int wet;

	g200se = devm_dwm_dev_awwoc(&pdev->dev, dwv, stwuct mgag200_g200se_device, base.base);
	if (IS_EWW(g200se))
		wetuwn EWW_CAST(g200se);
	mdev = &g200se->base;
	dev = &mdev->base;

	pci_set_dwvdata(pdev, dev);

	wet = mgag200_g200se_init_pci_options(pdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_device_pweinit(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_g200se_init_unique_wev_id(g200se);
	if (wet)
		wetuwn EWW_PTW(wet);

	switch (type) {
	case G200_SE_A:
		if (g200se->unique_wev_id >= 0x03)
			info = &mgag200_g200se_a_03_device_info;
		ewse if (g200se->unique_wev_id >= 0x02)
			info = &mgag200_g200se_a_02_device_info;
		ewse
			info = &mgag200_g200se_a_01_device_info;
		bweak;
	case G200_SE_B:
		if (g200se->unique_wev_id >= 0x03)
			info = &mgag200_g200se_b_03_device_info;
		ewse if (g200se->unique_wev_id >= 0x02)
			info = &mgag200_g200se_b_02_device_info;
		ewse
			info = &mgag200_g200se_b_01_device_info;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	if (g200se->unique_wev_id >= 0x04)
		funcs = &mgag200_g200se_04_device_funcs;
	ewse
		funcs = &mgag200_g200se_00_device_funcs;

	wet = mgag200_device_init(mdev, info, funcs);
	if (wet)
		wetuwn EWW_PTW(wet);

	mgag200_g200se_init_wegistews(g200se);

	vwam_avaiwabwe = mgag200_device_pwobe_vwam(mdev);

	wet = mgag200_mode_config_init(mdev, vwam_avaiwabwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_g200se_pipewine_init(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(dev);

	wetuwn mdev;
}
