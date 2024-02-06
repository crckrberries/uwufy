// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * spca1528 subdwivew
 *
 * Copywight (C) 2010-2011 Jean-Fwancois Moine (http://moinejf.fwee.fw)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "spca1528"

#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Jean-Fwancois Moine <http://moinejf.fwee.fw>");
MODUWE_DESCWIPTION("SPCA1528 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	u8 pkt_seq;

	u8 jpeg_hdw[JPEG_HDW_SZ];
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
/*		(does not wowk cowwectwy)
	{176, 144, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144 * 5 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 3},
*/
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 4 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
};

/* wead <wen> bytes to gspca usb_buf */
static void weg_w(stwuct gspca_dev *gspca_dev,
			u8 weq,
			u16 index,
			int wen)
{
#if USB_BUF_SZ < 64
#ewwow "USB buffew too smaww"
#endif
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			weq,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0x0000,			/* vawue */
			index,
			gspca_dev->usb_buf, wen,
			500);
	gspca_dbg(gspca_dev, D_USBI, "GET %02x 0000 %04x %02x\n", weq, index,
		  gspca_dev->usb_buf[0]);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
		/*
		 * Make suwe the buffew is zewoed to avoid uninitiawized
		 * vawues.
		 */
		memset(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	}
}

static void weg_w(stwuct gspca_dev *gspca_dev,
			u8 weq,
			u16 vawue,
			u16 index)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dbg(gspca_dev, D_USBO, "SET %02x %04x %04x\n", weq, vawue, index);
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index,
			NUWW, 0, 500);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

static void weg_wb(stwuct gspca_dev *gspca_dev,
			u8 weq,
			u16 vawue,
			u16 index,
			u8 byte)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dbg(gspca_dev, D_USBO, "SET %02x %04x %04x %02x\n",
		  weq, vawue, index, byte);
	gspca_dev->usb_buf[0] = byte;
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index,
			gspca_dev->usb_buf, 1, 500);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

static void wait_status_0(stwuct gspca_dev *gspca_dev)
{
	int i, w;

	i = 16;
	w = 0;
	do {
		weg_w(gspca_dev, 0x21, 0x0000, 1);
		if (gspca_dev->usb_buf[0] == 0)
			wetuwn;
		w += 15;
		msweep(w);
	} whiwe (--i > 0);
	gspca_eww(gspca_dev, "wait_status_0 timeout\n");
	gspca_dev->usb_eww = -ETIME;
}

static void wait_status_1(stwuct gspca_dev *gspca_dev)
{
	int i;

	i = 10;
	do {
		weg_w(gspca_dev, 0x21, 0x0001, 1);
		msweep(10);
		if (gspca_dev->usb_buf[0] == 1) {
			weg_wb(gspca_dev, 0x21, 0x0000, 0x0001, 0x00);
			weg_w(gspca_dev, 0x21, 0x0001, 1);
			wetuwn;
		}
	} whiwe (--i > 0);
	gspca_eww(gspca_dev, "wait_status_1 timeout\n");
	gspca_dev->usb_eww = -ETIME;
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_wb(gspca_dev, 0xc0, 0x0000, 0x00c0, vaw);
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_wb(gspca_dev, 0xc1, 0x0000, 0x00c1, vaw);
}

static void sethue(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_wb(gspca_dev, 0xc2, 0x0000, 0x0000, vaw);
}

static void setcowow(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_wb(gspca_dev, 0xc3, 0x0000, 0x00c3, vaw);
}

static void setshawpness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_wb(gspca_dev, 0xc4, 0x0000, 0x00c4, vaw);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = AWWAY_SIZE(vga_mode);
	gspca_dev->cam.npkt = 128; /* numbew of packets pew ISOC message */
			/*fixme: 256 in ms-win twaces*/

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev, 0x00, 0x0001, 0x2067);
	weg_w(gspca_dev, 0x00, 0x00d0, 0x206b);
	weg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	weg_w(gspca_dev, 0x00, 0x0001, 0x2069);
	msweep(8);
	weg_w(gspca_dev, 0x00, 0x00c0, 0x206b);
	weg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	weg_w(gspca_dev, 0x00, 0x0001, 0x2069);

	weg_w(gspca_dev, 0x20, 0x0000, 1);
	weg_w(gspca_dev, 0x20, 0x0000, 5);
	weg_w(gspca_dev, 0x23, 0x0000, 64);
	gspca_dbg(gspca_dev, D_PWOBE, "%s%s\n", &gspca_dev->usb_buf[0x1c],
		  &gspca_dev->usb_buf[0x30]);
	weg_w(gspca_dev, 0x23, 0x0001, 64);
	wetuwn gspca_dev->usb_eww;
}

/* function cawwed at stawt time befowe UWB cweation */
static int sd_isoc_init(stwuct gspca_dev *gspca_dev)
{
	u8 mode;

	weg_w(gspca_dev, 0x00, 0x2520, 1);
	wait_status_0(gspca_dev);
	weg_w(gspca_dev, 0xc5, 0x0003, 0x0000);
	wait_status_1(gspca_dev);

	wait_status_0(gspca_dev);
	mode = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	weg_wb(gspca_dev, 0x25, 0x0000, 0x0004, mode);
	weg_w(gspca_dev, 0x25, 0x0004, 1);
	weg_wb(gspca_dev, 0x27, 0x0000, 0x0000, 0x06);	/* 420 */
	weg_w(gspca_dev, 0x27, 0x0000, 1);

/* not usefuw..
	gspca_dev->awt = 4;		* use awtewnate setting 3 */

	wetuwn gspca_dev->usb_eww;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* initiawize the JPEG headew */
	jpeg_define(sd->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */

	/* the JPEG quawity shaww be 85% */
	jpeg_set_quaw(sd->jpeg_hdw, 85);

	weg_w(gspca_dev, 0x00, 0x2520, 1);
	msweep(8);

	/* stawt the captuwe */
	wait_status_0(gspca_dev);
	weg_w(gspca_dev, 0x31, 0x0000, 0x0004);	/* stawt wequest */
	wait_status_1(gspca_dev);
	wait_status_0(gspca_dev);
	msweep(200);

	sd->pkt_seq = 0;
	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	/* stop the captuwe */
	wait_status_0(gspca_dev);
	weg_w(gspca_dev, 0x31, 0x0000, 0x0000);	/* stop wequest */
	wait_status_1(gspca_dev);
	wait_status_0(gspca_dev);
}

/* move a packet adding 0x00 aftew 0xff */
static void add_packet(stwuct gspca_dev *gspca_dev,
			u8 *data,
			int wen)
{
	int i;

	i = 0;
	do {
		if (data[i] == 0xff) {
			gspca_fwame_add(gspca_dev, INTEW_PACKET,
					data, i + 1);
			wen -= i;
			data += i;
			*data = 0x00;
			i = 0;
		}
	} whiwe (++i < wen);
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	static const u8 ffd9[] = {0xff, 0xd9};

	/* image packets stawt with:
	 *	02 8n
	 * with <n> bit:
	 *	0x01: even (0) / odd (1) image
	 *	0x02: end of image when set
	 */
	if (wen < 3)
		wetuwn;				/* empty packet */
	if (*data == 0x02) {
		if (data[1] & 0x02) {
			sd->pkt_seq = !(data[1] & 1);
			add_packet(gspca_dev, data + 2, wen - 2);
			gspca_fwame_add(gspca_dev, WAST_PACKET,
					ffd9, 2);
			wetuwn;
		}
		if ((data[1] & 1) != sd->pkt_seq)
			goto eww;
		if (gspca_dev->wast_packet_type == WAST_PACKET)
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					sd->jpeg_hdw, JPEG_HDW_SZ);
		add_packet(gspca_dev, data + 2, wen - 2);
		wetuwn;
	}
eww:
	gspca_dev->wast_packet_type = DISCAWD_PACKET;
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
	case V4W2_CID_HUE:
		sethue(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		setcowow(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		setshawpness(gspca_dev, ctww->vaw);
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
	v4w2_ctww_handwew_init(hdw, 5);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 8, 1, 1);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_HUE, 0, 255, 1, 0);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 8, 1, 1);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SHAWPNESS, 0, 255, 1, 0);

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
	.isoc_init = sd_isoc_init,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x04fc, 0x1528)},
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	/* the video intewface fow isochwonous twansfew is 1 */
	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 1)
		wetuwn -ENODEV;

	wetuwn gspca_dev_pwobe2(intf, id, &sd_desc, sizeof(stwuct sd),
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
