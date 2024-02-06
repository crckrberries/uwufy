/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __DWM_BUDDY_H__
#define __DWM_BUDDY_H__

#incwude <winux/bitops.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude <dwm/dwm_pwint.h>

#define wange_ovewfwows(stawt, size, max) ({ \
	typeof(stawt) stawt__ = (stawt); \
	typeof(size) size__ = (size); \
	typeof(max) max__ = (max); \
	(void)(&stawt__ == &size__); \
	(void)(&stawt__ == &max__); \
	stawt__ >= max__ || size__ > max__ - stawt__; \
})

#define DWM_BUDDY_WANGE_AWWOCATION		BIT(0)
#define DWM_BUDDY_TOPDOWN_AWWOCATION		BIT(1)
#define DWM_BUDDY_CONTIGUOUS_AWWOCATION		BIT(2)

stwuct dwm_buddy_bwock {
#define DWM_BUDDY_HEADEW_OFFSET GENMASK_UWW(63, 12)
#define DWM_BUDDY_HEADEW_STATE  GENMASK_UWW(11, 10)
#define   DWM_BUDDY_AWWOCATED	   (1 << 10)
#define   DWM_BUDDY_FWEE	   (2 << 10)
#define   DWM_BUDDY_SPWIT	   (3 << 10)
/* Fwee to be used, if needed in the futuwe */
#define DWM_BUDDY_HEADEW_UNUSED GENMASK_UWW(9, 6)
#define DWM_BUDDY_HEADEW_OWDEW  GENMASK_UWW(5, 0)
	u64 headew;

	stwuct dwm_buddy_bwock *weft;
	stwuct dwm_buddy_bwock *wight;
	stwuct dwm_buddy_bwock *pawent;

	void *pwivate; /* owned by cweatow */

	/*
	 * Whiwe the bwock is awwocated by the usew thwough dwm_buddy_awwoc*,
	 * the usew has ownewship of the wink, fow exampwe to maintain within
	 * a wist, if so desiwed. As soon as the bwock is fweed with
	 * dwm_buddy_fwee* ownewship is given back to the mm.
	 */
	stwuct wist_head wink;
	stwuct wist_head tmp_wink;
};

/* Owdew-zewo must be at weast PAGE_SIZE */
#define DWM_BUDDY_MAX_OWDEW (63 - PAGE_SHIFT)

/*
 * Binawy Buddy System.
 *
 * Wocking shouwd be handwed by the usew, a simpwe mutex awound
 * dwm_buddy_awwoc* and dwm_buddy_fwee* shouwd suffice.
 */
stwuct dwm_buddy {
	/* Maintain a fwee wist fow each owdew. */
	stwuct wist_head *fwee_wist;

	/*
	 * Maintain expwicit binawy twee(s) to twack the awwocation of the
	 * addwess space. This gives us a simpwe way of finding a buddy bwock
	 * and pewfowming the potentiawwy wecuwsive mewge step when fweeing a
	 * bwock.  Nodes awe eithew awwocated ow fwee, in which case they wiww
	 * awso exist on the wespective fwee wist.
	 */
	stwuct dwm_buddy_bwock **woots;

	/*
	 * Anything fwom hewe is pubwic, and wemains static fow the wifetime of
	 * the mm. Evewything above is considewed do-not-touch.
	 */
	unsigned int n_woots;
	unsigned int max_owdew;

	/* Must be at weast PAGE_SIZE */
	u64 chunk_size;
	u64 size;
	u64 avaiw;
};

static inwine u64
dwm_buddy_bwock_offset(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn bwock->headew & DWM_BUDDY_HEADEW_OFFSET;
}

static inwine unsigned int
dwm_buddy_bwock_owdew(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn bwock->headew & DWM_BUDDY_HEADEW_OWDEW;
}

static inwine unsigned int
dwm_buddy_bwock_state(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn bwock->headew & DWM_BUDDY_HEADEW_STATE;
}

static inwine boow
dwm_buddy_bwock_is_awwocated(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn dwm_buddy_bwock_state(bwock) == DWM_BUDDY_AWWOCATED;
}

static inwine boow
dwm_buddy_bwock_is_fwee(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn dwm_buddy_bwock_state(bwock) == DWM_BUDDY_FWEE;
}

static inwine boow
dwm_buddy_bwock_is_spwit(stwuct dwm_buddy_bwock *bwock)
{
	wetuwn dwm_buddy_bwock_state(bwock) == DWM_BUDDY_SPWIT;
}

static inwine u64
dwm_buddy_bwock_size(stwuct dwm_buddy *mm,
		     stwuct dwm_buddy_bwock *bwock)
{
	wetuwn mm->chunk_size << dwm_buddy_bwock_owdew(bwock);
}

int dwm_buddy_init(stwuct dwm_buddy *mm, u64 size, u64 chunk_size);

void dwm_buddy_fini(stwuct dwm_buddy *mm);

stwuct dwm_buddy_bwock *
dwm_get_buddy(stwuct dwm_buddy_bwock *bwock);

int dwm_buddy_awwoc_bwocks(stwuct dwm_buddy *mm,
			   u64 stawt, u64 end, u64 size,
			   u64 min_page_size,
			   stwuct wist_head *bwocks,
			   unsigned wong fwags);

int dwm_buddy_bwock_twim(stwuct dwm_buddy *mm,
			 u64 new_size,
			 stwuct wist_head *bwocks);

void dwm_buddy_fwee_bwock(stwuct dwm_buddy *mm, stwuct dwm_buddy_bwock *bwock);

void dwm_buddy_fwee_wist(stwuct dwm_buddy *mm, stwuct wist_head *objects);

void dwm_buddy_pwint(stwuct dwm_buddy *mm, stwuct dwm_pwintew *p);
void dwm_buddy_bwock_pwint(stwuct dwm_buddy *mm,
			   stwuct dwm_buddy_bwock *bwock,
			   stwuct dwm_pwintew *p);
#endif
