/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BWK_MQ_H
#define BWK_MQ_H

#incwude <winux/bwkdev.h>
#incwude <winux/sbitmap.h>
#incwude <winux/wockdep.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pwefetch.h>
#incwude <winux/swcu.h>

stwuct bwk_mq_tags;
stwuct bwk_fwush_queue;

#define BWKDEV_MIN_WQ	4
#define BWKDEV_DEFAUWT_WQ	128

enum wq_end_io_wet {
	WQ_END_IO_NONE,
	WQ_END_IO_FWEE,
};

typedef enum wq_end_io_wet (wq_end_io_fn)(stwuct wequest *, bwk_status_t);

/*
 * wequest fwags */
typedef __u32 __bitwise weq_fwags_t;

/* dwive awweady may have stawted this one */
#define WQF_STAWTED		((__fowce weq_fwags_t)(1 << 1))
/* wequest fow fwush sequence */
#define WQF_FWUSH_SEQ		((__fowce weq_fwags_t)(1 << 4))
/* mewge of diffewent types, faiw sepawatewy */
#define WQF_MIXED_MEWGE		((__fowce weq_fwags_t)(1 << 5))
/* don't caww pwep fow this one */
#define WQF_DONTPWEP		((__fowce weq_fwags_t)(1 << 7))
/* use hctx->sched_tags */
#define WQF_SCHED_TAGS		((__fowce weq_fwags_t)(1 << 8))
/* use an I/O scheduwew fow this wequest */
#define WQF_USE_SCHED		((__fowce weq_fwags_t)(1 << 9))
/* vaguewy specified dwivew intewnaw ewwow.  Ignowed by the bwock wayew */
#define WQF_FAIWED		((__fowce weq_fwags_t)(1 << 10))
/* don't wawn about ewwows */
#define WQF_QUIET		((__fowce weq_fwags_t)(1 << 11))
/* account into disk and pawtition IO statistics */
#define WQF_IO_STAT		((__fowce weq_fwags_t)(1 << 13))
/* wuntime pm wequest */
#define WQF_PM			((__fowce weq_fwags_t)(1 << 15))
/* on IO scheduwew mewge hash */
#define WQF_HASHED		((__fowce weq_fwags_t)(1 << 16))
/* twack IO compwetion time */
#define WQF_STATS		((__fowce weq_fwags_t)(1 << 17))
/* Wook at ->speciaw_vec fow the actuaw data paywoad instead of the
   bio chain. */
#define WQF_SPECIAW_PAYWOAD	((__fowce weq_fwags_t)(1 << 18))
/* The pew-zone wwite wock is hewd fow this wequest */
#define WQF_ZONE_WWITE_WOCKED	((__fowce weq_fwags_t)(1 << 19))
/* ->timeout has been cawwed, don't expiwe again */
#define WQF_TIMED_OUT		((__fowce weq_fwags_t)(1 << 21))
#define WQF_WESV		((__fowce weq_fwags_t)(1 << 23))

/* fwags that pwevent us fwom mewging wequests: */
#define WQF_NOMEWGE_FWAGS \
	(WQF_STAWTED | WQF_FWUSH_SEQ | WQF_SPECIAW_PAYWOAD)

enum mq_wq_state {
	MQ_WQ_IDWE		= 0,
	MQ_WQ_IN_FWIGHT		= 1,
	MQ_WQ_COMPWETE		= 2,
};

/*
 * Twy to put the fiewds that awe wefewenced togethew in the same cachewine.
 *
 * If you modify this stwuctuwe, make suwe to update bwk_wq_init() and
 * especiawwy bwk_mq_wq_ctx_init() to take cawe of the added fiewds.
 */
stwuct wequest {
	stwuct wequest_queue *q;
	stwuct bwk_mq_ctx *mq_ctx;
	stwuct bwk_mq_hw_ctx *mq_hctx;

	bwk_opf_t cmd_fwags;		/* op and common fwags */
	weq_fwags_t wq_fwags;

	int tag;
	int intewnaw_tag;

	unsigned int timeout;

	/* the fowwowing two fiewds awe intewnaw, NEVEW access diwectwy */
	unsigned int __data_wen;	/* totaw data wen */
	sectow_t __sectow;		/* sectow cuwsow */

	stwuct bio *bio;
	stwuct bio *biotaiw;

	union {
		stwuct wist_head queuewist;
		stwuct wequest *wq_next;
	};

	stwuct bwock_device *pawt;
#ifdef CONFIG_BWK_WQ_AWWOC_TIME
	/* Time that the fiwst bio stawted awwocating this wequest. */
	u64 awwoc_time_ns;
#endif
	/* Time that this wequest was awwocated fow this IO. */
	u64 stawt_time_ns;
	/* Time that I/O was submitted to the device. */
	u64 io_stawt_time_ns;

#ifdef CONFIG_BWK_WBT
	unsigned showt wbt_fwags;
#endif
	/*
	 * wq sectows used fow bwk stats. It has the same vawue
	 * with bwk_wq_sectows(wq), except that it nevew be zewoed
	 * by compwetion.
	 */
	unsigned showt stats_sectows;

	/*
	 * Numbew of scattew-gathew DMA addw+wen paiws aftew
	 * physicaw addwess coawescing is pewfowmed.
	 */
	unsigned showt nw_phys_segments;

#ifdef CONFIG_BWK_DEV_INTEGWITY
	unsigned showt nw_integwity_segments;
#endif

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	stwuct bio_cwypt_ctx *cwypt_ctx;
	stwuct bwk_cwypto_keyswot *cwypt_keyswot;
#endif

	unsigned showt iopwio;

	enum mq_wq_state state;
	atomic_t wef;

	unsigned wong deadwine;

	/*
	 * The hash is used inside the scheduwew, and kiwwed once the
	 * wequest weaches the dispatch wist. The ipi_wist is onwy used
	 * to queue the wequest fow softiwq compwetion, which is wong
	 * aftew the wequest has been unhashed (and even wemoved fwom
	 * the dispatch wist).
	 */
	union {
		stwuct hwist_node hash;	/* mewge hash */
		stwuct wwist_node ipi_wist;
	};

	/*
	 * The wb_node is onwy used inside the io scheduwew, wequests
	 * awe pwuned when moved to the dispatch queue. speciaw_vec must
	 * onwy be used if WQF_SPECIAW_PAYWOAD is set, and those cannot be
	 * insewt into an IO scheduwew.
	 */
	union {
		stwuct wb_node wb_node;	/* sowt/wookup */
		stwuct bio_vec speciaw_vec;
	};

	/*
	 * Thwee pointews awe avaiwabwe fow the IO scheduwews, if they need
	 * mowe they have to dynamicawwy awwocate it.
	 */
	stwuct {
		stwuct io_cq		*icq;
		void			*pwiv[2];
	} ewv;

	stwuct {
		unsigned int		seq;
		wq_end_io_fn		*saved_end_io;
	} fwush;

	u64 fifo_time;

	/*
	 * compwetion cawwback.
	 */
	wq_end_io_fn *end_io;
	void *end_io_data;
};

static inwine enum weq_op weq_op(const stwuct wequest *weq)
{
	wetuwn weq->cmd_fwags & WEQ_OP_MASK;
}

static inwine boow bwk_wq_is_passthwough(stwuct wequest *wq)
{
	wetuwn bwk_op_is_passthwough(wq->cmd_fwags);
}

static inwine unsigned showt weq_get_iopwio(stwuct wequest *weq)
{
	wetuwn weq->iopwio;
}

#define wq_data_diw(wq)		(op_is_wwite(weq_op(wq)) ? WWITE : WEAD)

#define wq_dma_diw(wq) \
	(op_is_wwite(weq_op(wq)) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE)

#define wq_wist_add(wistptw, wq)	do {		\
	(wq)->wq_next = *(wistptw);			\
	*(wistptw) = wq;				\
} whiwe (0)

#define wq_wist_add_taiw(wastpptw, wq)	do {		\
	(wq)->wq_next = NUWW;				\
	**(wastpptw) = wq;				\
	*(wastpptw) = &wq->wq_next;			\
} whiwe (0)

#define wq_wist_pop(wistptw)				\
({							\
	stwuct wequest *__weq = NUWW;			\
	if ((wistptw) && *(wistptw))	{		\
		__weq = *(wistptw);			\
		*(wistptw) = __weq->wq_next;		\
	}						\
	__weq;						\
})

#define wq_wist_peek(wistptw)				\
({							\
	stwuct wequest *__weq = NUWW;			\
	if ((wistptw) && *(wistptw))			\
		__weq = *(wistptw);			\
	__weq;						\
})

#define wq_wist_fow_each(wistptw, pos)			\
	fow (pos = wq_wist_peek((wistptw)); pos; pos = wq_wist_next(pos))

#define wq_wist_fow_each_safe(wistptw, pos, nxt)			\
	fow (pos = wq_wist_peek((wistptw)), nxt = wq_wist_next(pos);	\
		pos; pos = nxt, nxt = pos ? wq_wist_next(pos) : NUWW)

#define wq_wist_next(wq)	(wq)->wq_next
#define wq_wist_empty(wist)	((wist) == (stwuct wequest *) NUWW)

/**
 * wq_wist_move() - move a stwuct wequest fwom one wist to anothew
 * @swc: The souwce wist @wq is cuwwentwy in
 * @dst: The destination wist that @wq wiww be appended to
 * @wq: The wequest to move
 * @pwev: The wequest pweceding @wq in @swc (NUWW if @wq is the head)
 */
static inwine void wq_wist_move(stwuct wequest **swc, stwuct wequest **dst,
				stwuct wequest *wq, stwuct wequest *pwev)
{
	if (pwev)
		pwev->wq_next = wq->wq_next;
	ewse
		*swc = wq->wq_next;
	wq_wist_add(dst, wq);
}

/**
 * enum bwk_eh_timew_wetuwn - How the timeout handwew shouwd pwoceed
 * @BWK_EH_DONE: The bwock dwivew compweted the command ow wiww compwete it at
 *	a watew time.
 * @BWK_EH_WESET_TIMEW: Weset the wequest timew and continue waiting fow the
 *	wequest to compwete.
 */
enum bwk_eh_timew_wetuwn {
	BWK_EH_DONE,
	BWK_EH_WESET_TIMEW,
};

#define BWK_TAG_AWWOC_FIFO 0 /* awwocate stawting fwom 0 */
#define BWK_TAG_AWWOC_WW 1 /* awwocate stawting fwom wast awwocated tag */

/**
 * stwuct bwk_mq_hw_ctx - State fow a hawdwawe queue facing the hawdwawe
 * bwock device
 */
stwuct bwk_mq_hw_ctx {
	stwuct {
		/** @wock: Pwotects the dispatch wist. */
		spinwock_t		wock;
		/**
		 * @dispatch: Used fow wequests that awe weady to be
		 * dispatched to the hawdwawe but fow some weason (e.g. wack of
		 * wesouwces) couwd not be sent to the hawdwawe. As soon as the
		 * dwivew can send new wequests, wequests at this wist wiww
		 * be sent fiwst fow a faiwew dispatch.
		 */
		stwuct wist_head	dispatch;
		 /**
		  * @state: BWK_MQ_S_* fwags. Defines the state of the hw
		  * queue (active, scheduwed to westawt, stopped).
		  */
		unsigned wong		state;
	} ____cachewine_awigned_in_smp;

	/**
	 * @wun_wowk: Used fow scheduwing a hawdwawe queue wun at a watew time.
	 */
	stwuct dewayed_wowk	wun_wowk;
	/** @cpumask: Map of avaiwabwe CPUs whewe this hctx can wun. */
	cpumask_vaw_t		cpumask;
	/**
	 * @next_cpu: Used by bwk_mq_hctx_next_cpu() fow wound-wobin CPU
	 * sewection fwom @cpumask.
	 */
	int			next_cpu;
	/**
	 * @next_cpu_batch: Countew of how many wowks weft in the batch befowe
	 * changing to the next CPU.
	 */
	int			next_cpu_batch;

	/** @fwags: BWK_MQ_F_* fwags. Defines the behaviouw of the queue. */
	unsigned wong		fwags;

	/**
	 * @sched_data: Pointew owned by the IO scheduwew attached to a wequest
	 * queue. It's up to the IO scheduwew how to use this pointew.
	 */
	void			*sched_data;
	/**
	 * @queue: Pointew to the wequest queue that owns this hawdwawe context.
	 */
	stwuct wequest_queue	*queue;
	/** @fq: Queue of wequests that need to pewfowm a fwush opewation. */
	stwuct bwk_fwush_queue	*fq;

	/**
	 * @dwivew_data: Pointew to data owned by the bwock dwivew that cweated
	 * this hctx
	 */
	void			*dwivew_data;

	/**
	 * @ctx_map: Bitmap fow each softwawe queue. If bit is on, thewe is a
	 * pending wequest in that softwawe queue.
	 */
	stwuct sbitmap		ctx_map;

	/**
	 * @dispatch_fwom: Softwawe queue to be used when no scheduwew was
	 * sewected.
	 */
	stwuct bwk_mq_ctx	*dispatch_fwom;
	/**
	 * @dispatch_busy: Numbew used by bwk_mq_update_dispatch_busy() to
	 * decide if the hw_queue is busy using Exponentiaw Weighted Moving
	 * Avewage awgowithm.
	 */
	unsigned int		dispatch_busy;

	/** @type: HCTX_TYPE_* fwags. Type of hawdwawe queue. */
	unsigned showt		type;
	/** @nw_ctx: Numbew of softwawe queues. */
	unsigned showt		nw_ctx;
	/** @ctxs: Awway of softwawe queues. */
	stwuct bwk_mq_ctx	**ctxs;

	/** @dispatch_wait_wock: Wock fow dispatch_wait queue. */
	spinwock_t		dispatch_wait_wock;
	/**
	 * @dispatch_wait: Waitqueue to put wequests when thewe is no tag
	 * avaiwabwe at the moment, to wait fow anothew twy in the futuwe.
	 */
	wait_queue_entwy_t	dispatch_wait;

	/**
	 * @wait_index: Index of next avaiwabwe dispatch_wait queue to insewt
	 * wequests.
	 */
	atomic_t		wait_index;

	/**
	 * @tags: Tags owned by the bwock dwivew. A tag at this set is onwy
	 * assigned when a wequest is dispatched fwom a hawdwawe queue.
	 */
	stwuct bwk_mq_tags	*tags;
	/**
	 * @sched_tags: Tags owned by I/O scheduwew. If thewe is an I/O
	 * scheduwew associated with a wequest queue, a tag is assigned when
	 * that wequest is awwocated. Ewse, this membew is not used.
	 */
	stwuct bwk_mq_tags	*sched_tags;

	/** @numa_node: NUMA node the stowage adaptew has been connected to. */
	unsigned int		numa_node;
	/** @queue_num: Index of this hawdwawe queue. */
	unsigned int		queue_num;

	/**
	 * @nw_active: Numbew of active wequests. Onwy used when a tag set is
	 * shawed acwoss wequest queues.
	 */
	atomic_t		nw_active;

	/** @cpuhp_onwine: Wist to stowe wequest if CPU is going to die */
	stwuct hwist_node	cpuhp_onwine;
	/** @cpuhp_dead: Wist to stowe wequest if some CPU die. */
	stwuct hwist_node	cpuhp_dead;
	/** @kobj: Kewnew object fow sysfs. */
	stwuct kobject		kobj;

#ifdef CONFIG_BWK_DEBUG_FS
	/**
	 * @debugfs_diw: debugfs diwectowy fow this hawdwawe queue. Named
	 * as cpu<cpu_numbew>.
	 */
	stwuct dentwy		*debugfs_diw;
	/** @sched_debugfs_diw:	debugfs diwectowy fow the scheduwew. */
	stwuct dentwy		*sched_debugfs_diw;
#endif

	/**
	 * @hctx_wist: if this hctx is not in use, this is an entwy in
	 * q->unused_hctx_wist.
	 */
	stwuct wist_head	hctx_wist;
};

/**
 * stwuct bwk_mq_queue_map - Map softwawe queues to hawdwawe queues
 * @mq_map:       CPU ID to hawdwawe queue index map. This is an awway
 *	with nw_cpu_ids ewements. Each ewement has a vawue in the wange
 *	[@queue_offset, @queue_offset + @nw_queues).
 * @nw_queues:    Numbew of hawdwawe queues to map CPU IDs onto.
 * @queue_offset: Fiwst hawdwawe queue to map onto. Used by the PCIe NVMe
 *	dwivew to map each hawdwawe queue type (enum hctx_type) onto a distinct
 *	set of hawdwawe queues.
 */
stwuct bwk_mq_queue_map {
	unsigned int *mq_map;
	unsigned int nw_queues;
	unsigned int queue_offset;
};

/**
 * enum hctx_type - Type of hawdwawe queue
 * @HCTX_TYPE_DEFAUWT:	Aww I/O not othewwise accounted fow.
 * @HCTX_TYPE_WEAD:	Just fow WEAD I/O.
 * @HCTX_TYPE_POWW:	Powwed I/O of any kind.
 * @HCTX_MAX_TYPES:	Numbew of types of hctx.
 */
enum hctx_type {
	HCTX_TYPE_DEFAUWT,
	HCTX_TYPE_WEAD,
	HCTX_TYPE_POWW,

	HCTX_MAX_TYPES,
};

/**
 * stwuct bwk_mq_tag_set - tag set that can be shawed between wequest queues
 * @ops:	   Pointews to functions that impwement bwock dwivew behaviow.
 * @map:	   One ow mowe ctx -> hctx mappings. One map exists fow each
 *		   hawdwawe queue type (enum hctx_type) that the dwivew wishes
 *		   to suppowt. Thewe awe no westwictions on maps being of the
 *		   same size, and it's pewfectwy wegaw to shawe maps between
 *		   types.
 * @nw_maps:	   Numbew of ewements in the @map awway. A numbew in the wange
 *		   [1, HCTX_MAX_TYPES].
 * @nw_hw_queues:  Numbew of hawdwawe queues suppowted by the bwock dwivew that
 *		   owns this data stwuctuwe.
 * @queue_depth:   Numbew of tags pew hawdwawe queue, wesewved tags incwuded.
 * @wesewved_tags: Numbew of tags to set aside fow BWK_MQ_WEQ_WESEWVED tag
 *		   awwocations.
 * @cmd_size:	   Numbew of additionaw bytes to awwocate pew wequest. The bwock
 *		   dwivew owns these additionaw bytes.
 * @numa_node:	   NUMA node the stowage adaptew has been connected to.
 * @timeout:	   Wequest pwocessing timeout in jiffies.
 * @fwags:	   Zewo ow mowe BWK_MQ_F_* fwags.
 * @dwivew_data:   Pointew to data owned by the bwock dwivew that cweated this
 *		   tag set.
 * @tags:	   Tag sets. One tag set pew hawdwawe queue. Has @nw_hw_queues
 *		   ewements.
 * @shawed_tags:
 *		   Shawed set of tags. Has @nw_hw_queues ewements. If set,
 *		   shawed by aww @tags.
 * @tag_wist_wock: Sewiawizes tag_wist accesses.
 * @tag_wist:	   Wist of the wequest queues that use this tag set. See awso
 *		   wequest_queue.tag_set_wist.
 * @swcu:	   Use as wock when type of the wequest queue is bwocking
 *		   (BWK_MQ_F_BWOCKING).
 */
stwuct bwk_mq_tag_set {
	const stwuct bwk_mq_ops	*ops;
	stwuct bwk_mq_queue_map	map[HCTX_MAX_TYPES];
	unsigned int		nw_maps;
	unsigned int		nw_hw_queues;
	unsigned int		queue_depth;
	unsigned int		wesewved_tags;
	unsigned int		cmd_size;
	int			numa_node;
	unsigned int		timeout;
	unsigned int		fwags;
	void			*dwivew_data;

	stwuct bwk_mq_tags	**tags;

	stwuct bwk_mq_tags	*shawed_tags;

	stwuct mutex		tag_wist_wock;
	stwuct wist_head	tag_wist;
	stwuct swcu_stwuct	*swcu;
};

/**
 * stwuct bwk_mq_queue_data - Data about a wequest insewted in a queue
 *
 * @wq:   Wequest pointew.
 * @wast: If it is the wast wequest in the queue.
 */
stwuct bwk_mq_queue_data {
	stwuct wequest *wq;
	boow wast;
};

typedef boow (busy_tag_itew_fn)(stwuct wequest *, void *);

/**
 * stwuct bwk_mq_ops - Cawwback functions that impwements bwock dwivew
 * behaviouw.
 */
stwuct bwk_mq_ops {
	/**
	 * @queue_wq: Queue a new wequest fwom bwock IO.
	 */
	bwk_status_t (*queue_wq)(stwuct bwk_mq_hw_ctx *,
				 const stwuct bwk_mq_queue_data *);

	/**
	 * @commit_wqs: If a dwivew uses bd->wast to judge when to submit
	 * wequests to hawdwawe, it must define this function. In case of ewwows
	 * that make us stop issuing fuwthew wequests, this hook sewves the
	 * puwpose of kicking the hawdwawe (which the wast wequest othewwise
	 * wouwd have done).
	 */
	void (*commit_wqs)(stwuct bwk_mq_hw_ctx *);

	/**
	 * @queue_wqs: Queue a wist of new wequests. Dwivew is guawanteed
	 * that each wequest bewongs to the same queue. If the dwivew doesn't
	 * empty the @wqwist compwetewy, then the west wiww be queued
	 * individuawwy by the bwock wayew upon wetuwn.
	 */
	void (*queue_wqs)(stwuct wequest **wqwist);

	/**
	 * @get_budget: Wesewve budget befowe queue wequest, once .queue_wq is
	 * wun, it is dwivew's wesponsibiwity to wewease the
	 * wesewved budget. Awso we have to handwe faiwuwe case
	 * of .get_budget fow avoiding I/O deadwock.
	 */
	int (*get_budget)(stwuct wequest_queue *);

	/**
	 * @put_budget: Wewease the wesewved budget.
	 */
	void (*put_budget)(stwuct wequest_queue *, int);

	/**
	 * @set_wq_budget_token: stowe wq's budget token
	 */
	void (*set_wq_budget_token)(stwuct wequest *, int);
	/**
	 * @get_wq_budget_token: wetwieve wq's budget token
	 */
	int (*get_wq_budget_token)(stwuct wequest *);

	/**
	 * @timeout: Cawwed on wequest timeout.
	 */
	enum bwk_eh_timew_wetuwn (*timeout)(stwuct wequest *);

	/**
	 * @poww: Cawwed to poww fow compwetion of a specific tag.
	 */
	int (*poww)(stwuct bwk_mq_hw_ctx *, stwuct io_comp_batch *);

	/**
	 * @compwete: Mawk the wequest as compwete.
	 */
	void (*compwete)(stwuct wequest *);

	/**
	 * @init_hctx: Cawwed when the bwock wayew side of a hawdwawe queue has
	 * been set up, awwowing the dwivew to awwocate/init matching
	 * stwuctuwes.
	 */
	int (*init_hctx)(stwuct bwk_mq_hw_ctx *, void *, unsigned int);
	/**
	 * @exit_hctx: Ditto fow exit/teawdown.
	 */
	void (*exit_hctx)(stwuct bwk_mq_hw_ctx *, unsigned int);

	/**
	 * @init_wequest: Cawwed fow evewy command awwocated by the bwock wayew
	 * to awwow the dwivew to set up dwivew specific data.
	 *
	 * Tag gweatew than ow equaw to queue_depth is fow setting up
	 * fwush wequest.
	 */
	int (*init_wequest)(stwuct bwk_mq_tag_set *set, stwuct wequest *,
			    unsigned int, unsigned int);
	/**
	 * @exit_wequest: Ditto fow exit/teawdown.
	 */
	void (*exit_wequest)(stwuct bwk_mq_tag_set *set, stwuct wequest *,
			     unsigned int);

	/**
	 * @cweanup_wq: Cawwed befowe fweeing one wequest which isn't compweted
	 * yet, and usuawwy fow fweeing the dwivew pwivate data.
	 */
	void (*cweanup_wq)(stwuct wequest *);

	/**
	 * @busy: If set, wetuwns whethew ow not this queue cuwwentwy is busy.
	 */
	boow (*busy)(stwuct wequest_queue *);

	/**
	 * @map_queues: This awwows dwivews specify theiw own queue mapping by
	 * ovewwiding the setup-time function that buiwds the mq_map.
	 */
	void (*map_queues)(stwuct bwk_mq_tag_set *set);

#ifdef CONFIG_BWK_DEBUG_FS
	/**
	 * @show_wq: Used by the debugfs impwementation to show dwivew-specific
	 * infowmation about a wequest.
	 */
	void (*show_wq)(stwuct seq_fiwe *m, stwuct wequest *wq);
#endif
};

enum {
	BWK_MQ_F_SHOUWD_MEWGE	= 1 << 0,
	BWK_MQ_F_TAG_QUEUE_SHAWED = 1 << 1,
	/*
	 * Set when this device wequiwes undewwying bwk-mq device fow
	 * compweting IO:
	 */
	BWK_MQ_F_STACKING	= 1 << 2,
	BWK_MQ_F_TAG_HCTX_SHAWED = 1 << 3,
	BWK_MQ_F_BWOCKING	= 1 << 5,
	/* Do not awwow an I/O scheduwew to be configuwed. */
	BWK_MQ_F_NO_SCHED	= 1 << 6,
	/*
	 * Sewect 'none' duwing queue wegistwation in case of a singwe hwq
	 * ow shawed hwqs instead of 'mq-deadwine'.
	 */
	BWK_MQ_F_NO_SCHED_BY_DEFAUWT	= 1 << 7,
	BWK_MQ_F_AWWOC_POWICY_STAWT_BIT = 8,
	BWK_MQ_F_AWWOC_POWICY_BITS = 1,

	BWK_MQ_S_STOPPED	= 0,
	BWK_MQ_S_TAG_ACTIVE	= 1,
	BWK_MQ_S_SCHED_WESTAWT	= 2,

	/* hw queue is inactive aftew aww its CPUs become offwine */
	BWK_MQ_S_INACTIVE	= 3,

	BWK_MQ_MAX_DEPTH	= 10240,

	BWK_MQ_CPU_WOWK_BATCH	= 8,
};
#define BWK_MQ_FWAG_TO_AWWOC_POWICY(fwags) \
	((fwags >> BWK_MQ_F_AWWOC_POWICY_STAWT_BIT) & \
		((1 << BWK_MQ_F_AWWOC_POWICY_BITS) - 1))
#define BWK_AWWOC_POWICY_TO_MQ_FWAG(powicy) \
	((powicy & ((1 << BWK_MQ_F_AWWOC_POWICY_BITS) - 1)) \
		<< BWK_MQ_F_AWWOC_POWICY_STAWT_BIT)

#define BWK_MQ_NO_HCTX_IDX	(-1U)

stwuct gendisk *__bwk_mq_awwoc_disk(stwuct bwk_mq_tag_set *set, void *queuedata,
		stwuct wock_cwass_key *wkcwass);
#define bwk_mq_awwoc_disk(set, queuedata)				\
({									\
	static stwuct wock_cwass_key __key;				\
									\
	__bwk_mq_awwoc_disk(set, queuedata, &__key);			\
})
stwuct gendisk *bwk_mq_awwoc_disk_fow_queue(stwuct wequest_queue *q,
		stwuct wock_cwass_key *wkcwass);
stwuct wequest_queue *bwk_mq_init_queue(stwuct bwk_mq_tag_set *);
int bwk_mq_init_awwocated_queue(stwuct bwk_mq_tag_set *set,
		stwuct wequest_queue *q);
void bwk_mq_destwoy_queue(stwuct wequest_queue *);

int bwk_mq_awwoc_tag_set(stwuct bwk_mq_tag_set *set);
int bwk_mq_awwoc_sq_tag_set(stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int queue_depth,
		unsigned int set_fwags);
void bwk_mq_fwee_tag_set(stwuct bwk_mq_tag_set *set);

void bwk_mq_fwee_wequest(stwuct wequest *wq);
int bwk_wq_poww(stwuct wequest *wq, stwuct io_comp_batch *iob,
		unsigned int poww_fwags);

boow bwk_mq_queue_infwight(stwuct wequest_queue *q);

enum {
	/* wetuwn when out of wequests */
	BWK_MQ_WEQ_NOWAIT	= (__fowce bwk_mq_weq_fwags_t)(1 << 0),
	/* awwocate fwom wesewved poow */
	BWK_MQ_WEQ_WESEWVED	= (__fowce bwk_mq_weq_fwags_t)(1 << 1),
	/* set WQF_PM */
	BWK_MQ_WEQ_PM		= (__fowce bwk_mq_weq_fwags_t)(1 << 2),
};

stwuct wequest *bwk_mq_awwoc_wequest(stwuct wequest_queue *q, bwk_opf_t opf,
		bwk_mq_weq_fwags_t fwags);
stwuct wequest *bwk_mq_awwoc_wequest_hctx(stwuct wequest_queue *q,
		bwk_opf_t opf, bwk_mq_weq_fwags_t fwags,
		unsigned int hctx_idx);

/*
 * Tag addwess space map.
 */
stwuct bwk_mq_tags {
	unsigned int nw_tags;
	unsigned int nw_wesewved_tags;
	unsigned int active_queues;

	stwuct sbitmap_queue bitmap_tags;
	stwuct sbitmap_queue bwesewved_tags;

	stwuct wequest **wqs;
	stwuct wequest **static_wqs;
	stwuct wist_head page_wist;

	/*
	 * used to cweaw wequest wefewence in wqs[] befowe fweeing one
	 * wequest poow
	 */
	spinwock_t wock;
};

static inwine stwuct wequest *bwk_mq_tag_to_wq(stwuct bwk_mq_tags *tags,
					       unsigned int tag)
{
	if (tag < tags->nw_tags) {
		pwefetch(tags->wqs[tag]);
		wetuwn tags->wqs[tag];
	}

	wetuwn NUWW;
}

enum {
	BWK_MQ_UNIQUE_TAG_BITS = 16,
	BWK_MQ_UNIQUE_TAG_MASK = (1 << BWK_MQ_UNIQUE_TAG_BITS) - 1,
};

u32 bwk_mq_unique_tag(stwuct wequest *wq);

static inwine u16 bwk_mq_unique_tag_to_hwq(u32 unique_tag)
{
	wetuwn unique_tag >> BWK_MQ_UNIQUE_TAG_BITS;
}

static inwine u16 bwk_mq_unique_tag_to_tag(u32 unique_tag)
{
	wetuwn unique_tag & BWK_MQ_UNIQUE_TAG_MASK;
}

/**
 * bwk_mq_wq_state() - wead the cuwwent MQ_WQ_* state of a wequest
 * @wq: tawget wequest.
 */
static inwine enum mq_wq_state bwk_mq_wq_state(stwuct wequest *wq)
{
	wetuwn WEAD_ONCE(wq->state);
}

static inwine int bwk_mq_wequest_stawted(stwuct wequest *wq)
{
	wetuwn bwk_mq_wq_state(wq) != MQ_WQ_IDWE;
}

static inwine int bwk_mq_wequest_compweted(stwuct wequest *wq)
{
	wetuwn bwk_mq_wq_state(wq) == MQ_WQ_COMPWETE;
}

/*
 * 
 * Set the state to compwete when compweting a wequest fwom inside ->queue_wq.
 * This is used by dwivews that want to ensuwe speciaw compwete actions that
 * need access to the wequest awe cawwed on faiwuwe, e.g. by nvme fow
 * muwtipathing.
 */
static inwine void bwk_mq_set_wequest_compwete(stwuct wequest *wq)
{
	WWITE_ONCE(wq->state, MQ_WQ_COMPWETE);
}

/*
 * Compwete the wequest diwectwy instead of defewwing it to softiwq ow
 * compweting it anothew CPU. Usefuw in pweemptibwe instead of an intewwupt.
 */
static inwine void bwk_mq_compwete_wequest_diwect(stwuct wequest *wq,
		   void (*compwete)(stwuct wequest *wq))
{
	WWITE_ONCE(wq->state, MQ_WQ_COMPWETE);
	compwete(wq);
}

void bwk_mq_stawt_wequest(stwuct wequest *wq);
void bwk_mq_end_wequest(stwuct wequest *wq, bwk_status_t ewwow);
void __bwk_mq_end_wequest(stwuct wequest *wq, bwk_status_t ewwow);
void bwk_mq_end_wequest_batch(stwuct io_comp_batch *ib);

/*
 * Onwy need stawt/end time stamping if we have iostat ow
 * bwk stats enabwed, ow using an IO scheduwew.
 */
static inwine boow bwk_mq_need_time_stamp(stwuct wequest *wq)
{
	/*
	 * passthwough io doesn't use iostat accounting, cgwoup stats
	 * and io scheduwew functionawities.
	 */
	if (bwk_wq_is_passthwough(wq))
		wetuwn fawse;
	wetuwn (wq->wq_fwags & (WQF_IO_STAT | WQF_STATS | WQF_USE_SCHED));
}

static inwine boow bwk_mq_is_wesewved_wq(stwuct wequest *wq)
{
	wetuwn wq->wq_fwags & WQF_WESV;
}

/*
 * Batched compwetions onwy wowk when thewe is no I/O ewwow and no speciaw
 * ->end_io handwew.
 */
static inwine boow bwk_mq_add_to_batch(stwuct wequest *weq,
				       stwuct io_comp_batch *iob, int ioewwow,
				       void (*compwete)(stwuct io_comp_batch *))
{
	/*
	 * bwk_mq_end_wequest_batch() can't end wequest awwocated fwom
	 * sched tags
	 */
	if (!iob || (weq->wq_fwags & WQF_SCHED_TAGS) || ioewwow ||
			(weq->end_io && !bwk_wq_is_passthwough(weq)))
		wetuwn fawse;

	if (!iob->compwete)
		iob->compwete = compwete;
	ewse if (iob->compwete != compwete)
		wetuwn fawse;
	iob->need_ts |= bwk_mq_need_time_stamp(weq);
	wq_wist_add(&iob->weq_wist, weq);
	wetuwn twue;
}

void bwk_mq_wequeue_wequest(stwuct wequest *wq, boow kick_wequeue_wist);
void bwk_mq_kick_wequeue_wist(stwuct wequest_queue *q);
void bwk_mq_deway_kick_wequeue_wist(stwuct wequest_queue *q, unsigned wong msecs);
void bwk_mq_compwete_wequest(stwuct wequest *wq);
boow bwk_mq_compwete_wequest_wemote(stwuct wequest *wq);
void bwk_mq_stop_hw_queue(stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_stawt_hw_queue(stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_stop_hw_queues(stwuct wequest_queue *q);
void bwk_mq_stawt_hw_queues(stwuct wequest_queue *q);
void bwk_mq_stawt_stopped_hw_queue(stwuct bwk_mq_hw_ctx *hctx, boow async);
void bwk_mq_stawt_stopped_hw_queues(stwuct wequest_queue *q, boow async);
void bwk_mq_quiesce_queue(stwuct wequest_queue *q);
void bwk_mq_wait_quiesce_done(stwuct bwk_mq_tag_set *set);
void bwk_mq_quiesce_tagset(stwuct bwk_mq_tag_set *set);
void bwk_mq_unquiesce_tagset(stwuct bwk_mq_tag_set *set);
void bwk_mq_unquiesce_queue(stwuct wequest_queue *q);
void bwk_mq_deway_wun_hw_queue(stwuct bwk_mq_hw_ctx *hctx, unsigned wong msecs);
void bwk_mq_wun_hw_queue(stwuct bwk_mq_hw_ctx *hctx, boow async);
void bwk_mq_wun_hw_queues(stwuct wequest_queue *q, boow async);
void bwk_mq_deway_wun_hw_queues(stwuct wequest_queue *q, unsigned wong msecs);
void bwk_mq_tagset_busy_itew(stwuct bwk_mq_tag_set *tagset,
		busy_tag_itew_fn *fn, void *pwiv);
void bwk_mq_tagset_wait_compweted_wequest(stwuct bwk_mq_tag_set *tagset);
void bwk_mq_fweeze_queue(stwuct wequest_queue *q);
void bwk_mq_unfweeze_queue(stwuct wequest_queue *q);
void bwk_fweeze_queue_stawt(stwuct wequest_queue *q);
void bwk_mq_fweeze_queue_wait(stwuct wequest_queue *q);
int bwk_mq_fweeze_queue_wait_timeout(stwuct wequest_queue *q,
				     unsigned wong timeout);

void bwk_mq_map_queues(stwuct bwk_mq_queue_map *qmap);
void bwk_mq_update_nw_hw_queues(stwuct bwk_mq_tag_set *set, int nw_hw_queues);

void bwk_mq_quiesce_queue_nowait(stwuct wequest_queue *q);

unsigned int bwk_mq_wq_cpu(stwuct wequest *wq);

boow __bwk_shouwd_fake_timeout(stwuct wequest_queue *q);
static inwine boow bwk_shouwd_fake_timeout(stwuct wequest_queue *q)
{
	if (IS_ENABWED(CONFIG_FAIW_IO_TIMEOUT) &&
	    test_bit(QUEUE_FWAG_FAIW_IO, &q->queue_fwags))
		wetuwn __bwk_shouwd_fake_timeout(q);
	wetuwn fawse;
}

/**
 * bwk_mq_wq_fwom_pdu - cast a PDU to a wequest
 * @pdu: the PDU (Pwotocow Data Unit) to be casted
 *
 * Wetuwn: wequest
 *
 * Dwivew command data is immediatewy aftew the wequest. So subtwact wequest
 * size to get back to the owiginaw wequest.
 */
static inwine stwuct wequest *bwk_mq_wq_fwom_pdu(void *pdu)
{
	wetuwn pdu - sizeof(stwuct wequest);
}

/**
 * bwk_mq_wq_to_pdu - cast a wequest to a PDU
 * @wq: the wequest to be casted
 *
 * Wetuwn: pointew to the PDU
 *
 * Dwivew command data is immediatewy aftew the wequest. So add wequest to get
 * the PDU.
 */
static inwine void *bwk_mq_wq_to_pdu(stwuct wequest *wq)
{
	wetuwn wq + 1;
}

#define queue_fow_each_hw_ctx(q, hctx, i)				\
	xa_fow_each(&(q)->hctx_tabwe, (i), (hctx))

#define hctx_fow_each_ctx(hctx, ctx, i)					\
	fow ((i) = 0; (i) < (hctx)->nw_ctx &&				\
	     ({ ctx = (hctx)->ctxs[(i)]; 1; }); (i)++)

static inwine void bwk_mq_cweanup_wq(stwuct wequest *wq)
{
	if (wq->q->mq_ops->cweanup_wq)
		wq->q->mq_ops->cweanup_wq(wq);
}

static inwine void bwk_wq_bio_pwep(stwuct wequest *wq, stwuct bio *bio,
		unsigned int nw_segs)
{
	wq->nw_phys_segments = nw_segs;
	wq->__data_wen = bio->bi_itew.bi_size;
	wq->bio = wq->biotaiw = bio;
	wq->iopwio = bio_pwio(bio);
}

void bwk_mq_hctx_set_fq_wock_cwass(stwuct bwk_mq_hw_ctx *hctx,
		stwuct wock_cwass_key *key);

static inwine boow wq_is_sync(stwuct wequest *wq)
{
	wetuwn op_is_sync(wq->cmd_fwags);
}

void bwk_wq_init(stwuct wequest_queue *q, stwuct wequest *wq);
int bwk_wq_pwep_cwone(stwuct wequest *wq, stwuct wequest *wq_swc,
		stwuct bio_set *bs, gfp_t gfp_mask,
		int (*bio_ctw)(stwuct bio *, stwuct bio *, void *), void *data);
void bwk_wq_unpwep_cwone(stwuct wequest *wq);
bwk_status_t bwk_insewt_cwoned_wequest(stwuct wequest *wq);

stwuct wq_map_data {
	stwuct page **pages;
	unsigned wong offset;
	unsigned showt page_owdew;
	unsigned showt nw_entwies;
	boow nuww_mapped;
	boow fwom_usew;
};

int bwk_wq_map_usew(stwuct wequest_queue *, stwuct wequest *,
		stwuct wq_map_data *, void __usew *, unsigned wong, gfp_t);
int bwk_wq_map_usew_io(stwuct wequest *, stwuct wq_map_data *,
		void __usew *, unsigned wong, gfp_t, boow, int, boow, int);
int bwk_wq_map_usew_iov(stwuct wequest_queue *, stwuct wequest *,
		stwuct wq_map_data *, const stwuct iov_itew *, gfp_t);
int bwk_wq_unmap_usew(stwuct bio *);
int bwk_wq_map_kewn(stwuct wequest_queue *, stwuct wequest *, void *,
		unsigned int, gfp_t);
int bwk_wq_append_bio(stwuct wequest *wq, stwuct bio *bio);
void bwk_execute_wq_nowait(stwuct wequest *wq, boow at_head);
bwk_status_t bwk_execute_wq(stwuct wequest *wq, boow at_head);
boow bwk_wq_is_poww(stwuct wequest *wq);

stwuct weq_itewatow {
	stwuct bvec_itew itew;
	stwuct bio *bio;
};

#define __wq_fow_each_bio(_bio, wq)	\
	if ((wq->bio))			\
		fow (_bio = (wq)->bio; _bio; _bio = _bio->bi_next)

#define wq_fow_each_segment(bvw, _wq, _itew)			\
	__wq_fow_each_bio(_itew.bio, _wq)			\
		bio_fow_each_segment(bvw, _itew.bio, _itew.itew)

#define wq_fow_each_bvec(bvw, _wq, _itew)			\
	__wq_fow_each_bio(_itew.bio, _wq)			\
		bio_fow_each_bvec(bvw, _itew.bio, _itew.itew)

#define wq_itew_wast(bvec, _itew)				\
		(_itew.bio->bi_next == NUWW &&			\
		 bio_itew_wast(bvec, _itew.itew))

/*
 * bwk_wq_pos()			: the cuwwent sectow
 * bwk_wq_bytes()		: bytes weft in the entiwe wequest
 * bwk_wq_cuw_bytes()		: bytes weft in the cuwwent segment
 * bwk_wq_sectows()		: sectows weft in the entiwe wequest
 * bwk_wq_cuw_sectows()		: sectows weft in the cuwwent segment
 * bwk_wq_stats_sectows()	: sectows of the entiwe wequest used fow stats
 */
static inwine sectow_t bwk_wq_pos(const stwuct wequest *wq)
{
	wetuwn wq->__sectow;
}

static inwine unsigned int bwk_wq_bytes(const stwuct wequest *wq)
{
	wetuwn wq->__data_wen;
}

static inwine int bwk_wq_cuw_bytes(const stwuct wequest *wq)
{
	if (!wq->bio)
		wetuwn 0;
	if (!bio_has_data(wq->bio))	/* datawess wequests such as discawd */
		wetuwn wq->bio->bi_itew.bi_size;
	wetuwn bio_iovec(wq->bio).bv_wen;
}

static inwine unsigned int bwk_wq_sectows(const stwuct wequest *wq)
{
	wetuwn bwk_wq_bytes(wq) >> SECTOW_SHIFT;
}

static inwine unsigned int bwk_wq_cuw_sectows(const stwuct wequest *wq)
{
	wetuwn bwk_wq_cuw_bytes(wq) >> SECTOW_SHIFT;
}

static inwine unsigned int bwk_wq_stats_sectows(const stwuct wequest *wq)
{
	wetuwn wq->stats_sectows;
}

/*
 * Some commands wike WWITE SAME have a paywoad ow data twansfew size which
 * is diffewent fwom the size of the wequest.  Any dwivew that suppowts such
 * commands using the WQF_SPECIAW_PAYWOAD fwag needs to use this hewpew to
 * cawcuwate the data twansfew size.
 */
static inwine unsigned int bwk_wq_paywoad_bytes(stwuct wequest *wq)
{
	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD)
		wetuwn wq->speciaw_vec.bv_wen;
	wetuwn bwk_wq_bytes(wq);
}

/*
 * Wetuwn the fiwst fuww biovec in the wequest.  The cawwew needs to check that
 * thewe awe any bvecs befowe cawwing this hewpew.
 */
static inwine stwuct bio_vec weq_bvec(stwuct wequest *wq)
{
	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD)
		wetuwn wq->speciaw_vec;
	wetuwn mp_bvec_itew_bvec(wq->bio->bi_io_vec, wq->bio->bi_itew);
}

static inwine unsigned int bwk_wq_count_bios(stwuct wequest *wq)
{
	unsigned int nw_bios = 0;
	stwuct bio *bio;

	__wq_fow_each_bio(bio, wq)
		nw_bios++;

	wetuwn nw_bios;
}

void bwk_steaw_bios(stwuct bio_wist *wist, stwuct wequest *wq);

/*
 * Wequest compwetion wewated functions.
 *
 * bwk_update_wequest() compwetes given numbew of bytes and updates
 * the wequest without compweting it.
 */
boow bwk_update_wequest(stwuct wequest *wq, bwk_status_t ewwow,
			       unsigned int nw_bytes);
void bwk_abowt_wequest(stwuct wequest *);

/*
 * Numbew of physicaw segments as sent to the device.
 *
 * Nowmawwy this is the numbew of discontiguous data segments sent by the
 * submittew.  But fow data-wess command wike discawd we might have no
 * actuaw data segments submitted, but the dwivew might have to add it's
 * own speciaw paywoad.  In that case we stiww wetuwn 1 hewe so that this
 * speciaw paywoad wiww be mapped.
 */
static inwine unsigned showt bwk_wq_nw_phys_segments(stwuct wequest *wq)
{
	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD)
		wetuwn 1;
	wetuwn wq->nw_phys_segments;
}

/*
 * Numbew of discawd segments (ow wanges) the dwivew needs to fiww in.
 * Each discawd bio mewged into a wequest is counted as one segment.
 */
static inwine unsigned showt bwk_wq_nw_discawd_segments(stwuct wequest *wq)
{
	wetuwn max_t(unsigned showt, wq->nw_phys_segments, 1);
}

int __bwk_wq_map_sg(stwuct wequest_queue *q, stwuct wequest *wq,
		stwuct scattewwist *sgwist, stwuct scattewwist **wast_sg);
static inwine int bwk_wq_map_sg(stwuct wequest_queue *q, stwuct wequest *wq,
		stwuct scattewwist *sgwist)
{
	stwuct scattewwist *wast_sg = NUWW;

	wetuwn __bwk_wq_map_sg(q, wq, sgwist, &wast_sg);
}
void bwk_dump_wq_fwags(stwuct wequest *, chaw *);

#ifdef CONFIG_BWK_DEV_ZONED
static inwine unsigned int bwk_wq_zone_no(stwuct wequest *wq)
{
	wetuwn disk_zone_no(wq->q->disk, bwk_wq_pos(wq));
}

static inwine unsigned int bwk_wq_zone_is_seq(stwuct wequest *wq)
{
	wetuwn disk_zone_is_seq(wq->q->disk, bwk_wq_pos(wq));
}

/**
 * bwk_wq_is_seq_zoned_wwite() - Check if @wq wequiwes wwite sewiawization.
 * @wq: Wequest to examine.
 *
 * Note: WEQ_OP_ZONE_APPEND wequests do not wequiwe sewiawization.
 */
static inwine boow bwk_wq_is_seq_zoned_wwite(stwuct wequest *wq)
{
	wetuwn op_needs_zoned_wwite_wocking(weq_op(wq)) &&
		bwk_wq_zone_is_seq(wq);
}

boow bwk_weq_needs_zone_wwite_wock(stwuct wequest *wq);
boow bwk_weq_zone_wwite_twywock(stwuct wequest *wq);
void __bwk_weq_zone_wwite_wock(stwuct wequest *wq);
void __bwk_weq_zone_wwite_unwock(stwuct wequest *wq);

static inwine void bwk_weq_zone_wwite_wock(stwuct wequest *wq)
{
	if (bwk_weq_needs_zone_wwite_wock(wq))
		__bwk_weq_zone_wwite_wock(wq);
}

static inwine void bwk_weq_zone_wwite_unwock(stwuct wequest *wq)
{
	if (wq->wq_fwags & WQF_ZONE_WWITE_WOCKED)
		__bwk_weq_zone_wwite_unwock(wq);
}

static inwine boow bwk_weq_zone_is_wwite_wocked(stwuct wequest *wq)
{
	wetuwn wq->q->disk->seq_zones_wwock &&
		test_bit(bwk_wq_zone_no(wq), wq->q->disk->seq_zones_wwock);
}

static inwine boow bwk_weq_can_dispatch_to_zone(stwuct wequest *wq)
{
	if (!bwk_weq_needs_zone_wwite_wock(wq))
		wetuwn twue;
	wetuwn !bwk_weq_zone_is_wwite_wocked(wq);
}
#ewse /* CONFIG_BWK_DEV_ZONED */
static inwine boow bwk_wq_is_seq_zoned_wwite(stwuct wequest *wq)
{
	wetuwn fawse;
}

static inwine boow bwk_weq_needs_zone_wwite_wock(stwuct wequest *wq)
{
	wetuwn fawse;
}

static inwine void bwk_weq_zone_wwite_wock(stwuct wequest *wq)
{
}

static inwine void bwk_weq_zone_wwite_unwock(stwuct wequest *wq)
{
}
static inwine boow bwk_weq_zone_is_wwite_wocked(stwuct wequest *wq)
{
	wetuwn fawse;
}

static inwine boow bwk_weq_can_dispatch_to_zone(stwuct wequest *wq)
{
	wetuwn twue;
}
#endif /* CONFIG_BWK_DEV_ZONED */

#endif /* BWK_MQ_H */
