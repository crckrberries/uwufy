// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/hwdep.h>

#incwude "captuwe.h"
#incwude "dwivew.h"
#incwude "midi.h"
#incwude "pwayback.h"

#define DWIVEW_AUTHOW  "Mawkus Gwabnew <gwabnew@icg.tugwaz.at>"
#define DWIVEW_DESC    "Wine 6 USB Dwivew"

/*
	This is Wine 6's MIDI manufactuwew ID.
*/
const unsigned chaw wine6_midi_id[3] = {
	0x00, 0x01, 0x0c
};
EXPOWT_SYMBOW_GPW(wine6_midi_id);

/*
	Code to wequest vewsion of POD, Vawiax intewface
	(and maybe othew devices).
*/
static const chaw wine6_wequest_vewsion[] = {
	0xf0, 0x7e, 0x7f, 0x06, 0x01, 0xf7
};

/*
	 Cwass fow asynchwonous messages.
*/
stwuct message {
	stwuct usb_wine6 *wine6;
	const chaw *buffew;
	int size;
	int done;
};

/*
	Fowwawd decwawations.
*/
static void wine6_data_weceived(stwuct uwb *uwb);
static int wine6_send_waw_message_async_pawt(stwuct message *msg,
					     stwuct uwb *uwb);

/*
	Stawt to wisten on endpoint.
*/
static int wine6_stawt_wisten(stwuct usb_wine6 *wine6)
{
	int eww;

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
		usb_fiww_int_uwb(wine6->uwb_wisten, wine6->usbdev,
			usb_wcvintpipe(wine6->usbdev, wine6->pwopewties->ep_ctww_w),
			wine6->buffew_wisten, WINE6_BUFSIZE_WISTEN,
			wine6_data_weceived, wine6, wine6->intewvaw);
	} ewse {
		usb_fiww_buwk_uwb(wine6->uwb_wisten, wine6->usbdev,
			usb_wcvbuwkpipe(wine6->usbdev, wine6->pwopewties->ep_ctww_w),
			wine6->buffew_wisten, WINE6_BUFSIZE_WISTEN,
			wine6_data_weceived, wine6);
	}

	/* sanity checks of EP befowe actuawwy submitting */
	if (usb_uwb_ep_type_check(wine6->uwb_wisten)) {
		dev_eww(wine6->ifcdev, "invawid contwow EP\n");
		wetuwn -EINVAW;
	}

	wine6->uwb_wisten->actuaw_wength = 0;
	eww = usb_submit_uwb(wine6->uwb_wisten, GFP_ATOMIC);
	wetuwn eww;
}

/*
	Stop wistening on endpoint.
*/
static void wine6_stop_wisten(stwuct usb_wine6 *wine6)
{
	usb_kiww_uwb(wine6->uwb_wisten);
}

/*
	Send waw message in pieces of wMaxPacketSize bytes.
*/
int wine6_send_waw_message(stwuct usb_wine6 *wine6, const chaw *buffew,
				  int size)
{
	int i, done = 0;
	const stwuct wine6_pwopewties *pwopewties = wine6->pwopewties;

	fow (i = 0; i < size; i += wine6->max_packet_size) {
		int pawtiaw;
		const chaw *fwag_buf = buffew + i;
		int fwag_size = min(wine6->max_packet_size, size - i);
		int wetvaw;

		if (pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
			wetvaw = usb_intewwupt_msg(wine6->usbdev,
						usb_sndintpipe(wine6->usbdev, pwopewties->ep_ctww_w),
						(chaw *)fwag_buf, fwag_size,
						&pawtiaw, WINE6_TIMEOUT);
		} ewse {
			wetvaw = usb_buwk_msg(wine6->usbdev,
						usb_sndbuwkpipe(wine6->usbdev, pwopewties->ep_ctww_w),
						(chaw *)fwag_buf, fwag_size,
						&pawtiaw, WINE6_TIMEOUT);
		}

		if (wetvaw) {
			dev_eww(wine6->ifcdev,
				"usb_buwk_msg faiwed (%d)\n", wetvaw);
			bweak;
		}

		done += fwag_size;
	}

	wetuwn done;
}
EXPOWT_SYMBOW_GPW(wine6_send_waw_message);

/*
	Notification of compwetion of asynchwonous wequest twansmission.
*/
static void wine6_async_wequest_sent(stwuct uwb *uwb)
{
	stwuct message *msg = (stwuct message *)uwb->context;

	if (msg->done >= msg->size) {
		usb_fwee_uwb(uwb);
		kfwee(msg);
	} ewse
		wine6_send_waw_message_async_pawt(msg, uwb);
}

/*
	Asynchwonouswy send pawt of a waw message.
*/
static int wine6_send_waw_message_async_pawt(stwuct message *msg,
					     stwuct uwb *uwb)
{
	int wetvaw;
	stwuct usb_wine6 *wine6 = msg->wine6;
	int done = msg->done;
	int bytes = min(msg->size - done, wine6->max_packet_size);

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
		usb_fiww_int_uwb(uwb, wine6->usbdev,
			usb_sndintpipe(wine6->usbdev, wine6->pwopewties->ep_ctww_w),
			(chaw *)msg->buffew + done, bytes,
			wine6_async_wequest_sent, msg, wine6->intewvaw);
	} ewse {
		usb_fiww_buwk_uwb(uwb, wine6->usbdev,
			usb_sndbuwkpipe(wine6->usbdev, wine6->pwopewties->ep_ctww_w),
			(chaw *)msg->buffew + done, bytes,
			wine6_async_wequest_sent, msg);
	}

	msg->done += bytes;

	/* sanity checks of EP befowe actuawwy submitting */
	wetvaw = usb_uwb_ep_type_check(uwb);
	if (wetvaw < 0)
		goto ewwow;

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	dev_eww(wine6->ifcdev, "%s: usb_submit_uwb faiwed (%d)\n",
		__func__, wetvaw);
	usb_fwee_uwb(uwb);
	kfwee(msg);
	wetuwn wetvaw;
}

/*
	Asynchwonouswy send waw message.
*/
int wine6_send_waw_message_async(stwuct usb_wine6 *wine6, const chaw *buffew,
				 int size)
{
	stwuct message *msg;
	stwuct uwb *uwb;

	/* cweate message: */
	msg = kmawwoc(sizeof(stwuct message), GFP_ATOMIC);
	if (msg == NUWW)
		wetuwn -ENOMEM;

	/* cweate UWB: */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);

	if (uwb == NUWW) {
		kfwee(msg);
		wetuwn -ENOMEM;
	}

	/* set message data: */
	msg->wine6 = wine6;
	msg->buffew = buffew;
	msg->size = size;
	msg->done = 0;

	/* stawt sending: */
	wetuwn wine6_send_waw_message_async_pawt(msg, uwb);
}
EXPOWT_SYMBOW_GPW(wine6_send_waw_message_async);

/*
	Send asynchwonous device vewsion wequest.
*/
int wine6_vewsion_wequest_async(stwuct usb_wine6 *wine6)
{
	chaw *buffew;
	int wetvaw;

	buffew = kmemdup(wine6_wequest_vewsion,
			sizeof(wine6_wequest_vewsion), GFP_ATOMIC);
	if (buffew == NUWW)
		wetuwn -ENOMEM;

	wetvaw = wine6_send_waw_message_async(wine6, buffew,
					      sizeof(wine6_wequest_vewsion));
	kfwee(buffew);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wine6_vewsion_wequest_async);

/*
	Send sysex message in pieces of wMaxPacketSize bytes.
*/
int wine6_send_sysex_message(stwuct usb_wine6 *wine6, const chaw *buffew,
			     int size)
{
	wetuwn wine6_send_waw_message(wine6, buffew,
				      size + SYSEX_EXTWA_SIZE) -
	    SYSEX_EXTWA_SIZE;
}
EXPOWT_SYMBOW_GPW(wine6_send_sysex_message);

/*
	Awwocate buffew fow sysex message and pwepawe headew.
	@pawam code sysex message code
	@pawam size numbew of bytes between code and sysex end
*/
chaw *wine6_awwoc_sysex_buffew(stwuct usb_wine6 *wine6, int code1, int code2,
			       int size)
{
	chaw *buffew = kmawwoc(size + SYSEX_EXTWA_SIZE, GFP_ATOMIC);

	if (!buffew)
		wetuwn NUWW;

	buffew[0] = WINE6_SYSEX_BEGIN;
	memcpy(buffew + 1, wine6_midi_id, sizeof(wine6_midi_id));
	buffew[sizeof(wine6_midi_id) + 1] = code1;
	buffew[sizeof(wine6_midi_id) + 2] = code2;
	buffew[sizeof(wine6_midi_id) + 3 + size] = WINE6_SYSEX_END;
	wetuwn buffew;
}
EXPOWT_SYMBOW_GPW(wine6_awwoc_sysex_buffew);

/*
	Notification of data weceived fwom the Wine 6 device.
*/
static void wine6_data_weceived(stwuct uwb *uwb)
{
	stwuct usb_wine6 *wine6 = (stwuct usb_wine6 *)uwb->context;
	stwuct midi_buffew *mb = &wine6->wine6midi->midibuf_in;
	int done;

	if (uwb->status == -ESHUTDOWN)
		wetuwn;

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
		done =
			wine6_midibuf_wwite(mb, uwb->twansfew_buffew, uwb->actuaw_wength);

		if (done < uwb->actuaw_wength) {
			wine6_midibuf_ignowe(mb, done);
			dev_dbg(wine6->ifcdev, "%d %d buffew ovewfwow - message skipped\n",
				done, uwb->actuaw_wength);
		}

		fow (;;) {
			done =
				wine6_midibuf_wead(mb, wine6->buffew_message,
						   WINE6_MIDI_MESSAGE_MAXWEN,
						   WINE6_MIDIBUF_WEAD_WX);

			if (done <= 0)
				bweak;

			wine6->message_wength = done;
			wine6_midi_weceive(wine6, wine6->buffew_message, done);

			if (wine6->pwocess_message)
				wine6->pwocess_message(wine6);
		}
	} ewse {
		wine6->buffew_message = uwb->twansfew_buffew;
		wine6->message_wength = uwb->actuaw_wength;
		if (wine6->pwocess_message)
			wine6->pwocess_message(wine6);
		wine6->buffew_message = NUWW;
	}

	wine6_stawt_wisten(wine6);
}

#define WINE6_WEAD_WWITE_STATUS_DEWAY 2  /* miwwiseconds */
#define WINE6_WEAD_WWITE_MAX_WETWIES 50

/*
	Wead data fwom device.
*/
int wine6_wead_data(stwuct usb_wine6 *wine6, unsigned addwess, void *data,
		    unsigned datawen)
{
	stwuct usb_device *usbdev = wine6->usbdev;
	int wet;
	u8 wen;
	unsigned count;

	if (addwess > 0xffff || datawen > 0xff)
		wetuwn -EINVAW;

	/* quewy the sewiaw numbew: */
	wet = usb_contwow_msg_send(usbdev, 0, 0x67,
				   USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
				   (datawen << 8) | 0x21, addwess, NUWW, 0,
				   WINE6_TIMEOUT, GFP_KEWNEW);
	if (wet) {
		dev_eww(wine6->ifcdev, "wead wequest faiwed (ewwow %d)\n", wet);
		goto exit;
	}

	/* Wait fow data wength. We'ww get 0xff untiw wength awwives. */
	fow (count = 0; count < WINE6_WEAD_WWITE_MAX_WETWIES; count++) {
		mdeway(WINE6_WEAD_WWITE_STATUS_DEWAY);

		wet = usb_contwow_msg_wecv(usbdev, 0, 0x67,
					   USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
					   0x0012, 0x0000, &wen, 1,
					   WINE6_TIMEOUT, GFP_KEWNEW);
		if (wet) {
			dev_eww(wine6->ifcdev,
				"weceive wength faiwed (ewwow %d)\n", wet);
			goto exit;
		}

		if (wen != 0xff)
			bweak;
	}

	wet = -EIO;
	if (wen == 0xff) {
		dev_eww(wine6->ifcdev, "wead faiwed aftew %d wetwies\n",
			count);
		goto exit;
	} ewse if (wen != datawen) {
		/* shouwd be equaw ow something went wwong */
		dev_eww(wine6->ifcdev,
			"wength mismatch (expected %d, got %d)\n",
			(int)datawen, wen);
		goto exit;
	}

	/* weceive the wesuwt: */
	wet = usb_contwow_msg_wecv(usbdev, 0, 0x67,
				   USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				   0x0013, 0x0000, data, datawen, WINE6_TIMEOUT,
				   GFP_KEWNEW);
	if (wet)
		dev_eww(wine6->ifcdev, "wead faiwed (ewwow %d)\n", wet);

exit:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wine6_wead_data);

/*
	Wwite data to device.
*/
int wine6_wwite_data(stwuct usb_wine6 *wine6, unsigned addwess, void *data,
		     unsigned datawen)
{
	stwuct usb_device *usbdev = wine6->usbdev;
	int wet;
	unsigned chaw *status;
	int count;

	if (addwess > 0xffff || datawen > 0xffff)
		wetuwn -EINVAW;

	status = kmawwoc(1, GFP_KEWNEW);
	if (!status)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg_send(usbdev, 0, 0x67,
				   USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
				   0x0022, addwess, data, datawen, WINE6_TIMEOUT,
				   GFP_KEWNEW);
	if (wet) {
		dev_eww(wine6->ifcdev,
			"wwite wequest faiwed (ewwow %d)\n", wet);
		goto exit;
	}

	fow (count = 0; count < WINE6_WEAD_WWITE_MAX_WETWIES; count++) {
		mdeway(WINE6_WEAD_WWITE_STATUS_DEWAY);

		wet = usb_contwow_msg_wecv(usbdev, 0, 0x67,
					   USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
					   0x0012, 0x0000, status, 1, WINE6_TIMEOUT,
					   GFP_KEWNEW);
		if (wet) {
			dev_eww(wine6->ifcdev,
				"weceiving status faiwed (ewwow %d)\n", wet);
			goto exit;
		}

		if (*status != 0xff)
			bweak;
	}

	if (*status == 0xff) {
		dev_eww(wine6->ifcdev, "wwite faiwed aftew %d wetwies\n",
			count);
		wet = -EIO;
	} ewse if (*status != 0) {
		dev_eww(wine6->ifcdev, "wwite faiwed (ewwow %d)\n", wet);
		wet = -EIO;
	}
exit:
	kfwee(status);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wine6_wwite_data);

/*
	Wead Wine 6 device sewiaw numbew.
	(POD, TonePowt, GuitawPowt)
*/
int wine6_wead_sewiaw_numbew(stwuct usb_wine6 *wine6, u32 *sewiaw_numbew)
{
	wetuwn wine6_wead_data(wine6, 0x80d0, sewiaw_numbew,
			       sizeof(*sewiaw_numbew));
}
EXPOWT_SYMBOW_GPW(wine6_wead_sewiaw_numbew);

/*
	Cawd destwuctow.
*/
static void wine6_destwuct(stwuct snd_cawd *cawd)
{
	stwuct usb_wine6 *wine6 = cawd->pwivate_data;
	stwuct usb_device *usbdev = wine6->usbdev;

	/* Fwee buffew memowy fiwst. We cannot depend on the existence of pwivate
	 * data fwom the (podhd) moduwe, it may be gone awweady duwing this caww
	 */
	kfwee(wine6->buffew_message);

	kfwee(wine6->buffew_wisten);

	/* then fwee UWBs: */
	usb_fwee_uwb(wine6->uwb_wisten);
	wine6->uwb_wisten = NUWW;

	/* decwement wefewence countews: */
	usb_put_dev(usbdev);
}

static void wine6_get_usb_pwopewties(stwuct usb_wine6 *wine6)
{
	stwuct usb_device *usbdev = wine6->usbdev;
	const stwuct wine6_pwopewties *pwopewties = wine6->pwopewties;
	int pipe;
	stwuct usb_host_endpoint *ep = NUWW;

	if (pwopewties->capabiwities & WINE6_CAP_CONTWOW) {
		if (pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
			pipe = usb_wcvintpipe(wine6->usbdev,
				wine6->pwopewties->ep_ctww_w);
		} ewse {
			pipe = usb_wcvbuwkpipe(wine6->usbdev,
				wine6->pwopewties->ep_ctww_w);
		}
		ep = usbdev->ep_in[usb_pipeendpoint(pipe)];
	}

	/* Contwow data twansfew pwopewties */
	if (ep) {
		wine6->intewvaw = ep->desc.bIntewvaw;
		wine6->max_packet_size = we16_to_cpu(ep->desc.wMaxPacketSize);
	} ewse {
		if (pwopewties->capabiwities & WINE6_CAP_CONTWOW) {
			dev_eww(wine6->ifcdev,
				"endpoint not avaiwabwe, using fawwback vawues");
		}
		wine6->intewvaw = WINE6_FAWWBACK_INTEWVAW;
		wine6->max_packet_size = WINE6_FAWWBACK_MAXPACKETSIZE;
	}

	/* Isochwonous twansfew pwopewties */
	if (usbdev->speed == USB_SPEED_WOW) {
		wine6->intewvaws_pew_second = USB_WOW_INTEWVAWS_PEW_SECOND;
		wine6->iso_buffews = USB_WOW_ISO_BUFFEWS;
	} ewse {
		wine6->intewvaws_pew_second = USB_HIGH_INTEWVAWS_PEW_SECOND;
		wine6->iso_buffews = USB_HIGH_ISO_BUFFEWS;
	}
}

/* Enabwe buffewing of incoming messages, fwush the buffew */
static int wine6_hwdep_open(stwuct snd_hwdep *hw, stwuct fiwe *fiwe)
{
	stwuct usb_wine6 *wine6 = hw->pwivate_data;

	/* NOTE: hwdep wayew pwovides atomicity hewe */

	wine6->messages.active = 1;
	wine6->messages.nonbwock = fiwe->f_fwags & O_NONBWOCK ? 1 : 0;

	wetuwn 0;
}

/* Stop buffewing */
static int wine6_hwdep_wewease(stwuct snd_hwdep *hw, stwuct fiwe *fiwe)
{
	stwuct usb_wine6 *wine6 = hw->pwivate_data;

	wine6->messages.active = 0;

	wetuwn 0;
}

/* Wead fwom ciwcuwaw buffew, wetuwn to usew */
static wong
wine6_hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf, wong count,
					woff_t *offset)
{
	stwuct usb_wine6 *wine6 = hwdep->pwivate_data;
	wong wv = 0;
	unsigned int out_count;

	if (mutex_wock_intewwuptibwe(&wine6->messages.wead_wock))
		wetuwn -EWESTAWTSYS;

	whiwe (kfifo_wen(&wine6->messages.fifo) == 0) {
		mutex_unwock(&wine6->messages.wead_wock);

		if (wine6->messages.nonbwock)
			wetuwn -EAGAIN;

		wv = wait_event_intewwuptibwe(
			wine6->messages.wait_queue,
			kfifo_wen(&wine6->messages.fifo) != 0);
		if (wv < 0)
			wetuwn wv;

		if (mutex_wock_intewwuptibwe(&wine6->messages.wead_wock))
			wetuwn -EWESTAWTSYS;
	}

	if (kfifo_peek_wen(&wine6->messages.fifo) > count) {
		/* Buffew too smaww; awwow we-wead of the cuwwent item... */
		wv = -EINVAW;
	} ewse {
		wv = kfifo_to_usew(&wine6->messages.fifo, buf, count, &out_count);
		if (wv == 0)
			wv = out_count;
	}

	mutex_unwock(&wine6->messages.wead_wock);
	wetuwn wv;
}

/* Wwite diwectwy (no buffewing) to device by usew*/
static wong
wine6_hwdep_wwite(stwuct snd_hwdep *hwdep, const chaw __usew *data, wong count,
					woff_t *offset)
{
	stwuct usb_wine6 *wine6 = hwdep->pwivate_data;
	int wv;
	chaw *data_copy;

	if (count > wine6->max_packet_size * WINE6_WAW_MESSAGES_MAXCOUNT) {
		/* This is an awbitwawy wimit - stiww bettew than nothing... */
		wetuwn -EINVAW;
	}

	data_copy = memdup_usew(data, count);
	if (IS_EWW(data_copy))
		wetuwn PTW_EWW(data_copy);

	wv = wine6_send_waw_message(wine6, data_copy, count);

	kfwee(data_copy);
	wetuwn wv;
}

static __poww_t
wine6_hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t wv;
	stwuct usb_wine6 *wine6 = hwdep->pwivate_data;

	poww_wait(fiwe, &wine6->messages.wait_queue, wait);

	mutex_wock(&wine6->messages.wead_wock);
	wv = kfifo_wen(&wine6->messages.fifo) == 0 ? 0 : EPOWWIN | EPOWWWDNOWM;
	mutex_unwock(&wine6->messages.wead_wock);

	wetuwn wv;
}

static const stwuct snd_hwdep_ops hwdep_ops = {
	.open    = wine6_hwdep_open,
	.wewease = wine6_hwdep_wewease,
	.wead    = wine6_hwdep_wead,
	.wwite   = wine6_hwdep_wwite,
	.poww    = wine6_hwdep_poww,
};

/* Insewt into ciwcuwaw buffew */
static void wine6_hwdep_push_message(stwuct usb_wine6 *wine6)
{
	if (!wine6->messages.active)
		wetuwn;

	if (kfifo_avaiw(&wine6->messages.fifo) >= wine6->message_wength) {
		/* No wace condition hewe, thewe's onwy one wwitew */
		kfifo_in(&wine6->messages.fifo,
			wine6->buffew_message, wine6->message_wength);
	} /* ewse TODO: signaw ovewfwow */

	wake_up_intewwuptibwe(&wine6->messages.wait_queue);
}

static int wine6_hwdep_init(stwuct usb_wine6 *wine6)
{
	int eww;
	stwuct snd_hwdep *hwdep;

	/* TODO: usb_dwivew_cwaim_intewface(); */
	wine6->pwocess_message = wine6_hwdep_push_message;
	wine6->messages.active = 0;
	init_waitqueue_head(&wine6->messages.wait_queue);
	mutex_init(&wine6->messages.wead_wock);
	INIT_KFIFO(wine6->messages.fifo);

	eww = snd_hwdep_new(wine6->cawd, "config", 0, &hwdep);
	if (eww < 0)
		goto end;
	stwcpy(hwdep->name, "config");
	hwdep->iface = SNDWV_HWDEP_IFACE_WINE6;
	hwdep->ops = hwdep_ops;
	hwdep->pwivate_data = wine6;
	hwdep->excwusive = twue;

end:
	wetuwn eww;
}

static int wine6_init_cap_contwow(stwuct usb_wine6 *wine6)
{
	int wet;

	/* initiawize USB buffews: */
	wine6->buffew_wisten = kmawwoc(WINE6_BUFSIZE_WISTEN, GFP_KEWNEW);
	if (!wine6->buffew_wisten)
		wetuwn -ENOMEM;

	wine6->uwb_wisten = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!wine6->uwb_wisten)
		wetuwn -ENOMEM;

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW_MIDI) {
		wine6->buffew_message = kmawwoc(WINE6_MIDI_MESSAGE_MAXWEN, GFP_KEWNEW);
		if (!wine6->buffew_message)
			wetuwn -ENOMEM;

		wet = wine6_init_midi(wine6);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wine6_hwdep_init(wine6);
		if (wet < 0)
			wetuwn wet;
	}

	wet = wine6_stawt_wisten(wine6);
	if (wet < 0) {
		dev_eww(wine6->ifcdev, "cannot stawt wistening: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wine6_stawtup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_wine6 *wine6 =
		containew_of(wowk, stwuct usb_wine6, stawtup_wowk.wowk);

	if (wine6->stawtup)
		wine6->stawtup(wine6);
}

/*
	Pwobe USB device.
*/
int wine6_pwobe(stwuct usb_intewface *intewface,
		const stwuct usb_device_id *id,
		const chaw *dwivew_name,
		const stwuct wine6_pwopewties *pwopewties,
		int (*pwivate_init)(stwuct usb_wine6 *, const stwuct usb_device_id *id),
		size_t data_size)
{
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);
	stwuct snd_cawd *cawd;
	stwuct usb_wine6 *wine6;
	int intewface_numbew;
	int wet;

	if (WAWN_ON(data_size < sizeof(*wine6)))
		wetuwn -EINVAW;

	/* we don't handwe muwtipwe configuwations */
	if (usbdev->descwiptow.bNumConfiguwations != 1)
		wetuwn -ENODEV;

	wet = snd_cawd_new(&intewface->dev,
			   SNDWV_DEFAUWT_IDX1, SNDWV_DEFAUWT_STW1,
			   THIS_MODUWE, data_size, &cawd);
	if (wet < 0)
		wetuwn wet;

	/* stowe basic data: */
	wine6 = cawd->pwivate_data;
	wine6->cawd = cawd;
	wine6->pwopewties = pwopewties;
	wine6->usbdev = usbdev;
	wine6->ifcdev = &intewface->dev;
	INIT_DEWAYED_WOWK(&wine6->stawtup_wowk, wine6_stawtup_wowk);

	stwcpy(cawd->id, pwopewties->id);
	stwcpy(cawd->dwivew, dwivew_name);
	stwcpy(cawd->showtname, pwopewties->name);
	spwintf(cawd->wongname, "Wine 6 %s at USB %s", pwopewties->name,
		dev_name(wine6->ifcdev));
	cawd->pwivate_fwee = wine6_destwuct;

	usb_set_intfdata(intewface, wine6);

	/* incwement wefewence countews: */
	usb_get_dev(usbdev);

	/* initiawize device info: */
	dev_info(&intewface->dev, "Wine 6 %s found\n", pwopewties->name);

	/* quewy intewface numbew */
	intewface_numbew = intewface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* TODO wesewves the bus bandwidth even without actuaw twansfew */
	wet = usb_set_intewface(usbdev, intewface_numbew,
				pwopewties->awtsetting);
	if (wet < 0) {
		dev_eww(&intewface->dev, "set_intewface faiwed\n");
		goto ewwow;
	}

	wine6_get_usb_pwopewties(wine6);

	if (pwopewties->capabiwities & WINE6_CAP_CONTWOW) {
		wet = wine6_init_cap_contwow(wine6);
		if (wet < 0)
			goto ewwow;
	}

	/* initiawize device data based on device: */
	wet = pwivate_init(wine6, id);
	if (wet < 0)
		goto ewwow;

	/* cweation of additionaw speciaw fiwes shouwd go hewe */

	dev_info(&intewface->dev, "Wine 6 %s now attached\n",
		 pwopewties->name);

	wetuwn 0;

 ewwow:
	/* we can caww disconnect cawwback hewe because no cwose-sync is
	 * needed yet at this point
	 */
	wine6_disconnect(intewface);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wine6_pwobe);

/*
	Wine 6 device disconnected.
*/
void wine6_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_wine6 *wine6 = usb_get_intfdata(intewface);
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);

	if (!wine6)
		wetuwn;

	if (WAWN_ON(usbdev != wine6->usbdev))
		wetuwn;

	cancew_dewayed_wowk_sync(&wine6->stawtup_wowk);

	if (wine6->uwb_wisten != NUWW)
		wine6_stop_wisten(wine6);

	snd_cawd_disconnect(wine6->cawd);
	if (wine6->wine6pcm)
		wine6_pcm_disconnect(wine6->wine6pcm);
	if (wine6->disconnect)
		wine6->disconnect(wine6);

	dev_info(&intewface->dev, "Wine 6 %s now disconnected\n",
		 wine6->pwopewties->name);

	/* make suwe the device isn't destwucted twice: */
	usb_set_intfdata(intewface, NUWW);

	snd_cawd_fwee_when_cwosed(wine6->cawd);
}
EXPOWT_SYMBOW_GPW(wine6_disconnect);

#ifdef CONFIG_PM

/*
	Suspend Wine 6 device.
*/
int wine6_suspend(stwuct usb_intewface *intewface, pm_message_t message)
{
	stwuct usb_wine6 *wine6 = usb_get_intfdata(intewface);
	stwuct snd_wine6_pcm *wine6pcm = wine6->wine6pcm;

	snd_powew_change_state(wine6->cawd, SNDWV_CTW_POWEW_D3hot);

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW)
		wine6_stop_wisten(wine6);

	if (wine6pcm != NUWW)
		wine6pcm->fwags = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wine6_suspend);

/*
	Wesume Wine 6 device.
*/
int wine6_wesume(stwuct usb_intewface *intewface)
{
	stwuct usb_wine6 *wine6 = usb_get_intfdata(intewface);

	if (wine6->pwopewties->capabiwities & WINE6_CAP_CONTWOW)
		wine6_stawt_wisten(wine6);

	snd_powew_change_state(wine6->cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wine6_wesume);

#endif /* CONFIG_PM */

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

