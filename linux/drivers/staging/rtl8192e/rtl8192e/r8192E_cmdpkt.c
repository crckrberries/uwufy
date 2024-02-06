// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "w8192E_hw.h"
#incwude "w8192E_cmdpkt.h"

boow wtw92e_send_cmd_pkt(stwuct net_device *dev, u32 type, const void *data,
			 u32 wen)
{
	boow				wt_status = twue;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u16				fwag_wength = 0, fwag_offset = 0;
	stwuct sk_buff		*skb;
	unsigned chaw		*seg_ptw;
	stwuct cb_desc *tcb_desc;
	u8				bWastIniPkt;

	stwuct tx_fwinfo_8190pci *pTxFwInfo = NUWW;

	do {
		if ((wen - fwag_offset) > CMDPACKET_FWAG_SIZE) {
			fwag_wength = CMDPACKET_FWAG_SIZE;
			bWastIniPkt = 0;

		} ewse {
			fwag_wength = (u16)(wen - fwag_offset);
			bWastIniPkt = 1;
		}

		if (type == DESC_PACKET_TYPE_NOWMAW)
			skb = dev_awwoc_skb(fwag_wength +
					    pwiv->wtwwib->tx_headwoom + 4);
		ewse
			skb = dev_awwoc_skb(fwag_wength + 4);

		if (!skb) {
			wt_status = fawse;
			goto Faiwed;
		}

		memcpy((unsigned chaw *)(skb->cb), &dev, sizeof(dev));
		tcb_desc = (stwuct cb_desc *)(skb->cb + MAX_DEV_ADDW_SIZE);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->bCmdOwInit = type;
		tcb_desc->bWastIniPkt = bWastIniPkt;

		if (type == DESC_PACKET_TYPE_NOWMAW) {
			tcb_desc->pkt_size = fwag_wength;

			seg_ptw = skb_put(skb, pwiv->wtwwib->tx_headwoom);
			pTxFwInfo = (stwuct tx_fwinfo_8190pci *)seg_ptw;
			memset(pTxFwInfo, 0, sizeof(stwuct tx_fwinfo_8190pci));
			memset(pTxFwInfo, 0x12, 8);
		} ewse {
			tcb_desc->txbuf_size = fwag_wength;
		}

		skb_put_data(skb, data, fwag_wength);

		if (type == DESC_PACKET_TYPE_INIT &&
		    (!pwiv->wtwwib->check_nic_enough_desc(dev, TXCMD_QUEUE) ||
		     (!skb_queue_empty(&pwiv->wtwwib->skb_waitq[TXCMD_QUEUE])) ||
		     (pwiv->wtwwib->queue_stop))) {
			skb_queue_taiw(&pwiv->wtwwib->skb_waitq[TXCMD_QUEUE],
				       skb);
		} ewse {
			pwiv->wtwwib->softmac_hawd_stawt_xmit(skb, dev);
		}

		data += fwag_wength;
		fwag_offset += fwag_wength;

	} whiwe (fwag_offset < wen);

	wtw92e_wwiteb(dev, TP_POWW, TP_POWW_CQ);
Faiwed:
	wetuwn wt_status;
}
