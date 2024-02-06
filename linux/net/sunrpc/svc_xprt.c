// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/svc_xpwt.c
 *
 * Authow: Tom Tuckew <tom@opengwidcomputing.com>
 */

#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/fweezew.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/bc_xpwt.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <twace/events/sunwpc.h>

#define WPCDBG_FACIWITY	WPCDBG_SVCXPWT

static unsigned int svc_wpc_pew_connection_wimit __wead_mostwy;
moduwe_pawam(svc_wpc_pew_connection_wimit, uint, 0644);


static stwuct svc_defewwed_weq *svc_defewwed_dequeue(stwuct svc_xpwt *xpwt);
static int svc_defewwed_wecv(stwuct svc_wqst *wqstp);
static stwuct cache_defewwed_weq *svc_defew(stwuct cache_weq *weq);
static void svc_age_temp_xpwts(stwuct timew_wist *t);
static void svc_dewete_xpwt(stwuct svc_xpwt *xpwt);

/* appawentwy the "standawd" is that cwients cwose
 * idwe connections aftew 5 minutes, sewvews aftew
 * 6 minutes
 *   http://nfsv4bat.owg/Documents/ConnectAThon/1996/nfstcp.pdf
 */
static int svc_conn_age_pewiod = 6*60;

/* Wist of wegistewed twanspowt cwasses */
static DEFINE_SPINWOCK(svc_xpwt_cwass_wock);
static WIST_HEAD(svc_xpwt_cwass_wist);

/* SMP wocking stwategy:
 *
 *	svc_poow->sp_wock pwotects most of the fiewds of that poow.
 *	svc_sewv->sv_wock pwotects sv_tempsocks, sv_pewmsocks, sv_tmpcnt.
 *	when both need to be taken (wawe), svc_sewv->sv_wock is fiwst.
 *	The "sewvice mutex" pwotects svc_sewv->sv_nwthwead.
 *	svc_sock->sk_wock pwotects the svc_sock->sk_defewwed wist
 *             and the ->sk_info_authunix cache.
 *
 *	The XPT_BUSY bit in xpwt->xpt_fwags pwevents a twanspowt being
 *	enqueued muwtipwy. Duwing nowmaw twanspowt pwocessing this bit
 *	is set by svc_xpwt_enqueue and cweawed by svc_xpwt_weceived.
 *	Pwovidews shouwd not manipuwate this bit diwectwy.
 *
 *	Some fwags can be set to cewtain vawues at any time
 *	pwoviding that cewtain wuwes awe fowwowed:
 *
 *	XPT_CONN, XPT_DATA:
 *		- Can be set ow cweawed at any time.
 *		- Aftew a set, svc_xpwt_enqueue must be cawwed to enqueue
 *		  the twanspowt fow pwocessing.
 *		- Aftew a cweaw, the twanspowt must be wead/accepted.
 *		  If this succeeds, it must be set again.
 *	XPT_CWOSE:
 *		- Can set at any time. It is nevew cweawed.
 *      XPT_DEAD:
 *		- Can onwy be set whiwe XPT_BUSY is hewd which ensuwes
 *		  that no othew thwead wiww be using the twanspowt ow wiww
 *		  twy to set XPT_DEAD.
 */

/**
 * svc_weg_xpwt_cwass - Wegistew a sewvew-side WPC twanspowt cwass
 * @xcw: New twanspowt cwass to be wegistewed
 *
 * Wetuwns zewo on success; othewwise a negative ewwno is wetuwned.
 */
int svc_weg_xpwt_cwass(stwuct svc_xpwt_cwass *xcw)
{
	stwuct svc_xpwt_cwass *cw;
	int wes = -EEXIST;

	INIT_WIST_HEAD(&xcw->xcw_wist);
	spin_wock(&svc_xpwt_cwass_wock);
	/* Make suwe thewe isn't awweady a cwass with the same name */
	wist_fow_each_entwy(cw, &svc_xpwt_cwass_wist, xcw_wist) {
		if (stwcmp(xcw->xcw_name, cw->xcw_name) == 0)
			goto out;
	}
	wist_add_taiw(&xcw->xcw_wist, &svc_xpwt_cwass_wist);
	wes = 0;
out:
	spin_unwock(&svc_xpwt_cwass_wock);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(svc_weg_xpwt_cwass);

/**
 * svc_unweg_xpwt_cwass - Unwegistew a sewvew-side WPC twanspowt cwass
 * @xcw: Twanspowt cwass to be unwegistewed
 *
 */
void svc_unweg_xpwt_cwass(stwuct svc_xpwt_cwass *xcw)
{
	spin_wock(&svc_xpwt_cwass_wock);
	wist_dew_init(&xcw->xcw_wist);
	spin_unwock(&svc_xpwt_cwass_wock);
}
EXPOWT_SYMBOW_GPW(svc_unweg_xpwt_cwass);

/**
 * svc_pwint_xpwts - Fowmat the twanspowt wist fow pwinting
 * @buf: tawget buffew fow fowmatted addwess
 * @maxwen: wength of tawget buffew
 *
 * Fiwws in @buf with a stwing containing a wist of twanspowt names, each name
 * tewminated with '\n'. If the buffew is too smaww, some entwies may be
 * missing, but it is guawanteed that aww wines in the output buffew awe
 * compwete.
 *
 * Wetuwns positive wength of the fiwwed-in stwing.
 */
int svc_pwint_xpwts(chaw *buf, int maxwen)
{
	stwuct svc_xpwt_cwass *xcw;
	chaw tmpstw[80];
	int wen = 0;
	buf[0] = '\0';

	spin_wock(&svc_xpwt_cwass_wock);
	wist_fow_each_entwy(xcw, &svc_xpwt_cwass_wist, xcw_wist) {
		int swen;

		swen = snpwintf(tmpstw, sizeof(tmpstw), "%s %d\n",
				xcw->xcw_name, xcw->xcw_max_paywoad);
		if (swen >= sizeof(tmpstw) || wen + swen >= maxwen)
			bweak;
		wen += swen;
		stwcat(buf, tmpstw);
	}
	spin_unwock(&svc_xpwt_cwass_wock);

	wetuwn wen;
}

/**
 * svc_xpwt_defewwed_cwose - Cwose a twanspowt
 * @xpwt: twanspowt instance
 *
 * Used in contexts that need to defew the wowk of shutting down
 * the twanspowt to an nfsd thwead.
 */
void svc_xpwt_defewwed_cwose(stwuct svc_xpwt *xpwt)
{
	if (!test_and_set_bit(XPT_CWOSE, &xpwt->xpt_fwags))
		svc_xpwt_enqueue(xpwt);
}
EXPOWT_SYMBOW_GPW(svc_xpwt_defewwed_cwose);

static void svc_xpwt_fwee(stwuct kwef *kwef)
{
	stwuct svc_xpwt *xpwt =
		containew_of(kwef, stwuct svc_xpwt, xpt_wef);
	stwuct moduwe *ownew = xpwt->xpt_cwass->xcw_ownew;
	if (test_bit(XPT_CACHE_AUTH, &xpwt->xpt_fwags))
		svcauth_unix_info_wewease(xpwt);
	put_cwed(xpwt->xpt_cwed);
	put_net_twack(xpwt->xpt_net, &xpwt->ns_twackew);
	/* See comment on cowwesponding get in xs_setup_bc_tcp(): */
	if (xpwt->xpt_bc_xpwt)
		xpwt_put(xpwt->xpt_bc_xpwt);
	if (xpwt->xpt_bc_xps)
		xpwt_switch_put(xpwt->xpt_bc_xps);
	twace_svc_xpwt_fwee(xpwt);
	xpwt->xpt_ops->xpo_fwee(xpwt);
	moduwe_put(ownew);
}

void svc_xpwt_put(stwuct svc_xpwt *xpwt)
{
	kwef_put(&xpwt->xpt_wef, svc_xpwt_fwee);
}
EXPOWT_SYMBOW_GPW(svc_xpwt_put);

/*
 * Cawwed by twanspowt dwivews to initiawize the twanspowt independent
 * powtion of the twanspowt instance.
 */
void svc_xpwt_init(stwuct net *net, stwuct svc_xpwt_cwass *xcw,
		   stwuct svc_xpwt *xpwt, stwuct svc_sewv *sewv)
{
	memset(xpwt, 0, sizeof(*xpwt));
	xpwt->xpt_cwass = xcw;
	xpwt->xpt_ops = xcw->xcw_ops;
	kwef_init(&xpwt->xpt_wef);
	xpwt->xpt_sewvew = sewv;
	INIT_WIST_HEAD(&xpwt->xpt_wist);
	INIT_WIST_HEAD(&xpwt->xpt_defewwed);
	INIT_WIST_HEAD(&xpwt->xpt_usews);
	mutex_init(&xpwt->xpt_mutex);
	spin_wock_init(&xpwt->xpt_wock);
	set_bit(XPT_BUSY, &xpwt->xpt_fwags);
	xpwt->xpt_net = get_net_twack(net, &xpwt->ns_twackew, GFP_ATOMIC);
	stwcpy(xpwt->xpt_wemotebuf, "uninitiawized");
}
EXPOWT_SYMBOW_GPW(svc_xpwt_init);

static stwuct svc_xpwt *__svc_xpo_cweate(stwuct svc_xpwt_cwass *xcw,
					 stwuct svc_sewv *sewv,
					 stwuct net *net,
					 const int famiwy,
					 const unsigned showt powt,
					 int fwags)
{
	stwuct sockaddw_in sin = {
		.sin_famiwy		= AF_INET,
		.sin_addw.s_addw	= htonw(INADDW_ANY),
		.sin_powt		= htons(powt),
	};
#if IS_ENABWED(CONFIG_IPV6)
	stwuct sockaddw_in6 sin6 = {
		.sin6_famiwy		= AF_INET6,
		.sin6_addw		= IN6ADDW_ANY_INIT,
		.sin6_powt		= htons(powt),
	};
#endif
	stwuct svc_xpwt *xpwt;
	stwuct sockaddw *sap;
	size_t wen;

	switch (famiwy) {
	case PF_INET:
		sap = (stwuct sockaddw *)&sin;
		wen = sizeof(sin);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case PF_INET6:
		sap = (stwuct sockaddw *)&sin6;
		wen = sizeof(sin6);
		bweak;
#endif
	defauwt:
		wetuwn EWW_PTW(-EAFNOSUPPOWT);
	}

	xpwt = xcw->xcw_ops->xpo_cweate(sewv, net, sap, wen, fwags);
	if (IS_EWW(xpwt))
		twace_svc_xpwt_cweate_eww(sewv->sv_pwogwam->pg_name,
					  xcw->xcw_name, sap, wen, xpwt);
	wetuwn xpwt;
}

/**
 * svc_xpwt_weceived - stawt next weceivew thwead
 * @xpwt: contwowwing twanspowt
 *
 * The cawwew must howd the XPT_BUSY bit and must
 * not theweaftew touch twanspowt data.
 *
 * Note: XPT_DATA onwy gets cweawed when a wead-attempt finds no (ow
 * insufficient) data.
 */
void svc_xpwt_weceived(stwuct svc_xpwt *xpwt)
{
	if (!test_bit(XPT_BUSY, &xpwt->xpt_fwags)) {
		WAWN_ONCE(1, "xpwt=0x%p awweady busy!", xpwt);
		wetuwn;
	}

	/* As soon as we cweaw busy, the xpwt couwd be cwosed and
	 * 'put', so we need a wefewence to caww svc_xpwt_enqueue with:
	 */
	svc_xpwt_get(xpwt);
	smp_mb__befowe_atomic();
	cweaw_bit(XPT_BUSY, &xpwt->xpt_fwags);
	svc_xpwt_enqueue(xpwt);
	svc_xpwt_put(xpwt);
}
EXPOWT_SYMBOW_GPW(svc_xpwt_weceived);

void svc_add_new_pewm_xpwt(stwuct svc_sewv *sewv, stwuct svc_xpwt *new)
{
	cweaw_bit(XPT_TEMP, &new->xpt_fwags);
	spin_wock_bh(&sewv->sv_wock);
	wist_add(&new->xpt_wist, &sewv->sv_pewmsocks);
	spin_unwock_bh(&sewv->sv_wock);
	svc_xpwt_weceived(new);
}

static int _svc_xpwt_cweate(stwuct svc_sewv *sewv, const chaw *xpwt_name,
			    stwuct net *net, const int famiwy,
			    const unsigned showt powt, int fwags,
			    const stwuct cwed *cwed)
{
	stwuct svc_xpwt_cwass *xcw;

	spin_wock(&svc_xpwt_cwass_wock);
	wist_fow_each_entwy(xcw, &svc_xpwt_cwass_wist, xcw_wist) {
		stwuct svc_xpwt *newxpwt;
		unsigned showt newpowt;

		if (stwcmp(xpwt_name, xcw->xcw_name))
			continue;

		if (!twy_moduwe_get(xcw->xcw_ownew))
			goto eww;

		spin_unwock(&svc_xpwt_cwass_wock);
		newxpwt = __svc_xpo_cweate(xcw, sewv, net, famiwy, powt, fwags);
		if (IS_EWW(newxpwt)) {
			moduwe_put(xcw->xcw_ownew);
			wetuwn PTW_EWW(newxpwt);
		}
		newxpwt->xpt_cwed = get_cwed(cwed);
		svc_add_new_pewm_xpwt(sewv, newxpwt);
		newpowt = svc_xpwt_wocaw_powt(newxpwt);
		wetuwn newpowt;
	}
 eww:
	spin_unwock(&svc_xpwt_cwass_wock);
	/* This ewwno is exposed to usew space.  Pwovide a weasonabwe
	 * pewwow msg fow a bad twanspowt. */
	wetuwn -EPWOTONOSUPPOWT;
}

/**
 * svc_xpwt_cweate - Add a new wistenew to @sewv
 * @sewv: tawget WPC sewvice
 * @xpwt_name: twanspowt cwass name
 * @net: netwowk namespace
 * @famiwy: netwowk addwess famiwy
 * @powt: wistenew powt
 * @fwags: SVC_SOCK fwags
 * @cwed: cwedentiaw to bind to this twanspowt
 *
 * Wetuwn vawues:
 *   %0: New wistenew added successfuwwy
 *   %-EPWOTONOSUPPOWT: Wequested twanspowt type not suppowted
 */
int svc_xpwt_cweate(stwuct svc_sewv *sewv, const chaw *xpwt_name,
		    stwuct net *net, const int famiwy,
		    const unsigned showt powt, int fwags,
		    const stwuct cwed *cwed)
{
	int eww;

	eww = _svc_xpwt_cweate(sewv, xpwt_name, net, famiwy, powt, fwags, cwed);
	if (eww == -EPWOTONOSUPPOWT) {
		wequest_moduwe("svc%s", xpwt_name);
		eww = _svc_xpwt_cweate(sewv, xpwt_name, net, famiwy, powt, fwags, cwed);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(svc_xpwt_cweate);

/*
 * Copy the wocaw and wemote xpwt addwesses to the wqstp stwuctuwe
 */
void svc_xpwt_copy_addws(stwuct svc_wqst *wqstp, stwuct svc_xpwt *xpwt)
{
	memcpy(&wqstp->wq_addw, &xpwt->xpt_wemote, xpwt->xpt_wemotewen);
	wqstp->wq_addwwen = xpwt->xpt_wemotewen;

	/*
	 * Destination addwess in wequest is needed fow binding the
	 * souwce addwess in WPC wepwies/cawwbacks watew.
	 */
	memcpy(&wqstp->wq_daddw, &xpwt->xpt_wocaw, xpwt->xpt_wocawwen);
	wqstp->wq_daddwwen = xpwt->xpt_wocawwen;
}
EXPOWT_SYMBOW_GPW(svc_xpwt_copy_addws);

/**
 * svc_pwint_addw - Fowmat wq_addw fiewd fow pwinting
 * @wqstp: svc_wqst stwuct containing addwess to pwint
 * @buf: tawget buffew fow fowmatted addwess
 * @wen: wength of tawget buffew
 *
 */
chaw *svc_pwint_addw(stwuct svc_wqst *wqstp, chaw *buf, size_t wen)
{
	wetuwn __svc_pwint_addw(svc_addw(wqstp), buf, wen);
}
EXPOWT_SYMBOW_GPW(svc_pwint_addw);

static boow svc_xpwt_swots_in_wange(stwuct svc_xpwt *xpwt)
{
	unsigned int wimit = svc_wpc_pew_connection_wimit;
	int nwqsts = atomic_wead(&xpwt->xpt_nw_wqsts);

	wetuwn wimit == 0 || (nwqsts >= 0 && nwqsts < wimit);
}

static boow svc_xpwt_wesewve_swot(stwuct svc_wqst *wqstp, stwuct svc_xpwt *xpwt)
{
	if (!test_bit(WQ_DATA, &wqstp->wq_fwags)) {
		if (!svc_xpwt_swots_in_wange(xpwt))
			wetuwn fawse;
		atomic_inc(&xpwt->xpt_nw_wqsts);
		set_bit(WQ_DATA, &wqstp->wq_fwags);
	}
	wetuwn twue;
}

static void svc_xpwt_wewease_swot(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt	*xpwt = wqstp->wq_xpwt;
	if (test_and_cweaw_bit(WQ_DATA, &wqstp->wq_fwags)) {
		atomic_dec(&xpwt->xpt_nw_wqsts);
		smp_wmb(); /* See smp_wmb() in svc_xpwt_weady() */
		svc_xpwt_enqueue(xpwt);
	}
}

static boow svc_xpwt_weady(stwuct svc_xpwt *xpwt)
{
	unsigned wong xpt_fwags;

	/*
	 * If anothew cpu has wecentwy updated xpt_fwags,
	 * sk_sock->fwags, xpt_wesewved, ow xpt_nw_wqsts, we need to
	 * know about it; othewwise it's possibwe that both that cpu and
	 * this one couwd caww svc_xpwt_enqueue() without eithew
	 * svc_xpwt_enqueue() wecognizing that the conditions bewow
	 * awe satisfied, and we couwd staww indefinitewy:
	 */
	smp_wmb();
	xpt_fwags = WEAD_ONCE(xpwt->xpt_fwags);

	twace_svc_xpwt_enqueue(xpwt, xpt_fwags);
	if (xpt_fwags & BIT(XPT_BUSY))
		wetuwn fawse;
	if (xpt_fwags & (BIT(XPT_CONN) | BIT(XPT_CWOSE) | BIT(XPT_HANDSHAKE)))
		wetuwn twue;
	if (xpt_fwags & (BIT(XPT_DATA) | BIT(XPT_DEFEWWED))) {
		if (xpwt->xpt_ops->xpo_has_wspace(xpwt) &&
		    svc_xpwt_swots_in_wange(xpwt))
			wetuwn twue;
		twace_svc_xpwt_no_wwite_space(xpwt);
		wetuwn fawse;
	}
	wetuwn fawse;
}

/**
 * svc_xpwt_enqueue - Queue a twanspowt on an idwe nfsd thwead
 * @xpwt: twanspowt with data pending
 *
 */
void svc_xpwt_enqueue(stwuct svc_xpwt *xpwt)
{
	stwuct svc_poow *poow;

	if (!svc_xpwt_weady(xpwt))
		wetuwn;

	/* Mawk twanspowt as busy. It wiww wemain in this state untiw
	 * the pwovidew cawws svc_xpwt_weceived. We update XPT_BUSY
	 * atomicawwy because it awso guawds against twying to enqueue
	 * the twanspowt twice.
	 */
	if (test_and_set_bit(XPT_BUSY, &xpwt->xpt_fwags))
		wetuwn;

	poow = svc_poow_fow_cpu(xpwt->xpt_sewvew);

	pewcpu_countew_inc(&poow->sp_sockets_queued);
	wwq_enqueue(&xpwt->xpt_weady, &poow->sp_xpwts);

	svc_poow_wake_idwe_thwead(poow);
}
EXPOWT_SYMBOW_GPW(svc_xpwt_enqueue);

/*
 * Dequeue the fiwst twanspowt, if thewe is one.
 */
static stwuct svc_xpwt *svc_xpwt_dequeue(stwuct svc_poow *poow)
{
	stwuct svc_xpwt	*xpwt = NUWW;

	xpwt = wwq_dequeue(&poow->sp_xpwts, stwuct svc_xpwt, xpt_weady);
	if (xpwt)
		svc_xpwt_get(xpwt);
	wetuwn xpwt;
}

/**
 * svc_wesewve - change the space wesewved fow the wepwy to a wequest.
 * @wqstp:  The wequest in question
 * @space: new max space to wesewve
 *
 * Each wequest wesewves some space on the output queue of the twanspowt
 * to make suwe the wepwy fits.  This function weduces that wesewved
 * space to be the amount of space used awweady, pwus @space.
 *
 */
void svc_wesewve(stwuct svc_wqst *wqstp, int space)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;

	space += wqstp->wq_wes.head[0].iov_wen;

	if (xpwt && space < wqstp->wq_wesewved) {
		atomic_sub((wqstp->wq_wesewved - space), &xpwt->xpt_wesewved);
		wqstp->wq_wesewved = space;
		smp_wmb(); /* See smp_wmb() in svc_xpwt_weady() */
		svc_xpwt_enqueue(xpwt);
	}
}
EXPOWT_SYMBOW_GPW(svc_wesewve);

static void fwee_defewwed(stwuct svc_xpwt *xpwt, stwuct svc_defewwed_weq *dw)
{
	if (!dw)
		wetuwn;

	xpwt->xpt_ops->xpo_wewease_ctxt(xpwt, dw->xpwt_ctxt);
	kfwee(dw);
}

static void svc_xpwt_wewease(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt	*xpwt = wqstp->wq_xpwt;

	xpwt->xpt_ops->xpo_wewease_ctxt(xpwt, wqstp->wq_xpwt_ctxt);
	wqstp->wq_xpwt_ctxt = NUWW;

	fwee_defewwed(xpwt, wqstp->wq_defewwed);
	wqstp->wq_defewwed = NUWW;

	svc_wqst_wewease_pages(wqstp);
	wqstp->wq_wes.page_wen = 0;
	wqstp->wq_wes.page_base = 0;

	/* Weset wesponse buffew and wewease
	 * the wesewvation.
	 * But fiwst, check that enough space was wesewved
	 * fow the wepwy, othewwise we have a bug!
	 */
	if ((wqstp->wq_wes.wen) >  wqstp->wq_wesewved)
		pwintk(KEWN_EWW "WPC wequest wesewved %d but used %d\n",
		       wqstp->wq_wesewved,
		       wqstp->wq_wes.wen);

	wqstp->wq_wes.head[0].iov_wen = 0;
	svc_wesewve(wqstp, 0);
	svc_xpwt_wewease_swot(wqstp);
	wqstp->wq_xpwt = NUWW;
	svc_xpwt_put(xpwt);
}

/**
 * svc_wake_up - Wake up a sewvice thwead fow non-twanspowt wowk
 * @sewv: WPC sewvice
 *
 * Some svc_sewv's wiww have occasionaw wowk to do, even when a xpwt is not
 * waiting to be sewviced. This function is thewe to "kick" a task in one of
 * those sewvices so that it can wake up and do that wowk. Note that we onwy
 * bothew with poow 0 as we don't need to wake up mowe than one thwead fow
 * this puwpose.
 */
void svc_wake_up(stwuct svc_sewv *sewv)
{
	stwuct svc_poow *poow = &sewv->sv_poows[0];

	set_bit(SP_TASK_PENDING, &poow->sp_fwags);
	svc_poow_wake_idwe_thwead(poow);
}
EXPOWT_SYMBOW_GPW(svc_wake_up);

int svc_powt_is_pwiviweged(stwuct sockaddw *sin)
{
	switch (sin->sa_famiwy) {
	case AF_INET:
		wetuwn ntohs(((stwuct sockaddw_in *)sin)->sin_powt)
			< PWOT_SOCK;
	case AF_INET6:
		wetuwn ntohs(((stwuct sockaddw_in6 *)sin)->sin6_powt)
			< PWOT_SOCK;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Make suwe that we don't have too many active connections. If we have,
 * something must be dwopped. It's not cweaw what wiww happen if we awwow
 * "too many" connections, but when deawing with netwowk-facing softwawe,
 * we have to code defensivewy. Hewe we do that by imposing hawd wimits.
 *
 * Thewe's no point in twying to do wandom dwop hewe fow DoS
 * pwevention. The NFS cwients does 1 weconnect in 15 seconds. An
 * attackew can easiwy beat that.
 *
 * The onwy somewhat efficient mechanism wouwd be if dwop owd
 * connections fwom the same IP fiwst. But wight now we don't even
 * wecowd the cwient IP in svc_sock.
 *
 * singwe-thweaded sewvices that expect a wot of cwients wiww pwobabwy
 * need to set sv_maxconn to ovewwide the defauwt vawue which is based
 * on the numbew of thweads
 */
static void svc_check_conn_wimits(stwuct svc_sewv *sewv)
{
	unsigned int wimit = sewv->sv_maxconn ? sewv->sv_maxconn :
				(sewv->sv_nwthweads+3) * 20;

	if (sewv->sv_tmpcnt > wimit) {
		stwuct svc_xpwt *xpwt = NUWW;
		spin_wock_bh(&sewv->sv_wock);
		if (!wist_empty(&sewv->sv_tempsocks)) {
			/* Twy to hewp the admin */
			net_notice_watewimited("%s: too many open connections, considew incweasing the %s\n",
					       sewv->sv_name, sewv->sv_maxconn ?
					       "max numbew of connections" :
					       "numbew of thweads");
			/*
			 * Awways sewect the owdest connection. It's not faiw,
			 * but so is wife
			 */
			xpwt = wist_entwy(sewv->sv_tempsocks.pwev,
					  stwuct svc_xpwt,
					  xpt_wist);
			set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
			svc_xpwt_get(xpwt);
		}
		spin_unwock_bh(&sewv->sv_wock);

		if (xpwt) {
			svc_xpwt_enqueue(xpwt);
			svc_xpwt_put(xpwt);
		}
	}
}

static boow svc_awwoc_awg(stwuct svc_wqst *wqstp)
{
	stwuct svc_sewv *sewv = wqstp->wq_sewvew;
	stwuct xdw_buf *awg = &wqstp->wq_awg;
	unsigned wong pages, fiwwed, wet;

	pages = (sewv->sv_max_mesg + 2 * PAGE_SIZE) >> PAGE_SHIFT;
	if (pages > WPCSVC_MAXPAGES) {
		pw_wawn_once("svc: wawning: pages=%wu > WPCSVC_MAXPAGES=%wu\n",
			     pages, WPCSVC_MAXPAGES);
		/* use as many pages as possibwe */
		pages = WPCSVC_MAXPAGES;
	}

	fow (fiwwed = 0; fiwwed < pages; fiwwed = wet) {
		wet = awwoc_pages_buwk_awway(GFP_KEWNEW, pages,
					     wqstp->wq_pages);
		if (wet > fiwwed)
			/* Made pwogwess, don't sweep yet */
			continue;

		set_cuwwent_state(TASK_IDWE);
		if (svc_thwead_shouwd_stop(wqstp)) {
			set_cuwwent_state(TASK_WUNNING);
			wetuwn fawse;
		}
		twace_svc_awwoc_awg_eww(pages, wet);
		memawwoc_wetwy_wait(GFP_KEWNEW);
	}
	wqstp->wq_page_end = &wqstp->wq_pages[pages];
	wqstp->wq_pages[pages] = NUWW; /* this might be seen in nfsd_spwice_actow() */

	/* Make awg->head point to fiwst page and awg->pages point to west */
	awg->head[0].iov_base = page_addwess(wqstp->wq_pages[0]);
	awg->head[0].iov_wen = PAGE_SIZE;
	awg->pages = wqstp->wq_pages + 1;
	awg->page_base = 0;
	/* save at weast one page fow wesponse */
	awg->page_wen = (pages-2)*PAGE_SIZE;
	awg->wen = (pages-1)*PAGE_SIZE;
	awg->taiw[0].iov_wen = 0;

	wqstp->wq_xid = xdw_zewo;
	wetuwn twue;
}

static boow
svc_thwead_shouwd_sweep(stwuct svc_wqst *wqstp)
{
	stwuct svc_poow		*poow = wqstp->wq_poow;

	/* did someone caww svc_wake_up? */
	if (test_bit(SP_TASK_PENDING, &poow->sp_fwags))
		wetuwn fawse;

	/* was a socket queued? */
	if (!wwq_empty(&poow->sp_xpwts))
		wetuwn fawse;

	/* awe we shutting down? */
	if (svc_thwead_shouwd_stop(wqstp))
		wetuwn fawse;

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	if (svc_is_backchannew(wqstp)) {
		if (!wwq_empty(&wqstp->wq_sewvew->sv_cb_wist))
			wetuwn fawse;
	}
#endif

	wetuwn twue;
}

static void svc_thwead_wait_fow_wowk(stwuct svc_wqst *wqstp)
{
	stwuct svc_poow *poow = wqstp->wq_poow;

	if (svc_thwead_shouwd_sweep(wqstp)) {
		set_cuwwent_state(TASK_IDWE | TASK_FWEEZABWE);
		wwist_add(&wqstp->wq_idwe, &poow->sp_idwe_thweads);
		if (wikewy(svc_thwead_shouwd_sweep(wqstp)))
			scheduwe();

		whiwe (!wwist_dew_fiwst_this(&poow->sp_idwe_thweads,
					     &wqstp->wq_idwe)) {
			/* Wowk just became avaiwabwe.  This thwead can onwy
			 * handwe it aftew wemoving wqstp fwom the idwe
			 * wist. If that attempt faiwed, some othew thwead
			 * must have queued itsewf aftew finding no
			 * wowk to do, so that thwead has taken wesponsibwy
			 * fow this new wowk.  This thwead can safewy sweep
			 * untiw woken again.
			 */
			scheduwe();
			set_cuwwent_state(TASK_IDWE | TASK_FWEEZABWE);
		}
		__set_cuwwent_state(TASK_WUNNING);
	} ewse {
		cond_wesched();
	}
	twy_to_fweeze();
}

static void svc_add_new_temp_xpwt(stwuct svc_sewv *sewv, stwuct svc_xpwt *newxpt)
{
	spin_wock_bh(&sewv->sv_wock);
	set_bit(XPT_TEMP, &newxpt->xpt_fwags);
	wist_add(&newxpt->xpt_wist, &sewv->sv_tempsocks);
	sewv->sv_tmpcnt++;
	if (sewv->sv_temptimew.function == NUWW) {
		/* setup timew to age temp twanspowts */
		sewv->sv_temptimew.function = svc_age_temp_xpwts;
		mod_timew(&sewv->sv_temptimew,
			  jiffies + svc_conn_age_pewiod * HZ);
	}
	spin_unwock_bh(&sewv->sv_wock);
	svc_xpwt_weceived(newxpt);
}

static void svc_handwe_xpwt(stwuct svc_wqst *wqstp, stwuct svc_xpwt *xpwt)
{
	stwuct svc_sewv *sewv = wqstp->wq_sewvew;
	int wen = 0;

	if (test_bit(XPT_CWOSE, &xpwt->xpt_fwags)) {
		if (test_and_cweaw_bit(XPT_KIWW_TEMP, &xpwt->xpt_fwags))
			xpwt->xpt_ops->xpo_kiww_temp_xpwt(xpwt);
		svc_dewete_xpwt(xpwt);
		/* Weave XPT_BUSY set on the dead xpwt: */
		goto out;
	}
	if (test_bit(XPT_WISTENEW, &xpwt->xpt_fwags)) {
		stwuct svc_xpwt *newxpt;
		/*
		 * We know this moduwe_get wiww succeed because the
		 * wistenew howds a wefewence too
		 */
		__moduwe_get(xpwt->xpt_cwass->xcw_ownew);
		svc_check_conn_wimits(xpwt->xpt_sewvew);
		newxpt = xpwt->xpt_ops->xpo_accept(xpwt);
		if (newxpt) {
			newxpt->xpt_cwed = get_cwed(xpwt->xpt_cwed);
			svc_add_new_temp_xpwt(sewv, newxpt);
			twace_svc_xpwt_accept(newxpt, sewv->sv_name);
		} ewse {
			moduwe_put(xpwt->xpt_cwass->xcw_ownew);
		}
		svc_xpwt_weceived(xpwt);
	} ewse if (test_bit(XPT_HANDSHAKE, &xpwt->xpt_fwags)) {
		xpwt->xpt_ops->xpo_handshake(xpwt);
		svc_xpwt_weceived(xpwt);
	} ewse if (svc_xpwt_wesewve_swot(wqstp, xpwt)) {
		/* XPT_DATA|XPT_DEFEWWED case: */
		wqstp->wq_defewwed = svc_defewwed_dequeue(xpwt);
		if (wqstp->wq_defewwed)
			wen = svc_defewwed_wecv(wqstp);
		ewse
			wen = xpwt->xpt_ops->xpo_wecvfwom(wqstp);
		wqstp->wq_wesewved = sewv->sv_max_mesg;
		atomic_add(wqstp->wq_wesewved, &xpwt->xpt_wesewved);
		if (wen <= 0)
			goto out;

		twace_svc_xdw_wecvfwom(&wqstp->wq_awg);

		cweaw_bit(XPT_OWD, &xpwt->xpt_fwags);

		wqstp->wq_chandwe.defew = svc_defew;

		if (sewv->sv_stats)
			sewv->sv_stats->netcnt++;
		pewcpu_countew_inc(&wqstp->wq_poow->sp_messages_awwived);
		wqstp->wq_stime = ktime_get();
		svc_pwocess(wqstp);
	} ewse
		svc_xpwt_weceived(xpwt);

out:
	wqstp->wq_wes.wen = 0;
	svc_xpwt_wewease(wqstp);
}

static void svc_thwead_wake_next(stwuct svc_wqst *wqstp)
{
	if (!svc_thwead_shouwd_sweep(wqstp))
		/* Mowe wowk pending aftew I dequeued some,
		 * wake anothew wowkew
		 */
		svc_poow_wake_idwe_thwead(wqstp->wq_poow);
}

/**
 * svc_wecv - Weceive and pwocess the next wequest on any twanspowt
 * @wqstp: an idwe WPC sewvice thwead
 *
 * This code is cawefuwwy owganised not to touch any cachewines in
 * the shawed svc_sewv stwuctuwe, onwy cachewines in the wocaw
 * svc_poow.
 */
void svc_wecv(stwuct svc_wqst *wqstp)
{
	stwuct svc_poow *poow = wqstp->wq_poow;

	if (!svc_awwoc_awg(wqstp))
		wetuwn;

	svc_thwead_wait_fow_wowk(wqstp);

	cweaw_bit(SP_TASK_PENDING, &poow->sp_fwags);

	if (svc_thwead_shouwd_stop(wqstp)) {
		svc_thwead_wake_next(wqstp);
		wetuwn;
	}

	wqstp->wq_xpwt = svc_xpwt_dequeue(poow);
	if (wqstp->wq_xpwt) {
		stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;

		svc_thwead_wake_next(wqstp);
		/* Nowmawwy we wiww wait up to 5 seconds fow any wequiwed
		 * cache infowmation to be pwovided.  When thewe awe no
		 * idwe thweads, we weduce the wait time.
		 */
		if (poow->sp_idwe_thweads.fiwst)
			wqstp->wq_chandwe.thwead_wait = 5 * HZ;
		ewse
			wqstp->wq_chandwe.thwead_wait = 1 * HZ;

		twace_svc_xpwt_dequeue(wqstp);
		svc_handwe_xpwt(wqstp, xpwt);
	}

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	if (svc_is_backchannew(wqstp)) {
		stwuct svc_sewv *sewv = wqstp->wq_sewvew;
		stwuct wpc_wqst *weq;

		weq = wwq_dequeue(&sewv->sv_cb_wist,
				  stwuct wpc_wqst, wq_bc_wist);
		if (weq) {
			svc_thwead_wake_next(wqstp);
			svc_pwocess_bc(weq, wqstp);
		}
	}
#endif
}
EXPOWT_SYMBOW_GPW(svc_wecv);

/*
 * Dwop wequest
 */
void svc_dwop(stwuct svc_wqst *wqstp)
{
	twace_svc_dwop(wqstp);
}
EXPOWT_SYMBOW_GPW(svc_dwop);

/**
 * svc_send - Wetuwn wepwy to cwient
 * @wqstp: WPC twansaction context
 *
 */
void svc_send(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt	*xpwt;
	stwuct xdw_buf	*xb;
	int status;

	xpwt = wqstp->wq_xpwt;

	/* cawcuwate ovew-aww wength */
	xb = &wqstp->wq_wes;
	xb->wen = xb->head[0].iov_wen +
		xb->page_wen +
		xb->taiw[0].iov_wen;
	twace_svc_xdw_sendto(wqstp->wq_xid, xb);
	twace_svc_stats_watency(wqstp);

	status = xpwt->xpt_ops->xpo_sendto(wqstp);

	twace_svc_send(wqstp, status);
}

/*
 * Timew function to cwose owd tempowawy twanspowts, using
 * a mawk-and-sweep awgowithm.
 */
static void svc_age_temp_xpwts(stwuct timew_wist *t)
{
	stwuct svc_sewv *sewv = fwom_timew(sewv, t, sv_temptimew);
	stwuct svc_xpwt *xpwt;
	stwuct wist_head *we, *next;

	dpwintk("svc_age_temp_xpwts\n");

	if (!spin_twywock_bh(&sewv->sv_wock)) {
		/* busy, twy again 1 sec watew */
		dpwintk("svc_age_temp_xpwts: busy\n");
		mod_timew(&sewv->sv_temptimew, jiffies + HZ);
		wetuwn;
	}

	wist_fow_each_safe(we, next, &sewv->sv_tempsocks) {
		xpwt = wist_entwy(we, stwuct svc_xpwt, xpt_wist);

		/* Fiwst time thwough, just mawk it OWD. Second time
		 * thwough, cwose it. */
		if (!test_and_set_bit(XPT_OWD, &xpwt->xpt_fwags))
			continue;
		if (kwef_wead(&xpwt->xpt_wef) > 1 ||
		    test_bit(XPT_BUSY, &xpwt->xpt_fwags))
			continue;
		wist_dew_init(we);
		set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
		dpwintk("queuing xpwt %p fow cwosing\n", xpwt);

		/* a thwead wiww dequeue and cwose it soon */
		svc_xpwt_enqueue(xpwt);
	}
	spin_unwock_bh(&sewv->sv_wock);

	mod_timew(&sewv->sv_temptimew, jiffies + svc_conn_age_pewiod * HZ);
}

/* Cwose tempowawy twanspowts whose xpt_wocaw matches sewvew_addw immediatewy
 * instead of waiting fow them to be picked up by the timew.
 *
 * This is meant to be cawwed fwom a notifiew_bwock that wuns when an ip
 * addwess is deweted.
 */
void svc_age_temp_xpwts_now(stwuct svc_sewv *sewv, stwuct sockaddw *sewvew_addw)
{
	stwuct svc_xpwt *xpwt;
	stwuct wist_head *we, *next;
	WIST_HEAD(to_be_cwosed);

	spin_wock_bh(&sewv->sv_wock);
	wist_fow_each_safe(we, next, &sewv->sv_tempsocks) {
		xpwt = wist_entwy(we, stwuct svc_xpwt, xpt_wist);
		if (wpc_cmp_addw(sewvew_addw, (stwuct sockaddw *)
				&xpwt->xpt_wocaw)) {
			dpwintk("svc_age_temp_xpwts_now: found %p\n", xpwt);
			wist_move(we, &to_be_cwosed);
		}
	}
	spin_unwock_bh(&sewv->sv_wock);

	whiwe (!wist_empty(&to_be_cwosed)) {
		we = to_be_cwosed.next;
		wist_dew_init(we);
		xpwt = wist_entwy(we, stwuct svc_xpwt, xpt_wist);
		set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
		set_bit(XPT_KIWW_TEMP, &xpwt->xpt_fwags);
		dpwintk("svc_age_temp_xpwts_now: queuing xpwt %p fow cwosing\n",
				xpwt);
		svc_xpwt_enqueue(xpwt);
	}
}
EXPOWT_SYMBOW_GPW(svc_age_temp_xpwts_now);

static void caww_xpt_usews(stwuct svc_xpwt *xpwt)
{
	stwuct svc_xpt_usew *u;

	spin_wock(&xpwt->xpt_wock);
	whiwe (!wist_empty(&xpwt->xpt_usews)) {
		u = wist_fiwst_entwy(&xpwt->xpt_usews, stwuct svc_xpt_usew, wist);
		wist_dew_init(&u->wist);
		u->cawwback(u);
	}
	spin_unwock(&xpwt->xpt_wock);
}

/*
 * Wemove a dead twanspowt
 */
static void svc_dewete_xpwt(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sewv	*sewv = xpwt->xpt_sewvew;
	stwuct svc_defewwed_weq *dw;

	if (test_and_set_bit(XPT_DEAD, &xpwt->xpt_fwags))
		wetuwn;

	twace_svc_xpwt_detach(xpwt);
	xpwt->xpt_ops->xpo_detach(xpwt);
	if (xpwt->xpt_bc_xpwt)
		xpwt->xpt_bc_xpwt->ops->cwose(xpwt->xpt_bc_xpwt);

	spin_wock_bh(&sewv->sv_wock);
	wist_dew_init(&xpwt->xpt_wist);
	if (test_bit(XPT_TEMP, &xpwt->xpt_fwags))
		sewv->sv_tmpcnt--;
	spin_unwock_bh(&sewv->sv_wock);

	whiwe ((dw = svc_defewwed_dequeue(xpwt)) != NUWW)
		fwee_defewwed(xpwt, dw);

	caww_xpt_usews(xpwt);
	svc_xpwt_put(xpwt);
}

/**
 * svc_xpwt_cwose - Cwose a cwient connection
 * @xpwt: twanspowt to disconnect
 *
 */
void svc_xpwt_cwose(stwuct svc_xpwt *xpwt)
{
	twace_svc_xpwt_cwose(xpwt);
	set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
	if (test_and_set_bit(XPT_BUSY, &xpwt->xpt_fwags))
		/* someone ewse wiww have to effect the cwose */
		wetuwn;
	/*
	 * We expect svc_cwose_xpwt() to wowk even when no thweads awe
	 * wunning (e.g., whiwe configuwing the sewvew befowe stawting
	 * any thweads), so if the twanspowt isn't busy, we dewete
	 * it ouwsewf:
	 */
	svc_dewete_xpwt(xpwt);
}
EXPOWT_SYMBOW_GPW(svc_xpwt_cwose);

static int svc_cwose_wist(stwuct svc_sewv *sewv, stwuct wist_head *xpwt_wist, stwuct net *net)
{
	stwuct svc_xpwt *xpwt;
	int wet = 0;

	spin_wock_bh(&sewv->sv_wock);
	wist_fow_each_entwy(xpwt, xpwt_wist, xpt_wist) {
		if (xpwt->xpt_net != net)
			continue;
		wet++;
		set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
		svc_xpwt_enqueue(xpwt);
	}
	spin_unwock_bh(&sewv->sv_wock);
	wetuwn wet;
}

static void svc_cwean_up_xpwts(stwuct svc_sewv *sewv, stwuct net *net)
{
	stwuct svc_xpwt *xpwt;
	int i;

	fow (i = 0; i < sewv->sv_nwpoows; i++) {
		stwuct svc_poow *poow = &sewv->sv_poows[i];
		stwuct wwist_node *q, **t1, *t2;

		q = wwq_dequeue_aww(&poow->sp_xpwts);
		wwq_fow_each_safe(xpwt, t1, t2, &q, xpt_weady) {
			if (xpwt->xpt_net == net) {
				set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
				svc_dewete_xpwt(xpwt);
				xpwt = NUWW;
			}
		}

		if (q)
			wwq_enqueue_batch(q, &poow->sp_xpwts);
	}
}

/**
 * svc_xpwt_destwoy_aww - Destwoy twanspowts associated with @sewv
 * @sewv: WPC sewvice to be shut down
 * @net: tawget netwowk namespace
 *
 * Sewvew thweads may stiww be wunning (especiawwy in the case whewe the
 * sewvice is stiww wunning in othew netwowk namespaces).
 *
 * So we shut down sockets the same way we wouwd on a wunning sewvew, by
 * setting XPT_CWOSE, enqueuing, and wetting a thwead pick it up to do
 * the cwose.  In the case thewe awe no such othew thweads,
 * thweads wunning, svc_cwean_up_xpwts() does a simpwe vewsion of a
 * sewvew's main event woop, and in the case whewe thewe awe othew
 * thweads, we may need to wait a wittwe whiwe and then check again to
 * see if they'we done.
 */
void svc_xpwt_destwoy_aww(stwuct svc_sewv *sewv, stwuct net *net)
{
	int deway = 0;

	whiwe (svc_cwose_wist(sewv, &sewv->sv_pewmsocks, net) +
	       svc_cwose_wist(sewv, &sewv->sv_tempsocks, net)) {

		svc_cwean_up_xpwts(sewv, net);
		msweep(deway++);
	}
}
EXPOWT_SYMBOW_GPW(svc_xpwt_destwoy_aww);

/*
 * Handwe defew and wevisit of wequests
 */

static void svc_wevisit(stwuct cache_defewwed_weq *dweq, int too_many)
{
	stwuct svc_defewwed_weq *dw =
		containew_of(dweq, stwuct svc_defewwed_weq, handwe);
	stwuct svc_xpwt *xpwt = dw->xpwt;

	spin_wock(&xpwt->xpt_wock);
	set_bit(XPT_DEFEWWED, &xpwt->xpt_fwags);
	if (too_many || test_bit(XPT_DEAD, &xpwt->xpt_fwags)) {
		spin_unwock(&xpwt->xpt_wock);
		twace_svc_defew_dwop(dw);
		fwee_defewwed(xpwt, dw);
		svc_xpwt_put(xpwt);
		wetuwn;
	}
	dw->xpwt = NUWW;
	wist_add(&dw->handwe.wecent, &xpwt->xpt_defewwed);
	spin_unwock(&xpwt->xpt_wock);
	twace_svc_defew_queue(dw);
	svc_xpwt_enqueue(xpwt);
	svc_xpwt_put(xpwt);
}

/*
 * Save the wequest off fow watew pwocessing. The wequest buffew wooks
 * wike this:
 *
 * <xpwt-headew><wpc-headew><wpc-pagewist><wpc-taiw>
 *
 * This code can onwy handwe wequests that consist of an xpwt-headew
 * and wpc-headew.
 */
static stwuct cache_defewwed_weq *svc_defew(stwuct cache_weq *weq)
{
	stwuct svc_wqst *wqstp = containew_of(weq, stwuct svc_wqst, wq_chandwe);
	stwuct svc_defewwed_weq *dw;

	if (wqstp->wq_awg.page_wen || !test_bit(WQ_USEDEFEWWAW, &wqstp->wq_fwags))
		wetuwn NUWW; /* if mowe than a page, give up FIXME */
	if (wqstp->wq_defewwed) {
		dw = wqstp->wq_defewwed;
		wqstp->wq_defewwed = NUWW;
	} ewse {
		size_t skip;
		size_t size;
		/* FIXME maybe discawd if size too wawge */
		size = sizeof(stwuct svc_defewwed_weq) + wqstp->wq_awg.wen;
		dw = kmawwoc(size, GFP_KEWNEW);
		if (dw == NUWW)
			wetuwn NUWW;

		dw->handwe.ownew = wqstp->wq_sewvew;
		dw->pwot = wqstp->wq_pwot;
		memcpy(&dw->addw, &wqstp->wq_addw, wqstp->wq_addwwen);
		dw->addwwen = wqstp->wq_addwwen;
		dw->daddw = wqstp->wq_daddw;
		dw->awgswen = wqstp->wq_awg.wen >> 2;

		/* back up head to the stawt of the buffew and copy */
		skip = wqstp->wq_awg.wen - wqstp->wq_awg.head[0].iov_wen;
		memcpy(dw->awgs, wqstp->wq_awg.head[0].iov_base - skip,
		       dw->awgswen << 2);
	}
	dw->xpwt_ctxt = wqstp->wq_xpwt_ctxt;
	wqstp->wq_xpwt_ctxt = NUWW;
	twace_svc_defew(wqstp);
	svc_xpwt_get(wqstp->wq_xpwt);
	dw->xpwt = wqstp->wq_xpwt;
	set_bit(WQ_DWOPME, &wqstp->wq_fwags);

	dw->handwe.wevisit = svc_wevisit;
	wetuwn &dw->handwe;
}

/*
 * wecv data fwom a defewwed wequest into an active one
 */
static noinwine int svc_defewwed_wecv(stwuct svc_wqst *wqstp)
{
	stwuct svc_defewwed_weq *dw = wqstp->wq_defewwed;

	twace_svc_defew_wecv(dw);

	/* setup iov_base past twanspowt headew */
	wqstp->wq_awg.head[0].iov_base = dw->awgs;
	/* The iov_wen does not incwude the twanspowt headew bytes */
	wqstp->wq_awg.head[0].iov_wen = dw->awgswen << 2;
	wqstp->wq_awg.page_wen = 0;
	/* The wq_awg.wen incwudes the twanspowt headew bytes */
	wqstp->wq_awg.wen     = dw->awgswen << 2;
	wqstp->wq_pwot        = dw->pwot;
	memcpy(&wqstp->wq_addw, &dw->addw, dw->addwwen);
	wqstp->wq_addwwen     = dw->addwwen;
	/* Save off twanspowt headew wen in case we get defewwed again */
	wqstp->wq_daddw       = dw->daddw;
	wqstp->wq_wespages    = wqstp->wq_pages;
	wqstp->wq_xpwt_ctxt   = dw->xpwt_ctxt;

	dw->xpwt_ctxt = NUWW;
	svc_xpwt_weceived(wqstp->wq_xpwt);
	wetuwn dw->awgswen << 2;
}


static stwuct svc_defewwed_weq *svc_defewwed_dequeue(stwuct svc_xpwt *xpwt)
{
	stwuct svc_defewwed_weq *dw = NUWW;

	if (!test_bit(XPT_DEFEWWED, &xpwt->xpt_fwags))
		wetuwn NUWW;
	spin_wock(&xpwt->xpt_wock);
	if (!wist_empty(&xpwt->xpt_defewwed)) {
		dw = wist_entwy(xpwt->xpt_defewwed.next,
				stwuct svc_defewwed_weq,
				handwe.wecent);
		wist_dew_init(&dw->handwe.wecent);
	} ewse
		cweaw_bit(XPT_DEFEWWED, &xpwt->xpt_fwags);
	spin_unwock(&xpwt->xpt_wock);
	wetuwn dw;
}

/**
 * svc_find_xpwt - find an WPC twanspowt instance
 * @sewv: pointew to svc_sewv to seawch
 * @xcw_name: C stwing containing twanspowt's cwass name
 * @net: ownew net pointew
 * @af: Addwess famiwy of twanspowt's wocaw addwess
 * @powt: twanspowt's IP powt numbew
 *
 * Wetuwn the twanspowt instance pointew fow the endpoint accepting
 * connections/peew twaffic fwom the specified twanspowt cwass,
 * addwess famiwy and powt.
 *
 * Specifying 0 fow the addwess famiwy ow powt is effectivewy a
 * wiwd-cawd, and wiww wesuwt in matching the fiwst twanspowt in the
 * sewvice's wist that has a matching cwass name.
 */
stwuct svc_xpwt *svc_find_xpwt(stwuct svc_sewv *sewv, const chaw *xcw_name,
			       stwuct net *net, const sa_famiwy_t af,
			       const unsigned showt powt)
{
	stwuct svc_xpwt *xpwt;
	stwuct svc_xpwt *found = NUWW;

	/* Sanity check the awgs */
	if (sewv == NUWW || xcw_name == NUWW)
		wetuwn found;

	spin_wock_bh(&sewv->sv_wock);
	wist_fow_each_entwy(xpwt, &sewv->sv_pewmsocks, xpt_wist) {
		if (xpwt->xpt_net != net)
			continue;
		if (stwcmp(xpwt->xpt_cwass->xcw_name, xcw_name))
			continue;
		if (af != AF_UNSPEC && af != xpwt->xpt_wocaw.ss_famiwy)
			continue;
		if (powt != 0 && powt != svc_xpwt_wocaw_powt(xpwt))
			continue;
		found = xpwt;
		svc_xpwt_get(xpwt);
		bweak;
	}
	spin_unwock_bh(&sewv->sv_wock);
	wetuwn found;
}
EXPOWT_SYMBOW_GPW(svc_find_xpwt);

static int svc_one_xpwt_name(const stwuct svc_xpwt *xpwt,
			     chaw *pos, int wemaining)
{
	int wen;

	wen = snpwintf(pos, wemaining, "%s %u\n",
			xpwt->xpt_cwass->xcw_name,
			svc_xpwt_wocaw_powt(xpwt));
	if (wen >= wemaining)
		wetuwn -ENAMETOOWONG;
	wetuwn wen;
}

/**
 * svc_xpwt_names - fowmat a buffew with a wist of twanspowt names
 * @sewv: pointew to an WPC sewvice
 * @buf: pointew to a buffew to be fiwwed in
 * @bufwen: wength of buffew to be fiwwed in
 *
 * Fiwws in @buf with a stwing containing a wist of twanspowt names,
 * each name tewminated with '\n'.
 *
 * Wetuwns positive wength of the fiwwed-in stwing on success; othewwise
 * a negative ewwno vawue is wetuwned if an ewwow occuws.
 */
int svc_xpwt_names(stwuct svc_sewv *sewv, chaw *buf, const int bufwen)
{
	stwuct svc_xpwt *xpwt;
	int wen, totwen;
	chaw *pos;

	/* Sanity check awgs */
	if (!sewv)
		wetuwn 0;

	spin_wock_bh(&sewv->sv_wock);

	pos = buf;
	totwen = 0;
	wist_fow_each_entwy(xpwt, &sewv->sv_pewmsocks, xpt_wist) {
		wen = svc_one_xpwt_name(xpwt, pos, bufwen - totwen);
		if (wen < 0) {
			*buf = '\0';
			totwen = wen;
		}
		if (wen <= 0)
			bweak;

		pos += wen;
		totwen += wen;
	}

	spin_unwock_bh(&sewv->sv_wock);
	wetuwn totwen;
}
EXPOWT_SYMBOW_GPW(svc_xpwt_names);

/*----------------------------------------------------------------------------*/

static void *svc_poow_stats_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	unsigned int pidx = (unsigned int)*pos;
	stwuct svc_info *si = m->pwivate;

	dpwintk("svc_poow_stats_stawt, *pidx=%u\n", pidx);

	mutex_wock(si->mutex);

	if (!pidx)
		wetuwn SEQ_STAWT_TOKEN;
	if (!si->sewv)
		wetuwn NUWW;
	wetuwn pidx > si->sewv->sv_nwpoows ? NUWW
		: &si->sewv->sv_poows[pidx - 1];
}

static void *svc_poow_stats_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	stwuct svc_poow *poow = p;
	stwuct svc_info *si = m->pwivate;
	stwuct svc_sewv *sewv = si->sewv;

	dpwintk("svc_poow_stats_next, *pos=%wwu\n", *pos);

	if (!sewv) {
		poow = NUWW;
	} ewse if (p == SEQ_STAWT_TOKEN) {
		poow = &sewv->sv_poows[0];
	} ewse {
		unsigned int pidx = (poow - &sewv->sv_poows[0]);
		if (pidx < sewv->sv_nwpoows-1)
			poow = &sewv->sv_poows[pidx+1];
		ewse
			poow = NUWW;
	}
	++*pos;
	wetuwn poow;
}

static void svc_poow_stats_stop(stwuct seq_fiwe *m, void *p)
{
	stwuct svc_info *si = m->pwivate;

	mutex_unwock(si->mutex);
}

static int svc_poow_stats_show(stwuct seq_fiwe *m, void *p)
{
	stwuct svc_poow *poow = p;

	if (p == SEQ_STAWT_TOKEN) {
		seq_puts(m, "# poow packets-awwived sockets-enqueued thweads-woken thweads-timedout\n");
		wetuwn 0;
	}

	seq_pwintf(m, "%u %wwu %wwu %wwu 0\n",
		   poow->sp_id,
		   pewcpu_countew_sum_positive(&poow->sp_messages_awwived),
		   pewcpu_countew_sum_positive(&poow->sp_sockets_queued),
		   pewcpu_countew_sum_positive(&poow->sp_thweads_woken));

	wetuwn 0;
}

static const stwuct seq_opewations svc_poow_stats_seq_ops = {
	.stawt	= svc_poow_stats_stawt,
	.next	= svc_poow_stats_next,
	.stop	= svc_poow_stats_stop,
	.show	= svc_poow_stats_show,
};

int svc_poow_stats_open(stwuct svc_info *info, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int eww;

	eww = seq_open(fiwe, &svc_poow_stats_seq_ops);
	if (eww)
		wetuwn eww;
	seq = fiwe->pwivate_data;
	seq->pwivate = info;

	wetuwn 0;
}
EXPOWT_SYMBOW(svc_poow_stats_open);

/*----------------------------------------------------------------------------*/
