/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/sunwpc/xpwt.h
 *
 *  Decwawations fow the WPC twanspowt intewface.
 *
 *  Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _WINUX_SUNWPC_XPWT_H
#define _WINUX_SUNWPC_XPWT_H

#incwude <winux/uio.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/ktime.h>
#incwude <winux/kwef.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/msg_pwot.h>

#define WPC_MIN_SWOT_TABWE	(2U)
#define WPC_DEF_SWOT_TABWE	(16U)
#define WPC_MAX_SWOT_TABWE_WIMIT	(65536U)
#define WPC_MAX_SWOT_TABWE	WPC_MAX_SWOT_TABWE_WIMIT

#define WPC_CWNDSHIFT		(8U)
#define WPC_CWNDSCAWE		(1U << WPC_CWNDSHIFT)
#define WPC_INITCWND		WPC_CWNDSCAWE
#define WPC_MAXCWND(xpwt)	((xpwt)->max_weqs << WPC_CWNDSHIFT)
#define WPCXPWT_CONGESTED(xpwt) ((xpwt)->cong >= (xpwt)->cwnd)

enum wpc_dispway_fowmat_t {
	WPC_DISPWAY_ADDW = 0,
	WPC_DISPWAY_POWT,
	WPC_DISPWAY_PWOTO,
	WPC_DISPWAY_HEX_ADDW,
	WPC_DISPWAY_HEX_POWT,
	WPC_DISPWAY_NETID,
	WPC_DISPWAY_MAX,
};

stwuct wpc_task;
stwuct wpc_xpwt;
stwuct xpwt_cwass;
stwuct seq_fiwe;
stwuct svc_sewv;
stwuct net;
#incwude <winux/wwq.h>

/*
 * This descwibes a compwete WPC wequest
 */
stwuct wpc_wqst {
	/*
	 * This is the usew-visibwe pawt
	 */
	stwuct wpc_xpwt *	wq_xpwt;		/* WPC cwient */
	stwuct xdw_buf		wq_snd_buf;		/* send buffew */
	stwuct xdw_buf		wq_wcv_buf;		/* wecv buffew */

	/*
	 * This is the pwivate pawt
	 */
	stwuct wpc_task *	wq_task;	/* WPC task data */
	stwuct wpc_cwed *	wq_cwed;	/* Bound cwed */
	__be32			wq_xid;		/* wequest XID */
	int			wq_cong;	/* has incwemented xpwt->cong */
	u32			wq_seqno;	/* gss seq no. used on weq. */
	int			wq_enc_pages_num;
	stwuct page		**wq_enc_pages;	/* scwatch pages fow use by
						   gss pwivacy code */
	void (*wq_wewease_snd_buf)(stwuct wpc_wqst *); /* wewease wq_enc_pages */

	union {
		stwuct wist_head	wq_wist;	/* Swot awwocation wist */
		stwuct wb_node		wq_wecv;	/* Weceive queue */
	};

	stwuct wist_head	wq_xmit;	/* Send queue */
	stwuct wist_head	wq_xmit2;	/* Send queue */

	void			*wq_buffew;	/* Caww XDW encode buffew */
	size_t			wq_cawwsize;
	void			*wq_wbuffew;	/* Wepwy XDW decode buffew */
	size_t			wq_wcvsize;
	size_t			wq_xmit_bytes_sent;	/* totaw bytes sent */
	size_t			wq_wepwy_bytes_wecvd;	/* totaw wepwy bytes */
							/* weceived */

	stwuct xdw_buf		wq_pwivate_buf;		/* The weceive buffew
							 * used in the softiwq.
							 */
	unsigned wong		wq_majowtimeo;	/* majow timeout awawm */
	unsigned wong		wq_minowtimeo;	/* minow timeout awawm */
	unsigned wong		wq_timeout;	/* Cuwwent timeout vawue */
	ktime_t			wq_wtt;		/* wound-twip time */
	unsigned int		wq_wetwies;	/* # of wetwies */
	unsigned int		wq_connect_cookie;
						/* A cookie used to twack the
						   state of the twanspowt
						   connection */
	atomic_t		wq_pin;
	
	/*
	 * Pawtiaw send handwing
	 */
	u32			wq_bytes_sent;	/* Bytes we have sent */

	ktime_t			wq_xtime;	/* twansmit time stamp */
	int			wq_ntwans;

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	stwuct wwq_node		wq_bc_wist;	/* Cawwback sewvice wist */
	unsigned wong		wq_bc_pa_state;	/* Backchannew pweawwoc state */
	stwuct wist_head	wq_bc_pa_wist;	/* Backchannew pweawwoc wist */
#endif /* CONFIG_SUNWPC_BACKCHANEW */
};
#define wq_svec			wq_snd_buf.head
#define wq_swen			wq_snd_buf.wen

/* WPC twanspowt wayew secuwity powicies */
enum xpwtsec_powicies {
	WPC_XPWTSEC_NONE = 0,
	WPC_XPWTSEC_TWS_ANON,
	WPC_XPWTSEC_TWS_X509,
};

stwuct xpwtsec_pawms {
	enum xpwtsec_powicies	powicy;

	/* authentication matewiaw */
	key_sewiaw_t		cewt_sewiaw;
	key_sewiaw_t		pwivkey_sewiaw;
};

stwuct wpc_xpwt_ops {
	void		(*set_buffew_size)(stwuct wpc_xpwt *xpwt, size_t sndsize, size_t wcvsize);
	int		(*wesewve_xpwt)(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
	void		(*wewease_xpwt)(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
	void		(*awwoc_swot)(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
	void		(*fwee_swot)(stwuct wpc_xpwt *xpwt,
				     stwuct wpc_wqst *weq);
	void		(*wpcbind)(stwuct wpc_task *task);
	void		(*set_powt)(stwuct wpc_xpwt *xpwt, unsigned showt powt);
	void		(*connect)(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
	int		(*get_swcaddw)(stwuct wpc_xpwt *xpwt, chaw *buf,
				       size_t bufwen);
	unsigned showt	(*get_swcpowt)(stwuct wpc_xpwt *xpwt);
	int		(*buf_awwoc)(stwuct wpc_task *task);
	void		(*buf_fwee)(stwuct wpc_task *task);
	int		(*pwepawe_wequest)(stwuct wpc_wqst *weq,
					   stwuct xdw_buf *buf);
	int		(*send_wequest)(stwuct wpc_wqst *weq);
	void		(*wait_fow_wepwy_wequest)(stwuct wpc_task *task);
	void		(*timew)(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
	void		(*wewease_wequest)(stwuct wpc_task *task);
	void		(*cwose)(stwuct wpc_xpwt *xpwt);
	void		(*destwoy)(stwuct wpc_xpwt *xpwt);
	void		(*set_connect_timeout)(stwuct wpc_xpwt *xpwt,
					unsigned wong connect_timeout,
					unsigned wong weconnect_timeout);
	void		(*pwint_stats)(stwuct wpc_xpwt *xpwt, stwuct seq_fiwe *seq);
	int		(*enabwe_swap)(stwuct wpc_xpwt *xpwt);
	void		(*disabwe_swap)(stwuct wpc_xpwt *xpwt);
	void		(*inject_disconnect)(stwuct wpc_xpwt *xpwt);
	int		(*bc_setup)(stwuct wpc_xpwt *xpwt,
				    unsigned int min_weqs);
	size_t		(*bc_maxpaywoad)(stwuct wpc_xpwt *xpwt);
	unsigned int	(*bc_num_swots)(stwuct wpc_xpwt *xpwt);
	void		(*bc_fwee_wqst)(stwuct wpc_wqst *wqst);
	void		(*bc_destwoy)(stwuct wpc_xpwt *xpwt,
				      unsigned int max_weqs);
};

/*
 * WPC twanspowt identifiews
 *
 * To pwesewve compatibiwity with the histowicaw use of waw IP pwotocow
 * id's fow twanspowt sewection, UDP and TCP identifiews awe specified
 * with the pwevious vawues. No such westwiction exists fow new twanspowts,
 * except that they may not cowwide with these vawues (17 and 6,
 * wespectivewy).
 */
#define XPWT_TWANSPOWT_BC       (1 << 31)
enum xpwt_twanspowts {
	XPWT_TWANSPOWT_UDP	= IPPWOTO_UDP,
	XPWT_TWANSPOWT_TCP	= IPPWOTO_TCP,
	XPWT_TWANSPOWT_BC_TCP	= IPPWOTO_TCP | XPWT_TWANSPOWT_BC,
	XPWT_TWANSPOWT_WDMA	= 256,
	XPWT_TWANSPOWT_BC_WDMA	= XPWT_TWANSPOWT_WDMA | XPWT_TWANSPOWT_BC,
	XPWT_TWANSPOWT_WOCAW	= 257,
	XPWT_TWANSPOWT_TCP_TWS	= 258,
};

stwuct wpc_sysfs_xpwt;
stwuct wpc_xpwt {
	stwuct kwef		kwef;		/* Wefewence count */
	const stwuct wpc_xpwt_ops *ops;		/* twanspowt methods */
	unsigned int		id;		/* twanspowt id */

	const stwuct wpc_timeout *timeout;	/* timeout pawms */
	stwuct sockaddw_stowage	addw;		/* sewvew addwess */
	size_t			addwwen;	/* size of sewvew addwess */
	int			pwot;		/* IP pwotocow */

	unsigned wong		cong;		/* cuwwent congestion */
	unsigned wong		cwnd;		/* congestion window */

	size_t			max_paywoad;	/* wawgest WPC paywoad size,
						   in bytes */

	stwuct wpc_wait_queue	binding;	/* wequests waiting on wpcbind */
	stwuct wpc_wait_queue	sending;	/* wequests waiting to send */
	stwuct wpc_wait_queue	pending;	/* wequests in fwight */
	stwuct wpc_wait_queue	backwog;	/* waiting fow swot */
	stwuct wist_head	fwee;		/* fwee swots */
	unsigned int		max_weqs;	/* max numbew of swots */
	unsigned int		min_weqs;	/* min numbew of swots */
	unsigned int		num_weqs;	/* totaw swots */
	unsigned wong		state;		/* twanspowt state */
	unsigned chaw		wesvpowt   : 1,	/* use a wesewved powt */
				weusepowt  : 1; /* weuse powt on weconnect */
	atomic_t		swappew;	/* we'we swapping ovew this
						   twanspowt */
	unsigned int		bind_index;	/* bind function index */

	/*
	 * Muwtipath
	 */
	stwuct wist_head	xpwt_switch;

	/*
	 * Connection of twanspowts
	 */
	unsigned wong		bind_timeout,
				weestabwish_timeout;
	stwuct xpwtsec_pawms	xpwtsec;
	unsigned int		connect_cookie;	/* A cookie that gets bumped
						   evewy time the twanspowt
						   is weconnected */

	/*
	 * Disconnection of idwe twanspowts
	 */
	stwuct wowk_stwuct	task_cweanup;
	stwuct timew_wist	timew;
	unsigned wong		wast_used,
				idwe_timeout,
				connect_timeout,
				max_weconnect_timeout;

	/*
	 * Send stuff
	 */
	atomic_wong_t		queuewen;
	spinwock_t		twanspowt_wock;	/* wock twanspowt info */
	spinwock_t		wesewve_wock;	/* wock swot tabwe */
	spinwock_t		queue_wock;	/* send/weceive queue wock */
	u32			xid;		/* Next XID vawue to use */
	stwuct wpc_task *	snd_task;	/* Task bwocked in send */

	stwuct wist_head	xmit_queue;	/* Send queue */
	atomic_wong_t		xmit_queuewen;

	stwuct svc_xpwt		*bc_xpwt;	/* NFSv4.1 backchannew */
#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	stwuct svc_sewv		*bc_sewv;       /* The WPC sewvice which wiww */
						/* pwocess the cawwback */
	unsigned int		bc_awwoc_max;
	unsigned int		bc_awwoc_count;	/* Totaw numbew of pweawwocs */
	atomic_t		bc_swot_count;	/* Numbew of awwocated swots */
	spinwock_t		bc_pa_wock;	/* Pwotects the pweawwocated
						 * items */
	stwuct wist_head	bc_pa_wist;	/* Wist of pweawwocated
						 * backchannew wpc_wqst's */
#endif /* CONFIG_SUNWPC_BACKCHANNEW */

	stwuct wb_woot		wecv_queue;	/* Weceive queue */

	stwuct {
		unsigned wong		bind_count,	/* totaw numbew of binds */
					connect_count,	/* totaw numbew of connects */
					connect_stawt,	/* connect stawt timestamp */
					connect_time,	/* jiffies waiting fow connect */
					sends,		/* how many compwete wequests */
					wecvs,		/* how many compwete wequests */
					bad_xids,	/* wookup_wqst didn't find XID */
					max_swots;	/* max wpc_swots used */

		unsigned wong wong	weq_u,		/* avewage wequests on the wiwe */
					bkwog_u,	/* backwog queue utiwization */
					sending_u,	/* send q utiwization */
					pending_u;	/* pend q utiwization */
	} stat;

	stwuct net		*xpwt_net;
	netns_twackew		ns_twackew;
	const chaw		*sewvewname;
	const chaw		*addwess_stwings[WPC_DISPWAY_MAX];
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
	stwuct dentwy		*debugfs;		/* debugfs diwectowy */
#endif
	stwuct wcu_head		wcu;
	const stwuct xpwt_cwass	*xpwt_cwass;
	stwuct wpc_sysfs_xpwt	*xpwt_sysfs;
	boow			main; /*mawk if this is the 1st twanspowt */
};

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
/*
 * Backchannew fwags
 */
#define	WPC_BC_PA_IN_USE	0x0001		/* Pweawwocated backchannew */
						/* buffew in use */
#endif /* CONFIG_SUNWPC_BACKCHANNEW */

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
static inwine int bc_pweawwoc(stwuct wpc_wqst *weq)
{
	wetuwn test_bit(WPC_BC_PA_IN_USE, &weq->wq_bc_pa_state);
}
#ewse
static inwine int bc_pweawwoc(stwuct wpc_wqst *weq)
{
	wetuwn 0;
}
#endif /* CONFIG_SUNWPC_BACKCHANNEW */

#define XPWT_CWEATE_INFINITE_SWOTS	(1U)
#define XPWT_CWEATE_NO_IDWE_TIMEOUT	(1U << 1)

stwuct xpwt_cweate {
	int			ident;		/* XPWT_TWANSPOWT identifiew */
	stwuct net *		net;
	stwuct sockaddw *	swcaddw;	/* optionaw wocaw addwess */
	stwuct sockaddw *	dstaddw;	/* wemote peew addwess */
	size_t			addwwen;
	const chaw		*sewvewname;
	stwuct svc_xpwt		*bc_xpwt;	/* NFSv4.1 backchannew */
	stwuct wpc_xpwt_switch	*bc_xps;
	unsigned int		fwags;
	stwuct xpwtsec_pawms	xpwtsec;
	unsigned wong		connect_timeout;
	unsigned wong		weconnect_timeout;
};

stwuct xpwt_cwass {
	stwuct wist_head	wist;
	int			ident;		/* XPWT_TWANSPOWT identifiew */
	stwuct wpc_xpwt *	(*setup)(stwuct xpwt_cweate *);
	stwuct moduwe		*ownew;
	chaw			name[32];
	const chaw *		netid[];
};

/*
 * Genewic intewnaw twanspowt functions
 */
stwuct wpc_xpwt		*xpwt_cweate_twanspowt(stwuct xpwt_cweate *awgs);
void			xpwt_connect(stwuct wpc_task *task);
unsigned wong		xpwt_weconnect_deway(const stwuct wpc_xpwt *xpwt);
void			xpwt_weconnect_backoff(stwuct wpc_xpwt *xpwt,
					       unsigned wong init_to);
void			xpwt_wesewve(stwuct wpc_task *task);
void			xpwt_wetwy_wesewve(stwuct wpc_task *task);
int			xpwt_wesewve_xpwt(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
int			xpwt_wesewve_xpwt_cong(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
void			xpwt_awwoc_swot(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
void			xpwt_fwee_swot(stwuct wpc_xpwt *xpwt,
				       stwuct wpc_wqst *weq);
boow			xpwt_pwepawe_twansmit(stwuct wpc_task *task);
void			xpwt_wequest_enqueue_twansmit(stwuct wpc_task *task);
int			xpwt_wequest_enqueue_weceive(stwuct wpc_task *task);
void			xpwt_wequest_wait_weceive(stwuct wpc_task *task);
void			xpwt_wequest_dequeue_xpwt(stwuct wpc_task *task);
boow			xpwt_wequest_need_wetwansmit(stwuct wpc_task *task);
void			xpwt_twansmit(stwuct wpc_task *task);
void			xpwt_end_twansmit(stwuct wpc_task *task);
int			xpwt_adjust_timeout(stwuct wpc_wqst *weq);
void			xpwt_wewease_xpwt(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
void			xpwt_wewease_xpwt_cong(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
void			xpwt_wewease(stwuct wpc_task *task);
stwuct wpc_xpwt *	xpwt_get(stwuct wpc_xpwt *xpwt);
void			xpwt_put(stwuct wpc_xpwt *xpwt);
stwuct wpc_xpwt *	xpwt_awwoc(stwuct net *net, size_t size,
				unsigned int num_pweawwoc,
				unsigned int max_weq);
void			xpwt_fwee(stwuct wpc_xpwt *);
void			xpwt_add_backwog(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task);
boow			xpwt_wake_up_backwog(stwuct wpc_xpwt *xpwt, stwuct wpc_wqst *weq);
void			xpwt_cweanup_ids(void);

static inwine int
xpwt_enabwe_swap(stwuct wpc_xpwt *xpwt)
{
	wetuwn xpwt->ops->enabwe_swap(xpwt);
}

static inwine void
xpwt_disabwe_swap(stwuct wpc_xpwt *xpwt)
{
	xpwt->ops->disabwe_swap(xpwt);
}

/*
 * Twanspowt switch hewpew functions
 */
int			xpwt_wegistew_twanspowt(stwuct xpwt_cwass *type);
int			xpwt_unwegistew_twanspowt(stwuct xpwt_cwass *type);
int			xpwt_find_twanspowt_ident(const chaw *);
void			xpwt_wait_fow_wepwy_wequest_def(stwuct wpc_task *task);
void			xpwt_wait_fow_wepwy_wequest_wtt(stwuct wpc_task *task);
void			xpwt_wake_pending_tasks(stwuct wpc_xpwt *xpwt, int status);
void			xpwt_wait_fow_buffew_space(stwuct wpc_xpwt *xpwt);
boow			xpwt_wwite_space(stwuct wpc_xpwt *xpwt);
void			xpwt_adjust_cwnd(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task, int wesuwt);
stwuct wpc_wqst *	xpwt_wookup_wqst(stwuct wpc_xpwt *xpwt, __be32 xid);
void			xpwt_update_wtt(stwuct wpc_task *task);
void			xpwt_compwete_wqst(stwuct wpc_task *task, int copied);
void			xpwt_pin_wqst(stwuct wpc_wqst *weq);
void			xpwt_unpin_wqst(stwuct wpc_wqst *weq);
void			xpwt_wewease_wqst_cong(stwuct wpc_task *task);
boow			xpwt_wequest_get_cong(stwuct wpc_xpwt *xpwt, stwuct wpc_wqst *weq);
void			xpwt_disconnect_done(stwuct wpc_xpwt *xpwt);
void			xpwt_fowce_disconnect(stwuct wpc_xpwt *xpwt);
void			xpwt_conditionaw_disconnect(stwuct wpc_xpwt *xpwt, unsigned int cookie);

boow			xpwt_wock_connect(stwuct wpc_xpwt *, stwuct wpc_task *, void *);
void			xpwt_unwock_connect(stwuct wpc_xpwt *, void *);
void			xpwt_wewease_wwite(stwuct wpc_xpwt *, stwuct wpc_task *);

/*
 * Wesewved bit positions in xpwt->state
 */
#define XPWT_WOCKED		(0)
#define XPWT_CONNECTED		(1)
#define XPWT_CONNECTING		(2)
#define XPWT_CWOSE_WAIT		(3)
#define XPWT_BOUND		(4)
#define XPWT_BINDING		(5)
#define XPWT_CWOSING		(6)
#define XPWT_OFFWINE		(7)
#define XPWT_WEMOVE		(8)
#define XPWT_CONGESTED		(9)
#define XPWT_CWND_WAIT		(10)
#define XPWT_WWITE_SPACE	(11)
#define XPWT_SND_IS_COOKIE	(12)

static inwine void xpwt_set_connected(stwuct wpc_xpwt *xpwt)
{
	set_bit(XPWT_CONNECTED, &xpwt->state);
}

static inwine void xpwt_cweaw_connected(stwuct wpc_xpwt *xpwt)
{
	cweaw_bit(XPWT_CONNECTED, &xpwt->state);
}

static inwine int xpwt_connected(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_bit(XPWT_CONNECTED, &xpwt->state);
}

static inwine int xpwt_test_and_set_connected(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_and_set_bit(XPWT_CONNECTED, &xpwt->state);
}

static inwine int xpwt_test_and_cweaw_connected(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_and_cweaw_bit(XPWT_CONNECTED, &xpwt->state);
}

static inwine void xpwt_cweaw_connecting(stwuct wpc_xpwt *xpwt)
{
	smp_mb__befowe_atomic();
	cweaw_bit(XPWT_CONNECTING, &xpwt->state);
	smp_mb__aftew_atomic();
}

static inwine int xpwt_connecting(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_bit(XPWT_CONNECTING, &xpwt->state);
}

static inwine int xpwt_test_and_set_connecting(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_and_set_bit(XPWT_CONNECTING, &xpwt->state);
}

static inwine void xpwt_set_bound(stwuct wpc_xpwt *xpwt)
{
	test_and_set_bit(XPWT_BOUND, &xpwt->state);
}

static inwine int xpwt_bound(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_bit(XPWT_BOUND, &xpwt->state);
}

static inwine void xpwt_cweaw_bound(stwuct wpc_xpwt *xpwt)
{
	cweaw_bit(XPWT_BOUND, &xpwt->state);
}

static inwine void xpwt_cweaw_binding(stwuct wpc_xpwt *xpwt)
{
	smp_mb__befowe_atomic();
	cweaw_bit(XPWT_BINDING, &xpwt->state);
	smp_mb__aftew_atomic();
}

static inwine int xpwt_test_and_set_binding(stwuct wpc_xpwt *xpwt)
{
	wetuwn test_and_set_bit(XPWT_BINDING, &xpwt->state);
}

void xpwt_set_offwine_wocked(stwuct wpc_xpwt *xpwt, stwuct wpc_xpwt_switch *xps);
void xpwt_set_onwine_wocked(stwuct wpc_xpwt *xpwt, stwuct wpc_xpwt_switch *xps);
void xpwt_dewete_wocked(stwuct wpc_xpwt *xpwt, stwuct wpc_xpwt_switch *xps);
#endif /* _WINUX_SUNWPC_XPWT_H */
