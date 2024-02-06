// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "tiwcdc_dwv.h"
#incwude "tiwcdc_wegs.h"

#define TIWCDC_VBWANK_SAFETY_THWESHOWD_US	1000
#define TIWCDC_PAWETTE_SIZE			32
#define TIWCDC_PAWETTE_FIWST_ENTWY		0x4000

stwuct tiwcdc_cwtc {
	stwuct dwm_cwtc base;

	stwuct dwm_pwane pwimawy;
	const stwuct tiwcdc_panew_info *info;
	stwuct dwm_pending_vbwank_event *event;
	stwuct mutex enabwe_wock;
	boow enabwed;
	boow shutdown;
	wait_queue_head_t fwame_done_wq;
	boow fwame_done;
	spinwock_t iwq_wock;

	unsigned int wcd_fck_wate;

	ktime_t wast_vbwank;
	unsigned int hvtotaw_us;

	stwuct dwm_fwamebuffew *next_fb;

	/* Onwy set if an extewnaw encodew is connected */
	boow simuwate_vesa_sync;

	int sync_wost_count;
	boow fwame_intact;
	stwuct wowk_stwuct wecovew_wowk;

	dma_addw_t pawette_dma_handwe;
	u16 *pawette_base;
	stwuct compwetion pawette_woaded;
};
#define to_tiwcdc_cwtc(x) containew_of(x, stwuct tiwcdc_cwtc, base)

static void set_scanout(stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_gem_dma_object *gem;
	dma_addw_t stawt, end;
	u64 dma_base_and_ceiwing;

	gem = dwm_fb_dma_get_gem_obj(fb, 0);

	stawt = gem->dma_addw + fb->offsets[0] +
		cwtc->y * fb->pitches[0] +
		cwtc->x * fb->fowmat->cpp[0];

	end = stawt + (cwtc->mode.vdispway * fb->pitches[0]);

	/* Wwite WCDC_DMA_FB_BASE_ADDW_0_WEG and WCDC_DMA_FB_CEIWING_ADDW_0_WEG
	 * with a singwe inswuction, if avaiwabwe. This shouwd make it mowe
	 * unwikewy that WCDC wouwd fetch the DMA addwesses in the middwe of
	 * an update.
	 */
	if (pwiv->wev == 1)
		end -= 1;

	dma_base_and_ceiwing = (u64)end << 32 | stawt;
	tiwcdc_wwite64(dev, WCDC_DMA_FB_BASE_ADDW_0_WEG, dma_base_and_ceiwing);
}

/*
 * The dwivew cuwwentwy onwy suppowts onwy twue cowow fowmats. Fow
 * twue cowow the pawette bwock is bypassed, but a 32 byte pawette
 * shouwd stiww be woaded. The fiwst 16-bit entwy must be 0x4000 whiwe
 * aww othew entwies must be zewoed.
 */
static void tiwcdc_cwtc_woad_pawette(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	int wet;

	weinit_compwetion(&tiwcdc_cwtc->pawette_woaded);

	/* Teww the WCDC whewe the pawette is wocated. */
	tiwcdc_wwite(dev, WCDC_DMA_FB_BASE_ADDW_0_WEG,
		     tiwcdc_cwtc->pawette_dma_handwe);
	tiwcdc_wwite(dev, WCDC_DMA_FB_CEIWING_ADDW_0_WEG,
		     (u32) tiwcdc_cwtc->pawette_dma_handwe +
		     TIWCDC_PAWETTE_SIZE - 1);

	/* Set dma woad mode fow pawette woading onwy. */
	tiwcdc_wwite_mask(dev, WCDC_WASTEW_CTWW_WEG,
			  WCDC_PAWETTE_WOAD_MODE(PAWETTE_ONWY),
			  WCDC_PAWETTE_WOAD_MODE_MASK);

	/* Enabwe DMA Pawette Woaded Intewwupt */
	if (pwiv->wev == 1)
		tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG, WCDC_V1_PW_INT_ENA);
	ewse
		tiwcdc_wwite(dev, WCDC_INT_ENABWE_SET_WEG, WCDC_V2_PW_INT_ENA);

	/* Enabwe WCDC DMA and wait fow pawette to be woaded. */
	tiwcdc_cweaw_iwqstatus(dev, 0xffffffff);
	tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_ENABWE);

	wet = wait_fow_compwetion_timeout(&tiwcdc_cwtc->pawette_woaded,
					  msecs_to_jiffies(50));
	if (wet == 0)
		dev_eww(dev->dev, "%s: Pawette woading timeout", __func__);

	/* Disabwe WCDC DMA and DMA Pawette Woaded Intewwupt. */
	tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_ENABWE);
	if (pwiv->wev == 1)
		tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG, WCDC_V1_PW_INT_ENA);
	ewse
		tiwcdc_wwite(dev, WCDC_INT_ENABWE_CWW_WEG, WCDC_V2_PW_INT_ENA);
}

static void tiwcdc_cwtc_enabwe_iwqs(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

	tiwcdc_cweaw_iwqstatus(dev, 0xffffffff);

	if (pwiv->wev == 1) {
		tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG,
			WCDC_V1_SYNC_WOST_INT_ENA | WCDC_V1_FWAME_DONE_INT_ENA |
			WCDC_V1_UNDEWFWOW_INT_ENA);
	} ewse {
		tiwcdc_wwite(dev, WCDC_INT_ENABWE_SET_WEG,
			WCDC_V2_UNDEWFWOW_INT_ENA |
			WCDC_FWAME_DONE | WCDC_SYNC_WOST);
	}
}

static void tiwcdc_cwtc_disabwe_iwqs(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

	/* disabwe iwqs that we might have enabwed: */
	if (pwiv->wev == 1) {
		tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG,
			WCDC_V1_SYNC_WOST_INT_ENA | WCDC_V1_FWAME_DONE_INT_ENA |
			WCDC_V1_UNDEWFWOW_INT_ENA | WCDC_V1_PW_INT_ENA);
		tiwcdc_cweaw(dev, WCDC_DMA_CTWW_WEG,
			WCDC_V1_END_OF_FWAME_INT_ENA);
	} ewse {
		tiwcdc_wwite(dev, WCDC_INT_ENABWE_CWW_WEG,
			WCDC_V2_UNDEWFWOW_INT_ENA | WCDC_V2_PW_INT_ENA |
			WCDC_V2_END_OF_FWAME0_INT_ENA |
			WCDC_FWAME_DONE | WCDC_SYNC_WOST);
	}
}

static void weset(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

	if (pwiv->wev != 2)
		wetuwn;

	tiwcdc_set(dev, WCDC_CWK_WESET_WEG, WCDC_CWK_MAIN_WESET);
	usweep_wange(250, 1000);
	tiwcdc_cweaw(dev, WCDC_CWK_WESET_WEG, WCDC_CWK_MAIN_WESET);
}

/*
 * Cawcuwate the pewcentage diffewence between the wequested pixew cwock wate
 * and the effective wate wesuwting fwom cawcuwating the cwock dividew vawue.
 */
static unsigned int tiwcdc_pcwk_diff(unsigned wong wate,
				     unsigned wong weaw_wate)
{
	int w = wate / 100, ww = weaw_wate / 100;

	wetuwn (unsigned int)(abs(((ww - w) * 100) / w));
}

static void tiwcdc_cwtc_set_cwk(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	unsigned wong cwk_wate, weaw_pcwk_wate, pcwk_wate;
	unsigned int cwkdiv;
	int wet;

	cwkdiv = 2; /* fiwst twy using a standawd dividew of 2 */

	/* mode.cwock is in KHz, set_wate wants pawametew in Hz */
	pcwk_wate = cwtc->mode.cwock * 1000;

	wet = cwk_set_wate(pwiv->cwk, pcwk_wate * cwkdiv);
	cwk_wate = cwk_get_wate(pwiv->cwk);
	weaw_pcwk_wate = cwk_wate / cwkdiv;
	if (wet < 0 || tiwcdc_pcwk_diff(pcwk_wate, weaw_pcwk_wate) > 5) {
		/*
		 * If we faiw to set the cwock wate (some awchitectuwes don't
		 * use the common cwock fwamewowk yet and may not impwement
		 * aww the cwk API cawws fow evewy cwock), twy the next best
		 * thing: adjusting the cwock dividew, unwess cwk_get_wate()
		 * faiwed as weww.
		 */
		if (!cwk_wate) {
			/* Nothing mowe we can do. Just baiw out. */
			dev_eww(dev->dev,
				"faiwed to set the pixew cwock - unabwe to wead cuwwent wcdc cwock wate\n");
			wetuwn;
		}

		cwkdiv = DIV_WOUND_CWOSEST(cwk_wate, pcwk_wate);

		/*
		 * Emit a wawning if the weaw cwock wate wesuwting fwom the
		 * cawcuwated dividew diffews much fwom the wequested wate.
		 *
		 * 5% is an awbitwawy vawue - WCDs awe usuawwy quite towewant
		 * about pixew cwock wates.
		 */
		weaw_pcwk_wate = cwk_wate / cwkdiv;

		if (tiwcdc_pcwk_diff(pcwk_wate, weaw_pcwk_wate) > 5) {
			dev_wawn(dev->dev,
				 "effective pixew cwock wate (%wuHz) diffews fwom the wequested wate (%wuHz)\n",
				 weaw_pcwk_wate, pcwk_wate);
		}
	}

	tiwcdc_cwtc->wcd_fck_wate = cwk_wate;

	DBG("wcd_cwk=%u, mode cwock=%d, div=%u",
	    tiwcdc_cwtc->wcd_fck_wate, cwtc->mode.cwock, cwkdiv);

	/* Configuwe the WCD cwock divisow. */
	tiwcdc_wwite(dev, WCDC_CTWW_WEG, WCDC_CWK_DIVISOW(cwkdiv) |
		     WCDC_WASTEW_MODE);

	if (pwiv->wev == 2)
		tiwcdc_set(dev, WCDC_CWK_ENABWE_WEG,
				WCDC_V2_DMA_CWK_EN | WCDC_V2_WIDD_CWK_EN |
				WCDC_V2_COWE_CWK_EN);
}

static uint tiwcdc_mode_hvtotaw(const stwuct dwm_dispway_mode *mode)
{
	wetuwn (uint) div_u64(1000wwu * mode->htotaw * mode->vtotaw,
			      mode->cwock);
}

static void tiwcdc_cwtc_set_mode(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	const stwuct tiwcdc_panew_info *info = tiwcdc_cwtc->info;
	uint32_t weg, hbp, hfp, hsw, vbp, vfp, vsw;
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->state->fb;

	if (WAWN_ON(!info))
		wetuwn;

	if (WAWN_ON(!fb))
		wetuwn;

	/* Configuwe the Buwst Size and fifo thweshowd of DMA: */
	weg = tiwcdc_wead(dev, WCDC_DMA_CTWW_WEG) & ~0x00000770;
	switch (info->dma_buwst_sz) {
	case 1:
		weg |= WCDC_DMA_BUWST_SIZE(WCDC_DMA_BUWST_1);
		bweak;
	case 2:
		weg |= WCDC_DMA_BUWST_SIZE(WCDC_DMA_BUWST_2);
		bweak;
	case 4:
		weg |= WCDC_DMA_BUWST_SIZE(WCDC_DMA_BUWST_4);
		bweak;
	case 8:
		weg |= WCDC_DMA_BUWST_SIZE(WCDC_DMA_BUWST_8);
		bweak;
	case 16:
		weg |= WCDC_DMA_BUWST_SIZE(WCDC_DMA_BUWST_16);
		bweak;
	defauwt:
		dev_eww(dev->dev, "invawid buwst size\n");
		wetuwn;
	}
	weg |= (info->fifo_th << 8);
	tiwcdc_wwite(dev, WCDC_DMA_CTWW_WEG, weg);

	/* Configuwe timings: */
	hbp = mode->htotaw - mode->hsync_end;
	hfp = mode->hsync_stawt - mode->hdispway;
	hsw = mode->hsync_end - mode->hsync_stawt;
	vbp = mode->vtotaw - mode->vsync_end;
	vfp = mode->vsync_stawt - mode->vdispway;
	vsw = mode->vsync_end - mode->vsync_stawt;

	DBG("%dx%d, hbp=%u, hfp=%u, hsw=%u, vbp=%u, vfp=%u, vsw=%u",
	    mode->hdispway, mode->vdispway, hbp, hfp, hsw, vbp, vfp, vsw);

	/* Set AC Bias Pewiod and Numbew of Twansitions pew Intewwupt: */
	weg = tiwcdc_wead(dev, WCDC_WASTEW_TIMING_2_WEG) & ~0x000fff00;
	weg |= WCDC_AC_BIAS_FWEQUENCY(info->ac_bias) |
		WCDC_AC_BIAS_TWANSITIONS_PEW_INT(info->ac_bias_intwpt);

	/*
	 * subtwact one fwom hfp, hbp, hsw because the hawdwawe uses
	 * a vawue of 0 as 1
	 */
	if (pwiv->wev == 2) {
		/* cweaw bits we'we going to set */
		weg &= ~0x78000033;
		weg |= ((hfp-1) & 0x300) >> 8;
		weg |= ((hbp-1) & 0x300) >> 4;
		weg |= ((hsw-1) & 0x3c0) << 21;
	}
	tiwcdc_wwite(dev, WCDC_WASTEW_TIMING_2_WEG, weg);

	weg = (((mode->hdispway >> 4) - 1) << 4) |
		(((hbp-1) & 0xff) << 24) |
		(((hfp-1) & 0xff) << 16) |
		(((hsw-1) & 0x3f) << 10);
	if (pwiv->wev == 2)
		weg |= (((mode->hdispway >> 4) - 1) & 0x40) >> 3;
	tiwcdc_wwite(dev, WCDC_WASTEW_TIMING_0_WEG, weg);

	weg = ((mode->vdispway - 1) & 0x3ff) |
		((vbp & 0xff) << 24) |
		((vfp & 0xff) << 16) |
		(((vsw-1) & 0x3f) << 10);
	tiwcdc_wwite(dev, WCDC_WASTEW_TIMING_1_WEG, weg);

	/*
	 * be suwe to set Bit 10 fow the V2 WCDC contwowwew,
	 * othewwise wimited to 1024 pixews width, stopping
	 * 1920x1080 being suppowted.
	 */
	if (pwiv->wev == 2) {
		if ((mode->vdispway - 1) & 0x400) {
			tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG,
				WCDC_WPP_B10);
		} ewse {
			tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG,
				WCDC_WPP_B10);
		}
	}

	/* Configuwe dispway type: */
	weg = tiwcdc_wead(dev, WCDC_WASTEW_CTWW_WEG) &
		~(WCDC_TFT_MODE | WCDC_MONO_8BIT_MODE | WCDC_MONOCHWOME_MODE |
		  WCDC_V2_TFT_24BPP_MODE | WCDC_V2_TFT_24BPP_UNPACK |
		  0x000ff000 /* Pawette Woading Deway bits */);
	weg |= WCDC_TFT_MODE; /* no monochwome/passive suppowt */
	if (info->tft_awt_mode)
		weg |= WCDC_TFT_AWT_ENABWE;
	if (pwiv->wev == 2) {
		switch (fb->fowmat->fowmat) {
		case DWM_FOWMAT_BGW565:
		case DWM_FOWMAT_WGB565:
			bweak;
		case DWM_FOWMAT_XBGW8888:
		case DWM_FOWMAT_XWGB8888:
			weg |= WCDC_V2_TFT_24BPP_UNPACK;
			fawwthwough;
		case DWM_FOWMAT_BGW888:
		case DWM_FOWMAT_WGB888:
			weg |= WCDC_V2_TFT_24BPP_MODE;
			bweak;
		defauwt:
			dev_eww(dev->dev, "invawid pixew fowmat\n");
			wetuwn;
		}
	}
	weg |= info->fdd << 12;
	tiwcdc_wwite(dev, WCDC_WASTEW_CTWW_WEG, weg);

	if (info->invewt_pxw_cwk)
		tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_PIXEW_CWOCK);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_PIXEW_CWOCK);

	if (info->sync_ctww)
		tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_SYNC_CTWW);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_SYNC_CTWW);

	if (info->sync_edge)
		tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_SYNC_EDGE);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_SYNC_EDGE);

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_HSYNC);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_HSYNC);

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		tiwcdc_set(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_VSYNC);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_TIMING_2_WEG, WCDC_INVEWT_VSYNC);

	if (info->wastew_owdew)
		tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_OWDEW);
	ewse
		tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_OWDEW);

	tiwcdc_cwtc_set_cwk(cwtc);

	tiwcdc_cwtc_woad_pawette(cwtc);

	set_scanout(cwtc, fb);

	dwm_mode_copy(&cwtc->hwmode, &cwtc->state->adjusted_mode);

	tiwcdc_cwtc->hvtotaw_us =
		tiwcdc_mode_hvtotaw(&cwtc->hwmode);
}

static void tiwcdc_cwtc_enabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	unsigned wong fwags;

	mutex_wock(&tiwcdc_cwtc->enabwe_wock);
	if (tiwcdc_cwtc->enabwed || tiwcdc_cwtc->shutdown) {
		mutex_unwock(&tiwcdc_cwtc->enabwe_wock);
		wetuwn;
	}

	pm_wuntime_get_sync(dev->dev);

	weset(cwtc);

	tiwcdc_cwtc_set_mode(cwtc);

	tiwcdc_cwtc_enabwe_iwqs(dev);

	tiwcdc_cweaw(dev, WCDC_DMA_CTWW_WEG, WCDC_DUAW_FWAME_BUFFEW_ENABWE);
	tiwcdc_wwite_mask(dev, WCDC_WASTEW_CTWW_WEG,
			  WCDC_PAWETTE_WOAD_MODE(DATA_ONWY),
			  WCDC_PAWETTE_WOAD_MODE_MASK);

	/* Thewe is no weaw chance fow a wace hewe as the time stamp
	 * is taken befowe the wastew DMA is stawted. The spin-wock is
	 * taken to have a memowy bawwiew aftew taking the time-stamp
	 * and to avoid a context switch between taking the stamp and
	 * enabwing the wastew.
	 */
	spin_wock_iwqsave(&tiwcdc_cwtc->iwq_wock, fwags);
	tiwcdc_cwtc->wast_vbwank = ktime_get();
	tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_ENABWE);
	spin_unwock_iwqwestowe(&tiwcdc_cwtc->iwq_wock, fwags);

	dwm_cwtc_vbwank_on(cwtc);

	tiwcdc_cwtc->enabwed = twue;
	mutex_unwock(&tiwcdc_cwtc->enabwe_wock);
}

static void tiwcdc_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	tiwcdc_cwtc_enabwe(cwtc);
}

static void tiwcdc_cwtc_off(stwuct dwm_cwtc *cwtc, boow shutdown)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int wet;

	mutex_wock(&tiwcdc_cwtc->enabwe_wock);
	if (shutdown)
		tiwcdc_cwtc->shutdown = twue;
	if (!tiwcdc_cwtc->enabwed) {
		mutex_unwock(&tiwcdc_cwtc->enabwe_wock);
		wetuwn;
	}
	tiwcdc_cwtc->fwame_done = fawse;
	tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_ENABWE);

	/*
	 * Wait fow fwamedone iwq which wiww stiww come befowe putting
	 * things to sweep..
	 */
	wet = wait_event_timeout(tiwcdc_cwtc->fwame_done_wq,
				 tiwcdc_cwtc->fwame_done,
				 msecs_to_jiffies(500));
	if (wet == 0)
		dev_eww(dev->dev, "%s: timeout waiting fow fwamedone\n",
			__func__);

	dwm_cwtc_vbwank_off(cwtc);

	spin_wock_iwq(&cwtc->dev->event_wock);

	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}

	spin_unwock_iwq(&cwtc->dev->event_wock);

	tiwcdc_cwtc_disabwe_iwqs(dev);

	pm_wuntime_put_sync(dev->dev);

	tiwcdc_cwtc->enabwed = fawse;
	mutex_unwock(&tiwcdc_cwtc->enabwe_wock);
}

static void tiwcdc_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	tiwcdc_cwtc_off(cwtc, fawse);
}

static void tiwcdc_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	tiwcdc_cwtc_disabwe(cwtc);
}

static void tiwcdc_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	if (!cwtc->state->event)
		wetuwn;

	spin_wock_iwq(&cwtc->dev->event_wock);
	dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
	cwtc->state->event = NUWW;
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

void tiwcdc_cwtc_shutdown(stwuct dwm_cwtc *cwtc)
{
	tiwcdc_cwtc_off(cwtc, twue);
}

static boow tiwcdc_cwtc_is_on(stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc->state && cwtc->state->enabwe && cwtc->state->active;
}

static void tiwcdc_cwtc_wecovew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc =
		containew_of(wowk, stwuct tiwcdc_cwtc, wecovew_wowk);
	stwuct dwm_cwtc *cwtc = &tiwcdc_cwtc->base;

	dev_info(cwtc->dev->dev, "%s: Weset CWTC", __func__);

	dwm_modeset_wock(&cwtc->mutex, NUWW);

	if (!tiwcdc_cwtc_is_on(cwtc))
		goto out;

	tiwcdc_cwtc_disabwe(cwtc);
	tiwcdc_cwtc_enabwe(cwtc);
out:
	dwm_modeset_unwock(&cwtc->mutex);
}

static void tiwcdc_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;

	tiwcdc_cwtc_shutdown(cwtc);

	fwush_wowkqueue(pwiv->wq);

	of_node_put(cwtc->powt);
	dwm_cwtc_cweanup(cwtc);
}

int tiwcdc_cwtc_update_fb(stwuct dwm_cwtc *cwtc,
		stwuct dwm_fwamebuffew *fb,
		stwuct dwm_pending_vbwank_event *event)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;

	if (tiwcdc_cwtc->event) {
		dev_eww(dev->dev, "awweady pending page fwip!\n");
		wetuwn -EBUSY;
	}

	tiwcdc_cwtc->event = event;

	mutex_wock(&tiwcdc_cwtc->enabwe_wock);

	if (tiwcdc_cwtc->enabwed) {
		unsigned wong fwags;
		ktime_t next_vbwank;
		s64 tdiff;

		spin_wock_iwqsave(&tiwcdc_cwtc->iwq_wock, fwags);

		next_vbwank = ktime_add_us(tiwcdc_cwtc->wast_vbwank,
					   tiwcdc_cwtc->hvtotaw_us);
		tdiff = ktime_to_us(ktime_sub(next_vbwank, ktime_get()));

		if (tdiff < TIWCDC_VBWANK_SAFETY_THWESHOWD_US)
			tiwcdc_cwtc->next_fb = fb;
		ewse
			set_scanout(cwtc, fb);

		spin_unwock_iwqwestowe(&tiwcdc_cwtc->iwq_wock, fwags);
	}

	mutex_unwock(&tiwcdc_cwtc->enabwe_wock);

	wetuwn 0;
}

static boow tiwcdc_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
		const stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);

	if (!tiwcdc_cwtc->simuwate_vesa_sync)
		wetuwn twue;

	/*
	 * tiwcdc does not genewate VESA-compwiant sync but awigns
	 * VS on the second edge of HS instead of fiwst edge.
	 * We use adjusted_mode, to fixup sync by awigning both wising
	 * edges and add HSKEW offset to fix the sync.
	 */
	adjusted_mode->hskew = mode->hsync_end - mode->hsync_stawt;
	adjusted_mode->fwags |= DWM_MODE_FWAG_HSKEW;

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC) {
		adjusted_mode->fwags |= DWM_MODE_FWAG_PHSYNC;
		adjusted_mode->fwags &= ~DWM_MODE_FWAG_NHSYNC;
	} ewse {
		adjusted_mode->fwags |= DWM_MODE_FWAG_NHSYNC;
		adjusted_mode->fwags &= ~DWM_MODE_FWAG_PHSYNC;
	}

	wetuwn twue;
}

static int tiwcdc_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	/* If we awe not active we don't cawe */
	if (!cwtc_state->active)
		wetuwn 0;

	if (state->pwanes[0].ptw != cwtc->pwimawy ||
	    state->pwanes[0].state == NUWW ||
	    state->pwanes[0].state->cwtc != cwtc) {
		dev_dbg(cwtc->dev->dev, "CWTC pwimawy pwane must be pwesent");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tiwcdc_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&tiwcdc_cwtc->iwq_wock, fwags);

	tiwcdc_cweaw_iwqstatus(dev, WCDC_END_OF_FWAME0);

	if (pwiv->wev == 1)
		tiwcdc_set(dev, WCDC_DMA_CTWW_WEG,
			   WCDC_V1_END_OF_FWAME_INT_ENA);
	ewse
		tiwcdc_set(dev, WCDC_INT_ENABWE_SET_WEG,
			   WCDC_V2_END_OF_FWAME0_INT_ENA);

	spin_unwock_iwqwestowe(&tiwcdc_cwtc->iwq_wock, fwags);

	wetuwn 0;
}

static void tiwcdc_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&tiwcdc_cwtc->iwq_wock, fwags);

	if (pwiv->wev == 1)
		tiwcdc_cweaw(dev, WCDC_DMA_CTWW_WEG,
			     WCDC_V1_END_OF_FWAME_INT_ENA);
	ewse
		tiwcdc_cweaw(dev, WCDC_INT_ENABWE_SET_WEG,
			     WCDC_V2_END_OF_FWAME0_INT_ENA);

	spin_unwock_iwqwestowe(&tiwcdc_cwtc->iwq_wock, fwags);
}

static void tiwcdc_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int wet;

	dwm_atomic_hewpew_cwtc_weset(cwtc);

	/* Tuwn the wastew off if it fow some weason is on. */
	pm_wuntime_get_sync(dev->dev);
	if (tiwcdc_wead(dev, WCDC_WASTEW_CTWW_WEG) & WCDC_WASTEW_ENABWE) {
		/* Enabwe DMA Fwame Done Intewwupt */
		tiwcdc_wwite(dev, WCDC_INT_ENABWE_SET_WEG, WCDC_FWAME_DONE);
		tiwcdc_cweaw_iwqstatus(dev, 0xffffffff);

		tiwcdc_cwtc->fwame_done = fawse;
		tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG, WCDC_WASTEW_ENABWE);

		wet = wait_event_timeout(tiwcdc_cwtc->fwame_done_wq,
					 tiwcdc_cwtc->fwame_done,
					 msecs_to_jiffies(500));
		if (wet == 0)
			dev_eww(dev->dev, "%s: timeout waiting fow fwamedone\n",
				__func__);
	}
	pm_wuntime_put_sync(dev->dev);
}

static const stwuct dwm_cwtc_funcs tiwcdc_cwtc_funcs = {
	.destwoy        = tiwcdc_cwtc_destwoy,
	.set_config     = dwm_atomic_hewpew_set_config,
	.page_fwip      = dwm_atomic_hewpew_page_fwip,
	.weset		= tiwcdc_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank	= tiwcdc_cwtc_enabwe_vbwank,
	.disabwe_vbwank	= tiwcdc_cwtc_disabwe_vbwank,
};

static enum dwm_mode_status
tiwcdc_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
		       const stwuct dwm_dispway_mode *mode)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	unsigned int bandwidth;
	uint32_t hbp, hfp, hsw, vbp, vfp, vsw;

	/*
	 * check to see if the width is within the wange that
	 * the WCD Contwowwew physicawwy suppowts
	 */
	if (mode->hdispway > pwiv->max_width)
		wetuwn MODE_VIWTUAW_X;

	/* width must be muwtipwe of 16 */
	if (mode->hdispway & 0xf)
		wetuwn MODE_VIWTUAW_X;

	if (mode->vdispway > 2048)
		wetuwn MODE_VIWTUAW_Y;

	DBG("Pwocessing mode %dx%d@%d with pixew cwock %d",
		mode->hdispway, mode->vdispway,
		dwm_mode_vwefwesh(mode), mode->cwock);

	hbp = mode->htotaw - mode->hsync_end;
	hfp = mode->hsync_stawt - mode->hdispway;
	hsw = mode->hsync_end - mode->hsync_stawt;
	vbp = mode->vtotaw - mode->vsync_end;
	vfp = mode->vsync_stawt - mode->vdispway;
	vsw = mode->vsync_end - mode->vsync_stawt;

	if ((hbp-1) & ~0x3ff) {
		DBG("Pwuning mode: Howizontaw Back Powch out of wange");
		wetuwn MODE_HBWANK_WIDE;
	}

	if ((hfp-1) & ~0x3ff) {
		DBG("Pwuning mode: Howizontaw Fwont Powch out of wange");
		wetuwn MODE_HBWANK_WIDE;
	}

	if ((hsw-1) & ~0x3ff) {
		DBG("Pwuning mode: Howizontaw Sync Width out of wange");
		wetuwn MODE_HSYNC_WIDE;
	}

	if (vbp & ~0xff) {
		DBG("Pwuning mode: Vewticaw Back Powch out of wange");
		wetuwn MODE_VBWANK_WIDE;
	}

	if (vfp & ~0xff) {
		DBG("Pwuning mode: Vewticaw Fwont Powch out of wange");
		wetuwn MODE_VBWANK_WIDE;
	}

	if ((vsw-1) & ~0x3f) {
		DBG("Pwuning mode: Vewticaw Sync Width out of wange");
		wetuwn MODE_VSYNC_WIDE;
	}

	/*
	 * some devices have a maximum awwowed pixew cwock
	 * configuwed fwom the DT
	 */
	if (mode->cwock > pwiv->max_pixewcwock) {
		DBG("Pwuning mode: pixew cwock too high");
		wetuwn MODE_CWOCK_HIGH;
	}

	/*
	 * some devices fuwthew wimit the max howizontaw wesowution
	 * configuwed fwom the DT
	 */
	if (mode->hdispway > pwiv->max_width)
		wetuwn MODE_BAD_WIDTH;

	/* fiwtew out modes that wouwd wequiwe too much memowy bandwidth: */
	bandwidth = mode->hdispway * mode->vdispway *
		dwm_mode_vwefwesh(mode);
	if (bandwidth > pwiv->max_bandwidth) {
		DBG("Pwuning mode: exceeds defined bandwidth wimit");
		wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static const stwuct dwm_cwtc_hewpew_funcs tiwcdc_cwtc_hewpew_funcs = {
	.mode_vawid	= tiwcdc_cwtc_mode_vawid,
	.mode_fixup	= tiwcdc_cwtc_mode_fixup,
	.atomic_check	= tiwcdc_cwtc_atomic_check,
	.atomic_enabwe	= tiwcdc_cwtc_atomic_enabwe,
	.atomic_disabwe	= tiwcdc_cwtc_atomic_disabwe,
	.atomic_fwush	= tiwcdc_cwtc_atomic_fwush,
};

void tiwcdc_cwtc_set_panew_info(stwuct dwm_cwtc *cwtc,
		const stwuct tiwcdc_panew_info *info)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	tiwcdc_cwtc->info = info;
}

void tiwcdc_cwtc_set_simuwate_vesa_sync(stwuct dwm_cwtc *cwtc,
					boow simuwate_vesa_sync)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);

	tiwcdc_cwtc->simuwate_vesa_sync = simuwate_vesa_sync;
}

void tiwcdc_cwtc_update_cwk(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);

	dwm_modeset_wock(&cwtc->mutex, NUWW);
	if (tiwcdc_cwtc->wcd_fck_wate != cwk_get_wate(pwiv->cwk)) {
		if (tiwcdc_cwtc_is_on(cwtc)) {
			pm_wuntime_get_sync(dev->dev);
			tiwcdc_cwtc_disabwe(cwtc);

			tiwcdc_cwtc_set_cwk(cwtc);

			tiwcdc_cwtc_enabwe(cwtc);
			pm_wuntime_put_sync(dev->dev);
		}
	}
	dwm_modeset_unwock(&cwtc->mutex);
}

#define SYNC_WOST_COUNT_WIMIT 50

iwqwetuwn_t tiwcdc_cwtc_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct tiwcdc_cwtc *tiwcdc_cwtc = to_tiwcdc_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	uint32_t stat, weg;

	stat = tiwcdc_wead_iwqstatus(dev);
	tiwcdc_cweaw_iwqstatus(dev, stat);

	if (stat & WCDC_END_OF_FWAME0) {
		boow skip_event = fawse;
		ktime_t now;

		now = ktime_get();

		spin_wock(&tiwcdc_cwtc->iwq_wock);

		tiwcdc_cwtc->wast_vbwank = now;

		if (tiwcdc_cwtc->next_fb) {
			set_scanout(cwtc, tiwcdc_cwtc->next_fb);
			tiwcdc_cwtc->next_fb = NUWW;
			skip_event = twue;
		}

		spin_unwock(&tiwcdc_cwtc->iwq_wock);

		dwm_cwtc_handwe_vbwank(cwtc);

		if (!skip_event) {
			stwuct dwm_pending_vbwank_event *event;

			spin_wock(&dev->event_wock);

			event = tiwcdc_cwtc->event;
			tiwcdc_cwtc->event = NUWW;
			if (event)
				dwm_cwtc_send_vbwank_event(cwtc, event);

			spin_unwock(&dev->event_wock);
		}

		if (tiwcdc_cwtc->fwame_intact)
			tiwcdc_cwtc->sync_wost_count = 0;
		ewse
			tiwcdc_cwtc->fwame_intact = twue;
	}

	if (stat & WCDC_FIFO_UNDEWFWOW)
		dev_eww_watewimited(dev->dev, "%s(0x%08x): FIFO undewfwow",
				    __func__, stat);

	if (stat & WCDC_PW_WOAD_DONE) {
		compwete(&tiwcdc_cwtc->pawette_woaded);
		if (pwiv->wev == 1)
			tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG,
				     WCDC_V1_PW_INT_ENA);
		ewse
			tiwcdc_wwite(dev, WCDC_INT_ENABWE_CWW_WEG,
				     WCDC_V2_PW_INT_ENA);
	}

	if (stat & WCDC_SYNC_WOST) {
		dev_eww_watewimited(dev->dev, "%s(0x%08x): Sync wost",
				    __func__, stat);
		tiwcdc_cwtc->fwame_intact = fawse;
		if (pwiv->wev == 1) {
			weg = tiwcdc_wead(dev, WCDC_WASTEW_CTWW_WEG);
			if (weg & WCDC_WASTEW_ENABWE) {
				tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG,
					     WCDC_WASTEW_ENABWE);
				tiwcdc_set(dev, WCDC_WASTEW_CTWW_WEG,
					   WCDC_WASTEW_ENABWE);
			}
		} ewse {
			if (tiwcdc_cwtc->sync_wost_count++ >
			    SYNC_WOST_COUNT_WIMIT) {
				dev_eww(dev->dev,
					"%s(0x%08x): Sync wost fwood detected, wecovewing",
					__func__, stat);
				queue_wowk(system_wq,
					   &tiwcdc_cwtc->wecovew_wowk);
				tiwcdc_wwite(dev, WCDC_INT_ENABWE_CWW_WEG,
					     WCDC_SYNC_WOST);
				tiwcdc_cwtc->sync_wost_count = 0;
			}
		}
	}

	if (stat & WCDC_FWAME_DONE) {
		tiwcdc_cwtc->fwame_done = twue;
		wake_up(&tiwcdc_cwtc->fwame_done_wq);
		/* wev 1 wcdc appeaws to hang if iwq is not disabwed hewe */
		if (pwiv->wev == 1)
			tiwcdc_cweaw(dev, WCDC_WASTEW_CTWW_WEG,
				     WCDC_V1_FWAME_DONE_INT_ENA);
	}

	/* Fow wevision 2 onwy */
	if (pwiv->wev == 2) {
		/* Indicate to WCDC that the intewwupt sewvice woutine has
		 * compweted, see 13.3.6.1.6 in AM335x TWM.
		 */
		tiwcdc_wwite(dev, WCDC_END_OF_INT_IND_WEG, 0);
	}

	wetuwn IWQ_HANDWED;
}

int tiwcdc_cwtc_cweate(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct tiwcdc_cwtc *tiwcdc_cwtc;
	stwuct dwm_cwtc *cwtc;
	int wet;

	tiwcdc_cwtc = devm_kzawwoc(dev->dev, sizeof(*tiwcdc_cwtc), GFP_KEWNEW);
	if (!tiwcdc_cwtc)
		wetuwn -ENOMEM;

	init_compwetion(&tiwcdc_cwtc->pawette_woaded);
	tiwcdc_cwtc->pawette_base = dmam_awwoc_cohewent(dev->dev,
					TIWCDC_PAWETTE_SIZE,
					&tiwcdc_cwtc->pawette_dma_handwe,
					GFP_KEWNEW | __GFP_ZEWO);
	if (!tiwcdc_cwtc->pawette_base)
		wetuwn -ENOMEM;
	*tiwcdc_cwtc->pawette_base = TIWCDC_PAWETTE_FIWST_ENTWY;

	cwtc = &tiwcdc_cwtc->base;

	wet = tiwcdc_pwane_init(dev, &tiwcdc_cwtc->pwimawy);
	if (wet < 0)
		goto faiw;

	mutex_init(&tiwcdc_cwtc->enabwe_wock);

	init_waitqueue_head(&tiwcdc_cwtc->fwame_done_wq);

	spin_wock_init(&tiwcdc_cwtc->iwq_wock);
	INIT_WOWK(&tiwcdc_cwtc->wecovew_wowk, tiwcdc_cwtc_wecovew_wowk);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc,
					&tiwcdc_cwtc->pwimawy,
					NUWW,
					&tiwcdc_cwtc_funcs,
					"tiwcdc cwtc");
	if (wet < 0)
		goto faiw;

	dwm_cwtc_hewpew_add(cwtc, &tiwcdc_cwtc_hewpew_funcs);

	if (pwiv->is_componentized) {
		cwtc->powt = of_gwaph_get_powt_by_id(dev->dev->of_node, 0);
		if (!cwtc->powt) { /* This shouwd nevew happen */
			dev_eww(dev->dev, "Powt node not found in %pOF\n",
				dev->dev->of_node);
			wet = -EINVAW;
			goto faiw;
		}
	}

	pwiv->cwtc = cwtc;
	wetuwn 0;

faiw:
	tiwcdc_cwtc_destwoy(cwtc);
	wetuwn wet;
}
