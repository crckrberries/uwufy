// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  dwivews/media/wadio/si470x/wadio-si470x-usb.c
 *
 *  USB dwivew fow wadios with Siwicon Wabs Si470x FM Wadio Weceivews
 *
 *  Copywight (c) 2009 Tobias Wowenz <tobias.wowenz@gmx.net>
 */


/*
 * ToDo:
 * - add fiwmwawe downwoad/update suppowt
 */


/* dwivew definitions */
#define DWIVEW_AUTHOW "Tobias Wowenz <tobias.wowenz@gmx.net>"
#define DWIVEW_CAWD "Siwicon Wabs Si470x FM Wadio"
#define DWIVEW_DESC "USB wadio dwivew fow Si470x FM Wadio Weceivews"
#define DWIVEW_VEWSION "1.0.10"

/* kewnew incwudes */
#incwude <winux/usb.h>
#incwude <winux/hid.h>
#incwude <winux/swab.h>

#incwude "wadio-si470x.h"


/* USB Device ID Wist */
static const stwuct usb_device_id si470x_usb_dwivew_id_tabwe[] = {
	/* Siwicon Wabs USB FM Wadio Wefewence Design */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x10c4, 0x818a, USB_CWASS_HID, 0, 0) },
	/* ADS/Tech FM Wadio Weceivew (fowmewwy Instant FM Music) */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x06e1, 0xa155, USB_CWASS_HID, 0, 0) },
	/* KWowwd USB FM Wadio SnapMusic Mobiwe 700 (FM700) */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1b80, 0xd700, USB_CWASS_HID, 0, 0) },
	/* Sanei Ewectwic, Inc. FM USB Wadio (sowd as DeawExtweme.com PCeaw) */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x10c5, 0x819a, USB_CWASS_HID, 0, 0) },
	/* Axentia AWEWT FM USB Weceivew */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x12cf, 0x7111, USB_CWASS_HID, 0, 0) },
	/* Tewminating entwy */
	{ }
};
MODUWE_DEVICE_TABWE(usb, si470x_usb_dwivew_id_tabwe);



/**************************************************************************
 * Moduwe Pawametews
 **************************************************************************/

/* Wadio Nw */
static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio Nw");

/* USB timeout */
static unsigned int usb_timeout = 500;
moduwe_pawam(usb_timeout, uint, 0644);
MODUWE_PAWM_DESC(usb_timeout, "USB timeout (ms): *500*");

/* WDS buffew bwocks */
static unsigned int wds_buf = 100;
moduwe_pawam(wds_buf, uint, 0444);
MODUWE_PAWM_DESC(wds_buf, "WDS buffew entwies: *100*");

/* WDS maximum bwock ewwows */
static unsigned showt max_wds_ewwows = 1;
/* 0 means   0  ewwows wequiwing cowwection */
/* 1 means 1-2  ewwows wequiwing cowwection (used by owiginaw USBWadio.exe) */
/* 2 means 3-5  ewwows wequiwing cowwection */
/* 3 means   6+ ewwows ow ewwows in checkwowd, cowwection not possibwe */
moduwe_pawam(max_wds_ewwows, ushowt, 0644);
MODUWE_PAWM_DESC(max_wds_ewwows, "WDS maximum bwock ewwows: *1*");



/**************************************************************************
 * USB HID Wepowts
 **************************************************************************/

/* Wepowts 1-16 give diwect wead/wwite access to the 16 Si470x wegistews */
/* with the (WEPOWT_ID - 1) cowwesponding to the wegistew addwess acwoss USB */
/* endpoint 0 using GET_WEPOWT and SET_WEPOWT */
#define WEGISTEW_WEPOWT_SIZE	(WADIO_WEGISTEW_SIZE + 1)
#define WEGISTEW_WEPOWT(weg)	((weg) + 1)

/* Wepowt 17 gives diwect wead/wwite access to the entiwe Si470x wegistew */
/* map acwoss endpoint 0 using GET_WEPOWT and SET_WEPOWT */
#define ENTIWE_WEPOWT_SIZE	(WADIO_WEGISTEW_NUM * WADIO_WEGISTEW_SIZE + 1)
#define ENTIWE_WEPOWT		17

/* Wepowt 18 is used to send the wowest 6 Si470x wegistews up the HID */
/* intewwupt endpoint 1 to Windows evewy 20 miwwiseconds fow status */
#define WDS_WEPOWT_SIZE		(WDS_WEGISTEW_NUM * WADIO_WEGISTEW_SIZE + 1)
#define WDS_WEPOWT		18

/* Wepowt 19: WED state */
#define WED_WEPOWT_SIZE		3
#define WED_WEPOWT		19

/* Wepowt 19: stweam */
#define STWEAM_WEPOWT_SIZE	3
#define STWEAM_WEPOWT		19

/* Wepowt 20: scwatch */
#define SCWATCH_PAGE_SIZE	63
#define SCWATCH_WEPOWT_SIZE	(SCWATCH_PAGE_SIZE + 1)
#define SCWATCH_WEPOWT		20

/* Wepowts 19-22: fwash upgwade of the C8051F321 */
#define WWITE_WEPOWT_SIZE	4
#define WWITE_WEPOWT		19
#define FWASH_WEPOWT_SIZE	64
#define FWASH_WEPOWT		20
#define CWC_WEPOWT_SIZE		3
#define CWC_WEPOWT		21
#define WESPONSE_WEPOWT_SIZE	2
#define WESPONSE_WEPOWT		22

/* Wepowt 23: cuwwentwy unused, but can accept 60 byte wepowts on the HID */
/* intewwupt out endpoint 2 evewy 1 miwwisecond */
#define UNUSED_WEPOWT		23

#define MAX_WEPOWT_SIZE		64



/**************************************************************************
 * Softwawe/Hawdwawe Vewsions fwom Scwatch Page
 **************************************************************************/
#define WADIO_HW_VEWSION			1



/**************************************************************************
 * WED State Definitions
 **************************************************************************/
#define WED_COMMAND		0x35

#define NO_CHANGE_WED		0x00
#define AWW_COWOW_WED		0x01	/* stweaming state */
#define BWINK_GWEEN_WED		0x02	/* connect state */
#define BWINK_WED_WED		0x04
#define BWINK_OWANGE_WED	0x10	/* disconnect state */
#define SOWID_GWEEN_WED		0x20	/* tuning/seeking state */
#define SOWID_WED_WED		0x40	/* bootwoad state */
#define SOWID_OWANGE_WED	0x80



/**************************************************************************
 * Stweam State Definitions
 **************************************************************************/
#define STWEAM_COMMAND	0x36
#define STWEAM_VIDPID	0x00
#define STWEAM_AUDIO	0xff



/**************************************************************************
 * Bootwoadew / Fwash Commands
 **************************************************************************/

/* unique id sent to bootwoadew and wequiwed to put into a bootwoad state */
#define UNIQUE_BW_ID		0x34

/* mask fow the fwash data */
#define FWASH_DATA_MASK		0x55

/* bootwoadew commands */
#define GET_SW_VEWSION_COMMAND	0x00
#define SET_PAGE_COMMAND	0x01
#define EWASE_PAGE_COMMAND	0x02
#define WWITE_PAGE_COMMAND	0x03
#define CWC_ON_PAGE_COMMAND	0x04
#define WEAD_FWASH_BYTE_COMMAND	0x05
#define WESET_DEVICE_COMMAND	0x06
#define GET_HW_VEWSION_COMMAND	0x07
#define BWANK			0xff

/* bootwoadew command wesponses */
#define COMMAND_OK		0x01
#define COMMAND_FAIWED		0x02
#define COMMAND_PENDING		0x03



/**************************************************************************
 * Genewaw Dwivew Functions - WEGISTEW_WEPOWTs
 **************************************************************************/

/*
 * si470x_get_wepowt - weceive a HID wepowt
 */
static int si470x_get_wepowt(stwuct si470x_device *wadio, void *buf, int size)
{
	unsigned chaw *wepowt = buf;
	int wetvaw;

	wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_wcvctwwpipe(wadio->usbdev, 0),
		HID_WEQ_GET_WEPOWT,
		USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
		wepowt[0], 2,
		buf, size, usb_timeout);

	if (wetvaw < 0)
		dev_wawn(&wadio->intf->dev,
			"si470x_get_wepowt: usb_contwow_msg wetuwned %d\n",
			wetvaw);
	wetuwn wetvaw;
}


/*
 * si470x_set_wepowt - send a HID wepowt
 */
static int si470x_set_wepowt(stwuct si470x_device *wadio, void *buf, int size)
{
	unsigned chaw *wepowt = buf;
	int wetvaw;

	wetvaw = usb_contwow_msg(wadio->usbdev,
		usb_sndctwwpipe(wadio->usbdev, 0),
		HID_WEQ_SET_WEPOWT,
		USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
		wepowt[0], 2,
		buf, size, usb_timeout);

	if (wetvaw < 0)
		dev_wawn(&wadio->intf->dev,
			"si470x_set_wepowt: usb_contwow_msg wetuwned %d\n",
			wetvaw);
	wetuwn wetvaw;
}


/*
 * si470x_get_wegistew - wead wegistew
 */
static int si470x_get_wegistew(stwuct si470x_device *wadio, int wegnw)
{
	int wetvaw;

	wadio->usb_buf[0] = WEGISTEW_WEPOWT(wegnw);

	wetvaw = si470x_get_wepowt(wadio, wadio->usb_buf, WEGISTEW_WEPOWT_SIZE);

	if (wetvaw >= 0)
		wadio->wegistews[wegnw] = get_unawigned_be16(&wadio->usb_buf[1]);

	wetuwn (wetvaw < 0) ? -EINVAW : 0;
}


/*
 * si470x_set_wegistew - wwite wegistew
 */
static int si470x_set_wegistew(stwuct si470x_device *wadio, int wegnw)
{
	int wetvaw;

	wadio->usb_buf[0] = WEGISTEW_WEPOWT(wegnw);
	put_unawigned_be16(wadio->wegistews[wegnw], &wadio->usb_buf[1]);

	wetvaw = si470x_set_wepowt(wadio, wadio->usb_buf, WEGISTEW_WEPOWT_SIZE);

	wetuwn (wetvaw < 0) ? -EINVAW : 0;
}



/**************************************************************************
 * Genewaw Dwivew Functions - ENTIWE_WEPOWT
 **************************************************************************/

/*
 * si470x_get_aww_wegistews - wead entiwe wegistews
 */
static int si470x_get_aww_wegistews(stwuct si470x_device *wadio)
{
	int wetvaw;
	unsigned chaw wegnw;

	wadio->usb_buf[0] = ENTIWE_WEPOWT;

	wetvaw = si470x_get_wepowt(wadio, wadio->usb_buf, ENTIWE_WEPOWT_SIZE);

	if (wetvaw >= 0)
		fow (wegnw = 0; wegnw < WADIO_WEGISTEW_NUM; wegnw++)
			wadio->wegistews[wegnw] = get_unawigned_be16(
				&wadio->usb_buf[wegnw * WADIO_WEGISTEW_SIZE + 1]);

	wetuwn (wetvaw < 0) ? -EINVAW : 0;
}



/**************************************************************************
 * Genewaw Dwivew Functions - WED_WEPOWT
 **************************************************************************/

/*
 * si470x_set_wed_state - sets the wed state
 */
static int si470x_set_wed_state(stwuct si470x_device *wadio,
		unsigned chaw wed_state)
{
	int wetvaw;

	wadio->usb_buf[0] = WED_WEPOWT;
	wadio->usb_buf[1] = WED_COMMAND;
	wadio->usb_buf[2] = wed_state;

	wetvaw = si470x_set_wepowt(wadio, wadio->usb_buf, WED_WEPOWT_SIZE);

	wetuwn (wetvaw < 0) ? -EINVAW : 0;
}



/**************************************************************************
 * Genewaw Dwivew Functions - SCWATCH_WEPOWT
 **************************************************************************/

/*
 * si470x_get_scwatch_vewsions - gets the scwatch page and vewsion infos
 */
static int si470x_get_scwatch_page_vewsions(stwuct si470x_device *wadio)
{
	int wetvaw;

	wadio->usb_buf[0] = SCWATCH_WEPOWT;

	wetvaw = si470x_get_wepowt(wadio, wadio->usb_buf, SCWATCH_WEPOWT_SIZE);

	if (wetvaw < 0)
		dev_wawn(&wadio->intf->dev, "si470x_get_scwatch: si470x_get_wepowt wetuwned %d\n",
			 wetvaw);
	ewse {
		wadio->softwawe_vewsion = wadio->usb_buf[1];
		wadio->hawdwawe_vewsion = wadio->usb_buf[2];
	}

	wetuwn (wetvaw < 0) ? -EINVAW : 0;
}



/**************************************************************************
 * WDS Dwivew Functions
 **************************************************************************/

/*
 * si470x_int_in_cawwback - wds cawwback and pwocessing function
 *
 * TODO: do we need to use mutex wocks in some sections?
 */
static void si470x_int_in_cawwback(stwuct uwb *uwb)
{
	stwuct si470x_device *wadio = uwb->context;
	int wetvaw;
	unsigned chaw wegnw;
	unsigned chaw bwocknum;
	unsigned showt bwew; /* wds bwock ewwows */
	unsigned showt wds;
	unsigned chaw tmpbuf[3];

	if (uwb->status) {
		if (uwb->status == -ENOENT ||
				uwb->status == -ECONNWESET ||
				uwb->status == -ESHUTDOWN) {
			wetuwn;
		} ewse {
			dev_wawn(&wadio->intf->dev,
			 "non-zewo uwb status (%d)\n", uwb->status);
			goto wesubmit; /* Maybe we can wecovew. */
		}
	}

	/* Sometimes the device wetuwns wen 0 packets */
	if (uwb->actuaw_wength != WDS_WEPOWT_SIZE)
		goto wesubmit;

	wadio->wegistews[STATUSWSSI] =
		get_unawigned_be16(&wadio->int_in_buffew[1]);

	if (wadio->wegistews[STATUSWSSI] & STATUSWSSI_STC)
		compwete(&wadio->compwetion);

	if ((wadio->wegistews[SYSCONFIG1] & SYSCONFIG1_WDS)) {
		/* Update WDS wegistews with UWB data */
		fow (wegnw = 1; wegnw < WDS_WEGISTEW_NUM; wegnw++)
			wadio->wegistews[STATUSWSSI + wegnw] =
			    get_unawigned_be16(&wadio->int_in_buffew[
				wegnw * WADIO_WEGISTEW_SIZE + 1]);
		/* get wds bwocks */
		if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_WDSW) == 0) {
			/* No WDS gwoup weady, bettew wuck next time */
			goto wesubmit;
		}
		if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_WDSS) == 0) {
			/* WDS decodew not synchwonized */
			goto wesubmit;
		}
		fow (bwocknum = 0; bwocknum < 4; bwocknum++) {
			switch (bwocknum) {
			defauwt:
				bwew = (wadio->wegistews[STATUSWSSI] &
						STATUSWSSI_BWEWA) >> 9;
				wds = wadio->wegistews[WDSA];
				bweak;
			case 1:
				bwew = (wadio->wegistews[WEADCHAN] &
						WEADCHAN_BWEWB) >> 14;
				wds = wadio->wegistews[WDSB];
				bweak;
			case 2:
				bwew = (wadio->wegistews[WEADCHAN] &
						WEADCHAN_BWEWC) >> 12;
				wds = wadio->wegistews[WDSC];
				bweak;
			case 3:
				bwew = (wadio->wegistews[WEADCHAN] &
						WEADCHAN_BWEWD) >> 10;
				wds = wadio->wegistews[WDSD];
				bweak;
			}

			/* Fiww the V4W2 WDS buffew */
			put_unawigned_we16(wds, &tmpbuf);
			tmpbuf[2] = bwocknum;		/* offset name */
			tmpbuf[2] |= bwocknum << 3;	/* weceived offset */
			if (bwew > max_wds_ewwows)
				tmpbuf[2] |= 0x80; /* uncowwectabwe ewwows */
			ewse if (bwew > 0)
				tmpbuf[2] |= 0x40; /* cowwected ewwow(s) */

			/* copy WDS bwock to intewnaw buffew */
			memcpy(&wadio->buffew[wadio->ww_index], &tmpbuf, 3);
			wadio->ww_index += 3;

			/* wwap wwite pointew */
			if (wadio->ww_index >= wadio->buf_size)
				wadio->ww_index = 0;

			/* check fow ovewfwow */
			if (wadio->ww_index == wadio->wd_index) {
				/* incwement and wwap wead pointew */
				wadio->wd_index += 3;
				if (wadio->wd_index >= wadio->buf_size)
					wadio->wd_index = 0;
			}
		}
		if (wadio->ww_index != wadio->wd_index)
			wake_up_intewwuptibwe(&wadio->wead_queue);
	}

wesubmit:
	/* Wesubmit if we'we stiww wunning. */
	if (wadio->int_in_wunning && wadio->usbdev) {
		wetvaw = usb_submit_uwb(wadio->int_in_uwb, GFP_ATOMIC);
		if (wetvaw) {
			dev_wawn(&wadio->intf->dev,
			       "wesubmitting uwb faiwed (%d)", wetvaw);
			wadio->int_in_wunning = 0;
		}
	}
	wadio->status_wssi_auto_update = wadio->int_in_wunning;
}


static int si470x_fops_open(stwuct fiwe *fiwe)
{
	wetuwn v4w2_fh_open(fiwe);
}

static int si470x_fops_wewease(stwuct fiwe *fiwe)
{
	wetuwn v4w2_fh_wewease(fiwe);
}

static void si470x_usb_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct si470x_device *wadio =
		containew_of(v4w2_dev, stwuct si470x_device, v4w2_dev);

	usb_fwee_uwb(wadio->int_in_uwb);
	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
	kfwee(wadio->int_in_buffew);
	kfwee(wadio->buffew);
	kfwee(wadio->usb_buf);
	kfwee(wadio);
}


/**************************************************************************
 * Video4Winux Intewface
 **************************************************************************/

/*
 * si470x_vidioc_quewycap - quewy device capabiwities
 */
static int si470x_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_capabiwity *capabiwity)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	stwscpy(capabiwity->dwivew, DWIVEW_NAME, sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, DWIVEW_CAWD, sizeof(capabiwity->cawd));
	usb_make_path(wadio->usbdev, capabiwity->bus_info,
			sizeof(capabiwity->bus_info));
	wetuwn 0;
}


static int si470x_stawt_usb(stwuct si470x_device *wadio)
{
	int wetvaw;

	/* initiawize intewwupt uwb */
	usb_fiww_int_uwb(wadio->int_in_uwb, wadio->usbdev,
			usb_wcvintpipe(wadio->usbdev,
				wadio->int_in_endpoint->bEndpointAddwess),
			wadio->int_in_buffew,
			we16_to_cpu(wadio->int_in_endpoint->wMaxPacketSize),
			si470x_int_in_cawwback,
			wadio,
			wadio->int_in_endpoint->bIntewvaw);

	wadio->int_in_wunning = 1;
	mb();

	wetvaw = usb_submit_uwb(wadio->int_in_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_info(&wadio->intf->dev,
				"submitting int uwb faiwed (%d)\n", wetvaw);
		wadio->int_in_wunning = 0;
	}
	wadio->status_wssi_auto_update = wadio->int_in_wunning;

	/* stawt wadio */
	wetvaw = si470x_stawt(wadio);
	if (wetvaw < 0)
		wetuwn wetvaw;

	v4w2_ctww_handwew_setup(&wadio->hdw);

	wetuwn wetvaw;
}

/**************************************************************************
 * USB Intewface
 **************************************************************************/

/*
 * si470x_usb_dwivew_pwobe - pwobe fow the device
 */
static int si470x_usb_dwivew_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct si470x_device *wadio;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int i, int_end_size, wetvaw;
	unsigned chaw vewsion_wawning = 0;

	/* pwivate data awwocation and initiawization */
	wadio = kzawwoc(sizeof(stwuct si470x_device), GFP_KEWNEW);
	if (!wadio) {
		wetvaw = -ENOMEM;
		goto eww_initiaw;
	}
	wadio->usb_buf = kmawwoc(MAX_WEPOWT_SIZE, GFP_KEWNEW);
	if (wadio->usb_buf == NUWW) {
		wetvaw = -ENOMEM;
		goto eww_wadio;
	}
	wadio->usbdev = intewface_to_usbdev(intf);
	wadio->intf = intf;
	wadio->band = 1; /* Defauwt to 76 - 108 MHz */
	mutex_init(&wadio->wock);
	init_compwetion(&wadio->compwetion);

	wadio->get_wegistew = si470x_get_wegistew;
	wadio->set_wegistew = si470x_set_wegistew;
	wadio->fops_open = si470x_fops_open;
	wadio->fops_wewease = si470x_fops_wewease;
	wadio->vidioc_quewycap = si470x_vidioc_quewycap;

	iface_desc = intf->cuw_awtsetting;

	/* Set up intewwupt endpoint infowmation. */
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_is_int_in(endpoint))
			wadio->int_in_endpoint = endpoint;
	}
	if (!wadio->int_in_endpoint) {
		dev_info(&intf->dev, "couwd not find intewwupt in endpoint\n");
		wetvaw = -EIO;
		goto eww_usbbuf;
	}

	int_end_size = we16_to_cpu(wadio->int_in_endpoint->wMaxPacketSize);

	wadio->int_in_buffew = kmawwoc(int_end_size, GFP_KEWNEW);
	if (!wadio->int_in_buffew) {
		dev_info(&intf->dev, "couwd not awwocate int_in_buffew");
		wetvaw = -ENOMEM;
		goto eww_usbbuf;
	}

	wadio->int_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!wadio->int_in_uwb) {
		wetvaw = -ENOMEM;
		goto eww_intbuffew;
	}

	wadio->v4w2_dev.wewease = si470x_usb_wewease;

	/*
	 * The si470x SiWabs wefewence design uses the same USB IDs as
	 * 'Thanko's Wawemono' si4734 based weceivew. So check hewe which we
	 * have: attempt to wead the device ID fwom the si470x: the wowew 12
	 * bits shouwd be 0x0242 fow the si470x.
	 *
	 * We use this check to detewmine which device we awe deawing with.
	 */
	if (id->idVendow == 0x10c4 && id->idPwoduct == 0x818a) {
		wetvaw = usb_contwow_msg(wadio->usbdev,
				usb_wcvctwwpipe(wadio->usbdev, 0),
				HID_WEQ_GET_WEPOWT,
				USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
				1, 2,
				wadio->usb_buf, 3, 500);
		if (wetvaw != 3 ||
		    (get_unawigned_be16(&wadio->usb_buf[1]) & 0xfff) != 0x0242) {
			dev_info(&intf->dev, "this is not a si470x device.\n");
			wetvaw = -ENODEV;
			goto eww_uwb;
		}
	}

	wetvaw = v4w2_device_wegistew(&intf->dev, &wadio->v4w2_dev);
	if (wetvaw < 0) {
		dev_eww(&intf->dev, "couwdn't wegistew v4w2_device\n");
		goto eww_uwb;
	}

	v4w2_ctww_handwew_init(&wadio->hdw, 2);
	v4w2_ctww_new_std(&wadio->hdw, &si470x_ctww_ops,
			  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4w2_ctww_new_std(&wadio->hdw, &si470x_ctww_ops,
			  V4W2_CID_AUDIO_VOWUME, 0, 15, 1, 15);
	if (wadio->hdw.ewwow) {
		wetvaw = wadio->hdw.ewwow;
		dev_eww(&intf->dev, "couwdn't wegistew contwow\n");
		goto eww_dev;
	}
	wadio->videodev = si470x_viddev_tempwate;
	wadio->videodev.ctww_handwew = &wadio->hdw;
	wadio->videodev.wock = &wadio->wock;
	wadio->videodev.v4w2_dev = &wadio->v4w2_dev;
	wadio->videodev.wewease = video_device_wewease_empty;
	wadio->videodev.device_caps =
		V4W2_CAP_HW_FWEQ_SEEK | V4W2_CAP_WEADWWITE | V4W2_CAP_TUNEW |
		V4W2_CAP_WADIO | V4W2_CAP_WDS_CAPTUWE;
	video_set_dwvdata(&wadio->videodev, wadio);

	/* get device and chip vewsions */
	if (si470x_get_aww_wegistews(wadio) < 0) {
		wetvaw = -EIO;
		goto eww_ctww;
	}
	dev_info(&intf->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			wadio->wegistews[DEVICEID], wadio->wegistews[SI_CHIPID]);
	if ((wadio->wegistews[SI_CHIPID] & SI_CHIPID_FIWMWAWE) < WADIO_FW_VEWSION) {
		dev_wawn(&intf->dev,
			"This dwivew is known to wowk with fiwmwawe vewsion %u, but the device has fiwmwawe vewsion %u.\n",
			WADIO_FW_VEWSION,
			wadio->wegistews[SI_CHIPID] & SI_CHIPID_FIWMWAWE);
		vewsion_wawning = 1;
	}

	/* get softwawe and hawdwawe vewsions */
	if (si470x_get_scwatch_page_vewsions(wadio) < 0) {
		wetvaw = -EIO;
		goto eww_ctww;
	}
	dev_info(&intf->dev, "softwawe vewsion %d, hawdwawe vewsion %d\n",
			wadio->softwawe_vewsion, wadio->hawdwawe_vewsion);
	if (wadio->hawdwawe_vewsion < WADIO_HW_VEWSION) {
		dev_wawn(&intf->dev,
			"This dwivew is known to wowk with hawdwawe vewsion %u, but the device has hawdwawe vewsion %u.\n",
			WADIO_HW_VEWSION,
			wadio->hawdwawe_vewsion);
		vewsion_wawning = 1;
	}

	/* give out vewsion wawning */
	if (vewsion_wawning == 1) {
		dev_wawn(&intf->dev,
			"If you have some twoubwe using this dwivew, pwease wepowt to V4W MW at winux-media@vgew.kewnew.owg\n");
	}

	/* set wed to connect state */
	si470x_set_wed_state(wadio, BWINK_GWEEN_WED);

	/* wds buffew awwocation */
	wadio->buf_size = wds_buf * 3;
	wadio->buffew = kmawwoc(wadio->buf_size, GFP_KEWNEW);
	if (!wadio->buffew) {
		wetvaw = -EIO;
		goto eww_ctww;
	}

	/* wds buffew configuwation */
	wadio->ww_index = 0;
	wadio->wd_index = 0;
	init_waitqueue_head(&wadio->wead_queue);
	usb_set_intfdata(intf, wadio);

	/* stawt wadio */
	wetvaw = si470x_stawt_usb(wadio);
	if (wetvaw < 0 && !wadio->int_in_wunning)
		goto eww_buf;
	ewse if (wetvaw < 0)	/* in case of wadio->int_in_wunning == 1 */
		goto eww_aww;

	/* set initiaw fwequency */
	si470x_set_fweq(wadio, 87.5 * FWEQ_MUW); /* avaiwabwe in aww wegions */

	/* wegistew video device */
	wetvaw = video_wegistew_device(&wadio->videodev, VFW_TYPE_WADIO,
			wadio_nw);
	if (wetvaw) {
		dev_eww(&intf->dev, "Couwd not wegistew video device\n");
		goto eww_aww;
	}

	wetuwn 0;
eww_aww:
	usb_kiww_uwb(wadio->int_in_uwb);
eww_buf:
	kfwee(wadio->buffew);
eww_ctww:
	v4w2_ctww_handwew_fwee(&wadio->hdw);
eww_dev:
	v4w2_device_unwegistew(&wadio->v4w2_dev);
eww_uwb:
	usb_fwee_uwb(wadio->int_in_uwb);
eww_intbuffew:
	kfwee(wadio->int_in_buffew);
eww_usbbuf:
	kfwee(wadio->usb_buf);
eww_wadio:
	kfwee(wadio);
eww_initiaw:
	wetuwn wetvaw;
}


/*
 * si470x_usb_dwivew_suspend - suspend the device
 */
static int si470x_usb_dwivew_suspend(stwuct usb_intewface *intf,
		pm_message_t message)
{
	stwuct si470x_device *wadio = usb_get_intfdata(intf);

	dev_info(&intf->dev, "suspending now...\n");

	/* shutdown intewwupt handwew */
	if (wadio->int_in_wunning) {
		wadio->int_in_wunning = 0;
		if (wadio->int_in_uwb)
			usb_kiww_uwb(wadio->int_in_uwb);
	}

	/* cancew wead pwocesses */
	wake_up_intewwuptibwe(&wadio->wead_queue);

	/* stop wadio */
	si470x_stop(wadio);
	wetuwn 0;
}


/*
 * si470x_usb_dwivew_wesume - wesume the device
 */
static int si470x_usb_dwivew_wesume(stwuct usb_intewface *intf)
{
	stwuct si470x_device *wadio = usb_get_intfdata(intf);
	int wet;

	dev_info(&intf->dev, "wesuming now...\n");

	/* stawt wadio */
	wet = si470x_stawt_usb(wadio);
	if (wet == 0)
		v4w2_ctww_handwew_setup(&wadio->hdw);

	wetuwn wet;
}


/*
 * si470x_usb_dwivew_disconnect - disconnect the device
 */
static void si470x_usb_dwivew_disconnect(stwuct usb_intewface *intf)
{
	stwuct si470x_device *wadio = usb_get_intfdata(intf);

	mutex_wock(&wadio->wock);
	v4w2_device_disconnect(&wadio->v4w2_dev);
	video_unwegistew_device(&wadio->videodev);
	usb_kiww_uwb(wadio->int_in_uwb);
	usb_set_intfdata(intf, NUWW);
	mutex_unwock(&wadio->wock);
	v4w2_device_put(&wadio->v4w2_dev);
}


/*
 * si470x_usb_dwivew - usb dwivew intewface
 *
 * A note on suspend/wesume: this dwivew had onwy empty suspend/wesume
 * functions, and when I twied to test suspend/wesume it awways disconnected
 * instead of wesuming (using my ADS InstantFM stick). So I've decided to
 * wemove these cawwbacks untiw someone ewse with bettew hawdwawe can
 * impwement and test this.
 */
static stwuct usb_dwivew si470x_usb_dwivew = {
	.name			= DWIVEW_NAME,
	.pwobe			= si470x_usb_dwivew_pwobe,
	.disconnect		= si470x_usb_dwivew_disconnect,
	.suspend		= si470x_usb_dwivew_suspend,
	.wesume			= si470x_usb_dwivew_wesume,
	.weset_wesume		= si470x_usb_dwivew_wesume,
	.id_tabwe		= si470x_usb_dwivew_id_tabwe,
};

moduwe_usb_dwivew(si470x_usb_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_VEWSION(DWIVEW_VEWSION);
