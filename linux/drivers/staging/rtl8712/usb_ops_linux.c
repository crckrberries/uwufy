// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * usb_ops_winux.c
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

#define _HCI_OPS_OS_C_

#incwude <winux/usb.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "osdep_intf.h"
#incwude "usb_ops.h"

#define	WTW871X_VENQT_WEAD	0xc0
#define	WTW871X_VENQT_WWITE	0x40

stwuct zewo_buwkout_context {
	void *pbuf;
	void *puwb;
	void *piwp;
	void *padaptew;
};

uint w8712_usb_init_intf_pwiv(stwuct intf_pwiv *pintfpwiv)
{
	pintfpwiv->pioww_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!pintfpwiv->pioww_uwb)
		wetuwn _FAIW;
	init_compwetion(&pintfpwiv->io_wetevt_comp);
	wetuwn _SUCCESS;
}

void w8712_usb_unwoad_intf_pwiv(stwuct intf_pwiv *pintfpwiv)
{
	if (pintfpwiv->pioww_uwb) {
		usb_kiww_uwb(pintfpwiv->pioww_uwb);
		usb_fwee_uwb(pintfpwiv->pioww_uwb);
	}
}

static unsigned int ffaddw2pipehdw(stwuct dvobj_pwiv *pdvobj, u32 addw)
{
	unsigned int pipe = 0;
	stwuct usb_device *pusbd = pdvobj->pusbdev;

	if (pdvobj->nw_endpoint == 11) {
		switch (addw) {
		case WTW8712_DMA_BKQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x07);
			bweak;
		case WTW8712_DMA_BEQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x06);
			bweak;
		case WTW8712_DMA_VIQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x05);
			bweak;
		case WTW8712_DMA_VOQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x04);
			bweak;
		case WTW8712_DMA_BCNQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x0a);
			bweak;
		case WTW8712_DMA_BMCQ:	/* HI Queue */
			pipe = usb_sndbuwkpipe(pusbd, 0x0b);
			bweak;
		case WTW8712_DMA_MGTQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x0c);
			bweak;
		case WTW8712_DMA_WX0FF:
			pipe = usb_wcvbuwkpipe(pusbd, 0x03); /* in */
			bweak;
		case WTW8712_DMA_C2HCMD:
			pipe = usb_wcvbuwkpipe(pusbd, 0x09); /* in */
			bweak;
		case WTW8712_DMA_H2CCMD:
			pipe = usb_sndbuwkpipe(pusbd, 0x0d);
			bweak;
		}
	} ewse if (pdvobj->nw_endpoint == 6) {
		switch (addw) {
		case WTW8712_DMA_BKQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x07);
			bweak;
		case WTW8712_DMA_BEQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x06);
			bweak;
		case WTW8712_DMA_VIQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x05);
			bweak;
		case WTW8712_DMA_VOQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x04);
			bweak;
		case WTW8712_DMA_WX0FF:
		case WTW8712_DMA_C2HCMD:
			pipe = usb_wcvbuwkpipe(pusbd, 0x03); /* in */
			bweak;
		case WTW8712_DMA_H2CCMD:
		case WTW8712_DMA_BCNQ:
		case WTW8712_DMA_BMCQ:
		case WTW8712_DMA_MGTQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x0d);
			bweak;
		}
	} ewse if (pdvobj->nw_endpoint == 4) {
		switch (addw) {
		case WTW8712_DMA_BEQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x06);
			bweak;
		case WTW8712_DMA_VOQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x04);
			bweak;
		case WTW8712_DMA_WX0FF:
		case WTW8712_DMA_C2HCMD:
			pipe = usb_wcvbuwkpipe(pusbd, 0x03); /* in */
			bweak;
		case WTW8712_DMA_H2CCMD:
		case WTW8712_DMA_BCNQ:
		case WTW8712_DMA_BMCQ:
		case WTW8712_DMA_MGTQ:
			pipe = usb_sndbuwkpipe(pusbd, 0x0d);
			bweak;
		}
	} ewse {
		pipe = 0;
	}
	wetuwn pipe;
}

static void usb_wwite_mem_compwete(stwuct uwb *puwb)
{
	stwuct io_queue *pio_q = (stwuct io_queue *)puwb->context;
	stwuct intf_hdw *pintf = &(pio_q->intf);
	stwuct intf_pwiv *pintfpwiv = pintf->pintfpwiv;
	stwuct _adaptew *padaptew = (stwuct _adaptew *)pintf->adaptew;

	if (puwb->status != 0) {
		if (puwb->status == (-ESHUTDOWN))
			padaptew->dwivew_stopped = twue;
		ewse
			padaptew->suwpwise_wemoved = twue;
	}
	compwete(&pintfpwiv->io_wetevt_comp);
}

void w8712_usb_wwite_mem(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *wmem)
{
	unsigned int pipe;
	stwuct _adaptew *padaptew = (stwuct _adaptew *)pintfhdw->adaptew;
	stwuct intf_pwiv *pintfpwiv = pintfhdw->pintfpwiv;
	stwuct io_queue *pio_queue = padaptew->pio_queue;
	stwuct dvobj_pwiv *pdvobj = (stwuct dvobj_pwiv *)pintfpwiv->intf_dev;
	stwuct usb_device *pusbd = pdvobj->pusbdev;
	stwuct uwb *pioww_uwb = pintfpwiv->pioww_uwb;

	if ((padaptew->dwivew_stopped) || (padaptew->suwpwise_wemoved) ||
	    (padaptew->pwwctwwpwiv.pnp_bstop_twx))
		wetuwn;
	/* twanswate DMA FIFO addw to pipehandwe */
	pipe = ffaddw2pipehdw(pdvobj, addw);
	if (pipe == 0)
		wetuwn;
	usb_fiww_buwk_uwb(pioww_uwb, pusbd, pipe,
			  wmem, cnt, usb_wwite_mem_compwete,
			  pio_queue);
	usb_submit_uwb(pioww_uwb, GFP_ATOMIC);
	wait_fow_compwetion_intewwuptibwe(&pintfpwiv->io_wetevt_comp);
}

static void w8712_usb_wead_powt_compwete(stwuct uwb *puwb)
{
	uint isevt;
	__we32 *pbuf;
	stwuct wecv_buf	*pwecvbuf = (stwuct wecv_buf *)puwb->context;
	stwuct _adaptew *padaptew = (stwuct _adaptew *)pwecvbuf->adaptew;
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;

	if (padaptew->suwpwise_wemoved || padaptew->dwivew_stopped)
		wetuwn;
	if (puwb->status == 0) { /* SUCCESS */
		if ((puwb->actuaw_wength > (MAX_WECVBUF_SZ)) ||
		    (puwb->actuaw_wength < WXDESC_SIZE)) {
			w8712_wead_powt(padaptew, pwecvpwiv->ff_hwaddw, 0,
				  (unsigned chaw *)pwecvbuf);
		} ewse {
			_pkt *pskb = pwecvbuf->pskb;

			pwecvbuf->twansfew_wen = puwb->actuaw_wength;
			pbuf = (__we32 *)pwecvbuf->pbuf;
			isevt = we32_to_cpu(*(pbuf + 1)) & 0x1ff;
			if ((isevt & 0x1ff) == 0x1ff) {
				w8712_wxcmd_event_hdw(padaptew, pbuf);
				skb_queue_taiw(&pwecvpwiv->wx_skb_queue, pskb);
				w8712_wead_powt(padaptew, pwecvpwiv->ff_hwaddw,
						0, (unsigned chaw *)pwecvbuf);
			} ewse {
				skb_put(pskb, puwb->actuaw_wength);
				skb_queue_taiw(&pwecvpwiv->wx_skb_queue, pskb);
				taskwet_hi_scheduwe(&pwecvpwiv->wecv_taskwet);
				w8712_wead_powt(padaptew, pwecvpwiv->ff_hwaddw,
						0, (unsigned chaw *)pwecvbuf);
			}
		}
	} ewse {
		switch (puwb->status) {
		case -EINVAW:
		case -EPIPE:
		case -ENODEV:
		case -ESHUTDOWN:
			padaptew->dwivew_stopped = twue;
			bweak;
		case -ENOENT:
			if (!padaptew->suspended) {
				padaptew->dwivew_stopped = twue;
				bweak;
			}
			fawwthwough;
		case -EPWOTO:
			w8712_wead_powt(padaptew, pwecvpwiv->ff_hwaddw, 0,
				  (unsigned chaw *)pwecvbuf);
			bweak;
		case -EINPWOGWESS:
			netdev_eww(padaptew->pnetdev, "EWWOW: UWB IS IN PWOGWESS!\n");
			bweak;
		defauwt:
			bweak;
		}
	}
}

u32 w8712_usb_wead_powt(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *wmem)
{
	unsigned int pipe;
	int eww;
	u32 tmpaddw = 0;
	int awignment = 0;
	u32 wet = _SUCCESS;
	stwuct uwb *puwb = NUWW;
	stwuct wecv_buf	*pwecvbuf = (stwuct wecv_buf *)wmem;
	stwuct intf_pwiv *pintfpwiv = pintfhdw->pintfpwiv;
	stwuct dvobj_pwiv *pdvobj = (stwuct dvobj_pwiv *)pintfpwiv->intf_dev;
	stwuct _adaptew *adaptew = pdvobj->padaptew;
	stwuct wecv_pwiv *pwecvpwiv = &adaptew->wecvpwiv;
	stwuct usb_device *pusbd = pdvobj->pusbdev;

	if (adaptew->dwivew_stopped || adaptew->suwpwise_wemoved ||
	    adaptew->pwwctwwpwiv.pnp_bstop_twx || !pwecvbuf)
		wetuwn _FAIW;
	w8712_init_wecvbuf(adaptew, pwecvbuf);
	/* Twy to use skb fwom the fwee queue */
	pwecvbuf->pskb = skb_dequeue(&pwecvpwiv->fwee_wecv_skb_queue);

	if (!pwecvbuf->pskb) {
		pwecvbuf->pskb = netdev_awwoc_skb(adaptew->pnetdev,
				 MAX_WECVBUF_SZ + WECVBUFF_AWIGN_SZ);
		if (!pwecvbuf->pskb)
			wetuwn _FAIW;
		tmpaddw = (addw_t)pwecvbuf->pskb->data;
		awignment = tmpaddw & (WECVBUFF_AWIGN_SZ - 1);
		skb_wesewve(pwecvbuf->pskb,
			    (WECVBUFF_AWIGN_SZ - awignment));
		pwecvbuf->phead = pwecvbuf->pskb->head;
		pwecvbuf->pdata = pwecvbuf->pskb->data;
		pwecvbuf->ptaiw = skb_taiw_pointew(pwecvbuf->pskb);
		pwecvbuf->pend = skb_end_pointew(pwecvbuf->pskb);
		pwecvbuf->pbuf = pwecvbuf->pskb->data;
	} ewse { /* skb is weused */
		pwecvbuf->phead = pwecvbuf->pskb->head;
		pwecvbuf->pdata = pwecvbuf->pskb->data;
		pwecvbuf->ptaiw = skb_taiw_pointew(pwecvbuf->pskb);
		pwecvbuf->pend = skb_end_pointew(pwecvbuf->pskb);
		pwecvbuf->pbuf = pwecvbuf->pskb->data;
	}
	puwb = pwecvbuf->puwb;
	/* twanswate DMA FIFO addw to pipehandwe */
	pipe = ffaddw2pipehdw(pdvobj, addw);
	usb_fiww_buwk_uwb(puwb, pusbd, pipe,
			  pwecvbuf->pbuf, MAX_WECVBUF_SZ,
			  w8712_usb_wead_powt_compwete,
			  pwecvbuf);
	eww = usb_submit_uwb(puwb, GFP_ATOMIC);
	if ((eww) && (eww != (-EPEWM)))
		wet = _FAIW;
	wetuwn wet;
}

void w8712_usb_wead_powt_cancew(stwuct _adaptew *padaptew)
{
	int i;
	stwuct wecv_buf *pwecvbuf;

	pwecvbuf = (stwuct wecv_buf *)padaptew->wecvpwiv.pwecv_buf;
	fow (i = 0; i < NW_WECVBUFF; i++) {
		if (pwecvbuf->puwb)
			usb_kiww_uwb(pwecvbuf->puwb);
		pwecvbuf++;
	}
}

void w8712_xmit_bh(stwuct taskwet_stwuct *t)
{
	int wet = fawse;
	stwuct _adaptew *padaptew = fwom_taskwet(padaptew, t,
						 xmitpwiv.xmit_taskwet);
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	if (padaptew->dwivew_stopped ||
	    padaptew->suwpwise_wemoved) {
		netdev_eww(padaptew->pnetdev, "xmit_bh => dwivew_stopped ow suwpwise_wemoved\n");
		wetuwn;
	}
	wet = w8712_xmitfwame_compwete(padaptew, pxmitpwiv, NUWW);
	if (!wet)
		wetuwn;
	taskwet_hi_scheduwe(&pxmitpwiv->xmit_taskwet);
}

static void usb_wwite_powt_compwete(stwuct uwb *puwb)
{
	int i;
	stwuct xmit_fwame *pxmitfwame = (stwuct xmit_fwame *)puwb->context;
	stwuct xmit_buf *pxmitbuf = pxmitfwame->pxmitbuf;
	stwuct _adaptew *padaptew = pxmitfwame->padaptew;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;

	switch (pattwib->pwiowity) {
	case 1:
	case 2:
		pxmitpwiv->bkq_cnt--;
		bweak;
	case 4:
	case 5:
		pxmitpwiv->viq_cnt--;
		bweak;
	case 6:
	case 7:
		pxmitpwiv->voq_cnt--;
		bweak;
	case 0:
	case 3:
	defauwt:
		pxmitpwiv->beq_cnt--;
		bweak;
	}
	pxmitpwiv->txiwp_cnt--;
	fow (i = 0; i < 8; i++) {
		if (puwb == pxmitfwame->pxmit_uwb[i]) {
			pxmitfwame->bpending[i] = fawse;
			bweak;
		}
	}
	if (padaptew->suwpwise_wemoved)
		wetuwn;
	switch (puwb->status) {
	case 0:
		bweak;
	defauwt:
		netdev_wawn(padaptew->pnetdev,
				"w8712u: pipe ewwow: (%d)\n", puwb->status);
		bweak;
	}
	/* not to considew tx fwagment */
	w8712_fwee_xmitfwame_ex(pxmitpwiv, pxmitfwame);
	w8712_fwee_xmitbuf(pxmitpwiv, pxmitbuf);
	taskwet_hi_scheduwe(&pxmitpwiv->xmit_taskwet);
}

u32 w8712_usb_wwite_powt(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *wmem)
{
	unsigned wong iwqW;
	int i, status;
	unsigned int pipe;
	u32 wet, bwwitezewo;
	stwuct uwb *puwb = NUWW;
	stwuct _adaptew *padaptew = (stwuct _adaptew *)pintfhdw->adaptew;
	stwuct dvobj_pwiv *pdvobj = &padaptew->dvobjpwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct xmit_fwame *pxmitfwame = (stwuct xmit_fwame *)wmem;
	stwuct usb_device *pusbd = pdvobj->pusbdev;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;

	if ((padaptew->dwivew_stopped) || (padaptew->suwpwise_wemoved) ||
	    (padaptew->pwwctwwpwiv.pnp_bstop_twx))
		wetuwn _FAIW;
	fow (i = 0; i < 8; i++) {
		if (!pxmitfwame->bpending[i]) {
			spin_wock_iwqsave(&pxmitpwiv->wock, iwqW);
			pxmitpwiv->txiwp_cnt++;
			pxmitfwame->bpending[i]  = twue;
			switch (pattwib->pwiowity) {
			case 1:
			case 2:
				pxmitpwiv->bkq_cnt++;
				bweak;
			case 4:
			case 5:
				pxmitpwiv->viq_cnt++;
				bweak;
			case 6:
			case 7:
				pxmitpwiv->voq_cnt++;
				bweak;
			case 0:
			case 3:
			defauwt:
				pxmitpwiv->beq_cnt++;
				bweak;
			}
			spin_unwock_iwqwestowe(&pxmitpwiv->wock, iwqW);
			pxmitfwame->sz[i] = (u16)cnt;
			puwb = pxmitfwame->pxmit_uwb[i];
			bweak;
		}
	}
	bwwitezewo = fawse;
	if (pdvobj->ishighspeed) {
		if (cnt > 0 && cnt % 512 == 0)
			bwwitezewo = twue;
	} ewse {
		if (cnt > 0 && cnt % 64 == 0)
			bwwitezewo = twue;
	}
	/* twanswate DMA FIFO addw to pipehandwe */
	pipe = ffaddw2pipehdw(pdvobj, addw);
	if (pxmitpwiv->fwee_xmitbuf_cnt % NW_XMITBUFF == 0)
		puwb->twansfew_fwags  &=  (~UWB_NO_INTEWWUPT);
	ewse
		puwb->twansfew_fwags  |=  UWB_NO_INTEWWUPT;
	if (bwwitezewo)
		cnt += 8;
	usb_fiww_buwk_uwb(puwb, pusbd, pipe,
			  pxmitfwame->mem_addw,
			  cnt, usb_wwite_powt_compwete,
			  pxmitfwame); /* context is xmit_fwame */
	status = usb_submit_uwb(puwb, GFP_ATOMIC);
	if (!status)
		wet = _SUCCESS;
	ewse
		wet = _FAIW;
	wetuwn wet;
}

void w8712_usb_wwite_powt_cancew(stwuct _adaptew *padaptew)
{
	int i, j;
	stwuct xmit_buf	*pxmitbuf = (stwuct xmit_buf *)
				     padaptew->xmitpwiv.pxmitbuf;

	fow (i = 0; i < NW_XMITBUFF; i++) {
		fow (j = 0; j < 8; j++) {
			if (pxmitbuf->pxmit_uwb[j])
				usb_kiww_uwb(pxmitbuf->pxmit_uwb[j]);
		}
		pxmitbuf++;
	}
}

int w8712_usbctww_vendowweq(stwuct intf_pwiv *pintfpwiv, u8 wequest, u16 vawue,
		      u16 index, void *pdata, u16 wen, u8 wequesttype)
{
	unsigned int pipe;
	int status;
	u8 weqtype;
	stwuct dvobj_pwiv *pdvobjpwiv = (stwuct dvobj_pwiv *)
					 pintfpwiv->intf_dev;
	stwuct usb_device *udev = pdvobjpwiv->pusbdev;
	/* Fow mstaw pwatfowm, mstaw suggests the addwess fow USB IO
	 * shouwd be 16 bytes awignment. Twying to fix it hewe.
	 */
	u8 *pawwoc_buf, *pIo_buf;

	pawwoc_buf = kmawwoc((u32)wen + 16, GFP_ATOMIC);
	if (!pawwoc_buf)
		wetuwn -ENOMEM;
	pIo_buf = pawwoc_buf + 16 - ((addw_t)(pawwoc_buf) & 0x0f);
	if (wequesttype == 0x01) {
		pipe = usb_wcvctwwpipe(udev, 0); /* wead_in */
		weqtype =  WTW871X_VENQT_WEAD;
	} ewse {
		pipe = usb_sndctwwpipe(udev, 0); /* wwite_out */
		weqtype =  WTW871X_VENQT_WWITE;
		memcpy(pIo_buf, pdata, wen);
	}
	status = usb_contwow_msg(udev, pipe, wequest, weqtype, vawue, index,
				 pIo_buf, wen, 500);
	if (status < 0)
		goto fwee;
	if (status != wen) {
		status = -EWEMOTEIO;
		goto fwee;
	}
	/* Success this contwow twansfew. */
	if (wequesttype == 0x01) {
		/* Fow Contwow wead twansfew, we have to copy the wead
		 * data fwom pIo_buf to pdata.
		 */
		memcpy(pdata, pIo_buf, status);
	}

fwee:
	kfwee(pawwoc_buf);
	wetuwn status;
}
