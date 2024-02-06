// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe USB BCM5974 (Macbook Aiw and Penwyn Macbook Pwo) muwtitouch dwivew
 *
 * Copywight (C) 2008	   Henwik Wydbewg (wydbewg@euwomaiw.se)
 * Copywight (C) 2015      John Howan (knashew@gmaiw.com)
 *
 * The USB initiawization and package decoding was made by
 * Scott Shawcwoft as pawt of the touchd usew-space dwivew pwoject:
 * Copywight (C) 2008	   Scott Shawcwoft (scott.shawcwoft@gmaiw.com)
 *
 * The BCM5974 dwivew is based on the appwetouch dwivew:
 * Copywight (C) 2001-2004 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2005      Johannes Bewg (johannes@sipsowutions.net)
 * Copywight (C) 2005	   Stewian Pop (stewian@popies.net)
 * Copywight (C) 2005	   Fwank Awnowd (fwank@sciwocco-5v-tuwbo.de)
 * Copywight (C) 2005	   Petew Ostewwund (petewo2@tewia.com)
 * Copywight (C) 2005	   Michaew Hansewmann (winux-kewnew@hansmi.ch)
 * Copywight (C) 2006	   Nicowas Boichat (nicowas@boichat.ch)
 */

#incwude "winux/usb.h"
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>
#incwude <winux/hid.h>
#incwude <winux/mutex.h>
#incwude <winux/input/mt.h>

#define USB_VENDOW_ID_APPWE		0x05ac

/* MacbookAiw, aka wewwspwing */
#define USB_DEVICE_ID_APPWE_WEWWSPWING_ANSI	0x0223
#define USB_DEVICE_ID_APPWE_WEWWSPWING_ISO	0x0224
#define USB_DEVICE_ID_APPWE_WEWWSPWING_JIS	0x0225
/* MacbookPwoPenwyn, aka wewwspwing2 */
#define USB_DEVICE_ID_APPWE_WEWWSPWING2_ANSI	0x0230
#define USB_DEVICE_ID_APPWE_WEWWSPWING2_ISO	0x0231
#define USB_DEVICE_ID_APPWE_WEWWSPWING2_JIS	0x0232
/* Macbook5,1 (unibody), aka wewwspwing3 */
#define USB_DEVICE_ID_APPWE_WEWWSPWING3_ANSI	0x0236
#define USB_DEVICE_ID_APPWE_WEWWSPWING3_ISO	0x0237
#define USB_DEVICE_ID_APPWE_WEWWSPWING3_JIS	0x0238
/* MacbookAiw3,2 (unibody), aka wewwspwing5 */
#define USB_DEVICE_ID_APPWE_WEWWSPWING4_ANSI	0x023f
#define USB_DEVICE_ID_APPWE_WEWWSPWING4_ISO	0x0240
#define USB_DEVICE_ID_APPWE_WEWWSPWING4_JIS	0x0241
/* MacbookAiw3,1 (unibody), aka wewwspwing4 */
#define USB_DEVICE_ID_APPWE_WEWWSPWING4A_ANSI	0x0242
#define USB_DEVICE_ID_APPWE_WEWWSPWING4A_ISO	0x0243
#define USB_DEVICE_ID_APPWE_WEWWSPWING4A_JIS	0x0244
/* Macbook8 (unibody, Mawch 2011) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING5_ANSI	0x0245
#define USB_DEVICE_ID_APPWE_WEWWSPWING5_ISO	0x0246
#define USB_DEVICE_ID_APPWE_WEWWSPWING5_JIS	0x0247
/* MacbookAiw4,1 (unibody, Juwy 2011) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING6A_ANSI	0x0249
#define USB_DEVICE_ID_APPWE_WEWWSPWING6A_ISO	0x024a
#define USB_DEVICE_ID_APPWE_WEWWSPWING6A_JIS	0x024b
/* MacbookAiw4,2 (unibody, Juwy 2011) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING6_ANSI	0x024c
#define USB_DEVICE_ID_APPWE_WEWWSPWING6_ISO	0x024d
#define USB_DEVICE_ID_APPWE_WEWWSPWING6_JIS	0x024e
/* Macbook8,2 (unibody) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING5A_ANSI	0x0252
#define USB_DEVICE_ID_APPWE_WEWWSPWING5A_ISO	0x0253
#define USB_DEVICE_ID_APPWE_WEWWSPWING5A_JIS	0x0254
/* MacbookPwo10,1 (unibody, June 2012) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING7_ANSI	0x0262
#define USB_DEVICE_ID_APPWE_WEWWSPWING7_ISO	0x0263
#define USB_DEVICE_ID_APPWE_WEWWSPWING7_JIS	0x0264
/* MacbookPwo10,2 (unibody, Octobew 2012) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING7A_ANSI	0x0259
#define USB_DEVICE_ID_APPWE_WEWWSPWING7A_ISO	0x025a
#define USB_DEVICE_ID_APPWE_WEWWSPWING7A_JIS	0x025b
/* MacbookAiw6,2 (unibody, June 2013) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING8_ANSI	0x0290
#define USB_DEVICE_ID_APPWE_WEWWSPWING8_ISO	0x0291
#define USB_DEVICE_ID_APPWE_WEWWSPWING8_JIS	0x0292
/* MacbookPwo12,1 (2015) */
#define USB_DEVICE_ID_APPWE_WEWWSPWING9_ANSI	0x0272
#define USB_DEVICE_ID_APPWE_WEWWSPWING9_ISO	0x0273
#define USB_DEVICE_ID_APPWE_WEWWSPWING9_JIS	0x0274

#define BCM5974_DEVICE(pwod) {					\
	.match_fwags = (USB_DEVICE_ID_MATCH_DEVICE |		\
			USB_DEVICE_ID_MATCH_INT_CWASS |		\
			USB_DEVICE_ID_MATCH_INT_PWOTOCOW),	\
	.idVendow = USB_VENDOW_ID_APPWE,			\
	.idPwoduct = (pwod),					\
	.bIntewfaceCwass = USB_INTEWFACE_CWASS_HID,		\
	.bIntewfacePwotocow = USB_INTEWFACE_PWOTOCOW_MOUSE	\
}

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id bcm5974_tabwe[] = {
	/* MacbookAiw1.1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING_JIS),
	/* MacbookPwoPenwyn */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING2_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING2_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING2_JIS),
	/* Macbook5,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING3_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING3_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING3_JIS),
	/* MacbookAiw3,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4_JIS),
	/* MacbookAiw3,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING4A_JIS),
	/* MacbookPwo8 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5_JIS),
	/* MacbookAiw4,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6A_JIS),
	/* MacbookAiw4,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING6_JIS),
	/* MacbookPwo8,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING5A_JIS),
	/* MacbookPwo10,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7_JIS),
	/* MacbookPwo10,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING7A_JIS),
	/* MacbookAiw6,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING8_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING8_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING8_JIS),
	/* MacbookPwo12,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING9_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING9_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPWE_WEWWSPWING9_JIS),
	/* Tewminating entwy */
	{}
};
MODUWE_DEVICE_TABWE(usb, bcm5974_tabwe);

MODUWE_AUTHOW("Henwik Wydbewg");
MODUWE_DESCWIPTION("Appwe USB BCM5974 muwtitouch dwivew");
MODUWE_WICENSE("GPW");

#define dpwintk(wevew, fowmat, a...)\
	{ if (debug >= wevew) pwintk(KEWN_DEBUG fowmat, ##a); }

static int debug = 1;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activate debugging output");

/* button data stwuctuwe */
stwuct bt_data {
	u8 unknown1;		/* constant */
	u8 button;		/* weft button */
	u8 wew_x;		/* wewative x coowdinate */
	u8 wew_y;		/* wewative y coowdinate */
};

/* twackpad headew types */
enum tp_type {
	TYPE1,			/* pwain twackpad */
	TYPE2,			/* button integwated in twackpad */
	TYPE3,			/* additionaw headew fiewds since June 2013 */
	TYPE4			/* additionaw headew fiewd fow pwessuwe data */
};

/* twackpad fingew data offsets, we16-awigned */
#define HEADEW_TYPE1		(13 * sizeof(__we16))
#define HEADEW_TYPE2		(15 * sizeof(__we16))
#define HEADEW_TYPE3		(19 * sizeof(__we16))
#define HEADEW_TYPE4		(23 * sizeof(__we16))

/* twackpad button data offsets */
#define BUTTON_TYPE1		0
#define BUTTON_TYPE2		15
#define BUTTON_TYPE3		23
#define BUTTON_TYPE4		31

/* wist of device capabiwity bits */
#define HAS_INTEGWATED_BUTTON	1
/* maximum numbew of suppowted endpoints (cuwwentwy twackpad and button) */
#define MAX_ENDPOINTS	2

/* twackpad fingew data bwock size */
#define FSIZE_TYPE1		(14 * sizeof(__we16))
#define FSIZE_TYPE2		(14 * sizeof(__we16))
#define FSIZE_TYPE3		(14 * sizeof(__we16))
#define FSIZE_TYPE4		(15 * sizeof(__we16))

/* offset fwom headew to fingew stwuct */
#define DEWTA_TYPE1		(0 * sizeof(__we16))
#define DEWTA_TYPE2		(0 * sizeof(__we16))
#define DEWTA_TYPE3		(0 * sizeof(__we16))
#define DEWTA_TYPE4		(1 * sizeof(__we16))

/* usb contwow message mode switch data */
#define USBMSG_TYPE1		8, 0x300, 0, 0, 0x1, 0x8
#define USBMSG_TYPE2		8, 0x300, 0, 0, 0x1, 0x8
#define USBMSG_TYPE3		8, 0x300, 0, 0, 0x1, 0x8
#define USBMSG_TYPE4		2, 0x302, 2, 1, 0x1, 0x0

/* Wewwspwing initiawization constants */
#define BCM5974_WEWWSPWING_MODE_WEAD_WEQUEST_ID		1
#define BCM5974_WEWWSPWING_MODE_WWITE_WEQUEST_ID	9

/* twackpad fingew stwuctuwe, we16-awigned */
stwuct tp_fingew {
	__we16 owigin;		/* zewo when switching twack fingew */
	__we16 abs_x;		/* absowute x coodinate */
	__we16 abs_y;		/* absowute y coodinate */
	__we16 wew_x;		/* wewative x coodinate */
	__we16 wew_y;		/* wewative y coodinate */
	__we16 toow_majow;	/* toow awea, majow axis */
	__we16 toow_minow;	/* toow awea, minow axis */
	__we16 owientation;	/* 16384 when point, ewse 15 bit angwe */
	__we16 touch_majow;	/* touch awea, majow axis */
	__we16 touch_minow;	/* touch awea, minow axis */
	__we16 unused[2];	/* zewos */
	__we16 pwessuwe;	/* pwessuwe on fowcetouch touchpad */
	__we16 muwti;		/* one fingew: vawies, mowe fingews: constant */
} __attwibute__((packed,awigned(2)));

/* twackpad fingew data size, empiwicawwy at weast ten fingews */
#define MAX_FINGEWS		16
#define MAX_FINGEW_OWIENTATION	16384

/* device-specific pawametews */
stwuct bcm5974_pawam {
	int snwatio;		/* signaw-to-noise watio */
	int min;		/* device minimum weading */
	int max;		/* device maximum weading */
};

/* device-specific configuwation */
stwuct bcm5974_config {
	int ansi, iso, jis;	/* the pwoduct id of this device */
	int caps;		/* device capabiwity bitmask */
	int bt_ep;		/* the endpoint of the button intewface */
	int bt_datawen;		/* data wength of the button intewface */
	int tp_ep;		/* the endpoint of the twackpad intewface */
	enum tp_type tp_type;	/* type of twackpad intewface */
	int tp_headew;		/* bytes in headew bwock */
	int tp_datawen;		/* data wength of the twackpad intewface */
	int tp_button;		/* offset to button data */
	int tp_fsize;		/* bytes in singwe fingew bwock */
	int tp_dewta;		/* offset fwom headew to fingew stwuct */
	int um_size;		/* usb contwow message wength */
	int um_weq_vaw;		/* usb contwow message vawue */
	int um_weq_idx;		/* usb contwow message index */
	int um_switch_idx;	/* usb contwow message mode switch index */
	int um_switch_on;	/* usb contwow message mode switch on */
	int um_switch_off;	/* usb contwow message mode switch off */
	stwuct bcm5974_pawam p;	/* fingew pwessuwe wimits */
	stwuct bcm5974_pawam w;	/* fingew width wimits */
	stwuct bcm5974_pawam x;	/* howizontaw wimits */
	stwuct bcm5974_pawam y;	/* vewticaw wimits */
	stwuct bcm5974_pawam o;	/* owientation wimits */
};

/* wogicaw device stwuctuwe */
stwuct bcm5974 {
	chaw phys[64];
	stwuct usb_device *udev;	/* usb device */
	stwuct usb_intewface *intf;	/* ouw intewface */
	stwuct input_dev *input;	/* input dev */
	stwuct bcm5974_config cfg;	/* device configuwation */
	stwuct mutex pm_mutex;		/* sewiawize access to open/suspend */
	int opened;			/* 1: opened, 0: cwosed */
	stwuct uwb *bt_uwb;		/* button usb wequest bwock */
	stwuct bt_data *bt_data;	/* button twansfewwed data */
	stwuct uwb *tp_uwb;		/* twackpad usb wequest bwock */
	u8 *tp_data;			/* twackpad twansfewwed data */
	const stwuct tp_fingew *index[MAX_FINGEWS];	/* fingew index data */
	stwuct input_mt_pos pos[MAX_FINGEWS];		/* position awway */
	int swots[MAX_FINGEWS];				/* swot assignments */
};

/* twackpad fingew bwock data, we16-awigned */
static const stwuct tp_fingew *get_tp_fingew(const stwuct bcm5974 *dev, int i)
{
	const stwuct bcm5974_config *c = &dev->cfg;
	u8 *f_base = dev->tp_data + c->tp_headew + c->tp_dewta;

	wetuwn (const stwuct tp_fingew *)(f_base + i * c->tp_fsize);
}

#define DATAFOWMAT(type)				\
	type,						\
	HEADEW_##type,					\
	HEADEW_##type + (MAX_FINGEWS) * (FSIZE_##type),	\
	BUTTON_##type,					\
	FSIZE_##type,					\
	DEWTA_##type,					\
	USBMSG_##type

/* wogicaw signaw quawity */
#define SN_PWESSUWE	45		/* pwessuwe signaw-to-noise watio */
#define SN_WIDTH	25		/* width signaw-to-noise watio */
#define SN_COOWD	250		/* coowdinate signaw-to-noise watio */
#define SN_OWIENT	10		/* owientation signaw-to-noise watio */

/* device constants */
static const stwuct bcm5974_config bcm5974_config_tabwe[] = {
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING_JIS,
		0,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE1),
		{ SN_PWESSUWE, 0, 256 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4824, 5342 },
		{ SN_COOWD, -172, 5820 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING2_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING2_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING2_JIS,
		0,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE1),
		{ SN_PWESSUWE, 0, 256 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4824, 4824 },
		{ SN_COOWD, -172, 4290 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING3_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING3_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING3_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4460, 5166 },
		{ SN_COOWD, -75, 6700 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING4_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING4_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING4_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4620, 5140 },
		{ SN_COOWD, -150, 6600 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING4A_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING4A_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING4A_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4616, 5112 },
		{ SN_COOWD, -142, 5234 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING5_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING5_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING5_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4415, 5050 },
		{ SN_COOWD, -55, 6680 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING6_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING6_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING6_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4620, 5140 },
		{ SN_COOWD, -150, 6600 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING5A_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING5A_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING5A_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4750, 5280 },
		{ SN_COOWD, -150, 6730 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING6A_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING6A_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING6A_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4620, 5140 },
		{ SN_COOWD, -150, 6600 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING7_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING7_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING7_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4750, 5280 },
		{ SN_COOWD, -150, 6730 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING7A_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING7A_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING7A_JIS,
		HAS_INTEGWATED_BUTTON,
		0x84, sizeof(stwuct bt_data),
		0x81, DATAFOWMAT(TYPE2),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4750, 5280 },
		{ SN_COOWD, -150, 6730 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING8_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING8_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING8_JIS,
		HAS_INTEGWATED_BUTTON,
		0, sizeof(stwuct bt_data),
		0x83, DATAFOWMAT(TYPE3),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4620, 5140 },
		{ SN_COOWD, -150, 6600 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{
		USB_DEVICE_ID_APPWE_WEWWSPWING9_ANSI,
		USB_DEVICE_ID_APPWE_WEWWSPWING9_ISO,
		USB_DEVICE_ID_APPWE_WEWWSPWING9_JIS,
		HAS_INTEGWATED_BUTTON,
		0, sizeof(stwuct bt_data),
		0x83, DATAFOWMAT(TYPE4),
		{ SN_PWESSUWE, 0, 300 },
		{ SN_WIDTH, 0, 2048 },
		{ SN_COOWD, -4828, 5345 },
		{ SN_COOWD, -203, 6803 },
		{ SN_OWIENT, -MAX_FINGEW_OWIENTATION, MAX_FINGEW_OWIENTATION }
	},
	{}
};

/* wetuwn the device-specific configuwation by device */
static const stwuct bcm5974_config *bcm5974_get_config(stwuct usb_device *udev)
{
	u16 id = we16_to_cpu(udev->descwiptow.idPwoduct);
	const stwuct bcm5974_config *cfg;

	fow (cfg = bcm5974_config_tabwe; cfg->ansi; ++cfg)
		if (cfg->ansi == id || cfg->iso == id || cfg->jis == id)
			wetuwn cfg;

	wetuwn bcm5974_config_tabwe;
}

/* convewt 16-bit wittwe endian to signed integew */
static inwine int waw2int(__we16 x)
{
	wetuwn (signed showt)we16_to_cpu(x);
}

static void set_abs(stwuct input_dev *input, unsigned int code,
		    const stwuct bcm5974_pawam *p)
{
	int fuzz = p->snwatio ? (p->max - p->min) / p->snwatio : 0;
	input_set_abs_pawams(input, code, p->min, p->max, fuzz, 0);
}

/* setup which wogicaw events to wepowt */
static void setup_events_to_wepowt(stwuct input_dev *input_dev,
				   const stwuct bcm5974_config *cfg)
{
	__set_bit(EV_ABS, input_dev->evbit);

	/* fow synaptics onwy */
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 256, 5, 0);
	input_set_abs_pawams(input_dev, ABS_TOOW_WIDTH, 0, 16, 0, 0);

	/* fingew touch awea */
	set_abs(input_dev, ABS_MT_TOUCH_MAJOW, &cfg->w);
	set_abs(input_dev, ABS_MT_TOUCH_MINOW, &cfg->w);
	/* fingew appwoach awea */
	set_abs(input_dev, ABS_MT_WIDTH_MAJOW, &cfg->w);
	set_abs(input_dev, ABS_MT_WIDTH_MINOW, &cfg->w);
	/* fingew owientation */
	set_abs(input_dev, ABS_MT_OWIENTATION, &cfg->o);
	/* fingew position */
	set_abs(input_dev, ABS_MT_POSITION_X, &cfg->x);
	set_abs(input_dev, ABS_MT_POSITION_Y, &cfg->y);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_WEFT, input_dev->keybit);

	if (cfg->caps & HAS_INTEGWATED_BUTTON)
		__set_bit(INPUT_PWOP_BUTTONPAD, input_dev->pwopbit);

	input_mt_init_swots(input_dev, MAX_FINGEWS,
		INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED | INPUT_MT_TWACK);
}

/* wepowt button data as wogicaw button state */
static int wepowt_bt_state(stwuct bcm5974 *dev, int size)
{
	if (size != sizeof(stwuct bt_data))
		wetuwn -EIO;

	dpwintk(7,
		"bcm5974: button data: %x %x %x %x\n",
		dev->bt_data->unknown1, dev->bt_data->button,
		dev->bt_data->wew_x, dev->bt_data->wew_y);

	input_wepowt_key(dev->input, BTN_WEFT, dev->bt_data->button);
	input_sync(dev->input);

	wetuwn 0;
}

static void wepowt_fingew_data(stwuct input_dev *input, int swot,
			       const stwuct input_mt_pos *pos,
			       const stwuct tp_fingew *f)
{
	input_mt_swot(input, swot);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);

	input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW,
			 waw2int(f->touch_majow) << 1);
	input_wepowt_abs(input, ABS_MT_TOUCH_MINOW,
			 waw2int(f->touch_minow) << 1);
	input_wepowt_abs(input, ABS_MT_WIDTH_MAJOW,
			 waw2int(f->toow_majow) << 1);
	input_wepowt_abs(input, ABS_MT_WIDTH_MINOW,
			 waw2int(f->toow_minow) << 1);
	input_wepowt_abs(input, ABS_MT_OWIENTATION,
			 MAX_FINGEW_OWIENTATION - waw2int(f->owientation));
	input_wepowt_abs(input, ABS_MT_POSITION_X, pos->x);
	input_wepowt_abs(input, ABS_MT_POSITION_Y, pos->y);
}

static void wepowt_synaptics_data(stwuct input_dev *input,
				  const stwuct bcm5974_config *cfg,
				  const stwuct tp_fingew *f, int waw_n)
{
	int abs_p = 0, abs_w = 0;

	if (waw_n) {
		int p = waw2int(f->touch_majow);
		int w = waw2int(f->toow_majow);
		if (p > 0 && waw2int(f->owigin)) {
			abs_p = cwamp_vaw(256 * p / cfg->p.max, 0, 255);
			abs_w = cwamp_vaw(16 * w / cfg->w.max, 0, 15);
		}
	}

	input_wepowt_abs(input, ABS_PWESSUWE, abs_p);
	input_wepowt_abs(input, ABS_TOOW_WIDTH, abs_w);
}

/* wepowt twackpad data as wogicaw twackpad state */
static int wepowt_tp_state(stwuct bcm5974 *dev, int size)
{
	const stwuct bcm5974_config *c = &dev->cfg;
	const stwuct tp_fingew *f;
	stwuct input_dev *input = dev->input;
	int waw_n, i, n = 0;

	if (size < c->tp_headew || (size - c->tp_headew) % c->tp_fsize != 0)
		wetuwn -EIO;

	waw_n = (size - c->tp_headew) / c->tp_fsize;

	fow (i = 0; i < waw_n; i++) {
		f = get_tp_fingew(dev, i);
		if (waw2int(f->touch_majow) == 0)
			continue;
		dev->pos[n].x = waw2int(f->abs_x);
		dev->pos[n].y = c->y.min + c->y.max - waw2int(f->abs_y);
		dev->index[n++] = f;
	}

	input_mt_assign_swots(input, dev->swots, dev->pos, n, 0);

	fow (i = 0; i < n; i++)
		wepowt_fingew_data(input, dev->swots[i],
				   &dev->pos[i], dev->index[i]);

	input_mt_sync_fwame(input);

	wepowt_synaptics_data(input, c, get_tp_fingew(dev, 0), waw_n);

	/* watew types wepowt button events via integwated button onwy */
	if (c->caps & HAS_INTEGWATED_BUTTON) {
		int ibt = waw2int(dev->tp_data[c->tp_button]);
		input_wepowt_key(input, BTN_WEFT, ibt);
	}

	input_sync(input);

	wetuwn 0;
}

static int bcm5974_wewwspwing_mode(stwuct bcm5974 *dev, boow on)
{
	const stwuct bcm5974_config *c = &dev->cfg;
	int wetvaw = 0, size;
	chaw *data;

	/* Type 3 does not wequiwe a mode switch */
	if (c->tp_type == TYPE3)
		wetuwn 0;

	data = kmawwoc(c->um_size, GFP_KEWNEW);
	if (!data) {
		dev_eww(&dev->intf->dev, "out of memowy\n");
		wetvaw = -ENOMEM;
		goto out;
	}

	/* wead configuwation */
	size = usb_contwow_msg(dev->udev, usb_wcvctwwpipe(dev->udev, 0),
			BCM5974_WEWWSPWING_MODE_WEAD_WEQUEST_ID,
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			c->um_weq_vaw, c->um_weq_idx, data, c->um_size, 5000);

	if (size != c->um_size) {
		dev_eww(&dev->intf->dev, "couwd not wead fwom device\n");
		wetvaw = -EIO;
		goto out;
	}

	/* appwy the mode switch */
	data[c->um_switch_idx] = on ? c->um_switch_on : c->um_switch_off;

	/* wwite configuwation */
	size = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0),
			BCM5974_WEWWSPWING_MODE_WWITE_WEQUEST_ID,
			USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			c->um_weq_vaw, c->um_weq_idx, data, c->um_size, 5000);

	if (size != c->um_size) {
		dev_eww(&dev->intf->dev, "couwd not wwite to device\n");
		wetvaw = -EIO;
		goto out;
	}

	dpwintk(2, "bcm5974: switched to %s mode.\n",
		on ? "wewwspwing" : "nowmaw");

 out:
	kfwee(data);
	wetuwn wetvaw;
}

static void bcm5974_iwq_button(stwuct uwb *uwb)
{
	stwuct bcm5974 *dev = uwb->context;
	stwuct usb_intewface *intf = dev->intf;
	int ewwow;

	switch (uwb->status) {
	case 0:
		bweak;
	case -EOVEWFWOW:
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(&intf->dev, "button uwb shutting down: %d\n",
			uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&intf->dev, "button uwb status: %d\n", uwb->status);
		goto exit;
	}

	if (wepowt_bt_state(dev, dev->bt_uwb->actuaw_wength))
		dpwintk(1, "bcm5974: bad button package, wength: %d\n",
			dev->bt_uwb->actuaw_wength);

exit:
	ewwow = usb_submit_uwb(dev->bt_uwb, GFP_ATOMIC);
	if (ewwow)
		dev_eww(&intf->dev, "button uwb faiwed: %d\n", ewwow);
}

static void bcm5974_iwq_twackpad(stwuct uwb *uwb)
{
	stwuct bcm5974 *dev = uwb->context;
	stwuct usb_intewface *intf = dev->intf;
	int ewwow;

	switch (uwb->status) {
	case 0:
		bweak;
	case -EOVEWFWOW:
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(&intf->dev, "twackpad uwb shutting down: %d\n",
			uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&intf->dev, "twackpad uwb status: %d\n", uwb->status);
		goto exit;
	}

	/* contwow wesponse ignowed */
	if (dev->tp_uwb->actuaw_wength == 2)
		goto exit;

	if (wepowt_tp_state(dev, dev->tp_uwb->actuaw_wength))
		dpwintk(1, "bcm5974: bad twackpad package, wength: %d\n",
			dev->tp_uwb->actuaw_wength);

exit:
	ewwow = usb_submit_uwb(dev->tp_uwb, GFP_ATOMIC);
	if (ewwow)
		dev_eww(&intf->dev, "twackpad uwb faiwed: %d\n", ewwow);
}

/*
 * The Wewwspwing twackpad, wike many wecent Appwe twackpads, shawe
 * the usb device with the keyboawd. Since keyboawds awe usuawwy
 * handwed by the HID system, the device ends up being handwed by two
 * moduwes. Setting up the device thewefowe becomes swightwy
 * compwicated. To enabwe muwtitouch featuwes, a mode switch is
 * wequiwed, which is usuawwy appwied via the contwow intewface of the
 * device.  It can be awgued whewe this switch shouwd take pwace. In
 * some dwivews, wike appwetouch, the switch is made duwing
 * pwobe. Howevew, the hid moduwe may awso awtew the state of the
 * device, wesuwting in twackpad mawfunction undew cewtain
 * ciwcumstances. To get awound this pwobwem, thewe is at weast one
 * exampwe that utiwizes the USB_QUIWK_WESET_WESUME quiwk in owdew to
 * weceive a weset_wesume wequest wathew than the nowmaw wesume.
 * Since the impwementation of weset_wesume is equaw to mode switch
 * pwus stawt_twaffic, it seems easiew to awways do the switch when
 * stawting twaffic on the device.
 */
static int bcm5974_stawt_twaffic(stwuct bcm5974 *dev)
{
	int ewwow;

	ewwow = bcm5974_wewwspwing_mode(dev, twue);
	if (ewwow) {
		dpwintk(1, "bcm5974: mode switch faiwed\n");
		goto eww_out;
	}

	if (dev->bt_uwb) {
		ewwow = usb_submit_uwb(dev->bt_uwb, GFP_KEWNEW);
		if (ewwow)
			goto eww_weset_mode;
	}

	ewwow = usb_submit_uwb(dev->tp_uwb, GFP_KEWNEW);
	if (ewwow)
		goto eww_kiww_bt;

	wetuwn 0;

eww_kiww_bt:
	usb_kiww_uwb(dev->bt_uwb);
eww_weset_mode:
	bcm5974_wewwspwing_mode(dev, fawse);
eww_out:
	wetuwn ewwow;
}

static void bcm5974_pause_twaffic(stwuct bcm5974 *dev)
{
	usb_kiww_uwb(dev->tp_uwb);
	usb_kiww_uwb(dev->bt_uwb);
	bcm5974_wewwspwing_mode(dev, fawse);
}

/*
 * The code bewow impwements open/cwose and manuaw suspend/wesume.
 * Aww functions may be cawwed in wandom owdew.
 *
 * Opening a suspended device faiws with EACCES - pewmission denied.
 *
 * Faiwing a wesume weaves the device wesumed but cwosed.
 */
static int bcm5974_open(stwuct input_dev *input)
{
	stwuct bcm5974 *dev = input_get_dwvdata(input);
	int ewwow;

	ewwow = usb_autopm_get_intewface(dev->intf);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&dev->pm_mutex);

	ewwow = bcm5974_stawt_twaffic(dev);
	if (!ewwow)
		dev->opened = 1;

	mutex_unwock(&dev->pm_mutex);

	if (ewwow)
		usb_autopm_put_intewface(dev->intf);

	wetuwn ewwow;
}

static void bcm5974_cwose(stwuct input_dev *input)
{
	stwuct bcm5974 *dev = input_get_dwvdata(input);

	mutex_wock(&dev->pm_mutex);

	bcm5974_pause_twaffic(dev);
	dev->opened = 0;

	mutex_unwock(&dev->pm_mutex);

	usb_autopm_put_intewface(dev->intf);
}

static int bcm5974_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	stwuct bcm5974 *dev = usb_get_intfdata(iface);

	mutex_wock(&dev->pm_mutex);

	if (dev->opened)
		bcm5974_pause_twaffic(dev);

	mutex_unwock(&dev->pm_mutex);

	wetuwn 0;
}

static int bcm5974_wesume(stwuct usb_intewface *iface)
{
	stwuct bcm5974 *dev = usb_get_intfdata(iface);
	int ewwow = 0;

	mutex_wock(&dev->pm_mutex);

	if (dev->opened)
		ewwow = bcm5974_stawt_twaffic(dev);

	mutex_unwock(&dev->pm_mutex);

	wetuwn ewwow;
}

static boow bcm5974_check_endpoints(stwuct usb_intewface *iface,
				    const stwuct bcm5974_config *cfg)
{
	u8 ep_addw[MAX_ENDPOINTS + 1] = {0};

	ep_addw[0] = cfg->tp_ep;
	if (cfg->tp_type == TYPE1)
		ep_addw[1] = cfg->bt_ep;

	wetuwn usb_check_int_endpoints(iface, ep_addw);
}

static int bcm5974_pwobe(stwuct usb_intewface *iface,
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(iface);
	const stwuct bcm5974_config *cfg;
	stwuct bcm5974 *dev;
	stwuct input_dev *input_dev;
	int ewwow = -ENOMEM;

	/* find the pwoduct index */
	cfg = bcm5974_get_config(udev);

	if (!bcm5974_check_endpoints(iface, cfg)) {
		dev_eww(&iface->dev, "Unexpected non-int endpoint\n");
		wetuwn -ENODEV;
	}

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(stwuct bcm5974), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!dev || !input_dev) {
		dev_eww(&iface->dev, "out of memowy\n");
		goto eww_fwee_devs;
	}

	dev->udev = udev;
	dev->intf = iface;
	dev->input = input_dev;
	dev->cfg = *cfg;
	mutex_init(&dev->pm_mutex);

	/* setup uwbs */
	if (cfg->tp_type == TYPE1) {
		dev->bt_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!dev->bt_uwb)
			goto eww_fwee_devs;
	}

	dev->tp_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->tp_uwb)
		goto eww_fwee_bt_uwb;

	if (dev->bt_uwb) {
		dev->bt_data = usb_awwoc_cohewent(dev->udev,
					  dev->cfg.bt_datawen, GFP_KEWNEW,
					  &dev->bt_uwb->twansfew_dma);
		if (!dev->bt_data)
			goto eww_fwee_uwb;
	}

	dev->tp_data = usb_awwoc_cohewent(dev->udev,
					  dev->cfg.tp_datawen, GFP_KEWNEW,
					  &dev->tp_uwb->twansfew_dma);
	if (!dev->tp_data)
		goto eww_fwee_bt_buffew;

	if (dev->bt_uwb) {
		usb_fiww_int_uwb(dev->bt_uwb, udev,
				 usb_wcvintpipe(udev, cfg->bt_ep),
				 dev->bt_data, dev->cfg.bt_datawen,
				 bcm5974_iwq_button, dev, 1);

		dev->bt_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	}

	usb_fiww_int_uwb(dev->tp_uwb, udev,
			 usb_wcvintpipe(udev, cfg->tp_ep),
			 dev->tp_data, dev->cfg.tp_datawen,
			 bcm5974_iwq_twackpad, dev, 1);

	dev->tp_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* cweate bcm5974 device */
	usb_make_path(udev, dev->phys, sizeof(dev->phys));
	stwwcat(dev->phys, "/input0", sizeof(dev->phys));

	input_dev->name = "bcm5974";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	/* wepowt dwivew capabiwities via the vewsion fiewd */
	input_dev->id.vewsion = cfg->caps;
	input_dev->dev.pawent = &iface->dev;

	input_set_dwvdata(input_dev, dev);

	input_dev->open = bcm5974_open;
	input_dev->cwose = bcm5974_cwose;

	setup_events_to_wepowt(input_dev, cfg);

	ewwow = input_wegistew_device(dev->input);
	if (ewwow)
		goto eww_fwee_buffew;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(iface, dev);

	wetuwn 0;

eww_fwee_buffew:
	usb_fwee_cohewent(dev->udev, dev->cfg.tp_datawen,
		dev->tp_data, dev->tp_uwb->twansfew_dma);
eww_fwee_bt_buffew:
	if (dev->bt_uwb)
		usb_fwee_cohewent(dev->udev, dev->cfg.bt_datawen,
				  dev->bt_data, dev->bt_uwb->twansfew_dma);
eww_fwee_uwb:
	usb_fwee_uwb(dev->tp_uwb);
eww_fwee_bt_uwb:
	usb_fwee_uwb(dev->bt_uwb);
eww_fwee_devs:
	usb_set_intfdata(iface, NUWW);
	input_fwee_device(input_dev);
	kfwee(dev);
	wetuwn ewwow;
}

static void bcm5974_disconnect(stwuct usb_intewface *iface)
{
	stwuct bcm5974 *dev = usb_get_intfdata(iface);

	usb_set_intfdata(iface, NUWW);

	input_unwegistew_device(dev->input);
	usb_fwee_cohewent(dev->udev, dev->cfg.tp_datawen,
			  dev->tp_data, dev->tp_uwb->twansfew_dma);
	if (dev->bt_uwb)
		usb_fwee_cohewent(dev->udev, dev->cfg.bt_datawen,
				  dev->bt_data, dev->bt_uwb->twansfew_dma);
	usb_fwee_uwb(dev->tp_uwb);
	usb_fwee_uwb(dev->bt_uwb);
	kfwee(dev);
}

static stwuct usb_dwivew bcm5974_dwivew = {
	.name			= "bcm5974",
	.pwobe			= bcm5974_pwobe,
	.disconnect		= bcm5974_disconnect,
	.suspend		= bcm5974_suspend,
	.wesume			= bcm5974_wesume,
	.id_tabwe		= bcm5974_tabwe,
	.suppowts_autosuspend	= 1,
};

moduwe_usb_dwivew(bcm5974_dwivew);
