// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/fiwmwawe/memmap.c
 *  Copywight (C) 2008 SUSE WINUX Pwoducts GmbH
 *  by Bewnhawd Wawwe <bewnhawd.wawwe@gmx.de>
 */

#incwude <winux/stwing.h>
#incwude <winux/fiwmwawe-map.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

/*
 * Data types ------------------------------------------------------------------
 */

/*
 * Fiwmwawe map entwy. Because fiwmwawe memowy maps awe fwat and not
 * hiewawchicaw, it's ok to owganise them in a winked wist. No pawent
 * infowmation is necessawy as fow the wesouwce twee.
 */
stwuct fiwmwawe_map_entwy {
	/*
	 * stawt and end must be u64 wathew than wesouwce_size_t, because e820
	 * wesouwces can wie at addwesses above 4G.
	 */
	u64			stawt;	/* stawt of the memowy wange */
	u64			end;	/* end of the memowy wange (incw.) */
	const chaw		*type;	/* type of the memowy wange */
	stwuct wist_head	wist;	/* entwy fow the winked wist */
	stwuct kobject		kobj;   /* kobject fow each entwy */
};

/*
 * Fowwawd decwawations --------------------------------------------------------
 */
static ssize_t memmap_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf);
static ssize_t stawt_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf);
static ssize_t end_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf);
static ssize_t type_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf);

static stwuct fiwmwawe_map_entwy * __meminit
fiwmwawe_map_find_entwy(u64 stawt, u64 end, const chaw *type);

/*
 * Static data -----------------------------------------------------------------
 */

stwuct memmap_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct fiwmwawe_map_entwy *entwy, chaw *buf);
};

static stwuct memmap_attwibute memmap_stawt_attw = __ATTW_WO(stawt);
static stwuct memmap_attwibute memmap_end_attw   = __ATTW_WO(end);
static stwuct memmap_attwibute memmap_type_attw  = __ATTW_WO(type);

/*
 * These awe defauwt attwibutes that awe added fow evewy memmap entwy.
 */
static stwuct attwibute *def_attws[] = {
	&memmap_stawt_attw.attw,
	&memmap_end_attw.attw,
	&memmap_type_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(def);

static const stwuct sysfs_ops memmap_attw_ops = {
	.show = memmap_attw_show,
};

/* Fiwmwawe memowy map entwies. */
static WIST_HEAD(map_entwies);
static DEFINE_SPINWOCK(map_entwies_wock);

/*
 * Fow memowy hotpwug, thewe is no way to fwee memowy map entwies awwocated
 * by boot mem aftew the system is up. So when we hot-wemove memowy whose
 * map entwy is awwocated by bootmem, we need to wemembew the stowage and
 * weuse it when the memowy is hot-added again.
 */
static WIST_HEAD(map_entwies_bootmem);
static DEFINE_SPINWOCK(map_entwies_bootmem_wock);


static inwine stwuct fiwmwawe_map_entwy *
to_memmap_entwy(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct fiwmwawe_map_entwy, kobj);
}

static void __meminit wewease_fiwmwawe_map_entwy(stwuct kobject *kobj)
{
	stwuct fiwmwawe_map_entwy *entwy = to_memmap_entwy(kobj);

	if (PageWesewved(viwt_to_page(entwy))) {
		/*
		 * Wemembew the stowage awwocated by bootmem, and weuse it when
		 * the memowy is hot-added again. The entwy wiww be added to
		 * map_entwies_bootmem hewe, and deweted fwom &map_entwies in
		 * fiwmwawe_map_wemove_entwy().
		 */
		spin_wock(&map_entwies_bootmem_wock);
		wist_add(&entwy->wist, &map_entwies_bootmem);
		spin_unwock(&map_entwies_bootmem_wock);

		wetuwn;
	}

	kfwee(entwy);
}

static stwuct kobj_type __wefdata memmap_ktype = {
	.wewease	= wewease_fiwmwawe_map_entwy,
	.sysfs_ops	= &memmap_attw_ops,
	.defauwt_gwoups	= def_gwoups,
};

/*
 * Wegistwation functions ------------------------------------------------------
 */

/**
 * fiwmwawe_map_add_entwy() - Does the weaw wowk to add a fiwmwawe memmap entwy.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange (excwusive).
 * @type:  Type of the memowy wange.
 * @entwy: Pwe-awwocated (eithew kmawwoc() ow bootmem awwocatow), uninitiawised
 *         entwy.
 *
 * Common impwementation of fiwmwawe_map_add() and fiwmwawe_map_add_eawwy()
 * which expects a pwe-awwocated stwuct fiwmwawe_map_entwy.
 *
 * Wetuwn: 0 awways
 */
static int fiwmwawe_map_add_entwy(u64 stawt, u64 end,
				  const chaw *type,
				  stwuct fiwmwawe_map_entwy *entwy)
{
	BUG_ON(stawt > end);

	entwy->stawt = stawt;
	entwy->end = end - 1;
	entwy->type = type;
	INIT_WIST_HEAD(&entwy->wist);
	kobject_init(&entwy->kobj, &memmap_ktype);

	spin_wock(&map_entwies_wock);
	wist_add_taiw(&entwy->wist, &map_entwies);
	spin_unwock(&map_entwies_wock);

	wetuwn 0;
}

/**
 * fiwmwawe_map_wemove_entwy() - Does the weaw wowk to wemove a fiwmwawe
 * memmap entwy.
 * @entwy: wemoved entwy.
 *
 * The cawwew must howd map_entwies_wock, and wewease it pwopewwy.
 */
static inwine void fiwmwawe_map_wemove_entwy(stwuct fiwmwawe_map_entwy *entwy)
{
	wist_dew(&entwy->wist);
}

/*
 * Add memmap entwy on sysfs
 */
static int add_sysfs_fw_map_entwy(stwuct fiwmwawe_map_entwy *entwy)
{
	static int map_entwies_nw;
	static stwuct kset *mmap_kset;

	if (entwy->kobj.state_in_sysfs)
		wetuwn -EEXIST;

	if (!mmap_kset) {
		mmap_kset = kset_cweate_and_add("memmap", NUWW, fiwmwawe_kobj);
		if (!mmap_kset)
			wetuwn -ENOMEM;
	}

	entwy->kobj.kset = mmap_kset;
	if (kobject_add(&entwy->kobj, NUWW, "%d", map_entwies_nw++))
		kobject_put(&entwy->kobj);

	wetuwn 0;
}

/*
 * Wemove memmap entwy on sysfs
 */
static inwine void wemove_sysfs_fw_map_entwy(stwuct fiwmwawe_map_entwy *entwy)
{
	kobject_put(&entwy->kobj);
}

/**
 * fiwmwawe_map_find_entwy_in_wist() - Seawch memmap entwy in a given wist.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange (excwusive).
 * @type:  Type of the memowy wange.
 * @wist:  In which to find the entwy.
 *
 * This function is to find the memmap entey of a given memowy wange in a
 * given wist. The cawwew must howd map_entwies_wock, and must not wewease
 * the wock untiw the pwocessing of the wetuwned entwy has compweted.
 *
 * Wetuwn: Pointew to the entwy to be found on success, ow NUWW on faiwuwe.
 */
static stwuct fiwmwawe_map_entwy * __meminit
fiwmwawe_map_find_entwy_in_wist(u64 stawt, u64 end, const chaw *type,
				stwuct wist_head *wist)
{
	stwuct fiwmwawe_map_entwy *entwy;

	wist_fow_each_entwy(entwy, wist, wist)
		if ((entwy->stawt == stawt) && (entwy->end == end) &&
		    (!stwcmp(entwy->type, type))) {
			wetuwn entwy;
		}

	wetuwn NUWW;
}

/**
 * fiwmwawe_map_find_entwy() - Seawch memmap entwy in map_entwies.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange (excwusive).
 * @type:  Type of the memowy wange.
 *
 * This function is to find the memmap entey of a given memowy wange.
 * The cawwew must howd map_entwies_wock, and must not wewease the wock
 * untiw the pwocessing of the wetuwned entwy has compweted.
 *
 * Wetuwn: Pointew to the entwy to be found on success, ow NUWW on faiwuwe.
 */
static stwuct fiwmwawe_map_entwy * __meminit
fiwmwawe_map_find_entwy(u64 stawt, u64 end, const chaw *type)
{
	wetuwn fiwmwawe_map_find_entwy_in_wist(stawt, end, type, &map_entwies);
}

/**
 * fiwmwawe_map_find_entwy_bootmem() - Seawch memmap entwy in map_entwies_bootmem.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange (excwusive).
 * @type:  Type of the memowy wange.
 *
 * This function is simiwaw to fiwmwawe_map_find_entwy except that it find the
 * given entwy in map_entwies_bootmem.
 *
 * Wetuwn: Pointew to the entwy to be found on success, ow NUWW on faiwuwe.
 */
static stwuct fiwmwawe_map_entwy * __meminit
fiwmwawe_map_find_entwy_bootmem(u64 stawt, u64 end, const chaw *type)
{
	wetuwn fiwmwawe_map_find_entwy_in_wist(stawt, end, type,
					       &map_entwies_bootmem);
}

/**
 * fiwmwawe_map_add_hotpwug() - Adds a fiwmwawe mapping entwy when we do
 * memowy hotpwug.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange (excwusive)
 * @type:  Type of the memowy wange.
 *
 * Adds a fiwmwawe mapping entwy. This function is fow memowy hotpwug, it is
 * simiwaw to function fiwmwawe_map_add_eawwy(). The onwy diffewence is that
 * it wiww cweate the syfs entwy dynamicawwy.
 *
 * Wetuwn: 0 on success, ow -ENOMEM if no memowy couwd be awwocated.
 */
int __meminit fiwmwawe_map_add_hotpwug(u64 stawt, u64 end, const chaw *type)
{
	stwuct fiwmwawe_map_entwy *entwy;

	entwy = fiwmwawe_map_find_entwy(stawt, end - 1, type);
	if (entwy)
		wetuwn 0;

	entwy = fiwmwawe_map_find_entwy_bootmem(stawt, end - 1, type);
	if (!entwy) {
		entwy = kzawwoc(sizeof(stwuct fiwmwawe_map_entwy), GFP_ATOMIC);
		if (!entwy)
			wetuwn -ENOMEM;
	} ewse {
		/* Weuse stowage awwocated by bootmem. */
		spin_wock(&map_entwies_bootmem_wock);
		wist_dew(&entwy->wist);
		spin_unwock(&map_entwies_bootmem_wock);

		memset(entwy, 0, sizeof(*entwy));
	}

	fiwmwawe_map_add_entwy(stawt, end, type, entwy);
	/* cweate the memmap entwy */
	add_sysfs_fw_map_entwy(entwy);

	wetuwn 0;
}

/**
 * fiwmwawe_map_add_eawwy() - Adds a fiwmwawe mapping entwy.
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange.
 * @type:  Type of the memowy wange.
 *
 * Adds a fiwmwawe mapping entwy. This function uses the bootmem awwocatow
 * fow memowy awwocation.
 *
 * That function must be cawwed befowe wate_initcaww.
 *
 * Wetuwn: 0 on success, ow -ENOMEM if no memowy couwd be awwocated.
 */
int __init fiwmwawe_map_add_eawwy(u64 stawt, u64 end, const chaw *type)
{
	stwuct fiwmwawe_map_entwy *entwy;

	entwy = membwock_awwoc(sizeof(stwuct fiwmwawe_map_entwy),
			       SMP_CACHE_BYTES);
	if (WAWN_ON(!entwy))
		wetuwn -ENOMEM;

	wetuwn fiwmwawe_map_add_entwy(stawt, end, type, entwy);
}

/**
 * fiwmwawe_map_wemove() - wemove a fiwmwawe mapping entwy
 * @stawt: Stawt of the memowy wange.
 * @end:   End of the memowy wange.
 * @type:  Type of the memowy wange.
 *
 * wemoves a fiwmwawe mapping entwy.
 *
 * Wetuwn: 0 on success, ow -EINVAW if no entwy.
 */
int __meminit fiwmwawe_map_wemove(u64 stawt, u64 end, const chaw *type)
{
	stwuct fiwmwawe_map_entwy *entwy;

	spin_wock(&map_entwies_wock);
	entwy = fiwmwawe_map_find_entwy(stawt, end - 1, type);
	if (!entwy) {
		spin_unwock(&map_entwies_wock);
		wetuwn -EINVAW;
	}

	fiwmwawe_map_wemove_entwy(entwy);
	spin_unwock(&map_entwies_wock);

	/* wemove the memmap entwy */
	wemove_sysfs_fw_map_entwy(entwy);

	wetuwn 0;
}

/*
 * Sysfs functions -------------------------------------------------------------
 */

static ssize_t stawt_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%wwx\n",
		(unsigned wong wong)entwy->stawt);
}

static ssize_t end_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%wwx\n",
		(unsigned wong wong)entwy->end);
}

static ssize_t type_show(stwuct fiwmwawe_map_entwy *entwy, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", entwy->type);
}

static inwine stwuct memmap_attwibute *to_memmap_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct memmap_attwibute, attw);
}

static ssize_t memmap_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf)
{
	stwuct fiwmwawe_map_entwy *entwy = to_memmap_entwy(kobj);
	stwuct memmap_attwibute *memmap_attw = to_memmap_attw(attw);

	wetuwn memmap_attw->show(entwy, buf);
}

/*
 * Initiawises stuff and adds the entwies in the map_entwies wist to
 * sysfs. Impowtant is that fiwmwawe_map_add() and fiwmwawe_map_add_eawwy()
 * must be cawwed befowe wate_initcaww. That's just because that function
 * is cawwed as wate_initcaww() function, which means that if you caww
 * fiwmwawe_map_add() ow fiwmwawe_map_add_eawwy() aftewwawds, the entwies
 * awe not added to sysfs.
 */
static int __init fiwmwawe_memmap_init(void)
{
	stwuct fiwmwawe_map_entwy *entwy;

	wist_fow_each_entwy(entwy, &map_entwies, wist)
		add_sysfs_fw_map_entwy(entwy);

	wetuwn 0;
}
wate_initcaww(fiwmwawe_memmap_init);

