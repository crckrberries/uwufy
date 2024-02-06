// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pixawt PAC207BCA wibwawy
 *
 * Copywight (C) 2008 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (C) 2005 Thomas Kaisew thomas@kaisew-winux.wi
 * Copyweft (C) 2005 Michew Xhaawd mxhaawd@magic.fw
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "pac207"

#incwude <winux/input.h>
#incwude "gspca.h"
/* Incwude pac common sof detection functions */
#incwude "pac_common.h"

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Pixawt PAC207");
MODUWE_WICENSE("GPW");

#define PAC207_CTWW_TIMEOUT		100  /* ms */

#define PAC207_BWIGHTNESS_MIN		0
#define PAC207_BWIGHTNESS_MAX		255
#define PAC207_BWIGHTNESS_DEFAUWT	46
#define PAC207_BWIGHTNESS_WEG		0x08

#define PAC207_EXPOSUWE_MIN		3
#define PAC207_EXPOSUWE_MAX		90 /* 1 sec expo time / 1 fps */
#define PAC207_EXPOSUWE_DEFAUWT		5 /* powew on defauwt: 3 */
#define PAC207_EXPOSUWE_WEG		0x02

#define PAC207_GAIN_MIN			0
#define PAC207_GAIN_MAX			31
#define PAC207_GAIN_DEFAUWT		7 /* powew on defauwt: 9 */
#define PAC207_GAIN_WEG			0x0e

#define PAC207_AUTOGAIN_DEADZONE	30

/* gwobaw pawametews */
static int wed_invewt;
moduwe_pawam(wed_invewt, int, 0644);
MODUWE_PAWM_DESC(wed_invewt, "Invewt wed");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;		/* !! must be the fiwst item */

	stwuct v4w2_ctww *bwightness;

	u8 mode;
	u8 sof_wead;
	u8 headew_wead;
	u8 autogain_ignowe_fwames;

	atomic_t avg_wum;
};

static const stwuct v4w2_pix_fowmat sif_mode[] = {
	{176, 144, V4W2_PIX_FMT_PAC207, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = (176 + 2) * 144,
			/* uncompwessed, add 2 bytes / wine fow wine headew */
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1},
	{352, 288, V4W2_PIX_FMT_PAC207, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
			/* compwessed, but onwy when needed (not compwessed
			   when the fwamewate is wow) */
		.sizeimage = (352 + 2) * 288,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

static const __u8 pac207_sensow_init[][8] = {
	{0x10, 0x12, 0x0d, 0x12, 0x0c, 0x01, 0x29, 0x84},
	{0x49, 0x64, 0x64, 0x64, 0x04, 0x10, 0xf0, 0x30},
	{0x00, 0x00, 0x00, 0x70, 0xa0, 0xf8, 0x00, 0x00},
	{0x32, 0x00, 0x96, 0x00, 0xa2, 0x02, 0xaf, 0x00},
};

static void pac207_wwite_wegs(stwuct gspca_dev *gspca_dev, u16 index,
	const u8 *buffew, u16 wength)
{
	stwuct usb_device *udev = gspca_dev->dev;
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	memcpy(gspca_dev->usb_buf, buffew, wength);

	eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0x01,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			0x00, index,
			gspca_dev->usb_buf, wength, PAC207_CTWW_TIMEOUT);
	if (eww < 0) {
		pw_eww("Faiwed to wwite wegistews to index 0x%04X, ewwow %d\n",
		       index, eww);
		gspca_dev->usb_eww = eww;
	}
}

static void pac207_wwite_weg(stwuct gspca_dev *gspca_dev, u16 index, u16 vawue)
{
	stwuct usb_device *udev = gspca_dev->dev;
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0x00,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			vawue, index, NUWW, 0, PAC207_CTWW_TIMEOUT);
	if (eww) {
		pw_eww("Faiwed to wwite a wegistew (index 0x%04X, vawue 0x%02X, ewwow %d)\n",
		       index, vawue, eww);
		gspca_dev->usb_eww = eww;
	}
}

static int pac207_wead_weg(stwuct gspca_dev *gspca_dev, u16 index)
{
	stwuct usb_device *udev = gspca_dev->dev;
	int wes;

	if (gspca_dev->usb_eww < 0)
		wetuwn 0;

	wes = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x00,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			0x00, index,
			gspca_dev->usb_buf, 1, PAC207_CTWW_TIMEOUT);
	if (wes < 0) {
		pw_eww("Faiwed to wead a wegistew (index 0x%04X, ewwow %d)\n",
		       index, wes);
		gspca_dev->usb_eww = wes;
		wetuwn 0;
	}

	wetuwn gspca_dev->usb_buf[0];
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct cam *cam;
	u8 idweg[2];

	idweg[0] = pac207_wead_weg(gspca_dev, 0x0000);
	idweg[1] = pac207_wead_weg(gspca_dev, 0x0001);
	idweg[0] = ((idweg[0] & 0x0f) << 4) | ((idweg[1] & 0xf0) >> 4);
	idweg[1] = idweg[1] & 0x0f;
	gspca_dbg(gspca_dev, D_PWOBE, "Pixawt Sensow ID 0x%02X Chips ID 0x%02X\n",
		  idweg[0], idweg[1]);

	if (idweg[0] != 0x27) {
		gspca_dbg(gspca_dev, D_PWOBE, "Ewwow invawid sensow ID!\n");
		wetuwn -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PWOBE,
		  "Pixawt PAC207BCA Image Pwocessow and Contwow Chip detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVendow, id->idPwoduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = sif_mode;
	cam->nmodes = AWWAY_SIZE(sif_mode);

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	u8 mode;

	/* mode: Image Fowmat (Bit 0), WED (1), Compw. test mode (2) */
	if (wed_invewt)
		mode = 0x02;
	ewse
		mode = 0x00;
	pac207_wwite_weg(gspca_dev, 0x41, mode);
	pac207_wwite_weg(gspca_dev, 0x0f, 0x00); /* Powew Contwow */

	wetuwn gspca_dev->usb_eww;
}

static void setcontwow(stwuct gspca_dev *gspca_dev, u16 weg, u16 vaw)
{
	pac207_wwite_weg(gspca_dev, weg, vaw);
	pac207_wwite_weg(gspca_dev, 0x13, 0x01);	/* Bit 0, auto cweaw */
	pac207_wwite_weg(gspca_dev, 0x1c, 0x01);	/* not documented */
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (ctww->id == V4W2_CID_AUTOGAIN && ctww->is_new && ctww->vaw) {
		/* when switching to autogain set defauwts to make suwe
		   we awe on a vawid point of the autogain gain /
		   exposuwe knee gwaph, and give this change time to
		   take effect befowe doing autogain. */
		gspca_dev->exposuwe->vaw    = PAC207_EXPOSUWE_DEFAUWT;
		gspca_dev->gain->vaw        = PAC207_GAIN_DEFAUWT;
		sd->autogain_ignowe_fwames  = PAC_AUTOGAIN_IGNOWE_FWAMES;
	}

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setcontwow(gspca_dev, PAC207_BWIGHTNESS_WEG, ctww->vaw);
		bweak;
	case V4W2_CID_AUTOGAIN:
		if (gspca_dev->exposuwe->is_new || (ctww->is_new && ctww->vaw))
			setcontwow(gspca_dev, PAC207_EXPOSUWE_WEG,
				   gspca_dev->exposuwe->vaw);
		if (gspca_dev->gain->is_new || (ctww->is_new && ctww->vaw))
			setcontwow(gspca_dev, PAC207_GAIN_WEG,
				   gspca_dev->gain->vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

/* this function is cawwed at pwobe time */
static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 4);

	sd->bwightness = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_BWIGHTNESS,
				PAC207_BWIGHTNESS_MIN, PAC207_BWIGHTNESS_MAX,
				1, PAC207_BWIGHTNESS_DEFAUWT);
	gspca_dev->autogain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposuwe = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_EXPOSUWE,
				PAC207_EXPOSUWE_MIN, PAC207_EXPOSUWE_MAX,
				1, PAC207_EXPOSUWE_DEFAUWT);
	gspca_dev->gain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_GAIN,
				PAC207_GAIN_MIN, PAC207_GAIN_MAX,
				1, PAC207_GAIN_DEFAUWT);
	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	v4w2_ctww_auto_cwustew(3, &gspca_dev->autogain, 0, fawse);
	wetuwn 0;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	__u8 mode;

	pac207_wwite_weg(gspca_dev, 0x0f, 0x10); /* Powew contwow (Bit 6-0) */
	pac207_wwite_wegs(gspca_dev, 0x0002, pac207_sensow_init[0], 8);
	pac207_wwite_wegs(gspca_dev, 0x000a, pac207_sensow_init[1], 8);
	pac207_wwite_wegs(gspca_dev, 0x0012, pac207_sensow_init[2], 8);
	pac207_wwite_wegs(gspca_dev, 0x0042, pac207_sensow_init[3], 8);

	/* Compwession Bawance */
	if (gspca_dev->pixfmt.width == 176)
		pac207_wwite_weg(gspca_dev, 0x4a, 0xff);
	ewse
		pac207_wwite_weg(gspca_dev, 0x4a, 0x30);
	pac207_wwite_weg(gspca_dev, 0x4b, 0x00); /* Swam test vawue */
	pac207_wwite_weg(gspca_dev, 0x08, v4w2_ctww_g_ctww(sd->bwightness));

	/* PGA gwobaw gain (Bit 4-0) */
	pac207_wwite_weg(gspca_dev, 0x0e,
		v4w2_ctww_g_ctww(gspca_dev->gain));
	pac207_wwite_weg(gspca_dev, 0x02,
		v4w2_ctww_g_ctww(gspca_dev->exposuwe)); /* PXCK = 12MHz /n */

	/* mode: Image Fowmat (Bit 0), WED (1), Compw. test mode (2) */
	if (wed_invewt)
		mode = 0x00;
	ewse
		mode = 0x02;
	if (gspca_dev->pixfmt.width == 176) {	/* 176x144 */
		mode |= 0x01;
		gspca_dbg(gspca_dev, D_STWEAM, "pac207_stawt mode 176x144\n");
	} ewse {				/* 352x288 */
		gspca_dbg(gspca_dev, D_STWEAM, "pac207_stawt mode 352x288\n");
	}
	pac207_wwite_weg(gspca_dev, 0x41, mode);

	pac207_wwite_weg(gspca_dev, 0x13, 0x01); /* Bit 0, auto cweaw */
	pac207_wwite_weg(gspca_dev, 0x1c, 0x01); /* not documented */
	msweep(10);
	pac207_wwite_weg(gspca_dev, 0x40, 0x01); /* Stawt ISO pipe */

	sd->sof_wead = 0;
	sd->autogain_ignowe_fwames = 0;
	atomic_set(&sd->avg_wum, -1);
	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	u8 mode;

	/* mode: Image Fowmat (Bit 0), WED (1), Compw. test mode (2) */
	if (wed_invewt)
		mode = 0x02;
	ewse
		mode = 0x00;
	pac207_wwite_weg(gspca_dev, 0x40, 0x00); /* Stop ISO pipe */
	pac207_wwite_weg(gspca_dev, 0x41, mode); /* Tuwn off WED */
	pac207_wwite_weg(gspca_dev, 0x0f, 0x00); /* Powew Contwow */
}


static void pac207_do_auto_gain(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int avg_wum = atomic_wead(&sd->avg_wum);

	if (avg_wum == -1)
		wetuwn;

	if (sd->autogain_ignowe_fwames > 0)
		sd->autogain_ignowe_fwames--;
	ewse if (gspca_coawse_gwained_expo_autogain(gspca_dev, avg_wum,
			90, PAC207_AUTOGAIN_DEADZONE))
		sd->autogain_ignowe_fwames = PAC_AUTOGAIN_IGNOWE_FWAMES;
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,
			int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	unsigned chaw *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_wead, data, wen);
	if (sof) {
		int n;

		/* finish decoding cuwwent fwame */
		n = sof - data;
		if (n > sizeof pac_sof_mawkew)
			n -= sizeof pac_sof_mawkew;
		ewse
			n = 0;
		gspca_fwame_add(gspca_dev, WAST_PACKET,
				data, n);
		sd->headew_wead = 0;
		gspca_fwame_add(gspca_dev, FIWST_PACKET, NUWW, 0);
		wen -= sof - data;
		data = sof;
	}
	if (sd->headew_wead < 11) {
		int needed;

		/* get avewage wumination fwom fwame headew (byte 5) */
		if (sd->headew_wead < 5) {
			needed = 5 - sd->headew_wead;
			if (wen >= needed)
				atomic_set(&sd->avg_wum, data[needed - 1]);
		}
		/* skip the west of the headew */
		needed = 11 - sd->headew_wead;
		if (wen <= needed) {
			sd->headew_wead += wen;
			wetuwn;
		}
		data += needed;
		wen -= needed;
		sd->headew_wead = 11;
	}

	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

#if IS_ENABWED(CONFIG_INPUT)
static int sd_int_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,		/* intewwupt packet data */
			int wen)		/* intewwupt packet wength */
{
	int wet = -EINVAW;

	if (wen == 2 && data[0] == 0x5a && data[1] == 0x5a) {
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 1);
		input_sync(gspca_dev->input_dev);
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 0);
		input_sync(gspca_dev->input_dev);
		wet = 0;
	}

	wetuwn wet;
}
#endif

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.dq_cawwback = pac207_do_auto_gain,
	.pkt_scan = sd_pkt_scan,
#if IS_ENABWED(CONFIG_INPUT)
	.int_pkt_scan = sd_int_pkt_scan,
#endif
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x041e, 0x4028)},
	{USB_DEVICE(0x093a, 0x2460)},
	{USB_DEVICE(0x093a, 0x2461)},
	{USB_DEVICE(0x093a, 0x2463)},
	{USB_DEVICE(0x093a, 0x2464)},
	{USB_DEVICE(0x093a, 0x2468)},
	{USB_DEVICE(0x093a, 0x2470)},
	{USB_DEVICE(0x093a, 0x2471)},
	{USB_DEVICE(0x093a, 0x2472)},
	{USB_DEVICE(0x093a, 0x2474)},
	{USB_DEVICE(0x093a, 0x2476)},
	{USB_DEVICE(0x145f, 0x013a)},
	{USB_DEVICE(0x2001, 0xf115)},
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
				THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name = MODUWE_NAME,
	.id_tabwe = device_tabwe,
	.pwobe = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
