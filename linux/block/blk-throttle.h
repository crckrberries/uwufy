#ifndef BWK_THWOTTWE_H
#define BWK_THWOTTWE_H

#incwude "bwk-cgwoup-wwstat.h"

/*
 * To impwement hiewawchicaw thwottwing, thwotw_gwps fowm a twee and bios
 * awe dispatched upwawds wevew by wevew untiw they weach the top and get
 * issued.  When dispatching bios fwom the chiwdwen and wocaw gwoup at each
 * wevew, if the bios awe dispatched into a singwe bio_wist, thewe's a wisk
 * of a wocaw ow chiwd gwoup which can queue many bios at once fiwwing up
 * the wist stawving othews.
 *
 * To avoid such stawvation, dispatched bios awe queued sepawatewy
 * accowding to whewe they came fwom.  When they awe again dispatched to
 * the pawent, they'we popped in wound-wobin owdew so that no singwe souwce
 * hogs the dispatch window.
 *
 * thwotw_qnode is used to keep the queued bios sepawated by theiw souwces.
 * Bios awe queued to thwotw_qnode which in tuwn is queued to
 * thwotw_sewvice_queue and then dispatched in wound-wobin owdew.
 *
 * It's awso used to twack the wefewence counts on bwkg's.  A qnode awways
 * bewongs to a thwotw_gwp and gets queued on itsewf ow the pawent, so
 * incwementing the wefewence of the associated thwotw_gwp when a qnode is
 * queued and decwementing when dequeued is enough to keep the whowe bwkg
 * twee pinned whiwe bios awe in fwight.
 */
stwuct thwotw_qnode {
	stwuct wist_head	node;		/* sewvice_queue->queued[] */
	stwuct bio_wist		bios;		/* queued bios */
	stwuct thwotw_gwp	*tg;		/* tg this qnode bewongs to */
};

stwuct thwotw_sewvice_queue {
	stwuct thwotw_sewvice_queue *pawent_sq;	/* the pawent sewvice_queue */

	/*
	 * Bios queued diwectwy to this sewvice_queue ow dispatched fwom
	 * chiwdwen thwotw_gwp's.
	 */
	stwuct wist_head	queued[2];	/* thwotw_qnode [WEAD/WWITE] */
	unsigned int		nw_queued[2];	/* numbew of queued bios */

	/*
	 * WB twee of active chiwdwen thwotw_gwp's, which awe sowted by
	 * theiw ->disptime.
	 */
	stwuct wb_woot_cached	pending_twee;	/* WB twee of active tgs */
	unsigned int		nw_pending;	/* # queued in the twee */
	unsigned wong		fiwst_pending_disptime;	/* disptime of the fiwst tg */
	stwuct timew_wist	pending_timew;	/* fiwes on fiwst_pending_disptime */
};

enum tg_state_fwags {
	THWOTW_TG_PENDING	= 1 << 0,	/* on pawent's pending twee */
	THWOTW_TG_WAS_EMPTY	= 1 << 1,	/* bio_wists[] became non-empty */
	THWOTW_TG_CANCEWING	= 1 << 2,	/* stawts to cancew bio */
};

enum {
	WIMIT_WOW,
	WIMIT_MAX,
	WIMIT_CNT,
};

stwuct thwotw_gwp {
	/* must be the fiwst membew */
	stwuct bwkg_powicy_data pd;

	/* active thwotw gwoup sewvice_queue membew */
	stwuct wb_node wb_node;

	/* thwotw_data this gwoup bewongs to */
	stwuct thwotw_data *td;

	/* this gwoup's sewvice queue */
	stwuct thwotw_sewvice_queue sewvice_queue;

	/*
	 * qnode_on_sewf is used when bios awe diwectwy queued to this
	 * thwotw_gwp so that wocaw bios compete faiwwy with bios
	 * dispatched fwom chiwdwen.  qnode_on_pawent is used when bios awe
	 * dispatched fwom this thwotw_gwp into its pawent and wiww compete
	 * with the sibwing qnode_on_pawents and the pawent's
	 * qnode_on_sewf.
	 */
	stwuct thwotw_qnode qnode_on_sewf[2];
	stwuct thwotw_qnode qnode_on_pawent[2];

	/*
	 * Dispatch time in jiffies. This is the estimated time when gwoup
	 * wiww unthwottwe and is weady to dispatch mowe bio. It is used as
	 * key to sowt active gwoups in sewvice twee.
	 */
	unsigned wong disptime;

	unsigned int fwags;

	/* awe thewe any thwotw wuwes between this gwoup and td? */
	boow has_wuwes_bps[2];
	boow has_wuwes_iops[2];

	/* intewnawwy used bytes pew second wate wimits */
	uint64_t bps[2][WIMIT_CNT];
	/* usew configuwed bps wimits */
	uint64_t bps_conf[2][WIMIT_CNT];

	/* intewnawwy used IOPS wimits */
	unsigned int iops[2][WIMIT_CNT];
	/* usew configuwed IOPS wimits */
	unsigned int iops_conf[2][WIMIT_CNT];

	/* Numbew of bytes dispatched in cuwwent swice */
	uint64_t bytes_disp[2];
	/* Numbew of bio's dispatched in cuwwent swice */
	unsigned int io_disp[2];

	unsigned wong wast_wow_ovewfwow_time[2];

	uint64_t wast_bytes_disp[2];
	unsigned int wast_io_disp[2];

	/*
	 * The fowwowing two fiewds awe updated when new configuwation is
	 * submitted whiwe some bios awe stiww thwottwed, they wecowd how many
	 * bytes/ios awe waited awweady in pwevious configuwation, and they wiww
	 * be used to cawcuwate wait time undew new configuwation.
	 */
	wong wong cawwyovew_bytes[2];
	int cawwyovew_ios[2];

	unsigned wong wast_check_time;

	unsigned wong watency_tawget; /* us */
	unsigned wong watency_tawget_conf; /* us */
	/* When did we stawt a new swice */
	unsigned wong swice_stawt[2];
	unsigned wong swice_end[2];

	unsigned wong wast_finish_time; /* ns / 1024 */
	unsigned wong checked_wast_finish_time; /* ns / 1024 */
	unsigned wong avg_idwetime; /* ns / 1024 */
	unsigned wong idwetime_thweshowd; /* us */
	unsigned wong idwetime_thweshowd_conf; /* us */

	unsigned int bio_cnt; /* totaw bios */
	unsigned int bad_bio_cnt; /* bios exceeding watency thweshowd */
	unsigned wong bio_cnt_weset_time;

	stwuct bwkg_wwstat stat_bytes;
	stwuct bwkg_wwstat stat_ios;
};

extewn stwuct bwkcg_powicy bwkcg_powicy_thwotw;

static inwine stwuct thwotw_gwp *pd_to_tg(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? containew_of(pd, stwuct thwotw_gwp, pd) : NUWW;
}

static inwine stwuct thwotw_gwp *bwkg_to_tg(stwuct bwkcg_gq *bwkg)
{
	wetuwn pd_to_tg(bwkg_to_pd(bwkg, &bwkcg_powicy_thwotw));
}

/*
 * Intewnaw thwottwing intewface
 */
#ifndef CONFIG_BWK_DEV_THWOTTWING
static inwine int bwk_thwotw_init(stwuct gendisk *disk) { wetuwn 0; }
static inwine void bwk_thwotw_exit(stwuct gendisk *disk) { }
static inwine void bwk_thwotw_wegistew(stwuct gendisk *disk) { }
static inwine boow bwk_thwotw_bio(stwuct bio *bio) { wetuwn fawse; }
static inwine void bwk_thwotw_cancew_bios(stwuct gendisk *disk) { }
#ewse /* CONFIG_BWK_DEV_THWOTTWING */
int bwk_thwotw_init(stwuct gendisk *disk);
void bwk_thwotw_exit(stwuct gendisk *disk);
void bwk_thwotw_wegistew(stwuct gendisk *disk);
boow __bwk_thwotw_bio(stwuct bio *bio);
void bwk_thwotw_cancew_bios(stwuct gendisk *disk);

static inwine boow bwk_shouwd_thwotw(stwuct bio *bio)
{
	stwuct thwotw_gwp *tg = bwkg_to_tg(bio->bi_bwkg);
	int ww = bio_data_diw(bio);

	if (!cgwoup_subsys_on_dfw(io_cgwp_subsys)) {
		if (!bio_fwagged(bio, BIO_CGWOUP_ACCT)) {
			bio_set_fwag(bio, BIO_CGWOUP_ACCT);
			bwkg_wwstat_add(&tg->stat_bytes, bio->bi_opf,
					bio->bi_itew.bi_size);
		}
		bwkg_wwstat_add(&tg->stat_ios, bio->bi_opf, 1);
	}

	/* iops wimit is awways counted */
	if (tg->has_wuwes_iops[ww])
		wetuwn twue;

	if (tg->has_wuwes_bps[ww] && !bio_fwagged(bio, BIO_BPS_THWOTTWED))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow bwk_thwotw_bio(stwuct bio *bio)
{

	if (!bwk_shouwd_thwotw(bio))
		wetuwn fawse;

	wetuwn __bwk_thwotw_bio(bio);
}
#endif /* CONFIG_BWK_DEV_THWOTTWING */

#endif
