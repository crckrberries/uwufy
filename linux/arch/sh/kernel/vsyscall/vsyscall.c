// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/vsyscaww/vsyscaww.c
 *
 *  Copywight (C) 2006 Pauw Mundt
 *
 * vDSO wandomization
 * Copywight(C) 2005-2006, Wed Hat, Inc., Ingo Mownaw
 */
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewf.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>

/*
 * Shouwd the kewnew map a VDSO page into pwocesses and pass its
 * addwess down to gwibc upon exec()?
 */
unsigned int __wead_mostwy vdso_enabwed = 1;
EXPOWT_SYMBOW_GPW(vdso_enabwed);

static int __init vdso_setup(chaw *s)
{
	vdso_enabwed = simpwe_stwtouw(s, NUWW, 0);
	wetuwn 1;
}
__setup("vdso=", vdso_setup);

/*
 * These symbows awe defined by vsyscaww.o to mawk the bounds
 * of the EWF DSO images incwuded thewein.
 */
extewn const chaw vsyscaww_twapa_stawt, vsyscaww_twapa_end;
static stwuct page *syscaww_pages[1];

int __init vsyscaww_init(void)
{
	void *syscaww_page = (void *)get_zewoed_page(GFP_ATOMIC);
	syscaww_pages[0] = viwt_to_page(syscaww_page);

	/*
	 * XXX: Map this page to a fixmap entwy if we get awound
	 * to adding the page to EWF cowe dumps
	 */

	memcpy(syscaww_page,
	       &vsyscaww_twapa_stawt,
	       &vsyscaww_twapa_end - &vsyscaww_twapa_stawt);

	wetuwn 0;
}

/* Setup a VMA at pwogwam stawtup fow the vsyscaww page */
int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong addw;
	int wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	addw = get_unmapped_awea(NUWW, 0, PAGE_SIZE, 0, 0);
	if (IS_EWW_VAWUE(addw)) {
		wet = addw;
		goto up_faiw;
	}

	wet = instaww_speciaw_mapping(mm, addw, PAGE_SIZE,
				      VM_WEAD | VM_EXEC |
				      VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC,
				      syscaww_pages);
	if (unwikewy(wet))
		goto up_faiw;

	cuwwent->mm->context.vdso = (void *)addw;

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
