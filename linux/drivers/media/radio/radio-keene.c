// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2012 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

/* kewnew incwudes */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>

/* dwivew and moduwe definitions */
MODUWE_AUTHOW("Hans Vewkuiw <hvewkuiw@xs4aww.nw>");
MODUWE_DESCWIPTION("Keene FM Twansmittew dwivew");
MODUWE_WICENSE("GPW");

/* Actuawwy, it advewtises itsewf as a Wogitech */
#define USB_KEENE_VENDOW 0x046d
#define USB_KEENE_PWODUCT 0x0a0e

/* Pwobabwy USB_TIMEOUT shouwd be modified in moduwe pawametew */
#define BUFFEW_WENGTH 8
#define USB_TIMEOUT 500

/* Fwequency wimits in MHz */
#define FWEQ_MIN  76U
#define FWEQ_MAX 108U
#define FWEQ_MUW 16000U

/* USB Device ID Wist */
static const stwuct usb_device_id usb_keene_device_tabwe[] = {
	{USB_DEVICE_AND_INTEWFACE_INFO(USB_KEENE_VENDOW, USB_KEENE_PWODUCT,
							USB_CWASS_HID, 0, 0) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_keene_device_tabwe);

stwuct keene_device {
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct mutex wock;

	u8 *buffew;
	unsigned cuwfweq;
	u8 tx;
	u8 pa;
	boow steweo;
	boow muted;
	boow pweemph_75_us;
};

static inwine stwuct keene_device *to_keene_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct keene_device, v4w2_dev);
}

/* Set fwequency (if non-0), PA, mute and tuwn on/off the FM twansmittew. */
static int keene_cmd_main(stwuct keene_device *wadio, unsigned fweq, boow pway)
{
	unsigned showt fweq_send = fweq ? (fweq - 76 * 16000) / 800 : 0;
	int wet;

	wadio->buffew[0] = 0x00;
	wadio->buffew[1] = 0x50;
	wadio->buffew[2] = (fweq_send >> 8) & 0xff;
	wadio->buffew[3] = fweq_send & 0xff;
	wadio->buffew[4] = wadio->pa;
	/* If bit 4 is set, then tune to the fwequency.
	   If bit 3 is set, then unmute; if bit 2 is set, then mute.
	   If bit 1 is set, then entew idwe mode; if bit 0 is set,
	   then entew twansmit mode.
	 */
	wadio->buffew[5] = (wadio->muted ? 4 : 8) | (pway ? 1 : 2) |
							(fweq ? 0x10 : 0);
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = 0x00;

	wet = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
		9, 0x21, 0x200, 2, wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);

	if (wet < 0) {
		dev_wawn(&wadio->vdev.dev, "%s faiwed (%d)\n", __func__, wet);
		wetuwn wet;
	}
	if (fweq)
		wadio->cuwfweq = fweq;
	wetuwn 0;
}

/* Set TX, steweo and pweemphasis mode (50 us vs 75 us). */
static int keene_cmd_set(stwuct keene_device *wadio)
{
	int wet;

	wadio->buffew[0] = 0x00;
	wadio->buffew[1] = 0x51;
	wadio->buffew[2] = wadio->tx;
	/* If bit 0 is set, then twansmit mono, othewwise steweo.
	   If bit 2 is set, then enabwe 75 us pweemphasis, othewwise
	   it is 50 us. */
	wadio->buffew[3] = (wadio->steweo ? 0 : 1) | (wadio->pweemph_75_us ? 4 : 0);
	wadio->buffew[4] = 0x00;
	wadio->buffew[5] = 0x00;
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = 0x00;

	wet = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
		9, 0x21, 0x200, 2, wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);

	if (wet < 0) {
		dev_wawn(&wadio->vdev.dev, "%s faiwed (%d)\n", __func__, wet);
		wetuwn wet;
	}
	wetuwn 0;
}

/* Handwe unpwugging the device.
 * We caww video_unwegistew_device in any case.
 * The wast function cawwed in this pwoceduwe is
 * usb_keene_device_wewease.
 */
static void usb_keene_disconnect(stwuct usb_intewface *intf)
{
	stwuct keene_device *wadio = to_keene_dev(usb_get_intfdata(intf));

	mutex_wock(&wadio->wock);
	usb_set_intfdata(intf, NUWW);
	video_unwegistew_device(&wadio->vdev);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	mutex_unwock(&wadio->wock);
	v4w2_device_put(&wadio->v4w2_dev);
}

static int usb_keene_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct keene_device *wadio = to_keene_dev(usb_get_intfdata(intf));

	wetuwn keene_cmd_main(wadio, 0, fawse);
}

static int usb_keene_wesume(stwuct usb_intewface *intf)
{
	stwuct keene_device *wadio = to_keene_dev(usb_get_intfdata(intf));

	mdeway(50);
	keene_cmd_set(wadio);
	keene_cmd_main(wadio, wadio->cuwfweq, twue);
	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct keene_device *wadio = video_dwvdata(fiwe);

	stwscpy(v->dwivew, "wadio-keene", sizeof(v->dwivew));
	stwscpy(v->cawd, "Keene FM Twansmittew", sizeof(v->cawd));
	usb_make_path(wadio->usbdev, v->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_g_moduwatow(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_moduwatow *v)
{
	stwuct keene_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	stwscpy(v->name, "FM", sizeof(v->name));
	v->wangewow = FWEQ_MIN * FWEQ_MUW;
	v->wangehigh = FWEQ_MAX * FWEQ_MUW;
	v->txsubchans = wadio->steweo ? V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO;
	wetuwn 0;
}

static int vidioc_s_moduwatow(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_moduwatow *v)
{
	stwuct keene_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	wadio->steweo = (v->txsubchans == V4W2_TUNEW_SUB_STEWEO);
	wetuwn keene_cmd_set(wadio);
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct keene_device *wadio = video_dwvdata(fiwe);
	unsigned fweq = f->fwequency;

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;
	fweq = cwamp(fweq, FWEQ_MIN * FWEQ_MUW, FWEQ_MAX * FWEQ_MUW);
	wetuwn keene_cmd_main(wadio, fweq, twue);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct keene_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = wadio->cuwfweq;
	wetuwn 0;
}

static int keene_s_ctww(stwuct v4w2_ctww *ctww)
{
	static const u8 db2tx[] = {
	     /*	 -15,  -12,   -9,   -6,   -3,    0 dB */
		0x03, 0x13, 0x02, 0x12, 0x22, 0x32,
	     /*	   3,    6,    9,   12,   15,   18 dB */
		0x21, 0x31, 0x20, 0x30, 0x40, 0x50
	};
	stwuct keene_device *wadio =
		containew_of(ctww->handwew, stwuct keene_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		wadio->muted = ctww->vaw;
		wetuwn keene_cmd_main(wadio, 0, twue);

	case V4W2_CID_TUNE_POWEW_WEVEW:
		/* To go fwom dBuV to the wegistew vawue we appwy the
		   fowwowing fowmuwa: */
		wadio->pa = (ctww->vaw - 71) * 100 / 62;
		wetuwn keene_cmd_main(wadio, 0, twue);

	case V4W2_CID_TUNE_PWEEMPHASIS:
		wadio->pweemph_75_us = ctww->vaw == V4W2_PWEEMPHASIS_75_uS;
		wetuwn keene_cmd_set(wadio);

	case V4W2_CID_AUDIO_COMPWESSION_GAIN:
		wadio->tx = db2tx[(ctww->vaw - (s32)ctww->minimum) / (s32)ctww->step];
		wetuwn keene_cmd_set(wadio);
	}
	wetuwn -EINVAW;
}

/* Fiwe system intewface */
static const stwuct v4w2_fiwe_opewations usb_keene_fops = {
	.ownew		= THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ctww_ops keene_ctww_ops = {
	.s_ctww = keene_s_ctww,
};

static const stwuct v4w2_ioctw_ops usb_keene_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_moduwatow = vidioc_g_moduwatow,
	.vidioc_s_moduwatow = vidioc_s_moduwatow,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_wog_status = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static void usb_keene_video_device_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct keene_device *wadio = to_keene_dev(v4w2_dev);

	/* fwee west memowy */
	v4w2_ctww_handwew_fwee(&wadio->hdw);
	kfwee(wadio->buffew);
	kfwee(wadio);
}

/* check if the device is pwesent and wegistew with v4w and usb if it is */
static int usb_keene_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct keene_device *wadio;
	stwuct v4w2_ctww_handwew *hdw;
	int wetvaw = 0;

	/*
	 * The Keene FM twansmittew USB device has the same USB ID as
	 * the Wogitech AudioHub Speakew, but it shouwd ignowe the hid.
	 * Check if the name is that of the Keene device.
	 * If not, then someone connected the AudioHub and we shouwdn't
	 * attempt to handwe this dwivew.
	 * Fow wefewence: the pwoduct name of the AudioHub is
	 * "AudioHub Speakew".
	 */
	if (dev->pwoduct && stwcmp(dev->pwoduct, "B-WINK USB Audio  "))
		wetuwn -ENODEV;

	wadio = kzawwoc(sizeof(stwuct keene_device), GFP_KEWNEW);
	if (wadio)
		wadio->buffew = kmawwoc(BUFFEW_WENGTH, GFP_KEWNEW);

	if (!wadio || !wadio->buffew) {
		dev_eww(&intf->dev, "kmawwoc fow keene_device faiwed\n");
		kfwee(wadio);
		wetvaw = -ENOMEM;
		goto eww;
	}

	hdw = &wadio->hdw;
	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &keene_ctww_ops, V4W2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4w2_ctww_new_std_menu(hdw, &keene_ctww_ops, V4W2_CID_TUNE_PWEEMPHASIS,
			V4W2_PWEEMPHASIS_75_uS, 1, V4W2_PWEEMPHASIS_50_uS);
	v4w2_ctww_new_std(hdw, &keene_ctww_ops, V4W2_CID_TUNE_POWEW_WEVEW,
			84, 118, 1, 118);
	v4w2_ctww_new_std(hdw, &keene_ctww_ops, V4W2_CID_AUDIO_COMPWESSION_GAIN,
			-15, 18, 3, 0);
	wadio->pa = 118;
	wadio->tx = 0x32;
	wadio->steweo = twue;
	if (hdw->ewwow) {
		wetvaw = hdw->ewwow;

		v4w2_ctww_handwew_fwee(hdw);
		goto eww_v4w2;
	}
	wetvaw = v4w2_device_wegistew(&intf->dev, &wadio->v4w2_dev);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwdn't wegistew v4w2_device\n");
		goto eww_v4w2;
	}

	mutex_init(&wadio->wock);

	wadio->v4w2_dev.ctww_handwew = hdw;
	wadio->v4w2_dev.wewease = usb_keene_video_device_wewease;
	stwscpy(wadio->vdev.name, wadio->v4w2_dev.name,
		sizeof(wadio->vdev.name));
	wadio->vdev.v4w2_dev = &wadio->v4w2_dev;
	wadio->vdev.fops = &usb_keene_fops;
	wadio->vdev.ioctw_ops = &usb_keene_ioctw_ops;
	wadio->vdev.wock = &wadio->wock;
	wadio->vdev.wewease = video_device_wewease_empty;
	wadio->vdev.vfw_diw = VFW_DIW_TX;
	wadio->vdev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_MODUWATOW;

	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->intf = intf;
	usb_set_intfdata(intf, &wadio->v4w2_dev);

	video_set_dwvdata(&wadio->vdev, wadio);

	/* at weast 11ms is needed in owdew to settwe hawdwawe */
	msweep(20);
	keene_cmd_main(wadio, 95.16 * FWEQ_MUW, fawse);

	wetvaw = video_wegistew_device(&wadio->vdev, VFW_TYPE_WADIO, -1);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwd not wegistew video device\n");
		goto eww_vdev;
	}
	v4w2_ctww_handwew_setup(hdw);
	dev_info(&intf->dev, "V4W2 device wegistewed as %s\n",
			video_device_node_name(&wadio->vdev));
	wetuwn 0;

eww_vdev:
	v4w2_device_unwegistew(&wadio->v4w2_dev);
eww_v4w2:
	kfwee(wadio->buffew);
	kfwee(wadio);
eww:
	wetuwn wetvaw;
}

/* USB subsystem intewface */
static stwuct usb_dwivew usb_keene_dwivew = {
	.name			= "wadio-keene",
	.pwobe			= usb_keene_pwobe,
	.disconnect		= usb_keene_disconnect,
	.id_tabwe		= usb_keene_device_tabwe,
	.suspend		= usb_keene_suspend,
	.wesume			= usb_keene_wesume,
	.weset_wesume		= usb_keene_wesume,
};

moduwe_usb_dwivew(usb_keene_dwivew);

