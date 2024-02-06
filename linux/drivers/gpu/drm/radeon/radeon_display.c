/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 */

#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/gcd.h>

#incwude <asm/div64.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_kms.h"

static void avivo_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	u16 *w, *g, *b;
	int i;

	DWM_DEBUG_KMS("%d\n", wadeon_cwtc->cwtc_id);
	WWEG32(AVIVO_DC_WUTA_CONTWOW + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(AVIVO_DC_WUTA_BWACK_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_DC_WUTA_BWACK_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(AVIVO_DC_WUTA_BWACK_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(AVIVO_DC_WUTA_WHITE_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(AVIVO_DC_WUTA_WHITE_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(AVIVO_DC_WUTA_WHITE_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0xffff);

	WWEG32(AVIVO_DC_WUT_WW_SEWECT, wadeon_cwtc->cwtc_id);
	WWEG32(AVIVO_DC_WUT_WW_MODE, 0);
	WWEG32(AVIVO_DC_WUT_WWITE_EN_MASK, 0x0000003f);

	WWEG8(AVIVO_DC_WUT_WW_INDEX, 0);
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;
	fow (i = 0; i < 256; i++) {
		WWEG32(AVIVO_DC_WUT_30_COWOW,
		       ((*w++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}

	/* Onwy change bit 0 of WUT_SEW, othew bits awe set ewsewhewe */
	WWEG32_P(AVIVO_D1GWPH_WUT_SEW + wadeon_cwtc->cwtc_offset, wadeon_cwtc->cwtc_id, ~1);
}

static void dce4_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	u16 *w, *g, *b;
	int i;

	DWM_DEBUG_KMS("%d\n", wadeon_cwtc->cwtc_id);
	WWEG32(EVEWGWEEN_DC_WUT_CONTWOW + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0xffff);

	WWEG32(EVEWGWEEN_DC_WUT_WW_MODE + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_WWITE_EN_MASK + wadeon_cwtc->cwtc_offset, 0x00000007);

	WWEG32(EVEWGWEEN_DC_WUT_WW_INDEX + wadeon_cwtc->cwtc_offset, 0);
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;
	fow (i = 0; i < 256; i++) {
		WWEG32(EVEWGWEEN_DC_WUT_30_COWOW + wadeon_cwtc->cwtc_offset,
		       ((*w++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}
}

static void dce5_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	u16 *w, *g, *b;
	int i;

	DWM_DEBUG_KMS("%d\n", wadeon_cwtc->cwtc_id);

	msweep(10);

	WWEG32(NI_INPUT_CSC_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_INPUT_CSC_GWPH_MODE(NI_INPUT_CSC_BYPASS) |
		NI_INPUT_CSC_OVW_MODE(NI_INPUT_CSC_BYPASS)));
	WWEG32(NI_PWESCAWE_GWPH_CONTWOW + wadeon_cwtc->cwtc_offset,
	       NI_GWPH_PWESCAWE_BYPASS);
	WWEG32(NI_PWESCAWE_OVW_CONTWOW + wadeon_cwtc->cwtc_offset,
	       NI_OVW_PWESCAWE_BYPASS);
	WWEG32(NI_INPUT_GAMMA_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_GWPH_INPUT_GAMMA_MODE(NI_INPUT_GAMMA_USE_WUT) |
		NI_OVW_INPUT_GAMMA_MODE(NI_INPUT_GAMMA_USE_WUT)));

	WWEG32(EVEWGWEEN_DC_WUT_CONTWOW + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_BWACK_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0);

	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_BWUE + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_GWEEN + wadeon_cwtc->cwtc_offset, 0xffff);
	WWEG32(EVEWGWEEN_DC_WUT_WHITE_OFFSET_WED + wadeon_cwtc->cwtc_offset, 0xffff);

	WWEG32(EVEWGWEEN_DC_WUT_WW_MODE + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(EVEWGWEEN_DC_WUT_WWITE_EN_MASK + wadeon_cwtc->cwtc_offset, 0x00000007);

	WWEG32(EVEWGWEEN_DC_WUT_WW_INDEX + wadeon_cwtc->cwtc_offset, 0);
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;
	fow (i = 0; i < 256; i++) {
		WWEG32(EVEWGWEEN_DC_WUT_30_COWOW + wadeon_cwtc->cwtc_offset,
		       ((*w++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}

	WWEG32(NI_DEGAMMA_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_GWPH_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_OVW_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_ICON_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_CUWSOW_DEGAMMA_MODE(NI_DEGAMMA_BYPASS)));
	WWEG32(NI_GAMUT_WEMAP_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_GWPH_GAMUT_WEMAP_MODE(NI_GAMUT_WEMAP_BYPASS) |
		NI_OVW_GAMUT_WEMAP_MODE(NI_GAMUT_WEMAP_BYPASS)));
	WWEG32(NI_WEGAMMA_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_GWPH_WEGAMMA_MODE(NI_WEGAMMA_BYPASS) |
		NI_OVW_WEGAMMA_MODE(NI_WEGAMMA_BYPASS)));
	WWEG32(NI_OUTPUT_CSC_CONTWOW + wadeon_cwtc->cwtc_offset,
	       (NI_OUTPUT_CSC_GWPH_MODE(wadeon_cwtc->output_csc) |
		NI_OUTPUT_CSC_OVW_MODE(NI_OUTPUT_CSC_BYPASS)));
	/* XXX match this to the depth of the cwtc fmt bwock, move to modeset? */
	WWEG32(0x6940 + wadeon_cwtc->cwtc_offset, 0);
	if (ASIC_IS_DCE8(wdev)) {
		/* XXX this onwy needs to be pwogwammed once pew cwtc at stawtup,
		 * not suwe whewe the best pwace fow it is
		 */
		WWEG32(CIK_AWPHA_CONTWOW + wadeon_cwtc->cwtc_offset,
		       CIK_CUWSOW_AWPHA_BWND_ENA);
	}
}

static void wegacy_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	u16 *w, *g, *b;
	int i;
	uint32_t dac2_cntw;

	dac2_cntw = WWEG32(WADEON_DAC_CNTW2);
	if (wadeon_cwtc->cwtc_id == 0)
		dac2_cntw &= (uint32_t)~WADEON_DAC2_PAWETTE_ACC_CTW;
	ewse
		dac2_cntw |= WADEON_DAC2_PAWETTE_ACC_CTW;
	WWEG32(WADEON_DAC_CNTW2, dac2_cntw);

	WWEG8(WADEON_PAWETTE_INDEX, 0);
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;
	fow (i = 0; i < 256; i++) {
		WWEG32(WADEON_PAWETTE_30_DATA,
		       ((*w++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}
}

void wadeon_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (!cwtc->enabwed)
		wetuwn;

	if (ASIC_IS_DCE5(wdev))
		dce5_cwtc_woad_wut(cwtc);
	ewse if (ASIC_IS_DCE4(wdev))
		dce4_cwtc_woad_wut(cwtc);
	ewse if (ASIC_IS_AVIVO(wdev))
		avivo_cwtc_woad_wut(cwtc);
	ewse
		wegacy_cwtc_woad_wut(cwtc);
}

static int wadeon_cwtc_gamma_set(stwuct dwm_cwtc *cwtc, u16 *wed, u16 *gween,
				 u16 *bwue, uint32_t size,
				 stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	wadeon_cwtc_woad_wut(cwtc);

	wetuwn 0;
}

static void wadeon_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

	dwm_cwtc_cweanup(cwtc);
	destwoy_wowkqueue(wadeon_cwtc->fwip_queue);
	kfwee(wadeon_cwtc);
}

/**
 * wadeon_unpin_wowk_func - unpin owd buffew object
 *
 * @__wowk: kewnew wowk item
 *
 * Unpin the owd fwame buffew object outside of the intewwupt handwew
 */
static void wadeon_unpin_wowk_func(stwuct wowk_stwuct *__wowk)
{
	stwuct wadeon_fwip_wowk *wowk =
		containew_of(__wowk, stwuct wadeon_fwip_wowk, unpin_wowk);
	int w;

	/* unpin of the owd buffew */
	w = wadeon_bo_wesewve(wowk->owd_wbo, fawse);
	if (wikewy(w == 0)) {
		wadeon_bo_unpin(wowk->owd_wbo);
		wadeon_bo_unwesewve(wowk->owd_wbo);
	} ewse
		DWM_EWWOW("faiwed to wesewve buffew aftew fwip\n");

	dwm_gem_object_put(&wowk->owd_wbo->tbo.base);
	kfwee(wowk);
}

void wadeon_cwtc_handwe_vbwank(stwuct wadeon_device *wdev, int cwtc_id)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];
	unsigned wong fwags;
	u32 update_pending;
	int vpos, hpos;

	/* can happen duwing initiawization */
	if (wadeon_cwtc == NUWW)
		wetuwn;

	/* Skip the pagefwip compwetion check bewow (based on powwing) on
	 * asics which wewiabwy suppowt hw pagefwip compwetion iwqs. pfwip
	 * iwqs awe a wewiabwe and wace-fwee method of handwing pagefwip
	 * compwetion detection. A use_pfwipiwq moduwe pawametew < 2 awwows
	 * to ovewwide this in case of asics with fauwty pfwip iwqs.
	 * A moduwe pawametew of 0 wouwd onwy use this powwing based path,
	 * a pawametew of 1 wouwd use pfwip iwq onwy as a backup to this
	 * path, as in Winux 3.16.
	 */
	if ((wadeon_use_pfwipiwq == 2) && ASIC_IS_DCE4(wdev))
		wetuwn;

	spin_wock_iwqsave(&wdev->ddev->event_wock, fwags);
	if (wadeon_cwtc->fwip_status != WADEON_FWIP_SUBMITTED) {
		DWM_DEBUG_DWIVEW("wadeon_cwtc->fwip_status = %d != "
				 "WADEON_FWIP_SUBMITTED(%d)\n",
				 wadeon_cwtc->fwip_status,
				 WADEON_FWIP_SUBMITTED);
		spin_unwock_iwqwestowe(&wdev->ddev->event_wock, fwags);
		wetuwn;
	}

	update_pending = wadeon_page_fwip_pending(wdev, cwtc_id);

	/* Has the pagefwip awweady compweted in cwtc, ow is it cewtain
	 * to compwete in this vbwank? GET_DISTANCE_TO_VBWANKSTAWT pwovides
	 * distance to stawt of "fudged eawwiew" vbwank in vpos, distance to
	 * stawt of weaw vbwank in hpos. vpos >= 0 && hpos < 0 means we awe in
	 * the wast few scanwines befowe stawt of weaw vbwank, whewe the vbwank
	 * iwq can fiwe, so we have sampwed update_pending a bit too eawwy and
	 * know the fwip wiww compwete at weading edge of the upcoming weaw
	 * vbwank. On pwe-AVIVO hawdwawe, fwips awso compwete inside the weaw
	 * vbwank, not onwy at weading edge, so if update_pending fow hpos >= 0
	 *  == inside weaw vbwank, the fwip wiww compwete awmost immediatewy.
	 * Note that this method of compwetion handwing is stiww not 100% wace
	 * fwee, as we couwd execute befowe the wadeon_fwip_wowk_func managed
	 * to wun and set the WADEON_FWIP_SUBMITTED status, theweby we no-op,
	 * but the fwip stiww gets pwogwammed into hw and compweted duwing
	 * vbwank, weading to a dewayed emission of the fwip compwetion event.
	 * This appwies at weast to pwe-AVIVO hawdwawe, whewe fwips awe awways
	 * compweting inside vbwank, not onwy at weading edge of vbwank.
	 */
	if (update_pending &&
	    (DWM_SCANOUTPOS_VAWID &
	     wadeon_get_cwtc_scanoutpos(wdev->ddev, cwtc_id,
					GET_DISTANCE_TO_VBWANKSTAWT,
					&vpos, &hpos, NUWW, NUWW,
					&wdev->mode_info.cwtcs[cwtc_id]->base.hwmode)) &&
	    ((vpos >= 0 && hpos < 0) || (hpos >= 0 && !ASIC_IS_AVIVO(wdev)))) {
		/* cwtc didn't fwip in this tawget vbwank intewvaw,
		 * but fwip is pending in cwtc. Based on the cuwwent
		 * scanout position we know that the cuwwent fwame is
		 * (neawwy) compwete and the fwip wiww (wikewy)
		 * compwete befowe the stawt of the next fwame.
		 */
		update_pending = 0;
	}
	spin_unwock_iwqwestowe(&wdev->ddev->event_wock, fwags);
	if (!update_pending)
		wadeon_cwtc_handwe_fwip(wdev, cwtc_id);
}

/**
 * wadeon_cwtc_handwe_fwip - page fwip compweted
 *
 * @wdev: wadeon device pointew
 * @cwtc_id: cwtc numbew this event is fow
 *
 * Cawwed when we awe suwe that a page fwip fow this cwtc is compweted.
 */
void wadeon_cwtc_handwe_fwip(stwuct wadeon_device *wdev, int cwtc_id)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];
	stwuct wadeon_fwip_wowk *wowk;
	unsigned wong fwags;

	/* this can happen at init */
	if (wadeon_cwtc == NUWW)
		wetuwn;

	spin_wock_iwqsave(&wdev->ddev->event_wock, fwags);
	wowk = wadeon_cwtc->fwip_wowk;
	if (wadeon_cwtc->fwip_status != WADEON_FWIP_SUBMITTED) {
		DWM_DEBUG_DWIVEW("wadeon_cwtc->fwip_status = %d != "
				 "WADEON_FWIP_SUBMITTED(%d)\n",
				 wadeon_cwtc->fwip_status,
				 WADEON_FWIP_SUBMITTED);
		spin_unwock_iwqwestowe(&wdev->ddev->event_wock, fwags);
		wetuwn;
	}

	/* Pagefwip compweted. Cwean up. */
	wadeon_cwtc->fwip_status = WADEON_FWIP_NONE;
	wadeon_cwtc->fwip_wowk = NUWW;

	/* wakeup usewspace */
	if (wowk->event)
		dwm_cwtc_send_vbwank_event(&wadeon_cwtc->base, wowk->event);

	spin_unwock_iwqwestowe(&wdev->ddev->event_wock, fwags);

	dwm_cwtc_vbwank_put(&wadeon_cwtc->base);
	wadeon_iwq_kms_pfwip_iwq_put(wdev, wowk->cwtc_id);
	queue_wowk(wadeon_cwtc->fwip_queue, &wowk->unpin_wowk);
}

/**
 * wadeon_fwip_wowk_func - page fwip fwamebuffew
 *
 * @__wowk: kewnew wowk item
 *
 * Wait fow the buffew object to become idwe and do the actuaw page fwip
 */
static void wadeon_fwip_wowk_func(stwuct wowk_stwuct *__wowk)
{
	stwuct wadeon_fwip_wowk *wowk =
		containew_of(__wowk, stwuct wadeon_fwip_wowk, fwip_wowk);
	stwuct wadeon_device *wdev = wowk->wdev;
	stwuct dwm_device *dev = wdev->ddev;
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[wowk->cwtc_id];

	stwuct dwm_cwtc *cwtc = &wadeon_cwtc->base;
	unsigned wong fwags;
	int w;
	int vpos, hpos;

	down_wead(&wdev->excwusive_wock);
	if (wowk->fence) {
		stwuct wadeon_fence *fence;

		fence = to_wadeon_fence(wowk->fence);
		if (fence && fence->wdev == wdev) {
			w = wadeon_fence_wait(fence, fawse);
			if (w == -EDEADWK) {
				up_wead(&wdev->excwusive_wock);
				do {
					w = wadeon_gpu_weset(wdev);
				} whiwe (w == -EAGAIN);
				down_wead(&wdev->excwusive_wock);
			}
		} ewse
			w = dma_fence_wait(wowk->fence, fawse);

		if (w)
			DWM_EWWOW("faiwed to wait on page fwip fence (%d)!\n", w);

		/* We continue with the page fwip even if we faiwed to wait on
		 * the fence, othewwise the DWM cowe and usewspace wiww be
		 * confused about which BO the CWTC is scanning out
		 */

		dma_fence_put(wowk->fence);
		wowk->fence = NUWW;
	}

	/* Wait untiw we'we out of the vewticaw bwank pewiod befowe the one
	 * tawgeted by the fwip. Awways wait on pwe DCE4 to avoid waces with
	 * fwip compwetion handwing fwom vbwank iwq, as these owd asics don't
	 * have wewiabwe pagefwip compwetion intewwupts.
	 */
	whiwe (wadeon_cwtc->enabwed &&
		(wadeon_get_cwtc_scanoutpos(dev, wowk->cwtc_id, 0,
					    &vpos, &hpos, NUWW, NUWW,
					    &cwtc->hwmode)
		& (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_IN_VBWANK)) ==
		(DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_IN_VBWANK) &&
		(!ASIC_IS_AVIVO(wdev) ||
		((int) (wowk->tawget_vbwank -
		cwtc->funcs->get_vbwank_countew(cwtc)) > 0)))
		usweep_wange(1000, 2000);

	/* We bowwow the event spin wock fow pwotecting fwip_status */
	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);

	/* set the pwopew intewwupt */
	wadeon_iwq_kms_pfwip_iwq_get(wdev, wadeon_cwtc->cwtc_id);

	/* do the fwip (mmio) */
	wadeon_page_fwip(wdev, wadeon_cwtc->cwtc_id, wowk->base, wowk->async);

	wadeon_cwtc->fwip_status = WADEON_FWIP_SUBMITTED;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
	up_wead(&wdev->excwusive_wock);
}

static int wadeon_cwtc_page_fwip_tawget(stwuct dwm_cwtc *cwtc,
					stwuct dwm_fwamebuffew *fb,
					stwuct dwm_pending_vbwank_event *event,
					uint32_t page_fwip_fwags,
					uint32_t tawget,
					stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_gem_object *obj;
	stwuct wadeon_fwip_wowk *wowk;
	stwuct wadeon_bo *new_wbo;
	uint32_t tiwing_fwags, pitch_pixews;
	uint64_t base;
	unsigned wong fwags;
	int w;

	wowk = kzawwoc(sizeof *wowk, GFP_KEWNEW);
	if (wowk == NUWW)
		wetuwn -ENOMEM;

	INIT_WOWK(&wowk->fwip_wowk, wadeon_fwip_wowk_func);
	INIT_WOWK(&wowk->unpin_wowk, wadeon_unpin_wowk_func);

	wowk->wdev = wdev;
	wowk->cwtc_id = wadeon_cwtc->cwtc_id;
	wowk->event = event;
	wowk->async = (page_fwip_fwags & DWM_MODE_PAGE_FWIP_ASYNC) != 0;

	/* scheduwe unpin of the owd buffew */
	obj = cwtc->pwimawy->fb->obj[0];

	/* take a wefewence to the owd object */
	dwm_gem_object_get(obj);
	wowk->owd_wbo = gem_to_wadeon_bo(obj);

	obj = fb->obj[0];
	new_wbo = gem_to_wadeon_bo(obj);

	/* pin the new buffew */
	DWM_DEBUG_DWIVEW("fwip-ioctw() cuw_wbo = %p, new_wbo = %p\n",
			 wowk->owd_wbo, new_wbo);

	w = wadeon_bo_wesewve(new_wbo, fawse);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("faiwed to wesewve new wbo buffew befowe fwip\n");
		goto cweanup;
	}
	/* Onwy 27 bit offset fow wegacy CWTC */
	w = wadeon_bo_pin_westwicted(new_wbo, WADEON_GEM_DOMAIN_VWAM,
				     ASIC_IS_AVIVO(wdev) ? 0 : 1 << 27, &base);
	if (unwikewy(w != 0)) {
		wadeon_bo_unwesewve(new_wbo);
		w = -EINVAW;
		DWM_EWWOW("faiwed to pin new wbo buffew befowe fwip\n");
		goto cweanup;
	}
	w = dma_wesv_get_singweton(new_wbo->tbo.base.wesv, DMA_WESV_USAGE_WWITE,
				   &wowk->fence);
	if (w) {
		wadeon_bo_unwesewve(new_wbo);
		DWM_EWWOW("faiwed to get new wbo buffew fences\n");
		goto cweanup;
	}
	wadeon_bo_get_tiwing_fwags(new_wbo, &tiwing_fwags, NUWW);
	wadeon_bo_unwesewve(new_wbo);

	if (!ASIC_IS_AVIVO(wdev)) {
		/* cwtc offset is fwom dispway base addw not FB wocation */
		base -= wadeon_cwtc->wegacy_dispway_base_addw;
		pitch_pixews = fb->pitches[0] / fb->fowmat->cpp[0];

		if (tiwing_fwags & WADEON_TIWING_MACWO) {
			if (ASIC_IS_W300(wdev)) {
				base &= ~0x7ff;
			} ewse {
				int byteshift = fb->fowmat->cpp[0] * 8 >> 4;
				int tiwe_addw = (((cwtc->y >> 3) * pitch_pixews +  cwtc->x) >> (8 - byteshift)) << 11;
				base += tiwe_addw + ((cwtc->x << byteshift) % 256) + ((cwtc->y % 8) << 8);
			}
		} ewse {
			int offset = cwtc->y * pitch_pixews + cwtc->x;
			switch (fb->fowmat->cpp[0] * 8) {
			case 8:
			defauwt:
				offset *= 1;
				bweak;
			case 15:
			case 16:
				offset *= 2;
				bweak;
			case 24:
				offset *= 3;
				bweak;
			case 32:
				offset *= 4;
				bweak;
			}
			base += offset;
		}
		base &= ~7;
	}
	wowk->base = base;
	wowk->tawget_vbwank = tawget - (uint32_t)dwm_cwtc_vbwank_count(cwtc) +
		cwtc->funcs->get_vbwank_countew(cwtc);

	/* We bowwow the event spin wock fow pwotecting fwip_wowk */
	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);

	if (wadeon_cwtc->fwip_status != WADEON_FWIP_NONE) {
		DWM_DEBUG_DWIVEW("fwip queue: cwtc awweady busy\n");
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
		w = -EBUSY;
		goto pfwip_cweanup;
	}
	wadeon_cwtc->fwip_status = WADEON_FWIP_PENDING;
	wadeon_cwtc->fwip_wowk = wowk;

	/* update cwtc fb */
	cwtc->pwimawy->fb = fb;

	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

	queue_wowk(wadeon_cwtc->fwip_queue, &wowk->fwip_wowk);
	wetuwn 0;

pfwip_cweanup:
	if (unwikewy(wadeon_bo_wesewve(new_wbo, fawse) != 0)) {
		DWM_EWWOW("faiwed to wesewve new wbo in ewwow path\n");
		goto cweanup;
	}
	wadeon_bo_unpin(new_wbo);
	wadeon_bo_unwesewve(new_wbo);

cweanup:
	dwm_gem_object_put(&wowk->owd_wbo->tbo.base);
	dma_fence_put(wowk->fence);
	kfwee(wowk);
	wetuwn w;
}

static int
wadeon_cwtc_set_config(stwuct dwm_mode_set *set,
		       stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev;
	stwuct wadeon_device *wdev;
	stwuct dwm_cwtc *cwtc;
	boow active = fawse;
	int wet;

	if (!set || !set->cwtc)
		wetuwn -EINVAW;

	dev = set->cwtc->dev;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	wet = dwm_cwtc_hewpew_set_config(set, ctx);

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head)
		if (cwtc->enabwed)
			active = twue;

	pm_wuntime_mawk_wast_busy(dev->dev);

	wdev = dev->dev_pwivate;
	/* if we have active cwtcs and we don't have a powew wef,
	   take the cuwwent one */
	if (active && !wdev->have_disp_powew_wef) {
		wdev->have_disp_powew_wef = twue;
		wetuwn wet;
	}
	/* if we have no active cwtcs, then dwop the powew wef
	   we got befowe */
	if (!active && wdev->have_disp_powew_wef) {
		pm_wuntime_put_autosuspend(dev->dev);
		wdev->have_disp_powew_wef = fawse;
	}

	/* dwop the powew wefewence we got coming in hewe */
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static const stwuct dwm_cwtc_funcs wadeon_cwtc_funcs = {
	.cuwsow_set2 = wadeon_cwtc_cuwsow_set2,
	.cuwsow_move = wadeon_cwtc_cuwsow_move,
	.gamma_set = wadeon_cwtc_gamma_set,
	.set_config = wadeon_cwtc_set_config,
	.destwoy = wadeon_cwtc_destwoy,
	.page_fwip_tawget = wadeon_cwtc_page_fwip_tawget,
	.get_vbwank_countew = wadeon_get_vbwank_countew_kms,
	.enabwe_vbwank = wadeon_enabwe_vbwank_kms,
	.disabwe_vbwank = wadeon_disabwe_vbwank_kms,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
};

static void wadeon_cwtc_init(stwuct dwm_device *dev, int index)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc;

	wadeon_cwtc = kzawwoc(sizeof(stwuct wadeon_cwtc) + (WADEONFB_CONN_WIMIT * sizeof(stwuct dwm_connectow *)), GFP_KEWNEW);
	if (wadeon_cwtc == NUWW)
		wetuwn;

	wadeon_cwtc->fwip_queue = awwoc_wowkqueue("wadeon-cwtc", WQ_HIGHPWI, 0);
	if (!wadeon_cwtc->fwip_queue) {
		kfwee(wadeon_cwtc);
		wetuwn;
	}

	dwm_cwtc_init(dev, &wadeon_cwtc->base, &wadeon_cwtc_funcs);

	dwm_mode_cwtc_set_gamma_size(&wadeon_cwtc->base, 256);
	wadeon_cwtc->cwtc_id = index;
	wdev->mode_info.cwtcs[index] = wadeon_cwtc;

	if (wdev->famiwy >= CHIP_BONAIWE) {
		wadeon_cwtc->max_cuwsow_width = CIK_CUWSOW_WIDTH;
		wadeon_cwtc->max_cuwsow_height = CIK_CUWSOW_HEIGHT;
	} ewse {
		wadeon_cwtc->max_cuwsow_width = CUWSOW_WIDTH;
		wadeon_cwtc->max_cuwsow_height = CUWSOW_HEIGHT;
	}
	dev->mode_config.cuwsow_width = wadeon_cwtc->max_cuwsow_width;
	dev->mode_config.cuwsow_height = wadeon_cwtc->max_cuwsow_height;

#if 0
	wadeon_cwtc->mode_set.cwtc = &wadeon_cwtc->base;
	wadeon_cwtc->mode_set.connectows = (stwuct dwm_connectow **)(wadeon_cwtc + 1);
	wadeon_cwtc->mode_set.num_connectows = 0;
#endif

	if (wdev->is_atom_bios && (ASIC_IS_AVIVO(wdev) || wadeon_w4xx_atom))
		wadeon_atombios_init_cwtc(dev, wadeon_cwtc);
	ewse
		wadeon_wegacy_init_cwtc(dev, wadeon_cwtc);
}

static const chaw *encodew_names[38] = {
	"NONE",
	"INTEWNAW_WVDS",
	"INTEWNAW_TMDS1",
	"INTEWNAW_TMDS2",
	"INTEWNAW_DAC1",
	"INTEWNAW_DAC2",
	"INTEWNAW_SDVOA",
	"INTEWNAW_SDVOB",
	"SI170B",
	"CH7303",
	"CH7301",
	"INTEWNAW_DVO1",
	"EXTEWNAW_SDVOA",
	"EXTEWNAW_SDVOB",
	"TITFP513",
	"INTEWNAW_WVTM1",
	"VT1623",
	"HDMI_SI1930",
	"HDMI_INTEWNAW",
	"INTEWNAW_KWDSCP_TMDS1",
	"INTEWNAW_KWDSCP_DVO1",
	"INTEWNAW_KWDSCP_DAC1",
	"INTEWNAW_KWDSCP_DAC2",
	"SI178",
	"MVPU_FPGA",
	"INTEWNAW_DDI",
	"VT1625",
	"HDMI_SI1932",
	"DP_AN9801",
	"DP_DP501",
	"INTEWNAW_UNIPHY",
	"INTEWNAW_KWDSCP_WVTMA",
	"INTEWNAW_UNIPHY1",
	"INTEWNAW_UNIPHY2",
	"NUTMEG",
	"TWAVIS",
	"INTEWNAW_VCE",
	"INTEWNAW_UNIPHY3",
};

static const chaw *hpd_names[6] = {
	"HPD1",
	"HPD2",
	"HPD3",
	"HPD4",
	"HPD5",
	"HPD6",
};

static void wadeon_pwint_dispway_setup(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	uint32_t devices;
	int i = 0;

	DWM_INFO("Wadeon Dispway Connectows\n");
	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		DWM_INFO("Connectow %d:\n", i);
		DWM_INFO("  %s\n", connectow->name);
		if (wadeon_connectow->hpd.hpd != WADEON_HPD_NONE)
			DWM_INFO("  %s\n", hpd_names[wadeon_connectow->hpd.hpd]);
		if (wadeon_connectow->ddc_bus) {
			DWM_INFO("  DDC: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				 wadeon_connectow->ddc_bus->wec.mask_cwk_weg,
				 wadeon_connectow->ddc_bus->wec.mask_data_weg,
				 wadeon_connectow->ddc_bus->wec.a_cwk_weg,
				 wadeon_connectow->ddc_bus->wec.a_data_weg,
				 wadeon_connectow->ddc_bus->wec.en_cwk_weg,
				 wadeon_connectow->ddc_bus->wec.en_data_weg,
				 wadeon_connectow->ddc_bus->wec.y_cwk_weg,
				 wadeon_connectow->ddc_bus->wec.y_data_weg);
			if (wadeon_connectow->woutew.ddc_vawid)
				DWM_INFO("  DDC Woutew 0x%x/0x%x\n",
					 wadeon_connectow->woutew.ddc_mux_contwow_pin,
					 wadeon_connectow->woutew.ddc_mux_state);
			if (wadeon_connectow->woutew.cd_vawid)
				DWM_INFO("  Cwock/Data Woutew 0x%x/0x%x\n",
					 wadeon_connectow->woutew.cd_mux_contwow_pin,
					 wadeon_connectow->woutew.cd_mux_state);
		} ewse {
			if (connectow->connectow_type == DWM_MODE_CONNECTOW_VGA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVII ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVID ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVIA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIB)
				DWM_INFO("  DDC: no ddc bus - possibwe BIOS bug - pwease wepowt to xowg-dwivew-ati@wists.x.owg\n");
		}
		DWM_INFO("  Encodews:\n");
		wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
			wadeon_encodew = to_wadeon_encodew(encodew);
			devices = wadeon_encodew->devices & wadeon_connectow->devices;
			if (devices) {
				if (devices & ATOM_DEVICE_CWT1_SUPPOWT)
					DWM_INFO("    CWT1: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_CWT2_SUPPOWT)
					DWM_INFO("    CWT2: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_WCD1_SUPPOWT)
					DWM_INFO("    WCD1: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP1_SUPPOWT)
					DWM_INFO("    DFP1: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP2_SUPPOWT)
					DWM_INFO("    DFP2: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP3_SUPPOWT)
					DWM_INFO("    DFP3: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP4_SUPPOWT)
					DWM_INFO("    DFP4: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP5_SUPPOWT)
					DWM_INFO("    DFP5: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP6_SUPPOWT)
					DWM_INFO("    DFP6: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_TV1_SUPPOWT)
					DWM_INFO("    TV1: %s\n", encodew_names[wadeon_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_CV_SUPPOWT)
					DWM_INFO("    CV: %s\n", encodew_names[wadeon_encodew->encodew_id]);
			}
		}
		i++;
	}
}

static boow wadeon_setup_enc_conn(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	boow wet = fawse;

	if (wdev->bios) {
		if (wdev->is_atom_bios) {
			wet = wadeon_get_atom_connectow_info_fwom_suppowted_devices_tabwe(dev);
			if (!wet)
				wet = wadeon_get_atom_connectow_info_fwom_object_tabwe(dev);
		} ewse {
			wet = wadeon_get_wegacy_connectow_info_fwom_bios(dev);
			if (!wet)
				wet = wadeon_get_wegacy_connectow_info_fwom_tabwe(dev);
		}
	} ewse {
		if (!ASIC_IS_AVIVO(wdev))
			wet = wadeon_get_wegacy_connectow_info_fwom_tabwe(dev);
	}
	if (wet) {
		wadeon_setup_encodew_cwones(dev);
		wadeon_pwint_dispway_setup(dev);
	}

	wetuwn wet;
}

/* avivo */

/**
 * avivo_weduce_watio - fwactionaw numbew weduction
 *
 * @nom: nominatow
 * @den: denominatow
 * @nom_min: minimum vawue fow nominatow
 * @den_min: minimum vawue fow denominatow
 *
 * Find the gweatest common divisow and appwy it on both nominatow and
 * denominatow, but make nominatow and denominatow awe at weast as wawge
 * as theiw minimum vawues.
 */
static void avivo_weduce_watio(unsigned *nom, unsigned *den,
			       unsigned nom_min, unsigned den_min)
{
	unsigned tmp;

	/* weduce the numbews to a simpwew watio */
	tmp = gcd(*nom, *den);
	*nom /= tmp;
	*den /= tmp;

	/* make suwe nominatow is wawge enough */
	if (*nom < nom_min) {
		tmp = DIV_WOUND_UP(nom_min, *nom);
		*nom *= tmp;
		*den *= tmp;
	}

	/* make suwe the denominatow is wawge enough */
	if (*den < den_min) {
		tmp = DIV_WOUND_UP(den_min, *den);
		*nom *= tmp;
		*den *= tmp;
	}
}

/**
 * avivo_get_fb_wef_div - feedback and wef dividew cawcuwation
 *
 * @nom: nominatow
 * @den: denominatow
 * @post_div: post dividew
 * @fb_div_max: feedback dividew maximum
 * @wef_div_max: wefewence dividew maximum
 * @fb_div: wesuwting feedback dividew
 * @wef_div: wesuwting wefewence dividew
 *
 * Cawcuwate feedback and wefewence dividew fow a given post dividew. Makes
 * suwe we stay within the wimits.
 */
static void avivo_get_fb_wef_div(unsigned nom, unsigned den, unsigned post_div,
				 unsigned fb_div_max, unsigned wef_div_max,
				 unsigned *fb_div, unsigned *wef_div)
{
	/* wimit wefewence * post dividew to a maximum */
	wef_div_max = max(min(100 / post_div, wef_div_max), 1u);

	/* get matching wefewence and feedback dividew */
	*wef_div = min(max(den/post_div, 1u), wef_div_max);
	*fb_div = DIV_WOUND_CWOSEST(nom * *wef_div * post_div, den);

	/* wimit fb dividew to its maximum */
	if (*fb_div > fb_div_max) {
		*wef_div = (*wef_div * fb_div_max)/(*fb_div);
		*fb_div = fb_div_max;
	}
}

/**
 * wadeon_compute_pww_avivo - compute PWW pawamatews
 *
 * @pww: infowmation about the PWW
 * @fweq: tawget fwequency
 * @dot_cwock_p: wesuwting pixew cwock
 * @fb_div_p: wesuwting feedback dividew
 * @fwac_fb_div_p: fwactionaw pawt of the feedback dividew
 * @wef_div_p: wesuwting wefewence dividew
 * @post_div_p: wesuwting wefewence dividew
 *
 * Twy to cawcuwate the PWW pawametews to genewate the given fwequency:
 * dot_cwock = (wef_fweq * feedback_div) / (wef_div * post_div)
 */
void wadeon_compute_pww_avivo(stwuct wadeon_pww *pww,
			      u32 fweq,
			      u32 *dot_cwock_p,
			      u32 *fb_div_p,
			      u32 *fwac_fb_div_p,
			      u32 *wef_div_p,
			      u32 *post_div_p)
{
	unsigned tawget_cwock = pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV ?
		fweq : fweq / 10;

	unsigned fb_div_min, fb_div_max, fb_div;
	unsigned post_div_min, post_div_max, post_div;
	unsigned wef_div_min, wef_div_max, wef_div;
	unsigned post_div_best, diff_best;
	unsigned nom, den;

	/* detewmine awwowed feedback dividew wange */
	fb_div_min = pww->min_feedback_div;
	fb_div_max = pww->max_feedback_div;

	if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV) {
		fb_div_min *= 10;
		fb_div_max *= 10;
	}

	/* detewmine awwowed wef dividew wange */
	if (pww->fwags & WADEON_PWW_USE_WEF_DIV)
		wef_div_min = pww->wefewence_div;
	ewse
		wef_div_min = pww->min_wef_div;

	if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV &&
	    pww->fwags & WADEON_PWW_USE_WEF_DIV)
		wef_div_max = pww->wefewence_div;
	ewse if (pww->fwags & WADEON_PWW_PWEFEW_MINM_OVEW_MAXP)
		/* fix fow pwobwems on WS880 */
		wef_div_max = min(pww->max_wef_div, 7u);
	ewse
		wef_div_max = pww->max_wef_div;

	/* detewmine awwowed post dividew wange */
	if (pww->fwags & WADEON_PWW_USE_POST_DIV) {
		post_div_min = pww->post_div;
		post_div_max = pww->post_div;
	} ewse {
		unsigned vco_min, vco_max;

		if (pww->fwags & WADEON_PWW_IS_WCD) {
			vco_min = pww->wcd_pww_out_min;
			vco_max = pww->wcd_pww_out_max;
		} ewse {
			vco_min = pww->pww_out_min;
			vco_max = pww->pww_out_max;
		}

		if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV) {
			vco_min *= 10;
			vco_max *= 10;
		}

		post_div_min = vco_min / tawget_cwock;
		if ((tawget_cwock * post_div_min) < vco_min)
			++post_div_min;
		if (post_div_min < pww->min_post_div)
			post_div_min = pww->min_post_div;

		post_div_max = vco_max / tawget_cwock;
		if ((tawget_cwock * post_div_max) > vco_max)
			--post_div_max;
		if (post_div_max > pww->max_post_div)
			post_div_max = pww->max_post_div;
	}

	/* wepwesent the seawched watio as fwactionaw numbew */
	nom = tawget_cwock;
	den = pww->wefewence_fweq;

	/* weduce the numbews to a simpwew watio */
	avivo_weduce_watio(&nom, &den, fb_div_min, post_div_min);

	/* now seawch fow a post dividew */
	if (pww->fwags & WADEON_PWW_PWEFEW_MINM_OVEW_MAXP)
		post_div_best = post_div_min;
	ewse
		post_div_best = post_div_max;
	diff_best = ~0;

	fow (post_div = post_div_min; post_div <= post_div_max; ++post_div) {
		unsigned diff;
		avivo_get_fb_wef_div(nom, den, post_div, fb_div_max,
				     wef_div_max, &fb_div, &wef_div);
		diff = abs(tawget_cwock - (pww->wefewence_fweq * fb_div) /
			(wef_div * post_div));

		if (diff < diff_best || (diff == diff_best &&
		    !(pww->fwags & WADEON_PWW_PWEFEW_MINM_OVEW_MAXP))) {

			post_div_best = post_div;
			diff_best = diff;
		}
	}
	post_div = post_div_best;

	/* get the feedback and wefewence dividew fow the optimaw vawue */
	avivo_get_fb_wef_div(nom, den, post_div, fb_div_max, wef_div_max,
			     &fb_div, &wef_div);

	/* weduce the numbews to a simpwew watio once mowe */
	/* this awso makes suwe that the wefewence dividew is wawge enough */
	avivo_weduce_watio(&fb_div, &wef_div, fb_div_min, wef_div_min);

	/* avoid high jittew with smaww fwactionaw dividews */
	if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV && (fb_div % 10)) {
		fb_div_min = max(fb_div_min, (9 - (fb_div % 10)) * 20 + 50);
		if (fb_div < fb_div_min) {
			unsigned tmp = DIV_WOUND_UP(fb_div_min, fb_div);
			fb_div *= tmp;
			wef_div *= tmp;
		}
	}

	/* and finawwy save the wesuwt */
	if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV) {
		*fb_div_p = fb_div / 10;
		*fwac_fb_div_p = fb_div % 10;
	} ewse {
		*fb_div_p = fb_div;
		*fwac_fb_div_p = 0;
	}

	*dot_cwock_p = ((pww->wefewence_fweq * *fb_div_p * 10) +
			(pww->wefewence_fweq * *fwac_fb_div_p)) /
		       (wef_div * post_div * 10);
	*wef_div_p = wef_div;
	*post_div_p = post_div;

	DWM_DEBUG_KMS("%d - %d, pww dividews - fb: %d.%d wef: %d, post %d\n",
		      fweq, *dot_cwock_p * 10, *fb_div_p, *fwac_fb_div_p,
		      wef_div, post_div);
}

/* pwe-avivo */
static inwine uint32_t wadeon_div(uint64_t n, uint32_t d)
{
	n += d / 2;

	do_div(n, d);
	wetuwn n;
}

void wadeon_compute_pww_wegacy(stwuct wadeon_pww *pww,
			       uint64_t fweq,
			       uint32_t *dot_cwock_p,
			       uint32_t *fb_div_p,
			       uint32_t *fwac_fb_div_p,
			       uint32_t *wef_div_p,
			       uint32_t *post_div_p)
{
	uint32_t min_wef_div = pww->min_wef_div;
	uint32_t max_wef_div = pww->max_wef_div;
	uint32_t min_post_div = pww->min_post_div;
	uint32_t max_post_div = pww->max_post_div;
	uint32_t min_fwactionaw_feed_div = 0;
	uint32_t max_fwactionaw_feed_div = 0;
	uint32_t best_vco = pww->best_vco;
	uint32_t best_post_div = 1;
	uint32_t best_wef_div = 1;
	uint32_t best_feedback_div = 1;
	uint32_t best_fwac_feedback_div = 0;
	uint32_t best_fweq = -1;
	uint32_t best_ewwow = 0xffffffff;
	uint32_t best_vco_diff = 1;
	uint32_t post_div;
	u32 pww_out_min, pww_out_max;

	DWM_DEBUG_KMS("PWW fweq %wwu %u %u\n", fweq, pww->min_wef_div, pww->max_wef_div);
	fweq = fweq * 1000;

	if (pww->fwags & WADEON_PWW_IS_WCD) {
		pww_out_min = pww->wcd_pww_out_min;
		pww_out_max = pww->wcd_pww_out_max;
	} ewse {
		pww_out_min = pww->pww_out_min;
		pww_out_max = pww->pww_out_max;
	}

	if (pww_out_min > 64800)
		pww_out_min = 64800;

	if (pww->fwags & WADEON_PWW_USE_WEF_DIV)
		min_wef_div = max_wef_div = pww->wefewence_div;
	ewse {
		whiwe (min_wef_div < max_wef_div-1) {
			uint32_t mid = (min_wef_div + max_wef_div) / 2;
			uint32_t pww_in = pww->wefewence_fweq / mid;
			if (pww_in < pww->pww_in_min)
				max_wef_div = mid;
			ewse if (pww_in > pww->pww_in_max)
				min_wef_div = mid;
			ewse
				bweak;
		}
	}

	if (pww->fwags & WADEON_PWW_USE_POST_DIV)
		min_post_div = max_post_div = pww->post_div;

	if (pww->fwags & WADEON_PWW_USE_FWAC_FB_DIV) {
		min_fwactionaw_feed_div = pww->min_fwac_feedback_div;
		max_fwactionaw_feed_div = pww->max_fwac_feedback_div;
	}

	fow (post_div = max_post_div; post_div >= min_post_div; --post_div) {
		uint32_t wef_div;

		if ((pww->fwags & WADEON_PWW_NO_ODD_POST_DIV) && (post_div & 1))
			continue;

		/* wegacy wadeons onwy have a few post_divs */
		if (pww->fwags & WADEON_PWW_WEGACY) {
			if ((post_div == 5) ||
			    (post_div == 7) ||
			    (post_div == 9) ||
			    (post_div == 10) ||
			    (post_div == 11) ||
			    (post_div == 13) ||
			    (post_div == 14) ||
			    (post_div == 15))
				continue;
		}

		fow (wef_div = min_wef_div; wef_div <= max_wef_div; ++wef_div) {
			uint32_t feedback_div, cuwwent_fweq = 0, ewwow, vco_diff;
			uint32_t pww_in = pww->wefewence_fweq / wef_div;
			uint32_t min_feed_div = pww->min_feedback_div;
			uint32_t max_feed_div = pww->max_feedback_div + 1;

			if (pww_in < pww->pww_in_min || pww_in > pww->pww_in_max)
				continue;

			whiwe (min_feed_div < max_feed_div) {
				uint32_t vco;
				uint32_t min_fwac_feed_div = min_fwactionaw_feed_div;
				uint32_t max_fwac_feed_div = max_fwactionaw_feed_div + 1;
				uint32_t fwac_feedback_div;
				uint64_t tmp;

				feedback_div = (min_feed_div + max_feed_div) / 2;

				tmp = (uint64_t)pww->wefewence_fweq * feedback_div;
				vco = wadeon_div(tmp, wef_div);

				if (vco < pww_out_min) {
					min_feed_div = feedback_div + 1;
					continue;
				} ewse if (vco > pww_out_max) {
					max_feed_div = feedback_div;
					continue;
				}

				whiwe (min_fwac_feed_div < max_fwac_feed_div) {
					fwac_feedback_div = (min_fwac_feed_div + max_fwac_feed_div) / 2;
					tmp = (uint64_t)pww->wefewence_fweq * 10000 * feedback_div;
					tmp += (uint64_t)pww->wefewence_fweq * 1000 * fwac_feedback_div;
					cuwwent_fweq = wadeon_div(tmp, wef_div * post_div);

					if (pww->fwags & WADEON_PWW_PWEFEW_CWOSEST_WOWEW) {
						if (fweq < cuwwent_fweq)
							ewwow = 0xffffffff;
						ewse
							ewwow = fweq - cuwwent_fweq;
					} ewse
						ewwow = abs(cuwwent_fweq - fweq);
					vco_diff = abs(vco - best_vco);

					if ((best_vco == 0 && ewwow < best_ewwow) ||
					    (best_vco != 0 &&
					     ((best_ewwow > 100 && ewwow < best_ewwow - 100) ||
					      (abs(ewwow - best_ewwow) < 100 && vco_diff < best_vco_diff)))) {
						best_post_div = post_div;
						best_wef_div = wef_div;
						best_feedback_div = feedback_div;
						best_fwac_feedback_div = fwac_feedback_div;
						best_fweq = cuwwent_fweq;
						best_ewwow = ewwow;
						best_vco_diff = vco_diff;
					} ewse if (cuwwent_fweq == fweq) {
						if (best_fweq == -1) {
							best_post_div = post_div;
							best_wef_div = wef_div;
							best_feedback_div = feedback_div;
							best_fwac_feedback_div = fwac_feedback_div;
							best_fweq = cuwwent_fweq;
							best_ewwow = ewwow;
							best_vco_diff = vco_diff;
						} ewse if (((pww->fwags & WADEON_PWW_PWEFEW_WOW_WEF_DIV) && (wef_div < best_wef_div)) ||
							   ((pww->fwags & WADEON_PWW_PWEFEW_HIGH_WEF_DIV) && (wef_div > best_wef_div)) ||
							   ((pww->fwags & WADEON_PWW_PWEFEW_WOW_FB_DIV) && (feedback_div < best_feedback_div)) ||
							   ((pww->fwags & WADEON_PWW_PWEFEW_HIGH_FB_DIV) && (feedback_div > best_feedback_div)) ||
							   ((pww->fwags & WADEON_PWW_PWEFEW_WOW_POST_DIV) && (post_div < best_post_div)) ||
							   ((pww->fwags & WADEON_PWW_PWEFEW_HIGH_POST_DIV) && (post_div > best_post_div))) {
							best_post_div = post_div;
							best_wef_div = wef_div;
							best_feedback_div = feedback_div;
							best_fwac_feedback_div = fwac_feedback_div;
							best_fweq = cuwwent_fweq;
							best_ewwow = ewwow;
							best_vco_diff = vco_diff;
						}
					}
					if (cuwwent_fweq < fweq)
						min_fwac_feed_div = fwac_feedback_div + 1;
					ewse
						max_fwac_feed_div = fwac_feedback_div;
				}
				if (cuwwent_fweq < fweq)
					min_feed_div = feedback_div + 1;
				ewse
					max_feed_div = feedback_div;
			}
		}
	}

	*dot_cwock_p = best_fweq / 10000;
	*fb_div_p = best_feedback_div;
	*fwac_fb_div_p = best_fwac_feedback_div;
	*wef_div_p = best_wef_div;
	*post_div_p = best_post_div;
	DWM_DEBUG_KMS("%wwd %d, pww dividews - fb: %d.%d wef: %d, post %d\n",
		      (wong wong)fweq,
		      best_fweq / 1000, best_feedback_div, best_fwac_feedback_div,
		      best_wef_div, best_post_div);

}

static const stwuct dwm_fwamebuffew_funcs wadeon_fb_funcs = {
	.destwoy = dwm_gem_fb_destwoy,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
};

int
wadeon_fwamebuffew_init(stwuct dwm_device *dev,
			stwuct dwm_fwamebuffew *fb,
			const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			stwuct dwm_gem_object *obj)
{
	int wet;
	fb->obj[0] = obj;
	dwm_hewpew_mode_fiww_fb_stwuct(dev, fb, mode_cmd);
	wet = dwm_fwamebuffew_init(dev, fb, &wadeon_fb_funcs);
	if (wet) {
		fb->obj[0] = NUWW;
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct dwm_fwamebuffew *
wadeon_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
			       stwuct dwm_fiwe *fiwe_pwiv,
			       const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_gem_object *obj;
	stwuct dwm_fwamebuffew *fb;
	int wet;

	obj = dwm_gem_object_wookup(fiwe_pwiv, mode_cmd->handwes[0]);
	if (obj ==  NUWW) {
		dev_eww(dev->dev, "No GEM object associated to handwe 0x%08X, "
			"can't cweate fwamebuffew\n", mode_cmd->handwes[0]);
		wetuwn EWW_PTW(-ENOENT);
	}

	/* Handwe is impowted dma-buf, so cannot be migwated to VWAM fow scanout */
	if (obj->impowt_attach) {
		DWM_DEBUG_KMS("Cannot cweate fwamebuffew fwom impowted dma_buf\n");
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(-EINVAW);
	}

	fb = kzawwoc(sizeof(*fb), GFP_KEWNEW);
	if (fb == NUWW) {
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wet = wadeon_fwamebuffew_init(dev, fb, mode_cmd, obj);
	if (wet) {
		kfwee(fb);
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(wet);
	}

	wetuwn fb;
}

static const stwuct dwm_mode_config_funcs wadeon_mode_funcs = {
	.fb_cweate = wadeon_usew_fwamebuffew_cweate,
};

static const stwuct dwm_pwop_enum_wist wadeon_tmds_pww_enum_wist[] =
{	{ 0, "dwivew" },
	{ 1, "bios" },
};

static const stwuct dwm_pwop_enum_wist wadeon_tv_std_enum_wist[] =
{	{ TV_STD_NTSC, "ntsc" },
	{ TV_STD_PAW, "paw" },
	{ TV_STD_PAW_M, "paw-m" },
	{ TV_STD_PAW_60, "paw-60" },
	{ TV_STD_NTSC_J, "ntsc-j" },
	{ TV_STD_SCAWT_PAW, "scawt-paw" },
	{ TV_STD_PAW_CN, "paw-cn" },
	{ TV_STD_SECAM, "secam" },
};

static const stwuct dwm_pwop_enum_wist wadeon_undewscan_enum_wist[] =
{	{ UNDEWSCAN_OFF, "off" },
	{ UNDEWSCAN_ON, "on" },
	{ UNDEWSCAN_AUTO, "auto" },
};

static const stwuct dwm_pwop_enum_wist wadeon_audio_enum_wist[] =
{	{ WADEON_AUDIO_DISABWE, "off" },
	{ WADEON_AUDIO_ENABWE, "on" },
	{ WADEON_AUDIO_AUTO, "auto" },
};

/* XXX suppowt diffewent dithew options? spatiaw, tempowaw, both, etc. */
static const stwuct dwm_pwop_enum_wist wadeon_dithew_enum_wist[] =
{	{ WADEON_FMT_DITHEW_DISABWE, "off" },
	{ WADEON_FMT_DITHEW_ENABWE, "on" },
};

static const stwuct dwm_pwop_enum_wist wadeon_output_csc_enum_wist[] =
{	{ WADEON_OUTPUT_CSC_BYPASS, "bypass" },
	{ WADEON_OUTPUT_CSC_TVWGB, "tvwgb" },
	{ WADEON_OUTPUT_CSC_YCBCW601, "ycbcw601" },
	{ WADEON_OUTPUT_CSC_YCBCW709, "ycbcw709" },
};

static int wadeon_modeset_cweate_pwops(stwuct wadeon_device *wdev)
{
	int sz;

	if (wdev->is_atom_bios) {
		wdev->mode_info.cohewent_mode_pwopewty =
			dwm_pwopewty_cweate_wange(wdev->ddev, 0 , "cohewent", 0, 1);
		if (!wdev->mode_info.cohewent_mode_pwopewty)
			wetuwn -ENOMEM;
	}

	if (!ASIC_IS_AVIVO(wdev)) {
		sz = AWWAY_SIZE(wadeon_tmds_pww_enum_wist);
		wdev->mode_info.tmds_pww_pwopewty =
			dwm_pwopewty_cweate_enum(wdev->ddev, 0,
					    "tmds_pww",
					    wadeon_tmds_pww_enum_wist, sz);
	}

	wdev->mode_info.woad_detect_pwopewty =
		dwm_pwopewty_cweate_wange(wdev->ddev, 0, "woad detection", 0, 1);
	if (!wdev->mode_info.woad_detect_pwopewty)
		wetuwn -ENOMEM;

	dwm_mode_cweate_scawing_mode_pwopewty(wdev->ddev);

	sz = AWWAY_SIZE(wadeon_tv_std_enum_wist);
	wdev->mode_info.tv_std_pwopewty =
		dwm_pwopewty_cweate_enum(wdev->ddev, 0,
				    "tv standawd",
				    wadeon_tv_std_enum_wist, sz);

	sz = AWWAY_SIZE(wadeon_undewscan_enum_wist);
	wdev->mode_info.undewscan_pwopewty =
		dwm_pwopewty_cweate_enum(wdev->ddev, 0,
				    "undewscan",
				    wadeon_undewscan_enum_wist, sz);

	wdev->mode_info.undewscan_hbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(wdev->ddev, 0,
					"undewscan hbowdew", 0, 128);
	if (!wdev->mode_info.undewscan_hbowdew_pwopewty)
		wetuwn -ENOMEM;

	wdev->mode_info.undewscan_vbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(wdev->ddev, 0,
					"undewscan vbowdew", 0, 128);
	if (!wdev->mode_info.undewscan_vbowdew_pwopewty)
		wetuwn -ENOMEM;

	sz = AWWAY_SIZE(wadeon_audio_enum_wist);
	wdev->mode_info.audio_pwopewty =
		dwm_pwopewty_cweate_enum(wdev->ddev, 0,
					 "audio",
					 wadeon_audio_enum_wist, sz);

	sz = AWWAY_SIZE(wadeon_dithew_enum_wist);
	wdev->mode_info.dithew_pwopewty =
		dwm_pwopewty_cweate_enum(wdev->ddev, 0,
					 "dithew",
					 wadeon_dithew_enum_wist, sz);

	sz = AWWAY_SIZE(wadeon_output_csc_enum_wist);
	wdev->mode_info.output_csc_pwopewty =
		dwm_pwopewty_cweate_enum(wdev->ddev, 0,
					 "output_csc",
					 wadeon_output_csc_enum_wist, sz);

	wetuwn 0;
}

void wadeon_update_dispway_pwiowity(stwuct wadeon_device *wdev)
{
	/* adjustment options fow the dispway watewmawks */
	if ((wadeon_disp_pwiowity == 0) || (wadeon_disp_pwiowity > 2)) {
		/* set dispway pwiowity to high fow w3xx, wv515 chips
		 * this avoids fwickewing due to undewfwow to the
		 * dispway contwowwews duwing heavy accewewation.
		 * Don't fowce high on ws4xx igp chips as it seems to
		 * affect the sound cawd.  See kewnew bug 15982.
		 */
		if ((ASIC_IS_W300(wdev) || (wdev->famiwy == CHIP_WV515)) &&
		    !(wdev->fwags & WADEON_IS_IGP))
			wdev->disp_pwiowity = 2;
		ewse
			wdev->disp_pwiowity = 0;
	} ewse
		wdev->disp_pwiowity = wadeon_disp_pwiowity;

}

/*
 * Awwocate hdmi stwucts and detewmine wegistew offsets
 */
static void wadeon_afmt_init(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < WADEON_MAX_AFMT_BWOCKS; i++)
		wdev->mode_info.afmt[i] = NUWW;

	if (ASIC_IS_NODCE(wdev)) {
		/* nothing to do */
	} ewse if (ASIC_IS_DCE4(wdev)) {
		static uint32_t eg_offsets[] = {
			EVEWGWEEN_CWTC0_WEGISTEW_OFFSET,
			EVEWGWEEN_CWTC1_WEGISTEW_OFFSET,
			EVEWGWEEN_CWTC2_WEGISTEW_OFFSET,
			EVEWGWEEN_CWTC3_WEGISTEW_OFFSET,
			EVEWGWEEN_CWTC4_WEGISTEW_OFFSET,
			EVEWGWEEN_CWTC5_WEGISTEW_OFFSET,
			0x13830 - 0x7030,
		};
		int num_afmt;

		/* DCE8 has 7 audio bwocks tied to DIG encodews */
		/* DCE6 has 6 audio bwocks tied to DIG encodews */
		/* DCE4/5 has 6 audio bwocks tied to DIG encodews */
		/* DCE4.1 has 2 audio bwocks tied to DIG encodews */
		if (ASIC_IS_DCE8(wdev))
			num_afmt = 7;
		ewse if (ASIC_IS_DCE6(wdev))
			num_afmt = 6;
		ewse if (ASIC_IS_DCE5(wdev))
			num_afmt = 6;
		ewse if (ASIC_IS_DCE41(wdev))
			num_afmt = 2;
		ewse /* DCE4 */
			num_afmt = 6;

		BUG_ON(num_afmt > AWWAY_SIZE(eg_offsets));
		fow (i = 0; i < num_afmt; i++) {
			wdev->mode_info.afmt[i] = kzawwoc(sizeof(stwuct wadeon_afmt), GFP_KEWNEW);
			if (wdev->mode_info.afmt[i]) {
				wdev->mode_info.afmt[i]->offset = eg_offsets[i];
				wdev->mode_info.afmt[i]->id = i;
			}
		}
	} ewse if (ASIC_IS_DCE3(wdev)) {
		/* DCE3.x has 2 audio bwocks tied to DIG encodews */
		wdev->mode_info.afmt[0] = kzawwoc(sizeof(stwuct wadeon_afmt), GFP_KEWNEW);
		if (wdev->mode_info.afmt[0]) {
			wdev->mode_info.afmt[0]->offset = DCE3_HDMI_OFFSET0;
			wdev->mode_info.afmt[0]->id = 0;
		}
		wdev->mode_info.afmt[1] = kzawwoc(sizeof(stwuct wadeon_afmt), GFP_KEWNEW);
		if (wdev->mode_info.afmt[1]) {
			wdev->mode_info.afmt[1]->offset = DCE3_HDMI_OFFSET1;
			wdev->mode_info.afmt[1]->id = 1;
		}
	} ewse if (ASIC_IS_DCE2(wdev)) {
		/* DCE2 has at weast 1 woutabwe audio bwock */
		wdev->mode_info.afmt[0] = kzawwoc(sizeof(stwuct wadeon_afmt), GFP_KEWNEW);
		if (wdev->mode_info.afmt[0]) {
			wdev->mode_info.afmt[0]->offset = DCE2_HDMI_OFFSET0;
			wdev->mode_info.afmt[0]->id = 0;
		}
		/* w6xx has 2 woutabwe audio bwocks */
		if (wdev->famiwy >= CHIP_W600) {
			wdev->mode_info.afmt[1] = kzawwoc(sizeof(stwuct wadeon_afmt), GFP_KEWNEW);
			if (wdev->mode_info.afmt[1]) {
				wdev->mode_info.afmt[1]->offset = DCE2_HDMI_OFFSET1;
				wdev->mode_info.afmt[1]->id = 1;
			}
		}
	}
}

static void wadeon_afmt_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < WADEON_MAX_AFMT_BWOCKS; i++) {
		kfwee(wdev->mode_info.afmt[i]);
		wdev->mode_info.afmt[i] = NUWW;
	}
}

int wadeon_modeset_init(stwuct wadeon_device *wdev)
{
	int i;
	int wet;

	dwm_mode_config_init(wdev->ddev);
	wdev->mode_info.mode_config_initiawized = twue;

	wdev->ddev->mode_config.funcs = &wadeon_mode_funcs;

	if (wadeon_use_pfwipiwq == 2 && wdev->famiwy >= CHIP_W600)
		wdev->ddev->mode_config.async_page_fwip = twue;

	if (ASIC_IS_DCE5(wdev)) {
		wdev->ddev->mode_config.max_width = 16384;
		wdev->ddev->mode_config.max_height = 16384;
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		wdev->ddev->mode_config.max_width = 8192;
		wdev->ddev->mode_config.max_height = 8192;
	} ewse {
		wdev->ddev->mode_config.max_width = 4096;
		wdev->ddev->mode_config.max_height = 4096;
	}

	wdev->ddev->mode_config.pwefewwed_depth = 24;
	wdev->ddev->mode_config.pwefew_shadow = 1;

	wdev->ddev->mode_config.fb_modifiews_not_suppowted = twue;

	wet = wadeon_modeset_cweate_pwops(wdev);
	if (wet) {
		wetuwn wet;
	}

	/* init i2c buses */
	wadeon_i2c_init(wdev);

	/* check combios fow a vawid hawdcoded EDID - Sun sewvews */
	if (!wdev->is_atom_bios) {
		/* check fow hawdcoded EDID in BIOS */
		wadeon_combios_check_hawdcoded_edid(wdev);
	}

	/* awwocate cwtcs */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		wadeon_cwtc_init(wdev->ddev, i);
	}

	/* okay we shouwd have aww the bios connectows */
	wet = wadeon_setup_enc_conn(wdev->ddev);
	if (!wet) {
		wetuwn wet;
	}

	/* init dig PHYs, disp eng pww */
	if (wdev->is_atom_bios) {
		wadeon_atom_encodew_init(wdev);
		wadeon_atom_disp_eng_pww_init(wdev);
	}

	/* initiawize hpd */
	wadeon_hpd_init(wdev);

	/* setup afmt */
	wadeon_afmt_init(wdev);

	dwm_kms_hewpew_poww_init(wdev->ddev);

	/* do pm wate init */
	wet = wadeon_pm_wate_init(wdev);

	wetuwn 0;
}

void wadeon_modeset_fini(stwuct wadeon_device *wdev)
{
	if (wdev->mode_info.mode_config_initiawized) {
		dwm_kms_hewpew_poww_fini(wdev->ddev);
		wadeon_hpd_fini(wdev);
		dwm_hewpew_fowce_disabwe_aww(wdev->ddev);
		wadeon_afmt_fini(wdev);
		dwm_mode_config_cweanup(wdev->ddev);
		wdev->mode_info.mode_config_initiawized = fawse;
	}

	kfwee(wdev->mode_info.bios_hawdcoded_edid);

	/* fwee i2c buses */
	wadeon_i2c_fini(wdev);
}

static boow is_hdtv_mode(const stwuct dwm_dispway_mode *mode)
{
	/* twy and guess if this is a tv ow a monitow */
	if ((mode->vdispway == 480 && mode->hdispway == 720) || /* 480p */
	    (mode->vdispway == 576) || /* 576p */
	    (mode->vdispway == 720) || /* 720p */
	    (mode->vdispway == 1080)) /* 1080p */
		wetuwn twue;
	ewse
		wetuwn fawse;
}

boow wadeon_cwtc_scawing_mode_fixup(stwuct dwm_cwtc *cwtc,
				const stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct dwm_connectow *connectow;
	boow fiwst = twue;
	u32 swc_v = 1, dst_v = 1;
	u32 swc_h = 1, dst_h = 1;

	wadeon_cwtc->h_bowdew = 0;
	wadeon_cwtc->v_bowdew = 0;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc != cwtc)
			continue;
		wadeon_encodew = to_wadeon_encodew(encodew);
		connectow = wadeon_get_connectow_fow_encodew(encodew);

		if (fiwst) {
			/* set scawing */
			if (wadeon_encodew->wmx_type == WMX_OFF)
				wadeon_cwtc->wmx_type = WMX_OFF;
			ewse if (mode->hdispway < wadeon_encodew->native_mode.hdispway ||
				 mode->vdispway < wadeon_encodew->native_mode.vdispway)
				wadeon_cwtc->wmx_type = wadeon_encodew->wmx_type;
			ewse
				wadeon_cwtc->wmx_type = WMX_OFF;
			/* copy native mode */
			memcpy(&wadeon_cwtc->native_mode,
			       &wadeon_encodew->native_mode,
				sizeof(stwuct dwm_dispway_mode));
			swc_v = cwtc->mode.vdispway;
			dst_v = wadeon_cwtc->native_mode.vdispway;
			swc_h = cwtc->mode.hdispway;
			dst_h = wadeon_cwtc->native_mode.hdispway;

			/* fix up fow ovewscan on hdmi */
			if (ASIC_IS_AVIVO(wdev) &&
			    (!(mode->fwags & DWM_MODE_FWAG_INTEWWACE)) &&
			    ((wadeon_encodew->undewscan_type == UNDEWSCAN_ON) ||
			     ((wadeon_encodew->undewscan_type == UNDEWSCAN_AUTO) &&
			      dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow)) &&
			      is_hdtv_mode(mode)))) {
				if (wadeon_encodew->undewscan_hbowdew != 0)
					wadeon_cwtc->h_bowdew = wadeon_encodew->undewscan_hbowdew;
				ewse
					wadeon_cwtc->h_bowdew = (mode->hdispway >> 5) + 16;
				if (wadeon_encodew->undewscan_vbowdew != 0)
					wadeon_cwtc->v_bowdew = wadeon_encodew->undewscan_vbowdew;
				ewse
					wadeon_cwtc->v_bowdew = (mode->vdispway >> 5) + 16;
				wadeon_cwtc->wmx_type = WMX_FUWW;
				swc_v = cwtc->mode.vdispway;
				dst_v = cwtc->mode.vdispway - (wadeon_cwtc->v_bowdew * 2);
				swc_h = cwtc->mode.hdispway;
				dst_h = cwtc->mode.hdispway - (wadeon_cwtc->h_bowdew * 2);
			}
			fiwst = fawse;
		} ewse {
			if (wadeon_cwtc->wmx_type != wadeon_encodew->wmx_type) {
				/* WAWNING: Wight now this can't happen but
				 * in the futuwe we need to check that scawing
				 * awe consistent acwoss diffewent encodew
				 * (ie aww encodew can wowk with the same
				 *  scawing).
				 */
				DWM_EWWOW("Scawing not consistent acwoss encodew.\n");
				wetuwn fawse;
			}
		}
	}
	if (wadeon_cwtc->wmx_type != WMX_OFF) {
		fixed20_12 a, b;
		a.fuww = dfixed_const(swc_v);
		b.fuww = dfixed_const(dst_v);
		wadeon_cwtc->vsc.fuww = dfixed_div(a, b);
		a.fuww = dfixed_const(swc_h);
		b.fuww = dfixed_const(dst_h);
		wadeon_cwtc->hsc.fuww = dfixed_div(a, b);
	} ewse {
		wadeon_cwtc->vsc.fuww = dfixed_const(1);
		wadeon_cwtc->hsc.fuww = dfixed_const(1);
	}
	wetuwn twue;
}

/*
 * Wetwieve cuwwent video scanout position of cwtc on a given gpu, and
 * an optionaw accuwate timestamp of when quewy happened.
 *
 * \pawam dev Device to quewy.
 * \pawam cwtc Cwtc to quewy.
 * \pawam fwags Fwags fwom cawwew (DWM_CAWWED_FWOM_VBWIWQ ow 0).
 *              Fow dwivew intewnaw use onwy awso suppowts these fwags:
 *
 *              USE_WEAW_VBWANKSTAWT to use the weaw stawt of vbwank instead
 *              of a fudged eawwiew stawt of vbwank.
 *
 *              GET_DISTANCE_TO_VBWANKSTAWT to wetuwn distance to the
 *              fudged eawwiew stawt of vbwank in *vpos and the distance
 *              to twue stawt of vbwank in *hpos.
 *
 * \pawam *vpos Wocation whewe vewticaw scanout position shouwd be stowed.
 * \pawam *hpos Wocation whewe howizontaw scanout position shouwd go.
 * \pawam *stime Tawget wocation fow timestamp taken immediatewy befowe
 *               scanout position quewy. Can be NUWW to skip timestamp.
 * \pawam *etime Tawget wocation fow timestamp taken immediatewy aftew
 *               scanout position quewy. Can be NUWW to skip timestamp.
 *
 * Wetuwns vpos as a positive numbew whiwe in active scanout awea.
 * Wetuwns vpos as a negative numbew inside vbwank, counting the numbew
 * of scanwines to go untiw end of vbwank, e.g., -1 means "one scanwine
 * untiw stawt of active scanout / end of vbwank."
 *
 * \wetuwn Fwags, ow'ed togethew as fowwows:
 *
 * DWM_SCANOUTPOS_VAWID = Quewy successfuw.
 * DWM_SCANOUTPOS_INVBW = Inside vbwank.
 * DWM_SCANOUTPOS_ACCUWATE = Wetuwned position is accuwate. A wack of
 * this fwag means that wetuwned position may be offset by a constant but
 * unknown smaww numbew of scanwines wwt. weaw scanout position.
 *
 */
int wadeon_get_cwtc_scanoutpos(stwuct dwm_device *dev, unsigned int pipe,
			       unsigned int fwags, int *vpos, int *hpos,
			       ktime_t *stime, ktime_t *etime,
			       const stwuct dwm_dispway_mode *mode)
{
	u32 stat_cwtc = 0, vbw = 0, position = 0;
	int vbw_stawt, vbw_end, vtotaw, wet = 0;
	boow in_vbw = twue;

	stwuct wadeon_device *wdev = dev->dev_pwivate;

	/* pweempt_disabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Get optionaw system timestamp befowe quewy. */
	if (stime)
		*stime = ktime_get();

	if (ASIC_IS_DCE4(wdev)) {
		if (pipe == 0) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC0_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC0_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 1) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC1_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC1_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 2) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC2_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC2_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 3) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC3_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC3_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 4) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC4_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC4_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 5) {
			vbw = WWEG32(EVEWGWEEN_CWTC_V_BWANK_STAWT_END +
				     EVEWGWEEN_CWTC5_WEGISTEW_OFFSET);
			position = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION +
					  EVEWGWEEN_CWTC5_WEGISTEW_OFFSET);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		if (pipe == 0) {
			vbw = WWEG32(AVIVO_D1CWTC_V_BWANK_STAWT_END);
			position = WWEG32(AVIVO_D1CWTC_STATUS_POSITION);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 1) {
			vbw = WWEG32(AVIVO_D2CWTC_V_BWANK_STAWT_END);
			position = WWEG32(AVIVO_D2CWTC_STATUS_POSITION);
			wet |= DWM_SCANOUTPOS_VAWID;
		}
	} ewse {
		/* Pwe-AVIVO: Diffewent encoding of scanout pos and vbwank intewvaw. */
		if (pipe == 0) {
			/* Assume vbw_end == 0, get vbw_stawt fwom
			 * uppew 16 bits.
			 */
			vbw = (WWEG32(WADEON_CWTC_V_TOTAW_DISP) &
				WADEON_CWTC_V_DISP) >> WADEON_CWTC_V_DISP_SHIFT;
			/* Onwy wetwieve vpos fwom uppew 16 bits, set hpos == 0. */
			position = (WWEG32(WADEON_CWTC_VWINE_CWNT_VWINE) >> 16) & WADEON_CWTC_V_TOTAW;
			stat_cwtc = WWEG32(WADEON_CWTC_STATUS);
			if (!(stat_cwtc & 1))
				in_vbw = fawse;

			wet |= DWM_SCANOUTPOS_VAWID;
		}
		if (pipe == 1) {
			vbw = (WWEG32(WADEON_CWTC2_V_TOTAW_DISP) &
				WADEON_CWTC_V_DISP) >> WADEON_CWTC_V_DISP_SHIFT;
			position = (WWEG32(WADEON_CWTC2_VWINE_CWNT_VWINE) >> 16) & WADEON_CWTC_V_TOTAW;
			stat_cwtc = WWEG32(WADEON_CWTC2_STATUS);
			if (!(stat_cwtc & 1))
				in_vbw = fawse;

			wet |= DWM_SCANOUTPOS_VAWID;
		}
	}

	/* Get optionaw system timestamp aftew quewy. */
	if (etime)
		*etime = ktime_get();

	/* pweempt_enabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Decode into vewticaw and howizontaw scanout position. */
	*vpos = position & 0x1fff;
	*hpos = (position >> 16) & 0x1fff;

	/* Vawid vbwank awea boundawies fwom gpu wetwieved? */
	if (vbw > 0) {
		/* Yes: Decode. */
		wet |= DWM_SCANOUTPOS_ACCUWATE;
		vbw_stawt = vbw & 0x1fff;
		vbw_end = (vbw >> 16) & 0x1fff;
	}
	ewse {
		/* No: Fake something weasonabwe which gives at weast ok wesuwts. */
		vbw_stawt = mode->cwtc_vdispway;
		vbw_end = 0;
	}

	/* Cawwed fwom dwivew intewnaw vbwank countew quewy code? */
	if (fwags & GET_DISTANCE_TO_VBWANKSTAWT) {
	    /* Cawwew wants distance fwom weaw vbw_stawt in *hpos */
	    *hpos = *vpos - vbw_stawt;
	}

	/* Fudge vbwank to stawt a few scanwines eawwiew to handwe the
	 * pwobwem that vbwank iwqs fiwe a few scanwines befowe stawt
	 * of vbwank. Some dwivew intewnaw cawwews need the twue vbwank
	 * stawt to be used and signaw this via the USE_WEAW_VBWANKSTAWT fwag.
	 *
	 * The cause of the "eawwy" vbwank iwq is that the iwq is twiggewed
	 * by the wine buffew wogic when the wine buffew wead position entews
	 * the vbwank, wheweas ouw cwtc scanout position natuwawwy wags the
	 * wine buffew wead position.
	 */
	if (!(fwags & USE_WEAW_VBWANKSTAWT))
		vbw_stawt -= wdev->mode_info.cwtcs[pipe]->wb_vbwank_wead_wines;

	/* Test scanout position against vbwank wegion. */
	if ((*vpos < vbw_stawt) && (*vpos >= vbw_end))
		in_vbw = fawse;

	/* In vbwank? */
	if (in_vbw)
	    wet |= DWM_SCANOUTPOS_IN_VBWANK;

	/* Cawwed fwom dwivew intewnaw vbwank countew quewy code? */
	if (fwags & GET_DISTANCE_TO_VBWANKSTAWT) {
		/* Cawwew wants distance fwom fudged eawwiew vbw_stawt */
		*vpos -= vbw_stawt;
		wetuwn wet;
	}

	/* Check if inside vbwank awea and appwy cowwective offsets:
	 * vpos wiww then be >=0 in video scanout awea, but negative
	 * within vbwank awea, counting down the numbew of wines untiw
	 * stawt of scanout.
	 */

	/* Inside "uppew pawt" of vbwank awea? Appwy cowwective offset if so: */
	if (in_vbw && (*vpos >= vbw_stawt)) {
		vtotaw = mode->cwtc_vtotaw;
		*vpos = *vpos - vtotaw;
	}

	/* Cowwect fow shifted end of vbw at vbw_end. */
	*vpos = *vpos - vbw_end;

	wetuwn wet;
}

boow
wadeon_get_cwtc_scanout_position(stwuct dwm_cwtc *cwtc,
				 boow in_vbwank_iwq, int *vpos, int *hpos,
				 ktime_t *stime, ktime_t *etime,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;

	wetuwn wadeon_get_cwtc_scanoutpos(dev, pipe, 0, vpos, hpos,
					  stime, etime, mode);
}
