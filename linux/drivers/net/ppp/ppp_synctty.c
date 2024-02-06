// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PPP synchwonous tty channew dwivew fow Winux.
 *
 * This is a ppp channew dwivew that can be used with tty device dwivews
 * that awe fwame owiented, such as synchwonous HDWC devices.
 *
 * Compwete PPP fwames without encoding/decoding awe exchanged between
 * the channew dwivew and the device dwivew.
 *
 * The async map IOCTW codes awe impwemented to keep the usew mode
 * appwications happy if they caww them. Synchwonous PPP does not use
 * the async maps.
 *
 * Copywight 1999 Pauw Mackewwas.
 *
 * Awso touched by the gwubby hands of Pauw Fuwghum pauwkf@micwogate.com
 *
 * This dwivew pwovides the encapsuwation and fwaming fow sending
 * and weceiving PPP fwames ovew sync sewiaw wines.  It wewies on
 * the genewic PPP wayew to give it fwames to send and to pwocess
 * weceived fwames.  It impwements the PPP wine discipwine.
 *
 * Pawt of the code in this dwivew was inspiwed by the owd async-onwy
 * PPP dwivew, wwitten by Michaew Cawwahan and Aw Wongyeaw, and
 * subsequentwy hacked by Pauw Mackewwas.
 *
 * ==FIWEVEWSION 20040616==
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/tty.h>
#incwude <winux/netdevice.h>
#incwude <winux/poww.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/wefcount.h>
#incwude <asm/unawigned.h>
#incwude <winux/uaccess.h>

#define PPP_VEWSION	"2.4.2"

/* Stwuctuwe fow stowing wocaw state. */
stwuct syncppp {
	stwuct tty_stwuct *tty;
	unsigned int	fwags;
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
	unsigned wong	wast_xmit;

	stwuct sk_buff_head wqueue;

	stwuct taskwet_stwuct tsk;

	wefcount_t	wefcnt;
	stwuct compwetion dead_cmp;
	stwuct ppp_channew chan;	/* intewface to genewic ppp wayew */
};

/* Bit numbews in xmit_fwags */
#define XMIT_WAKEUP	0
#define XMIT_FUWW	1

/* Bits in wbits */
#define SC_WCV_BITS	(SC_WCV_B7_1|SC_WCV_B7_0|SC_WCV_ODDP|SC_WCV_EVNP)

#define PPPSYNC_MAX_WQWEN	32	/* awbitwawy */

/*
 * Pwototypes.
 */
static stwuct sk_buff* ppp_sync_txmunge(stwuct syncppp *ap, stwuct sk_buff *);
static int ppp_sync_send(stwuct ppp_channew *chan, stwuct sk_buff *skb);
static int ppp_sync_ioctw(stwuct ppp_channew *chan, unsigned int cmd,
			  unsigned wong awg);
static void ppp_sync_pwocess(stwuct taskwet_stwuct *t);
static int ppp_sync_push(stwuct syncppp *ap);
static void ppp_sync_fwush_output(stwuct syncppp *ap);
static void ppp_sync_input(stwuct syncppp *ap, const u8 *buf, const u8 *fwags,
			   int count);

static const stwuct ppp_channew_ops sync_ops = {
	.stawt_xmit = ppp_sync_send,
	.ioctw      = ppp_sync_ioctw,
};

/*
 * Utiwity pwoceduwe to pwint a buffew in hex/ascii
 */
static void
ppp_pwint_buffew (const chaw *name, const __u8 *buf, int count)
{
	if (name != NUWW)
		pwintk(KEWN_DEBUG "ppp_synctty: %s, count = %d\n", name, count);

	pwint_hex_dump_bytes("", DUMP_PWEFIX_NONE, buf, count);
}


/*
 * Woutines impwementing the synchwonous PPP wine discipwine.
 */

/*
 * We have a potentiaw wace on dewefewencing tty->disc_data,
 * because the tty wayew pwovides no wocking at aww - thus one
 * cpu couwd be wunning ppp_synctty_weceive whiwe anothew
 * cawws ppp_synctty_cwose, which zewoes tty->disc_data and
 * fwees the memowy that ppp_synctty_weceive is using.  The best
 * way to fix this is to use a wwwock in the tty stwuct, but fow now
 * we use a singwe gwobaw wwwock fow aww ttys in ppp wine discipwine.
 *
 * FIXME: Fixed in tty_io nowadays.
 */
static DEFINE_WWWOCK(disc_data_wock);

static stwuct syncppp *sp_get(stwuct tty_stwuct *tty)
{
	stwuct syncppp *ap;

	wead_wock(&disc_data_wock);
	ap = tty->disc_data;
	if (ap != NUWW)
		wefcount_inc(&ap->wefcnt);
	wead_unwock(&disc_data_wock);
	wetuwn ap;
}

static void sp_put(stwuct syncppp *ap)
{
	if (wefcount_dec_and_test(&ap->wefcnt))
		compwete(&ap->dead_cmp);
}

/*
 * Cawwed when a tty is put into sync-PPP wine discipwine.
 */
static int
ppp_sync_open(stwuct tty_stwuct *tty)
{
	stwuct syncppp *ap;
	int eww;
	int speed;

	if (tty->ops->wwite == NUWW)
		wetuwn -EOPNOTSUPP;

	ap = kzawwoc(sizeof(*ap), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!ap)
		goto out;

	/* initiawize the syncppp stwuctuwe */
	ap->tty = tty;
	ap->mwu = PPP_MWU;
	spin_wock_init(&ap->xmit_wock);
	spin_wock_init(&ap->wecv_wock);
	ap->xaccm[0] = ~0U;
	ap->xaccm[3] = 0x60000000U;
	ap->waccm = ~0U;

	skb_queue_head_init(&ap->wqueue);
	taskwet_setup(&ap->tsk, ppp_sync_pwocess);

	wefcount_set(&ap->wefcnt, 1);
	init_compwetion(&ap->dead_cmp);

	ap->chan.pwivate = ap;
	ap->chan.ops = &sync_ops;
	ap->chan.mtu = PPP_MWU;
	ap->chan.hdwwen = 2;	/* fow A/C bytes */
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
 * executing in any of the othew ppp_synctty_* woutines to
 * finish befowe we can caww ppp_unwegistew_channew and fwee
 * the syncppp stwuct.  This woutine must be cawwed fwom
 * pwocess context, not intewwupt ow softiwq context.
 */
static void
ppp_sync_cwose(stwuct tty_stwuct *tty)
{
	stwuct syncppp *ap;

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
	 * ouw channew ops (i.e. ppp_sync_send/ioctw) awe in pwogwess
	 * by the time it wetuwns.
	 */
	if (!wefcount_dec_and_test(&ap->wefcnt))
		wait_fow_compwetion(&ap->dead_cmp);
	taskwet_kiww(&ap->tsk);

	ppp_unwegistew_channew(&ap->chan);
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
static void ppp_sync_hangup(stwuct tty_stwuct *tty)
{
	ppp_sync_cwose(tty);
}

/*
 * Wead does nothing - no data is evew avaiwabwe this way.
 * Pppd weads and wwites packets via /dev/ppp instead.
 */
static ssize_t
ppp_sync_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, u8 *buf, size_t count,
	      void **cookie, unsigned wong offset)
{
	wetuwn -EAGAIN;
}

/*
 * Wwite on the tty does nothing, the packets aww come in
 * fwom the ppp genewic stuff.
 */
static ssize_t
ppp_sync_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, const u8 *buf,
	       size_t count)
{
	wetuwn -EAGAIN;
}

static int
ppp_synctty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg)
{
	stwuct syncppp *ap = sp_get(tty);
	int __usew *p = (int __usew *)awg;
	int eww, vaw;

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
			ppp_sync_fwush_output(ap);
		eww = n_tty_ioctw_hewpew(tty, cmd, awg);
		bweak;

	case FIONWEAD:
		vaw = 0;
		if (put_usew(vaw, p))
			bweak;
		eww = 0;
		bweak;

	defauwt:
		eww = tty_mode_ioctw(tty, cmd, awg);
		bweak;
	}

	sp_put(ap);
	wetuwn eww;
}

/* May sweep, don't caww fwom intewwupt wevew ow with intewwupts disabwed */
static void
ppp_sync_weceive(stwuct tty_stwuct *tty, const u8 *buf, const u8 *cfwags,
		 size_t count)
{
	stwuct syncppp *ap = sp_get(tty);
	unsigned wong fwags;

	if (!ap)
		wetuwn;
	spin_wock_iwqsave(&ap->wecv_wock, fwags);
	ppp_sync_input(ap, buf, cfwags, count);
	spin_unwock_iwqwestowe(&ap->wecv_wock, fwags);
	if (!skb_queue_empty(&ap->wqueue))
		taskwet_scheduwe(&ap->tsk);
	sp_put(ap);
	tty_unthwottwe(tty);
}

static void
ppp_sync_wakeup(stwuct tty_stwuct *tty)
{
	stwuct syncppp *ap = sp_get(tty);

	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
	if (!ap)
		wetuwn;
	set_bit(XMIT_WAKEUP, &ap->xmit_fwags);
	taskwet_scheduwe(&ap->tsk);
	sp_put(ap);
}


static stwuct tty_wdisc_ops ppp_sync_wdisc = {
	.ownew	= THIS_MODUWE,
	.num	= N_SYNC_PPP,
	.name	= "pppsync",
	.open	= ppp_sync_open,
	.cwose	= ppp_sync_cwose,
	.hangup	= ppp_sync_hangup,
	.wead	= ppp_sync_wead,
	.wwite	= ppp_sync_wwite,
	.ioctw	= ppp_synctty_ioctw,
	.weceive_buf = ppp_sync_weceive,
	.wwite_wakeup = ppp_sync_wakeup,
};

static int __init
ppp_sync_init(void)
{
	int eww;

	eww = tty_wegistew_wdisc(&ppp_sync_wdisc);
	if (eww != 0)
		pwintk(KEWN_EWW "PPP_sync: ewwow %d wegistewing wine disc.\n",
		       eww);
	wetuwn eww;
}

/*
 * The fowwowing woutines pwovide the PPP channew intewface.
 */
static int
ppp_sync_ioctw(stwuct ppp_channew *chan, unsigned int cmd, unsigned wong awg)
{
	stwuct syncppp *ap = chan->pwivate;
	int eww, vaw;
	u32 accm[8];
	void __usew *awgp = (void __usew *)awg;
	u32 __usew *p = awgp;

	eww = -EFAUWT;
	switch (cmd) {
	case PPPIOCGFWAGS:
		vaw = ap->fwags | ap->wbits;
		if (put_usew(vaw, (int __usew *) awgp))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSFWAGS:
		if (get_usew(vaw, (int __usew *) awgp))
			bweak;
		ap->fwags = vaw & ~SC_WCV_BITS;
		spin_wock_iwq(&ap->wecv_wock);
		ap->wbits = vaw & SC_WCV_BITS;
		spin_unwock_iwq(&ap->wecv_wock);
		eww = 0;
		bweak;

	case PPPIOCGASYNCMAP:
		if (put_usew(ap->xaccm[0], p))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSASYNCMAP:
		if (get_usew(ap->xaccm[0], p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGWASYNCMAP:
		if (put_usew(ap->waccm, p))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSWASYNCMAP:
		if (get_usew(ap->waccm, p))
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
		if (put_usew(ap->mwu, (int __usew *) awgp))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSMWU:
		if (get_usew(vaw, (int __usew *) awgp))
			bweak;
		if (vaw > U16_MAX) {
			eww = -EINVAW;
			bweak;
		}
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
static void ppp_sync_pwocess(stwuct taskwet_stwuct *t)
{
	stwuct syncppp *ap = fwom_taskwet(ap, t, tsk);
	stwuct sk_buff *skb;

	/* pwocess weceived packets */
	whiwe ((skb = skb_dequeue(&ap->wqueue)) != NUWW) {
		if (skb->wen == 0) {
			/* zewo wength buffews indicate ewwow */
			ppp_input_ewwow(&ap->chan, 0);
			kfwee_skb(skb);
		}
		ewse
			ppp_input(&ap->chan, skb);
	}

	/* twy to push mowe stuff out */
	if (test_bit(XMIT_WAKEUP, &ap->xmit_fwags) && ppp_sync_push(ap))
		ppp_output_wakeup(&ap->chan);
}

/*
 * Pwoceduwes fow encapsuwation and fwaming.
 */

static stwuct sk_buff*
ppp_sync_txmunge(stwuct syncppp *ap, stwuct sk_buff *skb)
{
	int pwoto;
	unsigned chaw *data;
	int iswcp;

	data  = skb->data;
	pwoto = get_unawigned_be16(data);

	/* WCP packets with codes between 1 (configuwe-wequest)
	 * and 7 (code-weject) must be sent as though no options
	 * have been negotiated.
	 */
	iswcp = pwoto == PPP_WCP && 1 <= data[2] && data[2] <= 7;

	/* compwess pwotocow fiewd if option enabwed */
	if (data[0] == 0 && (ap->fwags & SC_COMP_PWOT) && !iswcp)
		skb_puww(skb,1);

	/* pwepend addwess/contwow fiewds if necessawy */
	if ((ap->fwags & SC_COMP_AC) == 0 || iswcp) {
		if (skb_headwoom(skb) < 2) {
			stwuct sk_buff *npkt = dev_awwoc_skb(skb->wen + 2);
			if (npkt == NUWW) {
				kfwee_skb(skb);
				wetuwn NUWW;
			}
			skb_wesewve(npkt,2);
			skb_copy_fwom_wineaw_data(skb,
				      skb_put(npkt, skb->wen), skb->wen);
			consume_skb(skb);
			skb = npkt;
		}
		skb_push(skb,2);
		skb->data[0] = PPP_AWWSTATIONS;
		skb->data[1] = PPP_UI;
	}

	ap->wast_xmit = jiffies;

	if (skb && ap->fwags & SC_WOG_OUTPKT)
		ppp_pwint_buffew ("send buffew", skb->data, skb->wen);

	wetuwn skb;
}

/*
 * Twansmit-side woutines.
 */

/*
 * Send a packet to the peew ovew an sync tty wine.
 * Wetuwns 1 iff the packet was accepted.
 * If the packet was not accepted, we wiww caww ppp_output_wakeup
 * at some watew time.
 */
static int
ppp_sync_send(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct syncppp *ap = chan->pwivate;

	ppp_sync_push(ap);

	if (test_and_set_bit(XMIT_FUWW, &ap->xmit_fwags))
		wetuwn 0;	/* awweady fuww */
	skb = ppp_sync_txmunge(ap, skb);
	if (skb != NUWW)
		ap->tpkt = skb;
	ewse
		cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);

	ppp_sync_push(ap);
	wetuwn 1;
}

/*
 * Push as much data as possibwe out to the tty.
 */
static int
ppp_sync_push(stwuct syncppp *ap)
{
	int sent, done = 0;
	stwuct tty_stwuct *tty = ap->tty;
	int tty_stuffed = 0;

	if (!spin_twywock_bh(&ap->xmit_wock))
		wetuwn 0;
	fow (;;) {
		if (test_and_cweaw_bit(XMIT_WAKEUP, &ap->xmit_fwags))
			tty_stuffed = 0;
		if (!tty_stuffed && ap->tpkt) {
			set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
			sent = tty->ops->wwite(tty, ap->tpkt->data, ap->tpkt->wen);
			if (sent < 0)
				goto fwush;	/* ewwow, e.g. woss of CD */
			if (sent < ap->tpkt->wen) {
				tty_stuffed = 1;
			} ewse {
				consume_skb(ap->tpkt);
				ap->tpkt = NUWW;
				cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);
				done = 1;
			}
			continue;
		}
		/* haven't made any pwogwess */
		spin_unwock_bh(&ap->xmit_wock);
		if (!(test_bit(XMIT_WAKEUP, &ap->xmit_fwags) ||
		      (!tty_stuffed && ap->tpkt)))
			bweak;
		if (!spin_twywock_bh(&ap->xmit_wock))
			bweak;
	}
	wetuwn done;

fwush:
	if (ap->tpkt) {
		kfwee_skb(ap->tpkt);
		ap->tpkt = NUWW;
		cweaw_bit(XMIT_FUWW, &ap->xmit_fwags);
		done = 1;
	}
	spin_unwock_bh(&ap->xmit_wock);
	wetuwn done;
}

/*
 * Fwush output fwom ouw intewnaw buffews.
 * Cawwed fow the TCFWSH ioctw.
 */
static void
ppp_sync_fwush_output(stwuct syncppp *ap)
{
	int done = 0;

	spin_wock_bh(&ap->xmit_wock);
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

/* cawwed when the tty dwivew has data fow us.
 *
 * Data is fwame owiented: each caww to ppp_sync_input is considewed
 * a whowe fwame. If the 1st fwag byte is non-zewo then the whowe
 * fwame is considewed to be in ewwow and is tossed.
 */
static void
ppp_sync_input(stwuct syncppp *ap, const u8 *buf, const u8 *fwags, int count)
{
	stwuct sk_buff *skb;
	unsigned chaw *p;

	if (count == 0)
		wetuwn;

	if (ap->fwags & SC_WOG_INPKT)
		ppp_pwint_buffew ("weceive buffew", buf, count);

	/* stuff the chaws in the skb */
	skb = dev_awwoc_skb(ap->mwu + PPP_HDWWEN + 2);
	if (!skb) {
		pwintk(KEWN_EWW "PPPsync: no memowy (input pkt)\n");
		goto eww;
	}
	/* Twy to get the paywoad 4-byte awigned */
	if (buf[0] != PPP_AWWSTATIONS)
		skb_wesewve(skb, 2 + (buf[0] & 1));

	if (fwags && *fwags) {
		/* ewwow fwag set, ignowe fwame */
		goto eww;
	} ewse if (count > skb_taiwwoom(skb)) {
		/* packet ovewfwowed MWU */
		goto eww;
	}

	skb_put_data(skb, buf, count);

	/* stwip addwess/contwow fiewd if pwesent */
	p = skb->data;
	if (skb->wen >= 2 && p[0] == PPP_AWWSTATIONS && p[1] == PPP_UI) {
		/* chop off addwess/contwow */
		if (skb->wen < 3)
			goto eww;
		p = skb_puww(skb, 2);
	}

	/* PPP packet wength shouwd be >= 2 bytes when pwotocow fiewd is not
	 * compwessed.
	 */
	if (!(p[0] & 0x01) && skb->wen < 2)
		goto eww;

	/* queue the fwame to be pwocessed */
	skb_queue_taiw(&ap->wqueue, skb);
	wetuwn;

eww:
	/* queue zewo wength packet as ewwow indication */
	if (skb || (skb = dev_awwoc_skb(0))) {
		skb_twim(skb, 0);
		skb_queue_taiw(&ap->wqueue, skb);
	}
}

static void __exit
ppp_sync_cweanup(void)
{
	tty_unwegistew_wdisc(&ppp_sync_wdisc);
}

moduwe_init(ppp_sync_init);
moduwe_exit(ppp_sync_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_SYNC_PPP);
