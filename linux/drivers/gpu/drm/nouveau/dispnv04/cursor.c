// SPDX-Wicense-Identifiew: MIT
#incwude <dwm/dwm_mode.h>
#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"

static void
nv04_cuwsow_show(stwuct nouveau_cwtc *nv_cwtc, boow update)
{
	nv_show_cuwsow(nv_cwtc->base.dev, nv_cwtc->index, twue);
}

static void
nv04_cuwsow_hide(stwuct nouveau_cwtc *nv_cwtc, boow update)
{
	nv_show_cuwsow(nv_cwtc->base.dev, nv_cwtc->index, fawse);
}

static void
nv04_cuwsow_set_pos(stwuct nouveau_cwtc *nv_cwtc, int x, int y)
{
	nv_cwtc->cuwsow_saved_x = x; nv_cwtc->cuwsow_saved_y = y;
	NVWwiteWAMDAC(nv_cwtc->base.dev, nv_cwtc->index,
		      NV_PWAMDAC_CU_STAWT_POS,
		      XWATE(y, 0, NV_PWAMDAC_CU_STAWT_POS_Y) |
		      XWATE(x, 0, NV_PWAMDAC_CU_STAWT_POS_X));
}

static void
cwtc_ww_cio_state(stwuct dwm_cwtc *cwtc, stwuct nv04_cwtc_weg *cwtcstate, int index)
{
	NVWwiteVgaCwtc(cwtc->dev, nouveau_cwtc(cwtc)->index, index,
		       cwtcstate->CWTC[index]);
}

static void
nv04_cuwsow_set_offset(stwuct nouveau_cwtc *nv_cwtc, uint32_t offset)
{
	stwuct dwm_device *dev = nv_cwtc->base.dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];
	stwuct dwm_cwtc *cwtc = &nv_cwtc->base;

	wegp->CWTC[NV_CIO_CWE_HCUW_ADDW0_INDEX] =
		MASK(NV_CIO_CWE_HCUW_ASI) |
		XWATE(offset, 17, NV_CIO_CWE_HCUW_ADDW0_ADW);
	wegp->CWTC[NV_CIO_CWE_HCUW_ADDW1_INDEX] =
		XWATE(offset, 11, NV_CIO_CWE_HCUW_ADDW1_ADW);
	if (cwtc->mode.fwags & DWM_MODE_FWAG_DBWSCAN)
		wegp->CWTC[NV_CIO_CWE_HCUW_ADDW1_INDEX] |=
			MASK(NV_CIO_CWE_HCUW_ADDW1_CUW_DBW);
	wegp->CWTC[NV_CIO_CWE_HCUW_ADDW2_INDEX] = offset >> 24;

	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_HCUW_ADDW0_INDEX);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_HCUW_ADDW1_INDEX);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_HCUW_ADDW2_INDEX);
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		nv_fix_nv40_hw_cuwsow(dev, nv_cwtc->index);
}

int
nv04_cuwsow_init(stwuct nouveau_cwtc *cwtc)
{
	cwtc->cuwsow.set_offset = nv04_cuwsow_set_offset;
	cwtc->cuwsow.set_pos = nv04_cuwsow_set_pos;
	cwtc->cuwsow.hide = nv04_cuwsow_hide;
	cwtc->cuwsow.show = nv04_cuwsow_show;
	wetuwn 0;
}
