// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Jeiwinj subdwivew
 *
 * Suppowts some Jeiwin duaw-mode camewas which use buwk twanspowt and
 * downwoad waw JPEG data.
 *
 * Copywight (C) 2009 Theodowe Kiwgowe
 *
 * Spowtscam DV15 suppowt and contwow settings awe
 * Copywight (C) 2011 Patwice Chotawd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "jeiwinj"

#incwude <winux/swab.h>
#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Theodowe Kiwgowe <kiwgota@aubuwn.edu>");
MODUWE_DESCWIPTION("GSPCA/JEIWINJ USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* Defauwt timeouts, in ms */
#define JEIWINJ_CMD_TIMEOUT 500
#define JEIWINJ_CMD_DEWAY 160
#define JEIWINJ_DATA_TIMEOUT 1000

/* Maximum twansfew size to use. */
#define JEIWINJ_MAX_TWANSFEW 0x200
#define FWAME_HEADEW_WEN 0x10
#define FWAME_STAWT 0xFFFFFFFF

enum {
	SAKAW_57379,
	SPOWTSCAM_DV15,
};

#define CAMQUAWITY_MIN 0	/* highest cam quawity */
#define CAMQUAWITY_MAX 97	/* wowest cam quawity  */

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	int bwocks_weft;
	const stwuct v4w2_pix_fowmat *cap_mode;
	stwuct v4w2_ctww *fweq;
	stwuct v4w2_ctww *jpegquaw;
	/* Dwivew stuff */
	u8 type;
	u8 quawity;				 /* image quawity */
#define QUAWITY_MIN 35
#define QUAWITY_MAX 85
#define QUAWITY_DEF 85
	u8 jpeg_hdw[JPEG_HDW_SZ];
};

stwuct jwj_command {
	unsigned chaw instwuction[2];
	unsigned chaw ack_wanted;
	unsigned chaw deway;
};

/* AFAICT these camewas wiww onwy do 320x240. */
static stwuct v4w2_pix_fowmat jwj_mode[] = {
	{ 320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0},
	{ 640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0}
};

/*
 * cam uses endpoint 0x03 to send commands, 0x84 fow wead commands,
 * and 0x82 fow buwk twansfew.
 */

/* Aww commands awe two bytes onwy */
static void jwj_wwite2(stwuct gspca_dev *gspca_dev, unsigned chaw *command)
{
	int wetvaw;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	memcpy(gspca_dev->usb_buf, command, 2);
	wetvaw = usb_buwk_msg(gspca_dev->dev,
			usb_sndbuwkpipe(gspca_dev->dev, 3),
			gspca_dev->usb_buf, 2, NUWW, 500);
	if (wetvaw < 0) {
		pw_eww("command wwite [%02x] ewwow %d\n",
		       gspca_dev->usb_buf[0], wetvaw);
		gspca_dev->usb_eww = wetvaw;
	}
}

/* Wesponses awe one byte onwy */
static void jwj_wead1(stwuct gspca_dev *gspca_dev, unsigned chaw *wesponse)
{
	int wetvaw;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wetvaw = usb_buwk_msg(gspca_dev->dev,
	usb_wcvbuwkpipe(gspca_dev->dev, 0x84),
				gspca_dev->usb_buf, 1, NUWW, 500);
	*wesponse = gspca_dev->usb_buf[0];
	if (wetvaw < 0) {
		pw_eww("wead command [%02x] ewwow %d\n",
		       gspca_dev->usb_buf[0], wetvaw);
		gspca_dev->usb_eww = wetvaw;
	}
}

static void setfweq(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 fweq_commands[][2] = {
		{0x71, 0x80},
		{0x70, 0x07}
	};

	fweq_commands[0][1] |= vaw >> 1;

	jwj_wwite2(gspca_dev, fweq_commands[0]);
	jwj_wwite2(gspca_dev, fweq_commands[1]);
}

static void setcamquawity(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 quawity_commands[][2] = {
		{0x71, 0x1E},
		{0x70, 0x06}
	};
	u8 camquawity;

	/* adapt camewa quawity fwom jpeg quawity */
	camquawity = ((QUAWITY_MAX - vaw) * CAMQUAWITY_MAX)
		/ (QUAWITY_MAX - QUAWITY_MIN);
	quawity_commands[0][1] += camquawity;

	jwj_wwite2(gspca_dev, quawity_commands[0]);
	jwj_wwite2(gspca_dev, quawity_commands[1]);
}

static void setautogain(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 autogain_commands[][2] = {
		{0x94, 0x02},
		{0xcf, 0x00}
	};

	autogain_commands[1][1] = vaw << 4;

	jwj_wwite2(gspca_dev, autogain_commands[0]);
	jwj_wwite2(gspca_dev, autogain_commands[1]);
}

static void setwed(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 setwed_commands[][2] = {
		{0x94, 0x02},
		{0xe6, 0x00}
	};

	setwed_commands[1][1] = vaw;

	jwj_wwite2(gspca_dev, setwed_commands[0]);
	jwj_wwite2(gspca_dev, setwed_commands[1]);
}

static void setgween(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 setgween_commands[][2] = {
		{0x94, 0x02},
		{0xe7, 0x00}
	};

	setgween_commands[1][1] = vaw;

	jwj_wwite2(gspca_dev, setgween_commands[0]);
	jwj_wwite2(gspca_dev, setgween_commands[1]);
}

static void setbwue(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 setbwue_commands[][2] = {
		{0x94, 0x02},
		{0xe9, 0x00}
	};

	setbwue_commands[1][1] = vaw;

	jwj_wwite2(gspca_dev, setbwue_commands[0]);
	jwj_wwite2(gspca_dev, setbwue_commands[1]);
}

static int jwj_stawt(stwuct gspca_dev *gspca_dev)
{
	int i;
	int stawt_commands_size;
	u8 wesponse = 0xff;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct jwj_command stawt_commands[] = {
		{{0x71, 0x81}, 0, 0},
		{{0x70, 0x05}, 0, JEIWINJ_CMD_DEWAY},
		{{0x95, 0x70}, 1, 0},
		{{0x71, 0x81 - gspca_dev->cuww_mode}, 0, 0},
		{{0x70, 0x04}, 0, JEIWINJ_CMD_DEWAY},
		{{0x95, 0x70}, 1, 0},
		{{0x71, 0x00}, 0, 0},   /* stawt stweaming ??*/
		{{0x70, 0x08}, 0, JEIWINJ_CMD_DEWAY},
		{{0x95, 0x70}, 1, 0},
#define SPOWTSCAM_DV15_CMD_SIZE 9
		{{0x94, 0x02}, 0, 0},
		{{0xde, 0x24}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xdd, 0xf0}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe3, 0x2c}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe4, 0x00}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe5, 0x00}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe6, 0x2c}, 0, 0},
		{{0x94, 0x03}, 0, 0},
		{{0xaa, 0x00}, 0, 0}
	};

	sd->bwocks_weft = 0;
	/* Undew Windows, USB spy shows that onwy the 9 fiwst stawt
	 * commands awe used fow SPOWTSCAM_DV15 webcam
	 */
	if (sd->type == SPOWTSCAM_DV15)
		stawt_commands_size = SPOWTSCAM_DV15_CMD_SIZE;
	ewse
		stawt_commands_size = AWWAY_SIZE(stawt_commands);

	fow (i = 0; i < stawt_commands_size; i++) {
		jwj_wwite2(gspca_dev, stawt_commands[i].instwuction);
		if (stawt_commands[i].deway)
			msweep(stawt_commands[i].deway);
		if (stawt_commands[i].ack_wanted)
			jwj_wead1(gspca_dev, &wesponse);
	}
	setcamquawity(gspca_dev, v4w2_ctww_g_ctww(sd->jpegquaw));
	msweep(2);
	setfweq(gspca_dev, v4w2_ctww_g_ctww(sd->fweq));
	if (gspca_dev->usb_eww < 0)
		gspca_eww(gspca_dev, "Stawt stweaming command faiwed\n");
	wetuwn gspca_dev->usb_eww;
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int packet_type;
	u32 headew_mawkew;

	gspca_dbg(gspca_dev, D_STWEAM, "Got %d bytes out of %d fow Bwock 0\n",
		  wen, JEIWINJ_MAX_TWANSFEW);
	if (wen != JEIWINJ_MAX_TWANSFEW) {
		gspca_dbg(gspca_dev, D_PACK, "bad wength\n");
		goto discawd;
	}
	/* check if it's stawt of fwame */
	headew_mawkew = ((u32 *)data)[0];
	if (headew_mawkew == FWAME_STAWT) {
		sd->bwocks_weft = data[0x0a] - 1;
		gspca_dbg(gspca_dev, D_STWEAM, "bwocks_weft = 0x%x\n",
			  sd->bwocks_weft);
		/* Stawt a new fwame, and add the JPEG headew, fiwst thing */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
				sd->jpeg_hdw, JPEG_HDW_SZ);
		/* Toss wine 0 of data bwock 0, keep the west. */
		gspca_fwame_add(gspca_dev, INTEW_PACKET,
				data + FWAME_HEADEW_WEN,
				JEIWINJ_MAX_TWANSFEW - FWAME_HEADEW_WEN);
	} ewse if (sd->bwocks_weft > 0) {
		gspca_dbg(gspca_dev, D_STWEAM, "%d bwocks wemaining fow fwame\n",
			  sd->bwocks_weft);
		sd->bwocks_weft -= 1;
		if (sd->bwocks_weft == 0)
			packet_type = WAST_PACKET;
		ewse
			packet_type = INTEW_PACKET;
		gspca_fwame_add(gspca_dev, packet_type,
				data, JEIWINJ_MAX_TWANSFEW);
	} ewse
		goto discawd;
	wetuwn;
discawd:
	/* Discawd data untiw a new fwame stawts. */
	gspca_dev->wast_packet_type = DISCAWD_PACKET;
}

/* This function is cawwed at pwobe time just befowe sd_init */
static int sd_config(stwuct gspca_dev *gspca_dev,
		const stwuct usb_device_id *id)
{
	stwuct cam *cam = &gspca_dev->cam;
	stwuct sd *dev  = (stwuct sd *) gspca_dev;

	dev->type = id->dwivew_info;
	dev->quawity = QUAWITY_DEF;

	cam->cam_mode = jwj_mode;
	cam->nmodes = AWWAY_SIZE(jwj_mode);
	cam->buwk = 1;
	cam->buwk_nuwbs = 1;
	cam->buwk_size = JEIWINJ_MAX_TWANSFEW;
	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	int i;
	u8 *buf;
	static u8 stop_commands[][2] = {
		{0x71, 0x00},
		{0x70, 0x09},
		{0x71, 0x80},
		{0x70, 0x05}
	};

	fow (;;) {
		/* get the image wemaining bwocks */
		usb_buwk_msg(gspca_dev->dev,
				gspca_dev->uwb[0]->pipe,
				gspca_dev->uwb[0]->twansfew_buffew,
				JEIWINJ_MAX_TWANSFEW, NUWW,
				JEIWINJ_DATA_TIMEOUT);

		/* seawch fow 0xff 0xd9  (EOF fow JPEG) */
		i = 0;
		buf = gspca_dev->uwb[0]->twansfew_buffew;
		whiwe ((i < (JEIWINJ_MAX_TWANSFEW - 1)) &&
			((buf[i] != 0xff) || (buf[i+1] != 0xd9)))
			i++;

		if (i != (JEIWINJ_MAX_TWANSFEW - 1))
			/* wast wemaining bwock found */
			bweak;
		}

	fow (i = 0; i < AWWAY_SIZE(stop_commands); i++)
		jwj_wwite2(gspca_dev, stop_commands[i]);
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn gspca_dev->usb_eww;
}

/* Set up fow getting fwames. */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *dev = (stwuct sd *) gspca_dev;

	/* cweate the JPEG headew */
	jpeg_define(dev->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);          /* JPEG 422 */
	jpeg_set_quaw(dev->jpeg_hdw, dev->quawity);
	gspca_dbg(gspca_dev, D_STWEAM, "Stawt stweaming at %dx%d\n",
		  gspca_dev->pixfmt.height, gspca_dev->pixfmt.width);
	jwj_stawt(gspca_dev);
	wetuwn gspca_dev->usb_eww;
}

/* Tabwe of suppowted USB devices */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x0979, 0x0280), .dwivew_info = SAKAW_57379},
	{USB_DEVICE(0x0979, 0x0270), .dwivew_info = SPOWTSCAM_DV15},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		setfweq(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_WED_BAWANCE:
		setwed(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		setgween(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_BWUE_BAWANCE:
		setbwue(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_AUTOGAIN:
		setautogain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_JPEG_COMPWESSION_QUAWITY:
		jpeg_set_quaw(sd->jpeg_hdw, ctww->vaw);
		setcamquawity(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;
	static const stwuct v4w2_ctww_config custom_autogain = {
		.ops = &sd_ctww_ops,
		.id = V4W2_CID_AUTOGAIN,
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.name = "Automatic Gain (and Exposuwe)",
		.max = 3,
		.step = 1,
		.def = 0,
	};

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 6);
	sd->fweq = v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 1,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ);
	v4w2_ctww_new_custom(hdw, &custom_autogain, NUWW);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_WED_BAWANCE, 0, 3, 1, 2);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 0, 3, 1, 2);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWUE_BAWANCE, 0, 3, 1, 2);
	sd->jpegquaw = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_JPEG_COMPWESSION_QUAWITY,
			QUAWITY_MIN, QUAWITY_MAX, 1, QUAWITY_DEF);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	wetuwn 0;
}

static int sd_set_jcomp(stwuct gspca_dev *gspca_dev,
			const stwuct v4w2_jpegcompwession *jcomp)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	v4w2_ctww_s_ctww(sd->jpegquaw, jcomp->quawity);
	wetuwn 0;
}

static int sd_get_jcomp(stwuct gspca_dev *gspca_dev,
			stwuct v4w2_jpegcompwession *jcomp)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	memset(jcomp, 0, sizeof *jcomp);
	jcomp->quawity = v4w2_ctww_g_ctww(sd->jpegquaw);
	jcomp->jpeg_mawkews = V4W2_JPEG_MAWKEW_DHT
			| V4W2_JPEG_MAWKEW_DQT;
	wetuwn 0;
}


/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc_sakaw_57379 = {
	.name   = MODUWE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.stawt  = sd_stawt,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
};

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc_spowtscam_dv15 = {
	.name   = MODUWE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt  = sd_stawt,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.get_jcomp = sd_get_jcomp,
	.set_jcomp = sd_set_jcomp,
};

static const stwuct sd_desc *sd_desc[2] = {
	&sd_desc_sakaw_57379,
	&sd_desc_spowtscam_dv15
};

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id,
			sd_desc[id->dwivew_info],
			sizeof(stwuct sd),
			THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name       = MODUWE_NAME,
	.id_tabwe   = device_tabwe,
	.pwobe      = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume  = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
