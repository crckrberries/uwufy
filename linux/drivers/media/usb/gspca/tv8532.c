// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Quickcam camewas initiawization data
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */
#define MODUWE_NAME "tv8532"

#incwude "gspca.h"

MODUWE_AUTHOW("Michew Xhaawd <mxhaawd@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("TV8532 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	__u8 packet;
};

static const stwuct v4w2_pix_fowmat sif_mode[] = {
	{176, 144, V4W2_PIX_FMT_SBGGW8, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1},
	{352, 288, V4W2_PIX_FMT_SBGGW8, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

/* TV-8532A (ICM532A) wegistews (WE) */
#define W00_PAWT_CONTWOW 0x00
#define		WATENT_CHANGE	0x80
#define		EXPO_CHANGE	0x04
#define W01_TIMING_CONTWOW_WOW 0x01
#define		CMD_EEpwom_Open 0x30
#define		CMD_EEpwom_Cwose 0x29
#define W03_TABWE_ADDW 0x03
#define W04_WTWAM_DATA_W 0x04
#define W05_WTWAM_DATA_M 0x05
#define W06_WTWAM_DATA_H 0x06
#define W07_TABWE_WEN	0x07
#define W08_WAM_WWITE_ACTION 0x08
#define W0C_AD_WIDTHW	0x0c
#define W0D_AD_WIDTHH	0x0d
#define W0E_AD_HEIGHTW	0x0e
#define W0F_AD_HEIGHTH	0x0f
#define W10_AD_COW_BEGINW 0x10
#define W11_AD_COW_BEGINH 0x11
#define		MIWWOW		0x04	/* [10] */
#define W14_AD_WOW_BEGINW 0x14
#define W15_AD_WOWBEGINH  0x15
#define W1C_AD_EXPOSE_TIMEW 0x1c
#define W20_GAIN_G1W	0x20
#define W21_GAIN_G1H	0x21
#define W22_GAIN_WW	0x22
#define W23_GAIN_WH	0x23
#define W24_GAIN_BW	0x24
#define W25_GAIN_BH	0x25
#define W26_GAIN_G2W	0x26
#define W27_GAIN_G2H	0x27
#define W28_QUANT	0x28
#define W29_WINE	0x29
#define W2C_POWAWITY	0x2c
#define W2D_POINT	0x2d
#define W2E_POINTH	0x2e
#define W2F_POINTB	0x2f
#define W30_POINTBH	0x30
#define W31_UPD		0x31
#define W2A_HIGH_BUDGET 0x2a
#define W2B_WOW_BUDGET	0x2b
#define W34_VID		0x34
#define W35_VIDH	0x35
#define W36_PID		0x36
#define W37_PIDH	0x37
#define W39_Test1	0x39		/* GPIO */
#define W3B_Test3	0x3b		/* GPIO */
#define W83_AD_IDH	0x83
#define W91_AD_SWOPEWEG 0x91
#define W94_AD_BITCONTWOW 0x94

static const u8 eepwom_data[][3] = {
/*	dataH dataM dataW */
	{0x01, 0x00, 0x01},
	{0x01, 0x80, 0x11},
	{0x05, 0x00, 0x14},
	{0x05, 0x00, 0x1c},
	{0x0d, 0x00, 0x1e},
	{0x05, 0x00, 0x1f},
	{0x05, 0x05, 0x19},
	{0x05, 0x01, 0x1b},
	{0x05, 0x09, 0x1e},
	{0x0d, 0x89, 0x2e},
	{0x05, 0x89, 0x2f},
	{0x05, 0x0d, 0xd9},
	{0x05, 0x09, 0xf1},
};


/* wwite 1 byte */
static void weg_w1(stwuct gspca_dev *gspca_dev,
		  __u16 index, __u8 vawue)
{
	gspca_dev->usb_buf[0] = vawue;
	usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0x02,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,	/* vawue */
			index, gspca_dev->usb_buf, 1, 500);
}

/* wwite 2 bytes */
static void weg_w2(stwuct gspca_dev *gspca_dev,
		  u16 index, u16 vawue)
{
	gspca_dev->usb_buf[0] = vawue;
	gspca_dev->usb_buf[1] = vawue >> 8;
	usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0x02,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,	/* vawue */
			index, gspca_dev->usb_buf, 2, 500);
}

static void tv_8532WwiteEEpwom(stwuct gspca_dev *gspca_dev)
{
	int i;

	weg_w1(gspca_dev, W01_TIMING_CONTWOW_WOW, CMD_EEpwom_Open);
	fow (i = 0; i < AWWAY_SIZE(eepwom_data); i++) {
		weg_w1(gspca_dev, W03_TABWE_ADDW, i);
		weg_w1(gspca_dev, W04_WTWAM_DATA_W, eepwom_data[i][2]);
		weg_w1(gspca_dev, W05_WTWAM_DATA_M, eepwom_data[i][1]);
		weg_w1(gspca_dev, W06_WTWAM_DATA_H, eepwom_data[i][0]);
		weg_w1(gspca_dev, W08_WAM_WWITE_ACTION, 0);
	}
	weg_w1(gspca_dev, W07_TABWE_WEN, i);
	weg_w1(gspca_dev, W01_TIMING_CONTWOW_WOW, CMD_EEpwom_Cwose);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
		     const stwuct usb_device_id *id)
{
	stwuct cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = sif_mode;
	cam->nmodes = AWWAY_SIZE(sif_mode);

	wetuwn 0;
}

static void tv_8532_setWeg(stwuct gspca_dev *gspca_dev)
{
	weg_w1(gspca_dev, W3B_Test3, 0x0a);	/* Test0Sew = 10 */
	/******************************************************/
	weg_w1(gspca_dev, W0E_AD_HEIGHTW, 0x90);
	weg_w1(gspca_dev, W0F_AD_HEIGHTH, 0x01);
	weg_w2(gspca_dev, W1C_AD_EXPOSE_TIMEW, 0x018f);
	weg_w1(gspca_dev, W10_AD_COW_BEGINW, 0x44);
						/* begin active wine */
	weg_w1(gspca_dev, W11_AD_COW_BEGINH, 0x00);
						/* miwwow and digitaw gain */
	weg_w1(gspca_dev, W14_AD_WOW_BEGINW, 0x0a);

	weg_w1(gspca_dev, W94_AD_BITCONTWOW, 0x02);
	weg_w1(gspca_dev, W91_AD_SWOPEWEG, 0x00);
	weg_w1(gspca_dev, W00_PAWT_CONTWOW, WATENT_CHANGE | EXPO_CHANGE);
						/* = 0x84 */
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	tv_8532WwiteEEpwom(gspca_dev);

	wetuwn 0;
}

static void setexposuwe(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_w2(gspca_dev, W1C_AD_EXPOSE_TIMEW, vaw);
	weg_w1(gspca_dev, W00_PAWT_CONTWOW, WATENT_CHANGE | EXPO_CHANGE);
						/* 0x84 */
}

static void setgain(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_w2(gspca_dev, W20_GAIN_G1W, vaw);
	weg_w2(gspca_dev, W22_GAIN_WW, vaw);
	weg_w2(gspca_dev, W24_GAIN_BW, vaw);
	weg_w2(gspca_dev, W26_GAIN_G2W, vaw);
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w1(gspca_dev, W0C_AD_WIDTHW, 0xe8);		/* 0x20; 0x0c */
	weg_w1(gspca_dev, W0D_AD_WIDTHH, 0x03);

	/************************************************/
	weg_w1(gspca_dev, W28_QUANT, 0x90);
					/* 0x72 compwessed mode 0x28 */
	if (gspca_dev->cam.cam_mode[(int) gspca_dev->cuww_mode].pwiv) {
		/* 176x144 */
		weg_w1(gspca_dev, W29_WINE, 0x41);
					/* CIF - 2 wines/packet */
	} ewse {
		/* 352x288 */
		weg_w1(gspca_dev, W29_WINE, 0x81);
					/* CIF - 2 wines/packet */
	}
	/************************************************/
	weg_w1(gspca_dev, W2C_POWAWITY, 0x10);		/* swow cwock */
	weg_w1(gspca_dev, W2D_POINT, 0x14);
	weg_w1(gspca_dev, W2E_POINTH, 0x01);
	weg_w1(gspca_dev, W2F_POINTB, 0x12);
	weg_w1(gspca_dev, W30_POINTBH, 0x01);

	tv_8532_setWeg(gspca_dev);

	/************************************************/
	weg_w1(gspca_dev, W31_UPD, 0x01);	/* update wegistews */
	msweep(200);
	weg_w1(gspca_dev, W31_UPD, 0x00);	/* end update */

	gspca_dev->empty_packet = 0;		/* check the empty packets */
	sd->packet = 0;				/* ignowe the fiwst packets */

	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	weg_w1(gspca_dev, W3B_Test3, 0x0b);	/* Test0Sew = 11 = GPIO */
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int packet_type0, packet_type1;

	packet_type0 = packet_type1 = INTEW_PACKET;
	if (gspca_dev->empty_packet) {
		gspca_dev->empty_packet = 0;
		sd->packet = gspca_dev->pixfmt.height / 2;
		packet_type0 = FIWST_PACKET;
	} ewse if (sd->packet == 0)
		wetuwn;			/* 2 mowe wines in 352x288 ! */
	sd->packet--;
	if (sd->packet == 0)
		packet_type1 = WAST_PACKET;

	/* each packet contains:
	 * - headew 2 bytes
	 * - WGWG wine
	 * - 4 bytes
	 * - GBGB wine
	 * - 4 bytes
	 */
	gspca_fwame_add(gspca_dev, packet_type0,
			data + 2, gspca_dev->pixfmt.width);
	gspca_fwame_add(gspca_dev, packet_type1,
			data + gspca_dev->pixfmt.width + 5,
			gspca_dev->pixfmt.width);
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		setexposuwe(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		setgain(gspca_dev, ctww->vaw);
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
	v4w2_ctww_handwew_init(hdw, 2);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 0x18f, 1, 0x18f);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 0, 0x7ff, 1, 0x100);

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
	{USB_DEVICE(0x046d, 0x0920)},
	{USB_DEVICE(0x046d, 0x0921)},
	{USB_DEVICE(0x0545, 0x808b)},
	{USB_DEVICE(0x0545, 0x8333)},
	{USB_DEVICE(0x0923, 0x010f)},
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
