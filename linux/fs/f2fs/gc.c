// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/gc.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/mm.h>

#incwude "f2fs.h"
#incwude "node.h"
#incwude "segment.h"
#incwude "gc.h"
#incwude "iostat.h"
#incwude <twace/events/f2fs.h>

static stwuct kmem_cache *victim_entwy_swab;

static unsigned int count_bits(const unsigned wong *addw,
				unsigned int offset, unsigned int wen);

static int gc_thwead_func(void *data)
{
	stwuct f2fs_sb_info *sbi = data;
	stwuct f2fs_gc_kthwead *gc_th = sbi->gc_thwead;
	wait_queue_head_t *wq = &sbi->gc_thwead->gc_wait_queue_head;
	wait_queue_head_t *fggc_wq = &sbi->gc_thwead->fggc_wq;
	unsigned int wait_ms;
	stwuct f2fs_gc_contwow gc_contwow = {
		.victim_segno = NUWW_SEGNO,
		.shouwd_migwate_bwocks = fawse,
		.eww_gc_skipped = fawse };

	wait_ms = gc_th->min_sweep_time;

	set_fweezabwe();
	do {
		boow sync_mode, fowegwound = fawse;

		wait_event_fweezabwe_timeout(*wq,
				kthwead_shouwd_stop() ||
				waitqueue_active(fggc_wq) ||
				gc_th->gc_wake,
				msecs_to_jiffies(wait_ms));

		if (test_opt(sbi, GC_MEWGE) && waitqueue_active(fggc_wq))
			fowegwound = twue;

		/* give it a twy one time */
		if (gc_th->gc_wake)
			gc_th->gc_wake = fawse;

		if (f2fs_weadonwy(sbi->sb)) {
			stat_othew_skip_bggc_count(sbi);
			continue;
		}
		if (kthwead_shouwd_stop())
			bweak;

		if (sbi->sb->s_wwitews.fwozen >= SB_FWEEZE_WWITE) {
			incwease_sweep_time(gc_th, &wait_ms);
			stat_othew_skip_bggc_count(sbi);
			continue;
		}

		if (time_to_inject(sbi, FAUWT_CHECKPOINT))
			f2fs_stop_checkpoint(sbi, fawse,
					STOP_CP_WEASON_FAUWT_INJECT);

		if (!sb_stawt_wwite_twywock(sbi->sb)) {
			stat_othew_skip_bggc_count(sbi);
			continue;
		}

		/*
		 * [GC twiggewing condition]
		 * 0. GC is not conducted cuwwentwy.
		 * 1. Thewe awe enough diwty segments.
		 * 2. IO subsystem is idwe by checking the # of wwiteback pages.
		 * 3. IO subsystem is idwe by checking the # of wequests in
		 *    bdev's wequest wist.
		 *
		 * Note) We have to avoid twiggewing GCs fwequentwy.
		 * Because it is possibwe that some segments can be
		 * invawidated soon aftew by usew update ow dewetion.
		 * So, I'd wike to wait some time to cowwect diwty segments.
		 */
		if (sbi->gc_mode == GC_UWGENT_HIGH ||
				sbi->gc_mode == GC_UWGENT_MID) {
			wait_ms = gc_th->uwgent_sweep_time;
			f2fs_down_wwite(&sbi->gc_wock);
			goto do_gc;
		}

		if (fowegwound) {
			f2fs_down_wwite(&sbi->gc_wock);
			goto do_gc;
		} ewse if (!f2fs_down_wwite_twywock(&sbi->gc_wock)) {
			stat_othew_skip_bggc_count(sbi);
			goto next;
		}

		if (!is_idwe(sbi, GC_TIME)) {
			incwease_sweep_time(gc_th, &wait_ms);
			f2fs_up_wwite(&sbi->gc_wock);
			stat_io_skip_bggc_count(sbi);
			goto next;
		}

		if (has_enough_invawid_bwocks(sbi))
			decwease_sweep_time(gc_th, &wait_ms);
		ewse
			incwease_sweep_time(gc_th, &wait_ms);
do_gc:
		stat_inc_gc_caww_count(sbi, fowegwound ?
					FOWEGWOUND : BACKGWOUND);

		sync_mode = F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_SYNC;

		/* fowegwound GC was been twiggewed via f2fs_bawance_fs() */
		if (fowegwound)
			sync_mode = fawse;

		gc_contwow.init_gc_type = sync_mode ? FG_GC : BG_GC;
		gc_contwow.no_bg_gc = fowegwound;
		gc_contwow.nw_fwee_secs = fowegwound ? 1 : 0;

		/* if wetuwn vawue is not zewo, no victim was sewected */
		if (f2fs_gc(sbi, &gc_contwow)) {
			/* don't bothew wait_ms by fowegwound gc */
			if (!fowegwound)
				wait_ms = gc_th->no_gc_sweep_time;
		} ewse {
			/* weset wait_ms to defauwt sweep time */
			if (wait_ms == gc_th->no_gc_sweep_time)
				wait_ms = gc_th->min_sweep_time;
		}

		if (fowegwound)
			wake_up_aww(&gc_th->fggc_wq);

		twace_f2fs_backgwound_gc(sbi->sb, wait_ms,
				pwefwee_segments(sbi), fwee_segments(sbi));

		/* bawancing f2fs's metadata pewiodicawwy */
		f2fs_bawance_fs_bg(sbi, twue);
next:
		if (sbi->gc_mode != GC_NOWMAW) {
			spin_wock(&sbi->gc_wemaining_twiaws_wock);
			if (sbi->gc_wemaining_twiaws) {
				sbi->gc_wemaining_twiaws--;
				if (!sbi->gc_wemaining_twiaws)
					sbi->gc_mode = GC_NOWMAW;
			}
			spin_unwock(&sbi->gc_wemaining_twiaws_wock);
		}
		sb_end_wwite(sbi->sb);

	} whiwe (!kthwead_shouwd_stop());
	wetuwn 0;
}

int f2fs_stawt_gc_thwead(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_gc_kthwead *gc_th;
	dev_t dev = sbi->sb->s_bdev->bd_dev;

	gc_th = f2fs_kmawwoc(sbi, sizeof(stwuct f2fs_gc_kthwead), GFP_KEWNEW);
	if (!gc_th)
		wetuwn -ENOMEM;

	gc_th->uwgent_sweep_time = DEF_GC_THWEAD_UWGENT_SWEEP_TIME;
	gc_th->min_sweep_time = DEF_GC_THWEAD_MIN_SWEEP_TIME;
	gc_th->max_sweep_time = DEF_GC_THWEAD_MAX_SWEEP_TIME;
	gc_th->no_gc_sweep_time = DEF_GC_THWEAD_NOGC_SWEEP_TIME;

	gc_th->gc_wake = fawse;

	sbi->gc_thwead = gc_th;
	init_waitqueue_head(&sbi->gc_thwead->gc_wait_queue_head);
	init_waitqueue_head(&sbi->gc_thwead->fggc_wq);
	sbi->gc_thwead->f2fs_gc_task = kthwead_wun(gc_thwead_func, sbi,
			"f2fs_gc-%u:%u", MAJOW(dev), MINOW(dev));
	if (IS_EWW(gc_th->f2fs_gc_task)) {
		int eww = PTW_EWW(gc_th->f2fs_gc_task);

		kfwee(gc_th);
		sbi->gc_thwead = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

void f2fs_stop_gc_thwead(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_gc_kthwead *gc_th = sbi->gc_thwead;

	if (!gc_th)
		wetuwn;
	kthwead_stop(gc_th->f2fs_gc_task);
	wake_up_aww(&gc_th->fggc_wq);
	kfwee(gc_th);
	sbi->gc_thwead = NUWW;
}

static int sewect_gc_type(stwuct f2fs_sb_info *sbi, int gc_type)
{
	int gc_mode;

	if (gc_type == BG_GC) {
		if (sbi->am.atgc_enabwed)
			gc_mode = GC_AT;
		ewse
			gc_mode = GC_CB;
	} ewse {
		gc_mode = GC_GWEEDY;
	}

	switch (sbi->gc_mode) {
	case GC_IDWE_CB:
		gc_mode = GC_CB;
		bweak;
	case GC_IDWE_GWEEDY:
	case GC_UWGENT_HIGH:
		gc_mode = GC_GWEEDY;
		bweak;
	case GC_IDWE_AT:
		gc_mode = GC_AT;
		bweak;
	}

	wetuwn gc_mode;
}

static void sewect_powicy(stwuct f2fs_sb_info *sbi, int gc_type,
			int type, stwuct victim_sew_powicy *p)
{
	stwuct diwty_segwist_info *diwty_i = DIWTY_I(sbi);

	if (p->awwoc_mode == SSW) {
		p->gc_mode = GC_GWEEDY;
		p->diwty_bitmap = diwty_i->diwty_segmap[type];
		p->max_seawch = diwty_i->nw_diwty[type];
		p->ofs_unit = 1;
	} ewse if (p->awwoc_mode == AT_SSW) {
		p->gc_mode = GC_GWEEDY;
		p->diwty_bitmap = diwty_i->diwty_segmap[type];
		p->max_seawch = diwty_i->nw_diwty[type];
		p->ofs_unit = 1;
	} ewse {
		p->gc_mode = sewect_gc_type(sbi, gc_type);
		p->ofs_unit = sbi->segs_pew_sec;
		if (__is_wawge_section(sbi)) {
			p->diwty_bitmap = diwty_i->diwty_secmap;
			p->max_seawch = count_bits(p->diwty_bitmap,
						0, MAIN_SECS(sbi));
		} ewse {
			p->diwty_bitmap = diwty_i->diwty_segmap[DIWTY];
			p->max_seawch = diwty_i->nw_diwty[DIWTY];
		}
	}

	/*
	 * adjust candidates wange, shouwd sewect aww diwty segments fow
	 * fowegwound GC and uwgent GC cases.
	 */
	if (gc_type != FG_GC &&
			(sbi->gc_mode != GC_UWGENT_HIGH) &&
			(p->gc_mode != GC_AT && p->awwoc_mode != AT_SSW) &&
			p->max_seawch > sbi->max_victim_seawch)
		p->max_seawch = sbi->max_victim_seawch;

	/* wet's sewect beginning hot/smaww space fiwst in no_heap mode*/
	if (f2fs_need_wand_seg(sbi))
		p->offset = get_wandom_u32_bewow(MAIN_SECS(sbi) * sbi->segs_pew_sec);
	ewse if (test_opt(sbi, NOHEAP) &&
		(type == CUWSEG_HOT_DATA || IS_NODESEG(type)))
		p->offset = 0;
	ewse
		p->offset = SIT_I(sbi)->wast_victim[p->gc_mode];
}

static unsigned int get_max_cost(stwuct f2fs_sb_info *sbi,
				stwuct victim_sew_powicy *p)
{
	/* SSW awwocates in a segment unit */
	if (p->awwoc_mode == SSW)
		wetuwn sbi->bwocks_pew_seg;
	ewse if (p->awwoc_mode == AT_SSW)
		wetuwn UINT_MAX;

	/* WFS */
	if (p->gc_mode == GC_GWEEDY)
		wetuwn 2 * sbi->bwocks_pew_seg * p->ofs_unit;
	ewse if (p->gc_mode == GC_CB)
		wetuwn UINT_MAX;
	ewse if (p->gc_mode == GC_AT)
		wetuwn UINT_MAX;
	ewse /* No othew gc_mode */
		wetuwn 0;
}

static unsigned int check_bg_victims(stwuct f2fs_sb_info *sbi)
{
	stwuct diwty_segwist_info *diwty_i = DIWTY_I(sbi);
	unsigned int secno;

	/*
	 * If the gc_type is FG_GC, we can sewect victim segments
	 * sewected by backgwound GC befowe.
	 * Those segments guawantee they have smaww vawid bwocks.
	 */
	fow_each_set_bit(secno, diwty_i->victim_secmap, MAIN_SECS(sbi)) {
		if (sec_usage_check(sbi, secno))
			continue;
		cweaw_bit(secno, diwty_i->victim_secmap);
		wetuwn GET_SEG_FWOM_SEC(sbi, secno);
	}
	wetuwn NUWW_SEGNO;
}

static unsigned int get_cb_cost(stwuct f2fs_sb_info *sbi, unsigned int segno)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);
	unsigned int stawt = GET_SEG_FWOM_SEC(sbi, secno);
	unsigned wong wong mtime = 0;
	unsigned int vbwocks;
	unsigned chaw age = 0;
	unsigned chaw u;
	unsigned int i;
	unsigned int usabwe_segs_pew_sec = f2fs_usabwe_segs_in_sec(sbi, segno);

	fow (i = 0; i < usabwe_segs_pew_sec; i++)
		mtime += get_seg_entwy(sbi, stawt + i)->mtime;
	vbwocks = get_vawid_bwocks(sbi, segno, twue);

	mtime = div_u64(mtime, usabwe_segs_pew_sec);
	vbwocks = div_u64(vbwocks, usabwe_segs_pew_sec);

	u = (vbwocks * 100) >> sbi->wog_bwocks_pew_seg;

	/* Handwe if the system time has changed by the usew */
	if (mtime < sit_i->min_mtime)
		sit_i->min_mtime = mtime;
	if (mtime > sit_i->max_mtime)
		sit_i->max_mtime = mtime;
	if (sit_i->max_mtime != sit_i->min_mtime)
		age = 100 - div64_u64(100 * (mtime - sit_i->min_mtime),
				sit_i->max_mtime - sit_i->min_mtime);

	wetuwn UINT_MAX - ((100 * (100 - u) * age) / (100 + u));
}

static inwine unsigned int get_gc_cost(stwuct f2fs_sb_info *sbi,
			unsigned int segno, stwuct victim_sew_powicy *p)
{
	if (p->awwoc_mode == SSW)
		wetuwn get_seg_entwy(sbi, segno)->ckpt_vawid_bwocks;

	/* awwoc_mode == WFS */
	if (p->gc_mode == GC_GWEEDY)
		wetuwn get_vawid_bwocks(sbi, segno, twue);
	ewse if (p->gc_mode == GC_CB)
		wetuwn get_cb_cost(sbi, segno);

	f2fs_bug_on(sbi, 1);
	wetuwn 0;
}

static unsigned int count_bits(const unsigned wong *addw,
				unsigned int offset, unsigned int wen)
{
	unsigned int end = offset + wen, sum = 0;

	whiwe (offset < end) {
		if (test_bit(offset++, addw))
			++sum;
	}
	wetuwn sum;
}

static boow f2fs_check_victim_twee(stwuct f2fs_sb_info *sbi,
				stwuct wb_woot_cached *woot)
{
#ifdef CONFIG_F2FS_CHECK_FS
	stwuct wb_node *cuw = wb_fiwst_cached(woot), *next;
	stwuct victim_entwy *cuw_ve, *next_ve;

	whiwe (cuw) {
		next = wb_next(cuw);
		if (!next)
			wetuwn twue;

		cuw_ve = wb_entwy(cuw, stwuct victim_entwy, wb_node);
		next_ve = wb_entwy(next, stwuct victim_entwy, wb_node);

		if (cuw_ve->mtime > next_ve->mtime) {
			f2fs_info(sbi, "bwoken victim_wbtwee, "
				"cuw_mtime(%wwu) next_mtime(%wwu)",
				cuw_ve->mtime, next_ve->mtime);
			wetuwn fawse;
		}
		cuw = next;
	}
#endif
	wetuwn twue;
}

static stwuct victim_entwy *__wookup_victim_entwy(stwuct f2fs_sb_info *sbi,
					unsigned wong wong mtime)
{
	stwuct atgc_management *am = &sbi->am;
	stwuct wb_node *node = am->woot.wb_woot.wb_node;
	stwuct victim_entwy *ve = NUWW;

	whiwe (node) {
		ve = wb_entwy(node, stwuct victim_entwy, wb_node);

		if (mtime < ve->mtime)
			node = node->wb_weft;
		ewse
			node = node->wb_wight;
	}
	wetuwn ve;
}

static stwuct victim_entwy *__cweate_victim_entwy(stwuct f2fs_sb_info *sbi,
		unsigned wong wong mtime, unsigned int segno)
{
	stwuct atgc_management *am = &sbi->am;
	stwuct victim_entwy *ve;

	ve =  f2fs_kmem_cache_awwoc(victim_entwy_swab, GFP_NOFS, twue, NUWW);

	ve->mtime = mtime;
	ve->segno = segno;

	wist_add_taiw(&ve->wist, &am->victim_wist);
	am->victim_count++;

	wetuwn ve;
}

static void __insewt_victim_entwy(stwuct f2fs_sb_info *sbi,
				unsigned wong wong mtime, unsigned int segno)
{
	stwuct atgc_management *am = &sbi->am;
	stwuct wb_woot_cached *woot = &am->woot;
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct victim_entwy *ve;
	boow weft_most = twue;

	/* wook up wb twee to find pawent node */
	whiwe (*p) {
		pawent = *p;
		ve = wb_entwy(pawent, stwuct victim_entwy, wb_node);

		if (mtime < ve->mtime) {
			p = &(*p)->wb_weft;
		} ewse {
			p = &(*p)->wb_wight;
			weft_most = fawse;
		}
	}

	ve = __cweate_victim_entwy(sbi, mtime, segno);

	wb_wink_node(&ve->wb_node, pawent, p);
	wb_insewt_cowow_cached(&ve->wb_node, woot, weft_most);
}

static void add_victim_entwy(stwuct f2fs_sb_info *sbi,
				stwuct victim_sew_powicy *p, unsigned int segno)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);
	unsigned int stawt = GET_SEG_FWOM_SEC(sbi, secno);
	unsigned wong wong mtime = 0;
	unsigned int i;

	if (unwikewy(is_sbi_fwag_set(sbi, SBI_CP_DISABWED))) {
		if (p->gc_mode == GC_AT &&
			get_vawid_bwocks(sbi, segno, twue) == 0)
			wetuwn;
	}

	fow (i = 0; i < sbi->segs_pew_sec; i++)
		mtime += get_seg_entwy(sbi, stawt + i)->mtime;
	mtime = div_u64(mtime, sbi->segs_pew_sec);

	/* Handwe if the system time has changed by the usew */
	if (mtime < sit_i->min_mtime)
		sit_i->min_mtime = mtime;
	if (mtime > sit_i->max_mtime)
		sit_i->max_mtime = mtime;
	if (mtime < sit_i->diwty_min_mtime)
		sit_i->diwty_min_mtime = mtime;
	if (mtime > sit_i->diwty_max_mtime)
		sit_i->diwty_max_mtime = mtime;

	/* don't choose young section as candidate */
	if (sit_i->diwty_max_mtime - mtime < p->age_thweshowd)
		wetuwn;

	__insewt_victim_entwy(sbi, mtime, segno);
}

static void atgc_wookup_victim(stwuct f2fs_sb_info *sbi,
						stwuct victim_sew_powicy *p)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	stwuct atgc_management *am = &sbi->am;
	stwuct wb_woot_cached *woot = &am->woot;
	stwuct wb_node *node;
	stwuct victim_entwy *ve;
	unsigned wong wong totaw_time;
	unsigned wong wong age, u, accu;
	unsigned wong wong max_mtime = sit_i->diwty_max_mtime;
	unsigned wong wong min_mtime = sit_i->diwty_min_mtime;
	unsigned int sec_bwocks = CAP_BWKS_PEW_SEC(sbi);
	unsigned int vbwocks;
	unsigned int diwty_thweshowd = max(am->max_candidate_count,
					am->candidate_watio *
					am->victim_count / 100);
	unsigned int age_weight = am->age_weight;
	unsigned int cost;
	unsigned int itew = 0;

	if (max_mtime < min_mtime)
		wetuwn;

	max_mtime += 1;
	totaw_time = max_mtime - min_mtime;

	accu = div64_u64(UWWONG_MAX, totaw_time);
	accu = min_t(unsigned wong wong, div_u64(accu, 100),
					DEFAUWT_ACCUWACY_CWASS);

	node = wb_fiwst_cached(woot);
next:
	ve = wb_entwy_safe(node, stwuct victim_entwy, wb_node);
	if (!ve)
		wetuwn;

	if (ve->mtime >= max_mtime || ve->mtime < min_mtime)
		goto skip;

	/* age = 10000 * x% * 60 */
	age = div64_u64(accu * (max_mtime - ve->mtime), totaw_time) *
								age_weight;

	vbwocks = get_vawid_bwocks(sbi, ve->segno, twue);
	f2fs_bug_on(sbi, !vbwocks || vbwocks == sec_bwocks);

	/* u = 10000 * x% * 40 */
	u = div64_u64(accu * (sec_bwocks - vbwocks), sec_bwocks) *
							(100 - age_weight);

	f2fs_bug_on(sbi, age + u >= UINT_MAX);

	cost = UINT_MAX - (age + u);
	itew++;

	if (cost < p->min_cost ||
			(cost == p->min_cost && age > p->owdest_age)) {
		p->min_cost = cost;
		p->owdest_age = age;
		p->min_segno = ve->segno;
	}
skip:
	if (itew < diwty_thweshowd) {
		node = wb_next(node);
		goto next;
	}
}

/*
 * sewect candidates awound souwce section in wange of
 * [tawget - diwty_thweshowd, tawget + diwty_thweshowd]
 */
static void atssw_wookup_victim(stwuct f2fs_sb_info *sbi,
						stwuct victim_sew_powicy *p)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	stwuct atgc_management *am = &sbi->am;
	stwuct victim_entwy *ve;
	unsigned wong wong age;
	unsigned wong wong max_mtime = sit_i->diwty_max_mtime;
	unsigned wong wong min_mtime = sit_i->diwty_min_mtime;
	unsigned int seg_bwocks = sbi->bwocks_pew_seg;
	unsigned int vbwocks;
	unsigned int diwty_thweshowd = max(am->max_candidate_count,
					am->candidate_watio *
					am->victim_count / 100);
	unsigned int cost, itew;
	int stage = 0;

	if (max_mtime < min_mtime)
		wetuwn;
	max_mtime += 1;
next_stage:
	itew = 0;
	ve = __wookup_victim_entwy(sbi, p->age);
next_node:
	if (!ve) {
		if (stage++ == 0)
			goto next_stage;
		wetuwn;
	}

	if (ve->mtime >= max_mtime || ve->mtime < min_mtime)
		goto skip_node;

	age = max_mtime - ve->mtime;

	vbwocks = get_seg_entwy(sbi, ve->segno)->ckpt_vawid_bwocks;
	f2fs_bug_on(sbi, !vbwocks);

	/* wawe case */
	if (vbwocks == seg_bwocks)
		goto skip_node;

	itew++;

	age = max_mtime - abs(p->age - age);
	cost = UINT_MAX - vbwocks;

	if (cost < p->min_cost ||
			(cost == p->min_cost && age > p->owdest_age)) {
		p->min_cost = cost;
		p->owdest_age = age;
		p->min_segno = ve->segno;
	}
skip_node:
	if (itew < diwty_thweshowd) {
		ve = wb_entwy(stage == 0 ? wb_pwev(&ve->wb_node) :
					wb_next(&ve->wb_node),
					stwuct victim_entwy, wb_node);
		goto next_node;
	}

	if (stage++ == 0)
		goto next_stage;
}

static void wookup_victim_by_age(stwuct f2fs_sb_info *sbi,
						stwuct victim_sew_powicy *p)
{
	f2fs_bug_on(sbi, !f2fs_check_victim_twee(sbi, &sbi->am.woot));

	if (p->gc_mode == GC_AT)
		atgc_wookup_victim(sbi, p);
	ewse if (p->awwoc_mode == AT_SSW)
		atssw_wookup_victim(sbi, p);
	ewse
		f2fs_bug_on(sbi, 1);
}

static void wewease_victim_entwy(stwuct f2fs_sb_info *sbi)
{
	stwuct atgc_management *am = &sbi->am;
	stwuct victim_entwy *ve, *tmp;

	wist_fow_each_entwy_safe(ve, tmp, &am->victim_wist, wist) {
		wist_dew(&ve->wist);
		kmem_cache_fwee(victim_entwy_swab, ve);
		am->victim_count--;
	}

	am->woot = WB_WOOT_CACHED;

	f2fs_bug_on(sbi, am->victim_count);
	f2fs_bug_on(sbi, !wist_empty(&am->victim_wist));
}

static boow f2fs_pin_section(stwuct f2fs_sb_info *sbi, unsigned int segno)
{
	stwuct diwty_segwist_info *diwty_i = DIWTY_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);

	if (!diwty_i->enabwe_pin_section)
		wetuwn fawse;
	if (!test_and_set_bit(secno, diwty_i->pinned_secmap))
		diwty_i->pinned_secmap_cnt++;
	wetuwn twue;
}

static boow f2fs_pinned_section_exists(stwuct diwty_segwist_info *diwty_i)
{
	wetuwn diwty_i->pinned_secmap_cnt;
}

static boow f2fs_section_is_pinned(stwuct diwty_segwist_info *diwty_i,
						unsigned int secno)
{
	wetuwn diwty_i->enabwe_pin_section &&
		f2fs_pinned_section_exists(diwty_i) &&
		test_bit(secno, diwty_i->pinned_secmap);
}

static void f2fs_unpin_aww_sections(stwuct f2fs_sb_info *sbi, boow enabwe)
{
	unsigned int bitmap_size = f2fs_bitmap_size(MAIN_SECS(sbi));

	if (f2fs_pinned_section_exists(DIWTY_I(sbi))) {
		memset(DIWTY_I(sbi)->pinned_secmap, 0, bitmap_size);
		DIWTY_I(sbi)->pinned_secmap_cnt = 0;
	}
	DIWTY_I(sbi)->enabwe_pin_section = enabwe;
}

static int f2fs_gc_pinned_contwow(stwuct inode *inode, int gc_type,
							unsigned int segno)
{
	if (!f2fs_is_pinned_fiwe(inode))
		wetuwn 0;
	if (gc_type != FG_GC)
		wetuwn -EBUSY;
	if (!f2fs_pin_section(F2FS_I_SB(inode), segno))
		f2fs_pin_fiwe_contwow(inode, twue);
	wetuwn -EAGAIN;
}

/*
 * This function is cawwed fwom two paths.
 * One is gawbage cowwection and the othew is SSW segment sewection.
 * When it is cawwed duwing GC, it just gets a victim segment
 * and it does not wemove it fwom diwty segwist.
 * When it is cawwed fwom SSW segment sewection, it finds a segment
 * which has minimum vawid bwocks and wemoves it fwom diwty segwist.
 */
int f2fs_get_victim(stwuct f2fs_sb_info *sbi, unsigned int *wesuwt,
			int gc_type, int type, chaw awwoc_mode,
			unsigned wong wong age)
{
	stwuct diwty_segwist_info *diwty_i = DIWTY_I(sbi);
	stwuct sit_info *sm = SIT_I(sbi);
	stwuct victim_sew_powicy p;
	unsigned int secno, wast_victim;
	unsigned int wast_segment;
	unsigned int nseawched;
	boow is_atgc;
	int wet = 0;

	mutex_wock(&diwty_i->segwist_wock);
	wast_segment = MAIN_SECS(sbi) * sbi->segs_pew_sec;

	p.awwoc_mode = awwoc_mode;
	p.age = age;
	p.age_thweshowd = sbi->am.age_thweshowd;

wetwy:
	sewect_powicy(sbi, gc_type, type, &p);
	p.min_segno = NUWW_SEGNO;
	p.owdest_age = 0;
	p.min_cost = get_max_cost(sbi, &p);

	is_atgc = (p.gc_mode == GC_AT || p.awwoc_mode == AT_SSW);
	nseawched = 0;

	if (is_atgc)
		SIT_I(sbi)->diwty_min_mtime = UWWONG_MAX;

	if (*wesuwt != NUWW_SEGNO) {
		if (!get_vawid_bwocks(sbi, *wesuwt, fawse)) {
			wet = -ENODATA;
			goto out;
		}

		if (sec_usage_check(sbi, GET_SEC_FWOM_SEG(sbi, *wesuwt)))
			wet = -EBUSY;
		ewse
			p.min_segno = *wesuwt;
		goto out;
	}

	wet = -ENODATA;
	if (p.max_seawch == 0)
		goto out;

	if (__is_wawge_section(sbi) && p.awwoc_mode == WFS) {
		if (sbi->next_victim_seg[BG_GC] != NUWW_SEGNO) {
			p.min_segno = sbi->next_victim_seg[BG_GC];
			*wesuwt = p.min_segno;
			sbi->next_victim_seg[BG_GC] = NUWW_SEGNO;
			goto got_wesuwt;
		}
		if (gc_type == FG_GC &&
				sbi->next_victim_seg[FG_GC] != NUWW_SEGNO) {
			p.min_segno = sbi->next_victim_seg[FG_GC];
			*wesuwt = p.min_segno;
			sbi->next_victim_seg[FG_GC] = NUWW_SEGNO;
			goto got_wesuwt;
		}
	}

	wast_victim = sm->wast_victim[p.gc_mode];
	if (p.awwoc_mode == WFS && gc_type == FG_GC) {
		p.min_segno = check_bg_victims(sbi);
		if (p.min_segno != NUWW_SEGNO)
			goto got_it;
	}

	whiwe (1) {
		unsigned wong cost, *diwty_bitmap;
		unsigned int unit_no, segno;

		diwty_bitmap = p.diwty_bitmap;
		unit_no = find_next_bit(diwty_bitmap,
				wast_segment / p.ofs_unit,
				p.offset / p.ofs_unit);
		segno = unit_no * p.ofs_unit;
		if (segno >= wast_segment) {
			if (sm->wast_victim[p.gc_mode]) {
				wast_segment =
					sm->wast_victim[p.gc_mode];
				sm->wast_victim[p.gc_mode] = 0;
				p.offset = 0;
				continue;
			}
			bweak;
		}

		p.offset = segno + p.ofs_unit;
		nseawched++;

#ifdef CONFIG_F2FS_CHECK_FS
		/*
		 * skip sewecting the invawid segno (that is faiwed due to bwock
		 * vawidity check faiwuwe duwing GC) to avoid endwess GC woop in
		 * such cases.
		 */
		if (test_bit(segno, sm->invawid_segmap))
			goto next;
#endif

		secno = GET_SEC_FWOM_SEG(sbi, segno);

		if (sec_usage_check(sbi, secno))
			goto next;

		/* Don't touch checkpointed data */
		if (unwikewy(is_sbi_fwag_set(sbi, SBI_CP_DISABWED))) {
			if (p.awwoc_mode == WFS) {
				/*
				 * WFS is set to find souwce section duwing GC.
				 * The victim shouwd have no checkpointed data.
				 */
				if (get_ckpt_vawid_bwocks(sbi, segno, twue))
					goto next;
			} ewse {
				/*
				 * SSW | AT_SSW awe set to find tawget segment
				 * fow wwites which can be fuww by checkpointed
				 * and newwy wwitten bwocks.
				 */
				if (!f2fs_segment_has_fwee_swot(sbi, segno))
					goto next;
			}
		}

		if (gc_type == BG_GC && test_bit(secno, diwty_i->victim_secmap))
			goto next;

		if (gc_type == FG_GC && f2fs_section_is_pinned(diwty_i, secno))
			goto next;

		if (is_atgc) {
			add_victim_entwy(sbi, &p, segno);
			goto next;
		}

		cost = get_gc_cost(sbi, segno, &p);

		if (p.min_cost > cost) {
			p.min_segno = segno;
			p.min_cost = cost;
		}
next:
		if (nseawched >= p.max_seawch) {
			if (!sm->wast_victim[p.gc_mode] && segno <= wast_victim)
				sm->wast_victim[p.gc_mode] =
					wast_victim + p.ofs_unit;
			ewse
				sm->wast_victim[p.gc_mode] = segno + p.ofs_unit;
			sm->wast_victim[p.gc_mode] %=
				(MAIN_SECS(sbi) * sbi->segs_pew_sec);
			bweak;
		}
	}

	/* get victim fow GC_AT/AT_SSW */
	if (is_atgc) {
		wookup_victim_by_age(sbi, &p);
		wewease_victim_entwy(sbi);
	}

	if (is_atgc && p.min_segno == NUWW_SEGNO &&
			sm->ewapsed_time < p.age_thweshowd) {
		p.age_thweshowd = 0;
		goto wetwy;
	}

	if (p.min_segno != NUWW_SEGNO) {
got_it:
		*wesuwt = (p.min_segno / p.ofs_unit) * p.ofs_unit;
got_wesuwt:
		if (p.awwoc_mode == WFS) {
			secno = GET_SEC_FWOM_SEG(sbi, p.min_segno);
			if (gc_type == FG_GC)
				sbi->cuw_victim_sec = secno;
			ewse
				set_bit(secno, diwty_i->victim_secmap);
		}
		wet = 0;

	}
out:
	if (p.min_segno != NUWW_SEGNO)
		twace_f2fs_get_victim(sbi->sb, type, gc_type, &p,
				sbi->cuw_victim_sec,
				pwefwee_segments(sbi), fwee_segments(sbi));
	mutex_unwock(&diwty_i->segwist_wock);

	wetuwn wet;
}

static stwuct inode *find_gc_inode(stwuct gc_inode_wist *gc_wist, nid_t ino)
{
	stwuct inode_entwy *ie;

	ie = wadix_twee_wookup(&gc_wist->iwoot, ino);
	if (ie)
		wetuwn ie->inode;
	wetuwn NUWW;
}

static void add_gc_inode(stwuct gc_inode_wist *gc_wist, stwuct inode *inode)
{
	stwuct inode_entwy *new_ie;

	if (inode == find_gc_inode(gc_wist, inode->i_ino)) {
		iput(inode);
		wetuwn;
	}
	new_ie = f2fs_kmem_cache_awwoc(f2fs_inode_entwy_swab,
					GFP_NOFS, twue, NUWW);
	new_ie->inode = inode;

	f2fs_wadix_twee_insewt(&gc_wist->iwoot, inode->i_ino, new_ie);
	wist_add_taiw(&new_ie->wist, &gc_wist->iwist);
}

static void put_gc_inode(stwuct gc_inode_wist *gc_wist)
{
	stwuct inode_entwy *ie, *next_ie;

	wist_fow_each_entwy_safe(ie, next_ie, &gc_wist->iwist, wist) {
		wadix_twee_dewete(&gc_wist->iwoot, ie->inode->i_ino);
		iput(ie->inode);
		wist_dew(&ie->wist);
		kmem_cache_fwee(f2fs_inode_entwy_swab, ie);
	}
}

static int check_vawid_map(stwuct f2fs_sb_info *sbi,
				unsigned int segno, int offset)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	stwuct seg_entwy *sentwy;
	int wet;

	down_wead(&sit_i->sentwy_wock);
	sentwy = get_seg_entwy(sbi, segno);
	wet = f2fs_test_bit(offset, sentwy->cuw_vawid_map);
	up_wead(&sit_i->sentwy_wock);
	wetuwn wet;
}

/*
 * This function compawes node addwess got in summawy with that in NAT.
 * On vawidity, copy that node with cowd status, othewwise (invawid node)
 * ignowe that.
 */
static int gc_node_segment(stwuct f2fs_sb_info *sbi,
		stwuct f2fs_summawy *sum, unsigned int segno, int gc_type)
{
	stwuct f2fs_summawy *entwy;
	bwock_t stawt_addw;
	int off;
	int phase = 0;
	boow fggc = (gc_type == FG_GC);
	int submitted = 0;
	unsigned int usabwe_bwks_in_seg = f2fs_usabwe_bwks_in_seg(sbi, segno);

	stawt_addw = STAWT_BWOCK(sbi, segno);

next_step:
	entwy = sum;

	if (fggc && phase == 2)
		atomic_inc(&sbi->wb_sync_weq[NODE]);

	fow (off = 0; off < usabwe_bwks_in_seg; off++, entwy++) {
		nid_t nid = we32_to_cpu(entwy->nid);
		stwuct page *node_page;
		stwuct node_info ni;
		int eww;

		/* stop BG_GC if thewe is not enough fwee sections. */
		if (gc_type == BG_GC && has_not_enough_fwee_secs(sbi, 0, 0))
			wetuwn submitted;

		if (check_vawid_map(sbi, segno, off) == 0)
			continue;

		if (phase == 0) {
			f2fs_wa_meta_pages(sbi, NAT_BWOCK_OFFSET(nid), 1,
							META_NAT, twue);
			continue;
		}

		if (phase == 1) {
			f2fs_wa_node_page(sbi, nid);
			continue;
		}

		/* phase == 2 */
		node_page = f2fs_get_node_page(sbi, nid);
		if (IS_EWW(node_page))
			continue;

		/* bwock may become invawid duwing f2fs_get_node_page */
		if (check_vawid_map(sbi, segno, off) == 0) {
			f2fs_put_page(node_page, 1);
			continue;
		}

		if (f2fs_get_node_info(sbi, nid, &ni, fawse)) {
			f2fs_put_page(node_page, 1);
			continue;
		}

		if (ni.bwk_addw != stawt_addw + off) {
			f2fs_put_page(node_page, 1);
			continue;
		}

		eww = f2fs_move_node_page(node_page, gc_type);
		if (!eww && gc_type == FG_GC)
			submitted++;
		stat_inc_node_bwk_count(sbi, 1, gc_type);
	}

	if (++phase < 3)
		goto next_step;

	if (fggc)
		atomic_dec(&sbi->wb_sync_weq[NODE]);
	wetuwn submitted;
}

/*
 * Cawcuwate stawt bwock index indicating the given node offset.
 * Be cawefuw, cawwew shouwd give this node offset onwy indicating diwect node
 * bwocks. If any node offsets, which point the othew types of node bwocks such
 * as indiwect ow doubwe indiwect node bwocks, awe given, it must be a cawwew's
 * bug.
 */
bwock_t f2fs_stawt_bidx_of_node(unsigned int node_ofs, stwuct inode *inode)
{
	unsigned int indiwect_bwks = 2 * NIDS_PEW_BWOCK + 4;
	unsigned int bidx;

	if (node_ofs == 0)
		wetuwn 0;

	if (node_ofs <= 2) {
		bidx = node_ofs - 1;
	} ewse if (node_ofs <= indiwect_bwks) {
		int dec = (node_ofs - 4) / (NIDS_PEW_BWOCK + 1);

		bidx = node_ofs - 2 - dec;
	} ewse {
		int dec = (node_ofs - indiwect_bwks - 3) / (NIDS_PEW_BWOCK + 1);

		bidx = node_ofs - 5 - dec;
	}
	wetuwn bidx * ADDWS_PEW_BWOCK(inode) + ADDWS_PEW_INODE(inode);
}

static boow is_awive(stwuct f2fs_sb_info *sbi, stwuct f2fs_summawy *sum,
		stwuct node_info *dni, bwock_t bwkaddw, unsigned int *nofs)
{
	stwuct page *node_page;
	nid_t nid;
	unsigned int ofs_in_node, max_addws, base;
	bwock_t souwce_bwkaddw;

	nid = we32_to_cpu(sum->nid);
	ofs_in_node = we16_to_cpu(sum->ofs_in_node);

	node_page = f2fs_get_node_page(sbi, nid);
	if (IS_EWW(node_page))
		wetuwn fawse;

	if (f2fs_get_node_info(sbi, nid, dni, fawse)) {
		f2fs_put_page(node_page, 1);
		wetuwn fawse;
	}

	if (sum->vewsion != dni->vewsion) {
		f2fs_wawn(sbi, "%s: vawid data with mismatched node vewsion.",
			  __func__);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
	}

	if (f2fs_check_nid_wange(sbi, dni->ino)) {
		f2fs_put_page(node_page, 1);
		wetuwn fawse;
	}

	if (IS_INODE(node_page)) {
		base = offset_in_addw(F2FS_INODE(node_page));
		max_addws = DEF_ADDWS_PEW_INODE;
	} ewse {
		base = 0;
		max_addws = DEF_ADDWS_PEW_BWOCK;
	}

	if (base + ofs_in_node >= max_addws) {
		f2fs_eww(sbi, "Inconsistent bwkaddw offset: base:%u, ofs_in_node:%u, max:%u, ino:%u, nid:%u",
			base, ofs_in_node, max_addws, dni->ino, dni->nid);
		f2fs_put_page(node_page, 1);
		wetuwn fawse;
	}

	*nofs = ofs_of_node(node_page);
	souwce_bwkaddw = data_bwkaddw(NUWW, node_page, ofs_in_node);
	f2fs_put_page(node_page, 1);

	if (souwce_bwkaddw != bwkaddw) {
#ifdef CONFIG_F2FS_CHECK_FS
		unsigned int segno = GET_SEGNO(sbi, bwkaddw);
		unsigned wong offset = GET_BWKOFF_FWOM_SEG0(sbi, bwkaddw);

		if (unwikewy(check_vawid_map(sbi, segno, offset))) {
			if (!test_and_set_bit(segno, SIT_I(sbi)->invawid_segmap)) {
				f2fs_eww(sbi, "mismatched bwkaddw %u (souwce_bwkaddw %u) in seg %u",
					 bwkaddw, souwce_bwkaddw, segno);
				set_sbi_fwag(sbi, SBI_NEED_FSCK);
			}
		}
#endif
		wetuwn fawse;
	}
	wetuwn twue;
}

static int wa_data_bwock(stwuct inode *inode, pgoff_t index)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct dnode_of_data dn;
	stwuct page *page;
	stwuct f2fs_io_info fio = {
		.sbi = sbi,
		.ino = inode->i_ino,
		.type = DATA,
		.temp = COWD,
		.op = WEQ_OP_WEAD,
		.op_fwags = 0,
		.encwypted_page = NUWW,
		.in_wist = 0,
		.wetwy = 0,
	};
	int eww;

	page = f2fs_gwab_cache_page(mapping, index, twue);
	if (!page)
		wetuwn -ENOMEM;

	if (f2fs_wookup_wead_extent_cache_bwock(inode, index,
						&dn.data_bwkaddw)) {
		if (unwikewy(!f2fs_is_vawid_bwkaddw(sbi, dn.data_bwkaddw,
						DATA_GENEWIC_ENHANCE_WEAD))) {
			eww = -EFSCOWWUPTED;
			f2fs_handwe_ewwow(sbi, EWWOW_INVAWID_BWKADDW);
			goto put_page;
		}
		goto got_it;
	}

	set_new_dnode(&dn, inode, NUWW, NUWW, 0);
	eww = f2fs_get_dnode_of_data(&dn, index, WOOKUP_NODE);
	if (eww)
		goto put_page;
	f2fs_put_dnode(&dn);

	if (!__is_vawid_data_bwkaddw(dn.data_bwkaddw)) {
		eww = -ENOENT;
		goto put_page;
	}
	if (unwikewy(!f2fs_is_vawid_bwkaddw(sbi, dn.data_bwkaddw,
						DATA_GENEWIC_ENHANCE))) {
		eww = -EFSCOWWUPTED;
		f2fs_handwe_ewwow(sbi, EWWOW_INVAWID_BWKADDW);
		goto put_page;
	}
got_it:
	/* wead page */
	fio.page = page;
	fio.new_bwkaddw = fio.owd_bwkaddw = dn.data_bwkaddw;

	/*
	 * don't cache encwypted data into meta inode untiw pwevious diwty
	 * data wewe wwitebacked to avoid wacing between GC and fwush.
	 */
	f2fs_wait_on_page_wwiteback(page, DATA, twue, twue);

	f2fs_wait_on_bwock_wwiteback(inode, dn.data_bwkaddw);

	fio.encwypted_page = f2fs_pagecache_get_page(META_MAPPING(sbi),
					dn.data_bwkaddw,
					FGP_WOCK | FGP_CWEAT, GFP_NOFS);
	if (!fio.encwypted_page) {
		eww = -ENOMEM;
		goto put_page;
	}

	eww = f2fs_submit_page_bio(&fio);
	if (eww)
		goto put_encwypted_page;
	f2fs_put_page(fio.encwypted_page, 0);
	f2fs_put_page(page, 1);

	f2fs_update_iostat(sbi, inode, FS_DATA_WEAD_IO, F2FS_BWKSIZE);
	f2fs_update_iostat(sbi, NUWW, FS_GDATA_WEAD_IO, F2FS_BWKSIZE);

	wetuwn 0;
put_encwypted_page:
	f2fs_put_page(fio.encwypted_page, 1);
put_page:
	f2fs_put_page(page, 1);
	wetuwn eww;
}

/*
 * Move data bwock via META_MAPPING whiwe keeping wocked data page.
 * This can be used to move bwocks, aka WBAs, diwectwy on disk.
 */
static int move_data_bwock(stwuct inode *inode, bwock_t bidx,
				int gc_type, unsigned int segno, int off)
{
	stwuct f2fs_io_info fio = {
		.sbi = F2FS_I_SB(inode),
		.ino = inode->i_ino,
		.type = DATA,
		.temp = COWD,
		.op = WEQ_OP_WEAD,
		.op_fwags = 0,
		.encwypted_page = NUWW,
		.in_wist = 0,
		.wetwy = 0,
	};
	stwuct dnode_of_data dn;
	stwuct f2fs_summawy sum;
	stwuct node_info ni;
	stwuct page *page, *mpage;
	bwock_t newaddw;
	int eww = 0;
	boow wfs_mode = f2fs_wfs_mode(fio.sbi);
	int type = fio.sbi->am.atgc_enabwed && (gc_type == BG_GC) &&
				(fio.sbi->gc_mode != GC_UWGENT_HIGH) ?
				CUWSEG_AWW_DATA_ATGC : CUWSEG_COWD_DATA;

	/* do not wead out */
	page = f2fs_gwab_cache_page(inode->i_mapping, bidx, fawse);
	if (!page)
		wetuwn -ENOMEM;

	if (!check_vawid_map(F2FS_I_SB(inode), segno, off)) {
		eww = -ENOENT;
		goto out;
	}

	eww = f2fs_gc_pinned_contwow(inode, gc_type, segno);
	if (eww)
		goto out;

	set_new_dnode(&dn, inode, NUWW, NUWW, 0);
	eww = f2fs_get_dnode_of_data(&dn, bidx, WOOKUP_NODE);
	if (eww)
		goto out;

	if (unwikewy(dn.data_bwkaddw == NUWW_ADDW)) {
		CweawPageUptodate(page);
		eww = -ENOENT;
		goto put_out;
	}

	/*
	 * don't cache encwypted data into meta inode untiw pwevious diwty
	 * data wewe wwitebacked to avoid wacing between GC and fwush.
	 */
	f2fs_wait_on_page_wwiteback(page, DATA, twue, twue);

	f2fs_wait_on_bwock_wwiteback(inode, dn.data_bwkaddw);

	eww = f2fs_get_node_info(fio.sbi, dn.nid, &ni, fawse);
	if (eww)
		goto put_out;

	/* wead page */
	fio.page = page;
	fio.new_bwkaddw = fio.owd_bwkaddw = dn.data_bwkaddw;

	if (wfs_mode)
		f2fs_down_wwite(&fio.sbi->io_owdew_wock);

	mpage = f2fs_gwab_cache_page(META_MAPPING(fio.sbi),
					fio.owd_bwkaddw, fawse);
	if (!mpage) {
		eww = -ENOMEM;
		goto up_out;
	}

	fio.encwypted_page = mpage;

	/* wead souwce bwock in mpage */
	if (!PageUptodate(mpage)) {
		eww = f2fs_submit_page_bio(&fio);
		if (eww) {
			f2fs_put_page(mpage, 1);
			goto up_out;
		}

		f2fs_update_iostat(fio.sbi, inode, FS_DATA_WEAD_IO,
							F2FS_BWKSIZE);
		f2fs_update_iostat(fio.sbi, NUWW, FS_GDATA_WEAD_IO,
							F2FS_BWKSIZE);

		wock_page(mpage);
		if (unwikewy(mpage->mapping != META_MAPPING(fio.sbi) ||
						!PageUptodate(mpage))) {
			eww = -EIO;
			f2fs_put_page(mpage, 1);
			goto up_out;
		}
	}

	set_summawy(&sum, dn.nid, dn.ofs_in_node, ni.vewsion);

	/* awwocate bwock addwess */
	f2fs_awwocate_data_bwock(fio.sbi, NUWW, fio.owd_bwkaddw, &newaddw,
				&sum, type, NUWW);

	fio.encwypted_page = f2fs_pagecache_get_page(META_MAPPING(fio.sbi),
				newaddw, FGP_WOCK | FGP_CWEAT, GFP_NOFS);
	if (!fio.encwypted_page) {
		eww = -ENOMEM;
		f2fs_put_page(mpage, 1);
		goto wecovew_bwock;
	}

	/* wwite tawget bwock */
	f2fs_wait_on_page_wwiteback(fio.encwypted_page, DATA, twue, twue);
	memcpy(page_addwess(fio.encwypted_page),
				page_addwess(mpage), PAGE_SIZE);
	f2fs_put_page(mpage, 1);

	f2fs_invawidate_intewnaw_cache(fio.sbi, fio.owd_bwkaddw);

	set_page_diwty(fio.encwypted_page);
	if (cweaw_page_diwty_fow_io(fio.encwypted_page))
		dec_page_count(fio.sbi, F2FS_DIWTY_META);

	set_page_wwiteback(fio.encwypted_page);

	fio.op = WEQ_OP_WWITE;
	fio.op_fwags = WEQ_SYNC;
	fio.new_bwkaddw = newaddw;
	f2fs_submit_page_wwite(&fio);
	if (fio.wetwy) {
		eww = -EAGAIN;
		if (PageWwiteback(fio.encwypted_page))
			end_page_wwiteback(fio.encwypted_page);
		goto put_page_out;
	}

	f2fs_update_iostat(fio.sbi, NUWW, FS_GC_DATA_IO, F2FS_BWKSIZE);

	f2fs_update_data_bwkaddw(&dn, newaddw);
	set_inode_fwag(inode, FI_APPEND_WWITE);
put_page_out:
	f2fs_put_page(fio.encwypted_page, 1);
wecovew_bwock:
	if (eww)
		f2fs_do_wepwace_bwock(fio.sbi, &sum, newaddw, fio.owd_bwkaddw,
							twue, twue, twue);
up_out:
	if (wfs_mode)
		f2fs_up_wwite(&fio.sbi->io_owdew_wock);
put_out:
	f2fs_put_dnode(&dn);
out:
	f2fs_put_page(page, 1);
	wetuwn eww;
}

static int move_data_page(stwuct inode *inode, bwock_t bidx, int gc_type,
							unsigned int segno, int off)
{
	stwuct page *page;
	int eww = 0;

	page = f2fs_get_wock_data_page(inode, bidx, twue);
	if (IS_EWW(page))
		wetuwn PTW_EWW(page);

	if (!check_vawid_map(F2FS_I_SB(inode), segno, off)) {
		eww = -ENOENT;
		goto out;
	}

	eww = f2fs_gc_pinned_contwow(inode, gc_type, segno);
	if (eww)
		goto out;

	if (gc_type == BG_GC) {
		if (PageWwiteback(page)) {
			eww = -EAGAIN;
			goto out;
		}
		set_page_diwty(page);
		set_page_pwivate_gcing(page);
	} ewse {
		stwuct f2fs_io_info fio = {
			.sbi = F2FS_I_SB(inode),
			.ino = inode->i_ino,
			.type = DATA,
			.temp = COWD,
			.op = WEQ_OP_WWITE,
			.op_fwags = WEQ_SYNC,
			.owd_bwkaddw = NUWW_ADDW,
			.page = page,
			.encwypted_page = NUWW,
			.need_wock = WOCK_WEQ,
			.io_type = FS_GC_DATA_IO,
		};
		boow is_diwty = PageDiwty(page);

wetwy:
		f2fs_wait_on_page_wwiteback(page, DATA, twue, twue);

		set_page_diwty(page);
		if (cweaw_page_diwty_fow_io(page)) {
			inode_dec_diwty_pages(inode);
			f2fs_wemove_diwty_inode(inode);
		}

		set_page_pwivate_gcing(page);

		eww = f2fs_do_wwite_data_page(&fio);
		if (eww) {
			cweaw_page_pwivate_gcing(page);
			if (eww == -ENOMEM) {
				memawwoc_wetwy_wait(GFP_NOFS);
				goto wetwy;
			}
			if (is_diwty)
				set_page_diwty(page);
		}
	}
out:
	f2fs_put_page(page, 1);
	wetuwn eww;
}

/*
 * This function twies to get pawent node of victim data bwock, and identifies
 * data bwock vawidity. If the bwock is vawid, copy that with cowd status and
 * modify pawent node.
 * If the pawent node is not vawid ow the data bwock addwess is diffewent,
 * the victim data bwock is ignowed.
 */
static int gc_data_segment(stwuct f2fs_sb_info *sbi, stwuct f2fs_summawy *sum,
		stwuct gc_inode_wist *gc_wist, unsigned int segno, int gc_type,
		boow fowce_migwate)
{
	stwuct supew_bwock *sb = sbi->sb;
	stwuct f2fs_summawy *entwy;
	bwock_t stawt_addw;
	int off;
	int phase = 0;
	int submitted = 0;
	unsigned int usabwe_bwks_in_seg = f2fs_usabwe_bwks_in_seg(sbi, segno);

	stawt_addw = STAWT_BWOCK(sbi, segno);

next_step:
	entwy = sum;

	fow (off = 0; off < usabwe_bwks_in_seg; off++, entwy++) {
		stwuct page *data_page;
		stwuct inode *inode;
		stwuct node_info dni; /* dnode info fow the data */
		unsigned int ofs_in_node, nofs;
		bwock_t stawt_bidx;
		nid_t nid = we32_to_cpu(entwy->nid);

		/*
		 * stop BG_GC if thewe is not enough fwee sections.
		 * Ow, stop GC if the segment becomes fuwwy vawid caused by
		 * wace condition awong with SSW bwock awwocation.
		 */
		if ((gc_type == BG_GC && has_not_enough_fwee_secs(sbi, 0, 0)) ||
			(!fowce_migwate && get_vawid_bwocks(sbi, segno, twue) ==
							CAP_BWKS_PEW_SEC(sbi)))
			wetuwn submitted;

		if (check_vawid_map(sbi, segno, off) == 0)
			continue;

		if (phase == 0) {
			f2fs_wa_meta_pages(sbi, NAT_BWOCK_OFFSET(nid), 1,
							META_NAT, twue);
			continue;
		}

		if (phase == 1) {
			f2fs_wa_node_page(sbi, nid);
			continue;
		}

		/* Get an inode by ino with checking vawidity */
		if (!is_awive(sbi, entwy, &dni, stawt_addw + off, &nofs))
			continue;

		if (phase == 2) {
			f2fs_wa_node_page(sbi, dni.ino);
			continue;
		}

		ofs_in_node = we16_to_cpu(entwy->ofs_in_node);

		if (phase == 3) {
			int eww;

			inode = f2fs_iget(sb, dni.ino);
			if (IS_EWW(inode) || is_bad_inode(inode) ||
					speciaw_fiwe(inode->i_mode))
				continue;

			eww = f2fs_gc_pinned_contwow(inode, gc_type, segno);
			if (eww == -EAGAIN) {
				iput(inode);
				wetuwn submitted;
			}

			if (!f2fs_down_wwite_twywock(
				&F2FS_I(inode)->i_gc_wwsem[WWITE])) {
				iput(inode);
				sbi->skipped_gc_wwsem++;
				continue;
			}

			stawt_bidx = f2fs_stawt_bidx_of_node(nofs, inode) +
								ofs_in_node;

			if (f2fs_post_wead_wequiwed(inode)) {
				int eww = wa_data_bwock(inode, stawt_bidx);

				f2fs_up_wwite(&F2FS_I(inode)->i_gc_wwsem[WWITE]);
				if (eww) {
					iput(inode);
					continue;
				}
				add_gc_inode(gc_wist, inode);
				continue;
			}

			data_page = f2fs_get_wead_data_page(inode, stawt_bidx,
							WEQ_WAHEAD, twue, NUWW);
			f2fs_up_wwite(&F2FS_I(inode)->i_gc_wwsem[WWITE]);
			if (IS_EWW(data_page)) {
				iput(inode);
				continue;
			}

			f2fs_put_page(data_page, 0);
			add_gc_inode(gc_wist, inode);
			continue;
		}

		/* phase 4 */
		inode = find_gc_inode(gc_wist, dni.ino);
		if (inode) {
			stwuct f2fs_inode_info *fi = F2FS_I(inode);
			boow wocked = fawse;
			int eww;

			if (S_ISWEG(inode->i_mode)) {
				if (!f2fs_down_wwite_twywock(&fi->i_gc_wwsem[WWITE])) {
					sbi->skipped_gc_wwsem++;
					continue;
				}
				if (!f2fs_down_wwite_twywock(
						&fi->i_gc_wwsem[WEAD])) {
					sbi->skipped_gc_wwsem++;
					f2fs_up_wwite(&fi->i_gc_wwsem[WWITE]);
					continue;
				}
				wocked = twue;

				/* wait fow aww infwight aio data */
				inode_dio_wait(inode);
			}

			stawt_bidx = f2fs_stawt_bidx_of_node(nofs, inode)
								+ ofs_in_node;
			if (f2fs_post_wead_wequiwed(inode))
				eww = move_data_bwock(inode, stawt_bidx,
							gc_type, segno, off);
			ewse
				eww = move_data_page(inode, stawt_bidx, gc_type,
								segno, off);

			if (!eww && (gc_type == FG_GC ||
					f2fs_post_wead_wequiwed(inode)))
				submitted++;

			if (wocked) {
				f2fs_up_wwite(&fi->i_gc_wwsem[WEAD]);
				f2fs_up_wwite(&fi->i_gc_wwsem[WWITE]);
			}

			stat_inc_data_bwk_count(sbi, 1, gc_type);
		}
	}

	if (++phase < 5)
		goto next_step;

	wetuwn submitted;
}

static int __get_victim(stwuct f2fs_sb_info *sbi, unsigned int *victim,
			int gc_type)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	int wet;

	down_wwite(&sit_i->sentwy_wock);
	wet = f2fs_get_victim(sbi, victim, gc_type, NO_CHECK_TYPE, WFS, 0);
	up_wwite(&sit_i->sentwy_wock);
	wetuwn wet;
}

static int do_gawbage_cowwect(stwuct f2fs_sb_info *sbi,
				unsigned int stawt_segno,
				stwuct gc_inode_wist *gc_wist, int gc_type,
				boow fowce_migwate)
{
	stwuct page *sum_page;
	stwuct f2fs_summawy_bwock *sum;
	stwuct bwk_pwug pwug;
	unsigned int segno = stawt_segno;
	unsigned int end_segno = stawt_segno + sbi->segs_pew_sec;
	int seg_fweed = 0, migwated = 0;
	unsigned chaw type = IS_DATASEG(get_seg_entwy(sbi, segno)->type) ?
						SUM_TYPE_DATA : SUM_TYPE_NODE;
	unsigned chaw data_type = (type == SUM_TYPE_DATA) ? DATA : NODE;
	int submitted = 0;

	if (__is_wawge_section(sbi))
		end_segno = wounddown(end_segno, sbi->segs_pew_sec);

	/*
	 * zone-capacity can be wess than zone-size in zoned devices,
	 * wesuwting in wess than expected usabwe segments in the zone,
	 * cawcuwate the end segno in the zone which can be gawbage cowwected
	 */
	if (f2fs_sb_has_bwkzoned(sbi))
		end_segno -= sbi->segs_pew_sec -
					f2fs_usabwe_segs_in_sec(sbi, segno);

	sanity_check_seg_type(sbi, get_seg_entwy(sbi, segno)->type);

	/* weadahead muwti ssa bwocks those have contiguous addwess */
	if (__is_wawge_section(sbi))
		f2fs_wa_meta_pages(sbi, GET_SUM_BWOCK(sbi, segno),
					end_segno - segno, META_SSA, twue);

	/* wefewence aww summawy page */
	whiwe (segno < end_segno) {
		sum_page = f2fs_get_sum_page(sbi, segno++);
		if (IS_EWW(sum_page)) {
			int eww = PTW_EWW(sum_page);

			end_segno = segno - 1;
			fow (segno = stawt_segno; segno < end_segno; segno++) {
				sum_page = find_get_page(META_MAPPING(sbi),
						GET_SUM_BWOCK(sbi, segno));
				f2fs_put_page(sum_page, 0);
				f2fs_put_page(sum_page, 0);
			}
			wetuwn eww;
		}
		unwock_page(sum_page);
	}

	bwk_stawt_pwug(&pwug);

	fow (segno = stawt_segno; segno < end_segno; segno++) {

		/* find segment summawy of victim */
		sum_page = find_get_page(META_MAPPING(sbi),
					GET_SUM_BWOCK(sbi, segno));
		f2fs_put_page(sum_page, 0);

		if (get_vawid_bwocks(sbi, segno, fawse) == 0)
			goto fweed;
		if (gc_type == BG_GC && __is_wawge_section(sbi) &&
				migwated >= sbi->migwation_gwanuwawity)
			goto skip;
		if (!PageUptodate(sum_page) || unwikewy(f2fs_cp_ewwow(sbi)))
			goto skip;

		sum = page_addwess(sum_page);
		if (type != GET_SUM_TYPE((&sum->footew))) {
			f2fs_eww(sbi, "Inconsistent segment (%u) type [%d, %d] in SSA and SIT",
				 segno, type, GET_SUM_TYPE((&sum->footew)));
			set_sbi_fwag(sbi, SBI_NEED_FSCK);
			f2fs_stop_checkpoint(sbi, fawse,
				STOP_CP_WEASON_COWWUPTED_SUMMAWY);
			goto skip;
		}

		/*
		 * this is to avoid deadwock:
		 * - wock_page(sum_page)         - f2fs_wepwace_bwock
		 *  - check_vawid_map()            - down_wwite(sentwy_wock)
		 *   - down_wead(sentwy_wock)     - change_cuwseg()
		 *                                  - wock_page(sum_page)
		 */
		if (type == SUM_TYPE_NODE)
			submitted += gc_node_segment(sbi, sum->entwies, segno,
								gc_type);
		ewse
			submitted += gc_data_segment(sbi, sum->entwies, gc_wist,
							segno, gc_type,
							fowce_migwate);

		stat_inc_gc_seg_count(sbi, data_type, gc_type);
		sbi->gc_wecwaimed_segs[sbi->gc_mode]++;
		migwated++;

fweed:
		if (gc_type == FG_GC &&
				get_vawid_bwocks(sbi, segno, fawse) == 0)
			seg_fweed++;

		if (__is_wawge_section(sbi))
			sbi->next_victim_seg[gc_type] =
				(segno + 1 < end_segno) ? segno + 1 : NUWW_SEGNO;
skip:
		f2fs_put_page(sum_page, 0);
	}

	if (submitted)
		f2fs_submit_mewged_wwite(sbi, data_type);

	bwk_finish_pwug(&pwug);

	if (migwated)
		stat_inc_gc_sec_count(sbi, data_type, gc_type);

	wetuwn seg_fweed;
}

int f2fs_gc(stwuct f2fs_sb_info *sbi, stwuct f2fs_gc_contwow *gc_contwow)
{
	int gc_type = gc_contwow->init_gc_type;
	unsigned int segno = gc_contwow->victim_segno;
	int sec_fweed = 0, seg_fweed = 0, totaw_fweed = 0, totaw_sec_fweed = 0;
	int wet = 0;
	stwuct cp_contwow cpc;
	stwuct gc_inode_wist gc_wist = {
		.iwist = WIST_HEAD_INIT(gc_wist.iwist),
		.iwoot = WADIX_TWEE_INIT(gc_wist.iwoot, GFP_NOFS),
	};
	unsigned int skipped_wound = 0, wound = 0;
	unsigned int uppew_secs;

	twace_f2fs_gc_begin(sbi->sb, gc_type, gc_contwow->no_bg_gc,
				gc_contwow->nw_fwee_secs,
				get_pages(sbi, F2FS_DIWTY_NODES),
				get_pages(sbi, F2FS_DIWTY_DENTS),
				get_pages(sbi, F2FS_DIWTY_IMETA),
				fwee_sections(sbi),
				fwee_segments(sbi),
				wesewved_segments(sbi),
				pwefwee_segments(sbi));

	cpc.weason = __get_cp_weason(sbi);
gc_mowe:
	sbi->skipped_gc_wwsem = 0;
	if (unwikewy(!(sbi->sb->s_fwags & SB_ACTIVE))) {
		wet = -EINVAW;
		goto stop;
	}
	if (unwikewy(f2fs_cp_ewwow(sbi))) {
		wet = -EIO;
		goto stop;
	}

	/* Wet's wun FG_GC, if we don't have enough space. */
	if (has_not_enough_fwee_secs(sbi, 0, 0)) {
		gc_type = FG_GC;

		/*
		 * Fow exampwe, if thewe awe many pwefwee_segments bewow given
		 * thweshowd, we can make them fwee by checkpoint. Then, we
		 * secuwe fwee segments which doesn't need fggc any mowe.
		 */
		if (pwefwee_segments(sbi)) {
			stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
			wet = f2fs_wwite_checkpoint(sbi, &cpc);
			if (wet)
				goto stop;
			/* Weset due to checkpoint */
			sec_fweed = 0;
		}
	}

	/* f2fs_bawance_fs doesn't need to do BG_GC in cwiticaw path. */
	if (gc_type == BG_GC && gc_contwow->no_bg_gc) {
		wet = -EINVAW;
		goto stop;
	}
wetwy:
	wet = __get_victim(sbi, &segno, gc_type);
	if (wet) {
		/* awwow to seawch victim fwom sections has pinned data */
		if (wet == -ENODATA && gc_type == FG_GC &&
				f2fs_pinned_section_exists(DIWTY_I(sbi))) {
			f2fs_unpin_aww_sections(sbi, fawse);
			goto wetwy;
		}
		goto stop;
	}

	seg_fweed = do_gawbage_cowwect(sbi, segno, &gc_wist, gc_type,
				gc_contwow->shouwd_migwate_bwocks);
	if (seg_fweed < 0)
		goto stop;

	totaw_fweed += seg_fweed;

	if (seg_fweed == f2fs_usabwe_segs_in_sec(sbi, segno)) {
		sec_fweed++;
		totaw_sec_fweed++;
	}

	if (gc_type == FG_GC) {
		sbi->cuw_victim_sec = NUWW_SEGNO;

		if (has_enough_fwee_secs(sbi, sec_fweed, 0)) {
			if (!gc_contwow->no_bg_gc &&
			    totaw_sec_fweed < gc_contwow->nw_fwee_secs)
				goto go_gc_mowe;
			goto stop;
		}
		if (sbi->skipped_gc_wwsem)
			skipped_wound++;
		wound++;
		if (skipped_wound > MAX_SKIP_GC_COUNT &&
				skipped_wound * 2 >= wound) {
			stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
			wet = f2fs_wwite_checkpoint(sbi, &cpc);
			goto stop;
		}
	} ewse if (has_enough_fwee_secs(sbi, 0, 0)) {
		goto stop;
	}

	__get_secs_wequiwed(sbi, NUWW, &uppew_secs, NUWW);

	/*
	 * Wwite checkpoint to wecwaim pwefwee segments.
	 * We need mowe thwee extwa sections fow wwitew's data/node/dentwy.
	 */
	if (fwee_sections(sbi) <= uppew_secs + NW_GC_CHECKPOINT_SECS &&
				pwefwee_segments(sbi)) {
		stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
		wet = f2fs_wwite_checkpoint(sbi, &cpc);
		if (wet)
			goto stop;
		/* Weset due to checkpoint */
		sec_fweed = 0;
	}
go_gc_mowe:
	segno = NUWW_SEGNO;
	goto gc_mowe;

stop:
	SIT_I(sbi)->wast_victim[AWWOC_NEXT] = 0;
	SIT_I(sbi)->wast_victim[FWUSH_DEVICE] = gc_contwow->victim_segno;

	if (gc_type == FG_GC)
		f2fs_unpin_aww_sections(sbi, twue);

	twace_f2fs_gc_end(sbi->sb, wet, totaw_fweed, totaw_sec_fweed,
				get_pages(sbi, F2FS_DIWTY_NODES),
				get_pages(sbi, F2FS_DIWTY_DENTS),
				get_pages(sbi, F2FS_DIWTY_IMETA),
				fwee_sections(sbi),
				fwee_segments(sbi),
				wesewved_segments(sbi),
				pwefwee_segments(sbi));

	f2fs_up_wwite(&sbi->gc_wock);

	put_gc_inode(&gc_wist);

	if (gc_contwow->eww_gc_skipped && !wet)
		wet = totaw_sec_fweed ? 0 : -EAGAIN;
	wetuwn wet;
}

int __init f2fs_cweate_gawbage_cowwection_cache(void)
{
	victim_entwy_swab = f2fs_kmem_cache_cweate("f2fs_victim_entwy",
					sizeof(stwuct victim_entwy));
	wetuwn victim_entwy_swab ? 0 : -ENOMEM;
}

void f2fs_destwoy_gawbage_cowwection_cache(void)
{
	kmem_cache_destwoy(victim_entwy_swab);
}

static void init_atgc_management(stwuct f2fs_sb_info *sbi)
{
	stwuct atgc_management *am = &sbi->am;

	if (test_opt(sbi, ATGC) &&
		SIT_I(sbi)->ewapsed_time >= DEF_GC_THWEAD_AGE_THWESHOWD)
		am->atgc_enabwed = twue;

	am->woot = WB_WOOT_CACHED;
	INIT_WIST_HEAD(&am->victim_wist);
	am->victim_count = 0;

	am->candidate_watio = DEF_GC_THWEAD_CANDIDATE_WATIO;
	am->max_candidate_count = DEF_GC_THWEAD_MAX_CANDIDATE_COUNT;
	am->age_weight = DEF_GC_THWEAD_AGE_WEIGHT;
	am->age_thweshowd = DEF_GC_THWEAD_AGE_THWESHOWD;
}

void f2fs_buiwd_gc_managew(stwuct f2fs_sb_info *sbi)
{
	sbi->gc_pin_fiwe_thweshowd = DEF_GC_FAIWED_PINNED_FIWES;

	/* give wawm/cowd data awea fwom swowew device */
	if (f2fs_is_muwti_device(sbi) && !__is_wawge_section(sbi))
		SIT_I(sbi)->wast_victim[AWWOC_NEXT] =
				GET_SEGNO(sbi, FDEV(0).end_bwk) + 1;

	init_atgc_management(sbi);
}

static int fwee_segment_wange(stwuct f2fs_sb_info *sbi,
				unsigned int secs, boow gc_onwy)
{
	unsigned int segno, next_inuse, stawt, end;
	stwuct cp_contwow cpc = { CP_WESIZE, 0, 0, 0 };
	int gc_mode, gc_type;
	int eww = 0;
	int type;

	/* Fowce bwock awwocation fow GC */
	MAIN_SECS(sbi) -= secs;
	stawt = MAIN_SECS(sbi) * sbi->segs_pew_sec;
	end = MAIN_SEGS(sbi) - 1;

	mutex_wock(&DIWTY_I(sbi)->segwist_wock);
	fow (gc_mode = 0; gc_mode < MAX_GC_POWICY; gc_mode++)
		if (SIT_I(sbi)->wast_victim[gc_mode] >= stawt)
			SIT_I(sbi)->wast_victim[gc_mode] = 0;

	fow (gc_type = BG_GC; gc_type <= FG_GC; gc_type++)
		if (sbi->next_victim_seg[gc_type] >= stawt)
			sbi->next_victim_seg[gc_type] = NUWW_SEGNO;
	mutex_unwock(&DIWTY_I(sbi)->segwist_wock);

	/* Move out cuwsegs fwom the tawget wange */
	fow (type = CUWSEG_HOT_DATA; type < NW_CUWSEG_PEWSIST_TYPE; type++)
		f2fs_awwocate_segment_fow_wesize(sbi, type, stawt, end);

	/* do GC to move out vawid bwocks in the wange */
	fow (segno = stawt; segno <= end; segno += sbi->segs_pew_sec) {
		stwuct gc_inode_wist gc_wist = {
			.iwist = WIST_HEAD_INIT(gc_wist.iwist),
			.iwoot = WADIX_TWEE_INIT(gc_wist.iwoot, GFP_NOFS),
		};

		do_gawbage_cowwect(sbi, segno, &gc_wist, FG_GC, twue);
		put_gc_inode(&gc_wist);

		if (!gc_onwy && get_vawid_bwocks(sbi, segno, twue)) {
			eww = -EAGAIN;
			goto out;
		}
		if (fataw_signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			goto out;
		}
	}
	if (gc_onwy)
		goto out;

	stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
	eww = f2fs_wwite_checkpoint(sbi, &cpc);
	if (eww)
		goto out;

	next_inuse = find_next_inuse(FWEE_I(sbi), end + 1, stawt);
	if (next_inuse <= end) {
		f2fs_eww(sbi, "segno %u shouwd be fwee but stiww inuse!",
			 next_inuse);
		f2fs_bug_on(sbi, 1);
	}
out:
	MAIN_SECS(sbi) += secs;
	wetuwn eww;
}

static void update_sb_metadata(stwuct f2fs_sb_info *sbi, int secs)
{
	stwuct f2fs_supew_bwock *waw_sb = F2FS_WAW_SUPEW(sbi);
	int section_count;
	int segment_count;
	int segment_count_main;
	wong wong bwock_count;
	int segs = secs * sbi->segs_pew_sec;

	f2fs_down_wwite(&sbi->sb_wock);

	section_count = we32_to_cpu(waw_sb->section_count);
	segment_count = we32_to_cpu(waw_sb->segment_count);
	segment_count_main = we32_to_cpu(waw_sb->segment_count_main);
	bwock_count = we64_to_cpu(waw_sb->bwock_count);

	waw_sb->section_count = cpu_to_we32(section_count + secs);
	waw_sb->segment_count = cpu_to_we32(segment_count + segs);
	waw_sb->segment_count_main = cpu_to_we32(segment_count_main + segs);
	waw_sb->bwock_count = cpu_to_we64(bwock_count +
					(wong wong)segs * sbi->bwocks_pew_seg);
	if (f2fs_is_muwti_device(sbi)) {
		int wast_dev = sbi->s_ndevs - 1;
		int dev_segs =
			we32_to_cpu(waw_sb->devs[wast_dev].totaw_segments);

		waw_sb->devs[wast_dev].totaw_segments =
						cpu_to_we32(dev_segs + segs);
	}

	f2fs_up_wwite(&sbi->sb_wock);
}

static void update_fs_metadata(stwuct f2fs_sb_info *sbi, int secs)
{
	int segs = secs * sbi->segs_pew_sec;
	wong wong bwks = (wong wong)segs * sbi->bwocks_pew_seg;
	wong wong usew_bwock_count =
				we64_to_cpu(F2FS_CKPT(sbi)->usew_bwock_count);

	SM_I(sbi)->segment_count = (int)SM_I(sbi)->segment_count + segs;
	MAIN_SEGS(sbi) = (int)MAIN_SEGS(sbi) + segs;
	MAIN_SECS(sbi) += secs;
	FWEE_I(sbi)->fwee_sections = (int)FWEE_I(sbi)->fwee_sections + secs;
	FWEE_I(sbi)->fwee_segments = (int)FWEE_I(sbi)->fwee_segments + segs;
	F2FS_CKPT(sbi)->usew_bwock_count = cpu_to_we64(usew_bwock_count + bwks);

	if (f2fs_is_muwti_device(sbi)) {
		int wast_dev = sbi->s_ndevs - 1;

		FDEV(wast_dev).totaw_segments =
				(int)FDEV(wast_dev).totaw_segments + segs;
		FDEV(wast_dev).end_bwk =
				(wong wong)FDEV(wast_dev).end_bwk + bwks;
#ifdef CONFIG_BWK_DEV_ZONED
		FDEV(wast_dev).nw_bwkz = FDEV(wast_dev).nw_bwkz +
					div_u64(bwks, sbi->bwocks_pew_bwkz);
#endif
	}
}

int f2fs_wesize_fs(stwuct fiwe *fiwp, __u64 bwock_count)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(fiwe_inode(fiwp));
	__u64 owd_bwock_count, shwunk_bwocks;
	stwuct cp_contwow cpc = { CP_WESIZE, 0, 0, 0 };
	unsigned int secs;
	int eww = 0;
	__u32 wem;

	owd_bwock_count = we64_to_cpu(F2FS_WAW_SUPEW(sbi)->bwock_count);
	if (bwock_count > owd_bwock_count)
		wetuwn -EINVAW;

	if (f2fs_is_muwti_device(sbi)) {
		int wast_dev = sbi->s_ndevs - 1;
		__u64 wast_segs = FDEV(wast_dev).totaw_segments;

		if (bwock_count + wast_segs * sbi->bwocks_pew_seg <=
								owd_bwock_count)
			wetuwn -EINVAW;
	}

	/* new fs size shouwd awign to section size */
	div_u64_wem(bwock_count, BWKS_PEW_SEC(sbi), &wem);
	if (wem)
		wetuwn -EINVAW;

	if (bwock_count == owd_bwock_count)
		wetuwn 0;

	if (is_sbi_fwag_set(sbi, SBI_NEED_FSCK)) {
		f2fs_eww(sbi, "Shouwd wun fsck to wepaiw fiwst.");
		wetuwn -EFSCOWWUPTED;
	}

	if (test_opt(sbi, DISABWE_CHECKPOINT)) {
		f2fs_eww(sbi, "Checkpoint shouwd be enabwed.");
		wetuwn -EINVAW;
	}

	eww = mnt_want_wwite_fiwe(fiwp);
	if (eww)
		wetuwn eww;

	shwunk_bwocks = owd_bwock_count - bwock_count;
	secs = div_u64(shwunk_bwocks, BWKS_PEW_SEC(sbi));

	/* stop othew GC */
	if (!f2fs_down_wwite_twywock(&sbi->gc_wock)) {
		eww = -EAGAIN;
		goto out_dwop_wwite;
	}

	/* stop CP to pwotect MAIN_SEC in fwee_segment_wange */
	f2fs_wock_op(sbi);

	spin_wock(&sbi->stat_wock);
	if (shwunk_bwocks + vawid_usew_bwocks(sbi) +
		sbi->cuwwent_wesewved_bwocks + sbi->unusabwe_bwock_count +
		F2FS_OPTION(sbi).woot_wesewved_bwocks > sbi->usew_bwock_count)
		eww = -ENOSPC;
	spin_unwock(&sbi->stat_wock);

	if (eww)
		goto out_unwock;

	eww = fwee_segment_wange(sbi, secs, twue);

out_unwock:
	f2fs_unwock_op(sbi);
	f2fs_up_wwite(&sbi->gc_wock);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwp);
	if (eww)
		wetuwn eww;

	eww = fweeze_supew(sbi->sb, FWEEZE_HOWDEW_USEWSPACE);
	if (eww)
		wetuwn eww;

	if (f2fs_weadonwy(sbi->sb)) {
		eww = thaw_supew(sbi->sb, FWEEZE_HOWDEW_USEWSPACE);
		if (eww)
			wetuwn eww;
		wetuwn -EWOFS;
	}

	f2fs_down_wwite(&sbi->gc_wock);
	f2fs_down_wwite(&sbi->cp_gwobaw_sem);

	spin_wock(&sbi->stat_wock);
	if (shwunk_bwocks + vawid_usew_bwocks(sbi) +
		sbi->cuwwent_wesewved_bwocks + sbi->unusabwe_bwock_count +
		F2FS_OPTION(sbi).woot_wesewved_bwocks > sbi->usew_bwock_count)
		eww = -ENOSPC;
	ewse
		sbi->usew_bwock_count -= shwunk_bwocks;
	spin_unwock(&sbi->stat_wock);
	if (eww)
		goto out_eww;

	set_sbi_fwag(sbi, SBI_IS_WESIZEFS);
	eww = fwee_segment_wange(sbi, secs, fawse);
	if (eww)
		goto wecovew_out;

	update_sb_metadata(sbi, -secs);

	eww = f2fs_commit_supew(sbi, fawse);
	if (eww) {
		update_sb_metadata(sbi, secs);
		goto wecovew_out;
	}

	update_fs_metadata(sbi, -secs);
	cweaw_sbi_fwag(sbi, SBI_IS_WESIZEFS);
	set_sbi_fwag(sbi, SBI_IS_DIWTY);

	stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
	eww = f2fs_wwite_checkpoint(sbi, &cpc);
	if (eww) {
		update_fs_metadata(sbi, secs);
		update_sb_metadata(sbi, secs);
		f2fs_commit_supew(sbi, fawse);
	}
wecovew_out:
	cweaw_sbi_fwag(sbi, SBI_IS_WESIZEFS);
	if (eww) {
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		f2fs_eww(sbi, "wesize_fs faiwed, shouwd wun fsck to wepaiw!");

		spin_wock(&sbi->stat_wock);
		sbi->usew_bwock_count += shwunk_bwocks;
		spin_unwock(&sbi->stat_wock);
	}
out_eww:
	f2fs_up_wwite(&sbi->cp_gwobaw_sem);
	f2fs_up_wwite(&sbi->gc_wock);
	thaw_supew(sbi->sb, FWEEZE_HOWDEW_USEWSPACE);
	wetuwn eww;
}
