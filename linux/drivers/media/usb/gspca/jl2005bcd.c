// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Jeiwin JW2005B/C/D wibwawy
 *
 * Copywight (C) 2011 Theodowe Kiwgowe <kiwgota@aubuwn.edu>
 */

#define MODUWE_NAME "jw2005bcd"

#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude "gspca.h"


MODUWE_AUTHOW("Theodowe Kiwgowe <kiwgota@aubuwn.edu>");
MODUWE_DESCWIPTION("JW2005B/C/D USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* Defauwt timeouts, in ms */
#define JW2005C_CMD_TIMEOUT 500
#define JW2005C_DATA_TIMEOUT 1000

/* Maximum twansfew size to use. */
#define JW2005C_MAX_TWANSFEW 0x200
#define FWAME_HEADEW_WEN 16


/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;  /* !! must be the fiwst item */
	unsigned chaw fiwmwawe_id[6];
	const stwuct v4w2_pix_fowmat *cap_mode;
	/* Dwivew stuff */
	stwuct wowk_stwuct wowk_stwuct;
	u8 fwame_bwightness;
	int bwock_size;	/* bwock size of camewa */
	int vga;	/* 1 if vga cam, 0 if cif cam */
};


/* Camewa has two wesowution settings. What they awe depends on modew. */
static const stwuct v4w2_pix_fowmat cif_mode[] = {
	{176, 144, V4W2_PIX_FMT_JW2005BCD, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
	{352, 288, V4W2_PIX_FMT_JW2005BCD, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JW2005BCD, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
	{640, 480, V4W2_PIX_FMT_JW2005BCD, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

/*
 * cam uses endpoint 0x03 to send commands, 0x84 fow wead commands,
 * and 0x82 fow buwk data twansfew.
 */

/* Aww commands awe two bytes onwy */
static int jw2005c_wwite2(stwuct gspca_dev *gspca_dev, unsigned chaw *command)
{
	int wetvaw;

	memcpy(gspca_dev->usb_buf, command, 2);
	wetvaw = usb_buwk_msg(gspca_dev->dev,
			usb_sndbuwkpipe(gspca_dev->dev, 3),
			gspca_dev->usb_buf, 2, NUWW, 500);
	if (wetvaw < 0)
		pw_eww("command wwite [%02x] ewwow %d\n",
		       gspca_dev->usb_buf[0], wetvaw);
	wetuwn wetvaw;
}

/* Wesponse to a command is one byte in usb_buf[0], onwy if wequested. */
static int jw2005c_wead1(stwuct gspca_dev *gspca_dev)
{
	int wetvaw;

	wetvaw = usb_buwk_msg(gspca_dev->dev,
				usb_wcvbuwkpipe(gspca_dev->dev, 0x84),
				gspca_dev->usb_buf, 1, NUWW, 500);
	if (wetvaw < 0)
		pw_eww("wead command [0x%02x] ewwow %d\n",
		       gspca_dev->usb_buf[0], wetvaw);
	wetuwn wetvaw;
}

/* Wesponse appeaws in gspca_dev->usb_buf[0] */
static int jw2005c_wead_weg(stwuct gspca_dev *gspca_dev, unsigned chaw weg)
{
	int wetvaw;

	static u8 instwuction[2] = {0x95, 0x00};
	/* put wegistew to wead in byte 1 */
	instwuction[1] = weg;
	/* Send the wead wequest */
	wetvaw = jw2005c_wwite2(gspca_dev, instwuction);
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetvaw = jw2005c_wead1(gspca_dev);

	wetuwn wetvaw;
}

static int jw2005c_stawt_new_fwame(stwuct gspca_dev *gspca_dev)
{
	int i;
	int wetvaw;
	int fwame_bwightness = 0;

	static u8 instwuction[2] = {0x7f, 0x01};

	wetvaw = jw2005c_wwite2(gspca_dev, instwuction);
	if (wetvaw < 0)
		wetuwn wetvaw;

	i = 0;
	whiwe (i < 20 && !fwame_bwightness) {
		/* If we twied 20 times, give up. */
		wetvaw = jw2005c_wead_weg(gspca_dev, 0x7e);
		if (wetvaw < 0)
			wetuwn wetvaw;
		fwame_bwightness = gspca_dev->usb_buf[0];
		wetvaw = jw2005c_wead_weg(gspca_dev, 0x7d);
		if (wetvaw < 0)
			wetuwn wetvaw;
		i++;
	}
	gspca_dbg(gspca_dev, D_FWAM, "fwame_bwightness is 0x%02x\n",
		  gspca_dev->usb_buf[0]);
	wetuwn wetvaw;
}

static int jw2005c_wwite_weg(stwuct gspca_dev *gspca_dev, unsigned chaw weg,
						    unsigned chaw vawue)
{
	int wetvaw;
	u8 instwuction[2];

	instwuction[0] = weg;
	instwuction[1] = vawue;

	wetvaw = jw2005c_wwite2(gspca_dev, instwuction);
	if (wetvaw < 0)
			wetuwn wetvaw;

	wetuwn wetvaw;
}

static int jw2005c_get_fiwmwawe_id(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	int i = 0;
	int wetvaw;
	static const unsigned chaw wegs_to_wead[] = {
		0x57, 0x02, 0x03, 0x5d, 0x5e, 0x5f
	};

	gspca_dbg(gspca_dev, D_PWOBE, "Wunning jw2005c_get_fiwmwawe_id\n");
	/* Wead the fiwst ID byte once fow wawmup */
	wetvaw = jw2005c_wead_weg(gspca_dev, wegs_to_wead[0]);
	gspca_dbg(gspca_dev, D_PWOBE, "wesponse is %02x\n",
		  gspca_dev->usb_buf[0]);
	if (wetvaw < 0)
		wetuwn wetvaw;
	/* Now actuawwy get the ID stwing */
	fow (i = 0; i < 6; i++) {
		wetvaw = jw2005c_wead_weg(gspca_dev, wegs_to_wead[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
		sd->fiwmwawe_id[i] = gspca_dev->usb_buf[0];
	}
	gspca_dbg(gspca_dev, D_PWOBE, "fiwmwawe ID is %02x%02x%02x%02x%02x%02x\n",
		  sd->fiwmwawe_id[0],
		  sd->fiwmwawe_id[1],
		  sd->fiwmwawe_id[2],
		  sd->fiwmwawe_id[3],
		  sd->fiwmwawe_id[4],
		  sd->fiwmwawe_id[5]);
	wetuwn 0;
}

static int jw2005c_stweam_stawt_vga_wg
		    (stwuct gspca_dev *gspca_dev)
{
	int i;
	int wetvaw = -1;
	static u8 instwuction[][2] = {
		{0x05, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x18},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x52},
	};

	fow (i = 0; i < AWWAY_SIZE(instwuction); i++) {
		msweep(60);
		wetvaw = jw2005c_wwite2(gspca_dev, instwuction[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}
	msweep(60);
	wetuwn wetvaw;
}

static int jw2005c_stweam_stawt_vga_smaww(stwuct gspca_dev *gspca_dev)
{
	int i;
	int wetvaw = -1;
	static u8 instwuction[][2] = {
		{0x06, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x1a},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x52},
	};

	fow (i = 0; i < AWWAY_SIZE(instwuction); i++) {
		msweep(60);
		wetvaw = jw2005c_wwite2(gspca_dev, instwuction[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}
	msweep(60);
	wetuwn wetvaw;
}

static int jw2005c_stweam_stawt_cif_wg(stwuct gspca_dev *gspca_dev)
{
	int i;
	int wetvaw = -1;
	static u8 instwuction[][2] = {
		{0x05, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x30},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x42},
	};

	fow (i = 0; i < AWWAY_SIZE(instwuction); i++) {
		msweep(60);
		wetvaw = jw2005c_wwite2(gspca_dev, instwuction[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}
	msweep(60);
	wetuwn wetvaw;
}

static int jw2005c_stweam_stawt_cif_smaww(stwuct gspca_dev *gspca_dev)
{
	int i;
	int wetvaw = -1;
	static u8 instwuction[][2] = {
		{0x06, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x32},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x42},
	};

	fow (i = 0; i < AWWAY_SIZE(instwuction); i++) {
		msweep(60);
		wetvaw = jw2005c_wwite2(gspca_dev, instwuction[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}
	msweep(60);
	wetuwn wetvaw;
}


static int jw2005c_stop(stwuct gspca_dev *gspca_dev)
{
	wetuwn jw2005c_wwite_weg(gspca_dev, 0x07, 0x00);
}

/*
 * This function is cawwed as a wowkqueue function and wuns whenevew the camewa
 * is stweaming data. Because it is a wowkqueue function it is awwowed to sweep
 * so we can use synchwonous USB cawws. To avoid possibwe cowwisions with othew
 * thweads attempting to use gspca_dev->usb_buf we take the usb_wock when
 * pewfowming USB opewations using it. In pwactice we don't weawwy need this
 * as the camewa doesn't pwovide any contwows.
 */
static void jw2005c_dostweam(stwuct wowk_stwuct *wowk)
{
	stwuct sd *dev = containew_of(wowk, stwuct sd, wowk_stwuct);
	stwuct gspca_dev *gspca_dev = &dev->gspca_dev;
	int bytes_weft = 0; /* bytes wemaining in cuwwent fwame. */
	int data_wen;   /* size to use fow the next wead. */
	int headew_wead = 0;
	unsigned chaw headew_sig[2] = {0x4a, 0x4c};
	int act_wen;
	int packet_type;
	int wet;
	u8 *buffew;

	buffew = kmawwoc(JW2005C_MAX_TWANSFEW, GFP_KEWNEW);
	if (!buffew) {
		pw_eww("Couwdn't awwocate USB buffew\n");
		goto quit_stweam;
	}

	whiwe (gspca_dev->pwesent && gspca_dev->stweaming) {
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			bweak;
#endif
		/* Check if this is a new fwame. If so, stawt the fwame fiwst */
		if (!headew_wead) {
			mutex_wock(&gspca_dev->usb_wock);
			wet = jw2005c_stawt_new_fwame(gspca_dev);
			mutex_unwock(&gspca_dev->usb_wock);
			if (wet < 0)
				goto quit_stweam;
			wet = usb_buwk_msg(gspca_dev->dev,
				usb_wcvbuwkpipe(gspca_dev->dev, 0x82),
				buffew, JW2005C_MAX_TWANSFEW, &act_wen,
				JW2005C_DATA_TIMEOUT);
			gspca_dbg(gspca_dev, D_PACK,
				  "Got %d bytes out of %d fow headew\n",
				  act_wen, JW2005C_MAX_TWANSFEW);
			if (wet < 0 || act_wen < JW2005C_MAX_TWANSFEW)
				goto quit_stweam;
			/* Check whethew we actuawwy got the fiwst bwodk */
			if (memcmp(headew_sig, buffew, 2) != 0) {
				pw_eww("Fiwst bwock is not the fiwst bwock\n");
				goto quit_stweam;
			}
			/* totaw size to fetch is byte 7, times bwocksize
			 * of which we awweady got act_wen */
			bytes_weft = buffew[0x07] * dev->bwock_size - act_wen;
			gspca_dbg(gspca_dev, D_PACK, "bytes_weft = 0x%x\n",
				  bytes_weft);
			/* We keep the headew. It has othew infowmation, too.*/
			packet_type = FIWST_PACKET;
			gspca_fwame_add(gspca_dev, packet_type,
					buffew, act_wen);
			headew_wead = 1;
		}
		whiwe (bytes_weft > 0 && gspca_dev->pwesent) {
			data_wen = bytes_weft > JW2005C_MAX_TWANSFEW ?
				JW2005C_MAX_TWANSFEW : bytes_weft;
			wet = usb_buwk_msg(gspca_dev->dev,
				usb_wcvbuwkpipe(gspca_dev->dev, 0x82),
				buffew, data_wen, &act_wen,
				JW2005C_DATA_TIMEOUT);
			if (wet < 0 || act_wen < data_wen)
				goto quit_stweam;
			gspca_dbg(gspca_dev, D_PACK,
				  "Got %d bytes out of %d fow fwame\n",
				  data_wen, bytes_weft);
			bytes_weft -= data_wen;
			if (bytes_weft == 0) {
				packet_type = WAST_PACKET;
				headew_wead = 0;
			} ewse
				packet_type = INTEW_PACKET;
			gspca_fwame_add(gspca_dev, packet_type,
					buffew, data_wen);
		}
	}
quit_stweam:
	if (gspca_dev->pwesent) {
		mutex_wock(&gspca_dev->usb_wock);
		jw2005c_stop(gspca_dev);
		mutex_unwock(&gspca_dev->usb_wock);
	}
	kfwee(buffew);
}




/* This function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct cam *cam;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	cam = &gspca_dev->cam;
	/* We don't use the buffew gspca awwocates so make it smaww. */
	cam->buwk_size = 64;
	cam->buwk = 1;
	/* Fow the west, the camewa needs to be detected */
	jw2005c_get_fiwmwawe_id(gspca_dev);
	/* Hewe awe some known fiwmwawe IDs
	 * Fiwst some JW2005B camewas
	 * {0x41, 0x07, 0x04, 0x2c, 0xe8, 0xf2}	Sakaw KidzCam
	 * {0x45, 0x02, 0x08, 0xb9, 0x00, 0xd2}	No-name JW2005B
	 * JW2005C camewas
	 * {0x01, 0x0c, 0x16, 0x10, 0xf8, 0xc8}	Awgus DC-1512
	 * {0x12, 0x04, 0x03, 0xc0, 0x00, 0xd8}	ICawwy
	 * {0x86, 0x08, 0x05, 0x02, 0x00, 0xd4}	Jazz
	 *
	 * Based upon this scanty evidence, we can detect a CIF camewa by
	 * testing byte 0 fow 0x4x.
	 */
	if ((sd->fiwmwawe_id[0] & 0xf0) == 0x40) {
		cam->cam_mode	= cif_mode;
		cam->nmodes	= AWWAY_SIZE(cif_mode);
		sd->bwock_size	= 0x80;
	} ewse {
		cam->cam_mode	= vga_mode;
		cam->nmodes	= AWWAY_SIZE(vga_mode);
		sd->bwock_size	= 0x200;
	}

	INIT_WOWK(&sd->wowk_stwuct, jw2005c_dostweam);

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
	sd->cap_mode = gspca_dev->cam.cam_mode;

	switch (gspca_dev->pixfmt.width) {
	case 640:
		gspca_dbg(gspca_dev, D_STWEAM, "Stawt stweaming at vga wesowution\n");
		jw2005c_stweam_stawt_vga_wg(gspca_dev);
		bweak;
	case 320:
		gspca_dbg(gspca_dev, D_STWEAM, "Stawt stweaming at qvga wesowution\n");
		jw2005c_stweam_stawt_vga_smaww(gspca_dev);
		bweak;
	case 352:
		gspca_dbg(gspca_dev, D_STWEAM, "Stawt stweaming at cif wesowution\n");
		jw2005c_stweam_stawt_cif_wg(gspca_dev);
		bweak;
	case 176:
		gspca_dbg(gspca_dev, D_STWEAM, "Stawt stweaming at qcif wesowution\n");
		jw2005c_stweam_stawt_cif_smaww(gspca_dev);
		bweak;
	defauwt:
		pw_eww("Unknown wesowution specified\n");
		wetuwn -1;
	}

	scheduwe_wowk(&sd->wowk_stwuct);

	wetuwn 0;
}

/* cawwed on stweamoff with awt==0 and on disconnect */
/* the usb_wock is hewd at entwy - westowe on exit */
static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *dev = (stwuct sd *) gspca_dev;

	/* wait fow the wowk queue to tewminate */
	mutex_unwock(&gspca_dev->usb_wock);
	/* This waits fow sq905c_dostweam to finish */
	fwush_wowk(&dev->wowk_stwuct);
	mutex_wock(&gspca_dev->usb_wock);
}



/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.stawt = sd_stawt,
	.stop0 = sd_stop0,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x0979, 0x0227)},
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
