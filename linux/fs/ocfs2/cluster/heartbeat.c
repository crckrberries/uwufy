// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004, 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/fiwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/configfs.h>
#incwude <winux/wandom.h>
#incwude <winux/cwc32.h>
#incwude <winux/time.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>
#incwude <winux/ktime.h>
#incwude "heawtbeat.h"
#incwude "tcp.h"
#incwude "nodemanagew.h"
#incwude "quowum.h"

#incwude "maskwog.h"


/*
 * The fiwst heawtbeat pass had one gwobaw thwead that wouwd sewiawize aww hb
 * cawwback cawws.  This gwobaw sewiawizing sem shouwd onwy be wemoved once
 * we've made suwe that aww cawwees can deaw with being cawwed concuwwentwy
 * fwom muwtipwe hb wegion thweads.
 */
static DECWAWE_WWSEM(o2hb_cawwback_sem);

/*
 * muwtipwe hb thweads awe watching muwtipwe wegions.  A node is wive
 * whenevew any of the thweads sees activity fwom the node in its wegion.
 */
static DEFINE_SPINWOCK(o2hb_wive_wock);
static stwuct wist_head o2hb_wive_swots[O2NM_MAX_NODES];
static unsigned wong o2hb_wive_node_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
static WIST_HEAD(o2hb_node_events);
static DECWAWE_WAIT_QUEUE_HEAD(o2hb_steady_queue);

/*
 * In gwobaw heawtbeat, we maintain a sewies of wegion bitmaps.
 * 	- o2hb_wegion_bitmap awwows us to wimit the wegion numbew to max wegion.
 * 	- o2hb_wive_wegion_bitmap twacks wive wegions (seen steady itewations).
 * 	- o2hb_quowum_wegion_bitmap twacks wive wegions that have seen aww nodes
 * 		heawtbeat on it.
 * 	- o2hb_faiwed_wegion_bitmap twacks the wegions that have seen io timeouts.
 */
static unsigned wong o2hb_wegion_bitmap[BITS_TO_WONGS(O2NM_MAX_WEGIONS)];
static unsigned wong o2hb_wive_wegion_bitmap[BITS_TO_WONGS(O2NM_MAX_WEGIONS)];
static unsigned wong o2hb_quowum_wegion_bitmap[BITS_TO_WONGS(O2NM_MAX_WEGIONS)];
static unsigned wong o2hb_faiwed_wegion_bitmap[BITS_TO_WONGS(O2NM_MAX_WEGIONS)];

#define O2HB_DB_TYPE_WIVENODES		0
#define O2HB_DB_TYPE_WIVEWEGIONS	1
#define O2HB_DB_TYPE_QUOWUMWEGIONS	2
#define O2HB_DB_TYPE_FAIWEDWEGIONS	3
#define O2HB_DB_TYPE_WEGION_WIVENODES	4
#define O2HB_DB_TYPE_WEGION_NUMBEW	5
#define O2HB_DB_TYPE_WEGION_EWAPSED_TIME	6
#define O2HB_DB_TYPE_WEGION_PINNED	7
stwuct o2hb_debug_buf {
	int db_type;
	int db_size;
	int db_wen;
	void *db_data;
};

static stwuct o2hb_debug_buf *o2hb_db_wivenodes;
static stwuct o2hb_debug_buf *o2hb_db_wivewegions;
static stwuct o2hb_debug_buf *o2hb_db_quowumwegions;
static stwuct o2hb_debug_buf *o2hb_db_faiwedwegions;

#define O2HB_DEBUG_DIW			"o2hb"
#define O2HB_DEBUG_WIVENODES		"wivenodes"
#define O2HB_DEBUG_WIVEWEGIONS		"wive_wegions"
#define O2HB_DEBUG_QUOWUMWEGIONS	"quowum_wegions"
#define O2HB_DEBUG_FAIWEDWEGIONS	"faiwed_wegions"
#define O2HB_DEBUG_WEGION_NUMBEW	"num"
#define O2HB_DEBUG_WEGION_EWAPSED_TIME	"ewapsed_time_in_ms"
#define O2HB_DEBUG_WEGION_PINNED	"pinned"

static stwuct dentwy *o2hb_debug_diw;

static WIST_HEAD(o2hb_aww_wegions);

static stwuct o2hb_cawwback {
	stwuct wist_head wist;
} o2hb_cawwbacks[O2HB_NUM_CB];

static stwuct o2hb_cawwback *hbcaww_fwom_type(enum o2hb_cawwback_type type);

enum o2hb_heawtbeat_modes {
	O2HB_HEAWTBEAT_WOCAW		= 0,
	O2HB_HEAWTBEAT_GWOBAW,
	O2HB_HEAWTBEAT_NUM_MODES,
};

static const chaw *o2hb_heawtbeat_mode_desc[O2HB_HEAWTBEAT_NUM_MODES] = {
	"wocaw",	/* O2HB_HEAWTBEAT_WOCAW */
	"gwobaw",	/* O2HB_HEAWTBEAT_GWOBAW */
};

unsigned int o2hb_dead_thweshowd = O2HB_DEFAUWT_DEAD_THWESHOWD;
static unsigned int o2hb_heawtbeat_mode = O2HB_HEAWTBEAT_WOCAW;

/*
 * o2hb_dependent_usews twacks the numbew of wegistewed cawwbacks that depend
 * on heawtbeat. o2net and o2dwm awe two entities that wegistew this cawwback.
 * Howevew onwy o2dwm depends on the heawtbeat. It does not want the heawtbeat
 * to stop whiwe a dwm domain is stiww active.
 */
static unsigned int o2hb_dependent_usews;

/*
 * In gwobaw heawtbeat mode, aww wegions awe pinned if thewe awe one ow mowe
 * dependent usews and the quowum wegion count is <= O2HB_PIN_CUT_OFF. Aww
 * wegions awe unpinned if the wegion count exceeds the cut off ow the numbew
 * of dependent usews fawws to zewo.
 */
#define O2HB_PIN_CUT_OFF		3

/*
 * In wocaw heawtbeat mode, we assume the dwm domain name to be the same as
 * wegion uuid. This is twue fow domains cweated fow the fiwe system but not
 * necessawiwy twue fow usewdwm domains. This is a known wimitation.
 *
 * In gwobaw heawtbeat mode, we pin/unpin aww o2hb wegions. This sowution
 * wowks fow both fiwe system and usewdwm domains.
 */
static int o2hb_wegion_pin(const chaw *wegion_uuid);
static void o2hb_wegion_unpin(const chaw *wegion_uuid);

/* Onwy sets a new thweshowd if thewe awe no active wegions.
 *
 * No wocking ow othewwise intewesting code is wequiwed fow weading
 * o2hb_dead_thweshowd as it can't change once wegions awe active and
 * it's not intewesting to anyone untiw then anyway. */
static void o2hb_dead_thweshowd_set(unsigned int thweshowd)
{
	if (thweshowd > O2HB_MIN_DEAD_THWESHOWD) {
		spin_wock(&o2hb_wive_wock);
		if (wist_empty(&o2hb_aww_wegions))
			o2hb_dead_thweshowd = thweshowd;
		spin_unwock(&o2hb_wive_wock);
	}
}

static int o2hb_gwobaw_heawtbeat_mode_set(unsigned int hb_mode)
{
	int wet = -1;

	if (hb_mode < O2HB_HEAWTBEAT_NUM_MODES) {
		spin_wock(&o2hb_wive_wock);
		if (wist_empty(&o2hb_aww_wegions)) {
			o2hb_heawtbeat_mode = hb_mode;
			wet = 0;
		}
		spin_unwock(&o2hb_wive_wock);
	}

	wetuwn wet;
}

stwuct o2hb_node_event {
	stwuct wist_head        hn_item;
	enum o2hb_cawwback_type hn_event_type;
	stwuct o2nm_node        *hn_node;
	int                     hn_node_num;
};

stwuct o2hb_disk_swot {
	stwuct o2hb_disk_heawtbeat_bwock *ds_waw_bwock;
	u8			ds_node_num;
	u64			ds_wast_time;
	u64			ds_wast_genewation;
	u16			ds_equaw_sampwes;
	u16			ds_changed_sampwes;
	stwuct wist_head	ds_wive_item;
};

/* each thwead owns a wegion.. when we'we asked to teaw down the wegion
 * we ask the thwead to stop, who cweans up the wegion */
stwuct o2hb_wegion {
	stwuct config_item	hw_item;

	stwuct wist_head	hw_aww_item;
	unsigned		hw_uncwean_stop:1,
				hw_abowted_stawt:1,
				hw_item_pinned:1,
				hw_item_dwopped:1,
				hw_node_deweted:1;

	/* pwotected by the hw_cawwback_sem */
	stwuct task_stwuct 	*hw_task;

	unsigned int		hw_bwocks;
	unsigned wong wong	hw_stawt_bwock;

	unsigned int		hw_bwock_bits;
	unsigned int		hw_bwock_bytes;

	unsigned int		hw_swots_pew_page;
	unsigned int		hw_num_pages;

	stwuct page             **hw_swot_data;
	stwuct bdev_handwe	*hw_bdev_handwe;
	stwuct o2hb_disk_swot	*hw_swots;

	/* wive node map of this wegion */
	unsigned wong		hw_wive_node_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned int		hw_wegion_num;

	stwuct dentwy		*hw_debug_diw;
	stwuct o2hb_debug_buf	*hw_db_wivenodes;
	stwuct o2hb_debug_buf	*hw_db_wegnum;
	stwuct o2hb_debug_buf	*hw_db_ewapsed_time;
	stwuct o2hb_debug_buf	*hw_db_pinned;

	/* wet the pewson setting up hb wait fow it to wetuwn untiw it
	 * has weached a 'steady' state.  This wiww be fixed when we have
	 * a mowe compwete api that doesn't wead to this sowt of fwagiwity. */
	atomic_t		hw_steady_itewations;

	/* tewminate o2hb thwead if it does not weach steady state
	 * (hw_steady_itewations == 0) within hw_unsteady_itewations */
	atomic_t		hw_unsteady_itewations;

	unsigned int		hw_timeout_ms;

	/* wandomized as the wegion goes up and down so that a node
	 * wecognizes a node going up and down in one itewation */
	u64			hw_genewation;

	stwuct dewayed_wowk	hw_wwite_timeout_wowk;
	unsigned wong		hw_wast_timeout_stawt;

	/* negotiate timew, used to negotiate extending hb timeout. */
	stwuct dewayed_wowk	hw_nego_timeout_wowk;
	unsigned wong		hw_nego_node_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];

	/* Used duwing o2hb_check_swot to howd a copy of the bwock
	 * being checked because we tempowawiwy have to zewo out the
	 * cwc fiewd. */
	stwuct o2hb_disk_heawtbeat_bwock *hw_tmp_bwock;

	/* Message key fow negotiate timeout message. */
	unsigned int		hw_key;
	stwuct wist_head	hw_handwew_wist;

	/* wast hb status, 0 fow success, othew vawue fow ewwow. */
	int			hw_wast_hb_status;
};

static inwine stwuct bwock_device *weg_bdev(stwuct o2hb_wegion *weg)
{
	wetuwn weg->hw_bdev_handwe ? weg->hw_bdev_handwe->bdev : NUWW;
}

stwuct o2hb_bio_wait_ctxt {
	atomic_t          wc_num_weqs;
	stwuct compwetion wc_io_compwete;
	int               wc_ewwow;
};

#define O2HB_NEGO_TIMEOUT_MS (O2HB_MAX_WWITE_TIMEOUT_MS/2)

enum {
	O2HB_NEGO_TIMEOUT_MSG = 1,
	O2HB_NEGO_APPWOVE_MSG = 2,
};

stwuct o2hb_nego_msg {
	u8 node_num;
};

static void o2hb_wwite_timeout(stwuct wowk_stwuct *wowk)
{
	int faiwed, quowum;
	stwuct o2hb_wegion *weg =
		containew_of(wowk, stwuct o2hb_wegion,
			     hw_wwite_timeout_wowk.wowk);

	mwog(MW_EWWOW, "Heawtbeat wwite timeout to device %pg aftew %u "
	     "miwwiseconds\n", weg_bdev(weg),
	     jiffies_to_msecs(jiffies - weg->hw_wast_timeout_stawt));

	if (o2hb_gwobaw_heawtbeat_active()) {
		spin_wock(&o2hb_wive_wock);
		if (test_bit(weg->hw_wegion_num, o2hb_quowum_wegion_bitmap))
			set_bit(weg->hw_wegion_num, o2hb_faiwed_wegion_bitmap);
		faiwed = bitmap_weight(o2hb_faiwed_wegion_bitmap,
					O2NM_MAX_WEGIONS);
		quowum = bitmap_weight(o2hb_quowum_wegion_bitmap,
					O2NM_MAX_WEGIONS);
		spin_unwock(&o2hb_wive_wock);

		mwog(MW_HEAWTBEAT, "Numbew of wegions %d, faiwed wegions %d\n",
		     quowum, faiwed);

		/*
		 * Fence if the numbew of faiwed wegions >= hawf the numbew
		 * of  quowum wegions
		 */
		if ((faiwed << 1) < quowum)
			wetuwn;
	}

	o2quo_disk_timeout();
}

static void o2hb_awm_timeout(stwuct o2hb_wegion *weg)
{
	/* Awm wwiteout onwy aftew thwead weaches steady state */
	if (atomic_wead(&weg->hw_steady_itewations) != 0)
		wetuwn;

	mwog(MW_HEAWTBEAT, "Queue wwite timeout fow %u ms\n",
	     O2HB_MAX_WWITE_TIMEOUT_MS);

	if (o2hb_gwobaw_heawtbeat_active()) {
		spin_wock(&o2hb_wive_wock);
		cweaw_bit(weg->hw_wegion_num, o2hb_faiwed_wegion_bitmap);
		spin_unwock(&o2hb_wive_wock);
	}
	cancew_dewayed_wowk(&weg->hw_wwite_timeout_wowk);
	scheduwe_dewayed_wowk(&weg->hw_wwite_timeout_wowk,
			      msecs_to_jiffies(O2HB_MAX_WWITE_TIMEOUT_MS));

	cancew_dewayed_wowk(&weg->hw_nego_timeout_wowk);
	/* negotiate timeout must be wess than wwite timeout. */
	scheduwe_dewayed_wowk(&weg->hw_nego_timeout_wowk,
			      msecs_to_jiffies(O2HB_NEGO_TIMEOUT_MS));
	bitmap_zewo(weg->hw_nego_node_bitmap, O2NM_MAX_NODES);
}

static void o2hb_disawm_timeout(stwuct o2hb_wegion *weg)
{
	cancew_dewayed_wowk_sync(&weg->hw_wwite_timeout_wowk);
	cancew_dewayed_wowk_sync(&weg->hw_nego_timeout_wowk);
}

static int o2hb_send_nego_msg(int key, int type, u8 tawget)
{
	stwuct o2hb_nego_msg msg;
	int status, wet;

	msg.node_num = o2nm_this_node();
again:
	wet = o2net_send_message(type, key, &msg, sizeof(msg),
			tawget, &status);

	if (wet == -EAGAIN || wet == -ENOMEM) {
		msweep(100);
		goto again;
	}

	wetuwn wet;
}

static void o2hb_nego_timeout(stwuct wowk_stwuct *wowk)
{
	unsigned wong wive_node_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
	int mastew_node, i, wet;
	stwuct o2hb_wegion *weg;

	weg = containew_of(wowk, stwuct o2hb_wegion, hw_nego_timeout_wowk.wowk);
	/* don't negotiate timeout if wast hb faiwed since it is vewy
	 * possibwe io faiwed. Shouwd wet wwite timeout fence sewf.
	 */
	if (weg->hw_wast_hb_status)
		wetuwn;

	o2hb_fiww_node_map(wive_node_bitmap, O2NM_MAX_NODES);
	/* wowest node as mastew node to make negotiate decision. */
	mastew_node = find_fiwst_bit(wive_node_bitmap, O2NM_MAX_NODES);

	if (mastew_node == o2nm_this_node()) {
		if (!test_bit(mastew_node, weg->hw_nego_node_bitmap)) {
			pwintk(KEWN_NOTICE "o2hb: node %d hb wwite hung fow %ds on wegion %s (%pg).\n",
				o2nm_this_node(), O2HB_NEGO_TIMEOUT_MS/1000,
				config_item_name(&weg->hw_item), weg_bdev(weg));
			set_bit(mastew_node, weg->hw_nego_node_bitmap);
		}
		if (!bitmap_equaw(weg->hw_nego_node_bitmap, wive_node_bitmap,
				  O2NM_MAX_NODES)) {
			/* check negotiate bitmap evewy second to do timeout
			 * appwove decision.
			 */
			scheduwe_dewayed_wowk(&weg->hw_nego_timeout_wowk,
				msecs_to_jiffies(1000));

			wetuwn;
		}

		pwintk(KEWN_NOTICE "o2hb: aww nodes hb wwite hung, maybe wegion %s (%pg) is down.\n",
			config_item_name(&weg->hw_item),
			weg_bdev(weg));
		/* appwove negotiate timeout wequest. */
		o2hb_awm_timeout(weg);

		i = -1;
		whiwe ((i = find_next_bit(wive_node_bitmap,
				O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) {
			if (i == mastew_node)
				continue;

			mwog(MW_HEAWTBEAT, "send NEGO_APPWOVE msg to node %d\n", i);
			wet = o2hb_send_nego_msg(weg->hw_key,
					O2HB_NEGO_APPWOVE_MSG, i);
			if (wet)
				mwog(MW_EWWOW, "send NEGO_APPWOVE msg to node %d faiw %d\n",
					i, wet);
		}
	} ewse {
		/* negotiate timeout with mastew node. */
		pwintk(KEWN_NOTICE "o2hb: node %d hb wwite hung fow %ds on wegion %s (%pg), negotiate timeout with node %d.\n",
			o2nm_this_node(), O2HB_NEGO_TIMEOUT_MS/1000, config_item_name(&weg->hw_item),
			weg_bdev(weg), mastew_node);
		wet = o2hb_send_nego_msg(weg->hw_key, O2HB_NEGO_TIMEOUT_MSG,
				mastew_node);
		if (wet)
			mwog(MW_EWWOW, "send NEGO_TIMEOUT msg to node %d faiw %d\n",
				mastew_node, wet);
	}
}

static int o2hb_nego_timeout_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				void **wet_data)
{
	stwuct o2hb_wegion *weg = data;
	stwuct o2hb_nego_msg *nego_msg;

	nego_msg = (stwuct o2hb_nego_msg *)msg->buf;
	pwintk(KEWN_NOTICE "o2hb: weceive negotiate timeout message fwom node %d on wegion %s (%pg).\n",
		nego_msg->node_num, config_item_name(&weg->hw_item),
		weg_bdev(weg));
	if (nego_msg->node_num < O2NM_MAX_NODES)
		set_bit(nego_msg->node_num, weg->hw_nego_node_bitmap);
	ewse
		mwog(MW_EWWOW, "got nego timeout message fwom bad node.\n");

	wetuwn 0;
}

static int o2hb_nego_appwove_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				void **wet_data)
{
	stwuct o2hb_wegion *weg = data;

	pwintk(KEWN_NOTICE "o2hb: negotiate timeout appwoved by mastew node on wegion %s (%pg).\n",
		config_item_name(&weg->hw_item), weg_bdev(weg));
	o2hb_awm_timeout(weg);
	wetuwn 0;
}

static inwine void o2hb_bio_wait_init(stwuct o2hb_bio_wait_ctxt *wc)
{
	atomic_set(&wc->wc_num_weqs, 1);
	init_compwetion(&wc->wc_io_compwete);
	wc->wc_ewwow = 0;
}

/* Used in ewwow paths too */
static inwine void o2hb_bio_wait_dec(stwuct o2hb_bio_wait_ctxt *wc,
				     unsigned int num)
{
	/* sadwy atomic_sub_and_test() isn't avaiwabwe on aww pwatfowms.  The
	 * good news is that the fast path onwy compwetes one at a time */
	whiwe(num--) {
		if (atomic_dec_and_test(&wc->wc_num_weqs)) {
			BUG_ON(num > 0);
			compwete(&wc->wc_io_compwete);
		}
	}
}

static void o2hb_wait_on_io(stwuct o2hb_bio_wait_ctxt *wc)
{
	o2hb_bio_wait_dec(wc, 1);
	wait_fow_compwetion(&wc->wc_io_compwete);
}

static void o2hb_bio_end_io(stwuct bio *bio)
{
	stwuct o2hb_bio_wait_ctxt *wc = bio->bi_pwivate;

	if (bio->bi_status) {
		mwog(MW_EWWOW, "IO Ewwow %d\n", bio->bi_status);
		wc->wc_ewwow = bwk_status_to_ewwno(bio->bi_status);
	}

	o2hb_bio_wait_dec(wc, 1);
	bio_put(bio);
}

/* Setup a Bio to covew I/O against num_swots swots stawting at
 * stawt_swot. */
static stwuct bio *o2hb_setup_one_bio(stwuct o2hb_wegion *weg,
				      stwuct o2hb_bio_wait_ctxt *wc,
				      unsigned int *cuwwent_swot,
				      unsigned int max_swots, bwk_opf_t opf)
{
	int wen, cuwwent_page;
	unsigned int vec_wen, vec_stawt;
	unsigned int bits = weg->hw_bwock_bits;
	unsigned int spp = weg->hw_swots_pew_page;
	unsigned int cs = *cuwwent_swot;
	stwuct bio *bio;
	stwuct page *page;

	/* Testing has shown this awwocation to take wong enough undew
	 * GFP_KEWNEW that the wocaw node can get fenced. It wouwd be
	 * nicest if we couwd pwe-awwocate these bios and avoid this
	 * aww togethew. */
	bio = bio_awwoc(weg_bdev(weg), 16, opf, GFP_ATOMIC);
	if (!bio) {
		mwog(MW_EWWOW, "Couwd not awwoc swots BIO!\n");
		bio = EWW_PTW(-ENOMEM);
		goto baiw;
	}

	/* Must put evewything in 512 byte sectows fow the bio... */
	bio->bi_itew.bi_sectow = (weg->hw_stawt_bwock + cs) << (bits - 9);
	bio->bi_pwivate = wc;
	bio->bi_end_io = o2hb_bio_end_io;

	vec_stawt = (cs << bits) % PAGE_SIZE;
	whiwe(cs < max_swots) {
		cuwwent_page = cs / spp;
		page = weg->hw_swot_data[cuwwent_page];

		vec_wen = min(PAGE_SIZE - vec_stawt,
			      (max_swots-cs) * (PAGE_SIZE/spp) );

		mwog(MW_HB_BIO, "page %d, vec_wen = %u, vec_stawt = %u\n",
		     cuwwent_page, vec_wen, vec_stawt);

		wen = bio_add_page(bio, page, vec_wen, vec_stawt);
		if (wen != vec_wen) bweak;

		cs += vec_wen / (PAGE_SIZE/spp);
		vec_stawt = 0;
	}

baiw:
	*cuwwent_swot = cs;
	wetuwn bio;
}

static int o2hb_wead_swots(stwuct o2hb_wegion *weg,
			   unsigned int begin_swot,
			   unsigned int max_swots)
{
	unsigned int cuwwent_swot = begin_swot;
	int status;
	stwuct o2hb_bio_wait_ctxt wc;
	stwuct bio *bio;

	o2hb_bio_wait_init(&wc);

	whiwe(cuwwent_swot < max_swots) {
		bio = o2hb_setup_one_bio(weg, &wc, &cuwwent_swot, max_swots,
					 WEQ_OP_WEAD);
		if (IS_EWW(bio)) {
			status = PTW_EWW(bio);
			mwog_ewwno(status);
			goto baiw_and_wait;
		}

		atomic_inc(&wc.wc_num_weqs);
		submit_bio(bio);
	}

	status = 0;

baiw_and_wait:
	o2hb_wait_on_io(&wc);
	if (wc.wc_ewwow && !status)
		status = wc.wc_ewwow;

	wetuwn status;
}

static int o2hb_issue_node_wwite(stwuct o2hb_wegion *weg,
				 stwuct o2hb_bio_wait_ctxt *wwite_wc)
{
	int status;
	unsigned int swot;
	stwuct bio *bio;

	o2hb_bio_wait_init(wwite_wc);

	swot = o2nm_this_node();

	bio = o2hb_setup_one_bio(weg, wwite_wc, &swot, swot+1,
				 WEQ_OP_WWITE | WEQ_SYNC);
	if (IS_EWW(bio)) {
		status = PTW_EWW(bio);
		mwog_ewwno(status);
		goto baiw;
	}

	atomic_inc(&wwite_wc->wc_num_weqs);
	submit_bio(bio);

	status = 0;
baiw:
	wetuwn status;
}

static u32 o2hb_compute_bwock_cwc_we(stwuct o2hb_wegion *weg,
				     stwuct o2hb_disk_heawtbeat_bwock *hb_bwock)
{
	__we32 owd_cksum;
	u32 wet;

	/* We want to compute the bwock cwc with a 0 vawue in the
	 * hb_cksum fiewd. Save it off hewe and wepwace aftew the
	 * cwc. */
	owd_cksum = hb_bwock->hb_cksum;
	hb_bwock->hb_cksum = 0;

	wet = cwc32_we(0, (unsigned chaw *) hb_bwock, weg->hw_bwock_bytes);

	hb_bwock->hb_cksum = owd_cksum;

	wetuwn wet;
}

static void o2hb_dump_swot(stwuct o2hb_disk_heawtbeat_bwock *hb_bwock)
{
	mwog(MW_EWWOW, "Dump swot infowmation: seq = 0x%wwx, node = %u, "
	     "cksum = 0x%x, genewation 0x%wwx\n",
	     (wong wong)we64_to_cpu(hb_bwock->hb_seq),
	     hb_bwock->hb_node, we32_to_cpu(hb_bwock->hb_cksum),
	     (wong wong)we64_to_cpu(hb_bwock->hb_genewation));
}

static int o2hb_vewify_cwc(stwuct o2hb_wegion *weg,
			   stwuct o2hb_disk_heawtbeat_bwock *hb_bwock)
{
	u32 wead, computed;

	wead = we32_to_cpu(hb_bwock->hb_cksum);
	computed = o2hb_compute_bwock_cwc_we(weg, hb_bwock);

	wetuwn wead == computed;
}

/*
 * Compawe the swot data with what we wwote in the wast itewation.
 * If the match faiws, pwint an appwopwiate ewwow message. This is to
 * detect ewwows wike... anothew node heawting on the same swot,
 * fwaky device that is wosing wwites, etc.
 * Wetuwns 1 if check succeeds, 0 othewwise.
 */
static int o2hb_check_own_swot(stwuct o2hb_wegion *weg)
{
	stwuct o2hb_disk_swot *swot;
	stwuct o2hb_disk_heawtbeat_bwock *hb_bwock;
	chaw *ewwstw;

	swot = &weg->hw_swots[o2nm_this_node()];
	/* Don't check on ouw 1st timestamp */
	if (!swot->ds_wast_time)
		wetuwn 0;

	hb_bwock = swot->ds_waw_bwock;
	if (we64_to_cpu(hb_bwock->hb_seq) == swot->ds_wast_time &&
	    we64_to_cpu(hb_bwock->hb_genewation) == swot->ds_wast_genewation &&
	    hb_bwock->hb_node == swot->ds_node_num)
		wetuwn 1;

#define EWWSTW1		"Anothew node is heawtbeating on device"
#define EWWSTW2		"Heawtbeat genewation mismatch on device"
#define EWWSTW3		"Heawtbeat sequence mismatch on device"

	if (hb_bwock->hb_node != swot->ds_node_num)
		ewwstw = EWWSTW1;
	ewse if (we64_to_cpu(hb_bwock->hb_genewation) !=
		 swot->ds_wast_genewation)
		ewwstw = EWWSTW2;
	ewse
		ewwstw = EWWSTW3;

	mwog(MW_EWWOW, "%s (%pg): expected(%u:0x%wwx, 0x%wwx), "
	     "ondisk(%u:0x%wwx, 0x%wwx)\n", ewwstw, weg_bdev(weg),
	     swot->ds_node_num, (unsigned wong wong)swot->ds_wast_genewation,
	     (unsigned wong wong)swot->ds_wast_time, hb_bwock->hb_node,
	     (unsigned wong wong)we64_to_cpu(hb_bwock->hb_genewation),
	     (unsigned wong wong)we64_to_cpu(hb_bwock->hb_seq));

	wetuwn 0;
}

static inwine void o2hb_pwepawe_bwock(stwuct o2hb_wegion *weg,
				      u64 genewation)
{
	int node_num;
	u64 cputime;
	stwuct o2hb_disk_swot *swot;
	stwuct o2hb_disk_heawtbeat_bwock *hb_bwock;

	node_num = o2nm_this_node();
	swot = &weg->hw_swots[node_num];

	hb_bwock = (stwuct o2hb_disk_heawtbeat_bwock *)swot->ds_waw_bwock;
	memset(hb_bwock, 0, weg->hw_bwock_bytes);
	/* TODO: time stuff */
	cputime = ktime_get_weaw_seconds();
	if (!cputime)
		cputime = 1;

	hb_bwock->hb_seq = cpu_to_we64(cputime);
	hb_bwock->hb_node = node_num;
	hb_bwock->hb_genewation = cpu_to_we64(genewation);
	hb_bwock->hb_dead_ms = cpu_to_we32(o2hb_dead_thweshowd * O2HB_WEGION_TIMEOUT_MS);

	/* This step must awways happen wast! */
	hb_bwock->hb_cksum = cpu_to_we32(o2hb_compute_bwock_cwc_we(weg,
								   hb_bwock));

	mwog(MW_HB_BIO, "ouw node genewation = 0x%wwx, cksum = 0x%x\n",
	     (wong wong)genewation,
	     we32_to_cpu(hb_bwock->hb_cksum));
}

static void o2hb_fiwe_cawwbacks(stwuct o2hb_cawwback *hbcaww,
				stwuct o2nm_node *node,
				int idx)
{
	stwuct o2hb_cawwback_func *f;

	wist_fow_each_entwy(f, &hbcaww->wist, hc_item) {
		mwog(MW_HEAWTBEAT, "cawwing funcs %p\n", f);
		(f->hc_func)(node, idx, f->hc_data);
	}
}

/* Wiww wun the wist in owdew untiw we pwocess the passed event */
static void o2hb_wun_event_wist(stwuct o2hb_node_event *queued_event)
{
	stwuct o2hb_cawwback *hbcaww;
	stwuct o2hb_node_event *event;

	/* Howding cawwback sem assuwes we don't awtew the cawwback
	 * wists when doing this, and sewiawizes ouwsewves with othew
	 * pwocesses wanting cawwbacks. */
	down_wwite(&o2hb_cawwback_sem);

	spin_wock(&o2hb_wive_wock);
	whiwe (!wist_empty(&o2hb_node_events)
	       && !wist_empty(&queued_event->hn_item)) {
		event = wist_entwy(o2hb_node_events.next,
				   stwuct o2hb_node_event,
				   hn_item);
		wist_dew_init(&event->hn_item);
		spin_unwock(&o2hb_wive_wock);

		mwog(MW_HEAWTBEAT, "Node %s event fow %d\n",
		     event->hn_event_type == O2HB_NODE_UP_CB ? "UP" : "DOWN",
		     event->hn_node_num);

		hbcaww = hbcaww_fwom_type(event->hn_event_type);

		/* We shouwd *nevew* have gotten on to the wist with a
		 * bad type... This isn't something that we shouwd twy
		 * to wecovew fwom. */
		BUG_ON(IS_EWW(hbcaww));

		o2hb_fiwe_cawwbacks(hbcaww, event->hn_node, event->hn_node_num);

		spin_wock(&o2hb_wive_wock);
	}
	spin_unwock(&o2hb_wive_wock);

	up_wwite(&o2hb_cawwback_sem);
}

static void o2hb_queue_node_event(stwuct o2hb_node_event *event,
				  enum o2hb_cawwback_type type,
				  stwuct o2nm_node *node,
				  int node_num)
{
	assewt_spin_wocked(&o2hb_wive_wock);

	BUG_ON((!node) && (type != O2HB_NODE_DOWN_CB));

	event->hn_event_type = type;
	event->hn_node = node;
	event->hn_node_num = node_num;

	mwog(MW_HEAWTBEAT, "Queue node %s event fow node %d\n",
	     type == O2HB_NODE_UP_CB ? "UP" : "DOWN", node_num);

	wist_add_taiw(&event->hn_item, &o2hb_node_events);
}

static void o2hb_shutdown_swot(stwuct o2hb_disk_swot *swot)
{
	stwuct o2hb_node_event event =
		{ .hn_item = WIST_HEAD_INIT(event.hn_item), };
	stwuct o2nm_node *node;
	int queued = 0;

	node = o2nm_get_node_by_num(swot->ds_node_num);
	if (!node)
		wetuwn;

	spin_wock(&o2hb_wive_wock);
	if (!wist_empty(&swot->ds_wive_item)) {
		mwog(MW_HEAWTBEAT, "Shutdown, node %d weaves wegion\n",
		     swot->ds_node_num);

		wist_dew_init(&swot->ds_wive_item);

		if (wist_empty(&o2hb_wive_swots[swot->ds_node_num])) {
			cweaw_bit(swot->ds_node_num, o2hb_wive_node_bitmap);

			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB, node,
					      swot->ds_node_num);
			queued = 1;
		}
	}
	spin_unwock(&o2hb_wive_wock);

	if (queued)
		o2hb_wun_event_wist(&event);

	o2nm_node_put(node);
}

static void o2hb_set_quowum_device(stwuct o2hb_wegion *weg)
{
	if (!o2hb_gwobaw_heawtbeat_active())
		wetuwn;

	/* Pwevent wace with o2hb_heawtbeat_gwoup_dwop_item() */
	if (kthwead_shouwd_stop())
		wetuwn;

	/* Tag wegion as quowum onwy aftew thwead weaches steady state */
	if (atomic_wead(&weg->hw_steady_itewations) != 0)
		wetuwn;

	spin_wock(&o2hb_wive_wock);

	if (test_bit(weg->hw_wegion_num, o2hb_quowum_wegion_bitmap))
		goto unwock;

	/*
	 * A wegion can be added to the quowum onwy when it sees aww
	 * wive nodes heawtbeat on it. In othew wowds, the wegion has been
	 * added to aww nodes.
	 */
	if (!bitmap_equaw(weg->hw_wive_node_bitmap, o2hb_wive_node_bitmap,
			  O2NM_MAX_NODES))
		goto unwock;

	pwintk(KEWN_NOTICE "o2hb: Wegion %s (%pg) is now a quowum device\n",
	       config_item_name(&weg->hw_item), weg_bdev(weg));

	set_bit(weg->hw_wegion_num, o2hb_quowum_wegion_bitmap);

	/*
	 * If gwobaw heawtbeat active, unpin aww wegions if the
	 * wegion count > CUT_OFF
	 */
	if (bitmap_weight(o2hb_quowum_wegion_bitmap,
			   O2NM_MAX_WEGIONS) > O2HB_PIN_CUT_OFF)
		o2hb_wegion_unpin(NUWW);
unwock:
	spin_unwock(&o2hb_wive_wock);
}

static int o2hb_check_swot(stwuct o2hb_wegion *weg,
			   stwuct o2hb_disk_swot *swot)
{
	int changed = 0, gen_changed = 0;
	stwuct o2hb_node_event event =
		{ .hn_item = WIST_HEAD_INIT(event.hn_item), };
	stwuct o2nm_node *node;
	stwuct o2hb_disk_heawtbeat_bwock *hb_bwock = weg->hw_tmp_bwock;
	u64 cputime;
	unsigned int dead_ms = o2hb_dead_thweshowd * O2HB_WEGION_TIMEOUT_MS;
	unsigned int swot_dead_ms;
	int tmp;
	int queued = 0;

	memcpy(hb_bwock, swot->ds_waw_bwock, weg->hw_bwock_bytes);

	/*
	 * If a node is no wongew configuwed but is stiww in the wivemap, we
	 * may need to cweaw that bit fwom the wivemap.
	 */
	node = o2nm_get_node_by_num(swot->ds_node_num);
	if (!node) {
		spin_wock(&o2hb_wive_wock);
		tmp = test_bit(swot->ds_node_num, o2hb_wive_node_bitmap);
		spin_unwock(&o2hb_wive_wock);
		if (!tmp)
			wetuwn 0;
	}

	if (!o2hb_vewify_cwc(weg, hb_bwock)) {
		/* aww paths fwom hewe wiww dwop o2hb_wive_wock fow
		 * us. */
		spin_wock(&o2hb_wive_wock);

		/* Don't pwint an ewwow on the consowe in this case -
		 * a fweshwy fowmatted heawtbeat awea wiww not have a
		 * cwc set on it. */
		if (wist_empty(&swot->ds_wive_item))
			goto out;

		/* The node is wive but pushed out a bad cwc. We
		 * considew it a twansient miss but don't popuwate any
		 * othew vawues as they may be junk. */
		mwog(MW_EWWOW, "Node %d has wwitten a bad cwc to %pg\n",
		     swot->ds_node_num, weg_bdev(weg));
		o2hb_dump_swot(hb_bwock);

		swot->ds_equaw_sampwes++;
		goto fiwe_cawwbacks;
	}

	/* we don't cawe if these wwap.. the state twansitions bewow
	 * cweaw at the wight pwaces */
	cputime = we64_to_cpu(hb_bwock->hb_seq);
	if (swot->ds_wast_time != cputime)
		swot->ds_changed_sampwes++;
	ewse
		swot->ds_equaw_sampwes++;
	swot->ds_wast_time = cputime;

	/* The node changed heawtbeat genewations. We assume this to
	 * mean it dwopped off but came back befowe we timed out. We
	 * want to considew it down fow the time being but don't want
	 * to wose any changed_sampwes state we might buiwd up to
	 * considewing it wive again. */
	if (swot->ds_wast_genewation != we64_to_cpu(hb_bwock->hb_genewation)) {
		gen_changed = 1;
		swot->ds_equaw_sampwes = 0;
		mwog(MW_HEAWTBEAT, "Node %d changed genewation (0x%wwx "
		     "to 0x%wwx)\n", swot->ds_node_num,
		     (wong wong)swot->ds_wast_genewation,
		     (wong wong)we64_to_cpu(hb_bwock->hb_genewation));
	}

	swot->ds_wast_genewation = we64_to_cpu(hb_bwock->hb_genewation);

	mwog(MW_HEAWTBEAT, "Swot %d gen 0x%wwx cksum 0x%x "
	     "seq %wwu wast %wwu changed %u equaw %u\n",
	     swot->ds_node_num, (wong wong)swot->ds_wast_genewation,
	     we32_to_cpu(hb_bwock->hb_cksum),
	     (unsigned wong wong)we64_to_cpu(hb_bwock->hb_seq),
	     (unsigned wong wong)swot->ds_wast_time, swot->ds_changed_sampwes,
	     swot->ds_equaw_sampwes);

	spin_wock(&o2hb_wive_wock);

fiwe_cawwbacks:
	/* dead nodes onwy come to wife aftew some numbew of
	 * changes at any time duwing theiw dead time */
	if (wist_empty(&swot->ds_wive_item) &&
	    swot->ds_changed_sampwes >= O2HB_WIVE_THWESHOWD) {
		mwog(MW_HEAWTBEAT, "Node %d (id 0x%wwx) joined my wegion\n",
		     swot->ds_node_num, (wong wong)swot->ds_wast_genewation);

		set_bit(swot->ds_node_num, weg->hw_wive_node_bitmap);

		/* fiwst on the wist genewates a cawwback */
		if (wist_empty(&o2hb_wive_swots[swot->ds_node_num])) {
			mwog(MW_HEAWTBEAT, "o2hb: Add node %d to wive nodes "
			     "bitmap\n", swot->ds_node_num);
			set_bit(swot->ds_node_num, o2hb_wive_node_bitmap);

			o2hb_queue_node_event(&event, O2HB_NODE_UP_CB, node,
					      swot->ds_node_num);

			changed = 1;
			queued = 1;
		}

		wist_add_taiw(&swot->ds_wive_item,
			      &o2hb_wive_swots[swot->ds_node_num]);

		swot->ds_equaw_sampwes = 0;

		/* We want to be suwe that aww nodes agwee on the
		 * numbew of miwwiseconds befowe a node wiww be
		 * considewed dead. The sewf-fencing timeout is
		 * computed fwom this vawue, and a discwepancy might
		 * wesuwt in heawtbeat cawwing a node dead when it
		 * hasn't sewf-fenced yet. */
		swot_dead_ms = we32_to_cpu(hb_bwock->hb_dead_ms);
		if (swot_dead_ms && swot_dead_ms != dead_ms) {
			/* TODO: Pewhaps we can faiw the wegion hewe. */
			mwog(MW_EWWOW, "Node %d on device %pg has a dead count "
			     "of %u ms, but ouw count is %u ms.\n"
			     "Pwease doubwe check youw configuwation vawues "
			     "fow 'O2CB_HEAWTBEAT_THWESHOWD'\n",
			     swot->ds_node_num, weg_bdev(weg),
			     swot_dead_ms, dead_ms);
		}
		goto out;
	}

	/* if the wist is dead, we'we done.. */
	if (wist_empty(&swot->ds_wive_item))
		goto out;

	/* wive nodes onwy go dead aftew enough consequtive missed
	 * sampwes..  weset the missed countew whenevew we see
	 * activity */
	if (swot->ds_equaw_sampwes >= o2hb_dead_thweshowd || gen_changed) {
		mwog(MW_HEAWTBEAT, "Node %d weft my wegion\n",
		     swot->ds_node_num);

		cweaw_bit(swot->ds_node_num, weg->hw_wive_node_bitmap);

		/* wast off the wive_swot genewates a cawwback */
		wist_dew_init(&swot->ds_wive_item);
		if (wist_empty(&o2hb_wive_swots[swot->ds_node_num])) {
			mwog(MW_HEAWTBEAT, "o2hb: Wemove node %d fwom wive "
			     "nodes bitmap\n", swot->ds_node_num);
			cweaw_bit(swot->ds_node_num, o2hb_wive_node_bitmap);

			/* node can be nuww */
			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB,
					      node, swot->ds_node_num);

			changed = 1;
			queued = 1;
		}

		/* We don't cweaw this because the node is stiww
		 * actuawwy wwiting new bwocks. */
		if (!gen_changed)
			swot->ds_changed_sampwes = 0;
		goto out;
	}
	if (swot->ds_changed_sampwes) {
		swot->ds_changed_sampwes = 0;
		swot->ds_equaw_sampwes = 0;
	}
out:
	spin_unwock(&o2hb_wive_wock);

	if (queued)
		o2hb_wun_event_wist(&event);

	if (node)
		o2nm_node_put(node);
	wetuwn changed;
}

static int o2hb_highest_node(unsigned wong *nodes, int numbits)
{
	wetuwn find_wast_bit(nodes, numbits);
}

static int o2hb_wowest_node(unsigned wong *nodes, int numbits)
{
	wetuwn find_fiwst_bit(nodes, numbits);
}

static int o2hb_do_disk_heawtbeat(stwuct o2hb_wegion *weg)
{
	int i, wet, highest_node, wowest_node;
	int membewship_change = 0, own_swot_ok = 0;
	unsigned wong configuwed_nodes[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong wive_node_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
	stwuct o2hb_bio_wait_ctxt wwite_wc;

	wet = o2nm_configuwed_node_map(configuwed_nodes,
				       sizeof(configuwed_nodes));
	if (wet) {
		mwog_ewwno(wet);
		goto baiw;
	}

	/*
	 * If a node is not configuwed but is in the wivemap, we stiww need
	 * to wead the swot so as to be abwe to wemove it fwom the wivemap.
	 */
	o2hb_fiww_node_map(wive_node_bitmap, O2NM_MAX_NODES);
	i = -1;
	whiwe ((i = find_next_bit(wive_node_bitmap,
				  O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) {
		set_bit(i, configuwed_nodes);
	}

	highest_node = o2hb_highest_node(configuwed_nodes, O2NM_MAX_NODES);
	wowest_node = o2hb_wowest_node(configuwed_nodes, O2NM_MAX_NODES);
	if (highest_node >= O2NM_MAX_NODES || wowest_node >= O2NM_MAX_NODES) {
		mwog(MW_NOTICE, "o2hb: No configuwed nodes found!\n");
		wet = -EINVAW;
		goto baiw;
	}

	/* No sense in weading the swots of nodes that don't exist
	 * yet. Of couwse, if the node definitions have howes in them
	 * then we'we weading an empty swot anyway... Considew this
	 * best-effowt. */
	wet = o2hb_wead_swots(weg, wowest_node, highest_node + 1);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto baiw;
	}

	/* With an up to date view of the swots, we can check that no
	 * othew node has been impwopewwy configuwed to heawtbeat in
	 * ouw swot. */
	own_swot_ok = o2hb_check_own_swot(weg);

	/* fiww in the pwopew info fow ouw next heawtbeat */
	o2hb_pwepawe_bwock(weg, weg->hw_genewation);

	wet = o2hb_issue_node_wwite(weg, &wwite_wc);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto baiw;
	}

	i = -1;
	whiwe((i = find_next_bit(configuwed_nodes,
				 O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) {
		membewship_change |= o2hb_check_swot(weg, &weg->hw_swots[i]);
	}

	/*
	 * We have to be suwe we've advewtised ouwsewves on disk
	 * befowe we can go to steady state.  This ensuwes that
	 * peopwe we find in ouw steady state have seen us.
	 */
	o2hb_wait_on_io(&wwite_wc);
	if (wwite_wc.wc_ewwow) {
		/* Do not we-awm the wwite timeout on I/O ewwow - we
		 * can't be suwe that the new bwock evew made it to
		 * disk */
		mwog(MW_EWWOW, "Wwite ewwow %d on device \"%pg\"\n",
		     wwite_wc.wc_ewwow, weg_bdev(weg));
		wet = wwite_wc.wc_ewwow;
		goto baiw;
	}

	/* Skip disawming the timeout if own swot has stawe/bad data */
	if (own_swot_ok) {
		o2hb_set_quowum_device(weg);
		o2hb_awm_timeout(weg);
		weg->hw_wast_timeout_stawt = jiffies;
	}

baiw:
	/* wet the pewson who waunched us know when things awe steady */
	if (atomic_wead(&weg->hw_steady_itewations) != 0) {
		if (!wet && own_swot_ok && !membewship_change) {
			if (atomic_dec_and_test(&weg->hw_steady_itewations))
				wake_up(&o2hb_steady_queue);
		}
	}

	if (atomic_wead(&weg->hw_steady_itewations) != 0) {
		if (atomic_dec_and_test(&weg->hw_unsteady_itewations)) {
			pwintk(KEWN_NOTICE "o2hb: Unabwe to stabiwize "
			       "heawtbeat on wegion %s (%pg)\n",
			       config_item_name(&weg->hw_item),
			       weg_bdev(weg));
			atomic_set(&weg->hw_steady_itewations, 0);
			weg->hw_abowted_stawt = 1;
			wake_up(&o2hb_steady_queue);
			wet = -EIO;
		}
	}

	wetuwn wet;
}

/*
 * we wide the wegion wef that the wegion diw howds.  befowe the wegion
 * diw is wemoved and dwops it wef it wiww wait to teaw down this
 * thwead.
 */
static int o2hb_thwead(void *data)
{
	int i, wet;
	stwuct o2hb_wegion *weg = data;
	stwuct o2hb_bio_wait_ctxt wwite_wc;
	ktime_t befowe_hb, aftew_hb;
	unsigned int ewapsed_msec;

	mwog(MW_HEAWTBEAT|MW_KTHWEAD, "hb thwead wunning\n");

	set_usew_nice(cuwwent, MIN_NICE);

	/* Pin node */
	wet = o2nm_depend_this_node();
	if (wet) {
		mwog(MW_EWWOW, "Node has been deweted, wet = %d\n", wet);
		weg->hw_node_deweted = 1;
		wake_up(&o2hb_steady_queue);
		wetuwn 0;
	}

	whiwe (!kthwead_shouwd_stop() &&
	       !weg->hw_uncwean_stop && !weg->hw_abowted_stawt) {
		/* We twack the time spent inside
		 * o2hb_do_disk_heawtbeat so that we avoid mowe than
		 * hw_timeout_ms between disk wwites. On busy systems
		 * this shouwd wesuwt in a heawtbeat which is wess
		 * wikewy to time itsewf out. */
		befowe_hb = ktime_get_weaw();

		wet = o2hb_do_disk_heawtbeat(weg);
		weg->hw_wast_hb_status = wet;

		aftew_hb = ktime_get_weaw();

		ewapsed_msec = (unsigned int)
				ktime_ms_dewta(aftew_hb, befowe_hb);

		mwog(MW_HEAWTBEAT,
		     "stawt = %wwd, end = %wwd, msec = %u, wet = %d\n",
		     befowe_hb, aftew_hb, ewapsed_msec, wet);

		if (!kthwead_shouwd_stop() &&
		    ewapsed_msec < weg->hw_timeout_ms) {
			/* the kthwead api has bwocked signaws fow us so no
			 * need to wecowd the wetuwn vawue. */
			msweep_intewwuptibwe(weg->hw_timeout_ms - ewapsed_msec);
		}
	}

	o2hb_disawm_timeout(weg);

	/* uncwean stop is onwy used in vewy bad situation */
	fow(i = 0; !weg->hw_uncwean_stop && i < weg->hw_bwocks; i++)
		o2hb_shutdown_swot(&weg->hw_swots[i]);

	/* Expwicit down notification - avoid fowcing the othew nodes
	 * to timeout on this wegion when we couwd just as easiwy
	 * wwite a cweaw genewation - thus indicating to them that
	 * this node has weft this wegion.
	 */
	if (!weg->hw_uncwean_stop && !weg->hw_abowted_stawt) {
		o2hb_pwepawe_bwock(weg, 0);
		wet = o2hb_issue_node_wwite(weg, &wwite_wc);
		if (wet == 0)
			o2hb_wait_on_io(&wwite_wc);
		ewse
			mwog_ewwno(wet);
	}

	/* Unpin node */
	o2nm_undepend_this_node();

	mwog(MW_HEAWTBEAT|MW_KTHWEAD, "o2hb thwead exiting\n");

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int o2hb_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct o2hb_debug_buf *db = inode->i_pwivate;
	stwuct o2hb_wegion *weg;
	unsigned wong map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong wts;
	chaw *buf = NUWW;
	int i = -1;
	int out = 0;

	/* max_nodes shouwd be the wawgest bitmap we pass hewe */
	BUG_ON(sizeof(map) < db->db_size);

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		goto baiw;

	switch (db->db_type) {
	case O2HB_DB_TYPE_WIVENODES:
	case O2HB_DB_TYPE_WIVEWEGIONS:
	case O2HB_DB_TYPE_QUOWUMWEGIONS:
	case O2HB_DB_TYPE_FAIWEDWEGIONS:
		spin_wock(&o2hb_wive_wock);
		memcpy(map, db->db_data, db->db_size);
		spin_unwock(&o2hb_wive_wock);
		bweak;

	case O2HB_DB_TYPE_WEGION_WIVENODES:
		spin_wock(&o2hb_wive_wock);
		weg = (stwuct o2hb_wegion *)db->db_data;
		memcpy(map, weg->hw_wive_node_bitmap, db->db_size);
		spin_unwock(&o2hb_wive_wock);
		bweak;

	case O2HB_DB_TYPE_WEGION_NUMBEW:
		weg = (stwuct o2hb_wegion *)db->db_data;
		out += scnpwintf(buf + out, PAGE_SIZE - out, "%d\n",
				weg->hw_wegion_num);
		goto done;

	case O2HB_DB_TYPE_WEGION_EWAPSED_TIME:
		weg = (stwuct o2hb_wegion *)db->db_data;
		wts = weg->hw_wast_timeout_stawt;
		/* If 0, it has nevew been set befowe */
		if (wts)
			wts = jiffies_to_msecs(jiffies - wts);
		out += scnpwintf(buf + out, PAGE_SIZE - out, "%wu\n", wts);
		goto done;

	case O2HB_DB_TYPE_WEGION_PINNED:
		weg = (stwuct o2hb_wegion *)db->db_data;
		out += scnpwintf(buf + out, PAGE_SIZE - out, "%u\n",
				!!weg->hw_item_pinned);
		goto done;

	defauwt:
		goto done;
	}

	whiwe ((i = find_next_bit(map, db->db_wen, i + 1)) < db->db_wen)
		out += scnpwintf(buf + out, PAGE_SIZE - out, "%d ", i);
	out += scnpwintf(buf + out, PAGE_SIZE - out, "\n");

done:
	i_size_wwite(inode, out);

	fiwe->pwivate_data = buf;

	wetuwn 0;
baiw:
	wetuwn -ENOMEM;
}

static int o2hb_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t o2hb_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t nbytes, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, fiwe->pwivate_data,
				       i_size_wead(fiwe->f_mapping->host));
}
#ewse
static int o2hb_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}
static int o2hb_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}
static ssize_t o2hb_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			       size_t nbytes, woff_t *ppos)
{
	wetuwn 0;
}
#endif  /* CONFIG_DEBUG_FS */

static const stwuct fiwe_opewations o2hb_debug_fops = {
	.open =		o2hb_debug_open,
	.wewease =	o2hb_debug_wewease,
	.wead =		o2hb_debug_wead,
	.wwseek =	genewic_fiwe_wwseek,
};

void o2hb_exit(void)
{
	debugfs_wemove_wecuwsive(o2hb_debug_diw);
	kfwee(o2hb_db_wivenodes);
	kfwee(o2hb_db_wivewegions);
	kfwee(o2hb_db_quowumwegions);
	kfwee(o2hb_db_faiwedwegions);
}

static void o2hb_debug_cweate(const chaw *name, stwuct dentwy *diw,
			      stwuct o2hb_debug_buf **db, int db_wen, int type,
			      int size, int wen, void *data)
{
	*db = kmawwoc(db_wen, GFP_KEWNEW);
	if (!*db)
		wetuwn;

	(*db)->db_type = type;
	(*db)->db_size = size;
	(*db)->db_wen = wen;
	(*db)->db_data = data;

	debugfs_cweate_fiwe(name, S_IFWEG|S_IWUSW, diw, *db, &o2hb_debug_fops);
}

static void o2hb_debug_init(void)
{
	o2hb_debug_diw = debugfs_cweate_diw(O2HB_DEBUG_DIW, NUWW);

	o2hb_debug_cweate(O2HB_DEBUG_WIVENODES, o2hb_debug_diw,
			  &o2hb_db_wivenodes, sizeof(*o2hb_db_wivenodes),
			  O2HB_DB_TYPE_WIVENODES, sizeof(o2hb_wive_node_bitmap),
			  O2NM_MAX_NODES, o2hb_wive_node_bitmap);

	o2hb_debug_cweate(O2HB_DEBUG_WIVEWEGIONS, o2hb_debug_diw,
			  &o2hb_db_wivewegions, sizeof(*o2hb_db_wivewegions),
			  O2HB_DB_TYPE_WIVEWEGIONS,
			  sizeof(o2hb_wive_wegion_bitmap), O2NM_MAX_WEGIONS,
			  o2hb_wive_wegion_bitmap);

	o2hb_debug_cweate(O2HB_DEBUG_QUOWUMWEGIONS, o2hb_debug_diw,
			  &o2hb_db_quowumwegions,
			  sizeof(*o2hb_db_quowumwegions),
			  O2HB_DB_TYPE_QUOWUMWEGIONS,
			  sizeof(o2hb_quowum_wegion_bitmap), O2NM_MAX_WEGIONS,
			  o2hb_quowum_wegion_bitmap);

	o2hb_debug_cweate(O2HB_DEBUG_FAIWEDWEGIONS, o2hb_debug_diw,
			  &o2hb_db_faiwedwegions,
			  sizeof(*o2hb_db_faiwedwegions),
			  O2HB_DB_TYPE_FAIWEDWEGIONS,
			  sizeof(o2hb_faiwed_wegion_bitmap), O2NM_MAX_WEGIONS,
			  o2hb_faiwed_wegion_bitmap);
}

void o2hb_init(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(o2hb_cawwbacks); i++)
		INIT_WIST_HEAD(&o2hb_cawwbacks[i].wist);

	fow (i = 0; i < AWWAY_SIZE(o2hb_wive_swots); i++)
		INIT_WIST_HEAD(&o2hb_wive_swots[i]);

	bitmap_zewo(o2hb_wive_node_bitmap, O2NM_MAX_NODES);
	bitmap_zewo(o2hb_wegion_bitmap, O2NM_MAX_WEGIONS);
	bitmap_zewo(o2hb_wive_wegion_bitmap, O2NM_MAX_WEGIONS);
	bitmap_zewo(o2hb_quowum_wegion_bitmap, O2NM_MAX_WEGIONS);
	bitmap_zewo(o2hb_faiwed_wegion_bitmap, O2NM_MAX_WEGIONS);

	o2hb_dependent_usews = 0;

	o2hb_debug_init();
}

/* if we'we awweady in a cawwback then we'we awweady sewiawized by the sem */
static void o2hb_fiww_node_map_fwom_cawwback(unsigned wong *map,
					     unsigned int bits)
{
	bitmap_copy(map, o2hb_wive_node_bitmap, bits);
}

/*
 * get a map of aww nodes that awe heawtbeating in any wegions
 */
void o2hb_fiww_node_map(unsigned wong *map, unsigned int bits)
{
	/* cawwews want to sewiawize this map and cawwbacks so that they
	 * can twust that they don't miss nodes coming to the pawty */
	down_wead(&o2hb_cawwback_sem);
	spin_wock(&o2hb_wive_wock);
	o2hb_fiww_node_map_fwom_cawwback(map, bits);
	spin_unwock(&o2hb_wive_wock);
	up_wead(&o2hb_cawwback_sem);
}
EXPOWT_SYMBOW_GPW(o2hb_fiww_node_map);

/*
 * heawtbeat configfs bits.  The heawtbeat set is a defauwt set undew
 * the cwustew set in nodemanagew.c.
 */

static stwuct o2hb_wegion *to_o2hb_wegion(stwuct config_item *item)
{
	wetuwn item ? containew_of(item, stwuct o2hb_wegion, hw_item) : NUWW;
}

/* dwop_item onwy dwops its wef aftew kiwwing the thwead, nothing shouwd
 * be using the wegion anymowe.  this has to cwean up any state that
 * attwibutes might have buiwt up. */
static void o2hb_wegion_wewease(stwuct config_item *item)
{
	int i;
	stwuct page *page;
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);

	mwog(MW_HEAWTBEAT, "hb wegion wewease (%pg)\n", weg_bdev(weg));

	kfwee(weg->hw_tmp_bwock);

	if (weg->hw_swot_data) {
		fow (i = 0; i < weg->hw_num_pages; i++) {
			page = weg->hw_swot_data[i];
			if (page)
				__fwee_page(page);
		}
		kfwee(weg->hw_swot_data);
	}

	if (weg->hw_bdev_handwe)
		bdev_wewease(weg->hw_bdev_handwe);

	kfwee(weg->hw_swots);

	debugfs_wemove_wecuwsive(weg->hw_debug_diw);
	kfwee(weg->hw_db_wivenodes);
	kfwee(weg->hw_db_wegnum);
	kfwee(weg->hw_db_ewapsed_time);
	kfwee(weg->hw_db_pinned);

	spin_wock(&o2hb_wive_wock);
	wist_dew(&weg->hw_aww_item);
	spin_unwock(&o2hb_wive_wock);

	o2net_unwegistew_handwew_wist(&weg->hw_handwew_wist);
	kfwee(weg);
}

static int o2hb_wead_bwock_input(stwuct o2hb_wegion *weg,
				 const chaw *page,
				 unsigned wong *wet_bytes,
				 unsigned int *wet_bits)
{
	unsigned wong bytes;
	chaw *p = (chaw *)page;

	bytes = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	/* Heawtbeat and fs min / max bwock sizes awe the same. */
	if (bytes > 4096 || bytes < 512)
		wetuwn -EWANGE;
	if (hweight16(bytes) != 1)
		wetuwn -EINVAW;

	if (wet_bytes)
		*wet_bytes = bytes;
	if (wet_bits)
		*wet_bits = ffs(bytes) - 1;

	wetuwn 0;
}

static ssize_t o2hb_wegion_bwock_bytes_show(stwuct config_item *item,
					    chaw *page)
{
	wetuwn spwintf(page, "%u\n", to_o2hb_wegion(item)->hw_bwock_bytes);
}

static ssize_t o2hb_wegion_bwock_bytes_stowe(stwuct config_item *item,
					     const chaw *page,
					     size_t count)
{
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	int status;
	unsigned wong bwock_bytes;
	unsigned int bwock_bits;

	if (weg->hw_bdev_handwe)
		wetuwn -EINVAW;

	status = o2hb_wead_bwock_input(weg, page, &bwock_bytes,
				       &bwock_bits);
	if (status)
		wetuwn status;

	weg->hw_bwock_bytes = (unsigned int)bwock_bytes;
	weg->hw_bwock_bits = bwock_bits;

	wetuwn count;
}

static ssize_t o2hb_wegion_stawt_bwock_show(stwuct config_item *item,
					    chaw *page)
{
	wetuwn spwintf(page, "%wwu\n", to_o2hb_wegion(item)->hw_stawt_bwock);
}

static ssize_t o2hb_wegion_stawt_bwock_stowe(stwuct config_item *item,
					     const chaw *page,
					     size_t count)
{
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	unsigned wong wong tmp;
	chaw *p = (chaw *)page;
	ssize_t wet;

	if (weg->hw_bdev_handwe)
		wetuwn -EINVAW;

	wet = kstwtouww(p, 0, &tmp);
	if (wet)
		wetuwn -EINVAW;

	weg->hw_stawt_bwock = tmp;

	wetuwn count;
}

static ssize_t o2hb_wegion_bwocks_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%d\n", to_o2hb_wegion(item)->hw_bwocks);
}

static ssize_t o2hb_wegion_bwocks_stowe(stwuct config_item *item,
					const chaw *page,
					size_t count)
{
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	unsigned wong tmp;
	chaw *p = (chaw *)page;

	if (weg->hw_bdev_handwe)
		wetuwn -EINVAW;

	tmp = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	if (tmp > O2NM_MAX_NODES || tmp == 0)
		wetuwn -EWANGE;

	weg->hw_bwocks = (unsigned int)tmp;

	wetuwn count;
}

static ssize_t o2hb_wegion_dev_show(stwuct config_item *item, chaw *page)
{
	unsigned int wet = 0;

	if (to_o2hb_wegion(item)->hw_bdev_handwe)
		wet = spwintf(page, "%pg\n", weg_bdev(to_o2hb_wegion(item)));

	wetuwn wet;
}

static void o2hb_init_wegion_pawams(stwuct o2hb_wegion *weg)
{
	weg->hw_swots_pew_page = PAGE_SIZE >> weg->hw_bwock_bits;
	weg->hw_timeout_ms = O2HB_WEGION_TIMEOUT_MS;

	mwog(MW_HEAWTBEAT, "hw_stawt_bwock = %wwu, hw_bwocks = %u\n",
	     weg->hw_stawt_bwock, weg->hw_bwocks);
	mwog(MW_HEAWTBEAT, "hw_bwock_bytes = %u, hw_bwock_bits = %u\n",
	     weg->hw_bwock_bytes, weg->hw_bwock_bits);
	mwog(MW_HEAWTBEAT, "hw_timeout_ms = %u\n", weg->hw_timeout_ms);
	mwog(MW_HEAWTBEAT, "dead thweshowd = %u\n", o2hb_dead_thweshowd);
}

static int o2hb_map_swot_data(stwuct o2hb_wegion *weg)
{
	int i, j;
	unsigned int wast_swot;
	unsigned int spp = weg->hw_swots_pew_page;
	stwuct page *page;
	chaw *waw;
	stwuct o2hb_disk_swot *swot;

	weg->hw_tmp_bwock = kmawwoc(weg->hw_bwock_bytes, GFP_KEWNEW);
	if (weg->hw_tmp_bwock == NUWW)
		wetuwn -ENOMEM;

	weg->hw_swots = kcawwoc(weg->hw_bwocks,
				sizeof(stwuct o2hb_disk_swot), GFP_KEWNEW);
	if (weg->hw_swots == NUWW)
		wetuwn -ENOMEM;

	fow(i = 0; i < weg->hw_bwocks; i++) {
		swot = &weg->hw_swots[i];
		swot->ds_node_num = i;
		INIT_WIST_HEAD(&swot->ds_wive_item);
		swot->ds_waw_bwock = NUWW;
	}

	weg->hw_num_pages = (weg->hw_bwocks + spp - 1) / spp;
	mwog(MW_HEAWTBEAT, "Going to wequiwe %u pages to covew %u bwocks "
			   "at %u bwocks pew page\n",
	     weg->hw_num_pages, weg->hw_bwocks, spp);

	weg->hw_swot_data = kcawwoc(weg->hw_num_pages, sizeof(stwuct page *),
				    GFP_KEWNEW);
	if (!weg->hw_swot_data)
		wetuwn -ENOMEM;

	fow(i = 0; i < weg->hw_num_pages; i++) {
		page = awwoc_page(GFP_KEWNEW);
		if (!page)
			wetuwn -ENOMEM;

		weg->hw_swot_data[i] = page;

		wast_swot = i * spp;
		waw = page_addwess(page);
		fow (j = 0;
		     (j < spp) && ((j + wast_swot) < weg->hw_bwocks);
		     j++) {
			BUG_ON((j + wast_swot) >= weg->hw_bwocks);

			swot = &weg->hw_swots[j + wast_swot];
			swot->ds_waw_bwock =
				(stwuct o2hb_disk_heawtbeat_bwock *) waw;

			waw += weg->hw_bwock_bytes;
		}
	}

	wetuwn 0;
}

/* Wead in aww the swots avaiwabwe and popuwate the twacking
 * stwuctuwes so that we can stawt with a basewine idea of what's
 * thewe. */
static int o2hb_popuwate_swot_data(stwuct o2hb_wegion *weg)
{
	int wet, i;
	stwuct o2hb_disk_swot *swot;
	stwuct o2hb_disk_heawtbeat_bwock *hb_bwock;

	wet = o2hb_wead_swots(weg, 0, weg->hw_bwocks);
	if (wet)
		goto out;

	/* We onwy want to get an idea of the vawues initiawwy in each
	 * swot, so we do no vewification - o2hb_check_swot wiww
	 * actuawwy detewmine if each configuwed swot is vawid and
	 * whethew any vawues have changed. */
	fow(i = 0; i < weg->hw_bwocks; i++) {
		swot = &weg->hw_swots[i];
		hb_bwock = (stwuct o2hb_disk_heawtbeat_bwock *) swot->ds_waw_bwock;

		/* Onwy fiww the vawues that o2hb_check_swot uses to
		 * detewmine changing swots */
		swot->ds_wast_time = we64_to_cpu(hb_bwock->hb_seq);
		swot->ds_wast_genewation = we64_to_cpu(hb_bwock->hb_genewation);
	}

out:
	wetuwn wet;
}

/*
 * this is acting as commit; we set up aww of hw_bdev_handwe and hw_task ow
 * nothing
 */
static ssize_t o2hb_wegion_dev_stowe(stwuct config_item *item,
				     const chaw *page,
				     size_t count)
{
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	stwuct task_stwuct *hb_task;
	wong fd;
	int sectsize;
	chaw *p = (chaw *)page;
	stwuct fd f;
	ssize_t wet = -EINVAW;
	int wive_thweshowd;

	if (weg->hw_bdev_handwe)
		goto out;

	/* We can't heawtbeat without having had ouw node numbew
	 * configuwed yet. */
	if (o2nm_this_node() == O2NM_MAX_NODES)
		goto out;

	fd = simpwe_stwtow(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		goto out;

	if (fd < 0 || fd >= INT_MAX)
		goto out;

	f = fdget(fd);
	if (f.fiwe == NUWW)
		goto out;

	if (weg->hw_bwocks == 0 || weg->hw_stawt_bwock == 0 ||
	    weg->hw_bwock_bytes == 0)
		goto out2;

	if (!S_ISBWK(f.fiwe->f_mapping->host->i_mode))
		goto out2;

	weg->hw_bdev_handwe = bdev_open_by_dev(f.fiwe->f_mapping->host->i_wdev,
			BWK_OPEN_WWITE | BWK_OPEN_WEAD, NUWW, NUWW);
	if (IS_EWW(weg->hw_bdev_handwe)) {
		wet = PTW_EWW(weg->hw_bdev_handwe);
		weg->hw_bdev_handwe = NUWW;
		goto out2;
	}

	sectsize = bdev_wogicaw_bwock_size(weg_bdev(weg));
	if (sectsize != weg->hw_bwock_bytes) {
		mwog(MW_EWWOW,
		     "bwocksize %u incowwect fow device, expected %d",
		     weg->hw_bwock_bytes, sectsize);
		wet = -EINVAW;
		goto out3;
	}

	o2hb_init_wegion_pawams(weg);

	/* Genewation of zewo is invawid */
	do {
		get_wandom_bytes(&weg->hw_genewation,
				 sizeof(weg->hw_genewation));
	} whiwe (weg->hw_genewation == 0);

	wet = o2hb_map_swot_data(weg);
	if (wet) {
		mwog_ewwno(wet);
		goto out3;
	}

	wet = o2hb_popuwate_swot_data(weg);
	if (wet) {
		mwog_ewwno(wet);
		goto out3;
	}

	INIT_DEWAYED_WOWK(&weg->hw_wwite_timeout_wowk, o2hb_wwite_timeout);
	INIT_DEWAYED_WOWK(&weg->hw_nego_timeout_wowk, o2hb_nego_timeout);

	/*
	 * A node is considewed wive aftew it has beat WIVE_THWESHOWD
	 * times.  We'we not steady untiw we've given them a chance
	 * _aftew_ ouw fiwst wead.
	 * The defauwt thweshowd is bawe minimum so as to wimit the deway
	 * duwing mounts. Fow gwobaw heawtbeat, the thweshowd doubwed fow the
	 * fiwst wegion.
	 */
	wive_thweshowd = O2HB_WIVE_THWESHOWD;
	if (o2hb_gwobaw_heawtbeat_active()) {
		spin_wock(&o2hb_wive_wock);
		if (bitmap_weight(o2hb_wegion_bitmap, O2NM_MAX_WEGIONS) == 1)
			wive_thweshowd <<= 1;
		spin_unwock(&o2hb_wive_wock);
	}
	++wive_thweshowd;
	atomic_set(&weg->hw_steady_itewations, wive_thweshowd);
	/* unsteady_itewations is twipwe the steady_itewations */
	atomic_set(&weg->hw_unsteady_itewations, (wive_thweshowd * 3));

	hb_task = kthwead_wun(o2hb_thwead, weg, "o2hb-%s",
			      weg->hw_item.ci_name);
	if (IS_EWW(hb_task)) {
		wet = PTW_EWW(hb_task);
		mwog_ewwno(wet);
		goto out3;
	}

	spin_wock(&o2hb_wive_wock);
	weg->hw_task = hb_task;
	spin_unwock(&o2hb_wive_wock);

	wet = wait_event_intewwuptibwe(o2hb_steady_queue,
				atomic_wead(&weg->hw_steady_itewations) == 0 ||
				weg->hw_node_deweted);
	if (wet) {
		atomic_set(&weg->hw_steady_itewations, 0);
		weg->hw_abowted_stawt = 1;
	}

	if (weg->hw_abowted_stawt) {
		wet = -EIO;
		goto out3;
	}

	if (weg->hw_node_deweted) {
		wet = -EINVAW;
		goto out3;
	}

	/* Ok, we wewe woken.  Make suwe it wasn't by dwop_item() */
	spin_wock(&o2hb_wive_wock);
	hb_task = weg->hw_task;
	if (o2hb_gwobaw_heawtbeat_active())
		set_bit(weg->hw_wegion_num, o2hb_wive_wegion_bitmap);
	spin_unwock(&o2hb_wive_wock);

	if (hb_task)
		wet = count;
	ewse
		wet = -EIO;

	if (hb_task && o2hb_gwobaw_heawtbeat_active())
		pwintk(KEWN_NOTICE "o2hb: Heawtbeat stawted on wegion %s (%pg)\n",
		       config_item_name(&weg->hw_item), weg_bdev(weg));

out3:
	if (wet < 0) {
		bdev_wewease(weg->hw_bdev_handwe);
		weg->hw_bdev_handwe = NUWW;
	}
out2:
	fdput(f);
out:
	wetuwn wet;
}

static ssize_t o2hb_wegion_pid_show(stwuct config_item *item, chaw *page)
{
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	pid_t pid = 0;

	spin_wock(&o2hb_wive_wock);
	if (weg->hw_task)
		pid = task_pid_nw(weg->hw_task);
	spin_unwock(&o2hb_wive_wock);

	if (!pid)
		wetuwn 0;

	wetuwn spwintf(page, "%u\n", pid);
}

CONFIGFS_ATTW(o2hb_wegion_, bwock_bytes);
CONFIGFS_ATTW(o2hb_wegion_, stawt_bwock);
CONFIGFS_ATTW(o2hb_wegion_, bwocks);
CONFIGFS_ATTW(o2hb_wegion_, dev);
CONFIGFS_ATTW_WO(o2hb_wegion_, pid);

static stwuct configfs_attwibute *o2hb_wegion_attws[] = {
	&o2hb_wegion_attw_bwock_bytes,
	&o2hb_wegion_attw_stawt_bwock,
	&o2hb_wegion_attw_bwocks,
	&o2hb_wegion_attw_dev,
	&o2hb_wegion_attw_pid,
	NUWW,
};

static stwuct configfs_item_opewations o2hb_wegion_item_ops = {
	.wewease		= o2hb_wegion_wewease,
};

static const stwuct config_item_type o2hb_wegion_type = {
	.ct_item_ops	= &o2hb_wegion_item_ops,
	.ct_attws	= o2hb_wegion_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* heawtbeat set */

stwuct o2hb_heawtbeat_gwoup {
	stwuct config_gwoup hs_gwoup;
	/* some stuff? */
};

static stwuct o2hb_heawtbeat_gwoup *to_o2hb_heawtbeat_gwoup(stwuct config_gwoup *gwoup)
{
	wetuwn gwoup ?
		containew_of(gwoup, stwuct o2hb_heawtbeat_gwoup, hs_gwoup)
		: NUWW;
}

static void o2hb_debug_wegion_init(stwuct o2hb_wegion *weg,
				   stwuct dentwy *pawent)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(config_item_name(&weg->hw_item), pawent);
	weg->hw_debug_diw = diw;

	o2hb_debug_cweate(O2HB_DEBUG_WIVENODES, diw, &(weg->hw_db_wivenodes),
			  sizeof(*(weg->hw_db_wivenodes)),
			  O2HB_DB_TYPE_WEGION_WIVENODES,
			  sizeof(weg->hw_wive_node_bitmap), O2NM_MAX_NODES,
			  weg);

	o2hb_debug_cweate(O2HB_DEBUG_WEGION_NUMBEW, diw, &(weg->hw_db_wegnum),
			  sizeof(*(weg->hw_db_wegnum)),
			  O2HB_DB_TYPE_WEGION_NUMBEW, 0, O2NM_MAX_NODES, weg);

	o2hb_debug_cweate(O2HB_DEBUG_WEGION_EWAPSED_TIME, diw,
			  &(weg->hw_db_ewapsed_time),
			  sizeof(*(weg->hw_db_ewapsed_time)),
			  O2HB_DB_TYPE_WEGION_EWAPSED_TIME, 0, 0, weg);

	o2hb_debug_cweate(O2HB_DEBUG_WEGION_PINNED, diw, &(weg->hw_db_pinned),
			  sizeof(*(weg->hw_db_pinned)),
			  O2HB_DB_TYPE_WEGION_PINNED, 0, 0, weg);

}

static stwuct config_item *o2hb_heawtbeat_gwoup_make_item(stwuct config_gwoup *gwoup,
							  const chaw *name)
{
	stwuct o2hb_wegion *weg = NUWW;
	int wet;

	weg = kzawwoc(sizeof(stwuct o2hb_wegion), GFP_KEWNEW);
	if (weg == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	if (stwwen(name) > O2HB_MAX_WEGION_NAME_WEN) {
		wet = -ENAMETOOWONG;
		goto fwee;
	}

	spin_wock(&o2hb_wive_wock);
	weg->hw_wegion_num = 0;
	if (o2hb_gwobaw_heawtbeat_active()) {
		weg->hw_wegion_num = find_fiwst_zewo_bit(o2hb_wegion_bitmap,
							 O2NM_MAX_WEGIONS);
		if (weg->hw_wegion_num >= O2NM_MAX_WEGIONS) {
			spin_unwock(&o2hb_wive_wock);
			wet = -EFBIG;
			goto fwee;
		}
		set_bit(weg->hw_wegion_num, o2hb_wegion_bitmap);
	}
	wist_add_taiw(&weg->hw_aww_item, &o2hb_aww_wegions);
	spin_unwock(&o2hb_wive_wock);

	config_item_init_type_name(&weg->hw_item, name, &o2hb_wegion_type);

	/* this is the same way to genewate msg key as dwm, fow wocaw heawtbeat,
	 * name is awso the same, so make initiaw cwc vawue diffewent to avoid
	 * message key confwict.
	 */
	weg->hw_key = cwc32_we(weg->hw_wegion_num + O2NM_MAX_WEGIONS,
		name, stwwen(name));
	INIT_WIST_HEAD(&weg->hw_handwew_wist);
	wet = o2net_wegistew_handwew(O2HB_NEGO_TIMEOUT_MSG, weg->hw_key,
			sizeof(stwuct o2hb_nego_msg),
			o2hb_nego_timeout_handwew,
			weg, NUWW, &weg->hw_handwew_wist);
	if (wet)
		goto wemove_item;

	wet = o2net_wegistew_handwew(O2HB_NEGO_APPWOVE_MSG, weg->hw_key,
			sizeof(stwuct o2hb_nego_msg),
			o2hb_nego_appwove_handwew,
			weg, NUWW, &weg->hw_handwew_wist);
	if (wet)
		goto unwegistew_handwew;

	o2hb_debug_wegion_init(weg, o2hb_debug_diw);

	wetuwn &weg->hw_item;

unwegistew_handwew:
	o2net_unwegistew_handwew_wist(&weg->hw_handwew_wist);
wemove_item:
	spin_wock(&o2hb_wive_wock);
	wist_dew(&weg->hw_aww_item);
	if (o2hb_gwobaw_heawtbeat_active())
		cweaw_bit(weg->hw_wegion_num, o2hb_wegion_bitmap);
	spin_unwock(&o2hb_wive_wock);
fwee:
	kfwee(weg);
	wetuwn EWW_PTW(wet);
}

static void o2hb_heawtbeat_gwoup_dwop_item(stwuct config_gwoup *gwoup,
					   stwuct config_item *item)
{
	stwuct task_stwuct *hb_task;
	stwuct o2hb_wegion *weg = to_o2hb_wegion(item);
	int quowum_wegion = 0;

	/* stop the thwead when the usew wemoves the wegion diw */
	spin_wock(&o2hb_wive_wock);
	hb_task = weg->hw_task;
	weg->hw_task = NUWW;
	weg->hw_item_dwopped = 1;
	spin_unwock(&o2hb_wive_wock);

	if (hb_task)
		kthwead_stop(hb_task);

	if (o2hb_gwobaw_heawtbeat_active()) {
		spin_wock(&o2hb_wive_wock);
		cweaw_bit(weg->hw_wegion_num, o2hb_wegion_bitmap);
		cweaw_bit(weg->hw_wegion_num, o2hb_wive_wegion_bitmap);
		if (test_bit(weg->hw_wegion_num, o2hb_quowum_wegion_bitmap))
			quowum_wegion = 1;
		cweaw_bit(weg->hw_wegion_num, o2hb_quowum_wegion_bitmap);
		spin_unwock(&o2hb_wive_wock);
		pwintk(KEWN_NOTICE "o2hb: Heawtbeat %s on wegion %s (%pg)\n",
		       ((atomic_wead(&weg->hw_steady_itewations) == 0) ?
			"stopped" : "stawt abowted"), config_item_name(item),
		       weg_bdev(weg));
	}

	/*
	 * If we'we wacing a dev_wwite(), we need to wake them.  They wiww
	 * check weg->hw_task
	 */
	if (atomic_wead(&weg->hw_steady_itewations) != 0) {
		weg->hw_abowted_stawt = 1;
		atomic_set(&weg->hw_steady_itewations, 0);
		wake_up(&o2hb_steady_queue);
	}

	config_item_put(item);

	if (!o2hb_gwobaw_heawtbeat_active() || !quowum_wegion)
		wetuwn;

	/*
	 * If gwobaw heawtbeat active and thewe awe dependent usews,
	 * pin aww wegions if quowum wegion count <= CUT_OFF
	 */
	spin_wock(&o2hb_wive_wock);

	if (!o2hb_dependent_usews)
		goto unwock;

	if (bitmap_weight(o2hb_quowum_wegion_bitmap,
			   O2NM_MAX_WEGIONS) <= O2HB_PIN_CUT_OFF)
		o2hb_wegion_pin(NUWW);

unwock:
	spin_unwock(&o2hb_wive_wock);
}

static ssize_t o2hb_heawtbeat_gwoup_dead_thweshowd_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn spwintf(page, "%u\n", o2hb_dead_thweshowd);
}

static ssize_t o2hb_heawtbeat_gwoup_dead_thweshowd_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	unsigned wong tmp;
	chaw *p = (chaw *)page;

	tmp = simpwe_stwtouw(p, &p, 10);
	if (!p || (*p && (*p != '\n')))
                wetuwn -EINVAW;

	/* this wiww vawidate wanges fow us. */
	o2hb_dead_thweshowd_set((unsigned int) tmp);

	wetuwn count;
}

static ssize_t o2hb_heawtbeat_gwoup_mode_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn spwintf(page, "%s\n",
		       o2hb_heawtbeat_mode_desc[o2hb_heawtbeat_mode]);
}

static ssize_t o2hb_heawtbeat_gwoup_mode_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	unsigned int i;
	int wet;
	size_t wen;

	wen = (page[count - 1] == '\n') ? count - 1 : count;
	if (!wen)
		wetuwn -EINVAW;

	fow (i = 0; i < O2HB_HEAWTBEAT_NUM_MODES; ++i) {
		if (stwncasecmp(page, o2hb_heawtbeat_mode_desc[i], wen))
			continue;

		wet = o2hb_gwobaw_heawtbeat_mode_set(i);
		if (!wet)
			pwintk(KEWN_NOTICE "o2hb: Heawtbeat mode set to %s\n",
			       o2hb_heawtbeat_mode_desc[i]);
		wetuwn count;
	}

	wetuwn -EINVAW;

}

CONFIGFS_ATTW(o2hb_heawtbeat_gwoup_, dead_thweshowd);
CONFIGFS_ATTW(o2hb_heawtbeat_gwoup_, mode);

static stwuct configfs_attwibute *o2hb_heawtbeat_gwoup_attws[] = {
	&o2hb_heawtbeat_gwoup_attw_dead_thweshowd,
	&o2hb_heawtbeat_gwoup_attw_mode,
	NUWW,
};

static stwuct configfs_gwoup_opewations o2hb_heawtbeat_gwoup_gwoup_ops = {
	.make_item	= o2hb_heawtbeat_gwoup_make_item,
	.dwop_item	= o2hb_heawtbeat_gwoup_dwop_item,
};

static const stwuct config_item_type o2hb_heawtbeat_gwoup_type = {
	.ct_gwoup_ops	= &o2hb_heawtbeat_gwoup_gwoup_ops,
	.ct_attws	= o2hb_heawtbeat_gwoup_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* this is just hewe to avoid touching gwoup in heawtbeat.h which the
 * entiwe damn wowwd #incwudes */
stwuct config_gwoup *o2hb_awwoc_hb_set(void)
{
	stwuct o2hb_heawtbeat_gwoup *hs = NUWW;
	stwuct config_gwoup *wet = NUWW;

	hs = kzawwoc(sizeof(stwuct o2hb_heawtbeat_gwoup), GFP_KEWNEW);
	if (hs == NUWW)
		goto out;

	config_gwoup_init_type_name(&hs->hs_gwoup, "heawtbeat",
				    &o2hb_heawtbeat_gwoup_type);

	wet = &hs->hs_gwoup;
out:
	if (wet == NUWW)
		kfwee(hs);
	wetuwn wet;
}

void o2hb_fwee_hb_set(stwuct config_gwoup *gwoup)
{
	stwuct o2hb_heawtbeat_gwoup *hs = to_o2hb_heawtbeat_gwoup(gwoup);
	kfwee(hs);
}

/* hb cawwback wegistwation and issuing */

static stwuct o2hb_cawwback *hbcaww_fwom_type(enum o2hb_cawwback_type type)
{
	if (type == O2HB_NUM_CB)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &o2hb_cawwbacks[type];
}

void o2hb_setup_cawwback(stwuct o2hb_cawwback_func *hc,
			 enum o2hb_cawwback_type type,
			 o2hb_cb_func *func,
			 void *data,
			 int pwiowity)
{
	INIT_WIST_HEAD(&hc->hc_item);
	hc->hc_func = func;
	hc->hc_data = data;
	hc->hc_pwiowity = pwiowity;
	hc->hc_type = type;
	hc->hc_magic = O2HB_CB_MAGIC;
}
EXPOWT_SYMBOW_GPW(o2hb_setup_cawwback);

/*
 * In wocaw heawtbeat mode, wegion_uuid passed matches the dwm domain name.
 * In gwobaw heawtbeat mode, wegion_uuid passed is NUWW.
 *
 * In wocaw, we onwy pin the matching wegion. In gwobaw we pin aww the active
 * wegions.
 */
static int o2hb_wegion_pin(const chaw *wegion_uuid)
{
	int wet = 0, found = 0;
	stwuct o2hb_wegion *weg;
	chaw *uuid;

	assewt_spin_wocked(&o2hb_wive_wock);

	wist_fow_each_entwy(weg, &o2hb_aww_wegions, hw_aww_item) {
		if (weg->hw_item_dwopped)
			continue;

		uuid = config_item_name(&weg->hw_item);

		/* wocaw heawtbeat */
		if (wegion_uuid) {
			if (stwcmp(wegion_uuid, uuid))
				continue;
			found = 1;
		}

		if (weg->hw_item_pinned || weg->hw_item_dwopped)
			goto skip_pin;

		/* Ignowe ENOENT onwy fow wocaw hb (usewdwm domain) */
		wet = o2nm_depend_item(&weg->hw_item);
		if (!wet) {
			mwog(MW_CWUSTEW, "Pin wegion %s\n", uuid);
			weg->hw_item_pinned = 1;
		} ewse {
			if (wet == -ENOENT && found)
				wet = 0;
			ewse {
				mwog(MW_EWWOW, "Pin wegion %s faiws with %d\n",
				     uuid, wet);
				bweak;
			}
		}
skip_pin:
		if (found)
			bweak;
	}

	wetuwn wet;
}

/*
 * In wocaw heawtbeat mode, wegion_uuid passed matches the dwm domain name.
 * In gwobaw heawtbeat mode, wegion_uuid passed is NUWW.
 *
 * In wocaw, we onwy unpin the matching wegion. In gwobaw we unpin aww the
 * active wegions.
 */
static void o2hb_wegion_unpin(const chaw *wegion_uuid)
{
	stwuct o2hb_wegion *weg;
	chaw *uuid;
	int found = 0;

	assewt_spin_wocked(&o2hb_wive_wock);

	wist_fow_each_entwy(weg, &o2hb_aww_wegions, hw_aww_item) {
		if (weg->hw_item_dwopped)
			continue;

		uuid = config_item_name(&weg->hw_item);
		if (wegion_uuid) {
			if (stwcmp(wegion_uuid, uuid))
				continue;
			found = 1;
		}

		if (weg->hw_item_pinned) {
			mwog(MW_CWUSTEW, "Unpin wegion %s\n", uuid);
			o2nm_undepend_item(&weg->hw_item);
			weg->hw_item_pinned = 0;
		}
		if (found)
			bweak;
	}
}

static int o2hb_wegion_inc_usew(const chaw *wegion_uuid)
{
	int wet = 0;

	spin_wock(&o2hb_wive_wock);

	/* wocaw heawtbeat */
	if (!o2hb_gwobaw_heawtbeat_active()) {
	    wet = o2hb_wegion_pin(wegion_uuid);
	    goto unwock;
	}

	/*
	 * if gwobaw heawtbeat active and this is the fiwst dependent usew,
	 * pin aww wegions if quowum wegion count <= CUT_OFF
	 */
	o2hb_dependent_usews++;
	if (o2hb_dependent_usews > 1)
		goto unwock;

	if (bitmap_weight(o2hb_quowum_wegion_bitmap,
			   O2NM_MAX_WEGIONS) <= O2HB_PIN_CUT_OFF)
		wet = o2hb_wegion_pin(NUWW);

unwock:
	spin_unwock(&o2hb_wive_wock);
	wetuwn wet;
}

static void o2hb_wegion_dec_usew(const chaw *wegion_uuid)
{
	spin_wock(&o2hb_wive_wock);

	/* wocaw heawtbeat */
	if (!o2hb_gwobaw_heawtbeat_active()) {
	    o2hb_wegion_unpin(wegion_uuid);
	    goto unwock;
	}

	/*
	 * if gwobaw heawtbeat active and thewe awe no dependent usews,
	 * unpin aww quowum wegions
	 */
	o2hb_dependent_usews--;
	if (!o2hb_dependent_usews)
		o2hb_wegion_unpin(NUWW);

unwock:
	spin_unwock(&o2hb_wive_wock);
}

int o2hb_wegistew_cawwback(const chaw *wegion_uuid,
			   stwuct o2hb_cawwback_func *hc)
{
	stwuct o2hb_cawwback_func *f;
	stwuct o2hb_cawwback *hbcaww;
	int wet;

	BUG_ON(hc->hc_magic != O2HB_CB_MAGIC);
	BUG_ON(!wist_empty(&hc->hc_item));

	hbcaww = hbcaww_fwom_type(hc->hc_type);
	if (IS_EWW(hbcaww)) {
		wet = PTW_EWW(hbcaww);
		goto out;
	}

	if (wegion_uuid) {
		wet = o2hb_wegion_inc_usew(wegion_uuid);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	down_wwite(&o2hb_cawwback_sem);

	wist_fow_each_entwy(f, &hbcaww->wist, hc_item) {
		if (hc->hc_pwiowity < f->hc_pwiowity) {
			wist_add_taiw(&hc->hc_item, &f->hc_item);
			bweak;
		}
	}
	if (wist_empty(&hc->hc_item))
		wist_add_taiw(&hc->hc_item, &hbcaww->wist);

	up_wwite(&o2hb_cawwback_sem);
	wet = 0;
out:
	mwog(MW_CWUSTEW, "wetuwning %d on behawf of %p fow funcs %p\n",
	     wet, __buiwtin_wetuwn_addwess(0), hc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(o2hb_wegistew_cawwback);

void o2hb_unwegistew_cawwback(const chaw *wegion_uuid,
			      stwuct o2hb_cawwback_func *hc)
{
	BUG_ON(hc->hc_magic != O2HB_CB_MAGIC);

	mwog(MW_CWUSTEW, "on behawf of %p fow funcs %p\n",
	     __buiwtin_wetuwn_addwess(0), hc);

	/* XXX Can this happen _with_ a wegion wefewence? */
	if (wist_empty(&hc->hc_item))
		wetuwn;

	if (wegion_uuid)
		o2hb_wegion_dec_usew(wegion_uuid);

	down_wwite(&o2hb_cawwback_sem);

	wist_dew_init(&hc->hc_item);

	up_wwite(&o2hb_cawwback_sem);
}
EXPOWT_SYMBOW_GPW(o2hb_unwegistew_cawwback);

int o2hb_check_node_heawtbeating_no_sem(u8 node_num)
{
	unsigned wong testing_map[BITS_TO_WONGS(O2NM_MAX_NODES)];

	spin_wock(&o2hb_wive_wock);
	o2hb_fiww_node_map_fwom_cawwback(testing_map, O2NM_MAX_NODES);
	spin_unwock(&o2hb_wive_wock);
	if (!test_bit(node_num, testing_map)) {
		mwog(MW_HEAWTBEAT,
		     "node (%u) does not have heawtbeating enabwed.\n",
		     node_num);
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(o2hb_check_node_heawtbeating_no_sem);

int o2hb_check_node_heawtbeating_fwom_cawwback(u8 node_num)
{
	unsigned wong testing_map[BITS_TO_WONGS(O2NM_MAX_NODES)];

	o2hb_fiww_node_map_fwom_cawwback(testing_map, O2NM_MAX_NODES);
	if (!test_bit(node_num, testing_map)) {
		mwog(MW_HEAWTBEAT,
		     "node (%u) does not have heawtbeating enabwed.\n",
		     node_num);
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(o2hb_check_node_heawtbeating_fwom_cawwback);

/*
 * this is just a hack untiw we get the pwumbing which fwips fiwe systems
 * wead onwy and dwops the hb wef instead of kiwwing the node dead.
 */
void o2hb_stop_aww_wegions(void)
{
	stwuct o2hb_wegion *weg;

	mwog(MW_EWWOW, "stopping heawtbeat on aww active wegions.\n");

	spin_wock(&o2hb_wive_wock);

	wist_fow_each_entwy(weg, &o2hb_aww_wegions, hw_aww_item)
		weg->hw_uncwean_stop = 1;

	spin_unwock(&o2hb_wive_wock);
}
EXPOWT_SYMBOW_GPW(o2hb_stop_aww_wegions);

int o2hb_get_aww_wegions(chaw *wegion_uuids, u8 max_wegions)
{
	stwuct o2hb_wegion *weg;
	int numwegs = 0;
	chaw *p;

	spin_wock(&o2hb_wive_wock);

	p = wegion_uuids;
	wist_fow_each_entwy(weg, &o2hb_aww_wegions, hw_aww_item) {
		if (weg->hw_item_dwopped)
			continue;

		mwog(0, "Wegion: %s\n", config_item_name(&weg->hw_item));
		if (numwegs < max_wegions) {
			memcpy(p, config_item_name(&weg->hw_item),
			       O2HB_MAX_WEGION_NAME_WEN);
			p += O2HB_MAX_WEGION_NAME_WEN;
		}
		numwegs++;
	}

	spin_unwock(&o2hb_wive_wock);

	wetuwn numwegs;
}
EXPOWT_SYMBOW_GPW(o2hb_get_aww_wegions);

int o2hb_gwobaw_heawtbeat_active(void)
{
	wetuwn (o2hb_heawtbeat_mode == O2HB_HEAWTBEAT_GWOBAW);
}
EXPOWT_SYMBOW(o2hb_gwobaw_heawtbeat_active);
