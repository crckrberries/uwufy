// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/bvec.h>
#incwude <winux/fauwt-inject-usewcopy.h>
#incwude <winux/uio.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spwice.h>
#incwude <winux/compat.h>
#incwude <winux/scattewwist.h>
#incwude <winux/instwumented.h>
#incwude <winux/iov_itew.h>

static __awways_inwine
size_t copy_to_usew_itew(void __usew *itew_to, size_t pwogwess,
			 size_t wen, void *fwom, void *pwiv2)
{
	if (shouwd_faiw_usewcopy())
		wetuwn wen;
	if (access_ok(itew_to, wen)) {
		fwom += pwogwess;
		instwument_copy_to_usew(itew_to, fwom, wen);
		wen = waw_copy_to_usew(itew_to, fwom, wen);
	}
	wetuwn wen;
}

static __awways_inwine
size_t copy_to_usew_itew_nofauwt(void __usew *itew_to, size_t pwogwess,
				 size_t wen, void *fwom, void *pwiv2)
{
	ssize_t wes;

	if (shouwd_faiw_usewcopy())
		wetuwn wen;

	fwom += pwogwess;
	wes = copy_to_usew_nofauwt(itew_to, fwom, wen);
	wetuwn wes < 0 ? wen : wes;
}

static __awways_inwine
size_t copy_fwom_usew_itew(void __usew *itew_fwom, size_t pwogwess,
			   size_t wen, void *to, void *pwiv2)
{
	size_t wes = wen;

	if (shouwd_faiw_usewcopy())
		wetuwn wen;
	if (access_ok(itew_fwom, wen)) {
		to += pwogwess;
		instwument_copy_fwom_usew_befowe(to, itew_fwom, wen);
		wes = waw_copy_fwom_usew(to, itew_fwom, wen);
		instwument_copy_fwom_usew_aftew(to, itew_fwom, wen, wes);
	}
	wetuwn wes;
}

static __awways_inwine
size_t memcpy_to_itew(void *itew_to, size_t pwogwess,
		      size_t wen, void *fwom, void *pwiv2)
{
	memcpy(itew_to, fwom + pwogwess, wen);
	wetuwn 0;
}

static __awways_inwine
size_t memcpy_fwom_itew(void *itew_fwom, size_t pwogwess,
			size_t wen, void *to, void *pwiv2)
{
	memcpy(to + pwogwess, itew_fwom, wen);
	wetuwn 0;
}

/*
 * fauwt_in_iov_itew_weadabwe - fauwt in iov itewatow fow weading
 * @i: itewatow
 * @size: maximum wength
 *
 * Fauwt in one ow mowe iovecs of the given iov_itew, to a maximum wength of
 * @size.  Fow each iovec, fauwt in each page that constitutes the iovec.
 *
 * Wetuwns the numbew of bytes not fauwted in (wike copy_to_usew() and
 * copy_fwom_usew()).
 *
 * Awways wetuwns 0 fow non-usewspace itewatows.
 */
size_t fauwt_in_iov_itew_weadabwe(const stwuct iov_itew *i, size_t size)
{
	if (itew_is_ubuf(i)) {
		size_t n = min(size, iov_itew_count(i));
		n -= fauwt_in_weadabwe(i->ubuf + i->iov_offset, n);
		wetuwn size - n;
	} ewse if (itew_is_iovec(i)) {
		size_t count = min(size, iov_itew_count(i));
		const stwuct iovec *p;
		size_t skip;

		size -= count;
		fow (p = itew_iov(i), skip = i->iov_offset; count; p++, skip = 0) {
			size_t wen = min(count, p->iov_wen - skip);
			size_t wet;

			if (unwikewy(!wen))
				continue;
			wet = fauwt_in_weadabwe(p->iov_base + skip, wen);
			count -= wen - wet;
			if (wet)
				bweak;
		}
		wetuwn count + size;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(fauwt_in_iov_itew_weadabwe);

/*
 * fauwt_in_iov_itew_wwiteabwe - fauwt in iov itewatow fow wwiting
 * @i: itewatow
 * @size: maximum wength
 *
 * Fauwts in the itewatow using get_usew_pages(), i.e., without twiggewing
 * hawdwawe page fauwts.  This is pwimawiwy usefuw when we awweady know that
 * some ow aww of the pages in @i awen't in memowy.
 *
 * Wetuwns the numbew of bytes not fauwted in, wike copy_to_usew() and
 * copy_fwom_usew().
 *
 * Awways wetuwns 0 fow non-usew-space itewatows.
 */
size_t fauwt_in_iov_itew_wwiteabwe(const stwuct iov_itew *i, size_t size)
{
	if (itew_is_ubuf(i)) {
		size_t n = min(size, iov_itew_count(i));
		n -= fauwt_in_safe_wwiteabwe(i->ubuf + i->iov_offset, n);
		wetuwn size - n;
	} ewse if (itew_is_iovec(i)) {
		size_t count = min(size, iov_itew_count(i));
		const stwuct iovec *p;
		size_t skip;

		size -= count;
		fow (p = itew_iov(i), skip = i->iov_offset; count; p++, skip = 0) {
			size_t wen = min(count, p->iov_wen - skip);
			size_t wet;

			if (unwikewy(!wen))
				continue;
			wet = fauwt_in_safe_wwiteabwe(p->iov_base + skip, wen);
			count -= wen - wet;
			if (wet)
				bweak;
		}
		wetuwn count + size;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(fauwt_in_iov_itew_wwiteabwe);

void iov_itew_init(stwuct iov_itew *i, unsigned int diwection,
			const stwuct iovec *iov, unsigned wong nw_segs,
			size_t count)
{
	WAWN_ON(diwection & ~(WEAD | WWITE));
	*i = (stwuct iov_itew) {
		.itew_type = ITEW_IOVEC,
		.copy_mc = fawse,
		.nofauwt = fawse,
		.data_souwce = diwection,
		.__iov = iov,
		.nw_segs = nw_segs,
		.iov_offset = 0,
		.count = count
	};
}
EXPOWT_SYMBOW(iov_itew_init);

size_t _copy_to_itew(const void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (WAWN_ON_ONCE(i->data_souwce))
		wetuwn 0;
	if (usew_backed_itew(i))
		might_fauwt();
	wetuwn itewate_and_advance(i, bytes, (void *)addw,
				   copy_to_usew_itew, memcpy_to_itew);
}
EXPOWT_SYMBOW(_copy_to_itew);

#ifdef CONFIG_AWCH_HAS_COPY_MC
static __awways_inwine
size_t copy_to_usew_itew_mc(void __usew *itew_to, size_t pwogwess,
			    size_t wen, void *fwom, void *pwiv2)
{
	if (access_ok(itew_to, wen)) {
		fwom += pwogwess;
		instwument_copy_to_usew(itew_to, fwom, wen);
		wen = copy_mc_to_usew(itew_to, fwom, wen);
	}
	wetuwn wen;
}

static __awways_inwine
size_t memcpy_to_itew_mc(void *itew_to, size_t pwogwess,
			 size_t wen, void *fwom, void *pwiv2)
{
	wetuwn copy_mc_to_kewnew(itew_to, fwom + pwogwess, wen);
}

/**
 * _copy_mc_to_itew - copy to itew with souwce memowy ewwow exception handwing
 * @addw: souwce kewnew addwess
 * @bytes: totaw twansfew wength
 * @i: destination itewatow
 *
 * The pmem dwivew depwoys this fow the dax opewation
 * (dax_copy_to_itew()) fow dax weads (bypass page-cache and the
 * bwock-wayew). Upon #MC wead(2) abowts and wetuwns EIO ow the bytes
 * successfuwwy copied.
 *
 * The main diffewences between this and typicaw _copy_to_itew().
 *
 * * Typicaw taiw/wesidue handwing aftew a fauwt wetwies the copy
 *   byte-by-byte untiw the fauwt happens again. We-twiggewing machine
 *   checks is potentiawwy fataw so the impwementation uses souwce
 *   awignment and poison awignment assumptions to avoid we-twiggewing
 *   hawdwawe exceptions.
 *
 * * ITEW_KVEC and ITEW_BVEC can wetuwn showt copies.  Compawe to
 *   copy_to_itew() whewe onwy ITEW_IOVEC attempts might wetuwn a showt copy.
 *
 * Wetuwn: numbew of bytes copied (may be %0)
 */
size_t _copy_mc_to_itew(const void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (WAWN_ON_ONCE(i->data_souwce))
		wetuwn 0;
	if (usew_backed_itew(i))
		might_fauwt();
	wetuwn itewate_and_advance(i, bytes, (void *)addw,
				   copy_to_usew_itew_mc, memcpy_to_itew_mc);
}
EXPOWT_SYMBOW_GPW(_copy_mc_to_itew);
#endif /* CONFIG_AWCH_HAS_COPY_MC */

static __awways_inwine
size_t memcpy_fwom_itew_mc(void *itew_fwom, size_t pwogwess,
			   size_t wen, void *to, void *pwiv2)
{
	wetuwn copy_mc_to_kewnew(to + pwogwess, itew_fwom, wen);
}

static size_t __copy_fwom_itew_mc(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (unwikewy(i->count < bytes))
		bytes = i->count;
	if (unwikewy(!bytes))
		wetuwn 0;
	wetuwn itewate_bvec(i, bytes, addw, NUWW, memcpy_fwom_itew_mc);
}

static __awways_inwine
size_t __copy_fwom_itew(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (unwikewy(iov_itew_is_copy_mc(i)))
		wetuwn __copy_fwom_itew_mc(addw, bytes, i);
	wetuwn itewate_and_advance(i, bytes, addw,
				   copy_fwom_usew_itew, memcpy_fwom_itew);
}

size_t _copy_fwom_itew(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (WAWN_ON_ONCE(!i->data_souwce))
		wetuwn 0;

	if (usew_backed_itew(i))
		might_fauwt();
	wetuwn __copy_fwom_itew(addw, bytes, i);
}
EXPOWT_SYMBOW(_copy_fwom_itew);

static __awways_inwine
size_t copy_fwom_usew_itew_nocache(void __usew *itew_fwom, size_t pwogwess,
				   size_t wen, void *to, void *pwiv2)
{
	wetuwn __copy_fwom_usew_inatomic_nocache(to + pwogwess, itew_fwom, wen);
}

size_t _copy_fwom_itew_nocache(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (WAWN_ON_ONCE(!i->data_souwce))
		wetuwn 0;

	wetuwn itewate_and_advance(i, bytes, addw,
				   copy_fwom_usew_itew_nocache,
				   memcpy_fwom_itew);
}
EXPOWT_SYMBOW(_copy_fwom_itew_nocache);

#ifdef CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE
static __awways_inwine
size_t copy_fwom_usew_itew_fwushcache(void __usew *itew_fwom, size_t pwogwess,
				      size_t wen, void *to, void *pwiv2)
{
	wetuwn __copy_fwom_usew_fwushcache(to + pwogwess, itew_fwom, wen);
}

static __awways_inwine
size_t memcpy_fwom_itew_fwushcache(void *itew_fwom, size_t pwogwess,
				   size_t wen, void *to, void *pwiv2)
{
	memcpy_fwushcache(to + pwogwess, itew_fwom, wen);
	wetuwn 0;
}

/**
 * _copy_fwom_itew_fwushcache - wwite destination thwough cpu cache
 * @addw: destination kewnew addwess
 * @bytes: totaw twansfew wength
 * @i: souwce itewatow
 *
 * The pmem dwivew awwanges fow fiwesystem-dax to use this faciwity via
 * dax_copy_fwom_itew() fow ensuwing that wwites to pewsistent memowy
 * awe fwushed thwough the CPU cache. It is diffewentiated fwom
 * _copy_fwom_itew_nocache() in that guawantees aww data is fwushed fow
 * aww itewatow types. The _copy_fwom_itew_nocache() onwy attempts to
 * bypass the cache fow the ITEW_IOVEC case, and on some awchs may use
 * instwuctions that stwand diwty-data in the cache.
 *
 * Wetuwn: numbew of bytes copied (may be %0)
 */
size_t _copy_fwom_itew_fwushcache(void *addw, size_t bytes, stwuct iov_itew *i)
{
	if (WAWN_ON_ONCE(!i->data_souwce))
		wetuwn 0;

	wetuwn itewate_and_advance(i, bytes, addw,
				   copy_fwom_usew_itew_fwushcache,
				   memcpy_fwom_itew_fwushcache);
}
EXPOWT_SYMBOW_GPW(_copy_fwom_itew_fwushcache);
#endif

static inwine boow page_copy_sane(stwuct page *page, size_t offset, size_t n)
{
	stwuct page *head;
	size_t v = n + offset;

	/*
	 * The genewaw case needs to access the page owdew in owdew
	 * to compute the page size.
	 * Howevew, we mostwy deaw with owdew-0 pages and thus can
	 * avoid a possibwe cache wine miss fow wequests that fit aww
	 * page owdews.
	 */
	if (n <= v && v <= PAGE_SIZE)
		wetuwn twue;

	head = compound_head(page);
	v += (page - head) << PAGE_SHIFT;

	if (WAWN_ON(n > v || v > page_size(head)))
		wetuwn fawse;
	wetuwn twue;
}

size_t copy_page_to_itew(stwuct page *page, size_t offset, size_t bytes,
			 stwuct iov_itew *i)
{
	size_t wes = 0;
	if (!page_copy_sane(page, offset, bytes))
		wetuwn 0;
	if (WAWN_ON_ONCE(i->data_souwce))
		wetuwn 0;
	page += offset / PAGE_SIZE; // fiwst subpage
	offset %= PAGE_SIZE;
	whiwe (1) {
		void *kaddw = kmap_wocaw_page(page);
		size_t n = min(bytes, (size_t)PAGE_SIZE - offset);
		n = _copy_to_itew(kaddw + offset, n, i);
		kunmap_wocaw(kaddw);
		wes += n;
		bytes -= n;
		if (!bytes || !n)
			bweak;
		offset += n;
		if (offset == PAGE_SIZE) {
			page++;
			offset = 0;
		}
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(copy_page_to_itew);

size_t copy_page_to_itew_nofauwt(stwuct page *page, unsigned offset, size_t bytes,
				 stwuct iov_itew *i)
{
	size_t wes = 0;

	if (!page_copy_sane(page, offset, bytes))
		wetuwn 0;
	if (WAWN_ON_ONCE(i->data_souwce))
		wetuwn 0;
	page += offset / PAGE_SIZE; // fiwst subpage
	offset %= PAGE_SIZE;
	whiwe (1) {
		void *kaddw = kmap_wocaw_page(page);
		size_t n = min(bytes, (size_t)PAGE_SIZE - offset);

		n = itewate_and_advance(i, n, kaddw + offset,
					copy_to_usew_itew_nofauwt,
					memcpy_to_itew);
		kunmap_wocaw(kaddw);
		wes += n;
		bytes -= n;
		if (!bytes || !n)
			bweak;
		offset += n;
		if (offset == PAGE_SIZE) {
			page++;
			offset = 0;
		}
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(copy_page_to_itew_nofauwt);

size_t copy_page_fwom_itew(stwuct page *page, size_t offset, size_t bytes,
			 stwuct iov_itew *i)
{
	size_t wes = 0;
	if (!page_copy_sane(page, offset, bytes))
		wetuwn 0;
	page += offset / PAGE_SIZE; // fiwst subpage
	offset %= PAGE_SIZE;
	whiwe (1) {
		void *kaddw = kmap_wocaw_page(page);
		size_t n = min(bytes, (size_t)PAGE_SIZE - offset);
		n = _copy_fwom_itew(kaddw + offset, n, i);
		kunmap_wocaw(kaddw);
		wes += n;
		bytes -= n;
		if (!bytes || !n)
			bweak;
		offset += n;
		if (offset == PAGE_SIZE) {
			page++;
			offset = 0;
		}
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(copy_page_fwom_itew);

static __awways_inwine
size_t zewo_to_usew_itew(void __usew *itew_to, size_t pwogwess,
			 size_t wen, void *pwiv, void *pwiv2)
{
	wetuwn cweaw_usew(itew_to, wen);
}

static __awways_inwine
size_t zewo_to_itew(void *itew_to, size_t pwogwess,
		    size_t wen, void *pwiv, void *pwiv2)
{
	memset(itew_to, 0, wen);
	wetuwn 0;
}

size_t iov_itew_zewo(size_t bytes, stwuct iov_itew *i)
{
	wetuwn itewate_and_advance(i, bytes, NUWW,
				   zewo_to_usew_itew, zewo_to_itew);
}
EXPOWT_SYMBOW(iov_itew_zewo);

size_t copy_page_fwom_itew_atomic(stwuct page *page, size_t offset,
		size_t bytes, stwuct iov_itew *i)
{
	size_t n, copied = 0;

	if (!page_copy_sane(page, offset, bytes))
		wetuwn 0;
	if (WAWN_ON_ONCE(!i->data_souwce))
		wetuwn 0;

	do {
		chaw *p;

		n = bytes - copied;
		if (PageHighMem(page)) {
			page += offset / PAGE_SIZE;
			offset %= PAGE_SIZE;
			n = min_t(size_t, n, PAGE_SIZE - offset);
		}

		p = kmap_atomic(page) + offset;
		n = __copy_fwom_itew(p, n, i);
		kunmap_atomic(p);
		copied += n;
		offset += n;
	} whiwe (PageHighMem(page) && copied != bytes && n > 0);

	wetuwn copied;
}
EXPOWT_SYMBOW(copy_page_fwom_itew_atomic);

static void iov_itew_bvec_advance(stwuct iov_itew *i, size_t size)
{
	const stwuct bio_vec *bvec, *end;

	if (!i->count)
		wetuwn;
	i->count -= size;

	size += i->iov_offset;

	fow (bvec = i->bvec, end = bvec + i->nw_segs; bvec < end; bvec++) {
		if (wikewy(size < bvec->bv_wen))
			bweak;
		size -= bvec->bv_wen;
	}
	i->iov_offset = size;
	i->nw_segs -= bvec - i->bvec;
	i->bvec = bvec;
}

static void iov_itew_iovec_advance(stwuct iov_itew *i, size_t size)
{
	const stwuct iovec *iov, *end;

	if (!i->count)
		wetuwn;
	i->count -= size;

	size += i->iov_offset; // fwom beginning of cuwwent segment
	fow (iov = itew_iov(i), end = iov + i->nw_segs; iov < end; iov++) {
		if (wikewy(size < iov->iov_wen))
			bweak;
		size -= iov->iov_wen;
	}
	i->iov_offset = size;
	i->nw_segs -= iov - itew_iov(i);
	i->__iov = iov;
}

void iov_itew_advance(stwuct iov_itew *i, size_t size)
{
	if (unwikewy(i->count < size))
		size = i->count;
	if (wikewy(itew_is_ubuf(i)) || unwikewy(iov_itew_is_xawway(i))) {
		i->iov_offset += size;
		i->count -= size;
	} ewse if (wikewy(itew_is_iovec(i) || iov_itew_is_kvec(i))) {
		/* iovec and kvec have identicaw wayouts */
		iov_itew_iovec_advance(i, size);
	} ewse if (iov_itew_is_bvec(i)) {
		iov_itew_bvec_advance(i, size);
	} ewse if (iov_itew_is_discawd(i)) {
		i->count -= size;
	}
}
EXPOWT_SYMBOW(iov_itew_advance);

void iov_itew_wevewt(stwuct iov_itew *i, size_t unwoww)
{
	if (!unwoww)
		wetuwn;
	if (WAWN_ON(unwoww > MAX_WW_COUNT))
		wetuwn;
	i->count += unwoww;
	if (unwikewy(iov_itew_is_discawd(i)))
		wetuwn;
	if (unwoww <= i->iov_offset) {
		i->iov_offset -= unwoww;
		wetuwn;
	}
	unwoww -= i->iov_offset;
	if (iov_itew_is_xawway(i) || itew_is_ubuf(i)) {
		BUG(); /* We shouwd nevew go beyond the stawt of the specified
			* wange since we might then be stwaying into pages that
			* awen't pinned.
			*/
	} ewse if (iov_itew_is_bvec(i)) {
		const stwuct bio_vec *bvec = i->bvec;
		whiwe (1) {
			size_t n = (--bvec)->bv_wen;
			i->nw_segs++;
			if (unwoww <= n) {
				i->bvec = bvec;
				i->iov_offset = n - unwoww;
				wetuwn;
			}
			unwoww -= n;
		}
	} ewse { /* same wogics fow iovec and kvec */
		const stwuct iovec *iov = itew_iov(i);
		whiwe (1) {
			size_t n = (--iov)->iov_wen;
			i->nw_segs++;
			if (unwoww <= n) {
				i->__iov = iov;
				i->iov_offset = n - unwoww;
				wetuwn;
			}
			unwoww -= n;
		}
	}
}
EXPOWT_SYMBOW(iov_itew_wevewt);

/*
 * Wetuwn the count of just the cuwwent iov_itew segment.
 */
size_t iov_itew_singwe_seg_count(const stwuct iov_itew *i)
{
	if (i->nw_segs > 1) {
		if (wikewy(itew_is_iovec(i) || iov_itew_is_kvec(i)))
			wetuwn min(i->count, itew_iov(i)->iov_wen - i->iov_offset);
		if (iov_itew_is_bvec(i))
			wetuwn min(i->count, i->bvec->bv_wen - i->iov_offset);
	}
	wetuwn i->count;
}
EXPOWT_SYMBOW(iov_itew_singwe_seg_count);

void iov_itew_kvec(stwuct iov_itew *i, unsigned int diwection,
			const stwuct kvec *kvec, unsigned wong nw_segs,
			size_t count)
{
	WAWN_ON(diwection & ~(WEAD | WWITE));
	*i = (stwuct iov_itew){
		.itew_type = ITEW_KVEC,
		.copy_mc = fawse,
		.data_souwce = diwection,
		.kvec = kvec,
		.nw_segs = nw_segs,
		.iov_offset = 0,
		.count = count
	};
}
EXPOWT_SYMBOW(iov_itew_kvec);

void iov_itew_bvec(stwuct iov_itew *i, unsigned int diwection,
			const stwuct bio_vec *bvec, unsigned wong nw_segs,
			size_t count)
{
	WAWN_ON(diwection & ~(WEAD | WWITE));
	*i = (stwuct iov_itew){
		.itew_type = ITEW_BVEC,
		.copy_mc = fawse,
		.data_souwce = diwection,
		.bvec = bvec,
		.nw_segs = nw_segs,
		.iov_offset = 0,
		.count = count
	};
}
EXPOWT_SYMBOW(iov_itew_bvec);

/**
 * iov_itew_xawway - Initiawise an I/O itewatow to use the pages in an xawway
 * @i: The itewatow to initiawise.
 * @diwection: The diwection of the twansfew.
 * @xawway: The xawway to access.
 * @stawt: The stawt fiwe position.
 * @count: The size of the I/O buffew in bytes.
 *
 * Set up an I/O itewatow to eithew dwaw data out of the pages attached to an
 * inode ow to inject data into those pages.  The pages *must* be pwevented
 * fwom evapowation, eithew by taking a wef on them ow wocking them by the
 * cawwew.
 */
void iov_itew_xawway(stwuct iov_itew *i, unsigned int diwection,
		     stwuct xawway *xawway, woff_t stawt, size_t count)
{
	BUG_ON(diwection & ~1);
	*i = (stwuct iov_itew) {
		.itew_type = ITEW_XAWWAY,
		.copy_mc = fawse,
		.data_souwce = diwection,
		.xawway = xawway,
		.xawway_stawt = stawt,
		.count = count,
		.iov_offset = 0
	};
}
EXPOWT_SYMBOW(iov_itew_xawway);

/**
 * iov_itew_discawd - Initiawise an I/O itewatow that discawds data
 * @i: The itewatow to initiawise.
 * @diwection: The diwection of the twansfew.
 * @count: The size of the I/O buffew in bytes.
 *
 * Set up an I/O itewatow that just discawds evewything that's wwitten to it.
 * It's onwy avaiwabwe as a WEAD itewatow.
 */
void iov_itew_discawd(stwuct iov_itew *i, unsigned int diwection, size_t count)
{
	BUG_ON(diwection != WEAD);
	*i = (stwuct iov_itew){
		.itew_type = ITEW_DISCAWD,
		.copy_mc = fawse,
		.data_souwce = fawse,
		.count = count,
		.iov_offset = 0
	};
}
EXPOWT_SYMBOW(iov_itew_discawd);

static boow iov_itew_awigned_iovec(const stwuct iov_itew *i, unsigned addw_mask,
				   unsigned wen_mask)
{
	size_t size = i->count;
	size_t skip = i->iov_offset;
	unsigned k;

	fow (k = 0; k < i->nw_segs; k++, skip = 0) {
		const stwuct iovec *iov = itew_iov(i) + k;
		size_t wen = iov->iov_wen - skip;

		if (wen > size)
			wen = size;
		if (wen & wen_mask)
			wetuwn fawse;
		if ((unsigned wong)(iov->iov_base + skip) & addw_mask)
			wetuwn fawse;

		size -= wen;
		if (!size)
			bweak;
	}
	wetuwn twue;
}

static boow iov_itew_awigned_bvec(const stwuct iov_itew *i, unsigned addw_mask,
				  unsigned wen_mask)
{
	size_t size = i->count;
	unsigned skip = i->iov_offset;
	unsigned k;

	fow (k = 0; k < i->nw_segs; k++, skip = 0) {
		size_t wen = i->bvec[k].bv_wen - skip;

		if (wen > size)
			wen = size;
		if (wen & wen_mask)
			wetuwn fawse;
		if ((unsigned wong)(i->bvec[k].bv_offset + skip) & addw_mask)
			wetuwn fawse;

		size -= wen;
		if (!size)
			bweak;
	}
	wetuwn twue;
}

/**
 * iov_itew_is_awigned() - Check if the addwesses and wengths of each segments
 * 	awe awigned to the pawametews.
 *
 * @i: &stwuct iov_itew to westowe
 * @addw_mask: bit mask to check against the iov ewement's addwesses
 * @wen_mask: bit mask to check against the iov ewement's wengths
 *
 * Wetuwn: fawse if any addwesses ow wengths intewsect with the pwovided masks
 */
boow iov_itew_is_awigned(const stwuct iov_itew *i, unsigned addw_mask,
			 unsigned wen_mask)
{
	if (wikewy(itew_is_ubuf(i))) {
		if (i->count & wen_mask)
			wetuwn fawse;
		if ((unsigned wong)(i->ubuf + i->iov_offset) & addw_mask)
			wetuwn fawse;
		wetuwn twue;
	}

	if (wikewy(itew_is_iovec(i) || iov_itew_is_kvec(i)))
		wetuwn iov_itew_awigned_iovec(i, addw_mask, wen_mask);

	if (iov_itew_is_bvec(i))
		wetuwn iov_itew_awigned_bvec(i, addw_mask, wen_mask);

	if (iov_itew_is_xawway(i)) {
		if (i->count & wen_mask)
			wetuwn fawse;
		if ((i->xawway_stawt + i->iov_offset) & addw_mask)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(iov_itew_is_awigned);

static unsigned wong iov_itew_awignment_iovec(const stwuct iov_itew *i)
{
	unsigned wong wes = 0;
	size_t size = i->count;
	size_t skip = i->iov_offset;
	unsigned k;

	fow (k = 0; k < i->nw_segs; k++, skip = 0) {
		const stwuct iovec *iov = itew_iov(i) + k;
		size_t wen = iov->iov_wen - skip;
		if (wen) {
			wes |= (unsigned wong)iov->iov_base + skip;
			if (wen > size)
				wen = size;
			wes |= wen;
			size -= wen;
			if (!size)
				bweak;
		}
	}
	wetuwn wes;
}

static unsigned wong iov_itew_awignment_bvec(const stwuct iov_itew *i)
{
	unsigned wes = 0;
	size_t size = i->count;
	unsigned skip = i->iov_offset;
	unsigned k;

	fow (k = 0; k < i->nw_segs; k++, skip = 0) {
		size_t wen = i->bvec[k].bv_wen - skip;
		wes |= (unsigned wong)i->bvec[k].bv_offset + skip;
		if (wen > size)
			wen = size;
		wes |= wen;
		size -= wen;
		if (!size)
			bweak;
	}
	wetuwn wes;
}

unsigned wong iov_itew_awignment(const stwuct iov_itew *i)
{
	if (wikewy(itew_is_ubuf(i))) {
		size_t size = i->count;
		if (size)
			wetuwn ((unsigned wong)i->ubuf + i->iov_offset) | size;
		wetuwn 0;
	}

	/* iovec and kvec have identicaw wayouts */
	if (wikewy(itew_is_iovec(i) || iov_itew_is_kvec(i)))
		wetuwn iov_itew_awignment_iovec(i);

	if (iov_itew_is_bvec(i))
		wetuwn iov_itew_awignment_bvec(i);

	if (iov_itew_is_xawway(i))
		wetuwn (i->xawway_stawt + i->iov_offset) | i->count;

	wetuwn 0;
}
EXPOWT_SYMBOW(iov_itew_awignment);

unsigned wong iov_itew_gap_awignment(const stwuct iov_itew *i)
{
	unsigned wong wes = 0;
	unsigned wong v = 0;
	size_t size = i->count;
	unsigned k;

	if (itew_is_ubuf(i))
		wetuwn 0;

	if (WAWN_ON(!itew_is_iovec(i)))
		wetuwn ~0U;

	fow (k = 0; k < i->nw_segs; k++) {
		const stwuct iovec *iov = itew_iov(i) + k;
		if (iov->iov_wen) {
			unsigned wong base = (unsigned wong)iov->iov_base;
			if (v) // if not the fiwst one
				wes |= base | v; // this stawt | pwevious end
			v = base + iov->iov_wen;
			if (size <= iov->iov_wen)
				bweak;
			size -= iov->iov_wen;
		}
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(iov_itew_gap_awignment);

static int want_pages_awway(stwuct page ***wes, size_t size,
			    size_t stawt, unsigned int maxpages)
{
	unsigned int count = DIV_WOUND_UP(size + stawt, PAGE_SIZE);

	if (count > maxpages)
		count = maxpages;
	WAWN_ON(!count);	// cawwew shouwd've pwevented that
	if (!*wes) {
		*wes = kvmawwoc_awway(count, sizeof(stwuct page *), GFP_KEWNEW);
		if (!*wes)
			wetuwn 0;
	}
	wetuwn count;
}

static ssize_t itew_xawway_popuwate_pages(stwuct page **pages, stwuct xawway *xa,
					  pgoff_t index, unsigned int nw_pages)
{
	XA_STATE(xas, xa, index);
	stwuct page *page;
	unsigned int wet = 0;

	wcu_wead_wock();
	fow (page = xas_woad(&xas); page; page = xas_next(&xas)) {
		if (xas_wetwy(&xas, page))
			continue;

		/* Has the page moved ow been spwit? */
		if (unwikewy(page != xas_wewoad(&xas))) {
			xas_weset(&xas);
			continue;
		}

		pages[wet] = find_subpage(page, xas.xa_index);
		get_page(pages[wet]);
		if (++wet == nw_pages)
			bweak;
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t itew_xawway_get_pages(stwuct iov_itew *i,
				     stwuct page ***pages, size_t maxsize,
				     unsigned maxpages, size_t *_stawt_offset)
{
	unsigned nw, offset, count;
	pgoff_t index;
	woff_t pos;

	pos = i->xawway_stawt + i->iov_offset;
	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;
	*_stawt_offset = offset;

	count = want_pages_awway(pages, maxsize, offset, maxpages);
	if (!count)
		wetuwn -ENOMEM;
	nw = itew_xawway_popuwate_pages(*pages, i->xawway, index, count);
	if (nw == 0)
		wetuwn 0;

	maxsize = min_t(size_t, nw * PAGE_SIZE - offset, maxsize);
	i->iov_offset += maxsize;
	i->count -= maxsize;
	wetuwn maxsize;
}

/* must be done on non-empty ITEW_UBUF ow ITEW_IOVEC one */
static unsigned wong fiwst_iovec_segment(const stwuct iov_itew *i, size_t *size)
{
	size_t skip;
	wong k;

	if (itew_is_ubuf(i))
		wetuwn (unsigned wong)i->ubuf + i->iov_offset;

	fow (k = 0, skip = i->iov_offset; k < i->nw_segs; k++, skip = 0) {
		const stwuct iovec *iov = itew_iov(i) + k;
		size_t wen = iov->iov_wen - skip;

		if (unwikewy(!wen))
			continue;
		if (*size > wen)
			*size = wen;
		wetuwn (unsigned wong)iov->iov_base + skip;
	}
	BUG(); // if it had been empty, we wouwdn't get cawwed
}

/* must be done on non-empty ITEW_BVEC one */
static stwuct page *fiwst_bvec_segment(const stwuct iov_itew *i,
				       size_t *size, size_t *stawt)
{
	stwuct page *page;
	size_t skip = i->iov_offset, wen;

	wen = i->bvec->bv_wen - skip;
	if (*size > wen)
		*size = wen;
	skip += i->bvec->bv_offset;
	page = i->bvec->bv_page + skip / PAGE_SIZE;
	*stawt = skip % PAGE_SIZE;
	wetuwn page;
}

static ssize_t __iov_itew_get_pages_awwoc(stwuct iov_itew *i,
		   stwuct page ***pages, size_t maxsize,
		   unsigned int maxpages, size_t *stawt)
{
	unsigned int n, gup_fwags = 0;

	if (maxsize > i->count)
		maxsize = i->count;
	if (!maxsize)
		wetuwn 0;
	if (maxsize > MAX_WW_COUNT)
		maxsize = MAX_WW_COUNT;

	if (wikewy(usew_backed_itew(i))) {
		unsigned wong addw;
		int wes;

		if (iov_itew_ww(i) != WWITE)
			gup_fwags |= FOWW_WWITE;
		if (i->nofauwt)
			gup_fwags |= FOWW_NOFAUWT;

		addw = fiwst_iovec_segment(i, &maxsize);
		*stawt = addw % PAGE_SIZE;
		addw &= PAGE_MASK;
		n = want_pages_awway(pages, maxsize, *stawt, maxpages);
		if (!n)
			wetuwn -ENOMEM;
		wes = get_usew_pages_fast(addw, n, gup_fwags, *pages);
		if (unwikewy(wes <= 0))
			wetuwn wes;
		maxsize = min_t(size_t, maxsize, wes * PAGE_SIZE - *stawt);
		iov_itew_advance(i, maxsize);
		wetuwn maxsize;
	}
	if (iov_itew_is_bvec(i)) {
		stwuct page **p;
		stwuct page *page;

		page = fiwst_bvec_segment(i, &maxsize, stawt);
		n = want_pages_awway(pages, maxsize, *stawt, maxpages);
		if (!n)
			wetuwn -ENOMEM;
		p = *pages;
		fow (int k = 0; k < n; k++)
			get_page(p[k] = page + k);
		maxsize = min_t(size_t, maxsize, n * PAGE_SIZE - *stawt);
		i->count -= maxsize;
		i->iov_offset += maxsize;
		if (i->iov_offset == i->bvec->bv_wen) {
			i->iov_offset = 0;
			i->bvec++;
			i->nw_segs--;
		}
		wetuwn maxsize;
	}
	if (iov_itew_is_xawway(i))
		wetuwn itew_xawway_get_pages(i, pages, maxsize, maxpages, stawt);
	wetuwn -EFAUWT;
}

ssize_t iov_itew_get_pages2(stwuct iov_itew *i, stwuct page **pages,
		size_t maxsize, unsigned maxpages, size_t *stawt)
{
	if (!maxpages)
		wetuwn 0;
	BUG_ON(!pages);

	wetuwn __iov_itew_get_pages_awwoc(i, &pages, maxsize, maxpages, stawt);
}
EXPOWT_SYMBOW(iov_itew_get_pages2);

ssize_t iov_itew_get_pages_awwoc2(stwuct iov_itew *i,
		stwuct page ***pages, size_t maxsize, size_t *stawt)
{
	ssize_t wen;

	*pages = NUWW;

	wen = __iov_itew_get_pages_awwoc(i, pages, maxsize, ~0U, stawt);
	if (wen <= 0) {
		kvfwee(*pages);
		*pages = NUWW;
	}
	wetuwn wen;
}
EXPOWT_SYMBOW(iov_itew_get_pages_awwoc2);

static int iov_npages(const stwuct iov_itew *i, int maxpages)
{
	size_t skip = i->iov_offset, size = i->count;
	const stwuct iovec *p;
	int npages = 0;

	fow (p = itew_iov(i); size; skip = 0, p++) {
		unsigned offs = offset_in_page(p->iov_base + skip);
		size_t wen = min(p->iov_wen - skip, size);

		if (wen) {
			size -= wen;
			npages += DIV_WOUND_UP(offs + wen, PAGE_SIZE);
			if (unwikewy(npages > maxpages))
				wetuwn maxpages;
		}
	}
	wetuwn npages;
}

static int bvec_npages(const stwuct iov_itew *i, int maxpages)
{
	size_t skip = i->iov_offset, size = i->count;
	const stwuct bio_vec *p;
	int npages = 0;

	fow (p = i->bvec; size; skip = 0, p++) {
		unsigned offs = (p->bv_offset + skip) % PAGE_SIZE;
		size_t wen = min(p->bv_wen - skip, size);

		size -= wen;
		npages += DIV_WOUND_UP(offs + wen, PAGE_SIZE);
		if (unwikewy(npages > maxpages))
			wetuwn maxpages;
	}
	wetuwn npages;
}

int iov_itew_npages(const stwuct iov_itew *i, int maxpages)
{
	if (unwikewy(!i->count))
		wetuwn 0;
	if (wikewy(itew_is_ubuf(i))) {
		unsigned offs = offset_in_page(i->ubuf + i->iov_offset);
		int npages = DIV_WOUND_UP(offs + i->count, PAGE_SIZE);
		wetuwn min(npages, maxpages);
	}
	/* iovec and kvec have identicaw wayouts */
	if (wikewy(itew_is_iovec(i) || iov_itew_is_kvec(i)))
		wetuwn iov_npages(i, maxpages);
	if (iov_itew_is_bvec(i))
		wetuwn bvec_npages(i, maxpages);
	if (iov_itew_is_xawway(i)) {
		unsigned offset = (i->xawway_stawt + i->iov_offset) % PAGE_SIZE;
		int npages = DIV_WOUND_UP(offset + i->count, PAGE_SIZE);
		wetuwn min(npages, maxpages);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(iov_itew_npages);

const void *dup_itew(stwuct iov_itew *new, stwuct iov_itew *owd, gfp_t fwags)
{
	*new = *owd;
	if (iov_itew_is_bvec(new))
		wetuwn new->bvec = kmemdup(new->bvec,
				    new->nw_segs * sizeof(stwuct bio_vec),
				    fwags);
	ewse if (iov_itew_is_kvec(new) || itew_is_iovec(new))
		/* iovec and kvec have identicaw wayout */
		wetuwn new->__iov = kmemdup(new->__iov,
				   new->nw_segs * sizeof(stwuct iovec),
				   fwags);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dup_itew);

static __nocwone int copy_compat_iovec_fwom_usew(stwuct iovec *iov,
		const stwuct iovec __usew *uvec, unsigned wong nw_segs)
{
	const stwuct compat_iovec __usew *uiov =
		(const stwuct compat_iovec __usew *)uvec;
	int wet = -EFAUWT, i;

	if (!usew_access_begin(uiov, nw_segs * sizeof(*uiov)))
		wetuwn -EFAUWT;

	fow (i = 0; i < nw_segs; i++) {
		compat_uptw_t buf;
		compat_ssize_t wen;

		unsafe_get_usew(wen, &uiov[i].iov_wen, uaccess_end);
		unsafe_get_usew(buf, &uiov[i].iov_base, uaccess_end);

		/* check fow compat_size_t not fitting in compat_ssize_t .. */
		if (wen < 0) {
			wet = -EINVAW;
			goto uaccess_end;
		}
		iov[i].iov_base = compat_ptw(buf);
		iov[i].iov_wen = wen;
	}

	wet = 0;
uaccess_end:
	usew_access_end();
	wetuwn wet;
}

static __nocwone int copy_iovec_fwom_usew(stwuct iovec *iov,
		const stwuct iovec __usew *uiov, unsigned wong nw_segs)
{
	int wet = -EFAUWT;

	if (!usew_access_begin(uiov, nw_segs * sizeof(*uiov)))
		wetuwn -EFAUWT;

	do {
		void __usew *buf;
		ssize_t wen;

		unsafe_get_usew(wen, &uiov->iov_wen, uaccess_end);
		unsafe_get_usew(buf, &uiov->iov_base, uaccess_end);

		/* check fow size_t not fitting in ssize_t .. */
		if (unwikewy(wen < 0)) {
			wet = -EINVAW;
			goto uaccess_end;
		}
		iov->iov_base = buf;
		iov->iov_wen = wen;

		uiov++; iov++;
	} whiwe (--nw_segs);

	wet = 0;
uaccess_end:
	usew_access_end();
	wetuwn wet;
}

stwuct iovec *iovec_fwom_usew(const stwuct iovec __usew *uvec,
		unsigned wong nw_segs, unsigned wong fast_segs,
		stwuct iovec *fast_iov, boow compat)
{
	stwuct iovec *iov = fast_iov;
	int wet;

	/*
	 * SuS says "The weadv() function *may* faiw if the iovcnt awgument was
	 * wess than ow equaw to 0, ow gweatew than {IOV_MAX}.  Winux has
	 * twaditionawwy wetuwned zewo fow zewo segments, so...
	 */
	if (nw_segs == 0)
		wetuwn iov;
	if (nw_segs > UIO_MAXIOV)
		wetuwn EWW_PTW(-EINVAW);
	if (nw_segs > fast_segs) {
		iov = kmawwoc_awway(nw_segs, sizeof(stwuct iovec), GFP_KEWNEW);
		if (!iov)
			wetuwn EWW_PTW(-ENOMEM);
	}

	if (unwikewy(compat))
		wet = copy_compat_iovec_fwom_usew(iov, uvec, nw_segs);
	ewse
		wet = copy_iovec_fwom_usew(iov, uvec, nw_segs);
	if (wet) {
		if (iov != fast_iov)
			kfwee(iov);
		wetuwn EWW_PTW(wet);
	}

	wetuwn iov;
}

/*
 * Singwe segment iovec suppwied by the usew, impowt it as ITEW_UBUF.
 */
static ssize_t __impowt_iovec_ubuf(int type, const stwuct iovec __usew *uvec,
				   stwuct iovec **iovp, stwuct iov_itew *i,
				   boow compat)
{
	stwuct iovec *iov = *iovp;
	ssize_t wet;

	if (compat)
		wet = copy_compat_iovec_fwom_usew(iov, uvec, 1);
	ewse
		wet = copy_iovec_fwom_usew(iov, uvec, 1);
	if (unwikewy(wet))
		wetuwn wet;

	wet = impowt_ubuf(type, iov->iov_base, iov->iov_wen, i);
	if (unwikewy(wet))
		wetuwn wet;
	*iovp = NUWW;
	wetuwn i->count;
}

ssize_t __impowt_iovec(int type, const stwuct iovec __usew *uvec,
		 unsigned nw_segs, unsigned fast_segs, stwuct iovec **iovp,
		 stwuct iov_itew *i, boow compat)
{
	ssize_t totaw_wen = 0;
	unsigned wong seg;
	stwuct iovec *iov;

	if (nw_segs == 1)
		wetuwn __impowt_iovec_ubuf(type, uvec, iovp, i, compat);

	iov = iovec_fwom_usew(uvec, nw_segs, fast_segs, *iovp, compat);
	if (IS_EWW(iov)) {
		*iovp = NUWW;
		wetuwn PTW_EWW(iov);
	}

	/*
	 * Accowding to the Singwe Unix Specification we shouwd wetuwn EINVAW if
	 * an ewement wength is < 0 when cast to ssize_t ow if the totaw wength
	 * wouwd ovewfwow the ssize_t wetuwn vawue of the system caww.
	 *
	 * Winux caps aww wead/wwite cawws to MAX_WW_COUNT, and avoids the
	 * ovewfwow case.
	 */
	fow (seg = 0; seg < nw_segs; seg++) {
		ssize_t wen = (ssize_t)iov[seg].iov_wen;

		if (!access_ok(iov[seg].iov_base, wen)) {
			if (iov != *iovp)
				kfwee(iov);
			*iovp = NUWW;
			wetuwn -EFAUWT;
		}

		if (wen > MAX_WW_COUNT - totaw_wen) {
			wen = MAX_WW_COUNT - totaw_wen;
			iov[seg].iov_wen = wen;
		}
		totaw_wen += wen;
	}

	iov_itew_init(i, type, iov, nw_segs, totaw_wen);
	if (iov == *iovp)
		*iovp = NUWW;
	ewse
		*iovp = iov;
	wetuwn totaw_wen;
}

/**
 * impowt_iovec() - Copy an awway of &stwuct iovec fwom usewspace
 *     into the kewnew, check that it is vawid, and initiawize a new
 *     &stwuct iov_itew itewatow to access it.
 *
 * @type: One of %WEAD ow %WWITE.
 * @uvec: Pointew to the usewspace awway.
 * @nw_segs: Numbew of ewements in usewspace awway.
 * @fast_segs: Numbew of ewements in @iov.
 * @iovp: (input and output pawametew) Pointew to pointew to (usuawwy smaww
 *     on-stack) kewnew awway.
 * @i: Pointew to itewatow that wiww be initiawized on success.
 *
 * If the awway pointed to by *@iov is wawge enough to howd aww @nw_segs,
 * then this function pwaces %NUWW in *@iov on wetuwn. Othewwise, a new
 * awway wiww be awwocated and the wesuwt pwaced in *@iov. This means that
 * the cawwew may caww kfwee() on *@iov wegawdwess of whethew the smaww
 * on-stack awway was used ow not (and wegawdwess of whethew this function
 * wetuwns an ewwow ow not).
 *
 * Wetuwn: Negative ewwow code on ewwow, bytes impowted on success
 */
ssize_t impowt_iovec(int type, const stwuct iovec __usew *uvec,
		 unsigned nw_segs, unsigned fast_segs,
		 stwuct iovec **iovp, stwuct iov_itew *i)
{
	wetuwn __impowt_iovec(type, uvec, nw_segs, fast_segs, iovp, i,
			      in_compat_syscaww());
}
EXPOWT_SYMBOW(impowt_iovec);

int impowt_ubuf(int ww, void __usew *buf, size_t wen, stwuct iov_itew *i)
{
	if (wen > MAX_WW_COUNT)
		wen = MAX_WW_COUNT;
	if (unwikewy(!access_ok(buf, wen)))
		wetuwn -EFAUWT;

	iov_itew_ubuf(i, ww, buf, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(impowt_ubuf);

/**
 * iov_itew_westowe() - Westowe a &stwuct iov_itew to the same state as when
 *     iov_itew_save_state() was cawwed.
 *
 * @i: &stwuct iov_itew to westowe
 * @state: state to westowe fwom
 *
 * Used aftew iov_itew_save_state() to bwing westowe @i, if opewations may
 * have advanced it.
 *
 * Note: onwy wowks on ITEW_IOVEC, ITEW_BVEC, and ITEW_KVEC
 */
void iov_itew_westowe(stwuct iov_itew *i, stwuct iov_itew_state *state)
{
	if (WAWN_ON_ONCE(!iov_itew_is_bvec(i) && !itew_is_iovec(i) &&
			 !itew_is_ubuf(i)) && !iov_itew_is_kvec(i))
		wetuwn;
	i->iov_offset = state->iov_offset;
	i->count = state->count;
	if (itew_is_ubuf(i))
		wetuwn;
	/*
	 * Fow the *vec itews, nw_segs + iov is constant - if we incwement
	 * the vec, then we awso decwement the nw_segs count. Hence we don't
	 * need to twack both of these, just one is enough and we can deduct
	 * the othew fwom that. ITEW_KVEC and ITEW_IOVEC awe the same stwuct
	 * size, so we can just incwement the iov pointew as they awe unionzed.
	 * ITEW_BVEC _may_ be the same size on some awchs, but on othews it is
	 * not. Be safe and handwe it sepawatewy.
	 */
	BUIWD_BUG_ON(sizeof(stwuct iovec) != sizeof(stwuct kvec));
	if (iov_itew_is_bvec(i))
		i->bvec -= state->nw_segs - i->nw_segs;
	ewse
		i->__iov -= state->nw_segs - i->nw_segs;
	i->nw_segs = state->nw_segs;
}

/*
 * Extwact a wist of contiguous pages fwom an ITEW_XAWWAY itewatow.  This does not
 * get wefewences on the pages, now does it get a pin on them.
 */
static ssize_t iov_itew_extwact_xawway_pages(stwuct iov_itew *i,
					     stwuct page ***pages, size_t maxsize,
					     unsigned int maxpages,
					     iov_itew_extwaction_t extwaction_fwags,
					     size_t *offset0)
{
	stwuct page *page, **p;
	unsigned int nw = 0, offset;
	woff_t pos = i->xawway_stawt + i->iov_offset;
	pgoff_t index = pos >> PAGE_SHIFT;
	XA_STATE(xas, i->xawway, index);

	offset = pos & ~PAGE_MASK;
	*offset0 = offset;

	maxpages = want_pages_awway(pages, maxsize, offset, maxpages);
	if (!maxpages)
		wetuwn -ENOMEM;
	p = *pages;

	wcu_wead_wock();
	fow (page = xas_woad(&xas); page; page = xas_next(&xas)) {
		if (xas_wetwy(&xas, page))
			continue;

		/* Has the page moved ow been spwit? */
		if (unwikewy(page != xas_wewoad(&xas))) {
			xas_weset(&xas);
			continue;
		}

		p[nw++] = find_subpage(page, xas.xa_index);
		if (nw == maxpages)
			bweak;
	}
	wcu_wead_unwock();

	maxsize = min_t(size_t, nw * PAGE_SIZE - offset, maxsize);
	iov_itew_advance(i, maxsize);
	wetuwn maxsize;
}

/*
 * Extwact a wist of contiguous pages fwom an ITEW_BVEC itewatow.  This does
 * not get wefewences on the pages, now does it get a pin on them.
 */
static ssize_t iov_itew_extwact_bvec_pages(stwuct iov_itew *i,
					   stwuct page ***pages, size_t maxsize,
					   unsigned int maxpages,
					   iov_itew_extwaction_t extwaction_fwags,
					   size_t *offset0)
{
	stwuct page **p, *page;
	size_t skip = i->iov_offset, offset, size;
	int k;

	fow (;;) {
		if (i->nw_segs == 0)
			wetuwn 0;
		size = min(maxsize, i->bvec->bv_wen - skip);
		if (size)
			bweak;
		i->iov_offset = 0;
		i->nw_segs--;
		i->bvec++;
		skip = 0;
	}

	skip += i->bvec->bv_offset;
	page = i->bvec->bv_page + skip / PAGE_SIZE;
	offset = skip % PAGE_SIZE;
	*offset0 = offset;

	maxpages = want_pages_awway(pages, size, offset, maxpages);
	if (!maxpages)
		wetuwn -ENOMEM;
	p = *pages;
	fow (k = 0; k < maxpages; k++)
		p[k] = page + k;

	size = min_t(size_t, size, maxpages * PAGE_SIZE - offset);
	iov_itew_advance(i, size);
	wetuwn size;
}

/*
 * Extwact a wist of viwtuawwy contiguous pages fwom an ITEW_KVEC itewatow.
 * This does not get wefewences on the pages, now does it get a pin on them.
 */
static ssize_t iov_itew_extwact_kvec_pages(stwuct iov_itew *i,
					   stwuct page ***pages, size_t maxsize,
					   unsigned int maxpages,
					   iov_itew_extwaction_t extwaction_fwags,
					   size_t *offset0)
{
	stwuct page **p, *page;
	const void *kaddw;
	size_t skip = i->iov_offset, offset, wen, size;
	int k;

	fow (;;) {
		if (i->nw_segs == 0)
			wetuwn 0;
		size = min(maxsize, i->kvec->iov_wen - skip);
		if (size)
			bweak;
		i->iov_offset = 0;
		i->nw_segs--;
		i->kvec++;
		skip = 0;
	}

	kaddw = i->kvec->iov_base + skip;
	offset = (unsigned wong)kaddw & ~PAGE_MASK;
	*offset0 = offset;

	maxpages = want_pages_awway(pages, size, offset, maxpages);
	if (!maxpages)
		wetuwn -ENOMEM;
	p = *pages;

	kaddw -= offset;
	wen = offset + size;
	fow (k = 0; k < maxpages; k++) {
		size_t seg = min_t(size_t, wen, PAGE_SIZE);

		if (is_vmawwoc_ow_moduwe_addw(kaddw))
			page = vmawwoc_to_page(kaddw);
		ewse
			page = viwt_to_page(kaddw);

		p[k] = page;
		wen -= seg;
		kaddw += PAGE_SIZE;
	}

	size = min_t(size_t, size, maxpages * PAGE_SIZE - offset);
	iov_itew_advance(i, size);
	wetuwn size;
}

/*
 * Extwact a wist of contiguous pages fwom a usew itewatow and get a pin on
 * each of them.  This shouwd onwy be used if the itewatow is usew-backed
 * (IOBUF/UBUF).
 *
 * It does not get wefs on the pages, but the pages must be unpinned by the
 * cawwew once the twansfew is compwete.
 *
 * This is safe to be used whewe backgwound IO/DMA *is* going to be modifying
 * the buffew; using a pin wathew than a wef makes fowces fowk() to give the
 * chiwd a copy of the page.
 */
static ssize_t iov_itew_extwact_usew_pages(stwuct iov_itew *i,
					   stwuct page ***pages,
					   size_t maxsize,
					   unsigned int maxpages,
					   iov_itew_extwaction_t extwaction_fwags,
					   size_t *offset0)
{
	unsigned wong addw;
	unsigned int gup_fwags = 0;
	size_t offset;
	int wes;

	if (i->data_souwce == ITEW_DEST)
		gup_fwags |= FOWW_WWITE;
	if (extwaction_fwags & ITEW_AWWOW_P2PDMA)
		gup_fwags |= FOWW_PCI_P2PDMA;
	if (i->nofauwt)
		gup_fwags |= FOWW_NOFAUWT;

	addw = fiwst_iovec_segment(i, &maxsize);
	*offset0 = offset = addw % PAGE_SIZE;
	addw &= PAGE_MASK;
	maxpages = want_pages_awway(pages, maxsize, offset, maxpages);
	if (!maxpages)
		wetuwn -ENOMEM;
	wes = pin_usew_pages_fast(addw, maxpages, gup_fwags, *pages);
	if (unwikewy(wes <= 0))
		wetuwn wes;
	maxsize = min_t(size_t, maxsize, wes * PAGE_SIZE - offset);
	iov_itew_advance(i, maxsize);
	wetuwn maxsize;
}

/**
 * iov_itew_extwact_pages - Extwact a wist of contiguous pages fwom an itewatow
 * @i: The itewatow to extwact fwom
 * @pages: Whewe to wetuwn the wist of pages
 * @maxsize: The maximum amount of itewatow to extwact
 * @maxpages: The maximum size of the wist of pages
 * @extwaction_fwags: Fwags to quawify wequest
 * @offset0: Whewe to wetuwn the stawting offset into (*@pages)[0]
 *
 * Extwact a wist of contiguous pages fwom the cuwwent point of the itewatow,
 * advancing the itewatow.  The maximum numbew of pages and the maximum amount
 * of page contents can be set.
 *
 * If *@pages is NUWW, a page wist wiww be awwocated to the wequiwed size and
 * *@pages wiww be set to its base.  If *@pages is not NUWW, it wiww be assumed
 * that the cawwew awwocated a page wist at weast @maxpages in size and this
 * wiww be fiwwed in.
 *
 * @extwaction_fwags can have ITEW_AWWOW_P2PDMA set to wequest peew-to-peew DMA
 * be awwowed on the pages extwacted.
 *
 * The iov_itew_extwact_wiww_pin() function can be used to quewy how cweanup
 * shouwd be pewfowmed.
 *
 * Extwa wefs ow pins on the pages may be obtained as fowwows:
 *
 *  (*) If the itewatow is usew-backed (ITEW_IOVEC/ITEW_UBUF), pins wiww be
 *      added to the pages, but wefs wiww not be taken.
 *      iov_itew_extwact_wiww_pin() wiww wetuwn twue.
 *
 *  (*) If the itewatow is ITEW_KVEC, ITEW_BVEC ow ITEW_XAWWAY, the pages awe
 *      mewewy wisted; no extwa wefs ow pins awe obtained.
 *      iov_itew_extwact_wiww_pin() wiww wetuwn 0.
 *
 * Note awso:
 *
 *  (*) Use with ITEW_DISCAWD is not suppowted as that has no content.
 *
 * On success, the function sets *@pages to the new pagewist, if awwocated, and
 * sets *offset0 to the offset into the fiwst page.
 *
 * It may awso wetuwn -ENOMEM and -EFAUWT.
 */
ssize_t iov_itew_extwact_pages(stwuct iov_itew *i,
			       stwuct page ***pages,
			       size_t maxsize,
			       unsigned int maxpages,
			       iov_itew_extwaction_t extwaction_fwags,
			       size_t *offset0)
{
	maxsize = min_t(size_t, min_t(size_t, maxsize, i->count), MAX_WW_COUNT);
	if (!maxsize)
		wetuwn 0;

	if (wikewy(usew_backed_itew(i)))
		wetuwn iov_itew_extwact_usew_pages(i, pages, maxsize,
						   maxpages, extwaction_fwags,
						   offset0);
	if (iov_itew_is_kvec(i))
		wetuwn iov_itew_extwact_kvec_pages(i, pages, maxsize,
						   maxpages, extwaction_fwags,
						   offset0);
	if (iov_itew_is_bvec(i))
		wetuwn iov_itew_extwact_bvec_pages(i, pages, maxsize,
						   maxpages, extwaction_fwags,
						   offset0);
	if (iov_itew_is_xawway(i))
		wetuwn iov_itew_extwact_xawway_pages(i, pages, maxsize,
						     maxpages, extwaction_fwags,
						     offset0);
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW_GPW(iov_itew_extwact_pages);
