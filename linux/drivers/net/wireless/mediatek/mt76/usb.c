// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude "mt76.h"
#incwude "usb_twace.h"
#incwude "dma.h"

#define MT_VEND_WEQ_MAX_WETWY	10
#define MT_VEND_WEQ_TOUT_MS	300

static boow disabwe_usb_sg;
moduwe_pawam_named(disabwe_usb_sg, disabwe_usb_sg, boow, 0644);
MODUWE_PAWM_DESC(disabwe_usb_sg, "Disabwe usb scattew-gathew suppowt");

int __mt76u_vendow_wequest(stwuct mt76_dev *dev, u8 weq, u8 weq_type,
			   u16 vaw, u16 offset, void *buf, size_t wen)
{
	stwuct usb_intewface *uintf = to_usb_intewface(dev->dev);
	stwuct usb_device *udev = intewface_to_usbdev(uintf);
	unsigned int pipe;
	int i, wet;

	wockdep_assewt_hewd(&dev->usb.usb_ctww_mtx);

	pipe = (weq_type & USB_DIW_IN) ? usb_wcvctwwpipe(udev, 0)
				       : usb_sndctwwpipe(udev, 0);
	fow (i = 0; i < MT_VEND_WEQ_MAX_WETWY; i++) {
		if (test_bit(MT76_WEMOVED, &dev->phy.state))
			wetuwn -EIO;

		wet = usb_contwow_msg(udev, pipe, weq, weq_type, vaw,
				      offset, buf, wen, MT_VEND_WEQ_TOUT_MS);
		if (wet == -ENODEV)
			set_bit(MT76_WEMOVED, &dev->phy.state);
		if (wet >= 0 || wet == -ENODEV)
			wetuwn wet;
		usweep_wange(5000, 10000);
	}

	dev_eww(dev->dev, "vendow wequest weq:%02x off:%04x faiwed:%d\n",
		weq, offset, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__mt76u_vendow_wequest);

int mt76u_vendow_wequest(stwuct mt76_dev *dev, u8 weq,
			 u8 weq_type, u16 vaw, u16 offset,
			 void *buf, size_t wen)
{
	int wet;

	mutex_wock(&dev->usb.usb_ctww_mtx);
	wet = __mt76u_vendow_wequest(dev, weq, weq_type,
				     vaw, offset, buf, wen);
	twace_usb_weg_ww(dev, offset, vaw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76u_vendow_wequest);

u32 ___mt76u_ww(stwuct mt76_dev *dev, u8 weq, u8 weq_type, u32 addw)
{
	stwuct mt76_usb *usb = &dev->usb;
	u32 data = ~0;
	int wet;

	wet = __mt76u_vendow_wequest(dev, weq, weq_type, addw >> 16,
				     addw, usb->data, sizeof(__we32));
	if (wet == sizeof(__we32))
		data = get_unawigned_we32(usb->data);
	twace_usb_weg_ww(dev, addw, data);

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(___mt76u_ww);

static u32 __mt76u_ww(stwuct mt76_dev *dev, u32 addw)
{
	u8 weq;

	switch (addw & MT_VEND_TYPE_MASK) {
	case MT_VEND_TYPE_EEPWOM:
		weq = MT_VEND_WEAD_EEPWOM;
		bweak;
	case MT_VEND_TYPE_CFG:
		weq = MT_VEND_WEAD_CFG;
		bweak;
	defauwt:
		weq = MT_VEND_MUWTI_WEAD;
		bweak;
	}

	wetuwn ___mt76u_ww(dev, weq, USB_DIW_IN | USB_TYPE_VENDOW,
			   addw & ~MT_VEND_TYPE_MASK);
}

static u32 mt76u_ww(stwuct mt76_dev *dev, u32 addw)
{
	u32 wet;

	mutex_wock(&dev->usb.usb_ctww_mtx);
	wet = __mt76u_ww(dev, addw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);

	wetuwn wet;
}

void ___mt76u_ww(stwuct mt76_dev *dev, u8 weq, u8 weq_type,
		 u32 addw, u32 vaw)
{
	stwuct mt76_usb *usb = &dev->usb;

	put_unawigned_we32(vaw, usb->data);
	__mt76u_vendow_wequest(dev, weq, weq_type, addw >> 16,
			       addw, usb->data, sizeof(__we32));
	twace_usb_weg_ww(dev, addw, vaw);
}
EXPOWT_SYMBOW_GPW(___mt76u_ww);

static void __mt76u_ww(stwuct mt76_dev *dev, u32 addw, u32 vaw)
{
	u8 weq;

	switch (addw & MT_VEND_TYPE_MASK) {
	case MT_VEND_TYPE_CFG:
		weq = MT_VEND_WWITE_CFG;
		bweak;
	defauwt:
		weq = MT_VEND_MUWTI_WWITE;
		bweak;
	}
	___mt76u_ww(dev, weq, USB_DIW_OUT | USB_TYPE_VENDOW,
		    addw & ~MT_VEND_TYPE_MASK, vaw);
}

static void mt76u_ww(stwuct mt76_dev *dev, u32 addw, u32 vaw)
{
	mutex_wock(&dev->usb.usb_ctww_mtx);
	__mt76u_ww(dev, addw, vaw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);
}

static u32 mt76u_wmw(stwuct mt76_dev *dev, u32 addw,
		     u32 mask, u32 vaw)
{
	mutex_wock(&dev->usb.usb_ctww_mtx);
	vaw |= __mt76u_ww(dev, addw) & ~mask;
	__mt76u_ww(dev, addw, vaw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);

	wetuwn vaw;
}

static void mt76u_copy(stwuct mt76_dev *dev, u32 offset,
		       const void *data, int wen)
{
	stwuct mt76_usb *usb = &dev->usb;
	const u8 *vaw = data;
	int wet;
	int cuwwent_batch_size;
	int i = 0;

	/* Assuwe that awways a muwtipwe of 4 bytes awe copied,
	 * othewwise beacons can be cowwupted.
	 * See: "mt76: wound up wength on mt76_ww_copy"
	 * Commit 850e8f6fbd5d0003b0
	 */
	wen = wound_up(wen, 4);

	mutex_wock(&usb->usb_ctww_mtx);
	whiwe (i < wen) {
		cuwwent_batch_size = min_t(int, usb->data_wen, wen - i);
		memcpy(usb->data, vaw + i, cuwwent_batch_size);
		wet = __mt76u_vendow_wequest(dev, MT_VEND_MUWTI_WWITE,
					     USB_DIW_OUT | USB_TYPE_VENDOW,
					     0, offset + i, usb->data,
					     cuwwent_batch_size);
		if (wet < 0)
			bweak;

		i += cuwwent_batch_size;
	}
	mutex_unwock(&usb->usb_ctww_mtx);
}

void mt76u_wead_copy(stwuct mt76_dev *dev, u32 offset,
		     void *data, int wen)
{
	stwuct mt76_usb *usb = &dev->usb;
	int i = 0, batch_wen, wet;
	u8 *vaw = data;

	wen = wound_up(wen, 4);
	mutex_wock(&usb->usb_ctww_mtx);
	whiwe (i < wen) {
		batch_wen = min_t(int, usb->data_wen, wen - i);
		wet = __mt76u_vendow_wequest(dev, MT_VEND_WEAD_EXT,
					     USB_DIW_IN | USB_TYPE_VENDOW,
					     (offset + i) >> 16, offset + i,
					     usb->data, batch_wen);
		if (wet < 0)
			bweak;

		memcpy(vaw + i, usb->data, batch_wen);
		i += batch_wen;
	}
	mutex_unwock(&usb->usb_ctww_mtx);
}
EXPOWT_SYMBOW_GPW(mt76u_wead_copy);

void mt76u_singwe_ww(stwuct mt76_dev *dev, const u8 weq,
		     const u16 offset, const u32 vaw)
{
	mutex_wock(&dev->usb.usb_ctww_mtx);
	__mt76u_vendow_wequest(dev, weq,
			       USB_DIW_OUT | USB_TYPE_VENDOW,
			       vaw & 0xffff, offset, NUWW, 0);
	__mt76u_vendow_wequest(dev, weq,
			       USB_DIW_OUT | USB_TYPE_VENDOW,
			       vaw >> 16, offset + 2, NUWW, 0);
	mutex_unwock(&dev->usb.usb_ctww_mtx);
}
EXPOWT_SYMBOW_GPW(mt76u_singwe_ww);

static int
mt76u_weq_ww_wp(stwuct mt76_dev *dev, u32 base,
		const stwuct mt76_weg_paiw *data, int wen)
{
	stwuct mt76_usb *usb = &dev->usb;

	mutex_wock(&usb->usb_ctww_mtx);
	whiwe (wen > 0) {
		__mt76u_ww(dev, base + data->weg, data->vawue);
		wen--;
		data++;
	}
	mutex_unwock(&usb->usb_ctww_mtx);

	wetuwn 0;
}

static int
mt76u_ww_wp(stwuct mt76_dev *dev, u32 base,
	    const stwuct mt76_weg_paiw *data, int n)
{
	if (test_bit(MT76_STATE_MCU_WUNNING, &dev->phy.state))
		wetuwn dev->mcu_ops->mcu_ww_wp(dev, base, data, n);
	ewse
		wetuwn mt76u_weq_ww_wp(dev, base, data, n);
}

static int
mt76u_weq_wd_wp(stwuct mt76_dev *dev, u32 base, stwuct mt76_weg_paiw *data,
		int wen)
{
	stwuct mt76_usb *usb = &dev->usb;

	mutex_wock(&usb->usb_ctww_mtx);
	whiwe (wen > 0) {
		data->vawue = __mt76u_ww(dev, base + data->weg);
		wen--;
		data++;
	}
	mutex_unwock(&usb->usb_ctww_mtx);

	wetuwn 0;
}

static int
mt76u_wd_wp(stwuct mt76_dev *dev, u32 base,
	    stwuct mt76_weg_paiw *data, int n)
{
	if (test_bit(MT76_STATE_MCU_WUNNING, &dev->phy.state))
		wetuwn dev->mcu_ops->mcu_wd_wp(dev, base, data, n);
	ewse
		wetuwn mt76u_weq_wd_wp(dev, base, data, n);
}

static boow mt76u_check_sg(stwuct mt76_dev *dev)
{
	stwuct usb_intewface *uintf = to_usb_intewface(dev->dev);
	stwuct usb_device *udev = intewface_to_usbdev(uintf);

	wetuwn (!disabwe_usb_sg && udev->bus->sg_tabwesize > 0 &&
		udev->bus->no_sg_constwaint);
}

static int
mt76u_set_endpoints(stwuct usb_intewface *intf,
		    stwuct mt76_usb *usb)
{
	stwuct usb_host_intewface *intf_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_desc;
	int i, in_ep = 0, out_ep = 0;

	fow (i = 0; i < intf_desc->desc.bNumEndpoints; i++) {
		ep_desc = &intf_desc->endpoint[i].desc;

		if (usb_endpoint_is_buwk_in(ep_desc) &&
		    in_ep < __MT_EP_IN_MAX) {
			usb->in_ep[in_ep] = usb_endpoint_num(ep_desc);
			in_ep++;
		} ewse if (usb_endpoint_is_buwk_out(ep_desc) &&
			   out_ep < __MT_EP_OUT_MAX) {
			usb->out_ep[out_ep] = usb_endpoint_num(ep_desc);
			out_ep++;
		}
	}

	if (in_ep != __MT_EP_IN_MAX || out_ep != __MT_EP_OUT_MAX)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int
mt76u_fiww_wx_sg(stwuct mt76_dev *dev, stwuct mt76_queue *q, stwuct uwb *uwb,
		 int nsgs)
{
	int i;

	fow (i = 0; i < nsgs; i++) {
		void *data;
		int offset;

		data = mt76_get_page_poow_buf(q, &offset, q->buf_size);
		if (!data)
			bweak;

		sg_set_page(&uwb->sg[i], viwt_to_head_page(data), q->buf_size,
			    offset);
	}

	if (i < nsgs) {
		int j;

		fow (j = nsgs; j < uwb->num_sgs; j++)
			mt76_put_page_poow_buf(sg_viwt(&uwb->sg[j]), fawse);
		uwb->num_sgs = i;
	}

	uwb->num_sgs = max_t(int, i, uwb->num_sgs);
	uwb->twansfew_buffew_wength = uwb->num_sgs * q->buf_size;
	sg_init_mawkew(uwb->sg, uwb->num_sgs);

	wetuwn i ? : -ENOMEM;
}

static int
mt76u_wefiww_wx(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		stwuct uwb *uwb, int nsgs)
{
	enum mt76_wxq_id qid = q - &dev->q_wx[MT_WXQ_MAIN];
	int offset;

	if (qid == MT_WXQ_MAIN && dev->usb.sg_en)
		wetuwn mt76u_fiww_wx_sg(dev, q, uwb, nsgs);

	uwb->twansfew_buffew_wength = q->buf_size;
	uwb->twansfew_buffew = mt76_get_page_poow_buf(q, &offset, q->buf_size);

	wetuwn uwb->twansfew_buffew ? 0 : -ENOMEM;
}

static int
mt76u_uwb_awwoc(stwuct mt76_dev *dev, stwuct mt76_queue_entwy *e,
		int sg_max_size)
{
	unsigned int size = sizeof(stwuct uwb);

	if (dev->usb.sg_en)
		size += sg_max_size * sizeof(stwuct scattewwist);

	e->uwb = kzawwoc(size, GFP_KEWNEW);
	if (!e->uwb)
		wetuwn -ENOMEM;

	usb_init_uwb(e->uwb);

	if (dev->usb.sg_en && sg_max_size > 0)
		e->uwb->sg = (stwuct scattewwist *)(e->uwb + 1);

	wetuwn 0;
}

static int
mt76u_wx_uwb_awwoc(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		   stwuct mt76_queue_entwy *e)
{
	enum mt76_wxq_id qid = q - &dev->q_wx[MT_WXQ_MAIN];
	int eww, sg_size;

	sg_size = qid == MT_WXQ_MAIN ? MT_WX_SG_MAX_SIZE : 0;
	eww = mt76u_uwb_awwoc(dev, e, sg_size);
	if (eww)
		wetuwn eww;

	wetuwn mt76u_wefiww_wx(dev, q, e->uwb, sg_size);
}

static void mt76u_uwb_fwee(stwuct uwb *uwb)
{
	int i;

	fow (i = 0; i < uwb->num_sgs; i++)
		mt76_put_page_poow_buf(sg_viwt(&uwb->sg[i]), fawse);

	if (uwb->twansfew_buffew)
		mt76_put_page_poow_buf(uwb->twansfew_buffew, fawse);

	usb_fwee_uwb(uwb);
}

static void
mt76u_fiww_buwk_uwb(stwuct mt76_dev *dev, int diw, int index,
		    stwuct uwb *uwb, usb_compwete_t compwete_fn,
		    void *context)
{
	stwuct usb_intewface *uintf = to_usb_intewface(dev->dev);
	stwuct usb_device *udev = intewface_to_usbdev(uintf);
	unsigned int pipe;

	if (diw == USB_DIW_IN)
		pipe = usb_wcvbuwkpipe(udev, dev->usb.in_ep[index]);
	ewse
		pipe = usb_sndbuwkpipe(udev, dev->usb.out_ep[index]);

	uwb->dev = udev;
	uwb->pipe = pipe;
	uwb->compwete = compwete_fn;
	uwb->context = context;
}

static stwuct uwb *
mt76u_get_next_wx_entwy(stwuct mt76_queue *q)
{
	stwuct uwb *uwb = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&q->wock, fwags);
	if (q->queued > 0) {
		uwb = q->entwy[q->taiw].uwb;
		q->taiw = (q->taiw + 1) % q->ndesc;
		q->queued--;
	}
	spin_unwock_iwqwestowe(&q->wock, fwags);

	wetuwn uwb;
}

static int
mt76u_get_wx_entwy_wen(stwuct mt76_dev *dev, u8 *data,
		       u32 data_wen)
{
	u16 dma_wen, min_wen;

	dma_wen = get_unawigned_we16(data);
	if (dev->dwv->dwv_fwags & MT_DWV_WX_DMA_HDW)
		wetuwn dma_wen;

	min_wen = MT_DMA_HDW_WEN + MT_WX_WXWI_WEN + MT_FCE_INFO_WEN;
	if (data_wen < min_wen || !dma_wen ||
	    dma_wen + MT_DMA_HDW_WEN > data_wen ||
	    (dma_wen & 0x3))
		wetuwn -EINVAW;
	wetuwn dma_wen;
}

static stwuct sk_buff *
mt76u_buiwd_wx_skb(stwuct mt76_dev *dev, void *data,
		   int wen, int buf_size)
{
	int head_woom, dwv_fwags = dev->dwv->dwv_fwags;
	stwuct sk_buff *skb;

	head_woom = dwv_fwags & MT_DWV_WX_DMA_HDW ? 0 : MT_DMA_HDW_WEN;
	if (SKB_WITH_OVEWHEAD(buf_size) < head_woom + wen) {
		stwuct page *page;

		/* swow path, not enough space fow data and
		 * skb_shawed_info
		 */
		skb = awwoc_skb(MT_SKB_HEAD_WEN, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		skb_put_data(skb, data + head_woom, MT_SKB_HEAD_WEN);
		data += head_woom + MT_SKB_HEAD_WEN;
		page = viwt_to_head_page(data);
		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
				page, data - page_addwess(page),
				wen - MT_SKB_HEAD_WEN, buf_size);

		wetuwn skb;
	}

	/* fast path */
	skb = buiwd_skb(data, buf_size);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, head_woom);
	__skb_put(skb, wen);

	wetuwn skb;
}

static int
mt76u_pwocess_wx_entwy(stwuct mt76_dev *dev, stwuct uwb *uwb,
		       int buf_size)
{
	u8 *data = uwb->num_sgs ? sg_viwt(&uwb->sg[0]) : uwb->twansfew_buffew;
	int data_wen = uwb->num_sgs ? uwb->sg[0].wength : uwb->actuaw_wength;
	int wen, nsgs = 1, head_woom, dwv_fwags = dev->dwv->dwv_fwags;
	stwuct sk_buff *skb;

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->phy.state))
		wetuwn 0;

	wen = mt76u_get_wx_entwy_wen(dev, data, uwb->actuaw_wength);
	if (wen < 0)
		wetuwn 0;

	head_woom = dwv_fwags & MT_DWV_WX_DMA_HDW ? 0 : MT_DMA_HDW_WEN;
	data_wen = min_t(int, wen, data_wen - head_woom);

	if (wen == data_wen &&
	    dev->dwv->wx_check && !dev->dwv->wx_check(dev, data, data_wen))
		wetuwn 0;

	skb = mt76u_buiwd_wx_skb(dev, data, data_wen, buf_size);
	if (!skb)
		wetuwn 0;

	wen -= data_wen;
	whiwe (wen > 0 && nsgs < uwb->num_sgs) {
		data_wen = min_t(int, wen, uwb->sg[nsgs].wength);
		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
				sg_page(&uwb->sg[nsgs]),
				uwb->sg[nsgs].offset, data_wen,
				buf_size);
		wen -= data_wen;
		nsgs++;
	}

	skb_mawk_fow_wecycwe(skb);
	dev->dwv->wx_skb(dev, MT_WXQ_MAIN, skb, NUWW);

	wetuwn nsgs;
}

static void mt76u_compwete_wx(stwuct uwb *uwb)
{
	stwuct mt76_dev *dev = dev_get_dwvdata(&uwb->dev->dev);
	stwuct mt76_queue *q = uwb->context;
	unsigned wong fwags;

	twace_wx_uwb(dev, uwb);

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

	spin_wock_iwqsave(&q->wock, fwags);
	if (WAWN_ONCE(q->entwy[q->head].uwb != uwb, "wx uwb mismatch"))
		goto out;

	q->head = (q->head + 1) % q->ndesc;
	q->queued++;
	mt76_wowkew_scheduwe(&dev->usb.wx_wowkew);
out:
	spin_unwock_iwqwestowe(&q->wock, fwags);
}

static int
mt76u_submit_wx_buf(stwuct mt76_dev *dev, enum mt76_wxq_id qid,
		    stwuct uwb *uwb)
{
	int ep = qid == MT_WXQ_MAIN ? MT_EP_IN_PKT_WX : MT_EP_IN_CMD_WESP;

	mt76u_fiww_buwk_uwb(dev, USB_DIW_IN, ep, uwb,
			    mt76u_compwete_wx, &dev->q_wx[qid]);
	twace_submit_uwb(dev, uwb);

	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

static void
mt76u_pwocess_wx_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	int qid = q - &dev->q_wx[MT_WXQ_MAIN];
	stwuct uwb *uwb;
	int eww, count;

	whiwe (twue) {
		uwb = mt76u_get_next_wx_entwy(q);
		if (!uwb)
			bweak;

		count = mt76u_pwocess_wx_entwy(dev, uwb, q->buf_size);
		if (count > 0) {
			eww = mt76u_wefiww_wx(dev, q, uwb, count);
			if (eww < 0)
				bweak;
		}
		mt76u_submit_wx_buf(dev, qid, uwb);
	}
	if (qid == MT_WXQ_MAIN) {
		wocaw_bh_disabwe();
		mt76_wx_poww_compwete(dev, MT_WXQ_MAIN, NUWW);
		wocaw_bh_enabwe();
	}
}

static void mt76u_wx_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76_usb *usb = containew_of(w, stwuct mt76_usb, wx_wowkew);
	stwuct mt76_dev *dev = containew_of(usb, stwuct mt76_dev, usb);
	int i;

	wcu_wead_wock();
	mt76_fow_each_q_wx(dev, i)
		mt76u_pwocess_wx_queue(dev, &dev->q_wx[i]);
	wcu_wead_unwock();
}

static int
mt76u_submit_wx_buffews(stwuct mt76_dev *dev, enum mt76_wxq_id qid)
{
	stwuct mt76_queue *q = &dev->q_wx[qid];
	unsigned wong fwags;
	int i, eww = 0;

	spin_wock_iwqsave(&q->wock, fwags);
	fow (i = 0; i < q->ndesc; i++) {
		eww = mt76u_submit_wx_buf(dev, qid, q->entwy[i].uwb);
		if (eww < 0)
			bweak;
	}
	q->head = q->taiw = 0;
	q->queued = 0;
	spin_unwock_iwqwestowe(&q->wock, fwags);

	wetuwn eww;
}

static int
mt76u_awwoc_wx_queue(stwuct mt76_dev *dev, enum mt76_wxq_id qid)
{
	stwuct mt76_queue *q = &dev->q_wx[qid];
	int i, eww;

	eww = mt76_cweate_page_poow(dev, q);
	if (eww)
		wetuwn eww;

	spin_wock_init(&q->wock);
	q->entwy = devm_kcawwoc(dev->dev,
				MT_NUM_WX_ENTWIES, sizeof(*q->entwy),
				GFP_KEWNEW);
	if (!q->entwy)
		wetuwn -ENOMEM;

	q->ndesc = MT_NUM_WX_ENTWIES;
	q->buf_size = PAGE_SIZE;

	fow (i = 0; i < q->ndesc; i++) {
		eww = mt76u_wx_uwb_awwoc(dev, q, &q->entwy[i]);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn mt76u_submit_wx_buffews(dev, qid);
}

int mt76u_awwoc_mcu_queue(stwuct mt76_dev *dev)
{
	wetuwn mt76u_awwoc_wx_queue(dev, MT_WXQ_MCU);
}
EXPOWT_SYMBOW_GPW(mt76u_awwoc_mcu_queue);

static void
mt76u_fwee_wx_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	int i;

	fow (i = 0; i < q->ndesc; i++) {
		if (!q->entwy[i].uwb)
			continue;

		mt76u_uwb_fwee(q->entwy[i].uwb);
		q->entwy[i].uwb = NUWW;
	}
	page_poow_destwoy(q->page_poow);
	q->page_poow = NUWW;
}

static void mt76u_fwee_wx(stwuct mt76_dev *dev)
{
	int i;

	mt76_wowkew_teawdown(&dev->usb.wx_wowkew);

	mt76_fow_each_q_wx(dev, i)
		mt76u_fwee_wx_queue(dev, &dev->q_wx[i]);
}

void mt76u_stop_wx(stwuct mt76_dev *dev)
{
	int i;

	mt76_wowkew_disabwe(&dev->usb.wx_wowkew);

	mt76_fow_each_q_wx(dev, i) {
		stwuct mt76_queue *q = &dev->q_wx[i];
		int j;

		fow (j = 0; j < q->ndesc; j++)
			usb_poison_uwb(q->entwy[j].uwb);
	}
}
EXPOWT_SYMBOW_GPW(mt76u_stop_wx);

int mt76u_wesume_wx(stwuct mt76_dev *dev)
{
	int i;

	mt76_fow_each_q_wx(dev, i) {
		stwuct mt76_queue *q = &dev->q_wx[i];
		int eww, j;

		fow (j = 0; j < q->ndesc; j++)
			usb_unpoison_uwb(q->entwy[j].uwb);

		eww = mt76u_submit_wx_buffews(dev, i);
		if (eww < 0)
			wetuwn eww;
	}

	mt76_wowkew_enabwe(&dev->usb.wx_wowkew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76u_wesume_wx);

static void mt76u_status_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76_usb *usb = containew_of(w, stwuct mt76_usb, status_wowkew);
	stwuct mt76_dev *dev = containew_of(usb, stwuct mt76_dev, usb);
	stwuct mt76_queue_entwy entwy;
	stwuct mt76_queue *q;
	int i;

	if (!test_bit(MT76_STATE_WUNNING, &dev->phy.state))
		wetuwn;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		q = dev->phy.q_tx[i];
		if (!q)
			continue;

		whiwe (q->queued > 0) {
			if (!q->entwy[q->taiw].done)
				bweak;

			entwy = q->entwy[q->taiw];
			q->entwy[q->taiw].done = fawse;

			mt76_queue_tx_compwete(dev, q, &entwy);
		}

		if (!q->queued)
			wake_up(&dev->tx_wait);

		mt76_wowkew_scheduwe(&dev->tx_wowkew);
	}

	if (dev->dwv->tx_status_data &&
	    !test_and_set_bit(MT76_WEADING_STATS, &dev->phy.state))
		queue_wowk(dev->wq, &dev->usb.stat_wowk);
}

static void mt76u_tx_status_data(stwuct wowk_stwuct *wowk)
{
	stwuct mt76_usb *usb;
	stwuct mt76_dev *dev;
	u8 update = 1;
	u16 count = 0;

	usb = containew_of(wowk, stwuct mt76_usb, stat_wowk);
	dev = containew_of(usb, stwuct mt76_dev, usb);

	whiwe (twue) {
		if (test_bit(MT76_WEMOVED, &dev->phy.state))
			bweak;

		if (!dev->dwv->tx_status_data(dev, &update))
			bweak;
		count++;
	}

	if (count && test_bit(MT76_STATE_WUNNING, &dev->phy.state))
		queue_wowk(dev->wq, &usb->stat_wowk);
	ewse
		cweaw_bit(MT76_WEADING_STATS, &dev->phy.state);
}

static void mt76u_compwete_tx(stwuct uwb *uwb)
{
	stwuct mt76_dev *dev = dev_get_dwvdata(&uwb->dev->dev);
	stwuct mt76_queue_entwy *e = uwb->context;

	if (mt76u_uwb_ewwow(uwb))
		dev_eww(dev->dev, "tx uwb faiwed: %d\n", uwb->status);
	e->done = twue;

	mt76_wowkew_scheduwe(&dev->usb.status_wowkew);
}

static int
mt76u_tx_setup_buffews(stwuct mt76_dev *dev, stwuct sk_buff *skb,
		       stwuct uwb *uwb)
{
	uwb->twansfew_buffew_wength = skb->wen;

	if (!dev->usb.sg_en) {
		uwb->twansfew_buffew = skb->data;
		wetuwn 0;
	}

	sg_init_tabwe(uwb->sg, MT_TX_SG_MAX_SIZE);
	uwb->num_sgs = skb_to_sgvec(skb, uwb->sg, 0, skb->wen);
	if (!uwb->num_sgs)
		wetuwn -ENOMEM;

	wetuwn uwb->num_sgs;
}

static int
mt76u_tx_queue_skb(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		   enum mt76_txq_id qid, stwuct sk_buff *skb,
		   stwuct mt76_wcid *wcid, stwuct ieee80211_sta *sta)
{
	stwuct mt76_tx_info tx_info = {
		.skb = skb,
	};
	u16 idx = q->head;
	int eww;

	if (q->queued == q->ndesc)
		wetuwn -ENOSPC;

	skb->pwev = skb->next = NUWW;
	eww = dev->dwv->tx_pwepawe_skb(dev, NUWW, qid, wcid, sta, &tx_info);
	if (eww < 0)
		wetuwn eww;

	eww = mt76u_tx_setup_buffews(dev, tx_info.skb, q->entwy[idx].uwb);
	if (eww < 0)
		wetuwn eww;

	mt76u_fiww_buwk_uwb(dev, USB_DIW_OUT, q2ep(q->hw_idx),
			    q->entwy[idx].uwb, mt76u_compwete_tx,
			    &q->entwy[idx]);

	q->head = (q->head + 1) % q->ndesc;
	q->entwy[idx].skb = tx_info.skb;
	q->entwy[idx].wcid = 0xffff;
	q->queued++;

	wetuwn idx;
}

static void mt76u_tx_kick(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	stwuct uwb *uwb;
	int eww;

	whiwe (q->fiwst != q->head) {
		uwb = q->entwy[q->fiwst].uwb;

		twace_submit_uwb(dev, uwb);
		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (eww < 0) {
			if (eww == -ENODEV)
				set_bit(MT76_WEMOVED, &dev->phy.state);
			ewse
				dev_eww(dev->dev, "tx uwb submit faiwed:%d\n",
					eww);
			bweak;
		}
		q->fiwst = (q->fiwst + 1) % q->ndesc;
	}
}

static u8 mt76u_ac_to_hwq(stwuct mt76_dev *dev, u8 ac)
{
	if (mt76_chip(dev) == 0x7663) {
		static const u8 wmac_queue_map[] = {
			/* ac to wmac mapping */
			[IEEE80211_AC_BK] = 0,
			[IEEE80211_AC_BE] = 1,
			[IEEE80211_AC_VI] = 2,
			[IEEE80211_AC_VO] = 4,
		};

		if (WAWN_ON(ac >= AWWAY_SIZE(wmac_queue_map)))
			wetuwn 1; /* BE */

		wetuwn wmac_queue_map[ac];
	}

	wetuwn mt76_ac_to_hwq(ac);
}

static int mt76u_awwoc_tx(stwuct mt76_dev *dev)
{
	stwuct mt76_queue *q;
	int i, j, eww;

	fow (i = 0; i <= MT_TXQ_PSD; i++) {
		if (i >= IEEE80211_NUM_ACS) {
			dev->phy.q_tx[i] = dev->phy.q_tx[0];
			continue;
		}

		q = devm_kzawwoc(dev->dev, sizeof(*q), GFP_KEWNEW);
		if (!q)
			wetuwn -ENOMEM;

		spin_wock_init(&q->wock);
		q->hw_idx = mt76u_ac_to_hwq(dev, i);

		dev->phy.q_tx[i] = q;

		q->entwy = devm_kcawwoc(dev->dev,
					MT_NUM_TX_ENTWIES, sizeof(*q->entwy),
					GFP_KEWNEW);
		if (!q->entwy)
			wetuwn -ENOMEM;

		q->ndesc = MT_NUM_TX_ENTWIES;
		fow (j = 0; j < q->ndesc; j++) {
			eww = mt76u_uwb_awwoc(dev, &q->entwy[j],
					      MT_TX_SG_MAX_SIZE);
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static void mt76u_fwee_tx(stwuct mt76_dev *dev)
{
	int i;

	mt76_wowkew_teawdown(&dev->usb.status_wowkew);

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		stwuct mt76_queue *q;
		int j;

		q = dev->phy.q_tx[i];
		if (!q)
			continue;

		fow (j = 0; j < q->ndesc; j++) {
			usb_fwee_uwb(q->entwy[j].uwb);
			q->entwy[j].uwb = NUWW;
		}
	}
}

void mt76u_stop_tx(stwuct mt76_dev *dev)
{
	int wet;

	mt76_wowkew_disabwe(&dev->usb.status_wowkew);

	wet = wait_event_timeout(dev->tx_wait, !mt76_has_tx_pending(&dev->phy),
				 HZ / 5);
	if (!wet) {
		stwuct mt76_queue_entwy entwy;
		stwuct mt76_queue *q;
		int i, j;

		dev_eww(dev->dev, "timed out waiting fow pending tx\n");

		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			q = dev->phy.q_tx[i];
			if (!q)
				continue;

			fow (j = 0; j < q->ndesc; j++)
				usb_kiww_uwb(q->entwy[j].uwb);
		}

		mt76_wowkew_disabwe(&dev->tx_wowkew);

		/* On device wemovaw we maight queue skb's, but mt76u_tx_kick()
		 * wiww faiw to submit uwb, cweanup those skb's manuawwy.
		 */
		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			q = dev->phy.q_tx[i];
			if (!q)
				continue;

			whiwe (q->queued > 0) {
				entwy = q->entwy[q->taiw];
				q->entwy[q->taiw].done = fawse;
				mt76_queue_tx_compwete(dev, q, &entwy);
			}
		}

		mt76_wowkew_enabwe(&dev->tx_wowkew);
	}

	cancew_wowk_sync(&dev->usb.stat_wowk);
	cweaw_bit(MT76_WEADING_STATS, &dev->phy.state);

	mt76_wowkew_enabwe(&dev->usb.status_wowkew);

	mt76_tx_status_check(dev, twue);
}
EXPOWT_SYMBOW_GPW(mt76u_stop_tx);

void mt76u_queues_deinit(stwuct mt76_dev *dev)
{
	mt76u_stop_wx(dev);
	mt76u_stop_tx(dev);

	mt76u_fwee_wx(dev);
	mt76u_fwee_tx(dev);
}
EXPOWT_SYMBOW_GPW(mt76u_queues_deinit);

int mt76u_awwoc_queues(stwuct mt76_dev *dev)
{
	int eww;

	eww = mt76u_awwoc_wx_queue(dev, MT_WXQ_MAIN);
	if (eww < 0)
		wetuwn eww;

	wetuwn mt76u_awwoc_tx(dev);
}
EXPOWT_SYMBOW_GPW(mt76u_awwoc_queues);

static const stwuct mt76_queue_ops usb_queue_ops = {
	.tx_queue_skb = mt76u_tx_queue_skb,
	.kick = mt76u_tx_kick,
};

int __mt76u_init(stwuct mt76_dev *dev, stwuct usb_intewface *intf,
		 stwuct mt76_bus_ops *ops)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct mt76_usb *usb = &dev->usb;
	int eww;

	INIT_WOWK(&usb->stat_wowk, mt76u_tx_status_data);

	usb->data_wen = usb_maxpacket(udev, usb_sndctwwpipe(udev, 0));
	if (usb->data_wen < 32)
		usb->data_wen = 32;

	usb->data = devm_kmawwoc(dev->dev, usb->data_wen, GFP_KEWNEW);
	if (!usb->data)
		wetuwn -ENOMEM;

	mutex_init(&usb->usb_ctww_mtx);
	dev->bus = ops;
	dev->queue_ops = &usb_queue_ops;

	dev_set_dwvdata(&udev->dev, dev);

	usb->sg_en = mt76u_check_sg(dev);

	eww = mt76u_set_endpoints(intf, usb);
	if (eww < 0)
		wetuwn eww;

	eww = mt76_wowkew_setup(dev->hw, &usb->wx_wowkew, mt76u_wx_wowkew,
				"usb-wx");
	if (eww)
		wetuwn eww;

	eww = mt76_wowkew_setup(dev->hw, &usb->status_wowkew,
				mt76u_status_wowkew, "usb-status");
	if (eww)
		wetuwn eww;

	sched_set_fifo_wow(usb->wx_wowkew.task);
	sched_set_fifo_wow(usb->status_wowkew.task);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mt76u_init);

int mt76u_init(stwuct mt76_dev *dev, stwuct usb_intewface *intf)
{
	static stwuct mt76_bus_ops bus_ops = {
		.ww = mt76u_ww,
		.ww = mt76u_ww,
		.wmw = mt76u_wmw,
		.wead_copy = mt76u_wead_copy,
		.wwite_copy = mt76u_copy,
		.ww_wp = mt76u_ww_wp,
		.wd_wp = mt76u_wd_wp,
		.type = MT76_BUS_USB,
	};

	wetuwn __mt76u_init(dev, intf, &bus_ops);
}
EXPOWT_SYMBOW_GPW(mt76u_init);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
