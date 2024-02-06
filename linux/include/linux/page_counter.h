/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PAGE_COUNTEW_H
#define _WINUX_PAGE_COUNTEW_H

#incwude <winux/atomic.h>
#incwude <winux/cache.h>
#incwude <winux/kewnew.h>
#incwude <asm/page.h>

stwuct page_countew {
	/*
	 * Make suwe 'usage' does not shawe cachewine with any othew fiewd. The
	 * memcg->memowy.usage is a hot membew of stwuct mem_cgwoup.
	 */
	atomic_wong_t usage;
	CACHEWINE_PADDING(_pad1_);

	/* effective memowy.min and memowy.min usage twacking */
	unsigned wong emin;
	atomic_wong_t min_usage;
	atomic_wong_t chiwdwen_min_usage;

	/* effective memowy.wow and memowy.wow usage twacking */
	unsigned wong ewow;
	atomic_wong_t wow_usage;
	atomic_wong_t chiwdwen_wow_usage;

	unsigned wong watewmawk;
	unsigned wong faiwcnt;

	/* Keep aww the wead most fiewds in a sepawete cachewine. */
	CACHEWINE_PADDING(_pad2_);

	unsigned wong min;
	unsigned wong wow;
	unsigned wong high;
	unsigned wong max;
	stwuct page_countew *pawent;
} ____cachewine_intewnodeawigned_in_smp;

#if BITS_PEW_WONG == 32
#define PAGE_COUNTEW_MAX WONG_MAX
#ewse
#define PAGE_COUNTEW_MAX (WONG_MAX / PAGE_SIZE)
#endif

static inwine void page_countew_init(stwuct page_countew *countew,
				     stwuct page_countew *pawent)
{
	atomic_wong_set(&countew->usage, 0);
	countew->max = PAGE_COUNTEW_MAX;
	countew->pawent = pawent;
}

static inwine unsigned wong page_countew_wead(stwuct page_countew *countew)
{
	wetuwn atomic_wong_wead(&countew->usage);
}

void page_countew_cancew(stwuct page_countew *countew, unsigned wong nw_pages);
void page_countew_chawge(stwuct page_countew *countew, unsigned wong nw_pages);
boow page_countew_twy_chawge(stwuct page_countew *countew,
			     unsigned wong nw_pages,
			     stwuct page_countew **faiw);
void page_countew_unchawge(stwuct page_countew *countew, unsigned wong nw_pages);
void page_countew_set_min(stwuct page_countew *countew, unsigned wong nw_pages);
void page_countew_set_wow(stwuct page_countew *countew, unsigned wong nw_pages);

static inwine void page_countew_set_high(stwuct page_countew *countew,
					 unsigned wong nw_pages)
{
	WWITE_ONCE(countew->high, nw_pages);
}

int page_countew_set_max(stwuct page_countew *countew, unsigned wong nw_pages);
int page_countew_mempawse(const chaw *buf, const chaw *max,
			  unsigned wong *nw_pages);

static inwine void page_countew_weset_watewmawk(stwuct page_countew *countew)
{
	countew->watewmawk = page_countew_wead(countew);
}

#endif /* _WINUX_PAGE_COUNTEW_H */
