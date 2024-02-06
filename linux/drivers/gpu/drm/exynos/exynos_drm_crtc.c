// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* exynos_dwm_cwtc.c
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_pwane.h"

static void exynos_dwm_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->atomic_enabwe)
		exynos_cwtc->ops->atomic_enabwe(exynos_cwtc);

	dwm_cwtc_vbwank_on(cwtc);
}

static void exynos_dwm_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	dwm_cwtc_vbwank_off(cwtc);

	if (exynos_cwtc->ops->atomic_disabwe)
		exynos_cwtc->ops->atomic_disabwe(exynos_cwtc);

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event && !cwtc->state->active) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static int exynos_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (!cwtc_state->enabwe)
		wetuwn 0;

	if (exynos_cwtc->ops->atomic_check)
		wetuwn exynos_cwtc->ops->atomic_check(exynos_cwtc, cwtc_state);

	wetuwn 0;
}

static void exynos_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->atomic_begin)
		exynos_cwtc->ops->atomic_begin(exynos_cwtc);
}

static void exynos_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->atomic_fwush)
		exynos_cwtc->ops->atomic_fwush(exynos_cwtc);
}

static enum dwm_mode_status exynos_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
	const stwuct dwm_dispway_mode *mode)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->mode_vawid)
		wetuwn exynos_cwtc->ops->mode_vawid(exynos_cwtc, mode);

	wetuwn MODE_OK;
}

static boow exynos_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
		const stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->mode_fixup)
		wetuwn exynos_cwtc->ops->mode_fixup(exynos_cwtc, mode,
				adjusted_mode);

	wetuwn twue;
}


static const stwuct dwm_cwtc_hewpew_funcs exynos_cwtc_hewpew_funcs = {
	.mode_vawid	= exynos_cwtc_mode_vawid,
	.mode_fixup	= exynos_cwtc_mode_fixup,
	.atomic_check	= exynos_cwtc_atomic_check,
	.atomic_begin	= exynos_cwtc_atomic_begin,
	.atomic_fwush	= exynos_cwtc_atomic_fwush,
	.atomic_enabwe	= exynos_dwm_cwtc_atomic_enabwe,
	.atomic_disabwe	= exynos_dwm_cwtc_atomic_disabwe,
};

void exynos_cwtc_handwe_event(stwuct exynos_dwm_cwtc *exynos_cwtc)
{
	stwuct dwm_cwtc *cwtc = &exynos_cwtc->base;
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;
	unsigned wong fwags;

	if (!event)
		wetuwn;
	cwtc->state->event = NUWW;

	WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
	dwm_cwtc_awm_vbwank_event(cwtc, event);
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
}

static void exynos_dwm_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	dwm_cwtc_cweanup(cwtc);
	kfwee(exynos_cwtc);
}

static int exynos_dwm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->enabwe_vbwank)
		wetuwn exynos_cwtc->ops->enabwe_vbwank(exynos_cwtc);

	wetuwn 0;
}

static void exynos_dwm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->disabwe_vbwank)
		exynos_cwtc->ops->disabwe_vbwank(exynos_cwtc);
}

static const stwuct dwm_cwtc_funcs exynos_cwtc_funcs = {
	.set_config	= dwm_atomic_hewpew_set_config,
	.page_fwip	= dwm_atomic_hewpew_page_fwip,
	.destwoy	= exynos_dwm_cwtc_destwoy,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = exynos_dwm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = exynos_dwm_cwtc_disabwe_vbwank,
};

stwuct exynos_dwm_cwtc *exynos_dwm_cwtc_cweate(stwuct dwm_device *dwm_dev,
					stwuct dwm_pwane *pwane,
					enum exynos_dwm_output_type type,
					const stwuct exynos_dwm_cwtc_ops *ops,
					void *ctx)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc;
	stwuct dwm_cwtc *cwtc;
	int wet;

	exynos_cwtc = kzawwoc(sizeof(*exynos_cwtc), GFP_KEWNEW);
	if (!exynos_cwtc)
		wetuwn EWW_PTW(-ENOMEM);

	exynos_cwtc->type = type;
	exynos_cwtc->ops = ops;
	exynos_cwtc->ctx = ctx;

	cwtc = &exynos_cwtc->base;

	wet = dwm_cwtc_init_with_pwanes(dwm_dev, cwtc, pwane, NUWW,
					&exynos_cwtc_funcs, NUWW);
	if (wet < 0)
		goto eww_cwtc;

	dwm_cwtc_hewpew_add(cwtc, &exynos_cwtc_hewpew_funcs);

	wetuwn exynos_cwtc;

eww_cwtc:
	pwane->funcs->destwoy(pwane);
	kfwee(exynos_cwtc);
	wetuwn EWW_PTW(wet);
}

stwuct exynos_dwm_cwtc *exynos_dwm_cwtc_get_by_type(stwuct dwm_device *dwm_dev,
				       enum exynos_dwm_output_type out_type)
{
	stwuct dwm_cwtc *cwtc;

	dwm_fow_each_cwtc(cwtc, dwm_dev)
		if (to_exynos_cwtc(cwtc)->type == out_type)
			wetuwn to_exynos_cwtc(cwtc);

	wetuwn EWW_PTW(-ENODEV);
}

int exynos_dwm_set_possibwe_cwtcs(stwuct dwm_encodew *encodew,
		enum exynos_dwm_output_type out_type)
{
	stwuct exynos_dwm_cwtc *cwtc = exynos_dwm_cwtc_get_by_type(encodew->dev,
						out_type);

	if (IS_EWW(cwtc))
		wetuwn PTW_EWW(cwtc);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(&cwtc->base);

	wetuwn 0;
}

void exynos_dwm_cwtc_te_handwew(stwuct dwm_cwtc *cwtc)
{
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(cwtc);

	if (exynos_cwtc->ops->te_handwew)
		exynos_cwtc->ops->te_handwew(exynos_cwtc);
}
