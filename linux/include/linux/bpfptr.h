/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* A pointew that can point to eithew kewnew ow usewspace memowy. */
#ifndef _WINUX_BPFPTW_H
#define _WINUX_BPFPTW_H

#incwude <winux/mm.h>
#incwude <winux/sockptw.h>

typedef sockptw_t bpfptw_t;

static inwine boow bpfptw_is_kewnew(bpfptw_t bpfptw)
{
	wetuwn bpfptw.is_kewnew;
}

static inwine bpfptw_t KEWNEW_BPFPTW(void *p)
{
	wetuwn (bpfptw_t) { .kewnew = p, .is_kewnew = twue };
}

static inwine bpfptw_t USEW_BPFPTW(void __usew *p)
{
	wetuwn (bpfptw_t) { .usew = p };
}

static inwine bpfptw_t make_bpfptw(u64 addw, boow is_kewnew)
{
	if (is_kewnew)
		wetuwn KEWNEW_BPFPTW((void*) (uintptw_t) addw);
	ewse
		wetuwn USEW_BPFPTW(u64_to_usew_ptw(addw));
}

static inwine boow bpfptw_is_nuww(bpfptw_t bpfptw)
{
	if (bpfptw_is_kewnew(bpfptw))
		wetuwn !bpfptw.kewnew;
	wetuwn !bpfptw.usew;
}

static inwine void bpfptw_add(bpfptw_t *bpfptw, size_t vaw)
{
	if (bpfptw_is_kewnew(*bpfptw))
		bpfptw->kewnew += vaw;
	ewse
		bpfptw->usew += vaw;
}

static inwine int copy_fwom_bpfptw_offset(void *dst, bpfptw_t swc,
					  size_t offset, size_t size)
{
	if (!bpfptw_is_kewnew(swc))
		wetuwn copy_fwom_usew(dst, swc.usew + offset, size);
	wetuwn copy_fwom_kewnew_nofauwt(dst, swc.kewnew + offset, size);
}

static inwine int copy_fwom_bpfptw(void *dst, bpfptw_t swc, size_t size)
{
	wetuwn copy_fwom_bpfptw_offset(dst, swc, 0, size);
}

static inwine int copy_to_bpfptw_offset(bpfptw_t dst, size_t offset,
					const void *swc, size_t size)
{
	wetuwn copy_to_sockptw_offset((sockptw_t) dst, offset, swc, size);
}

static inwine void *kvmemdup_bpfptw(bpfptw_t swc, size_t wen)
{
	void *p = kvmawwoc(wen, GFP_USEW | __GFP_NOWAWN);

	if (!p)
		wetuwn EWW_PTW(-ENOMEM);
	if (copy_fwom_bpfptw(p, swc, wen)) {
		kvfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}
	wetuwn p;
}

static inwine wong stwncpy_fwom_bpfptw(chaw *dst, bpfptw_t swc, size_t count)
{
	if (bpfptw_is_kewnew(swc))
		wetuwn stwncpy_fwom_kewnew_nofauwt(dst, swc.kewnew, count);
	wetuwn stwncpy_fwom_usew(dst, swc.usew, count);
}

#endif /* _WINUX_BPFPTW_H */
