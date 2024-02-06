// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* exynos_dwm_vidi.c
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co.Wtd
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 */

#incwude <winux/component.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_fb.h"
#incwude "exynos_dwm_pwane.h"
#incwude "exynos_dwm_vidi.h"

/* VIDI uses fixed wefwesh wate of 50Hz */
#define VIDI_WEFWESH_TIME (1000 / 50)

/* vidi has totawwy thwee viwtuaw windows. */
#define WINDOWS_NW		3

#define ctx_fwom_connectow(c)	containew_of(c, stwuct vidi_context, \
					connectow)

stwuct vidi_context {
	stwuct dwm_encodew		encodew;
	stwuct dwm_device		*dwm_dev;
	stwuct device			*dev;
	stwuct exynos_dwm_cwtc		*cwtc;
	stwuct dwm_connectow		connectow;
	stwuct exynos_dwm_pwane		pwanes[WINDOWS_NW];
	stwuct edid			*waw_edid;
	unsigned int			cwkdiv;
	unsigned int			connected;
	boow				suspended;
	stwuct timew_wist		timew;
	stwuct mutex			wock;
};

static inwine stwuct vidi_context *encodew_to_vidi(stwuct dwm_encodew *e)
{
	wetuwn containew_of(e, stwuct vidi_context, encodew);
}

static const chaw fake_edid_info[] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x4c, 0x2d, 0x05, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x12, 0x01, 0x03, 0x80, 0x10, 0x09, 0x78,
	0x0a, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26, 0x0f, 0x50, 0x54, 0xbd,
	0xee, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x66, 0x21, 0x50, 0xb0, 0x51, 0x00,
	0x1b, 0x30, 0x40, 0x70, 0x36, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e,
	0x01, 0x1d, 0x00, 0x72, 0x51, 0xd0, 0x1e, 0x20, 0x6e, 0x28, 0x55, 0x00,
	0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x18,
	0x4b, 0x1a, 0x44, 0x17, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x00, 0x00, 0x00, 0xfc, 0x00, 0x53, 0x41, 0x4d, 0x53, 0x55, 0x4e, 0x47,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xbc, 0x02, 0x03, 0x1e, 0xf1,
	0x46, 0x84, 0x05, 0x03, 0x10, 0x20, 0x22, 0x23, 0x09, 0x07, 0x07, 0x83,
	0x01, 0x00, 0x00, 0xe2, 0x00, 0x0f, 0x67, 0x03, 0x0c, 0x00, 0x10, 0x00,
	0xb8, 0x2d, 0x01, 0x1d, 0x80, 0x18, 0x71, 0x1c, 0x16, 0x20, 0x58, 0x2c,
	0x25, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x9e, 0x8c, 0x0a, 0xd0, 0x8a,
	0x20, 0xe0, 0x2d, 0x10, 0x10, 0x3e, 0x96, 0x00, 0xa0, 0x5a, 0x00, 0x00,
	0x00, 0x18, 0x02, 0x3a, 0x80, 0x18, 0x71, 0x38, 0x2d, 0x40, 0x58, 0x2c,
	0x45, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x06
};

static const uint32_t fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_NV12,
};

static const enum dwm_pwane_type vidi_win_types[WINDOWS_NW] = {
	DWM_PWANE_TYPE_PWIMAWY,
	DWM_PWANE_TYPE_OVEWWAY,
	DWM_PWANE_TYPE_CUWSOW,
};

static int vidi_enabwe_vbwank(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct vidi_context *ctx = cwtc->ctx;

	if (ctx->suspended)
		wetuwn -EPEWM;

	mod_timew(&ctx->timew,
		jiffies + msecs_to_jiffies(VIDI_WEFWESH_TIME) - 1);

	wetuwn 0;
}

static void vidi_disabwe_vbwank(stwuct exynos_dwm_cwtc *cwtc)
{
}

static void vidi_update_pwane(stwuct exynos_dwm_cwtc *cwtc,
			      stwuct exynos_dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->base.state;
	stwuct vidi_context *ctx = cwtc->ctx;
	dma_addw_t addw;

	if (ctx->suspended)
		wetuwn;

	addw = exynos_dwm_fb_dma_addw(state->fb, 0);
	DWM_DEV_DEBUG_KMS(ctx->dev, "dma_addw = %pad\n", &addw);
}

static void vidi_atomic_enabwe(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct vidi_context *ctx = cwtc->ctx;

	mutex_wock(&ctx->wock);

	ctx->suspended = fawse;

	mutex_unwock(&ctx->wock);

	dwm_cwtc_vbwank_on(&cwtc->base);
}

static void vidi_atomic_disabwe(stwuct exynos_dwm_cwtc *cwtc)
{
	stwuct vidi_context *ctx = cwtc->ctx;

	dwm_cwtc_vbwank_off(&cwtc->base);

	mutex_wock(&ctx->wock);

	ctx->suspended = twue;

	mutex_unwock(&ctx->wock);
}

static const stwuct exynos_dwm_cwtc_ops vidi_cwtc_ops = {
	.atomic_enabwe = vidi_atomic_enabwe,
	.atomic_disabwe = vidi_atomic_disabwe,
	.enabwe_vbwank = vidi_enabwe_vbwank,
	.disabwe_vbwank = vidi_disabwe_vbwank,
	.update_pwane = vidi_update_pwane,
	.atomic_fwush = exynos_cwtc_handwe_event,
};

static void vidi_fake_vbwank_timew(stwuct timew_wist *t)
{
	stwuct vidi_context *ctx = fwom_timew(ctx, t, timew);

	if (dwm_cwtc_handwe_vbwank(&ctx->cwtc->base))
		mod_timew(&ctx->timew,
			jiffies + msecs_to_jiffies(VIDI_WEFWESH_TIME) - 1);
}

static ssize_t vidi_show_connection(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vidi_context *ctx = dev_get_dwvdata(dev);
	int wc;

	mutex_wock(&ctx->wock);

	wc = spwintf(buf, "%d\n", ctx->connected);

	mutex_unwock(&ctx->wock);

	wetuwn wc;
}

static ssize_t vidi_stowe_connection(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct vidi_context *ctx = dev_get_dwvdata(dev);
	int wet;

	wet = kstwtoint(buf, 0, &ctx->connected);
	if (wet)
		wetuwn wet;

	if (ctx->connected > 1)
		wetuwn -EINVAW;

	/* use fake edid data fow test. */
	if (!ctx->waw_edid)
		ctx->waw_edid = (stwuct edid *)fake_edid_info;

	/* if waw_edid isn't same as fake data then it can't be tested. */
	if (ctx->waw_edid != (stwuct edid *)fake_edid_info) {
		DWM_DEV_DEBUG_KMS(dev, "edid data is not fake data.\n");
		wetuwn -EINVAW;
	}

	DWM_DEV_DEBUG_KMS(dev, "wequested connection.\n");

	dwm_hewpew_hpd_iwq_event(ctx->dwm_dev);

	wetuwn wen;
}

static DEVICE_ATTW(connection, 0644, vidi_show_connection,
			vidi_stowe_connection);

static stwuct attwibute *vidi_attws[] = {
	&dev_attw_connection.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vidi);

int vidi_connection_ioctw(stwuct dwm_device *dwm_dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vidi_context *ctx = dev_get_dwvdata(dwm_dev->dev);
	stwuct dwm_exynos_vidi_connection *vidi = data;

	if (!vidi) {
		DWM_DEV_DEBUG_KMS(ctx->dev,
				  "usew data fow vidi is nuww.\n");
		wetuwn -EINVAW;
	}

	if (vidi->connection > 1) {
		DWM_DEV_DEBUG_KMS(ctx->dev,
				  "connection shouwd be 0 ow 1.\n");
		wetuwn -EINVAW;
	}

	if (ctx->connected == vidi->connection) {
		DWM_DEV_DEBUG_KMS(ctx->dev,
				  "same connection wequest.\n");
		wetuwn -EINVAW;
	}

	if (vidi->connection) {
		stwuct edid *waw_edid;

		waw_edid = (stwuct edid *)(unsigned wong)vidi->edid;
		if (!dwm_edid_is_vawid(waw_edid)) {
			DWM_DEV_DEBUG_KMS(ctx->dev,
					  "edid data is invawid.\n");
			wetuwn -EINVAW;
		}
		ctx->waw_edid = dwm_edid_dupwicate(waw_edid);
		if (!ctx->waw_edid) {
			DWM_DEV_DEBUG_KMS(ctx->dev,
					  "faiwed to awwocate waw_edid.\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		/*
		 * with connection = 0, fwee waw_edid
		 * onwy if waw edid data isn't same as fake data.
		 */
		if (ctx->waw_edid && ctx->waw_edid !=
				(stwuct edid *)fake_edid_info) {
			kfwee(ctx->waw_edid);
			ctx->waw_edid = NUWW;
		}
	}

	ctx->connected = vidi->connection;
	dwm_hewpew_hpd_iwq_event(ctx->dwm_dev);

	wetuwn 0;
}

static enum dwm_connectow_status vidi_detect(stwuct dwm_connectow *connectow,
			boow fowce)
{
	stwuct vidi_context *ctx = ctx_fwom_connectow(connectow);

	/*
	 * connection wequest wouwd come fwom usew side
	 * to do hotpwug thwough specific ioctw.
	 */
	wetuwn ctx->connected ? connectow_status_connected :
			connectow_status_disconnected;
}

static void vidi_connectow_destwoy(stwuct dwm_connectow *connectow)
{
}

static const stwuct dwm_connectow_funcs vidi_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = vidi_detect,
	.destwoy = vidi_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int vidi_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct vidi_context *ctx = ctx_fwom_connectow(connectow);
	stwuct edid *edid;
	int edid_wen;

	/*
	 * the edid data comes fwom usew side and it wouwd be set
	 * to ctx->waw_edid thwough specific ioctw.
	 */
	if (!ctx->waw_edid) {
		DWM_DEV_DEBUG_KMS(ctx->dev, "waw_edid is nuww.\n");
		wetuwn -EFAUWT;
	}

	edid_wen = (1 + ctx->waw_edid->extensions) * EDID_WENGTH;
	edid = kmemdup(ctx->waw_edid, edid_wen, GFP_KEWNEW);
	if (!edid) {
		DWM_DEV_DEBUG_KMS(ctx->dev, "faiwed to awwocate edid\n");
		wetuwn -ENOMEM;
	}

	dwm_connectow_update_edid_pwopewty(connectow, edid);

	wetuwn dwm_add_edid_modes(connectow, edid);
}

static const stwuct dwm_connectow_hewpew_funcs vidi_connectow_hewpew_funcs = {
	.get_modes = vidi_get_modes,
};

static int vidi_cweate_connectow(stwuct dwm_encodew *encodew)
{
	stwuct vidi_context *ctx = encodew_to_vidi(encodew);
	stwuct dwm_connectow *connectow = &ctx->connectow;
	int wet;

	connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	wet = dwm_connectow_init(ctx->dwm_dev, connectow,
			&vidi_connectow_funcs, DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet) {
		DWM_DEV_EWWOW(ctx->dev,
			      "Faiwed to initiawize connectow with dwm\n");
		wetuwn wet;
	}

	dwm_connectow_hewpew_add(connectow, &vidi_connectow_hewpew_funcs);
	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn 0;
}

static void exynos_vidi_mode_set(stwuct dwm_encodew *encodew,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode)
{
}

static void exynos_vidi_enabwe(stwuct dwm_encodew *encodew)
{
}

static void exynos_vidi_disabwe(stwuct dwm_encodew *encodew)
{
}

static const stwuct dwm_encodew_hewpew_funcs exynos_vidi_encodew_hewpew_funcs = {
	.mode_set = exynos_vidi_mode_set,
	.enabwe = exynos_vidi_enabwe,
	.disabwe = exynos_vidi_disabwe,
};

static int vidi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct vidi_context *ctx = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_encodew *encodew = &ctx->encodew;
	stwuct exynos_dwm_pwane *exynos_pwane;
	stwuct exynos_dwm_pwane_config pwane_config = { 0 };
	unsigned int i;
	int wet;

	ctx->dwm_dev = dwm_dev;

	pwane_config.pixew_fowmats = fowmats;
	pwane_config.num_pixew_fowmats = AWWAY_SIZE(fowmats);

	fow (i = 0; i < WINDOWS_NW; i++) {
		pwane_config.zpos = i;
		pwane_config.type = vidi_win_types[i];

		wet = exynos_pwane_init(dwm_dev, &ctx->pwanes[i], i,
					&pwane_config);
		if (wet)
			wetuwn wet;
	}

	exynos_pwane = &ctx->pwanes[DEFAUWT_WIN];
	ctx->cwtc = exynos_dwm_cwtc_cweate(dwm_dev, &exynos_pwane->base,
			EXYNOS_DISPWAY_TYPE_VIDI, &vidi_cwtc_ops, ctx);
	if (IS_EWW(ctx->cwtc)) {
		DWM_DEV_EWWOW(dev, "faiwed to cweate cwtc.\n");
		wetuwn PTW_EWW(ctx->cwtc);
	}

	dwm_simpwe_encodew_init(dwm_dev, encodew, DWM_MODE_ENCODEW_TMDS);

	dwm_encodew_hewpew_add(encodew, &exynos_vidi_encodew_hewpew_funcs);

	wet = exynos_dwm_set_possibwe_cwtcs(encodew, EXYNOS_DISPWAY_TYPE_VIDI);
	if (wet < 0)
		wetuwn wet;

	wet = vidi_cweate_connectow(encodew);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to cweate connectow wet = %d\n",
			      wet);
		dwm_encodew_cweanup(encodew);
		wetuwn wet;
	}

	wetuwn 0;
}


static void vidi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct vidi_context *ctx = dev_get_dwvdata(dev);

	dew_timew_sync(&ctx->timew);
}

static const stwuct component_ops vidi_component_ops = {
	.bind	= vidi_bind,
	.unbind = vidi_unbind,
};

static int vidi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vidi_context *ctx;
	stwuct device *dev = &pdev->dev;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;

	timew_setup(&ctx->timew, vidi_fake_vbwank_timew, 0);

	mutex_init(&ctx->wock);

	pwatfowm_set_dwvdata(pdev, ctx);

	wetuwn component_add(dev, &vidi_component_ops);
}

static void vidi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vidi_context *ctx = pwatfowm_get_dwvdata(pdev);

	if (ctx->waw_edid != (stwuct edid *)fake_edid_info) {
		kfwee(ctx->waw_edid);
		ctx->waw_edid = NUWW;
	}

	component_dew(&pdev->dev, &vidi_component_ops);
}

stwuct pwatfowm_dwivew vidi_dwivew = {
	.pwobe		= vidi_pwobe,
	.wemove_new	= vidi_wemove,
	.dwivew		= {
		.name	= "exynos-dwm-vidi",
		.ownew	= THIS_MODUWE,
		.dev_gwoups = vidi_gwoups,
	},
};
