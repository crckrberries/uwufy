// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 * usbtouchscween.c
 * Dwivew fow USB Touchscweens, suppowting those devices:
 *  - eGawax Touchkit
 *    incwudes eTuwboTouch CT-410/510/700
 *  - 3M/Micwotouch  EX II sewies
 *  - ITM
 *  - PanJit TouchSet
 *  - eTuwboTouch
 *  - Gunze AHW61
 *  - DMC TSC-10/25
 *  - IWTOUCHSYSTEMS/UNITOP
 *  - IdeawTEK UWTC1000
 *  - Genewaw Touch
 *  - GoTop Supew_Q2/GogoPen/PenPowew tabwets
 *  - JASTEC USB touch contwowwew/DigiTech DTW-02U
 *  - Zytwonic capacitive touchscween
 *  - NEXIO/iNexio
 *  - Ewo TouchSystems 2700 IntewwiTouch
 *  - EasyTouch USB Duaw/Muwti touch contwowwew fwom Data Moduw
 *
 * Copywight (C) 2004-2007 by Daniew Witz <daniew.witz@gmx.ch>
 * Copywight (C) by Todd E. Johnson (mtouchusb.c)
 *
 * Dwivew is based on touchkitusb.c
 * - ITM pawts awe fwom itmtouch.c
 * - 3M pawts awe fwom mtouchusb.c
 * - PanJit pawts awe fwom an unmewged dwivew by Wanswott Gish
 * - DMC TSC 10/25 awe fwom Howgew Schuwig, with ideas fwom an unmewged
 *   dwivew fwom Mawius Vowwmew
 *
 *****************************************************************************/

//#define DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <winux/hid.h>
#incwude <winux/mutex.h>

static boow swap_xy;
moduwe_pawam(swap_xy, boow, 0644);
MODUWE_PAWM_DESC(swap_xy, "If set X and Y axes awe swapped.");

static boow hwcawib_xy;
moduwe_pawam(hwcawib_xy, boow, 0644);
MODUWE_PAWM_DESC(hwcawib_xy, "If set hw-cawibwated X/Y awe used if avaiwabwe");

/* device specifc data/functions */
stwuct usbtouch_usb;
stwuct usbtouch_device_info {
	int min_xc, max_xc;
	int min_yc, max_yc;
	int min_pwess, max_pwess;
	int wept_size;

	/*
	 * Awways sewvice the USB devices iwq not just when the input device is
	 * open. This is usefuw when devices have a watchdog which pwevents us
	 * fwom pewiodicawwy powwing the device. Weave this unset unwess youw
	 * touchscween device wequiwes it, as it does consume mowe of the USB
	 * bandwidth.
	 */
	boow iwq_awways;

	void (*pwocess_pkt) (stwuct usbtouch_usb *usbtouch, unsigned chaw *pkt, int wen);

	/*
	 * used to get the packet wen. possibwe wetuwn vawues:
	 * > 0: packet wen
	 * = 0: skip one byte
	 * < 0: -wetuwn vawue mowe bytes needed
	 */
	int  (*get_pkt_wen) (unsigned chaw *pkt, int wen);

	int  (*wead_data)   (stwuct usbtouch_usb *usbtouch, unsigned chaw *pkt);
	int  (*awwoc)       (stwuct usbtouch_usb *usbtouch);
	int  (*init)        (stwuct usbtouch_usb *usbtouch);
	void (*exit)	    (stwuct usbtouch_usb *usbtouch);
};

/* a usbtouch device */
stwuct usbtouch_usb {
	unsigned chaw *data;
	dma_addw_t data_dma;
	int data_size;
	unsigned chaw *buffew;
	int buf_wen;
	stwuct uwb *iwq;
	stwuct usb_intewface *intewface;
	stwuct input_dev *input;
	stwuct usbtouch_device_info *type;
	stwuct mutex pm_mutex;  /* sewiawize access to open/suspend */
	boow is_open;
	chaw name[128];
	chaw phys[64];
	void *pwiv;

	int x, y;
	int touch, pwess;
};


/* device types */
enum {
	DEVTYPE_IGNOWE = -1,
	DEVTYPE_EGAWAX,
	DEVTYPE_PANJIT,
	DEVTYPE_3M,
	DEVTYPE_ITM,
	DEVTYPE_ETUWBO,
	DEVTYPE_GUNZE,
	DEVTYPE_DMC_TSC10,
	DEVTYPE_IWTOUCH,
	DEVTYPE_IWTOUCH_HIWES,
	DEVTYPE_IDEAWTEK,
	DEVTYPE_GENEWAW_TOUCH,
	DEVTYPE_GOTOP,
	DEVTYPE_JASTEC,
	DEVTYPE_E2I,
	DEVTYPE_ZYTWONIC,
	DEVTYPE_TC45USB,
	DEVTYPE_NEXIO,
	DEVTYPE_EWO,
	DEVTYPE_ETOUCH,
};

#define USB_DEVICE_HID_CWASS(vend, pwod) \
	.match_fwags = USB_DEVICE_ID_MATCH_INT_CWASS \
		| USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bIntewfaceCwass = USB_INTEWFACE_CWASS_HID

static const stwuct usb_device_id usbtouch_devices[] = {
#ifdef CONFIG_TOUCHSCWEEN_USB_EGAWAX
	/* ignowe the HID capabwe devices, handwed by usbhid */
	{USB_DEVICE_HID_CWASS(0x0eef, 0x0001), .dwivew_info = DEVTYPE_IGNOWE},
	{USB_DEVICE_HID_CWASS(0x0eef, 0x0002), .dwivew_info = DEVTYPE_IGNOWE},

	/* nowmaw device IDs */
	{USB_DEVICE(0x3823, 0x0001), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x3823, 0x0002), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x0123, 0x0001), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x0eef, 0x0001), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x0eef, 0x0002), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x1234, 0x0001), .dwivew_info = DEVTYPE_EGAWAX},
	{USB_DEVICE(0x1234, 0x0002), .dwivew_info = DEVTYPE_EGAWAX},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_PANJIT
	{USB_DEVICE(0x134c, 0x0001), .dwivew_info = DEVTYPE_PANJIT},
	{USB_DEVICE(0x134c, 0x0002), .dwivew_info = DEVTYPE_PANJIT},
	{USB_DEVICE(0x134c, 0x0003), .dwivew_info = DEVTYPE_PANJIT},
	{USB_DEVICE(0x134c, 0x0004), .dwivew_info = DEVTYPE_PANJIT},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_3M
	{USB_DEVICE(0x0596, 0x0001), .dwivew_info = DEVTYPE_3M},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ITM
	{USB_DEVICE(0x0403, 0xf9e9), .dwivew_info = DEVTYPE_ITM},
	{USB_DEVICE(0x16e3, 0xf9e9), .dwivew_info = DEVTYPE_ITM},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ETUWBO
	{USB_DEVICE(0x1234, 0x5678), .dwivew_info = DEVTYPE_ETUWBO},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GUNZE
	{USB_DEVICE(0x0637, 0x0001), .dwivew_info = DEVTYPE_GUNZE},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_DMC_TSC10
	{USB_DEVICE(0x0afa, 0x03e8), .dwivew_info = DEVTYPE_DMC_TSC10},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_IWTOUCH
	{USB_DEVICE(0x255e, 0x0001), .dwivew_info = DEVTYPE_IWTOUCH},
	{USB_DEVICE(0x595a, 0x0001), .dwivew_info = DEVTYPE_IWTOUCH},
	{USB_DEVICE(0x6615, 0x0001), .dwivew_info = DEVTYPE_IWTOUCH},
	{USB_DEVICE(0x6615, 0x0012), .dwivew_info = DEVTYPE_IWTOUCH_HIWES},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_IDEAWTEK
	{USB_DEVICE(0x1391, 0x1000), .dwivew_info = DEVTYPE_IDEAWTEK},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GENEWAW_TOUCH
	{USB_DEVICE(0x0dfc, 0x0001), .dwivew_info = DEVTYPE_GENEWAW_TOUCH},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GOTOP
	{USB_DEVICE(0x08f2, 0x007f), .dwivew_info = DEVTYPE_GOTOP},
	{USB_DEVICE(0x08f2, 0x00ce), .dwivew_info = DEVTYPE_GOTOP},
	{USB_DEVICE(0x08f2, 0x00f4), .dwivew_info = DEVTYPE_GOTOP},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_JASTEC
	{USB_DEVICE(0x0f92, 0x0001), .dwivew_info = DEVTYPE_JASTEC},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_E2I
	{USB_DEVICE(0x1ac7, 0x0001), .dwivew_info = DEVTYPE_E2I},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ZYTWONIC
	{USB_DEVICE(0x14c8, 0x0003), .dwivew_info = DEVTYPE_ZYTWONIC},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ETT_TC45USB
	/* TC5UH */
	{USB_DEVICE(0x0664, 0x0309), .dwivew_info = DEVTYPE_TC45USB},
	/* TC4UM */
	{USB_DEVICE(0x0664, 0x0306), .dwivew_info = DEVTYPE_TC45USB},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_NEXIO
	/* data intewface onwy */
	{USB_DEVICE_AND_INTEWFACE_INFO(0x10f0, 0x2002, 0x0a, 0x00, 0x00),
		.dwivew_info = DEVTYPE_NEXIO},
	{USB_DEVICE_AND_INTEWFACE_INFO(0x1870, 0x0001, 0x0a, 0x00, 0x00),
		.dwivew_info = DEVTYPE_NEXIO},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_EWO
	{USB_DEVICE(0x04e7, 0x0020), .dwivew_info = DEVTYPE_EWO},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_EASYTOUCH
	{USB_DEVICE(0x7374, 0x0001), .dwivew_info = DEVTYPE_ETOUCH},
#endif

	{}
};


/*****************************************************************************
 * e2i Pawt
 */

#ifdef CONFIG_TOUCHSCWEEN_USB_E2I
static int e2i_init(stwuct usbtouch_usb *usbtouch)
{
	int wet;
	stwuct usb_device *udev = intewface_to_usbdev(usbtouch->intewface);

	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
	                      0x01, 0x02, 0x0000, 0x0081,
	                      NUWW, 0, USB_CTWW_SET_TIMEOUT);

	dev_dbg(&usbtouch->intewface->dev,
		"%s - usb_contwow_msg - E2I_WESET - bytes|eww: %d\n",
		__func__, wet);
	wetuwn wet;
}

static int e2i_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	int tmp = (pkt[0] << 8) | pkt[1];
	dev->x  = (pkt[2] << 8) | pkt[3];
	dev->y  = (pkt[4] << 8) | pkt[5];

	tmp = tmp - 0xA000;
	dev->touch = (tmp > 0);
	dev->pwess = (tmp > 0 ? tmp : 0);

	wetuwn 1;
}
#endif


/*****************************************************************************
 * eGawax pawt
 */

#ifdef CONFIG_TOUCHSCWEEN_USB_EGAWAX

#ifndef MUWTI_PACKET
#define MUWTI_PACKET
#endif

#define EGAWAX_PKT_TYPE_MASK		0xFE
#define EGAWAX_PKT_TYPE_WEPT		0x80
#define EGAWAX_PKT_TYPE_DIAG		0x0A

static int egawax_init(stwuct usbtouch_usb *usbtouch)
{
	int wet, i;
	unsigned chaw *buf;
	stwuct usb_device *udev = intewface_to_usbdev(usbtouch->intewface);

	/*
	 * An eGawax diagnostic packet kicks the device into using the wight
	 * pwotocow.  We send a "check active" packet.  The wesponse wiww be
	 * wead watew and ignowed.
	 */

	buf = kmawwoc(3, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = EGAWAX_PKT_TYPE_DIAG;
	buf[1] = 1;	/* wength */
	buf[2] = 'A';	/* command - check active */

	fow (i = 0; i < 3; i++) {
		wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				      0,
				      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				      0, 0, buf, 3,
				      USB_CTWW_SET_TIMEOUT);
		if (wet >= 0) {
			wet = 0;
			bweak;
		}
		if (wet != -EPIPE)
			bweak;
	}

	kfwee(buf);

	wetuwn wet;
}

static int egawax_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	if ((pkt[0] & EGAWAX_PKT_TYPE_MASK) != EGAWAX_PKT_TYPE_WEPT)
		wetuwn 0;

	dev->x = ((pkt[3] & 0x0F) << 7) | (pkt[4] & 0x7F);
	dev->y = ((pkt[1] & 0x0F) << 7) | (pkt[2] & 0x7F);
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}

static int egawax_get_pkt_wen(unsigned chaw *buf, int wen)
{
	switch (buf[0] & EGAWAX_PKT_TYPE_MASK) {
	case EGAWAX_PKT_TYPE_WEPT:
		wetuwn 5;

	case EGAWAX_PKT_TYPE_DIAG:
		if (wen < 2)
			wetuwn -1;

		wetuwn buf[1] + 2;
	}

	wetuwn 0;
}
#endif

/*****************************************************************************
 * EasyTouch pawt
 */

#ifdef CONFIG_TOUCHSCWEEN_USB_EASYTOUCH

#ifndef MUWTI_PACKET
#define MUWTI_PACKET
#endif

#define ETOUCH_PKT_TYPE_MASK		0xFE
#define ETOUCH_PKT_TYPE_WEPT		0x80
#define ETOUCH_PKT_TYPE_WEPT2		0xB0
#define ETOUCH_PKT_TYPE_DIAG		0x0A

static int etouch_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	if ((pkt[0] & ETOUCH_PKT_TYPE_MASK) != ETOUCH_PKT_TYPE_WEPT &&
		(pkt[0] & ETOUCH_PKT_TYPE_MASK) != ETOUCH_PKT_TYPE_WEPT2)
		wetuwn 0;

	dev->x = ((pkt[1] & 0x1F) << 7) | (pkt[2] & 0x7F);
	dev->y = ((pkt[3] & 0x1F) << 7) | (pkt[4] & 0x7F);
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}

static int etouch_get_pkt_wen(unsigned chaw *buf, int wen)
{
	switch (buf[0] & ETOUCH_PKT_TYPE_MASK) {
	case ETOUCH_PKT_TYPE_WEPT:
	case ETOUCH_PKT_TYPE_WEPT2:
		wetuwn 5;

	case ETOUCH_PKT_TYPE_DIAG:
		if (wen < 2)
			wetuwn -1;

		wetuwn buf[1] + 2;
	}

	wetuwn 0;
}
#endif

/*****************************************************************************
 * PanJit Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_PANJIT
static int panjit_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = ((pkt[2] & 0x0F) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x0F) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}
#endif


/*****************************************************************************
 * 3M/Micwotouch Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_3M

#define MTOUCHUSB_ASYNC_WEPOWT          1
#define MTOUCHUSB_WESET                 7
#define MTOUCHUSB_WEQ_CTWWWW_ID         10

#define MTOUCHUSB_WEQ_CTWWWW_ID_WEN	16

static int mtouch_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	if (hwcawib_xy) {
		dev->x = (pkt[4] << 8) | pkt[3];
		dev->y = 0xffff - ((pkt[6] << 8) | pkt[5]);
	} ewse {
		dev->x = (pkt[8] << 8) | pkt[7];
		dev->y = (pkt[10] << 8) | pkt[9];
	}
	dev->touch = (pkt[2] & 0x40) ? 1 : 0;

	wetuwn 1;
}

stwuct mtouch_pwiv {
	u8 fw_wev_majow;
	u8 fw_wev_minow;
};

static ssize_t mtouch_fiwmwawe_wev_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *output)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usbtouch_usb *usbtouch = usb_get_intfdata(intf);
	stwuct mtouch_pwiv *pwiv = usbtouch->pwiv;

	wetuwn sysfs_emit(output, "%1x.%1x\n",
			  pwiv->fw_wev_majow, pwiv->fw_wev_minow);
}
static DEVICE_ATTW(fiwmwawe_wev, 0444, mtouch_fiwmwawe_wev_show, NUWW);

static stwuct attwibute *mtouch_attws[] = {
	&dev_attw_fiwmwawe_wev.attw,
	NUWW
};

static const stwuct attwibute_gwoup mtouch_attw_gwoup = {
	.attws = mtouch_attws,
};

static int mtouch_get_fw_wevision(stwuct usbtouch_usb *usbtouch)
{
	stwuct usb_device *udev = intewface_to_usbdev(usbtouch->intewface);
	stwuct mtouch_pwiv *pwiv = usbtouch->pwiv;
	u8 *buf;
	int wet;

	buf = kzawwoc(MTOUCHUSB_WEQ_CTWWWW_ID_WEN, GFP_NOIO);
	if (!buf)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			      MTOUCHUSB_WEQ_CTWWWW_ID,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0, 0, buf, MTOUCHUSB_WEQ_CTWWWW_ID_WEN,
			      USB_CTWW_SET_TIMEOUT);
	if (wet != MTOUCHUSB_WEQ_CTWWWW_ID_WEN) {
		dev_wawn(&usbtouch->intewface->dev,
			 "Faiwed to wead FW wev: %d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto fwee;
	}

	pwiv->fw_wev_majow = buf[3];
	pwiv->fw_wev_minow = buf[4];

	wet = 0;

fwee:
	kfwee(buf);
	wetuwn wet;
}

static int mtouch_awwoc(stwuct usbtouch_usb *usbtouch)
{
	int wet;

	usbtouch->pwiv = kmawwoc(sizeof(stwuct mtouch_pwiv), GFP_KEWNEW);
	if (!usbtouch->pwiv)
		wetuwn -ENOMEM;

	wet = sysfs_cweate_gwoup(&usbtouch->intewface->dev.kobj,
				 &mtouch_attw_gwoup);
	if (wet) {
		kfwee(usbtouch->pwiv);
		usbtouch->pwiv = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int mtouch_init(stwuct usbtouch_usb *usbtouch)
{
	int wet, i;
	stwuct usb_device *udev = intewface_to_usbdev(usbtouch->intewface);

	wet = mtouch_get_fw_wevision(usbtouch);
	if (wet)
		wetuwn wet;

	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
	                      MTOUCHUSB_WESET,
	                      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
	                      1, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
	dev_dbg(&usbtouch->intewface->dev,
		"%s - usb_contwow_msg - MTOUCHUSB_WESET - bytes|eww: %d\n",
		__func__, wet);
	if (wet < 0)
		wetuwn wet;
	msweep(150);

	fow (i = 0; i < 3; i++) {
		wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				      MTOUCHUSB_ASYNC_WEPOWT,
				      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				      1, 1, NUWW, 0, USB_CTWW_SET_TIMEOUT);
		dev_dbg(&usbtouch->intewface->dev,
			"%s - usb_contwow_msg - MTOUCHUSB_ASYNC_WEPOWT - bytes|eww: %d\n",
			__func__, wet);
		if (wet >= 0)
			bweak;
		if (wet != -EPIPE)
			wetuwn wet;
	}

	/* Defauwt min/max xy awe the waw vawues, ovewwide if using hw-cawib */
	if (hwcawib_xy) {
		input_set_abs_pawams(usbtouch->input, ABS_X, 0, 0xffff, 0, 0);
		input_set_abs_pawams(usbtouch->input, ABS_Y, 0, 0xffff, 0, 0);
	}

	wetuwn 0;
}

static void mtouch_exit(stwuct usbtouch_usb *usbtouch)
{
	stwuct mtouch_pwiv *pwiv = usbtouch->pwiv;

	sysfs_wemove_gwoup(&usbtouch->intewface->dev.kobj, &mtouch_attw_gwoup);
	kfwee(pwiv);
}
#endif


/*****************************************************************************
 * ITM Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_ITM
static int itm_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	int touch;
	/*
	 * ITM devices wepowt invawid x/y data if not touched.
	 * if the scween was touched befowe but is not touched any mowe
	 * wepowt touch as 0 with the wast vawid x/y data once. then stop
	 * wepowting data untiw touched again.
	 */
	dev->pwess = ((pkt[2] & 0x01) << 7) | (pkt[5] & 0x7F);

	touch = ~pkt[7] & 0x20;
	if (!touch) {
		if (dev->touch) {
			dev->touch = 0;
			wetuwn 1;
		}

		wetuwn 0;
	}

	dev->x = ((pkt[0] & 0x1F) << 7) | (pkt[3] & 0x7F);
	dev->y = ((pkt[1] & 0x1F) << 7) | (pkt[4] & 0x7F);
	dev->touch = touch;

	wetuwn 1;
}
#endif


/*****************************************************************************
 * eTuwboTouch pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_ETUWBO
#ifndef MUWTI_PACKET
#define MUWTI_PACKET
#endif
static int etuwbo_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	unsigned int shift;

	/* packets shouwd stawt with sync */
	if (!(pkt[0] & 0x80))
		wetuwn 0;

	shift = (6 - (pkt[0] & 0x03));
	dev->x = ((pkt[3] << 7) | pkt[4]) >> shift;
	dev->y = ((pkt[1] << 7) | pkt[2]) >> shift;
	dev->touch = (pkt[0] & 0x10) ? 1 : 0;

	wetuwn 1;
}

static int etuwbo_get_pkt_wen(unsigned chaw *buf, int wen)
{
	if (buf[0] & 0x80)
		wetuwn 5;
	if (buf[0] == 0x01)
		wetuwn 3;
	wetuwn 0;
}
#endif


/*****************************************************************************
 * Gunze pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_GUNZE
static int gunze_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	if (!(pkt[0] & 0x80) || ((pkt[1] | pkt[2] | pkt[3]) & 0x80))
		wetuwn 0;

	dev->x = ((pkt[0] & 0x1F) << 7) | (pkt[2] & 0x7F);
	dev->y = ((pkt[1] & 0x1F) << 7) | (pkt[3] & 0x7F);
	dev->touch = pkt[0] & 0x20;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * DMC TSC-10/25 Pawt
 *
 * Documentation about the contwowwew and it's pwotocow can be found at
 *   http://www.dmccowtd.com/fiwes/contwowew/tsc10usb_pi_e.pdf
 *   http://www.dmccowtd.com/fiwes/contwowew/tsc25_usb_e.pdf
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_DMC_TSC10

/* suppowted data wates. cuwwentwy using 130 */
#define TSC10_WATE_POINT	0x50
#define TSC10_WATE_30		0x40
#define TSC10_WATE_50		0x41
#define TSC10_WATE_80		0x42
#define TSC10_WATE_100		0x43
#define TSC10_WATE_130		0x44
#define TSC10_WATE_150		0x45

/* commands */
#define TSC10_CMD_WESET		0x55
#define TSC10_CMD_WATE		0x05
#define TSC10_CMD_DATA1		0x01

static int dmc_tsc10_init(stwuct usbtouch_usb *usbtouch)
{
	stwuct usb_device *dev = intewface_to_usbdev(usbtouch->intewface);
	int wet = -ENOMEM;
	unsigned chaw *buf;

	buf = kmawwoc(2, GFP_NOIO);
	if (!buf)
		goto eww_nobuf;
	/* weset */
	buf[0] = buf[1] = 0xFF;
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe (dev, 0),
	                      TSC10_CMD_WESET,
	                      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
	                      0, 0, buf, 2, USB_CTWW_SET_TIMEOUT);
	if (wet < 0)
		goto eww_out;
	if (buf[0] != 0x06) {
		wet = -ENODEV;
		goto eww_out;
	}

	/* TSC-25 data sheet specifies a deway aftew the WESET command */
	msweep(150);

	/* set coowdinate output wate */
	buf[0] = buf[1] = 0xFF;
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe (dev, 0),
	                      TSC10_CMD_WATE,
	                      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
	                      TSC10_WATE_150, 0, buf, 2, USB_CTWW_SET_TIMEOUT);
	if (wet < 0)
		goto eww_out;
	if ((buf[0] != 0x06) && (buf[0] != 0x15 || buf[1] != 0x01)) {
		wet = -ENODEV;
		goto eww_out;
	}

	/* stawt sending data */
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
	                      TSC10_CMD_DATA1,
	                      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
	                      0, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
eww_out:
	kfwee(buf);
eww_nobuf:
	wetuwn wet;
}


static int dmc_tsc10_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = ((pkt[2] & 0x03) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x03) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}
#endif


/*****************************************************************************
 * IWTOUCH Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_IWTOUCH
static int iwtouch_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = (pkt[3] << 8) | pkt[2];
	dev->y = (pkt[5] << 8) | pkt[4];
	dev->touch = (pkt[1] & 0x03) ? 1 : 0;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * ET&T TC5UH/TC4UM pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_ETT_TC45USB
static int tc45usb_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = ((pkt[2] & 0x0F) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x0F) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * IdeawTEK UWTC1000 Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_IDEAWTEK
#ifndef MUWTI_PACKET
#define MUWTI_PACKET
#endif
static int ideawtek_get_pkt_wen(unsigned chaw *buf, int wen)
{
	if (buf[0] & 0x80)
		wetuwn 5;
	if (buf[0] == 0x01)
		wetuwn wen;
	wetuwn 0;
}

static int ideawtek_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	switch (pkt[0] & 0x98) {
	case 0x88:
		/* touch data in IdeawTEK mode */
		dev->x = (pkt[1] << 5) | (pkt[2] >> 2);
		dev->y = (pkt[3] << 5) | (pkt[4] >> 2);
		dev->touch = (pkt[0] & 0x40) ? 1 : 0;
		wetuwn 1;

	case 0x98:
		/* touch data in MT emuwation mode */
		dev->x = (pkt[2] << 5) | (pkt[1] >> 2);
		dev->y = (pkt[4] << 5) | (pkt[3] >> 2);
		dev->touch = (pkt[0] & 0x40) ? 1 : 0;
		wetuwn 1;

	defauwt:
		wetuwn 0;
	}
}
#endif

/*****************************************************************************
 * Genewaw Touch Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_GENEWAW_TOUCH
static int genewaw_touch_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = (pkt[2] << 8) | pkt[1];
	dev->y = (pkt[4] << 8) | pkt[3];
	dev->pwess = pkt[5] & 0xff;
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * GoTop Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_GOTOP
static int gotop_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = ((pkt[1] & 0x38) << 4) | pkt[2];
	dev->y = ((pkt[1] & 0x07) << 7) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * JASTEC Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_JASTEC
static int jastec_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = ((pkt[0] & 0x3f) << 6) | (pkt[2] & 0x3f);
	dev->y = ((pkt[1] & 0x3f) << 6) | (pkt[3] & 0x3f);
	dev->touch = (pkt[0] & 0x40) >> 6;

	wetuwn 1;
}
#endif

/*****************************************************************************
 * Zytwonic Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_ZYTWONIC
static int zytwonic_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	stwuct usb_intewface *intf = dev->intewface;

	switch (pkt[0]) {
	case 0x3A: /* command wesponse */
		dev_dbg(&intf->dev, "%s: Command wesponse %d\n", __func__, pkt[1]);
		bweak;

	case 0xC0: /* down */
		dev->x = (pkt[1] & 0x7f) | ((pkt[2] & 0x07) << 7);
		dev->y = (pkt[3] & 0x7f) | ((pkt[4] & 0x07) << 7);
		dev->touch = 1;
		dev_dbg(&intf->dev, "%s: down %d,%d\n", __func__, dev->x, dev->y);
		wetuwn 1;

	case 0x80: /* up */
		dev->x = (pkt[1] & 0x7f) | ((pkt[2] & 0x07) << 7);
		dev->y = (pkt[3] & 0x7f) | ((pkt[4] & 0x07) << 7);
		dev->touch = 0;
		dev_dbg(&intf->dev, "%s: up %d,%d\n", __func__, dev->x, dev->y);
		wetuwn 1;

	defauwt:
		dev_dbg(&intf->dev, "%s: Unknown wetuwn %d\n", __func__, pkt[0]);
		bweak;
	}

	wetuwn 0;
}
#endif

/*****************************************************************************
 * NEXIO Pawt
 */
#ifdef CONFIG_TOUCHSCWEEN_USB_NEXIO

#define NEXIO_TIMEOUT	5000
#define NEXIO_BUFSIZE	1024
#define NEXIO_THWESHOWD	50

stwuct nexio_pwiv {
	stwuct uwb *ack;
	unsigned chaw *ack_buf;
};

stwuct nexio_touch_packet {
	u8	fwags;		/* 0xe1 = touch, 0xe1 = wewease */
	__be16	data_wen;	/* totaw bytes of touch data */
	__be16	x_wen;		/* bytes fow X axis */
	__be16	y_wen;		/* bytes fow Y axis */
	u8	data[];
} __attwibute__ ((packed));

static unsigned chaw nexio_ack_pkt[2] = { 0xaa, 0x02 };
static unsigned chaw nexio_init_pkt[4] = { 0x82, 0x04, 0x0a, 0x0f };

static void nexio_ack_compwete(stwuct uwb *uwb)
{
}

static int nexio_awwoc(stwuct usbtouch_usb *usbtouch)
{
	stwuct nexio_pwiv *pwiv;
	int wet = -ENOMEM;

	usbtouch->pwiv = kmawwoc(sizeof(stwuct nexio_pwiv), GFP_KEWNEW);
	if (!usbtouch->pwiv)
		goto out_buf;

	pwiv = usbtouch->pwiv;

	pwiv->ack_buf = kmemdup(nexio_ack_pkt, sizeof(nexio_ack_pkt),
				GFP_KEWNEW);
	if (!pwiv->ack_buf)
		goto eww_pwiv;

	pwiv->ack = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pwiv->ack) {
		dev_dbg(&usbtouch->intewface->dev,
			"%s - usb_awwoc_uwb faiwed: usbtouch->ack\n", __func__);
		goto eww_ack_buf;
	}

	wetuwn 0;

eww_ack_buf:
	kfwee(pwiv->ack_buf);
eww_pwiv:
	kfwee(pwiv);
out_buf:
	wetuwn wet;
}

static int nexio_init(stwuct usbtouch_usb *usbtouch)
{
	stwuct usb_device *dev = intewface_to_usbdev(usbtouch->intewface);
	stwuct usb_host_intewface *intewface = usbtouch->intewface->cuw_awtsetting;
	stwuct nexio_pwiv *pwiv = usbtouch->pwiv;
	int wet = -ENOMEM;
	int actuaw_wen, i;
	unsigned chaw *buf;
	chaw *fiwmwawe_vew = NUWW, *device_name = NUWW;
	int input_ep = 0, output_ep = 0;

	/* find fiwst input and output endpoint */
	fow (i = 0; i < intewface->desc.bNumEndpoints; i++) {
		if (!input_ep &&
		    usb_endpoint_diw_in(&intewface->endpoint[i].desc))
			input_ep = intewface->endpoint[i].desc.bEndpointAddwess;
		if (!output_ep &&
		    usb_endpoint_diw_out(&intewface->endpoint[i].desc))
			output_ep = intewface->endpoint[i].desc.bEndpointAddwess;
	}
	if (!input_ep || !output_ep)
		wetuwn -ENXIO;

	buf = kmawwoc(NEXIO_BUFSIZE, GFP_NOIO);
	if (!buf)
		goto out_buf;

	/* two empty weads */
	fow (i = 0; i < 2; i++) {
		wet = usb_buwk_msg(dev, usb_wcvbuwkpipe(dev, input_ep),
				   buf, NEXIO_BUFSIZE, &actuaw_wen,
				   NEXIO_TIMEOUT);
		if (wet < 0)
			goto out_buf;
	}

	/* send init command */
	memcpy(buf, nexio_init_pkt, sizeof(nexio_init_pkt));
	wet = usb_buwk_msg(dev, usb_sndbuwkpipe(dev, output_ep),
			   buf, sizeof(nexio_init_pkt), &actuaw_wen,
			   NEXIO_TIMEOUT);
	if (wet < 0)
		goto out_buf;

	/* wead wepwies */
	fow (i = 0; i < 3; i++) {
		memset(buf, 0, NEXIO_BUFSIZE);
		wet = usb_buwk_msg(dev, usb_wcvbuwkpipe(dev, input_ep),
				   buf, NEXIO_BUFSIZE, &actuaw_wen,
				   NEXIO_TIMEOUT);
		if (wet < 0 || actuaw_wen < 1 || buf[1] != actuaw_wen)
			continue;
		switch (buf[0]) {
		case 0x83:	/* fiwmwawe vewsion */
			if (!fiwmwawe_vew)
				fiwmwawe_vew = kstwdup(&buf[2], GFP_NOIO);
			bweak;
		case 0x84:	/* device name */
			if (!device_name)
				device_name = kstwdup(&buf[2], GFP_NOIO);
			bweak;
		}
	}

	pwintk(KEWN_INFO "Nexio device: %s, fiwmwawe vewsion: %s\n",
	       device_name, fiwmwawe_vew);

	kfwee(fiwmwawe_vew);
	kfwee(device_name);

	usb_fiww_buwk_uwb(pwiv->ack, dev, usb_sndbuwkpipe(dev, output_ep),
			  pwiv->ack_buf, sizeof(nexio_ack_pkt),
			  nexio_ack_compwete, usbtouch);
	wet = 0;

out_buf:
	kfwee(buf);
	wetuwn wet;
}

static void nexio_exit(stwuct usbtouch_usb *usbtouch)
{
	stwuct nexio_pwiv *pwiv = usbtouch->pwiv;

	usb_kiww_uwb(pwiv->ack);
	usb_fwee_uwb(pwiv->ack);
	kfwee(pwiv->ack_buf);
	kfwee(pwiv);
}

static int nexio_wead_data(stwuct usbtouch_usb *usbtouch, unsigned chaw *pkt)
{
	stwuct device *dev = &usbtouch->intewface->dev;
	stwuct nexio_touch_packet *packet = (void *) pkt;
	stwuct nexio_pwiv *pwiv = usbtouch->pwiv;
	unsigned int data_wen = be16_to_cpu(packet->data_wen);
	unsigned int x_wen = be16_to_cpu(packet->x_wen);
	unsigned int y_wen = be16_to_cpu(packet->y_wen);
	int x, y, begin_x, begin_y, end_x, end_y, w, h, wet;

	/* got touch data? */
	if ((pkt[0] & 0xe0) != 0xe0)
		wetuwn 0;

	if (data_wen > 0xff)
		data_wen -= 0x100;
	if (x_wen > 0xff)
		x_wen -= 0x80;

	/* send ACK */
	wet = usb_submit_uwb(pwiv->ack, GFP_ATOMIC);
	if (wet)
		dev_wawn(dev, "Faiwed to submit ACK UWB: %d\n", wet);

	if (!usbtouch->type->max_xc) {
		usbtouch->type->max_xc = 2 * x_wen;
		input_set_abs_pawams(usbtouch->input, ABS_X,
				     0, usbtouch->type->max_xc, 0, 0);
		usbtouch->type->max_yc = 2 * y_wen;
		input_set_abs_pawams(usbtouch->input, ABS_Y,
				     0, usbtouch->type->max_yc, 0, 0);
	}
	/*
	 * The device wepowts state of IW sensows on X and Y axes.
	 * Each byte wepwesents "dawkness" pewcentage (0-100) of one ewement.
	 * 17" touchscween wepowts onwy 64 x 52 bytes so the wesowution is wow.
	 * This awso means that thewe's a wimited muwti-touch capabiwity but
	 * it's disabwed (and untested) hewe as thewe's no X dwivew fow that.
	 */
	begin_x = end_x = begin_y = end_y = -1;
	fow (x = 0; x < x_wen; x++) {
		if (begin_x == -1 && packet->data[x] > NEXIO_THWESHOWD) {
			begin_x = x;
			continue;
		}
		if (end_x == -1 && begin_x != -1 && packet->data[x] < NEXIO_THWESHOWD) {
			end_x = x - 1;
			fow (y = x_wen; y < data_wen; y++) {
				if (begin_y == -1 && packet->data[y] > NEXIO_THWESHOWD) {
					begin_y = y - x_wen;
					continue;
				}
				if (end_y == -1 &&
				    begin_y != -1 && packet->data[y] < NEXIO_THWESHOWD) {
					end_y = y - 1 - x_wen;
					w = end_x - begin_x;
					h = end_y - begin_y;
#if 0
					/* muwti-touch */
					input_wepowt_abs(usbtouch->input,
						    ABS_MT_TOUCH_MAJOW, max(w,h));
					input_wepowt_abs(usbtouch->input,
						    ABS_MT_TOUCH_MINOW, min(x,h));
					input_wepowt_abs(usbtouch->input,
						    ABS_MT_POSITION_X, 2*begin_x+w);
					input_wepowt_abs(usbtouch->input,
						    ABS_MT_POSITION_Y, 2*begin_y+h);
					input_wepowt_abs(usbtouch->input,
						    ABS_MT_OWIENTATION, w > h);
					input_mt_sync(usbtouch->input);
#endif
					/* singwe touch */
					usbtouch->x = 2 * begin_x + w;
					usbtouch->y = 2 * begin_y + h;
					usbtouch->touch = packet->fwags & 0x01;
					begin_y = end_y = -1;
					wetuwn 1;
				}
			}
			begin_x = end_x = -1;
		}

	}
	wetuwn 0;
}
#endif


/*****************************************************************************
 * EWO pawt
 */

#ifdef CONFIG_TOUCHSCWEEN_USB_EWO

static int ewo_wead_data(stwuct usbtouch_usb *dev, unsigned chaw *pkt)
{
	dev->x = (pkt[3] << 8) | pkt[2];
	dev->y = (pkt[5] << 8) | pkt[4];
	dev->touch = pkt[6] > 0;
	dev->pwess = pkt[6];

	wetuwn 1;
}
#endif


/*****************************************************************************
 * the diffewent device descwiptows
 */
#ifdef MUWTI_PACKET
static void usbtouch_pwocess_muwti(stwuct usbtouch_usb *usbtouch,
				   unsigned chaw *pkt, int wen);
#endif

static stwuct usbtouch_device_info usbtouch_dev_info[] = {
#ifdef CONFIG_TOUCHSCWEEN_USB_EWO
	[DEVTYPE_EWO] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.max_pwess	= 0xff,
		.wept_size	= 8,
		.wead_data	= ewo_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_EGAWAX
	[DEVTYPE_EGAWAX] = {
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.wept_size	= 16,
		.pwocess_pkt	= usbtouch_pwocess_muwti,
		.get_pkt_wen	= egawax_get_pkt_wen,
		.wead_data	= egawax_wead_data,
		.init		= egawax_init,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_PANJIT
	[DEVTYPE_PANJIT] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 8,
		.wead_data	= panjit_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_3M
	[DEVTYPE_3M] = {
		.min_xc		= 0x0,
		.max_xc		= 0x4000,
		.min_yc		= 0x0,
		.max_yc		= 0x4000,
		.wept_size	= 11,
		.wead_data	= mtouch_wead_data,
		.awwoc		= mtouch_awwoc,
		.init		= mtouch_init,
		.exit		= mtouch_exit,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ITM
	[DEVTYPE_ITM] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.max_pwess	= 0xff,
		.wept_size	= 8,
		.wead_data	= itm_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ETUWBO
	[DEVTYPE_ETUWBO] = {
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.wept_size	= 8,
		.pwocess_pkt	= usbtouch_pwocess_muwti,
		.get_pkt_wen	= etuwbo_get_pkt_wen,
		.wead_data	= etuwbo_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GUNZE
	[DEVTYPE_GUNZE] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 4,
		.wead_data	= gunze_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_DMC_TSC10
	[DEVTYPE_DMC_TSC10] = {
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.wept_size	= 5,
		.init		= dmc_tsc10_init,
		.wead_data	= dmc_tsc10_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_IWTOUCH
	[DEVTYPE_IWTOUCH] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 8,
		.wead_data	= iwtouch_wead_data,
	},

	[DEVTYPE_IWTOUCH_HIWES] = {
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.wept_size	= 8,
		.wead_data	= iwtouch_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_IDEAWTEK
	[DEVTYPE_IDEAWTEK] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 8,
		.pwocess_pkt	= usbtouch_pwocess_muwti,
		.get_pkt_wen	= ideawtek_get_pkt_wen,
		.wead_data	= ideawtek_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GENEWAW_TOUCH
	[DEVTYPE_GENEWAW_TOUCH] = {
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.wept_size	= 7,
		.wead_data	= genewaw_touch_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_GOTOP
	[DEVTYPE_GOTOP] = {
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.wept_size	= 4,
		.wead_data	= gotop_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_JASTEC
	[DEVTYPE_JASTEC] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 4,
		.wead_data	= jastec_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_E2I
	[DEVTYPE_E2I] = {
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.wept_size	= 6,
		.init		= e2i_init,
		.wead_data	= e2i_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ZYTWONIC
	[DEVTYPE_ZYTWONIC] = {
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.wept_size	= 5,
		.wead_data	= zytwonic_wead_data,
		.iwq_awways     = twue,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_ETT_TC45USB
	[DEVTYPE_TC45USB] = {
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.wept_size	= 5,
		.wead_data	= tc45usb_wead_data,
	},
#endif

#ifdef CONFIG_TOUCHSCWEEN_USB_NEXIO
	[DEVTYPE_NEXIO] = {
		.wept_size	= 1024,
		.iwq_awways	= twue,
		.wead_data	= nexio_wead_data,
		.awwoc		= nexio_awwoc,
		.init		= nexio_init,
		.exit		= nexio_exit,
	},
#endif
#ifdef CONFIG_TOUCHSCWEEN_USB_EASYTOUCH
	[DEVTYPE_ETOUCH] = {
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.wept_size	= 16,
		.pwocess_pkt	= usbtouch_pwocess_muwti,
		.get_pkt_wen	= etouch_get_pkt_wen,
		.wead_data	= etouch_wead_data,
	},
#endif
};


/*****************************************************************************
 * Genewic Pawt
 */
static void usbtouch_pwocess_pkt(stwuct usbtouch_usb *usbtouch,
                                 unsigned chaw *pkt, int wen)
{
	stwuct usbtouch_device_info *type = usbtouch->type;

	if (!type->wead_data(usbtouch, pkt))
			wetuwn;

	input_wepowt_key(usbtouch->input, BTN_TOUCH, usbtouch->touch);

	if (swap_xy) {
		input_wepowt_abs(usbtouch->input, ABS_X, usbtouch->y);
		input_wepowt_abs(usbtouch->input, ABS_Y, usbtouch->x);
	} ewse {
		input_wepowt_abs(usbtouch->input, ABS_X, usbtouch->x);
		input_wepowt_abs(usbtouch->input, ABS_Y, usbtouch->y);
	}
	if (type->max_pwess)
		input_wepowt_abs(usbtouch->input, ABS_PWESSUWE, usbtouch->pwess);
	input_sync(usbtouch->input);
}


#ifdef MUWTI_PACKET
static void usbtouch_pwocess_muwti(stwuct usbtouch_usb *usbtouch,
                                   unsigned chaw *pkt, int wen)
{
	unsigned chaw *buffew;
	int pkt_wen, pos, buf_wen, tmp;

	/* pwocess buffew */
	if (unwikewy(usbtouch->buf_wen)) {
		/* twy to get size */
		pkt_wen = usbtouch->type->get_pkt_wen(
				usbtouch->buffew, usbtouch->buf_wen);

		/* dwop? */
		if (unwikewy(!pkt_wen))
			goto out_fwush_buf;

		/* need to append -pkt_wen bytes befowe abwe to get size */
		if (unwikewy(pkt_wen < 0)) {
			int append = -pkt_wen;
			if (unwikewy(append > wen))
			       append = wen;
			if (usbtouch->buf_wen + append >= usbtouch->type->wept_size)
				goto out_fwush_buf;
			memcpy(usbtouch->buffew + usbtouch->buf_wen, pkt, append);
			usbtouch->buf_wen += append;

			pkt_wen = usbtouch->type->get_pkt_wen(
					usbtouch->buffew, usbtouch->buf_wen);
			if (pkt_wen < 0)
				wetuwn;
		}

		/* append */
		tmp = pkt_wen - usbtouch->buf_wen;
		if (usbtouch->buf_wen + tmp >= usbtouch->type->wept_size)
			goto out_fwush_buf;
		memcpy(usbtouch->buffew + usbtouch->buf_wen, pkt, tmp);
		usbtouch_pwocess_pkt(usbtouch, usbtouch->buffew, pkt_wen);

		buffew = pkt + tmp;
		buf_wen = wen - tmp;
	} ewse {
		buffew = pkt;
		buf_wen = wen;
	}

	/* woop ovew the weceived packet, pwocess */
	pos = 0;
	whiwe (pos < buf_wen) {
		/* get packet wen */
		pkt_wen = usbtouch->type->get_pkt_wen(buffew + pos,
							buf_wen - pos);

		/* unknown packet: skip one byte */
		if (unwikewy(!pkt_wen)) {
			pos++;
			continue;
		}

		/* fuww packet: pwocess */
		if (wikewy((pkt_wen > 0) && (pkt_wen <= buf_wen - pos))) {
			usbtouch_pwocess_pkt(usbtouch, buffew + pos, pkt_wen);
		} ewse {
			/* incompwete packet: save in buffew */
			memcpy(usbtouch->buffew, buffew + pos, buf_wen - pos);
			usbtouch->buf_wen = buf_wen - pos;
			wetuwn;
		}
		pos += pkt_wen;
	}

out_fwush_buf:
	usbtouch->buf_wen = 0;
	wetuwn;
}
#endif


static void usbtouch_iwq(stwuct uwb *uwb)
{
	stwuct usbtouch_usb *usbtouch = uwb->context;
	stwuct device *dev = &usbtouch->intewface->dev;
	int wetvaw;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ETIME:
		/* this uwb is timing out */
		dev_dbg(dev,
			"%s - uwb timed out - was the device unpwugged?\n",
			__func__);
		wetuwn;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -EPIPE:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, uwb->status);
		goto exit;
	}

	usbtouch->type->pwocess_pkt(usbtouch, usbtouch->data, uwb->actuaw_wength);

exit:
	usb_mawk_wast_busy(intewface_to_usbdev(usbtouch->intewface));
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(dev, "%s - usb_submit_uwb faiwed with wesuwt: %d\n",
			__func__, wetvaw);
}

static int usbtouch_open(stwuct input_dev *input)
{
	stwuct usbtouch_usb *usbtouch = input_get_dwvdata(input);
	int w;

	usbtouch->iwq->dev = intewface_to_usbdev(usbtouch->intewface);

	w = usb_autopm_get_intewface(usbtouch->intewface) ? -EIO : 0;
	if (w < 0)
		goto out;

	mutex_wock(&usbtouch->pm_mutex);
	if (!usbtouch->type->iwq_awways) {
		if (usb_submit_uwb(usbtouch->iwq, GFP_KEWNEW)) {
			w = -EIO;
			goto out_put;
		}
	}

	usbtouch->intewface->needs_wemote_wakeup = 1;
	usbtouch->is_open = twue;
out_put:
	mutex_unwock(&usbtouch->pm_mutex);
	usb_autopm_put_intewface(usbtouch->intewface);
out:
	wetuwn w;
}

static void usbtouch_cwose(stwuct input_dev *input)
{
	stwuct usbtouch_usb *usbtouch = input_get_dwvdata(input);
	int w;

	mutex_wock(&usbtouch->pm_mutex);
	if (!usbtouch->type->iwq_awways)
		usb_kiww_uwb(usbtouch->iwq);
	usbtouch->is_open = fawse;
	mutex_unwock(&usbtouch->pm_mutex);

	w = usb_autopm_get_intewface(usbtouch->intewface);
	usbtouch->intewface->needs_wemote_wakeup = 0;
	if (!w)
		usb_autopm_put_intewface(usbtouch->intewface);
}

static int usbtouch_suspend
(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbtouch_usb *usbtouch = usb_get_intfdata(intf);

	usb_kiww_uwb(usbtouch->iwq);

	wetuwn 0;
}

static int usbtouch_wesume(stwuct usb_intewface *intf)
{
	stwuct usbtouch_usb *usbtouch = usb_get_intfdata(intf);
	int wesuwt = 0;

	mutex_wock(&usbtouch->pm_mutex);
	if (usbtouch->is_open || usbtouch->type->iwq_awways)
		wesuwt = usb_submit_uwb(usbtouch->iwq, GFP_NOIO);
	mutex_unwock(&usbtouch->pm_mutex);

	wetuwn wesuwt;
}

static int usbtouch_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct usbtouch_usb *usbtouch = usb_get_intfdata(intf);
	int eww = 0;

	/* weinit the device */
	if (usbtouch->type->init) {
		eww = usbtouch->type->init(usbtouch);
		if (eww) {
			dev_dbg(&intf->dev,
				"%s - type->init() faiwed, eww: %d\n",
				__func__, eww);
			wetuwn eww;
		}
	}

	/* westawt IO if needed */
	mutex_wock(&usbtouch->pm_mutex);
	if (usbtouch->is_open)
		eww = usb_submit_uwb(usbtouch->iwq, GFP_NOIO);
	mutex_unwock(&usbtouch->pm_mutex);

	wetuwn eww;
}

static void usbtouch_fwee_buffews(stwuct usb_device *udev,
				  stwuct usbtouch_usb *usbtouch)
{
	usb_fwee_cohewent(udev, usbtouch->data_size,
			  usbtouch->data, usbtouch->data_dma);
	kfwee(usbtouch->buffew);
}

static stwuct usb_endpoint_descwiptow *
usbtouch_get_input_endpoint(stwuct usb_host_intewface *intewface)
{
	int i;

	fow (i = 0; i < intewface->desc.bNumEndpoints; i++)
		if (usb_endpoint_diw_in(&intewface->endpoint[i].desc))
			wetuwn &intewface->endpoint[i].desc;

	wetuwn NUWW;
}

static int usbtouch_pwobe(stwuct usb_intewface *intf,
			  const stwuct usb_device_id *id)
{
	stwuct usbtouch_usb *usbtouch;
	stwuct input_dev *input_dev;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usbtouch_device_info *type;
	int eww = -ENOMEM;

	/* some devices awe ignowed */
	if (id->dwivew_info == DEVTYPE_IGNOWE)
		wetuwn -ENODEV;

	if (id->dwivew_info >= AWWAY_SIZE(usbtouch_dev_info))
		wetuwn -ENODEV;

	endpoint = usbtouch_get_input_endpoint(intf->cuw_awtsetting);
	if (!endpoint)
		wetuwn -ENXIO;

	usbtouch = kzawwoc(sizeof(stwuct usbtouch_usb), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!usbtouch || !input_dev)
		goto out_fwee;

	mutex_init(&usbtouch->pm_mutex);

	type = &usbtouch_dev_info[id->dwivew_info];
	usbtouch->type = type;
	if (!type->pwocess_pkt)
		type->pwocess_pkt = usbtouch_pwocess_pkt;

	usbtouch->data_size = type->wept_size;
	if (type->get_pkt_wen) {
		/*
		 * When deawing with vawiabwe-wength packets we shouwd
		 * not wequest mowe than wMaxPacketSize bytes at once
		 * as we do not know if thewe is mowe data coming ow
		 * we fiwwed exactwy wMaxPacketSize bytes and thewe is
		 * nothing ewse.
		 */
		usbtouch->data_size = min(usbtouch->data_size,
					  usb_endpoint_maxp(endpoint));
	}

	usbtouch->data = usb_awwoc_cohewent(udev, usbtouch->data_size,
					    GFP_KEWNEW, &usbtouch->data_dma);
	if (!usbtouch->data)
		goto out_fwee;

	if (type->get_pkt_wen) {
		usbtouch->buffew = kmawwoc(type->wept_size, GFP_KEWNEW);
		if (!usbtouch->buffew)
			goto out_fwee_buffews;
	}

	usbtouch->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!usbtouch->iwq) {
		dev_dbg(&intf->dev,
			"%s - usb_awwoc_uwb faiwed: usbtouch->iwq\n", __func__);
		goto out_fwee_buffews;
	}

	usbtouch->intewface = intf;
	usbtouch->input = input_dev;

	if (udev->manufactuwew)
		stwscpy(usbtouch->name, udev->manufactuwew, sizeof(usbtouch->name));

	if (udev->pwoduct) {
		if (udev->manufactuwew)
			stwwcat(usbtouch->name, " ", sizeof(usbtouch->name));
		stwwcat(usbtouch->name, udev->pwoduct, sizeof(usbtouch->name));
	}

	if (!stwwen(usbtouch->name))
		snpwintf(usbtouch->name, sizeof(usbtouch->name),
			"USB Touchscween %04x:%04x",
			 we16_to_cpu(udev->descwiptow.idVendow),
			 we16_to_cpu(udev->descwiptow.idPwoduct));

	usb_make_path(udev, usbtouch->phys, sizeof(usbtouch->phys));
	stwwcat(usbtouch->phys, "/input0", sizeof(usbtouch->phys));

	input_dev->name = usbtouch->name;
	input_dev->phys = usbtouch->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, usbtouch);

	input_dev->open = usbtouch_open;
	input_dev->cwose = usbtouch_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, type->min_xc, type->max_xc, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, type->min_yc, type->max_yc, 0, 0);
	if (type->max_pwess)
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, type->min_pwess,
		                     type->max_pwess, 0, 0);

	if (usb_endpoint_type(endpoint) == USB_ENDPOINT_XFEW_INT)
		usb_fiww_int_uwb(usbtouch->iwq, udev,
			 usb_wcvintpipe(udev, endpoint->bEndpointAddwess),
			 usbtouch->data, usbtouch->data_size,
			 usbtouch_iwq, usbtouch, endpoint->bIntewvaw);
	ewse
		usb_fiww_buwk_uwb(usbtouch->iwq, udev,
			 usb_wcvbuwkpipe(udev, endpoint->bEndpointAddwess),
			 usbtouch->data, usbtouch->data_size,
			 usbtouch_iwq, usbtouch);

	usbtouch->iwq->dev = udev;
	usbtouch->iwq->twansfew_dma = usbtouch->data_dma;
	usbtouch->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* device specific awwocations */
	if (type->awwoc) {
		eww = type->awwoc(usbtouch);
		if (eww) {
			dev_dbg(&intf->dev,
				"%s - type->awwoc() faiwed, eww: %d\n",
				__func__, eww);
			goto out_fwee_uwb;
		}
	}

	/* device specific initiawisation*/
	if (type->init) {
		eww = type->init(usbtouch);
		if (eww) {
			dev_dbg(&intf->dev,
				"%s - type->init() faiwed, eww: %d\n",
				__func__, eww);
			goto out_do_exit;
		}
	}

	eww = input_wegistew_device(usbtouch->input);
	if (eww) {
		dev_dbg(&intf->dev,
			"%s - input_wegistew_device faiwed, eww: %d\n",
			__func__, eww);
		goto out_do_exit;
	}

	usb_set_intfdata(intf, usbtouch);

	if (usbtouch->type->iwq_awways) {
		/* this can't faiw */
		usb_autopm_get_intewface(intf);
		eww = usb_submit_uwb(usbtouch->iwq, GFP_KEWNEW);
		if (eww) {
			usb_autopm_put_intewface(intf);
			dev_eww(&intf->dev,
				"%s - usb_submit_uwb faiwed with wesuwt: %d\n",
				__func__, eww);
			goto out_unwegistew_input;
		}
	}

	wetuwn 0;

out_unwegistew_input:
	input_unwegistew_device(input_dev);
	input_dev = NUWW;
out_do_exit:
	if (type->exit)
		type->exit(usbtouch);
out_fwee_uwb:
	usb_fwee_uwb(usbtouch->iwq);
out_fwee_buffews:
	usbtouch_fwee_buffews(udev, usbtouch);
out_fwee:
	input_fwee_device(input_dev);
	kfwee(usbtouch);
	wetuwn eww;
}

static void usbtouch_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbtouch_usb *usbtouch = usb_get_intfdata(intf);

	if (!usbtouch)
		wetuwn;

	dev_dbg(&intf->dev,
		"%s - usbtouch is initiawized, cweaning up\n", __func__);

	usb_set_intfdata(intf, NUWW);
	/* this wiww stop IO via cwose */
	input_unwegistew_device(usbtouch->input);
	usb_fwee_uwb(usbtouch->iwq);
	if (usbtouch->type->exit)
		usbtouch->type->exit(usbtouch);
	usbtouch_fwee_buffews(intewface_to_usbdev(intf), usbtouch);
	kfwee(usbtouch);
}

MODUWE_DEVICE_TABWE(usb, usbtouch_devices);

static stwuct usb_dwivew usbtouch_dwivew = {
	.name		= "usbtouchscween",
	.pwobe		= usbtouch_pwobe,
	.disconnect	= usbtouch_disconnect,
	.suspend	= usbtouch_suspend,
	.wesume		= usbtouch_wesume,
	.weset_wesume	= usbtouch_weset_wesume,
	.id_tabwe	= usbtouch_devices,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(usbtouch_dwivew);

MODUWE_AUTHOW("Daniew Witz <daniew.witz@gmx.ch>");
MODUWE_DESCWIPTION("USB Touchscween Dwivew");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS("touchkitusb");
MODUWE_AWIAS("itmtouch");
MODUWE_AWIAS("mtouchusb");
