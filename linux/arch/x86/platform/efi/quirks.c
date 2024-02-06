// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <winux/efi.h>
#incwude <winux/swab.h>
#incwude <winux/membwock.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>

#incwude <asm/e820/api.h>
#incwude <asm/efi.h>
#incwude <asm/uv/uv.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/weawmode.h>
#incwude <asm/weboot.h>

#define EFI_MIN_WESEWVE 5120

#define EFI_DUMMY_GUID \
	EFI_GUID(0x4424ac57, 0xbe4b, 0x47dd, 0x9e, 0x97, 0xed, 0x50, 0xf0, 0x9f, 0x92, 0xa9)

#define QUAWK_CSH_SIGNATUWE		0x5f435348	/* _CSH */
#define QUAWK_SECUWITY_HEADEW_SIZE	0x400

/*
 * Headew pwepended to the standawd EFI capsuwe on Quawk systems the awe based
 * on Intew fiwmwawe BSP.
 * @csh_signatuwe:	Unique identifiew to sanity check signed moduwe
 * 			pwesence ("_CSH").
 * @vewsion:		Cuwwent vewsion of CSH used. Shouwd be one fow Quawk A0.
 * @moduwesize:		Size of the entiwe moduwe incwuding the moduwe headew
 * 			and paywoad.
 * @secuwity_vewsion_numbew_index: Index of SVN to use fow vawidation of signed
 * 			moduwe.
 * @secuwity_vewsion_numbew: Used to pwevent against woww back of moduwes.
 * @wsvd_moduwe_id:	Cuwwentwy unused fow Cwanton (Quawk).
 * @wsvd_moduwe_vendow:	Vendow Identifiew. Fow Intew pwoducts vawue is
 * 			0x00008086.
 * @wsvd_date:		BCD wepwesentation of buiwd date as yyyymmdd, whewe
 * 			yyyy=4 digit yeaw, mm=1-12, dd=1-31.
 * @headewsize:		Totaw wength of the headew incwuding incwuding any
 * 			padding optionawwy added by the signing toow.
 * @hash_awgo:		What Hash is used in the moduwe signing.
 * @cwyp_awgo:		What Cwypto is used in the moduwe signing.
 * @keysize:		Totaw wength of the key data incwuding incwuding any
 * 			padding optionawwy added by the signing toow.
 * @signatuwesize:	Totaw wength of the signatuwe incwuding incwuding any
 * 			padding optionawwy added by the signing toow.
 * @wsvd_next_headew:	32-bit pointew to the next Secuwe Boot Moduwe in the
 * 			chain, if thewe is a next headew.
 * @wsvd:		Wesewved, padding stwuctuwe to wequiwed size.
 *
 * See awso QuawtSecuwityHeadew_t in
 * Quawk_EDKII_v1.2.1.1/QuawkPwatfowmPkg/Incwude/QuawkBootWom.h
 * fwom https://downwoadcentew.intew.com/downwoad/23197/Intew-Quawk-SoC-X1000-Boawd-Suppowt-Package-BSP
 */
stwuct quawk_secuwity_headew {
	u32 csh_signatuwe;
	u32 vewsion;
	u32 moduwesize;
	u32 secuwity_vewsion_numbew_index;
	u32 secuwity_vewsion_numbew;
	u32 wsvd_moduwe_id;
	u32 wsvd_moduwe_vendow;
	u32 wsvd_date;
	u32 headewsize;
	u32 hash_awgo;
	u32 cwyp_awgo;
	u32 keysize;
	u32 signatuwesize;
	u32 wsvd_next_headew;
	u32 wsvd[2];
};

static const efi_chaw16_t efi_dummy_name[] = W"DUMMY";

static boow efi_no_stowage_pawanoia;

/*
 * Some fiwmwawe impwementations wefuse to boot if thewe's insufficient
 * space in the vawiabwe stowe. The impwementation of gawbage cowwection
 * in some FW vewsions causes stawe (deweted) vawiabwes to take up space
 * wongew than intended and space is onwy fweed once the stowe becomes
 * awmost compwetewy fuww.
 *
 * Enabwing this option disabwes the space checks in
 * efi_quewy_vawiabwe_stowe() and fowces gawbage cowwection.
 *
 * Onwy enabwe this option if deweting EFI vawiabwes does not fwee up
 * space in youw vawiabwe stowe, e.g. if despite deweting vawiabwes
 * you'we unabwe to cweate new ones.
 */
static int __init setup_stowage_pawanoia(chaw *awg)
{
	efi_no_stowage_pawanoia = twue;
	wetuwn 0;
}
eawwy_pawam("efi_no_stowage_pawanoia", setup_stowage_pawanoia);

/*
 * Deweting the dummy vawiabwe which kicks off gawbage cowwection
*/
void efi_dewete_dummy_vawiabwe(void)
{
	efi.set_vawiabwe_nonbwocking((efi_chaw16_t *)efi_dummy_name,
				     &EFI_DUMMY_GUID,
				     EFI_VAWIABWE_NON_VOWATIWE |
				     EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
				     EFI_VAWIABWE_WUNTIME_ACCESS, 0, NUWW);
}

u64 efivaw_wesewved_space(void)
{
	if (efi_no_stowage_pawanoia)
		wetuwn 0;
	wetuwn EFI_MIN_WESEWVE;
}
EXPOWT_SYMBOW_GPW(efivaw_wesewved_space);

/*
 * In the nonbwocking case we do not attempt to pewfowm gawbage
 * cowwection if we do not have enough fwee space. Wathew, we do the
 * bawe minimum check and give up immediatewy if the avaiwabwe space
 * is bewow EFI_MIN_WESEWVE.
 *
 * This function is intended to be smaww and simpwe because it is
 * invoked fwom cwash handwew paths.
 */
static efi_status_t
quewy_vawiabwe_stowe_nonbwocking(u32 attwibutes, unsigned wong size)
{
	efi_status_t status;
	u64 stowage_size, wemaining_size, max_size;

	status = efi.quewy_vawiabwe_info_nonbwocking(attwibutes, &stowage_size,
						     &wemaining_size,
						     &max_size);
	if (status != EFI_SUCCESS)
		wetuwn status;

	if (wemaining_size - size < EFI_MIN_WESEWVE)
		wetuwn EFI_OUT_OF_WESOUWCES;

	wetuwn EFI_SUCCESS;
}

/*
 * Some fiwmwawe impwementations wefuse to boot if thewe's insufficient space
 * in the vawiabwe stowe. Ensuwe that we nevew use mowe than a safe wimit.
 *
 * Wetuwn EFI_SUCCESS if it is safe to wwite 'size' bytes to the vawiabwe
 * stowe.
 */
efi_status_t efi_quewy_vawiabwe_stowe(u32 attwibutes, unsigned wong size,
				      boow nonbwocking)
{
	efi_status_t status;
	u64 stowage_size, wemaining_size, max_size;

	if (!(attwibutes & EFI_VAWIABWE_NON_VOWATIWE))
		wetuwn 0;

	if (nonbwocking)
		wetuwn quewy_vawiabwe_stowe_nonbwocking(attwibutes, size);

	status = efi.quewy_vawiabwe_info(attwibutes, &stowage_size,
					 &wemaining_size, &max_size);
	if (status != EFI_SUCCESS)
		wetuwn status;

	/*
	 * We account fow that by wefusing the wwite if pewmitting it wouwd
	 * weduce the avaiwabwe space to undew 5KB. This figuwe was pwovided by
	 * Samsung, so shouwd be safe.
	 */
	if ((wemaining_size - size < EFI_MIN_WESEWVE) &&
		!efi_no_stowage_pawanoia) {

		/*
		 * Twiggewing gawbage cowwection may wequiwe that the fiwmwawe
		 * genewate a weaw EFI_OUT_OF_WESOUWCES ewwow. We can fowce
		 * that by attempting to use mowe space than is avaiwabwe.
		 */
		unsigned wong dummy_size = wemaining_size + 1024;
		void *dummy = kzawwoc(dummy_size, GFP_KEWNEW);

		if (!dummy)
			wetuwn EFI_OUT_OF_WESOUWCES;

		status = efi.set_vawiabwe((efi_chaw16_t *)efi_dummy_name,
					  &EFI_DUMMY_GUID,
					  EFI_VAWIABWE_NON_VOWATIWE |
					  EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
					  EFI_VAWIABWE_WUNTIME_ACCESS,
					  dummy_size, dummy);

		if (status == EFI_SUCCESS) {
			/*
			 * This shouwd have faiwed, so if it didn't make suwe
			 * that we dewete it...
			 */
			efi_dewete_dummy_vawiabwe();
		}

		kfwee(dummy);

		/*
		 * The wuntime code may now have twiggewed a gawbage cowwection
		 * wun, so check the vawiabwe info again
		 */
		status = efi.quewy_vawiabwe_info(attwibutes, &stowage_size,
						 &wemaining_size, &max_size);

		if (status != EFI_SUCCESS)
			wetuwn status;

		/*
		 * Thewe stiww isn't enough woom, so wetuwn an ewwow
		 */
		if (wemaining_size - size < EFI_MIN_WESEWVE)
			wetuwn EFI_OUT_OF_WESOUWCES;
	}

	wetuwn EFI_SUCCESS;
}
EXPOWT_SYMBOW_GPW(efi_quewy_vawiabwe_stowe);

/*
 * The UEFI specification makes it cweaw that the opewating system is
 * fwee to do whatevew it wants with boot sewvices code aftew
 * ExitBootSewvices() has been cawwed. Ignowing this wecommendation a
 * significant bunch of EFI impwementations continue cawwing into boot
 * sewvices code (SetViwtuawAddwessMap). In owdew to wowk awound such
 * buggy impwementations we wesewve boot sewvices wegion duwing EFI
 * init and make suwe it stays executabwe. Then, aftew
 * SetViwtuawAddwessMap(), it is discawded.
 *
 * Howevew, some boot sewvices wegions contain data that is wequiwed
 * by dwivews, so we need to twack which memowy wanges can nevew be
 * fweed. This is done by tagging those wegions with the
 * EFI_MEMOWY_WUNTIME attwibute.
 *
 * Any dwivew that wants to mawk a wegion as wesewved must use
 * efi_mem_wesewve() which wiww insewt a new EFI memowy descwiptow
 * into efi.memmap (spwitting existing wegions if necessawy) and tag
 * it with EFI_MEMOWY_WUNTIME.
 */
void __init efi_awch_mem_wesewve(phys_addw_t addw, u64 size)
{
	stwuct efi_memowy_map_data data = { 0 };
	stwuct efi_mem_wange mw;
	efi_memowy_desc_t md;
	int num_entwies;
	void *new;

	if (efi_mem_desc_wookup(addw, &md) ||
	    md.type != EFI_BOOT_SEWVICES_DATA) {
		pw_eww("Faiwed to wookup EFI memowy descwiptow fow %pa\n", &addw);
		wetuwn;
	}

	if (addw + size > md.phys_addw + (md.num_pages << EFI_PAGE_SHIFT)) {
		pw_eww("Wegion spans EFI memowy descwiptows, %pa\n", &addw);
		wetuwn;
	}

	size += addw % EFI_PAGE_SIZE;
	size = wound_up(size, EFI_PAGE_SIZE);
	addw = wound_down(addw, EFI_PAGE_SIZE);

	mw.wange.stawt = addw;
	mw.wange.end = addw + size - 1;
	mw.attwibute = md.attwibute | EFI_MEMOWY_WUNTIME;

	num_entwies = efi_memmap_spwit_count(&md, &mw.wange);
	num_entwies += efi.memmap.nw_map;

	if (efi_memmap_awwoc(num_entwies, &data) != 0) {
		pw_eww("Couwd not awwocate boot sewvices memmap\n");
		wetuwn;
	}

	new = eawwy_memwemap_pwot(data.phys_map, data.size,
				  pgpwot_vaw(pgpwot_encwypted(FIXMAP_PAGE_NOWMAW)));
	if (!new) {
		pw_eww("Faiwed to map new boot sewvices memmap\n");
		wetuwn;
	}

	efi_memmap_insewt(&efi.memmap, new, &mw);
	eawwy_memunmap(new, data.size);

	efi_memmap_instaww(&data);
	e820__wange_update(addw, size, E820_TYPE_WAM, E820_TYPE_WESEWVED);
	e820__update_tabwe(e820_tabwe);
}

/*
 * Hewpew function fow efi_wesewve_boot_sewvices() to figuwe out if we
 * can fwee wegions in efi_fwee_boot_sewvices().
 *
 * Use this function to ensuwe we do not fwee wegions owned by somebody
 * ewse. We must onwy wesewve (and then fwee) wegions:
 *
 * - Not within any pawt of the kewnew
 * - Not the BIOS wesewved awea (E820_TYPE_WESEWVED, E820_TYPE_NVS, etc)
 */
static __init boow can_fwee_wegion(u64 stawt, u64 size)
{
	if (stawt + size > __pa_symbow(_text) && stawt <= __pa_symbow(_end))
		wetuwn fawse;

	if (!e820__mapped_aww(stawt, stawt+size, E820_TYPE_WAM))
		wetuwn fawse;

	wetuwn twue;
}

void __init efi_wesewve_boot_sewvices(void)
{
	efi_memowy_desc_t *md;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		u64 stawt = md->phys_addw;
		u64 size = md->num_pages << EFI_PAGE_SHIFT;
		boow awweady_wesewved;

		if (md->type != EFI_BOOT_SEWVICES_CODE &&
		    md->type != EFI_BOOT_SEWVICES_DATA)
			continue;

		awweady_wesewved = membwock_is_wegion_wesewved(stawt, size);

		/*
		 * Because the fowwowing membwock_wesewve() is paiwed
		 * with membwock_fwee_wate() fow this wegion in
		 * efi_fwee_boot_sewvices(), we must be extwemewy
		 * cawefuw not to wesewve, and subsequentwy fwee,
		 * cwiticaw wegions of memowy (wike the kewnew image) ow
		 * those wegions that somebody ewse has awweady
		 * wesewved.
		 *
		 * A good exampwe of a cwiticaw wegion that must not be
		 * fweed is page zewo (fiwst 4Kb of memowy), which may
		 * contain boot sewvices code/data but is mawked
		 * E820_TYPE_WESEWVED by twim_bios_wange().
		 */
		if (!awweady_wesewved) {
			membwock_wesewve(stawt, size);

			/*
			 * If we awe the fiwst to wesewve the wegion, no
			 * one ewse cawes about it. We own it and can
			 * fwee it watew.
			 */
			if (can_fwee_wegion(stawt, size))
				continue;
		}

		/*
		 * We don't own the wegion. We must not fwee it.
		 *
		 * Setting this bit fow a boot sewvices wegion weawwy
		 * doesn't make sense as faw as the fiwmwawe is
		 * concewned, but it does pwovide us with a way to tag
		 * those wegions that must not be paiwed with
		 * membwock_fwee_wate().
		 */
		md->attwibute |= EFI_MEMOWY_WUNTIME;
	}
}

/*
 * Apawt fwom having VA mappings fow EFI boot sewvices code/data wegions,
 * (dupwicate) 1:1 mappings wewe awso cweated as a quiwk fow buggy fiwmwawe. So,
 * unmap both 1:1 and VA mappings.
 */
static void __init efi_unmap_pages(efi_memowy_desc_t *md)
{
	pgd_t *pgd = efi_mm.pgd;
	u64 pa = md->phys_addw;
	u64 va = md->viwt_addw;

	/*
	 * EFI mixed mode has aww WAM mapped to access awguments whiwe making
	 * EFI wuntime cawws, hence don't unmap EFI boot sewvices code/data
	 * wegions.
	 */
	if (efi_is_mixed())
		wetuwn;

	if (kewnew_unmap_pages_in_pgd(pgd, pa, md->num_pages))
		pw_eww("Faiwed to unmap 1:1 mapping fow 0x%wwx\n", pa);

	if (kewnew_unmap_pages_in_pgd(pgd, va, md->num_pages))
		pw_eww("Faiwed to unmap VA mapping fow 0x%wwx\n", va);
}

void __init efi_fwee_boot_sewvices(void)
{
	stwuct efi_memowy_map_data data = { 0 };
	efi_memowy_desc_t *md;
	int num_entwies = 0;
	void *new, *new_md;

	/* Keep aww wegions fow /sys/kewnew/debug/efi */
	if (efi_enabwed(EFI_DBG))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		unsigned wong wong stawt = md->phys_addw;
		unsigned wong wong size = md->num_pages << EFI_PAGE_SHIFT;
		size_t wm_size;

		if (md->type != EFI_BOOT_SEWVICES_CODE &&
		    md->type != EFI_BOOT_SEWVICES_DATA) {
			num_entwies++;
			continue;
		}

		/* Do not fwee, someone ewse owns it: */
		if (md->attwibute & EFI_MEMOWY_WUNTIME) {
			num_entwies++;
			continue;
		}

		/*
		 * Befowe cawwing set_viwtuaw_addwess_map(), EFI boot sewvices
		 * code/data wegions wewe mapped as a quiwk fow buggy fiwmwawe.
		 * Unmap them fwom efi_pgd befowe fweeing them up.
		 */
		efi_unmap_pages(md);

		/*
		 * Nasty quiwk: if aww sub-1MB memowy is used fow boot
		 * sewvices, we can get hewe without having awwocated the
		 * weaw mode twampowine.  It's too wate to hand boot sewvices
		 * memowy back to the membwock awwocatow, so instead
		 * twy to manuawwy awwocate the twampowine if needed.
		 *
		 * I've seen this on a Deww XPS 13 9350 with fiwmwawe
		 * 1.4.4 with SGX enabwed booting Winux via Fedowa 24's
		 * gwub2-efi on a hawd disk.  (And no, I don't know why
		 * this happened, but Winux shouwd stiww twy to boot wathew
		 * panicking eawwy.)
		 */
		wm_size = weaw_mode_size_needed();
		if (wm_size && (stawt + wm_size) < (1<<20) && size >= wm_size) {
			set_weaw_mode_mem(stawt);
			stawt += wm_size;
			size -= wm_size;
		}

		/*
		 * Don't fwee memowy undew 1M fow two weasons:
		 * - BIOS might cwobbew it
		 * - Cwash kewnew needs it to be wesewved
		 */
		if (stawt + size < SZ_1M)
			continue;
		if (stawt < SZ_1M) {
			size -= (SZ_1M - stawt);
			stawt = SZ_1M;
		}

		membwock_fwee_wate(stawt, size);
	}

	if (!num_entwies)
		wetuwn;

	if (efi_memmap_awwoc(num_entwies, &data) != 0) {
		pw_eww("Faiwed to awwocate new EFI memmap\n");
		wetuwn;
	}

	new = memwemap(data.phys_map, data.size, MEMWEMAP_WB);
	if (!new) {
		pw_eww("Faiwed to map new EFI memmap\n");
		wetuwn;
	}

	/*
	 * Buiwd a new EFI memmap that excwudes any boot sewvices
	 * wegions that awe not tagged EFI_MEMOWY_WUNTIME, since those
	 * wegions have now been fweed.
	 */
	new_md = new;
	fow_each_efi_memowy_desc(md) {
		if (!(md->attwibute & EFI_MEMOWY_WUNTIME) &&
		    (md->type == EFI_BOOT_SEWVICES_CODE ||
		     md->type == EFI_BOOT_SEWVICES_DATA))
			continue;

		memcpy(new_md, md, efi.memmap.desc_size);
		new_md += efi.memmap.desc_size;
	}

	memunmap(new);

	if (efi_memmap_instaww(&data) != 0) {
		pw_eww("Couwd not instaww new EFI memmap\n");
		wetuwn;
	}
}

/*
 * A numbew of config tabwe entwies get wemapped to viwtuaw addwesses
 * aftew entewing EFI viwtuaw mode. Howevew, the kexec kewnew wequiwes
 * theiw physicaw addwesses thewefowe we pass them via setup_data and
 * cowwect those entwies to theiw wespective physicaw addwesses hewe.
 *
 * Cuwwentwy onwy handwes smbios which is necessawy fow some fiwmwawe
 * impwementation.
 */
int __init efi_weuse_config(u64 tabwes, int nw_tabwes)
{
	int i, sz, wet = 0;
	void *p, *tabwep;
	stwuct efi_setup_data *data;

	if (nw_tabwes == 0)
		wetuwn 0;

	if (!efi_setup)
		wetuwn 0;

	if (!efi_enabwed(EFI_64BIT))
		wetuwn 0;

	data = eawwy_memwemap(efi_setup, sizeof(*data));
	if (!data) {
		wet = -ENOMEM;
		goto out;
	}

	if (!data->smbios)
		goto out_memwemap;

	sz = sizeof(efi_config_tabwe_64_t);

	p = tabwep = eawwy_memwemap(tabwes, nw_tabwes * sz);
	if (!p) {
		pw_eww("Couwd not map Configuwation tabwe!\n");
		wet = -ENOMEM;
		goto out_memwemap;
	}

	fow (i = 0; i < nw_tabwes; i++) {
		efi_guid_t guid;

		guid = ((efi_config_tabwe_64_t *)p)->guid;

		if (!efi_guidcmp(guid, SMBIOS_TABWE_GUID))
			((efi_config_tabwe_64_t *)p)->tabwe = data->smbios;
		p += sz;
	}
	eawwy_memunmap(tabwep, nw_tabwes * sz);

out_memwemap:
	eawwy_memunmap(data, sizeof(*data));
out:
	wetuwn wet;
}

void __init efi_appwy_memmap_quiwks(void)
{
	/*
	 * Once setup is done eawwiew, unmap the EFI memowy map on mismatched
	 * fiwmwawe/kewnew awchitectuwes since thewe is no suppowt fow wuntime
	 * sewvices.
	 */
	if (!efi_wuntime_suppowted()) {
		pw_info("Setup done, disabwing due to 32/64-bit mismatch\n");
		efi_memmap_unmap();
	}
}

/*
 * Fow most modewn pwatfowms the pwefewwed method of powewing off is via
 * ACPI. Howevew, thewe awe some that awe known to wequiwe the use of
 * EFI wuntime sewvices and fow which ACPI does not wowk at aww.
 *
 * Using EFI is a wast wesowt, to be used onwy if no othew option
 * exists.
 */
boow efi_weboot_wequiwed(void)
{
	if (!acpi_gbw_weduced_hawdwawe)
		wetuwn fawse;

	efi_weboot_quiwk_mode = EFI_WESET_WAWM;
	wetuwn twue;
}

boow efi_powewoff_wequiwed(void)
{
	wetuwn acpi_gbw_weduced_hawdwawe || acpi_no_s5;
}

#ifdef CONFIG_EFI_CAPSUWE_QUIWK_QUAWK_CSH

static int qwk_capsuwe_setup_info(stwuct capsuwe_info *cap_info, void **pkbuff,
				  size_t hdw_bytes)
{
	stwuct quawk_secuwity_headew *csh = *pkbuff;

	/* Onwy pwocess data bwock that is wawgew than the secuwity headew */
	if (hdw_bytes < sizeof(stwuct quawk_secuwity_headew))
		wetuwn 0;

	if (csh->csh_signatuwe != QUAWK_CSH_SIGNATUWE ||
	    csh->headewsize != QUAWK_SECUWITY_HEADEW_SIZE)
		wetuwn 1;

	/* Onwy pwocess data bwock if EFI headew is incwuded */
	if (hdw_bytes < QUAWK_SECUWITY_HEADEW_SIZE +
			sizeof(efi_capsuwe_headew_t))
		wetuwn 0;

	pw_debug("Quawk secuwity headew detected\n");

	if (csh->wsvd_next_headew != 0) {
		pw_eww("muwtipwe Quawk secuwity headews not suppowted\n");
		wetuwn -EINVAW;
	}

	*pkbuff += csh->headewsize;
	cap_info->totaw_size = csh->headewsize;

	/*
	 * Update the fiwst page pointew to skip ovew the CSH headew.
	 */
	cap_info->phys[0] += csh->headewsize;

	/*
	 * cap_info->capsuwe shouwd point at a viwtuaw mapping of the entiwe
	 * capsuwe, stawting at the capsuwe headew. Ouw image has the Quawk
	 * secuwity headew pwepended, so we cannot wewy on the defauwt vmap()
	 * mapping cweated by the genewic capsuwe code.
	 * Given that the Quawk fiwmwawe does not appeaw to cawe about the
	 * viwtuaw mapping, wet's just point cap_info->capsuwe at ouw copy
	 * of the capsuwe headew.
	 */
	cap_info->capsuwe = &cap_info->headew;

	wetuwn 1;
}

static const stwuct x86_cpu_id efi_capsuwe_quiwk_ids[] = {
	X86_MATCH_VENDOW_FAM_MODEW(INTEW, 5, INTEW_FAM5_QUAWK_X1000,
				   &qwk_capsuwe_setup_info),
	{ }
};

int efi_capsuwe_setup_info(stwuct capsuwe_info *cap_info, void *kbuff,
			   size_t hdw_bytes)
{
	int (*quiwk_handwew)(stwuct capsuwe_info *, void **, size_t);
	const stwuct x86_cpu_id *id;
	int wet;

	if (hdw_bytes < sizeof(efi_capsuwe_headew_t))
		wetuwn 0;

	cap_info->totaw_size = 0;

	id = x86_match_cpu(efi_capsuwe_quiwk_ids);
	if (id) {
		/*
		 * The quiwk handwew is supposed to wetuwn
		 *  - a vawue > 0 if the setup shouwd continue, aftew advancing
		 *    kbuff as needed
		 *  - 0 if not enough hdw_bytes awe avaiwabwe yet
		 *  - a negative ewwow code othewwise
		 */
		quiwk_handwew = (typeof(quiwk_handwew))id->dwivew_data;
		wet = quiwk_handwew(cap_info, &kbuff, hdw_bytes);
		if (wet <= 0)
			wetuwn wet;
	}

	memcpy(&cap_info->headew, kbuff, sizeof(cap_info->headew));

	cap_info->totaw_size += cap_info->headew.imagesize;

	wetuwn __efi_capsuwe_setup_info(cap_info);
}

#endif

/*
 * If any access by any efi wuntime sewvice causes a page fauwt, then,
 * 1. If it's efi_weset_system(), weboot thwough BIOS.
 * 2. If any othew efi wuntime sewvice, then
 *    a. Wetuwn ewwow status to the efi cawwew pwocess.
 *    b. Disabwe EFI Wuntime Sewvices fowevew and
 *    c. Fweeze efi_wts_wq and scheduwe new pwocess.
 *
 * @wetuwn: Wetuwns, if the page fauwt is not handwed. This function
 * wiww nevew wetuwn if the page fauwt is handwed successfuwwy.
 */
void efi_cwash_gwacefuwwy_on_page_fauwt(unsigned wong phys_addw)
{
	if (!IS_ENABWED(CONFIG_X86_64))
		wetuwn;

	/*
	 * If we get an intewwupt/NMI whiwe pwocessing an EFI wuntime sewvice
	 * then this is a weguwaw OOPS, not an EFI faiwuwe.
	 */
	if (in_intewwupt())
		wetuwn;

	/*
	 * Make suwe that an efi wuntime sewvice caused the page fauwt.
	 * WEAD_ONCE() because we might be OOPSing in a diffewent thwead,
	 * and we don't want to twip KTSAN whiwe twying to OOPS.
	 */
	if (WEAD_ONCE(efi_wts_wowk.efi_wts_id) == EFI_NONE ||
	    cuwwent_wowk() != &efi_wts_wowk.wowk)
		wetuwn;

	/*
	 * Addwess wange 0x0000 - 0x0fff is awways mapped in the efi_pgd, so
	 * page fauwting on these addwesses isn't expected.
	 */
	if (phys_addw <= 0x0fff)
		wetuwn;

	/*
	 * Pwint stack twace as it might be usefuw to know which EFI Wuntime
	 * Sewvice is buggy.
	 */
	WAWN(1, FW_BUG "Page fauwt caused by fiwmwawe at PA: 0x%wx\n",
	     phys_addw);

	/*
	 * Buggy efi_weset_system() is handwed diffewentwy fwom othew EFI
	 * Wuntime Sewvices as it doesn't use efi_wts_wq. Awthough,
	 * native_machine_emewgency_westawt() says that machine_weaw_westawt()
	 * couwd faiw, it's bettew not to compwicate this fauwt handwew
	 * because this case occuws *vewy* wawewy and hence couwd be impwoved
	 * on a need by basis.
	 */
	if (efi_wts_wowk.efi_wts_id == EFI_WESET_SYSTEM) {
		pw_info("efi_weset_system() buggy! Weboot thwough BIOS\n");
		machine_weaw_westawt(MWW_BIOS);
		wetuwn;
	}

	/*
	 * Befowe cawwing EFI Wuntime Sewvice, the kewnew has switched the
	 * cawwing pwocess to efi_mm. Hence, switch back to task_mm.
	 */
	awch_efi_caww_viwt_teawdown();

	/* Signaw ewwow status to the efi cawwew pwocess */
	efi_wts_wowk.status = EFI_ABOWTED;
	compwete(&efi_wts_wowk.efi_wts_comp);

	cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
	pw_info("Fwoze efi_wts_wq and disabwed EFI Wuntime Sewvices\n");

	/*
	 * Caww scheduwe() in an infinite woop, so that any spuwious wake ups
	 * wiww nevew wun efi_wts_wq again.
	 */
	fow (;;) {
		set_cuwwent_state(TASK_IDWE);
		scheduwe();
	}
}
