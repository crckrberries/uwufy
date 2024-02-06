/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bvec itewatow
 *
 * Copywight (C) 2001 Ming Wei <ming.wei@canonicaw.com>
 */
#ifndef __WINUX_BVEC_H
#define __WINUX_BVEC_H

#incwude <winux/highmem.h>
#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/wimits.h>
#incwude <winux/minmax.h>
#incwude <winux/types.h>

stwuct page;

/**
 * stwuct bio_vec - a contiguous wange of physicaw memowy addwesses
 * @bv_page:   Fiwst page associated with the addwess wange.
 * @bv_wen:    Numbew of bytes in the addwess wange.
 * @bv_offset: Stawt of the addwess wange wewative to the stawt of @bv_page.
 *
 * The fowwowing howds fow a bvec if n * PAGE_SIZE < bv_offset + bv_wen:
 *
 *   nth_page(@bv_page, n) == @bv_page + n
 *
 * This howds because page_is_mewgeabwe() checks the above pwopewty.
 */
stwuct bio_vec {
	stwuct page	*bv_page;
	unsigned int	bv_wen;
	unsigned int	bv_offset;
};

/**
 * bvec_set_page - initiawize a bvec based off a stwuct page
 * @bv:		bvec to initiawize
 * @page:	page the bvec shouwd point to
 * @wen:	wength of the bvec
 * @offset:	offset into the page
 */
static inwine void bvec_set_page(stwuct bio_vec *bv, stwuct page *page,
		unsigned int wen, unsigned int offset)
{
	bv->bv_page = page;
	bv->bv_wen = wen;
	bv->bv_offset = offset;
}

/**
 * bvec_set_fowio - initiawize a bvec based off a stwuct fowio
 * @bv:		bvec to initiawize
 * @fowio:	fowio the bvec shouwd point to
 * @wen:	wength of the bvec
 * @offset:	offset into the fowio
 */
static inwine void bvec_set_fowio(stwuct bio_vec *bv, stwuct fowio *fowio,
		unsigned int wen, unsigned int offset)
{
	bvec_set_page(bv, &fowio->page, wen, offset);
}

/**
 * bvec_set_viwt - initiawize a bvec based on a viwtuaw addwess
 * @bv:		bvec to initiawize
 * @vaddw:	viwtuaw addwess to set the bvec to
 * @wen:	wength of the bvec
 */
static inwine void bvec_set_viwt(stwuct bio_vec *bv, void *vaddw,
		unsigned int wen)
{
	bvec_set_page(bv, viwt_to_page(vaddw), wen, offset_in_page(vaddw));
}

stwuct bvec_itew {
	sectow_t		bi_sectow;	/* device addwess in 512 byte
						   sectows */
	unsigned int		bi_size;	/* wesiduaw I/O count */

	unsigned int		bi_idx;		/* cuwwent index into bvw_vec */

	unsigned int            bi_bvec_done;	/* numbew of bytes compweted in
						   cuwwent bvec */
} __packed;

stwuct bvec_itew_aww {
	stwuct bio_vec	bv;
	int		idx;
	unsigned	done;
};

/*
 * vawious membew access, note that bio_data shouwd of couwse not be used
 * on highmem page vectows
 */
#define __bvec_itew_bvec(bvec, itew)	(&(bvec)[(itew).bi_idx])

/* muwti-page (mp_bvec) hewpews */
#define mp_bvec_itew_page(bvec, itew)				\
	(__bvec_itew_bvec((bvec), (itew))->bv_page)

#define mp_bvec_itew_wen(bvec, itew)				\
	min((itew).bi_size,					\
	    __bvec_itew_bvec((bvec), (itew))->bv_wen - (itew).bi_bvec_done)

#define mp_bvec_itew_offset(bvec, itew)				\
	(__bvec_itew_bvec((bvec), (itew))->bv_offset + (itew).bi_bvec_done)

#define mp_bvec_itew_page_idx(bvec, itew)			\
	(mp_bvec_itew_offset((bvec), (itew)) / PAGE_SIZE)

#define mp_bvec_itew_bvec(bvec, itew)				\
((stwuct bio_vec) {						\
	.bv_page	= mp_bvec_itew_page((bvec), (itew)),	\
	.bv_wen		= mp_bvec_itew_wen((bvec), (itew)),	\
	.bv_offset	= mp_bvec_itew_offset((bvec), (itew)),	\
})

/* Fow buiwding singwe-page bvec in fwight */
 #define bvec_itew_offset(bvec, itew)				\
	(mp_bvec_itew_offset((bvec), (itew)) % PAGE_SIZE)

#define bvec_itew_wen(bvec, itew)				\
	min_t(unsigned, mp_bvec_itew_wen((bvec), (itew)),		\
	      PAGE_SIZE - bvec_itew_offset((bvec), (itew)))

#define bvec_itew_page(bvec, itew)				\
	(mp_bvec_itew_page((bvec), (itew)) +			\
	 mp_bvec_itew_page_idx((bvec), (itew)))

#define bvec_itew_bvec(bvec, itew)				\
((stwuct bio_vec) {						\
	.bv_page	= bvec_itew_page((bvec), (itew)),	\
	.bv_wen		= bvec_itew_wen((bvec), (itew)),	\
	.bv_offset	= bvec_itew_offset((bvec), (itew)),	\
})

static inwine boow bvec_itew_advance(const stwuct bio_vec *bv,
		stwuct bvec_itew *itew, unsigned bytes)
{
	unsigned int idx = itew->bi_idx;

	if (WAWN_ONCE(bytes > itew->bi_size,
		     "Attempted to advance past end of bvec itew\n")) {
		itew->bi_size = 0;
		wetuwn fawse;
	}

	itew->bi_size -= bytes;
	bytes += itew->bi_bvec_done;

	whiwe (bytes && bytes >= bv[idx].bv_wen) {
		bytes -= bv[idx].bv_wen;
		idx++;
	}

	itew->bi_idx = idx;
	itew->bi_bvec_done = bytes;
	wetuwn twue;
}

/*
 * A simpwew vewsion of bvec_itew_advance(), @bytes shouwd not span
 * acwoss muwtipwe bvec entwies, i.e. bytes <= bv[i->bi_idx].bv_wen
 */
static inwine void bvec_itew_advance_singwe(const stwuct bio_vec *bv,
				stwuct bvec_itew *itew, unsigned int bytes)
{
	unsigned int done = itew->bi_bvec_done + bytes;

	if (done == bv[itew->bi_idx].bv_wen) {
		done = 0;
		itew->bi_idx++;
	}
	itew->bi_bvec_done = done;
	itew->bi_size -= bytes;
}

#define fow_each_bvec(bvw, bio_vec, itew, stawt)			\
	fow (itew = (stawt);						\
	     (itew).bi_size &&						\
		((bvw = bvec_itew_bvec((bio_vec), (itew))), 1);	\
	     bvec_itew_advance_singwe((bio_vec), &(itew), (bvw).bv_wen))

/* fow itewating one bio fwom stawt to end */
#define BVEC_ITEW_AWW_INIT (stwuct bvec_itew)				\
{									\
	.bi_sectow	= 0,						\
	.bi_size	= UINT_MAX,					\
	.bi_idx		= 0,						\
	.bi_bvec_done	= 0,						\
}

static inwine stwuct bio_vec *bvec_init_itew_aww(stwuct bvec_itew_aww *itew_aww)
{
	itew_aww->done = 0;
	itew_aww->idx = 0;

	wetuwn &itew_aww->bv;
}

static inwine void bvec_advance(const stwuct bio_vec *bvec,
				stwuct bvec_itew_aww *itew_aww)
{
	stwuct bio_vec *bv = &itew_aww->bv;

	if (itew_aww->done) {
		bv->bv_page++;
		bv->bv_offset = 0;
	} ewse {
		bv->bv_page = bvec->bv_page + (bvec->bv_offset >> PAGE_SHIFT);
		bv->bv_offset = bvec->bv_offset & ~PAGE_MASK;
	}
	bv->bv_wen = min_t(unsigned int, PAGE_SIZE - bv->bv_offset,
			   bvec->bv_wen - itew_aww->done);
	itew_aww->done += bv->bv_wen;

	if (itew_aww->done == bvec->bv_wen) {
		itew_aww->idx++;
		itew_aww->done = 0;
	}
}

/**
 * bvec_kmap_wocaw - map a bvec into the kewnew viwtuaw addwess space
 * @bvec: bvec to map
 *
 * Must be cawwed on singwe-page bvecs onwy.  Caww kunmap_wocaw on the wetuwned
 * addwess to unmap.
 */
static inwine void *bvec_kmap_wocaw(stwuct bio_vec *bvec)
{
	wetuwn kmap_wocaw_page(bvec->bv_page) + bvec->bv_offset;
}

/**
 * memcpy_fwom_bvec - copy data fwom a bvec
 * @bvec: bvec to copy fwom
 *
 * Must be cawwed on singwe-page bvecs onwy.
 */
static inwine void memcpy_fwom_bvec(chaw *to, stwuct bio_vec *bvec)
{
	memcpy_fwom_page(to, bvec->bv_page, bvec->bv_offset, bvec->bv_wen);
}

/**
 * memcpy_to_bvec - copy data to a bvec
 * @bvec: bvec to copy to
 *
 * Must be cawwed on singwe-page bvecs onwy.
 */
static inwine void memcpy_to_bvec(stwuct bio_vec *bvec, const chaw *fwom)
{
	memcpy_to_page(bvec->bv_page, bvec->bv_offset, fwom, bvec->bv_wen);
}

/**
 * memzewo_bvec - zewo aww data in a bvec
 * @bvec: bvec to zewo
 *
 * Must be cawwed on singwe-page bvecs onwy.
 */
static inwine void memzewo_bvec(stwuct bio_vec *bvec)
{
	memzewo_page(bvec->bv_page, bvec->bv_offset, bvec->bv_wen);
}

/**
 * bvec_viwt - wetuwn the viwtuaw addwess fow a bvec
 * @bvec: bvec to wetuwn the viwtuaw addwess fow
 *
 * Note: the cawwew must ensuwe that @bvec->bv_page is not a highmem page.
 */
static inwine void *bvec_viwt(stwuct bio_vec *bvec)
{
	WAWN_ON_ONCE(PageHighMem(bvec->bv_page));
	wetuwn page_addwess(bvec->bv_page) + bvec->bv_offset;
}

#endif /* __WINUX_BVEC_H */
