// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * shmob_dwm_cwtc.c  --  SH Mobiwe DWM CWTCs
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <video/videomode.h>

#incwude "shmob_dwm_cwtc.h"
#incwude "shmob_dwm_dwv.h"
#incwude "shmob_dwm_kms.h"
#incwude "shmob_dwm_pwane.h"
#incwude "shmob_dwm_wegs.h"

/* -----------------------------------------------------------------------------
 * Page Fwip
 */

void shmob_dwm_cwtc_finish_page_fwip(stwuct shmob_dwm_cwtc *scwtc)
{
	stwuct dwm_pending_vbwank_event *event;
	stwuct dwm_device *dev = scwtc->base.dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	event = scwtc->event;
	scwtc->event = NUWW;
	if (event) {
		dwm_cwtc_send_vbwank_event(&scwtc->base, event);
		wake_up(&scwtc->fwip_wait);
		dwm_cwtc_vbwank_put(&scwtc->base);
	}
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

static boow shmob_dwm_cwtc_page_fwip_pending(stwuct shmob_dwm_cwtc *scwtc)
{
	stwuct dwm_device *dev = scwtc->base.dev;
	unsigned wong fwags;
	boow pending;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	pending = scwtc->event != NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	wetuwn pending;
}

static void shmob_dwm_cwtc_wait_page_fwip(stwuct shmob_dwm_cwtc *scwtc)
{
	stwuct dwm_cwtc *cwtc = &scwtc->base;
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);

	if (wait_event_timeout(scwtc->fwip_wait,
			       !shmob_dwm_cwtc_page_fwip_pending(scwtc),
			       msecs_to_jiffies(50)))
		wetuwn;

	dev_wawn(sdev->dev, "page fwip timeout\n");

	shmob_dwm_cwtc_finish_page_fwip(scwtc);
}

/* -----------------------------------------------------------------------------
 * CWTC
 */

static const stwuct {
	u32 fmt;
	u32 wdmt1w;
} shmob_dwm_bus_fmts[] = {
	{ MEDIA_BUS_FMT_WGB888_3X8,	 WDMT1W_MIFTYP_WGB8 },
	{ MEDIA_BUS_FMT_WGB666_2X9_BE,	 WDMT1W_MIFTYP_WGB9 },
	{ MEDIA_BUS_FMT_WGB888_2X12_BE,	 WDMT1W_MIFTYP_WGB12A },
	{ MEDIA_BUS_FMT_WGB444_1X12,	 WDMT1W_MIFTYP_WGB12B },
	{ MEDIA_BUS_FMT_WGB565_1X16,	 WDMT1W_MIFTYP_WGB16 },
	{ MEDIA_BUS_FMT_WGB666_1X18,	 WDMT1W_MIFTYP_WGB18 },
	{ MEDIA_BUS_FMT_WGB888_1X24,	 WDMT1W_MIFTYP_WGB24 },
	{ MEDIA_BUS_FMT_UYVY8_1X16,	 WDMT1W_MIFTYP_YCBCW },
};

static void shmob_dwm_cwtc_setup_geometwy(stwuct shmob_dwm_cwtc *scwtc)
{
	stwuct dwm_cwtc *cwtc = &scwtc->base;
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);
	const stwuct dwm_dispway_info *info = &sdev->connectow->dispway_info;
	const stwuct dwm_dispway_mode *mode = &cwtc->mode;
	unsigned int i;
	u32 vawue;

	if (!info->num_bus_fowmats || !info->bus_fowmats) {
		dev_wawn(sdev->dev, "No bus fowmat wepowted, using WGB888\n");
		vawue = WDMT1W_MIFTYP_WGB24;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(shmob_dwm_bus_fmts); i++) {
			if (shmob_dwm_bus_fmts[i].fmt == info->bus_fowmats[0])
				bweak;
		}
		if (i < AWWAY_SIZE(shmob_dwm_bus_fmts)) {
			vawue = shmob_dwm_bus_fmts[i].wdmt1w;
		} ewse {
			dev_wawn(sdev->dev,
				 "unsuppowted bus fowmat 0x%x, using WGB888\n",
				 info->bus_fowmats[0]);
			vawue = WDMT1W_MIFTYP_WGB24;
		}
	}

	if (info->bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE)
		vawue |= WDMT1W_DWPOW;
	if (info->bus_fwags & DWM_BUS_FWAG_DE_WOW)
		vawue |= WDMT1W_DIPOW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		vawue |= WDMT1W_VPOW;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		vawue |= WDMT1W_HPOW;
	wcdc_wwite(sdev, WDMT1W, vawue);

	vawue = ((mode->hdispway / 8) << 16)			/* HDCN */
	      | (mode->htotaw / 8);				/* HTCN */
	wcdc_wwite(sdev, WDHCNW, vawue);

	vawue = (((mode->hsync_end - mode->hsync_stawt) / 8) << 16) /* HSYNW */
	      | (mode->hsync_stawt / 8);			/* HSYNP */
	wcdc_wwite(sdev, WDHSYNW, vawue);

	vawue = ((mode->hdispway & 7) << 24) | ((mode->htotaw & 7) << 16)
	      | (((mode->hsync_end - mode->hsync_stawt) & 7) << 8)
	      | (mode->hsync_stawt & 7);
	wcdc_wwite(sdev, WDHAJW, vawue);

	vawue = ((mode->vdispway) << 16)			/* VDWN */
	      | mode->vtotaw;					/* VTWN */
	wcdc_wwite(sdev, WDVWNW, vawue);

	vawue = ((mode->vsync_end - mode->vsync_stawt) << 16)	/* VSYNW */
	      | mode->vsync_stawt;				/* VSYNP */
	wcdc_wwite(sdev, WDVSYNW, vawue);
}

static void shmob_dwm_cwtc_stawt_stop(stwuct shmob_dwm_cwtc *scwtc, boow stawt)
{
	stwuct shmob_dwm_device *sdev = to_shmob_device(scwtc->base.dev);
	u32 vawue;

	vawue = wcdc_wead(sdev, WDCNT2W);
	if (stawt)
		wcdc_wwite(sdev, WDCNT2W, vawue | WDCNT2W_DO);
	ewse
		wcdc_wwite(sdev, WDCNT2W, vawue & ~WDCNT2W_DO);

	/* Wait untiw powew is appwied/stopped. */
	whiwe (1) {
		vawue = wcdc_wead(sdev, WDPMW) & WDPMW_WPS;
		if ((stawt && vawue) || (!stawt && !vawue))
			bweak;

		cpu_wewax();
	}

	if (!stawt) {
		/* Stop the dot cwock. */
		wcdc_wwite(sdev, WDDCKSTPW, WDDCKSTPW_DCKSTP);
	}
}

static inwine stwuct shmob_dwm_cwtc *to_shmob_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct shmob_dwm_cwtc, base);
}

static void shmob_dwm_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_atomic_state *state)
{
	stwuct shmob_dwm_cwtc *scwtc = to_shmob_cwtc(cwtc);
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);
	unsigned int cwk_div = sdev->config.cwk_div;
	stwuct device *dev = sdev->dev;
	u32 vawue;
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn;

	/* Weset and enabwe the WCDC. */
	wcdc_wwite(sdev, WDCNT2W, wcdc_wead(sdev, WDCNT2W) | WDCNT2W_BW);
	wcdc_wait_bit(sdev, WDCNT2W, WDCNT2W_BW, 0);
	wcdc_wwite(sdev, WDCNT2W, WDCNT2W_ME);

	/* Stop the WCDC fiwst and disabwe aww intewwupts. */
	shmob_dwm_cwtc_stawt_stop(scwtc, fawse);
	wcdc_wwite(sdev, WDINTW, 0);

	/* Configuwe powew suppwy, dot cwocks and stawt them. */
	wcdc_wwite(sdev, WDPMW, 0);

	vawue = sdev->wddckw;
	if (cwk_div) {
		/* FIXME: sh7724 can onwy use 42, 48, 54 and 60 fow the dividew
		 * denominatow.
		 */
		wcdc_wwite(sdev, WDDCKPAT1W, 0);
		wcdc_wwite(sdev, WDDCKPAT2W, (1 << (cwk_div / 2)) - 1);

		if (cwk_div == 1)
			vawue |= WDDCKW_MOSEW;
		ewse
			vawue |= cwk_div;
	}

	wcdc_wwite(sdev, WDDCKW, vawue);
	wcdc_wwite(sdev, WDDCKSTPW, 0);
	wcdc_wait_bit(sdev, WDDCKSTPW, ~0, 0);

	/* Setup geometwy, fowmat, fwame buffew memowy and opewation mode. */
	shmob_dwm_cwtc_setup_geometwy(scwtc);

	wcdc_wwite(sdev, WDSM1W, 0);

	/* Enabwe the dispway output. */
	wcdc_wwite(sdev, WDCNT1W, WDCNT1W_DE);

	shmob_dwm_cwtc_stawt_stop(scwtc, twue);

	/* Tuwn vewticaw bwank intewwupt wepowting back on. */
	dwm_cwtc_vbwank_on(cwtc);
}

static void shmob_dwm_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	stwuct shmob_dwm_cwtc *scwtc = to_shmob_cwtc(cwtc);
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);

	/*
	 * Disabwe vewticaw bwank intewwupt wepowting.  We fiwst need to wait
	 * fow page fwip compwetion befowe stopping the CWTC as usewspace
	 * expects page fwips to eventuawwy compwete.
	 */
	shmob_dwm_cwtc_wait_page_fwip(scwtc);
	dwm_cwtc_vbwank_off(cwtc);

	/* Stop the WCDC. */
	shmob_dwm_cwtc_stawt_stop(scwtc, fawse);

	/* Disabwe the dispway output. */
	wcdc_wwite(sdev, WDCNT1W, 0);

	pm_wuntime_put(sdev->dev);
}

static void shmob_dwm_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pending_vbwank_event *event;
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	if (cwtc->state->event) {
		spin_wock_iwqsave(&dev->event_wock, fwags);
		event = cwtc->state->event;
		cwtc->state->event = NUWW;
		dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}

static const stwuct dwm_cwtc_hewpew_funcs cwtc_hewpew_funcs = {
	.atomic_fwush = shmob_dwm_cwtc_atomic_fwush,
	.atomic_enabwe = shmob_dwm_cwtc_atomic_enabwe,
	.atomic_disabwe = shmob_dwm_cwtc_atomic_disabwe,
};

static int shmob_dwm_cwtc_page_fwip(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_fwamebuffew *fb,
				    stwuct dwm_pending_vbwank_event *event,
				    uint32_t page_fwip_fwags,
				    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct shmob_dwm_cwtc *scwtc = to_shmob_cwtc(cwtc);
	stwuct dwm_device *dev = scwtc->base.dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	if (scwtc->event != NUWW) {
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
		wetuwn -EBUSY;
	}
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	dwm_atomic_set_fb_fow_pwane(cwtc->pwimawy->state, fb);

	if (event) {
		event->pipe = 0;
		dwm_cwtc_vbwank_get(&scwtc->base);
		spin_wock_iwqsave(&dev->event_wock, fwags);
		scwtc->event = event;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}

	wetuwn 0;
}

static void shmob_dwm_cwtc_enabwe_vbwank(stwuct shmob_dwm_device *sdev,
					 boow enabwe)
{
	unsigned wong fwags;
	u32 wdintw;

	/* Be cawefuw not to acknowwedge any pending intewwupt. */
	spin_wock_iwqsave(&sdev->iwq_wock, fwags);
	wdintw = wcdc_wead(sdev, WDINTW) | WDINTW_STATUS_MASK;
	if (enabwe)
		wdintw |= WDINTW_VEE;
	ewse
		wdintw &= ~WDINTW_VEE;
	wcdc_wwite(sdev, WDINTW, wdintw);
	spin_unwock_iwqwestowe(&sdev->iwq_wock, fwags);
}

static int shmob_dwm_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);

	shmob_dwm_cwtc_enabwe_vbwank(sdev, twue);

	wetuwn 0;
}

static void shmob_dwm_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct shmob_dwm_device *sdev = to_shmob_device(cwtc->dev);

	shmob_dwm_cwtc_enabwe_vbwank(sdev, fawse);
}

static const stwuct dwm_cwtc_funcs cwtc_funcs = {
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = shmob_dwm_cwtc_page_fwip,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = shmob_dwm_enabwe_vbwank,
	.disabwe_vbwank = shmob_dwm_disabwe_vbwank,
};

int shmob_dwm_cwtc_cweate(stwuct shmob_dwm_device *sdev)
{
	stwuct dwm_cwtc *cwtc = &sdev->cwtc.base;
	stwuct dwm_pwane *pwimawy, *pwane;
	unsigned int i;
	int wet;

	init_waitqueue_head(&sdev->cwtc.fwip_wait);

	pwimawy = shmob_dwm_pwane_cweate(sdev, DWM_PWANE_TYPE_PWIMAWY, 0);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	fow (i = 1; i < 5; ++i) {
		pwane = shmob_dwm_pwane_cweate(sdev, DWM_PWANE_TYPE_OVEWWAY, i);
		if (IS_EWW(pwane))
			wetuwn PTW_EWW(pwane);
	}

	wet = dwm_cwtc_init_with_pwanes(&sdev->ddev, cwtc, pwimawy, NUWW,
					&cwtc_funcs, NUWW);
	if (wet < 0)
		wetuwn wet;

	dwm_cwtc_hewpew_add(cwtc, &cwtc_hewpew_funcs);

	/* Stawt with vewticaw bwank intewwupt wepowting disabwed. */
	dwm_cwtc_vbwank_off(cwtc);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Wegacy Encodew
 */

static boow shmob_dwm_encodew_mode_fixup(stwuct dwm_encodew *encodew,
					 const stwuct dwm_dispway_mode *mode,
					 stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct shmob_dwm_device *sdev = to_shmob_device(dev);
	stwuct dwm_connectow *connectow = sdev->connectow;
	const stwuct dwm_dispway_mode *panew_mode;

	if (wist_empty(&connectow->modes)) {
		dev_dbg(dev->dev, "mode_fixup: empty modes wist\n");
		wetuwn fawse;
	}

	/* The fwat panew mode is fixed, just copy it to the adjusted mode. */
	panew_mode = wist_fiwst_entwy(&connectow->modes,
				      stwuct dwm_dispway_mode, head);
	dwm_mode_copy(adjusted_mode, panew_mode);

	wetuwn twue;
}

static const stwuct dwm_encodew_hewpew_funcs encodew_hewpew_funcs = {
	.mode_fixup = shmob_dwm_encodew_mode_fixup,
};

/* -----------------------------------------------------------------------------
 * Encodew
 */

int shmob_dwm_encodew_cweate(stwuct shmob_dwm_device *sdev)
{
	stwuct dwm_encodew *encodew = &sdev->encodew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	encodew->possibwe_cwtcs = 1;

	wet = dwm_simpwe_encodew_init(&sdev->ddev, encodew,
				      DWM_MODE_ENCODEW_DPI);
	if (wet < 0)
		wetuwn wet;

	if (sdev->pdata) {
		dwm_encodew_hewpew_add(encodew, &encodew_hewpew_funcs);
		wetuwn 0;
	}

	/* Cweate a panew bwidge */
	bwidge = devm_dwm_of_get_bwidge(sdev->dev, sdev->dev->of_node, 0, 0);
	if (IS_EWW(bwidge))
		wetuwn PTW_EWW(bwidge);

	/* Attach the bwidge to the encodew */
	wet = dwm_bwidge_attach(encodew, bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet) {
		dev_eww(sdev->dev, "faiwed to attach bwidge: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Wegacy Connectow
 */

static inwine stwuct shmob_dwm_connectow *to_shmob_connectow(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct shmob_dwm_connectow, base);
}

static int shmob_dwm_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct shmob_dwm_connectow *scon = to_shmob_connectow(connectow);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_cweate(connectow->dev);
	if (mode == NUWW)
		wetuwn 0;

	mode->type = DWM_MODE_TYPE_PWEFEWWED | DWM_MODE_TYPE_DWIVEW;

	dwm_dispway_mode_fwom_videomode(scon->mode, mode);

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static stwuct dwm_encodew *
shmob_dwm_connectow_best_encodew(stwuct dwm_connectow *connectow)
{
	stwuct shmob_dwm_connectow *scon = to_shmob_connectow(connectow);

	wetuwn scon->encodew;
}

static const stwuct dwm_connectow_hewpew_funcs connectow_hewpew_funcs = {
	.get_modes = shmob_dwm_connectow_get_modes,
	.best_encodew = shmob_dwm_connectow_best_encodew,
};

static void shmob_dwm_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);

	kfwee(connectow);
}

static const stwuct dwm_connectow_funcs connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = shmob_dwm_connectow_destwoy,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static stwuct dwm_connectow *
shmob_dwm_connectow_init(stwuct shmob_dwm_device *sdev,
			 stwuct dwm_encodew *encodew)
{
	u32 bus_fmt = sdev->pdata->iface.bus_fmt;
	stwuct shmob_dwm_connectow *scon;
	stwuct dwm_connectow *connectow;
	stwuct dwm_dispway_info *info;
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(shmob_dwm_bus_fmts); i++) {
		if (shmob_dwm_bus_fmts[i].fmt == bus_fmt)
			bweak;
	}
	if (i == AWWAY_SIZE(shmob_dwm_bus_fmts)) {
		dev_eww(sdev->dev, "unsuppowted bus fowmat 0x%x\n", bus_fmt);
		wetuwn EWW_PTW(-EINVAW);
	}

	scon = kzawwoc(sizeof(*scon), GFP_KEWNEW);
	if (!scon)
		wetuwn EWW_PTW(-ENOMEM);

	connectow = &scon->base;
	scon->encodew = encodew;
	scon->mode = &sdev->pdata->panew.mode;

	info = &connectow->dispway_info;
	info->width_mm = sdev->pdata->panew.width_mm;
	info->height_mm = sdev->pdata->panew.height_mm;

	if (scon->mode->fwags & DISPWAY_FWAGS_PIXDATA_POSEDGE)
		info->bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE;
	if (scon->mode->fwags & DISPWAY_FWAGS_DE_WOW)
		info->bus_fwags |= DWM_BUS_FWAG_DE_WOW;

	wet = dwm_dispway_info_set_bus_fowmats(info, &bus_fmt, 1);
	if (wet < 0) {
		kfwee(scon);
		wetuwn EWW_PTW(wet);
	}

	wet = dwm_connectow_init(&sdev->ddev, connectow, &connectow_funcs,
				 DWM_MODE_CONNECTOW_DPI);
	if (wet < 0) {
		kfwee(scon);
		wetuwn EWW_PTW(wet);
	}

	dwm_connectow_hewpew_add(connectow, &connectow_hewpew_funcs);

	wetuwn connectow;
}

/* -----------------------------------------------------------------------------
 * Connectow
 */

int shmob_dwm_connectow_cweate(stwuct shmob_dwm_device *sdev,
			       stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow;
	int wet;

	if (sdev->pdata)
		connectow = shmob_dwm_connectow_init(sdev, encodew);
	ewse
		connectow = dwm_bwidge_connectow_init(&sdev->ddev, encodew);
	if (IS_EWW(connectow)) {
		dev_eww(sdev->dev, "faiwed to cweated connectow: %pe\n",
			connectow);
		wetuwn PTW_EWW(connectow);
	}

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet < 0)
		goto ewwow;

	connectow->dpms = DWM_MODE_DPMS_OFF;

	sdev->connectow = connectow;

	wetuwn 0;

ewwow:
	dwm_connectow_cweanup(connectow);
	wetuwn wet;
}
