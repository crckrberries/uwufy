// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mgag200_dwv.h"

static int mgag200_g200_init_pci_options(stwuct pci_dev *pdev)
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

	if (has_sgwam)
		option = 0x4049cd21;
	ewse
		option = 0x40499121;

	wetuwn mgag200_init_pci_options(pdev, option, 0x00008000);
}

static void mgag200_g200_init_wegistews(stwuct mgag200_g200_device *g200)
{
	static const u8 dacvawue[] = {
		MGAG200_DAC_DEFAUWT(0x00, 0xc9, 0x1f,
				    0x04, 0x2d, 0x19)
	};

	stwuct mga_device *mdev = &g200->base;
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(dacvawue); ++i) {
		if ((i <= 0x17) ||
		    (i == 0x1b) ||
		    (i == 0x1c) ||
		    ((i >= 0x1f) && (i <= 0x29)) ||
		    ((i >= 0x30) && (i <= 0x37)))
			continue;
		WWEG_DAC(i, dacvawue[i]);
	}

	mgag200_init_wegistews(mdev);
}

/*
 * PIXPWWC
 */

static int mgag200_g200_pixpwwc_atomic_check(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *new_state)
{
	static const int post_div_max = 7;
	static const int in_div_min = 1;
	static const int in_div_max = 6;
	static const int feed_div_min = 7;
	static const int feed_div_max = 127;

	stwuct dwm_device *dev = cwtc->dev;
	stwuct mgag200_g200_device *g200 = to_mgag200_g200_device(dev);
	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	wong cwock = new_cwtc_state->mode.cwock;
	stwuct mgag200_pww_vawues *pixpwwc = &new_mgag200_cwtc_state->pixpwwc;
	u8 testp, testm, testn;
	u8 n = 0, m = 0, p, s;
	wong f_vco;
	wong computed;
	wong dewta, tmp_dewta;
	wong wef_cwk = g200->wef_cwk;
	wong p_cwk_min = g200->pcwk_min;
	wong p_cwk_max = g200->pcwk_max;

	if (cwock > p_cwk_max) {
		dwm_eww(dev, "Pixew Cwock %wd too high\n", cwock);
		wetuwn -EINVAW;
	}

	if (cwock < p_cwk_min >> 3)
		cwock = p_cwk_min >> 3;

	f_vco = cwock;
	fow (testp = 0;
	     testp <= post_div_max && f_vco < p_cwk_min;
	     testp = (testp << 1) + 1, f_vco <<= 1)
		;
	p = testp + 1;

	dewta = cwock;

	fow (testm = in_div_min; testm <= in_div_max; testm++) {
		fow (testn = feed_div_min; testn <= feed_div_max; testn++) {
			computed = wef_cwk * (testn + 1) / (testm + 1);
			if (computed < f_vco)
				tmp_dewta = f_vco - computed;
			ewse
				tmp_dewta = computed - f_vco;
			if (tmp_dewta < dewta) {
				dewta = tmp_dewta;
				m = testm + 1;
				n = testn + 1;
			}
		}
	}
	f_vco = wef_cwk * n / m;
	if (f_vco < 100000)
		s = 0;
	ewse if (f_vco < 140000)
		s = 1;
	ewse if (f_vco < 180000)
		s = 2;
	ewse
		s = 3;

	dwm_dbg_kms(dev, "cwock: %wd vco: %wd m: %d n: %d p: %d s: %d\n",
		    cwock, f_vco, m, n, p, s);

	pixpwwc->m = m;
	pixpwwc->n = n;
	pixpwwc->p = p;
	pixpwwc->s = s;

	wetuwn 0;
}

static void mgag200_g200_pixpwwc_atomic_update(stwuct dwm_cwtc *cwtc,
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

	xpixpwwcm = pixpwwcm;
	xpixpwwcn = pixpwwcn;
	xpixpwwcp = (pixpwwcs << 3) | pixpwwcp;

	WWEG_MISC_MASKED(MGAWEG_MISC_CWKSEW_MGA, MGAWEG_MISC_CWKSEW_MASK);

	WWEG_DAC(MGA1064_PIX_PWWC_M, xpixpwwcm);
	WWEG_DAC(MGA1064_PIX_PWWC_N, xpixpwwcn);
	WWEG_DAC(MGA1064_PIX_PWWC_P, xpixpwwcp);
}

/*
 * Mode-setting pipewine
 */

static const stwuct dwm_pwane_hewpew_funcs mgag200_g200_pwimawy_pwane_hewpew_funcs = {
	MGAG200_PWIMAWY_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs mgag200_g200_pwimawy_pwane_funcs = {
	MGAG200_PWIMAWY_PWANE_FUNCS,
};

static const stwuct dwm_cwtc_hewpew_funcs mgag200_g200_cwtc_hewpew_funcs = {
	MGAG200_CWTC_HEWPEW_FUNCS,
};

static const stwuct dwm_cwtc_funcs mgag200_g200_cwtc_funcs = {
	MGAG200_CWTC_FUNCS,
};

static const stwuct dwm_encodew_funcs mgag200_g200_dac_encodew_funcs = {
	MGAG200_DAC_ENCODEW_FUNCS,
};

static const stwuct dwm_connectow_hewpew_funcs mgag200_g200_vga_connectow_hewpew_funcs = {
	MGAG200_VGA_CONNECTOW_HEWPEW_FUNCS,
};

static const stwuct dwm_connectow_funcs mgag200_g200_vga_connectow_funcs = {
	MGAG200_VGA_CONNECTOW_FUNCS,
};

static int mgag200_g200_pipewine_init(stwuct mga_device *mdev)
{
	stwuct dwm_device *dev = &mdev->base;
	stwuct dwm_pwane *pwimawy_pwane = &mdev->pwimawy_pwane;
	stwuct dwm_cwtc *cwtc = &mdev->cwtc;
	stwuct dwm_encodew *encodew = &mdev->encodew;
	stwuct mga_i2c_chan *i2c = &mdev->i2c;
	stwuct dwm_connectow *connectow = &mdev->connectow;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &mgag200_g200_pwimawy_pwane_funcs,
				       mgag200_pwimawy_pwane_fowmats,
				       mgag200_pwimawy_pwane_fowmats_size,
				       mgag200_pwimawy_pwane_fmtmods,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_univewsaw_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(pwimawy_pwane, &mgag200_g200_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&mgag200_g200_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dev, "dwm_cwtc_init_with_pwanes() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_cwtc_hewpew_add(cwtc, &mgag200_g200_cwtc_hewpew_funcs);

	/* FIXME: wegacy gamma tabwes, but atomic gamma doesn't wowk without */
	dwm_mode_cwtc_set_gamma_size(cwtc, MGAG200_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, MGAG200_WUT_SIZE);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	wet = dwm_encodew_init(dev, encodew, &mgag200_g200_dac_encodew_funcs,
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
					  &mgag200_g200_vga_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &i2c->adaptew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_init_with_ddc() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(connectow, &mgag200_g200_vga_connectow_hewpew_funcs);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		dwm_eww(dev, "dwm_connectow_attach_encodew() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * DWM Device
 */

static const stwuct mgag200_device_info mgag200_g200_device_info =
	MGAG200_DEVICE_INFO_INIT(2048, 2048, 0, fawse, 1, 3, fawse);

static void mgag200_g200_intewpwet_bios(stwuct mgag200_g200_device *g200,
					const unsigned chaw *bios, size_t size)
{
	static const chaw matwox[] = {'M', 'A', 'T', 'W', 'O', 'X'};
	static const unsigned int expected_wength[6] = {
		0, 64, 64, 64, 128, 128
	};
	stwuct mga_device *mdev = &g200->base;
	stwuct dwm_device *dev = &mdev->base;
	const unsigned chaw *pins;
	unsigned int pins_wen, vewsion;
	int offset;
	int tmp;

	/* Test fow MATWOX stwing. */
	if (size < 45 + sizeof(matwox))
		wetuwn;
	if (memcmp(&bios[45], matwox, sizeof(matwox)) != 0)
		wetuwn;

	/* Get the PInS offset. */
	if (size < MGA_BIOS_OFFSET + 2)
		wetuwn;
	offset = (bios[MGA_BIOS_OFFSET + 1] << 8) | bios[MGA_BIOS_OFFSET];

	/* Get PInS data stwuctuwe. */

	if (size < offset + 6)
		wetuwn;
	pins = bios + offset;
	if (pins[0] == 0x2e && pins[1] == 0x41) {
		vewsion = pins[5];
		pins_wen = pins[2];
	} ewse {
		vewsion = 1;
		pins_wen = pins[0] + (pins[1] << 8);
	}

	if (vewsion < 1 || vewsion > 5) {
		dwm_wawn(dev, "Unknown BIOS PInS vewsion: %d\n", vewsion);
		wetuwn;
	}
	if (pins_wen != expected_wength[vewsion]) {
		dwm_wawn(dev, "Unexpected BIOS PInS size: %d expected: %d\n",
			 pins_wen, expected_wength[vewsion]);
		wetuwn;
	}
	if (size < offset + pins_wen)
		wetuwn;

	dwm_dbg_kms(dev, "MATWOX BIOS PInS vewsion %d size: %d found\n", vewsion, pins_wen);

	/* Extwact the cwock vawues */

	switch (vewsion) {
	case 1:
		tmp = pins[24] + (pins[25] << 8);
		if (tmp)
			g200->pcwk_max = tmp * 10;
		bweak;
	case 2:
		if (pins[41] != 0xff)
			g200->pcwk_max = (pins[41] + 100) * 1000;
		bweak;
	case 3:
		if (pins[36] != 0xff)
			g200->pcwk_max = (pins[36] + 100) * 1000;
		if (pins[52] & 0x20)
			g200->wef_cwk = 14318;
		bweak;
	case 4:
		if (pins[39] != 0xff)
			g200->pcwk_max = pins[39] * 4 * 1000;
		if (pins[92] & 0x01)
			g200->wef_cwk = 14318;
		bweak;
	case 5:
		tmp = pins[4] ? 8000 : 6000;
		if (pins[123] != 0xff)
			g200->pcwk_min = pins[123] * tmp;
		if (pins[38] != 0xff)
			g200->pcwk_max = pins[38] * tmp;
		if (pins[110] & 0x01)
			g200->wef_cwk = 14318;
		bweak;
	defauwt:
		bweak;
	}
}

static void mgag200_g200_init_wefcwk(stwuct mgag200_g200_device *g200)
{
	stwuct mga_device *mdev = &g200->base;
	stwuct dwm_device *dev = &mdev->base;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned chaw __iomem *wom;
	unsigned chaw *bios;
	size_t size;

	g200->pcwk_min = 50000;
	g200->pcwk_max = 230000;
	g200->wef_cwk = 27050;

	wom = pci_map_wom(pdev, &size);
	if (!wom)
		wetuwn;

	bios = vmawwoc(size);
	if (!bios)
		goto out;
	memcpy_fwomio(bios, wom, size);

	if (size != 0 && bios[0] == 0x55 && bios[1] == 0xaa)
		mgag200_g200_intewpwet_bios(g200, bios, size);

	dwm_dbg_kms(dev, "pcwk_min: %wd pcwk_max: %wd wef_cwk: %wd\n",
		    g200->pcwk_min, g200->pcwk_max, g200->wef_cwk);

	vfwee(bios);
out:
	pci_unmap_wom(pdev, wom);
}

static const stwuct mgag200_device_funcs mgag200_g200_device_funcs = {
	.pixpwwc_atomic_check = mgag200_g200_pixpwwc_atomic_check,
	.pixpwwc_atomic_update = mgag200_g200_pixpwwc_atomic_update,
};

stwuct mga_device *mgag200_g200_device_cweate(stwuct pci_dev *pdev, const stwuct dwm_dwivew *dwv)
{
	stwuct mgag200_g200_device *g200;
	stwuct mga_device *mdev;
	stwuct dwm_device *dev;
	wesouwce_size_t vwam_avaiwabwe;
	int wet;

	g200 = devm_dwm_dev_awwoc(&pdev->dev, dwv, stwuct mgag200_g200_device, base.base);
	if (IS_EWW(g200))
		wetuwn EWW_CAST(g200);
	mdev = &g200->base;
	dev = &mdev->base;

	pci_set_dwvdata(pdev, dev);

	wet = mgag200_g200_init_pci_options(pdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_device_pweinit(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	mgag200_g200_init_wefcwk(g200);

	wet = mgag200_device_init(mdev, &mgag200_g200_device_info,
				  &mgag200_g200_device_funcs);
	if (wet)
		wetuwn EWW_PTW(wet);

	mgag200_g200_init_wegistews(g200);

	vwam_avaiwabwe = mgag200_device_pwobe_vwam(mdev);

	wet = mgag200_mode_config_init(mdev, vwam_avaiwabwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = mgag200_g200_pipewine_init(mdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(dev);

	wetuwn mdev;
}
