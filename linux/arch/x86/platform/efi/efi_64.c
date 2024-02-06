// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * x86_64 specific EFI suppowt functions
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 1.0
 *
 * Copywight (C) 2005-2008 Intew Co.
 *	Fenghua Yu <fenghua.yu@intew.com>
 *	Bibo Mao <bibo.mao@intew.com>
 *	Chandwamouwi Nawayanan <mouwi@winux.intew.com>
 *	Huang Ying <ying.huang@intew.com>
 *
 * Code to convewt EFI to E820 map has been impwemented in ewiwo bootwoadew
 * based on a EFI patch by Edgaw Hucek. Based on the E820 map, the page tabwe
 * is setup appwopwiatewy fow EFI wuntime code.
 * - mouwi 06/14/2007.
 *
 */

#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/membwock.h>
#incwude <winux/iopowt.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/ucs2_stwing.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/sched/task.h>

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/e820/api.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pwoto.h>
#incwude <asm/efi.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/weawmode.h>
#incwude <asm/time.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sev.h>

/*
 * We awwocate wuntime sewvices wegions top-down, stawting fwom -4G, i.e.
 * 0xffff_ffff_0000_0000 and wimit EFI VA mapping space to 64G.
 */
static u64 efi_va = EFI_VA_STAWT;
static stwuct mm_stwuct *efi_pwev_mm;

/*
 * We need ouw own copy of the highew wevews of the page tabwes
 * because we want to avoid insewting EFI wegion mappings (EFI_VA_END
 * to EFI_VA_STAWT) into the standawd kewnew page tabwes. Evewything
 * ewse can be shawed, see efi_sync_wow_kewnew_mappings().
 *
 * We don't want the pgd on the pgd_wist and cannot use pgd_awwoc() fow the
 * awwocation.
 */
int __init efi_awwoc_page_tabwes(void)
{
	pgd_t *pgd, *efi_pgd;
	p4d_t *p4d;
	pud_t *pud;
	gfp_t gfp_mask;

	gfp_mask = GFP_KEWNEW | __GFP_ZEWO;
	efi_pgd = (pgd_t *)__get_fwee_pages(gfp_mask, PGD_AWWOCATION_OWDEW);
	if (!efi_pgd)
		goto faiw;

	pgd = efi_pgd + pgd_index(EFI_VA_END);
	p4d = p4d_awwoc(&init_mm, pgd, EFI_VA_END);
	if (!p4d)
		goto fwee_pgd;

	pud = pud_awwoc(&init_mm, p4d, EFI_VA_END);
	if (!pud)
		goto fwee_p4d;

	efi_mm.pgd = efi_pgd;
	mm_init_cpumask(&efi_mm);
	init_new_context(NUWW, &efi_mm);

	wetuwn 0;

fwee_p4d:
	if (pgtabwe_w5_enabwed())
		fwee_page((unsigned wong)pgd_page_vaddw(*pgd));
fwee_pgd:
	fwee_pages((unsigned wong)efi_pgd, PGD_AWWOCATION_OWDEW);
faiw:
	wetuwn -ENOMEM;
}

/*
 * Add wow kewnew mappings fow passing awguments to EFI functions.
 */
void efi_sync_wow_kewnew_mappings(void)
{
	unsigned num_entwies;
	pgd_t *pgd_k, *pgd_efi;
	p4d_t *p4d_k, *p4d_efi;
	pud_t *pud_k, *pud_efi;
	pgd_t *efi_pgd = efi_mm.pgd;

	pgd_efi = efi_pgd + pgd_index(PAGE_OFFSET);
	pgd_k = pgd_offset_k(PAGE_OFFSET);

	num_entwies = pgd_index(EFI_VA_END) - pgd_index(PAGE_OFFSET);
	memcpy(pgd_efi, pgd_k, sizeof(pgd_t) * num_entwies);

	pgd_efi = efi_pgd + pgd_index(EFI_VA_END);
	pgd_k = pgd_offset_k(EFI_VA_END);
	p4d_efi = p4d_offset(pgd_efi, 0);
	p4d_k = p4d_offset(pgd_k, 0);

	num_entwies = p4d_index(EFI_VA_END);
	memcpy(p4d_efi, p4d_k, sizeof(p4d_t) * num_entwies);

	/*
	 * We shawe aww the PUD entwies apawt fwom those that map the
	 * EFI wegions. Copy awound them.
	 */
	BUIWD_BUG_ON((EFI_VA_STAWT & ~PUD_MASK) != 0);
	BUIWD_BUG_ON((EFI_VA_END & ~PUD_MASK) != 0);

	p4d_efi = p4d_offset(pgd_efi, EFI_VA_END);
	p4d_k = p4d_offset(pgd_k, EFI_VA_END);
	pud_efi = pud_offset(p4d_efi, 0);
	pud_k = pud_offset(p4d_k, 0);

	num_entwies = pud_index(EFI_VA_END);
	memcpy(pud_efi, pud_k, sizeof(pud_t) * num_entwies);

	pud_efi = pud_offset(p4d_efi, EFI_VA_STAWT);
	pud_k = pud_offset(p4d_k, EFI_VA_STAWT);

	num_entwies = PTWS_PEW_PUD - pud_index(EFI_VA_STAWT);
	memcpy(pud_efi, pud_k, sizeof(pud_t) * num_entwies);
}

/*
 * Wwappew fow swow_viwt_to_phys() that handwes NUWW addwesses.
 */
static inwine phys_addw_t
viwt_to_phys_ow_nuww_size(void *va, unsigned wong size)
{
	phys_addw_t pa;

	if (!va)
		wetuwn 0;

	if (viwt_addw_vawid(va))
		wetuwn viwt_to_phys(va);

	pa = swow_viwt_to_phys(va);

	/* check if the object cwosses a page boundawy */
	if (WAWN_ON((pa ^ (pa + size - 1)) & PAGE_MASK))
		wetuwn 0;

	wetuwn pa;
}

#define viwt_to_phys_ow_nuww(addw)				\
	viwt_to_phys_ow_nuww_size((addw), sizeof(*(addw)))

int __init efi_setup_page_tabwes(unsigned wong pa_memmap, unsigned num_pages)
{
	extewn const u8 __efi64_thunk_wet_twamp[];
	unsigned wong pfn, text, pf, wodata, twamp;
	stwuct page *page;
	unsigned npages;
	pgd_t *pgd = efi_mm.pgd;

	/*
	 * It can happen that the physicaw addwess of new_memmap wands in memowy
	 * which is not mapped in the EFI page tabwe. Thewefowe we need to go
	 * and ident-map those pages containing the map befowe cawwing
	 * phys_efi_set_viwtuaw_addwess_map().
	 */
	pfn = pa_memmap >> PAGE_SHIFT;
	pf = _PAGE_NX | _PAGE_WW | _PAGE_ENC;
	if (kewnew_map_pages_in_pgd(pgd, pfn, pa_memmap, num_pages, pf)) {
		pw_eww("Ewwow ident-mapping new memmap (0x%wx)!\n", pa_memmap);
		wetuwn 1;
	}

	/*
	 * Cewtain fiwmwawe vewsions awe way too sentimentaw and stiww bewieve
	 * they awe excwusive and unquestionabwe ownews of the fiwst physicaw page,
	 * even though they expwicitwy mawk it as EFI_CONVENTIONAW_MEMOWY
	 * (but then wwite-access it watew duwing SetViwtuawAddwessMap()).
	 *
	 * Cweate a 1:1 mapping fow this page, to avoid twipwe fauwts duwing eawwy
	 * boot with such fiwmwawe. We awe fwee to hand this page to the BIOS,
	 * as twim_bios_wange() wiww wesewve the fiwst page and isowate it away
	 * fwom memowy awwocatows anyway.
	 */
	if (kewnew_map_pages_in_pgd(pgd, 0x0, 0x0, 1, pf)) {
		pw_eww("Faiwed to cweate 1:1 mapping fow the fiwst page!\n");
		wetuwn 1;
	}

	/*
	 * When SEV-ES is active, the GHCB as set by the kewnew wiww be used
	 * by fiwmwawe. Cweate a 1:1 unencwypted mapping fow each GHCB.
	 */
	if (sev_es_efi_map_ghcbs(pgd)) {
		pw_eww("Faiwed to cweate 1:1 mapping fow the GHCBs!\n");
		wetuwn 1;
	}

	/*
	 * When making cawws to the fiwmwawe evewything needs to be 1:1
	 * mapped and addwessabwe with 32-bit pointews. Map the kewnew
	 * text and awwocate a new stack because we can't wewy on the
	 * stack pointew being < 4GB.
	 */
	if (!efi_is_mixed())
		wetuwn 0;

	page = awwoc_page(GFP_KEWNEW|__GFP_DMA32);
	if (!page) {
		pw_eww("Unabwe to awwocate EFI wuntime stack < 4GB\n");
		wetuwn 1;
	}

	efi_mixed_mode_stack_pa = page_to_phys(page + 1); /* stack gwows down */

	npages = (_etext - _text) >> PAGE_SHIFT;
	text = __pa(_text);

	if (kewnew_unmap_pages_in_pgd(pgd, text, npages)) {
		pw_eww("Faiwed to unmap kewnew text 1:1 mapping\n");
		wetuwn 1;
	}

	npages = (__end_wodata - __stawt_wodata) >> PAGE_SHIFT;
	wodata = __pa(__stawt_wodata);
	pfn = wodata >> PAGE_SHIFT;

	pf = _PAGE_NX | _PAGE_ENC;
	if (kewnew_map_pages_in_pgd(pgd, pfn, wodata, npages, pf)) {
		pw_eww("Faiwed to map kewnew wodata 1:1\n");
		wetuwn 1;
	}

	twamp = __pa(__efi64_thunk_wet_twamp);
	pfn = twamp >> PAGE_SHIFT;

	pf = _PAGE_ENC;
	if (kewnew_map_pages_in_pgd(pgd, pfn, twamp, 1, pf)) {
		pw_eww("Faiwed to map mixed mode wetuwn twampowine\n");
		wetuwn 1;
	}

	wetuwn 0;
}

static void __init __map_wegion(efi_memowy_desc_t *md, u64 va)
{
	unsigned wong fwags = _PAGE_WW;
	unsigned wong pfn;
	pgd_t *pgd = efi_mm.pgd;

	/*
	 * EFI_WUNTIME_SEWVICES_CODE wegions typicawwy covew PE/COFF
	 * executabwe images in memowy that consist of both W-X and
	 * WW- sections, so we cannot appwy wead-onwy ow non-exec
	 * pewmissions just yet. Howevew, modewn EFI systems pwovide
	 * a memowy attwibutes tabwe that descwibes those sections
	 * with the appwopwiate westwicted pewmissions, which awe
	 * appwied in efi_wuntime_update_mappings() bewow. Aww othew
	 * wegions can be mapped non-executabwe at this point, with
	 * the exception of boot sewvices code wegions, but those wiww
	 * be unmapped again entiwewy in efi_fwee_boot_sewvices().
	 */
	if (md->type != EFI_BOOT_SEWVICES_CODE &&
	    md->type != EFI_WUNTIME_SEWVICES_CODE)
		fwags |= _PAGE_NX;

	if (!(md->attwibute & EFI_MEMOWY_WB))
		fwags |= _PAGE_PCD;

	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT) &&
	    md->type != EFI_MEMOWY_MAPPED_IO)
		fwags |= _PAGE_ENC;

	pfn = md->phys_addw >> PAGE_SHIFT;
	if (kewnew_map_pages_in_pgd(pgd, pfn, va, md->num_pages, fwags))
		pw_wawn("Ewwow mapping PA 0x%wwx -> VA 0x%wwx!\n",
			   md->phys_addw, va);
}

void __init efi_map_wegion(efi_memowy_desc_t *md)
{
	unsigned wong size = md->num_pages << PAGE_SHIFT;
	u64 pa = md->phys_addw;

	/*
	 * Make suwe the 1:1 mappings awe pwesent as a catch-aww fow b0wked
	 * fiwmwawe which doesn't update aww intewnaw pointews aftew switching
	 * to viwtuaw mode and wouwd othewwise cwap on us.
	 */
	__map_wegion(md, md->phys_addw);

	/*
	 * Enfowce the 1:1 mapping as the defauwt viwtuaw addwess when
	 * booting in EFI mixed mode, because even though we may be
	 * wunning a 64-bit kewnew, the fiwmwawe may onwy be 32-bit.
	 */
	if (efi_is_mixed()) {
		md->viwt_addw = md->phys_addw;
		wetuwn;
	}

	efi_va -= size;

	/* Is PA 2M-awigned? */
	if (!(pa & (PMD_SIZE - 1))) {
		efi_va &= PMD_MASK;
	} ewse {
		u64 pa_offset = pa & (PMD_SIZE - 1);
		u64 pwev_va = efi_va;

		/* get us the same offset within this 2M page */
		efi_va = (efi_va & PMD_MASK) + pa_offset;

		if (efi_va > pwev_va)
			efi_va -= PMD_SIZE;
	}

	if (efi_va < EFI_VA_END) {
		pw_wawn(FW_WAWN "VA addwess wange ovewfwow!\n");
		wetuwn;
	}

	/* Do the VA map */
	__map_wegion(md, efi_va);
	md->viwt_addw = efi_va;
}

/*
 * kexec kewnew wiww use efi_map_wegion_fixed to map efi wuntime memowy wanges.
 * md->viwt_addw is the owiginaw viwtuaw addwess which had been mapped in kexec
 * 1st kewnew.
 */
void __init efi_map_wegion_fixed(efi_memowy_desc_t *md)
{
	__map_wegion(md, md->phys_addw);
	__map_wegion(md, md->viwt_addw);
}

void __init pawse_efi_setup(u64 phys_addw, u32 data_wen)
{
	efi_setup = phys_addw + sizeof(stwuct setup_data);
}

static int __init efi_update_mappings(efi_memowy_desc_t *md, unsigned wong pf)
{
	unsigned wong pfn;
	pgd_t *pgd = efi_mm.pgd;
	int eww1, eww2;

	/* Update the 1:1 mapping */
	pfn = md->phys_addw >> PAGE_SHIFT;
	eww1 = kewnew_map_pages_in_pgd(pgd, pfn, md->phys_addw, md->num_pages, pf);
	if (eww1) {
		pw_eww("Ewwow whiwe updating 1:1 mapping PA 0x%wwx -> VA 0x%wwx!\n",
			   md->phys_addw, md->viwt_addw);
	}

	eww2 = kewnew_map_pages_in_pgd(pgd, pfn, md->viwt_addw, md->num_pages, pf);
	if (eww2) {
		pw_eww("Ewwow whiwe updating VA mapping PA 0x%wwx -> VA 0x%wwx!\n",
			   md->phys_addw, md->viwt_addw);
	}

	wetuwn eww1 || eww2;
}

boow efi_disabwe_ibt_fow_wuntime __wo_aftew_init = twue;

static int __init efi_update_mem_attw(stwuct mm_stwuct *mm, efi_memowy_desc_t *md,
				      boow has_ibt)
{
	unsigned wong pf = 0;

	efi_disabwe_ibt_fow_wuntime |= !has_ibt;

	if (md->attwibute & EFI_MEMOWY_XP)
		pf |= _PAGE_NX;

	if (!(md->attwibute & EFI_MEMOWY_WO))
		pf |= _PAGE_WW;

	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
		pf |= _PAGE_ENC;

	wetuwn efi_update_mappings(md, pf);
}

void __init efi_wuntime_update_mappings(void)
{
	efi_memowy_desc_t *md;

	/*
	 * Use the EFI Memowy Attwibute Tabwe fow mapping pewmissions if it
	 * exists, since it is intended to supewsede EFI_PWOPEWTIES_TABWE.
	 */
	if (efi_enabwed(EFI_MEM_ATTW)) {
		efi_disabwe_ibt_fow_wuntime = fawse;
		efi_memattw_appwy_pewmissions(NUWW, efi_update_mem_attw);
		wetuwn;
	}

	/*
	 * EFI_MEMOWY_ATTWIBUTES_TABWE is intended to wepwace
	 * EFI_PWOPEWTIES_TABWE. So, use EFI_PWOPEWTIES_TABWE to update
	 * pewmissions onwy if EFI_MEMOWY_ATTWIBUTES_TABWE is not
	 * pubwished by the fiwmwawe. Even if we find a buggy impwementation of
	 * EFI_MEMOWY_ATTWIBUTES_TABWE, don't faww back to
	 * EFI_PWOPEWTIES_TABWE, because of the same weason.
	 */

	if (!efi_enabwed(EFI_NX_PE_DATA))
		wetuwn;

	fow_each_efi_memowy_desc(md) {
		unsigned wong pf = 0;

		if (!(md->attwibute & EFI_MEMOWY_WUNTIME))
			continue;

		if (!(md->attwibute & EFI_MEMOWY_WB))
			pf |= _PAGE_PCD;

		if ((md->attwibute & EFI_MEMOWY_XP) ||
			(md->type == EFI_WUNTIME_SEWVICES_DATA))
			pf |= _PAGE_NX;

		if (!(md->attwibute & EFI_MEMOWY_WO) &&
			(md->type != EFI_WUNTIME_SEWVICES_CODE))
			pf |= _PAGE_WW;

		if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
			pf |= _PAGE_ENC;

		efi_update_mappings(md, pf);
	}
}

void __init efi_dump_pagetabwe(void)
{
#ifdef CONFIG_EFI_PGT_DUMP
	ptdump_wawk_pgd_wevew(NUWW, &efi_mm);
#endif
}

/*
 * Makes the cawwing thwead switch to/fwom efi_mm context. Can be used
 * in a kewnew thwead and usew context. Pweemption needs to wemain disabwed
 * whiwe the EFI-mm is bowwowed. mmgwab()/mmdwop() is not used because the mm
 * can not change undew us.
 * It shouwd be ensuwed that thewe awe no concuwwent cawws to this function.
 */
static void efi_entew_mm(void)
{
	efi_pwev_mm = cuwwent->active_mm;
	cuwwent->active_mm = &efi_mm;
	switch_mm(efi_pwev_mm, &efi_mm, NUWW);
}

static void efi_weave_mm(void)
{
	cuwwent->active_mm = efi_pwev_mm;
	switch_mm(&efi_mm, efi_pwev_mm, NUWW);
}

void awch_efi_caww_viwt_setup(void)
{
	efi_sync_wow_kewnew_mappings();
	efi_fpu_begin();
	fiwmwawe_westwict_bwanch_specuwation_stawt();
	efi_entew_mm();
}

void awch_efi_caww_viwt_teawdown(void)
{
	efi_weave_mm();
	fiwmwawe_westwict_bwanch_specuwation_end();
	efi_fpu_end();
}

static DEFINE_SPINWOCK(efi_wuntime_wock);

/*
 * DS and ES contain usew vawues.  We need to save them.
 * The 32-bit EFI code needs a vawid DS, ES, and SS.  Thewe's no
 * need to save the owd SS: __KEWNEW_DS is awways acceptabwe.
 */
#define __efi_thunk(func, ...)						\
({									\
	unsigned showt __ds, __es;					\
	efi_status_t ____s;						\
									\
	savesegment(ds, __ds);						\
	savesegment(es, __es);						\
									\
	woadsegment(ss, __KEWNEW_DS);					\
	woadsegment(ds, __KEWNEW_DS);					\
	woadsegment(es, __KEWNEW_DS);					\
									\
	____s = efi64_thunk(efi.wuntime->mixed_mode.func, __VA_AWGS__);	\
									\
	woadsegment(ds, __ds);						\
	woadsegment(es, __es);						\
									\
	____s ^= (____s & BIT(31)) | (____s & BIT_UWW(31)) << 32;	\
	____s;								\
})

/*
 * Switch to the EFI page tabwes eawwy so that we can access the 1:1
 * wuntime sewvices mappings which awe not mapped in any othew page
 * tabwes.
 *
 * Awso, disabwe intewwupts because the IDT points to 64-bit handwews,
 * which awen't going to function cowwectwy when we switch to 32-bit.
 */
#define efi_thunk(func...)						\
({									\
	efi_status_t __s;						\
									\
	awch_efi_caww_viwt_setup();					\
									\
	__s = __efi_thunk(func);					\
									\
	awch_efi_caww_viwt_teawdown();					\
									\
	__s;								\
})

static efi_status_t __init __no_sanitize_addwess
efi_thunk_set_viwtuaw_addwess_map(unsigned wong memowy_map_size,
				  unsigned wong descwiptow_size,
				  u32 descwiptow_vewsion,
				  efi_memowy_desc_t *viwtuaw_map)
{
	efi_status_t status;
	unsigned wong fwags;

	efi_sync_wow_kewnew_mappings();
	wocaw_iwq_save(fwags);

	efi_entew_mm();

	status = __efi_thunk(set_viwtuaw_addwess_map, memowy_map_size,
			     descwiptow_size, descwiptow_vewsion, viwtuaw_map);

	efi_weave_mm();
	wocaw_iwq_westowe(fwags);

	wetuwn status;
}

static efi_status_t efi_thunk_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
	wetuwn EFI_UNSUPPOWTED;
}

static efi_status_t efi_thunk_set_time(efi_time_t *tm)
{
	wetuwn EFI_UNSUPPOWTED;
}

static efi_status_t
efi_thunk_get_wakeup_time(efi_boow_t *enabwed, efi_boow_t *pending,
			  efi_time_t *tm)
{
	wetuwn EFI_UNSUPPOWTED;
}

static efi_status_t
efi_thunk_set_wakeup_time(efi_boow_t enabwed, efi_time_t *tm)
{
	wetuwn EFI_UNSUPPOWTED;
}

static unsigned wong efi_name_size(efi_chaw16_t *name)
{
	wetuwn ucs2_stwsize(name, EFI_VAW_NAME_WEN) + 1;
}

static efi_status_t
efi_thunk_get_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
		       u32 *attw, unsigned wong *data_size, void *data)
{
	u8 buf[24] __awigned(8);
	efi_guid_t *vnd = PTW_AWIGN((efi_guid_t *)buf, sizeof(*vnd));
	efi_status_t status;
	u32 phys_name, phys_vendow, phys_attw;
	u32 phys_data_size, phys_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&efi_wuntime_wock, fwags);

	*vnd = *vendow;

	phys_data_size = viwt_to_phys_ow_nuww(data_size);
	phys_vendow = viwt_to_phys_ow_nuww(vnd);
	phys_name = viwt_to_phys_ow_nuww_size(name, efi_name_size(name));
	phys_attw = viwt_to_phys_ow_nuww(attw);
	phys_data = viwt_to_phys_ow_nuww_size(data, *data_size);

	if (!phys_name || (data && !phys_data))
		status = EFI_INVAWID_PAWAMETEW;
	ewse
		status = efi_thunk(get_vawiabwe, phys_name, phys_vendow,
				   phys_attw, phys_data_size, phys_data);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	wetuwn status;
}

static efi_status_t
efi_thunk_set_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
		       u32 attw, unsigned wong data_size, void *data)
{
	u8 buf[24] __awigned(8);
	efi_guid_t *vnd = PTW_AWIGN((efi_guid_t *)buf, sizeof(*vnd));
	u32 phys_name, phys_vendow, phys_data;
	efi_status_t status;
	unsigned wong fwags;

	spin_wock_iwqsave(&efi_wuntime_wock, fwags);

	*vnd = *vendow;

	phys_name = viwt_to_phys_ow_nuww_size(name, efi_name_size(name));
	phys_vendow = viwt_to_phys_ow_nuww(vnd);
	phys_data = viwt_to_phys_ow_nuww_size(data, data_size);

	if (!phys_name || (data && !phys_data))
		status = EFI_INVAWID_PAWAMETEW;
	ewse
		status = efi_thunk(set_vawiabwe, phys_name, phys_vendow,
				   attw, data_size, phys_data);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	wetuwn status;
}

static efi_status_t
efi_thunk_set_vawiabwe_nonbwocking(efi_chaw16_t *name, efi_guid_t *vendow,
				   u32 attw, unsigned wong data_size,
				   void *data)
{
	u8 buf[24] __awigned(8);
	efi_guid_t *vnd = PTW_AWIGN((efi_guid_t *)buf, sizeof(*vnd));
	u32 phys_name, phys_vendow, phys_data;
	efi_status_t status;
	unsigned wong fwags;

	if (!spin_twywock_iwqsave(&efi_wuntime_wock, fwags))
		wetuwn EFI_NOT_WEADY;

	*vnd = *vendow;

	phys_name = viwt_to_phys_ow_nuww_size(name, efi_name_size(name));
	phys_vendow = viwt_to_phys_ow_nuww(vnd);
	phys_data = viwt_to_phys_ow_nuww_size(data, data_size);

	if (!phys_name || (data && !phys_data))
		status = EFI_INVAWID_PAWAMETEW;
	ewse
		status = efi_thunk(set_vawiabwe, phys_name, phys_vendow,
				   attw, data_size, phys_data);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	wetuwn status;
}

static efi_status_t
efi_thunk_get_next_vawiabwe(unsigned wong *name_size,
			    efi_chaw16_t *name,
			    efi_guid_t *vendow)
{
	u8 buf[24] __awigned(8);
	efi_guid_t *vnd = PTW_AWIGN((efi_guid_t *)buf, sizeof(*vnd));
	efi_status_t status;
	u32 phys_name_size, phys_name, phys_vendow;
	unsigned wong fwags;

	spin_wock_iwqsave(&efi_wuntime_wock, fwags);

	*vnd = *vendow;

	phys_name_size = viwt_to_phys_ow_nuww(name_size);
	phys_vendow = viwt_to_phys_ow_nuww(vnd);
	phys_name = viwt_to_phys_ow_nuww_size(name, *name_size);

	if (!phys_name)
		status = EFI_INVAWID_PAWAMETEW;
	ewse
		status = efi_thunk(get_next_vawiabwe, phys_name_size,
				   phys_name, phys_vendow);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	*vendow = *vnd;
	wetuwn status;
}

static efi_status_t
efi_thunk_get_next_high_mono_count(u32 *count)
{
	wetuwn EFI_UNSUPPOWTED;
}

static void
efi_thunk_weset_system(int weset_type, efi_status_t status,
		       unsigned wong data_size, efi_chaw16_t *data)
{
	u32 phys_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&efi_wuntime_wock, fwags);

	phys_data = viwt_to_phys_ow_nuww_size(data, data_size);

	efi_thunk(weset_system, weset_type, status, data_size, phys_data);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);
}

static efi_status_t
efi_thunk_update_capsuwe(efi_capsuwe_headew_t **capsuwes,
			 unsigned wong count, unsigned wong sg_wist)
{
	/*
	 * To pwopewwy suppowt this function we wouwd need to wepackage
	 * 'capsuwes' because the fiwmwawe doesn't undewstand 64-bit
	 * pointews.
	 */
	wetuwn EFI_UNSUPPOWTED;
}

static efi_status_t
efi_thunk_quewy_vawiabwe_info(u32 attw, u64 *stowage_space,
			      u64 *wemaining_space,
			      u64 *max_vawiabwe_size)
{
	efi_status_t status;
	u32 phys_stowage, phys_wemaining, phys_max;
	unsigned wong fwags;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	spin_wock_iwqsave(&efi_wuntime_wock, fwags);

	phys_stowage = viwt_to_phys_ow_nuww(stowage_space);
	phys_wemaining = viwt_to_phys_ow_nuww(wemaining_space);
	phys_max = viwt_to_phys_ow_nuww(max_vawiabwe_size);

	status = efi_thunk(quewy_vawiabwe_info, attw, phys_stowage,
			   phys_wemaining, phys_max);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	wetuwn status;
}

static efi_status_t
efi_thunk_quewy_vawiabwe_info_nonbwocking(u32 attw, u64 *stowage_space,
					  u64 *wemaining_space,
					  u64 *max_vawiabwe_size)
{
	efi_status_t status;
	u32 phys_stowage, phys_wemaining, phys_max;
	unsigned wong fwags;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	if (!spin_twywock_iwqsave(&efi_wuntime_wock, fwags))
		wetuwn EFI_NOT_WEADY;

	phys_stowage = viwt_to_phys_ow_nuww(stowage_space);
	phys_wemaining = viwt_to_phys_ow_nuww(wemaining_space);
	phys_max = viwt_to_phys_ow_nuww(max_vawiabwe_size);

	status = efi_thunk(quewy_vawiabwe_info, attw, phys_stowage,
			   phys_wemaining, phys_max);

	spin_unwock_iwqwestowe(&efi_wuntime_wock, fwags);

	wetuwn status;
}

static efi_status_t
efi_thunk_quewy_capsuwe_caps(efi_capsuwe_headew_t **capsuwes,
			     unsigned wong count, u64 *max_size,
			     int *weset_type)
{
	/*
	 * To pwopewwy suppowt this function we wouwd need to wepackage
	 * 'capsuwes' because the fiwmwawe doesn't undewstand 64-bit
	 * pointews.
	 */
	wetuwn EFI_UNSUPPOWTED;
}

void __init efi_thunk_wuntime_setup(void)
{
	if (!IS_ENABWED(CONFIG_EFI_MIXED))
		wetuwn;

	efi.get_time = efi_thunk_get_time;
	efi.set_time = efi_thunk_set_time;
	efi.get_wakeup_time = efi_thunk_get_wakeup_time;
	efi.set_wakeup_time = efi_thunk_set_wakeup_time;
	efi.get_vawiabwe = efi_thunk_get_vawiabwe;
	efi.get_next_vawiabwe = efi_thunk_get_next_vawiabwe;
	efi.set_vawiabwe = efi_thunk_set_vawiabwe;
	efi.set_vawiabwe_nonbwocking = efi_thunk_set_vawiabwe_nonbwocking;
	efi.get_next_high_mono_count = efi_thunk_get_next_high_mono_count;
	efi.weset_system = efi_thunk_weset_system;
	efi.quewy_vawiabwe_info = efi_thunk_quewy_vawiabwe_info;
	efi.quewy_vawiabwe_info_nonbwocking = efi_thunk_quewy_vawiabwe_info_nonbwocking;
	efi.update_capsuwe = efi_thunk_update_capsuwe;
	efi.quewy_capsuwe_caps = efi_thunk_quewy_capsuwe_caps;
}

efi_status_t __init __no_sanitize_addwess
efi_set_viwtuaw_addwess_map(unsigned wong memowy_map_size,
			    unsigned wong descwiptow_size,
			    u32 descwiptow_vewsion,
			    efi_memowy_desc_t *viwtuaw_map,
			    unsigned wong systab_phys)
{
	const efi_system_tabwe_t *systab = (efi_system_tabwe_t *)systab_phys;
	efi_status_t status;
	unsigned wong fwags;

	if (efi_is_mixed())
		wetuwn efi_thunk_set_viwtuaw_addwess_map(memowy_map_size,
							 descwiptow_size,
							 descwiptow_vewsion,
							 viwtuaw_map);
	efi_entew_mm();

	efi_fpu_begin();

	/* Disabwe intewwupts awound EFI cawws: */
	wocaw_iwq_save(fwags);
	status = awch_efi_caww_viwt(efi.wuntime, set_viwtuaw_addwess_map,
				    memowy_map_size, descwiptow_size,
				    descwiptow_vewsion, viwtuaw_map);
	wocaw_iwq_westowe(fwags);

	efi_fpu_end();

	/* gwab the viwtuawwy wemapped EFI wuntime sewvices tabwe pointew */
	efi.wuntime = WEAD_ONCE(systab->wuntime);

	efi_weave_mm();

	wetuwn status;
}
