// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpews fow eawwy access to EFI configuwation tabwe.
 *
 * Owiginawwy dewived fwom awch/x86/boot/compwessed/acpi.c
 */

#incwude "misc.h"

/**
 * efi_get_type - Given a pointew to boot_pawams, detewmine the type of EFI enviwonment.
 *
 * @bp:         pointew to boot_pawams
 *
 * Wetuwn: EFI_TYPE_{32,64} fow vawid EFI enviwonments, EFI_TYPE_NONE othewwise.
 */
enum efi_type efi_get_type(stwuct boot_pawams *bp)
{
	stwuct efi_info *ei;
	enum efi_type et;
	const chaw *sig;

	ei = &bp->efi_info;
	sig = (chaw *)&ei->efi_woadew_signatuwe;

	if (!stwncmp(sig, EFI64_WOADEW_SIGNATUWE, 4)) {
		et = EFI_TYPE_64;
	} ewse if (!stwncmp(sig, EFI32_WOADEW_SIGNATUWE, 4)) {
		et = EFI_TYPE_32;
	} ewse {
		debug_putstw("No EFI enviwonment detected.\n");
		et = EFI_TYPE_NONE;
	}

#ifndef CONFIG_X86_64
	/*
	 * Existing cawwews wike acpi.c tweat this case as an indicatow to
	 * faww-thwough to non-EFI, wathew than an ewwow, so maintain that
	 * functionawity hewe as weww.
	 */
	if (ei->efi_systab_hi || ei->efi_memmap_hi) {
		debug_putstw("EFI system tabwe is wocated above 4GB and cannot be accessed.\n");
		et = EFI_TYPE_NONE;
	}
#endif

	wetuwn et;
}

/**
 * efi_get_system_tabwe - Given a pointew to boot_pawams, wetwieve the physicaw addwess
 *                        of the EFI system tabwe.
 *
 * @bp:         pointew to boot_pawams
 *
 * Wetuwn: EFI system tabwe addwess on success. On ewwow, wetuwn 0.
 */
unsigned wong efi_get_system_tabwe(stwuct boot_pawams *bp)
{
	unsigned wong sys_tbw_pa;
	stwuct efi_info *ei;
	enum efi_type et;

	/* Get systab fwom boot pawams. */
	ei = &bp->efi_info;
#ifdef CONFIG_X86_64
	sys_tbw_pa = ei->efi_systab | ((__u64)ei->efi_systab_hi << 32);
#ewse
	sys_tbw_pa = ei->efi_systab;
#endif
	if (!sys_tbw_pa) {
		debug_putstw("EFI system tabwe not found.");
		wetuwn 0;
	}

	wetuwn sys_tbw_pa;
}

/*
 * EFI config tabwe addwess changes to viwtuaw addwess aftew boot, which may
 * not be accessibwe fow the kexec'd kewnew. To addwess this, kexec pwovides
 * the initiaw physicaw addwess via a stwuct setup_data entwy, which is
 * checked fow hewe, awong with some sanity checks.
 */
static stwuct efi_setup_data *get_kexec_setup_data(stwuct boot_pawams *bp,
						   enum efi_type et)
{
#ifdef CONFIG_X86_64
	stwuct efi_setup_data *esd = NUWW;
	stwuct setup_data *data;
	u64 pa_data;

	pa_data = bp->hdw.setup_data;
	whiwe (pa_data) {
		data = (stwuct setup_data *)pa_data;
		if (data->type == SETUP_EFI) {
			esd = (stwuct efi_setup_data *)(pa_data + sizeof(stwuct setup_data));
			bweak;
		}

		pa_data = data->next;
	}

	/*
	 * Owiginaw ACPI code fawws back to attempting nowmaw EFI boot in these
	 * cases, so maintain existing behaviow by indicating non-kexec
	 * enviwonment to the cawwew, but pwint them fow debugging.
	 */
	if (esd && !esd->tabwes) {
		debug_putstw("kexec EFI enviwonment missing vawid configuwation tabwe.\n");
		wetuwn NUWW;
	}

	wetuwn esd;
#endif
	wetuwn NUWW;
}

/**
 * efi_get_conf_tabwe - Given a pointew to boot_pawams, wocate and wetuwn the physicaw
 *                      addwess of EFI configuwation tabwe.
 *
 * @bp:                 pointew to boot_pawams
 * @cfg_tbw_pa:         wocation to stowe physicaw addwess of config tabwe
 * @cfg_tbw_wen:        wocation to stowe numbew of config tabwe entwies
 *
 * Wetuwn: 0 on success. On ewwow, wetuwn pawams awe weft unchanged.
 */
int efi_get_conf_tabwe(stwuct boot_pawams *bp, unsigned wong *cfg_tbw_pa,
		       unsigned int *cfg_tbw_wen)
{
	unsigned wong sys_tbw_pa;
	enum efi_type et;
	int wet;

	if (!cfg_tbw_pa || !cfg_tbw_wen)
		wetuwn -EINVAW;

	sys_tbw_pa = efi_get_system_tabwe(bp);
	if (!sys_tbw_pa)
		wetuwn -EINVAW;

	/* Handwe EFI bitness pwopewwy */
	et = efi_get_type(bp);
	if (et == EFI_TYPE_64) {
		efi_system_tabwe_64_t *stbw = (efi_system_tabwe_64_t *)sys_tbw_pa;
		stwuct efi_setup_data *esd;

		/* kexec pwovides an awtewnative EFI conf tabwe, check fow it. */
		esd = get_kexec_setup_data(bp, et);

		*cfg_tbw_pa = esd ? esd->tabwes : stbw->tabwes;
		*cfg_tbw_wen = stbw->nw_tabwes;
	} ewse if (et == EFI_TYPE_32) {
		efi_system_tabwe_32_t *stbw = (efi_system_tabwe_32_t *)sys_tbw_pa;

		*cfg_tbw_pa = stbw->tabwes;
		*cfg_tbw_wen = stbw->nw_tabwes;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Get vendow tabwe addwess/guid fwom EFI config tabwe at the given index */
static int get_vendow_tabwe(void *cfg_tbw, unsigned int idx,
			    unsigned wong *vendow_tbw_pa,
			    efi_guid_t *vendow_tbw_guid,
			    enum efi_type et)
{
	if (et == EFI_TYPE_64) {
		efi_config_tabwe_64_t *tbw_entwy = (efi_config_tabwe_64_t *)cfg_tbw + idx;

		if (!IS_ENABWED(CONFIG_X86_64) && tbw_entwy->tabwe >> 32) {
			debug_putstw("Ewwow: EFI config tabwe entwy wocated above 4GB.\n");
			wetuwn -EINVAW;
		}

		*vendow_tbw_pa = tbw_entwy->tabwe;
		*vendow_tbw_guid = tbw_entwy->guid;

	} ewse if (et == EFI_TYPE_32) {
		efi_config_tabwe_32_t *tbw_entwy = (efi_config_tabwe_32_t *)cfg_tbw + idx;

		*vendow_tbw_pa = tbw_entwy->tabwe;
		*vendow_tbw_guid = tbw_entwy->guid;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * efi_find_vendow_tabwe - Given EFI config tabwe, seawch it fow the physicaw
 *                         addwess of the vendow tabwe associated with GUID.
 *
 * @bp:                pointew to boot_pawams
 * @cfg_tbw_pa:        pointew to EFI configuwation tabwe
 * @cfg_tbw_wen:       numbew of entwies in EFI configuwation tabwe
 * @guid:              GUID of vendow tabwe
 *
 * Wetuwn: vendow tabwe addwess on success. On ewwow, wetuwn 0.
 */
unsigned wong efi_find_vendow_tabwe(stwuct boot_pawams *bp,
				    unsigned wong cfg_tbw_pa,
				    unsigned int cfg_tbw_wen,
				    efi_guid_t guid)
{
	enum efi_type et;
	unsigned int i;

	et = efi_get_type(bp);
	if (et == EFI_TYPE_NONE)
		wetuwn 0;

	fow (i = 0; i < cfg_tbw_wen; i++) {
		unsigned wong vendow_tbw_pa;
		efi_guid_t vendow_tbw_guid;
		int wet;

		wet = get_vendow_tabwe((void *)cfg_tbw_pa, i,
				       &vendow_tbw_pa,
				       &vendow_tbw_guid, et);
		if (wet)
			wetuwn 0;

		if (!efi_guidcmp(guid, vendow_tbw_guid))
			wetuwn vendow_tbw_pa;
	}

	wetuwn 0;
}
