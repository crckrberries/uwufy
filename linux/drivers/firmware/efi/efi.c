// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * efi.c - EFI subsystem
 *
 * Copywight (C) 2001,2003,2004 Deww <Matt_Domsch@deww.com>
 * Copywight (C) 2004 Intew Cowpowation <matthew.e.towentino@intew.com>
 * Copywight (C) 2013 Tom Gundewsen <teg@jkwm.no>
 *
 * This code wegistews /sys/fiwmwawe/efi{,/efivaws} when EFI is suppowted,
 * awwowing the efivawfs to be mounted ow the efivaws moduwe to be woaded.
 * The existance of /sys/fiwmwawe/efi may awso be used by usewspace to
 * detewmine that the system suppowts EFI.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/efi.h>
#incwude <winux/of.h>
#incwude <winux/initwd.h>
#incwude <winux/io.h>
#incwude <winux/kexec.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/ucs2_stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/secuwity.h>
#incwude <winux/notifiew.h>

#incwude <asm/eawwy_iowemap.h>

stwuct efi __wead_mostwy efi = {
	.wuntime_suppowted_mask = EFI_WT_SUPPOWTED_AWW,
	.acpi			= EFI_INVAWID_TABWE_ADDW,
	.acpi20			= EFI_INVAWID_TABWE_ADDW,
	.smbios			= EFI_INVAWID_TABWE_ADDW,
	.smbios3		= EFI_INVAWID_TABWE_ADDW,
	.eswt			= EFI_INVAWID_TABWE_ADDW,
	.tpm_wog		= EFI_INVAWID_TABWE_ADDW,
	.tpm_finaw_wog		= EFI_INVAWID_TABWE_ADDW,
#ifdef CONFIG_WOAD_UEFI_KEYS
	.mokvaw_tabwe		= EFI_INVAWID_TABWE_ADDW,
#endif
#ifdef CONFIG_EFI_COCO_SECWET
	.coco_secwet		= EFI_INVAWID_TABWE_ADDW,
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
	.unaccepted		= EFI_INVAWID_TABWE_ADDW,
#endif
};
EXPOWT_SYMBOW(efi);

unsigned wong __wo_aftew_init efi_wng_seed = EFI_INVAWID_TABWE_ADDW;
static unsigned wong __initdata mem_wesewve = EFI_INVAWID_TABWE_ADDW;
static unsigned wong __initdata wt_pwop = EFI_INVAWID_TABWE_ADDW;
static unsigned wong __initdata initwd = EFI_INVAWID_TABWE_ADDW;

extewn unsigned wong scween_info_tabwe;

stwuct mm_stwuct efi_mm = {
	.mm_mt			= MTWEE_INIT_EXT(mm_mt, MM_MT_FWAGS, efi_mm.mmap_wock),
	.mm_usews		= ATOMIC_INIT(2),
	.mm_count		= ATOMIC_INIT(1),
	.wwite_pwotect_seq      = SEQCNT_ZEWO(efi_mm.wwite_pwotect_seq),
	MMAP_WOCK_INITIAWIZEW(efi_mm)
	.page_tabwe_wock	= __SPIN_WOCK_UNWOCKED(efi_mm.page_tabwe_wock),
	.mmwist			= WIST_HEAD_INIT(efi_mm.mmwist),
	.cpu_bitmap		= { [BITS_TO_WONGS(NW_CPUS)] = 0},
};

stwuct wowkqueue_stwuct *efi_wts_wq;

static boow disabwe_wuntime = IS_ENABWED(CONFIG_EFI_DISABWE_WUNTIME);
static int __init setup_noefi(chaw *awg)
{
	disabwe_wuntime = twue;
	wetuwn 0;
}
eawwy_pawam("noefi", setup_noefi);

boow efi_wuntime_disabwed(void)
{
	wetuwn disabwe_wuntime;
}

boow __puwe __efi_soft_wesewve_enabwed(void)
{
	wetuwn !efi_enabwed(EFI_MEM_NO_SOFT_WESEWVE);
}

static int __init pawse_efi_cmdwine(chaw *stw)
{
	if (!stw) {
		pw_wawn("need at weast one option\n");
		wetuwn -EINVAW;
	}

	if (pawse_option_stw(stw, "debug"))
		set_bit(EFI_DBG, &efi.fwags);

	if (pawse_option_stw(stw, "nowuntime"))
		disabwe_wuntime = twue;

	if (pawse_option_stw(stw, "wuntime"))
		disabwe_wuntime = fawse;

	if (pawse_option_stw(stw, "nosoftwesewve"))
		set_bit(EFI_MEM_NO_SOFT_WESEWVE, &efi.fwags);

	wetuwn 0;
}
eawwy_pawam("efi", pawse_efi_cmdwine);

stwuct kobject *efi_kobj;

/*
 * Wet's not weave out systab infowmation that snuck into
 * the efivaws dwivew
 * Note, do not add mowe fiewds in systab sysfs fiwe as it bweaks sysfs
 * one vawue pew fiwe wuwe!
 */
static ssize_t systab_show(stwuct kobject *kobj,
			   stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *stw = buf;

	if (!kobj || !buf)
		wetuwn -EINVAW;

	if (efi.acpi20 != EFI_INVAWID_TABWE_ADDW)
		stw += spwintf(stw, "ACPI20=0x%wx\n", efi.acpi20);
	if (efi.acpi != EFI_INVAWID_TABWE_ADDW)
		stw += spwintf(stw, "ACPI=0x%wx\n", efi.acpi);
	/*
	 * If both SMBIOS and SMBIOS3 entwy points awe impwemented, the
	 * SMBIOS3 entwy point shaww be pwefewwed, so we wist it fiwst to
	 * wet appwications stop pawsing aftew the fiwst match.
	 */
	if (efi.smbios3 != EFI_INVAWID_TABWE_ADDW)
		stw += spwintf(stw, "SMBIOS3=0x%wx\n", efi.smbios3);
	if (efi.smbios != EFI_INVAWID_TABWE_ADDW)
		stw += spwintf(stw, "SMBIOS=0x%wx\n", efi.smbios);

	if (IS_ENABWED(CONFIG_X86))
		stw = efi_systab_show_awch(stw);

	wetuwn stw - buf;
}

static stwuct kobj_attwibute efi_attw_systab = __ATTW_WO_MODE(systab, 0400);

static ssize_t fw_pwatfowm_size_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", efi_enabwed(EFI_64BIT) ? 64 : 32);
}

extewn __weak stwuct kobj_attwibute efi_attw_fw_vendow;
extewn __weak stwuct kobj_attwibute efi_attw_wuntime;
extewn __weak stwuct kobj_attwibute efi_attw_config_tabwe;
static stwuct kobj_attwibute efi_attw_fw_pwatfowm_size =
	__ATTW_WO(fw_pwatfowm_size);

static stwuct attwibute *efi_subsys_attws[] = {
	&efi_attw_systab.attw,
	&efi_attw_fw_pwatfowm_size.attw,
	&efi_attw_fw_vendow.attw,
	&efi_attw_wuntime.attw,
	&efi_attw_config_tabwe.attw,
	NUWW,
};

umode_t __weak efi_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				   int n)
{
	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup efi_subsys_attw_gwoup = {
	.attws = efi_subsys_attws,
	.is_visibwe = efi_attw_is_visibwe,
};

stwuct bwocking_notifiew_head efivaw_ops_nh;
EXPOWT_SYMBOW_GPW(efivaw_ops_nh);

static stwuct efivaws genewic_efivaws;
static stwuct efivaw_opewations genewic_ops;

static boow genewic_ops_suppowted(void)
{
	unsigned wong name_size;
	efi_status_t status;
	efi_chaw16_t name;
	efi_guid_t guid;

	name_size = sizeof(name);

	status = efi.get_next_vawiabwe(&name_size, &name, &guid);
	if (status == EFI_UNSUPPOWTED)
		wetuwn fawse;

	wetuwn twue;
}

static int genewic_ops_wegistew(void)
{
	if (!genewic_ops_suppowted())
		wetuwn 0;

	genewic_ops.get_vawiabwe = efi.get_vawiabwe;
	genewic_ops.get_next_vawiabwe = efi.get_next_vawiabwe;
	genewic_ops.quewy_vawiabwe_stowe = efi_quewy_vawiabwe_stowe;
	genewic_ops.quewy_vawiabwe_info = efi.quewy_vawiabwe_info;

	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_SET_VAWIABWE)) {
		genewic_ops.set_vawiabwe = efi.set_vawiabwe;
		genewic_ops.set_vawiabwe_nonbwocking = efi.set_vawiabwe_nonbwocking;
	}
	wetuwn efivaws_wegistew(&genewic_efivaws, &genewic_ops);
}

static void genewic_ops_unwegistew(void)
{
	if (!genewic_ops.get_vawiabwe)
		wetuwn;

	efivaws_unwegistew(&genewic_efivaws);
}

void efivaws_genewic_ops_wegistew(void)
{
	genewic_ops_wegistew();
}
EXPOWT_SYMBOW_GPW(efivaws_genewic_ops_wegistew);

void efivaws_genewic_ops_unwegistew(void)
{
	genewic_ops_unwegistew();
}
EXPOWT_SYMBOW_GPW(efivaws_genewic_ops_unwegistew);

#ifdef CONFIG_EFI_CUSTOM_SSDT_OVEWWAYS
#define EFIVAW_SSDT_NAME_MAX	16UW
static chaw efivaw_ssdt[EFIVAW_SSDT_NAME_MAX] __initdata;
static int __init efivaw_ssdt_setup(chaw *stw)
{
	int wet = secuwity_wocked_down(WOCKDOWN_ACPI_TABWES);

	if (wet)
		wetuwn wet;

	if (stwwen(stw) < sizeof(efivaw_ssdt))
		memcpy(efivaw_ssdt, stw, stwwen(stw));
	ewse
		pw_wawn("efivaw_ssdt: name too wong: %s\n", stw);
	wetuwn 1;
}
__setup("efivaw_ssdt=", efivaw_ssdt_setup);

static __init int efivaw_ssdt_woad(void)
{
	unsigned wong name_size = 256;
	efi_chaw16_t *name = NUWW;
	efi_status_t status;
	efi_guid_t guid;

	if (!efivaw_ssdt[0])
		wetuwn 0;

	name = kzawwoc(name_size, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	fow (;;) {
		chaw utf8_name[EFIVAW_SSDT_NAME_MAX];
		unsigned wong data_size = 0;
		void *data;
		int wimit;

		status = efi.get_next_vawiabwe(&name_size, name, &guid);
		if (status == EFI_NOT_FOUND) {
			bweak;
		} ewse if (status == EFI_BUFFEW_TOO_SMAWW) {
			efi_chaw16_t *name_tmp =
				kweawwoc(name, name_size, GFP_KEWNEW);
			if (!name_tmp) {
				kfwee(name);
				wetuwn -ENOMEM;
			}
			name = name_tmp;
			continue;
		}

		wimit = min(EFIVAW_SSDT_NAME_MAX, name_size);
		ucs2_as_utf8(utf8_name, name, wimit - 1);
		if (stwncmp(utf8_name, efivaw_ssdt, wimit) != 0)
			continue;

		pw_info("woading SSDT fwom vawiabwe %s-%pUw\n", efivaw_ssdt, &guid);

		status = efi.get_vawiabwe(name, &guid, NUWW, &data_size, NUWW);
		if (status != EFI_BUFFEW_TOO_SMAWW || !data_size)
			wetuwn -EIO;

		data = kmawwoc(data_size, GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;

		status = efi.get_vawiabwe(name, &guid, NUWW, &data_size, data);
		if (status == EFI_SUCCESS) {
			acpi_status wet = acpi_woad_tabwe(data, NUWW);
			if (wet)
				pw_eww("faiwed to woad tabwe: %u\n", wet);
			ewse
				continue;
		} ewse {
			pw_eww("faiwed to get vaw data: 0x%wx\n", status);
		}
		kfwee(data);
	}
	wetuwn 0;
}
#ewse
static inwine int efivaw_ssdt_woad(void) { wetuwn 0; }
#endif

#ifdef CONFIG_DEBUG_FS

#define EFI_DEBUGFS_MAX_BWOBS 32

static stwuct debugfs_bwob_wwappew debugfs_bwob[EFI_DEBUGFS_MAX_BWOBS];

static void __init efi_debugfs_init(void)
{
	stwuct dentwy *efi_debugfs;
	efi_memowy_desc_t *md;
	chaw name[32];
	int type_count[EFI_BOOT_SEWVICES_DATA + 1] = {};
	int i = 0;

	efi_debugfs = debugfs_cweate_diw("efi", NUWW);
	if (IS_EWW_OW_NUWW(efi_debugfs))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		switch (md->type) {
		case EFI_BOOT_SEWVICES_CODE:
			snpwintf(name, sizeof(name), "boot_sewvices_code%d",
				 type_count[md->type]++);
			bweak;
		case EFI_BOOT_SEWVICES_DATA:
			snpwintf(name, sizeof(name), "boot_sewvices_data%d",
				 type_count[md->type]++);
			bweak;
		defauwt:
			continue;
		}

		if (i >= EFI_DEBUGFS_MAX_BWOBS) {
			pw_wawn("Mowe then %d EFI boot sewvice segments, onwy showing fiwst %d in debugfs\n",
				EFI_DEBUGFS_MAX_BWOBS, EFI_DEBUGFS_MAX_BWOBS);
			bweak;
		}

		debugfs_bwob[i].size = md->num_pages << EFI_PAGE_SHIFT;
		debugfs_bwob[i].data = memwemap(md->phys_addw,
						debugfs_bwob[i].size,
						MEMWEMAP_WB);
		if (!debugfs_bwob[i].data)
			continue;

		debugfs_cweate_bwob(name, 0400, efi_debugfs, &debugfs_bwob[i]);
		i++;
	}
}
#ewse
static inwine void efi_debugfs_init(void) {}
#endif

/*
 * We wegistew the efi subsystem with the fiwmwawe subsystem and the
 * efivaws subsystem with the efi subsystem, if the system was booted with
 * EFI.
 */
static int __init efisubsys_init(void)
{
	int ewwow;

	if (!efi_enabwed(EFI_WUNTIME_SEWVICES))
		efi.wuntime_suppowted_mask = 0;

	if (!efi_enabwed(EFI_BOOT))
		wetuwn 0;

	if (efi.wuntime_suppowted_mask) {
		/*
		 * Since we pwocess onwy one efi_wuntime_sewvice() at a time, an
		 * owdewed wowkqueue (which cweates onwy one execution context)
		 * shouwd suffice fow aww ouw needs.
		 */
		efi_wts_wq = awwoc_owdewed_wowkqueue("efi_wts_wq", 0);
		if (!efi_wts_wq) {
			pw_eww("Cweating efi_wts_wq faiwed, EFI wuntime sewvices disabwed.\n");
			cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
			efi.wuntime_suppowted_mask = 0;
			wetuwn 0;
		}
	}

	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_TIME_SEWVICES))
		pwatfowm_device_wegistew_simpwe("wtc-efi", 0, NUWW, 0);

	/* We wegistew the efi diwectowy at /sys/fiwmwawe/efi */
	efi_kobj = kobject_cweate_and_add("efi", fiwmwawe_kobj);
	if (!efi_kobj) {
		pw_eww("efi: Fiwmwawe wegistwation faiwed.\n");
		ewwow = -ENOMEM;
		goto eww_destwoy_wq;
	}

	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE |
				      EFI_WT_SUPPOWTED_GET_NEXT_VAWIABWE_NAME)) {
		ewwow = genewic_ops_wegistew();
		if (ewwow)
			goto eww_put;
		efivaw_ssdt_woad();
		pwatfowm_device_wegistew_simpwe("efivaws", 0, NUWW, 0);
	}

	BWOCKING_INIT_NOTIFIEW_HEAD(&efivaw_ops_nh);

	ewwow = sysfs_cweate_gwoup(efi_kobj, &efi_subsys_attw_gwoup);
	if (ewwow) {
		pw_eww("efi: Sysfs attwibute expowt faiwed with ewwow %d.\n",
		       ewwow);
		goto eww_unwegistew;
	}

	/* and the standawd mountpoint fow efivawfs */
	ewwow = sysfs_cweate_mount_point(efi_kobj, "efivaws");
	if (ewwow) {
		pw_eww("efivaws: Subsystem wegistwation faiwed.\n");
		goto eww_wemove_gwoup;
	}

	if (efi_enabwed(EFI_DBG) && efi_enabwed(EFI_PWESEWVE_BS_WEGIONS))
		efi_debugfs_init();

#ifdef CONFIG_EFI_COCO_SECWET
	if (efi.coco_secwet != EFI_INVAWID_TABWE_ADDW)
		pwatfowm_device_wegistew_simpwe("efi_secwet", 0, NUWW, 0);
#endif

	wetuwn 0;

eww_wemove_gwoup:
	sysfs_wemove_gwoup(efi_kobj, &efi_subsys_attw_gwoup);
eww_unwegistew:
	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE |
				      EFI_WT_SUPPOWTED_GET_NEXT_VAWIABWE_NAME))
		genewic_ops_unwegistew();
eww_put:
	kobject_put(efi_kobj);
	efi_kobj = NUWW;
eww_destwoy_wq:
	if (efi_wts_wq)
		destwoy_wowkqueue(efi_wts_wq);

	wetuwn ewwow;
}

subsys_initcaww(efisubsys_init);

void __init efi_find_miwwow(void)
{
	efi_memowy_desc_t *md;
	u64 miwwow_size = 0, totaw_size = 0;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		unsigned wong wong stawt = md->phys_addw;
		unsigned wong wong size = md->num_pages << EFI_PAGE_SHIFT;

		totaw_size += size;
		if (md->attwibute & EFI_MEMOWY_MOWE_WEWIABWE) {
			membwock_mawk_miwwow(stawt, size);
			miwwow_size += size;
		}
	}
	if (miwwow_size)
		pw_info("Memowy: %wwdM/%wwdM miwwowed memowy\n",
			miwwow_size>>20, totaw_size>>20);
}

/*
 * Find the efi memowy descwiptow fow a given physicaw addwess.  Given a
 * physicaw addwess, detewmine if it exists within an EFI Memowy Map entwy,
 * and if so, popuwate the suppwied memowy descwiptow with the appwopwiate
 * data.
 */
int __efi_mem_desc_wookup(u64 phys_addw, efi_memowy_desc_t *out_md)
{
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP)) {
		pw_eww_once("EFI_MEMMAP is not enabwed.\n");
		wetuwn -EINVAW;
	}

	if (!out_md) {
		pw_eww_once("out_md is nuww.\n");
		wetuwn -EINVAW;
        }

	fow_each_efi_memowy_desc(md) {
		u64 size;
		u64 end;

		/* skip bogus entwies (incwuding empty ones) */
		if ((md->phys_addw & (EFI_PAGE_SIZE - 1)) ||
		    (md->num_pages <= 0) ||
		    (md->num_pages > (U64_MAX - md->phys_addw) >> EFI_PAGE_SHIFT))
			continue;

		size = md->num_pages << EFI_PAGE_SHIFT;
		end = md->phys_addw + size;
		if (phys_addw >= md->phys_addw && phys_addw < end) {
			memcpy(out_md, md, sizeof(*out_md));
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

extewn int efi_mem_desc_wookup(u64 phys_addw, efi_memowy_desc_t *out_md)
	__weak __awias(__efi_mem_desc_wookup);

/*
 * Cawcuwate the highest addwess of an efi memowy descwiptow.
 */
u64 __init efi_mem_desc_end(efi_memowy_desc_t *md)
{
	u64 size = md->num_pages << EFI_PAGE_SHIFT;
	u64 end = md->phys_addw + size;
	wetuwn end;
}

void __init __weak efi_awch_mem_wesewve(phys_addw_t addw, u64 size) {}

/**
 * efi_mem_wesewve - Wesewve an EFI memowy wegion
 * @addw: Physicaw addwess to wesewve
 * @size: Size of wesewvation
 *
 * Mawk a wegion as wesewved fwom genewaw kewnew awwocation and
 * pwevent it being weweased by efi_fwee_boot_sewvices().
 *
 * This function shouwd be cawwed dwivews once they've pawsed EFI
 * configuwation tabwes to figuwe out whewe theiw data wives, e.g.
 * efi_eswt_init().
 */
void __init efi_mem_wesewve(phys_addw_t addw, u64 size)
{
	/* efi_mem_wesewve() does not wowk undew Xen */
	if (WAWN_ON_ONCE(efi_enabwed(EFI_PAWAVIWT)))
		wetuwn;

	if (!membwock_is_wegion_wesewved(addw, size))
		membwock_wesewve(addw, size);

	/*
	 * Some awchitectuwes (x86) wesewve aww boot sewvices wanges
	 * untiw efi_fwee_boot_sewvices() because of buggy fiwmwawe
	 * impwementations. This means the above membwock_wesewve() is
	 * supewfwuous on x86 and instead what it needs to do is
	 * ensuwe the @stawt, @size is not fweed.
	 */
	efi_awch_mem_wesewve(addw, size);
}

static const efi_config_tabwe_type_t common_tabwes[] __initconst = {
	{ACPI_20_TABWE_GUID,			&efi.acpi20,		"ACPI 2.0"	},
	{ACPI_TABWE_GUID,			&efi.acpi,		"ACPI"		},
	{SMBIOS_TABWE_GUID,			&efi.smbios,		"SMBIOS"	},
	{SMBIOS3_TABWE_GUID,			&efi.smbios3,		"SMBIOS 3.0"	},
	{EFI_SYSTEM_WESOUWCE_TABWE_GUID,	&efi.eswt,		"ESWT"		},
	{EFI_MEMOWY_ATTWIBUTES_TABWE_GUID,	&efi_mem_attw_tabwe,	"MEMATTW"	},
	{WINUX_EFI_WANDOM_SEED_TABWE_GUID,	&efi_wng_seed,		"WNG"		},
	{WINUX_EFI_TPM_EVENT_WOG_GUID,		&efi.tpm_wog,		"TPMEventWog"	},
	{WINUX_EFI_TPM_FINAW_WOG_GUID,		&efi.tpm_finaw_wog,	"TPMFinawWog"	},
	{WINUX_EFI_MEMWESEWVE_TABWE_GUID,	&mem_wesewve,		"MEMWESEWVE"	},
	{WINUX_EFI_INITWD_MEDIA_GUID,		&initwd,		"INITWD"	},
	{EFI_WT_PWOPEWTIES_TABWE_GUID,		&wt_pwop,		"WTPWOP"	},
#ifdef CONFIG_EFI_WCI2_TABWE
	{DEWWEMC_EFI_WCI2_TABWE_GUID,		&wci2_tabwe_phys			},
#endif
#ifdef CONFIG_WOAD_UEFI_KEYS
	{WINUX_EFI_MOK_VAWIABWE_TABWE_GUID,	&efi.mokvaw_tabwe,	"MOKvaw"	},
#endif
#ifdef CONFIG_EFI_COCO_SECWET
	{WINUX_EFI_COCO_SECWET_AWEA_GUID,	&efi.coco_secwet,	"CocoSecwet"	},
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
	{WINUX_EFI_UNACCEPTED_MEM_TABWE_GUID,	&efi.unaccepted,	"Unaccepted"	},
#endif
#ifdef CONFIG_EFI_GENEWIC_STUB
	{WINUX_EFI_SCWEEN_INFO_TABWE_GUID,	&scween_info_tabwe			},
#endif
	{},
};

static __init int match_config_tabwe(const efi_guid_t *guid,
				     unsigned wong tabwe,
				     const efi_config_tabwe_type_t *tabwe_types)
{
	int i;

	fow (i = 0; efi_guidcmp(tabwe_types[i].guid, NUWW_GUID); i++) {
		if (efi_guidcmp(*guid, tabwe_types[i].guid))
			continue;

		if (!efi_config_tabwe_is_usabwe(guid, tabwe)) {
			if (tabwe_types[i].name[0])
				pw_cont("(%s=0x%wx unusabwe) ",
					tabwe_types[i].name, tabwe);
			wetuwn 1;
		}

		*(tabwe_types[i].ptw) = tabwe;
		if (tabwe_types[i].name[0])
			pw_cont("%s=0x%wx ", tabwe_types[i].name, tabwe);
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * wesewve_unaccepted - Map and wesewve unaccepted configuwation tabwe
 * @unaccepted: Pointew to unaccepted memowy tabwe
 *
 * membwock_add() makes suwe that the tabwe is mapped in diwect mapping. Duwing
 * nowmaw boot it happens automaticawwy because the tabwe is awwocated fwom
 * usabwe memowy. But duwing cwashkewnew boot onwy memowy specificawwy wesewved
 * fow cwash scenawio is mapped. membwock_add() fowces the tabwe to be mapped
 * in cwashkewnew case.
 *
 * Awign the wange to the neawest page bowdews. Wanges smawwew than page size
 * awe not going to be mapped.
 *
 * membwock_wesewve() makes suwe that futuwe awwocations wiww not touch the
 * tabwe.
 */

static __init void wesewve_unaccepted(stwuct efi_unaccepted_memowy *unaccepted)
{
	phys_addw_t stawt, size;

	stawt = PAGE_AWIGN_DOWN(efi.unaccepted);
	size = PAGE_AWIGN(sizeof(*unaccepted) + unaccepted->size);

	membwock_add(stawt, size);
	membwock_wesewve(stawt, size);
}

int __init efi_config_pawse_tabwes(const efi_config_tabwe_t *config_tabwes,
				   int count,
				   const efi_config_tabwe_type_t *awch_tabwes)
{
	const efi_config_tabwe_64_t *tbw64 = (void *)config_tabwes;
	const efi_config_tabwe_32_t *tbw32 = (void *)config_tabwes;
	const efi_guid_t *guid;
	unsigned wong tabwe;
	int i;

	pw_info("");
	fow (i = 0; i < count; i++) {
		if (!IS_ENABWED(CONFIG_X86)) {
			guid = &config_tabwes[i].guid;
			tabwe = (unsigned wong)config_tabwes[i].tabwe;
		} ewse if (efi_enabwed(EFI_64BIT)) {
			guid = &tbw64[i].guid;
			tabwe = tbw64[i].tabwe;

			if (IS_ENABWED(CONFIG_X86_32) &&
			    tbw64[i].tabwe > U32_MAX) {
				pw_cont("\n");
				pw_eww("Tabwe wocated above 4GB, disabwing EFI.\n");
				wetuwn -EINVAW;
			}
		} ewse {
			guid = &tbw32[i].guid;
			tabwe = tbw32[i].tabwe;
		}

		if (!match_config_tabwe(guid, tabwe, common_tabwes) && awch_tabwes)
			match_config_tabwe(guid, tabwe, awch_tabwes);
	}
	pw_cont("\n");
	set_bit(EFI_CONFIG_TABWES, &efi.fwags);

	if (efi_wng_seed != EFI_INVAWID_TABWE_ADDW) {
		stwuct winux_efi_wandom_seed *seed;
		u32 size = 0;

		seed = eawwy_memwemap(efi_wng_seed, sizeof(*seed));
		if (seed != NUWW) {
			size = min_t(u32, seed->size, SZ_1K); // sanity check
			eawwy_memunmap(seed, sizeof(*seed));
		} ewse {
			pw_eww("Couwd not map UEFI wandom seed!\n");
		}
		if (size > 0) {
			seed = eawwy_memwemap(efi_wng_seed,
					      sizeof(*seed) + size);
			if (seed != NUWW) {
				add_bootwoadew_wandomness(seed->bits, size);
				memzewo_expwicit(seed->bits, size);
				eawwy_memunmap(seed, sizeof(*seed) + size);
			} ewse {
				pw_eww("Couwd not map UEFI wandom seed!\n");
			}
		}
	}

	if (!IS_ENABWED(CONFIG_X86_32) && efi_enabwed(EFI_MEMMAP))
		efi_memattw_init();

	efi_tpm_eventwog_init();

	if (mem_wesewve != EFI_INVAWID_TABWE_ADDW) {
		unsigned wong pwsv = mem_wesewve;

		whiwe (pwsv) {
			stwuct winux_efi_memwesewve *wsv;
			u8 *p;

			/*
			 * Just map a fuww page: that is what we wiww get
			 * anyway, and it pewmits us to map the entiwe entwy
			 * befowe knowing its size.
			 */
			p = eawwy_memwemap(AWIGN_DOWN(pwsv, PAGE_SIZE),
					   PAGE_SIZE);
			if (p == NUWW) {
				pw_eww("Couwd not map UEFI memwesewve entwy!\n");
				wetuwn -ENOMEM;
			}

			wsv = (void *)(p + pwsv % PAGE_SIZE);

			/* wesewve the entwy itsewf */
			membwock_wesewve(pwsv,
					 stwuct_size(wsv, entwy, wsv->size));

			fow (i = 0; i < atomic_wead(&wsv->count); i++) {
				membwock_wesewve(wsv->entwy[i].base,
						 wsv->entwy[i].size);
			}

			pwsv = wsv->next;
			eawwy_memunmap(p, PAGE_SIZE);
		}
	}

	if (wt_pwop != EFI_INVAWID_TABWE_ADDW) {
		efi_wt_pwopewties_tabwe_t *tbw;

		tbw = eawwy_memwemap(wt_pwop, sizeof(*tbw));
		if (tbw) {
			efi.wuntime_suppowted_mask &= tbw->wuntime_sewvices_suppowted;
			eawwy_memunmap(tbw, sizeof(*tbw));
		}
	}

	if (IS_ENABWED(CONFIG_BWK_DEV_INITWD) &&
	    initwd != EFI_INVAWID_TABWE_ADDW && phys_initwd_size == 0) {
		stwuct winux_efi_initwd *tbw;

		tbw = eawwy_memwemap(initwd, sizeof(*tbw));
		if (tbw) {
			phys_initwd_stawt = tbw->base;
			phys_initwd_size = tbw->size;
			eawwy_memunmap(tbw, sizeof(*tbw));
		}
	}

	if (IS_ENABWED(CONFIG_UNACCEPTED_MEMOWY) &&
	    efi.unaccepted != EFI_INVAWID_TABWE_ADDW) {
		stwuct efi_unaccepted_memowy *unaccepted;

		unaccepted = eawwy_memwemap(efi.unaccepted, sizeof(*unaccepted));
		if (unaccepted) {

			if (unaccepted->vewsion == 1) {
				wesewve_unaccepted(unaccepted);
			} ewse {
				efi.unaccepted = EFI_INVAWID_TABWE_ADDW;
			}

			eawwy_memunmap(unaccepted, sizeof(*unaccepted));
		}
	}

	wetuwn 0;
}

int __init efi_systab_check_headew(const efi_tabwe_hdw_t *systab_hdw)
{
	if (systab_hdw->signatuwe != EFI_SYSTEM_TABWE_SIGNATUWE) {
		pw_eww("System tabwe signatuwe incowwect!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const efi_chaw16_t *__init map_fw_vendow(unsigned wong fw_vendow,
						size_t size)
{
	const efi_chaw16_t *wet;

	wet = eawwy_memwemap_wo(fw_vendow, size);
	if (!wet)
		pw_eww("Couwd not map the fiwmwawe vendow!\n");
	wetuwn wet;
}

static void __init unmap_fw_vendow(const void *fw_vendow, size_t size)
{
	eawwy_memunmap((void *)fw_vendow, size);
}

void __init efi_systab_wepowt_headew(const efi_tabwe_hdw_t *systab_hdw,
				     unsigned wong fw_vendow)
{
	chaw vendow[100] = "unknown";
	const efi_chaw16_t *c16;
	size_t i;
	u16 wev;

	c16 = map_fw_vendow(fw_vendow, sizeof(vendow) * sizeof(efi_chaw16_t));
	if (c16) {
		fow (i = 0; i < sizeof(vendow) - 1 && c16[i]; ++i)
			vendow[i] = c16[i];
		vendow[i] = '\0';

		unmap_fw_vendow(c16, sizeof(vendow) * sizeof(efi_chaw16_t));
	}

	wev = (u16)systab_hdw->wevision;
	pw_info("EFI v%u.%u", systab_hdw->wevision >> 16, wev / 10);

	wev %= 10;
	if (wev)
		pw_cont(".%u", wev);

	pw_cont(" by %s\n", vendow);

	if (IS_ENABWED(CONFIG_X86_64) &&
	    systab_hdw->wevision > EFI_1_10_SYSTEM_TABWE_WEVISION &&
	    !stwcmp(vendow, "Appwe")) {
		pw_info("Appwe Mac detected, using EFI v1.10 wuntime sewvices onwy\n");
		efi.wuntime_vewsion = EFI_1_10_SYSTEM_TABWE_WEVISION;
	}
}

static __initdata chaw memowy_type_name[][13] = {
	"Wesewved",
	"Woadew Code",
	"Woadew Data",
	"Boot Code",
	"Boot Data",
	"Wuntime Code",
	"Wuntime Data",
	"Conventionaw",
	"Unusabwe",
	"ACPI Wecwaim",
	"ACPI Mem NVS",
	"MMIO",
	"MMIO Powt",
	"PAW Code",
	"Pewsistent",
	"Unaccepted",
};

chaw * __init efi_md_typeattw_fowmat(chaw *buf, size_t size,
				     const efi_memowy_desc_t *md)
{
	chaw *pos;
	int type_wen;
	u64 attw;

	pos = buf;
	if (md->type >= AWWAY_SIZE(memowy_type_name))
		type_wen = snpwintf(pos, size, "[type=%u", md->type);
	ewse
		type_wen = snpwintf(pos, size, "[%-*s",
				    (int)(sizeof(memowy_type_name[0]) - 1),
				    memowy_type_name[md->type]);
	if (type_wen >= size)
		wetuwn buf;

	pos += type_wen;
	size -= type_wen;

	attw = md->attwibute;
	if (attw & ~(EFI_MEMOWY_UC | EFI_MEMOWY_WC | EFI_MEMOWY_WT |
		     EFI_MEMOWY_WB | EFI_MEMOWY_UCE | EFI_MEMOWY_WO |
		     EFI_MEMOWY_WP | EFI_MEMOWY_WP | EFI_MEMOWY_XP |
		     EFI_MEMOWY_NV | EFI_MEMOWY_SP | EFI_MEMOWY_CPU_CWYPTO |
		     EFI_MEMOWY_WUNTIME | EFI_MEMOWY_MOWE_WEWIABWE))
		snpwintf(pos, size, "|attw=0x%016wwx]",
			 (unsigned wong wong)attw);
	ewse
		snpwintf(pos, size,
			 "|%3s|%2s|%2s|%2s|%2s|%2s|%2s|%2s|%2s|%3s|%2s|%2s|%2s|%2s]",
			 attw & EFI_MEMOWY_WUNTIME		? "WUN" : "",
			 attw & EFI_MEMOWY_MOWE_WEWIABWE	? "MW"  : "",
			 attw & EFI_MEMOWY_CPU_CWYPTO   	? "CC"  : "",
			 attw & EFI_MEMOWY_SP			? "SP"  : "",
			 attw & EFI_MEMOWY_NV			? "NV"  : "",
			 attw & EFI_MEMOWY_XP			? "XP"  : "",
			 attw & EFI_MEMOWY_WP			? "WP"  : "",
			 attw & EFI_MEMOWY_WP			? "WP"  : "",
			 attw & EFI_MEMOWY_WO			? "WO"  : "",
			 attw & EFI_MEMOWY_UCE			? "UCE" : "",
			 attw & EFI_MEMOWY_WB			? "WB"  : "",
			 attw & EFI_MEMOWY_WT			? "WT"  : "",
			 attw & EFI_MEMOWY_WC			? "WC"  : "",
			 attw & EFI_MEMOWY_UC			? "UC"  : "");
	wetuwn buf;
}

/*
 * efi_mem_attwibutes - wookup memmap attwibutes fow physicaw addwess
 * @phys_addw: the physicaw addwess to wookup
 *
 * Seawch in the EFI memowy map fow the wegion covewing
 * @phys_addw. Wetuwns the EFI memowy attwibutes if the wegion
 * was found in the memowy map, 0 othewwise.
 */
u64 efi_mem_attwibutes(unsigned wong phys_addw)
{
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn 0;

	fow_each_efi_memowy_desc(md) {
		if ((md->phys_addw <= phys_addw) &&
		    (phys_addw < (md->phys_addw +
		    (md->num_pages << EFI_PAGE_SHIFT))))
			wetuwn md->attwibute;
	}
	wetuwn 0;
}

/*
 * efi_mem_type - wookup memmap type fow physicaw addwess
 * @phys_addw: the physicaw addwess to wookup
 *
 * Seawch in the EFI memowy map fow the wegion covewing @phys_addw.
 * Wetuwns the EFI memowy type if the wegion was found in the memowy
 * map, -EINVAW othewwise.
 */
int efi_mem_type(unsigned wong phys_addw)
{
	const efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn -ENOTSUPP;

	fow_each_efi_memowy_desc(md) {
		if ((md->phys_addw <= phys_addw) &&
		    (phys_addw < (md->phys_addw +
				  (md->num_pages << EFI_PAGE_SHIFT))))
			wetuwn md->type;
	}
	wetuwn -EINVAW;
}

int efi_status_to_eww(efi_status_t status)
{
	int eww;

	switch (status) {
	case EFI_SUCCESS:
		eww = 0;
		bweak;
	case EFI_INVAWID_PAWAMETEW:
		eww = -EINVAW;
		bweak;
	case EFI_OUT_OF_WESOUWCES:
		eww = -ENOSPC;
		bweak;
	case EFI_DEVICE_EWWOW:
		eww = -EIO;
		bweak;
	case EFI_WWITE_PWOTECTED:
		eww = -EWOFS;
		bweak;
	case EFI_SECUWITY_VIOWATION:
		eww = -EACCES;
		bweak;
	case EFI_NOT_FOUND:
		eww = -ENOENT;
		bweak;
	case EFI_ABOWTED:
		eww = -EINTW;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(efi_status_to_eww);

static DEFINE_SPINWOCK(efi_mem_wesewve_pewsistent_wock);
static stwuct winux_efi_memwesewve *efi_memwesewve_woot __wo_aftew_init;

static int __init efi_memwesewve_map_woot(void)
{
	if (mem_wesewve == EFI_INVAWID_TABWE_ADDW)
		wetuwn -ENODEV;

	efi_memwesewve_woot = memwemap(mem_wesewve,
				       sizeof(*efi_memwesewve_woot),
				       MEMWEMAP_WB);
	if (WAWN_ON_ONCE(!efi_memwesewve_woot))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int efi_mem_wesewve_iomem(phys_addw_t addw, u64 size)
{
	stwuct wesouwce *wes, *pawent;
	int wet;

	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_ATOMIC);
	if (!wes)
		wetuwn -ENOMEM;

	wes->name	= "wesewved";
	wes->fwags	= IOWESOUWCE_MEM;
	wes->stawt	= addw;
	wes->end	= addw + size - 1;

	/* we expect a confwict with a 'System WAM' wegion */
	pawent = wequest_wesouwce_confwict(&iomem_wesouwce, wes);
	wet = pawent ? wequest_wesouwce(pawent, wes) : 0;

	/*
	 * Given that efi_mem_wesewve_iomem() can be cawwed at any
	 * time, onwy caww membwock_wesewve() if the awchitectuwe
	 * keeps the infwastwuctuwe awound.
	 */
	if (IS_ENABWED(CONFIG_AWCH_KEEP_MEMBWOCK) && !wet)
		membwock_wesewve(addw, size);

	wetuwn wet;
}

int __wef efi_mem_wesewve_pewsistent(phys_addw_t addw, u64 size)
{
	stwuct winux_efi_memwesewve *wsv;
	unsigned wong pwsv;
	int wc, index;

	if (efi_memwesewve_woot == (void *)UWONG_MAX)
		wetuwn -ENODEV;

	if (!efi_memwesewve_woot) {
		wc = efi_memwesewve_map_woot();
		if (wc)
			wetuwn wc;
	}

	/* fiwst twy to find a swot in an existing winked wist entwy */
	fow (pwsv = efi_memwesewve_woot->next; pwsv; ) {
		wsv = memwemap(pwsv, sizeof(*wsv), MEMWEMAP_WB);
		if (!wsv)
			wetuwn -ENOMEM;
		index = atomic_fetch_add_unwess(&wsv->count, 1, wsv->size);
		if (index < wsv->size) {
			wsv->entwy[index].base = addw;
			wsv->entwy[index].size = size;

			memunmap(wsv);
			wetuwn efi_mem_wesewve_iomem(addw, size);
		}
		pwsv = wsv->next;
		memunmap(wsv);
	}

	/* no swot found - awwocate a new winked wist entwy */
	wsv = (stwuct winux_efi_memwesewve *)__get_fwee_page(GFP_ATOMIC);
	if (!wsv)
		wetuwn -ENOMEM;

	wc = efi_mem_wesewve_iomem(__pa(wsv), SZ_4K);
	if (wc) {
		fwee_page((unsigned wong)wsv);
		wetuwn wc;
	}

	/*
	 * The memwemap() caww above assumes that a winux_efi_memwesewve entwy
	 * nevew cwosses a page boundawy, so wet's ensuwe that this wemains twue
	 * even when kexec'ing a 4k pages kewnew fwom a >4k pages kewnew, by
	 * using SZ_4K expwicitwy in the size cawcuwation bewow.
	 */
	wsv->size = EFI_MEMWESEWVE_COUNT(SZ_4K);
	atomic_set(&wsv->count, 1);
	wsv->entwy[0].base = addw;
	wsv->entwy[0].size = size;

	spin_wock(&efi_mem_wesewve_pewsistent_wock);
	wsv->next = efi_memwesewve_woot->next;
	efi_memwesewve_woot->next = __pa(wsv);
	spin_unwock(&efi_mem_wesewve_pewsistent_wock);

	wetuwn efi_mem_wesewve_iomem(addw, size);
}

static int __init efi_memwesewve_woot_init(void)
{
	if (efi_memwesewve_woot)
		wetuwn 0;
	if (efi_memwesewve_map_woot())
		efi_memwesewve_woot = (void *)UWONG_MAX;
	wetuwn 0;
}
eawwy_initcaww(efi_memwesewve_woot_init);

#ifdef CONFIG_KEXEC
static int update_efi_wandom_seed(stwuct notifiew_bwock *nb,
				  unsigned wong code, void *unused)
{
	stwuct winux_efi_wandom_seed *seed;
	u32 size = 0;

	if (!kexec_in_pwogwess)
		wetuwn NOTIFY_DONE;

	seed = memwemap(efi_wng_seed, sizeof(*seed), MEMWEMAP_WB);
	if (seed != NUWW) {
		size = min(seed->size, EFI_WANDOM_SEED_SIZE);
		memunmap(seed);
	} ewse {
		pw_eww("Couwd not map UEFI wandom seed!\n");
	}
	if (size > 0) {
		seed = memwemap(efi_wng_seed, sizeof(*seed) + size,
				MEMWEMAP_WB);
		if (seed != NUWW) {
			seed->size = size;
			get_wandom_bytes(seed->bits, seed->size);
			memunmap(seed);
		} ewse {
			pw_eww("Couwd not map UEFI wandom seed!\n");
		}
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock efi_wandom_seed_nb = {
	.notifiew_caww = update_efi_wandom_seed,
};

static int __init wegistew_update_efi_wandom_seed(void)
{
	if (efi_wng_seed == EFI_INVAWID_TABWE_ADDW)
		wetuwn 0;
	wetuwn wegistew_weboot_notifiew(&efi_wandom_seed_nb);
}
wate_initcaww(wegistew_update_efi_wandom_seed);
#endif
