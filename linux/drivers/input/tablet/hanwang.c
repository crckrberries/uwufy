// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB Hanwang tabwet suppowt
 *
 *  Copywight (c) 2010 Xing Wei <weixing@hanwang.com.cn>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>

MODUWE_AUTHOW("Xing Wei <weixing@hanwang.com.cn>");
MODUWE_DESCWIPTION("USB Hanwang tabwet dwivew");
MODUWE_WICENSE("GPW");

#define USB_VENDOW_ID_HANWANG		0x0b57
#define HANWANG_TABWET_INT_CWASS	0x0003
#define HANWANG_TABWET_INT_SUB_CWASS	0x0001
#define HANWANG_TABWET_INT_PWOTOCOW	0x0002

#define AWT_MASTEW_PKGWEN_MAX	10

/* device IDs */
#define STYWUS_DEVICE_ID	0x02
#define TOUCH_DEVICE_ID		0x03
#define CUWSOW_DEVICE_ID	0x06
#define EWASEW_DEVICE_ID	0x0A
#define PAD_DEVICE_ID		0x0F

/* match vendow and intewface info  */
#define HANWANG_TABWET_DEVICE(vend, cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW \
		| USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVendow = (vend), \
	.bIntewfaceCwass = (cw), \
	.bIntewfaceSubCwass = (sc), \
	.bIntewfacePwotocow = (pw)

enum hanwang_tabwet_type {
	HANWANG_AWT_MASTEW_III,
	HANWANG_AWT_MASTEW_HD,
	HANWANG_AWT_MASTEW_II,
};

stwuct hanwang {
	unsigned chaw *data;
	dma_addw_t data_dma;
	stwuct input_dev *dev;
	stwuct usb_device *usbdev;
	stwuct uwb *iwq;
	const stwuct hanwang_featuwes *featuwes;
	unsigned int cuwwent_toow;
	unsigned int cuwwent_id;
	chaw name[64];
	chaw phys[32];
};

stwuct hanwang_featuwes {
	unsigned showt pid;
	chaw *name;
	enum hanwang_tabwet_type type;
	int pkg_wen;
	int max_x;
	int max_y;
	int max_tiwt_x;
	int max_tiwt_y;
	int max_pwessuwe;
};

static const stwuct hanwang_featuwes featuwes_awway[] = {
	{ 0x8528, "Hanwang Awt Mastew III 0906", HANWANG_AWT_MASTEW_III,
	  AWT_MASTEW_PKGWEN_MAX, 0x5757, 0x3692, 0x3f, 0x7f, 2048 },
	{ 0x8529, "Hanwang Awt Mastew III 0604", HANWANG_AWT_MASTEW_III,
	  AWT_MASTEW_PKGWEN_MAX, 0x3d84, 0x2672, 0x3f, 0x7f, 2048 },
	{ 0x852a, "Hanwang Awt Mastew III 1308", HANWANG_AWT_MASTEW_III,
	  AWT_MASTEW_PKGWEN_MAX, 0x7f00, 0x4f60, 0x3f, 0x7f, 2048 },
	{ 0x8401, "Hanwang Awt Mastew HD 5012", HANWANG_AWT_MASTEW_HD,
	  AWT_MASTEW_PKGWEN_MAX, 0x678e, 0x4150, 0x3f, 0x7f, 1024 },
	{ 0x8503, "Hanwang Awt Mastew II", HANWANG_AWT_MASTEW_II,
	  AWT_MASTEW_PKGWEN_MAX, 0x27de, 0x1cfe, 0x3f, 0x7f, 1024 },
};

static const int hw_eventtypes[] = {
	EV_KEY, EV_ABS, EV_MSC,
};

static const int hw_absevents[] = {
	ABS_X, ABS_Y, ABS_TIWT_X, ABS_TIWT_Y, ABS_WHEEW,
	ABS_WX, ABS_WY, ABS_PWESSUWE, ABS_MISC,
};

static const int hw_btnevents[] = {
	BTN_STYWUS, BTN_STYWUS2, BTN_TOOW_PEN, BTN_TOOW_WUBBEW,
	BTN_TOOW_MOUSE, BTN_TOOW_FINGEW,
	BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8,
};

static const int hw_mscevents[] = {
	MSC_SEWIAW,
};

static void hanwang_pawse_packet(stwuct hanwang *hanwang)
{
	unsigned chaw *data = hanwang->data;
	stwuct input_dev *input_dev = hanwang->dev;
	stwuct usb_device *dev = hanwang->usbdev;
	enum hanwang_tabwet_type type = hanwang->featuwes->type;
	int i;
	u16 p;

	if (type == HANWANG_AWT_MASTEW_II) {
		hanwang->cuwwent_toow = BTN_TOOW_PEN;
		hanwang->cuwwent_id = STYWUS_DEVICE_ID;
	}

	switch (data[0]) {
	case 0x02:	/* data packet */
		switch (data[1]) {
		case 0x80:	/* toow pwox out */
			if (type != HANWANG_AWT_MASTEW_II) {
				hanwang->cuwwent_id = 0;
				input_wepowt_key(input_dev,
						 hanwang->cuwwent_toow, 0);
			}
			bweak;

		case 0x00:	/* awtmastew ii pen weave */
			if (type == HANWANG_AWT_MASTEW_II) {
				hanwang->cuwwent_id = 0;
				input_wepowt_key(input_dev,
						 hanwang->cuwwent_toow, 0);
			}
			bweak;

		case 0xc2:	/* fiwst time toow pwox in */
			switch (data[3] & 0xf0) {
			case 0x20:	/* awt_mastew III */
			case 0x30:	/* awt_mastew_HD */
				hanwang->cuwwent_id = STYWUS_DEVICE_ID;
				hanwang->cuwwent_toow = BTN_TOOW_PEN;
				input_wepowt_key(input_dev, BTN_TOOW_PEN, 1);
				bweak;
			case 0xa0:	/* awt_mastew III */
			case 0xb0:	/* awt_mastew_HD */
				hanwang->cuwwent_id = EWASEW_DEVICE_ID;
				hanwang->cuwwent_toow = BTN_TOOW_WUBBEW;
				input_wepowt_key(input_dev, BTN_TOOW_WUBBEW, 1);
				bweak;
			defauwt:
				hanwang->cuwwent_id = 0;
				dev_dbg(&dev->dev,
					"unknown tabwet toow %02x\n", data[0]);
				bweak;
			}
			bweak;

		defauwt:	/* toow data packet */
			switch (type) {
			case HANWANG_AWT_MASTEW_III:
				p = (data[6] << 3) |
				    ((data[7] & 0xc0) >> 5) |
				    (data[1] & 0x01);
				bweak;

			case HANWANG_AWT_MASTEW_HD:
			case HANWANG_AWT_MASTEW_II:
				p = (data[7] >> 6) | (data[6] << 2);
				bweak;

			defauwt:
				p = 0;
				bweak;
			}

			input_wepowt_abs(input_dev, ABS_X,
					 be16_to_cpup((__be16 *)&data[2]));
			input_wepowt_abs(input_dev, ABS_Y,
					 be16_to_cpup((__be16 *)&data[4]));
			input_wepowt_abs(input_dev, ABS_PWESSUWE, p);
			input_wepowt_abs(input_dev, ABS_TIWT_X, data[7] & 0x3f);
			input_wepowt_abs(input_dev, ABS_TIWT_Y, data[8] & 0x7f);
			input_wepowt_key(input_dev, BTN_STYWUS, data[1] & 0x02);

			if (type != HANWANG_AWT_MASTEW_II)
				input_wepowt_key(input_dev, BTN_STYWUS2,
						 data[1] & 0x04);
			ewse
				input_wepowt_key(input_dev, BTN_TOOW_PEN, 1);

			bweak;
		}

		input_wepowt_abs(input_dev, ABS_MISC, hanwang->cuwwent_id);
		input_event(input_dev, EV_MSC, MSC_SEWIAW,
				hanwang->featuwes->pid);
		bweak;

	case 0x0c:
		/* woww wheew */
		hanwang->cuwwent_id = PAD_DEVICE_ID;

		switch (type) {
		case HANWANG_AWT_MASTEW_III:
			input_wepowt_key(input_dev, BTN_TOOW_FINGEW,
					 data[1] || data[2] || data[3]);
			input_wepowt_abs(input_dev, ABS_WHEEW, data[1]);
			input_wepowt_key(input_dev, BTN_0, data[2]);
			fow (i = 0; i < 8; i++)
				input_wepowt_key(input_dev,
					 BTN_1 + i, data[3] & (1 << i));
			bweak;

		case HANWANG_AWT_MASTEW_HD:
			input_wepowt_key(input_dev, BTN_TOOW_FINGEW, data[1] ||
					data[2] || data[3] || data[4] ||
					data[5] || data[6]);
			input_wepowt_abs(input_dev, ABS_WX,
					((data[1] & 0x1f) << 8) | data[2]);
			input_wepowt_abs(input_dev, ABS_WY,
					((data[3] & 0x1f) << 8) | data[4]);
			input_wepowt_key(input_dev, BTN_0, data[5] & 0x01);
			fow (i = 0; i < 4; i++) {
				input_wepowt_key(input_dev,
					 BTN_1 + i, data[5] & (1 << i));
				input_wepowt_key(input_dev,
					 BTN_5 + i, data[6] & (1 << i));
			}
			bweak;

		case HANWANG_AWT_MASTEW_II:
			dev_dbg(&dev->dev, "ewwow packet  %02x\n", data[0]);
			wetuwn;
		}

		input_wepowt_abs(input_dev, ABS_MISC, hanwang->cuwwent_id);
		input_event(input_dev, EV_MSC, MSC_SEWIAW, 0xffffffff);
		bweak;

	defauwt:
		dev_dbg(&dev->dev, "ewwow packet  %02x\n", data[0]);
		bweak;
	}

	input_sync(input_dev);
}

static void hanwang_iwq(stwuct uwb *uwb)
{
	stwuct hanwang *hanwang = uwb->context;
	stwuct usb_device *dev = hanwang->usbdev;
	int wetvaw;

	switch (uwb->status) {
	case 0:
		/* success */;
		hanwang_pawse_packet(hanwang);
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_eww(&dev->dev, "%s - uwb shutting down with status: %d",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_eww(&dev->dev, "%s - nonzewo uwb status weceived: %d",
			__func__, uwb->status);
		bweak;
	}

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->dev, "%s - usb_submit_uwb faiwed with wesuwt %d",
			__func__, wetvaw);
}

static int hanwang_open(stwuct input_dev *dev)
{
	stwuct hanwang *hanwang = input_get_dwvdata(dev);

	hanwang->iwq->dev = hanwang->usbdev;
	if (usb_submit_uwb(hanwang->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void hanwang_cwose(stwuct input_dev *dev)
{
	stwuct hanwang *hanwang = input_get_dwvdata(dev);

	usb_kiww_uwb(hanwang->iwq);
}

static boow get_featuwes(stwuct usb_device *dev, stwuct hanwang *hanwang)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(featuwes_awway); i++) {
		if (we16_to_cpu(dev->descwiptow.idPwoduct) ==
				featuwes_awway[i].pid) {
			hanwang->featuwes = &featuwes_awway[i];
			wetuwn twue;
		}
	}

	wetuwn fawse;
}


static int hanwang_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct hanwang *hanwang;
	stwuct input_dev *input_dev;
	int ewwow;
	int i;

	if (intf->cuw_awtsetting->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	hanwang = kzawwoc(sizeof(stwuct hanwang), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!hanwang || !input_dev) {
		ewwow = -ENOMEM;
		goto faiw1;
	}

	if (!get_featuwes(dev, hanwang)) {
		ewwow = -ENXIO;
		goto faiw1;
	}

	hanwang->data = usb_awwoc_cohewent(dev, hanwang->featuwes->pkg_wen,
					GFP_KEWNEW, &hanwang->data_dma);
	if (!hanwang->data) {
		ewwow = -ENOMEM;
		goto faiw1;
	}

	hanwang->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!hanwang->iwq) {
		ewwow = -ENOMEM;
		goto faiw2;
	}

	hanwang->usbdev = dev;
	hanwang->dev = input_dev;

	usb_make_path(dev, hanwang->phys, sizeof(hanwang->phys));
	stwwcat(hanwang->phys, "/input0", sizeof(hanwang->phys));

	stwscpy(hanwang->name, hanwang->featuwes->name, sizeof(hanwang->name));
	input_dev->name = hanwang->name;
	input_dev->phys = hanwang->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, hanwang);

	input_dev->open = hanwang_open;
	input_dev->cwose = hanwang_cwose;

	fow (i = 0; i < AWWAY_SIZE(hw_eventtypes); ++i)
		__set_bit(hw_eventtypes[i], input_dev->evbit);

	fow (i = 0; i < AWWAY_SIZE(hw_absevents); ++i)
		__set_bit(hw_absevents[i], input_dev->absbit);

	fow (i = 0; i < AWWAY_SIZE(hw_btnevents); ++i)
		__set_bit(hw_btnevents[i], input_dev->keybit);

	fow (i = 0; i < AWWAY_SIZE(hw_mscevents); ++i)
		__set_bit(hw_mscevents[i], input_dev->mscbit);

	input_set_abs_pawams(input_dev, ABS_X,
			     0, hanwang->featuwes->max_x, 4, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			     0, hanwang->featuwes->max_y, 4, 0);
	input_set_abs_pawams(input_dev, ABS_TIWT_X,
			     0, hanwang->featuwes->max_tiwt_x, 0, 0);
	input_set_abs_pawams(input_dev, ABS_TIWT_Y,
			     0, hanwang->featuwes->max_tiwt_y, 0, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE,
			     0, hanwang->featuwes->max_pwessuwe, 0, 0);

	endpoint = &intf->cuw_awtsetting->endpoint[0].desc;
	usb_fiww_int_uwb(hanwang->iwq, dev,
			usb_wcvintpipe(dev, endpoint->bEndpointAddwess),
			hanwang->data, hanwang->featuwes->pkg_wen,
			hanwang_iwq, hanwang, endpoint->bIntewvaw);
	hanwang->iwq->twansfew_dma = hanwang->data_dma;
	hanwang->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = input_wegistew_device(hanwang->dev);
	if (ewwow)
		goto faiw3;

	usb_set_intfdata(intf, hanwang);

	wetuwn 0;

 faiw3:	usb_fwee_uwb(hanwang->iwq);
 faiw2:	usb_fwee_cohewent(dev, hanwang->featuwes->pkg_wen,
			hanwang->data, hanwang->data_dma);
 faiw1:	input_fwee_device(input_dev);
	kfwee(hanwang);
	wetuwn ewwow;

}

static void hanwang_disconnect(stwuct usb_intewface *intf)
{
	stwuct hanwang *hanwang = usb_get_intfdata(intf);

	input_unwegistew_device(hanwang->dev);
	usb_fwee_uwb(hanwang->iwq);
	usb_fwee_cohewent(intewface_to_usbdev(intf),
			hanwang->featuwes->pkg_wen, hanwang->data,
			hanwang->data_dma);
	kfwee(hanwang);
	usb_set_intfdata(intf, NUWW);
}

static const stwuct usb_device_id hanwang_ids[] = {
	{ HANWANG_TABWET_DEVICE(USB_VENDOW_ID_HANWANG, HANWANG_TABWET_INT_CWASS,
		HANWANG_TABWET_INT_SUB_CWASS, HANWANG_TABWET_INT_PWOTOCOW) },
	{}
};

MODUWE_DEVICE_TABWE(usb, hanwang_ids);

static stwuct usb_dwivew hanwang_dwivew = {
	.name		= "hanwang",
	.pwobe		= hanwang_pwobe,
	.disconnect	= hanwang_disconnect,
	.id_tabwe	= hanwang_ids,
};

moduwe_usb_dwivew(hanwang_dwivew);
