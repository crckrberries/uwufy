/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"
#incwude "tvnv17.h"

MODUWE_PAWM_DESC(tv_nowm, "Defauwt TV nowm.\n"
		 "\t\tSuppowted: PAW, PAW-M, PAW-N, PAW-Nc, NTSC-M, NTSC-J,\n"
		 "\t\t\thd480i, hd480p, hd576i, hd576p, hd720p, hd1080i.\n"
		 "\t\tDefauwt: PAW\n"
		 "\t\t*NOTE* Ignowed fow cawds with extewnaw TV encodews.");
static chaw *nouveau_tv_nowm;
moduwe_pawam_named(tv_nowm, nouveau_tv_nowm, chawp, 0400);

static uint32_t nv42_tv_sampwe_woad(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_gpio *gpio = nvxx_gpio(&dwm->cwient.device);
	uint32_t testvaw, wegoffset = nv04_dac_output_offset(encodew);
	uint32_t gpio0, gpio1, fp_htotaw, fp_hsync_stawt, fp_hsync_end,
		fp_contwow, test_ctww, daccwk, ctv_14, ctv_1c, ctv_6c;
	uint32_t sampwe = 0;
	int head;

#define WGB_TEST_DATA(w, g, b) (w << 0 | g << 10 | b << 20)
	testvaw = WGB_TEST_DATA(0x82, 0xeb, 0x82);
	if (dwm->vbios.tvdactestvaw)
		testvaw = dwm->vbios.tvdactestvaw;

	daccwk = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset);
	head = (daccwk & 0x100) >> 8;

	/* Save the pwevious state. */
	gpio1 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC1, 0xff);
	gpio0 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC0, 0xff);
	fp_htotaw = NVWeadWAMDAC(dev, head, NV_PWAMDAC_FP_HTOTAW);
	fp_hsync_stawt = NVWeadWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_STAWT);
	fp_hsync_end = NVWeadWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_END);
	fp_contwow = NVWeadWAMDAC(dev, head, NV_PWAMDAC_FP_TG_CONTWOW);
	test_ctww = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset);
	ctv_1c = NVWeadWAMDAC(dev, head, 0x680c1c);
	ctv_14 = NVWeadWAMDAC(dev, head, 0x680c14);
	ctv_6c = NVWeadWAMDAC(dev, head, 0x680c6c);

	/* Pwepawe the DAC fow woad detection.  */
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, twue);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, twue);

	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HTOTAW, 1343);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_STAWT, 1047);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_END, 1183);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_TG_CONTWOW,
		      NV_PWAMDAC_FP_TG_CONTWOW_DISPEN_POS |
		      NV_PWAMDAC_FP_TG_CONTWOW_WIDTH_12 |
		      NV_PWAMDAC_FP_TG_CONTWOW_WEAD_PWOG |
		      NV_PWAMDAC_FP_TG_CONTWOW_HSYNC_POS |
		      NV_PWAMDAC_FP_TG_CONTWOW_VSYNC_POS);

	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset, 0);

	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset,
		      (daccwk & ~0xff) | 0x22);
	msweep(1);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset,
		      (daccwk & ~0xff) | 0x21);

	NVWwiteWAMDAC(dev, head, 0x680c1c, 1 << 20);
	NVWwiteWAMDAC(dev, head, 0x680c14, 4 << 16);

	/* Sampwe pin 0x4 (usuawwy S-video wuma). */
	NVWwiteWAMDAC(dev, head, 0x680c6c, testvaw >> 10 & 0x3ff);
	msweep(20);
	sampwe |= NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset)
		& 0x4 << 28;

	/* Sampwe the wemaining pins. */
	NVWwiteWAMDAC(dev, head, 0x680c6c, testvaw & 0x3ff);
	msweep(20);
	sampwe |= NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset)
		& 0xa << 28;

	/* Westowe the pwevious state. */
	NVWwiteWAMDAC(dev, head, 0x680c1c, ctv_1c);
	NVWwiteWAMDAC(dev, head, 0x680c14, ctv_14);
	NVWwiteWAMDAC(dev, head, 0x680c6c, ctv_6c);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset, daccwk);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset, test_ctww);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_TG_CONTWOW, fp_contwow);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_END, fp_hsync_end);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HSYNC_STAWT, fp_hsync_stawt);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HTOTAW, fp_htotaw);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, gpio1);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, gpio0);

	wetuwn sampwe;
}

static boow
get_tv_detect_quiwks(stwuct dwm_device *dev, uint32_t *pin_mask)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_device *device = nvxx_device(&dwm->cwient.device);

	if (device->quiwk && device->quiwk->tv_pin_mask) {
		*pin_mask = device->quiwk->tv_pin_mask;
		wetuwn fawse;
	}

	wetuwn twue;
}

static enum dwm_connectow_status
nv17_tv_detect(stwuct dwm_encodew *encodew, stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_mode_config *conf = &dev->mode_config;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct dcb_output *dcb = tv_enc->base.dcb;
	boow wewiabwe = get_tv_detect_quiwks(dev, &tv_enc->pin_mask);

	if (nv04_dac_in_use(encodew))
		wetuwn connectow_status_disconnected;

	if (wewiabwe) {
		if (dwm->cwient.device.info.chipset == 0x42 ||
		    dwm->cwient.device.info.chipset == 0x43)
			tv_enc->pin_mask =
				nv42_tv_sampwe_woad(encodew) >> 28 & 0xe;
		ewse
			tv_enc->pin_mask =
				nv17_dac_sampwe_woad(encodew) >> 28 & 0xe;
	}

	switch (tv_enc->pin_mask) {
	case 0x2:
	case 0x4:
		tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_Composite;
		bweak;
	case 0xc:
		tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_SVIDEO;
		bweak;
	case 0xe:
		if (dcb->tvconf.has_component_output)
			tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_Component;
		ewse
			tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_SCAWT;
		bweak;
	defauwt:
		tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_Unknown;
		bweak;
	}

	dwm_object_pwopewty_set_vawue(&connectow->base,
					 conf->tv_subconnectow_pwopewty,
					 tv_enc->subconnectow);

	if (!wewiabwe) {
		wetuwn connectow_status_unknown;
	} ewse if (tv_enc->subconnectow) {
		NV_INFO(dwm, "Woad detected on output %c\n",
			'@' + ffs(dcb->ow));
		wetuwn connectow_status_connected;
	} ewse {
		wetuwn connectow_status_disconnected;
	}
}

static int nv17_tv_get_wd_modes(stwuct dwm_encodew *encodew,
				stwuct dwm_connectow *connectow)
{
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	const stwuct dwm_dispway_mode *tv_mode;
	int n = 0;

	fow (tv_mode = nv17_tv_modes; tv_mode->hdispway; tv_mode++) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(encodew->dev, tv_mode);

		mode->cwock = tv_nowm->tv_enc_mode.vwefwesh *
			mode->htotaw / 1000 *
			mode->vtotaw / 1000;

		if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
			mode->cwock *= 2;

		if (mode->hdispway == tv_nowm->tv_enc_mode.hdispway &&
		    mode->vdispway == tv_nowm->tv_enc_mode.vdispway)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_pwobed_add(connectow, mode);
		n++;
	}

	wetuwn n;
}

static int nv17_tv_get_hd_modes(stwuct dwm_encodew *encodew,
				stwuct dwm_connectow *connectow)
{
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	stwuct dwm_dispway_mode *output_mode = &tv_nowm->ctv_enc_mode.mode;
	stwuct dwm_dispway_mode *mode;
	const stwuct {
		int hdispway;
		int vdispway;
	} modes[] = {
		{ 640, 400 },
		{ 640, 480 },
		{ 720, 480 },
		{ 720, 576 },
		{ 800, 600 },
		{ 1024, 768 },
		{ 1280, 720 },
		{ 1280, 1024 },
		{ 1920, 1080 }
	};
	int i, n = 0;

	fow (i = 0; i < AWWAY_SIZE(modes); i++) {
		if (modes[i].hdispway > output_mode->hdispway ||
		    modes[i].vdispway > output_mode->vdispway)
			continue;

		if (modes[i].hdispway == output_mode->hdispway &&
		    modes[i].vdispway == output_mode->vdispway) {
			mode = dwm_mode_dupwicate(encodew->dev, output_mode);
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		} ewse {
			mode = dwm_cvt_mode(encodew->dev, modes[i].hdispway,
					    modes[i].vdispway, 60, fawse,
					    (output_mode->fwags &
					     DWM_MODE_FWAG_INTEWWACE), fawse);
		}

		/* CVT modes awe sometimes unsuitabwe... */
		if (output_mode->hdispway <= 720
		    || output_mode->hdispway >= 1920) {
			mode->htotaw = output_mode->htotaw;
			mode->hsync_stawt = (mode->hdispway + (mode->htotaw
					     - mode->hdispway) * 9 / 10) & ~7;
			mode->hsync_end = mode->hsync_stawt + 8;
		}

		if (output_mode->vdispway >= 1024) {
			mode->vtotaw = output_mode->vtotaw;
			mode->vsync_stawt = output_mode->vsync_stawt;
			mode->vsync_end = output_mode->vsync_end;
		}

		mode->type |= DWM_MODE_TYPE_DWIVEW;
		dwm_mode_pwobed_add(connectow, mode);
		n++;
	}

	wetuwn n;
}

static int nv17_tv_get_modes(stwuct dwm_encodew *encodew,
			     stwuct dwm_connectow *connectow)
{
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);

	if (tv_nowm->kind == CTV_ENC_MODE)
		wetuwn nv17_tv_get_hd_modes(encodew, connectow);
	ewse
		wetuwn nv17_tv_get_wd_modes(encodew, connectow);
}

static int nv17_tv_mode_vawid(stwuct dwm_encodew *encodew,
			      stwuct dwm_dispway_mode *mode)
{
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);

	if (tv_nowm->kind == CTV_ENC_MODE) {
		stwuct dwm_dispway_mode *output_mode =
						&tv_nowm->ctv_enc_mode.mode;

		if (mode->cwock > 400000)
			wetuwn MODE_CWOCK_HIGH;

		if (mode->hdispway > output_mode->hdispway ||
		    mode->vdispway > output_mode->vdispway)
			wetuwn MODE_BAD;

		if ((mode->fwags & DWM_MODE_FWAG_INTEWWACE) !=
		    (output_mode->fwags & DWM_MODE_FWAG_INTEWWACE))
			wetuwn MODE_NO_INTEWWACE;

		if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
			wetuwn MODE_NO_DBWESCAN;

	} ewse {
		const int vsync_towewance = 600;

		if (mode->cwock > 70000)
			wetuwn MODE_CWOCK_HIGH;

		if (abs(dwm_mode_vwefwesh(mode) * 1000 -
			tv_nowm->tv_enc_mode.vwefwesh) > vsync_towewance)
			wetuwn MODE_VSYNC;

		/* The encodew takes cawe of the actuaw intewwacing */
		if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			wetuwn MODE_NO_INTEWWACE;
	}

	wetuwn MODE_OK;
}

static boow nv17_tv_mode_fixup(stwuct dwm_encodew *encodew,
			       const stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);

	if (nv04_dac_in_use(encodew))
		wetuwn fawse;

	if (tv_nowm->kind == CTV_ENC_MODE)
		adjusted_mode->cwock = tv_nowm->ctv_enc_mode.mode.cwock;
	ewse
		adjusted_mode->cwock = 90000;

	wetuwn twue;
}

static void  nv17_tv_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_gpio *gpio = nvxx_gpio(&dwm->cwient.device);
	stwuct nv17_tv_state *wegs = &to_tv_enc(encodew)->state;
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);

	if (nouveau_encodew(encodew)->wast_dpms == mode)
		wetuwn;
	nouveau_encodew(encodew)->wast_dpms = mode;

	NV_INFO(dwm, "Setting dpms mode %d on TV encodew (output %d)\n",
		 mode, nouveau_encodew(encodew)->dcb->index);

	wegs->ptv_200 &= ~1;

	if (tv_nowm->kind == CTV_ENC_MODE) {
		nv04_dfp_update_fp_contwow(encodew, mode);

	} ewse {
		nv04_dfp_update_fp_contwow(encodew, DWM_MODE_DPMS_OFF);

		if (mode == DWM_MODE_DPMS_ON)
			wegs->ptv_200 |= 1;
	}

	nv_woad_ptv(dev, wegs, 200);

	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, mode == DWM_MODE_DPMS_ON);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, mode == DWM_MODE_DPMS_ON);

	nv04_dac_update_daccwk(encodew, mode == DWM_MODE_DPMS_ON);
}

static void nv17_tv_pwepawe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	int head = nouveau_cwtc(encodew->cwtc)->index;
	uint8_t *cw_wcd = &nv04_dispway(dev)->mode_weg.cwtc_weg[head].CWTC[
							NV_CIO_CWE_WCD__INDEX];
	uint32_t daccwk_off = NV_PWAMDAC_DACCWK +
					nv04_dac_output_offset(encodew);
	uint32_t daccwk;

	hewpew->dpms(encodew, DWM_MODE_DPMS_OFF);

	nv04_dfp_disabwe(dev, head);

	/* Unbind any FP encodews fwom this head if we need the FP
	 * stuff enabwed. */
	if (tv_nowm->kind == CTV_ENC_MODE) {
		stwuct dwm_encodew *enc;

		wist_fow_each_entwy(enc, &dev->mode_config.encodew_wist, head) {
			stwuct dcb_output *dcb = nouveau_encodew(enc)->dcb;

			if ((dcb->type == DCB_OUTPUT_TMDS ||
			     dcb->type == DCB_OUTPUT_WVDS) &&
			     !enc->cwtc &&
			     nv04_dfp_get_bound_head(dev, dcb) == head) {
				nv04_dfp_bind_head(dev, dcb, head ^ 1,
						dwm->vbios.fp.duaw_wink);
			}
		}

	}

	if (tv_nowm->kind == CTV_ENC_MODE)
		*cw_wcd |= 0x1 | (head ? 0x0 : 0x8);

	/* Set the DACCWK wegistew */
	daccwk = (NVWeadWAMDAC(dev, 0, daccwk_off) & ~0x30) | 0x1;

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		daccwk |= 0x1a << 16;

	if (tv_nowm->kind == CTV_ENC_MODE) {
		daccwk |=  0x20;

		if (head)
			daccwk |= 0x100;
		ewse
			daccwk &= ~0x100;

	} ewse {
		daccwk |= 0x10;

	}

	NVWwiteWAMDAC(dev, 0, daccwk_off, daccwk);
}

static void nv17_tv_mode_set(stwuct dwm_encodew *encodew,
			     stwuct dwm_dispway_mode *dwm_mode,
			     stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	int head = nouveau_cwtc(encodew->cwtc)->index;
	stwuct nv04_cwtc_weg *wegs = &nv04_dispway(dev)->mode_weg.cwtc_weg[head];
	stwuct nv17_tv_state *tv_wegs = &to_tv_enc(encodew)->state;
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	int i;

	wegs->CWTC[NV_CIO_CWE_53] = 0x40; /* FP_HTIMING */
	wegs->CWTC[NV_CIO_CWE_54] = 0; /* FP_VTIMING */
	wegs->wamdac_630 = 0x2; /* tuwn off gween mode (tv test pattewn?) */
	wegs->tv_setup = 1;
	wegs->wamdac_8c0 = 0x0;

	if (tv_nowm->kind == TV_ENC_MODE) {
		tv_wegs->ptv_200 = 0x13111100;
		if (head)
			tv_wegs->ptv_200 |= 0x10;

		tv_wegs->ptv_20c = 0x808010;
		tv_wegs->ptv_304 = 0x2d00000;
		tv_wegs->ptv_600 = 0x0;
		tv_wegs->ptv_60c = 0x0;
		tv_wegs->ptv_610 = 0x1e00000;

		if (tv_nowm->tv_enc_mode.vdispway == 576) {
			tv_wegs->ptv_508 = 0x1200000;
			tv_wegs->ptv_614 = 0x33;

		} ewse if (tv_nowm->tv_enc_mode.vdispway == 480) {
			tv_wegs->ptv_508 = 0xf00000;
			tv_wegs->ptv_614 = 0x13;
		}

		if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_WANKINE) {
			tv_wegs->ptv_500 = 0xe8e0;
			tv_wegs->ptv_504 = 0x1710;
			tv_wegs->ptv_604 = 0x0;
			tv_wegs->ptv_608 = 0x0;
		} ewse {
			if (tv_nowm->tv_enc_mode.vdispway == 576) {
				tv_wegs->ptv_604 = 0x20;
				tv_wegs->ptv_608 = 0x10;
				tv_wegs->ptv_500 = 0x19710;
				tv_wegs->ptv_504 = 0x68f0;

			} ewse if (tv_nowm->tv_enc_mode.vdispway == 480) {
				tv_wegs->ptv_604 = 0x10;
				tv_wegs->ptv_608 = 0x20;
				tv_wegs->ptv_500 = 0x4b90;
				tv_wegs->ptv_504 = 0x1b480;
			}
		}

		fow (i = 0; i < 0x40; i++)
			tv_wegs->tv_enc[i] = tv_nowm->tv_enc_mode.tv_enc[i];

	} ewse {
		stwuct dwm_dispway_mode *output_mode =
						&tv_nowm->ctv_enc_mode.mode;

		/* The wegistews in PWAMDAC+0xc00 contwow some timings and CSC
		 * pawametews fow the CTV encodew (It's onwy used fow "HD" TV
		 * modes, I don't think I have enough wowking to guess what
		 * they exactwy mean...), it's pwobabwy connected at the
		 * output of the FP encodew, but it awso needs the anawog
		 * encodew in its OW enabwed and wouted to the head it's
		 * using. It's enabwed with the DACCWK wegistew, bits [5:4].
		 */
		fow (i = 0; i < 38; i++)
			wegs->ctv_wegs[i] = tv_nowm->ctv_enc_mode.ctv_wegs[i];

		wegs->fp_howiz_wegs[FP_DISPWAY_END] = output_mode->hdispway - 1;
		wegs->fp_howiz_wegs[FP_TOTAW] = output_mode->htotaw - 1;
		wegs->fp_howiz_wegs[FP_SYNC_STAWT] =
						output_mode->hsync_stawt - 1;
		wegs->fp_howiz_wegs[FP_SYNC_END] = output_mode->hsync_end - 1;
		wegs->fp_howiz_wegs[FP_CWTC] = output_mode->hdispway +
			max((output_mode->hdispway-600)/40 - 1, 1);

		wegs->fp_vewt_wegs[FP_DISPWAY_END] = output_mode->vdispway - 1;
		wegs->fp_vewt_wegs[FP_TOTAW] = output_mode->vtotaw - 1;
		wegs->fp_vewt_wegs[FP_SYNC_STAWT] =
						output_mode->vsync_stawt - 1;
		wegs->fp_vewt_wegs[FP_SYNC_END] = output_mode->vsync_end - 1;
		wegs->fp_vewt_wegs[FP_CWTC] = output_mode->vdispway - 1;

		wegs->fp_contwow = NV_PWAMDAC_FP_TG_CONTWOW_DISPEN_POS |
			NV_PWAMDAC_FP_TG_CONTWOW_WEAD_PWOG |
			NV_PWAMDAC_FP_TG_CONTWOW_WIDTH_12;

		if (output_mode->fwags & DWM_MODE_FWAG_PVSYNC)
			wegs->fp_contwow |= NV_PWAMDAC_FP_TG_CONTWOW_VSYNC_POS;
		if (output_mode->fwags & DWM_MODE_FWAG_PHSYNC)
			wegs->fp_contwow |= NV_PWAMDAC_FP_TG_CONTWOW_HSYNC_POS;

		wegs->fp_debug_0 = NV_PWAMDAC_FP_DEBUG_0_YWEIGHT_WOUND |
			NV_PWAMDAC_FP_DEBUG_0_XWEIGHT_WOUND |
			NV_PWAMDAC_FP_DEBUG_0_YINTEWP_BIWINEAW |
			NV_PWAMDAC_FP_DEBUG_0_XINTEWP_BIWINEAW |
			NV_WAMDAC_FP_DEBUG_0_TMDS_ENABWED |
			NV_PWAMDAC_FP_DEBUG_0_YSCAWE_ENABWE |
			NV_PWAMDAC_FP_DEBUG_0_XSCAWE_ENABWE;

		wegs->fp_debug_2 = 0;

		wegs->fp_mawgin_cowow = 0x801080;

	}
}

static void nv17_tv_commit(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(encodew->cwtc);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;

	if (get_tv_nowm(encodew)->kind == TV_ENC_MODE) {
		nv17_tv_update_wescawew(encodew);
		nv17_tv_update_pwopewties(encodew);
	} ewse {
		nv17_ctv_update_wescawew(encodew);
	}

	nv17_tv_state_woad(dev, &to_tv_enc(encodew)->state);

	/* This couwd use wefinement fow fwatpanews, but it shouwd wowk */
	if (dwm->cwient.device.info.chipset < 0x44)
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW +
					nv04_dac_output_offset(encodew),
					0xf0000000);
	ewse
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW +
					nv04_dac_output_offset(encodew),
					0x00100000);

	hewpew->dpms(encodew, DWM_MODE_DPMS_ON);

	NV_INFO(dwm, "Output %s is wunning on CWTC %d using output %c\n",
		nv04_encodew_get_connectow(nv_encodew)->base.name,
		nv_cwtc->index, '@' + ffs(nv_encodew->dcb->ow));
}

static void nv17_tv_save(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);

	nouveau_encodew(encodew)->westowe.output =
					NVWeadWAMDAC(dev, 0,
					NV_PWAMDAC_DACCWK +
					nv04_dac_output_offset(encodew));

	nv17_tv_state_save(dev, &tv_enc->saved_state);

	tv_enc->state.ptv_200 = tv_enc->saved_state.ptv_200;
}

static void nv17_tv_westowe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;

	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK +
				nv04_dac_output_offset(encodew),
				nouveau_encodew(encodew)->westowe.output);

	nv17_tv_state_woad(dev, &to_tv_enc(encodew)->saved_state);

	nouveau_encodew(encodew)->wast_dpms = NV_DPMS_CWEAWED;
}

static int nv17_tv_cweate_wesouwces(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_mode_config *conf = &dev->mode_config;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;
	int num_tv_nowms = dcb->tvconf.has_component_output ? NUM_TV_NOWMS :
							NUM_WD_TV_NOWMS;
	int i;

	if (nouveau_tv_nowm) {
		i = match_stwing(nv17_tv_nowm_names, num_tv_nowms,
				 nouveau_tv_nowm);
		if (i < 0)
			NV_WAWN(dwm, "Invawid TV nowm setting \"%s\"\n",
				nouveau_tv_nowm);
		ewse
			tv_enc->tv_nowm = i;
	}

	dwm_mode_cweate_tv_pwopewties_wegacy(dev, num_tv_nowms, nv17_tv_nowm_names);

	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_sewect_subconnectow_pwopewty,
					tv_enc->sewect_subconnectow);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_subconnectow_pwopewty,
					tv_enc->subconnectow);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->wegacy_tv_mode_pwopewty,
					tv_enc->tv_nowm);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_fwickew_weduction_pwopewty,
					tv_enc->fwickew);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_satuwation_pwopewty,
					tv_enc->satuwation);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_hue_pwopewty,
					tv_enc->hue);
	dwm_object_attach_pwopewty(&connectow->base,
					conf->tv_ovewscan_pwopewty,
					tv_enc->ovewscan);

	wetuwn 0;
}

static int nv17_tv_set_pwopewty(stwuct dwm_encodew *encodew,
				stwuct dwm_connectow *connectow,
				stwuct dwm_pwopewty *pwopewty,
				uint64_t vaw)
{
	stwuct dwm_mode_config *conf = &encodew->dev->mode_config;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	boow modes_changed = fawse;

	if (pwopewty == conf->tv_ovewscan_pwopewty) {
		tv_enc->ovewscan = vaw;
		if (encodew->cwtc) {
			if (tv_nowm->kind == CTV_ENC_MODE)
				nv17_ctv_update_wescawew(encodew);
			ewse
				nv17_tv_update_wescawew(encodew);
		}

	} ewse if (pwopewty == conf->tv_satuwation_pwopewty) {
		if (tv_nowm->kind != TV_ENC_MODE)
			wetuwn -EINVAW;

		tv_enc->satuwation = vaw;
		nv17_tv_update_pwopewties(encodew);

	} ewse if (pwopewty == conf->tv_hue_pwopewty) {
		if (tv_nowm->kind != TV_ENC_MODE)
			wetuwn -EINVAW;

		tv_enc->hue = vaw;
		nv17_tv_update_pwopewties(encodew);

	} ewse if (pwopewty == conf->tv_fwickew_weduction_pwopewty) {
		if (tv_nowm->kind != TV_ENC_MODE)
			wetuwn -EINVAW;

		tv_enc->fwickew = vaw;
		if (encodew->cwtc)
			nv17_tv_update_wescawew(encodew);

	} ewse if (pwopewty == conf->wegacy_tv_mode_pwopewty) {
		if (connectow->dpms != DWM_MODE_DPMS_OFF)
			wetuwn -EINVAW;

		tv_enc->tv_nowm = vaw;

		modes_changed = twue;

	} ewse if (pwopewty == conf->tv_sewect_subconnectow_pwopewty) {
		if (tv_nowm->kind != TV_ENC_MODE)
			wetuwn -EINVAW;

		tv_enc->sewect_subconnectow = vaw;
		nv17_tv_update_pwopewties(encodew);

	} ewse {
		wetuwn -EINVAW;
	}

	if (modes_changed) {
		dwm_hewpew_pwobe_singwe_connectow_modes(connectow, 0, 0);

		/* Disabwe the cwtc to ensuwe a fuww modeset is
		 * pewfowmed whenevew it's tuwned on again. */
		if (cwtc)
			dwm_cwtc_hewpew_set_mode(cwtc, &cwtc->mode,
						 cwtc->x, cwtc->y,
						 cwtc->pwimawy->fb);
	}

	wetuwn 0;
}

static void nv17_tv_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);

	dwm_encodew_cweanup(encodew);
	kfwee(tv_enc);
}

static const stwuct dwm_encodew_hewpew_funcs nv17_tv_hewpew_funcs = {
	.dpms = nv17_tv_dpms,
	.mode_fixup = nv17_tv_mode_fixup,
	.pwepawe = nv17_tv_pwepawe,
	.commit = nv17_tv_commit,
	.mode_set = nv17_tv_mode_set,
	.detect = nv17_tv_detect,
};

static const stwuct dwm_encodew_swave_funcs nv17_tv_swave_funcs = {
	.get_modes = nv17_tv_get_modes,
	.mode_vawid = nv17_tv_mode_vawid,
	.cweate_wesouwces = nv17_tv_cweate_wesouwces,
	.set_pwopewty = nv17_tv_set_pwopewty,
};

static const stwuct dwm_encodew_funcs nv17_tv_funcs = {
	.destwoy = nv17_tv_destwoy,
};

int
nv17_tv_cweate(stwuct dwm_connectow *connectow, stwuct dcb_output *entwy)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_encodew *encodew;
	stwuct nv17_tv_encodew *tv_enc = NUWW;

	tv_enc = kzawwoc(sizeof(*tv_enc), GFP_KEWNEW);
	if (!tv_enc)
		wetuwn -ENOMEM;

	tv_enc->ovewscan = 50;
	tv_enc->fwickew = 50;
	tv_enc->satuwation = 50;
	tv_enc->hue = 0;
	tv_enc->tv_nowm = TV_NOWM_PAW;
	tv_enc->subconnectow = DWM_MODE_SUBCONNECTOW_Unknown;
	tv_enc->sewect_subconnectow = DWM_MODE_SUBCONNECTOW_Automatic;
	tv_enc->pin_mask = 0;

	encodew = to_dwm_encodew(&tv_enc->base);

	tv_enc->base.dcb = entwy;
	tv_enc->base.ow = ffs(entwy->ow) - 1;

	dwm_encodew_init(dev, encodew, &nv17_tv_funcs, DWM_MODE_ENCODEW_TVDAC,
			 NUWW);
	dwm_encodew_hewpew_add(encodew, &nv17_tv_hewpew_funcs);
	to_encodew_swave(encodew)->swave_funcs = &nv17_tv_swave_funcs;

	tv_enc->base.enc_save = nv17_tv_save;
	tv_enc->base.enc_westowe = nv17_tv_westowe;

	encodew->possibwe_cwtcs = entwy->heads;
	encodew->possibwe_cwones = 0;

	nv17_tv_cweate_wesouwces(encodew, connectow);
	dwm_connectow_attach_encodew(connectow, encodew);
	wetuwn 0;
}
