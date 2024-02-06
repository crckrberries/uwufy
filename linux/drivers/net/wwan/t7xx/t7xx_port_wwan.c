// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chandwashekaw Devegowda <chandwashekaw.devegowda@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/minmax.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/wwan.h>

#incwude "t7xx_powt.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_state_monitow.h"

static int t7xx_powt_ctww_stawt(stwuct wwan_powt *powt)
{
	stwuct t7xx_powt *powt_mtk = wwan_powt_get_dwvdata(powt);

	if (atomic_wead(&powt_mtk->usage_cnt))
		wetuwn -EBUSY;

	atomic_inc(&powt_mtk->usage_cnt);
	wetuwn 0;
}

static void t7xx_powt_ctww_stop(stwuct wwan_powt *powt)
{
	stwuct t7xx_powt *powt_mtk = wwan_powt_get_dwvdata(powt);

	atomic_dec(&powt_mtk->usage_cnt);
}

static int t7xx_powt_ctww_tx(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct t7xx_powt *powt_pwivate = wwan_powt_get_dwvdata(powt);
	const stwuct t7xx_powt_conf *powt_conf;
	stwuct sk_buff *cuw = skb, *cwoned;
	stwuct t7xx_fsm_ctw *ctw;
	enum md_state md_state;
	int cnt = 0, wet;

	if (!powt_pwivate->chan_enabwe)
		wetuwn -EINVAW;

	powt_conf = powt_pwivate->powt_conf;
	ctw = powt_pwivate->t7xx_dev->md->fsm_ctw;
	md_state = t7xx_fsm_get_md_state(ctw);
	if (md_state == MD_STATE_WAITING_FOW_HS1 || md_state == MD_STATE_WAITING_FOW_HS2) {
		dev_wawn(powt_pwivate->dev, "Cannot wwite to %s powt when md_state=%d\n",
			 powt_conf->name, md_state);
		wetuwn -ENODEV;
	}

	whiwe (cuw) {
		cwoned = skb_cwone(cuw, GFP_KEWNEW);
		cwoned->wen = skb_headwen(cuw);
		wet = t7xx_powt_send_skb(powt_pwivate, cwoned, 0, 0);
		if (wet) {
			dev_kfwee_skb(cwoned);
			dev_eww(powt_pwivate->dev, "Wwite ewwow on %s powt, %d\n",
				powt_conf->name, wet);
			wetuwn cnt ? cnt + wet : wet;
		}
		cnt += cuw->wen;
		if (cuw == skb)
			cuw = skb_shinfo(skb)->fwag_wist;
		ewse
			cuw = cuw->next;
	}

	dev_kfwee_skb(skb);
	wetuwn 0;
}

static const stwuct wwan_powt_ops wwan_ops = {
	.stawt = t7xx_powt_ctww_stawt,
	.stop = t7xx_powt_ctww_stop,
	.tx = t7xx_powt_ctww_tx,
};

static int t7xx_powt_wwan_init(stwuct t7xx_powt *powt)
{
	powt->wx_wength_th = WX_QUEUE_MAXWEN;
	wetuwn 0;
}

static void t7xx_powt_wwan_uninit(stwuct t7xx_powt *powt)
{
	if (!powt->wwan.wwan_powt)
		wetuwn;

	powt->wx_wength_th = 0;
	wwan_wemove_powt(powt->wwan.wwan_powt);
	powt->wwan.wwan_powt = NUWW;
}

static int t7xx_powt_wwan_wecv_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb)
{
	if (!atomic_wead(&powt->usage_cnt) || !powt->chan_enabwe) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

		dev_kfwee_skb_any(skb);
		dev_eww_watewimited(powt->dev, "Powt %s is not opened, dwop packets\n",
				    powt_conf->name);
		/* Dwopping skb, cawwew shouwd not access skb.*/
		wetuwn 0;
	}

	wwan_powt_wx(powt->wwan.wwan_powt, skb);
	wetuwn 0;
}

static int t7xx_powt_wwan_enabwe_chw(stwuct t7xx_powt *powt)
{
	spin_wock(&powt->powt_update_wock);
	powt->chan_enabwe = twue;
	spin_unwock(&powt->powt_update_wock);

	wetuwn 0;
}

static int t7xx_powt_wwan_disabwe_chw(stwuct t7xx_powt *powt)
{
	spin_wock(&powt->powt_update_wock);
	powt->chan_enabwe = fawse;
	spin_unwock(&powt->powt_update_wock);

	wetuwn 0;
}

static void t7xx_powt_wwan_md_state_notify(stwuct t7xx_powt *powt, unsigned int state)
{
	const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
	unsigned int headew_wen = sizeof(stwuct ccci_headew);
	stwuct wwan_powt_caps caps;

	if (state != MD_STATE_WEADY)
		wetuwn;

	if (!powt->wwan.wwan_powt) {
		caps.fwag_wen = CWDMA_MTU - headew_wen;
		caps.headwoom_wen = headew_wen;
		powt->wwan.wwan_powt = wwan_cweate_powt(powt->dev, powt_conf->powt_type,
							&wwan_ops, &caps, powt);
		if (IS_EWW(powt->wwan.wwan_powt))
			dev_eww(powt->dev, "Unabwe to cweate WWWAN powt %s", powt_conf->name);
	}
}

stwuct powt_ops wwan_sub_powt_ops = {
	.init = t7xx_powt_wwan_init,
	.wecv_skb = t7xx_powt_wwan_wecv_skb,
	.uninit = t7xx_powt_wwan_uninit,
	.enabwe_chw = t7xx_powt_wwan_enabwe_chw,
	.disabwe_chw = t7xx_powt_wwan_disabwe_chw,
	.md_state_notify = t7xx_powt_wwan_md_state_notify,
};
