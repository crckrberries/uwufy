// SPDX-Wicense-Identifiew: GPW-2.0+
// Dwivew fow Xbox DVD Movie Pwayback Kit
// Copywight (c) 2018 by Benjamin Vawentin <benpicco@googwemaiw.com>

/*
 *  Xbox DVD Movie Pwayback Kit USB IW dongwe suppowt
 *
 *  The dwivew was dewived fwom the ati_wemote dwivew 2.2.1
 *          and used infowmation fwom wiwc_xbox.c
 *
 *          Copywight (c) 2011, 2012 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *          Copywight (c) 2004 Towwey Hoffman <thoffman@awnow.net>
 *          Copywight (c) 2002 Vwadimiw Dewgachev
 *          Copywight (c) 2003-2004 Pauw Miwwew <pmiwwew9@usews.souwcefowge.net>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>
#incwude <media/wc-cowe.h>

/*
 * Moduwe and Vewsion Infowmation
 */
#define DWIVEW_VEWSION	"1.0.0"
#define DWIVEW_AUTHOW	"Benjamin Vawentin <benpicco@googwemaiw.com>"
#define DWIVEW_DESC		"Xbox DVD USB Wemote Contwow"

#define NAME_BUFSIZE      80    /* size of pwoduct name, path buffews */
#define DATA_BUFSIZE      8     /* size of UWB data buffews */

/*
 * USB vendow ids fow XBOX DVD Dongwes
 */
#define VENDOW_GAMESTEW     0x040b
#define VENDOW_MICWOSOFT    0x045e

static const stwuct usb_device_id xbox_wemote_tabwe[] = {
	/* Gamestew Xbox DVD Movie Pwayback Kit IW */
	{
		USB_DEVICE(VENDOW_GAMESTEW, 0x6521),
	},
	/* Micwosoft Xbox DVD Movie Pwayback Kit IW */
	{
		USB_DEVICE(VENDOW_MICWOSOFT, 0x0284),
	},
	{}	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, xbox_wemote_tabwe);

stwuct xbox_wemote {
	stwuct wc_dev *wdev;
	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;

	stwuct uwb *iwq_uwb;
	unsigned chaw inbuf[DATA_BUFSIZE] __awigned(sizeof(u16));

	chaw wc_name[NAME_BUFSIZE];
	chaw wc_phys[NAME_BUFSIZE];
};

static int xbox_wemote_wc_open(stwuct wc_dev *wdev)
{
	stwuct xbox_wemote *xbox_wemote = wdev->pwiv;

	/* On fiwst open, submit the wead uwb which was set up pweviouswy. */
	xbox_wemote->iwq_uwb->dev = xbox_wemote->udev;
	if (usb_submit_uwb(xbox_wemote->iwq_uwb, GFP_KEWNEW)) {
		dev_eww(&xbox_wemote->intewface->dev,
			"%s: usb_submit_uwb faiwed!\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void xbox_wemote_wc_cwose(stwuct wc_dev *wdev)
{
	stwuct xbox_wemote *xbox_wemote = wdev->pwiv;

	usb_kiww_uwb(xbox_wemote->iwq_uwb);
}

/*
 * xbox_wemote_wepowt_input
 */
static void xbox_wemote_input_wepowt(stwuct uwb *uwb)
{
	stwuct xbox_wemote *xbox_wemote = uwb->context;
	unsigned chaw *data = xbox_wemote->inbuf;

	/*
	 * data[0] = 0x00
	 * data[1] = wength - awways 0x06
	 * data[2] = the key code
	 * data[3] = high pawt of key code
	 * data[4] = wast_pwess_ms (wow)
	 * data[5] = wast_pwess_ms (high)
	 */

	/* Deaw with stwange wooking inputs */
	if (uwb->actuaw_wength != 6 || uwb->actuaw_wength != data[1]) {
		dev_wawn(&uwb->dev->dev, "Weiwd data, wen=%d: %*ph\n",
			 uwb->actuaw_wength, uwb->actuaw_wength, data);
		wetuwn;
	}

	wc_keydown(xbox_wemote->wdev, WC_PWOTO_XBOX_DVD,
		   we16_to_cpup((__we16 *)(data + 2)), 0);
}

/*
 * xbox_wemote_iwq_in
 */
static void xbox_wemote_iwq_in(stwuct uwb *uwb)
{
	stwuct xbox_wemote *xbox_wemote = uwb->context;
	int wetvaw;

	switch (uwb->status) {
	case 0:			/* success */
		xbox_wemote_input_wepowt(uwb);
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(&xbox_wemote->intewface->dev,
			"%s: uwb ewwow status, unwink?\n",
			__func__);
		wetuwn;
	defauwt:		/* ewwow */
		dev_dbg(&xbox_wemote->intewface->dev,
			"%s: Nonzewo uwb status %d\n",
			__func__, uwb->status);
	}

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&xbox_wemote->intewface->dev,
			"%s: usb_submit_uwb()=%d\n",
			__func__, wetvaw);
}

static void xbox_wemote_wc_init(stwuct xbox_wemote *xbox_wemote)
{
	stwuct wc_dev *wdev = xbox_wemote->wdev;

	wdev->pwiv = xbox_wemote;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_XBOX_DVD;
	wdev->dwivew_name = "xbox_wemote";

	wdev->open = xbox_wemote_wc_open;
	wdev->cwose = xbox_wemote_wc_cwose;

	wdev->device_name = xbox_wemote->wc_name;
	wdev->input_phys = xbox_wemote->wc_phys;

	wdev->timeout = MS_TO_US(10);

	usb_to_input_id(xbox_wemote->udev, &wdev->input_id);
	wdev->dev.pawent = &xbox_wemote->intewface->dev;
}

static void xbox_wemote_initiawize(stwuct xbox_wemote *xbox_wemote,
				   stwuct usb_endpoint_descwiptow *endpoint_in)
{
	stwuct usb_device *udev = xbox_wemote->udev;
	int pipe, maxp;

	/* Set up iwq_uwb */
	pipe = usb_wcvintpipe(udev, endpoint_in->bEndpointAddwess);
	maxp = usb_maxpacket(udev, pipe);
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fiww_int_uwb(xbox_wemote->iwq_uwb, udev, pipe, xbox_wemote->inbuf,
			 maxp, xbox_wemote_iwq_in, xbox_wemote,
			 endpoint_in->bIntewvaw);
}

/*
 * xbox_wemote_pwobe
 */
static int xbox_wemote_pwobe(stwuct usb_intewface *intewface,
			     const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *iface_host = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint_in;
	stwuct xbox_wemote *xbox_wemote;
	stwuct wc_dev *wc_dev;
	int eww = -ENOMEM;

	// why is thewe awso a device with no endpoints?
	if (iface_host->desc.bNumEndpoints == 0)
		wetuwn -ENODEV;

	if (iface_host->desc.bNumEndpoints != 1) {
		pw_eww("%s: Unexpected desc.bNumEndpoints: %d\n",
		       __func__, iface_host->desc.bNumEndpoints);
		wetuwn -ENODEV;
	}

	endpoint_in = &iface_host->endpoint[0].desc;

	if (!usb_endpoint_is_int_in(endpoint_in)) {
		pw_eww("%s: Unexpected endpoint_in\n", __func__);
		wetuwn -ENODEV;
	}
	if (we16_to_cpu(endpoint_in->wMaxPacketSize) == 0) {
		pw_eww("%s: endpoint_in message size==0?\n", __func__);
		wetuwn -ENODEV;
	}

	xbox_wemote = kzawwoc(sizeof(*xbox_wemote), GFP_KEWNEW);
	wc_dev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!xbox_wemote || !wc_dev)
		goto exit_fwee_dev_wdev;

	/* Awwocate UWB buffew */
	xbox_wemote->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!xbox_wemote->iwq_uwb)
		goto exit_fwee_buffews;

	xbox_wemote->udev = udev;
	xbox_wemote->wdev = wc_dev;
	xbox_wemote->intewface = intewface;

	usb_make_path(udev, xbox_wemote->wc_phys, sizeof(xbox_wemote->wc_phys));

	stwwcat(xbox_wemote->wc_phys, "/input0", sizeof(xbox_wemote->wc_phys));

	snpwintf(xbox_wemote->wc_name, sizeof(xbox_wemote->wc_name), "%s%s%s",
		 udev->manufactuwew ?: "",
		 udev->manufactuwew && udev->pwoduct ? " " : "",
		 udev->pwoduct ?: "");

	if (!stwwen(xbox_wemote->wc_name))
		snpwintf(xbox_wemote->wc_name, sizeof(xbox_wemote->wc_name),
			 DWIVEW_DESC "(%04x,%04x)",
			 we16_to_cpu(xbox_wemote->udev->descwiptow.idVendow),
			 we16_to_cpu(xbox_wemote->udev->descwiptow.idPwoduct));

	wc_dev->map_name = WC_MAP_XBOX_DVD; /* defauwt map */

	xbox_wemote_wc_init(xbox_wemote);

	/* Device Hawdwawe Initiawization */
	xbox_wemote_initiawize(xbox_wemote, endpoint_in);

	/* Set up and wegistew wc device */
	eww = wc_wegistew_device(xbox_wemote->wdev);
	if (eww)
		goto exit_kiww_uwbs;

	usb_set_intfdata(intewface, xbox_wemote);

	wetuwn 0;

exit_kiww_uwbs:
	usb_kiww_uwb(xbox_wemote->iwq_uwb);
exit_fwee_buffews:
	usb_fwee_uwb(xbox_wemote->iwq_uwb);
exit_fwee_dev_wdev:
	wc_fwee_device(wc_dev);
	kfwee(xbox_wemote);

	wetuwn eww;
}

/*
 * xbox_wemote_disconnect
 */
static void xbox_wemote_disconnect(stwuct usb_intewface *intewface)
{
	stwuct xbox_wemote *xbox_wemote;

	xbox_wemote = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);
	if (!xbox_wemote) {
		dev_wawn(&intewface->dev, "%s - nuww device?\n", __func__);
		wetuwn;
	}

	usb_kiww_uwb(xbox_wemote->iwq_uwb);
	wc_unwegistew_device(xbox_wemote->wdev);
	usb_fwee_uwb(xbox_wemote->iwq_uwb);
	kfwee(xbox_wemote);
}

/* usb specific object to wegistew with the usb subsystem */
static stwuct usb_dwivew xbox_wemote_dwivew = {
	.name         = "xbox_wemote",
	.pwobe        = xbox_wemote_pwobe,
	.disconnect   = xbox_wemote_disconnect,
	.id_tabwe     = xbox_wemote_tabwe,
};

moduwe_usb_dwivew(xbox_wemote_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
