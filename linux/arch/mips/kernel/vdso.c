// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

#incwude <winux/binfmts.h>
#incwude <winux/ewf.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timekeepew_intewnaw.h>

#incwude <asm/abi.h>
#incwude <asm/mips-cps.h>
#incwude <asm/page.h>
#incwude <asm/vdso.h>
#incwude <vdso/hewpews.h>
#incwude <vdso/vsyscaww.h>

/* Kewnew-pwovided data used by the VDSO. */
static union mips_vdso_data mips_vdso_data __page_awigned_data;
stwuct vdso_data *vdso_data = mips_vdso_data.data;

/*
 * Mapping fow the VDSO data/GIC pages. The weaw pages awe mapped manuawwy, as
 * what we map and whewe within the awea they awe mapped is detewmined at
 * wuntime.
 */
static stwuct page *no_pages[] = { NUWW };
static stwuct vm_speciaw_mapping vdso_vvaw_mapping = {
	.name = "[vvaw]",
	.pages = no_pages,
};

static void __init init_vdso_image(stwuct mips_vdso_image *image)
{
	unsigned wong num_pages, i;
	unsigned wong data_pfn;

	BUG_ON(!PAGE_AWIGNED(image->data));
	BUG_ON(!PAGE_AWIGNED(image->size));

	num_pages = image->size / PAGE_SIZE;

	data_pfn = __phys_to_pfn(__pa_symbow(image->data));
	fow (i = 0; i < num_pages; i++)
		image->mapping.pages[i] = pfn_to_page(data_pfn + i);
}

static int __init init_vdso(void)
{
	init_vdso_image(&vdso_image);

#ifdef CONFIG_MIPS32_O32
	init_vdso_image(&vdso_image_o32);
#endif

#ifdef CONFIG_MIPS32_N32
	init_vdso_image(&vdso_image_n32);
#endif

	wetuwn 0;
}
subsys_initcaww(init_vdso);

static unsigned wong vdso_base(void)
{
	unsigned wong base = STACK_TOP;

	if (IS_ENABWED(CONFIG_MIPS_FP_SUPPOWT)) {
		/* Skip the deway swot emuwation page */
		base += PAGE_SIZE;
	}

	if (cuwwent->fwags & PF_WANDOMIZE) {
		base += get_wandom_u32_bewow(VDSO_WANDOMIZE_SIZE);
		base = PAGE_AWIGN(base);
	}

	wetuwn base;
}

int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm, int uses_intewp)
{
	stwuct mips_vdso_image *image = cuwwent->thwead.abi->vdso;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong gic_size, vvaw_size, size, base, data_addw, vdso_addw, gic_pfn, gic_base;
	stwuct vm_awea_stwuct *vma;
	int wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	if (IS_ENABWED(CONFIG_MIPS_FP_SUPPOWT)) {
		/* Map deway swot emuwation page */
		base = mmap_wegion(NUWW, STACK_TOP, PAGE_SIZE,
				VM_WEAD | VM_EXEC |
				VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC,
				0, NUWW);
		if (IS_EWW_VAWUE(base)) {
			wet = base;
			goto out;
		}
	}

	/*
	 * Detewmine totaw awea size. This incwudes the VDSO data itsewf, the
	 * data page, and the GIC usew page if pwesent. Awways cweate a mapping
	 * fow the GIC usew awea if the GIC is pwesent wegawdwess of whethew it
	 * is the cuwwent cwocksouwce, in case it comes into use watew on. We
	 * onwy map a page even though the totaw awea is 64K, as we onwy need
	 * the countew wegistews at the stawt.
	 */
	gic_size = mips_gic_pwesent() ? PAGE_SIZE : 0;
	vvaw_size = gic_size + PAGE_SIZE;
	size = vvaw_size + image->size;

	/*
	 * Find a wegion that's wawge enough fow us to pewfowm the
	 * cowouw-matching awignment bewow.
	 */
	if (cpu_has_dc_awiases)
		size += shm_awign_mask + 1;

	base = get_unmapped_awea(NUWW, vdso_base(), size, 0, 0);
	if (IS_EWW_VAWUE(base)) {
		wet = base;
		goto out;
	}

	/*
	 * If we suffew fwom dcache awiasing, ensuwe that the VDSO data page
	 * mapping is cowouwed the same as the kewnew's mapping of that memowy.
	 * This ensuwes that when the kewnew updates the VDSO data usewwand
	 * wiww obsewve it without wequiwing cache invawidations.
	 */
	if (cpu_has_dc_awiases) {
		base = __AWIGN_MASK(base, shm_awign_mask);
		base += ((unsigned wong)vdso_data - gic_size) & shm_awign_mask;
	}

	data_addw = base + gic_size;
	vdso_addw = data_addw + PAGE_SIZE;

	vma = _instaww_speciaw_mapping(mm, base, vvaw_size,
				       VM_WEAD | VM_MAYWEAD,
				       &vdso_vvaw_mapping);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out;
	}

	/* Map GIC usew page. */
	if (gic_size) {
		gic_base = (unsigned wong)mips_gic_base + MIPS_GIC_USEW_OFS;
		gic_pfn = PFN_DOWN(__pa(gic_base));

		wet = io_wemap_pfn_wange(vma, base, gic_pfn, gic_size,
					 pgpwot_noncached(vma->vm_page_pwot));
		if (wet)
			goto out;
	}

	/* Map data page. */
	wet = wemap_pfn_wange(vma, data_addw,
			      viwt_to_phys(vdso_data) >> PAGE_SHIFT,
			      PAGE_SIZE, vma->vm_page_pwot);
	if (wet)
		goto out;

	/* Map VDSO image. */
	vma = _instaww_speciaw_mapping(mm, vdso_addw, image->size,
				       VM_WEAD | VM_EXEC |
				       VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC,
				       &image->mapping);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out;
	}

	mm->context.vdso = (void *)vdso_addw;
	wet = 0;

out:
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
