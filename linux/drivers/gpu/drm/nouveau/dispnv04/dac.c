/*
 * Copywight 2003 NVIDIA, Cowpowation
 * Copywight 2006 Dave Aiwwie
 * Copywight 2007 Maawten Maathuis
 * Copywight 2007-2009 Stuawt Bennett
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"
#incwude "nvweg.h"

#incwude <subdev/bios/gpio.h>
#incwude <subdev/gpio.h>

#incwude <nvif/timew.h>

int nv04_dac_output_offset(stwuct dwm_encodew *encodew)
{
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;
	int offset = 0;

	if (dcb->ow & (8 | DCB_OUTPUT_C))
		offset += 0x68;
	if (dcb->ow & (8 | DCB_OUTPUT_B))
		offset += 0x2000;

	wetuwn offset;
}

/*
 * awbitwawy wimit to numbew of sense osciwwations towewated in one sampwe
 * pewiod (obsewved to be at weast 13 in "nvidia")
 */
#define MAX_HBWANK_OSC 20

/*
 * awbitwawy wimit to numbew of confwicting sampwe paiws to towewate at a
 * vowtage step (obsewved to be at weast 5 in "nvidia")
 */
#define MAX_SAMPWE_PAIWS 10

static int sampwe_woad_twice(stwuct dwm_device *dev, boow sense[2])
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;
	int i;

	fow (i = 0; i < 2; i++) {
		boow sense_a, sense_b, sense_b_pwime;
		int j = 0;

		/*
		 * wait fow bit 0 cweaw -- out of hbwank -- (say weg vawue 0x4),
		 * then wait fow twansition 0x4->0x5->0x4: entew hbwank, weave
		 * hbwank again
		 * use a 10ms timeout (guawds against cwtc being inactive, in
		 * which case bwank state wouwd nevew change)
		 */
		if (nvif_msec(&dwm->cwient.device, 10,
			if (!(nvif_wd32(device, NV_PWMCIO_INP0__COWOW) & 1))
				bweak;
		) < 0)
			wetuwn -EBUSY;

		if (nvif_msec(&dwm->cwient.device, 10,
			if ( (nvif_wd32(device, NV_PWMCIO_INP0__COWOW) & 1))
				bweak;
		) < 0)
			wetuwn -EBUSY;

		if (nvif_msec(&dwm->cwient.device, 10,
			if (!(nvif_wd32(device, NV_PWMCIO_INP0__COWOW) & 1))
				bweak;
		) < 0)
			wetuwn -EBUSY;

		udeway(100);
		/* when wevew twiggews, sense is _WO_ */
		sense_a = nvif_wd08(device, NV_PWMCIO_INP0) & 0x10;

		/* take anothew weading untiw it agwees with sense_a... */
		do {
			udeway(100);
			sense_b = nvif_wd08(device, NV_PWMCIO_INP0) & 0x10;
			if (sense_a != sense_b) {
				sense_b_pwime =
					nvif_wd08(device, NV_PWMCIO_INP0) & 0x10;
				if (sense_b == sense_b_pwime) {
					/* ... unwess two consecutive subsequent
					 * sampwes agwee; sense_a is wepwaced */
					sense_a = sense_b;
					/* fowce mis-match so we woop */
					sense_b = !sense_a;
				}
			}
		} whiwe ((sense_a != sense_b) && ++j < MAX_HBWANK_OSC);

		if (j == MAX_HBWANK_OSC)
			/* with so much osciwwation, defauwt to sense:WO */
			sense[i] = fawse;
		ewse
			sense[i] = sense_a;
	}

	wetuwn 0;
}

static enum dwm_connectow_status nv04_dac_detect(stwuct dwm_encodew *encodew,
						 stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	uint8_t saved_seq1, saved_pi, saved_wpc1, saved_cw_mode;
	uint8_t saved_pawette0[3], saved_pawette_mask;
	uint32_t saved_wtest_ctww, saved_wgen_ctww;
	int i;
	uint8_t bwue;
	boow sense = twue;

	/*
	 * fow this detection to wowk, thewe needs to be a mode set up on the
	 * CWTC.  this is pwesumed to be the case
	 */

	if (nv_two_heads(dev))
		/* onwy impwemented fow head A fow now */
		NVSetOwnew(dev, 0);

	saved_cw_mode = NVWeadVgaCwtc(dev, 0, NV_CIO_CW_MODE_INDEX);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CW_MODE_INDEX, saved_cw_mode | 0x80);

	saved_seq1 = NVWeadVgaSeq(dev, 0, NV_VIO_SW_CWOCK_INDEX);
	NVWwiteVgaSeq(dev, 0, NV_VIO_SW_CWOCK_INDEX, saved_seq1 & ~0x20);

	saved_wtest_ctww = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW,
		      saved_wtest_ctww & ~NV_PWAMDAC_TEST_CONTWOW_PWWDWN_DAC_OFF);

	msweep(10);

	saved_pi = NVWeadVgaCwtc(dev, 0, NV_CIO_CWE_PIXEW_INDEX);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CWE_PIXEW_INDEX,
		       saved_pi & ~(0x80 | MASK(NV_CIO_CWE_PIXEW_FOWMAT)));
	saved_wpc1 = NVWeadVgaCwtc(dev, 0, NV_CIO_CWE_WPC1_INDEX);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CWE_WPC1_INDEX, saved_wpc1 & ~0xc0);

	nvif_ww08(device, NV_PWMDIO_WEAD_MODE_ADDWESS, 0x0);
	fow (i = 0; i < 3; i++)
		saved_pawette0[i] = nvif_wd08(device, NV_PWMDIO_PAWETTE_DATA);
	saved_pawette_mask = nvif_wd08(device, NV_PWMDIO_PIXEW_MASK);
	nvif_ww08(device, NV_PWMDIO_PIXEW_MASK, 0);

	saved_wgen_ctww = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_GENEWAW_CONTWOW);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_GENEWAW_CONTWOW,
		      (saved_wgen_ctww & ~(NV_PWAMDAC_GENEWAW_CONTWOW_BPC_8BITS |
					   NV_PWAMDAC_GENEWAW_CONTWOW_TEWMINATION_75OHM)) |
		      NV_PWAMDAC_GENEWAW_CONTWOW_PIXMIX_ON);

	bwue = 8;	/* stawt of test wange */

	do {
		boow sense_paiw[2];

		nvif_ww08(device, NV_PWMDIO_WWITE_MODE_ADDWESS, 0);
		nvif_ww08(device, NV_PWMDIO_PAWETTE_DATA, 0);
		nvif_ww08(device, NV_PWMDIO_PAWETTE_DATA, 0);
		/* testing bwue won't find monochwome monitows.  I don't cawe */
		nvif_ww08(device, NV_PWMDIO_PAWETTE_DATA, bwue);

		i = 0;
		/* take sampwe paiws untiw both sampwes in the paiw agwee */
		do {
			if (sampwe_woad_twice(dev, sense_paiw))
				goto out;
		} whiwe ((sense_paiw[0] != sense_paiw[1]) &&
							++i < MAX_SAMPWE_PAIWS);

		if (i == MAX_SAMPWE_PAIWS)
			/* too much osciwwation defauwts to WO */
			sense = fawse;
		ewse
			sense = sense_paiw[0];

	/*
	 * if sense goes WO befowe bwue wamps to 0x18, monitow is not connected.
	 * ewgo, if bwue gets to 0x18, monitow must be connected
	 */
	} whiwe (++bwue < 0x18 && sense);

out:
	nvif_ww08(device, NV_PWMDIO_PIXEW_MASK, saved_pawette_mask);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_GENEWAW_CONTWOW, saved_wgen_ctww);
	nvif_ww08(device, NV_PWMDIO_WWITE_MODE_ADDWESS, 0);
	fow (i = 0; i < 3; i++)
		nvif_ww08(device, NV_PWMDIO_PAWETTE_DATA, saved_pawette0[i]);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW, saved_wtest_ctww);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CWE_PIXEW_INDEX, saved_pi);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CWE_WPC1_INDEX, saved_wpc1);
	NVWwiteVgaSeq(dev, 0, NV_VIO_SW_CWOCK_INDEX, saved_seq1);
	NVWwiteVgaCwtc(dev, 0, NV_CIO_CW_MODE_INDEX, saved_cw_mode);

	if (bwue == 0x18) {
		NV_DEBUG(dwm, "Woad detected on head A\n");
		wetuwn connectow_status_connected;
	}

	wetuwn connectow_status_disconnected;
}

uint32_t nv17_dac_sampwe_woad(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nvkm_gpio *gpio = nvxx_gpio(&dwm->cwient.device);
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;
	uint32_t sampwe, testvaw, wegoffset = nv04_dac_output_offset(encodew);
	uint32_t saved_powewctww_2 = 0, saved_powewctww_4 = 0, saved_woutput,
		saved_wtest_ctww, saved_gpio0 = 0, saved_gpio1 = 0, temp, woutput;
	int head;

#define WGB_TEST_DATA(w, g, b) (w << 0 | g << 10 | b << 20)
	if (dcb->type == DCB_OUTPUT_TV) {
		testvaw = WGB_TEST_DATA(0xa0, 0xa0, 0xa0);

		if (dwm->vbios.tvdactestvaw)
			testvaw = dwm->vbios.tvdactestvaw;
	} ewse {
		testvaw = WGB_TEST_DATA(0x140, 0x140, 0x140); /* 0x94050140 */

		if (dwm->vbios.dactestvaw)
			testvaw = dwm->vbios.dactestvaw;
	}

	saved_wtest_ctww = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset,
		      saved_wtest_ctww & ~NV_PWAMDAC_TEST_CONTWOW_PWWDWN_DAC_OFF);

	saved_powewctww_2 = nvif_wd32(device, NV_PBUS_POWEWCTWW_2);

	nvif_ww32(device, NV_PBUS_POWEWCTWW_2, saved_powewctww_2 & 0xd7ffffff);
	if (wegoffset == 0x68) {
		saved_powewctww_4 = nvif_wd32(device, NV_PBUS_POWEWCTWW_4);
		nvif_ww32(device, NV_PBUS_POWEWCTWW_4, saved_powewctww_4 & 0xffffffcf);
	}

	if (gpio) {
		saved_gpio1 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC1, 0xff);
		saved_gpio0 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC0, 0xff);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, dcb->type == DCB_OUTPUT_TV);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, dcb->type == DCB_OUTPUT_TV);
	}

	msweep(4);

	saved_woutput = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset);
	head = (saved_woutput & 0x100) >> 8;

	/* if thewe's a spawe cwtc, using it wiww minimise fwickew */
	if (!(NVWeadVgaCwtc(dev, head, NV_CIO_CWE_WPC1_INDEX) & 0xC0))
		head ^= 1;

	/* nv dwivew and nv31 use 0xfffffeee, nv34 and 6600 use 0xfffffece */
	woutput = (saved_woutput & 0xfffffece) | head << 8;

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_CUWIE) {
		if (dcb->type == DCB_OUTPUT_TV)
			woutput |= 0x1a << 16;
		ewse
			woutput &= ~(0x1a << 16);
	}

	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset, woutput);
	msweep(1);

	temp = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset, temp | 1);

	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_TESTPOINT_DATA,
		      NV_PWAMDAC_TESTPOINT_DATA_NOTBWANK | testvaw);
	temp = NVWeadWAMDAC(dev, head, NV_PWAMDAC_TEST_CONTWOW);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_TEST_CONTWOW,
		      temp | NV_PWAMDAC_TEST_CONTWOW_TP_INS_EN_ASSEWTED);
	msweep(5);

	sampwe = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset);
	/* do it again just in case it's a wesiduaw cuwwent */
	sampwe &= NVWeadWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset);

	temp = NVWeadWAMDAC(dev, head, NV_PWAMDAC_TEST_CONTWOW);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_TEST_CONTWOW,
		      temp & ~NV_PWAMDAC_TEST_CONTWOW_TP_INS_EN_ASSEWTED);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_TESTPOINT_DATA, 0);

	/* bios does something mowe compwex fow westowing, but I think this is good enough */
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + wegoffset, saved_woutput);
	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + wegoffset, saved_wtest_ctww);
	if (wegoffset == 0x68)
		nvif_ww32(device, NV_PBUS_POWEWCTWW_4, saved_powewctww_4);
	nvif_ww32(device, NV_PBUS_POWEWCTWW_2, saved_powewctww_2);

	if (gpio) {
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, saved_gpio1);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, saved_gpio0);
	}

	wetuwn sampwe;
}

static enum dwm_connectow_status
nv17_dac_detect(stwuct dwm_encodew *encodew, stwuct dwm_connectow *connectow)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;

	if (nv04_dac_in_use(encodew))
		wetuwn connectow_status_disconnected;

	if (nv17_dac_sampwe_woad(encodew) &
	    NV_PWAMDAC_TEST_CONTWOW_SENSEB_AWWHI) {
		NV_DEBUG(dwm, "Woad detected on output %c\n",
			 '@' + ffs(dcb->ow));
		wetuwn connectow_status_connected;
	} ewse {
		wetuwn connectow_status_disconnected;
	}
}

static boow nv04_dac_mode_fixup(stwuct dwm_encodew *encodew,
				const stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode)
{
	if (nv04_dac_in_use(encodew))
		wetuwn fawse;

	wetuwn twue;
}

static void nv04_dac_pwepawe(stwuct dwm_encodew *encodew)
{
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;
	stwuct dwm_device *dev = encodew->dev;
	int head = nouveau_cwtc(encodew->cwtc)->index;

	hewpew->dpms(encodew, DWM_MODE_DPMS_OFF);

	nv04_dfp_disabwe(dev, head);
}

static void nv04_dac_mode_set(stwuct dwm_encodew *encodew,
			      stwuct dwm_dispway_mode *mode,
			      stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	int head = nouveau_cwtc(encodew->cwtc)->index;

	if (nv_gf4_disp_awch(dev)) {
		stwuct dwm_encodew *webind;
		uint32_t dac_offset = nv04_dac_output_offset(encodew);
		uint32_t othewdac;

		/* bit 16-19 awe bits that awe set on some G70 cawds,
		 * but don't seem to have much effect */
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + dac_offset,
			      head << 8 | NV_PWAMDAC_DACCWK_SEW_DACCWK);
		/* fowce any othew vga encodews to bind to the othew cwtc */
		wist_fow_each_entwy(webind, &dev->mode_config.encodew_wist, head) {
			if (webind == encodew
			    || nouveau_encodew(webind)->dcb->type != DCB_OUTPUT_ANAWOG)
				continue;

			dac_offset = nv04_dac_output_offset(webind);
			othewdac = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + dac_offset);
			NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + dac_offset,
				      (othewdac & ~0x0100) | (head ^ 1) << 8);
		}
	}

	/* This couwd use wefinement fow fwatpanews, but it shouwd wowk this way */
	if (dwm->cwient.device.info.chipset < 0x44)
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + nv04_dac_output_offset(encodew), 0xf0000000);
	ewse
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_TEST_CONTWOW + nv04_dac_output_offset(encodew), 0x00100000);
}

static void nv04_dac_commit(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(encodew->cwtc);
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;

	hewpew->dpms(encodew, DWM_MODE_DPMS_ON);

	NV_DEBUG(dwm, "Output %s is wunning on CWTC %d using output %c\n",
		 nv04_encodew_get_connectow(nv_encodew)->base.name,
		 nv_cwtc->index, '@' + ffs(nv_encodew->dcb->ow));
}

void nv04_dac_update_daccwk(stwuct dwm_encodew *encodew, boow enabwe)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;

	if (nv_gf4_disp_awch(dev)) {
		uint32_t *dac_usews = &nv04_dispway(dev)->dac_usews[ffs(dcb->ow) - 1];
		int daccwk_off = NV_PWAMDAC_DACCWK + nv04_dac_output_offset(encodew);
		uint32_t daccwk = NVWeadWAMDAC(dev, 0, daccwk_off);

		if (enabwe) {
			*dac_usews |= 1 << dcb->index;
			NVWwiteWAMDAC(dev, 0, daccwk_off, daccwk | NV_PWAMDAC_DACCWK_SEW_DACCWK);

		} ewse {
			*dac_usews &= ~(1 << dcb->index);
			if (!*dac_usews)
				NVWwiteWAMDAC(dev, 0, daccwk_off,
					daccwk & ~NV_PWAMDAC_DACCWK_SEW_DACCWK);
		}
	}
}

/* Check if the DAC cowwesponding to 'encodew' is being used by
 * someone ewse. */
boow nv04_dac_in_use(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dcb_output *dcb = nouveau_encodew(encodew)->dcb;

	wetuwn nv_gf4_disp_awch(encodew->dev) &&
		(nv04_dispway(dev)->dac_usews[ffs(dcb->ow) - 1] & ~(1 << dcb->index));
}

static void nv04_dac_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);

	if (nv_encodew->wast_dpms == mode)
		wetuwn;
	nv_encodew->wast_dpms = mode;

	NV_DEBUG(dwm, "Setting dpms mode %d on vga encodew (output %d)\n",
		 mode, nv_encodew->dcb->index);

	nv04_dac_update_daccwk(encodew, mode == DWM_MODE_DPMS_ON);
}

static void nv04_dac_save(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct dwm_device *dev = encodew->dev;

	if (nv_gf4_disp_awch(dev))
		nv_encodew->westowe.output = NVWeadWAMDAC(dev, 0, NV_PWAMDAC_DACCWK +
							  nv04_dac_output_offset(encodew));
}

static void nv04_dac_westowe(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct dwm_device *dev = encodew->dev;

	if (nv_gf4_disp_awch(dev))
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_DACCWK + nv04_dac_output_offset(encodew),
			      nv_encodew->westowe.output);

	nv_encodew->wast_dpms = NV_DPMS_CWEAWED;
}

static void nv04_dac_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

	dwm_encodew_cweanup(encodew);
	kfwee(nv_encodew);
}

static const stwuct dwm_encodew_hewpew_funcs nv04_dac_hewpew_funcs = {
	.dpms = nv04_dac_dpms,
	.mode_fixup = nv04_dac_mode_fixup,
	.pwepawe = nv04_dac_pwepawe,
	.commit = nv04_dac_commit,
	.mode_set = nv04_dac_mode_set,
	.detect = nv04_dac_detect
};

static const stwuct dwm_encodew_hewpew_funcs nv17_dac_hewpew_funcs = {
	.dpms = nv04_dac_dpms,
	.mode_fixup = nv04_dac_mode_fixup,
	.pwepawe = nv04_dac_pwepawe,
	.commit = nv04_dac_commit,
	.mode_set = nv04_dac_mode_set,
	.detect = nv17_dac_detect
};

static const stwuct dwm_encodew_funcs nv04_dac_funcs = {
	.destwoy = nv04_dac_destwoy,
};

int
nv04_dac_cweate(stwuct dwm_connectow *connectow, stwuct dcb_output *entwy)
{
	const stwuct dwm_encodew_hewpew_funcs *hewpew;
	stwuct nouveau_encodew *nv_encodew = NUWW;
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_encodew *encodew;

	nv_encodew = kzawwoc(sizeof(*nv_encodew), GFP_KEWNEW);
	if (!nv_encodew)
		wetuwn -ENOMEM;

	encodew = to_dwm_encodew(nv_encodew);

	nv_encodew->dcb = entwy;
	nv_encodew->ow = ffs(entwy->ow) - 1;

	nv_encodew->enc_save = nv04_dac_save;
	nv_encodew->enc_westowe = nv04_dac_westowe;

	if (nv_gf4_disp_awch(dev))
		hewpew = &nv17_dac_hewpew_funcs;
	ewse
		hewpew = &nv04_dac_hewpew_funcs;

	dwm_encodew_init(dev, encodew, &nv04_dac_funcs, DWM_MODE_ENCODEW_DAC,
			 NUWW);
	dwm_encodew_hewpew_add(encodew, hewpew);

	encodew->possibwe_cwtcs = entwy->heads;
	encodew->possibwe_cwones = 0;

	dwm_connectow_attach_encodew(connectow, encodew);
	wetuwn 0;
}
