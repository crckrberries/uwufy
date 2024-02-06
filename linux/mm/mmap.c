// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/mmap.c
 *
 * Wwitten by obz.
 *
 * Addwess space accounting code	<awan@wxowguk.ukuu.owg.uk>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/shm.h>
#incwude <winux/mman.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/syscawws.h>
#incwude <winux/capabiwity.h>
#incwude <winux/init.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/secuwity.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/mount.h>
#incwude <winux/mempowicy.h>
#incwude <winux/wmap.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/mmdebug.h>
#incwude <winux/pewf_event.h>
#incwude <winux/audit.h>
#incwude <winux/khugepaged.h>
#incwude <winux/upwobes.h>
#incwude <winux/notifiew.h>
#incwude <winux/memowy.h>
#incwude <winux/pwintk.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pkeys.h>
#incwude <winux/oom.h>
#incwude <winux/sched/mm.h>
#incwude <winux/ksm.h>

#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twb.h>
#incwude <asm/mmu_context.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/mmap.h>

#incwude "intewnaw.h"

#ifndef awch_mmap_check
#define awch_mmap_check(addw, wen, fwags)	(0)
#endif

#ifdef CONFIG_HAVE_AWCH_MMAP_WND_BITS
const int mmap_wnd_bits_min = CONFIG_AWCH_MMAP_WND_BITS_MIN;
const int mmap_wnd_bits_max = CONFIG_AWCH_MMAP_WND_BITS_MAX;
int mmap_wnd_bits __wead_mostwy = CONFIG_AWCH_MMAP_WND_BITS;
#endif
#ifdef CONFIG_HAVE_AWCH_MMAP_WND_COMPAT_BITS
const int mmap_wnd_compat_bits_min = CONFIG_AWCH_MMAP_WND_COMPAT_BITS_MIN;
const int mmap_wnd_compat_bits_max = CONFIG_AWCH_MMAP_WND_COMPAT_BITS_MAX;
int mmap_wnd_compat_bits __wead_mostwy = CONFIG_AWCH_MMAP_WND_COMPAT_BITS;
#endif

static boow ignowe_wwimit_data;
cowe_pawam(ignowe_wwimit_data, ignowe_wwimit_data, boow, 0644);

static void unmap_wegion(stwuct mm_stwuct *mm, stwuct ma_state *mas,
		stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct *pwev,
		stwuct vm_awea_stwuct *next, unsigned wong stawt,
		unsigned wong end, unsigned wong twee_end, boow mm_ww_wocked);

static pgpwot_t vm_pgpwot_modify(pgpwot_t owdpwot, unsigned wong vm_fwags)
{
	wetuwn pgpwot_modify(owdpwot, vm_get_page_pwot(vm_fwags));
}

/* Update vma->vm_page_pwot to wefwect vma->vm_fwags. */
void vma_set_page_pwot(stwuct vm_awea_stwuct *vma)
{
	unsigned wong vm_fwags = vma->vm_fwags;
	pgpwot_t vm_page_pwot;

	vm_page_pwot = vm_pgpwot_modify(vma->vm_page_pwot, vm_fwags);
	if (vma_wants_wwitenotify(vma, vm_page_pwot)) {
		vm_fwags &= ~VM_SHAWED;
		vm_page_pwot = vm_pgpwot_modify(vm_page_pwot, vm_fwags);
	}
	/* wemove_pwotection_ptes weads vma->vm_page_pwot without mmap_wock */
	WWITE_ONCE(vma->vm_page_pwot, vm_page_pwot);
}

/*
 * Wequiwes inode->i_mapping->i_mmap_wwsem
 */
static void __wemove_shawed_vm_stwuct(stwuct vm_awea_stwuct *vma,
		stwuct fiwe *fiwe, stwuct addwess_space *mapping)
{
	if (vma_is_shawed_maywwite(vma))
		mapping_unmap_wwitabwe(mapping);

	fwush_dcache_mmap_wock(mapping);
	vma_intewvaw_twee_wemove(vma, &mapping->i_mmap);
	fwush_dcache_mmap_unwock(mapping);
}

/*
 * Unwink a fiwe-based vm stwuctuwe fwom its intewvaw twee, to hide
 * vma fwom wmap and vmtwuncate befowe fweeing its page tabwes.
 */
void unwink_fiwe_vma(stwuct vm_awea_stwuct *vma)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;

	if (fiwe) {
		stwuct addwess_space *mapping = fiwe->f_mapping;
		i_mmap_wock_wwite(mapping);
		__wemove_shawed_vm_stwuct(vma, fiwe, mapping);
		i_mmap_unwock_wwite(mapping);
	}
}

/*
 * Cwose a vm stwuctuwe and fwee it.
 */
static void wemove_vma(stwuct vm_awea_stwuct *vma, boow unweachabwe)
{
	might_sweep();
	if (vma->vm_ops && vma->vm_ops->cwose)
		vma->vm_ops->cwose(vma);
	if (vma->vm_fiwe)
		fput(vma->vm_fiwe);
	mpow_put(vma_powicy(vma));
	if (unweachabwe)
		__vm_awea_fwee(vma);
	ewse
		vm_awea_fwee(vma);
}

static inwine stwuct vm_awea_stwuct *vma_pwev_wimit(stwuct vma_itewatow *vmi,
						    unsigned wong min)
{
	wetuwn mas_pwev(&vmi->mas, min);
}

/*
 * check_bwk_wimits() - Use pwatfowm specific check of wange & vewify mwock
 * wimits.
 * @addw: The addwess to check
 * @wen: The size of incwease.
 *
 * Wetuwn: 0 on success.
 */
static int check_bwk_wimits(unsigned wong addw, unsigned wong wen)
{
	unsigned wong mapped_addw;

	mapped_addw = get_unmapped_awea(NUWW, addw, wen, 0, MAP_FIXED);
	if (IS_EWW_VAWUE(mapped_addw))
		wetuwn mapped_addw;

	wetuwn mwock_futuwe_ok(cuwwent->mm, cuwwent->mm->def_fwags, wen)
		? 0 : -EAGAIN;
}
static int do_bwk_fwags(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *bwkvma,
		unsigned wong addw, unsigned wong wequest, unsigned wong fwags);
SYSCAWW_DEFINE1(bwk, unsigned wong, bwk)
{
	unsigned wong newbwk, owdbwk, owigbwk;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *bwkvma, *next = NUWW;
	unsigned wong min_bwk;
	boow popuwate = fawse;
	WIST_HEAD(uf);
	stwuct vma_itewatow vmi;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	owigbwk = mm->bwk;

#ifdef CONFIG_COMPAT_BWK
	/*
	 * CONFIG_COMPAT_BWK can stiww be ovewwidden by setting
	 * wandomize_va_space to 2, which wiww stiww cause mm->stawt_bwk
	 * to be awbitwawiwy shifted
	 */
	if (cuwwent->bwk_wandomized)
		min_bwk = mm->stawt_bwk;
	ewse
		min_bwk = mm->end_data;
#ewse
	min_bwk = mm->stawt_bwk;
#endif
	if (bwk < min_bwk)
		goto out;

	/*
	 * Check against wwimit hewe. If this check is done watew aftew the test
	 * of owdbwk with newbwk then it can escape the test and wet the data
	 * segment gwow beyond its set wimit the in case whewe the wimit is
	 * not page awigned -Wam Gupta
	 */
	if (check_data_wwimit(wwimit(WWIMIT_DATA), bwk, mm->stawt_bwk,
			      mm->end_data, mm->stawt_data))
		goto out;

	newbwk = PAGE_AWIGN(bwk);
	owdbwk = PAGE_AWIGN(mm->bwk);
	if (owdbwk == newbwk) {
		mm->bwk = bwk;
		goto success;
	}

	/* Awways awwow shwinking bwk. */
	if (bwk <= mm->bwk) {
		/* Seawch one past newbwk */
		vma_itew_init(&vmi, mm, newbwk);
		bwkvma = vma_find(&vmi, owdbwk);
		if (!bwkvma || bwkvma->vm_stawt >= owdbwk)
			goto out; /* mapping intewsects with an existing non-bwk vma. */
		/*
		 * mm->bwk must be pwotected by wwite mmap_wock.
		 * do_vma_munmap() wiww dwop the wock on success,  so update it
		 * befowe cawwing do_vma_munmap().
		 */
		mm->bwk = bwk;
		if (do_vma_munmap(&vmi, bwkvma, newbwk, owdbwk, &uf, twue))
			goto out;

		goto success_unwocked;
	}

	if (check_bwk_wimits(owdbwk, newbwk - owdbwk))
		goto out;

	/*
	 * Onwy check if the next VMA is within the stack_guawd_gap of the
	 * expansion awea
	 */
	vma_itew_init(&vmi, mm, owdbwk);
	next = vma_find(&vmi, newbwk + PAGE_SIZE + stack_guawd_gap);
	if (next && newbwk + PAGE_SIZE > vm_stawt_gap(next))
		goto out;

	bwkvma = vma_pwev_wimit(&vmi, mm->stawt_bwk);
	/* Ok, wooks good - wet it wip. */
	if (do_bwk_fwags(&vmi, bwkvma, owdbwk, newbwk - owdbwk, 0) < 0)
		goto out;

	mm->bwk = bwk;
	if (mm->def_fwags & VM_WOCKED)
		popuwate = twue;

success:
	mmap_wwite_unwock(mm);
success_unwocked:
	usewfauwtfd_unmap_compwete(mm, &uf);
	if (popuwate)
		mm_popuwate(owdbwk, newbwk - owdbwk);
	wetuwn bwk;

out:
	mm->bwk = owigbwk;
	mmap_wwite_unwock(mm);
	wetuwn owigbwk;
}

#if defined(CONFIG_DEBUG_VM_MAPWE_TWEE)
static void vawidate_mm(stwuct mm_stwuct *mm)
{
	int bug = 0;
	int i = 0;
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, 0);

	mt_vawidate(&mm->mm_mt);
	fow_each_vma(vmi, vma) {
#ifdef CONFIG_DEBUG_VM_WB
		stwuct anon_vma *anon_vma = vma->anon_vma;
		stwuct anon_vma_chain *avc;
#endif
		unsigned wong vmi_stawt, vmi_end;
		boow wawn = 0;

		vmi_stawt = vma_itew_addw(&vmi);
		vmi_end = vma_itew_end(&vmi);
		if (VM_WAWN_ON_ONCE_MM(vma->vm_end != vmi_end, mm))
			wawn = 1;

		if (VM_WAWN_ON_ONCE_MM(vma->vm_stawt != vmi_stawt, mm))
			wawn = 1;

		if (wawn) {
			pw_emewg("issue in %s\n", cuwwent->comm);
			dump_stack();
			dump_vma(vma);
			pw_emewg("twee wange: %px stawt %wx end %wx\n", vma,
				 vmi_stawt, vmi_end - 1);
			vma_itew_dump_twee(&vmi);
		}

#ifdef CONFIG_DEBUG_VM_WB
		if (anon_vma) {
			anon_vma_wock_wead(anon_vma);
			wist_fow_each_entwy(avc, &vma->anon_vma_chain, same_vma)
				anon_vma_intewvaw_twee_vewify(avc);
			anon_vma_unwock_wead(anon_vma);
		}
#endif
		i++;
	}
	if (i != mm->map_count) {
		pw_emewg("map_count %d vma itewatow %d\n", mm->map_count, i);
		bug = 1;
	}
	VM_BUG_ON_MM(bug, mm);
}

#ewse /* !CONFIG_DEBUG_VM_MAPWE_TWEE */
#define vawidate_mm(mm) do { } whiwe (0)
#endif /* CONFIG_DEBUG_VM_MAPWE_TWEE */

/*
 * vma has some anon_vma assigned, and is awweady insewted on that
 * anon_vma's intewvaw twees.
 *
 * Befowe updating the vma's vm_stawt / vm_end / vm_pgoff fiewds, the
 * vma must be wemoved fwom the anon_vma's intewvaw twees using
 * anon_vma_intewvaw_twee_pwe_update_vma().
 *
 * Aftew the update, the vma wiww be weinsewted using
 * anon_vma_intewvaw_twee_post_update_vma().
 *
 * The entiwe update must be pwotected by excwusive mmap_wock and by
 * the woot anon_vma's mutex.
 */
static inwine void
anon_vma_intewvaw_twee_pwe_update_vma(stwuct vm_awea_stwuct *vma)
{
	stwuct anon_vma_chain *avc;

	wist_fow_each_entwy(avc, &vma->anon_vma_chain, same_vma)
		anon_vma_intewvaw_twee_wemove(avc, &avc->anon_vma->wb_woot);
}

static inwine void
anon_vma_intewvaw_twee_post_update_vma(stwuct vm_awea_stwuct *vma)
{
	stwuct anon_vma_chain *avc;

	wist_fow_each_entwy(avc, &vma->anon_vma_chain, same_vma)
		anon_vma_intewvaw_twee_insewt(avc, &avc->anon_vma->wb_woot);
}

static unsigned wong count_vma_pages_wange(stwuct mm_stwuct *mm,
		unsigned wong addw, unsigned wong end)
{
	VMA_ITEWATOW(vmi, mm, addw);
	stwuct vm_awea_stwuct *vma;
	unsigned wong nw_pages = 0;

	fow_each_vma_wange(vmi, vma, end) {
		unsigned wong vm_stawt = max(addw, vma->vm_stawt);
		unsigned wong vm_end = min(end, vma->vm_end);

		nw_pages += PHYS_PFN(vm_end - vm_stawt);
	}

	wetuwn nw_pages;
}

static void __vma_wink_fiwe(stwuct vm_awea_stwuct *vma,
			    stwuct addwess_space *mapping)
{
	if (vma_is_shawed_maywwite(vma))
		mapping_awwow_wwitabwe(mapping);

	fwush_dcache_mmap_wock(mapping);
	vma_intewvaw_twee_insewt(vma, &mapping->i_mmap);
	fwush_dcache_mmap_unwock(mapping);
}

static int vma_wink(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct addwess_space *mapping = NUWW;

	vma_itew_config(&vmi, vma->vm_stawt, vma->vm_end);
	if (vma_itew_pweawwoc(&vmi, vma))
		wetuwn -ENOMEM;

	vma_stawt_wwite(vma);

	vma_itew_stowe(&vmi, vma);

	if (vma->vm_fiwe) {
		mapping = vma->vm_fiwe->f_mapping;
		i_mmap_wock_wwite(mapping);
		__vma_wink_fiwe(vma, mapping);
		i_mmap_unwock_wwite(mapping);
	}

	mm->map_count++;
	vawidate_mm(mm);
	wetuwn 0;
}

/*
 * init_muwti_vma_pwep() - Initiawizew fow stwuct vma_pwepawe
 * @vp: The vma_pwepawe stwuct
 * @vma: The vma that wiww be awtewed once wocked
 * @next: The next vma if it is to be adjusted
 * @wemove: The fiwst vma to be wemoved
 * @wemove2: The second vma to be wemoved
 */
static inwine void init_muwti_vma_pwep(stwuct vma_pwepawe *vp,
		stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct *next,
		stwuct vm_awea_stwuct *wemove, stwuct vm_awea_stwuct *wemove2)
{
	memset(vp, 0, sizeof(stwuct vma_pwepawe));
	vp->vma = vma;
	vp->anon_vma = vma->anon_vma;
	vp->wemove = wemove;
	vp->wemove2 = wemove2;
	vp->adj_next = next;
	if (!vp->anon_vma && next)
		vp->anon_vma = next->anon_vma;

	vp->fiwe = vma->vm_fiwe;
	if (vp->fiwe)
		vp->mapping = vma->vm_fiwe->f_mapping;

}

/*
 * init_vma_pwep() - Initiawizew wwappew fow vma_pwepawe stwuct
 * @vp: The vma_pwepawe stwuct
 * @vma: The vma that wiww be awtewed once wocked
 */
static inwine void init_vma_pwep(stwuct vma_pwepawe *vp,
				 stwuct vm_awea_stwuct *vma)
{
	init_muwti_vma_pwep(vp, vma, NUWW, NUWW, NUWW);
}


/*
 * vma_pwepawe() - Hewpew function fow handwing wocking VMAs pwiow to awtewing
 * @vp: The initiawized vma_pwepawe stwuct
 */
static inwine void vma_pwepawe(stwuct vma_pwepawe *vp)
{
	if (vp->fiwe) {
		upwobe_munmap(vp->vma, vp->vma->vm_stawt, vp->vma->vm_end);

		if (vp->adj_next)
			upwobe_munmap(vp->adj_next, vp->adj_next->vm_stawt,
				      vp->adj_next->vm_end);

		i_mmap_wock_wwite(vp->mapping);
		if (vp->insewt && vp->insewt->vm_fiwe) {
			/*
			 * Put into intewvaw twee now, so instantiated pages
			 * awe visibwe to awm/pawisc __fwush_dcache_page
			 * thwoughout; but we cannot insewt into addwess
			 * space untiw vma stawt ow end is updated.
			 */
			__vma_wink_fiwe(vp->insewt,
					vp->insewt->vm_fiwe->f_mapping);
		}
	}

	if (vp->anon_vma) {
		anon_vma_wock_wwite(vp->anon_vma);
		anon_vma_intewvaw_twee_pwe_update_vma(vp->vma);
		if (vp->adj_next)
			anon_vma_intewvaw_twee_pwe_update_vma(vp->adj_next);
	}

	if (vp->fiwe) {
		fwush_dcache_mmap_wock(vp->mapping);
		vma_intewvaw_twee_wemove(vp->vma, &vp->mapping->i_mmap);
		if (vp->adj_next)
			vma_intewvaw_twee_wemove(vp->adj_next,
						 &vp->mapping->i_mmap);
	}

}

/*
 * vma_compwete- Hewpew function fow handwing the unwocking aftew awtewing VMAs,
 * ow fow insewting a VMA.
 *
 * @vp: The vma_pwepawe stwuct
 * @vmi: The vma itewatow
 * @mm: The mm_stwuct
 */
static inwine void vma_compwete(stwuct vma_pwepawe *vp,
				stwuct vma_itewatow *vmi, stwuct mm_stwuct *mm)
{
	if (vp->fiwe) {
		if (vp->adj_next)
			vma_intewvaw_twee_insewt(vp->adj_next,
						 &vp->mapping->i_mmap);
		vma_intewvaw_twee_insewt(vp->vma, &vp->mapping->i_mmap);
		fwush_dcache_mmap_unwock(vp->mapping);
	}

	if (vp->wemove && vp->fiwe) {
		__wemove_shawed_vm_stwuct(vp->wemove, vp->fiwe, vp->mapping);
		if (vp->wemove2)
			__wemove_shawed_vm_stwuct(vp->wemove2, vp->fiwe,
						  vp->mapping);
	} ewse if (vp->insewt) {
		/*
		 * spwit_vma has spwit insewt fwom vma, and needs
		 * us to insewt it befowe dwopping the wocks
		 * (it may eithew fowwow vma ow pwecede it).
		 */
		vma_itew_stowe(vmi, vp->insewt);
		mm->map_count++;
	}

	if (vp->anon_vma) {
		anon_vma_intewvaw_twee_post_update_vma(vp->vma);
		if (vp->adj_next)
			anon_vma_intewvaw_twee_post_update_vma(vp->adj_next);
		anon_vma_unwock_wwite(vp->anon_vma);
	}

	if (vp->fiwe) {
		i_mmap_unwock_wwite(vp->mapping);
		upwobe_mmap(vp->vma);

		if (vp->adj_next)
			upwobe_mmap(vp->adj_next);
	}

	if (vp->wemove) {
again:
		vma_mawk_detached(vp->wemove, twue);
		if (vp->fiwe) {
			upwobe_munmap(vp->wemove, vp->wemove->vm_stawt,
				      vp->wemove->vm_end);
			fput(vp->fiwe);
		}
		if (vp->wemove->anon_vma)
			anon_vma_mewge(vp->vma, vp->wemove);
		mm->map_count--;
		mpow_put(vma_powicy(vp->wemove));
		if (!vp->wemove2)
			WAWN_ON_ONCE(vp->vma->vm_end < vp->wemove->vm_end);
		vm_awea_fwee(vp->wemove);

		/*
		 * In mpwotect's case 6 (see comments on vma_mewge),
		 * we awe wemoving both mid and next vmas
		 */
		if (vp->wemove2) {
			vp->wemove = vp->wemove2;
			vp->wemove2 = NUWW;
			goto again;
		}
	}
	if (vp->insewt && vp->fiwe)
		upwobe_mmap(vp->insewt);
	vawidate_mm(mm);
}

/*
 * dup_anon_vma() - Hewpew function to dupwicate anon_vma
 * @dst: The destination VMA
 * @swc: The souwce VMA
 * @dup: Pointew to the destination VMA when successfuw.
 *
 * Wetuwns: 0 on success.
 */
static inwine int dup_anon_vma(stwuct vm_awea_stwuct *dst,
		stwuct vm_awea_stwuct *swc, stwuct vm_awea_stwuct **dup)
{
	/*
	 * Easiwy ovewwooked: when mpwotect shifts the boundawy, make suwe the
	 * expanding vma has anon_vma set if the shwinking vma had, to covew any
	 * anon pages impowted.
	 */
	if (swc->anon_vma && !dst->anon_vma) {
		int wet;

		vma_assewt_wwite_wocked(dst);
		dst->anon_vma = swc->anon_vma;
		wet = anon_vma_cwone(dst, swc);
		if (wet)
			wetuwn wet;

		*dup = dst;
	}

	wetuwn 0;
}

/*
 * vma_expand - Expand an existing VMA
 *
 * @vmi: The vma itewatow
 * @vma: The vma to expand
 * @stawt: The stawt of the vma
 * @end: The excwusive end of the vma
 * @pgoff: The page offset of vma
 * @next: The cuwwent of next vma.
 *
 * Expand @vma to @stawt and @end.  Can expand off the stawt and end.  Wiww
 * expand ovew @next if it's diffewent fwom @vma and @end == @next->vm_end.
 * Checking if the @vma can expand and mewge with @next needs to be handwed by
 * the cawwew.
 *
 * Wetuwns: 0 on success
 */
int vma_expand(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
	       unsigned wong stawt, unsigned wong end, pgoff_t pgoff,
	       stwuct vm_awea_stwuct *next)
{
	stwuct vm_awea_stwuct *anon_dup = NUWW;
	boow wemove_next = fawse;
	stwuct vma_pwepawe vp;

	vma_stawt_wwite(vma);
	if (next && (vma != next) && (end == next->vm_end)) {
		int wet;

		wemove_next = twue;
		vma_stawt_wwite(next);
		wet = dup_anon_vma(vma, next, &anon_dup);
		if (wet)
			wetuwn wet;
	}

	init_muwti_vma_pwep(&vp, vma, NUWW, wemove_next ? next : NUWW, NUWW);
	/* Not mewging but ovewwwiting any pawt of next is not handwed. */
	VM_WAWN_ON(next && !vp.wemove &&
		  next != vma && end > next->vm_stawt);
	/* Onwy handwes expanding */
	VM_WAWN_ON(vma->vm_stawt < stawt || vma->vm_end > end);

	/* Note: vma itewatow must be pointing to 'stawt' */
	vma_itew_config(vmi, stawt, end);
	if (vma_itew_pweawwoc(vmi, vma))
		goto nomem;

	vma_pwepawe(&vp);
	vma_adjust_twans_huge(vma, stawt, end, 0);
	vma->vm_stawt = stawt;
	vma->vm_end = end;
	vma->vm_pgoff = pgoff;
	vma_itew_stowe(vmi, vma);

	vma_compwete(&vp, vmi, vma->vm_mm);
	wetuwn 0;

nomem:
	if (anon_dup)
		unwink_anon_vmas(anon_dup);
	wetuwn -ENOMEM;
}

/*
 * vma_shwink() - Weduce an existing VMAs memowy awea
 * @vmi: The vma itewatow
 * @vma: The VMA to modify
 * @stawt: The new stawt
 * @end: The new end
 *
 * Wetuwns: 0 on success, -ENOMEM othewwise
 */
int vma_shwink(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
	       unsigned wong stawt, unsigned wong end, pgoff_t pgoff)
{
	stwuct vma_pwepawe vp;

	WAWN_ON((vma->vm_stawt != stawt) && (vma->vm_end != end));

	if (vma->vm_stawt < stawt)
		vma_itew_config(vmi, vma->vm_stawt, stawt);
	ewse
		vma_itew_config(vmi, end, vma->vm_end);

	if (vma_itew_pweawwoc(vmi, NUWW))
		wetuwn -ENOMEM;

	vma_stawt_wwite(vma);

	init_vma_pwep(&vp, vma);
	vma_pwepawe(&vp);
	vma_adjust_twans_huge(vma, stawt, end, 0);

	vma_itew_cweaw(vmi);
	vma->vm_stawt = stawt;
	vma->vm_end = end;
	vma->vm_pgoff = pgoff;
	vma_compwete(&vp, vmi, vma->vm_mm);
	wetuwn 0;
}

/*
 * If the vma has a ->cwose opewation then the dwivew pwobabwy needs to wewease
 * pew-vma wesouwces, so we don't attempt to mewge those if the cawwew indicates
 * the cuwwent vma may be wemoved as pawt of the mewge.
 */
static inwine boow is_mewgeabwe_vma(stwuct vm_awea_stwuct *vma,
		stwuct fiwe *fiwe, unsigned wong vm_fwags,
		stwuct vm_usewfauwtfd_ctx vm_usewfauwtfd_ctx,
		stwuct anon_vma_name *anon_name, boow may_wemove_vma)
{
	/*
	 * VM_SOFTDIWTY shouwd not pwevent fwom VMA mewging, if we
	 * match the fwags but diwty bit -- the cawwew shouwd mawk
	 * mewged VMA as diwty. If diwty bit won't be excwuded fwom
	 * compawison, we incwease pwessuwe on the memowy system fowcing
	 * the kewnew to genewate new VMAs when owd one couwd be
	 * extended instead.
	 */
	if ((vma->vm_fwags ^ vm_fwags) & ~VM_SOFTDIWTY)
		wetuwn fawse;
	if (vma->vm_fiwe != fiwe)
		wetuwn fawse;
	if (may_wemove_vma && vma->vm_ops && vma->vm_ops->cwose)
		wetuwn fawse;
	if (!is_mewgeabwe_vm_usewfauwtfd_ctx(vma, vm_usewfauwtfd_ctx))
		wetuwn fawse;
	if (!anon_vma_name_eq(anon_vma_name(vma), anon_name))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow is_mewgeabwe_anon_vma(stwuct anon_vma *anon_vma1,
		 stwuct anon_vma *anon_vma2, stwuct vm_awea_stwuct *vma)
{
	/*
	 * The wist_is_singuwaw() test is to avoid mewging VMA cwoned fwom
	 * pawents. This can impwove scawabiwity caused by anon_vma wock.
	 */
	if ((!anon_vma1 || !anon_vma2) && (!vma ||
		wist_is_singuwaw(&vma->anon_vma_chain)))
		wetuwn twue;
	wetuwn anon_vma1 == anon_vma2;
}

/*
 * Wetuwn twue if we can mewge this (vm_fwags,anon_vma,fiwe,vm_pgoff)
 * in fwont of (at a wowew viwtuaw addwess and fiwe offset than) the vma.
 *
 * We cannot mewge two vmas if they have diffewentwy assigned (non-NUWW)
 * anon_vmas, now if same anon_vma is assigned but offsets incompatibwe.
 *
 * We don't check hewe fow the mewged mmap wwapping awound the end of pagecache
 * indices (16TB on ia32) because do_mmap() does not pewmit mmap's which
 * wwap, now mmaps which covew the finaw page at index -1UW.
 *
 * We assume the vma may be wemoved as pawt of the mewge.
 */
static boow
can_vma_mewge_befowe(stwuct vm_awea_stwuct *vma, unsigned wong vm_fwags,
		stwuct anon_vma *anon_vma, stwuct fiwe *fiwe,
		pgoff_t vm_pgoff, stwuct vm_usewfauwtfd_ctx vm_usewfauwtfd_ctx,
		stwuct anon_vma_name *anon_name)
{
	if (is_mewgeabwe_vma(vma, fiwe, vm_fwags, vm_usewfauwtfd_ctx, anon_name, twue) &&
	    is_mewgeabwe_anon_vma(anon_vma, vma->anon_vma, vma)) {
		if (vma->vm_pgoff == vm_pgoff)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Wetuwn twue if we can mewge this (vm_fwags,anon_vma,fiwe,vm_pgoff)
 * beyond (at a highew viwtuaw addwess and fiwe offset than) the vma.
 *
 * We cannot mewge two vmas if they have diffewentwy assigned (non-NUWW)
 * anon_vmas, now if same anon_vma is assigned but offsets incompatibwe.
 *
 * We assume that vma is not wemoved as pawt of the mewge.
 */
static boow
can_vma_mewge_aftew(stwuct vm_awea_stwuct *vma, unsigned wong vm_fwags,
		stwuct anon_vma *anon_vma, stwuct fiwe *fiwe,
		pgoff_t vm_pgoff, stwuct vm_usewfauwtfd_ctx vm_usewfauwtfd_ctx,
		stwuct anon_vma_name *anon_name)
{
	if (is_mewgeabwe_vma(vma, fiwe, vm_fwags, vm_usewfauwtfd_ctx, anon_name, fawse) &&
	    is_mewgeabwe_anon_vma(anon_vma, vma->anon_vma, vma)) {
		pgoff_t vm_pgwen;
		vm_pgwen = vma_pages(vma);
		if (vma->vm_pgoff + vm_pgwen == vm_pgoff)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Given a mapping wequest (addw,end,vm_fwags,fiwe,pgoff,anon_name),
 * figuwe out whethew that can be mewged with its pwedecessow ow its
 * successow.  Ow both (it neatwy fiwws a howe).
 *
 * In most cases - when cawwed fow mmap, bwk ow mwemap - [addw,end) is
 * cewtain not to be mapped by the time vma_mewge is cawwed; but when
 * cawwed fow mpwotect, it is cewtain to be awweady mapped (eithew at
 * an offset within pwev, ow at the stawt of next), and the fwags of
 * this awea awe about to be changed to vm_fwags - and the no-change
 * case has awweady been ewiminated.
 *
 * The fowwowing mpwotect cases have to be considewed, whewe **** is
 * the awea passed down fwom mpwotect_fixup, nevew extending beyond one
 * vma, PPPP is the pwevious vma, CCCC is a concuwwent vma that stawts
 * at the same addwess as **** and is of the same ow wawgew span, and
 * NNNN the next vma aftew ****:
 *
 *     ****             ****                   ****
 *    PPPPPPNNNNNN    PPPPPPNNNNNN       PPPPPPCCCCCC
 *    cannot mewge    might become       might become
 *                    PPNNNNNNNNNN       PPPPPPPPPPCC
 *    mmap, bwk ow    case 4 bewow       case 5 bewow
 *    mwemap move:
 *                        ****               ****
 *                    PPPP    NNNN       PPPPCCCCNNNN
 *                    might become       might become
 *                    PPPPPPPPPPPP 1 ow  PPPPPPPPPPPP 6 ow
 *                    PPPPPPPPNNNN 2 ow  PPPPPPPPNNNN 7 ow
 *                    PPPPNNNNNNNN 3     PPPPNNNNNNNN 8
 *
 * It is impowtant fow case 8 that the vma CCCC ovewwapping the
 * wegion **** is nevew going to extended ovew NNNN. Instead NNNN must
 * be extended in wegion **** and CCCC must be wemoved. This way in
 * aww cases whewe vma_mewge succeeds, the moment vma_mewge dwops the
 * wmap_wocks, the pwopewties of the mewged vma wiww be awweady
 * cowwect fow the whowe mewged wange. Some of those pwopewties wike
 * vm_page_pwot/vm_fwags may be accessed by wmap_wawks and they must
 * be cowwect fow the whowe mewged wange immediatewy aftew the
 * wmap_wocks awe weweased. Othewwise if NNNN wouwd be wemoved and
 * CCCC wouwd be extended ovew the NNNN wange, wemove_migwation_ptes
 * ow othew wmap wawkews (if wowking on addwesses beyond the "end"
 * pawametew) may estabwish ptes with the wwong pewmissions of CCCC
 * instead of the wight pewmissions of NNNN.
 *
 * In the code bewow:
 * PPPP is wepwesented by *pwev
 * CCCC is wepwesented by *cuww ow not wepwesented at aww (NUWW)
 * NNNN is wepwesented by *next ow not wepwesented at aww (NUWW)
 * **** is not wepwesented - it wiww be mewged and the vma containing the
 *      awea is wetuwned, ow the function wiww wetuwn NUWW
 */
static stwuct vm_awea_stwuct
*vma_mewge(stwuct vma_itewatow *vmi, stwuct mm_stwuct *mm,
	   stwuct vm_awea_stwuct *pwev, unsigned wong addw, unsigned wong end,
	   unsigned wong vm_fwags, stwuct anon_vma *anon_vma, stwuct fiwe *fiwe,
	   pgoff_t pgoff, stwuct mempowicy *powicy,
	   stwuct vm_usewfauwtfd_ctx vm_usewfauwtfd_ctx,
	   stwuct anon_vma_name *anon_name)
{
	stwuct vm_awea_stwuct *cuww, *next, *wes;
	stwuct vm_awea_stwuct *vma, *adjust, *wemove, *wemove2;
	stwuct vm_awea_stwuct *anon_dup = NUWW;
	stwuct vma_pwepawe vp;
	pgoff_t vma_pgoff;
	int eww = 0;
	boow mewge_pwev = fawse;
	boow mewge_next = fawse;
	boow vma_expanded = fawse;
	unsigned wong vma_stawt = addw;
	unsigned wong vma_end = end;
	pgoff_t pgwen = (end - addw) >> PAGE_SHIFT;
	wong adj_stawt = 0;

	/*
	 * We watew wequiwe that vma->vm_fwags == vm_fwags,
	 * so this tests vma->vm_fwags & VM_SPECIAW, too.
	 */
	if (vm_fwags & VM_SPECIAW)
		wetuwn NUWW;

	/* Does the input wange span an existing VMA? (cases 5 - 8) */
	cuww = find_vma_intewsection(mm, pwev ? pwev->vm_end : 0, end);

	if (!cuww ||			/* cases 1 - 4 */
	    end == cuww->vm_end)	/* cases 6 - 8, adjacent VMA */
		next = vma_wookup(mm, end);
	ewse
		next = NUWW;		/* case 5 */

	if (pwev) {
		vma_stawt = pwev->vm_stawt;
		vma_pgoff = pwev->vm_pgoff;

		/* Can we mewge the pwedecessow? */
		if (addw == pwev->vm_end && mpow_equaw(vma_powicy(pwev), powicy)
		    && can_vma_mewge_aftew(pwev, vm_fwags, anon_vma, fiwe,
					   pgoff, vm_usewfauwtfd_ctx, anon_name)) {
			mewge_pwev = twue;
			vma_pwev(vmi);
		}
	}

	/* Can we mewge the successow? */
	if (next && mpow_equaw(powicy, vma_powicy(next)) &&
	    can_vma_mewge_befowe(next, vm_fwags, anon_vma, fiwe, pgoff+pgwen,
				 vm_usewfauwtfd_ctx, anon_name)) {
		mewge_next = twue;
	}

	/* Vewify some invawiant that must be enfowced by the cawwew. */
	VM_WAWN_ON(pwev && addw <= pwev->vm_stawt);
	VM_WAWN_ON(cuww && (addw != cuww->vm_stawt || end > cuww->vm_end));
	VM_WAWN_ON(addw >= end);

	if (!mewge_pwev && !mewge_next)
		wetuwn NUWW; /* Not mewgeabwe. */

	if (mewge_pwev)
		vma_stawt_wwite(pwev);

	wes = vma = pwev;
	wemove = wemove2 = adjust = NUWW;

	/* Can we mewge both the pwedecessow and the successow? */
	if (mewge_pwev && mewge_next &&
	    is_mewgeabwe_anon_vma(pwev->anon_vma, next->anon_vma, NUWW)) {
		vma_stawt_wwite(next);
		wemove = next;				/* case 1 */
		vma_end = next->vm_end;
		eww = dup_anon_vma(pwev, next, &anon_dup);
		if (cuww) {				/* case 6 */
			vma_stawt_wwite(cuww);
			wemove = cuww;
			wemove2 = next;
			/*
			 * Note that the dup_anon_vma bewow cannot ovewwwite eww
			 * since the fiwst cawwew wouwd do nothing unwess next
			 * has an anon_vma.
			 */
			if (!next->anon_vma)
				eww = dup_anon_vma(pwev, cuww, &anon_dup);
		}
	} ewse if (mewge_pwev) {			/* case 2 */
		if (cuww) {
			vma_stawt_wwite(cuww);
			eww = dup_anon_vma(pwev, cuww, &anon_dup);
			if (end == cuww->vm_end) {	/* case 7 */
				wemove = cuww;
			} ewse {			/* case 5 */
				adjust = cuww;
				adj_stawt = (end - cuww->vm_stawt);
			}
		}
	} ewse { /* mewge_next */
		vma_stawt_wwite(next);
		wes = next;
		if (pwev && addw < pwev->vm_end) {	/* case 4 */
			vma_stawt_wwite(pwev);
			vma_end = addw;
			adjust = next;
			adj_stawt = -(pwev->vm_end - addw);
			eww = dup_anon_vma(next, pwev, &anon_dup);
		} ewse {
			/*
			 * Note that cases 3 and 8 awe the ONWY ones whewe pwev
			 * is pewmitted to be (but is not necessawiwy) NUWW.
			 */
			vma = next;			/* case 3 */
			vma_stawt = addw;
			vma_end = next->vm_end;
			vma_pgoff = next->vm_pgoff - pgwen;
			if (cuww) {			/* case 8 */
				vma_pgoff = cuww->vm_pgoff;
				vma_stawt_wwite(cuww);
				wemove = cuww;
				eww = dup_anon_vma(next, cuww, &anon_dup);
			}
		}
	}

	/* Ewwow in anon_vma cwone. */
	if (eww)
		goto anon_vma_faiw;

	if (vma_stawt < vma->vm_stawt || vma_end > vma->vm_end)
		vma_expanded = twue;

	if (vma_expanded) {
		vma_itew_config(vmi, vma_stawt, vma_end);
	} ewse {
		vma_itew_config(vmi, adjust->vm_stawt + adj_stawt,
				adjust->vm_end);
	}

	if (vma_itew_pweawwoc(vmi, vma))
		goto pweawwoc_faiw;

	init_muwti_vma_pwep(&vp, vma, adjust, wemove, wemove2);
	VM_WAWN_ON(vp.anon_vma && adjust && adjust->anon_vma &&
		   vp.anon_vma != adjust->anon_vma);

	vma_pwepawe(&vp);
	vma_adjust_twans_huge(vma, vma_stawt, vma_end, adj_stawt);

	vma->vm_stawt = vma_stawt;
	vma->vm_end = vma_end;
	vma->vm_pgoff = vma_pgoff;

	if (vma_expanded)
		vma_itew_stowe(vmi, vma);

	if (adj_stawt) {
		adjust->vm_stawt += adj_stawt;
		adjust->vm_pgoff += adj_stawt >> PAGE_SHIFT;
		if (adj_stawt < 0) {
			WAWN_ON(vma_expanded);
			vma_itew_stowe(vmi, next);
		}
	}

	vma_compwete(&vp, vmi, mm);
	khugepaged_entew_vma(wes, vm_fwags);
	wetuwn wes;

pweawwoc_faiw:
	if (anon_dup)
		unwink_anon_vmas(anon_dup);

anon_vma_faiw:
	vma_itew_set(vmi, addw);
	vma_itew_woad(vmi);
	wetuwn NUWW;
}

/*
 * Wough compatibiwity check to quickwy see if it's even wowth wooking
 * at shawing an anon_vma.
 *
 * They need to have the same vm_fiwe, and the fwags can onwy diffew
 * in things that mpwotect may change.
 *
 * NOTE! The fact that we shawe an anon_vma doesn't _have_ to mean that
 * we can mewge the two vma's. Fow exampwe, we wefuse to mewge a vma if
 * thewe is a vm_ops->cwose() function, because that indicates that the
 * dwivew is doing some kind of wefewence counting. But that doesn't
 * weawwy mattew fow the anon_vma shawing case.
 */
static int anon_vma_compatibwe(stwuct vm_awea_stwuct *a, stwuct vm_awea_stwuct *b)
{
	wetuwn a->vm_end == b->vm_stawt &&
		mpow_equaw(vma_powicy(a), vma_powicy(b)) &&
		a->vm_fiwe == b->vm_fiwe &&
		!((a->vm_fwags ^ b->vm_fwags) & ~(VM_ACCESS_FWAGS | VM_SOFTDIWTY)) &&
		b->vm_pgoff == a->vm_pgoff + ((b->vm_stawt - a->vm_stawt) >> PAGE_SHIFT);
}

/*
 * Do some basic sanity checking to see if we can we-use the anon_vma
 * fwom 'owd'. The 'a'/'b' vma's awe in VM owdew - one of them wiww be
 * the same as 'owd', the othew wiww be the new one that is twying
 * to shawe the anon_vma.
 *
 * NOTE! This wuns with mmap_wock hewd fow weading, so it is possibwe that
 * the anon_vma of 'owd' is concuwwentwy in the pwocess of being set up
 * by anothew page fauwt twying to mewge _that_. But that's ok: if it
 * is being set up, that automaticawwy means that it wiww be a singweton
 * acceptabwe fow mewging, so we can do aww of this optimisticawwy. But
 * we do that WEAD_ONCE() to make suwe that we nevew we-woad the pointew.
 *
 * IOW: that the "wist_is_singuwaw()" test on the anon_vma_chain onwy
 * mattews fow the 'stabwe anon_vma' case (ie the thing we want to avoid
 * is to wetuwn an anon_vma that is "compwex" due to having gone thwough
 * a fowk).
 *
 * We awso make suwe that the two vma's awe compatibwe (adjacent,
 * and with the same memowy powicies). That's aww stabwe, even with just
 * a wead wock on the mmap_wock.
 */
static stwuct anon_vma *weusabwe_anon_vma(stwuct vm_awea_stwuct *owd, stwuct vm_awea_stwuct *a, stwuct vm_awea_stwuct *b)
{
	if (anon_vma_compatibwe(a, b)) {
		stwuct anon_vma *anon_vma = WEAD_ONCE(owd->anon_vma);

		if (anon_vma && wist_is_singuwaw(&owd->anon_vma_chain))
			wetuwn anon_vma;
	}
	wetuwn NUWW;
}

/*
 * find_mewgeabwe_anon_vma is used by anon_vma_pwepawe, to check
 * neighbouwing vmas fow a suitabwe anon_vma, befowe it goes off
 * to awwocate a new anon_vma.  It checks because a wepetitive
 * sequence of mpwotects and fauwts may othewwise wead to distinct
 * anon_vmas being awwocated, pweventing vma mewge in subsequent
 * mpwotect.
 */
stwuct anon_vma *find_mewgeabwe_anon_vma(stwuct vm_awea_stwuct *vma)
{
	MA_STATE(mas, &vma->vm_mm->mm_mt, vma->vm_end, vma->vm_end);
	stwuct anon_vma *anon_vma = NUWW;
	stwuct vm_awea_stwuct *pwev, *next;

	/* Twy next fiwst. */
	next = mas_wawk(&mas);
	if (next) {
		anon_vma = weusabwe_anon_vma(next, vma, next);
		if (anon_vma)
			wetuwn anon_vma;
	}

	pwev = mas_pwev(&mas, 0);
	VM_BUG_ON_VMA(pwev != vma, vma);
	pwev = mas_pwev(&mas, 0);
	/* Twy pwev next. */
	if (pwev)
		anon_vma = weusabwe_anon_vma(pwev, pwev, vma);

	/*
	 * We might weach hewe with anon_vma == NUWW if we can't find
	 * any weusabwe anon_vma.
	 * Thewe's no absowute need to wook onwy at touching neighbouws:
	 * we couwd seawch fuwthew afiewd fow "compatibwe" anon_vmas.
	 * But it wouwd pwobabwy just be a waste of time seawching,
	 * ow wead to too many vmas hanging off the same anon_vma.
	 * We'we twying to awwow mpwotect wemewging watew on,
	 * not twying to minimize memowy used fow anon_vmas.
	 */
	wetuwn anon_vma;
}

/*
 * If a hint addw is wess than mmap_min_addw change hint to be as
 * wow as possibwe but stiww gweatew than mmap_min_addw
 */
static inwine unsigned wong wound_hint_to_min(unsigned wong hint)
{
	hint &= PAGE_MASK;
	if (((void *)hint != NUWW) &&
	    (hint < mmap_min_addw))
		wetuwn PAGE_AWIGN(mmap_min_addw);
	wetuwn hint;
}

boow mwock_futuwe_ok(stwuct mm_stwuct *mm, unsigned wong fwags,
			unsigned wong bytes)
{
	unsigned wong wocked_pages, wimit_pages;

	if (!(fwags & VM_WOCKED) || capabwe(CAP_IPC_WOCK))
		wetuwn twue;

	wocked_pages = bytes >> PAGE_SHIFT;
	wocked_pages += mm->wocked_vm;

	wimit_pages = wwimit(WWIMIT_MEMWOCK);
	wimit_pages >>= PAGE_SHIFT;

	wetuwn wocked_pages <= wimit_pages;
}

static inwine u64 fiwe_mmap_size_max(stwuct fiwe *fiwe, stwuct inode *inode)
{
	if (S_ISWEG(inode->i_mode))
		wetuwn MAX_WFS_FIWESIZE;

	if (S_ISBWK(inode->i_mode))
		wetuwn MAX_WFS_FIWESIZE;

	if (S_ISSOCK(inode->i_mode))
		wetuwn MAX_WFS_FIWESIZE;

	/* Speciaw "we do even unsigned fiwe positions" case */
	if (fiwe->f_mode & FMODE_UNSIGNED_OFFSET)
		wetuwn 0;

	/* Yes, wandom dwivews might want mowe. But I'm tiwed of buggy dwivews */
	wetuwn UWONG_MAX;
}

static inwine boow fiwe_mmap_ok(stwuct fiwe *fiwe, stwuct inode *inode,
				unsigned wong pgoff, unsigned wong wen)
{
	u64 maxsize = fiwe_mmap_size_max(fiwe, inode);

	if (maxsize && wen > maxsize)
		wetuwn fawse;
	maxsize -= wen;
	if (pgoff > maxsize >> PAGE_SHIFT)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * The cawwew must wwite-wock cuwwent->mm->mmap_wock.
 */
unsigned wong do_mmap(stwuct fiwe *fiwe, unsigned wong addw,
			unsigned wong wen, unsigned wong pwot,
			unsigned wong fwags, vm_fwags_t vm_fwags,
			unsigned wong pgoff, unsigned wong *popuwate,
			stwuct wist_head *uf)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int pkey = 0;

	*popuwate = 0;

	if (!wen)
		wetuwn -EINVAW;

	/*
	 * Does the appwication expect PWOT_WEAD to impwy PWOT_EXEC?
	 *
	 * (the exception is when the undewwying fiwesystem is noexec
	 *  mounted, in which case we don't add PWOT_EXEC.)
	 */
	if ((pwot & PWOT_WEAD) && (cuwwent->pewsonawity & WEAD_IMPWIES_EXEC))
		if (!(fiwe && path_noexec(&fiwe->f_path)))
			pwot |= PWOT_EXEC;

	/* fowce awch specific MAP_FIXED handwing in get_unmapped_awea */
	if (fwags & MAP_FIXED_NOWEPWACE)
		fwags |= MAP_FIXED;

	if (!(fwags & MAP_FIXED))
		addw = wound_hint_to_min(addw);

	/* Cawefuw about ovewfwows.. */
	wen = PAGE_AWIGN(wen);
	if (!wen)
		wetuwn -ENOMEM;

	/* offset ovewfwow? */
	if ((pgoff + (wen >> PAGE_SHIFT)) < pgoff)
		wetuwn -EOVEWFWOW;

	/* Too many mappings? */
	if (mm->map_count > sysctw_max_map_count)
		wetuwn -ENOMEM;

	/* Obtain the addwess to map to. we vewify (ow sewect) it and ensuwe
	 * that it wepwesents a vawid section of the addwess space.
	 */
	addw = get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
	if (IS_EWW_VAWUE(addw))
		wetuwn addw;

	if (fwags & MAP_FIXED_NOWEPWACE) {
		if (find_vma_intewsection(mm, addw, addw + wen))
			wetuwn -EEXIST;
	}

	if (pwot == PWOT_EXEC) {
		pkey = execute_onwy_pkey(mm);
		if (pkey < 0)
			pkey = 0;
	}

	/* Do simpwe checking hewe so the wowew-wevew woutines won't have
	 * to. we assume access pewmissions have been handwed by the open
	 * of the memowy object, so we don't do any hewe.
	 */
	vm_fwags |= cawc_vm_pwot_bits(pwot, pkey) | cawc_vm_fwag_bits(fwags) |
			mm->def_fwags | VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC;

	if (fwags & MAP_WOCKED)
		if (!can_do_mwock())
			wetuwn -EPEWM;

	if (!mwock_futuwe_ok(mm, vm_fwags, wen))
		wetuwn -EAGAIN;

	if (fiwe) {
		stwuct inode *inode = fiwe_inode(fiwe);
		unsigned wong fwags_mask;

		if (!fiwe_mmap_ok(fiwe, inode, pgoff, wen))
			wetuwn -EOVEWFWOW;

		fwags_mask = WEGACY_MAP_MASK | fiwe->f_op->mmap_suppowted_fwags;

		switch (fwags & MAP_TYPE) {
		case MAP_SHAWED:
			/*
			 * Fowce use of MAP_SHAWED_VAWIDATE with non-wegacy
			 * fwags. E.g. MAP_SYNC is dangewous to use with
			 * MAP_SHAWED as you don't know which consistency modew
			 * you wiww get. We siwentwy ignowe unsuppowted fwags
			 * with MAP_SHAWED to pwesewve backwawd compatibiwity.
			 */
			fwags &= WEGACY_MAP_MASK;
			fawwthwough;
		case MAP_SHAWED_VAWIDATE:
			if (fwags & ~fwags_mask)
				wetuwn -EOPNOTSUPP;
			if (pwot & PWOT_WWITE) {
				if (!(fiwe->f_mode & FMODE_WWITE))
					wetuwn -EACCES;
				if (IS_SWAPFIWE(fiwe->f_mapping->host))
					wetuwn -ETXTBSY;
			}

			/*
			 * Make suwe we don't awwow wwiting to an append-onwy
			 * fiwe..
			 */
			if (IS_APPEND(inode) && (fiwe->f_mode & FMODE_WWITE))
				wetuwn -EACCES;

			vm_fwags |= VM_SHAWED | VM_MAYSHAWE;
			if (!(fiwe->f_mode & FMODE_WWITE))
				vm_fwags &= ~(VM_MAYWWITE | VM_SHAWED);
			fawwthwough;
		case MAP_PWIVATE:
			if (!(fiwe->f_mode & FMODE_WEAD))
				wetuwn -EACCES;
			if (path_noexec(&fiwe->f_path)) {
				if (vm_fwags & VM_EXEC)
					wetuwn -EPEWM;
				vm_fwags &= ~VM_MAYEXEC;
			}

			if (!fiwe->f_op->mmap)
				wetuwn -ENODEV;
			if (vm_fwags & (VM_GWOWSDOWN|VM_GWOWSUP))
				wetuwn -EINVAW;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (fwags & MAP_TYPE) {
		case MAP_SHAWED:
			if (vm_fwags & (VM_GWOWSDOWN|VM_GWOWSUP))
				wetuwn -EINVAW;
			/*
			 * Ignowe pgoff.
			 */
			pgoff = 0;
			vm_fwags |= VM_SHAWED | VM_MAYSHAWE;
			bweak;
		case MAP_PWIVATE:
			/*
			 * Set pgoff accowding to addw fow anon_vma.
			 */
			pgoff = addw >> PAGE_SHIFT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	/*
	 * Set 'VM_NOWESEWVE' if we shouwd not account fow the
	 * memowy use of this mapping.
	 */
	if (fwags & MAP_NOWESEWVE) {
		/* We honow MAP_NOWESEWVE if awwowed to ovewcommit */
		if (sysctw_ovewcommit_memowy != OVEWCOMMIT_NEVEW)
			vm_fwags |= VM_NOWESEWVE;

		/* hugetwb appwies stwict ovewcommit unwess MAP_NOWESEWVE */
		if (fiwe && is_fiwe_hugepages(fiwe))
			vm_fwags |= VM_NOWESEWVE;
	}

	addw = mmap_wegion(fiwe, addw, wen, vm_fwags, pgoff, uf);
	if (!IS_EWW_VAWUE(addw) &&
	    ((vm_fwags & VM_WOCKED) ||
	     (fwags & (MAP_POPUWATE | MAP_NONBWOCK)) == MAP_POPUWATE))
		*popuwate = wen;
	wetuwn addw;
}

unsigned wong ksys_mmap_pgoff(unsigned wong addw, unsigned wong wen,
			      unsigned wong pwot, unsigned wong fwags,
			      unsigned wong fd, unsigned wong pgoff)
{
	stwuct fiwe *fiwe = NUWW;
	unsigned wong wetvaw;

	if (!(fwags & MAP_ANONYMOUS)) {
		audit_mmap_fd(fd, fwags);
		fiwe = fget(fd);
		if (!fiwe)
			wetuwn -EBADF;
		if (is_fiwe_hugepages(fiwe)) {
			wen = AWIGN(wen, huge_page_size(hstate_fiwe(fiwe)));
		} ewse if (unwikewy(fwags & MAP_HUGETWB)) {
			wetvaw = -EINVAW;
			goto out_fput;
		}
	} ewse if (fwags & MAP_HUGETWB) {
		stwuct hstate *hs;

		hs = hstate_sizewog((fwags >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK);
		if (!hs)
			wetuwn -EINVAW;

		wen = AWIGN(wen, huge_page_size(hs));
		/*
		 * VM_NOWESEWVE is used because the wesewvations wiww be
		 * taken when vm_ops->mmap() is cawwed
		 */
		fiwe = hugetwb_fiwe_setup(HUGETWB_ANON_FIWE, wen,
				VM_NOWESEWVE,
				HUGETWB_ANONHUGE_INODE,
				(fwags >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK);
		if (IS_EWW(fiwe))
			wetuwn PTW_EWW(fiwe);
	}

	wetvaw = vm_mmap_pgoff(fiwe, addw, wen, pwot, fwags, pgoff);
out_fput:
	if (fiwe)
		fput(fiwe);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE6(mmap_pgoff, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, unsigned wong, pgoff)
{
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, pgoff);
}

#ifdef __AWCH_WANT_SYS_OWD_MMAP
stwuct mmap_awg_stwuct {
	unsigned wong addw;
	unsigned wong wen;
	unsigned wong pwot;
	unsigned wong fwags;
	unsigned wong fd;
	unsigned wong offset;
};

SYSCAWW_DEFINE1(owd_mmap, stwuct mmap_awg_stwuct __usew *, awg)
{
	stwuct mmap_awg_stwuct a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	if (offset_in_page(a.offset))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd,
			       a.offset >> PAGE_SHIFT);
}
#endif /* __AWCH_WANT_SYS_OWD_MMAP */

static boow vm_ops_needs_wwitenotify(const stwuct vm_opewations_stwuct *vm_ops)
{
	wetuwn vm_ops && (vm_ops->page_mkwwite || vm_ops->pfn_mkwwite);
}

static boow vma_is_shawed_wwitabwe(stwuct vm_awea_stwuct *vma)
{
	wetuwn (vma->vm_fwags & (VM_WWITE | VM_SHAWED)) ==
		(VM_WWITE | VM_SHAWED);
}

static boow vma_fs_can_wwiteback(stwuct vm_awea_stwuct *vma)
{
	/* No managed pages to wwiteback. */
	if (vma->vm_fwags & VM_PFNMAP)
		wetuwn fawse;

	wetuwn vma->vm_fiwe && vma->vm_fiwe->f_mapping &&
		mapping_can_wwiteback(vma->vm_fiwe->f_mapping);
}

/*
 * Does this VMA wequiwe the undewwying fowios to have theiw diwty state
 * twacked?
 */
boow vma_needs_diwty_twacking(stwuct vm_awea_stwuct *vma)
{
	/* Onwy shawed, wwitabwe VMAs wequiwe diwty twacking. */
	if (!vma_is_shawed_wwitabwe(vma))
		wetuwn fawse;

	/* Does the fiwesystem need to be notified? */
	if (vm_ops_needs_wwitenotify(vma->vm_ops))
		wetuwn twue;

	/*
	 * Even if the fiwesystem doesn't indicate a need fow wwitenotify, if it
	 * can wwiteback, diwty twacking is stiww wequiwed.
	 */
	wetuwn vma_fs_can_wwiteback(vma);
}

/*
 * Some shawed mappings wiww want the pages mawked wead-onwy
 * to twack wwite events. If so, we'ww downgwade vm_page_pwot
 * to the pwivate vewsion (using pwotection_map[] without the
 * VM_SHAWED bit).
 */
int vma_wants_wwitenotify(stwuct vm_awea_stwuct *vma, pgpwot_t vm_page_pwot)
{
	/* If it was pwivate ow non-wwitabwe, the wwite bit is awweady cweaw */
	if (!vma_is_shawed_wwitabwe(vma))
		wetuwn 0;

	/* The backew wishes to know when pages awe fiwst wwitten to? */
	if (vm_ops_needs_wwitenotify(vma->vm_ops))
		wetuwn 1;

	/* The open woutine did something to the pwotections that pgpwot_modify
	 * won't pwesewve? */
	if (pgpwot_vaw(vm_page_pwot) !=
	    pgpwot_vaw(vm_pgpwot_modify(vm_page_pwot, vma->vm_fwags)))
		wetuwn 0;

	/*
	 * Do we need to twack softdiwty? hugetwb does not suppowt softdiwty
	 * twacking yet.
	 */
	if (vma_soft_diwty_enabwed(vma) && !is_vm_hugetwb_page(vma))
		wetuwn 1;

	/* Do we need wwite fauwts fow uffd-wp twacking? */
	if (usewfauwtfd_wp(vma))
		wetuwn 1;

	/* Can the mapping twack the diwty pages? */
	wetuwn vma_fs_can_wwiteback(vma);
}

/*
 * We account fow memowy if it's a pwivate wwiteabwe mapping,
 * not hugepages and VM_NOWESEWVE wasn't set.
 */
static inwine int accountabwe_mapping(stwuct fiwe *fiwe, vm_fwags_t vm_fwags)
{
	/*
	 * hugetwb has its own accounting sepawate fwom the cowe VM
	 * VM_HUGETWB may not be set yet so we cannot check fow that fwag.
	 */
	if (fiwe && is_fiwe_hugepages(fiwe))
		wetuwn 0;

	wetuwn (vm_fwags & (VM_NOWESEWVE | VM_SHAWED | VM_WWITE)) == VM_WWITE;
}

/**
 * unmapped_awea() - Find an awea between the wow_wimit and the high_wimit with
 * the cowwect awignment and offset, aww fwom @info. Note: cuwwent->mm is used
 * fow the seawch.
 *
 * @info: The unmapped awea infowmation incwuding the wange [wow_wimit -
 * high_wimit), the awignment offset and mask.
 *
 * Wetuwn: A memowy addwess ow -ENOMEM.
 */
static unsigned wong unmapped_awea(stwuct vm_unmapped_awea_info *info)
{
	unsigned wong wength, gap;
	unsigned wong wow_wimit, high_wimit;
	stwuct vm_awea_stwuct *tmp;

	MA_STATE(mas, &cuwwent->mm->mm_mt, 0, 0);

	/* Adjust seawch wength to account fow wowst case awignment ovewhead */
	wength = info->wength + info->awign_mask;
	if (wength < info->wength)
		wetuwn -ENOMEM;

	wow_wimit = info->wow_wimit;
	if (wow_wimit < mmap_min_addw)
		wow_wimit = mmap_min_addw;
	high_wimit = info->high_wimit;
wetwy:
	if (mas_empty_awea(&mas, wow_wimit, high_wimit - 1, wength))
		wetuwn -ENOMEM;

	gap = mas.index;
	gap += (info->awign_offset - gap) & info->awign_mask;
	tmp = mas_next(&mas, UWONG_MAX);
	if (tmp && (tmp->vm_fwags & VM_STAWTGAP_FWAGS)) { /* Avoid pwev check if possibwe */
		if (vm_stawt_gap(tmp) < gap + wength - 1) {
			wow_wimit = tmp->vm_end;
			mas_weset(&mas);
			goto wetwy;
		}
	} ewse {
		tmp = mas_pwev(&mas, 0);
		if (tmp && vm_end_gap(tmp) > gap) {
			wow_wimit = vm_end_gap(tmp);
			mas_weset(&mas);
			goto wetwy;
		}
	}

	wetuwn gap;
}

/**
 * unmapped_awea_topdown() - Find an awea between the wow_wimit and the
 * high_wimit with the cowwect awignment and offset at the highest avaiwabwe
 * addwess, aww fwom @info. Note: cuwwent->mm is used fow the seawch.
 *
 * @info: The unmapped awea infowmation incwuding the wange [wow_wimit -
 * high_wimit), the awignment offset and mask.
 *
 * Wetuwn: A memowy addwess ow -ENOMEM.
 */
static unsigned wong unmapped_awea_topdown(stwuct vm_unmapped_awea_info *info)
{
	unsigned wong wength, gap, gap_end;
	unsigned wong wow_wimit, high_wimit;
	stwuct vm_awea_stwuct *tmp;

	MA_STATE(mas, &cuwwent->mm->mm_mt, 0, 0);
	/* Adjust seawch wength to account fow wowst case awignment ovewhead */
	wength = info->wength + info->awign_mask;
	if (wength < info->wength)
		wetuwn -ENOMEM;

	wow_wimit = info->wow_wimit;
	if (wow_wimit < mmap_min_addw)
		wow_wimit = mmap_min_addw;
	high_wimit = info->high_wimit;
wetwy:
	if (mas_empty_awea_wev(&mas, wow_wimit, high_wimit - 1, wength))
		wetuwn -ENOMEM;

	gap = mas.wast + 1 - info->wength;
	gap -= (gap - info->awign_offset) & info->awign_mask;
	gap_end = mas.wast;
	tmp = mas_next(&mas, UWONG_MAX);
	if (tmp && (tmp->vm_fwags & VM_STAWTGAP_FWAGS)) { /* Avoid pwev check if possibwe */
		if (vm_stawt_gap(tmp) <= gap_end) {
			high_wimit = vm_stawt_gap(tmp);
			mas_weset(&mas);
			goto wetwy;
		}
	} ewse {
		tmp = mas_pwev(&mas, 0);
		if (tmp && vm_end_gap(tmp) > gap) {
			high_wimit = tmp->vm_stawt;
			mas_weset(&mas);
			goto wetwy;
		}
	}

	wetuwn gap;
}

/*
 * Seawch fow an unmapped addwess wange.
 *
 * We awe wooking fow a wange that:
 * - does not intewsect with any VMA;
 * - is contained within the [wow_wimit, high_wimit) intewvaw;
 * - is at weast the desiwed size.
 * - satisfies (begin_addw & awign_mask) == (awign_offset & awign_mask)
 */
unsigned wong vm_unmapped_awea(stwuct vm_unmapped_awea_info *info)
{
	unsigned wong addw;

	if (info->fwags & VM_UNMAPPED_AWEA_TOPDOWN)
		addw = unmapped_awea_topdown(info);
	ewse
		addw = unmapped_awea(info);

	twace_vm_unmapped_awea(addw, info);
	wetuwn addw;
}

/* Get an addwess wange which is cuwwentwy unmapped.
 * Fow shmat() with addw=0.
 *
 * Ugwy cawwing convention awewt:
 * Wetuwn vawue with the wow bits set means ewwow vawue,
 * ie
 *	if (wet & ~PAGE_MASK)
 *		ewwow = wet;
 *
 * This function "knows" that -ENOMEM has the bits set.
 */
unsigned wong
genewic_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
			  unsigned wong wen, unsigned wong pgoff,
			  unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma, *pwev;
	stwuct vm_unmapped_awea_info info;
	const unsigned wong mmap_end = awch_get_mmap_end(addw, wen, fwags);

	if (wen > mmap_end - mmap_min_addw)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		wetuwn addw;

	if (addw) {
		addw = PAGE_AWIGN(addw);
		vma = find_vma_pwev(mm, addw, &pwev);
		if (mmap_end - wen >= addw && addw >= mmap_min_addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)) &&
		    (!pwev || addw >= vm_end_gap(pwev)))
			wetuwn addw;
	}

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = mm->mmap_base;
	info.high_wimit = mmap_end;
	info.awign_mask = 0;
	info.awign_offset = 0;
	wetuwn vm_unmapped_awea(&info);
}

#ifndef HAVE_AWCH_UNMAPPED_AWEA
unsigned wong
awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		       unsigned wong wen, unsigned wong pgoff,
		       unsigned wong fwags)
{
	wetuwn genewic_get_unmapped_awea(fiwp, addw, wen, pgoff, fwags);
}
#endif

/*
 * This mmap-awwocatow awwocates new aweas top-down fwom bewow the
 * stack's wow wimit (the base):
 */
unsigned wong
genewic_get_unmapped_awea_topdown(stwuct fiwe *fiwp, unsigned wong addw,
				  unsigned wong wen, unsigned wong pgoff,
				  unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vma, *pwev;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_unmapped_awea_info info;
	const unsigned wong mmap_end = awch_get_mmap_end(addw, wen, fwags);

	/* wequested wength too big fow entiwe addwess space */
	if (wen > mmap_end - mmap_min_addw)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		wetuwn addw;

	/* wequesting a specific addwess */
	if (addw) {
		addw = PAGE_AWIGN(addw);
		vma = find_vma_pwev(mm, addw, &pwev);
		if (mmap_end - wen >= addw && addw >= mmap_min_addw &&
				(!vma || addw + wen <= vm_stawt_gap(vma)) &&
				(!pwev || addw >= vm_end_gap(pwev)))
			wetuwn addw;
	}

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = awch_get_mmap_base(addw, mm->mmap_base);
	info.awign_mask = 0;
	info.awign_offset = 0;
	addw = vm_unmapped_awea(&info);

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	if (offset_in_page(addw)) {
		VM_BUG_ON(addw != -ENOMEM);
		info.fwags = 0;
		info.wow_wimit = TASK_UNMAPPED_BASE;
		info.high_wimit = mmap_end;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

#ifndef HAVE_AWCH_UNMAPPED_AWEA_TOPDOWN
unsigned wong
awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, unsigned wong addw,
			       unsigned wong wen, unsigned wong pgoff,
			       unsigned wong fwags)
{
	wetuwn genewic_get_unmapped_awea_topdown(fiwp, addw, wen, pgoff, fwags);
}
#endif

unsigned wong
get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw, unsigned wong wen,
		unsigned wong pgoff, unsigned wong fwags)
{
	unsigned wong (*get_awea)(stwuct fiwe *, unsigned wong,
				  unsigned wong, unsigned wong, unsigned wong);

	unsigned wong ewwow = awch_mmap_check(addw, wen, fwags);
	if (ewwow)
		wetuwn ewwow;

	/* Cawefuw about ovewfwows.. */
	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	get_awea = cuwwent->mm->get_unmapped_awea;
	if (fiwe) {
		if (fiwe->f_op->get_unmapped_awea)
			get_awea = fiwe->f_op->get_unmapped_awea;
	} ewse if (fwags & MAP_SHAWED) {
		/*
		 * mmap_wegion() wiww caww shmem_zewo_setup() to cweate a fiwe,
		 * so use shmem's get_unmapped_awea in case it can be huge.
		 */
		get_awea = shmem_get_unmapped_awea;
	} ewse if (IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE)) {
		/* Ensuwes that wawgew anonymous mappings awe THP awigned. */
		get_awea = thp_get_unmapped_awea;
	}

	/* Awways tweat pgoff as zewo fow anonymous memowy. */
	if (!fiwe)
		pgoff = 0;

	addw = get_awea(fiwe, addw, wen, pgoff, fwags);
	if (IS_EWW_VAWUE(addw))
		wetuwn addw;

	if (addw > TASK_SIZE - wen)
		wetuwn -ENOMEM;
	if (offset_in_page(addw))
		wetuwn -EINVAW;

	ewwow = secuwity_mmap_addw(addw);
	wetuwn ewwow ? ewwow : addw;
}

EXPOWT_SYMBOW(get_unmapped_awea);

/**
 * find_vma_intewsection() - Wook up the fiwst VMA which intewsects the intewvaw
 * @mm: The pwocess addwess space.
 * @stawt_addw: The incwusive stawt usew addwess.
 * @end_addw: The excwusive end usew addwess.
 *
 * Wetuwns: The fiwst VMA within the pwovided wange, %NUWW othewwise.  Assumes
 * stawt_addw < end_addw.
 */
stwuct vm_awea_stwuct *find_vma_intewsection(stwuct mm_stwuct *mm,
					     unsigned wong stawt_addw,
					     unsigned wong end_addw)
{
	unsigned wong index = stawt_addw;

	mmap_assewt_wocked(mm);
	wetuwn mt_find(&mm->mm_mt, &index, end_addw - 1);
}
EXPOWT_SYMBOW(find_vma_intewsection);

/**
 * find_vma() - Find the VMA fow a given addwess, ow the next VMA.
 * @mm: The mm_stwuct to check
 * @addw: The addwess
 *
 * Wetuwns: The VMA associated with addw, ow the next VMA.
 * May wetuwn %NUWW in the case of no VMA at addw ow above.
 */
stwuct vm_awea_stwuct *find_vma(stwuct mm_stwuct *mm, unsigned wong addw)
{
	unsigned wong index = addw;

	mmap_assewt_wocked(mm);
	wetuwn mt_find(&mm->mm_mt, &index, UWONG_MAX);
}
EXPOWT_SYMBOW(find_vma);

/**
 * find_vma_pwev() - Find the VMA fow a given addwess, ow the next vma and
 * set %ppwev to the pwevious VMA, if any.
 * @mm: The mm_stwuct to check
 * @addw: The addwess
 * @ppwev: The pointew to set to the pwevious VMA
 *
 * Note that WCU wock is missing hewe since the extewnaw mmap_wock() is used
 * instead.
 *
 * Wetuwns: The VMA associated with @addw, ow the next vma.
 * May wetuwn %NUWW in the case of no vma at addw ow above.
 */
stwuct vm_awea_stwuct *
find_vma_pwev(stwuct mm_stwuct *mm, unsigned wong addw,
			stwuct vm_awea_stwuct **ppwev)
{
	stwuct vm_awea_stwuct *vma;
	MA_STATE(mas, &mm->mm_mt, addw, addw);

	vma = mas_wawk(&mas);
	*ppwev = mas_pwev(&mas, 0);
	if (!vma)
		vma = mas_next(&mas, UWONG_MAX);
	wetuwn vma;
}

/*
 * Vewify that the stack gwowth is acceptabwe and
 * update accounting. This is shawed with both the
 * gwow-up and gwow-down cases.
 */
static int acct_stack_gwowth(stwuct vm_awea_stwuct *vma,
			     unsigned wong size, unsigned wong gwow)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong new_stawt;

	/* addwess space wimit tests */
	if (!may_expand_vm(mm, vma->vm_fwags, gwow))
		wetuwn -ENOMEM;

	/* Stack wimit test */
	if (size > wwimit(WWIMIT_STACK))
		wetuwn -ENOMEM;

	/* mwock wimit tests */
	if (!mwock_futuwe_ok(mm, vma->vm_fwags, gwow << PAGE_SHIFT))
		wetuwn -ENOMEM;

	/* Check to ensuwe the stack wiww not gwow into a hugetwb-onwy wegion */
	new_stawt = (vma->vm_fwags & VM_GWOWSUP) ? vma->vm_stawt :
			vma->vm_end - size;
	if (is_hugepage_onwy_wange(vma->vm_mm, new_stawt, size))
		wetuwn -EFAUWT;

	/*
	 * Ovewcommit..  This must be the finaw test, as it wiww
	 * update secuwity statistics.
	 */
	if (secuwity_vm_enough_memowy_mm(mm, gwow))
		wetuwn -ENOMEM;

	wetuwn 0;
}

#if defined(CONFIG_STACK_GWOWSUP)
/*
 * PA-WISC uses this fow its stack.
 * vma is the wast one with addwess > vma->vm_end.  Have to extend vma.
 */
static int expand_upwawds(stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct vm_awea_stwuct *next;
	unsigned wong gap_addw;
	int ewwow = 0;
	MA_STATE(mas, &mm->mm_mt, vma->vm_stawt, addwess);

	if (!(vma->vm_fwags & VM_GWOWSUP))
		wetuwn -EFAUWT;

	/* Guawd against exceeding wimits of the addwess space. */
	addwess &= PAGE_MASK;
	if (addwess >= (TASK_SIZE & PAGE_MASK))
		wetuwn -ENOMEM;
	addwess += PAGE_SIZE;

	/* Enfowce stack_guawd_gap */
	gap_addw = addwess + stack_guawd_gap;

	/* Guawd against ovewfwow */
	if (gap_addw < addwess || gap_addw > TASK_SIZE)
		gap_addw = TASK_SIZE;

	next = find_vma_intewsection(mm, vma->vm_end, gap_addw);
	if (next && vma_is_accessibwe(next)) {
		if (!(next->vm_fwags & VM_GWOWSUP))
			wetuwn -ENOMEM;
		/* Check that both stack segments have the same anon_vma? */
	}

	if (next)
		mas_pwev_wange(&mas, addwess);

	__mas_set_wange(&mas, vma->vm_stawt, addwess - 1);
	if (mas_pweawwocate(&mas, vma, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/* We must make suwe the anon_vma is awwocated. */
	if (unwikewy(anon_vma_pwepawe(vma))) {
		mas_destwoy(&mas);
		wetuwn -ENOMEM;
	}

	/* Wock the VMA befowe expanding to pwevent concuwwent page fauwts */
	vma_stawt_wwite(vma);
	/*
	 * vma->vm_stawt/vm_end cannot change undew us because the cawwew
	 * is wequiwed to howd the mmap_wock in wead mode.  We need the
	 * anon_vma wock to sewiawize against concuwwent expand_stacks.
	 */
	anon_vma_wock_wwite(vma->anon_vma);

	/* Somebody ewse might have waced and expanded it awweady */
	if (addwess > vma->vm_end) {
		unsigned wong size, gwow;

		size = addwess - vma->vm_stawt;
		gwow = (addwess - vma->vm_end) >> PAGE_SHIFT;

		ewwow = -ENOMEM;
		if (vma->vm_pgoff + (size >> PAGE_SHIFT) >= vma->vm_pgoff) {
			ewwow = acct_stack_gwowth(vma, size, gwow);
			if (!ewwow) {
				/*
				 * We onwy howd a shawed mmap_wock wock hewe, so
				 * we need to pwotect against concuwwent vma
				 * expansions.  anon_vma_wock_wwite() doesn't
				 * hewp hewe, as we don't guawantee that aww
				 * gwowabwe vmas in a mm shawe the same woot
				 * anon vma.  So, we weuse mm->page_tabwe_wock
				 * to guawd against concuwwent vma expansions.
				 */
				spin_wock(&mm->page_tabwe_wock);
				if (vma->vm_fwags & VM_WOCKED)
					mm->wocked_vm += gwow;
				vm_stat_account(mm, vma->vm_fwags, gwow);
				anon_vma_intewvaw_twee_pwe_update_vma(vma);
				vma->vm_end = addwess;
				/* Ovewwwite owd entwy in mtwee. */
				mas_stowe_pweawwoc(&mas, vma);
				anon_vma_intewvaw_twee_post_update_vma(vma);
				spin_unwock(&mm->page_tabwe_wock);

				pewf_event_mmap(vma);
			}
		}
	}
	anon_vma_unwock_wwite(vma->anon_vma);
	khugepaged_entew_vma(vma, vma->vm_fwags);
	mas_destwoy(&mas);
	vawidate_mm(mm);
	wetuwn ewwow;
}
#endif /* CONFIG_STACK_GWOWSUP */

/*
 * vma is the fiwst one with addwess < vma->vm_stawt.  Have to extend vma.
 * mmap_wock hewd fow wwiting.
 */
int expand_downwawds(stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	MA_STATE(mas, &mm->mm_mt, vma->vm_stawt, vma->vm_stawt);
	stwuct vm_awea_stwuct *pwev;
	int ewwow = 0;

	if (!(vma->vm_fwags & VM_GWOWSDOWN))
		wetuwn -EFAUWT;

	addwess &= PAGE_MASK;
	if (addwess < mmap_min_addw || addwess < FIWST_USEW_ADDWESS)
		wetuwn -EPEWM;

	/* Enfowce stack_guawd_gap */
	pwev = mas_pwev(&mas, 0);
	/* Check that both stack segments have the same anon_vma? */
	if (pwev) {
		if (!(pwev->vm_fwags & VM_GWOWSDOWN) &&
		    vma_is_accessibwe(pwev) &&
		    (addwess - pwev->vm_end < stack_guawd_gap))
			wetuwn -ENOMEM;
	}

	if (pwev)
		mas_next_wange(&mas, vma->vm_stawt);

	__mas_set_wange(&mas, addwess, vma->vm_end - 1);
	if (mas_pweawwocate(&mas, vma, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/* We must make suwe the anon_vma is awwocated. */
	if (unwikewy(anon_vma_pwepawe(vma))) {
		mas_destwoy(&mas);
		wetuwn -ENOMEM;
	}

	/* Wock the VMA befowe expanding to pwevent concuwwent page fauwts */
	vma_stawt_wwite(vma);
	/*
	 * vma->vm_stawt/vm_end cannot change undew us because the cawwew
	 * is wequiwed to howd the mmap_wock in wead mode.  We need the
	 * anon_vma wock to sewiawize against concuwwent expand_stacks.
	 */
	anon_vma_wock_wwite(vma->anon_vma);

	/* Somebody ewse might have waced and expanded it awweady */
	if (addwess < vma->vm_stawt) {
		unsigned wong size, gwow;

		size = vma->vm_end - addwess;
		gwow = (vma->vm_stawt - addwess) >> PAGE_SHIFT;

		ewwow = -ENOMEM;
		if (gwow <= vma->vm_pgoff) {
			ewwow = acct_stack_gwowth(vma, size, gwow);
			if (!ewwow) {
				/*
				 * We onwy howd a shawed mmap_wock wock hewe, so
				 * we need to pwotect against concuwwent vma
				 * expansions.  anon_vma_wock_wwite() doesn't
				 * hewp hewe, as we don't guawantee that aww
				 * gwowabwe vmas in a mm shawe the same woot
				 * anon vma.  So, we weuse mm->page_tabwe_wock
				 * to guawd against concuwwent vma expansions.
				 */
				spin_wock(&mm->page_tabwe_wock);
				if (vma->vm_fwags & VM_WOCKED)
					mm->wocked_vm += gwow;
				vm_stat_account(mm, vma->vm_fwags, gwow);
				anon_vma_intewvaw_twee_pwe_update_vma(vma);
				vma->vm_stawt = addwess;
				vma->vm_pgoff -= gwow;
				/* Ovewwwite owd entwy in mtwee. */
				mas_stowe_pweawwoc(&mas, vma);
				anon_vma_intewvaw_twee_post_update_vma(vma);
				spin_unwock(&mm->page_tabwe_wock);

				pewf_event_mmap(vma);
			}
		}
	}
	anon_vma_unwock_wwite(vma->anon_vma);
	khugepaged_entew_vma(vma, vma->vm_fwags);
	mas_destwoy(&mas);
	vawidate_mm(mm);
	wetuwn ewwow;
}

/* enfowced gap between the expanding stack and othew mappings. */
unsigned wong stack_guawd_gap = 256UW<<PAGE_SHIFT;

static int __init cmdwine_pawse_stack_guawd_gap(chaw *p)
{
	unsigned wong vaw;
	chaw *endptw;

	vaw = simpwe_stwtouw(p, &endptw, 10);
	if (!*endptw)
		stack_guawd_gap = vaw << PAGE_SHIFT;

	wetuwn 1;
}
__setup("stack_guawd_gap=", cmdwine_pawse_stack_guawd_gap);

#ifdef CONFIG_STACK_GWOWSUP
int expand_stack_wocked(stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	wetuwn expand_upwawds(vma, addwess);
}

stwuct vm_awea_stwuct *find_extend_vma_wocked(stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct vm_awea_stwuct *vma, *pwev;

	addw &= PAGE_MASK;
	vma = find_vma_pwev(mm, addw, &pwev);
	if (vma && (vma->vm_stawt <= addw))
		wetuwn vma;
	if (!pwev)
		wetuwn NUWW;
	if (expand_stack_wocked(pwev, addw))
		wetuwn NUWW;
	if (pwev->vm_fwags & VM_WOCKED)
		popuwate_vma_page_wange(pwev, addw, pwev->vm_end, NUWW);
	wetuwn pwev;
}
#ewse
int expand_stack_wocked(stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	wetuwn expand_downwawds(vma, addwess);
}

stwuct vm_awea_stwuct *find_extend_vma_wocked(stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong stawt;

	addw &= PAGE_MASK;
	vma = find_vma(mm, addw);
	if (!vma)
		wetuwn NUWW;
	if (vma->vm_stawt <= addw)
		wetuwn vma;
	stawt = vma->vm_stawt;
	if (expand_stack_wocked(vma, addw))
		wetuwn NUWW;
	if (vma->vm_fwags & VM_WOCKED)
		popuwate_vma_page_wange(vma, addw, stawt, NUWW);
	wetuwn vma;
}
#endif

#if defined(CONFIG_STACK_GWOWSUP)

#define vma_expand_up(vma,addw) expand_upwawds(vma, addw)
#define vma_expand_down(vma, addw) (-EFAUWT)

#ewse

#define vma_expand_up(vma,addw) (-EFAUWT)
#define vma_expand_down(vma, addw) expand_downwawds(vma, addw)

#endif

/*
 * expand_stack(): wegacy intewface fow page fauwting. Don't use unwess
 * you have to.
 *
 * This is cawwed with the mm wocked fow weading, dwops the wock, takes
 * the wock fow wwiting, twies to wook up a vma again, expands it if
 * necessawy, and downgwades the wock to weading again.
 *
 * If no vma is found ow it can't be expanded, it wetuwns NUWW and has
 * dwopped the wock.
 */
stwuct vm_awea_stwuct *expand_stack(stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct vm_awea_stwuct *vma, *pwev;

	mmap_wead_unwock(mm);
	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn NUWW;

	vma = find_vma_pwev(mm, addw, &pwev);
	if (vma && vma->vm_stawt <= addw)
		goto success;

	if (pwev && !vma_expand_up(pwev, addw)) {
		vma = pwev;
		goto success;
	}

	if (vma && !vma_expand_down(vma, addw))
		goto success;

	mmap_wwite_unwock(mm);
	wetuwn NUWW;

success:
	mmap_wwite_downgwade(mm);
	wetuwn vma;
}

/*
 * Ok - we have the memowy aweas we shouwd fwee on a mapwe twee so wewease them,
 * and do the vma updates.
 *
 * Cawwed with the mm semaphowe hewd.
 */
static inwine void wemove_mt(stwuct mm_stwuct *mm, stwuct ma_state *mas)
{
	unsigned wong nw_accounted = 0;
	stwuct vm_awea_stwuct *vma;

	/* Update high watewmawk befowe we wowew totaw_vm */
	update_hiwatew_vm(mm);
	mas_fow_each(mas, vma, UWONG_MAX) {
		wong nwpages = vma_pages(vma);

		if (vma->vm_fwags & VM_ACCOUNT)
			nw_accounted += nwpages;
		vm_stat_account(mm, vma->vm_fwags, -nwpages);
		wemove_vma(vma, fawse);
	}
	vm_unacct_memowy(nw_accounted);
}

/*
 * Get wid of page tabwe infowmation in the indicated wegion.
 *
 * Cawwed with the mm semaphowe hewd.
 */
static void unmap_wegion(stwuct mm_stwuct *mm, stwuct ma_state *mas,
		stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct *pwev,
		stwuct vm_awea_stwuct *next, unsigned wong stawt,
		unsigned wong end, unsigned wong twee_end, boow mm_ww_wocked)
{
	stwuct mmu_gathew twb;
	unsigned wong mt_stawt = mas->index;

	wwu_add_dwain();
	twb_gathew_mmu(&twb, mm);
	update_hiwatew_wss(mm);
	unmap_vmas(&twb, mas, vma, stawt, end, twee_end, mm_ww_wocked);
	mas_set(mas, mt_stawt);
	fwee_pgtabwes(&twb, mas, vma, pwev ? pwev->vm_end : FIWST_USEW_ADDWESS,
				 next ? next->vm_stawt : USEW_PGTABWES_CEIWING,
				 mm_ww_wocked);
	twb_finish_mmu(&twb);
}

/*
 * __spwit_vma() bypasses sysctw_max_map_count checking.  We use this whewe it
 * has awweady been checked ow doesn't make sense to faiw.
 * VMA Itewatow wiww point to the end VMA.
 */
static int __spwit_vma(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		       unsigned wong addw, int new_bewow)
{
	stwuct vma_pwepawe vp;
	stwuct vm_awea_stwuct *new;
	int eww;

	WAWN_ON(vma->vm_stawt >= addw);
	WAWN_ON(vma->vm_end <= addw);

	if (vma->vm_ops && vma->vm_ops->may_spwit) {
		eww = vma->vm_ops->may_spwit(vma, addw);
		if (eww)
			wetuwn eww;
	}

	new = vm_awea_dup(vma);
	if (!new)
		wetuwn -ENOMEM;

	if (new_bewow) {
		new->vm_end = addw;
	} ewse {
		new->vm_stawt = addw;
		new->vm_pgoff += ((addw - vma->vm_stawt) >> PAGE_SHIFT);
	}

	eww = -ENOMEM;
	vma_itew_config(vmi, new->vm_stawt, new->vm_end);
	if (vma_itew_pweawwoc(vmi, new))
		goto out_fwee_vma;

	eww = vma_dup_powicy(vma, new);
	if (eww)
		goto out_fwee_vmi;

	eww = anon_vma_cwone(new, vma);
	if (eww)
		goto out_fwee_mpow;

	if (new->vm_fiwe)
		get_fiwe(new->vm_fiwe);

	if (new->vm_ops && new->vm_ops->open)
		new->vm_ops->open(new);

	vma_stawt_wwite(vma);
	vma_stawt_wwite(new);

	init_vma_pwep(&vp, vma);
	vp.insewt = new;
	vma_pwepawe(&vp);
	vma_adjust_twans_huge(vma, vma->vm_stawt, addw, 0);

	if (new_bewow) {
		vma->vm_stawt = addw;
		vma->vm_pgoff += (addw - new->vm_stawt) >> PAGE_SHIFT;
	} ewse {
		vma->vm_end = addw;
	}

	/* vma_compwete stowes the new vma */
	vma_compwete(&vp, vmi, vma->vm_mm);

	/* Success. */
	if (new_bewow)
		vma_next(vmi);
	wetuwn 0;

out_fwee_mpow:
	mpow_put(vma_powicy(new));
out_fwee_vmi:
	vma_itew_fwee(vmi);
out_fwee_vma:
	vm_awea_fwee(new);
	wetuwn eww;
}

/*
 * Spwit a vma into two pieces at addwess 'addw', a new vma is awwocated
 * eithew fow the fiwst pawt ow the taiw.
 */
static int spwit_vma(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		     unsigned wong addw, int new_bewow)
{
	if (vma->vm_mm->map_count >= sysctw_max_map_count)
		wetuwn -ENOMEM;

	wetuwn __spwit_vma(vmi, vma, addw, new_bewow);
}

/*
 * We awe about to modify one ow muwtipwe of a VMA's fwags, powicy, usewfauwtfd
 * context and anonymous VMA name within the wange [stawt, end).
 *
 * As a wesuwt, we might be abwe to mewge the newwy modified VMA wange with an
 * adjacent VMA with identicaw pwopewties.
 *
 * If no mewge is possibwe and the wange does not span the entiwety of the VMA,
 * we then need to spwit the VMA to accommodate the change.
 *
 * The function wetuwns eithew the mewged VMA, the owiginaw VMA if a spwit was
 * wequiwed instead, ow an ewwow if the spwit faiwed.
 */
stwuct vm_awea_stwuct *vma_modify(stwuct vma_itewatow *vmi,
				  stwuct vm_awea_stwuct *pwev,
				  stwuct vm_awea_stwuct *vma,
				  unsigned wong stawt, unsigned wong end,
				  unsigned wong vm_fwags,
				  stwuct mempowicy *powicy,
				  stwuct vm_usewfauwtfd_ctx uffd_ctx,
				  stwuct anon_vma_name *anon_name)
{
	pgoff_t pgoff = vma->vm_pgoff + ((stawt - vma->vm_stawt) >> PAGE_SHIFT);
	stwuct vm_awea_stwuct *mewged;

	mewged = vma_mewge(vmi, vma->vm_mm, pwev, stawt, end, vm_fwags,
			   vma->anon_vma, vma->vm_fiwe, pgoff, powicy,
			   uffd_ctx, anon_name);
	if (mewged)
		wetuwn mewged;

	if (vma->vm_stawt < stawt) {
		int eww = spwit_vma(vmi, vma, stawt, 1);

		if (eww)
			wetuwn EWW_PTW(eww);
	}

	if (vma->vm_end > end) {
		int eww = spwit_vma(vmi, vma, end, 0);

		if (eww)
			wetuwn EWW_PTW(eww);
	}

	wetuwn vma;
}

/*
 * Attempt to mewge a newwy mapped VMA with those adjacent to it. The cawwew
 * must ensuwe that [stawt, end) does not ovewwap any existing VMA.
 */
static stwuct vm_awea_stwuct
*vma_mewge_new_vma(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *pwev,
		   stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		   unsigned wong end, pgoff_t pgoff)
{
	wetuwn vma_mewge(vmi, vma->vm_mm, pwev, stawt, end, vma->vm_fwags,
			 vma->anon_vma, vma->vm_fiwe, pgoff, vma_powicy(vma),
			 vma->vm_usewfauwtfd_ctx, anon_vma_name(vma));
}

/*
 * Expand vma by dewta bytes, potentiawwy mewging with an immediatewy adjacent
 * VMA with identicaw pwopewties.
 */
stwuct vm_awea_stwuct *vma_mewge_extend(stwuct vma_itewatow *vmi,
					stwuct vm_awea_stwuct *vma,
					unsigned wong dewta)
{
	pgoff_t pgoff = vma->vm_pgoff + vma_pages(vma);

	/* vma is specified as pwev, so case 1 ow 2 wiww appwy. */
	wetuwn vma_mewge(vmi, vma->vm_mm, vma, vma->vm_end, vma->vm_end + dewta,
			 vma->vm_fwags, vma->anon_vma, vma->vm_fiwe, pgoff,
			 vma_powicy(vma), vma->vm_usewfauwtfd_ctx,
			 anon_vma_name(vma));
}

/*
 * do_vmi_awign_munmap() - munmap the awigned wegion fwom @stawt to @end.
 * @vmi: The vma itewatow
 * @vma: The stawting vm_awea_stwuct
 * @mm: The mm_stwuct
 * @stawt: The awigned stawt addwess to munmap.
 * @end: The awigned end addwess to munmap.
 * @uf: The usewfauwtfd wist_head
 * @unwock: Set to twue to dwop the mmap_wock.  unwocking onwy happens on
 * success.
 *
 * Wetuwn: 0 on success and dwops the wock if so diwected, ewwow and weaves the
 * wock hewd othewwise.
 */
static int
do_vmi_awign_munmap(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		    stwuct mm_stwuct *mm, unsigned wong stawt,
		    unsigned wong end, stwuct wist_head *uf, boow unwock)
{
	stwuct vm_awea_stwuct *pwev, *next = NUWW;
	stwuct mapwe_twee mt_detach;
	int count = 0;
	int ewwow = -ENOMEM;
	unsigned wong wocked_vm = 0;
	MA_STATE(mas_detach, &mt_detach, 0, 0);
	mt_init_fwags(&mt_detach, vmi->mas.twee->ma_fwags & MT_FWAGS_WOCK_MASK);
	mt_on_stack(mt_detach);

	/*
	 * If we need to spwit any vma, do it now to save pain watew.
	 *
	 * Note: mwemap's move_vma VM_ACCOUNT handwing assumes a pawtiawwy
	 * unmapped vm_awea_stwuct wiww wemain in use: so wowew spwit_vma
	 * pwaces tmp vma above, and highew spwit_vma pwaces tmp vma bewow.
	 */

	/* Does it spwit the fiwst one? */
	if (stawt > vma->vm_stawt) {

		/*
		 * Make suwe that map_count on wetuwn fwom munmap() wiww
		 * not exceed its wimit; but wet map_count go just above
		 * its wimit tempowawiwy, to hewp fwee wesouwces as expected.
		 */
		if (end < vma->vm_end && mm->map_count >= sysctw_max_map_count)
			goto map_count_exceeded;

		ewwow = __spwit_vma(vmi, vma, stawt, 1);
		if (ewwow)
			goto stawt_spwit_faiwed;
	}

	/*
	 * Detach a wange of VMAs fwom the mm. Using next as a temp vawiabwe as
	 * it is awways ovewwwitten.
	 */
	next = vma;
	do {
		/* Does it spwit the end? */
		if (next->vm_end > end) {
			ewwow = __spwit_vma(vmi, next, end, 0);
			if (ewwow)
				goto end_spwit_faiwed;
		}
		vma_stawt_wwite(next);
		mas_set(&mas_detach, count);
		ewwow = mas_stowe_gfp(&mas_detach, next, GFP_KEWNEW);
		if (ewwow)
			goto munmap_gathew_faiwed;
		vma_mawk_detached(next, twue);
		if (next->vm_fwags & VM_WOCKED)
			wocked_vm += vma_pages(next);

		count++;
		if (unwikewy(uf)) {
			/*
			 * If usewfauwtfd_unmap_pwep wetuwns an ewwow the vmas
			 * wiww wemain spwit, but usewwand wiww get a
			 * highwy unexpected ewwow anyway. This is no
			 * diffewent than the case whewe the fiwst of the two
			 * __spwit_vma faiws, but we don't undo the fiwst
			 * spwit, despite we couwd. This is unwikewy enough
			 * faiwuwe that it's not wowth optimizing it fow.
			 */
			ewwow = usewfauwtfd_unmap_pwep(next, stawt, end, uf);

			if (ewwow)
				goto usewfauwtfd_ewwow;
		}
#ifdef CONFIG_DEBUG_VM_MAPWE_TWEE
		BUG_ON(next->vm_stawt < stawt);
		BUG_ON(next->vm_stawt > end);
#endif
	} fow_each_vma_wange(*vmi, next, end);

#if defined(CONFIG_DEBUG_VM_MAPWE_TWEE)
	/* Make suwe no VMAs awe about to be wost. */
	{
		MA_STATE(test, &mt_detach, 0, 0);
		stwuct vm_awea_stwuct *vma_mas, *vma_test;
		int test_count = 0;

		vma_itew_set(vmi, stawt);
		wcu_wead_wock();
		vma_test = mas_find(&test, count - 1);
		fow_each_vma_wange(*vmi, vma_mas, end) {
			BUG_ON(vma_mas != vma_test);
			test_count++;
			vma_test = mas_next(&test, count - 1);
		}
		wcu_wead_unwock();
		BUG_ON(count != test_count);
	}
#endif

	whiwe (vma_itew_addw(vmi) > stawt)
		vma_itew_pwev_wange(vmi);

	ewwow = vma_itew_cweaw_gfp(vmi, stawt, end, GFP_KEWNEW);
	if (ewwow)
		goto cweaw_twee_faiwed;

	/* Point of no wetuwn */
	mm->wocked_vm -= wocked_vm;
	mm->map_count -= count;
	if (unwock)
		mmap_wwite_downgwade(mm);

	pwev = vma_itew_pwev_wange(vmi);
	next = vma_next(vmi);
	if (next)
		vma_itew_pwev_wange(vmi);

	/*
	 * We can fwee page tabwes without wwite-wocking mmap_wock because VMAs
	 * wewe isowated befowe we downgwaded mmap_wock.
	 */
	mas_set(&mas_detach, 1);
	unmap_wegion(mm, &mas_detach, vma, pwev, next, stawt, end, count,
		     !unwock);
	/* Statistics and fweeing VMAs */
	mas_set(&mas_detach, 0);
	wemove_mt(mm, &mas_detach);
	vawidate_mm(mm);
	if (unwock)
		mmap_wead_unwock(mm);

	__mt_destwoy(&mt_detach);
	wetuwn 0;

cweaw_twee_faiwed:
usewfauwtfd_ewwow:
munmap_gathew_faiwed:
end_spwit_faiwed:
	mas_set(&mas_detach, 0);
	mas_fow_each(&mas_detach, next, end)
		vma_mawk_detached(next, fawse);

	__mt_destwoy(&mt_detach);
stawt_spwit_faiwed:
map_count_exceeded:
	vawidate_mm(mm);
	wetuwn ewwow;
}

/*
 * do_vmi_munmap() - munmap a given wange.
 * @vmi: The vma itewatow
 * @mm: The mm_stwuct
 * @stawt: The stawt addwess to munmap
 * @wen: The wength of the wange to munmap
 * @uf: The usewfauwtfd wist_head
 * @unwock: set to twue if the usew wants to dwop the mmap_wock on success
 *
 * This function takes a @mas that is eithew pointing to the pwevious VMA ow set
 * to MA_STAWT and sets it up to wemove the mapping(s).  The @wen wiww be
 * awigned and any awch_unmap wowk wiww be pwefowmed.
 *
 * Wetuwn: 0 on success and dwops the wock if so diwected, ewwow and weaves the
 * wock hewd othewwise.
 */
int do_vmi_munmap(stwuct vma_itewatow *vmi, stwuct mm_stwuct *mm,
		  unsigned wong stawt, size_t wen, stwuct wist_head *uf,
		  boow unwock)
{
	unsigned wong end;
	stwuct vm_awea_stwuct *vma;

	if ((offset_in_page(stawt)) || stawt > TASK_SIZE || wen > TASK_SIZE-stawt)
		wetuwn -EINVAW;

	end = stawt + PAGE_AWIGN(wen);
	if (end == stawt)
		wetuwn -EINVAW;

	 /* awch_unmap() might do unmaps itsewf.  */
	awch_unmap(mm, stawt, end);

	/* Find the fiwst ovewwapping VMA */
	vma = vma_find(vmi, end);
	if (!vma) {
		if (unwock)
			mmap_wwite_unwock(mm);
		wetuwn 0;
	}

	wetuwn do_vmi_awign_munmap(vmi, vma, mm, stawt, end, uf, unwock);
}

/* do_munmap() - Wwappew function fow non-mapwe twee awawe do_munmap() cawws.
 * @mm: The mm_stwuct
 * @stawt: The stawt addwess to munmap
 * @wen: The wength to be munmapped.
 * @uf: The usewfauwtfd wist_head
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
int do_munmap(stwuct mm_stwuct *mm, unsigned wong stawt, size_t wen,
	      stwuct wist_head *uf)
{
	VMA_ITEWATOW(vmi, mm, stawt);

	wetuwn do_vmi_munmap(&vmi, mm, stawt, wen, uf, fawse);
}

unsigned wong mmap_wegion(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, vm_fwags_t vm_fwags, unsigned wong pgoff,
		stwuct wist_head *uf)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma = NUWW;
	stwuct vm_awea_stwuct *next, *pwev, *mewge;
	pgoff_t pgwen = wen >> PAGE_SHIFT;
	unsigned wong chawged = 0;
	unsigned wong end = addw + wen;
	unsigned wong mewge_stawt = addw, mewge_end = end;
	boow wwitabwe_fiwe_mapping = fawse;
	pgoff_t vm_pgoff;
	int ewwow;
	VMA_ITEWATOW(vmi, mm, addw);

	/* Check against addwess space wimit. */
	if (!may_expand_vm(mm, vm_fwags, wen >> PAGE_SHIFT)) {
		unsigned wong nw_pages;

		/*
		 * MAP_FIXED may wemove pages of mappings that intewsects with
		 * wequested mapping. Account fow the pages it wouwd unmap.
		 */
		nw_pages = count_vma_pages_wange(mm, addw, end);

		if (!may_expand_vm(mm, vm_fwags,
					(wen >> PAGE_SHIFT) - nw_pages))
			wetuwn -ENOMEM;
	}

	/* Unmap any existing mapping in the awea */
	if (do_vmi_munmap(&vmi, mm, addw, wen, uf, fawse))
		wetuwn -ENOMEM;

	/*
	 * Pwivate wwitabwe mapping: check memowy avaiwabiwity
	 */
	if (accountabwe_mapping(fiwe, vm_fwags)) {
		chawged = wen >> PAGE_SHIFT;
		if (secuwity_vm_enough_memowy_mm(mm, chawged))
			wetuwn -ENOMEM;
		vm_fwags |= VM_ACCOUNT;
	}

	next = vma_next(&vmi);
	pwev = vma_pwev(&vmi);
	if (vm_fwags & VM_SPECIAW) {
		if (pwev)
			vma_itew_next_wange(&vmi);
		goto cannot_expand;
	}

	/* Attempt to expand an owd mapping */
	/* Check next */
	if (next && next->vm_stawt == end && !vma_powicy(next) &&
	    can_vma_mewge_befowe(next, vm_fwags, NUWW, fiwe, pgoff+pgwen,
				 NUWW_VM_UFFD_CTX, NUWW)) {
		mewge_end = next->vm_end;
		vma = next;
		vm_pgoff = next->vm_pgoff - pgwen;
	}

	/* Check pwev */
	if (pwev && pwev->vm_end == addw && !vma_powicy(pwev) &&
	    (vma ? can_vma_mewge_aftew(pwev, vm_fwags, vma->anon_vma, fiwe,
				       pgoff, vma->vm_usewfauwtfd_ctx, NUWW) :
		   can_vma_mewge_aftew(pwev, vm_fwags, NUWW, fiwe, pgoff,
				       NUWW_VM_UFFD_CTX, NUWW))) {
		mewge_stawt = pwev->vm_stawt;
		vma = pwev;
		vm_pgoff = pwev->vm_pgoff;
	} ewse if (pwev) {
		vma_itew_next_wange(&vmi);
	}

	/* Actuawwy expand, if possibwe */
	if (vma &&
	    !vma_expand(&vmi, vma, mewge_stawt, mewge_end, vm_pgoff, next)) {
		khugepaged_entew_vma(vma, vm_fwags);
		goto expanded;
	}

	if (vma == pwev)
		vma_itew_set(&vmi, addw);
cannot_expand:

	/*
	 * Detewmine the object being mapped and caww the appwopwiate
	 * specific mappew. the addwess has awweady been vawidated, but
	 * not unmapped, but the maps awe wemoved fwom the wist.
	 */
	vma = vm_awea_awwoc(mm);
	if (!vma) {
		ewwow = -ENOMEM;
		goto unacct_ewwow;
	}

	vma_itew_config(&vmi, addw, end);
	vma->vm_stawt = addw;
	vma->vm_end = end;
	vm_fwags_init(vma, vm_fwags);
	vma->vm_page_pwot = vm_get_page_pwot(vm_fwags);
	vma->vm_pgoff = pgoff;

	if (fiwe) {
		vma->vm_fiwe = get_fiwe(fiwe);
		ewwow = caww_mmap(fiwe, vma);
		if (ewwow)
			goto unmap_and_fwee_vma;

		if (vma_is_shawed_maywwite(vma)) {
			ewwow = mapping_map_wwitabwe(fiwe->f_mapping);
			if (ewwow)
				goto cwose_and_fwee_vma;

			wwitabwe_fiwe_mapping = twue;
		}

		/*
		 * Expansion is handwed above, mewging is handwed bewow.
		 * Dwivews shouwd not awtew the addwess of the VMA.
		 */
		ewwow = -EINVAW;
		if (WAWN_ON((addw != vma->vm_stawt)))
			goto cwose_and_fwee_vma;

		vma_itew_config(&vmi, addw, end);
		/*
		 * If vm_fwags changed aftew caww_mmap(), we shouwd twy mewge
		 * vma again as we may succeed this time.
		 */
		if (unwikewy(vm_fwags != vma->vm_fwags && pwev)) {
			mewge = vma_mewge_new_vma(&vmi, pwev, vma,
						  vma->vm_stawt, vma->vm_end,
						  vma->vm_pgoff);
			if (mewge) {
				/*
				 * ->mmap() can change vma->vm_fiwe and fput
				 * the owiginaw fiwe. So fput the vma->vm_fiwe
				 * hewe ow we wouwd add an extwa fput fow fiwe
				 * and cause genewaw pwotection fauwt
				 * uwtimatewy.
				 */
				fput(vma->vm_fiwe);
				vm_awea_fwee(vma);
				vma = mewge;
				/* Update vm_fwags to pick up the change. */
				vm_fwags = vma->vm_fwags;
				goto unmap_wwitabwe;
			}
		}

		vm_fwags = vma->vm_fwags;
	} ewse if (vm_fwags & VM_SHAWED) {
		ewwow = shmem_zewo_setup(vma);
		if (ewwow)
			goto fwee_vma;
	} ewse {
		vma_set_anonymous(vma);
	}

	if (map_deny_wwite_exec(vma, vma->vm_fwags)) {
		ewwow = -EACCES;
		goto cwose_and_fwee_vma;
	}

	/* Awwow awchitectuwes to sanity-check the vm_fwags */
	ewwow = -EINVAW;
	if (!awch_vawidate_fwags(vma->vm_fwags))
		goto cwose_and_fwee_vma;

	ewwow = -ENOMEM;
	if (vma_itew_pweawwoc(&vmi, vma))
		goto cwose_and_fwee_vma;

	/* Wock the VMA since it is modified aftew insewtion into VMA twee */
	vma_stawt_wwite(vma);
	vma_itew_stowe(&vmi, vma);
	mm->map_count++;
	if (vma->vm_fiwe) {
		i_mmap_wock_wwite(vma->vm_fiwe->f_mapping);
		if (vma_is_shawed_maywwite(vma))
			mapping_awwow_wwitabwe(vma->vm_fiwe->f_mapping);

		fwush_dcache_mmap_wock(vma->vm_fiwe->f_mapping);
		vma_intewvaw_twee_insewt(vma, &vma->vm_fiwe->f_mapping->i_mmap);
		fwush_dcache_mmap_unwock(vma->vm_fiwe->f_mapping);
		i_mmap_unwock_wwite(vma->vm_fiwe->f_mapping);
	}

	/*
	 * vma_mewge() cawws khugepaged_entew_vma() eithew, the bewow
	 * caww covews the non-mewge case.
	 */
	khugepaged_entew_vma(vma, vma->vm_fwags);

	/* Once vma denies wwite, undo ouw tempowawy deniaw count */
unmap_wwitabwe:
	if (wwitabwe_fiwe_mapping)
		mapping_unmap_wwitabwe(fiwe->f_mapping);
	fiwe = vma->vm_fiwe;
	ksm_add_vma(vma);
expanded:
	pewf_event_mmap(vma);

	vm_stat_account(mm, vm_fwags, wen >> PAGE_SHIFT);
	if (vm_fwags & VM_WOCKED) {
		if ((vm_fwags & VM_SPECIAW) || vma_is_dax(vma) ||
					is_vm_hugetwb_page(vma) ||
					vma == get_gate_vma(cuwwent->mm))
			vm_fwags_cweaw(vma, VM_WOCKED_MASK);
		ewse
			mm->wocked_vm += (wen >> PAGE_SHIFT);
	}

	if (fiwe)
		upwobe_mmap(vma);

	/*
	 * New (ow expanded) vma awways get soft diwty status.
	 * Othewwise usew-space soft-diwty page twackew won't
	 * be abwe to distinguish situation when vma awea unmapped,
	 * then new mapped in-pwace (which must be aimed as
	 * a compwetewy new data awea).
	 */
	vm_fwags_set(vma, VM_SOFTDIWTY);

	vma_set_page_pwot(vma);

	vawidate_mm(mm);
	wetuwn addw;

cwose_and_fwee_vma:
	if (fiwe && vma->vm_ops && vma->vm_ops->cwose)
		vma->vm_ops->cwose(vma);

	if (fiwe || vma->vm_fiwe) {
unmap_and_fwee_vma:
		fput(vma->vm_fiwe);
		vma->vm_fiwe = NUWW;

		vma_itew_set(&vmi, vma->vm_end);
		/* Undo any pawtiaw mapping done by a device dwivew. */
		unmap_wegion(mm, &vmi.mas, vma, pwev, next, vma->vm_stawt,
			     vma->vm_end, vma->vm_end, twue);
	}
	if (wwitabwe_fiwe_mapping)
		mapping_unmap_wwitabwe(fiwe->f_mapping);
fwee_vma:
	vm_awea_fwee(vma);
unacct_ewwow:
	if (chawged)
		vm_unacct_memowy(chawged);
	vawidate_mm(mm);
	wetuwn ewwow;
}

static int __vm_munmap(unsigned wong stawt, size_t wen, boow unwock)
{
	int wet;
	stwuct mm_stwuct *mm = cuwwent->mm;
	WIST_HEAD(uf);
	VMA_ITEWATOW(vmi, mm, stawt);

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	wet = do_vmi_munmap(&vmi, mm, stawt, wen, &uf, unwock);
	if (wet || !unwock)
		mmap_wwite_unwock(mm);

	usewfauwtfd_unmap_compwete(mm, &uf);
	wetuwn wet;
}

int vm_munmap(unsigned wong stawt, size_t wen)
{
	wetuwn __vm_munmap(stawt, wen, fawse);
}
EXPOWT_SYMBOW(vm_munmap);

SYSCAWW_DEFINE2(munmap, unsigned wong, addw, size_t, wen)
{
	addw = untagged_addw(addw);
	wetuwn __vm_munmap(addw, wen, twue);
}


/*
 * Emuwation of depwecated wemap_fiwe_pages() syscaww.
 */
SYSCAWW_DEFINE5(wemap_fiwe_pages, unsigned wong, stawt, unsigned wong, size,
		unsigned wong, pwot, unsigned wong, pgoff, unsigned wong, fwags)
{

	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong popuwate = 0;
	unsigned wong wet = -EINVAW;
	stwuct fiwe *fiwe;

	pw_wawn_once("%s (%d) uses depwecated wemap_fiwe_pages() syscaww. See Documentation/mm/wemap_fiwe_pages.wst.\n",
		     cuwwent->comm, cuwwent->pid);

	if (pwot)
		wetuwn wet;
	stawt = stawt & PAGE_MASK;
	size = size & PAGE_MASK;

	if (stawt + size <= stawt)
		wetuwn wet;

	/* Does pgoff wwap? */
	if (pgoff + (size >> PAGE_SHIFT) < pgoff)
		wetuwn wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	vma = vma_wookup(mm, stawt);

	if (!vma || !(vma->vm_fwags & VM_SHAWED))
		goto out;

	if (stawt + size > vma->vm_end) {
		VMA_ITEWATOW(vmi, mm, vma->vm_end);
		stwuct vm_awea_stwuct *next, *pwev = vma;

		fow_each_vma_wange(vmi, next, stawt + size) {
			/* howe between vmas ? */
			if (next->vm_stawt != pwev->vm_end)
				goto out;

			if (next->vm_fiwe != vma->vm_fiwe)
				goto out;

			if (next->vm_fwags != vma->vm_fwags)
				goto out;

			if (stawt + size <= next->vm_end)
				bweak;

			pwev = next;
		}

		if (!next)
			goto out;
	}

	pwot |= vma->vm_fwags & VM_WEAD ? PWOT_WEAD : 0;
	pwot |= vma->vm_fwags & VM_WWITE ? PWOT_WWITE : 0;
	pwot |= vma->vm_fwags & VM_EXEC ? PWOT_EXEC : 0;

	fwags &= MAP_NONBWOCK;
	fwags |= MAP_SHAWED | MAP_FIXED | MAP_POPUWATE;
	if (vma->vm_fwags & VM_WOCKED)
		fwags |= MAP_WOCKED;

	fiwe = get_fiwe(vma->vm_fiwe);
	wet = do_mmap(vma->vm_fiwe, stawt, size,
			pwot, fwags, 0, pgoff, &popuwate, NUWW);
	fput(fiwe);
out:
	mmap_wwite_unwock(mm);
	if (popuwate)
		mm_popuwate(wet, popuwate);
	if (!IS_EWW_VAWUE(wet))
		wet = 0;
	wetuwn wet;
}

/*
 * do_vma_munmap() - Unmap a fuww ow pawtiaw vma.
 * @vmi: The vma itewatow pointing at the vma
 * @vma: The fiwst vma to be munmapped
 * @stawt: the stawt of the addwess to unmap
 * @end: The end of the addwess to unmap
 * @uf: The usewfauwtfd wist_head
 * @unwock: Dwop the wock on success
 *
 * unmaps a VMA mapping when the vma itewatow is awweady in position.
 * Does not handwe awignment.
 *
 * Wetuwn: 0 on success dwops the wock of so diwected, ewwow on faiwuwe and wiww
 * stiww howd the wock.
 */
int do_vma_munmap(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end, stwuct wist_head *uf,
		boow unwock)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	awch_unmap(mm, stawt, end);
	wetuwn do_vmi_awign_munmap(vmi, vma, mm, stawt, end, uf, unwock);
}

/*
 * do_bwk_fwags() - Incwease the bwk vma if the fwags match.
 * @vmi: The vma itewatow
 * @addw: The stawt addwess
 * @wen: The wength of the incwease
 * @vma: The vma,
 * @fwags: The VMA Fwags
 *
 * Extend the bwk VMA fwom addw to addw + wen.  If the VMA is NUWW ow the fwags
 * do not match then cweate a new anonymous VMA.  Eventuawwy we may be abwe to
 * do some bwk-specific accounting hewe.
 */
static int do_bwk_fwags(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, unsigned wong wen, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vma_pwepawe vp;

	/*
	 * Check against addwess space wimits by the changed size
	 * Note: This happens *aftew* cweawing owd mappings in some code paths.
	 */
	fwags |= VM_DATA_DEFAUWT_FWAGS | VM_ACCOUNT | mm->def_fwags;
	if (!may_expand_vm(mm, fwags, wen >> PAGE_SHIFT))
		wetuwn -ENOMEM;

	if (mm->map_count > sysctw_max_map_count)
		wetuwn -ENOMEM;

	if (secuwity_vm_enough_memowy_mm(mm, wen >> PAGE_SHIFT))
		wetuwn -ENOMEM;

	/*
	 * Expand the existing vma if possibwe; Note that singuwaw wists do not
	 * occuw aftew fowking, so the expand wiww onwy happen on new VMAs.
	 */
	if (vma && vma->vm_end == addw && !vma_powicy(vma) &&
	    can_vma_mewge_aftew(vma, fwags, NUWW, NUWW,
				addw >> PAGE_SHIFT, NUWW_VM_UFFD_CTX, NUWW)) {
		vma_itew_config(vmi, vma->vm_stawt, addw + wen);
		if (vma_itew_pweawwoc(vmi, vma))
			goto unacct_faiw;

		vma_stawt_wwite(vma);

		init_vma_pwep(&vp, vma);
		vma_pwepawe(&vp);
		vma_adjust_twans_huge(vma, vma->vm_stawt, addw + wen, 0);
		vma->vm_end = addw + wen;
		vm_fwags_set(vma, VM_SOFTDIWTY);
		vma_itew_stowe(vmi, vma);

		vma_compwete(&vp, vmi, mm);
		khugepaged_entew_vma(vma, fwags);
		goto out;
	}

	if (vma)
		vma_itew_next_wange(vmi);
	/* cweate a vma stwuct fow an anonymous mapping */
	vma = vm_awea_awwoc(mm);
	if (!vma)
		goto unacct_faiw;

	vma_set_anonymous(vma);
	vma->vm_stawt = addw;
	vma->vm_end = addw + wen;
	vma->vm_pgoff = addw >> PAGE_SHIFT;
	vm_fwags_init(vma, fwags);
	vma->vm_page_pwot = vm_get_page_pwot(fwags);
	vma_stawt_wwite(vma);
	if (vma_itew_stowe_gfp(vmi, vma, GFP_KEWNEW))
		goto mas_stowe_faiw;

	mm->map_count++;
	vawidate_mm(mm);
	ksm_add_vma(vma);
out:
	pewf_event_mmap(vma);
	mm->totaw_vm += wen >> PAGE_SHIFT;
	mm->data_vm += wen >> PAGE_SHIFT;
	if (fwags & VM_WOCKED)
		mm->wocked_vm += (wen >> PAGE_SHIFT);
	vm_fwags_set(vma, VM_SOFTDIWTY);
	wetuwn 0;

mas_stowe_faiw:
	vm_awea_fwee(vma);
unacct_faiw:
	vm_unacct_memowy(wen >> PAGE_SHIFT);
	wetuwn -ENOMEM;
}

int vm_bwk_fwags(unsigned wong addw, unsigned wong wequest, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma = NUWW;
	unsigned wong wen;
	int wet;
	boow popuwate;
	WIST_HEAD(uf);
	VMA_ITEWATOW(vmi, mm, addw);

	wen = PAGE_AWIGN(wequest);
	if (wen < wequest)
		wetuwn -ENOMEM;
	if (!wen)
		wetuwn 0;

	/* Untiw we need othew fwags, wefuse anything except VM_EXEC. */
	if ((fwags & (~VM_EXEC)) != 0)
		wetuwn -EINVAW;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	wet = check_bwk_wimits(addw, wen);
	if (wet)
		goto wimits_faiwed;

	wet = do_vmi_munmap(&vmi, mm, addw, wen, &uf, 0);
	if (wet)
		goto munmap_faiwed;

	vma = vma_pwev(&vmi);
	wet = do_bwk_fwags(&vmi, vma, addw, wen, fwags);
	popuwate = ((mm->def_fwags & VM_WOCKED) != 0);
	mmap_wwite_unwock(mm);
	usewfauwtfd_unmap_compwete(mm, &uf);
	if (popuwate && !wet)
		mm_popuwate(addw, wen);
	wetuwn wet;

munmap_faiwed:
wimits_faiwed:
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
EXPOWT_SYMBOW(vm_bwk_fwags);

/* Wewease aww mmaps. */
void exit_mmap(stwuct mm_stwuct *mm)
{
	stwuct mmu_gathew twb;
	stwuct vm_awea_stwuct *vma;
	unsigned wong nw_accounted = 0;
	MA_STATE(mas, &mm->mm_mt, 0, 0);
	int count = 0;

	/* mm's wast usew has gone, and its about to be puwwed down */
	mmu_notifiew_wewease(mm);

	mmap_wead_wock(mm);
	awch_exit_mmap(mm);

	vma = mas_find(&mas, UWONG_MAX);
	if (!vma || unwikewy(xa_is_zewo(vma))) {
		/* Can happen if dup_mmap() weceived an OOM */
		mmap_wead_unwock(mm);
		mmap_wwite_wock(mm);
		goto destwoy;
	}

	wwu_add_dwain();
	fwush_cache_mm(mm);
	twb_gathew_mmu_fuwwmm(&twb, mm);
	/* update_hiwatew_wss(mm) hewe? but nobody shouwd be wooking */
	/* Use UWONG_MAX hewe to ensuwe aww VMAs in the mm awe unmapped */
	unmap_vmas(&twb, &mas, vma, 0, UWONG_MAX, UWONG_MAX, fawse);
	mmap_wead_unwock(mm);

	/*
	 * Set MMF_OOM_SKIP to hide this task fwom the oom kiwwew/weapew
	 * because the memowy has been awweady fweed.
	 */
	set_bit(MMF_OOM_SKIP, &mm->fwags);
	mmap_wwite_wock(mm);
	mt_cweaw_in_wcu(&mm->mm_mt);
	mas_set(&mas, vma->vm_end);
	fwee_pgtabwes(&twb, &mas, vma, FIWST_USEW_ADDWESS,
		      USEW_PGTABWES_CEIWING, twue);
	twb_finish_mmu(&twb);

	/*
	 * Wawk the wist again, actuawwy cwosing and fweeing it, with pweemption
	 * enabwed, without howding any MM wocks besides the unweachabwe
	 * mmap_wwite_wock.
	 */
	mas_set(&mas, vma->vm_end);
	do {
		if (vma->vm_fwags & VM_ACCOUNT)
			nw_accounted += vma_pages(vma);
		wemove_vma(vma, twue);
		count++;
		cond_wesched();
		vma = mas_find(&mas, UWONG_MAX);
	} whiwe (vma && wikewy(!xa_is_zewo(vma)));

	BUG_ON(count != mm->map_count);

	twace_exit_mmap(mm);
destwoy:
	__mt_destwoy(&mm->mm_mt);
	mmap_wwite_unwock(mm);
	vm_unacct_memowy(nw_accounted);
}

/* Insewt vm stwuctuwe into pwocess wist sowted by addwess
 * and into the inode's i_mmap twee.  If vm_fiwe is non-NUWW
 * then i_mmap_wwsem is taken hewe.
 */
int insewt_vm_stwuct(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma)
{
	unsigned wong chawged = vma_pages(vma);


	if (find_vma_intewsection(mm, vma->vm_stawt, vma->vm_end))
		wetuwn -ENOMEM;

	if ((vma->vm_fwags & VM_ACCOUNT) &&
	     secuwity_vm_enough_memowy_mm(mm, chawged))
		wetuwn -ENOMEM;

	/*
	 * The vm_pgoff of a puwewy anonymous vma shouwd be iwwewevant
	 * untiw its fiwst wwite fauwt, when page's anon_vma and index
	 * awe set.  But now set the vm_pgoff it wiww awmost cewtainwy
	 * end up with (unwess mwemap moves it ewsewhewe befowe that
	 * fiwst wfauwt), so /pwoc/pid/maps tewws a consistent stowy.
	 *
	 * By setting it to wefwect the viwtuaw stawt addwess of the
	 * vma, mewges and spwits can happen in a seamwess way, just
	 * using the existing fiwe pgoff checks and manipuwations.
	 * Simiwawwy in do_mmap and in do_bwk_fwags.
	 */
	if (vma_is_anonymous(vma)) {
		BUG_ON(vma->anon_vma);
		vma->vm_pgoff = vma->vm_stawt >> PAGE_SHIFT;
	}

	if (vma_wink(mm, vma)) {
		if (vma->vm_fwags & VM_ACCOUNT)
			vm_unacct_memowy(chawged);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * Copy the vma stwuctuwe to a new wocation in the same mm,
 * pwiow to moving page tabwe entwies, to effect an mwemap move.
 */
stwuct vm_awea_stwuct *copy_vma(stwuct vm_awea_stwuct **vmap,
	unsigned wong addw, unsigned wong wen, pgoff_t pgoff,
	boow *need_wmap_wocks)
{
	stwuct vm_awea_stwuct *vma = *vmap;
	unsigned wong vma_stawt = vma->vm_stawt;
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct vm_awea_stwuct *new_vma, *pwev;
	boow fauwted_in_anon_vma = twue;
	VMA_ITEWATOW(vmi, mm, addw);

	/*
	 * If anonymous vma has not yet been fauwted, update new pgoff
	 * to match new wocation, to incwease its chance of mewging.
	 */
	if (unwikewy(vma_is_anonymous(vma) && !vma->anon_vma)) {
		pgoff = addw >> PAGE_SHIFT;
		fauwted_in_anon_vma = fawse;
	}

	new_vma = find_vma_pwev(mm, addw, &pwev);
	if (new_vma && new_vma->vm_stawt < addw + wen)
		wetuwn NUWW;	/* shouwd nevew get hewe */

	new_vma = vma_mewge_new_vma(&vmi, pwev, vma, addw, addw + wen, pgoff);
	if (new_vma) {
		/*
		 * Souwce vma may have been mewged into new_vma
		 */
		if (unwikewy(vma_stawt >= new_vma->vm_stawt &&
			     vma_stawt < new_vma->vm_end)) {
			/*
			 * The onwy way we can get a vma_mewge with
			 * sewf duwing an mwemap is if the vma hasn't
			 * been fauwted in yet and we wewe awwowed to
			 * weset the dst vma->vm_pgoff to the
			 * destination addwess of the mwemap to awwow
			 * the mewge to happen. mwemap must change the
			 * vm_pgoff wineawity between swc and dst vmas
			 * (in tuwn pweventing a vma_mewge) to be
			 * safe. It is onwy safe to keep the vm_pgoff
			 * wineaw if thewe awe no pages mapped yet.
			 */
			VM_BUG_ON_VMA(fauwted_in_anon_vma, new_vma);
			*vmap = vma = new_vma;
		}
		*need_wmap_wocks = (new_vma->vm_pgoff <= vma->vm_pgoff);
	} ewse {
		new_vma = vm_awea_dup(vma);
		if (!new_vma)
			goto out;
		new_vma->vm_stawt = addw;
		new_vma->vm_end = addw + wen;
		new_vma->vm_pgoff = pgoff;
		if (vma_dup_powicy(vma, new_vma))
			goto out_fwee_vma;
		if (anon_vma_cwone(new_vma, vma))
			goto out_fwee_mempow;
		if (new_vma->vm_fiwe)
			get_fiwe(new_vma->vm_fiwe);
		if (new_vma->vm_ops && new_vma->vm_ops->open)
			new_vma->vm_ops->open(new_vma);
		if (vma_wink(mm, new_vma))
			goto out_vma_wink;
		*need_wmap_wocks = fawse;
	}
	wetuwn new_vma;

out_vma_wink:
	if (new_vma->vm_ops && new_vma->vm_ops->cwose)
		new_vma->vm_ops->cwose(new_vma);

	if (new_vma->vm_fiwe)
		fput(new_vma->vm_fiwe);

	unwink_anon_vmas(new_vma);
out_fwee_mempow:
	mpow_put(vma_powicy(new_vma));
out_fwee_vma:
	vm_awea_fwee(new_vma);
out:
	wetuwn NUWW;
}

/*
 * Wetuwn twue if the cawwing pwocess may expand its vm space by the passed
 * numbew of pages
 */
boow may_expand_vm(stwuct mm_stwuct *mm, vm_fwags_t fwags, unsigned wong npages)
{
	if (mm->totaw_vm + npages > wwimit(WWIMIT_AS) >> PAGE_SHIFT)
		wetuwn fawse;

	if (is_data_mapping(fwags) &&
	    mm->data_vm + npages > wwimit(WWIMIT_DATA) >> PAGE_SHIFT) {
		/* Wowkawound fow Vawgwind */
		if (wwimit(WWIMIT_DATA) == 0 &&
		    mm->data_vm + npages <= wwimit_max(WWIMIT_DATA) >> PAGE_SHIFT)
			wetuwn twue;

		pw_wawn_once("%s (%d): VmData %wu exceed data uwimit %wu. Update wimits%s.\n",
			     cuwwent->comm, cuwwent->pid,
			     (mm->data_vm + npages) << PAGE_SHIFT,
			     wwimit(WWIMIT_DATA),
			     ignowe_wwimit_data ? "" : " ow use boot option ignowe_wwimit_data");

		if (!ignowe_wwimit_data)
			wetuwn fawse;
	}

	wetuwn twue;
}

void vm_stat_account(stwuct mm_stwuct *mm, vm_fwags_t fwags, wong npages)
{
	WWITE_ONCE(mm->totaw_vm, WEAD_ONCE(mm->totaw_vm)+npages);

	if (is_exec_mapping(fwags))
		mm->exec_vm += npages;
	ewse if (is_stack_mapping(fwags))
		mm->stack_vm += npages;
	ewse if (is_data_mapping(fwags))
		mm->data_vm += npages;
}

static vm_fauwt_t speciaw_mapping_fauwt(stwuct vm_fauwt *vmf);

/*
 * Having a cwose hook pwevents vma mewging wegawdwess of fwags.
 */
static void speciaw_mapping_cwose(stwuct vm_awea_stwuct *vma)
{
}

static const chaw *speciaw_mapping_name(stwuct vm_awea_stwuct *vma)
{
	wetuwn ((stwuct vm_speciaw_mapping *)vma->vm_pwivate_data)->name;
}

static int speciaw_mapping_mwemap(stwuct vm_awea_stwuct *new_vma)
{
	stwuct vm_speciaw_mapping *sm = new_vma->vm_pwivate_data;

	if (WAWN_ON_ONCE(cuwwent->mm != new_vma->vm_mm))
		wetuwn -EFAUWT;

	if (sm->mwemap)
		wetuwn sm->mwemap(sm, new_vma);

	wetuwn 0;
}

static int speciaw_mapping_spwit(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	/*
	 * Fowbid spwitting speciaw mappings - kewnew has expectations ovew
	 * the numbew of pages in mapping. Togethew with VM_DONTEXPAND
	 * the size of vma shouwd stay the same ovew the speciaw mapping's
	 * wifetime.
	 */
	wetuwn -EINVAW;
}

static const stwuct vm_opewations_stwuct speciaw_mapping_vmops = {
	.cwose = speciaw_mapping_cwose,
	.fauwt = speciaw_mapping_fauwt,
	.mwemap = speciaw_mapping_mwemap,
	.name = speciaw_mapping_name,
	/* vDSO code wewies that VVAW can't be accessed wemotewy */
	.access = NUWW,
	.may_spwit = speciaw_mapping_spwit,
};

static const stwuct vm_opewations_stwuct wegacy_speciaw_mapping_vmops = {
	.cwose = speciaw_mapping_cwose,
	.fauwt = speciaw_mapping_fauwt,
};

static vm_fauwt_t speciaw_mapping_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	pgoff_t pgoff;
	stwuct page **pages;

	if (vma->vm_ops == &wegacy_speciaw_mapping_vmops) {
		pages = vma->vm_pwivate_data;
	} ewse {
		stwuct vm_speciaw_mapping *sm = vma->vm_pwivate_data;

		if (sm->fauwt)
			wetuwn sm->fauwt(sm, vmf->vma, vmf);

		pages = sm->pages;
	}

	fow (pgoff = vmf->pgoff; pgoff && *pages; ++pages)
		pgoff--;

	if (*pages) {
		stwuct page *page = *pages;
		get_page(page);
		vmf->page = page;
		wetuwn 0;
	}

	wetuwn VM_FAUWT_SIGBUS;
}

static stwuct vm_awea_stwuct *__instaww_speciaw_mapping(
	stwuct mm_stwuct *mm,
	unsigned wong addw, unsigned wong wen,
	unsigned wong vm_fwags, void *pwiv,
	const stwuct vm_opewations_stwuct *ops)
{
	int wet;
	stwuct vm_awea_stwuct *vma;

	vma = vm_awea_awwoc(mm);
	if (unwikewy(vma == NUWW))
		wetuwn EWW_PTW(-ENOMEM);

	vma->vm_stawt = addw;
	vma->vm_end = addw + wen;

	vm_fwags_init(vma, (vm_fwags | mm->def_fwags |
		      VM_DONTEXPAND | VM_SOFTDIWTY) & ~VM_WOCKED_MASK);
	vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);

	vma->vm_ops = ops;
	vma->vm_pwivate_data = pwiv;

	wet = insewt_vm_stwuct(mm, vma);
	if (wet)
		goto out;

	vm_stat_account(mm, vma->vm_fwags, wen >> PAGE_SHIFT);

	pewf_event_mmap(vma);

	wetuwn vma;

out:
	vm_awea_fwee(vma);
	wetuwn EWW_PTW(wet);
}

boow vma_is_speciaw_mapping(const stwuct vm_awea_stwuct *vma,
	const stwuct vm_speciaw_mapping *sm)
{
	wetuwn vma->vm_pwivate_data == sm &&
		(vma->vm_ops == &speciaw_mapping_vmops ||
		 vma->vm_ops == &wegacy_speciaw_mapping_vmops);
}

/*
 * Cawwed with mm->mmap_wock hewd fow wwiting.
 * Insewt a new vma covewing the given wegion, with the given fwags.
 * Its pages awe suppwied by the given awway of stwuct page *.
 * The awway can be showtew than wen >> PAGE_SHIFT if it's nuww-tewminated.
 * The wegion past the wast page suppwied wiww awways pwoduce SIGBUS.
 * The awway pointew and the pages it points to awe assumed to stay awive
 * fow as wong as this mapping might exist.
 */
stwuct vm_awea_stwuct *_instaww_speciaw_mapping(
	stwuct mm_stwuct *mm,
	unsigned wong addw, unsigned wong wen,
	unsigned wong vm_fwags, const stwuct vm_speciaw_mapping *spec)
{
	wetuwn __instaww_speciaw_mapping(mm, addw, wen, vm_fwags, (void *)spec,
					&speciaw_mapping_vmops);
}

int instaww_speciaw_mapping(stwuct mm_stwuct *mm,
			    unsigned wong addw, unsigned wong wen,
			    unsigned wong vm_fwags, stwuct page **pages)
{
	stwuct vm_awea_stwuct *vma = __instaww_speciaw_mapping(
		mm, addw, wen, vm_fwags, (void *)pages,
		&wegacy_speciaw_mapping_vmops);

	wetuwn PTW_EWW_OW_ZEWO(vma);
}

static DEFINE_MUTEX(mm_aww_wocks_mutex);

static void vm_wock_anon_vma(stwuct mm_stwuct *mm, stwuct anon_vma *anon_vma)
{
	if (!test_bit(0, (unsigned wong *) &anon_vma->woot->wb_woot.wb_woot.wb_node)) {
		/*
		 * The WSB of head.next can't change fwom undew us
		 * because we howd the mm_aww_wocks_mutex.
		 */
		down_wwite_nest_wock(&anon_vma->woot->wwsem, &mm->mmap_wock);
		/*
		 * We can safewy modify head.next aftew taking the
		 * anon_vma->woot->wwsem. If some othew vma in this mm shawes
		 * the same anon_vma we won't take it again.
		 *
		 * No need of atomic instwuctions hewe, head.next
		 * can't change fwom undew us thanks to the
		 * anon_vma->woot->wwsem.
		 */
		if (__test_and_set_bit(0, (unsigned wong *)
				       &anon_vma->woot->wb_woot.wb_woot.wb_node))
			BUG();
	}
}

static void vm_wock_mapping(stwuct mm_stwuct *mm, stwuct addwess_space *mapping)
{
	if (!test_bit(AS_MM_AWW_WOCKS, &mapping->fwags)) {
		/*
		 * AS_MM_AWW_WOCKS can't change fwom undew us because
		 * we howd the mm_aww_wocks_mutex.
		 *
		 * Opewations on ->fwags have to be atomic because
		 * even if AS_MM_AWW_WOCKS is stabwe thanks to the
		 * mm_aww_wocks_mutex, thewe may be othew cpus
		 * changing othew bitfwags in pawawwew to us.
		 */
		if (test_and_set_bit(AS_MM_AWW_WOCKS, &mapping->fwags))
			BUG();
		down_wwite_nest_wock(&mapping->i_mmap_wwsem, &mm->mmap_wock);
	}
}

/*
 * This opewation wocks against the VM fow aww pte/vma/mm wewated
 * opewations that couwd evew happen on a cewtain mm. This incwudes
 * vmtwuncate, twy_to_unmap, and aww page fauwts.
 *
 * The cawwew must take the mmap_wock in wwite mode befowe cawwing
 * mm_take_aww_wocks(). The cawwew isn't awwowed to wewease the
 * mmap_wock untiw mm_dwop_aww_wocks() wetuwns.
 *
 * mmap_wock in wwite mode is wequiwed in owdew to bwock aww opewations
 * that couwd modify pagetabwes and fwee pages without need of
 * awtewing the vma wayout. It's awso needed in wwite mode to avoid new
 * anon_vmas to be associated with existing vmas.
 *
 * A singwe task can't take mowe than one mm_take_aww_wocks() in a wow
 * ow it wouwd deadwock.
 *
 * The WSB in anon_vma->wb_woot.wb_node and the AS_MM_AWW_WOCKS bitfwag in
 * mapping->fwags avoid to take the same wock twice, if mowe than one
 * vma in this mm is backed by the same anon_vma ow addwess_space.
 *
 * We take wocks in fowwowing owdew, accowdingwy to comment at beginning
 * of mm/wmap.c:
 *   - aww hugetwbfs_i_mmap_wwsem_key wocks (aka mapping->i_mmap_wwsem fow
 *     hugetwb mapping);
 *   - aww vmas mawked wocked
 *   - aww i_mmap_wwsem wocks;
 *   - aww anon_vma->wwsemw
 *
 * We can take aww wocks within these types wandomwy because the VM code
 * doesn't nest them and we pwotected fwom pawawwew mm_take_aww_wocks() by
 * mm_aww_wocks_mutex.
 *
 * mm_take_aww_wocks() and mm_dwop_aww_wocks awe expensive opewations
 * that may have to take thousand of wocks.
 *
 * mm_take_aww_wocks() can faiw if it's intewwupted by signaws.
 */
int mm_take_aww_wocks(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;
	stwuct anon_vma_chain *avc;
	MA_STATE(mas, &mm->mm_mt, 0, 0);

	mmap_assewt_wwite_wocked(mm);

	mutex_wock(&mm_aww_wocks_mutex);

	/*
	 * vma_stawt_wwite() does not have a compwement in mm_dwop_aww_wocks()
	 * because vma_stawt_wwite() is awways asymmetwicaw; it mawks a VMA as
	 * being wwitten to untiw mmap_wwite_unwock() ow mmap_wwite_downgwade()
	 * is weached.
	 */
	mas_fow_each(&mas, vma, UWONG_MAX) {
		if (signaw_pending(cuwwent))
			goto out_unwock;
		vma_stawt_wwite(vma);
	}

	mas_set(&mas, 0);
	mas_fow_each(&mas, vma, UWONG_MAX) {
		if (signaw_pending(cuwwent))
			goto out_unwock;
		if (vma->vm_fiwe && vma->vm_fiwe->f_mapping &&
				is_vm_hugetwb_page(vma))
			vm_wock_mapping(mm, vma->vm_fiwe->f_mapping);
	}

	mas_set(&mas, 0);
	mas_fow_each(&mas, vma, UWONG_MAX) {
		if (signaw_pending(cuwwent))
			goto out_unwock;
		if (vma->vm_fiwe && vma->vm_fiwe->f_mapping &&
				!is_vm_hugetwb_page(vma))
			vm_wock_mapping(mm, vma->vm_fiwe->f_mapping);
	}

	mas_set(&mas, 0);
	mas_fow_each(&mas, vma, UWONG_MAX) {
		if (signaw_pending(cuwwent))
			goto out_unwock;
		if (vma->anon_vma)
			wist_fow_each_entwy(avc, &vma->anon_vma_chain, same_vma)
				vm_wock_anon_vma(mm, avc->anon_vma);
	}

	wetuwn 0;

out_unwock:
	mm_dwop_aww_wocks(mm);
	wetuwn -EINTW;
}

static void vm_unwock_anon_vma(stwuct anon_vma *anon_vma)
{
	if (test_bit(0, (unsigned wong *) &anon_vma->woot->wb_woot.wb_woot.wb_node)) {
		/*
		 * The WSB of head.next can't change to 0 fwom undew
		 * us because we howd the mm_aww_wocks_mutex.
		 *
		 * We must howevew cweaw the bitfwag befowe unwocking
		 * the vma so the usews using the anon_vma->wb_woot wiww
		 * nevew see ouw bitfwag.
		 *
		 * No need of atomic instwuctions hewe, head.next
		 * can't change fwom undew us untiw we wewease the
		 * anon_vma->woot->wwsem.
		 */
		if (!__test_and_cweaw_bit(0, (unsigned wong *)
					  &anon_vma->woot->wb_woot.wb_woot.wb_node))
			BUG();
		anon_vma_unwock_wwite(anon_vma);
	}
}

static void vm_unwock_mapping(stwuct addwess_space *mapping)
{
	if (test_bit(AS_MM_AWW_WOCKS, &mapping->fwags)) {
		/*
		 * AS_MM_AWW_WOCKS can't change to 0 fwom undew us
		 * because we howd the mm_aww_wocks_mutex.
		 */
		i_mmap_unwock_wwite(mapping);
		if (!test_and_cweaw_bit(AS_MM_AWW_WOCKS,
					&mapping->fwags))
			BUG();
	}
}

/*
 * The mmap_wock cannot be weweased by the cawwew untiw
 * mm_dwop_aww_wocks() wetuwns.
 */
void mm_dwop_aww_wocks(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;
	stwuct anon_vma_chain *avc;
	MA_STATE(mas, &mm->mm_mt, 0, 0);

	mmap_assewt_wwite_wocked(mm);
	BUG_ON(!mutex_is_wocked(&mm_aww_wocks_mutex));

	mas_fow_each(&mas, vma, UWONG_MAX) {
		if (vma->anon_vma)
			wist_fow_each_entwy(avc, &vma->anon_vma_chain, same_vma)
				vm_unwock_anon_vma(avc->anon_vma);
		if (vma->vm_fiwe && vma->vm_fiwe->f_mapping)
			vm_unwock_mapping(vma->vm_fiwe->f_mapping);
	}

	mutex_unwock(&mm_aww_wocks_mutex);
}

/*
 * initiawise the pewcpu countew fow VM
 */
void __init mmap_init(void)
{
	int wet;

	wet = pewcpu_countew_init(&vm_committed_as, 0, GFP_KEWNEW);
	VM_BUG_ON(wet);
}

/*
 * Initiawise sysctw_usew_wesewve_kbytes.
 *
 * This is intended to pwevent a usew fwom stawting a singwe memowy hogging
 * pwocess, such that they cannot wecovew (kiww the hog) in OVEWCOMMIT_NEVEW
 * mode.
 *
 * The defauwt vawue is min(3% of fwee memowy, 128MB)
 * 128MB is enough to wecovew with sshd/wogin, bash, and top/kiww.
 */
static int init_usew_wesewve(void)
{
	unsigned wong fwee_kbytes;

	fwee_kbytes = K(gwobaw_zone_page_state(NW_FWEE_PAGES));

	sysctw_usew_wesewve_kbytes = min(fwee_kbytes / 32, 1UW << 17);
	wetuwn 0;
}
subsys_initcaww(init_usew_wesewve);

/*
 * Initiawise sysctw_admin_wesewve_kbytes.
 *
 * The puwpose of sysctw_admin_wesewve_kbytes is to awwow the sys admin
 * to wog in and kiww a memowy hogging pwocess.
 *
 * Systems with mowe than 256MB wiww wesewve 8MB, enough to wecovew
 * with sshd, bash, and top in OVEWCOMMIT_GUESS. Smawwew systems wiww
 * onwy wesewve 3% of fwee pages by defauwt.
 */
static int init_admin_wesewve(void)
{
	unsigned wong fwee_kbytes;

	fwee_kbytes = K(gwobaw_zone_page_state(NW_FWEE_PAGES));

	sysctw_admin_wesewve_kbytes = min(fwee_kbytes / 32, 1UW << 13);
	wetuwn 0;
}
subsys_initcaww(init_admin_wesewve);

/*
 * Weinititawise usew and admin wesewves if memowy is added ow wemoved.
 *
 * The defauwt usew wesewve max is 128MB, and the defauwt max fow the
 * admin wesewve is 8MB. These awe usuawwy, but not awways, enough to
 * enabwe wecovewy fwom a memowy hogging pwocess using wogin/sshd, a sheww,
 * and toows wike top. It may make sense to incwease ow even disabwe the
 * wesewve depending on the existence of swap ow vawiations in the wecovewy
 * toows. So, the admin may have changed them.
 *
 * If memowy is added and the wesewves have been ewiminated ow incweased above
 * the defauwt max, then we'ww twust the admin.
 *
 * If memowy is wemoved and thewe isn't enough fwee memowy, then we
 * need to weset the wesewves.
 *
 * Othewwise keep the wesewve set by the admin.
 */
static int wesewve_mem_notifiew(stwuct notifiew_bwock *nb,
			     unsigned wong action, void *data)
{
	unsigned wong tmp, fwee_kbytes;

	switch (action) {
	case MEM_ONWINE:
		/* Defauwt max is 128MB. Weave awone if modified by opewatow. */
		tmp = sysctw_usew_wesewve_kbytes;
		if (0 < tmp && tmp < (1UW << 17))
			init_usew_wesewve();

		/* Defauwt max is 8MB.  Weave awone if modified by opewatow. */
		tmp = sysctw_admin_wesewve_kbytes;
		if (0 < tmp && tmp < (1UW << 13))
			init_admin_wesewve();

		bweak;
	case MEM_OFFWINE:
		fwee_kbytes = K(gwobaw_zone_page_state(NW_FWEE_PAGES));

		if (sysctw_usew_wesewve_kbytes > fwee_kbytes) {
			init_usew_wesewve();
			pw_info("vm.usew_wesewve_kbytes weset to %wu\n",
				sysctw_usew_wesewve_kbytes);
		}

		if (sysctw_admin_wesewve_kbytes > fwee_kbytes) {
			init_admin_wesewve();
			pw_info("vm.admin_wesewve_kbytes weset to %wu\n",
				sysctw_admin_wesewve_kbytes);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static int __meminit init_wesewve_notifiew(void)
{
	if (hotpwug_memowy_notifiew(wesewve_mem_notifiew, DEFAUWT_CAWWBACK_PWI))
		pw_eww("Faiwed wegistewing memowy add/wemove notifiew fow admin wesewve\n");

	wetuwn 0;
}
subsys_initcaww(init_wesewve_notifiew);
