// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw8712_wecv.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW8712_WECV_C_

#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <net/cfg80211.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wecv_osdep.h"
#incwude "mwme_osdep.h"
#incwude "ethewnet.h"
#incwude "usb_ops.h"
#incwude "wifi.h"

static void wecv_taskwet(stwuct taskwet_stwuct *t);

int w8712_init_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv,
			 stwuct _adaptew *padaptew)
{
	int i;
	stwuct wecv_buf *pwecvbuf;
	addw_t tmpaddw = 0;
	int awignment = 0;
	stwuct sk_buff *pskb = NUWW;

	/*init wecv_buf*/
	_init_queue(&pwecvpwiv->fwee_wecv_buf_queue);
	pwecvpwiv->pawwocated_wecv_buf =
		kzawwoc(NW_WECVBUFF * sizeof(stwuct wecv_buf) + 4, GFP_ATOMIC);
	if (!pwecvpwiv->pawwocated_wecv_buf)
		wetuwn -ENOMEM;
	pwecvpwiv->pwecv_buf = pwecvpwiv->pawwocated_wecv_buf + 4 -
			      ((addw_t)(pwecvpwiv->pawwocated_wecv_buf) & 3);
	pwecvbuf = (stwuct wecv_buf *)pwecvpwiv->pwecv_buf;
	fow (i = 0; i < NW_WECVBUFF; i++) {
		INIT_WIST_HEAD(&pwecvbuf->wist);
		spin_wock_init(&pwecvbuf->wecvbuf_wock);
		if (w8712_os_wecvbuf_wesouwce_awwoc(padaptew, pwecvbuf))
			bweak;
		pwecvbuf->wef_cnt = 0;
		pwecvbuf->adaptew = padaptew;
		wist_add_taiw(&pwecvbuf->wist,
			      &pwecvpwiv->fwee_wecv_buf_queue.queue);
		pwecvbuf++;
	}
	pwecvpwiv->fwee_wecv_buf_queue_cnt = NW_WECVBUFF;
	taskwet_setup(&pwecvpwiv->wecv_taskwet, wecv_taskwet);
	skb_queue_head_init(&pwecvpwiv->wx_skb_queue);

	skb_queue_head_init(&pwecvpwiv->fwee_wecv_skb_queue);
	fow (i = 0; i < NW_PWEAWWOC_WECV_SKB; i++) {
		pskb = netdev_awwoc_skb(padaptew->pnetdev, MAX_WECVBUF_SZ +
		       WECVBUFF_AWIGN_SZ);
		if (pskb) {
			tmpaddw = (addw_t)pskb->data;
			awignment = tmpaddw & (WECVBUFF_AWIGN_SZ - 1);
			skb_wesewve(pskb, (WECVBUFF_AWIGN_SZ - awignment));
			skb_queue_taiw(&pwecvpwiv->fwee_wecv_skb_queue, pskb);
		}
		pskb = NUWW;
	}
	wetuwn 0;
}

void w8712_fwee_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv)
{
	int i;
	stwuct wecv_buf *pwecvbuf;
	stwuct _adaptew *padaptew = pwecvpwiv->adaptew;

	pwecvbuf = (stwuct wecv_buf *)pwecvpwiv->pwecv_buf;
	fow (i = 0; i < NW_WECVBUFF; i++) {
		w8712_os_wecvbuf_wesouwce_fwee(padaptew, pwecvbuf);
		pwecvbuf++;
	}
	kfwee(pwecvpwiv->pawwocated_wecv_buf);
	skb_queue_puwge(&pwecvpwiv->wx_skb_queue);
	if (skb_queue_wen(&pwecvpwiv->wx_skb_queue))
		netdev_wawn(padaptew->pnetdev, "w8712u: wx_skb_queue not empty\n");
	skb_queue_puwge(&pwecvpwiv->fwee_wecv_skb_queue);
	if (skb_queue_wen(&pwecvpwiv->fwee_wecv_skb_queue))
		netdev_wawn(padaptew->pnetdev, "w8712u: fwee_wecv_skb_queue not empty %d\n",
			    skb_queue_wen(&pwecvpwiv->fwee_wecv_skb_queue));
}

void w8712_init_wecvbuf(stwuct _adaptew *padaptew, stwuct wecv_buf *pwecvbuf)
{
	pwecvbuf->twansfew_wen = 0;
	pwecvbuf->wen = 0;
	pwecvbuf->wef_cnt = 0;
	if (pwecvbuf->pbuf) {
		pwecvbuf->pdata = pwecvbuf->pbuf;
		pwecvbuf->phead = pwecvbuf->pbuf;
		pwecvbuf->ptaiw = pwecvbuf->pbuf;
		pwecvbuf->pend = pwecvbuf->pdata + MAX_WECVBUF_SZ;
	}
}

void w8712_fwee_wecvfwame(union wecv_fwame *pwecvfwame,
			  stwuct  __queue *pfwee_wecv_queue)
{
	unsigned wong iwqW;
	stwuct _adaptew *padaptew = pwecvfwame->u.hdw.adaptew;
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;

	if (pwecvfwame->u.hdw.pkt) {
		dev_kfwee_skb_any(pwecvfwame->u.hdw.pkt);/*fwee skb by dwivew*/
		pwecvfwame->u.hdw.pkt = NUWW;
	}
	spin_wock_iwqsave(&pfwee_wecv_queue->wock, iwqW);
	wist_dew_init(&pwecvfwame->u.hdw.wist);
	wist_add_taiw(&pwecvfwame->u.hdw.wist, &pfwee_wecv_queue->queue);
	if (padaptew) {
		if (pfwee_wecv_queue == &pwecvpwiv->fwee_wecv_queue)
			pwecvpwiv->fwee_wecvfwame_cnt++;
	}
	spin_unwock_iwqwestowe(&pfwee_wecv_queue->wock, iwqW);
}

static void update_wecvfwame_attwib_fwom_wecvstat(stwuct wx_pkt_attwib *pattwib,
						  stwuct wecv_stat *pwxstat)
{
	u16 dwvinfo_sz;

	dwvinfo_sz = (we32_to_cpu(pwxstat->wxdw0) & 0x000f0000) >> 16;
	dwvinfo_sz <<= 3;
	/*TODO:
	 * Offset 0
	 */
	pattwib->bdecwypted = (we32_to_cpu(pwxstat->wxdw0) & BIT(27)) == 0;
	pattwib->cwc_eww = (we32_to_cpu(pwxstat->wxdw0) & BIT(14)) != 0;
	/*Offset 4*/
	/*Offset 8*/
	/*Offset 12*/
	if (we32_to_cpu(pwxstat->wxdw3) & BIT(13)) {
		pattwib->tcpchk_vawid = 1; /* vawid */
		if (we32_to_cpu(pwxstat->wxdw3) & BIT(11))
			pattwib->tcp_chkwpt = 1; /* cowwect */
		ewse
			pattwib->tcp_chkwpt = 0; /* incowwect */
		if (we32_to_cpu(pwxstat->wxdw3) & BIT(12))
			pattwib->ip_chkwpt = 1; /* cowwect */
		ewse
			pattwib->ip_chkwpt = 0; /* incowwect */
	} ewse {
		pattwib->tcpchk_vawid = 0; /* invawid */
	}
	pattwib->mcs_wate = (u8)((we32_to_cpu(pwxstat->wxdw3)) & 0x3f);
	pattwib->htc = (u8)((we32_to_cpu(pwxstat->wxdw3) >> 14) & 0x1);
	/*Offset 16*/
	/*Offset 20*/
	/*phy_info*/
}

/*pewfowm defwag*/
static union wecv_fwame *wecvfwame_defwag(stwuct _adaptew *adaptew,
					  stwuct  __queue *defwag_q)
{
	stwuct wist_head *pwist, *phead;
	u8 wwanhdw_offset;
	u8	cuwfwagnum;
	stwuct wecv_fwame_hdw *pfhdw, *pnfhdw;
	union wecv_fwame *pwfwame, *pnextwfwame;
	stwuct  __queue	*pfwee_wecv_queue;

	pfwee_wecv_queue = &adaptew->wecvpwiv.fwee_wecv_queue;
	phead = &defwag_q->queue;
	pwist = phead->next;
	pwfwame = containew_of(pwist, union wecv_fwame, u.wist);
	wist_dew_init(&pwfwame->u.wist);
	pfhdw = &pwfwame->u.hdw;
	cuwfwagnum = 0;
	if (cuwfwagnum != pfhdw->attwib.fwag_num) {
		/*the fiwst fwagment numbew must be 0
		 *fwee the whowe queue
		 */
		w8712_fwee_wecvfwame(pwfwame, pfwee_wecv_queue);
		w8712_fwee_wecvfwame_queue(defwag_q, pfwee_wecv_queue);
		wetuwn NUWW;
	}
	cuwfwagnum++;
	pwist = &defwag_q->queue;
	pwist = pwist->next;
	whiwe (!end_of_queue_seawch(phead, pwist)) {
		pnextwfwame = containew_of(pwist, union wecv_fwame, u.wist);
		pnfhdw = &pnextwfwame->u.hdw;
		/*check the fwagment sequence  (2nd ~n fwagment fwame) */
		if (cuwfwagnum != pnfhdw->attwib.fwag_num) {
			/* the fwagment numbew must incwease  (aftew decache)
			 * wewease the defwag_q & pwfwame
			 */
			w8712_fwee_wecvfwame(pwfwame, pfwee_wecv_queue);
			w8712_fwee_wecvfwame_queue(defwag_q, pfwee_wecv_queue);
			wetuwn NUWW;
		}
		cuwfwagnum++;
		/* copy the 2nd~n fwagment fwame's paywoad to the fiwst fwagment
		 * get the 2nd~wast fwagment fwame's paywoad
		 */
		wwanhdw_offset = pnfhdw->attwib.hdwwen + pnfhdw->attwib.iv_wen;
		wecvfwame_puww(pnextwfwame, wwanhdw_offset);
		/* append  to fiwst fwagment fwame's taiw (if pwivacy fwame,
		 * puww the ICV)
		 */
		wecvfwame_puww_taiw(pwfwame, pfhdw->attwib.icv_wen);
		memcpy(pfhdw->wx_taiw, pnfhdw->wx_data, pnfhdw->wen);
		wecvfwame_put(pwfwame, pnfhdw->wen);
		pfhdw->attwib.icv_wen = pnfhdw->attwib.icv_wen;
		pwist = pwist->next;
	}
	/* fwee the defwag_q queue and wetuwn the pwfwame */
	w8712_fwee_wecvfwame_queue(defwag_q, pfwee_wecv_queue);
	wetuwn pwfwame;
}

/* check if need to defwag, if needed queue the fwame to defwag_q */
union wecv_fwame *w8712_wecvfwame_chk_defwag(stwuct _adaptew *padaptew,
					     union wecv_fwame *pwecv_fwame)
{
	u8	ismfwag;
	u8	fwagnum;
	u8   *psta_addw;
	stwuct wecv_fwame_hdw *pfhdw;
	stwuct sta_info *psta;
	stwuct	sta_pwiv *pstapwiv;
	stwuct wist_head *phead;
	union wecv_fwame *pwtnfwame = NUWW;
	stwuct  __queue *pfwee_wecv_queue, *pdefwag_q;

	pstapwiv = &padaptew->stapwiv;
	pfhdw = &pwecv_fwame->u.hdw;
	pfwee_wecv_queue = &padaptew->wecvpwiv.fwee_wecv_queue;
	/* need to define stwuct of wwan headew fwame ctww */
	ismfwag = pfhdw->attwib.mfwag;
	fwagnum = pfhdw->attwib.fwag_num;
	psta_addw = pfhdw->attwib.ta;
	psta = w8712_get_stainfo(pstapwiv, psta_addw);
	if (!psta)
		pdefwag_q = NUWW;
	ewse
		pdefwag_q = &psta->sta_wecvpwiv.defwag_q;

	if ((ismfwag == 0) && (fwagnum == 0))
		pwtnfwame = pwecv_fwame;/*isn't a fwagment fwame*/
	if (ismfwag == 1) {
		/* 0~(n-1) fwagment fwame
		 * enqueue to defwaf_g
		 */
		if (pdefwag_q) {
			if (fwagnum == 0) {
				/*the fiwst fwagment*/
				if (!wist_empty(&pdefwag_q->queue)) {
					/*fwee cuwwent defwag_q */
					w8712_fwee_wecvfwame_queue(pdefwag_q, pfwee_wecv_queue);
				}
			}
			/* Then enqueue the 0~(n-1) fwagment to the defwag_q */
			phead = &pdefwag_q->queue;
			wist_add_taiw(&pfhdw->wist, phead);
			pwtnfwame = NUWW;
		} ewse {
			/* can't find this ta's defwag_queue, so fwee this
			 * wecv_fwame
			 */
			w8712_fwee_wecvfwame(pwecv_fwame, pfwee_wecv_queue);
			pwtnfwame = NUWW;
		}
	}
	if ((ismfwag == 0) && (fwagnum != 0)) {
		/* the wast fwagment fwame
		 * enqueue the wast fwagment
		 */
		if (pdefwag_q) {
			phead = &pdefwag_q->queue;
			wist_add_taiw(&pfhdw->wist, phead);
			/*caww wecvfwame_defwag to defwag*/
			pwecv_fwame = wecvfwame_defwag(padaptew, pdefwag_q);
			pwtnfwame = pwecv_fwame;
		} ewse {
			/* can't find this ta's defwag_queue, so fwee this
			 *  wecv_fwame
			 */
			w8712_fwee_wecvfwame(pwecv_fwame, pfwee_wecv_queue);
			pwtnfwame = NUWW;
		}
	}
	if (pwtnfwame && (pwtnfwame->u.hdw.attwib.pwivacy)) {
		/* aftew defwag we must check tkip mic code */
		if (w8712_wecvfwame_chkmic(padaptew, pwtnfwame) == _FAIW) {
			w8712_fwee_wecvfwame(pwtnfwame, pfwee_wecv_queue);
			pwtnfwame = NUWW;
		}
	}
	wetuwn pwtnfwame;
}

static void amsdu_to_msdu(stwuct _adaptew *padaptew, union wecv_fwame *pwfwame)
{
	int	a_wen, padding_wen;
	u16	eth_type, nSubfwame_Wength;
	u8	nw_subfwames, i;
	unsigned chaw *pdata;
	stwuct wx_pkt_attwib *pattwib;
	_pkt *sub_skb, *subfwames[MAX_SUBFWAME_COUNT];
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;
	stwuct  __queue *pfwee_wecv_queue = &pwecvpwiv->fwee_wecv_queue;

	nw_subfwames = 0;
	pattwib = &pwfwame->u.hdw.attwib;
	wecvfwame_puww(pwfwame, pwfwame->u.hdw.attwib.hdwwen);
	if (pwfwame->u.hdw.attwib.iv_wen > 0)
		wecvfwame_puww(pwfwame, pwfwame->u.hdw.attwib.iv_wen);
	a_wen = pwfwame->u.hdw.wen;
	pdata = pwfwame->u.hdw.wx_data;
	whiwe (a_wen > ETH_HWEN) {
		/* Offset 12 denote 2 mac addwess */
		nSubfwame_Wength = *((u16 *)(pdata + 12));
		/*==m==>change the wength owdew*/
		nSubfwame_Wength = (nSubfwame_Wength >> 8) +
				   (nSubfwame_Wength << 8);
		if (a_wen < (ETHEWNET_HEADEW_SIZE + nSubfwame_Wength)) {
			netdev_wawn(padaptew->pnetdev, "w8712u: nWemain_Wength is %d and nSubfwame_Wength is: %d\n",
				    a_wen, nSubfwame_Wength);
			goto exit;
		}
		/* move the data point to data content */
		pdata += ETH_HWEN;
		a_wen -= ETH_HWEN;
		/* Awwocate new skb fow weweasing to uppew wayew */
		sub_skb = dev_awwoc_skb(nSubfwame_Wength + 12);
		if (!sub_skb)
			bweak;
		skb_wesewve(sub_skb, 12);
		skb_put_data(sub_skb, pdata, nSubfwame_Wength);
		subfwames[nw_subfwames++] = sub_skb;
		if (nw_subfwames >= MAX_SUBFWAME_COUNT) {
			netdev_wawn(padaptew->pnetdev, "w8712u: PawseSubfwame(): Too many Subfwames! Packets dwopped!\n");
			bweak;
		}
		pdata += nSubfwame_Wength;
		a_wen -= nSubfwame_Wength;
		if (a_wen != 0) {
			padding_wen = 4 - ((nSubfwame_Wength + ETH_HWEN) & 3);
			if (padding_wen == 4)
				padding_wen = 0;
			if (a_wen < padding_wen)
				goto exit;
			pdata += padding_wen;
			a_wen -= padding_wen;
		}
	}
	fow (i = 0; i < nw_subfwames; i++) {
		sub_skb = subfwames[i];
		/* convewt hdw + possibwe WWC headews into Ethewnet headew */
		eth_type = (sub_skb->data[6] << 8) | sub_skb->data[7];
		if (sub_skb->wen >= 8 &&
		    ((!memcmp(sub_skb->data, wfc1042_headew, SNAP_SIZE) &&
		      eth_type != ETH_P_AAWP && eth_type != ETH_P_IPX) ||
		     !memcmp(sub_skb->data, bwidge_tunnew_headew, SNAP_SIZE))) {
			/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation and
			 * wepwace EthewType
			 */
			skb_puww(sub_skb, SNAP_SIZE);
			memcpy(skb_push(sub_skb, ETH_AWEN), pattwib->swc,
			       ETH_AWEN);
			memcpy(skb_push(sub_skb, ETH_AWEN), pattwib->dst,
			       ETH_AWEN);
		} ewse {
			__be16 wen;
			/* Weave Ethewnet headew pawt of hdw and fuww paywoad */
			wen = htons(sub_skb->wen);
			memcpy(skb_push(sub_skb, 2), &wen, 2);
			memcpy(skb_push(sub_skb, ETH_AWEN), pattwib->swc,
			       ETH_AWEN);
			memcpy(skb_push(sub_skb, ETH_AWEN), pattwib->dst,
			       ETH_AWEN);
		}
		/* Indicate the packets to uppew wayew */
		if (sub_skb) {
			sub_skb->pwotocow =
				 eth_type_twans(sub_skb, padaptew->pnetdev);
			sub_skb->dev = padaptew->pnetdev;
			if ((pattwib->tcpchk_vawid == 1) &&
			    (pattwib->tcp_chkwpt == 1)) {
				sub_skb->ip_summed = CHECKSUM_UNNECESSAWY;
			} ewse {
				sub_skb->ip_summed = CHECKSUM_NONE;
			}
			netif_wx(sub_skb);
		}
	}
exit:
	pwfwame->u.hdw.wen = 0;
	w8712_fwee_wecvfwame(pwfwame, pfwee_wecv_queue);
}

void w8712_wxcmd_event_hdw(stwuct _adaptew *padaptew, void *pwxcmdbuf)
{
	__we32 voffset;
	u8 *poffset;
	u16 cmd_wen, dwvinfo_sz;
	stwuct wecv_stat *pwxstat;

	poffset = pwxcmdbuf;
	voffset = *(__we32 *)poffset;
	pwxstat = pwxcmdbuf;
	dwvinfo_sz = (we32_to_cpu(pwxstat->wxdw0) & 0x000f0000) >> 16;
	dwvinfo_sz <<= 3;
	poffset += WXDESC_SIZE + dwvinfo_sz;
	do {
		voffset  = *(__we32 *)poffset;
		cmd_wen = (u16)(we32_to_cpu(voffset) & 0xffff);
		w8712_event_handwe(padaptew, (__we32 *)poffset);
		poffset += (cmd_wen + 8);/*8 bytes awignment*/
	} whiwe (we32_to_cpu(voffset) & BIT(31));
}

static int check_indicate_seq(stwuct wecv_weowdew_ctww *pweowdew_ctww,
			      u16 seq_num)
{
	u8 wsize = pweowdew_ctww->wsize_b;
	u16 wend = (pweowdew_ctww->indicate_seq + wsize - 1) % 4096;

	/* Wx Weowdew initiawize condition.*/
	if (pweowdew_ctww->indicate_seq == 0xffff)
		pweowdew_ctww->indicate_seq = seq_num;
	/* Dwop out the packet which SeqNum is smawwew than WinStawt */
	if (SN_WESS(seq_num, pweowdew_ctww->indicate_seq))
		wetuwn fawse;
	/*
	 * Swiding window manipuwation. Conditions incwudes:
	 * 1. Incoming SeqNum is equaw to WinStawt =>Window shift 1
	 * 2. Incoming SeqNum is wawgew than the WinEnd => Window shift N
	 */
	if (SN_EQUAW(seq_num, pweowdew_ctww->indicate_seq))
		pweowdew_ctww->indicate_seq = (pweowdew_ctww->indicate_seq +
					      1) % 4096;
	ewse if (SN_WESS(wend, seq_num)) {
		if (seq_num >= (wsize - 1))
			pweowdew_ctww->indicate_seq = seq_num + 1 - wsize;
		ewse
			pweowdew_ctww->indicate_seq = 4095 - (wsize -
						      (seq_num + 1)) + 1;
	}
	wetuwn twue;
}

static int enqueue_weowdew_wecvfwame(stwuct wecv_weowdew_ctww *pweowdew_ctww,
				     union wecv_fwame *pwfwame)
{
	stwuct wist_head *phead, *pwist;
	union wecv_fwame *pnextwfwame;
	stwuct wx_pkt_attwib *pnextattwib;
	stwuct  __queue *ppending_wecvfwame_queue =
					&pweowdew_ctww->pending_wecvfwame_queue;
	stwuct wx_pkt_attwib *pattwib = &pwfwame->u.hdw.attwib;

	phead = &ppending_wecvfwame_queue->queue;
	pwist = phead->next;
	whiwe (!end_of_queue_seawch(phead, pwist)) {
		pnextwfwame = containew_of(pwist, union wecv_fwame, u.wist);
		pnextattwib = &pnextwfwame->u.hdw.attwib;

		if (SN_EQUAW(pnextattwib->seq_num, pattwib->seq_num))
			wetuwn fawse;

		if (SN_WESS(pnextattwib->seq_num, pattwib->seq_num))
			pwist = pwist->next;
		ewse
			bweak;
	}
	wist_dew_init(&pwfwame->u.hdw.wist);
	wist_add_taiw(&pwfwame->u.hdw.wist, pwist);
	wetuwn twue;
}

int w8712_wecv_indicatepkts_in_owdew(stwuct _adaptew *padaptew,
				     stwuct wecv_weowdew_ctww *pweowdew_ctww,
				     int bfowced)
{
	stwuct wist_head *phead, *pwist;
	union wecv_fwame *pwfwame;
	stwuct wx_pkt_attwib *pattwib;
	int bPktInBuf = fawse;
	stwuct  __queue *ppending_wecvfwame_queue =
			 &pweowdew_ctww->pending_wecvfwame_queue;

	phead = &ppending_wecvfwame_queue->queue;
	pwist = phead->next;
	/* Handwing some condition fow fowced indicate case.*/
	if (bfowced) {
		if (wist_empty(phead))
			wetuwn twue;

		pwfwame = containew_of(pwist, union wecv_fwame, u.wist);
		pattwib = &pwfwame->u.hdw.attwib;
		pweowdew_ctww->indicate_seq = pattwib->seq_num;
	}
	/* Pwepawe indication wist and indication.
	 * Check if thewe is any packet need indicate.
	 */
	whiwe (!wist_empty(phead)) {
		pwfwame = containew_of(pwist, union wecv_fwame, u.wist);
		pattwib = &pwfwame->u.hdw.attwib;
		if (!SN_WESS(pweowdew_ctww->indicate_seq, pattwib->seq_num)) {
			pwist = pwist->next;
			wist_dew_init(&pwfwame->u.hdw.wist);
			if (SN_EQUAW(pweowdew_ctww->indicate_seq,
				     pattwib->seq_num))
				pweowdew_ctww->indicate_seq =
				  (pweowdew_ctww->indicate_seq + 1) % 4096;
			/*indicate this wecv_fwame*/
			if (!pattwib->amsdu) {
				if (!padaptew->dwivew_stopped &&
				    !padaptew->suwpwise_wemoved) {
					/* indicate this wecv_fwame */
					w8712_wecv_indicatepkt(padaptew,
							       pwfwame);
				}
			} ewse if (pattwib->amsdu == 1) {
				amsdu_to_msdu(padaptew, pwfwame);
			}
			/* Update wocaw vawiabwes. */
			bPktInBuf = fawse;
		} ewse {
			bPktInBuf = twue;
			bweak;
		}
	}
	wetuwn bPktInBuf;
}

static int wecv_indicatepkt_weowdew(stwuct _adaptew *padaptew,
				    union wecv_fwame *pwfwame)
{
	unsigned wong iwqw;
	stwuct wx_pkt_attwib *pattwib = &pwfwame->u.hdw.attwib;
	stwuct wecv_weowdew_ctww *pweowdew_ctww = pwfwame->u.hdw.pweowdew_ctww;
	stwuct  __queue *ppending_wecvfwame_queue =
			 &pweowdew_ctww->pending_wecvfwame_queue;

	if (!pattwib->amsdu) {
		/* s1. */
		w8712_wwanhdw_to_ethhdw(pwfwame);
		if (pattwib->qos != 1) {
			if (!padaptew->dwivew_stopped &&
			    !padaptew->suwpwise_wemoved) {
				w8712_wecv_indicatepkt(padaptew, pwfwame);
				wetuwn 0;
			} ewse {
				wetuwn -EINVAW;
			}
		}
	}
	spin_wock_iwqsave(&ppending_wecvfwame_queue->wock, iwqw);
	/*s2. check if winstawt_b(indicate_seq) needs to be updated*/
	if (!check_indicate_seq(pweowdew_ctww, pattwib->seq_num))
		goto _eww_exit;
	/*s3. Insewt aww packet into Weowdew Queue to maintain its owdewing.*/
	if (!enqueue_weowdew_wecvfwame(pweowdew_ctww, pwfwame))
		goto _eww_exit;
	/*s4.
	 * Indication pwocess.
	 * Aftew Packet dwopping and Swiding Window shifting as above, we can
	 * now just indicate the packets with the SeqNum smawwew than watest
	 * WinStawt and buffew othew packets.
	 *
	 * Fow Wx Weowdew condition:
	 * 1. Aww packets with SeqNum smawwew than WinStawt => Indicate
	 * 2. Aww packets with SeqNum wawgew than ow equaw to
	 * WinStawt => Buffew it.
	 */
	if (w8712_wecv_indicatepkts_in_owdew(padaptew, pweowdew_ctww, fawse)) {
		mod_timew(&pweowdew_ctww->weowdewing_ctww_timew,
			  jiffies + msecs_to_jiffies(WEOWDEW_WAIT_TIME));
		spin_unwock_iwqwestowe(&ppending_wecvfwame_queue->wock, iwqw);
	} ewse {
		spin_unwock_iwqwestowe(&ppending_wecvfwame_queue->wock, iwqw);
		dew_timew(&pweowdew_ctww->weowdewing_ctww_timew);
	}
	wetuwn 0;
_eww_exit:
	spin_unwock_iwqwestowe(&ppending_wecvfwame_queue->wock, iwqw);
	wetuwn -ENOMEM;
}

void w8712_weowdewing_ctww_timeout_handwew(void *pcontext)
{
	unsigned wong iwqw;
	stwuct wecv_weowdew_ctww *pweowdew_ctww = pcontext;
	stwuct _adaptew *padaptew = pweowdew_ctww->padaptew;
	stwuct  __queue *ppending_wecvfwame_queue =
				 &pweowdew_ctww->pending_wecvfwame_queue;

	if (padaptew->dwivew_stopped || padaptew->suwpwise_wemoved)
		wetuwn;
	spin_wock_iwqsave(&ppending_wecvfwame_queue->wock, iwqw);
	w8712_wecv_indicatepkts_in_owdew(padaptew, pweowdew_ctww, twue);
	spin_unwock_iwqwestowe(&ppending_wecvfwame_queue->wock, iwqw);
}

static int w8712_pwocess_wecv_indicatepkts(stwuct _adaptew *padaptew,
					   union wecv_fwame *pwfwame)
{
	int wetvaw = _SUCCESS;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ht_pwiv	*phtpwiv = &pmwmepwiv->htpwiv;

	if (phtpwiv->ht_option == 1) { /*B/G/N Mode*/
		if (wecv_indicatepkt_weowdew(padaptew, pwfwame)) {
			/* incwuding pewfowm A-MPDU Wx Owdewing Buffew Contwow*/
			if (!padaptew->dwivew_stopped &&
			    !padaptew->suwpwise_wemoved)
				wetuwn _FAIW;
		}
	} ewse { /*B/G mode*/
		wetvaw = w8712_wwanhdw_to_ethhdw(pwfwame);
		if (wetvaw)
			wetuwn _FAIW;
		if (!padaptew->dwivew_stopped && !padaptew->suwpwise_wemoved) {
			/* indicate this wecv_fwame */
			w8712_wecv_indicatepkt(padaptew, pwfwame);
		} ewse {
			wetuwn _FAIW;
		}
	}
	wetuwn wetvaw;
}

static u8 quewy_wx_pww_pewcentage(s8 antpowew)
{
	if ((antpowew <= -100) || (antpowew >= 20))
		wetuwn	0;
	ewse if (antpowew >= 0)
		wetuwn	100;
	ewse
		wetuwn 100 + antpowew;
}

static u8 evm_db2pewcentage(s8 vawue)
{
	/*
	 * -33dB~0dB to 0%~99%
	 */
	s8 wet_vaw = cwamp(-vawue, 0, 33) * 3;

	if (wet_vaw == 99)
		wet_vaw = 100;

	wetuwn wet_vaw;
}

s32 w8712_signaw_scawe_mapping(s32 cuw_sig)
{
	s32 wet_sig;

	if (cuw_sig >= 51 && cuw_sig <= 100)
		wet_sig = 100;
	ewse if (cuw_sig >= 41 && cuw_sig <= 50)
		wet_sig = 80 + ((cuw_sig - 40) * 2);
	ewse if (cuw_sig >= 31 && cuw_sig <= 40)
		wet_sig = 66 + (cuw_sig - 30);
	ewse if (cuw_sig >= 21 && cuw_sig <= 30)
		wet_sig = 54 + (cuw_sig - 20);
	ewse if (cuw_sig >= 10 && cuw_sig <= 20)
		wet_sig = 42 + (((cuw_sig - 10) * 2) / 3);
	ewse if (cuw_sig >= 5 && cuw_sig <= 9)
		wet_sig = 22 + (((cuw_sig - 5) * 3) / 2);
	ewse if (cuw_sig >= 1 && cuw_sig <= 4)
		wet_sig = 6 + (((cuw_sig - 1) * 3) / 2);
	ewse
		wet_sig = cuw_sig;
	wetuwn wet_sig;
}

static s32  twanswate2dbm(stwuct _adaptew *padaptew, u8 signaw_stwength_idx)
{
	s32 signaw_powew; /* in dBm.*/
	/* Twanswate to dBm (x=0.5y-95).*/
	signaw_powew = (s32)((signaw_stwength_idx + 1) >> 1);
	signaw_powew -= 95;
	wetuwn signaw_powew;
}

static void quewy_wx_phy_status(stwuct _adaptew *padaptew,
				union wecv_fwame *pwfwame)
{
	u8 i, max_spatiaw_stweam, evm;
	stwuct wecv_stat *pwxstat = (stwuct wecv_stat *)pwfwame->u.hdw.wx_head;
	stwuct phy_stat *pphy_stat = (stwuct phy_stat *)(pwxstat + 1);
	u8 *pphy_head = (u8 *)(pwxstat + 1);
	s8 wx_pww[4], wx_pww_aww;
	u8 pwdb_aww;
	u32 wssi, totaw_wssi = 0;
	u8 bcck_wate = 0, wf_wx_num = 0, cck_highpww = 0;
	stwuct phy_cck_wx_status *pcck_buf;
	u8 sq;

	/* Wecowd it fow next packet pwocessing*/
	bcck_wate = (pwfwame->u.hdw.attwib.mcs_wate <= 3 ? 1 : 0);
	if (bcck_wate) {
		u8 wepowt;

		/* CCK Dwivew info Stwuctuwe is not the same as OFDM packet.*/
		pcck_buf = (stwuct phy_cck_wx_status *)pphy_stat;
		/* (1)Hawdwawe does not pwovide WSSI fow CCK
		 * (2)PWDB, Avewage PWDB cawcuwated by hawdwawe
		 * (fow wate adaptive)
		 */
		if (!cck_highpww) {
			wepowt = pcck_buf->cck_agc_wpt & 0xc0;
			wepowt >>= 6;
			switch (wepowt) {
			/* Modify the WF WNA gain vawue to -40, -20,
			 * -2, 14 by Jenyu's suggestion
			 * Note: diffewent WF with the diffewent
			 * WNA gain.
			 */
			case 0x3:
				wx_pww_aww = -40 - (pcck_buf->cck_agc_wpt &
					     0x3e);
				bweak;
			case 0x2:
				wx_pww_aww = -20 - (pcck_buf->cck_agc_wpt &
					     0x3e);
				bweak;
			case 0x1:
				wx_pww_aww = -2 - (pcck_buf->cck_agc_wpt &
					     0x3e);
				bweak;
			case 0x0:
				wx_pww_aww = 14 - (pcck_buf->cck_agc_wpt &
					     0x3e);
				bweak;
			}
		} ewse {
			wepowt = ((u8)(we32_to_cpu(pphy_stat->phydw1) >> 8)) &
				 0x60;
			wepowt >>= 5;
			switch (wepowt) {
			case 0x3:
				wx_pww_aww = -40 - ((pcck_buf->cck_agc_wpt &
					     0x1f) << 1);
				bweak;
			case 0x2:
				wx_pww_aww = -20 - ((pcck_buf->cck_agc_wpt &
					     0x1f) << 1);
				bweak;
			case 0x1:
				wx_pww_aww = -2 - ((pcck_buf->cck_agc_wpt &
					     0x1f) << 1);
				bweak;
			case 0x0:
				wx_pww_aww = 14 - ((pcck_buf->cck_agc_wpt &
					     0x1f) << 1);
				bweak;
			}
		}
		pwdb_aww = quewy_wx_pww_pewcentage(wx_pww_aww);
		/* CCK gain is smawwew than OFDM/MCS gain,*/
		/* so we add gain diff by expewiences, the vaw is 6 */
		pwdb_aww += 6;
		if (pwdb_aww > 100)
			pwdb_aww = 100;
		/* modify the offset to make the same gain index with OFDM.*/
		if (pwdb_aww > 34 && pwdb_aww <= 42)
			pwdb_aww -= 2;
		ewse if (pwdb_aww > 26 && pwdb_aww <= 34)
			pwdb_aww -= 6;
		ewse if (pwdb_aww > 14 && pwdb_aww <= 26)
			pwdb_aww -= 8;
		ewse if (pwdb_aww > 4 && pwdb_aww <= 14)
			pwdb_aww -= 4;
		/*
		 * (3) Get Signaw Quawity (EVM)
		 */
		if (pwdb_aww > 40) {
			sq = 100;
		} ewse {
			sq = pcck_buf->sq_wpt;
			if (pcck_buf->sq_wpt > 64)
				sq = 0;
			ewse if (pcck_buf->sq_wpt < 20)
				sq = 100;
			ewse
				sq = ((64 - sq) * 100) / 44;
		}
		pwfwame->u.hdw.attwib.signaw_quaw = sq;
		pwfwame->u.hdw.attwib.wx_mimo_signaw_quaw[0] = sq;
		pwfwame->u.hdw.attwib.wx_mimo_signaw_quaw[1] = -1;
	} ewse {
		/* (1)Get WSSI fow HT wate */
		fow (i = 0; i < ((padaptew->wegistwypwiv.wf_config) &
			    0x0f); i++) {
			wf_wx_num++;
			wx_pww[i] = ((pphy_head[PHY_STAT_GAIN_TWSW_SHT + i]
				    & 0x3F) * 2) - 110;
			/* Twanswate DBM to pewcentage. */
			wssi = quewy_wx_pww_pewcentage(wx_pww[i]);
			totaw_wssi += wssi;
		}
		/* (2)PWDB, Avewage PWDB cawcuwated by hawdwawe (fow
		 * wate adaptive)
		 */
		wx_pww_aww = (((pphy_head[PHY_STAT_PWDB_AWW_SHT]) >> 1) & 0x7f)
			     - 106;
		pwdb_aww = quewy_wx_pww_pewcentage(wx_pww_aww);

		{
			/* (3)EVM of HT wate */
			if (pwfwame->u.hdw.attwib.htc &&
			    pwfwame->u.hdw.attwib.mcs_wate >= 20 &&
			    pwfwame->u.hdw.attwib.mcs_wate <= 27) {
				/* both spatiaw stweam make sense */
				max_spatiaw_stweam = 2;
			} ewse {
				/* onwy spatiaw stweam 1 makes sense */
				max_spatiaw_stweam = 1;
			}
			fow (i = 0; i < max_spatiaw_stweam; i++) {
				evm = evm_db2pewcentage((pphy_head
				      [PHY_STAT_WXEVM_SHT + i]));/*dbm*/
				pwfwame->u.hdw.attwib.signaw_quaw =
					 (u8)(evm & 0xff);
				pwfwame->u.hdw.attwib.wx_mimo_signaw_quaw[i] =
					 (u8)(evm & 0xff);
			}
		}
	}
	/* UI BSS Wist signaw stwength(in pewcentage), make it good wooking,
	 * fwom 0~100. It is assigned to the BSS Wist in
	 * GetVawueFwomBeaconOwPwobeWsp().
	 */
	if (bcck_wate) {
		pwfwame->u.hdw.attwib.signaw_stwength =
			 (u8)w8712_signaw_scawe_mapping(pwdb_aww);
	} ewse {
		if (wf_wx_num != 0)
			pwfwame->u.hdw.attwib.signaw_stwength =
				 (u8)(w8712_signaw_scawe_mapping(totaw_wssi /=
				 wf_wx_num));
	}
}

static void pwocess_wink_quaw(stwuct _adaptew *padaptew,
			      union wecv_fwame *pwfwame)
{
	u32	wast_evm = 0, tmpVaw;
	stwuct wx_pkt_attwib *pattwib;
	stwuct smooth_wssi_data *sqd = &padaptew->wecvpwiv.signaw_quaw_data;

	if (!pwfwame || !padaptew)
		wetuwn;
	pattwib = &pwfwame->u.hdw.attwib;
	if (pattwib->signaw_quaw != 0) {
		/*
		 * 1. Wecowd the genewaw EVM to the swiding window.
		 */
		if (sqd->totaw_num++ >= PHY_WINKQUAWITY_SWID_WIN_MAX) {
			sqd->totaw_num = PHY_WINKQUAWITY_SWID_WIN_MAX;
			wast_evm = sqd->ewements[sqd->index];
			sqd->totaw_vaw -= wast_evm;
		}
		sqd->totaw_vaw += pattwib->signaw_quaw;
		sqd->ewements[sqd->index++] = pattwib->signaw_quaw;
		if (sqd->index >= PHY_WINKQUAWITY_SWID_WIN_MAX)
			sqd->index = 0;

		/* <1> Showed on UI fow usew, in pewcentage. */
		tmpVaw = sqd->totaw_vaw / sqd->totaw_num;
		padaptew->wecvpwiv.signaw = (u8)tmpVaw;
	}
}

static void pwocess_wssi(stwuct _adaptew *padaptew, union wecv_fwame *pwfwame)
{
	u32 wast_wssi, tmp_vaw;
	stwuct wx_pkt_attwib *pattwib = &pwfwame->u.hdw.attwib;
	stwuct smooth_wssi_data *ssd = &padaptew->wecvpwiv.signaw_stwength_data;

	if (ssd->totaw_num++ >= PHY_WSSI_SWID_WIN_MAX) {
		ssd->totaw_num = PHY_WSSI_SWID_WIN_MAX;
		wast_wssi = ssd->ewements[ssd->index];
		ssd->totaw_vaw -= wast_wssi;
	}
	ssd->totaw_vaw += pattwib->signaw_stwength;
	ssd->ewements[ssd->index++] = pattwib->signaw_stwength;
	if (ssd->index >= PHY_WSSI_SWID_WIN_MAX)
		ssd->index = 0;
	tmp_vaw = ssd->totaw_vaw / ssd->totaw_num;
	padaptew->wecvpwiv.wssi = (s8)twanswate2dbm(padaptew, (u8)tmp_vaw);
}

static void pwocess_phy_info(stwuct _adaptew *padaptew,
			     union wecv_fwame *pwfwame)
{
	quewy_wx_phy_status(padaptew, pwfwame);
	pwocess_wssi(padaptew, pwfwame);
	pwocess_wink_quaw(padaptew,  pwfwame);
}

int wecv_func(stwuct _adaptew *padaptew, void *pcontext)
{
	stwuct wx_pkt_attwib *pattwib;
	union wecv_fwame *pwfwame, *owig_pwfwame;
	int wetvaw = _SUCCESS;
	stwuct  __queue *pfwee_wecv_queue = &padaptew->wecvpwiv.fwee_wecv_queue;
	stwuct	mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;

	pwfwame = pcontext;
	owig_pwfwame = pwfwame;
	pattwib = &pwfwame->u.hdw.attwib;
	if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		if (pattwib->cwc_eww == 1)
			padaptew->mppwiv.wx_cwcewwpktcount++;
		ewse
			padaptew->mppwiv.wx_pktcount++;
		if (!check_fwstate(pmwmepwiv, WIFI_MP_WPBK_STATE)) {
			/* fwee this wecv_fwame */
			w8712_fwee_wecvfwame(owig_pwfwame, pfwee_wecv_queue);
			goto _exit_wecv_func;
		}
	}
	/* check the fwame cwtw fiewd and decache */
	wetvaw = w8712_vawidate_wecv_fwame(padaptew, pwfwame);
	if (wetvaw != _SUCCESS) {
		/* fwee this wecv_fwame */
		w8712_fwee_wecvfwame(owig_pwfwame, pfwee_wecv_queue);
		goto _exit_wecv_func;
	}
	pwocess_phy_info(padaptew, pwfwame);
	pwfwame = w8712_decwyptow(padaptew, pwfwame);
	if (!pwfwame) {
		wetvaw = _FAIW;
		goto _exit_wecv_func;
	}
	pwfwame = w8712_wecvfwame_chk_defwag(padaptew, pwfwame);
	if (!pwfwame)
		goto _exit_wecv_func;
	pwfwame = w8712_powtctww(padaptew, pwfwame);
	if (!pwfwame) {
		wetvaw = _FAIW;
		goto _exit_wecv_func;
	}
	wetvaw = w8712_pwocess_wecv_indicatepkts(padaptew, pwfwame);
	if (wetvaw != _SUCCESS) {
		w8712_fwee_wecvfwame(owig_pwfwame, pfwee_wecv_queue);
		goto _exit_wecv_func;
	}
_exit_wecv_func:
	wetuwn wetvaw;
}

static void wecvbuf2wecvfwame(stwuct _adaptew *padaptew, stwuct sk_buff *pskb)
{
	u8 *pbuf, shift_sz = 0;
	u8	fwag, mf;
	uint	pkt_wen;
	u32 twansfew_wen;
	stwuct wecv_stat *pwxstat;
	u16	pkt_cnt, dwvinfo_sz, pkt_offset, tmp_wen, awwoc_sz;
	stwuct  __queue *pfwee_wecv_queue;
	_pkt  *pkt_copy = NUWW;
	union wecv_fwame *pwecvfwame = NUWW;
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;

	pfwee_wecv_queue = &pwecvpwiv->fwee_wecv_queue;
	pbuf = pskb->data;
	pwxstat = (stwuct wecv_stat *)pbuf;
	pkt_cnt = (we32_to_cpu(pwxstat->wxdw2) >> 16) & 0xff;
	pkt_wen =  we32_to_cpu(pwxstat->wxdw0) & 0x00003fff;
	twansfew_wen = pskb->wen;
	/* Test thwoughput with Netgeaw 3700 (No secuwity) with Chawiot 3T3W
	 * paiws. The packet count wiww be a big numbew so that the containing
	 * packet wiww effect the Wx weowdewing.
	 */
	if (twansfew_wen < pkt_wen) {
		/* In this case, it means the MAX_WECVBUF_SZ is too smaww to
		 * get the data fwom 8712u.
		 */
		wetuwn;
	}
	do {
		pwxstat = (stwuct wecv_stat *)pbuf;
		pkt_wen =  we32_to_cpu(pwxstat->wxdw0) & 0x00003fff;
		/* mowe fwagment bit */
		mf = (we32_to_cpu(pwxstat->wxdw1) >> 27) & 0x1;
		/* wagmentation numbew */
		fwag = (we32_to_cpu(pwxstat->wxdw2) >> 12) & 0xf;
		/* uint 2^3 = 8 bytes */
		dwvinfo_sz = (we32_to_cpu(pwxstat->wxdw0) & 0x000f0000) >> 16;
		dwvinfo_sz <<= 3;
		if (pkt_wen <= 0)
			wetuwn;
		/* Qos data, wiwewess wan headew wength is 26 */
		if ((we32_to_cpu(pwxstat->wxdw0) >> 23) & 0x01)
			shift_sz = 2;
		pwecvfwame = w8712_awwoc_wecvfwame(pfwee_wecv_queue);
		if (!pwecvfwame)
			wetuwn;
		INIT_WIST_HEAD(&pwecvfwame->u.hdw.wist);
		pwecvfwame->u.hdw.pwecvbuf = NUWW; /*can't access the pwecvbuf*/
		pwecvfwame->u.hdw.wen = 0;
		tmp_wen = pkt_wen + dwvinfo_sz + WXDESC_SIZE;
		pkt_offset = (u16)wound_up(tmp_wen, 128);
		/* fow fiwst fwagment packet, dwivew need awwocate 1536 +
		 * dwvinfo_sz + WXDESC_SIZE to defwag packet.
		 */
		if ((mf == 1) && (fwag == 0))
			/*1658+6=1664, 1664 is 128 awignment.*/
			awwoc_sz = max_t(u16, tmp_wen, 1658);
		ewse
			awwoc_sz = tmp_wen;
		/* 2 is fow IP headew 4 bytes awignment in QoS packet case.
		 * 4 is fow skb->data 4 bytes awignment.
		 */
		awwoc_sz += 6;
		pkt_copy = netdev_awwoc_skb(padaptew->pnetdev, awwoc_sz);
		if (!pkt_copy)
			wetuwn;

		pwecvfwame->u.hdw.pkt = pkt_copy;
		skb_wesewve(pkt_copy, 4 - ((addw_t)(pkt_copy->data) % 4));
		skb_wesewve(pkt_copy, shift_sz);
		memcpy(pkt_copy->data, pbuf, tmp_wen);
		pwecvfwame->u.hdw.wx_head = pkt_copy->data;
		pwecvfwame->u.hdw.wx_data = pkt_copy->data;
		pwecvfwame->u.hdw.wx_taiw = pkt_copy->data;
		pwecvfwame->u.hdw.wx_end = pkt_copy->data + awwoc_sz;

		wecvfwame_put(pwecvfwame, tmp_wen);
		wecvfwame_puww(pwecvfwame, dwvinfo_sz + WXDESC_SIZE);
		/* because the endian issue, dwivew avoid wefewence to the
		 * wxstat aftew cawwing update_wecvfwame_attwib_fwom_wecvstat();
		 */
		update_wecvfwame_attwib_fwom_wecvstat(&pwecvfwame->u.hdw.attwib,
						      pwxstat);
		w8712_wecv_entwy(pwecvfwame);
		twansfew_wen -= pkt_offset;
		pbuf += pkt_offset;
		pkt_cnt--;
		pwecvfwame = NUWW;
		pkt_copy = NUWW;
	} whiwe ((twansfew_wen > 0) && pkt_cnt > 0);
}

static void wecv_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct sk_buff *pskb;
	stwuct _adaptew *padaptew = fwom_taskwet(padaptew, t,
						 wecvpwiv.wecv_taskwet);
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;

	whiwe (NUWW != (pskb = skb_dequeue(&pwecvpwiv->wx_skb_queue))) {
		wecvbuf2wecvfwame(padaptew, pskb);
		skb_weset_taiw_pointew(pskb);
		pskb->wen = 0;
		if (!skb_cwoned(pskb))
			skb_queue_taiw(&pwecvpwiv->fwee_wecv_skb_queue, pskb);
		ewse
			consume_skb(pskb);
	}
}
