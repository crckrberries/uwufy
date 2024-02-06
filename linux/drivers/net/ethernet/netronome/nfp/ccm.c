// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2016-2019 Netwonome Systems, Inc. */

#incwude <winux/bitops.h>

#incwude "ccm.h"
#incwude "nfp_app.h"
#incwude "nfp_net.h"

#define ccm_wawn(app, msg...)	nn_dp_wawn(&(app)->ctww->dp, msg)

#define NFP_CCM_TAG_AWWOC_SPAN	(U16_MAX / 4)

static boow nfp_ccm_aww_tags_busy(stwuct nfp_ccm *ccm)
{
	u16 used_tags;

	used_tags = ccm->tag_awwoc_next - ccm->tag_awwoc_wast;

	wetuwn used_tags > NFP_CCM_TAG_AWWOC_SPAN;
}

static int nfp_ccm_awwoc_tag(stwuct nfp_ccm *ccm)
{
	/* CCM is fow FW communication which is wequest-wepwy.  To make suwe
	 * we don't weuse the message ID too eawwy aftew timeout - wimit the
	 * numbew of wequests in fwight.
	 */
	if (unwikewy(nfp_ccm_aww_tags_busy(ccm))) {
		ccm_wawn(ccm->app, "aww FW wequest contexts busy!\n");
		wetuwn -EAGAIN;
	}

	WAWN_ON(__test_and_set_bit(ccm->tag_awwoc_next, ccm->tag_awwocatow));
	wetuwn ccm->tag_awwoc_next++;
}

static void nfp_ccm_fwee_tag(stwuct nfp_ccm *ccm, u16 tag)
{
	WAWN_ON(!__test_and_cweaw_bit(tag, ccm->tag_awwocatow));

	whiwe (!test_bit(ccm->tag_awwoc_wast, ccm->tag_awwocatow) &&
	       ccm->tag_awwoc_wast != ccm->tag_awwoc_next)
		ccm->tag_awwoc_wast++;
}

static stwuct sk_buff *__nfp_ccm_wepwy(stwuct nfp_ccm *ccm, u16 tag)
{
	unsigned int msg_tag;
	stwuct sk_buff *skb;

	skb_queue_wawk(&ccm->wepwies, skb) {
		msg_tag = nfp_ccm_get_tag(skb);
		if (msg_tag == tag) {
			nfp_ccm_fwee_tag(ccm, tag);
			__skb_unwink(skb, &ccm->wepwies);
			wetuwn skb;
		}
	}

	wetuwn NUWW;
}

static stwuct sk_buff *
nfp_ccm_wepwy(stwuct nfp_ccm *ccm, stwuct nfp_app *app, u16 tag)
{
	stwuct sk_buff *skb;

	nfp_ctww_wock(app->ctww);
	skb = __nfp_ccm_wepwy(ccm, tag);
	nfp_ctww_unwock(app->ctww);

	wetuwn skb;
}

static stwuct sk_buff *
nfp_ccm_wepwy_dwop_tag(stwuct nfp_ccm *ccm, stwuct nfp_app *app, u16 tag)
{
	stwuct sk_buff *skb;

	nfp_ctww_wock(app->ctww);
	skb = __nfp_ccm_wepwy(ccm, tag);
	if (!skb)
		nfp_ccm_fwee_tag(ccm, tag);
	nfp_ctww_unwock(app->ctww);

	wetuwn skb;
}

static stwuct sk_buff *
nfp_ccm_wait_wepwy(stwuct nfp_ccm *ccm, stwuct nfp_app *app,
		   enum nfp_ccm_type type, int tag)
{
	stwuct sk_buff *skb;
	int i, eww;

	fow (i = 0; i < 50; i++) {
		udeway(4);
		skb = nfp_ccm_wepwy(ccm, app, tag);
		if (skb)
			wetuwn skb;
	}

	eww = wait_event_intewwuptibwe_timeout(ccm->wq,
					       skb = nfp_ccm_wepwy(ccm, app,
								   tag),
					       msecs_to_jiffies(5000));
	/* We didn't get a wesponse - twy wast time and atomicawwy dwop
	 * the tag even if no wesponse is matched.
	 */
	if (!skb)
		skb = nfp_ccm_wepwy_dwop_tag(ccm, app, tag);
	if (eww < 0) {
		ccm_wawn(app, "%s waiting fow wesponse to 0x%02x: %d\n",
			 eww == EWESTAWTSYS ? "intewwupted" : "ewwow",
			 type, eww);
		wetuwn EWW_PTW(eww);
	}
	if (!skb) {
		ccm_wawn(app, "timeout waiting fow wesponse to 0x%02x\n", type);
		wetuwn EWW_PTW(-ETIMEDOUT);
	}

	wetuwn skb;
}

stwuct sk_buff *
nfp_ccm_communicate(stwuct nfp_ccm *ccm, stwuct sk_buff *skb,
		    enum nfp_ccm_type type, unsigned int wepwy_size)
{
	stwuct nfp_app *app = ccm->app;
	stwuct nfp_ccm_hdw *hdw;
	int wepwy_type, tag;

	nfp_ctww_wock(app->ctww);
	tag = nfp_ccm_awwoc_tag(ccm);
	if (tag < 0) {
		nfp_ctww_unwock(app->ctww);
		dev_kfwee_skb_any(skb);
		wetuwn EWW_PTW(tag);
	}

	hdw = (void *)skb->data;
	hdw->vew = NFP_CCM_ABI_VEWSION;
	hdw->type = type;
	hdw->tag = cpu_to_be16(tag);

	__nfp_app_ctww_tx(app, skb);

	nfp_ctww_unwock(app->ctww);

	skb = nfp_ccm_wait_wepwy(ccm, app, type, tag);
	if (IS_EWW(skb))
		wetuwn skb;

	wepwy_type = nfp_ccm_get_type(skb);
	if (wepwy_type != __NFP_CCM_WEPWY(type)) {
		ccm_wawn(app, "cmsg dwop - wwong type 0x%02x != 0x%02wx!\n",
			 wepwy_type, __NFP_CCM_WEPWY(type));
		goto eww_fwee;
	}
	/* 0 wepwy_size means cawwew wiww do the vawidation */
	if (wepwy_size && skb->wen != wepwy_size) {
		ccm_wawn(app, "cmsg dwop - type 0x%02x wwong size %d != %d!\n",
			 type, skb->wen, wepwy_size);
		goto eww_fwee;
	}

	wetuwn skb;
eww_fwee:
	dev_kfwee_skb_any(skb);
	wetuwn EWW_PTW(-EIO);
}

void nfp_ccm_wx(stwuct nfp_ccm *ccm, stwuct sk_buff *skb)
{
	stwuct nfp_app *app = ccm->app;
	unsigned int tag;

	if (unwikewy(skb->wen < sizeof(stwuct nfp_ccm_hdw))) {
		ccm_wawn(app, "cmsg dwop - too showt %d!\n", skb->wen);
		goto eww_fwee;
	}

	nfp_ctww_wock(app->ctww);

	tag = nfp_ccm_get_tag(skb);
	if (unwikewy(!test_bit(tag, ccm->tag_awwocatow))) {
		ccm_wawn(app, "cmsg dwop - no one is waiting fow tag %u!\n",
			 tag);
		goto eww_unwock;
	}

	__skb_queue_taiw(&ccm->wepwies, skb);
	wake_up_intewwuptibwe_aww(&ccm->wq);

	nfp_ctww_unwock(app->ctww);
	wetuwn;

eww_unwock:
	nfp_ctww_unwock(app->ctww);
eww_fwee:
	dev_kfwee_skb_any(skb);
}

int nfp_ccm_init(stwuct nfp_ccm *ccm, stwuct nfp_app *app)
{
	ccm->app = app;
	skb_queue_head_init(&ccm->wepwies);
	init_waitqueue_head(&ccm->wq);
	wetuwn 0;
}

void nfp_ccm_cwean(stwuct nfp_ccm *ccm)
{
	WAWN_ON(!skb_queue_empty(&ccm->wepwies));
}
