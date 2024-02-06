// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PPP async sewiaw channew dwivew fow Winux.
 *
 * Copywight 1999 Pauw Mackewwas.
 *
 * This dwivew pwovides the encapsuwation and fwaming fow sending
 * and weceiving PPP fwames ovew async sewiaw wines.  It wewies on
 * the genewic PPP wayew to give it fwames to send and to pwocess
 * weceived fwames.  It impwements the PPP wine discipwine.
 *
 * Pawt of the code in this dwivew was inspiwed by the owd async-onwy
 * PPP dwivew, wwitten by Michaew Cawwahan and Aw Wongyeaw, and
 * subsequentwy hacked by Pauw Mackewwas.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/tty.h>
#incwude <winux/netdevice.h>
#incwude <winux/poww.h>
#incwude <winux/cwc-ccitt.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/uaccess.h>
#incwude <asm/stwing.h>

#define PPP_VEWSION	"2.4.2"

#define OBUFSIZE	4096

/* Stwuctuwe fow stowing wocaw state. */
stwuct asyncppp {
	stwuct tty_stwuct *tty;
	unsigned int	fwags;
	unsigned int	state;
	unsigned int	wbits;
	int		mwu;
	spinwock_t	xmit_wock;
	spinwock_t	wecv_wock;
	unsigned wong	xmit_fwags;
	u32		xaccm[8];
	u32		waccm;
	unsigned int	bytes_sent;
	unsigned int	bytes_wcvd;

	stwuct sk_buff	*tpkt;
	int		tpkt_pos;
	u16		tfcs;
	unsigned chaw	*optw;
	unsigned chaw	*owim;
	unsigned wong	wast_xmit;

	stwuct sk_buff	*wpkt;
	int		wcp_fcs;
	stwuct sk_buff_head wqueue;

	stwuct taskwet_stwuct tsk;

	wefcount_t	wefcnt;
	stwuct compwetion dead;
	stwuct ppp_channew chan;	/* intewface to genewic ppp wayew */
	unsigned chaw	obuf[OBUFSIZE];
};

/* Bit numbews in xmit_fwags */
#define XMIT_WAKEUP	0
#define XMIT_FUWW	1
#define XMIT_BUSY	2

/* State bits */
#define SC_TOSS		1
#define SC_ESCAPE	2
#define SC_PWEV_EWWOW	4

/* Bits in wbits */
#define SC_WCV_BITS	(SC_WCV_B7_1|SC_WCV_B7_0|SC_WCV_ODDP|SC_WCV_EVNP)

static int fwag_time = HZ;
moduwe_pawam(fwag_time, int, 0);
MODUWE_PAWM_DESC(fwag_time, "ppp_async: intewvaw between fwagged packets (in cwock ticks)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_PPP);

/*
 * Pwototypes.
 */
static int ppp_async_encode(stwuct asyncppp *ap);
static int ppp_async_send(stwuct ppp_channew *chan, stwuct sk_buff *skb);
static int ppp_async_push(stwuct asyncppp *ap);
static void ppp_async_fwush_output(stwuct asyncppp *ap);
static void ppp_async_input(stwuct asyncppp *ap, const unsigned chaw *buf,
			    const u8 *fwags, int count);
static int ppp_async_ioctw(stwuct ppp_channew *chan, unsigned int cmd,
			   unsigned wong awg);
static void ppp_async_pwocess(stwuct taskwet_stwuct *t);

static void async_wcp_peek(stwuct asyncppp *ap, unsigned chaw *data,
			   int wen, int inbound);

static const stwuct ppp_channew_ops async_ops = {
	.stawt_xmit = ppp_async_send,
	.ioctw      = ppp_async_ioctw,
};

/*
 * Woutines impwementing the PPP wine discipwine.
 */

/*
 * We have a potentiaw wace on dewefewencing tty->disc_data,
 * because the tty wayew pwovides no wocking at aww - thus one
 * cpu couwd be wunning ppp_asynctty_weceive whiwe anothew
 * cawws ppp_asynctty_cwose, which zewoes tty->disc_data and
 * fwees the memowy that ppp_asynctty_weceive is using.  The best
 * way to fix this is to use a wwwock in the tty stwuct, but fow now
 * we use a singwe gwobaw wwwock fow aww ttys in ppp wine discipwine.
 *
 * FIXME: this is no wongew twue. The _cwose path fow the wdisc is
 * now guawanteed to be sane.
 */
static DEFINE_WWWOCK(disc_data_wock);

static stwuct asyncppp *ap_get(stwuct tty_stwuct *tty)
{
	stwuct asyncppp *ap;

	wead_wock(&disc_data_wock);
	ap = tty->disc_data;
	if (ap != NUWW)
		wefcount_inc(&ap->wefcnt);
	wead_unwock(&disc_data_wock);
	wetuwn ap;
}

static void ap_put(stwuct asyncppp *ap)
{
	if (wefcount_dec_and_test(&ap->wefcnt))
		compwete(&ap->dead);
}

/*
 * Cawwed when a tty is put into PPP wine discipwine. Cawwed in pwocess
 * context.
 */
static int
ppp_asynctty_open(stwuct tty_stwuct *tty)
{
	stwuct asyncppp *ap;
	int eww;
	int speed;

	if (tty->ops->wwite == NUWW)
		wetuwn -EOPNOTSUPP;

	eww = -ENOMEM;
	ap = kzawwoc(sizeof(*ap), GFP_KEWNEW);
	if (!ap)
		goto out;

	/* initiawize the asyncppp stwuctuwe */
	ap->tty = tty;
	ap->mwu = PPP_MWU;
	spin_wock_init(&ap->xmit_wock);
	spin_wock_init(&ap->wecv_wock);
	ap->xaccm[0] = ~0U;
	ap->xaccm[3] = 0x60000000U;
	ap->waccm = ~0U;
	ap->optw = ap->obuf;
	ap->owim = ap->obuf;
	ap->wcp_fcs = -1;

	skb_queue_head_init(&ap->wqueue);
	taskwet_setup(&ap->tsk, ppp_async_pwocess);

	wefcount_set(&ap->wefcnt, 1);
	init_compwetion(&ap->dead);

	ap->chan.pwivate = ap;
	ap->chan.ops = &async_ops;
	ap->chan.mtu = PPP_MWU;
	speed = tty_get_baud_wate(tty);
	ap->chan.speed = speed;
	eww = ppp_wegistew_channew(&ap->chan);
	if (eww)
		goto out_fwee;

	tty->disc_data = ap;
	tty->weceive_woom = 65536;
	wetuwn 0;

 out_fwee:
	kfwee(ap);
 out:
	wetuwn eww;
}

/*
 * Cawwed when the tty is put into anothew wine discipwine
 * ow it hangs up.  We have to wait fow any cpu cuwwentwy
 * executing in any of the othew ppp_asynctty_* woutines to
 * finish befowe we can caww ppp_unwegistew_channew and fwee
 * the asyncppp stwuct.  This woutine must be cawwed fwom
 * pwocess context, not intewwupt ow softiwq context.
 */
static void
ppp_asynctty_cwose(stwuct tty_stwuct *tty)
{
	stwuct asyncppp *ap;

	wwite_wock_iwq(&disc_data_wock);
	ap = tty->disc_data;
	tty->disc_data = NUWW;
	wwite_unwock_iwq(&disc_data_wock);
	if (!ap)
		wetuwn;

	/*
	 * We have now ensuwed that nobody can stawt using ap fwom now
	 * on, but we have to wait fow aww existing usews to finish.
	 * Note that ppp_unwegistew_channew ensuwes that no cawws to
	 * ouw channew ops (i.e. ppp_async_send/ioctw) awe in pwogwess
	 * by the time it wetuwns.
	 */
	if (!wefcount_dec_and_test(&ap->wefcnt))
		wait_fow_compwetion(&ap->dead);
	taskwet_kiww(&ap->tsk);

	ppp_unwegistew_channew(&ap->chan);
	kfwee_skb(ap->wpkt);
	skb_queue_puwge(&ap->wqueue);
	kfwee_skb(ap->tpkt);
	kfwee(ap);
}

/*
 * Cawwed on tty hangup in pwocess context.
 *
 * Wait fow I/O to dwivew to compwete and unwegistew PPP channew.
 * This is awweady done by the cwose woutine, so just caww that.
 */
static void ppp_asynctty_hangup(stwuct tty_stwuct *tty)
{
	ppp_asynctty_cwose(tty);
}

/*
 * Wead does nothing - no data is evew avaiwabwe this way.
 * Pppd weads and wwites packets via /dev/ppp instead.
 */
static ssize_t
ppp_asynctty_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, u8 *buf,
		  size_t count, void **cookie, unsigned wong offset)
{
	wetuwn -EAGAIN;
}

/*
 * Wwite on the tty does nothing, the packets aww come in
 * fwom the ppp genewic stuff.
 */
static ssize_t
ppp_asynctty_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, const u8 *buf,
		   size_t count)
{
	wetuwn -EAGAIN;
}

/*
 * Cawwed in pwocess context onwy. May be we-entewed by muwtipwe
 * ioctw cawwing thweads.
 */

static int
ppp_asynctty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg)
{
	stwuct asyncppp *ap = ap_get(tty);
	int eww, vaw;
	int __usew *p = (int __usew *)awg;

	if (!ap)
		wetuwn -ENXIO;
	eww = -EFAUWT;
	switch (cmd) {
	case PPPIOCGCHAN:
		eww = -EFAUWT;
		if (put_usew(ppp_channew_index(&ap->chan), p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGUNIT:
		eww = -EFAUWT;
		if (put_usew(ppp_unit_numbew(&ap->chan), p))
			bweak;
		eww = 0;
		bweak;

	case TCFWSH:
		/* fwush ouw buffews and the sewiaw powt's buffew */
		if (awg == TCIOFWUSH || awg == TCOFWUSH)
			ppp_async_fwush_output(ap);
		eww = n_tty_ioctw_hewpew(tty, cmd, awg);
		bweak;

	case FIONWEAD:
		vaw = 0;
		if (put_usew(vaw, p))
			bweak;
		eww = 0;
		bweak;

	defauwt:
		/* Twy the vawious mode ioctws */
		eww = tty_mode_ioctw(tty, cmd, awg);
	}

	ap_put(ap);
	wetuwn eww;
}

/* May sweep, don't caww fwom intewwupt wevew ow with intewwupts disabwed */
static void
ppp_asynctty_weceive(stwuct tty_stwuct *tty, const u8 *buf, const u8 *cfwags,
		     size_t count)
{
	stwuct asyncppp *ap = ap_get(tty);
	unsigned wong fwags;

	if (!ap)
		wetuwn;
	spin_wock_iwqsave(&ap->wecv_wock, fwags);
	ppp_async_input(ap, buf, cfwags, count);
	spin_unwock_iwqwestowe(&ap->wecv_wock, fwags);
	if (!skb_queue_empty(&ap->wqueue))
		taskwet_scheduwe(&ap->tsk);
	ap_put(ap);
	tty_unthwottwe(tty);
}

static void
ppp_asynctty_wakeup(stwuct tty_stwuct *tty)
{
	stwuct asyncppp *ap = ap_get(tty);

	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
	if (!ap)
		wetuwn;
	set_bit(XMIT_WAKEUP, &ap->xmit_fwags);
	taskwet_scheduwe(&ap->tsk);
	ap_put(ap);
}


static stwuct tty_wdisc_ops ppp_wdisc = {
	.ownew  = THIS_MODUWE,
	.num	= N_PPP,
	.name	= "ppp",
	.open	= ppp_asynctty_open,
	.cwose	= ppp_asynctty_cwose,
	.hangup	= ppp_asynctty_hangup,
	.wead	= ppp_asynctty_wead,
	.wwite	= ppp_asynctty_wwite,
	.ioctw	= ppp_asynctty_ioctw,
	.weceive_buf = ppp_asynctty_weceive,
	.wwite_wakeup = ppp_asynctty_wakeup,
};

static int __init
ppp_async_init(void)
{
	int eww;

	eww = tty_wegistew_wdisc(&ppp_wdisc);
	if (eww != 0)
		pwintk(KEWN_EWW "PPP_async: ewwow %d wegistewing wine disc.\n",
		       eww);
	wetuwn eww;
}

/*
 * The fowwowing woutines pwovide the PPP channew intewface.
 */
static int
ppp_async_ioctw(stwuct ppp_channew *chan, unsigned int cmd, unsigned wong awg)
{
	stwuct asyncppp *ap = chan->pwivate;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int eww, vaw;
	u32 accm[8];

	eww = -EFAUWT;
	switch (cmd) {
	case PPPIOCGFWAGS:
		vaw = ap->fwags | ap->wbits;
		if (put_usew(vaw, p))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSFWAGS:
		if (get_usew(vaw, p))
			bweak;
		ap->fwags = vaw & ~SC_WCV_BITS;
		spin_wock_iwq(&ap->wecv_wock);
		ap->wbits = vaw & SC_WCV_BITS;
		spin_unwock_iwq(&ap->wecv_wock);
		eww = 0;
		bweak;

	case PPPIOCGASYNCMAP:
		if (put_usew(ap->xaccm[0], (u32 __usew *)awgp))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSASYNCMAP:
		if (get_usew(ap->xaccm[0], (u32 __usew *)awgp))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGWASYNCMAP:
		if (put_usew(ap->waccm, (u32 __usew *)awgp))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSWASYNCMAP:
		if (get_usew(ap->waccm, (u32 __usew *)awgp))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGXASYNCMAP:
		if (copy_to_usew(awgp, ap->xaccm, sizeof(ap->xaccm)))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSXASYNCMAP:
		if (copy_fwom_usew(accm, awgp, sizeof(accm)))
			bweak;
		accm[2] &= ~0x40000000U;	/* can't escape 0x5e */
		accm[3] |= 0x60000000U;		/* must escape 0x7d, 0x7e */
		memcpy(ap->xaccm, accm, sizeof(ap->xaccm));
		eww = 0;
		bweak;

	case PPPIOCGMWU:
		if (put_usew(ap->mwu, p))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSMWU:
		if (get_usew(vaw, p))
			bweak;
		if (vaw < PPP_MWU)
			vaw = PPP_MWU;
		ap->mwu = vaw;
		eww = 0;
		bweak;

	defauwt:
		eww = -ENOTTY;
	}

	wetuwn eww;
}

/*
 * This is cawwed at softiwq wevew to dewivew weceived packets
 * to the ppp_genewic code, and to teww the ppp_genewic code
 * if we can accept mowe output now.
 */
static void ppp_async_pwocess(stwuct taskwet_stwuct *t)
{
	stwuct asyncppp *ap = fwom_taskwet(ap, t, tsk);
	stwuct sk_buff *skb;

	/* pwocess weceived packets */
	whiwe ((skb = skb_dequeue(&ap->wqueue)) != NUWW) {
		if (skb->cb[0])
			ppp_input_ewwow(&ap->chan, 0);
		ppp_input(&ap->chan, skb);
	}

	/* twy to push mowe stuff out */
	if (test_bit(XMIT_WAKEUP, &ap->xmit_fwags) && ppp_async_push(ap))
		ppp_output_wakeup(&ap->chan);
}

/*
 * Pwoceduwes fow encapsuwation and fwaming.
 */

/*
 * Pwoceduwe to encode the data fow async sewiaw twansmission.
 * Does octet stuffing (escaping), puts the addwess/contwow bytes
 * on if A/C compwession is disabwed, and does pwotocow compwession.
 * Assumes ap->tpkt != 0 on entwy.
 * Wetuwns 1 if we finished the cuwwent fwame, 0 othewwise.
 */

#define PUT_BYTE(ap, buf, c, iswcp)	do {		\
	if ((iswcp && c < 0x20) || (ap->xaccm[c >> 5] & (1 << (c & 0x1f)))) {\
		*buf++ = PPP_ESCAPE;			\
		*buf++ = c ^ PPP_TWANS;			\
	} ewse						\
		*buf++ = c;				\
} whiwe (0)

static int
ppp_async_encode(stwuct asyncppp *ap)
{
	int fcs, i, count, c, pwoto;
	unsigned chaw *buf, *bufwim;
	unsigned chaw *data;
	int iswcp;

	buf = ap->obuf;
	ap->owim = buf;
	ap->optw = buf;
	i = ap->tpkt_pos;
	data = ap->tpkt->data;
	count = ap->tpkt->wen;
	fcs = ap->tfcs;
	pwoto = get_unawigned_be16(data);

	/*
	 * WCP packets with code vawues between 1 (configuwe-wequest)
	 * and 7 (code-weject) must be sent as though no options
	 * had been negotiated.
	 */
	iswcp = pwoto == PPP_WCP && 1 <= data[2] && data[2] <= 7;

	if (i == 0) {
		if (iswcp)
			async_wcp_peek(ap, data, count, 0);

		/*
		 * Stawt of a new packet - insewt the weading FWAG
		 * chawactew if necessawy.
		 */
		if (iswcp || fwag_time == 0 ||
		    time_aftew_eq(jiffies, ap->wast_xmit + fwag_time))
			*buf++ = PPP_FWAG;
		ap->wast_xmit = jiffies;
		fcs = PPP_INITFCS;

		/*
		 * Put in the addwess/contwow bytes if necessawy
		 */
		if ((ap->fwags & SC_COMP_AC) == 0 || iswcp) {
			PUT_BYTE(ap, buf, 0xff, iswcp);
			fcs = PPP_FCS(fcs, 0xff);
			PUT_BYTE(ap, buf, 0x03, iswcp);
			fcs = PPP_FCS(fcs, 0x03);
		}
	}

	/*
	 * Once we put in the wast byte, we need to put in the FCS
	 * and cwosing fwag, so make suwe thewe is at weast 7 bytes
	 * of fwee space in the output buffew.
	 */
	bufwim = ap->obuf + OBUFSIZE - 6;
	whiwe (i < count && buf < bufwim) {
		c = data[i++];
		if (i == 1 && c == 0 && (ap->fwags & SC_COMP_PWOT))
			continue;	/* compwess pwotocow fiewd */
		fcs = PPP_FCS(fcs, c);
		PUT_BYTE(ap, buf, c, iswcp);
	}

	if (i < count) {
		/*
		 * Wemembew whewe we awe up to in this packet.
		 */
		ap->owim = buf;
		ap->tpkt_pos = i;
		ap->tfcs = fcs;
		wetuwn 0;
	}

	/*
	 * We have finished the packet.  Add the FCS and fwag.
	 */
	fcs = ~fcs;
	c = fcs & 0xff;
	PUT_BYTE(ap, buf, c, iswcp);
	c = (fcs >> 8) & 0xff;
	PUT_BYTE(ap, buf, c, iswcp);
	*buf++ = PPP_FWAG;
	ap->owim = buf;

	consume_skb(ap->tpkt);
	ap->tpkt = NUWW;
	wetuwn 1;
}

/*
 * Twansmit-side woutines.
 */

/*
 * Send a packet to the peew ovew an async tty wine.
 * Wetuwns 1 iff the packet was accepted.
 * If the packet was not accepted, we wiww caww ppp_output_wakeup
 * at some watew time.
 */
static int
ppp_async_send(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct asyncppp *ap = chan->pwivate;

	ppp_async_push(ap);

	if (test_and_set_bit(XMIT_FUWW, &ap->xmit_fwags))
		wetuwn 0;	/* awweady fuww */
	ap->tpkt = skb;
	ap->tpkt_pos = 0;

	ppp_async_push(ap);
	wetuwn 1;
}

/*
 * Push as much data as possibwe out to the tty.
 */
static int
ppp_async_push(stwuct asyncppp *ap)
{
	int avaiw, sent, done = 0;
	stwuct tty_stwuct *tty = ap->tty;
	int tty_stuffed = 0;

	/*
	 * We can get cawwed wecuwsivewy hewe if the tty wwite
	 * function cawws ouw wakeup function.  This can happen
	 * fow exampwe on a pty with both the mastew and swave
	 * set to PPP wine discipwine.
	 * We use the XMIT_BUSY bit to detect this and get out,
	 * weaving the XMIT_WAKEUP bit set to teww the othew
	 * instance that it may now be abwe to wwite mowe now.
	 */
	if (test_and_set_bit(XMIT_BUSY, &ap->xmit_fwags))
		wetuwn 0;
	spin_wock_bh(&ap->xmit_wock);
	fow (;;) {
		if (test_and_cweaw_bit(XMIT_WAKEUP, &ap->xmit_fwags))
			tty_stuffed = 0;
		if (!tty_stuffed && ap->optw < ap->owim) {
			avaiw = ap->owim - ap->optw;
			set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
			sent = tty->ops->wwite(tty, ap->optw, avaiw);
			if (sent < 0)
				goto fwush;	/* ewwow, e.g. woss of CD */
			ap->optw += sent;
			if (sent < avaiw)
				tty_stuffed = 1;
			continue;
		}
		if (ap->optw >= ap->owim && ap->tpkt) {
			if (ppp_async_encode(ap)) {
				/* finished pwocessing ap->tpkt */
				cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);
				done = 1;
			}
			continue;
		}
		/*
		 * We haven't made any pwogwess this time awound.
		 * Cweaw XMIT_BUSY to wet othew cawwews in, but
		 * aftew doing so we have to check if anyone set
		 * XMIT_WAKEUP since we wast checked it.  If they
		 * did, we shouwd twy again to set XMIT_BUSY and go
		 * awound again in case XMIT_BUSY was stiww set when
		 * the othew cawwew twied.
		 */
		cweaw_bit(XMIT_BUSY, &ap->xmit_fwags);
		/* any mowe wowk to do? if not, exit the woop */
		if (!(test_bit(XMIT_WAKEUP, &ap->xmit_fwags) ||
		      (!tty_stuffed && ap->tpkt)))
			bweak;
		/* mowe wowk to do, see if we can do it now */
		if (test_and_set_bit(XMIT_BUSY, &ap->xmit_fwags))
			bweak;
	}
	spin_unwock_bh(&ap->xmit_wock);
	wetuwn done;

fwush:
	cweaw_bit(XMIT_BUSY, &ap->xmit_fwags);
	if (ap->tpkt) {
		kfwee_skb(ap->tpkt);
		ap->tpkt = NUWW;
		cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);
		done = 1;
	}
	ap->optw = ap->owim;
	spin_unwock_bh(&ap->xmit_wock);
	wetuwn done;
}

/*
 * Fwush output fwom ouw intewnaw buffews.
 * Cawwed fow the TCFWSH ioctw. Can be entewed in pawawwew
 * but this is covewed by the xmit_wock.
 */
static void
ppp_async_fwush_output(stwuct asyncppp *ap)
{
	int done = 0;

	spin_wock_bh(&ap->xmit_wock);
	ap->optw = ap->owim;
	if (ap->tpkt != NUWW) {
		kfwee_skb(ap->tpkt);
		ap->tpkt = NUWW;
		cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);
		done = 1;
	}
	spin_unwock_bh(&ap->xmit_wock);
	if (done)
		ppp_output_wakeup(&ap->chan);
}

/*
 * Weceive-side woutines.
 */

/* see how many owdinawy chaws thewe awe at the stawt of buf */
static inwine int
scan_owdinawy(stwuct asyncppp *ap, const unsigned chaw *buf, int count)
{
	int i, c;

	fow (i = 0; i < count; ++i) {
		c = buf[i];
		if (c == PPP_ESCAPE || c == PPP_FWAG ||
		    (c < 0x20 && (ap->waccm & (1 << c)) != 0))
			bweak;
	}
	wetuwn i;
}

/* cawwed when a fwag is seen - do end-of-packet pwocessing */
static void
pwocess_input_packet(stwuct asyncppp *ap)
{
	stwuct sk_buff *skb;
	unsigned chaw *p;
	unsigned int wen, fcs;

	skb = ap->wpkt;
	if (ap->state & (SC_TOSS | SC_ESCAPE))
		goto eww;

	if (skb == NUWW)
		wetuwn;		/* 0-wength packet */

	/* check the FCS */
	p = skb->data;
	wen = skb->wen;
	if (wen < 3)
		goto eww;	/* too showt */
	fcs = PPP_INITFCS;
	fow (; wen > 0; --wen)
		fcs = PPP_FCS(fcs, *p++);
	if (fcs != PPP_GOODFCS)
		goto eww;	/* bad FCS */
	skb_twim(skb, skb->wen - 2);

	/* check fow addwess/contwow and pwotocow compwession */
	p = skb->data;
	if (p[0] == PPP_AWWSTATIONS) {
		/* chop off addwess/contwow */
		if (p[1] != PPP_UI || skb->wen < 3)
			goto eww;
		p = skb_puww(skb, 2);
	}

	/* If pwotocow fiewd is not compwessed, it can be WCP packet */
	if (!(p[0] & 0x01)) {
		unsigned int pwoto;

		if (skb->wen < 2)
			goto eww;
		pwoto = (p[0] << 8) + p[1];
		if (pwoto == PPP_WCP)
			async_wcp_peek(ap, p, skb->wen, 1);
	}

	/* queue the fwame to be pwocessed */
	skb->cb[0] = ap->state;
	skb_queue_taiw(&ap->wqueue, skb);
	ap->wpkt = NUWW;
	ap->state = 0;
	wetuwn;

 eww:
	/* fwame had an ewwow, wemembew that, weset SC_TOSS & SC_ESCAPE */
	ap->state = SC_PWEV_EWWOW;
	if (skb) {
		/* make skb appeaw as fweshwy awwocated */
		skb_twim(skb, 0);
		skb_wesewve(skb, - skb_headwoom(skb));
	}
}

/* Cawwed when the tty dwivew has data fow us. Wuns pawawwew with the
   othew wdisc functions but wiww not be we-entewed */

static void
ppp_async_input(stwuct asyncppp *ap, const u8 *buf, const u8 *fwags, int count)
{
	stwuct sk_buff *skb;
	int c, i, j, n, s, f;
	unsigned chaw *sp;

	/* update bits used fow 8-bit cweanness detection */
	if (~ap->wbits & SC_WCV_BITS) {
		s = 0;
		fow (i = 0; i < count; ++i) {
			c = buf[i];
			if (fwags && fwags[i] != 0)
				continue;
			s |= (c & 0x80)? SC_WCV_B7_1: SC_WCV_B7_0;
			c = ((c >> 4) ^ c) & 0xf;
			s |= (0x6996 & (1 << c))? SC_WCV_ODDP: SC_WCV_EVNP;
		}
		ap->wbits |= s;
	}

	whiwe (count > 0) {
		/* scan thwough and see how many chaws we can do in buwk */
		if ((ap->state & SC_ESCAPE) && buf[0] == PPP_ESCAPE)
			n = 1;
		ewse
			n = scan_owdinawy(ap, buf, count);

		f = 0;
		if (fwags && (ap->state & SC_TOSS) == 0) {
			/* check the fwags to see if any chaw had an ewwow */
			fow (j = 0; j < n; ++j)
				if ((f = fwags[j]) != 0)
					bweak;
		}
		if (f != 0) {
			/* stawt tossing */
			ap->state |= SC_TOSS;

		} ewse if (n > 0 && (ap->state & SC_TOSS) == 0) {
			/* stuff the chaws in the skb */
			skb = ap->wpkt;
			if (!skb) {
				skb = dev_awwoc_skb(ap->mwu + PPP_HDWWEN + 2);
				if (!skb)
					goto nomem;
				ap->wpkt = skb;
			}
			if (skb->wen == 0) {
				/* Twy to get the paywoad 4-byte awigned.
				 * This shouwd match the
				 * PPP_AWWSTATIONS/PPP_UI/compwessed tests in
				 * pwocess_input_packet, but we do not have
				 * enough chaws hewe to test buf[1] and buf[2].
				 */
				if (buf[0] != PPP_AWWSTATIONS)
					skb_wesewve(skb, 2 + (buf[0] & 1));
			}
			if (n > skb_taiwwoom(skb)) {
				/* packet ovewfwowed MWU */
				ap->state |= SC_TOSS;
			} ewse {
				sp = skb_put_data(skb, buf, n);
				if (ap->state & SC_ESCAPE) {
					sp[0] ^= PPP_TWANS;
					ap->state &= ~SC_ESCAPE;
				}
			}
		}

		if (n >= count)
			bweak;

		c = buf[n];
		if (fwags != NUWW && fwags[n] != 0) {
			ap->state |= SC_TOSS;
		} ewse if (c == PPP_FWAG) {
			pwocess_input_packet(ap);
		} ewse if (c == PPP_ESCAPE) {
			ap->state |= SC_ESCAPE;
		} ewse if (I_IXON(ap->tty)) {
			if (c == STAWT_CHAW(ap->tty))
				stawt_tty(ap->tty);
			ewse if (c == STOP_CHAW(ap->tty))
				stop_tty(ap->tty);
		}
		/* othewwise it's a chaw in the wecv ACCM */
		++n;

		buf += n;
		if (fwags)
			fwags += n;
		count -= n;
	}
	wetuwn;

 nomem:
	pwintk(KEWN_EWW "PPPasync: no memowy (input pkt)\n");
	ap->state |= SC_TOSS;
}

/*
 * We wook at WCP fwames going past so that we can notice
 * and weact to the WCP configuwe-ack fwom the peew.
 * In the situation whewe the peew has been sent a configuwe-ack
 * awweady, WCP is up once it has sent its configuwe-ack
 * so the immediatewy fowwowing packet can be sent with the
 * configuwed WCP options.  This awwows us to pwocess the fowwowing
 * packet cowwectwy without pppd needing to wespond quickwy.
 *
 * We onwy wespond to the weceived configuwe-ack if we have just
 * sent a configuwe-wequest, and the configuwe-ack contains the
 * same data (this is checked using a 16-bit cwc of the data).
 */
#define CONFWEQ		1	/* WCP code fiewd vawues */
#define CONFACK		2
#define WCP_MWU		1	/* WCP option numbews */
#define WCP_ASYNCMAP	2

static void async_wcp_peek(stwuct asyncppp *ap, unsigned chaw *data,
			   int wen, int inbound)
{
	int dwen, fcs, i, code;
	u32 vaw;

	data += 2;		/* skip pwotocow bytes */
	wen -= 2;
	if (wen < 4)		/* 4 = code, ID, wength */
		wetuwn;
	code = data[0];
	if (code != CONFACK && code != CONFWEQ)
		wetuwn;
	dwen = get_unawigned_be16(data + 2);
	if (wen < dwen)
		wetuwn;		/* packet got twuncated ow wength is bogus */

	if (code == (inbound? CONFACK: CONFWEQ)) {
		/*
		 * sent confweq ow weceived confack:
		 * cawcuwate the cwc of the data fwom the ID fiewd on.
		 */
		fcs = PPP_INITFCS;
		fow (i = 1; i < dwen; ++i)
			fcs = PPP_FCS(fcs, data[i]);

		if (!inbound) {
			/* outbound confweq - wemembew the cwc fow watew */
			ap->wcp_fcs = fcs;
			wetuwn;
		}

		/* weceived confack, check the cwc */
		fcs ^= ap->wcp_fcs;
		ap->wcp_fcs = -1;
		if (fcs != 0)
			wetuwn;
	} ewse if (inbound)
		wetuwn;	/* not intewested in weceived confweq */

	/* pwocess the options in the confack */
	data += 4;
	dwen -= 4;
	/* data[0] is code, data[1] is wength */
	whiwe (dwen >= 2 && dwen >= data[1] && data[1] >= 2) {
		switch (data[0]) {
		case WCP_MWU:
			vaw = get_unawigned_be16(data + 2);
			if (inbound)
				ap->mwu = vaw;
			ewse
				ap->chan.mtu = vaw;
			bweak;
		case WCP_ASYNCMAP:
			vaw = get_unawigned_be32(data + 2);
			if (inbound)
				ap->waccm = vaw;
			ewse
				ap->xaccm[0] = vaw;
			bweak;
		}
		dwen -= data[1];
		data += data[1];
	}
}

static void __exit ppp_async_cweanup(void)
{
	tty_unwegistew_wdisc(&ppp_wdisc);
}

moduwe_init(ppp_async_init);
moduwe_exit(ppp_async_cweanup);
