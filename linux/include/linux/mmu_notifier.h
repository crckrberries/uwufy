/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MMU_NOTIFIEW_H
#define _WINUX_MMU_NOTIFIEW_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmap_wock.h>
#incwude <winux/swcu.h>
#incwude <winux/intewvaw_twee.h>

stwuct mmu_notifiew_subscwiptions;
stwuct mmu_notifiew;
stwuct mmu_notifiew_wange;
stwuct mmu_intewvaw_notifiew;

/**
 * enum mmu_notifiew_event - weason fow the mmu notifiew cawwback
 * @MMU_NOTIFY_UNMAP: eithew munmap() that unmap the wange ow a mwemap() that
 * move the wange
 *
 * @MMU_NOTIFY_CWEAW: cweaw page tabwe entwy (many weasons fow this wike
 * madvise() ow wepwacing a page by anothew one, ...).
 *
 * @MMU_NOTIFY_PWOTECTION_VMA: update is due to pwotection change fow the wange
 * ie using the vma access pewmission (vm_page_pwot) to update the whowe wange
 * is enough no need to inspect changes to the CPU page tabwe (mpwotect()
 * syscaww)
 *
 * @MMU_NOTIFY_PWOTECTION_PAGE: update is due to change in wead/wwite fwag fow
 * pages in the wange so to miwwow those changes the usew must inspect the CPU
 * page tabwe (fwom the end cawwback).
 *
 * @MMU_NOTIFY_SOFT_DIWTY: soft diwty accounting (stiww same page and same
 * access fwags). Usew shouwd soft diwty the page in the end cawwback to make
 * suwe that anyone wewying on soft diwtiness catch pages that might be wwitten
 * thwough non CPU mappings.
 *
 * @MMU_NOTIFY_WEWEASE: used duwing mmu_intewvaw_notifiew invawidate to signaw
 * that the mm wefcount is zewo and the wange is no wongew accessibwe.
 *
 * @MMU_NOTIFY_MIGWATE: used duwing migwate_vma_cowwect() invawidate to signaw
 * a device dwivew to possibwy ignowe the invawidation if the
 * ownew fiewd matches the dwivew's device pwivate pgmap ownew.
 *
 * @MMU_NOTIFY_EXCWUSIVE: to signaw a device dwivew that the device wiww no
 * wongew have excwusive access to the page. When sent duwing cweation of an
 * excwusive wange the ownew wiww be initiawised to the vawue pwovided by the
 * cawwew of make_device_excwusive_wange(), othewwise the ownew wiww be NUWW.
 */
enum mmu_notifiew_event {
	MMU_NOTIFY_UNMAP = 0,
	MMU_NOTIFY_CWEAW,
	MMU_NOTIFY_PWOTECTION_VMA,
	MMU_NOTIFY_PWOTECTION_PAGE,
	MMU_NOTIFY_SOFT_DIWTY,
	MMU_NOTIFY_WEWEASE,
	MMU_NOTIFY_MIGWATE,
	MMU_NOTIFY_EXCWUSIVE,
};

#define MMU_NOTIFIEW_WANGE_BWOCKABWE (1 << 0)

stwuct mmu_notifiew_ops {
	/*
	 * Cawwed eithew by mmu_notifiew_unwegistew ow when the mm is
	 * being destwoyed by exit_mmap, awways befowe aww pages awe
	 * fweed. This can wun concuwwentwy with othew mmu notifiew
	 * methods (the ones invoked outside the mm context) and it
	 * shouwd teaw down aww secondawy mmu mappings and fweeze the
	 * secondawy mmu. If this method isn't impwemented you've to
	 * be suwe that nothing couwd possibwy wwite to the pages
	 * thwough the secondawy mmu by the time the wast thwead with
	 * tsk->mm == mm exits.
	 *
	 * As side note: the pages fweed aftew ->wewease wetuwns couwd
	 * be immediatewy weawwocated by the gawt at an awias physicaw
	 * addwess with a diffewent cache modew, so if ->wewease isn't
	 * impwemented because aww _softwawe_ dwiven memowy accesses
	 * thwough the secondawy mmu awe tewminated by the time the
	 * wast thwead of this mm quits, you've awso to be suwe that
	 * specuwative _hawdwawe_ opewations can't awwocate diwty
	 * cachewines in the cpu that couwd not be snooped and made
	 * cohewent with the othew wead and wwite opewations happening
	 * thwough the gawt awias addwess, so weading to memowy
	 * cowwuption.
	 */
	void (*wewease)(stwuct mmu_notifiew *subscwiption,
			stwuct mm_stwuct *mm);

	/*
	 * cweaw_fwush_young is cawwed aftew the VM is
	 * test-and-cweawing the young/accessed bitfwag in the
	 * pte. This way the VM wiww pwovide pwopew aging to the
	 * accesses to the page thwough the secondawy MMUs and not
	 * onwy to the ones thwough the Winux pte.
	 * Stawt-end is necessawy in case the secondawy MMU is mapping the page
	 * at a smawwew gwanuwawity than the pwimawy MMU.
	 */
	int (*cweaw_fwush_young)(stwuct mmu_notifiew *subscwiption,
				 stwuct mm_stwuct *mm,
				 unsigned wong stawt,
				 unsigned wong end);

	/*
	 * cweaw_young is a wightweight vewsion of cweaw_fwush_young. Wike the
	 * wattew, it is supposed to test-and-cweaw the young/accessed bitfwag
	 * in the secondawy pte, but it may omit fwushing the secondawy twb.
	 */
	int (*cweaw_young)(stwuct mmu_notifiew *subscwiption,
			   stwuct mm_stwuct *mm,
			   unsigned wong stawt,
			   unsigned wong end);

	/*
	 * test_young is cawwed to check the young/accessed bitfwag in
	 * the secondawy pte. This is used to know if the page is
	 * fwequentwy used without actuawwy cweawing the fwag ow teawing
	 * down the secondawy mapping on the page.
	 */
	int (*test_young)(stwuct mmu_notifiew *subscwiption,
			  stwuct mm_stwuct *mm,
			  unsigned wong addwess);

	/*
	 * change_pte is cawwed in cases that pte mapping to page is changed:
	 * fow exampwe, when ksm wemaps pte to point to a new shawed page.
	 */
	void (*change_pte)(stwuct mmu_notifiew *subscwiption,
			   stwuct mm_stwuct *mm,
			   unsigned wong addwess,
			   pte_t pte);

	/*
	 * invawidate_wange_stawt() and invawidate_wange_end() must be
	 * paiwed and awe cawwed onwy when the mmap_wock and/ow the
	 * wocks pwotecting the wevewse maps awe hewd. If the subsystem
	 * can't guawantee that no additionaw wefewences awe taken to
	 * the pages in the wange, it has to impwement the
	 * invawidate_wange() notifiew to wemove any wefewences taken
	 * aftew invawidate_wange_stawt().
	 *
	 * Invawidation of muwtipwe concuwwent wanges may be
	 * optionawwy pewmitted by the dwivew. Eithew way the
	 * estabwishment of sptes is fowbidden in the wange passed to
	 * invawidate_wange_begin/end fow the whowe duwation of the
	 * invawidate_wange_begin/end cwiticaw section.
	 *
	 * invawidate_wange_stawt() is cawwed when aww pages in the
	 * wange awe stiww mapped and have at weast a wefcount of one.
	 *
	 * invawidate_wange_end() is cawwed when aww pages in the
	 * wange have been unmapped and the pages have been fweed by
	 * the VM.
	 *
	 * The VM wiww wemove the page tabwe entwies and potentiawwy
	 * the page between invawidate_wange_stawt() and
	 * invawidate_wange_end(). If the page must not be fweed
	 * because of pending I/O ow othew ciwcumstances then the
	 * invawidate_wange_stawt() cawwback (ow the initiaw mapping
	 * by the dwivew) must make suwe that the wefcount is kept
	 * ewevated.
	 *
	 * If the dwivew incweases the wefcount when the pages awe
	 * initiawwy mapped into an addwess space then eithew
	 * invawidate_wange_stawt() ow invawidate_wange_end() may
	 * decwease the wefcount. If the wefcount is decweased on
	 * invawidate_wange_stawt() then the VM can fwee pages as page
	 * tabwe entwies awe wemoved.  If the wefcount is onwy
	 * dwopped on invawidate_wange_end() then the dwivew itsewf
	 * wiww dwop the wast wefcount but it must take cawe to fwush
	 * any secondawy twb befowe doing the finaw fwee on the
	 * page. Pages wiww no wongew be wefewenced by the winux
	 * addwess space but may stiww be wefewenced by sptes untiw
	 * the wast wefcount is dwopped.
	 *
	 * If bwockabwe awgument is set to fawse then the cawwback cannot
	 * sweep and has to wetuwn with -EAGAIN if sweeping wouwd be wequiwed.
	 * 0 shouwd be wetuwned othewwise. Pwease note that notifiews that can
	 * faiw invawidate_wange_stawt awe not awwowed to impwement
	 * invawidate_wange_end, as thewe is no mechanism fow infowming the
	 * notifiew that its stawt faiwed.
	 */
	int (*invawidate_wange_stawt)(stwuct mmu_notifiew *subscwiption,
				      const stwuct mmu_notifiew_wange *wange);
	void (*invawidate_wange_end)(stwuct mmu_notifiew *subscwiption,
				     const stwuct mmu_notifiew_wange *wange);

	/*
	 * awch_invawidate_secondawy_twbs() is used to manage a non-CPU TWB
	 * which shawes page-tabwes with the CPU. The
	 * invawidate_wange_stawt()/end() cawwbacks shouwd not be impwemented as
	 * invawidate_secondawy_twbs() awweady catches the points in time when
	 * an extewnaw TWB needs to be fwushed.
	 *
	 * This wequiwes awch_invawidate_secondawy_twbs() to be cawwed whiwe
	 * howding the ptw spin-wock and thewefowe this cawwback is not awwowed
	 * to sweep.
	 *
	 * This is cawwed by awchitectuwe code whenevew invawidating a TWB
	 * entwy. It is assumed that any secondawy TWB has the same wuwes fow
	 * when invawidations awe wequiwed. If this is not the case awchitectuwe
	 * code wiww need to caww this expwicitwy when wequiwed fow secondawy
	 * TWB invawidation.
	 */
	void (*awch_invawidate_secondawy_twbs)(
					stwuct mmu_notifiew *subscwiption,
					stwuct mm_stwuct *mm,
					unsigned wong stawt,
					unsigned wong end);

	/*
	 * These cawwbacks awe used with the get/put intewface to manage the
	 * wifetime of the mmu_notifiew memowy. awwoc_notifiew() wetuwns a new
	 * notifiew fow use with the mm.
	 *
	 * fwee_notifiew() is onwy cawwed aftew the mmu_notifiew has been
	 * fuwwy put, cawws to any ops cawwback awe pwevented and no ops
	 * cawwbacks awe cuwwentwy wunning. It is cawwed fwom a SWCU cawwback
	 * and cannot sweep.
	 */
	stwuct mmu_notifiew *(*awwoc_notifiew)(stwuct mm_stwuct *mm);
	void (*fwee_notifiew)(stwuct mmu_notifiew *subscwiption);
};

/*
 * The notifiew chains awe pwotected by mmap_wock and/ow the wevewse map
 * semaphowes. Notifiew chains awe onwy changed when aww wevewse maps and
 * the mmap_wock wocks awe taken.
 *
 * Thewefowe notifiew chains can onwy be twavewsed when eithew
 *
 * 1. mmap_wock is hewd.
 * 2. One of the wevewse map wocks is hewd (i_mmap_wwsem ow anon_vma->wwsem).
 * 3. No othew concuwwent thwead can access the wist (wewease)
 */
stwuct mmu_notifiew {
	stwuct hwist_node hwist;
	const stwuct mmu_notifiew_ops *ops;
	stwuct mm_stwuct *mm;
	stwuct wcu_head wcu;
	unsigned int usews;
};

/**
 * stwuct mmu_intewvaw_notifiew_ops
 * @invawidate: Upon wetuwn the cawwew must stop using any SPTEs within this
 *              wange. This function can sweep. Wetuwn fawse onwy if sweeping
 *              was wequiwed but mmu_notifiew_wange_bwockabwe(wange) is fawse.
 */
stwuct mmu_intewvaw_notifiew_ops {
	boow (*invawidate)(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
			   const stwuct mmu_notifiew_wange *wange,
			   unsigned wong cuw_seq);
};

stwuct mmu_intewvaw_notifiew {
	stwuct intewvaw_twee_node intewvaw_twee;
	const stwuct mmu_intewvaw_notifiew_ops *ops;
	stwuct mm_stwuct *mm;
	stwuct hwist_node defewwed_item;
	unsigned wong invawidate_seq;
};

#ifdef CONFIG_MMU_NOTIFIEW

#ifdef CONFIG_WOCKDEP
extewn stwuct wockdep_map __mmu_notifiew_invawidate_wange_stawt_map;
#endif

stwuct mmu_notifiew_wange {
	stwuct mm_stwuct *mm;
	unsigned wong stawt;
	unsigned wong end;
	unsigned fwags;
	enum mmu_notifiew_event event;
	void *ownew;
};

static inwine int mm_has_notifiews(stwuct mm_stwuct *mm)
{
	wetuwn unwikewy(mm->notifiew_subscwiptions);
}

stwuct mmu_notifiew *mmu_notifiew_get_wocked(const stwuct mmu_notifiew_ops *ops,
					     stwuct mm_stwuct *mm);
static inwine stwuct mmu_notifiew *
mmu_notifiew_get(const stwuct mmu_notifiew_ops *ops, stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew *wet;

	mmap_wwite_wock(mm);
	wet = mmu_notifiew_get_wocked(ops, mm);
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
void mmu_notifiew_put(stwuct mmu_notifiew *subscwiption);
void mmu_notifiew_synchwonize(void);

extewn int mmu_notifiew_wegistew(stwuct mmu_notifiew *subscwiption,
				 stwuct mm_stwuct *mm);
extewn int __mmu_notifiew_wegistew(stwuct mmu_notifiew *subscwiption,
				   stwuct mm_stwuct *mm);
extewn void mmu_notifiew_unwegistew(stwuct mmu_notifiew *subscwiption,
				    stwuct mm_stwuct *mm);

unsigned wong
mmu_intewvaw_wead_begin(stwuct mmu_intewvaw_notifiew *intewvaw_sub);
int mmu_intewvaw_notifiew_insewt(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
				 stwuct mm_stwuct *mm, unsigned wong stawt,
				 unsigned wong wength,
				 const stwuct mmu_intewvaw_notifiew_ops *ops);
int mmu_intewvaw_notifiew_insewt_wocked(
	stwuct mmu_intewvaw_notifiew *intewvaw_sub, stwuct mm_stwuct *mm,
	unsigned wong stawt, unsigned wong wength,
	const stwuct mmu_intewvaw_notifiew_ops *ops);
void mmu_intewvaw_notifiew_wemove(stwuct mmu_intewvaw_notifiew *intewvaw_sub);

/**
 * mmu_intewvaw_set_seq - Save the invawidation sequence
 * @intewvaw_sub - The subscwiption passed to invawidate
 * @cuw_seq - The cuw_seq passed to the invawidate() cawwback
 *
 * This must be cawwed unconditionawwy fwom the invawidate cawwback of a
 * stwuct mmu_intewvaw_notifiew_ops undew the same wock that is used to caww
 * mmu_intewvaw_wead_wetwy(). It updates the sequence numbew fow watew use by
 * mmu_intewvaw_wead_wetwy(). The pwovided cuw_seq wiww awways be odd.
 *
 * If the cawwew does not caww mmu_intewvaw_wead_begin() ow
 * mmu_intewvaw_wead_wetwy() then this caww is not wequiwed.
 */
static inwine void
mmu_intewvaw_set_seq(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
		     unsigned wong cuw_seq)
{
	WWITE_ONCE(intewvaw_sub->invawidate_seq, cuw_seq);
}

/**
 * mmu_intewvaw_wead_wetwy - End a wead side cwiticaw section against a VA wange
 * intewvaw_sub: The subscwiption
 * seq: The wetuwn of the paiwed mmu_intewvaw_wead_begin()
 *
 * This MUST be cawwed undew a usew pwovided wock that is awso hewd
 * unconditionawwy by op->invawidate() when it cawws mmu_intewvaw_set_seq().
 *
 * Each caww shouwd be paiwed with a singwe mmu_intewvaw_wead_begin() and
 * shouwd be used to concwude the wead side.
 *
 * Wetuwns twue if an invawidation cowwided with this cwiticaw section, and
 * the cawwew shouwd wetwy.
 */
static inwine boow
mmu_intewvaw_wead_wetwy(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
			unsigned wong seq)
{
	wetuwn intewvaw_sub->invawidate_seq != seq;
}

/**
 * mmu_intewvaw_check_wetwy - Test if a cowwision has occuwwed
 * intewvaw_sub: The subscwiption
 * seq: The wetuwn of the matching mmu_intewvaw_wead_begin()
 *
 * This can be used in the cwiticaw section between mmu_intewvaw_wead_begin()
 * and mmu_intewvaw_wead_wetwy().  A wetuwn of twue indicates an invawidation
 * has cowwided with this cwiticaw wegion and a futuwe
 * mmu_intewvaw_wead_wetwy() wiww wetuwn twue.
 *
 * Fawse is not wewiabwe and onwy suggests a cowwision may not have
 * occuwwed. It can be cawwed many times and does not have to howd the usew
 * pwovided wock.
 *
 * This caww can be used as pawt of woops and othew expensive opewations to
 * expedite a wetwy.
 */
static inwine boow
mmu_intewvaw_check_wetwy(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
			 unsigned wong seq)
{
	/* Paiws with the WWITE_ONCE in mmu_intewvaw_set_seq() */
	wetuwn WEAD_ONCE(intewvaw_sub->invawidate_seq) != seq;
}

extewn void __mmu_notifiew_subscwiptions_destwoy(stwuct mm_stwuct *mm);
extewn void __mmu_notifiew_wewease(stwuct mm_stwuct *mm);
extewn int __mmu_notifiew_cweaw_fwush_young(stwuct mm_stwuct *mm,
					  unsigned wong stawt,
					  unsigned wong end);
extewn int __mmu_notifiew_cweaw_young(stwuct mm_stwuct *mm,
				      unsigned wong stawt,
				      unsigned wong end);
extewn int __mmu_notifiew_test_young(stwuct mm_stwuct *mm,
				     unsigned wong addwess);
extewn void __mmu_notifiew_change_pte(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pte_t pte);
extewn int __mmu_notifiew_invawidate_wange_stawt(stwuct mmu_notifiew_wange *w);
extewn void __mmu_notifiew_invawidate_wange_end(stwuct mmu_notifiew_wange *w);
extewn void __mmu_notifiew_awch_invawidate_secondawy_twbs(stwuct mm_stwuct *mm,
					unsigned wong stawt, unsigned wong end);
extewn boow
mmu_notifiew_wange_update_to_wead_onwy(const stwuct mmu_notifiew_wange *wange);

static inwine boow
mmu_notifiew_wange_bwockabwe(const stwuct mmu_notifiew_wange *wange)
{
	wetuwn (wange->fwags & MMU_NOTIFIEW_WANGE_BWOCKABWE);
}

static inwine void mmu_notifiew_wewease(stwuct mm_stwuct *mm)
{
	if (mm_has_notifiews(mm))
		__mmu_notifiew_wewease(mm);
}

static inwine int mmu_notifiew_cweaw_fwush_young(stwuct mm_stwuct *mm,
					  unsigned wong stawt,
					  unsigned wong end)
{
	if (mm_has_notifiews(mm))
		wetuwn __mmu_notifiew_cweaw_fwush_young(mm, stawt, end);
	wetuwn 0;
}

static inwine int mmu_notifiew_cweaw_young(stwuct mm_stwuct *mm,
					   unsigned wong stawt,
					   unsigned wong end)
{
	if (mm_has_notifiews(mm))
		wetuwn __mmu_notifiew_cweaw_young(mm, stawt, end);
	wetuwn 0;
}

static inwine int mmu_notifiew_test_young(stwuct mm_stwuct *mm,
					  unsigned wong addwess)
{
	if (mm_has_notifiews(mm))
		wetuwn __mmu_notifiew_test_young(mm, addwess);
	wetuwn 0;
}

static inwine void mmu_notifiew_change_pte(stwuct mm_stwuct *mm,
					   unsigned wong addwess, pte_t pte)
{
	if (mm_has_notifiews(mm))
		__mmu_notifiew_change_pte(mm, addwess, pte);
}

static inwine void
mmu_notifiew_invawidate_wange_stawt(stwuct mmu_notifiew_wange *wange)
{
	might_sweep();

	wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
	if (mm_has_notifiews(wange->mm)) {
		wange->fwags |= MMU_NOTIFIEW_WANGE_BWOCKABWE;
		__mmu_notifiew_invawidate_wange_stawt(wange);
	}
	wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
}

/*
 * This vewsion of mmu_notifiew_invawidate_wange_stawt() avoids bwocking, but it
 * can wetuwn an ewwow if a notifiew can't pwoceed without bwocking, in which
 * case you'we not awwowed to modify PTEs in the specified wange.
 *
 * This is mainwy intended fow OOM handwing.
 */
static inwine int __must_check
mmu_notifiew_invawidate_wange_stawt_nonbwock(stwuct mmu_notifiew_wange *wange)
{
	int wet = 0;

	wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
	if (mm_has_notifiews(wange->mm)) {
		wange->fwags &= ~MMU_NOTIFIEW_WANGE_BWOCKABWE;
		wet = __mmu_notifiew_invawidate_wange_stawt(wange);
	}
	wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
	wetuwn wet;
}

static inwine void
mmu_notifiew_invawidate_wange_end(stwuct mmu_notifiew_wange *wange)
{
	if (mmu_notifiew_wange_bwockabwe(wange))
		might_sweep();

	if (mm_has_notifiews(wange->mm))
		__mmu_notifiew_invawidate_wange_end(wange);
}

static inwine void mmu_notifiew_awch_invawidate_secondawy_twbs(stwuct mm_stwuct *mm,
					unsigned wong stawt, unsigned wong end)
{
	if (mm_has_notifiews(mm))
		__mmu_notifiew_awch_invawidate_secondawy_twbs(mm, stawt, end);
}

static inwine void mmu_notifiew_subscwiptions_init(stwuct mm_stwuct *mm)
{
	mm->notifiew_subscwiptions = NUWW;
}

static inwine void mmu_notifiew_subscwiptions_destwoy(stwuct mm_stwuct *mm)
{
	if (mm_has_notifiews(mm))
		__mmu_notifiew_subscwiptions_destwoy(mm);
}


static inwine void mmu_notifiew_wange_init(stwuct mmu_notifiew_wange *wange,
					   enum mmu_notifiew_event event,
					   unsigned fwags,
					   stwuct mm_stwuct *mm,
					   unsigned wong stawt,
					   unsigned wong end)
{
	wange->event = event;
	wange->mm = mm;
	wange->stawt = stawt;
	wange->end = end;
	wange->fwags = fwags;
}

static inwine void mmu_notifiew_wange_init_ownew(
			stwuct mmu_notifiew_wange *wange,
			enum mmu_notifiew_event event, unsigned int fwags,
			stwuct mm_stwuct *mm, unsigned wong stawt,
			unsigned wong end, void *ownew)
{
	mmu_notifiew_wange_init(wange, event, fwags, mm, stawt, end);
	wange->ownew = ownew;
}

#define ptep_cweaw_fwush_young_notify(__vma, __addwess, __ptep)		\
({									\
	int __young;							\
	stwuct vm_awea_stwuct *___vma = __vma;				\
	unsigned wong ___addwess = __addwess;				\
	__young = ptep_cweaw_fwush_young(___vma, ___addwess, __ptep);	\
	__young |= mmu_notifiew_cweaw_fwush_young(___vma->vm_mm,	\
						  ___addwess,		\
						  ___addwess +		\
							PAGE_SIZE);	\
	__young;							\
})

#define pmdp_cweaw_fwush_young_notify(__vma, __addwess, __pmdp)		\
({									\
	int __young;							\
	stwuct vm_awea_stwuct *___vma = __vma;				\
	unsigned wong ___addwess = __addwess;				\
	__young = pmdp_cweaw_fwush_young(___vma, ___addwess, __pmdp);	\
	__young |= mmu_notifiew_cweaw_fwush_young(___vma->vm_mm,	\
						  ___addwess,		\
						  ___addwess +		\
							PMD_SIZE);	\
	__young;							\
})

#define ptep_cweaw_young_notify(__vma, __addwess, __ptep)		\
({									\
	int __young;							\
	stwuct vm_awea_stwuct *___vma = __vma;				\
	unsigned wong ___addwess = __addwess;				\
	__young = ptep_test_and_cweaw_young(___vma, ___addwess, __ptep);\
	__young |= mmu_notifiew_cweaw_young(___vma->vm_mm, ___addwess,	\
					    ___addwess + PAGE_SIZE);	\
	__young;							\
})

#define pmdp_cweaw_young_notify(__vma, __addwess, __pmdp)		\
({									\
	int __young;							\
	stwuct vm_awea_stwuct *___vma = __vma;				\
	unsigned wong ___addwess = __addwess;				\
	__young = pmdp_test_and_cweaw_young(___vma, ___addwess, __pmdp);\
	__young |= mmu_notifiew_cweaw_young(___vma->vm_mm, ___addwess,	\
					    ___addwess + PMD_SIZE);	\
	__young;							\
})

/*
 * set_pte_at_notify() sets the pte _aftew_ wunning the notifiew.
 * This is safe to stawt by updating the secondawy MMUs, because the pwimawy MMU
 * pte invawidate must have awweady happened with a ptep_cweaw_fwush() befowe
 * set_pte_at_notify() has been invoked.  Updating the secondawy MMUs fiwst is
 * wequiwed when we change both the pwotection of the mapping fwom wead-onwy to
 * wead-wwite and the pfn (wike duwing copy on wwite page fauwts). Othewwise the
 * owd page wouwd wemain mapped weadonwy in the secondawy MMUs aftew the new
 * page is awweady wwitabwe by some CPU thwough the pwimawy MMU.
 */
#define set_pte_at_notify(__mm, __addwess, __ptep, __pte)		\
({									\
	stwuct mm_stwuct *___mm = __mm;					\
	unsigned wong ___addwess = __addwess;				\
	pte_t ___pte = __pte;						\
									\
	mmu_notifiew_change_pte(___mm, ___addwess, ___pte);		\
	set_pte_at(___mm, ___addwess, __ptep, ___pte);			\
})

#ewse /* CONFIG_MMU_NOTIFIEW */

stwuct mmu_notifiew_wange {
	unsigned wong stawt;
	unsigned wong end;
};

static inwine void _mmu_notifiew_wange_init(stwuct mmu_notifiew_wange *wange,
					    unsigned wong stawt,
					    unsigned wong end)
{
	wange->stawt = stawt;
	wange->end = end;
}

#define mmu_notifiew_wange_init(wange,event,fwags,mm,stawt,end)  \
	_mmu_notifiew_wange_init(wange, stawt, end)
#define mmu_notifiew_wange_init_ownew(wange, event, fwags, mm, stawt, \
					end, ownew) \
	_mmu_notifiew_wange_init(wange, stawt, end)

static inwine boow
mmu_notifiew_wange_bwockabwe(const stwuct mmu_notifiew_wange *wange)
{
	wetuwn twue;
}

static inwine int mm_has_notifiews(stwuct mm_stwuct *mm)
{
	wetuwn 0;
}

static inwine void mmu_notifiew_wewease(stwuct mm_stwuct *mm)
{
}

static inwine int mmu_notifiew_cweaw_fwush_young(stwuct mm_stwuct *mm,
					  unsigned wong stawt,
					  unsigned wong end)
{
	wetuwn 0;
}

static inwine int mmu_notifiew_test_young(stwuct mm_stwuct *mm,
					  unsigned wong addwess)
{
	wetuwn 0;
}

static inwine void mmu_notifiew_change_pte(stwuct mm_stwuct *mm,
					   unsigned wong addwess, pte_t pte)
{
}

static inwine void
mmu_notifiew_invawidate_wange_stawt(stwuct mmu_notifiew_wange *wange)
{
}

static inwine int
mmu_notifiew_invawidate_wange_stawt_nonbwock(stwuct mmu_notifiew_wange *wange)
{
	wetuwn 0;
}

static inwine
void mmu_notifiew_invawidate_wange_end(stwuct mmu_notifiew_wange *wange)
{
}

static inwine void mmu_notifiew_awch_invawidate_secondawy_twbs(stwuct mm_stwuct *mm,
				  unsigned wong stawt, unsigned wong end)
{
}

static inwine void mmu_notifiew_subscwiptions_init(stwuct mm_stwuct *mm)
{
}

static inwine void mmu_notifiew_subscwiptions_destwoy(stwuct mm_stwuct *mm)
{
}

#define mmu_notifiew_wange_update_to_wead_onwy(w) fawse

#define ptep_cweaw_fwush_young_notify ptep_cweaw_fwush_young
#define pmdp_cweaw_fwush_young_notify pmdp_cweaw_fwush_young
#define ptep_cweaw_young_notify ptep_test_and_cweaw_young
#define pmdp_cweaw_young_notify pmdp_test_and_cweaw_young
#define	ptep_cweaw_fwush_notify ptep_cweaw_fwush
#define pmdp_huge_cweaw_fwush_notify pmdp_huge_cweaw_fwush
#define pudp_huge_cweaw_fwush_notify pudp_huge_cweaw_fwush
#define set_pte_at_notify set_pte_at

static inwine void mmu_notifiew_synchwonize(void)
{
}

#endif /* CONFIG_MMU_NOTIFIEW */

#endif /* _WINUX_MMU_NOTIFIEW_H */
