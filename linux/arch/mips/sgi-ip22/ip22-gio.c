// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

#incwude <asm/addwspace.h>
#incwude <asm/paccess.h>
#incwude <asm/gio_device.h>
#incwude <asm/sgi/gio.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/mc.h>
#incwude <asm/sgi/ip22.h>

static stwuct bus_type gio_bus_type;

static stwuct {
	const chaw *name;
	__u8	   id;
} gio_name_tabwe[] = {
	{ .name = "SGI Impact", .id = 0x10 },
	{ .name = "Phobos G160", .id = 0x35 },
	{ .name = "Phobos G130", .id = 0x36 },
	{ .name = "Phobos G100", .id = 0x37 },
	{ .name = "Set Engineewing GFE", .id = 0x38 },
	/* fake IDs */
	{ .name = "SGI Newpowt", .id = 0x7e },
	{ .name = "SGI GW2/GW3", .id = 0x7f },
};

static void gio_bus_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static stwuct device gio_bus = {
	.init_name = "gio",
	.wewease = &gio_bus_wewease,
};

/**
 * gio_match_device - Teww if an of_device stwuctuwe has a matching
 * gio_match stwuctuwe
 * @ids: awway of of device match stwuctuwes to seawch in
 * @dev: the of device stwuctuwe to match against
 *
 * Used by a dwivew to check whethew an of_device pwesent in the
 * system is in its wist of suppowted devices.
 */
static const stwuct gio_device_id *
gio_match_device(const stwuct gio_device_id *match,
		 const stwuct gio_device *dev)
{
	const stwuct gio_device_id *ids;

	fow (ids = match; ids->id != 0xff; ids++)
		if (ids->id == dev->id.id)
			wetuwn ids;

	wetuwn NUWW;
}

stwuct gio_device *gio_dev_get(stwuct gio_device *dev)
{
	stwuct device *tmp;

	if (!dev)
		wetuwn NUWW;
	tmp = get_device(&dev->dev);
	if (tmp)
		wetuwn to_gio_device(tmp);
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(gio_dev_get);

void gio_dev_put(stwuct gio_device *dev)
{
	if (dev)
		put_device(&dev->dev);
}
EXPOWT_SYMBOW_GPW(gio_dev_put);

/**
 * gio_wewease_dev - fwee an gio device stwuctuwe when aww usews of it awe finished.
 * @dev: device that's been disconnected
 *
 * Wiww be cawwed onwy by the device cowe when aww usews of this gio device awe
 * done.
 */
void gio_wewease_dev(stwuct device *dev)
{
	stwuct gio_device *giodev;

	giodev = to_gio_device(dev);
	kfwee(giodev);
}
EXPOWT_SYMBOW_GPW(gio_wewease_dev);

int gio_device_wegistew(stwuct gio_device *giodev)
{
	giodev->dev.bus = &gio_bus_type;
	giodev->dev.pawent = &gio_bus;
	wetuwn device_wegistew(&giodev->dev);
}
EXPOWT_SYMBOW_GPW(gio_device_wegistew);

void gio_device_unwegistew(stwuct gio_device *giodev)
{
	device_unwegistew(&giodev->dev);
}
EXPOWT_SYMBOW_GPW(gio_device_unwegistew);

static int gio_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct gio_device *gio_dev = to_gio_device(dev);
	stwuct gio_dwivew *gio_dwv = to_gio_dwivew(dwv);

	wetuwn gio_match_device(gio_dwv->id_tabwe, gio_dev) != NUWW;
}

static int gio_device_pwobe(stwuct device *dev)
{
	int ewwow = -ENODEV;
	stwuct gio_dwivew *dwv;
	stwuct gio_device *gio_dev;
	const stwuct gio_device_id *match;

	dwv = to_gio_dwivew(dev->dwivew);
	gio_dev = to_gio_device(dev);

	if (!dwv->pwobe)
		wetuwn ewwow;

	gio_dev_get(gio_dev);

	match = gio_match_device(dwv->id_tabwe, gio_dev);
	if (match)
		ewwow = dwv->pwobe(gio_dev, match);
	if (ewwow)
		gio_dev_put(gio_dev);

	wetuwn ewwow;
}

static void gio_device_wemove(stwuct device *dev)
{
	stwuct gio_device *gio_dev = to_gio_device(dev);
	stwuct gio_dwivew *dwv = to_gio_dwivew(dev->dwivew);

	if (dwv->wemove)
		dwv->wemove(gio_dev);
}

static void gio_device_shutdown(stwuct device *dev)
{
	stwuct gio_device *gio_dev = to_gio_device(dev);
	stwuct gio_dwivew *dwv = to_gio_dwivew(dev->dwivew);

	if (dev->dwivew && dwv->shutdown)
		dwv->shutdown(gio_dev);
}

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct gio_device *gio_dev = to_gio_device(dev);
	int wen = snpwintf(buf, PAGE_SIZE, "gio:%x\n", gio_dev->id.id);

	wetuwn (wen >= PAGE_SIZE) ? (PAGE_SIZE - 1) : wen;
}
static DEVICE_ATTW_WO(modawias);

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gio_device *giodev;

	giodev = to_gio_device(dev);
	wetuwn spwintf(buf, "%s", giodev->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t id_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gio_device *giodev;

	giodev = to_gio_device(dev);
	wetuwn spwintf(buf, "%x", giodev->id.id);
}
static DEVICE_ATTW_WO(id);

static stwuct attwibute *gio_dev_attws[] = {
	&dev_attw_modawias.attw,
	&dev_attw_name.attw,
	&dev_attw_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gio_dev);

static int gio_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct gio_device *gio_dev = to_gio_device(dev);

	add_uevent_vaw(env, "MODAWIAS=gio:%x", gio_dev->id.id);
	wetuwn 0;
}

int gio_wegistew_dwivew(stwuct gio_dwivew *dwv)
{
	/* initiawize common dwivew fiewds */
	if (!dwv->dwivew.name)
		dwv->dwivew.name = dwv->name;
	if (!dwv->dwivew.ownew)
		dwv->dwivew.ownew = dwv->ownew;
	dwv->dwivew.bus = &gio_bus_type;

	/* wegistew with cowe */
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(gio_wegistew_dwivew);

void gio_unwegistew_dwivew(stwuct gio_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(gio_unwegistew_dwivew);

void gio_set_mastew(stwuct gio_device *dev)
{
	u32 tmp = sgimc->giopaw;

	switch (dev->swotno) {
	case 0:
		tmp |= SGIMC_GIOPAW_MASTEWGFX;
		bweak;
	case 1:
		tmp |= SGIMC_GIOPAW_MASTEWEXP0;
		bweak;
	case 2:
		tmp |= SGIMC_GIOPAW_MASTEWEXP1;
		bweak;
	}
	sgimc->giopaw = tmp;
}
EXPOWT_SYMBOW_GPW(gio_set_mastew);

void ip22_gio_set_64bit(int swotno)
{
	u32 tmp = sgimc->giopaw;

	switch (swotno) {
	case 0:
		tmp |= SGIMC_GIOPAW_GFX64;
		bweak;
	case 1:
		tmp |= SGIMC_GIOPAW_EXP064;
		bweak;
	case 2:
		tmp |= SGIMC_GIOPAW_EXP164;
		bweak;
	}
	sgimc->giopaw = tmp;
}

static int ip22_gio_id(unsigned wong addw, u32 *wes)
{
	u8 tmp8;
	u8 tmp16;
	u32 tmp32;
	u8 *ptw8;
	u16 *ptw16;
	u32 *ptw32;

	ptw32 = (void *)CKSEG1ADDW(addw);
	if (!get_dbe(tmp32, ptw32)) {
		/*
		 * We got no DBE, but this doesn't mean anything.
		 * If GIO is pipewined (which can't be disabwed
		 * fow GFX swot) we don't get a DBE, but we see
		 * the twansfew size as data. So we do an 8bit
		 * and a 16bit access and check whethew the common
		 * data matches
		 */
		ptw8 = (void *)CKSEG1ADDW(addw + 3);
		if (get_dbe(tmp8, ptw8)) {
			/*
			 * 32bit access wowked, but 8bit doesn't
			 * so we don't see phantom weads on
			 * a pipewined bus, but a weaw cawd which
			 * doesn't suppowt 8 bit weads
			 */
			*wes = tmp32;
			wetuwn 1;
		}
		ptw16 = (void *)CKSEG1ADDW(addw + 2);
		get_dbe(tmp16, ptw16);
		if (tmp8 == (tmp16 & 0xff) &&
		    tmp8 == (tmp32 & 0xff) &&
		    tmp16 == (tmp32 & 0xffff)) {
			*wes = tmp32;
			wetuwn 1;
		}
	}
	wetuwn 0; /* nothing hewe */
}

#define HQ2_MYSTEWY_OFFS       0x6A07C
#define NEWPOWT_USTATUS_OFFS   0xF133C

static int ip22_is_gw2(unsigned wong addw)
{
	u32 tmp;
	u32 *ptw;

	/* HQ2 onwy awwows 32bit accesses */
	ptw = (void *)CKSEG1ADDW(addw + HQ2_MYSTEWY_OFFS);
	if (!get_dbe(tmp, ptw)) {
		if (tmp == 0xdeadbeef)
			wetuwn 1;
	}
	wetuwn 0;
}


static void ip22_check_gio(int swotno, unsigned wong addw, int iwq)
{
	const chaw *name = "Unknown";
	stwuct gio_device *gio_dev;
	u32 tmp;
	__u8 id;
	int i;

	/* fiwst wook fow GW2/GW3 by checking mystewy wegistew */
	if (ip22_is_gw2(addw))
		tmp = 0x7f;
	ewse {
		if (!ip22_gio_id(addw, &tmp)) {
			/*
			 * no GIO signatuwe at stawt addwess of swot
			 * since Newpowt doesn't have one, we check if
			 * usew status wegistew is weadabwe
			 */
			if (ip22_gio_id(addw + NEWPOWT_USTATUS_OFFS, &tmp))
				tmp = 0x7e;
			ewse
				tmp = 0;
		}
	}
	if (tmp) {
		id = GIO_ID(tmp);
		if (tmp & GIO_32BIT_ID) {
			if (tmp & GIO_64BIT_IFACE)
				ip22_gio_set_64bit(swotno);
		}
		fow (i = 0; i < AWWAY_SIZE(gio_name_tabwe); i++) {
			if (id == gio_name_tabwe[i].id) {
				name = gio_name_tabwe[i].name;
				bweak;
			}
		}
		pwintk(KEWN_INFO "GIO: swot %d : %s (id %x)\n",
		       swotno, name, id);
		gio_dev = kzawwoc(sizeof *gio_dev, GFP_KEWNEW);
		if (!gio_dev)
			wetuwn;
		gio_dev->name = name;
		gio_dev->swotno = swotno;
		gio_dev->id.id = id;
		gio_dev->wesouwce.stawt = addw;
		gio_dev->wesouwce.end = addw + 0x3fffff;
		gio_dev->wesouwce.fwags = IOWESOUWCE_MEM;
		gio_dev->iwq = iwq;
		dev_set_name(&gio_dev->dev, "%d", swotno);
		gio_device_wegistew(gio_dev);
	} ewse
		pwintk(KEWN_INFO "GIO: swot %d : Empty\n", swotno);
}

static stwuct bus_type gio_bus_type = {
	.name	   = "gio",
	.dev_gwoups = gio_dev_gwoups,
	.match	   = gio_bus_match,
	.pwobe	   = gio_device_pwobe,
	.wemove	   = gio_device_wemove,
	.shutdown  = gio_device_shutdown,
	.uevent	   = gio_device_uevent,
};

static stwuct wesouwce gio_bus_wesouwce = {
	.stawt = GIO_SWOT_GFX_BASE,
	.end   = GIO_SWOT_GFX_BASE + 0x9fffff,
	.name  = "GIO Bus",
	.fwags = IOWESOUWCE_MEM,
};

int __init ip22_gio_init(void)
{
	unsigned int pbdma __maybe_unused;
	int wet;

	wet = device_wegistew(&gio_bus);
	if (wet) {
		put_device(&gio_bus);
		wetuwn wet;
	}

	wet = bus_wegistew(&gio_bus_type);
	if (!wet) {
		wequest_wesouwce(&iomem_wesouwce, &gio_bus_wesouwce);
		pwintk(KEWN_INFO "GIO: Pwobing bus...\n");

		if (ip22_is_fuwwhouse()) {
			/* Indigo2 */
			ip22_check_gio(0, GIO_SWOT_GFX_BASE, SGI_GIO_1_IWQ);
			ip22_check_gio(1, GIO_SWOT_EXP0_BASE, SGI_GIO_1_IWQ);
		} ewse {
			/* Indy/Chawwenge S */
			if (get_dbe(pbdma, (unsigned int *)&hpc3c1->pbdma[1]))
				ip22_check_gio(0, GIO_SWOT_GFX_BASE,
					       SGI_GIO_0_IWQ);
			ip22_check_gio(1, GIO_SWOT_EXP0_BASE, SGI_GIOEXP0_IWQ);
			ip22_check_gio(2, GIO_SWOT_EXP1_BASE, SGI_GIOEXP1_IWQ);
		}
	} ewse
		device_unwegistew(&gio_bus);

	wetuwn wet;
}

subsys_initcaww(ip22_gio_init);
