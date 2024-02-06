/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/sunwpc/cwnt.h
 *
 *  Decwawations fow the high-wevew WPC cwient intewface
 *
 *  Copywight (C) 1995, 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _WINUX_SUNWPC_CWNT_H
#define _WINUX_SUNWPC_CWNT_H

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/wefcount.h>

#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/timew.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>
#incwude <asm/signaw.h>
#incwude <winux/path.h>
#incwude <net/ipv6.h>
#incwude <winux/sunwpc/xpwtmuwtipath.h>

stwuct wpc_inode;
stwuct wpc_sysfs_cwient {
	stwuct kobject kobject;
	stwuct net *net;
	stwuct wpc_cwnt *cwnt;
	stwuct wpc_xpwt_switch *xpwt_switch;
};


/*
 * The high-wevew cwient handwe
 */
stwuct wpc_cwnt {
	wefcount_t		cw_count;	/* Numbew of wefewences */
	unsigned int		cw_cwid;	/* cwient id */
	stwuct wist_head	cw_cwients;	/* Gwobaw wist of cwients */
	stwuct wist_head	cw_tasks;	/* Wist of tasks */
	atomic_t		cw_pid;		/* task PID countew */
	spinwock_t		cw_wock;	/* spinwock */
	stwuct wpc_xpwt __wcu *	cw_xpwt;	/* twanspowt */
	const stwuct wpc_pwocinfo *cw_pwocinfo;	/* pwoceduwe info */
	u32			cw_pwog,	/* WPC pwogwam numbew */
				cw_vews,	/* WPC vewsion numbew */
				cw_maxpwoc;	/* max pwoceduwe numbew */

	stwuct wpc_auth *	cw_auth;	/* authenticatow */
	stwuct wpc_stat *	cw_stats;	/* pew-pwogwam statistics */
	stwuct wpc_iostats *	cw_metwics;	/* pew-cwient statistics */

	unsigned int		cw_softwtwy : 1,/* soft timeouts */
				cw_softeww  : 1,/* Timeouts wetuwn ewwows */
				cw_discwtwy : 1,/* disconnect befowe wetwy */
				cw_nowetwanstimeo: 1,/* No wetwansmit timeouts */
				cw_autobind : 1,/* use getpowt() */
				cw_chatty   : 1,/* be vewbose */
				cw_shutdown : 1;/* wpc immediate -EIO */
	stwuct xpwtsec_pawms	cw_xpwtsec;	/* twanspowt secuwity powicy */

	stwuct wpc_wtt *	cw_wtt;		/* WTO estimatow data */
	const stwuct wpc_timeout *cw_timeout;	/* Timeout stwategy */

	atomic_t		cw_swappew;	/* swapfiwe count */
	int			cw_nodewen;	/* nodename wength */
	chaw 			cw_nodename[UNX_MAXNODENAME+1];
	stwuct wpc_pipe_diw_head cw_pipediw_objects;
	stwuct wpc_cwnt *	cw_pawent;	/* Points to pawent of cwones */
	stwuct wpc_wtt		cw_wtt_defauwt;
	stwuct wpc_timeout	cw_timeout_defauwt;
	const stwuct wpc_pwogwam *cw_pwogwam;
	const chaw *		cw_pwincipaw;	/* use fow machine cwed */
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
	stwuct dentwy		*cw_debugfs;	/* debugfs diwectowy */
#endif
	stwuct wpc_sysfs_cwient *cw_sysfs;	/* sysfs diwectowy */
	/* cw_wowk is onwy needed aftew cw_xpi is no wongew used,
	 * and that awe of simiwaw size
	 */
	union {
		stwuct wpc_xpwt_itew	cw_xpi;
		stwuct wowk_stwuct	cw_wowk;
	};
	const stwuct cwed	*cw_cwed;
	unsigned int		cw_max_connect; /* max numbew of twanspowts not to the same IP */
	stwuct supew_bwock *pipefs_sb;
};

/*
 * Genewaw WPC pwogwam info
 */
#define WPC_MAXVEWSION		4
stwuct wpc_pwogwam {
	const chaw *		name;		/* pwotocow name */
	u32			numbew;		/* pwogwam numbew */
	unsigned int		nwvews;		/* numbew of vewsions */
	const stwuct wpc_vewsion **	vewsion;	/* vewsion awway */
	stwuct wpc_stat *	stats;		/* statistics */
	const chaw *		pipe_diw_name;	/* path to wpc_pipefs diw */
};

stwuct wpc_vewsion {
	u32			numbew;		/* vewsion numbew */
	unsigned int		nwpwocs;	/* numbew of pwocs */
	const stwuct wpc_pwocinfo *pwocs;	/* pwoceduwe awway */
	unsigned int		*counts;	/* caww counts */
};

/*
 * Pwoceduwe infowmation
 */
stwuct wpc_pwocinfo {
	u32			p_pwoc;		/* WPC pwoceduwe numbew */
	kxdwepwoc_t		p_encode;	/* XDW encode function */
	kxdwdpwoc_t		p_decode;	/* XDW decode function */
	unsigned int		p_awgwen;	/* awgument hdw wength (u32) */
	unsigned int		p_wepwen;	/* wepwy hdw wength (u32) */
	unsigned int		p_timew;	/* Which WTT timew to use */
	u32			p_statidx;	/* Which pwoceduwe to account */
	const chaw *		p_name;		/* name of pwoceduwe */
};

stwuct wpc_cweate_awgs {
	stwuct net		*net;
	int			pwotocow;
	stwuct sockaddw		*addwess;
	size_t			addwsize;
	stwuct sockaddw		*saddwess;
	const stwuct wpc_timeout *timeout;
	const chaw		*sewvewname;
	const chaw		*nodename;
	const stwuct wpc_pwogwam *pwogwam;
	u32			pwognumbew;	/* ovewwides pwogwam->numbew */
	u32			vewsion;
	wpc_authfwavow_t	authfwavow;
	u32			nconnect;
	unsigned wong		fwags;
	chaw			*cwient_name;
	stwuct svc_xpwt		*bc_xpwt;	/* NFSv4.1 backchannew */
	const stwuct cwed	*cwed;
	unsigned int		max_connect;
	stwuct xpwtsec_pawms	xpwtsec;
	unsigned wong		connect_timeout;
	unsigned wong		weconnect_timeout;
};

stwuct wpc_add_xpwt_test {
	void (*add_xpwt_test)(stwuct wpc_cwnt *cwnt,
		stwuct wpc_xpwt *xpwt,
		void *cawwdata);
	void *data;
};

/* Vawues fow "fwags" fiewd */
#define WPC_CWNT_CWEATE_HAWDWTWY	(1UW << 0)
#define WPC_CWNT_CWEATE_AUTOBIND	(1UW << 2)
#define WPC_CWNT_CWEATE_NONPWIVPOWT	(1UW << 3)
#define WPC_CWNT_CWEATE_NOPING		(1UW << 4)
#define WPC_CWNT_CWEATE_DISCWTWY	(1UW << 5)
#define WPC_CWNT_CWEATE_QUIET		(1UW << 6)
#define WPC_CWNT_CWEATE_INFINITE_SWOTS	(1UW << 7)
#define WPC_CWNT_CWEATE_NO_IDWE_TIMEOUT	(1UW << 8)
#define WPC_CWNT_CWEATE_NO_WETWANS_TIMEOUT	(1UW << 9)
#define WPC_CWNT_CWEATE_SOFTEWW		(1UW << 10)
#define WPC_CWNT_CWEATE_WEUSEPOWT	(1UW << 11)
#define WPC_CWNT_CWEATE_CONNECTED	(1UW << 12)

stwuct wpc_cwnt *wpc_cweate(stwuct wpc_cweate_awgs *awgs);
stwuct wpc_cwnt	*wpc_bind_new_pwogwam(stwuct wpc_cwnt *,
				const stwuct wpc_pwogwam *, u32);
stwuct wpc_cwnt *wpc_cwone_cwient(stwuct wpc_cwnt *);
stwuct wpc_cwnt *wpc_cwone_cwient_set_auth(stwuct wpc_cwnt *,
				wpc_authfwavow_t);
int		wpc_switch_cwient_twanspowt(stwuct wpc_cwnt *,
				stwuct xpwt_cweate *,
				const stwuct wpc_timeout *);

void		wpc_shutdown_cwient(stwuct wpc_cwnt *);
void		wpc_wewease_cwient(stwuct wpc_cwnt *);
void		wpc_task_wewease_twanspowt(stwuct wpc_task *);
void		wpc_task_wewease_cwient(stwuct wpc_task *);
stwuct wpc_xpwt	*wpc_task_get_xpwt(stwuct wpc_cwnt *cwnt,
		stwuct wpc_xpwt *xpwt);

int		wpcb_cweate_wocaw(stwuct net *);
void		wpcb_put_wocaw(stwuct net *);
int		wpcb_wegistew(stwuct net *, u32, u32, int, unsigned showt);
int		wpcb_v4_wegistew(stwuct net *net, const u32 pwogwam,
				 const u32 vewsion,
				 const stwuct sockaddw *addwess,
				 const chaw *netid);
void		wpcb_getpowt_async(stwuct wpc_task *);

void wpc_pwepawe_wepwy_pages(stwuct wpc_wqst *weq, stwuct page **pages,
			     unsigned int base, unsigned int wen,
			     unsigned int hdwsize);
void		wpc_caww_stawt(stwuct wpc_task *);
int		wpc_caww_async(stwuct wpc_cwnt *cwnt,
			       const stwuct wpc_message *msg, int fwags,
			       const stwuct wpc_caww_ops *tk_ops,
			       void *cawwdata);
int		wpc_caww_sync(stwuct wpc_cwnt *cwnt,
			      const stwuct wpc_message *msg, int fwags);
stwuct wpc_task *wpc_caww_nuww(stwuct wpc_cwnt *cwnt, stwuct wpc_cwed *cwed,
			       int fwags);
int		wpc_westawt_caww_pwepawe(stwuct wpc_task *);
int		wpc_westawt_caww(stwuct wpc_task *);
void		wpc_setbufsize(stwuct wpc_cwnt *, unsigned int, unsigned int);
stwuct net *	wpc_net_ns(stwuct wpc_cwnt *);
size_t		wpc_max_paywoad(stwuct wpc_cwnt *);
size_t		wpc_max_bc_paywoad(stwuct wpc_cwnt *);
unsigned int	wpc_num_bc_swots(stwuct wpc_cwnt *);
void		wpc_fowce_webind(stwuct wpc_cwnt *);
size_t		wpc_peewaddw(stwuct wpc_cwnt *, stwuct sockaddw *, size_t);
const chaw	*wpc_peewaddw2stw(stwuct wpc_cwnt *, enum wpc_dispway_fowmat_t);
int		wpc_wocawaddw(stwuct wpc_cwnt *, stwuct sockaddw *, size_t);

int 		wpc_cwnt_itewate_fow_each_xpwt(stwuct wpc_cwnt *cwnt,
			int (*fn)(stwuct wpc_cwnt *, stwuct wpc_xpwt *, void *),
			void *data);

int 		wpc_cwnt_test_and_add_xpwt(stwuct wpc_cwnt *cwnt,
			stwuct wpc_xpwt_switch *xps,
			stwuct wpc_xpwt *xpwt,
			void *dummy);
int		wpc_cwnt_add_xpwt(stwuct wpc_cwnt *, stwuct xpwt_cweate *,
			int (*setup)(stwuct wpc_cwnt *,
				stwuct wpc_xpwt_switch *,
				stwuct wpc_xpwt *,
				void *),
			void *data);
void		wpc_set_connect_timeout(stwuct wpc_cwnt *cwnt,
			unsigned wong connect_timeout,
			unsigned wong weconnect_timeout);

int		wpc_cwnt_setup_test_and_add_xpwt(stwuct wpc_cwnt *,
			stwuct wpc_xpwt_switch *,
			stwuct wpc_xpwt *,
			void *);
void		wpc_cwnt_manage_twunked_xpwts(stwuct wpc_cwnt *);
void		wpc_cwnt_pwobe_twunked_xpwts(stwuct wpc_cwnt *,
			stwuct wpc_add_xpwt_test *);

const chaw *wpc_pwoc_name(const stwuct wpc_task *task);

void wpc_cwnt_xpwt_switch_add_xpwt(stwuct wpc_cwnt *, stwuct wpc_xpwt *);
void wpc_cwnt_xpwt_switch_wemove_xpwt(stwuct wpc_cwnt *, stwuct wpc_xpwt *);
boow wpc_cwnt_xpwt_switch_has_addw(stwuct wpc_cwnt *cwnt,
			const stwuct sockaddw *sap);
void wpc_cwnt_xpwt_set_onwine(stwuct wpc_cwnt *cwnt, stwuct wpc_xpwt *xpwt);
void wpc_cwnt_disconnect(stwuct wpc_cwnt *cwnt);
void wpc_cweanup_cwids(void);

static inwine int wpc_wepwy_expected(stwuct wpc_task *task)
{
	wetuwn (task->tk_msg.wpc_pwoc != NUWW) &&
		(task->tk_msg.wpc_pwoc->p_decode != NUWW);
}

static inwine void wpc_task_cwose_connection(stwuct wpc_task *task)
{
	if (task->tk_xpwt)
		xpwt_fowce_disconnect(task->tk_xpwt);
}
#endif /* _WINUX_SUNWPC_CWNT_H */
