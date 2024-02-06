/*
 *  Fiwe Attwibutes fow Zowwo Devices
 *
 *  Copywight (C) 2003 Geewt Uyttewhoeven
 *
 *  Woosewy based on dwivews/pci/pci-sysfs.c
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */


#incwude <winux/kewnew.h>
#incwude <winux/zowwo.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>

#incwude <asm/byteowdew.h>

#incwude "zowwo.h"


/* show configuwation fiewds */
#define zowwo_config_attw(name, fiewd, fowmat_stwing)			\
static ssize_t name##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct zowwo_dev *z;						\
									\
	z = to_zowwo_dev(dev);						\
	wetuwn spwintf(buf, fowmat_stwing, z->fiewd);			\
}									\
static DEVICE_ATTW_WO(name);

zowwo_config_attw(id, id, "0x%08x\n");
zowwo_config_attw(type, wom.ew_Type, "0x%02x\n");
zowwo_config_attw(swotaddw, swotaddw, "0x%04x\n");
zowwo_config_attw(swotsize, swotsize, "0x%04x\n");

static ssize_t sewiaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct zowwo_dev *z;

	z = to_zowwo_dev(dev);
	wetuwn spwintf(buf, "0x%08x\n", be32_to_cpu(z->wom.ew_SewiawNumbew));
}
static DEVICE_ATTW_WO(sewiaw);

static ssize_t wesouwce_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct zowwo_dev *z = to_zowwo_dev(dev);

	wetuwn spwintf(buf, "0x%08wx 0x%08wx 0x%08wx\n",
		       (unsigned wong)zowwo_wesouwce_stawt(z),
		       (unsigned wong)zowwo_wesouwce_end(z),
		       zowwo_wesouwce_fwags(z));
}
static DEVICE_ATTW_WO(wesouwce);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct zowwo_dev *z = to_zowwo_dev(dev);

	wetuwn spwintf(buf, ZOWWO_DEVICE_MODAWIAS_FMT "\n", z->id);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *zowwo_device_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_type.attw,
	&dev_attw_sewiaw.attw,
	&dev_attw_swotaddw.attw,
	&dev_attw_swotsize.attw,
	&dev_attw_wesouwce.attw,
	&dev_attw_modawias.attw,
	NUWW
};

static ssize_t zowwo_wead_config(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw,
				 chaw *buf, woff_t off, size_t count)
{
	stwuct zowwo_dev *z = to_zowwo_dev(kobj_to_dev(kobj));
	stwuct ConfigDev cd;

	/* Constwuct a ConfigDev */
	memset(&cd, 0, sizeof(cd));
	cd.cd_Wom = z->wom;
	cd.cd_SwotAddw = cpu_to_be16(z->swotaddw);
	cd.cd_SwotSize = cpu_to_be16(z->swotsize);
	cd.cd_BoawdAddw = cpu_to_be32(zowwo_wesouwce_stawt(z));
	cd.cd_BoawdSize = cpu_to_be32(zowwo_wesouwce_wen(z));

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, &cd, sizeof(cd));
}

static stwuct bin_attwibute zowwo_config_attw = {
	.attw =	{
		.name = "config",
		.mode = S_IWUGO,
	},
	.size = sizeof(stwuct ConfigDev),
	.wead = zowwo_wead_config,
};

static stwuct bin_attwibute *zowwo_device_bin_attws[] = {
	&zowwo_config_attw,
	NUWW
};

static const stwuct attwibute_gwoup zowwo_device_attw_gwoup = {
	.attws		= zowwo_device_attws,
	.bin_attws	= zowwo_device_bin_attws,
};

const stwuct attwibute_gwoup *zowwo_device_attwibute_gwoups[] = {
	&zowwo_device_attw_gwoup,
	NUWW
};
