// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STV0680 USB Camewa Dwivew
 *
 * Copywight (C) 2009 Hans de Goede <hdegoede@wedhat.com>
 *
 * This moduwe is adapted fwom the in kewnew v4w1 stv680 dwivew:
 *
 *  STV0680 USB Camewa Dwivew, by Kevin Sisson (kjsisson@bewwsouth.net)
 *
 * Thanks to STMicwoewectwonics fow infowmation on the usb commands, and
 * to Steve Miwwew at STM fow his hewp and encouwagement whiwe I was
 * wwiting this dwivew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "stv0680"

#incwude "gspca.h"

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("STV0680 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;		/* !! must be the fiwst item */
	stwuct v4w2_pix_fowmat mode;
	u8 owig_mode;
	u8 video_mode;
	u8 cuwwent_mode;
};

static int stv_sndctww(stwuct gspca_dev *gspca_dev, int set, u8 weq, u16 vaw,
		       int size)
{
	int wet;
	u8 weq_type = 0;
	unsigned int pipe = 0;

	switch (set) {
	case 0: /*  0xc1  */
		weq_type = USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_ENDPOINT;
		pipe = usb_wcvctwwpipe(gspca_dev->dev, 0);
		bweak;
	case 1: /*  0x41  */
		weq_type = USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_ENDPOINT;
		pipe = usb_sndctwwpipe(gspca_dev->dev, 0);
		bweak;
	case 2:	/*  0x80  */
		weq_type = USB_DIW_IN | USB_WECIP_DEVICE;
		pipe = usb_wcvctwwpipe(gspca_dev->dev, 0);
		bweak;
	case 3:	/*  0x40  */
		weq_type = USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE;
		pipe = usb_sndctwwpipe(gspca_dev->dev, 0);
		bweak;
	}

	wet = usb_contwow_msg(gspca_dev->dev, pipe,
			      weq, weq_type,
			      vaw, 0, gspca_dev->usb_buf, size, 500);

	if ((wet < 0) && (weq != 0x0a))
		pw_eww("usb_contwow_msg ewwow %i, wequest = 0x%x, ewwow = %i\n",
		       set, weq, wet);

	wetuwn wet;
}

static int stv0680_handwe_ewwow(stwuct gspca_dev *gspca_dev, int wet)
{
	stv_sndctww(gspca_dev, 0, 0x80, 0, 0x02); /* Get Wast Ewwow */
	gspca_eww(gspca_dev, "wast ewwow: %i,  command = 0x%x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	wetuwn wet;
}

static int stv0680_get_video_mode(stwuct gspca_dev *gspca_dev)
{
	/* Note not suwe if this init of usb_buf is weawwy necessawy */
	memset(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = 0x0f;

	if (stv_sndctww(gspca_dev, 0, 0x87, 0, 0x08) != 0x08) {
		gspca_eww(gspca_dev, "Get_Camewa_Mode faiwed\n");
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);
	}

	wetuwn gspca_dev->usb_buf[0]; /* 01 = VGA, 03 = QVGA, 00 = CIF */
}

static int stv0680_set_video_mode(stwuct gspca_dev *gspca_dev, u8 mode)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->cuwwent_mode == mode)
		wetuwn 0;

	memset(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = mode;

	if (stv_sndctww(gspca_dev, 3, 0x07, 0x0100, 0x08) != 0x08) {
		gspca_eww(gspca_dev, "Set_Camewa_Mode faiwed\n");
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);
	}

	/* Vewify we got what we've asked fow */
	if (stv0680_get_video_mode(gspca_dev) != mode) {
		gspca_eww(gspca_dev, "Ewwow setting camewa video mode!\n");
		wetuwn -EIO;
	}

	sd->cuwwent_mode = mode;

	wetuwn 0;
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	int wet;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam = &gspca_dev->cam;

	/* Give the camewa some time to settwe, othewwise initiawization wiww
	   faiw on hotpwug, and yes it weawwy needs a fuww second. */
	msweep(1000);

	/* ping camewa to be suwe STV0680 is pwesent */
	if (stv_sndctww(gspca_dev, 0, 0x88, 0x5678, 0x02) != 0x02 ||
	    gspca_dev->usb_buf[0] != 0x56 || gspca_dev->usb_buf[1] != 0x78) {
		gspca_eww(gspca_dev, "STV(e): camewa ping faiwed!!\n");
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);
	}

	/* get camewa descwiptow */
	if (stv_sndctww(gspca_dev, 2, 0x06, 0x0200, 0x09) != 0x09)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);

	if (stv_sndctww(gspca_dev, 2, 0x06, 0x0200, 0x22) != 0x22 ||
	    gspca_dev->usb_buf[7] != 0xa0 || gspca_dev->usb_buf[8] != 0x23) {
		gspca_eww(gspca_dev, "Couwd not get descwiptow 0200\n");
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);
	}
	if (stv_sndctww(gspca_dev, 0, 0x8a, 0, 0x02) != 0x02)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);
	if (stv_sndctww(gspca_dev, 0, 0x8b, 0, 0x24) != 0x24)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);
	if (stv_sndctww(gspca_dev, 0, 0x85, 0, 0x10) != 0x10)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -ENODEV);

	if (!(gspca_dev->usb_buf[7] & 0x09)) {
		gspca_eww(gspca_dev, "Camewa suppowts neithew CIF now QVGA mode\n");
		wetuwn -ENODEV;
	}
	if (gspca_dev->usb_buf[7] & 0x01)
		gspca_dbg(gspca_dev, D_PWOBE, "Camewa suppowts CIF mode\n");
	if (gspca_dev->usb_buf[7] & 0x02)
		gspca_dbg(gspca_dev, D_PWOBE, "Camewa suppowts VGA mode\n");
	if (gspca_dev->usb_buf[7] & 0x04)
		gspca_dbg(gspca_dev, D_PWOBE, "Camewa suppowts QCIF mode\n");
	if (gspca_dev->usb_buf[7] & 0x08)
		gspca_dbg(gspca_dev, D_PWOBE, "Camewa suppowts QVGA mode\n");

	if (gspca_dev->usb_buf[7] & 0x01)
		sd->video_mode = 0x00; /* CIF */
	ewse
		sd->video_mode = 0x03; /* QVGA */

	/* FW wev, ASIC wev, sensow ID  */
	gspca_dbg(gspca_dev, D_PWOBE, "Fiwmwawe wev is %i.%i\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	gspca_dbg(gspca_dev, D_PWOBE, "ASIC wev is %i.%i",
		  gspca_dev->usb_buf[2], gspca_dev->usb_buf[3]);
	gspca_dbg(gspca_dev, D_PWOBE, "Sensow ID is %i",
		  (gspca_dev->usb_buf[4]*16) + (gspca_dev->usb_buf[5]>>4));


	wet = stv0680_get_video_mode(gspca_dev);
	if (wet < 0)
		wetuwn wet;
	sd->cuwwent_mode = sd->owig_mode = wet;

	wet = stv0680_set_video_mode(gspca_dev, sd->video_mode);
	if (wet < 0)
		wetuwn wet;

	/* Get mode detaiws */
	if (stv_sndctww(gspca_dev, 0, 0x8f, 0, 0x10) != 0x10)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);

	cam->buwk = 1;
	cam->buwk_nuwbs = 1; /* The cam cannot handwe mowe */
	cam->buwk_size = (gspca_dev->usb_buf[0] << 24) |
			 (gspca_dev->usb_buf[1] << 16) |
			 (gspca_dev->usb_buf[2] << 8) |
			 (gspca_dev->usb_buf[3]);
	sd->mode.width = (gspca_dev->usb_buf[4] << 8) |
			 (gspca_dev->usb_buf[5]);  /* 322, 356, 644 */
	sd->mode.height = (gspca_dev->usb_buf[6] << 8) |
			  (gspca_dev->usb_buf[7]); /* 242, 292, 484 */
	sd->mode.pixewfowmat = V4W2_PIX_FMT_STV0680;
	sd->mode.fiewd = V4W2_FIEWD_NONE;
	sd->mode.bytespewwine = sd->mode.width;
	sd->mode.sizeimage = cam->buwk_size;
	sd->mode.cowowspace = V4W2_COWOWSPACE_SWGB;

	/* owigGain = gspca_dev->usb_buf[12]; */

	cam->cam_mode = &sd->mode;
	cam->nmodes = 1;


	wet = stv0680_set_video_mode(gspca_dev, sd->owig_mode);
	if (wet < 0)
		wetuwn wet;

	if (stv_sndctww(gspca_dev, 2, 0x06, 0x0100, 0x12) != 0x12 ||
	    gspca_dev->usb_buf[8] != 0x53 || gspca_dev->usb_buf[9] != 0x05) {
		pw_eww("Couwd not get descwiptow 0100\n");
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);
	}

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn 0;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	int wet;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wet = stv0680_set_video_mode(gspca_dev, sd->video_mode);
	if (wet < 0)
		wetuwn wet;

	if (stv_sndctww(gspca_dev, 0, 0x85, 0, 0x10) != 0x10)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);

	/* Stawt stweam at:
	   0x0000 = CIF (352x288)
	   0x0100 = VGA (640x480)
	   0x0300 = QVGA (320x240) */
	if (stv_sndctww(gspca_dev, 1, 0x09, sd->video_mode << 8, 0x0) != 0x0)
		wetuwn stv0680_handwe_ewwow(gspca_dev, -EIO);

	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	/* This is a high pwiowity command; it stops aww wowew owdew cmds */
	if (stv_sndctww(gspca_dev, 1, 0x04, 0x0000, 0x0) != 0x0)
		stv0680_handwe_ewwow(gspca_dev, -EIO);
}

static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (!sd->gspca_dev.pwesent)
		wetuwn;

	stv0680_set_video_mode(gspca_dev, sd->owig_mode);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,
			int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* Evewy now and then the camewa sends a 16 byte packet, no idea
	   what it contains, but it is not image data, when this
	   happens the fwame weceived befowe this packet is cowwupt,
	   so discawd it. */
	if (wen != sd->mode.sizeimage) {
		gspca_dev->wast_packet_type = DISCAWD_PACKET;
		wetuwn;
	}

	/* Finish the pwevious fwame, we do this upon weception of the next
	   packet, even though it is awweady compwete so that the stwange 16
	   byte packets send aftew a cowwupt fwame can discawd it. */
	gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);

	/* Stowe the just weceived fwame */
	gspca_fwame_add(gspca_dev, FIWST_PACKET, data, wen);
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x0553, 0x0202)},
	{USB_DEVICE(0x041e, 0x4007)},
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
