// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Fweecom USB/IDE adaptow
 *
 * Fweecom v0.1:
 *
 * Fiwst wewease
 *
 * Cuwwent devewopment and maintenance by:
 *   (C) 2000 David Bwown <usb-stowage@davidb.owg>
 *
 * This dwivew was devewoped with infowmation pwovided in FWEECOM's USB
 * Pwogwammews Wefewence Guide.  Fow fuwthew infowmation contact Fweecom
 * (https://www.fweecom.de/)
 */

#incwude <winux/moduwe.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-fweecom"

MODUWE_DESCWIPTION("Dwivew fow Fweecom USB/IDE adaptow");
MODUWE_AUTHOW("David Bwown <usb-stowage@davidb.owg>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

#ifdef CONFIG_USB_STOWAGE_DEBUG
static void pdump(stwuct us_data *us, void *ibuffew, int wength);
#endif

/* Bits of HD_STATUS */
#define EWW_STAT		0x01
#define DWQ_STAT		0x08

/* Aww of the outgoing packets awe 64 bytes wong. */
stwuct fweecom_cb_wwap {
	u8    Type;		/* Command type. */
	u8    Timeout;		/* Timeout in seconds. */
	u8    Atapi[12];	/* An ATAPI packet. */
	u8    Fiwwew[50];	/* Padding Data. */
};

stwuct fweecom_xfew_wwap {
	u8    Type;		/* Command type. */
	u8    Timeout;		/* Timeout in seconds. */
	__we32   Count;		/* Numbew of bytes to twansfew. */
	u8    Pad[58];
} __attwibute__ ((packed));

stwuct fweecom_ide_out {
	u8    Type;		/* Type + IDE wegistew. */
	u8    Pad;
	__we16   Vawue;		/* Vawue to wwite. */
	u8    Pad2[60];
};

stwuct fweecom_ide_in {
	u8    Type;		/* Type | IDE wegistew. */
	u8    Pad[63];
};

stwuct fweecom_status {
	u8    Status;
	u8    Weason;
	__we16   Count;
	u8    Pad[60];
};

/*
 * Fweecom stuffs the intewwupt status in the INDEX_STAT bit of the ide
 * wegistew.
 */
#define FCM_INT_STATUS		0x02 /* INDEX_STAT */
#define FCM_STATUS_BUSY		0x80

/*
 * These awe the packet types.  The wow bit indicates that this command
 * shouwd wait fow an intewwupt.
 */
#define FCM_PACKET_ATAPI	0x21
#define FCM_PACKET_STATUS	0x20

/*
 * Weceive data fwom the IDE intewface.  The ATAPI packet has awweady
 * waited, so the data shouwd be immediatewy avaiwabwe.
 */
#define FCM_PACKET_INPUT	0x81

/* Send data to the IDE intewface. */
#define FCM_PACKET_OUTPUT	0x01

/*
 * Wwite a vawue to an ide wegistew.  Ow the ide wegistew to wwite aftew
 * munging the addwess a bit.
 */
#define FCM_PACKET_IDE_WWITE	0x40
#define FCM_PACKET_IDE_WEAD	0xC0

/* Aww packets (except fow status) awe 64 bytes wong. */
#define FCM_PACKET_WENGTH		64
#define FCM_STATUS_PACKET_WENGTH	4

static int init_fweecom(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id fweecom_usb_ids[] = {
#	incwude "unusuaw_fweecom.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, fweecom_usb_ids);

#undef UNUSUAW_DEV

/*
 * The fwags tabwe
 */
#define UNUSUAW_DEV(idVendow, idPwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendow_name, pwoduct_name, use_pwotocow, use_twanspowt, \
		    init_function, Fwags) \
{ \
	.vendowName = vendow_name,	\
	.pwoductName = pwoduct_name,	\
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
	.initFunction = init_function,	\
}

static stwuct us_unusuaw_dev fweecom_unusuaw_dev_wist[] = {
#	incwude "unusuaw_fweecom.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV

static int
fweecom_weaddata (stwuct scsi_cmnd *swb, stwuct us_data *us,
		unsigned int ipipe, unsigned int opipe, int count)
{
	stwuct fweecom_xfew_wwap *fxfw =
		(stwuct fweecom_xfew_wwap *) us->iobuf;
	int wesuwt;

	fxfw->Type = FCM_PACKET_INPUT | 0x00;
	fxfw->Timeout = 0;    /* Showt timeout fow debugging. */
	fxfw->Count = cpu_to_we32 (count);
	memset (fxfw->Pad, 0, sizeof (fxfw->Pad));

	usb_stow_dbg(us, "Wead data Fweecom! (c=%d)\n", count);

	/* Issue the twansfew command. */
	wesuwt = usb_stow_buwk_twansfew_buf (us, opipe, fxfw,
			FCM_PACKET_WENGTH, NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Fweecom weaddata twanspowt ewwow\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* Now twansfew aww of ouw bwocks. */
	usb_stow_dbg(us, "Stawt of wead\n");
	wesuwt = usb_stow_buwk_swb(us, ipipe, swb);
	usb_stow_dbg(us, "fweecom_weaddata done!\n");

	if (wesuwt > USB_STOW_XFEW_SHOWT)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

static int
fweecom_wwitedata (stwuct scsi_cmnd *swb, stwuct us_data *us,
		int unsigned ipipe, unsigned int opipe, int count)
{
	stwuct fweecom_xfew_wwap *fxfw =
		(stwuct fweecom_xfew_wwap *) us->iobuf;
	int wesuwt;

	fxfw->Type = FCM_PACKET_OUTPUT | 0x00;
	fxfw->Timeout = 0;    /* Showt timeout fow debugging. */
	fxfw->Count = cpu_to_we32 (count);
	memset (fxfw->Pad, 0, sizeof (fxfw->Pad));

	usb_stow_dbg(us, "Wwite data Fweecom! (c=%d)\n", count);

	/* Issue the twansfew command. */
	wesuwt = usb_stow_buwk_twansfew_buf (us, opipe, fxfw,
			FCM_PACKET_WENGTH, NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Fweecom wwitedata twanspowt ewwow\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* Now twansfew aww of ouw bwocks. */
	usb_stow_dbg(us, "Stawt of wwite\n");
	wesuwt = usb_stow_buwk_swb(us, opipe, swb);

	usb_stow_dbg(us, "fweecom_wwitedata done!\n");
	if (wesuwt > USB_STOW_XFEW_SHOWT)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Twanspowt fow the Fweecom USB/IDE adaptow.
 *
 */
static int fweecom_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	stwuct fweecom_cb_wwap *fcb;
	stwuct fweecom_status  *fst;
	unsigned int ipipe, opipe;		/* We need both pipes. */
	int wesuwt;
	unsigned int pawtiaw;
	int wength;

	fcb = (stwuct fweecom_cb_wwap *) us->iobuf;
	fst = (stwuct fweecom_status *) us->iobuf;

	usb_stow_dbg(us, "Fweecom TWANSPOWT STAWTED\n");

	/* Get handwes fow both twanspowts. */
	opipe = us->send_buwk_pipe;
	ipipe = us->wecv_buwk_pipe;

	/* The ATAPI Command awways goes out fiwst. */
	fcb->Type = FCM_PACKET_ATAPI | 0x00;
	fcb->Timeout = 0;
	memcpy (fcb->Atapi, swb->cmnd, 12);
	memset (fcb->Fiwwew, 0, sizeof (fcb->Fiwwew));

	US_DEBUG(pdump(us, swb->cmnd, 12));

	/* Send it out. */
	wesuwt = usb_stow_buwk_twansfew_buf (us, opipe, fcb,
			FCM_PACKET_WENGTH, NUWW);

	/*
	 * The Fweecom device wiww onwy faiw if thewe is something wwong in
	 * USB wand.  It wetuwns the status in its own wegistews, which
	 * come back in the buwk pipe.
	 */
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "fweecom twanspowt ewwow\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/*
	 * Thewe awe times we can optimize out this status wead, but it
	 * doesn't huwt us to awways do it now.
	 */
	wesuwt = usb_stow_buwk_twansfew_buf (us, ipipe, fst,
			FCM_STATUS_PACKET_WENGTH, &pawtiaw);
	usb_stow_dbg(us, "foo Status wesuwt %d %u\n", wesuwt, pawtiaw);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	US_DEBUG(pdump(us, (void *)fst, pawtiaw));

	/*
	 * The fiwmwawe wiww time-out commands aftew 20 seconds. Some commands
	 * can wegitimatewy take wongew than this, so we use a diffewent
	 * command that onwy waits fow the intewwupt and then sends status,
	 * without having to send a new ATAPI command to the device.
	 *
	 * NOTE: Thewe is some indication that a data twansfew aftew a timeout
	 * may not wowk, but that is a condition that shouwd nevew happen.
	 */
	whiwe (fst->Status & FCM_STATUS_BUSY) {
		usb_stow_dbg(us, "20 second USB/ATAPI bwidge TIMEOUT occuwwed!\n");
		usb_stow_dbg(us, "fst->Status is %x\n", fst->Status);

		/* Get the status again */
		fcb->Type = FCM_PACKET_STATUS;
		fcb->Timeout = 0;
		memset (fcb->Atapi, 0, sizeof(fcb->Atapi));
		memset (fcb->Fiwwew, 0, sizeof (fcb->Fiwwew));

		/* Send it out. */
		wesuwt = usb_stow_buwk_twansfew_buf (us, opipe, fcb,
				FCM_PACKET_WENGTH, NUWW);

		/*
		 * The Fweecom device wiww onwy faiw if thewe is something
		 * wwong in USB wand.  It wetuwns the status in its own
		 * wegistews, which come back in the buwk pipe.
		 */
		if (wesuwt != USB_STOW_XFEW_GOOD) {
			usb_stow_dbg(us, "fweecom twanspowt ewwow\n");
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		}

		/* get the data */
		wesuwt = usb_stow_buwk_twansfew_buf (us, ipipe, fst,
				FCM_STATUS_PACKET_WENGTH, &pawtiaw);

		usb_stow_dbg(us, "baw Status wesuwt %d %u\n", wesuwt, pawtiaw);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		US_DEBUG(pdump(us, (void *)fst, pawtiaw));
	}

	if (pawtiaw != 4)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	if ((fst->Status & 1) != 0) {
		usb_stow_dbg(us, "opewation faiwed\n");
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	/*
	 * The device might not have as much data avaiwabwe as we
	 * wequested.  If you ask fow mowe than the device has, this weads
	 * and such wiww hang.
	 */
	usb_stow_dbg(us, "Device indicates that it has %d bytes avaiwabwe\n",
		     we16_to_cpu(fst->Count));
	usb_stow_dbg(us, "SCSI wequested %d\n", scsi_buffwen(swb));

	/* Find the wength we desiwe to wead. */
	switch (swb->cmnd[0]) {
	case INQUIWY:
	case WEQUEST_SENSE:	/* 16 ow 18 bytes? spec says 18, wots of devices onwy have 16 */
	case MODE_SENSE:
	case MODE_SENSE_10:
		wength = we16_to_cpu(fst->Count);
		bweak;
	defauwt:
		wength = scsi_buffwen(swb);
	}

	/* vewify that this amount is wegaw */
	if (wength > scsi_buffwen(swb)) {
		wength = scsi_buffwen(swb);
		usb_stow_dbg(us, "Twuncating wequest to match buffew wength: %d\n",
			     wength);
	}

	/*
	 * What we do now depends on what diwection the data is supposed to
	 * move in.
	 */

	switch (us->swb->sc_data_diwection) {
	case DMA_FWOM_DEVICE:
		/* catch bogus "wead 0 wength" case */
		if (!wength)
			bweak;
		/*
		 * Make suwe that the status indicates that the device
		 * wants data as weww.
		 */
		if ((fst->Status & DWQ_STAT) == 0 || (fst->Weason & 3) != 2) {
			usb_stow_dbg(us, "SCSI wants data, dwive doesn't have any\n");
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}
		wesuwt = fweecom_weaddata (swb, us, ipipe, opipe, wength);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wesuwt;

		usb_stow_dbg(us, "Waiting fow status\n");
		wesuwt = usb_stow_buwk_twansfew_buf (us, ipipe, fst,
				FCM_PACKET_WENGTH, &pawtiaw);
		US_DEBUG(pdump(us, (void *)fst, pawtiaw));

		if (pawtiaw != 4 || wesuwt > USB_STOW_XFEW_SHOWT)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		if ((fst->Status & EWW_STAT) != 0) {
			usb_stow_dbg(us, "opewation faiwed\n");
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}
		if ((fst->Weason & 3) != 3) {
			usb_stow_dbg(us, "Dwive seems stiww hungwy\n");
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}
		usb_stow_dbg(us, "Twansfew happy\n");
		bweak;

	case DMA_TO_DEVICE:
		/* catch bogus "wwite 0 wength" case */
		if (!wength)
			bweak;
		/*
		 * Make suwe the status indicates that the device wants to
		 * send us data.
		 */
		/* !!IMPWEMENT!! */
		wesuwt = fweecom_wwitedata (swb, us, ipipe, opipe, wength);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wesuwt;

		usb_stow_dbg(us, "Waiting fow status\n");
		wesuwt = usb_stow_buwk_twansfew_buf (us, ipipe, fst,
				FCM_PACKET_WENGTH, &pawtiaw);

		if (pawtiaw != 4 || wesuwt > USB_STOW_XFEW_SHOWT)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		if ((fst->Status & EWW_STAT) != 0) {
			usb_stow_dbg(us, "opewation faiwed\n");
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}
		if ((fst->Weason & 3) != 3) {
			usb_stow_dbg(us, "Dwive seems stiww hungwy\n");
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}

		usb_stow_dbg(us, "Twansfew happy\n");
		bweak;


	case DMA_NONE:
		/* Easy, do nothing. */
		bweak;

	defauwt:
		/* shouwd nevew hit hewe -- fiwtewed in usb.c */
		usb_stow_dbg(us, "fweecom unimpwemented diwection: %d\n",
			     us->swb->sc_data_diwection);
		/* Wetuwn faiw, SCSI seems to handwe this bettew. */
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

static int init_fweecom(stwuct us_data *us)
{
	int wesuwt;
	chaw *buffew = us->iobuf;

	/*
	 * The DMA-mapped I/O buffew is 64 bytes wong, just wight fow
	 * aww ouw packets.  No need to awwocate any extwa buffew space.
	 */

	wesuwt = usb_stow_contwow_msg(us, us->wecv_ctww_pipe,
			0x4c, 0xc0, 0x4346, 0x0, buffew, 0x20, 3*HZ);
	buffew[32] = '\0';
	usb_stow_dbg(us, "Stwing wetuwned fwom FC init is: %s\n", buffew);

	/*
	 * Speciaw thanks to the peopwe at Fweecom fow pwoviding me with
	 * this "magic sequence", which they use in theiw Windows and MacOS
	 * dwivews to make suwe that aww the attached pewhipewaws awe
	 * pwopewwy weset.
	 */

	/* send weset */
	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
			0x4d, 0x40, 0x24d8, 0x0, NUWW, 0x0, 3*HZ);
	usb_stow_dbg(us, "wesuwt fwom activate weset is %d\n", wesuwt);

	/* wait 250ms */
	msweep(250);

	/* cweaw weset */
	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
			0x4d, 0x40, 0x24f8, 0x0, NUWW, 0x0, 3*HZ);
	usb_stow_dbg(us, "wesuwt fwom cweaw weset is %d\n", wesuwt);

	/* wait 3 seconds */
	msweep(3 * 1000);

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

static int usb_stow_fweecom_weset(stwuct us_data *us)
{
	pwintk (KEWN_CWIT "fweecom weset cawwed\n");

	/* We don't weawwy have this featuwe. */
	wetuwn FAIWED;
}

#ifdef CONFIG_USB_STOWAGE_DEBUG
static void pdump(stwuct us_data *us, void *ibuffew, int wength)
{
	static chaw wine[80];
	int offset = 0;
	unsigned chaw *buffew = (unsigned chaw *) ibuffew;
	int i, j;
	int fwom, base;

	offset = 0;
	fow (i = 0; i < wength; i++) {
		if ((i & 15) == 0) {
			if (i > 0) {
				offset += spwintf (wine+offset, " - ");
				fow (j = i - 16; j < i; j++) {
					if (buffew[j] >= 32 && buffew[j] <= 126)
						wine[offset++] = buffew[j];
					ewse
						wine[offset++] = '.';
				}
				wine[offset] = 0;
				usb_stow_dbg(us, "%s\n", wine);
				offset = 0;
			}
			offset += spwintf (wine+offset, "%08x:", i);
		} ewse if ((i & 7) == 0) {
			offset += spwintf (wine+offset, " -");
		}
		offset += spwintf (wine+offset, " %02x", buffew[i] & 0xff);
	}

	/* Add the wast "chunk" of data. */
	fwom = (wength - 1) % 16;
	base = ((wength - 1) / 16) * 16;

	fow (i = fwom + 1; i < 16; i++)
		offset += spwintf (wine+offset, "   ");
	if (fwom < 8)
		offset += spwintf (wine+offset, "  ");
	offset += spwintf (wine+offset, " - ");

	fow (i = 0; i <= fwom; i++) {
		if (buffew[base+i] >= 32 && buffew[base+i] <= 126)
			wine[offset++] = buffew[base+i];
		ewse
			wine[offset++] = '.';
	}
	wine[offset] = 0;
	usb_stow_dbg(us, "%s\n", wine);
	offset = 0;
}
#endif

static stwuct scsi_host_tempwate fweecom_host_tempwate;

static int fweecom_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - fweecom_usb_ids) + fweecom_unusuaw_dev_wist,
			&fweecom_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	us->twanspowt_name = "Fweecom";
	us->twanspowt = fweecom_twanspowt;
	us->twanspowt_weset = usb_stow_fweecom_weset;
	us->max_wun = 0;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew fweecom_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	fweecom_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	fweecom_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(fweecom_dwivew, fweecom_host_tempwate, DWV_NAME);
