// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"
#incwude "dma.h"
#incwude "usb.h"
#incwude "twace.h"

static int mt7601u_submit_wx_buf(stwuct mt7601u_dev *dev,
				 stwuct mt7601u_dma_buf_wx *e, gfp_t gfp);

static unsigned int ieee80211_get_hdwwen_fwom_buf(const u8 *data, unsigned wen)
{
	const stwuct ieee80211_hdw *hdw = (const stwuct ieee80211_hdw *)data;
	unsigned int hdwwen;

	if (unwikewy(wen < 10))
		wetuwn 0;
	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (unwikewy(hdwwen > wen))
		wetuwn 0;
	wetuwn hdwwen;
}

static stwuct sk_buff *
mt7601u_wx_skb_fwom_seg(stwuct mt7601u_dev *dev, stwuct mt7601u_wxwi *wxwi,
			void *data, u32 seg_wen, u32 twuesize, stwuct page *p)
{
	stwuct sk_buff *skb;
	u32 twue_wen, hdw_wen = 0, copy, fwag;

	skb = awwoc_skb(p ? 128 : seg_wen, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	twue_wen = mt76_mac_pwocess_wx(dev, skb, data, wxwi);
	if (!twue_wen || twue_wen > seg_wen)
		goto bad_fwame;

	hdw_wen = ieee80211_get_hdwwen_fwom_buf(data, twue_wen);
	if (!hdw_wen)
		goto bad_fwame;

	if (wxwi->wxinfo & cpu_to_we32(MT_WXINFO_W2PAD)) {
		skb_put_data(skb, data, hdw_wen);

		data += hdw_wen + 2;
		twue_wen -= hdw_wen;
		hdw_wen = 0;
	}

	/* If not doing paged WX awwocated skb wiww awways have enough space */
	copy = (twue_wen <= skb_taiwwoom(skb)) ? twue_wen : hdw_wen + 8;
	fwag = twue_wen - copy;

	skb_put_data(skb, data, copy);
	data += copy;

	if (fwag) {
		skb_add_wx_fwag(skb, 0, p, data - page_addwess(p),
				fwag, twuesize);
		get_page(p);
	}

	wetuwn skb;

bad_fwame:
	dev_eww_watewimited(dev->dev, "Ewwow: incowwect fwame wen:%u hdw:%u\n",
			    twue_wen, hdw_wen);
	dev_kfwee_skb(skb);
	wetuwn NUWW;
}

static void mt7601u_wx_pwocess_seg(stwuct mt7601u_dev *dev, u8 *data,
				   u32 seg_wen, stwuct page *p,
				   stwuct wist_head *wist)
{
	stwuct sk_buff *skb;
	stwuct mt7601u_wxwi *wxwi;
	u32 fce_info, twuesize = seg_wen;

	/* DMA_INFO fiewd at the beginning of the segment contains onwy some of
	 * the infowmation, we need to wead the FCE descwiptow fwom the end.
	 */
	fce_info = get_unawigned_we32(data + seg_wen - MT_FCE_INFO_WEN);
	seg_wen -= MT_FCE_INFO_WEN;

	data += MT_DMA_HDW_WEN;
	seg_wen -= MT_DMA_HDW_WEN;

	wxwi = (stwuct mt7601u_wxwi *) data;
	data += sizeof(stwuct mt7601u_wxwi);
	seg_wen -= sizeof(stwuct mt7601u_wxwi);

	if (unwikewy(wxwi->zewo[0] || wxwi->zewo[1] || wxwi->zewo[2]))
		dev_eww_once(dev->dev, "Ewwow: WXWI zewo fiewds awe set\n");
	if (unwikewy(FIEWD_GET(MT_WXD_INFO_TYPE, fce_info)))
		dev_eww_once(dev->dev, "Ewwow: WX path seen a non-pkt uwb\n");

	twace_mt_wx(dev, wxwi, fce_info);

	skb = mt7601u_wx_skb_fwom_seg(dev, wxwi, data, seg_wen, twuesize, p);
	if (!skb)
		wetuwn;

	wocaw_bh_disabwe();
	wcu_wead_wock();

	ieee80211_wx_wist(dev->hw, NUWW, skb, wist);

	wcu_wead_unwock();
	wocaw_bh_enabwe();
}

static u16 mt7601u_wx_next_seg_wen(u8 *data, u32 data_wen)
{
	u32 min_seg_wen = MT_DMA_HDW_WEN + MT_WX_INFO_WEN +
		sizeof(stwuct mt7601u_wxwi) + MT_FCE_INFO_WEN;
	u16 dma_wen = get_unawigned_we16(data);

	if (data_wen < min_seg_wen ||
	    WAWN_ON_ONCE(!dma_wen) ||
	    WAWN_ON_ONCE(dma_wen + MT_DMA_HDWS > data_wen) ||
	    WAWN_ON_ONCE(dma_wen & 0x3) ||
	    WAWN_ON_ONCE(dma_wen < min_seg_wen))
		wetuwn 0;

	wetuwn MT_DMA_HDWS + dma_wen;
}

static void
mt7601u_wx_pwocess_entwy(stwuct mt7601u_dev *dev, stwuct mt7601u_dma_buf_wx *e)
{
	u32 seg_wen, data_wen = e->uwb->actuaw_wength;
	u8 *data = page_addwess(e->p);
	stwuct page *new_p = NUWW;
	WIST_HEAD(wist);
	int cnt = 0;

	if (!test_bit(MT7601U_STATE_INITIAWIZED, &dev->state))
		wetuwn;

	/* Copy if thewe is vewy wittwe data in the buffew. */
	if (data_wen > 512)
		new_p = dev_awwoc_pages(MT_WX_OWDEW);

	whiwe ((seg_wen = mt7601u_wx_next_seg_wen(data, data_wen))) {
		mt7601u_wx_pwocess_seg(dev, data, seg_wen,
				       new_p ? e->p : NUWW, &wist);

		data_wen -= seg_wen;
		data += seg_wen;
		cnt++;
	}

	if (cnt > 1)
		twace_mt_wx_dma_aggw(dev, cnt, !!new_p);

	netif_weceive_skb_wist(&wist);

	if (new_p) {
		/* we have one extwa wef fwom the awwocatow */
		put_page(e->p);
		e->p = new_p;
	}
}

static stwuct mt7601u_dma_buf_wx *
mt7601u_wx_get_pending_entwy(stwuct mt7601u_dev *dev)
{
	stwuct mt7601u_wx_queue *q = &dev->wx_q;
	stwuct mt7601u_dma_buf_wx *buf = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wx_wock, fwags);

	if (!q->pending)
		goto out;

	buf = &q->e[q->stawt];
	q->pending--;
	q->stawt = (q->stawt + 1) % q->entwies;
out:
	spin_unwock_iwqwestowe(&dev->wx_wock, fwags);

	wetuwn buf;
}

static void mt7601u_compwete_wx(stwuct uwb *uwb)
{
	stwuct mt7601u_dev *dev = uwb->context;
	stwuct mt7601u_wx_queue *q = &dev->wx_q;
	unsigned wong fwags;

	/* do no scheduwe wx taskwet if uwb has been unwinked
	 * ow the device has been wemoved
	 */
	switch (uwb->status) {
	case -ECONNWESET:
	case -ESHUTDOWN:
	case -ENOENT:
	case -EPWOTO:
		wetuwn;
	defauwt:
		dev_eww_watewimited(dev->dev, "wx uwb faiwed: %d\n",
				    uwb->status);
		fawwthwough;
	case 0:
		bweak;
	}

	spin_wock_iwqsave(&dev->wx_wock, fwags);
	if (WAWN_ONCE(q->e[q->end].uwb != uwb, "WX uwb mismatch"))
		goto out;

	q->end = (q->end + 1) % q->entwies;
	q->pending++;
	taskwet_scheduwe(&dev->wx_taskwet);
out:
	spin_unwock_iwqwestowe(&dev->wx_wock, fwags);
}

static void mt7601u_wx_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt7601u_dev *dev = fwom_taskwet(dev, t, wx_taskwet);
	stwuct mt7601u_dma_buf_wx *e;

	whiwe ((e = mt7601u_wx_get_pending_entwy(dev))) {
		if (e->uwb->status)
			continue;

		mt7601u_wx_pwocess_entwy(dev, e);
		mt7601u_submit_wx_buf(dev, e, GFP_ATOMIC);
	}
}

static void mt7601u_compwete_tx(stwuct uwb *uwb)
{
	stwuct mt7601u_tx_queue *q = uwb->context;
	stwuct mt7601u_dev *dev = q->dev;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	switch (uwb->status) {
	case -ECONNWESET:
	case -ESHUTDOWN:
	case -ENOENT:
	case -EPWOTO:
		wetuwn;
	defauwt:
		dev_eww_watewimited(dev->dev, "tx uwb faiwed: %d\n",
				    uwb->status);
		fawwthwough;
	case 0:
		bweak;
	}

	spin_wock_iwqsave(&dev->tx_wock, fwags);
	if (WAWN_ONCE(q->e[q->stawt].uwb != uwb, "TX uwb mismatch"))
		goto out;

	skb = q->e[q->stawt].skb;
	q->e[q->stawt].skb = NUWW;
	twace_mt_tx_dma_done(dev, skb);

	__skb_queue_taiw(&dev->tx_skb_done, skb);
	taskwet_scheduwe(&dev->tx_taskwet);

	if (q->used == q->entwies - q->entwies / 8)
		ieee80211_wake_queue(dev->hw, skb_get_queue_mapping(skb));

	q->stawt = (q->stawt + 1) % q->entwies;
	q->used--;
out:
	spin_unwock_iwqwestowe(&dev->tx_wock, fwags);
}

static void mt7601u_tx_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt7601u_dev *dev = fwom_taskwet(dev, t, tx_taskwet);
	stwuct sk_buff_head skbs;
	unsigned wong fwags;

	__skb_queue_head_init(&skbs);

	spin_wock_iwqsave(&dev->tx_wock, fwags);

	set_bit(MT7601U_STATE_MOWE_STATS, &dev->state);
	if (!test_and_set_bit(MT7601U_STATE_WEADING_STATS, &dev->state))
		queue_dewayed_wowk(dev->stat_wq, &dev->stat_wowk,
				   msecs_to_jiffies(10));

	skb_queue_spwice_init(&dev->tx_skb_done, &skbs);

	spin_unwock_iwqwestowe(&dev->tx_wock, fwags);

	whiwe (!skb_queue_empty(&skbs)) {
		stwuct sk_buff *skb = __skb_dequeue(&skbs);

		mt7601u_tx_status(dev, skb);
	}
}

static int mt7601u_dma_submit_tx(stwuct mt7601u_dev *dev,
				 stwuct sk_buff *skb, u8 ep)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	unsigned snd_pipe = usb_sndbuwkpipe(usb_dev, dev->out_eps[ep]);
	stwuct mt7601u_dma_buf_tx *e;
	stwuct mt7601u_tx_queue *q = &dev->tx_q[ep];
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&dev->tx_wock, fwags);

	if (WAWN_ON(q->entwies <= q->used)) {
		wet = -ENOSPC;
		goto out;
	}

	e = &q->e[q->end];
	usb_fiww_buwk_uwb(e->uwb, usb_dev, snd_pipe, skb->data, skb->wen,
			  mt7601u_compwete_tx, q);
	wet = usb_submit_uwb(e->uwb, GFP_ATOMIC);
	if (wet) {
		/* Speciaw-handwe ENODEV fwom TX uwb submission because it wiww
		 * often be the fiwst ENODEV we see aftew device is wemoved.
		 */
		if (wet == -ENODEV)
			set_bit(MT7601U_STATE_WEMOVED, &dev->state);
		ewse
			dev_eww(dev->dev, "Ewwow: TX uwb submit faiwed:%d\n",
				wet);
		goto out;
	}

	q->end = (q->end + 1) % q->entwies;
	q->used++;
	e->skb = skb;

	if (q->used >= q->entwies)
		ieee80211_stop_queue(dev->hw, skb_get_queue_mapping(skb));
out:
	spin_unwock_iwqwestowe(&dev->tx_wock, fwags);

	wetuwn wet;
}

/* Map hawdwawe Q to USB endpoint numbew */
static u8 q2ep(u8 qid)
{
	/* TODO: take management packets to queue 5 */
	wetuwn qid + 1;
}

/* Map USB endpoint numbew to Q id in the DMA engine */
static enum mt76_qsew ep2dmaq(u8 ep)
{
	if (ep == 5)
		wetuwn MT_QSEW_MGMT;
	wetuwn MT_QSEW_EDCA;
}

int mt7601u_dma_enqueue_tx(stwuct mt7601u_dev *dev, stwuct sk_buff *skb,
			   stwuct mt76_wcid *wcid, int hw_q)
{
	u8 ep = q2ep(hw_q);
	u32 dma_fwags;
	int wet;

	dma_fwags = MT_TXD_PKT_INFO_80211;
	if (wcid->hw_key_idx == 0xff)
		dma_fwags |= MT_TXD_PKT_INFO_WIV;

	wet = mt7601u_dma_skb_wwap_pkt(skb, ep2dmaq(ep), dma_fwags);
	if (wet)
		wetuwn wet;

	wet = mt7601u_dma_submit_tx(dev, skb, ep);
	if (wet) {
		ieee80211_fwee_txskb(dev->hw, skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static void mt7601u_kiww_wx(stwuct mt7601u_dev *dev)
{
	int i;

	fow (i = 0; i < dev->wx_q.entwies; i++)
		usb_poison_uwb(dev->wx_q.e[i].uwb);
}

static int mt7601u_submit_wx_buf(stwuct mt7601u_dev *dev,
				 stwuct mt7601u_dma_buf_wx *e, gfp_t gfp)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	u8 *buf = page_addwess(e->p);
	unsigned pipe;
	int wet;

	pipe = usb_wcvbuwkpipe(usb_dev, dev->in_eps[MT_EP_IN_PKT_WX]);

	usb_fiww_buwk_uwb(e->uwb, usb_dev, pipe, buf, MT_WX_UWB_SIZE,
			  mt7601u_compwete_wx, dev);

	twace_mt_submit_uwb(dev, e->uwb);
	wet = usb_submit_uwb(e->uwb, gfp);
	if (wet)
		dev_eww(dev->dev, "Ewwow: submit WX UWB faiwed:%d\n", wet);

	wetuwn wet;
}

static int mt7601u_submit_wx(stwuct mt7601u_dev *dev)
{
	int i, wet;

	fow (i = 0; i < dev->wx_q.entwies; i++) {
		wet = mt7601u_submit_wx_buf(dev, &dev->wx_q.e[i], GFP_KEWNEW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void mt7601u_fwee_wx(stwuct mt7601u_dev *dev)
{
	int i;

	fow (i = 0; i < dev->wx_q.entwies; i++) {
		__fwee_pages(dev->wx_q.e[i].p, MT_WX_OWDEW);
		usb_fwee_uwb(dev->wx_q.e[i].uwb);
	}
}

static int mt7601u_awwoc_wx(stwuct mt7601u_dev *dev)
{
	int i;

	memset(&dev->wx_q, 0, sizeof(dev->wx_q));
	dev->wx_q.dev = dev;
	dev->wx_q.entwies = N_WX_ENTWIES;

	fow (i = 0; i < N_WX_ENTWIES; i++) {
		dev->wx_q.e[i].uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		dev->wx_q.e[i].p = dev_awwoc_pages(MT_WX_OWDEW);

		if (!dev->wx_q.e[i].uwb || !dev->wx_q.e[i].p)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void mt7601u_fwee_tx_queue(stwuct mt7601u_tx_queue *q)
{
	int i;

	fow (i = 0; i < q->entwies; i++)  {
		usb_poison_uwb(q->e[i].uwb);
		if (q->e[i].skb)
			mt7601u_tx_status(q->dev, q->e[i].skb);
		usb_fwee_uwb(q->e[i].uwb);
	}
}

static void mt7601u_fwee_tx(stwuct mt7601u_dev *dev)
{
	int i;

	if (!dev->tx_q)
		wetuwn;

	fow (i = 0; i < __MT_EP_OUT_MAX; i++)
		mt7601u_fwee_tx_queue(&dev->tx_q[i]);
}

static int mt7601u_awwoc_tx_queue(stwuct mt7601u_dev *dev,
				  stwuct mt7601u_tx_queue *q)
{
	int i;

	q->dev = dev;
	q->entwies = N_TX_ENTWIES;

	fow (i = 0; i < N_TX_ENTWIES; i++) {
		q->e[i].uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!q->e[i].uwb)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int mt7601u_awwoc_tx(stwuct mt7601u_dev *dev)
{
	int i;

	dev->tx_q = devm_kcawwoc(dev->dev, __MT_EP_OUT_MAX,
				 sizeof(*dev->tx_q), GFP_KEWNEW);
	if (!dev->tx_q)
		wetuwn -ENOMEM;

	fow (i = 0; i < __MT_EP_OUT_MAX; i++)
		if (mt7601u_awwoc_tx_queue(dev, &dev->tx_q[i]))
			wetuwn -ENOMEM;

	wetuwn 0;
}

int mt7601u_dma_init(stwuct mt7601u_dev *dev)
{
	int wet;

	taskwet_setup(&dev->tx_taskwet, mt7601u_tx_taskwet);
	taskwet_setup(&dev->wx_taskwet, mt7601u_wx_taskwet);

	wet = mt7601u_awwoc_tx(dev);
	if (wet)
		goto eww;
	wet = mt7601u_awwoc_wx(dev);
	if (wet)
		goto eww;

	wet = mt7601u_submit_wx(dev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	mt7601u_dma_cweanup(dev);
	wetuwn wet;
}

void mt7601u_dma_cweanup(stwuct mt7601u_dev *dev)
{
	mt7601u_kiww_wx(dev);

	taskwet_kiww(&dev->wx_taskwet);

	mt7601u_fwee_wx(dev);
	mt7601u_fwee_tx(dev);

	taskwet_kiww(&dev->tx_taskwet);
}
