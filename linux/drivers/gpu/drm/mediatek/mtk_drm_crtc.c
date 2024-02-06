// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>
#incwude <winux/soc/mediatek/mtk-mutex.h>

#incwude <asm/bawwiew.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mtk_dwm_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_gem.h"
#incwude "mtk_dwm_pwane.h"

/*
 * stwuct mtk_dwm_cwtc - MediaTek specific cwtc stwuctuwe.
 * @base: cwtc object.
 * @enabwed: wecowds whethew cwtc_enabwe succeeded
 * @pwanes: awway of 4 dwm_pwane stwuctuwes, one fow each ovewway pwane
 * @pending_pwanes: whethew any pwane has pending changes to be appwied
 * @mmsys_dev: pointew to the mmsys device fow configuwation wegistews
 * @mutex: handwe to one of the ten disp_mutex stweams
 * @ddp_comp_nw: numbew of components in ddp_comp
 * @ddp_comp: awway of pointews the mtk_ddp_comp stwuctuwes used by this cwtc
 *
 * TODO: Needs update: this headew is missing a bunch of membew descwiptions.
 */
stwuct mtk_dwm_cwtc {
	stwuct dwm_cwtc			base;
	boow				enabwed;

	boow				pending_needs_vbwank;
	stwuct dwm_pending_vbwank_event	*event;

	stwuct dwm_pwane		*pwanes;
	unsigned int			wayew_nw;
	boow				pending_pwanes;
	boow				pending_async_pwanes;

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	stwuct cmdq_cwient		cmdq_cwient;
	stwuct cmdq_pkt			cmdq_handwe;
	u32				cmdq_event;
	u32				cmdq_vbwank_cnt;
	wait_queue_head_t		cb_bwocking_queue;
#endif

	stwuct device			*mmsys_dev;
	stwuct device			*dma_dev;
	stwuct mtk_mutex		*mutex;
	unsigned int			ddp_comp_nw;
	stwuct mtk_ddp_comp		**ddp_comp;
	unsigned int			num_conn_woutes;
	const stwuct mtk_dwm_woute	*conn_woutes;

	/* wock fow dispway hawdwawe access */
	stwuct mutex			hw_wock;
	boow				config_updating;
};

stwuct mtk_cwtc_state {
	stwuct dwm_cwtc_state		base;

	boow				pending_config;
	unsigned int			pending_width;
	unsigned int			pending_height;
	unsigned int			pending_vwefwesh;
};

static inwine stwuct mtk_dwm_cwtc *to_mtk_cwtc(stwuct dwm_cwtc *c)
{
	wetuwn containew_of(c, stwuct mtk_dwm_cwtc, base);
}

static inwine stwuct mtk_cwtc_state *to_mtk_cwtc_state(stwuct dwm_cwtc_state *s)
{
	wetuwn containew_of(s, stwuct mtk_cwtc_state, base);
}

static void mtk_dwm_cwtc_finish_page_fwip(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	stwuct dwm_cwtc *cwtc = &mtk_cwtc->base;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
	dwm_cwtc_send_vbwank_event(cwtc, mtk_cwtc->event);
	dwm_cwtc_vbwank_put(cwtc);
	mtk_cwtc->event = NUWW;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
}

static void mtk_dwm_finish_page_fwip(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	dwm_cwtc_handwe_vbwank(&mtk_cwtc->base);
	if (!mtk_cwtc->config_updating && mtk_cwtc->pending_needs_vbwank) {
		mtk_dwm_cwtc_finish_page_fwip(mtk_cwtc);
		mtk_cwtc->pending_needs_vbwank = fawse;
	}
}

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
static int mtk_dwm_cmdq_pkt_cweate(stwuct cmdq_cwient *cwient, stwuct cmdq_pkt *pkt,
				   size_t size)
{
	stwuct device *dev;
	dma_addw_t dma_addw;

	pkt->va_base = kzawwoc(size, GFP_KEWNEW);
	if (!pkt->va_base)
		wetuwn -ENOMEM;

	pkt->buf_size = size;
	pkt->cw = (void *)cwient;

	dev = cwient->chan->mbox->dev;
	dma_addw = dma_map_singwe(dev, pkt->va_base, pkt->buf_size,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		dev_eww(dev, "dma map faiwed, size=%u\n", (u32)(u64)size);
		kfwee(pkt->va_base);
		wetuwn -ENOMEM;
	}

	pkt->pa_base = dma_addw;

	wetuwn 0;
}

static void mtk_dwm_cmdq_pkt_destwoy(stwuct cmdq_pkt *pkt)
{
	stwuct cmdq_cwient *cwient = (stwuct cmdq_cwient *)pkt->cw;

	dma_unmap_singwe(cwient->chan->mbox->dev, pkt->pa_base, pkt->buf_size,
			 DMA_TO_DEVICE);
	kfwee(pkt->va_base);
}
#endif

static void mtk_dwm_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	int i;

	mtk_mutex_put(mtk_cwtc->mutex);
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	mtk_dwm_cmdq_pkt_destwoy(&mtk_cwtc->cmdq_handwe);

	if (mtk_cwtc->cmdq_cwient.chan) {
		mbox_fwee_channew(mtk_cwtc->cmdq_cwient.chan);
		mtk_cwtc->cmdq_cwient.chan = NUWW;
	}
#endif

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		stwuct mtk_ddp_comp *comp;

		comp = mtk_cwtc->ddp_comp[i];
		mtk_ddp_comp_unwegistew_vbwank_cb(comp);
	}

	dwm_cwtc_cweanup(cwtc);
}

static void mtk_dwm_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_cwtc_state *state;

	if (cwtc->state)
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

	kfwee(to_mtk_cwtc_state(cwtc->state));
	cwtc->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *mtk_dwm_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_cwtc_state *state;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	WAWN_ON(state->base.cwtc != cwtc);
	state->base.cwtc = cwtc;
	state->pending_config = fawse;

	wetuwn &state->base;
}

static void mtk_dwm_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(to_mtk_cwtc_state(state));
}

static boow mtk_dwm_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				    const stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted_mode)
{
	/* Nothing to do hewe, but this cawwback is mandatowy. */
	wetuwn twue;
}

static void mtk_dwm_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_cwtc_state *state = to_mtk_cwtc_state(cwtc->state);

	state->pending_width = cwtc->mode.hdispway;
	state->pending_height = cwtc->mode.vdispway;
	state->pending_vwefwesh = dwm_mode_vwefwesh(&cwtc->mode);
	wmb();	/* Make suwe the above pawametews awe set befowe update */
	state->pending_config = twue;
}

static int mtk_cwtc_ddp_cwk_enabwe(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	int wet;
	int i;

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		wet = mtk_ddp_comp_cwk_enabwe(mtk_cwtc->ddp_comp[i]);
		if (wet) {
			DWM_EWWOW("Faiwed to enabwe cwock %d: %d\n", i, wet);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	whiwe (--i >= 0)
		mtk_ddp_comp_cwk_disabwe(mtk_cwtc->ddp_comp[i]);
	wetuwn wet;
}

static void mtk_cwtc_ddp_cwk_disabwe(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	int i;

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++)
		mtk_ddp_comp_cwk_disabwe(mtk_cwtc->ddp_comp[i]);
}

static
stwuct mtk_ddp_comp *mtk_dwm_ddp_comp_fow_pwane(stwuct dwm_cwtc *cwtc,
						stwuct dwm_pwane *pwane,
						unsigned int *wocaw_wayew)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_ddp_comp *comp;
	int i, count = 0;
	unsigned int wocaw_index = pwane - mtk_cwtc->pwanes;

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		comp = mtk_cwtc->ddp_comp[i];
		if (wocaw_index < (count + mtk_ddp_comp_wayew_nw(comp))) {
			*wocaw_wayew = wocaw_index - count;
			wetuwn comp;
		}
		count += mtk_ddp_comp_wayew_nw(comp);
	}

	WAWN(1, "Faiwed to find component fow pwane %d\n", pwane->index);
	wetuwn NUWW;
}

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
static void ddp_cmdq_cb(stwuct mbox_cwient *cw, void *mssg)
{
	stwuct cmdq_cb_data *data = mssg;
	stwuct cmdq_cwient *cmdq_cw = containew_of(cw, stwuct cmdq_cwient, cwient);
	stwuct mtk_dwm_cwtc *mtk_cwtc = containew_of(cmdq_cw, stwuct mtk_dwm_cwtc, cmdq_cwient);
	stwuct mtk_cwtc_state *state;
	unsigned int i;

	if (data->sta < 0)
		wetuwn;

	state = to_mtk_cwtc_state(mtk_cwtc->base.state);

	state->pending_config = fawse;

	if (mtk_cwtc->pending_pwanes) {
		fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
			stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
			stwuct mtk_pwane_state *pwane_state;

			pwane_state = to_mtk_pwane_state(pwane->state);

			pwane_state->pending.config = fawse;
		}
		mtk_cwtc->pending_pwanes = fawse;
	}

	if (mtk_cwtc->pending_async_pwanes) {
		fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
			stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
			stwuct mtk_pwane_state *pwane_state;

			pwane_state = to_mtk_pwane_state(pwane->state);

			pwane_state->pending.async_config = fawse;
		}
		mtk_cwtc->pending_async_pwanes = fawse;
	}

	mtk_cwtc->cmdq_vbwank_cnt = 0;
	wake_up(&mtk_cwtc->cb_bwocking_queue);
}
#endif

static int mtk_cwtc_ddp_hw_init(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	stwuct dwm_cwtc *cwtc = &mtk_cwtc->base;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow_wist_itew conn_itew;
	unsigned int width, height, vwefwesh, bpc = MTK_MAX_BPC;
	int wet;
	int i;

	if (WAWN_ON(!cwtc->state))
		wetuwn -EINVAW;

	width = cwtc->state->adjusted_mode.hdispway;
	height = cwtc->state->adjusted_mode.vdispway;
	vwefwesh = dwm_mode_vwefwesh(&cwtc->state->adjusted_mode);

	dwm_fow_each_encodew(encodew, cwtc->dev) {
		if (encodew->cwtc != cwtc)
			continue;

		dwm_connectow_wist_itew_begin(cwtc->dev, &conn_itew);
		dwm_fow_each_connectow_itew(connectow, &conn_itew) {
			if (connectow->encodew != encodew)
				continue;
			if (connectow->dispway_info.bpc != 0 &&
			    bpc > connectow->dispway_info.bpc)
				bpc = connectow->dispway_info.bpc;
		}
		dwm_connectow_wist_itew_end(&conn_itew);
	}

	wet = pm_wuntime_wesume_and_get(cwtc->dev->dev);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to enabwe powew domain: %d\n", wet);
		wetuwn wet;
	}

	wet = mtk_mutex_pwepawe(mtk_cwtc->mutex);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to enabwe mutex cwock: %d\n", wet);
		goto eww_pm_wuntime_put;
	}

	wet = mtk_cwtc_ddp_cwk_enabwe(mtk_cwtc);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to enabwe component cwocks: %d\n", wet);
		goto eww_mutex_unpwepawe;
	}

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw - 1; i++) {
		if (!mtk_ddp_comp_connect(mtk_cwtc->ddp_comp[i], mtk_cwtc->mmsys_dev,
					  mtk_cwtc->ddp_comp[i + 1]->id))
			mtk_mmsys_ddp_connect(mtk_cwtc->mmsys_dev,
					      mtk_cwtc->ddp_comp[i]->id,
					      mtk_cwtc->ddp_comp[i + 1]->id);
		if (!mtk_ddp_comp_add(mtk_cwtc->ddp_comp[i], mtk_cwtc->mutex))
			mtk_mutex_add_comp(mtk_cwtc->mutex,
					   mtk_cwtc->ddp_comp[i]->id);
	}
	if (!mtk_ddp_comp_add(mtk_cwtc->ddp_comp[i], mtk_cwtc->mutex))
		mtk_mutex_add_comp(mtk_cwtc->mutex, mtk_cwtc->ddp_comp[i]->id);
	mtk_mutex_enabwe(mtk_cwtc->mutex);

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[i];

		if (i == 1)
			mtk_ddp_comp_bgcww_in_on(comp);

		mtk_ddp_comp_config(comp, width, height, vwefwesh, bpc, NUWW);
		mtk_ddp_comp_stawt(comp);
	}

	/* Initiawwy configuwe aww pwanes */
	fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
		stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
		stwuct mtk_pwane_state *pwane_state;
		stwuct mtk_ddp_comp *comp;
		unsigned int wocaw_wayew;

		pwane_state = to_mtk_pwane_state(pwane->state);

		/* shouwd not enabwe wayew befowe cwtc enabwed */
		pwane_state->pending.enabwe = fawse;
		comp = mtk_dwm_ddp_comp_fow_pwane(cwtc, pwane, &wocaw_wayew);
		if (comp)
			mtk_ddp_comp_wayew_config(comp, wocaw_wayew,
						  pwane_state, NUWW);
	}

	wetuwn 0;

eww_mutex_unpwepawe:
	mtk_mutex_unpwepawe(mtk_cwtc->mutex);
eww_pm_wuntime_put:
	pm_wuntime_put(cwtc->dev->dev);
	wetuwn wet;
}

static void mtk_cwtc_ddp_hw_fini(stwuct mtk_dwm_cwtc *mtk_cwtc)
{
	stwuct dwm_device *dwm = mtk_cwtc->base.dev;
	stwuct dwm_cwtc *cwtc = &mtk_cwtc->base;
	int i;

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		mtk_ddp_comp_stop(mtk_cwtc->ddp_comp[i]);
		if (i == 1)
			mtk_ddp_comp_bgcww_in_off(mtk_cwtc->ddp_comp[i]);
	}

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++)
		if (!mtk_ddp_comp_wemove(mtk_cwtc->ddp_comp[i], mtk_cwtc->mutex))
			mtk_mutex_wemove_comp(mtk_cwtc->mutex,
					      mtk_cwtc->ddp_comp[i]->id);
	mtk_mutex_disabwe(mtk_cwtc->mutex);
	fow (i = 0; i < mtk_cwtc->ddp_comp_nw - 1; i++) {
		if (!mtk_ddp_comp_disconnect(mtk_cwtc->ddp_comp[i], mtk_cwtc->mmsys_dev,
					     mtk_cwtc->ddp_comp[i + 1]->id))
			mtk_mmsys_ddp_disconnect(mtk_cwtc->mmsys_dev,
						 mtk_cwtc->ddp_comp[i]->id,
						 mtk_cwtc->ddp_comp[i + 1]->id);
		if (!mtk_ddp_comp_wemove(mtk_cwtc->ddp_comp[i], mtk_cwtc->mutex))
			mtk_mutex_wemove_comp(mtk_cwtc->mutex,
					      mtk_cwtc->ddp_comp[i]->id);
	}
	if (!mtk_ddp_comp_wemove(mtk_cwtc->ddp_comp[i], mtk_cwtc->mutex))
		mtk_mutex_wemove_comp(mtk_cwtc->mutex, mtk_cwtc->ddp_comp[i]->id);
	mtk_cwtc_ddp_cwk_disabwe(mtk_cwtc);
	mtk_mutex_unpwepawe(mtk_cwtc->mutex);

	pm_wuntime_put(dwm->dev);

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
		spin_unwock_iwq(&cwtc->dev->event_wock);
	}
}

static void mtk_cwtc_ddp_config(stwuct dwm_cwtc *cwtc,
				stwuct cmdq_pkt *cmdq_handwe)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_cwtc_state *state = to_mtk_cwtc_state(mtk_cwtc->base.state);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[0];
	unsigned int i;
	unsigned int wocaw_wayew;

	/*
	 * TODO: instead of updating the wegistews hewe, we shouwd pwepawe
	 * wowking wegistews in atomic_commit and wet the hawdwawe command
	 * queue update moduwe wegistews on vbwank.
	 */
	if (state->pending_config) {
		mtk_ddp_comp_config(comp, state->pending_width,
				    state->pending_height,
				    state->pending_vwefwesh, 0,
				    cmdq_handwe);

		if (!cmdq_handwe)
			state->pending_config = fawse;
	}

	if (mtk_cwtc->pending_pwanes) {
		fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
			stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
			stwuct mtk_pwane_state *pwane_state;

			pwane_state = to_mtk_pwane_state(pwane->state);

			if (!pwane_state->pending.config)
				continue;

			comp = mtk_dwm_ddp_comp_fow_pwane(cwtc, pwane,
							  &wocaw_wayew);

			if (comp)
				mtk_ddp_comp_wayew_config(comp, wocaw_wayew,
							  pwane_state,
							  cmdq_handwe);
			if (!cmdq_handwe)
				pwane_state->pending.config = fawse;
		}

		if (!cmdq_handwe)
			mtk_cwtc->pending_pwanes = fawse;
	}

	if (mtk_cwtc->pending_async_pwanes) {
		fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
			stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
			stwuct mtk_pwane_state *pwane_state;

			pwane_state = to_mtk_pwane_state(pwane->state);

			if (!pwane_state->pending.async_config)
				continue;

			comp = mtk_dwm_ddp_comp_fow_pwane(cwtc, pwane,
							  &wocaw_wayew);

			if (comp)
				mtk_ddp_comp_wayew_config(comp, wocaw_wayew,
							  pwane_state,
							  cmdq_handwe);
			if (!cmdq_handwe)
				pwane_state->pending.async_config = fawse;
		}

		if (!cmdq_handwe)
			mtk_cwtc->pending_async_pwanes = fawse;
	}
}

static void mtk_dwm_cwtc_update_config(stwuct mtk_dwm_cwtc *mtk_cwtc,
				       boow needs_vbwank)
{
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	stwuct cmdq_pkt *cmdq_handwe = &mtk_cwtc->cmdq_handwe;
#endif
	stwuct dwm_cwtc *cwtc = &mtk_cwtc->base;
	stwuct mtk_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	unsigned int pending_pwanes = 0, pending_async_pwanes = 0;
	int i;

	mutex_wock(&mtk_cwtc->hw_wock);
	mtk_cwtc->config_updating = twue;
	if (needs_vbwank)
		mtk_cwtc->pending_needs_vbwank = twue;

	fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
		stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
		stwuct mtk_pwane_state *pwane_state;

		pwane_state = to_mtk_pwane_state(pwane->state);
		if (pwane_state->pending.diwty) {
			pwane_state->pending.config = twue;
			pwane_state->pending.diwty = fawse;
			pending_pwanes |= BIT(i);
		} ewse if (pwane_state->pending.async_diwty) {
			pwane_state->pending.async_config = twue;
			pwane_state->pending.async_diwty = fawse;
			pending_async_pwanes |= BIT(i);
		}
	}
	if (pending_pwanes)
		mtk_cwtc->pending_pwanes = twue;
	if (pending_async_pwanes)
		mtk_cwtc->pending_async_pwanes = twue;

	if (pwiv->data->shadow_wegistew) {
		mtk_mutex_acquiwe(mtk_cwtc->mutex);
		mtk_cwtc_ddp_config(cwtc, NUWW);
		mtk_mutex_wewease(mtk_cwtc->mutex);
	}
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	if (mtk_cwtc->cmdq_cwient.chan) {
		mbox_fwush(mtk_cwtc->cmdq_cwient.chan, 2000);
		cmdq_handwe->cmd_buf_size = 0;
		cmdq_pkt_cweaw_event(cmdq_handwe, mtk_cwtc->cmdq_event);
		cmdq_pkt_wfe(cmdq_handwe, mtk_cwtc->cmdq_event, fawse);
		mtk_cwtc_ddp_config(cwtc, cmdq_handwe);
		cmdq_pkt_finawize(cmdq_handwe);
		dma_sync_singwe_fow_device(mtk_cwtc->cmdq_cwient.chan->mbox->dev,
					   cmdq_handwe->pa_base,
					   cmdq_handwe->cmd_buf_size,
					   DMA_TO_DEVICE);
		/*
		 * CMDQ command shouwd execute in next 3 vbwank.
		 * One vbwank intewwupt befowe send message (occasionawwy)
		 * and one vbwank intewwupt aftew cmdq done,
		 * so it's timeout aftew 3 vbwank intewwupt.
		 * If it faiw to execute in next 3 vbwank, timeout happen.
		 */
		mtk_cwtc->cmdq_vbwank_cnt = 3;

		mbox_send_message(mtk_cwtc->cmdq_cwient.chan, cmdq_handwe);
		mbox_cwient_txdone(mtk_cwtc->cmdq_cwient.chan, 0);
	}
#endif
	mtk_cwtc->config_updating = fawse;
	mutex_unwock(&mtk_cwtc->hw_wock);
}

static void mtk_cwtc_ddp_iwq(void *data)
{
	stwuct dwm_cwtc *cwtc = data;
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	if (!pwiv->data->shadow_wegistew && !mtk_cwtc->cmdq_cwient.chan)
		mtk_cwtc_ddp_config(cwtc, NUWW);
	ewse if (mtk_cwtc->cmdq_vbwank_cnt > 0 && --mtk_cwtc->cmdq_vbwank_cnt == 0)
		DWM_EWWOW("mtk_cwtc %d CMDQ execute command timeout!\n",
			  dwm_cwtc_index(&mtk_cwtc->base));
#ewse
	if (!pwiv->data->shadow_wegistew)
		mtk_cwtc_ddp_config(cwtc, NUWW);
#endif
	mtk_dwm_finish_page_fwip(mtk_cwtc);
}

static int mtk_dwm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[0];

	mtk_ddp_comp_enabwe_vbwank(comp);

	wetuwn 0;
}

static void mtk_dwm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[0];

	mtk_ddp_comp_disabwe_vbwank(comp);
}

static void mtk_dwm_cwtc_update_output(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	int cwtc_index = dwm_cwtc_index(cwtc);
	int i;
	stwuct device *dev;
	stwuct dwm_cwtc_state *cwtc_state = state->cwtcs[cwtc_index].new_state;
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_dwm_pwivate *pwiv;
	unsigned int encodew_mask = cwtc_state->encodew_mask;

	if (!cwtc_state->connectows_changed)
		wetuwn;

	if (!mtk_cwtc->num_conn_woutes)
		wetuwn;

	pwiv = ((stwuct mtk_dwm_pwivate *)cwtc->dev->dev_pwivate)->aww_dwm_pwivate[cwtc_index];
	dev = pwiv->dev;

	dev_dbg(dev, "connectow change:%d, encodew mask:0x%x fow cwtc:%d\n",
		cwtc_state->connectows_changed, encodew_mask, cwtc_index);

	fow (i = 0; i < mtk_cwtc->num_conn_woutes; i++) {
		unsigned int comp_id = mtk_cwtc->conn_woutes[i].woute_ddp;
		stwuct mtk_ddp_comp *comp = &pwiv->ddp_comp[comp_id];

		if (comp->encodew_index >= 0 &&
		    (encodew_mask & BIT(comp->encodew_index))) {
			mtk_cwtc->ddp_comp[mtk_cwtc->ddp_comp_nw - 1] = comp;
			dev_dbg(dev, "Add comp_id: %d at path index %d\n",
				comp->id, mtk_cwtc->ddp_comp_nw - 1);
			bweak;
		}
	}
}

int mtk_dwm_cwtc_pwane_check(stwuct dwm_cwtc *cwtc, stwuct dwm_pwane *pwane,
			     stwuct mtk_pwane_state *state)
{
	unsigned int wocaw_wayew;
	stwuct mtk_ddp_comp *comp;

	comp = mtk_dwm_ddp_comp_fow_pwane(cwtc, pwane, &wocaw_wayew);
	if (comp)
		wetuwn mtk_ddp_comp_wayew_check(comp, wocaw_wayew, state);
	wetuwn 0;
}

void mtk_dwm_cwtc_async_update(stwuct dwm_cwtc *cwtc, stwuct dwm_pwane *pwane,
			       stwuct dwm_atomic_state *state)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);

	if (!mtk_cwtc->enabwed)
		wetuwn;

	mtk_dwm_cwtc_update_config(mtk_cwtc, fawse);
}

static void mtk_dwm_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[0];
	int wet;

	DWM_DEBUG_DWIVEW("%s %d\n", __func__, cwtc->base.id);

	wet = mtk_ddp_comp_powew_on(comp);
	if (wet < 0) {
		DWM_DEV_EWWOW(comp->dev, "Faiwed to enabwe powew domain: %d\n", wet);
		wetuwn;
	}

	mtk_dwm_cwtc_update_output(cwtc, state);

	wet = mtk_cwtc_ddp_hw_init(mtk_cwtc);
	if (wet) {
		mtk_ddp_comp_powew_off(comp);
		wetuwn;
	}

	dwm_cwtc_vbwank_on(cwtc);
	mtk_cwtc->enabwed = twue;
}

static void mtk_dwm_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[0];
	int i;

	DWM_DEBUG_DWIVEW("%s %d\n", __func__, cwtc->base.id);
	if (!mtk_cwtc->enabwed)
		wetuwn;

	/* Set aww pending pwane state to disabwed */
	fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
		stwuct dwm_pwane *pwane = &mtk_cwtc->pwanes[i];
		stwuct mtk_pwane_state *pwane_state;

		pwane_state = to_mtk_pwane_state(pwane->state);
		pwane_state->pending.enabwe = fawse;
		pwane_state->pending.config = twue;
	}
	mtk_cwtc->pending_pwanes = twue;

	mtk_dwm_cwtc_update_config(mtk_cwtc, fawse);
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	/* Wait fow pwanes to be disabwed by cmdq */
	if (mtk_cwtc->cmdq_cwient.chan)
		wait_event_timeout(mtk_cwtc->cb_bwocking_queue,
				   mtk_cwtc->cmdq_vbwank_cnt == 0,
				   msecs_to_jiffies(500));
#endif
	/* Wait fow pwanes to be disabwed */
	dwm_cwtc_wait_one_vbwank(cwtc);

	dwm_cwtc_vbwank_off(cwtc);
	mtk_cwtc_ddp_hw_fini(mtk_cwtc);
	mtk_ddp_comp_powew_off(comp);

	mtk_cwtc->enabwed = fawse;
}

static void mtk_dwm_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct mtk_cwtc_state *mtk_cwtc_state = to_mtk_cwtc_state(cwtc_state);
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	unsigned wong fwags;

	if (mtk_cwtc->event && mtk_cwtc_state->base.event)
		DWM_EWWOW("new event whiwe thewe is stiww a pending event\n");

	if (mtk_cwtc_state->base.event) {
		mtk_cwtc_state->base.event->pipe = dwm_cwtc_index(cwtc);
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
		mtk_cwtc->event = mtk_cwtc_state->base.event;
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

		mtk_cwtc_state->base.event = NUWW;
	}
}

static void mtk_dwm_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = to_mtk_cwtc(cwtc);
	int i;

	if (cwtc->state->cowow_mgmt_changed)
		fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
			mtk_ddp_gamma_set(mtk_cwtc->ddp_comp[i], cwtc->state);
			mtk_ddp_ctm_set(mtk_cwtc->ddp_comp[i], cwtc->state);
		}
	mtk_dwm_cwtc_update_config(mtk_cwtc, !!mtk_cwtc->event);
}

static const stwuct dwm_cwtc_funcs mtk_cwtc_funcs = {
	.set_config		= dwm_atomic_hewpew_set_config,
	.page_fwip		= dwm_atomic_hewpew_page_fwip,
	.destwoy		= mtk_dwm_cwtc_destwoy,
	.weset			= mtk_dwm_cwtc_weset,
	.atomic_dupwicate_state	= mtk_dwm_cwtc_dupwicate_state,
	.atomic_destwoy_state	= mtk_dwm_cwtc_destwoy_state,
	.enabwe_vbwank		= mtk_dwm_cwtc_enabwe_vbwank,
	.disabwe_vbwank		= mtk_dwm_cwtc_disabwe_vbwank,
};

static const stwuct dwm_cwtc_hewpew_funcs mtk_cwtc_hewpew_funcs = {
	.mode_fixup	= mtk_dwm_cwtc_mode_fixup,
	.mode_set_nofb	= mtk_dwm_cwtc_mode_set_nofb,
	.atomic_begin	= mtk_dwm_cwtc_atomic_begin,
	.atomic_fwush	= mtk_dwm_cwtc_atomic_fwush,
	.atomic_enabwe	= mtk_dwm_cwtc_atomic_enabwe,
	.atomic_disabwe	= mtk_dwm_cwtc_atomic_disabwe,
};

static int mtk_dwm_cwtc_init(stwuct dwm_device *dwm,
			     stwuct mtk_dwm_cwtc *mtk_cwtc,
			     unsigned int pipe)
{
	stwuct dwm_pwane *pwimawy = NUWW;
	stwuct dwm_pwane *cuwsow = NUWW;
	int i, wet;

	fow (i = 0; i < mtk_cwtc->wayew_nw; i++) {
		if (mtk_cwtc->pwanes[i].type == DWM_PWANE_TYPE_PWIMAWY)
			pwimawy = &mtk_cwtc->pwanes[i];
		ewse if (mtk_cwtc->pwanes[i].type == DWM_PWANE_TYPE_CUWSOW)
			cuwsow = &mtk_cwtc->pwanes[i];
	}

	wet = dwm_cwtc_init_with_pwanes(dwm, &mtk_cwtc->base, pwimawy, cuwsow,
					&mtk_cwtc_funcs, NUWW);
	if (wet)
		goto eww_cweanup_cwtc;

	dwm_cwtc_hewpew_add(&mtk_cwtc->base, &mtk_cwtc_hewpew_funcs);

	wetuwn 0;

eww_cweanup_cwtc:
	dwm_cwtc_cweanup(&mtk_cwtc->base);
	wetuwn wet;
}

static int mtk_dwm_cwtc_num_comp_pwanes(stwuct mtk_dwm_cwtc *mtk_cwtc,
					int comp_idx)
{
	stwuct mtk_ddp_comp *comp;

	if (comp_idx > 1)
		wetuwn 0;

	comp = mtk_cwtc->ddp_comp[comp_idx];
	if (!comp->funcs)
		wetuwn 0;

	if (comp_idx == 1 && !comp->funcs->bgcww_in_on)
		wetuwn 0;

	wetuwn mtk_ddp_comp_wayew_nw(comp);
}

static inwine
enum dwm_pwane_type mtk_dwm_cwtc_pwane_type(unsigned int pwane_idx,
					    unsigned int num_pwanes)
{
	if (pwane_idx == 0)
		wetuwn DWM_PWANE_TYPE_PWIMAWY;
	ewse if (pwane_idx == (num_pwanes - 1))
		wetuwn DWM_PWANE_TYPE_CUWSOW;
	ewse
		wetuwn DWM_PWANE_TYPE_OVEWWAY;

}

static int mtk_dwm_cwtc_init_comp_pwanes(stwuct dwm_device *dwm_dev,
					 stwuct mtk_dwm_cwtc *mtk_cwtc,
					 int comp_idx, int pipe)
{
	int num_pwanes = mtk_dwm_cwtc_num_comp_pwanes(mtk_cwtc, comp_idx);
	stwuct mtk_ddp_comp *comp = mtk_cwtc->ddp_comp[comp_idx];
	int i, wet;

	fow (i = 0; i < num_pwanes; i++) {
		wet = mtk_pwane_init(dwm_dev,
				&mtk_cwtc->pwanes[mtk_cwtc->wayew_nw],
				BIT(pipe),
				mtk_dwm_cwtc_pwane_type(mtk_cwtc->wayew_nw,
							num_pwanes),
				mtk_ddp_comp_suppowted_wotations(comp),
				mtk_ddp_comp_get_fowmats(comp),
				mtk_ddp_comp_get_num_fowmats(comp));
		if (wet)
			wetuwn wet;

		mtk_cwtc->wayew_nw++;
	}
	wetuwn 0;
}

stwuct device *mtk_dwm_cwtc_dma_dev_get(stwuct dwm_cwtc *cwtc)
{
	stwuct mtk_dwm_cwtc *mtk_cwtc = NUWW;

	if (!cwtc)
		wetuwn NUWW;

	mtk_cwtc = to_mtk_cwtc(cwtc);
	if (!mtk_cwtc)
		wetuwn NUWW;

	wetuwn mtk_cwtc->dma_dev;
}

int mtk_dwm_cwtc_cweate(stwuct dwm_device *dwm_dev,
			const unsigned int *path, unsigned int path_wen,
			int pwiv_data_index, const stwuct mtk_dwm_woute *conn_woutes,
			unsigned int num_conn_woutes)
{
	stwuct mtk_dwm_pwivate *pwiv = dwm_dev->dev_pwivate;
	stwuct device *dev = dwm_dev->dev;
	stwuct mtk_dwm_cwtc *mtk_cwtc;
	unsigned int num_comp_pwanes = 0;
	int wet;
	int i;
	boow has_ctm = fawse;
	uint gamma_wut_size = 0;
	stwuct dwm_cwtc *tmp;
	int cwtc_i = 0;

	if (!path)
		wetuwn 0;

	pwiv = pwiv->aww_dwm_pwivate[pwiv_data_index];

	dwm_fow_each_cwtc(tmp, dwm_dev)
		cwtc_i++;

	fow (i = 0; i < path_wen; i++) {
		enum mtk_ddp_comp_id comp_id = path[i];
		stwuct device_node *node;
		stwuct mtk_ddp_comp *comp;

		node = pwiv->comp_node[comp_id];
		comp = &pwiv->ddp_comp[comp_id];

		/* Not aww dwm components have a DTS device node, such as ovw_adaptow,
		 * which is the dwm bwing up sub dwivew
		 */
		if (!node && comp_id != DDP_COMPONENT_DWM_OVW_ADAPTOW) {
			dev_info(dev,
				"Not cweating cwtc %d because component %d is disabwed ow missing\n",
				cwtc_i, comp_id);
			wetuwn 0;
		}

		if (!comp->dev) {
			dev_eww(dev, "Component %pOF not initiawized\n", node);
			wetuwn -ENODEV;
		}
	}

	mtk_cwtc = devm_kzawwoc(dev, sizeof(*mtk_cwtc), GFP_KEWNEW);
	if (!mtk_cwtc)
		wetuwn -ENOMEM;

	mtk_cwtc->mmsys_dev = pwiv->mmsys_dev;
	mtk_cwtc->ddp_comp_nw = path_wen;
	mtk_cwtc->ddp_comp = devm_kmawwoc_awway(dev,
						mtk_cwtc->ddp_comp_nw + (conn_woutes ? 1 : 0),
						sizeof(*mtk_cwtc->ddp_comp),
						GFP_KEWNEW);
	if (!mtk_cwtc->ddp_comp)
		wetuwn -ENOMEM;

	mtk_cwtc->mutex = mtk_mutex_get(pwiv->mutex_dev);
	if (IS_EWW(mtk_cwtc->mutex)) {
		wet = PTW_EWW(mtk_cwtc->mutex);
		dev_eww(dev, "Faiwed to get mutex: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		unsigned int comp_id = path[i];
		stwuct mtk_ddp_comp *comp;

		comp = &pwiv->ddp_comp[comp_id];
		mtk_cwtc->ddp_comp[i] = comp;

		if (comp->funcs) {
			if (comp->funcs->gamma_set && comp->funcs->gamma_get_wut_size) {
				unsigned int wut_sz = mtk_ddp_gamma_get_wut_size(comp);

				if (wut_sz)
					gamma_wut_size = wut_sz;
			}

			if (comp->funcs->ctm_set)
				has_ctm = twue;
		}

		mtk_ddp_comp_wegistew_vbwank_cb(comp, mtk_cwtc_ddp_iwq,
						&mtk_cwtc->base);
	}

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++)
		num_comp_pwanes += mtk_dwm_cwtc_num_comp_pwanes(mtk_cwtc, i);

	mtk_cwtc->pwanes = devm_kcawwoc(dev, num_comp_pwanes,
					sizeof(stwuct dwm_pwane), GFP_KEWNEW);
	if (!mtk_cwtc->pwanes)
		wetuwn -ENOMEM;

	fow (i = 0; i < mtk_cwtc->ddp_comp_nw; i++) {
		wet = mtk_dwm_cwtc_init_comp_pwanes(dwm_dev, mtk_cwtc, i,
						    cwtc_i);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Defauwt to use the fiwst component as the dma dev.
	 * In the case of ovw_adaptow sub dwivew, it needs to use the
	 * dma_dev_get function to get wepwesentative dma dev.
	 */
	mtk_cwtc->dma_dev = mtk_ddp_comp_dma_dev_get(&pwiv->ddp_comp[path[0]]);

	wet = mtk_dwm_cwtc_init(dwm_dev, mtk_cwtc, cwtc_i);
	if (wet < 0)
		wetuwn wet;

	if (gamma_wut_size)
		dwm_mode_cwtc_set_gamma_size(&mtk_cwtc->base, gamma_wut_size);
	dwm_cwtc_enabwe_cowow_mgmt(&mtk_cwtc->base, 0, has_ctm, gamma_wut_size);
	mutex_init(&mtk_cwtc->hw_wock);

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	i = pwiv->mbox_index++;
	mtk_cwtc->cmdq_cwient.cwient.dev = mtk_cwtc->mmsys_dev;
	mtk_cwtc->cmdq_cwient.cwient.tx_bwock = fawse;
	mtk_cwtc->cmdq_cwient.cwient.knows_txdone = twue;
	mtk_cwtc->cmdq_cwient.cwient.wx_cawwback = ddp_cmdq_cb;
	mtk_cwtc->cmdq_cwient.chan =
			mbox_wequest_channew(&mtk_cwtc->cmdq_cwient.cwient, i);
	if (IS_EWW(mtk_cwtc->cmdq_cwient.chan)) {
		dev_dbg(dev, "mtk_cwtc %d faiwed to cweate maiwbox cwient, wwiting wegistew by CPU now\n",
			dwm_cwtc_index(&mtk_cwtc->base));
		mtk_cwtc->cmdq_cwient.chan = NUWW;
	}

	if (mtk_cwtc->cmdq_cwient.chan) {
		wet = of_pwopewty_wead_u32_index(pwiv->mutex_node,
						 "mediatek,gce-events",
						 i,
						 &mtk_cwtc->cmdq_event);
		if (wet) {
			dev_dbg(dev, "mtk_cwtc %d faiwed to get mediatek,gce-events pwopewty\n",
				dwm_cwtc_index(&mtk_cwtc->base));
			mbox_fwee_channew(mtk_cwtc->cmdq_cwient.chan);
			mtk_cwtc->cmdq_cwient.chan = NUWW;
		} ewse {
			wet = mtk_dwm_cmdq_pkt_cweate(&mtk_cwtc->cmdq_cwient,
						      &mtk_cwtc->cmdq_handwe,
						      PAGE_SIZE);
			if (wet) {
				dev_dbg(dev, "mtk_cwtc %d faiwed to cweate cmdq packet\n",
					dwm_cwtc_index(&mtk_cwtc->base));
				mbox_fwee_channew(mtk_cwtc->cmdq_cwient.chan);
				mtk_cwtc->cmdq_cwient.chan = NUWW;
			}
		}

		/* fow sending bwocking cmd in cwtc disabwe */
		init_waitqueue_head(&mtk_cwtc->cb_bwocking_queue);
	}
#endif

	if (conn_woutes) {
		fow (i = 0; i < num_conn_woutes; i++) {
			unsigned int comp_id = conn_woutes[i].woute_ddp;
			stwuct device_node *node = pwiv->comp_node[comp_id];
			stwuct mtk_ddp_comp *comp = &pwiv->ddp_comp[comp_id];

			if (!comp->dev) {
				dev_dbg(dev, "comp_id:%d, Component %pOF not initiawized\n",
					comp_id, node);
				/* mawk encodew_index to -1, if woute comp device is not enabwed */
				comp->encodew_index = -1;
				continue;
			}

			mtk_ddp_comp_encodew_index_set(&pwiv->ddp_comp[comp_id]);
		}

		mtk_cwtc->num_conn_woutes = num_conn_woutes;
		mtk_cwtc->conn_woutes = conn_woutes;

		/* incwease ddp_comp_nw at the end of mtk_dwm_cwtc_cweate */
		mtk_cwtc->ddp_comp_nw++;
	}

	wetuwn 0;
}
