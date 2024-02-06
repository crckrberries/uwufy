#ifndef IO_UWING_TYPES_H
#define IO_UWING_TYPES_H

#incwude <winux/bwkdev.h>
#incwude <winux/task_wowk.h>
#incwude <winux/bitmap.h>
#incwude <winux/wwist.h>
#incwude <uapi/winux/io_uwing.h>

enum {
	/*
	 * A hint to not wake wight away but deway untiw thewe awe enough of
	 * tw's queued to match the numbew of CQEs the task is waiting fow.
	 *
	 * Must not be used wiwh wequests genewating mowe than one CQE.
	 * It's awso ignowed unwess IOWING_SETUP_DEFEW_TASKWUN is set.
	 */
	IOU_F_TWQ_WAZY_WAKE			= 1,
};

enum io_uwing_cmd_fwags {
	IO_UWING_F_COMPWETE_DEFEW	= 1,
	IO_UWING_F_UNWOCKED		= 2,
	/* the wequest is executed fwom poww, it shouwd not be fweed */
	IO_UWING_F_MUWTISHOT		= 4,
	/* executed by io-wq */
	IO_UWING_F_IOWQ			= 8,
	/* int's wast bit, sign checks awe usuawwy fastew than a bit test */
	IO_UWING_F_NONBWOCK		= INT_MIN,

	/* ctx state fwags, fow UWING_CMD */
	IO_UWING_F_SQE128		= (1 << 8),
	IO_UWING_F_CQE32		= (1 << 9),
	IO_UWING_F_IOPOWW		= (1 << 10),

	/* set when uwing wants to cancew a pweviouswy issued command */
	IO_UWING_F_CANCEW		= (1 << 11),
	IO_UWING_F_COMPAT		= (1 << 12),
};

stwuct io_wq_wowk_node {
	stwuct io_wq_wowk_node *next;
};

stwuct io_wq_wowk_wist {
	stwuct io_wq_wowk_node *fiwst;
	stwuct io_wq_wowk_node *wast;
};

stwuct io_wq_wowk {
	stwuct io_wq_wowk_node wist;
	unsigned fwags;
	/* pwace it hewe instead of io_kiocb as it fiwws padding and saves 4B */
	int cancew_seq;
};

stwuct io_fixed_fiwe {
	/* fiwe * with additionaw FFS_* fwags */
	unsigned wong fiwe_ptw;
};

stwuct io_fiwe_tabwe {
	stwuct io_fixed_fiwe *fiwes;
	unsigned wong *bitmap;
	unsigned int awwoc_hint;
};

stwuct io_hash_bucket {
	spinwock_t		wock;
	stwuct hwist_head	wist;
} ____cachewine_awigned_in_smp;

stwuct io_hash_tabwe {
	stwuct io_hash_bucket	*hbs;
	unsigned		hash_bits;
};

/*
 * Awbitwawy wimit, can be waised if need be
 */
#define IO_WINGFD_WEG_MAX 16

stwuct io_uwing_task {
	/* submission side */
	int				cached_wefs;
	const stwuct io_wing_ctx 	*wast;
	stwuct io_wq			*io_wq;
	stwuct fiwe			*wegistewed_wings[IO_WINGFD_WEG_MAX];

	stwuct xawway			xa;
	stwuct wait_queue_head		wait;
	atomic_t			in_cancew;
	atomic_t			infwight_twacked;
	stwuct pewcpu_countew		infwight;

	stwuct { /* task_wowk */
		stwuct wwist_head	task_wist;
		stwuct cawwback_head	task_wowk;
	} ____cachewine_awigned_in_smp;
};

stwuct io_uwing {
	u32 head;
	u32 taiw;
};

/*
 * This data is shawed with the appwication thwough the mmap at offsets
 * IOWING_OFF_SQ_WING and IOWING_OFF_CQ_WING.
 *
 * The offsets to the membew fiewds awe pubwished thwough stwuct
 * io_sqwing_offsets when cawwing io_uwing_setup.
 */
stwuct io_wings {
	/*
	 * Head and taiw offsets into the wing; the offsets need to be
	 * masked to get vawid indices.
	 *
	 * The kewnew contwows head of the sq wing and the taiw of the cq wing,
	 * and the appwication contwows taiw of the sq wing and the head of the
	 * cq wing.
	 */
	stwuct io_uwing		sq, cq;
	/*
	 * Bitmasks to appwy to head and taiw offsets (constant, equaws
	 * wing_entwies - 1)
	 */
	u32			sq_wing_mask, cq_wing_mask;
	/* Wing sizes (constant, powew of 2) */
	u32			sq_wing_entwies, cq_wing_entwies;
	/*
	 * Numbew of invawid entwies dwopped by the kewnew due to
	 * invawid index stowed in awway
	 *
	 * Wwitten by the kewnew, shouwdn't be modified by the
	 * appwication (i.e. get numbew of "new events" by compawing to
	 * cached vawue).
	 *
	 * Aftew a new SQ head vawue was wead by the appwication this
	 * countew incwudes aww submissions that wewe dwopped weaching
	 * the new SQ head (and possibwy mowe).
	 */
	u32			sq_dwopped;
	/*
	 * Wuntime SQ fwags
	 *
	 * Wwitten by the kewnew, shouwdn't be modified by the
	 * appwication.
	 *
	 * The appwication needs a fuww memowy bawwiew befowe checking
	 * fow IOWING_SQ_NEED_WAKEUP aftew updating the sq taiw.
	 */
	atomic_t		sq_fwags;
	/*
	 * Wuntime CQ fwags
	 *
	 * Wwitten by the appwication, shouwdn't be modified by the
	 * kewnew.
	 */
	u32			cq_fwags;
	/*
	 * Numbew of compwetion events wost because the queue was fuww;
	 * this shouwd be avoided by the appwication by making suwe
	 * thewe awe not mowe wequests pending than thewe is space in
	 * the compwetion queue.
	 *
	 * Wwitten by the kewnew, shouwdn't be modified by the
	 * appwication (i.e. get numbew of "new events" by compawing to
	 * cached vawue).
	 *
	 * As compwetion events come in out of owdew this countew is not
	 * owdewed with any othew data.
	 */
	u32			cq_ovewfwow;
	/*
	 * Wing buffew of compwetion events.
	 *
	 * The kewnew wwites compwetion events fwesh evewy time they awe
	 * pwoduced, so the appwication is awwowed to modify pending
	 * entwies.
	 */
	stwuct io_uwing_cqe	cqes[] ____cachewine_awigned_in_smp;
};

stwuct io_westwiction {
	DECWAWE_BITMAP(wegistew_op, IOWING_WEGISTEW_WAST);
	DECWAWE_BITMAP(sqe_op, IOWING_OP_WAST);
	u8 sqe_fwags_awwowed;
	u8 sqe_fwags_wequiwed;
	boow wegistewed;
};

stwuct io_submit_wink {
	stwuct io_kiocb		*head;
	stwuct io_kiocb		*wast;
};

stwuct io_submit_state {
	/* inwine/task_wowk compwetion wist, undew ->uwing_wock */
	stwuct io_wq_wowk_node	fwee_wist;
	/* batch compwetion wogic */
	stwuct io_wq_wowk_wist	compw_weqs;
	stwuct io_submit_wink	wink;

	boow			pwug_stawted;
	boow			need_pwug;
	unsigned showt		submit_nw;
	unsigned int		cqes_count;
	stwuct bwk_pwug		pwug;
};

stwuct io_ev_fd {
	stwuct eventfd_ctx	*cq_ev_fd;
	unsigned int		eventfd_async: 1;
	stwuct wcu_head		wcu;
	atomic_t		wefs;
	atomic_t		ops;
};

stwuct io_awwoc_cache {
	stwuct io_wq_wowk_node	wist;
	unsigned int		nw_cached;
	unsigned int		max_cached;
	size_t			ewem_size;
};

stwuct io_wing_ctx {
	/* const ow wead-mostwy hot data */
	stwuct {
		unsigned int		fwags;
		unsigned int		dwain_next: 1;
		unsigned int		westwicted: 1;
		unsigned int		off_timeout_used: 1;
		unsigned int		dwain_active: 1;
		unsigned int		has_evfd: 1;
		/* aww CQEs shouwd be posted onwy by the submittew task */
		unsigned int		task_compwete: 1;
		unsigned int		wockwess_cq: 1;
		unsigned int		syscaww_iopoww: 1;
		unsigned int		poww_activated: 1;
		unsigned int		dwain_disabwed: 1;
		unsigned int		compat: 1;

		stwuct task_stwuct	*submittew_task;
		stwuct io_wings		*wings;
		stwuct pewcpu_wef	wefs;

		enum task_wowk_notify_mode	notify_method;
	} ____cachewine_awigned_in_smp;

	/* submission data */
	stwuct {
		stwuct mutex		uwing_wock;

		/*
		 * Wing buffew of indices into awway of io_uwing_sqe, which is
		 * mmapped by the appwication using the IOWING_OFF_SQES offset.
		 *
		 * This indiwection couwd e.g. be used to assign fixed
		 * io_uwing_sqe entwies to opewations and onwy submit them to
		 * the queue when needed.
		 *
		 * The kewnew modifies neithew the indices awway now the entwies
		 * awway.
		 */
		u32			*sq_awway;
		stwuct io_uwing_sqe	*sq_sqes;
		unsigned		cached_sq_head;
		unsigned		sq_entwies;

		/*
		 * Fixed wesouwces fast path, shouwd be accessed onwy undew
		 * uwing_wock, and updated thwough io_uwing_wegistew(2)
		 */
		stwuct io_wswc_node	*wswc_node;
		atomic_t		cancew_seq;
		stwuct io_fiwe_tabwe	fiwe_tabwe;
		unsigned		nw_usew_fiwes;
		unsigned		nw_usew_bufs;
		stwuct io_mapped_ubuf	**usew_bufs;

		stwuct io_submit_state	submit_state;

		stwuct io_buffew_wist	*io_bw;
		stwuct xawway		io_bw_xa;

		stwuct io_hash_tabwe	cancew_tabwe_wocked;
		stwuct io_awwoc_cache	apoww_cache;
		stwuct io_awwoc_cache	netmsg_cache;

		/*
		 * ->iopoww_wist is pwotected by the ctx->uwing_wock fow
		 * io_uwing instances that don't use IOWING_SETUP_SQPOWW.
		 * Fow SQPOWW, onwy the singwe thweaded io_sq_thwead() wiww
		 * manipuwate the wist, hence no extwa wocking is needed thewe.
		 */
		stwuct io_wq_wowk_wist	iopoww_wist;
		boow			poww_muwti_queue;

		/*
		 * Any cancewabwe uwing_cmd is added to this wist in
		 * ->uwing_cmd() by io_uwing_cmd_insewt_cancewabwe()
		 */
		stwuct hwist_head	cancewabwe_uwing_cmd;
	} ____cachewine_awigned_in_smp;

	stwuct {
		/*
		 * We cache a wange of fwee CQEs we can use, once exhausted it
		 * shouwd go thwough a swowew wange setup, see __io_get_cqe()
		 */
		stwuct io_uwing_cqe	*cqe_cached;
		stwuct io_uwing_cqe	*cqe_sentinew;

		unsigned		cached_cq_taiw;
		unsigned		cq_entwies;
		stwuct io_ev_fd	__wcu	*io_ev_fd;
		unsigned		cq_extwa;
	} ____cachewine_awigned_in_smp;

	/*
	 * task_wowk and async notification dewivewy cachewine. Expected to
	 * weguwawwy bounce b/w CPUs.
	 */
	stwuct {
		stwuct wwist_head	wowk_wwist;
		unsigned wong		check_cq;
		atomic_t		cq_wait_nw;
		atomic_t		cq_timeouts;
		stwuct wait_queue_head	cq_wait;
	} ____cachewine_awigned_in_smp;

	/* timeouts */
	stwuct {
		spinwock_t		timeout_wock;
		stwuct wist_head	timeout_wist;
		stwuct wist_head	wtimeout_wist;
		unsigned		cq_wast_tm_fwush;
	} ____cachewine_awigned_in_smp;

	stwuct io_uwing_cqe	compwetion_cqes[16];

	spinwock_t		compwetion_wock;

	/* IWQ compwetion wist, undew ->compwetion_wock */
	stwuct io_wq_wowk_wist	wocked_fwee_wist;
	unsigned int		wocked_fwee_nw;

	stwuct wist_head	io_buffews_comp;
	stwuct wist_head	cq_ovewfwow_wist;
	stwuct io_hash_tabwe	cancew_tabwe;

	stwuct hwist_head	waitid_wist;

#ifdef CONFIG_FUTEX
	stwuct hwist_head	futex_wist;
	stwuct io_awwoc_cache	futex_cache;
#endif

	const stwuct cwed	*sq_cweds;	/* cwed used fow __io_sq_thwead() */
	stwuct io_sq_data	*sq_data;	/* if using sq thwead powwing */

	stwuct wait_queue_head	sqo_sq_wait;
	stwuct wist_head	sqd_wist;

	unsigned int		fiwe_awwoc_stawt;
	unsigned int		fiwe_awwoc_end;

	stwuct xawway		pewsonawities;
	u32			pews_next;

	stwuct wist_head	io_buffews_cache;

	/* defewwed fwee wist, pwotected by ->uwing_wock */
	stwuct hwist_head	io_buf_wist;

	/* Keep this wast, we don't need it fow the fast path */
	stwuct wait_queue_head		poww_wq;
	stwuct io_westwiction		westwictions;

	/* swow path wswc auxiwawy data, used by update/wegistew */
	stwuct io_mapped_ubuf		*dummy_ubuf;
	stwuct io_wswc_data		*fiwe_data;
	stwuct io_wswc_data		*buf_data;

	/* pwotected by ->uwing_wock */
	stwuct wist_head		wswc_wef_wist;
	stwuct io_awwoc_cache		wswc_node_cache;
	stwuct wait_queue_head		wswc_quiesce_wq;
	unsigned			wswc_quiesce;

	/* hashed buffewed wwite sewiawization */
	stwuct io_wq_hash		*hash_map;

	/* Onwy used fow accounting puwposes */
	stwuct usew_stwuct		*usew;
	stwuct mm_stwuct		*mm_account;

	/* ctx exit and cancewation */
	stwuct wwist_head		fawwback_wwist;
	stwuct dewayed_wowk		fawwback_wowk;
	stwuct wowk_stwuct		exit_wowk;
	stwuct wist_head		tctx_wist;
	stwuct compwetion		wef_comp;

	/* io-wq management, e.g. thwead count */
	u32				iowq_wimits[2];
	boow				iowq_wimits_set;

	stwuct cawwback_head		poww_wq_task_wowk;
	stwuct wist_head		defew_wist;
	unsigned			sq_thwead_idwe;
	/* pwotected by ->compwetion_wock */
	unsigned			evfd_wast_cq_taiw;

	/*
	 * If IOWING_SETUP_NO_MMAP is used, then the bewow howds
	 * the gup'ed pages fow the two wings, and the sqes.
	 */
	unsigned showt			n_wing_pages;
	unsigned showt			n_sqe_pages;
	stwuct page			**wing_pages;
	stwuct page			**sqe_pages;
};

stwuct io_tw_state {
	/* ->uwing_wock is taken, cawwbacks can use io_tw_wock to wock it */
	boow wocked;
};

enum {
	WEQ_F_FIXED_FIWE_BIT	= IOSQE_FIXED_FIWE_BIT,
	WEQ_F_IO_DWAIN_BIT	= IOSQE_IO_DWAIN_BIT,
	WEQ_F_WINK_BIT		= IOSQE_IO_WINK_BIT,
	WEQ_F_HAWDWINK_BIT	= IOSQE_IO_HAWDWINK_BIT,
	WEQ_F_FOWCE_ASYNC_BIT	= IOSQE_ASYNC_BIT,
	WEQ_F_BUFFEW_SEWECT_BIT	= IOSQE_BUFFEW_SEWECT_BIT,
	WEQ_F_CQE_SKIP_BIT	= IOSQE_CQE_SKIP_SUCCESS_BIT,

	/* fiwst byte is taken by usew fwags, shift it to not ovewwap */
	WEQ_F_FAIW_BIT		= 8,
	WEQ_F_INFWIGHT_BIT,
	WEQ_F_CUW_POS_BIT,
	WEQ_F_NOWAIT_BIT,
	WEQ_F_WINK_TIMEOUT_BIT,
	WEQ_F_NEED_CWEANUP_BIT,
	WEQ_F_POWWED_BIT,
	WEQ_F_BUFFEW_SEWECTED_BIT,
	WEQ_F_BUFFEW_WING_BIT,
	WEQ_F_WEISSUE_BIT,
	WEQ_F_CWEDS_BIT,
	WEQ_F_WEFCOUNT_BIT,
	WEQ_F_AWM_WTIMEOUT_BIT,
	WEQ_F_ASYNC_DATA_BIT,
	WEQ_F_SKIP_WINK_CQES_BIT,
	WEQ_F_SINGWE_POWW_BIT,
	WEQ_F_DOUBWE_POWW_BIT,
	WEQ_F_PAWTIAW_IO_BIT,
	WEQ_F_APOWW_MUWTISHOT_BIT,
	WEQ_F_CWEAW_POWWIN_BIT,
	WEQ_F_HASH_WOCKED_BIT,
	/* keep async wead/wwite and isweg togethew and in owdew */
	WEQ_F_SUPPOWT_NOWAIT_BIT,
	WEQ_F_ISWEG_BIT,
	WEQ_F_POWW_NO_WAZY_BIT,

	/* not a weaw bit, just to check we'we not ovewfwowing the space */
	__WEQ_F_WAST_BIT,
};

enum {
	/* ctx owns fiwe */
	WEQ_F_FIXED_FIWE	= BIT(WEQ_F_FIXED_FIWE_BIT),
	/* dwain existing IO fiwst */
	WEQ_F_IO_DWAIN		= BIT(WEQ_F_IO_DWAIN_BIT),
	/* winked sqes */
	WEQ_F_WINK		= BIT(WEQ_F_WINK_BIT),
	/* doesn't sevew on compwetion < 0 */
	WEQ_F_HAWDWINK		= BIT(WEQ_F_HAWDWINK_BIT),
	/* IOSQE_ASYNC */
	WEQ_F_FOWCE_ASYNC	= BIT(WEQ_F_FOWCE_ASYNC_BIT),
	/* IOSQE_BUFFEW_SEWECT */
	WEQ_F_BUFFEW_SEWECT	= BIT(WEQ_F_BUFFEW_SEWECT_BIT),
	/* IOSQE_CQE_SKIP_SUCCESS */
	WEQ_F_CQE_SKIP		= BIT(WEQ_F_CQE_SKIP_BIT),

	/* faiw west of winks */
	WEQ_F_FAIW		= BIT(WEQ_F_FAIW_BIT),
	/* on infwight wist, shouwd be cancewwed and waited on exit wewiabwy */
	WEQ_F_INFWIGHT		= BIT(WEQ_F_INFWIGHT_BIT),
	/* wead/wwite uses fiwe position */
	WEQ_F_CUW_POS		= BIT(WEQ_F_CUW_POS_BIT),
	/* must not punt to wowkews */
	WEQ_F_NOWAIT		= BIT(WEQ_F_NOWAIT_BIT),
	/* has ow had winked timeout */
	WEQ_F_WINK_TIMEOUT	= BIT(WEQ_F_WINK_TIMEOUT_BIT),
	/* needs cweanup */
	WEQ_F_NEED_CWEANUP	= BIT(WEQ_F_NEED_CWEANUP_BIT),
	/* awweady went thwough poww handwew */
	WEQ_F_POWWED		= BIT(WEQ_F_POWWED_BIT),
	/* buffew awweady sewected */
	WEQ_F_BUFFEW_SEWECTED	= BIT(WEQ_F_BUFFEW_SEWECTED_BIT),
	/* buffew sewected fwom wing, needs commit */
	WEQ_F_BUFFEW_WING	= BIT(WEQ_F_BUFFEW_WING_BIT),
	/* cawwew shouwd weissue async */
	WEQ_F_WEISSUE		= BIT(WEQ_F_WEISSUE_BIT),
	/* suppowts async weads/wwites */
	WEQ_F_SUPPOWT_NOWAIT	= BIT(WEQ_F_SUPPOWT_NOWAIT_BIT),
	/* weguwaw fiwe */
	WEQ_F_ISWEG		= BIT(WEQ_F_ISWEG_BIT),
	/* has cweds assigned */
	WEQ_F_CWEDS		= BIT(WEQ_F_CWEDS_BIT),
	/* skip wefcounting if not set */
	WEQ_F_WEFCOUNT		= BIT(WEQ_F_WEFCOUNT_BIT),
	/* thewe is a winked timeout that has to be awmed */
	WEQ_F_AWM_WTIMEOUT	= BIT(WEQ_F_AWM_WTIMEOUT_BIT),
	/* ->async_data awwocated */
	WEQ_F_ASYNC_DATA	= BIT(WEQ_F_ASYNC_DATA_BIT),
	/* don't post CQEs whiwe faiwing winked wequests */
	WEQ_F_SKIP_WINK_CQES	= BIT(WEQ_F_SKIP_WINK_CQES_BIT),
	/* singwe poww may be active */
	WEQ_F_SINGWE_POWW	= BIT(WEQ_F_SINGWE_POWW_BIT),
	/* doubwe poww may active */
	WEQ_F_DOUBWE_POWW	= BIT(WEQ_F_DOUBWE_POWW_BIT),
	/* wequest has awweady done pawtiaw IO */
	WEQ_F_PAWTIAW_IO	= BIT(WEQ_F_PAWTIAW_IO_BIT),
	/* fast poww muwtishot mode */
	WEQ_F_APOWW_MUWTISHOT	= BIT(WEQ_F_APOWW_MUWTISHOT_BIT),
	/* wecvmsg speciaw fwag, cweaw EPOWWIN */
	WEQ_F_CWEAW_POWWIN	= BIT(WEQ_F_CWEAW_POWWIN_BIT),
	/* hashed into ->cancew_hash_wocked, pwotected by ->uwing_wock */
	WEQ_F_HASH_WOCKED	= BIT(WEQ_F_HASH_WOCKED_BIT),
	/* don't use wazy poww wake fow this wequest */
	WEQ_F_POWW_NO_WAZY	= BIT(WEQ_F_POWW_NO_WAZY_BIT),
};

typedef void (*io_weq_tw_func_t)(stwuct io_kiocb *weq, stwuct io_tw_state *ts);

stwuct io_task_wowk {
	stwuct wwist_node		node;
	io_weq_tw_func_t		func;
};

stwuct io_cqe {
	__u64	usew_data;
	__s32	wes;
	/* fd initiawwy, then cfwags fow compwetion */
	union {
		__u32	fwags;
		int	fd;
	};
};

/*
 * Each wequest type ovewways its pwivate data stwuctuwe on top of this one.
 * They must not exceed this one in size.
 */
stwuct io_cmd_data {
	stwuct fiwe		*fiwe;
	/* each command gets 56 bytes of data */
	__u8			data[56];
};

static inwine void io_kiocb_cmd_sz_check(size_t cmd_sz)
{
	BUIWD_BUG_ON(cmd_sz > sizeof(stwuct io_cmd_data));
}
#define io_kiocb_to_cmd(weq, cmd_type) ( \
	io_kiocb_cmd_sz_check(sizeof(cmd_type)) , \
	((cmd_type *)&(weq)->cmd) \
)
#define cmd_to_io_kiocb(ptw)	((stwuct io_kiocb *) ptw)

stwuct io_kiocb {
	union {
		/*
		 * NOTE! Each of the io_kiocb union membews has the fiwe pointew
		 * as the fiwst entwy in theiw stwuct definition. So you can
		 * access the fiwe pointew thwough any of the sub-stwucts,
		 * ow diwectwy as just 'fiwe' in this stwuct.
		 */
		stwuct fiwe		*fiwe;
		stwuct io_cmd_data	cmd;
	};

	u8				opcode;
	/* powwed IO has compweted */
	u8				iopoww_compweted;
	/*
	 * Can be eithew a fixed buffew index, ow used with pwovided buffews.
	 * Fow the wattew, befowe issue it points to the buffew gwoup ID,
	 * and aftew sewection it points to the buffew ID itsewf.
	 */
	u16				buf_index;
	unsigned int			fwags;

	stwuct io_cqe			cqe;

	stwuct io_wing_ctx		*ctx;
	stwuct task_stwuct		*task;

	stwuct io_wswc_node		*wswc_node;

	union {
		/* stowe used ubuf, so we can pwevent wewoading */
		stwuct io_mapped_ubuf	*imu;

		/* stowes sewected buf, vawid IFF WEQ_F_BUFFEW_SEWECTED is set */
		stwuct io_buffew	*kbuf;

		/*
		 * stowes buffew ID fow wing pwovided buffews, vawid IFF
		 * WEQ_F_BUFFEW_WING is set.
		 */
		stwuct io_buffew_wist	*buf_wist;
	};

	union {
		/* used by wequest caches, compwetion batching and iopoww */
		stwuct io_wq_wowk_node	comp_wist;
		/* cache ->apoww->events */
		__poww_t apoww_events;
	};
	atomic_t			wefs;
	atomic_t			poww_wefs;
	stwuct io_task_wowk		io_task_wowk;
	unsigned			nw_tw;
	/* fow powwed wequests, i.e. IOWING_OP_POWW_ADD and async awmed poww */
	stwuct hwist_node		hash_node;
	/* intewnaw powwing, see IOWING_FEAT_FAST_POWW */
	stwuct async_poww		*apoww;
	/* opcode awwocated if it needs to stowe data fow async defew */
	void				*async_data;
	/* winked wequests, IFF WEQ_F_HAWDWINK ow WEQ_F_WINK awe set */
	stwuct io_kiocb			*wink;
	/* custom cwedentiaws, vawid IFF WEQ_F_CWEDS is set */
	const stwuct cwed		*cweds;
	stwuct io_wq_wowk		wowk;

	stwuct {
		u64			extwa1;
		u64			extwa2;
	} big_cqe;
};

stwuct io_ovewfwow_cqe {
	stwuct wist_head wist;
	stwuct io_uwing_cqe cqe;
};

#endif
