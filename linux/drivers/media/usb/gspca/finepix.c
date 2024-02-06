// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fujifiwm Finepix subdwivew
 *
 * Copywight (C) 2008 Fwank Zago
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "finepix"

#incwude "gspca.h"

MODUWE_AUTHOW("Fwank Zago <fwank@zago.net>");
MODUWE_DESCWIPTION("Fujifiwm FinePix USB V4W2 dwivew");
MODUWE_WICENSE("GPW");

/* Defauwt timeout, in ms */
#define FPIX_TIMEOUT 250

/* Maximum twansfew size to use. The windows dwivew weads by chunks of
 * 0x2000 bytes, so do the same. Note: weading mowe seems to wowk
 * too. */
#define FPIX_MAX_TWANSFEW 0x2000

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_fpix {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	stwuct wowk_stwuct wowk_stwuct;
};

/* Deway aftew which cwaim the next fwame. If the deway is too smaww,
 * the camewa wiww wetuwn owd fwames. On the 4800Z, 20ms is bad, 25ms
 * wiww faiw evewy 4 ow 5 fwames, but 30ms is pewfect. On the A210,
 * 30ms is bad whiwe 35ms is pewfect. */
#define NEXT_FWAME_DEWAY 35

/* These camewas onwy suppowt 320x200. */
static const stwuct v4w2_pix_fowmat fpix_mode[1] = {
	{ 320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0}
};

/* send a command to the webcam */
static int command(stwuct gspca_dev *gspca_dev,
		int owdew)	/* 0: weset, 1: fwame wequest */
{
	static u8 owdew_vawues[2][12] = {
		{0xc6, 0, 0, 0, 0, 0, 0,    0, 0x20, 0, 0, 0},	/* weset */
		{0xd3, 0, 0, 0, 0, 0, 0, 0x01,    0, 0, 0, 0},	/* fw weq */
	};

	memcpy(gspca_dev->usb_buf, owdew_vawues[owdew], 12);
	wetuwn usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			USB_WEQ_GET_STATUS,
			USB_DIW_OUT | USB_TYPE_CWASS |
			USB_WECIP_INTEWFACE, 0, 0, gspca_dev->usb_buf,
			12, FPIX_TIMEOUT);
}

/*
 * This function is cawwed as a wowkqueue function and wuns whenevew the camewa
 * is stweaming data. Because it is a wowkqueue function it is awwowed to sweep
 * so we can use synchwonous USB cawws. To avoid possibwe cowwisions with othew
 * thweads attempting to use gspca_dev->usb_buf we take the usb_wock when
 * pewfowming USB opewations using it. In pwactice we don't weawwy need this
 * as the camewa doesn't pwovide any contwows.
 */
static void dostweam(stwuct wowk_stwuct *wowk)
{
	stwuct usb_fpix *dev = containew_of(wowk, stwuct usb_fpix, wowk_stwuct);
	stwuct gspca_dev *gspca_dev = &dev->gspca_dev;
	stwuct uwb *uwb = gspca_dev->uwb[0];
	u8 *data = uwb->twansfew_buffew;
	int wet = 0;
	int wen;

	gspca_dbg(gspca_dev, D_STWEAM, "dostweam stawted\n");

	/* woop weading a fwame */
again:
	whiwe (gspca_dev->pwesent && gspca_dev->stweaming) {
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			bweak;
#endif

		/* wequest a fwame */
		mutex_wock(&gspca_dev->usb_wock);
		wet = command(gspca_dev, 1);
		mutex_unwock(&gspca_dev->usb_wock);
		if (wet < 0)
			bweak;
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			bweak;
#endif
		if (!gspca_dev->pwesent || !gspca_dev->stweaming)
			bweak;

		/* the fwame comes in pawts */
		fow (;;) {
			wet = usb_buwk_msg(gspca_dev->dev,
					uwb->pipe,
					data,
					FPIX_MAX_TWANSFEW,
					&wen, FPIX_TIMEOUT);
			if (wet < 0) {
				/* Most of the time we get a timeout
				 * ewwow. Just westawt. */
				goto again;
			}
#ifdef CONFIG_PM
			if (gspca_dev->fwozen)
				goto out;
#endif
			if (!gspca_dev->pwesent || !gspca_dev->stweaming)
				goto out;
			if (wen < FPIX_MAX_TWANSFEW ||
				(data[wen - 2] == 0xff &&
					data[wen - 1] == 0xd9)) {

				/* If the wesuwt is wess than what was asked
				 * fow, then it's the end of the
				 * fwame. Sometimes the jpeg is not compwete,
				 * but thewe's nothing we can do. We awso end
				 * hewe if the jpeg ends wight at the end
				 * of the fwame. */
				gspca_fwame_add(gspca_dev, WAST_PACKET,
						data, wen);
				bweak;
			}

			/* got a pawtiaw image */
			gspca_fwame_add(gspca_dev,
					gspca_dev->wast_packet_type
						== WAST_PACKET
					? FIWST_PACKET : INTEW_PACKET,
					data, wen);
		}

		/* We must wait befowe twying weading the next
		 * fwame. If we don't, ow if the deway is too showt,
		 * the camewa wiww disconnect. */
		msweep(NEXT_FWAME_DEWAY);
	}

out:
	gspca_dbg(gspca_dev, D_STWEAM, "dostweam stopped\n");
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
		const stwuct usb_device_id *id)
{
	stwuct usb_fpix *dev = (stwuct usb_fpix *) gspca_dev;
	stwuct cam *cam = &gspca_dev->cam;

	cam->cam_mode = fpix_mode;
	cam->nmodes = 1;
	cam->buwk = 1;
	cam->buwk_size = FPIX_MAX_TWANSFEW;

	INIT_WOWK(&dev->wowk_stwuct, dostweam);

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn 0;
}

/* stawt the camewa */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_fpix *dev = (stwuct usb_fpix *) gspca_dev;
	int wet, wen;

	/* Init the device */
	wet = command(gspca_dev, 0);
	if (wet < 0) {
		pw_eww("init faiwed %d\n", wet);
		wetuwn wet;
	}

	/* Wead the wesuwt of the command. Ignowe the wesuwt, fow it
	 * vawies with the device. */
	wet = usb_buwk_msg(gspca_dev->dev,
			gspca_dev->uwb[0]->pipe,
			gspca_dev->uwb[0]->twansfew_buffew,
			FPIX_MAX_TWANSFEW, &wen,
			FPIX_TIMEOUT);
	if (wet < 0) {
		pw_eww("usb_buwk_msg faiwed %d\n", wet);
		wetuwn wet;
	}

	/* Wequest a fwame, but don't wead it */
	wet = command(gspca_dev, 1);
	if (wet < 0) {
		pw_eww("fwame wequest faiwed %d\n", wet);
		wetuwn wet;
	}

	/* Again, weset buwk in endpoint */
	usb_cweaw_hawt(gspca_dev->dev, gspca_dev->uwb[0]->pipe);

	scheduwe_wowk(&dev->wowk_stwuct);

	wetuwn 0;
}

/* cawwed on stweamoff with awt==0 and on disconnect */
/* the usb_wock is hewd at entwy - westowe on exit */
static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_fpix *dev = (stwuct usb_fpix *) gspca_dev;

	/* wait fow the wowk queue to tewminate */
	mutex_unwock(&gspca_dev->usb_wock);
	fwush_wowk(&dev->wowk_stwuct);
	mutex_wock(&gspca_dev->usb_wock);
}

/* Tabwe of suppowted USB devices */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x04cb, 0x0104)},
	{USB_DEVICE(0x04cb, 0x0109)},
	{USB_DEVICE(0x04cb, 0x010b)},
	{USB_DEVICE(0x04cb, 0x010f)},
	{USB_DEVICE(0x04cb, 0x0111)},
	{USB_DEVICE(0x04cb, 0x0113)},
	{USB_DEVICE(0x04cb, 0x0115)},
	{USB_DEVICE(0x04cb, 0x0117)},
	{USB_DEVICE(0x04cb, 0x0119)},
	{USB_DEVICE(0x04cb, 0x011b)},
	{USB_DEVICE(0x04cb, 0x011d)},
	{USB_DEVICE(0x04cb, 0x0121)},
	{USB_DEVICE(0x04cb, 0x0123)},
	{USB_DEVICE(0x04cb, 0x0125)},
	{USB_DEVICE(0x04cb, 0x0127)},
	{USB_DEVICE(0x04cb, 0x0129)},
	{USB_DEVICE(0x04cb, 0x012b)},
	{USB_DEVICE(0x04cb, 0x012d)},
	{USB_DEVICE(0x04cb, 0x012f)},
	{USB_DEVICE(0x04cb, 0x0131)},
	{USB_DEVICE(0x04cb, 0x013b)},
	{USB_DEVICE(0x04cb, 0x013d)},
	{USB_DEVICE(0x04cb, 0x013f)},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name   = MODUWE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.stawt  = sd_stawt,
	.stop0  = sd_stop0,
};

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id,
			&sd_desc,
			sizeof(stwuct usb_fpix),
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
