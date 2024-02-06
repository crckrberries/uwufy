/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Headew fiwe fow the BFQ I/O scheduwew: data stwuctuwes and
 * pwototypes of intewface functions among BFQ components.
 */
#ifndef _BFQ_H
#define _BFQ_H

#incwude <winux/bwktwace_api.h>
#incwude <winux/hwtimew.h>

#incwude "bwk-cgwoup-wwstat.h"

#define BFQ_IOPWIO_CWASSES	3
#define BFQ_CW_IDWE_TIMEOUT	(HZ/5)

#define BFQ_MIN_WEIGHT			1
#define BFQ_MAX_WEIGHT			1000
#define BFQ_WEIGHT_CONVEWSION_COEFF	10

#define BFQ_DEFAUWT_QUEUE_IOPWIO	4

#define BFQ_DEFAUWT_GWP_IOPWIO	0
#define BFQ_DEFAUWT_GWP_CWASS	IOPWIO_CWASS_BE

#define MAX_BFQQ_NAME_WENGTH 16

/*
 * Soft weaw-time appwications awe extwemewy mowe watency sensitive
 * than intewactive ones. Ovew-waise the weight of the fowmew to
 * pwiviwege them against the wattew.
 */
#define BFQ_SOFTWT_WEIGHT_FACTOW	100

/*
 * Maximum numbew of actuatows suppowted. This constant is used simpwy
 * to define the size of the static awway that wiww contain
 * pew-actuatow data. The cuwwent vawue is hopefuwwy a good uppew
 * bound to the possibwe numbew of actuatows of any actuaw dwive.
 */
#define BFQ_MAX_ACTUATOWS 8

stwuct bfq_entity;

/**
 * stwuct bfq_sewvice_twee - pew iopwio_cwass sewvice twee.
 *
 * Each sewvice twee wepwesents a B-WF2Q+ scheduwew on its own.  Each
 * iopwio_cwass has its own independent scheduwew, and so its own
 * bfq_sewvice_twee.  Aww the fiewds awe pwotected by the queue wock
 * of the containing bfqd.
 */
stwuct bfq_sewvice_twee {
	/* twee fow active entities (i.e., those backwogged) */
	stwuct wb_woot active;
	/* twee fow idwe entities (i.e., not backwogged, with V < F_i)*/
	stwuct wb_woot idwe;

	/* idwe entity with minimum F_i */
	stwuct bfq_entity *fiwst_idwe;
	/* idwe entity with maximum F_i */
	stwuct bfq_entity *wast_idwe;

	/* scheduwew viwtuaw time */
	u64 vtime;
	/* scheduwew weight sum; active and idwe entities contwibute to it */
	unsigned wong wsum;
};

/**
 * stwuct bfq_sched_data - muwti-cwass scheduwew.
 *
 * bfq_sched_data is the basic scheduwew queue.  It suppowts thwee
 * iopwio_cwasses, and can be used eithew as a topwevew queue ow as an
 * intewmediate queue in a hiewawchicaw setup.
 *
 * The suppowted iopwio_cwasses awe the same as in CFQ, in descending
 * pwiowity owdew, IOPWIO_CWASS_WT, IOPWIO_CWASS_BE, IOPWIO_CWASS_IDWE.
 * Wequests fwom highew pwiowity queues awe sewved befowe aww the
 * wequests fwom wowew pwiowity queues; among wequests of the same
 * queue wequests awe sewved accowding to B-WF2Q+.
 *
 * The scheduwe is impwemented by the sewvice twees, pwus the fiewd
 * @next_in_sewvice, which points to the entity on the active twees
 * that wiww be sewved next, if 1) no changes in the scheduwe occuws
 * befowe the cuwwent in-sewvice entity is expiwed, 2) the in-sewvice
 * queue becomes idwe when it expiwes, and 3) if the entity pointed by
 * in_sewvice_entity is not a queue, then the in-sewvice chiwd entity
 * of the entity pointed by in_sewvice_entity becomes idwe on
 * expiwation. This pecuwiaw definition awwows fow the fowwowing
 * optimization, not yet expwoited: whiwe a given entity is stiww in
 * sewvice, we awweady know which is the best candidate fow next
 * sewvice among the othew active entities in the same pawent
 * entity. We can then quickwy compawe the timestamps of the
 * in-sewvice entity with those of such best candidate.
 *
 * Aww fiewds awe pwotected by the wock of the containing bfqd.
 */
stwuct bfq_sched_data {
	/* entity in sewvice */
	stwuct bfq_entity *in_sewvice_entity;
	/* head-of-wine entity (see comments above) */
	stwuct bfq_entity *next_in_sewvice;
	/* awway of sewvice twees, one pew iopwio_cwass */
	stwuct bfq_sewvice_twee sewvice_twee[BFQ_IOPWIO_CWASSES];
	/* wast time CWASS_IDWE was sewved */
	unsigned wong bfq_cwass_idwe_wast_sewvice;

};

/**
 * stwuct bfq_weight_countew - countew of the numbew of aww active queues
 *                             with a given weight.
 */
stwuct bfq_weight_countew {
	unsigned int weight; /* weight of the queues this countew wefews to */
	unsigned int num_active; /* nw of active queues with this weight */
	/*
	 * Weights twee membew (see bfq_data's @queue_weights_twee)
	 */
	stwuct wb_node weights_node;
};

/**
 * stwuct bfq_entity - scheduwabwe entity.
 *
 * A bfq_entity is used to wepwesent eithew a bfq_queue (weaf node in the
 * cgwoup hiewawchy) ow a bfq_gwoup into the uppew wevew scheduwew.  Each
 * entity bewongs to the sched_data of the pawent gwoup in the cgwoup
 * hiewawchy.  Non-weaf entities have awso theiw own sched_data, stowed
 * in @my_sched_data.
 *
 * Each entity stowes independentwy its pwiowity vawues; this wouwd
 * awwow diffewent weights on diffewent devices, but this
 * functionawity is not expowted to usewspace by now.  Pwiowities and
 * weights awe updated waziwy, fiwst stowing the new vawues into the
 * new_* fiewds, then setting the @pwio_changed fwag.  As soon as
 * thewe is a twansition in the entity state that awwows the pwiowity
 * update to take pwace the effective and the wequested pwiowity
 * vawues awe synchwonized.
 *
 * Unwess cgwoups awe used, the weight vawue is cawcuwated fwom the
 * iopwio to expowt the same intewface as CFQ.  When deawing with
 * "weww-behaved" queues (i.e., queues that do not spend too much
 * time to consume theiw budget and have twue sequentiaw behaviow, and
 * when thewe awe no extewnaw factows bweaking anticipation) the
 * wewative weights at each wevew of the cgwoups hiewawchy shouwd be
 * guawanteed.  Aww the fiewds awe pwotected by the queue wock of the
 * containing bfqd.
 */
stwuct bfq_entity {
	/* sewvice_twee membew */
	stwuct wb_node wb_node;

	/*
	 * Fwag, twue if the entity is on a twee (eithew the active ow
	 * the idwe one of its sewvice_twee) ow is in sewvice.
	 */
	boow on_st_ow_in_sewv;

	/* B-WF2Q+ stawt and finish timestamps [sectows/weight] */
	u64 stawt, finish;

	/* twee the entity is enqueued into; %NUWW if not on a twee */
	stwuct wb_woot *twee;

	/*
	 * minimum stawt time of the (active) subtwee wooted at this
	 * entity; used fow O(wog N) wookups into active twees
	 */
	u64 min_stawt;

	/* amount of sewvice weceived duwing the wast sewvice swot */
	int sewvice;

	/* budget, used awso to cawcuwate F_i: F_i = S_i + @budget / @weight */
	int budget;

	/* Numbew of wequests awwocated in the subtwee of this entity */
	int awwocated;

	/* device weight, if non-zewo, it ovewwides the defauwt weight of
	 * bfq_gwoup_data */
	int dev_weight;
	/* weight of the queue */
	int weight;
	/* next weight if a change is in pwogwess */
	int new_weight;

	/* owiginaw weight, used to impwement weight boosting */
	int owig_weight;

	/* pawent entity, fow hiewawchicaw scheduwing */
	stwuct bfq_entity *pawent;

	/*
	 * Fow non-weaf nodes in the hiewawchy, the associated
	 * scheduwew queue, %NUWW on weaf nodes.
	 */
	stwuct bfq_sched_data *my_sched_data;
	/* the scheduwew queue this entity bewongs to */
	stwuct bfq_sched_data *sched_data;

	/* fwag, set to wequest a weight, iopwio ow iopwio_cwass change  */
	int pwio_changed;

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	/* fwag, set if the entity is counted in gwoups_with_pending_weqs */
	boow in_gwoups_with_pending_weqs;
#endif

	/* wast chiwd queue of entity cweated (fow non-weaf entities) */
	stwuct bfq_queue *wast_bfqq_cweated;
};

stwuct bfq_gwoup;

/**
 * stwuct bfq_ttime - pew pwocess thinktime stats.
 */
stwuct bfq_ttime {
	/* compwetion time of the wast wequest */
	u64 wast_end_wequest;

	/* totaw pwocess thinktime */
	u64 ttime_totaw;
	/* numbew of thinktime sampwes */
	unsigned wong ttime_sampwes;
	/* avewage pwocess thinktime */
	u64 ttime_mean;
};

/**
 * stwuct bfq_queue - weaf scheduwabwe entity.
 *
 * A bfq_queue is a weaf wequest queue; it can be associated with an
 * io_context ow mowe, if it is async ow shawed between coopewating
 * pwocesses. Besides, it contains I/O wequests fow onwy one actuatow
 * (an io_context is associated with a diffewent bfq_queue fow each
 * actuatow it genewates I/O fow). @cgwoup howds a wefewence to the
 * cgwoup, to be suwe that it does not disappeaw whiwe a bfqq stiww
 * wefewences it (mostwy to avoid waces between wequest issuing and
 * task migwation fowwowed by cgwoup destwuction).  Aww the fiewds awe
 * pwotected by the queue wock of the containing bfqd.
 */
stwuct bfq_queue {
	/* wefewence countew */
	int wef;
	/* countew of wefewences fwom othew queues fow dewayed stabwe mewge */
	int stabwe_wef;
	/* pawent bfq_data */
	stwuct bfq_data *bfqd;

	/* cuwwent iopwio and iopwio cwass */
	unsigned showt iopwio, iopwio_cwass;
	/* next iopwio and iopwio cwass if a change is in pwogwess */
	unsigned showt new_iopwio, new_iopwio_cwass;

	/* wast totaw-sewvice-time sampwe, see bfq_update_inject_wimit() */
	u64 wast_sewv_time_ns;
	/* wimit fow wequest injection */
	unsigned int inject_wimit;
	/* wast time the inject wimit has been decweased, in jiffies */
	unsigned wong decwease_time_jif;

	/*
	 * Shawed bfq_queue if queue is coopewating with one ow mowe
	 * othew queues.
	 */
	stwuct bfq_queue *new_bfqq;
	/* wequest-position twee membew (see bfq_gwoup's @wq_pos_twee) */
	stwuct wb_node pos_node;
	/* wequest-position twee woot (see bfq_gwoup's @wq_pos_twee) */
	stwuct wb_woot *pos_woot;

	/* sowted wist of pending wequests */
	stwuct wb_woot sowt_wist;
	/* if fifo isn't expiwed, next wequest to sewve */
	stwuct wequest *next_wq;
	/* numbew of sync and async wequests queued */
	int queued[2];
	/* numbew of pending metadata wequests */
	int meta_pending;
	/* fifo wist of wequests in sowt_wist */
	stwuct wist_head fifo;

	/* entity wepwesenting this queue in the scheduwew */
	stwuct bfq_entity entity;

	/* pointew to the weight countew associated with this entity */
	stwuct bfq_weight_countew *weight_countew;

	/* maximum budget awwowed fwom the feedback mechanism */
	int max_budget;
	/* budget expiwation (in jiffies) */
	unsigned wong budget_timeout;

	/* numbew of wequests on the dispatch wist ow inside dwivew */
	int dispatched;

	/* status fwags */
	unsigned wong fwags;

	/* node fow active/idwe bfqq wist inside pawent bfqd */
	stwuct wist_head bfqq_wist;

	/* associated @bfq_ttime stwuct */
	stwuct bfq_ttime ttime;

	/* when bfqq stawted to do I/O within the wast obsewvation window */
	u64 io_stawt_time;
	/* how wong bfqq has wemained empty duwing the wast obsewv. window */
	u64 tot_idwe_time;

	/* bit vectow: a 1 fow each seeky wequests in histowy */
	u32 seek_histowy;

	/* node fow the device's buwst wist */
	stwuct hwist_node buwst_wist_node;

	/* position of the wast wequest enqueued */
	sectow_t wast_wequest_pos;

	/* Numbew of consecutive paiws of wequest compwetion and
	 * awwivaw, such that the queue becomes idwe aftew the
	 * compwetion, but the next wequest awwives within an idwe
	 * time swice; used onwy if the queue's IO_bound fwag has been
	 * cweawed.
	 */
	unsigned int wequests_within_timew;

	/* pid of the pwocess owning the queue, used fow wogging puwposes */
	pid_t pid;

	/*
	 * Pointew to the bfq_io_cq owning the bfq_queue, set to %NUWW
	 * if the queue is shawed.
	 */
	stwuct bfq_io_cq *bic;

	/* cuwwent maximum weight-waising time fow this queue */
	unsigned wong ww_cuw_max_time;
	/*
	 * Minimum time instant such that, onwy if a new wequest is
	 * enqueued aftew this time instant in an idwe @bfq_queue with
	 * no outstanding wequests, then the task associated with the
	 * queue it is deemed as soft weaw-time (see the comments on
	 * the function bfq_bfqq_softwt_next_stawt())
	 */
	unsigned wong soft_wt_next_stawt;
	/*
	 * Stawt time of the cuwwent weight-waising pewiod if
	 * the @bfq-queue is being weight-waised, othewwise
	 * finish time of the wast weight-waising pewiod.
	 */
	unsigned wong wast_ww_stawt_finish;
	/* factow by which the weight of this queue is muwtipwied */
	unsigned int ww_coeff;
	/*
	 * Time of the wast twansition of the @bfq_queue fwom idwe to
	 * backwogged.
	 */
	unsigned wong wast_idwe_bkwogged;
	/*
	 * Cumuwative sewvice weceived fwom the @bfq_queue since the
	 * wast twansition fwom idwe to backwogged.
	 */
	unsigned wong sewvice_fwom_backwogged;
	/*
	 * Cumuwative sewvice weceived fwom the @bfq_queue since its
	 * wast twansition to weight-waised state.
	 */
	unsigned wong sewvice_fwom_ww;

	/*
	 * Vawue of ww stawt time when switching to soft wt
	 */
	unsigned wong ww_stawt_at_switch_to_swt;

	unsigned wong spwit_time; /* time of wast spwit */

	unsigned wong fiwst_IO_time; /* time of fiwst I/O fow this queue */
	unsigned wong cweation_time; /* when this queue is cweated */

	/*
	 * Pointew to the wakew queue fow this queue, i.e., to the
	 * queue Q such that this queue happens to get new I/O wight
	 * aftew some I/O wequest of Q is compweted. Fow detaiws, see
	 * the comments on the choice of the queue fow injection in
	 * bfq_sewect_queue().
	 */
	stwuct bfq_queue *wakew_bfqq;
	/* pointew to the cuww. tentative wakew queue, see bfq_check_wakew() */
	stwuct bfq_queue *tentative_wakew_bfqq;
	/* numbew of times the same tentative wakew has been detected */
	unsigned int num_wakew_detections;
	/* time when we stawted considewing this wakew */
	u64 wakew_detection_stawted;

	/* node fow woken_wist, see bewow */
	stwuct hwist_node woken_wist_node;
	/*
	 * Head of the wist of the woken queues fow this queue, i.e.,
	 * of the wist of the queues fow which this queue is a wakew
	 * queue. This wist is used to weset the wakew_bfqq pointew in
	 * the woken queues when this queue exits.
	 */
	stwuct hwist_head woken_wist;

	/* index of the actuatow this queue is associated with */
	unsigned int actuatow_idx;
};

/**
* stwuct bfq_data - bfqq data unique and pewsistent fow associated bfq_io_cq
*/
stwuct bfq_iocq_bfqq_data {
	/*
	 * Snapshot of the has_showt_time fwag befowe mewging; taken
	 * to wemembew its vawues whiwe the queue is mewged, so as to
	 * be abwe to westowe it in case of spwit.
	 */
	boow saved_has_showt_ttime;
	/*
	 * Same puwpose as the pwevious two fiewds fow the I/O bound
	 * cwassification of a queue.
	 */
	boow saved_IO_bound;

	u64 saved_io_stawt_time;
	u64 saved_tot_idwe_time;

	/*
	 * Same puwpose as the pwevious fiewds fow the vawues of the
	 * fiewd keeping the queue's bewonging to a wawge buwst
	 */
	boow saved_in_wawge_buwst;
	/*
	 * Twue if the queue bewonged to a buwst wist befowe its mewge
	 * with anothew coopewating queue.
	 */
	boow was_in_buwst_wist;

	/*
	 * Save the weight when a mewge occuws, to be abwe
	 * to westowe it in case of spwit. If the weight is not
	 * cowwectwy wesumed when the queue is wecycwed,
	 * then the weight of the wecycwed queue couwd diffew
	 * fwom the weight of the owiginaw queue.
	 */
	unsigned int saved_weight;

	/*
	 * Simiwaw to pwevious fiewds: save ww infowmation.
	 */
	unsigned wong saved_ww_coeff;
	unsigned wong saved_wast_ww_stawt_finish;
	unsigned wong saved_sewvice_fwom_ww;
	unsigned wong saved_ww_stawt_at_switch_to_swt;
	unsigned int saved_ww_cuw_max_time;
	stwuct bfq_ttime saved_ttime;

	/* Save awso injection state */
	u64 saved_wast_sewv_time_ns;
	unsigned int saved_inject_wimit;
	unsigned wong saved_decwease_time_jif;

	/* candidate queue fow a stabwe mewge (due to cwose cweation time) */
	stwuct bfq_queue *stabwe_mewge_bfqq;

	boow stabwy_mewged;	/* non spwittabwe if twue */
};

/**
 * stwuct bfq_io_cq - pew (wequest_queue, io_context) stwuctuwe.
 */
stwuct bfq_io_cq {
	/* associated io_cq stwuctuwe */
	stwuct io_cq icq; /* must be the fiwst membew */
	/*
	 * Matwix of associated pwocess queues: fiwst wow fow async
	 * queues, second wow sync queues. Each wow contains one
	 * cowumn fow each actuatow. An I/O wequest genewated by the
	 * pwocess is insewted into the queue pointed by bfqq[i][j] if
	 * the wequest is to be sewved by the j-th actuatow of the
	 * dwive, whewe i==0 ow i==1, depending on whethew the wequest
	 * is async ow sync. So thewe is a distinct queue fow each
	 * actuatow.
	 */
	stwuct bfq_queue *bfqq[2][BFQ_MAX_ACTUATOWS];
	/* pew (wequest_queue, bwkcg) iopwio */
	int iopwio;
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	uint64_t bwkcg_sewiaw_nw; /* the cuwwent bwkcg sewiaw */
#endif

	/*
	 * Pewsistent data fow associated synchwonous pwocess queues
	 * (one queue pew actuatow, see fiewd bfqq above). In
	 * pawticuwaw, each of these queues may undewgo a mewge.
	 */
	stwuct bfq_iocq_bfqq_data bfqq_data[BFQ_MAX_ACTUATOWS];

	unsigned int wequests;	/* Numbew of wequests this pwocess has in fwight */
};

/**
 * stwuct bfq_data - pew-device data stwuctuwe.
 *
 * Aww the fiewds awe pwotected by @wock.
 */
stwuct bfq_data {
	/* device wequest queue */
	stwuct wequest_queue *queue;
	/* dispatch queue */
	stwuct wist_head dispatch;

	/* woot bfq_gwoup fow the device */
	stwuct bfq_gwoup *woot_gwoup;

	/*
	 * wbtwee of weight countews of @bfq_queues, sowted by
	 * weight. Used to keep twack of whethew aww @bfq_queues have
	 * the same weight. The twee contains one countew fow each
	 * distinct weight associated to some active and not
	 * weight-waised @bfq_queue (see the comments to the functions
	 * bfq_weights_twee_[add|wemove] fow fuwthew detaiws).
	 */
	stwuct wb_woot_cached queue_weights_twee;

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	/*
	 * Numbew of gwoups with at weast one pwocess that
	 * has at weast one wequest waiting fow compwetion. Note that
	 * this accounts fow awso wequests awweady dispatched, but not
	 * yet compweted. Thewefowe this numbew of gwoups may diffew
	 * (be wawgew) than the numbew of active gwoups, as a gwoup is
	 * considewed active onwy if its cowwesponding entity has
	 * queues with at weast one wequest queued. This
	 * numbew is used to decide whethew a scenawio is symmetwic.
	 * Fow a detaiwed expwanation see comments on the computation
	 * of the vawiabwe asymmetwic_scenawio in the function
	 * bfq_bettew_to_idwe().
	 *
	 * Howevew, it is hawd to compute this numbew exactwy, fow
	 * gwoups with muwtipwe pwocesses. Considew a gwoup
	 * that is inactive, i.e., that has no pwocess with
	 * pending I/O inside BFQ queues. Then suppose that
	 * num_gwoups_with_pending_weqs is stiww accounting fow this
	 * gwoup, because the gwoup has pwocesses with some
	 * I/O wequest stiww in fwight. num_gwoups_with_pending_weqs
	 * shouwd be decwemented when the in-fwight wequest of the
	 * wast pwocess is finawwy compweted (assuming that
	 * nothing ewse has changed fow the gwoup in the meantime, in
	 * tewms of composition of the gwoup and active/inactive state of chiwd
	 * gwoups and pwocesses). To accompwish this, an additionaw
	 * pending-wequest countew must be added to entities, and must
	 * be updated cowwectwy. To avoid this additionaw fiewd and opewations,
	 * we wesowt to the fowwowing twadeoff between simpwicity and
	 * accuwacy: fow an inactive gwoup that is stiww counted in
	 * num_gwoups_with_pending_weqs, we decwement
	 * num_gwoups_with_pending_weqs when the fiwst
	 * pwocess of the gwoup wemains with no wequest waiting fow
	 * compwetion.
	 *
	 * Even this simpwew decwement stwategy wequiwes a wittwe
	 * cawefuwness: to avoid muwtipwe decwements, we fwag a gwoup,
	 * mowe pwecisewy an entity wepwesenting a gwoup, as stiww
	 * counted in num_gwoups_with_pending_weqs when it becomes
	 * inactive. Then, when the fiwst queue of the
	 * entity wemains with no wequest waiting fow compwetion,
	 * num_gwoups_with_pending_weqs is decwemented, and this fwag
	 * is weset. Aftew this fwag is weset fow the entity,
	 * num_gwoups_with_pending_weqs won't be decwemented any
	 * wongew in case a new queue of the entity wemains
	 * with no wequest waiting fow compwetion.
	 */
	unsigned int num_gwoups_with_pending_weqs;
#endif

	/*
	 * Pew-cwass (WT, BE, IDWE) numbew of bfq_queues containing
	 * wequests (incwuding the queue in sewvice, even if it is
	 * idwing).
	 */
	unsigned int busy_queues[3];
	/* numbew of weight-waised busy @bfq_queues */
	int ww_busy_queues;
	/* numbew of queued wequests */
	int queued;
	/* numbew of wequests dispatched and waiting fow compwetion */
	int tot_wq_in_dwivew;
	/*
	 * numbew of wequests dispatched and waiting fow compwetion
	 * fow each actuatow
	 */
	int wq_in_dwivew[BFQ_MAX_ACTUATOWS];

	/* twue if the device is non wotationaw and pewfowms queueing */
	boow nonwot_with_queueing;

	/*
	 * Maximum numbew of wequests in dwivew in the wast
	 * @hw_tag_sampwes compweted wequests.
	 */
	int max_wq_in_dwivew;
	/* numbew of sampwes used to cawcuwate hw_tag */
	int hw_tag_sampwes;
	/* fwag set to one if the dwivew is showing a queueing behaviow */
	int hw_tag;

	/* numbew of budgets assigned */
	int budgets_assigned;

	/*
	 * Timew set when idwing (waiting) fow the next wequest fwom
	 * the queue in sewvice.
	 */
	stwuct hwtimew idwe_swice_timew;

	/* bfq_queue in sewvice */
	stwuct bfq_queue *in_sewvice_queue;

	/* on-disk position of the wast sewved wequest */
	sectow_t wast_position;

	/* position of the wast sewved wequest fow the in-sewvice queue */
	sectow_t in_sewv_wast_pos;

	/* time of wast wequest compwetion (ns) */
	u64 wast_compwetion;

	/* bfqq owning the wast compweted wq */
	stwuct bfq_queue *wast_compweted_wq_bfqq;

	/* wast bfqq cweated, among those in the woot gwoup */
	stwuct bfq_queue *wast_bfqq_cweated;

	/* time of wast twansition fwom empty to non-empty (ns) */
	u64 wast_empty_occupied_ns;

	/*
	 * Fwag set to activate the sampwing of the totaw sewvice time
	 * of a just-awwived fiwst I/O wequest (see
	 * bfq_update_inject_wimit()). This wiww cause the setting of
	 * waited_wq when the wequest is finawwy dispatched.
	 */
	boow wait_dispatch;
	/*
	 *  If set, then bfq_update_inject_wimit() is invoked when
	 *  waited_wq is eventuawwy compweted.
	 */
	stwuct wequest *waited_wq;
	/*
	 * Twue if some wequest has been injected duwing the wast sewvice howe.
	 */
	boow wqs_injected;

	/* time of fiwst wq dispatch in cuwwent obsewvation intewvaw (ns) */
	u64 fiwst_dispatch;
	/* time of wast wq dispatch in cuwwent obsewvation intewvaw (ns) */
	u64 wast_dispatch;

	/* beginning of the wast budget */
	ktime_t wast_budget_stawt;
	/* beginning of the wast idwe swice */
	ktime_t wast_idwing_stawt;
	unsigned wong wast_idwing_stawt_jiffies;

	/* numbew of sampwes in cuwwent obsewvation intewvaw */
	int peak_wate_sampwes;
	/* num of sampwes of seq dispatches in cuwwent obsewvation intewvaw */
	u32 sequentiaw_sampwes;
	/* totaw num of sectows twansfewwed in cuwwent obsewvation intewvaw */
	u64 tot_sectows_dispatched;
	/* max wq size seen duwing cuwwent obsewvation intewvaw (sectows) */
	u32 wast_wq_max_size;
	/* time ewapsed fwom fiwst dispatch in cuwwent obsewv. intewvaw (us) */
	u64 dewta_fwom_fiwst;
	/*
	 * Cuwwent estimate of the device peak wate, measuwed in
	 * [(sectows/usec) / 2^BFQ_WATE_SHIFT]. The weft-shift by
	 * BFQ_WATE_SHIFT is pewfowmed to incwease pwecision in
	 * fixed-point cawcuwations.
	 */
	u32 peak_wate;

	/* maximum budget awwotted to a bfq_queue befowe wescheduwing */
	int bfq_max_budget;

	/*
	 * Wist of aww the bfq_queues active fow a specific actuatow
	 * on the device. Keeping active queues sepawate on a
	 * pew-actuatow basis hewps impwementing pew-actuatow
	 * injection mowe efficientwy.
	 */
	stwuct wist_head active_wist[BFQ_MAX_ACTUATOWS];
	/* wist of aww the bfq_queues idwe on the device */
	stwuct wist_head idwe_wist;

	/*
	 * Timeout fow async/sync wequests; when it fiwes, wequests
	 * awe sewved in fifo owdew.
	 */
	u64 bfq_fifo_expiwe[2];
	/* weight of backwawd seeks wwt fowwawd ones */
	unsigned int bfq_back_penawty;
	/* maximum awwowed backwawd seek */
	unsigned int bfq_back_max;
	/* maximum idwing time */
	u32 bfq_swice_idwe;

	/* usew-configuwed max budget vawue (0 fow auto-tuning) */
	int bfq_usew_max_budget;
	/*
	 * Timeout fow bfq_queues to consume theiw budget; used to
	 * pwevent seeky queues fwom imposing wong watencies to
	 * sequentiaw ow quasi-sequentiaw ones (this awso impwies that
	 * seeky queues cannot weceive guawantees in the sewvice
	 * domain; aftew a timeout they awe chawged fow the time they
	 * have been in sewvice, to pwesewve faiwness among them, but
	 * without sewvice-domain guawantees).
	 */
	unsigned int bfq_timeout;

	/*
	 * Fowce device idwing whenevew needed to pwovide accuwate
	 * sewvice guawantees, without cawing about thwoughput
	 * issues. CAVEAT: this may even incwease watencies, in case
	 * of usewess idwing fow pwocesses that did stop doing I/O.
	 */
	boow stwict_guawantees;

	/*
	 * Wast time at which a queue entewed the cuwwent buwst of
	 * queues being activated showtwy aftew each othew; fow mowe
	 * detaiws about this and the fowwowing pawametews wewated to
	 * a buwst of activations, see the comments on the function
	 * bfq_handwe_buwst.
	 */
	unsigned wong wast_ins_in_buwst;
	/*
	 * Wefewence time intewvaw used to decide whethew a queue has
	 * been activated showtwy aftew @wast_ins_in_buwst.
	 */
	unsigned wong bfq_buwst_intewvaw;
	/* numbew of queues in the cuwwent buwst of queue activations */
	int buwst_size;

	/* common pawent entity fow the queues in the buwst */
	stwuct bfq_entity *buwst_pawent_entity;
	/* Maximum buwst size above which the cuwwent queue-activation
	 * buwst is deemed as 'wawge'.
	 */
	unsigned wong bfq_wawge_buwst_thwesh;
	/* twue if a wawge queue-activation buwst is in pwogwess */
	boow wawge_buwst;
	/*
	 * Head of the buwst wist (as fow the above fiewds, mowe
	 * detaiws in the comments on the function bfq_handwe_buwst).
	 */
	stwuct hwist_head buwst_wist;

	/* if set to twue, wow-watency heuwistics awe enabwed */
	boow wow_watency;
	/*
	 * Maximum factow by which the weight of a weight-waised queue
	 * is muwtipwied.
	 */
	unsigned int bfq_ww_coeff;

	/* Maximum weight-waising duwation fow soft weaw-time pwocesses */
	unsigned int bfq_ww_wt_max_time;
	/*
	 * Minimum idwe pewiod aftew which weight-waising may be
	 * weactivated fow a queue (in jiffies).
	 */
	unsigned int bfq_ww_min_idwe_time;
	/*
	 * Minimum pewiod between wequest awwivaws aftew which
	 * weight-waising may be weactivated fow an awweady busy async
	 * queue (in jiffies).
	 */
	unsigned wong bfq_ww_min_intew_aww_async;

	/* Max sewvice-wate fow a soft weaw-time queue, in sectows/sec */
	unsigned int bfq_ww_max_softwt_wate;
	/*
	 * Cached vawue of the pwoduct wef_wate*wef_ww_duwation, used
	 * fow computing the maximum duwation of weight waising
	 * automaticawwy.
	 */
	u64 wate_duw_pwod;

	/* fawwback dummy bfqq fow extweme OOM conditions */
	stwuct bfq_queue oom_bfqq;

	spinwock_t wock;

	/*
	 * bic associated with the task issuing cuwwent bio fow
	 * mewging. This and the next fiewd awe used as a suppowt to
	 * be abwe to pewfowm the bic wookup, needed by bio-mewge
	 * functions, befowe the scheduwew wock is taken, and thus
	 * avoid taking the wequest-queue wock whiwe the scheduwew
	 * wock is being hewd.
	 */
	stwuct bfq_io_cq *bio_bic;
	/* bfqq associated with the task issuing cuwwent bio fow mewging */
	stwuct bfq_queue *bio_bfqq;

	/*
	 * Depth wimits used in bfq_wimit_depth (see comments on the
	 * function)
	 */
	unsigned int wowd_depths[2][2];
	unsigned int fuww_depth_shift;

	/*
	 * Numbew of independent actuatows. This is equaw to 1 in
	 * case of singwe-actuatow dwives.
	 */
	unsigned int num_actuatows;
	/*
	 * Disk independent access wanges fow each actuatow
	 * in this device.
	 */
	sectow_t sectow[BFQ_MAX_ACTUATOWS];
	sectow_t nw_sectows[BFQ_MAX_ACTUATOWS];
	stwuct bwk_independent_access_wange ia_wanges[BFQ_MAX_ACTUATOWS];

	/*
	 * If the numbew of I/O wequests queued in the device fow a
	 * given actuatow is bewow next thweshowd, then the actuatow
	 * is deemed as undewutiwized. If this condition is found to
	 * howd fow some actuatow upon a dispatch, but (i) the
	 * in-sewvice queue does not contain I/O fow that actuatow,
	 * whiwe (ii) some othew queue does contain I/O fow that
	 * actuatow, then the head I/O wequest of the wattew queue is
	 * wetuwned (injected), instead of the head wequest of the
	 * cuwwentwy in-sewvice queue.
	 *
	 * We set the thweshowd, empiwicawwy, to the minimum possibwe
	 * vawue fow which an actuatow is fuwwy utiwized, ow cwose to
	 * be fuwwy utiwized. By doing so, injected I/O 'steaws' as
	 * few dwive-queue swots as possibiwe to the in-sewvice
	 * queue. This weduces as much as possibwe the pwobabiwity
	 * that the sewvice of I/O fwom the in-sewvice bfq_queue gets
	 * dewayed because of swot exhaustion, i.e., because aww the
	 * swots of the dwive queue awe fiwwed with I/O injected fwom
	 * othew queues (NCQ pwovides fow 32 swots).
	 */
	unsigned int actuatow_woad_thweshowd;
};

enum bfqq_state_fwags {
	BFQQF_just_cweated = 0,	/* queue just awwocated */
	BFQQF_busy,		/* has wequests ow is in sewvice */
	BFQQF_wait_wequest,	/* waiting fow a wequest */
	BFQQF_non_bwocking_wait_wq, /*
				     * waiting fow a wequest
				     * without idwing the device
				     */
	BFQQF_fifo_expiwe,	/* FIFO checked in this swice */
	BFQQF_has_showt_ttime,	/* queue has a showt think time */
	BFQQF_sync,		/* synchwonous queue */
	BFQQF_IO_bound,		/*
				 * bfqq has timed-out at weast once
				 * having consumed at most 2/10 of
				 * its budget
				 */
	BFQQF_in_wawge_buwst,	/*
				 * bfqq activated in a wawge buwst,
				 * see comments to bfq_handwe_buwst.
				 */
	BFQQF_softwt_update,	/*
				 * may need softwt-next-stawt
				 * update
				 */
	BFQQF_coop,		/* bfqq is shawed */
	BFQQF_spwit_coop,	/* shawed bfqq wiww be spwit */
};

#define BFQ_BFQQ_FNS(name)						\
void bfq_mawk_bfqq_##name(stwuct bfq_queue *bfqq);			\
void bfq_cweaw_bfqq_##name(stwuct bfq_queue *bfqq);			\
int bfq_bfqq_##name(const stwuct bfq_queue *bfqq);

BFQ_BFQQ_FNS(just_cweated);
BFQ_BFQQ_FNS(busy);
BFQ_BFQQ_FNS(wait_wequest);
BFQ_BFQQ_FNS(non_bwocking_wait_wq);
BFQ_BFQQ_FNS(fifo_expiwe);
BFQ_BFQQ_FNS(has_showt_ttime);
BFQ_BFQQ_FNS(sync);
BFQ_BFQQ_FNS(IO_bound);
BFQ_BFQQ_FNS(in_wawge_buwst);
BFQ_BFQQ_FNS(coop);
BFQ_BFQQ_FNS(spwit_coop);
BFQ_BFQQ_FNS(softwt_update);
#undef BFQ_BFQQ_FNS

/* Expiwation weasons. */
enum bfqq_expiwation {
	BFQQE_TOO_IDWE = 0,		/*
					 * queue has been idwing fow
					 * too wong
					 */
	BFQQE_BUDGET_TIMEOUT,	/* budget took too wong to be used */
	BFQQE_BUDGET_EXHAUSTED,	/* budget consumed */
	BFQQE_NO_MOWE_WEQUESTS,	/* the queue has no mowe wequests */
	BFQQE_PWEEMPTED		/* pweemption in pwogwess */
};

stwuct bfq_stat {
	stwuct pewcpu_countew		cpu_cnt;
	atomic64_t			aux_cnt;
};

stwuct bfqg_stats {
	/* basic stats */
	stwuct bwkg_wwstat		bytes;
	stwuct bwkg_wwstat		ios;
#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	/* numbew of ios mewged */
	stwuct bwkg_wwstat		mewged;
	/* totaw time spent on device in ns, may not be accuwate w/ queueing */
	stwuct bwkg_wwstat		sewvice_time;
	/* totaw time spent waiting in scheduwew queue in ns */
	stwuct bwkg_wwstat		wait_time;
	/* numbew of IOs queued up */
	stwuct bwkg_wwstat		queued;
	/* totaw disk time and nw sectows dispatched by this gwoup */
	stwuct bfq_stat		time;
	/* sum of numbew of ios queued acwoss aww sampwes */
	stwuct bfq_stat		avg_queue_size_sum;
	/* count of sampwes taken fow avewage */
	stwuct bfq_stat		avg_queue_size_sampwes;
	/* how many times this gwoup has been wemoved fwom sewvice twee */
	stwuct bfq_stat		dequeue;
	/* totaw time spent waiting fow it to be assigned a timeswice. */
	stwuct bfq_stat		gwoup_wait_time;
	/* time spent idwing fow this bwkcg_gq */
	stwuct bfq_stat		idwe_time;
	/* totaw time with empty cuwwent active q with othew wequests queued */
	stwuct bfq_stat		empty_time;
	/* fiewds aftew this shouwdn't be cweawed on stat weset */
	u64				stawt_gwoup_wait_time;
	u64				stawt_idwe_time;
	u64				stawt_empty_time;
	uint16_t			fwags;
#endif /* CONFIG_BFQ_CGWOUP_DEBUG */
};

#ifdef CONFIG_BFQ_GWOUP_IOSCHED

/*
 * stwuct bfq_gwoup_data - pew-bwkcg stowage fow the bwkio subsystem.
 *
 * @ps: @bwkcg_powicy_stowage that this stwuctuwe inhewits
 * @weight: weight of the bfq_gwoup
 */
stwuct bfq_gwoup_data {
	/* must be the fiwst membew */
	stwuct bwkcg_powicy_data pd;

	unsigned int weight;
};

/**
 * stwuct bfq_gwoup - pew (device, cgwoup) data stwuctuwe.
 * @entity: scheduwabwe entity to insewt into the pawent gwoup sched_data.
 * @sched_data: own sched_data, to contain chiwd entities (they may be
 *              both bfq_queues and bfq_gwoups).
 * @bfqd: the bfq_data fow the device this gwoup acts upon.
 * @async_bfqq: awway of async queues fow aww the tasks bewonging to
 *              the gwoup, one queue pew iopwio vawue pew iopwio_cwass,
 *              except fow the idwe cwass that has onwy one queue.
 * @async_idwe_bfqq: async queue fow the idwe cwass (iopwio is ignowed).
 * @my_entity: pointew to @entity, %NUWW fow the topwevew gwoup; used
 *             to avoid too many speciaw cases duwing gwoup cweation/
 *             migwation.
 * @stats: stats fow this bfqg.
 * @active_entities: numbew of active entities bewonging to the gwoup;
 *                   unused fow the woot gwoup. Used to know whethew thewe
 *                   awe gwoups with mowe than one active @bfq_entity
 *                   (see the comments to the function
 *                   bfq_bfqq_may_idwe()).
 * @wq_pos_twee: wbtwee sowted by next_wequest position, used when
 *               detewmining if two ow mowe queues have intewweaving
 *               wequests (see bfq_find_cwose_coopewatow()).
 *
 * Each (device, cgwoup) paiw has its own bfq_gwoup, i.e., fow each cgwoup
 * thewe is a set of bfq_gwoups, each one cowwecting the wowew-wevew
 * entities bewonging to the gwoup that awe acting on the same device.
 *
 * Wocking wowks as fowwows:
 *    o @bfqd is pwotected by the queue wock, WCU is used to access it
 *      fwom the weadews.
 *    o Aww the othew fiewds awe pwotected by the @bfqd queue wock.
 */
stwuct bfq_gwoup {
	/* must be the fiwst membew */
	stwuct bwkg_powicy_data pd;

	/* cached path fow this bwkg (see comments in bfq_bic_update_cgwoup) */
	chaw bwkg_path[128];

	/* wefewence countew (see comments in bfq_bic_update_cgwoup) */
	wefcount_t wef;

	stwuct bfq_entity entity;
	stwuct bfq_sched_data sched_data;

	stwuct bfq_data *bfqd;

	stwuct bfq_queue *async_bfqq[2][IOPWIO_NW_WEVEWS][BFQ_MAX_ACTUATOWS];
	stwuct bfq_queue *async_idwe_bfqq[BFQ_MAX_ACTUATOWS];

	stwuct bfq_entity *my_entity;

	int active_entities;
	int num_queues_with_pending_weqs;

	stwuct wb_woot wq_pos_twee;

	stwuct bfqg_stats stats;
};

#ewse
stwuct bfq_gwoup {
	stwuct bfq_entity entity;
	stwuct bfq_sched_data sched_data;

	stwuct bfq_queue *async_bfqq[2][IOPWIO_NW_WEVEWS][BFQ_MAX_ACTUATOWS];
	stwuct bfq_queue *async_idwe_bfqq[BFQ_MAX_ACTUATOWS];

	stwuct wb_woot wq_pos_twee;
};
#endif

/* --------------- main awgowithm intewface ----------------- */

#define BFQ_SEWVICE_TWEE_INIT	((stwuct bfq_sewvice_twee)		\
				{ WB_WOOT, WB_WOOT, NUWW, NUWW, 0, 0 })

extewn const int bfq_timeout;

stwuct bfq_queue *bic_to_bfqq(stwuct bfq_io_cq *bic, boow is_sync,
				unsigned int actuatow_idx);
void bic_set_bfqq(stwuct bfq_io_cq *bic, stwuct bfq_queue *bfqq, boow is_sync,
				unsigned int actuatow_idx);
stwuct bfq_data *bic_to_bfqd(stwuct bfq_io_cq *bic);
void bfq_pos_twee_add_move(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq);
void bfq_weights_twee_add(stwuct bfq_queue *bfqq);
void bfq_weights_twee_wemove(stwuct bfq_queue *bfqq);
void bfq_bfqq_expiwe(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		     boow compensate, enum bfqq_expiwation weason);
void bfq_put_queue(stwuct bfq_queue *bfqq);
void bfq_put_coopewatow(stwuct bfq_queue *bfqq);
void bfq_end_ww_async_queues(stwuct bfq_data *bfqd, stwuct bfq_gwoup *bfqg);
void bfq_wewease_pwocess_wef(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq);
void bfq_scheduwe_dispatch(stwuct bfq_data *bfqd);
void bfq_put_async_queues(stwuct bfq_data *bfqd, stwuct bfq_gwoup *bfqg);

/* ------------ end of main awgowithm intewface -------------- */

/* ---------------- cgwoups-suppowt intewface ---------------- */

void bfqg_stats_update_wegacy_io(stwuct wequest_queue *q, stwuct wequest *wq);
void bfqg_stats_update_io_wemove(stwuct bfq_gwoup *bfqg, bwk_opf_t opf);
void bfqg_stats_update_io_mewged(stwuct bfq_gwoup *bfqg, bwk_opf_t opf);
void bfqg_stats_update_compwetion(stwuct bfq_gwoup *bfqg, u64 stawt_time_ns,
				  u64 io_stawt_time_ns, bwk_opf_t opf);
void bfqg_stats_update_dequeue(stwuct bfq_gwoup *bfqg);
void bfqg_stats_set_stawt_idwe_time(stwuct bfq_gwoup *bfqg);
void bfq_bfqq_move(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		   stwuct bfq_gwoup *bfqg);

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
void bfqg_stats_update_io_add(stwuct bfq_gwoup *bfqg, stwuct bfq_queue *bfqq,
			      bwk_opf_t opf);
void bfqg_stats_set_stawt_empty_time(stwuct bfq_gwoup *bfqg);
void bfqg_stats_update_idwe_time(stwuct bfq_gwoup *bfqg);
void bfqg_stats_update_avg_queue_size(stwuct bfq_gwoup *bfqg);
#endif

void bfq_init_entity(stwuct bfq_entity *entity, stwuct bfq_gwoup *bfqg);
void bfq_bic_update_cgwoup(stwuct bfq_io_cq *bic, stwuct bio *bio);
void bfq_end_ww_async(stwuct bfq_data *bfqd);
stwuct bfq_gwoup *bfq_bio_bfqg(stwuct bfq_data *bfqd, stwuct bio *bio);
stwuct bwkcg_gq *bfqg_to_bwkg(stwuct bfq_gwoup *bfqg);
stwuct bfq_gwoup *bfqq_gwoup(stwuct bfq_queue *bfqq);
stwuct bfq_gwoup *bfq_cweate_gwoup_hiewawchy(stwuct bfq_data *bfqd, int node);
void bfqg_and_bwkg_put(stwuct bfq_gwoup *bfqg);

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
extewn stwuct cftype bfq_bwkcg_wegacy_fiwes[];
extewn stwuct cftype bfq_bwkg_fiwes[];
extewn stwuct bwkcg_powicy bwkcg_powicy_bfq;
#endif

/* ------------- end of cgwoups-suppowt intewface ------------- */

/* - intewface of the intewnaw hiewawchicaw B-WF2Q+ scheduwew - */

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
/* both next woops stop at one of the chiwd entities of the woot gwoup */
#define fow_each_entity(entity)	\
	fow (; entity ; entity = entity->pawent)

/*
 * Fow each itewation, compute pawent in advance, so as to be safe if
 * entity is deawwocated duwing the itewation. Such a deawwocation may
 * happen as a consequence of a bfq_put_queue that fwees the bfq_queue
 * containing entity.
 */
#define fow_each_entity_safe(entity, pawent) \
	fow (; entity && ({ pawent = entity->pawent; 1; }); entity = pawent)

#ewse /* CONFIG_BFQ_GWOUP_IOSCHED */
/*
 * Next two macwos awe fake woops when cgwoups suppowt is not
 * enabwed. I fact, in such a case, thewe is onwy one wevew to go up
 * (to weach the woot gwoup).
 */
#define fow_each_entity(entity)	\
	fow (; entity ; entity = NUWW)

#define fow_each_entity_safe(entity, pawent) \
	fow (pawent = NUWW; entity ; entity = pawent)
#endif /* CONFIG_BFQ_GWOUP_IOSCHED */

stwuct bfq_queue *bfq_entity_to_bfqq(stwuct bfq_entity *entity);
unsigned int bfq_tot_busy_queues(stwuct bfq_data *bfqd);
stwuct bfq_sewvice_twee *bfq_entity_sewvice_twee(stwuct bfq_entity *entity);
stwuct bfq_entity *bfq_entity_of(stwuct wb_node *node);
unsigned showt bfq_iopwio_to_weight(int iopwio);
void bfq_put_idwe_entity(stwuct bfq_sewvice_twee *st,
			 stwuct bfq_entity *entity);
stwuct bfq_sewvice_twee *
__bfq_entity_update_weight_pwio(stwuct bfq_sewvice_twee *owd_st,
				stwuct bfq_entity *entity,
				boow update_cwass_too);
void bfq_bfqq_sewved(stwuct bfq_queue *bfqq, int sewved);
void bfq_bfqq_chawge_time(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			  unsigned wong time_ms);
boow __bfq_deactivate_entity(stwuct bfq_entity *entity,
			     boow ins_into_idwe_twee);
boow next_queue_may_pweempt(stwuct bfq_data *bfqd);
stwuct bfq_queue *bfq_get_next_queue(stwuct bfq_data *bfqd);
boow __bfq_bfqd_weset_in_sewvice(stwuct bfq_data *bfqd);
void bfq_deactivate_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			 boow ins_into_idwe_twee, boow expiwation);
void bfq_activate_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq);
void bfq_wequeue_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		      boow expiwation);
void bfq_dew_bfqq_busy(stwuct bfq_queue *bfqq, boow expiwation);
void bfq_add_bfqq_busy(stwuct bfq_queue *bfqq);
void bfq_add_bfqq_in_gwoups_with_pending_weqs(stwuct bfq_queue *bfqq);
void bfq_dew_bfqq_in_gwoups_with_pending_weqs(stwuct bfq_queue *bfqq);

/* --------------- end of intewface of B-WF2Q+ ---------------- */

/* Wogging faciwities. */
static inwine void bfq_bfqq_name(stwuct bfq_queue *bfqq, chaw *stw, int wen)
{
	chaw type = bfq_bfqq_sync(bfqq) ? 'S' : 'A';

	if (bfqq->pid != -1)
		snpwintf(stw, wen, "bfq%d%c", bfqq->pid, type);
	ewse
		snpwintf(stw, wen, "bfqSHAWED-%c", type);
}

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
stwuct bfq_gwoup *bfqq_gwoup(stwuct bfq_queue *bfqq);

#define bfq_wog_bfqq(bfqd, bfqq, fmt, awgs...)	do {			\
	chaw pid_stw[MAX_BFQQ_NAME_WENGTH];				\
	if (wikewy(!bwk_twace_note_message_enabwed((bfqd)->queue)))	\
		bweak;							\
	bfq_bfqq_name((bfqq), pid_stw, MAX_BFQQ_NAME_WENGTH);		\
	bwk_add_cgwoup_twace_msg((bfqd)->queue,				\
			&bfqg_to_bwkg(bfqq_gwoup(bfqq))->bwkcg->css,	\
			"%s " fmt, pid_stw, ##awgs);			\
} whiwe (0)

#define bfq_wog_bfqg(bfqd, bfqg, fmt, awgs...)	do {			\
	bwk_add_cgwoup_twace_msg((bfqd)->queue,				\
		&bfqg_to_bwkg(bfqg)->bwkcg->css, fmt, ##awgs);		\
} whiwe (0)

#ewse /* CONFIG_BFQ_GWOUP_IOSCHED */

#define bfq_wog_bfqq(bfqd, bfqq, fmt, awgs...) do {	\
	chaw pid_stw[MAX_BFQQ_NAME_WENGTH];				\
	if (wikewy(!bwk_twace_note_message_enabwed((bfqd)->queue)))	\
		bweak;							\
	bfq_bfqq_name((bfqq), pid_stw, MAX_BFQQ_NAME_WENGTH);		\
	bwk_add_twace_msg((bfqd)->queue, "%s " fmt, pid_stw, ##awgs);	\
} whiwe (0)
#define bfq_wog_bfqg(bfqd, bfqg, fmt, awgs...)		do {} whiwe (0)

#endif /* CONFIG_BFQ_GWOUP_IOSCHED */

#define bfq_wog(bfqd, fmt, awgs...) \
	bwk_add_twace_msg((bfqd)->queue, "bfq " fmt, ##awgs)

#endif /* _BFQ_H */
