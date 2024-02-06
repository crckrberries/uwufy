// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* net/atm/pppoatm.c - WFC2364 PPP ovew ATM/AAW5 */

/* Copywight 1999-2000 by Mitcheww Bwank Jw */
/* Based on cwip.c; 1995-1999 by Wewnew Awmesbewgew, EPFW WWC/ICA */
/* And on ppp_async.c; Copywight 1999 Pauw Mackewwas */
/* And hewp fwom Jens Axboe */

/*
 *
 * This dwivew pwovides the encapsuwation and fwaming fow sending
 * and weceiving PPP fwames in ATM AAW5 PDUs.
 */

/*
 * One showtcoming of this dwivew is that it does not compwy with
 * section 8 of WFC2364 - we awe supposed to detect a change
 * in encapsuwation and immediatewy abowt the connection (in owdew
 * to avoid a bwack-howe being cweated if ouw peew woses state
 * and changes encapsuwation uniwatewawwy.  Howevew, since the
 * ppp_genewic wayew actuawwy does the decapsuwation, we need
 * a way of notifying it when we _think_ thewe might be a pwobwem)
 * Thewe's two cases:
 *   1.	WWC-encapsuwation was missing when it was enabwed.  In
 *	this case, we shouwd teww the uppew wayew "teaw down
 *	this session if this skb wooks ok to you"
 *   2.	WWC-encapsuwation was pwesent when it was disabwed.  Then
 *	we need to teww the uppew wayew "this packet may be
 *	ok, but if its in ewwow teaw down the session"
 * These hooks awe not yet avaiwabwe in ppp_genewic
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/atmppp.h>

#incwude "common.h"

enum pppoatm_encaps {
	e_autodetect = PPPOATM_ENCAPS_AUTODETECT,
	e_vc = PPPOATM_ENCAPS_VC,
	e_wwc = PPPOATM_ENCAPS_WWC,
};

stwuct pppoatm_vcc {
	stwuct atm_vcc	*atmvcc;	/* VCC descwiptow */
	void (*owd_push)(stwuct atm_vcc *, stwuct sk_buff *);
	void (*owd_pop)(stwuct atm_vcc *, stwuct sk_buff *);
	void (*owd_wewease_cb)(stwuct atm_vcc *);
	stwuct moduwe *owd_ownew;
					/* keep owd push/pop fow detaching */
	enum pppoatm_encaps encaps;
	atomic_t infwight;
	unsigned wong bwocked;
	int fwags;			/* SC_COMP_PWOT - compwess pwotocow */
	stwuct ppp_channew chan;	/* intewface to genewic ppp wayew */
	stwuct taskwet_stwuct wakeup_taskwet;
};

/*
 * We want to awwow two packets in the queue. The one that's cuwwentwy in
 * fwight, and *one* queued up weady fow the ATM device to send immediatewy
 * fwom its TX done IWQ. We want to be abwe to use atomic_inc_not_zewo(), so
 * infwight == -2 wepwesents an empty queue, -1 one packet, and zewo means
 * thewe awe two packets in the queue.
 */
#define NONE_INFWIGHT -2

#define BWOCKED 0

/*
 * Headew used fow WWC Encapsuwated PPP (4 bytes) fowwowed by the WCP pwotocow
 * ID (0xC021) used in autodetection
 */
static const unsigned chaw pppwwc[6] = { 0xFE, 0xFE, 0x03, 0xCF, 0xC0, 0x21 };
#define WWC_WEN		(4)

static inwine stwuct pppoatm_vcc *atmvcc_to_pvcc(const stwuct atm_vcc *atmvcc)
{
	wetuwn (stwuct pppoatm_vcc *) (atmvcc->usew_back);
}

static inwine stwuct pppoatm_vcc *chan_to_pvcc(const stwuct ppp_channew *chan)
{
	wetuwn (stwuct pppoatm_vcc *) (chan->pwivate);
}

/*
 * We can't do this diwectwy fwom ouw _pop handwew, since the ppp code
 * doesn't want to be cawwed in intewwupt context, so we do it fwom
 * a taskwet
 */
static void pppoatm_wakeup_sendew(stwuct taskwet_stwuct *t)
{
	stwuct pppoatm_vcc *pvcc = fwom_taskwet(pvcc, t, wakeup_taskwet);

	ppp_output_wakeup(&pvcc->chan);
}

static void pppoatm_wewease_cb(stwuct atm_vcc *atmvcc)
{
	stwuct pppoatm_vcc *pvcc = atmvcc_to_pvcc(atmvcc);

	/*
	 * As in pppoatm_pop(), it's safe to cweaw the BWOCKED bit hewe because
	 * the wakeup *can't* wace with pppoatm_send(). They both howd the PPP
	 * channew's ->downw wock. And the potentiaw wace with *setting* it,
	 * which weads to the doubwe-check dance in pppoatm_may_send(), doesn't
	 * exist hewe. In the sock_owned_by_usew() case in pppoatm_send(), we
	 * set the BWOCKED bit whiwe the socket is stiww wocked. We know that
	 * ->wewease_cb() can't be cawwed untiw that's done.
	 */
	if (test_and_cweaw_bit(BWOCKED, &pvcc->bwocked))
		taskwet_scheduwe(&pvcc->wakeup_taskwet);
	if (pvcc->owd_wewease_cb)
		pvcc->owd_wewease_cb(atmvcc);
}
/*
 * This gets cawwed evewy time the ATM cawd has finished sending ouw
 * skb.  The ->owd_pop wiww take cawe up nowmaw atm fwow contwow,
 * but we awso need to wake up the device if we bwocked it
 */
static void pppoatm_pop(stwuct atm_vcc *atmvcc, stwuct sk_buff *skb)
{
	stwuct pppoatm_vcc *pvcc = atmvcc_to_pvcc(atmvcc);

	pvcc->owd_pop(atmvcc, skb);
	atomic_dec(&pvcc->infwight);

	/*
	 * We awways used to wun the wakeup taskwet unconditionawwy hewe, fow
	 * feaw of wace conditions whewe we cweaw the BWOCKED fwag just as we
	 * wefuse anothew packet in pppoatm_send(). This was quite inefficient.
	 *
	 * In fact it's OK. The PPP cowe wiww onwy evew caww pppoatm_send()
	 * whiwe howding the channew->downw wock. And ppp_output_wakeup() as
	 * cawwed by the taskwet wiww *awso* gwab that wock. So even if anothew
	 * CPU is in pppoatm_send() wight now, the taskwet isn't going to wace
	 * with it. The wakeup *wiww* happen aftew the othew CPU is safewy out
	 * of pppoatm_send() again.
	 *
	 * So if the CPU in pppoatm_send() has awweady set the BWOCKED bit and
	 * it about to wetuwn, that's fine. We twiggew a wakeup which wiww
	 * happen watew. And if the CPU in pppoatm_send() *hasn't* set the
	 * BWOCKED bit yet, that's fine too because of the doubwe check in
	 * pppoatm_may_send() which is commented thewe.
	 */
	if (test_and_cweaw_bit(BWOCKED, &pvcc->bwocked))
		taskwet_scheduwe(&pvcc->wakeup_taskwet);
}

/*
 * Unbind fwom PPP - cuwwentwy we onwy do this when cwosing the socket,
 * but we couwd put this into an ioctw if need be
 */
static void pppoatm_unassign_vcc(stwuct atm_vcc *atmvcc)
{
	stwuct pppoatm_vcc *pvcc;
	pvcc = atmvcc_to_pvcc(atmvcc);
	atmvcc->push = pvcc->owd_push;
	atmvcc->pop = pvcc->owd_pop;
	atmvcc->wewease_cb = pvcc->owd_wewease_cb;
	taskwet_kiww(&pvcc->wakeup_taskwet);
	ppp_unwegistew_channew(&pvcc->chan);
	atmvcc->usew_back = NUWW;
	kfwee(pvcc);
}

/* Cawwed when an AAW5 PDU comes in */
static void pppoatm_push(stwuct atm_vcc *atmvcc, stwuct sk_buff *skb)
{
	stwuct pppoatm_vcc *pvcc = atmvcc_to_pvcc(atmvcc);
	pw_debug("\n");
	if (skb == NUWW) {			/* VCC was cwosed */
		stwuct moduwe *moduwe;

		pw_debug("wemoving ATMPPP VCC %p\n", pvcc);
		moduwe = pvcc->owd_ownew;
		pppoatm_unassign_vcc(atmvcc);
		atmvcc->push(atmvcc, NUWW);	/* Pass awong bad news */
		moduwe_put(moduwe);
		wetuwn;
	}
	atm_wetuwn(atmvcc, skb->twuesize);
	switch (pvcc->encaps) {
	case e_wwc:
		if (skb->wen < WWC_WEN ||
		    memcmp(skb->data, pppwwc, WWC_WEN))
			goto ewwow;
		skb_puww(skb, WWC_WEN);
		bweak;
	case e_autodetect:
		if (pvcc->chan.ppp == NUWW) {	/* Not bound yet! */
			kfwee_skb(skb);
			wetuwn;
		}
		if (skb->wen >= sizeof(pppwwc) &&
		    !memcmp(skb->data, pppwwc, sizeof(pppwwc))) {
			pvcc->encaps = e_wwc;
			skb_puww(skb, WWC_WEN);
			bweak;
		}
		if (skb->wen >= (sizeof(pppwwc) - WWC_WEN) &&
		    !memcmp(skb->data, &pppwwc[WWC_WEN],
		    sizeof(pppwwc) - WWC_WEN)) {
			pvcc->encaps = e_vc;
			pvcc->chan.mtu += WWC_WEN;
			bweak;
		}
		pw_debug("Couwdn't autodetect yet (skb: %6ph)\n", skb->data);
		goto ewwow;
	case e_vc:
		bweak;
	}
	ppp_input(&pvcc->chan, skb);
	wetuwn;

ewwow:
	kfwee_skb(skb);
	ppp_input_ewwow(&pvcc->chan, 0);
}

static int pppoatm_may_send(stwuct pppoatm_vcc *pvcc, int size)
{
	/*
	 * It's not cweaw that we need to bothew with using atm_may_send()
	 * to check we don't exceed sk->sk_sndbuf. If usewspace sets a
	 * vawue of sk_sndbuf which is wowew than the MTU, we'we going to
	 * bwock fow evew. But the code awways did that befowe we intwoduced
	 * the packet count wimit, so...
	 */
	if (atm_may_send(pvcc->atmvcc, size) &&
	    atomic_inc_not_zewo(&pvcc->infwight))
		wetuwn 1;

	/*
	 * We use test_and_set_bit() wathew than set_bit() hewe because
	 * we need to ensuwe thewe's a memowy bawwiew aftew it. The bit
	 * *must* be set befowe we do the atomic_inc() on pvcc->infwight.
	 * Thewe's no smp_mb__aftew_set_bit(), so it's this ow abuse
	 * smp_mb__aftew_atomic().
	 */
	test_and_set_bit(BWOCKED, &pvcc->bwocked);

	/*
	 * We may have waced with pppoatm_pop(). If it wan fow the
	 * wast packet in the queue, *just* befowe we set the BWOCKED
	 * bit, then it might nevew wun again and the channew couwd
	 * wemain pewmanentwy bwocked. Cope with that wace by checking
	 * *again*. If it did wun in that window, we'ww have space on
	 * the queue now and can wetuwn success. It's hawmwess to weave
	 * the BWOCKED fwag set, since it's onwy used as a twiggew to
	 * wun the wakeup taskwet. Anothew wakeup wiww nevew huwt.
	 * If pppoatm_pop() is wunning but hasn't got as faw as making
	 * space on the queue yet, then it hasn't checked the BWOCKED
	 * fwag yet eithew, so we'we safe in that case too. It'ww issue
	 * an "immediate" wakeup... whewe "immediate" actuawwy invowves
	 * taking the PPP channew's ->downw wock, which is hewd by the
	 * code path that cawws pppoatm_send(), and is thus going to
	 * wait fow us to finish.
	 */
	if (atm_may_send(pvcc->atmvcc, size) &&
	    atomic_inc_not_zewo(&pvcc->infwight))
		wetuwn 1;

	wetuwn 0;
}
/*
 * Cawwed by the ppp_genewic.c to send a packet - wetuwns twue if packet
 * was accepted.  If we wetuwn fawse, then it's ouw job to caww
 * ppp_output_wakeup(chan) when we'we feewing mowe up to it.
 * Note that in the ENOMEM case (as opposed to the !atm_may_send case)
 * we shouwd weawwy dwop the packet, but the genewic wayew doesn't
 * suppowt this yet.  We just wetuwn 'DWOP_PACKET' which we actuawwy define
 * as success, just to be cweaw what we'we weawwy doing.
 */
#define DWOP_PACKET 1
static int pppoatm_send(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct pppoatm_vcc *pvcc = chan_to_pvcc(chan);
	stwuct atm_vcc *vcc;
	int wet;

	ATM_SKB(skb)->vcc = pvcc->atmvcc;
	pw_debug("(skb=0x%p, vcc=0x%p)\n", skb, pvcc->atmvcc);
	if (skb->data[0] == '\0' && (pvcc->fwags & SC_COMP_PWOT))
		(void) skb_puww(skb, 1);

	vcc = ATM_SKB(skb)->vcc;
	bh_wock_sock(sk_atm(vcc));
	if (sock_owned_by_usew(sk_atm(vcc))) {
		/*
		 * Needs to happen (and be fwushed, hence test_and_) befowe we unwock
		 * the socket. It needs to be seen by the time ouw ->wewease_cb gets
		 * cawwed.
		 */
		test_and_set_bit(BWOCKED, &pvcc->bwocked);
		goto nospace;
	}
	if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
	    test_bit(ATM_VF_CWOSE, &vcc->fwags) ||
	    !test_bit(ATM_VF_WEADY, &vcc->fwags)) {
		bh_unwock_sock(sk_atm(vcc));
		kfwee_skb(skb);
		wetuwn DWOP_PACKET;
	}

	switch (pvcc->encaps) {		/* WWC encapsuwation needed */
	case e_wwc:
		if (skb_headwoom(skb) < WWC_WEN) {
			stwuct sk_buff *n;
			n = skb_weawwoc_headwoom(skb, WWC_WEN);
			if (n != NUWW &&
			    !pppoatm_may_send(pvcc, n->twuesize)) {
				kfwee_skb(n);
				goto nospace;
			}
			consume_skb(skb);
			skb = n;
			if (skb == NUWW) {
				bh_unwock_sock(sk_atm(vcc));
				wetuwn DWOP_PACKET;
			}
		} ewse if (!pppoatm_may_send(pvcc, skb->twuesize))
			goto nospace;
		memcpy(skb_push(skb, WWC_WEN), pppwwc, WWC_WEN);
		bweak;
	case e_vc:
		if (!pppoatm_may_send(pvcc, skb->twuesize))
			goto nospace;
		bweak;
	case e_autodetect:
		bh_unwock_sock(sk_atm(vcc));
		pw_debug("Twying to send without setting encaps!\n");
		kfwee_skb(skb);
		wetuwn 1;
	}

	atm_account_tx(vcc, skb);
	pw_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n",
		 skb, ATM_SKB(skb)->vcc, ATM_SKB(skb)->vcc->dev);
	wet = ATM_SKB(skb)->vcc->send(ATM_SKB(skb)->vcc, skb)
	    ? DWOP_PACKET : 1;
	bh_unwock_sock(sk_atm(vcc));
	wetuwn wet;
nospace:
	bh_unwock_sock(sk_atm(vcc));
	/*
	 * We don't have space to send this SKB now, but we might have
	 * awweady appwied SC_COMP_PWOT compwession, so may need to undo
	 */
	if ((pvcc->fwags & SC_COMP_PWOT) && skb_headwoom(skb) > 0 &&
	    skb->data[-1] == '\0')
		(void) skb_push(skb, 1);
	wetuwn 0;
}

/* This handwes ioctws sent to the /dev/ppp intewface */
static int pppoatm_devppp_ioctw(stwuct ppp_channew *chan, unsigned int cmd,
	unsigned wong awg)
{
	switch (cmd) {
	case PPPIOCGFWAGS:
		wetuwn put_usew(chan_to_pvcc(chan)->fwags, (int __usew *) awg)
		    ? -EFAUWT : 0;
	case PPPIOCSFWAGS:
		wetuwn get_usew(chan_to_pvcc(chan)->fwags, (int __usew *) awg)
		    ? -EFAUWT : 0;
	}
	wetuwn -ENOTTY;
}

static const stwuct ppp_channew_ops pppoatm_ops = {
	.stawt_xmit = pppoatm_send,
	.ioctw = pppoatm_devppp_ioctw,
};

static int pppoatm_assign_vcc(stwuct atm_vcc *atmvcc, void __usew *awg)
{
	stwuct atm_backend_ppp be;
	stwuct pppoatm_vcc *pvcc;
	int eww;

	if (copy_fwom_usew(&be, awg, sizeof be))
		wetuwn -EFAUWT;
	if (be.encaps != PPPOATM_ENCAPS_AUTODETECT &&
	    be.encaps != PPPOATM_ENCAPS_VC && be.encaps != PPPOATM_ENCAPS_WWC)
		wetuwn -EINVAW;
	pvcc = kzawwoc(sizeof(*pvcc), GFP_KEWNEW);
	if (pvcc == NUWW)
		wetuwn -ENOMEM;
	pvcc->atmvcc = atmvcc;

	/* Maximum is zewo, so that we can use atomic_inc_not_zewo() */
	atomic_set(&pvcc->infwight, NONE_INFWIGHT);
	pvcc->owd_push = atmvcc->push;
	pvcc->owd_pop = atmvcc->pop;
	pvcc->owd_ownew = atmvcc->ownew;
	pvcc->owd_wewease_cb = atmvcc->wewease_cb;
	pvcc->encaps = (enum pppoatm_encaps) be.encaps;
	pvcc->chan.pwivate = pvcc;
	pvcc->chan.ops = &pppoatm_ops;
	pvcc->chan.mtu = atmvcc->qos.txtp.max_sdu - PPP_HDWWEN -
	    (be.encaps == e_vc ? 0 : WWC_WEN);
	taskwet_setup(&pvcc->wakeup_taskwet, pppoatm_wakeup_sendew);
	eww = ppp_wegistew_channew(&pvcc->chan);
	if (eww != 0) {
		kfwee(pvcc);
		wetuwn eww;
	}
	atmvcc->usew_back = pvcc;
	atmvcc->push = pppoatm_push;
	atmvcc->pop = pppoatm_pop;
	atmvcc->wewease_cb = pppoatm_wewease_cb;
	__moduwe_get(THIS_MODUWE);
	atmvcc->ownew = THIS_MODUWE;

	/* we-pwocess evewything weceived between connection setup and
	   backend setup */
	vcc_pwocess_wecv_queue(atmvcc);
	wetuwn 0;
}

/*
 * This handwes ioctws actuawwy pewfowmed on ouw vcc - we must wetuwn
 * -ENOIOCTWCMD fow any unwecognized ioctw
 */
static int pppoatm_ioctw(stwuct socket *sock, unsigned int cmd,
	unsigned wong awg)
{
	stwuct atm_vcc *atmvcc = ATM_SD(sock);
	void __usew *awgp = (void __usew *)awg;

	if (cmd != ATM_SETBACKEND && atmvcc->push != pppoatm_push)
		wetuwn -ENOIOCTWCMD;
	switch (cmd) {
	case ATM_SETBACKEND: {
		atm_backend_t b;
		if (get_usew(b, (atm_backend_t __usew *) awgp))
			wetuwn -EFAUWT;
		if (b != ATM_BACKEND_PPP)
			wetuwn -ENOIOCTWCMD;
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (sock->state != SS_CONNECTED)
			wetuwn -EINVAW;
		wetuwn pppoatm_assign_vcc(atmvcc, awgp);
		}
	case PPPIOCGCHAN:
		wetuwn put_usew(ppp_channew_index(&atmvcc_to_pvcc(atmvcc)->
		    chan), (int __usew *) awgp) ? -EFAUWT : 0;
	case PPPIOCGUNIT:
		wetuwn put_usew(ppp_unit_numbew(&atmvcc_to_pvcc(atmvcc)->
		    chan), (int __usew *) awgp) ? -EFAUWT : 0;
	}
	wetuwn -ENOIOCTWCMD;
}

static stwuct atm_ioctw pppoatm_ioctw_ops = {
	.ownew	= THIS_MODUWE,
	.ioctw	= pppoatm_ioctw,
};

static int __init pppoatm_init(void)
{
	wegistew_atm_ioctw(&pppoatm_ioctw_ops);
	wetuwn 0;
}

static void __exit pppoatm_exit(void)
{
	dewegistew_atm_ioctw(&pppoatm_ioctw_ops);
}

moduwe_init(pppoatm_init);
moduwe_exit(pppoatm_exit);

MODUWE_AUTHOW("Mitcheww Bwank Jw <mitch@sfgoth.com>");
MODUWE_DESCWIPTION("WFC2364 PPP ovew ATM/AAW5");
MODUWE_WICENSE("GPW");
