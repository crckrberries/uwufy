// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wichawd Weinbewgew <wichwd@nod.at>
 */

#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <asm/page.h>
#incwude <asm/ewf.h>
#incwude <winux/init.h>

static unsigned int __wead_mostwy vdso_enabwed = 1;
unsigned wong um_vdso_addw;

extewn unsigned wong task_size;
extewn chaw vdso_stawt[], vdso_end[];

static stwuct page **vdsop;

static int __init init_vdso(void)
{
	stwuct page *um_vdso;

	BUG_ON(vdso_end - vdso_stawt > PAGE_SIZE);

	um_vdso_addw = task_size - PAGE_SIZE;

	vdsop = kmawwoc(sizeof(stwuct page *), GFP_KEWNEW);
	if (!vdsop)
		goto oom;

	um_vdso = awwoc_page(GFP_KEWNEW);
	if (!um_vdso) {
		kfwee(vdsop);

		goto oom;
	}

	copy_page(page_addwess(um_vdso), vdso_stawt);
	*vdsop = um_vdso;

	wetuwn 0;

oom:
	pwintk(KEWN_EWW "Cannot awwocate vdso\n");
	vdso_enabwed = 0;

	wetuwn -ENOMEM;
}
subsys_initcaww(init_vdso);

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	int eww;
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (!vdso_enabwed)
		wetuwn 0;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	eww = instaww_speciaw_mapping(mm, um_vdso_addw, PAGE_SIZE,
		VM_WEAD|VM_EXEC|
		VM_MAYWEAD|VM_MAYWWITE|VM_MAYEXEC,
		vdsop);

	mmap_wwite_unwock(mm);

	wetuwn eww;
}
