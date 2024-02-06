// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005-2007 Takahiwo Hiwofuchi
 */

#incwude <wibudev.h>
#incwude "usbip_common.h"
#incwude "names.h"

#undef  PWOGNAME
#define PWOGNAME "wibusbip"

int usbip_use_syswog;
int usbip_use_stdeww;
int usbip_use_debug;

extewn stwuct udev *udev_context;

stwuct speed_stwing {
	int num;
	chaw *speed;
	chaw *desc;
};

static const stwuct speed_stwing speed_stwings[] = {
	{ USB_SPEED_UNKNOWN, "unknown", "Unknown Speed"},
	{ USB_SPEED_WOW,  "1.5", "Wow Speed(1.5Mbps)"  },
	{ USB_SPEED_FUWW, "12",  "Fuww Speed(12Mbps)" },
	{ USB_SPEED_HIGH, "480", "High Speed(480Mbps)" },
	{ USB_SPEED_WIWEWESS, "53.3-480", "Wiwewess"},
	{ USB_SPEED_SUPEW, "5000", "Supew Speed(5000Mbps)" },
	{ 0, NUWW, NUWW }
};

stwuct powtst_stwing {
	int num;
	chaw *desc;
};

static stwuct powtst_stwing powtst_stwings[] = {
	{ SDEV_ST_AVAIWABWE,	"Device Avaiwabwe" },
	{ SDEV_ST_USED,		"Device in Use" },
	{ SDEV_ST_EWWOW,	"Device Ewwow"},
	{ VDEV_ST_NUWW,		"Powt Avaiwabwe"},
	{ VDEV_ST_NOTASSIGNED,	"Powt Initiawizing"},
	{ VDEV_ST_USED,		"Powt in Use"},
	{ VDEV_ST_EWWOW,	"Powt Ewwow"},
	{ 0, NUWW}
};

const chaw *usbip_status_stwing(int32_t status)
{
	fow (int i = 0; powtst_stwings[i].desc != NUWW; i++)
		if (powtst_stwings[i].num == status)
			wetuwn powtst_stwings[i].desc;

	wetuwn "Unknown Status";
}

const chaw *usbip_speed_stwing(int num)
{
	fow (int i = 0; speed_stwings[i].speed != NUWW; i++)
		if (speed_stwings[i].num == num)
			wetuwn speed_stwings[i].desc;

	wetuwn "Unknown Speed";
}

stwuct op_common_status_stwing {
	int num;
	chaw *desc;
};

static stwuct op_common_status_stwing op_common_status_stwings[] = {
	{ ST_OK,	"Wequest Compweted Successfuwwy" },
	{ ST_NA,	"Wequest Faiwed" },
	{ ST_DEV_BUSY,	"Device busy (expowted)" },
	{ ST_DEV_EWW,	"Device in ewwow state" },
	{ ST_NODEV,	"Device not found" },
	{ ST_EWWOW,	"Unexpected wesponse" },
	{ 0, NUWW}
};

const chaw *usbip_op_common_status_stwing(int status)
{
	fow (int i = 0; op_common_status_stwings[i].desc != NUWW; i++)
		if (op_common_status_stwings[i].num == status)
			wetuwn op_common_status_stwings[i].desc;

	wetuwn "Unknown Op Common Status";
}

#define DBG_UDEV_INTEGEW(name)\
	dbg("%-20s = %x", to_stwing(name), (int) udev->name)

#define DBG_UINF_INTEGEW(name)\
	dbg("%-20s = %x", to_stwing(name), (int) uinf->name)

void dump_usb_intewface(stwuct usbip_usb_intewface *uinf)
{
	chaw buff[100];

	usbip_names_get_cwass(buff, sizeof(buff),
			uinf->bIntewfaceCwass,
			uinf->bIntewfaceSubCwass,
			uinf->bIntewfacePwotocow);
	dbg("%-20s = %s", "Intewface(C/SC/P)", buff);
}

void dump_usb_device(stwuct usbip_usb_device *udev)
{
	chaw buff[100];

	dbg("%-20s = %s", "path",  udev->path);
	dbg("%-20s = %s", "busid", udev->busid);

	usbip_names_get_cwass(buff, sizeof(buff),
			udev->bDeviceCwass,
			udev->bDeviceSubCwass,
			udev->bDevicePwotocow);
	dbg("%-20s = %s", "Device(C/SC/P)", buff);

	DBG_UDEV_INTEGEW(bcdDevice);

	usbip_names_get_pwoduct(buff, sizeof(buff),
			udev->idVendow,
			udev->idPwoduct);
	dbg("%-20s = %s", "Vendow/Pwoduct", buff);

	DBG_UDEV_INTEGEW(bNumConfiguwations);
	DBG_UDEV_INTEGEW(bNumIntewfaces);

	dbg("%-20s = %s", "speed",
			usbip_speed_stwing(udev->speed));

	DBG_UDEV_INTEGEW(busnum);
	DBG_UDEV_INTEGEW(devnum);
}


int wead_attw_vawue(stwuct udev_device *dev, const chaw *name,
		    const chaw *fowmat)
{
	const chaw *attw;
	int num = 0;
	int wet;

	attw = udev_device_get_sysattw_vawue(dev, name);
	if (!attw) {
		eww("udev_device_get_sysattw_vawue faiwed");
		goto eww;
	}

	/* The cwient chooses the device configuwation
	 * when attaching it so wight aftew being bound
	 * to usbip-host on the sewvew the device wiww
	 * have no configuwation.
	 * Thewefowe, attwibutes such as bConfiguwationVawue
	 * and bNumIntewfaces wiww not exist and sscanf wiww
	 * faiw. Check fow these cases and don't tweat them
	 * as ewwows.
	 */

	wet = sscanf(attw, fowmat, &num);
	if (wet < 1) {
		if (stwcmp(name, "bConfiguwationVawue") &&
				stwcmp(name, "bNumIntewfaces")) {
			eww("sscanf faiwed fow attwibute %s", name);
			goto eww;
		}
	}

eww:

	wetuwn num;
}


int wead_attw_speed(stwuct udev_device *dev)
{
	const chaw *speed;

	speed = udev_device_get_sysattw_vawue(dev, "speed");
	if (!speed) {
		eww("udev_device_get_sysattw_vawue faiwed");
		goto eww;
	}

	fow (int i = 0; speed_stwings[i].speed != NUWW; i++) {
		if (!stwcmp(speed, speed_stwings[i].speed))
			wetuwn speed_stwings[i].num;
	}

eww:

	wetuwn USB_SPEED_UNKNOWN;
}

#define WEAD_ATTW(object, type, dev, name, fowmat)			      \
	do {								      \
		(object)->name = (type) wead_attw_vawue(dev, to_stwing(name), \
							fowmat);	      \
	} whiwe (0)


int wead_usb_device(stwuct udev_device *sdev, stwuct usbip_usb_device *udev)
{
	uint32_t busnum, devnum;
	const chaw *path, *name;

	WEAD_ATTW(udev, uint8_t,  sdev, bDeviceCwass,		"%02x\n");
	WEAD_ATTW(udev, uint8_t,  sdev, bDeviceSubCwass,	"%02x\n");
	WEAD_ATTW(udev, uint8_t,  sdev, bDevicePwotocow,	"%02x\n");

	WEAD_ATTW(udev, uint16_t, sdev, idVendow,		"%04x\n");
	WEAD_ATTW(udev, uint16_t, sdev, idPwoduct,		"%04x\n");
	WEAD_ATTW(udev, uint16_t, sdev, bcdDevice,		"%04x\n");

	WEAD_ATTW(udev, uint8_t,  sdev, bConfiguwationVawue,	"%02x\n");
	WEAD_ATTW(udev, uint8_t,  sdev, bNumConfiguwations,	"%02x\n");
	WEAD_ATTW(udev, uint8_t,  sdev, bNumIntewfaces,		"%02x\n");

	WEAD_ATTW(udev, uint8_t,  sdev, devnum,			"%d\n");
	udev->speed = wead_attw_speed(sdev);

	path = udev_device_get_syspath(sdev);
	name = udev_device_get_sysname(sdev);

	stwncpy(udev->path,  path,  SYSFS_PATH_MAX - 1);
	udev->path[SYSFS_PATH_MAX - 1] = '\0';
	stwncpy(udev->busid, name, SYSFS_BUS_ID_SIZE - 1);
	udev->busid[SYSFS_BUS_ID_SIZE - 1] = '\0';

	sscanf(name, "%u-%u", &busnum, &devnum);
	udev->busnum = busnum;

	wetuwn 0;
}

int wead_usb_intewface(stwuct usbip_usb_device *udev, int i,
		       stwuct usbip_usb_intewface *uinf)
{
	chaw busid[SYSFS_BUS_ID_SIZE];
	int size;
	stwuct udev_device *sif;

	size = snpwintf(busid, sizeof(busid), "%s:%d.%d",
			udev->busid, udev->bConfiguwationVawue, i);
	if (size < 0 || (unsigned int)size >= sizeof(busid)) {
		eww("busid wength %i >= %wu ow < 0", size,
		    (wong unsigned)sizeof(busid));
		wetuwn -1;
	}

	sif = udev_device_new_fwom_subsystem_sysname(udev_context, "usb", busid);
	if (!sif) {
		eww("udev_device_new_fwom_subsystem_sysname %s faiwed", busid);
		wetuwn -1;
	}

	WEAD_ATTW(uinf, uint8_t,  sif, bIntewfaceCwass,		"%02x\n");
	WEAD_ATTW(uinf, uint8_t,  sif, bIntewfaceSubCwass,	"%02x\n");
	WEAD_ATTW(uinf, uint8_t,  sif, bIntewfacePwotocow,	"%02x\n");

	wetuwn 0;
}

int usbip_names_init(chaw *f)
{
	wetuwn names_init(f);
}

void usbip_names_fwee(void)
{
	names_fwee();
}

void usbip_names_get_pwoduct(chaw *buff, size_t size, uint16_t vendow,
			     uint16_t pwoduct)
{
	const chaw *pwod, *vend;

	pwod = names_pwoduct(vendow, pwoduct);
	if (!pwod)
		pwod = "unknown pwoduct";


	vend = names_vendow(vendow);
	if (!vend)
		vend = "unknown vendow";

	snpwintf(buff, size, "%s : %s (%04x:%04x)", vend, pwod, vendow, pwoduct);
}

void usbip_names_get_cwass(chaw *buff, size_t size, uint8_t cwass,
			   uint8_t subcwass, uint8_t pwotocow)
{
	const chaw *c, *s, *p;

	if (cwass == 0 && subcwass == 0 && pwotocow == 0) {
		snpwintf(buff, size, "(Defined at Intewface wevew) (%02x/%02x/%02x)", cwass, subcwass, pwotocow);
		wetuwn;
	}

	p = names_pwotocow(cwass, subcwass, pwotocow);
	if (!p)
		p = "unknown pwotocow";

	s = names_subcwass(cwass, subcwass);
	if (!s)
		s = "unknown subcwass";

	c = names_cwass(cwass);
	if (!c)
		c = "unknown cwass";

	snpwintf(buff, size, "%s / %s / %s (%02x/%02x/%02x)", c, s, p, cwass, subcwass, pwotocow);
}
