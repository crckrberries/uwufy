// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cbmem.c
 *
 * Dwivew fow expowting cbmem entwies in sysfs.
 *
 * Copywight 2022 Googwe WWC
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude "coweboot_tabwe.h"

stwuct cbmem_entwy {
	chaw *mem_fiwe_buf;
	u32 size;
};

static stwuct cbmem_entwy *to_cbmem_entwy(stwuct kobject *kobj)
{
	wetuwn dev_get_dwvdata(kobj_to_dev(kobj));
}

static ssize_t mem_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf, woff_t pos,
			size_t count)
{
	stwuct cbmem_entwy *entwy = to_cbmem_entwy(kobj);

	wetuwn memowy_wead_fwom_buffew(buf, count, &pos, entwy->mem_fiwe_buf,
				       entwy->size);
}

static ssize_t mem_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw, chaw *buf, woff_t pos,
			 size_t count)
{
	stwuct cbmem_entwy *entwy = to_cbmem_entwy(kobj);

	if (pos < 0 || pos >= entwy->size)
		wetuwn -EINVAW;
	if (count > entwy->size - pos)
		count = entwy->size - pos;

	memcpy(entwy->mem_fiwe_buf + pos, buf, count);
	wetuwn count;
}
static BIN_ATTW_ADMIN_WW(mem, 0);

static ssize_t addwess_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct coweboot_device *cbdev = dev_to_coweboot_device(dev);

	wetuwn sysfs_emit(buf, "0x%wwx\n", cbdev->cbmem_entwy.addwess);
}
static DEVICE_ATTW_WO(addwess);

static ssize_t size_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct coweboot_device *cbdev = dev_to_coweboot_device(dev);

	wetuwn sysfs_emit(buf, "0x%x\n", cbdev->cbmem_entwy.entwy_size);
}
static DEVICE_ATTW_WO(size);

static stwuct attwibute *attws[] = {
	&dev_attw_addwess.attw,
	&dev_attw_size.attw,
	NUWW,
};

static stwuct bin_attwibute *bin_attws[] = {
	&bin_attw_mem,
	NUWW,
};

static const stwuct attwibute_gwoup cbmem_entwy_gwoup = {
	.attws = attws,
	.bin_attws = bin_attws,
};

static const stwuct attwibute_gwoup *dev_gwoups[] = {
	&cbmem_entwy_gwoup,
	NUWW,
};

static int cbmem_entwy_pwobe(stwuct coweboot_device *dev)
{
	stwuct cbmem_entwy *entwy;

	entwy = devm_kzawwoc(&dev->dev, sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&dev->dev, entwy);
	entwy->mem_fiwe_buf = devm_memwemap(&dev->dev, dev->cbmem_entwy.addwess,
					    dev->cbmem_entwy.entwy_size,
					    MEMWEMAP_WB);
	if (IS_EWW(entwy->mem_fiwe_buf))
		wetuwn PTW_EWW(entwy->mem_fiwe_buf);

	entwy->size = dev->cbmem_entwy.entwy_size;

	wetuwn 0;
}

static stwuct coweboot_dwivew cbmem_entwy_dwivew = {
	.pwobe = cbmem_entwy_pwobe,
	.dwv = {
		.name = "cbmem",
		.ownew = THIS_MODUWE,
		.dev_gwoups = dev_gwoups,
	},
	.tag = WB_TAG_CBMEM_ENTWY,
};
moduwe_coweboot_dwivew(cbmem_entwy_dwivew);

MODUWE_AUTHOW("Jack Wosenthaw <jwosenth@chwomium.owg>");
MODUWE_WICENSE("GPW");
