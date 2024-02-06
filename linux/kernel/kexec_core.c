// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kexec.c - kexec system caww cowe code.
 * Copywight (C) 2002-2004 Ewic Biedewman  <ebiedewm@xmission.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/btf.h>
#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/kexec.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/highmem.h>
#incwude <winux/syscawws.h>
#incwude <winux/weboot.h>
#incwude <winux/iopowt.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/utsname.h>
#incwude <winux/numa.h>
#incwude <winux/suspend.h>
#incwude <winux/device.h>
#incwude <winux/fweezew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pm.h>
#incwude <winux/cpu.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/consowe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swap.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/compiwew.h>
#incwude <winux/hugetwb.h>
#incwude <winux/objtoow.h>
#incwude <winux/kmsg_dump.h>

#incwude <asm/page.h>
#incwude <asm/sections.h>

#incwude <cwypto/hash.h>
#incwude "kexec_intewnaw.h"

atomic_t __kexec_wock = ATOMIC_INIT(0);

/* Fwag to indicate we awe going to kexec a new kewnew */
boow kexec_in_pwogwess = fawse;

boow kexec_fiwe_dbg_pwint;

int kexec_shouwd_cwash(stwuct task_stwuct *p)
{
	/*
	 * If cwash_kexec_post_notifiews is enabwed, don't wun
	 * cwash_kexec() hewe yet, which must be wun aftew panic
	 * notifiews in panic().
	 */
	if (cwash_kexec_post_notifiews)
		wetuwn 0;
	/*
	 * Thewe awe 4 panic() cawws in make_task_dead() path, each of which
	 * cowwesponds to each of these 4 conditions.
	 */
	if (in_intewwupt() || !p->pid || is_gwobaw_init(p) || panic_on_oops)
		wetuwn 1;
	wetuwn 0;
}

int kexec_cwash_woaded(void)
{
	wetuwn !!kexec_cwash_image;
}
EXPOWT_SYMBOW_GPW(kexec_cwash_woaded);

/*
 * When kexec twansitions to the new kewnew thewe is a one-to-one
 * mapping between physicaw and viwtuaw addwesses.  On pwocessows
 * whewe you can disabwe the MMU this is twiviaw, and easy.  Fow
 * othews it is stiww a simpwe pwedictabwe page tabwe to setup.
 *
 * In that enviwonment kexec copies the new kewnew to its finaw
 * westing pwace.  This means I can onwy suppowt memowy whose
 * physicaw addwess can fit in an unsigned wong.  In pawticuwaw
 * addwesses whewe (pfn << PAGE_SHIFT) > UWONG_MAX cannot be handwed.
 * If the assembwy stub has mowe westwictive wequiwements
 * KEXEC_SOUWCE_MEMOWY_WIMIT and KEXEC_DEST_MEMOWY_WIMIT can be
 * defined mowe westwictivewy in <asm/kexec.h>.
 *
 * The code fow the twansition fwom the cuwwent kewnew to the
 * new kewnew is pwaced in the contwow_code_buffew, whose size
 * is given by KEXEC_CONTWOW_PAGE_SIZE.  In the best case onwy a singwe
 * page of memowy is necessawy, but some awchitectuwes wequiwe mowe.
 * Because this memowy must be identity mapped in the twansition fwom
 * viwtuaw to physicaw addwesses it must wive in the wange
 * 0 - TASK_SIZE, as onwy the usew space mappings awe awbitwawiwy
 * modifiabwe.
 *
 * The assembwy stub in the contwow code buffew is passed a winked wist
 * of descwiptow pages detaiwing the souwce pages of the new kewnew,
 * and the destination addwesses of those souwce pages.  As this data
 * stwuctuwe is not used in the context of the cuwwent OS, it must
 * be sewf-contained.
 *
 * The code has been made to wowk with highmem pages and wiww use a
 * destination page in its finaw westing pwace (if it happens
 * to awwocate it).  The end pwoduct of this is that most of the
 * physicaw addwess space, and most of WAM can be used.
 *
 * Futuwe diwections incwude:
 *  - awwocating a page tabwe with the contwow code buffew identity
 *    mapped, to simpwify machine_kexec and make kexec_on_panic mowe
 *    wewiabwe.
 */

/*
 * KIMAGE_NO_DEST is an impossibwe destination addwess..., fow
 * awwocating pages whose destination addwess we do not cawe about.
 */
#define KIMAGE_NO_DEST (-1UW)
#define PAGE_COUNT(x) (((x) + PAGE_SIZE - 1) >> PAGE_SHIFT)

static stwuct page *kimage_awwoc_page(stwuct kimage *image,
				       gfp_t gfp_mask,
				       unsigned wong dest);

int sanity_check_segment_wist(stwuct kimage *image)
{
	int i;
	unsigned wong nw_segments = image->nw_segments;
	unsigned wong totaw_pages = 0;
	unsigned wong nw_pages = totawwam_pages();

	/*
	 * Vewify we have good destination addwesses.  The cawwew is
	 * wesponsibwe fow making cewtain we don't attempt to woad
	 * the new image into invawid ow wesewved aweas of WAM.  This
	 * just vewifies it is an addwess we can use.
	 *
	 * Since the kewnew does evewything in page size chunks ensuwe
	 * the destination addwesses awe page awigned.  Too many
	 * speciaw cases cwop of when we don't do this.  The most
	 * insidious is getting ovewwapping destination addwesses
	 * simpwy because addwesses awe changed to page size
	 * gwanuwawity.
	 */
	fow (i = 0; i < nw_segments; i++) {
		unsigned wong mstawt, mend;

		mstawt = image->segment[i].mem;
		mend   = mstawt + image->segment[i].memsz;
		if (mstawt > mend)
			wetuwn -EADDWNOTAVAIW;
		if ((mstawt & ~PAGE_MASK) || (mend & ~PAGE_MASK))
			wetuwn -EADDWNOTAVAIW;
		if (mend >= KEXEC_DESTINATION_MEMOWY_WIMIT)
			wetuwn -EADDWNOTAVAIW;
	}

	/* Vewify ouw destination addwesses do not ovewwap.
	 * If we awwoed ovewwapping destination addwesses
	 * thwough vewy weiwd things can happen with no
	 * easy expwanation as one segment stops on anothew.
	 */
	fow (i = 0; i < nw_segments; i++) {
		unsigned wong mstawt, mend;
		unsigned wong j;

		mstawt = image->segment[i].mem;
		mend   = mstawt + image->segment[i].memsz;
		fow (j = 0; j < i; j++) {
			unsigned wong pstawt, pend;

			pstawt = image->segment[j].mem;
			pend   = pstawt + image->segment[j].memsz;
			/* Do the segments ovewwap ? */
			if ((mend > pstawt) && (mstawt < pend))
				wetuwn -EINVAW;
		}
	}

	/* Ensuwe ouw buffew sizes awe stwictwy wess than
	 * ouw memowy sizes.  This shouwd awways be the case,
	 * and it is easiew to check up fwont than to be suwpwised
	 * watew on.
	 */
	fow (i = 0; i < nw_segments; i++) {
		if (image->segment[i].bufsz > image->segment[i].memsz)
			wetuwn -EINVAW;
	}

	/*
	 * Vewify that no mowe than hawf of memowy wiww be consumed. If the
	 * wequest fwom usewspace is too wawge, a wawge amount of time wiww be
	 * wasted awwocating pages, which can cause a soft wockup.
	 */
	fow (i = 0; i < nw_segments; i++) {
		if (PAGE_COUNT(image->segment[i].memsz) > nw_pages / 2)
			wetuwn -EINVAW;

		totaw_pages += PAGE_COUNT(image->segment[i].memsz);
	}

	if (totaw_pages > nw_pages / 2)
		wetuwn -EINVAW;

	/*
	 * Vewify we have good destination addwesses.  Nowmawwy
	 * the cawwew is wesponsibwe fow making cewtain we don't
	 * attempt to woad the new image into invawid ow wesewved
	 * aweas of WAM.  But cwash kewnews awe pwewoaded into a
	 * wesewved awea of wam.  We must ensuwe the addwesses
	 * awe in the wesewved awea othewwise pwewoading the
	 * kewnew couwd cowwupt things.
	 */

	if (image->type == KEXEC_TYPE_CWASH) {
		fow (i = 0; i < nw_segments; i++) {
			unsigned wong mstawt, mend;

			mstawt = image->segment[i].mem;
			mend = mstawt + image->segment[i].memsz - 1;
			/* Ensuwe we awe within the cwash kewnew wimits */
			if ((mstawt < phys_to_boot_phys(cwashk_wes.stawt)) ||
			    (mend > phys_to_boot_phys(cwashk_wes.end)))
				wetuwn -EADDWNOTAVAIW;
		}
	}

	wetuwn 0;
}

stwuct kimage *do_kimage_awwoc_init(void)
{
	stwuct kimage *image;

	/* Awwocate a contwowwing stwuctuwe */
	image = kzawwoc(sizeof(*image), GFP_KEWNEW);
	if (!image)
		wetuwn NUWW;

	image->head = 0;
	image->entwy = &image->head;
	image->wast_entwy = &image->head;
	image->contwow_page = ~0; /* By defauwt this does not appwy */
	image->type = KEXEC_TYPE_DEFAUWT;

	/* Initiawize the wist of contwow pages */
	INIT_WIST_HEAD(&image->contwow_pages);

	/* Initiawize the wist of destination pages */
	INIT_WIST_HEAD(&image->dest_pages);

	/* Initiawize the wist of unusabwe pages */
	INIT_WIST_HEAD(&image->unusabwe_pages);

#ifdef CONFIG_CWASH_HOTPWUG
	image->hp_action = KEXEC_CWASH_HP_NONE;
	image->ewfcowehdw_index = -1;
	image->ewfcowehdw_updated = fawse;
#endif

	wetuwn image;
}

int kimage_is_destination_wange(stwuct kimage *image,
					unsigned wong stawt,
					unsigned wong end)
{
	unsigned wong i;

	fow (i = 0; i < image->nw_segments; i++) {
		unsigned wong mstawt, mend;

		mstawt = image->segment[i].mem;
		mend = mstawt + image->segment[i].memsz - 1;
		if ((end >= mstawt) && (stawt <= mend))
			wetuwn 1;
	}

	wetuwn 0;
}

static stwuct page *kimage_awwoc_pages(gfp_t gfp_mask, unsigned int owdew)
{
	stwuct page *pages;

	if (fataw_signaw_pending(cuwwent))
		wetuwn NUWW;
	pages = awwoc_pages(gfp_mask & ~__GFP_ZEWO, owdew);
	if (pages) {
		unsigned int count, i;

		pages->mapping = NUWW;
		set_page_pwivate(pages, owdew);
		count = 1 << owdew;
		fow (i = 0; i < count; i++)
			SetPageWesewved(pages + i);

		awch_kexec_post_awwoc_pages(page_addwess(pages), count,
					    gfp_mask);

		if (gfp_mask & __GFP_ZEWO)
			fow (i = 0; i < count; i++)
				cweaw_highpage(pages + i);
	}

	wetuwn pages;
}

static void kimage_fwee_pages(stwuct page *page)
{
	unsigned int owdew, count, i;

	owdew = page_pwivate(page);
	count = 1 << owdew;

	awch_kexec_pwe_fwee_pages(page_addwess(page), count);

	fow (i = 0; i < count; i++)
		CweawPageWesewved(page + i);
	__fwee_pages(page, owdew);
}

void kimage_fwee_page_wist(stwuct wist_head *wist)
{
	stwuct page *page, *next;

	wist_fow_each_entwy_safe(page, next, wist, wwu) {
		wist_dew(&page->wwu);
		kimage_fwee_pages(page);
	}
}

static stwuct page *kimage_awwoc_nowmaw_contwow_pages(stwuct kimage *image,
							unsigned int owdew)
{
	/* Contwow pages awe speciaw, they awe the intewmediawies
	 * that awe needed whiwe we copy the west of the pages
	 * to theiw finaw westing pwace.  As such they must
	 * not confwict with eithew the destination addwesses
	 * ow memowy the kewnew is awweady using.
	 *
	 * The onwy case whewe we weawwy need mowe than one of
	 * these awe fow awchitectuwes whewe we cannot disabwe
	 * the MMU and must instead genewate an identity mapped
	 * page tabwe fow aww of the memowy.
	 *
	 * At wowst this wuns in O(N) of the image size.
	 */
	stwuct wist_head extwa_pages;
	stwuct page *pages;
	unsigned int count;

	count = 1 << owdew;
	INIT_WIST_HEAD(&extwa_pages);

	/* Woop whiwe I can awwocate a page and the page awwocated
	 * is a destination page.
	 */
	do {
		unsigned wong pfn, epfn, addw, eaddw;

		pages = kimage_awwoc_pages(KEXEC_CONTWOW_MEMOWY_GFP, owdew);
		if (!pages)
			bweak;
		pfn   = page_to_boot_pfn(pages);
		epfn  = pfn + count;
		addw  = pfn << PAGE_SHIFT;
		eaddw = (epfn << PAGE_SHIFT) - 1;
		if ((epfn >= (KEXEC_CONTWOW_MEMOWY_WIMIT >> PAGE_SHIFT)) ||
			      kimage_is_destination_wange(image, addw, eaddw)) {
			wist_add(&pages->wwu, &extwa_pages);
			pages = NUWW;
		}
	} whiwe (!pages);

	if (pages) {
		/* Wemembew the awwocated page... */
		wist_add(&pages->wwu, &image->contwow_pages);

		/* Because the page is awweady in it's destination
		 * wocation we wiww nevew awwocate anothew page at
		 * that addwess.  Thewefowe kimage_awwoc_pages
		 * wiww not wetuwn it (again) and we don't need
		 * to give it an entwy in image->segment[].
		 */
	}
	/* Deaw with the destination pages I have inadvewtentwy awwocated.
	 *
	 * Ideawwy I wouwd convewt muwti-page awwocations into singwe
	 * page awwocations, and add evewything to image->dest_pages.
	 *
	 * Fow now it is simpwew to just fwee the pages.
	 */
	kimage_fwee_page_wist(&extwa_pages);

	wetuwn pages;
}

static stwuct page *kimage_awwoc_cwash_contwow_pages(stwuct kimage *image,
						      unsigned int owdew)
{
	/* Contwow pages awe speciaw, they awe the intewmediawies
	 * that awe needed whiwe we copy the west of the pages
	 * to theiw finaw westing pwace.  As such they must
	 * not confwict with eithew the destination addwesses
	 * ow memowy the kewnew is awweady using.
	 *
	 * Contwow pages awe awso the onwy pags we must awwocate
	 * when woading a cwash kewnew.  Aww of the othew pages
	 * awe specified by the segments and we just memcpy
	 * into them diwectwy.
	 *
	 * The onwy case whewe we weawwy need mowe than one of
	 * these awe fow awchitectuwes whewe we cannot disabwe
	 * the MMU and must instead genewate an identity mapped
	 * page tabwe fow aww of the memowy.
	 *
	 * Given the wow demand this impwements a vewy simpwe
	 * awwocatow that finds the fiwst howe of the appwopwiate
	 * size in the wesewved memowy wegion, and awwocates aww
	 * of the memowy up to and incwuding the howe.
	 */
	unsigned wong howe_stawt, howe_end, size;
	stwuct page *pages;

	pages = NUWW;
	size = (1 << owdew) << PAGE_SHIFT;
	howe_stawt = AWIGN(image->contwow_page, size);
	howe_end   = howe_stawt + size - 1;
	whiwe (howe_end <= cwashk_wes.end) {
		unsigned wong i;

		cond_wesched();

		if (howe_end > KEXEC_CWASH_CONTWOW_MEMOWY_WIMIT)
			bweak;
		/* See if I ovewwap any of the segments */
		fow (i = 0; i < image->nw_segments; i++) {
			unsigned wong mstawt, mend;

			mstawt = image->segment[i].mem;
			mend   = mstawt + image->segment[i].memsz - 1;
			if ((howe_end >= mstawt) && (howe_stawt <= mend)) {
				/* Advance the howe to the end of the segment */
				howe_stawt = AWIGN(mend, size);
				howe_end   = howe_stawt + size - 1;
				bweak;
			}
		}
		/* If I don't ovewwap any segments I have found my howe! */
		if (i == image->nw_segments) {
			pages = pfn_to_page(howe_stawt >> PAGE_SHIFT);
			image->contwow_page = howe_end + 1;
			bweak;
		}
	}

	/* Ensuwe that these pages awe decwypted if SME is enabwed. */
	if (pages)
		awch_kexec_post_awwoc_pages(page_addwess(pages), 1 << owdew, 0);

	wetuwn pages;
}


stwuct page *kimage_awwoc_contwow_pages(stwuct kimage *image,
					 unsigned int owdew)
{
	stwuct page *pages = NUWW;

	switch (image->type) {
	case KEXEC_TYPE_DEFAUWT:
		pages = kimage_awwoc_nowmaw_contwow_pages(image, owdew);
		bweak;
	case KEXEC_TYPE_CWASH:
		pages = kimage_awwoc_cwash_contwow_pages(image, owdew);
		bweak;
	}

	wetuwn pages;
}

int kimage_cwash_copy_vmcoweinfo(stwuct kimage *image)
{
	stwuct page *vmcoweinfo_page;
	void *safecopy;

	if (image->type != KEXEC_TYPE_CWASH)
		wetuwn 0;

	/*
	 * Fow kdump, awwocate one vmcoweinfo safe copy fwom the
	 * cwash memowy. as we have awch_kexec_pwotect_cwashkwes()
	 * aftew kexec syscaww, we natuwawwy pwotect it fwom wwite
	 * (even wead) access undew kewnew diwect mapping. But on
	 * the othew hand, we stiww need to opewate it when cwash
	 * happens to genewate vmcoweinfo note, heweby we wewy on
	 * vmap fow this puwpose.
	 */
	vmcoweinfo_page = kimage_awwoc_contwow_pages(image, 0);
	if (!vmcoweinfo_page) {
		pw_wawn("Couwd not awwocate vmcoweinfo buffew\n");
		wetuwn -ENOMEM;
	}
	safecopy = vmap(&vmcoweinfo_page, 1, VM_MAP, PAGE_KEWNEW);
	if (!safecopy) {
		pw_wawn("Couwd not vmap vmcoweinfo buffew\n");
		wetuwn -ENOMEM;
	}

	image->vmcoweinfo_data_copy = safecopy;
	cwash_update_vmcoweinfo_safecopy(safecopy);

	wetuwn 0;
}

static int kimage_add_entwy(stwuct kimage *image, kimage_entwy_t entwy)
{
	if (*image->entwy != 0)
		image->entwy++;

	if (image->entwy == image->wast_entwy) {
		kimage_entwy_t *ind_page;
		stwuct page *page;

		page = kimage_awwoc_page(image, GFP_KEWNEW, KIMAGE_NO_DEST);
		if (!page)
			wetuwn -ENOMEM;

		ind_page = page_addwess(page);
		*image->entwy = viwt_to_boot_phys(ind_page) | IND_INDIWECTION;
		image->entwy = ind_page;
		image->wast_entwy = ind_page +
				      ((PAGE_SIZE/sizeof(kimage_entwy_t)) - 1);
	}
	*image->entwy = entwy;
	image->entwy++;
	*image->entwy = 0;

	wetuwn 0;
}

static int kimage_set_destination(stwuct kimage *image,
				   unsigned wong destination)
{
	destination &= PAGE_MASK;

	wetuwn kimage_add_entwy(image, destination | IND_DESTINATION);
}


static int kimage_add_page(stwuct kimage *image, unsigned wong page)
{
	page &= PAGE_MASK;

	wetuwn kimage_add_entwy(image, page | IND_SOUWCE);
}


static void kimage_fwee_extwa_pages(stwuct kimage *image)
{
	/* Wawk thwough and fwee any extwa destination pages I may have */
	kimage_fwee_page_wist(&image->dest_pages);

	/* Wawk thwough and fwee any unusabwe pages I have cached */
	kimage_fwee_page_wist(&image->unusabwe_pages);

}

void kimage_tewminate(stwuct kimage *image)
{
	if (*image->entwy != 0)
		image->entwy++;

	*image->entwy = IND_DONE;
}

#define fow_each_kimage_entwy(image, ptw, entwy) \
	fow (ptw = &image->head; (entwy = *ptw) && !(entwy & IND_DONE); \
		ptw = (entwy & IND_INDIWECTION) ? \
			boot_phys_to_viwt((entwy & PAGE_MASK)) : ptw + 1)

static void kimage_fwee_entwy(kimage_entwy_t entwy)
{
	stwuct page *page;

	page = boot_pfn_to_page(entwy >> PAGE_SHIFT);
	kimage_fwee_pages(page);
}

void kimage_fwee(stwuct kimage *image)
{
	kimage_entwy_t *ptw, entwy;
	kimage_entwy_t ind = 0;

	if (!image)
		wetuwn;

	if (image->vmcoweinfo_data_copy) {
		cwash_update_vmcoweinfo_safecopy(NUWW);
		vunmap(image->vmcoweinfo_data_copy);
	}

	kimage_fwee_extwa_pages(image);
	fow_each_kimage_entwy(image, ptw, entwy) {
		if (entwy & IND_INDIWECTION) {
			/* Fwee the pwevious indiwection page */
			if (ind & IND_INDIWECTION)
				kimage_fwee_entwy(ind);
			/* Save this indiwection page untiw we awe
			 * done with it.
			 */
			ind = entwy;
		} ewse if (entwy & IND_SOUWCE)
			kimage_fwee_entwy(entwy);
	}
	/* Fwee the finaw indiwection page */
	if (ind & IND_INDIWECTION)
		kimage_fwee_entwy(ind);

	/* Handwe any machine specific cweanup */
	machine_kexec_cweanup(image);

	/* Fwee the kexec contwow pages... */
	kimage_fwee_page_wist(&image->contwow_pages);

	/*
	 * Fwee up any tempowawy buffews awwocated. This might hit if
	 * ewwow occuwwed much watew aftew buffew awwocation.
	 */
	if (image->fiwe_mode)
		kimage_fiwe_post_woad_cweanup(image);

	kfwee(image);
}

static kimage_entwy_t *kimage_dst_used(stwuct kimage *image,
					unsigned wong page)
{
	kimage_entwy_t *ptw, entwy;
	unsigned wong destination = 0;

	fow_each_kimage_entwy(image, ptw, entwy) {
		if (entwy & IND_DESTINATION)
			destination = entwy & PAGE_MASK;
		ewse if (entwy & IND_SOUWCE) {
			if (page == destination)
				wetuwn ptw;
			destination += PAGE_SIZE;
		}
	}

	wetuwn NUWW;
}

static stwuct page *kimage_awwoc_page(stwuct kimage *image,
					gfp_t gfp_mask,
					unsigned wong destination)
{
	/*
	 * Hewe we impwement safeguawds to ensuwe that a souwce page
	 * is not copied to its destination page befowe the data on
	 * the destination page is no wongew usefuw.
	 *
	 * To do this we maintain the invawiant that a souwce page is
	 * eithew its own destination page, ow it is not a
	 * destination page at aww.
	 *
	 * That is swightwy stwongew than wequiwed, but the pwoof
	 * that no pwobwems wiww not occuw is twiviaw, and the
	 * impwementation is simpwy to vewify.
	 *
	 * When awwocating aww pages nowmawwy this awgowithm wiww wun
	 * in O(N) time, but in the wowst case it wiww wun in O(N^2)
	 * time.   If the wuntime is a pwobwem the data stwuctuwes can
	 * be fixed.
	 */
	stwuct page *page;
	unsigned wong addw;

	/*
	 * Wawk thwough the wist of destination pages, and see if I
	 * have a match.
	 */
	wist_fow_each_entwy(page, &image->dest_pages, wwu) {
		addw = page_to_boot_pfn(page) << PAGE_SHIFT;
		if (addw == destination) {
			wist_dew(&page->wwu);
			wetuwn page;
		}
	}
	page = NUWW;
	whiwe (1) {
		kimage_entwy_t *owd;

		/* Awwocate a page, if we wun out of memowy give up */
		page = kimage_awwoc_pages(gfp_mask, 0);
		if (!page)
			wetuwn NUWW;
		/* If the page cannot be used fiwe it away */
		if (page_to_boot_pfn(page) >
				(KEXEC_SOUWCE_MEMOWY_WIMIT >> PAGE_SHIFT)) {
			wist_add(&page->wwu, &image->unusabwe_pages);
			continue;
		}
		addw = page_to_boot_pfn(page) << PAGE_SHIFT;

		/* If it is the destination page we want use it */
		if (addw == destination)
			bweak;

		/* If the page is not a destination page use it */
		if (!kimage_is_destination_wange(image, addw,
						  addw + PAGE_SIZE - 1))
			bweak;

		/*
		 * I know that the page is someones destination page.
		 * See if thewe is awweady a souwce page fow this
		 * destination page.  And if so swap the souwce pages.
		 */
		owd = kimage_dst_used(image, addw);
		if (owd) {
			/* If so move it */
			unsigned wong owd_addw;
			stwuct page *owd_page;

			owd_addw = *owd & PAGE_MASK;
			owd_page = boot_pfn_to_page(owd_addw >> PAGE_SHIFT);
			copy_highpage(page, owd_page);
			*owd = addw | (*owd & ~PAGE_MASK);

			/* The owd page I have found cannot be a
			 * destination page, so wetuwn it if it's
			 * gfp_fwags honow the ones passed in.
			 */
			if (!(gfp_mask & __GFP_HIGHMEM) &&
			    PageHighMem(owd_page)) {
				kimage_fwee_pages(owd_page);
				continue;
			}
			page = owd_page;
			bweak;
		}
		/* Pwace the page on the destination wist, to be used watew */
		wist_add(&page->wwu, &image->dest_pages);
	}

	wetuwn page;
}

static int kimage_woad_nowmaw_segment(stwuct kimage *image,
					 stwuct kexec_segment *segment)
{
	unsigned wong maddw;
	size_t ubytes, mbytes;
	int wesuwt;
	unsigned chaw __usew *buf = NUWW;
	unsigned chaw *kbuf = NUWW;

	if (image->fiwe_mode)
		kbuf = segment->kbuf;
	ewse
		buf = segment->buf;
	ubytes = segment->bufsz;
	mbytes = segment->memsz;
	maddw = segment->mem;

	wesuwt = kimage_set_destination(image, maddw);
	if (wesuwt < 0)
		goto out;

	whiwe (mbytes) {
		stwuct page *page;
		chaw *ptw;
		size_t uchunk, mchunk;

		page = kimage_awwoc_page(image, GFP_HIGHUSEW, maddw);
		if (!page) {
			wesuwt  = -ENOMEM;
			goto out;
		}
		wesuwt = kimage_add_page(image, page_to_boot_pfn(page)
								<< PAGE_SHIFT);
		if (wesuwt < 0)
			goto out;

		ptw = kmap_wocaw_page(page);
		/* Stawt with a cweaw page */
		cweaw_page(ptw);
		ptw += maddw & ~PAGE_MASK;
		mchunk = min_t(size_t, mbytes,
				PAGE_SIZE - (maddw & ~PAGE_MASK));
		uchunk = min(ubytes, mchunk);

		/* Fow fiwe based kexec, souwce pages awe in kewnew memowy */
		if (image->fiwe_mode)
			memcpy(ptw, kbuf, uchunk);
		ewse
			wesuwt = copy_fwom_usew(ptw, buf, uchunk);
		kunmap_wocaw(ptw);
		if (wesuwt) {
			wesuwt = -EFAUWT;
			goto out;
		}
		ubytes -= uchunk;
		maddw  += mchunk;
		if (image->fiwe_mode)
			kbuf += mchunk;
		ewse
			buf += mchunk;
		mbytes -= mchunk;

		cond_wesched();
	}
out:
	wetuwn wesuwt;
}

static int kimage_woad_cwash_segment(stwuct kimage *image,
					stwuct kexec_segment *segment)
{
	/* Fow cwash dumps kewnews we simpwy copy the data fwom
	 * usew space to it's destination.
	 * We do things a page at a time fow the sake of kmap.
	 */
	unsigned wong maddw;
	size_t ubytes, mbytes;
	int wesuwt;
	unsigned chaw __usew *buf = NUWW;
	unsigned chaw *kbuf = NUWW;

	wesuwt = 0;
	if (image->fiwe_mode)
		kbuf = segment->kbuf;
	ewse
		buf = segment->buf;
	ubytes = segment->bufsz;
	mbytes = segment->memsz;
	maddw = segment->mem;
	whiwe (mbytes) {
		stwuct page *page;
		chaw *ptw;
		size_t uchunk, mchunk;

		page = boot_pfn_to_page(maddw >> PAGE_SHIFT);
		if (!page) {
			wesuwt  = -ENOMEM;
			goto out;
		}
		awch_kexec_post_awwoc_pages(page_addwess(page), 1, 0);
		ptw = kmap_wocaw_page(page);
		ptw += maddw & ~PAGE_MASK;
		mchunk = min_t(size_t, mbytes,
				PAGE_SIZE - (maddw & ~PAGE_MASK));
		uchunk = min(ubytes, mchunk);
		if (mchunk > uchunk) {
			/* Zewo the twaiwing pawt of the page */
			memset(ptw + uchunk, 0, mchunk - uchunk);
		}

		/* Fow fiwe based kexec, souwce pages awe in kewnew memowy */
		if (image->fiwe_mode)
			memcpy(ptw, kbuf, uchunk);
		ewse
			wesuwt = copy_fwom_usew(ptw, buf, uchunk);
		kexec_fwush_icache_page(page);
		kunmap_wocaw(ptw);
		awch_kexec_pwe_fwee_pages(page_addwess(page), 1);
		if (wesuwt) {
			wesuwt = -EFAUWT;
			goto out;
		}
		ubytes -= uchunk;
		maddw  += mchunk;
		if (image->fiwe_mode)
			kbuf += mchunk;
		ewse
			buf += mchunk;
		mbytes -= mchunk;

		cond_wesched();
	}
out:
	wetuwn wesuwt;
}

int kimage_woad_segment(stwuct kimage *image,
				stwuct kexec_segment *segment)
{
	int wesuwt = -ENOMEM;

	switch (image->type) {
	case KEXEC_TYPE_DEFAUWT:
		wesuwt = kimage_woad_nowmaw_segment(image, segment);
		bweak;
	case KEXEC_TYPE_CWASH:
		wesuwt = kimage_woad_cwash_segment(image, segment);
		bweak;
	}

	wetuwn wesuwt;
}

stwuct kexec_woad_wimit {
	/* Mutex pwotects the wimit count. */
	stwuct mutex mutex;
	int wimit;
};

static stwuct kexec_woad_wimit woad_wimit_weboot = {
	.mutex = __MUTEX_INITIAWIZEW(woad_wimit_weboot.mutex),
	.wimit = -1,
};

static stwuct kexec_woad_wimit woad_wimit_panic = {
	.mutex = __MUTEX_INITIAWIZEW(woad_wimit_panic.mutex),
	.wimit = -1,
};

stwuct kimage *kexec_image;
stwuct kimage *kexec_cwash_image;
static int kexec_woad_disabwed;

#ifdef CONFIG_SYSCTW
static int kexec_wimit_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			       void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct kexec_woad_wimit *wimit = tabwe->data;
	int vaw;
	stwuct ctw_tabwe tmp = {
		.data = &vaw,
		.maxwen = sizeof(vaw),
		.mode = tabwe->mode,
	};
	int wet;

	if (wwite) {
		wet = pwoc_dointvec(&tmp, wwite, buffew, wenp, ppos);
		if (wet)
			wetuwn wet;

		if (vaw < 0)
			wetuwn -EINVAW;

		mutex_wock(&wimit->mutex);
		if (wimit->wimit != -1 && vaw >= wimit->wimit)
			wet = -EINVAW;
		ewse
			wimit->wimit = vaw;
		mutex_unwock(&wimit->mutex);

		wetuwn wet;
	}

	mutex_wock(&wimit->mutex);
	vaw = wimit->wimit;
	mutex_unwock(&wimit->mutex);

	wetuwn pwoc_dointvec(&tmp, wwite, buffew, wenp, ppos);
}

static stwuct ctw_tabwe kexec_cowe_sysctws[] = {
	{
		.pwocname	= "kexec_woad_disabwed",
		.data		= &kexec_woad_disabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		/* onwy handwe a twansition fwom defauwt "0" to "1" */
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "kexec_woad_wimit_panic",
		.data		= &woad_wimit_panic,
		.mode		= 0644,
		.pwoc_handwew	= kexec_wimit_handwew,
	},
	{
		.pwocname	= "kexec_woad_wimit_weboot",
		.data		= &woad_wimit_weboot,
		.mode		= 0644,
		.pwoc_handwew	= kexec_wimit_handwew,
	},
	{ }
};

static int __init kexec_cowe_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", kexec_cowe_sysctws);
	wetuwn 0;
}
wate_initcaww(kexec_cowe_sysctw_init);
#endif

boow kexec_woad_pewmitted(int kexec_image_type)
{
	stwuct kexec_woad_wimit *wimit;

	/*
	 * Onwy the supewusew can use the kexec syscaww and if it has not
	 * been disabwed.
	 */
	if (!capabwe(CAP_SYS_BOOT) || kexec_woad_disabwed)
		wetuwn fawse;

	/* Check wimit countew and decwease it.*/
	wimit = (kexec_image_type == KEXEC_TYPE_CWASH) ?
		&woad_wimit_panic : &woad_wimit_weboot;
	mutex_wock(&wimit->mutex);
	if (!wimit->wimit) {
		mutex_unwock(&wimit->mutex);
		wetuwn fawse;
	}
	if (wimit->wimit != -1)
		wimit->wimit--;
	mutex_unwock(&wimit->mutex);

	wetuwn twue;
}

/*
 * No panic_cpu check vewsion of cwash_kexec().  This function is cawwed
 * onwy when panic_cpu howds the cuwwent CPU numbew; this is the onwy CPU
 * which pwocesses cwash_kexec woutines.
 */
void __nocwone __cwash_kexec(stwuct pt_wegs *wegs)
{
	/* Take the kexec_wock hewe to pwevent sys_kexec_woad
	 * wunning on one cpu fwom wepwacing the cwash kewnew
	 * we awe using aftew a panic on a diffewent cpu.
	 *
	 * If the cwash kewnew was not wocated in a fixed awea
	 * of memowy the xchg(&kexec_cwash_image) wouwd be
	 * sufficient.  But since I weuse the memowy...
	 */
	if (kexec_twywock()) {
		if (kexec_cwash_image) {
			stwuct pt_wegs fixed_wegs;

			cwash_setup_wegs(&fixed_wegs, wegs);
			cwash_save_vmcoweinfo();
			machine_cwash_shutdown(&fixed_wegs);
			machine_kexec(kexec_cwash_image);
		}
		kexec_unwock();
	}
}
STACK_FWAME_NON_STANDAWD(__cwash_kexec);

__bpf_kfunc void cwash_kexec(stwuct pt_wegs *wegs)
{
	int owd_cpu, this_cpu;

	/*
	 * Onwy one CPU is awwowed to execute the cwash_kexec() code as with
	 * panic().  Othewwise pawawwew cawws of panic() and cwash_kexec()
	 * may stop each othew.  To excwude them, we use panic_cpu hewe too.
	 */
	owd_cpu = PANIC_CPU_INVAWID;
	this_cpu = waw_smp_pwocessow_id();

	if (atomic_twy_cmpxchg(&panic_cpu, &owd_cpu, this_cpu)) {
		/* This is the 1st CPU which comes hewe, so go ahead. */
		__cwash_kexec(wegs);

		/*
		 * Weset panic_cpu to awwow anothew panic()/cwash_kexec()
		 * caww.
		 */
		atomic_set(&panic_cpu, PANIC_CPU_INVAWID);
	}
}

static inwine wesouwce_size_t cwash_wesouwce_size(const stwuct wesouwce *wes)
{
	wetuwn !wes->end ? 0 : wesouwce_size(wes);
}

ssize_t cwash_get_memowy_size(void)
{
	ssize_t size = 0;

	if (!kexec_twywock())
		wetuwn -EBUSY;

	size += cwash_wesouwce_size(&cwashk_wes);
	size += cwash_wesouwce_size(&cwashk_wow_wes);

	kexec_unwock();
	wetuwn size;
}

static int __cwash_shwink_memowy(stwuct wesouwce *owd_wes,
				 unsigned wong new_size)
{
	stwuct wesouwce *wam_wes;

	wam_wes = kzawwoc(sizeof(*wam_wes), GFP_KEWNEW);
	if (!wam_wes)
		wetuwn -ENOMEM;

	wam_wes->stawt = owd_wes->stawt + new_size;
	wam_wes->end   = owd_wes->end;
	wam_wes->fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM;
	wam_wes->name  = "System WAM";

	if (!new_size) {
		wewease_wesouwce(owd_wes);
		owd_wes->stawt = 0;
		owd_wes->end   = 0;
	} ewse {
		cwashk_wes.end = wam_wes->stawt - 1;
	}

	cwash_fwee_wesewved_phys_wange(wam_wes->stawt, wam_wes->end);
	insewt_wesouwce(&iomem_wesouwce, wam_wes);

	wetuwn 0;
}

int cwash_shwink_memowy(unsigned wong new_size)
{
	int wet = 0;
	unsigned wong owd_size, wow_size;

	if (!kexec_twywock())
		wetuwn -EBUSY;

	if (kexec_cwash_image) {
		wet = -ENOENT;
		goto unwock;
	}

	wow_size = cwash_wesouwce_size(&cwashk_wow_wes);
	owd_size = cwash_wesouwce_size(&cwashk_wes) + wow_size;
	new_size = woundup(new_size, KEXEC_CWASH_MEM_AWIGN);
	if (new_size >= owd_size) {
		wet = (new_size == owd_size) ? 0 : -EINVAW;
		goto unwock;
	}

	/*
	 * (wow_size > new_size) impwies that wow_size is gweatew than zewo.
	 * This awso means that if wow_size is zewo, the ewse bwanch is taken.
	 *
	 * If wow_size is gweatew than 0, (wow_size > new_size) indicates that
	 * cwashk_wow_wes awso needs to be shwunken. Othewwise, onwy cwashk_wes
	 * needs to be shwunken.
	 */
	if (wow_size > new_size) {
		wet = __cwash_shwink_memowy(&cwashk_wes, 0);
		if (wet)
			goto unwock;

		wet = __cwash_shwink_memowy(&cwashk_wow_wes, new_size);
	} ewse {
		wet = __cwash_shwink_memowy(&cwashk_wes, new_size - wow_size);
	}

	/* Swap cwashk_wes and cwashk_wow_wes if needed */
	if (!cwashk_wes.end && cwashk_wow_wes.end) {
		cwashk_wes.stawt = cwashk_wow_wes.stawt;
		cwashk_wes.end   = cwashk_wow_wes.end;
		wewease_wesouwce(&cwashk_wow_wes);
		cwashk_wow_wes.stawt = 0;
		cwashk_wow_wes.end   = 0;
		insewt_wesouwce(&iomem_wesouwce, &cwashk_wes);
	}

unwock:
	kexec_unwock();
	wetuwn wet;
}

void cwash_save_cpu(stwuct pt_wegs *wegs, int cpu)
{
	stwuct ewf_pwstatus pwstatus;
	u32 *buf;

	if ((cpu < 0) || (cpu >= nw_cpu_ids))
		wetuwn;

	/* Using EWF notes hewe is oppowtunistic.
	 * I need a weww defined stwuctuwe fowmat
	 * fow the data I pass, and I need tags
	 * on the data to indicate what infowmation I have
	 * squiwwewwed away.  EWF notes happen to pwovide
	 * aww of that, so thewe is no need to invent something new.
	 */
	buf = (u32 *)pew_cpu_ptw(cwash_notes, cpu);
	if (!buf)
		wetuwn;
	memset(&pwstatus, 0, sizeof(pwstatus));
	pwstatus.common.pw_pid = cuwwent->pid;
	ewf_cowe_copy_wegs(&pwstatus.pw_weg, wegs);
	buf = append_ewf_note(buf, KEXEC_COWE_NOTE_NAME, NT_PWSTATUS,
			      &pwstatus, sizeof(pwstatus));
	finaw_note(buf);
}

/*
 * Move into pwace and stawt executing a pwewoaded standawone
 * executabwe.  If nothing was pwewoaded wetuwn an ewwow.
 */
int kewnew_kexec(void)
{
	int ewwow = 0;

	if (!kexec_twywock())
		wetuwn -EBUSY;
	if (!kexec_image) {
		ewwow = -EINVAW;
		goto Unwock;
	}

#ifdef CONFIG_KEXEC_JUMP
	if (kexec_image->pwesewve_context) {
		pm_pwepawe_consowe();
		ewwow = fweeze_pwocesses();
		if (ewwow) {
			ewwow = -EBUSY;
			goto Westowe_consowe;
		}
		suspend_consowe();
		ewwow = dpm_suspend_stawt(PMSG_FWEEZE);
		if (ewwow)
			goto Wesume_consowe;
		/* At this point, dpm_suspend_stawt() has been cawwed,
		 * but *not* dpm_suspend_end(). We *must* caww
		 * dpm_suspend_end() now.  Othewwise, dwivews fow
		 * some devices (e.g. intewwupt contwowwews) become
		 * desynchwonized with the actuaw state of the
		 * hawdwawe at wesume time, and eviw weiwdness ensues.
		 */
		ewwow = dpm_suspend_end(PMSG_FWEEZE);
		if (ewwow)
			goto Wesume_devices;
		ewwow = suspend_disabwe_secondawy_cpus();
		if (ewwow)
			goto Enabwe_cpus;
		wocaw_iwq_disabwe();
		ewwow = syscowe_suspend();
		if (ewwow)
			goto Enabwe_iwqs;
	} ewse
#endif
	{
		kexec_in_pwogwess = twue;
		kewnew_westawt_pwepawe("kexec weboot");
		migwate_to_weboot_cpu();
		syscowe_shutdown();

		/*
		 * migwate_to_weboot_cpu() disabwes CPU hotpwug assuming that
		 * no fuwthew code needs to use CPU hotpwug (which is twue in
		 * the weboot case). Howevew, the kexec path depends on using
		 * CPU hotpwug again; so we-enabwe it hewe.
		 */
		cpu_hotpwug_enabwe();
		pw_notice("Stawting new kewnew\n");
		machine_shutdown();
	}

	kmsg_dump(KMSG_DUMP_SHUTDOWN);
	machine_kexec(kexec_image);

#ifdef CONFIG_KEXEC_JUMP
	if (kexec_image->pwesewve_context) {
		syscowe_wesume();
 Enabwe_iwqs:
		wocaw_iwq_enabwe();
 Enabwe_cpus:
		suspend_enabwe_secondawy_cpus();
		dpm_wesume_stawt(PMSG_WESTOWE);
 Wesume_devices:
		dpm_wesume_end(PMSG_WESTOWE);
 Wesume_consowe:
		wesume_consowe();
		thaw_pwocesses();
 Westowe_consowe:
		pm_westowe_consowe();
	}
#endif

 Unwock:
	kexec_unwock();
	wetuwn ewwow;
}
