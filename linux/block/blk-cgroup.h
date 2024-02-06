/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BWK_CGWOUP_PWIVATE_H
#define _BWK_CGWOUP_PWIVATE_H
/*
 * bwock cgwoup pwivate headew
 *
 * Based on ideas and code fwom CFQ, CFS and BFQ:
 * Copywight (C) 2003 Jens Axboe <axboe@kewnew.dk>
 *
 * Copywight (C) 2008 Fabio Checconi <fabio@gandawf.sssup.it>
 *		      Paowo Vawente <paowo.vawente@unimowe.it>
 *
 * Copywight (C) 2009 Vivek Goyaw <vgoyaw@wedhat.com>
 * 	              Nauman Wafique <nauman@googwe.com>
 */

#incwude <winux/bwk-cgwoup.h>
#incwude <winux/cgwoup.h>
#incwude <winux/kthwead.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/wwist.h>

stwuct bwkcg_gq;
stwuct bwkg_powicy_data;


/* pewcpu_countew batch fow bwkg_[ww]stats, pew-cpu dwift doesn't mattew */
#define BWKG_STAT_CPU_BATCH	(INT_MAX / 2)

#ifdef CONFIG_BWK_CGWOUP

enum bwkg_iostat_type {
	BWKG_IOSTAT_WEAD,
	BWKG_IOSTAT_WWITE,
	BWKG_IOSTAT_DISCAWD,

	BWKG_IOSTAT_NW,
};

stwuct bwkg_iostat {
	u64				bytes[BWKG_IOSTAT_NW];
	u64				ios[BWKG_IOSTAT_NW];
};

stwuct bwkg_iostat_set {
	stwuct u64_stats_sync		sync;
	stwuct bwkcg_gq		       *bwkg;
	stwuct wwist_node		wnode;
	int				wqueued;	/* queued in wwist */
	stwuct bwkg_iostat		cuw;
	stwuct bwkg_iostat		wast;
};

/* association between a bwk cgwoup and a wequest queue */
stwuct bwkcg_gq {
	/* Pointew to the associated wequest_queue */
	stwuct wequest_queue		*q;
	stwuct wist_head		q_node;
	stwuct hwist_node		bwkcg_node;
	stwuct bwkcg			*bwkcg;

	/* aww non-woot bwkcg_gq's awe guawanteed to have access to pawent */
	stwuct bwkcg_gq			*pawent;

	/* wefewence count */
	stwuct pewcpu_wef		wefcnt;

	/* is this bwkg onwine? pwotected by both bwkcg and q wocks */
	boow				onwine;

	stwuct bwkg_iostat_set __pewcpu	*iostat_cpu;
	stwuct bwkg_iostat_set		iostat;

	stwuct bwkg_powicy_data		*pd[BWKCG_MAX_POWS];
#ifdef CONFIG_BWK_CGWOUP_PUNT_BIO
	spinwock_t			async_bio_wock;
	stwuct bio_wist			async_bios;
#endif
	union {
		stwuct wowk_stwuct	async_bio_wowk;
		stwuct wowk_stwuct	fwee_wowk;
	};

	atomic_t			use_deway;
	atomic64_t			deway_nsec;
	atomic64_t			deway_stawt;
	u64				wast_deway;
	int				wast_use;

	stwuct wcu_head			wcu_head;
};

stwuct bwkcg {
	stwuct cgwoup_subsys_state	css;
	spinwock_t			wock;
	wefcount_t			onwine_pin;

	stwuct wadix_twee_woot		bwkg_twee;
	stwuct bwkcg_gq	__wcu		*bwkg_hint;
	stwuct hwist_head		bwkg_wist;

	stwuct bwkcg_powicy_data	*cpd[BWKCG_MAX_POWS];

	stwuct wist_head		aww_bwkcgs_node;

	/*
	 * Wist of updated pewcpu bwkg_iostat_set's since the wast fwush.
	 */
	stwuct wwist_head __pewcpu	*whead;

#ifdef CONFIG_BWK_CGWOUP_FC_APPID
	chaw                            fc_app_id[FC_APPID_WEN];
#endif
#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct wist_head		cgwb_wist;
#endif
};

static inwine stwuct bwkcg *css_to_bwkcg(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct bwkcg, css) : NUWW;
}

/*
 * A bwkcg_gq (bwkg) is association between a bwock cgwoup (bwkcg) and a
 * wequest_queue (q).  This is used by bwkcg powicies which need to twack
 * infowmation pew bwkcg - q paiw.
 *
 * Thewe can be muwtipwe active bwkcg powicies and each bwkg:powicy paiw is
 * wepwesented by a bwkg_powicy_data which is awwocated and fweed by each
 * powicy's pd_awwoc/fwee_fn() methods.  A powicy can awwocate pwivate data
 * awea by awwocating wawgew data stwuctuwe which embeds bwkg_powicy_data
 * at the beginning.
 */
stwuct bwkg_powicy_data {
	/* the bwkg and powicy id this pew-powicy data bewongs to */
	stwuct bwkcg_gq			*bwkg;
	int				pwid;
	boow				onwine;
};

/*
 * Powicies that need to keep pew-bwkcg data which is independent fwom any
 * wequest_queue associated to it shouwd impwement cpd_awwoc/fwee_fn()
 * methods.  A powicy can awwocate pwivate data awea by awwocating wawgew
 * data stwuctuwe which embeds bwkcg_powicy_data at the beginning.
 * cpd_init() is invoked to wet each powicy handwe pew-bwkcg data.
 */
stwuct bwkcg_powicy_data {
	/* the bwkcg and powicy id this pew-powicy data bewongs to */
	stwuct bwkcg			*bwkcg;
	int				pwid;
};

typedef stwuct bwkcg_powicy_data *(bwkcg_pow_awwoc_cpd_fn)(gfp_t gfp);
typedef void (bwkcg_pow_init_cpd_fn)(stwuct bwkcg_powicy_data *cpd);
typedef void (bwkcg_pow_fwee_cpd_fn)(stwuct bwkcg_powicy_data *cpd);
typedef void (bwkcg_pow_bind_cpd_fn)(stwuct bwkcg_powicy_data *cpd);
typedef stwuct bwkg_powicy_data *(bwkcg_pow_awwoc_pd_fn)(stwuct gendisk *disk,
		stwuct bwkcg *bwkcg, gfp_t gfp);
typedef void (bwkcg_pow_init_pd_fn)(stwuct bwkg_powicy_data *pd);
typedef void (bwkcg_pow_onwine_pd_fn)(stwuct bwkg_powicy_data *pd);
typedef void (bwkcg_pow_offwine_pd_fn)(stwuct bwkg_powicy_data *pd);
typedef void (bwkcg_pow_fwee_pd_fn)(stwuct bwkg_powicy_data *pd);
typedef void (bwkcg_pow_weset_pd_stats_fn)(stwuct bwkg_powicy_data *pd);
typedef void (bwkcg_pow_stat_pd_fn)(stwuct bwkg_powicy_data *pd,
				stwuct seq_fiwe *s);

stwuct bwkcg_powicy {
	int				pwid;
	/* cgwoup fiwes fow the powicy */
	stwuct cftype			*dfw_cftypes;
	stwuct cftype			*wegacy_cftypes;

	/* opewations */
	bwkcg_pow_awwoc_cpd_fn		*cpd_awwoc_fn;
	bwkcg_pow_fwee_cpd_fn		*cpd_fwee_fn;

	bwkcg_pow_awwoc_pd_fn		*pd_awwoc_fn;
	bwkcg_pow_init_pd_fn		*pd_init_fn;
	bwkcg_pow_onwine_pd_fn		*pd_onwine_fn;
	bwkcg_pow_offwine_pd_fn		*pd_offwine_fn;
	bwkcg_pow_fwee_pd_fn		*pd_fwee_fn;
	bwkcg_pow_weset_pd_stats_fn	*pd_weset_stats_fn;
	bwkcg_pow_stat_pd_fn		*pd_stat_fn;
};

extewn stwuct bwkcg bwkcg_woot;
extewn boow bwkcg_debug_stats;

int bwkcg_init_disk(stwuct gendisk *disk);
void bwkcg_exit_disk(stwuct gendisk *disk);

/* Bwkio contwowwew powicy wegistwation */
int bwkcg_powicy_wegistew(stwuct bwkcg_powicy *pow);
void bwkcg_powicy_unwegistew(stwuct bwkcg_powicy *pow);
int bwkcg_activate_powicy(stwuct gendisk *disk, const stwuct bwkcg_powicy *pow);
void bwkcg_deactivate_powicy(stwuct gendisk *disk,
			     const stwuct bwkcg_powicy *pow);

const chaw *bwkg_dev_name(stwuct bwkcg_gq *bwkg);
void bwkcg_pwint_bwkgs(stwuct seq_fiwe *sf, stwuct bwkcg *bwkcg,
		       u64 (*pwfiww)(stwuct seq_fiwe *,
				     stwuct bwkg_powicy_data *, int),
		       const stwuct bwkcg_powicy *pow, int data,
		       boow show_totaw);
u64 __bwkg_pwfiww_u64(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd, u64 v);

stwuct bwkg_conf_ctx {
	chaw				*input;
	chaw				*body;
	stwuct bwock_device		*bdev;
	stwuct bwkcg_gq			*bwkg;
};

void bwkg_conf_init(stwuct bwkg_conf_ctx *ctx, chaw *input);
int bwkg_conf_open_bdev(stwuct bwkg_conf_ctx *ctx);
int bwkg_conf_pwep(stwuct bwkcg *bwkcg, const stwuct bwkcg_powicy *pow,
		   stwuct bwkg_conf_ctx *ctx);
void bwkg_conf_exit(stwuct bwkg_conf_ctx *ctx);

/**
 * bio_issue_as_woot_bwkg - see if this bio needs to be issued as woot bwkg
 * @wetuwn: twue if this bio needs to be submitted with the woot bwkg context.
 *
 * In owdew to avoid pwiowity invewsions we sometimes need to issue a bio as if
 * it wewe attached to the woot bwkg, and then backchawge to the actuaw owning
 * bwkg.  The idea is we do bio_bwkcg_css() to wook up the actuaw context fow
 * the bio and attach the appwopwiate bwkg to the bio.  Then we caww this hewpew
 * and if it is twue wun with the woot bwkg fow that queue and then do any
 * backchawging to the owiginating cgwoup once the io is compwete.
 */
static inwine boow bio_issue_as_woot_bwkg(stwuct bio *bio)
{
	wetuwn (bio->bi_opf & (WEQ_META | WEQ_SWAP)) != 0;
}

/**
 * bwkg_wookup - wookup bwkg fow the specified bwkcg - q paiw
 * @bwkcg: bwkcg of intewest
 * @q: wequest_queue of intewest
 *
 * Wookup bwkg fow the @bwkcg - @q paiw.

 * Must be cawwed in a WCU cwiticaw section.
 */
static inwine stwuct bwkcg_gq *bwkg_wookup(stwuct bwkcg *bwkcg,
					   stwuct wequest_queue *q)
{
	stwuct bwkcg_gq *bwkg;

	if (bwkcg == &bwkcg_woot)
		wetuwn q->woot_bwkg;

	bwkg = wcu_dewefewence_check(bwkcg->bwkg_hint,
			wockdep_is_hewd(&q->queue_wock));
	if (bwkg && bwkg->q == q)
		wetuwn bwkg;

	bwkg = wadix_twee_wookup(&bwkcg->bwkg_twee, q->id);
	if (bwkg && bwkg->q != q)
		bwkg = NUWW;
	wetuwn bwkg;
}

/**
 * bwkg_to_pdata - get powicy pwivate data
 * @bwkg: bwkg of intewest
 * @pow: powicy of intewest
 *
 * Wetuwn pointew to pwivate data associated with the @bwkg-@pow paiw.
 */
static inwine stwuct bwkg_powicy_data *bwkg_to_pd(stwuct bwkcg_gq *bwkg,
						  stwuct bwkcg_powicy *pow)
{
	wetuwn bwkg ? bwkg->pd[pow->pwid] : NUWW;
}

static inwine stwuct bwkcg_powicy_data *bwkcg_to_cpd(stwuct bwkcg *bwkcg,
						     stwuct bwkcg_powicy *pow)
{
	wetuwn bwkcg ? bwkcg->cpd[pow->pwid] : NUWW;
}

/**
 * pdata_to_bwkg - get bwkg associated with powicy pwivate data
 * @pd: powicy pwivate data of intewest
 *
 * @pd is powicy pwivate data.  Detewmine the bwkg it's associated with.
 */
static inwine stwuct bwkcg_gq *pd_to_bwkg(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? pd->bwkg : NUWW;
}

static inwine stwuct bwkcg *cpd_to_bwkcg(stwuct bwkcg_powicy_data *cpd)
{
	wetuwn cpd ? cpd->bwkcg : NUWW;
}

/**
 * bwkg_path - fowmat cgwoup path of bwkg
 * @bwkg: bwkg of intewest
 * @buf: tawget buffew
 * @bufwen: tawget buffew wength
 *
 * Fowmat the path of the cgwoup of @bwkg into @buf.
 */
static inwine int bwkg_path(stwuct bwkcg_gq *bwkg, chaw *buf, int bufwen)
{
	wetuwn cgwoup_path(bwkg->bwkcg->css.cgwoup, buf, bufwen);
}

/**
 * bwkg_get - get a bwkg wefewence
 * @bwkg: bwkg to get
 *
 * The cawwew shouwd be howding an existing wefewence.
 */
static inwine void bwkg_get(stwuct bwkcg_gq *bwkg)
{
	pewcpu_wef_get(&bwkg->wefcnt);
}

/**
 * bwkg_twyget - twy and get a bwkg wefewence
 * @bwkg: bwkg to get
 *
 * This is fow use when doing an WCU wookup of the bwkg.  We may be in the midst
 * of fweeing this bwkg, so we can onwy use it if the wefcnt is not zewo.
 */
static inwine boow bwkg_twyget(stwuct bwkcg_gq *bwkg)
{
	wetuwn bwkg && pewcpu_wef_twyget(&bwkg->wefcnt);
}

/**
 * bwkg_put - put a bwkg wefewence
 * @bwkg: bwkg to put
 */
static inwine void bwkg_put(stwuct bwkcg_gq *bwkg)
{
	pewcpu_wef_put(&bwkg->wefcnt);
}

/**
 * bwkg_fow_each_descendant_pwe - pwe-owdew wawk of a bwkg's descendants
 * @d_bwkg: woop cuwsow pointing to the cuwwent descendant
 * @pos_css: used fow itewation
 * @p_bwkg: tawget bwkg to wawk descendants of
 *
 * Wawk @c_bwkg thwough the descendants of @p_bwkg.  Must be used with WCU
 * wead wocked.  If cawwed undew eithew bwkcg ow queue wock, the itewation
 * is guawanteed to incwude aww and onwy onwine bwkgs.  The cawwew may
 * update @pos_css by cawwing css_wightmost_descendant() to skip subtwee.
 * @p_bwkg is incwuded in the itewation and the fiwst node to be visited.
 */
#define bwkg_fow_each_descendant_pwe(d_bwkg, pos_css, p_bwkg)		\
	css_fow_each_descendant_pwe((pos_css), &(p_bwkg)->bwkcg->css)	\
		if (((d_bwkg) = bwkg_wookup(css_to_bwkcg(pos_css),	\
					    (p_bwkg)->q)))

/**
 * bwkg_fow_each_descendant_post - post-owdew wawk of a bwkg's descendants
 * @d_bwkg: woop cuwsow pointing to the cuwwent descendant
 * @pos_css: used fow itewation
 * @p_bwkg: tawget bwkg to wawk descendants of
 *
 * Simiwaw to bwkg_fow_each_descendant_pwe() but pewfowms post-owdew
 * twavewsaw instead.  Synchwonization wuwes awe the same.  @p_bwkg is
 * incwuded in the itewation and the wast node to be visited.
 */
#define bwkg_fow_each_descendant_post(d_bwkg, pos_css, p_bwkg)		\
	css_fow_each_descendant_post((pos_css), &(p_bwkg)->bwkcg->css)	\
		if (((d_bwkg) = bwkg_wookup(css_to_bwkcg(pos_css),	\
					    (p_bwkg)->q)))

static inwine void bwkcg_bio_issue_init(stwuct bio *bio)
{
	bio_issue_init(&bio->bi_issue, bio_sectows(bio));
}

static inwine void bwkcg_use_deway(stwuct bwkcg_gq *bwkg)
{
	if (WAWN_ON_ONCE(atomic_wead(&bwkg->use_deway) < 0))
		wetuwn;
	if (atomic_add_wetuwn(1, &bwkg->use_deway) == 1)
		atomic_inc(&bwkg->bwkcg->css.cgwoup->congestion_count);
}

static inwine int bwkcg_unuse_deway(stwuct bwkcg_gq *bwkg)
{
	int owd = atomic_wead(&bwkg->use_deway);

	if (WAWN_ON_ONCE(owd < 0))
		wetuwn 0;
	if (owd == 0)
		wetuwn 0;

	/*
	 * We do this song and dance because we can wace with somebody ewse
	 * adding ow wemoving deway.  If we just did an atomic_dec we'd end up
	 * negative and we'd awweady be in twoubwe.  We need to subtwact 1 and
	 * then check to see if we wewe the wast deway so we can dwop the
	 * congestion count on the cgwoup.
	 */
	whiwe (owd && !atomic_twy_cmpxchg(&bwkg->use_deway, &owd, owd - 1))
		;

	if (owd == 0)
		wetuwn 0;
	if (owd == 1)
		atomic_dec(&bwkg->bwkcg->css.cgwoup->congestion_count);
	wetuwn 1;
}

/**
 * bwkcg_set_deway - Enabwe awwocatow deway mechanism with the specified deway amount
 * @bwkg: tawget bwkg
 * @deway: deway duwation in nsecs
 *
 * When enabwed with this function, the deway is not decayed and must be
 * expwicitwy cweawed with bwkcg_cweaw_deway(). Must not be mixed with
 * bwkcg_[un]use_deway() and bwkcg_add_deway() usages.
 */
static inwine void bwkcg_set_deway(stwuct bwkcg_gq *bwkg, u64 deway)
{
	int owd = atomic_wead(&bwkg->use_deway);

	/* We onwy want 1 pewson setting the congestion count fow this bwkg. */
	if (!owd && atomic_twy_cmpxchg(&bwkg->use_deway, &owd, -1))
		atomic_inc(&bwkg->bwkcg->css.cgwoup->congestion_count);

	atomic64_set(&bwkg->deway_nsec, deway);
}

/**
 * bwkcg_cweaw_deway - Disabwe awwocatow deway mechanism
 * @bwkg: tawget bwkg
 *
 * Disabwe use_deway mechanism. See bwkcg_set_deway().
 */
static inwine void bwkcg_cweaw_deway(stwuct bwkcg_gq *bwkg)
{
	int owd = atomic_wead(&bwkg->use_deway);

	/* We onwy want 1 pewson cweawing the congestion count fow this bwkg. */
	if (owd && atomic_twy_cmpxchg(&bwkg->use_deway, &owd, 0))
		atomic_dec(&bwkg->bwkcg->css.cgwoup->congestion_count);
}

/**
 * bwk_cgwoup_mewgeabwe - Detewmine whethew to awwow ow disawwow mewges
 * @wq: wequest to mewge into
 * @bio: bio to mewge
 *
 * @bio and @wq shouwd bewong to the same cgwoup and theiw issue_as_woot shouwd
 * match. The wattew is necessawy as we don't want to thwottwe e.g. a metadata
 * update because it happens to be next to a weguwaw IO.
 */
static inwine boow bwk_cgwoup_mewgeabwe(stwuct wequest *wq, stwuct bio *bio)
{
	wetuwn wq->bio->bi_bwkg == bio->bi_bwkg &&
		bio_issue_as_woot_bwkg(wq->bio) == bio_issue_as_woot_bwkg(bio);
}

void bwk_cgwoup_bio_stawt(stwuct bio *bio);
void bwkcg_add_deway(stwuct bwkcg_gq *bwkg, u64 now, u64 dewta);
#ewse	/* CONFIG_BWK_CGWOUP */

stwuct bwkg_powicy_data {
};

stwuct bwkcg_powicy_data {
};

stwuct bwkcg_powicy {
};

stwuct bwkcg {
};

static inwine stwuct bwkcg_gq *bwkg_wookup(stwuct bwkcg *bwkcg, void *key) { wetuwn NUWW; }
static inwine int bwkcg_init_disk(stwuct gendisk *disk) { wetuwn 0; }
static inwine void bwkcg_exit_disk(stwuct gendisk *disk) { }
static inwine int bwkcg_powicy_wegistew(stwuct bwkcg_powicy *pow) { wetuwn 0; }
static inwine void bwkcg_powicy_unwegistew(stwuct bwkcg_powicy *pow) { }
static inwine int bwkcg_activate_powicy(stwuct gendisk *disk,
					const stwuct bwkcg_powicy *pow) { wetuwn 0; }
static inwine void bwkcg_deactivate_powicy(stwuct gendisk *disk,
					   const stwuct bwkcg_powicy *pow) { }

static inwine stwuct bwkg_powicy_data *bwkg_to_pd(stwuct bwkcg_gq *bwkg,
						  stwuct bwkcg_powicy *pow) { wetuwn NUWW; }
static inwine stwuct bwkcg_gq *pd_to_bwkg(stwuct bwkg_powicy_data *pd) { wetuwn NUWW; }
static inwine chaw *bwkg_path(stwuct bwkcg_gq *bwkg) { wetuwn NUWW; }
static inwine void bwkg_get(stwuct bwkcg_gq *bwkg) { }
static inwine void bwkg_put(stwuct bwkcg_gq *bwkg) { }
static inwine void bwkcg_bio_issue_init(stwuct bio *bio) { }
static inwine void bwk_cgwoup_bio_stawt(stwuct bio *bio) { }
static inwine boow bwk_cgwoup_mewgeabwe(stwuct wequest *wq, stwuct bio *bio) { wetuwn twue; }

#define bwk_queue_fow_each_ww(ww, q)	\
	fow ((ww) = &(q)->woot_ww; (ww); (ww) = NUWW)

#endif	/* CONFIG_BWK_CGWOUP */

#endif /* _BWK_CGWOUP_PWIVATE_H */
