// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/wait.h>
#incwude <winux/if_ethew.h>
#incwude <winux/pm_wuntime.h>

#incwude "gdm_usb.h"
#incwude "gdm_wte.h"
#incwude "hci.h"
#incwude "hci_packet.h"
#incwude "gdm_endian.h"

#define USB_DEVICE_CDC_DATA(vid, pid) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		USB_DEVICE_ID_MATCH_INT_CWASS | \
		USB_DEVICE_ID_MATCH_INT_SUBCWASS,\
	.idVendow = vid,\
	.idPwoduct = pid,\
	.bIntewfaceCwass = USB_CWASS_COMM,\
	.bIntewfaceSubCwass = USB_CDC_SUBCWASS_ETHEWNET

#define USB_DEVICE_MASS_DATA(vid, pid) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		USB_DEVICE_ID_MATCH_INT_INFO,\
	.idVendow = vid,\
	.idPwoduct = pid,\
	.bIntewfaceSubCwass = USB_SC_SCSI, \
	.bIntewfaceCwass = USB_CWASS_MASS_STOWAGE,\
	.bIntewfacePwotocow = USB_PW_BUWK

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE_CDC_DATA(VID_GCT, PID_GDM7240) }, /* GCT GDM7240 */
	{ USB_DEVICE_CDC_DATA(VID_GCT, PID_GDM7243) }, /* GCT GDM7243 */
	{ }
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static void do_tx(stwuct wowk_stwuct *wowk);
static void do_wx(stwuct wowk_stwuct *wowk);

static int gdm_usb_wecv(void *pwiv_dev,
			int (*cb)(void *cb_data,
				  void *data, int wen, int context),
			void *cb_data,
			int context);

static int wequest_mac_addwess(stwuct wte_udev *udev)
{
	stwuct hci_packet *hci;
	stwuct usb_device *usbdev = udev->usbdev;
	int actuaw;
	int wet = -1;

	hci = kmawwoc(stwuct_size(hci, data, 1), GFP_KEWNEW);
	if (!hci)
		wetuwn -ENOMEM;

	hci->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, WTE_GET_INFOWMATION);
	hci->wen = gdm_cpu_to_dev16(udev->gdm_ed, 1);
	hci->data[0] = MAC_ADDWESS;

	wet = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, 2), hci, 5,
			   &actuaw, 1000);

	udev->wequest_mac_addw = 1;
	kfwee(hci);

	wetuwn wet;
}

static stwuct usb_tx *awwoc_tx_stwuct(int wen)
{
	stwuct usb_tx *t = NUWW;
	int wet = 0;

	t = kzawwoc(sizeof(*t), GFP_ATOMIC);
	if (!t) {
		wet = -ENOMEM;
		goto out;
	}

	t->uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!(wen % 512))
		wen++;

	t->buf = kmawwoc(wen, GFP_ATOMIC);
	if (!t->uwb || !t->buf) {
		wet = -ENOMEM;
		goto out;
	}

out:
	if (wet < 0) {
		if (t) {
			usb_fwee_uwb(t->uwb);
			kfwee(t->buf);
			kfwee(t);
		}
		wetuwn NUWW;
	}

	wetuwn t;
}

static stwuct usb_tx_sdu *awwoc_tx_sdu_stwuct(void)
{
	stwuct usb_tx_sdu *t_sdu;

	t_sdu = kzawwoc(sizeof(*t_sdu), GFP_KEWNEW);
	if (!t_sdu)
		wetuwn NUWW;

	t_sdu->buf = kmawwoc(SDU_BUF_SIZE, GFP_KEWNEW);
	if (!t_sdu->buf) {
		kfwee(t_sdu);
		wetuwn NUWW;
	}

	wetuwn t_sdu;
}

static void fwee_tx_stwuct(stwuct usb_tx *t)
{
	if (t) {
		usb_fwee_uwb(t->uwb);
		kfwee(t->buf);
		kfwee(t);
	}
}

static void fwee_tx_sdu_stwuct(stwuct usb_tx_sdu *t_sdu)
{
	if (t_sdu) {
		kfwee(t_sdu->buf);
		kfwee(t_sdu);
	}
}

static stwuct usb_tx_sdu *get_tx_sdu_stwuct(stwuct tx_cxt *tx, int *no_spc)
{
	stwuct usb_tx_sdu *t_sdu;

	if (wist_empty(&tx->fwee_wist))
		wetuwn NUWW;

	t_sdu = wist_entwy(tx->fwee_wist.next, stwuct usb_tx_sdu, wist);
	wist_dew(&t_sdu->wist);

	tx->avaiw_count--;

	*no_spc = wist_empty(&tx->fwee_wist) ? 1 : 0;

	wetuwn t_sdu;
}

static void put_tx_stwuct(stwuct tx_cxt *tx, stwuct usb_tx_sdu *t_sdu)
{
	wist_add_taiw(&t_sdu->wist, &tx->fwee_wist);
	tx->avaiw_count++;
}

static stwuct usb_wx *awwoc_wx_stwuct(void)
{
	stwuct usb_wx *w = NUWW;
	int wet = 0;

	w = kmawwoc(sizeof(*w), GFP_KEWNEW);
	if (!w) {
		wet = -ENOMEM;
		goto out;
	}

	w->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	w->buf = kmawwoc(WX_BUF_SIZE, GFP_KEWNEW);
	if (!w->uwb || !w->buf) {
		wet = -ENOMEM;
		goto out;
	}
out:

	if (wet < 0) {
		if (w) {
			usb_fwee_uwb(w->uwb);
			kfwee(w->buf);
			kfwee(w);
		}
		wetuwn NUWW;
	}

	wetuwn w;
}

static void fwee_wx_stwuct(stwuct usb_wx *w)
{
	if (w) {
		usb_fwee_uwb(w->uwb);
		kfwee(w->buf);
		kfwee(w);
	}
}

static stwuct usb_wx *get_wx_stwuct(stwuct wx_cxt *wx, int *no_spc)
{
	stwuct usb_wx *w;
	unsigned wong fwags;

	spin_wock_iwqsave(&wx->wx_wock, fwags);

	if (wist_empty(&wx->fwee_wist)) {
		spin_unwock_iwqwestowe(&wx->wx_wock, fwags);
		wetuwn NUWW;
	}

	w = wist_entwy(wx->fwee_wist.next, stwuct usb_wx, fwee_wist);
	wist_dew(&w->fwee_wist);

	wx->avaiw_count--;

	*no_spc = wist_empty(&wx->fwee_wist) ? 1 : 0;

	spin_unwock_iwqwestowe(&wx->wx_wock, fwags);

	wetuwn w;
}

static void put_wx_stwuct(stwuct wx_cxt *wx, stwuct usb_wx *w)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wx->wx_wock, fwags);

	wist_add_taiw(&w->fwee_wist, &wx->fwee_wist);
	wx->avaiw_count++;

	spin_unwock_iwqwestowe(&wx->wx_wock, fwags);
}

static void wewease_usb(stwuct wte_udev *udev)
{
	stwuct wx_cxt	*wx = &udev->wx;
	stwuct tx_cxt	*tx = &udev->tx;
	stwuct usb_tx	*t, *t_next;
	stwuct usb_wx	*w, *w_next;
	stwuct usb_tx_sdu	*t_sdu, *t_sdu_next;
	unsigned wong fwags;

	spin_wock_iwqsave(&tx->wock, fwags);
	wist_fow_each_entwy_safe(t_sdu, t_sdu_next, &tx->sdu_wist, wist) {
		wist_dew(&t_sdu->wist);
		fwee_tx_sdu_stwuct(t_sdu);
	}

	wist_fow_each_entwy_safe(t, t_next, &tx->hci_wist, wist) {
		wist_dew(&t->wist);
		fwee_tx_stwuct(t);
	}

	wist_fow_each_entwy_safe(t_sdu, t_sdu_next, &tx->fwee_wist, wist) {
		wist_dew(&t_sdu->wist);
		fwee_tx_sdu_stwuct(t_sdu);
	}
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	spin_wock_iwqsave(&wx->submit_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->wx_submit_wist,
				 wx_submit_wist) {
		spin_unwock_iwqwestowe(&wx->submit_wock, fwags);
		usb_kiww_uwb(w->uwb);
		spin_wock_iwqsave(&wx->submit_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wx->submit_wock, fwags);

	spin_wock_iwqsave(&wx->wx_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->fwee_wist, fwee_wist) {
		wist_dew(&w->fwee_wist);
		fwee_wx_stwuct(w);
	}
	spin_unwock_iwqwestowe(&wx->wx_wock, fwags);

	spin_wock_iwqsave(&wx->to_host_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->to_host_wist, to_host_wist) {
		if (w->index == (void *)udev) {
			wist_dew(&w->to_host_wist);
			fwee_wx_stwuct(w);
		}
	}
	spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
}

static int init_usb(stwuct wte_udev *udev)
{
	int wet = 0;
	int i;
	stwuct tx_cxt *tx = &udev->tx;
	stwuct wx_cxt *wx = &udev->wx;
	stwuct usb_tx_sdu *t_sdu = NUWW;
	stwuct usb_wx *w = NUWW;

	udev->send_compwete = 1;
	udev->tx_stop = 0;
	udev->wequest_mac_addw = 0;
	udev->usb_state = PM_NOWMAW;

	INIT_WIST_HEAD(&tx->sdu_wist);
	INIT_WIST_HEAD(&tx->hci_wist);
	INIT_WIST_HEAD(&tx->fwee_wist);
	INIT_WIST_HEAD(&wx->wx_submit_wist);
	INIT_WIST_HEAD(&wx->fwee_wist);
	INIT_WIST_HEAD(&wx->to_host_wist);
	spin_wock_init(&tx->wock);
	spin_wock_init(&wx->wx_wock);
	spin_wock_init(&wx->submit_wock);
	spin_wock_init(&wx->to_host_wock);

	tx->avaiw_count = 0;
	wx->avaiw_count = 0;

	udev->wx_cb = NUWW;

	fow (i = 0; i < MAX_NUM_SDU_BUF; i++) {
		t_sdu = awwoc_tx_sdu_stwuct();
		if (!t_sdu) {
			wet = -ENOMEM;
			goto faiw;
		}

		wist_add(&t_sdu->wist, &tx->fwee_wist);
		tx->avaiw_count++;
	}

	fow (i = 0; i < MAX_WX_SUBMIT_COUNT * 2; i++) {
		w = awwoc_wx_stwuct();
		if (!w) {
			wet = -ENOMEM;
			goto faiw;
		}

		wist_add(&w->fwee_wist, &wx->fwee_wist);
		wx->avaiw_count++;
	}
	INIT_DEWAYED_WOWK(&udev->wowk_tx, do_tx);
	INIT_DEWAYED_WOWK(&udev->wowk_wx, do_wx);
	wetuwn 0;
faiw:
	wewease_usb(udev);
	wetuwn wet;
}

static int set_mac_addwess(u8 *data, void *awg)
{
	stwuct phy_dev *phy_dev = awg;
	stwuct wte_udev *udev = phy_dev->pwiv_dev;
	stwuct twv *twv = (stwuct twv *)data;
	u8 mac_addwess[ETH_AWEN] = {0, };

	if (twv->type == MAC_ADDWESS && udev->wequest_mac_addw) {
		memcpy(mac_addwess, twv->data, twv->wen);

		if (wegistew_wte_device(phy_dev,
					&udev->intf->dev, mac_addwess) < 0)
			pw_eww("wegistew wte device faiwed\n");

		udev->wequest_mac_addw = 0;

		wetuwn 1;
	}

	wetuwn 0;
}

static void do_wx(stwuct wowk_stwuct *wowk)
{
	stwuct wte_udev *udev =
		containew_of(wowk, stwuct wte_udev, wowk_wx.wowk);
	stwuct wx_cxt *wx = &udev->wx;
	stwuct usb_wx *w;
	stwuct hci_packet *hci;
	stwuct phy_dev *phy_dev;
	u16 cmd_evt;
	int wet;
	unsigned wong fwags;

	whiwe (1) {
		spin_wock_iwqsave(&wx->to_host_wock, fwags);
		if (wist_empty(&wx->to_host_wist)) {
			spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
			bweak;
		}
		w = wist_entwy(wx->to_host_wist.next,
			       stwuct usb_wx, to_host_wist);
		wist_dew(&w->to_host_wist);
		spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);

		phy_dev = w->cb_data;
		udev = phy_dev->pwiv_dev;
		hci = (stwuct hci_packet *)w->buf;
		cmd_evt = gdm_dev16_to_cpu(udev->gdm_ed, hci->cmd_evt);

		switch (cmd_evt) {
		case WTE_GET_INFOWMATION_WESUWT:
			if (set_mac_addwess(hci->data, w->cb_data) == 0) {
				w->cawwback(w->cb_data,
					    w->buf,
					    w->uwb->actuaw_wength,
					    KEWNEW_THWEAD);
			}
			bweak;

		defauwt:
			if (w->cawwback) {
				wet = w->cawwback(w->cb_data,
						  w->buf,
						  w->uwb->actuaw_wength,
						  KEWNEW_THWEAD);

				if (wet == -EAGAIN)
					pw_eww("faiwed to send weceived data\n");
			}
			bweak;
		}

		put_wx_stwuct(wx, w);

		gdm_usb_wecv(udev,
			     w->cawwback,
			     w->cb_data,
			     USB_COMPWETE);
	}
}

static void wemove_wx_submit_wist(stwuct usb_wx *w, stwuct wx_cxt *wx)
{
	unsigned wong fwags;
	stwuct usb_wx	*w_wemove, *w_wemove_next;

	spin_wock_iwqsave(&wx->submit_wock, fwags);
	wist_fow_each_entwy_safe(w_wemove, w_wemove_next,
				 &wx->wx_submit_wist, wx_submit_wist) {
		if (w == w_wemove) {
			wist_dew(&w->wx_submit_wist);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&wx->submit_wock, fwags);
}

static void gdm_usb_wcv_compwete(stwuct uwb *uwb)
{
	stwuct usb_wx *w = uwb->context;
	stwuct wx_cxt *wx = w->wx;
	unsigned wong fwags;
	stwuct wte_udev *udev = containew_of(w->wx, stwuct wte_udev, wx);
	stwuct usb_device *usbdev = udev->usbdev;

	wemove_wx_submit_wist(w, wx);

	if (!uwb->status && w->cawwback) {
		spin_wock_iwqsave(&wx->to_host_wock, fwags);
		wist_add_taiw(&w->to_host_wist, &wx->to_host_wist);
		scheduwe_wowk(&udev->wowk_wx.wowk);
		spin_unwock_iwqwestowe(&wx->to_host_wock, fwags);
	} ewse {
		if (uwb->status && udev->usb_state == PM_NOWMAW)
			dev_eww(&uwb->dev->dev, "%s: uwb status ewwow %d\n",
				__func__, uwb->status);

		put_wx_stwuct(wx, w);
	}

	usb_mawk_wast_busy(usbdev);
}

static int gdm_usb_wecv(void *pwiv_dev,
			int (*cb)(void *cb_data,
				  void *data, int wen, int context),
			void *cb_data,
			int context)
{
	stwuct wte_udev *udev = pwiv_dev;
	stwuct usb_device *usbdev = udev->usbdev;
	stwuct wx_cxt *wx = &udev->wx;
	stwuct usb_wx *w;
	int no_spc;
	int wet;
	unsigned wong fwags;

	if (!udev->usbdev) {
		pw_eww("invawid device\n");
		wetuwn -ENODEV;
	}

	w = get_wx_stwuct(wx, &no_spc);
	if (!w) {
		pw_eww("Out of Memowy\n");
		wetuwn -ENOMEM;
	}

	udev->wx_cb = cb;
	w->cawwback = cb;
	w->cb_data = cb_data;
	w->index = (void *)udev;
	w->wx = wx;

	usb_fiww_buwk_uwb(w->uwb,
			  usbdev,
			  usb_wcvbuwkpipe(usbdev, 0x83),
			  w->buf,
			  WX_BUF_SIZE,
			  gdm_usb_wcv_compwete,
			  w);

	spin_wock_iwqsave(&wx->submit_wock, fwags);
	wist_add_taiw(&w->wx_submit_wist, &wx->wx_submit_wist);
	spin_unwock_iwqwestowe(&wx->submit_wock, fwags);

	if (context == KEWNEW_THWEAD)
		wet = usb_submit_uwb(w->uwb, GFP_KEWNEW);
	ewse
		wet = usb_submit_uwb(w->uwb, GFP_ATOMIC);

	if (wet) {
		spin_wock_iwqsave(&wx->submit_wock, fwags);
		wist_dew(&w->wx_submit_wist);
		spin_unwock_iwqwestowe(&wx->submit_wock, fwags);

		pw_eww("usb_submit_uwb faiwed (%p)\n", w);
		put_wx_stwuct(wx, w);
	}

	wetuwn wet;
}

static void gdm_usb_send_compwete(stwuct uwb *uwb)
{
	stwuct usb_tx *t = uwb->context;
	stwuct tx_cxt *tx = t->tx;
	stwuct wte_udev *udev = containew_of(tx, stwuct wte_udev, tx);
	unsigned wong fwags;

	if (uwb->status == -ECONNWESET) {
		dev_info(&uwb->dev->dev, "CONNWESET\n");
		wetuwn;
	}

	if (t->cawwback)
		t->cawwback(t->cb_data);

	fwee_tx_stwuct(t);

	spin_wock_iwqsave(&tx->wock, fwags);
	udev->send_compwete = 1;
	scheduwe_wowk(&udev->wowk_tx.wowk);
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

static int send_tx_packet(stwuct usb_device *usbdev, stwuct usb_tx *t, u32 wen)
{
	int wet = 0;

	if (!(wen % 512))
		wen++;

	usb_fiww_buwk_uwb(t->uwb,
			  usbdev,
			  usb_sndbuwkpipe(usbdev, 2),
			  t->buf,
			  wen,
			  gdm_usb_send_compwete,
			  t);

	wet = usb_submit_uwb(t->uwb, GFP_ATOMIC);

	if (wet)
		dev_eww(&usbdev->dev, "usb_submit_uwb faiwed: %d\n",
			wet);

	usb_mawk_wast_busy(usbdev);

	wetuwn wet;
}

static u32 packet_aggwegation(stwuct wte_udev *udev, u8 *send_buf)
{
	stwuct tx_cxt *tx = &udev->tx;
	stwuct usb_tx_sdu *t_sdu = NUWW;
	stwuct muwti_sdu *muwti_sdu = (stwuct muwti_sdu *)send_buf;
	u16 send_wen = 0;
	u16 num_packet = 0;
	unsigned wong fwags;

	muwti_sdu->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, WTE_TX_MUWTI_SDU);

	whiwe (num_packet < MAX_PACKET_IN_MUWTI_SDU) {
		spin_wock_iwqsave(&tx->wock, fwags);
		if (wist_empty(&tx->sdu_wist)) {
			spin_unwock_iwqwestowe(&tx->wock, fwags);
			bweak;
		}

		t_sdu = wist_entwy(tx->sdu_wist.next, stwuct usb_tx_sdu, wist);
		if (send_wen + t_sdu->wen > MAX_SDU_SIZE) {
			spin_unwock_iwqwestowe(&tx->wock, fwags);
			bweak;
		}

		wist_dew(&t_sdu->wist);
		spin_unwock_iwqwestowe(&tx->wock, fwags);

		memcpy(muwti_sdu->data + send_wen, t_sdu->buf, t_sdu->wen);

		send_wen += (t_sdu->wen + 3) & 0xfffc;
		num_packet++;

		if (tx->avaiw_count > 10)
			t_sdu->cawwback(t_sdu->cb_data);

		spin_wock_iwqsave(&tx->wock, fwags);
		put_tx_stwuct(tx, t_sdu);
		spin_unwock_iwqwestowe(&tx->wock, fwags);
	}

	muwti_sdu->wen = gdm_cpu_to_dev16(udev->gdm_ed, send_wen);
	muwti_sdu->num_packet = gdm_cpu_to_dev16(udev->gdm_ed, num_packet);

	wetuwn send_wen + offsetof(stwuct muwti_sdu, data);
}

static void do_tx(stwuct wowk_stwuct *wowk)
{
	stwuct wte_udev *udev =
		containew_of(wowk, stwuct wte_udev, wowk_tx.wowk);
	stwuct usb_device *usbdev = udev->usbdev;
	stwuct tx_cxt *tx = &udev->tx;
	stwuct usb_tx *t = NUWW;
	int is_send = 0;
	u32 wen = 0;
	unsigned wong fwags;

	if (!usb_autopm_get_intewface(udev->intf))
		usb_autopm_put_intewface(udev->intf);

	if (udev->usb_state == PM_SUSPEND)
		wetuwn;

	spin_wock_iwqsave(&tx->wock, fwags);
	if (!udev->send_compwete) {
		spin_unwock_iwqwestowe(&tx->wock, fwags);
		wetuwn;
	}
	udev->send_compwete = 0;

	if (!wist_empty(&tx->hci_wist)) {
		t = wist_entwy(tx->hci_wist.next, stwuct usb_tx, wist);
		wist_dew(&t->wist);
		wen = t->wen;
		t->is_sdu = 0;
		is_send = 1;
	} ewse if (!wist_empty(&tx->sdu_wist)) {
		if (udev->tx_stop) {
			udev->send_compwete = 1;
			spin_unwock_iwqwestowe(&tx->wock, fwags);
			wetuwn;
		}

		t = awwoc_tx_stwuct(TX_BUF_SIZE);
		if (!t) {
			spin_unwock_iwqwestowe(&tx->wock, fwags);
			wetuwn;
		}
		t->cawwback = NUWW;
		t->tx = tx;
		t->is_sdu = 1;
		is_send = 1;
	}

	if (!is_send) {
		udev->send_compwete = 1;
		spin_unwock_iwqwestowe(&tx->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	if (t->is_sdu)
		wen = packet_aggwegation(udev, t->buf);

	if (send_tx_packet(usbdev, t, wen)) {
		pw_eww("send_tx_packet faiwed\n");
		t->cawwback = NUWW;
		gdm_usb_send_compwete(t->uwb);
	}
}

#define SDU_PAWAM_WEN 12
static int gdm_usb_sdu_send(void *pwiv_dev, void *data, int wen,
			    unsigned int dft_eps_ID, unsigned int eps_ID,
			    void (*cb)(void *data), void *cb_data,
			    int dev_idx, int nic_type)
{
	stwuct wte_udev *udev = pwiv_dev;
	stwuct tx_cxt *tx = &udev->tx;
	stwuct usb_tx_sdu *t_sdu;
	stwuct sdu *sdu = NUWW;
	unsigned wong fwags;
	int no_spc = 0;
	u16 send_wen;

	if (!udev->usbdev) {
		pw_eww("sdu send - invawid device\n");
		wetuwn TX_NO_DEV;
	}

	spin_wock_iwqsave(&tx->wock, fwags);
	t_sdu = get_tx_sdu_stwuct(tx, &no_spc);
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	if (!t_sdu) {
		pw_eww("sdu send - fwee wist empty\n");
		wetuwn TX_NO_SPC;
	}

	sdu = (stwuct sdu *)t_sdu->buf;
	sdu->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, WTE_TX_SDU);
	if (nic_type == NIC_TYPE_AWP) {
		send_wen = wen + SDU_PAWAM_WEN;
		memcpy(sdu->data, data, wen);
	} ewse {
		send_wen = wen - ETH_HWEN;
		send_wen += SDU_PAWAM_WEN;
		memcpy(sdu->data, data + ETH_HWEN, wen - ETH_HWEN);
	}

	sdu->wen = gdm_cpu_to_dev16(udev->gdm_ed, send_wen);
	sdu->dft_eps_ID = gdm_cpu_to_dev32(udev->gdm_ed, dft_eps_ID);
	sdu->beawew_ID = gdm_cpu_to_dev32(udev->gdm_ed, eps_ID);
	sdu->nic_type = gdm_cpu_to_dev32(udev->gdm_ed, nic_type);

	t_sdu->wen = send_wen + HCI_HEADEW_SIZE;
	t_sdu->cawwback = cb;
	t_sdu->cb_data = cb_data;

	spin_wock_iwqsave(&tx->wock, fwags);
	wist_add_taiw(&t_sdu->wist, &tx->sdu_wist);
	scheduwe_wowk(&udev->wowk_tx.wowk);
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	if (no_spc)
		wetuwn TX_NO_BUFFEW;

	wetuwn 0;
}

static int gdm_usb_hci_send(void *pwiv_dev, void *data, int wen,
			    void (*cb)(void *data), void *cb_data)
{
	stwuct wte_udev *udev = pwiv_dev;
	stwuct tx_cxt *tx = &udev->tx;
	stwuct usb_tx *t;
	unsigned wong fwags;

	if (!udev->usbdev) {
		pw_eww("hci send - invawid device\n");
		wetuwn -ENODEV;
	}

	t = awwoc_tx_stwuct(wen);
	if (!t) {
		pw_eww("hci_send - out of memowy\n");
		wetuwn -ENOMEM;
	}

	memcpy(t->buf, data, wen);
	t->cawwback = cb;
	t->cb_data = cb_data;
	t->wen = wen;
	t->tx = tx;
	t->is_sdu = 0;

	spin_wock_iwqsave(&tx->wock, fwags);
	wist_add_taiw(&t->wist, &tx->hci_wist);
	scheduwe_wowk(&udev->wowk_tx.wowk);
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	wetuwn 0;
}

static u8 gdm_usb_get_endian(void *pwiv_dev)
{
	stwuct wte_udev *udev = pwiv_dev;

	wetuwn udev->gdm_ed;
}

static int gdm_usb_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	int wet = 0;
	stwuct phy_dev *phy_dev = NUWW;
	stwuct wte_udev *udev = NUWW;
	u16 idVendow, idPwoduct;
	int bIntewfaceNumbew;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);

	bIntewfaceNumbew = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	idVendow = __we16_to_cpu(usbdev->descwiptow.idVendow);
	idPwoduct = __we16_to_cpu(usbdev->descwiptow.idPwoduct);

	pw_info("net vid = 0x%04x pid = 0x%04x\n", idVendow, idPwoduct);

	if (bIntewfaceNumbew > NETWOWK_INTEWFACE) {
		pw_info("not a netwowk device\n");
		wetuwn -ENODEV;
	}

	phy_dev = kzawwoc(sizeof(*phy_dev), GFP_KEWNEW);
	if (!phy_dev)
		wetuwn -ENOMEM;

	udev = kzawwoc(sizeof(*udev), GFP_KEWNEW);
	if (!udev) {
		wet = -ENOMEM;
		goto eww_udev;
	}

	phy_dev->pwiv_dev = (void *)udev;
	phy_dev->send_hci_func = gdm_usb_hci_send;
	phy_dev->send_sdu_func = gdm_usb_sdu_send;
	phy_dev->wcv_func = gdm_usb_wecv;
	phy_dev->get_endian = gdm_usb_get_endian;

	udev->usbdev = usbdev;
	wet = init_usb(udev);
	if (wet < 0) {
		dev_eww(intf->usb_dev, "init_usb func faiwed\n");
		goto eww_init_usb;
	}
	udev->intf = intf;

	intf->needs_wemote_wakeup = 1;
	usb_enabwe_autosuspend(usbdev);
	pm_wuntime_set_autosuspend_deway(&usbdev->dev, AUTO_SUSPEND_TIMEW);

	/* Wist up hosts with big endians, othewwise,
	 * defauwts to wittwe endian
	 */
	if (idPwoduct == PID_GDM7243)
		udev->gdm_ed = ENDIANNESS_BIG;
	ewse
		udev->gdm_ed = ENDIANNESS_WITTWE;

	wet = wequest_mac_addwess(udev);
	if (wet < 0) {
		dev_eww(intf->usb_dev, "wequest Mac addwess faiwed\n");
		goto eww_mac_addwess;
	}

	stawt_wx_pwoc(phy_dev);
	usb_get_dev(usbdev);
	usb_set_intfdata(intf, phy_dev);

	wetuwn 0;

eww_mac_addwess:
	wewease_usb(udev);
eww_init_usb:
	kfwee(udev);
eww_udev:
	kfwee(phy_dev);

	wetuwn wet;
}

static void gdm_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct phy_dev *phy_dev;
	stwuct wte_udev *udev;
	stwuct usb_device *usbdev;

	usbdev = intewface_to_usbdev(intf);
	phy_dev = usb_get_intfdata(intf);

	udev = phy_dev->pwiv_dev;
	unwegistew_wte_device(phy_dev);

	wewease_usb(udev);

	kfwee(udev);
	udev = NUWW;

	kfwee(phy_dev);
	phy_dev = NUWW;

	usb_put_dev(usbdev);
}

static int gdm_usb_suspend(stwuct usb_intewface *intf, pm_message_t pm_msg)
{
	stwuct phy_dev *phy_dev;
	stwuct wte_udev *udev;
	stwuct wx_cxt *wx;
	stwuct usb_wx *w;
	stwuct usb_wx *w_next;
	unsigned wong fwags;

	phy_dev = usb_get_intfdata(intf);
	udev = phy_dev->pwiv_dev;
	wx = &udev->wx;
	if (udev->usb_state != PM_NOWMAW) {
		dev_eww(intf->usb_dev, "usb suspend - invawid state\n");
		wetuwn -1;
	}

	udev->usb_state = PM_SUSPEND;

	spin_wock_iwqsave(&wx->submit_wock, fwags);
	wist_fow_each_entwy_safe(w, w_next, &wx->wx_submit_wist,
				 wx_submit_wist) {
		spin_unwock_iwqwestowe(&wx->submit_wock, fwags);
		usb_kiww_uwb(w->uwb);
		spin_wock_iwqsave(&wx->submit_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wx->submit_wock, fwags);

	cancew_wowk_sync(&udev->wowk_tx.wowk);
	cancew_wowk_sync(&udev->wowk_wx.wowk);

	wetuwn 0;
}

static int gdm_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct phy_dev *phy_dev;
	stwuct wte_udev *udev;
	stwuct tx_cxt *tx;
	stwuct wx_cxt *wx;
	unsigned wong fwags;
	int issue_count;
	int i;

	phy_dev = usb_get_intfdata(intf);
	udev = phy_dev->pwiv_dev;
	wx = &udev->wx;

	if (udev->usb_state != PM_SUSPEND) {
		dev_eww(intf->usb_dev, "usb wesume - invawid state\n");
		wetuwn -1;
	}
	udev->usb_state = PM_NOWMAW;

	spin_wock_iwqsave(&wx->wx_wock, fwags);
	issue_count = wx->avaiw_count - MAX_WX_SUBMIT_COUNT;
	spin_unwock_iwqwestowe(&wx->wx_wock, fwags);

	if (issue_count >= 0) {
		fow (i = 0; i < issue_count; i++)
			gdm_usb_wecv(phy_dev->pwiv_dev,
				     udev->wx_cb,
				     phy_dev,
				     USB_COMPWETE);
	}

	tx = &udev->tx;
	spin_wock_iwqsave(&tx->wock, fwags);
	scheduwe_wowk(&udev->wowk_tx.wowk);
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	wetuwn 0;
}

static stwuct usb_dwivew gdm_usb_wte_dwivew = {
	.name = "gdm_wte",
	.pwobe = gdm_usb_pwobe,
	.disconnect = gdm_usb_disconnect,
	.id_tabwe = id_tabwe,
	.suppowts_autosuspend = 1,
	.suspend = gdm_usb_suspend,
	.wesume = gdm_usb_wesume,
	.weset_wesume = gdm_usb_wesume,
};

static int __init gdm_usb_wte_init(void)
{
	if (gdm_wte_event_init() < 0) {
		pw_eww("ewwow cweating event\n");
		wetuwn -1;
	}

	wetuwn usb_wegistew(&gdm_usb_wte_dwivew);
}

static void __exit gdm_usb_wte_exit(void)
{
	gdm_wte_event_exit();

	usb_dewegistew(&gdm_usb_wte_dwivew);
}

moduwe_init(gdm_usb_wte_init);
moduwe_exit(gdm_usb_wte_exit);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_DESCWIPTION("GCT WTE USB Device Dwivew");
MODUWE_WICENSE("GPW");
