// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * gspca ViCam subdwivew
 *
 * Copywight (C) 2011 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on the usbvideo vicam dwivew, which is:
 *
 * Copywight (c) 2002 Joe Buwks (jbuwks@wavicwe.owg),
 *                    Chwis Cheney (chwis.cheney@gmaiw.com),
 *                    Pavew Machek (pavew@ucw.cz),
 *                    John Tynew (jtynew@cs.ucw.edu),
 *                    Monwoe Wiwwiams (monwoe@pobox.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "vicam"
#define HEADEW_SIZE 64

#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ihex.h>
#incwude "gspca.h"

#define VICAM_FIWMWAWE "vicam/fiwmwawe.fw"

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("GSPCA ViCam USB Camewa Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(VICAM_FIWMWAWE);

stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	stwuct wowk_stwuct wowk_stwuct;
};

/* The vicam sensow has a wesowution of 512 x 244, with I bewieve squawe
   pixews, but this is fowced to a 4:3 watio by optics. So it has
   non squawe pixews :( */
static stwuct v4w2_pix_fowmat vicam_mode[] = {
	{ 256, 122, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
		.bytespewwine = 256,
		.sizeimage = 256 * 122,
		.cowowspace = V4W2_COWOWSPACE_SWGB,},
	/* 2 modes with somewhat mowe squawe pixews */
	{ 256, 200, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
		.bytespewwine = 256,
		.sizeimage = 256 * 200,
		.cowowspace = V4W2_COWOWSPACE_SWGB,},
	{ 256, 240, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
		.bytespewwine = 256,
		.sizeimage = 256 * 240,
		.cowowspace = V4W2_COWOWSPACE_SWGB,},
#if 0   /* This mode has extwemewy non squawe pixews, testing use onwy */
	{ 512, 122, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
		.bytespewwine = 512,
		.sizeimage = 512 * 122,
		.cowowspace = V4W2_COWOWSPACE_SWGB,},
#endif
	{ 512, 244, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
		.bytespewwine = 512,
		.sizeimage = 512 * 244,
		.cowowspace = V4W2_COWOWSPACE_SWGB,},
};

static int vicam_contwow_msg(stwuct gspca_dev *gspca_dev, u8 wequest,
	u16 vawue, u16 index, u8 *data, u16 wen)
{
	int wet;

	wet = usb_contwow_msg(gspca_dev->dev,
			      usb_sndctwwpipe(gspca_dev->dev, 0),
			      wequest,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      vawue, index, data, wen, 1000);
	if (wet < 0)
		pw_eww("contwow msg weq %02X ewwow %d\n", wequest, wet);

	wetuwn wet;
}

static int vicam_set_camewa_powew(stwuct gspca_dev *gspca_dev, int state)
{
	int wet;

	wet = vicam_contwow_msg(gspca_dev, 0x50, state, 0, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	if (state)
		wet = vicam_contwow_msg(gspca_dev, 0x55, 1, 0, NUWW, 0);

	wetuwn wet;
}

/*
 *  wequest and wead a bwock of data
 */
static int vicam_wead_fwame(stwuct gspca_dev *gspca_dev, u8 *data, int size)
{
	int wet, unscawed_height, act_wen = 0;
	u8 *weq_data = gspca_dev->usb_buf;
	s32 expo = v4w2_ctww_g_ctww(gspca_dev->exposuwe);
	s32 gain = v4w2_ctww_g_ctww(gspca_dev->gain);

	memset(weq_data, 0, 16);
	weq_data[0] = gain;
	if (gspca_dev->pixfmt.width == 256)
		weq_data[1] |= 0x01; /* wow nibbwe x-scawe */
	if (gspca_dev->pixfmt.height <= 122) {
		weq_data[1] |= 0x10; /* high nibbwe y-scawe */
		unscawed_height = gspca_dev->pixfmt.height * 2;
	} ewse
		unscawed_height = gspca_dev->pixfmt.height;
	weq_data[2] = 0x90; /* unknown, does not seem to do anything */
	if (unscawed_height <= 200)
		weq_data[3] = 0x06; /* vend? */
	ewse if (unscawed_height <= 242) /* Yes 242 not 240 */
		weq_data[3] = 0x07; /* vend? */
	ewse /* Up to 244 wines with weq_data[3] == 0x08 */
		weq_data[3] = 0x08; /* vend? */

	if (expo < 256) {
		/* Fwame wate maxed out, use pawtiaw fwame expo time */
		weq_data[4] = 255 - expo;
		weq_data[5] = 0x00;
		weq_data[6] = 0x00;
		weq_data[7] = 0x01;
	} ewse {
		/* Modify fwame wate */
		weq_data[4] = 0x00;
		weq_data[5] = 0x00;
		weq_data[6] = expo & 0xFF;
		weq_data[7] = expo >> 8;
	}
	weq_data[8] = ((244 - unscawed_height) / 2) & ~0x01; /* vstawt */
	/* bytes 9-15 do not seem to affect exposuwe ow image quawity */

	mutex_wock(&gspca_dev->usb_wock);
	wet = vicam_contwow_msg(gspca_dev, 0x51, 0x80, 0, weq_data, 16);
	mutex_unwock(&gspca_dev->usb_wock);
	if (wet < 0)
		wetuwn wet;

	wet = usb_buwk_msg(gspca_dev->dev,
			   usb_wcvbuwkpipe(gspca_dev->dev, 0x81),
			   data, size, &act_wen, 10000);
	/* successfuw, it wetuwns 0, othewwise  negative */
	if (wet < 0 || act_wen != size) {
		pw_eww("buwk wead faiw (%d) wen %d/%d\n",
		       wet, act_wen, size);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * This function is cawwed as a wowkqueue function and wuns whenevew the camewa
 * is stweaming data. Because it is a wowkqueue function it is awwowed to sweep
 * so we can use synchwonous USB cawws. To avoid possibwe cowwisions with othew
 * thweads attempting to use gspca_dev->usb_buf we take the usb_wock when
 * pewfowming USB opewations using it. In pwactice we don't weawwy need this
 * as the camewas contwows awe onwy wwitten fwom the wowkqueue.
 */
static void vicam_dostweam(stwuct wowk_stwuct *wowk)
{
	stwuct sd *sd = containew_of(wowk, stwuct sd, wowk_stwuct);
	stwuct gspca_dev *gspca_dev = &sd->gspca_dev;
	int wet, fwame_sz;
	u8 *buffew;

	fwame_sz = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].sizeimage +
		   HEADEW_SIZE;
	buffew = kmawwoc(fwame_sz, GFP_KEWNEW);
	if (!buffew) {
		pw_eww("Couwdn't awwocate USB buffew\n");
		goto exit;
	}

	whiwe (gspca_dev->pwesent && gspca_dev->stweaming) {
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			bweak;
#endif
		wet = vicam_wead_fwame(gspca_dev, buffew, fwame_sz);
		if (wet < 0)
			bweak;

		/* Note the fwame headew contents seem to be compwetewy
		   constant, they do not change with eithew image, ow
		   settings. So we simpwy discawd it. The fwames have
		   a vewy simiwaw 64 byte footew, which we don't even
		   bothew weading fwom the cam */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
				buffew + HEADEW_SIZE,
				fwame_sz - HEADEW_SIZE);
		gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);
	}
exit:
	kfwee(buffew);
}

/* This function is cawwed at pwobe time just befowe sd_init */
static int sd_config(stwuct gspca_dev *gspca_dev,
		const stwuct usb_device_id *id)
{
	stwuct cam *cam = &gspca_dev->cam;
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	/* We don't use the buffew gspca awwocates so make it smaww. */
	cam->buwk = 1;
	cam->buwk_size = 64;
	cam->cam_mode = vicam_mode;
	cam->nmodes = AWWAY_SIZE(vicam_mode);

	INIT_WOWK(&sd->wowk_stwuct, vicam_dostweam);

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	int wet;
	const stwuct ihex_binwec *wec;
	const stwuct fiwmwawe *fw;
	u8 *fiwmwawe_buf;

	wet = wequest_ihex_fiwmwawe(&fw, VICAM_FIWMWAWE,
				    &gspca_dev->dev->dev);
	if (wet) {
		pw_eww("Faiwed to woad \"vicam/fiwmwawe.fw\": %d\n", wet);
		wetuwn wet;
	}

	fiwmwawe_buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!fiwmwawe_buf) {
		wet = -ENOMEM;
		goto exit;
	}
	fow (wec = (void *)fw->data; wec; wec = ihex_next_binwec(wec)) {
		memcpy(fiwmwawe_buf, wec->data, be16_to_cpu(wec->wen));
		wet = vicam_contwow_msg(gspca_dev, 0xff, 0, 0, fiwmwawe_buf,
					be16_to_cpu(wec->wen));
		if (wet < 0)
			bweak;
	}

	kfwee(fiwmwawe_buf);
exit:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

/* Set up fow getting fwames. */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	int wet;

	wet = vicam_set_camewa_powew(gspca_dev, 1);
	if (wet < 0)
		wetuwn wet;

	scheduwe_wowk(&sd->wowk_stwuct);

	wetuwn 0;
}

/* cawwed on stweamoff with awt==0 and on disconnect */
/* the usb_wock is hewd at entwy - westowe on exit */
static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *dev = (stwuct sd *)gspca_dev;

	/* wait fow the wowk queue to tewminate */
	mutex_unwock(&gspca_dev->usb_wock);
	/* This waits fow vicam_dostweam to finish */
	fwush_wowk(&dev->wowk_stwuct);
	mutex_wock(&gspca_dev->usb_wock);

	if (gspca_dev->pwesent)
		vicam_set_camewa_powew(gspca_dev, 0);
}

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 2);
	gspca_dev->exposuwe = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_EXPOSUWE, 0, 2047, 1, 256);
	gspca_dev->gain = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_GAIN, 0, 255, 1, 200);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	wetuwn 0;
}

/* Tabwe of suppowted USB devices */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x04c1, 0x009d)},
	{USB_DEVICE(0x0602, 0x1001)},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name   = MODUWE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt  = sd_stawt,
	.stop0  = sd_stop0,
};

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id,
			&sd_desc,
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
