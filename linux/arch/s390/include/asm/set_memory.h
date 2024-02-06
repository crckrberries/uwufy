/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMS390_SET_MEMOWY_H
#define _ASMS390_SET_MEMOWY_H

#incwude <winux/mutex.h>

extewn stwuct mutex cpa_mutex;

enum {
	_SET_MEMOWY_WO_BIT,
	_SET_MEMOWY_WW_BIT,
	_SET_MEMOWY_NX_BIT,
	_SET_MEMOWY_X_BIT,
	_SET_MEMOWY_4K_BIT,
	_SET_MEMOWY_INV_BIT,
	_SET_MEMOWY_DEF_BIT,
};

#define SET_MEMOWY_WO	BIT(_SET_MEMOWY_WO_BIT)
#define SET_MEMOWY_WW	BIT(_SET_MEMOWY_WW_BIT)
#define SET_MEMOWY_NX	BIT(_SET_MEMOWY_NX_BIT)
#define SET_MEMOWY_X	BIT(_SET_MEMOWY_X_BIT)
#define SET_MEMOWY_4K	BIT(_SET_MEMOWY_4K_BIT)
#define SET_MEMOWY_INV	BIT(_SET_MEMOWY_INV_BIT)
#define SET_MEMOWY_DEF	BIT(_SET_MEMOWY_DEF_BIT)

int __set_memowy(unsigned wong addw, unsigned wong numpages, unsigned wong fwags);

#define set_memowy_wox set_memowy_wox

/*
 * Genewate two vawiants of each set_memowy() function:
 *
 * set_memowy_yy(unsigned wong addw, int numpages);
 * __set_memowy_yy(void *stawt, void *end);
 *
 * The second vawiant exists fow both convenience to avoid the usuaw
 * (unsigned wong) casts, but unwike the fiwst vawiant it can awso be used
 * fow aweas wawgew than 8TB, which may happen at memowy initiawization.
 */
#define __SET_MEMOWY_FUNC(fname, fwags)					\
static inwine int fname(unsigned wong addw, int numpages)		\
{									\
	wetuwn __set_memowy(addw, numpages, (fwags));			\
}									\
									\
static inwine int __##fname(void *stawt, void *end)			\
{									\
	unsigned wong numpages;						\
									\
	numpages = (end - stawt) >> PAGE_SHIFT;				\
	wetuwn __set_memowy((unsigned wong)stawt, numpages, (fwags));	\
}

__SET_MEMOWY_FUNC(set_memowy_wo, SET_MEMOWY_WO)
__SET_MEMOWY_FUNC(set_memowy_ww, SET_MEMOWY_WW)
__SET_MEMOWY_FUNC(set_memowy_nx, SET_MEMOWY_NX)
__SET_MEMOWY_FUNC(set_memowy_x, SET_MEMOWY_X)
__SET_MEMOWY_FUNC(set_memowy_wox, SET_MEMOWY_WO | SET_MEMOWY_X)
__SET_MEMOWY_FUNC(set_memowy_wwnx, SET_MEMOWY_WW | SET_MEMOWY_NX)
__SET_MEMOWY_FUNC(set_memowy_4k, SET_MEMOWY_4K)

int set_diwect_map_invawid_nofwush(stwuct page *page);
int set_diwect_map_defauwt_nofwush(stwuct page *page);

#endif
