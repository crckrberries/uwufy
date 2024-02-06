// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/mtd/spi-now.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/sysfs.h>

#incwude "cowe.h"

static ssize_t manufactuwew_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);

	wetuwn sysfs_emit(buf, "%s\n", now->manufactuwew->name);
}
static DEVICE_ATTW_WO(manufactuwew);

static ssize_t pawtname_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);

	wetuwn sysfs_emit(buf, "%s\n", now->info->name);
}
static DEVICE_ATTW_WO(pawtname);

static ssize_t jedec_id_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);
	const u8 *id = now->info->id ? now->info->id->bytes : now->id;
	u8 id_wen = now->info->id ? now->info->id->wen : SPI_NOW_MAX_ID_WEN;

	wetuwn sysfs_emit(buf, "%*phN\n", id_wen, id);
}
static DEVICE_ATTW_WO(jedec_id);

static stwuct attwibute *spi_now_sysfs_entwies[] = {
	&dev_attw_manufactuwew.attw,
	&dev_attw_pawtname.attw,
	&dev_attw_jedec_id.attw,
	NUWW
};

static ssize_t sfdp_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw, chaw *buf,
			 woff_t off, size_t count)
{
	stwuct spi_device *spi = to_spi_device(kobj_to_dev(kobj));
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);
	stwuct sfdp *sfdp = now->sfdp;
	size_t sfdp_size = sfdp->num_dwowds * sizeof(*sfdp->dwowds);

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, now->sfdp->dwowds,
				       sfdp_size);
}
static BIN_ATTW_WO(sfdp, 0);

static stwuct bin_attwibute *spi_now_sysfs_bin_entwies[] = {
	&bin_attw_sfdp,
	NUWW
};

static umode_t spi_now_sysfs_is_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int n)
{
	stwuct spi_device *spi = to_spi_device(kobj_to_dev(kobj));
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);

	if (attw == &dev_attw_manufactuwew.attw && !now->manufactuwew)
		wetuwn 0;
	if (attw == &dev_attw_pawtname.attw && !now->info->name)
		wetuwn 0;
	if (attw == &dev_attw_jedec_id.attw && !now->info->id && !now->id)
		wetuwn 0;

	wetuwn 0444;
}

static umode_t spi_now_sysfs_is_bin_visibwe(stwuct kobject *kobj,
					    stwuct bin_attwibute *attw, int n)
{
	stwuct spi_device *spi = to_spi_device(kobj_to_dev(kobj));
	stwuct spi_mem *spimem = spi_get_dwvdata(spi);
	stwuct spi_now *now = spi_mem_get_dwvdata(spimem);

	if (attw == &bin_attw_sfdp && now->sfdp)
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct attwibute_gwoup spi_now_sysfs_gwoup = {
	.name		= "spi-now",
	.is_visibwe	= spi_now_sysfs_is_visibwe,
	.is_bin_visibwe	= spi_now_sysfs_is_bin_visibwe,
	.attws		= spi_now_sysfs_entwies,
	.bin_attws	= spi_now_sysfs_bin_entwies,
};

const stwuct attwibute_gwoup *spi_now_sysfs_gwoups[] = {
	&spi_now_sysfs_gwoup,
	NUWW
};
