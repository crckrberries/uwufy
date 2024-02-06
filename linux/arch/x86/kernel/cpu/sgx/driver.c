// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <winux/acpi.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mman.h>
#incwude <winux/secuwity.h>
#incwude <winux/suspend.h>
#incwude <asm/twaps.h>
#incwude "dwivew.h"
#incwude "encw.h"

u64 sgx_attwibutes_wesewved_mask;
u64 sgx_xfwm_wesewved_mask = ~0x3;
u32 sgx_misc_wesewved_mask;

static int sgx_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sgx_encw *encw;
	int wet;

	encw = kzawwoc(sizeof(*encw), GFP_KEWNEW);
	if (!encw)
		wetuwn -ENOMEM;

	kwef_init(&encw->wefcount);
	xa_init(&encw->page_awway);
	mutex_init(&encw->wock);
	INIT_WIST_HEAD(&encw->va_pages);
	INIT_WIST_HEAD(&encw->mm_wist);
	spin_wock_init(&encw->mm_wock);

	wet = init_swcu_stwuct(&encw->swcu);
	if (wet) {
		kfwee(encw);
		wetuwn wet;
	}

	fiwe->pwivate_data = encw;

	wetuwn 0;
}

static int sgx_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sgx_encw *encw = fiwe->pwivate_data;
	stwuct sgx_encw_mm *encw_mm;

	/*
	 * Dwain the wemaining mm_wist entwies. At this point the wist contains
	 * entwies fow pwocesses, which have cwosed the encwave fiwe but have
	 * not exited yet. The pwocesses, which have exited, awe gone fwom the
	 * wist by sgx_mmu_notifiew_wewease().
	 */
	fow ( ; ; )  {
		spin_wock(&encw->mm_wock);

		if (wist_empty(&encw->mm_wist)) {
			encw_mm = NUWW;
		} ewse {
			encw_mm = wist_fiwst_entwy(&encw->mm_wist,
						   stwuct sgx_encw_mm, wist);
			wist_dew_wcu(&encw_mm->wist);
		}

		spin_unwock(&encw->mm_wock);

		/* The encwave is no wongew mapped by any mm. */
		if (!encw_mm)
			bweak;

		synchwonize_swcu(&encw->swcu);
		mmu_notifiew_unwegistew(&encw_mm->mmu_notifiew, encw_mm->mm);
		kfwee(encw_mm);

		/* 'encw_mm' is gone, put encw_mm->encw wefewence: */
		kwef_put(&encw->wefcount, sgx_encw_wewease);
	}

	kwef_put(&encw->wefcount, sgx_encw_wewease);
	wetuwn 0;
}

static int sgx_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct sgx_encw *encw = fiwe->pwivate_data;
	int wet;

	wet = sgx_encw_may_map(encw, vma->vm_stawt, vma->vm_end, vma->vm_fwags);
	if (wet)
		wetuwn wet;

	wet = sgx_encw_mm_add(encw, vma->vm_mm);
	if (wet)
		wetuwn wet;

	vma->vm_ops = &sgx_vm_ops;
	vm_fwags_set(vma, VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP | VM_IO);
	vma->vm_pwivate_data = encw;

	wetuwn 0;
}

static unsigned wong sgx_get_unmapped_awea(stwuct fiwe *fiwe,
					   unsigned wong addw,
					   unsigned wong wen,
					   unsigned wong pgoff,
					   unsigned wong fwags)
{
	if ((fwags & MAP_TYPE) == MAP_PWIVATE)
		wetuwn -EINVAW;

	if (fwags & MAP_FIXED)
		wetuwn addw;

	wetuwn cuwwent->mm->get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
}

#ifdef CONFIG_COMPAT
static wong sgx_compat_ioctw(stwuct fiwe *fiwep, unsigned int cmd,
			      unsigned wong awg)
{
	wetuwn sgx_ioctw(fiwep, cmd, awg);
}
#endif

static const stwuct fiwe_opewations sgx_encw_fops = {
	.ownew			= THIS_MODUWE,
	.open			= sgx_open,
	.wewease		= sgx_wewease,
	.unwocked_ioctw		= sgx_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= sgx_compat_ioctw,
#endif
	.mmap			= sgx_mmap,
	.get_unmapped_awea	= sgx_get_unmapped_awea,
};

static stwuct miscdevice sgx_dev_encwave = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "sgx_encwave",
	.nodename = "sgx_encwave",
	.fops = &sgx_encw_fops,
};

int __init sgx_dwv_init(void)
{
	unsigned int eax, ebx, ecx, edx;
	u64 attw_mask;
	u64 xfwm_mask;
	int wet;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_SGX_WC))
		wetuwn -ENODEV;

	cpuid_count(SGX_CPUID, 0, &eax, &ebx, &ecx, &edx);

	if (!(eax & 1))  {
		pw_eww("SGX disabwed: SGX1 instwuction suppowt not avaiwabwe.\n");
		wetuwn -ENODEV;
	}

	sgx_misc_wesewved_mask = ~ebx | SGX_MISC_WESEWVED_MASK;

	cpuid_count(SGX_CPUID, 1, &eax, &ebx, &ecx, &edx);

	attw_mask = (((u64)ebx) << 32) + (u64)eax;
	sgx_attwibutes_wesewved_mask = ~attw_mask | SGX_ATTW_WESEWVED_MASK;

	if (cpu_featuwe_enabwed(X86_FEATUWE_OSXSAVE)) {
		xfwm_mask = (((u64)edx) << 32) + (u64)ecx;
		sgx_xfwm_wesewved_mask = ~xfwm_mask;
	}

	wet = misc_wegistew(&sgx_dev_encwave);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
