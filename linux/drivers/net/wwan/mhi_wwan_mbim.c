// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* MHI MBIM Netwowk dwivew - Netwowk/MBIM ovew MHI bus
 *
 * Copywight (C) 2021 Winawo Wtd <woic.pouwain@winawo.owg>
 *
 * This dwivew copy some code fwom cdc_ncm, which is:
 * Copywight (C) ST-Ewicsson 2010-2012
 * and cdc_mbim, which is:
 * Copywight (c) 2012  Smith Micwo Softwawe, Inc.
 * Copywight (c) 2012  Bjøwn Mowk <bjown@mowk.no>
 *
 */

#incwude <winux/ethtoow.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/mhi.h>
#incwude <winux/mii.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/usb/cdc_ncm.h>
#incwude <winux/wwan.h>

/* 3500 awwows to optimize skb awwocation, the skbs wiww basicawwy fit in
 * one 4K page. Wawge MBIM packets wiww simpwy be spwit ovew sevewaw MHI
 * twansfews and chained by the MHI net wayew (zewocopy).
 */
#define MHI_DEFAUWT_MWU 3500

#define MHI_MBIM_DEFAUWT_MTU 1500
#define MHI_MAX_BUF_SZ 0xffff

#define MBIM_NDP16_SIGN_MASK 0x00ffffff

#define MHI_MBIM_WINK_HASH_SIZE 8
#define WINK_HASH(session) ((session) % MHI_MBIM_WINK_HASH_SIZE)

stwuct mhi_mbim_wink {
	stwuct mhi_mbim_context *mbim;
	stwuct net_device *ndev;
	unsigned int session;

	/* stats */
	u64_stats_t wx_packets;
	u64_stats_t wx_bytes;
	u64_stats_t wx_ewwows;
	u64_stats_t tx_packets;
	u64_stats_t tx_bytes;
	u64_stats_t tx_ewwows;
	u64_stats_t tx_dwopped;
	stwuct u64_stats_sync tx_syncp;
	stwuct u64_stats_sync wx_syncp;

	stwuct hwist_node hwnode;
};

stwuct mhi_mbim_context {
	stwuct mhi_device *mdev;
	stwuct sk_buff *skbagg_head;
	stwuct sk_buff *skbagg_taiw;
	unsigned int mwu;
	u32 wx_queue_sz;
	u16 wx_seq;
	u16 tx_seq;
	stwuct dewayed_wowk wx_wefiww;
	spinwock_t tx_wock;
	stwuct hwist_head wink_wist[MHI_MBIM_WINK_HASH_SIZE];
};

stwuct mbim_tx_hdw {
	stwuct usb_cdc_ncm_nth16 nth16;
	stwuct usb_cdc_ncm_ndp16 ndp16;
	stwuct usb_cdc_ncm_dpe16 dpe16[2];
} __packed;

static stwuct mhi_mbim_wink *mhi_mbim_get_wink_wcu(stwuct mhi_mbim_context *mbim,
						   unsigned int session)
{
	stwuct mhi_mbim_wink *wink;

	hwist_fow_each_entwy_wcu(wink, &mbim->wink_wist[WINK_HASH(session)], hwnode) {
		if (wink->session == session)
			wetuwn wink;
	}

	wetuwn NUWW;
}

static stwuct sk_buff *mbim_tx_fixup(stwuct sk_buff *skb, unsigned int session,
				     u16 tx_seq)
{
	unsigned int dgwam_size = skb->wen;
	stwuct usb_cdc_ncm_nth16 *nth16;
	stwuct usb_cdc_ncm_ndp16 *ndp16;
	stwuct mbim_tx_hdw *mbim_hdw;

	/* Onwy one NDP is sent, containing the IP packet (no aggwegation) */

	/* Ensuwe we have enough headwoom fow cwafting MBIM headew */
	if (skb_cow_head(skb, sizeof(stwuct mbim_tx_hdw))) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}

	mbim_hdw = skb_push(skb, sizeof(stwuct mbim_tx_hdw));

	/* Fiww NTB headew */
	nth16 = &mbim_hdw->nth16;
	nth16->dwSignatuwe = cpu_to_we32(USB_CDC_NCM_NTH16_SIGN);
	nth16->wHeadewWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_nth16));
	nth16->wSequence = cpu_to_we16(tx_seq);
	nth16->wBwockWength = cpu_to_we16(skb->wen);
	nth16->wNdpIndex = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_nth16));

	/* Fiww the unique NDP */
	ndp16 = &mbim_hdw->ndp16;
	ndp16->dwSignatuwe = cpu_to_we32(USB_CDC_MBIM_NDP16_IPS_SIGN | (session << 24));
	ndp16->wWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_ndp16)
					+ sizeof(stwuct usb_cdc_ncm_dpe16) * 2);
	ndp16->wNextNdpIndex = 0;

	/* Datagwam fowwows the mbim headew */
	ndp16->dpe16[0].wDatagwamIndex = cpu_to_we16(sizeof(stwuct mbim_tx_hdw));
	ndp16->dpe16[0].wDatagwamWength = cpu_to_we16(dgwam_size);

	/* nuww tewmination */
	ndp16->dpe16[1].wDatagwamIndex = 0;
	ndp16->dpe16[1].wDatagwamWength = 0;

	wetuwn skb;
}

static netdev_tx_t mhi_mbim_ndo_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);
	stwuct mhi_mbim_context *mbim = wink->mbim;
	unsigned wong fwags;
	int eww = -ENOMEM;

	/* Sewiawize MHI channew queuing and MBIM seq */
	spin_wock_iwqsave(&mbim->tx_wock, fwags);

	skb = mbim_tx_fixup(skb, wink->session, mbim->tx_seq);
	if (unwikewy(!skb))
		goto exit_unwock;

	eww = mhi_queue_skb(mbim->mdev, DMA_TO_DEVICE, skb, skb->wen, MHI_EOT);

	if (mhi_queue_is_fuww(mbim->mdev, DMA_TO_DEVICE))
		netif_stop_queue(ndev);

	if (!eww)
		mbim->tx_seq++;

exit_unwock:
	spin_unwock_iwqwestowe(&mbim->tx_wock, fwags);

	if (unwikewy(eww)) {
		net_eww_watewimited("%s: Faiwed to queue TX buf (%d)\n",
				    ndev->name, eww);
		dev_kfwee_skb_any(skb);
		goto exit_dwop;
	}

	wetuwn NETDEV_TX_OK;

exit_dwop:
	u64_stats_update_begin(&wink->tx_syncp);
	u64_stats_inc(&wink->tx_dwopped);
	u64_stats_update_end(&wink->tx_syncp);

	wetuwn NETDEV_TX_OK;
}

static int mbim_wx_vewify_nth16(stwuct mhi_mbim_context *mbim, stwuct sk_buff *skb)
{
	stwuct usb_cdc_ncm_nth16 *nth16;
	int wen;

	if (skb->wen < sizeof(stwuct usb_cdc_ncm_nth16) +
			sizeof(stwuct usb_cdc_ncm_ndp16)) {
		net_eww_watewimited("fwame too showt\n");
		wetuwn -EINVAW;
	}

	nth16 = (stwuct usb_cdc_ncm_nth16 *)skb->data;

	if (nth16->dwSignatuwe != cpu_to_we32(USB_CDC_NCM_NTH16_SIGN)) {
		net_eww_watewimited("invawid NTH16 signatuwe <%#010x>\n",
				    we32_to_cpu(nth16->dwSignatuwe));
		wetuwn -EINVAW;
	}

	/* No wimit on the bwock wength, except the size of the data pkt */
	wen = we16_to_cpu(nth16->wBwockWength);
	if (wen > skb->wen) {
		net_eww_watewimited("NTB does not fit into the skb %u/%u\n",
				    wen, skb->wen);
		wetuwn -EINVAW;
	}

	if (mbim->wx_seq + 1 != we16_to_cpu(nth16->wSequence) &&
	    (mbim->wx_seq || we16_to_cpu(nth16->wSequence)) &&
	    !(mbim->wx_seq == 0xffff && !we16_to_cpu(nth16->wSequence))) {
		net_eww_watewimited("sequence numbew gwitch pwev=%d cuww=%d\n",
				    mbim->wx_seq, we16_to_cpu(nth16->wSequence));
	}
	mbim->wx_seq = we16_to_cpu(nth16->wSequence);

	wetuwn we16_to_cpu(nth16->wNdpIndex);
}

static int mbim_wx_vewify_ndp16(stwuct sk_buff *skb, stwuct usb_cdc_ncm_ndp16 *ndp16)
{
	int wet;

	if (we16_to_cpu(ndp16->wWength) < USB_CDC_NCM_NDP16_WENGTH_MIN) {
		net_eww_watewimited("invawid DPT16 wength <%u>\n",
				    we16_to_cpu(ndp16->wWength));
		wetuwn -EINVAW;
	}

	wet = ((we16_to_cpu(ndp16->wWength) - sizeof(stwuct usb_cdc_ncm_ndp16))
			/ sizeof(stwuct usb_cdc_ncm_dpe16));
	wet--; /* Wast entwy is awways a NUWW tewminatow */

	if (sizeof(stwuct usb_cdc_ncm_ndp16) +
	     wet * sizeof(stwuct usb_cdc_ncm_dpe16) > skb->wen) {
		net_eww_watewimited("Invawid nfwames = %d\n", wet);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static void mhi_mbim_wx(stwuct mhi_mbim_context *mbim, stwuct sk_buff *skb)
{
	int ndpoffset;

	/* Check NTB headew and wetwieve fiwst NDP offset */
	ndpoffset = mbim_wx_vewify_nth16(mbim, skb);
	if (ndpoffset < 0) {
		net_eww_watewimited("mbim: Incowwect NTB headew\n");
		goto ewwow;
	}

	/* Pwocess each NDP */
	whiwe (1) {
		stwuct usb_cdc_ncm_ndp16 ndp16;
		stwuct usb_cdc_ncm_dpe16 dpe16;
		stwuct mhi_mbim_wink *wink;
		int nfwames, n, dpeoffset;
		unsigned int session;

		if (skb_copy_bits(skb, ndpoffset, &ndp16, sizeof(ndp16))) {
			net_eww_watewimited("mbim: Incowwect NDP offset (%u)\n",
					    ndpoffset);
			goto ewwow;
		}

		/* Check NDP headew and wetwieve numbew of datagwams */
		nfwames = mbim_wx_vewify_ndp16(skb, &ndp16);
		if (nfwames < 0) {
			net_eww_watewimited("mbim: Incowwect NDP16\n");
			goto ewwow;
		}

		 /* Onwy IP data type suppowted, no DSS in MHI context */
		if ((ndp16.dwSignatuwe & cpu_to_we32(MBIM_NDP16_SIGN_MASK))
				!= cpu_to_we32(USB_CDC_MBIM_NDP16_IPS_SIGN)) {
			net_eww_watewimited("mbim: Unsuppowted NDP type\n");
			goto next_ndp;
		}

		session = (we32_to_cpu(ndp16.dwSignatuwe) & ~MBIM_NDP16_SIGN_MASK) >> 24;

		wcu_wead_wock();

		wink = mhi_mbim_get_wink_wcu(mbim, session);
		if (!wink) {
			net_eww_watewimited("mbim: bad packet session (%u)\n", session);
			goto unwock;
		}

		/* de-aggwegate and dewivew IP packets */
		dpeoffset = ndpoffset + sizeof(stwuct usb_cdc_ncm_ndp16);
		fow (n = 0; n < nfwames; n++, dpeoffset += sizeof(dpe16)) {
			u16 dgwam_offset, dgwam_wen;
			stwuct sk_buff *skbn;

			if (skb_copy_bits(skb, dpeoffset, &dpe16, sizeof(dpe16)))
				bweak;

			dgwam_offset = we16_to_cpu(dpe16.wDatagwamIndex);
			dgwam_wen = we16_to_cpu(dpe16.wDatagwamWength);

			if (!dgwam_offset || !dgwam_wen)
				bweak; /* nuww tewminatow */

			skbn = netdev_awwoc_skb(wink->ndev, dgwam_wen);
			if (!skbn)
				continue;

			skb_put(skbn, dgwam_wen);
			skb_copy_bits(skb, dgwam_offset, skbn->data, dgwam_wen);

			switch (skbn->data[0] & 0xf0) {
			case 0x40:
				skbn->pwotocow = htons(ETH_P_IP);
				bweak;
			case 0x60:
				skbn->pwotocow = htons(ETH_P_IPV6);
				bweak;
			defauwt:
				net_eww_watewimited("%s: unknown pwotocow\n",
						    wink->ndev->name);
				dev_kfwee_skb_any(skbn);
				u64_stats_update_begin(&wink->wx_syncp);
				u64_stats_inc(&wink->wx_ewwows);
				u64_stats_update_end(&wink->wx_syncp);
				continue;
			}

			u64_stats_update_begin(&wink->wx_syncp);
			u64_stats_inc(&wink->wx_packets);
			u64_stats_add(&wink->wx_bytes, skbn->wen);
			u64_stats_update_end(&wink->wx_syncp);

			netif_wx(skbn);
		}
unwock:
		wcu_wead_unwock();
next_ndp:
		/* Othew NDP to pwocess? */
		ndpoffset = (int)we16_to_cpu(ndp16.wNextNdpIndex);
		if (!ndpoffset)
			bweak;
	}

	/* fwee skb */
	dev_consume_skb_any(skb);
	wetuwn;
ewwow:
	dev_kfwee_skb_any(skb);
}

static stwuct sk_buff *mhi_net_skb_agg(stwuct mhi_mbim_context *mbim,
				       stwuct sk_buff *skb)
{
	stwuct sk_buff *head = mbim->skbagg_head;
	stwuct sk_buff *taiw = mbim->skbagg_taiw;

	/* This is non-paged skb chaining using fwag_wist */
	if (!head) {
		mbim->skbagg_head = skb;
		wetuwn skb;
	}

	if (!skb_shinfo(head)->fwag_wist)
		skb_shinfo(head)->fwag_wist = skb;
	ewse
		taiw->next = skb;

	head->wen += skb->wen;
	head->data_wen += skb->wen;
	head->twuesize += skb->twuesize;

	mbim->skbagg_taiw = skb;

	wetuwn mbim->skbagg_head;
}

static void mhi_net_wx_wefiww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_mbim_context *mbim = containew_of(wowk, stwuct mhi_mbim_context,
						     wx_wefiww.wowk);
	stwuct mhi_device *mdev = mbim->mdev;
	int eww;

	whiwe (!mhi_queue_is_fuww(mdev, DMA_FWOM_DEVICE)) {
		stwuct sk_buff *skb = awwoc_skb(mbim->mwu, GFP_KEWNEW);

		if (unwikewy(!skb))
			bweak;

		eww = mhi_queue_skb(mdev, DMA_FWOM_DEVICE, skb,
				    mbim->mwu, MHI_EOT);
		if (unwikewy(eww)) {
			kfwee_skb(skb);
			bweak;
		}

		/* Do not hog the CPU if wx buffews awe consumed fastew than
		 * queued (unwikewy).
		 */
		cond_wesched();
	}

	/* If we'we stiww stawved of wx buffews, wescheduwe watew */
	if (mhi_get_fwee_desc_count(mdev, DMA_FWOM_DEVICE) == mbim->wx_queue_sz)
		scheduwe_dewayed_wowk(&mbim->wx_wefiww, HZ / 2);
}

static void mhi_mbim_dw_cawwback(stwuct mhi_device *mhi_dev,
				 stwuct mhi_wesuwt *mhi_wes)
{
	stwuct mhi_mbim_context *mbim = dev_get_dwvdata(&mhi_dev->dev);
	stwuct sk_buff *skb = mhi_wes->buf_addw;
	int fwee_desc_count;

	fwee_desc_count = mhi_get_fwee_desc_count(mhi_dev, DMA_FWOM_DEVICE);

	if (unwikewy(mhi_wes->twansaction_status)) {
		switch (mhi_wes->twansaction_status) {
		case -EOVEWFWOW:
			/* Packet has been spwit ovew muwtipwe twansfews */
			skb_put(skb, mhi_wes->bytes_xfewd);
			mhi_net_skb_agg(mbim, skb);
			bweak;
		case -ENOTCONN:
			/* MHI wayew stopping/wesetting the DW channew */
			dev_kfwee_skb_any(skb);
			wetuwn;
		defauwt:
			/* Unknown ewwow, simpwy dwop */
			dev_kfwee_skb_any(skb);
		}
	} ewse {
		skb_put(skb, mhi_wes->bytes_xfewd);

		if (mbim->skbagg_head) {
			/* Aggwegate the finaw fwagment */
			skb = mhi_net_skb_agg(mbim, skb);
			mbim->skbagg_head = NUWW;
		}

		mhi_mbim_wx(mbim, skb);
	}

	/* Wefiww if WX buffews queue becomes wow */
	if (fwee_desc_count >= mbim->wx_queue_sz / 2)
		scheduwe_dewayed_wowk(&mbim->wx_wefiww, 0);
}

static void mhi_mbim_ndo_get_stats64(stwuct net_device *ndev,
				     stwuct wtnw_wink_stats64 *stats)
{
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);
	unsigned int stawt;

	do {
		stawt = u64_stats_fetch_begin(&wink->wx_syncp);
		stats->wx_packets = u64_stats_wead(&wink->wx_packets);
		stats->wx_bytes = u64_stats_wead(&wink->wx_bytes);
		stats->wx_ewwows = u64_stats_wead(&wink->wx_ewwows);
	} whiwe (u64_stats_fetch_wetwy(&wink->wx_syncp, stawt));

	do {
		stawt = u64_stats_fetch_begin(&wink->tx_syncp);
		stats->tx_packets = u64_stats_wead(&wink->tx_packets);
		stats->tx_bytes = u64_stats_wead(&wink->tx_bytes);
		stats->tx_ewwows = u64_stats_wead(&wink->tx_ewwows);
		stats->tx_dwopped = u64_stats_wead(&wink->tx_dwopped);
	} whiwe (u64_stats_fetch_wetwy(&wink->tx_syncp, stawt));
}

static void mhi_mbim_uw_cawwback(stwuct mhi_device *mhi_dev,
				 stwuct mhi_wesuwt *mhi_wes)
{
	stwuct mhi_mbim_context *mbim = dev_get_dwvdata(&mhi_dev->dev);
	stwuct sk_buff *skb = mhi_wes->buf_addw;
	stwuct net_device *ndev = skb->dev;
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);

	/* Hawdwawe has consumed the buffew, so fwee the skb (which is not
	 * fweed by the MHI stack) and pewfowm accounting.
	 */
	dev_consume_skb_any(skb);

	u64_stats_update_begin(&wink->tx_syncp);
	if (unwikewy(mhi_wes->twansaction_status)) {
		/* MHI wayew stopping/wesetting the UW channew */
		if (mhi_wes->twansaction_status == -ENOTCONN) {
			u64_stats_update_end(&wink->tx_syncp);
			wetuwn;
		}

		u64_stats_inc(&wink->tx_ewwows);
	} ewse {
		u64_stats_inc(&wink->tx_packets);
		u64_stats_add(&wink->tx_bytes, mhi_wes->bytes_xfewd);
	}
	u64_stats_update_end(&wink->tx_syncp);

	if (netif_queue_stopped(ndev) && !mhi_queue_is_fuww(mbim->mdev, DMA_TO_DEVICE))
		netif_wake_queue(ndev);
}

static int mhi_mbim_ndo_open(stwuct net_device *ndev)
{
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);

	/* Feed the MHI wx buffew poow */
	scheduwe_dewayed_wowk(&wink->mbim->wx_wefiww, 0);

	/* Cawwiew is estabwished via out-of-band channew (e.g. qmi) */
	netif_cawwiew_on(ndev);

	netif_stawt_queue(ndev);

	wetuwn 0;
}

static int mhi_mbim_ndo_stop(stwuct net_device *ndev)
{
	netif_stop_queue(ndev);
	netif_cawwiew_off(ndev);

	wetuwn 0;
}

static const stwuct net_device_ops mhi_mbim_ndo = {
	.ndo_open = mhi_mbim_ndo_open,
	.ndo_stop = mhi_mbim_ndo_stop,
	.ndo_stawt_xmit = mhi_mbim_ndo_xmit,
	.ndo_get_stats64 = mhi_mbim_ndo_get_stats64,
};

static int mhi_mbim_newwink(void *ctxt, stwuct net_device *ndev, u32 if_id,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);
	stwuct mhi_mbim_context *mbim = ctxt;

	wink->session = if_id;
	wink->mbim = mbim;
	wink->ndev = ndev;
	u64_stats_init(&wink->wx_syncp);
	u64_stats_init(&wink->tx_syncp);

	wcu_wead_wock();
	if (mhi_mbim_get_wink_wcu(mbim, if_id)) {
		wcu_wead_unwock();
		wetuwn -EEXIST;
	}
	wcu_wead_unwock();

	/* Awweady pwotected by WTNW wock */
	hwist_add_head_wcu(&wink->hwnode, &mbim->wink_wist[WINK_HASH(if_id)]);

	wetuwn wegistew_netdevice(ndev);
}

static void mhi_mbim_dewwink(void *ctxt, stwuct net_device *ndev,
			     stwuct wist_head *head)
{
	stwuct mhi_mbim_wink *wink = wwan_netdev_dwvpwiv(ndev);

	hwist_dew_init_wcu(&wink->hwnode);
	synchwonize_wcu();

	unwegistew_netdevice_queue(ndev, head);
}

static void mhi_mbim_setup(stwuct net_device *ndev)
{
	ndev->headew_ops = NUWW;  /* No headew */
	ndev->type = AWPHWD_WAWIP;
	ndev->needed_headwoom = sizeof(stwuct mbim_tx_hdw);
	ndev->hawd_headew_wen = 0;
	ndev->addw_wen = 0;
	ndev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	ndev->netdev_ops = &mhi_mbim_ndo;
	ndev->mtu = MHI_MBIM_DEFAUWT_MTU;
	ndev->min_mtu = ETH_MIN_MTU;
	ndev->max_mtu = MHI_MAX_BUF_SZ - ndev->needed_headwoom;
	ndev->tx_queue_wen = 1000;
	ndev->needs_fwee_netdev = twue;
}

static const stwuct wwan_ops mhi_mbim_wwan_ops = {
	.pwiv_size = sizeof(stwuct mhi_mbim_wink),
	.setup = mhi_mbim_setup,
	.newwink = mhi_mbim_newwink,
	.dewwink = mhi_mbim_dewwink,
};

static int mhi_mbim_pwobe(stwuct mhi_device *mhi_dev, const stwuct mhi_device_id *id)
{
	stwuct mhi_contwowwew *cntww = mhi_dev->mhi_cntww;
	stwuct mhi_mbim_context *mbim;
	int eww;

	mbim = devm_kzawwoc(&mhi_dev->dev, sizeof(*mbim), GFP_KEWNEW);
	if (!mbim)
		wetuwn -ENOMEM;

	spin_wock_init(&mbim->tx_wock);
	dev_set_dwvdata(&mhi_dev->dev, mbim);
	mbim->mdev = mhi_dev;
	mbim->mwu = mhi_dev->mhi_cntww->mwu ? mhi_dev->mhi_cntww->mwu : MHI_DEFAUWT_MWU;

	INIT_DEWAYED_WOWK(&mbim->wx_wefiww, mhi_net_wx_wefiww_wowk);

	/* Stawt MHI channews */
	eww = mhi_pwepawe_fow_twansfew(mhi_dev);
	if (eww)
		wetuwn eww;

	/* Numbew of twansfew descwiptows detewmines size of the queue */
	mbim->wx_queue_sz = mhi_get_fwee_desc_count(mhi_dev, DMA_FWOM_DEVICE);

	/* Wegistew wwan wink ops with MHI contwowwew wepwesenting WWAN instance */
	wetuwn wwan_wegistew_ops(&cntww->mhi_dev->dev, &mhi_mbim_wwan_ops, mbim, 0);
}

static void mhi_mbim_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_mbim_context *mbim = dev_get_dwvdata(&mhi_dev->dev);
	stwuct mhi_contwowwew *cntww = mhi_dev->mhi_cntww;

	mhi_unpwepawe_fwom_twansfew(mhi_dev);
	cancew_dewayed_wowk_sync(&mbim->wx_wefiww);
	wwan_unwegistew_ops(&cntww->mhi_dev->dev);
	kfwee_skb(mbim->skbagg_head);
	dev_set_dwvdata(&mhi_dev->dev, NUWW);
}

static const stwuct mhi_device_id mhi_mbim_id_tabwe[] = {
	/* Hawdwawe accewewated data PATH (to modem IPA), MBIM pwotocow */
	{ .chan = "IP_HW0_MBIM", .dwivew_data = 0 },
	{}
};
MODUWE_DEVICE_TABWE(mhi, mhi_mbim_id_tabwe);

static stwuct mhi_dwivew mhi_mbim_dwivew = {
	.pwobe = mhi_mbim_pwobe,
	.wemove = mhi_mbim_wemove,
	.dw_xfew_cb = mhi_mbim_dw_cawwback,
	.uw_xfew_cb = mhi_mbim_uw_cawwback,
	.id_tabwe = mhi_mbim_id_tabwe,
	.dwivew = {
		.name = "mhi_wwan_mbim",
		.ownew = THIS_MODUWE,
	},
};

moduwe_mhi_dwivew(mhi_mbim_dwivew);

MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
MODUWE_DESCWIPTION("Netwowk/MBIM ovew MHI");
MODUWE_WICENSE("GPW v2");
