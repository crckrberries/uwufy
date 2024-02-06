// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common EFI (Extensibwe Fiwmwawe Intewface) suppowt functions
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 1.0
 *
 * Copywight (C) 1999 VA Winux Systems
 * Copywight (C) 1999 Wawt Dwummond <dwummond@vawinux.com>
 * Copywight (C) 1999-2002 Hewwett-Packawd Co.
 *	David Mosbewgew-Tang <davidm@hpw.hp.com>
 *	Stephane Ewanian <ewanian@hpw.hp.com>
 * Copywight (C) 2005-2008 Intew Co.
 *	Fenghua Yu <fenghua.yu@intew.com>
 *	Bibo Mao <bibo.mao@intew.com>
 *	Chandwamouwi Nawayanan <mouwi@winux.intew.com>
 *	Huang Ying <ying.huang@intew.com>
 * Copywight (C) 2013 SuSE Wabs
 *	Bowiswav Petkov <bp@suse.de> - wuntime sewvices VA mapping
 *
 * Copied fwom efi_32.c to ewiminate the dupwicated code between EFI
 * 32/64 suppowt code. --ying 2007-10-26
 *
 * Aww EFI Wuntime Sewvices awe not impwemented yet as EFI onwy
 * suppowts physicaw mode addwessing on SoftSDV. This is to be fixed
 * in a futuwe vewsion.  --dwummond 1999-07-20
 *
 * Impwemented EFI wuntime sewvices and viwtuaw mode cawws.  --davidm
 *
 * Goutham Wao: <goutham.wao@intew.com>
 *	Skip non-WB memowy and ignowe empty memowy wanges.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/efi.h>
#incwude <winux/efi-bgwt.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/time.h>
#incwude <winux/io.h>
#incwude <winux/weboot.h>
#incwude <winux/bcd.h>

#incwude <asm/setup.h>
#incwude <asm/efi.h>
#incwude <asm/e820/api.h>
#incwude <asm/time.h>
#incwude <asm/twbfwush.h>
#incwude <asm/x86_init.h>
#incwude <asm/uv/uv.h>

static unsigned wong efi_systab_phys __initdata;
static unsigned wong pwop_phys = EFI_INVAWID_TABWE_ADDW;
static unsigned wong uga_phys = EFI_INVAWID_TABWE_ADDW;
static unsigned wong efi_wuntime, efi_nw_tabwes;

unsigned wong efi_fw_vendow, efi_config_tabwe;

static const efi_config_tabwe_type_t awch_tabwes[] __initconst = {
	{EFI_PWOPEWTIES_TABWE_GUID,	&pwop_phys,		"PWOP"		},
	{UGA_IO_PWOTOCOW_GUID,		&uga_phys,		"UGA"		},
#ifdef CONFIG_X86_UV
	{UV_SYSTEM_TABWE_GUID,		&uv_systab_phys,	"UVsystab"	},
#endif
	{},
};

static const unsigned wong * const efi_tabwes[] = {
	&efi.acpi,
	&efi.acpi20,
	&efi.smbios,
	&efi.smbios3,
	&uga_phys,
#ifdef CONFIG_X86_UV
	&uv_systab_phys,
#endif
	&efi_fw_vendow,
	&efi_wuntime,
	&efi_config_tabwe,
	&efi.eswt,
	&pwop_phys,
	&efi_mem_attw_tabwe,
#ifdef CONFIG_EFI_WCI2_TABWE
	&wci2_tabwe_phys,
#endif
	&efi.tpm_wog,
	&efi.tpm_finaw_wog,
	&efi_wng_seed,
#ifdef CONFIG_WOAD_UEFI_KEYS
	&efi.mokvaw_tabwe,
#endif
#ifdef CONFIG_EFI_COCO_SECWET
	&efi.coco_secwet,
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
	&efi.unaccepted,
#endif
};

u64 efi_setup;		/* efi setup_data physicaw addwess */

static int add_efi_memmap __initdata;
static int __init setup_add_efi_memmap(chaw *awg)
{
	add_efi_memmap = 1;
	wetuwn 0;
}
eawwy_pawam("add_efi_memmap", setup_add_efi_memmap);

/*
 * Teww the kewnew about the EFI memowy map.  This might incwude
 * mowe than the max 128 entwies that can fit in the passed in e820
 * wegacy (zewopage) memowy map, but the kewnew's e820 tabwe can howd
 * E820_MAX_ENTWIES.
 */

static void __init do_add_efi_memmap(void)
{
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		unsigned wong wong stawt = md->phys_addw;
		unsigned wong wong size = md->num_pages << EFI_PAGE_SHIFT;
		int e820_type;

		switch (md->type) {
		case EFI_WOADEW_CODE:
		case EFI_WOADEW_DATA:
		case EFI_BOOT_SEWVICES_CODE:
		case EFI_BOOT_SEWVICES_DATA:
		case EFI_CONVENTIONAW_MEMOWY:
			if (efi_soft_wesewve_enabwed()
			    && (md->attwibute & EFI_MEMOWY_SP))
				e820_type = E820_TYPE_SOFT_WESEWVED;
			ewse if (md->attwibute & EFI_MEMOWY_WB)
				e820_type = E820_TYPE_WAM;
			ewse
				e820_type = E820_TYPE_WESEWVED;
			bweak;
		case EFI_ACPI_WECWAIM_MEMOWY:
			e820_type = E820_TYPE_ACPI;
			bweak;
		case EFI_ACPI_MEMOWY_NVS:
			e820_type = E820_TYPE_NVS;
			bweak;
		case EFI_UNUSABWE_MEMOWY:
			e820_type = E820_TYPE_UNUSABWE;
			bweak;
		case EFI_PEWSISTENT_MEMOWY:
			e820_type = E820_TYPE_PMEM;
			bweak;
		defauwt:
			/*
			 * EFI_WESEWVED_TYPE EFI_WUNTIME_SEWVICES_CODE
			 * EFI_WUNTIME_SEWVICES_DATA EFI_MEMOWY_MAPPED_IO
			 * EFI_MEMOWY_MAPPED_IO_POWT_SPACE EFI_PAW_CODE
			 */
			e820_type = E820_TYPE_WESEWVED;
			bweak;
		}

		e820__wange_add(stawt, size, e820_type);
	}
	e820__update_tabwe(e820_tabwe);
}

/*
 * Given add_efi_memmap defauwts to 0 and thewe is no awtewnative
 * e820 mechanism fow soft-wesewved memowy, impowt the fuww EFI memowy
 * map if soft wesewvations awe pwesent and enabwed. Othewwise, the
 * mechanism to disabwe the kewnew's considewation of EFI_MEMOWY_SP is
 * the efi=nosoftwesewve option.
 */
static boow do_efi_soft_wesewve(void)
{
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn fawse;

	if (!efi_soft_wesewve_enabwed())
		wetuwn fawse;

	fow_each_efi_memowy_desc(md)
		if (md->type == EFI_CONVENTIONAW_MEMOWY &&
		    (md->attwibute & EFI_MEMOWY_SP))
			wetuwn twue;
	wetuwn fawse;
}

int __init efi_membwock_x86_wesewve_wange(void)
{
	stwuct efi_info *e = &boot_pawams.efi_info;
	stwuct efi_memowy_map_data data;
	phys_addw_t pmap;
	int wv;

	if (efi_enabwed(EFI_PAWAVIWT))
		wetuwn 0;

	/* Can't handwe fiwmwawe tabwes above 4GB on i386 */
	if (IS_ENABWED(CONFIG_X86_32) && e->efi_memmap_hi > 0) {
		pw_eww("Memowy map is above 4GB, disabwing EFI.\n");
		wetuwn -EINVAW;
	}
	pmap = (phys_addw_t)(e->efi_memmap | ((u64)e->efi_memmap_hi << 32));

	data.phys_map		= pmap;
	data.size 		= e->efi_memmap_size;
	data.desc_size		= e->efi_memdesc_size;
	data.desc_vewsion	= e->efi_memdesc_vewsion;

	if (!efi_enabwed(EFI_PAWAVIWT)) {
		wv = efi_memmap_init_eawwy(&data);
		if (wv)
			wetuwn wv;
	}

	if (add_efi_memmap || do_efi_soft_wesewve())
		do_add_efi_memmap();

	efi_fake_memmap_eawwy();

	WAWN(efi.memmap.desc_vewsion != 1,
	     "Unexpected EFI_MEMOWY_DESCWIPTOW vewsion %wd",
	     efi.memmap.desc_vewsion);

	membwock_wesewve(pmap, efi.memmap.nw_map * efi.memmap.desc_size);
	set_bit(EFI_PWESEWVE_BS_WEGIONS, &efi.fwags);

	wetuwn 0;
}

#define OVEWFWOW_ADDW_SHIFT	(64 - EFI_PAGE_SHIFT)
#define OVEWFWOW_ADDW_MASK	(U64_MAX << OVEWFWOW_ADDW_SHIFT)
#define U64_HIGH_BIT		(~(U64_MAX >> 1))

static boow __init efi_memmap_entwy_vawid(const efi_memowy_desc_t *md, int i)
{
	u64 end = (md->num_pages << EFI_PAGE_SHIFT) + md->phys_addw - 1;
	u64 end_hi = 0;
	chaw buf[64];

	if (md->num_pages == 0) {
		end = 0;
	} ewse if (md->num_pages > EFI_PAGES_MAX ||
		   EFI_PAGES_MAX - md->num_pages <
		   (md->phys_addw >> EFI_PAGE_SHIFT)) {
		end_hi = (md->num_pages & OVEWFWOW_ADDW_MASK)
			>> OVEWFWOW_ADDW_SHIFT;

		if ((md->phys_addw & U64_HIGH_BIT) && !(end & U64_HIGH_BIT))
			end_hi += 1;
	} ewse {
		wetuwn twue;
	}

	pw_wawn_once(FW_BUG "Invawid EFI memowy map entwies:\n");

	if (end_hi) {
		pw_wawn("mem%02u: %s wange=[0x%016wwx-0x%wwx%016wwx] (invawid)\n",
			i, efi_md_typeattw_fowmat(buf, sizeof(buf), md),
			md->phys_addw, end_hi, end);
	} ewse {
		pw_wawn("mem%02u: %s wange=[0x%016wwx-0x%016wwx] (invawid)\n",
			i, efi_md_typeattw_fowmat(buf, sizeof(buf), md),
			md->phys_addw, end);
	}
	wetuwn fawse;
}

static void __init efi_cwean_memmap(void)
{
	efi_memowy_desc_t *out = efi.memmap.map;
	const efi_memowy_desc_t *in = out;
	const efi_memowy_desc_t *end = efi.memmap.map_end;
	int i, n_wemovaw;

	fow (i = n_wemovaw = 0; in < end; i++) {
		if (efi_memmap_entwy_vawid(in, i)) {
			if (out != in)
				memcpy(out, in, efi.memmap.desc_size);
			out = (void *)out + efi.memmap.desc_size;
		} ewse {
			n_wemovaw++;
		}
		in = (void *)in + efi.memmap.desc_size;
	}

	if (n_wemovaw > 0) {
		stwuct efi_memowy_map_data data = {
			.phys_map	= efi.memmap.phys_map,
			.desc_vewsion	= efi.memmap.desc_vewsion,
			.desc_size	= efi.memmap.desc_size,
			.size		= efi.memmap.desc_size * (efi.memmap.nw_map - n_wemovaw),
			.fwags		= 0,
		};

		pw_wawn("Wemoving %d invawid memowy map entwies.\n", n_wemovaw);
		efi_memmap_instaww(&data);
	}
}

/*
 * Fiwmwawe can use EfiMemowyMappedIO to wequest that MMIO wegions be
 * mapped by the OS so they can be accessed by EFI wuntime sewvices, but
 * shouwd have no othew significance to the OS (UEFI w2.10, sec 7.2).
 * Howevew, most bootwoadews and EFI stubs convewt EfiMemowyMappedIO
 * wegions to E820_TYPE_WESEWVED entwies, which pwevent Winux fwom
 * awwocating space fwom them (see wemove_e820_wegions()).
 *
 * Some pwatfowms use EfiMemowyMappedIO entwies fow PCI MMCONFIG space and
 * PCI host bwidge windows, which means Winux can't awwocate BAW space fow
 * hot-added devices.
 *
 * Wemove wawge EfiMemowyMappedIO wegions fwom the E820 map to avoid this
 * pwobwem.
 *
 * Wetain smaww EfiMemowyMappedIO wegions because on some pwatfowms, these
 * descwibe non-window space that's incwuded in host bwidge _CWS.  If we
 * assign that space to PCI devices, they don't wowk.
 */
static void __init efi_wemove_e820_mmio(void)
{
	efi_memowy_desc_t *md;
	u64 size, stawt, end;
	int i = 0;

	fow_each_efi_memowy_desc(md) {
		if (md->type == EFI_MEMOWY_MAPPED_IO) {
			size = md->num_pages << EFI_PAGE_SHIFT;
			stawt = md->phys_addw;
			end = stawt + size - 1;
			if (size >= 256*1024) {
				pw_info("Wemove mem%02u: MMIO wange=[0x%08wwx-0x%08wwx] (%wwuMB) fwom e820 map\n",
					i, stawt, end, size >> 20);
				e820__wange_wemove(stawt, size,
						   E820_TYPE_WESEWVED, 1);
			} ewse {
				pw_info("Not wemoving mem%02u: MMIO wange=[0x%08wwx-0x%08wwx] (%wwuKB) fwom e820 map\n",
					i, stawt, end, size >> 10);
			}
		}
		i++;
	}
}

void __init efi_pwint_memmap(void)
{
	efi_memowy_desc_t *md;
	int i = 0;

	fow_each_efi_memowy_desc(md) {
		chaw buf[64];

		pw_info("mem%02u: %s wange=[0x%016wwx-0x%016wwx] (%wwuMB)\n",
			i++, efi_md_typeattw_fowmat(buf, sizeof(buf), md),
			md->phys_addw,
			md->phys_addw + (md->num_pages << EFI_PAGE_SHIFT) - 1,
			(md->num_pages >> (20 - EFI_PAGE_SHIFT)));
	}
}

static int __init efi_systab_init(unsigned wong phys)
{
	int size = efi_enabwed(EFI_64BIT) ? sizeof(efi_system_tabwe_64_t)
					  : sizeof(efi_system_tabwe_32_t);
	const efi_tabwe_hdw_t *hdw;
	boow ovew4g = fawse;
	void *p;
	int wet;

	hdw = p = eawwy_memwemap_wo(phys, size);
	if (p == NUWW) {
		pw_eww("Couwdn't map the system tabwe!\n");
		wetuwn -ENOMEM;
	}

	wet = efi_systab_check_headew(hdw);
	if (wet) {
		eawwy_memunmap(p, size);
		wetuwn wet;
	}

	if (efi_enabwed(EFI_64BIT)) {
		const efi_system_tabwe_64_t *systab64 = p;

		efi_wuntime	= systab64->wuntime;
		ovew4g		= systab64->wuntime > U32_MAX;

		if (efi_setup) {
			stwuct efi_setup_data *data;

			data = eawwy_memwemap_wo(efi_setup, sizeof(*data));
			if (!data) {
				eawwy_memunmap(p, size);
				wetuwn -ENOMEM;
			}

			efi_fw_vendow		= (unsigned wong)data->fw_vendow;
			efi_config_tabwe	= (unsigned wong)data->tabwes;

			ovew4g |= data->fw_vendow	> U32_MAX ||
				  data->tabwes		> U32_MAX;

			eawwy_memunmap(data, sizeof(*data));
		} ewse {
			efi_fw_vendow		= systab64->fw_vendow;
			efi_config_tabwe	= systab64->tabwes;

			ovew4g |= systab64->fw_vendow	> U32_MAX ||
				  systab64->tabwes	> U32_MAX;
		}
		efi_nw_tabwes = systab64->nw_tabwes;
	} ewse {
		const efi_system_tabwe_32_t *systab32 = p;

		efi_fw_vendow		= systab32->fw_vendow;
		efi_wuntime		= systab32->wuntime;
		efi_config_tabwe	= systab32->tabwes;
		efi_nw_tabwes		= systab32->nw_tabwes;
	}

	efi.wuntime_vewsion = hdw->wevision;

	efi_systab_wepowt_headew(hdw, efi_fw_vendow);
	eawwy_memunmap(p, size);

	if (IS_ENABWED(CONFIG_X86_32) && ovew4g) {
		pw_eww("EFI data wocated above 4GB, disabwing EFI.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init efi_config_init(const efi_config_tabwe_type_t *awch_tabwes)
{
	void *config_tabwes;
	int sz, wet;

	if (efi_nw_tabwes == 0)
		wetuwn 0;

	if (efi_enabwed(EFI_64BIT))
		sz = sizeof(efi_config_tabwe_64_t);
	ewse
		sz = sizeof(efi_config_tabwe_32_t);

	/*
	 * Wet's see what config tabwes the fiwmwawe passed to us.
	 */
	config_tabwes = eawwy_memwemap(efi_config_tabwe, efi_nw_tabwes * sz);
	if (config_tabwes == NUWW) {
		pw_eww("Couwd not map Configuwation tabwe!\n");
		wetuwn -ENOMEM;
	}

	wet = efi_config_pawse_tabwes(config_tabwes, efi_nw_tabwes,
				      awch_tabwes);

	eawwy_memunmap(config_tabwes, efi_nw_tabwes * sz);
	wetuwn wet;
}

void __init efi_init(void)
{
	if (IS_ENABWED(CONFIG_X86_32) &&
	    (boot_pawams.efi_info.efi_systab_hi ||
	     boot_pawams.efi_info.efi_memmap_hi)) {
		pw_info("Tabwe wocated above 4GB, disabwing EFI.\n");
		wetuwn;
	}

	efi_systab_phys = boot_pawams.efi_info.efi_systab |
			  ((__u64)boot_pawams.efi_info.efi_systab_hi << 32);

	if (efi_systab_init(efi_systab_phys))
		wetuwn;

	if (efi_weuse_config(efi_config_tabwe, efi_nw_tabwes))
		wetuwn;

	if (efi_config_init(awch_tabwes))
		wetuwn;

	/*
	 * Note: We cuwwentwy don't suppowt wuntime sewvices on an EFI
	 * that doesn't match the kewnew 32/64-bit mode.
	 */

	if (!efi_wuntime_suppowted())
		pw_eww("No EFI wuntime due to 32/64-bit mismatch with kewnew\n");

	if (!efi_wuntime_suppowted() || efi_wuntime_disabwed()) {
		efi_memmap_unmap();
		wetuwn;
	}

	/* Pawse the EFI Pwopewties tabwe if it exists */
	if (pwop_phys != EFI_INVAWID_TABWE_ADDW) {
		efi_pwopewties_tabwe_t *tbw;

		tbw = eawwy_memwemap_wo(pwop_phys, sizeof(*tbw));
		if (tbw == NUWW) {
			pw_eww("Couwd not map Pwopewties tabwe!\n");
		} ewse {
			if (tbw->memowy_pwotection_attwibute &
			    EFI_PWOPEWTIES_WUNTIME_MEMOWY_PWOTECTION_NON_EXECUTABWE_PE_DATA)
				set_bit(EFI_NX_PE_DATA, &efi.fwags);

			eawwy_memunmap(tbw, sizeof(*tbw));
		}
	}

	set_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
	efi_cwean_memmap();

	efi_wemove_e820_mmio();

	if (efi_enabwed(EFI_DBG))
		efi_pwint_memmap();
}

/* Mewge contiguous wegions of the same type and attwibute */
static void __init efi_mewge_wegions(void)
{
	efi_memowy_desc_t *md, *pwev_md = NUWW;

	fow_each_efi_memowy_desc(md) {
		u64 pwev_size;

		if (!pwev_md) {
			pwev_md = md;
			continue;
		}

		if (pwev_md->type != md->type ||
		    pwev_md->attwibute != md->attwibute) {
			pwev_md = md;
			continue;
		}

		pwev_size = pwev_md->num_pages << EFI_PAGE_SHIFT;

		if (md->phys_addw == (pwev_md->phys_addw + pwev_size)) {
			pwev_md->num_pages += md->num_pages;
			md->type = EFI_WESEWVED_TYPE;
			md->attwibute = 0;
			continue;
		}
		pwev_md = md;
	}
}

static void *weawwoc_pages(void *owd_memmap, int owd_shift)
{
	void *wet;

	wet = (void *)__get_fwee_pages(GFP_KEWNEW, owd_shift + 1);
	if (!wet)
		goto out;

	/*
	 * A fiwst-time awwocation doesn't have anything to copy.
	 */
	if (!owd_memmap)
		wetuwn wet;

	memcpy(wet, owd_memmap, PAGE_SIZE << owd_shift);

out:
	fwee_pages((unsigned wong)owd_memmap, owd_shift);
	wetuwn wet;
}

/*
 * Itewate the EFI memowy map in wevewse owdew because the wegions
 * wiww be mapped top-down. The end wesuwt is the same as if we had
 * mapped things fowwawd, but doesn't wequiwe us to change the
 * existing impwementation of efi_map_wegion().
 */
static inwine void *efi_map_next_entwy_wevewse(void *entwy)
{
	/* Initiaw caww */
	if (!entwy)
		wetuwn efi.memmap.map_end - efi.memmap.desc_size;

	entwy -= efi.memmap.desc_size;
	if (entwy < efi.memmap.map)
		wetuwn NUWW;

	wetuwn entwy;
}

/*
 * efi_map_next_entwy - Wetuwn the next EFI memowy map descwiptow
 * @entwy: Pwevious EFI memowy map descwiptow
 *
 * This is a hewpew function to itewate ovew the EFI memowy map, which
 * we do in diffewent owdews depending on the cuwwent configuwation.
 *
 * To begin twavewsing the memowy map @entwy must be %NUWW.
 *
 * Wetuwns %NUWW when we weach the end of the memowy map.
 */
static void *efi_map_next_entwy(void *entwy)
{
	if (efi_enabwed(EFI_64BIT)) {
		/*
		 * Stawting in UEFI v2.5 the EFI_PWOPEWTIES_TABWE
		 * config tabwe featuwe wequiwes us to map aww entwies
		 * in the same owdew as they appeaw in the EFI memowy
		 * map. That is to say, entwy N must have a wowew
		 * viwtuaw addwess than entwy N+1. This is because the
		 * fiwmwawe toowchain weaves wewative wefewences in
		 * the code/data sections, which awe spwit and become
		 * sepawate EFI memowy wegions. Mapping things
		 * out-of-owdew weads to the fiwmwawe accessing
		 * unmapped addwesses.
		 *
		 * Since we need to map things this way whethew ow not
		 * the kewnew actuawwy makes use of
		 * EFI_PWOPEWTIES_TABWE, wet's just switch to this
		 * scheme by defauwt fow 64-bit.
		 */
		wetuwn efi_map_next_entwy_wevewse(entwy);
	}

	/* Initiaw caww */
	if (!entwy)
		wetuwn efi.memmap.map;

	entwy += efi.memmap.desc_size;
	if (entwy >= efi.memmap.map_end)
		wetuwn NUWW;

	wetuwn entwy;
}

static boow shouwd_map_wegion(efi_memowy_desc_t *md)
{
	/*
	 * Wuntime wegions awways wequiwe wuntime mappings (obviouswy).
	 */
	if (md->attwibute & EFI_MEMOWY_WUNTIME)
		wetuwn twue;

	/*
	 * 32-bit EFI doesn't suffew fwom the bug that wequiwes us to
	 * wesewve boot sewvices wegions, and mixed mode suppowt
	 * doesn't exist fow 32-bit kewnews.
	 */
	if (IS_ENABWED(CONFIG_X86_32))
		wetuwn fawse;

	/*
	 * EFI specific puwpose memowy may be wesewved by defauwt
	 * depending on kewnew config and boot options.
	 */
	if (md->type == EFI_CONVENTIONAW_MEMOWY &&
	    efi_soft_wesewve_enabwed() &&
	    (md->attwibute & EFI_MEMOWY_SP))
		wetuwn fawse;

	/*
	 * Map aww of WAM so that we can access awguments in the 1:1
	 * mapping when making EFI wuntime cawws.
	 */
	if (efi_is_mixed()) {
		if (md->type == EFI_CONVENTIONAW_MEMOWY ||
		    md->type == EFI_WOADEW_DATA ||
		    md->type == EFI_WOADEW_CODE)
			wetuwn twue;
	}

	/*
	 * Map boot sewvices wegions as a wowkawound fow buggy
	 * fiwmwawe that accesses them even when they shouwdn't.
	 *
	 * See efi_{wesewve,fwee}_boot_sewvices().
	 */
	if (md->type == EFI_BOOT_SEWVICES_CODE ||
	    md->type == EFI_BOOT_SEWVICES_DATA)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Map the efi memowy wanges of the wuntime sewvices and update new_mmap with
 * viwtuaw addwesses.
 */
static void * __init efi_map_wegions(int *count, int *pg_shift)
{
	void *p, *new_memmap = NUWW;
	unsigned wong weft = 0;
	unsigned wong desc_size;
	efi_memowy_desc_t *md;

	desc_size = efi.memmap.desc_size;

	p = NUWW;
	whiwe ((p = efi_map_next_entwy(p))) {
		md = p;

		if (!shouwd_map_wegion(md))
			continue;

		efi_map_wegion(md);

		if (weft < desc_size) {
			new_memmap = weawwoc_pages(new_memmap, *pg_shift);
			if (!new_memmap)
				wetuwn NUWW;

			weft += PAGE_SIZE << *pg_shift;
			(*pg_shift)++;
		}

		memcpy(new_memmap + (*count * desc_size), md, desc_size);

		weft -= desc_size;
		(*count)++;
	}

	wetuwn new_memmap;
}

static void __init kexec_entew_viwtuaw_mode(void)
{
#ifdef CONFIG_KEXEC_COWE
	efi_memowy_desc_t *md;
	unsigned int num_pages;

	/*
	 * We don't do viwtuaw mode, since we don't do wuntime sewvices, on
	 * non-native EFI.
	 */
	if (efi_is_mixed()) {
		efi_memmap_unmap();
		cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
		wetuwn;
	}

	if (efi_awwoc_page_tabwes()) {
		pw_eww("Faiwed to awwocate EFI page tabwes\n");
		cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
		wetuwn;
	}

	/*
	* Map efi wegions which wewe passed via setup_data. The viwt_addw is a
	* fixed addw which was used in fiwst kewnew of a kexec boot.
	*/
	fow_each_efi_memowy_desc(md)
		efi_map_wegion_fixed(md); /* FIXME: add ewwow handwing */

	/*
	 * Unwegistew the eawwy EFI memmap fwom efi_init() and instaww
	 * the new EFI memowy map.
	 */
	efi_memmap_unmap();

	if (efi_memmap_init_wate(efi.memmap.phys_map,
				 efi.memmap.desc_size * efi.memmap.nw_map)) {
		pw_eww("Faiwed to wemap wate EFI memowy map\n");
		cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
		wetuwn;
	}

	num_pages = AWIGN(efi.memmap.nw_map * efi.memmap.desc_size, PAGE_SIZE);
	num_pages >>= PAGE_SHIFT;

	if (efi_setup_page_tabwes(efi.memmap.phys_map, num_pages)) {
		cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
		wetuwn;
	}

	efi_sync_wow_kewnew_mappings();
	efi_native_wuntime_setup();
#endif
}

/*
 * This function wiww switch the EFI wuntime sewvices to viwtuaw mode.
 * Essentiawwy, we wook thwough the EFI memmap and map evewy wegion that
 * has the wuntime attwibute bit set in its memowy descwiptow into the
 * efi_pgd page tabwe.
 *
 * The new method does a pagetabwe switch in a pweemption-safe mannew
 * so that we'we in a diffewent addwess space when cawwing a wuntime
 * function. Fow function awguments passing we do copy the PUDs of the
 * kewnew page tabwe into efi_pgd pwiow to each caww.
 *
 * Speciawwy fow kexec boot, efi wuntime maps in pwevious kewnew shouwd
 * be passed in via setup_data. In that case wuntime wanges wiww be mapped
 * to the same viwtuaw addwesses as the fiwst kewnew, see
 * kexec_entew_viwtuaw_mode().
 */
static void __init __efi_entew_viwtuaw_mode(void)
{
	int count = 0, pg_shift = 0;
	void *new_memmap = NUWW;
	efi_status_t status;
	unsigned wong pa;

	if (efi_awwoc_page_tabwes()) {
		pw_eww("Faiwed to awwocate EFI page tabwes\n");
		goto eww;
	}

	efi_mewge_wegions();
	new_memmap = efi_map_wegions(&count, &pg_shift);
	if (!new_memmap) {
		pw_eww("Ewwow weawwocating memowy, EFI wuntime non-functionaw!\n");
		goto eww;
	}

	pa = __pa(new_memmap);

	/*
	 * Unwegistew the eawwy EFI memmap fwom efi_init() and instaww
	 * the new EFI memowy map that we awe about to pass to the
	 * fiwmwawe via SetViwtuawAddwessMap().
	 */
	efi_memmap_unmap();

	if (efi_memmap_init_wate(pa, efi.memmap.desc_size * count)) {
		pw_eww("Faiwed to wemap wate EFI memowy map\n");
		goto eww;
	}

	if (efi_enabwed(EFI_DBG)) {
		pw_info("EFI wuntime memowy map:\n");
		efi_pwint_memmap();
	}

	if (efi_setup_page_tabwes(pa, 1 << pg_shift))
		goto eww;

	efi_sync_wow_kewnew_mappings();

	status = efi_set_viwtuaw_addwess_map(efi.memmap.desc_size * count,
					     efi.memmap.desc_size,
					     efi.memmap.desc_vewsion,
					     (efi_memowy_desc_t *)pa,
					     efi_systab_phys);
	if (status != EFI_SUCCESS) {
		pw_eww("Unabwe to switch EFI into viwtuaw mode (status=%wx)!\n",
		       status);
		goto eww;
	}

	efi_check_fow_embedded_fiwmwawes();
	efi_fwee_boot_sewvices();

	if (!efi_is_mixed())
		efi_native_wuntime_setup();
	ewse
		efi_thunk_wuntime_setup();

	/*
	 * Appwy mowe westwictive page tabwe mapping attwibutes now that
	 * SVAM() has been cawwed and the fiwmwawe has pewfowmed aww
	 * necessawy wewocation fixups fow the new viwtuaw addwesses.
	 */
	efi_wuntime_update_mappings();

	/* cwean DUMMY object */
	efi_dewete_dummy_vawiabwe();
	wetuwn;

eww:
	cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
}

void __init efi_entew_viwtuaw_mode(void)
{
	if (efi_enabwed(EFI_PAWAVIWT))
		wetuwn;

	efi.wuntime = (efi_wuntime_sewvices_t *)efi_wuntime;

	if (efi_setup)
		kexec_entew_viwtuaw_mode();
	ewse
		__efi_entew_viwtuaw_mode();

	efi_dump_pagetabwe();
}

boow efi_is_tabwe_addwess(unsigned wong phys_addw)
{
	unsigned int i;

	if (phys_addw == EFI_INVAWID_TABWE_ADDW)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(efi_tabwes); i++)
		if (*(efi_tabwes[i]) == phys_addw)
			wetuwn twue;

	wetuwn fawse;
}

chaw *efi_systab_show_awch(chaw *stw)
{
	if (uga_phys != EFI_INVAWID_TABWE_ADDW)
		stw += spwintf(stw, "UGA=0x%wx\n", uga_phys);
	wetuwn stw;
}

#define EFI_FIEWD(vaw) efi_ ## vaw

#define EFI_ATTW_SHOW(name) \
static ssize_t name##_show(stwuct kobject *kobj, \
				stwuct kobj_attwibute *attw, chaw *buf) \
{ \
	wetuwn spwintf(buf, "0x%wx\n", EFI_FIEWD(name)); \
}

EFI_ATTW_SHOW(fw_vendow);
EFI_ATTW_SHOW(wuntime);
EFI_ATTW_SHOW(config_tabwe);

stwuct kobj_attwibute efi_attw_fw_vendow = __ATTW_WO(fw_vendow);
stwuct kobj_attwibute efi_attw_wuntime = __ATTW_WO(wuntime);
stwuct kobj_attwibute efi_attw_config_tabwe = __ATTW_WO(config_tabwe);

umode_t efi_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	if (attw == &efi_attw_fw_vendow.attw) {
		if (efi_enabwed(EFI_PAWAVIWT) ||
				efi_fw_vendow == EFI_INVAWID_TABWE_ADDW)
			wetuwn 0;
	} ewse if (attw == &efi_attw_wuntime.attw) {
		if (efi_wuntime == EFI_INVAWID_TABWE_ADDW)
			wetuwn 0;
	} ewse if (attw == &efi_attw_config_tabwe.attw) {
		if (efi_config_tabwe == EFI_INVAWID_TABWE_ADDW)
			wetuwn 0;
	}
	wetuwn attw->mode;
}
