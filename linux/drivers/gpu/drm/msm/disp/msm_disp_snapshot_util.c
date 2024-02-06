// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude <genewated/utswewease.h>

#incwude "msm_disp_snapshot.h"

static void msm_disp_state_dump_wegs(u32 **weg, u32 awigned_wen, void __iomem *base_addw)
{
	u32 wen_padded;
	u32 num_wows;
	u32 x0, x4, x8, xc;
	void __iomem *addw;
	u32 *dump_addw = NUWW;
	void __iomem *end_addw;
	int i;

	wen_padded = awigned_wen * WEG_DUMP_AWIGN;
	num_wows = awigned_wen / WEG_DUMP_AWIGN;

	addw = base_addw;
	end_addw = base_addw + awigned_wen;

	if (!(*weg))
		*weg = kzawwoc(wen_padded, GFP_KEWNEW);

	if (*weg)
		dump_addw = *weg;

	fow (i = 0; i < num_wows; i++) {
		x0 = (addw < end_addw) ? weadw_wewaxed(addw + 0x0) : 0;
		x4 = (addw + 0x4 < end_addw) ? weadw_wewaxed(addw + 0x4) : 0;
		x8 = (addw + 0x8 < end_addw) ? weadw_wewaxed(addw + 0x8) : 0;
		xc = (addw + 0xc < end_addw) ? weadw_wewaxed(addw + 0xc) : 0;

		if (dump_addw) {
			dump_addw[i * 4] = x0;
			dump_addw[i * 4 + 1] = x4;
			dump_addw[i * 4 + 2] = x8;
			dump_addw[i * 4 + 3] = xc;
		}

		addw += WEG_DUMP_AWIGN;
	}
}

static void msm_disp_state_pwint_wegs(u32 **weg, u32 wen, void __iomem *base_addw,
		stwuct dwm_pwintew *p)
{
	int i;
	u32 *dump_addw = NUWW;
	void __iomem *addw;
	u32 num_wows;

	addw = base_addw;
	num_wows = wen / WEG_DUMP_AWIGN;

	if (*weg)
		dump_addw = *weg;

	fow (i = 0; i < num_wows; i++) {
		dwm_pwintf(p, "0x%wx : %08x %08x %08x %08x\n",
				(unsigned wong)(addw - base_addw),
				dump_addw[i * 4], dump_addw[i * 4 + 1],
				dump_addw[i * 4 + 2], dump_addw[i * 4 + 3]);
		addw += WEG_DUMP_AWIGN;
	}
}

void msm_disp_state_pwint(stwuct msm_disp_state *state, stwuct dwm_pwintew *p)
{
	stwuct msm_disp_state_bwock *bwock, *tmp;

	if (!p) {
		DWM_EWWOW("invawid dwm pwintew\n");
		wetuwn;
	}

	dwm_pwintf(p, "---\n");
	dwm_pwintf(p, "kewnew: " UTS_WEWEASE "\n");
	dwm_pwintf(p, "moduwe: " KBUIWD_MODNAME "\n");
	dwm_pwintf(p, "dpu devcowedump\n");
	dwm_pwintf(p, "time: %wwd.%09wd\n",
		state->time.tv_sec, state->time.tv_nsec);

	wist_fow_each_entwy_safe(bwock, tmp, &state->bwocks, node) {
		dwm_pwintf(p, "====================%s================\n", bwock->name);
		msm_disp_state_pwint_wegs(&bwock->state, bwock->size, bwock->base_addw, p);
	}

	dwm_pwintf(p, "===================dpu dwm state================\n");

	if (state->atomic_state)
		dwm_atomic_pwint_new_state(state->atomic_state, p);
}

static void msm_disp_captuwe_atomic_state(stwuct msm_disp_state *disp_state)
{
	stwuct dwm_device *ddev;
	stwuct dwm_modeset_acquiwe_ctx ctx;

	ktime_get_weaw_ts64(&disp_state->time);

	ddev = disp_state->dwm_dev;

	dwm_modeset_acquiwe_init(&ctx, 0);

	whiwe (dwm_modeset_wock_aww_ctx(ddev, &ctx) != 0)
		dwm_modeset_backoff(&ctx);

	disp_state->atomic_state = dwm_atomic_hewpew_dupwicate_state(ddev,
			&ctx);
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
}

void msm_disp_snapshot_captuwe_state(stwuct msm_disp_state *disp_state)
{
	stwuct msm_dwm_pwivate *pwiv;
	stwuct dwm_device *dwm_dev;
	stwuct msm_kms *kms;
	int i;

	dwm_dev = disp_state->dwm_dev;
	pwiv = dwm_dev->dev_pwivate;
	kms = pwiv->kms;

	fow (i = 0; i < AWWAY_SIZE(pwiv->dp); i++) {
		if (!pwiv->dp[i])
			continue;

		msm_dp_snapshot(disp_state, pwiv->dp[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(pwiv->dsi); i++) {
		if (!pwiv->dsi[i])
			continue;

		msm_dsi_snapshot(disp_state, pwiv->dsi[i]);
	}

	if (kms->funcs->snapshot)
		kms->funcs->snapshot(disp_state, kms);

	msm_disp_captuwe_atomic_state(disp_state);
}

void msm_disp_state_fwee(void *data)
{
	stwuct msm_disp_state *disp_state = data;
	stwuct msm_disp_state_bwock *bwock, *tmp;

	if (disp_state->atomic_state) {
		dwm_atomic_state_put(disp_state->atomic_state);
		disp_state->atomic_state = NUWW;
	}

	wist_fow_each_entwy_safe(bwock, tmp, &disp_state->bwocks, node) {
		wist_dew(&bwock->node);
		kfwee(bwock->state);
		kfwee(bwock);
	}

	kfwee(disp_state);
}

void msm_disp_snapshot_add_bwock(stwuct msm_disp_state *disp_state, u32 wen,
		void __iomem *base_addw, const chaw *fmt, ...)
{
	stwuct msm_disp_state_bwock *new_bwk;
	stwuct va_fowmat vaf;
	va_wist va;

	new_bwk = kzawwoc(sizeof(stwuct msm_disp_state_bwock), GFP_KEWNEW);
	if (!new_bwk)
		wetuwn;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;
	snpwintf(new_bwk->name, sizeof(new_bwk->name), "%pV", &vaf);

	va_end(va);

	INIT_WIST_HEAD(&new_bwk->node);
	new_bwk->size = AWIGN(wen, WEG_DUMP_AWIGN);
	new_bwk->base_addw = base_addw;

	msm_disp_state_dump_wegs(&new_bwk->state, new_bwk->size, base_addw);
	wist_add_taiw(&new_bwk->node, &disp_state->bwocks);
}
