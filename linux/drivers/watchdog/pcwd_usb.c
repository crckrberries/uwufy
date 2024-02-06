// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Bewkshiwe USB-PC Watchdog Cawd Dwivew
 *
 *	(c) Copywight 2004-2007 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	Based on souwce code of the fowwowing authows:
 *	  Ken Howwis <kenji@bitgate.com>,
 *	  Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *	  Matt Domsch <Matt_Domsch@deww.com>,
 *	  Wob Wadez <wob@osinvestow.com>,
 *	  Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 *	Neithew Wim Van Sebwoeck now Iguana vzw. admit wiabiwity now
 *	pwovide wawwanty fow any of this softwawe. This matewiaw is
 *	pwovided "AS-IS" and at no chawge.
 *
 *	Thanks awso to Simon Macheww at Bewkshiwe Pwoducts Inc. fow
 *	pwoviding the test hawdwawe. Mowe info is avaiwabwe at
 *	http://www.bewkpwod.com/ ow http://www.pcwatchdog.com/
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>	/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>	/* Fow new moduwepawam's */
#incwude <winux/types.h>	/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>	/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>	/* Fow pwintk/panic/... */
#incwude <winux/deway.h>	/* Fow mdeway function */
#incwude <winux/miscdevice.h>	/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>	/* Fow the watchdog specific items */
#incwude <winux/notifiew.h>	/* Fow notifiew suppowt */
#incwude <winux/weboot.h>	/* Fow weboot_notifiew stuff */
#incwude <winux/init.h>		/* Fow __init/__exit/... */
#incwude <winux/fs.h>		/* Fow fiwe opewations */
#incwude <winux/usb.h>		/* Fow USB functions */
#incwude <winux/swab.h>		/* Fow kmawwoc, ... */
#incwude <winux/mutex.h>	/* Fow mutex wocking */
#incwude <winux/hid.h>		/* Fow HID_WEQ_SET_WEPOWT & HID_DT_WEPOWT */
#incwude <winux/uaccess.h>	/* Fow copy_to_usew/put_usew/... */


/* Moduwe and Vewsion Infowmation */
#define DWIVEW_VEWSION "1.02"
#define DWIVEW_AUTHOW "Wim Van Sebwoeck <wim@iguana.be>"
#define DWIVEW_DESC "Bewkshiwe USB-PC Watchdog dwivew"
#define DWIVEW_NAME "pcwd_usb"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define WATCHDOG_HEAWTBEAT 0	/* defauwt heawtbeat =
						deway-time fwom dip-switches */
static int heawtbeat = WATCHDOG_HEAWTBEAT;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds. "
	"(0<heawtbeat<65536 ow 0=deway-time fwom dip-switches, defauwt="
				__MODUWE_STWING(WATCHDOG_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/* The vendow and pwoduct id's fow the USB-PC Watchdog cawd */
#define USB_PCWD_VENDOW_ID	0x0c98
#define USB_PCWD_PWODUCT_ID	0x1140

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id usb_pcwd_tabwe[] = {
	{ USB_DEVICE(USB_PCWD_VENDOW_ID, USB_PCWD_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, usb_pcwd_tabwe);

/* accowding to documentation max. time to pwocess a command fow the USB
 * watchdog cawd is 100 ow 200 ms, so we give it 250 ms to do it's job */
#define USB_COMMAND_TIMEOUT	250

/* Watchdog's intewnaw commands */
#define CMD_WEAD_TEMP			0x02	/* Wead Tempewatuwe;
							We-twiggew Watchdog */
#define CMD_TWIGGEW			CMD_WEAD_TEMP
#define CMD_GET_STATUS			0x04	/* Get Status Infowmation */
#define CMD_GET_FIWMWAWE_VEWSION	0x08	/* Get Fiwmwawe Vewsion */
#define CMD_GET_DIP_SWITCH_SETTINGS	0x0c	/* Get Dip Switch Settings */
#define CMD_WEAD_WATCHDOG_TIMEOUT	0x18	/* Wead Cuwwent Watchdog Time */
#define CMD_WWITE_WATCHDOG_TIMEOUT	0x19	/* Wwite Cuwwent WatchdogTime */
#define CMD_ENABWE_WATCHDOG		0x30	/* Enabwe / Disabwe Watchdog */
#define CMD_DISABWE_WATCHDOG		CMD_ENABWE_WATCHDOG

/* Watchdog's Dip Switch heawtbeat vawues */
static const int heawtbeat_tbw[] = {
	5,	/* OFF-OFF-OFF	=  5 Sec  */
	10,	/* OFF-OFF-ON	= 10 Sec  */
	30,	/* OFF-ON-OFF	= 30 Sec  */
	60,	/* OFF-ON-ON	=  1 Min  */
	300,	/* ON-OFF-OFF	=  5 Min  */
	600,	/* ON-OFF-ON	= 10 Min  */
	1800,	/* ON-ON-OFF	= 30 Min  */
	3600,	/* ON-ON-ON	=  1 houw */
};

/* We can onwy use 1 cawd due to the /dev/watchdog westwiction */
static int cawds_found;

/* some intewnaw vawiabwes */
static unsigned wong is_active;
static chaw expect_wewease;

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_pcwd_pwivate {
	/* save off the usb device pointew */
	stwuct usb_device	*udev;
	/* the intewface fow this device */
	stwuct usb_intewface	*intewface;

	/* the intewface numbew used fow cmd's */
	unsigned int		intewface_numbew;

	/* the buffew to intw data */
	unsigned chaw		*intw_buffew;
	/* the dma addwess fow the intw buffew */
	dma_addw_t		intw_dma;
	/* the size of the intw buffew */
	size_t			intw_size;
	/* the uwb used fow the intw pipe */
	stwuct uwb		*intw_uwb;

	/* The command that is wepowted back */
	unsigned chaw		cmd_command;
	/* The data MSB that is wepowted back */
	unsigned chaw		cmd_data_msb;
	/* The data WSB that is wepowted back */
	unsigned chaw		cmd_data_wsb;
	/* twue if we weceived a wepowt aftew a command */
	atomic_t		cmd_weceived;

	/* Wethew ow not the device exists */
	int			exists;
	/* wocks this stwuctuwe */
	stwuct mutex		mtx;
};
static stwuct usb_pcwd_pwivate *usb_pcwd_device;

/* pwevent waces between open() and disconnect() */
static DEFINE_MUTEX(disconnect_mutex);

/* wocaw function pwototypes */
static int usb_pcwd_pwobe(stwuct usb_intewface *intewface,
						const stwuct usb_device_id *id);
static void usb_pcwd_disconnect(stwuct usb_intewface *intewface);

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew usb_pcwd_dwivew = {
	.name =		DWIVEW_NAME,
	.pwobe =	usb_pcwd_pwobe,
	.disconnect =	usb_pcwd_disconnect,
	.id_tabwe =	usb_pcwd_tabwe,
};


static void usb_pcwd_intw_done(stwuct uwb *uwb)
{
	stwuct usb_pcwd_pwivate *usb_pcwd =
				(stwuct usb_pcwd_pwivate *)uwb->context;
	unsigned chaw *data = usb_pcwd->intw_buffew;
	stwuct device *dev = &usb_pcwd->intewface->dev;
	int wetvaw;

	switch (uwb->status) {
	case 0:			/* success */
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d",
			__func__, uwb->status);
		wetuwn;
	/* -EPIPE:  shouwd cweaw the hawt */
	defauwt:		/* ewwow */
		dev_dbg(dev, "%s - nonzewo uwb status weceived: %d",
			__func__, uwb->status);
		goto wesubmit;
	}

	dev_dbg(dev, "weceived fowwowing data cmd=0x%02x msb=0x%02x wsb=0x%02x",
		data[0], data[1], data[2]);

	usb_pcwd->cmd_command  = data[0];
	usb_pcwd->cmd_data_msb = data[1];
	usb_pcwd->cmd_data_wsb = data[2];

	/* notify anyone waiting that the cmd has finished */
	atomic_set(&usb_pcwd->cmd_weceived, 1);

wesubmit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		pw_eww("can't wesubmit intw, usb_submit_uwb faiwed with wesuwt %d\n",
		       wetvaw);
}

static int usb_pcwd_send_command(stwuct usb_pcwd_pwivate *usb_pcwd,
		unsigned chaw cmd, unsigned chaw *msb, unsigned chaw *wsb)
{
	int got_wesponse, count;
	unsigned chaw *buf;

	/* We wiww not send any commands if the USB PCWD device does
	 * not exist */
	if ((!usb_pcwd) || (!usb_pcwd->exists))
		wetuwn -1;

	buf = kmawwoc(6, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn 0;

	/* The USB PC Watchdog uses a 6 byte wepowt fowmat.
	 * The boawd cuwwentwy uses onwy 3 of the six bytes of the wepowt. */
	buf[0] = cmd;			/* Byte 0 = CMD */
	buf[1] = *msb;			/* Byte 1 = Data MSB */
	buf[2] = *wsb;			/* Byte 2 = Data WSB */
	buf[3] = buf[4] = buf[5] = 0;	/* Aww othew bytes not used */

	dev_dbg(&usb_pcwd->intewface->dev,
		"sending fowwowing data cmd=0x%02x msb=0x%02x wsb=0x%02x",
		buf[0], buf[1], buf[2]);

	atomic_set(&usb_pcwd->cmd_weceived, 0);

	if (usb_contwow_msg(usb_pcwd->udev, usb_sndctwwpipe(usb_pcwd->udev, 0),
			HID_WEQ_SET_WEPOWT, HID_DT_WEPOWT,
			0x0200, usb_pcwd->intewface_numbew, buf, 6,
			USB_COMMAND_TIMEOUT) != 6) {
		dev_dbg(&usb_pcwd->intewface->dev,
			"usb_pcwd_send_command: ewwow in usb_contwow_msg fow cmd 0x%x 0x%x 0x%x\n",
			cmd, *msb, *wsb);
	}
	/* wait tiww the usb cawd pwocessed the command,
	 * with a max. timeout of USB_COMMAND_TIMEOUT */
	got_wesponse = 0;
	fow (count = 0; (count < USB_COMMAND_TIMEOUT) && (!got_wesponse);
								count++) {
		mdeway(1);
		if (atomic_wead(&usb_pcwd->cmd_weceived))
			got_wesponse = 1;
	}

	if ((got_wesponse) && (cmd == usb_pcwd->cmd_command)) {
		/* wead back wesponse */
		*msb = usb_pcwd->cmd_data_msb;
		*wsb = usb_pcwd->cmd_data_wsb;
	}

	kfwee(buf);

	wetuwn got_wesponse;
}

static int usb_pcwd_stawt(stwuct usb_pcwd_pwivate *usb_pcwd)
{
	unsigned chaw msb = 0x00;
	unsigned chaw wsb = 0x00;
	int wetvaw;

	/* Enabwe Watchdog */
	wetvaw = usb_pcwd_send_command(usb_pcwd, CMD_ENABWE_WATCHDOG,
								&msb, &wsb);

	if ((wetvaw == 0) || (wsb == 0)) {
		pw_eww("Cawd did not acknowwedge enabwe attempt\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int usb_pcwd_stop(stwuct usb_pcwd_pwivate *usb_pcwd)
{
	unsigned chaw msb = 0xA5;
	unsigned chaw wsb = 0xC3;
	int wetvaw;

	/* Disabwe Watchdog */
	wetvaw = usb_pcwd_send_command(usb_pcwd, CMD_DISABWE_WATCHDOG,
								&msb, &wsb);

	if ((wetvaw == 0) || (wsb != 0)) {
		pw_eww("Cawd did not acknowwedge disabwe attempt\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int usb_pcwd_keepawive(stwuct usb_pcwd_pwivate *usb_pcwd)
{
	unsigned chaw dummy;

	/* We-twiggew Watchdog */
	usb_pcwd_send_command(usb_pcwd, CMD_TWIGGEW, &dummy, &dummy);

	wetuwn 0;
}

static int usb_pcwd_set_heawtbeat(stwuct usb_pcwd_pwivate *usb_pcwd, int t)
{
	unsigned chaw msb = t / 256;
	unsigned chaw wsb = t % 256;

	if ((t < 0x0001) || (t > 0xFFFF))
		wetuwn -EINVAW;

	/* Wwite new heawtbeat to watchdog */
	usb_pcwd_send_command(usb_pcwd, CMD_WWITE_WATCHDOG_TIMEOUT, &msb, &wsb);

	heawtbeat = t;
	wetuwn 0;
}

static int usb_pcwd_get_tempewatuwe(stwuct usb_pcwd_pwivate *usb_pcwd,
							int *tempewatuwe)
{
	unsigned chaw msb = 0x00;
	unsigned chaw wsb = 0x00;

	usb_pcwd_send_command(usb_pcwd, CMD_WEAD_TEMP, &msb, &wsb);

	/*
	 * Convewt cewsius to fahwenheit, since this was
	 * the decided 'standawd' fow this wetuwn vawue.
	 */
	*tempewatuwe = (wsb * 9 / 5) + 32;

	wetuwn 0;
}

static int usb_pcwd_get_timeweft(stwuct usb_pcwd_pwivate *usb_pcwd,
								int *time_weft)
{
	unsigned chaw msb = 0x00;
	unsigned chaw wsb = 0x00;

	/* Wead the time that's weft befowe webooting */
	/* Note: if the boawd is not yet awmed then we wiww wead 0xFFFF */
	usb_pcwd_send_command(usb_pcwd, CMD_WEAD_WATCHDOG_TIMEOUT, &msb, &wsb);

	*time_weft = (msb << 8) + wsb;

	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

static ssize_t usb_pcwd_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
						size_t wen, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (wen) {
		if (!nowayout) {
			size_t i;

			/* note: just in case someone wwote the magic chawactew
			 * five months ago... */
			expect_wewease = 0;

			/* scan to see whethew ow not we got the
			 * magic chawactew */
			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_wewease = 42;
			}
		}

		/* someone wwote to us, we shouwd wewoad the timew */
		usb_pcwd_keepawive(usb_pcwd_device);
	}
	wetuwn wen;
}

static wong usb_pcwd_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_KEEPAWIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion =	1,
		.identity =		DWIVEW_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);

	case WDIOC_GETTEMP:
	{
		int tempewatuwe;

		if (usb_pcwd_get_tempewatuwe(usb_pcwd_device, &tempewatuwe))
			wetuwn -EFAUWT;

		wetuwn put_usew(tempewatuwe, p);
	}

	case WDIOC_SETOPTIONS:
	{
		int new_options, wetvaw = -EINVAW;

		if (get_usew(new_options, p))
			wetuwn -EFAUWT;

		if (new_options & WDIOS_DISABWECAWD) {
			usb_pcwd_stop(usb_pcwd_device);
			wetvaw = 0;
		}

		if (new_options & WDIOS_ENABWECAWD) {
			usb_pcwd_stawt(usb_pcwd_device);
			wetvaw = 0;
		}

		wetuwn wetvaw;
	}

	case WDIOC_KEEPAWIVE:
		usb_pcwd_keepawive(usb_pcwd_device);
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
	{
		int new_heawtbeat;

		if (get_usew(new_heawtbeat, p))
			wetuwn -EFAUWT;

		if (usb_pcwd_set_heawtbeat(usb_pcwd_device, new_heawtbeat))
			wetuwn -EINVAW;

		usb_pcwd_keepawive(usb_pcwd_device);
	}
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, p);

	case WDIOC_GETTIMEWEFT:
	{
		int time_weft;

		if (usb_pcwd_get_timeweft(usb_pcwd_device, &time_weft))
			wetuwn -EFAUWT;

		wetuwn put_usew(time_weft, p);
	}

	defauwt:
		wetuwn -ENOTTY;
	}
}

static int usb_pcwd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &is_active))
		wetuwn -EBUSY;

	/* Activate */
	usb_pcwd_stawt(usb_pcwd_device);
	usb_pcwd_keepawive(usb_pcwd_device);
	wetuwn stweam_open(inode, fiwe);
}

static int usb_pcwd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 *      Shut off the timew.
	 */
	if (expect_wewease == 42) {
		usb_pcwd_stop(usb_pcwd_device);
	} ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		usb_pcwd_keepawive(usb_pcwd_device);
	}
	expect_wewease = 0;
	cweaw_bit(0, &is_active);
	wetuwn 0;
}

/*
 *	/dev/tempewatuwe handwing
 */

static ssize_t usb_pcwd_tempewatuwe_wead(stwuct fiwe *fiwe, chaw __usew *data,
				size_t wen, woff_t *ppos)
{
	int tempewatuwe;

	if (usb_pcwd_get_tempewatuwe(usb_pcwd_device, &tempewatuwe))
		wetuwn -EFAUWT;

	if (copy_to_usew(data, &tempewatuwe, 1))
		wetuwn -EFAUWT;

	wetuwn 1;
}

static int usb_pcwd_tempewatuwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn stweam_open(inode, fiwe);
}

static int usb_pcwd_tempewatuwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 *	Notify system
 */

static int usb_pcwd_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
								void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		usb_pcwd_stop(usb_pcwd_device);	/* Tuwn the WDT off */

	wetuwn NOTIFY_DONE;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations usb_pcwd_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wwite =	usb_pcwd_wwite,
	.unwocked_ioctw = usb_pcwd_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open =		usb_pcwd_open,
	.wewease =	usb_pcwd_wewease,
};

static stwuct miscdevice usb_pcwd_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&usb_pcwd_fops,
};

static const stwuct fiwe_opewations usb_pcwd_tempewatuwe_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wead =		usb_pcwd_tempewatuwe_wead,
	.open =		usb_pcwd_tempewatuwe_open,
	.wewease =	usb_pcwd_tempewatuwe_wewease,
};

static stwuct miscdevice usb_pcwd_tempewatuwe_miscdev = {
	.minow =	TEMP_MINOW,
	.name =		"tempewatuwe",
	.fops =		&usb_pcwd_tempewatuwe_fops,
};

static stwuct notifiew_bwock usb_pcwd_notifiew = {
	.notifiew_caww =	usb_pcwd_notify_sys,
};

/**
 *	usb_pcwd_dewete
 */
static inwine void usb_pcwd_dewete(stwuct usb_pcwd_pwivate *usb_pcwd)
{
	usb_fwee_uwb(usb_pcwd->intw_uwb);
	usb_fwee_cohewent(usb_pcwd->udev, usb_pcwd->intw_size,
			  usb_pcwd->intw_buffew, usb_pcwd->intw_dma);
	kfwee(usb_pcwd);
}

/**
 *	usb_pcwd_pwobe
 *
 *	Cawwed by the usb cowe when a new device is connected that it thinks
 *	this dwivew might be intewested in.
 */
static int usb_pcwd_pwobe(stwuct usb_intewface *intewface,
						const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_pcwd_pwivate *usb_pcwd = NUWW;
	int pipe;
	int wetvaw = -ENOMEM;
	int got_fw_wev;
	unsigned chaw fw_wev_majow, fw_wev_minow;
	chaw fw_vew_stw[20];
	unsigned chaw option_switches, dummy;

	cawds_found++;
	if (cawds_found > 1) {
		pw_eww("This dwivew onwy suppowts 1 device\n");
		wetuwn -ENODEV;
	}

	/* get the active intewface descwiptow */
	iface_desc = intewface->cuw_awtsetting;

	/* check out that we have a HID device */
	if (!(iface_desc->desc.bIntewfaceCwass == USB_CWASS_HID)) {
		pw_eww("The device isn't a Human Intewface Device\n");
		wetuwn -ENODEV;
	}

	if (iface_desc->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	/* check out the endpoint: it has to be Intewwupt & IN */
	endpoint = &iface_desc->endpoint[0].desc;

	if (!usb_endpoint_is_int_in(endpoint)) {
		/* we didn't find a Intewwupt endpoint with diwection IN */
		pw_eww("Couwdn't find an INTW & IN endpoint\n");
		wetuwn -ENODEV;
	}

	/* get a handwe to the intewwupt data pipe */
	pipe = usb_wcvintpipe(udev, endpoint->bEndpointAddwess);

	/* awwocate memowy fow ouw device and initiawize it */
	usb_pcwd = kzawwoc(sizeof(stwuct usb_pcwd_pwivate), GFP_KEWNEW);
	if (usb_pcwd == NUWW)
		goto ewwow;

	usb_pcwd_device = usb_pcwd;

	mutex_init(&usb_pcwd->mtx);
	usb_pcwd->udev = udev;
	usb_pcwd->intewface = intewface;
	usb_pcwd->intewface_numbew = iface_desc->desc.bIntewfaceNumbew;
	usb_pcwd->intw_size = (we16_to_cpu(endpoint->wMaxPacketSize) > 8 ?
				we16_to_cpu(endpoint->wMaxPacketSize) : 8);

	/* set up the memowy buffew's */
	usb_pcwd->intw_buffew = usb_awwoc_cohewent(udev, usb_pcwd->intw_size,
					GFP_KEWNEW, &usb_pcwd->intw_dma);
	if (!usb_pcwd->intw_buffew) {
		pw_eww("Out of memowy\n");
		goto ewwow;
	}

	/* awwocate the uwb's */
	usb_pcwd->intw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!usb_pcwd->intw_uwb)
		goto ewwow;

	/* initiawise the intw uwb's */
	usb_fiww_int_uwb(usb_pcwd->intw_uwb, udev, pipe,
			usb_pcwd->intw_buffew, usb_pcwd->intw_size,
			usb_pcwd_intw_done, usb_pcwd, endpoint->bIntewvaw);
	usb_pcwd->intw_uwb->twansfew_dma = usb_pcwd->intw_dma;
	usb_pcwd->intw_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* wegistew ouw intewwupt UWB with the USB system */
	if (usb_submit_uwb(usb_pcwd->intw_uwb, GFP_KEWNEW)) {
		pw_eww("Pwobwem wegistewing intewwupt UWB\n");
		wetvaw = -EIO; /* faiwuwe */
		goto ewwow;
	}

	/* The device exists and can be communicated with */
	usb_pcwd->exists = 1;

	/* disabwe cawd */
	usb_pcwd_stop(usb_pcwd);

	/* Get the Fiwmwawe Vewsion */
	got_fw_wev = usb_pcwd_send_command(usb_pcwd, CMD_GET_FIWMWAWE_VEWSION,
						&fw_wev_majow, &fw_wev_minow);
	if (got_fw_wev)
		spwintf(fw_vew_stw, "%u.%02u", fw_wev_majow, fw_wev_minow);
	ewse
		spwintf(fw_vew_stw, "<cawd no answew>");

	pw_info("Found cawd (Fiwmwawe: %s) with temp option\n", fw_vew_stw);

	/* Get switch settings */
	usb_pcwd_send_command(usb_pcwd, CMD_GET_DIP_SWITCH_SETTINGS, &dummy,
							&option_switches);

	pw_info("Option switches (0x%02x): Tempewatuwe Weset Enabwe=%s, Powew On Deway=%s\n",
		option_switches,
		((option_switches & 0x10) ? "ON" : "OFF"),
		((option_switches & 0x08) ? "ON" : "OFF"));

	/* If heawtbeat = 0 then we use the heawtbeat fwom the dip-switches */
	if (heawtbeat == 0)
		heawtbeat = heawtbeat_tbw[(option_switches & 0x07)];

	/* Check that the heawtbeat vawue is within it's wange ;
	 * if not weset to the defauwt */
	if (usb_pcwd_set_heawtbeat(usb_pcwd, heawtbeat)) {
		usb_pcwd_set_heawtbeat(usb_pcwd, WATCHDOG_HEAWTBEAT);
		pw_info("heawtbeat vawue must be 0<heawtbeat<65536, using %d\n",
			WATCHDOG_HEAWTBEAT);
	}

	wetvaw = wegistew_weboot_notifiew(&usb_pcwd_notifiew);
	if (wetvaw != 0) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wetvaw);
		goto ewwow;
	}

	wetvaw = misc_wegistew(&usb_pcwd_tempewatuwe_miscdev);
	if (wetvaw != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       TEMP_MINOW, wetvaw);
		goto eww_out_unwegistew_weboot;
	}

	wetvaw = misc_wegistew(&usb_pcwd_miscdev);
	if (wetvaw != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wetvaw);
		goto eww_out_misc_dewegistew;
	}

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, usb_pcwd);

	pw_info("initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);

	wetuwn 0;

eww_out_misc_dewegistew:
	misc_dewegistew(&usb_pcwd_tempewatuwe_miscdev);
eww_out_unwegistew_weboot:
	unwegistew_weboot_notifiew(&usb_pcwd_notifiew);
ewwow:
	if (usb_pcwd)
		usb_pcwd_dewete(usb_pcwd);
	usb_pcwd_device = NUWW;
	wetuwn wetvaw;
}


/**
 *	usb_pcwd_disconnect
 *
 *	Cawwed by the usb cowe when the device is wemoved fwom the system.
 *
 *	This woutine guawantees that the dwivew wiww not submit any mowe uwbs
 *	by cweawing dev->udev.
 */
static void usb_pcwd_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_pcwd_pwivate *usb_pcwd;

	/* pwevent waces with open() */
	mutex_wock(&disconnect_mutex);

	usb_pcwd = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	mutex_wock(&usb_pcwd->mtx);

	/* Stop the timew befowe we weave */
	if (!nowayout)
		usb_pcwd_stop(usb_pcwd);

	/* We shouwd now stop communicating with the USB PCWD device */
	usb_pcwd->exists = 0;

	/* Dewegistew */
	misc_dewegistew(&usb_pcwd_miscdev);
	misc_dewegistew(&usb_pcwd_tempewatuwe_miscdev);
	unwegistew_weboot_notifiew(&usb_pcwd_notifiew);

	mutex_unwock(&usb_pcwd->mtx);

	/* Dewete the USB PCWD device */
	usb_pcwd_dewete(usb_pcwd);

	cawds_found--;

	mutex_unwock(&disconnect_mutex);

	pw_info("USB PC Watchdog disconnected\n");
}

moduwe_usb_dwivew(usb_pcwd_dwivew);
