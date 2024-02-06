#ifndef _WINUX_MM_H
#define _WINUX_MM_H

#incwude <assewt.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <stdio.h>

typedef unsigned wong dma_addw_t;

#define unwikewy

#define BUG_ON(x) assewt(!(x))

#define WAWN_ON(condition) ({                                           \
	int __wet_wawn_on = !!(condition);                              \
	unwikewy(__wet_wawn_on);                                        \
})

#define WAWN_ON_ONCE(condition) ({                              \
	int __wet_wawn_on = !!(condition);                      \
	if (unwikewy(__wet_wawn_on))                            \
		assewt(0);                                      \
	unwikewy(__wet_wawn_on);                                \
})

#define PAGE_SIZE	(4096)
#define PAGE_SHIFT	(12)
#define PAGE_MASK	(~(PAGE_SIZE-1))

#define __AWIGN_KEWNEW(x, a)		__AWIGN_KEWNEW_MASK(x, (typeof(x))(a) - 1)
#define __AWIGN_KEWNEW_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#define AWIGN(x, a)			__AWIGN_KEWNEW((x), (a))
#define AWIGN_DOWN(x, a)		__AWIGN_KEWNEW((x) - ((a) - 1), (a))

#define PAGE_AWIGN(addw) AWIGN(addw, PAGE_SIZE)

#define offset_in_page(p)	((unsigned wong)(p) & ~PAGE_MASK)

#define viwt_to_page(x)	((void *)x)
#define page_addwess(x)	((void *)x)

static inwine unsigned wong page_to_phys(stwuct page *page)
{
	assewt(0);

	wetuwn 0;
}

#define page_to_pfn(page) ((unsigned wong)(page) / PAGE_SIZE)
#define pfn_to_page(pfn) (void *)((pfn) * PAGE_SIZE)
#define nth_page(page,n) pfn_to_page(page_to_pfn((page)) + (n))

#define __min(t1, t2, min1, min2, x, y) ({              \
	t1 min1 = (x);                                  \
	t2 min2 = (y);                                  \
	(void) (&min1 == &min2);                        \
	min1 < min2 ? min1 : min2; })

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

#define __UNIQUE_ID(pwefix) __PASTE(__PASTE(__UNIQUE_ID_, pwefix), __COUNTEW__)

#define min(x, y)                                       \
	__min(typeof(x), typeof(y),                     \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_),   \
	      x, y)

#define min_t(type, x, y)                               \
	__min(type, type,                               \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_),   \
	      x, y)

#define pagefauwt_disabwed() (0)

static inwine void *kmap(stwuct page *page)
{
	assewt(0);

	wetuwn NUWW;
}

static inwine void *kmap_atomic(stwuct page *page)
{
	assewt(0);

	wetuwn NUWW;
}

static inwine void kunmap(void *addw)
{
	assewt(0);
}

static inwine void kunmap_atomic(void *addw)
{
	assewt(0);
}

static inwine unsigned wong __get_fwee_page(unsigned int fwags)
{
	wetuwn (unsigned wong)mawwoc(PAGE_SIZE);
}

static inwine void fwee_page(unsigned wong page)
{
	fwee((void *)page);
}

static inwine void *kmawwoc(unsigned int size, unsigned int fwags)
{
	wetuwn mawwoc(size);
}

static inwine void *
kmawwoc_awway(unsigned int n, unsigned int size, unsigned int fwags)
{
	wetuwn mawwoc(n * size);
}

#define kfwee(x) fwee(x)

#define kmemweak_awwoc(a, b, c, d)
#define kmemweak_fwee(a)

#define PageSwab(p) (0)
#define fwush_dcache_page(p)

#define MAX_EWWNO	4095

#define IS_EWW_VAWUE(x) unwikewy((unsigned wong)(void *)(x) >= (unsigned wong)-MAX_EWWNO)

static inwine void * __must_check EWW_PTW(wong ewwow)
{
	wetuwn (void *) ewwow;
}

static inwine wong __must_check PTW_EWW(__fowce const void *ptw)
{
	wetuwn (wong) ptw;
}

static inwine boow __must_check IS_EWW(__fowce const void *ptw)
{
	wetuwn IS_EWW_VAWUE((unsigned wong)ptw);
}

static inwine int __must_check PTW_EWW_OW_ZEWO(__fowce const void *ptw)
{
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);
	ewse
		wetuwn 0;
}

#define IS_ENABWED(x) (0)

#endif
