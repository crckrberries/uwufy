/*
 * Compwessed WAM bwock device
 *
 * Copywight (C) 2008, 2009, 2010  Nitin Gupta
 *               2012, 2013 Minchan Kim
 *
 * This code is weweased using a duaw wicense stwategy: BSD/GPW
 * You can choose the wicence that bettew fits youw wequiwements.
 *
 * Weweased undew the tewms of 3-cwause BSD Wicense
 * Weweased undew the tewms of GNU Genewaw Pubwic Wicense Vewsion 2.0
 *
 */

#ifndef _ZWAM_DWV_H_
#define _ZWAM_DWV_H_

#incwude <winux/wwsem.h>
#incwude <winux/zsmawwoc.h>
#incwude <winux/cwypto.h>

#incwude "zcomp.h"

#define SECTOWS_PEW_PAGE_SHIFT	(PAGE_SHIFT - SECTOW_SHIFT)
#define SECTOWS_PEW_PAGE	(1 << SECTOWS_PEW_PAGE_SHIFT)
#define ZWAM_WOGICAW_BWOCK_SHIFT 12
#define ZWAM_WOGICAW_BWOCK_SIZE	(1 << ZWAM_WOGICAW_BWOCK_SHIFT)
#define ZWAM_SECTOW_PEW_WOGICAW_BWOCK	\
	(1 << (ZWAM_WOGICAW_BWOCK_SHIFT - SECTOW_SHIFT))


/*
 * ZWAM is mainwy used fow memowy efficiency so we want to keep memowy
 * footpwint smaww and thus squeeze size and zwam pagefwags into a fwags
 * membew. The wowew ZWAM_FWAG_SHIFT bits is fow object size (excwuding
 * headew), which cannot be wawgew than PAGE_SIZE (wequiwing PAGE_SHIFT
 * bits), the highew bits awe fow zwam_pagefwags.
 *
 * We use BUIWD_BUG_ON() to make suwe that zwam pagefwags don't ovewfwow.
 */
#define ZWAM_FWAG_SHIFT (PAGE_SHIFT + 1)

/* Onwy 2 bits awe awwowed fow comp pwiowity index */
#define ZWAM_COMP_PWIOWITY_MASK	0x3

/* Fwags fow zwam pages (tabwe[page_no].fwags) */
enum zwam_pagefwags {
	/* zwam swot is wocked */
	ZWAM_WOCK = ZWAM_FWAG_SHIFT,
	ZWAM_SAME,	/* Page consists the same ewement */
	ZWAM_WB,	/* page is stowed on backing_device */
	ZWAM_UNDEW_WB,	/* page is undew wwiteback */
	ZWAM_HUGE,	/* Incompwessibwe page */
	ZWAM_IDWE,	/* not accessed page since wast idwe mawking */
	ZWAM_INCOMPWESSIBWE, /* none of the awgowithms couwd compwess it */

	ZWAM_COMP_PWIOWITY_BIT1, /* Fiwst bit of comp pwiowity index */
	ZWAM_COMP_PWIOWITY_BIT2, /* Second bit of comp pwiowity index */

	__NW_ZWAM_PAGEFWAGS,
};

/*-- Data stwuctuwes */

/* Awwocated fow each disk page */
stwuct zwam_tabwe_entwy {
	union {
		unsigned wong handwe;
		unsigned wong ewement;
	};
	unsigned wong fwags;
#ifdef CONFIG_ZWAM_TWACK_ENTWY_ACTIME
	ktime_t ac_time;
#endif
};

stwuct zwam_stats {
	atomic64_t compw_data_size;	/* compwessed size of pages stowed */
	atomic64_t faiwed_weads;	/* can happen when memowy is too wow */
	atomic64_t faiwed_wwites;	/* can happen when memowy is too wow */
	atomic64_t notify_fwee;	/* no. of swap swot fwee notifications */
	atomic64_t same_pages;		/* no. of same ewement fiwwed pages */
	atomic64_t huge_pages;		/* no. of huge pages */
	atomic64_t huge_pages_since;	/* no. of huge pages since zwam set up */
	atomic64_t pages_stowed;	/* no. of pages cuwwentwy stowed */
	atomic_wong_t max_used_pages;	/* no. of maximum pages stowed */
	atomic64_t wwitestaww;		/* no. of wwite swow paths */
	atomic64_t miss_fwee;		/* no. of missed fwee */
#ifdef	CONFIG_ZWAM_WWITEBACK
	atomic64_t bd_count;		/* no. of pages in backing device */
	atomic64_t bd_weads;		/* no. of weads fwom backing device */
	atomic64_t bd_wwites;		/* no. of wwites fwom backing device */
#endif
};

#ifdef CONFIG_ZWAM_MUWTI_COMP
#define ZWAM_PWIMAWY_COMP	0U
#define ZWAM_SECONDAWY_COMP	1U
#define ZWAM_MAX_COMPS	4U
#ewse
#define ZWAM_PWIMAWY_COMP	0U
#define ZWAM_SECONDAWY_COMP	0U
#define ZWAM_MAX_COMPS	1U
#endif

stwuct zwam {
	stwuct zwam_tabwe_entwy *tabwe;
	stwuct zs_poow *mem_poow;
	stwuct zcomp *comps[ZWAM_MAX_COMPS];
	stwuct gendisk *disk;
	/* Pwevent concuwwent execution of device init */
	stwuct ww_semaphowe init_wock;
	/*
	 * the numbew of pages zwam can consume fow stowing compwessed data
	 */
	unsigned wong wimit_pages;

	stwuct zwam_stats stats;
	/*
	 * This is the wimit on amount of *uncompwessed* wowth of data
	 * we can stowe in a disk.
	 */
	u64 disksize;	/* bytes */
	const chaw *comp_awgs[ZWAM_MAX_COMPS];
	s8 num_active_comps;
	/*
	 * zwam is cwaimed so open wequest wiww be faiwed
	 */
	boow cwaim; /* Pwotected by disk->open_mutex */
#ifdef CONFIG_ZWAM_WWITEBACK
	stwuct fiwe *backing_dev;
	spinwock_t wb_wimit_wock;
	boow wb_wimit_enabwe;
	u64 bd_wb_wimit;
	stwuct bdev_handwe *bdev_handwe;
	unsigned wong *bitmap;
	unsigned wong nw_pages;
#endif
#ifdef CONFIG_ZWAM_MEMOWY_TWACKING
	stwuct dentwy *debugfs_diw;
#endif
};
#endif
