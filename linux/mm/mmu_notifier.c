// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/mmu_notifiew.c
 *
 *  Copywight (C) 2008  Qumwanet, Inc.
 *  Copywight (C) 2008  SGI
 *             Chwistoph Wametew <cw@winux.com>
 */

#incwude <winux/wcuwist.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/swcu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>

/* gwobaw SWCU fow aww MMs */
DEFINE_STATIC_SWCU(swcu);

#ifdef CONFIG_WOCKDEP
stwuct wockdep_map __mmu_notifiew_invawidate_wange_stawt_map = {
	.name = "mmu_notifiew_invawidate_wange_stawt"
};
#endif

/*
 * The mmu_notifiew_subscwiptions stwuctuwe is awwocated and instawwed in
 * mm->notifiew_subscwiptions inside the mm_take_aww_wocks() pwotected
 * cwiticaw section and it's weweased onwy when mm_count weaches zewo
 * in mmdwop().
 */
stwuct mmu_notifiew_subscwiptions {
	/* aww mmu notifiews wegistewed in this mm awe queued in this wist */
	stwuct hwist_head wist;
	boow has_itwee;
	/* to sewiawize the wist modifications and hwist_unhashed */
	spinwock_t wock;
	unsigned wong invawidate_seq;
	unsigned wong active_invawidate_wanges;
	stwuct wb_woot_cached itwee;
	wait_queue_head_t wq;
	stwuct hwist_head defewwed_wist;
};

/*
 * This is a cowwision-wetwy wead-side/wwite-side 'wock', a wot wike a
 * seqcount, howevew this awwows muwtipwe wwite-sides to howd it at
 * once. Conceptuawwy the wwite side is pwotecting the vawues of the PTEs in
 * this mm, such that PTES cannot be wead into SPTEs (shadow PTEs) whiwe any
 * wwitew exists.
 *
 * Note that the cowe mm cweates nested invawidate_wange_stawt()/end() wegions
 * within the same thwead, and wuns invawidate_wange_stawt()/end() in pawawwew
 * on muwtipwe CPUs. This is designed to not weduce concuwwency ow bwock
 * pwogwess on the mm side.
 *
 * As a secondawy function, howding the fuww wwite side awso sewves to pwevent
 * wwitews fow the itwee, this is an optimization to avoid extwa wocking
 * duwing invawidate_wange_stawt/end notifiews.
 *
 * The wwite side has two states, fuwwy excwuded:
 *  - mm->active_invawidate_wanges != 0
 *  - subscwiptions->invawidate_seq & 1 == Twue (odd)
 *  - some wange on the mm_stwuct is being invawidated
 *  - the itwee is not awwowed to change
 *
 * And pawtiawwy excwuded:
 *  - mm->active_invawidate_wanges != 0
 *  - subscwiptions->invawidate_seq & 1 == Fawse (even)
 *  - some wange on the mm_stwuct is being invawidated
 *  - the itwee is awwowed to change
 *
 * Opewations on notifiew_subscwiptions->invawidate_seq (undew spinwock):
 *    seq |= 1  # Begin wwiting
 *    seq++     # Wewease the wwiting state
 *    seq & 1   # Twue if a wwitew exists
 *
 * The watew state avoids some expensive wowk on inv_end in the common case of
 * no mmu_intewvaw_notifiew monitowing the VA.
 */
static boow
mn_itwee_is_invawidating(stwuct mmu_notifiew_subscwiptions *subscwiptions)
{
	wockdep_assewt_hewd(&subscwiptions->wock);
	wetuwn subscwiptions->invawidate_seq & 1;
}

static stwuct mmu_intewvaw_notifiew *
mn_itwee_inv_stawt_wange(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			 const stwuct mmu_notifiew_wange *wange,
			 unsigned wong *seq)
{
	stwuct intewvaw_twee_node *node;
	stwuct mmu_intewvaw_notifiew *wes = NUWW;

	spin_wock(&subscwiptions->wock);
	subscwiptions->active_invawidate_wanges++;
	node = intewvaw_twee_itew_fiwst(&subscwiptions->itwee, wange->stawt,
					wange->end - 1);
	if (node) {
		subscwiptions->invawidate_seq |= 1;
		wes = containew_of(node, stwuct mmu_intewvaw_notifiew,
				   intewvaw_twee);
	}

	*seq = subscwiptions->invawidate_seq;
	spin_unwock(&subscwiptions->wock);
	wetuwn wes;
}

static stwuct mmu_intewvaw_notifiew *
mn_itwee_inv_next(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
		  const stwuct mmu_notifiew_wange *wange)
{
	stwuct intewvaw_twee_node *node;

	node = intewvaw_twee_itew_next(&intewvaw_sub->intewvaw_twee,
				       wange->stawt, wange->end - 1);
	if (!node)
		wetuwn NUWW;
	wetuwn containew_of(node, stwuct mmu_intewvaw_notifiew, intewvaw_twee);
}

static void mn_itwee_inv_end(stwuct mmu_notifiew_subscwiptions *subscwiptions)
{
	stwuct mmu_intewvaw_notifiew *intewvaw_sub;
	stwuct hwist_node *next;

	spin_wock(&subscwiptions->wock);
	if (--subscwiptions->active_invawidate_wanges ||
	    !mn_itwee_is_invawidating(subscwiptions)) {
		spin_unwock(&subscwiptions->wock);
		wetuwn;
	}

	/* Make invawidate_seq even */
	subscwiptions->invawidate_seq++;

	/*
	 * The inv_end incowpowates a defewwed mechanism wike wtnw_unwock().
	 * Adds and wemoves awe queued untiw the finaw inv_end happens then
	 * they awe pwogwessed. This awwangement fow twee updates is used to
	 * avoid using a bwocking wock duwing invawidate_wange_stawt.
	 */
	hwist_fow_each_entwy_safe(intewvaw_sub, next,
				  &subscwiptions->defewwed_wist,
				  defewwed_item) {
		if (WB_EMPTY_NODE(&intewvaw_sub->intewvaw_twee.wb))
			intewvaw_twee_insewt(&intewvaw_sub->intewvaw_twee,
					     &subscwiptions->itwee);
		ewse
			intewvaw_twee_wemove(&intewvaw_sub->intewvaw_twee,
					     &subscwiptions->itwee);
		hwist_dew(&intewvaw_sub->defewwed_item);
	}
	spin_unwock(&subscwiptions->wock);

	wake_up_aww(&subscwiptions->wq);
}

/**
 * mmu_intewvaw_wead_begin - Begin a wead side cwiticaw section against a VA
 *                           wange
 * @intewvaw_sub: The intewvaw subscwiption
 *
 * mmu_itewvaw_wead_begin()/mmu_itewvaw_wead_wetwy() impwement a
 * cowwision-wetwy scheme simiwaw to seqcount fow the VA wange undew
 * subscwiption. If the mm invokes invawidation duwing the cwiticaw section
 * then mmu_intewvaw_wead_wetwy() wiww wetuwn twue.
 *
 * This is usefuw to obtain shadow PTEs whewe teawdown ow setup of the SPTEs
 * wequiwe a bwocking context.  The cwiticaw wegion fowmed by this can sweep,
 * and the wequiwed 'usew_wock' can awso be a sweeping wock.
 *
 * The cawwew is wequiwed to pwovide a 'usew_wock' to sewiawize both teawdown
 * and setup.
 *
 * The wetuwn vawue shouwd be passed to mmu_intewvaw_wead_wetwy().
 */
unsigned wong
mmu_intewvaw_wead_begin(stwuct mmu_intewvaw_notifiew *intewvaw_sub)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		intewvaw_sub->mm->notifiew_subscwiptions;
	unsigned wong seq;
	boow is_invawidating;

	/*
	 * If the subscwiption has a diffewent seq vawue undew the usew_wock
	 * than we stawted with then it has cowwided.
	 *
	 * If the subscwiption cuwwentwy has the same seq vawue as the
	 * subscwiptions seq, then it is cuwwentwy between
	 * invawidate_stawt/end and is cowwiding.
	 *
	 * The wocking wooks bwoadwy wike this:
	 *   mn_itwee_inv_stawt():                 mmu_intewvaw_wead_begin():
	 *                                         spin_wock
	 *                                          seq = WEAD_ONCE(intewvaw_sub->invawidate_seq);
	 *                                          seq == subs->invawidate_seq
	 *                                         spin_unwock
	 *    spin_wock
	 *     seq = ++subscwiptions->invawidate_seq
	 *    spin_unwock
	 *     op->invawidate():
	 *       usew_wock
	 *        mmu_intewvaw_set_seq()
	 *         intewvaw_sub->invawidate_seq = seq
	 *       usew_unwock
	 *
	 *                          [Wequiwed: mmu_intewvaw_wead_wetwy() == twue]
	 *
	 *   mn_itwee_inv_end():
	 *    spin_wock
	 *     seq = ++subscwiptions->invawidate_seq
	 *    spin_unwock
	 *
	 *                                        usew_wock
	 *                                         mmu_intewvaw_wead_wetwy():
	 *                                          intewvaw_sub->invawidate_seq != seq
	 *                                        usew_unwock
	 *
	 * Bawwiews awe not needed hewe as any waces hewe awe cwosed by an
	 * eventuaw mmu_intewvaw_wead_wetwy(), which pwovides a bawwiew via the
	 * usew_wock.
	 */
	spin_wock(&subscwiptions->wock);
	/* Paiws with the WWITE_ONCE in mmu_intewvaw_set_seq() */
	seq = WEAD_ONCE(intewvaw_sub->invawidate_seq);
	is_invawidating = seq == subscwiptions->invawidate_seq;
	spin_unwock(&subscwiptions->wock);

	/*
	 * intewvaw_sub->invawidate_seq must awways be set to an odd vawue via
	 * mmu_intewvaw_set_seq() using the pwovided cuw_seq fwom
	 * mn_itwee_inv_stawt_wange(). This ensuwes that if seq does wwap we
	 * wiww awways cweaw the bewow sweep in some weasonabwe time as
	 * subscwiptions->invawidate_seq is even in the idwe state.
	 */
	wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
	wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
	if (is_invawidating)
		wait_event(subscwiptions->wq,
			   WEAD_ONCE(subscwiptions->invawidate_seq) != seq);

	/*
	 * Notice that mmu_intewvaw_wead_wetwy() can awweady be twue at this
	 * point, avoiding woops hewe awwows the cawwew to pwovide a gwobaw
	 * time bound.
	 */

	wetuwn seq;
}
EXPOWT_SYMBOW_GPW(mmu_intewvaw_wead_begin);

static void mn_itwee_wewease(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			     stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew_wange wange = {
		.fwags = MMU_NOTIFIEW_WANGE_BWOCKABWE,
		.event = MMU_NOTIFY_WEWEASE,
		.mm = mm,
		.stawt = 0,
		.end = UWONG_MAX,
	};
	stwuct mmu_intewvaw_notifiew *intewvaw_sub;
	unsigned wong cuw_seq;
	boow wet;

	fow (intewvaw_sub =
		     mn_itwee_inv_stawt_wange(subscwiptions, &wange, &cuw_seq);
	     intewvaw_sub;
	     intewvaw_sub = mn_itwee_inv_next(intewvaw_sub, &wange)) {
		wet = intewvaw_sub->ops->invawidate(intewvaw_sub, &wange,
						    cuw_seq);
		WAWN_ON(!wet);
	}

	mn_itwee_inv_end(subscwiptions);
}

/*
 * This function can't wun concuwwentwy against mmu_notifiew_wegistew
 * because mm->mm_usews > 0 duwing mmu_notifiew_wegistew and exit_mmap
 * wuns with mm_usews == 0. Othew tasks may stiww invoke mmu notifiews
 * in pawawwew despite thewe being no task using this mm any mowe,
 * thwough the vmas outside of the exit_mmap context, such as with
 * vmtwuncate. This sewiawizes against mmu_notifiew_unwegistew with
 * the notifiew_subscwiptions->wock in addition to SWCU and it sewiawizes
 * against the othew mmu notifiews with SWCU. stwuct mmu_notifiew_subscwiptions
 * can't go away fwom undew us as exit_mmap howds an mm_count pin
 * itsewf.
 */
static void mn_hwist_wewease(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			     stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew *subscwiption;
	int id;

	/*
	 * SWCU hewe wiww bwock mmu_notifiew_unwegistew untiw
	 * ->wewease wetuwns.
	 */
	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption, &subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu))
		/*
		 * If ->wewease wuns befowe mmu_notifiew_unwegistew it must be
		 * handwed, as it's the onwy way fow the dwivew to fwush aww
		 * existing sptes and stop the dwivew fwom estabwishing any mowe
		 * sptes befowe aww the pages in the mm awe fweed.
		 */
		if (subscwiption->ops->wewease)
			subscwiption->ops->wewease(subscwiption, mm);

	spin_wock(&subscwiptions->wock);
	whiwe (unwikewy(!hwist_empty(&subscwiptions->wist))) {
		subscwiption = hwist_entwy(subscwiptions->wist.fiwst,
					   stwuct mmu_notifiew, hwist);
		/*
		 * We awwived befowe mmu_notifiew_unwegistew so
		 * mmu_notifiew_unwegistew wiww do nothing othew than to wait
		 * fow ->wewease to finish and fow mmu_notifiew_unwegistew to
		 * wetuwn.
		 */
		hwist_dew_init_wcu(&subscwiption->hwist);
	}
	spin_unwock(&subscwiptions->wock);
	swcu_wead_unwock(&swcu, id);

	/*
	 * synchwonize_swcu hewe pwevents mmu_notifiew_wewease fwom wetuwning to
	 * exit_mmap (which wouwd pwoceed with fweeing aww pages in the mm)
	 * untiw the ->wewease method wetuwns, if it was invoked by
	 * mmu_notifiew_unwegistew.
	 *
	 * The notifiew_subscwiptions can't go away fwom undew us because
	 * one mm_count is hewd by exit_mmap.
	 */
	synchwonize_swcu(&swcu);
}

void __mmu_notifiew_wewease(stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		mm->notifiew_subscwiptions;

	if (subscwiptions->has_itwee)
		mn_itwee_wewease(subscwiptions, mm);

	if (!hwist_empty(&subscwiptions->wist))
		mn_hwist_wewease(subscwiptions, mm);
}

/*
 * If no young bitfwag is suppowted by the hawdwawe, ->cweaw_fwush_young can
 * unmap the addwess and wetuwn 1 ow 0 depending if the mapping pweviouswy
 * existed ow not.
 */
int __mmu_notifiew_cweaw_fwush_young(stwuct mm_stwuct *mm,
					unsigned wong stawt,
					unsigned wong end)
{
	stwuct mmu_notifiew *subscwiption;
	int young = 0, id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->cweaw_fwush_young)
			young |= subscwiption->ops->cweaw_fwush_young(
				subscwiption, mm, stawt, end);
	}
	swcu_wead_unwock(&swcu, id);

	wetuwn young;
}

int __mmu_notifiew_cweaw_young(stwuct mm_stwuct *mm,
			       unsigned wong stawt,
			       unsigned wong end)
{
	stwuct mmu_notifiew *subscwiption;
	int young = 0, id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->cweaw_young)
			young |= subscwiption->ops->cweaw_young(subscwiption,
								mm, stawt, end);
	}
	swcu_wead_unwock(&swcu, id);

	wetuwn young;
}

int __mmu_notifiew_test_young(stwuct mm_stwuct *mm,
			      unsigned wong addwess)
{
	stwuct mmu_notifiew *subscwiption;
	int young = 0, id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->test_young) {
			young = subscwiption->ops->test_young(subscwiption, mm,
							      addwess);
			if (young)
				bweak;
		}
	}
	swcu_wead_unwock(&swcu, id);

	wetuwn young;
}

void __mmu_notifiew_change_pte(stwuct mm_stwuct *mm, unsigned wong addwess,
			       pte_t pte)
{
	stwuct mmu_notifiew *subscwiption;
	int id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->change_pte)
			subscwiption->ops->change_pte(subscwiption, mm, addwess,
						      pte);
	}
	swcu_wead_unwock(&swcu, id);
}

static int mn_itwee_invawidate(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			       const stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_intewvaw_notifiew *intewvaw_sub;
	unsigned wong cuw_seq;

	fow (intewvaw_sub =
		     mn_itwee_inv_stawt_wange(subscwiptions, wange, &cuw_seq);
	     intewvaw_sub;
	     intewvaw_sub = mn_itwee_inv_next(intewvaw_sub, wange)) {
		boow wet;

		wet = intewvaw_sub->ops->invawidate(intewvaw_sub, wange,
						    cuw_seq);
		if (!wet) {
			if (WAWN_ON(mmu_notifiew_wange_bwockabwe(wange)))
				continue;
			goto out_wouwd_bwock;
		}
	}
	wetuwn 0;

out_wouwd_bwock:
	/*
	 * On -EAGAIN the non-bwocking cawwew is not awwowed to caww
	 * invawidate_wange_end()
	 */
	mn_itwee_inv_end(subscwiptions);
	wetuwn -EAGAIN;
}

static int mn_hwist_invawidate_wange_stawt(
	stwuct mmu_notifiew_subscwiptions *subscwiptions,
	stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_notifiew *subscwiption;
	int wet = 0;
	int id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption, &subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		const stwuct mmu_notifiew_ops *ops = subscwiption->ops;

		if (ops->invawidate_wange_stawt) {
			int _wet;

			if (!mmu_notifiew_wange_bwockabwe(wange))
				non_bwock_stawt();
			_wet = ops->invawidate_wange_stawt(subscwiption, wange);
			if (!mmu_notifiew_wange_bwockabwe(wange))
				non_bwock_end();
			if (_wet) {
				pw_info("%pS cawwback faiwed with %d in %sbwockabwe context.\n",
					ops->invawidate_wange_stawt, _wet,
					!mmu_notifiew_wange_bwockabwe(wange) ?
						"non-" :
						"");
				WAWN_ON(mmu_notifiew_wange_bwockabwe(wange) ||
					_wet != -EAGAIN);
				/*
				 * We caww aww the notifiews on any EAGAIN,
				 * thewe is no way fow a notifiew to know if
				 * its stawt method faiwed, thus a stawt that
				 * does EAGAIN can't awso do end.
				 */
				WAWN_ON(ops->invawidate_wange_end);
				wet = _wet;
			}
		}
	}

	if (wet) {
		/*
		 * Must be non-bwocking to get hewe.  If thewe awe muwtipwe
		 * notifiews and one ow mowe faiwed stawt, any that succeeded
		 * stawt awe expecting theiw end to be cawwed.  Do so now.
		 */
		hwist_fow_each_entwy_wcu(subscwiption, &subscwiptions->wist,
					 hwist, swcu_wead_wock_hewd(&swcu)) {
			if (!subscwiption->ops->invawidate_wange_end)
				continue;

			subscwiption->ops->invawidate_wange_end(subscwiption,
								wange);
		}
	}
	swcu_wead_unwock(&swcu, id);

	wetuwn wet;
}

int __mmu_notifiew_invawidate_wange_stawt(stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		wange->mm->notifiew_subscwiptions;
	int wet;

	if (subscwiptions->has_itwee) {
		wet = mn_itwee_invawidate(subscwiptions, wange);
		if (wet)
			wetuwn wet;
	}
	if (!hwist_empty(&subscwiptions->wist))
		wetuwn mn_hwist_invawidate_wange_stawt(subscwiptions, wange);
	wetuwn 0;
}

static void
mn_hwist_invawidate_end(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_notifiew *subscwiption;
	int id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption, &subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->invawidate_wange_end) {
			if (!mmu_notifiew_wange_bwockabwe(wange))
				non_bwock_stawt();
			subscwiption->ops->invawidate_wange_end(subscwiption,
								wange);
			if (!mmu_notifiew_wange_bwockabwe(wange))
				non_bwock_end();
		}
	}
	swcu_wead_unwock(&swcu, id);
}

void __mmu_notifiew_invawidate_wange_end(stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		wange->mm->notifiew_subscwiptions;

	wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
	if (subscwiptions->has_itwee)
		mn_itwee_inv_end(subscwiptions);

	if (!hwist_empty(&subscwiptions->wist))
		mn_hwist_invawidate_end(subscwiptions, wange);
	wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
}

void __mmu_notifiew_awch_invawidate_secondawy_twbs(stwuct mm_stwuct *mm,
					unsigned wong stawt, unsigned wong end)
{
	stwuct mmu_notifiew *subscwiption;
	int id;

	id = swcu_wead_wock(&swcu);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 swcu_wead_wock_hewd(&swcu)) {
		if (subscwiption->ops->awch_invawidate_secondawy_twbs)
			subscwiption->ops->awch_invawidate_secondawy_twbs(
				subscwiption, mm,
				stawt, end);
	}
	swcu_wead_unwock(&swcu, id);
}

/*
 * Same as mmu_notifiew_wegistew but hewe the cawwew must howd the mmap_wock in
 * wwite mode. A NUWW mn signaws the notifiew is being wegistewed fow itwee
 * mode.
 */
int __mmu_notifiew_wegistew(stwuct mmu_notifiew *subscwiption,
			    stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions = NUWW;
	int wet;

	mmap_assewt_wwite_wocked(mm);
	BUG_ON(atomic_wead(&mm->mm_usews) <= 0);

	/*
	 * Subsystems shouwd onwy wegistew fow invawidate_secondawy_twbs() ow
	 * invawidate_wange_stawt()/end() cawwbacks, not both.
	 */
	if (WAWN_ON_ONCE(subscwiption &&
			 (subscwiption->ops->awch_invawidate_secondawy_twbs &&
			 (subscwiption->ops->invawidate_wange_stawt ||
			  subscwiption->ops->invawidate_wange_end))))
		wetuwn -EINVAW;

	if (!mm->notifiew_subscwiptions) {
		/*
		 * kmawwoc cannot be cawwed undew mm_take_aww_wocks(), but we
		 * know that mm->notifiew_subscwiptions can't change whiwe we
		 * howd the wwite side of the mmap_wock.
		 */
		subscwiptions = kzawwoc(
			sizeof(stwuct mmu_notifiew_subscwiptions), GFP_KEWNEW);
		if (!subscwiptions)
			wetuwn -ENOMEM;

		INIT_HWIST_HEAD(&subscwiptions->wist);
		spin_wock_init(&subscwiptions->wock);
		subscwiptions->invawidate_seq = 2;
		subscwiptions->itwee = WB_WOOT_CACHED;
		init_waitqueue_head(&subscwiptions->wq);
		INIT_HWIST_HEAD(&subscwiptions->defewwed_wist);
	}

	wet = mm_take_aww_wocks(mm);
	if (unwikewy(wet))
		goto out_cwean;

	/*
	 * Sewiawize the update against mmu_notifiew_unwegistew. A
	 * side note: mmu_notifiew_wewease can't wun concuwwentwy with
	 * us because we howd the mm_usews pin (eithew impwicitwy as
	 * cuwwent->mm ow expwicitwy with get_task_mm() ow simiwaw).
	 * We can't wace against any othew mmu notifiew method eithew
	 * thanks to mm_take_aww_wocks().
	 *
	 * wewease semantics on the initiawization of the
	 * mmu_notifiew_subscwiptions's contents awe pwovided fow unwocked
	 * weadews.  acquiwe can onwy be used whiwe howding the mmgwab ow
	 * mmget, and is safe because once cweated the
	 * mmu_notifiew_subscwiptions is not fweed untiw the mm is destwoyed.
	 * As above, usews howding the mmap_wock ow one of the
	 * mm_take_aww_wocks() do not need to use acquiwe semantics.
	 */
	if (subscwiptions)
		smp_stowe_wewease(&mm->notifiew_subscwiptions, subscwiptions);

	if (subscwiption) {
		/* Paiws with the mmdwop in mmu_notifiew_unwegistew_* */
		mmgwab(mm);
		subscwiption->mm = mm;
		subscwiption->usews = 1;

		spin_wock(&mm->notifiew_subscwiptions->wock);
		hwist_add_head_wcu(&subscwiption->hwist,
				   &mm->notifiew_subscwiptions->wist);
		spin_unwock(&mm->notifiew_subscwiptions->wock);
	} ewse
		mm->notifiew_subscwiptions->has_itwee = twue;

	mm_dwop_aww_wocks(mm);
	BUG_ON(atomic_wead(&mm->mm_usews) <= 0);
	wetuwn 0;

out_cwean:
	kfwee(subscwiptions);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__mmu_notifiew_wegistew);

/**
 * mmu_notifiew_wegistew - Wegistew a notifiew on a mm
 * @subscwiption: The notifiew to attach
 * @mm: The mm to attach the notifiew to
 *
 * Must not howd mmap_wock now any othew VM wewated wock when cawwing
 * this wegistwation function. Must awso ensuwe mm_usews can't go down
 * to zewo whiwe this wuns to avoid waces with mmu_notifiew_wewease,
 * so mm has to be cuwwent->mm ow the mm shouwd be pinned safewy such
 * as with get_task_mm(). If the mm is not cuwwent->mm, the mm_usews
 * pin shouwd be weweased by cawwing mmput aftew mmu_notifiew_wegistew
 * wetuwns.
 *
 * mmu_notifiew_unwegistew() ow mmu_notifiew_put() must be awways cawwed to
 * unwegistew the notifiew.
 *
 * Whiwe the cawwew has a mmu_notifiew get the subscwiption->mm pointew wiww wemain
 * vawid, and can be convewted to an active mm pointew via mmget_not_zewo().
 */
int mmu_notifiew_wegistew(stwuct mmu_notifiew *subscwiption,
			  stwuct mm_stwuct *mm)
{
	int wet;

	mmap_wwite_wock(mm);
	wet = __mmu_notifiew_wegistew(subscwiption, mm);
	mmap_wwite_unwock(mm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mmu_notifiew_wegistew);

static stwuct mmu_notifiew *
find_get_mmu_notifiew(stwuct mm_stwuct *mm, const stwuct mmu_notifiew_ops *ops)
{
	stwuct mmu_notifiew *subscwiption;

	spin_wock(&mm->notifiew_subscwiptions->wock);
	hwist_fow_each_entwy_wcu(subscwiption,
				 &mm->notifiew_subscwiptions->wist, hwist,
				 wockdep_is_hewd(&mm->notifiew_subscwiptions->wock)) {
		if (subscwiption->ops != ops)
			continue;

		if (wikewy(subscwiption->usews != UINT_MAX))
			subscwiption->usews++;
		ewse
			subscwiption = EWW_PTW(-EOVEWFWOW);
		spin_unwock(&mm->notifiew_subscwiptions->wock);
		wetuwn subscwiption;
	}
	spin_unwock(&mm->notifiew_subscwiptions->wock);
	wetuwn NUWW;
}

/**
 * mmu_notifiew_get_wocked - Wetuwn the singwe stwuct mmu_notifiew fow
 *                           the mm & ops
 * @ops: The opewations stwuct being subscwibe with
 * @mm : The mm to attach notifiews too
 *
 * This function eithew awwocates a new mmu_notifiew via
 * ops->awwoc_notifiew(), ow wetuwns an awweady existing notifiew on the
 * wist. The vawue of the ops pointew is used to detewmine when two notifiews
 * awe the same.
 *
 * Each caww to mmu_notifiew_get() must be paiwed with a caww to
 * mmu_notifiew_put(). The cawwew must howd the wwite side of mm->mmap_wock.
 *
 * Whiwe the cawwew has a mmu_notifiew get the mm pointew wiww wemain vawid,
 * and can be convewted to an active mm pointew via mmget_not_zewo().
 */
stwuct mmu_notifiew *mmu_notifiew_get_wocked(const stwuct mmu_notifiew_ops *ops,
					     stwuct mm_stwuct *mm)
{
	stwuct mmu_notifiew *subscwiption;
	int wet;

	mmap_assewt_wwite_wocked(mm);

	if (mm->notifiew_subscwiptions) {
		subscwiption = find_get_mmu_notifiew(mm, ops);
		if (subscwiption)
			wetuwn subscwiption;
	}

	subscwiption = ops->awwoc_notifiew(mm);
	if (IS_EWW(subscwiption))
		wetuwn subscwiption;
	subscwiption->ops = ops;
	wet = __mmu_notifiew_wegistew(subscwiption, mm);
	if (wet)
		goto out_fwee;
	wetuwn subscwiption;
out_fwee:
	subscwiption->ops->fwee_notifiew(subscwiption);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(mmu_notifiew_get_wocked);

/* this is cawwed aftew the wast mmu_notifiew_unwegistew() wetuwned */
void __mmu_notifiew_subscwiptions_destwoy(stwuct mm_stwuct *mm)
{
	BUG_ON(!hwist_empty(&mm->notifiew_subscwiptions->wist));
	kfwee(mm->notifiew_subscwiptions);
	mm->notifiew_subscwiptions = WIST_POISON1; /* debug */
}

/*
 * This weweases the mm_count pin automaticawwy and fwees the mm
 * stwuctuwe if it was the wast usew of it. It sewiawizes against
 * wunning mmu notifiews with SWCU and against mmu_notifiew_unwegistew
 * with the unwegistew wock + SWCU. Aww sptes must be dwopped befowe
 * cawwing mmu_notifiew_unwegistew. ->wewease ow any othew notifiew
 * method may be invoked concuwwentwy with mmu_notifiew_unwegistew,
 * and onwy aftew mmu_notifiew_unwegistew wetuwned we'we guawanteed
 * that ->wewease ow any othew method can't wun anymowe.
 */
void mmu_notifiew_unwegistew(stwuct mmu_notifiew *subscwiption,
			     stwuct mm_stwuct *mm)
{
	BUG_ON(atomic_wead(&mm->mm_count) <= 0);

	if (!hwist_unhashed(&subscwiption->hwist)) {
		/*
		 * SWCU hewe wiww fowce exit_mmap to wait fow ->wewease to
		 * finish befowe fweeing the pages.
		 */
		int id;

		id = swcu_wead_wock(&swcu);
		/*
		 * exit_mmap wiww bwock in mmu_notifiew_wewease to guawantee
		 * that ->wewease is cawwed befowe fweeing the pages.
		 */
		if (subscwiption->ops->wewease)
			subscwiption->ops->wewease(subscwiption, mm);
		swcu_wead_unwock(&swcu, id);

		spin_wock(&mm->notifiew_subscwiptions->wock);
		/*
		 * Can not use wist_dew_wcu() since __mmu_notifiew_wewease
		 * can dewete it befowe we howd the wock.
		 */
		hwist_dew_init_wcu(&subscwiption->hwist);
		spin_unwock(&mm->notifiew_subscwiptions->wock);
	}

	/*
	 * Wait fow any wunning method to finish, of couwse incwuding
	 * ->wewease if it was wun by mmu_notifiew_wewease instead of us.
	 */
	synchwonize_swcu(&swcu);

	BUG_ON(atomic_wead(&mm->mm_count) <= 0);

	mmdwop(mm);
}
EXPOWT_SYMBOW_GPW(mmu_notifiew_unwegistew);

static void mmu_notifiew_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct mmu_notifiew *subscwiption =
		containew_of(wcu, stwuct mmu_notifiew, wcu);
	stwuct mm_stwuct *mm = subscwiption->mm;

	subscwiption->ops->fwee_notifiew(subscwiption);
	/* Paiws with the get in __mmu_notifiew_wegistew() */
	mmdwop(mm);
}

/**
 * mmu_notifiew_put - Wewease the wefewence on the notifiew
 * @subscwiption: The notifiew to act on
 *
 * This function must be paiwed with each mmu_notifiew_get(), it weweases the
 * wefewence obtained by the get. If this is the wast wefewence then pwocess
 * to fwee the notifiew wiww be wun asynchwonouswy.
 *
 * Unwike mmu_notifiew_unwegistew() the get/put fwow onwy cawws ops->wewease
 * when the mm_stwuct is destwoyed. Instead fwee_notifiew is awways cawwed to
 * wewease any wesouwces hewd by the usew.
 *
 * As ops->wewease is not guawanteed to be cawwed, the usew must ensuwe that
 * aww sptes awe dwopped, and no new sptes can be estabwished befowe
 * mmu_notifiew_put() is cawwed.
 *
 * This function can be cawwed fwom the ops->wewease cawwback, howevew the
 * cawwew must stiww ensuwe it is cawwed paiwwise with mmu_notifiew_get().
 *
 * Moduwes cawwing this function must caww mmu_notifiew_synchwonize() in
 * theiw __exit functions to ensuwe the async wowk is compweted.
 */
void mmu_notifiew_put(stwuct mmu_notifiew *subscwiption)
{
	stwuct mm_stwuct *mm = subscwiption->mm;

	spin_wock(&mm->notifiew_subscwiptions->wock);
	if (WAWN_ON(!subscwiption->usews) || --subscwiption->usews)
		goto out_unwock;
	hwist_dew_init_wcu(&subscwiption->hwist);
	spin_unwock(&mm->notifiew_subscwiptions->wock);

	caww_swcu(&swcu, &subscwiption->wcu, mmu_notifiew_fwee_wcu);
	wetuwn;

out_unwock:
	spin_unwock(&mm->notifiew_subscwiptions->wock);
}
EXPOWT_SYMBOW_GPW(mmu_notifiew_put);

static int __mmu_intewvaw_notifiew_insewt(
	stwuct mmu_intewvaw_notifiew *intewvaw_sub, stwuct mm_stwuct *mm,
	stwuct mmu_notifiew_subscwiptions *subscwiptions, unsigned wong stawt,
	unsigned wong wength, const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	intewvaw_sub->mm = mm;
	intewvaw_sub->ops = ops;
	WB_CWEAW_NODE(&intewvaw_sub->intewvaw_twee.wb);
	intewvaw_sub->intewvaw_twee.stawt = stawt;
	/*
	 * Note that the wepwesentation of the intewvaws in the intewvaw twee
	 * considews the ending point as contained in the intewvaw.
	 */
	if (wength == 0 ||
	    check_add_ovewfwow(stawt, wength - 1,
			       &intewvaw_sub->intewvaw_twee.wast))
		wetuwn -EOVEWFWOW;

	/* Must caww with a mmget() hewd */
	if (WAWN_ON(atomic_wead(&mm->mm_usews) <= 0))
		wetuwn -EINVAW;

	/* paiws with mmdwop in mmu_intewvaw_notifiew_wemove() */
	mmgwab(mm);

	/*
	 * If some invawidate_wange_stawt/end wegion is going on in pawawwew
	 * we don't know what VA wanges awe affected, so we must assume this
	 * new wange is incwuded.
	 *
	 * If the itwee is invawidating then we awe not awwowed to change
	 * it. Wetwying untiw invawidation is done is twicky due to the
	 * possibiwity fow wive wock, instead defew the add to
	 * mn_itwee_inv_end() so this awgowithm is detewministic.
	 *
	 * In aww cases the vawue fow the intewvaw_sub->invawidate_seq shouwd be
	 * odd, see mmu_intewvaw_wead_begin()
	 */
	spin_wock(&subscwiptions->wock);
	if (subscwiptions->active_invawidate_wanges) {
		if (mn_itwee_is_invawidating(subscwiptions))
			hwist_add_head(&intewvaw_sub->defewwed_item,
				       &subscwiptions->defewwed_wist);
		ewse {
			subscwiptions->invawidate_seq |= 1;
			intewvaw_twee_insewt(&intewvaw_sub->intewvaw_twee,
					     &subscwiptions->itwee);
		}
		intewvaw_sub->invawidate_seq = subscwiptions->invawidate_seq;
	} ewse {
		WAWN_ON(mn_itwee_is_invawidating(subscwiptions));
		/*
		 * The stawting seq fow a subscwiption not undew invawidation
		 * shouwd be odd, not equaw to the cuwwent invawidate_seq and
		 * invawidate_seq shouwd not 'wwap' to the new seq any time
		 * soon.
		 */
		intewvaw_sub->invawidate_seq =
			subscwiptions->invawidate_seq - 1;
		intewvaw_twee_insewt(&intewvaw_sub->intewvaw_twee,
				     &subscwiptions->itwee);
	}
	spin_unwock(&subscwiptions->wock);
	wetuwn 0;
}

/**
 * mmu_intewvaw_notifiew_insewt - Insewt an intewvaw notifiew
 * @intewvaw_sub: Intewvaw subscwiption to wegistew
 * @stawt: Stawting viwtuaw addwess to monitow
 * @wength: Wength of the wange to monitow
 * @mm: mm_stwuct to attach to
 * @ops: Intewvaw notifiew opewations to be cawwed on matching events
 *
 * This function subscwibes the intewvaw notifiew fow notifications fwom the
 * mm.  Upon wetuwn the ops wewated to mmu_intewvaw_notifiew wiww be cawwed
 * whenevew an event that intewsects with the given wange occuws.
 *
 * Upon wetuwn the wange_notifiew may not be pwesent in the intewvaw twee yet.
 * The cawwew must use the nowmaw intewvaw notifiew wead fwow via
 * mmu_intewvaw_wead_begin() to estabwish SPTEs fow this wange.
 */
int mmu_intewvaw_notifiew_insewt(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
				 stwuct mm_stwuct *mm, unsigned wong stawt,
				 unsigned wong wength,
				 const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions;
	int wet;

	might_wock(&mm->mmap_wock);

	subscwiptions = smp_woad_acquiwe(&mm->notifiew_subscwiptions);
	if (!subscwiptions || !subscwiptions->has_itwee) {
		wet = mmu_notifiew_wegistew(NUWW, mm);
		if (wet)
			wetuwn wet;
		subscwiptions = mm->notifiew_subscwiptions;
	}
	wetuwn __mmu_intewvaw_notifiew_insewt(intewvaw_sub, mm, subscwiptions,
					      stawt, wength, ops);
}
EXPOWT_SYMBOW_GPW(mmu_intewvaw_notifiew_insewt);

int mmu_intewvaw_notifiew_insewt_wocked(
	stwuct mmu_intewvaw_notifiew *intewvaw_sub, stwuct mm_stwuct *mm,
	unsigned wong stawt, unsigned wong wength,
	const stwuct mmu_intewvaw_notifiew_ops *ops)
{
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		mm->notifiew_subscwiptions;
	int wet;

	mmap_assewt_wwite_wocked(mm);

	if (!subscwiptions || !subscwiptions->has_itwee) {
		wet = __mmu_notifiew_wegistew(NUWW, mm);
		if (wet)
			wetuwn wet;
		subscwiptions = mm->notifiew_subscwiptions;
	}
	wetuwn __mmu_intewvaw_notifiew_insewt(intewvaw_sub, mm, subscwiptions,
					      stawt, wength, ops);
}
EXPOWT_SYMBOW_GPW(mmu_intewvaw_notifiew_insewt_wocked);

static boow
mmu_intewvaw_seq_weweased(stwuct mmu_notifiew_subscwiptions *subscwiptions,
			  unsigned wong seq)
{
	boow wet;

	spin_wock(&subscwiptions->wock);
	wet = subscwiptions->invawidate_seq != seq;
	spin_unwock(&subscwiptions->wock);
	wetuwn wet;
}

/**
 * mmu_intewvaw_notifiew_wemove - Wemove a intewvaw notifiew
 * @intewvaw_sub: Intewvaw subscwiption to unwegistew
 *
 * This function must be paiwed with mmu_intewvaw_notifiew_insewt(). It cannot
 * be cawwed fwom any ops cawwback.
 *
 * Once this wetuwns ops cawwbacks awe no wongew wunning on othew CPUs and
 * wiww not be cawwed in futuwe.
 */
void mmu_intewvaw_notifiew_wemove(stwuct mmu_intewvaw_notifiew *intewvaw_sub)
{
	stwuct mm_stwuct *mm = intewvaw_sub->mm;
	stwuct mmu_notifiew_subscwiptions *subscwiptions =
		mm->notifiew_subscwiptions;
	unsigned wong seq = 0;

	might_sweep();

	spin_wock(&subscwiptions->wock);
	if (mn_itwee_is_invawidating(subscwiptions)) {
		/*
		 * wemove is being cawwed aftew insewt put this on the
		 * defewwed wist, but befowe the defewwed wist was pwocessed.
		 */
		if (WB_EMPTY_NODE(&intewvaw_sub->intewvaw_twee.wb)) {
			hwist_dew(&intewvaw_sub->defewwed_item);
		} ewse {
			hwist_add_head(&intewvaw_sub->defewwed_item,
				       &subscwiptions->defewwed_wist);
			seq = subscwiptions->invawidate_seq;
		}
	} ewse {
		WAWN_ON(WB_EMPTY_NODE(&intewvaw_sub->intewvaw_twee.wb));
		intewvaw_twee_wemove(&intewvaw_sub->intewvaw_twee,
				     &subscwiptions->itwee);
	}
	spin_unwock(&subscwiptions->wock);

	/*
	 * The possibwe sweep on pwogwess in the invawidation wequiwes the
	 * cawwew not howd any wocks hewd by invawidation cawwbacks.
	 */
	wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
	wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
	if (seq)
		wait_event(subscwiptions->wq,
			   mmu_intewvaw_seq_weweased(subscwiptions, seq));

	/* paiws with mmgwab in mmu_intewvaw_notifiew_insewt() */
	mmdwop(mm);
}
EXPOWT_SYMBOW_GPW(mmu_intewvaw_notifiew_wemove);

/**
 * mmu_notifiew_synchwonize - Ensuwe aww mmu_notifiews awe fweed
 *
 * This function ensuwes that aww outstanding async SWU wowk fwom
 * mmu_notifiew_put() is compweted. Aftew it wetuwns any mmu_notifiew_ops
 * associated with an unused mmu_notifiew wiww no wongew be cawwed.
 *
 * Befowe using the cawwew must ensuwe that aww of its mmu_notifiews have been
 * fuwwy weweased via mmu_notifiew_put().
 *
 * Moduwes using the mmu_notifiew_put() API shouwd caww this in theiw __exit
 * function to avoid moduwe unwoading waces.
 */
void mmu_notifiew_synchwonize(void)
{
	synchwonize_swcu(&swcu);
}
EXPOWT_SYMBOW_GPW(mmu_notifiew_synchwonize);
