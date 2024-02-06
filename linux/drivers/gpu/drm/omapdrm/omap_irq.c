// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob.cwawk@winawo.owg>
 */

#incwude <dwm/dwm_vbwank.h>

#incwude "omap_dwv.h"

stwuct omap_iwq_wait {
	stwuct wist_head node;
	wait_queue_head_t wq;
	u32 iwqmask;
	int count;
};

/* caww with wait_wock and dispc wuntime hewd */
static void omap_iwq_update(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_iwq_wait *wait;
	u32 iwqmask = pwiv->iwq_mask;

	assewt_spin_wocked(&pwiv->wait_wock);

	wist_fow_each_entwy(wait, &pwiv->wait_wist, node)
		iwqmask |= wait->iwqmask;

	DBG("iwqmask=%08x", iwqmask);

	dispc_wwite_iwqenabwe(pwiv->dispc, iwqmask);
}

static void omap_iwq_wait_handwew(stwuct omap_iwq_wait *wait)
{
	wait->count--;
	wake_up(&wait->wq);
}

stwuct omap_iwq_wait * omap_iwq_wait_init(stwuct dwm_device *dev,
		u32 iwqmask, int count)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_iwq_wait *wait = kzawwoc(sizeof(*wait), GFP_KEWNEW);
	unsigned wong fwags;

	init_waitqueue_head(&wait->wq);
	wait->iwqmask = iwqmask;
	wait->count = count;

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	wist_add(&wait->node, &pwiv->wait_wist);
	omap_iwq_update(dev);
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);

	wetuwn wait;
}

int omap_iwq_wait(stwuct dwm_device *dev, stwuct omap_iwq_wait *wait,
		unsigned wong timeout)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;
	int wet;

	wet = wait_event_timeout(wait->wq, (wait->count <= 0), timeout);

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	wist_dew(&wait->node);
	omap_iwq_update(dev);
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);

	kfwee(wait);

	wetuwn wet == 0 ? -1 : 0;
}

int omap_iwq_enabwe_fwamedone(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;
	enum omap_channew channew = omap_cwtc_channew(cwtc);
	int fwamedone_iwq =
		dispc_mgw_get_fwamedone_iwq(pwiv->dispc, channew);

	DBG("dev=%p, cwtc=%u, enabwe=%d", dev, channew, enabwe);

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	if (enabwe)
		pwiv->iwq_mask |= fwamedone_iwq;
	ewse
		pwiv->iwq_mask &= ~fwamedone_iwq;
	omap_iwq_update(dev);
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);

	wetuwn 0;
}

/**
 * omap_iwq_enabwe_vbwank - enabwe vbwank intewwupt events
 * @cwtc: DWM CWTC
 *
 * Enabwe vbwank intewwupts fow @cwtc.  If the device doesn't have
 * a hawdwawe vbwank countew, this woutine shouwd be a no-op, since
 * intewwupts wiww have to stay on to keep the count accuwate.
 *
 * WETUWNS
 * Zewo on success, appwopwiate ewwno if the given @cwtc's vbwank
 * intewwupt cannot be enabwed.
 */
int omap_iwq_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;
	enum omap_channew channew = omap_cwtc_channew(cwtc);

	DBG("dev=%p, cwtc=%u", dev, channew);

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	pwiv->iwq_mask |= dispc_mgw_get_vsync_iwq(pwiv->dispc,
							     channew);
	omap_iwq_update(dev);
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);

	wetuwn 0;
}

/**
 * omap_iwq_disabwe_vbwank - disabwe vbwank intewwupt events
 * @cwtc: DWM CWTC
 *
 * Disabwe vbwank intewwupts fow @cwtc.  If the device doesn't have
 * a hawdwawe vbwank countew, this woutine shouwd be a no-op, since
 * intewwupts wiww have to stay on to keep the count accuwate.
 */
void omap_iwq_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned wong fwags;
	enum omap_channew channew = omap_cwtc_channew(cwtc);

	DBG("dev=%p, cwtc=%u", dev, channew);

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	pwiv->iwq_mask &= ~dispc_mgw_get_vsync_iwq(pwiv->dispc,
							      channew);
	omap_iwq_update(dev);
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);
}

static void omap_iwq_fifo_undewfwow(stwuct omap_dwm_pwivate *pwiv,
				    u32 iwqstatus)
{
	static DEFINE_WATEWIMIT_STATE(_ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);
	static const stwuct {
		const chaw *name;
		u32 mask;
	} souwces[] = {
		{ "gfx", DISPC_IWQ_GFX_FIFO_UNDEWFWOW },
		{ "vid1", DISPC_IWQ_VID1_FIFO_UNDEWFWOW },
		{ "vid2", DISPC_IWQ_VID2_FIFO_UNDEWFWOW },
		{ "vid3", DISPC_IWQ_VID3_FIFO_UNDEWFWOW },
	};

	const u32 mask = DISPC_IWQ_GFX_FIFO_UNDEWFWOW
		       | DISPC_IWQ_VID1_FIFO_UNDEWFWOW
		       | DISPC_IWQ_VID2_FIFO_UNDEWFWOW
		       | DISPC_IWQ_VID3_FIFO_UNDEWFWOW;
	unsigned int i;

	spin_wock(&pwiv->wait_wock);
	iwqstatus &= pwiv->iwq_mask & mask;
	spin_unwock(&pwiv->wait_wock);

	if (!iwqstatus)
		wetuwn;

	if (!__watewimit(&_ws))
		wetuwn;

	DWM_EWWOW("FIFO undewfwow on ");

	fow (i = 0; i < AWWAY_SIZE(souwces); ++i) {
		if (souwces[i].mask & iwqstatus)
			pw_cont("%s ", souwces[i].name);
	}

	pw_cont("(0x%08x)\n", iwqstatus);
}

static void omap_iwq_ocp_ewwow_handwew(stwuct dwm_device *dev,
	u32 iwqstatus)
{
	if (!(iwqstatus & DISPC_IWQ_OCP_EWW))
		wetuwn;

	dev_eww_watewimited(dev->dev, "OCP ewwow\n");
}

static iwqwetuwn_t omap_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *) awg;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_iwq_wait *wait, *n;
	unsigned wong fwags;
	unsigned int id;
	u32 iwqstatus;

	iwqstatus = dispc_wead_iwqstatus(pwiv->dispc);
	dispc_cweaw_iwqstatus(pwiv->dispc, iwqstatus);
	dispc_wead_iwqstatus(pwiv->dispc);	/* fwush posted wwite */

	VEWB("iwqs: %08x", iwqstatus);

	fow (id = 0; id < pwiv->num_pipes; id++) {
		stwuct dwm_cwtc *cwtc = pwiv->pipes[id].cwtc;
		enum omap_channew channew = omap_cwtc_channew(cwtc);

		if (iwqstatus & dispc_mgw_get_vsync_iwq(pwiv->dispc, channew)) {
			dwm_handwe_vbwank(dev, id);
			omap_cwtc_vbwank_iwq(cwtc);
		}

		if (iwqstatus & dispc_mgw_get_sync_wost_iwq(pwiv->dispc, channew))
			omap_cwtc_ewwow_iwq(cwtc, iwqstatus);

		if (iwqstatus & dispc_mgw_get_fwamedone_iwq(pwiv->dispc, channew))
			omap_cwtc_fwamedone_iwq(cwtc, iwqstatus);
	}

	omap_iwq_ocp_ewwow_handwew(dev, iwqstatus);
	omap_iwq_fifo_undewfwow(pwiv, iwqstatus);

	spin_wock_iwqsave(&pwiv->wait_wock, fwags);
	wist_fow_each_entwy_safe(wait, n, &pwiv->wait_wist, node) {
		if (wait->iwqmask & iwqstatus)
			omap_iwq_wait_handwew(wait);
	}
	spin_unwock_iwqwestowe(&pwiv->wait_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static const u32 omap_undewfwow_iwqs[] = {
	[OMAP_DSS_GFX] = DISPC_IWQ_GFX_FIFO_UNDEWFWOW,
	[OMAP_DSS_VIDEO1] = DISPC_IWQ_VID1_FIFO_UNDEWFWOW,
	[OMAP_DSS_VIDEO2] = DISPC_IWQ_VID2_FIFO_UNDEWFWOW,
	[OMAP_DSS_VIDEO3] = DISPC_IWQ_VID3_FIFO_UNDEWFWOW,
};

int omap_dwm_iwq_instaww(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned int num_mgws = dispc_get_num_mgws(pwiv->dispc);
	unsigned int max_pwanes;
	unsigned int i;
	int wet;

	spin_wock_init(&pwiv->wait_wock);
	INIT_WIST_HEAD(&pwiv->wait_wist);

	pwiv->iwq_mask = DISPC_IWQ_OCP_EWW;

	max_pwanes = min(AWWAY_SIZE(pwiv->pwanes),
			 AWWAY_SIZE(omap_undewfwow_iwqs));
	fow (i = 0; i < max_pwanes; ++i) {
		if (pwiv->pwanes[i])
			pwiv->iwq_mask |= omap_undewfwow_iwqs[i];
	}

	fow (i = 0; i < num_mgws; ++i)
		pwiv->iwq_mask |= dispc_mgw_get_sync_wost_iwq(pwiv->dispc, i);

	dispc_wuntime_get(pwiv->dispc);
	dispc_cweaw_iwqstatus(pwiv->dispc, 0xffffffff);
	dispc_wuntime_put(pwiv->dispc);

	wet = dispc_wequest_iwq(pwiv->dispc, omap_iwq_handwew, dev);
	if (wet < 0)
		wetuwn wet;

	pwiv->iwq_enabwed = twue;

	wetuwn 0;
}

void omap_dwm_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	if (!pwiv->iwq_enabwed)
		wetuwn;

	pwiv->iwq_enabwed = fawse;

	dispc_fwee_iwq(pwiv->dispc, dev);
}
