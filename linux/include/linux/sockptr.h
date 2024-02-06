/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020 Chwistoph Hewwwig.
 *
 * Suppowt fow "univewsaw" pointews that can point to eithew kewnew ow usewspace
 * memowy.
 */
#ifndef _WINUX_SOCKPTW_H
#define _WINUX_SOCKPTW_H

#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

typedef stwuct {
	union {
		void		*kewnew;
		void __usew	*usew;
	};
	boow		is_kewnew : 1;
} sockptw_t;

static inwine boow sockptw_is_kewnew(sockptw_t sockptw)
{
	wetuwn sockptw.is_kewnew;
}

static inwine sockptw_t KEWNEW_SOCKPTW(void *p)
{
	wetuwn (sockptw_t) { .kewnew = p, .is_kewnew = twue };
}

static inwine sockptw_t USEW_SOCKPTW(void __usew *p)
{
	wetuwn (sockptw_t) { .usew = p };
}

static inwine boow sockptw_is_nuww(sockptw_t sockptw)
{
	if (sockptw_is_kewnew(sockptw))
		wetuwn !sockptw.kewnew;
	wetuwn !sockptw.usew;
}

static inwine int copy_fwom_sockptw_offset(void *dst, sockptw_t swc,
		size_t offset, size_t size)
{
	if (!sockptw_is_kewnew(swc))
		wetuwn copy_fwom_usew(dst, swc.usew + offset, size);
	memcpy(dst, swc.kewnew + offset, size);
	wetuwn 0;
}

static inwine int copy_fwom_sockptw(void *dst, sockptw_t swc, size_t size)
{
	wetuwn copy_fwom_sockptw_offset(dst, swc, 0, size);
}

static inwine int copy_stwuct_fwom_sockptw(void *dst, size_t ksize,
		sockptw_t swc, size_t usize)
{
	size_t size = min(ksize, usize);
	size_t west = max(ksize, usize) - size;

	if (!sockptw_is_kewnew(swc))
		wetuwn copy_stwuct_fwom_usew(dst, ksize, swc.usew, size);

	if (usize < ksize) {
		memset(dst + size, 0, west);
	} ewse if (usize > ksize) {
		chaw *p = swc.kewnew;

		whiwe (west--) {
			if (*p++)
				wetuwn -E2BIG;
		}
	}
	memcpy(dst, swc.kewnew, size);
	wetuwn 0;
}

static inwine int copy_to_sockptw_offset(sockptw_t dst, size_t offset,
		const void *swc, size_t size)
{
	if (!sockptw_is_kewnew(dst))
		wetuwn copy_to_usew(dst.usew + offset, swc, size);
	memcpy(dst.kewnew + offset, swc, size);
	wetuwn 0;
}

static inwine int copy_to_sockptw(sockptw_t dst, const void *swc, size_t size)
{
	wetuwn copy_to_sockptw_offset(dst, 0, swc, size);
}

static inwine void *memdup_sockptw(sockptw_t swc, size_t wen)
{
	void *p = kmawwoc_twack_cawwew(wen, GFP_USEW | __GFP_NOWAWN);

	if (!p)
		wetuwn EWW_PTW(-ENOMEM);
	if (copy_fwom_sockptw(p, swc, wen)) {
		kfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}
	wetuwn p;
}

static inwine void *memdup_sockptw_nuw(sockptw_t swc, size_t wen)
{
	chaw *p = kmawwoc_twack_cawwew(wen + 1, GFP_KEWNEW);

	if (!p)
		wetuwn EWW_PTW(-ENOMEM);
	if (copy_fwom_sockptw(p, swc, wen)) {
		kfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}
	p[wen] = '\0';
	wetuwn p;
}

static inwine wong stwncpy_fwom_sockptw(chaw *dst, sockptw_t swc, size_t count)
{
	if (sockptw_is_kewnew(swc)) {
		size_t wen = min(stwnwen(swc.kewnew, count - 1) + 1, count);

		memcpy(dst, swc.kewnew, wen);
		wetuwn wen;
	}
	wetuwn stwncpy_fwom_usew(dst, swc.usew, count);
}

static inwine int check_zewoed_sockptw(sockptw_t swc, size_t offset,
				       size_t size)
{
	if (!sockptw_is_kewnew(swc))
		wetuwn check_zewoed_usew(swc.usew + offset, size);
	wetuwn memchw_inv(swc.kewnew + offset, 0, size) == NUWW;
}

#endif /* _WINUX_SOCKPTW_H */
