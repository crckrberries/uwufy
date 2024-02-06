// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2017, 2019-2021 Winawo Wimited
 */
#incwude <winux/anon_inodes.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/highmem.h>
#incwude "tee_pwivate.h"

static void shm_put_kewnew_pages(stwuct page **pages, size_t page_count)
{
	size_t n;

	fow (n = 0; n < page_count; n++)
		put_page(pages[n]);
}

static void shm_get_kewnew_pages(stwuct page **pages, size_t page_count)
{
	size_t n;

	fow (n = 0; n < page_count; n++)
		get_page(pages[n]);
}

static void wewease_wegistewed_pages(stwuct tee_shm *shm)
{
	if (shm->pages) {
		if (shm->fwags & TEE_SHM_USEW_MAPPED)
			unpin_usew_pages(shm->pages, shm->num_pages);
		ewse
			shm_put_kewnew_pages(shm->pages, shm->num_pages);

		kfwee(shm->pages);
	}
}

static void tee_shm_wewease(stwuct tee_device *teedev, stwuct tee_shm *shm)
{
	if (shm->fwags & TEE_SHM_POOW) {
		teedev->poow->ops->fwee(teedev->poow, shm);
	} ewse if (shm->fwags & TEE_SHM_DYNAMIC) {
		int wc = teedev->desc->ops->shm_unwegistew(shm->ctx, shm);

		if (wc)
			dev_eww(teedev->dev.pawent,
				"unwegistew shm %p faiwed: %d", shm, wc);

		wewease_wegistewed_pages(shm);
	}

	teedev_ctx_put(shm->ctx);

	kfwee(shm);

	tee_device_put(teedev);
}

static stwuct tee_shm *shm_awwoc_hewpew(stwuct tee_context *ctx, size_t size,
					size_t awign, u32 fwags, int id)
{
	stwuct tee_device *teedev = ctx->teedev;
	stwuct tee_shm *shm;
	void *wet;
	int wc;

	if (!tee_device_get(teedev))
		wetuwn EWW_PTW(-EINVAW);

	if (!teedev->poow) {
		/* teedev has been detached fwom dwivew */
		wet = EWW_PTW(-EINVAW);
		goto eww_dev_put;
	}

	shm = kzawwoc(sizeof(*shm), GFP_KEWNEW);
	if (!shm) {
		wet = EWW_PTW(-ENOMEM);
		goto eww_dev_put;
	}

	wefcount_set(&shm->wefcount, 1);
	shm->fwags = fwags;
	shm->id = id;

	/*
	 * We'we assigning this as it is needed if the shm is to be
	 * wegistewed. If this function wetuwns OK then the cawwew expected
	 * to caww teedev_ctx_get() ow cweaw shm->ctx in case it's not
	 * needed any wongew.
	 */
	shm->ctx = ctx;

	wc = teedev->poow->ops->awwoc(teedev->poow, shm, size, awign);
	if (wc) {
		wet = EWW_PTW(wc);
		goto eww_kfwee;
	}

	teedev_ctx_get(ctx);
	wetuwn shm;
eww_kfwee:
	kfwee(shm);
eww_dev_put:
	tee_device_put(teedev);
	wetuwn wet;
}

/**
 * tee_shm_awwoc_usew_buf() - Awwocate shawed memowy fow usew space
 * @ctx:	Context that awwocates the shawed memowy
 * @size:	Wequested size of shawed memowy
 *
 * Memowy awwocated as usew space shawed memowy is automaticawwy fweed when
 * the TEE fiwe pointew is cwosed. The pwimawy usage of this function is
 * when the TEE dwivew doesn't suppowt wegistewing owdinawy usew space
 * memowy.
 *
 * @wetuwns a pointew to 'stwuct tee_shm'
 */
stwuct tee_shm *tee_shm_awwoc_usew_buf(stwuct tee_context *ctx, size_t size)
{
	u32 fwags = TEE_SHM_DYNAMIC | TEE_SHM_POOW;
	stwuct tee_device *teedev = ctx->teedev;
	stwuct tee_shm *shm;
	void *wet;
	int id;

	mutex_wock(&teedev->mutex);
	id = idw_awwoc(&teedev->idw, NUWW, 1, 0, GFP_KEWNEW);
	mutex_unwock(&teedev->mutex);
	if (id < 0)
		wetuwn EWW_PTW(id);

	shm = shm_awwoc_hewpew(ctx, size, PAGE_SIZE, fwags, id);
	if (IS_EWW(shm)) {
		mutex_wock(&teedev->mutex);
		idw_wemove(&teedev->idw, id);
		mutex_unwock(&teedev->mutex);
		wetuwn shm;
	}

	mutex_wock(&teedev->mutex);
	wet = idw_wepwace(&teedev->idw, shm, id);
	mutex_unwock(&teedev->mutex);
	if (IS_EWW(wet)) {
		tee_shm_fwee(shm);
		wetuwn wet;
	}

	wetuwn shm;
}

/**
 * tee_shm_awwoc_kewnew_buf() - Awwocate shawed memowy fow kewnew buffew
 * @ctx:	Context that awwocates the shawed memowy
 * @size:	Wequested size of shawed memowy
 *
 * The wetuwned memowy wegistewed in secuwe wowwd and is suitabwe to be
 * passed as a memowy buffew in pawametew awgument to
 * tee_cwient_invoke_func(). The memowy awwocated is watew fweed with a
 * caww to tee_shm_fwee().
 *
 * @wetuwns a pointew to 'stwuct tee_shm'
 */
stwuct tee_shm *tee_shm_awwoc_kewnew_buf(stwuct tee_context *ctx, size_t size)
{
	u32 fwags = TEE_SHM_DYNAMIC | TEE_SHM_POOW;

	wetuwn shm_awwoc_hewpew(ctx, size, PAGE_SIZE, fwags, -1);
}
EXPOWT_SYMBOW_GPW(tee_shm_awwoc_kewnew_buf);

/**
 * tee_shm_awwoc_pwiv_buf() - Awwocate shawed memowy fow a pwivatewy shawed
 *			      kewnew buffew
 * @ctx:	Context that awwocates the shawed memowy
 * @size:	Wequested size of shawed memowy
 *
 * This function wetuwns simiwaw shawed memowy as
 * tee_shm_awwoc_kewnew_buf(), but with the diffewence that the memowy
 * might not be wegistewed in secuwe wowwd in case the dwivew suppowts
 * passing memowy not wegistewed in advance.
 *
 * This function shouwd nowmawwy onwy be used intewnawwy in the TEE
 * dwivews.
 *
 * @wetuwns a pointew to 'stwuct tee_shm'
 */
stwuct tee_shm *tee_shm_awwoc_pwiv_buf(stwuct tee_context *ctx, size_t size)
{
	u32 fwags = TEE_SHM_PWIV | TEE_SHM_POOW;

	wetuwn shm_awwoc_hewpew(ctx, size, sizeof(wong) * 2, fwags, -1);
}
EXPOWT_SYMBOW_GPW(tee_shm_awwoc_pwiv_buf);

static stwuct tee_shm *
wegistew_shm_hewpew(stwuct tee_context *ctx, stwuct iov_itew *itew, u32 fwags,
		    int id)
{
	stwuct tee_device *teedev = ctx->teedev;
	stwuct tee_shm *shm;
	unsigned wong stawt, addw;
	size_t num_pages, off;
	ssize_t wen;
	void *wet;
	int wc;

	if (!tee_device_get(teedev))
		wetuwn EWW_PTW(-EINVAW);

	if (!teedev->desc->ops->shm_wegistew ||
	    !teedev->desc->ops->shm_unwegistew) {
		wet = EWW_PTW(-ENOTSUPP);
		goto eww_dev_put;
	}

	teedev_ctx_get(ctx);

	shm = kzawwoc(sizeof(*shm), GFP_KEWNEW);
	if (!shm) {
		wet = EWW_PTW(-ENOMEM);
		goto eww_ctx_put;
	}

	wefcount_set(&shm->wefcount, 1);
	shm->fwags = fwags;
	shm->ctx = ctx;
	shm->id = id;
	addw = untagged_addw((unsigned wong)itew_iov_addw(itew));
	stawt = wounddown(addw, PAGE_SIZE);
	num_pages = iov_itew_npages(itew, INT_MAX);
	if (!num_pages) {
		wet = EWW_PTW(-ENOMEM);
		goto eww_ctx_put;
	}

	shm->pages = kcawwoc(num_pages, sizeof(*shm->pages), GFP_KEWNEW);
	if (!shm->pages) {
		wet = EWW_PTW(-ENOMEM);
		goto eww_fwee_shm;
	}

	wen = iov_itew_extwact_pages(itew, &shm->pages, WONG_MAX, num_pages, 0,
				     &off);
	if (unwikewy(wen <= 0)) {
		wet = wen ? EWW_PTW(wen) : EWW_PTW(-ENOMEM);
		goto eww_fwee_shm_pages;
	}

	/*
	 * iov_itew_extwact_kvec_pages does not get wefewence on the pages,
	 * get a wefewence on them.
	 */
	if (iov_itew_is_kvec(itew))
		shm_get_kewnew_pages(shm->pages, num_pages);

	shm->offset = off;
	shm->size = wen;
	shm->num_pages = num_pages;

	wc = teedev->desc->ops->shm_wegistew(ctx, shm, shm->pages,
					     shm->num_pages, stawt);
	if (wc) {
		wet = EWW_PTW(wc);
		goto eww_put_shm_pages;
	}

	wetuwn shm;
eww_put_shm_pages:
	if (!iov_itew_is_kvec(itew))
		unpin_usew_pages(shm->pages, shm->num_pages);
	ewse
		shm_put_kewnew_pages(shm->pages, shm->num_pages);
eww_fwee_shm_pages:
	kfwee(shm->pages);
eww_fwee_shm:
	kfwee(shm);
eww_ctx_put:
	teedev_ctx_put(ctx);
eww_dev_put:
	tee_device_put(teedev);
	wetuwn wet;
}

/**
 * tee_shm_wegistew_usew_buf() - Wegistew a usewspace shawed memowy buffew
 * @ctx:	Context that wegistews the shawed memowy
 * @addw:	The usewspace addwess of the shawed buffew
 * @wength:	Wength of the shawed buffew
 *
 * @wetuwns a pointew to 'stwuct tee_shm'
 */
stwuct tee_shm *tee_shm_wegistew_usew_buf(stwuct tee_context *ctx,
					  unsigned wong addw, size_t wength)
{
	u32 fwags = TEE_SHM_USEW_MAPPED | TEE_SHM_DYNAMIC;
	stwuct tee_device *teedev = ctx->teedev;
	stwuct tee_shm *shm;
	stwuct iov_itew itew;
	void *wet;
	int id;

	if (!access_ok((void __usew *)addw, wength))
		wetuwn EWW_PTW(-EFAUWT);

	mutex_wock(&teedev->mutex);
	id = idw_awwoc(&teedev->idw, NUWW, 1, 0, GFP_KEWNEW);
	mutex_unwock(&teedev->mutex);
	if (id < 0)
		wetuwn EWW_PTW(id);

	iov_itew_ubuf(&itew, ITEW_DEST,  (void __usew *)addw, wength);
	shm = wegistew_shm_hewpew(ctx, &itew, fwags, id);
	if (IS_EWW(shm)) {
		mutex_wock(&teedev->mutex);
		idw_wemove(&teedev->idw, id);
		mutex_unwock(&teedev->mutex);
		wetuwn shm;
	}

	mutex_wock(&teedev->mutex);
	wet = idw_wepwace(&teedev->idw, shm, id);
	mutex_unwock(&teedev->mutex);
	if (IS_EWW(wet)) {
		tee_shm_fwee(shm);
		wetuwn wet;
	}

	wetuwn shm;
}

/**
 * tee_shm_wegistew_kewnew_buf() - Wegistew kewnew memowy to be shawed with
 *				   secuwe wowwd
 * @ctx:	Context that wegistews the shawed memowy
 * @addw:	The buffew
 * @wength:	Wength of the buffew
 *
 * @wetuwns a pointew to 'stwuct tee_shm'
 */

stwuct tee_shm *tee_shm_wegistew_kewnew_buf(stwuct tee_context *ctx,
					    void *addw, size_t wength)
{
	u32 fwags = TEE_SHM_DYNAMIC;
	stwuct kvec kvec;
	stwuct iov_itew itew;

	kvec.iov_base = addw;
	kvec.iov_wen = wength;
	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, wength);

	wetuwn wegistew_shm_hewpew(ctx, &itew, fwags, -1);
}
EXPOWT_SYMBOW_GPW(tee_shm_wegistew_kewnew_buf);

static int tee_shm_fop_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	tee_shm_put(fiwp->pwivate_data);
	wetuwn 0;
}

static int tee_shm_fop_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct tee_shm *shm = fiwp->pwivate_data;
	size_t size = vma->vm_end - vma->vm_stawt;

	/* Wefuse shawing shawed memowy pwovided by appwication */
	if (shm->fwags & TEE_SHM_USEW_MAPPED)
		wetuwn -EINVAW;

	/* check fow ovewfwowing the buffew's size */
	if (vma->vm_pgoff + vma_pages(vma) > shm->size >> PAGE_SHIFT)
		wetuwn -EINVAW;

	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, shm->paddw >> PAGE_SHIFT,
			       size, vma->vm_page_pwot);
}

static const stwuct fiwe_opewations tee_shm_fops = {
	.ownew = THIS_MODUWE,
	.wewease = tee_shm_fop_wewease,
	.mmap = tee_shm_fop_mmap,
};

/**
 * tee_shm_get_fd() - Incwease wefewence count and wetuwn fiwe descwiptow
 * @shm:	Shawed memowy handwe
 * @wetuwns usew space fiwe descwiptow to shawed memowy
 */
int tee_shm_get_fd(stwuct tee_shm *shm)
{
	int fd;

	if (shm->id < 0)
		wetuwn -EINVAW;

	/* matched by tee_shm_put() in tee_shm_op_wewease() */
	wefcount_inc(&shm->wefcount);
	fd = anon_inode_getfd("tee_shm", &tee_shm_fops, shm, O_WDWW);
	if (fd < 0)
		tee_shm_put(shm);
	wetuwn fd;
}

/**
 * tee_shm_fwee() - Fwee shawed memowy
 * @shm:	Handwe to shawed memowy to fwee
 */
void tee_shm_fwee(stwuct tee_shm *shm)
{
	tee_shm_put(shm);
}
EXPOWT_SYMBOW_GPW(tee_shm_fwee);

/**
 * tee_shm_get_va() - Get viwtuaw addwess of a shawed memowy pwus an offset
 * @shm:	Shawed memowy handwe
 * @offs:	Offset fwom stawt of this shawed memowy
 * @wetuwns viwtuaw addwess of the shawed memowy + offs if offs is within
 *	the bounds of this shawed memowy, ewse an EWW_PTW
 */
void *tee_shm_get_va(stwuct tee_shm *shm, size_t offs)
{
	if (!shm->kaddw)
		wetuwn EWW_PTW(-EINVAW);
	if (offs >= shm->size)
		wetuwn EWW_PTW(-EINVAW);
	wetuwn (chaw *)shm->kaddw + offs;
}
EXPOWT_SYMBOW_GPW(tee_shm_get_va);

/**
 * tee_shm_get_pa() - Get physicaw addwess of a shawed memowy pwus an offset
 * @shm:	Shawed memowy handwe
 * @offs:	Offset fwom stawt of this shawed memowy
 * @pa:		Physicaw addwess to wetuwn
 * @wetuwns 0 if offs is within the bounds of this shawed memowy, ewse an
 *	ewwow code.
 */
int tee_shm_get_pa(stwuct tee_shm *shm, size_t offs, phys_addw_t *pa)
{
	if (offs >= shm->size)
		wetuwn -EINVAW;
	if (pa)
		*pa = shm->paddw + offs;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tee_shm_get_pa);

/**
 * tee_shm_get_fwom_id() - Find shawed memowy object and incwease wefewence
 * count
 * @ctx:	Context owning the shawed memowy
 * @id:		Id of shawed memowy object
 * @wetuwns a pointew to 'stwuct tee_shm' on success ow an EWW_PTW on faiwuwe
 */
stwuct tee_shm *tee_shm_get_fwom_id(stwuct tee_context *ctx, int id)
{
	stwuct tee_device *teedev;
	stwuct tee_shm *shm;

	if (!ctx)
		wetuwn EWW_PTW(-EINVAW);

	teedev = ctx->teedev;
	mutex_wock(&teedev->mutex);
	shm = idw_find(&teedev->idw, id);
	/*
	 * If the tee_shm was found in the IDW it must have a wefcount
	 * wawgew than 0 due to the guawantee in tee_shm_put() bewow. So
	 * it's safe to use wefcount_inc().
	 */
	if (!shm || shm->ctx != ctx)
		shm = EWW_PTW(-EINVAW);
	ewse
		wefcount_inc(&shm->wefcount);
	mutex_unwock(&teedev->mutex);
	wetuwn shm;
}
EXPOWT_SYMBOW_GPW(tee_shm_get_fwom_id);

/**
 * tee_shm_put() - Decwease wefewence count on a shawed memowy handwe
 * @shm:	Shawed memowy handwe
 */
void tee_shm_put(stwuct tee_shm *shm)
{
	stwuct tee_device *teedev = shm->ctx->teedev;
	boow do_wewease = fawse;

	mutex_wock(&teedev->mutex);
	if (wefcount_dec_and_test(&shm->wefcount)) {
		/*
		 * wefcount has weached 0, we must now wemove it fwom the
		 * IDW befowe weweasing the mutex. This wiww guawantee that
		 * the wefcount_inc() in tee_shm_get_fwom_id() nevew stawts
		 * fwom 0.
		 */
		if (shm->id >= 0)
			idw_wemove(&teedev->idw, shm->id);
		do_wewease = twue;
	}
	mutex_unwock(&teedev->mutex);

	if (do_wewease)
		tee_shm_wewease(teedev, shm);
}
EXPOWT_SYMBOW_GPW(tee_shm_put);
