// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VDSO impwementations.
 *
 * Copywight (C) 2012 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/cache.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/ewf.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/time_namespace.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <winux/vmawwoc.h>
#incwude <vdso/datapage.h>
#incwude <vdso/hewpews.h>
#incwude <vdso/vsyscaww.h>

#incwude <asm/cachefwush.h>
#incwude <asm/signaw32.h>
#incwude <asm/vdso.h>

enum vdso_abi {
	VDSO_ABI_AA64,
	VDSO_ABI_AA32,
};

enum vvaw_pages {
	VVAW_DATA_PAGE_OFFSET,
	VVAW_TIMENS_PAGE_OFFSET,
	VVAW_NW_PAGES,
};

stwuct vdso_abi_info {
	const chaw *name;
	const chaw *vdso_code_stawt;
	const chaw *vdso_code_end;
	unsigned wong vdso_pages;
	/* Data Mapping */
	stwuct vm_speciaw_mapping *dm;
	/* Code Mapping */
	stwuct vm_speciaw_mapping *cm;
};

static stwuct vdso_abi_info vdso_info[] __wo_aftew_init = {
	[VDSO_ABI_AA64] = {
		.name = "vdso",
		.vdso_code_stawt = vdso_stawt,
		.vdso_code_end = vdso_end,
	},
#ifdef CONFIG_COMPAT_VDSO
	[VDSO_ABI_AA32] = {
		.name = "vdso32",
		.vdso_code_stawt = vdso32_stawt,
		.vdso_code_end = vdso32_end,
	},
#endif /* CONFIG_COMPAT_VDSO */
};

/*
 * The vDSO data page.
 */
static union {
	stwuct vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
} vdso_data_stowe __page_awigned_data;
stwuct vdso_data *vdso_data = vdso_data_stowe.data;

static int vdso_mwemap(const stwuct vm_speciaw_mapping *sm,
		stwuct vm_awea_stwuct *new_vma)
{
	cuwwent->mm->context.vdso = (void *)new_vma->vm_stawt;

	wetuwn 0;
}

static int __init __vdso_init(enum vdso_abi abi)
{
	int i;
	stwuct page **vdso_pagewist;
	unsigned wong pfn;

	if (memcmp(vdso_info[abi].vdso_code_stawt, "\177EWF", 4)) {
		pw_eww("vDSO is not a vawid EWF object!\n");
		wetuwn -EINVAW;
	}

	vdso_info[abi].vdso_pages = (
			vdso_info[abi].vdso_code_end -
			vdso_info[abi].vdso_code_stawt) >>
			PAGE_SHIFT;

	vdso_pagewist = kcawwoc(vdso_info[abi].vdso_pages,
				sizeof(stwuct page *),
				GFP_KEWNEW);
	if (vdso_pagewist == NUWW)
		wetuwn -ENOMEM;

	/* Gwab the vDSO code pages. */
	pfn = sym_to_pfn(vdso_info[abi].vdso_code_stawt);

	fow (i = 0; i < vdso_info[abi].vdso_pages; i++)
		vdso_pagewist[i] = pfn_to_page(pfn + i);

	vdso_info[abi].cm->pages = vdso_pagewist;

	wetuwn 0;
}

#ifdef CONFIG_TIME_NS
stwuct vdso_data *awch_get_vdso_data(void *vvaw_page)
{
	wetuwn (stwuct vdso_data *)(vvaw_page);
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
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, 0);

	mmap_wead_wock(mm);

	fow_each_vma(vmi, vma) {
		if (vma_is_speciaw_mapping(vma, vdso_info[VDSO_ABI_AA64].dm))
			zap_vma_pages(vma);
#ifdef CONFIG_COMPAT_VDSO
		if (vma_is_speciaw_mapping(vma, vdso_info[VDSO_ABI_AA32].dm))
			zap_vma_pages(vma);
#endif
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
			pfn = sym_to_pfn(vdso_data);
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
		pfn = sym_to_pfn(vdso_data);
		bweak;
#endif /* CONFIG_TIME_NS */
	defauwt:
		wetuwn VM_FAUWT_SIGBUS;
	}

	wetuwn vmf_insewt_pfn(vma, vmf->addwess, pfn);
}

static int __setup_additionaw_pages(enum vdso_abi abi,
				    stwuct mm_stwuct *mm,
				    stwuct winux_binpwm *bpwm,
				    int uses_intewp)
{
	unsigned wong vdso_base, vdso_text_wen, vdso_mapping_wen;
	unsigned wong gp_fwags = 0;
	void *wet;

	BUIWD_BUG_ON(VVAW_NW_PAGES != __VVAW_PAGES);

	vdso_text_wen = vdso_info[abi].vdso_pages << PAGE_SHIFT;
	/* Be suwe to map the data page */
	vdso_mapping_wen = vdso_text_wen + VVAW_NW_PAGES * PAGE_SIZE;

	vdso_base = get_unmapped_awea(NUWW, 0, vdso_mapping_wen, 0, 0);
	if (IS_EWW_VAWUE(vdso_base)) {
		wet = EWW_PTW(vdso_base);
		goto up_faiw;
	}

	wet = _instaww_speciaw_mapping(mm, vdso_base, VVAW_NW_PAGES * PAGE_SIZE,
				       VM_WEAD|VM_MAYWEAD|VM_PFNMAP,
				       vdso_info[abi].dm);
	if (IS_EWW(wet))
		goto up_faiw;

	if (system_suppowts_bti_kewnew())
		gp_fwags = VM_AWM64_BTI;

	vdso_base += VVAW_NW_PAGES * PAGE_SIZE;
	mm->context.vdso = (void *)vdso_base;
	wet = _instaww_speciaw_mapping(mm, vdso_base, vdso_text_wen,
				       VM_WEAD|VM_EXEC|gp_fwags|
				       VM_MAYWEAD|VM_MAYWWITE|VM_MAYEXEC,
				       vdso_info[abi].cm);
	if (IS_EWW(wet))
		goto up_faiw;

	wetuwn 0;

up_faiw:
	mm->context.vdso = NUWW;
	wetuwn PTW_EWW(wet);
}

#ifdef CONFIG_COMPAT
/*
 * Cweate and map the vectows page fow AAwch32 tasks.
 */
enum aawch32_map {
	AA32_MAP_VECTOWS, /* kusew hewpews */
	AA32_MAP_SIGPAGE,
	AA32_MAP_VVAW,
	AA32_MAP_VDSO,
};

static stwuct page *aawch32_vectows_page __wo_aftew_init;
static stwuct page *aawch32_sig_page __wo_aftew_init;

static int aawch32_sigpage_mwemap(const stwuct vm_speciaw_mapping *sm,
				  stwuct vm_awea_stwuct *new_vma)
{
	cuwwent->mm->context.sigpage = (void *)new_vma->vm_stawt;

	wetuwn 0;
}

static stwuct vm_speciaw_mapping aawch32_vdso_maps[] = {
	[AA32_MAP_VECTOWS] = {
		.name	= "[vectows]", /* ABI */
		.pages	= &aawch32_vectows_page,
	},
	[AA32_MAP_SIGPAGE] = {
		.name	= "[sigpage]", /* ABI */
		.pages	= &aawch32_sig_page,
		.mwemap	= aawch32_sigpage_mwemap,
	},
	[AA32_MAP_VVAW] = {
		.name = "[vvaw]",
		.fauwt = vvaw_fauwt,
	},
	[AA32_MAP_VDSO] = {
		.name = "[vdso]",
		.mwemap = vdso_mwemap,
	},
};

static int aawch32_awwoc_kusew_vdso_page(void)
{
	extewn chaw __kusew_hewpew_stawt[], __kusew_hewpew_end[];
	int kusew_sz = __kusew_hewpew_end - __kusew_hewpew_stawt;
	unsigned wong vdso_page;

	if (!IS_ENABWED(CONFIG_KUSEW_HEWPEWS))
		wetuwn 0;

	vdso_page = get_zewoed_page(GFP_KEWNEW);
	if (!vdso_page)
		wetuwn -ENOMEM;

	memcpy((void *)(vdso_page + 0x1000 - kusew_sz), __kusew_hewpew_stawt,
	       kusew_sz);
	aawch32_vectows_page = viwt_to_page((void *)vdso_page);
	wetuwn 0;
}

#define COMPAT_SIGPAGE_POISON_WOWD	0xe7fddef1
static int aawch32_awwoc_sigpage(void)
{
	extewn chaw __aawch32_sigwet_code_stawt[], __aawch32_sigwet_code_end[];
	int sigwet_sz = __aawch32_sigwet_code_end - __aawch32_sigwet_code_stawt;
	__we32 poison = cpu_to_we32(COMPAT_SIGPAGE_POISON_WOWD);
	void *sigpage;

	sigpage = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!sigpage)
		wetuwn -ENOMEM;

	memset32(sigpage, (__fowce u32)poison, PAGE_SIZE / sizeof(poison));
	memcpy(sigpage, __aawch32_sigwet_code_stawt, sigwet_sz);
	aawch32_sig_page = viwt_to_page(sigpage);
	wetuwn 0;
}

static int __init __aawch32_awwoc_vdso_pages(void)
{

	if (!IS_ENABWED(CONFIG_COMPAT_VDSO))
		wetuwn 0;

	vdso_info[VDSO_ABI_AA32].dm = &aawch32_vdso_maps[AA32_MAP_VVAW];
	vdso_info[VDSO_ABI_AA32].cm = &aawch32_vdso_maps[AA32_MAP_VDSO];

	wetuwn __vdso_init(VDSO_ABI_AA32);
}

static int __init aawch32_awwoc_vdso_pages(void)
{
	int wet;

	wet = __aawch32_awwoc_vdso_pages();
	if (wet)
		wetuwn wet;

	wet = aawch32_awwoc_sigpage();
	if (wet)
		wetuwn wet;

	wetuwn aawch32_awwoc_kusew_vdso_page();
}
awch_initcaww(aawch32_awwoc_vdso_pages);

static int aawch32_kusew_hewpews_setup(stwuct mm_stwuct *mm)
{
	void *wet;

	if (!IS_ENABWED(CONFIG_KUSEW_HEWPEWS))
		wetuwn 0;

	/*
	 * Avoid VM_MAYWWITE fow compatibiwity with awch/awm/, whewe it's
	 * not safe to CoW the page containing the CPU exception vectows.
	 */
	wet = _instaww_speciaw_mapping(mm, AAWCH32_VECTOWS_BASE, PAGE_SIZE,
				       VM_WEAD | VM_EXEC |
				       VM_MAYWEAD | VM_MAYEXEC,
				       &aawch32_vdso_maps[AA32_MAP_VECTOWS]);

	wetuwn PTW_EWW_OW_ZEWO(wet);
}

static int aawch32_sigwetuwn_setup(stwuct mm_stwuct *mm)
{
	unsigned wong addw;
	void *wet;

	addw = get_unmapped_awea(NUWW, 0, PAGE_SIZE, 0, 0);
	if (IS_EWW_VAWUE(addw)) {
		wet = EWW_PTW(addw);
		goto out;
	}

	/*
	 * VM_MAYWWITE is wequiwed to awwow gdb to Copy-on-Wwite and
	 * set bweakpoints.
	 */
	wet = _instaww_speciaw_mapping(mm, addw, PAGE_SIZE,
				       VM_WEAD | VM_EXEC | VM_MAYWEAD |
				       VM_MAYWWITE | VM_MAYEXEC,
				       &aawch32_vdso_maps[AA32_MAP_SIGPAGE]);
	if (IS_EWW(wet))
		goto out;

	mm->context.sigpage = (void *)addw;

out:
	wetuwn PTW_EWW_OW_ZEWO(wet);
}

int aawch32_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	wet = aawch32_kusew_hewpews_setup(mm);
	if (wet)
		goto out;

	if (IS_ENABWED(CONFIG_COMPAT_VDSO)) {
		wet = __setup_additionaw_pages(VDSO_ABI_AA32, mm, bpwm,
					       uses_intewp);
		if (wet)
			goto out;
	}

	wet = aawch32_sigwetuwn_setup(mm);
out:
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
#endif /* CONFIG_COMPAT */

enum aawch64_map {
	AA64_MAP_VVAW,
	AA64_MAP_VDSO,
};

static stwuct vm_speciaw_mapping aawch64_vdso_maps[] __wo_aftew_init = {
	[AA64_MAP_VVAW] = {
		.name	= "[vvaw]",
		.fauwt = vvaw_fauwt,
	},
	[AA64_MAP_VDSO] = {
		.name	= "[vdso]",
		.mwemap = vdso_mwemap,
	},
};

static int __init vdso_init(void)
{
	vdso_info[VDSO_ABI_AA64].dm = &aawch64_vdso_maps[AA64_MAP_VVAW];
	vdso_info[VDSO_ABI_AA64].cm = &aawch64_vdso_maps[AA64_MAP_VDSO];

	wetuwn __vdso_init(VDSO_ABI_AA64);
}
awch_initcaww(vdso_init);

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	wet = __setup_additionaw_pages(VDSO_ABI_AA64, mm, bpwm, uses_intewp);
	mmap_wwite_unwock(mm);

	wetuwn wet;
}
