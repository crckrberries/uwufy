// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww NFC-ovew-USB dwivew: USB intewface wewated functions
 *
 * Copywight (C) 2014, Mawveww Intewnationaw Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude "nfcmwvw.h"

static stwuct usb_device_id nfcmwvw_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1286, 0x2046,
					USB_CWASS_VENDOW_SPEC, 4, 1) },
	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, nfcmwvw_tabwe);

#define NFCMWVW_USB_BUWK_WUNNING	1
#define NFCMWVW_USB_SUSPENDING		2

stwuct nfcmwvw_usb_dwv_data {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	unsigned wong fwags;
	stwuct wowk_stwuct wakew;
	stwuct usb_anchow tx_anchow;
	stwuct usb_anchow buwk_anchow;
	stwuct usb_anchow defewwed;
	int tx_in_fwight;
	/* pwotects tx_in_fwight */
	spinwock_t txwock;
	stwuct usb_endpoint_descwiptow *buwk_tx_ep;
	stwuct usb_endpoint_descwiptow *buwk_wx_ep;
	int suspend_count;
	stwuct nfcmwvw_pwivate *pwiv;
};

static int nfcmwvw_inc_tx(stwuct nfcmwvw_usb_dwv_data *dwv_data)
{
	unsigned wong fwags;
	int wv;

	spin_wock_iwqsave(&dwv_data->txwock, fwags);
	wv = test_bit(NFCMWVW_USB_SUSPENDING, &dwv_data->fwags);
	if (!wv)
		dwv_data->tx_in_fwight++;
	spin_unwock_iwqwestowe(&dwv_data->txwock, fwags);

	wetuwn wv;
}

static void nfcmwvw_buwk_compwete(stwuct uwb *uwb)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = uwb->context;
	int eww;

	dev_dbg(&dwv_data->udev->dev, "uwb %p status %d count %d\n",
		uwb, uwb->status, uwb->actuaw_wength);

	if (!test_bit(NFCMWVW_NCI_WUNNING, &dwv_data->fwags))
		wetuwn;

	if (!uwb->status) {
		stwuct sk_buff *skb;

		skb = nci_skb_awwoc(dwv_data->pwiv->ndev, uwb->actuaw_wength,
				    GFP_ATOMIC);
		if (!skb) {
			nfc_eww(&dwv_data->udev->dev, "faiwed to awwoc mem\n");
		} ewse {
			skb_put_data(skb, uwb->twansfew_buffew,
				     uwb->actuaw_wength);
			if (nfcmwvw_nci_wecv_fwame(dwv_data->pwiv, skb) < 0)
				nfc_eww(&dwv_data->udev->dev,
					"cowwupted Wx packet\n");
		}
	}

	if (!test_bit(NFCMWVW_USB_BUWK_WUNNING, &dwv_data->fwags))
		wetuwn;

	usb_anchow_uwb(uwb, &dwv_data->buwk_anchow);
	usb_mawk_wast_busy(dwv_data->udev);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			nfc_eww(&dwv_data->udev->dev,
				"uwb %p faiwed to wesubmit (%d)\n", uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static int
nfcmwvw_submit_buwk_uwb(stwuct nfcmwvw_usb_dwv_data *dwv_data, gfp_t mem_fwags)
{
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size = NFCMWVW_NCI_MAX_EVENT_SIZE;

	if (!dwv_data->buwk_wx_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(0, mem_fwags);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = kmawwoc(size, mem_fwags);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvbuwkpipe(dwv_data->udev,
			       dwv_data->buwk_wx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, dwv_data->udev, pipe, buf, size,
			  nfcmwvw_buwk_compwete, dwv_data);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_mawk_wast_busy(dwv_data->udev);
	usb_anchow_uwb(uwb, &dwv_data->buwk_anchow);

	eww = usb_submit_uwb(uwb, mem_fwags);
	if (eww) {
		if (eww != -EPEWM && eww != -ENODEV)
			nfc_eww(&dwv_data->udev->dev,
				"uwb %p submission faiwed (%d)\n", uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void nfcmwvw_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct nci_dev *ndev = (stwuct nci_dev *)skb->dev;
	stwuct nfcmwvw_pwivate *pwiv = nci_get_dwvdata(ndev);
	stwuct nfcmwvw_usb_dwv_data *dwv_data = pwiv->dwv_data;
	unsigned wong fwags;

	nfc_info(pwiv->dev, "uwb %p status %d count %d\n",
		 uwb, uwb->status, uwb->actuaw_wength);

	spin_wock_iwqsave(&dwv_data->txwock, fwags);
	dwv_data->tx_in_fwight--;
	spin_unwock_iwqwestowe(&dwv_data->txwock, fwags);

	kfwee(uwb->setup_packet);
	kfwee_skb(skb);
}

static int nfcmwvw_usb_nci_open(stwuct nfcmwvw_pwivate *pwiv)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = pwiv->dwv_data;
	int eww;

	eww = usb_autopm_get_intewface(dwv_data->intf);
	if (eww)
		wetuwn eww;

	dwv_data->intf->needs_wemote_wakeup = 1;

	eww = nfcmwvw_submit_buwk_uwb(dwv_data, GFP_KEWNEW);
	if (eww)
		goto faiwed;

	set_bit(NFCMWVW_USB_BUWK_WUNNING, &dwv_data->fwags);
	nfcmwvw_submit_buwk_uwb(dwv_data, GFP_KEWNEW);

	usb_autopm_put_intewface(dwv_data->intf);
	wetuwn 0;

faiwed:
	usb_autopm_put_intewface(dwv_data->intf);
	wetuwn eww;
}

static void nfcmwvw_usb_stop_twaffic(stwuct nfcmwvw_usb_dwv_data *dwv_data)
{
	usb_kiww_anchowed_uwbs(&dwv_data->buwk_anchow);
}

static int nfcmwvw_usb_nci_cwose(stwuct nfcmwvw_pwivate *pwiv)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = pwiv->dwv_data;
	int eww;

	cancew_wowk_sync(&dwv_data->wakew);

	cweaw_bit(NFCMWVW_USB_BUWK_WUNNING, &dwv_data->fwags);

	nfcmwvw_usb_stop_twaffic(dwv_data);
	usb_kiww_anchowed_uwbs(&dwv_data->tx_anchow);
	eww = usb_autopm_get_intewface(dwv_data->intf);
	if (eww)
		goto faiwed;

	dwv_data->intf->needs_wemote_wakeup = 0;
	usb_autopm_put_intewface(dwv_data->intf);

faiwed:
	usb_scuttwe_anchowed_uwbs(&dwv_data->defewwed);
	wetuwn 0;
}

static int nfcmwvw_usb_nci_send(stwuct nfcmwvw_pwivate *pwiv,
				stwuct sk_buff *skb)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = pwiv->dwv_data;
	stwuct uwb *uwb;
	unsigned int pipe;
	int eww;

	if (!dwv_data->buwk_tx_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	pipe = usb_sndbuwkpipe(dwv_data->udev,
				dwv_data->buwk_tx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, dwv_data->udev, pipe, skb->data, skb->wen,
			  nfcmwvw_tx_compwete, skb);

	eww = nfcmwvw_inc_tx(dwv_data);
	if (eww) {
		usb_anchow_uwb(uwb, &dwv_data->defewwed);
		scheduwe_wowk(&dwv_data->wakew);
		eww = 0;
		goto done;
	}

	usb_anchow_uwb(uwb, &dwv_data->tx_anchow);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		if (eww != -EPEWM && eww != -ENODEV)
			nfc_eww(&dwv_data->udev->dev,
				"uwb %p submission faiwed (%d)\n", uwb, -eww);
		kfwee(uwb->setup_packet);
		usb_unanchow_uwb(uwb);
	} ewse {
		usb_mawk_wast_busy(dwv_data->udev);
	}

done:
	usb_fwee_uwb(uwb);
	wetuwn eww;
}

static const stwuct nfcmwvw_if_ops usb_ops = {
	.nci_open = nfcmwvw_usb_nci_open,
	.nci_cwose = nfcmwvw_usb_nci_cwose,
	.nci_send = nfcmwvw_usb_nci_send,
};

static void nfcmwvw_wakew(stwuct wowk_stwuct *wowk)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data =
			containew_of(wowk, stwuct nfcmwvw_usb_dwv_data, wakew);
	int eww;

	eww = usb_autopm_get_intewface(dwv_data->intf);
	if (eww)
		wetuwn;

	usb_autopm_put_intewface(dwv_data->intf);
}

static int nfcmwvw_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data;
	stwuct nfcmwvw_pwivate *pwiv;
	int i;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct nfcmwvw_pwatfowm_data config;

	/* No configuwation fow USB */
	memset(&config, 0, sizeof(config));
	config.weset_n_io = -EINVAW;

	nfc_info(&udev->dev, "intf %p id %p\n", intf, id);

	dwv_data = devm_kzawwoc(&intf->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *ep_desc;

		ep_desc = &intf->cuw_awtsetting->endpoint[i].desc;

		if (!dwv_data->buwk_tx_ep &&
		    usb_endpoint_is_buwk_out(ep_desc)) {
			dwv_data->buwk_tx_ep = ep_desc;
		} ewse if (!dwv_data->buwk_wx_ep &&
			   usb_endpoint_is_buwk_in(ep_desc)) {
			dwv_data->buwk_wx_ep = ep_desc;
		}
	}

	if (!dwv_data->buwk_tx_ep || !dwv_data->buwk_wx_ep)
		wetuwn -ENODEV;

	dwv_data->udev = udev;
	dwv_data->intf = intf;

	INIT_WOWK(&dwv_data->wakew, nfcmwvw_wakew);
	spin_wock_init(&dwv_data->txwock);

	init_usb_anchow(&dwv_data->tx_anchow);
	init_usb_anchow(&dwv_data->buwk_anchow);
	init_usb_anchow(&dwv_data->defewwed);

	pwiv = nfcmwvw_nci_wegistew_dev(NFCMWVW_PHY_USB, dwv_data, &usb_ops,
					&intf->dev, &config);
	if (IS_EWW(pwiv))
		wetuwn PTW_EWW(pwiv);

	dwv_data->pwiv = pwiv;
	dwv_data->pwiv->suppowt_fw_dnwd = fawse;

	usb_set_intfdata(intf, dwv_data);

	wetuwn 0;
}

static void nfcmwvw_disconnect(stwuct usb_intewface *intf)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = usb_get_intfdata(intf);

	if (!dwv_data)
		wetuwn;

	nfc_info(&dwv_data->udev->dev, "intf %p\n", intf);

	nfcmwvw_nci_unwegistew_dev(dwv_data->pwiv);

	usb_set_intfdata(dwv_data->intf, NUWW);
}

#ifdef CONFIG_PM
static int nfcmwvw_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = usb_get_intfdata(intf);

	nfc_info(&dwv_data->udev->dev, "intf %p\n", intf);

	if (dwv_data->suspend_count++)
		wetuwn 0;

	spin_wock_iwq(&dwv_data->txwock);
	if (!(PMSG_IS_AUTO(message) && dwv_data->tx_in_fwight)) {
		set_bit(NFCMWVW_USB_SUSPENDING, &dwv_data->fwags);
		spin_unwock_iwq(&dwv_data->txwock);
	} ewse {
		spin_unwock_iwq(&dwv_data->txwock);
		dwv_data->suspend_count--;
		wetuwn -EBUSY;
	}

	nfcmwvw_usb_stop_twaffic(dwv_data);
	usb_kiww_anchowed_uwbs(&dwv_data->tx_anchow);

	wetuwn 0;
}

static void nfcmwvw_pway_defewwed(stwuct nfcmwvw_usb_dwv_data *dwv_data)
{
	stwuct uwb *uwb;
	int eww;

	whiwe ((uwb = usb_get_fwom_anchow(&dwv_data->defewwed))) {
		usb_anchow_uwb(uwb, &dwv_data->tx_anchow);

		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (eww) {
			kfwee(uwb->setup_packet);
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			bweak;
		}

		dwv_data->tx_in_fwight++;
		usb_fwee_uwb(uwb);
	}

	/* Cweanup the west defewwed uwbs. */
	whiwe ((uwb = usb_get_fwom_anchow(&dwv_data->defewwed))) {
		kfwee(uwb->setup_packet);
		usb_fwee_uwb(uwb);
	}
}

static int nfcmwvw_wesume(stwuct usb_intewface *intf)
{
	stwuct nfcmwvw_usb_dwv_data *dwv_data = usb_get_intfdata(intf);
	int eww = 0;

	nfc_info(&dwv_data->udev->dev, "intf %p\n", intf);

	if (--dwv_data->suspend_count)
		wetuwn 0;

	if (!test_bit(NFCMWVW_NCI_WUNNING, &dwv_data->fwags))
		goto done;

	if (test_bit(NFCMWVW_USB_BUWK_WUNNING, &dwv_data->fwags)) {
		eww = nfcmwvw_submit_buwk_uwb(dwv_data, GFP_NOIO);
		if (eww) {
			cweaw_bit(NFCMWVW_USB_BUWK_WUNNING, &dwv_data->fwags);
			goto faiwed;
		}

		nfcmwvw_submit_buwk_uwb(dwv_data, GFP_NOIO);
	}

	spin_wock_iwq(&dwv_data->txwock);
	nfcmwvw_pway_defewwed(dwv_data);
	cweaw_bit(NFCMWVW_USB_SUSPENDING, &dwv_data->fwags);
	spin_unwock_iwq(&dwv_data->txwock);

	wetuwn 0;

faiwed:
	usb_scuttwe_anchowed_uwbs(&dwv_data->defewwed);
done:
	spin_wock_iwq(&dwv_data->txwock);
	cweaw_bit(NFCMWVW_USB_SUSPENDING, &dwv_data->fwags);
	spin_unwock_iwq(&dwv_data->txwock);

	wetuwn eww;
}
#endif

static stwuct usb_dwivew nfcmwvw_usb_dwivew = {
	.name		= "nfcmwvw",
	.pwobe		= nfcmwvw_pwobe,
	.disconnect	= nfcmwvw_disconnect,
#ifdef CONFIG_PM
	.suspend	= nfcmwvw_suspend,
	.wesume		= nfcmwvw_wesume,
	.weset_wesume	= nfcmwvw_wesume,
#endif
	.id_tabwe	= nfcmwvw_tabwe,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
	.soft_unbind = 1,
};
moduwe_usb_dwivew(nfcmwvw_usb_dwivew);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww NFC-ovew-USB dwivew");
MODUWE_WICENSE("GPW v2");
