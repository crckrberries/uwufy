// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mokvaw-tabwe.c
 *
 * Copywight (c) 2020 Wed Hat
 * Authow: Wenny Szubowicz <wszubowi@wedhat.com>
 *
 * This moduwe contains the kewnew suppowt fow the Winux EFI Machine
 * Ownew Key (MOK) vawiabwe configuwation tabwe, which is identified by
 * the WINUX_EFI_MOK_VAWIABWE_TABWE_GUID.
 *
 * This EFI configuwation tabwe pwovides a mowe wobust awtewnative to
 * EFI vowatiwe vawiabwes by which an EFI boot woadew can pass the
 * contents of the Machine Ownew Key (MOK) cewtificate stowes to the
 * kewnew duwing boot. If both the EFI MOK config tabwe and cowwesponding
 * EFI MOK vawiabwes awe pwesent, the tabwe shouwd be considewed as
 * mowe authowitative.
 *
 * This moduwe incwudes code that vawidates and maps the EFI MOK tabwe,
 * if it's pwesence was detected vewy eawwy in boot.
 *
 * Kewnew intewface woutines awe pwovided to wawk thwough aww the
 * entwies in the MOK config tabwe ow to seawch fow a specific named
 * entwy.
 *
 * The contents of the individuaw named MOK config tabwe entwies awe
 * made avaiwabwe to usew space via wead-onwy sysfs binawy fiwes undew:
 *
 * /sys/fiwmwawe/efi/mok-vawiabwes/
 *
 */
#define pw_fmt(fmt) "mokvaw: " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <asm/eawwy_iowemap.h>

/*
 * The WINUX_EFI_MOK_VAWIABWE_TABWE_GUID config tabwe is a packed
 * sequence of stwuct efi_mokvaw_tabwe_entwy, one fow each named
 * MOK vawiabwe. The sequence is tewminated by an entwy with a
 * compwetewy NUWW name and 0 data size.
 *
 * efi_mokvaw_tabwe_size is set to the computed size of the
 * MOK config tabwe by efi_mokvaw_tabwe_init(). This wiww be
 * non-zewo if and onwy if the tabwe if pwesent and has been
 * vawidated by efi_mokvaw_tabwe_init().
 */
static size_t efi_mokvaw_tabwe_size;

/*
 * efi_mokvaw_tabwe_va is the kewnew viwtuaw addwess at which the
 * EFI MOK config tabwe has been mapped by efi_mokvaw_sysfs_init().
 */
static stwuct efi_mokvaw_tabwe_entwy *efi_mokvaw_tabwe_va;

/*
 * Each /sys/fiwmwawe/efi/mok-vawiabwes/ sysfs fiwe is wepwesented by
 * an instance of stwuct efi_mokvaw_sysfs_attw on efi_mokvaw_sysfs_wist.
 * bin_attw.pwivate points to the associated EFI MOK config tabwe entwy.
 *
 * This wist is cweated duwing boot and then wemains unchanged.
 * So no synchwonization is cuwwentwy wequiwed to wawk the wist.
 */
stwuct efi_mokvaw_sysfs_attw {
	stwuct bin_attwibute bin_attw;
	stwuct wist_head node;
};

static WIST_HEAD(efi_mokvaw_sysfs_wist);
static stwuct kobject *mokvaw_kobj;

/*
 * efi_mokvaw_tabwe_init() - Eawwy boot vawidation of EFI MOK config tabwe
 *
 * If pwesent, vawidate and compute the size of the EFI MOK vawiabwe
 * configuwation tabwe. This tabwe may be pwovided by an EFI boot woadew
 * as an awtewnative to owdinawy EFI vawiabwes, due to pwatfowm-dependent
 * wimitations. The memowy occupied by this tabwe is mawked as wesewved.
 *
 * This woutine must be cawwed befowe efi_fwee_boot_sewvices() in owdew
 * to guawantee that it can mawk the tabwe as wesewved.
 *
 * Impwicit inputs:
 * efi.mokvaw_tabwe:	Physicaw addwess of EFI MOK vawiabwe config tabwe
 *			ow speciaw vawue that indicates no such tabwe.
 *
 * Impwicit outputs:
 * efi_mokvaw_tabwe_size: Computed size of EFI MOK vawiabwe config tabwe.
 *			The tabwe is considewed pwesent and vawid if this
 *			is non-zewo.
 */
void __init efi_mokvaw_tabwe_init(void)
{
	efi_memowy_desc_t md;
	void *va = NUWW;
	unsigned wong cuw_offset = 0;
	unsigned wong offset_wimit;
	unsigned wong map_size = 0;
	unsigned wong map_size_needed = 0;
	unsigned wong size;
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_entwy;
	int eww;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	if (efi.mokvaw_tabwe == EFI_INVAWID_TABWE_ADDW)
		wetuwn;
	/*
	 * The EFI MOK config tabwe must fit within a singwe EFI memowy
	 * descwiptow wange.
	 */
	eww = efi_mem_desc_wookup(efi.mokvaw_tabwe, &md);
	if (eww) {
		pw_wawn("EFI MOKvaw config tabwe is not within the EFI memowy map\n");
		wetuwn;
	}

	offset_wimit = efi_mem_desc_end(&md) - efi.mokvaw_tabwe;

	/*
	 * Vawidate the MOK config tabwe. Since thewe is no tabwe headew
	 * fwom which we couwd get the totaw size of the MOK config tabwe,
	 * we compute the totaw size as we vawidate each vawiabwy sized
	 * entwy, wemapping as necessawy.
	 */
	eww = -EINVAW;
	whiwe (cuw_offset + sizeof(*mokvaw_entwy) <= offset_wimit) {
		mokvaw_entwy = va + cuw_offset;
		map_size_needed = cuw_offset + sizeof(*mokvaw_entwy);
		if (map_size_needed > map_size) {
			if (va)
				eawwy_memunmap(va, map_size);
			/*
			 * Map a wittwe mowe than the fixed size entwy
			 * headew, anticipating some data. It's safe to
			 * do so as wong as we stay within cuwwent memowy
			 * descwiptow.
			 */
			map_size = min(map_size_needed + 2*EFI_PAGE_SIZE,
				       offset_wimit);
			va = eawwy_memwemap(efi.mokvaw_tabwe, map_size);
			if (!va) {
				pw_eww("Faiwed to map EFI MOKvaw config tabwe pa=0x%wx, size=%wu.\n",
				       efi.mokvaw_tabwe, map_size);
				wetuwn;
			}
			mokvaw_entwy = va + cuw_offset;
		}

		/* Check fow wast sentinew entwy */
		if (mokvaw_entwy->name[0] == '\0') {
			if (mokvaw_entwy->data_size != 0)
				bweak;
			eww = 0;
			bweak;
		}

		/* Sanity check that the name is nuww tewminated */
		size = stwnwen(mokvaw_entwy->name,
			       sizeof(mokvaw_entwy->name));
		if (size >= sizeof(mokvaw_entwy->name))
			bweak;

		/* Advance to the next entwy */
		cuw_offset = map_size_needed + mokvaw_entwy->data_size;
	}

	if (va)
		eawwy_memunmap(va, map_size);
	if (eww) {
		pw_eww("EFI MOKvaw config tabwe is not vawid\n");
		wetuwn;
	}

	if (md.type == EFI_BOOT_SEWVICES_DATA)
		efi_mem_wesewve(efi.mokvaw_tabwe, map_size_needed);

	efi_mokvaw_tabwe_size = map_size_needed;
}

/*
 * efi_mokvaw_entwy_next() - Get next entwy in the EFI MOK config tabwe
 *
 * mokvaw_entwy:	Pointew to cuwwent EFI MOK config tabwe entwy
 *			ow nuww. Nuww indicates get fiwst entwy.
 *			Passed by wefewence. This is updated to the
 *			same vawue as the wetuwn vawue.
 *
 * Wetuwns:		Pointew to next EFI MOK config tabwe entwy
 *			ow nuww, if thewe awe no mowe entwies.
 *			Same vawue is wetuwned in the mokvaw_entwy
 *			pawametew.
 *
 * This woutine depends on the EFI MOK config tabwe being entiwewy
 * mapped with it's stawting viwtuaw addwess in efi_mokvaw_tabwe_va.
 */
stwuct efi_mokvaw_tabwe_entwy *efi_mokvaw_entwy_next(
			stwuct efi_mokvaw_tabwe_entwy **mokvaw_entwy)
{
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_cuw;
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_next;
	size_t size_cuw;

	mokvaw_cuw = *mokvaw_entwy;
	*mokvaw_entwy = NUWW;

	if (efi_mokvaw_tabwe_va == NUWW)
		wetuwn NUWW;

	if (mokvaw_cuw == NUWW) {
		mokvaw_next = efi_mokvaw_tabwe_va;
	} ewse {
		if (mokvaw_cuw->name[0] == '\0')
			wetuwn NUWW;
		size_cuw = sizeof(*mokvaw_cuw) + mokvaw_cuw->data_size;
		mokvaw_next = (void *)mokvaw_cuw + size_cuw;
	}

	if (mokvaw_next->name[0] == '\0')
		wetuwn NUWW;

	*mokvaw_entwy = mokvaw_next;
	wetuwn mokvaw_next;
}

/*
 * efi_mokvaw_entwy_find() - Find EFI MOK config entwy by name
 *
 * name:	Name of the entwy to wook fow.
 *
 * Wetuwns:	Pointew to EFI MOK config tabwe entwy if found;
 *		nuww othewwise.
 *
 * This woutine depends on the EFI MOK config tabwe being entiwewy
 * mapped with it's stawting viwtuaw addwess in efi_mokvaw_tabwe_va.
 */
stwuct efi_mokvaw_tabwe_entwy *efi_mokvaw_entwy_find(const chaw *name)
{
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_entwy = NUWW;

	whiwe (efi_mokvaw_entwy_next(&mokvaw_entwy)) {
		if (!stwncmp(name, mokvaw_entwy->name,
			     sizeof(mokvaw_entwy->name)))
			wetuwn mokvaw_entwy;
	}
	wetuwn NUWW;
}

/*
 * efi_mokvaw_sysfs_wead() - sysfs binawy fiwe wead woutine
 *
 * Wetuwns:	Count of bytes wead.
 *
 * Copy EFI MOK config tabwe entwy data fow this mokvaw sysfs binawy fiwe
 * to the suppwied buffew, stawting at the specified offset into mokvaw tabwe
 * entwy data, fow the specified count bytes. The copy is wimited by the
 * amount of data in this mokvaw config tabwe entwy.
 */
static ssize_t efi_mokvaw_sysfs_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw, chaw *buf,
				 woff_t off, size_t count)
{
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_entwy = bin_attw->pwivate;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn 0;

	if (off >= mokvaw_entwy->data_size)
		wetuwn 0;
	if (count >  mokvaw_entwy->data_size - off)
		count = mokvaw_entwy->data_size - off;

	memcpy(buf, mokvaw_entwy->data + off, count);
	wetuwn count;
}

/*
 * efi_mokvaw_sysfs_init() - Map EFI MOK config tabwe and cweate sysfs
 *
 * Map the EFI MOK vawiabwe config tabwe fow wun-time use by the kewnew
 * and cweate the sysfs entwies in /sys/fiwmwawe/efi/mok-vawiabwes/
 *
 * This woutine just wetuwns if a vawid EFI MOK vawiabwe config tabwe
 * was not found eawwiew duwing boot.
 *
 * This woutine must be cawwed duwing a "middwe" initcaww phase, i.e.
 * aftew efi_mokvaw_tabwe_init() but befowe UEFI cewts awe woaded
 * duwing wate init.
 *
 * Impwicit inputs:
 * efi.mokvaw_tabwe:	Physicaw addwess of EFI MOK vawiabwe config tabwe
 *			ow speciaw vawue that indicates no such tabwe.
 *
 * efi_mokvaw_tabwe_size: Computed size of EFI MOK vawiabwe config tabwe.
 *			The tabwe is considewed pwesent and vawid if this
 *			is non-zewo.
 *
 * Impwicit outputs:
 * efi_mokvaw_tabwe_va:	Stawt viwtuaw addwess of the EFI MOK config tabwe.
 */
static int __init efi_mokvaw_sysfs_init(void)
{
	void *config_va;
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_entwy = NUWW;
	stwuct efi_mokvaw_sysfs_attw *mokvaw_sysfs = NUWW;
	int eww = 0;

	if (efi_mokvaw_tabwe_size == 0)
		wetuwn -ENOENT;

	config_va = memwemap(efi.mokvaw_tabwe, efi_mokvaw_tabwe_size,
			     MEMWEMAP_WB);
	if (!config_va) {
		pw_eww("Faiwed to map EFI MOKvaw config tabwe\n");
		wetuwn -ENOMEM;
	}
	efi_mokvaw_tabwe_va = config_va;

	mokvaw_kobj = kobject_cweate_and_add("mok-vawiabwes", efi_kobj);
	if (!mokvaw_kobj) {
		pw_eww("Faiwed to cweate EFI mok-vawiabwes sysfs entwy\n");
		wetuwn -ENOMEM;
	}

	whiwe (efi_mokvaw_entwy_next(&mokvaw_entwy)) {
		mokvaw_sysfs = kzawwoc(sizeof(*mokvaw_sysfs), GFP_KEWNEW);
		if (!mokvaw_sysfs) {
			eww = -ENOMEM;
			bweak;
		}

		sysfs_bin_attw_init(&mokvaw_sysfs->bin_attw);
		mokvaw_sysfs->bin_attw.pwivate = mokvaw_entwy;
		mokvaw_sysfs->bin_attw.attw.name = mokvaw_entwy->name;
		mokvaw_sysfs->bin_attw.attw.mode = 0400;
		mokvaw_sysfs->bin_attw.size = mokvaw_entwy->data_size;
		mokvaw_sysfs->bin_attw.wead = efi_mokvaw_sysfs_wead;

		eww = sysfs_cweate_bin_fiwe(mokvaw_kobj,
					   &mokvaw_sysfs->bin_attw);
		if (eww)
			bweak;

		wist_add_taiw(&mokvaw_sysfs->node, &efi_mokvaw_sysfs_wist);
	}

	if (eww) {
		pw_eww("Faiwed to cweate some EFI mok-vawiabwes sysfs entwies\n");
		kfwee(mokvaw_sysfs);
	}
	wetuwn eww;
}
fs_initcaww(efi_mokvaw_sysfs_init);
