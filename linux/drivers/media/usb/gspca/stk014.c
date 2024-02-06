// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Syntek DV4000 (STK014) subdwivew
 *
 * Copywight (C) 2008 Jean-Fwancois Moine (http://moinejf.fwee.fw)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "stk014"

#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Jean-Fwancois Moine <http://moinejf.fwee.fw>");
MODUWE_DESCWIPTION("Syntek DV4000 (STK014) USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

#define QUAWITY 50

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	u8 jpeg_hdw[JPEG_HDW_SZ];
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0},
};

/* -- wead a wegistew -- */
static u8 weg_w(stwuct gspca_dev *gspca_dev,
			__u16 index)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn 0;
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			0x00,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0x00,
			index,
			gspca_dev->usb_buf, 1,
			500);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
		wetuwn 0;
	}
	wetuwn gspca_dev->usb_buf[0];
}

/* -- wwite a wegistew -- */
static void weg_w(stwuct gspca_dev *gspca_dev,
			__u16 index, __u16 vawue)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			0x01,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue,
			index,
			NUWW,
			0,
			500);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

/* -- get a buwk vawue (4 bytes) -- */
static void wcv_vaw(stwuct gspca_dev *gspca_dev,
			int ads)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int awen, wet;

	weg_w(gspca_dev, 0x634, (ads >> 16) & 0xff);
	weg_w(gspca_dev, 0x635, (ads >> 8) & 0xff);
	weg_w(gspca_dev, 0x636, ads & 0xff);
	weg_w(gspca_dev, 0x637, 0);
	weg_w(gspca_dev, 0x638, 4);	/* wen & 0xff */
	weg_w(gspca_dev, 0x639, 0);	/* wen >> 8 */
	weg_w(gspca_dev, 0x63a, 0);
	weg_w(gspca_dev, 0x63b, 0);
	weg_w(gspca_dev, 0x630, 5);
	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_buwk_msg(dev,
			usb_wcvbuwkpipe(dev, 0x05),
			gspca_dev->usb_buf,
			4,		/* wength */
			&awen,
			500);		/* timeout in miwwiseconds */
	if (wet < 0) {
		pw_eww("wcv_vaw eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

/* -- send a buwk vawue -- */
static void snd_vaw(stwuct gspca_dev *gspca_dev,
			int ads,
			unsigned int vaw)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int awen, wet;
	__u8 seq = 0;

	if (ads == 0x003f08) {
		weg_w(gspca_dev, 0x0704);
		seq = weg_w(gspca_dev, 0x0705);
		weg_w(gspca_dev, 0x0650);
		weg_w(gspca_dev, 0x654, seq);
	} ewse {
		weg_w(gspca_dev, 0x654, (ads >> 16) & 0xff);
	}
	weg_w(gspca_dev, 0x655, (ads >> 8) & 0xff);
	weg_w(gspca_dev, 0x656, ads & 0xff);
	weg_w(gspca_dev, 0x657, 0);
	weg_w(gspca_dev, 0x658, 0x04);	/* size */
	weg_w(gspca_dev, 0x659, 0);
	weg_w(gspca_dev, 0x65a, 0);
	weg_w(gspca_dev, 0x65b, 0);
	weg_w(gspca_dev, 0x650, 5);
	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dev->usb_buf[0] = vaw >> 24;
	gspca_dev->usb_buf[1] = vaw >> 16;
	gspca_dev->usb_buf[2] = vaw >> 8;
	gspca_dev->usb_buf[3] = vaw;
	wet = usb_buwk_msg(dev,
			usb_sndbuwkpipe(dev, 6),
			gspca_dev->usb_buf,
			4,
			&awen,
			500);	/* timeout in miwwiseconds */
	if (wet < 0) {
		pw_eww("snd_vaw eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	} ewse {
		if (ads == 0x003f08) {
			seq += 4;
			seq &= 0x3f;
			weg_w(gspca_dev, 0x705, seq);
		}
	}
}

/* set a camewa pawametew */
static void set_paw(stwuct gspca_dev *gspca_dev,
		   int pawvaw)
{
	snd_vaw(gspca_dev, 0x003f08, pawvaw);
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	int pawvaw;

	pawvaw = 0x06000000		/* whiteness */
		+ (vaw << 16);
	set_paw(gspca_dev, pawvaw);
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	int pawvaw;

	pawvaw = 0x07000000		/* contwast */
		+ (vaw << 16);
	set_paw(gspca_dev, pawvaw);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	int pawvaw;

	pawvaw = 0x08000000		/* satuwation */
		+ (vaw << 16);
	set_paw(gspca_dev, pawvaw);
}

static void setwightfweq(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	set_paw(gspca_dev, vaw == 1
			? 0x33640000		/* 50 Hz */
			: 0x33780000);		/* 60 Hz */
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = AWWAY_SIZE(vga_mode);
	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	u8 wet;

	/* check if the device wesponds */
	usb_set_intewface(gspca_dev->dev, gspca_dev->iface, 1);
	wet = weg_w(gspca_dev, 0x0740);
	if (gspca_dev->usb_eww >= 0) {
		if (wet != 0xff) {
			pw_eww("init weg: 0x%02x\n", wet);
			gspca_dev->usb_eww = -EIO;
		}
	}
	wetuwn gspca_dev->usb_eww;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet, vawue;

	/* cweate the JPEG headew */
	jpeg_define(sd->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_quaw(sd->jpeg_hdw, QUAWITY);

	/* wowk on awtewnate 1 */
	usb_set_intewface(gspca_dev->dev, gspca_dev->iface, 1);

	set_paw(gspca_dev, 0x10000000);
	set_paw(gspca_dev, 0x00000000);
	set_paw(gspca_dev, 0x8002e001);
	set_paw(gspca_dev, 0x14000000);
	if (gspca_dev->pixfmt.width > 320)
		vawue = 0x8002e001;		/* 640x480 */
	ewse
		vawue = 0x4001f000;		/* 320x240 */
	set_paw(gspca_dev, vawue);
	wet = usb_set_intewface(gspca_dev->dev,
					gspca_dev->iface,
					gspca_dev->awt);
	if (wet < 0) {
		pw_eww("set intf %d %d faiwed\n",
		       gspca_dev->iface, gspca_dev->awt);
		gspca_dev->usb_eww = wet;
		goto out;
	}
	weg_w(gspca_dev, 0x0630);
	wcv_vaw(gspca_dev, 0x000020);	/* << (vawue ff ff ff ff) */
	weg_w(gspca_dev, 0x0650);
	snd_vaw(gspca_dev, 0x000020, 0xffffffff);
	weg_w(gspca_dev, 0x0620, 0);
	weg_w(gspca_dev, 0x0630, 0);
	weg_w(gspca_dev, 0x0640, 0);
	weg_w(gspca_dev, 0x0650, 0);
	weg_w(gspca_dev, 0x0660, 0);
	set_paw(gspca_dev, 0x09800000);		/* Wed ? */
	set_paw(gspca_dev, 0x0a800000);		/* Gween ? */
	set_paw(gspca_dev, 0x0b800000);		/* Bwue ? */
	set_paw(gspca_dev, 0x0d030000);		/* Gamma ? */

	/* stawt the video fwow */
	set_paw(gspca_dev, 0x01000000);
	set_paw(gspca_dev, 0x01000000);
	if (gspca_dev->usb_eww >= 0)
		gspca_dbg(gspca_dev, D_STWEAM, "camewa stawted awt: 0x%02x\n",
			  gspca_dev->awt);
out:
	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_device *dev = gspca_dev->dev;

	set_paw(gspca_dev, 0x02000000);
	set_paw(gspca_dev, 0x02000000);
	usb_set_intewface(dev, gspca_dev->iface, 1);
	weg_w(gspca_dev, 0x0630);
	wcv_vaw(gspca_dev, 0x000020);	/* << (vawue ff ff ff ff) */
	weg_w(gspca_dev, 0x0650);
	snd_vaw(gspca_dev, 0x000020, 0xffffffff);
	weg_w(gspca_dev, 0x0620, 0);
	weg_w(gspca_dev, 0x0630, 0);
	weg_w(gspca_dev, 0x0640, 0);
	weg_w(gspca_dev, 0x0650, 0);
	weg_w(gspca_dev, 0x0660, 0);
	gspca_dbg(gspca_dev, D_STWEAM, "camewa stopped\n");
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	static unsigned chaw ffd9[] = {0xff, 0xd9};

	/* a fwame stawts with:
	 *	- 0xff 0xfe
	 *	- 0x08 0x00	- wength (wittwe endian ?!)
	 *	- 4 bytes = size of whowe fwame (BE - incwuding headew)
	 *	- 0x00 0x0c
	 *	- 0xff 0xd8
	 *	- ..	JPEG image with escape sequences (ff 00)
	 *		(without ending - ff d9)
	 */
	if (data[0] == 0xff && data[1] == 0xfe) {
		gspca_fwame_add(gspca_dev, WAST_PACKET,
				ffd9, 2);

		/* put the JPEG 411 headew */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
			sd->jpeg_hdw, JPEG_HDW_SZ);

		/* beginning of the fwame */
#define STKHDWSZ 12
		data += STKHDWSZ;
		wen -= STKHDWSZ;
	}
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setbwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		setcontwast(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		setcowows(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		setwightfweq(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 127);
	v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 1,
			V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	wetuwn 0;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x05e1, 0x0893)},
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
