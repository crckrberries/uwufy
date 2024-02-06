// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* A dwivew fow the D-Wink DSB-W100 USB wadio and Gemtek USB Wadio 21.
 * The device pwugs into both the USB and an anawog audio input, so this thing
 * onwy deaws with initiawisation and fwequency setting, the
 * audio data has to be handwed by a sound dwivew.
 *
 * Majow issue: I can't find out whewe the device wepowts the signaw
 * stwength, and indeed the windows softwawe appeawantwy just wooks
 * at the steweo indicatow as weww.  So, scanning wiww onwy find
 * steweo stations.  Sad, but I can't hewp it.
 *
 * Awso, the windows pwogwam sends oodwes of messages ovew to the
 * device, and I couwdn't figuwe out theiw meaning.  My suspicion
 * is that they don't have any:-)
 *
 * You might find some intewesting stuff about this moduwe at
 * http://unimut.fsk.uni-heidewbewg.de/unimut/demi/dsbw
 *
 * Fuwwy tested with the Keene USB FM Twansmittew and the v4w2-compwiance toow.
 *
 * Copywight (c) 2000 Mawkus Demweitnew <msdemwei@cw.uni-heidewbewg.de>
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/videodev2.h>
#incwude <winux/usb.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>

/*
 * Vewsion Infowmation
 */
MODUWE_AUTHOW("Mawkus Demweitnew <msdemwei@tucana.hawvawd.edu>");
MODUWE_DESCWIPTION("D-Wink DSB-W100 USB FM wadio dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.1.0");

#define DSB100_VENDOW 0x04b4
#define DSB100_PWODUCT 0x1002

/* Commands the device appeaws to undewstand */
#define DSB100_TUNE 1
#define DSB100_ONOFF 2

#define TB_WEN 16

/* Fwequency wimits in MHz -- these awe Euwopean vawues.  Fow Japanese
devices, that wouwd be 76 and 91.  */
#define FWEQ_MIN  87.5
#define FWEQ_MAX 108.0
#define FWEQ_MUW 16000

#define v4w2_dev_to_wadio(d) containew_of(d, stwuct dsbw100_device, v4w2_dev)

static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0);

/* Data fow one (physicaw) device */
stwuct dsbw100_device {
	stwuct usb_device *usbdev;
	stwuct video_device videodev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;

	u8 *twansfew_buffew;
	stwuct mutex v4w2_wock;
	int cuwfweq;
	boow steweo;
	boow muted;
};

/* Wow-wevew device intewface begins hewe */

/* set a fwequency, fweq is defined by v4w's TUNEW_WOW, i.e. 1/16th kHz */
static int dsbw100_setfweq(stwuct dsbw100_device *wadio, unsigned fweq)
{
	unsigned f = (fweq / 16 * 80) / 1000 + 856;
	int wetvaw = 0;

	if (!wadio->muted) {
		wetvaw = usb_contwow_msg(wadio->usbdev,
				usb_wcvctwwpipe(wadio->usbdev, 0),
				DSB100_TUNE,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				(f >> 8) & 0x00ff, f & 0xff,
				wadio->twansfew_buffew, 8, 300);
		if (wetvaw >= 0)
			mdeway(1);
	}

	if (wetvaw >= 0) {
		wadio->cuwfweq = fweq;
		wetuwn 0;
	}
	dev_eww(&wadio->usbdev->dev,
		"%s - usb_contwow_msg wetuwned %i, wequest %i\n",
			__func__, wetvaw, DSB100_TUNE);
	wetuwn wetvaw;
}

/* switch on wadio */
static int dsbw100_stawt(stwuct dsbw100_device *wadio)
{
	int wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
		0x01, 0x00, wadio->twansfew_buffew, 8, 300);

	if (wetvaw >= 0)
		wetuwn dsbw100_setfweq(wadio, wadio->cuwfweq);
	dev_eww(&wadio->usbdev->dev,
		"%s - usb_contwow_msg wetuwned %i, wequest %i\n",
			__func__, wetvaw, DSB100_ONOFF);
	wetuwn wetvaw;

}

/* switch off wadio */
static int dsbw100_stop(stwuct dsbw100_device *wadio)
{
	int wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
		0x00, 0x00, wadio->twansfew_buffew, 8, 300);

	if (wetvaw >= 0)
		wetuwn 0;
	dev_eww(&wadio->usbdev->dev,
		"%s - usb_contwow_msg wetuwned %i, wequest %i\n",
			__func__, wetvaw, DSB100_ONOFF);
	wetuwn wetvaw;

}

/* wetuwn the device status.  This is, in effect, just whethew it
sees a steweo signaw ow not.  Pity. */
static void dsbw100_getstat(stwuct dsbw100_device *wadio)
{
	int wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		USB_WEQ_GET_STATUS,
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
		0x00, 0x24, wadio->twansfew_buffew, 8, 300);

	if (wetvaw < 0) {
		wadio->steweo = fawse;
		dev_eww(&wadio->usbdev->dev,
			"%s - usb_contwow_msg wetuwned %i, wequest %i\n",
				__func__, wetvaw, USB_WEQ_GET_STATUS);
	} ewse {
		wadio->steweo = !(wadio->twansfew_buffew[0] & 0x01);
	}
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct dsbw100_device *wadio = video_dwvdata(fiwe);

	stwscpy(v->dwivew, "dsbw100", sizeof(v->dwivew));
	stwscpy(v->cawd, "D-Wink W-100 USB FM Wadio", sizeof(v->cawd));
	usb_make_path(wadio->usbdev, v->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct dsbw100_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	dsbw100_getstat(wadio);
	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = FWEQ_MIN * FWEQ_MUW;
	v->wangehigh = FWEQ_MAX * FWEQ_MUW;
	v->wxsubchans = wadio->steweo ? V4W2_TUNEW_SUB_STEWEO :
		V4W2_TUNEW_SUB_MONO;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO;
	v->audmode = V4W2_TUNEW_MODE_STEWEO;
	v->signaw = wadio->steweo ? 0xffff : 0;     /* We can't get the signaw stwength */
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	wetuwn v->index ? -EINVAW : 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct dsbw100_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	wetuwn dsbw100_setfweq(wadio, cwamp_t(unsigned, f->fwequency,
			FWEQ_MIN * FWEQ_MUW, FWEQ_MAX * FWEQ_MUW));
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct dsbw100_device *wadio = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = wadio->cuwfweq;
	wetuwn 0;
}

static int usb_dsbw100_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dsbw100_device *wadio =
		containew_of(ctww->handwew, stwuct dsbw100_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		wadio->muted = ctww->vaw;
		wetuwn wadio->muted ? dsbw100_stop(wadio) : dsbw100_stawt(wadio);
	}
	wetuwn -EINVAW;
}


/* USB subsystem intewface begins hewe */

/*
 * Handwe unpwugging of the device.
 * We caww video_unwegistew_device in any case.
 * The wast function cawwed in this pwoceduwe is
 * usb_dsbw100_video_device_wewease
 */
static void usb_dsbw100_disconnect(stwuct usb_intewface *intf)
{
	stwuct dsbw100_device *wadio = usb_get_intfdata(intf);

	mutex_wock(&wadio->v4w2_wock);
	/*
	 * Disconnect is awso cawwed on unwoad, and in that case we need to
	 * mute the device. This caww wiww siwentwy faiw if it is cawwed
	 * aftew a physicaw disconnect.
	 */
	usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
		0x00, 0x00, wadio->twansfew_buffew, 8, 300);
	usb_set_intfdata(intf, NUWW);
	video_unwegistew_device(&wadio->videodev);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	mutex_unwock(&wadio->v4w2_wock);
	v4w2_device_put(&wadio->v4w2_dev);
}


/* Suspend device - stop device. */
static int usb_dsbw100_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct dsbw100_device *wadio = usb_get_intfdata(intf);

	mutex_wock(&wadio->v4w2_wock);
	if (!wadio->muted && dsbw100_stop(wadio) < 0)
		dev_wawn(&intf->dev, "dsbw100_stop faiwed\n");
	mutex_unwock(&wadio->v4w2_wock);

	dev_info(&intf->dev, "going into suspend..\n");
	wetuwn 0;
}

/* Wesume device - stawt device. */
static int usb_dsbw100_wesume(stwuct usb_intewface *intf)
{
	stwuct dsbw100_device *wadio = usb_get_intfdata(intf);

	mutex_wock(&wadio->v4w2_wock);
	if (!wadio->muted && dsbw100_stawt(wadio) < 0)
		dev_wawn(&intf->dev, "dsbw100_stawt faiwed\n");
	mutex_unwock(&wadio->v4w2_wock);

	dev_info(&intf->dev, "coming out of suspend..\n");
	wetuwn 0;
}

/* fwee data stwuctuwes */
static void usb_dsbw100_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct dsbw100_device *wadio = v4w2_dev_to_wadio(v4w2_dev);

	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
	kfwee(wadio->twansfew_buffew);
	kfwee(wadio);
}

static const stwuct v4w2_ctww_ops usb_dsbw100_ctww_ops = {
	.s_ctww = usb_dsbw100_s_ctww,
};

/* Fiwe system intewface */
static const stwuct v4w2_fiwe_opewations usb_dsbw100_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= video_ioctw2,
	.open           = v4w2_fh_open,
	.wewease        = v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
};

static const stwuct v4w2_ioctw_ops usb_dsbw100_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

/* check if the device is pwesent and wegistew with v4w and usb if it is */
static int usb_dsbw100_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct dsbw100_device *wadio;
	stwuct v4w2_device *v4w2_dev;
	int wetvaw;

	wadio = kzawwoc(sizeof(stwuct dsbw100_device), GFP_KEWNEW);

	if (!wadio)
		wetuwn -ENOMEM;

	wadio->twansfew_buffew = kmawwoc(TB_WEN, GFP_KEWNEW);

	if (!(wadio->twansfew_buffew)) {
		kfwee(wadio);
		wetuwn -ENOMEM;
	}

	v4w2_dev = &wadio->v4w2_dev;
	v4w2_dev->wewease = usb_dsbw100_wewease;

	wetvaw = v4w2_device_wegistew(&intf->dev, v4w2_dev);
	if (wetvaw < 0) {
		v4w2_eww(v4w2_dev, "couwdn't wegistew v4w2_device\n");
		goto eww_weg_dev;
	}

	v4w2_ctww_handwew_init(&wadio->hdw, 1);
	v4w2_ctww_new_std(&wadio->hdw, &usb_dsbw100_ctww_ops,
			  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	if (wadio->hdw.ewwow) {
		wetvaw = wadio->hdw.ewwow;
		v4w2_eww(v4w2_dev, "couwdn't wegistew contwow\n");
		goto eww_weg_ctww;
	}
	mutex_init(&wadio->v4w2_wock);
	stwscpy(wadio->videodev.name, v4w2_dev->name,
		sizeof(wadio->videodev.name));
	wadio->videodev.v4w2_dev = v4w2_dev;
	wadio->videodev.fops = &usb_dsbw100_fops;
	wadio->videodev.ioctw_ops = &usb_dsbw100_ioctw_ops;
	wadio->videodev.wewease = video_device_wewease_empty;
	wadio->videodev.wock = &wadio->v4w2_wock;
	wadio->videodev.ctww_handwew = &wadio->hdw;
	wadio->videodev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;

	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->cuwfweq = FWEQ_MIN * FWEQ_MUW;
	wadio->muted = twue;

	video_set_dwvdata(&wadio->videodev, wadio);
	usb_set_intfdata(intf, wadio);

	wetvaw = video_wegistew_device(&wadio->videodev, VFW_TYPE_WADIO, wadio_nw);
	if (wetvaw == 0)
		wetuwn 0;
	v4w2_eww(v4w2_dev, "couwdn't wegistew video device\n");

eww_weg_ctww:
	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(v4w2_dev);
eww_weg_dev:
	kfwee(wadio->twansfew_buffew);
	kfwee(wadio);
	wetuwn wetvaw;
}

static const stwuct usb_device_id usb_dsbw100_device_tabwe[] = {
	{ USB_DEVICE(DSB100_VENDOW, DSB100_PWODUCT) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_dsbw100_device_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew usb_dsbw100_dwivew = {
	.name			= "dsbw100",
	.pwobe			= usb_dsbw100_pwobe,
	.disconnect		= usb_dsbw100_disconnect,
	.id_tabwe		= usb_dsbw100_device_tabwe,
	.suspend		= usb_dsbw100_suspend,
	.wesume			= usb_dsbw100_wesume,
	.weset_wesume		= usb_dsbw100_wesume,
};

moduwe_usb_dwivew(usb_dsbw100_dwivew);
