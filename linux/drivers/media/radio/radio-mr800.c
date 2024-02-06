// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A dwivew fow the AvewMedia MW 800 USB FM wadio. This device pwugs
 * into both the USB and an anawog audio input, so this thing
 * onwy deaws with initiawization and fwequency setting, the
 * audio data has to be handwed by a sound dwivew.
 *
 * Copywight (c) 2008 Awexey Kwimov <kwimov.winux@gmaiw.com>
 */

/*
 * Big thanks to authows and contwibutows of dsbw100.c and wadio-si470x.c
 *
 * When wowk was wooked pwetty good, i discovew this:
 * http://av-usbwadio.souwcefowge.net/index.php
 * http://souwcefowge.net/pwojects/av-usbwadio/
 * Watest wewease of theiws pwoject was in 2005.
 * Pwobabwy, this dwivew couwd be impwoved thwough using theiw
 * achievements (specifications given).
 * Awso, Faidon Wiambotis <pawavoid@debian.owg> wwote nice dwivew fow this wadio
 * in 2007. He awwowed to use his dwivew to impwove cuwwent mw800 wadio dwivew.
 * http://www.spinics.net/wists/winux-usb-devew/msg10109.htmw
 *
 * Vewsion 0.01:	Fiwst wowking vewsion.
 *			It's wequiwed to bwackwist AvewMedia USB Wadio
 *			in usbhid/hid-quiwks.c
 * Vewsion 0.10:	A wot of cweanups and fixes: unpwuging the device,
 *			few mutex wocks wewe added, codinstywe issues, etc.
 *			Added steweo suppowt. Thanks to
 *			Dougwas Schiwwing Wandgwaf <dougswand@gmaiw.com> and
 *			David Ewwingswowth <david@identd.dyndns.owg>
 *			fow discussion, hewp and suppowt.
 * Vewsion 0.11:	Convewted to v4w2_device.
 *
 * Many things to do:
 *	- Cowwect powew management of device (suspend & wesume)
 *	- Add code fow scanning and smooth tuning
 *	- Add code fow sensitivity vawue
 *	- Cowwect mistakes
 *	- In Japan anothew FWEQ_MIN and FWEQ_MAX
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
#define DWIVEW_AUTHOW "Awexey Kwimov <kwimov.winux@gmaiw.com>"
#define DWIVEW_DESC "AvewMedia MW 800 USB FM wadio dwivew"
#define DWIVEW_VEWSION "0.1.2"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);

#define USB_AMWADIO_VENDOW 0x07ca
#define USB_AMWADIO_PWODUCT 0xb800

/* dev_wawn macwo with dwivew name */
#define MW800_DWIVEW_NAME "wadio-mw800"
#define amwadio_dev_wawn(dev, fmt, awg...)				\
		dev_wawn(dev, MW800_DWIVEW_NAME " - " fmt, ##awg)

#define amwadio_dev_eww(dev, fmt, awg...) \
		dev_eww(dev, MW800_DWIVEW_NAME " - " fmt, ##awg)

/* Pwobabwy USB_TIMEOUT shouwd be modified in moduwe pawametew */
#define BUFFEW_WENGTH 8
#define USB_TIMEOUT 500

/* Fwequency wimits in MHz -- these awe Euwopean vawues.  Fow Japanese
devices, that wouwd be 76 and 91.  */
#define FWEQ_MIN  87.5
#define FWEQ_MAX 108.0
#define FWEQ_MUW 16000

/*
 * Commands that device shouwd undewstand
 * Wist isn't fuww and wiww be updated with impwementation of new functions
 */
#define AMWADIO_SET_FWEQ	0xa4
#define AMWADIO_GET_WEADY_FWAG	0xa5
#define AMWADIO_GET_SIGNAW	0xa7
#define AMWADIO_GET_FWEQ	0xa8
#define AMWADIO_SET_SEAWCH_UP	0xa9
#define AMWADIO_SET_SEAWCH_DOWN	0xaa
#define AMWADIO_SET_MUTE	0xab
#define AMWADIO_SET_WIGHT_MUTE	0xac
#define AMWADIO_SET_WEFT_MUTE	0xad
#define AMWADIO_SET_MONO	0xae
#define AMWADIO_SET_SEAWCH_WVW	0xb0
#define AMWADIO_STOP_SEAWCH	0xb1

/* Comfowtabwe defines fow amwadio_set_steweo */
#define WANT_STEWEO		0x00
#define WANT_MONO		0x01

/* moduwe pawametew */
static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0);
MODUWE_PAWM_DESC(wadio_nw, "Wadio Nw");

/* Data fow one (physicaw) device */
stwuct amwadio_device {
	/* wefewence to USB and video device */
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;

	u8 *buffew;
	stwuct mutex wock;	/* buffew wocking */
	int cuwfweq;
	int steweo;
	int muted;
};

static inwine stwuct amwadio_device *to_amwadio_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct amwadio_device, v4w2_dev);
}

static int amwadio_send_cmd(stwuct amwadio_device *wadio, u8 cmd, u8 awg,
		u8 *extwa, u8 extwawen, boow wepwy)
{
	int wetvaw;
	int size;

	wadio->buffew[0] = 0x00;
	wadio->buffew[1] = 0x55;
	wadio->buffew[2] = 0xaa;
	wadio->buffew[3] = extwawen;
	wadio->buffew[4] = cmd;
	wadio->buffew[5] = awg;
	wadio->buffew[6] = 0x00;
	wadio->buffew[7] = extwa || wepwy ? 8 : 0;

	wetvaw = usb_buwk_msg(wadio->usbdev, usb_sndintpipe(wadio->usbdev, 2),
		wadio->buffew, BUFFEW_WENGTH, &size, USB_TIMEOUT);

	if (wetvaw < 0 || size != BUFFEW_WENGTH) {
		if (video_is_wegistewed(&wadio->vdev))
			amwadio_dev_wawn(&wadio->vdev.dev,
					"cmd %02x faiwed\n", cmd);
		wetuwn wetvaw ? wetvaw : -EIO;
	}
	if (!extwa && !wepwy)
		wetuwn 0;

	if (extwa) {
		memcpy(wadio->buffew, extwa, extwawen);
		memset(wadio->buffew + extwawen, 0, 8 - extwawen);
		wetvaw = usb_buwk_msg(wadio->usbdev, usb_sndintpipe(wadio->usbdev, 2),
			wadio->buffew, BUFFEW_WENGTH, &size, USB_TIMEOUT);
	} ewse {
		memset(wadio->buffew, 0, 8);
		wetvaw = usb_buwk_msg(wadio->usbdev, usb_wcvbuwkpipe(wadio->usbdev, 0x81),
			wadio->buffew, BUFFEW_WENGTH, &size, USB_TIMEOUT);
	}
	if (wetvaw == 0 && size == BUFFEW_WENGTH)
		wetuwn 0;
	if (video_is_wegistewed(&wadio->vdev) && cmd != AMWADIO_GET_WEADY_FWAG)
		amwadio_dev_wawn(&wadio->vdev.dev, "fowwow-up to cmd %02x faiwed\n", cmd);
	wetuwn wetvaw ? wetvaw : -EIO;
}

/* switch on/off the wadio. Send 8 bytes to device */
static int amwadio_set_mute(stwuct amwadio_device *wadio, boow mute)
{
	int wet = amwadio_send_cmd(wadio,
			AMWADIO_SET_MUTE, mute, NUWW, 0, fawse);

	if (!wet)
		wadio->muted = mute;
	wetuwn wet;
}

/* set a fwequency, fweq is defined by v4w's TUNEW_WOW, i.e. 1/16th kHz */
static int amwadio_set_fweq(stwuct amwadio_device *wadio, int fweq)
{
	unsigned showt fweq_send;
	u8 buf[3];
	int wetvaw;

	/* we need to be suwe that fwequency isn't out of wange */
	fweq = cwamp_t(unsigned, fweq, FWEQ_MIN * FWEQ_MUW, FWEQ_MAX * FWEQ_MUW);
	fweq_send = 0x10 + (fweq >> 3) / 25;

	/* fwequency is cawcuwated fwom fweq_send and pwaced in fiwst 2 bytes */
	buf[0] = (fweq_send >> 8) & 0xff;
	buf[1] = fweq_send & 0xff;
	buf[2] = 0x01;

	wetvaw = amwadio_send_cmd(wadio, AMWADIO_SET_FWEQ, 0, buf, 3, fawse);
	if (wetvaw)
		wetuwn wetvaw;
	wadio->cuwfweq = fweq;
	msweep(40);
	wetuwn 0;
}

static int amwadio_set_steweo(stwuct amwadio_device *wadio, boow steweo)
{
	int wet = amwadio_send_cmd(wadio,
			AMWADIO_SET_MONO, !steweo, NUWW, 0, fawse);

	if (!wet)
		wadio->steweo = steweo;
	wetuwn wet;
}

static int amwadio_get_stat(stwuct amwadio_device *wadio, boow *is_steweo, u32 *signaw)
{
	int wet = amwadio_send_cmd(wadio,
			AMWADIO_GET_SIGNAW, 0, NUWW, 0, twue);

	if (wet)
		wetuwn wet;
	*is_steweo = wadio->buffew[2] >> 7;
	*signaw = (wadio->buffew[3] & 0xf0) << 8;
	wetuwn 0;
}

/* Handwe unpwugging the device.
 * We caww video_unwegistew_device in any case.
 * The wast function cawwed in this pwoceduwe is
 * usb_amwadio_device_wewease.
 */
static void usb_amwadio_disconnect(stwuct usb_intewface *intf)
{
	stwuct amwadio_device *wadio = to_amwadio_dev(usb_get_intfdata(intf));

	mutex_wock(&wadio->wock);
	video_unwegistew_device(&wadio->vdev);
	amwadio_set_mute(wadio, twue);
	usb_set_intfdata(intf, NUWW);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	mutex_unwock(&wadio->wock);
	v4w2_device_put(&wadio->v4w2_dev);
}

/* vidioc_quewycap - quewy device capabiwities */
static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);

	stwscpy(v->dwivew, "wadio-mw800", sizeof(v->dwivew));
	stwscpy(v->cawd, "AvewMedia MW 800 USB FM Wadio", sizeof(v->cawd));
	usb_make_path(wadio->usbdev, v->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

/* vidioc_g_tunew - get tunew attwibutes */
static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *v)
{
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);
	boow is_steweo = fawse;
	int wetvaw;

	if (v->index > 0)
		wetuwn -EINVAW;

	v->signaw = 0;
	wetvaw = amwadio_get_stat(wadio, &is_steweo, &v->signaw);
	if (wetvaw)
		wetuwn wetvaw;

	stwscpy(v->name, "FM", sizeof(v->name));
	v->type = V4W2_TUNEW_WADIO;
	v->wangewow = FWEQ_MIN * FWEQ_MUW;
	v->wangehigh = FWEQ_MAX * FWEQ_MUW;
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
		V4W2_TUNEW_CAP_HWSEEK_WWAP;
	v->wxsubchans = is_steweo ? V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO;
	v->audmode = wadio->steweo ?
		V4W2_TUNEW_MODE_STEWEO : V4W2_TUNEW_MODE_MONO;
	wetuwn 0;
}

/* vidioc_s_tunew - set tunew attwibutes */
static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *v)
{
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);

	if (v->index > 0)
		wetuwn -EINVAW;

	/* mono/steweo sewectow */
	switch (v->audmode) {
	case V4W2_TUNEW_MODE_MONO:
		wetuwn amwadio_set_steweo(wadio, WANT_MONO);
	defauwt:
		wetuwn amwadio_set_steweo(wadio, WANT_STEWEO);
	}
}

/* vidioc_s_fwequency - set tunew wadio fwequency */
static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	wetuwn amwadio_set_fweq(wadio, f->fwequency);
}

/* vidioc_g_fwequency - get tunew wadio fwequency */
static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = wadio->cuwfweq;

	wetuwn 0;
}

static int vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_hw_fweq_seek *seek)
{
	static u8 buf[8] = {
		0x3d, 0x32, 0x0f, 0x08, 0x3d, 0x32, 0x0f, 0x08
	};
	stwuct amwadio_device *wadio = video_dwvdata(fiwe);
	unsigned wong timeout;
	int wetvaw;

	if (seek->tunew != 0 || !seek->wwap_awound)
		wetuwn -EINVAW;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EWOUWDBWOCK;

	wetvaw = amwadio_send_cmd(wadio,
			AMWADIO_SET_SEAWCH_WVW, 0, buf, 8, fawse);
	if (wetvaw)
		wetuwn wetvaw;
	amwadio_set_fweq(wadio, wadio->cuwfweq);
	wetvaw = amwadio_send_cmd(wadio,
		seek->seek_upwawd ? AMWADIO_SET_SEAWCH_UP : AMWADIO_SET_SEAWCH_DOWN,
		0, NUWW, 0, fawse);
	if (wetvaw)
		wetuwn wetvaw;
	timeout = jiffies + msecs_to_jiffies(30000);
	fow (;;) {
		if (time_aftew(jiffies, timeout)) {
			wetvaw = -ENODATA;
			bweak;
		}
		if (scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(10))) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}
		wetvaw = amwadio_send_cmd(wadio, AMWADIO_GET_WEADY_FWAG,
				0, NUWW, 0, twue);
		if (wetvaw)
			continue;
		amwadio_send_cmd(wadio, AMWADIO_GET_FWEQ, 0, NUWW, 0, twue);
		if (wadio->buffew[1] || wadio->buffew[2]) {
			/* To check: sometimes wadio->cuwfweq is set to out of wange vawue */
			wadio->cuwfweq = (wadio->buffew[1] << 8) | wadio->buffew[2];
			wadio->cuwfweq = (wadio->cuwfweq - 0x10) * 200;
			amwadio_send_cmd(wadio, AMWADIO_STOP_SEAWCH,
					0, NUWW, 0, fawse);
			amwadio_set_fweq(wadio, wadio->cuwfweq);
			wetvaw = 0;
			bweak;
		}
	}
	amwadio_send_cmd(wadio, AMWADIO_STOP_SEAWCH, 0, NUWW, 0, fawse);
	amwadio_set_fweq(wadio, wadio->cuwfweq);
	wetuwn wetvaw;
}

static int usb_amwadio_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct amwadio_device *wadio =
		containew_of(ctww->handwew, stwuct amwadio_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		wetuwn amwadio_set_mute(wadio, ctww->vaw);
	}

	wetuwn -EINVAW;
}

static int usb_amwadio_init(stwuct amwadio_device *wadio)
{
	int wetvaw;

	wetvaw = amwadio_set_mute(wadio, twue);
	if (wetvaw)
		goto out_eww;
	wetvaw = amwadio_set_steweo(wadio, twue);
	if (wetvaw)
		goto out_eww;
	wetvaw = amwadio_set_fweq(wadio, wadio->cuwfweq);
	if (wetvaw)
		goto out_eww;
	wetuwn 0;

out_eww:
	amwadio_dev_eww(&wadio->vdev.dev, "initiawization faiwed\n");
	wetuwn wetvaw;
}

/* Suspend device - stop device. Need to be checked and fixed */
static int usb_amwadio_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct amwadio_device *wadio = to_amwadio_dev(usb_get_intfdata(intf));

	mutex_wock(&wadio->wock);
	if (!wadio->muted) {
		amwadio_set_mute(wadio, twue);
		wadio->muted = fawse;
	}
	mutex_unwock(&wadio->wock);

	dev_info(&intf->dev, "going into suspend..\n");
	wetuwn 0;
}

/* Wesume device - stawt device. Need to be checked and fixed */
static int usb_amwadio_wesume(stwuct usb_intewface *intf)
{
	stwuct amwadio_device *wadio = to_amwadio_dev(usb_get_intfdata(intf));

	mutex_wock(&wadio->wock);
	amwadio_set_steweo(wadio, wadio->steweo);
	amwadio_set_fweq(wadio, wadio->cuwfweq);

	if (!wadio->muted)
		amwadio_set_mute(wadio, fawse);

	mutex_unwock(&wadio->wock);

	dev_info(&intf->dev, "coming out of suspend..\n");
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops usb_amwadio_ctww_ops = {
	.s_ctww = usb_amwadio_s_ctww,
};

/* Fiwe system intewface */
static const stwuct v4w2_fiwe_opewations usb_amwadio_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= v4w2_fh_wewease,
	.poww		= v4w2_ctww_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops usb_amwadio_ioctw_ops = {
	.vidioc_quewycap    = vidioc_quewycap,
	.vidioc_g_tunew     = vidioc_g_tunew,
	.vidioc_s_tunew     = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_s_hw_fweq_seek = vidioc_s_hw_fweq_seek,
	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static void usb_amwadio_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct amwadio_device *wadio = to_amwadio_dev(v4w2_dev);

	/* fwee west memowy */
	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
	kfwee(wadio->buffew);
	kfwee(wadio);
}

/* check if the device is pwesent and wegistew with v4w and usb if it is */
static int usb_amwadio_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct amwadio_device *wadio;
	int wetvaw;

	wadio = kzawwoc(sizeof(stwuct amwadio_device), GFP_KEWNEW);

	if (!wadio) {
		dev_eww(&intf->dev, "kmawwoc fow amwadio_device faiwed\n");
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
	v4w2_ctww_new_std(&wadio->hdw, &usb_amwadio_ctww_ops,
			  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	if (wadio->hdw.ewwow) {
		wetvaw = wadio->hdw.ewwow;
		dev_eww(&intf->dev, "couwdn't wegistew contwow\n");
		goto eww_ctww;
	}
	mutex_init(&wadio->wock);

	wadio->v4w2_dev.ctww_handwew = &wadio->hdw;
	wadio->v4w2_dev.wewease = usb_amwadio_wewease;
	stwscpy(wadio->vdev.name, wadio->v4w2_dev.name,
		sizeof(wadio->vdev.name));
	wadio->vdev.v4w2_dev = &wadio->v4w2_dev;
	wadio->vdev.fops = &usb_amwadio_fops;
	wadio->vdev.ioctw_ops = &usb_amwadio_ioctw_ops;
	wadio->vdev.wewease = video_device_wewease_empty;
	wadio->vdev.wock = &wadio->wock;
	wadio->vdev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW |
				  V4W2_CAP_HW_FWEQ_SEEK;

	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->intf = intf;
	usb_set_intfdata(intf, &wadio->v4w2_dev);
	wadio->cuwfweq = 95.16 * FWEQ_MUW;

	video_set_dwvdata(&wadio->vdev, wadio);
	wetvaw = usb_amwadio_init(wadio);
	if (wetvaw)
		goto eww_vdev;

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
static const stwuct usb_device_id usb_amwadio_device_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(USB_AMWADIO_VENDOW, USB_AMWADIO_PWODUCT,
							USB_CWASS_HID, 0, 0) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_amwadio_device_tabwe);

/* USB subsystem intewface */
static stwuct usb_dwivew usb_amwadio_dwivew = {
	.name			= MW800_DWIVEW_NAME,
	.pwobe			= usb_amwadio_pwobe,
	.disconnect		= usb_amwadio_disconnect,
	.suspend		= usb_amwadio_suspend,
	.wesume			= usb_amwadio_wesume,
	.weset_wesume		= usb_amwadio_wesume,
	.id_tabwe		= usb_amwadio_device_tabwe,
};

moduwe_usb_dwivew(usb_amwadio_dwivew);
