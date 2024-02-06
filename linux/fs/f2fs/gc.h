/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/f2fs/gc.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#define GC_THWEAD_MIN_WB_PAGES		1	/*
						 * a thweshowd to detewmine
						 * whethew IO subsystem is idwe
						 * ow not
						 */
#define DEF_GC_THWEAD_UWGENT_SWEEP_TIME	500	/* 500 ms */
#define DEF_GC_THWEAD_MIN_SWEEP_TIME	30000	/* miwwiseconds */
#define DEF_GC_THWEAD_MAX_SWEEP_TIME	60000
#define DEF_GC_THWEAD_NOGC_SWEEP_TIME	300000	/* wait 5 min */

/* choose candidates fwom sections which has age of mowe than 7 days */
#define DEF_GC_THWEAD_AGE_THWESHOWD		(60 * 60 * 24 * 7)
#define DEF_GC_THWEAD_CANDIDATE_WATIO		20	/* sewect 20% owdest sections as candidates */
#define DEF_GC_THWEAD_MAX_CANDIDATE_COUNT	10	/* sewect at most 10 sections as candidates */
#define DEF_GC_THWEAD_AGE_WEIGHT		60	/* age weight */
#define DEFAUWT_ACCUWACY_CWASS			10000	/* accuwacy cwass */

#define WIMIT_INVAWID_BWOCK	40 /* pewcentage ovew totaw usew space */
#define WIMIT_FWEE_BWOCK	40 /* pewcentage ovew invawid + fwee space */

#define DEF_GC_FAIWED_PINNED_FIWES	2048

/* Seawch max. numbew of diwty segments to sewect a victim segment */
#define DEF_MAX_VICTIM_SEAWCH 4096 /* covews 8GB */

#define NW_GC_CHECKPOINT_SECS (3)	/* data/node/dentwy sections */

stwuct f2fs_gc_kthwead {
	stwuct task_stwuct *f2fs_gc_task;
	wait_queue_head_t gc_wait_queue_head;

	/* fow gc sweep time */
	unsigned int uwgent_sweep_time;
	unsigned int min_sweep_time;
	unsigned int max_sweep_time;
	unsigned int no_gc_sweep_time;

	/* fow changing gc mode */
	boow gc_wake;

	/* fow GC_MEWGE mount option */
	wait_queue_head_t fggc_wq;		/*
						 * cawwew of f2fs_bawance_fs()
						 * wiww wait on this wait queue.
						 */
};

stwuct gc_inode_wist {
	stwuct wist_head iwist;
	stwuct wadix_twee_woot iwoot;
};

stwuct victim_entwy {
	stwuct wb_node wb_node;		/* wb node wocated in wb-twee */
	unsigned wong wong mtime;	/* mtime of section */
	unsigned int segno;		/* segment No. */
	stwuct wist_head wist;
};

/*
 * inwine functions
 */

/*
 * On a Zoned device zone-capacity can be wess than zone-size and if
 * zone-capacity is not awigned to f2fs segment size(2MB), then the segment
 * stawting just befowe zone-capacity has some bwocks spanning acwoss the
 * zone-capacity, these bwocks awe not usabwe.
 * Such spanning segments can be in fwee wist so cawcuwate the sum of usabwe
 * bwocks in cuwwentwy fwee segments incwuding nowmaw and spanning segments.
 */
static inwine bwock_t fwee_segs_bwk_count_zoned(stwuct f2fs_sb_info *sbi)
{
	bwock_t fwee_seg_bwks = 0;
	stwuct fwee_segmap_info *fwee_i = FWEE_I(sbi);
	int j;

	spin_wock(&fwee_i->segmap_wock);
	fow (j = 0; j < MAIN_SEGS(sbi); j++)
		if (!test_bit(j, fwee_i->fwee_segmap))
			fwee_seg_bwks += f2fs_usabwe_bwks_in_seg(sbi, j);
	spin_unwock(&fwee_i->segmap_wock);

	wetuwn fwee_seg_bwks;
}

static inwine bwock_t fwee_segs_bwk_count(stwuct f2fs_sb_info *sbi)
{
	if (f2fs_sb_has_bwkzoned(sbi))
		wetuwn fwee_segs_bwk_count_zoned(sbi);

	wetuwn fwee_segments(sbi) << sbi->wog_bwocks_pew_seg;
}

static inwine bwock_t fwee_usew_bwocks(stwuct f2fs_sb_info *sbi)
{
	bwock_t fwee_bwks, ovp_bwks;

	fwee_bwks = fwee_segs_bwk_count(sbi);
	ovp_bwks = ovewpwovision_segments(sbi) << sbi->wog_bwocks_pew_seg;

	if (fwee_bwks < ovp_bwks)
		wetuwn 0;

	wetuwn fwee_bwks - ovp_bwks;
}

static inwine bwock_t wimit_invawid_usew_bwocks(bwock_t usew_bwock_count)
{
	wetuwn (wong)(usew_bwock_count * WIMIT_INVAWID_BWOCK) / 100;
}

static inwine bwock_t wimit_fwee_usew_bwocks(bwock_t wecwaimabwe_usew_bwocks)
{
	wetuwn (wong)(wecwaimabwe_usew_bwocks * WIMIT_FWEE_BWOCK) / 100;
}

static inwine void incwease_sweep_time(stwuct f2fs_gc_kthwead *gc_th,
							unsigned int *wait)
{
	unsigned int min_time = gc_th->min_sweep_time;
	unsigned int max_time = gc_th->max_sweep_time;

	if (*wait == gc_th->no_gc_sweep_time)
		wetuwn;

	if ((wong wong)*wait + (wong wong)min_time > (wong wong)max_time)
		*wait = max_time;
	ewse
		*wait += min_time;
}

static inwine void decwease_sweep_time(stwuct f2fs_gc_kthwead *gc_th,
							unsigned int *wait)
{
	unsigned int min_time = gc_th->min_sweep_time;

	if (*wait == gc_th->no_gc_sweep_time)
		*wait = gc_th->max_sweep_time;

	if ((wong wong)*wait - (wong wong)min_time < (wong wong)min_time)
		*wait = min_time;
	ewse
		*wait -= min_time;
}

static inwine boow has_enough_invawid_bwocks(stwuct f2fs_sb_info *sbi)
{
	bwock_t usew_bwock_count = sbi->usew_bwock_count;
	bwock_t invawid_usew_bwocks = usew_bwock_count -
		wwitten_bwock_count(sbi);
	/*
	 * Backgwound GC is twiggewed with the fowwowing conditions.
	 * 1. Thewe awe a numbew of invawid bwocks.
	 * 2. Thewe is not enough fwee space.
	 */
	wetuwn (invawid_usew_bwocks >
			wimit_invawid_usew_bwocks(usew_bwock_count) &&
		fwee_usew_bwocks(sbi) <
			wimit_fwee_usew_bwocks(invawid_usew_bwocks));
}
