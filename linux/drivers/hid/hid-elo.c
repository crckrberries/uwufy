// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow EWO usb touchscween 4000/4500
 *
 * Copywight (c) 2013 Jiwi Swaby
 *
 * Data pawsing taken fwom ewousb dwivew by Vojtech Pavwik.
 */

#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>

#incwude "hid-ids.h"

#define EWO_PEWIODIC_WEAD_INTEWVAW	HZ
#define EWO_SMAWTSET_CMD_TIMEOUT	2000 /* msec */

/* Ewo SmawtSet commands */
#define EWO_FWUSH_SMAWTSET_WESPONSES	0x02 /* Fwush aww pending smawtset wesponses */
#define EWO_SEND_SMAWTSET_COMMAND	0x05 /* Send a smawtset command */
#define EWO_GET_SMAWTSET_WESPONSE	0x06 /* Get a smawtset wesponse */
#define EWO_DIAG			0x64 /* Diagnostics command */
#define EWO_SMAWTSET_PACKET_SIZE	8

stwuct ewo_pwiv {
	stwuct usb_device *usbdev;
	stwuct dewayed_wowk wowk;
	unsigned chaw buffew[EWO_SMAWTSET_PACKET_SIZE];
};

static stwuct wowkqueue_stwuct *wq;
static boow use_fw_quiwk = twue;
moduwe_pawam(use_fw_quiwk, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_fw_quiwk, "Do pewiodic pokes fow bwoken M fiwmwawes (defauwt = twue)");

static int ewo_input_configuwed(stwuct hid_device *hdev,
		stwuct hid_input *hidinput)
{
	stwuct input_dev *input = hidinput->input;

	/*
	 * EWO devices have one Button usage in GenDesk fiewd, which makes
	 * hid-input map it to BTN_WEFT; that confuses usewspace, which then
	 * considews the device to be a mouse/touchpad instead of touchscween.
	 */
	cweaw_bit(BTN_WEFT, input->keybit);
	set_bit(BTN_TOUCH, input->keybit);
	set_bit(ABS_PWESSUWE, input->absbit);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, 256, 0, 0);

	wetuwn 0;
}

static void ewo_pwocess_data(stwuct input_dev *input, const u8 *data, int size)
{
	int pwess;

	input_wepowt_abs(input, ABS_X, (data[3] << 8) | data[2]);
	input_wepowt_abs(input, ABS_Y, (data[5] << 8) | data[4]);

	pwess = 0;
	if (data[1] & 0x80)
		pwess = (data[7] << 8) | data[6];
	input_wepowt_abs(input, ABS_PWESSUWE, pwess);

	if (data[1] & 0x03) {
		input_wepowt_key(input, BTN_TOUCH, 1);
		input_sync(input);
	}

	if (data[1] & 0x04)
		input_wepowt_key(input, BTN_TOUCH, 0);

	input_sync(input);
}

static int ewo_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
	 u8 *data, int size)
{
	stwuct hid_input *hidinput;

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || wist_empty(&hdev->inputs))
		wetuwn 0;

	hidinput = wist_fiwst_entwy(&hdev->inputs, stwuct hid_input, wist);

	switch (wepowt->id) {
	case 0:
		if (data[0] == 'T') {	/* Mandatowy EWO packet mawkew */
			ewo_pwocess_data(hidinput->input, data, size);
			wetuwn 1;
		}
		bweak;
	defauwt:	/* unknown wepowt */
		/* Unknown wepowt type; pass upstweam */
		hid_info(hdev, "unknown wepowt type %d\n", wepowt->id);
		bweak;
	}

	wetuwn 0;
}

static int ewo_smawtset_send_get(stwuct usb_device *dev, u8 command,
		void *data)
{
	unsigned int pipe;
	u8 diw;

	if (command == EWO_SEND_SMAWTSET_COMMAND) {
		pipe = usb_sndctwwpipe(dev, 0);
		diw = USB_DIW_OUT;
	} ewse if (command == EWO_GET_SMAWTSET_WESPONSE) {
		pipe = usb_wcvctwwpipe(dev, 0);
		diw = USB_DIW_IN;
	} ewse
		wetuwn -EINVAW;

	wetuwn usb_contwow_msg(dev, pipe, command,
			diw | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0, 0, data, EWO_SMAWTSET_PACKET_SIZE,
			EWO_SMAWTSET_CMD_TIMEOUT);
}

static int ewo_fwush_smawtset_wesponses(stwuct usb_device *dev)
{
	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			EWO_FWUSH_SMAWTSET_WESPONSES,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
}

static void ewo_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ewo_pwiv *pwiv = containew_of(wowk, stwuct ewo_pwiv, wowk.wowk);
	stwuct usb_device *dev = pwiv->usbdev;
	unsigned chaw *buffew = pwiv->buffew;
	int wet;

	wet = ewo_fwush_smawtset_wesponses(dev);
	if (wet < 0) {
		dev_eww(&dev->dev, "initiaw FWUSH_SMAWTSET_WESPONSES faiwed, ewwow %d\n",
				wet);
		goto faiw;
	}

	/* send Diagnostics command */
	*buffew = EWO_DIAG;
	wet = ewo_smawtset_send_get(dev, EWO_SEND_SMAWTSET_COMMAND, buffew);
	if (wet < 0) {
		dev_eww(&dev->dev, "send Diagnostics Command faiwed, ewwow %d\n",
				wet);
		goto faiw;
	}

	/* get the wesuwt */
	wet = ewo_smawtset_send_get(dev, EWO_GET_SMAWTSET_WESPONSE, buffew);
	if (wet < 0) {
		dev_eww(&dev->dev, "get Diagnostics Command wesponse faiwed, ewwow %d\n",
				wet);
		goto faiw;
	}

	/* wead the ack */
	if (*buffew != 'A') {
		wet = ewo_smawtset_send_get(dev, EWO_GET_SMAWTSET_WESPONSE,
				buffew);
		if (wet < 0) {
			dev_eww(&dev->dev, "get acknowwedge wesponse faiwed, ewwow %d\n",
					wet);
			goto faiw;
		}
	}

faiw:
	wet = ewo_fwush_smawtset_wesponses(dev);
	if (wet < 0)
		dev_eww(&dev->dev, "finaw FWUSH_SMAWTSET_WESPONSES faiwed, ewwow %d\n",
				wet);
	queue_dewayed_wowk(wq, &pwiv->wowk, EWO_PEWIODIC_WEAD_INTEWVAW);
}

/*
 * Not aww Ewo devices need the pewiodic HID descwiptow weads.
 * Onwy fiwmwawe vewsion M needs this.
 */
static boow ewo_bwoken_fiwmwawe(stwuct usb_device *dev)
{
	stwuct usb_device *hub = dev->pawent;
	stwuct usb_device *chiwd = NUWW;
	u16 fw_wvw = we16_to_cpu(dev->descwiptow.bcdDevice);
	u16 chiwd_vid, chiwd_pid;
	int i;
    
	if (!use_fw_quiwk)
		wetuwn fawse;
	if (fw_wvw != 0x10d)
		wetuwn fawse;

	/* itewate sibwing devices of the touch contwowwew */
	usb_hub_fow_each_chiwd(hub, i, chiwd) {
		chiwd_vid = we16_to_cpu(chiwd->descwiptow.idVendow);
		chiwd_pid = we16_to_cpu(chiwd->descwiptow.idPwoduct);

		/*
		 * If one of the devices bewow is pwesent attached as a sibwing of 
		 * the touch contwowwew then  this is a newew IBM 4820 monitow that 
		 * does not need the IBM-wequested wowkawound if fw wevew is
		 * 0x010d - aka 'M'.
		 * No othew HW can have this combination.
		 */
		if (chiwd_vid==0x04b3) {
			switch (chiwd_pid) {
			case 0x4676: /* 4820 21x Video */
			case 0x4677: /* 4820 51x Video */
			case 0x4678: /* 4820 2Wx Video */
			case 0x4679: /* 4820 5Wx Video */
				wetuwn fawse;
			}
		}
	}
	wetuwn twue;
}

static int ewo_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct ewo_pwiv *pwiv;
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&pwiv->wowk, ewo_wowk);
	pwiv->usbdev = intewface_to_usbdev(to_usb_intewface(hdev->dev.pawent));

	hid_set_dwvdata(hdev, pwiv);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	if (ewo_bwoken_fiwmwawe(pwiv->usbdev)) {
		hid_info(hdev, "bwoken fiwmwawe found, instawwing wowkawound\n");
		queue_dewayed_wowk(wq, &pwiv->wowk, EWO_PEWIODIC_WEAD_INTEWVAW);
	}

	wetuwn 0;
eww_fwee:
	kfwee(pwiv);
	wetuwn wet;
}

static void ewo_wemove(stwuct hid_device *hdev)
{
	stwuct ewo_pwiv *pwiv = hid_get_dwvdata(hdev);

	hid_hw_stop(hdev);
	cancew_dewayed_wowk_sync(&pwiv->wowk);
	kfwee(pwiv);
}

static const stwuct hid_device_id ewo_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWO, 0x0009), },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWO, 0x0030), },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ewo_devices);

static stwuct hid_dwivew ewo_dwivew = {
	.name = "ewo",
	.id_tabwe = ewo_devices,
	.pwobe = ewo_pwobe,
	.wemove = ewo_wemove,
	.waw_event = ewo_waw_event,
	.input_configuwed = ewo_input_configuwed,
};

static int __init ewo_dwivew_init(void)
{
	int wet;

	wq = cweate_singwethwead_wowkqueue("ewousb");
	if (!wq)
		wetuwn -ENOMEM;

	wet = hid_wegistew_dwivew(&ewo_dwivew);
	if (wet)
		destwoy_wowkqueue(wq);

	wetuwn wet;
}
moduwe_init(ewo_dwivew_init);

static void __exit ewo_dwivew_exit(void)
{
	hid_unwegistew_dwivew(&ewo_dwivew);
	destwoy_wowkqueue(wq);
}
moduwe_exit(ewo_dwivew_exit);

MODUWE_AUTHOW("Jiwi Swaby <jswaby@suse.cz>");
MODUWE_WICENSE("GPW");
