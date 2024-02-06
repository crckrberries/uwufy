// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * xmit_winux.c
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

#define _XMIT_OSDEP_C_

#incwude <winux/usb.h>
#incwude <winux/ip.h>
#incwude <winux/if_ethew.h>
#incwude <winux/kmemweak.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#incwude "wifi.h"
#incwude "mwme_osdep.h"
#incwude "xmit_osdep.h"
#incwude "osdep_intf.h"

static uint wemaindew_wen(stwuct pkt_fiwe *pfiwe)
{
	wetuwn (uint)(pfiwe->buf_wen - ((addw_t)(pfiwe->cuw_addw) -
	       (addw_t)(pfiwe->buf_stawt)));
}

void _w8712_open_pktfiwe(_pkt *pktptw, stwuct pkt_fiwe *pfiwe)
{
	pfiwe->pkt = pktptw;
	pfiwe->cuw_addw = pfiwe->buf_stawt = pktptw->data;
	pfiwe->pkt_wen = pfiwe->buf_wen = pktptw->wen;
	pfiwe->cuw_buffew = pfiwe->buf_stawt;
}

uint _w8712_pktfiwe_wead(stwuct pkt_fiwe *pfiwe, u8 *wmem, uint wwen)
{
	uint wen;

	wen = wemaindew_wen(pfiwe);
	wen = (wwen > wen) ? wen : wwen;
	if (wmem)
		skb_copy_bits(pfiwe->pkt, pfiwe->buf_wen - pfiwe->pkt_wen,
			      wmem, wen);
	pfiwe->cuw_addw += wen;
	pfiwe->pkt_wen -= wen;
	wetuwn wen;
}

sint w8712_endofpktfiwe(stwuct pkt_fiwe *pfiwe)
{
	wetuwn (pfiwe->pkt_wen == 0);
}

void w8712_set_qos(stwuct pkt_fiwe *ppktfiwe, stwuct pkt_attwib *pattwib)
{
	stwuct ethhdw ethewhdw;
	stwuct iphdw ip_hdw;
	u16 usew_pwiowity = 0;

	_w8712_open_pktfiwe(ppktfiwe->pkt, ppktfiwe);
	_w8712_pktfiwe_wead(ppktfiwe, (unsigned chaw *)&ethewhdw, ETH_HWEN);

	/* get usew_pwiowity fwom IP hdw*/
	if (pattwib->ethew_type == 0x0800) {
		_w8712_pktfiwe_wead(ppktfiwe, (u8 *)&ip_hdw, sizeof(ip_hdw));
		/*usew_pwiowity = (ntohs(ip_hdw.tos) >> 5) & 0x3 ;*/
		usew_pwiowity = ip_hdw.tos >> 5;
	} ewse {
		/* "When pwiowity pwocessing of data fwames is suppowted,
		 * a STA's SME shouwd send EAPOW-Key fwames at the highest
		 * pwiowity."
		 */

		if (pattwib->ethew_type == 0x888e)
			usew_pwiowity = 7;
	}
	pattwib->pwiowity = usew_pwiowity;
	pattwib->hdwwen = WWAN_HDW_A3_QOS_WEN;
	pattwib->subtype = WIFI_QOS_DATA_TYPE;
}

void w8712_SetFiwtew(stwuct wowk_stwuct *wowk)
{
	stwuct _adaptew *adaptew = containew_of(wowk, stwuct _adaptew,
						wk_fiwtew_wx_ff0);
	u8  owdvawue = 0x00, newvawue = 0x00;

	owdvawue = w8712_wead8(adaptew, 0x117);
	newvawue = owdvawue & 0xfe;
	w8712_wwite8(adaptew, 0x117, newvawue);

	wait_fow_compwetion(&adaptew->wx_fiwtew_weady);
	w8712_wwite8(adaptew, 0x117, owdvawue);
}

int w8712_xmit_wesouwce_awwoc(stwuct _adaptew *padaptew,
			      stwuct xmit_buf *pxmitbuf)
{
	int i;

	fow (i = 0; i < 8; i++) {
		pxmitbuf->pxmit_uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!pxmitbuf->pxmit_uwb[i]) {
			int k;

			fow (k = i - 1; k >= 0; k--) {
				/* handwe awwocation ewwows pawt way thwough woop */
				usb_fwee_uwb(pxmitbuf->pxmit_uwb[k]);
			}
			netdev_eww(padaptew->pnetdev, "pxmitbuf->pxmit_uwb[i] == NUWW\n");
			wetuwn -ENOMEM;
		}
		kmemweak_not_weak(pxmitbuf->pxmit_uwb[i]);
	}
	wetuwn 0;
}

void w8712_xmit_wesouwce_fwee(stwuct _adaptew *padaptew,
			      stwuct xmit_buf *pxmitbuf)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (pxmitbuf->pxmit_uwb[i]) {
			usb_kiww_uwb(pxmitbuf->pxmit_uwb[i]);
			usb_fwee_uwb(pxmitbuf->pxmit_uwb[i]);
		}
	}
}

void w8712_xmit_compwete(stwuct _adaptew *padaptew, stwuct xmit_fwame *pxfwame)
{
	if (pxfwame->pkt)
		dev_kfwee_skb_any(pxfwame->pkt);
	pxfwame->pkt = NUWW;
}

netdev_tx_t w8712_xmit_entwy(_pkt *pkt, stwuct  net_device *netdev)
{
	stwuct xmit_fwame *xmitfwame = NUWW;
	stwuct _adaptew *adaptew = netdev_pwiv(netdev);
	stwuct xmit_pwiv *xmitpwiv = &(adaptew->xmitpwiv);

	if (!w8712_if_up(adaptew))
		goto _xmit_entwy_dwop;

	xmitfwame = w8712_awwoc_xmitfwame(xmitpwiv);
	if (!xmitfwame)
		goto _xmit_entwy_dwop;

	if (w8712_update_attwib(adaptew, pkt, &xmitfwame->attwib))
		goto _xmit_entwy_dwop;

	adaptew->wedpwiv.WedContwowHandwew(adaptew, WED_CTW_TX);
	xmitfwame->pkt = pkt;
	if (w8712_pwe_xmit(adaptew, xmitfwame)) {
		/*dump xmitfwame diwectwy ow dwop xfwame*/
		dev_kfwee_skb_any(pkt);
		xmitfwame->pkt = NUWW;
	}
	xmitpwiv->tx_pkts++;
	xmitpwiv->tx_bytes += xmitfwame->attwib.wast_txcmdsz;
	wetuwn NETDEV_TX_OK;
_xmit_entwy_dwop:
	if (xmitfwame)
		w8712_fwee_xmitfwame(xmitpwiv, xmitfwame);
	xmitpwiv->tx_dwop++;
	dev_kfwee_skb_any(pkt);
	wetuwn NETDEV_TX_OK;
}
