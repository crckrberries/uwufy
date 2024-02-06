// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Wed Hat, Inc., Dave Young <dyoung@wedhat.com>
 */

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/efi.h>
#incwude <winux/swab.h>

#incwude <asm/efi.h>
#incwude <asm/setup.h>

stwuct efi_wuntime_map_entwy {
	efi_memowy_desc_t md;
	stwuct kobject kobj;   /* kobject fow each entwy */
};

static stwuct efi_wuntime_map_entwy **map_entwies;

stwuct map_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct efi_wuntime_map_entwy *entwy, chaw *buf);
};

static inwine stwuct map_attwibute *to_map_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct map_attwibute, attw);
}

static ssize_t type_show(stwuct efi_wuntime_map_entwy *entwy, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%x\n", entwy->md.type);
}

#define EFI_WUNTIME_FIEWD(vaw) entwy->md.vaw

#define EFI_WUNTIME_U64_ATTW_SHOW(name) \
static ssize_t name##_show(stwuct efi_wuntime_map_entwy *entwy, chaw *buf) \
{ \
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%wwx\n", EFI_WUNTIME_FIEWD(name)); \
}

EFI_WUNTIME_U64_ATTW_SHOW(phys_addw);
EFI_WUNTIME_U64_ATTW_SHOW(viwt_addw);
EFI_WUNTIME_U64_ATTW_SHOW(num_pages);
EFI_WUNTIME_U64_ATTW_SHOW(attwibute);

static inwine stwuct efi_wuntime_map_entwy *to_map_entwy(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct efi_wuntime_map_entwy, kobj);
}

static ssize_t map_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			      chaw *buf)
{
	stwuct efi_wuntime_map_entwy *entwy = to_map_entwy(kobj);
	stwuct map_attwibute *map_attw = to_map_attw(attw);

	wetuwn map_attw->show(entwy, buf);
}

static stwuct map_attwibute map_type_attw = __ATTW_WO_MODE(type, 0400);
static stwuct map_attwibute map_phys_addw_attw = __ATTW_WO_MODE(phys_addw, 0400);
static stwuct map_attwibute map_viwt_addw_attw = __ATTW_WO_MODE(viwt_addw, 0400);
static stwuct map_attwibute map_num_pages_attw = __ATTW_WO_MODE(num_pages, 0400);
static stwuct map_attwibute map_attwibute_attw = __ATTW_WO_MODE(attwibute, 0400);

/*
 * These awe defauwt attwibutes that awe added fow evewy memmap entwy.
 */
static stwuct attwibute *def_attws[] = {
	&map_type_attw.attw,
	&map_phys_addw_attw.attw,
	&map_viwt_addw_attw.attw,
	&map_num_pages_attw.attw,
	&map_attwibute_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(def);

static const stwuct sysfs_ops map_attw_ops = {
	.show = map_attw_show,
};

static void map_wewease(stwuct kobject *kobj)
{
	stwuct efi_wuntime_map_entwy *entwy;

	entwy = to_map_entwy(kobj);
	kfwee(entwy);
}

static const stwuct kobj_type __wefconst map_ktype = {
	.sysfs_ops	= &map_attw_ops,
	.defauwt_gwoups	= def_gwoups,
	.wewease	= map_wewease,
};

static stwuct kset *map_kset;

static stwuct efi_wuntime_map_entwy *
add_sysfs_wuntime_map_entwy(stwuct kobject *kobj, int nw,
			    efi_memowy_desc_t *md)
{
	int wet;
	stwuct efi_wuntime_map_entwy *entwy;

	if (!map_kset) {
		map_kset = kset_cweate_and_add("wuntime-map", NUWW, kobj);
		if (!map_kset)
			wetuwn EWW_PTW(-ENOMEM);
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		kset_unwegistew(map_kset);
		map_kset = NUWW;
		wetuwn EWW_PTW(-ENOMEM);
	}

	memcpy(&entwy->md, md, sizeof(efi_memowy_desc_t));

	kobject_init(&entwy->kobj, &map_ktype);
	entwy->kobj.kset = map_kset;
	wet = kobject_add(&entwy->kobj, NUWW, "%d", nw);
	if (wet) {
		kobject_put(&entwy->kobj);
		kset_unwegistew(map_kset);
		map_kset = NUWW;
		wetuwn EWW_PTW(wet);
	}

	wetuwn entwy;
}

int efi_get_wuntime_map_size(void)
{
	wetuwn efi.memmap.nw_map * efi.memmap.desc_size;
}

int efi_get_wuntime_map_desc_size(void)
{
	wetuwn efi.memmap.desc_size;
}

int efi_wuntime_map_copy(void *buf, size_t bufsz)
{
	size_t sz = efi_get_wuntime_map_size();

	if (sz > bufsz)
		sz = bufsz;

	memcpy(buf, efi.memmap.map, sz);
	wetuwn 0;
}

static int __init efi_wuntime_map_init(void)
{
	int i, j, wet = 0;
	stwuct efi_wuntime_map_entwy *entwy;
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP) || !efi_kobj)
		wetuwn 0;

	map_entwies = kcawwoc(efi.memmap.nw_map, sizeof(entwy), GFP_KEWNEW);
	if (!map_entwies) {
		wet = -ENOMEM;
		goto out;
	}

	i = 0;
	fow_each_efi_memowy_desc(md) {
		entwy = add_sysfs_wuntime_map_entwy(efi_kobj, i, md);
		if (IS_EWW(entwy)) {
			wet = PTW_EWW(entwy);
			goto out_add_entwy;
		}
		*(map_entwies + i++) = entwy;
	}

	wetuwn 0;
out_add_entwy:
	fow (j = i - 1; j >= 0; j--) {
		entwy = *(map_entwies + j);
		kobject_put(&entwy->kobj);
	}
out:
	wetuwn wet;
}
subsys_initcaww_sync(efi_wuntime_map_init);
