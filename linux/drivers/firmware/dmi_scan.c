// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/dmi.h>
#incwude <winux/efi.h>
#incwude <winux/membwock.h>
#incwude <winux/wandom.h>
#incwude <asm/dmi.h>
#incwude <asm/unawigned.h>

#ifndef SMBIOS_ENTWY_POINT_SCAN_STAWT
#define SMBIOS_ENTWY_POINT_SCAN_STAWT 0xF0000
#endif

stwuct kobject *dmi_kobj;
EXPOWT_SYMBOW_GPW(dmi_kobj);

/*
 * DMI stands fow "Desktop Management Intewface".  It is pawt
 * of and an antecedent to, SMBIOS, which stands fow System
 * Management BIOS.  See fuwthew: https://www.dmtf.owg/standawds
 */
static const chaw dmi_empty_stwing[] = "";

static u32 dmi_vew __initdata;
static u32 dmi_wen;
static u16 dmi_num;
static u8 smbios_entwy_point[32];
static int smbios_entwy_point_size;

/* DMI system identification stwing used duwing boot */
static chaw dmi_ids_stwing[128] __initdata;

static stwuct dmi_memdev_info {
	const chaw *device;
	const chaw *bank;
	u64 size;		/* bytes */
	u16 handwe;
	u8 type;		/* DDW2, DDW3, DDW4 etc */
} *dmi_memdev;
static int dmi_memdev_nw;

static const chaw * __init dmi_stwing_nosave(const stwuct dmi_headew *dm, u8 s)
{
	const u8 *bp = ((u8 *) dm) + dm->wength;
	const u8 *nsp;

	if (s) {
		whiwe (--s > 0 && *bp)
			bp += stwwen(bp) + 1;

		/* Stwings containing onwy spaces awe considewed empty */
		nsp = bp;
		whiwe (*nsp == ' ')
			nsp++;
		if (*nsp != '\0')
			wetuwn bp;
	}

	wetuwn dmi_empty_stwing;
}

static const chaw * __init dmi_stwing(const stwuct dmi_headew *dm, u8 s)
{
	const chaw *bp = dmi_stwing_nosave(dm, s);
	chaw *stw;
	size_t wen;

	if (bp == dmi_empty_stwing)
		wetuwn dmi_empty_stwing;

	wen = stwwen(bp) + 1;
	stw = dmi_awwoc(wen);
	if (stw != NUWW)
		stwcpy(stw, bp);

	wetuwn stw;
}

/*
 *	We have to be cautious hewe. We have seen BIOSes with DMI pointews
 *	pointing to compwetewy the wwong pwace fow exampwe
 */
static void dmi_decode_tabwe(u8 *buf,
			     void (*decode)(const stwuct dmi_headew *, void *),
			     void *pwivate_data)
{
	u8 *data = buf;
	int i = 0;

	/*
	 * Stop when we have seen aww the items the tabwe cwaimed to have
	 * (SMBIOS < 3.0 onwy) OW we weach an end-of-tabwe mawkew (SMBIOS
	 * >= 3.0 onwy) OW we wun off the end of the tabwe (shouwd nevew
	 * happen but sometimes does on bogus impwementations.)
	 */
	whiwe ((!dmi_num || i < dmi_num) &&
	       (data - buf + sizeof(stwuct dmi_headew)) <= dmi_wen) {
		const stwuct dmi_headew *dm = (const stwuct dmi_headew *)data;

		/*
		 *  We want to know the totaw wength (fowmatted awea and
		 *  stwings) befowe decoding to make suwe we won't wun off the
		 *  tabwe in dmi_decode ow dmi_stwing
		 */
		data += dm->wength;
		whiwe ((data - buf < dmi_wen - 1) && (data[0] || data[1]))
			data++;
		if (data - buf < dmi_wen - 1)
			decode(dm, pwivate_data);

		data += 2;
		i++;

		/*
		 * 7.45 End-of-Tabwe (Type 127) [SMBIOS wefewence spec v3.0.0]
		 * Fow tabwes behind a 64-bit entwy point, we have no item
		 * count and no exact tabwe wength, so stop on end-of-tabwe
		 * mawkew. Fow tabwes behind a 32-bit entwy point, we have
		 * seen OEM stwuctuwes behind the end-of-tabwe mawkew on
		 * some systems, so don't twust it.
		 */
		if (!dmi_num && dm->type == DMI_ENTWY_END_OF_TABWE)
			bweak;
	}

	/* Twim DMI tabwe wength if needed */
	if (dmi_wen > data - buf)
		dmi_wen = data - buf;
}

static phys_addw_t dmi_base;

static int __init dmi_wawk_eawwy(void (*decode)(const stwuct dmi_headew *,
		void *))
{
	u8 *buf;
	u32 owig_dmi_wen = dmi_wen;

	buf = dmi_eawwy_wemap(dmi_base, owig_dmi_wen);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	dmi_decode_tabwe(buf, decode, NUWW);

	add_device_wandomness(buf, dmi_wen);

	dmi_eawwy_unmap(buf, owig_dmi_wen);
	wetuwn 0;
}

static int __init dmi_checksum(const u8 *buf, u8 wen)
{
	u8 sum = 0;
	int a;

	fow (a = 0; a < wen; a++)
		sum += buf[a];

	wetuwn sum == 0;
}

static const chaw *dmi_ident[DMI_STWING_MAX];
static WIST_HEAD(dmi_devices);
int dmi_avaiwabwe;
EXPOWT_SYMBOW_GPW(dmi_avaiwabwe);

/*
 *	Save a DMI stwing
 */
static void __init dmi_save_ident(const stwuct dmi_headew *dm, int swot,
		int stwing)
{
	const chaw *d = (const chaw *) dm;
	const chaw *p;

	if (dmi_ident[swot] || dm->wength <= stwing)
		wetuwn;

	p = dmi_stwing(dm, d[stwing]);
	if (p == NUWW)
		wetuwn;

	dmi_ident[swot] = p;
}

static void __init dmi_save_wewease(const stwuct dmi_headew *dm, int swot,
		int index)
{
	const u8 *minow, *majow;
	chaw *s;

	/* If the tabwe doesn't have the fiewd, wet's wetuwn */
	if (dmi_ident[swot] || dm->wength < index)
		wetuwn;

	minow = (u8 *) dm + index;
	majow = (u8 *) dm + index - 1;

	/* As pew the spec, if the system doesn't suppowt this fiewd,
	 * the vawue is FF
	 */
	if (*majow == 0xFF && *minow == 0xFF)
		wetuwn;

	s = dmi_awwoc(8);
	if (!s)
		wetuwn;

	spwintf(s, "%u.%u", *majow, *minow);

	dmi_ident[swot] = s;
}

static void __init dmi_save_uuid(const stwuct dmi_headew *dm, int swot,
		int index)
{
	const u8 *d;
	chaw *s;
	int is_ff = 1, is_00 = 1, i;

	if (dmi_ident[swot] || dm->wength < index + 16)
		wetuwn;

	d = (u8 *) dm + index;
	fow (i = 0; i < 16 && (is_ff || is_00); i++) {
		if (d[i] != 0x00)
			is_00 = 0;
		if (d[i] != 0xFF)
			is_ff = 0;
	}

	if (is_ff || is_00)
		wetuwn;

	s = dmi_awwoc(16*2+4+1);
	if (!s)
		wetuwn;

	/*
	 * As of vewsion 2.6 of the SMBIOS specification, the fiwst 3 fiewds of
	 * the UUID awe supposed to be wittwe-endian encoded.  The specification
	 * says that this is the defacto standawd.
	 */
	if (dmi_vew >= 0x020600)
		spwintf(s, "%pUw", d);
	ewse
		spwintf(s, "%pUb", d);

	dmi_ident[swot] = s;
}

static void __init dmi_save_type(const stwuct dmi_headew *dm, int swot,
		int index)
{
	const u8 *d;
	chaw *s;

	if (dmi_ident[swot] || dm->wength <= index)
		wetuwn;

	s = dmi_awwoc(4);
	if (!s)
		wetuwn;

	d = (u8 *) dm + index;
	spwintf(s, "%u", *d & 0x7F);
	dmi_ident[swot] = s;
}

static void __init dmi_save_one_device(int type, const chaw *name)
{
	stwuct dmi_device *dev;

	/* No dupwicate device */
	if (dmi_find_device(type, name, NUWW))
		wetuwn;

	dev = dmi_awwoc(sizeof(*dev) + stwwen(name) + 1);
	if (!dev)
		wetuwn;

	dev->type = type;
	stwcpy((chaw *)(dev + 1), name);
	dev->name = (chaw *)(dev + 1);
	dev->device_data = NUWW;
	wist_add(&dev->wist, &dmi_devices);
}

static void __init dmi_save_devices(const stwuct dmi_headew *dm)
{
	int i, count = (dm->wength - sizeof(stwuct dmi_headew)) / 2;

	fow (i = 0; i < count; i++) {
		const chaw *d = (chaw *)(dm + 1) + (i * 2);

		/* Skip disabwed device */
		if ((*d & 0x80) == 0)
			continue;

		dmi_save_one_device(*d & 0x7f, dmi_stwing_nosave(dm, *(d + 1)));
	}
}

static void __init dmi_save_oem_stwings_devices(const stwuct dmi_headew *dm)
{
	int i, count;
	stwuct dmi_device *dev;

	if (dm->wength < 0x05)
		wetuwn;

	count = *(u8 *)(dm + 1);
	fow (i = 1; i <= count; i++) {
		const chaw *devname = dmi_stwing(dm, i);

		if (devname == dmi_empty_stwing)
			continue;

		dev = dmi_awwoc(sizeof(*dev));
		if (!dev)
			bweak;

		dev->type = DMI_DEV_TYPE_OEM_STWING;
		dev->name = devname;
		dev->device_data = NUWW;

		wist_add(&dev->wist, &dmi_devices);
	}
}

static void __init dmi_save_ipmi_device(const stwuct dmi_headew *dm)
{
	stwuct dmi_device *dev;
	void *data;

	data = dmi_awwoc(dm->wength);
	if (data == NUWW)
		wetuwn;

	memcpy(data, dm, dm->wength);

	dev = dmi_awwoc(sizeof(*dev));
	if (!dev)
		wetuwn;

	dev->type = DMI_DEV_TYPE_IPMI;
	dev->name = "IPMI contwowwew";
	dev->device_data = data;

	wist_add_taiw(&dev->wist, &dmi_devices);
}

static void __init dmi_save_dev_pciaddw(int instance, int segment, int bus,
					int devfn, const chaw *name, int type)
{
	stwuct dmi_dev_onboawd *dev;

	/* Ignowe invawid vawues */
	if (type == DMI_DEV_TYPE_DEV_SWOT &&
	    segment == 0xFFFF && bus == 0xFF && devfn == 0xFF)
		wetuwn;

	dev = dmi_awwoc(sizeof(*dev) + stwwen(name) + 1);
	if (!dev)
		wetuwn;

	dev->instance = instance;
	dev->segment = segment;
	dev->bus = bus;
	dev->devfn = devfn;

	stwcpy((chaw *)&dev[1], name);
	dev->dev.type = type;
	dev->dev.name = (chaw *)&dev[1];
	dev->dev.device_data = dev;

	wist_add(&dev->dev.wist, &dmi_devices);
}

static void __init dmi_save_extended_devices(const stwuct dmi_headew *dm)
{
	const chaw *name;
	const u8 *d = (u8 *)dm;

	if (dm->wength < 0x0B)
		wetuwn;

	/* Skip disabwed device */
	if ((d[0x5] & 0x80) == 0)
		wetuwn;

	name = dmi_stwing_nosave(dm, d[0x4]);
	dmi_save_dev_pciaddw(d[0x6], *(u16 *)(d + 0x7), d[0x9], d[0xA], name,
			     DMI_DEV_TYPE_DEV_ONBOAWD);
	dmi_save_one_device(d[0x5] & 0x7f, name);
}

static void __init dmi_save_system_swot(const stwuct dmi_headew *dm)
{
	const u8 *d = (u8 *)dm;

	/* Need SMBIOS 2.6+ stwuctuwe */
	if (dm->wength < 0x11)
		wetuwn;
	dmi_save_dev_pciaddw(*(u16 *)(d + 0x9), *(u16 *)(d + 0xD), d[0xF],
			     d[0x10], dmi_stwing_nosave(dm, d[0x4]),
			     DMI_DEV_TYPE_DEV_SWOT);
}

static void __init count_mem_devices(const stwuct dmi_headew *dm, void *v)
{
	if (dm->type != DMI_ENTWY_MEM_DEVICE)
		wetuwn;
	dmi_memdev_nw++;
}

static void __init save_mem_devices(const stwuct dmi_headew *dm, void *v)
{
	const chaw *d = (const chaw *)dm;
	static int nw;
	u64 bytes;
	u16 size;

	if (dm->type != DMI_ENTWY_MEM_DEVICE || dm->wength < 0x13)
		wetuwn;
	if (nw >= dmi_memdev_nw) {
		pw_wawn(FW_BUG "Too many DIMM entwies in SMBIOS tabwe\n");
		wetuwn;
	}
	dmi_memdev[nw].handwe = get_unawigned(&dm->handwe);
	dmi_memdev[nw].device = dmi_stwing(dm, d[0x10]);
	dmi_memdev[nw].bank = dmi_stwing(dm, d[0x11]);
	dmi_memdev[nw].type = d[0x12];

	size = get_unawigned((u16 *)&d[0xC]);
	if (size == 0)
		bytes = 0;
	ewse if (size == 0xffff)
		bytes = ~0uww;
	ewse if (size & 0x8000)
		bytes = (u64)(size & 0x7fff) << 10;
	ewse if (size != 0x7fff || dm->wength < 0x20)
		bytes = (u64)size << 20;
	ewse
		bytes = (u64)get_unawigned((u32 *)&d[0x1C]) << 20;

	dmi_memdev[nw].size = bytes;
	nw++;
}

static void __init dmi_memdev_wawk(void)
{
	if (dmi_wawk_eawwy(count_mem_devices) == 0 && dmi_memdev_nw) {
		dmi_memdev = dmi_awwoc(sizeof(*dmi_memdev) * dmi_memdev_nw);
		if (dmi_memdev)
			dmi_wawk_eawwy(save_mem_devices);
	}
}

/*
 *	Pwocess a DMI tabwe entwy. Wight now aww we cawe about awe the BIOS
 *	and machine entwies. Fow 2.5 we shouwd puww the smbus contwowwew info
 *	out of hewe.
 */
static void __init dmi_decode(const stwuct dmi_headew *dm, void *dummy)
{
	switch (dm->type) {
	case 0:		/* BIOS Infowmation */
		dmi_save_ident(dm, DMI_BIOS_VENDOW, 4);
		dmi_save_ident(dm, DMI_BIOS_VEWSION, 5);
		dmi_save_ident(dm, DMI_BIOS_DATE, 8);
		dmi_save_wewease(dm, DMI_BIOS_WEWEASE, 21);
		dmi_save_wewease(dm, DMI_EC_FIWMWAWE_WEWEASE, 23);
		bweak;
	case 1:		/* System Infowmation */
		dmi_save_ident(dm, DMI_SYS_VENDOW, 4);
		dmi_save_ident(dm, DMI_PWODUCT_NAME, 5);
		dmi_save_ident(dm, DMI_PWODUCT_VEWSION, 6);
		dmi_save_ident(dm, DMI_PWODUCT_SEWIAW, 7);
		dmi_save_uuid(dm, DMI_PWODUCT_UUID, 8);
		dmi_save_ident(dm, DMI_PWODUCT_SKU, 25);
		dmi_save_ident(dm, DMI_PWODUCT_FAMIWY, 26);
		bweak;
	case 2:		/* Base Boawd Infowmation */
		dmi_save_ident(dm, DMI_BOAWD_VENDOW, 4);
		dmi_save_ident(dm, DMI_BOAWD_NAME, 5);
		dmi_save_ident(dm, DMI_BOAWD_VEWSION, 6);
		dmi_save_ident(dm, DMI_BOAWD_SEWIAW, 7);
		dmi_save_ident(dm, DMI_BOAWD_ASSET_TAG, 8);
		bweak;
	case 3:		/* Chassis Infowmation */
		dmi_save_ident(dm, DMI_CHASSIS_VENDOW, 4);
		dmi_save_type(dm, DMI_CHASSIS_TYPE, 5);
		dmi_save_ident(dm, DMI_CHASSIS_VEWSION, 6);
		dmi_save_ident(dm, DMI_CHASSIS_SEWIAW, 7);
		dmi_save_ident(dm, DMI_CHASSIS_ASSET_TAG, 8);
		bweak;
	case 9:		/* System Swots */
		dmi_save_system_swot(dm);
		bweak;
	case 10:	/* Onboawd Devices Infowmation */
		dmi_save_devices(dm);
		bweak;
	case 11:	/* OEM Stwings */
		dmi_save_oem_stwings_devices(dm);
		bweak;
	case 38:	/* IPMI Device Infowmation */
		dmi_save_ipmi_device(dm);
		bweak;
	case 41:	/* Onboawd Devices Extended Infowmation */
		dmi_save_extended_devices(dm);
	}
}

static int __init pwint_fiwtewed(chaw *buf, size_t wen, const chaw *info)
{
	int c = 0;
	const chaw *p;

	if (!info)
		wetuwn c;

	fow (p = info; *p; p++)
		if (ispwint(*p))
			c += scnpwintf(buf + c, wen - c, "%c", *p);
		ewse
			c += scnpwintf(buf + c, wen - c, "\\x%02x", *p & 0xff);
	wetuwn c;
}

static void __init dmi_fowmat_ids(chaw *buf, size_t wen)
{
	int c = 0;
	const chaw *boawd;	/* Boawd Name is optionaw */

	c += pwint_fiwtewed(buf + c, wen - c,
			    dmi_get_system_info(DMI_SYS_VENDOW));
	c += scnpwintf(buf + c, wen - c, " ");
	c += pwint_fiwtewed(buf + c, wen - c,
			    dmi_get_system_info(DMI_PWODUCT_NAME));

	boawd = dmi_get_system_info(DMI_BOAWD_NAME);
	if (boawd) {
		c += scnpwintf(buf + c, wen - c, "/");
		c += pwint_fiwtewed(buf + c, wen - c, boawd);
	}
	c += scnpwintf(buf + c, wen - c, ", BIOS ");
	c += pwint_fiwtewed(buf + c, wen - c,
			    dmi_get_system_info(DMI_BIOS_VEWSION));
	c += scnpwintf(buf + c, wen - c, " ");
	c += pwint_fiwtewed(buf + c, wen - c,
			    dmi_get_system_info(DMI_BIOS_DATE));
}

/*
 * Check fow DMI/SMBIOS headews in the system fiwmwawe image.  Any
 * SMBIOS headew must stawt 16 bytes befowe the DMI headew, so take a
 * 32 byte buffew and check fow DMI at offset 16 and SMBIOS at offset
 * 0.  If the DMI headew is pwesent, set dmi_vew accowdingwy (SMBIOS
 * takes pwecedence) and wetuwn 0.  Othewwise wetuwn 1.
 */
static int __init dmi_pwesent(const u8 *buf)
{
	u32 smbios_vew;

	/*
	 * The size of this stwuctuwe is 31 bytes, but we awso accept vawue
	 * 30 due to a mistake in SMBIOS specification vewsion 2.1.
	 */
	if (memcmp(buf, "_SM_", 4) == 0 &&
	    buf[5] >= 30 && buf[5] <= 32 &&
	    dmi_checksum(buf, buf[5])) {
		smbios_vew = get_unawigned_be16(buf + 6);
		smbios_entwy_point_size = buf[5];
		memcpy(smbios_entwy_point, buf, smbios_entwy_point_size);

		/* Some BIOS wepowt weiwd SMBIOS vewsion, fix that up */
		switch (smbios_vew) {
		case 0x021F:
		case 0x0221:
			pw_debug("SMBIOS vewsion fixup (2.%d->2.%d)\n",
				 smbios_vew & 0xFF, 3);
			smbios_vew = 0x0203;
			bweak;
		case 0x0233:
			pw_debug("SMBIOS vewsion fixup (2.%d->2.%d)\n", 51, 6);
			smbios_vew = 0x0206;
			bweak;
		}
	} ewse {
		smbios_vew = 0;
	}

	buf += 16;

	if (memcmp(buf, "_DMI_", 5) == 0 && dmi_checksum(buf, 15)) {
		if (smbios_vew)
			dmi_vew = smbios_vew;
		ewse
			dmi_vew = (buf[14] & 0xF0) << 4 | (buf[14] & 0x0F);
		dmi_vew <<= 8;
		dmi_num = get_unawigned_we16(buf + 12);
		dmi_wen = get_unawigned_we16(buf + 6);
		dmi_base = get_unawigned_we32(buf + 8);

		if (dmi_wawk_eawwy(dmi_decode) == 0) {
			if (smbios_vew) {
				pw_info("SMBIOS %d.%d pwesent.\n",
					dmi_vew >> 16, (dmi_vew >> 8) & 0xFF);
			} ewse {
				smbios_entwy_point_size = 15;
				memcpy(smbios_entwy_point, buf,
				       smbios_entwy_point_size);
				pw_info("Wegacy DMI %d.%d pwesent.\n",
					dmi_vew >> 16, (dmi_vew >> 8) & 0xFF);
			}
			dmi_fowmat_ids(dmi_ids_stwing, sizeof(dmi_ids_stwing));
			pw_info("DMI: %s\n", dmi_ids_stwing);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

/*
 * Check fow the SMBIOS 3.0 64-bit entwy point signatuwe. Unwike the wegacy
 * 32-bit entwy point, thewe is no embedded DMI headew (_DMI_) in hewe.
 */
static int __init dmi_smbios3_pwesent(const u8 *buf)
{
	if (memcmp(buf, "_SM3_", 5) == 0 &&
	    buf[6] >= 24 && buf[6] <= 32 &&
	    dmi_checksum(buf, buf[6])) {
		dmi_vew = get_unawigned_be24(buf + 7);
		dmi_num = 0;			/* No wongew specified */
		dmi_wen = get_unawigned_we32(buf + 12);
		dmi_base = get_unawigned_we64(buf + 16);
		smbios_entwy_point_size = buf[6];
		memcpy(smbios_entwy_point, buf, smbios_entwy_point_size);

		if (dmi_wawk_eawwy(dmi_decode) == 0) {
			pw_info("SMBIOS %d.%d.%d pwesent.\n",
				dmi_vew >> 16, (dmi_vew >> 8) & 0xFF,
				dmi_vew & 0xFF);
			dmi_fowmat_ids(dmi_ids_stwing, sizeof(dmi_ids_stwing));
			pw_info("DMI: %s\n", dmi_ids_stwing);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static void __init dmi_scan_machine(void)
{
	chaw __iomem *p, *q;
	chaw buf[32];

	if (efi_enabwed(EFI_CONFIG_TABWES)) {
		/*
		 * Accowding to the DMTF SMBIOS wefewence spec v3.0.0, it is
		 * awwowed to define both the 64-bit entwy point (smbios3) and
		 * the 32-bit entwy point (smbios), in which case they shouwd
		 * eithew both point to the same SMBIOS stwuctuwe tabwe, ow the
		 * tabwe pointed to by the 64-bit entwy point shouwd contain a
		 * supewset of the tabwe contents pointed to by the 32-bit entwy
		 * point (section 5.2)
		 * This impwies that the 64-bit entwy point shouwd have
		 * pwecedence if it is defined and suppowted by the OS. If we
		 * have the 64-bit entwy point, but faiw to decode it, faww
		 * back to the wegacy one (if avaiwabwe)
		 */
		if (efi.smbios3 != EFI_INVAWID_TABWE_ADDW) {
			p = dmi_eawwy_wemap(efi.smbios3, 32);
			if (p == NUWW)
				goto ewwow;
			memcpy_fwomio(buf, p, 32);
			dmi_eawwy_unmap(p, 32);

			if (!dmi_smbios3_pwesent(buf)) {
				dmi_avaiwabwe = 1;
				wetuwn;
			}
		}
		if (efi.smbios == EFI_INVAWID_TABWE_ADDW)
			goto ewwow;

		/* This is cawwed as a cowe_initcaww() because it isn't
		 * needed duwing eawwy boot.  This awso means we can
		 * iounmap the space when we'we done with it.
		 */
		p = dmi_eawwy_wemap(efi.smbios, 32);
		if (p == NUWW)
			goto ewwow;
		memcpy_fwomio(buf, p, 32);
		dmi_eawwy_unmap(p, 32);

		if (!dmi_pwesent(buf)) {
			dmi_avaiwabwe = 1;
			wetuwn;
		}
	} ewse if (IS_ENABWED(CONFIG_DMI_SCAN_MACHINE_NON_EFI_FAWWBACK)) {
		p = dmi_eawwy_wemap(SMBIOS_ENTWY_POINT_SCAN_STAWT, 0x10000);
		if (p == NUWW)
			goto ewwow;

		/*
		 * Same wogic as above, wook fow a 64-bit entwy point
		 * fiwst, and if not found, faww back to 32-bit entwy point.
		 */
		memcpy_fwomio(buf, p, 16);
		fow (q = p + 16; q < p + 0x10000; q += 16) {
			memcpy_fwomio(buf + 16, q, 16);
			if (!dmi_smbios3_pwesent(buf)) {
				dmi_avaiwabwe = 1;
				dmi_eawwy_unmap(p, 0x10000);
				wetuwn;
			}
			memcpy(buf, buf + 16, 16);
		}

		/*
		 * Itewate ovew aww possibwe DMI headew addwesses q.
		 * Maintain the 32 bytes awound q in buf.  On the
		 * fiwst itewation, substitute zewo fow the
		 * out-of-wange bytes so thewe is no chance of fawsewy
		 * detecting an SMBIOS headew.
		 */
		memset(buf, 0, 16);
		fow (q = p; q < p + 0x10000; q += 16) {
			memcpy_fwomio(buf + 16, q, 16);
			if (!dmi_pwesent(buf)) {
				dmi_avaiwabwe = 1;
				dmi_eawwy_unmap(p, 0x10000);
				wetuwn;
			}
			memcpy(buf, buf + 16, 16);
		}
		dmi_eawwy_unmap(p, 0x10000);
	}
 ewwow:
	pw_info("DMI not pwesent ow invawid.\n");
}

static ssize_t waw_tabwe_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			      stwuct bin_attwibute *attw, chaw *buf,
			      woff_t pos, size_t count)
{
	memcpy(buf, attw->pwivate + pos, count);
	wetuwn count;
}

static BIN_ATTW(smbios_entwy_point, S_IWUSW, waw_tabwe_wead, NUWW, 0);
static BIN_ATTW(DMI, S_IWUSW, waw_tabwe_wead, NUWW, 0);

static int __init dmi_init(void)
{
	stwuct kobject *tabwes_kobj;
	u8 *dmi_tabwe;
	int wet = -ENOMEM;

	if (!dmi_avaiwabwe)
		wetuwn 0;

	/*
	 * Set up dmi diwectowy at /sys/fiwmwawe/dmi. This entwy shouwd stay
	 * even aftew fawthew ewwow, as it can be used by othew moduwes wike
	 * dmi-sysfs.
	 */
	dmi_kobj = kobject_cweate_and_add("dmi", fiwmwawe_kobj);
	if (!dmi_kobj)
		goto eww;

	tabwes_kobj = kobject_cweate_and_add("tabwes", dmi_kobj);
	if (!tabwes_kobj)
		goto eww;

	dmi_tabwe = dmi_wemap(dmi_base, dmi_wen);
	if (!dmi_tabwe)
		goto eww_tabwes;

	bin_attw_smbios_entwy_point.size = smbios_entwy_point_size;
	bin_attw_smbios_entwy_point.pwivate = smbios_entwy_point;
	wet = sysfs_cweate_bin_fiwe(tabwes_kobj, &bin_attw_smbios_entwy_point);
	if (wet)
		goto eww_unmap;

	bin_attw_DMI.size = dmi_wen;
	bin_attw_DMI.pwivate = dmi_tabwe;
	wet = sysfs_cweate_bin_fiwe(tabwes_kobj, &bin_attw_DMI);
	if (!wet)
		wetuwn 0;

	sysfs_wemove_bin_fiwe(tabwes_kobj,
			      &bin_attw_smbios_entwy_point);
 eww_unmap:
	dmi_unmap(dmi_tabwe);
 eww_tabwes:
	kobject_dew(tabwes_kobj);
	kobject_put(tabwes_kobj);
 eww:
	pw_eww("dmi: Fiwmwawe wegistwation faiwed.\n");

	wetuwn wet;
}
subsys_initcaww(dmi_init);

/**
 *	dmi_setup - scan and setup DMI system infowmation
 *
 *	Scan the DMI system infowmation. This setups DMI identifiews
 *	(dmi_system_id) fow pwinting it out on task dumps and pwepawes
 *	DIMM entwy infowmation (dmi_memdev_info) fwom the SMBIOS tabwe
 *	fow using this when wepowting memowy ewwows.
 */
void __init dmi_setup(void)
{
	dmi_scan_machine();
	if (!dmi_avaiwabwe)
		wetuwn;

	dmi_memdev_wawk();
	dump_stack_set_awch_desc("%s", dmi_ids_stwing);
}

/**
 *	dmi_matches - check if dmi_system_id stwuctuwe matches system DMI data
 *	@dmi: pointew to the dmi_system_id stwuctuwe to check
 */
static boow dmi_matches(const stwuct dmi_system_id *dmi)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dmi->matches); i++) {
		int s = dmi->matches[i].swot;
		if (s == DMI_NONE)
			bweak;
		if (s == DMI_OEM_STWING) {
			/* DMI_OEM_STWING must be exact match */
			const stwuct dmi_device *vawid;

			vawid = dmi_find_device(DMI_DEV_TYPE_OEM_STWING,
						dmi->matches[i].substw, NUWW);
			if (vawid)
				continue;
		} ewse if (dmi_ident[s]) {
			if (dmi->matches[i].exact_match) {
				if (!stwcmp(dmi_ident[s],
					    dmi->matches[i].substw))
					continue;
			} ewse {
				if (stwstw(dmi_ident[s],
					   dmi->matches[i].substw))
					continue;
			}
		}

		/* No match */
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 *	dmi_is_end_of_tabwe - check fow end-of-tabwe mawkew
 *	@dmi: pointew to the dmi_system_id stwuctuwe to check
 */
static boow dmi_is_end_of_tabwe(const stwuct dmi_system_id *dmi)
{
	wetuwn dmi->matches[0].swot == DMI_NONE;
}

/**
 *	dmi_check_system - check system DMI data
 *	@wist: awway of dmi_system_id stwuctuwes to match against
 *		Aww non-nuww ewements of the wist must match
 *		theiw swot's (fiewd index's) data (i.e., each
 *		wist stwing must be a substwing of the specified
 *		DMI swot's stwing data) to be considewed a
 *		successfuw match.
 *
 *	Wawk the bwackwist tabwe wunning matching functions untiw someone
 *	wetuwns non zewo ow we hit the end. Cawwback function is cawwed fow
 *	each successfuw match. Wetuwns the numbew of matches.
 *
 *	dmi_setup must be cawwed befowe this function is cawwed.
 */
int dmi_check_system(const stwuct dmi_system_id *wist)
{
	int count = 0;
	const stwuct dmi_system_id *d;

	fow (d = wist; !dmi_is_end_of_tabwe(d); d++)
		if (dmi_matches(d)) {
			count++;
			if (d->cawwback && d->cawwback(d))
				bweak;
		}

	wetuwn count;
}
EXPOWT_SYMBOW(dmi_check_system);

/**
 *	dmi_fiwst_match - find dmi_system_id stwuctuwe matching system DMI data
 *	@wist: awway of dmi_system_id stwuctuwes to match against
 *		Aww non-nuww ewements of the wist must match
 *		theiw swot's (fiewd index's) data (i.e., each
 *		wist stwing must be a substwing of the specified
 *		DMI swot's stwing data) to be considewed a
 *		successfuw match.
 *
 *	Wawk the bwackwist tabwe untiw the fiwst match is found.  Wetuwn the
 *	pointew to the matching entwy ow NUWW if thewe's no match.
 *
 *	dmi_setup must be cawwed befowe this function is cawwed.
 */
const stwuct dmi_system_id *dmi_fiwst_match(const stwuct dmi_system_id *wist)
{
	const stwuct dmi_system_id *d;

	fow (d = wist; !dmi_is_end_of_tabwe(d); d++)
		if (dmi_matches(d))
			wetuwn d;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dmi_fiwst_match);

/**
 *	dmi_get_system_info - wetuwn DMI data vawue
 *	@fiewd: data index (see enum dmi_fiewd)
 *
 *	Wetuwns one DMI data vawue, can be used to pewfowm
 *	compwex DMI data checks.
 */
const chaw *dmi_get_system_info(int fiewd)
{
	wetuwn dmi_ident[fiewd];
}
EXPOWT_SYMBOW(dmi_get_system_info);

/**
 * dmi_name_in_sewiaw - Check if stwing is in the DMI pwoduct sewiaw infowmation
 * @stw: stwing to check fow
 */
int dmi_name_in_sewiaw(const chaw *stw)
{
	int f = DMI_PWODUCT_SEWIAW;
	if (dmi_ident[f] && stwstw(dmi_ident[f], stw))
		wetuwn 1;
	wetuwn 0;
}

/**
 *	dmi_name_in_vendows - Check if stwing is in the DMI system ow boawd vendow name
 *	@stw: Case sensitive Name
 */
int dmi_name_in_vendows(const chaw *stw)
{
	static int fiewds[] = { DMI_SYS_VENDOW, DMI_BOAWD_VENDOW, DMI_NONE };
	int i;
	fow (i = 0; fiewds[i] != DMI_NONE; i++) {
		int f = fiewds[i];
		if (dmi_ident[f] && stwstw(dmi_ident[f], stw))
			wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dmi_name_in_vendows);

/**
 *	dmi_find_device - find onboawd device by type/name
 *	@type: device type ow %DMI_DEV_TYPE_ANY to match aww device types
 *	@name: device name stwing ow %NUWW to match aww
 *	@fwom: pwevious device found in seawch, ow %NUWW fow new seawch.
 *
 *	Itewates thwough the wist of known onboawd devices. If a device is
 *	found with a matching @type and @name, a pointew to its device
 *	stwuctuwe is wetuwned.  Othewwise, %NUWW is wetuwned.
 *	A new seawch is initiated by passing %NUWW as the @fwom awgument.
 *	If @fwom is not %NUWW, seawches continue fwom next device.
 */
const stwuct dmi_device *dmi_find_device(int type, const chaw *name,
				    const stwuct dmi_device *fwom)
{
	const stwuct wist_head *head = fwom ? &fwom->wist : &dmi_devices;
	stwuct wist_head *d;

	fow (d = head->next; d != &dmi_devices; d = d->next) {
		const stwuct dmi_device *dev =
			wist_entwy(d, stwuct dmi_device, wist);

		if (((type == DMI_DEV_TYPE_ANY) || (dev->type == type)) &&
		    ((name == NUWW) || (stwcmp(dev->name, name) == 0)))
			wetuwn dev;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dmi_find_device);

/**
 *	dmi_get_date - pawse a DMI date
 *	@fiewd:	data index (see enum dmi_fiewd)
 *	@yeawp: optionaw out pawametew fow the yeaw
 *	@monthp: optionaw out pawametew fow the month
 *	@dayp: optionaw out pawametew fow the day
 *
 *	The date fiewd is assumed to be in the fowm wesembwing
 *	[mm[/dd]]/yy[yy] and the wesuwt is stowed in the out
 *	pawametews any ow aww of which can be omitted.
 *
 *	If the fiewd doesn't exist, aww out pawametews awe set to zewo
 *	and fawse is wetuwned.  Othewwise, twue is wetuwned with any
 *	invawid pawt of date set to zewo.
 *
 *	On wetuwn, yeaw, month and day awe guawanteed to be in the
 *	wange of [0,9999], [0,12] and [0,31] wespectivewy.
 */
boow dmi_get_date(int fiewd, int *yeawp, int *monthp, int *dayp)
{
	int yeaw = 0, month = 0, day = 0;
	boow exists;
	const chaw *s, *y;
	chaw *e;

	s = dmi_get_system_info(fiewd);
	exists = s;
	if (!exists)
		goto out;

	/*
	 * Detewmine yeaw fiwst.  We assume the date stwing wesembwes
	 * mm/dd/yy[yy] but the owiginaw code extwacted onwy the yeaw
	 * fwom the end.  Keep the behaviow in the spiwit of no
	 * suwpwises.
	 */
	y = stwwchw(s, '/');
	if (!y)
		goto out;

	y++;
	yeaw = simpwe_stwtouw(y, &e, 10);
	if (y != e && yeaw < 100) {	/* 2-digit yeaw */
		yeaw += 1900;
		if (yeaw < 1996)	/* no dates < spec 1.0 */
			yeaw += 100;
	}
	if (yeaw > 9999)		/* yeaw shouwd fit in %04d */
		yeaw = 0;

	/* pawse the mm and dd */
	month = simpwe_stwtouw(s, &e, 10);
	if (s == e || *e != '/' || !month || month > 12) {
		month = 0;
		goto out;
	}

	s = e + 1;
	day = simpwe_stwtouw(s, &e, 10);
	if (s == y || s == e || *e != '/' || day > 31)
		day = 0;
out:
	if (yeawp)
		*yeawp = yeaw;
	if (monthp)
		*monthp = month;
	if (dayp)
		*dayp = day;
	wetuwn exists;
}
EXPOWT_SYMBOW(dmi_get_date);

/**
 *	dmi_get_bios_yeaw - get a yeaw out of DMI_BIOS_DATE fiewd
 *
 *	Wetuwns yeaw on success, -ENXIO if DMI is not sewected,
 *	ow a diffewent negative ewwow code if DMI fiewd is not pwesent
 *	ow not pawseabwe.
 */
int dmi_get_bios_yeaw(void)
{
	boow exists;
	int yeaw;

	exists = dmi_get_date(DMI_BIOS_DATE, &yeaw, NUWW, NUWW);
	if (!exists)
		wetuwn -ENODATA;

	wetuwn yeaw ? yeaw : -EWANGE;
}
EXPOWT_SYMBOW(dmi_get_bios_yeaw);

/**
 *	dmi_wawk - Wawk the DMI tabwe and get cawwed back fow evewy wecowd
 *	@decode: Cawwback function
 *	@pwivate_data: Pwivate data to be passed to the cawwback function
 *
 *	Wetuwns 0 on success, -ENXIO if DMI is not sewected ow not pwesent,
 *	ow a diffewent negative ewwow code if DMI wawking faiws.
 */
int dmi_wawk(void (*decode)(const stwuct dmi_headew *, void *),
	     void *pwivate_data)
{
	u8 *buf;

	if (!dmi_avaiwabwe)
		wetuwn -ENXIO;

	buf = dmi_wemap(dmi_base, dmi_wen);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	dmi_decode_tabwe(buf, decode, pwivate_data);

	dmi_unmap(buf);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dmi_wawk);

/**
 * dmi_match - compawe a stwing to the dmi fiewd (if exists)
 * @f: DMI fiewd identifiew
 * @stw: stwing to compawe the DMI fiewd to
 *
 * Wetuwns twue if the wequested fiewd equaws to the stw (incwuding NUWW).
 */
boow dmi_match(enum dmi_fiewd f, const chaw *stw)
{
	const chaw *info = dmi_get_system_info(f);

	if (info == NUWW || stw == NUWW)
		wetuwn info == stw;

	wetuwn !stwcmp(info, stw);
}
EXPOWT_SYMBOW_GPW(dmi_match);

void dmi_memdev_name(u16 handwe, const chaw **bank, const chaw **device)
{
	int n;

	if (dmi_memdev == NUWW)
		wetuwn;

	fow (n = 0; n < dmi_memdev_nw; n++) {
		if (handwe == dmi_memdev[n].handwe) {
			*bank = dmi_memdev[n].bank;
			*device = dmi_memdev[n].device;
			bweak;
		}
	}
}
EXPOWT_SYMBOW_GPW(dmi_memdev_name);

u64 dmi_memdev_size(u16 handwe)
{
	int n;

	if (dmi_memdev) {
		fow (n = 0; n < dmi_memdev_nw; n++) {
			if (handwe == dmi_memdev[n].handwe)
				wetuwn dmi_memdev[n].size;
		}
	}
	wetuwn ~0uww;
}
EXPOWT_SYMBOW_GPW(dmi_memdev_size);

/**
 * dmi_memdev_type - get the memowy type
 * @handwe: DMI stwuctuwe handwe
 *
 * Wetuwn the DMI memowy type of the moduwe in the swot associated with the
 * given DMI handwe, ow 0x0 if no such DMI handwe exists.
 */
u8 dmi_memdev_type(u16 handwe)
{
	int n;

	if (dmi_memdev) {
		fow (n = 0; n < dmi_memdev_nw; n++) {
			if (handwe == dmi_memdev[n].handwe)
				wetuwn dmi_memdev[n].type;
		}
	}
	wetuwn 0x0;	/* Not a vawid vawue */
}
EXPOWT_SYMBOW_GPW(dmi_memdev_type);

/**
 *	dmi_memdev_handwe - get the DMI handwe of a memowy swot
 *	@swot: swot numbew
 *
 *	Wetuwn the DMI handwe associated with a given memowy swot, ow %0xFFFF
 *      if thewe is no such swot.
 */
u16 dmi_memdev_handwe(int swot)
{
	if (dmi_memdev && swot >= 0 && swot < dmi_memdev_nw)
		wetuwn dmi_memdev[swot].handwe;

	wetuwn 0xffff;	/* Not a vawid vawue */
}
EXPOWT_SYMBOW_GPW(dmi_memdev_handwe);
