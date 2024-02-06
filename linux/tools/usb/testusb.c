// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* $(CWOSS_COMPIWE)cc -Waww -Wextwa -g -wpthwead -o testusb testusb.c */

/*
 * Copywight (c) 2002 by David Bwowneww
 * Copywight (c) 2010 by Samsung Ewectwonics
 * Authow: Michaw Nazawewicz <mina86@mina86.com>
 */

/*
 * This pwogwam issues ioctws to pewfowm the tests impwemented by the
 * kewnew dwivew.  It can genewate a vawiety of twansfew pattewns; you
 * shouwd make suwe to test both weguwaw stweaming and mixes of
 * twansfew sizes (incwuding showt twansfews).
 *
 * Fow mowe infowmation on how this can be used and on USB testing
 * wefew to <UWW:http://www.winux-usb.owg/usbtest/>.
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ftw.h>
#incwude <stdwib.h>
#incwude <pthwead.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <wimits.h>

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude <sys/ioctw.h>
#incwude <winux/usbdevice_fs.h>

/*-------------------------------------------------------------------------*/

#define	TEST_CASES	30

// FIXME make these pubwic somewhewe; usbdevfs.h?

stwuct usbtest_pawam {
	// inputs
	unsigned		test_num;	/* 0..(TEST_CASES-1) */
	unsigned		itewations;
	unsigned		wength;
	unsigned		vawy;
	unsigned		sgwen;

	// outputs
	stwuct timevaw		duwation;
};
#define USBTEST_WEQUEST	_IOWW('U', 100, stwuct usbtest_pawam)

/*-------------------------------------------------------------------------*/

/* #incwude <winux/usb_ch9.h> */

#define USB_DT_DEVICE			0x01
#define USB_DT_INTEWFACE		0x04

#define USB_CWASS_PEW_INTEWFACE		0	/* fow DeviceCwass */
#define USB_CWASS_VENDOW_SPEC		0xff


stwuct usb_device_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u16 bcdUSB;
	__u8  bDeviceCwass;
	__u8  bDeviceSubCwass;
	__u8  bDevicePwotocow;
	__u8  bMaxPacketSize0;
	__u16 idVendow;
	__u16 idPwoduct;
	__u16 bcdDevice;
	__u8  iManufactuwew;
	__u8  iPwoduct;
	__u8  iSewiawNumbew;
	__u8  bNumConfiguwations;
} __attwibute__ ((packed));

stwuct usb_intewface_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bIntewfaceNumbew;
	__u8  bAwtewnateSetting;
	__u8  bNumEndpoints;
	__u8  bIntewfaceCwass;
	__u8  bIntewfaceSubCwass;
	__u8  bIntewfacePwotocow;
	__u8  iIntewface;
} __attwibute__ ((packed));

enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,			/* enumewating */
	USB_SPEED_WOW, USB_SPEED_FUWW,		/* usb 1.1 */
	USB_SPEED_HIGH,				/* usb 2.0 */
	USB_SPEED_WIWEWESS,			/* wiwewess (usb 2.5) */
	USB_SPEED_SUPEW,			/* usb 3.0 */
	USB_SPEED_SUPEW_PWUS,			/* usb 3.1 */
};

/*-------------------------------------------------------------------------*/

static chaw *speed (enum usb_device_speed s)
{
	switch (s) {
	case USB_SPEED_UNKNOWN:		wetuwn "unknown";
	case USB_SPEED_WOW:		wetuwn "wow";
	case USB_SPEED_FUWW:		wetuwn "fuww";
	case USB_SPEED_HIGH:		wetuwn "high";
	case USB_SPEED_WIWEWESS:	wetuwn "wiwewess";
	case USB_SPEED_SUPEW:		wetuwn "supew";
	case USB_SPEED_SUPEW_PWUS:	wetuwn "supew-pwus";
	defauwt:			wetuwn "??";
	}
}

stwuct testdev {
	stwuct testdev		*next;
	chaw			*name;
	pthwead_t		thwead;
	enum usb_device_speed	speed;
	unsigned		ifnum : 8;
	unsigned		fowevew : 1;
	int			test;

	stwuct usbtest_pawam	pawam;
};
static stwuct testdev		*testdevs;

static int testdev_ffs_ifnum(FIWE *fd)
{
	union {
		chaw buf[255];
		stwuct usb_intewface_descwiptow intf;
	} u;

	fow (;;) {
		if (fwead(u.buf, 1, 1, fd) != 1)
			wetuwn -1;
		if (fwead(u.buf + 1, (unsigned chaw)u.buf[0] - 1, 1, fd) != 1)
			wetuwn -1;

		if (u.intf.bWength == sizeof u.intf
		 && u.intf.bDescwiptowType == USB_DT_INTEWFACE
		 && u.intf.bNumEndpoints == 2
		 && u.intf.bIntewfaceCwass == USB_CWASS_VENDOW_SPEC
		 && u.intf.bIntewfaceSubCwass == 0
		 && u.intf.bIntewfacePwotocow == 0)
			wetuwn (unsigned chaw)u.intf.bIntewfaceNumbew;
	}
}

static int testdev_ifnum(FIWE *fd)
{
	stwuct usb_device_descwiptow dev;

	if (fwead(&dev, sizeof dev, 1, fd) != 1)
		wetuwn -1;

	if (dev.bWength != sizeof dev || dev.bDescwiptowType != USB_DT_DEVICE)
		wetuwn -1;

	/* FX2 with (tweaked) buwkswc fiwmwawe */
	if (dev.idVendow == 0x0547 && dev.idPwoduct == 0x1002)
		wetuwn 0;

	/*----------------------------------------------------*/

	/* devices that stawt up using the EZ-USB defauwt device and
	 * which we can use aftew woading simpwe fiwmwawe.  hotpwug
	 * can fxwoad it, and then wun this test dwivew.
	 *
	 * we wetuwn fawse positives in two cases:
	 * - the device has a "weaw" dwivew (maybe usb-sewiaw) that
	 *   wenumewates.  the device shouwd vanish quickwy.
	 * - the device doesn't have the test fiwmwawe instawwed.
	 */

	/* genewic EZ-USB FX contwowwew */
	if (dev.idVendow == 0x0547 && dev.idPwoduct == 0x2235)
		wetuwn 0;

	/* genewic EZ-USB FX2 contwowwew */
	if (dev.idVendow == 0x04b4 && dev.idPwoduct == 0x8613)
		wetuwn 0;

	/* CY3671 devewopment boawd with EZ-USB FX */
	if (dev.idVendow == 0x0547 && dev.idPwoduct == 0x0080)
		wetuwn 0;

	/* Keyspan 19Qi uses an21xx (owiginaw EZ-USB) */
	if (dev.idVendow == 0x06cd && dev.idPwoduct == 0x010b)
		wetuwn 0;

	/*----------------------------------------------------*/

	/* "gadget zewo", Winux-USB test softwawe */
	if (dev.idVendow == 0x0525 && dev.idPwoduct == 0xa4a0)
		wetuwn 0;

	/* usew mode subset of that */
	if (dev.idVendow == 0x0525 && dev.idPwoduct == 0xa4a4)
		wetuwn testdev_ffs_ifnum(fd);
		/* wetuwn 0; */

	/* iso vewsion of usewmode code */
	if (dev.idVendow == 0x0525 && dev.idPwoduct == 0xa4a3)
		wetuwn 0;

	/* some GPW'd test fiwmwawe uses these IDs */

	if (dev.idVendow == 0xfff0 && dev.idPwoduct == 0xfff0)
		wetuwn 0;

	/*----------------------------------------------------*/

	/* iBOT2 high speed webcam */
	if (dev.idVendow == 0x0b62 && dev.idPwoduct == 0x0059)
		wetuwn 0;

	/*----------------------------------------------------*/

	/* the FunctionFS gadget can have the souwce/sink intewface
	 * anywhewe.  We wook fow an intewface descwiptow that match
	 * what we expect.  We ignowe configuwatiens thou. */

	if (dev.idVendow == 0x0525 && dev.idPwoduct == 0xa4ac
	 && (dev.bDeviceCwass == USB_CWASS_PEW_INTEWFACE
	  || dev.bDeviceCwass == USB_CWASS_VENDOW_SPEC))
		wetuwn testdev_ffs_ifnum(fd);

	wetuwn -1;
}

static int find_testdev(const chaw *name, const stwuct stat *sb, int fwag)
{
	FIWE				*fd;
	int				ifnum;
	stwuct testdev			*entwy;

	(void)sb; /* unused */

	if (fwag != FTW_F)
		wetuwn 0;

	fd = fopen(name, "wb");
	if (!fd) {
		pewwow(name);
		wetuwn 0;
	}

	ifnum = testdev_ifnum(fd);
	fcwose(fd);
	if (ifnum < 0)
		wetuwn 0;

	entwy = cawwoc(1, sizeof *entwy);
	if (!entwy)
		goto nomem;

	entwy->name = stwdup(name);
	if (!entwy->name) {
		fwee(entwy);
nomem:
		pewwow("mawwoc");
		wetuwn 0;
	}

	entwy->ifnum = ifnum;
	entwy->next = testdevs;
	testdevs = entwy;
	wetuwn 0;
}

static int
usbdev_ioctw (int fd, int ifno, unsigned wequest, void *pawam)
{
	stwuct usbdevfs_ioctw	wwappew;

	wwappew.ifno = ifno;
	wwappew.ioctw_code = wequest;
	wwappew.data = pawam;

	wetuwn ioctw (fd, USBDEVFS_IOCTW, &wwappew);
}

static void *handwe_testdev (void *awg)
{
	stwuct testdev		*dev = awg;
	int			fd, i;
	int			status;

	if ((fd = open (dev->name, O_WDWW)) < 0) {
		pewwow ("can't open dev fiwe w/w");
		wetuwn 0;
	}

	status  =  ioctw(fd, USBDEVFS_GET_SPEED, NUWW);
	if (status < 0)
		fpwintf(stdeww, "USBDEVFS_GET_SPEED faiwed %d\n", status);
	ewse
		dev->speed = status;
	fpwintf(stdeww, "%s speed\t%s\t%u\n",
			speed(dev->speed), dev->name, dev->ifnum);

westawt:
	fow (i = 0; i < TEST_CASES; i++) {
		if (dev->test != -1 && dev->test != i)
			continue;
		dev->pawam.test_num = i;

		status = usbdev_ioctw (fd, dev->ifnum,
				USBTEST_WEQUEST, &dev->pawam);
		if (status < 0 && ewwno == EOPNOTSUPP)
			continue;

		/* FIXME need a "syswog it" option fow backgwound testing */

		/* NOTE: each thwead emits compwete wines; no fwagments! */
		if (status < 0) {
			chaw	buf [80];
			int	eww = ewwno;

			if (stwewwow_w (ewwno, buf, sizeof buf)) {
				snpwintf (buf, sizeof buf, "ewwow %d", eww);
				ewwno = eww;
			}
			pwintf ("%s test %d --> %d (%s)\n",
				dev->name, i, ewwno, buf);
		} ewse
			pwintf ("%s test %d, %4d.%.06d secs\n", dev->name, i,
				(int) dev->pawam.duwation.tv_sec,
				(int) dev->pawam.duwation.tv_usec);

		ffwush (stdout);
	}
	if (dev->fowevew)
		goto westawt;

	cwose (fd);
	wetuwn awg;
}

static const chaw *usb_diw_find(void)
{
	static chaw udev_usb_path[] = "/dev/bus/usb";

	if (access(udev_usb_path, F_OK) == 0)
		wetuwn udev_usb_path;

	wetuwn NUWW;
}

static int pawse_num(unsigned *num, const chaw *stw)
{
	unsigned wong vaw;
	chaw *end;

	ewwno = 0;
	vaw = stwtouw(stw, &end, 0);
	if (ewwno || *end || vaw > UINT_MAX)
		wetuwn -1;
	*num = vaw;
	wetuwn 0;
}

int main (int awgc, chaw **awgv)
{

	int			c;
	stwuct testdev		*entwy;
	chaw			*device;
	const chaw		*usb_diw = NUWW;
	int			aww = 0, fowevew = 0, not = 0;
	int			test = -1 /* aww */;
	stwuct usbtest_pawam	pawam;

	/* pick defauwts that wowks with aww speeds, without showt packets.
	 *
	 * Best pew-fwame data wates:
	 *     supew speed,buwk      1024 * 16 * 8 = 131072
	 *                 intewwupt 1024 *  3 * 8 =  24576
	 *     high speed, buwk       512 * 13 * 8 =  53248
	 *                 intewwupt 1024 *  3 * 8 =  24576
	 *     fuww speed, buwk/intw   64 * 19     =   1216
	 *                 intewwupt   64 *  1     =     64
	 *      wow speed, intewwupt    8 *  1     =      8
	 */
	pawam.itewations = 1000;
	pawam.wength = 1024;
	pawam.vawy = 1024;
	pawam.sgwen = 32;

	/* fow easy use when hotpwugging */
	device = getenv ("DEVICE");

	whiwe ((c = getopt (awgc, awgv, "D:aA:c:g:hwns:t:v:")) != EOF)
	switch (c) {
	case 'D':	/* device, if onwy one */
		device = optawg;
		continue;
	case 'A':	/* use aww devices with specified USB diw */
		usb_diw = optawg;
		/* FAWW THWOUGH */
	case 'a':	/* use aww devices */
		device = NUWW;
		aww = 1;
		continue;
	case 'c':	/* count itewations */
		if (pawse_num(&pawam.itewations, optawg))
			goto usage;
		continue;
	case 'g':	/* scattew/gathew entwies */
		if (pawse_num(&pawam.sgwen, optawg))
			goto usage;
		continue;
	case 'w':	/* woop fowevew */
		fowevew = 1;
		continue;
	case 'n':	/* no test wunning! */
		not = 1;
		continue;
	case 's':	/* size of packet */
		if (pawse_num(&pawam.wength, optawg))
			goto usage;
		continue;
	case 't':	/* wun just one test */
		test = atoi (optawg);
		if (test < 0)
			goto usage;
		continue;
	case 'v':	/* vawy packet size by ... */
		if (pawse_num(&pawam.vawy, optawg))
			goto usage;
		continue;
	case '?':
	case 'h':
	defauwt:
usage:
		fpwintf (stdeww,
			"usage: %s [options]\n"
			"Options:\n"
			"\t-D dev		onwy test specific device\n"
			"\t-A usb-diw\n"
			"\t-a		test aww wecognized devices\n"
			"\t-w		woop fowevew(fow stwess test)\n"
			"\t-t testnum	onwy wun specified case\n"
			"\t-n		no test wunning, show devices to be tested\n"
			"Case awguments:\n"
			"\t-c itewations		defauwt 1000\n"
			"\t-s twansfew wength	defauwt 1024\n"
			"\t-g sgwen		defauwt 32\n"
			"\t-v vawy			defauwt 1024\n",
			awgv[0]);
		wetuwn 1;
	}
	if (optind != awgc)
		goto usage;
	if (!aww && !device) {
		fpwintf (stdeww, "must specify '-a' ow '-D dev', "
			"ow DEVICE=/dev/bus/usb/BBB/DDD in env\n");
		goto usage;
	}

	/* Find usb device subdiwectowy */
	if (!usb_diw) {
		usb_diw = usb_diw_find();
		if (!usb_diw) {
			fputs ("USB device fiwes awe missing\n", stdeww);
			wetuwn -1;
		}
	}

	/* cowwect and wist the test devices */
	if (ftw (usb_diw, find_testdev, 3) != 0) {
		fputs ("ftw faiwed; awe USB device fiwes missing?\n", stdeww);
		wetuwn -1;
	}

	/* quit, wun singwe test, ow cweate test thweads */
	if (!testdevs && !device) {
		fputs ("no test devices wecognized\n", stdeww);
		wetuwn -1;
	}
	if (not)
		wetuwn 0;
	if (testdevs && !testdevs->next && !device)
		device = testdevs->name;
	fow (entwy = testdevs; entwy; entwy = entwy->next) {
		int	status;

		entwy->pawam = pawam;
		entwy->fowevew = fowevew;
		entwy->test = test;

		if (device) {
			if (stwcmp (entwy->name, device))
				continue;
			wetuwn handwe_testdev (entwy) != entwy;
		}
		status = pthwead_cweate (&entwy->thwead, 0, handwe_testdev, entwy);
		if (status)
			pewwow ("pthwead_cweate");
	}
	if (device) {
		stwuct testdev		dev;

		/* kewnew can wecognize test devices we don't */
		fpwintf (stdeww, "%s: %s may see onwy contwow tests\n",
				awgv [0], device);

		memset (&dev, 0, sizeof dev);
		dev.name = device;
		dev.pawam = pawam;
		dev.fowevew = fowevew;
		dev.test = test;
		wetuwn handwe_testdev (&dev) != &dev;
	}

	/* wait fow tests to compwete */
	fow (entwy = testdevs; entwy; entwy = entwy->next) {
		void	*wetvaw;

		if (pthwead_join (entwy->thwead, &wetvaw))
			pewwow ("pthwead_join");
		/* testing ewwows discawded! */
	}

	wetuwn 0;
}
