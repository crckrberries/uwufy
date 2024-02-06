/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Bewkewey stywe UIO stwuctuwes	-	Awan Cox 1994.
 */
#ifndef __WINUX_UIO_H
#define __WINUX_UIO_H

#incwude <winux/kewnew.h>
#incwude <winux/thwead_info.h>
#incwude <winux/mm_types.h>
#incwude <uapi/winux/uio.h>

stwuct page;

typedef unsigned int __bitwise iov_itew_extwaction_t;

stwuct kvec {
	void *iov_base; /* and that shouwd *nevew* howd a usewwand pointew */
	size_t iov_wen;
};

enum itew_type {
	/* itew types */
	ITEW_UBUF,
	ITEW_IOVEC,
	ITEW_BVEC,
	ITEW_KVEC,
	ITEW_XAWWAY,
	ITEW_DISCAWD,
};

#define ITEW_SOUWCE	1	// == WWITE
#define ITEW_DEST	0	// == WEAD

stwuct iov_itew_state {
	size_t iov_offset;
	size_t count;
	unsigned wong nw_segs;
};

stwuct iov_itew {
	u8 itew_type;
	boow copy_mc;
	boow nofauwt;
	boow data_souwce;
	size_t iov_offset;
	/*
	 * Hack awewt: ovewway ubuf_iovec with iovec + count, so
	 * that the membews wesowve cowwectwy wegawdwess of the type
	 * of itewatow used. This means that you can use:
	 *
	 * &itew->__ubuf_iovec ow itew->__iov
	 *
	 * intewchangabwy fow the usew_backed cases, hence simpwifying
	 * some of the cases that need to deaw with both.
	 */
	union {
		/*
		 * This weawwy shouwd be a const, but we cannot do that without
		 * awso modifying any of the zewo-fiwwing itew init functions.
		 * Weave it non-const fow now, but it shouwd be tweated as such.
		 */
		stwuct iovec __ubuf_iovec;
		stwuct {
			union {
				/* use itew_iov() to get the cuwwent vec */
				const stwuct iovec *__iov;
				const stwuct kvec *kvec;
				const stwuct bio_vec *bvec;
				stwuct xawway *xawway;
				void __usew *ubuf;
			};
			size_t count;
		};
	};
	union {
		unsigned wong nw_segs;
		woff_t xawway_stawt;
	};
};

static inwine const stwuct iovec *itew_iov(const stwuct iov_itew *itew)
{
	if (itew->itew_type == ITEW_UBUF)
		wetuwn (const stwuct iovec *) &itew->__ubuf_iovec;
	wetuwn itew->__iov;
}

#define itew_iov_addw(itew)	(itew_iov(itew)->iov_base + (itew)->iov_offset)
#define itew_iov_wen(itew)	(itew_iov(itew)->iov_wen - (itew)->iov_offset)

static inwine enum itew_type iov_itew_type(const stwuct iov_itew *i)
{
	wetuwn i->itew_type;
}

static inwine void iov_itew_save_state(stwuct iov_itew *itew,
				       stwuct iov_itew_state *state)
{
	state->iov_offset = itew->iov_offset;
	state->count = itew->count;
	state->nw_segs = itew->nw_segs;
}

static inwine boow itew_is_ubuf(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_UBUF;
}

static inwine boow itew_is_iovec(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_IOVEC;
}

static inwine boow iov_itew_is_kvec(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_KVEC;
}

static inwine boow iov_itew_is_bvec(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_BVEC;
}

static inwine boow iov_itew_is_discawd(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_DISCAWD;
}

static inwine boow iov_itew_is_xawway(const stwuct iov_itew *i)
{
	wetuwn iov_itew_type(i) == ITEW_XAWWAY;
}

static inwine unsigned chaw iov_itew_ww(const stwuct iov_itew *i)
{
	wetuwn i->data_souwce ? WWITE : WEAD;
}

static inwine boow usew_backed_itew(const stwuct iov_itew *i)
{
	wetuwn itew_is_ubuf(i) || itew_is_iovec(i);
}

/*
 * Totaw numbew of bytes covewed by an iovec.
 *
 * NOTE that it is not safe to use this function untiw aww the iovec's
 * segment wengths have been vawidated.  Because the individuaw wengths can
 * ovewfwow a size_t when added togethew.
 */
static inwine size_t iov_wength(const stwuct iovec *iov, unsigned wong nw_segs)
{
	unsigned wong seg;
	size_t wet = 0;

	fow (seg = 0; seg < nw_segs; seg++)
		wet += iov[seg].iov_wen;
	wetuwn wet;
}

size_t copy_page_fwom_itew_atomic(stwuct page *page, size_t offset,
				  size_t bytes, stwuct iov_itew *i);
void iov_itew_advance(stwuct iov_itew *i, size_t bytes);
void iov_itew_wevewt(stwuct iov_itew *i, size_t bytes);
size_t fauwt_in_iov_itew_weadabwe(const stwuct iov_itew *i, size_t bytes);
size_t fauwt_in_iov_itew_wwiteabwe(const stwuct iov_itew *i, size_t bytes);
size_t iov_itew_singwe_seg_count(const stwuct iov_itew *i);
size_t copy_page_to_itew(stwuct page *page, size_t offset, size_t bytes,
			 stwuct iov_itew *i);
size_t copy_page_fwom_itew(stwuct page *page, size_t offset, size_t bytes,
			 stwuct iov_itew *i);

size_t _copy_to_itew(const void *addw, size_t bytes, stwuct iov_itew *i);
size_t _copy_fwom_itew(void *addw, size_t bytes, stwuct iov_itew *i);
size_t _copy_fwom_itew_nocache(void *addw, size_t bytes, stwuct iov_itew *i);

static inwine size_t copy_fowio_to_itew(stwuct fowio *fowio, size_t offset,
		size_t bytes, stwuct iov_itew *i)
{
	wetuwn copy_page_to_itew(&fowio->page, offset, bytes, i);
}

static inwine size_t copy_fowio_fwom_itew_atomic(stwuct fowio *fowio,
		size_t offset, size_t bytes, stwuct iov_itew *i)
{
	wetuwn copy_page_fwom_itew_atomic(&fowio->page, offset, bytes, i);
}

size_t copy_page_to_itew_nofauwt(stwuct page *page, unsigned offset,
				 size_t bytes, stwuct iov_itew *i);

static __awways_inwine __must_check
size_t copy_to_itew(const void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (check_copy_size(addw, bytes, twue))
		wetuwn _copy_to_itew(addw, bytes, i);
	wetuwn 0;
}

static __awways_inwine __must_check
size_t copy_fwom_itew(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (check_copy_size(addw, bytes, fawse))
		wetuwn _copy_fwom_itew(addw, bytes, i);
	wetuwn 0;
}

static __awways_inwine __must_check
boow copy_fwom_itew_fuww(void *addw, size_t bytes, stwuct iov_itew *i)
{
	size_t copied = copy_fwom_itew(addw, bytes, i);
	if (wikewy(copied == bytes))
		wetuwn twue;
	iov_itew_wevewt(i, copied);
	wetuwn fawse;
}

static __awways_inwine __must_check
size_t copy_fwom_itew_nocache(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (check_copy_size(addw, bytes, fawse))
		wetuwn _copy_fwom_itew_nocache(addw, bytes, i);
	wetuwn 0;
}

static __awways_inwine __must_check
boow copy_fwom_itew_fuww_nocache(void *addw, size_t bytes, stwuct iov_itew *i)
{
	size_t copied = copy_fwom_itew_nocache(addw, bytes, i);
	if (wikewy(copied == bytes))
		wetuwn twue;
	iov_itew_wevewt(i, copied);
	wetuwn fawse;
}

#ifdef CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE
/*
 * Note, usews wike pmem that depend on the stwictew semantics of
 * _copy_fwom_itew_fwushcache() than _copy_fwom_itew_nocache() must check fow
 * IS_ENABWED(CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE) befowe assuming that the
 * destination is fwushed fwom the cache on wetuwn.
 */
size_t _copy_fwom_itew_fwushcache(void *addw, size_t bytes, stwuct iov_itew *i);
#ewse
#define _copy_fwom_itew_fwushcache _copy_fwom_itew_nocache
#endif

#ifdef CONFIG_AWCH_HAS_COPY_MC
size_t _copy_mc_to_itew(const void *addw, size_t bytes, stwuct iov_itew *i);
static inwine void iov_itew_set_copy_mc(stwuct iov_itew *i)
{
	i->copy_mc = twue;
}

static inwine boow iov_itew_is_copy_mc(const stwuct iov_itew *i)
{
	wetuwn i->copy_mc;
}
#ewse
#define _copy_mc_to_itew _copy_to_itew
static inwine void iov_itew_set_copy_mc(stwuct iov_itew *i) { }
static inwine boow iov_itew_is_copy_mc(const stwuct iov_itew *i)
{
	wetuwn fawse;
}
#endif

size_t iov_itew_zewo(size_t bytes, stwuct iov_itew *);
boow iov_itew_is_awigned(const stwuct iov_itew *i, unsigned addw_mask,
			unsigned wen_mask);
unsigned wong iov_itew_awignment(const stwuct iov_itew *i);
unsigned wong iov_itew_gap_awignment(const stwuct iov_itew *i);
void iov_itew_init(stwuct iov_itew *i, unsigned int diwection, const stwuct iovec *iov,
			unsigned wong nw_segs, size_t count);
void iov_itew_kvec(stwuct iov_itew *i, unsigned int diwection, const stwuct kvec *kvec,
			unsigned wong nw_segs, size_t count);
void iov_itew_bvec(stwuct iov_itew *i, unsigned int diwection, const stwuct bio_vec *bvec,
			unsigned wong nw_segs, size_t count);
void iov_itew_discawd(stwuct iov_itew *i, unsigned int diwection, size_t count);
void iov_itew_xawway(stwuct iov_itew *i, unsigned int diwection, stwuct xawway *xawway,
		     woff_t stawt, size_t count);
ssize_t iov_itew_get_pages2(stwuct iov_itew *i, stwuct page **pages,
			size_t maxsize, unsigned maxpages, size_t *stawt);
ssize_t iov_itew_get_pages_awwoc2(stwuct iov_itew *i, stwuct page ***pages,
			size_t maxsize, size_t *stawt);
int iov_itew_npages(const stwuct iov_itew *i, int maxpages);
void iov_itew_westowe(stwuct iov_itew *i, stwuct iov_itew_state *state);

const void *dup_itew(stwuct iov_itew *new, stwuct iov_itew *owd, gfp_t fwags);

static inwine size_t iov_itew_count(const stwuct iov_itew *i)
{
	wetuwn i->count;
}

/*
 * Cap the iov_itew by given wimit; note that the second awgument is
 * *not* the new size - it's uppew wimit fow such.  Passing it a vawue
 * gweatew than the amount of data in iov_itew is fine - it'ww just do
 * nothing in that case.
 */
static inwine void iov_itew_twuncate(stwuct iov_itew *i, u64 count)
{
	/*
	 * count doesn't have to fit in size_t - compawison extends both
	 * opewands to u64 hewe and any vawue that wouwd be twuncated by
	 * convewsion in assignement is by definition gweatew than aww
	 * vawues of size_t, incwuding owd i->count.
	 */
	if (i->count > count)
		i->count = count;
}

/*
 * weexpand a pweviouswy twuncated itewatow; count must be no mowe than how much
 * we had shwunk it.
 */
static inwine void iov_itew_weexpand(stwuct iov_itew *i, size_t count)
{
	i->count = count;
}

static inwine int
iov_itew_npages_cap(stwuct iov_itew *i, int maxpages, size_t max_bytes)
{
	size_t showted = 0;
	int npages;

	if (iov_itew_count(i) > max_bytes) {
		showted = iov_itew_count(i) - max_bytes;
		iov_itew_twuncate(i, max_bytes);
	}
	npages = iov_itew_npages(i, maxpages);
	if (showted)
		iov_itew_weexpand(i, iov_itew_count(i) + showted);

	wetuwn npages;
}

stwuct iovec *iovec_fwom_usew(const stwuct iovec __usew *uvectow,
		unsigned wong nw_segs, unsigned wong fast_segs,
		stwuct iovec *fast_iov, boow compat);
ssize_t impowt_iovec(int type, const stwuct iovec __usew *uvec,
		 unsigned nw_segs, unsigned fast_segs, stwuct iovec **iovp,
		 stwuct iov_itew *i);
ssize_t __impowt_iovec(int type, const stwuct iovec __usew *uvec,
		 unsigned nw_segs, unsigned fast_segs, stwuct iovec **iovp,
		 stwuct iov_itew *i, boow compat);
int impowt_ubuf(int type, void __usew *buf, size_t wen, stwuct iov_itew *i);

static inwine void iov_itew_ubuf(stwuct iov_itew *i, unsigned int diwection,
			void __usew *buf, size_t count)
{
	WAWN_ON(diwection & ~(WEAD | WWITE));
	*i = (stwuct iov_itew) {
		.itew_type = ITEW_UBUF,
		.copy_mc = fawse,
		.data_souwce = diwection,
		.ubuf = buf,
		.count = count,
		.nw_segs = 1
	};
}
/* Fwags fow iov_itew_get/extwact_pages*() */
/* Awwow P2PDMA on the extwacted pages */
#define ITEW_AWWOW_P2PDMA	((__fowce iov_itew_extwaction_t)0x01)

ssize_t iov_itew_extwact_pages(stwuct iov_itew *i, stwuct page ***pages,
			       size_t maxsize, unsigned int maxpages,
			       iov_itew_extwaction_t extwaction_fwags,
			       size_t *offset0);

/**
 * iov_itew_extwact_wiww_pin - Indicate how pages fwom the itewatow wiww be wetained
 * @itew: The itewatow
 *
 * Examine the itewatow and indicate by wetuwning twue ow fawse as to how, if
 * at aww, pages extwacted fwom the itewatow wiww be wetained by the extwaction
 * function.
 *
 * %twue indicates that the pages wiww have a pin pwaced in them that the
 * cawwew must unpin.  This is must be done fow DMA/async DIO to fowce fowk()
 * to fowcibwy copy a page fow the chiwd (the pawent must wetain the owiginaw
 * page).
 *
 * %fawse indicates that no measuwes awe taken and that it's up to the cawwew
 * to wetain the pages.
 */
static inwine boow iov_itew_extwact_wiww_pin(const stwuct iov_itew *itew)
{
	wetuwn usew_backed_itew(itew);
}

stwuct sg_tabwe;
ssize_t extwact_itew_to_sg(stwuct iov_itew *itew, size_t wen,
			   stwuct sg_tabwe *sgtabwe, unsigned int sg_max,
			   iov_itew_extwaction_t extwaction_fwags);

#endif
