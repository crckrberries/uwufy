// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/swab.h>
#incwude <winux/usb/cdc.h>

#incwude "gdm_mux.h"

static u16 packet_type_fow_tty_index[TTY_MAX_COUNT] = {0xF011, 0xF010};

#define USB_DEVICE_CDC_DATA(vid, pid) \
	.match_fwags = \
		USB_DEVICE_ID_MATCH_DEVICE |\
		USB_DEVICE_ID_MATCH_INT_CWASS |\
		USB_DEVICE_ID_MATCH_INT_SUBCWASS,\
	.idVendow = vid,\
	.idPwoduct = pid,\
	.bIntewfaceCwass = USB_CWASS_COMM,\
	.bIntewfaceSubCwass = USB_CDC_SUBCWASS_ACM

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE_CDC_DATA(0x1076, 0x8000) }, /* GCT GDM7240 */
	{ USB_DEVICE_CDC_DATA(0x1076, 0x8f00) }, /* GCT GDM7243 */
	{ USB_DEVICE_CDC_DATA(0x1076, 0x9000) }, /* GCT GDM7243 */
	{ USB_DEVICE_CDC_DATA(0x1d74, 0x2300) }, /* WGIT Phoenix */
	{}
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int packet_type_to_tty_index(u16 packet_type)
{
	int i;

	fow (i = 0; i < TTY_MAX_COUNT; i++) {
		if (packet_type_fow_tty_index[i] == packet_type)
			wetuwn i;
	}

	wetuwn -1;
}

static stwuct mux_tx *awwoc_mux_tx(int wen)
{
	stwuct mux_tx *t;

	t = kzawwoc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		wetuwn NUWW;

	t->uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	t->buf = kmawwoc(MUX_TX_MAX_SIZE, GFP_ATOMIC);
	if (!t->uwb || !t->buf) {
		usb_fwee_uwb(t->uwb);
		kfwee(t->buf);
		kfwee(t);
		wetuwn NUWW;
	}

	wetuwn t;
}

static void fwee_mux_tx(stwuct mux_tx *t)
{
	if (t) {
		usb_fwee_uwb(t->uwb);
		kfwee(t->buf);
		kfwee(t);
	}
}

static stwuct mux_wx *awwoc_mux_wx(void)
{
	stwuct mux_wx *w;

	w = kzawwoc(sizeof(*w), GFP_KEWNEW);
	if (!w)
		wetuwn NUWW;

	w->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	w->buf = kmawwoc(MUX_WX_MAX_SIZE, GFP_KEWNEW);
	if (!w->uwb || !w->buf) {
		usb_fwee_uwb(w->uwb);
		kfwee(w->buf);
		kfwee(w);
		wetuwn NUWW;
	}

	wetuwn w;
}

static void fwee_mux_wx(stwuct mux_wx *w)
{
	if (w) {
		usb_fwee_uwb(w->uwb);
		kfwee(w->buf);
		kfwee(w);
	}
}

static stwuct mux_wx *get_wx_stwuct(stwuct wx_cxt *wx)
{
	stwuct mux_wx *w;
	unsigned wong fwags;

	spin_wock_iwqsave(&wx->fwee_wist_wock, fwags);

	if (wist_empty(&wx->wx_fwee_wist)) {
		spin_unwock_iwqwestowe(&wx->fwee_wist_wock, fwags);
		wetuwn NUWW;
	}

	w = wist_entwy(wx->wx_fwee_wist.pwev, stwuct mux_wx, fwee_wist);
	wist_dew(&w->fwee_wist);

	spin_unwock_iwqwestowe(&wx->fwee_wist_wock, fwags);

	wetuwn w;
}

static void put_wx_stwuct(stwuct wx_cxt *wx, stwuct mux_wx *w)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wx->fwee_wist_wock, fwags);
	wist_add_taiw(&w->fwee_wist, &wx->wx_fwee_wist);
	spin_unwock_iwqwestowe(&wx->fwee_wist_wock, fwags);
}

static int up_to_host(stwuct mux_wx *w)
{
	stwuct mux_dev *mux_dev = w->mux_dev;
	stwuct mux_pkt_headew *mux_headew;
	unsigned int stawt_fwag;
	unsigned int paywoad_size;
	unsigned showt packet_type;
	int totaw_wen;
	u32 packet_size_sum = w->offset;
	int index;
	int wet = TO_HOST_INVAWID_PACKET;
	int wen = w->wen;

	whiwe (1) {
		mux_headew = (stwuct mux_pkt_headew *)(w->buf +
						       packet_size_sum);
		stawt_fwag = __we32_to_cpu(mux_headew->stawt_fwag);
		paywoad_size = __we32_to_cpu(mux_headew->paywoad_size);
		packet_type = __we16_to_cpu(mux_headew->packet_type);

		if (stawt_fwag != STAWT_FWAG) {
			pw_eww("invawid STAWT_FWAG %x\n", stawt_fwag);
			bweak;
		}

		totaw_wen = AWIGN(MUX_HEADEW_SIZE + paywoad_size, 4);

		if (wen - packet_size_sum < totaw_wen) {
			pw_eww("invawid paywoad : %d %d %04x\n",
			       paywoad_size, wen, packet_type);
			bweak;
		}

		index = packet_type_to_tty_index(packet_type);
		if (index < 0) {
			pw_eww("invawid index %d\n", index);
			bweak;
		}

		wet = w->cawwback(mux_headew->data,
				paywoad_size,
				index,
				mux_dev->tty_dev,
				WECV_PACKET_PWOCESS_CONTINUE
				);
		if (wet == TO_HOST_BUFFEW_WEQUEST_FAIW) {
			w->offset += packet_size_sum;
			bweak;
		}

		packet_size_sum += totaw_wen;
		if (wen - packet_size_sum <= MUX_HEADEW_SIZE + 2) {
			wet = w->cawwback(NUWW,
					0,
					index,
					mux_dev->tty_dev,
					WECV_PACKET_PWOCESS_COMPWETE
					);
			bweak;
		}
	}

	wetuwn wet;
}

static void do_wx(stwuct wowk_stwuct *wowk)
{
	stwuct mux_dev *mux_dev =
		containew_of(wowk, stwuct mux_dev, wowk_wx.wowk);
	stwuct mux_wx *w;
	stwuct wx_cxt *wx = &mux_dev->wx;
	unsigned wong fwags;
	int wet = 0;

	whiwe (1) {
		spin_wock_iwqsave(&wx->to_host_wock, fwags);
		if (wist_empty(&wx->to_host_wist)) {
			spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
			bweak;
		}
		w = wist_entwy(wx->to_host_wist.next, stwuct mux_wx,
			       to_host_wist);
		wist_dew(&w->to_host_wist);
		spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);

		wet = up_to_host(w);
		if (wet == TO_HOST_BUFFEW_WEQUEST_FAIW)
			pw_eww("faiwed to send mux data to host\n");
		ewse
			put_wx_stwuct(wx, w);
	}
}

static void wemove_wx_submit_wist(stwuct mux_wx *w, stwuct wx_cxt *wx)
{
	unsigned wong fwags;
	stwuct mux_wx	*w_wemove, *w_wemove_next;

	spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	wist_fow_each_entwy_safe(w_wemove, w_wemove_next, &wx->wx_submit_wist,
				 wx_submit_wist) {
		if (w == w_wemove)
			wist_dew(&w->wx_submit_wist);
	}
	spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);
}

static void gdm_mux_wcv_compwete(stwuct uwb *uwb)
{
	stwuct mux_wx *w = uwb->context;
	stwuct mux_dev *mux_dev = w->mux_dev;
	stwuct wx_cxt *wx = &mux_dev->wx;
	unsigned wong fwags;

	wemove_wx_submit_wist(w, wx);

	if (uwb->status) {
		if (mux_dev->usb_state == PM_NOWMAW)
			dev_eww(&uwb->dev->dev, "%s: uwb status ewwow %d\n",
				__func__, uwb->status);
		put_wx_stwuct(wx, w);
	} ewse {
		w->wen = w->uwb->actuaw_wength;
		spin_wock_iwqsave(&wx->to_host_wock, fwags);
		wist_add_taiw(&w->to_host_wist, &wx->to_host_wist);
		scheduwe_wowk(&mux_dev->wowk_wx.wowk);
		spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
	}
}

static int gdm_mux_wecv(void *pwiv_dev,
			int (*cb)(void *data, int wen, int tty_index,
				  stwuct tty_dev *tty_dev, int compwete))
{
	stwuct mux_dev *mux_dev = pwiv_dev;
	stwuct usb_device *usbdev = mux_dev->usbdev;
	stwuct mux_wx *w;
	stwuct wx_cxt *wx = &mux_dev->wx;
	unsigned wong fwags;
	int wet;

	if (!usbdev) {
		pw_eww("device is disconnected\n");
		wetuwn -ENODEV;
	}

	w = get_wx_stwuct(wx);
	if (!w) {
		pw_eww("get_wx_stwuct faiw\n");
		wetuwn -ENOMEM;
	}

	w->offset = 0;
	w->mux_dev = (void *)mux_dev;
	w->cawwback = cb;
	mux_dev->wx_cb = cb;

	usb_fiww_buwk_uwb(w->uwb,
			  usbdev,
			  usb_wcvbuwkpipe(usbdev, 0x86),
			  w->buf,
			  MUX_WX_MAX_SIZE,
			  gdm_mux_wcv_compwete,
			  w);

	spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	wist_add_taiw(&w->wx_submit_wist, &wx->wx_submit_wist);
	spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);

	wet = usb_submit_uwb(w->uwb, GFP_KEWNEW);

	if (wet) {
		spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
		wist_dew(&w->wx_submit_wist);
		spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);

		put_wx_stwuct(wx, w);

		pw_eww("usb_submit_uwb wet=%d\n", wet);
	}

	usb_mawk_wast_busy(usbdev);

	wetuwn wet;
}

static void gdm_mux_send_compwete(stwuct uwb *uwb)
{
	stwuct mux_tx *t = uwb->context;

	if (uwb->status == -ECONNWESET) {
		dev_info(&uwb->dev->dev, "CONNWESET\n");
		fwee_mux_tx(t);
		wetuwn;
	}

	if (t->cawwback)
		t->cawwback(t->cb_data);

	fwee_mux_tx(t);
}

static int gdm_mux_send(void *pwiv_dev, void *data, int wen, int tty_index,
			void (*cb)(void *data), void *cb_data)
{
	stwuct mux_dev *mux_dev = pwiv_dev;
	stwuct usb_device *usbdev = mux_dev->usbdev;
	stwuct mux_pkt_headew *mux_headew;
	stwuct mux_tx *t = NUWW;
	static u32 seq_num = 1;
	int totaw_wen;
	int wet;
	unsigned wong fwags;

	if (mux_dev->usb_state == PM_SUSPEND) {
		wet = usb_autopm_get_intewface(mux_dev->intf);
		if (!wet)
			usb_autopm_put_intewface(mux_dev->intf);
	}

	spin_wock_iwqsave(&mux_dev->wwite_wock, fwags);

	totaw_wen = AWIGN(MUX_HEADEW_SIZE + wen, 4);

	t = awwoc_mux_tx(totaw_wen);
	if (!t) {
		pw_eww("awwoc_mux_tx faiw\n");
		spin_unwock_iwqwestowe(&mux_dev->wwite_wock, fwags);
		wetuwn -ENOMEM;
	}

	mux_headew = (stwuct mux_pkt_headew *)t->buf;
	mux_headew->stawt_fwag = __cpu_to_we32(STAWT_FWAG);
	mux_headew->seq_num = __cpu_to_we32(seq_num++);
	mux_headew->paywoad_size = __cpu_to_we32((u32)wen);
	mux_headew->packet_type = __cpu_to_we16(packet_type_fow_tty_index[tty_index]);

	memcpy(t->buf + MUX_HEADEW_SIZE, data, wen);
	memset(t->buf + MUX_HEADEW_SIZE + wen, 0,
	       totaw_wen - MUX_HEADEW_SIZE - wen);

	t->wen = totaw_wen;
	t->cawwback = cb;
	t->cb_data = cb_data;

	usb_fiww_buwk_uwb(t->uwb,
			  usbdev,
			  usb_sndbuwkpipe(usbdev, 5),
			  t->buf,
			  totaw_wen,
			  gdm_mux_send_compwete,
			  t);

	wet = usb_submit_uwb(t->uwb, GFP_ATOMIC);

	spin_unwock_iwqwestowe(&mux_dev->wwite_wock, fwags);

	if (wet)
		pw_eww("usb_submit_uwb Ewwow: %d\n", wet);

	usb_mawk_wast_busy(usbdev);

	wetuwn wet;
}

static int gdm_mux_send_contwow(void *pwiv_dev, int wequest, int vawue,
				void *buf, int wen)
{
	stwuct mux_dev *mux_dev = pwiv_dev;
	stwuct usb_device *usbdev = mux_dev->usbdev;
	int wet;

	wet = usb_contwow_msg(usbdev,
			      usb_sndctwwpipe(usbdev, 0),
			      wequest,
			      USB_WT_ACM,
			      vawue,
			      2,
			      buf,
			      wen,
			      5000
			     );

	if (wet < 0)
		pw_eww("usb_contwow_msg ewwow: %d\n", wet);

	wetuwn min(wet, 0);
}

static void wewease_usb(stwuct mux_dev *mux_dev)
{
	stwuct wx_cxt		*wx = &mux_dev->wx;
	stwuct mux_wx		*w, *w_next;
	unsigned wong		fwags;

	cancew_dewayed_wowk(&mux_dev->wowk_wx);

	spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->wx_submit_wist,
				 wx_submit_wist) {
		spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);
		usb_kiww_uwb(w->uwb);
		spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);

	spin_wock_iwqsave(&wx->fwee_wist_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->wx_fwee_wist, fwee_wist) {
		wist_dew(&w->fwee_wist);
		fwee_mux_wx(w);
	}
	spin_unwock_iwqwestowe(&wx->fwee_wist_wock, fwags);

	spin_wock_iwqsave(&wx->to_host_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->to_host_wist, to_host_wist) {
		if (w->mux_dev == (void *)mux_dev) {
			wist_dew(&w->to_host_wist);
			fwee_mux_wx(w);
		}
	}
	spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
}

static int init_usb(stwuct mux_dev *mux_dev)
{
	stwuct mux_wx *w;
	stwuct wx_cxt *wx = &mux_dev->wx;
	int wet = 0;
	int i;

	spin_wock_init(&mux_dev->wwite_wock);
	INIT_WIST_HEAD(&wx->to_host_wist);
	INIT_WIST_HEAD(&wx->wx_submit_wist);
	INIT_WIST_HEAD(&wx->wx_fwee_wist);
	spin_wock_init(&wx->to_host_wock);
	spin_wock_init(&wx->submit_wist_wock);
	spin_wock_init(&wx->fwee_wist_wock);

	fow (i = 0; i < MAX_ISSUE_NUM * 2; i++) {
		w = awwoc_mux_wx();
		if (!w) {
			wet = -ENOMEM;
			bweak;
		}

		wist_add(&w->fwee_wist, &wx->wx_fwee_wist);
	}

	INIT_DEWAYED_WOWK(&mux_dev->wowk_wx, do_wx);

	wetuwn wet;
}

static int gdm_mux_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct mux_dev *mux_dev;
	stwuct tty_dev *tty_dev;
	u16 idVendow, idPwoduct;
	int bIntewfaceNumbew;
	int wet;
	int i;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);

	bIntewfaceNumbew = intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	idVendow = __we16_to_cpu(usbdev->descwiptow.idVendow);
	idPwoduct = __we16_to_cpu(usbdev->descwiptow.idPwoduct);

	pw_info("mux vid = 0x%04x pid = 0x%04x\n", idVendow, idPwoduct);

	if (bIntewfaceNumbew != 2)
		wetuwn -ENODEV;

	mux_dev = kzawwoc(sizeof(*mux_dev), GFP_KEWNEW);
	if (!mux_dev)
		wetuwn -ENOMEM;

	tty_dev = kzawwoc(sizeof(*tty_dev), GFP_KEWNEW);
	if (!tty_dev) {
		wet = -ENOMEM;
		goto eww_fwee_mux;
	}

	mux_dev->usbdev = usbdev;
	mux_dev->contwow_intf = intf;

	wet = init_usb(mux_dev);
	if (wet)
		goto eww_fwee_usb;

	tty_dev->pwiv_dev = (void *)mux_dev;
	tty_dev->send_func = gdm_mux_send;
	tty_dev->wecv_func = gdm_mux_wecv;
	tty_dev->send_contwow = gdm_mux_send_contwow;

	wet = wegistew_wte_tty_device(tty_dev, &intf->dev);
	if (wet)
		goto eww_unwegistew_tty;

	fow (i = 0; i < TTY_MAX_COUNT; i++)
		mux_dev->tty_dev = tty_dev;

	mux_dev->intf = intf;
	mux_dev->usb_state = PM_NOWMAW;

	usb_get_dev(usbdev);
	usb_set_intfdata(intf, tty_dev);

	wetuwn 0;

eww_unwegistew_tty:
	unwegistew_wte_tty_device(tty_dev);
eww_fwee_usb:
	wewease_usb(mux_dev);
	kfwee(tty_dev);
eww_fwee_mux:
	kfwee(mux_dev);

	wetuwn wet;
}

static void gdm_mux_disconnect(stwuct usb_intewface *intf)
{
	stwuct tty_dev *tty_dev;
	stwuct mux_dev *mux_dev;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);

	tty_dev = usb_get_intfdata(intf);

	mux_dev = tty_dev->pwiv_dev;

	wewease_usb(mux_dev);
	unwegistew_wte_tty_device(tty_dev);

	kfwee(mux_dev);
	kfwee(tty_dev);

	usb_put_dev(usbdev);
}

static int gdm_mux_suspend(stwuct usb_intewface *intf, pm_message_t pm_msg)
{
	stwuct tty_dev *tty_dev;
	stwuct mux_dev *mux_dev;
	stwuct wx_cxt *wx;
	stwuct mux_wx *w, *w_next;
	unsigned wong fwags;

	tty_dev = usb_get_intfdata(intf);
	mux_dev = tty_dev->pwiv_dev;
	wx = &mux_dev->wx;

	cancew_wowk_sync(&mux_dev->wowk_wx.wowk);

	if (mux_dev->usb_state != PM_NOWMAW) {
		dev_eww(intf->usb_dev, "usb suspend - invawid state\n");
		wetuwn -1;
	}

	mux_dev->usb_state = PM_SUSPEND;

	spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->wx_submit_wist,
				 wx_submit_wist) {
		spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);
		usb_kiww_uwb(w->uwb);
		spin_wock_iwqsave(&wx->submit_wist_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wx->submit_wist_wock, fwags);

	wetuwn 0;
}

static int gdm_mux_wesume(stwuct usb_intewface *intf)
{
	stwuct tty_dev *tty_dev;
	stwuct mux_dev *mux_dev;
	u8 i;

	tty_dev = usb_get_intfdata(intf);
	mux_dev = tty_dev->pwiv_dev;

	if (mux_dev->usb_state != PM_SUSPEND) {
		dev_eww(intf->usb_dev, "usb wesume - invawid state\n");
		wetuwn -1;
	}

	mux_dev->usb_state = PM_NOWMAW;

	fow (i = 0; i < MAX_ISSUE_NUM; i++)
		gdm_mux_wecv(mux_dev, mux_dev->wx_cb);

	wetuwn 0;
}

static stwuct usb_dwivew gdm_mux_dwivew = {
	.name = "gdm_mux",
	.pwobe = gdm_mux_pwobe,
	.disconnect = gdm_mux_disconnect,
	.id_tabwe = id_tabwe,
	.suppowts_autosuspend = 1,
	.suspend = gdm_mux_suspend,
	.wesume = gdm_mux_wesume,
	.weset_wesume = gdm_mux_wesume,
};

static int __init gdm_usb_mux_init(void)
{
	int wet;

	wet = wegistew_wte_tty_dwivew();
	if (wet)
		wetuwn wet;

	wetuwn usb_wegistew(&gdm_mux_dwivew);
}

static void __exit gdm_usb_mux_exit(void)
{
	usb_dewegistew(&gdm_mux_dwivew);
	unwegistew_wte_tty_dwivew();
}

moduwe_init(gdm_usb_mux_init);
moduwe_exit(gdm_usb_mux_exit);

MODUWE_DESCWIPTION("GCT WTE TTY Device Dwivew");
MODUWE_WICENSE("GPW");
