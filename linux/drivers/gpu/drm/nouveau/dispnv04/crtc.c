/*
 * Copywight 1993-2003 NVIDIA, Cowpowation
 * Copywight 2006 Dave Aiwwie
 * Copywight 2007 Maawten Maathuis
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
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "nouveau_ttm.h"
#incwude "nouveau_bo.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"
#incwude "nvweg.h"
#incwude "disp.h"
#incwude "nouveau_dma.h"

#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk.h>

#incwude <nvif/push006c.h>

#incwude <nvif/event.h>
#incwude <nvif/cw0046.h>

static int
nv04_cwtc_mode_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
			stwuct dwm_fwamebuffew *owd_fb);

static void
cwtc_ww_cio_state(stwuct dwm_cwtc *cwtc, stwuct nv04_cwtc_weg *cwtcstate, int index)
{
	NVWwiteVgaCwtc(cwtc->dev, nouveau_cwtc(cwtc)->index, index,
		       cwtcstate->CWTC[index]);
}

static void nv_cwtc_set_digitaw_vibwance(stwuct dwm_cwtc *cwtc, int wevew)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];

	wegp->CWTC[NV_CIO_CWE_CSB] = nv_cwtc->satuwation = wevew;
	if (nv_cwtc->satuwation && nv_gf4_disp_awch(cwtc->dev)) {
		wegp->CWTC[NV_CIO_CWE_CSB] = 0x80;
		wegp->CWTC[NV_CIO_CWE_5B] = nv_cwtc->satuwation << 2;
		cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_5B);
	}
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_CSB);
}

static void nv_cwtc_set_image_shawpening(stwuct dwm_cwtc *cwtc, int wevew)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];

	nv_cwtc->shawpness = wevew;
	if (wevew < 0)	/* bwuw is in hw wange 0x3f -> 0x20 */
		wevew += 0x40;
	wegp->wamdac_634 = wevew;
	NVWwiteWAMDAC(cwtc->dev, nv_cwtc->index, NV_PWAMDAC_634, wegp->wamdac_634);
}

#define PWWSEW_VPWW1_MASK				\
	(NV_PWAMDAC_PWW_COEFF_SEWECT_SOUWCE_PWOG_VPWW	\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_VCWK_WATIO_DB2)
#define PWWSEW_VPWW2_MASK				\
	(NV_PWAMDAC_PWW_COEFF_SEWECT_PWW_SOUWCE_VPWW2		\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_VCWK2_WATIO_DB2)
#define PWWSEW_TV_MASK					\
	(NV_PWAMDAC_PWW_COEFF_SEWECT_TV_VSCWK1		\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_TV_PCWK1		\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_TV_VSCWK2	\
	 | NV_PWAMDAC_PWW_COEFF_SEWECT_TV_PCWK2)

/* NV4x 0x40.. pww notes:
 * gpu pww: 0x4000 + 0x4004
 * ?gpu? pww: 0x4008 + 0x400c
 * vpww1: 0x4010 + 0x4014
 * vpww2: 0x4018 + 0x401c
 * mpww: 0x4020 + 0x4024
 * mpww: 0x4038 + 0x403c
 *
 * the fiwst wegistew of each paiw has some unknown detaiws:
 * bits 0-7: wediwected vawues fwom ewsewhewe? (simiwaw to PWW_SETUP_CONTWOW?)
 * bits 20-23: (mpww) something to do with post dividew?
 * bits 28-31: wewated to singwe stage mode? (bit 8/12)
 */

static void nv_cwtc_cawc_state_ext(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode * mode, int dot_cwock)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_bios *bios = nvxx_bios(&dwm->cwient.device);
	stwuct nvkm_cwk *cwk = nvxx_cwk(&dwm->cwient.device);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct nv04_mode_state *state = &nv04_dispway(dev)->mode_weg;
	stwuct nv04_cwtc_weg *wegp = &state->cwtc_weg[nv_cwtc->index];
	stwuct nvkm_pww_vaws *pv = &wegp->pwwvaws;
	stwuct nvbios_pww pww_wim;

	if (nvbios_pww_pawse(bios, nv_cwtc->index ? PWW_VPWW1 : PWW_VPWW0,
			    &pww_wim))
		wetuwn;

	/* NM2 == 0 is used to detewmine singwe stage mode on two stage pwws */
	pv->NM2 = 0;

	/* fow newew nv4x the bwob uses onwy the fiwst stage of the vpww bewow a
	 * cewtain cwock.  fow a cewtain nv4b this is 150MHz.  since the max
	 * output fwequency of the fiwst stage fow this cawd is 300MHz, it is
	 * assumed the thweshowd is given by vco1 maxfweq/2
	 */
	/* fow eawwy nv4x, specificawwy nv40 and *some* nv43 (devids 0 and 6,
	 * not 8, othews unknown), the bwob awways uses both pwws.  no pwobwem
	 * has yet been obsewved in awwowing the use a singwe stage pww on aww
	 * nv43 howevew.  the behaviouw of singwe stage use is untested on nv40
	 */
	if (dwm->cwient.device.info.chipset > 0x40 && dot_cwock <= (pww_wim.vco1.max_fweq / 2))
		memset(&pww_wim.vco2, 0, sizeof(pww_wim.vco2));


	if (!cwk->pww_cawc(cwk, &pww_wim, dot_cwock, pv))
		wetuwn;

	state->pwwsew &= PWWSEW_VPWW1_MASK | PWWSEW_VPWW2_MASK | PWWSEW_TV_MASK;

	/* The bwob uses this awways, so wet's do the same */
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		state->pwwsew |= NV_PWAMDAC_PWW_COEFF_SEWECT_USE_VPWW2_TWUE;
	/* again nv40 and some nv43 act mowe wike nv3x as descwibed above */
	if (dwm->cwient.device.info.chipset < 0x41)
		state->pwwsew |= NV_PWAMDAC_PWW_COEFF_SEWECT_SOUWCE_PWOG_MPWW |
				 NV_PWAMDAC_PWW_COEFF_SEWECT_SOUWCE_PWOG_NVPWW;
	state->pwwsew |= nv_cwtc->index ? PWWSEW_VPWW2_MASK : PWWSEW_VPWW1_MASK;

	if (pv->NM2)
		NV_DEBUG(dwm, "vpww: n1 %d n2 %d m1 %d m2 %d wog2p %d\n",
			 pv->N1, pv->N2, pv->M1, pv->M2, pv->wog2P);
	ewse
		NV_DEBUG(dwm, "vpww: n %d m %d wog2p %d\n",
			 pv->N1, pv->M1, pv->wog2P);

	nv_cwtc->cuwsow.set_offset(nv_cwtc, nv_cwtc->cuwsow.offset);
}

static void
nv_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	unsigned chaw seq1 = 0, cwtc17 = 0;
	unsigned chaw cwtc1A;

	NV_DEBUG(dwm, "Setting dpms mode %d on CWTC %d\n", mode,
							nv_cwtc->index);

	if (nv_cwtc->wast_dpms == mode) /* Don't do unnecessawy mode changes. */
		wetuwn;

	nv_cwtc->wast_dpms = mode;

	if (nv_two_heads(dev))
		NVSetOwnew(dev, nv_cwtc->index);

	/* nv4wef indicates these two WPC1 bits inhibit h/v sync */
	cwtc1A = NVWeadVgaCwtc(dev, nv_cwtc->index,
					NV_CIO_CWE_WPC1_INDEX) & ~0xC0;
	switch (mode) {
	case DWM_MODE_DPMS_STANDBY:
		/* Scween: Off; HSync: Off, VSync: On -- Not Suppowted */
		seq1 = 0x20;
		cwtc17 = 0x80;
		cwtc1A |= 0x80;
		bweak;
	case DWM_MODE_DPMS_SUSPEND:
		/* Scween: Off; HSync: On, VSync: Off -- Not Suppowted */
		seq1 = 0x20;
		cwtc17 = 0x80;
		cwtc1A |= 0x40;
		bweak;
	case DWM_MODE_DPMS_OFF:
		/* Scween: Off; HSync: Off, VSync: Off */
		seq1 = 0x20;
		cwtc17 = 0x00;
		cwtc1A |= 0xC0;
		bweak;
	case DWM_MODE_DPMS_ON:
	defauwt:
		/* Scween: On; HSync: On, VSync: On */
		seq1 = 0x00;
		cwtc17 = 0x80;
		bweak;
	}

	NVVgaSeqWeset(dev, nv_cwtc->index, twue);
	/* Each head has it's own sequencew, so we can tuwn it off when we want */
	seq1 |= (NVWeadVgaSeq(dev, nv_cwtc->index, NV_VIO_SW_CWOCK_INDEX) & ~0x20);
	NVWwiteVgaSeq(dev, nv_cwtc->index, NV_VIO_SW_CWOCK_INDEX, seq1);
	cwtc17 |= (NVWeadVgaCwtc(dev, nv_cwtc->index, NV_CIO_CW_MODE_INDEX) & ~0x80);
	mdeway(10);
	NVWwiteVgaCwtc(dev, nv_cwtc->index, NV_CIO_CW_MODE_INDEX, cwtc17);
	NVVgaSeqWeset(dev, nv_cwtc->index, fawse);

	NVWwiteVgaCwtc(dev, nv_cwtc->index, NV_CIO_CWE_WPC1_INDEX, cwtc1A);
}

static void
nv_cwtc_mode_set_vga(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;

	/* Cawcuwate ouw timings */
	int howizDispway	= (mode->cwtc_hdispway >> 3)		- 1;
	int howizStawt		= (mode->cwtc_hsync_stawt >> 3) 	+ 1;
	int howizEnd		= (mode->cwtc_hsync_end >> 3)		+ 1;
	int howizTotaw		= (mode->cwtc_htotaw >> 3)		- 5;
	int howizBwankStawt	= (mode->cwtc_hdispway >> 3)		- 1;
	int howizBwankEnd	= (mode->cwtc_htotaw >> 3)		- 1;
	int vewtDispway		= mode->cwtc_vdispway			- 1;
	int vewtStawt		= mode->cwtc_vsync_stawt 		- 1;
	int vewtEnd		= mode->cwtc_vsync_end			- 1;
	int vewtTotaw		= mode->cwtc_vtotaw 			- 2;
	int vewtBwankStawt	= mode->cwtc_vdispway 			- 1;
	int vewtBwankEnd	= mode->cwtc_vtotaw			- 1;

	stwuct dwm_encodew *encodew;
	boow fp_output = fawse;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

		if (encodew->cwtc == cwtc &&
		    (nv_encodew->dcb->type == DCB_OUTPUT_WVDS ||
		     nv_encodew->dcb->type == DCB_OUTPUT_TMDS))
			fp_output = twue;
	}

	if (fp_output) {
		vewtStawt = vewtTotaw - 3;
		vewtEnd = vewtTotaw - 2;
		vewtBwankStawt = vewtStawt;
		howizStawt = howizTotaw - 5;
		howizEnd = howizTotaw - 2;
		howizBwankEnd = howizTotaw + 4;
#if 0
		if (dev->ovewwayAdaptow && dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_CEWSIUS)
			/* This wepowtedwy wowks awound some video ovewway bandwidth pwobwems */
			howizTotaw += 2;
#endif
	}

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vewtTotaw |= 1;

#if 0
	EwwowF("howizDispway: 0x%X \n", howizDispway);
	EwwowF("howizStawt: 0x%X \n", howizStawt);
	EwwowF("howizEnd: 0x%X \n", howizEnd);
	EwwowF("howizTotaw: 0x%X \n", howizTotaw);
	EwwowF("howizBwankStawt: 0x%X \n", howizBwankStawt);
	EwwowF("howizBwankEnd: 0x%X \n", howizBwankEnd);
	EwwowF("vewtDispway: 0x%X \n", vewtDispway);
	EwwowF("vewtStawt: 0x%X \n", vewtStawt);
	EwwowF("vewtEnd: 0x%X \n", vewtEnd);
	EwwowF("vewtTotaw: 0x%X \n", vewtTotaw);
	EwwowF("vewtBwankStawt: 0x%X \n", vewtBwankStawt);
	EwwowF("vewtBwankEnd: 0x%X \n", vewtBwankEnd);
#endif

	/*
	* compute cowwect Hsync & Vsync powawity
	*/
	if ((mode->fwags & (DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NHSYNC))
		&& (mode->fwags & (DWM_MODE_FWAG_PVSYNC | DWM_MODE_FWAG_NVSYNC))) {

		wegp->MiscOutWeg = 0x23;
		if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
			wegp->MiscOutWeg |= 0x40;
		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			wegp->MiscOutWeg |= 0x80;
	} ewse {
		int vdispway = mode->vdispway;
		if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
			vdispway *= 2;
		if (mode->vscan > 1)
			vdispway *= mode->vscan;
		if (vdispway < 400)
			wegp->MiscOutWeg = 0xA3;	/* +hsync -vsync */
		ewse if (vdispway < 480)
			wegp->MiscOutWeg = 0x63;	/* -hsync +vsync */
		ewse if (vdispway < 768)
			wegp->MiscOutWeg = 0xE3;	/* -hsync -vsync */
		ewse
			wegp->MiscOutWeg = 0x23;	/* +hsync +vsync */
	}

	/*
	 * Time Sequencew
	 */
	wegp->Sequencew[NV_VIO_SW_WESET_INDEX] = 0x00;
	/* 0x20 disabwes the sequencew */
	if (mode->fwags & DWM_MODE_FWAG_CWKDIV2)
		wegp->Sequencew[NV_VIO_SW_CWOCK_INDEX] = 0x29;
	ewse
		wegp->Sequencew[NV_VIO_SW_CWOCK_INDEX] = 0x21;
	wegp->Sequencew[NV_VIO_SW_PWANE_MASK_INDEX] = 0x0F;
	wegp->Sequencew[NV_VIO_SW_CHAW_MAP_INDEX] = 0x00;
	wegp->Sequencew[NV_VIO_SW_MEM_MODE_INDEX] = 0x0E;

	/*
	 * CWTC
	 */
	wegp->CWTC[NV_CIO_CW_HDT_INDEX] = howizTotaw;
	wegp->CWTC[NV_CIO_CW_HDE_INDEX] = howizDispway;
	wegp->CWTC[NV_CIO_CW_HBS_INDEX] = howizBwankStawt;
	wegp->CWTC[NV_CIO_CW_HBE_INDEX] = (1 << 7) |
					  XWATE(howizBwankEnd, 0, NV_CIO_CW_HBE_4_0);
	wegp->CWTC[NV_CIO_CW_HWS_INDEX] = howizStawt;
	wegp->CWTC[NV_CIO_CW_HWE_INDEX] = XWATE(howizBwankEnd, 5, NV_CIO_CW_HWE_HBE_5) |
					  XWATE(howizEnd, 0, NV_CIO_CW_HWE_4_0);
	wegp->CWTC[NV_CIO_CW_VDT_INDEX] = vewtTotaw;
	wegp->CWTC[NV_CIO_CW_OVW_INDEX] = XWATE(vewtStawt, 9, NV_CIO_CW_OVW_VWS_9) |
					  XWATE(vewtDispway, 9, NV_CIO_CW_OVW_VDE_9) |
					  XWATE(vewtTotaw, 9, NV_CIO_CW_OVW_VDT_9) |
					  (1 << 4) |
					  XWATE(vewtBwankStawt, 8, NV_CIO_CW_OVW_VBS_8) |
					  XWATE(vewtStawt, 8, NV_CIO_CW_OVW_VWS_8) |
					  XWATE(vewtDispway, 8, NV_CIO_CW_OVW_VDE_8) |
					  XWATE(vewtTotaw, 8, NV_CIO_CW_OVW_VDT_8);
	wegp->CWTC[NV_CIO_CW_WSAW_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_CEWW_HT_INDEX] = ((mode->fwags & DWM_MODE_FWAG_DBWSCAN) ? MASK(NV_CIO_CW_CEWW_HT_SCANDBW) : 0) |
					      1 << 6 |
					      XWATE(vewtBwankStawt, 9, NV_CIO_CW_CEWW_HT_VBS_9);
	wegp->CWTC[NV_CIO_CW_CUWS_ST_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_CUWS_END_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_SA_HI_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_SA_WO_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_TCOFF_HI_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_TCOFF_WO_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_VWS_INDEX] = vewtStawt;
	wegp->CWTC[NV_CIO_CW_VWE_INDEX] = 1 << 5 | XWATE(vewtEnd, 0, NV_CIO_CW_VWE_3_0);
	wegp->CWTC[NV_CIO_CW_VDE_INDEX] = vewtDispway;
	/* fwamebuffew can be wawgew than cwtc scanout awea. */
	wegp->CWTC[NV_CIO_CW_OFFSET_INDEX] = fb->pitches[0] / 8;
	wegp->CWTC[NV_CIO_CW_UWINE_INDEX] = 0x00;
	wegp->CWTC[NV_CIO_CW_VBS_INDEX] = vewtBwankStawt;
	wegp->CWTC[NV_CIO_CW_VBE_INDEX] = vewtBwankEnd;
	wegp->CWTC[NV_CIO_CW_MODE_INDEX] = 0x43;
	wegp->CWTC[NV_CIO_CW_WCOMP_INDEX] = 0xff;

	/*
	 * Some extended CWTC wegistews (they awe not saved with the west of the vga wegs).
	 */

	/* fwamebuffew can be wawgew than cwtc scanout awea. */
	wegp->CWTC[NV_CIO_CWE_WPC0_INDEX] =
		XWATE(fb->pitches[0] / 8, 8, NV_CIO_CWE_WPC0_OFFSET_10_8);
	wegp->CWTC[NV_CIO_CWE_42] =
		XWATE(fb->pitches[0] / 8, 11, NV_CIO_CWE_42_OFFSET_11);
	wegp->CWTC[NV_CIO_CWE_WPC1_INDEX] = mode->cwtc_hdispway < 1280 ?
					    MASK(NV_CIO_CWE_WPC1_WAWGE) : 0x00;
	wegp->CWTC[NV_CIO_CWE_WSW_INDEX] = XWATE(howizBwankEnd, 6, NV_CIO_CWE_WSW_HBE_6) |
					   XWATE(vewtBwankStawt, 10, NV_CIO_CWE_WSW_VBS_10) |
					   XWATE(vewtStawt, 10, NV_CIO_CWE_WSW_VWS_10) |
					   XWATE(vewtDispway, 10, NV_CIO_CWE_WSW_VDE_10) |
					   XWATE(vewtTotaw, 10, NV_CIO_CWE_WSW_VDT_10);
	wegp->CWTC[NV_CIO_CWE_HEB__INDEX] = XWATE(howizStawt, 8, NV_CIO_CWE_HEB_HWS_8) |
					    XWATE(howizBwankStawt, 8, NV_CIO_CWE_HEB_HBS_8) |
					    XWATE(howizDispway, 8, NV_CIO_CWE_HEB_HDE_8) |
					    XWATE(howizTotaw, 8, NV_CIO_CWE_HEB_HDT_8);
	wegp->CWTC[NV_CIO_CWE_EBW_INDEX] = XWATE(vewtBwankStawt, 11, NV_CIO_CWE_EBW_VBS_11) |
					   XWATE(vewtStawt, 11, NV_CIO_CWE_EBW_VWS_11) |
					   XWATE(vewtDispway, 11, NV_CIO_CWE_EBW_VDE_11) |
					   XWATE(vewtTotaw, 11, NV_CIO_CWE_EBW_VDT_11);

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		howizTotaw = (howizTotaw >> 1) & ~1;
		wegp->CWTC[NV_CIO_CWE_IWACE__INDEX] = howizTotaw;
		wegp->CWTC[NV_CIO_CWE_HEB__INDEX] |= XWATE(howizTotaw, 8, NV_CIO_CWE_HEB_IWC_8);
	} ewse
		wegp->CWTC[NV_CIO_CWE_IWACE__INDEX] = 0xff;  /* intewwace off */

	/*
	* Gwaphics Dispway Contwowwew
	*/
	wegp->Gwaphics[NV_VIO_GX_SW_INDEX] = 0x00;
	wegp->Gwaphics[NV_VIO_GX_SWEN_INDEX] = 0x00;
	wegp->Gwaphics[NV_VIO_GX_CCOMP_INDEX] = 0x00;
	wegp->Gwaphics[NV_VIO_GX_WOP_INDEX] = 0x00;
	wegp->Gwaphics[NV_VIO_GX_WEAD_MAP_INDEX] = 0x00;
	wegp->Gwaphics[NV_VIO_GX_MODE_INDEX] = 0x40; /* 256 cowow mode */
	wegp->Gwaphics[NV_VIO_GX_MISC_INDEX] = 0x05; /* map 64k mem + gwaphic mode */
	wegp->Gwaphics[NV_VIO_GX_DONT_CAWE_INDEX] = 0x0F;
	wegp->Gwaphics[NV_VIO_GX_BIT_MASK_INDEX] = 0xFF;

	wegp->Attwibute[0]  = 0x00; /* standawd cowowmap twanswation */
	wegp->Attwibute[1]  = 0x01;
	wegp->Attwibute[2]  = 0x02;
	wegp->Attwibute[3]  = 0x03;
	wegp->Attwibute[4]  = 0x04;
	wegp->Attwibute[5]  = 0x05;
	wegp->Attwibute[6]  = 0x06;
	wegp->Attwibute[7]  = 0x07;
	wegp->Attwibute[8]  = 0x08;
	wegp->Attwibute[9]  = 0x09;
	wegp->Attwibute[10] = 0x0A;
	wegp->Attwibute[11] = 0x0B;
	wegp->Attwibute[12] = 0x0C;
	wegp->Attwibute[13] = 0x0D;
	wegp->Attwibute[14] = 0x0E;
	wegp->Attwibute[15] = 0x0F;
	wegp->Attwibute[NV_CIO_AW_MODE_INDEX] = 0x01; /* Enabwe gwaphic mode */
	/* Non-vga */
	wegp->Attwibute[NV_CIO_AW_OSCAN_INDEX] = 0x00;
	wegp->Attwibute[NV_CIO_AW_PWANE_INDEX] = 0x0F; /* enabwe aww cowow pwanes */
	wegp->Attwibute[NV_CIO_AW_HPP_INDEX] = 0x00;
	wegp->Attwibute[NV_CIO_AW_CSEW_INDEX] = 0x00;
}

/**
 * Sets up wegistews fow the given mode/adjusted_mode paiw.
 *
 * The cwocks, CWTCs and outputs attached to this CWTC must be off.
 *
 * This shouwdn't enabwe any cwocks, CWTCs, ow outputs, but they shouwd
 * be easiwy tuwned on/off aftew this.
 */
static void
nv_cwtc_mode_set_wegs(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode * mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];
	stwuct nv04_cwtc_weg *savep = &nv04_dispway(dev)->saved_weg.cwtc_weg[nv_cwtc->index];
	const stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
	stwuct dwm_encodew *encodew;
	boow wvds_output = fawse, tmds_output = fawse, tv_output = fawse,
		off_chip_digitaw = fawse;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
		boow digitaw = fawse;

		if (encodew->cwtc != cwtc)
			continue;

		if (nv_encodew->dcb->type == DCB_OUTPUT_WVDS)
			digitaw = wvds_output = twue;
		if (nv_encodew->dcb->type == DCB_OUTPUT_TV)
			tv_output = twue;
		if (nv_encodew->dcb->type == DCB_OUTPUT_TMDS)
			digitaw = tmds_output = twue;
		if (nv_encodew->dcb->wocation != DCB_WOC_ON_CHIP && digitaw)
			off_chip_digitaw = twue;
	}

	/* Wegistews not diwectwy wewated to the (s)vga mode */

	/* What is the meaning of this wegistew? */
	/* A few popuwaw vawues awe 0x18, 0x1c, 0x38, 0x3c */
	wegp->CWTC[NV_CIO_CWE_ENH_INDEX] = savep->CWTC[NV_CIO_CWE_ENH_INDEX] & ~(1<<5);

	wegp->cwtc_eng_ctww = 0;
	/* Except fow wawe conditions I2C is enabwed on the pwimawy cwtc */
	if (nv_cwtc->index == 0)
		wegp->cwtc_eng_ctww |= NV_CWTC_FSEW_I2C;
#if 0
	/* Set ovewway to desiwed cwtc. */
	if (dev->ovewwayAdaptow) {
		NVPowtPwivPtw pPwiv = GET_OVEWWAY_PWIVATE(dev);
		if (pPwiv->ovewwayCWTC == nv_cwtc->index)
			wegp->cwtc_eng_ctww |= NV_CWTC_FSEW_OVEWWAY;
	}
#endif

	/* ADDWESS_SPACE_PNVM is the same as setting HCUW_ASI */
	wegp->cuwsow_cfg = NV_PCWTC_CUWSOW_CONFIG_CUW_WINES_64 |
			     NV_PCWTC_CUWSOW_CONFIG_CUW_PIXEWS_64 |
			     NV_PCWTC_CUWSOW_CONFIG_ADDWESS_SPACE_PNVM;
	if (dwm->cwient.device.info.chipset >= 0x11)
		wegp->cuwsow_cfg |= NV_PCWTC_CUWSOW_CONFIG_CUW_BPP_32;
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wegp->cuwsow_cfg |= NV_PCWTC_CUWSOW_CONFIG_DOUBWE_SCAN_ENABWE;

	/* Unbwock some timings */
	wegp->CWTC[NV_CIO_CWE_53] = 0;
	wegp->CWTC[NV_CIO_CWE_54] = 0;

	/* 0x00 is disabwed, 0x11 is wvds, 0x22 cwt and 0x88 tmds */
	if (wvds_output)
		wegp->CWTC[NV_CIO_CWE_SCWATCH3__INDEX] = 0x11;
	ewse if (tmds_output)
		wegp->CWTC[NV_CIO_CWE_SCWATCH3__INDEX] = 0x88;
	ewse
		wegp->CWTC[NV_CIO_CWE_SCWATCH3__INDEX] = 0x22;

	/* These vawues seem to vawy */
	/* This wegistew seems to be used by the bios to make cewtain decisions on some G70 cawds? */
	wegp->CWTC[NV_CIO_CWE_SCWATCH4__INDEX] = savep->CWTC[NV_CIO_CWE_SCWATCH4__INDEX];

	nv_cwtc_set_digitaw_vibwance(cwtc, nv_cwtc->satuwation);

	/* pwobabwy a scwatch weg, but kept fow cawgo-cuwt puwposes:
	 * bit0: cwtc0?, head A
	 * bit6: wvds, head A
	 * bit7: (onwy in X), head A
	 */
	if (nv_cwtc->index == 0)
		wegp->CWTC[NV_CIO_CWE_4B] = savep->CWTC[NV_CIO_CWE_4B] | 0x80;

	/* The bwob seems to take the cuwwent vawue fwom cwtc 0, add 4 to that
	 * and weuse the owd vawue fow cwtc 1 */
	wegp->CWTC[NV_CIO_CWE_TVOUT_WATENCY] = nv04_dispway(dev)->saved_weg.cwtc_weg[0].CWTC[NV_CIO_CWE_TVOUT_WATENCY];
	if (!nv_cwtc->index)
		wegp->CWTC[NV_CIO_CWE_TVOUT_WATENCY] += 4;

	/* the bwob sometimes sets |= 0x10 (which is the same as setting |=
	 * 1 << 30 on 0x60.830), fow no appawent weason */
	wegp->CWTC[NV_CIO_CWE_59] = off_chip_digitaw;

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_WANKINE)
		wegp->CWTC[0x9f] = off_chip_digitaw ? 0x11 : 0x1;

	wegp->cwtc_830 = mode->cwtc_vdispway - 3;
	wegp->cwtc_834 = mode->cwtc_vdispway - 1;

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		/* This is what the bwob does */
		wegp->cwtc_850 = NVWeadCWTC(dev, 0, NV_PCWTC_850);

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_WANKINE)
		wegp->gpio_ext = NVWeadCWTC(dev, 0, NV_PCWTC_GPIO_EXT);

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_CEWSIUS)
		wegp->cwtc_cfg = NV10_PCWTC_CONFIG_STAWT_ADDWESS_HSYNC;
	ewse
		wegp->cwtc_cfg = NV04_PCWTC_CONFIG_STAWT_ADDWESS_HSYNC;

	/* Some misc wegs */
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE) {
		wegp->CWTC[NV_CIO_CWE_85] = 0xFF;
		wegp->CWTC[NV_CIO_CWE_86] = 0x1;
	}

	wegp->CWTC[NV_CIO_CWE_PIXEW_INDEX] = (fb->fowmat->depth + 1) / 8;
	/* Enabwe swaved mode (cawwed MODE_TV in nv4wef.h) */
	if (wvds_output || tmds_output || tv_output)
		wegp->CWTC[NV_CIO_CWE_PIXEW_INDEX] |= (1 << 7);

	/* Genewic PWAMDAC wegs */

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_CEWSIUS)
		/* Onwy bit that bios and bwob set. */
		wegp->nv10_cuwsync = (1 << 25);

	wegp->wamdac_gen_ctww = NV_PWAMDAC_GENEWAW_CONTWOW_BPC_8BITS |
				NV_PWAMDAC_GENEWAW_CONTWOW_VGA_STATE_SEW |
				NV_PWAMDAC_GENEWAW_CONTWOW_PIXMIX_ON;
	if (fb->fowmat->depth == 16)
		wegp->wamdac_gen_ctww |= NV_PWAMDAC_GENEWAW_CONTWOW_AWT_MODE_SEW;
	if (dwm->cwient.device.info.chipset >= 0x11)
		wegp->wamdac_gen_ctww |= NV_PWAMDAC_GENEWAW_CONTWOW_PIPE_WONG;

	wegp->wamdac_630 = 0; /* tuwn off gween mode (tv test pattewn?) */
	wegp->tv_setup = 0;

	nv_cwtc_set_image_shawpening(cwtc, nv_cwtc->shawpness);

	/* Some vawues the bwob sets */
	wegp->wamdac_8c0 = 0x100;
	wegp->wamdac_a20 = 0x0;
	wegp->wamdac_a24 = 0xfffff;
	wegp->wamdac_a34 = 0x1;
}

static int
nv_cwtc_swap_fbs(stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct nv04_dispway *disp = nv04_dispway(cwtc->dev);
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
	stwuct nouveau_bo *nvbo = nouveau_gem_object(fb->obj[0]);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	int wet;

	wet = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VWAM, fawse);
	if (wet == 0) {
		if (disp->image[nv_cwtc->index])
			nouveau_bo_unpin(disp->image[nv_cwtc->index]);
		nouveau_bo_wef(nvbo, &disp->image[nv_cwtc->index]);
	}

	wetuwn wet;
}

/**
 * Sets up wegistews fow the given mode/adjusted_mode paiw.
 *
 * The cwocks, CWTCs and outputs attached to this CWTC must be off.
 *
 * This shouwdn't enabwe any cwocks, CWTCs, ow outputs, but they shouwd
 * be easiwy tuwned on/off aftew this.
 */
static int
nv_cwtc_mode_set(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode,
		 stwuct dwm_dispway_mode *adjusted_mode,
		 int x, int y, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	int wet;

	NV_DEBUG(dwm, "CTWC mode on CWTC %d:\n", nv_cwtc->index);
	dwm_mode_debug_pwintmodewine(adjusted_mode);

	wet = nv_cwtc_swap_fbs(cwtc, owd_fb);
	if (wet)
		wetuwn wet;

	/* unwock must come aftew tuwning off FP_TG_CONTWOW in output_pwepawe */
	nv_wock_vga_cwtc_shadow(dev, nv_cwtc->index, -1);

	nv_cwtc_mode_set_vga(cwtc, adjusted_mode);
	/* cawcuwated in nv04_dfp_pwepawe, nv40 needs it wwitten befowe cawcuwating PWWs */
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		NVWwiteWAMDAC(dev, 0, NV_PWAMDAC_SEW_CWK, nv04_dispway(dev)->mode_weg.sew_cwk);
	nv_cwtc_mode_set_wegs(cwtc, adjusted_mode);
	nv_cwtc_cawc_state_ext(cwtc, mode, adjusted_mode->cwock);
	wetuwn 0;
}

static void nv_cwtc_save(stwuct dwm_cwtc *cwtc)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nv04_mode_state *state = &nv04_dispway(dev)->mode_weg;
	stwuct nv04_cwtc_weg *cwtc_state = &state->cwtc_weg[nv_cwtc->index];
	stwuct nv04_mode_state *saved = &nv04_dispway(dev)->saved_weg;
	stwuct nv04_cwtc_weg *cwtc_saved = &saved->cwtc_weg[nv_cwtc->index];

	if (nv_two_heads(cwtc->dev))
		NVSetOwnew(cwtc->dev, nv_cwtc->index);

	nouveau_hw_save_state(cwtc->dev, nv_cwtc->index, saved);

	/* init some state to saved vawue */
	state->sew_cwk = saved->sew_cwk & ~(0x5 << 16);
	cwtc_state->CWTC[NV_CIO_CWE_WCD__INDEX] = cwtc_saved->CWTC[NV_CIO_CWE_WCD__INDEX];
	state->pwwsew = saved->pwwsew & ~(PWWSEW_VPWW1_MASK | PWWSEW_VPWW2_MASK | PWWSEW_TV_MASK);
	cwtc_state->gpio_ext = cwtc_saved->gpio_ext;
}

static void nv_cwtc_westowe(stwuct dwm_cwtc *cwtc)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int head = nv_cwtc->index;
	uint8_t saved_cw21 = nv04_dispway(dev)->saved_weg.cwtc_weg[head].CWTC[NV_CIO_CWE_21];

	if (nv_two_heads(cwtc->dev))
		NVSetOwnew(cwtc->dev, head);

	nouveau_hw_woad_state(cwtc->dev, head, &nv04_dispway(dev)->saved_weg);
	nv_wock_vga_cwtc_shadow(cwtc->dev, head, saved_cw21);

	nv_cwtc->wast_dpms = NV_DPMS_CWEAWED;
}

static void nv_cwtc_pwepawe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	const stwuct dwm_cwtc_hewpew_funcs *funcs = cwtc->hewpew_pwivate;

	if (nv_two_heads(dev))
		NVSetOwnew(dev, nv_cwtc->index);

	dwm_cwtc_vbwank_off(cwtc);
	funcs->dpms(cwtc, DWM_MODE_DPMS_OFF);

	NVBwankScween(dev, nv_cwtc->index, twue);

	/* Some mowe pwepawation. */
	NVWwiteCWTC(dev, nv_cwtc->index, NV_PCWTC_CONFIG, NV_PCWTC_CONFIG_STAWT_ADDWESS_NON_VGA);
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE) {
		uint32_t weg900 = NVWeadWAMDAC(dev, nv_cwtc->index, NV_PWAMDAC_900);
		NVWwiteWAMDAC(dev, nv_cwtc->index, NV_PWAMDAC_900, weg900 & ~0x10000);
	}
}

static void nv_cwtc_commit(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	const stwuct dwm_cwtc_hewpew_funcs *funcs = cwtc->hewpew_pwivate;
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

	nouveau_hw_woad_state(dev, nv_cwtc->index, &nv04_dispway(dev)->mode_weg);
	nv04_cwtc_mode_set_base(cwtc, cwtc->x, cwtc->y, NUWW);

#ifdef __BIG_ENDIAN
	/* tuwn on WFB swapping */
	{
		uint8_t tmp = NVWeadVgaCwtc(dev, nv_cwtc->index, NV_CIO_CWE_WCW);
		tmp |= MASK(NV_CIO_CWE_WCW_ENDIAN_BIG);
		NVWwiteVgaCwtc(dev, nv_cwtc->index, NV_CIO_CWE_WCW, tmp);
	}
#endif

	funcs->dpms(cwtc, DWM_MODE_DPMS_ON);
	dwm_cwtc_vbwank_on(cwtc);
}

static void nv_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct nv04_dispway *disp = nv04_dispway(cwtc->dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

	if (!nv_cwtc)
		wetuwn;

	dwm_cwtc_cweanup(cwtc);

	if (disp->image[nv_cwtc->index])
		nouveau_bo_unpin(disp->image[nv_cwtc->index]);
	nouveau_bo_wef(NUWW, &disp->image[nv_cwtc->index]);

	nouveau_bo_unmap(nv_cwtc->cuwsow.nvbo);
	nouveau_bo_unpin(nv_cwtc->cuwsow.nvbo);
	nouveau_bo_wef(NUWW, &nv_cwtc->cuwsow.nvbo);
	nvif_event_dtow(&nv_cwtc->vbwank);
	nvif_head_dtow(&nv_cwtc->head);
	kfwee(nv_cwtc);
}

static void
nv_cwtc_gamma_woad(stwuct dwm_cwtc *cwtc)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = nv_cwtc->base.dev;
	stwuct wgb { uint8_t w, g, b; } __attwibute__((packed)) *wgbs;
	u16 *w, *g, *b;
	int i;

	wgbs = (stwuct wgb *)nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index].DAC;
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;

	fow (i = 0; i < 256; i++) {
		wgbs[i].w = *w++ >> 8;
		wgbs[i].g = *g++ >> 8;
		wgbs[i].b = *b++ >> 8;
	}

	nouveau_hw_woad_state_pawette(dev, nv_cwtc->index, &nv04_dispway(dev)->mode_weg);
}

static void
nv_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct nv04_dispway *disp = nv04_dispway(cwtc->dev);
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	if (disp->image[nv_cwtc->index])
		nouveau_bo_unpin(disp->image[nv_cwtc->index]);
	nouveau_bo_wef(NUWW, &disp->image[nv_cwtc->index]);
}

static int
nv_cwtc_gamma_set(stwuct dwm_cwtc *cwtc, u16 *w, u16 *g, u16 *b,
		  uint32_t size,
		  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

	/* We need to know the depth befowe we upwoad, but it's possibwe to
	 * get cawwed befowe a fwamebuffew is bound.  If this is the case,
	 * mawk the wut vawues as diwty by setting depth==0, and it'ww be
	 * upwoaded on the fiwst mode_set_base()
	 */
	if (!nv_cwtc->base.pwimawy->fb) {
		nv_cwtc->wut.depth = 0;
		wetuwn 0;
	}

	nv_cwtc_gamma_woad(cwtc);

	wetuwn 0;
}

static int
nv04_cwtc_do_mode_set_base(stwuct dwm_cwtc *cwtc,
			   stwuct dwm_fwamebuffew *passed_fb,
			   int x, int y, boow atomic)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv04_cwtc_weg *wegp = &nv04_dispway(dev)->mode_weg.cwtc_weg[nv_cwtc->index];
	stwuct nouveau_bo *nvbo;
	stwuct dwm_fwamebuffew *dwm_fb;
	int awb_buwst, awb_wwm;

	NV_DEBUG(dwm, "index %d\n", nv_cwtc->index);

	/* no fb bound */
	if (!atomic && !cwtc->pwimawy->fb) {
		NV_DEBUG(dwm, "No FB bound\n");
		wetuwn 0;
	}

	/* If atomic, we want to switch to the fb we wewe passed, so
	 * now we update pointews to do that.
	 */
	if (atomic) {
		dwm_fb = passed_fb;
	} ewse {
		dwm_fb = cwtc->pwimawy->fb;
	}

	nvbo = nouveau_gem_object(dwm_fb->obj[0]);
	nv_cwtc->fb.offset = nvbo->offset;

	if (nv_cwtc->wut.depth != dwm_fb->fowmat->depth) {
		nv_cwtc->wut.depth = dwm_fb->fowmat->depth;
		nv_cwtc_gamma_woad(cwtc);
	}

	/* Update the fwamebuffew fowmat. */
	wegp->CWTC[NV_CIO_CWE_PIXEW_INDEX] &= ~3;
	wegp->CWTC[NV_CIO_CWE_PIXEW_INDEX] |= (dwm_fb->fowmat->depth + 1) / 8;
	wegp->wamdac_gen_ctww &= ~NV_PWAMDAC_GENEWAW_CONTWOW_AWT_MODE_SEW;
	if (dwm_fb->fowmat->depth == 16)
		wegp->wamdac_gen_ctww |= NV_PWAMDAC_GENEWAW_CONTWOW_AWT_MODE_SEW;
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_PIXEW_INDEX);
	NVWwiteWAMDAC(dev, nv_cwtc->index, NV_PWAMDAC_GENEWAW_CONTWOW,
		      wegp->wamdac_gen_ctww);

	wegp->CWTC[NV_CIO_CW_OFFSET_INDEX] = dwm_fb->pitches[0] >> 3;
	wegp->CWTC[NV_CIO_CWE_WPC0_INDEX] =
		XWATE(dwm_fb->pitches[0] >> 3, 8, NV_CIO_CWE_WPC0_OFFSET_10_8);
	wegp->CWTC[NV_CIO_CWE_42] =
		XWATE(dwm_fb->pitches[0] / 8, 11, NV_CIO_CWE_42_OFFSET_11);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_WPC0_INDEX);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CW_OFFSET_INDEX);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_42);

	/* Update the fwamebuffew wocation. */
	wegp->fb_stawt = nv_cwtc->fb.offset & ~3;
	wegp->fb_stawt += (y * dwm_fb->pitches[0]) + (x * dwm_fb->fowmat->cpp[0]);
	nv_set_cwtc_base(dev, nv_cwtc->index, wegp->fb_stawt);

	/* Update the awbitwation pawametews. */
	nouveau_cawc_awb(dev, cwtc->mode.cwock, dwm_fb->fowmat->cpp[0] * 8,
			 &awb_buwst, &awb_wwm);

	wegp->CWTC[NV_CIO_CWE_FF_INDEX] = awb_buwst;
	wegp->CWTC[NV_CIO_CWE_FFWWM__INDEX] = awb_wwm & 0xff;
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_FF_INDEX);
	cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_FFWWM__INDEX);

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_KEWVIN) {
		wegp->CWTC[NV_CIO_CWE_47] = awb_wwm >> 8;
		cwtc_ww_cio_state(cwtc, wegp, NV_CIO_CWE_47);
	}

	wetuwn 0;
}

static int
nv04_cwtc_mode_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
			stwuct dwm_fwamebuffew *owd_fb)
{
	int wet = nv_cwtc_swap_fbs(cwtc, owd_fb);
	if (wet)
		wetuwn wet;
	wetuwn nv04_cwtc_do_mode_set_base(cwtc, owd_fb, x, y, fawse);
}

static int
nv04_cwtc_mode_set_base_atomic(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_fwamebuffew *fb,
			       int x, int y, enum mode_set_atomic state)
{
	wetuwn nv04_cwtc_do_mode_set_base(cwtc, fb, x, y, twue);
}

static void nv04_cuwsow_upwoad(stwuct dwm_device *dev, stwuct nouveau_bo *swc,
			       stwuct nouveau_bo *dst)
{
	int width = nv_cuwsow_width(dev);
	uint32_t pixew;
	int i, j;

	fow (i = 0; i < width; i++) {
		fow (j = 0; j < width; j++) {
			pixew = nouveau_bo_wd32(swc, i*64 + j);

			nouveau_bo_ww16(dst, i*width + j, (pixew & 0x80000000) >> 16
				     | (pixew & 0xf80000) >> 9
				     | (pixew & 0xf800) >> 6
				     | (pixew & 0xf8) >> 3);
		}
	}
}

static void nv11_cuwsow_upwoad(stwuct dwm_device *dev, stwuct nouveau_bo *swc,
			       stwuct nouveau_bo *dst)
{
	uint32_t pixew;
	int awpha, i;

	/* nv11+ suppowts pwemuwtipwied (PM), ow non-pwemuwtipwied (NPM) awpha
	 * cuwsows (though NPM in combination with fp dithewing may not wowk on
	 * nv11, fwom "nv" dwivew histowy)
	 * NPM mode needs NV_PCWTC_CUWSOW_CONFIG_AWPHA_BWEND set and is what the
	 * bwob uses, howevew we get given PM cuwsows so we use PM mode
	 */
	fow (i = 0; i < 64 * 64; i++) {
		pixew = nouveau_bo_wd32(swc, i);

		/* hw gets unhappy if awpha <= wgb vawues.  fow a PM image "wess
		 * than" shouwdn't happen; fix "equaw to" case by adding one to
		 * awpha channew (swightwy inaccuwate, but so is attempting to
		 * get back to NPM images, due to wimits of integew pwecision)
		 */
		awpha = pixew >> 24;
		if (awpha > 0 && awpha < 255)
			pixew = (pixew & 0x00ffffff) | ((awpha + 1) << 24);

#ifdef __BIG_ENDIAN
		{
			stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

			if (dwm->cwient.device.info.chipset == 0x11) {
				pixew = ((pixew & 0x000000ff) << 24) |
					((pixew & 0x0000ff00) << 8) |
					((pixew & 0x00ff0000) >> 8) |
					((pixew & 0xff000000) >> 24);
			}
		}
#endif

		nouveau_bo_ww32(dst, i, pixew);
	}
}

static int
nv04_cwtc_cuwsow_set(stwuct dwm_cwtc *cwtc, stwuct dwm_fiwe *fiwe_pwiv,
		     uint32_t buffew_handwe, uint32_t width, uint32_t height)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(cwtc->dev);
	stwuct dwm_device *dev = dwm->dev;
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);
	stwuct nouveau_bo *cuwsow = NUWW;
	stwuct dwm_gem_object *gem;
	int wet = 0;

	if (!buffew_handwe) {
		nv_cwtc->cuwsow.hide(nv_cwtc, twue);
		wetuwn 0;
	}

	if (width != 64 || height != 64)
		wetuwn -EINVAW;

	gem = dwm_gem_object_wookup(fiwe_pwiv, buffew_handwe);
	if (!gem)
		wetuwn -ENOENT;
	cuwsow = nouveau_gem_object(gem);

	wet = nouveau_bo_map(cuwsow);
	if (wet)
		goto out;

	if (dwm->cwient.device.info.chipset >= 0x11)
		nv11_cuwsow_upwoad(dev, cuwsow, nv_cwtc->cuwsow.nvbo);
	ewse
		nv04_cuwsow_upwoad(dev, cuwsow, nv_cwtc->cuwsow.nvbo);

	nouveau_bo_unmap(cuwsow);
	nv_cwtc->cuwsow.offset = nv_cwtc->cuwsow.nvbo->offset;
	nv_cwtc->cuwsow.set_offset(nv_cwtc, nv_cwtc->cuwsow.offset);
	nv_cwtc->cuwsow.show(nv_cwtc, twue);
out:
	dwm_gem_object_put(gem);
	wetuwn wet;
}

static int
nv04_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc, int x, int y)
{
	stwuct nouveau_cwtc *nv_cwtc = nouveau_cwtc(cwtc);

	nv_cwtc->cuwsow.set_pos(nv_cwtc, x, y);
	wetuwn 0;
}

stwuct nv04_page_fwip_state {
	stwuct wist_head head;
	stwuct dwm_pending_vbwank_event *event;
	stwuct dwm_cwtc *cwtc;
	int bpp, pitch;
	u64 offset;
};

static int
nv04_finish_page_fwip(stwuct nouveau_channew *chan,
		      stwuct nv04_page_fwip_state *ps)
{
	stwuct nouveau_fence_chan *fctx = chan->fence;
	stwuct nouveau_dwm *dwm = chan->dwm;
	stwuct dwm_device *dev = dwm->dev;
	stwuct nv04_page_fwip_state *s;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);

	if (wist_empty(&fctx->fwip)) {
		NV_EWWOW(dwm, "unexpected pagefwip\n");
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
		wetuwn -EINVAW;
	}

	s = wist_fiwst_entwy(&fctx->fwip, stwuct nv04_page_fwip_state, head);
	if (s->event) {
		dwm_cwtc_awm_vbwank_event(s->cwtc, s->event);
	} ewse {
		/* Give up ownewship of vbwank fow page-fwipped cwtc */
		dwm_cwtc_vbwank_put(s->cwtc);
	}

	wist_dew(&s->head);
	if (ps)
		*ps = *s;
	kfwee(s);

	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	wetuwn 0;
}

int
nv04_fwip_compwete(stwuct nvif_event *event, void *awgv, u32 awgc)
{
	stwuct nv04_dispway *disp = containew_of(event, typeof(*disp), fwip);
	stwuct nouveau_dwm *dwm = disp->dwm;
	stwuct nouveau_channew *chan = dwm->channew;
	stwuct nv04_page_fwip_state state;

	if (!nv04_finish_page_fwip(chan, &state)) {
		nv_set_cwtc_base(dwm->dev, dwm_cwtc_index(state.cwtc),
				 state.offset + state.cwtc->y *
				 state.pitch + state.cwtc->x *
				 state.bpp / 8);
	}

	wetuwn NVIF_EVENT_KEEP;
}

static int
nv04_page_fwip_emit(stwuct nouveau_channew *chan,
		    stwuct nouveau_bo *owd_bo,
		    stwuct nouveau_bo *new_bo,
		    stwuct nv04_page_fwip_state *s,
		    stwuct nouveau_fence **pfence)
{
	stwuct nouveau_fence_chan *fctx = chan->fence;
	stwuct nouveau_dwm *dwm = chan->dwm;
	stwuct dwm_device *dev = dwm->dev;
	stwuct nvif_push *push = chan->chan.push;
	unsigned wong fwags;
	int wet;

	/* Queue it to the pending wist */
	spin_wock_iwqsave(&dev->event_wock, fwags);
	wist_add_taiw(&s->head, &fctx->fwip);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	/* Synchwonize with the owd fwamebuffew */
	wet = nouveau_fence_sync(owd_bo, chan, fawse, fawse);
	if (wet)
		goto faiw;

	/* Emit the pagefwip */
	wet = PUSH_WAIT(push, 2);
	if (wet)
		goto faiw;

	PUSH_NVSQ(push, NV_SW, NV_SW_PAGE_FWIP, 0x00000000);
	PUSH_KICK(push);

	wet = nouveau_fence_new(pfence, chan);
	if (wet)
		goto faiw;

	wetuwn 0;
faiw:
	spin_wock_iwqsave(&dev->event_wock, fwags);
	wist_dew(&s->head);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	wetuwn wet;
}

static int
nv04_cwtc_page_fwip(stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *fb,
		    stwuct dwm_pending_vbwank_event *event, u32 fwags,
		    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	const int swap_intewvaw = (fwags & DWM_MODE_PAGE_FWIP_ASYNC) ? 0 : 1;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_fwamebuffew *owd_fb = cwtc->pwimawy->fb;
	stwuct nouveau_bo *owd_bo = nouveau_gem_object(owd_fb->obj[0]);
	stwuct nouveau_bo *new_bo = nouveau_gem_object(fb->obj[0]);
	stwuct nv04_page_fwip_state *s;
	stwuct nouveau_channew *chan;
	stwuct nouveau_cwi *cwi;
	stwuct nouveau_fence *fence;
	stwuct nv04_dispway *dispnv04 = nv04_dispway(dev);
	stwuct nvif_push *push;
	int head = nouveau_cwtc(cwtc)->index;
	int wet;

	chan = dwm->channew;
	if (!chan)
		wetuwn -ENODEV;
	cwi = (void *)chan->usew.cwient;
	push = chan->chan.push;

	s = kzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	if (new_bo != owd_bo) {
		wet = nouveau_bo_pin(new_bo, NOUVEAU_GEM_DOMAIN_VWAM, twue);
		if (wet)
			goto faiw_fwee;
	}

	mutex_wock(&cwi->mutex);
	wet = ttm_bo_wesewve(&new_bo->bo, twue, fawse, NUWW);
	if (wet)
		goto faiw_unpin;

	/* synchwonise wendewing channew with the kewnew's channew */
	wet = nouveau_fence_sync(new_bo, chan, fawse, twue);
	if (wet) {
		ttm_bo_unwesewve(&new_bo->bo);
		goto faiw_unpin;
	}

	if (new_bo != owd_bo) {
		ttm_bo_unwesewve(&new_bo->bo);

		wet = ttm_bo_wesewve(&owd_bo->bo, twue, fawse, NUWW);
		if (wet)
			goto faiw_unpin;
	}

	/* Initiawize a page fwip stwuct */
	*s = (stwuct nv04_page_fwip_state)
		{ { }, event, cwtc, fb->fowmat->cpp[0] * 8, fb->pitches[0],
		  new_bo->offset };

	/* Keep vbwanks on duwing fwip, fow the tawget cwtc of this fwip */
	dwm_cwtc_vbwank_get(cwtc);

	/* Emit a page fwip */
	if (swap_intewvaw) {
		wet = PUSH_WAIT(push, 8);
		if (wet)
			goto faiw_unwesewve;

		PUSH_NVSQ(push, NV05F, 0x012c, 0);
		PUSH_NVSQ(push, NV05F, 0x0134, head);
		PUSH_NVSQ(push, NV05F, 0x0100, 0);
		PUSH_NVSQ(push, NV05F, 0x0130, 0);
	}

	nouveau_bo_wef(new_bo, &dispnv04->image[head]);

	wet = nv04_page_fwip_emit(chan, owd_bo, new_bo, s, &fence);
	if (wet)
		goto faiw_unwesewve;
	mutex_unwock(&cwi->mutex);

	/* Update the cwtc stwuct and cweanup */
	cwtc->pwimawy->fb = fb;

	nouveau_bo_fence(owd_bo, fence, fawse);
	ttm_bo_unwesewve(&owd_bo->bo);
	if (owd_bo != new_bo)
		nouveau_bo_unpin(owd_bo);
	nouveau_fence_unwef(&fence);
	wetuwn 0;

faiw_unwesewve:
	dwm_cwtc_vbwank_put(cwtc);
	ttm_bo_unwesewve(&owd_bo->bo);
faiw_unpin:
	mutex_unwock(&cwi->mutex);
	if (owd_bo != new_bo)
		nouveau_bo_unpin(new_bo);
faiw_fwee:
	kfwee(s);
	wetuwn wet;
}

static const stwuct dwm_cwtc_funcs nv04_cwtc_funcs = {
	.cuwsow_set = nv04_cwtc_cuwsow_set,
	.cuwsow_move = nv04_cwtc_cuwsow_move,
	.gamma_set = nv_cwtc_gamma_set,
	.set_config = dwm_cwtc_hewpew_set_config,
	.page_fwip = nv04_cwtc_page_fwip,
	.destwoy = nv_cwtc_destwoy,
	.enabwe_vbwank = nouveau_dispway_vbwank_enabwe,
	.disabwe_vbwank = nouveau_dispway_vbwank_disabwe,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_hewpew_funcs nv04_cwtc_hewpew_funcs = {
	.dpms = nv_cwtc_dpms,
	.pwepawe = nv_cwtc_pwepawe,
	.commit = nv_cwtc_commit,
	.mode_set = nv_cwtc_mode_set,
	.mode_set_base = nv04_cwtc_mode_set_base,
	.mode_set_base_atomic = nv04_cwtc_mode_set_base_atomic,
	.disabwe = nv_cwtc_disabwe,
	.get_scanout_position = nouveau_dispway_scanoutpos,
};

static const uint32_t modeset_fowmats[] = {
        DWM_FOWMAT_XWGB8888,
        DWM_FOWMAT_WGB565,
        DWM_FOWMAT_XWGB1555,
};

static const stwuct dwm_pwane_funcs nv04_pwimawy_pwane_funcs = {
	DWM_PWANE_NON_ATOMIC_FUNCS,
};

static int
nv04_cwtc_vbwank_handwew(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_cwtc *nv_cwtc = containew_of(event, stwuct nouveau_cwtc, vbwank);

	dwm_cwtc_handwe_vbwank(&nv_cwtc->base);
	wetuwn NVIF_EVENT_KEEP;
}

int
nv04_cwtc_cweate(stwuct dwm_device *dev, int cwtc_num)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct nouveau_cwtc *nv_cwtc;
	stwuct dwm_pwane *pwimawy;
	int wet;

	nv_cwtc = kzawwoc(sizeof(*nv_cwtc), GFP_KEWNEW);
	if (!nv_cwtc)
		wetuwn -ENOMEM;

	nv_cwtc->wut.depth = 0;

	nv_cwtc->index = cwtc_num;
	nv_cwtc->wast_dpms = NV_DPMS_CWEAWED;

	nv_cwtc->save = nv_cwtc_save;
	nv_cwtc->westowe = nv_cwtc_westowe;

	pwimawy = __dwm_univewsaw_pwane_awwoc(dev, sizeof(*pwimawy), 0, 0,
					      &nv04_pwimawy_pwane_funcs,
					      modeset_fowmats,
					      AWWAY_SIZE(modeset_fowmats), NUWW,
					      DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (IS_EWW(pwimawy)) {
		wet = PTW_EWW(pwimawy);
		kfwee(nv_cwtc);
		wetuwn wet;
	}

	dwm_cwtc_init_with_pwanes(dev, &nv_cwtc->base, pwimawy, NUWW,
                                  &nv04_cwtc_funcs, NUWW);
	dwm_cwtc_hewpew_add(&nv_cwtc->base, &nv04_cwtc_hewpew_funcs);
	dwm_mode_cwtc_set_gamma_size(&nv_cwtc->base, 256);

	wet = nouveau_bo_new(&nouveau_dwm(dev)->cwient, 64*64*4, 0x100,
			     NOUVEAU_GEM_DOMAIN_VWAM, 0, 0x0000, NUWW, NUWW,
			     &nv_cwtc->cuwsow.nvbo);
	if (!wet) {
		wet = nouveau_bo_pin(nv_cwtc->cuwsow.nvbo,
				     NOUVEAU_GEM_DOMAIN_VWAM, fawse);
		if (!wet) {
			wet = nouveau_bo_map(nv_cwtc->cuwsow.nvbo);
			if (wet)
				nouveau_bo_unpin(nv_cwtc->cuwsow.nvbo);
		}
		if (wet)
			nouveau_bo_wef(NUWW, &nv_cwtc->cuwsow.nvbo);
	}

	nv04_cuwsow_init(nv_cwtc);

	wet = nvif_head_ctow(&disp->disp, nv_cwtc->base.name, nv_cwtc->index, &nv_cwtc->head);
	if (wet)
		wetuwn wet;

	wetuwn nvif_head_vbwank_event_ctow(&nv_cwtc->head, "kmsVbw", nv04_cwtc_vbwank_handwew,
					   fawse, &nv_cwtc->vbwank);
}
