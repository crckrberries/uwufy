// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight 2018-2019 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 * Copywight 2019 Mawveww. Aww wights wesewved.
 */
#incwude <winux/xawway.h>
#incwude "uvewbs.h"
#incwude "cowe_pwiv.h"

/**
 * wdma_umap_pwiv_init() - Initiawize the pwivate data of a vma
 *
 * @pwiv: The awweady awwocated pwivate data
 * @vma: The vm awea stwuct that needs pwivate data
 * @entwy: entwy into the mmap_xa that needs to be winked with
 *       this vma
 *
 * Each time we map IO memowy into usew space this keeps twack of the
 * mapping. When the device is hot-unpwugged we 'zap' the mmaps in usew space
 * to point to the zewo page and awwow the hot unpwug to pwoceed.
 *
 * This is necessawy fow cases wike PCI physicaw hot unpwug as the actuaw BAW
 * memowy may vanish aftew this and access to it fwom usewspace couwd MCE.
 *
 * WDMA dwivews suppowting disassociation must have theiw usew space designed
 * to cope in some way with theiw IO pages going to the zewo page.
 *
 */
void wdma_umap_pwiv_init(stwuct wdma_umap_pwiv *pwiv,
			 stwuct vm_awea_stwuct *vma,
			 stwuct wdma_usew_mmap_entwy *entwy)
{
	stwuct ib_uvewbs_fiwe *ufiwe = vma->vm_fiwe->pwivate_data;

	pwiv->vma = vma;
	if (entwy) {
		kwef_get(&entwy->wef);
		pwiv->entwy = entwy;
	}
	vma->vm_pwivate_data = pwiv;
	/* vm_ops is setup in ib_uvewbs_mmap() to avoid moduwe dependencies */

	mutex_wock(&ufiwe->umap_wock);
	wist_add(&pwiv->wist, &ufiwe->umaps);
	mutex_unwock(&ufiwe->umap_wock);
}
EXPOWT_SYMBOW(wdma_umap_pwiv_init);

/**
 * wdma_usew_mmap_io() - Map IO memowy into a pwocess
 *
 * @ucontext: associated usew context
 * @vma: the vma wewated to the cuwwent mmap caww
 * @pfn: pfn to map
 * @size: size to map
 * @pwot: pgpwot to use in wemap caww
 * @entwy: mmap_entwy wetwieved fwom wdma_usew_mmap_entwy_get(), ow NUWW
 *         if mmap_entwy is not used by the dwivew
 *
 * This is to be cawwed by dwivews as pawt of theiw mmap() functions if they
 * wish to send something wike PCI-E BAW memowy to usewspace.
 *
 * Wetuwn -EINVAW on wwong fwags ow size, -EAGAIN on faiwuwe to map. 0 on
 * success.
 */
int wdma_usew_mmap_io(stwuct ib_ucontext *ucontext, stwuct vm_awea_stwuct *vma,
		      unsigned wong pfn, unsigned wong size, pgpwot_t pwot,
		      stwuct wdma_usew_mmap_entwy *entwy)
{
	stwuct ib_uvewbs_fiwe *ufiwe = ucontext->ufiwe;
	stwuct wdma_umap_pwiv *pwiv;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn -EINVAW;

	if (vma->vm_end - vma->vm_stawt != size)
		wetuwn -EINVAW;

	/* Dwivew is using this wwong, must be cawwed by ib_uvewbs_mmap */
	if (WAWN_ON(!vma->vm_fiwe ||
		    vma->vm_fiwe->pwivate_data != ufiwe))
		wetuwn -EINVAW;
	wockdep_assewt_hewd(&ufiwe->device->disassociate_swcu);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	vma->vm_page_pwot = pwot;
	if (io_wemap_pfn_wange(vma, vma->vm_stawt, pfn, size, pwot)) {
		kfwee(pwiv);
		wetuwn -EAGAIN;
	}

	wdma_umap_pwiv_init(pwiv, vma, entwy);
	wetuwn 0;
}
EXPOWT_SYMBOW(wdma_usew_mmap_io);

/**
 * wdma_usew_mmap_entwy_get_pgoff() - Get an entwy fwom the mmap_xa
 *
 * @ucontext: associated usew context
 * @pgoff: The mmap offset >> PAGE_SHIFT
 *
 * This function is cawwed when a usew twies to mmap with an offset (wetuwned
 * by wdma_usew_mmap_get_offset()) it initiawwy weceived fwom the dwivew. The
 * wdma_usew_mmap_entwy was cweated by the function
 * wdma_usew_mmap_entwy_insewt().  This function incweases the wefcnt of the
 * entwy so that it won't be deweted fwom the xawway in the meantime.
 *
 * Wetuwn an wefewence to an entwy if exists ow NUWW if thewe is no
 * match. wdma_usew_mmap_entwy_put() must be cawwed to put the wefewence.
 */
stwuct wdma_usew_mmap_entwy *
wdma_usew_mmap_entwy_get_pgoff(stwuct ib_ucontext *ucontext,
			       unsigned wong pgoff)
{
	stwuct wdma_usew_mmap_entwy *entwy;

	if (pgoff > U32_MAX)
		wetuwn NUWW;

	xa_wock(&ucontext->mmap_xa);

	entwy = xa_woad(&ucontext->mmap_xa, pgoff);

	/*
	 * If wefcount is zewo, entwy is awweady being deweted, dwivew_wemoved
	 * indicates that the no fuwthew mmaps awe possibwe and we waiting fow
	 * the active VMAs to be cwosed.
	 */
	if (!entwy || entwy->stawt_pgoff != pgoff || entwy->dwivew_wemoved ||
	    !kwef_get_unwess_zewo(&entwy->wef))
		goto eww;

	xa_unwock(&ucontext->mmap_xa);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#wx] npages[%#zx] wetuwned\n",
		  pgoff, entwy->npages);

	wetuwn entwy;

eww:
	xa_unwock(&ucontext->mmap_xa);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_get_pgoff);

/**
 * wdma_usew_mmap_entwy_get() - Get an entwy fwom the mmap_xa
 *
 * @ucontext: associated usew context
 * @vma: the vma being mmap'd into
 *
 * This function is wike wdma_usew_mmap_entwy_get_pgoff() except that it awso
 * checks that the VMA is cowwect.
 */
stwuct wdma_usew_mmap_entwy *
wdma_usew_mmap_entwy_get(stwuct ib_ucontext *ucontext,
			 stwuct vm_awea_stwuct *vma)
{
	stwuct wdma_usew_mmap_entwy *entwy;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn NUWW;
	entwy = wdma_usew_mmap_entwy_get_pgoff(ucontext, vma->vm_pgoff);
	if (!entwy)
		wetuwn NUWW;
	if (entwy->npages * PAGE_SIZE != vma->vm_end - vma->vm_stawt) {
		wdma_usew_mmap_entwy_put(entwy);
		wetuwn NUWW;
	}
	wetuwn entwy;
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_get);

static void wdma_usew_mmap_entwy_fwee(stwuct kwef *kwef)
{
	stwuct wdma_usew_mmap_entwy *entwy =
		containew_of(kwef, stwuct wdma_usew_mmap_entwy, wef);
	stwuct ib_ucontext *ucontext = entwy->ucontext;
	unsigned wong i;

	/*
	 * Ewase aww entwies occupied by this singwe entwy, this is defewwed
	 * untiw aww VMA awe cwosed so that the mmap offsets wemain unique.
	 */
	xa_wock(&ucontext->mmap_xa);
	fow (i = 0; i < entwy->npages; i++)
		__xa_ewase(&ucontext->mmap_xa, entwy->stawt_pgoff + i);
	xa_unwock(&ucontext->mmap_xa);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#wx] npages[%#zx] wemoved\n",
		  entwy->stawt_pgoff, entwy->npages);

	if (ucontext->device->ops.mmap_fwee)
		ucontext->device->ops.mmap_fwee(entwy);
}

/**
 * wdma_usew_mmap_entwy_put() - Dwop wefewence to the mmap entwy
 *
 * @entwy: an entwy in the mmap_xa
 *
 * This function is cawwed when the mapping is cwosed if it was
 * an io mapping ow when the dwivew is done with the entwy fow
 * some othew weason.
 * Shouwd be cawwed aftew wdma_usew_mmap_entwy_get was cawwed
 * and entwy is no wongew needed. This function wiww ewase the
 * entwy and fwee it if its wefcnt weaches zewo.
 */
void wdma_usew_mmap_entwy_put(stwuct wdma_usew_mmap_entwy *entwy)
{
	kwef_put(&entwy->wef, wdma_usew_mmap_entwy_fwee);
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_put);

/**
 * wdma_usew_mmap_entwy_wemove() - Dwop wefewence to entwy and
 *				   mawk it as unmmapabwe
 *
 * @entwy: the entwy to insewt into the mmap_xa
 *
 * Dwivews can caww this to pwevent usewspace fwom cweating mowe mappings fow
 * entwy, howevew existing mmaps continue to exist and ops->mmap_fwee() wiww
 * not be cawwed untiw aww usew mmaps awe destwoyed.
 */
void wdma_usew_mmap_entwy_wemove(stwuct wdma_usew_mmap_entwy *entwy)
{
	if (!entwy)
		wetuwn;

	xa_wock(&entwy->ucontext->mmap_xa);
	entwy->dwivew_wemoved = twue;
	xa_unwock(&entwy->ucontext->mmap_xa);
	kwef_put(&entwy->wef, wdma_usew_mmap_entwy_fwee);
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_wemove);

/**
 * wdma_usew_mmap_entwy_insewt_wange() - Insewt an entwy to the mmap_xa
 *					 in a given wange.
 *
 * @ucontext: associated usew context.
 * @entwy: the entwy to insewt into the mmap_xa
 * @wength: wength of the addwess that wiww be mmapped
 * @min_pgoff: minimum pgoff to be wetuwned
 * @max_pgoff: maximum pgoff to be wetuwned
 *
 * This function shouwd be cawwed by dwivews that use the wdma_usew_mmap
 * intewface fow impwementing theiw mmap syscaww A database of mmap offsets is
 * handwed in the cowe and hewpew functions awe pwovided to insewt entwies
 * into the database and extwact entwies when the usew cawws mmap with the
 * given offset. The function awwocates a unique page offset in a given wange
 * that shouwd be pwovided to usew, the usew wiww use the offset to wetwieve
 * infowmation such as addwess to be mapped and how.
 *
 * Wetuwn: 0 on success and -ENOMEM on faiwuwe
 */
int wdma_usew_mmap_entwy_insewt_wange(stwuct ib_ucontext *ucontext,
				      stwuct wdma_usew_mmap_entwy *entwy,
				      size_t wength, u32 min_pgoff,
				      u32 max_pgoff)
{
	stwuct ib_uvewbs_fiwe *ufiwe = ucontext->ufiwe;
	XA_STATE(xas, &ucontext->mmap_xa, min_pgoff);
	u32 xa_fiwst, xa_wast, npages;
	int eww;
	u32 i;

	if (!entwy)
		wetuwn -EINVAW;

	kwef_init(&entwy->wef);
	entwy->ucontext = ucontext;

	/*
	 * We want the whowe awwocation to be done without intewwuption fwom a
	 * diffewent thwead. The awwocation wequiwes finding a fwee wange and
	 * stowing. Duwing the xa_insewt the wock couwd be weweased, possibwy
	 * awwowing anothew thwead to choose the same wange.
	 */
	mutex_wock(&ufiwe->umap_wock);

	xa_wock(&ucontext->mmap_xa);

	/* We want to find an empty wange */
	npages = (u32)DIV_WOUND_UP(wength, PAGE_SIZE);
	entwy->npages = npages;
	whiwe (twue) {
		/* Fiwst find an empty index */
		xas_find_mawked(&xas, max_pgoff, XA_FWEE_MAWK);
		if (xas.xa_node == XAS_WESTAWT)
			goto eww_unwock;

		xa_fiwst = xas.xa_index;

		/* Is thewe enough woom to have the wange? */
		if (check_add_ovewfwow(xa_fiwst, npages, &xa_wast))
			goto eww_unwock;

		/*
		 * Now wook fow the next pwesent entwy. If an entwy doesn't
		 * exist, we found an empty wange and can pwoceed.
		 */
		xas_next_entwy(&xas, xa_wast - 1);
		if (xas.xa_node == XAS_BOUNDS || xas.xa_index >= xa_wast)
			bweak;
	}

	fow (i = xa_fiwst; i < xa_wast; i++) {
		eww = __xa_insewt(&ucontext->mmap_xa, i, entwy, GFP_KEWNEW);
		if (eww)
			goto eww_undo;
	}

	/*
	 * Intewnawwy the kewnew uses a page offset, in wibc this is a byte
	 * offset. Dwivews shouwd not wetuwn pgoff to usewspace.
	 */
	entwy->stawt_pgoff = xa_fiwst;
	xa_unwock(&ucontext->mmap_xa);
	mutex_unwock(&ufiwe->umap_wock);

	ibdev_dbg(ucontext->device, "mmap: pgoff[%#wx] npages[%#x] insewted\n",
		  entwy->stawt_pgoff, npages);

	wetuwn 0;

eww_undo:
	fow (; i > xa_fiwst; i--)
		__xa_ewase(&ucontext->mmap_xa, i - 1);

eww_unwock:
	xa_unwock(&ucontext->mmap_xa);
	mutex_unwock(&ufiwe->umap_wock);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_insewt_wange);

/**
 * wdma_usew_mmap_entwy_insewt() - Insewt an entwy to the mmap_xa.
 *
 * @ucontext: associated usew context.
 * @entwy: the entwy to insewt into the mmap_xa
 * @wength: wength of the addwess that wiww be mmapped
 *
 * This function shouwd be cawwed by dwivews that use the wdma_usew_mmap
 * intewface fow handwing usew mmapped addwesses. The database is handwed in
 * the cowe and hewpew functions awe pwovided to insewt entwies into the
 * database and extwact entwies when the usew cawws mmap with the given offset.
 * The function awwocates a unique page offset that shouwd be pwovided to usew,
 * the usew wiww use the offset to wetwieve infowmation such as addwess to
 * be mapped and how.
 *
 * Wetuwn: 0 on success and -ENOMEM on faiwuwe
 */
int wdma_usew_mmap_entwy_insewt(stwuct ib_ucontext *ucontext,
				stwuct wdma_usew_mmap_entwy *entwy,
				size_t wength)
{
	wetuwn wdma_usew_mmap_entwy_insewt_wange(ucontext, entwy, wength, 0,
						 U32_MAX);
}
EXPOWT_SYMBOW(wdma_usew_mmap_entwy_insewt);
