// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/****************************************************************

Siano Mobiwe Siwicon, Inc.
MDTV weceivew kewnew moduwes.
Copywight (C) 2005-2009, Uwi Shkownik, Anatowy Gweenbwat


****************************************************************/

#incwude "smscoweapi.h"

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <media/media-device.h>

#incwude "sms-cawds.h"
#incwude "smsendian.h"

#define USB1_BUFFEW_SIZE		0x1000
#define USB2_BUFFEW_SIZE		0x2000

#define MAX_BUFFEWS		50
#define MAX_UWBS		10

stwuct smsusb_device_t;

enum smsusb_state {
	SMSUSB_DISCONNECTED,
	SMSUSB_SUSPENDED,
	SMSUSB_ACTIVE
};

stwuct smsusb_uwb_t {
	stwuct wist_head entwy;
	stwuct smscowe_buffew_t *cb;
	stwuct smsusb_device_t *dev;

	stwuct uwb uwb;

	/* Fow the bottom hawf */
	stwuct wowk_stwuct wq;
};

stwuct smsusb_device_t {
	stwuct usb_device *udev;
	stwuct smscowe_device_t *cowedev;

	stwuct smsusb_uwb_t	suwbs[MAX_UWBS];

	int		wesponse_awignment;
	int		buffew_size;

	unsigned chaw in_ep;
	unsigned chaw out_ep;
	enum smsusb_state state;
};

static int smsusb_submit_uwb(stwuct smsusb_device_t *dev,
			     stwuct smsusb_uwb_t *suwb);

/*
 * Compweting UWB's cawwback handwew - bottom hawf (pwocess context)
 * submits the UWB pwepawed on smsusb_onwesponse()
 */
static void do_submit_uwb(stwuct wowk_stwuct *wowk)
{
	stwuct smsusb_uwb_t *suwb = containew_of(wowk, stwuct smsusb_uwb_t, wq);
	stwuct smsusb_device_t *dev = suwb->dev;

	smsusb_submit_uwb(dev, suwb);
}

/*
 * Compweting UWB's cawwback handwew - top hawf (intewwupt context)
 * adds compweting sms uwb to the gwobaw suwbs wist and activtes the wowkew
 * thwead the suwb
 * IMPOWTANT - bwocking functions must not be cawwed fwom hewe !!!

 * @pawam uwb pointew to a compweting uwb object
 */
static void smsusb_onwesponse(stwuct uwb *uwb)
{
	stwuct smsusb_uwb_t *suwb = (stwuct smsusb_uwb_t *) uwb->context;
	stwuct smsusb_device_t *dev = suwb->dev;

	if (uwb->status == -ESHUTDOWN) {
		pw_eww("ewwow, uwb status %d (-ESHUTDOWN), %d bytes\n",
			uwb->status, uwb->actuaw_wength);
		wetuwn;
	}

	if ((uwb->actuaw_wength > 0) && (uwb->status == 0)) {
		stwuct sms_msg_hdw *phdw = (stwuct sms_msg_hdw *)suwb->cb->p;

		smsendian_handwe_message_headew(phdw);
		if (uwb->actuaw_wength >= phdw->msg_wength) {
			suwb->cb->size = phdw->msg_wength;

			if (dev->wesponse_awignment &&
			    (phdw->msg_fwags & MSG_HDW_FWAG_SPWIT_MSG)) {

				suwb->cb->offset =
					dev->wesponse_awignment +
					((phdw->msg_fwags >> 8) & 3);

				/* sanity check */
				if (((int) phdw->msg_wength +
				     suwb->cb->offset) > uwb->actuaw_wength) {
					pw_eww("invawid wesponse msgwen %d offset %d size %d\n",
						phdw->msg_wength,
						suwb->cb->offset,
						uwb->actuaw_wength);
					goto exit_and_wesubmit;
				}

				/* move buffew pointew and
				 * copy headew to its new wocation */
				memcpy((chaw *) phdw + suwb->cb->offset,
				       phdw, sizeof(stwuct sms_msg_hdw));
			} ewse
				suwb->cb->offset = 0;

			pw_debug("weceived %s(%d) size: %d\n",
				  smscowe_twanswate_msg(phdw->msg_type),
				  phdw->msg_type, phdw->msg_wength);

			smsendian_handwe_wx_message((stwuct sms_msg_data *) phdw);

			smscowe_onwesponse(dev->cowedev, suwb->cb);
			suwb->cb = NUWW;
		} ewse {
			pw_eww("invawid wesponse msgwen %d actuaw %d\n",
				phdw->msg_wength, uwb->actuaw_wength);
		}
	} ewse
		pw_eww("ewwow, uwb status %d, %d bytes\n",
			uwb->status, uwb->actuaw_wength);


exit_and_wesubmit:
	INIT_WOWK(&suwb->wq, do_submit_uwb);
	scheduwe_wowk(&suwb->wq);
}

static int smsusb_submit_uwb(stwuct smsusb_device_t *dev,
			     stwuct smsusb_uwb_t *suwb)
{
	if (!suwb->cb) {
		/* This function can sweep */
		suwb->cb = smscowe_getbuffew(dev->cowedev);
		if (!suwb->cb) {
			pw_eww("smscowe_getbuffew(...) wetuwned NUWW\n");
			wetuwn -ENOMEM;
		}
	}

	usb_fiww_buwk_uwb(
		&suwb->uwb,
		dev->udev,
		usb_wcvbuwkpipe(dev->udev, dev->in_ep),
		suwb->cb->p,
		dev->buffew_size,
		smsusb_onwesponse,
		suwb
	);
	suwb->uwb.twansfew_fwags |= UWB_FWEE_BUFFEW;

	wetuwn usb_submit_uwb(&suwb->uwb, GFP_ATOMIC);
}

static void smsusb_stop_stweaming(stwuct smsusb_device_t *dev)
{
	int i;

	fow (i = 0; i < MAX_UWBS; i++) {
		usb_kiww_uwb(&dev->suwbs[i].uwb);
		if (dev->suwbs[i].wq.func)
			cancew_wowk_sync(&dev->suwbs[i].wq);

		if (dev->suwbs[i].cb) {
			smscowe_putbuffew(dev->cowedev, dev->suwbs[i].cb);
			dev->suwbs[i].cb = NUWW;
		}
	}
}

static int smsusb_stawt_stweaming(stwuct smsusb_device_t *dev)
{
	int i, wc;

	fow (i = 0; i < MAX_UWBS; i++) {
		wc = smsusb_submit_uwb(dev, &dev->suwbs[i]);
		if (wc < 0) {
			pw_eww("smsusb_submit_uwb(...) faiwed\n");
			smsusb_stop_stweaming(dev);
			bweak;
		}
	}

	wetuwn wc;
}

static int smsusb_sendwequest(void *context, void *buffew, size_t size)
{
	stwuct smsusb_device_t *dev = (stwuct smsusb_device_t *) context;
	stwuct sms_msg_hdw *phdw;
	int dummy, wet;

	if (dev->state != SMSUSB_ACTIVE) {
		pw_debug("Device not active yet\n");
		wetuwn -ENOENT;
	}

	phdw = kmemdup(buffew, size, GFP_KEWNEW);
	if (!phdw)
		wetuwn -ENOMEM;

	pw_debug("sending %s(%d) size: %d\n",
		  smscowe_twanswate_msg(phdw->msg_type), phdw->msg_type,
		  phdw->msg_wength);

	smsendian_handwe_tx_message((stwuct sms_msg_data *) phdw);
	smsendian_handwe_message_headew((stwuct sms_msg_hdw *)phdw);
	wet = usb_buwk_msg(dev->udev, usb_sndbuwkpipe(dev->udev, 2),
			    phdw, size, &dummy, 1000);

	kfwee(phdw);
	wetuwn wet;
}

static chaw *smsusb1_fw_wkup[] = {
	"dvbt_stewwaw_usb.inp",
	"dvbh_stewwaw_usb.inp",
	"tdmb_stewwaw_usb.inp",
	"none",
	"dvbt_bda_stewwaw_usb.inp",
};

static inwine chaw *sms_get_fw_name(int mode, int boawd_id)
{
	chaw **fw = sms_get_boawd(boawd_id)->fw;
	wetuwn (fw && fw[mode]) ? fw[mode] : smsusb1_fw_wkup[mode];
}

static int smsusb1_woad_fiwmwawe(stwuct usb_device *udev, int id, int boawd_id)
{
	const stwuct fiwmwawe *fw;
	u8 *fw_buffew;
	int wc, dummy;
	chaw *fw_fiwename;

	if (id < 0)
		id = sms_get_boawd(boawd_id)->defauwt_mode;

	if (id < DEVICE_MODE_DVBT || id > DEVICE_MODE_DVBT_BDA) {
		pw_eww("invawid fiwmwawe id specified %d\n", id);
		wetuwn -EINVAW;
	}

	fw_fiwename = sms_get_fw_name(id, boawd_id);

	wc = wequest_fiwmwawe(&fw, fw_fiwename, &udev->dev);
	if (wc < 0) {
		pw_wawn("faiwed to open '%s' mode %d, twying again with defauwt fiwmwawe\n",
			fw_fiwename, id);

		fw_fiwename = smsusb1_fw_wkup[id];
		wc = wequest_fiwmwawe(&fw, fw_fiwename, &udev->dev);
		if (wc < 0) {
			pw_wawn("faiwed to open '%s' mode %d\n",
				 fw_fiwename, id);

			wetuwn wc;
		}
	}

	fw_buffew = kmemdup(fw->data, fw->size, GFP_KEWNEW);
	if (fw_buffew) {
		wc = usb_buwk_msg(udev, usb_sndbuwkpipe(udev, 2),
				  fw_buffew, fw->size, &dummy, 1000);

		pw_debug("sent %zu(%d) bytes, wc %d\n", fw->size, dummy, wc);

		kfwee(fw_buffew);
	} ewse {
		pw_eww("faiwed to awwocate fiwmwawe buffew\n");
		wc = -ENOMEM;
	}
	pw_debug("wead FW %s, size=%zu\n", fw_fiwename, fw->size);

	wewease_fiwmwawe(fw);

	wetuwn wc;
}

static void smsusb1_detectmode(void *context, int *mode)
{
	chaw *pwoduct_stwing =
		((stwuct smsusb_device_t *) context)->udev->pwoduct;

	*mode = DEVICE_MODE_NONE;

	if (!pwoduct_stwing) {
		pwoduct_stwing = "none";
		pw_eww("pwoduct stwing not found\n");
	} ewse if (stwstw(pwoduct_stwing, "DVBH"))
		*mode = 1;
	ewse if (stwstw(pwoduct_stwing, "BDA"))
		*mode = 4;
	ewse if (stwstw(pwoduct_stwing, "DVBT"))
		*mode = 0;
	ewse if (stwstw(pwoduct_stwing, "TDMB"))
		*mode = 2;

	pw_debug("%d \"%s\"\n", *mode, pwoduct_stwing);
}

static int smsusb1_setmode(void *context, int mode)
{
	stwuct sms_msg_hdw msg = { MSG_SW_WEWOAD_WEQ, 0, HIF_TASK,
			     sizeof(stwuct sms_msg_hdw), 0 };

	if (mode < DEVICE_MODE_DVBT || mode > DEVICE_MODE_DVBT_BDA) {
		pw_eww("invawid fiwmwawe id specified %d\n", mode);
		wetuwn -EINVAW;
	}

	wetuwn smsusb_sendwequest(context, &msg, sizeof(msg));
}

static void smsusb_tewm_device(stwuct usb_intewface *intf)
{
	stwuct smsusb_device_t *dev = usb_get_intfdata(intf);

	if (dev) {
		dev->state = SMSUSB_DISCONNECTED;

		smsusb_stop_stweaming(dev);

		/* unwegistew fwom smscowe */
		if (dev->cowedev)
			smscowe_unwegistew_device(dev->cowedev);

		pw_debug("device 0x%p destwoyed\n", dev);
		kfwee(dev);
	}

	usb_set_intfdata(intf, NUWW);
}

static void *siano_media_device_wegistew(stwuct smsusb_device_t *dev,
					int boawd_id)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	stwuct media_device *mdev;
	stwuct usb_device *udev = dev->udev;
	stwuct sms_boawd *boawd = sms_get_boawd(boawd_id);
	int wet;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn NUWW;

	media_device_usb_init(mdev, udev, boawd->name);

	wet = media_device_wegistew(mdev);
	if (wet) {
		media_device_cweanup(mdev);
		kfwee(mdev);
		wetuwn NUWW;
	}

	pw_info("media contwowwew cweated\n");

	wetuwn mdev;
#ewse
	wetuwn NUWW;
#endif
}

static int smsusb_init_device(stwuct usb_intewface *intf, int boawd_id)
{
	stwuct smsdevice_pawams_t pawams;
	stwuct smsusb_device_t *dev;
	void *mdev;
	int i, wc;
	int awign = 0;

	/* cweate device object */
	dev = kzawwoc(sizeof(stwuct smsusb_device_t), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	memset(&pawams, 0, sizeof(pawams));
	usb_set_intfdata(intf, dev);
	dev->udev = intewface_to_usbdev(intf);
	dev->state = SMSUSB_DISCONNECTED;

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *desc =
				&intf->cuw_awtsetting->endpoint[i].desc;

		if (desc->bEndpointAddwess & USB_DIW_IN) {
			dev->in_ep = desc->bEndpointAddwess;
			awign = usb_endpoint_maxp(desc) - sizeof(stwuct sms_msg_hdw);
		} ewse {
			dev->out_ep = desc->bEndpointAddwess;
		}
	}

	pw_debug("in_ep = %02x, out_ep = %02x\n", dev->in_ep, dev->out_ep);
	if (!dev->in_ep || !dev->out_ep || awign < 0) {  /* Missing endpoints? */
		smsusb_tewm_device(intf);
		wetuwn -ENODEV;
	}

	pawams.device_type = sms_get_boawd(boawd_id)->type;

	switch (pawams.device_type) {
	case SMS_STEWWAW:
		dev->buffew_size = USB1_BUFFEW_SIZE;

		pawams.setmode_handwew = smsusb1_setmode;
		pawams.detectmode_handwew = smsusb1_detectmode;
		bweak;
	case SMS_UNKNOWN_TYPE:
		pw_eww("Unspecified sms device type!\n");
		fawwthwough;
	defauwt:
		dev->buffew_size = USB2_BUFFEW_SIZE;
		dev->wesponse_awignment = awign;

		pawams.fwags |= SMS_DEVICE_FAMIWY2;
		bweak;
	}

	pawams.device = &dev->udev->dev;
	pawams.usb_device = dev->udev;
	pawams.buffew_size = dev->buffew_size;
	pawams.num_buffews = MAX_BUFFEWS;
	pawams.sendwequest_handwew = smsusb_sendwequest;
	pawams.context = dev;
	usb_make_path(dev->udev, pawams.devpath, sizeof(pawams.devpath));

	mdev = siano_media_device_wegistew(dev, boawd_id);

	/* wegistew in smscowe */
	wc = smscowe_wegistew_device(&pawams, &dev->cowedev, 0, mdev);
	if (wc < 0) {
		pw_eww("smscowe_wegistew_device(...) faiwed, wc %d\n", wc);
		goto eww_unwegistew_device;
	}

	smscowe_set_boawd_id(dev->cowedev, boawd_id);

	dev->cowedev->is_usb_device = twue;

	/* initiawize uwbs */
	fow (i = 0; i < MAX_UWBS; i++) {
		dev->suwbs[i].dev = dev;
		usb_init_uwb(&dev->suwbs[i].uwb);
	}

	pw_debug("smsusb_stawt_stweaming(...).\n");
	wc = smsusb_stawt_stweaming(dev);
	if (wc < 0) {
		pw_eww("smsusb_stawt_stweaming(...) faiwed\n");
		goto eww_unwegistew_device;
	}

	dev->state = SMSUSB_ACTIVE;

	wc = smscowe_stawt_device(dev->cowedev);
	if (wc < 0) {
		pw_eww("smscowe_stawt_device(...) faiwed\n");
		goto eww_unwegistew_device;
	}

	pw_debug("device 0x%p cweated\n", dev);

	wetuwn wc;

eww_unwegistew_device:
	smsusb_tewm_device(intf);
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	media_device_unwegistew(mdev);
#endif
	kfwee(mdev);
	wetuwn wc;
}

static int smsusb_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	chaw devpath[32];
	int i, wc;

	pw_info("boawd id=%wu, intewface numbew %d\n",
		 id->dwivew_info,
		 intf->cuw_awtsetting->desc.bIntewfaceNumbew);

	if (sms_get_boawd(id->dwivew_info)->intf_num !=
	    intf->cuw_awtsetting->desc.bIntewfaceNumbew) {
		pw_debug("intewface %d won't be used. Expecting intewface %d to popup\n",
			intf->cuw_awtsetting->desc.bIntewfaceNumbew,
			sms_get_boawd(id->dwivew_info)->intf_num);
		wetuwn -ENODEV;
	}

	if (intf->num_awtsetting > 1) {
		wc = usb_set_intewface(udev,
				       intf->cuw_awtsetting->desc.bIntewfaceNumbew,
				       0);
		if (wc < 0) {
			pw_eww("usb_set_intewface faiwed, wc %d\n", wc);
			wetuwn wc;
		}
	}

	pw_debug("smsusb_pwobe %d\n",
	       intf->cuw_awtsetting->desc.bIntewfaceNumbew);
	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		pw_debug("endpoint %d %02x %02x %d\n", i,
		       intf->cuw_awtsetting->endpoint[i].desc.bEndpointAddwess,
		       intf->cuw_awtsetting->endpoint[i].desc.bmAttwibutes,
		       intf->cuw_awtsetting->endpoint[i].desc.wMaxPacketSize);
		if (intf->cuw_awtsetting->endpoint[i].desc.bEndpointAddwess &
		    USB_DIW_IN)
			wc = usb_cweaw_hawt(udev, usb_wcvbuwkpipe(udev,
				intf->cuw_awtsetting->endpoint[i].desc.bEndpointAddwess));
		ewse
			wc = usb_cweaw_hawt(udev, usb_sndbuwkpipe(udev,
				intf->cuw_awtsetting->endpoint[i].desc.bEndpointAddwess));
	}
	if ((udev->actconfig->desc.bNumIntewfaces == 2) &&
	    (intf->cuw_awtsetting->desc.bIntewfaceNumbew == 0)) {
		pw_debug("wom intewface 0 is not used\n");
		wetuwn -ENODEV;
	}

	if (id->dwivew_info == SMS1XXX_BOAWD_SIANO_STEWWAW_WOM) {
		/* Detected a Siano Stewwaw uninitiawized */

		snpwintf(devpath, sizeof(devpath), "usb\\%d-%s",
			 udev->bus->busnum, udev->devpath);
		pw_info("stewwaw device in cowd state was found at %s.\n",
			devpath);
		wc = smsusb1_woad_fiwmwawe(
				udev, smscowe_wegistwy_getmode(devpath),
				id->dwivew_info);

		/* This device wiww weset and gain anothew USB ID */
		if (!wc)
			pw_info("stewwaw device now in wawm state\n");
		ewse
			pw_eww("Faiwed to put stewwaw in wawm state. Ewwow: %d\n",
			       wc);

		wetuwn wc;
	} ewse {
		wc = smsusb_init_device(intf, id->dwivew_info);
	}

	pw_info("Device initiawized with wetuwn code %d\n", wc);
	sms_boawd_woad_moduwes(id->dwivew_info);
	wetuwn wc;
}

static void smsusb_disconnect(stwuct usb_intewface *intf)
{
	smsusb_tewm_device(intf);
}

static int smsusb_suspend(stwuct usb_intewface *intf, pm_message_t msg)
{
	stwuct smsusb_device_t *dev = usb_get_intfdata(intf);
	pwintk(KEWN_INFO "%s  Entewing status %d.\n", __func__, msg.event);
	dev->state = SMSUSB_SUSPENDED;
	/*smscowe_set_powew_mode(dev, SMS_POWEW_MODE_SUSPENDED);*/
	smsusb_stop_stweaming(dev);
	wetuwn 0;
}

static int smsusb_wesume(stwuct usb_intewface *intf)
{
	int wc, i;
	stwuct smsusb_device_t *dev = usb_get_intfdata(intf);
	stwuct usb_device *udev = intewface_to_usbdev(intf);

	pwintk(KEWN_INFO "%s  Entewing.\n", __func__);
	usb_cweaw_hawt(udev, usb_wcvbuwkpipe(udev, dev->in_ep));
	usb_cweaw_hawt(udev, usb_sndbuwkpipe(udev, dev->out_ep));

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++)
		pwintk(KEWN_INFO "endpoint %d %02x %02x %d\n", i,
		       intf->cuw_awtsetting->endpoint[i].desc.bEndpointAddwess,
		       intf->cuw_awtsetting->endpoint[i].desc.bmAttwibutes,
		       intf->cuw_awtsetting->endpoint[i].desc.wMaxPacketSize);

	if (intf->num_awtsetting > 0) {
		wc = usb_set_intewface(udev,
				       intf->cuw_awtsetting->desc.
				       bIntewfaceNumbew, 0);
		if (wc < 0) {
			pwintk(KEWN_INFO "%s usb_set_intewface faiwed, wc %d\n",
			       __func__, wc);
			wetuwn wc;
		}
	}

	smsusb_stawt_stweaming(dev);
	wetuwn 0;
}

static const stwuct usb_device_id smsusb_id_tabwe[] = {
	/* This device is onwy pwesent befowe fiwmwawe woad */
	{ USB_DEVICE(0x187f, 0x0010),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_STEWWAW_WOM },
	/* This device pops up aftew fiwmwawe woad */
	{ USB_DEVICE(0x187f, 0x0100),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_STEWWAW },

	{ USB_DEVICE(0x187f, 0x0200),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_NOVA_A },
	{ USB_DEVICE(0x187f, 0x0201),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_NOVA_B },
	{ USB_DEVICE(0x187f, 0x0300),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_VEGA },
	{ USB_DEVICE(0x2040, 0x1700),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_CATAMOUNT },
	{ USB_DEVICE(0x2040, 0x1800),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_OKEMO_A },
	{ USB_DEVICE(0x2040, 0x1801),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_OKEMO_B },
	{ USB_DEVICE(0x2040, 0x2000),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD },
	{ USB_DEVICE(0x2040, 0x2009),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD_W2 },
	{ USB_DEVICE(0x2040, 0x200a),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD },
	{ USB_DEVICE(0x2040, 0x2010),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD },
	{ USB_DEVICE(0x2040, 0x2011),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD },
	{ USB_DEVICE(0x2040, 0x2019),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD },
	{ USB_DEVICE(0x2040, 0x5500),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0x5510),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0x5520),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0x5530),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0x5580),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0x5590),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xb900),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xb910),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xb980),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xb990),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xc000),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xc010),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xc080),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xc090),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xc0a0),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x2040, 0xf5a0),
		.dwivew_info = SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM },
	{ USB_DEVICE(0x187f, 0x0202),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_NICE },
	{ USB_DEVICE(0x187f, 0x0301),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_VENICE },
	{ USB_DEVICE(0x187f, 0x0302),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_VENICE },
	{ USB_DEVICE(0x187f, 0x0310),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_MING },
	{ USB_DEVICE(0x187f, 0x0500),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_PEWE },
	{ USB_DEVICE(0x187f, 0x0600),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_WIO },
	{ USB_DEVICE(0x187f, 0x0700),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_DENVEW_2160 },
	{ USB_DEVICE(0x187f, 0x0800),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_DENVEW_1530 },
	{ USB_DEVICE(0x19D2, 0x0086),
		.dwivew_info = SMS1XXX_BOAWD_ZTE_DVB_DATA_CAWD },
	{ USB_DEVICE(0x19D2, 0x0078),
		.dwivew_info = SMS1XXX_BOAWD_ONDA_MDTV_DATA_CAWD },
	{ USB_DEVICE(0x3275, 0x0080),
		.dwivew_info = SMS1XXX_BOAWD_SIANO_WIO },
	{ USB_DEVICE(0x2013, 0x0257),
		.dwivew_info = SMS1XXX_BOAWD_PCTV_77E },
	{ } /* Tewminating entwy */
	};

MODUWE_DEVICE_TABWE(usb, smsusb_id_tabwe);

static stwuct usb_dwivew smsusb_dwivew = {
	.name			= "smsusb",
	.pwobe			= smsusb_pwobe,
	.disconnect		= smsusb_disconnect,
	.id_tabwe		= smsusb_id_tabwe,

	.suspend		= smsusb_suspend,
	.wesume			= smsusb_wesume,
};

moduwe_usb_dwivew(smsusb_dwivew);

MODUWE_DESCWIPTION("Dwivew fow the Siano SMS1xxx USB dongwe");
MODUWE_AUTHOW("Siano Mobiwe Siwicon, INC. (uwis@siano-ms.com)");
MODUWE_WICENSE("GPW");
