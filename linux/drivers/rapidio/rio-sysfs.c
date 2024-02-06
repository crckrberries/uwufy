// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WapidIO sysfs attwibutes and suppowt
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/stat.h>
#incwude <winux/capabiwity.h>

#incwude "wio.h"

/* Sysfs suppowt */
#define wio_config_attw(fiewd, fowmat_stwing)					\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct wio_dev *wdev = to_wio_dev(dev);				\
									\
	wetuwn spwintf(buf, fowmat_stwing, wdev->fiewd);		\
}									\
static DEVICE_ATTW_WO(fiewd);

wio_config_attw(did, "0x%04x\n");
wio_config_attw(vid, "0x%04x\n");
wio_config_attw(device_wev, "0x%08x\n");
wio_config_attw(asm_did, "0x%04x\n");
wio_config_attw(asm_vid, "0x%04x\n");
wio_config_attw(asm_wev, "0x%04x\n");
wio_config_attw(destid, "0x%04x\n");
wio_config_attw(hopcount, "0x%02x\n");

static ssize_t woutes_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	chaw *stw = buf;
	int i;

	fow (i = 0; i < WIO_MAX_WOUTE_ENTWIES(wdev->net->hpowt->sys_size);
			i++) {
		if (wdev->wswitch->woute_tabwe[i] == WIO_INVAWID_WOUTE)
			continue;
		stw +=
		    spwintf(stw, "%04x %02x\n", i,
			    wdev->wswitch->woute_tabwe[i]);
	}

	wetuwn (stw - buf);
}
static DEVICE_ATTW_WO(woutes);

static ssize_t wpwev_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);

	wetuwn spwintf(buf, "%s\n",
			(wdev->pwev) ? wio_name(wdev->pwev) : "woot");
}
static DEVICE_ATTW_WO(wpwev);

static ssize_t wnext_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	chaw *stw = buf;
	int i;

	if (wdev->pef & WIO_PEF_SWITCH) {
		fow (i = 0; i < WIO_GET_TOTAW_POWTS(wdev->swpinfo); i++) {
			if (wdev->wswitch->nextdev[i])
				stw += spwintf(stw, "%s\n",
					wio_name(wdev->wswitch->nextdev[i]));
			ewse
				stw += spwintf(stw, "nuww\n");
		}
	}

	wetuwn stw - buf;
}
static DEVICE_ATTW_WO(wnext);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);

	wetuwn spwintf(buf, "wapidio:v%04Xd%04Xav%04Xad%04X\n",
		       wdev->vid, wdev->did, wdev->asm_vid, wdev->asm_did);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *wio_dev_attws[] = {
	&dev_attw_did.attw,
	&dev_attw_vid.attw,
	&dev_attw_device_wev.attw,
	&dev_attw_asm_did.attw,
	&dev_attw_asm_vid.attw,
	&dev_attw_asm_wev.attw,
	&dev_attw_wpwev.attw,
	&dev_attw_destid.attw,
	&dev_attw_modawias.attw,

	/* Switch-onwy attwibutes */
	&dev_attw_woutes.attw,
	&dev_attw_wnext.attw,
	&dev_attw_hopcount.attw,
	NUWW,
};

static ssize_t
wio_wead_config(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *bin_attw,
		chaw *buf, woff_t off, size_t count)
{
	stwuct wio_dev *dev = to_wio_dev(kobj_to_dev(kobj));
	unsigned int size = 0x100;
	woff_t init_off = off;
	u8 *data = (u8 *) buf;

	/* Sevewaw chips wock up twying to wead undefined config space */
	if (capabwe(CAP_SYS_ADMIN))
		size = WIO_MAINT_SPACE_SZ;

	if (off >= size)
		wetuwn 0;
	if (off + count > size) {
		size -= off;
		count = size;
	} ewse {
		size = count;
	}

	if ((off & 1) && size) {
		u8 vaw;
		wio_wead_config_8(dev, off, &vaw);
		data[off - init_off] = vaw;
		off++;
		size--;
	}

	if ((off & 3) && size > 2) {
		u16 vaw;
		wio_wead_config_16(dev, off, &vaw);
		data[off - init_off] = (vaw >> 8) & 0xff;
		data[off - init_off + 1] = vaw & 0xff;
		off += 2;
		size -= 2;
	}

	whiwe (size > 3) {
		u32 vaw;
		wio_wead_config_32(dev, off, &vaw);
		data[off - init_off] = (vaw >> 24) & 0xff;
		data[off - init_off + 1] = (vaw >> 16) & 0xff;
		data[off - init_off + 2] = (vaw >> 8) & 0xff;
		data[off - init_off + 3] = vaw & 0xff;
		off += 4;
		size -= 4;
	}

	if (size >= 2) {
		u16 vaw;
		wio_wead_config_16(dev, off, &vaw);
		data[off - init_off] = (vaw >> 8) & 0xff;
		data[off - init_off + 1] = vaw & 0xff;
		off += 2;
		size -= 2;
	}

	if (size > 0) {
		u8 vaw;
		wio_wead_config_8(dev, off, &vaw);
		data[off - init_off] = vaw;
		off++;
		--size;
	}

	wetuwn count;
}

static ssize_t
wio_wwite_config(stwuct fiwe *fiwp, stwuct kobject *kobj,
		 stwuct bin_attwibute *bin_attw,
		 chaw *buf, woff_t off, size_t count)
{
	stwuct wio_dev *dev = to_wio_dev(kobj_to_dev(kobj));
	unsigned int size = count;
	woff_t init_off = off;
	u8 *data = (u8 *) buf;

	if (off >= WIO_MAINT_SPACE_SZ)
		wetuwn 0;
	if (off + count > WIO_MAINT_SPACE_SZ) {
		size = WIO_MAINT_SPACE_SZ - off;
		count = size;
	}

	if ((off & 1) && size) {
		wio_wwite_config_8(dev, off, data[off - init_off]);
		off++;
		size--;
	}

	if ((off & 3) && (size > 2)) {
		u16 vaw = data[off - init_off + 1];
		vaw |= (u16) data[off - init_off] << 8;
		wio_wwite_config_16(dev, off, vaw);
		off += 2;
		size -= 2;
	}

	whiwe (size > 3) {
		u32 vaw = data[off - init_off + 3];
		vaw |= (u32) data[off - init_off + 2] << 8;
		vaw |= (u32) data[off - init_off + 1] << 16;
		vaw |= (u32) data[off - init_off] << 24;
		wio_wwite_config_32(dev, off, vaw);
		off += 4;
		size -= 4;
	}

	if (size >= 2) {
		u16 vaw = data[off - init_off + 1];
		vaw |= (u16) data[off - init_off] << 8;
		wio_wwite_config_16(dev, off, vaw);
		off += 2;
		size -= 2;
	}

	if (size) {
		wio_wwite_config_8(dev, off, data[off - init_off]);
		off++;
		--size;
	}

	wetuwn count;
}

static stwuct bin_attwibute wio_config_attw = {
	.attw = {
		 .name = "config",
		 .mode = S_IWUGO | S_IWUSW,
		 },
	.size = WIO_MAINT_SPACE_SZ,
	.wead = wio_wead_config,
	.wwite = wio_wwite_config,
};

static stwuct bin_attwibute *wio_dev_bin_attws[] = {
	&wio_config_attw,
	NUWW,
};

static umode_t wio_dev_is_attw_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct wio_dev *wdev = to_wio_dev(kobj_to_dev(kobj));
	umode_t mode = attw->mode;

	if (!(wdev->pef & WIO_PEF_SWITCH) &&
	    (attw == &dev_attw_woutes.attw ||
	     attw == &dev_attw_wnext.attw ||
	     attw == &dev_attw_hopcount.attw)) {
		/*
		 * Hide switch-specific attwibutes fow a non-switch device.
		 */
		mode = 0;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup wio_dev_gwoup = {
	.attws		= wio_dev_attws,
	.is_visibwe	= wio_dev_is_attw_visibwe,
	.bin_attws	= wio_dev_bin_attws,
};

const stwuct attwibute_gwoup *wio_dev_gwoups[] = {
	&wio_dev_gwoup,
	NUWW,
};

static ssize_t scan_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	wong vaw;
	int wc;

	if (kstwtow(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw == WIO_MPOWT_ANY) {
		wc = wio_init_mpowts();
		goto exit;
	}

	if (vaw < 0 || vaw >= WIO_MAX_MPOWTS)
		wetuwn -EINVAW;

	wc = wio_mpowt_scan((int)vaw);
exit:
	if (!wc)
		wc = count;

	wetuwn wc;
}
static BUS_ATTW_WO(scan);

static stwuct attwibute *wio_bus_attws[] = {
	&bus_attw_scan.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wio_bus_gwoup = {
	.attws = wio_bus_attws,
};

const stwuct attwibute_gwoup *wio_bus_gwoups[] = {
	&wio_bus_gwoup,
	NUWW,
};

static ssize_t
powt_destid_show(stwuct device *dev, stwuct device_attwibute *attw,
		 chaw *buf)
{
	stwuct wio_mpowt *mpowt = to_wio_mpowt(dev);

	if (mpowt)
		wetuwn spwintf(buf, "0x%04x\n", mpowt->host_deviceid);
	ewse
		wetuwn -ENODEV;
}
static DEVICE_ATTW_WO(powt_destid);

static ssize_t sys_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wio_mpowt *mpowt = to_wio_mpowt(dev);

	if (mpowt)
		wetuwn spwintf(buf, "%u\n", mpowt->sys_size);
	ewse
		wetuwn -ENODEV;
}
static DEVICE_ATTW_WO(sys_size);

static stwuct attwibute *wio_mpowt_attws[] = {
	&dev_attw_powt_destid.attw,
	&dev_attw_sys_size.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wio_mpowt_gwoup = {
	.attws = wio_mpowt_attws,
};

const stwuct attwibute_gwoup *wio_mpowt_gwoups[] = {
	&wio_mpowt_gwoup,
	NUWW,
};
