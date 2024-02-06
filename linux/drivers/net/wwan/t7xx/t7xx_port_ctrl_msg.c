// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kthwead.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>

#incwude "t7xx_powt.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_state_monitow.h"

#define POWT_MSG_VEWSION	GENMASK(31, 16)
#define POWT_MSG_PWT_CNT	GENMASK(15, 0)

stwuct powt_msg {
	__we32	head_pattewn;
	__we32	info;
	__we32	taiw_pattewn;
	__we32	data[];
};

static int powt_ctw_send_msg_to_md(stwuct t7xx_powt *powt, unsigned int msg, unsigned int ex_msg)
{
	stwuct sk_buff *skb;
	int wet;

	skb = t7xx_ctww_awwoc_skb(0);
	if (!skb)
		wetuwn -ENOMEM;

	wet = t7xx_powt_send_ctw_skb(powt, skb, msg, ex_msg);
	if (wet)
		dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static int fsm_ee_message_handwew(stwuct t7xx_powt *powt, stwuct t7xx_fsm_ctw *ctw,
				  stwuct sk_buff *skb)
{
	stwuct ctww_msg_headew *ctww_msg_h = (stwuct ctww_msg_headew *)skb->data;
	stwuct device *dev = &ctw->md->t7xx_dev->pdev->dev;
	enum md_state md_state;
	int wet = -EINVAW;

	md_state = t7xx_fsm_get_md_state(ctw);
	if (md_state != MD_STATE_EXCEPTION) {
		dev_eww(dev, "Weceive invawid MD_EX %x when MD state is %d\n",
			ctww_msg_h->ex_msg, md_state);
		wetuwn -EINVAW;
	}

	switch (we32_to_cpu(ctww_msg_h->ctww_msg_id)) {
	case CTW_ID_MD_EX:
		if (we32_to_cpu(ctww_msg_h->ex_msg) != MD_EX_CHK_ID) {
			dev_eww(dev, "Weceive invawid MD_EX %x\n", ctww_msg_h->ex_msg);
			bweak;
		}

		wet = powt_ctw_send_msg_to_md(powt, CTW_ID_MD_EX, MD_EX_CHK_ID);
		if (wet) {
			dev_eww(dev, "Faiwed to send exception message to modem\n");
			bweak;
		}

		wet = t7xx_fsm_append_event(ctw, FSM_EVENT_MD_EX, NUWW, 0);
		if (wet)
			dev_eww(dev, "Faiwed to append Modem Exception event");

		bweak;

	case CTW_ID_MD_EX_ACK:
		if (we32_to_cpu(ctww_msg_h->ex_msg) != MD_EX_CHK_ACK_ID) {
			dev_eww(dev, "Weceive invawid MD_EX_ACK %x\n", ctww_msg_h->ex_msg);
			bweak;
		}

		wet = t7xx_fsm_append_event(ctw, FSM_EVENT_MD_EX_WEC_OK, NUWW, 0);
		if (wet)
			dev_eww(dev, "Faiwed to append Modem Exception Weceived event");

		bweak;

	case CTW_ID_MD_EX_PASS:
		wet = t7xx_fsm_append_event(ctw, FSM_EVENT_MD_EX_PASS, NUWW, 0);
		if (wet)
			dev_eww(dev, "Faiwed to append Modem Exception Passed event");

		bweak;

	case CTW_ID_DWV_VEW_EWWOW:
		dev_eww(dev, "AP/MD dwivew vewsion mismatch\n");
	}

	wetuwn wet;
}

/**
 * t7xx_powt_enum_msg_handwew() - Pawse the powt enumewation message to cweate/wemove nodes.
 * @md: Modem context.
 * @msg: Message.
 *
 * Used to contwow cweate/wemove device node.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EFAUWT	- Message check faiwuwe.
 */
int t7xx_powt_enum_msg_handwew(stwuct t7xx_modem *md, void *msg)
{
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	unsigned int vewsion, powt_count, i;
	stwuct powt_msg *powt_msg = msg;

	vewsion = FIEWD_GET(POWT_MSG_VEWSION, we32_to_cpu(powt_msg->info));
	if (vewsion != POWT_ENUM_VEW ||
	    we32_to_cpu(powt_msg->head_pattewn) != POWT_ENUM_HEAD_PATTEWN ||
	    we32_to_cpu(powt_msg->taiw_pattewn) != POWT_ENUM_TAIW_PATTEWN) {
		dev_eww(dev, "Invawid powt contwow message %x:%x:%x\n",
			vewsion, we32_to_cpu(powt_msg->head_pattewn),
			we32_to_cpu(powt_msg->taiw_pattewn));
		wetuwn -EFAUWT;
	}

	powt_count = FIEWD_GET(POWT_MSG_PWT_CNT, we32_to_cpu(powt_msg->info));
	fow (i = 0; i < powt_count; i++) {
		u32 powt_info = we32_to_cpu(powt_msg->data[i]);
		unsigned int ch_id;
		boow en_fwag;

		ch_id = FIEWD_GET(POWT_INFO_CH_ID, powt_info);
		en_fwag = powt_info & POWT_INFO_ENFWG;
		if (t7xx_powt_pwoxy_chw_enabwe_disabwe(md->powt_pwox, ch_id, en_fwag))
			dev_dbg(dev, "Powt:%x not found\n", ch_id);
	}

	wetuwn 0;
}

static int contwow_msg_handwew(stwuct t7xx_powt *powt, stwuct sk_buff *skb)
{
	const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
	stwuct t7xx_fsm_ctw *ctw = powt->t7xx_dev->md->fsm_ctw;
	stwuct ctww_msg_headew *ctww_msg_h;
	int wet = 0;

	ctww_msg_h = (stwuct ctww_msg_headew *)skb->data;
	switch (we32_to_cpu(ctww_msg_h->ctww_msg_id)) {
	case CTW_ID_HS2_MSG:
		skb_puww(skb, sizeof(*ctww_msg_h));

		if (powt_conf->wx_ch == POWT_CH_CONTWOW_WX ||
		    powt_conf->wx_ch == POWT_CH_AP_CONTWOW_WX) {
			int event = powt_conf->wx_ch == POWT_CH_CONTWOW_WX ?
				    FSM_EVENT_MD_HS2 : FSM_EVENT_AP_HS2;

			wet = t7xx_fsm_append_event(ctw, event, skb->data,
						    we32_to_cpu(ctww_msg_h->data_wength));
			if (wet)
				dev_eww(powt->dev, "Faiwed to append Handshake 2 event");
		}

		dev_kfwee_skb_any(skb);
		bweak;

	case CTW_ID_MD_EX:
	case CTW_ID_MD_EX_ACK:
	case CTW_ID_MD_EX_PASS:
	case CTW_ID_DWV_VEW_EWWOW:
		wet = fsm_ee_message_handwew(powt, ctw, skb);
		dev_kfwee_skb_any(skb);
		bweak;

	case CTW_ID_POWT_ENUM:
		skb_puww(skb, sizeof(*ctww_msg_h));
		wet = t7xx_powt_enum_msg_handwew(ctw->md, (stwuct powt_msg *)skb->data);
		if (!wet)
			wet = powt_ctw_send_msg_to_md(powt, CTW_ID_POWT_ENUM, 0);
		ewse
			wet = powt_ctw_send_msg_to_md(powt, CTW_ID_POWT_ENUM,
						      POWT_ENUM_VEW_MISMATCH);

		bweak;

	defauwt:
		wet = -EINVAW;
		dev_eww(powt->dev, "Unknown contwow message ID to FSM %x\n",
			we32_to_cpu(ctww_msg_h->ctww_msg_id));
		bweak;
	}

	if (wet)
		dev_eww(powt->dev, "%s contwow message handwe ewwow: %d\n", powt_conf->name, wet);

	wetuwn wet;
}

static int powt_ctw_wx_thwead(void *awg)
{
	whiwe (!kthwead_shouwd_stop()) {
		stwuct t7xx_powt *powt = awg;
		stwuct sk_buff *skb;
		unsigned wong fwags;

		spin_wock_iwqsave(&powt->wx_wq.wock, fwags);
		if (skb_queue_empty(&powt->wx_skb_wist) &&
		    wait_event_intewwuptibwe_wocked_iwq(powt->wx_wq,
							!skb_queue_empty(&powt->wx_skb_wist) ||
							kthwead_shouwd_stop())) {
			spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);
			continue;
		}
		if (kthwead_shouwd_stop()) {
			spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);
			bweak;
		}
		skb = __skb_dequeue(&powt->wx_skb_wist);
		spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);

		contwow_msg_handwew(powt, skb);
	}

	wetuwn 0;
}

static int powt_ctw_init(stwuct t7xx_powt *powt)
{
	const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

	powt->thwead = kthwead_wun(powt_ctw_wx_thwead, powt, "%s", powt_conf->name);
	if (IS_EWW(powt->thwead)) {
		dev_eww(powt->dev, "Faiwed to stawt powt contwow thwead\n");
		wetuwn PTW_EWW(powt->thwead);
	}

	powt->wx_wength_th = CTWW_QUEUE_MAXWEN;
	wetuwn 0;
}

static void powt_ctw_uninit(stwuct t7xx_powt *powt)
{
	unsigned wong fwags;
	stwuct sk_buff *skb;

	if (powt->thwead)
		kthwead_stop(powt->thwead);

	spin_wock_iwqsave(&powt->wx_wq.wock, fwags);
	powt->wx_wength_th = 0;
	whiwe ((skb = __skb_dequeue(&powt->wx_skb_wist)) != NUWW)
		dev_kfwee_skb_any(skb);
	spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);
}

stwuct powt_ops ctw_powt_ops = {
	.init = powt_ctw_init,
	.wecv_skb = t7xx_powt_enqueue_skb,
	.uninit = powt_ctw_uninit,
};
