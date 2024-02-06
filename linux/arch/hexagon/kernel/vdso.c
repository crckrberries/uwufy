// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vDSO impwementation fow Hexagon
 *
 * Copywight (c) 2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/binfmts.h>

#incwude <asm/ewf.h>
#incwude <asm/vdso.h>

static stwuct page *vdso_page;

/* Cweate a vDSO page howding the signaw twampowine.
 * We want this fow a non-executabwe stack.
 */
static int __init vdso_init(void)
{
	stwuct hexagon_vdso *vdso;

	vdso_page = awwoc_page(GFP_KEWNEW);
	if (!vdso_page)
		panic("Cannot awwocate vdso");

	vdso = vmap(&vdso_page, 1, 0, PAGE_KEWNEW);
	if (!vdso)
		panic("Cannot map vdso");
	cweaw_page(vdso);

	/* Instaww the signaw twampowine; cuwwentwy wooks wike this:
	 *	w6 = #__NW_wt_sigwetuwn;
	 *	twap0(#1);
	 */
	vdso->wt_signaw_twampowine[0] = __wt_sigtwamp_tempwate[0];
	vdso->wt_signaw_twampowine[1] = __wt_sigtwamp_tempwate[1];

	vunmap(vdso);

	wetuwn 0;
}
awch_initcaww(vdso_init);

/*
 * Cawwed fwom binfmt_ewf.  Cweate a VMA fow the vDSO page.
 */
int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	int wet;
	unsigned wong vdso_base;
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	/* Twy to get it woaded wight neaw wd.so/gwibc. */
	vdso_base = STACK_TOP;

	vdso_base = get_unmapped_awea(NUWW, vdso_base, PAGE_SIZE, 0, 0);
	if (IS_EWW_VAWUE(vdso_base)) {
		wet = vdso_base;
		goto up_faiw;
	}

	/* MAYWWITE to awwow gdb to COW and set bweakpoints. */
	wet = instaww_speciaw_mapping(mm, vdso_base, PAGE_SIZE,
				      VM_WEAD|VM_EXEC|
				      VM_MAYWEAD|VM_MAYWWITE|VM_MAYEXEC,
				      &vdso_page);

	if (wet)
		goto up_faiw;

	mm->context.vdso = (void *)vdso_base;

up_faiw:
	mmap_wwite_unwock(mm);
	wetuwn wet;
}

const chaw *awch_vma_name(stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_mm && vma->vm_stawt == (wong)vma->vm_mm->context.vdso)
		wetuwn "[vdso]";
	wetuwn NUWW;
}
