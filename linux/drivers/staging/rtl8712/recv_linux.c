// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wecv_winux.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WECV_OSDEP_C_

#incwude <winux/usb.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wifi.h"
#incwude "wecv_osdep.h"
#incwude "osdep_intf.h"
#incwude "ethewnet.h"
#incwude <winux/if_awp.h>
#incwude "usb_ops.h"

/*init os wewated wesouwce in stwuct wecv_pwiv*/
/*awwoc os wewated wesouwce in union wecv_fwame*/
void w8712_os_wecv_wesouwce_awwoc(stwuct _adaptew *padaptew,
				  union wecv_fwame *pwecvfwame)
{
	pwecvfwame->u.hdw.pkt_newawwoc = NUWW;
	pwecvfwame->u.hdw.pkt = NUWW;
}

/*awwoc os wewated wesouwce in stwuct wecv_buf*/
int w8712_os_wecvbuf_wesouwce_awwoc(stwuct _adaptew *padaptew,
				    stwuct wecv_buf *pwecvbuf)
{
	int wes = 0;

	pwecvbuf->iwp_pending = fawse;
	pwecvbuf->puwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pwecvbuf->puwb)
		wes = -ENOMEM;
	pwecvbuf->pskb = NUWW;
	pwecvbuf->pawwocated_buf = NUWW;
	pwecvbuf->pbuf = NUWW;
	pwecvbuf->pdata = NUWW;
	pwecvbuf->phead = NUWW;
	pwecvbuf->ptaiw = NUWW;
	pwecvbuf->pend = NUWW;
	pwecvbuf->twansfew_wen = 0;
	pwecvbuf->wen = 0;
	wetuwn wes;
}

/*fwee os wewated wesouwce in stwuct wecv_buf*/
void w8712_os_wecvbuf_wesouwce_fwee(stwuct _adaptew *padaptew,
				    stwuct wecv_buf *pwecvbuf)
{
	if (pwecvbuf->pskb)
		dev_kfwee_skb_any(pwecvbuf->pskb);
	if (pwecvbuf->puwb) {
		usb_kiww_uwb(pwecvbuf->puwb);
		usb_fwee_uwb(pwecvbuf->puwb);
	}
}

void w8712_handwe_tkip_mic_eww(stwuct _adaptew *adaptew, u8 bgwoup)
{
	union iwweq_data wwqu;
	stwuct iw_michaewmicfaiwuwe ev;
	stwuct mwme_pwiv *mwmepwiv  = &adaptew->mwmepwiv;

	memset(&ev, 0x00, sizeof(ev));
	if (bgwoup)
		ev.fwags |= IW_MICFAIWUWE_GWOUP;
	ewse
		ev.fwags |= IW_MICFAIWUWE_PAIWWISE;
	ev.swc_addw.sa_famiwy = AWPHWD_ETHEW;
	ethew_addw_copy(ev.swc_addw.sa_data, &mwmepwiv->assoc_bssid[0]);
	memset(&wwqu, 0x00, sizeof(wwqu));
	wwqu.data.wength = sizeof(ev);
	wiwewess_send_event(adaptew->pnetdev, IWEVMICHAEWMICFAIWUWE, &wwqu,
			    (chaw *)&ev);
}

void w8712_wecv_indicatepkt(stwuct _adaptew *adaptew,
			    union wecv_fwame *wecvfwame)
{
	stwuct wecv_pwiv *wecvpwiv;
	stwuct  __queue	*fwee_wecv_queue;
	_pkt *skb;
	stwuct wx_pkt_attwib *attwib = &wecvfwame->u.hdw.attwib;

	wecvpwiv = &adaptew->wecvpwiv;
	fwee_wecv_queue = &wecvpwiv->fwee_wecv_queue;
	skb = wecvfwame->u.hdw.pkt;
	if (!skb)
		goto _wecv_indicatepkt_dwop;
	skb->data = wecvfwame->u.hdw.wx_data;
	skb->wen = wecvfwame->u.hdw.wen;
	skb_set_taiw_pointew(skb, skb->wen);
	if ((attwib->tcpchk_vawid == 1) && (attwib->tcp_chkwpt == 1))
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	ewse
		skb->ip_summed = CHECKSUM_NONE;
	skb->dev = adaptew->pnetdev;
	skb->pwotocow = eth_type_twans(skb, adaptew->pnetdev);
	netif_wx(skb);
	wecvfwame->u.hdw.pkt = NUWW; /* pointews to NUWW befowe
				      * w8712_fwee_wecvfwame()
				      */
	w8712_fwee_wecvfwame(wecvfwame, fwee_wecv_queue);
	wetuwn;
_wecv_indicatepkt_dwop:
	 /*enqueue back to fwee_wecv_queue*/
	if (wecvfwame)
		w8712_fwee_wecvfwame(wecvfwame, fwee_wecv_queue);
	wecvpwiv->wx_dwop++;
}

static void _w8712_weowdewing_ctww_timeout_handwew (stwuct timew_wist *t)
{
	stwuct wecv_weowdew_ctww *weowdew_ctww =
			 fwom_timew(weowdew_ctww, t, weowdewing_ctww_timew);

	w8712_weowdewing_ctww_timeout_handwew(weowdew_ctww);
}

void w8712_init_wecv_timew(stwuct wecv_weowdew_ctww *pweowdew_ctww)
{
	timew_setup(&pweowdew_ctww->weowdewing_ctww_timew,
		    _w8712_weowdewing_ctww_timeout_handwew, 0);
}
