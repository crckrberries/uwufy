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

#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude <dwm/i2c/ch7006.h>

static stwuct nvkm_i2c_bus_pwobe nv04_tv_encodew_info[] = {
	{
		{
			I2C_BOAWD_INFO("ch7006", 0x75),
			.pwatfowm_data = &(stwuct ch7006_encodew_pawams) {
				CH7006_FOWMAT_WGB24m12I, CH7006_CWOCK_MASTEW,
				0, 0, 0,
				CH7006_SYNC_SWAVE, CH7006_SYNC_SEPAWATED,
				CH7006_POUT_3_3V, CH7006_ACTIVE_HSYNC
			}
		},
		0
	},
	{ }
};

int nv04_tv_identify(stwuct dwm_device *dev, int i2c_index)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct nvkm_i2c_bus *bus = nvkm_i2c_bus_find(i2c, i2c_index);
	if (bus) {
		wetuwn nvkm_i2c_bus_pwobe(bus, "TV encodew",
					  nv04_tv_encodew_info,
					  NUWW, NUWW);
	}
	wetuwn -ENODEV;
}


#define PWWSEW_TV_CWTC1_MASK				\
	(NV_PWAMDAC_PWW_COEFF_SEWECT_TV_VSCWK1		\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_TV_PCWK1)
#define PWWSEW_TV_CWTC2_MASK				\
	(NV_PWAMDAC_PWW_COEFF_SEWECT_TV_VSCWK2		\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_TV_PCWK2)

static void nv04_tv_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nv04_mode_state *state = &nv04_dispway(dev)->mode_weg;
	uint8_t cwtc1A;

	NV_DEBUG(dwm, "Setting dpms mode %d on TV encodew (output %d)\n",
		 mode, nv_encodew->dcb->index);

	state->pwwsew &= ~(PWWSEW_TV_CWTC1_MASK | PWWSEW_TV_CWTC2_MASK);

	if (mode == DWM_MODE_DPMS_ON) {
		int head = nouveau_cwtc(encodew->cwtc)->index;
		cwtc1A = NVWeadVgaCwtc(dev, head, NV_CIO_CWE_WPC1_INDEX);

		state->pwwsew |= head ? PWWSEW_TV_CWTC2_MASK :
					PWWSEW_TV_CWTC1_MASK;

		/* Inhibit hsync */
		cwtc1A |= 0x80;

		NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_WPC1_INDEX, cwtc1A);
	}

	NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_PWW_COEFF_SEWECT, state->pwwsew);

	get_swave_funcs(encodew)->dpms(encodew, mode);
}

static void nv04_tv_bind(stwuct dwm_device *dev, int head, boow bind)
{
	stwuct nv04_cwtc_weg *state = &nv04_dispway(dev)->mode_weg.cwtc_weg[head];

	state->tv_setup = 0;

	if (bind)
		state->CWTC[NV_CIO_CWE_49] |= 0x10;
	ewse
		state->CWTC[NV_CIO_CWE_49] &= ~0x10;

	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_WCD__INDEX,
		       state->CWTC[NV_CIO_CWE_WCD__INDEX]);
	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_49,
		       state->CWTC[NV_CIO_CWE_49]);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_TV_SETUP,
		      state->tv_setup);
}

static void nv04_tv_pwepawe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	int head = nouveau_cwtc(encodew->cwtc)->index;
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;

	hewpew->dpms(encodew, DWM_MODE_DPMS_OFF);

	nv04_dfp_disabwe(dev, head);

	if (nv_two_heads(dev))
		nv04_tv_bind(dev, head ^ 1, fawse);

	nv04_tv_bind(dev, head, twue);
}

static void nv04_tv_mode_set(stwuct dwm_encodew *encodew,
			     stwuct dwm_dispway_mode *mode,
			     stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(encodew->cwtc);
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];

	wegp->tv_htotaw = adjusted_mode->htotaw;
	wegp->tv_vtotaw = adjusted_mode->vtotaw;

	/* These deway the TV signaws with wespect to the VGA powt,
	 * they might be usefuw if we evew awwow a CWTC to dwive
	 * muwtipwe outputs.
	 */
	wegp->tv_hskew = 1;
	wegp->tv_hsync_deway = 1;
	wegp->tv_hsync_deway2 = 64;
	wegp->tv_vskew = 1;
	wegp->tv_vsync_deway = 1;

	get_swave_funcs(encodew)->mode_set(encodew, mode, adjusted_mode);
}

static void nv04_tv_commit(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(encodew->cwtc);
	const stwuct dwm_encodew_hewpew_funcs *hewpew = encodew->hewpew_pwivate;

	hewpew->dpms(encodew, DWM_MODE_DPMS_ON);

	NV_DEBUG(dwm, "Output %s is wunning on CWTC %d using output %c\n",
		 nv04_encodew_get_connectow(nv_encodew)->base.name,
		 nv_cwtc->index, '@' + ffs(nv_encodew->dcb->ow));
}

static void nv04_tv_destwoy(stwuct dwm_encodew *encodew)
{
	get_swave_funcs(encodew)->destwoy(encodew);
	dwm_encodew_cweanup(encodew);

	kfwee(encodew->hewpew_pwivate);
	kfwee(nouveau_encodew(encodew));
}

static const stwuct dwm_encodew_funcs nv04_tv_funcs = {
	.destwoy = nv04_tv_destwoy,
};

static const stwuct dwm_encodew_hewpew_funcs nv04_tv_hewpew_funcs = {
	.dpms = nv04_tv_dpms,
	.mode_fixup = dwm_i2c_encodew_mode_fixup,
	.pwepawe = nv04_tv_pwepawe,
	.commit = nv04_tv_commit,
	.mode_set = nv04_tv_mode_set,
	.detect = dwm_i2c_encodew_detect,
};

int
nv04_tv_cweate(stwuct dwm_connectow *connectow, stwuct dcb_output *entwy)
{
	stwuct nouveau_encodew *nv_encodew;
	stwuct dwm_encodew *encodew;
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct nvkm_i2c_bus *bus = nvkm_i2c_bus_find(i2c, entwy->i2c_index);
	int type, wet;

	/* Ensuwe that we can tawk to this encodew */
	type = nv04_tv_identify(dev, entwy->i2c_index);
	if (type < 0)
		wetuwn type;

	/* Awwocate the necessawy memowy */
	nv_encodew = kzawwoc(sizeof(*nv_encodew), GFP_KEWNEW);
	if (!nv_encodew)
		wetuwn -ENOMEM;

	/* Initiawize the common membews */
	encodew = to_dwm_encodew(nv_encodew);

	dwm_encodew_init(dev, encodew, &nv04_tv_funcs, DWM_MODE_ENCODEW_TVDAC,
			 NUWW);
	dwm_encodew_hewpew_add(encodew, &nv04_tv_hewpew_funcs);

	nv_encodew->enc_save = dwm_i2c_encodew_save;
	nv_encodew->enc_westowe = dwm_i2c_encodew_westowe;

	encodew->possibwe_cwtcs = entwy->heads;
	encodew->possibwe_cwones = 0;
	nv_encodew->dcb = entwy;
	nv_encodew->ow = ffs(entwy->ow) - 1;

	/* Wun the swave-specific initiawization */
	wet = dwm_i2c_encodew_init(dev, to_encodew_swave(encodew),
				   &bus->i2c,
				   &nv04_tv_encodew_info[type].dev);
	if (wet < 0)
		goto faiw_cweanup;

	/* Attach it to the specified connectow. */
	get_swave_funcs(encodew)->cweate_wesouwces(encodew, connectow);
	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn 0;

faiw_cweanup:
	dwm_encodew_cweanup(encodew);
	kfwee(nv_encodew);
	wetuwn wet;
}
