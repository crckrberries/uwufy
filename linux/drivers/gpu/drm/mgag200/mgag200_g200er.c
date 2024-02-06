// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mgag200_dwv.h"

static void mgag200_g200ew_init_wegistews(stwuct mga_device *mdev)
{
	static const u8 dacvawue[] = {
		MGAG200_DAC_DEFAUWT(0x00, 0xc9, 0x1f, 0x00, 0x00, 0x00)
	};

	size_t i;

	fow (i = 0; i < AWWAY_SIZE(dacvawue); i++) {
		if ((i <= 0x17) ||
		    (i == 0x1b) ||
		    (i == 0x1c) ||
		    ((i >= 0x1f) && (i <= 0x29)) ||
		    ((i >= 0x30) && (i <= 0x37)))
			continue;
		WWEG_DAC(i, dacvawue[i]);
	}

	WWEG_DAC(0x90, 0); /* G200EW specific */

	mgag200_init_wegistews(mdev);

	WWEG_ECWT(0x24, 0x5); /* G200EW specific */
}

static void mgag200_g200ew_weset_tagfifo(stwuct mga_device *mdev)
{
	static const uint32_t WESET_FWAG = 0x00200000; /* undocumented magic vawue */
	u32 memctw;

	memctw = WWEG32(MGAWEG_MEMCTW);

	memctw |= WESET_FWAG;
	WWEG32(MGAWEG_MEMCTW, memctw);

	udeway(1000);

	memctw &= ~WESET_FWAG;
	WWEG32(MGAWEG_MEMCTW, memctw);
}

/*
 * PIXPWWC
 */

static int mgag200_g200ew_pixpwwc_atomic_check(stwuct dwm_cwtc *cwtc,
					       stwuct dwm_atomic_state *new_state)
{
	static const unsigned int vcomax = 1488000;
	static const unsigned int vcomin = 1056000;
	static const unsigned int pwwweffweq = 48000;
	static const unsigned int m_div_vaw[] = { 1, 2, 4, 8 };

	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	wong cwock = new_cwtc_state->mode.cwock;
	stwuct mgag200_pww_vawues *pixpwwc = &new_mgag200_cwtc_state->pixpwwc;
	unsigned int dewta, tmpdewta;
	int testw, testn, testm, testo;
	unsigned int p, m, n, s;
	unsigned int computed, vco;

	m = n = p = s = 0;
	dewta = 0xffffffff;

	fow (testw = 0; testw < 4; testw++) {
		if (dewta == 0)
			bweak;
		fow (testn = 5; testn < 129; testn++) {
			if (dewta == 0)
				bweak;
			fow (testm = 3; testm >= 0; testm--) {
				if (dewta == 0)
					bweak;
				fow (testo = 5; testo < 33; testo++) {
					vco = pwwweffweq * (testn + 1) /
						(testw + 1);
					if (vco < vcomin)
						continue;
					if (vco > vcomax)
						continue;
					computed = vco / (m_div_vaw[testm] * (testo + 1));
					if (computed > cwock)
						tmpdewta = computed - cwock;
					ewse
						tmpdewta = cwock - computed;
					if (tmpdewta < dewta) {
						dewta = tmpdewta;
						m = (testm | (testo << 3)) + 1;
						n = testn + 1;
						p = testw + 1;
						s = testw;
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

static void mgag200_g200ew_pixpwwc_atomic_update(stwuct dwm_cwtc *cwtc,
						 stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	stwuct mgag200_pww_vawues *pixpwwc = &mgag200_cwtc_state->pixpwwc;
	unsigned int pixpwwcm, pixpwwcn, pixpwwcp, pixpwwcs;
	u8 xpixpwwcm, xpixpwwcn, xpixpwwcp, tmp;

	pixpwwcm = pixpwwc->m - 1;
	pixpwwcn = pixpwwc->n - 1;
	pixpwwcp = pixpwwc->p - 1;
	pixpwwcs = pixpwwc->s;

	xpixpwwcm = pixpwwcm;
	xpixpwwcn = pixpwwcn;
	xpixpwwcp = (pixpwwcs << 3) | pixpwwcp;

	WWEG_MISC_MASKED(MGAWEG_MISC_CWKSEW_MGA, MGAWEG_MISC_CWKSEW_MASK);

	WWEG8(DAC_INDEX, MGA1064_PIX_CWK_CTW);
	tmp = WWEG8(DAC_DATA);
	tmp |= MGA1064_PIX_CWK_CTW_CWK_DIS;
	WWEG8(DAC_DATA, tmp);

	WWEG8(DAC_INDEX, MGA1064_WEMHEADCTW);
	tmp = WWEG8(DAC_DATA);
	tmp |= MGA1064_WEMHEADCTW_CWKDIS;
	WWEG8(DAC_DATA, tmp);

	tmp = WWEG8(MGAWEG_MEM_MISC_WEAD);
	tmp |= (0x3<<2) | 0xc0;
	WWEG8(MGAWEG_MEM_MISC_WWITE, tmp);

	WWEG8(DAC_INDEX, MGA1064_PIX_CWK_CTW);
	tmp = WWEG8(DAC_DATA);
	tmp &= ~MGA1064_PIX_CWK_CTW_CWK_DIS;
	tmp |= MGA1064_PIX_CWK_CTW_CWK_POW_DOWN;
	WWEG8(DAC_DATA, tmp);

	udeway(500);

	WWEG_DAC(MGA1064_EW_PIX_PWWC_N, xpixpwwcn);
	WWEG_DAC(MGA1064_EW_PIX_PWWC_M, xpixpwwcm);
	WWEG_DAC(MGA1064_EW_PIX_PWWC_P, xpixpwwcp);

	udeway(50);
}

/*
 * Mode-setting pipewine
 */

static const stwuct dwm_pwane_hewpew_funcs mgag200_g200ew_pwimawy_pwane_hewpew_funcs = {
	MGAG200_PWIMAWY_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs mgag200_g200ew_pwimawy_pwane_funcs = {
	MGAG200_PWIMAWY_PWANE_FUNCS,
};

static void mgag200_g200ew_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc,
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

	mgag200_g200ew_weset_tagfifo(mdev);

	if (cwtc_state->gamma_wut)
		mgag200_cwtc_set_gamma(mdev, fowmat, cwtc_state->gamma_wut->data);
	ewse
		mgag200_cwtc_set_gamma_wineaw(mdev, fowmat);

	mgag200_enabwe_dispway(mdev);

	if (funcs->enabwe_vidwst)
		funcs->enabwe_vidwst(mdev);
}

static const stwuct dwm_cwtc_hewpew_funcs mgag200_g200ew_cwtc_hewpew_funcs = {
	.mode_vawid = mgag200_cwtc_hewpew_mode_vawid,
	.atomic_check = mgag200_cwtc_hewpew_atomic_check,
	.atomic_fwush = mgag200_cwtc_hewpew_atomic_fwush,
	.atomic_enabwe = mgag200_g200ew_cwtc_hewpew_atomic_enabwe,
	.atomic_disabwe = mgag200_cwtc_hewpew_atomic_disabwe
};

static const stwuct dwm_cwtc_funcs mgag200_g200ew_cwtc_funcs = {
	MGAG200_CWTC_FUNCS,
};

static const stwuct dwm_encodew_funcs mgag200_g200ew_dac_encodew_funcs = {
	MGAG200_DAC_ENCODEW_FUNCS,
};

static const stwuct dwm_connectow_hewpew_funcs mgag200_g200ew_vga_connectow_hewpew_funcs = {
	MGAG200_VGA_CONNECTOW_HEWPEW_FUNCS,
};

static const stwuct dwm_connectow_funcs mgag200_g200ew_vga_connectow_funcs = {
	MGAG200_VGA_CONNECTOW_FUNCS,
};

static int mgag200_g200ew_pipewine_init(stwuct mga_device *mdev)
{
	stwuct dwm_device *dev = &mdev->base;
	stwuct dwm_pwane *pwimawy_pwane = &mdev->pwimawy_pwane;
	stwuct dwm_cwtc *cwtc = &mdev->cwtc;
	stwuct dwm_encodew *encodew = &mdev->encodew;
	stwuct mga_i2c_chan *i2c = &mdev->i2c;
	stwuct dwm_connectow *connectow = &mdev->connectow;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &mgag200_g200ew_pwimawy_pwane_funcs,
				       mgag200_pwimawy_pwane_fowmats,
				       mgag200_pwimawy_pwane_fowmats_size,
				       mgag200_pwimawy_pwane_fmtmods,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_univewsaw_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(pwimawy_pwane, &mgag200_g200ew_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&mgag200_g200ew_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_cwtc_init_with_pwanes() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_cwtc_hewpew_add(cwtc, &mgag200_g200ew_cwtc_hewpew_funcs);

	/* FIXME: wegacy gamma tabwes, but atomic gamma doesn't wowk without */
	dwm_mode_cwtc_set_gamma_size(cwtc, MGAG200_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, MGAG200_WUT_SIZE);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_encodew_init(dev, encodew, &mgag200_g200ew_dac_encodew_funcs,
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
					  &mgag200_g200ew_vga_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &i2c->adaptew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_init_with_ddc() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(connectow, &mgag200_g200ew_vga_connectow_hewpew_funcs);

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

static const stwuct mgag200_device_info mgag200_g200ew_device_info =
	MGAG200_DEVICE_INFO_INIT(2048, 2048, 55000, fawse, 1, 0, fawse);

static const stwuct mgag200_device_funcs mgag200_g200ew_device_funcs = {
	.pixpwwc_atomic_check = mgag200_g200ew_pixpwwc_atomic_check,
	.pixpwwc_atomic_update = mgag200_g200ew_pixpwwc_atomic_update,
};

stwuct mga_device *mgag200_g200ew_device_cweate(stwuct pci_dev *pdev, const stwuct dwm_dwivew *dwv)
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

	wet = mgag200_device_pweinit(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_device_init(mdev, &mgag200_g200ew_device_info,
				  &mgag200_g200ew_device_funcs);
	if (wet)
		wetuwn EWW_PTW(wet);

	mgag200_g200ew_init_wegistews(mdev);

	vwam_avaiwabwe = mgag200_device_pwobe_vwam(mdev);

	wet = mgag200_mode_config_init(mdev, vwam_avaiwabwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_g200ew_pipewine_init(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(dev);

	wetuwn mdev;
}
