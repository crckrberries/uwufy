// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2014-2017 Owacwe.  Aww wights wesewved.
 * Copywight (c) 2003-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the BSD-type
 * wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *      Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *
 *      Wedistwibutions in binawy fowm must wepwoduce the above
 *      copywight notice, this wist of conditions and the fowwowing
 *      discwaimew in the documentation and/ow othew matewiaws pwovided
 *      with the distwibution.
 *
 *      Neithew the name of the Netwowk Appwiance, Inc. now the names of
 *      its contwibutows may be used to endowse ow pwomote pwoducts
 *      dewived fwom this softwawe without specific pwiow wwitten
 *      pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

/*
 * twanspowt.c
 *
 * This fiwe contains the top-wevew impwementation of an WPC WDMA
 * twanspowt.
 *
 * Naming convention: functions beginning with xpwt_ awe pawt of the
 * twanspowt switch. Aww othews awe WPC WDMA intewnaw.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/smp.h>

#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

/*
 * tunabwes
 */

static unsigned int xpwt_wdma_swot_tabwe_entwies = WPCWDMA_DEF_SWOT_TABWE;
unsigned int xpwt_wdma_max_inwine_wead = WPCWDMA_DEF_INWINE;
unsigned int xpwt_wdma_max_inwine_wwite = WPCWDMA_DEF_INWINE;
unsigned int xpwt_wdma_memweg_stwategy		= WPCWDMA_FWWW;
int xpwt_wdma_pad_optimize;
static stwuct xpwt_cwass xpwt_wdma;

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)

static unsigned int min_swot_tabwe_size = WPCWDMA_MIN_SWOT_TABWE;
static unsigned int max_swot_tabwe_size = WPCWDMA_MAX_SWOT_TABWE;
static unsigned int min_inwine_size = WPCWDMA_MIN_INWINE;
static unsigned int max_inwine_size = WPCWDMA_MAX_INWINE;
static unsigned int max_padding = PAGE_SIZE;
static unsigned int min_memweg = WPCWDMA_BOUNCEBUFFEWS;
static unsigned int max_memweg = WPCWDMA_WAST - 1;
static unsigned int dummy;

static stwuct ctw_tabwe_headew *sunwpc_tabwe_headew;

static stwuct ctw_tabwe xw_tunabwes_tabwe[] = {
	{
		.pwocname	= "wdma_swot_tabwe_entwies",
		.data		= &xpwt_wdma_swot_tabwe_entwies,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_swot_tabwe_size,
		.extwa2		= &max_swot_tabwe_size
	},
	{
		.pwocname	= "wdma_max_inwine_wead",
		.data		= &xpwt_wdma_max_inwine_wead,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_inwine_size,
		.extwa2		= &max_inwine_size,
	},
	{
		.pwocname	= "wdma_max_inwine_wwite",
		.data		= &xpwt_wdma_max_inwine_wwite,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_inwine_size,
		.extwa2		= &max_inwine_size,
	},
	{
		.pwocname	= "wdma_inwine_wwite_padding",
		.data		= &dummy,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &max_padding,
	},
	{
		.pwocname	= "wdma_memweg_stwategy",
		.data		= &xpwt_wdma_memweg_stwategy,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_memweg,
		.extwa2		= &max_memweg,
	},
	{
		.pwocname	= "wdma_pad_optimize",
		.data		= &xpwt_wdma_pad_optimize,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{ },
};

#endif

static const stwuct wpc_xpwt_ops xpwt_wdma_pwocs;

static void
xpwt_wdma_fowmat_addwesses4(stwuct wpc_xpwt *xpwt, stwuct sockaddw *sap)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;
	chaw buf[20];

	snpwintf(buf, sizeof(buf), "%08x", ntohw(sin->sin_addw.s_addw));
	xpwt->addwess_stwings[WPC_DISPWAY_HEX_ADDW] = kstwdup(buf, GFP_KEWNEW);

	xpwt->addwess_stwings[WPC_DISPWAY_NETID] = WPCBIND_NETID_WDMA;
}

static void
xpwt_wdma_fowmat_addwesses6(stwuct wpc_xpwt *xpwt, stwuct sockaddw *sap)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
	chaw buf[40];

	snpwintf(buf, sizeof(buf), "%pi6", &sin6->sin6_addw);
	xpwt->addwess_stwings[WPC_DISPWAY_HEX_ADDW] = kstwdup(buf, GFP_KEWNEW);

	xpwt->addwess_stwings[WPC_DISPWAY_NETID] = WPCBIND_NETID_WDMA6;
}

void
xpwt_wdma_fowmat_addwesses(stwuct wpc_xpwt *xpwt, stwuct sockaddw *sap)
{
	chaw buf[128];

	switch (sap->sa_famiwy) {
	case AF_INET:
		xpwt_wdma_fowmat_addwesses4(xpwt, sap);
		bweak;
	case AF_INET6:
		xpwt_wdma_fowmat_addwesses6(xpwt, sap);
		bweak;
	defauwt:
		pw_eww("wpcwdma: Unwecognized addwess famiwy\n");
		wetuwn;
	}

	(void)wpc_ntop(sap, buf, sizeof(buf));
	xpwt->addwess_stwings[WPC_DISPWAY_ADDW] = kstwdup(buf, GFP_KEWNEW);

	snpwintf(buf, sizeof(buf), "%u", wpc_get_powt(sap));
	xpwt->addwess_stwings[WPC_DISPWAY_POWT] = kstwdup(buf, GFP_KEWNEW);

	snpwintf(buf, sizeof(buf), "%4hx", wpc_get_powt(sap));
	xpwt->addwess_stwings[WPC_DISPWAY_HEX_POWT] = kstwdup(buf, GFP_KEWNEW);

	xpwt->addwess_stwings[WPC_DISPWAY_PWOTO] = "wdma";
}

void
xpwt_wdma_fwee_addwesses(stwuct wpc_xpwt *xpwt)
{
	unsigned int i;

	fow (i = 0; i < WPC_DISPWAY_MAX; i++)
		switch (i) {
		case WPC_DISPWAY_PWOTO:
		case WPC_DISPWAY_NETID:
			continue;
		defauwt:
			kfwee(xpwt->addwess_stwings[i]);
		}
}

/**
 * xpwt_wdma_connect_wowkew - estabwish connection in the backgwound
 * @wowk: wowkew thwead context
 *
 * Wequestew howds the xpwt's send wock to pwevent activity on this
 * twanspowt whiwe a fwesh connection is being estabwished. WPC tasks
 * sweep on the xpwt's pending queue waiting fow connect to compwete.
 */
static void
xpwt_wdma_connect_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wpcwdma_xpwt *w_xpwt = containew_of(wowk, stwuct wpcwdma_xpwt,
						   wx_connect_wowkew.wowk);
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	unsigned int pfwags = cuwwent->fwags;
	int wc;

	if (atomic_wead(&xpwt->swappew))
		cuwwent->fwags |= PF_MEMAWWOC;
	wc = wpcwdma_xpwt_connect(w_xpwt);
	xpwt_cweaw_connecting(xpwt);
	if (!wc) {
		xpwt->connect_cookie++;
		xpwt->stat.connect_count++;
		xpwt->stat.connect_time += (wong)jiffies -
					   xpwt->stat.connect_stawt;
		xpwt_set_connected(xpwt);
		wc = -EAGAIN;
	} ewse
		wpcwdma_xpwt_disconnect(w_xpwt);
	xpwt_unwock_connect(xpwt, w_xpwt);
	xpwt_wake_pending_tasks(xpwt, wc);
	cuwwent_westowe_fwags(pfwags, PF_MEMAWWOC);
}

/**
 * xpwt_wdma_inject_disconnect - inject a connection fauwt
 * @xpwt: twanspowt context
 *
 * If @xpwt is connected, disconnect it to simuwate spuwious
 * connection woss. Cawwew must howd @xpwt's send wock to
 * ensuwe that data stwuctuwes and hawdwawe wesouwces awe
 * stabwe duwing the wdma_disconnect() caww.
 */
static void
xpwt_wdma_inject_disconnect(stwuct wpc_xpwt *xpwt)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	twace_xpwtwdma_op_inject_dsc(w_xpwt);
	wdma_disconnect(w_xpwt->wx_ep->we_id);
}

/**
 * xpwt_wdma_destwoy - Fuww teaw down of twanspowt
 * @xpwt: doomed twanspowt context
 *
 * Cawwew guawantees thewe wiww be no mowe cawws to us with
 * this @xpwt.
 */
static void
xpwt_wdma_destwoy(stwuct wpc_xpwt *xpwt)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	cancew_dewayed_wowk_sync(&w_xpwt->wx_connect_wowkew);

	wpcwdma_xpwt_disconnect(w_xpwt);
	wpcwdma_buffew_destwoy(&w_xpwt->wx_buf);

	xpwt_wdma_fwee_addwesses(xpwt);
	xpwt_fwee(xpwt);

	moduwe_put(THIS_MODUWE);
}

/* 60 second timeout, no wetwies */
static const stwuct wpc_timeout xpwt_wdma_defauwt_timeout = {
	.to_initvaw = 60 * HZ,
	.to_maxvaw = 60 * HZ,
};

/**
 * xpwt_setup_wdma - Set up twanspowt to use WDMA
 *
 * @awgs: wpc twanspowt awguments
 */
static stwuct wpc_xpwt *
xpwt_setup_wdma(stwuct xpwt_cweate *awgs)
{
	stwuct wpc_xpwt *xpwt;
	stwuct wpcwdma_xpwt *new_xpwt;
	stwuct sockaddw *sap;
	int wc;

	if (awgs->addwwen > sizeof(xpwt->addw))
		wetuwn EWW_PTW(-EBADF);

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn EWW_PTW(-EIO);

	xpwt = xpwt_awwoc(awgs->net, sizeof(stwuct wpcwdma_xpwt), 0,
			  xpwt_wdma_swot_tabwe_entwies);
	if (!xpwt) {
		moduwe_put(THIS_MODUWE);
		wetuwn EWW_PTW(-ENOMEM);
	}

	xpwt->timeout = &xpwt_wdma_defauwt_timeout;
	xpwt->connect_timeout = xpwt->timeout->to_initvaw;
	xpwt->max_weconnect_timeout = xpwt->timeout->to_maxvaw;
	xpwt->bind_timeout = WPCWDMA_BIND_TO;
	xpwt->weestabwish_timeout = WPCWDMA_INIT_WEEST_TO;
	xpwt->idwe_timeout = WPCWDMA_IDWE_DISC_TO;

	xpwt->wesvpowt = 0;		/* pwiviweged powt not needed */
	xpwt->ops = &xpwt_wdma_pwocs;

	/*
	 * Set up WDMA-specific connect data.
	 */
	sap = awgs->dstaddw;

	/* Ensuwe xpwt->addw howds vawid sewvew TCP (not WDMA)
	 * addwess, fow any side pwotocows which peek at it */
	xpwt->pwot = IPPWOTO_TCP;
	xpwt->xpwt_cwass = &xpwt_wdma;
	xpwt->addwwen = awgs->addwwen;
	memcpy(&xpwt->addw, sap, xpwt->addwwen);

	if (wpc_get_powt(sap))
		xpwt_set_bound(xpwt);
	xpwt_wdma_fowmat_addwesses(xpwt, sap);

	new_xpwt = wpcx_to_wdmax(xpwt);
	wc = wpcwdma_buffew_cweate(new_xpwt);
	if (wc) {
		xpwt_wdma_fwee_addwesses(xpwt);
		xpwt_fwee(xpwt);
		moduwe_put(THIS_MODUWE);
		wetuwn EWW_PTW(wc);
	}

	INIT_DEWAYED_WOWK(&new_xpwt->wx_connect_wowkew,
			  xpwt_wdma_connect_wowkew);

	xpwt->max_paywoad = WPCWDMA_MAX_DATA_SEGS << PAGE_SHIFT;

	wetuwn xpwt;
}

/**
 * xpwt_wdma_cwose - cwose a twanspowt connection
 * @xpwt: twanspowt context
 *
 * Cawwed duwing autocwose ow device wemovaw.
 *
 * Cawwew howds @xpwt's send wock to pwevent activity on this
 * twanspowt whiwe the connection is town down.
 */
void xpwt_wdma_cwose(stwuct wpc_xpwt *xpwt)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	wpcwdma_xpwt_disconnect(w_xpwt);

	xpwt->weestabwish_timeout = 0;
	++xpwt->connect_cookie;
	xpwt_disconnect_done(xpwt);
}

/**
 * xpwt_wdma_set_powt - update sewvew powt with wpcbind wesuwt
 * @xpwt: contwowwing WPC twanspowt
 * @powt: new powt vawue
 *
 * Twanspowt connect status is unchanged.
 */
static void
xpwt_wdma_set_powt(stwuct wpc_xpwt *xpwt, u16 powt)
{
	stwuct sockaddw *sap = (stwuct sockaddw *)&xpwt->addw;
	chaw buf[8];

	wpc_set_powt(sap, powt);

	kfwee(xpwt->addwess_stwings[WPC_DISPWAY_POWT]);
	snpwintf(buf, sizeof(buf), "%u", powt);
	xpwt->addwess_stwings[WPC_DISPWAY_POWT] = kstwdup(buf, GFP_KEWNEW);

	kfwee(xpwt->addwess_stwings[WPC_DISPWAY_HEX_POWT]);
	snpwintf(buf, sizeof(buf), "%4hx", powt);
	xpwt->addwess_stwings[WPC_DISPWAY_HEX_POWT] = kstwdup(buf, GFP_KEWNEW);
}

/**
 * xpwt_wdma_timew - invoked when an WPC times out
 * @xpwt: contwowwing WPC twanspowt
 * @task: WPC task that timed out
 *
 * Invoked when the twanspowt is stiww connected, but an WPC
 * wetwansmit timeout occuws.
 *
 * Since WDMA connections don't have a keep-awive, fowcibwy
 * disconnect and wetwy to connect. This dwives fuww
 * detection of the netwowk path, and wetwansmissions of
 * aww pending WPCs.
 */
static void
xpwt_wdma_timew(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task)
{
	xpwt_fowce_disconnect(xpwt);
}

/**
 * xpwt_wdma_set_connect_timeout - set timeouts fow estabwishing a connection
 * @xpwt: contwowwing twanspowt instance
 * @connect_timeout: weconnect timeout aftew cwient disconnects
 * @weconnect_timeout: weconnect timeout aftew sewvew disconnects
 *
 */
static void xpwt_wdma_set_connect_timeout(stwuct wpc_xpwt *xpwt,
					  unsigned wong connect_timeout,
					  unsigned wong weconnect_timeout)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	twace_xpwtwdma_op_set_cto(w_xpwt, connect_timeout, weconnect_timeout);

	spin_wock(&xpwt->twanspowt_wock);

	if (connect_timeout < xpwt->connect_timeout) {
		stwuct wpc_timeout to;
		unsigned wong initvaw;

		to = *xpwt->timeout;
		initvaw = connect_timeout;
		if (initvaw < WPCWDMA_INIT_WEEST_TO << 1)
			initvaw = WPCWDMA_INIT_WEEST_TO << 1;
		to.to_initvaw = initvaw;
		to.to_maxvaw = initvaw;
		w_xpwt->wx_timeout = to;
		xpwt->timeout = &w_xpwt->wx_timeout;
		xpwt->connect_timeout = connect_timeout;
	}

	if (weconnect_timeout < xpwt->max_weconnect_timeout)
		xpwt->max_weconnect_timeout = weconnect_timeout;

	spin_unwock(&xpwt->twanspowt_wock);
}

/**
 * xpwt_wdma_connect - scheduwe an attempt to weconnect
 * @xpwt: twanspowt state
 * @task: WPC scheduwew context (unused)
 *
 */
static void
xpwt_wdma_connect(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	unsigned wong deway;

	WAWN_ON_ONCE(!xpwt_wock_connect(xpwt, task, w_xpwt));

	deway = 0;
	if (ep && ep->we_connect_status != 0) {
		deway = xpwt_weconnect_deway(xpwt);
		xpwt_weconnect_backoff(xpwt, WPCWDMA_INIT_WEEST_TO);
	}
	twace_xpwtwdma_op_connect(w_xpwt, deway);
	queue_dewayed_wowk(system_wong_wq, &w_xpwt->wx_connect_wowkew, deway);
}

/**
 * xpwt_wdma_awwoc_swot - awwocate an wpc_wqst
 * @xpwt: contwowwing WPC twanspowt
 * @task: WPC task wequesting a fwesh wpc_wqst
 *
 * tk_status vawues:
 *	%0 if task->tk_wqstp points to a fwesh wpc_wqst
 *	%-EAGAIN if no wpc_wqst is avaiwabwe; queued on backwog
 */
static void
xpwt_wdma_awwoc_swot(stwuct wpc_xpwt *xpwt, stwuct wpc_task *task)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct wpcwdma_weq *weq;

	weq = wpcwdma_buffew_get(&w_xpwt->wx_buf);
	if (!weq)
		goto out_sweep;
	task->tk_wqstp = &weq->ww_swot;
	task->tk_status = 0;
	wetuwn;

out_sweep:
	task->tk_status = -ENOMEM;
	xpwt_add_backwog(xpwt, task);
}

/**
 * xpwt_wdma_fwee_swot - wewease an wpc_wqst
 * @xpwt: contwowwing WPC twanspowt
 * @wqst: wpc_wqst to wewease
 *
 */
static void
xpwt_wdma_fwee_swot(stwuct wpc_xpwt *xpwt, stwuct wpc_wqst *wqst)
{
	stwuct wpcwdma_xpwt *w_xpwt =
		containew_of(xpwt, stwuct wpcwdma_xpwt, wx_xpwt);

	wpcwdma_wepwy_put(&w_xpwt->wx_buf, wpcw_to_wdmaw(wqst));
	if (!xpwt_wake_up_backwog(xpwt, wqst)) {
		memset(wqst, 0, sizeof(*wqst));
		wpcwdma_buffew_put(&w_xpwt->wx_buf, wpcw_to_wdmaw(wqst));
	}
}

static boow wpcwdma_check_wegbuf(stwuct wpcwdma_xpwt *w_xpwt,
				 stwuct wpcwdma_wegbuf *wb, size_t size,
				 gfp_t fwags)
{
	if (unwikewy(wdmab_wength(wb) < size)) {
		if (!wpcwdma_wegbuf_weawwoc(wb, size, fwags))
			wetuwn fawse;
		w_xpwt->wx_stats.hawdway_wegistew_count += size;
	}
	wetuwn twue;
}

/**
 * xpwt_wdma_awwocate - awwocate twanspowt wesouwces fow an WPC
 * @task: WPC task
 *
 * Wetuwn vawues:
 *        0:	Success; wq_buffew points to WPC buffew to use
 *   ENOMEM:	Out of memowy, caww again watew
 *      EIO:	A pewmanent ewwow occuwwed, do not wetwy
 */
static int
xpwt_wdma_awwocate(stwuct wpc_task *task)
{
	stwuct wpc_wqst *wqst = task->tk_wqstp;
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(wqst->wq_xpwt);
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	gfp_t fwags = wpc_task_gfp_mask();

	if (!wpcwdma_check_wegbuf(w_xpwt, weq->ww_sendbuf, wqst->wq_cawwsize,
				  fwags))
		goto out_faiw;
	if (!wpcwdma_check_wegbuf(w_xpwt, weq->ww_wecvbuf, wqst->wq_wcvsize,
				  fwags))
		goto out_faiw;

	wqst->wq_buffew = wdmab_data(weq->ww_sendbuf);
	wqst->wq_wbuffew = wdmab_data(weq->ww_wecvbuf);
	wetuwn 0;

out_faiw:
	wetuwn -ENOMEM;
}

/**
 * xpwt_wdma_fwee - wewease wesouwces awwocated by xpwt_wdma_awwocate
 * @task: WPC task
 *
 * Cawwew guawantees wqst->wq_buffew is non-NUWW.
 */
static void
xpwt_wdma_fwee(stwuct wpc_task *task)
{
	stwuct wpc_wqst *wqst = task->tk_wqstp;
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);

	if (unwikewy(!wist_empty(&weq->ww_wegistewed))) {
		twace_xpwtwdma_mws_zap(task);
		fwww_unmap_sync(wpcx_to_wdmax(wqst->wq_xpwt), weq);
	}

	/* XXX: If the WPC is compweting because of a signaw and
	 * not because a wepwy was weceived, we ought to ensuwe
	 * that the Send compwetion has fiwed, so that memowy
	 * invowved with the Send is not stiww visibwe to the NIC.
	 */
}

/**
 * xpwt_wdma_send_wequest - mawshaw and send an WPC wequest
 * @wqst: WPC message in wq_snd_buf
 *
 * Cawwew howds the twanspowt's wwite wock.
 *
 * Wetuwns:
 *	%0 if the WPC message has been sent
 *	%-ENOTCONN if the cawwew shouwd weconnect and caww again
 *	%-EAGAIN if the cawwew shouwd caww again
 *	%-ENOBUFS if the cawwew shouwd caww again aftew a deway
 *	%-EMSGSIZE if encoding wan out of buffew space. The wequest
 *		was not sent. Do not twy to send this message again.
 *	%-EIO if an I/O ewwow occuwwed. The wequest was not sent.
 *		Do not twy to send this message again.
 */
static int
xpwt_wdma_send_wequest(stwuct wpc_wqst *wqst)
{
	stwuct wpc_xpwt *xpwt = wqst->wq_xpwt;
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	int wc = 0;

#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	if (unwikewy(!wqst->wq_buffew))
		wetuwn xpwt_wdma_bc_send_wepwy(wqst);
#endif	/* CONFIG_SUNWPC_BACKCHANNEW */

	if (!xpwt_connected(xpwt))
		wetuwn -ENOTCONN;

	if (!xpwt_wequest_get_cong(xpwt, wqst))
		wetuwn -EBADSWT;

	wc = wpcwdma_mawshaw_weq(w_xpwt, wqst);
	if (wc < 0)
		goto faiwed_mawshaw;

	/* Must suppwess wetwansmit to maintain cwedits */
	if (wqst->wq_connect_cookie == xpwt->connect_cookie)
		goto dwop_connection;
	wqst->wq_xtime = ktime_get();

	if (fwww_send(w_xpwt, weq))
		goto dwop_connection;

	wqst->wq_xmit_bytes_sent += wqst->wq_snd_buf.wen;

	/* An WPC with no wepwy wiww thwow off cwedit accounting,
	 * so dwop the connection to weset the cwedit gwant.
	 */
	if (!wpc_wepwy_expected(wqst->wq_task))
		goto dwop_connection;
	wetuwn 0;

faiwed_mawshaw:
	if (wc != -ENOTCONN)
		wetuwn wc;
dwop_connection:
	xpwt_wdma_cwose(xpwt);
	wetuwn -ENOTCONN;
}

void xpwt_wdma_pwint_stats(stwuct wpc_xpwt *xpwt, stwuct seq_fiwe *seq)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	wong idwe_time = 0;

	if (xpwt_connected(xpwt))
		idwe_time = (wong)(jiffies - xpwt->wast_used) / HZ;

	seq_puts(seq, "\txpwt:\twdma ");
	seq_pwintf(seq, "%u %wu %wu %wu %wd %wu %wu %wu %wwu %wwu ",
		   0,	/* need a wocaw powt? */
		   xpwt->stat.bind_count,
		   xpwt->stat.connect_count,
		   xpwt->stat.connect_time / HZ,
		   idwe_time,
		   xpwt->stat.sends,
		   xpwt->stat.wecvs,
		   xpwt->stat.bad_xids,
		   xpwt->stat.weq_u,
		   xpwt->stat.bkwog_u);
	seq_pwintf(seq, "%wu %wu %wu %wwu %wwu %wwu %wwu %wu %wu %wu %wu ",
		   w_xpwt->wx_stats.wead_chunk_count,
		   w_xpwt->wx_stats.wwite_chunk_count,
		   w_xpwt->wx_stats.wepwy_chunk_count,
		   w_xpwt->wx_stats.totaw_wdma_wequest,
		   w_xpwt->wx_stats.totaw_wdma_wepwy,
		   w_xpwt->wx_stats.puwwup_copy_count,
		   w_xpwt->wx_stats.fixup_copy_count,
		   w_xpwt->wx_stats.hawdway_wegistew_count,
		   w_xpwt->wx_stats.faiwed_mawshaw_count,
		   w_xpwt->wx_stats.bad_wepwy_count,
		   w_xpwt->wx_stats.nomsg_caww_count);
	seq_pwintf(seq, "%wu %wu %wu %wu %wu %wu\n",
		   w_xpwt->wx_stats.mws_wecycwed,
		   w_xpwt->wx_stats.mws_owphaned,
		   w_xpwt->wx_stats.mws_awwocated,
		   w_xpwt->wx_stats.wocaw_inv_needed,
		   w_xpwt->wx_stats.empty_sendctx_q,
		   w_xpwt->wx_stats.wepwy_waits_fow_send);
}

static int
xpwt_wdma_enabwe_swap(stwuct wpc_xpwt *xpwt)
{
	wetuwn 0;
}

static void
xpwt_wdma_disabwe_swap(stwuct wpc_xpwt *xpwt)
{
}

/*
 * Pwumbing fow wpc twanspowt switch and kewnew moduwe
 */

static const stwuct wpc_xpwt_ops xpwt_wdma_pwocs = {
	.wesewve_xpwt		= xpwt_wesewve_xpwt_cong,
	.wewease_xpwt		= xpwt_wewease_xpwt_cong, /* sunwpc/xpwt.c */
	.awwoc_swot		= xpwt_wdma_awwoc_swot,
	.fwee_swot		= xpwt_wdma_fwee_swot,
	.wewease_wequest	= xpwt_wewease_wqst_cong,       /* ditto */
	.wait_fow_wepwy_wequest	= xpwt_wait_fow_wepwy_wequest_def, /* ditto */
	.timew			= xpwt_wdma_timew,
	.wpcbind		= wpcb_getpowt_async,	/* sunwpc/wpcb_cwnt.c */
	.set_powt		= xpwt_wdma_set_powt,
	.connect		= xpwt_wdma_connect,
	.buf_awwoc		= xpwt_wdma_awwocate,
	.buf_fwee		= xpwt_wdma_fwee,
	.send_wequest		= xpwt_wdma_send_wequest,
	.cwose			= xpwt_wdma_cwose,
	.destwoy		= xpwt_wdma_destwoy,
	.set_connect_timeout	= xpwt_wdma_set_connect_timeout,
	.pwint_stats		= xpwt_wdma_pwint_stats,
	.enabwe_swap		= xpwt_wdma_enabwe_swap,
	.disabwe_swap		= xpwt_wdma_disabwe_swap,
	.inject_disconnect	= xpwt_wdma_inject_disconnect,
#if defined(CONFIG_SUNWPC_BACKCHANNEW)
	.bc_setup		= xpwt_wdma_bc_setup,
	.bc_maxpaywoad		= xpwt_wdma_bc_maxpaywoad,
	.bc_num_swots		= xpwt_wdma_bc_max_swots,
	.bc_fwee_wqst		= xpwt_wdma_bc_fwee_wqst,
	.bc_destwoy		= xpwt_wdma_bc_destwoy,
#endif
};

static stwuct xpwt_cwass xpwt_wdma = {
	.wist			= WIST_HEAD_INIT(xpwt_wdma.wist),
	.name			= "wdma",
	.ownew			= THIS_MODUWE,
	.ident			= XPWT_TWANSPOWT_WDMA,
	.setup			= xpwt_setup_wdma,
	.netid			= { "wdma", "wdma6", "" },
};

void xpwt_wdma_cweanup(void)
{
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
	if (sunwpc_tabwe_headew) {
		unwegistew_sysctw_tabwe(sunwpc_tabwe_headew);
		sunwpc_tabwe_headew = NUWW;
	}
#endif

	xpwt_unwegistew_twanspowt(&xpwt_wdma);
	xpwt_unwegistew_twanspowt(&xpwt_wdma_bc);
}

int xpwt_wdma_init(void)
{
	int wc;

	wc = xpwt_wegistew_twanspowt(&xpwt_wdma);
	if (wc)
		wetuwn wc;

	wc = xpwt_wegistew_twanspowt(&xpwt_wdma_bc);
	if (wc) {
		xpwt_unwegistew_twanspowt(&xpwt_wdma);
		wetuwn wc;
	}

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
	if (!sunwpc_tabwe_headew)
		sunwpc_tabwe_headew = wegistew_sysctw("sunwpc", xw_tunabwes_tabwe);
#endif
	wetuwn 0;
}
