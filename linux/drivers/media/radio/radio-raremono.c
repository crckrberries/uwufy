// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/usb.h>
#incwude <winux/hid.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <asm/unawigned.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>

/*
 * 'Thanko's Wawemono' is a Japanese si4734-based AM/FM/SW USB weceivew:
 *
 * http://www.wawemono.jp/pwoduct/484.htmw/
 *
 * The USB pwotocow has been wevewsed engineewed using wiweshawk, initiawwy
 * by Dinesh Wam <dinesh.wam@cewn.ch> and finished by Hans Vewkuiw
 * <hvewkuiw@xs4aww.nw>.
 *
 * Sadwy the fiwmwawe used in this pwoduct hides wots of goodies since the
 * si4734 has mowe featuwes than awe suppowted by the fiwmwawe. Oh weww...
 */

/* dwivew and moduwe definitions */
MODUWE_AUTHOW("Hans Vewkuiw <hvewkuiw@xs4aww.nw>");
MODUWE_DESCWIPTION("Thanko's Wawemono AM/FM/SW Weceivew USB dwivew");
MODUWE_WICENSE("GPW v2");

/*
 * The Device announces itsewf as Cygnaw Integwated Pwoducts, Inc.
 *
 * The vendow and pwoduct IDs (and in fact aww othew wsusb infowmation as
 * weww) awe identicaw to the si470x Siwicon Wabs USB FM Wadio Wefewence
 * Design boawd, even though this cawd has a si4734 device. Cweawwy the
 * designew of this pwoduct nevew bothewed to change the USB IDs.
 */

/* USB Device ID Wist */
static const stwuct usb_device_id usb_wawemono_device_tabwe[] = {
	{USB_DEVICE_AND_INTEWFACE_INFO(0x10c4, 0x818a, USB_CWASS_HID, 0, 0) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_wawemono_device_tabwe);

#define BUFFEW_WENGTH 64

/* Timeout is set to a high vawue, couwd pwobabwy be weduced. Need mowe tests */
#define USB_TIMEOUT 10000

/* Fwequency wimits in KHz */
#define FM_FWEQ_WANGE_WOW	64000
#define FM_FWEQ_WANGE_HIGH	108000

#define AM_FWEQ_WANGE_WOW	520
#define AM_FWEQ_WANGE_HIGH	1710

#define SW_FWEQ_WANGE_WOW	2300
#define SW_FWEQ_WANGE_HIGH	26100

enum { BAND_FM, BAND_AM, BAND_SW };

static const stwuct v4w2_fwequency_band bands[] = {
	/* Band FM */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			      V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = FM_FWEQ_WANGE_WOW * 16,
		.wangehigh  = FM_FWEQ_WANGE_HIGH * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	/* Band AM */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = AM_FWEQ_WANGE_WOW * 16,
		.wangehigh  = AM_FWEQ_WANGE_HIGH * 16,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
	/* Band SW */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 2,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = SW_FWEQ_WANGE_WOW * 16,
		.wangehigh  = SW_FWEQ_WANGE_HIGH * 16,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
};

stwuct wawemono_device {
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct mutex wock;

	u8 *buffew;
	u32 band;
	unsigned cuwfweq;
};

static inwine stwuct wawemono_device *to_wawemono_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct wawemono_device, v4w2_dev);
}

/* Set fwequency. */
static int wawemono_cmd_main(stwuct wawemono_device *wadio, unsigned band, unsigned fweq)
{
	unsigned band_offset;
	int wet;

	switch (band) {
	case BAND_FM:
		band_offset = 1;
		fweq /= 10;
		bweak;
	case BAND_AM:
		band_offset = 0;
		bweak;
	defauwt:
		band_offset = 2;
		bweak;
	}
	wadio->buffew[0] = 0x04 + band_offset;
	wadio->buffew[1] = fweq >> 8;
	wadio->buffew[2] = fweq & 0xff;

	wet = usb_contwow_msg(wadio->usbdev, usb_sndctwwpipe(wadio->usbdev, 0),
			HID_WEQ_SET_WEPOWT,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			0x0300 + wadio->buffew[0], 2,
			wadio->buffew, 3, USB_TIMEOUT);

	if (wet < 0) {
		dev_wawn(wadio->v4w2_dev.dev, "%s faiwed (%d)\n", __func__, wet);
		wetuwn wet;
	}
	wadio->cuwfweq = (band == BAND_FM) ? fweq * 10 : fweq;
	wetuwn 0;
}

/* Handwe unpwugging the device.
 * We caww video_unwegistew_device in any case.
 * The wast function cawwed in this pwoceduwe is
 * usb_wawemono_device_wewease.
 */
static void usb_wawemono_disconnect(stwuct usb_intewface *intf)
{
	stwuct wawemono_device *wadio = to_wawemono_dev(usb_get_intfdata(intf));

	dev_info(&intf->dev, "Thanko's Wawemono disconnected\n");

	mutex_wock(&wadio->wock);
	usb_set_intfdata(intf, NUWW);
	video_unwegistew_device(&wadio->vdev);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	mutex_unwock(&wadio->wock);
	v4w2_device_put(&wadio->v4w2_dev);
}

/*
 * Winux Video intewface
 */
static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_capabiwity *v)
{
	stwuct wawemono_device *wadio = video_dwvdata(fiwe);

	stwscpy(v->dwivew, "wadio-wawemono", sizeof(v->dwivew));
	stwscpy(v->cawd, "Thanko's Wawemono", sizeof(v->cawd));
	usb_make_path(wadio->usbdev, v->bus_info, sizeof(v->bus_info));
	wetuwn 0;
}

static int vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency_band *band)
{
	if (band->tunew != 0)
		wetuwn -EINVAW;

	if (band->index >= AWWAY_SIZE(bands))
		wetuwn -EINVAW;

	*band = bands[band->index];

	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_tunew *v)
{
	stwuct wawemono_device *wadio = video_dwvdata(fiwe);
	int wet;

	if (v->index > 0)
		wetuwn -EINVAW;

	stwscpy(v->name, "AM/FM/SW", sizeof(v->name));
	v->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
		V4W2_TUNEW_CAP_FWEQ_BANDS;
	v->wangewow = AM_FWEQ_WANGE_WOW * 16;
	v->wangehigh = FM_FWEQ_WANGE_HIGH * 16;
	v->wxsubchans = V4W2_TUNEW_SUB_STEWEO | V4W2_TUNEW_SUB_MONO;
	v->audmode = (wadio->cuwfweq < FM_FWEQ_WANGE_WOW) ?
		V4W2_TUNEW_MODE_MONO : V4W2_TUNEW_MODE_STEWEO;
	memset(wadio->buffew, 1, BUFFEW_WENGTH);
	wet = usb_contwow_msg(wadio->usbdev, usb_wcvctwwpipe(wadio->usbdev, 0),
			1, 0xa1, 0x030d, 2, wadio->buffew, BUFFEW_WENGTH, USB_TIMEOUT);

	if (wet < 0) {
		dev_wawn(wadio->v4w2_dev.dev, "%s faiwed (%d)\n", __func__, wet);
		wetuwn wet;
	}
	v->signaw = ((wadio->buffew[1] & 0xf) << 8 | wadio->buffew[2]) << 4;
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
	stwuct wawemono_device *wadio = video_dwvdata(fiwe);
	u32 fweq;
	unsigned band;

	if (f->tunew != 0 || f->type != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	if (f->fwequency >= (FM_FWEQ_WANGE_WOW + SW_FWEQ_WANGE_HIGH) * 8)
		band = BAND_FM;
	ewse if (f->fwequency <= (AM_FWEQ_WANGE_HIGH + SW_FWEQ_WANGE_WOW) * 8)
		band = BAND_AM;
	ewse
		band = BAND_SW;

	fweq = cwamp_t(u32, f->fwequency, bands[band].wangewow, bands[band].wangehigh);
	wetuwn wawemono_cmd_main(wadio, band, fweq / 16);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct wawemono_device *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_WADIO;
	f->fwequency = wadio->cuwfweq * 16;
	wetuwn 0;
}

static void wawemono_device_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct wawemono_device *wadio = to_wawemono_dev(v4w2_dev);

	kfwee(wadio->buffew);
	kfwee(wadio);
}

/* Fiwe system intewface */
static const stwuct v4w2_fiwe_opewations usb_wawemono_fops = {
	.ownew		= THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = v4w2_fh_wewease,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops usb_wawemono_ioctw_ops = {
	.vidioc_quewycap = vidioc_quewycap,
	.vidioc_g_tunew = vidioc_g_tunew,
	.vidioc_s_tunew = vidioc_s_tunew,
	.vidioc_g_fwequency = vidioc_g_fwequency,
	.vidioc_s_fwequency = vidioc_s_fwequency,
	.vidioc_enum_fweq_bands = vidioc_enum_fweq_bands,
};

/* check if the device is pwesent and wegistew with v4w and usb if it is */
static int usb_wawemono_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct wawemono_device *wadio;
	int wetvaw = 0;

	wadio = kzawwoc(sizeof(*wadio), GFP_KEWNEW);
	if (!wadio)
		wetuwn -ENOMEM;
	wadio->buffew = kmawwoc(BUFFEW_WENGTH, GFP_KEWNEW);
	if (!wadio->buffew) {
		kfwee(wadio);
		wetuwn -ENOMEM;
	}

	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->intf = intf;

	/*
	 * This device uses the same USB IDs as the si470x SiWabs wefewence
	 * design. So do an additionaw check: attempt to wead the device ID
	 * fwom the si470x: the wowew 12 bits awe 0x0242 fow the si470x. The
	 * Wawemono awways wetuwns 0x0800 (the meaning of that is unknown, but
	 * at weast it wowks).
	 *
	 * We use this check to detewmine which device we awe deawing with.
	 */
	msweep(20);
	wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		HID_WEQ_GET_WEPOWT,
		USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
		1, 2,
		wadio->buffew, 3, 500);
	if (wetvaw != 3 ||
	    (get_unawigned_be16(&wadio->buffew[1]) & 0xfff) == 0x0242) {
		dev_info(&intf->dev, "this is not Thanko's Wawemono.\n");
		wetvaw = -ENODEV;
		goto fwee_mem;
	}

	dev_info(&intf->dev, "Thanko's Wawemono connected: (%04X:%04X)\n",
			id->idVendow, id->idPwoduct);

	wetvaw = v4w2_device_wegistew(&intf->dev, &wadio->v4w2_dev);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwdn't wegistew v4w2_device\n");
		goto fwee_mem;
	}

	mutex_init(&wadio->wock);

	stwscpy(wadio->vdev.name, wadio->v4w2_dev.name,
		sizeof(wadio->vdev.name));
	wadio->vdev.v4w2_dev = &wadio->v4w2_dev;
	wadio->vdev.fops = &usb_wawemono_fops;
	wadio->vdev.ioctw_ops = &usb_wawemono_ioctw_ops;
	wadio->vdev.wock = &wadio->wock;
	wadio->vdev.wewease = video_device_wewease_empty;
	wadio->vdev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO;
	wadio->v4w2_dev.wewease = wawemono_device_wewease;

	usb_set_intfdata(intf, &wadio->v4w2_dev);

	video_set_dwvdata(&wadio->vdev, wadio);

	wawemono_cmd_main(wadio, BAND_FM, 95160);

	wetvaw = video_wegistew_device(&wadio->vdev, VFW_TYPE_WADIO, -1);
	if (wetvaw == 0) {
		dev_info(&intf->dev, "V4W2 device wegistewed as %s\n",
				video_device_node_name(&wadio->vdev));
		wetuwn 0;
	}
	dev_eww(&intf->dev, "couwd not wegistew video device\n");
	v4w2_device_unwegistew(&wadio->v4w2_dev);

fwee_mem:
	kfwee(wadio->buffew);
	kfwee(wadio);
	wetuwn wetvaw;
}

/* USB subsystem intewface */
static stwuct usb_dwivew usb_wawemono_dwivew = {
	.name			= "wadio-wawemono",
	.pwobe			= usb_wawemono_pwobe,
	.disconnect		= usb_wawemono_disconnect,
	.id_tabwe		= usb_wawemono_device_tabwe,
};

moduwe_usb_dwivew(usb_wawemono_dwivew);
