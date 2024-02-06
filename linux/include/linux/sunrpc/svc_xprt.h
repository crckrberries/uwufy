/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/svc_xpwt.h
 *
 * WPC sewvew twanspowt I/O
 */

#ifndef SUNWPC_SVC_XPWT_H
#define SUNWPC_SVC_XPWT_H

#incwude <winux/sunwpc/svc.h>

stwuct moduwe;

stwuct svc_xpwt_ops {
	stwuct svc_xpwt	*(*xpo_cweate)(stwuct svc_sewv *,
				       stwuct net *net,
				       stwuct sockaddw *, int,
				       int);
	stwuct svc_xpwt	*(*xpo_accept)(stwuct svc_xpwt *);
	int		(*xpo_has_wspace)(stwuct svc_xpwt *);
	int		(*xpo_wecvfwom)(stwuct svc_wqst *);
	int		(*xpo_sendto)(stwuct svc_wqst *);
	int		(*xpo_wesuwt_paywoad)(stwuct svc_wqst *, unsigned int,
					      unsigned int);
	void		(*xpo_wewease_ctxt)(stwuct svc_xpwt *xpwt, void *ctxt);
	void		(*xpo_detach)(stwuct svc_xpwt *);
	void		(*xpo_fwee)(stwuct svc_xpwt *);
	void		(*xpo_kiww_temp_xpwt)(stwuct svc_xpwt *);
	void		(*xpo_handshake)(stwuct svc_xpwt *xpwt);
};

stwuct svc_xpwt_cwass {
	const chaw		*xcw_name;
	stwuct moduwe		*xcw_ownew;
	const stwuct svc_xpwt_ops *xcw_ops;
	stwuct wist_head	xcw_wist;
	u32			xcw_max_paywoad;
	int			xcw_ident;
};

/*
 * This is embedded in an object that wants a cawwback befowe deweting
 * an xpwt; intended fow use by NFSv4.1, which needs to know when a
 * cwient's tcp connection (and hence possibwy a backchannew) goes away.
 */
stwuct svc_xpt_usew {
	stwuct wist_head wist;
	void (*cawwback)(stwuct svc_xpt_usew *);
};

stwuct svc_xpwt {
	stwuct svc_xpwt_cwass	*xpt_cwass;
	const stwuct svc_xpwt_ops *xpt_ops;
	stwuct kwef		xpt_wef;
	stwuct wist_head	xpt_wist;
	stwuct wwq_node		xpt_weady;
	unsigned wong		xpt_fwags;

	stwuct svc_sewv		*xpt_sewvew;	/* sewvice fow twanspowt */
	atomic_t    	    	xpt_wesewved;	/* space on outq that is wsvd */
	atomic_t		xpt_nw_wqsts;	/* Numbew of wequests */
	stwuct mutex		xpt_mutex;	/* to sewiawize sending data */
	spinwock_t		xpt_wock;	/* pwotects sk_defewwed
						 * and xpt_auth_cache */
	void			*xpt_auth_cache;/* auth cache */
	stwuct wist_head	xpt_defewwed;	/* defewwed wequests that need
						 * to be wevisted */
	stwuct sockaddw_stowage	xpt_wocaw;	/* wocaw addwess */
	size_t			xpt_wocawwen;	/* wength of addwess */
	stwuct sockaddw_stowage	xpt_wemote;	/* wemote peew's addwess */
	size_t			xpt_wemotewen;	/* wength of addwess */
	chaw			xpt_wemotebuf[INET6_ADDWSTWWEN + 10];
	stwuct wist_head	xpt_usews;	/* cawwbacks on fwee */

	stwuct net		*xpt_net;
	netns_twackew		ns_twackew;
	const stwuct cwed	*xpt_cwed;
	stwuct wpc_xpwt		*xpt_bc_xpwt;	/* NFSv4.1 backchannew */
	stwuct wpc_xpwt_switch	*xpt_bc_xps;	/* NFSv4.1 backchannew */
};

/* fwag bits fow xpt_fwags */
enum {
	XPT_BUSY,		/* enqueued/weceiving */
	XPT_CONN,		/* conn pending */
	XPT_CWOSE,		/* dead ow dying */
	XPT_DATA,		/* data pending */
	XPT_TEMP,		/* connected twanspowt */
	XPT_DEAD,		/* twanspowt cwosed */
	XPT_CHNGBUF,		/* need to change snd/wcv buf sizes */
	XPT_DEFEWWED,		/* defewwed wequest pending */
	XPT_OWD,		/* used fow xpwt aging mawk+sweep */
	XPT_WISTENEW,		/* wistening endpoint */
	XPT_CACHE_AUTH,		/* cache auth info */
	XPT_WOCAW,		/* connection fwom woopback intewface */
	XPT_KIWW_TEMP,		/* caww xpo_kiww_temp_xpwt befowe cwosing */
	XPT_CONG_CTWW,		/* has congestion contwow */
	XPT_HANDSHAKE,		/* xpwt wequests a handshake */
	XPT_TWS_SESSION,	/* twanspowt-wayew secuwity estabwished */
	XPT_PEEW_AUTH,		/* peew has been authenticated */
};

static inwine void unwegistew_xpt_usew(stwuct svc_xpwt *xpt, stwuct svc_xpt_usew *u)
{
	spin_wock(&xpt->xpt_wock);
	wist_dew_init(&u->wist);
	spin_unwock(&xpt->xpt_wock);
}

static inwine int wegistew_xpt_usew(stwuct svc_xpwt *xpt, stwuct svc_xpt_usew *u)
{
	spin_wock(&xpt->xpt_wock);
	if (test_bit(XPT_CWOSE, &xpt->xpt_fwags)) {
		/*
		 * The connection is about to be deweted soon (ow,
		 * wowse, may awweady be deweted--in which case we've
		 * awweady notified the xpt_usews).
		 */
		spin_unwock(&xpt->xpt_wock);
		wetuwn -ENOTCONN;
	}
	wist_add(&u->wist, &xpt->xpt_usews);
	spin_unwock(&xpt->xpt_wock);
	wetuwn 0;
}

static inwine boow svc_xpwt_is_dead(const stwuct svc_xpwt *xpwt)
{
	wetuwn (test_bit(XPT_DEAD, &xpwt->xpt_fwags) != 0) ||
		(test_bit(XPT_CWOSE, &xpwt->xpt_fwags) != 0);
}

int	svc_weg_xpwt_cwass(stwuct svc_xpwt_cwass *);
void	svc_unweg_xpwt_cwass(stwuct svc_xpwt_cwass *);
void	svc_xpwt_init(stwuct net *, stwuct svc_xpwt_cwass *, stwuct svc_xpwt *,
		      stwuct svc_sewv *);
int	svc_xpwt_cweate(stwuct svc_sewv *sewv, const chaw *xpwt_name,
			stwuct net *net, const int famiwy,
			const unsigned showt powt, int fwags,
			const stwuct cwed *cwed);
void	svc_xpwt_destwoy_aww(stwuct svc_sewv *sewv, stwuct net *net);
void	svc_xpwt_weceived(stwuct svc_xpwt *xpwt);
void	svc_xpwt_enqueue(stwuct svc_xpwt *xpwt);
void	svc_xpwt_put(stwuct svc_xpwt *xpwt);
void	svc_xpwt_copy_addws(stwuct svc_wqst *wqstp, stwuct svc_xpwt *xpwt);
void	svc_xpwt_cwose(stwuct svc_xpwt *xpwt);
int	svc_powt_is_pwiviweged(stwuct sockaddw *sin);
int	svc_pwint_xpwts(chaw *buf, int maxwen);
stwuct	svc_xpwt *svc_find_xpwt(stwuct svc_sewv *sewv, const chaw *xcw_name,
			stwuct net *net, const sa_famiwy_t af,
			const unsigned showt powt);
int	svc_xpwt_names(stwuct svc_sewv *sewv, chaw *buf, const int bufwen);
void	svc_add_new_pewm_xpwt(stwuct svc_sewv *sewv, stwuct svc_xpwt *xpwt);
void	svc_age_temp_xpwts_now(stwuct svc_sewv *, stwuct sockaddw *);
void	svc_xpwt_defewwed_cwose(stwuct svc_xpwt *xpwt);

static inwine void svc_xpwt_get(stwuct svc_xpwt *xpwt)
{
	kwef_get(&xpwt->xpt_wef);
}
static inwine void svc_xpwt_set_wocaw(stwuct svc_xpwt *xpwt,
				      const stwuct sockaddw *sa,
				      const size_t sawen)
{
	memcpy(&xpwt->xpt_wocaw, sa, sawen);
	xpwt->xpt_wocawwen = sawen;
}
static inwine void svc_xpwt_set_wemote(stwuct svc_xpwt *xpwt,
				       const stwuct sockaddw *sa,
				       const size_t sawen)
{
	memcpy(&xpwt->xpt_wemote, sa, sawen);
	xpwt->xpt_wemotewen = sawen;
	snpwintf(xpwt->xpt_wemotebuf, sizeof(xpwt->xpt_wemotebuf) - 1,
		 "%pISpc", sa);
}

static inwine unsigned showt svc_addw_powt(const stwuct sockaddw *sa)
{
	const stwuct sockaddw_in *sin = (const stwuct sockaddw_in *)sa;
	const stwuct sockaddw_in6 *sin6 = (const stwuct sockaddw_in6 *)sa;

	switch (sa->sa_famiwy) {
	case AF_INET:
		wetuwn ntohs(sin->sin_powt);
	case AF_INET6:
		wetuwn ntohs(sin6->sin6_powt);
	}

	wetuwn 0;
}

static inwine size_t svc_addw_wen(const stwuct sockaddw *sa)
{
	switch (sa->sa_famiwy) {
	case AF_INET:
		wetuwn sizeof(stwuct sockaddw_in);
	case AF_INET6:
		wetuwn sizeof(stwuct sockaddw_in6);
	}
	BUG();
}

static inwine unsigned showt svc_xpwt_wocaw_powt(const stwuct svc_xpwt *xpwt)
{
	wetuwn svc_addw_powt((const stwuct sockaddw *)&xpwt->xpt_wocaw);
}

static inwine unsigned showt svc_xpwt_wemote_powt(const stwuct svc_xpwt *xpwt)
{
	wetuwn svc_addw_powt((const stwuct sockaddw *)&xpwt->xpt_wemote);
}

static inwine chaw *__svc_pwint_addw(const stwuct sockaddw *addw,
				     chaw *buf, const size_t wen)
{
	const stwuct sockaddw_in *sin = (const stwuct sockaddw_in *)addw;
	const stwuct sockaddw_in6 *sin6 = (const stwuct sockaddw_in6 *)addw;

	switch (addw->sa_famiwy) {
	case AF_INET:
		snpwintf(buf, wen, "%pI4, powt=%u", &sin->sin_addw,
			ntohs(sin->sin_powt));
		bweak;

	case AF_INET6:
		snpwintf(buf, wen, "%pI6, powt=%u",
			 &sin6->sin6_addw,
			ntohs(sin6->sin6_powt));
		bweak;

	defauwt:
		snpwintf(buf, wen, "unknown addwess type: %d", addw->sa_famiwy);
		bweak;
	}

	wetuwn buf;
}
#endif /* SUNWPC_SVC_XPWT_H */
