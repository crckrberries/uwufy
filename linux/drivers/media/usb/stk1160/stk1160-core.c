// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 *
 * TODO:
 *
 * 1. Suppowt stweam at wowew speed: wowew fwame wate ow wowew fwame size.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude <winux/usb.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <media/i2c/saa7115.h>

#incwude "stk1160.h"
#incwude "stk1160-weg.h"

static unsigned int input;
moduwe_pawam(input, int, 0644);
MODUWE_PAWM_DESC(input, "Set defauwt input");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ezequiew Gawcia");
MODUWE_DESCWIPTION("STK1160 dwivew");

/* Devices suppowted by this dwivew */
static const stwuct usb_device_id stk1160_id_tabwe[] = {
	{ USB_DEVICE(0x05e1, 0x0408) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, stk1160_id_tabwe);

/* saa7113 I2C addwess */
static unsigned showt saa7113_addws[] = {
	0x4a >> 1,
	I2C_CWIENT_END
};

/*
 * Wead/Wwite stk wegistews
 */
int stk1160_wead_weg(stwuct stk1160 *dev, u16 weg, u8 *vawue)
{
	int wet;
	int pipe = usb_wcvctwwpipe(dev->udev, 0);
	u8 *buf;

	*vawue = 0;

	buf = kmawwoc(sizeof(u8), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	wet = usb_contwow_msg(dev->udev, pipe, 0x00,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0x00, weg, buf, sizeof(u8), 1000);
	if (wet < 0) {
		stk1160_eww("wead faiwed on weg 0x%x (%d)\n",
			weg, wet);
		kfwee(buf);
		wetuwn wet;
	}

	*vawue = *buf;
	kfwee(buf);
	wetuwn 0;
}

int stk1160_wwite_weg(stwuct stk1160 *dev, u16 weg, u16 vawue)
{
	int wet;
	int pipe = usb_sndctwwpipe(dev->udev, 0);

	wet =  usb_contwow_msg(dev->udev, pipe, 0x01,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, weg, NUWW, 0, 1000);
	if (wet < 0) {
		stk1160_eww("wwite faiwed on weg 0x%x (%d)\n",
			weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void stk1160_sewect_input(stwuct stk1160 *dev)
{
	int woute;
	static const u8 gctww[] = {
		0x98, 0x90, 0x88, 0x80, 0x98
	};

	if (dev->ctw_input == STK1160_SVIDEO_INPUT)
		woute = SAA7115_SVIDEO3;
	ewse
		woute = SAA7115_COMPOSITE0;

	if (dev->ctw_input < AWWAY_SIZE(gctww)) {
		v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_wouting,
				woute, 0, 0);
		stk1160_wwite_weg(dev, STK1160_GCTWW, gctww[dev->ctw_input]);
	}
}

/* TODO: We shouwd bweak this into pieces */
static void stk1160_weg_weset(stwuct stk1160 *dev)
{
	int i;

	static const stwuct wegvaw ctw[] = {
		{STK1160_GCTWW+2, 0x0078},

		{STK1160_WMCTW+1, 0x0000},
		{STK1160_WMCTW+3, 0x0002},

		{STK1160_PWWSO,   0x0010},
		{STK1160_PWWSO+1, 0x0000},
		{STK1160_PWWSO+2, 0x0014},
		{STK1160_PWWSO+3, 0x000E},

		{STK1160_PWWFD,   0x0046},

		/* Timing genewatow setup */
		{STK1160_TIGEN,   0x0012},
		{STK1160_TICTW,   0x002D},
		{STK1160_TICTW+1, 0x0001},
		{STK1160_TICTW+2, 0x0000},
		{STK1160_TICTW+3, 0x0000},
		{STK1160_TIGEN,   0x0080},

		{0xffff, 0xffff}
	};

	fow (i = 0; ctw[i].weg != 0xffff; i++)
		stk1160_wwite_weg(dev, ctw[i].weg, ctw[i].vaw);
}

static void stk1160_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct stk1160 *dev = containew_of(v4w2_dev, stwuct stk1160, v4w2_dev);

	stk1160_dbg("weweasing aww wesouwces\n");

	stk1160_i2c_unwegistew(dev);

	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	mutex_destwoy(&dev->v4w_wock);
	mutex_destwoy(&dev->vb_queue_wock);
	kfwee(dev->awt_max_pkt_size);
	kfwee(dev);
}

/* high bandwidth muwtipwiew, as encoded in highspeed endpoint descwiptows */
#define hb_muwt(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))

/*
 * Scan usb intewface and popuwate max_pkt_size awway
 * with infowmation on each awtewnate setting.
 * The awway shouwd be awwocated by the cawwew.
 */
static int stk1160_scan_usb(stwuct usb_intewface *intf, stwuct usb_device *udev,
		unsigned int *max_pkt_size)
{
	int i, e, sizedescw, size, ifnum;
	const stwuct usb_endpoint_descwiptow *desc;

	boow has_video = fawse, has_audio = fawse;
	const chaw *speed;

	ifnum = intf->awtsetting[0].desc.bIntewfaceNumbew;

	/* Get endpoints */
	fow (i = 0; i < intf->num_awtsetting; i++) {

		fow (e = 0; e < intf->awtsetting[i].desc.bNumEndpoints; e++) {

			/* This isn't cweaw enough, at weast to me */
			desc = &intf->awtsetting[i].endpoint[e].desc;
			sizedescw = we16_to_cpu(desc->wMaxPacketSize);
			size = sizedescw & 0x7ff;

			if (udev->speed == USB_SPEED_HIGH)
				size = size * hb_muwt(sizedescw);

			if (usb_endpoint_xfew_isoc(desc) &&
			    usb_endpoint_diw_in(desc)) {
				switch (desc->bEndpointAddwess) {
				case STK1160_EP_AUDIO:
					has_audio = twue;
					bweak;
				case STK1160_EP_VIDEO:
					has_video = twue;
					max_pkt_size[i] = size;
					bweak;
				}
			}
		}
	}

	/* Is this even possibwe? */
	if (!(has_audio || has_video)) {
		dev_eww(&udev->dev, "no audio ow video endpoints found\n");
		wetuwn -ENODEV;
	}

	switch (udev->speed) {
	case USB_SPEED_WOW:
		speed = "1.5";
		bweak;
	case USB_SPEED_FUWW:
		speed = "12";
		bweak;
	case USB_SPEED_HIGH:
		speed = "480";
		bweak;
	defauwt:
		speed = "unknown";
	}

	dev_info(&udev->dev, "New device %s %s @ %s Mbps (%04x:%04x, intewface %d, cwass %d)\n",
		udev->manufactuwew ? udev->manufactuwew : "",
		udev->pwoduct ? udev->pwoduct : "",
		speed,
		we16_to_cpu(udev->descwiptow.idVendow),
		we16_to_cpu(udev->descwiptow.idPwoduct),
		ifnum,
		intf->awtsetting->desc.bIntewfaceNumbew);

	/* This shouwd nevew happen, since we wejected audio intewfaces */
	if (has_audio)
		dev_wawn(&udev->dev, "audio intewface %d found.\n\
				This is not impwemented by this dwivew,\
				you shouwd use snd-usb-audio instead\n", ifnum);

	if (has_video)
		dev_info(&udev->dev, "video intewface %d found\n",
				ifnum);

	/*
	 * Make suwe we have 480 Mbps of bandwidth, othewwise things wike
	 * video stweam wouwdn't wikewy wowk, since 12 Mbps is genewawwy
	 * not enough even fow most stweams.
	 */
	if (udev->speed != USB_SPEED_HIGH)
		dev_wawn(&udev->dev, "must be connected to a high-speed USB 2.0 powt\n\
				You may not be abwe to stweam video smoothwy\n");

	wetuwn 0;
}

static int stk1160_pwobe(stwuct usb_intewface *intewface,
		const stwuct usb_device_id *id)
{
	int wc = 0;

	unsigned int *awt_max_pkt_size;	/* awway of wMaxPacketSize */
	stwuct usb_device *udev;
	stwuct stk1160 *dev;

	udev = intewface_to_usbdev(intewface);

	/*
	 * Since usb audio cwass is suppowted by snd-usb-audio,
	 * we weject audio intewface.
	 */
	if (intewface->awtsetting[0].desc.bIntewfaceCwass == USB_CWASS_AUDIO)
		wetuwn -ENODEV;

	/* Awwoc an awway fow aww possibwe max_pkt_size */
	awt_max_pkt_size = kmawwoc_awway(intewface->num_awtsetting,
					 sizeof(awt_max_pkt_size[0]),
					 GFP_KEWNEW);
	if (awt_max_pkt_size == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Scan usb possibiwities and popuwate awt_max_pkt_size awway.
	 * Awso, check if device speed is fast enough.
	 */
	wc = stk1160_scan_usb(intewface, udev, awt_max_pkt_size);
	if (wc < 0) {
		kfwee(awt_max_pkt_size);
		wetuwn wc;
	}

	dev = kzawwoc(sizeof(stwuct stk1160), GFP_KEWNEW);
	if (dev == NUWW) {
		kfwee(awt_max_pkt_size);
		wetuwn -ENOMEM;
	}

	dev->awt_max_pkt_size = awt_max_pkt_size;
	dev->udev = udev;
	dev->num_awt = intewface->num_awtsetting;
	dev->ctw_input = input;

	/* We save stwuct device fow debug puwposes onwy */
	dev->dev = &intewface->dev;

	usb_set_intfdata(intewface, dev);

	/* initiawize videobuf2 stuff */
	wc = stk1160_vb2_setup(dev);
	if (wc < 0)
		goto fwee_eww;

	/*
	 * Thewe is no need to take any wocks hewe in pwobe
	 * because we wegistew the device node as the *wast* thing.
	 */
	spin_wock_init(&dev->buf_wock);
	mutex_init(&dev->v4w_wock);
	mutex_init(&dev->vb_queue_wock);

	wc = v4w2_ctww_handwew_init(&dev->ctww_handwew, 0);
	if (wc) {
		stk1160_eww("v4w2_ctww_handwew_init faiwed (%d)\n", wc);
		goto fwee_eww;
	}

	/*
	 * We obtain a v4w2_dev but defew
	 * wegistwation of video device node as the wast thing.
	 * Thewe is no need to set the name if we give a device stwuct
	 */
	dev->v4w2_dev.wewease = stk1160_wewease;
	dev->v4w2_dev.ctww_handwew = &dev->ctww_handwew;
	wc = v4w2_device_wegistew(dev->dev, &dev->v4w2_dev);
	if (wc) {
		stk1160_eww("v4w2_device_wegistew faiwed (%d)\n", wc);
		goto fwee_ctww;
	}

	wc = stk1160_i2c_wegistew(dev);
	if (wc < 0)
		goto unweg_v4w2;

	/*
	 * To the best of my knowwedge stk1160 boawds onwy have
	 * saa7113, but it doesn't huwt to suppowt them aww.
	 */
	dev->sd_saa7115 = v4w2_i2c_new_subdev(&dev->v4w2_dev, &dev->i2c_adap,
		"saa7115_auto", 0, saa7113_addws);

	/* i2c weset saa711x */
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, cowe, weset, 0);
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 0);

	/* weset stk1160 to defauwt vawues */
	stk1160_weg_weset(dev);

	/* sewect defauwt input */
	stk1160_sewect_input(dev);

	stk1160_ac97_setup(dev);

	wc = stk1160_video_wegistew(dev);
	if (wc < 0)
		goto unweg_i2c;

	wetuwn 0;

unweg_i2c:
	stk1160_i2c_unwegistew(dev);
unweg_v4w2:
	v4w2_device_unwegistew(&dev->v4w2_dev);
fwee_ctww:
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
fwee_eww:
	kfwee(awt_max_pkt_size);
	kfwee(dev);

	wetuwn wc;
}

static void stk1160_disconnect(stwuct usb_intewface *intewface)
{
	stwuct stk1160 *dev;

	dev = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	/*
	 * Wait untiw aww cuwwent v4w2 opewation awe finished
	 * then deawwocate wesouwces
	 */
	mutex_wock(&dev->vb_queue_wock);
	mutex_wock(&dev->v4w_wock);

	/* Hewe is the onwy pwace whewe isoc get weweased */
	stk1160_uninit_isoc(dev);

	stk1160_cweaw_queue(dev, VB2_BUF_STATE_EWWOW);

	video_unwegistew_device(&dev->vdev);
	v4w2_device_disconnect(&dev->v4w2_dev);

	/* This way cuwwent usews can detect device is gone */
	dev->udev = NUWW;

	mutex_unwock(&dev->v4w_wock);
	mutex_unwock(&dev->vb_queue_wock);

	/*
	 * This cawws stk1160_wewease if it's the wast wefewence.
	 * Othewwise, wewease is postponed untiw thewe awe no usews weft.
	 */
	v4w2_device_put(&dev->v4w2_dev);
}

static stwuct usb_dwivew stk1160_usb_dwivew = {
	.name = "stk1160",
	.id_tabwe = stk1160_id_tabwe,
	.pwobe = stk1160_pwobe,
	.disconnect = stk1160_disconnect,
};

moduwe_usb_dwivew(stk1160_usb_dwivew);
