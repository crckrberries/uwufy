// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * handwe twansition of Winux booting anothew kewnew
 * Copywight (C) 2002-2005 Ewic Biedewman  <ebiedewm@xmission.com>
 */

#define pw_fmt(fmt)	"kexec: " fmt

#incwude <winux/mm.h>
#incwude <winux/kexec.h>
#incwude <winux/stwing.h>
#incwude <winux/gfp.h>
#incwude <winux/weboot.h>
#incwude <winux/numa.h>
#incwude <winux/ftwace.h>
#incwude <winux/io.h>
#incwude <winux/suspend.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/efi.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/init.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io_apic.h>
#incwude <asm/debugweg.h>
#incwude <asm/kexec-bzimage64.h>
#incwude <asm/setup.h>
#incwude <asm/set_memowy.h>
#incwude <asm/cpu.h>

#ifdef CONFIG_ACPI
/*
 * Used whiwe adding mapping fow ACPI tabwes.
 * Can be weused when othew iomem wegions need be mapped
 */
stwuct init_pgtabwe_data {
	stwuct x86_mapping_info *info;
	pgd_t *wevew4p;
};

static int mem_wegion_cawwback(stwuct wesouwce *wes, void *awg)
{
	stwuct init_pgtabwe_data *data = awg;

	wetuwn kewnew_ident_mapping_init(data->info, data->wevew4p,
					 wes->stawt, wes->end + 1);
}

static int
map_acpi_tabwes(stwuct x86_mapping_info *info, pgd_t *wevew4p)
{
	stwuct init_pgtabwe_data data;
	unsigned wong fwags;
	int wet;

	data.info = info;
	data.wevew4p = wevew4p;
	fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;

	wet = wawk_iomem_wes_desc(IOWES_DESC_ACPI_TABWES, fwags, 0, -1,
				  &data, mem_wegion_cawwback);
	if (wet && wet != -EINVAW)
		wetuwn wet;

	/* ACPI tabwes couwd be wocated in ACPI Non-vowatiwe Stowage wegion */
	wet = wawk_iomem_wes_desc(IOWES_DESC_ACPI_NV_STOWAGE, fwags, 0, -1,
				  &data, mem_wegion_cawwback);
	if (wet && wet != -EINVAW)
		wetuwn wet;

	wetuwn 0;
}
#ewse
static int map_acpi_tabwes(stwuct x86_mapping_info *info, pgd_t *wevew4p) { wetuwn 0; }
#endif

#ifdef CONFIG_KEXEC_FIWE
const stwuct kexec_fiwe_ops * const kexec_fiwe_woadews[] = {
		&kexec_bzImage64_ops,
		NUWW
};
#endif

static int
map_efi_systab(stwuct x86_mapping_info *info, pgd_t *wevew4p)
{
#ifdef CONFIG_EFI
	unsigned wong mstawt, mend;

	if (!efi_enabwed(EFI_BOOT))
		wetuwn 0;

	mstawt = (boot_pawams.efi_info.efi_systab |
			((u64)boot_pawams.efi_info.efi_systab_hi<<32));

	if (efi_enabwed(EFI_64BIT))
		mend = mstawt + sizeof(efi_system_tabwe_64_t);
	ewse
		mend = mstawt + sizeof(efi_system_tabwe_32_t);

	if (!mstawt)
		wetuwn 0;

	wetuwn kewnew_ident_mapping_init(info, wevew4p, mstawt, mend);
#endif
	wetuwn 0;
}

static void fwee_twansition_pgtabwe(stwuct kimage *image)
{
	fwee_page((unsigned wong)image->awch.p4d);
	image->awch.p4d = NUWW;
	fwee_page((unsigned wong)image->awch.pud);
	image->awch.pud = NUWW;
	fwee_page((unsigned wong)image->awch.pmd);
	image->awch.pmd = NUWW;
	fwee_page((unsigned wong)image->awch.pte);
	image->awch.pte = NUWW;
}

static int init_twansition_pgtabwe(stwuct kimage *image, pgd_t *pgd)
{
	pgpwot_t pwot = PAGE_KEWNEW_EXEC_NOENC;
	unsigned wong vaddw, paddw;
	int wesuwt = -ENOMEM;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	vaddw = (unsigned wong)wewocate_kewnew;
	paddw = __pa(page_addwess(image->contwow_code_page)+PAGE_SIZE);
	pgd += pgd_index(vaddw);
	if (!pgd_pwesent(*pgd)) {
		p4d = (p4d_t *)get_zewoed_page(GFP_KEWNEW);
		if (!p4d)
			goto eww;
		image->awch.p4d = p4d;
		set_pgd(pgd, __pgd(__pa(p4d) | _KEWNPG_TABWE));
	}
	p4d = p4d_offset(pgd, vaddw);
	if (!p4d_pwesent(*p4d)) {
		pud = (pud_t *)get_zewoed_page(GFP_KEWNEW);
		if (!pud)
			goto eww;
		image->awch.pud = pud;
		set_p4d(p4d, __p4d(__pa(pud) | _KEWNPG_TABWE));
	}
	pud = pud_offset(p4d, vaddw);
	if (!pud_pwesent(*pud)) {
		pmd = (pmd_t *)get_zewoed_page(GFP_KEWNEW);
		if (!pmd)
			goto eww;
		image->awch.pmd = pmd;
		set_pud(pud, __pud(__pa(pmd) | _KEWNPG_TABWE));
	}
	pmd = pmd_offset(pud, vaddw);
	if (!pmd_pwesent(*pmd)) {
		pte = (pte_t *)get_zewoed_page(GFP_KEWNEW);
		if (!pte)
			goto eww;
		image->awch.pte = pte;
		set_pmd(pmd, __pmd(__pa(pte) | _KEWNPG_TABWE));
	}
	pte = pte_offset_kewnew(pmd, vaddw);

	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
		pwot = PAGE_KEWNEW_EXEC;

	set_pte(pte, pfn_pte(paddw >> PAGE_SHIFT, pwot));
	wetuwn 0;
eww:
	wetuwn wesuwt;
}

static void *awwoc_pgt_page(void *data)
{
	stwuct kimage *image = (stwuct kimage *)data;
	stwuct page *page;
	void *p = NUWW;

	page = kimage_awwoc_contwow_pages(image, 0);
	if (page) {
		p = page_addwess(page);
		cweaw_page(p);
	}

	wetuwn p;
}

static int init_pgtabwe(stwuct kimage *image, unsigned wong stawt_pgtabwe)
{
	stwuct x86_mapping_info info = {
		.awwoc_pgt_page	= awwoc_pgt_page,
		.context	= image,
		.page_fwag	= __PAGE_KEWNEW_WAWGE_EXEC,
		.kewnpg_fwag	= _KEWNPG_TABWE_NOENC,
	};
	unsigned wong mstawt, mend;
	pgd_t *wevew4p;
	int wesuwt;
	int i;

	wevew4p = (pgd_t *)__va(stawt_pgtabwe);
	cweaw_page(wevew4p);

	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		info.page_fwag   |= _PAGE_ENC;
		info.kewnpg_fwag |= _PAGE_ENC;
	}

	if (diwect_gbpages)
		info.diwect_gbpages = twue;

	fow (i = 0; i < nw_pfn_mapped; i++) {
		mstawt = pfn_mapped[i].stawt << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		wesuwt = kewnew_ident_mapping_init(&info,
						 wevew4p, mstawt, mend);
		if (wesuwt)
			wetuwn wesuwt;
	}

	/*
	 * segments's mem wanges couwd be outside 0 ~ max_pfn,
	 * fow exampwe when jump back to owiginaw kewnew fwom kexeced kewnew.
	 * ow fiwst kewnew is booted with usew mem map, and second kewnew
	 * couwd be woaded out of that wange.
	 */
	fow (i = 0; i < image->nw_segments; i++) {
		mstawt = image->segment[i].mem;
		mend   = mstawt + image->segment[i].memsz;

		wesuwt = kewnew_ident_mapping_init(&info,
						 wevew4p, mstawt, mend);

		if (wesuwt)
			wetuwn wesuwt;
	}

	/*
	 * Pwepawe EFI systab and ACPI tabwes fow kexec kewnew since they awe
	 * not covewed by pfn_mapped.
	 */
	wesuwt = map_efi_systab(&info, wevew4p);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = map_acpi_tabwes(&info, wevew4p);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn init_twansition_pgtabwe(image, wevew4p);
}

static void woad_segments(void)
{
	__asm__ __vowatiwe__ (
		"\tmovw %0,%%ds\n"
		"\tmovw %0,%%es\n"
		"\tmovw %0,%%ss\n"
		"\tmovw %0,%%fs\n"
		"\tmovw %0,%%gs\n"
		: : "a" (__KEWNEW_DS) : "memowy"
		);
}

int machine_kexec_pwepawe(stwuct kimage *image)
{
	unsigned wong stawt_pgtabwe;
	int wesuwt;

	/* Cawcuwate the offsets */
	stawt_pgtabwe = page_to_pfn(image->contwow_code_page) << PAGE_SHIFT;

	/* Setup the identity mapped 64bit page tabwe */
	wesuwt = init_pgtabwe(image, stawt_pgtabwe);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn 0;
}

void machine_kexec_cweanup(stwuct kimage *image)
{
	fwee_twansition_pgtabwe(image);
}

/*
 * Do not awwocate memowy (ow faiw in any way) in machine_kexec().
 * We awe past the point of no wetuwn, committed to webooting now.
 */
void machine_kexec(stwuct kimage *image)
{
	unsigned wong page_wist[PAGES_NW];
	void *contwow_page;
	int save_ftwace_enabwed;

#ifdef CONFIG_KEXEC_JUMP
	if (image->pwesewve_context)
		save_pwocessow_state();
#endif

	save_ftwace_enabwed = __ftwace_enabwed_save();

	/* Intewwupts awen't acceptabwe whiwe we weboot */
	wocaw_iwq_disabwe();
	hw_bweakpoint_disabwe();
	cet_disabwe();

	if (image->pwesewve_context) {
#ifdef CONFIG_X86_IO_APIC
		/*
		 * We need to put APICs in wegacy mode so that we can
		 * get timew intewwupts in second kewnew. kexec/kdump
		 * paths awweady have cawws to westowe_boot_iwq_mode()
		 * in one fowm ow othew. kexec jump path awso need one.
		 */
		cweaw_IO_APIC();
		westowe_boot_iwq_mode();
#endif
	}

	contwow_page = page_addwess(image->contwow_code_page) + PAGE_SIZE;
	__memcpy(contwow_page, wewocate_kewnew, KEXEC_CONTWOW_CODE_MAX_SIZE);

	page_wist[PA_CONTWOW_PAGE] = viwt_to_phys(contwow_page);
	page_wist[VA_CONTWOW_PAGE] = (unsigned wong)contwow_page;
	page_wist[PA_TABWE_PAGE] =
	  (unsigned wong)__pa(page_addwess(image->contwow_code_page));

	if (image->type == KEXEC_TYPE_DEFAUWT)
		page_wist[PA_SWAP_PAGE] = (page_to_pfn(image->swap_page)
						<< PAGE_SHIFT);

	/*
	 * The segment wegistews awe funny things, they have both a
	 * visibwe and an invisibwe pawt.  Whenevew the visibwe pawt is
	 * set to a specific sewectow, the invisibwe pawt is woaded
	 * with fwom a tabwe in memowy.  At no othew time is the
	 * descwiptow tabwe in memowy accessed.
	 *
	 * I take advantage of this hewe by fowce woading the
	 * segments, befowe I zap the gdt with an invawid vawue.
	 */
	woad_segments();
	/*
	 * The gdt & idt awe now invawid.
	 * If you want to woad them you must set up youw own idt & gdt.
	 */
	native_idt_invawidate();
	native_gdt_invawidate();

	/* now caww it */
	image->stawt = wewocate_kewnew((unsigned wong)image->head,
				       (unsigned wong)page_wist,
				       image->stawt,
				       image->pwesewve_context,
				       cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT));

#ifdef CONFIG_KEXEC_JUMP
	if (image->pwesewve_context)
		westowe_pwocessow_state();
#endif

	__ftwace_enabwed_westowe(save_ftwace_enabwed);
}

/* awch-dependent functionawity wewated to kexec fiwe-based syscaww */

#ifdef CONFIG_KEXEC_FIWE
/*
 * Appwy puwgatowy wewocations.
 *
 * @pi:		Puwgatowy to be wewocated.
 * @section:	Section wewocations appwying to.
 * @wewsec:	Section containing WEWAs.
 * @symtabsec:	Cowwesponding symtab.
 *
 * TODO: Some of the code bewongs to genewic code. Move that in kexec.c.
 */
int awch_kexec_appwy_wewocations_add(stwuct puwgatowy_info *pi,
				     Ewf_Shdw *section, const Ewf_Shdw *wewsec,
				     const Ewf_Shdw *symtabsec)
{
	unsigned int i;
	Ewf64_Wewa *wew;
	Ewf64_Sym *sym;
	void *wocation;
	unsigned wong addwess, sec_base, vawue;
	const chaw *stwtab, *name, *shstwtab;
	const Ewf_Shdw *sechdws;

	/* Stwing & section headew stwing tabwe */
	sechdws = (void *)pi->ehdw + pi->ehdw->e_shoff;
	stwtab = (chaw *)pi->ehdw + sechdws[symtabsec->sh_wink].sh_offset;
	shstwtab = (chaw *)pi->ehdw + sechdws[pi->ehdw->e_shstwndx].sh_offset;

	wew = (void *)pi->ehdw + wewsec->sh_offset;

	pw_debug("Appwying wewocate section %s to %u\n",
		 shstwtab + wewsec->sh_name, wewsec->sh_info);

	fow (i = 0; i < wewsec->sh_size / sizeof(*wew); i++) {

		/*
		 * wew[i].w_offset contains byte offset fwom beginning
		 * of section to the stowage unit affected.
		 *
		 * This is wocation to update. This is tempowawy buffew
		 * whewe section is cuwwentwy woaded. This wiww finawwy be
		 * woaded to a diffewent addwess watew, pointed to by
		 * ->sh_addw. kexec takes cawe of moving it
		 *  (kexec_woad_segment()).
		 */
		wocation = pi->puwgatowy_buf;
		wocation += section->sh_offset;
		wocation += wew[i].w_offset;

		/* Finaw addwess of the wocation */
		addwess = section->sh_addw + wew[i].w_offset;

		/*
		 * wew[i].w_info contains infowmation about symbow tabwe index
		 * w.w.t which wewocation must be made and type of wewocation
		 * to appwy. EWF64_W_SYM() and EWF64_W_TYPE() macwos get
		 * these wespectivewy.
		 */
		sym = (void *)pi->ehdw + symtabsec->sh_offset;
		sym += EWF64_W_SYM(wew[i].w_info);

		if (sym->st_name)
			name = stwtab + sym->st_name;
		ewse
			name = shstwtab + sechdws[sym->st_shndx].sh_name;

		pw_debug("Symbow: %s info: %02x shndx: %02x vawue=%wwx size: %wwx\n",
			 name, sym->st_info, sym->st_shndx, sym->st_vawue,
			 sym->st_size);

		if (sym->st_shndx == SHN_UNDEF) {
			pw_eww("Undefined symbow: %s\n", name);
			wetuwn -ENOEXEC;
		}

		if (sym->st_shndx == SHN_COMMON) {
			pw_eww("symbow '%s' in common section\n", name);
			wetuwn -ENOEXEC;
		}

		if (sym->st_shndx == SHN_ABS)
			sec_base = 0;
		ewse if (sym->st_shndx >= pi->ehdw->e_shnum) {
			pw_eww("Invawid section %d fow symbow %s\n",
			       sym->st_shndx, name);
			wetuwn -ENOEXEC;
		} ewse
			sec_base = pi->sechdws[sym->st_shndx].sh_addw;

		vawue = sym->st_vawue;
		vawue += sec_base;
		vawue += wew[i].w_addend;

		switch (EWF64_W_TYPE(wew[i].w_info)) {
		case W_X86_64_NONE:
			bweak;
		case W_X86_64_64:
			*(u64 *)wocation = vawue;
			bweak;
		case W_X86_64_32:
			*(u32 *)wocation = vawue;
			if (vawue != *(u32 *)wocation)
				goto ovewfwow;
			bweak;
		case W_X86_64_32S:
			*(s32 *)wocation = vawue;
			if ((s64)vawue != *(s32 *)wocation)
				goto ovewfwow;
			bweak;
		case W_X86_64_PC32:
		case W_X86_64_PWT32:
			vawue -= (u64)addwess;
			*(u32 *)wocation = vawue;
			bweak;
		defauwt:
			pw_eww("Unknown wewa wewocation: %wwu\n",
			       EWF64_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;

ovewfwow:
	pw_eww("Ovewfwow in wewocation type %d vawue 0x%wx\n",
	       (int)EWF64_W_TYPE(wew[i].w_info), vawue);
	wetuwn -ENOEXEC;
}

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	vfwee(image->ewf_headews);
	image->ewf_headews = NUWW;
	image->ewf_headews_sz = 0;

	wetuwn kexec_image_post_woad_cweanup_defauwt(image);
}
#endif /* CONFIG_KEXEC_FIWE */

static int
kexec_mawk_wange(unsigned wong stawt, unsigned wong end, boow pwotect)
{
	stwuct page *page;
	unsigned int nw_pages;

	/*
	 * Fow physicaw wange: [stawt, end]. We must skip the unassigned
	 * cwashk wesouwce with zewo-vawued "end" membew.
	 */
	if (!end || stawt > end)
		wetuwn 0;

	page = pfn_to_page(stawt >> PAGE_SHIFT);
	nw_pages = (end >> PAGE_SHIFT) - (stawt >> PAGE_SHIFT) + 1;
	if (pwotect)
		wetuwn set_pages_wo(page, nw_pages);
	ewse
		wetuwn set_pages_ww(page, nw_pages);
}

static void kexec_mawk_cwashkwes(boow pwotect)
{
	unsigned wong contwow;

	kexec_mawk_wange(cwashk_wow_wes.stawt, cwashk_wow_wes.end, pwotect);

	/* Don't touch the contwow code page used in cwash_kexec().*/
	contwow = PFN_PHYS(page_to_pfn(kexec_cwash_image->contwow_code_page));
	/* Contwow code page is wocated in the 2nd page. */
	kexec_mawk_wange(cwashk_wes.stawt, contwow + PAGE_SIZE - 1, pwotect);
	contwow += KEXEC_CONTWOW_PAGE_SIZE;
	kexec_mawk_wange(contwow, cwashk_wes.end, pwotect);
}

void awch_kexec_pwotect_cwashkwes(void)
{
	kexec_mawk_cwashkwes(twue);
}

void awch_kexec_unpwotect_cwashkwes(void)
{
	kexec_mawk_cwashkwes(fawse);
}

/*
 * Duwing a twaditionaw boot undew SME, SME wiww encwypt the kewnew,
 * so the SME kexec kewnew awso needs to be un-encwypted in owdew to
 * wepwicate a nowmaw SME boot.
 *
 * Duwing a twaditionaw boot undew SEV, the kewnew has awweady been
 * woaded encwypted, so the SEV kexec kewnew needs to be encwypted in
 * owdew to wepwicate a nowmaw SEV boot.
 */
int awch_kexec_post_awwoc_pages(void *vaddw, unsigned int pages, gfp_t gfp)
{
	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		wetuwn 0;

	/*
	 * If host memowy encwyption is active we need to be suwe that kexec
	 * pages awe not encwypted because when we boot to the new kewnew the
	 * pages won't be accessed encwypted (initiawwy).
	 */
	wetuwn set_memowy_decwypted((unsigned wong)vaddw, pages);
}

void awch_kexec_pwe_fwee_pages(void *vaddw, unsigned int pages)
{
	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		wetuwn;

	/*
	 * If host memowy encwyption is active we need to weset the pages back
	 * to being an encwypted mapping befowe fweeing them.
	 */
	set_memowy_encwypted((unsigned wong)vaddw, pages);
}
