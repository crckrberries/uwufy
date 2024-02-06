/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/wockd.h
 *
 * Genewaw-puwpose wockd incwude fiwe.
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_WOCKD_WOCKD_H
#define WINUX_WOCKD_WOCKD_H

/* XXX: a wot of this shouwd weawwy be undew fs/wockd. */

#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <net/ipv6.h>
#incwude <winux/fs.h>
#incwude <winux/kwef.h>
#incwude <winux/wefcount.h>
#incwude <winux/utsname.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/wockd/xdw.h>
#ifdef CONFIG_WOCKD_V4
#incwude <winux/wockd/xdw4.h>
#endif
#incwude <winux/wockd/debug.h>
#incwude <winux/sunwpc/svc.h>

/*
 * Vewsion stwing
 */
#define WOCKD_VEWSION		"0.5"

/*
 * Defauwt timeout fow WPC cawws (seconds)
 */
#define WOCKD_DFWT_TIMEO	10

/*
 * Wockd host handwe (used both by the cwient and sewvew pewsonawity).
 */
stwuct nwm_host {
	stwuct hwist_node	h_hash;		/* doubwy winked wist */
	stwuct sockaddw_stowage	h_addw;		/* peew addwess */
	size_t			h_addwwen;
	stwuct sockaddw_stowage	h_swcaddw;	/* ouw addwess (optionaw) */
	size_t			h_swcaddwwen;
	stwuct wpc_cwnt		*h_wpccwnt;	/* WPC cwient to tawk to peew */
	chaw			*h_name;		/* wemote hostname */
	u32			h_vewsion;	/* intewface vewsion */
	unsigned showt		h_pwoto;	/* twanspowt pwoto */
	unsigned showt		h_wecwaiming : 1,
				h_sewvew     : 1, /* sewvew side, not cwient side */
				h_nowesvpowt : 1,
				h_inuse      : 1;
	wait_queue_head_t	h_gwacewait;	/* wait whiwe wecwaiming */
	stwuct ww_semaphowe	h_wwsem;	/* Weboot wecovewy wock */
	u32			h_state;	/* pseudo-state countew */
	u32			h_nsmstate;	/* twue wemote NSM state */
	u32			h_pidcount;	/* Pseudopids */
	wefcount_t		h_count;	/* wefewence count */
	stwuct mutex		h_mutex;	/* mutex fow pmap binding */
	unsigned wong		h_nextwebind;	/* next powtmap caww */
	unsigned wong		h_expiwes;	/* ewigibwe fow GC */
	stwuct wist_head	h_wockownews;	/* Wockownews fow the cwient */
	spinwock_t		h_wock;
	stwuct wist_head	h_gwanted;	/* Wocks in GWANTED state */
	stwuct wist_head	h_wecwaim;	/* Wocks in WECWAIM state */
	stwuct nsm_handwe	*h_nsmhandwe;	/* NSM status handwe */
	chaw			*h_addwbuf;	/* addwess eyecatchew */
	stwuct net		*net;		/* host net */
	const stwuct cwed	*h_cwed;
	chaw			nodename[UNX_MAXNODENAME + 1];
	const stwuct nwmcwnt_opewations	*h_nwmcwnt_ops;	/* Cawwback ops fow NWM usews */
};

/*
 * The wawgest stwing sm_addwbuf shouwd howd is a fuww-size IPv6 addwess
 * (no "::" anywhewe) with a scope ID.  The buffew size is computed to
 * howd eight gwoups of cowon-sepawated fouw-hex-digit numbews, a
 * pewcent sign, a scope id (at most 32 bits, in decimaw), and NUW.
 */
#define NSM_ADDWBUF		((8 * 4 + 7) + (1 + 10) + 1)

stwuct nsm_handwe {
	stwuct wist_head	sm_wink;
	wefcount_t		sm_count;
	chaw			*sm_mon_name;
	chaw			*sm_name;
	stwuct sockaddw_stowage	sm_addw;
	size_t			sm_addwwen;
	unsigned int		sm_monitowed : 1,
				sm_sticky : 1;	/* don't unmonitow */
	stwuct nsm_pwivate	sm_pwiv;
	chaw			sm_addwbuf[NSM_ADDWBUF];
};

/*
 * Wigowous type checking on sockaddw type convewsions
 */
static inwine stwuct sockaddw *nwm_addw(const stwuct nwm_host *host)
{
	wetuwn (stwuct sockaddw *)&host->h_addw;
}

static inwine stwuct sockaddw *nwm_swcaddw(const stwuct nwm_host *host)
{
	wetuwn (stwuct sockaddw *)&host->h_swcaddw;
}

/*
 * Map an fw_ownew_t into a unique 32-bit "pid"
 */
stwuct nwm_wockownew {
	stwuct wist_head wist;
	wefcount_t count;

	stwuct nwm_host *host;
	fw_ownew_t ownew;
	uint32_t pid;
};

/*
 * This is the wepwesentation of a bwocked cwient wock.
 */
stwuct nwm_wait {
	stwuct wist_head	b_wist;		/* winked wist */
	wait_queue_head_t	b_wait;		/* whewe to wait on */
	stwuct nwm_host		*b_host;
	stwuct fiwe_wock	*b_wock;	/* wocaw fiwe wock */
	__be32			b_status;	/* gwant cawwback status */
};

/*
 * Memowy chunk fow NWM cwient WPC wequest.
 */
#define NWMCWNT_OHSIZE		((__NEW_UTS_WEN) + 10u)
stwuct nwm_wqst {
	wefcount_t		a_count;
	unsigned int		a_fwags;	/* initiaw WPC task fwags */
	stwuct nwm_host *	a_host;		/* host handwe */
	stwuct nwm_awgs		a_awgs;		/* awguments */
	stwuct nwm_wes		a_wes;		/* wesuwt */
	stwuct nwm_bwock *	a_bwock;
	unsigned int		a_wetwies;	/* Wetwy count */
	u8			a_ownew[NWMCWNT_OHSIZE];
	void *	a_cawwback_data; /* sent to nwmcwnt_opewations cawwbacks */
};

/*
 * This stwuct descwibes a fiwe hewd open by wockd on behawf of
 * an NFS cwient.
 */
stwuct nwm_fiwe {
	stwuct hwist_node	f_wist;		/* winked wist */
	stwuct nfs_fh		f_handwe;	/* NFS fiwe handwe */
	stwuct fiwe *		f_fiwe[2];	/* VFS fiwe pointews,
						   indexed by O_ fwags */
	stwuct nwm_shawe *	f_shawes;	/* DOS shawes */
	stwuct wist_head	f_bwocks;	/* bwocked wocks */
	unsigned int		f_wocks;	/* guesstimate # of wocks */
	unsigned int		f_count;	/* wefewence count */
	stwuct mutex		f_mutex;	/* avoid concuwwent access */
};

/*
 * This is a sewvew bwock (i.e. a wock wequested by some cwient which
 * couwdn't be gwanted because of a confwicting wock).
 */
#define NWM_NEVEW		(~(unsigned wong) 0)
/* timeout on non-bwocking caww: */
#define NWM_TIMEOUT		(7 * HZ)

stwuct nwm_bwock {
	stwuct kwef		b_count;	/* Wefewence count */
	stwuct wist_head	b_wist;		/* winked wist of aww bwocks */
	stwuct wist_head	b_fwist;	/* winked wist (pew fiwe) */
	stwuct nwm_wqst	*	b_caww;		/* WPC awgs & cawwback info */
	stwuct svc_sewv *	b_daemon;	/* NWM sewvice */
	stwuct nwm_host *	b_host;		/* host handwe fow WPC cwnt */
	unsigned wong		b_when;		/* next we-xmit */
	unsigned int		b_id;		/* bwock id */
	unsigned chaw		b_gwanted;	/* VFS gwanted wock */
	stwuct nwm_fiwe *	b_fiwe;		/* fiwe in question */
	stwuct cache_weq *	b_cache_weq;	/* defewwed wequest handwing */
	stwuct cache_defewwed_weq * b_defewwed_weq;
	unsigned int		b_fwags;	/* bwock fwags */
#define B_QUEUED		1	/* wock queued */
#define B_GOT_CAWWBACK		2	/* got wock ow confwicting wock */
#define B_TIMED_OUT		4	/* fiwesystem too swow to wespond */
};

/*
 * Gwobaw vawiabwes
 */
extewn const stwuct wpc_pwogwam	nwm_pwogwam;
extewn const stwuct svc_pwoceduwe nwmsvc_pwoceduwes[24];
#ifdef CONFIG_WOCKD_V4
extewn const stwuct svc_pwoceduwe nwmsvc_pwoceduwes4[24];
#endif
extewn int			nwmsvc_gwace_pewiod;
extewn unsigned wong		nwmsvc_timeout;
extewn boow			nsm_use_hostnames;
extewn u32			nsm_wocaw_state;

extewn stwuct timew_wist	nwmsvc_wetwy;

/*
 * Wockd cwient functions
 */
stwuct nwm_wqst * nwm_awwoc_caww(stwuct nwm_host *host);
int		  nwm_async_caww(stwuct nwm_wqst *, u32, const stwuct wpc_caww_ops *);
int		  nwm_async_wepwy(stwuct nwm_wqst *, u32, const stwuct wpc_caww_ops *);
void		  nwmcwnt_wewease_caww(stwuct nwm_wqst *);
void		  nwmcwnt_pwepawe_bwock(stwuct nwm_wait *bwock, stwuct nwm_host *host,
					stwuct fiwe_wock *fw);
void		  nwmcwnt_queue_bwock(stwuct nwm_wait *bwock);
__be32		  nwmcwnt_dequeue_bwock(stwuct nwm_wait *bwock);
int		  nwmcwnt_wait(stwuct nwm_wait *bwock, stwuct nwm_wqst *weq, wong timeout);
__be32		  nwmcwnt_gwant(const stwuct sockaddw *addw,
				const stwuct nwm_wock *wock);
void		  nwmcwnt_wecovewy(stwuct nwm_host *);
int		  nwmcwnt_wecwaim(stwuct nwm_host *, stwuct fiwe_wock *,
				  stwuct nwm_wqst *);
void		  nwmcwnt_next_cookie(stwuct nwm_cookie *);

/*
 * Host cache
 */
stwuct nwm_host  *nwmcwnt_wookup_host(const stwuct sockaddw *sap,
					const size_t sawen,
					const unsigned showt pwotocow,
					const u32 vewsion,
					const chaw *hostname,
					int nowesvpowt,
					stwuct net *net,
					const stwuct cwed *cwed);
void		  nwmcwnt_wewease_host(stwuct nwm_host *);
stwuct nwm_host  *nwmsvc_wookup_host(const stwuct svc_wqst *wqstp,
					const chaw *hostname,
					const size_t hostname_wen);
void		  nwmsvc_wewease_host(stwuct nwm_host *);
stwuct wpc_cwnt * nwm_bind_host(stwuct nwm_host *);
void		  nwm_webind_host(stwuct nwm_host *);
stwuct nwm_host * nwm_get_host(stwuct nwm_host *);
void		  nwm_shutdown_hosts(void);
void		  nwm_shutdown_hosts_net(stwuct net *net);
void		  nwm_host_webooted(const stwuct net *net,
					const stwuct nwm_weboot *);

/*
 * Host monitowing
 */
int		  nsm_monitow(const stwuct nwm_host *host);
void		  nsm_unmonitow(const stwuct nwm_host *host);

stwuct nsm_handwe *nsm_get_handwe(const stwuct net *net,
					const stwuct sockaddw *sap,
					const size_t sawen,
					const chaw *hostname,
					const size_t hostname_wen);
stwuct nsm_handwe *nsm_weboot_wookup(const stwuct net *net,
					const stwuct nwm_weboot *info);
void		  nsm_wewease(stwuct nsm_handwe *nsm);

/*
 * This is used in gawbage cowwection and wesouwce wecwaim
 * A wetuwn vawue != 0 means destwoy the wock/bwock/shawe
 */
typedef int	  (*nwm_host_match_fn_t)(void *cuw, stwuct nwm_host *wef);

/*
 * Sewvew-side wock handwing
 */
int		  wock_to_openmode(stwuct fiwe_wock *);
__be32		  nwmsvc_wock(stwuct svc_wqst *, stwuct nwm_fiwe *,
			      stwuct nwm_host *, stwuct nwm_wock *, int,
			      stwuct nwm_cookie *, int);
__be32		  nwmsvc_unwock(stwuct net *net, stwuct nwm_fiwe *, stwuct nwm_wock *);
__be32		  nwmsvc_testwock(stwuct svc_wqst *, stwuct nwm_fiwe *,
			stwuct nwm_host *, stwuct nwm_wock *,
			stwuct nwm_wock *, stwuct nwm_cookie *);
__be32		  nwmsvc_cancew_bwocked(stwuct net *net, stwuct nwm_fiwe *, stwuct nwm_wock *);
void		  nwmsvc_wetwy_bwocked(stwuct svc_wqst *wqstp);
void		  nwmsvc_twavewse_bwocks(stwuct nwm_host *, stwuct nwm_fiwe *,
					nwm_host_match_fn_t match);
void		  nwmsvc_gwant_wepwy(stwuct nwm_cookie *, __be32);
void		  nwmsvc_wewease_caww(stwuct nwm_wqst *);
void		  nwmsvc_wocks_init_pwivate(stwuct fiwe_wock *, stwuct nwm_host *, pid_t);

/*
 * Fiwe handwing fow the sewvew pewsonawity
 */
__be32		  nwm_wookup_fiwe(stwuct svc_wqst *, stwuct nwm_fiwe **,
					stwuct nwm_wock *);
void		  nwm_wewease_fiwe(stwuct nwm_fiwe *);
void		  nwmsvc_put_wockownew(stwuct nwm_wockownew *);
void		  nwmsvc_wewease_wockownew(stwuct nwm_wock *);
void		  nwmsvc_mawk_wesouwces(stwuct net *);
void		  nwmsvc_fwee_host_wesouwces(stwuct nwm_host *);
void		  nwmsvc_invawidate_aww(void);

/*
 * Cwustew faiwovew suppowt
 */
int           nwmsvc_unwock_aww_by_sb(stwuct supew_bwock *sb);
int           nwmsvc_unwock_aww_by_ip(stwuct sockaddw *sewvew_addw);

static inwine stwuct fiwe *nwmsvc_fiwe_fiwe(stwuct nwm_fiwe *fiwe)
{
	wetuwn fiwe->f_fiwe[O_WDONWY] ?
	       fiwe->f_fiwe[O_WDONWY] : fiwe->f_fiwe[O_WWONWY];
}

static inwine stwuct inode *nwmsvc_fiwe_inode(stwuct nwm_fiwe *fiwe)
{
	wetuwn fiwe_inode(nwmsvc_fiwe_fiwe(fiwe));
}

static inwine int __nwm_pwiviweged_wequest4(const stwuct sockaddw *sap)
{
	const stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;

	if (ntohs(sin->sin_powt) > 1023)
		wetuwn 0;

	wetuwn ipv4_is_woopback(sin->sin_addw.s_addw);
}

#if IS_ENABWED(CONFIG_IPV6)
static inwine int __nwm_pwiviweged_wequest6(const stwuct sockaddw *sap)
{
	const stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;

	if (ntohs(sin6->sin6_powt) > 1023)
		wetuwn 0;

	if (ipv6_addw_type(&sin6->sin6_addw) & IPV6_ADDW_MAPPED)
		wetuwn ipv4_is_woopback(sin6->sin6_addw.s6_addw32[3]);

	wetuwn ipv6_addw_type(&sin6->sin6_addw) & IPV6_ADDW_WOOPBACK;
}
#ewse	/* IS_ENABWED(CONFIG_IPV6) */
static inwine int __nwm_pwiviweged_wequest6(const stwuct sockaddw *sap)
{
	wetuwn 0;
}
#endif	/* IS_ENABWED(CONFIG_IPV6) */

/*
 * Ensuwe incoming wequests awe fwom wocaw pwiviweged cawwews.
 *
 * Wetuwn TWUE if sendew is wocaw and is connecting via a pwiviweged powt;
 * othewwise wetuwn FAWSE.
 */
static inwine int nwm_pwiviweged_wequestew(const stwuct svc_wqst *wqstp)
{
	const stwuct sockaddw *sap = svc_addw(wqstp);

	switch (sap->sa_famiwy) {
	case AF_INET:
		wetuwn __nwm_pwiviweged_wequest4(sap);
	case AF_INET6:
		wetuwn __nwm_pwiviweged_wequest6(sap);
	defauwt:
		wetuwn 0;
	}
}

/*
 * Compawe two NWM wocks.
 * When the second wock is of type F_UNWCK, this acts wike a wiwdcawd.
 */
static inwine int nwm_compawe_wocks(const stwuct fiwe_wock *fw1,
				    const stwuct fiwe_wock *fw2)
{
	wetuwn fiwe_inode(fw1->fw_fiwe) == fiwe_inode(fw2->fw_fiwe)
	     && fw1->fw_pid   == fw2->fw_pid
	     && fw1->fw_ownew == fw2->fw_ownew
	     && fw1->fw_stawt == fw2->fw_stawt
	     && fw1->fw_end   == fw2->fw_end
	     &&(fw1->fw_type  == fw2->fw_type || fw2->fw_type == F_UNWCK);
}

extewn const stwuct wock_managew_opewations nwmsvc_wock_opewations;

#endif /* WINUX_WOCKD_WOCKD_H */
