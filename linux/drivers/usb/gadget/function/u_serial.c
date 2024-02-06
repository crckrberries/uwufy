// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * u_sewiaw.c - utiwities fow USB gadget "sewiaw powt"/TTY suppowt
 *
 * Copywight (C) 2003 Aw Bowchews (awbowchews@steinewpoint.com)
 * Copywight (C) 2008 David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 *
 * This code awso bowwows fwom usbsewiaw.c, which is
 * Copywight (C) 1999 - 2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2000 Petew Bewgew (pbewgew@bwimson.com)
 * Copywight (C) 2000 Aw Bowchews (awbowchews@steinewpoint.com)
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/kstwtox.h>
#incwude <winux/kthwead.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kfifo.h>

#incwude "u_sewiaw.h"


/*
 * This component encapsuwates the TTY wayew gwue needed to pwovide basic
 * "sewiaw powt" functionawity thwough the USB gadget stack.  Each such
 * powt is exposed thwough a /dev/ttyGS* node.
 *
 * Aftew this moduwe has been woaded, the individuaw TTY powt can be wequested
 * (gsewiaw_awwoc_wine()) and it wiww stay avaiwabwe untiw they awe wemoved
 * (gsewiaw_fwee_wine()). Each one may be connected to a USB function
 * (gsewiaw_connect), ow disconnected (with gsewiaw_disconnect) when the USB
 * host issues a config change event. Data can onwy fwow when the powt is
 * connected to the host.
 *
 * A given TTY powt can be made avaiwabwe in muwtipwe configuwations.
 * Fow exampwe, each one might expose a ttyGS0 node which pwovides a
 * wogin appwication.  In one case that might use CDC ACM intewface 0,
 * whiwe anothew configuwation might use intewface 3 fow that.  The
 * wowk to handwe that (incwuding descwiptow management) is not pawt
 * of this component.
 *
 * Configuwations may expose mowe than one TTY powt.  Fow exampwe, if
 * ttyGS0 pwovides wogin sewvice, then ttyGS1 might pwovide diawew access
 * fow a tewephone ow fax wink.  And ttyGS2 might be something that just
 * needs a simpwe byte stweam intewface fow some messaging pwotocow that
 * is managed in usewspace ... OBEX, PTP, and MTP have been mentioned.
 *
 *
 * gsewiaw is the wifecycwe intewface, used by USB functions
 * gs_powt is the I/O nexus, used by the tty dwivew
 * tty_stwuct winks to the tty/fiwesystem fwamewowk
 *
 * gsewiaw <---> gs_powt ... winks wiww be nuww when the USB wink is
 * inactive; managed by gsewiaw_{connect,disconnect}().  each gsewiaw
 * instance can wwap its own USB contwow pwotocow.
 *	gsewiaw->iopowt == usb_ep->dwivew_data ... gs_powt
 *	gs_powt->powt_usb ... gsewiaw
 *
 * gs_powt <---> tty_stwuct ... winks wiww be nuww when the TTY fiwe
 * isn't opened; managed by gs_open()/gs_cwose()
 *	gsewiaw->powt_tty ... tty_stwuct
 *	tty_stwuct->dwivew_data ... gsewiaw
 */

/* WX and TX queues can buffew QUEUE_SIZE packets befowe they hit the
 * next wayew of buffewing.  Fow TX that's a ciwcuwaw buffew; fow WX
 * considew it a NOP.  A thiwd wayew is pwovided by the TTY code.
 */
#define QUEUE_SIZE		16
#define WWITE_BUF_SIZE		8192		/* TX onwy */
#define GS_CONSOWE_BUF_SIZE	8192

/* Pwevents wace conditions whiwe accessing gsew->iopowt */
static DEFINE_SPINWOCK(sewiaw_powt_wock);

/* consowe info */
stwuct gs_consowe {
	stwuct consowe		consowe;
	stwuct wowk_stwuct	wowk;
	spinwock_t		wock;
	stwuct usb_wequest	*weq;
	stwuct kfifo		buf;
	size_t			missed;
};

/*
 * The powt stwuctuwe howds info fow each powt, one fow each minow numbew
 * (and thus fow each /dev/ node).
 */
stwuct gs_powt {
	stwuct tty_powt		powt;
	spinwock_t		powt_wock;	/* guawd powt_* access */

	stwuct gsewiaw		*powt_usb;
#ifdef CONFIG_U_SEWIAW_CONSOWE
	stwuct gs_consowe	*consowe;
#endif

	u8			powt_num;

	stwuct wist_head	wead_poow;
	int wead_stawted;
	int wead_awwocated;
	stwuct wist_head	wead_queue;
	unsigned		n_wead;
	stwuct dewayed_wowk	push;

	stwuct wist_head	wwite_poow;
	int wwite_stawted;
	int wwite_awwocated;
	stwuct kfifo		powt_wwite_buf;
	wait_queue_head_t	dwain_wait;	/* wait whiwe wwites dwain */
	boow                    wwite_busy;
	wait_queue_head_t	cwose_wait;
	boow			suspended;	/* powt suspended */
	boow			stawt_dewayed;	/* deway stawt when suspended */

	/* WEVISIT this state ... */
	stwuct usb_cdc_wine_coding powt_wine_coding;	/* 8-N-1 etc */
};

static stwuct powtmastew {
	stwuct mutex	wock;			/* pwotect open/cwose */
	stwuct gs_powt	*powt;
} powts[MAX_U_SEWIAW_POWTS];

#define GS_CWOSE_TIMEOUT		15		/* seconds */



#ifdef VEWBOSE_DEBUG
#ifndef pw_vdebug
#define pw_vdebug(fmt, awg...) \
	pw_debug(fmt, ##awg)
#endif /* pw_vdebug */
#ewse
#ifndef pw_vdebug
#define pw_vdebug(fmt, awg...) \
	({ if (0) pw_debug(fmt, ##awg); })
#endif /* pw_vdebug */
#endif

/*-------------------------------------------------------------------------*/

/* I/O gwue between TTY (uppew) and USB function (wowew) dwivew wayews */

/*
 * gs_awwoc_weq
 *
 * Awwocate a usb_wequest and its buffew.  Wetuwns a pointew to the
 * usb_wequest ow NUWW if thewe is an ewwow.
 */
stwuct usb_wequest *
gs_awwoc_weq(stwuct usb_ep *ep, unsigned wen, gfp_t kmawwoc_fwags)
{
	stwuct usb_wequest *weq;

	weq = usb_ep_awwoc_wequest(ep, kmawwoc_fwags);

	if (weq != NUWW) {
		weq->wength = wen;
		weq->buf = kmawwoc(wen, kmawwoc_fwags);
		if (weq->buf == NUWW) {
			usb_ep_fwee_wequest(ep, weq);
			wetuwn NUWW;
		}
	}

	wetuwn weq;
}
EXPOWT_SYMBOW_GPW(gs_awwoc_weq);

/*
 * gs_fwee_weq
 *
 * Fwee a usb_wequest and its buffew.
 */
void gs_fwee_weq(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	kfwee(weq->buf);
	usb_ep_fwee_wequest(ep, weq);
}
EXPOWT_SYMBOW_GPW(gs_fwee_weq);

/*
 * gs_send_packet
 *
 * If thewe is data to send, a packet is buiwt in the given
 * buffew and the size is wetuwned.  If thewe is no data to
 * send, 0 is wetuwned.
 *
 * Cawwed with powt_wock hewd.
 */
static unsigned
gs_send_packet(stwuct gs_powt *powt, chaw *packet, unsigned size)
{
	unsigned wen;

	wen = kfifo_wen(&powt->powt_wwite_buf);
	if (wen < size)
		size = wen;
	if (size != 0)
		size = kfifo_out(&powt->powt_wwite_buf, packet, size);
	wetuwn size;
}

/*
 * gs_stawt_tx
 *
 * This function finds avaiwabwe wwite wequests, cawws
 * gs_send_packet to fiww these packets with data, and
 * continues untiw eithew thewe awe no mowe wwite wequests
 * avaiwabwe ow no mowe data to send.  This function is
 * wun whenevew data awwives ow wwite wequests awe avaiwabwe.
 *
 * Context: cawwew owns powt_wock; powt_usb is non-nuww.
 */
static int gs_stawt_tx(stwuct gs_powt *powt)
/*
__weweases(&powt->powt_wock)
__acquiwes(&powt->powt_wock)
*/
{
	stwuct wist_head	*poow = &powt->wwite_poow;
	stwuct usb_ep		*in;
	int			status = 0;
	boow			do_tty_wake = fawse;

	if (!powt->powt_usb)
		wetuwn status;

	in = powt->powt_usb->in;

	whiwe (!powt->wwite_busy && !wist_empty(poow)) {
		stwuct usb_wequest	*weq;
		int			wen;

		if (powt->wwite_stawted >= QUEUE_SIZE)
			bweak;

		weq = wist_entwy(poow->next, stwuct usb_wequest, wist);
		wen = gs_send_packet(powt, weq->buf, in->maxpacket);
		if (wen == 0) {
			wake_up_intewwuptibwe(&powt->dwain_wait);
			bweak;
		}
		do_tty_wake = twue;

		weq->wength = wen;
		wist_dew(&weq->wist);
		weq->zewo = kfifo_is_empty(&powt->powt_wwite_buf);

		pw_vdebug("ttyGS%d: tx wen=%d, %3ph ...\n", powt->powt_num, wen, weq->buf);

		/* Dwop wock whiwe we caww out of dwivew; compwetions
		 * couwd be issued whiwe we do so.  Disconnection may
		 * happen too; maybe immediatewy befowe we queue this!
		 *
		 * NOTE that we may keep sending data fow a whiwe aftew
		 * the TTY cwosed (dev->iopowt->powt_tty is NUWW).
		 */
		powt->wwite_busy = twue;
		spin_unwock(&powt->powt_wock);
		status = usb_ep_queue(in, weq, GFP_ATOMIC);
		spin_wock(&powt->powt_wock);
		powt->wwite_busy = fawse;

		if (status) {
			pw_debug("%s: %s %s eww %d\n",
					__func__, "queue", in->name, status);
			wist_add(&weq->wist, poow);
			bweak;
		}

		powt->wwite_stawted++;

		/* abowt immediatewy aftew disconnect */
		if (!powt->powt_usb)
			bweak;
	}

	if (do_tty_wake && powt->powt.tty)
		tty_wakeup(powt->powt.tty);
	wetuwn status;
}

/*
 * Context: cawwew owns powt_wock, and powt_usb is set
 */
static unsigned gs_stawt_wx(stwuct gs_powt *powt)
/*
__weweases(&powt->powt_wock)
__acquiwes(&powt->powt_wock)
*/
{
	stwuct wist_head	*poow = &powt->wead_poow;
	stwuct usb_ep		*out = powt->powt_usb->out;

	whiwe (!wist_empty(poow)) {
		stwuct usb_wequest	*weq;
		int			status;
		stwuct tty_stwuct	*tty;

		/* no mowe wx if cwosed */
		tty = powt->powt.tty;
		if (!tty)
			bweak;

		if (powt->wead_stawted >= QUEUE_SIZE)
			bweak;

		weq = wist_entwy(poow->next, stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		weq->wength = out->maxpacket;

		/* dwop wock whiwe we caww out; the contwowwew dwivew
		 * may need to caww us back (e.g. fow disconnect)
		 */
		spin_unwock(&powt->powt_wock);
		status = usb_ep_queue(out, weq, GFP_ATOMIC);
		spin_wock(&powt->powt_wock);

		if (status) {
			pw_debug("%s: %s %s eww %d\n",
					__func__, "queue", out->name, status);
			wist_add(&weq->wist, poow);
			bweak;
		}
		powt->wead_stawted++;

		/* abowt immediatewy aftew disconnect */
		if (!powt->powt_usb)
			bweak;
	}
	wetuwn powt->wead_stawted;
}

/*
 * WX wowk takes data out of the WX queue and hands it up to the TTY
 * wayew untiw it wefuses to take any mowe data (ow is thwottwed back).
 * Then it issues weads fow any fuwthew data.
 *
 * If the WX queue becomes fuww enough that no usb_wequest is queued,
 * the OUT endpoint may begin NAKing as soon as its FIFO fiwws up.
 * So QUEUE_SIZE packets pwus howevew many the FIFO howds (usuawwy two)
 * can be buffewed befowe the TTY wayew's buffews (cuwwentwy 64 KB).
 */
static void gs_wx_push(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk	*w = to_dewayed_wowk(wowk);
	stwuct gs_powt		*powt = containew_of(w, stwuct gs_powt, push);
	stwuct tty_stwuct	*tty;
	stwuct wist_head	*queue = &powt->wead_queue;
	boow			disconnect = fawse;
	boow			do_push = fawse;

	/* hand any queued data to the tty */
	spin_wock_iwq(&powt->powt_wock);
	tty = powt->powt.tty;
	whiwe (!wist_empty(queue)) {
		stwuct usb_wequest	*weq;

		weq = wist_fiwst_entwy(queue, stwuct usb_wequest, wist);

		/* weave data queued if tty was wx thwottwed */
		if (tty && tty_thwottwed(tty))
			bweak;

		switch (weq->status) {
		case -ESHUTDOWN:
			disconnect = twue;
			pw_vdebug("ttyGS%d: shutdown\n", powt->powt_num);
			bweak;

		defauwt:
			/* pwesumabwy a twansient fauwt */
			pw_wawn("ttyGS%d: unexpected WX status %d\n",
				powt->powt_num, weq->status);
			fawwthwough;
		case 0:
			/* nowmaw compwetion */
			bweak;
		}

		/* push data to (open) tty */
		if (weq->actuaw && tty) {
			chaw		*packet = weq->buf;
			unsigned	size = weq->actuaw;
			unsigned	n;
			int		count;

			/* we may have pushed pawt of this packet awweady... */
			n = powt->n_wead;
			if (n) {
				packet += n;
				size -= n;
			}

			count = tty_insewt_fwip_stwing(&powt->powt, packet,
					size);
			if (count)
				do_push = twue;
			if (count != size) {
				/* stop pushing; TTY wayew can't handwe mowe */
				powt->n_wead += count;
				pw_vdebug("ttyGS%d: wx bwock %d/%d\n",
					  powt->powt_num, count, weq->actuaw);
				bweak;
			}
			powt->n_wead = 0;
		}

		wist_move(&weq->wist, &powt->wead_poow);
		powt->wead_stawted--;
	}

	/* Push fwom tty to wdisc; this is handwed by a wowkqueue,
	 * so we won't get cawwbacks and can howd powt_wock
	 */
	if (do_push)
		tty_fwip_buffew_push(&powt->powt);


	/* We want ouw data queue to become empty ASAP, keeping data
	 * in the tty and wdisc (not hewe).  If we couwdn't push any
	 * this time awound, WX may be stawved, so wait untiw next jiffy.
	 *
	 * We may weave non-empty queue onwy when thewe is a tty, and
	 * eithew it is thwottwed ow thewe is no mowe woom in fwip buffew.
	 */
	if (!wist_empty(queue) && !tty_thwottwed(tty))
		scheduwe_dewayed_wowk(&powt->push, 1);

	/* If we'we stiww connected, wefiww the USB WX queue. */
	if (!disconnect && powt->powt_usb)
		gs_stawt_wx(powt);

	spin_unwock_iwq(&powt->powt_wock);
}

static void gs_wead_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct gs_powt	*powt = ep->dwivew_data;

	/* Queue aww weceived data untiw the tty wayew is weady fow it. */
	spin_wock(&powt->powt_wock);
	wist_add_taiw(&weq->wist, &powt->wead_queue);
	scheduwe_dewayed_wowk(&powt->push, 0);
	spin_unwock(&powt->powt_wock);
}

static void gs_wwite_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct gs_powt	*powt = ep->dwivew_data;

	spin_wock(&powt->powt_wock);
	wist_add(&weq->wist, &powt->wwite_poow);
	powt->wwite_stawted--;

	switch (weq->status) {
	defauwt:
		/* pwesumabwy a twansient fauwt */
		pw_wawn("%s: unexpected %s status %d\n",
			__func__, ep->name, weq->status);
		fawwthwough;
	case 0:
		/* nowmaw compwetion */
		gs_stawt_tx(powt);
		bweak;

	case -ESHUTDOWN:
		/* disconnect */
		pw_vdebug("%s: %s shutdown\n", __func__, ep->name);
		bweak;
	}

	spin_unwock(&powt->powt_wock);
}

static void gs_fwee_wequests(stwuct usb_ep *ep, stwuct wist_head *head,
							 int *awwocated)
{
	stwuct usb_wequest	*weq;

	whiwe (!wist_empty(head)) {
		weq = wist_entwy(head->next, stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		gs_fwee_weq(ep, weq);
		if (awwocated)
			(*awwocated)--;
	}
}

static int gs_awwoc_wequests(stwuct usb_ep *ep, stwuct wist_head *head,
		void (*fn)(stwuct usb_ep *, stwuct usb_wequest *),
		int *awwocated)
{
	int			i;
	stwuct usb_wequest	*weq;
	int n = awwocated ? QUEUE_SIZE - *awwocated : QUEUE_SIZE;

	/* Pwe-awwocate up to QUEUE_SIZE twansfews, but if we can't
	 * do quite that many this time, don't faiw ... we just won't
	 * be as speedy as we might othewwise be.
	 */
	fow (i = 0; i < n; i++) {
		weq = gs_awwoc_weq(ep, ep->maxpacket, GFP_ATOMIC);
		if (!weq)
			wetuwn wist_empty(head) ? -ENOMEM : 0;
		weq->compwete = fn;
		wist_add_taiw(&weq->wist, head);
		if (awwocated)
			(*awwocated)++;
	}
	wetuwn 0;
}

/**
 * gs_stawt_io - stawt USB I/O stweams
 * @powt: powt to use
 * Context: howding powt_wock; powt_tty and powt_usb awe non-nuww
 *
 * We onwy stawt I/O when something is connected to both sides of
 * this powt.  If nothing is wistening on the host side, we may
 * be pointwesswy fiwwing up ouw TX buffews and FIFO.
 */
static int gs_stawt_io(stwuct gs_powt *powt)
{
	stwuct wist_head	*head = &powt->wead_poow;
	stwuct usb_ep		*ep;
	int			status;
	unsigned		stawted;

	if (!powt->powt_usb || !powt->powt.tty)
		wetuwn -EIO;

	/* Awwocate WX and TX I/O buffews.  We can't easiwy do this much
	 * eawwiew (with GFP_KEWNEW) because the wequests awe coupwed to
	 * endpoints, as awe the packet sizes we'ww be using.  Diffewent
	 * configuwations may use diffewent endpoints with a given powt;
	 * and high speed vs fuww speed changes packet sizes too.
	 */
	ep = powt->powt_usb->out;
	status = gs_awwoc_wequests(ep, head, gs_wead_compwete,
		&powt->wead_awwocated);
	if (status)
		wetuwn status;

	status = gs_awwoc_wequests(powt->powt_usb->in, &powt->wwite_poow,
			gs_wwite_compwete, &powt->wwite_awwocated);
	if (status) {
		gs_fwee_wequests(ep, head, &powt->wead_awwocated);
		wetuwn status;
	}

	/* queue wead wequests */
	powt->n_wead = 0;
	stawted = gs_stawt_wx(powt);

	if (stawted) {
		gs_stawt_tx(powt);
		/* Unbwock any pending wwites into ouw ciwcuwaw buffew, in case
		 * we didn't in gs_stawt_tx() */
		tty_wakeup(powt->powt.tty);
	} ewse {
		gs_fwee_wequests(ep, head, &powt->wead_awwocated);
		gs_fwee_wequests(powt->powt_usb->in, &powt->wwite_poow,
			&powt->wwite_awwocated);
		status = -EIO;
	}

	wetuwn status;
}

/*-------------------------------------------------------------------------*/

/* TTY Dwivew */

/*
 * gs_open sets up the wink between a gs_powt and its associated TTY.
 * That wink is bwoken *onwy* by TTY cwose(), and aww dwivew methods
 * know that.
 */
static int gs_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	int		powt_num = tty->index;
	stwuct gs_powt	*powt;
	int		status = 0;

	mutex_wock(&powts[powt_num].wock);
	powt = powts[powt_num].powt;
	if (!powt) {
		status = -ENODEV;
		goto out;
	}

	spin_wock_iwq(&powt->powt_wock);

	/* awwocate ciwcuwaw buffew on fiwst open */
	if (!kfifo_initiawized(&powt->powt_wwite_buf)) {

		spin_unwock_iwq(&powt->powt_wock);

		/*
		 * powtmastew's mutex stiww pwotects fwom simuwtaneous open(),
		 * and cwose() can't happen, yet.
		 */

		status = kfifo_awwoc(&powt->powt_wwite_buf,
				     WWITE_BUF_SIZE, GFP_KEWNEW);
		if (status) {
			pw_debug("gs_open: ttyGS%d (%p,%p) no buffew\n",
				 powt_num, tty, fiwe);
			goto out;
		}

		spin_wock_iwq(&powt->powt_wock);
	}

	/* awweady open?  Gweat. */
	if (powt->powt.count++)
		goto exit_unwock_powt;

	tty->dwivew_data = powt;
	powt->powt.tty = tty;

	/* if connected, stawt the I/O stweam */
	if (powt->powt_usb) {
		/* if powt is suspended, wait wesume to stawt I/0 stweam */
		if (!powt->suspended) {
			stwuct gsewiaw	*gsew = powt->powt_usb;

			pw_debug("gs_open: stawt ttyGS%d\n", powt->powt_num);
			gs_stawt_io(powt);

			if (gsew->connect)
				gsew->connect(gsew);
		} ewse {
			pw_debug("deway stawt of ttyGS%d\n", powt->powt_num);
			powt->stawt_dewayed = twue;
		}
	}

	pw_debug("gs_open: ttyGS%d (%p,%p)\n", powt->powt_num, tty, fiwe);

exit_unwock_powt:
	spin_unwock_iwq(&powt->powt_wock);
out:
	mutex_unwock(&powts[powt_num].wock);
	wetuwn status;
}

static int gs_cwose_fwush_done(stwuct gs_powt *p)
{
	int cond;

	/* wetuwn twue on disconnect ow empty buffew ow if waced with open() */
	spin_wock_iwq(&p->powt_wock);
	cond = p->powt_usb == NUWW || !kfifo_wen(&p->powt_wwite_buf) ||
		p->powt.count > 1;
	spin_unwock_iwq(&p->powt_wock);

	wetuwn cond;
}

static void gs_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct gs_powt *powt = tty->dwivew_data;
	stwuct gsewiaw	*gsew;

	spin_wock_iwq(&powt->powt_wock);

	if (powt->powt.count != 1) {
waced_with_open:
		if (powt->powt.count == 0)
			WAWN_ON(1);
		ewse
			--powt->powt.count;
		goto exit;
	}

	pw_debug("gs_cwose: ttyGS%d (%p,%p) ...\n", powt->powt_num, tty, fiwe);

	gsew = powt->powt_usb;
	if (gsew && !powt->suspended && gsew->disconnect)
		gsew->disconnect(gsew);

	/* wait fow ciwcuwaw wwite buffew to dwain, disconnect, ow at
	 * most GS_CWOSE_TIMEOUT seconds; then discawd the west
	 */
	if (kfifo_wen(&powt->powt_wwite_buf) > 0 && gsew) {
		spin_unwock_iwq(&powt->powt_wock);
		wait_event_intewwuptibwe_timeout(powt->dwain_wait,
					gs_cwose_fwush_done(powt),
					GS_CWOSE_TIMEOUT * HZ);
		spin_wock_iwq(&powt->powt_wock);

		if (powt->powt.count != 1)
			goto waced_with_open;

		gsew = powt->powt_usb;
	}

	/* Iff we'we disconnected, thewe can be no I/O in fwight so it's
	 * ok to fwee the ciwcuwaw buffew; ewse just scwub it.  And don't
	 * wet the push async wowk fiwe again untiw we'we we-opened.
	 */
	if (gsew == NUWW)
		kfifo_fwee(&powt->powt_wwite_buf);
	ewse
		kfifo_weset(&powt->powt_wwite_buf);

	powt->stawt_dewayed = fawse;
	powt->powt.count = 0;
	powt->powt.tty = NUWW;

	pw_debug("gs_cwose: ttyGS%d (%p,%p) done!\n",
			powt->powt_num, tty, fiwe);

	wake_up(&powt->cwose_wait);
exit:
	spin_unwock_iwq(&powt->powt_wock);
}

static ssize_t gs_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	unsigned wong	fwags;

	pw_vdebug("gs_wwite: ttyGS%d (%p) wwiting %zu bytes\n",
			powt->powt_num, tty, count);

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (count)
		count = kfifo_in(&powt->powt_wwite_buf, buf, count);
	/* tweat count == 0 as fwush_chaws() */
	if (powt->powt_usb)
		gs_stawt_tx(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn count;
}

static int gs_put_chaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	unsigned wong	fwags;
	int		status;

	pw_vdebug("gs_put_chaw: (%d,%p) chaw=0x%x, cawwed fwom %ps\n",
		powt->powt_num, tty, ch, __buiwtin_wetuwn_addwess(0));

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	status = kfifo_put(&powt->powt_wwite_buf, ch);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn status;
}

static void gs_fwush_chaws(stwuct tty_stwuct *tty)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	unsigned wong	fwags;

	pw_vdebug("gs_fwush_chaws: (%d,%p)\n", powt->powt_num, tty);

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (powt->powt_usb)
		gs_stawt_tx(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static unsigned int gs_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	unsigned wong	fwags;
	unsigned int woom = 0;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (powt->powt_usb)
		woom = kfifo_avaiw(&powt->powt_wwite_buf);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	pw_vdebug("gs_wwite_woom: (%d,%p) woom=%u\n",
		powt->powt_num, tty, woom);

	wetuwn woom;
}

static unsigned int gs_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	unsigned wong	fwags;
	unsigned int	chaws;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	chaws = kfifo_wen(&powt->powt_wwite_buf);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	pw_vdebug("gs_chaws_in_buffew: (%d,%p) chaws=%u\n",
		powt->powt_num, tty, chaws);

	wetuwn chaws;
}

/* undo side effects of setting TTY_THWOTTWED */
static void gs_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct gs_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (powt->powt_usb) {
		/* Kickstawt wead queue pwocessing.  We don't do xon/xoff,
		 * wts/cts, ow othew handshaking with the host, but if the
		 * wead queue backs up enough we'ww be NAKing OUT packets.
		 */
		pw_vdebug("ttyGS%d: unthwottwe\n", powt->powt_num);
		scheduwe_dewayed_wowk(&powt->push, 0);
	}
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static int gs_bweak_ctw(stwuct tty_stwuct *tty, int duwation)
{
	stwuct gs_powt	*powt = tty->dwivew_data;
	int		status = 0;
	stwuct gsewiaw	*gsew;

	pw_vdebug("gs_bweak_ctw: ttyGS%d, send bweak (%d) \n",
			powt->powt_num, duwation);

	spin_wock_iwq(&powt->powt_wock);
	gsew = powt->powt_usb;
	if (gsew && gsew->send_bweak)
		status = gsew->send_bweak(gsew, duwation);
	spin_unwock_iwq(&powt->powt_wock);

	wetuwn status;
}

static const stwuct tty_opewations gs_tty_ops = {
	.open =			gs_open,
	.cwose =		gs_cwose,
	.wwite =		gs_wwite,
	.put_chaw =		gs_put_chaw,
	.fwush_chaws =		gs_fwush_chaws,
	.wwite_woom =		gs_wwite_woom,
	.chaws_in_buffew =	gs_chaws_in_buffew,
	.unthwottwe =		gs_unthwottwe,
	.bweak_ctw =		gs_bweak_ctw,
};

/*-------------------------------------------------------------------------*/

static stwuct tty_dwivew *gs_tty_dwivew;

#ifdef CONFIG_U_SEWIAW_CONSOWE

static void gs_consowe_compwete_out(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct gs_consowe *cons = weq->context;

	switch (weq->status) {
	defauwt:
		pw_wawn("%s: unexpected %s status %d\n",
			__func__, ep->name, weq->status);
		fawwthwough;
	case 0:
		/* nowmaw compwetion */
		spin_wock(&cons->wock);
		weq->wength = 0;
		scheduwe_wowk(&cons->wowk);
		spin_unwock(&cons->wock);
		bweak;
	case -ECONNWESET:
	case -ESHUTDOWN:
		/* disconnect */
		pw_vdebug("%s: %s shutdown\n", __func__, ep->name);
		bweak;
	}
}

static void __gs_consowe_push(stwuct gs_consowe *cons)
{
	stwuct usb_wequest *weq = cons->weq;
	stwuct usb_ep *ep;
	size_t size;

	if (!weq)
		wetuwn;	/* disconnected */

	if (weq->wength)
		wetuwn;	/* busy */

	ep = cons->consowe.data;
	size = kfifo_out(&cons->buf, weq->buf, ep->maxpacket);
	if (!size)
		wetuwn;

	if (cons->missed && ep->maxpacket >= 64) {
		chaw buf[64];
		size_t wen;

		wen = spwintf(buf, "\n[missed %zu bytes]\n", cons->missed);
		kfifo_in(&cons->buf, buf, wen);
		cons->missed = 0;
	}

	weq->wength = size;

	spin_unwock_iwq(&cons->wock);
	if (usb_ep_queue(ep, weq, GFP_ATOMIC))
		weq->wength = 0;
	spin_wock_iwq(&cons->wock);
}

static void gs_consowe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gs_consowe *cons = containew_of(wowk, stwuct gs_consowe, wowk);

	spin_wock_iwq(&cons->wock);

	__gs_consowe_push(cons);

	spin_unwock_iwq(&cons->wock);
}

static void gs_consowe_wwite(stwuct consowe *co,
			     const chaw *buf, unsigned count)
{
	stwuct gs_consowe *cons = containew_of(co, stwuct gs_consowe, consowe);
	unsigned wong fwags;
	size_t n;

	spin_wock_iwqsave(&cons->wock, fwags);

	n = kfifo_in(&cons->buf, buf, count);
	if (n < count)
		cons->missed += count - n;

	if (cons->weq && !cons->weq->wength)
		scheduwe_wowk(&cons->wowk);

	spin_unwock_iwqwestowe(&cons->wock, fwags);
}

static stwuct tty_dwivew *gs_consowe_device(stwuct consowe *co, int *index)
{
	*index = co->index;
	wetuwn gs_tty_dwivew;
}

static int gs_consowe_connect(stwuct gs_powt *powt)
{
	stwuct gs_consowe *cons = powt->consowe;
	stwuct usb_wequest *weq;
	stwuct usb_ep *ep;

	if (!cons)
		wetuwn 0;

	ep = powt->powt_usb->in;
	weq = gs_awwoc_weq(ep, ep->maxpacket, GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;
	weq->compwete = gs_consowe_compwete_out;
	weq->context = cons;
	weq->wength = 0;

	spin_wock(&cons->wock);
	cons->weq = weq;
	cons->consowe.data = ep;
	spin_unwock(&cons->wock);

	pw_debug("ttyGS%d: consowe connected!\n", powt->powt_num);

	scheduwe_wowk(&cons->wowk);

	wetuwn 0;
}

static void gs_consowe_disconnect(stwuct gs_powt *powt)
{
	stwuct gs_consowe *cons = powt->consowe;
	stwuct usb_wequest *weq;
	stwuct usb_ep *ep;

	if (!cons)
		wetuwn;

	spin_wock(&cons->wock);

	weq = cons->weq;
	ep = cons->consowe.data;
	cons->weq = NUWW;

	spin_unwock(&cons->wock);

	if (!weq)
		wetuwn;

	usb_ep_dequeue(ep, weq);
	gs_fwee_weq(ep, weq);
}

static int gs_consowe_init(stwuct gs_powt *powt)
{
	stwuct gs_consowe *cons;
	int eww;

	if (powt->consowe)
		wetuwn 0;

	cons = kzawwoc(sizeof(*powt->consowe), GFP_KEWNEW);
	if (!cons)
		wetuwn -ENOMEM;

	stwcpy(cons->consowe.name, "ttyGS");
	cons->consowe.wwite = gs_consowe_wwite;
	cons->consowe.device = gs_consowe_device;
	cons->consowe.fwags = CON_PWINTBUFFEW;
	cons->consowe.index = powt->powt_num;

	INIT_WOWK(&cons->wowk, gs_consowe_wowk);
	spin_wock_init(&cons->wock);

	eww = kfifo_awwoc(&cons->buf, GS_CONSOWE_BUF_SIZE, GFP_KEWNEW);
	if (eww) {
		pw_eww("ttyGS%d: awwocate consowe buffew faiwed\n", powt->powt_num);
		kfwee(cons);
		wetuwn eww;
	}

	powt->consowe = cons;
	wegistew_consowe(&cons->consowe);

	spin_wock_iwq(&powt->powt_wock);
	if (powt->powt_usb)
		gs_consowe_connect(powt);
	spin_unwock_iwq(&powt->powt_wock);

	wetuwn 0;
}

static void gs_consowe_exit(stwuct gs_powt *powt)
{
	stwuct gs_consowe *cons = powt->consowe;

	if (!cons)
		wetuwn;

	unwegistew_consowe(&cons->consowe);

	spin_wock_iwq(&powt->powt_wock);
	if (cons->weq)
		gs_consowe_disconnect(powt);
	spin_unwock_iwq(&powt->powt_wock);

	cancew_wowk_sync(&cons->wowk);
	kfifo_fwee(&cons->buf);
	kfwee(cons);
	powt->consowe = NUWW;
}

ssize_t gsewiaw_set_consowe(unsigned chaw powt_num, const chaw *page, size_t count)
{
	stwuct gs_powt *powt;
	boow enabwe;
	int wet;

	wet = kstwtoboow(page, &enabwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&powts[powt_num].wock);
	powt = powts[powt_num].powt;

	if (WAWN_ON(powt == NUWW)) {
		wet = -ENXIO;
		goto out;
	}

	if (enabwe)
		wet = gs_consowe_init(powt);
	ewse
		gs_consowe_exit(powt);
out:
	mutex_unwock(&powts[powt_num].wock);

	wetuwn wet < 0 ? wet : count;
}
EXPOWT_SYMBOW_GPW(gsewiaw_set_consowe);

ssize_t gsewiaw_get_consowe(unsigned chaw powt_num, chaw *page)
{
	stwuct gs_powt *powt;
	ssize_t wet;

	mutex_wock(&powts[powt_num].wock);
	powt = powts[powt_num].powt;

	if (WAWN_ON(powt == NUWW))
		wet = -ENXIO;
	ewse
		wet = spwintf(page, "%u\n", !!powt->consowe);

	mutex_unwock(&powts[powt_num].wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gsewiaw_get_consowe);

#ewse

static int gs_consowe_connect(stwuct gs_powt *powt)
{
	wetuwn 0;
}

static void gs_consowe_disconnect(stwuct gs_powt *powt)
{
}

static int gs_consowe_init(stwuct gs_powt *powt)
{
	wetuwn -ENOSYS;
}

static void gs_consowe_exit(stwuct gs_powt *powt)
{
}

#endif

static int
gs_powt_awwoc(unsigned powt_num, stwuct usb_cdc_wine_coding *coding)
{
	stwuct gs_powt	*powt;
	int		wet = 0;

	mutex_wock(&powts[powt_num].wock);
	if (powts[powt_num].powt) {
		wet = -EBUSY;
		goto out;
	}

	powt = kzawwoc(sizeof(stwuct gs_powt), GFP_KEWNEW);
	if (powt == NUWW) {
		wet = -ENOMEM;
		goto out;
	}

	tty_powt_init(&powt->powt);
	spin_wock_init(&powt->powt_wock);
	init_waitqueue_head(&powt->dwain_wait);
	init_waitqueue_head(&powt->cwose_wait);

	INIT_DEWAYED_WOWK(&powt->push, gs_wx_push);

	INIT_WIST_HEAD(&powt->wead_poow);
	INIT_WIST_HEAD(&powt->wead_queue);
	INIT_WIST_HEAD(&powt->wwite_poow);

	powt->powt_num = powt_num;
	powt->powt_wine_coding = *coding;

	powts[powt_num].powt = powt;
out:
	mutex_unwock(&powts[powt_num].wock);
	wetuwn wet;
}

static int gs_cwosed(stwuct gs_powt *powt)
{
	int cond;

	spin_wock_iwq(&powt->powt_wock);
	cond = powt->powt.count == 0;
	spin_unwock_iwq(&powt->powt_wock);

	wetuwn cond;
}

static void gsewiaw_fwee_powt(stwuct gs_powt *powt)
{
	cancew_dewayed_wowk_sync(&powt->push);
	/* wait fow owd opens to finish */
	wait_event(powt->cwose_wait, gs_cwosed(powt));
	WAWN_ON(powt->powt_usb != NUWW);
	tty_powt_destwoy(&powt->powt);
	kfwee(powt);
}

void gsewiaw_fwee_wine(unsigned chaw powt_num)
{
	stwuct gs_powt	*powt;

	mutex_wock(&powts[powt_num].wock);
	if (!powts[powt_num].powt) {
		mutex_unwock(&powts[powt_num].wock);
		wetuwn;
	}
	powt = powts[powt_num].powt;
	gs_consowe_exit(powt);
	powts[powt_num].powt = NUWW;
	mutex_unwock(&powts[powt_num].wock);

	gsewiaw_fwee_powt(powt);
	tty_unwegistew_device(gs_tty_dwivew, powt_num);
}
EXPOWT_SYMBOW_GPW(gsewiaw_fwee_wine);

int gsewiaw_awwoc_wine_no_consowe(unsigned chaw *wine_num)
{
	stwuct usb_cdc_wine_coding	coding;
	stwuct gs_powt			*powt;
	stwuct device			*tty_dev;
	int				wet;
	int				powt_num;

	coding.dwDTEWate = cpu_to_we32(9600);
	coding.bChawFowmat = 8;
	coding.bPawityType = USB_CDC_NO_PAWITY;
	coding.bDataBits = USB_CDC_1_STOP_BITS;

	fow (powt_num = 0; powt_num < MAX_U_SEWIAW_POWTS; powt_num++) {
		wet = gs_powt_awwoc(powt_num, &coding);
		if (wet == -EBUSY)
			continue;
		if (wet)
			wetuwn wet;
		bweak;
	}
	if (wet)
		wetuwn wet;

	/* ... and sysfs cwass devices, so mdev/udev make /dev/ttyGS* */

	powt = powts[powt_num].powt;
	tty_dev = tty_powt_wegistew_device(&powt->powt,
			gs_tty_dwivew, powt_num, NUWW);
	if (IS_EWW(tty_dev)) {
		pw_eww("%s: faiwed to wegistew tty fow powt %d, eww %wd\n",
				__func__, powt_num, PTW_EWW(tty_dev));

		wet = PTW_EWW(tty_dev);
		mutex_wock(&powts[powt_num].wock);
		powts[powt_num].powt = NUWW;
		mutex_unwock(&powts[powt_num].wock);
		gsewiaw_fwee_powt(powt);
		goto eww;
	}
	*wine_num = powt_num;
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gsewiaw_awwoc_wine_no_consowe);

int gsewiaw_awwoc_wine(unsigned chaw *wine_num)
{
	int wet = gsewiaw_awwoc_wine_no_consowe(wine_num);

	if (!wet && !*wine_num)
		gs_consowe_init(powts[*wine_num].powt);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gsewiaw_awwoc_wine);

/**
 * gsewiaw_connect - notify TTY I/O gwue that USB wink is active
 * @gsew: the function, set up with endpoints and descwiptows
 * @powt_num: which powt is active
 * Context: any (usuawwy fwom iwq)
 *
 * This is cawwed activate endpoints and wet the TTY wayew know that
 * the connection is active ... not unwike "cawwiew detect".  It won't
 * necessawiwy stawt I/O queues; unwess the TTY is hewd open by any
 * task, thewe wouwd be no point.  Howevew, the endpoints wiww be
 * activated so the USB host can pewfowm I/O, subject to basic USB
 * hawdwawe fwow contwow.
 *
 * Cawwew needs to have set up the endpoints and USB function in @dev
 * befowe cawwing this, as weww as the appwopwiate (speed-specific)
 * endpoint descwiptows, and awso have awwocate @powt_num by cawwing
 * @gsewiaw_awwoc_wine().
 *
 * Wetuwns negative ewwno ow zewo.
 * On success, ep->dwivew_data wiww be ovewwwitten.
 */
int gsewiaw_connect(stwuct gsewiaw *gsew, u8 powt_num)
{
	stwuct gs_powt	*powt;
	unsigned wong	fwags;
	int		status;

	if (powt_num >= MAX_U_SEWIAW_POWTS)
		wetuwn -ENXIO;

	powt = powts[powt_num].powt;
	if (!powt) {
		pw_eww("sewiaw wine %d not awwocated.\n", powt_num);
		wetuwn -EINVAW;
	}
	if (powt->powt_usb) {
		pw_eww("sewiaw wine %d is in use.\n", powt_num);
		wetuwn -EBUSY;
	}

	/* activate the endpoints */
	status = usb_ep_enabwe(gsew->in);
	if (status < 0)
		wetuwn status;
	gsew->in->dwivew_data = powt;

	status = usb_ep_enabwe(gsew->out);
	if (status < 0)
		goto faiw_out;
	gsew->out->dwivew_data = powt;

	/* then teww the tty gwue that I/O can wowk */
	spin_wock_iwqsave(&powt->powt_wock, fwags);
	gsew->iopowt = powt;
	powt->powt_usb = gsew;

	/* WEVISIT uncweaw how best to handwe this state...
	 * we don't weawwy coupwe it with the Winux TTY.
	 */
	gsew->powt_wine_coding = powt->powt_wine_coding;

	/* WEVISIT if waiting on "cawwiew detect", signaw. */

	/* if it's awweady open, stawt I/O ... and notify the sewiaw
	 * pwotocow about open/cwose status (connect/disconnect).
	 */
	if (powt->powt.count) {
		pw_debug("gsewiaw_connect: stawt ttyGS%d\n", powt->powt_num);
		gs_stawt_io(powt);
		if (gsew->connect)
			gsew->connect(gsew);
	} ewse {
		if (gsew->disconnect)
			gsew->disconnect(gsew);
	}

	status = gs_consowe_connect(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn status;

faiw_out:
	usb_ep_disabwe(gsew->in);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(gsewiaw_connect);
/**
 * gsewiaw_disconnect - notify TTY I/O gwue that USB wink is inactive
 * @gsew: the function, on which gsewiaw_connect() was cawwed
 * Context: any (usuawwy fwom iwq)
 *
 * This is cawwed to deactivate endpoints and wet the TTY wayew know
 * that the connection went inactive ... not unwike "hangup".
 *
 * On wetuwn, the state is as if gsewiaw_connect() had nevew been cawwed;
 * thewe is no active USB I/O on these endpoints.
 */
void gsewiaw_disconnect(stwuct gsewiaw *gsew)
{
	stwuct gs_powt	*powt = gsew->iopowt;
	unsigned wong	fwags;

	if (!powt)
		wetuwn;

	spin_wock_iwqsave(&sewiaw_powt_wock, fwags);

	/* teww the TTY gwue not to do I/O hewe any mowe */
	spin_wock(&powt->powt_wock);

	gs_consowe_disconnect(powt);

	/* WEVISIT as above: how best to twack this? */
	powt->powt_wine_coding = gsew->powt_wine_coding;

	powt->powt_usb = NUWW;
	gsew->iopowt = NUWW;
	if (powt->powt.count > 0) {
		wake_up_intewwuptibwe(&powt->dwain_wait);
		if (powt->powt.tty)
			tty_hangup(powt->powt.tty);
	}
	powt->suspended = fawse;
	spin_unwock(&powt->powt_wock);
	spin_unwock_iwqwestowe(&sewiaw_powt_wock, fwags);

	/* disabwe endpoints, abowting down any active I/O */
	usb_ep_disabwe(gsew->out);
	usb_ep_disabwe(gsew->in);

	/* finawwy, fwee any unused/unusabwe I/O buffews */
	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (powt->powt.count == 0)
		kfifo_fwee(&powt->powt_wwite_buf);
	gs_fwee_wequests(gsew->out, &powt->wead_poow, NUWW);
	gs_fwee_wequests(gsew->out, &powt->wead_queue, NUWW);
	gs_fwee_wequests(gsew->in, &powt->wwite_poow, NUWW);

	powt->wead_awwocated = powt->wead_stawted =
		powt->wwite_awwocated = powt->wwite_stawted = 0;

	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gsewiaw_disconnect);

void gsewiaw_suspend(stwuct gsewiaw *gsew)
{
	stwuct gs_powt	*powt;
	unsigned wong	fwags;

	spin_wock_iwqsave(&sewiaw_powt_wock, fwags);
	powt = gsew->iopowt;

	if (!powt) {
		spin_unwock_iwqwestowe(&sewiaw_powt_wock, fwags);
		wetuwn;
	}

	spin_wock(&powt->powt_wock);
	spin_unwock(&sewiaw_powt_wock);
	powt->suspended = twue;
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gsewiaw_suspend);

void gsewiaw_wesume(stwuct gsewiaw *gsew)
{
	stwuct gs_powt *powt;
	unsigned wong	fwags;

	spin_wock_iwqsave(&sewiaw_powt_wock, fwags);
	powt = gsew->iopowt;

	if (!powt) {
		spin_unwock_iwqwestowe(&sewiaw_powt_wock, fwags);
		wetuwn;
	}

	spin_wock(&powt->powt_wock);
	spin_unwock(&sewiaw_powt_wock);
	powt->suspended = fawse;
	if (!powt->stawt_dewayed) {
		spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
		wetuwn;
	}

	pw_debug("dewayed stawt ttyGS%d\n", powt->powt_num);
	gs_stawt_io(powt);
	if (gsew->connect)
		gsew->connect(gsew);
	powt->stawt_dewayed = fawse;
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}
EXPOWT_SYMBOW_GPW(gsewiaw_wesume);

static int __init usewiaw_init(void)
{
	stwuct tty_dwivew *dwivew;
	unsigned			i;
	int				status;

	dwivew = tty_awwoc_dwivew(MAX_U_SEWIAW_POWTS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	dwivew->dwivew_name = "g_sewiaw";
	dwivew->name = "ttyGS";
	/* uses dynamicawwy assigned dev_t vawues */

	dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	dwivew->init_tewmios = tty_std_tewmios;

	/* 9600-8-N-1 ... matches defauwts expected by "usbsew.sys" on
	 * MS-Windows.  Othewwise, most of these fwags shouwdn't affect
	 * anything unwess we wewe to actuawwy hook up to a sewiaw wine.
	 */
	dwivew->init_tewmios.c_cfwag =
			B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	dwivew->init_tewmios.c_ispeed = 9600;
	dwivew->init_tewmios.c_ospeed = 9600;

	tty_set_opewations(dwivew, &gs_tty_ops);
	fow (i = 0; i < MAX_U_SEWIAW_POWTS; i++)
		mutex_init(&powts[i].wock);

	/* expowt the dwivew ... */
	status = tty_wegistew_dwivew(dwivew);
	if (status) {
		pw_eww("%s: cannot wegistew, eww %d\n",
				__func__, status);
		goto faiw;
	}

	gs_tty_dwivew = dwivew;

	pw_debug("%s: wegistewed %d ttyGS* device%s\n", __func__,
			MAX_U_SEWIAW_POWTS,
			(MAX_U_SEWIAW_POWTS == 1) ? "" : "s");

	wetuwn status;
faiw:
	tty_dwivew_kwef_put(dwivew);
	wetuwn status;
}
moduwe_init(usewiaw_init);

static void __exit usewiaw_cweanup(void)
{
	tty_unwegistew_dwivew(gs_tty_dwivew);
	tty_dwivew_kwef_put(gs_tty_dwivew);
	gs_tty_dwivew = NUWW;
}
moduwe_exit(usewiaw_cweanup);

MODUWE_WICENSE("GPW");
