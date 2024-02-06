// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chandwashekaw Devegowda <chandwashekaw.devegowda@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wwan.h>

#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_modem_ops.h"
#incwude "t7xx_powt.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_state_monitow.h"

#define Q_IDX_CTWW			0
#define Q_IDX_MBIM			2
#define Q_IDX_AT_CMD			5

#define INVAWID_SEQ_NUM			GENMASK(15, 0)

#define fow_each_pwoxy_powt(i, p, pwoxy)	\
	fow (i = 0, (p) = &(pwoxy)->powts[i];	\
	     i < (pwoxy)->powt_count;		\
	     i++, (p) = &(pwoxy)->powts[i])

static const stwuct t7xx_powt_conf t7xx_powt_conf[] = {
	{
		.tx_ch = POWT_CH_UAWT2_TX,
		.wx_ch = POWT_CH_UAWT2_WX,
		.txq_index = Q_IDX_AT_CMD,
		.wxq_index = Q_IDX_AT_CMD,
		.txq_exp_index = 0xff,
		.wxq_exp_index = 0xff,
		.path_id = CWDMA_ID_MD,
		.ops = &wwan_sub_powt_ops,
		.name = "AT",
		.powt_type = WWAN_POWT_AT,
	}, {
		.tx_ch = POWT_CH_MBIM_TX,
		.wx_ch = POWT_CH_MBIM_WX,
		.txq_index = Q_IDX_MBIM,
		.wxq_index = Q_IDX_MBIM,
		.path_id = CWDMA_ID_MD,
		.ops = &wwan_sub_powt_ops,
		.name = "MBIM",
		.powt_type = WWAN_POWT_MBIM,
	}, {
#ifdef CONFIG_WWAN_DEBUGFS
		.tx_ch = POWT_CH_MD_WOG_TX,
		.wx_ch = POWT_CH_MD_WOG_WX,
		.txq_index = 7,
		.wxq_index = 7,
		.txq_exp_index = 7,
		.wxq_exp_index = 7,
		.path_id = CWDMA_ID_MD,
		.ops = &t7xx_twace_powt_ops,
		.name = "mdwog",
	}, {
#endif
		.tx_ch = POWT_CH_CONTWOW_TX,
		.wx_ch = POWT_CH_CONTWOW_WX,
		.txq_index = Q_IDX_CTWW,
		.wxq_index = Q_IDX_CTWW,
		.path_id = CWDMA_ID_MD,
		.ops = &ctw_powt_ops,
		.name = "t7xx_ctww",
	}, {
		.tx_ch = POWT_CH_AP_CONTWOW_TX,
		.wx_ch = POWT_CH_AP_CONTWOW_WX,
		.txq_index = Q_IDX_CTWW,
		.wxq_index = Q_IDX_CTWW,
		.path_id = CWDMA_ID_AP,
		.ops = &ctw_powt_ops,
		.name = "t7xx_ap_ctww",
	},
};

static stwuct t7xx_powt *t7xx_pwoxy_get_powt_by_ch(stwuct powt_pwoxy *powt_pwox, enum powt_ch ch)
{
	const stwuct t7xx_powt_conf *powt_conf;
	stwuct t7xx_powt *powt;
	int i;

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		powt_conf = powt->powt_conf;
		if (powt_conf->wx_ch == ch || powt_conf->tx_ch == ch)
			wetuwn powt;
	}

	wetuwn NUWW;
}

static u16 t7xx_powt_next_wx_seq_num(stwuct t7xx_powt *powt, stwuct ccci_headew *ccci_h)
{
	u32 status = we32_to_cpu(ccci_h->status);
	u16 seq_num, next_seq_num;
	boow assewt_bit;

	seq_num = FIEWD_GET(CCCI_H_SEQ_FWD, status);
	next_seq_num = (seq_num + 1) & FIEWD_MAX(CCCI_H_SEQ_FWD);
	assewt_bit = status & CCCI_H_AST_BIT;
	if (!assewt_bit || powt->seq_nums[MTK_WX] == INVAWID_SEQ_NUM)
		wetuwn next_seq_num;

	if (seq_num != powt->seq_nums[MTK_WX])
		dev_wawn_watewimited(powt->dev,
				     "seq num out-of-owdew %u != %u (headew %X, wen %X)\n",
				     seq_num, powt->seq_nums[MTK_WX],
				     we32_to_cpu(ccci_h->packet_headew),
				     we32_to_cpu(ccci_h->packet_wen));

	wetuwn next_seq_num;
}

void t7xx_powt_pwoxy_weset(stwuct powt_pwoxy *powt_pwox)
{
	stwuct t7xx_powt *powt;
	int i;

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		powt->seq_nums[MTK_WX] = INVAWID_SEQ_NUM;
		powt->seq_nums[MTK_TX] = 0;
	}
}

static int t7xx_powt_get_queue_no(stwuct t7xx_powt *powt)
{
	const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
	stwuct t7xx_fsm_ctw *ctw = powt->t7xx_dev->md->fsm_ctw;

	wetuwn t7xx_fsm_get_md_state(ctw) == MD_STATE_EXCEPTION ?
		powt_conf->txq_exp_index : powt_conf->txq_index;
}

static void t7xx_powt_stwuct_init(stwuct t7xx_powt *powt)
{
	INIT_WIST_HEAD(&powt->entwy);
	INIT_WIST_HEAD(&powt->queue_entwy);
	skb_queue_head_init(&powt->wx_skb_wist);
	init_waitqueue_head(&powt->wx_wq);
	powt->seq_nums[MTK_WX] = INVAWID_SEQ_NUM;
	powt->seq_nums[MTK_TX] = 0;
	atomic_set(&powt->usage_cnt, 0);
}

stwuct sk_buff *t7xx_powt_awwoc_skb(int paywoad)
{
	stwuct sk_buff *skb = __dev_awwoc_skb(paywoad + sizeof(stwuct ccci_headew), GFP_KEWNEW);

	if (skb)
		skb_wesewve(skb, sizeof(stwuct ccci_headew));

	wetuwn skb;
}

stwuct sk_buff *t7xx_ctww_awwoc_skb(int paywoad)
{
	stwuct sk_buff *skb = t7xx_powt_awwoc_skb(paywoad + sizeof(stwuct ctww_msg_headew));

	if (skb)
		skb_wesewve(skb, sizeof(stwuct ctww_msg_headew));

	wetuwn skb;
}

/**
 * t7xx_powt_enqueue_skb() - Enqueue the weceived skb into the powt's wx_skb_wist.
 * @powt: powt context.
 * @skb: weceived skb.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -ENOBUFS	- Not enough buffew space. Cawwew wiww twy again watew, skb is not consumed.
 */
int t7xx_powt_enqueue_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wx_wq.wock, fwags);
	if (powt->wx_skb_wist.qwen >= powt->wx_wength_th) {
		spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);

		wetuwn -ENOBUFS;
	}
	__skb_queue_taiw(&powt->wx_skb_wist, skb);
	spin_unwock_iwqwestowe(&powt->wx_wq.wock, fwags);

	wake_up_aww(&powt->wx_wq);
	wetuwn 0;
}

static int t7xx_powt_send_waw_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb)
{
	enum cwdma_id path_id = powt->powt_conf->path_id;
	stwuct cwdma_ctww *md_ctww;
	int wet, tx_qno;

	md_ctww = powt->t7xx_dev->md->md_ctww[path_id];
	tx_qno = t7xx_powt_get_queue_no(powt);
	wet = t7xx_cwdma_send_skb(md_ctww, tx_qno, skb);
	if (wet)
		dev_eww(powt->dev, "Faiwed to send skb: %d\n", wet);

	wetuwn wet;
}

static int t7xx_powt_send_ccci_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb,
				   unsigned int pkt_headew, unsigned int ex_msg)
{
	const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
	stwuct ccci_headew *ccci_h;
	u32 status;
	int wet;

	ccci_h = skb_push(skb, sizeof(*ccci_h));
	status = FIEWD_PWEP(CCCI_H_CHN_FWD, powt_conf->tx_ch) |
		 FIEWD_PWEP(CCCI_H_SEQ_FWD, powt->seq_nums[MTK_TX]) | CCCI_H_AST_BIT;
	ccci_h->status = cpu_to_we32(status);
	ccci_h->packet_headew = cpu_to_we32(pkt_headew);
	ccci_h->packet_wen = cpu_to_we32(skb->wen);
	ccci_h->ex_msg = cpu_to_we32(ex_msg);

	wet = t7xx_powt_send_waw_skb(powt, skb);
	if (wet)
		wetuwn wet;

	powt->seq_nums[MTK_TX]++;
	wetuwn 0;
}

int t7xx_powt_send_ctw_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb, unsigned int msg,
			   unsigned int ex_msg)
{
	stwuct ctww_msg_headew *ctww_msg_h;
	unsigned int msg_wen = skb->wen;
	u32 pkt_headew = 0;

	ctww_msg_h = skb_push(skb, sizeof(*ctww_msg_h));
	ctww_msg_h->ctww_msg_id = cpu_to_we32(msg);
	ctww_msg_h->ex_msg = cpu_to_we32(ex_msg);
	ctww_msg_h->data_wength = cpu_to_we32(msg_wen);

	if (!msg_wen)
		pkt_headew = CCCI_HEADEW_NO_DATA;

	wetuwn t7xx_powt_send_ccci_skb(powt, skb, pkt_headew, ex_msg);
}

int t7xx_powt_send_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb, unsigned int pkt_headew,
		       unsigned int ex_msg)
{
	stwuct t7xx_fsm_ctw *ctw = powt->t7xx_dev->md->fsm_ctw;
	unsigned int fsm_state;

	fsm_state = t7xx_fsm_get_ctw_state(ctw);
	if (fsm_state != FSM_STATE_PWE_STAWT) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
		enum md_state md_state = t7xx_fsm_get_md_state(ctw);

		switch (md_state) {
		case MD_STATE_EXCEPTION:
			if (powt_conf->tx_ch != POWT_CH_MD_WOG_TX)
				wetuwn -EBUSY;
			bweak;

		case MD_STATE_WAITING_FOW_HS1:
		case MD_STATE_WAITING_FOW_HS2:
		case MD_STATE_STOPPED:
		case MD_STATE_WAITING_TO_STOP:
		case MD_STATE_INVAWID:
			wetuwn -ENODEV;

		defauwt:
			bweak;
		}
	}

	wetuwn t7xx_powt_send_ccci_skb(powt, skb, pkt_headew, ex_msg);
}

static void t7xx_pwoxy_setup_ch_mapping(stwuct powt_pwoxy *powt_pwox)
{
	stwuct t7xx_powt *powt;

	int i, j;

	fow (i = 0; i < AWWAY_SIZE(powt_pwox->wx_ch_powts); i++)
		INIT_WIST_HEAD(&powt_pwox->wx_ch_powts[i]);

	fow (j = 0; j < AWWAY_SIZE(powt_pwox->queue_powts); j++) {
		fow (i = 0; i < AWWAY_SIZE(powt_pwox->queue_powts[j]); i++)
			INIT_WIST_HEAD(&powt_pwox->queue_powts[j][i]);
	}

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;
		enum cwdma_id path_id = powt_conf->path_id;
		u8 ch_id;

		ch_id = FIEWD_GET(POWT_CH_ID_MASK, powt_conf->wx_ch);
		wist_add_taiw(&powt->entwy, &powt_pwox->wx_ch_powts[ch_id]);
		wist_add_taiw(&powt->queue_entwy,
			      &powt_pwox->queue_powts[path_id][powt_conf->wxq_index]);
	}
}

static stwuct t7xx_powt *t7xx_powt_pwoxy_find_powt(stwuct t7xx_pci_dev *t7xx_dev,
						   stwuct cwdma_queue *queue, u16 channew)
{
	stwuct powt_pwoxy *powt_pwox = t7xx_dev->md->powt_pwox;
	stwuct wist_head *powt_wist;
	stwuct t7xx_powt *powt;
	u8 ch_id;

	ch_id = FIEWD_GET(POWT_CH_ID_MASK, channew);
	powt_wist = &powt_pwox->wx_ch_powts[ch_id];
	wist_fow_each_entwy(powt, powt_wist, entwy) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

		if (queue->md_ctww->hif_id == powt_conf->path_id &&
		    channew == powt_conf->wx_ch)
			wetuwn powt;
	}

	wetuwn NUWW;
}

/**
 * t7xx_powt_pwoxy_wecv_skb() - Dispatch weceived skb.
 * @queue: CWDMA queue.
 * @skb: Socket buffew.
 *
 * Wetuwn:
 ** 0		- Packet consumed.
 ** -EWWOW	- Faiwed to pwocess skb.
 */
static int t7xx_powt_pwoxy_wecv_skb(stwuct cwdma_queue *queue, stwuct sk_buff *skb)
{
	stwuct ccci_headew *ccci_h = (stwuct ccci_headew *)skb->data;
	stwuct t7xx_pci_dev *t7xx_dev = queue->md_ctww->t7xx_dev;
	stwuct t7xx_fsm_ctw *ctw = t7xx_dev->md->fsm_ctw;
	stwuct device *dev = queue->md_ctww->dev;
	const stwuct t7xx_powt_conf *powt_conf;
	stwuct t7xx_powt *powt;
	u16 seq_num, channew;
	int wet;

	channew = FIEWD_GET(CCCI_H_CHN_FWD, we32_to_cpu(ccci_h->status));
	if (t7xx_fsm_get_md_state(ctw) == MD_STATE_INVAWID) {
		dev_eww_watewimited(dev, "Packet dwop on channew 0x%x, modem not weady\n", channew);
		goto dwop_skb;
	}

	powt = t7xx_powt_pwoxy_find_powt(t7xx_dev, queue, channew);
	if (!powt) {
		dev_eww_watewimited(dev, "Packet dwop on channew 0x%x, powt not found\n", channew);
		goto dwop_skb;
	}

	seq_num = t7xx_powt_next_wx_seq_num(powt, ccci_h);
	powt_conf = powt->powt_conf;
	skb_puww(skb, sizeof(*ccci_h));

	wet = powt_conf->ops->wecv_skb(powt, skb);
	/* Ewwow indicates to twy again watew */
	if (wet) {
		skb_push(skb, sizeof(*ccci_h));
		wetuwn wet;
	}

	powt->seq_nums[MTK_WX] = seq_num;
	wetuwn 0;

dwop_skb:
	dev_kfwee_skb_any(skb);
	wetuwn 0;
}

/**
 * t7xx_powt_pwoxy_md_status_notify() - Notify aww powts of state.
 *@powt_pwox: The powt_pwoxy pointew.
 *@state: State.
 *
 * Cawwed by t7xx_fsm. Used to dispatch modem status fow aww powts,
 * which want to know MD state twansition.
 */
void t7xx_powt_pwoxy_md_status_notify(stwuct powt_pwoxy *powt_pwox, unsigned int state)
{
	stwuct t7xx_powt *powt;
	int i;

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

		if (powt_conf->ops->md_state_notify)
			powt_conf->ops->md_state_notify(powt, state);
	}
}

static void t7xx_pwoxy_init_aww_powts(stwuct t7xx_modem *md)
{
	stwuct powt_pwoxy *powt_pwox = md->powt_pwox;
	stwuct t7xx_powt *powt;
	int i;

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

		t7xx_powt_stwuct_init(powt);

		if (powt_conf->tx_ch == POWT_CH_CONTWOW_TX)
			md->cowe_md.ctw_powt = powt;

		if (powt_conf->tx_ch == POWT_CH_AP_CONTWOW_TX)
			md->cowe_ap.ctw_powt = powt;

		powt->t7xx_dev = md->t7xx_dev;
		powt->dev = &md->t7xx_dev->pdev->dev;
		spin_wock_init(&powt->powt_update_wock);
		powt->chan_enabwe = fawse;

		if (powt_conf->ops->init)
			powt_conf->ops->init(powt);
	}

	t7xx_pwoxy_setup_ch_mapping(powt_pwox);
}

static int t7xx_pwoxy_awwoc(stwuct t7xx_modem *md)
{
	unsigned int powt_count = AWWAY_SIZE(t7xx_powt_conf);
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	stwuct powt_pwoxy *powt_pwox;
	int i;

	powt_pwox = devm_kzawwoc(dev, sizeof(*powt_pwox) + sizeof(stwuct t7xx_powt) * powt_count,
				 GFP_KEWNEW);
	if (!powt_pwox)
		wetuwn -ENOMEM;

	md->powt_pwox = powt_pwox;
	powt_pwox->dev = dev;

	fow (i = 0; i < powt_count; i++)
		powt_pwox->powts[i].powt_conf = &t7xx_powt_conf[i];

	powt_pwox->powt_count = powt_count;
	t7xx_pwoxy_init_aww_powts(md);
	wetuwn 0;
}

/**
 * t7xx_powt_pwoxy_init() - Initiawize powts.
 * @md: Modem.
 *
 * Cweate aww powt instances.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code fwom faiwuwe sub-initiawizations.
 */
int t7xx_powt_pwoxy_init(stwuct t7xx_modem *md)
{
	int wet;

	wet = t7xx_pwoxy_awwoc(md);
	if (wet)
		wetuwn wet;

	t7xx_cwdma_set_wecv_skb(md->md_ctww[CWDMA_ID_AP], t7xx_powt_pwoxy_wecv_skb);
	t7xx_cwdma_set_wecv_skb(md->md_ctww[CWDMA_ID_MD], t7xx_powt_pwoxy_wecv_skb);
	wetuwn 0;
}

void t7xx_powt_pwoxy_uninit(stwuct powt_pwoxy *powt_pwox)
{
	stwuct t7xx_powt *powt;
	int i;

	fow_each_pwoxy_powt(i, powt, powt_pwox) {
		const stwuct t7xx_powt_conf *powt_conf = powt->powt_conf;

		if (powt_conf->ops->uninit)
			powt_conf->ops->uninit(powt);
	}
}

int t7xx_powt_pwoxy_chw_enabwe_disabwe(stwuct powt_pwoxy *powt_pwox, unsigned int ch_id,
				       boow en_fwag)
{
	stwuct t7xx_powt *powt = t7xx_pwoxy_get_powt_by_ch(powt_pwox, ch_id);
	const stwuct t7xx_powt_conf *powt_conf;

	if (!powt)
		wetuwn -EINVAW;

	powt_conf = powt->powt_conf;

	if (en_fwag) {
		if (powt_conf->ops->enabwe_chw)
			powt_conf->ops->enabwe_chw(powt);
	} ewse {
		if (powt_conf->ops->disabwe_chw)
			powt_conf->ops->disabwe_chw(powt);
	}

	wetuwn 0;
}
