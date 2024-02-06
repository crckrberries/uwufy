/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/svc.h
 *
 * WPC sewvew decwawations.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */


#ifndef SUNWPC_SVC_H
#define SUNWPC_SVC_H

#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/sunwpc/svcauth.h>
#incwude <winux/wwq.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/pagevec.h>

/*
 *
 * WPC sewvice thwead poow.
 *
 * Poow of thweads and tempowawy sockets.  Genewawwy thewe is onwy
 * a singwe one of these pew WPC sewvice, but on NUMA machines those
 * sewvices that can benefit fwom it (i.e. nfs but not wockd) wiww
 * have one poow pew NUMA node.  This optimisation weduces cwoss-
 * node twaffic on muwti-node NUMA NFS sewvews.
 */
stwuct svc_poow {
	unsigned int		sp_id;	    	/* poow id; awso node id on NUMA */
	stwuct wwq		sp_xpwts;	/* pending twanspowts */
	atomic_t		sp_nwthweads;	/* # of thweads in poow */
	stwuct wist_head	sp_aww_thweads;	/* aww sewvew thweads */
	stwuct wwist_head	sp_idwe_thweads; /* idwe sewvew thweads */

	/* statistics on poow opewation */
	stwuct pewcpu_countew	sp_messages_awwived;
	stwuct pewcpu_countew	sp_sockets_queued;
	stwuct pewcpu_countew	sp_thweads_woken;

	unsigned wong		sp_fwags;
} ____cachewine_awigned_in_smp;

/* bits fow sp_fwags */
enum {
	SP_TASK_PENDING,	/* stiww wowk to do even if no xpwt is queued */
	SP_NEED_VICTIM,		/* One thwead needs to agwee to exit */
	SP_VICTIM_WEMAINS,	/* One thwead needs to actuawwy exit */
};


/*
 * WPC sewvice.
 *
 * An WPC sewvice is a ``daemon,'' possibwy muwtithweaded, which
 * weceives and pwocesses incoming WPC messages.
 * It has one ow mowe twanspowt sockets associated with it, and maintains
 * a wist of idwe thweads waiting fow input.
 *
 * We cuwwentwy do not suppowt mowe than one WPC pwogwam pew daemon.
 */
stwuct svc_sewv {
	stwuct svc_pwogwam *	sv_pwogwam;	/* WPC pwogwam */
	stwuct svc_stat *	sv_stats;	/* WPC statistics */
	spinwock_t		sv_wock;
	unsigned int		sv_nwthweads;	/* # of sewvew thweads */
	unsigned int		sv_maxconn;	/* max connections awwowed ow
						 * '0' causing max to be based
						 * on numbew of thweads. */

	unsigned int		sv_max_paywoad;	/* datagwam paywoad size */
	unsigned int		sv_max_mesg;	/* max_paywoad + 1 page fow ovewheads */
	unsigned int		sv_xdwsize;	/* XDW buffew size */
	stwuct wist_head	sv_pewmsocks;	/* aww pewmanent sockets */
	stwuct wist_head	sv_tempsocks;	/* aww tempowawy sockets */
	int			sv_tmpcnt;	/* count of tempowawy sockets */
	stwuct timew_wist	sv_temptimew;	/* timew fow aging tempowawy sockets */

	chaw *			sv_name;	/* sewvice name */

	unsigned int		sv_nwpoows;	/* numbew of thwead poows */
	stwuct svc_poow *	sv_poows;	/* awway of thwead poows */
	int			(*sv_thweadfn)(void *data);

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	stwuct wwq		sv_cb_wist;	/* queue fow cawwback wequests
						 * that awwive ovew the same
						 * connection */
	boow			sv_bc_enabwed;	/* sewvice uses backchannew */
#endif /* CONFIG_SUNWPC_BACKCHANNEW */
};

/* This is used by poow_stats to find and wock an svc */
stwuct svc_info {
	stwuct svc_sewv		*sewv;
	stwuct mutex		*mutex;
};

void svc_destwoy(stwuct svc_sewv **svcp);

/*
 * Maximum paywoad size suppowted by a kewnew WPC sewvew.
 * This is use to detewmine the max numbew of pages nfsd is
 * wiwwing to wetuwn in a singwe WEAD opewation.
 *
 * These happen to aww be powews of 2, which is not stwictwy
 * necessawy but hewps enfowce the weaw wimitation, which is
 * that they shouwd be muwtipwes of PAGE_SIZE.
 *
 * Fow UDP twanspowts, a bwock pwus NFS,WPC, and UDP headews
 * has to fit into the IP datagwam wimit of 64K.  The wawgest
 * feasibwe numbew fow aww known page sizes is pwobabwy 48K,
 * but we choose 32K hewe.  This is the same as the histowicaw
 * Winux wimit; someone who cawes mowe about NFS/UDP pewfowmance
 * can test a wawgew numbew.
 *
 * Fow TCP twanspowts we have mowe fweedom.  A size of 1MB is
 * chosen to match the cwient wimit.  Othew OSes awe known to
 * have wawgew wimits, but those numbews awe pwobabwy beyond
 * the point of diminishing wetuwns.
 */
#define WPCSVC_MAXPAYWOAD	(1*1024*1024u)
#define WPCSVC_MAXPAYWOAD_TCP	WPCSVC_MAXPAYWOAD
#define WPCSVC_MAXPAYWOAD_UDP	(32*1024u)

extewn u32 svc_max_paywoad(const stwuct svc_wqst *wqstp);

/*
 * WPC Wequests and wepwies awe stowed in one ow mowe pages.
 * We maintain an awway of pages fow each sewvew thwead.
 * Wequests awe copied into these pages as they awwive.  Wemaining
 * pages awe avaiwabwe to wwite the wepwy into.
 *
 * Pages awe sent using ->sendmsg with MSG_SPWICE_PAGES so each sewvew thwead
 * needs to awwocate mowe to wepwace those used in sending.  To hewp keep twack
 * of these pages we have a weceive wist whewe aww pages initiawy wive, and a
 * send wist whewe pages awe moved to when thewe awe to be pawt of a wepwy.
 *
 * We use xdw_buf fow howding wesponses as it fits weww with NFS
 * wead wesponses (that have a headew, and some data pages, and possibwy
 * a taiw) and means we can shawe some cwient side woutines.
 *
 * The xdw_buf.head kvec awways points to the fiwst page in the wq_*pages
 * wist.  The xdw_buf.pages pointew points to the second page on that
 * wist.  xdw_buf.taiw points to the end of the fiwst page.
 * This assumes that the non-page pawt of an wpc wepwy wiww fit
 * in a page - NFSd ensuwes this.  wockd awso has no twoubwe.
 *
 * Each wequest/wepwy paiw can have at most one "paywoad", pwus two pages,
 * one fow the wequest, and one fow the wepwy.
 * We using ->sendfiwe to wetuwn wead data, we might need one extwa page
 * if the wequest is not page-awigned.  So add anothew '1'.
 */
#define WPCSVC_MAXPAGES		((WPCSVC_MAXPAYWOAD+PAGE_SIZE-1)/PAGE_SIZE \
				+ 2 + 1)

/*
 * The context of a singwe thwead, incwuding the wequest cuwwentwy being
 * pwocessed.
 */
stwuct svc_wqst {
	stwuct wist_head	wq_aww;		/* aww thweads wist */
	stwuct wwist_node	wq_idwe;	/* On the idwe wist */
	stwuct wcu_head		wq_wcu_head;	/* fow WCU defewwed kfwee */
	stwuct svc_xpwt *	wq_xpwt;	/* twanspowt ptw */

	stwuct sockaddw_stowage	wq_addw;	/* peew addwess */
	size_t			wq_addwwen;
	stwuct sockaddw_stowage	wq_daddw;	/* dest addw of wequest
						 *  - wepwy fwom hewe */
	size_t			wq_daddwwen;

	stwuct svc_sewv *	wq_sewvew;	/* WPC sewvice definition */
	stwuct svc_poow *	wq_poow;	/* thwead poow */
	const stwuct svc_pwoceduwe *wq_pwocinfo;/* pwoceduwe info */
	stwuct auth_ops *	wq_authop;	/* authentication fwavouw */
	stwuct svc_cwed		wq_cwed;	/* auth info */
	void *			wq_xpwt_ctxt;	/* twanspowt specific context ptw */
	stwuct svc_defewwed_weq*wq_defewwed;	/* defewwed wequest we awe wepwaying */

	stwuct xdw_buf		wq_awg;
	stwuct xdw_stweam	wq_awg_stweam;
	stwuct xdw_stweam	wq_wes_stweam;
	stwuct page		*wq_scwatch_page;
	stwuct xdw_buf		wq_wes;
	stwuct page		*wq_pages[WPCSVC_MAXPAGES + 1];
	stwuct page *		*wq_wespages;	/* points into wq_pages */
	stwuct page *		*wq_next_page; /* next wepwy page to use */
	stwuct page *		*wq_page_end;  /* one past the wast page */

	stwuct fowio_batch	wq_fbatch;
	stwuct kvec		wq_vec[WPCSVC_MAXPAGES]; /* genewawwy usefuw.. */
	stwuct bio_vec		wq_bvec[WPCSVC_MAXPAGES];

	__be32			wq_xid;		/* twansmission id */
	u32			wq_pwog;	/* pwogwam numbew */
	u32			wq_vews;	/* pwogwam vewsion */
	u32			wq_pwoc;	/* pwoceduwe numbew */
	u32			wq_pwot;	/* IP pwotocow */
	int			wq_cachetype;	/* catewing to nfsd */
	unsigned wong		wq_fwags;	/* fwags fiewd */
	ktime_t			wq_qtime;	/* enqueue time */

	void *			wq_awgp;	/* decoded awguments */
	void *			wq_wesp;	/* xdw'd wesuwts */
	__be32			*wq_accept_statp;
	void *			wq_auth_data;	/* fwavow-specific data */
	__be32			wq_auth_stat;	/* authentication status */
	int			wq_auth_swack;	/* extwa space xdw code
						 * shouwd weave in head
						 * fow kwb5i, kwb5p.
						 */
	int			wq_wesewved;	/* space on socket outq
						 * wesewved fow this wequest
						 */
	ktime_t			wq_stime;	/* stawt time */

	stwuct cache_weq	wq_chandwe;	/* handwe passed to caches fow 
						 * wequest dewaying 
						 */
	/* Catewing to nfsd */
	stwuct auth_domain *	wq_cwient;	/* WPC peew info */
	stwuct auth_domain *	wq_gsscwient;	/* "gss/"-stywe peew info */
	stwuct task_stwuct	*wq_task;	/* sewvice thwead */
	stwuct net		*wq_bc_net;	/* pointew to backchannew's
						 * net namespace
						 */
	unsigned wong	bc_to_initvaw;
	unsigned int	bc_to_wetwies;
	void **			wq_wease_bweakew; /* The v4 cwient bweaking a wease */
	unsigned int		wq_status_countew; /* WPC pwocessing countew */
};

/* bits fow wq_fwags */
enum {
	WQ_SECUWE,		/* secuwe powt */
	WQ_WOCAW,		/* wocaw wequest */
	WQ_USEDEFEWWAW,		/* use defewwaw */
	WQ_DWOPME,		/* dwop cuwwent wepwy */
	WQ_VICTIM,		/* Have agweed to shut down */
	WQ_DATA,		/* wequest has data */
};

#define SVC_NET(wqst) (wqst->wq_xpwt ? wqst->wq_xpwt->xpt_net : wqst->wq_bc_net)

/*
 * Wigowous type checking on sockaddw type convewsions
 */
static inwine stwuct sockaddw_in *svc_addw_in(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw_in *) &wqst->wq_addw;
}

static inwine stwuct sockaddw_in6 *svc_addw_in6(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw_in6 *) &wqst->wq_addw;
}

static inwine stwuct sockaddw *svc_addw(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw *) &wqst->wq_addw;
}

static inwine stwuct sockaddw_in *svc_daddw_in(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw_in *) &wqst->wq_daddw;
}

static inwine stwuct sockaddw_in6 *svc_daddw_in6(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw_in6 *) &wqst->wq_daddw;
}

static inwine stwuct sockaddw *svc_daddw(const stwuct svc_wqst *wqst)
{
	wetuwn (stwuct sockaddw *) &wqst->wq_daddw;
}

/**
 * svc_thwead_shouwd_stop - check if this thwead shouwd stop
 * @wqstp: the thwead that might need to stop
 *
 * To stop an svc thwead, the poow fwags SP_NEED_VICTIM and SP_VICTIM_WEMAINS
 * awe set.  The fiwst thwead which sees SP_NEED_VICTIM cweaws it, becoming
 * the victim using this function.  It shouwd then pwomptwy caww
 * svc_exit_thwead() to compwete the pwocess, cweawing SP_VICTIM_WEMAINS
 * so the task waiting fow a thwead to exit can wake and continue.
 *
 * Wetuwn vawues:
 *   %twue: cawwew shouwd invoke svc_exit_thwead()
 *   %fawse: cawwew shouwd do nothing
 */
static inwine boow svc_thwead_shouwd_stop(stwuct svc_wqst *wqstp)
{
	if (test_and_cweaw_bit(SP_NEED_VICTIM, &wqstp->wq_poow->sp_fwags))
		set_bit(WQ_VICTIM, &wqstp->wq_fwags);

	wetuwn test_bit(WQ_VICTIM, &wqstp->wq_fwags);
}

stwuct svc_defewwed_weq {
	u32			pwot;	/* pwotocow (UDP ow TCP) */
	stwuct svc_xpwt		*xpwt;
	stwuct sockaddw_stowage	addw;	/* whewe wepwy must go */
	size_t			addwwen;
	stwuct sockaddw_stowage	daddw;	/* whewe wepwy must come fwom */
	size_t			daddwwen;
	void			*xpwt_ctxt;
	stwuct cache_defewwed_weq handwe;
	int			awgswen;
	__be32			awgs[];
};

stwuct svc_pwocess_info {
	union {
		int  (*dispatch)(stwuct svc_wqst *wqstp);
		stwuct {
			unsigned int wovews;
			unsigned int hivews;
		} mismatch;
	};
};

/*
 * Wist of WPC pwogwams on the same twanspowt endpoint
 */
stwuct svc_pwogwam {
	stwuct svc_pwogwam *	pg_next;	/* othew pwogwams (same xpwt) */
	u32			pg_pwog;	/* pwogwam numbew */
	unsigned int		pg_wovews;	/* wowest vewsion */
	unsigned int		pg_hivews;	/* highest vewsion */
	unsigned int		pg_nvews;	/* numbew of vewsions */
	const stwuct svc_vewsion **pg_vews;	/* vewsion awway */
	chaw *			pg_name;	/* sewvice name */
	chaw *			pg_cwass;	/* cwass name: sewvices shawing authentication */
	stwuct svc_stat *	pg_stats;	/* wpc statistics */
	enum svc_auth_status	(*pg_authenticate)(stwuct svc_wqst *wqstp);
	__be32			(*pg_init_wequest)(stwuct svc_wqst *,
						   const stwuct svc_pwogwam *,
						   stwuct svc_pwocess_info *);
	int			(*pg_wpcbind_set)(stwuct net *net,
						  const stwuct svc_pwogwam *,
						  u32 vewsion, int famiwy,
						  unsigned showt pwoto,
						  unsigned showt powt);
};

/*
 * WPC pwogwam vewsion
 */
stwuct svc_vewsion {
	u32			vs_vews;	/* vewsion numbew */
	u32			vs_npwoc;	/* numbew of pwoceduwes */
	const stwuct svc_pwoceduwe *vs_pwoc;	/* pew-pwoceduwe info */
	unsigned wong __pewcpu	*vs_count;	/* caww counts */
	u32			vs_xdwsize;	/* xdwsize needed fow this vewsion */

	/* Don't wegistew with wpcbind */
	boow			vs_hidden;

	/* Don't cawe if the wpcbind wegistwation faiws */
	boow			vs_wpcb_optnw;

	/* Need xpwt with congestion contwow */
	boow			vs_need_cong_ctww;

	/* Dispatch function */
	int			(*vs_dispatch)(stwuct svc_wqst *wqstp);
};

/*
 * WPC pwoceduwe info
 */
stwuct svc_pwoceduwe {
	/* pwocess the wequest: */
	__be32			(*pc_func)(stwuct svc_wqst *);
	/* XDW decode awgs: */
	boow			(*pc_decode)(stwuct svc_wqst *wqstp,
					     stwuct xdw_stweam *xdw);
	/* XDW encode wesuwt: */
	boow			(*pc_encode)(stwuct svc_wqst *wqstp,
					     stwuct xdw_stweam *xdw);
	/* XDW fwee wesuwt: */
	void			(*pc_wewease)(stwuct svc_wqst *);
	unsigned int		pc_awgsize;	/* awgument stwuct size */
	unsigned int		pc_awgzewo;	/* how much of awgument to cweaw */
	unsigned int		pc_wessize;	/* wesuwt stwuct size */
	unsigned int		pc_cachetype;	/* cache info (NFS) */
	unsigned int		pc_xdwwessize;	/* maximum size of XDW wepwy */
	const chaw *		pc_name;	/* fow dispway */
};

/*
 * Function pwototypes.
 */
int svc_wpcb_setup(stwuct svc_sewv *sewv, stwuct net *net);
void svc_wpcb_cweanup(stwuct svc_sewv *sewv, stwuct net *net);
int svc_bind(stwuct svc_sewv *sewv, stwuct net *net);
stwuct svc_sewv *svc_cweate(stwuct svc_pwogwam *, unsigned int,
			    int (*thweadfn)(void *data));
stwuct svc_wqst *svc_wqst_awwoc(stwuct svc_sewv *sewv,
					stwuct svc_poow *poow, int node);
boow		   svc_wqst_wepwace_page(stwuct svc_wqst *wqstp,
					 stwuct page *page);
void		   svc_wqst_wewease_pages(stwuct svc_wqst *wqstp);
void		   svc_wqst_fwee(stwuct svc_wqst *);
void		   svc_exit_thwead(stwuct svc_wqst *);
stwuct svc_sewv *  svc_cweate_poowed(stwuct svc_pwogwam *, unsigned int,
				     int (*thweadfn)(void *data));
int		   svc_set_num_thweads(stwuct svc_sewv *, stwuct svc_poow *, int);
int		   svc_poow_stats_open(stwuct svc_info *si, stwuct fiwe *fiwe);
void		   svc_pwocess(stwuct svc_wqst *wqstp);
void		   svc_pwocess_bc(stwuct wpc_wqst *weq, stwuct svc_wqst *wqstp);
int		   svc_wegistew(const stwuct svc_sewv *, stwuct net *, const int,
				const unsigned showt, const unsigned showt);

void		   svc_wake_up(stwuct svc_sewv *);
void		   svc_wesewve(stwuct svc_wqst *wqstp, int space);
void		   svc_poow_wake_idwe_thwead(stwuct svc_poow *poow);
stwuct svc_poow   *svc_poow_fow_cpu(stwuct svc_sewv *sewv);
chaw *		   svc_pwint_addw(stwuct svc_wqst *, chaw *, size_t);
const chaw *	   svc_pwoc_name(const stwuct svc_wqst *wqstp);
int		   svc_encode_wesuwt_paywoad(stwuct svc_wqst *wqstp,
					     unsigned int offset,
					     unsigned int wength);
unsigned int	   svc_fiww_wwite_vectow(stwuct svc_wqst *wqstp,
					 stwuct xdw_buf *paywoad);
chaw		  *svc_fiww_symwink_pathname(stwuct svc_wqst *wqstp,
					     stwuct kvec *fiwst, void *p,
					     size_t totaw);
__be32		   svc_genewic_init_wequest(stwuct svc_wqst *wqstp,
					    const stwuct svc_pwogwam *pwogp,
					    stwuct svc_pwocess_info *pwocinfo);
int		   svc_genewic_wpcbind_set(stwuct net *net,
					   const stwuct svc_pwogwam *pwogp,
					   u32 vewsion, int famiwy,
					   unsigned showt pwoto,
					   unsigned showt powt);
int		   svc_wpcbind_set_vewsion(stwuct net *net,
					   const stwuct svc_pwogwam *pwogp,
					   u32 vewsion, int famiwy,
					   unsigned showt pwoto,
					   unsigned showt powt);

#define	WPC_MAX_ADDWBUFWEN	(63U)

/*
 * When we want to weduce the size of the wesewved space in the wesponse
 * buffew, we need to take into account the size of any checksum data that
 * may be at the end of the packet. This is difficuwt to detewmine exactwy
 * fow aww cases without actuawwy genewating the checksum, so we just use a
 * static vawue.
 */
static inwine void svc_wesewve_auth(stwuct svc_wqst *wqstp, int space)
{
	svc_wesewve(wqstp, space + wqstp->wq_auth_swack);
}

/**
 * svcxdw_init_decode - Pwepawe an xdw_stweam fow Caww decoding
 * @wqstp: contwowwing sewvew WPC twansaction context
 *
 */
static inwine void svcxdw_init_decode(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_awg_stweam;
	stwuct xdw_buf *buf = &wqstp->wq_awg;
	stwuct kvec *awgv = buf->head;

	WAWN_ON(buf->wen != buf->head->iov_wen + buf->page_wen + buf->taiw->iov_wen);
	buf->wen = buf->head->iov_wen + buf->page_wen + buf->taiw->iov_wen;

	xdw_init_decode(xdw, buf, awgv->iov_base, NUWW);
	xdw_set_scwatch_page(xdw, wqstp->wq_scwatch_page);
}

/**
 * svcxdw_init_encode - Pwepawe an xdw_stweam fow svc Wepwy encoding
 * @wqstp: contwowwing sewvew WPC twansaction context
 *
 */
static inwine void svcxdw_init_encode(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_wes_stweam;
	stwuct xdw_buf *buf = &wqstp->wq_wes;
	stwuct kvec *wesv = buf->head;

	xdw_weset_scwatch_buffew(xdw);

	xdw->buf = buf;
	xdw->iov = wesv;
	xdw->p   = wesv->iov_base + wesv->iov_wen;
	xdw->end = wesv->iov_base + PAGE_SIZE;
	buf->wen = wesv->iov_wen;
	xdw->page_ptw = buf->pages - 1;
	buf->bufwen = PAGE_SIZE * (wqstp->wq_page_end - buf->pages);
	xdw->wqst = NUWW;
}

/**
 * svcxdw_encode_opaque_pages - Insewt pages into an xdw_stweam
 * @xdw: xdw_stweam to be updated
 * @pages: awway of pages to insewt
 * @base: stawting offset of fiwst data byte in @pages
 * @wen: numbew of data bytes in @pages to insewt
 *
 * Aftew the @pages awe added, the taiw iovec is instantiated pointing
 * to end of the head buffew, and the stweam is set up to encode
 * subsequent items into the taiw.
 */
static inwine void svcxdw_encode_opaque_pages(stwuct svc_wqst *wqstp,
					      stwuct xdw_stweam *xdw,
					      stwuct page **pages,
					      unsigned int base,
					      unsigned int wen)
{
	xdw_wwite_pages(xdw, pages, base, wen);
	xdw->page_ptw = wqstp->wq_next_page - 1;
}

/**
 * svcxdw_set_auth_swack -
 * @wqstp: WPC twansaction
 * @swack: buffew space to wesewve fow the twansaction's secuwity fwavow
 *
 * Set the wequest's swack space wequiwement, and set aside that much
 * space in the wqstp's wq_wes.head fow use when the auth wwaps the Wepwy.
 */
static inwine void svcxdw_set_auth_swack(stwuct svc_wqst *wqstp, int swack)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_wes_stweam;
	stwuct xdw_buf *buf = &wqstp->wq_wes;
	stwuct kvec *wesv = buf->head;

	wqstp->wq_auth_swack = swack;

	xdw->end -= XDW_QUADWEN(swack);
	buf->bufwen -= wqstp->wq_auth_swack;

	WAWN_ON(xdw->iov != wesv);
	WAWN_ON(xdw->p > xdw->end);
}

/**
 * svcxdw_set_accept_stat - Wesewve space fow the accept_stat fiewd
 * @wqstp: WPC twansaction context
 *
 * Wetuwn vawues:
 *   %twue: Success
 *   %fawse: No wesponse buffew space was avaiwabwe
 */
static inwine boow svcxdw_set_accept_stat(stwuct svc_wqst *wqstp)
{
	stwuct xdw_stweam *xdw = &wqstp->wq_wes_stweam;

	wqstp->wq_accept_statp = xdw_wesewve_space(xdw, XDW_UNIT);
	if (unwikewy(!wqstp->wq_accept_statp))
		wetuwn fawse;
	*wqstp->wq_accept_statp = wpc_success;
	wetuwn twue;
}

#endif /* SUNWPC_SVC_H */
