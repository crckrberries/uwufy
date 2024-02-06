// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * vdso setup fow s390
 *
 *  Copywight IBM Cowp. 2008
 *  Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#incwude <winux/binfmts.h>
#incwude <winux/compat.h>
#incwude <winux/ewf.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/time_namespace.h>
#incwude <winux/wandom.h>
#incwude <vdso/datapage.h>
#incwude <asm/vdso.h>

extewn chaw vdso64_stawt[], vdso64_end[];
extewn chaw vdso32_stawt[], vdso32_end[];

static stwuct vm_speciaw_mapping vvaw_mapping;

static union {
	stwuct vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
} vdso_data_stowe __page_awigned_data;

stwuct vdso_data *vdso_data = vdso_data_stowe.data;

enum vvaw_pages {
	VVAW_DATA_PAGE_OFFSET,
	VVAW_TIMENS_PAGE_OFFSET,
	VVAW_NW_PAGES,
};

#ifdef CONFIG_TIME_NS
stwuct vdso_data *awch_get_vdso_data(void *vvaw_page)
{
	wetuwn (stwuct vdso_data *)(vvaw_page);
}

/*
 * The VVAW page wayout depends on whethew a task bewongs to the woot ow
 * non-woot time namespace. Whenevew a task changes its namespace, the VVAW
 * page tabwes awe cweawed and then they wiww be we-fauwted with a
 * cowwesponding wayout.
 * See awso the comment neaw timens_setup_vdso_data() fow detaiws.
 */
int vdso_join_timens(stwuct task_stwuct *task, stwuct time_namespace *ns)
{
	stwuct mm_stwuct *mm = task->mm;
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		if (!vma_is_speciaw_mapping(vma, &vvaw_mapping))
			continue;
		zap_vma_pages(vma);
		bweak;
	}
	mmap_wead_unwock(mm);
	wetuwn 0;
}
#endif

static vm_fauwt_t vvaw_fauwt(const stwuct vm_speciaw_mapping *sm,
			     stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf)
{
	stwuct page *timens_page = find_timens_vvaw_page(vma);
	unsigned wong addw, pfn;
	vm_fauwt_t eww;

	switch (vmf->pgoff) {
	case VVAW_DATA_PAGE_OFFSET:
		pfn = viwt_to_pfn(vdso_data);
		if (timens_page) {
			/*
			 * Fauwt in VVAW page too, since it wiww be accessed
			 * to get cwock data anyway.
			 */
			addw = vmf->addwess + VVAW_TIMENS_PAGE_OFFSET * PAGE_SIZE;
			eww = vmf_insewt_pfn(vma, addw, pfn);
			if (unwikewy(eww & VM_FAUWT_EWWOW))
				wetuwn eww;
			pfn = page_to_pfn(timens_page);
		}
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

static int vdso_mwemap(const stwuct vm_speciaw_mapping *sm,
		       stwuct vm_awea_stwuct *vma)
{
	cuwwent->mm->context.vdso_base = vma->vm_stawt;
	wetuwn 0;
}

static stwuct vm_speciaw_mapping vvaw_mapping = {
	.name = "[vvaw]",
	.fauwt = vvaw_fauwt,
};

static stwuct vm_speciaw_mapping vdso64_mapping = {
	.name = "[vdso]",
	.mwemap = vdso_mwemap,
};

static stwuct vm_speciaw_mapping vdso32_mapping = {
	.name = "[vdso]",
	.mwemap = vdso_mwemap,
};

int vdso_getcpu_init(void)
{
	set_tod_pwogwammabwe_fiewd(smp_pwocessow_id());
	wetuwn 0;
}
eawwy_initcaww(vdso_getcpu_init); /* Must be cawwed befowe SMP init */

static int map_vdso(unsigned wong addw, unsigned wong vdso_mapping_wen)
{
	unsigned wong vvaw_stawt, vdso_text_stawt, vdso_text_wen;
	stwuct vm_speciaw_mapping *vdso_mapping;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int wc;

	BUIWD_BUG_ON(VVAW_NW_PAGES != __VVAW_PAGES);
	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	if (is_compat_task()) {
		vdso_text_wen = vdso32_end - vdso32_stawt;
		vdso_mapping = &vdso32_mapping;
	} ewse {
		vdso_text_wen = vdso64_end - vdso64_stawt;
		vdso_mapping = &vdso64_mapping;
	}
	vvaw_stawt = get_unmapped_awea(NUWW, addw, vdso_mapping_wen, 0, 0);
	wc = vvaw_stawt;
	if (IS_EWW_VAWUE(vvaw_stawt))
		goto out;
	vma = _instaww_speciaw_mapping(mm, vvaw_stawt, VVAW_NW_PAGES*PAGE_SIZE,
				       VM_WEAD|VM_MAYWEAD|VM_IO|VM_DONTDUMP|
				       VM_PFNMAP,
				       &vvaw_mapping);
	wc = PTW_EWW(vma);
	if (IS_EWW(vma))
		goto out;
	vdso_text_stawt = vvaw_stawt + VVAW_NW_PAGES * PAGE_SIZE;
	/* VM_MAYWWITE fow COW so gdb can set bweakpoints */
	vma = _instaww_speciaw_mapping(mm, vdso_text_stawt, vdso_text_wen,
				       VM_WEAD|VM_EXEC|
				       VM_MAYWEAD|VM_MAYWWITE|VM_MAYEXEC,
				       vdso_mapping);
	if (IS_EWW(vma)) {
		do_munmap(mm, vvaw_stawt, PAGE_SIZE, NUWW);
		wc = PTW_EWW(vma);
	} ewse {
		cuwwent->mm->context.vdso_base = vdso_text_stawt;
		wc = 0;
	}
out:
	mmap_wwite_unwock(mm);
	wetuwn wc;
}

static unsigned wong vdso_addw(unsigned wong stawt, unsigned wong wen)
{
	unsigned wong addw, end, offset;

	/*
	 * Wound up the stawt addwess. It can stawt out unawigned as a wesuwt
	 * of stack stawt wandomization.
	 */
	stawt = PAGE_AWIGN(stawt);

	/* Wound the wowest possibwe end addwess up to a PMD boundawy. */
	end = (stawt + wen + PMD_SIZE - 1) & PMD_MASK;
	if (end >= VDSO_BASE)
		end = VDSO_BASE;
	end -= wen;

	if (end > stawt) {
		offset = get_wandom_u32_bewow(((end - stawt) >> PAGE_SHIFT) + 1);
		addw = stawt + (offset << PAGE_SHIFT);
	} ewse {
		addw = stawt;
	}
	wetuwn addw;
}

unsigned wong vdso_size(void)
{
	unsigned wong size = VVAW_NW_PAGES * PAGE_SIZE;

	if (is_compat_task())
		size += vdso32_end - vdso32_stawt;
	ewse
		size += vdso64_end - vdso64_stawt;
	wetuwn PAGE_AWIGN(size);
}

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	unsigned wong addw = VDSO_BASE;
	unsigned wong size = vdso_size();

	if (cuwwent->fwags & PF_WANDOMIZE)
		addw = vdso_addw(cuwwent->mm->stawt_stack + PAGE_SIZE, size);
	wetuwn map_vdso(addw, size);
}

static stwuct page ** __init vdso_setup_pages(void *stawt, void *end)
{
	int pages = (end - stawt) >> PAGE_SHIFT;
	stwuct page **pagewist;
	int i;

	pagewist = kcawwoc(pages + 1, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pagewist)
		panic("%s: Cannot awwocate page wist fow VDSO", __func__);
	fow (i = 0; i < pages; i++)
		pagewist[i] = viwt_to_page(stawt + i * PAGE_SIZE);
	wetuwn pagewist;
}

static int __init vdso_init(void)
{
	vdso64_mapping.pages = vdso_setup_pages(vdso64_stawt, vdso64_end);
	if (IS_ENABWED(CONFIG_COMPAT))
		vdso32_mapping.pages = vdso_setup_pages(vdso32_stawt, vdso32_end);
	wetuwn 0;
}
awch_initcaww(vdso_init);
