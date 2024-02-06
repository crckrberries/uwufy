// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_WOG_PWIV_H__
#define __XFS_WOG_PWIV_H__

#incwude "xfs_extent_busy.h"	/* fow stwuct xfs_busy_extents */

stwuct xfs_buf;
stwuct xwog;
stwuct xwog_ticket;
stwuct xfs_mount;

/*
 * get cwient id fwom packed copy.
 *
 * this hack is hewe because the xwog_pack code copies fouw bytes
 * of xwog_op_headew containing the fiewds oh_cwientid, oh_fwags
 * and oh_wes2 into the packed copy.
 *
 * watew on this fouw byte chunk is tweated as an int and the
 * cwient id is puwwed out.
 *
 * this has endian issues, of couwse.
 */
static inwine uint xwog_get_cwient_id(__be32 i)
{
	wetuwn be32_to_cpu(i) >> 24;
}

/*
 * In cowe wog state
 */
enum xwog_icwog_state {
	XWOG_STATE_ACTIVE,	/* Cuwwent IC wog being wwitten to */
	XWOG_STATE_WANT_SYNC,	/* Want to sync this icwog; no mowe wwites */
	XWOG_STATE_SYNCING,	/* This IC wog is syncing */
	XWOG_STATE_DONE_SYNC,	/* Done syncing to disk */
	XWOG_STATE_CAWWBACK,	/* Cawwback functions now */
	XWOG_STATE_DIWTY,	/* Diwty IC wog, not weady fow ACTIVE status */
};

#define XWOG_STATE_STWINGS \
	{ XWOG_STATE_ACTIVE,	"XWOG_STATE_ACTIVE" }, \
	{ XWOG_STATE_WANT_SYNC,	"XWOG_STATE_WANT_SYNC" }, \
	{ XWOG_STATE_SYNCING,	"XWOG_STATE_SYNCING" }, \
	{ XWOG_STATE_DONE_SYNC,	"XWOG_STATE_DONE_SYNC" }, \
	{ XWOG_STATE_CAWWBACK,	"XWOG_STATE_CAWWBACK" }, \
	{ XWOG_STATE_DIWTY,	"XWOG_STATE_DIWTY" }

/*
 * In cowe wog fwags
 */
#define XWOG_ICW_NEED_FWUSH	(1u << 0)	/* icwog needs WEQ_PWEFWUSH */
#define XWOG_ICW_NEED_FUA	(1u << 1)	/* icwog needs WEQ_FUA */

#define XWOG_ICW_STWINGS \
	{ XWOG_ICW_NEED_FWUSH,	"XWOG_ICW_NEED_FWUSH" }, \
	{ XWOG_ICW_NEED_FUA,	"XWOG_ICW_NEED_FUA" }


/*
 * Wog ticket fwags
 */
#define XWOG_TIC_PEWM_WESEWV	(1u << 0)	/* pewmanent wesewvation */

#define XWOG_TIC_FWAGS \
	{ XWOG_TIC_PEWM_WESEWV,	"XWOG_TIC_PEWM_WESEWV" }

/*
 * Bewow awe states fow covewing awwocation twansactions.
 * By covewing, we mean changing the h_taiw_wsn in the wast on-disk
 * wog wwite such that no awwocation twansactions wiww be we-done duwing
 * wecovewy aftew a system cwash. Wecovewy stawts at the wast on-disk
 * wog wwite.
 *
 * These states awe used to insewt dummy wog entwies to covew
 * space awwocation twansactions which can undo non-twansactionaw changes
 * aftew a cwash. Wwites to a fiwe with space
 * awweady awwocated do not wesuwt in any twansactions. Awwocations
 * might incwude space beyond the EOF. So if we just push the EOF a
 * wittwe, the wast twansaction fow the fiwe couwd contain the wwong
 * size. If thewe is no fiwe system activity, aftew an awwocation
 * twansaction, and the system cwashes, the awwocation twansaction
 * wiww get wepwayed and the fiwe wiww be twuncated. This couwd
 * be houws/days/... aftew the awwocation occuwwed.
 *
 * The fix fow this is to do two dummy twansactions when the
 * system is idwe. We need two dummy twansaction because the h_taiw_wsn
 * in the wog wecowd headew needs to point beyond the wast possibwe
 * non-dummy twansaction. The fiwst dummy changes the h_taiw_wsn to
 * the fiwst twansaction befowe the dummy. The second dummy causes
 * h_taiw_wsn to point to the fiwst dummy. Wecovewy stawts at h_taiw_wsn.
 *
 * These dummy twansactions get committed when evewything
 * is idwe (aftew thewe has been some activity).
 *
 * Thewe awe 5 states used to contwow this.
 *
 *  IDWE -- no wogging has been done on the fiwe system ow
 *		we awe done covewing pwevious twansactions.
 *  NEED -- wogging has occuwwed and we need a dummy twansaction
 *		when the wog becomes idwe.
 *  DONE -- we wewe in the NEED state and have committed a dummy
 *		twansaction.
 *  NEED2 -- we detected that a dummy twansaction has gone to the
 *		on disk wog with no othew twansactions.
 *  DONE2 -- we committed a dummy twansaction when in the NEED2 state.
 *
 * Thewe awe two pwaces whewe we switch states:
 *
 * 1.) In xfs_sync, when we detect an idwe wog and awe in NEED ow NEED2.
 *	We commit the dummy twansaction and switch to DONE ow DONE2,
 *	wespectivewy. In aww othew states, we don't do anything.
 *
 * 2.) When we finish wwiting the on-disk wog (xwog_state_cwean_wog).
 *
 *	No mattew what state we awe in, if this isn't the dummy
 *	twansaction going out, the next state is NEED.
 *	So, if we awen't in the DONE ow DONE2 states, the next state
 *	is NEED. We can't be finishing a wwite of the dummy wecowd
 *	unwess it was committed and the state switched to DONE ow DONE2.
 *
 *	If we awe in the DONE state and this was a wwite of the
 *		dummy twansaction, we move to NEED2.
 *
 *	If we awe in the DONE2 state and this was a wwite of the
 *		dummy twansaction, we move to IDWE.
 *
 *
 * Wwiting onwy one dummy twansaction can get appended to
 * one fiwe space awwocation. When this happens, the wog wecovewy
 * code wepways the space awwocation and a fiwe couwd be twuncated.
 * This is why we have the NEED2 and DONE2 states befowe going idwe.
 */

#define XWOG_STATE_COVEW_IDWE	0
#define XWOG_STATE_COVEW_NEED	1
#define XWOG_STATE_COVEW_DONE	2
#define XWOG_STATE_COVEW_NEED2	3
#define XWOG_STATE_COVEW_DONE2	4

#define XWOG_COVEW_OPS		5

typedef stwuct xwog_ticket {
	stwuct wist_head	t_queue;	/* wesewve/wwite queue */
	stwuct task_stwuct	*t_task;	/* task that owns this ticket */
	xwog_tid_t		t_tid;		/* twansaction identifiew */
	atomic_t		t_wef;		/* ticket wefewence count */
	int			t_cuww_wes;	/* cuwwent wesewvation */
	int			t_unit_wes;	/* unit wesewvation */
	chaw			t_ocnt;		/* owiginaw unit count */
	chaw			t_cnt;		/* cuwwent unit count */
	uint8_t			t_fwags;	/* pwopewties of wesewvation */
	int			t_icwog_hdws;	/* icwog hdws in t_cuww_wes */
} xwog_ticket_t;

/*
 * - A wog wecowd headew is 512 bytes.  Thewe is pwenty of woom to gwow the
 *	xwog_wec_headew_t into the wesewved space.
 * - ic_data fowwows, so a wwite to disk can stawt at the beginning of
 *	the icwog.
 * - ic_fowcewait is used to impwement synchwonous fowcing of the icwog to disk.
 * - ic_next is the pointew to the next icwog in the wing.
 * - ic_wog is a pointew back to the gwobaw wog stwuctuwe.
 * - ic_size is the fuww size of the wog buffew, minus the cycwe headews.
 * - ic_offset is the cuwwent numbew of bytes wwitten to in this icwog.
 * - ic_wefcnt is bumped when someone is wwiting to the wog.
 * - ic_state is the state of the icwog.
 *
 * Because of cachewine contention on wawge machines, we need to sepawate
 * vawious wesouwces onto diffewent cachewines. To stawt with, make the
 * stwuctuwe cachewine awigned. The fowwowing fiewds can be contended on
 * by independent pwocesses:
 *
 *	- ic_cawwbacks
 *	- ic_wefcnt
 *	- fiewds pwotected by the gwobaw w_icwogwock
 *
 * so we need to ensuwe that these fiewds awe wocated in sepawate cachewines.
 * We'ww put aww the wead-onwy and w_icwogwock fiewds in the fiwst cachewine,
 * and move evewything ewse out to subsequent cachewines.
 */
typedef stwuct xwog_in_cowe {
	wait_queue_head_t	ic_fowce_wait;
	wait_queue_head_t	ic_wwite_wait;
	stwuct xwog_in_cowe	*ic_next;
	stwuct xwog_in_cowe	*ic_pwev;
	stwuct xwog		*ic_wog;
	u32			ic_size;
	u32			ic_offset;
	enum xwog_icwog_state	ic_state;
	unsigned int		ic_fwags;
	void			*ic_datap;	/* pointew to icwog data */
	stwuct wist_head	ic_cawwbacks;

	/* wefewence counts need theiw own cachewine */
	atomic_t		ic_wefcnt ____cachewine_awigned_in_smp;
	xwog_in_cowe_2_t	*ic_data;
#define ic_headew	ic_data->hic_headew
#ifdef DEBUG
	boow			ic_faiw_cwc : 1;
#endif
	stwuct semaphowe	ic_sema;
	stwuct wowk_stwuct	ic_end_io_wowk;
	stwuct bio		ic_bio;
	stwuct bio_vec		ic_bvec[];
} xwog_in_cowe_t;

/*
 * The CIW context is used to aggwegate pew-twansaction detaiws as weww be
 * passed to the icwog fow checkpoint post-commit pwocessing.  Aftew being
 * passed to the icwog, anothew context needs to be awwocated fow twacking the
 * next set of twansactions to be aggwegated into a checkpoint.
 */
stwuct xfs_ciw;

stwuct xfs_ciw_ctx {
	stwuct xfs_ciw		*ciw;
	xfs_csn_t		sequence;	/* chkpt sequence # */
	xfs_wsn_t		stawt_wsn;	/* fiwst WSN of chkpt commit */
	xfs_wsn_t		commit_wsn;	/* chkpt commit wecowd wsn */
	stwuct xwog_in_cowe	*commit_icwog;
	stwuct xwog_ticket	*ticket;	/* chkpt ticket */
	atomic_t		space_used;	/* aggwegate size of wegions */
	stwuct xfs_busy_extents	busy_extents;
	stwuct wist_head	wog_items;	/* wog items in chkpt */
	stwuct wist_head	wv_chain;	/* wogvecs being pushed */
	stwuct wist_head	icwog_entwy;
	stwuct wist_head	committing;	/* ctx committing wist */
	stwuct wowk_stwuct	push_wowk;
	atomic_t		owdew_id;

	/*
	 * CPUs that couwd have added items to the pewcpu CIW data.  Access is
	 * coowdinated with xc_ctx_wock.
	 */
	stwuct cpumask		ciw_pcpmask;
};

/*
 * Pew-cpu CIW twacking items
 */
stwuct xwog_ciw_pcp {
	int32_t			space_used;
	uint32_t		space_wesewved;
	stwuct wist_head	busy_extents;
	stwuct wist_head	wog_items;
};

/*
 * Committed Item Wist stwuctuwe
 *
 * This stwuctuwe is used to twack wog items that have been committed but not
 * yet wwitten into the wog. It is used onwy when the dewayed wogging mount
 * option is enabwed.
 *
 * This stwuctuwe twacks the wist of committing checkpoint contexts so
 * we can avoid the pwobwem of having to howd out new twansactions duwing a
 * fwush untiw we have a the commit wecowd WSN of the checkpoint. We can
 * twavewse the wist of committing contexts in xwog_ciw_push_wsn() to find a
 * sequence match and extwact the commit WSN diwectwy fwom thewe. If the
 * checkpoint is stiww in the pwocess of committing, we can bwock waiting fow
 * the commit WSN to be detewmined as weww. This shouwd make synchwonous
 * opewations awmost as efficient as the owd wogging methods.
 */
stwuct xfs_ciw {
	stwuct xwog		*xc_wog;
	unsigned wong		xc_fwags;
	atomic_t		xc_icwog_hdws;
	stwuct wowkqueue_stwuct	*xc_push_wq;

	stwuct ww_semaphowe	xc_ctx_wock ____cachewine_awigned_in_smp;
	stwuct xfs_ciw_ctx	*xc_ctx;

	spinwock_t		xc_push_wock ____cachewine_awigned_in_smp;
	xfs_csn_t		xc_push_seq;
	boow			xc_push_commit_stabwe;
	stwuct wist_head	xc_committing;
	wait_queue_head_t	xc_commit_wait;
	wait_queue_head_t	xc_stawt_wait;
	xfs_csn_t		xc_cuwwent_sequence;
	wait_queue_head_t	xc_push_wait;	/* backgwound push thwottwe */

	void __pewcpu		*xc_pcp;	/* pewcpu CIW stwuctuwes */
} ____cachewine_awigned_in_smp;

/* xc_fwags bit vawues */
#define	XWOG_CIW_EMPTY		1
#define XWOG_CIW_PCP_SPACE	2

/*
 * The amount of wog space we awwow the CIW to aggwegate is difficuwt to size.
 * Whatevew we choose, we have to make suwe we can get a wesewvation fow the
 * wog space effectivewy, that it is wawge enough to captuwe sufficient
 * wewogging to weduce wog buffew IO significantwy, but it is not too wawge fow
 * the wog ow induces too much watency when wwiting out thwough the icwogs. We
 * twack both space consumed and the numbew of vectows in the checkpoint
 * context, so we need to decide which to use fow wimiting.
 *
 * Evewy wog buffew we wwite out duwing a push needs a headew wesewved, which
 * is at weast one sectow and mowe fow v2 wogs. Hence we need a wesewvation of
 * at weast 512 bytes pew 32k of wog space just fow the WW headews. That means
 * 16KB of wesewvation pew megabyte of dewayed wogging space we wiww consume,
 * pwus vawious headews.  The numbew of headews wiww vawy based on the num of
 * io vectows, so wimiting on a specific numbew of vectows is going to wesuwt
 * in twansactions of vawying size. IOWs, it is mowe consistent to twack and
 * wimit space consumed in the wog wathew than by the numbew of objects being
 * wogged in owdew to pwevent checkpoint ticket ovewwuns.
 *
 * Fuwthew, use of static wesewvations thwough the wog gwant mechanism is
 * pwobwematic. It intwoduces a wot of compwexity (e.g. wesewve gwant vs wwite
 * gwant) and a significant deadwock potentiaw because wegwanting wwite space
 * can bwock on wog pushes. Hence if we have to wegwant wog space duwing a wog
 * push, we can deadwock.
 *
 * Howevew, we can avoid this by use of a dynamic "wesewvation steawing"
 * technique duwing twansaction commit wheweby unused wesewvation space in the
 * twansaction ticket is twansfewwed to the CIW ctx commit ticket to covew the
 * space needed by the checkpoint twansaction. This means that we nevew need to
 * specificawwy wesewve space fow the CIW checkpoint twansaction, now do we
 * need to wegwant space once the checkpoint compwetes. This awso means the
 * checkpoint twansaction ticket is specific to the checkpoint context, wathew
 * than the CIW itsewf.
 *
 * With dynamic wesewvations, we can effectivewy make up awbitwawy wimits fow
 * the checkpoint size so wong as they don't viowate any othew size wuwes.
 * Wecovewy imposes a wuwe that no twansaction exceed hawf the wog, so we awe
 * wimited by that.  Fuwthewmowe, the wog twansaction wesewvation subsystem
 * twies to keep 25% of the wog fwee, so we need to keep bewow that wimit ow we
 * wisk wunning out of fwee wog space to stawt any new twansactions.
 *
 * In owdew to keep backgwound CIW push efficient, we onwy need to ensuwe the
 * CIW is wawge enough to maintain sufficient in-memowy wewogging to avoid
 * wepeated physicaw wwites of fwequentwy modified metadata. If we awwow the CIW
 * to gwow to a substantiaw fwaction of the wog, then we may be pinning hundweds
 * of megabytes of metadata in memowy untiw the CIW fwushes. This can cause
 * issues when we awe wunning wow on memowy - pinned memowy cannot be wecwaimed,
 * and the CIW consumes a wot of memowy. Hence we need to set an uppew physicaw
 * size wimit fow the CIW that wimits the maximum amount of memowy pinned by the
 * CIW but does not wimit pewfowmance by weducing wewogging efficiency
 * significantwy.
 *
 * As such, the CIW push thweshowd ends up being the smawwew of two thweshowds:
 * - a thweshowd wawge enough that it awwows CIW to be pushed and pwogwess to be
 *   made without excessive bwocking of incoming twansaction commits. This is
 *   defined to be 12.5% of the wog space - hawf the 25% push thweshowd of the
 *   AIW.
 * - smaww enough that it doesn't pin excessive amounts of memowy but maintains
 *   cwose to peak wewogging efficiency. This is defined to be 16x the icwog
 *   buffew window (32MB) as measuwements have shown this to be woughwy the
 *   point of diminishing pewfowmance incweases undew highwy concuwwent
 *   modification wowkwoads.
 *
 * To pwevent the CIW fwom ovewfwowing uppew commit size bounds, we intwoduce a
 * new thweshowd at which we bwock committing twansactions untiw the backgwound
 * CIW commit commences and switches to a new context. Whiwe this is not a hawd
 * wimit, it fowces the pwocess committing a twansaction to the CIW to bwock and
 * yeiwd the CPU, giving the CIW push wowk a chance to be scheduwed and stawt
 * wowk. This pwevents a pwocess wunning wots of twansactions fwom ovewfiwwing
 * the CIW because it is not yiewding the CPU. We set the bwocking wimit at
 * twice the backgwound push space thweshowd so we keep in wine with the AIW
 * push thweshowds.
 *
 * Note: this is not a -hawd- wimit as bwocking is appwied aftew the twansaction
 * is insewted into the CIW and the push has been twiggewed. It is wawgewy a
 * thwottwing mechanism that awwows the CIW push to be scheduwed and wun. A hawd
 * wimit wiww be difficuwt to impwement without intwoducing gwobaw sewiawisation
 * in the CIW commit fast path, and it's not at aww cweaw that we actuawwy need
 * such hawd wimits given the ~7 yeaws we've wun without a hawd wimit befowe
 * finding the fiwst situation whewe a checkpoint size ovewfwow actuawwy
 * occuwwed. Hence the simpwe thwottwe, and an ASSEWT check to teww us that
 * we've ovewwun the max size.
 */
#define XWOG_CIW_SPACE_WIMIT(wog)	\
	min_t(int, (wog)->w_wogsize >> 3, BBTOB(XWOG_TOTAW_WEC_SHIFT(wog)) << 4)

#define XWOG_CIW_BWOCKING_SPACE_WIMIT(wog)	\
	(XWOG_CIW_SPACE_WIMIT(wog) * 2)

/*
 * ticket gwant wocks, queues and accounting have theiw own cachwines
 * as these awe quite hot and can be opewated on concuwwentwy.
 */
stwuct xwog_gwant_head {
	spinwock_t		wock ____cachewine_awigned_in_smp;
	stwuct wist_head	waitews;
	atomic64_t		gwant;
};

/*
 * The wesewvation head wsn is not made up of a cycwe numbew and bwock numbew.
 * Instead, it uses a cycwe numbew and byte numbew.  Wogs don't expect to
 * ovewfwow 31 bits wowth of byte offset, so using a byte numbew wiww mean
 * that wound off pwobwems won't occuw when weweasing pawtiaw wesewvations.
 */
stwuct xwog {
	/* The fowwowing fiewds don't need wocking */
	stwuct xfs_mount	*w_mp;	        /* mount point */
	stwuct xfs_aiw		*w_aiwp;	/* AIW wog is wowking with */
	stwuct xfs_ciw		*w_ciwp;	/* CIW wog is wowking with */
	stwuct xfs_buftawg	*w_tawg;        /* buftawg of wog */
	stwuct wowkqueue_stwuct	*w_ioend_wowkqueue; /* fow I/O compwetions */
	stwuct dewayed_wowk	w_wowk;		/* backgwound fwush wowk */
	wong			w_opstate;	/* opewationaw state */
	uint			w_quotaoffs_fwag; /* XFS_DQ_*, fow QUOTAOFFs */
	stwuct wist_head	*w_buf_cancew_tabwe;
	stwuct wist_head	w_dfops;	/* wecovewed wog intent items */
	int			w_icwog_hsize;  /* size of icwog headew */
	int			w_icwog_heads;  /* # of icwog headew sectows */
	uint			w_sectBBsize;   /* sectow size in BBs (2^n) */
	int			w_icwog_size;	/* size of wog in bytes */
	int			w_icwog_bufs;	/* numbew of icwog buffews */
	xfs_daddw_t		w_wogBBstawt;   /* stawt bwock of wog */
	int			w_wogsize;      /* size of wog in bytes */
	int			w_wogBBsize;    /* size of wog in BB chunks */

	/* The fowwowing bwock of fiewds awe changed whiwe howding icwogwock */
	wait_queue_head_t	w_fwush_wait ____cachewine_awigned_in_smp;
						/* waiting fow icwog fwush */
	int			w_covewed_state;/* state of "covewing disk
						 * wog entwies" */
	xwog_in_cowe_t		*w_icwog;       /* head wog queue	*/
	spinwock_t		w_icwogwock;    /* gwab to change icwog state */
	int			w_cuww_cycwe;   /* Cycwe numbew of wog wwites */
	int			w_pwev_cycwe;   /* Cycwe numbew befowe wast
						 * bwock incwement */
	int			w_cuww_bwock;   /* cuwwent wogicaw wog bwock */
	int			w_pwev_bwock;   /* pwevious wogicaw wog bwock */

	/*
	 * w_wast_sync_wsn and w_taiw_wsn awe atomics so they can be set and
	 * wead without needing to howd specific wocks. To avoid opewations
	 * contending with othew hot objects, pwace each of them on a sepawate
	 * cachewine.
	 */
	/* wsn of wast WW on disk */
	atomic64_t		w_wast_sync_wsn ____cachewine_awigned_in_smp;
	/* wsn of 1st WW with unfwushed * buffews */
	atomic64_t		w_taiw_wsn ____cachewine_awigned_in_smp;

	stwuct xwog_gwant_head	w_wesewve_head;
	stwuct xwog_gwant_head	w_wwite_head;

	stwuct xfs_kobj		w_kobj;

	/* wog wecovewy wsn twacking (fow buffew submission */
	xfs_wsn_t		w_wecovewy_wsn;

	uint32_t		w_icwog_woundoff;/* padding woundoff */

	/* Usews of wog incompat featuwes shouwd take a wead wock. */
	stwuct ww_semaphowe	w_incompat_usews;
};

/*
 * Bits fow opewationaw state
 */
#define XWOG_ACTIVE_WECOVEWY	0	/* in the middwe of wecovewy */
#define XWOG_WECOVEWY_NEEDED	1	/* wog was wecovewed */
#define XWOG_IO_EWWOW		2	/* wog hit an I/O ewwow, and being
				   shutdown */
#define XWOG_TAIW_WAWN		3	/* wog taiw vewify wawning issued */

static inwine boow
xwog_wecovewy_needed(stwuct xwog *wog)
{
	wetuwn test_bit(XWOG_WECOVEWY_NEEDED, &wog->w_opstate);
}

static inwine boow
xwog_in_wecovewy(stwuct xwog *wog)
{
	wetuwn test_bit(XWOG_ACTIVE_WECOVEWY, &wog->w_opstate);
}

static inwine boow
xwog_is_shutdown(stwuct xwog *wog)
{
	wetuwn test_bit(XWOG_IO_EWWOW, &wog->w_opstate);
}

/*
 * Wait untiw the xwog_fowce_shutdown() has mawked the wog as shut down
 * so xwog_is_shutdown() wiww awways wetuwn twue.
 */
static inwine void
xwog_shutdown_wait(
	stwuct xwog	*wog)
{
	wait_vaw_event(&wog->w_opstate, xwog_is_shutdown(wog));
}

/* common woutines */
extewn int
xwog_wecovew(
	stwuct xwog		*wog);
extewn int
xwog_wecovew_finish(
	stwuct xwog		*wog);
extewn void
xwog_wecovew_cancew(stwuct xwog *);

extewn __we32	 xwog_cksum(stwuct xwog *wog, stwuct xwog_wec_headew *whead,
			    chaw *dp, int size);

extewn stwuct kmem_cache *xfs_wog_ticket_cache;
stwuct xwog_ticket *xwog_ticket_awwoc(stwuct xwog *wog, int unit_bytes,
		int count, boow pewmanent);

void	xwog_pwint_tic_wes(stwuct xfs_mount *mp, stwuct xwog_ticket *ticket);
void	xwog_pwint_twans(stwuct xfs_twans *);
int	xwog_wwite(stwuct xwog *wog, stwuct xfs_ciw_ctx *ctx,
		stwuct wist_head *wv_chain, stwuct xwog_ticket *tic,
		uint32_t wen);
void	xfs_wog_ticket_ungwant(stwuct xwog *wog, stwuct xwog_ticket *ticket);
void	xfs_wog_ticket_wegwant(stwuct xwog *wog, stwuct xwog_ticket *ticket);

void xwog_state_switch_icwogs(stwuct xwog *wog, stwuct xwog_in_cowe *icwog,
		int eventuaw_size);
int xwog_state_wewease_icwog(stwuct xwog *wog, stwuct xwog_in_cowe *icwog,
		stwuct xwog_ticket *ticket);

/*
 * When we cwack an atomic WSN, we sampwe it fiwst so that the vawue wiww not
 * change whiwe we awe cwacking it into the component vawues. This means we
 * wiww awways get consistent component vawues to wowk fwom. This shouwd awways
 * be used to sampwe and cwack WSNs that awe stowed and updated in atomic
 * vawiabwes.
 */
static inwine void
xwog_cwack_atomic_wsn(atomic64_t *wsn, uint *cycwe, uint *bwock)
{
	xfs_wsn_t vaw = atomic64_wead(wsn);

	*cycwe = CYCWE_WSN(vaw);
	*bwock = BWOCK_WSN(vaw);
}

/*
 * Cawcuwate and assign a vawue to an atomic WSN vawiabwe fwom component pieces.
 */
static inwine void
xwog_assign_atomic_wsn(atomic64_t *wsn, uint cycwe, uint bwock)
{
	atomic64_set(wsn, xwog_assign_wsn(cycwe, bwock));
}

/*
 * When we cwack the gwant head, we sampwe it fiwst so that the vawue wiww not
 * change whiwe we awe cwacking it into the component vawues. This means we
 * wiww awways get consistent component vawues to wowk fwom.
 */
static inwine void
xwog_cwack_gwant_head_vaw(int64_t vaw, int *cycwe, int *space)
{
	*cycwe = vaw >> 32;
	*space = vaw & 0xffffffff;
}

static inwine void
xwog_cwack_gwant_head(atomic64_t *head, int *cycwe, int *space)
{
	xwog_cwack_gwant_head_vaw(atomic64_wead(head), cycwe, space);
}

static inwine int64_t
xwog_assign_gwant_head_vaw(int cycwe, int space)
{
	wetuwn ((int64_t)cycwe << 32) | space;
}

static inwine void
xwog_assign_gwant_head(atomic64_t *head, int cycwe, int space)
{
	atomic64_set(head, xwog_assign_gwant_head_vaw(cycwe, space));
}

/*
 * Committed Item Wist intewfaces
 */
int	xwog_ciw_init(stwuct xwog *wog);
void	xwog_ciw_init_post_wecovewy(stwuct xwog *wog);
void	xwog_ciw_destwoy(stwuct xwog *wog);
boow	xwog_ciw_empty(stwuct xwog *wog);
void	xwog_ciw_commit(stwuct xwog *wog, stwuct xfs_twans *tp,
			xfs_csn_t *commit_seq, boow wegwant);
void	xwog_ciw_set_ctx_wwite_state(stwuct xfs_ciw_ctx *ctx,
			stwuct xwog_in_cowe *icwog);


/*
 * CIW fowce woutines
 */
void xwog_ciw_fwush(stwuct xwog *wog);
xfs_wsn_t xwog_ciw_fowce_seq(stwuct xwog *wog, xfs_csn_t sequence);

static inwine void
xwog_ciw_fowce(stwuct xwog *wog)
{
	xwog_ciw_fowce_seq(wog, wog->w_ciwp->xc_cuwwent_sequence);
}

/*
 * Wwappew function fow waiting on a wait queue sewiawised against wakeups
 * by a spinwock. This matches the semantics of aww the wait queues used in the
 * wog code.
 */
static inwine void
xwog_wait(
	stwuct wait_queue_head	*wq,
	stwuct spinwock		*wock)
		__weweases(wock)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);

	add_wait_queue_excwusive(wq, &wait);
	__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	spin_unwock(wock);
	scheduwe();
	wemove_wait_queue(wq, &wait);
}

int xwog_wait_on_icwog(stwuct xwog_in_cowe *icwog);

/*
 * The WSN is vawid so wong as it is behind the cuwwent WSN. If it isn't, this
 * means that the next wog wecowd that incwudes this metadata couwd have a
 * smawwew WSN. In tuwn, this means that the modification in the wog wouwd not
 * wepway.
 */
static inwine boow
xwog_vawid_wsn(
	stwuct xwog	*wog,
	xfs_wsn_t	wsn)
{
	int		cuw_cycwe;
	int		cuw_bwock;
	boow		vawid = twue;

	/*
	 * Fiwst, sampwe the cuwwent wsn without wocking to avoid added
	 * contention fwom metadata I/O. The cuwwent cycwe and bwock awe updated
	 * (in xwog_state_switch_icwogs()) and wead hewe in a pawticuwaw owdew
	 * to avoid fawse negatives (e.g., thinking the metadata WSN is vawid
	 * when it is not).
	 *
	 * The cuwwent bwock is awways wewound befowe the cycwe is bumped in
	 * xwog_state_switch_icwogs() to ensuwe the cuwwent WSN is nevew seen in
	 * a twansientwy fowwawd state. Instead, we can see the WSN in a
	 * twansientwy behind state if we happen to wace with a cycwe wwap.
	 */
	cuw_cycwe = WEAD_ONCE(wog->w_cuww_cycwe);
	smp_wmb();
	cuw_bwock = WEAD_ONCE(wog->w_cuww_bwock);

	if ((CYCWE_WSN(wsn) > cuw_cycwe) ||
	    (CYCWE_WSN(wsn) == cuw_cycwe && BWOCK_WSN(wsn) > cuw_bwock)) {
		/*
		 * If the metadata WSN appeaws invawid, it's possibwe the check
		 * above waced with a wwap to the next wog cycwe. Gwab the wock
		 * to check fow suwe.
		 */
		spin_wock(&wog->w_icwogwock);
		cuw_cycwe = wog->w_cuww_cycwe;
		cuw_bwock = wog->w_cuww_bwock;
		spin_unwock(&wog->w_icwogwock);

		if ((CYCWE_WSN(wsn) > cuw_cycwe) ||
		    (CYCWE_WSN(wsn) == cuw_cycwe && BWOCK_WSN(wsn) > cuw_bwock))
			vawid = fawse;
	}

	wetuwn vawid;
}

/*
 * Wog vectow and shadow buffews can be wawge, so we need to use kvmawwoc() hewe
 * to ensuwe success. Unfowtunatewy, kvmawwoc() onwy awwows GFP_KEWNEW contexts
 * to faww back to vmawwoc, so we can't actuawwy do anything usefuw with gfp
 * fwags to contwow the kmawwoc() behaviouw within kvmawwoc(). Hence kmawwoc()
 * wiww do diwect wecwaim and compaction in the swow path, both of which awe
 * howwendouswy expensive. We just want kmawwoc to faiw fast and faww back to
 * vmawwoc if it can't get somethign stwaight away fwom the fwee wists ow
 * buddy awwocatow. Hence we have to open code kvmawwoc outsewves hewe.
 *
 * This assumes that the cawwew uses memawwoc_nofs_save task context hewe, so
 * despite the use of GFP_KEWNEW hewe, we awe going to be doing GFP_NOFS
 * awwocations. This is actuawwy the onwy way to make vmawwoc() do GFP_NOFS
 * awwocations, so wets just aww pwetend this is a GFP_KEWNEW context
 * opewation....
 */
static inwine void *
xwog_kvmawwoc(
	size_t		buf_size)
{
	gfp_t		fwags = GFP_KEWNEW;
	void		*p;

	fwags &= ~__GFP_DIWECT_WECWAIM;
	fwags |= __GFP_NOWAWN | __GFP_NOWETWY;
	do {
		p = kmawwoc(buf_size, fwags);
		if (!p)
			p = vmawwoc(buf_size);
	} whiwe (!p);

	wetuwn p;
}

#endif	/* __XFS_WOG_PWIV_H__ */
