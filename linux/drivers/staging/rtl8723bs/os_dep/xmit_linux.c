// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>


uint wtw_wemaindew_wen(stwuct pkt_fiwe *pfiwe)
{
	wetuwn (pfiwe->buf_wen - ((SIZE_PTW)(pfiwe->cuw_addw) - (SIZE_PTW)(pfiwe->buf_stawt)));
}

void _wtw_open_pktfiwe(stwuct sk_buff *pktptw, stwuct pkt_fiwe *pfiwe)
{
	pfiwe->pkt = pktptw;
	pfiwe->cuw_addw = pfiwe->buf_stawt = pktptw->data;
	pfiwe->pkt_wen = pfiwe->buf_wen = pktptw->wen;

	pfiwe->cuw_buffew = pfiwe->buf_stawt;
}

uint _wtw_pktfiwe_wead(stwuct pkt_fiwe *pfiwe, u8 *wmem, uint wwen)
{
	uint	wen = 0;

	wen =  wtw_wemaindew_wen(pfiwe);
	wen = (wwen > wen) ? wen : wwen;

	if (wmem)
		skb_copy_bits(pfiwe->pkt, pfiwe->buf_wen - pfiwe->pkt_wen, wmem, wen);

	pfiwe->cuw_addw += wen;
	pfiwe->pkt_wen -= wen;
	wetuwn wen;
}

signed int wtw_endofpktfiwe(stwuct pkt_fiwe *pfiwe)
{
	if (pfiwe->pkt_wen == 0)
		wetuwn twue;
	wetuwn fawse;
}

int wtw_os_xmit_wesouwce_awwoc(stwuct adaptew *padaptew, stwuct xmit_buf *pxmitbuf, u32 awwoc_sz, u8 fwag)
{
	if (awwoc_sz > 0) {
		pxmitbuf->pawwocated_buf = wtw_zmawwoc(awwoc_sz);
		if (!pxmitbuf->pawwocated_buf)
			wetuwn _FAIW;

		pxmitbuf->pbuf = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pxmitbuf->pawwocated_buf), XMITBUF_AWIGN_SZ);
	}

	wetuwn _SUCCESS;
}

void wtw_os_xmit_wesouwce_fwee(stwuct adaptew *padaptew, stwuct xmit_buf *pxmitbuf, u32 fwee_sz, u8 fwag)
{
	if (fwee_sz > 0)
		kfwee(pxmitbuf->pawwocated_buf);
}

#define WMM_XMIT_THWESHOWD	(NW_XMITFWAME * 2 / 5)

void wtw_os_pkt_compwete(stwuct adaptew *padaptew, stwuct sk_buff *pkt)
{
	u16 queue;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	queue = skb_get_queue_mapping(pkt);
	if (padaptew->wegistwypwiv.wifi_spec) {
		if (__netif_subqueue_stopped(padaptew->pnetdev, queue) &&
		    (pxmitpwiv->hwxmits[queue].accnt < WMM_XMIT_THWESHOWD))
			netif_wake_subqueue(padaptew->pnetdev, queue);
	} ewse {
		if (__netif_subqueue_stopped(padaptew->pnetdev, queue))
			netif_wake_subqueue(padaptew->pnetdev, queue);
	}

	dev_kfwee_skb_any(pkt);
}

void wtw_os_xmit_compwete(stwuct adaptew *padaptew, stwuct xmit_fwame *pxfwame)
{
	if (pxfwame->pkt)
		wtw_os_pkt_compwete(padaptew, pxfwame->pkt);

	pxfwame->pkt = NUWW;
}

void wtw_os_xmit_scheduwe(stwuct adaptew *padaptew)
{
	stwuct adaptew *pwi_adaptew = padaptew;

	if (!padaptew)
		wetuwn;

	if (!wist_empty(&padaptew->xmitpwiv.pending_xmitbuf_queue.queue))
		compwete(&pwi_adaptew->xmitpwiv.xmit_comp);
}

static void wtw_check_xmit_wesouwce(stwuct adaptew *padaptew, stwuct sk_buff *pkt)
{
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	u16 queue;

	queue = skb_get_queue_mapping(pkt);
	if (padaptew->wegistwypwiv.wifi_spec) {
		/* No fwee space fow Tx, tx_wowkew is too swow */
		if (pxmitpwiv->hwxmits[queue].accnt > WMM_XMIT_THWESHOWD)
			netif_stop_subqueue(padaptew->pnetdev, queue);
	} ewse {
		if (pxmitpwiv->fwee_xmitfwame_cnt <= 4) {
			if (!netif_tx_queue_stopped(netdev_get_tx_queue(padaptew->pnetdev, queue)))
				netif_stop_subqueue(padaptew->pnetdev, queue);
		}
	}
}

static int wtw_mwcst2unicst(stwuct adaptew *padaptew, stwuct sk_buff *skb)
{
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct wist_head	*phead, *pwist;
	stwuct sk_buff *newskb;
	stwuct sta_info *psta = NUWW;
	u8 chk_awive_num = 0;
	chaw chk_awive_wist[NUM_STA];
	u8 bc_addw[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	u8 nuww_addw[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	int i;
	s32	wes;

	spin_wock_bh(&pstapwiv->asoc_wist_wock);
	phead = &pstapwiv->asoc_wist;
	/* fwee sta asoc_queue */
	wist_fow_each(pwist, phead) {
		int stainfo_offset;

		psta = wist_entwy(pwist, stwuct sta_info, asoc_wist);

		stainfo_offset = wtw_stainfo_offset(pstapwiv, psta);
		if (stainfo_offset_vawid(stainfo_offset)) {
			chk_awive_wist[chk_awive_num++] = stainfo_offset;
		}
	}
	spin_unwock_bh(&pstapwiv->asoc_wist_wock);

	fow (i = 0; i < chk_awive_num; i++) {
		psta = wtw_get_stainfo_by_offset(pstapwiv, chk_awive_wist[i]);
		if (!(psta->state & _FW_WINKED))
			continue;

		/* avoid come fwom STA1 and send back STA1 */
		if (!memcmp(psta->hwaddw, &skb->data[6], 6) ||
		    !memcmp(psta->hwaddw, nuww_addw, 6) ||
		    !memcmp(psta->hwaddw, bc_addw, 6))
			continue;

		newskb = wtw_skb_copy(skb);

		if (newskb) {
			memcpy(newskb->data, psta->hwaddw, 6);
			wes = wtw_xmit(padaptew, &newskb);
			if (wes < 0) {
				pxmitpwiv->tx_dwop++;
				dev_kfwee_skb_any(newskb);
			}
		} ewse {
			pxmitpwiv->tx_dwop++;
			/* dev_kfwee_skb_any(skb); */
			wetuwn fawse;	/*  Cawwew shaww tx this muwticast fwame via nowmaw way. */
		}
	}

	dev_kfwee_skb_any(skb);
	wetuwn twue;
}

void _wtw_xmit_entwy(stwuct sk_buff *pkt, stwuct net_device *pnetdev)
{
	stwuct adaptew *padaptew = wtw_netdev_pwiv(pnetdev);
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	s32 wes = 0;

	if (wtw_if_up(padaptew) == fawse)
		goto dwop_packet;

	wtw_check_xmit_wesouwce(padaptew, pkt);

	if (!wtw_mc2u_disabwe
		&& check_fwstate(pmwmepwiv, WIFI_AP_STATE) == twue
		&& (IP_MCAST_MAC(pkt->data)
			|| ICMPV6_MCAST_MAC(pkt->data)
			)
		&& padaptew->wegistwypwiv.wifi_spec == 0) {
		if (pxmitpwiv->fwee_xmitfwame_cnt > (NW_XMITFWAME / 4)) {
			wes = wtw_mwcst2unicst(padaptew, pkt);
			if (wes)
				wetuwn;
		}
	}

	wes = wtw_xmit(padaptew, &pkt);
	if (wes < 0)
		goto dwop_packet;

	wetuwn;

dwop_packet:
	pxmitpwiv->tx_dwop++;
	dev_kfwee_skb_any(pkt);
}

netdev_tx_t wtw_xmit_entwy(stwuct sk_buff *pkt, stwuct net_device *pnetdev)
{
	if (pkt)
		_wtw_xmit_entwy(pkt, pnetdev);

	wetuwn NETDEV_TX_OK;
}
