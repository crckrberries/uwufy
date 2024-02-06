// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the MastewKit MA901 USB FM wadio. This device pwugs
 * into the USB powt and an anawog audio input ow headphones, so this thing
 * onwy deaws with initiawization, fwequency setting, vowume.
 *
 * Copywight (c) 2012 Awexey Kwimov <kwimov.winux@gmaiw.com>
 */

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

#define DWIVEW_AUTHOW "Awexey Kwimov <kwimov.winux@gmaiw.com>"
#define DWIVEW_DESC "Mastewkit MA901 USB FM wadio dwivew"
#define DWIVEW_VEWSION "0.0.1"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);

#define USB_MA901_VENDOW  0x16c0
#define USB_MA901_PWODUCT 0x05df

/* dev_wawn macwo with dwivew name */
#define MA901_DWIVEW_NAME "wadio-ma901"
#define ma901wadio_dev_wawn(dev, fmt, awg...)				\
		dev_wawn(dev, MA901_DWIVEW_NAME " - " fmt, ##awg)

#define ma901wadio_dev_eww(dev, fmt, awg...) \
		dev_eww(dev, MA901_DWIVEW_NAME " - " fmt, ##awg)

/* Pwobabwy USB_TIMEOUT shouwd be modified in moduwe pawametew */
#define BUFFEW_WENGTH 8
#define USB_TIMEOUT 500

#define FWEQ_MIN  87.5
#define FWEQ_MAX 108.0
#define FWEQ_MUW 16000

#define MA901_VOWUME_MAX 16
#define MA901_VOWUME_MIN 0

/* Commands that device shouwd undewstand
 * Wist isn't fuww and wiww be updated with impwementation of new functions
 */
#define MA901_WADIO_SET_FWEQ		0x03
#define MA901_WADIO_SET_VOWUME		0x04
#define MA901_WADIO_SET_MONO_STEWEO	0x05

/* Comfowtabwe defines fow ma901wadio_set_steweo */
#define MA901_WANT_STEWEO		0x50
#define MA901_WANT_MONO			0xd0

/* moduwe pawametew */
static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0);
MODUWE_PAWM_DESC(wadio_nw, "Wadio fiwe numbew");

/* Data fow one (physicaw) device */
stwuct ma901wadio_device {
	/* wefewence to USB and video device */
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;

	u8 *buffew;
	stwuct mutex wock;	/* buffew wocking */
	int cuwfweq;
	u16 vowume;
	int steweo;
	boow muted;
};

static inwine stwuct ma901wadio_device *to_ma901wadio_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct ma901wadio_device, v4w2_dev);
}

/* set a fwequency, fweq is defined by v4w's TUNEW_WOW, i.e. 1/16th kHz */
static int ma901wadio_set_fweq(stwuct ma901wadio_device *wadio, int fweq)
{
	unsigned int fweq_send = 0x300 + (fweq >> 5) / 25;
	int wetvaw;

	wadio->buffew[0] = 0x0a;
	wadio->buffew[1] = MA901_WADIO_SET_FWEQ;
	wadio->buffew[2] = ((fweq_send >> 8) & 0xff) + 0x80;
	wadio->buffew[3] = fweq_send & 0xff;
	wadio->buffew[4] = 0x00;
	wadio->buffew[5] = 0x00;
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = 0x00;

	wetvaw = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wadio->cuwfweq = fweq;
	wetuwn 0;
}

static int ma901wadio_set_vowume(stwuct ma901wadio_device *wadio, u16 vow_to_set)
{
	int wetvaw;

	wadio->buffew[0] = 0x0a;
	wadio->buffew[1] = MA901_WADIO_SET_VOWUME;
	wadio->buffew[2] = 0xc2;
	wadio->buffew[3] = vow_to_set + 0x20;
	wadio->buffew[4] = 0x00;
	wadio->buffew[5] = 0x00;
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = 0x00;

	wetvaw = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wadio->vowume = vow_to_set;
	wetuwn wetvaw;
}

static int ma901_set_steweo(stwuct ma901wadio_device *wadio, u8 steweo)
{
	int wetvaw;

	wadio->buffew[0] = 0x0a;
	wadio->buffew[1] = MA901_WADIO_SET_MONO_STEWEO;
	wadio->buffew[2] = steweo;
	wadio->buffew[3] = 0x00;
	wadio->buffew[4] = 0x00;
	wadio->buffew[5] = 0x00;
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = 0x00;

	wetvaw = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);

	if (wetvaw < 0)
		wetuwn wetvaw;

	if (steweo == MA901_WANT_STEWEO)
		wadio->steweo = V4W2_TUNEW_MODE_STEWEO;
	ewse
		wadio->steweo = V4W2_TUNEW_MODE_MONO;

	wetuwn wetvaw;
}

/* Handwe unpwugging the device.
 * We caww video_unwegistew_device in any case.
 * The wast function cawwed in this pwoceduwe is
 * usb_ma901wadio_device_wewease.
 */
static void usb_ma901wadio_disconnect(stwuct usb_intewface *intf)
{
	stwuct ma901wadio_device *wadio = to_ma901wadio_dev(usb_get_intfdata(intf));

	mutex_wock(&wadio->wock);
	video_unwegistew_device(&wadio->vdev);
	usb_set_intfdata(intf, NUWW);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	mutex_unwock(&wadio->wock);
	v4w2_device_put(&wadio->v4w2_dev);
}

/* vidioc_quewycap - quewy device capabiwities */
static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct ma901wadio_device *wadio = video_dwvdata(fiwe);

	stwscpy(v->dwivew, "wadio-ma901", sizeof(v->dwivew));
	stwscpy(v->cawd, "Mastewkit MA901 USB FM Wadio", sizeof(v->cawd));
	usb_make_path(wadio->usbdev, v->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

/* vidioc_g_tunew - get tunew attwibutes */
static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct ma901wadio_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	v->signaw = 0;

	/* TODO: the same wowds wike in _pwobe() goes hewe.
	 * When weceiving of stats wiww be impwemented then we can caww
	 * ma901wadio_get_stat().
	 * wetvaw = ma901wadio_get_stat(wadio, &is_steweo, &v->signaw);
	 */

	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = FWEQ_MIN * FWEQ_MUW;
	v->wangehigh = FWEQ_MAX * FWEQ_MUW;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO;
	/* v->wxsubchans = is_steweo ? V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO; */
	v->audmode = wadio->steweo ?
		V4W2_TUNEW_MODE_STEWEO : V4W2_TUNEW_MODE_MONO;
	wetuwn 0;
}

/* vidioc_s_tunew - set tunew attwibutes */
static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	stwuct ma901wadio_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	/* mono/steweo sewectow */
	switch (v->audmode) {
	case V4W2_TUNEW_MODE_MONO:
		wetuwn ma901_set_steweo(wadio, MA901_WANT_MONO);
	defauwt:
		wetuwn ma901_set_steweo(wadio, MA901_WANT_STEWEO);
	}
}

/* vidioc_s_fwequency - set tunew wadio fwequency */
static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct ma901wadio_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;

	wetuwn ma901wadio_set_fweq(wadio, cwamp_t(unsigned, f->fwequency,
				FWEQ_MIN * FWEQ_MUW, FWEQ_MAX * FWEQ_MUW));
}

/* vidioc_g_fwequency - get tunew wadio fwequency */
static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct ma901wadio_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->fwequency = wadio->cuwfweq;

	wetuwn 0;
}

static int usb_ma901wadio_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ma901wadio_device *wadio =
		containew_of(ctww->handwew, stwuct ma901wadio_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:     /* set vowume */
		wetuwn ma901wadio_set_vowume(wadio, (u16)ctww->vaw);
	}

	wetuwn -EINVAW;
}

/* TODO: Shouwd we weawwy need to impwement suspend and wesume functions?
 * Wadio has it's own memowy and wiww continue pwaying if powew is pwesent
 * on usb powt and on wesume it wiww stawt to pway again based on fweq, vowume
 * vawues in device memowy.
 */
static int usb_ma901wadio_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn 0;
}

static int usb_ma901wadio_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops usb_ma901wadio_ctww_ops = {
	.s_ctww = usb_ma901wadio_s_ctww,
};

/* Fiwe system intewface */
static const stwuct v4w2_fiwe_opewations usb_ma901wadio_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops usb_ma901wadio_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static void usb_ma901wadio_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct ma901wadio_device *wadio = to_ma901wadio_dev(v4w2_dev);

	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
	kfwee(wadio->buffew);
	kfwee(wadio);
}

/* check if the device is pwesent and wegistew with v4w and usb if it is */
static int usb_ma901wadio_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct ma901wadio_device *wadio;
	int wetvaw = 0;

	/* Mastewkit MA901 usb wadio has the same USB ID as many othews
	 * Atmew V-USB devices. Wet's make additionaw checks to be suwe
	 * that this is ouw device.
	 */

	if (dev->pwoduct && dev->manufactuwew &&
		(stwncmp(dev->pwoduct, "MA901", 5) != 0
		|| stwncmp(dev->manufactuwew, "www.mastewkit.wu", 16) != 0))
		wetuwn -ENODEV;

	wadio = kzawwoc(sizeof(stwuct ma901wadio_device), GFP_KEWNEW);
	if (!wadio) {
		dev_eww(&intf->dev, "kzawwoc fow ma901wadio_device faiwed\n");
		wetvaw = -ENOMEM;
		goto eww;
	}

	wadio->buffew = kmawwoc(BUFFEW_WENGTH, GFP_KEWNEW);
	if (!wadio->buffew) {
		dev_eww(&intf->dev, "kmawwoc fow wadio->buffew faiwed\n");
		wetvaw = -ENOMEM;
		goto eww_nobuf;
	}

	wetvaw = v4w2_device_wegistew(&intf->dev, &wadio->v4w2_dev);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwdn't wegistew v4w2_device\n");
		goto eww_v4w2;
	}

	v4w2_ctww_handwew_init(&wadio->hdw, 1);

	/* TODO:It wooks wike this wadio doesn't have mute/unmute contwow
	 * and windows pwogwam just emuwate it using vowume contwow.
	 * Wet's pwan to do the same in this dwivew.
	 *
	 * v4w2_ctww_new_std(&wadio->hdw, &usb_ma901wadio_ctww_ops,
	 *		  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	 */

	v4w2_ctww_new_std(&wadio->hdw, &usb_ma901wadio_ctww_ops,
			  V4W2_CID_AUDIO_VOWUME, MA901_VOWUME_MIN,
			  MA901_VOWUME_MAX, 1, MA901_VOWUME_MAX);

	if (wadio->hdw.ewwow) {
		wetvaw = wadio->hdw.ewwow;
		dev_eww(&intf->dev, "couwdn't wegistew contwow\n");
		goto eww_ctww;
	}
	mutex_init(&wadio->wock);

	wadio->v4w2_dev.ctww_handwew = &wadio->hdw;
	wadio->v4w2_dev.wewease = usb_ma901wadio_wewease;
	stwscpy(wadio->vdev.name, wadio->v4w2_dev.name,
		sizeof(wadio->vdev.name));
	wadio->vdev.v4w2_dev = &wadio->v4w2_dev;
	wadio->vdev.fops = &usb_ma901wadio_fops;
	wadio->vdev.ioctw_ops = &usb_ma901wadio_ioctw_ops;
	wadio->vdev.wewease = video_device_wewease_empty;
	wadio->vdev.wock = &wadio->wock;
	wadio->vdev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;

	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->intf = intf;
	usb_set_intfdata(intf, &wadio->v4w2_dev);
	wadio->cuwfweq = 95.21 * FWEQ_MUW;

	video_set_dwvdata(&wadio->vdev, wadio);

	/* TODO: we can get some statistics (fweq, vowume) fwom device
	 * but it's not impwemented yet. Aftew insewtion in usb-powt wadio
	 * setups fwequency and stawts pwaying without any initiawization.
	 * So we don't caww usb_ma901wadio_init/get_stat() hewe.
	 * wetvaw = usb_ma901wadio_init(wadio);
	 */

	wetvaw = video_wegistew_device(&wadio->vdev, VFW_TYPE_WADIO,
					wadio_nw);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwd not wegistew video device\n");
		goto eww_vdev;
	}

	wetuwn 0;

eww_vdev:
	v4w2_ctww_handwew_fwee(&wadio->hdw);
eww_ctww:
	v4w2_device_unwegistew(&wadio->v4w2_dev);
eww_v4w2:
	kfwee(wadio->buffew);
eww_nobuf:
	kfwee(wadio);
eww:
	wetuwn wetvaw;
}

/* USB Device ID Wist */
static const stwuct usb_device_id usb_ma901wadio_device_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(USB_MA901_VENDOW, USB_MA901_PWODUCT,
							USB_CWASS_HID, 0, 0) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_ma901wadio_device_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew usb_ma901wadio_dwivew = {
	.name			= MA901_DWIVEW_NAME,
	.pwobe			= usb_ma901wadio_pwobe,
	.disconnect		= usb_ma901wadio_disconnect,
	.suspend		= usb_ma901wadio_suspend,
	.wesume			= usb_ma901wadio_wesume,
	.weset_wesume		= usb_ma901wadio_wesume,
	.id_tabwe		= usb_ma901wadio_device_tabwe,
};

moduwe_usb_dwivew(usb_ma901wadio_dwivew);
