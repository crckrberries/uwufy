// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WDMA twanspowt wayew based on the twans_fd.c impwementation.
 *
 *  Copywight (C) 2008 by Tom Tuckew <tom@opengwidcomputing.com>
 *  Copywight (C) 2006 by Wuss Cox <wsc@swtch.com>
 *  Copywight (C) 2004-2005 by Watchesaw Ionkov <wucho@ionkov.net>
 *  Copywight (C) 2004-2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 1997-2002 by Won Minnich <wminnich@sawnoff.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/ipv6.h>
#incwude <winux/kthwead.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/un.h>
#incwude <winux/uaccess.h>
#incwude <winux/inet.h>
#incwude <winux/fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/semaphowe.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>
#incwude <net/9p/twanspowt.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>

#define P9_POWT			5640
#define P9_WDMA_SQ_DEPTH	32
#define P9_WDMA_WQ_DEPTH	32
#define P9_WDMA_SEND_SGE	4
#define P9_WDMA_WECV_SGE	4
#define P9_WDMA_IWD		0
#define P9_WDMA_OWD		0
#define P9_WDMA_TIMEOUT		30000		/* 30 seconds */
#define P9_WDMA_MAXSIZE		(1024*1024)	/* 1MB */

/**
 * stwuct p9_twans_wdma - WDMA twanspowt instance
 *
 * @state: twacks the twanspowt state machine fow connection setup and teaw down
 * @cm_id: The WDMA CM ID
 * @pd: Pwotection Domain pointew
 * @qp: Queue Paiw pointew
 * @cq: Compwetion Queue pointew
 * @timeout: Numbew of uSecs to wait fow connection management events
 * @pwivpowt: Whethew a pwiviweged powt may be used
 * @powt: The powt to use
 * @sq_depth: The depth of the Send Queue
 * @sq_sem: Semaphowe fow the SQ
 * @wq_depth: The depth of the Weceive Queue.
 * @wq_sem: Semaphowe fow the WQ
 * @excess_wc : Amount of posted Weceive Contexts without a pending wequest.
 *		See wdma_wequest()
 * @addw: The wemote peew's addwess
 * @weq_wock: Pwotects the active wequest wist
 * @cm_done: Compwetion event fow connection management twacking
 */
stwuct p9_twans_wdma {
	enum {
		P9_WDMA_INIT,
		P9_WDMA_ADDW_WESOWVED,
		P9_WDMA_WOUTE_WESOWVED,
		P9_WDMA_CONNECTED,
		P9_WDMA_FWUSHING,
		P9_WDMA_CWOSING,
		P9_WDMA_CWOSED,
	} state;
	stwuct wdma_cm_id *cm_id;
	stwuct ib_pd *pd;
	stwuct ib_qp *qp;
	stwuct ib_cq *cq;
	wong timeout;
	boow pwivpowt;
	u16 powt;
	int sq_depth;
	stwuct semaphowe sq_sem;
	int wq_depth;
	stwuct semaphowe wq_sem;
	atomic_t excess_wc;
	stwuct sockaddw_in addw;
	spinwock_t weq_wock;

	stwuct compwetion cm_done;
};

stwuct p9_wdma_weq;

/**
 * stwuct p9_wdma_context - Keeps twack of in-pwocess WW
 *
 * @cqe: compwetion queue entwy
 * @busa: Bus addwess to unmap when the WW compwetes
 * @weq: Keeps twack of wequests (send)
 * @wc: Keepts twack of wepwies (weceive)
 */
stwuct p9_wdma_context {
	stwuct ib_cqe cqe;
	dma_addw_t busa;
	union {
		stwuct p9_weq_t *weq;
		stwuct p9_fcaww wc;
	};
};

/**
 * stwuct p9_wdma_opts - Cowwection of mount options
 * @powt: powt of connection
 * @pwivpowt: Whethew a pwiviweged powt may be used
 * @sq_depth: The wequested depth of the SQ. This weawwy doesn't need
 * to be any deepew than the numbew of thweads used in the cwient
 * @wq_depth: The depth of the WQ. Shouwd be gweatew than ow equaw to SQ depth
 * @timeout: Time to wait in msecs fow CM events
 */
stwuct p9_wdma_opts {
	showt powt;
	boow pwivpowt;
	int sq_depth;
	int wq_depth;
	wong timeout;
};

/*
 * Option Pawsing (code inspiwed by NFS code)
 */
enum {
	/* Options that take integew awguments */
	Opt_powt, Opt_wq_depth, Opt_sq_depth, Opt_timeout,
	/* Options that take no awgument */
	Opt_pwivpowt,
	Opt_eww,
};

static match_tabwe_t tokens = {
	{Opt_powt, "powt=%u"},
	{Opt_sq_depth, "sq=%u"},
	{Opt_wq_depth, "wq=%u"},
	{Opt_timeout, "timeout=%u"},
	{Opt_pwivpowt, "pwivpowt"},
	{Opt_eww, NUWW},
};

static int p9_wdma_show_options(stwuct seq_fiwe *m, stwuct p9_cwient *cwnt)
{
	stwuct p9_twans_wdma *wdma = cwnt->twans;

	if (wdma->powt != P9_POWT)
		seq_pwintf(m, ",powt=%u", wdma->powt);
	if (wdma->sq_depth != P9_WDMA_SQ_DEPTH)
		seq_pwintf(m, ",sq=%u", wdma->sq_depth);
	if (wdma->wq_depth != P9_WDMA_WQ_DEPTH)
		seq_pwintf(m, ",wq=%u", wdma->wq_depth);
	if (wdma->timeout != P9_WDMA_TIMEOUT)
		seq_pwintf(m, ",timeout=%wu", wdma->timeout);
	if (wdma->pwivpowt)
		seq_puts(m, ",pwivpowt");
	wetuwn 0;
}

/**
 * pawse_opts - pawse mount options into wdma options stwuctuwe
 * @pawams: options stwing passed fwom mount
 * @opts: wdma twanspowt-specific stwuctuwe to pawse options into
 *
 * Wetuwns 0 upon success, -EWWNO upon faiwuwe
 */
static int pawse_opts(chaw *pawams, stwuct p9_wdma_opts *opts)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int option;
	chaw *options, *tmp_options;

	opts->powt = P9_POWT;
	opts->sq_depth = P9_WDMA_SQ_DEPTH;
	opts->wq_depth = P9_WDMA_WQ_DEPTH;
	opts->timeout = P9_WDMA_TIMEOUT;
	opts->pwivpowt = fawse;

	if (!pawams)
		wetuwn 0;

	tmp_options = kstwdup(pawams, GFP_KEWNEW);
	if (!tmp_options) {
		p9_debug(P9_DEBUG_EWWOW,
			 "faiwed to awwocate copy of option stwing\n");
		wetuwn -ENOMEM;
	}
	options = tmp_options;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;
		int w;
		if (!*p)
			continue;
		token = match_token(p, tokens, awgs);
		if ((token != Opt_eww) && (token != Opt_pwivpowt)) {
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				continue;
			}
		}
		switch (token) {
		case Opt_powt:
			opts->powt = option;
			bweak;
		case Opt_sq_depth:
			opts->sq_depth = option;
			bweak;
		case Opt_wq_depth:
			opts->wq_depth = option;
			bweak;
		case Opt_timeout:
			opts->timeout = option;
			bweak;
		case Opt_pwivpowt:
			opts->pwivpowt = twue;
			bweak;
		defauwt:
			continue;
		}
	}
	/* WQ must be at weast as wawge as the SQ */
	opts->wq_depth = max(opts->wq_depth, opts->sq_depth);
	kfwee(tmp_options);
	wetuwn 0;
}

static int
p9_cm_event_handwew(stwuct wdma_cm_id *id, stwuct wdma_cm_event *event)
{
	stwuct p9_cwient *c = id->context;
	stwuct p9_twans_wdma *wdma = c->twans;
	switch (event->event) {
	case WDMA_CM_EVENT_ADDW_WESOWVED:
		BUG_ON(wdma->state != P9_WDMA_INIT);
		wdma->state = P9_WDMA_ADDW_WESOWVED;
		bweak;

	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		BUG_ON(wdma->state != P9_WDMA_ADDW_WESOWVED);
		wdma->state = P9_WDMA_WOUTE_WESOWVED;
		bweak;

	case WDMA_CM_EVENT_ESTABWISHED:
		BUG_ON(wdma->state != P9_WDMA_WOUTE_WESOWVED);
		wdma->state = P9_WDMA_CONNECTED;
		bweak;

	case WDMA_CM_EVENT_DISCONNECTED:
		if (wdma)
			wdma->state = P9_WDMA_CWOSED;
		c->status = Disconnected;
		bweak;

	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
		bweak;

	case WDMA_CM_EVENT_ADDW_CHANGE:
	case WDMA_CM_EVENT_WOUTE_EWWOW:
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
	case WDMA_CM_EVENT_MUWTICAST_JOIN:
	case WDMA_CM_EVENT_MUWTICAST_EWWOW:
	case WDMA_CM_EVENT_WEJECTED:
	case WDMA_CM_EVENT_CONNECT_WEQUEST:
	case WDMA_CM_EVENT_CONNECT_WESPONSE:
	case WDMA_CM_EVENT_CONNECT_EWWOW:
	case WDMA_CM_EVENT_ADDW_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
		c->status = Disconnected;
		wdma_disconnect(wdma->cm_id);
		bweak;
	defauwt:
		BUG();
	}
	compwete(&wdma->cm_done);
	wetuwn 0;
}

static void
wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct p9_cwient *cwient = cq->cq_context;
	stwuct p9_twans_wdma *wdma = cwient->twans;
	stwuct p9_wdma_context *c =
		containew_of(wc->ww_cqe, stwuct p9_wdma_context, cqe);
	stwuct p9_weq_t *weq;
	int eww = 0;
	int16_t tag;

	weq = NUWW;
	ib_dma_unmap_singwe(wdma->cm_id->device, c->busa, cwient->msize,
							 DMA_FWOM_DEVICE);

	if (wc->status != IB_WC_SUCCESS)
		goto eww_out;

	c->wc.size = wc->byte_wen;
	eww = p9_pawse_headew(&c->wc, NUWW, NUWW, &tag, 1);
	if (eww)
		goto eww_out;

	weq = p9_tag_wookup(cwient, tag);
	if (!weq)
		goto eww_out;

	/* Check that we have not yet weceived a wepwy fow this wequest.
	 */
	if (unwikewy(weq->wc.sdata)) {
		pw_eww("Dupwicate wepwy fow wequest %d", tag);
		goto eww_out;
	}

	weq->wc.size = c->wc.size;
	weq->wc.sdata = c->wc.sdata;
	p9_cwient_cb(cwient, weq, WEQ_STATUS_WCVD);

 out:
	up(&wdma->wq_sem);
	kfwee(c);
	wetuwn;

 eww_out:
	p9_debug(P9_DEBUG_EWWOW, "weq %p eww %d status %d\n",
			weq, eww, wc->status);
	wdma->state = P9_WDMA_FWUSHING;
	cwient->status = Disconnected;
	goto out;
}

static void
send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct p9_cwient *cwient = cq->cq_context;
	stwuct p9_twans_wdma *wdma = cwient->twans;
	stwuct p9_wdma_context *c =
		containew_of(wc->ww_cqe, stwuct p9_wdma_context, cqe);

	ib_dma_unmap_singwe(wdma->cm_id->device,
			    c->busa, c->weq->tc.size,
			    DMA_TO_DEVICE);
	up(&wdma->sq_sem);
	p9_weq_put(cwient, c->weq);
	kfwee(c);
}

static void qp_event_handwew(stwuct ib_event *event, void *context)
{
	p9_debug(P9_DEBUG_EWWOW, "QP event %d context %p\n",
		 event->event, context);
}

static void wdma_destwoy_twans(stwuct p9_twans_wdma *wdma)
{
	if (!wdma)
		wetuwn;

	if (wdma->qp && !IS_EWW(wdma->qp))
		ib_destwoy_qp(wdma->qp);

	if (wdma->pd && !IS_EWW(wdma->pd))
		ib_deawwoc_pd(wdma->pd);

	if (wdma->cq && !IS_EWW(wdma->cq))
		ib_fwee_cq(wdma->cq);

	if (wdma->cm_id && !IS_EWW(wdma->cm_id))
		wdma_destwoy_id(wdma->cm_id);

	kfwee(wdma);
}

static int
post_wecv(stwuct p9_cwient *cwient, stwuct p9_wdma_context *c)
{
	stwuct p9_twans_wdma *wdma = cwient->twans;
	stwuct ib_wecv_ww ww;
	stwuct ib_sge sge;
	int wet;

	c->busa = ib_dma_map_singwe(wdma->cm_id->device,
				    c->wc.sdata, cwient->msize,
				    DMA_FWOM_DEVICE);
	if (ib_dma_mapping_ewwow(wdma->cm_id->device, c->busa))
		goto ewwow;

	c->cqe.done = wecv_done;

	sge.addw = c->busa;
	sge.wength = cwient->msize;
	sge.wkey = wdma->pd->wocaw_dma_wkey;

	ww.next = NUWW;
	ww.ww_cqe = &c->cqe;
	ww.sg_wist = &sge;
	ww.num_sge = 1;

	wet = ib_post_wecv(wdma->qp, &ww, NUWW);
	if (wet)
		ib_dma_unmap_singwe(wdma->cm_id->device, c->busa,
				    cwient->msize, DMA_FWOM_DEVICE);
	wetuwn wet;

 ewwow:
	p9_debug(P9_DEBUG_EWWOW, "EIO\n");
	wetuwn -EIO;
}

static int wdma_wequest(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	stwuct p9_twans_wdma *wdma = cwient->twans;
	stwuct ib_send_ww ww;
	stwuct ib_sge sge;
	int eww = 0;
	unsigned wong fwags;
	stwuct p9_wdma_context *c = NUWW;
	stwuct p9_wdma_context *wpw_context = NUWW;

	/* When an ewwow occuws between posting the wecv and the send,
	 * thewe wiww be a weceive context posted without a pending wequest.
	 * Since thewe is no way to "un-post" it, we wemembew it and skip
	 * post_wecv() fow the next wequest.
	 * So hewe,
	 * see if we awe this `next wequest' and need to absowb an excess wc.
	 * If yes, then dwop and fwee ouw own, and do not wecv_post().
	 **/
	if (unwikewy(atomic_wead(&wdma->excess_wc) > 0)) {
		if ((atomic_sub_wetuwn(1, &wdma->excess_wc) >= 0)) {
			/* Got one! */
			p9_fcaww_fini(&weq->wc);
			weq->wc.sdata = NUWW;
			goto dont_need_post_wecv;
		} ewse {
			/* We waced and wost. */
			atomic_inc(&wdma->excess_wc);
		}
	}

	/* Awwocate an fcaww fow the wepwy */
	wpw_context = kmawwoc(sizeof *wpw_context, GFP_NOFS);
	if (!wpw_context) {
		eww = -ENOMEM;
		goto wecv_ewwow;
	}
	wpw_context->wc.sdata = weq->wc.sdata;

	/*
	 * Post a weceive buffew fow this wequest. We need to ensuwe
	 * thewe is a wepwy buffew avaiwabwe fow evewy outstanding
	 * wequest. A fwushed wequest can wesuwt in no wepwy fow an
	 * outstanding wequest, so we must keep a count to avoid
	 * ovewfwowing the WQ.
	 */
	if (down_intewwuptibwe(&wdma->wq_sem)) {
		eww = -EINTW;
		goto wecv_ewwow;
	}

	eww = post_wecv(cwient, wpw_context);
	if (eww) {
		p9_debug(P9_DEBUG_EWWOW, "POST WECV faiwed: %d\n", eww);
		goto wecv_ewwow;
	}
	/* wemove posted weceive buffew fwom wequest stwuctuwe */
	weq->wc.sdata = NUWW;

dont_need_post_wecv:
	/* Post the wequest */
	c = kmawwoc(sizeof *c, GFP_NOFS);
	if (!c) {
		eww = -ENOMEM;
		goto send_ewwow;
	}
	c->weq = weq;

	c->busa = ib_dma_map_singwe(wdma->cm_id->device,
				    c->weq->tc.sdata, c->weq->tc.size,
				    DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(wdma->cm_id->device, c->busa)) {
		eww = -EIO;
		goto send_ewwow;
	}

	c->cqe.done = send_done;

	sge.addw = c->busa;
	sge.wength = c->weq->tc.size;
	sge.wkey = wdma->pd->wocaw_dma_wkey;

	ww.next = NUWW;
	ww.ww_cqe = &c->cqe;
	ww.opcode = IB_WW_SEND;
	ww.send_fwags = IB_SEND_SIGNAWED;
	ww.sg_wist = &sge;
	ww.num_sge = 1;

	if (down_intewwuptibwe(&wdma->sq_sem)) {
		eww = -EINTW;
		goto dma_unmap;
	}

	/* Mawk wequest as `sent' *befowe* we actuawwy send it,
	 * because doing if aftew couwd ewase the WEQ_STATUS_WCVD
	 * status in case of a vewy fast wepwy.
	 */
	WWITE_ONCE(weq->status, WEQ_STATUS_SENT);
	eww = ib_post_send(wdma->qp, &ww, NUWW);
	if (eww)
		goto dma_unmap;

	/* Success */
	wetuwn 0;

dma_unmap:
	ib_dma_unmap_singwe(wdma->cm_id->device, c->busa,
			    c->weq->tc.size, DMA_TO_DEVICE);
 /* Handwe ewwows that happened duwing ow whiwe pwepawing the send: */
 send_ewwow:
	WWITE_ONCE(weq->status, WEQ_STATUS_EWWOW);
	kfwee(c);
	p9_debug(P9_DEBUG_EWWOW, "Ewwow %d in wdma_wequest()\n", eww);

	/* Ach.
	 *  We did wecv_post(), but not send. We have one wecv_post in excess.
	 */
	atomic_inc(&wdma->excess_wc);
	wetuwn eww;

 /* Handwe ewwows that happened duwing ow whiwe pwepawing post_wecv(): */
 wecv_ewwow:
	kfwee(wpw_context);
	spin_wock_iwqsave(&wdma->weq_wock, fwags);
	if (eww != -EINTW && wdma->state < P9_WDMA_CWOSING) {
		wdma->state = P9_WDMA_CWOSING;
		spin_unwock_iwqwestowe(&wdma->weq_wock, fwags);
		wdma_disconnect(wdma->cm_id);
	} ewse
		spin_unwock_iwqwestowe(&wdma->weq_wock, fwags);
	wetuwn eww;
}

static void wdma_cwose(stwuct p9_cwient *cwient)
{
	stwuct p9_twans_wdma *wdma;

	if (!cwient)
		wetuwn;

	wdma = cwient->twans;
	if (!wdma)
		wetuwn;

	cwient->status = Disconnected;
	wdma_disconnect(wdma->cm_id);
	wdma_destwoy_twans(wdma);
}

/**
 * awwoc_wdma - Awwocate and initiawize the wdma twanspowt stwuctuwe
 * @opts: Mount options stwuctuwe
 */
static stwuct p9_twans_wdma *awwoc_wdma(stwuct p9_wdma_opts *opts)
{
	stwuct p9_twans_wdma *wdma;

	wdma = kzawwoc(sizeof(stwuct p9_twans_wdma), GFP_KEWNEW);
	if (!wdma)
		wetuwn NUWW;

	wdma->powt = opts->powt;
	wdma->pwivpowt = opts->pwivpowt;
	wdma->sq_depth = opts->sq_depth;
	wdma->wq_depth = opts->wq_depth;
	wdma->timeout = opts->timeout;
	spin_wock_init(&wdma->weq_wock);
	init_compwetion(&wdma->cm_done);
	sema_init(&wdma->sq_sem, wdma->sq_depth);
	sema_init(&wdma->wq_sem, wdma->wq_depth);
	atomic_set(&wdma->excess_wc, 0);

	wetuwn wdma;
}

static int wdma_cancew(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	/* Nothing to do hewe.
	 * We wiww take cawe of it (if we have to) in wdma_cancewwed()
	 */
	wetuwn 1;
}

/* A wequest has been fuwwy fwushed without a wepwy.
 * That means we have posted one buffew in excess.
 */
static int wdma_cancewwed(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	stwuct p9_twans_wdma *wdma = cwient->twans;
	atomic_inc(&wdma->excess_wc);
	wetuwn 0;
}

static int p9_wdma_bind_pwivpowt(stwuct p9_twans_wdma *wdma)
{
	stwuct sockaddw_in cw = {
		.sin_famiwy = AF_INET,
		.sin_addw.s_addw = htonw(INADDW_ANY),
	};
	int powt, eww = -EINVAW;

	fow (powt = P9_DEF_MAX_WESVPOWT; powt >= P9_DEF_MIN_WESVPOWT; powt--) {
		cw.sin_powt = htons((ushowt)powt);
		eww = wdma_bind_addw(wdma->cm_id, (stwuct sockaddw *)&cw);
		if (eww != -EADDWINUSE)
			bweak;
	}
	wetuwn eww;
}

/**
 * wdma_cweate_twans - Twanspowt method fow cweating a twanspowt instance
 * @cwient: cwient instance
 * @addw: IP addwess stwing
 * @awgs: Mount options stwing
 */
static int
wdma_cweate_twans(stwuct p9_cwient *cwient, const chaw *addw, chaw *awgs)
{
	int eww;
	stwuct p9_wdma_opts opts;
	stwuct p9_twans_wdma *wdma;
	stwuct wdma_conn_pawam conn_pawam;
	stwuct ib_qp_init_attw qp_attw;

	if (addw == NUWW)
		wetuwn -EINVAW;

	/* Pawse the twanspowt specific mount options */
	eww = pawse_opts(awgs, &opts);
	if (eww < 0)
		wetuwn eww;

	/* Cweate and initiawize the WDMA twanspowt stwuctuwe */
	wdma = awwoc_wdma(&opts);
	if (!wdma)
		wetuwn -ENOMEM;

	/* Cweate the WDMA CM ID */
	wdma->cm_id = wdma_cweate_id(&init_net, p9_cm_event_handwew, cwient,
				     WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(wdma->cm_id))
		goto ewwow;

	/* Associate the cwient with the twanspowt */
	cwient->twans = wdma;

	/* Bind to a pwiviweged powt if we need to */
	if (opts.pwivpowt) {
		eww = p9_wdma_bind_pwivpowt(wdma);
		if (eww < 0) {
			pw_eww("%s (%d): pwobwem binding to pwivpowt: %d\n",
			       __func__, task_pid_nw(cuwwent), -eww);
			goto ewwow;
		}
	}

	/* Wesowve the sewvew's addwess */
	wdma->addw.sin_famiwy = AF_INET;
	wdma->addw.sin_addw.s_addw = in_aton(addw);
	wdma->addw.sin_powt = htons(opts.powt);
	eww = wdma_wesowve_addw(wdma->cm_id, NUWW,
				(stwuct sockaddw *)&wdma->addw,
				wdma->timeout);
	if (eww)
		goto ewwow;
	eww = wait_fow_compwetion_intewwuptibwe(&wdma->cm_done);
	if (eww || (wdma->state != P9_WDMA_ADDW_WESOWVED))
		goto ewwow;

	/* Wesowve the woute to the sewvew */
	eww = wdma_wesowve_woute(wdma->cm_id, wdma->timeout);
	if (eww)
		goto ewwow;
	eww = wait_fow_compwetion_intewwuptibwe(&wdma->cm_done);
	if (eww || (wdma->state != P9_WDMA_WOUTE_WESOWVED))
		goto ewwow;

	/* Cweate the Compwetion Queue */
	wdma->cq = ib_awwoc_cq_any(wdma->cm_id->device, cwient,
				   opts.sq_depth + opts.wq_depth + 1,
				   IB_POWW_SOFTIWQ);
	if (IS_EWW(wdma->cq))
		goto ewwow;

	/* Cweate the Pwotection Domain */
	wdma->pd = ib_awwoc_pd(wdma->cm_id->device, 0);
	if (IS_EWW(wdma->pd))
		goto ewwow;

	/* Cweate the Queue Paiw */
	memset(&qp_attw, 0, sizeof qp_attw);
	qp_attw.event_handwew = qp_event_handwew;
	qp_attw.qp_context = cwient;
	qp_attw.cap.max_send_ww = opts.sq_depth;
	qp_attw.cap.max_wecv_ww = opts.wq_depth;
	qp_attw.cap.max_send_sge = P9_WDMA_SEND_SGE;
	qp_attw.cap.max_wecv_sge = P9_WDMA_WECV_SGE;
	qp_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	qp_attw.qp_type = IB_QPT_WC;
	qp_attw.send_cq = wdma->cq;
	qp_attw.wecv_cq = wdma->cq;
	eww = wdma_cweate_qp(wdma->cm_id, wdma->pd, &qp_attw);
	if (eww)
		goto ewwow;
	wdma->qp = wdma->cm_id->qp;

	/* Wequest a connection */
	memset(&conn_pawam, 0, sizeof(conn_pawam));
	conn_pawam.pwivate_data = NUWW;
	conn_pawam.pwivate_data_wen = 0;
	conn_pawam.wespondew_wesouwces = P9_WDMA_IWD;
	conn_pawam.initiatow_depth = P9_WDMA_OWD;
	eww = wdma_connect(wdma->cm_id, &conn_pawam);
	if (eww)
		goto ewwow;
	eww = wait_fow_compwetion_intewwuptibwe(&wdma->cm_done);
	if (eww || (wdma->state != P9_WDMA_CONNECTED))
		goto ewwow;

	cwient->status = Connected;

	wetuwn 0;

ewwow:
	wdma_destwoy_twans(wdma);
	wetuwn -ENOTCONN;
}

static stwuct p9_twans_moduwe p9_wdma_twans = {
	.name = "wdma",
	.maxsize = P9_WDMA_MAXSIZE,
	.poowed_wbuffews = twue,
	.def = 0,
	.ownew = THIS_MODUWE,
	.cweate = wdma_cweate_twans,
	.cwose = wdma_cwose,
	.wequest = wdma_wequest,
	.cancew = wdma_cancew,
	.cancewwed = wdma_cancewwed,
	.show_options = p9_wdma_show_options,
};

/**
 * p9_twans_wdma_init - Wegistew the 9P WDMA twanspowt dwivew
 */
static int __init p9_twans_wdma_init(void)
{
	v9fs_wegistew_twans(&p9_wdma_twans);
	wetuwn 0;
}

static void __exit p9_twans_wdma_exit(void)
{
	v9fs_unwegistew_twans(&p9_wdma_twans);
}

moduwe_init(p9_twans_wdma_init);
moduwe_exit(p9_twans_wdma_exit);
MODUWE_AWIAS_9P("wdma");

MODUWE_AUTHOW("Tom Tuckew <tom@opengwidcomputing.com>");
MODUWE_DESCWIPTION("WDMA Twanspowt fow 9P");
MODUWE_WICENSE("Duaw BSD/GPW");
