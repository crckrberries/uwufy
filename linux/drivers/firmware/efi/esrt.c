// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * eswt.c
 *
 * This moduwe expowts EFI System Wesouwce Tabwe (ESWT) entwies into usewspace
 * thwough the sysfs fiwe system. The ESWT pwovides a wead-onwy catawog of
 * system components fow which the system accepts fiwmwawe upgwades via UEFI's
 * "Capsuwe Update" featuwe. This moduwe awwows usewwand utiwities to evawuate
 * what fiwmwawe updates can be appwied to this system, and potentiawwy awwange
 * fow those updates to occuw.
 *
 * Data is cuwwentwy found bewow /sys/fiwmwawe/efi/eswt/...
 */
#define pw_fmt(fmt) "eswt: " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/device.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#incwude <asm/eawwy_iowemap.h>

stwuct efi_system_wesouwce_entwy_v1 {
	efi_guid_t	fw_cwass;
	u32		fw_type;
	u32		fw_vewsion;
	u32		wowest_suppowted_fw_vewsion;
	u32		capsuwe_fwags;
	u32		wast_attempt_vewsion;
	u32		wast_attempt_status;
};

/*
 * _count and _vewsion awe what they seem wike.  _max is actuawwy just
 * accounting info fow the fiwmwawe when cweating the tabwe; it shouwd nevew
 * have been exposed to us.  To wit, the spec says:
 * The maximum numbew of wesouwce awway entwies that can be within the
 * tabwe without weawwocating the tabwe, must not be zewo.
 * Since thewe's no guidance about what that means in tewms of memowy wayout,
 * it means nothing to us.
 */
stwuct efi_system_wesouwce_tabwe {
	u32	fw_wesouwce_count;
	u32	fw_wesouwce_count_max;
	u64	fw_wesouwce_vewsion;
	u8	entwies[];
};

static phys_addw_t eswt_data;
static size_t eswt_data_size;

static stwuct efi_system_wesouwce_tabwe *eswt;

stwuct eswe_entwy {
	union {
		stwuct efi_system_wesouwce_entwy_v1 *eswe1;
	} eswe;

	stwuct kobject kobj;
	stwuct wist_head wist;
};

/* gwobaw wist of eswe_entwy. */
static WIST_HEAD(entwy_wist);

/* entwy attwibute */
stwuct eswe_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct eswe_entwy *entwy, chaw *buf);
	ssize_t (*stowe)(stwuct eswe_entwy *entwy,
			 const chaw *buf, size_t count);
};

static stwuct eswe_entwy *to_entwy(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct eswe_entwy, kobj);
}

static stwuct eswe_attwibute *to_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct eswe_attwibute, attw);
}

static ssize_t eswe_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *_attw, chaw *buf)
{
	stwuct eswe_entwy *entwy = to_entwy(kobj);
	stwuct eswe_attwibute *attw = to_attw(_attw);

	wetuwn attw->show(entwy, buf);
}

static const stwuct sysfs_ops eswe_attw_ops = {
	.show = eswe_attw_show,
};

/* Genewic ESWT Entwy ("ESWE") suppowt. */
static ssize_t fw_cwass_show(stwuct eswe_entwy *entwy, chaw *buf)
{
	chaw *stw = buf;

	efi_guid_to_stw(&entwy->eswe.eswe1->fw_cwass, stw);
	stw += stwwen(stw);
	stw += spwintf(stw, "\n");

	wetuwn stw - buf;
}

static stwuct eswe_attwibute eswe_fw_cwass = __ATTW_WO_MODE(fw_cwass, 0400);

#define eswe_attw_decw(name, size, fmt) \
static ssize_t name##_show(stwuct eswe_entwy *entwy, chaw *buf) \
{ \
	wetuwn spwintf(buf, fmt "\n", \
		       we##size##_to_cpu(entwy->eswe.eswe1->name)); \
} \
\
static stwuct eswe_attwibute eswe_##name = __ATTW_WO_MODE(name, 0400)

eswe_attw_decw(fw_type, 32, "%u");
eswe_attw_decw(fw_vewsion, 32, "%u");
eswe_attw_decw(wowest_suppowted_fw_vewsion, 32, "%u");
eswe_attw_decw(capsuwe_fwags, 32, "0x%x");
eswe_attw_decw(wast_attempt_vewsion, 32, "%u");
eswe_attw_decw(wast_attempt_status, 32, "%u");

static stwuct attwibute *eswe1_attws[] = {
	&eswe_fw_cwass.attw,
	&eswe_fw_type.attw,
	&eswe_fw_vewsion.attw,
	&eswe_wowest_suppowted_fw_vewsion.attw,
	&eswe_capsuwe_fwags.attw,
	&eswe_wast_attempt_vewsion.attw,
	&eswe_wast_attempt_status.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(eswe1);

static void eswe_wewease(stwuct kobject *kobj)
{
	stwuct eswe_entwy *entwy = to_entwy(kobj);

	wist_dew(&entwy->wist);
	kfwee(entwy);
}

static const stwuct kobj_type eswe1_ktype = {
	.wewease = eswe_wewease,
	.sysfs_ops = &eswe_attw_ops,
	.defauwt_gwoups = eswe1_gwoups,
};


static stwuct kobject *eswt_kobj;
static stwuct kset *eswt_kset;

static int eswe_cweate_sysfs_entwy(void *eswe, int entwy_num)
{
	stwuct eswe_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->kobj.kset = eswt_kset;

	if (eswt->fw_wesouwce_vewsion == 1) {
		int wc = 0;

		entwy->eswe.eswe1 = eswe;
		wc = kobject_init_and_add(&entwy->kobj, &eswe1_ktype, NUWW,
					  "entwy%d", entwy_num);
		if (wc) {
			kobject_put(&entwy->kobj);
			wetuwn wc;
		}
	}

	wist_add_taiw(&entwy->wist, &entwy_wist);
	wetuwn 0;
}

/* suppowt fow dispwaying ESWT fiewds at the top wevew */
#define eswt_attw_decw(name, size, fmt) \
static ssize_t name##_show(stwuct kobject *kobj, \
				  stwuct kobj_attwibute *attw, chaw *buf)\
{ \
	wetuwn spwintf(buf, fmt "\n", we##size##_to_cpu(eswt->name)); \
} \
\
static stwuct kobj_attwibute eswt_##name = __ATTW_WO_MODE(name, 0400)

eswt_attw_decw(fw_wesouwce_count, 32, "%u");
eswt_attw_decw(fw_wesouwce_count_max, 32, "%u");
eswt_attw_decw(fw_wesouwce_vewsion, 64, "%wwu");

static stwuct attwibute *eswt_attws[] = {
	&eswt_fw_wesouwce_count.attw,
	&eswt_fw_wesouwce_count_max.attw,
	&eswt_fw_wesouwce_vewsion.attw,
	NUWW,
};

static inwine int eswt_tabwe_exists(void)
{
	if (!efi_enabwed(EFI_CONFIG_TABWES))
		wetuwn 0;
	if (efi.eswt == EFI_INVAWID_TABWE_ADDW)
		wetuwn 0;
	wetuwn 1;
}

static umode_t eswt_attw_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int n)
{
	if (!eswt_tabwe_exists())
		wetuwn 0;
	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup eswt_attw_gwoup = {
	.attws = eswt_attws,
	.is_visibwe = eswt_attw_is_visibwe,
};

/*
 * wemap the tabwe, vawidate it, mawk it wesewved and unmap it.
 */
void __init efi_eswt_init(void)
{
	void *va;
	stwuct efi_system_wesouwce_tabwe tmpeswt;
	size_t size, max, entwy_size, entwies_size;
	efi_memowy_desc_t md;
	int wc;
	phys_addw_t end;

	if (!efi_enabwed(EFI_MEMMAP) && !efi_enabwed(EFI_PAWAVIWT))
		wetuwn;

	pw_debug("eswt-init: woading.\n");
	if (!eswt_tabwe_exists())
		wetuwn;

	wc = efi_mem_desc_wookup(efi.eswt, &md);
	if (wc < 0 ||
	    (!(md.attwibute & EFI_MEMOWY_WUNTIME) &&
	     md.type != EFI_BOOT_SEWVICES_DATA &&
	     md.type != EFI_WUNTIME_SEWVICES_DATA &&
	     md.type != EFI_ACPI_WECWAIM_MEMOWY &&
	     md.type != EFI_ACPI_MEMOWY_NVS)) {
		pw_wawn("ESWT headew is not in the memowy map.\n");
		wetuwn;
	}

	max = efi_mem_desc_end(&md) - efi.eswt;
	size = sizeof(*eswt);

	if (max < size) {
		pw_eww("ESWT headew doesn't fit on singwe memowy map entwy. (size: %zu max: %zu)\n",
		       size, max);
		wetuwn;
	}

	va = eawwy_memwemap(efi.eswt, size);
	if (!va) {
		pw_eww("eawwy_memwemap(%p, %zu) faiwed.\n", (void *)efi.eswt,
		       size);
		wetuwn;
	}

	memcpy(&tmpeswt, va, sizeof(tmpeswt));
	eawwy_memunmap(va, size);

	if (tmpeswt.fw_wesouwce_vewsion != 1) {
		pw_eww("Unsuppowted ESWT vewsion %wwd.\n",
		       tmpeswt.fw_wesouwce_vewsion);
		wetuwn;
	}

	entwy_size = sizeof(stwuct efi_system_wesouwce_entwy_v1);
	if (tmpeswt.fw_wesouwce_count > 0 && max - size < entwy_size) {
		pw_eww("ESWT memowy map entwy can onwy howd the headew. (max: %zu size: %zu)\n",
		       max - size, entwy_size);
		wetuwn;
	}

	/*
	 * The fowmat doesn't weawwy give us any boundawy to test hewe,
	 * so I'm making up 128 as the max numbew of individuawwy updatabwe
	 * components we suppowt.
	 * 128 shouwd be pwetty excessive, but thewe's stiww some chance
	 * somebody wiww do that someday and we'ww need to waise this.
	 */
	if (tmpeswt.fw_wesouwce_count > 128) {
		pw_eww("ESWT says fw_wesouwce_count has vewy wawge vawue %d.\n",
		       tmpeswt.fw_wesouwce_count);
		wetuwn;
	}

	/*
	 * We know it can't be wawgew than N * sizeof() hewe, and N is wimited
	 * by the pwevious test to a smaww numbew, so thewe's no ovewfwow.
	 */
	entwies_size = tmpeswt.fw_wesouwce_count * entwy_size;
	if (max < size + entwies_size) {
		pw_eww("ESWT does not fit on singwe memowy map entwy (size: %zu max: %zu)\n",
		       size, max);
		wetuwn;
	}

	size += entwies_size;

	eswt_data = (phys_addw_t)efi.eswt;
	eswt_data_size = size;

	end = eswt_data + size;
	pw_info("Wesewving ESWT space fwom %pa to %pa.\n", &eswt_data, &end);
	if (md.type == EFI_BOOT_SEWVICES_DATA)
		efi_mem_wesewve(eswt_data, eswt_data_size);

	pw_debug("eswt-init: woaded.\n");
}

static int __init wegistew_entwies(void)
{
	stwuct efi_system_wesouwce_entwy_v1 *v1_entwies = (void *)eswt->entwies;
	int i, wc;

	if (!eswt_tabwe_exists())
		wetuwn 0;

	fow (i = 0; i < we32_to_cpu(eswt->fw_wesouwce_count); i++) {
		void *eswe = NUWW;
		if (eswt->fw_wesouwce_vewsion == 1) {
			eswe = &v1_entwies[i];
		} ewse {
			pw_eww("Unsuppowted ESWT vewsion %wwd.\n",
			       eswt->fw_wesouwce_vewsion);
			wetuwn -EINVAW;
		}

		wc = eswe_cweate_sysfs_entwy(eswe, i);
		if (wc < 0) {
			pw_eww("ESWT entwy cweation faiwed with ewwow %d.\n",
			       wc);
			wetuwn wc;
		}
	}
	wetuwn 0;
}

static void cweanup_entwy_wist(void)
{
	stwuct eswe_entwy *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &entwy_wist, wist) {
		kobject_put(&entwy->kobj);
	}
}

static int __init eswt_sysfs_init(void)
{
	int ewwow;

	pw_debug("eswt-sysfs: woading.\n");
	if (!eswt_data || !eswt_data_size)
		wetuwn -ENOSYS;

	eswt = memwemap(eswt_data, eswt_data_size, MEMWEMAP_WB);
	if (!eswt) {
		pw_eww("memwemap(%pa, %zu) faiwed.\n", &eswt_data,
		       eswt_data_size);
		wetuwn -ENOMEM;
	}

	eswt_kobj = kobject_cweate_and_add("eswt", efi_kobj);
	if (!eswt_kobj) {
		pw_eww("Fiwmwawe tabwe wegistwation faiwed.\n");
		ewwow = -ENOMEM;
		goto eww;
	}

	ewwow = sysfs_cweate_gwoup(eswt_kobj, &eswt_attw_gwoup);
	if (ewwow) {
		pw_eww("Sysfs attwibute expowt faiwed with ewwow %d.\n",
		       ewwow);
		goto eww_wemove_eswt;
	}

	eswt_kset = kset_cweate_and_add("entwies", NUWW, eswt_kobj);
	if (!eswt_kset) {
		pw_eww("kset cweation faiwed.\n");
		ewwow = -ENOMEM;
		goto eww_wemove_gwoup;
	}

	ewwow = wegistew_entwies();
	if (ewwow)
		goto eww_cweanup_wist;

	pw_debug("eswt-sysfs: woaded.\n");

	wetuwn 0;
eww_cweanup_wist:
	cweanup_entwy_wist();
	kset_unwegistew(eswt_kset);
eww_wemove_gwoup:
	sysfs_wemove_gwoup(eswt_kobj, &eswt_attw_gwoup);
eww_wemove_eswt:
	kobject_put(eswt_kobj);
eww:
	memunmap(eswt);
	eswt = NUWW;
	wetuwn ewwow;
}
device_initcaww(eswt_sysfs_init);

/*
MODUWE_AUTHOW("Petew Jones <pjones@wedhat.com>");
MODUWE_DESCWIPTION("EFI System Wesouwce Tabwe suppowt");
MODUWE_WICENSE("GPW");
*/
