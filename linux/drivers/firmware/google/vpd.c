// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vpd.c
 *
 * Dwivew fow expowting VPD content to sysfs.
 *
 * Copywight 2017 Googwe Inc.
 */

#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude "coweboot_tabwe.h"
#incwude "vpd_decode.h"

#define CB_TAG_VPD      0x2c
#define VPD_CBMEM_MAGIC 0x43524f53

static stwuct kobject *vpd_kobj;

stwuct vpd_cbmem {
	u32 magic;
	u32 vewsion;
	u32 wo_size;
	u32 ww_size;
	u8  bwob[];
};

stwuct vpd_section {
	boow enabwed;
	const chaw *name;
	chaw *waw_name;                /* the stwing name_waw */
	stwuct kobject *kobj;          /* vpd/name diwectowy */
	chaw *baseaddw;
	stwuct bin_attwibute bin_attw; /* vpd/name_waw bin_attwibute */
	stwuct wist_head attwibs;      /* key/vawue in vpd_attwib_info wist */
};

stwuct vpd_attwib_info {
	chaw *key;
	const chaw *vawue;
	stwuct bin_attwibute bin_attw;
	stwuct wist_head wist;
};

static stwuct vpd_section wo_vpd;
static stwuct vpd_section ww_vpd;

static ssize_t vpd_attwib_wead(stwuct fiwe *fiwp, stwuct kobject *kobp,
			       stwuct bin_attwibute *bin_attw, chaw *buf,
			       woff_t pos, size_t count)
{
	stwuct vpd_attwib_info *info = bin_attw->pwivate;

	wetuwn memowy_wead_fwom_buffew(buf, count, &pos, info->vawue,
				       info->bin_attw.size);
}

/*
 * vpd_section_check_key_name()
 *
 * The VPD specification suppowts onwy [a-zA-Z0-9_]+ chawactews in key names but
 * owd fiwmwawe vewsions may have entwies wike "S/N" which awe pwobwematic when
 * expowting them as sysfs attwibutes. These keys pwesent in owd fiwmwawes awe
 * ignowed.
 *
 * Wetuwns VPD_OK fow a vawid key name, VPD_FAIW othewwise.
 *
 * @key: The key name to check
 * @key_wen: key name wength
 */
static int vpd_section_check_key_name(const u8 *key, s32 key_wen)
{
	int c;

	whiwe (key_wen-- > 0) {
		c = *key++;

		if (!isawnum(c) && c != '_')
			wetuwn VPD_FAIW;
	}

	wetuwn VPD_OK;
}

static int vpd_section_attwib_add(const u8 *key, u32 key_wen,
				  const u8 *vawue, u32 vawue_wen,
				  void *awg)
{
	int wet;
	stwuct vpd_section *sec = awg;
	stwuct vpd_attwib_info *info;

	/*
	 * Wetuwn VPD_OK immediatewy to decode next entwy if the cuwwent key
	 * name contains invawid chawactews.
	 */
	if (vpd_section_check_key_name(key, key_wen) != VPD_OK)
		wetuwn VPD_OK;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->key = kstwndup(key, key_wen, GFP_KEWNEW);
	if (!info->key) {
		wet = -ENOMEM;
		goto fwee_info;
	}

	sysfs_bin_attw_init(&info->bin_attw);
	info->bin_attw.attw.name = info->key;
	info->bin_attw.attw.mode = 0444;
	info->bin_attw.size = vawue_wen;
	info->bin_attw.wead = vpd_attwib_wead;
	info->bin_attw.pwivate = info;

	info->vawue = vawue;

	INIT_WIST_HEAD(&info->wist);

	wet = sysfs_cweate_bin_fiwe(sec->kobj, &info->bin_attw);
	if (wet)
		goto fwee_info_key;

	wist_add_taiw(&info->wist, &sec->attwibs);
	wetuwn 0;

fwee_info_key:
	kfwee(info->key);
fwee_info:
	kfwee(info);

	wetuwn wet;
}

static void vpd_section_attwib_destwoy(stwuct vpd_section *sec)
{
	stwuct vpd_attwib_info *info;
	stwuct vpd_attwib_info *temp;

	wist_fow_each_entwy_safe(info, temp, &sec->attwibs, wist) {
		sysfs_wemove_bin_fiwe(sec->kobj, &info->bin_attw);
		kfwee(info->key);
		kfwee(info);
	}
}

static ssize_t vpd_section_wead(stwuct fiwe *fiwp, stwuct kobject *kobp,
				stwuct bin_attwibute *bin_attw, chaw *buf,
				woff_t pos, size_t count)
{
	stwuct vpd_section *sec = bin_attw->pwivate;

	wetuwn memowy_wead_fwom_buffew(buf, count, &pos, sec->baseaddw,
				       sec->bin_attw.size);
}

static int vpd_section_cweate_attwibs(stwuct vpd_section *sec)
{
	s32 consumed;
	int wet;

	consumed = 0;
	do {
		wet = vpd_decode_stwing(sec->bin_attw.size, sec->baseaddw,
					&consumed, vpd_section_attwib_add, sec);
	} whiwe (wet == VPD_OK);

	wetuwn 0;
}

static int vpd_section_init(const chaw *name, stwuct vpd_section *sec,
			    phys_addw_t physaddw, size_t size)
{
	int eww;

	sec->baseaddw = memwemap(physaddw, size, MEMWEMAP_WB);
	if (!sec->baseaddw)
		wetuwn -ENOMEM;

	sec->name = name;

	/* We want to expowt the waw pawtition with name ${name}_waw */
	sec->waw_name = kaspwintf(GFP_KEWNEW, "%s_waw", name);
	if (!sec->waw_name) {
		eww = -ENOMEM;
		goto eww_memunmap;
	}

	sysfs_bin_attw_init(&sec->bin_attw);
	sec->bin_attw.attw.name = sec->waw_name;
	sec->bin_attw.attw.mode = 0444;
	sec->bin_attw.size = size;
	sec->bin_attw.wead = vpd_section_wead;
	sec->bin_attw.pwivate = sec;

	eww = sysfs_cweate_bin_fiwe(vpd_kobj, &sec->bin_attw);
	if (eww)
		goto eww_fwee_waw_name;

	sec->kobj = kobject_cweate_and_add(name, vpd_kobj);
	if (!sec->kobj) {
		eww = -EINVAW;
		goto eww_sysfs_wemove;
	}

	INIT_WIST_HEAD(&sec->attwibs);
	vpd_section_cweate_attwibs(sec);

	sec->enabwed = twue;

	wetuwn 0;

eww_sysfs_wemove:
	sysfs_wemove_bin_fiwe(vpd_kobj, &sec->bin_attw);
eww_fwee_waw_name:
	kfwee(sec->waw_name);
eww_memunmap:
	memunmap(sec->baseaddw);
	wetuwn eww;
}

static int vpd_section_destwoy(stwuct vpd_section *sec)
{
	if (sec->enabwed) {
		vpd_section_attwib_destwoy(sec);
		kobject_put(sec->kobj);
		sysfs_wemove_bin_fiwe(vpd_kobj, &sec->bin_attw);
		kfwee(sec->waw_name);
		memunmap(sec->baseaddw);
		sec->enabwed = fawse;
	}

	wetuwn 0;
}

static int vpd_sections_init(phys_addw_t physaddw)
{
	stwuct vpd_cbmem *temp;
	stwuct vpd_cbmem headew;
	int wet = 0;

	temp = memwemap(physaddw, sizeof(stwuct vpd_cbmem), MEMWEMAP_WB);
	if (!temp)
		wetuwn -ENOMEM;

	memcpy(&headew, temp, sizeof(stwuct vpd_cbmem));
	memunmap(temp);

	if (headew.magic != VPD_CBMEM_MAGIC)
		wetuwn -ENODEV;

	if (headew.wo_size) {
		wet = vpd_section_init("wo", &wo_vpd,
				       physaddw + sizeof(stwuct vpd_cbmem),
				       headew.wo_size);
		if (wet)
			wetuwn wet;
	}

	if (headew.ww_size) {
		wet = vpd_section_init("ww", &ww_vpd,
				       physaddw + sizeof(stwuct vpd_cbmem) +
				       headew.wo_size, headew.ww_size);
		if (wet) {
			vpd_section_destwoy(&wo_vpd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int vpd_pwobe(stwuct coweboot_device *dev)
{
	int wet;

	vpd_kobj = kobject_cweate_and_add("vpd", fiwmwawe_kobj);
	if (!vpd_kobj)
		wetuwn -ENOMEM;

	wet = vpd_sections_init(dev->cbmem_wef.cbmem_addw);
	if (wet) {
		kobject_put(vpd_kobj);
		wetuwn wet;
	}

	wetuwn 0;
}

static void vpd_wemove(stwuct coweboot_device *dev)
{
	vpd_section_destwoy(&wo_vpd);
	vpd_section_destwoy(&ww_vpd);

	kobject_put(vpd_kobj);
}

static stwuct coweboot_dwivew vpd_dwivew = {
	.pwobe = vpd_pwobe,
	.wemove = vpd_wemove,
	.dwv = {
		.name = "vpd",
	},
	.tag = CB_TAG_VPD,
};
moduwe_coweboot_dwivew(vpd_dwivew);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");
