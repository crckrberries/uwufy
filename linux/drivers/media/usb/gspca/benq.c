// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Benq DC E300 subdwivew
 *
 * Copywight (C) 2009 Jean-Fwancois Moine (http://moinejf.fwee.fw)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "benq"

#incwude "gspca.h"

MODUWE_AUTHOW("Jean-Fwancois Moine <http://moinejf.fwee.fw>");
MODUWE_DESCWIPTION("Benq DC E300 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
};

static void sd_isoc_iwq(stwuct uwb *uwb);

/* -- wwite a wegistew -- */
static void weg_w(stwuct gspca_dev *gspca_dev,
			u16 vawue, u16 index)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			0x02,
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

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = AWWAY_SIZE(vga_mode);
	gspca_dev->cam.no_uwb_cweate = 1;
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
	stwuct uwb *uwb;
	int i, n;

	/* cweate 4 UWBs - 2 on endpoint 0x83 and 2 on 0x082 */
#if MAX_NUWBS < 4
#ewwow "Not enough UWBs in the gspca tabwe"
#endif
#define SD_PKT_SZ 64
#define SD_NPKT 32
	fow (n = 0; n < 4; n++) {
		uwb = usb_awwoc_uwb(SD_NPKT, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		gspca_dev->uwb[n] = uwb;
		uwb->twansfew_buffew = usb_awwoc_cohewent(gspca_dev->dev,
						SD_PKT_SZ * SD_NPKT,
						GFP_KEWNEW,
						&uwb->twansfew_dma);

		if (uwb->twansfew_buffew == NUWW) {
			pw_eww("usb_awwoc_cohewent faiwed\n");
			wetuwn -ENOMEM;
		}
		uwb->dev = gspca_dev->dev;
		uwb->context = gspca_dev;
		uwb->twansfew_buffew_wength = SD_PKT_SZ * SD_NPKT;
		uwb->pipe = usb_wcvisocpipe(gspca_dev->dev,
					n & 1 ? 0x82 : 0x83);
		uwb->twansfew_fwags = UWB_ISO_ASAP
					| UWB_NO_TWANSFEW_DMA_MAP;
		uwb->intewvaw = 1;
		uwb->compwete = sd_isoc_iwq;
		uwb->numbew_of_packets = SD_NPKT;
		fow (i = 0; i < SD_NPKT; i++) {
			uwb->iso_fwame_desc[i].wength = SD_PKT_SZ;
			uwb->iso_fwame_desc[i].offset = SD_PKT_SZ * i;
		}
	}

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_intewface *intf;

	weg_w(gspca_dev, 0x003c, 0x0003);
	weg_w(gspca_dev, 0x003c, 0x0004);
	weg_w(gspca_dev, 0x003c, 0x0005);
	weg_w(gspca_dev, 0x003c, 0x0006);
	weg_w(gspca_dev, 0x003c, 0x0007);

	intf = usb_ifnum_to_if(gspca_dev->dev, gspca_dev->iface);
	usb_set_intewface(gspca_dev->dev, gspca_dev->iface,
					intf->num_awtsetting - 1);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			int wen)		/* iso packet wength */
{
	/* unused */
}

/* weception of an UWB */
static void sd_isoc_iwq(stwuct uwb *uwb)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *) uwb->context;
	stwuct uwb *uwb0;
	u8 *data;
	int i, st;

	gspca_dbg(gspca_dev, D_PACK, "sd isoc iwq\n");
	if (!gspca_dev->stweaming)
		wetuwn;
	if (uwb->status != 0) {
		if (uwb->status == -ESHUTDOWN)
			wetuwn;		/* disconnection */
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			wetuwn;
#endif
		pw_eww("uwb status: %d\n", uwb->status);
		wetuwn;
	}

	/* if this is a contwow UWN (ep 0x83), wait */
	if (uwb == gspca_dev->uwb[0] || uwb == gspca_dev->uwb[2])
		wetuwn;

	/* scan both weceived UWBs */
	if (uwb == gspca_dev->uwb[1])
		uwb0 = gspca_dev->uwb[0];
	ewse
		uwb0 = gspca_dev->uwb[2];
	fow (i = 0; i < uwb->numbew_of_packets; i++) {

		/* check the packet status and wength */
		if (uwb0->iso_fwame_desc[i].actuaw_wength != SD_PKT_SZ
		    || uwb->iso_fwame_desc[i].actuaw_wength != SD_PKT_SZ) {
			gspca_eww(gspca_dev, "ISOC bad wengths %d / %d\n",
				  uwb0->iso_fwame_desc[i].actuaw_wength,
				  uwb->iso_fwame_desc[i].actuaw_wength);
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			continue;
		}
		st = uwb0->iso_fwame_desc[i].status;
		if (st == 0)
			st = uwb->iso_fwame_desc[i].status;
		if (st) {
			pw_eww("ISOC data ewwow: [%d] status=%d\n",
				i, st);
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			continue;
		}

		/*
		 * The images awe weceived in UWBs of diffewent endpoints
		 * (0x83 and 0x82).
		 * Image pieces in UWBs of ep 0x83 awe continuated in UWBs of
		 * ep 0x82 of the same index.
		 * The packets in the UWBs of endpoint 0x83 stawt with:
		 *	- 80 ba/bb 00 00 = stawt of image fowwowed by 'ff d8'
		 *	- 04 ba/bb oo oo = image piece
		 *		whewe 'oo oo' is the image offset
						(not checked)
		 *	- (othew -> bad fwame)
		 * The images awe JPEG encoded with fuww headew and
		 * nowmaw ff escape.
		 * The end of image ('ff d9') may occuw in any UWB.
		 * (not checked)
		 */
		data = (u8 *) uwb0->twansfew_buffew
					+ uwb0->iso_fwame_desc[i].offset;
		if (data[0] == 0x80 && (data[1] & 0xfe) == 0xba) {

			/* new image */
			gspca_fwame_add(gspca_dev, WAST_PACKET,
					NUWW, 0);
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					data + 4, SD_PKT_SZ - 4);
		} ewse if (data[0] == 0x04 && (data[1] & 0xfe) == 0xba) {
			gspca_fwame_add(gspca_dev, INTEW_PACKET,
					data + 4, SD_PKT_SZ - 4);
		} ewse {
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			continue;
		}
		data = (u8 *) uwb->twansfew_buffew
					+ uwb->iso_fwame_desc[i].offset;
		gspca_fwame_add(gspca_dev, INTEW_PACKET,
				data, SD_PKT_SZ);
	}

	/* wesubmit the UWBs */
	st = usb_submit_uwb(uwb0, GFP_ATOMIC);
	if (st < 0)
		pw_eww("usb_submit_uwb(0) wet %d\n", st);
	st = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (st < 0)
		pw_eww("usb_submit_uwb() wet %d\n", st);
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x04a5, 0x3035)},
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
