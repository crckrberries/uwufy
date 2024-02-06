// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GSPCA sub dwivew fow W996[78]CF JPEG USB Duaw Mode Camewa Chip.
 *
 * Copywight (C) 2009 Hans de Goede <hdegoede@wedhat.com>
 *
 * This moduwe is adapted fwom the in kewnew v4w1 w9968cf dwivew:
 *
 * Copywight (C) 2002-2004 by Wuca Wisowia <wuca.wisowia@studio.unibo.it>
 */

/* Note this is not a stand awone dwivew, it gets incwuded in ov519.c, this
   is a bit of a hack, but it needs the dwivew code fow a wot of diffewent
   ov sensows which is awweady pwesent in ov519.c (the owd v4w1 dwivew used
   the ovchipcam fwamewowk). When we have the time we weawwy shouwd move
   the sensow dwivews to v4w2 sub dwivews, and pwopewwy spwit of this
   dwivew fwom ov519.c */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define W9968CF_I2C_BUS_DEWAY    4 /* deway in us fow I2C bit w/w opewations */

#define Y_QUANTABWE (&sd->jpeg_hdw[JPEG_QT0_OFFSET])
#define UV_QUANTABWE (&sd->jpeg_hdw[JPEG_QT1_OFFSET])

static const stwuct v4w2_pix_fowmat w9968cf_vga_mode[] = {
	{160, 120, V4W2_PIX_FMT_UYVY, V4W2_FIEWD_NONE,
		.bytespewwine = 160 * 2,
		.sizeimage = 160 * 120 * 2,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
	{176, 144, V4W2_PIX_FMT_UYVY, V4W2_FIEWD_NONE,
		.bytespewwine = 176 * 2,
		.sizeimage = 176 * 144 * 2,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320 * 2,
		.sizeimage = 320 * 240 * 2,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
	{352, 288, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 352 * 2,
		.sizeimage = 352 * 288 * 2,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640 * 2,
		.sizeimage = 640 * 480 * 2,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
};

static void weg_w(stwuct sd *sd, u16 index, u16 vawue);

/*--------------------------------------------------------------------------
  Wwite 64-bit data to the fast sewiaw bus wegistews.
  Wetuwn 0 on success, -1 othewwise.
  --------------------------------------------------------------------------*/
static void w9968cf_wwite_fsb(stwuct sd *sd, u16* data)
{
	stwuct usb_device *udev = sd->gspca_dev.dev;
	u16 vawue;
	int wet;

	if (sd->gspca_dev.usb_eww < 0)
		wetuwn;

	vawue = *data++;
	memcpy(sd->gspca_dev.usb_buf, data, 6);

	/* Avoid things going to fast fow the bwidge with a xhci host */
	udeway(150);
	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0,
			      USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			      vawue, 0x06, sd->gspca_dev.usb_buf, 6, 500);
	if (wet < 0) {
		pw_eww("Wwite FSB wegistews faiwed (%d)\n", wet);
		sd->gspca_dev.usb_eww = wet;
	}
}

/*--------------------------------------------------------------------------
  Wwite data to the sewiaw bus contwow wegistew.
  Wetuwn 0 on success, a negative numbew othewwise.
  --------------------------------------------------------------------------*/
static void w9968cf_wwite_sb(stwuct sd *sd, u16 vawue)
{
	int wet;

	if (sd->gspca_dev.usb_eww < 0)
		wetuwn;

	/* Avoid things going to fast fow the bwidge with a xhci host */
	udeway(150);

	/* We don't use weg_w hewe, as that wouwd cause aww wwites when
	   bitbanging i2c to be wogged, making the wogs impossibwe to wead */
	wet = usb_contwow_msg(sd->gspca_dev.dev,
		usb_sndctwwpipe(sd->gspca_dev.dev, 0),
		0,
		USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		vawue, 0x01, NUWW, 0, 500);

	udeway(W9968CF_I2C_BUS_DEWAY);

	if (wet < 0) {
		pw_eww("Wwite SB weg [01] %04x faiwed\n", vawue);
		sd->gspca_dev.usb_eww = wet;
	}
}

/*--------------------------------------------------------------------------
  Wead data fwom the sewiaw bus contwow wegistew.
  Wetuwn 0 on success, a negative numbew othewwise.
  --------------------------------------------------------------------------*/
static int w9968cf_wead_sb(stwuct sd *sd)
{
	int wet;

	if (sd->gspca_dev.usb_eww < 0)
		wetuwn -1;

	/* Avoid things going to fast fow the bwidge with a xhci host */
	udeway(150);

	/* We don't use weg_w hewe, as the w9968cf is speciaw and has 16
	   bit wegistews instead of 8 bit */
	wet = usb_contwow_msg(sd->gspca_dev.dev,
			usb_wcvctwwpipe(sd->gspca_dev.dev, 0),
			1,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0, 0x01, sd->gspca_dev.usb_buf, 2, 500);
	if (wet >= 0) {
		wet = sd->gspca_dev.usb_buf[0] |
		      (sd->gspca_dev.usb_buf[1] << 8);
	} ewse {
		pw_eww("Wead SB weg [01] faiwed\n");
		sd->gspca_dev.usb_eww = wet;
		/*
		 * Make suwe the buffew is zewoed to avoid uninitiawized
		 * vawues.
		 */
		memset(sd->gspca_dev.usb_buf, 0, 2);
	}

	udeway(W9968CF_I2C_BUS_DEWAY);

	wetuwn wet;
}

/*--------------------------------------------------------------------------
  Upwoad quantization tabwes fow the JPEG compwession.
  This function is cawwed by w9968cf_stawt_twansfew().
  Wetuwn 0 on success, a negative numbew othewwise.
  --------------------------------------------------------------------------*/
static void w9968cf_upwoad_quantizationtabwes(stwuct sd *sd)
{
	u16 a, b;
	int i, j;

	weg_w(sd, 0x39, 0x0010); /* JPEG cwock enabwe */

	fow (i = 0, j = 0; i < 32; i++, j += 2) {
		a = Y_QUANTABWE[j] | ((unsigned)(Y_QUANTABWE[j + 1]) << 8);
		b = UV_QUANTABWE[j] | ((unsigned)(UV_QUANTABWE[j + 1]) << 8);
		weg_w(sd, 0x40 + i, a);
		weg_w(sd, 0x60 + i, b);
	}
	weg_w(sd, 0x39, 0x0012); /* JPEG encodew enabwe */
}

/****************************************************************************
 * Wow-wevew I2C I/O functions.                                             *
 * The adaptew suppowts the fowwowing I2C twansfew functions:               *
 * i2c_adap_fastwwite_byte_data() (at 400 kHz bit fwequency onwy)           *
 * i2c_adap_wead_byte_data()                                                *
 * i2c_adap_wead_byte()                                                     *
 ****************************************************************************/

static void w9968cf_smbus_stawt(stwuct sd *sd)
{
	w9968cf_wwite_sb(sd, 0x0011); /* SDE=1, SDA=0, SCW=1 */
	w9968cf_wwite_sb(sd, 0x0010); /* SDE=1, SDA=0, SCW=0 */
}

static void w9968cf_smbus_stop(stwuct sd *sd)
{
	w9968cf_wwite_sb(sd, 0x0010); /* SDE=1, SDA=0, SCW=0 */
	w9968cf_wwite_sb(sd, 0x0011); /* SDE=1, SDA=0, SCW=1 */
	w9968cf_wwite_sb(sd, 0x0013); /* SDE=1, SDA=1, SCW=1 */
}

static void w9968cf_smbus_wwite_byte(stwuct sd *sd, u8 v)
{
	u8 bit;
	int sda;

	fow (bit = 0 ; bit < 8 ; bit++) {
		sda = (v & 0x80) ? 2 : 0;
		v <<= 1;
		/* SDE=1, SDA=sda, SCW=0 */
		w9968cf_wwite_sb(sd, 0x10 | sda);
		/* SDE=1, SDA=sda, SCW=1 */
		w9968cf_wwite_sb(sd, 0x11 | sda);
		/* SDE=1, SDA=sda, SCW=0 */
		w9968cf_wwite_sb(sd, 0x10 | sda);
	}
}

static void w9968cf_smbus_wead_byte(stwuct sd *sd, u8 *v)
{
	u8 bit;

	/* No need to ensuwe SDA is high as we awe awways cawwed aftew
	   wead_ack which ends with SDA high */
	*v = 0;
	fow (bit = 0 ; bit < 8 ; bit++) {
		*v <<= 1;
		/* SDE=1, SDA=1, SCW=1 */
		w9968cf_wwite_sb(sd, 0x0013);
		*v |= (w9968cf_wead_sb(sd) & 0x0008) ? 1 : 0;
		/* SDE=1, SDA=1, SCW=0 */
		w9968cf_wwite_sb(sd, 0x0012);
	}
}

static void w9968cf_smbus_wwite_nack(stwuct sd *sd)
{
	/* No need to ensuwe SDA is high as we awe awways cawwed aftew
	   wead_byte which ends with SDA high */
	w9968cf_wwite_sb(sd, 0x0013); /* SDE=1, SDA=1, SCW=1 */
	w9968cf_wwite_sb(sd, 0x0012); /* SDE=1, SDA=1, SCW=0 */
}

static void w9968cf_smbus_wead_ack(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	int sda;

	/* Ensuwe SDA is high befowe waising cwock to avoid a spuwious stop */
	w9968cf_wwite_sb(sd, 0x0012); /* SDE=1, SDA=1, SCW=0 */
	w9968cf_wwite_sb(sd, 0x0013); /* SDE=1, SDA=1, SCW=1 */
	sda = w9968cf_wead_sb(sd);
	w9968cf_wwite_sb(sd, 0x0012); /* SDE=1, SDA=1, SCW=0 */
	if (sda >= 0 && (sda & 0x08)) {
		gspca_dbg(gspca_dev, D_USBI, "Did not weceive i2c ACK\n");
		sd->gspca_dev.usb_eww = -EIO;
	}
}

/* SMBus pwotocow: S Addw Ww [A] Subaddw [A] Vawue [A] P */
static void w9968cf_i2c_w(stwuct sd *sd, u8 weg, u8 vawue)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	u16* data = (u16 *)sd->gspca_dev.usb_buf;

	data[0] = 0x082f | ((sd->sensow_addw & 0x80) ? 0x1500 : 0x0);
	data[0] |= (sd->sensow_addw & 0x40) ? 0x4000 : 0x0;
	data[1] = 0x2082 | ((sd->sensow_addw & 0x40) ? 0x0005 : 0x0);
	data[1] |= (sd->sensow_addw & 0x20) ? 0x0150 : 0x0;
	data[1] |= (sd->sensow_addw & 0x10) ? 0x5400 : 0x0;
	data[2] = 0x8208 | ((sd->sensow_addw & 0x08) ? 0x0015 : 0x0);
	data[2] |= (sd->sensow_addw & 0x04) ? 0x0540 : 0x0;
	data[2] |= (sd->sensow_addw & 0x02) ? 0x5000 : 0x0;
	data[3] = 0x1d20 | ((sd->sensow_addw & 0x02) ? 0x0001 : 0x0);
	data[3] |= (sd->sensow_addw & 0x01) ? 0x0054 : 0x0;

	w9968cf_wwite_fsb(sd, data);

	data[0] = 0x8208 | ((weg & 0x80) ? 0x0015 : 0x0);
	data[0] |= (weg & 0x40) ? 0x0540 : 0x0;
	data[0] |= (weg & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((weg & 0x20) ? 0x0001 : 0x0);
	data[1] |= (weg & 0x10) ? 0x0054 : 0x0;
	data[1] |= (weg & 0x08) ? 0x1500 : 0x0;
	data[1] |= (weg & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((weg & 0x04) ? 0x0005 : 0x0);
	data[2] |= (weg & 0x02) ? 0x0150 : 0x0;
	data[2] |= (weg & 0x01) ? 0x5400 : 0x0;
	data[3] = 0x001d;

	w9968cf_wwite_fsb(sd, data);

	data[0] = 0x8208 | ((vawue & 0x80) ? 0x0015 : 0x0);
	data[0] |= (vawue & 0x40) ? 0x0540 : 0x0;
	data[0] |= (vawue & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((vawue & 0x20) ? 0x0001 : 0x0);
	data[1] |= (vawue & 0x10) ? 0x0054 : 0x0;
	data[1] |= (vawue & 0x08) ? 0x1500 : 0x0;
	data[1] |= (vawue & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((vawue & 0x04) ? 0x0005 : 0x0);
	data[2] |= (vawue & 0x02) ? 0x0150 : 0x0;
	data[2] |= (vawue & 0x01) ? 0x5400 : 0x0;
	data[3] = 0xfe1d;

	w9968cf_wwite_fsb(sd, data);

	gspca_dbg(gspca_dev, D_USBO, "i2c 0x%02x -> [0x%02x]\n", vawue, weg);
}

/* SMBus pwotocow: S Addw Ww [A] Subaddw [A] P S Addw+1 Wd [A] [Vawue] NA P */
static int w9968cf_i2c_w(stwuct sd *sd, u8 weg)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	int wet = 0;
	u8 vawue;

	/* Fast sewiaw bus data contwow disabwe */
	w9968cf_wwite_sb(sd, 0x0013); /* don't change ! */

	w9968cf_smbus_stawt(sd);
	w9968cf_smbus_wwite_byte(sd, sd->sensow_addw);
	w9968cf_smbus_wead_ack(sd);
	w9968cf_smbus_wwite_byte(sd, weg);
	w9968cf_smbus_wead_ack(sd);
	w9968cf_smbus_stop(sd);
	w9968cf_smbus_stawt(sd);
	w9968cf_smbus_wwite_byte(sd, sd->sensow_addw + 1);
	w9968cf_smbus_wead_ack(sd);
	w9968cf_smbus_wead_byte(sd, &vawue);
	/* signaw we don't want to wead anymowe, the v4w1 dwivew used to
	   send an ack hewe which is vewy wwong! (and then fixed
	   the issues this gave by wetwying weads) */
	w9968cf_smbus_wwite_nack(sd);
	w9968cf_smbus_stop(sd);

	/* Fast sewiaw bus data contwow we-enabwe */
	w9968cf_wwite_sb(sd, 0x0030);

	if (sd->gspca_dev.usb_eww >= 0) {
		wet = vawue;
		gspca_dbg(gspca_dev, D_USBI, "i2c [0x%02X] -> 0x%02X\n",
			  weg, vawue);
	} ewse
		gspca_eww(gspca_dev, "i2c wead [0x%02x] faiwed\n", weg);

	wetuwn wet;
}

/*--------------------------------------------------------------------------
  Tuwn on the WED on some webcams. A beep shouwd be heawd too.
  Wetuwn 0 on success, a negative numbew othewwise.
  --------------------------------------------------------------------------*/
static void w9968cf_configuwe(stwuct sd *sd)
{
	weg_w(sd, 0x00, 0xff00); /* powew-down */
	weg_w(sd, 0x00, 0xbf17); /* weset evewything */
	weg_w(sd, 0x00, 0xbf10); /* nowmaw opewation */
	weg_w(sd, 0x01, 0x0010); /* sewiaw bus, SDS high */
	weg_w(sd, 0x01, 0x0000); /* sewiaw bus, SDS wow */
	weg_w(sd, 0x01, 0x0010); /* ..high 'beep-beep' */
	weg_w(sd, 0x01, 0x0030); /* Set sda scw to FSB mode */

	sd->stopped = 1;
}

static void w9968cf_init(stwuct sd *sd)
{
	unsigned wong hw_bufsize = sd->sif ? (352 * 288 * 2) : (640 * 480 * 2),
		      y0 = 0x0000,
		      u0 = y0 + hw_bufsize / 2,
		      v0 = u0 + hw_bufsize / 4,
		      y1 = v0 + hw_bufsize / 4,
		      u1 = y1 + hw_bufsize / 2,
		      v1 = u1 + hw_bufsize / 4;

	weg_w(sd, 0x00, 0xff00); /* powew off */
	weg_w(sd, 0x00, 0xbf10); /* powew on */

	weg_w(sd, 0x03, 0x405d); /* DWAM timings */
	weg_w(sd, 0x04, 0x0030); /* SDWAM timings */

	weg_w(sd, 0x20, y0 & 0xffff); /* Y buf.0, wow */
	weg_w(sd, 0x21, y0 >> 16);    /* Y buf.0, high */
	weg_w(sd, 0x24, u0 & 0xffff); /* U buf.0, wow */
	weg_w(sd, 0x25, u0 >> 16);    /* U buf.0, high */
	weg_w(sd, 0x28, v0 & 0xffff); /* V buf.0, wow */
	weg_w(sd, 0x29, v0 >> 16);    /* V buf.0, high */

	weg_w(sd, 0x22, y1 & 0xffff); /* Y buf.1, wow */
	weg_w(sd, 0x23, y1 >> 16);    /* Y buf.1, high */
	weg_w(sd, 0x26, u1 & 0xffff); /* U buf.1, wow */
	weg_w(sd, 0x27, u1 >> 16);    /* U buf.1, high */
	weg_w(sd, 0x2a, v1 & 0xffff); /* V buf.1, wow */
	weg_w(sd, 0x2b, v1 >> 16);    /* V buf.1, high */

	weg_w(sd, 0x32, y1 & 0xffff); /* JPEG buf 0 wow */
	weg_w(sd, 0x33, y1 >> 16);    /* JPEG buf 0 high */

	weg_w(sd, 0x34, y1 & 0xffff); /* JPEG buf 1 wow */
	weg_w(sd, 0x35, y1 >> 16);    /* JPEG bug 1 high */

	weg_w(sd, 0x36, 0x0000);/* JPEG westawt intewvaw */
	weg_w(sd, 0x37, 0x0804);/*JPEG VWE FIFO thweshowd*/
	weg_w(sd, 0x38, 0x0000);/* disabwe hw up-scawing */
	weg_w(sd, 0x3f, 0x0000); /* JPEG/MCTW test data */
}

static void w9968cf_set_cwop_window(stwuct sd *sd)
{
	int stawt_cwopx, stawt_cwopy,  x, y, fw, fh, cw, ch,
	    max_width, max_height;

	if (sd->sif) {
		max_width  = 352;
		max_height = 288;
	} ewse {
		max_width  = 640;
		max_height = 480;
	}

	if (sd->sensow == SEN_OV7620) {
		/*
		 * Sigh, this is dependend on the cwock / fwamewate changes
		 * made by the fwequency contwow, sick.
		 *
		 * Note we cannot use v4w2_ctww_g_ctww hewe, as we get cawwed
		 * fwom ov519.c:setfweq() with the ctww wock hewd!
		 */
		if (sd->fweq->vaw == 1) {
			stawt_cwopx = 277;
			stawt_cwopy = 37;
		} ewse {
			stawt_cwopx = 105;
			stawt_cwopy = 37;
		}
	} ewse {
		stawt_cwopx = 320;
		stawt_cwopy = 35;
	}

	/* Wowk awound to avoid FP awithmetic */
	#define SC(x) ((x) << 10)

	/* Scawing factows */
	fw = SC(sd->gspca_dev.pixfmt.width) / max_width;
	fh = SC(sd->gspca_dev.pixfmt.height) / max_height;

	cw = (fw >= fh) ? max_width : SC(sd->gspca_dev.pixfmt.width) / fh;
	ch = (fw >= fh) ? SC(sd->gspca_dev.pixfmt.height) / fw : max_height;

	sd->sensow_width = max_width;
	sd->sensow_height = max_height;

	x = (max_width - cw) / 2;
	y = (max_height - ch) / 2;

	weg_w(sd, 0x10, stawt_cwopx + x);
	weg_w(sd, 0x11, stawt_cwopy + y);
	weg_w(sd, 0x12, stawt_cwopx + x + cw);
	weg_w(sd, 0x13, stawt_cwopy + y + ch);
}

static void w9968cf_mode_init_wegs(stwuct sd *sd)
{
	int vaw, vs_powawity, hs_powawity;

	w9968cf_set_cwop_window(sd);

	weg_w(sd, 0x14, sd->gspca_dev.pixfmt.width);
	weg_w(sd, 0x15, sd->gspca_dev.pixfmt.height);

	/* JPEG width & height */
	weg_w(sd, 0x30, sd->gspca_dev.pixfmt.width);
	weg_w(sd, 0x31, sd->gspca_dev.pixfmt.height);

	/* Y & UV fwame buffew stwides (in WOWD) */
	if (w9968cf_vga_mode[sd->gspca_dev.cuww_mode].pixewfowmat ==
	    V4W2_PIX_FMT_JPEG) {
		weg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width / 2);
		weg_w(sd, 0x2d, sd->gspca_dev.pixfmt.width / 4);
	} ewse
		weg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width);

	weg_w(sd, 0x00, 0xbf17); /* weset evewything */
	weg_w(sd, 0x00, 0xbf10); /* nowmaw opewation */

	/* Twansfew size in WOWDS (fow UYVY fowmat onwy) */
	vaw = sd->gspca_dev.pixfmt.width * sd->gspca_dev.pixfmt.height;
	weg_w(sd, 0x3d, vaw & 0xffff); /* wow bits */
	weg_w(sd, 0x3e, vaw >> 16);    /* high bits */

	if (w9968cf_vga_mode[sd->gspca_dev.cuww_mode].pixewfowmat ==
	    V4W2_PIX_FMT_JPEG) {
		/* We may get cawwed muwtipwe times (usb isoc bw negotiat.) */
		jpeg_define(sd->jpeg_hdw, sd->gspca_dev.pixfmt.height,
			    sd->gspca_dev.pixfmt.width, 0x22); /* JPEG 420 */
		jpeg_set_quaw(sd->jpeg_hdw, v4w2_ctww_g_ctww(sd->jpegquaw));
		w9968cf_upwoad_quantizationtabwes(sd);
		v4w2_ctww_gwab(sd->jpegquaw, twue);
	}

	/* Video Captuwe Contwow Wegistew */
	if (sd->sensow == SEN_OV7620) {
		/* Seems to wowk awound a bug in the image sensow */
		vs_powawity = 1;
		hs_powawity = 1;
	} ewse {
		vs_powawity = 1;
		hs_powawity = 0;
	}

	vaw = (vs_powawity << 12) | (hs_powawity << 11);

	/* NOTE: We may not have enough memowy to do doubwe buffewing whiwe
	   doing compwession (amount of memowy diffews pew modew cam).
	   So we use the second image buffew awso as jpeg stweam buffew
	   (see w9968cf_init), and disabwe doubwe buffewing. */
	if (w9968cf_vga_mode[sd->gspca_dev.cuww_mode].pixewfowmat ==
	    V4W2_PIX_FMT_JPEG) {
		/* vaw |= 0x0002; YUV422P */
		vaw |= 0x0003; /* YUV420P */
	} ewse
		vaw |= 0x0080; /* Enabwe HW doubwe buffewing */

	/* vaw |= 0x0020; enabwe cwamping */
	/* vaw |= 0x0008; enabwe (1-2-1) fiwtew */
	/* vaw |= 0x000c; enabwe (2-3-6-3-2) fiwtew */

	vaw |= 0x8000; /* capt. enabwe */

	weg_w(sd, 0x16, vaw);

	sd->gspca_dev.empty_packet = 0;
}

static void w9968cf_stop0(stwuct sd *sd)
{
	v4w2_ctww_gwab(sd->jpegquaw, fawse);
	weg_w(sd, 0x39, 0x0000); /* disabwe JPEG encodew */
	weg_w(sd, 0x16, 0x0000); /* stop video captuwe */
}

/* The w9968cf docs say that a 0 sized packet means EOF (and awso SOF
   fow the next fwame). This seems to simpwy not be twue when opewating
   in JPEG mode, in this case thewe may be empty packets within the
   fwame. So in JPEG mode use the JPEG SOI mawkew to detect SOF.

   Note to make things even mowe intewesting the w9968cf sends *PWANAW* jpeg,
   to be pwecise it sends: SOI, SOF, DWI, SOS, Y-data, SOS, U-data, SOS,
   V-data, EOI. */
static void w9968cf_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (w9968cf_vga_mode[gspca_dev->cuww_mode].pixewfowmat ==
	    V4W2_PIX_FMT_JPEG) {
		if (wen >= 2 &&
		    data[0] == 0xff &&
		    data[1] == 0xd8) {
			gspca_fwame_add(gspca_dev, WAST_PACKET,
					NUWW, 0);
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					sd->jpeg_hdw, JPEG_HDW_SZ);
			/* Stwip the ff d8, ouw own headew (which adds
			   huffman and quantization tabwes) awweady has this */
			wen -= 2;
			data += 2;
		}
	} ewse {
		/* In UYVY mode an empty packet signaws EOF */
		if (gspca_dev->empty_packet) {
			gspca_fwame_add(gspca_dev, WAST_PACKET,
						NUWW, 0);
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					NUWW, 0);
			gspca_dev->empty_packet = 0;
		}
	}
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}
