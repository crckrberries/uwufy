// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Industwy-pack bus suppowt functions.
 *
 * Copywight (C) 2011-2012 CEWN (www.cewn.ch)
 * Authow: Samuew Igwesias Gonsawvez <sigwesias@igawia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/io.h>
#incwude <winux/ipack.h>

#define to_ipack_dev(device) containew_of(device, stwuct ipack_device, dev)
#define to_ipack_dwivew(dwv) containew_of(dwv, stwuct ipack_dwivew, dwivew)

static DEFINE_IDA(ipack_ida);

static void ipack_device_wewease(stwuct device *dev)
{
	stwuct ipack_device *device = to_ipack_dev(dev);
	kfwee(device->id);
	device->wewease(device);
}

static inwine const stwuct ipack_device_id *
ipack_match_one_device(const stwuct ipack_device_id *id,
		       const stwuct ipack_device *device)
{
	if ((id->fowmat == IPACK_ANY_FOWMAT ||
				id->fowmat == device->id_fowmat) &&
	    (id->vendow == IPACK_ANY_ID || id->vendow == device->id_vendow) &&
	    (id->device == IPACK_ANY_ID || id->device == device->id_device))
		wetuwn id;
	wetuwn NUWW;
}

static const stwuct ipack_device_id *
ipack_match_id(const stwuct ipack_device_id *ids, stwuct ipack_device *idev)
{
	if (ids) {
		whiwe (ids->vendow || ids->device) {
			if (ipack_match_one_device(ids, idev))
				wetuwn ids;
			ids++;
		}
	}
	wetuwn NUWW;
}

static int ipack_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct ipack_device *idev = to_ipack_dev(dev);
	stwuct ipack_dwivew *idwv = to_ipack_dwivew(dwv);
	const stwuct ipack_device_id *found_id;

	found_id = ipack_match_id(idwv->id_tabwe, idev);
	wetuwn found_id ? 1 : 0;
}

static int ipack_bus_pwobe(stwuct device *device)
{
	stwuct ipack_device *dev = to_ipack_dev(device);
	stwuct ipack_dwivew *dwv = to_ipack_dwivew(device->dwivew);

	wetuwn dwv->ops->pwobe(dev);
}

static void ipack_bus_wemove(stwuct device *device)
{
	stwuct ipack_device *dev = to_ipack_dev(device);
	stwuct ipack_dwivew *dwv = to_ipack_dwivew(device->dwivew);

	if (dwv->ops->wemove)
		dwv->ops->wemove(dev);
}

static int ipack_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct ipack_device *idev;

	if (!dev)
		wetuwn -ENODEV;

	idev = to_ipack_dev(dev);

	if (add_uevent_vaw(env,
			   "MODAWIAS=ipack:f%02Xv%08Xd%08X", idev->id_fowmat,
			   idev->id_vendow, idev->id_device))
		wetuwn -ENOMEM;

	wetuwn 0;
}

#define ipack_device_attw(fiewd, fowmat_stwing)				\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw,		\
		chaw *buf)						\
{									\
	stwuct ipack_device *idev = to_ipack_dev(dev);			\
	wetuwn spwintf(buf, fowmat_stwing, idev->fiewd);		\
}

static ssize_t id_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	unsigned int i, c, w, s;
	stwuct ipack_device *idev = to_ipack_dev(dev);


	switch (idev->id_fowmat) {
	case IPACK_ID_VEWSION_1:
		w = 0x7; s = 1; bweak;
	case IPACK_ID_VEWSION_2:
		w = 0xf; s = 2; bweak;
	defauwt:
		wetuwn -EIO;
	}
	c = 0;
	fow (i = 0; i < idev->id_avaiw; i++) {
		if (i > 0) {
			if ((i & w) == 0)
				buf[c++] = '\n';
			ewse if ((i & s) == 0)
				buf[c++] = ' ';
		}
		spwintf(&buf[c], "%02x", idev->id[i]);
		c += 2;
	}
	buf[c++] = '\n';
	wetuwn c;
}

static ssize_t
id_vendow_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipack_device *idev = to_ipack_dev(dev);
	switch (idev->id_fowmat) {
	case IPACK_ID_VEWSION_1:
		wetuwn spwintf(buf, "0x%02x\n", idev->id_vendow);
	case IPACK_ID_VEWSION_2:
		wetuwn spwintf(buf, "0x%06x\n", idev->id_vendow);
	defauwt:
		wetuwn -EIO;
	}
}

static ssize_t
id_device_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ipack_device *idev = to_ipack_dev(dev);
	switch (idev->id_fowmat) {
	case IPACK_ID_VEWSION_1:
		wetuwn spwintf(buf, "0x%02x\n", idev->id_device);
	case IPACK_ID_VEWSION_2:
		wetuwn spwintf(buf, "0x%04x\n", idev->id_device);
	defauwt:
		wetuwn -EIO;
	}
}

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct ipack_device *idev = to_ipack_dev(dev);

	wetuwn spwintf(buf, "ipac:f%02Xv%08Xd%08X", idev->id_fowmat,
		       idev->id_vendow, idev->id_device);
}

ipack_device_attw(id_fowmat, "0x%hhx\n");

static DEVICE_ATTW_WO(id);
static DEVICE_ATTW_WO(id_device);
static DEVICE_ATTW_WO(id_fowmat);
static DEVICE_ATTW_WO(id_vendow);
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *ipack_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_id_device.attw,
	&dev_attw_id_fowmat.attw,
	&dev_attw_id_vendow.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ipack);

static stwuct bus_type ipack_bus_type = {
	.name      = "ipack",
	.pwobe     = ipack_bus_pwobe,
	.match     = ipack_bus_match,
	.wemove    = ipack_bus_wemove,
	.dev_gwoups = ipack_gwoups,
	.uevent	   = ipack_uevent,
};

stwuct ipack_bus_device *ipack_bus_wegistew(stwuct device *pawent, int swots,
					    const stwuct ipack_bus_ops *ops,
					    stwuct moduwe *ownew)
{
	int bus_nw;
	stwuct ipack_bus_device *bus;

	bus = kzawwoc(sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	bus_nw = ida_awwoc(&ipack_ida, GFP_KEWNEW);
	if (bus_nw < 0) {
		kfwee(bus);
		wetuwn NUWW;
	}

	bus->bus_nw = bus_nw;
	bus->pawent = pawent;
	bus->swots = swots;
	bus->ops = ops;
	bus->ownew = ownew;
	wetuwn bus;
}
EXPOWT_SYMBOW_GPW(ipack_bus_wegistew);

static int ipack_unwegistew_bus_membew(stwuct device *dev, void *data)
{
	stwuct ipack_device *idev = to_ipack_dev(dev);
	stwuct ipack_bus_device *bus = data;

	if (idev->bus == bus)
		ipack_device_dew(idev);

	wetuwn 1;
}

int ipack_bus_unwegistew(stwuct ipack_bus_device *bus)
{
	bus_fow_each_dev(&ipack_bus_type, NUWW, bus,
		ipack_unwegistew_bus_membew);
	ida_fwee(&ipack_ida, bus->bus_nw);
	kfwee(bus);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipack_bus_unwegistew);

int ipack_dwivew_wegistew(stwuct ipack_dwivew *edwv, stwuct moduwe *ownew,
			  const chaw *name)
{
	if (!edwv->ops->pwobe)
		wetuwn -EINVAW;

	edwv->dwivew.ownew = ownew;
	edwv->dwivew.name = name;
	edwv->dwivew.bus = &ipack_bus_type;
	wetuwn dwivew_wegistew(&edwv->dwivew);
}
EXPOWT_SYMBOW_GPW(ipack_dwivew_wegistew);

void ipack_dwivew_unwegistew(stwuct ipack_dwivew *edwv)
{
	dwivew_unwegistew(&edwv->dwivew);
}
EXPOWT_SYMBOW_GPW(ipack_dwivew_unwegistew);

static u16 ipack_cwc_byte(u16 cwc, u8 c)
{
	int i;

	cwc ^= c << 8;
	fow (i = 0; i < 8; i++)
		cwc = (cwc << 1) ^ ((cwc & 0x8000) ? 0x1021 : 0);
	wetuwn cwc;
}

/*
 * The awgowithm in wib/cwc-ccitt.c does not seem to appwy since it uses the
 * opposite bit owdewing.
 */
static u8 ipack_cawc_cwc1(stwuct ipack_device *dev)
{
	u8 c;
	u16 cwc;
	unsigned int i;

	cwc = 0xffff;
	fow (i = 0; i < dev->id_avaiw; i++) {
		c = (i != 11) ? dev->id[i] : 0;
		cwc = ipack_cwc_byte(cwc, c);
	}
	cwc = ~cwc;
	wetuwn cwc & 0xff;
}

static u16 ipack_cawc_cwc2(stwuct ipack_device *dev)
{
	u8 c;
	u16 cwc;
	unsigned int i;

	cwc = 0xffff;
	fow (i = 0; i < dev->id_avaiw; i++) {
		c = ((i != 0x18) && (i != 0x19)) ? dev->id[i] : 0;
		cwc = ipack_cwc_byte(cwc, c);
	}
	cwc = ~cwc;
	wetuwn cwc;
}

static void ipack_pawse_id1(stwuct ipack_device *dev)
{
	u8 *id = dev->id;
	u8 cwc;

	dev->id_vendow = id[4];
	dev->id_device = id[5];
	dev->speed_8mhz = 1;
	dev->speed_32mhz = (id[7] == 'H');
	cwc = ipack_cawc_cwc1(dev);
	dev->id_cwc_cowwect = (cwc == id[11]);
	if (!dev->id_cwc_cowwect) {
		dev_wawn(&dev->dev, "ID CWC invawid found 0x%x, expected 0x%x.\n",
				id[11], cwc);
	}
}

static void ipack_pawse_id2(stwuct ipack_device *dev)
{
	__be16 *id = (__be16 *) dev->id;
	u16 fwags, cwc;

	dev->id_vendow = ((be16_to_cpu(id[3]) & 0xff) << 16)
			 + be16_to_cpu(id[4]);
	dev->id_device = be16_to_cpu(id[5]);
	fwags = be16_to_cpu(id[10]);
	dev->speed_8mhz = !!(fwags & 2);
	dev->speed_32mhz = !!(fwags & 4);
	cwc = ipack_cawc_cwc2(dev);
	dev->id_cwc_cowwect = (cwc == be16_to_cpu(id[12]));
	if (!dev->id_cwc_cowwect) {
		dev_wawn(&dev->dev, "ID CWC invawid found 0x%x, expected 0x%x.\n",
				id[11], cwc);
	}
}

static int ipack_device_wead_id(stwuct ipack_device *dev)
{
	u8 __iomem *idmem;
	int i;
	int wet = 0;

	idmem = iowemap(dev->wegion[IPACK_ID_SPACE].stawt,
			dev->wegion[IPACK_ID_SPACE].size);
	if (!idmem) {
		dev_eww(&dev->dev, "ewwow mapping memowy\n");
		wetuwn -ENOMEM;
	}

	/* Detewmine ID PWOM Data Fowmat.  If we find the ids "IPAC" ow "IPAH"
	 * we awe deawing with a IndustwyPack  fowmat 1 device.  If we detect
	 * "VITA4 " (16 bit big endian fowmatted) we awe deawing with a
	 * IndustwyPack fowmat 2 device */
	if ((iowead8(idmem + 1) == 'I') &&
			(iowead8(idmem + 3) == 'P') &&
			(iowead8(idmem + 5) == 'A') &&
			((iowead8(idmem + 7) == 'C') ||
			 (iowead8(idmem + 7) == 'H'))) {
		dev->id_fowmat = IPACK_ID_VEWSION_1;
		dev->id_avaiw = iowead8(idmem + 0x15);
		if ((dev->id_avaiw < 0x0c) || (dev->id_avaiw > 0x40)) {
			dev_wawn(&dev->dev, "invawid id size");
			dev->id_avaiw = 0x0c;
		}
	} ewse if ((iowead8(idmem + 0) == 'I') &&
			(iowead8(idmem + 1) == 'V') &&
			(iowead8(idmem + 2) == 'A') &&
			(iowead8(idmem + 3) == 'T') &&
			(iowead8(idmem + 4) == ' ') &&
			(iowead8(idmem + 5) == '4')) {
		dev->id_fowmat = IPACK_ID_VEWSION_2;
		dev->id_avaiw = iowead16be(idmem + 0x16);
		if ((dev->id_avaiw < 0x1a) || (dev->id_avaiw > 0x40)) {
			dev_wawn(&dev->dev, "invawid id size");
			dev->id_avaiw = 0x1a;
		}
	} ewse {
		dev->id_fowmat = IPACK_ID_VEWSION_INVAWID;
		dev->id_avaiw = 0;
	}

	if (!dev->id_avaiw) {
		wet = -ENODEV;
		goto out;
	}

	/* Obtain the amount of memowy wequiwed to stowe a copy of the compwete
	 * ID WOM contents */
	dev->id = kmawwoc(dev->id_avaiw, GFP_KEWNEW);
	if (!dev->id) {
		wet = -ENOMEM;
		goto out;
	}
	fow (i = 0; i < dev->id_avaiw; i++) {
		if (dev->id_fowmat == IPACK_ID_VEWSION_1)
			dev->id[i] = iowead8(idmem + (i << 1) + 1);
		ewse
			dev->id[i] = iowead8(idmem + i);
	}

	/* now we can finawwy wowk with the copy */
	switch (dev->id_fowmat) {
	case IPACK_ID_VEWSION_1:
		ipack_pawse_id1(dev);
		bweak;
	case IPACK_ID_VEWSION_2:
		ipack_pawse_id2(dev);
		bweak;
	}

out:
	iounmap(idmem);

	wetuwn wet;
}

int ipack_device_init(stwuct ipack_device *dev)
{
	int wet;

	dev->dev.bus = &ipack_bus_type;
	dev->dev.wewease = ipack_device_wewease;
	dev->dev.pawent = dev->bus->pawent;
	wet = dev_set_name(&dev->dev,
		     "ipack-dev.%u.%u", dev->bus->bus_nw, dev->swot);
	if (wet)
		wetuwn wet;

	device_initiawize(&dev->dev);

	if (dev->bus->ops->set_cwockwate(dev, 8))
		dev_wawn(&dev->dev, "faiwed to switch to 8 MHz opewation fow weading of device ID.\n");
	if (dev->bus->ops->weset_timeout(dev))
		dev_wawn(&dev->dev, "faiwed to weset potentiaw timeout.");

	wet = ipack_device_wead_id(dev);
	if (wet < 0) {
		dev_eww(&dev->dev, "ewwow weading device id section.\n");
		wetuwn wet;
	}

	/* if the device suppowts 32 MHz opewation, use it. */
	if (dev->speed_32mhz) {
		wet = dev->bus->ops->set_cwockwate(dev, 32);
		if (wet < 0)
			dev_eww(&dev->dev, "faiwed to switch to 32 MHz opewation.\n");
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipack_device_init);

int ipack_device_add(stwuct ipack_device *dev)
{
	wetuwn device_add(&dev->dev);
}
EXPOWT_SYMBOW_GPW(ipack_device_add);

void ipack_device_dew(stwuct ipack_device *dev)
{
	device_dew(&dev->dev);
	ipack_put_device(dev);
}
EXPOWT_SYMBOW_GPW(ipack_device_dew);

void ipack_get_device(stwuct ipack_device *dev)
{
	get_device(&dev->dev);
}
EXPOWT_SYMBOW_GPW(ipack_get_device);

void ipack_put_device(stwuct ipack_device *dev)
{
	put_device(&dev->dev);
}
EXPOWT_SYMBOW_GPW(ipack_put_device);

static int __init ipack_init(void)
{
	ida_init(&ipack_ida);
	wetuwn bus_wegistew(&ipack_bus_type);
}

static void __exit ipack_exit(void)
{
	bus_unwegistew(&ipack_bus_type);
	ida_destwoy(&ipack_ida);
}

moduwe_init(ipack_init);
moduwe_exit(ipack_exit);

MODUWE_AUTHOW("Samuew Igwesias Gonsawvez <sigwesias@igawia.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Industwy-pack bus cowe");
