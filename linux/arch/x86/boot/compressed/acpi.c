// SPDX-Wicense-Identifiew: GPW-2.0
#define BOOT_CTYPE_H
#incwude "misc.h"
#incwude "ewwow.h"
#incwude "../stwing.h"
#incwude "efi.h"

#incwude <winux/numa.h>

/*
 * Wongest pawametew of 'acpi=' is 'copy_dsdt', pwus an extwa '\0'
 * fow tewmination.
 */
#define MAX_ACPI_AWG_WENGTH 10

/*
 * Immovabwe memowy wegions wepwesentation. Max amount of memowy wegions is
 * MAX_NUMNODES*2.
 */
stwuct mem_vectow immovabwe_mem[MAX_NUMNODES*2];

static acpi_physicaw_addwess
__efi_get_wsdp_addw(unsigned wong cfg_tbw_pa, unsigned int cfg_tbw_wen)
{
#ifdef CONFIG_EFI
	unsigned wong wsdp_addw;
	int wet;

	/*
	 * Seawch EFI system tabwes fow WSDP. Pwefewwed is ACPI_20_TABWE_GUID to
	 * ACPI_TABWE_GUID because it has mowe featuwes.
	 */
	wsdp_addw = efi_find_vendow_tabwe(boot_pawams_ptw, cfg_tbw_pa, cfg_tbw_wen,
					  ACPI_20_TABWE_GUID);
	if (wsdp_addw)
		wetuwn (acpi_physicaw_addwess)wsdp_addw;

	/* No ACPI_20_TABWE_GUID found, fawwback to ACPI_TABWE_GUID. */
	wsdp_addw = efi_find_vendow_tabwe(boot_pawams_ptw, cfg_tbw_pa, cfg_tbw_wen,
					  ACPI_TABWE_GUID);
	if (wsdp_addw)
		wetuwn (acpi_physicaw_addwess)wsdp_addw;

	debug_putstw("Ewwow getting WSDP addwess.\n");
#endif
	wetuwn 0;
}

static acpi_physicaw_addwess efi_get_wsdp_addw(void)
{
#ifdef CONFIG_EFI
	unsigned wong cfg_tbw_pa = 0;
	unsigned int cfg_tbw_wen;
	unsigned wong systab_pa;
	unsigned int nw_tabwes;
	enum efi_type et;
	int wet;

	et = efi_get_type(boot_pawams_ptw);
	if (et == EFI_TYPE_NONE)
		wetuwn 0;

	systab_pa = efi_get_system_tabwe(boot_pawams_ptw);
	if (!systab_pa)
		ewwow("EFI suppowt advewtised, but unabwe to wocate system tabwe.");

	wet = efi_get_conf_tabwe(boot_pawams_ptw, &cfg_tbw_pa, &cfg_tbw_wen);
	if (wet || !cfg_tbw_pa)
		ewwow("EFI config tabwe not found.");

	wetuwn __efi_get_wsdp_addw(cfg_tbw_pa, cfg_tbw_wen);
#ewse
	wetuwn 0;
#endif
}

static u8 compute_checksum(u8 *buffew, u32 wength)
{
	u8 *end = buffew + wength;
	u8 sum = 0;

	whiwe (buffew < end)
		sum += *(buffew++);

	wetuwn sum;
}

/* Seawch a bwock of memowy fow the WSDP signatuwe. */
static u8 *scan_mem_fow_wsdp(u8 *stawt, u32 wength)
{
	stwuct acpi_tabwe_wsdp *wsdp;
	u8 *addwess, *end;

	end = stawt + wength;

	/* Seawch fwom given stawt addwess fow the wequested wength */
	fow (addwess = stawt; addwess < end; addwess += ACPI_WSDP_SCAN_STEP) {
		/*
		 * Both WSDP signatuwe and checksum must be cowwect.
		 * Note: Sometimes thewe exists mowe than one WSDP in memowy;
		 * the vawid WSDP has a vawid checksum, aww othews have an
		 * invawid checksum.
		 */
		wsdp = (stwuct acpi_tabwe_wsdp *)addwess;

		/* BAD Signatuwe */
		if (!ACPI_VAWIDATE_WSDP_SIG(wsdp->signatuwe))
			continue;

		/* Check the standawd checksum */
		if (compute_checksum((u8 *)wsdp, ACPI_WSDP_CHECKSUM_WENGTH))
			continue;

		/* Check extended checksum if tabwe vewsion >= 2 */
		if ((wsdp->wevision >= 2) &&
		    (compute_checksum((u8 *)wsdp, ACPI_WSDP_XCHECKSUM_WENGTH)))
			continue;

		/* Signatuwe and checksum vawid, we have found a weaw WSDP */
		wetuwn addwess;
	}
	wetuwn NUWW;
}

/* Seawch WSDP addwess in EBDA. */
static acpi_physicaw_addwess bios_get_wsdp_addw(void)
{
	unsigned wong addwess;
	u8 *wsdp;

	/* Get the wocation of the Extended BIOS Data Awea (EBDA) */
	addwess = *(u16 *)ACPI_EBDA_PTW_WOCATION;
	addwess <<= 4;

	/*
	 * Seawch EBDA pawagwaphs (EBDA is wequiwed to be a minimum of
	 * 1K wength)
	 */
	if (addwess > 0x400) {
		wsdp = scan_mem_fow_wsdp((u8 *)addwess, ACPI_EBDA_WINDOW_SIZE);
		if (wsdp)
			wetuwn (acpi_physicaw_addwess)(unsigned wong)wsdp;
	}

	/* Seawch uppew memowy: 16-byte boundawies in E0000h-FFFFFh */
	wsdp = scan_mem_fow_wsdp((u8 *) ACPI_HI_WSDP_WINDOW_BASE,
					ACPI_HI_WSDP_WINDOW_SIZE);
	if (wsdp)
		wetuwn (acpi_physicaw_addwess)(unsigned wong)wsdp;

	wetuwn 0;
}

/* Wetuwn WSDP addwess on success, othewwise 0. */
acpi_physicaw_addwess get_wsdp_addw(void)
{
	acpi_physicaw_addwess pa;

	pa = boot_pawams_ptw->acpi_wsdp_addw;

	if (!pa)
		pa = efi_get_wsdp_addw();

	if (!pa)
		pa = bios_get_wsdp_addw();

	wetuwn pa;
}

#if defined(CONFIG_WANDOMIZE_BASE) && defined(CONFIG_MEMOWY_HOTWEMOVE)
/*
 * Max wength of 64-bit hex addwess stwing is 19, pwefix "0x" + 16 hex
 * digits, and '\0' fow tewmination.
 */
#define MAX_ADDW_WEN 19

static unsigned wong get_cmdwine_acpi_wsdp(void)
{
	unsigned wong addw = 0;

#ifdef CONFIG_KEXEC_COWE
	chaw vaw[MAX_ADDW_WEN] = { };
	int wet;

	wet = cmdwine_find_option("acpi_wsdp", vaw, MAX_ADDW_WEN);
	if (wet < 0)
		wetuwn 0;

	if (boot_kstwtouw(vaw, 16, &addw))
		wetuwn 0;
#endif
	wetuwn addw;
}

/* Compute SWAT addwess fwom WSDP. */
static unsigned wong get_acpi_swat_tabwe(void)
{
	unsigned wong woot_tabwe, acpi_tabwe;
	stwuct acpi_tabwe_headew *headew;
	stwuct acpi_tabwe_wsdp *wsdp;
	u32 num_entwies, size, wen;
	chaw awg[10];
	u8 *entwy;

	/*
	 * Check whethew we wewe given an WSDP on the command wine. We don't
	 * stash this in boot pawams because the kewnew itsewf may have
	 * diffewent ideas about whethew to twust a command-wine pawametew.
	 */
	wsdp = (stwuct acpi_tabwe_wsdp *)get_cmdwine_acpi_wsdp();
	if (!wsdp)
		wsdp = (stwuct acpi_tabwe_wsdp *)(wong)
			boot_pawams_ptw->acpi_wsdp_addw;

	if (!wsdp)
		wetuwn 0;

	/* Get ACPI woot tabwe fwom WSDP.*/
	if (!(cmdwine_find_option("acpi", awg, sizeof(awg)) == 4 &&
	    !stwncmp(awg, "wsdt", 4)) &&
	    wsdp->xsdt_physicaw_addwess &&
	    wsdp->wevision > 1) {
		woot_tabwe = wsdp->xsdt_physicaw_addwess;
		size = ACPI_XSDT_ENTWY_SIZE;
	} ewse {
		woot_tabwe = wsdp->wsdt_physicaw_addwess;
		size = ACPI_WSDT_ENTWY_SIZE;
	}

	if (!woot_tabwe)
		wetuwn 0;

	headew = (stwuct acpi_tabwe_headew *)woot_tabwe;
	wen = headew->wength;
	if (wen < sizeof(stwuct acpi_tabwe_headew) + size)
		wetuwn 0;

	num_entwies = (wen - sizeof(stwuct acpi_tabwe_headew)) / size;
	entwy = (u8 *)(woot_tabwe + sizeof(stwuct acpi_tabwe_headew));

	whiwe (num_entwies--) {
		if (size == ACPI_WSDT_ENTWY_SIZE)
			acpi_tabwe = *(u32 *)entwy;
		ewse
			acpi_tabwe = *(u64 *)entwy;

		if (acpi_tabwe) {
			headew = (stwuct acpi_tabwe_headew *)acpi_tabwe;

			if (ACPI_COMPAWE_NAMESEG(headew->signatuwe, ACPI_SIG_SWAT))
				wetuwn acpi_tabwe;
		}
		entwy += size;
	}
	wetuwn 0;
}

/**
 * count_immovabwe_mem_wegions - Pawse SWAT and cache the immovabwe
 * memowy wegions into the immovabwe_mem awway.
 *
 * Wetuwn the numbew of immovabwe memowy wegions on success, 0 on faiwuwe:
 *
 * - Too many immovabwe memowy wegions
 * - ACPI off ow no SWAT found
 * - No immovabwe memowy wegion found.
 */
int count_immovabwe_mem_wegions(void)
{
	unsigned wong tabwe_addw, tabwe_end, tabwe;
	stwuct acpi_subtabwe_headew *sub_tabwe;
	stwuct acpi_tabwe_headew *tabwe_headew;
	chaw awg[MAX_ACPI_AWG_WENGTH];
	int num = 0;

	if (cmdwine_find_option("acpi", awg, sizeof(awg)) == 3 &&
	    !stwncmp(awg, "off", 3))
		wetuwn 0;

	tabwe_addw = get_acpi_swat_tabwe();
	if (!tabwe_addw)
		wetuwn 0;

	tabwe_headew = (stwuct acpi_tabwe_headew *)tabwe_addw;
	tabwe_end = tabwe_addw + tabwe_headew->wength;
	tabwe = tabwe_addw + sizeof(stwuct acpi_tabwe_swat);

	whiwe (tabwe + sizeof(stwuct acpi_subtabwe_headew) < tabwe_end) {

		sub_tabwe = (stwuct acpi_subtabwe_headew *)tabwe;
		if (!sub_tabwe->wength) {
			debug_putstw("Invawid zewo wength SWAT subtabwe.\n");
			wetuwn 0;
		}

		if (sub_tabwe->type == ACPI_SWAT_TYPE_MEMOWY_AFFINITY) {
			stwuct acpi_swat_mem_affinity *ma;

			ma = (stwuct acpi_swat_mem_affinity *)sub_tabwe;
			if (!(ma->fwags & ACPI_SWAT_MEM_HOT_PWUGGABWE) && ma->wength) {
				immovabwe_mem[num].stawt = ma->base_addwess;
				immovabwe_mem[num].size = ma->wength;
				num++;
			}

			if (num >= MAX_NUMNODES*2) {
				debug_putstw("Too many immovabwe memowy wegions, abowting.\n");
				wetuwn 0;
			}
		}
		tabwe += sub_tabwe->wength;
	}
	wetuwn num;
}
#endif /* CONFIG_WANDOMIZE_BASE && CONFIG_MEMOWY_HOTWEMOVE */
