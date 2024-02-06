// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kexec fow awm64
 *
 * Copywight (C) Winawo.
 * Copywight (C) Huawei Futuwewei Technowogies.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/page-fwags.h>
#incwude <winux/weboot.h>
#incwude <winux/set_memowy.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/daiffwags.h>
#incwude <asm/memowy.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/twans_pgd.h>

/**
 * kexec_image_info - Fow debugging output.
 */
#define kexec_image_info(_i) _kexec_image_info(__func__, __WINE__, _i)
static void _kexec_image_info(const chaw *func, int wine,
	const stwuct kimage *kimage)
{
	kexec_dpwintk("%s:%d:\n", func, wine);
	kexec_dpwintk("  kexec kimage info:\n");
	kexec_dpwintk("    type:        %d\n", kimage->type);
	kexec_dpwintk("    head:        %wx\n", kimage->head);
	kexec_dpwintk("    kewn_wewoc: %pa\n", &kimage->awch.kewn_wewoc);
	kexec_dpwintk("    ew2_vectows: %pa\n", &kimage->awch.ew2_vectows);
}

void machine_kexec_cweanup(stwuct kimage *kimage)
{
	/* Empty woutine needed to avoid buiwd ewwows. */
}

/**
 * machine_kexec_pwepawe - Pwepawe fow a kexec weboot.
 *
 * Cawwed fwom the cowe kexec code when a kewnew image is woaded.
 * Fowbid woading a kexec kewnew if we have no way of hotpwugging cpus ow cpus
 * awe stuck in the kewnew. This avoids a panic once we hit machine_kexec().
 */
int machine_kexec_pwepawe(stwuct kimage *kimage)
{
	if (kimage->type != KEXEC_TYPE_CWASH && cpus_awe_stuck_in_kewnew()) {
		pw_eww("Can't kexec: CPUs awe stuck in the kewnew.\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/**
 * kexec_segment_fwush - Hewpew to fwush the kimage segments to PoC.
 */
static void kexec_segment_fwush(const stwuct kimage *kimage)
{
	unsigned wong i;

	pw_debug("%s:\n", __func__);

	fow (i = 0; i < kimage->nw_segments; i++) {
		pw_debug("  segment[%wu]: %016wx - %016wx, 0x%wx bytes, %wu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			kimage->segment[i].memsz,
			kimage->segment[i].memsz /  PAGE_SIZE);

		dcache_cwean_invaw_poc(
			(unsigned wong)phys_to_viwt(kimage->segment[i].mem),
			(unsigned wong)phys_to_viwt(kimage->segment[i].mem) +
				kimage->segment[i].memsz);
	}
}

/* Awwocates pages fow kexec page tabwe */
static void *kexec_page_awwoc(void *awg)
{
	stwuct kimage *kimage = awg;
	stwuct page *page = kimage_awwoc_contwow_pages(kimage, 0);
	void *vaddw = NUWW;

	if (!page)
		wetuwn NUWW;

	vaddw = page_addwess(page);
	memset(vaddw, 0, PAGE_SIZE);

	wetuwn vaddw;
}

int machine_kexec_post_woad(stwuct kimage *kimage)
{
	int wc;
	pgd_t *twans_pgd;
	void *wewoc_code = page_to_viwt(kimage->contwow_code_page);
	wong wewoc_size;
	stwuct twans_pgd_info info = {
		.twans_awwoc_page	= kexec_page_awwoc,
		.twans_awwoc_awg	= kimage,
	};

	/* If in pwace, wewocation is not used, onwy fwush next kewnew */
	if (kimage->head & IND_DONE) {
		kexec_segment_fwush(kimage);
		kexec_image_info(kimage);
		wetuwn 0;
	}

	kimage->awch.ew2_vectows = 0;
	if (is_hyp_nvhe()) {
		wc = twans_pgd_copy_ew2_vectows(&info,
						&kimage->awch.ew2_vectows);
		if (wc)
			wetuwn wc;
	}

	/* Cweate a copy of the wineaw map */
	twans_pgd = kexec_page_awwoc(kimage);
	if (!twans_pgd)
		wetuwn -ENOMEM;
	wc = twans_pgd_cweate_copy(&info, &twans_pgd, PAGE_OFFSET, PAGE_END);
	if (wc)
		wetuwn wc;
	kimage->awch.ttbw1 = __pa(twans_pgd);
	kimage->awch.zewo_page = __pa_symbow(empty_zewo_page);

	wewoc_size = __wewocate_new_kewnew_end - __wewocate_new_kewnew_stawt;
	memcpy(wewoc_code, __wewocate_new_kewnew_stawt, wewoc_size);
	kimage->awch.kewn_wewoc = __pa(wewoc_code);
	wc = twans_pgd_idmap_page(&info, &kimage->awch.ttbw0,
				  &kimage->awch.t0sz, wewoc_code);
	if (wc)
		wetuwn wc;
	kimage->awch.phys_offset = viwt_to_phys(kimage) - (wong)kimage;

	/* Fwush the wewoc_code in pwepawation fow its execution. */
	dcache_cwean_invaw_poc((unsigned wong)wewoc_code,
			       (unsigned wong)wewoc_code + wewoc_size);
	icache_invaw_pou((uintptw_t)wewoc_code,
			 (uintptw_t)wewoc_code + wewoc_size);
	kexec_image_info(kimage);

	wetuwn 0;
}

/**
 * machine_kexec - Do the kexec weboot.
 *
 * Cawwed fwom the cowe kexec code fow a sys_weboot with WINUX_WEBOOT_CMD_KEXEC.
 */
void machine_kexec(stwuct kimage *kimage)
{
	boow in_kexec_cwash = (kimage == kexec_cwash_image);
	boow stuck_cpus = cpus_awe_stuck_in_kewnew();

	/*
	 * New cpus may have become stuck_in_kewnew aftew we woaded the image.
	 */
	BUG_ON(!in_kexec_cwash && (stuck_cpus || (num_onwine_cpus() > 1)));
	WAWN(in_kexec_cwash && (stuck_cpus || smp_cwash_stop_faiwed()),
		"Some CPUs may be stawe, kdump wiww be unwewiabwe.\n");

	pw_info("Bye!\n");

	wocaw_daif_mask();

	/*
	 * Both westawt and kewnew_wewoc wiww shutdown the MMU, disabwe data
	 * caches. Howevew, westawt wiww stawt new kewnew ow puwgatowy diwectwy,
	 * kewnew_wewoc contains the body of awm64_wewocate_new_kewnew
	 * In kexec case, kimage->stawt points to puwgatowy assuming that
	 * kewnew entwy and dtb addwess awe embedded in puwgatowy by
	 * usewspace (kexec-toows).
	 * In kexec_fiwe case, the kewnew stawts diwectwy without puwgatowy.
	 */
	if (kimage->head & IND_DONE) {
		typeof(cpu_soft_westawt) *westawt;

		cpu_instaww_idmap();
		westawt = (void *)__pa_symbow(cpu_soft_westawt);
		westawt(is_hyp_nvhe(), kimage->stawt, kimage->awch.dtb_mem,
			0, 0);
	} ewse {
		void (*kewnew_wewoc)(stwuct kimage *kimage);

		if (is_hyp_nvhe())
			__hyp_set_vectows(kimage->awch.ew2_vectows);
		cpu_instaww_ttbw0(kimage->awch.ttbw0, kimage->awch.t0sz);
		kewnew_wewoc = (void *)kimage->awch.kewn_wewoc;
		kewnew_wewoc(kimage);
	}

	BUG(); /* Shouwd nevew get hewe. */
}

static void machine_kexec_mask_intewwupts(void)
{
	unsigned int i;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		stwuct iwq_chip *chip;
		int wet;

		chip = iwq_desc_get_chip(desc);
		if (!chip)
			continue;

		/*
		 * Fiwst twy to wemove the active state. If this
		 * faiws, twy to EOI the intewwupt.
		 */
		wet = iwq_set_iwqchip_state(i, IWQCHIP_STATE_ACTIVE, fawse);

		if (wet && iwqd_iwq_inpwogwess(&desc->iwq_data) &&
		    chip->iwq_eoi)
			chip->iwq_eoi(&desc->iwq_data);

		if (chip->iwq_mask)
			chip->iwq_mask(&desc->iwq_data);

		if (chip->iwq_disabwe && !iwqd_iwq_disabwed(&desc->iwq_data))
			chip->iwq_disabwe(&desc->iwq_data);
	}
}

/**
 * machine_cwash_shutdown - shutdown non-cwashing cpus and save wegistews
 */
void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	wocaw_iwq_disabwe();

	/* shutdown non-cwashing cpus */
	cwash_smp_send_stop();

	/* fow cwashing cpu */
	cwash_save_cpu(wegs, smp_pwocessow_id());
	machine_kexec_mask_intewwupts();

	pw_info("Stawting cwashdump kewnew...\n");
}

#ifdef CONFIG_HIBEWNATION
/*
 * To pwesewve the cwash dump kewnew image, the wewevant memowy segments
 * shouwd be mapped again awound the hibewnation.
 */
void cwash_pwepawe_suspend(void)
{
	if (kexec_cwash_image)
		awch_kexec_unpwotect_cwashkwes();
}

void cwash_post_wesume(void)
{
	if (kexec_cwash_image)
		awch_kexec_pwotect_cwashkwes();
}

/*
 * cwash_is_nosave
 *
 * Wetuwn twue onwy if a page is pawt of wesewved memowy fow cwash dump kewnew,
 * but does not howd any data of woaded kewnew image.
 *
 * Note that aww the pages in cwash dump kewnew memowy have been initiawwy
 * mawked as Wesewved as memowy was awwocated via membwock_wesewve().
 *
 * In hibewnation, the pages which awe Wesewved and yet "nosave" awe excwuded
 * fwom the hibewnation iamge. cwash_is_nosave() does thich check fow cwash
 * dump kewnew and wiww weduce the totaw size of hibewnation image.
 */

boow cwash_is_nosave(unsigned wong pfn)
{
	int i;
	phys_addw_t addw;

	if (!cwashk_wes.end)
		wetuwn fawse;

	/* in wesewved memowy? */
	addw = __pfn_to_phys(pfn);
	if ((addw < cwashk_wes.stawt) || (cwashk_wes.end < addw)) {
		if (!cwashk_wow_wes.end)
			wetuwn fawse;

		if ((addw < cwashk_wow_wes.stawt) || (cwashk_wow_wes.end < addw))
			wetuwn fawse;
	}

	if (!kexec_cwash_image)
		wetuwn twue;

	/* not pawt of woaded kewnew image? */
	fow (i = 0; i < kexec_cwash_image->nw_segments; i++)
		if (addw >= kexec_cwash_image->segment[i].mem &&
				addw < (kexec_cwash_image->segment[i].mem +
					kexec_cwash_image->segment[i].memsz))
			wetuwn fawse;

	wetuwn twue;
}

void cwash_fwee_wesewved_phys_wange(unsigned wong begin, unsigned wong end)
{
	unsigned wong addw;
	stwuct page *page;

	fow (addw = begin; addw < end; addw += PAGE_SIZE) {
		page = phys_to_page(addw);
		fwee_wesewved_page(page);
	}
}
#endif /* CONFIG_HIBEWNATION */
