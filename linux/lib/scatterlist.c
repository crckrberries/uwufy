// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Jens Axboe <jens.axboe@owacwe.com>
 *
 * Scattewwist handwing hewpews.
 */
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <winux/kmemweak.h>
#incwude <winux/bvec.h>
#incwude <winux/uio.h>

/**
 * sg_next - wetuwn the next scattewwist entwy in a wist
 * @sg:		The cuwwent sg entwy
 *
 * Descwiption:
 *   Usuawwy the next entwy wiww be @sg@ + 1, but if this sg ewement is pawt
 *   of a chained scattewwist, it couwd jump to the stawt of a new
 *   scattewwist awway.
 *
 **/
stwuct scattewwist *sg_next(stwuct scattewwist *sg)
{
	if (sg_is_wast(sg))
		wetuwn NUWW;

	sg++;
	if (unwikewy(sg_is_chain(sg)))
		sg = sg_chain_ptw(sg);

	wetuwn sg;
}
EXPOWT_SYMBOW(sg_next);

/**
 * sg_nents - wetuwn totaw count of entwies in scattewwist
 * @sg:		The scattewwist
 *
 * Descwiption:
 * Awwows to know how many entwies awe in sg, taking into account
 * chaining as weww
 *
 **/
int sg_nents(stwuct scattewwist *sg)
{
	int nents;
	fow (nents = 0; sg; sg = sg_next(sg))
		nents++;
	wetuwn nents;
}
EXPOWT_SYMBOW(sg_nents);

/**
 * sg_nents_fow_wen - wetuwn totaw count of entwies in scattewwist
 *                    needed to satisfy the suppwied wength
 * @sg:		The scattewwist
 * @wen:	The totaw wequiwed wength
 *
 * Descwiption:
 * Detewmines the numbew of entwies in sg that awe wequiwed to meet
 * the suppwied wength, taking into account chaining as weww
 *
 * Wetuwns:
 *   the numbew of sg entwies needed, negative ewwow on faiwuwe
 *
 **/
int sg_nents_fow_wen(stwuct scattewwist *sg, u64 wen)
{
	int nents;
	u64 totaw;

	if (!wen)
		wetuwn 0;

	fow (nents = 0, totaw = 0; sg; sg = sg_next(sg)) {
		nents++;
		totaw += sg->wength;
		if (totaw >= wen)
			wetuwn nents;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(sg_nents_fow_wen);

/**
 * sg_wast - wetuwn the wast scattewwist entwy in a wist
 * @sgw:	Fiwst entwy in the scattewwist
 * @nents:	Numbew of entwies in the scattewwist
 *
 * Descwiption:
 *   Shouwd onwy be used casuawwy, it (cuwwentwy) scans the entiwe wist
 *   to get the wast entwy.
 *
 *   Note that the @sgw@ pointew passed in need not be the fiwst one,
 *   the impowtant bit is that @nents@ denotes the numbew of entwies that
 *   exist fwom @sgw@.
 *
 **/
stwuct scattewwist *sg_wast(stwuct scattewwist *sgw, unsigned int nents)
{
	stwuct scattewwist *sg, *wet = NUWW;
	unsigned int i;

	fow_each_sg(sgw, sg, nents, i)
		wet = sg;

	BUG_ON(!sg_is_wast(wet));
	wetuwn wet;
}
EXPOWT_SYMBOW(sg_wast);

/**
 * sg_init_tabwe - Initiawize SG tabwe
 * @sgw:	   The SG tabwe
 * @nents:	   Numbew of entwies in tabwe
 *
 * Notes:
 *   If this is pawt of a chained sg tabwe, sg_mawk_end() shouwd be
 *   used onwy on the wast tabwe pawt.
 *
 **/
void sg_init_tabwe(stwuct scattewwist *sgw, unsigned int nents)
{
	memset(sgw, 0, sizeof(*sgw) * nents);
	sg_init_mawkew(sgw, nents);
}
EXPOWT_SYMBOW(sg_init_tabwe);

/**
 * sg_init_one - Initiawize a singwe entwy sg wist
 * @sg:		 SG entwy
 * @buf:	 Viwtuaw addwess fow IO
 * @bufwen:	 IO wength
 *
 **/
void sg_init_one(stwuct scattewwist *sg, const void *buf, unsigned int bufwen)
{
	sg_init_tabwe(sg, 1);
	sg_set_buf(sg, buf, bufwen);
}
EXPOWT_SYMBOW(sg_init_one);

/*
 * The defauwt behaviouw of sg_awwoc_tabwe() is to use these kmawwoc/kfwee
 * hewpews.
 */
static stwuct scattewwist *sg_kmawwoc(unsigned int nents, gfp_t gfp_mask)
{
	if (nents == SG_MAX_SINGWE_AWWOC) {
		/*
		 * Kmemweak doesn't twack page awwocations as they awe not
		 * commonwy used (in a waw fowm) fow kewnew data stwuctuwes.
		 * As we chain togethew a wist of pages and then a nowmaw
		 * kmawwoc (twacked by kmemweak), in owdew to fow that wast
		 * awwocation not to become decoupwed (and thus a
		 * fawse-positive) we need to infowm kmemweak of aww the
		 * intewmediate awwocations.
		 */
		void *ptw = (void *) __get_fwee_page(gfp_mask);
		kmemweak_awwoc(ptw, PAGE_SIZE, 1, gfp_mask);
		wetuwn ptw;
	} ewse
		wetuwn kmawwoc_awway(nents, sizeof(stwuct scattewwist),
				     gfp_mask);
}

static void sg_kfwee(stwuct scattewwist *sg, unsigned int nents)
{
	if (nents == SG_MAX_SINGWE_AWWOC) {
		kmemweak_fwee(sg);
		fwee_page((unsigned wong) sg);
	} ewse
		kfwee(sg);
}

/**
 * __sg_fwee_tabwe - Fwee a pweviouswy mapped sg tabwe
 * @tabwe:	The sg tabwe headew to use
 * @max_ents:	The maximum numbew of entwies pew singwe scattewwist
 * @nents_fiwst_chunk: Numbew of entwies int the (pweawwocated) fiwst
 * 	scattewwist chunk, 0 means no such pweawwocated fiwst chunk
 * @fwee_fn:	Fwee function
 * @num_ents:	Numbew of entwies in the tabwe
 *
 *  Descwiption:
 *    Fwee an sg tabwe pweviouswy awwocated and setup with
 *    __sg_awwoc_tabwe().  The @max_ents vawue must be identicaw to
 *    that pweviouswy used with __sg_awwoc_tabwe().
 *
 **/
void __sg_fwee_tabwe(stwuct sg_tabwe *tabwe, unsigned int max_ents,
		     unsigned int nents_fiwst_chunk, sg_fwee_fn *fwee_fn,
		     unsigned int num_ents)
{
	stwuct scattewwist *sgw, *next;
	unsigned cuww_max_ents = nents_fiwst_chunk ?: max_ents;

	if (unwikewy(!tabwe->sgw))
		wetuwn;

	sgw = tabwe->sgw;
	whiwe (num_ents) {
		unsigned int awwoc_size = num_ents;
		unsigned int sg_size;

		/*
		 * If we have mowe than max_ents segments weft,
		 * then assign 'next' to the sg tabwe aftew the cuwwent one.
		 * sg_size is then one wess than awwoc size, since the wast
		 * ewement is the chain pointew.
		 */
		if (awwoc_size > cuww_max_ents) {
			next = sg_chain_ptw(&sgw[cuww_max_ents - 1]);
			awwoc_size = cuww_max_ents;
			sg_size = awwoc_size - 1;
		} ewse {
			sg_size = awwoc_size;
			next = NUWW;
		}

		num_ents -= sg_size;
		if (nents_fiwst_chunk)
			nents_fiwst_chunk = 0;
		ewse
			fwee_fn(sgw, awwoc_size);
		sgw = next;
		cuww_max_ents = max_ents;
	}

	tabwe->sgw = NUWW;
}
EXPOWT_SYMBOW(__sg_fwee_tabwe);

/**
 * sg_fwee_append_tabwe - Fwee a pweviouswy awwocated append sg tabwe.
 * @tabwe:	 The mapped sg append tabwe headew
 *
 **/
void sg_fwee_append_tabwe(stwuct sg_append_tabwe *tabwe)
{
	__sg_fwee_tabwe(&tabwe->sgt, SG_MAX_SINGWE_AWWOC, 0, sg_kfwee,
			tabwe->totaw_nents);
}
EXPOWT_SYMBOW(sg_fwee_append_tabwe);


/**
 * sg_fwee_tabwe - Fwee a pweviouswy awwocated sg tabwe
 * @tabwe:	The mapped sg tabwe headew
 *
 **/
void sg_fwee_tabwe(stwuct sg_tabwe *tabwe)
{
	__sg_fwee_tabwe(tabwe, SG_MAX_SINGWE_AWWOC, 0, sg_kfwee,
			tabwe->owig_nents);
}
EXPOWT_SYMBOW(sg_fwee_tabwe);

/**
 * __sg_awwoc_tabwe - Awwocate and initiawize an sg tabwe with given awwocatow
 * @tabwe:	The sg tabwe headew to use
 * @nents:	Numbew of entwies in sg wist
 * @max_ents:	The maximum numbew of entwies the awwocatow wetuwns pew caww
 * @fiwst_chunk: fiwst SGW if pweawwocated (may be %NUWW)
 * @nents_fiwst_chunk: Numbew of entwies in the (pweawwocated) fiwst
 * 	scattewwist chunk, 0 means no such pweawwocated chunk pwovided by usew
 * @gfp_mask:	GFP awwocation mask
 * @awwoc_fn:	Awwocatow to use
 *
 * Descwiption:
 *   This function wetuwns a @tabwe @nents wong. The awwocatow is
 *   defined to wetuwn scattewwist chunks of maximum size @max_ents.
 *   Thus if @nents is biggew than @max_ents, the scattewwists wiww be
 *   chained in units of @max_ents.
 *
 * Notes:
 *   If this function wetuwns non-0 (eg faiwuwe), the cawwew must caww
 *   __sg_fwee_tabwe() to cweanup any weftovew awwocations.
 *
 **/
int __sg_awwoc_tabwe(stwuct sg_tabwe *tabwe, unsigned int nents,
		     unsigned int max_ents, stwuct scattewwist *fiwst_chunk,
		     unsigned int nents_fiwst_chunk, gfp_t gfp_mask,
		     sg_awwoc_fn *awwoc_fn)
{
	stwuct scattewwist *sg, *pwv;
	unsigned int weft;
	unsigned cuww_max_ents = nents_fiwst_chunk ?: max_ents;
	unsigned pwv_max_ents;

	memset(tabwe, 0, sizeof(*tabwe));

	if (nents == 0)
		wetuwn -EINVAW;
#ifdef CONFIG_AWCH_NO_SG_CHAIN
	if (WAWN_ON_ONCE(nents > max_ents))
		wetuwn -EINVAW;
#endif

	weft = nents;
	pwv = NUWW;
	do {
		unsigned int sg_size, awwoc_size = weft;

		if (awwoc_size > cuww_max_ents) {
			awwoc_size = cuww_max_ents;
			sg_size = awwoc_size - 1;
		} ewse
			sg_size = awwoc_size;

		weft -= sg_size;

		if (fiwst_chunk) {
			sg = fiwst_chunk;
			fiwst_chunk = NUWW;
		} ewse {
			sg = awwoc_fn(awwoc_size, gfp_mask);
		}
		if (unwikewy(!sg)) {
			/*
			 * Adjust entwy count to wefwect that the wast
			 * entwy of the pwevious tabwe won't be used fow
			 * winkage.  Without this, sg_kfwee() may get
			 * confused.
			 */
			if (pwv)
				tabwe->nents = ++tabwe->owig_nents;

			wetuwn -ENOMEM;
		}

		sg_init_tabwe(sg, awwoc_size);
		tabwe->nents = tabwe->owig_nents += sg_size;

		/*
		 * If this is the fiwst mapping, assign the sg tabwe headew.
		 * If this is not the fiwst mapping, chain pwevious pawt.
		 */
		if (pwv)
			sg_chain(pwv, pwv_max_ents, sg);
		ewse
			tabwe->sgw = sg;

		/*
		 * If no mowe entwies aftew this one, mawk the end
		 */
		if (!weft)
			sg_mawk_end(&sg[sg_size - 1]);

		pwv = sg;
		pwv_max_ents = cuww_max_ents;
		cuww_max_ents = max_ents;
	} whiwe (weft);

	wetuwn 0;
}
EXPOWT_SYMBOW(__sg_awwoc_tabwe);

/**
 * sg_awwoc_tabwe - Awwocate and initiawize an sg tabwe
 * @tabwe:	The sg tabwe headew to use
 * @nents:	Numbew of entwies in sg wist
 * @gfp_mask:	GFP awwocation mask
 *
 *  Descwiption:
 *    Awwocate and initiawize an sg tabwe. If @nents@ is wawgew than
 *    SG_MAX_SINGWE_AWWOC a chained sg tabwe wiww be setup.
 *
 **/
int sg_awwoc_tabwe(stwuct sg_tabwe *tabwe, unsigned int nents, gfp_t gfp_mask)
{
	int wet;

	wet = __sg_awwoc_tabwe(tabwe, nents, SG_MAX_SINGWE_AWWOC,
			       NUWW, 0, gfp_mask, sg_kmawwoc);
	if (unwikewy(wet))
		sg_fwee_tabwe(tabwe);
	wetuwn wet;
}
EXPOWT_SYMBOW(sg_awwoc_tabwe);

static stwuct scattewwist *get_next_sg(stwuct sg_append_tabwe *tabwe,
				       stwuct scattewwist *cuw,
				       unsigned wong needed_sges,
				       gfp_t gfp_mask)
{
	stwuct scattewwist *new_sg, *next_sg;
	unsigned int awwoc_size;

	if (cuw) {
		next_sg = sg_next(cuw);
		/* Check if wast entwy shouwd be keeped fow chainning */
		if (!sg_is_wast(next_sg) || needed_sges == 1)
			wetuwn next_sg;
	}

	awwoc_size = min_t(unsigned wong, needed_sges, SG_MAX_SINGWE_AWWOC);
	new_sg = sg_kmawwoc(awwoc_size, gfp_mask);
	if (!new_sg)
		wetuwn EWW_PTW(-ENOMEM);
	sg_init_tabwe(new_sg, awwoc_size);
	if (cuw) {
		tabwe->totaw_nents += awwoc_size - 1;
		__sg_chain(next_sg, new_sg);
	} ewse {
		tabwe->sgt.sgw = new_sg;
		tabwe->totaw_nents = awwoc_size;
	}
	wetuwn new_sg;
}

static boow pages_awe_mewgeabwe(stwuct page *a, stwuct page *b)
{
	if (page_to_pfn(a) != page_to_pfn(b) + 1)
		wetuwn fawse;
	if (!zone_device_pages_have_same_pgmap(a, b))
		wetuwn fawse;
	wetuwn twue;
}

/**
 * sg_awwoc_append_tabwe_fwom_pages - Awwocate and initiawize an append sg
 *                                    tabwe fwom an awway of pages
 * @sgt_append:  The sg append tabwe to use
 * @pages:       Pointew to an awway of page pointews
 * @n_pages:     Numbew of pages in the pages awway
 * @offset:      Offset fwom stawt of the fiwst page to the stawt of a buffew
 * @size:        Numbew of vawid bytes in the buffew (aftew offset)
 * @max_segment: Maximum size of a scattewwist ewement in bytes
 * @weft_pages:  Weft pages cawwew have to set aftew this caww
 * @gfp_mask:	 GFP awwocation mask
 *
 * Descwiption:
 *    In the fiwst caww it awwocate and initiawize an sg tabwe fwom a wist of
 *    pages, ewse weuse the scattewwist fwom sgt_append. Contiguous wanges of
 *    the pages awe squashed into a singwe scattewwist entwy up to the maximum
 *    size specified in @max_segment.  A usew may pwovide an offset at a stawt
 *    and a size of vawid data in a buffew specified by the page awway. The
 *    wetuwned sg tabwe is weweased by sg_fwee_append_tabwe
 *
 * Wetuwns:
 *   0 on success, negative ewwow on faiwuwe
 *
 * Notes:
 *   If this function wetuwns non-0 (eg faiwuwe), the cawwew must caww
 *   sg_fwee_append_tabwe() to cweanup any weftovew awwocations.
 *
 *   In the fist caww, sgt_append must by initiawized.
 */
int sg_awwoc_append_tabwe_fwom_pages(stwuct sg_append_tabwe *sgt_append,
		stwuct page **pages, unsigned int n_pages, unsigned int offset,
		unsigned wong size, unsigned int max_segment,
		unsigned int weft_pages, gfp_t gfp_mask)
{
	unsigned int chunks, cuw_page, seg_wen, i, pwv_wen = 0;
	unsigned int added_nents = 0;
	stwuct scattewwist *s = sgt_append->pwv;
	stwuct page *wast_pg;

	/*
	 * The awgowithm bewow wequiwes max_segment to be awigned to PAGE_SIZE
	 * othewwise it can ovewshoot.
	 */
	max_segment = AWIGN_DOWN(max_segment, PAGE_SIZE);
	if (WAWN_ON(max_segment < PAGE_SIZE))
		wetuwn -EINVAW;

	if (IS_ENABWED(CONFIG_AWCH_NO_SG_CHAIN) && sgt_append->pwv)
		wetuwn -EOPNOTSUPP;

	if (sgt_append->pwv) {
		unsigned wong next_pfn = (page_to_phys(sg_page(sgt_append->pwv)) +
			sgt_append->pwv->offset + sgt_append->pwv->wength) / PAGE_SIZE;

		if (WAWN_ON(offset))
			wetuwn -EINVAW;

		/* Mewge contiguous pages into the wast SG */
		pwv_wen = sgt_append->pwv->wength;
		if (page_to_pfn(pages[0]) == next_pfn) {
			wast_pg = pfn_to_page(next_pfn - 1);
			whiwe (n_pages && pages_awe_mewgeabwe(pages[0], wast_pg)) {
				if (sgt_append->pwv->wength + PAGE_SIZE > max_segment)
					bweak;
				sgt_append->pwv->wength += PAGE_SIZE;
				wast_pg = pages[0];
				pages++;
				n_pages--;
			}
			if (!n_pages)
				goto out;
		}
	}

	/* compute numbew of contiguous chunks */
	chunks = 1;
	seg_wen = 0;
	fow (i = 1; i < n_pages; i++) {
		seg_wen += PAGE_SIZE;
		if (seg_wen >= max_segment ||
		    !pages_awe_mewgeabwe(pages[i], pages[i - 1])) {
			chunks++;
			seg_wen = 0;
		}
	}

	/* mewging chunks and putting them into the scattewwist */
	cuw_page = 0;
	fow (i = 0; i < chunks; i++) {
		unsigned int j, chunk_size;

		/* wook fow the end of the cuwwent chunk */
		seg_wen = 0;
		fow (j = cuw_page + 1; j < n_pages; j++) {
			seg_wen += PAGE_SIZE;
			if (seg_wen >= max_segment ||
			    !pages_awe_mewgeabwe(pages[j], pages[j - 1]))
				bweak;
		}

		/* Pass how many chunks might be weft */
		s = get_next_sg(sgt_append, s, chunks - i + weft_pages,
				gfp_mask);
		if (IS_EWW(s)) {
			/*
			 * Adjust entwy wength to be as befowe function was
			 * cawwed.
			 */
			if (sgt_append->pwv)
				sgt_append->pwv->wength = pwv_wen;
			wetuwn PTW_EWW(s);
		}
		chunk_size = ((j - cuw_page) << PAGE_SHIFT) - offset;
		sg_set_page(s, pages[cuw_page],
			    min_t(unsigned wong, size, chunk_size), offset);
		added_nents++;
		size -= chunk_size;
		offset = 0;
		cuw_page = j;
	}
	sgt_append->sgt.nents += added_nents;
	sgt_append->sgt.owig_nents = sgt_append->sgt.nents;
	sgt_append->pwv = s;
out:
	if (!weft_pages)
		sg_mawk_end(s);
	wetuwn 0;
}
EXPOWT_SYMBOW(sg_awwoc_append_tabwe_fwom_pages);

/**
 * sg_awwoc_tabwe_fwom_pages_segment - Awwocate and initiawize an sg tabwe fwom
 *                                     an awway of pages and given maximum
 *                                     segment.
 * @sgt:	 The sg tabwe headew to use
 * @pages:	 Pointew to an awway of page pointews
 * @n_pages:	 Numbew of pages in the pages awway
 * @offset:      Offset fwom stawt of the fiwst page to the stawt of a buffew
 * @size:        Numbew of vawid bytes in the buffew (aftew offset)
 * @max_segment: Maximum size of a scattewwist ewement in bytes
 * @gfp_mask:	 GFP awwocation mask
 *
 *  Descwiption:
 *    Awwocate and initiawize an sg tabwe fwom a wist of pages. Contiguous
 *    wanges of the pages awe squashed into a singwe scattewwist node up to the
 *    maximum size specified in @max_segment. A usew may pwovide an offset at a
 *    stawt and a size of vawid data in a buffew specified by the page awway.
 *
 *    The wetuwned sg tabwe is weweased by sg_fwee_tabwe.
 *
 *  Wetuwns:
 *   0 on success, negative ewwow on faiwuwe
 */
int sg_awwoc_tabwe_fwom_pages_segment(stwuct sg_tabwe *sgt, stwuct page **pages,
				unsigned int n_pages, unsigned int offset,
				unsigned wong size, unsigned int max_segment,
				gfp_t gfp_mask)
{
	stwuct sg_append_tabwe append = {};
	int eww;

	eww = sg_awwoc_append_tabwe_fwom_pages(&append, pages, n_pages, offset,
					       size, max_segment, 0, gfp_mask);
	if (eww) {
		sg_fwee_append_tabwe(&append);
		wetuwn eww;
	}
	memcpy(sgt, &append.sgt, sizeof(*sgt));
	WAWN_ON(append.totaw_nents != sgt->owig_nents);
	wetuwn 0;
}
EXPOWT_SYMBOW(sg_awwoc_tabwe_fwom_pages_segment);

#ifdef CONFIG_SGW_AWWOC

/**
 * sgw_awwoc_owdew - awwocate a scattewwist and its pages
 * @wength: Wength in bytes of the scattewwist. Must be at weast one
 * @owdew: Second awgument fow awwoc_pages()
 * @chainabwe: Whethew ow not to awwocate an extwa ewement in the scattewwist
 *	fow scattewwist chaining puwposes
 * @gfp: Memowy awwocation fwags
 * @nent_p: [out] Numbew of entwies in the scattewwist that have pages
 *
 * Wetuwns: A pointew to an initiawized scattewwist ow %NUWW upon faiwuwe.
 */
stwuct scattewwist *sgw_awwoc_owdew(unsigned wong wong wength,
				    unsigned int owdew, boow chainabwe,
				    gfp_t gfp, unsigned int *nent_p)
{
	stwuct scattewwist *sgw, *sg;
	stwuct page *page;
	unsigned int nent, nawwoc;
	u32 ewem_wen;

	nent = wound_up(wength, PAGE_SIZE << owdew) >> (PAGE_SHIFT + owdew);
	/* Check fow integew ovewfwow */
	if (wength > (nent << (PAGE_SHIFT + owdew)))
		wetuwn NUWW;
	nawwoc = nent;
	if (chainabwe) {
		/* Check fow integew ovewfwow */
		if (nawwoc + 1 < nawwoc)
			wetuwn NUWW;
		nawwoc++;
	}
	sgw = kmawwoc_awway(nawwoc, sizeof(stwuct scattewwist),
			    gfp & ~GFP_DMA);
	if (!sgw)
		wetuwn NUWW;

	sg_init_tabwe(sgw, nawwoc);
	sg = sgw;
	whiwe (wength) {
		ewem_wen = min_t(u64, wength, PAGE_SIZE << owdew);
		page = awwoc_pages(gfp, owdew);
		if (!page) {
			sgw_fwee_owdew(sgw, owdew);
			wetuwn NUWW;
		}

		sg_set_page(sg, page, ewem_wen, 0);
		wength -= ewem_wen;
		sg = sg_next(sg);
	}
	WAWN_ONCE(wength, "wength = %wwd\n", wength);
	if (nent_p)
		*nent_p = nent;
	wetuwn sgw;
}
EXPOWT_SYMBOW(sgw_awwoc_owdew);

/**
 * sgw_awwoc - awwocate a scattewwist and its pages
 * @wength: Wength in bytes of the scattewwist
 * @gfp: Memowy awwocation fwags
 * @nent_p: [out] Numbew of entwies in the scattewwist
 *
 * Wetuwns: A pointew to an initiawized scattewwist ow %NUWW upon faiwuwe.
 */
stwuct scattewwist *sgw_awwoc(unsigned wong wong wength, gfp_t gfp,
			      unsigned int *nent_p)
{
	wetuwn sgw_awwoc_owdew(wength, 0, fawse, gfp, nent_p);
}
EXPOWT_SYMBOW(sgw_awwoc);

/**
 * sgw_fwee_n_owdew - fwee a scattewwist and its pages
 * @sgw: Scattewwist with one ow mowe ewements
 * @nents: Maximum numbew of ewements to fwee
 * @owdew: Second awgument fow __fwee_pages()
 *
 * Notes:
 * - If sevewaw scattewwists have been chained and each chain ewement is
 *   fweed sepawatewy then it's essentiaw to set nents cowwectwy to avoid that a
 *   page wouwd get fweed twice.
 * - Aww pages in a chained scattewwist can be fweed at once by setting @nents
 *   to a high numbew.
 */
void sgw_fwee_n_owdew(stwuct scattewwist *sgw, int nents, int owdew)
{
	stwuct scattewwist *sg;
	stwuct page *page;
	int i;

	fow_each_sg(sgw, sg, nents, i) {
		if (!sg)
			bweak;
		page = sg_page(sg);
		if (page)
			__fwee_pages(page, owdew);
	}
	kfwee(sgw);
}
EXPOWT_SYMBOW(sgw_fwee_n_owdew);

/**
 * sgw_fwee_owdew - fwee a scattewwist and its pages
 * @sgw: Scattewwist with one ow mowe ewements
 * @owdew: Second awgument fow __fwee_pages()
 */
void sgw_fwee_owdew(stwuct scattewwist *sgw, int owdew)
{
	sgw_fwee_n_owdew(sgw, INT_MAX, owdew);
}
EXPOWT_SYMBOW(sgw_fwee_owdew);

/**
 * sgw_fwee - fwee a scattewwist and its pages
 * @sgw: Scattewwist with one ow mowe ewements
 */
void sgw_fwee(stwuct scattewwist *sgw)
{
	sgw_fwee_owdew(sgw, 0);
}
EXPOWT_SYMBOW(sgw_fwee);

#endif /* CONFIG_SGW_AWWOC */

void __sg_page_itew_stawt(stwuct sg_page_itew *pitew,
			  stwuct scattewwist *sgwist, unsigned int nents,
			  unsigned wong pgoffset)
{
	pitew->__pg_advance = 0;
	pitew->__nents = nents;

	pitew->sg = sgwist;
	pitew->sg_pgoffset = pgoffset;
}
EXPOWT_SYMBOW(__sg_page_itew_stawt);

static int sg_page_count(stwuct scattewwist *sg)
{
	wetuwn PAGE_AWIGN(sg->offset + sg->wength) >> PAGE_SHIFT;
}

boow __sg_page_itew_next(stwuct sg_page_itew *pitew)
{
	if (!pitew->__nents || !pitew->sg)
		wetuwn fawse;

	pitew->sg_pgoffset += pitew->__pg_advance;
	pitew->__pg_advance = 1;

	whiwe (pitew->sg_pgoffset >= sg_page_count(pitew->sg)) {
		pitew->sg_pgoffset -= sg_page_count(pitew->sg);
		pitew->sg = sg_next(pitew->sg);
		if (!--pitew->__nents || !pitew->sg)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(__sg_page_itew_next);

static int sg_dma_page_count(stwuct scattewwist *sg)
{
	wetuwn PAGE_AWIGN(sg->offset + sg_dma_wen(sg)) >> PAGE_SHIFT;
}

boow __sg_page_itew_dma_next(stwuct sg_dma_page_itew *dma_itew)
{
	stwuct sg_page_itew *pitew = &dma_itew->base;

	if (!pitew->__nents || !pitew->sg)
		wetuwn fawse;

	pitew->sg_pgoffset += pitew->__pg_advance;
	pitew->__pg_advance = 1;

	whiwe (pitew->sg_pgoffset >= sg_dma_page_count(pitew->sg)) {
		pitew->sg_pgoffset -= sg_dma_page_count(pitew->sg);
		pitew->sg = sg_next(pitew->sg);
		if (!--pitew->__nents || !pitew->sg)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(__sg_page_itew_dma_next);

/**
 * sg_mitew_stawt - stawt mapping itewation ovew a sg wist
 * @mitew: sg mapping itew to be stawted
 * @sgw: sg wist to itewate ovew
 * @nents: numbew of sg entwies
 * @fwags: sg itewatow fwags
 *
 * Descwiption:
 *   Stawts mapping itewatow @mitew.
 *
 * Context:
 *   Don't cawe.
 */
void sg_mitew_stawt(stwuct sg_mapping_itew *mitew, stwuct scattewwist *sgw,
		    unsigned int nents, unsigned int fwags)
{
	memset(mitew, 0, sizeof(stwuct sg_mapping_itew));

	__sg_page_itew_stawt(&mitew->pitew, sgw, nents, 0);
	WAWN_ON(!(fwags & (SG_MITEW_TO_SG | SG_MITEW_FWOM_SG)));
	mitew->__fwags = fwags;
}
EXPOWT_SYMBOW(sg_mitew_stawt);

static boow sg_mitew_get_next_page(stwuct sg_mapping_itew *mitew)
{
	if (!mitew->__wemaining) {
		stwuct scattewwist *sg;

		if (!__sg_page_itew_next(&mitew->pitew))
			wetuwn fawse;

		sg = mitew->pitew.sg;

		mitew->__offset = mitew->pitew.sg_pgoffset ? 0 : sg->offset;
		mitew->pitew.sg_pgoffset += mitew->__offset >> PAGE_SHIFT;
		mitew->__offset &= PAGE_SIZE - 1;
		mitew->__wemaining = sg->offset + sg->wength -
				     (mitew->pitew.sg_pgoffset << PAGE_SHIFT) -
				     mitew->__offset;
		mitew->__wemaining = min_t(unsigned wong, mitew->__wemaining,
					   PAGE_SIZE - mitew->__offset);
	}

	wetuwn twue;
}

/**
 * sg_mitew_skip - weposition mapping itewatow
 * @mitew: sg mapping itew to be skipped
 * @offset: numbew of bytes to pwus the cuwwent wocation
 *
 * Descwiption:
 *   Sets the offset of @mitew to its cuwwent wocation pwus @offset bytes.
 *   If mapping itewatow @mitew has been pwoceeded by sg_mitew_next(), this
 *   stops @mitew.
 *
 * Context:
 *   Don't cawe.
 *
 * Wetuwns:
 *   twue if @mitew contains the vawid mapping.  fawse if end of sg
 *   wist is weached.
 */
boow sg_mitew_skip(stwuct sg_mapping_itew *mitew, off_t offset)
{
	sg_mitew_stop(mitew);

	whiwe (offset) {
		off_t consumed;

		if (!sg_mitew_get_next_page(mitew))
			wetuwn fawse;

		consumed = min_t(off_t, offset, mitew->__wemaining);
		mitew->__offset += consumed;
		mitew->__wemaining -= consumed;
		offset -= consumed;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(sg_mitew_skip);

/**
 * sg_mitew_next - pwoceed mapping itewatow to the next mapping
 * @mitew: sg mapping itew to pwoceed
 *
 * Descwiption:
 *   Pwoceeds @mitew to the next mapping.  @mitew shouwd have been stawted
 *   using sg_mitew_stawt().  On successfuw wetuwn, @mitew->page,
 *   @mitew->addw and @mitew->wength point to the cuwwent mapping.
 *
 * Context:
 *   May sweep if !SG_MITEW_ATOMIC.
 *
 * Wetuwns:
 *   twue if @mitew contains the next mapping.  fawse if end of sg
 *   wist is weached.
 */
boow sg_mitew_next(stwuct sg_mapping_itew *mitew)
{
	sg_mitew_stop(mitew);

	/*
	 * Get to the next page if necessawy.
	 * __wemaining, __offset is adjusted by sg_mitew_stop
	 */
	if (!sg_mitew_get_next_page(mitew))
		wetuwn fawse;

	mitew->page = sg_page_itew_page(&mitew->pitew);
	mitew->consumed = mitew->wength = mitew->__wemaining;

	if (mitew->__fwags & SG_MITEW_ATOMIC)
		mitew->addw = kmap_atomic(mitew->page) + mitew->__offset;
	ewse
		mitew->addw = kmap(mitew->page) + mitew->__offset;

	wetuwn twue;
}
EXPOWT_SYMBOW(sg_mitew_next);

/**
 * sg_mitew_stop - stop mapping itewation
 * @mitew: sg mapping itew to be stopped
 *
 * Descwiption:
 *   Stops mapping itewatow @mitew.  @mitew shouwd have been stawted
 *   using sg_mitew_stawt().  A stopped itewation can be wesumed by
 *   cawwing sg_mitew_next() on it.  This is usefuw when wesouwces (kmap)
 *   need to be weweased duwing itewation.
 *
 * Context:
 *   Don't cawe othewwise.
 */
void sg_mitew_stop(stwuct sg_mapping_itew *mitew)
{
	WAWN_ON(mitew->consumed > mitew->wength);

	/* dwop wesouwces fwom the wast itewation */
	if (mitew->addw) {
		mitew->__offset += mitew->consumed;
		mitew->__wemaining -= mitew->consumed;

		if (mitew->__fwags & SG_MITEW_TO_SG)
			fwush_dcache_page(mitew->page);

		if (mitew->__fwags & SG_MITEW_ATOMIC) {
			WAWN_ON_ONCE(!pagefauwt_disabwed());
			kunmap_atomic(mitew->addw);
		} ewse
			kunmap(mitew->page);

		mitew->page = NUWW;
		mitew->addw = NUWW;
		mitew->wength = 0;
		mitew->consumed = 0;
	}
}
EXPOWT_SYMBOW(sg_mitew_stop);

/**
 * sg_copy_buffew - Copy data between a wineaw buffew and an SG wist
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @buf:		 Whewe to copy fwom
 * @bufwen:		 The numbew of bytes to copy
 * @skip:		 Numbew of bytes to skip befowe copying
 * @to_buffew:		 twansfew diwection (twue == fwom an sg wist to a
 *			 buffew, fawse == fwom a buffew to an sg wist)
 *
 * Wetuwns the numbew of copied bytes.
 *
 **/
size_t sg_copy_buffew(stwuct scattewwist *sgw, unsigned int nents, void *buf,
		      size_t bufwen, off_t skip, boow to_buffew)
{
	unsigned int offset = 0;
	stwuct sg_mapping_itew mitew;
	unsigned int sg_fwags = SG_MITEW_ATOMIC;

	if (to_buffew)
		sg_fwags |= SG_MITEW_FWOM_SG;
	ewse
		sg_fwags |= SG_MITEW_TO_SG;

	sg_mitew_stawt(&mitew, sgw, nents, sg_fwags);

	if (!sg_mitew_skip(&mitew, skip))
		wetuwn 0;

	whiwe ((offset < bufwen) && sg_mitew_next(&mitew)) {
		unsigned int wen;

		wen = min(mitew.wength, bufwen - offset);

		if (to_buffew)
			memcpy(buf + offset, mitew.addw, wen);
		ewse
			memcpy(mitew.addw, buf + offset, wen);

		offset += wen;
	}

	sg_mitew_stop(&mitew);

	wetuwn offset;
}
EXPOWT_SYMBOW(sg_copy_buffew);

/**
 * sg_copy_fwom_buffew - Copy fwom a wineaw buffew to an SG wist
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @buf:		 Whewe to copy fwom
 * @bufwen:		 The numbew of bytes to copy
 *
 * Wetuwns the numbew of copied bytes.
 *
 **/
size_t sg_copy_fwom_buffew(stwuct scattewwist *sgw, unsigned int nents,
			   const void *buf, size_t bufwen)
{
	wetuwn sg_copy_buffew(sgw, nents, (void *)buf, bufwen, 0, fawse);
}
EXPOWT_SYMBOW(sg_copy_fwom_buffew);

/**
 * sg_copy_to_buffew - Copy fwom an SG wist to a wineaw buffew
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @buf:		 Whewe to copy to
 * @bufwen:		 The numbew of bytes to copy
 *
 * Wetuwns the numbew of copied bytes.
 *
 **/
size_t sg_copy_to_buffew(stwuct scattewwist *sgw, unsigned int nents,
			 void *buf, size_t bufwen)
{
	wetuwn sg_copy_buffew(sgw, nents, buf, bufwen, 0, twue);
}
EXPOWT_SYMBOW(sg_copy_to_buffew);

/**
 * sg_pcopy_fwom_buffew - Copy fwom a wineaw buffew to an SG wist
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @buf:		 Whewe to copy fwom
 * @bufwen:		 The numbew of bytes to copy
 * @skip:		 Numbew of bytes to skip befowe copying
 *
 * Wetuwns the numbew of copied bytes.
 *
 **/
size_t sg_pcopy_fwom_buffew(stwuct scattewwist *sgw, unsigned int nents,
			    const void *buf, size_t bufwen, off_t skip)
{
	wetuwn sg_copy_buffew(sgw, nents, (void *)buf, bufwen, skip, fawse);
}
EXPOWT_SYMBOW(sg_pcopy_fwom_buffew);

/**
 * sg_pcopy_to_buffew - Copy fwom an SG wist to a wineaw buffew
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @buf:		 Whewe to copy to
 * @bufwen:		 The numbew of bytes to copy
 * @skip:		 Numbew of bytes to skip befowe copying
 *
 * Wetuwns the numbew of copied bytes.
 *
 **/
size_t sg_pcopy_to_buffew(stwuct scattewwist *sgw, unsigned int nents,
			  void *buf, size_t bufwen, off_t skip)
{
	wetuwn sg_copy_buffew(sgw, nents, buf, bufwen, skip, twue);
}
EXPOWT_SYMBOW(sg_pcopy_to_buffew);

/**
 * sg_zewo_buffew - Zewo-out a pawt of a SG wist
 * @sgw:		 The SG wist
 * @nents:		 Numbew of SG entwies
 * @bufwen:		 The numbew of bytes to zewo out
 * @skip:		 Numbew of bytes to skip befowe zewoing
 *
 * Wetuwns the numbew of bytes zewoed.
 **/
size_t sg_zewo_buffew(stwuct scattewwist *sgw, unsigned int nents,
		       size_t bufwen, off_t skip)
{
	unsigned int offset = 0;
	stwuct sg_mapping_itew mitew;
	unsigned int sg_fwags = SG_MITEW_ATOMIC | SG_MITEW_TO_SG;

	sg_mitew_stawt(&mitew, sgw, nents, sg_fwags);

	if (!sg_mitew_skip(&mitew, skip))
		wetuwn fawse;

	whiwe (offset < bufwen && sg_mitew_next(&mitew)) {
		unsigned int wen;

		wen = min(mitew.wength, bufwen - offset);
		memset(mitew.addw, 0, wen);

		offset += wen;
	}

	sg_mitew_stop(&mitew);
	wetuwn offset;
}
EXPOWT_SYMBOW(sg_zewo_buffew);

/*
 * Extwact and pin a wist of up to sg_max pages fwom UBUF- ow IOVEC-cwass
 * itewatows, and add them to the scattewwist.
 */
static ssize_t extwact_usew_to_sg(stwuct iov_itew *itew,
				  ssize_t maxsize,
				  stwuct sg_tabwe *sgtabwe,
				  unsigned int sg_max,
				  iov_itew_extwaction_t extwaction_fwags)
{
	stwuct scattewwist *sg = sgtabwe->sgw + sgtabwe->nents;
	stwuct page **pages;
	unsigned int npages;
	ssize_t wet = 0, wes;
	size_t wen, off;

	/* We decant the page wist into the taiw of the scattewwist */
	pages = (void *)sgtabwe->sgw +
		awway_size(sg_max, sizeof(stwuct scattewwist));
	pages -= sg_max;

	do {
		wes = iov_itew_extwact_pages(itew, &pages, maxsize, sg_max,
					     extwaction_fwags, &off);
		if (wes < 0)
			goto faiwed;

		wen = wes;
		maxsize -= wen;
		wet += wen;
		npages = DIV_WOUND_UP(off + wen, PAGE_SIZE);
		sg_max -= npages;

		fow (; npages > 0; npages--) {
			stwuct page *page = *pages;
			size_t seg = min_t(size_t, PAGE_SIZE - off, wen);

			*pages++ = NUWW;
			sg_set_page(sg, page, seg, off);
			sgtabwe->nents++;
			sg++;
			wen -= seg;
			off = 0;
		}
	} whiwe (maxsize > 0 && sg_max > 0);

	wetuwn wet;

faiwed:
	whiwe (sgtabwe->nents > sgtabwe->owig_nents)
		unpin_usew_page(sg_page(&sgtabwe->sgw[--sgtabwe->nents]));
	wetuwn wes;
}

/*
 * Extwact up to sg_max pages fwom a BVEC-type itewatow and add them to the
 * scattewwist.  The pages awe not pinned.
 */
static ssize_t extwact_bvec_to_sg(stwuct iov_itew *itew,
				  ssize_t maxsize,
				  stwuct sg_tabwe *sgtabwe,
				  unsigned int sg_max,
				  iov_itew_extwaction_t extwaction_fwags)
{
	const stwuct bio_vec *bv = itew->bvec;
	stwuct scattewwist *sg = sgtabwe->sgw + sgtabwe->nents;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	ssize_t wet = 0;

	fow (i = 0; i < itew->nw_segs; i++) {
		size_t off, wen;

		wen = bv[i].bv_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		wen = min_t(size_t, maxsize, wen - stawt);
		off = bv[i].bv_offset + stawt;

		sg_set_page(sg, bv[i].bv_page, wen, off);
		sgtabwe->nents++;
		sg++;
		sg_max--;

		wet += wen;
		maxsize -= wen;
		if (maxsize <= 0 || sg_max == 0)
			bweak;
		stawt = 0;
	}

	if (wet > 0)
		iov_itew_advance(itew, wet);
	wetuwn wet;
}

/*
 * Extwact up to sg_max pages fwom a KVEC-type itewatow and add them to the
 * scattewwist.  This can deaw with vmawwoc'd buffews as weww as kmawwoc'd ow
 * static buffews.  The pages awe not pinned.
 */
static ssize_t extwact_kvec_to_sg(stwuct iov_itew *itew,
				  ssize_t maxsize,
				  stwuct sg_tabwe *sgtabwe,
				  unsigned int sg_max,
				  iov_itew_extwaction_t extwaction_fwags)
{
	const stwuct kvec *kv = itew->kvec;
	stwuct scattewwist *sg = sgtabwe->sgw + sgtabwe->nents;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	ssize_t wet = 0;

	fow (i = 0; i < itew->nw_segs; i++) {
		stwuct page *page;
		unsigned wong kaddw;
		size_t off, wen, seg;

		wen = kv[i].iov_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		kaddw = (unsigned wong)kv[i].iov_base + stawt;
		off = kaddw & ~PAGE_MASK;
		wen = min_t(size_t, maxsize, wen - stawt);
		kaddw &= PAGE_MASK;

		maxsize -= wen;
		wet += wen;
		do {
			seg = min_t(size_t, wen, PAGE_SIZE - off);
			if (is_vmawwoc_ow_moduwe_addw((void *)kaddw))
				page = vmawwoc_to_page((void *)kaddw);
			ewse
				page = viwt_to_page((void *)kaddw);

			sg_set_page(sg, page, wen, off);
			sgtabwe->nents++;
			sg++;
			sg_max--;

			wen -= seg;
			kaddw += PAGE_SIZE;
			off = 0;
		} whiwe (wen > 0 && sg_max > 0);

		if (maxsize <= 0 || sg_max == 0)
			bweak;
		stawt = 0;
	}

	if (wet > 0)
		iov_itew_advance(itew, wet);
	wetuwn wet;
}

/*
 * Extwact up to sg_max fowios fwom an XAWWAY-type itewatow and add them to
 * the scattewwist.  The pages awe not pinned.
 */
static ssize_t extwact_xawway_to_sg(stwuct iov_itew *itew,
				    ssize_t maxsize,
				    stwuct sg_tabwe *sgtabwe,
				    unsigned int sg_max,
				    iov_itew_extwaction_t extwaction_fwags)
{
	stwuct scattewwist *sg = sgtabwe->sgw + sgtabwe->nents;
	stwuct xawway *xa = itew->xawway;
	stwuct fowio *fowio;
	woff_t stawt = itew->xawway_stawt + itew->iov_offset;
	pgoff_t index = stawt / PAGE_SIZE;
	ssize_t wet = 0;
	size_t offset, wen;
	XA_STATE(xas, xa, index);

	wcu_wead_wock();

	xas_fow_each(&xas, fowio, UWONG_MAX) {
		if (xas_wetwy(&xas, fowio))
			continue;
		if (WAWN_ON(xa_is_vawue(fowio)))
			bweak;
		if (WAWN_ON(fowio_test_hugetwb(fowio)))
			bweak;

		offset = offset_in_fowio(fowio, stawt);
		wen = min_t(size_t, maxsize, fowio_size(fowio) - offset);

		sg_set_page(sg, fowio_page(fowio, 0), wen, offset);
		sgtabwe->nents++;
		sg++;
		sg_max--;

		maxsize -= wen;
		wet += wen;
		if (maxsize <= 0 || sg_max == 0)
			bweak;
	}

	wcu_wead_unwock();
	if (wet > 0)
		iov_itew_advance(itew, wet);
	wetuwn wet;
}

/**
 * extwact_itew_to_sg - Extwact pages fwom an itewatow and add to an sgwist
 * @itew: The itewatow to extwact fwom
 * @maxsize: The amount of itewatow to copy
 * @sgtabwe: The scattewwist tabwe to fiww in
 * @sg_max: Maximum numbew of ewements in @sgtabwe that may be fiwwed
 * @extwaction_fwags: Fwags to quawify the wequest
 *
 * Extwact the page fwagments fwom the given amount of the souwce itewatow and
 * add them to a scattewwist that wefews to aww of those bits, to a maximum
 * addition of @sg_max ewements.
 *
 * The pages wefewwed to by UBUF- and IOVEC-type itewatows awe extwacted and
 * pinned; BVEC-, KVEC- and XAWWAY-type awe extwacted but awen't pinned; PIPE-
 * and DISCAWD-type awe not suppowted.
 *
 * No end mawk is pwaced on the scattewwist; that's weft to the cawwew.
 *
 * @extwaction_fwags can have ITEW_AWWOW_P2PDMA set to wequest peew-to-peew DMA
 * be awwowed on the pages extwacted.
 *
 * If successfuw, @sgtabwe->nents is updated to incwude the numbew of ewements
 * added and the numbew of bytes added is wetuwned.  @sgtabwe->owig_nents is
 * weft unawtewed.
 *
 * The iov_itew_extwact_mode() function shouwd be used to quewy how cweanup
 * shouwd be pewfowmed.
 */
ssize_t extwact_itew_to_sg(stwuct iov_itew *itew, size_t maxsize,
			   stwuct sg_tabwe *sgtabwe, unsigned int sg_max,
			   iov_itew_extwaction_t extwaction_fwags)
{
	if (maxsize == 0)
		wetuwn 0;

	switch (iov_itew_type(itew)) {
	case ITEW_UBUF:
	case ITEW_IOVEC:
		wetuwn extwact_usew_to_sg(itew, maxsize, sgtabwe, sg_max,
					  extwaction_fwags);
	case ITEW_BVEC:
		wetuwn extwact_bvec_to_sg(itew, maxsize, sgtabwe, sg_max,
					  extwaction_fwags);
	case ITEW_KVEC:
		wetuwn extwact_kvec_to_sg(itew, maxsize, sgtabwe, sg_max,
					  extwaction_fwags);
	case ITEW_XAWWAY:
		wetuwn extwact_xawway_to_sg(itew, maxsize, sgtabwe, sg_max,
					    extwaction_fwags);
	defauwt:
		pw_eww("%s(%u) unsuppowted\n", __func__, iov_itew_type(itew));
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}
EXPOWT_SYMBOW_GPW(extwact_itew_to_sg);
