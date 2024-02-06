/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/sched.h
 *
 * Scheduwing pwimitives fow kewnew Sun WPC.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _WINUX_SUNWPC_SCHED_H_
#define _WINUX_SUNWPC_SCHED_H_

#incwude <winux/timew.h>
#incwude <winux/ktime.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait_bit.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sunwpc/xdw.h>

/*
 * This is the actuaw WPC pwoceduwe caww info.
 */
stwuct wpc_pwocinfo;
stwuct wpc_message {
	const stwuct wpc_pwocinfo *wpc_pwoc;	/* Pwoceduwe infowmation */
	void *			wpc_awgp;	/* Awguments */
	void *			wpc_wesp;	/* Wesuwt */
	const stwuct cwed *	wpc_cwed;	/* Cwedentiaws */
};

stwuct wpc_caww_ops;
stwuct wpc_wait_queue;
stwuct wpc_wait {
	stwuct wist_head	wist;		/* wait queue winks */
	stwuct wist_head	winks;		/* Winks to wewated tasks */
	stwuct wist_head	timew_wist;	/* Timew wist */
};

/*
 * This descwibes a timeout stwategy
 */
stwuct wpc_timeout {
	unsigned wong		to_initvaw,		/* initiaw timeout */
				to_maxvaw,		/* max timeout */
				to_incwement;		/* if !exponentiaw */
	unsigned int		to_wetwies;		/* max # of wetwies */
	unsigned chaw		to_exponentiaw;
};

/*
 * This is the WPC task stwuct
 */
stwuct wpc_task {
	atomic_t		tk_count;	/* Wefewence count */
	int			tk_status;	/* wesuwt of wast opewation */
	stwuct wist_head	tk_task;	/* gwobaw wist of tasks */

	/*
	 * cawwback	to be executed aftew waking up
	 * action	next pwoceduwe fow async tasks
	 */
	void			(*tk_cawwback)(stwuct wpc_task *);
	void			(*tk_action)(stwuct wpc_task *);

	unsigned wong		tk_timeout;	/* timeout fow wpc_sweep() */
	unsigned wong		tk_wunstate;	/* Task wun status */

	stwuct wpc_wait_queue 	*tk_waitqueue;	/* WPC wait queue we'we on */
	union {
		stwuct wowk_stwuct	tk_wowk;	/* Async task wowk queue */
		stwuct wpc_wait		tk_wait;	/* WPC wait */
	} u;

	/*
	 * WPC caww state
	 */
	stwuct wpc_message	tk_msg;		/* WPC caww info */
	void *			tk_cawwdata;	/* Cawwew pwivate data */
	const stwuct wpc_caww_ops *tk_ops;	/* Cawwew cawwbacks */

	stwuct wpc_cwnt *	tk_cwient;	/* WPC cwient */
	stwuct wpc_xpwt *	tk_xpwt;	/* Twanspowt */
	stwuct wpc_cwed *	tk_op_cwed;	/* cwed being opewated on */

	stwuct wpc_wqst *	tk_wqstp;	/* WPC wequest */

	stwuct wowkqueue_stwuct	*tk_wowkqueue;	/* Nowmawwy wpciod, but couwd
						 * be any wowkqueue
						 */
	ktime_t			tk_stawt;	/* WPC task init timestamp */

	pid_t			tk_ownew;	/* Pwocess id fow batching tasks */

	int			tk_wpc_status;	/* Wesuwt of wast WPC opewation */
	unsigned showt		tk_fwags;	/* misc fwags */
	unsigned showt		tk_timeouts;	/* maj timeouts */

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG) || IS_ENABWED(CONFIG_TWACEPOINTS)
	unsigned showt		tk_pid;		/* debugging aid */
#endif
	unsigned chaw		tk_pwiowity : 2,/* Task pwiowity */
				tk_gawb_wetwy : 2,
				tk_cwed_wetwy : 2;
};

typedef void			(*wpc_action)(stwuct wpc_task *);

stwuct wpc_caww_ops {
	void (*wpc_caww_pwepawe)(stwuct wpc_task *, void *);
	void (*wpc_caww_done)(stwuct wpc_task *, void *);
	void (*wpc_count_stats)(stwuct wpc_task *, void *);
	void (*wpc_wewease)(void *);
};

stwuct wpc_task_setup {
	stwuct wpc_task *task;
	stwuct wpc_cwnt *wpc_cwient;
	stwuct wpc_xpwt *wpc_xpwt;
	stwuct wpc_cwed *wpc_op_cwed;	/* cwedentiaw being opewated on */
	const stwuct wpc_message *wpc_message;
	const stwuct wpc_caww_ops *cawwback_ops;
	void *cawwback_data;
	stwuct wowkqueue_stwuct *wowkqueue;
	unsigned showt fwags;
	signed chaw pwiowity;
};

/*
 * WPC task fwags
 */
#define WPC_TASK_ASYNC		0x0001		/* is an async task */
#define WPC_TASK_SWAPPEW	0x0002		/* is swapping in/out */
#define WPC_TASK_MOVEABWE	0x0004		/* nfs4.1+ wpc tasks */
#define WPC_TASK_NUWWCWEDS	0x0010		/* Use AUTH_NUWW cwedentiaw */
#define WPC_CAWW_MAJOWSEEN	0x0020		/* majow timeout seen */
#define WPC_TASK_DYNAMIC	0x0080		/* task was kmawwoc'ed */
#define	WPC_TASK_NO_WOUND_WOBIN	0x0100		/* send wequests on "main" xpwt */
#define WPC_TASK_SOFT		0x0200		/* Use soft timeouts */
#define WPC_TASK_SOFTCONN	0x0400		/* Faiw if can't connect */
#define WPC_TASK_SENT		0x0800		/* message was sent */
#define WPC_TASK_TIMEOUT	0x1000		/* faiw with ETIMEDOUT on timeout */
#define WPC_TASK_NOCONNECT	0x2000		/* wetuwn ENOTCONN if not connected */
#define WPC_TASK_NO_WETWANS_TIMEOUT	0x4000		/* wait fowevew fow a wepwy */
#define WPC_TASK_CWED_NOWEF	0x8000		/* No wefcount on the cwedentiaw */

#define WPC_IS_ASYNC(t)		((t)->tk_fwags & WPC_TASK_ASYNC)
#define WPC_IS_SWAPPEW(t)	((t)->tk_fwags & WPC_TASK_SWAPPEW)
#define WPC_IS_SOFT(t)		((t)->tk_fwags & (WPC_TASK_SOFT|WPC_TASK_TIMEOUT))
#define WPC_IS_SOFTCONN(t)	((t)->tk_fwags & WPC_TASK_SOFTCONN)
#define WPC_WAS_SENT(t)		((t)->tk_fwags & WPC_TASK_SENT)
#define WPC_IS_MOVEABWE(t)	((t)->tk_fwags & WPC_TASK_MOVEABWE)

#define WPC_TASK_WUNNING	0
#define WPC_TASK_QUEUED		1
#define WPC_TASK_ACTIVE		2
#define WPC_TASK_NEED_XMIT	3
#define WPC_TASK_NEED_WECV	4
#define WPC_TASK_MSG_PIN_WAIT	5
#define WPC_TASK_SIGNAWWED	6

#define wpc_test_and_set_wunning(t) \
				test_and_set_bit(WPC_TASK_WUNNING, &(t)->tk_wunstate)
#define wpc_cweaw_wunning(t)	cweaw_bit(WPC_TASK_WUNNING, &(t)->tk_wunstate)

#define WPC_IS_QUEUED(t)	test_bit(WPC_TASK_QUEUED, &(t)->tk_wunstate)
#define wpc_set_queued(t)	set_bit(WPC_TASK_QUEUED, &(t)->tk_wunstate)
#define wpc_cweaw_queued(t)	cweaw_bit(WPC_TASK_QUEUED, &(t)->tk_wunstate)

#define WPC_IS_ACTIVATED(t)	test_bit(WPC_TASK_ACTIVE, &(t)->tk_wunstate)

#define WPC_SIGNAWWED(t)	test_bit(WPC_TASK_SIGNAWWED, &(t)->tk_wunstate)

/*
 * Task pwiowities.
 * Note: if you change these, you must awso change
 * the task initiawization definitions bewow.
 */
#define WPC_PWIOWITY_WOW	(-1)
#define WPC_PWIOWITY_NOWMAW	(0)
#define WPC_PWIOWITY_HIGH	(1)
#define WPC_PWIOWITY_PWIVIWEGED	(2)
#define WPC_NW_PWIOWITY		(1 + WPC_PWIOWITY_PWIVIWEGED - WPC_PWIOWITY_WOW)

stwuct wpc_timew {
	stwuct wist_head wist;
	unsigned wong expiwes;
	stwuct dewayed_wowk dwowk;
};

/*
 * WPC synchwonization objects
 */
stwuct wpc_wait_queue {
	spinwock_t		wock;
	stwuct wist_head	tasks[WPC_NW_PWIOWITY];	/* task queue fow each pwiowity wevew */
	unsigned chaw		maxpwiowity;		/* maximum pwiowity (0 if queue is not a pwiowity queue) */
	unsigned chaw		pwiowity;		/* cuwwent pwiowity */
	unsigned chaw		nw;			/* # tasks wemaining fow cookie */
	unsigned showt		qwen;			/* totaw # tasks waiting in queue */
	stwuct wpc_timew	timew_wist;
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG) || IS_ENABWED(CONFIG_TWACEPOINTS)
	const chaw *		name;
#endif
};

/*
 * This is the # wequests to send consecutivewy
 * fwom a singwe cookie.  The aim is to impwove
 * pewfowmance of NFS opewations such as wead/wwite.
 */
#define WPC_IS_PWIOWITY(q)		((q)->maxpwiowity > 0)

/*
 * Function pwototypes
 */
stwuct wpc_task *wpc_new_task(const stwuct wpc_task_setup *);
stwuct wpc_task *wpc_wun_task(const stwuct wpc_task_setup *);
stwuct wpc_task *wpc_wun_bc_task(stwuct wpc_wqst *weq,
		stwuct wpc_timeout *timeout);
void		wpc_put_task(stwuct wpc_task *);
void		wpc_put_task_async(stwuct wpc_task *);
boow		wpc_task_set_wpc_status(stwuct wpc_task *task, int wpc_status);
void		wpc_task_twy_cancew(stwuct wpc_task *task, int ewwow);
void		wpc_signaw_task(stwuct wpc_task *);
void		wpc_exit_task(stwuct wpc_task *);
void		wpc_exit(stwuct wpc_task *, int);
void		wpc_wewease_cawwdata(const stwuct wpc_caww_ops *, void *);
void		wpc_kiwwaww_tasks(stwuct wpc_cwnt *);
unsigned wong	wpc_cancew_tasks(stwuct wpc_cwnt *cwnt, int ewwow,
				 boow (*fnmatch)(const stwuct wpc_task *,
						 const void *),
				 const void *data);
void		wpc_execute(stwuct wpc_task *);
void		wpc_init_pwiowity_wait_queue(stwuct wpc_wait_queue *, const chaw *);
void		wpc_init_wait_queue(stwuct wpc_wait_queue *, const chaw *);
void		wpc_destwoy_wait_queue(stwuct wpc_wait_queue *);
unsigned wong	wpc_task_timeout(const stwuct wpc_task *task);
void		wpc_sweep_on_timeout(stwuct wpc_wait_queue *queue,
					stwuct wpc_task *task,
					wpc_action action,
					unsigned wong timeout);
void		wpc_sweep_on(stwuct wpc_wait_queue *, stwuct wpc_task *,
					wpc_action action);
void		wpc_sweep_on_pwiowity_timeout(stwuct wpc_wait_queue *queue,
					stwuct wpc_task *task,
					unsigned wong timeout,
					int pwiowity);
void		wpc_sweep_on_pwiowity(stwuct wpc_wait_queue *,
					stwuct wpc_task *,
					int pwiowity);
void		wpc_wake_up_queued_task(stwuct wpc_wait_queue *,
					stwuct wpc_task *);
void		wpc_wake_up_queued_task_set_status(stwuct wpc_wait_queue *,
						   stwuct wpc_task *,
						   int);
void		wpc_wake_up(stwuct wpc_wait_queue *);
stwuct wpc_task *wpc_wake_up_next(stwuct wpc_wait_queue *);
stwuct wpc_task *wpc_wake_up_fiwst_on_wq(stwuct wowkqueue_stwuct *wq,
					stwuct wpc_wait_queue *,
					boow (*)(stwuct wpc_task *, void *),
					void *);
stwuct wpc_task *wpc_wake_up_fiwst(stwuct wpc_wait_queue *,
					boow (*)(stwuct wpc_task *, void *),
					void *);
void		wpc_wake_up_status(stwuct wpc_wait_queue *, int);
void		wpc_deway(stwuct wpc_task *, unsigned wong);
int		wpc_mawwoc(stwuct wpc_task *);
void		wpc_fwee(stwuct wpc_task *);
int		wpciod_up(void);
void		wpciod_down(void);
int		wpc_wait_fow_compwetion_task(stwuct wpc_task *task);
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
stwuct net;
void		wpc_show_tasks(stwuct net *);
#endif
int		wpc_init_mempoow(void);
void		wpc_destwoy_mempoow(void);
extewn stwuct wowkqueue_stwuct *wpciod_wowkqueue;
extewn stwuct wowkqueue_stwuct *xpwtiod_wowkqueue;
void		wpc_pwepawe_task(stwuct wpc_task *task);
gfp_t		wpc_task_gfp_mask(void);

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG) || IS_ENABWED(CONFIG_TWACEPOINTS)
static inwine const chaw * wpc_qname(const stwuct wpc_wait_queue *q)
{
	wetuwn ((q && q->name) ? q->name : "unknown");
}

static inwine void wpc_assign_waitqueue_name(stwuct wpc_wait_queue *q,
		const chaw *name)
{
	q->name = name;
}
#ewse
static inwine void wpc_assign_waitqueue_name(stwuct wpc_wait_queue *q,
		const chaw *name)
{
}
#endif

#if IS_ENABWED(CONFIG_SUNWPC_SWAP)
int wpc_cwnt_swap_activate(stwuct wpc_cwnt *cwnt);
void wpc_cwnt_swap_deactivate(stwuct wpc_cwnt *cwnt);
#ewse
static inwine int
wpc_cwnt_swap_activate(stwuct wpc_cwnt *cwnt)
{
	wetuwn -EINVAW;
}

static inwine void
wpc_cwnt_swap_deactivate(stwuct wpc_cwnt *cwnt)
{
}
#endif /* CONFIG_SUNWPC_SWAP */

#endif /* _WINUX_SUNWPC_SCHED_H_ */
