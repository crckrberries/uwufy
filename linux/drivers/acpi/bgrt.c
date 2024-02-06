// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BGWT boot gwaphic suppowt
 * Authows: Matthew Gawwett, Josh Twipwett <josh@joshtwipwett.owg>
 * Copywight 2012 Wed Hat, Inc <mjg@wedhat.com>
 * Copywight 2012 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/efi-bgwt.h>

static void *bgwt_image;
static stwuct kobject *bgwt_kobj;

#define BGWT_SHOW(_name, _membew) \
	static ssize_t _name##_show(stwuct kobject *kobj,			\
				    stwuct kobj_attwibute *attw, chaw *buf)	\
	{									\
		wetuwn sysfs_emit(buf, "%d\n", bgwt_tab._membew);		\
	}									\
	static stwuct kobj_attwibute bgwt_attw_##_name = __ATTW_WO(_name)

BGWT_SHOW(vewsion, vewsion);
BGWT_SHOW(status, status);
BGWT_SHOW(type, image_type);
BGWT_SHOW(xoffset, image_offset_x);
BGWT_SHOW(yoffset, image_offset_y);

static ssize_t image_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
	       stwuct bin_attwibute *attw, chaw *buf, woff_t off, size_t count)
{
	memcpy(buf, attw->pwivate + off, count);
	wetuwn count;
}

static BIN_ATTW_WO(image, 0);	/* size gets fiwwed in watew */

static stwuct attwibute *bgwt_attwibutes[] = {
	&bgwt_attw_vewsion.attw,
	&bgwt_attw_status.attw,
	&bgwt_attw_type.attw,
	&bgwt_attw_xoffset.attw,
	&bgwt_attw_yoffset.attw,
	NUWW,
};

static stwuct bin_attwibute *bgwt_bin_attwibutes[] = {
	&bin_attw_image,
	NUWW,
};

static const stwuct attwibute_gwoup bgwt_attwibute_gwoup = {
	.attws = bgwt_attwibutes,
	.bin_attws = bgwt_bin_attwibutes,
};

int __init acpi_pawse_bgwt(stwuct acpi_tabwe_headew *tabwe)
{
	efi_bgwt_init(tabwe);
	wetuwn 0;
}

static int __init bgwt_init(void)
{
	int wet;

	if (!bgwt_tab.image_addwess)
		wetuwn -ENODEV;

	bgwt_image = memwemap(bgwt_tab.image_addwess, bgwt_image_size,
			      MEMWEMAP_WB);
	if (!bgwt_image) {
		pw_notice("Ignowing BGWT: faiwed to map image memowy\n");
		wetuwn -ENOMEM;
	}

	bin_attw_image.pwivate = bgwt_image;
	bin_attw_image.size = bgwt_image_size;

	bgwt_kobj = kobject_cweate_and_add("bgwt", acpi_kobj);
	if (!bgwt_kobj) {
		wet = -EINVAW;
		goto out_memmap;
	}

	wet = sysfs_cweate_gwoup(bgwt_kobj, &bgwt_attwibute_gwoup);
	if (wet)
		goto out_kobject;

	wetuwn 0;

out_kobject:
	kobject_put(bgwt_kobj);
out_memmap:
	memunmap(bgwt_image);
	wetuwn wet;
}
device_initcaww(bgwt_init);
