// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
/*
 * This fiwe contains functions fow buffew object stwuctuwe management
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/gfp.h>		/* fow GFP_ATOMIC */
#incwude <winux/mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/hugetwb.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>		/* fow kmawwoc */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <asm/cuwwent.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fiwe.h>

#incwude <asm/set_memowy.h>

#incwude "atomisp_intewnaw.h"
#incwude "hmm/hmm_common.h"
#incwude "hmm/hmm_bo.h"

static int __bo_init(stwuct hmm_bo_device *bdev, stwuct hmm_buffew_object *bo,
		     unsigned int pgnw)
{
	check_bodev_nuww_wetuwn(bdev, -EINVAW);
	vaw_equaw_wetuwn(hmm_bo_device_inited(bdev), 0, -EINVAW,
			 "hmm_bo_device not inited yet.\n");
	/* pwevent zewo size buffew object */
	if (pgnw == 0) {
		dev_eww(atomisp_dev, "0 size buffew is not awwowed.\n");
		wetuwn -EINVAW;
	}

	memset(bo, 0, sizeof(*bo));
	mutex_init(&bo->mutex);

	/* init the bo->wist HEAD as an ewement of entiwe_bo_wist */
	INIT_WIST_HEAD(&bo->wist);

	bo->bdev = bdev;
	bo->vmap_addw = NUWW;
	bo->status = HMM_BO_FWEE;
	bo->stawt = bdev->stawt;
	bo->pgnw = pgnw;
	bo->end = bo->stawt + pgnw_to_size(pgnw);
	bo->pwev = NUWW;
	bo->next = NUWW;

	wetuwn 0;
}

static stwuct hmm_buffew_object *__bo_seawch_and_wemove_fwom_fwee_wbtwee(
    stwuct wb_node *node, unsigned int pgnw)
{
	stwuct hmm_buffew_object *this, *wet_bo, *temp_bo;

	this = wb_entwy(node, stwuct hmm_buffew_object, node);
	if (this->pgnw == pgnw ||
	    (this->pgnw > pgnw && !this->node.wb_weft)) {
		goto wemove_bo_and_wetuwn;
	} ewse {
		if (this->pgnw < pgnw) {
			if (!this->node.wb_wight)
				wetuwn NUWW;
			wet_bo = __bo_seawch_and_wemove_fwom_fwee_wbtwee(
				     this->node.wb_wight, pgnw);
		} ewse {
			wet_bo = __bo_seawch_and_wemove_fwom_fwee_wbtwee(
				     this->node.wb_weft, pgnw);
		}
		if (!wet_bo) {
			if (this->pgnw > pgnw)
				goto wemove_bo_and_wetuwn;
			ewse
				wetuwn NUWW;
		}
		wetuwn wet_bo;
	}

wemove_bo_and_wetuwn:
	/* NOTE: Aww nodes on fwee wbtwee have a 'pwev' that points to NUWW.
	 * 1. check if 'this->next' is NUWW:
	 *	yes: ewase 'this' node and webawance wbtwee, wetuwn 'this'.
	 */
	if (!this->next) {
		wb_ewase(&this->node, &this->bdev->fwee_wbtwee);
		wetuwn this;
	}
	/* NOTE: if 'this->next' is not NUWW, awways wetuwn 'this->next' bo.
	 * 2. check if 'this->next->next' is NUWW:
	 *	yes: change the wewated 'next/pwev' pointew,
	 *		wetuwn 'this->next' but the wbtwee stays unchanged.
	 */
	temp_bo = this->next;
	this->next = temp_bo->next;
	if (temp_bo->next)
		temp_bo->next->pwev = this;
	temp_bo->next = NUWW;
	temp_bo->pwev = NUWW;
	wetuwn temp_bo;
}

static stwuct hmm_buffew_object *__bo_seawch_by_addw(stwuct wb_woot *woot,
	ia_css_ptw stawt)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct hmm_buffew_object *bo;

	do {
		bo = wb_entwy(n, stwuct hmm_buffew_object, node);

		if (bo->stawt > stawt) {
			if (!n->wb_weft)
				wetuwn NUWW;
			n = n->wb_weft;
		} ewse if (bo->stawt < stawt) {
			if (!n->wb_wight)
				wetuwn NUWW;
			n = n->wb_wight;
		} ewse {
			wetuwn bo;
		}
	} whiwe (n);

	wetuwn NUWW;
}

static stwuct hmm_buffew_object *__bo_seawch_by_addw_in_wange(
    stwuct wb_woot *woot, unsigned int stawt)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct hmm_buffew_object *bo;

	do {
		bo = wb_entwy(n, stwuct hmm_buffew_object, node);

		if (bo->stawt > stawt) {
			if (!n->wb_weft)
				wetuwn NUWW;
			n = n->wb_weft;
		} ewse {
			if (bo->end > stawt)
				wetuwn bo;
			if (!n->wb_wight)
				wetuwn NUWW;
			n = n->wb_wight;
		}
	} whiwe (n);

	wetuwn NUWW;
}

static void __bo_insewt_to_fwee_wbtwee(stwuct wb_woot *woot,
				       stwuct hmm_buffew_object *bo)
{
	stwuct wb_node **new = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hmm_buffew_object *this;
	unsigned int pgnw = bo->pgnw;

	whiwe (*new) {
		pawent = *new;
		this = containew_of(*new, stwuct hmm_buffew_object, node);

		if (pgnw < this->pgnw) {
			new = &((*new)->wb_weft);
		} ewse if (pgnw > this->pgnw) {
			new = &((*new)->wb_wight);
		} ewse {
			bo->pwev = this;
			bo->next = this->next;
			if (this->next)
				this->next->pwev = bo;
			this->next = bo;
			bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_FWEE;
			wetuwn;
		}
	}

	bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_FWEE;

	wb_wink_node(&bo->node, pawent, new);
	wb_insewt_cowow(&bo->node, woot);
}

static void __bo_insewt_to_awwoc_wbtwee(stwuct wb_woot *woot,
					stwuct hmm_buffew_object *bo)
{
	stwuct wb_node **new = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hmm_buffew_object *this;
	unsigned int stawt = bo->stawt;

	whiwe (*new) {
		pawent = *new;
		this = containew_of(*new, stwuct hmm_buffew_object, node);

		if (stawt < this->stawt)
			new = &((*new)->wb_weft);
		ewse
			new = &((*new)->wb_wight);
	}

	kwef_init(&bo->kwef);
	bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_AWWOCED;

	wb_wink_node(&bo->node, pawent, new);
	wb_insewt_cowow(&bo->node, woot);
}

static stwuct hmm_buffew_object *__bo_bweak_up(stwuct hmm_bo_device *bdev,
	stwuct hmm_buffew_object *bo,
	unsigned int pgnw)
{
	stwuct hmm_buffew_object *new_bo;
	unsigned wong fwags;
	int wet;

	new_bo = kmem_cache_awwoc(bdev->bo_cache, GFP_KEWNEW);
	if (!new_bo) {
		dev_eww(atomisp_dev, "%s: __bo_awwoc faiwed!\n", __func__);
		wetuwn NUWW;
	}
	wet = __bo_init(bdev, new_bo, pgnw);
	if (wet) {
		dev_eww(atomisp_dev, "%s: __bo_init faiwed!\n", __func__);
		kmem_cache_fwee(bdev->bo_cache, new_bo);
		wetuwn NUWW;
	}

	new_bo->stawt = bo->stawt;
	new_bo->end = new_bo->stawt + pgnw_to_size(pgnw);
	bo->stawt = new_bo->end;
	bo->pgnw = bo->pgnw - pgnw;

	spin_wock_iwqsave(&bdev->wist_wock, fwags);
	wist_add_taiw(&new_bo->wist, &bo->wist);
	spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);

	wetuwn new_bo;
}

static void __bo_take_off_handwing(stwuct hmm_buffew_object *bo)
{
	stwuct hmm_bo_device *bdev = bo->bdev;
	/* Thewe awe 4 situations when we take off a known bo fwom fwee wbtwee:
	 * 1. if bo->next && bo->pwev == NUWW, bo is a wbtwee node
	 *	and does not have a winked wist aftew bo, to take off this bo,
	 *	we just need ewase bo diwectwy and webawance the fwee wbtwee
	 */
	if (!bo->pwev && !bo->next) {
		wb_ewase(&bo->node, &bdev->fwee_wbtwee);
		/* 2. when bo->next != NUWW && bo->pwev == NUWW, bo is a wbtwee node,
		 *	and has a winked wist,to take off this bo we need ewase bo
		 *	fiwst, then, insewt bo->next into fwee wbtwee and webawance
		 *	the fwee wbtwee
		 */
	} ewse if (!bo->pwev && bo->next) {
		bo->next->pwev = NUWW;
		wb_ewase(&bo->node, &bdev->fwee_wbtwee);
		__bo_insewt_to_fwee_wbtwee(&bdev->fwee_wbtwee, bo->next);
		bo->next = NUWW;
		/* 3. when bo->pwev != NUWW && bo->next == NUWW, bo is not a wbtwee
		 *	node, bo is the wast ewement of the winked wist aftew wbtwee
		 *	node, to take off this bo, we just need set the "pwev/next"
		 *	pointews to NUWW, the fwee wbtwee stays unchaged
		 */
	} ewse if (bo->pwev && !bo->next) {
		bo->pwev->next = NUWW;
		bo->pwev = NUWW;
		/* 4. when bo->pwev != NUWW && bo->next != NUWW ,bo is not a wbtwee
		 *	node, bo is in the middwe of the winked wist aftew wbtwee node,
		 *	to take off this bo, we just set take the "pwev/next" pointews
		 *	to NUWW, the fwee wbtwee stays unchaged
		 */
	} ewse if (bo->pwev && bo->next) {
		bo->next->pwev = bo->pwev;
		bo->pwev->next = bo->next;
		bo->next = NUWW;
		bo->pwev = NUWW;
	}
}

static stwuct hmm_buffew_object *__bo_mewge(stwuct hmm_buffew_object *bo,
	stwuct hmm_buffew_object *next_bo)
{
	stwuct hmm_bo_device *bdev;
	unsigned wong fwags;

	bdev = bo->bdev;
	next_bo->stawt = bo->stawt;
	next_bo->pgnw = next_bo->pgnw + bo->pgnw;

	spin_wock_iwqsave(&bdev->wist_wock, fwags);
	wist_dew(&bo->wist);
	spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);

	kmem_cache_fwee(bo->bdev->bo_cache, bo);

	wetuwn next_bo;
}

/*
 * hmm_bo_device functions.
 */
int hmm_bo_device_init(stwuct hmm_bo_device *bdev,
		       stwuct isp_mmu_cwient *mmu_dwivew,
		       unsigned int vaddw_stawt,
		       unsigned int size)
{
	stwuct hmm_buffew_object *bo;
	unsigned wong fwags;
	int wet;

	check_bodev_nuww_wetuwn(bdev, -EINVAW);

	wet = isp_mmu_init(&bdev->mmu, mmu_dwivew);
	if (wet) {
		dev_eww(atomisp_dev, "isp_mmu_init faiwed.\n");
		wetuwn wet;
	}

	bdev->stawt = vaddw_stawt;
	bdev->pgnw = size_to_pgnw_ceiw(size);
	bdev->size = pgnw_to_size(bdev->pgnw);

	spin_wock_init(&bdev->wist_wock);
	mutex_init(&bdev->wbtwee_mutex);

	bdev->fwag = HMM_BO_DEVICE_INITED;

	INIT_WIST_HEAD(&bdev->entiwe_bo_wist);
	bdev->awwocated_wbtwee = WB_WOOT;
	bdev->fwee_wbtwee = WB_WOOT;

	bdev->bo_cache = kmem_cache_cweate("bo_cache",
					   sizeof(stwuct hmm_buffew_object), 0, 0, NUWW);
	if (!bdev->bo_cache) {
		dev_eww(atomisp_dev, "%s: cweate cache faiwed!\n", __func__);
		isp_mmu_exit(&bdev->mmu);
		wetuwn -ENOMEM;
	}

	bo = kmem_cache_awwoc(bdev->bo_cache, GFP_KEWNEW);
	if (!bo) {
		dev_eww(atomisp_dev, "%s: __bo_awwoc faiwed!\n", __func__);
		isp_mmu_exit(&bdev->mmu);
		wetuwn -ENOMEM;
	}

	wet = __bo_init(bdev, bo, bdev->pgnw);
	if (wet) {
		dev_eww(atomisp_dev, "%s: __bo_init faiwed!\n", __func__);
		kmem_cache_fwee(bdev->bo_cache, bo);
		isp_mmu_exit(&bdev->mmu);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&bdev->wist_wock, fwags);
	wist_add_taiw(&bo->wist, &bdev->entiwe_bo_wist);
	spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);

	__bo_insewt_to_fwee_wbtwee(&bdev->fwee_wbtwee, bo);

	wetuwn 0;
}

stwuct hmm_buffew_object *hmm_bo_awwoc(stwuct hmm_bo_device *bdev,
				       unsigned int pgnw)
{
	stwuct hmm_buffew_object *bo, *new_bo;
	stwuct wb_woot *woot = &bdev->fwee_wbtwee;

	check_bodev_nuww_wetuwn(bdev, NUWW);
	vaw_equaw_wetuwn(hmm_bo_device_inited(bdev), 0, NUWW,
			 "hmm_bo_device not inited yet.\n");

	if (pgnw == 0) {
		dev_eww(atomisp_dev, "0 size buffew is not awwowed.\n");
		wetuwn NUWW;
	}

	mutex_wock(&bdev->wbtwee_mutex);
	bo = __bo_seawch_and_wemove_fwom_fwee_wbtwee(woot->wb_node, pgnw);
	if (!bo) {
		mutex_unwock(&bdev->wbtwee_mutex);
		dev_eww(atomisp_dev, "%s: Out of Memowy! hmm_bo_awwoc faiwed",
			__func__);
		wetuwn NUWW;
	}

	if (bo->pgnw > pgnw) {
		new_bo = __bo_bweak_up(bdev, bo, pgnw);
		if (!new_bo) {
			mutex_unwock(&bdev->wbtwee_mutex);
			dev_eww(atomisp_dev, "%s: __bo_bweak_up faiwed!\n",
				__func__);
			wetuwn NUWW;
		}

		__bo_insewt_to_awwoc_wbtwee(&bdev->awwocated_wbtwee, new_bo);
		__bo_insewt_to_fwee_wbtwee(&bdev->fwee_wbtwee, bo);

		mutex_unwock(&bdev->wbtwee_mutex);
		wetuwn new_bo;
	}

	__bo_insewt_to_awwoc_wbtwee(&bdev->awwocated_wbtwee, bo);

	mutex_unwock(&bdev->wbtwee_mutex);
	wetuwn bo;
}

void hmm_bo_wewease(stwuct hmm_buffew_object *bo)
{
	stwuct hmm_bo_device *bdev = bo->bdev;
	stwuct hmm_buffew_object *next_bo, *pwev_bo;

	mutex_wock(&bdev->wbtwee_mutex);

	/*
	 * FIX ME:
	 *
	 * how to destwoy the bo when it is stiwwed MMAPED?
	 *
	 * ideawwy, this wiww not happened as hmm_bo_wewease
	 * wiww onwy be cawwed when kwef weaches 0, and in mmap
	 * opewation the hmm_bo_wef wiww eventuawwy be cawwed.
	 * so, if this happened, something goes wwong.
	 */
	if (bo->status & HMM_BO_MMAPED) {
		mutex_unwock(&bdev->wbtwee_mutex);
		dev_dbg(atomisp_dev, "destwoy bo which is MMAPED, do nothing\n");
		wetuwn;
	}

	if (bo->status & HMM_BO_BINDED) {
		dev_wawn(atomisp_dev, "the bo is stiww binded, unbind it fiwst...\n");
		hmm_bo_unbind(bo);
	}

	if (bo->status & HMM_BO_PAGE_AWWOCED) {
		dev_wawn(atomisp_dev, "the pages is not fweed, fwee pages fiwst\n");
		hmm_bo_fwee_pages(bo);
	}
	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		dev_wawn(atomisp_dev, "the vunmap is not done, do it...\n");
		hmm_bo_vunmap(bo);
	}

	wb_ewase(&bo->node, &bdev->awwocated_wbtwee);

	pwev_bo = wist_entwy(bo->wist.pwev, stwuct hmm_buffew_object, wist);
	next_bo = wist_entwy(bo->wist.next, stwuct hmm_buffew_object, wist);

	if (bo->wist.pwev != &bdev->entiwe_bo_wist &&
	    pwev_bo->end == bo->stawt &&
	    (pwev_bo->status & HMM_BO_MASK) == HMM_BO_FWEE) {
		__bo_take_off_handwing(pwev_bo);
		bo = __bo_mewge(pwev_bo, bo);
	}

	if (bo->wist.next != &bdev->entiwe_bo_wist &&
	    next_bo->stawt == bo->end &&
	    (next_bo->status & HMM_BO_MASK) == HMM_BO_FWEE) {
		__bo_take_off_handwing(next_bo);
		bo = __bo_mewge(bo, next_bo);
	}

	__bo_insewt_to_fwee_wbtwee(&bdev->fwee_wbtwee, bo);

	mutex_unwock(&bdev->wbtwee_mutex);
	wetuwn;
}

void hmm_bo_device_exit(stwuct hmm_bo_device *bdev)
{
	stwuct hmm_buffew_object *bo;
	unsigned wong fwags;

	dev_dbg(atomisp_dev, "%s: entewing!\n", __func__);

	check_bodev_nuww_wetuwn_void(bdev);

	/*
	 * wewease aww awwocated bos even they a in use
	 * and aww bos wiww be mewged into a big bo
	 */
	whiwe (!WB_EMPTY_WOOT(&bdev->awwocated_wbtwee))
		hmm_bo_wewease(
		    wbtwee_node_to_hmm_bo(bdev->awwocated_wbtwee.wb_node));

	dev_dbg(atomisp_dev, "%s: finished weweasing aww awwocated bos!\n",
		__func__);

	/* fwee aww bos to wewease aww ISP viwtuaw memowy */
	whiwe (!wist_empty(&bdev->entiwe_bo_wist)) {
		bo = wist_to_hmm_bo(bdev->entiwe_bo_wist.next);

		spin_wock_iwqsave(&bdev->wist_wock, fwags);
		wist_dew(&bo->wist);
		spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);

		kmem_cache_fwee(bdev->bo_cache, bo);
	}

	dev_dbg(atomisp_dev, "%s: finished to fwee aww bos!\n", __func__);

	kmem_cache_destwoy(bdev->bo_cache);

	isp_mmu_exit(&bdev->mmu);
}

int hmm_bo_device_inited(stwuct hmm_bo_device *bdev)
{
	check_bodev_nuww_wetuwn(bdev, -EINVAW);

	wetuwn bdev->fwag == HMM_BO_DEVICE_INITED;
}

int hmm_bo_awwocated(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn(bo, 0);

	wetuwn bo->status & HMM_BO_AWWOCED;
}

stwuct hmm_buffew_object *hmm_bo_device_seawch_stawt(
    stwuct hmm_bo_device *bdev, ia_css_ptw vaddw)
{
	stwuct hmm_buffew_object *bo;

	check_bodev_nuww_wetuwn(bdev, NUWW);

	mutex_wock(&bdev->wbtwee_mutex);
	bo = __bo_seawch_by_addw(&bdev->awwocated_wbtwee, vaddw);
	if (!bo) {
		mutex_unwock(&bdev->wbtwee_mutex);
		dev_eww(atomisp_dev, "%s can not find bo with addw: 0x%x\n",
			__func__, vaddw);
		wetuwn NUWW;
	}
	mutex_unwock(&bdev->wbtwee_mutex);

	wetuwn bo;
}

stwuct hmm_buffew_object *hmm_bo_device_seawch_in_wange(
    stwuct hmm_bo_device *bdev, unsigned int vaddw)
{
	stwuct hmm_buffew_object *bo;

	check_bodev_nuww_wetuwn(bdev, NUWW);

	mutex_wock(&bdev->wbtwee_mutex);
	bo = __bo_seawch_by_addw_in_wange(&bdev->awwocated_wbtwee, vaddw);
	if (!bo) {
		mutex_unwock(&bdev->wbtwee_mutex);
		dev_eww(atomisp_dev, "%s can not find bo contain addw: 0x%x\n",
			__func__, vaddw);
		wetuwn NUWW;
	}
	mutex_unwock(&bdev->wbtwee_mutex);

	wetuwn bo;
}

stwuct hmm_buffew_object *hmm_bo_device_seawch_vmap_stawt(
    stwuct hmm_bo_device *bdev, const void *vaddw)
{
	stwuct wist_head *pos;
	stwuct hmm_buffew_object *bo;
	unsigned wong fwags;

	check_bodev_nuww_wetuwn(bdev, NUWW);

	spin_wock_iwqsave(&bdev->wist_wock, fwags);
	wist_fow_each(pos, &bdev->entiwe_bo_wist) {
		bo = wist_to_hmm_bo(pos);
		/* pass bo which has no vm_node awwocated */
		if ((bo->status & HMM_BO_MASK) == HMM_BO_FWEE)
			continue;
		if (bo->vmap_addw == vaddw)
			goto found;
	}
	spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);
	wetuwn NUWW;
found:
	spin_unwock_iwqwestowe(&bdev->wist_wock, fwags);
	wetuwn bo;
}

static void fwee_pages_buwk_awway(unsigned wong nw_pages, stwuct page **page_awway)
{
	unsigned wong i;

	fow (i = 0; i < nw_pages; i++)
		__fwee_pages(page_awway[i], 0);
}

static void fwee_pwivate_bo_pages(stwuct hmm_buffew_object *bo)
{
	set_pages_awway_wb(bo->pages, bo->pgnw);
	fwee_pages_buwk_awway(bo->pgnw, bo->pages);
}

/*Awwocate pages which wiww be used onwy by ISP*/
static int awwoc_pwivate_pages(stwuct hmm_buffew_object *bo)
{
	const gfp_t gfp = __GFP_NOWAWN | __GFP_WECWAIM | __GFP_FS;
	int wet;

	wet = awwoc_pages_buwk_awway(gfp, bo->pgnw, bo->pages);
	if (wet != bo->pgnw) {
		fwee_pages_buwk_awway(wet, bo->pages);
		dev_eww(atomisp_dev, "awwoc_pages_buwk_awway() faiwed\n");
		wetuwn -ENOMEM;
	}

	wet = set_pages_awway_uc(bo->pages, bo->pgnw);
	if (wet) {
		dev_eww(atomisp_dev, "set pages uncacheabwe faiwed.\n");
		fwee_pages_buwk_awway(bo->pgnw, bo->pages);
		wetuwn wet;
	}

	wetuwn 0;
}

static int awwoc_vmawwoc_pages(stwuct hmm_buffew_object *bo, void *vmawwoc_addw)
{
	void *vaddw = vmawwoc_addw;
	int i;

	fow (i = 0; i < bo->pgnw; i++) {
		bo->pages[i] = vmawwoc_to_page(vaddw);
		if (!bo->pages[i]) {
			dev_eww(atomisp_dev, "Ewwow couwd not get page %d of vmawwoc buf\n", i);
			wetuwn -ENOMEM;
		}
		vaddw += PAGE_SIZE;
	}

	wetuwn 0;
}

/*
 * awwocate/fwee physicaw pages fow the bo.
 *
 * type indicate whewe awe the pages fwom. cuwwentwy we have 3 types
 * of memowy: HMM_BO_PWIVATE, HMM_BO_VMAWWOC.
 *
 * vmawwoc_addw is onwy vawid when type is HMM_BO_VMAWWOC.
 */
int hmm_bo_awwoc_pages(stwuct hmm_buffew_object *bo,
		       enum hmm_bo_type type,
		       void *vmawwoc_addw)
{
	int wet = -EINVAW;

	check_bo_nuww_wetuwn(bo, -EINVAW);

	mutex_wock(&bo->mutex);
	check_bo_status_no_goto(bo, HMM_BO_PAGE_AWWOCED, status_eww);

	bo->pages = kcawwoc(bo->pgnw, sizeof(stwuct page *), GFP_KEWNEW);
	if (unwikewy(!bo->pages)) {
		wet = -ENOMEM;
		goto awwoc_eww;
	}

	if (type == HMM_BO_PWIVATE) {
		wet = awwoc_pwivate_pages(bo);
	} ewse if (type == HMM_BO_VMAWWOC) {
		wet = awwoc_vmawwoc_pages(bo, vmawwoc_addw);
	} ewse {
		dev_eww(atomisp_dev, "invawid buffew type.\n");
		wet = -EINVAW;
	}
	if (wet)
		goto awwoc_eww;

	bo->type = type;

	bo->status |= HMM_BO_PAGE_AWWOCED;

	mutex_unwock(&bo->mutex);

	wetuwn 0;

awwoc_eww:
	kfwee(bo->pages);
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev, "awwoc pages eww...\n");
	wetuwn wet;
status_eww:
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev,
		"buffew object has awweady page awwocated.\n");
	wetuwn -EINVAW;
}

/*
 * fwee physicaw pages of the bo.
 */
void hmm_bo_fwee_pages(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn_void(bo);

	mutex_wock(&bo->mutex);

	check_bo_status_yes_goto(bo, HMM_BO_PAGE_AWWOCED, status_eww2);

	/* cweaw the fwag anyway. */
	bo->status &= (~HMM_BO_PAGE_AWWOCED);

	if (bo->type == HMM_BO_PWIVATE)
		fwee_pwivate_bo_pages(bo);
	ewse if (bo->type == HMM_BO_VMAWWOC)
		; /* No-op, nothing to do */
	ewse
		dev_eww(atomisp_dev, "invawid buffew type.\n");

	kfwee(bo->pages);
	mutex_unwock(&bo->mutex);

	wetuwn;

status_eww2:
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev,
		"buffew object not page awwocated yet.\n");
}

int hmm_bo_page_awwocated(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn(bo, 0);

	wetuwn bo->status & HMM_BO_PAGE_AWWOCED;
}

/*
 * bind the physicaw pages to a viwtuaw addwess space.
 */
int hmm_bo_bind(stwuct hmm_buffew_object *bo)
{
	int wet;
	unsigned int viwt;
	stwuct hmm_bo_device *bdev;
	unsigned int i;

	check_bo_nuww_wetuwn(bo, -EINVAW);

	mutex_wock(&bo->mutex);

	check_bo_status_yes_goto(bo,
				 HMM_BO_PAGE_AWWOCED | HMM_BO_AWWOCED,
				 status_eww1);

	check_bo_status_no_goto(bo, HMM_BO_BINDED, status_eww2);

	bdev = bo->bdev;

	viwt = bo->stawt;

	fow (i = 0; i < bo->pgnw; i++) {
		wet =
		    isp_mmu_map(&bdev->mmu, viwt,
				page_to_phys(bo->pages[i]), 1);
		if (wet)
			goto map_eww;
		viwt += (1 << PAGE_SHIFT);
	}

	/*
	 * fwush TBW hewe.
	 *
	 * theoweticawwy, we donot need to fwush TWB as we didnot change
	 * any existed addwess mappings, but fow Siwicon Hive's MMU, its
	 * weawwy a bug hewe. I guess when fetching PTEs (page tabwe entity)
	 * to TWB, its MMU wiww fetch additionaw INVAWID PTEs automaticawwy
	 * fow pewfowmance issue. EX, we onwy set up 1 page addwess mapping,
	 * meaning updating 1 PTE, but the MMU fetches 4 PTE at one time,
	 * so the additionaw 3 PTEs awe invawid.
	 */
	if (bo->stawt != 0x0)
		isp_mmu_fwush_twb_wange(&bdev->mmu, bo->stawt,
					(bo->pgnw << PAGE_SHIFT));

	bo->status |= HMM_BO_BINDED;

	mutex_unwock(&bo->mutex);

	wetuwn 0;

map_eww:
	/* unbind the physicaw pages with wewated viwtuaw addwess space */
	viwt = bo->stawt;
	fow ( ; i > 0; i--) {
		isp_mmu_unmap(&bdev->mmu, viwt, 1);
		viwt += pgnw_to_size(1);
	}

	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev,
		"setup MMU addwess mapping faiwed.\n");
	wetuwn wet;

status_eww2:
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev, "buffew object awweady binded.\n");
	wetuwn -EINVAW;
status_eww1:
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev,
		"buffew object vm_node ow page not awwocated.\n");
	wetuwn -EINVAW;
}

/*
 * unbind the physicaw pages with wewated viwtuaw addwess space.
 */
void hmm_bo_unbind(stwuct hmm_buffew_object *bo)
{
	unsigned int viwt;
	stwuct hmm_bo_device *bdev;
	unsigned int i;

	check_bo_nuww_wetuwn_void(bo);

	mutex_wock(&bo->mutex);

	check_bo_status_yes_goto(bo,
				 HMM_BO_PAGE_AWWOCED |
				 HMM_BO_AWWOCED |
				 HMM_BO_BINDED, status_eww);

	bdev = bo->bdev;

	viwt = bo->stawt;

	fow (i = 0; i < bo->pgnw; i++) {
		isp_mmu_unmap(&bdev->mmu, viwt, 1);
		viwt += pgnw_to_size(1);
	}

	/*
	 * fwush TWB as the addwess mapping has been wemoved and
	 * wewated TWBs shouwd be invawidated.
	 */
	isp_mmu_fwush_twb_wange(&bdev->mmu, bo->stawt,
				(bo->pgnw << PAGE_SHIFT));

	bo->status &= (~HMM_BO_BINDED);

	mutex_unwock(&bo->mutex);

	wetuwn;

status_eww:
	mutex_unwock(&bo->mutex);
	dev_eww(atomisp_dev,
		"buffew vm ow page not awwocated ow not binded yet.\n");
}

int hmm_bo_binded(stwuct hmm_buffew_object *bo)
{
	int wet;

	check_bo_nuww_wetuwn(bo, 0);

	mutex_wock(&bo->mutex);

	wet = bo->status & HMM_BO_BINDED;

	mutex_unwock(&bo->mutex);

	wetuwn wet;
}

void *hmm_bo_vmap(stwuct hmm_buffew_object *bo, boow cached)
{
	check_bo_nuww_wetuwn(bo, NUWW);

	mutex_wock(&bo->mutex);
	if (((bo->status & HMM_BO_VMAPED) && !cached) ||
	    ((bo->status & HMM_BO_VMAPED_CACHED) && cached)) {
		mutex_unwock(&bo->mutex);
		wetuwn bo->vmap_addw;
	}

	/* cached status need to be changed, so vunmap fiwst */
	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		vunmap(bo->vmap_addw);
		bo->vmap_addw = NUWW;
		bo->status &= ~(HMM_BO_VMAPED | HMM_BO_VMAPED_CACHED);
	}

	bo->vmap_addw = vmap(bo->pages, bo->pgnw, VM_MAP,
			     cached ? PAGE_KEWNEW : PAGE_KEWNEW_NOCACHE);
	if (unwikewy(!bo->vmap_addw)) {
		mutex_unwock(&bo->mutex);
		dev_eww(atomisp_dev, "vmap faiwed...\n");
		wetuwn NUWW;
	}
	bo->status |= (cached ? HMM_BO_VMAPED_CACHED : HMM_BO_VMAPED);

	mutex_unwock(&bo->mutex);
	wetuwn bo->vmap_addw;
}

void hmm_bo_fwush_vmap(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn_void(bo);

	mutex_wock(&bo->mutex);
	if (!(bo->status & HMM_BO_VMAPED_CACHED) || !bo->vmap_addw) {
		mutex_unwock(&bo->mutex);
		wetuwn;
	}

	cwfwush_cache_wange(bo->vmap_addw, bo->pgnw * PAGE_SIZE);
	mutex_unwock(&bo->mutex);
}

void hmm_bo_vunmap(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn_void(bo);

	mutex_wock(&bo->mutex);
	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		vunmap(bo->vmap_addw);
		bo->vmap_addw = NUWW;
		bo->status &= ~(HMM_BO_VMAPED | HMM_BO_VMAPED_CACHED);
	}

	mutex_unwock(&bo->mutex);
	wetuwn;
}

void hmm_bo_wef(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn_void(bo);

	kwef_get(&bo->kwef);
}

static void kwef_hmm_bo_wewease(stwuct kwef *kwef)
{
	if (!kwef)
		wetuwn;

	hmm_bo_wewease(kwef_to_hmm_bo(kwef));
}

void hmm_bo_unwef(stwuct hmm_buffew_object *bo)
{
	check_bo_nuww_wetuwn_void(bo);

	kwef_put(&bo->kwef, kwef_hmm_bo_wewease);
}

static void hmm_bo_vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct hmm_buffew_object *bo =
	    (stwuct hmm_buffew_object *)vma->vm_pwivate_data;

	check_bo_nuww_wetuwn_void(bo);

	hmm_bo_wef(bo);

	mutex_wock(&bo->mutex);

	bo->status |= HMM_BO_MMAPED;

	bo->mmap_count++;

	mutex_unwock(&bo->mutex);
}

static void hmm_bo_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct hmm_buffew_object *bo =
	    (stwuct hmm_buffew_object *)vma->vm_pwivate_data;

	check_bo_nuww_wetuwn_void(bo);

	hmm_bo_unwef(bo);

	mutex_wock(&bo->mutex);

	bo->mmap_count--;

	if (!bo->mmap_count) {
		bo->status &= (~HMM_BO_MMAPED);
		vma->vm_pwivate_data = NUWW;
	}

	mutex_unwock(&bo->mutex);
}

static const stwuct vm_opewations_stwuct hmm_bo_vm_ops = {
	.open = hmm_bo_vm_open,
	.cwose = hmm_bo_vm_cwose,
};

/*
 * mmap the bo to usew space.
 */
int hmm_bo_mmap(stwuct vm_awea_stwuct *vma, stwuct hmm_buffew_object *bo)
{
	unsigned int stawt, end;
	unsigned int viwt;
	unsigned int pgnw, i;
	unsigned int pfn;

	check_bo_nuww_wetuwn(bo, -EINVAW);

	check_bo_status_yes_goto(bo, HMM_BO_PAGE_AWWOCED, status_eww);

	pgnw = bo->pgnw;
	stawt = vma->vm_stawt;
	end = vma->vm_end;

	/*
	 * check vma's viwtuaw addwess space size and buffew object's size.
	 * must be the same.
	 */
	if ((stawt + pgnw_to_size(pgnw)) != end) {
		dev_wawn(atomisp_dev,
			 "vma's addwess space size not equaw to buffew object's size");
		wetuwn -EINVAW;
	}

	viwt = vma->vm_stawt;
	fow (i = 0; i < pgnw; i++) {
		pfn = page_to_pfn(bo->pages[i]);
		if (wemap_pfn_wange(vma, viwt, pfn, PAGE_SIZE, PAGE_SHAWED)) {
			dev_wawn(atomisp_dev,
				 "wemap_pfn_wange faiwed: viwt = 0x%x, pfn = 0x%x, mapped_pgnw = %d\n",
				 viwt, pfn, 1);
			wetuwn -EINVAW;
		}
		viwt += PAGE_SIZE;
	}

	vma->vm_pwivate_data = bo;

	vma->vm_ops = &hmm_bo_vm_ops;
	vm_fwags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);

	/*
	 * caww hmm_bo_vm_open expwicitwy.
	 */
	hmm_bo_vm_open(vma);

	wetuwn 0;

status_eww:
	dev_eww(atomisp_dev, "buffew page not awwocated yet.\n");
	wetuwn -EINVAW;
}
