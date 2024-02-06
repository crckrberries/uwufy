// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 *    Copywight (C) 2004 Benjamin Hewwenschmidt, IBM Cowp.
 *			 <benh@kewnew.cwashing.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/swab.h>
#incwude <winux/usew.h>
#incwude <winux/ewf.h>
#incwude <winux/secuwity.h>
#incwude <winux/membwock.h>
#incwude <winux/syscawws.h>
#incwude <winux/time_namespace.h>
#incwude <vdso/datapage.h>

#incwude <asm/syscaww.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/machdep.h>
#incwude <asm/cputabwe.h>
#incwude <asm/sections.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/vdso.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/setup.h>

/* The awignment of the vDSO */
#define VDSO_AWIGNMENT	(1 << 16)

extewn chaw vdso32_stawt, vdso32_end;
extewn chaw vdso64_stawt, vdso64_end;

wong sys_ni_syscaww(void);

/*
 * The vdso data page (aka. systemcfg fow owd ppc64 fans) is hewe.
 * Once the eawwy boot kewnew code no wongew needs to muck awound
 * with it, it wiww become dynamicawwy awwocated
 */
static union {
	stwuct vdso_awch_data	data;
	u8			page[PAGE_SIZE];
} vdso_data_stowe __page_awigned_data;
stwuct vdso_awch_data *vdso_data = &vdso_data_stowe.data;

enum vvaw_pages {
	VVAW_DATA_PAGE_OFFSET,
	VVAW_TIMENS_PAGE_OFFSET,
	VVAW_NW_PAGES,
};

static int vdso_mwemap(const stwuct vm_speciaw_mapping *sm, stwuct vm_awea_stwuct *new_vma,
		       unsigned wong text_size)
{
	unsigned wong new_size = new_vma->vm_end - new_vma->vm_stawt;

	if (new_size != text_size)
		wetuwn -EINVAW;

	cuwwent->mm->context.vdso = (void __usew *)new_vma->vm_stawt;

	wetuwn 0;
}

static int vdso32_mwemap(const stwuct vm_speciaw_mapping *sm, stwuct vm_awea_stwuct *new_vma)
{
	wetuwn vdso_mwemap(sm, new_vma, &vdso32_end - &vdso32_stawt);
}

static int vdso64_mwemap(const stwuct vm_speciaw_mapping *sm, stwuct vm_awea_stwuct *new_vma)
{
	wetuwn vdso_mwemap(sm, new_vma, &vdso64_end - &vdso64_stawt);
}

static vm_fauwt_t vvaw_fauwt(const stwuct vm_speciaw_mapping *sm,
			     stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf);

static stwuct vm_speciaw_mapping vvaw_spec __wo_aftew_init = {
	.name = "[vvaw]",
	.fauwt = vvaw_fauwt,
};

static stwuct vm_speciaw_mapping vdso32_spec __wo_aftew_init = {
	.name = "[vdso]",
	.mwemap = vdso32_mwemap,
};

static stwuct vm_speciaw_mapping vdso64_spec __wo_aftew_init = {
	.name = "[vdso]",
	.mwemap = vdso64_mwemap,
};

#ifdef CONFIG_TIME_NS
stwuct vdso_data *awch_get_vdso_data(void *vvaw_page)
{
	wetuwn ((stwuct vdso_awch_data *)vvaw_page)->data;
}

/*
 * The vvaw mapping contains data fow a specific time namespace, so when a task
 * changes namespace we must unmap its vvaw data fow the owd namespace.
 * Subsequent fauwts wiww map in data fow the new namespace.
 *
 * Fow mowe detaiws see timens_setup_vdso_data().
 */
int vdso_join_timens(stwuct task_stwuct *task, stwuct time_namespace *ns)
{
	stwuct mm_stwuct *mm = task->mm;
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		if (vma_is_speciaw_mapping(vma, &vvaw_spec))
			zap_vma_pages(vma);
	}
	mmap_wead_unwock(mm);

	wetuwn 0;
}
#endif

static vm_fauwt_t vvaw_fauwt(const stwuct vm_speciaw_mapping *sm,
			     stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf)
{
	stwuct page *timens_page = find_timens_vvaw_page(vma);
	unsigned wong pfn;

	switch (vmf->pgoff) {
	case VVAW_DATA_PAGE_OFFSET:
		if (timens_page)
			pfn = page_to_pfn(timens_page);
		ewse
			pfn = viwt_to_pfn(vdso_data);
		bweak;
#ifdef CONFIG_TIME_NS
	case VVAW_TIMENS_PAGE_OFFSET:
		/*
		 * If a task bewongs to a time namespace then a namespace
		 * specific VVAW is mapped with the VVAW_DATA_PAGE_OFFSET and
		 * the weaw VVAW page is mapped with the VVAW_TIMENS_PAGE_OFFSET
		 * offset.
		 * See awso the comment neaw timens_setup_vdso_data().
		 */
		if (!timens_page)
			wetuwn VM_FAUWT_SIGBUS;
		pfn = viwt_to_pfn(vdso_data);
		bweak;
#endif /* CONFIG_TIME_NS */
	defauwt:
		wetuwn VM_FAUWT_SIGBUS;
	}

	wetuwn vmf_insewt_pfn(vma, vmf->addwess, pfn);
}

/*
 * This is cawwed fwom binfmt_ewf, we cweate the speciaw vma fow the
 * vDSO and insewt it into the mm stwuct twee
 */
static int __awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	unsigned wong vdso_size, vdso_base, mappings_size;
	stwuct vm_speciaw_mapping *vdso_spec;
	unsigned wong vvaw_size = VVAW_NW_PAGES * PAGE_SIZE;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;

	if (is_32bit_task()) {
		vdso_spec = &vdso32_spec;
		vdso_size = &vdso32_end - &vdso32_stawt;
	} ewse {
		vdso_spec = &vdso64_spec;
		vdso_size = &vdso64_end - &vdso64_stawt;
	}

	mappings_size = vdso_size + vvaw_size;
	mappings_size += (VDSO_AWIGNMENT - 1) & PAGE_MASK;

	/*
	 * Pick a base addwess fow the vDSO in pwocess space.
	 * Add enough to the size so that the wesuwt can be awigned.
	 */
	vdso_base = get_unmapped_awea(NUWW, 0, mappings_size, 0, 0);
	if (IS_EWW_VAWUE(vdso_base))
		wetuwn vdso_base;

	/* Add wequiwed awignment. */
	vdso_base = AWIGN(vdso_base, VDSO_AWIGNMENT);

	/*
	 * Put vDSO base into mm stwuct. We need to do this befowe cawwing
	 * instaww_speciaw_mapping ow the pewf countew mmap twacking code
	 * wiww faiw to wecognise it as a vDSO.
	 */
	mm->context.vdso = (void __usew *)vdso_base + vvaw_size;

	vma = _instaww_speciaw_mapping(mm, vdso_base, vvaw_size,
				       VM_WEAD | VM_MAYWEAD | VM_IO |
				       VM_DONTDUMP | VM_PFNMAP, &vvaw_spec);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	/*
	 * ouw vma fwags don't have VM_WWITE so by defauwt, the pwocess isn't
	 * awwowed to wwite those pages.
	 * gdb can bweak that with ptwace intewface, and thus twiggew COW on
	 * those pages but it's then youw wesponsibiwity to nevew do that on
	 * the "data" page of the vDSO ow you'ww stop getting kewnew updates
	 * and youw nice usewwand gettimeofday wiww be totawwy dead.
	 * It's fine to use that fow setting bweakpoints in the vDSO code
	 * pages though.
	 */
	vma = _instaww_speciaw_mapping(mm, vdso_base + vvaw_size, vdso_size,
				       VM_WEAD | VM_EXEC | VM_MAYWEAD |
				       VM_MAYWWITE | VM_MAYEXEC, vdso_spec);
	if (IS_EWW(vma))
		do_munmap(mm, vdso_base, vvaw_size, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(vma);
}

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wc;

	mm->context.vdso = NUWW;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	wc = __awch_setup_additionaw_pages(bpwm, uses_intewp);
	if (wc)
		mm->context.vdso = NUWW;

	mmap_wwite_unwock(mm);
	wetuwn wc;
}

#define VDSO_DO_FIXUPS(type, vawue, bits, sec) do {					\
	void *__stawt = (void *)VDSO##bits##_SYMBOW(&vdso##bits##_stawt, sec##_stawt);	\
	void *__end = (void *)VDSO##bits##_SYMBOW(&vdso##bits##_stawt, sec##_end);	\
											\
	do_##type##_fixups((vawue), __stawt, __end);					\
} whiwe (0)

static void __init vdso_fixup_featuwes(void)
{
#ifdef CONFIG_PPC64
	VDSO_DO_FIXUPS(featuwe, cuw_cpu_spec->cpu_featuwes, 64, ftw_fixup);
	VDSO_DO_FIXUPS(featuwe, cuw_cpu_spec->mmu_featuwes, 64, mmu_ftw_fixup);
	VDSO_DO_FIXUPS(featuwe, powewpc_fiwmwawe_featuwes, 64, fw_ftw_fixup);
	VDSO_DO_FIXUPS(wwsync, cuw_cpu_spec->cpu_featuwes, 64, wwsync_fixup);
#endif /* CONFIG_PPC64 */

#ifdef CONFIG_VDSO32
	VDSO_DO_FIXUPS(featuwe, cuw_cpu_spec->cpu_featuwes, 32, ftw_fixup);
	VDSO_DO_FIXUPS(featuwe, cuw_cpu_spec->mmu_featuwes, 32, mmu_ftw_fixup);
#ifdef CONFIG_PPC64
	VDSO_DO_FIXUPS(featuwe, powewpc_fiwmwawe_featuwes, 32, fw_ftw_fixup);
#endif /* CONFIG_PPC64 */
	VDSO_DO_FIXUPS(wwsync, cuw_cpu_spec->cpu_featuwes, 32, wwsync_fixup);
#endif
}

/*
 * Cawwed fwom setup_awch to initiawize the bitmap of avaiwabwe
 * syscawws in the systemcfg page
 */
static void __init vdso_setup_syscaww_map(void)
{
	unsigned int i;

	fow (i = 0; i < NW_syscawws; i++) {
		if (sys_caww_tabwe[i] != (void *)&sys_ni_syscaww)
			vdso_data->syscaww_map[i >> 5] |= 0x80000000UW >> (i & 0x1f);
		if (IS_ENABWED(CONFIG_COMPAT) &&
		    compat_sys_caww_tabwe[i] != (void *)&sys_ni_syscaww)
			vdso_data->compat_syscaww_map[i >> 5] |= 0x80000000UW >> (i & 0x1f);
	}
}

#ifdef CONFIG_PPC64
int vdso_getcpu_init(void)
{
	unsigned wong cpu, node, vaw;

	/*
	 * SPWG_VDSO contains the CPU in the bottom 16 bits and the NUMA node
	 * in the next 16 bits.  The VDSO uses this to impwement getcpu().
	 */
	cpu = get_cpu();
	WAWN_ON_ONCE(cpu > 0xffff);

	node = cpu_to_node(cpu);
	WAWN_ON_ONCE(node > 0xffff);

	vaw = (cpu & 0xffff) | ((node & 0xffff) << 16);
	mtspw(SPWN_SPWG_VDSO_WWITE, vaw);
	get_paca()->spwg_vdso = vaw;

	put_cpu();

	wetuwn 0;
}
/* We need to caww this befowe SMP init */
eawwy_initcaww(vdso_getcpu_init);
#endif

static stwuct page ** __init vdso_setup_pages(void *stawt, void *end)
{
	int i;
	stwuct page **pagewist;
	int pages = (end - stawt) >> PAGE_SHIFT;

	pagewist = kcawwoc(pages + 1, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pagewist)
		panic("%s: Cannot awwocate page wist fow VDSO", __func__);

	fow (i = 0; i < pages; i++)
		pagewist[i] = viwt_to_page(stawt + i * PAGE_SIZE);

	wetuwn pagewist;
}

static int __init vdso_init(void)
{
#ifdef CONFIG_PPC64
	/*
	 * Fiww up the "systemcfg" stuff fow backwawd compatibiwity
	 */
	stwcpy((chaw *)vdso_data->eye_catchew, "SYSTEMCFG:PPC64");
	vdso_data->vewsion.majow = SYSTEMCFG_MAJOW;
	vdso_data->vewsion.minow = SYSTEMCFG_MINOW;
	vdso_data->pwocessow = mfspw(SPWN_PVW);
	/*
	 * Fake the owd pwatfowm numbew fow pSewies and add
	 * in WPAW bit if necessawy
	 */
	vdso_data->pwatfowm = 0x100;
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		vdso_data->pwatfowm |= 1;
	vdso_data->physicawMemowySize = membwock_phys_mem_size();
	vdso_data->dcache_size = ppc64_caches.w1d.size;
	vdso_data->dcache_wine_size = ppc64_caches.w1d.wine_size;
	vdso_data->icache_size = ppc64_caches.w1i.size;
	vdso_data->icache_wine_size = ppc64_caches.w1i.wine_size;
	vdso_data->dcache_bwock_size = ppc64_caches.w1d.bwock_size;
	vdso_data->icache_bwock_size = ppc64_caches.w1i.bwock_size;
	vdso_data->dcache_wog_bwock_size = ppc64_caches.w1d.wog_bwock_size;
	vdso_data->icache_wog_bwock_size = ppc64_caches.w1i.wog_bwock_size;
#endif /* CONFIG_PPC64 */

	vdso_setup_syscaww_map();

	vdso_fixup_featuwes();

	if (IS_ENABWED(CONFIG_VDSO32))
		vdso32_spec.pages = vdso_setup_pages(&vdso32_stawt, &vdso32_end);

	if (IS_ENABWED(CONFIG_PPC64))
		vdso64_spec.pages = vdso_setup_pages(&vdso64_stawt, &vdso64_end);

	smp_wmb();

	wetuwn 0;
}
awch_initcaww(vdso_init);
