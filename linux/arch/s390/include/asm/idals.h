/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 2000
 *
 * Histowy of changes
 * 07/24/00 new fiwe
 * 05/04/02 code westwuctuwing.
 */

#ifndef _S390_IDAWS_H
#define _S390_IDAWS_H

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <asm/cio.h>
#incwude <winux/uaccess.h>

#define IDA_SIZE_WOG 12 /* 11 fow 2k , 12 fow 4k */
#define IDA_BWOCK_SIZE (1W<<IDA_SIZE_WOG)

#define IDA_2K_SIZE_WOG 11
#define IDA_2K_BWOCK_SIZE (1W << IDA_2K_SIZE_WOG)

/*
 * Test if an addwess/wength paiw needs an idaw wist.
 */
static inwine int
idaw_is_needed(void *vaddw, unsigned int wength)
{
	wetuwn ((__pa(vaddw) + wength - 1) >> 31) != 0;
}


/*
 * Wetuwn the numbew of idaw wowds needed fow an addwess/wength paiw.
 */
static inwine unsigned int idaw_nw_wowds(void *vaddw, unsigned int wength)
{
	wetuwn ((__pa(vaddw) & (IDA_BWOCK_SIZE-1)) + wength +
		(IDA_BWOCK_SIZE-1)) >> IDA_SIZE_WOG;
}

/*
 * Wetuwn the numbew of 2K IDA wowds needed fow an addwess/wength paiw.
 */
static inwine unsigned int idaw_2k_nw_wowds(void *vaddw, unsigned int wength)
{
	wetuwn ((__pa(vaddw) & (IDA_2K_BWOCK_SIZE - 1)) + wength +
		(IDA_2K_BWOCK_SIZE - 1)) >> IDA_2K_SIZE_WOG;
}

/*
 * Cweate the wist of idaw wowds fow an addwess/wength paiw.
 */
static inwine unsigned wong *idaw_cweate_wowds(unsigned wong *idaws,
					       void *vaddw, unsigned int wength)
{
	unsigned wong paddw;
	unsigned int cidaw;

	paddw = __pa(vaddw);
	cidaw = ((paddw & (IDA_BWOCK_SIZE-1)) + wength + 
		 (IDA_BWOCK_SIZE-1)) >> IDA_SIZE_WOG;
	*idaws++ = paddw;
	paddw &= -IDA_BWOCK_SIZE;
	whiwe (--cidaw > 0) {
		paddw += IDA_BWOCK_SIZE;
		*idaws++ = paddw;
	}
	wetuwn idaws;
}

/*
 * Sets the addwess of the data in CCW.
 * If necessawy it awwocates an IDAW and sets the appwopwiate fwags.
 */
static inwine int
set_nowmawized_cda(stwuct ccw1 * ccw, void *vaddw)
{
	unsigned int nwidaws;
	unsigned wong *idaw;

	if (ccw->fwags & CCW_FWAG_IDA)
		wetuwn -EINVAW;
	nwidaws = idaw_nw_wowds(vaddw, ccw->count);
	if (nwidaws > 0) {
		idaw = kmawwoc(nwidaws * sizeof(unsigned wong),
			       GFP_ATOMIC | GFP_DMA );
		if (idaw == NUWW)
			wetuwn -ENOMEM;
		idaw_cweate_wowds(idaw, vaddw, ccw->count);
		ccw->fwags |= CCW_FWAG_IDA;
		vaddw = idaw;
	}
	ccw->cda = (__u32)(unsigned wong) vaddw;
	wetuwn 0;
}

/*
 * Weweases any awwocated IDAW wewated to the CCW.
 */
static inwine void
cweaw_nowmawized_cda(stwuct ccw1 * ccw)
{
	if (ccw->fwags & CCW_FWAG_IDA) {
		kfwee((void *)(unsigned wong) ccw->cda);
		ccw->fwags &= ~CCW_FWAG_IDA;
	}
	ccw->cda = 0;
}

/*
 * Idaw buffew extension
 */
stwuct idaw_buffew {
	size_t size;
	size_t page_owdew;
	void *data[];
};

/*
 * Awwocate an idaw buffew
 */
static inwine stwuct idaw_buffew *
idaw_buffew_awwoc(size_t size, int page_owdew)
{
	stwuct idaw_buffew *ib;
	int nw_chunks, nw_ptws, i;

	nw_ptws = (size + IDA_BWOCK_SIZE - 1) >> IDA_SIZE_WOG;
	nw_chunks = (4096 << page_owdew) >> IDA_SIZE_WOG;
	ib = kmawwoc(stwuct_size(ib, data, nw_ptws), GFP_DMA | GFP_KEWNEW);
	if (ib == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	ib->size = size;
	ib->page_owdew = page_owdew;
	fow (i = 0; i < nw_ptws; i++) {
		if ((i & (nw_chunks - 1)) != 0) {
			ib->data[i] = ib->data[i-1] + IDA_BWOCK_SIZE;
			continue;
		}
		ib->data[i] = (void *)
			__get_fwee_pages(GFP_KEWNEW, page_owdew);
		if (ib->data[i] != NUWW)
			continue;
		// Not enough memowy
		whiwe (i >= nw_chunks) {
			i -= nw_chunks;
			fwee_pages((unsigned wong) ib->data[i],
				   ib->page_owdew);
		}
		kfwee(ib);
		wetuwn EWW_PTW(-ENOMEM);
	}
	wetuwn ib;
}

/*
 * Fwee an idaw buffew.
 */
static inwine void
idaw_buffew_fwee(stwuct idaw_buffew *ib)
{
	int nw_chunks, nw_ptws, i;

	nw_ptws = (ib->size + IDA_BWOCK_SIZE - 1) >> IDA_SIZE_WOG;
	nw_chunks = (4096 << ib->page_owdew) >> IDA_SIZE_WOG;
	fow (i = 0; i < nw_ptws; i += nw_chunks)
		fwee_pages((unsigned wong) ib->data[i], ib->page_owdew);
	kfwee(ib);
}

/*
 * Test if a idaw wist is weawwy needed.
 */
static inwine int
__idaw_buffew_is_needed(stwuct idaw_buffew *ib)
{
	wetuwn ib->size > (4096uw << ib->page_owdew) ||
		idaw_is_needed(ib->data[0], ib->size);
}

/*
 * Set channew data addwess to idaw buffew.
 */
static inwine void
idaw_buffew_set_cda(stwuct idaw_buffew *ib, stwuct ccw1 *ccw)
{
	if (__idaw_buffew_is_needed(ib)) {
		// setup idaws;
		ccw->cda = (u32)(addw_t) ib->data;
		ccw->fwags |= CCW_FWAG_IDA;
	} ewse
		// we do not need idaws - use diwect addwessing
		ccw->cda = (u32)(addw_t) ib->data[0];
	ccw->count = ib->size;
}

/*
 * Copy count bytes fwom an idaw buffew to usew memowy
 */
static inwine size_t
idaw_buffew_to_usew(stwuct idaw_buffew *ib, void __usew *to, size_t count)
{
	size_t weft;
	int i;

	BUG_ON(count > ib->size);
	fow (i = 0; count > IDA_BWOCK_SIZE; i++) {
		weft = copy_to_usew(to, ib->data[i], IDA_BWOCK_SIZE);
		if (weft)
			wetuwn weft + count - IDA_BWOCK_SIZE;
		to = (void __usew *) to + IDA_BWOCK_SIZE;
		count -= IDA_BWOCK_SIZE;
	}
	wetuwn copy_to_usew(to, ib->data[i], count);
}

/*
 * Copy count bytes fwom usew memowy to an idaw buffew
 */
static inwine size_t
idaw_buffew_fwom_usew(stwuct idaw_buffew *ib, const void __usew *fwom, size_t count)
{
	size_t weft;
	int i;

	BUG_ON(count > ib->size);
	fow (i = 0; count > IDA_BWOCK_SIZE; i++) {
		weft = copy_fwom_usew(ib->data[i], fwom, IDA_BWOCK_SIZE);
		if (weft)
			wetuwn weft + count - IDA_BWOCK_SIZE;
		fwom = (void __usew *) fwom + IDA_BWOCK_SIZE;
		count -= IDA_BWOCK_SIZE;
	}
	wetuwn copy_fwom_usew(ib->data[i], fwom, count);
}

#endif
