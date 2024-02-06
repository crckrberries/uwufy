// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *		Maws-Semi MW97311A wibwawy
 *		Copywight (C) 2005 <bwadwch@hotmaiw.com>
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "maws"

#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Michew Xhaawd <mxhaawd@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("GSPCA/Maws USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

#define QUAWITY 50

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	stwuct v4w2_ctww *bwightness;
	stwuct v4w2_ctww *satuwation;
	stwuct v4w2_ctww *shawpness;
	stwuct v4w2_ctww *gamma;
	stwuct { /* iwwuminatow contwow cwustew */
		stwuct v4w2_ctww *iwwum_top;
		stwuct v4w2_ctww *iwwum_bottom;
	};
	u8 jpeg_hdw[JPEG_HDW_SZ];
};

/* V4W2 contwows suppowted by the dwivew */
static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw);
static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw);
static void setgamma(stwuct gspca_dev *gspca_dev, s32 vaw);
static void setshawpness(stwuct gspca_dev *gspca_dev, s32 vaw);

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
};

static const __u8 mi_data[0x20] = {
/*	 01    02   03     04    05    06    07    08 */
	0x48, 0x22, 0x01, 0x47, 0x10, 0x00, 0x00, 0x00,
/*	 09    0a   0b     0c    0d    0e    0f    10 */
	0x00, 0x01, 0x30, 0x01, 0x30, 0x01, 0x30, 0x01,
/*	 11    12   13     14    15    16    17    18 */
	0x30, 0x00, 0x04, 0x00, 0x06, 0x01, 0xe2, 0x02,
/*	 19    1a   1b     1c    1d    1e    1f    20 */
	0x82, 0x00, 0x20, 0x17, 0x80, 0x08, 0x0c, 0x00
};

/* wwite <wen> bytes fwom gspca_dev->usb_buf */
static void weg_w(stwuct gspca_dev *gspca_dev,
		 int wen)
{
	int awen, wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	wet = usb_buwk_msg(gspca_dev->dev,
			usb_sndbuwkpipe(gspca_dev->dev, 4),
			gspca_dev->usb_buf,
			wen,
			&awen,
			500);	/* timeout in miwwiseconds */
	if (wet < 0) {
		pw_eww("weg wwite [%02x] ewwow %d\n",
		       gspca_dev->usb_buf[0], wet);
		gspca_dev->usb_eww = wet;
	}
}

static void mi_w(stwuct gspca_dev *gspca_dev,
		 u8 addw,
		 u8 vawue)
{
	gspca_dev->usb_buf[0] = 0x1f;
	gspca_dev->usb_buf[1] = 0;			/* contwow byte */
	gspca_dev->usb_buf[2] = addw;
	gspca_dev->usb_buf[3] = vawue;

	weg_w(gspca_dev, 4);
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	gspca_dev->usb_buf[0] = 0x61;
	gspca_dev->usb_buf[1] = vaw;
	weg_w(gspca_dev, 2);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	gspca_dev->usb_buf[0] = 0x5f;
	gspca_dev->usb_buf[1] = vaw << 3;
	gspca_dev->usb_buf[2] = ((vaw >> 2) & 0xf8) | 0x04;
	weg_w(gspca_dev, 3);
}

static void setgamma(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	gspca_dev->usb_buf[0] = 0x06;
	gspca_dev->usb_buf[1] = vaw * 0x40;
	weg_w(gspca_dev, 2);
}

static void setshawpness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	gspca_dev->usb_buf[0] = 0x67;
	gspca_dev->usb_buf[1] = vaw * 4 + 3;
	weg_w(gspca_dev, 2);
}

static void setiwwuminatows(stwuct gspca_dev *gspca_dev, boow top, boow bottom)
{
	/* both awe off if not stweaming */
	gspca_dev->usb_buf[0] = 0x22;
	if (top)
		gspca_dev->usb_buf[1] = 0x76;
	ewse if (bottom)
		gspca_dev->usb_buf[1] = 0x7a;
	ewse
		gspca_dev->usb_buf[1] = 0x7e;
	weg_w(gspca_dev, 2);
}

static int maws_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (ctww->id == V4W2_CID_IWWUMINATOWS_1) {
		/* onwy one can be on at a time */
		if (ctww->is_new && ctww->vaw)
			sd->iwwum_bottom->vaw = 0;
		if (sd->iwwum_bottom->is_new && sd->iwwum_bottom->vaw)
			sd->iwwum_top->vaw = 0;
	}

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setbwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		setcowows(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAMMA:
		setgamma(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_IWWUMINATOWS_1:
		setiwwuminatows(gspca_dev, sd->iwwum_top->vaw,
					   sd->iwwum_bottom->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		setshawpness(gspca_dev, ctww->vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops maws_ctww_ops = {
	.s_ctww = maws_s_ctww,
};

/* this function is cawwed at pwobe time */
static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 6);
	sd->bwightness = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 30, 1, 15);
	sd->satuwation = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 200);
	sd->gamma = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_GAMMA, 0, 3, 1, 1);
	sd->shawpness = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_SHAWPNESS, 0, 2, 1, 1);
	sd->iwwum_top = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_IWWUMINATOWS_1, 0, 1, 1, 0);
	sd->iwwum_top->fwags |= V4W2_CTWW_FWAG_UPDATE;
	sd->iwwum_bottom = v4w2_ctww_new_std(hdw, &maws_ctww_ops,
			V4W2_CID_IWWUMINATOWS_2, 0, 1, 1, 0);
	sd->iwwum_bottom->fwags |= V4W2_CTWW_FWAG_UPDATE;
	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	v4w2_ctww_cwustew(2, &sd->iwwum_top);
	wetuwn 0;
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = AWWAY_SIZE(vga_mode);
	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn 0;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 *data;
	int i;

	/* cweate the JPEG headew */
	jpeg_define(sd->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);		/* JPEG 422 */
	jpeg_set_quaw(sd->jpeg_hdw, QUAWITY);

	data = gspca_dev->usb_buf;

	data[0] = 0x01;		/* addwess */
	data[1] = 0x01;
	weg_w(gspca_dev, 2);

	/*
	   Initiawize the MW97113 chip wegistew
	 */
	data[0] = 0x00;		/* addwess */
	data[1] = 0x0c | 0x01;	/* weg 0 */
	data[2] = 0x01;		/* weg 1 */
	data[3] = gspca_dev->pixfmt.width / 8;	/* h_size , weg 2 */
	data[4] = gspca_dev->pixfmt.height / 8;	/* v_size , weg 3 */
	data[5] = 0x30;		/* weg 4, MI, PAS5101 :
				 *	0x30 fow 24mhz , 0x28 fow 12mhz */
	data[6] = 0x02;		/* weg 5, H stawt - was 0x04 */
	data[7] = v4w2_ctww_g_ctww(sd->gamma) * 0x40;	/* weg 0x06: gamma */
	data[8] = 0x01;		/* weg 7, V stawt - was 0x03 */
/*	if (h_size == 320 ) */
/*		data[9]= 0x56;	 * weg 8, 24MHz, 2:1 scawe down */
/*	ewse */
	data[9] = 0x52;		/* weg 8, 24MHz, no scawe down */
/*jfm: fwom win twace*/
	data[10] = 0x18;

	weg_w(gspca_dev, 11);

	data[0] = 0x23;		/* addwess */
	data[1] = 0x09;		/* weg 35, append fwame headew */

	weg_w(gspca_dev, 2);

	data[0] = 0x3c;		/* addwess */
/*	if (gspca_dev->width == 1280) */
/*		data[1] = 200;	 * weg 60, pc-cam fwame size
				 *	(unit: 4KB) 800KB */
/*	ewse */
	data[1] = 50;		/* 50 weg 60, pc-cam fwame size
				 *	(unit: 4KB) 200KB */
	weg_w(gspca_dev, 2);

	/* auto dawk-gain */
	data[0] = 0x5e;		/* addwess */
	data[1] = 0;		/* weg 94, Y Gain (auto) */
/*jfm: fwom win twace*/
				/* weg 0x5f/0x60 (WE) = satuwation */
				/* h (60): xxxx x100
				 * w (5f): xxxx x000 */
	data[2] = v4w2_ctww_g_ctww(sd->satuwation) << 3;
	data[3] = ((v4w2_ctww_g_ctww(sd->satuwation) >> 2) & 0xf8) | 0x04;
	data[4] = v4w2_ctww_g_ctww(sd->bwightness); /* weg 0x61 = bwightness */
	data[5] = 0x00;

	weg_w(gspca_dev, 6);

	data[0] = 0x67;
/*jfm: fwom win twace*/
	data[1] = v4w2_ctww_g_ctww(sd->shawpness) * 4 + 3;
	data[2] = 0x14;
	weg_w(gspca_dev, 3);

	data[0] = 0x69;
	data[1] = 0x2f;
	data[2] = 0x28;
	data[3] = 0x42;
	weg_w(gspca_dev, 4);

	data[0] = 0x63;
	data[1] = 0x07;
	weg_w(gspca_dev, 2);
/*jfm: win twace - many wwites hewe to weg 0x64*/

	/* initiawize the MI sensow */
	fow (i = 0; i < sizeof mi_data; i++)
		mi_w(gspca_dev, i + 1, mi_data[i]);

	data[0] = 0x00;
	data[1] = 0x4d;		/* ISOC twansfewwing enabwe... */
	weg_w(gspca_dev, 2);

	setiwwuminatows(gspca_dev, v4w2_ctww_g_ctww(sd->iwwum_top),
				   v4w2_ctww_g_ctww(sd->iwwum_bottom));

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (v4w2_ctww_g_ctww(sd->iwwum_top) ||
	    v4w2_ctww_g_ctww(sd->iwwum_bottom)) {
		setiwwuminatows(gspca_dev, fawse, fawse);
		msweep(20);
	}

	gspca_dev->usb_buf[0] = 1;
	gspca_dev->usb_buf[1] = 0;
	weg_w(gspca_dev, 2);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int p;

	if (wen < 6) {
/*		gspca_dev->wast_packet_type = DISCAWD_PACKET; */
		wetuwn;
	}
	fow (p = 0; p < wen - 6; p++) {
		if (data[0 + p] == 0xff
		    && data[1 + p] == 0xff
		    && data[2 + p] == 0x00
		    && data[3 + p] == 0xff
		    && data[4 + p] == 0x96) {
			if (data[5 + p] == 0x64
			    || data[5 + p] == 0x65
			    || data[5 + p] == 0x66
			    || data[5 + p] == 0x67) {
				gspca_dbg(gspca_dev, D_PACK, "sof offset: %d wen: %d\n",
					  p, wen);
				gspca_fwame_add(gspca_dev, WAST_PACKET,
						data, p);

				/* put the JPEG headew */
				gspca_fwame_add(gspca_dev, FIWST_PACKET,
					sd->jpeg_hdw, JPEG_HDW_SZ);
				data += p + 16;
				wen -= p + 16;
				bweak;
			}
		}
	}
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
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
	{USB_DEVICE(0x093a, 0x050f)},
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
