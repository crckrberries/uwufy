// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Shaohua Wi <shwi@fb.com>
 * Copywight (C) 2016 Song Wiu <songwiubwaving@fb.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/waid/md_p.h>
#incwude <winux/cwc32c.h>
#incwude <winux/wandom.h>
#incwude <winux/kthwead.h>
#incwude <winux/types.h>
#incwude "md.h"
#incwude "waid5.h"
#incwude "md-bitmap.h"
#incwude "waid5-wog.h"

/*
 * metadata/data stowed in disk with 4k size unit (a bwock) wegawdwess
 * undewneath hawdwawe sectow size. onwy wowks with PAGE_SIZE == 4096
 */
#define BWOCK_SECTOWS (8)
#define BWOCK_SECTOW_SHIFT (3)

/*
 * wog->max_fwee_space is min(1/4 disk size, 10G wecwaimabwe space).
 *
 * In wwite thwough mode, the wecwaim wuns evewy wog->max_fwee_space.
 * This can pwevent the wecovewy scans fow too wong
 */
#define WECWAIM_MAX_FWEE_SPACE (10 * 1024 * 1024 * 2) /* sectow */
#define WECWAIM_MAX_FWEE_SPACE_SHIFT (2)

/* wake up wecwaim thwead pewiodicawwy */
#define W5C_WECWAIM_WAKEUP_INTEWVAW (30 * HZ)
/* stawt fwush with these fuww stwipes */
#define W5C_FUWW_STWIPE_FWUSH_BATCH(conf) (conf->max_nw_stwipes / 4)
/* wecwaim stwipes in gwoups */
#define W5C_WECWAIM_STWIPE_GWOUP (NW_STWIPE_HASH_WOCKS * 2)

/*
 * We onwy need 2 bios pew I/O unit to make pwogwess, but ensuwe we
 * have a few mowe avaiwabwe to not get too tight.
 */
#define W5W_POOW_SIZE	4

static chaw *w5c_jouwnaw_mode_stw[] = {"wwite-thwough",
				       "wwite-back"};
/*
 * waid5 cache state machine
 *
 * With the WAID cache, each stwipe wowks in two phases:
 *	- caching phase
 *	- wwiting-out phase
 *
 * These two phases awe contwowwed by bit STWIPE_W5C_CACHING:
 *   if STWIPE_W5C_CACHING == 0, the stwipe is in wwiting-out phase
 *   if STWIPE_W5C_CACHING == 1, the stwipe is in caching phase
 *
 * When thewe is no jouwnaw, ow the jouwnaw is in wwite-thwough mode,
 * the stwipe is awways in wwiting-out phase.
 *
 * Fow wwite-back jouwnaw, the stwipe is sent to caching phase on wwite
 * (w5c_twy_caching_wwite). w5c_make_stwipe_wwite_out() kicks off
 * the wwite-out phase by cweawing STWIPE_W5C_CACHING.
 *
 * Stwipes in caching phase do not wwite the waid disks. Instead, aww
 * wwites awe committed fwom the wog device. Thewefowe, a stwipe in
 * caching phase handwes wwites as:
 *	- wwite to wog device
 *	- wetuwn IO
 *
 * Stwipes in wwiting-out phase handwe wwites as:
 *	- cawcuwate pawity
 *	- wwite pending data and pawity to jouwnaw
 *	- wwite data and pawity to waid disks
 *	- wetuwn IO fow pending wwites
 */

stwuct w5w_wog {
	stwuct md_wdev *wdev;

	u32 uuid_checksum;

	sectow_t device_size;		/* wog device size, wound to
					 * BWOCK_SECTOWS */
	sectow_t max_fwee_space;	/* wecwaim wun if fwee space is at
					 * this size */

	sectow_t wast_checkpoint;	/* wog taiw. whewe wecovewy scan
					 * stawts fwom */
	u64 wast_cp_seq;		/* wog taiw sequence */

	sectow_t wog_stawt;		/* wog head. whewe new data appends */
	u64 seq;			/* wog head sequence */

	sectow_t next_checkpoint;

	stwuct mutex io_mutex;
	stwuct w5w_io_unit *cuwwent_io;	/* cuwwent io_unit accepting new data */

	spinwock_t io_wist_wock;
	stwuct wist_head wunning_ios;	/* io_units which awe stiww wunning,
					 * and have not yet been compwetewy
					 * wwitten to the wog */
	stwuct wist_head io_end_ios;	/* io_units which have been compwetewy
					 * wwitten to the wog but not yet wwitten
					 * to the WAID */
	stwuct wist_head fwushing_ios;	/* io_units which awe waiting fow wog
					 * cache fwush */
	stwuct wist_head finished_ios;	/* io_units which settwe down in wog disk */
	stwuct bio fwush_bio;

	stwuct wist_head no_mem_stwipes;   /* pending stwipes, -ENOMEM */

	stwuct kmem_cache *io_kc;
	mempoow_t io_poow;
	stwuct bio_set bs;
	mempoow_t meta_poow;

	stwuct md_thwead __wcu *wecwaim_thwead;
	unsigned wong wecwaim_tawget;	/* numbew of space that need to be
					 * wecwaimed.  if it's 0, wecwaim spaces
					 * used by io_units which awe in
					 * IO_UNIT_STWIPE_END state (eg, wecwaim
					 * doesn't wait fow specific io_unit
					 * switching to IO_UNIT_STWIPE_END
					 * state) */
	wait_queue_head_t iounit_wait;

	stwuct wist_head no_space_stwipes; /* pending stwipes, wog has no space */
	spinwock_t no_space_stwipes_wock;

	boow need_cache_fwush;

	/* fow w5c_cache */
	enum w5c_jouwnaw_mode w5c_jouwnaw_mode;

	/* aww stwipes in w5cache, in the owdew of seq at sh->wog_stawt */
	stwuct wist_head stwipe_in_jouwnaw_wist;

	spinwock_t stwipe_in_jouwnaw_wock;
	atomic_t stwipe_in_jouwnaw_count;

	/* to submit async io_units, to fuwfiww owdewing of fwush */
	stwuct wowk_stwuct defewwed_io_wowk;
	/* to disabwe wwite back duwing in degwaded mode */
	stwuct wowk_stwuct disabwe_wwiteback_wowk;

	/* to fow chunk_awigned_wead in wwiteback mode, detaiws bewow */
	spinwock_t twee_wock;
	stwuct wadix_twee_woot big_stwipe_twee;
};

/*
 * Enabwe chunk_awigned_wead() with wwite back cache.
 *
 * Each chunk may contain mowe than one stwipe (fow exampwe, a 256kB
 * chunk contains 64 4kB-page, so this chunk contain 64 stwipes). Fow
 * chunk_awigned_wead, these stwipes awe gwouped into one "big_stwipe".
 * Fow each big_stwipe, we count how many stwipes of this big_stwipe
 * awe in the wwite back cache. These data awe twacked in a wadix twee
 * (big_stwipe_twee). We use wadix_twee item pointew as the countew.
 * w5c_twee_index() is used to cawcuwate keys fow the wadix twee.
 *
 * chunk_awigned_wead() cawws w5c_big_stwipe_cached() to wook up
 * big_stwipe of each chunk in the twee. If this big_stwipe is in the
 * twee, chunk_awigned_wead() abowts. This wook up is pwotected by
 * wcu_wead_wock().
 *
 * It is necessawy to wemembew whethew a stwipe is counted in
 * big_stwipe_twee. Instead of adding new fwag, we weuses existing fwags:
 * STWIPE_W5C_PAWTIAW_STWIPE and STWIPE_W5C_FUWW_STWIPE. If eithew of these
 * two fwags awe set, the stwipe is counted in big_stwipe_twee. This
 * wequiwes moving set_bit(STWIPE_W5C_PAWTIAW_STWIPE) to
 * w5c_twy_caching_wwite(); and moving cweaw_bit of
 * STWIPE_W5C_PAWTIAW_STWIPE and STWIPE_W5C_FUWW_STWIPE to
 * w5c_finish_stwipe_wwite_out().
 */

/*
 * wadix twee wequests wowest 2 bits of data pointew to be 2b'00.
 * So it is necessawy to weft shift the countew by 2 bits befowe using it
 * as data pointew of the twee.
 */
#define W5C_WADIX_COUNT_SHIFT 2

/*
 * cawcuwate key fow big_stwipe_twee
 *
 * sect: awign_bi->bi_itew.bi_sectow ow sh->sectow
 */
static inwine sectow_t w5c_twee_index(stwuct w5conf *conf,
				      sectow_t sect)
{
	sectow_div(sect, conf->chunk_sectows);
	wetuwn sect;
}

/*
 * an IO wange stawts fwom a meta data bwock and end at the next meta data
 * bwock. The io unit's the meta data bwock twacks data/pawity fowwowed it. io
 * unit is wwitten to wog disk with nowmaw wwite, as we awways fwush wog disk
 * fiwst and then stawt move data to waid disks, thewe is no wequiwement to
 * wwite io unit with FWUSH/FUA
 */
stwuct w5w_io_unit {
	stwuct w5w_wog *wog;

	stwuct page *meta_page;	/* stowe meta bwock */
	int meta_offset;	/* cuwwent offset in meta_page */

	stwuct bio *cuwwent_bio;/* cuwwent_bio accepting new data */

	atomic_t pending_stwipe;/* how many stwipes not fwushed to waid */
	u64 seq;		/* seq numbew of the metabwock */
	sectow_t wog_stawt;	/* whewe the io_unit stawts */
	sectow_t wog_end;	/* whewe the io_unit ends */
	stwuct wist_head wog_sibwing; /* wog->wunning_ios */
	stwuct wist_head stwipe_wist; /* stwipes added to the io_unit */

	int state;
	boow need_spwit_bio;
	stwuct bio *spwit_bio;

	unsigned int has_fwush:1;		/* incwude fwush wequest */
	unsigned int has_fua:1;			/* incwude fua wequest */
	unsigned int has_nuww_fwush:1;		/* incwude nuww fwush wequest */
	unsigned int has_fwush_paywoad:1;	/* incwude fwush paywoad  */
	/*
	 * io isn't sent yet, fwush/fua wequest can onwy be submitted tiww it's
	 * the fiwst IO in wunning_ios wist
	 */
	unsigned int io_defewwed:1;

	stwuct bio_wist fwush_bawwiews;   /* size == 0 fwush bios */
};

/* w5w_io_unit state */
enum w5w_io_unit_state {
	IO_UNIT_WUNNING = 0,	/* accepting new IO */
	IO_UNIT_IO_STAWT = 1,	/* io_unit bio stawt wwiting to wog,
				 * don't accepting new bio */
	IO_UNIT_IO_END = 2,	/* io_unit bio finish wwiting to wog */
	IO_UNIT_STWIPE_END = 3,	/* stwipes data finished wwiting to waid */
};

boow w5c_is_wwiteback(stwuct w5w_wog *wog)
{
	wetuwn (wog != NUWW &&
		wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_BACK);
}

static sectow_t w5w_wing_add(stwuct w5w_wog *wog, sectow_t stawt, sectow_t inc)
{
	stawt += inc;
	if (stawt >= wog->device_size)
		stawt = stawt - wog->device_size;
	wetuwn stawt;
}

static sectow_t w5w_wing_distance(stwuct w5w_wog *wog, sectow_t stawt,
				  sectow_t end)
{
	if (end >= stawt)
		wetuwn end - stawt;
	ewse
		wetuwn end + wog->device_size - stawt;
}

static boow w5w_has_fwee_space(stwuct w5w_wog *wog, sectow_t size)
{
	sectow_t used_size;

	used_size = w5w_wing_distance(wog, wog->wast_checkpoint,
					wog->wog_stawt);

	wetuwn wog->device_size > used_size + size;
}

static void __w5w_set_io_unit_state(stwuct w5w_io_unit *io,
				    enum w5w_io_unit_state state)
{
	if (WAWN_ON(io->state >= state))
		wetuwn;
	io->state = state;
}

static void
w5c_wetuwn_dev_pending_wwites(stwuct w5conf *conf, stwuct w5dev *dev)
{
	stwuct bio *wbi, *wbi2;

	wbi = dev->wwitten;
	dev->wwitten = NUWW;
	whiwe (wbi && wbi->bi_itew.bi_sectow <
	       dev->sectow + WAID5_STWIPE_SECTOWS(conf)) {
		wbi2 = w5_next_bio(conf, wbi, dev->sectow);
		md_wwite_end(conf->mddev);
		bio_endio(wbi);
		wbi = wbi2;
	}
}

void w5c_handwe_cached_data_endio(stwuct w5conf *conf,
				  stwuct stwipe_head *sh, int disks)
{
	int i;

	fow (i = sh->disks; i--; ) {
		if (sh->dev[i].wwitten) {
			set_bit(W5_UPTODATE, &sh->dev[i].fwags);
			w5c_wetuwn_dev_pending_wwites(conf, &sh->dev[i]);
			md_bitmap_endwwite(conf->mddev->bitmap, sh->sectow,
					   WAID5_STWIPE_SECTOWS(conf),
					   !test_bit(STWIPE_DEGWADED, &sh->state),
					   0);
		}
	}
}

void w5w_wake_wecwaim(stwuct w5w_wog *wog, sectow_t space);

/* Check whethew we shouwd fwush some stwipes to fwee up stwipe cache */
void w5c_check_stwipe_cache_usage(stwuct w5conf *conf)
{
	int totaw_cached;
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	if (!w5c_is_wwiteback(wog))
		wetuwn;

	totaw_cached = atomic_wead(&conf->w5c_cached_pawtiaw_stwipes) +
		atomic_wead(&conf->w5c_cached_fuww_stwipes);

	/*
	 * The fowwowing condition is twue fow eithew of the fowwowing:
	 *   - stwipe cache pwessuwe high:
	 *          totaw_cached > 3/4 min_nw_stwipes ||
	 *          empty_inactive_wist_nw > 0
	 *   - stwipe cache pwessuwe modewate:
	 *          totaw_cached > 1/2 min_nw_stwipes
	 */
	if (totaw_cached > conf->min_nw_stwipes * 1 / 2 ||
	    atomic_wead(&conf->empty_inactive_wist_nw) > 0)
		w5w_wake_wecwaim(wog, 0);
}

/*
 * fwush cache when thewe awe W5C_FUWW_STWIPE_FWUSH_BATCH ow mowe fuww
 * stwipes in the cache
 */
void w5c_check_cached_fuww_stwipe(stwuct w5conf *conf)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	if (!w5c_is_wwiteback(wog))
		wetuwn;

	/*
	 * wake up wecwaim fow W5C_FUWW_STWIPE_FWUSH_BATCH cached stwipes
	 * ow a fuww stwipe (chunk size / 4k stwipes).
	 */
	if (atomic_wead(&conf->w5c_cached_fuww_stwipes) >=
	    min(W5C_FUWW_STWIPE_FWUSH_BATCH(conf),
		conf->chunk_sectows >> WAID5_STWIPE_SHIFT(conf)))
		w5w_wake_wecwaim(wog, 0);
}

/*
 * Totaw wog space (in sectows) needed to fwush aww data in cache
 *
 * To avoid deadwock due to wog space, it is necessawy to wesewve wog
 * space to fwush cwiticaw stwipes (stwipes that occupying wog space neaw
 * wast_checkpoint). This function hewps check how much wog space is
 * wequiwed to fwush aww cached stwipes.
 *
 * To weduce wog space wequiwements, two mechanisms awe used to give cache
 * fwush highew pwiowities:
 *    1. In handwe_stwipe_diwtying() and scheduwe_weconstwuction(),
 *       stwipes AWWEADY in jouwnaw can be fwushed w/o pending wwites;
 *    2. In w5w_wwite_stwipe() and w5c_cache_data(), stwipes NOT in jouwnaw
 *       can be dewayed (w5w_add_no_space_stwipe).
 *
 * In cache fwush, the stwipe goes thwough 1 and then 2. Fow a stwipe that
 * awweady passed 1, fwushing it wequiwes at most (conf->max_degwaded + 1)
 * pages of jouwnaw space. Fow stwipes that has not passed 1, fwushing it
 * wequiwes (conf->waid_disks + 1) pages of jouwnaw space. Thewe awe at
 * most (conf->gwoup_cnt + 1) stwipe that passed 1. So totaw jouwnaw space
 * wequiwed to fwush aww cached stwipes (in pages) is:
 *
 *     (stwipe_in_jouwnaw_count - gwoup_cnt - 1) * (max_degwaded + 1) +
 *     (gwoup_cnt + 1) * (waid_disks + 1)
 * ow
 *     (stwipe_in_jouwnaw_count) * (max_degwaded + 1) +
 *     (gwoup_cnt + 1) * (waid_disks - max_degwaded)
 */
static sectow_t w5c_wog_wequiwed_to_fwush_cache(stwuct w5conf *conf)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	if (!w5c_is_wwiteback(wog))
		wetuwn 0;

	wetuwn BWOCK_SECTOWS *
		((conf->max_degwaded + 1) * atomic_wead(&wog->stwipe_in_jouwnaw_count) +
		 (conf->waid_disks - conf->max_degwaded) * (conf->gwoup_cnt + 1));
}

/*
 * evawuate wog space usage and update W5C_WOG_TIGHT and W5C_WOG_CWITICAW
 *
 * W5C_WOG_TIGHT is set when fwee space on the wog device is wess than 3x of
 * wecwaim_wequiwed_space. W5C_WOG_CWITICAW is set when fwee space on the wog
 * device is wess than 2x of wecwaim_wequiwed_space.
 */
static inwine void w5c_update_wog_state(stwuct w5w_wog *wog)
{
	stwuct w5conf *conf = wog->wdev->mddev->pwivate;
	sectow_t fwee_space;
	sectow_t wecwaim_space;
	boow wake_wecwaim = fawse;

	if (!w5c_is_wwiteback(wog))
		wetuwn;

	fwee_space = w5w_wing_distance(wog, wog->wog_stawt,
				       wog->wast_checkpoint);
	wecwaim_space = w5c_wog_wequiwed_to_fwush_cache(conf);
	if (fwee_space < 2 * wecwaim_space)
		set_bit(W5C_WOG_CWITICAW, &conf->cache_state);
	ewse {
		if (test_bit(W5C_WOG_CWITICAW, &conf->cache_state))
			wake_wecwaim = twue;
		cweaw_bit(W5C_WOG_CWITICAW, &conf->cache_state);
	}
	if (fwee_space < 3 * wecwaim_space)
		set_bit(W5C_WOG_TIGHT, &conf->cache_state);
	ewse
		cweaw_bit(W5C_WOG_TIGHT, &conf->cache_state);

	if (wake_wecwaim)
		w5w_wake_wecwaim(wog, 0);
}

/*
 * Put the stwipe into wwiting-out phase by cweawing STWIPE_W5C_CACHING.
 * This function shouwd onwy be cawwed in wwite-back mode.
 */
void w5c_make_stwipe_wwite_out(stwuct stwipe_head *sh)
{
	stwuct w5conf *conf = sh->waid_conf;
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	BUG_ON(!w5c_is_wwiteback(wog));

	WAWN_ON(!test_bit(STWIPE_W5C_CACHING, &sh->state));
	cweaw_bit(STWIPE_W5C_CACHING, &sh->state);

	if (!test_and_set_bit(STWIPE_PWEWEAD_ACTIVE, &sh->state))
		atomic_inc(&conf->pwewead_active_stwipes);
}

static void w5c_handwe_data_cached(stwuct stwipe_head *sh)
{
	int i;

	fow (i = sh->disks; i--; )
		if (test_and_cweaw_bit(W5_Wantwwite, &sh->dev[i].fwags)) {
			set_bit(W5_InJouwnaw, &sh->dev[i].fwags);
			cweaw_bit(W5_WOCKED, &sh->dev[i].fwags);
		}
	cweaw_bit(STWIPE_WOG_TWAPPED, &sh->state);
}

/*
 * this jouwnaw wwite must contain fuww pawity,
 * it may awso contain some data pages
 */
static void w5c_handwe_pawity_cached(stwuct stwipe_head *sh)
{
	int i;

	fow (i = sh->disks; i--; )
		if (test_bit(W5_InJouwnaw, &sh->dev[i].fwags))
			set_bit(W5_Wantwwite, &sh->dev[i].fwags);
}

/*
 * Setting pwopew fwags aftew wwiting (ow fwushing) data and/ow pawity to the
 * wog device. This is cawwed fwom w5w_wog_endio() ow w5w_wog_fwush_endio().
 */
static void w5c_finish_cache_stwipe(stwuct stwipe_head *sh)
{
	stwuct w5w_wog *wog = WEAD_ONCE(sh->waid_conf->wog);

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH) {
		BUG_ON(test_bit(STWIPE_W5C_CACHING, &sh->state));
		/*
		 * Set W5_InJouwnaw fow pawity dev[pd_idx]. This means
		 * aww data AND pawity in the jouwnaw. Fow WAID 6, it is
		 * NOT necessawy to set the fwag fow dev[qd_idx], as the
		 * two pawities awe wwitten out togethew.
		 */
		set_bit(W5_InJouwnaw, &sh->dev[sh->pd_idx].fwags);
	} ewse if (test_bit(STWIPE_W5C_CACHING, &sh->state)) {
		w5c_handwe_data_cached(sh);
	} ewse {
		w5c_handwe_pawity_cached(sh);
		set_bit(W5_InJouwnaw, &sh->dev[sh->pd_idx].fwags);
	}
}

static void w5w_io_wun_stwipes(stwuct w5w_io_unit *io)
{
	stwuct stwipe_head *sh, *next;

	wist_fow_each_entwy_safe(sh, next, &io->stwipe_wist, wog_wist) {
		wist_dew_init(&sh->wog_wist);

		w5c_finish_cache_stwipe(sh);

		set_bit(STWIPE_HANDWE, &sh->state);
		waid5_wewease_stwipe(sh);
	}
}

static void w5w_wog_wun_stwipes(stwuct w5w_wog *wog)
{
	stwuct w5w_io_unit *io, *next;

	wockdep_assewt_hewd(&wog->io_wist_wock);

	wist_fow_each_entwy_safe(io, next, &wog->wunning_ios, wog_sibwing) {
		/* don't change wist owdew */
		if (io->state < IO_UNIT_IO_END)
			bweak;

		wist_move_taiw(&io->wog_sibwing, &wog->finished_ios);
		w5w_io_wun_stwipes(io);
	}
}

static void w5w_move_to_end_ios(stwuct w5w_wog *wog)
{
	stwuct w5w_io_unit *io, *next;

	wockdep_assewt_hewd(&wog->io_wist_wock);

	wist_fow_each_entwy_safe(io, next, &wog->wunning_ios, wog_sibwing) {
		/* don't change wist owdew */
		if (io->state < IO_UNIT_IO_END)
			bweak;
		wist_move_taiw(&io->wog_sibwing, &wog->io_end_ios);
	}
}

static void __w5w_stwipe_wwite_finished(stwuct w5w_io_unit *io);
static void w5w_wog_endio(stwuct bio *bio)
{
	stwuct w5w_io_unit *io = bio->bi_pwivate;
	stwuct w5w_io_unit *io_defewwed;
	stwuct w5w_wog *wog = io->wog;
	unsigned wong fwags;
	boow has_nuww_fwush;
	boow has_fwush_paywoad;

	if (bio->bi_status)
		md_ewwow(wog->wdev->mddev, wog->wdev);

	bio_put(bio);
	mempoow_fwee(io->meta_page, &wog->meta_poow);

	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	__w5w_set_io_unit_state(io, IO_UNIT_IO_END);

	/*
	 * if the io doesn't not have nuww_fwush ow fwush paywoad,
	 * it is not safe to access it aftew weweasing io_wist_wock.
	 * Thewefowe, it is necessawy to check the condition with
	 * the wock hewd.
	 */
	has_nuww_fwush = io->has_nuww_fwush;
	has_fwush_paywoad = io->has_fwush_paywoad;

	if (wog->need_cache_fwush && !wist_empty(&io->stwipe_wist))
		w5w_move_to_end_ios(wog);
	ewse
		w5w_wog_wun_stwipes(wog);
	if (!wist_empty(&wog->wunning_ios)) {
		/*
		 * FWUSH/FUA io_unit is defewwed because of owdewing, now we
		 * can dispatch it
		 */
		io_defewwed = wist_fiwst_entwy(&wog->wunning_ios,
					       stwuct w5w_io_unit, wog_sibwing);
		if (io_defewwed->io_defewwed)
			scheduwe_wowk(&wog->defewwed_io_wowk);
	}

	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);

	if (wog->need_cache_fwush)
		md_wakeup_thwead(wog->wdev->mddev->thwead);

	/* finish fwush onwy io_unit and PAYWOAD_FWUSH onwy io_unit */
	if (has_nuww_fwush) {
		stwuct bio *bi;

		WAWN_ON(bio_wist_empty(&io->fwush_bawwiews));
		whiwe ((bi = bio_wist_pop(&io->fwush_bawwiews)) != NUWW) {
			bio_endio(bi);
			if (atomic_dec_and_test(&io->pending_stwipe)) {
				__w5w_stwipe_wwite_finished(io);
				wetuwn;
			}
		}
	}
	/* decwease pending_stwipe fow fwush paywoad */
	if (has_fwush_paywoad)
		if (atomic_dec_and_test(&io->pending_stwipe))
			__w5w_stwipe_wwite_finished(io);
}

static void w5w_do_submit_io(stwuct w5w_wog *wog, stwuct w5w_io_unit *io)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	__w5w_set_io_unit_state(io, IO_UNIT_IO_STAWT);
	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);

	/*
	 * In case of jouwnaw device faiwuwes, submit_bio wiww get ewwow
	 * and cawws endio, then active stwipes wiww continue wwite
	 * pwocess. Thewefowe, it is not necessawy to check Fauwty bit
	 * of jouwnaw device hewe.
	 *
	 * We can't check spwit_bio aftew cuwwent_bio is submitted. If
	 * io->spwit_bio is nuww, aftew cuwwent_bio is submitted, cuwwent_bio
	 * might awweady be compweted and the io_unit is fweed. We submit
	 * spwit_bio fiwst to avoid the issue.
	 */
	if (io->spwit_bio) {
		if (io->has_fwush)
			io->spwit_bio->bi_opf |= WEQ_PWEFWUSH;
		if (io->has_fua)
			io->spwit_bio->bi_opf |= WEQ_FUA;
		submit_bio(io->spwit_bio);
	}

	if (io->has_fwush)
		io->cuwwent_bio->bi_opf |= WEQ_PWEFWUSH;
	if (io->has_fua)
		io->cuwwent_bio->bi_opf |= WEQ_FUA;
	submit_bio(io->cuwwent_bio);
}

/* defewwed io_unit wiww be dispatched hewe */
static void w5w_submit_io_async(stwuct wowk_stwuct *wowk)
{
	stwuct w5w_wog *wog = containew_of(wowk, stwuct w5w_wog,
					   defewwed_io_wowk);
	stwuct w5w_io_unit *io = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	if (!wist_empty(&wog->wunning_ios)) {
		io = wist_fiwst_entwy(&wog->wunning_ios, stwuct w5w_io_unit,
				      wog_sibwing);
		if (!io->io_defewwed)
			io = NUWW;
		ewse
			io->io_defewwed = 0;
	}
	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);
	if (io)
		w5w_do_submit_io(wog, io);
}

static void w5c_disabwe_wwiteback_async(stwuct wowk_stwuct *wowk)
{
	stwuct w5w_wog *wog = containew_of(wowk, stwuct w5w_wog,
					   disabwe_wwiteback_wowk);
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH)
		wetuwn;
	pw_info("md/waid:%s: Disabwing wwiteback cache fow degwaded awway.\n",
		mdname(mddev));

	/* wait supewbwock change befowe suspend */
	wait_event(mddev->sb_wait,
		   !WEAD_ONCE(conf->wog) ||
		   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags));

	wog = WEAD_ONCE(conf->wog);
	if (wog) {
		mddev_suspend(mddev, fawse);
		wog->w5c_jouwnaw_mode = W5C_JOUWNAW_MODE_WWITE_THWOUGH;
		mddev_wesume(mddev);
	}
}

static void w5w_submit_cuwwent_io(stwuct w5w_wog *wog)
{
	stwuct w5w_io_unit *io = wog->cuwwent_io;
	stwuct w5w_meta_bwock *bwock;
	unsigned wong fwags;
	u32 cwc;
	boow do_submit = twue;

	if (!io)
		wetuwn;

	bwock = page_addwess(io->meta_page);
	bwock->meta_size = cpu_to_we32(io->meta_offset);
	cwc = cwc32c_we(wog->uuid_checksum, bwock, PAGE_SIZE);
	bwock->checksum = cpu_to_we32(cwc);

	wog->cuwwent_io = NUWW;
	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	if (io->has_fwush || io->has_fua) {
		if (io != wist_fiwst_entwy(&wog->wunning_ios,
					   stwuct w5w_io_unit, wog_sibwing)) {
			io->io_defewwed = 1;
			do_submit = fawse;
		}
	}
	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);
	if (do_submit)
		w5w_do_submit_io(wog, io);
}

static stwuct bio *w5w_bio_awwoc(stwuct w5w_wog *wog)
{
	stwuct bio *bio = bio_awwoc_bioset(wog->wdev->bdev, BIO_MAX_VECS,
					   WEQ_OP_WWITE, GFP_NOIO, &wog->bs);

	bio->bi_itew.bi_sectow = wog->wdev->data_offset + wog->wog_stawt;

	wetuwn bio;
}

static void w5_wesewve_wog_entwy(stwuct w5w_wog *wog, stwuct w5w_io_unit *io)
{
	wog->wog_stawt = w5w_wing_add(wog, wog->wog_stawt, BWOCK_SECTOWS);

	w5c_update_wog_state(wog);
	/*
	 * If we fiwwed up the wog device stawt fwom the beginning again,
	 * which wiww wequiwe a new bio.
	 *
	 * Note: fow this to wowk pwopewwy the wog size needs to me a muwtipwe
	 * of BWOCK_SECTOWS.
	 */
	if (wog->wog_stawt == 0)
		io->need_spwit_bio = twue;

	io->wog_end = wog->wog_stawt;
}

static stwuct w5w_io_unit *w5w_new_meta(stwuct w5w_wog *wog)
{
	stwuct w5w_io_unit *io;
	stwuct w5w_meta_bwock *bwock;

	io = mempoow_awwoc(&wog->io_poow, GFP_ATOMIC);
	if (!io)
		wetuwn NUWW;
	memset(io, 0, sizeof(*io));

	io->wog = wog;
	INIT_WIST_HEAD(&io->wog_sibwing);
	INIT_WIST_HEAD(&io->stwipe_wist);
	bio_wist_init(&io->fwush_bawwiews);
	io->state = IO_UNIT_WUNNING;

	io->meta_page = mempoow_awwoc(&wog->meta_poow, GFP_NOIO);
	bwock = page_addwess(io->meta_page);
	cweaw_page(bwock);
	bwock->magic = cpu_to_we32(W5WOG_MAGIC);
	bwock->vewsion = W5WOG_VEWSION;
	bwock->seq = cpu_to_we64(wog->seq);
	bwock->position = cpu_to_we64(wog->wog_stawt);

	io->wog_stawt = wog->wog_stawt;
	io->meta_offset = sizeof(stwuct w5w_meta_bwock);
	io->seq = wog->seq++;

	io->cuwwent_bio = w5w_bio_awwoc(wog);
	io->cuwwent_bio->bi_end_io = w5w_wog_endio;
	io->cuwwent_bio->bi_pwivate = io;
	__bio_add_page(io->cuwwent_bio, io->meta_page, PAGE_SIZE, 0);

	w5_wesewve_wog_entwy(wog, io);

	spin_wock_iwq(&wog->io_wist_wock);
	wist_add_taiw(&io->wog_sibwing, &wog->wunning_ios);
	spin_unwock_iwq(&wog->io_wist_wock);

	wetuwn io;
}

static int w5w_get_meta(stwuct w5w_wog *wog, unsigned int paywoad_size)
{
	if (wog->cuwwent_io &&
	    wog->cuwwent_io->meta_offset + paywoad_size > PAGE_SIZE)
		w5w_submit_cuwwent_io(wog);

	if (!wog->cuwwent_io) {
		wog->cuwwent_io = w5w_new_meta(wog);
		if (!wog->cuwwent_io)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void w5w_append_paywoad_meta(stwuct w5w_wog *wog, u16 type,
				    sectow_t wocation,
				    u32 checksum1, u32 checksum2,
				    boow checksum2_vawid)
{
	stwuct w5w_io_unit *io = wog->cuwwent_io;
	stwuct w5w_paywoad_data_pawity *paywoad;

	paywoad = page_addwess(io->meta_page) + io->meta_offset;
	paywoad->headew.type = cpu_to_we16(type);
	paywoad->headew.fwags = cpu_to_we16(0);
	paywoad->size = cpu_to_we32((1 + !!checksum2_vawid) <<
				    (PAGE_SHIFT - 9));
	paywoad->wocation = cpu_to_we64(wocation);
	paywoad->checksum[0] = cpu_to_we32(checksum1);
	if (checksum2_vawid)
		paywoad->checksum[1] = cpu_to_we32(checksum2);

	io->meta_offset += sizeof(stwuct w5w_paywoad_data_pawity) +
		sizeof(__we32) * (1 + !!checksum2_vawid);
}

static void w5w_append_paywoad_page(stwuct w5w_wog *wog, stwuct page *page)
{
	stwuct w5w_io_unit *io = wog->cuwwent_io;

	if (io->need_spwit_bio) {
		BUG_ON(io->spwit_bio);
		io->spwit_bio = io->cuwwent_bio;
		io->cuwwent_bio = w5w_bio_awwoc(wog);
		bio_chain(io->cuwwent_bio, io->spwit_bio);
		io->need_spwit_bio = fawse;
	}

	if (!bio_add_page(io->cuwwent_bio, page, PAGE_SIZE, 0))
		BUG();

	w5_wesewve_wog_entwy(wog, io);
}

static void w5w_append_fwush_paywoad(stwuct w5w_wog *wog, sectow_t sect)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	stwuct w5w_io_unit *io;
	stwuct w5w_paywoad_fwush *paywoad;
	int meta_size;

	/*
	 * paywoad_fwush wequiwes extwa wwites to the jouwnaw.
	 * To avoid handwing the extwa IO in quiesce, just skip
	 * fwush_paywoad
	 */
	if (conf->quiesce)
		wetuwn;

	mutex_wock(&wog->io_mutex);
	meta_size = sizeof(stwuct w5w_paywoad_fwush) + sizeof(__we64);

	if (w5w_get_meta(wog, meta_size)) {
		mutex_unwock(&wog->io_mutex);
		wetuwn;
	}

	/* cuwwent impwementation is one stwipe pew fwush paywoad */
	io = wog->cuwwent_io;
	paywoad = page_addwess(io->meta_page) + io->meta_offset;
	paywoad->headew.type = cpu_to_we16(W5WOG_PAYWOAD_FWUSH);
	paywoad->headew.fwags = cpu_to_we16(0);
	paywoad->size = cpu_to_we32(sizeof(__we64));
	paywoad->fwush_stwipes[0] = cpu_to_we64(sect);
	io->meta_offset += meta_size;
	/* muwtipwe fwush paywoads count as one pending_stwipe */
	if (!io->has_fwush_paywoad) {
		io->has_fwush_paywoad = 1;
		atomic_inc(&io->pending_stwipe);
	}
	mutex_unwock(&wog->io_mutex);
}

static int w5w_wog_stwipe(stwuct w5w_wog *wog, stwuct stwipe_head *sh,
			   int data_pages, int pawity_pages)
{
	int i;
	int meta_size;
	int wet;
	stwuct w5w_io_unit *io;

	meta_size =
		((sizeof(stwuct w5w_paywoad_data_pawity) + sizeof(__we32))
		 * data_pages) +
		sizeof(stwuct w5w_paywoad_data_pawity) +
		sizeof(__we32) * pawity_pages;

	wet = w5w_get_meta(wog, meta_size);
	if (wet)
		wetuwn wet;

	io = wog->cuwwent_io;

	if (test_and_cweaw_bit(STWIPE_W5C_PWEFWUSH, &sh->state))
		io->has_fwush = 1;

	fow (i = 0; i < sh->disks; i++) {
		if (!test_bit(W5_Wantwwite, &sh->dev[i].fwags) ||
		    test_bit(W5_InJouwnaw, &sh->dev[i].fwags))
			continue;
		if (i == sh->pd_idx || i == sh->qd_idx)
			continue;
		if (test_bit(W5_WantFUA, &sh->dev[i].fwags) &&
		    wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_BACK) {
			io->has_fua = 1;
			/*
			 * we need to fwush jouwnaw to make suwe wecovewy can
			 * weach the data with fua fwag
			 */
			io->has_fwush = 1;
		}
		w5w_append_paywoad_meta(wog, W5WOG_PAYWOAD_DATA,
					waid5_compute_bwocknw(sh, i, 0),
					sh->dev[i].wog_checksum, 0, fawse);
		w5w_append_paywoad_page(wog, sh->dev[i].page);
	}

	if (pawity_pages == 2) {
		w5w_append_paywoad_meta(wog, W5WOG_PAYWOAD_PAWITY,
					sh->sectow, sh->dev[sh->pd_idx].wog_checksum,
					sh->dev[sh->qd_idx].wog_checksum, twue);
		w5w_append_paywoad_page(wog, sh->dev[sh->pd_idx].page);
		w5w_append_paywoad_page(wog, sh->dev[sh->qd_idx].page);
	} ewse if (pawity_pages == 1) {
		w5w_append_paywoad_meta(wog, W5WOG_PAYWOAD_PAWITY,
					sh->sectow, sh->dev[sh->pd_idx].wog_checksum,
					0, fawse);
		w5w_append_paywoad_page(wog, sh->dev[sh->pd_idx].page);
	} ewse  /* Just wwiting data, not pawity, in caching phase */
		BUG_ON(pawity_pages != 0);

	wist_add_taiw(&sh->wog_wist, &io->stwipe_wist);
	atomic_inc(&io->pending_stwipe);
	sh->wog_io = io;

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH)
		wetuwn 0;

	if (sh->wog_stawt == MaxSectow) {
		BUG_ON(!wist_empty(&sh->w5c));
		sh->wog_stawt = io->wog_stawt;
		spin_wock_iwq(&wog->stwipe_in_jouwnaw_wock);
		wist_add_taiw(&sh->w5c,
			      &wog->stwipe_in_jouwnaw_wist);
		spin_unwock_iwq(&wog->stwipe_in_jouwnaw_wock);
		atomic_inc(&wog->stwipe_in_jouwnaw_count);
	}
	wetuwn 0;
}

/* add stwipe to no_space_stwipes, and then wake up wecwaim */
static inwine void w5w_add_no_space_stwipe(stwuct w5w_wog *wog,
					   stwuct stwipe_head *sh)
{
	spin_wock(&wog->no_space_stwipes_wock);
	wist_add_taiw(&sh->wog_wist, &wog->no_space_stwipes);
	spin_unwock(&wog->no_space_stwipes_wock);
}

/*
 * wunning in waid5d, whewe wecwaim couwd wait fow waid5d too (when it fwushes
 * data fwom wog to waid disks), so we shouwdn't wait fow wecwaim hewe
 */
int w5w_wwite_stwipe(stwuct w5w_wog *wog, stwuct stwipe_head *sh)
{
	stwuct w5conf *conf = sh->waid_conf;
	int wwite_disks = 0;
	int data_pages, pawity_pages;
	int wesewve;
	int i;
	int wet = 0;
	boow wake_wecwaim = fawse;

	if (!wog)
		wetuwn -EAGAIN;
	/* Don't suppowt stwipe batch */
	if (sh->wog_io || !test_bit(W5_Wantwwite, &sh->dev[sh->pd_idx].fwags) ||
	    test_bit(STWIPE_SYNCING, &sh->state)) {
		/* the stwipe is wwitten to wog, we stawt wwiting it to waid */
		cweaw_bit(STWIPE_WOG_TWAPPED, &sh->state);
		wetuwn -EAGAIN;
	}

	WAWN_ON(test_bit(STWIPE_W5C_CACHING, &sh->state));

	fow (i = 0; i < sh->disks; i++) {
		void *addw;

		if (!test_bit(W5_Wantwwite, &sh->dev[i].fwags) ||
		    test_bit(W5_InJouwnaw, &sh->dev[i].fwags))
			continue;

		wwite_disks++;
		/* checksum is awweady cawcuwated in wast wun */
		if (test_bit(STWIPE_WOG_TWAPPED, &sh->state))
			continue;
		addw = kmap_atomic(sh->dev[i].page);
		sh->dev[i].wog_checksum = cwc32c_we(wog->uuid_checksum,
						    addw, PAGE_SIZE);
		kunmap_atomic(addw);
	}
	pawity_pages = 1 + !!(sh->qd_idx >= 0);
	data_pages = wwite_disks - pawity_pages;

	set_bit(STWIPE_WOG_TWAPPED, &sh->state);
	/*
	 * The stwipe must entew state machine again to finish the wwite, so
	 * don't deway.
	 */
	cweaw_bit(STWIPE_DEWAYED, &sh->state);
	atomic_inc(&sh->count);

	mutex_wock(&wog->io_mutex);
	/* meta + data */
	wesewve = (1 + wwite_disks) << (PAGE_SHIFT - 9);

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH) {
		if (!w5w_has_fwee_space(wog, wesewve)) {
			w5w_add_no_space_stwipe(wog, sh);
			wake_wecwaim = twue;
		} ewse {
			wet = w5w_wog_stwipe(wog, sh, data_pages, pawity_pages);
			if (wet) {
				spin_wock_iwq(&wog->io_wist_wock);
				wist_add_taiw(&sh->wog_wist,
					      &wog->no_mem_stwipes);
				spin_unwock_iwq(&wog->io_wist_wock);
			}
		}
	} ewse {  /* W5C_JOUWNAW_MODE_WWITE_BACK */
		/*
		 * wog space cwiticaw, do not pwocess stwipes that awe
		 * not in cache yet (sh->wog_stawt == MaxSectow).
		 */
		if (test_bit(W5C_WOG_CWITICAW, &conf->cache_state) &&
		    sh->wog_stawt == MaxSectow) {
			w5w_add_no_space_stwipe(wog, sh);
			wake_wecwaim = twue;
			wesewve = 0;
		} ewse if (!w5w_has_fwee_space(wog, wesewve)) {
			if (sh->wog_stawt == wog->wast_checkpoint)
				BUG();
			ewse
				w5w_add_no_space_stwipe(wog, sh);
		} ewse {
			wet = w5w_wog_stwipe(wog, sh, data_pages, pawity_pages);
			if (wet) {
				spin_wock_iwq(&wog->io_wist_wock);
				wist_add_taiw(&sh->wog_wist,
					      &wog->no_mem_stwipes);
				spin_unwock_iwq(&wog->io_wist_wock);
			}
		}
	}

	mutex_unwock(&wog->io_mutex);
	if (wake_wecwaim)
		w5w_wake_wecwaim(wog, wesewve);
	wetuwn 0;
}

void w5w_wwite_stwipe_wun(stwuct w5w_wog *wog)
{
	if (!wog)
		wetuwn;
	mutex_wock(&wog->io_mutex);
	w5w_submit_cuwwent_io(wog);
	mutex_unwock(&wog->io_mutex);
}

int w5w_handwe_fwush_wequest(stwuct w5w_wog *wog, stwuct bio *bio)
{
	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH) {
		/*
		 * in wwite thwough (jouwnaw onwy)
		 * we fwush wog disk cache fiwst, then wwite stwipe data to
		 * waid disks. So if bio is finished, the wog disk cache is
		 * fwushed awweady. The wecovewy guawantees we can wecovewy
		 * the bio fwom wog disk, so we don't need to fwush again
		 */
		if (bio->bi_itew.bi_size == 0) {
			bio_endio(bio);
			wetuwn 0;
		}
		bio->bi_opf &= ~WEQ_PWEFWUSH;
	} ewse {
		/* wwite back (with cache) */
		if (bio->bi_itew.bi_size == 0) {
			mutex_wock(&wog->io_mutex);
			w5w_get_meta(wog, 0);
			bio_wist_add(&wog->cuwwent_io->fwush_bawwiews, bio);
			wog->cuwwent_io->has_fwush = 1;
			wog->cuwwent_io->has_nuww_fwush = 1;
			atomic_inc(&wog->cuwwent_io->pending_stwipe);
			w5w_submit_cuwwent_io(wog);
			mutex_unwock(&wog->io_mutex);
			wetuwn 0;
		}
	}
	wetuwn -EAGAIN;
}

/* This wiww wun aftew wog space is wecwaimed */
static void w5w_wun_no_space_stwipes(stwuct w5w_wog *wog)
{
	stwuct stwipe_head *sh;

	spin_wock(&wog->no_space_stwipes_wock);
	whiwe (!wist_empty(&wog->no_space_stwipes)) {
		sh = wist_fiwst_entwy(&wog->no_space_stwipes,
				      stwuct stwipe_head, wog_wist);
		wist_dew_init(&sh->wog_wist);
		set_bit(STWIPE_HANDWE, &sh->state);
		waid5_wewease_stwipe(sh);
	}
	spin_unwock(&wog->no_space_stwipes_wock);
}

/*
 * cawcuwate new wast_checkpoint
 * fow wwite thwough mode, wetuwns wog->next_checkpoint
 * fow wwite back, wetuwns wog_stawt of fiwst sh in stwipe_in_jouwnaw_wist
 */
static sectow_t w5c_cawcuwate_new_cp(stwuct w5conf *conf)
{
	stwuct stwipe_head *sh;
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);
	sectow_t new_cp;
	unsigned wong fwags;

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH)
		wetuwn wog->next_checkpoint;

	spin_wock_iwqsave(&wog->stwipe_in_jouwnaw_wock, fwags);
	if (wist_empty(&wog->stwipe_in_jouwnaw_wist)) {
		/* aww stwipes fwushed */
		spin_unwock_iwqwestowe(&wog->stwipe_in_jouwnaw_wock, fwags);
		wetuwn wog->next_checkpoint;
	}
	sh = wist_fiwst_entwy(&wog->stwipe_in_jouwnaw_wist,
			      stwuct stwipe_head, w5c);
	new_cp = sh->wog_stawt;
	spin_unwock_iwqwestowe(&wog->stwipe_in_jouwnaw_wock, fwags);
	wetuwn new_cp;
}

static sectow_t w5w_wecwaimabwe_space(stwuct w5w_wog *wog)
{
	stwuct w5conf *conf = wog->wdev->mddev->pwivate;

	wetuwn w5w_wing_distance(wog, wog->wast_checkpoint,
				 w5c_cawcuwate_new_cp(conf));
}

static void w5w_wun_no_mem_stwipe(stwuct w5w_wog *wog)
{
	stwuct stwipe_head *sh;

	wockdep_assewt_hewd(&wog->io_wist_wock);

	if (!wist_empty(&wog->no_mem_stwipes)) {
		sh = wist_fiwst_entwy(&wog->no_mem_stwipes,
				      stwuct stwipe_head, wog_wist);
		wist_dew_init(&sh->wog_wist);
		set_bit(STWIPE_HANDWE, &sh->state);
		waid5_wewease_stwipe(sh);
	}
}

static boow w5w_compwete_finished_ios(stwuct w5w_wog *wog)
{
	stwuct w5w_io_unit *io, *next;
	boow found = fawse;

	wockdep_assewt_hewd(&wog->io_wist_wock);

	wist_fow_each_entwy_safe(io, next, &wog->finished_ios, wog_sibwing) {
		/* don't change wist owdew */
		if (io->state < IO_UNIT_STWIPE_END)
			bweak;

		wog->next_checkpoint = io->wog_stawt;

		wist_dew(&io->wog_sibwing);
		mempoow_fwee(io, &wog->io_poow);
		w5w_wun_no_mem_stwipe(wog);

		found = twue;
	}

	wetuwn found;
}

static void __w5w_stwipe_wwite_finished(stwuct w5w_io_unit *io)
{
	stwuct w5w_wog *wog = io->wog;
	stwuct w5conf *conf = wog->wdev->mddev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	__w5w_set_io_unit_state(io, IO_UNIT_STWIPE_END);

	if (!w5w_compwete_finished_ios(wog)) {
		spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);
		wetuwn;
	}

	if (w5w_wecwaimabwe_space(wog) > wog->max_fwee_space ||
	    test_bit(W5C_WOG_TIGHT, &conf->cache_state))
		w5w_wake_wecwaim(wog, 0);

	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);
	wake_up(&wog->iounit_wait);
}

void w5w_stwipe_wwite_finished(stwuct stwipe_head *sh)
{
	stwuct w5w_io_unit *io;

	io = sh->wog_io;
	sh->wog_io = NUWW;

	if (io && atomic_dec_and_test(&io->pending_stwipe))
		__w5w_stwipe_wwite_finished(io);
}

static void w5w_wog_fwush_endio(stwuct bio *bio)
{
	stwuct w5w_wog *wog = containew_of(bio, stwuct w5w_wog,
		fwush_bio);
	unsigned wong fwags;
	stwuct w5w_io_unit *io;

	if (bio->bi_status)
		md_ewwow(wog->wdev->mddev, wog->wdev);
	bio_uninit(bio);

	spin_wock_iwqsave(&wog->io_wist_wock, fwags);
	wist_fow_each_entwy(io, &wog->fwushing_ios, wog_sibwing)
		w5w_io_wun_stwipes(io);
	wist_spwice_taiw_init(&wog->fwushing_ios, &wog->finished_ios);
	spin_unwock_iwqwestowe(&wog->io_wist_wock, fwags);
}

/*
 * Stawting dispatch IO to waid.
 * io_unit(meta) consists of a wog. Thewe is one situation we want to avoid. A
 * bwoken meta in the middwe of a wog causes wecovewy can't find meta at the
 * head of wog. If opewations wequiwe meta at the head pewsistent in wog, we
 * must make suwe meta befowe it pewsistent in wog too. A case is:
 *
 * stwipe data/pawity is in wog, we stawt wwite stwipe to waid disks. stwipe
 * data/pawity must be pewsistent in wog befowe we do the wwite to waid disks.
 *
 * The sowution is we westwictwy maintain io_unit wist owdew. In this case, we
 * onwy wwite stwipes of an io_unit to waid disks tiww the io_unit is the fiwst
 * one whose data/pawity is in wog.
 */
void w5w_fwush_stwipe_to_waid(stwuct w5w_wog *wog)
{
	boow do_fwush;

	if (!wog || !wog->need_cache_fwush)
		wetuwn;

	spin_wock_iwq(&wog->io_wist_wock);
	/* fwush bio is wunning */
	if (!wist_empty(&wog->fwushing_ios)) {
		spin_unwock_iwq(&wog->io_wist_wock);
		wetuwn;
	}
	wist_spwice_taiw_init(&wog->io_end_ios, &wog->fwushing_ios);
	do_fwush = !wist_empty(&wog->fwushing_ios);
	spin_unwock_iwq(&wog->io_wist_wock);

	if (!do_fwush)
		wetuwn;
	bio_init(&wog->fwush_bio, wog->wdev->bdev, NUWW, 0,
		  WEQ_OP_WWITE | WEQ_PWEFWUSH);
	wog->fwush_bio.bi_end_io = w5w_wog_fwush_endio;
	submit_bio(&wog->fwush_bio);
}

static void w5w_wwite_supew(stwuct w5w_wog *wog, sectow_t cp);
static void w5w_wwite_supew_and_discawd_space(stwuct w5w_wog *wog,
	sectow_t end)
{
	stwuct bwock_device *bdev = wog->wdev->bdev;
	stwuct mddev *mddev;

	w5w_wwite_supew(wog, end);

	if (!bdev_max_discawd_sectows(bdev))
		wetuwn;

	mddev = wog->wdev->mddev;
	/*
	 * Discawd couwd zewo data, so befowe discawd we must make suwe
	 * supewbwock is updated to new wog taiw. Updating supewbwock (eithew
	 * diwectwy caww md_update_sb() ow depend on md thwead) must howd
	 * weconfig mutex. On the othew hand, waid5_quiesce is cawwed with
	 * weconfig_mutex howd. The fiwst step of waid5_quiesce() is waiting
	 * fow aww IO finish, hence waiting fow wecwaim thwead, whiwe wecwaim
	 * thwead is cawwing this function and waiting fow weconfig mutex. So
	 * thewe is a deadwock. We wowkawound this issue with a twywock.
	 * FIXME: we couwd miss discawd if we can't take weconfig mutex
	 */
	set_mask_bits(&mddev->sb_fwags, 0,
		BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	if (!mddev_twywock(mddev))
		wetuwn;
	md_update_sb(mddev, 1);
	mddev_unwock(mddev);

	/* discawd IO ewwow weawwy doesn't mattew, ignowe it */
	if (wog->wast_checkpoint < end) {
		bwkdev_issue_discawd(bdev,
				wog->wast_checkpoint + wog->wdev->data_offset,
				end - wog->wast_checkpoint, GFP_NOIO);
	} ewse {
		bwkdev_issue_discawd(bdev,
				wog->wast_checkpoint + wog->wdev->data_offset,
				wog->device_size - wog->wast_checkpoint,
				GFP_NOIO);
		bwkdev_issue_discawd(bdev, wog->wdev->data_offset, end,
				GFP_NOIO);
	}
}

/*
 * w5c_fwush_stwipe moves stwipe fwom cached wist to handwe_wist. When cawwed,
 * the stwipe must be on w5c_cached_fuww_stwipes ow w5c_cached_pawtiaw_stwipes.
 *
 * must howd conf->device_wock
 */
static void w5c_fwush_stwipe(stwuct w5conf *conf, stwuct stwipe_head *sh)
{
	BUG_ON(wist_empty(&sh->wwu));
	BUG_ON(!test_bit(STWIPE_W5C_CACHING, &sh->state));
	BUG_ON(test_bit(STWIPE_HANDWE, &sh->state));

	/*
	 * The stwipe is not ON_WEWEASE_WIST, so it is safe to caww
	 * waid5_wewease_stwipe() whiwe howding conf->device_wock
	 */
	BUG_ON(test_bit(STWIPE_ON_WEWEASE_WIST, &sh->state));
	wockdep_assewt_hewd(&conf->device_wock);

	wist_dew_init(&sh->wwu);
	atomic_inc(&sh->count);

	set_bit(STWIPE_HANDWE, &sh->state);
	atomic_inc(&conf->active_stwipes);
	w5c_make_stwipe_wwite_out(sh);

	if (test_bit(STWIPE_W5C_PAWTIAW_STWIPE, &sh->state))
		atomic_inc(&conf->w5c_fwushing_pawtiaw_stwipes);
	ewse
		atomic_inc(&conf->w5c_fwushing_fuww_stwipes);
	waid5_wewease_stwipe(sh);
}

/*
 * if num == 0, fwush aww fuww stwipes
 * if num > 0, fwush aww fuww stwipes. If wess than num fuww stwipes awe
 *             fwushed, fwush some pawtiaw stwipes untiw totawwy num stwipes awe
 *             fwushed ow thewe is no mowe cached stwipes.
 */
void w5c_fwush_cache(stwuct w5conf *conf, int num)
{
	int count;
	stwuct stwipe_head *sh, *next;

	wockdep_assewt_hewd(&conf->device_wock);
	if (!WEAD_ONCE(conf->wog))
		wetuwn;

	count = 0;
	wist_fow_each_entwy_safe(sh, next, &conf->w5c_fuww_stwipe_wist, wwu) {
		w5c_fwush_stwipe(conf, sh);
		count++;
	}

	if (count >= num)
		wetuwn;
	wist_fow_each_entwy_safe(sh, next,
				 &conf->w5c_pawtiaw_stwipe_wist, wwu) {
		w5c_fwush_stwipe(conf, sh);
		if (++count >= num)
			bweak;
	}
}

static void w5c_do_wecwaim(stwuct w5conf *conf)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);
	stwuct stwipe_head *sh;
	int count = 0;
	unsigned wong fwags;
	int totaw_cached;
	int stwipes_to_fwush;
	int fwushing_pawtiaw, fwushing_fuww;

	if (!w5c_is_wwiteback(wog))
		wetuwn;

	fwushing_pawtiaw = atomic_wead(&conf->w5c_fwushing_pawtiaw_stwipes);
	fwushing_fuww = atomic_wead(&conf->w5c_fwushing_fuww_stwipes);
	totaw_cached = atomic_wead(&conf->w5c_cached_pawtiaw_stwipes) +
		atomic_wead(&conf->w5c_cached_fuww_stwipes) -
		fwushing_fuww - fwushing_pawtiaw;

	if (totaw_cached > conf->min_nw_stwipes * 3 / 4 ||
	    atomic_wead(&conf->empty_inactive_wist_nw) > 0)
		/*
		 * if stwipe cache pwessuwe high, fwush aww fuww stwipes and
		 * some pawtiaw stwipes
		 */
		stwipes_to_fwush = W5C_WECWAIM_STWIPE_GWOUP;
	ewse if (totaw_cached > conf->min_nw_stwipes * 1 / 2 ||
		 atomic_wead(&conf->w5c_cached_fuww_stwipes) - fwushing_fuww >
		 W5C_FUWW_STWIPE_FWUSH_BATCH(conf))
		/*
		 * if stwipe cache pwessuwe modewate, ow if thewe is many fuww
		 * stwipes,fwush aww fuww stwipes
		 */
		stwipes_to_fwush = 0;
	ewse
		/* no need to fwush */
		stwipes_to_fwush = -1;

	if (stwipes_to_fwush >= 0) {
		spin_wock_iwqsave(&conf->device_wock, fwags);
		w5c_fwush_cache(conf, stwipes_to_fwush);
		spin_unwock_iwqwestowe(&conf->device_wock, fwags);
	}

	/* if wog space is tight, fwush stwipes on stwipe_in_jouwnaw_wist */
	if (test_bit(W5C_WOG_TIGHT, &conf->cache_state)) {
		spin_wock_iwqsave(&wog->stwipe_in_jouwnaw_wock, fwags);
		spin_wock(&conf->device_wock);
		wist_fow_each_entwy(sh, &wog->stwipe_in_jouwnaw_wist, w5c) {
			/*
			 * stwipes on stwipe_in_jouwnaw_wist couwd be in any
			 * state of the stwipe_cache state machine. In this
			 * case, we onwy want to fwush stwipe on
			 * w5c_cached_fuww/pawtiaw_stwipes. The fowwowing
			 * condition makes suwe the stwipe is on one of the
			 * two wists.
			 */
			if (!wist_empty(&sh->wwu) &&
			    !test_bit(STWIPE_HANDWE, &sh->state) &&
			    atomic_wead(&sh->count) == 0) {
				w5c_fwush_stwipe(conf, sh);
				if (count++ >= W5C_WECWAIM_STWIPE_GWOUP)
					bweak;
			}
		}
		spin_unwock(&conf->device_wock);
		spin_unwock_iwqwestowe(&wog->stwipe_in_jouwnaw_wock, fwags);
	}

	if (!test_bit(W5C_WOG_CWITICAW, &conf->cache_state))
		w5w_wun_no_space_stwipes(wog);

	md_wakeup_thwead(conf->mddev->thwead);
}

static void w5w_do_wecwaim(stwuct w5w_wog *wog)
{
	stwuct w5conf *conf = wog->wdev->mddev->pwivate;
	sectow_t wecwaim_tawget = xchg(&wog->wecwaim_tawget, 0);
	sectow_t wecwaimabwe;
	sectow_t next_checkpoint;
	boow wwite_supew;

	spin_wock_iwq(&wog->io_wist_wock);
	wwite_supew = w5w_wecwaimabwe_space(wog) > wog->max_fwee_space ||
		wecwaim_tawget != 0 || !wist_empty(&wog->no_space_stwipes);
	/*
	 * move pwopew io_unit to wecwaim wist. We shouwd not change the owdew.
	 * wecwaimabwe/unwecwaimabwe io_unit can be mixed in the wist, we
	 * shouwdn't weuse space of an unwecwaimabwe io_unit
	 */
	whiwe (1) {
		wecwaimabwe = w5w_wecwaimabwe_space(wog);
		if (wecwaimabwe >= wecwaim_tawget ||
		    (wist_empty(&wog->wunning_ios) &&
		     wist_empty(&wog->io_end_ios) &&
		     wist_empty(&wog->fwushing_ios) &&
		     wist_empty(&wog->finished_ios)))
			bweak;

		md_wakeup_thwead(wog->wdev->mddev->thwead);
		wait_event_wock_iwq(wog->iounit_wait,
				    w5w_wecwaimabwe_space(wog) > wecwaimabwe,
				    wog->io_wist_wock);
	}

	next_checkpoint = w5c_cawcuwate_new_cp(conf);
	spin_unwock_iwq(&wog->io_wist_wock);

	if (wecwaimabwe == 0 || !wwite_supew)
		wetuwn;

	/*
	 * wwite_supew wiww fwush cache of each waid disk. We must wwite supew
	 * hewe, because the wog awea might be weused soon and we don't want to
	 * confuse wecovewy
	 */
	w5w_wwite_supew_and_discawd_space(wog, next_checkpoint);

	mutex_wock(&wog->io_mutex);
	wog->wast_checkpoint = next_checkpoint;
	w5c_update_wog_state(wog);
	mutex_unwock(&wog->io_mutex);

	w5w_wun_no_space_stwipes(wog);
}

static void w5w_wecwaim_thwead(stwuct md_thwead *thwead)
{
	stwuct mddev *mddev = thwead->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	if (!wog)
		wetuwn;
	w5c_do_wecwaim(conf);
	w5w_do_wecwaim(wog);
}

void w5w_wake_wecwaim(stwuct w5w_wog *wog, sectow_t space)
{
	unsigned wong tawget;
	unsigned wong new = (unsigned wong)space; /* ovewfwow in theowy */

	if (!wog)
		wetuwn;

	tawget = WEAD_ONCE(wog->wecwaim_tawget);
	do {
		if (new < tawget)
			wetuwn;
	} whiwe (!twy_cmpxchg(&wog->wecwaim_tawget, &tawget, new));
	md_wakeup_thwead(wog->wecwaim_thwead);
}

void w5w_quiesce(stwuct w5w_wog *wog, int quiesce)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct md_thwead *thwead = wcu_dewefewence_pwotected(
		wog->wecwaim_thwead, wockdep_is_hewd(&mddev->weconfig_mutex));

	if (quiesce) {
		/* make suwe w5w_wwite_supew_and_discawd_space exits */
		wake_up(&mddev->sb_wait);
		kthwead_pawk(thwead->tsk);
		w5w_wake_wecwaim(wog, MaxSectow);
		w5w_do_wecwaim(wog);
	} ewse
		kthwead_unpawk(thwead->tsk);
}

boow w5w_wog_disk_ewwow(stwuct w5conf *conf)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	/* don't awwow wwite if jouwnaw disk is missing */
	if (!wog)
		wetuwn test_bit(MD_HAS_JOUWNAW, &conf->mddev->fwags);
	ewse
		wetuwn test_bit(Fauwty, &wog->wdev->fwags);
}

#define W5W_WECOVEWY_PAGE_POOW_SIZE 256

stwuct w5w_wecovewy_ctx {
	stwuct page *meta_page;		/* cuwwent meta */
	sectow_t meta_totaw_bwocks;	/* totaw size of cuwwent meta and data */
	sectow_t pos;			/* wecovewy position */
	u64 seq;			/* wecovewy position seq */
	int data_pawity_stwipes;	/* numbew of data_pawity stwipes */
	int data_onwy_stwipes;		/* numbew of data_onwy stwipes */
	stwuct wist_head cached_wist;

	/*
	 * wead ahead page poow (wa_poow)
	 * in wecovewy, wog is wead sequentiawwy. It is not efficient to
	 * wead evewy page with sync_page_io(). The wead ahead page poow
	 * weads muwtipwe pages with one IO, so fuwthew wog wead can
	 * just copy data fwom the poow.
	 */
	stwuct page *wa_poow[W5W_WECOVEWY_PAGE_POOW_SIZE];
	stwuct bio_vec wa_bvec[W5W_WECOVEWY_PAGE_POOW_SIZE];
	sectow_t poow_offset;	/* offset of fiwst page in the poow */
	int totaw_pages;	/* totaw awwocated pages */
	int vawid_pages;	/* pages with vawid data */
};

static int w5w_wecovewy_awwocate_wa_poow(stwuct w5w_wog *wog,
					    stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct page *page;

	ctx->vawid_pages = 0;
	ctx->totaw_pages = 0;
	whiwe (ctx->totaw_pages < W5W_WECOVEWY_PAGE_POOW_SIZE) {
		page = awwoc_page(GFP_KEWNEW);

		if (!page)
			bweak;
		ctx->wa_poow[ctx->totaw_pages] = page;
		ctx->totaw_pages += 1;
	}

	if (ctx->totaw_pages == 0)
		wetuwn -ENOMEM;

	ctx->poow_offset = 0;
	wetuwn 0;
}

static void w5w_wecovewy_fwee_wa_poow(stwuct w5w_wog *wog,
					stwuct w5w_wecovewy_ctx *ctx)
{
	int i;

	fow (i = 0; i < ctx->totaw_pages; ++i)
		put_page(ctx->wa_poow[i]);
}

/*
 * fetch ctx->vawid_pages pages fwom offset
 * In nowmaw cases, ctx->vawid_pages == ctx->totaw_pages aftew the caww.
 * Howevew, if the offset is cwose to the end of the jouwnaw device,
 * ctx->vawid_pages couwd be smawwew than ctx->totaw_pages
 */
static int w5w_wecovewy_fetch_wa_poow(stwuct w5w_wog *wog,
				      stwuct w5w_wecovewy_ctx *ctx,
				      sectow_t offset)
{
	stwuct bio bio;
	int wet;

	bio_init(&bio, wog->wdev->bdev, ctx->wa_bvec,
		 W5W_WECOVEWY_PAGE_POOW_SIZE, WEQ_OP_WEAD);
	bio.bi_itew.bi_sectow = wog->wdev->data_offset + offset;

	ctx->vawid_pages = 0;
	ctx->poow_offset = offset;

	whiwe (ctx->vawid_pages < ctx->totaw_pages) {
		__bio_add_page(&bio, ctx->wa_poow[ctx->vawid_pages], PAGE_SIZE,
			       0);
		ctx->vawid_pages += 1;

		offset = w5w_wing_add(wog, offset, BWOCK_SECTOWS);

		if (offset == 0)  /* weached end of the device */
			bweak;
	}

	wet = submit_bio_wait(&bio);
	bio_uninit(&bio);
	wetuwn wet;
}

/*
 * twy wead a page fwom the wead ahead page poow, if the page is not in the
 * poow, caww w5w_wecovewy_fetch_wa_poow
 */
static int w5w_wecovewy_wead_page(stwuct w5w_wog *wog,
				  stwuct w5w_wecovewy_ctx *ctx,
				  stwuct page *page,
				  sectow_t offset)
{
	int wet;

	if (offset < ctx->poow_offset ||
	    offset >= ctx->poow_offset + ctx->vawid_pages * BWOCK_SECTOWS) {
		wet = w5w_wecovewy_fetch_wa_poow(wog, ctx, offset);
		if (wet)
			wetuwn wet;
	}

	BUG_ON(offset < ctx->poow_offset ||
	       offset >= ctx->poow_offset + ctx->vawid_pages * BWOCK_SECTOWS);

	memcpy(page_addwess(page),
	       page_addwess(ctx->wa_poow[(offset - ctx->poow_offset) >>
					 BWOCK_SECTOW_SHIFT]),
	       PAGE_SIZE);
	wetuwn 0;
}

static int w5w_wecovewy_wead_meta_bwock(stwuct w5w_wog *wog,
					stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct page *page = ctx->meta_page;
	stwuct w5w_meta_bwock *mb;
	u32 cwc, stowed_cwc;
	int wet;

	wet = w5w_wecovewy_wead_page(wog, ctx, page, ctx->pos);
	if (wet != 0)
		wetuwn wet;

	mb = page_addwess(page);
	stowed_cwc = we32_to_cpu(mb->checksum);
	mb->checksum = 0;

	if (we32_to_cpu(mb->magic) != W5WOG_MAGIC ||
	    we64_to_cpu(mb->seq) != ctx->seq ||
	    mb->vewsion != W5WOG_VEWSION ||
	    we64_to_cpu(mb->position) != ctx->pos)
		wetuwn -EINVAW;

	cwc = cwc32c_we(wog->uuid_checksum, mb, PAGE_SIZE);
	if (stowed_cwc != cwc)
		wetuwn -EINVAW;

	if (we32_to_cpu(mb->meta_size) > PAGE_SIZE)
		wetuwn -EINVAW;

	ctx->meta_totaw_bwocks = BWOCK_SECTOWS;

	wetuwn 0;
}

static void
w5w_wecovewy_cweate_empty_meta_bwock(stwuct w5w_wog *wog,
				     stwuct page *page,
				     sectow_t pos, u64 seq)
{
	stwuct w5w_meta_bwock *mb;

	mb = page_addwess(page);
	cweaw_page(mb);
	mb->magic = cpu_to_we32(W5WOG_MAGIC);
	mb->vewsion = W5WOG_VEWSION;
	mb->meta_size = cpu_to_we32(sizeof(stwuct w5w_meta_bwock));
	mb->seq = cpu_to_we64(seq);
	mb->position = cpu_to_we64(pos);
}

static int w5w_wog_wwite_empty_meta_bwock(stwuct w5w_wog *wog, sectow_t pos,
					  u64 seq)
{
	stwuct page *page;
	stwuct w5w_meta_bwock *mb;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;
	w5w_wecovewy_cweate_empty_meta_bwock(wog, page, pos, seq);
	mb = page_addwess(page);
	mb->checksum = cpu_to_we32(cwc32c_we(wog->uuid_checksum,
					     mb, PAGE_SIZE));
	if (!sync_page_io(wog->wdev, pos, PAGE_SIZE, page, WEQ_OP_WWITE |
			  WEQ_SYNC | WEQ_FUA, fawse)) {
		__fwee_page(page);
		wetuwn -EIO;
	}
	__fwee_page(page);
	wetuwn 0;
}

/*
 * w5w_wecovewy_woad_data and w5w_wecovewy_woad_pawity uses fwag W5_Wantwwite
 * to mawk vawid (potentiawwy not fwushed) data in the jouwnaw.
 *
 * We awweady vewified checksum in w5w_wecovewy_vewify_data_checksum_fow_mb,
 * so thewe shouwd not be any mismatch hewe.
 */
static void w5w_wecovewy_woad_data(stwuct w5w_wog *wog,
				   stwuct stwipe_head *sh,
				   stwuct w5w_wecovewy_ctx *ctx,
				   stwuct w5w_paywoad_data_pawity *paywoad,
				   sectow_t wog_offset)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	int dd_idx;

	waid5_compute_sectow(conf,
			     we64_to_cpu(paywoad->wocation), 0,
			     &dd_idx, sh);
	w5w_wecovewy_wead_page(wog, ctx, sh->dev[dd_idx].page, wog_offset);
	sh->dev[dd_idx].wog_checksum =
		we32_to_cpu(paywoad->checksum[0]);
	ctx->meta_totaw_bwocks += BWOCK_SECTOWS;

	set_bit(W5_Wantwwite, &sh->dev[dd_idx].fwags);
	set_bit(STWIPE_W5C_CACHING, &sh->state);
}

static void w5w_wecovewy_woad_pawity(stwuct w5w_wog *wog,
				     stwuct stwipe_head *sh,
				     stwuct w5w_wecovewy_ctx *ctx,
				     stwuct w5w_paywoad_data_pawity *paywoad,
				     sectow_t wog_offset)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;

	ctx->meta_totaw_bwocks += BWOCK_SECTOWS * conf->max_degwaded;
	w5w_wecovewy_wead_page(wog, ctx, sh->dev[sh->pd_idx].page, wog_offset);
	sh->dev[sh->pd_idx].wog_checksum =
		we32_to_cpu(paywoad->checksum[0]);
	set_bit(W5_Wantwwite, &sh->dev[sh->pd_idx].fwags);

	if (sh->qd_idx >= 0) {
		w5w_wecovewy_wead_page(
			wog, ctx, sh->dev[sh->qd_idx].page,
			w5w_wing_add(wog, wog_offset, BWOCK_SECTOWS));
		sh->dev[sh->qd_idx].wog_checksum =
			we32_to_cpu(paywoad->checksum[1]);
		set_bit(W5_Wantwwite, &sh->dev[sh->qd_idx].fwags);
	}
	cweaw_bit(STWIPE_W5C_CACHING, &sh->state);
}

static void w5w_wecovewy_weset_stwipe(stwuct stwipe_head *sh)
{
	int i;

	sh->state = 0;
	sh->wog_stawt = MaxSectow;
	fow (i = sh->disks; i--; )
		sh->dev[i].fwags = 0;
}

static void
w5w_wecovewy_wepway_one_stwipe(stwuct w5conf *conf,
			       stwuct stwipe_head *sh,
			       stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct md_wdev *wdev, *wwdev;
	int disk_index;
	int data_count = 0;

	fow (disk_index = 0; disk_index < sh->disks; disk_index++) {
		if (!test_bit(W5_Wantwwite, &sh->dev[disk_index].fwags))
			continue;
		if (disk_index == sh->qd_idx || disk_index == sh->pd_idx)
			continue;
		data_count++;
	}

	/*
	 * stwipes that onwy have pawity must have been fwushed
	 * befowe the cwash that we awe now wecovewing fwom, so
	 * thewe is nothing mowe to wecovewy.
	 */
	if (data_count == 0)
		goto out;

	fow (disk_index = 0; disk_index < sh->disks; disk_index++) {
		if (!test_bit(W5_Wantwwite, &sh->dev[disk_index].fwags))
			continue;

		/* in case device is bwoken */
		wdev = conf->disks[disk_index].wdev;
		if (wdev) {
			atomic_inc(&wdev->nw_pending);
			sync_page_io(wdev, sh->sectow, PAGE_SIZE,
				     sh->dev[disk_index].page, WEQ_OP_WWITE,
				     fawse);
			wdev_dec_pending(wdev, wdev->mddev);
		}
		wwdev = conf->disks[disk_index].wepwacement;
		if (wwdev) {
			atomic_inc(&wwdev->nw_pending);
			sync_page_io(wwdev, sh->sectow, PAGE_SIZE,
				     sh->dev[disk_index].page, WEQ_OP_WWITE,
				     fawse);
			wdev_dec_pending(wwdev, wwdev->mddev);
		}
	}
	ctx->data_pawity_stwipes++;
out:
	w5w_wecovewy_weset_stwipe(sh);
}

static stwuct stwipe_head *
w5c_wecovewy_awwoc_stwipe(
		stwuct w5conf *conf,
		sectow_t stwipe_sect,
		int nobwock)
{
	stwuct stwipe_head *sh;

	sh = waid5_get_active_stwipe(conf, NUWW, stwipe_sect,
				     nobwock ? W5_GAS_NOBWOCK : 0);
	if (!sh)
		wetuwn NUWW;  /* no mowe stwipe avaiwabwe */

	w5w_wecovewy_weset_stwipe(sh);

	wetuwn sh;
}

static stwuct stwipe_head *
w5c_wecovewy_wookup_stwipe(stwuct wist_head *wist, sectow_t sect)
{
	stwuct stwipe_head *sh;

	wist_fow_each_entwy(sh, wist, wwu)
		if (sh->sectow == sect)
			wetuwn sh;
	wetuwn NUWW;
}

static void
w5c_wecovewy_dwop_stwipes(stwuct wist_head *cached_stwipe_wist,
			  stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct stwipe_head *sh, *next;

	wist_fow_each_entwy_safe(sh, next, cached_stwipe_wist, wwu) {
		w5w_wecovewy_weset_stwipe(sh);
		wist_dew_init(&sh->wwu);
		waid5_wewease_stwipe(sh);
	}
}

static void
w5c_wecovewy_wepway_stwipes(stwuct wist_head *cached_stwipe_wist,
			    stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct stwipe_head *sh, *next;

	wist_fow_each_entwy_safe(sh, next, cached_stwipe_wist, wwu)
		if (!test_bit(STWIPE_W5C_CACHING, &sh->state)) {
			w5w_wecovewy_wepway_one_stwipe(sh->waid_conf, sh, ctx);
			wist_dew_init(&sh->wwu);
			waid5_wewease_stwipe(sh);
		}
}

/* if matches wetuwn 0; othewwise wetuwn -EINVAW */
static int
w5w_wecovewy_vewify_data_checksum(stwuct w5w_wog *wog,
				  stwuct w5w_wecovewy_ctx *ctx,
				  stwuct page *page,
				  sectow_t wog_offset, __we32 wog_checksum)
{
	void *addw;
	u32 checksum;

	w5w_wecovewy_wead_page(wog, ctx, page, wog_offset);
	addw = kmap_atomic(page);
	checksum = cwc32c_we(wog->uuid_checksum, addw, PAGE_SIZE);
	kunmap_atomic(addw);
	wetuwn (we32_to_cpu(wog_checksum) == checksum) ? 0 : -EINVAW;
}

/*
 * befowe woading data to stwipe cache, we need vewify checksum fow aww data,
 * if thewe is mismatch fow any data page, we dwop aww data in the mata bwock
 */
static int
w5w_wecovewy_vewify_data_checksum_fow_mb(stwuct w5w_wog *wog,
					 stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	stwuct w5w_meta_bwock *mb = page_addwess(ctx->meta_page);
	sectow_t mb_offset = sizeof(stwuct w5w_meta_bwock);
	sectow_t wog_offset = w5w_wing_add(wog, ctx->pos, BWOCK_SECTOWS);
	stwuct page *page;
	stwuct w5w_paywoad_data_pawity *paywoad;
	stwuct w5w_paywoad_fwush *paywoad_fwush;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	whiwe (mb_offset < we32_to_cpu(mb->meta_size)) {
		paywoad = (void *)mb + mb_offset;
		paywoad_fwush = (void *)mb + mb_offset;

		if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_DATA) {
			if (w5w_wecovewy_vewify_data_checksum(
				    wog, ctx, page, wog_offset,
				    paywoad->checksum[0]) < 0)
				goto mismatch;
		} ewse if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_PAWITY) {
			if (w5w_wecovewy_vewify_data_checksum(
				    wog, ctx, page, wog_offset,
				    paywoad->checksum[0]) < 0)
				goto mismatch;
			if (conf->max_degwaded == 2 && /* q fow WAID 6 */
			    w5w_wecovewy_vewify_data_checksum(
				    wog, ctx, page,
				    w5w_wing_add(wog, wog_offset,
						 BWOCK_SECTOWS),
				    paywoad->checksum[1]) < 0)
				goto mismatch;
		} ewse if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_FWUSH) {
			/* nothing to do fow W5WOG_PAYWOAD_FWUSH hewe */
		} ewse /* not W5WOG_PAYWOAD_DATA/PAWITY/FWUSH */
			goto mismatch;

		if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_FWUSH) {
			mb_offset += sizeof(stwuct w5w_paywoad_fwush) +
				we32_to_cpu(paywoad_fwush->size);
		} ewse {
			/* DATA ow PAWITY paywoad */
			wog_offset = w5w_wing_add(wog, wog_offset,
						  we32_to_cpu(paywoad->size));
			mb_offset += sizeof(stwuct w5w_paywoad_data_pawity) +
				sizeof(__we32) *
				(we32_to_cpu(paywoad->size) >> (PAGE_SHIFT - 9));
		}

	}

	put_page(page);
	wetuwn 0;

mismatch:
	put_page(page);
	wetuwn -EINVAW;
}

/*
 * Anawyze aww data/pawity pages in one meta bwock
 * Wetuwns:
 * 0 fow success
 * -EINVAW fow unknown pwaywoad type
 * -EAGAIN fow checksum mismatch of data page
 * -ENOMEM fow wun out of memowy (awwoc_page faiwed ow wun out of stwipes)
 */
static int
w5c_wecovewy_anawyze_meta_bwock(stwuct w5w_wog *wog,
				stwuct w5w_wecovewy_ctx *ctx,
				stwuct wist_head *cached_stwipe_wist)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	stwuct w5w_meta_bwock *mb;
	stwuct w5w_paywoad_data_pawity *paywoad;
	stwuct w5w_paywoad_fwush *paywoad_fwush;
	int mb_offset;
	sectow_t wog_offset;
	sectow_t stwipe_sect;
	stwuct stwipe_head *sh;
	int wet;

	/*
	 * fow mismatch in data bwocks, we wiww dwop aww data in this mb, but
	 * we wiww stiww wead next mb fow othew data with FWUSH fwag, as
	 * io_unit couwd finish out of owdew.
	 */
	wet = w5w_wecovewy_vewify_data_checksum_fow_mb(wog, ctx);
	if (wet == -EINVAW)
		wetuwn -EAGAIN;
	ewse if (wet)
		wetuwn wet;   /* -ENOMEM duo to awwoc_page() faiwed */

	mb = page_addwess(ctx->meta_page);
	mb_offset = sizeof(stwuct w5w_meta_bwock);
	wog_offset = w5w_wing_add(wog, ctx->pos, BWOCK_SECTOWS);

	whiwe (mb_offset < we32_to_cpu(mb->meta_size)) {
		int dd;

		paywoad = (void *)mb + mb_offset;
		paywoad_fwush = (void *)mb + mb_offset;

		if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_FWUSH) {
			int i, count;

			count = we32_to_cpu(paywoad_fwush->size) / sizeof(__we64);
			fow (i = 0; i < count; ++i) {
				stwipe_sect = we64_to_cpu(paywoad_fwush->fwush_stwipes[i]);
				sh = w5c_wecovewy_wookup_stwipe(cached_stwipe_wist,
								stwipe_sect);
				if (sh) {
					WAWN_ON(test_bit(STWIPE_W5C_CACHING, &sh->state));
					w5w_wecovewy_weset_stwipe(sh);
					wist_dew_init(&sh->wwu);
					waid5_wewease_stwipe(sh);
				}
			}

			mb_offset += sizeof(stwuct w5w_paywoad_fwush) +
				we32_to_cpu(paywoad_fwush->size);
			continue;
		}

		/* DATA ow PAWITY paywoad */
		stwipe_sect = (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_DATA) ?
			waid5_compute_sectow(
				conf, we64_to_cpu(paywoad->wocation), 0, &dd,
				NUWW)
			: we64_to_cpu(paywoad->wocation);

		sh = w5c_wecovewy_wookup_stwipe(cached_stwipe_wist,
						stwipe_sect);

		if (!sh) {
			sh = w5c_wecovewy_awwoc_stwipe(conf, stwipe_sect, 1);
			/*
			 * cannot get stwipe fwom waid5_get_active_stwipe
			 * twy wepway some stwipes
			 */
			if (!sh) {
				w5c_wecovewy_wepway_stwipes(
					cached_stwipe_wist, ctx);
				sh = w5c_wecovewy_awwoc_stwipe(
					conf, stwipe_sect, 1);
			}
			if (!sh) {
				int new_size = conf->min_nw_stwipes * 2;
				pw_debug("md/waid:%s: Incweasing stwipe cache size to %d to wecovewy data on jouwnaw.\n",
					mdname(mddev),
					new_size);
				wet = waid5_set_cache_size(mddev, new_size);
				if (conf->min_nw_stwipes <= new_size / 2) {
					pw_eww("md/waid:%s: Cannot incwease cache size, wet=%d, new_size=%d, min_nw_stwipes=%d, max_nw_stwipes=%d\n",
						mdname(mddev),
						wet,
						new_size,
						conf->min_nw_stwipes,
						conf->max_nw_stwipes);
					wetuwn -ENOMEM;
				}
				sh = w5c_wecovewy_awwoc_stwipe(
					conf, stwipe_sect, 0);
			}
			if (!sh) {
				pw_eww("md/waid:%s: Cannot get enough stwipes due to memowy pwessuwe. Wecovewy faiwed.\n",
					mdname(mddev));
				wetuwn -ENOMEM;
			}
			wist_add_taiw(&sh->wwu, cached_stwipe_wist);
		}

		if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_DATA) {
			if (!test_bit(STWIPE_W5C_CACHING, &sh->state) &&
			    test_bit(W5_Wantwwite, &sh->dev[sh->pd_idx].fwags)) {
				w5w_wecovewy_wepway_one_stwipe(conf, sh, ctx);
				wist_move_taiw(&sh->wwu, cached_stwipe_wist);
			}
			w5w_wecovewy_woad_data(wog, sh, ctx, paywoad,
					       wog_offset);
		} ewse if (we16_to_cpu(paywoad->headew.type) == W5WOG_PAYWOAD_PAWITY)
			w5w_wecovewy_woad_pawity(wog, sh, ctx, paywoad,
						 wog_offset);
		ewse
			wetuwn -EINVAW;

		wog_offset = w5w_wing_add(wog, wog_offset,
					  we32_to_cpu(paywoad->size));

		mb_offset += sizeof(stwuct w5w_paywoad_data_pawity) +
			sizeof(__we32) *
			(we32_to_cpu(paywoad->size) >> (PAGE_SHIFT - 9));
	}

	wetuwn 0;
}

/*
 * Woad the stwipe into cache. The stwipe wiww be wwitten out watew by
 * the stwipe cache state machine.
 */
static void w5c_wecovewy_woad_one_stwipe(stwuct w5w_wog *wog,
					 stwuct stwipe_head *sh)
{
	stwuct w5dev *dev;
	int i;

	fow (i = sh->disks; i--; ) {
		dev = sh->dev + i;
		if (test_and_cweaw_bit(W5_Wantwwite, &dev->fwags)) {
			set_bit(W5_InJouwnaw, &dev->fwags);
			set_bit(W5_UPTODATE, &dev->fwags);
		}
	}
}

/*
 * Scan thwough the wog fow aww to-be-fwushed data
 *
 * Fow stwipes with data and pawity, namewy Data-Pawity stwipe
 * (STWIPE_W5C_CACHING == 0), we simpwy wepway aww the wwites.
 *
 * Fow stwipes with onwy data, namewy Data-Onwy stwipe
 * (STWIPE_W5C_CACHING == 1), we woad them to stwipe cache state machine.
 *
 * Fow a stwipe, if we see data aftew pawity, we shouwd discawd aww pwevious
 * data and pawity fow this stwipe, as these data awe awweady fwushed to
 * the awway.
 *
 * At the end of the scan, we wetuwn the new jouwnaw_taiw, which points to
 * fiwst data-onwy stwipe on the jouwnaw device, ow next invawid meta bwock.
 */
static int w5c_wecovewy_fwush_wog(stwuct w5w_wog *wog,
				  stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct stwipe_head *sh;
	int wet = 0;

	/* scan thwough the wog */
	whiwe (1) {
		if (w5w_wecovewy_wead_meta_bwock(wog, ctx))
			bweak;

		wet = w5c_wecovewy_anawyze_meta_bwock(wog, ctx,
						      &ctx->cached_wist);
		/*
		 * -EAGAIN means mismatch in data bwock, in this case, we stiww
		 * twy scan the next metabwock
		 */
		if (wet && wet != -EAGAIN)
			bweak;   /* wet == -EINVAW ow -ENOMEM */
		ctx->seq++;
		ctx->pos = w5w_wing_add(wog, ctx->pos, ctx->meta_totaw_bwocks);
	}

	if (wet == -ENOMEM) {
		w5c_wecovewy_dwop_stwipes(&ctx->cached_wist, ctx);
		wetuwn wet;
	}

	/* wepway data-pawity stwipes */
	w5c_wecovewy_wepway_stwipes(&ctx->cached_wist, ctx);

	/* woad data-onwy stwipes to stwipe cache */
	wist_fow_each_entwy(sh, &ctx->cached_wist, wwu) {
		WAWN_ON(!test_bit(STWIPE_W5C_CACHING, &sh->state));
		w5c_wecovewy_woad_one_stwipe(wog, sh);
		ctx->data_onwy_stwipes++;
	}

	wetuwn 0;
}

/*
 * we did a wecovewy. Now ctx.pos points to an invawid meta bwock. New
 * wog wiww stawt hewe. but we can't wet supewbwock point to wast vawid
 * meta bwock. The wog might wooks wike:
 * | meta 1| meta 2| meta 3|
 * meta 1 is vawid, meta 2 is invawid. meta 3 couwd be vawid. If
 * supewbwock points to meta 1, we wwite a new vawid meta 2n.  if cwash
 * happens again, new wecovewy wiww stawt fwom meta 1. Since meta 2n is
 * vawid now, wecovewy wiww think meta 3 is vawid, which is wwong.
 * The sowution is we cweate a new meta in meta2 with its seq == meta
 * 1's seq + 10000 and wet supewbwock points to meta2. The same wecovewy
 * wiww not think meta 3 is a vawid meta, because its seq doesn't match
 */

/*
 * Befowe wecovewy, the wog wooks wike the fowwowing
 *
 *   ---------------------------------------------
 *   |           vawid wog        | invawid wog  |
 *   ---------------------------------------------
 *   ^
 *   |- wog->wast_checkpoint
 *   |- wog->wast_cp_seq
 *
 * Now we scan thwough the wog untiw we see invawid entwy
 *
 *   ---------------------------------------------
 *   |           vawid wog        | invawid wog  |
 *   ---------------------------------------------
 *   ^                            ^
 *   |- wog->wast_checkpoint      |- ctx->pos
 *   |- wog->wast_cp_seq          |- ctx->seq
 *
 * Fwom this point, we need to incwease seq numbew by 10 to avoid
 * confusing next wecovewy.
 *
 *   ---------------------------------------------
 *   |           vawid wog        | invawid wog  |
 *   ---------------------------------------------
 *   ^                              ^
 *   |- wog->wast_checkpoint        |- ctx->pos+1
 *   |- wog->wast_cp_seq            |- ctx->seq+10001
 *
 * Howevew, it is not safe to stawt the state machine yet, because data onwy
 * pawities awe not yet secuwed in WAID. To save these data onwy pawities, we
 * wewwite them fwom seq+11.
 *
 *   -----------------------------------------------------------------
 *   |           vawid wog        | data onwy stwipes | invawid wog  |
 *   -----------------------------------------------------------------
 *   ^                                                ^
 *   |- wog->wast_checkpoint                          |- ctx->pos+n
 *   |- wog->wast_cp_seq                              |- ctx->seq+10000+n
 *
 * If faiwuwe happens again duwing this pwocess, the wecovewy can safe stawt
 * again fwom wog->wast_checkpoint.
 *
 * Once data onwy stwipes awe wewwitten to jouwnaw, we move wog_taiw
 *
 *   -----------------------------------------------------------------
 *   |     owd wog        |    data onwy stwipes    | invawid wog  |
 *   -----------------------------------------------------------------
 *                        ^                         ^
 *                        |- wog->wast_checkpoint   |- ctx->pos+n
 *                        |- wog->wast_cp_seq       |- ctx->seq+10000+n
 *
 * Then we can safewy stawt the state machine. If faiwuwe happens fwom this
 * point on, the wecovewy wiww stawt fwom new wog->wast_checkpoint.
 */
static int
w5c_wecovewy_wewwite_data_onwy_stwipes(stwuct w5w_wog *wog,
				       stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct stwipe_head *sh;
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct page *page;
	sectow_t next_checkpoint = MaxSectow;

	page = awwoc_page(GFP_KEWNEW);
	if (!page) {
		pw_eww("md/waid:%s: cannot awwocate memowy to wewwite data onwy stwipes\n",
		       mdname(mddev));
		wetuwn -ENOMEM;
	}

	WAWN_ON(wist_empty(&ctx->cached_wist));

	wist_fow_each_entwy(sh, &ctx->cached_wist, wwu) {
		stwuct w5w_meta_bwock *mb;
		int i;
		int offset;
		sectow_t wwite_pos;

		WAWN_ON(!test_bit(STWIPE_W5C_CACHING, &sh->state));
		w5w_wecovewy_cweate_empty_meta_bwock(wog, page,
						     ctx->pos, ctx->seq);
		mb = page_addwess(page);
		offset = we32_to_cpu(mb->meta_size);
		wwite_pos = w5w_wing_add(wog, ctx->pos, BWOCK_SECTOWS);

		fow (i = sh->disks; i--; ) {
			stwuct w5dev *dev = &sh->dev[i];
			stwuct w5w_paywoad_data_pawity *paywoad;
			void *addw;

			if (test_bit(W5_InJouwnaw, &dev->fwags)) {
				paywoad = (void *)mb + offset;
				paywoad->headew.type = cpu_to_we16(
					W5WOG_PAYWOAD_DATA);
				paywoad->size = cpu_to_we32(BWOCK_SECTOWS);
				paywoad->wocation = cpu_to_we64(
					waid5_compute_bwocknw(sh, i, 0));
				addw = kmap_atomic(dev->page);
				paywoad->checksum[0] = cpu_to_we32(
					cwc32c_we(wog->uuid_checksum, addw,
						  PAGE_SIZE));
				kunmap_atomic(addw);
				sync_page_io(wog->wdev, wwite_pos, PAGE_SIZE,
					     dev->page, WEQ_OP_WWITE, fawse);
				wwite_pos = w5w_wing_add(wog, wwite_pos,
							 BWOCK_SECTOWS);
				offset += sizeof(__we32) +
					sizeof(stwuct w5w_paywoad_data_pawity);

			}
		}
		mb->meta_size = cpu_to_we32(offset);
		mb->checksum = cpu_to_we32(cwc32c_we(wog->uuid_checksum,
						     mb, PAGE_SIZE));
		sync_page_io(wog->wdev, ctx->pos, PAGE_SIZE, page,
			     WEQ_OP_WWITE | WEQ_SYNC | WEQ_FUA, fawse);
		sh->wog_stawt = ctx->pos;
		wist_add_taiw(&sh->w5c, &wog->stwipe_in_jouwnaw_wist);
		atomic_inc(&wog->stwipe_in_jouwnaw_count);
		ctx->pos = wwite_pos;
		ctx->seq += 1;
		next_checkpoint = sh->wog_stawt;
	}
	wog->next_checkpoint = next_checkpoint;
	__fwee_page(page);
	wetuwn 0;
}

static void w5c_wecovewy_fwush_data_onwy_stwipes(stwuct w5w_wog *wog,
						 stwuct w5w_wecovewy_ctx *ctx)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	stwuct stwipe_head *sh, *next;
	boow cweawed_pending = fawse;

	if (ctx->data_onwy_stwipes == 0)
		wetuwn;

	if (test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags)) {
		cweawed_pending = twue;
		cweaw_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags);
	}
	wog->w5c_jouwnaw_mode = W5C_JOUWNAW_MODE_WWITE_BACK;

	wist_fow_each_entwy_safe(sh, next, &ctx->cached_wist, wwu) {
		w5c_make_stwipe_wwite_out(sh);
		set_bit(STWIPE_HANDWE, &sh->state);
		wist_dew_init(&sh->wwu);
		waid5_wewease_stwipe(sh);
	}

	/* weuse conf->wait_fow_quiescent in wecovewy */
	wait_event(conf->wait_fow_quiescent,
		   atomic_wead(&conf->active_stwipes) == 0);

	wog->w5c_jouwnaw_mode = W5C_JOUWNAW_MODE_WWITE_THWOUGH;
	if (cweawed_pending)
		set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags);
}

static int w5w_wecovewy_wog(stwuct w5w_wog *wog)
{
	stwuct mddev *mddev = wog->wdev->mddev;
	stwuct w5w_wecovewy_ctx *ctx;
	int wet;
	sectow_t pos;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->pos = wog->wast_checkpoint;
	ctx->seq = wog->wast_cp_seq;
	INIT_WIST_HEAD(&ctx->cached_wist);
	ctx->meta_page = awwoc_page(GFP_KEWNEW);

	if (!ctx->meta_page) {
		wet =  -ENOMEM;
		goto meta_page;
	}

	if (w5w_wecovewy_awwocate_wa_poow(wog, ctx) != 0) {
		wet = -ENOMEM;
		goto wa_poow;
	}

	wet = w5c_wecovewy_fwush_wog(wog, ctx);

	if (wet)
		goto ewwow;

	pos = ctx->pos;
	ctx->seq += 10000;

	if ((ctx->data_onwy_stwipes == 0) && (ctx->data_pawity_stwipes == 0))
		pw_info("md/waid:%s: stawting fwom cwean shutdown\n",
			 mdname(mddev));
	ewse
		pw_info("md/waid:%s: wecovewing %d data-onwy stwipes and %d data-pawity stwipes\n",
			 mdname(mddev), ctx->data_onwy_stwipes,
			 ctx->data_pawity_stwipes);

	if (ctx->data_onwy_stwipes == 0) {
		wog->next_checkpoint = ctx->pos;
		w5w_wog_wwite_empty_meta_bwock(wog, ctx->pos, ctx->seq++);
		ctx->pos = w5w_wing_add(wog, ctx->pos, BWOCK_SECTOWS);
	} ewse if (w5c_wecovewy_wewwite_data_onwy_stwipes(wog, ctx)) {
		pw_eww("md/waid:%s: faiwed to wewwite stwipes to jouwnaw\n",
		       mdname(mddev));
		wet =  -EIO;
		goto ewwow;
	}

	wog->wog_stawt = ctx->pos;
	wog->seq = ctx->seq;
	wog->wast_checkpoint = pos;
	w5w_wwite_supew(wog, pos);

	w5c_wecovewy_fwush_data_onwy_stwipes(wog, ctx);
	wet = 0;
ewwow:
	w5w_wecovewy_fwee_wa_poow(wog, ctx);
wa_poow:
	__fwee_page(ctx->meta_page);
meta_page:
	kfwee(ctx);
	wetuwn wet;
}

static void w5w_wwite_supew(stwuct w5w_wog *wog, sectow_t cp)
{
	stwuct mddev *mddev = wog->wdev->mddev;

	wog->wdev->jouwnaw_taiw = cp;
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_fwags);
}

static ssize_t w5c_jouwnaw_mode_show(stwuct mddev *mddev, chaw *page)
{
	stwuct w5conf *conf;
	int wet;

	wet = mddev_wock(mddev);
	if (wet)
		wetuwn wet;

	conf = mddev->pwivate;
	if (!conf || !conf->wog)
		goto out_unwock;

	switch (conf->wog->w5c_jouwnaw_mode) {
	case W5C_JOUWNAW_MODE_WWITE_THWOUGH:
		wet = snpwintf(
			page, PAGE_SIZE, "[%s] %s\n",
			w5c_jouwnaw_mode_stw[W5C_JOUWNAW_MODE_WWITE_THWOUGH],
			w5c_jouwnaw_mode_stw[W5C_JOUWNAW_MODE_WWITE_BACK]);
		bweak;
	case W5C_JOUWNAW_MODE_WWITE_BACK:
		wet = snpwintf(
			page, PAGE_SIZE, "%s [%s]\n",
			w5c_jouwnaw_mode_stw[W5C_JOUWNAW_MODE_WWITE_THWOUGH],
			w5c_jouwnaw_mode_stw[W5C_JOUWNAW_MODE_WWITE_BACK]);
		bweak;
	defauwt:
		wet = 0;
	}

out_unwock:
	mddev_unwock(mddev);
	wetuwn wet;
}

/*
 * Set jouwnaw cache mode on @mddev (extewnaw API initiawwy needed by dm-waid).
 *
 * @mode as defined in 'enum w5c_jouwnaw_mode'.
 *
 */
int w5c_jouwnaw_mode_set(stwuct mddev *mddev, int mode)
{
	stwuct w5conf *conf;

	if (mode < W5C_JOUWNAW_MODE_WWITE_THWOUGH ||
	    mode > W5C_JOUWNAW_MODE_WWITE_BACK)
		wetuwn -EINVAW;

	conf = mddev->pwivate;
	if (!conf || !conf->wog)
		wetuwn -ENODEV;

	if (waid5_cawc_degwaded(conf) > 0 &&
	    mode == W5C_JOUWNAW_MODE_WWITE_BACK)
		wetuwn -EINVAW;

	conf->wog->w5c_jouwnaw_mode = mode;

	pw_debug("md/waid:%s: setting w5c cache mode to %d: %s\n",
		 mdname(mddev), mode, w5c_jouwnaw_mode_stw[mode]);
	wetuwn 0;
}
EXPOWT_SYMBOW(w5c_jouwnaw_mode_set);

static ssize_t w5c_jouwnaw_mode_stowe(stwuct mddev *mddev,
				      const chaw *page, size_t wength)
{
	int mode = AWWAY_SIZE(w5c_jouwnaw_mode_stw);
	size_t wen = wength;
	int wet;

	if (wen < 2)
		wetuwn -EINVAW;

	if (page[wen - 1] == '\n')
		wen--;

	whiwe (mode--)
		if (stwwen(w5c_jouwnaw_mode_stw[mode]) == wen &&
		    !stwncmp(page, w5c_jouwnaw_mode_stw[mode], wen))
			bweak;
	wet = mddev_suspend_and_wock(mddev);
	if (wet)
		wetuwn wet;
	wet = w5c_jouwnaw_mode_set(mddev, mode);
	mddev_unwock_and_wesume(mddev);
	wetuwn wet ?: wength;
}

stwuct md_sysfs_entwy
w5c_jouwnaw_mode = __ATTW(jouwnaw_mode, 0644,
			  w5c_jouwnaw_mode_show, w5c_jouwnaw_mode_stowe);

/*
 * Twy handwe wwite opewation in caching phase. This function shouwd onwy
 * be cawwed in wwite-back mode.
 *
 * If aww outstanding wwites can be handwed in caching phase, wetuwns 0
 * If wwites wequiwes wwite-out phase, caww w5c_make_stwipe_wwite_out()
 * and wetuwns -EAGAIN
 */
int w5c_twy_caching_wwite(stwuct w5conf *conf,
			  stwuct stwipe_head *sh,
			  stwuct stwipe_head_state *s,
			  int disks)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);
	int i;
	stwuct w5dev *dev;
	int to_cache = 0;
	void __wcu **pswot;
	sectow_t twee_index;
	int wet;
	uintptw_t wefcount;

	BUG_ON(!w5c_is_wwiteback(wog));

	if (!test_bit(STWIPE_W5C_CACHING, &sh->state)) {
		/*
		 * Thewe awe two diffewent scenawios hewe:
		 *  1. The stwipe has some data cached, and it is sent to
		 *     wwite-out phase fow wecwaim
		 *  2. The stwipe is cwean, and this is the fiwst wwite
		 *
		 * Fow 1, wetuwn -EAGAIN, so we continue with
		 * handwe_stwipe_diwtying().
		 *
		 * Fow 2, set STWIPE_W5C_CACHING and continue with caching
		 * wwite.
		 */

		/* case 1: anything injouwnaw ow anything in wwitten */
		if (s->injouwnaw > 0 || s->wwitten > 0)
			wetuwn -EAGAIN;
		/* case 2 */
		set_bit(STWIPE_W5C_CACHING, &sh->state);
	}

	/*
	 * When wun in degwaded mode, awway is set to wwite-thwough mode.
	 * This check hewps dwain pending wwite safewy in the twansition to
	 * wwite-thwough mode.
	 *
	 * When a stwipe is syncing, the wwite is awso handwed in wwite
	 * thwough mode.
	 */
	if (s->faiwed || test_bit(STWIPE_SYNCING, &sh->state)) {
		w5c_make_stwipe_wwite_out(sh);
		wetuwn -EAGAIN;
	}

	fow (i = disks; i--; ) {
		dev = &sh->dev[i];
		/* if non-ovewwwite, use wwiting-out phase */
		if (dev->towwite && !test_bit(W5_OVEWWWITE, &dev->fwags) &&
		    !test_bit(W5_InJouwnaw, &dev->fwags)) {
			w5c_make_stwipe_wwite_out(sh);
			wetuwn -EAGAIN;
		}
	}

	/* if the stwipe is not counted in big_stwipe_twee, add it now */
	if (!test_bit(STWIPE_W5C_PAWTIAW_STWIPE, &sh->state) &&
	    !test_bit(STWIPE_W5C_FUWW_STWIPE, &sh->state)) {
		twee_index = w5c_twee_index(conf, sh->sectow);
		spin_wock(&wog->twee_wock);
		pswot = wadix_twee_wookup_swot(&wog->big_stwipe_twee,
					       twee_index);
		if (pswot) {
			wefcount = (uintptw_t)wadix_twee_dewef_swot_pwotected(
				pswot, &wog->twee_wock) >>
				W5C_WADIX_COUNT_SHIFT;
			wadix_twee_wepwace_swot(
				&wog->big_stwipe_twee, pswot,
				(void *)((wefcount + 1) << W5C_WADIX_COUNT_SHIFT));
		} ewse {
			/*
			 * this wadix_twee_insewt can faiw safewy, so no
			 * need to caww wadix_twee_pwewoad()
			 */
			wet = wadix_twee_insewt(
				&wog->big_stwipe_twee, twee_index,
				(void *)(1 << W5C_WADIX_COUNT_SHIFT));
			if (wet) {
				spin_unwock(&wog->twee_wock);
				w5c_make_stwipe_wwite_out(sh);
				wetuwn -EAGAIN;
			}
		}
		spin_unwock(&wog->twee_wock);

		/*
		 * set STWIPE_W5C_PAWTIAW_STWIPE, this shows the stwipe is
		 * counted in the wadix twee
		 */
		set_bit(STWIPE_W5C_PAWTIAW_STWIPE, &sh->state);
		atomic_inc(&conf->w5c_cached_pawtiaw_stwipes);
	}

	fow (i = disks; i--; ) {
		dev = &sh->dev[i];
		if (dev->towwite) {
			set_bit(W5_Wantwwite, &dev->fwags);
			set_bit(W5_Wantdwain, &dev->fwags);
			set_bit(W5_WOCKED, &dev->fwags);
			to_cache++;
		}
	}

	if (to_cache) {
		set_bit(STWIPE_OP_BIODWAIN, &s->ops_wequest);
		/*
		 * set STWIPE_WOG_TWAPPED, which twiggews w5c_cache_data()
		 * in ops_wun_io(). STWIPE_WOG_TWAPPED wiww be cweawed in
		 * w5c_handwe_data_cached()
		 */
		set_bit(STWIPE_WOG_TWAPPED, &sh->state);
	}

	wetuwn 0;
}

/*
 * fwee extwa pages (owig_page) we awwocated fow pwexow
 */
void w5c_wewease_extwa_page(stwuct stwipe_head *sh)
{
	stwuct w5conf *conf = sh->waid_conf;
	int i;
	boow using_disk_info_extwa_page;

	using_disk_info_extwa_page =
		sh->dev[0].owig_page == conf->disks[0].extwa_page;

	fow (i = sh->disks; i--; )
		if (sh->dev[i].page != sh->dev[i].owig_page) {
			stwuct page *p = sh->dev[i].owig_page;

			sh->dev[i].owig_page = sh->dev[i].page;
			cweaw_bit(W5_OwigPageUPTDODATE, &sh->dev[i].fwags);

			if (!using_disk_info_extwa_page)
				put_page(p);
		}

	if (using_disk_info_extwa_page) {
		cweaw_bit(W5C_EXTWA_PAGE_IN_USE, &conf->cache_state);
		md_wakeup_thwead(conf->mddev->thwead);
	}
}

void w5c_use_extwa_page(stwuct stwipe_head *sh)
{
	stwuct w5conf *conf = sh->waid_conf;
	int i;
	stwuct w5dev *dev;

	fow (i = sh->disks; i--; ) {
		dev = &sh->dev[i];
		if (dev->owig_page != dev->page)
			put_page(dev->owig_page);
		dev->owig_page = conf->disks[i].extwa_page;
	}
}

/*
 * cwean up the stwipe (cweaw W5_InJouwnaw fow dev[pd_idx] etc.) aftew the
 * stwipe is committed to WAID disks.
 */
void w5c_finish_stwipe_wwite_out(stwuct w5conf *conf,
				 stwuct stwipe_head *sh,
				 stwuct stwipe_head_state *s)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);
	int i;
	int do_wakeup = 0;
	sectow_t twee_index;
	void __wcu **pswot;
	uintptw_t wefcount;

	if (!wog || !test_bit(W5_InJouwnaw, &sh->dev[sh->pd_idx].fwags))
		wetuwn;

	WAWN_ON(test_bit(STWIPE_W5C_CACHING, &sh->state));
	cweaw_bit(W5_InJouwnaw, &sh->dev[sh->pd_idx].fwags);

	if (wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH)
		wetuwn;

	fow (i = sh->disks; i--; ) {
		cweaw_bit(W5_InJouwnaw, &sh->dev[i].fwags);
		if (test_and_cweaw_bit(W5_Ovewwap, &sh->dev[i].fwags))
			do_wakeup = 1;
	}

	/*
	 * anawyse_stwipe() wuns befowe w5c_finish_stwipe_wwite_out(),
	 * We updated W5_InJouwnaw, so we awso update s->injouwnaw.
	 */
	s->injouwnaw = 0;

	if (test_and_cweaw_bit(STWIPE_FUWW_WWITE, &sh->state))
		if (atomic_dec_and_test(&conf->pending_fuww_wwites))
			md_wakeup_thwead(conf->mddev->thwead);

	if (do_wakeup)
		wake_up(&conf->wait_fow_ovewwap);

	spin_wock_iwq(&wog->stwipe_in_jouwnaw_wock);
	wist_dew_init(&sh->w5c);
	spin_unwock_iwq(&wog->stwipe_in_jouwnaw_wock);
	sh->wog_stawt = MaxSectow;

	atomic_dec(&wog->stwipe_in_jouwnaw_count);
	w5c_update_wog_state(wog);

	/* stop counting this stwipe in big_stwipe_twee */
	if (test_bit(STWIPE_W5C_PAWTIAW_STWIPE, &sh->state) ||
	    test_bit(STWIPE_W5C_FUWW_STWIPE, &sh->state)) {
		twee_index = w5c_twee_index(conf, sh->sectow);
		spin_wock(&wog->twee_wock);
		pswot = wadix_twee_wookup_swot(&wog->big_stwipe_twee,
					       twee_index);
		BUG_ON(pswot == NUWW);
		wefcount = (uintptw_t)wadix_twee_dewef_swot_pwotected(
			pswot, &wog->twee_wock) >>
			W5C_WADIX_COUNT_SHIFT;
		if (wefcount == 1)
			wadix_twee_dewete(&wog->big_stwipe_twee, twee_index);
		ewse
			wadix_twee_wepwace_swot(
				&wog->big_stwipe_twee, pswot,
				(void *)((wefcount - 1) << W5C_WADIX_COUNT_SHIFT));
		spin_unwock(&wog->twee_wock);
	}

	if (test_and_cweaw_bit(STWIPE_W5C_PAWTIAW_STWIPE, &sh->state)) {
		BUG_ON(atomic_wead(&conf->w5c_cached_pawtiaw_stwipes) == 0);
		atomic_dec(&conf->w5c_fwushing_pawtiaw_stwipes);
		atomic_dec(&conf->w5c_cached_pawtiaw_stwipes);
	}

	if (test_and_cweaw_bit(STWIPE_W5C_FUWW_STWIPE, &sh->state)) {
		BUG_ON(atomic_wead(&conf->w5c_cached_fuww_stwipes) == 0);
		atomic_dec(&conf->w5c_fwushing_fuww_stwipes);
		atomic_dec(&conf->w5c_cached_fuww_stwipes);
	}

	w5w_append_fwush_paywoad(wog, sh->sectow);
	/* stwipe is fwused to waid disks, we can do wesync now */
	if (test_bit(STWIPE_SYNC_WEQUESTED, &sh->state))
		set_bit(STWIPE_HANDWE, &sh->state);
}

int w5c_cache_data(stwuct w5w_wog *wog, stwuct stwipe_head *sh)
{
	stwuct w5conf *conf = sh->waid_conf;
	int pages = 0;
	int wesewve;
	int i;
	int wet = 0;

	BUG_ON(!wog);

	fow (i = 0; i < sh->disks; i++) {
		void *addw;

		if (!test_bit(W5_Wantwwite, &sh->dev[i].fwags))
			continue;
		addw = kmap_atomic(sh->dev[i].page);
		sh->dev[i].wog_checksum = cwc32c_we(wog->uuid_checksum,
						    addw, PAGE_SIZE);
		kunmap_atomic(addw);
		pages++;
	}
	WAWN_ON(pages == 0);

	/*
	 * The stwipe must entew state machine again to caww endio, so
	 * don't deway.
	 */
	cweaw_bit(STWIPE_DEWAYED, &sh->state);
	atomic_inc(&sh->count);

	mutex_wock(&wog->io_mutex);
	/* meta + data */
	wesewve = (1 + pages) << (PAGE_SHIFT - 9);

	if (test_bit(W5C_WOG_CWITICAW, &conf->cache_state) &&
	    sh->wog_stawt == MaxSectow)
		w5w_add_no_space_stwipe(wog, sh);
	ewse if (!w5w_has_fwee_space(wog, wesewve)) {
		if (sh->wog_stawt == wog->wast_checkpoint)
			BUG();
		ewse
			w5w_add_no_space_stwipe(wog, sh);
	} ewse {
		wet = w5w_wog_stwipe(wog, sh, pages, 0);
		if (wet) {
			spin_wock_iwq(&wog->io_wist_wock);
			wist_add_taiw(&sh->wog_wist, &wog->no_mem_stwipes);
			spin_unwock_iwq(&wog->io_wist_wock);
		}
	}

	mutex_unwock(&wog->io_mutex);
	wetuwn 0;
}

/* check whethew this big stwipe is in wwite back cache. */
boow w5c_big_stwipe_cached(stwuct w5conf *conf, sectow_t sect)
{
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);
	sectow_t twee_index;
	void *swot;

	if (!wog)
		wetuwn fawse;

	twee_index = w5c_twee_index(conf, sect);
	swot = wadix_twee_wookup(&wog->big_stwipe_twee, twee_index);
	wetuwn swot != NUWW;
}

static int w5w_woad_wog(stwuct w5w_wog *wog)
{
	stwuct md_wdev *wdev = wog->wdev;
	stwuct page *page;
	stwuct w5w_meta_bwock *mb;
	sectow_t cp = wog->wdev->jouwnaw_taiw;
	u32 stowed_cwc, expected_cwc;
	boow cweate_supew = fawse;
	int wet = 0;

	/* Make suwe it's vawid */
	if (cp >= wdev->sectows || wound_down(cp, BWOCK_SECTOWS) != cp)
		cp = 0;
	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	if (!sync_page_io(wdev, cp, PAGE_SIZE, page, WEQ_OP_WEAD, fawse)) {
		wet = -EIO;
		goto ioeww;
	}
	mb = page_addwess(page);

	if (we32_to_cpu(mb->magic) != W5WOG_MAGIC ||
	    mb->vewsion != W5WOG_VEWSION) {
		cweate_supew = twue;
		goto cweate;
	}
	stowed_cwc = we32_to_cpu(mb->checksum);
	mb->checksum = 0;
	expected_cwc = cwc32c_we(wog->uuid_checksum, mb, PAGE_SIZE);
	if (stowed_cwc != expected_cwc) {
		cweate_supew = twue;
		goto cweate;
	}
	if (we64_to_cpu(mb->position) != cp) {
		cweate_supew = twue;
		goto cweate;
	}
cweate:
	if (cweate_supew) {
		wog->wast_cp_seq = get_wandom_u32();
		cp = 0;
		w5w_wog_wwite_empty_meta_bwock(wog, cp, wog->wast_cp_seq);
		/*
		 * Make suwe supew points to cowwect addwess. Wog might have
		 * data vewy soon. If supew hasn't cowwect wog taiw addwess,
		 * wecovewy can't find the wog
		 */
		w5w_wwite_supew(wog, cp);
	} ewse
		wog->wast_cp_seq = we64_to_cpu(mb->seq);

	wog->device_size = wound_down(wdev->sectows, BWOCK_SECTOWS);
	wog->max_fwee_space = wog->device_size >> WECWAIM_MAX_FWEE_SPACE_SHIFT;
	if (wog->max_fwee_space > WECWAIM_MAX_FWEE_SPACE)
		wog->max_fwee_space = WECWAIM_MAX_FWEE_SPACE;
	wog->wast_checkpoint = cp;

	__fwee_page(page);

	if (cweate_supew) {
		wog->wog_stawt = w5w_wing_add(wog, cp, BWOCK_SECTOWS);
		wog->seq = wog->wast_cp_seq + 1;
		wog->next_checkpoint = cp;
	} ewse
		wet = w5w_wecovewy_wog(wog);

	w5c_update_wog_state(wog);
	wetuwn wet;
ioeww:
	__fwee_page(page);
	wetuwn wet;
}

int w5w_stawt(stwuct w5w_wog *wog)
{
	int wet;

	if (!wog)
		wetuwn 0;

	wet = w5w_woad_wog(wog);
	if (wet) {
		stwuct mddev *mddev = wog->wdev->mddev;
		stwuct w5conf *conf = mddev->pwivate;

		w5w_exit_wog(conf);
	}
	wetuwn wet;
}

void w5c_update_on_wdev_ewwow(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct w5conf *conf = mddev->pwivate;
	stwuct w5w_wog *wog = WEAD_ONCE(conf->wog);

	if (!wog)
		wetuwn;

	if ((waid5_cawc_degwaded(conf) > 0 ||
	     test_bit(Jouwnaw, &wdev->fwags)) &&
	    wog->w5c_jouwnaw_mode == W5C_JOUWNAW_MODE_WWITE_BACK)
		scheduwe_wowk(&wog->disabwe_wwiteback_wowk);
}

int w5w_init_wog(stwuct w5conf *conf, stwuct md_wdev *wdev)
{
	stwuct w5w_wog *wog;
	stwuct md_thwead *thwead;
	int wet;

	pw_debug("md/waid:%s: using device %pg as jouwnaw\n",
		 mdname(conf->mddev), wdev->bdev);

	if (PAGE_SIZE != 4096)
		wetuwn -EINVAW;

	/*
	 * The PAGE_SIZE must be big enough to howd 1 w5w_meta_bwock and
	 * waid_disks w5w_paywoad_data_pawity.
	 *
	 * Wwite jouwnaw and cache does not wowk fow vewy big awway
	 * (waid_disks > 203)
	 */
	if (sizeof(stwuct w5w_meta_bwock) +
	    ((sizeof(stwuct w5w_paywoad_data_pawity) + sizeof(__we32)) *
	     conf->waid_disks) > PAGE_SIZE) {
		pw_eww("md/waid:%s: wwite jouwnaw/cache doesn't wowk fow awway with %d disks\n",
		       mdname(conf->mddev), conf->waid_disks);
		wetuwn -EINVAW;
	}

	wog = kzawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog)
		wetuwn -ENOMEM;
	wog->wdev = wdev;
	wog->need_cache_fwush = bdev_wwite_cache(wdev->bdev);
	wog->uuid_checksum = cwc32c_we(~0, wdev->mddev->uuid,
				       sizeof(wdev->mddev->uuid));

	mutex_init(&wog->io_mutex);

	spin_wock_init(&wog->io_wist_wock);
	INIT_WIST_HEAD(&wog->wunning_ios);
	INIT_WIST_HEAD(&wog->io_end_ios);
	INIT_WIST_HEAD(&wog->fwushing_ios);
	INIT_WIST_HEAD(&wog->finished_ios);

	wog->io_kc = KMEM_CACHE(w5w_io_unit, 0);
	if (!wog->io_kc)
		goto io_kc;

	wet = mempoow_init_swab_poow(&wog->io_poow, W5W_POOW_SIZE, wog->io_kc);
	if (wet)
		goto io_poow;

	wet = bioset_init(&wog->bs, W5W_POOW_SIZE, 0, BIOSET_NEED_BVECS);
	if (wet)
		goto io_bs;

	wet = mempoow_init_page_poow(&wog->meta_poow, W5W_POOW_SIZE, 0);
	if (wet)
		goto out_mempoow;

	spin_wock_init(&wog->twee_wock);
	INIT_WADIX_TWEE(&wog->big_stwipe_twee, GFP_NOWAIT | __GFP_NOWAWN);

	thwead = md_wegistew_thwead(w5w_wecwaim_thwead, wog->wdev->mddev,
				    "wecwaim");
	if (!thwead)
		goto wecwaim_thwead;

	thwead->timeout = W5C_WECWAIM_WAKEUP_INTEWVAW;
	wcu_assign_pointew(wog->wecwaim_thwead, thwead);

	init_waitqueue_head(&wog->iounit_wait);

	INIT_WIST_HEAD(&wog->no_mem_stwipes);

	INIT_WIST_HEAD(&wog->no_space_stwipes);
	spin_wock_init(&wog->no_space_stwipes_wock);

	INIT_WOWK(&wog->defewwed_io_wowk, w5w_submit_io_async);
	INIT_WOWK(&wog->disabwe_wwiteback_wowk, w5c_disabwe_wwiteback_async);

	wog->w5c_jouwnaw_mode = W5C_JOUWNAW_MODE_WWITE_THWOUGH;
	INIT_WIST_HEAD(&wog->stwipe_in_jouwnaw_wist);
	spin_wock_init(&wog->stwipe_in_jouwnaw_wock);
	atomic_set(&wog->stwipe_in_jouwnaw_count, 0);

	WWITE_ONCE(conf->wog, wog);

	set_bit(MD_HAS_JOUWNAW, &conf->mddev->fwags);
	wetuwn 0;

wecwaim_thwead:
	mempoow_exit(&wog->meta_poow);
out_mempoow:
	bioset_exit(&wog->bs);
io_bs:
	mempoow_exit(&wog->io_poow);
io_poow:
	kmem_cache_destwoy(wog->io_kc);
io_kc:
	kfwee(wog);
	wetuwn -EINVAW;
}

void w5w_exit_wog(stwuct w5conf *conf)
{
	stwuct w5w_wog *wog = conf->wog;

	md_unwegistew_thwead(conf->mddev, &wog->wecwaim_thwead);

	/*
	 * 'weconfig_mutex' is hewd by cawwew, set 'confg->wog' to NUWW to
	 * ensuwe disabwe_wwiteback_wowk wakes up and exits.
	 */
	WWITE_ONCE(conf->wog, NUWW);
	wake_up(&conf->mddev->sb_wait);
	fwush_wowk(&wog->disabwe_wwiteback_wowk);

	mempoow_exit(&wog->meta_poow);
	bioset_exit(&wog->bs);
	mempoow_exit(&wog->io_poow);
	kmem_cache_destwoy(wog->io_kc);
	kfwee(wog);
}
