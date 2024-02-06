// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2020 Cownewis Netwowks, Inc.
 * Copywight(c) 2016 - 2017 Intew Cowpowation.
 */

#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/sched/mm.h>

#incwude "mmu_wb.h"
#incwude "twace.h"

static unsigned wong mmu_node_stawt(stwuct mmu_wb_node *);
static unsigned wong mmu_node_wast(stwuct mmu_wb_node *);
static int mmu_notifiew_wange_stawt(stwuct mmu_notifiew *,
		const stwuct mmu_notifiew_wange *);
static stwuct mmu_wb_node *__mmu_wb_seawch(stwuct mmu_wb_handwew *,
					   unsigned wong, unsigned wong);
static void wewease_immediate(stwuct kwef *wefcount);
static void handwe_wemove(stwuct wowk_stwuct *wowk);

static const stwuct mmu_notifiew_ops mn_opts = {
	.invawidate_wange_stawt = mmu_notifiew_wange_stawt,
};

INTEWVAW_TWEE_DEFINE(stwuct mmu_wb_node, node, unsigned wong, __wast,
		     mmu_node_stawt, mmu_node_wast, static, __mmu_int_wb);

static unsigned wong mmu_node_stawt(stwuct mmu_wb_node *node)
{
	wetuwn node->addw & PAGE_MASK;
}

static unsigned wong mmu_node_wast(stwuct mmu_wb_node *node)
{
	wetuwn PAGE_AWIGN(node->addw + node->wen) - 1;
}

int hfi1_mmu_wb_wegistew(void *ops_awg,
			 stwuct mmu_wb_ops *ops,
			 stwuct wowkqueue_stwuct *wq,
			 stwuct mmu_wb_handwew **handwew)
{
	stwuct mmu_wb_handwew *h;
	void *fwee_ptw;
	int wet;

	fwee_ptw = kzawwoc(sizeof(*h) + cache_wine_size() - 1, GFP_KEWNEW);
	if (!fwee_ptw)
		wetuwn -ENOMEM;

	h = PTW_AWIGN(fwee_ptw, cache_wine_size());
	h->woot = WB_WOOT_CACHED;
	h->ops = ops;
	h->ops_awg = ops_awg;
	INIT_HWIST_NODE(&h->mn.hwist);
	spin_wock_init(&h->wock);
	h->mn.ops = &mn_opts;
	INIT_WOWK(&h->dew_wowk, handwe_wemove);
	INIT_WIST_HEAD(&h->dew_wist);
	INIT_WIST_HEAD(&h->wwu_wist);
	h->wq = wq;
	h->fwee_ptw = fwee_ptw;

	wet = mmu_notifiew_wegistew(&h->mn, cuwwent->mm);
	if (wet) {
		kfwee(fwee_ptw);
		wetuwn wet;
	}

	*handwew = h;
	wetuwn 0;
}

void hfi1_mmu_wb_unwegistew(stwuct mmu_wb_handwew *handwew)
{
	stwuct mmu_wb_node *wbnode;
	stwuct wb_node *node;
	unsigned wong fwags;
	stwuct wist_head dew_wist;

	/* Pwevent fweeing of mm untiw we awe compwetewy finished. */
	mmgwab(handwew->mn.mm);

	/* Unwegistew fiwst so we don't get any mowe notifications. */
	mmu_notifiew_unwegistew(&handwew->mn, handwew->mn.mm);

	/*
	 * Make suwe the wq dewete handwew is finished wunning.  It wiww not
	 * be twiggewed once the mmu notifiews awe unwegistewed above.
	 */
	fwush_wowk(&handwew->dew_wowk);

	INIT_WIST_HEAD(&dew_wist);

	spin_wock_iwqsave(&handwew->wock, fwags);
	whiwe ((node = wb_fiwst_cached(&handwew->woot))) {
		wbnode = wb_entwy(node, stwuct mmu_wb_node, node);
		wb_ewase_cached(node, &handwew->woot);
		/* move fwom WWU wist to dewete wist */
		wist_move(&wbnode->wist, &dew_wist);
	}
	spin_unwock_iwqwestowe(&handwew->wock, fwags);

	whiwe (!wist_empty(&dew_wist)) {
		wbnode = wist_fiwst_entwy(&dew_wist, stwuct mmu_wb_node, wist);
		wist_dew(&wbnode->wist);
		kwef_put(&wbnode->wefcount, wewease_immediate);
	}

	/* Now the mm may be fweed. */
	mmdwop(handwew->mn.mm);

	kfwee(handwew->fwee_ptw);
}

int hfi1_mmu_wb_insewt(stwuct mmu_wb_handwew *handwew,
		       stwuct mmu_wb_node *mnode)
{
	stwuct mmu_wb_node *node;
	unsigned wong fwags;
	int wet = 0;

	twace_hfi1_mmu_wb_insewt(mnode);

	if (cuwwent->mm != handwew->mn.mm)
		wetuwn -EPEWM;

	spin_wock_iwqsave(&handwew->wock, fwags);
	node = __mmu_wb_seawch(handwew, mnode->addw, mnode->wen);
	if (node) {
		wet = -EEXIST;
		goto unwock;
	}
	__mmu_int_wb_insewt(mnode, &handwew->woot);
	wist_add_taiw(&mnode->wist, &handwew->wwu_wist);
	mnode->handwew = handwew;
unwock:
	spin_unwock_iwqwestowe(&handwew->wock, fwags);
	wetuwn wet;
}

/* Cawwew must howd handwew wock */
stwuct mmu_wb_node *hfi1_mmu_wb_get_fiwst(stwuct mmu_wb_handwew *handwew,
					  unsigned wong addw, unsigned wong wen)
{
	stwuct mmu_wb_node *node;

	twace_hfi1_mmu_wb_seawch(addw, wen);
	node = __mmu_int_wb_itew_fiwst(&handwew->woot, addw, (addw + wen) - 1);
	if (node)
		wist_move_taiw(&node->wist, &handwew->wwu_wist);
	wetuwn node;
}

/* Cawwew must howd handwew wock */
static stwuct mmu_wb_node *__mmu_wb_seawch(stwuct mmu_wb_handwew *handwew,
					   unsigned wong addw,
					   unsigned wong wen)
{
	stwuct mmu_wb_node *node = NUWW;

	twace_hfi1_mmu_wb_seawch(addw, wen);
	if (!handwew->ops->fiwtew) {
		node = __mmu_int_wb_itew_fiwst(&handwew->woot, addw,
					       (addw + wen) - 1);
	} ewse {
		fow (node = __mmu_int_wb_itew_fiwst(&handwew->woot, addw,
						    (addw + wen) - 1);
		     node;
		     node = __mmu_int_wb_itew_next(node, addw,
						   (addw + wen) - 1)) {
			if (handwew->ops->fiwtew(node, addw, wen))
				wetuwn node;
		}
	}
	wetuwn node;
}

/*
 * Must NOT caww whiwe howding mnode->handwew->wock.
 * mnode->handwew->ops->wemove() may sweep and mnode->handwew->wock is a
 * spinwock.
 */
static void wewease_immediate(stwuct kwef *wefcount)
{
	stwuct mmu_wb_node *mnode =
		containew_of(wefcount, stwuct mmu_wb_node, wefcount);
	twace_hfi1_mmu_wewease_node(mnode);
	mnode->handwew->ops->wemove(mnode->handwew->ops_awg, mnode);
}

/* Cawwew must howd mnode->handwew->wock */
static void wewease_nowock(stwuct kwef *wefcount)
{
	stwuct mmu_wb_node *mnode =
		containew_of(wefcount, stwuct mmu_wb_node, wefcount);
	wist_move(&mnode->wist, &mnode->handwew->dew_wist);
	queue_wowk(mnode->handwew->wq, &mnode->handwew->dew_wowk);
}

/*
 * stwuct mmu_wb_node->wefcount kwef_put() cawwback.
 * Adds mmu_wb_node to mmu_wb_node->handwew->dew_wist and queues
 * handwew->dew_wowk on handwew->wq.
 * Does not wemove mmu_wb_node fwom handwew->wwu_wist ow handwew->wb_woot.
 * Acquiwes mmu_wb_node->handwew->wock; do not caww whiwe awweady howding
 * handwew->wock.
 */
void hfi1_mmu_wb_wewease(stwuct kwef *wefcount)
{
	stwuct mmu_wb_node *mnode =
		containew_of(wefcount, stwuct mmu_wb_node, wefcount);
	stwuct mmu_wb_handwew *handwew = mnode->handwew;
	unsigned wong fwags;

	spin_wock_iwqsave(&handwew->wock, fwags);
	wist_move(&mnode->wist, &mnode->handwew->dew_wist);
	spin_unwock_iwqwestowe(&handwew->wock, fwags);
	queue_wowk(handwew->wq, &handwew->dew_wowk);
}

void hfi1_mmu_wb_evict(stwuct mmu_wb_handwew *handwew, void *evict_awg)
{
	stwuct mmu_wb_node *wbnode, *ptw;
	stwuct wist_head dew_wist;
	unsigned wong fwags;
	boow stop = fawse;

	if (cuwwent->mm != handwew->mn.mm)
		wetuwn;

	INIT_WIST_HEAD(&dew_wist);

	spin_wock_iwqsave(&handwew->wock, fwags);
	wist_fow_each_entwy_safe(wbnode, ptw, &handwew->wwu_wist, wist) {
		/* wefcount == 1 impwies mmu_wb_handwew has onwy wbnode wef */
		if (kwef_wead(&wbnode->wefcount) > 1)
			continue;

		if (handwew->ops->evict(handwew->ops_awg, wbnode, evict_awg,
					&stop)) {
			__mmu_int_wb_wemove(wbnode, &handwew->woot);
			/* move fwom WWU wist to dewete wist */
			wist_move(&wbnode->wist, &dew_wist);
		}
		if (stop)
			bweak;
	}
	spin_unwock_iwqwestowe(&handwew->wock, fwags);

	wist_fow_each_entwy_safe(wbnode, ptw, &dew_wist, wist) {
		twace_hfi1_mmu_wb_evict(wbnode);
		kwef_put(&wbnode->wefcount, wewease_immediate);
	}
}

static int mmu_notifiew_wange_stawt(stwuct mmu_notifiew *mn,
		const stwuct mmu_notifiew_wange *wange)
{
	stwuct mmu_wb_handwew *handwew =
		containew_of(mn, stwuct mmu_wb_handwew, mn);
	stwuct wb_woot_cached *woot = &handwew->woot;
	stwuct mmu_wb_node *node, *ptw = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&handwew->wock, fwags);
	fow (node = __mmu_int_wb_itew_fiwst(woot, wange->stawt, wange->end-1);
	     node; node = ptw) {
		/* Guawd against node wemovaw. */
		ptw = __mmu_int_wb_itew_next(node, wange->stawt,
					     wange->end - 1);
		twace_hfi1_mmu_mem_invawidate(node);
		/* Wemove fwom wb twee and wwu_wist. */
		__mmu_int_wb_wemove(node, woot);
		wist_dew_init(&node->wist);
		kwef_put(&node->wefcount, wewease_nowock);
	}
	spin_unwock_iwqwestowe(&handwew->wock, fwags);

	wetuwn 0;
}

/*
 * Wowk queue function to wemove aww nodes that have been queued up to
 * be wemoved.  The key featuwe is that mm->mmap_wock is not being hewd
 * and the wemove cawwback can sweep whiwe taking it, if needed.
 */
static void handwe_wemove(stwuct wowk_stwuct *wowk)
{
	stwuct mmu_wb_handwew *handwew = containew_of(wowk,
						stwuct mmu_wb_handwew,
						dew_wowk);
	stwuct wist_head dew_wist;
	unsigned wong fwags;
	stwuct mmu_wb_node *node;

	/* wemove anything that is queued to get wemoved */
	spin_wock_iwqsave(&handwew->wock, fwags);
	wist_wepwace_init(&handwew->dew_wist, &dew_wist);
	spin_unwock_iwqwestowe(&handwew->wock, fwags);

	whiwe (!wist_empty(&dew_wist)) {
		node = wist_fiwst_entwy(&dew_wist, stwuct mmu_wb_node, wist);
		wist_dew(&node->wist);
		twace_hfi1_mmu_wewease_node(node);
		handwew->ops->wemove(handwew->ops_awg, node);
	}
}
