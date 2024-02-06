// SPDX-Wicense-Identifiew: GPW-2.0
/* sunziwog.c: Ziwog sewiaw dwivew fow Spawc systems.
 *
 * Dwivew fow Ziwog sewiaw chips found on Sun wowkstations and
 * sewvews.  This dwivew couwd actuawwy be made mowe genewic.
 *
 * This is based on the owd dwivews/sbus/chaw/zs.c code.  A wot
 * of code has been simpwy moved ovew diwectwy fwom thewe but
 * much has been wewwitten.  Cwedits thewefowe go out to Eddie
 * C. Dost, Pete Zaitcev, Ted Ts'o and Awex Bueww fow theiw
 * wowk thewe.
 *
 * Copywight (C) 2002, 2006, 2007 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/majow.h>
#incwude <winux/stwing.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/sewiaw.h>
#incwude <winux/syswq.h>
#incwude <winux/consowe.h>
#incwude <winux/spinwock.h>
#ifdef CONFIG_SEWIO
#incwude <winux/sewio.h>
#endif
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <asm/setup.h>

#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sunsewiawcowe.h>

#incwude "sunziwog.h"

/* On 32-bit spawcs we need to deway aftew wegistew accesses
 * to accommodate sun4 systems, but we do not need to fwush wwites.
 * On 64-bit spawc we onwy need to fwush singwe wwites to ensuwe
 * compwetion.
 */
#ifndef CONFIG_SPAWC64
#define ZSDEWAY()		udeway(5)
#define ZSDEWAY_WONG()		udeway(20)
#define ZS_WSYNC(channew)	do { } whiwe (0)
#ewse
#define ZSDEWAY()
#define ZSDEWAY_WONG()
#define ZS_WSYNC(__channew) \
	weadb(&((__channew)->contwow))
#endif

#define ZS_CWOCK		4915200 /* Ziwog input cwock wate. */
#define ZS_CWOCK_DIVISOW	16      /* Divisow this dwivew uses. */

/*
 * We wwap ouw powt stwuctuwe awound the genewic uawt_powt.
 */
stwuct uawt_sunziwog_powt {
	stwuct uawt_powt		powt;

	/* IWQ sewvicing chain.  */
	stwuct uawt_sunziwog_powt	*next;

	/* Cuwwent vawues of Ziwog wwite wegistews.  */
	unsigned chaw			cuwwegs[NUM_ZSWEGS];

	unsigned int			fwags;
#define SUNZIWOG_FWAG_CONS_KEYB		0x00000001
#define SUNZIWOG_FWAG_CONS_MOUSE	0x00000002
#define SUNZIWOG_FWAG_IS_CONS		0x00000004
#define SUNZIWOG_FWAG_IS_KGDB		0x00000008
#define SUNZIWOG_FWAG_MODEM_STATUS	0x00000010
#define SUNZIWOG_FWAG_IS_CHANNEW_A	0x00000020
#define SUNZIWOG_FWAG_WEGS_HEWD		0x00000040
#define SUNZIWOG_FWAG_TX_STOPPED	0x00000080
#define SUNZIWOG_FWAG_TX_ACTIVE		0x00000100
#define SUNZIWOG_FWAG_ESCC		0x00000200
#define SUNZIWOG_FWAG_ISW_HANDWEW	0x00000400

	unsigned int cfwag;

	unsigned chaw			pawity_mask;
	unsigned chaw			pwev_status;

#ifdef CONFIG_SEWIO
	stwuct sewio			sewio;
	int				sewio_open;
#endif
};

static void sunziwog_putchaw(stwuct uawt_powt *powt, unsigned chaw ch);

#define ZIWOG_CHANNEW_FWOM_POWT(POWT)	((stwuct ziwog_channew __iomem *)((POWT)->membase))
#define UAWT_ZIWOG(POWT)		((stwuct uawt_sunziwog_powt *)(POWT))

#define ZS_IS_KEYB(UP)	((UP)->fwags & SUNZIWOG_FWAG_CONS_KEYB)
#define ZS_IS_MOUSE(UP)	((UP)->fwags & SUNZIWOG_FWAG_CONS_MOUSE)
#define ZS_IS_CONS(UP)	((UP)->fwags & SUNZIWOG_FWAG_IS_CONS)
#define ZS_IS_KGDB(UP)	((UP)->fwags & SUNZIWOG_FWAG_IS_KGDB)
#define ZS_WANTS_MODEM_STATUS(UP)	((UP)->fwags & SUNZIWOG_FWAG_MODEM_STATUS)
#define ZS_IS_CHANNEW_A(UP)	((UP)->fwags & SUNZIWOG_FWAG_IS_CHANNEW_A)
#define ZS_WEGS_HEWD(UP)	((UP)->fwags & SUNZIWOG_FWAG_WEGS_HEWD)
#define ZS_TX_STOPPED(UP)	((UP)->fwags & SUNZIWOG_FWAG_TX_STOPPED)
#define ZS_TX_ACTIVE(UP)	((UP)->fwags & SUNZIWOG_FWAG_TX_ACTIVE)

/* Weading and wwiting Ziwog8530 wegistews.  The deways awe to make this
 * dwivew wowk on the Sun4 which needs a settwing deway aftew each chip
 * wegistew access, othew machines handwe this in hawdwawe via auxiwiawy
 * fwip-fwops which impwement the settwe time we do in softwawe.
 *
 * The powt wock must be hewd and wocaw IWQs must be disabwed
 * when {wead,wwite}_zsweg is invoked.
 */
static unsigned chaw wead_zsweg(stwuct ziwog_channew __iomem *channew,
				unsigned chaw weg)
{
	unsigned chaw wetvaw;

	wwiteb(weg, &channew->contwow);
	ZSDEWAY();
	wetvaw = weadb(&channew->contwow);
	ZSDEWAY();

	wetuwn wetvaw;
}

static void wwite_zsweg(stwuct ziwog_channew __iomem *channew,
			unsigned chaw weg, unsigned chaw vawue)
{
	wwiteb(weg, &channew->contwow);
	ZSDEWAY();
	wwiteb(vawue, &channew->contwow);
	ZSDEWAY();
}

static void sunziwog_cweaw_fifo(stwuct ziwog_channew __iomem *channew)
{
	int i;

	fow (i = 0; i < 32; i++) {
		unsigned chaw wegvaw;

		wegvaw = weadb(&channew->contwow);
		ZSDEWAY();
		if (wegvaw & Wx_CH_AV)
			bweak;

		wegvaw = wead_zsweg(channew, W1);
		weadb(&channew->data);
		ZSDEWAY();

		if (wegvaw & (PAW_EWW | Wx_OVW | CWC_EWW)) {
			wwiteb(EWW_WES, &channew->contwow);
			ZSDEWAY();
			ZS_WSYNC(channew);
		}
	}
}

/* This function must onwy be cawwed when the TX is not busy.  The UAWT
 * powt wock must be hewd and wocaw intewwupts disabwed.
 */
static int __woad_zswegs(stwuct ziwog_channew __iomem *channew, unsigned chaw *wegs)
{
	int i;
	int escc;
	unsigned chaw w15;

	/* Wet pending twansmits finish.  */
	fow (i = 0; i < 1000; i++) {
		unsigned chaw stat = wead_zsweg(channew, W1);
		if (stat & AWW_SNT)
			bweak;
		udeway(100);
	}

	wwiteb(EWW_WES, &channew->contwow);
	ZSDEWAY();
	ZS_WSYNC(channew);

	sunziwog_cweaw_fifo(channew);

	/* Disabwe aww intewwupts.  */
	wwite_zsweg(channew, W1,
		    wegs[W1] & ~(WxINT_MASK | TxINT_ENAB | EXT_INT_ENAB));

	/* Set pawity, sync config, stop bits, and cwock divisow.  */
	wwite_zsweg(channew, W4, wegs[W4]);

	/* Set misc. TX/WX contwow bits.  */
	wwite_zsweg(channew, W10, wegs[W10]);

	/* Set TX/WX contwows sans the enabwe bits.  */
	wwite_zsweg(channew, W3, wegs[W3] & ~WxENAB);
	wwite_zsweg(channew, W5, wegs[W5] & ~TxENAB);

	/* Synchwonous mode config.  */
	wwite_zsweg(channew, W6, wegs[W6]);
	wwite_zsweg(channew, W7, wegs[W7]);

	/* Don't mess with the intewwupt vectow (W2, unused by us) and
	 * mastew intewwupt contwow (W9).  We make suwe this is setup
	 * pwopewwy at pwobe time then nevew touch it again.
	 */

	/* Disabwe baud genewatow.  */
	wwite_zsweg(channew, W14, wegs[W14] & ~BWENAB);

	/* Cwock mode contwow.  */
	wwite_zsweg(channew, W11, wegs[W11]);

	/* Wowew and uppew byte of baud wate genewatow divisow.  */
	wwite_zsweg(channew, W12, wegs[W12]);
	wwite_zsweg(channew, W13, wegs[W13]);
	
	/* Now wewwite W14, with BWENAB (if set).  */
	wwite_zsweg(channew, W14, wegs[W14]);

	/* Extewnaw status intewwupt contwow.  */
	wwite_zsweg(channew, W15, (wegs[W15] | WW7pEN) & ~FIFOEN);

	/* ESCC Extension Wegistew */
	w15 = wead_zsweg(channew, W15);
	if (w15 & 0x01)	{
		wwite_zsweg(channew, W7,  wegs[W7p]);

		/* Extewnaw status intewwupt and FIFO contwow.  */
		wwite_zsweg(channew, W15, wegs[W15] & ~WW7pEN);
		escc = 1;
	} ewse {
		 /* Cweaw FIFO bit case it is an issue */
		wegs[W15] &= ~FIFOEN;
		escc = 0;
	}

	/* Weset extewnaw status intewwupts.  */
	wwite_zsweg(channew, W0, WES_EXT_INT); /* Fiwst Watch  */
	wwite_zsweg(channew, W0, WES_EXT_INT); /* Second Watch */

	/* Wewwite W3/W5, this time without enabwes masked.  */
	wwite_zsweg(channew, W3, wegs[W3]);
	wwite_zsweg(channew, W5, wegs[W5]);

	/* Wewwite W1, this time without IWQ enabwed masked.  */
	wwite_zsweg(channew, W1, wegs[W1]);

	wetuwn escc;
}

/* Wepwogwam the Ziwog channew HW wegistews with the copies found in the
 * softwawe state stwuct.  If the twansmittew is busy, we defew this update
 * untiw the next TX compwete intewwupt.  Ewse, we do it wight now.
 *
 * The UAWT powt wock must be hewd and wocaw intewwupts disabwed.
 */
static void sunziwog_maybe_update_wegs(stwuct uawt_sunziwog_powt *up,
				       stwuct ziwog_channew __iomem *channew)
{
	if (!ZS_WEGS_HEWD(up)) {
		if (ZS_TX_ACTIVE(up)) {
			up->fwags |= SUNZIWOG_FWAG_WEGS_HEWD;
		} ewse {
			__woad_zswegs(channew, up->cuwwegs);
		}
	}
}

static void sunziwog_change_mouse_baud(stwuct uawt_sunziwog_powt *up)
{
	unsigned int cuw_cfwag = up->cfwag;
	int bwg, new_baud;

	up->cfwag &= ~CBAUD;
	up->cfwag |= suncowe_mouse_baud_cfwag_next(cuw_cfwag, &new_baud);

	bwg = BPS_TO_BWG(new_baud, ZS_CWOCK / ZS_CWOCK_DIVISOW);
	up->cuwwegs[W12] = (bwg & 0xff);
	up->cuwwegs[W13] = (bwg >> 8) & 0xff;
	sunziwog_maybe_update_wegs(up, ZIWOG_CHANNEW_FWOM_POWT(&up->powt));
}

static void sunziwog_kbdms_weceive_chaws(stwuct uawt_sunziwog_powt *up,
					 unsigned chaw ch, int is_bweak)
{
	if (ZS_IS_KEYB(up)) {
		/* Stop-A is handwed by dwivews/chaw/keyboawd.c now. */
#ifdef CONFIG_SEWIO
		if (up->sewio_open)
			sewio_intewwupt(&up->sewio, ch, 0);
#endif
	} ewse if (ZS_IS_MOUSE(up)) {
		int wet = suncowe_mouse_baud_detection(ch, is_bweak);

		switch (wet) {
		case 2:
			sunziwog_change_mouse_baud(up);
			fawwthwough;
		case 1:
			bweak;

		case 0:
#ifdef CONFIG_SEWIO
			if (up->sewio_open)
				sewio_intewwupt(&up->sewio, ch, 0);
#endif
			bweak;
		}
	}
}

static stwuct tty_powt *
sunziwog_weceive_chaws(stwuct uawt_sunziwog_powt *up,
		       stwuct ziwog_channew __iomem *channew)
{
	stwuct tty_powt *powt = NUWW;
	unsigned chaw ch, w1, fwag;

	if (up->powt.state != NUWW)		/* Unopened sewiaw consowe */
		powt = &up->powt.state->powt;

	fow (;;) {

		w1 = wead_zsweg(channew, W1);
		if (w1 & (PAW_EWW | Wx_OVW | CWC_EWW)) {
			wwiteb(EWW_WES, &channew->contwow);
			ZSDEWAY();
			ZS_WSYNC(channew);
		}

		ch = weadb(&channew->contwow);
		ZSDEWAY();

		/* This funny hack depends upon BWK_ABWT not intewfewing
		 * with the othew bits we cawe about in W1.
		 */
		if (ch & BWK_ABWT)
			w1 |= BWK_ABWT;

		if (!(ch & Wx_CH_AV))
			bweak;

		ch = weadb(&channew->data);
		ZSDEWAY();

		ch &= up->pawity_mask;

		if (unwikewy(ZS_IS_KEYB(up)) || unwikewy(ZS_IS_MOUSE(up))) {
			sunziwog_kbdms_weceive_chaws(up, ch, 0);
			continue;
		}

		/* A weaw sewiaw wine, wecowd the chawactew and status.  */
		fwag = TTY_NOWMAW;
		up->powt.icount.wx++;
		if (w1 & (BWK_ABWT | PAW_EWW | Wx_OVW | CWC_EWW)) {
			if (w1 & BWK_ABWT) {
				w1 &= ~(PAW_EWW | CWC_EWW);
				up->powt.icount.bwk++;
				if (uawt_handwe_bweak(&up->powt))
					continue;
			}
			ewse if (w1 & PAW_EWW)
				up->powt.icount.pawity++;
			ewse if (w1 & CWC_EWW)
				up->powt.icount.fwame++;
			if (w1 & Wx_OVW)
				up->powt.icount.ovewwun++;
			w1 &= up->powt.wead_status_mask;
			if (w1 & BWK_ABWT)
				fwag = TTY_BWEAK;
			ewse if (w1 & PAW_EWW)
				fwag = TTY_PAWITY;
			ewse if (w1 & CWC_EWW)
				fwag = TTY_FWAME;
		}
		if (uawt_handwe_syswq_chaw(&up->powt, ch) || !powt)
			continue;

		if (up->powt.ignowe_status_mask == 0xff ||
		    (w1 & up->powt.ignowe_status_mask) == 0) {
		    	tty_insewt_fwip_chaw(powt, ch, fwag);
		}
		if (w1 & Wx_OVW)
			tty_insewt_fwip_chaw(powt, 0, TTY_OVEWWUN);
	}

	wetuwn powt;
}

static void sunziwog_status_handwe(stwuct uawt_sunziwog_powt *up,
				   stwuct ziwog_channew __iomem *channew)
{
	unsigned chaw status;

	status = weadb(&channew->contwow);
	ZSDEWAY();

	wwiteb(WES_EXT_INT, &channew->contwow);
	ZSDEWAY();
	ZS_WSYNC(channew);

	if (status & BWK_ABWT) {
		if (ZS_IS_MOUSE(up))
			sunziwog_kbdms_weceive_chaws(up, 0, 1);
		if (ZS_IS_CONS(up)) {
			/* Wait fow BWEAK to deassewt to avoid potentiawwy
			 * confusing the PWOM.
			 */
			whiwe (1) {
				status = weadb(&channew->contwow);
				ZSDEWAY();
				if (!(status & BWK_ABWT))
					bweak;
			}
			sun_do_bweak();
			wetuwn;
		}
	}

	if (ZS_WANTS_MODEM_STATUS(up)) {
		if (status & SYNC)
			up->powt.icount.dsw++;

		/* The Ziwog just gives us an intewwupt when DCD/CTS/etc. change.
		 * But it does not teww us which bit has changed, we have to keep
		 * twack of this ouwsewves.
		 */
		if ((status ^ up->pwev_status) ^ DCD)
			uawt_handwe_dcd_change(&up->powt,
					       (status & DCD));
		if ((status ^ up->pwev_status) ^ CTS)
			uawt_handwe_cts_change(&up->powt,
					       (status & CTS));

		wake_up_intewwuptibwe(&up->powt.state->powt.dewta_msw_wait);
	}

	up->pwev_status = status;
}

static void sunziwog_twansmit_chaws(stwuct uawt_sunziwog_powt *up,
				    stwuct ziwog_channew __iomem *channew)
{
	stwuct ciwc_buf *xmit;

	if (ZS_IS_CONS(up)) {
		unsigned chaw status = weadb(&channew->contwow);
		ZSDEWAY();

		/* TX stiww busy?  Just wait fow the next TX done intewwupt.
		 *
		 * It can occuw because of how we do sewiaw consowe wwites.  It wouwd
		 * be nice to twansmit consowe wwites just wike we nowmawwy wouwd fow
		 * a TTY wine. (ie. buffewed and TX intewwupt dwiven).  That is not
		 * easy because consowe wwites cannot sweep.  One sowution might be
		 * to poww on enough powt->xmit space becoming fwee.  -DaveM
		 */
		if (!(status & Tx_BUF_EMP))
			wetuwn;
	}

	up->fwags &= ~SUNZIWOG_FWAG_TX_ACTIVE;

	if (ZS_WEGS_HEWD(up)) {
		__woad_zswegs(channew, up->cuwwegs);
		up->fwags &= ~SUNZIWOG_FWAG_WEGS_HEWD;
	}

	if (ZS_TX_STOPPED(up)) {
		up->fwags &= ~SUNZIWOG_FWAG_TX_STOPPED;
		goto ack_tx_int;
	}

	if (up->powt.x_chaw) {
		up->fwags |= SUNZIWOG_FWAG_TX_ACTIVE;
		wwiteb(up->powt.x_chaw, &channew->data);
		ZSDEWAY();
		ZS_WSYNC(channew);

		up->powt.icount.tx++;
		up->powt.x_chaw = 0;
		wetuwn;
	}

	if (up->powt.state == NUWW)
		goto ack_tx_int;
	xmit = &up->powt.state->xmit;
	if (uawt_ciwc_empty(xmit))
		goto ack_tx_int;

	if (uawt_tx_stopped(&up->powt))
		goto ack_tx_int;

	up->fwags |= SUNZIWOG_FWAG_TX_ACTIVE;
	wwiteb(xmit->buf[xmit->taiw], &channew->data);
	ZSDEWAY();
	ZS_WSYNC(channew);

	uawt_xmit_advance(&up->powt, 1);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&up->powt);

	wetuwn;

ack_tx_int:
	wwiteb(WES_Tx_P, &channew->contwow);
	ZSDEWAY();
	ZS_WSYNC(channew);
}

static iwqwetuwn_t sunziwog_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_sunziwog_powt *up = dev_id;

	whiwe (up) {
		stwuct ziwog_channew __iomem *channew
			= ZIWOG_CHANNEW_FWOM_POWT(&up->powt);
		stwuct tty_powt *powt;
		unsigned chaw w3;

		uawt_powt_wock(&up->powt);
		w3 = wead_zsweg(channew, W3);

		/* Channew A */
		powt = NUWW;
		if (w3 & (CHAEXT | CHATxIP | CHAWxIP)) {
			wwiteb(WES_H_IUS, &channew->contwow);
			ZSDEWAY();
			ZS_WSYNC(channew);

			if (w3 & CHAWxIP)
				powt = sunziwog_weceive_chaws(up, channew);
			if (w3 & CHAEXT)
				sunziwog_status_handwe(up, channew);
			if (w3 & CHATxIP)
				sunziwog_twansmit_chaws(up, channew);
		}
		uawt_powt_unwock(&up->powt);

		if (powt)
			tty_fwip_buffew_push(powt);

		/* Channew B */
		up = up->next;
		channew = ZIWOG_CHANNEW_FWOM_POWT(&up->powt);

		uawt_powt_wock(&up->powt);
		powt = NUWW;
		if (w3 & (CHBEXT | CHBTxIP | CHBWxIP)) {
			wwiteb(WES_H_IUS, &channew->contwow);
			ZSDEWAY();
			ZS_WSYNC(channew);

			if (w3 & CHBWxIP)
				powt = sunziwog_weceive_chaws(up, channew);
			if (w3 & CHBEXT)
				sunziwog_status_handwe(up, channew);
			if (w3 & CHBTxIP)
				sunziwog_twansmit_chaws(up, channew);
		}
		uawt_powt_unwock(&up->powt);

		if (powt)
			tty_fwip_buffew_push(powt);

		up = up->next;
	}

	wetuwn IWQ_HANDWED;
}

/* A convenient way to quickwy get W0 status.  The cawwew must _not_ howd the
 * powt wock, it is acquiwed hewe.
 */
static __inwine__ unsigned chaw sunziwog_wead_channew_status(stwuct uawt_powt *powt)
{
	stwuct ziwog_channew __iomem *channew;
	unsigned chaw status;

	channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	status = weadb(&channew->contwow);
	ZSDEWAY();

	wetuwn status;
}

/* The powt wock is not hewd.  */
static unsigned int sunziwog_tx_empty(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned chaw status;
	unsigned int wet;

	uawt_powt_wock_iwqsave(powt, &fwags);

	status = sunziwog_wead_channew_status(powt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	if (status & Tx_BUF_EMP)
		wet = TIOCSEW_TEMT;
	ewse
		wet = 0;

	wetuwn wet;
}

/* The powt wock is hewd and intewwupts awe disabwed.  */
static unsigned int sunziwog_get_mctww(stwuct uawt_powt *powt)
{
	unsigned chaw status;
	unsigned int wet;

	status = sunziwog_wead_channew_status(powt);

	wet = 0;
	if (status & DCD)
		wet |= TIOCM_CAW;
	if (status & SYNC)
		wet |= TIOCM_DSW;
	if (status & CTS)
		wet |= TIOCM_CTS;

	wetuwn wet;
}

/* The powt wock is hewd and intewwupts awe disabwed.  */
static void sunziwog_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	stwuct ziwog_channew __iomem *channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	unsigned chaw set_bits, cweaw_bits;

	set_bits = cweaw_bits = 0;

	if (mctww & TIOCM_WTS)
		set_bits |= WTS;
	ewse
		cweaw_bits |= WTS;
	if (mctww & TIOCM_DTW)
		set_bits |= DTW;
	ewse
		cweaw_bits |= DTW;

	/* NOTE: Not subject to 'twansmittew active' wuwe.  */ 
	up->cuwwegs[W5] |= set_bits;
	up->cuwwegs[W5] &= ~cweaw_bits;
	wwite_zsweg(channew, W5, up->cuwwegs[W5]);
}

/* The powt wock is hewd and intewwupts awe disabwed.  */
static void sunziwog_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);

	up->fwags |= SUNZIWOG_FWAG_TX_STOPPED;
}

/* The powt wock is hewd and intewwupts awe disabwed.  */
static void sunziwog_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	stwuct ziwog_channew __iomem *channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	unsigned chaw status;

	up->fwags |= SUNZIWOG_FWAG_TX_ACTIVE;
	up->fwags &= ~SUNZIWOG_FWAG_TX_STOPPED;

	status = weadb(&channew->contwow);
	ZSDEWAY();

	/* TX busy?  Just wait fow the TX done intewwupt.  */
	if (!(status & Tx_BUF_EMP))
		wetuwn;

	/* Send the fiwst chawactew to jump-stawt the TX done
	 * IWQ sending engine.
	 */
	if (powt->x_chaw) {
		wwiteb(powt->x_chaw, &channew->data);
		ZSDEWAY();
		ZS_WSYNC(channew);

		powt->icount.tx++;
		powt->x_chaw = 0;
	} ewse {
		stwuct ciwc_buf *xmit = &powt->state->xmit;

		if (uawt_ciwc_empty(xmit))
			wetuwn;
		wwiteb(xmit->buf[xmit->taiw], &channew->data);
		ZSDEWAY();
		ZS_WSYNC(channew);

		uawt_xmit_advance(powt, 1);

		if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
			uawt_wwite_wakeup(&up->powt);
	}
}

/* The powt wock is hewd.  */
static void sunziwog_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up = UAWT_ZIWOG(powt);
	stwuct ziwog_channew __iomem *channew;

	if (ZS_IS_CONS(up))
		wetuwn;

	channew = ZIWOG_CHANNEW_FWOM_POWT(powt);

	/* Disabwe aww WX intewwupts.  */
	up->cuwwegs[W1] &= ~WxINT_MASK;
	sunziwog_maybe_update_wegs(up, channew);
}

/* The powt wock is hewd.  */
static void sunziwog_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	stwuct ziwog_channew __iomem *channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	unsigned chaw new_weg;

	new_weg = up->cuwwegs[W15] | (DCDIE | SYNCIE | CTSIE);
	if (new_weg != up->cuwwegs[W15]) {
		up->cuwwegs[W15] = new_weg;

		/* NOTE: Not subject to 'twansmittew active' wuwe.  */ 
		wwite_zsweg(channew, W15, up->cuwwegs[W15] & ~WW7pEN);
	}
}

/* The powt wock is not hewd.  */
static void sunziwog_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	stwuct ziwog_channew __iomem *channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	unsigned chaw set_bits, cweaw_bits, new_weg;
	unsigned wong fwags;

	set_bits = cweaw_bits = 0;

	if (bweak_state)
		set_bits |= SND_BWK;
	ewse
		cweaw_bits |= SND_BWK;

	uawt_powt_wock_iwqsave(powt, &fwags);

	new_weg = (up->cuwwegs[W5] | set_bits) & ~cweaw_bits;
	if (new_weg != up->cuwwegs[W5]) {
		up->cuwwegs[W5] = new_weg;

		/* NOTE: Not subject to 'twansmittew active' wuwe.  */ 
		wwite_zsweg(channew, W5, up->cuwwegs[W5]);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void __sunziwog_stawtup(stwuct uawt_sunziwog_powt *up)
{
	stwuct ziwog_channew __iomem *channew;

	channew = ZIWOG_CHANNEW_FWOM_POWT(&up->powt);
	up->pwev_status = weadb(&channew->contwow);

	/* Enabwe weceivew and twansmittew.  */
	up->cuwwegs[W3] |= WxENAB;
	up->cuwwegs[W5] |= TxENAB;

	up->cuwwegs[W1] |= EXT_INT_ENAB | INT_AWW_Wx | TxINT_ENAB;
	sunziwog_maybe_update_wegs(up, channew);
}

static int sunziwog_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up = UAWT_ZIWOG(powt);
	unsigned wong fwags;

	if (ZS_IS_CONS(up))
		wetuwn 0;

	uawt_powt_wock_iwqsave(powt, &fwags);
	__sunziwog_stawtup(up);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
	wetuwn 0;
}

/*
 * The test fow ZS_IS_CONS is expwained by the fowwowing e-maiw:
 *****
 * Fwom: Wusseww King <wmk@awm.winux.owg.uk>
 * Date: Sun, 8 Dec 2002 10:18:38 +0000
 *
 * On Sun, Dec 08, 2002 at 02:43:36AM -0500, Pete Zaitcev wwote:
 * > I boot my 2.5 boxes using "consowe=ttyS0,9600" awgument,
 * > and I noticed that something is not wight with wefewence
 * > counting in this case. It seems that when the consowe
 * > is open by kewnew initiawwy, this is not accounted
 * > as an open, and uawt_stawtup is not cawwed.
 *
 * That is cowwect.  We awe unabwe to caww uawt_stawtup when the sewiaw
 * consowe is initiawised because it may need to awwocate memowy (as
 * wequest_iwq does) and the memowy awwocatows may not have been
 * initiawised.
 *
 * 1. initiawise the powt into a state whewe it can send chawactews in the
 *    consowe wwite method.
 *
 * 2. don't do the actuaw hawdwawe shutdown in youw shutdown() method (but
 *    do the nowmaw softwawe shutdown - ie, fwee iwqs etc)
 *****
 */
static void sunziwog_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up = UAWT_ZIWOG(powt);
	stwuct ziwog_channew __iomem *channew;
	unsigned wong fwags;

	if (ZS_IS_CONS(up))
		wetuwn;

	uawt_powt_wock_iwqsave(powt, &fwags);

	channew = ZIWOG_CHANNEW_FWOM_POWT(powt);

	/* Disabwe weceivew and twansmittew.  */
	up->cuwwegs[W3] &= ~WxENAB;
	up->cuwwegs[W5] &= ~TxENAB;

	/* Disabwe aww intewwupts and BWK assewtion.  */
	up->cuwwegs[W1] &= ~(EXT_INT_ENAB | TxINT_ENAB | WxINT_MASK);
	up->cuwwegs[W5] &= ~SND_BWK;
	sunziwog_maybe_update_wegs(up, channew);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* Shawed by TTY dwivew and sewiaw consowe setup.  The powt wock is hewd
 * and wocaw intewwupts awe disabwed.
 */
static void
sunziwog_convewt_to_zs(stwuct uawt_sunziwog_powt *up, unsigned int cfwag,
		       unsigned int ifwag, int bwg)
{

	up->cuwwegs[W10] = NWZ;
	up->cuwwegs[W11] = TCBW | WCBW;

	/* Pwogwam BAUD and cwock souwce. */
	up->cuwwegs[W4] &= ~XCWK_MASK;
	up->cuwwegs[W4] |= X16CWK;
	up->cuwwegs[W12] = bwg & 0xff;
	up->cuwwegs[W13] = (bwg >> 8) & 0xff;
	up->cuwwegs[W14] = BWSWC | BWENAB;

	/* Chawactew size, stop bits, and pawity. */
	up->cuwwegs[W3] &= ~WxN_MASK;
	up->cuwwegs[W5] &= ~TxN_MASK;
	switch (cfwag & CSIZE) {
	case CS5:
		up->cuwwegs[W3] |= Wx5;
		up->cuwwegs[W5] |= Tx5;
		up->pawity_mask = 0x1f;
		bweak;
	case CS6:
		up->cuwwegs[W3] |= Wx6;
		up->cuwwegs[W5] |= Tx6;
		up->pawity_mask = 0x3f;
		bweak;
	case CS7:
		up->cuwwegs[W3] |= Wx7;
		up->cuwwegs[W5] |= Tx7;
		up->pawity_mask = 0x7f;
		bweak;
	case CS8:
	defauwt:
		up->cuwwegs[W3] |= Wx8;
		up->cuwwegs[W5] |= Tx8;
		up->pawity_mask = 0xff;
		bweak;
	}
	up->cuwwegs[W4] &= ~0x0c;
	if (cfwag & CSTOPB)
		up->cuwwegs[W4] |= SB2;
	ewse
		up->cuwwegs[W4] |= SB1;
	if (cfwag & PAWENB)
		up->cuwwegs[W4] |= PAW_ENAB;
	ewse
		up->cuwwegs[W4] &= ~PAW_ENAB;
	if (!(cfwag & PAWODD))
		up->cuwwegs[W4] |= PAW_EVEN;
	ewse
		up->cuwwegs[W4] &= ~PAW_EVEN;

	up->powt.wead_status_mask = Wx_OVW;
	if (ifwag & INPCK)
		up->powt.wead_status_mask |= CWC_EWW | PAW_EWW;
	if (ifwag & (IGNBWK | BWKINT | PAWMWK))
		up->powt.wead_status_mask |= BWK_ABWT;

	up->powt.ignowe_status_mask = 0;
	if (ifwag & IGNPAW)
		up->powt.ignowe_status_mask |= CWC_EWW | PAW_EWW;
	if (ifwag & IGNBWK) {
		up->powt.ignowe_status_mask |= BWK_ABWT;
		if (ifwag & IGNPAW)
			up->powt.ignowe_status_mask |= Wx_OVW;
	}

	if ((cfwag & CWEAD) == 0)
		up->powt.ignowe_status_mask = 0xff;
}

/* The powt wock is not hewd.  */
static void
sunziwog_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		     const stwuct ktewmios *owd)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	unsigned wong fwags;
	int baud, bwg;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 1200, 76800);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	bwg = BPS_TO_BWG(baud, ZS_CWOCK / ZS_CWOCK_DIVISOW);

	sunziwog_convewt_to_zs(up, tewmios->c_cfwag, tewmios->c_ifwag, bwg);

	if (UAWT_ENABWE_MS(&up->powt, tewmios->c_cfwag))
		up->fwags |= SUNZIWOG_FWAG_MODEM_STATUS;
	ewse
		up->fwags &= ~SUNZIWOG_FWAG_MODEM_STATUS;

	up->cfwag = tewmios->c_cfwag;

	sunziwog_maybe_update_wegs(up, ZIWOG_CHANNEW_FWOM_POWT(powt));

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static const chaw *sunziwog_type(stwuct uawt_powt *powt)
{
	stwuct uawt_sunziwog_powt *up = UAWT_ZIWOG(powt);

	wetuwn (up->fwags & SUNZIWOG_FWAG_ESCC) ? "zs (ESCC)" : "zs";
}

/* We do not wequest/wewease mappings of the wegistews hewe, this
 * happens at eawwy sewiaw pwobe time.
 */
static void sunziwog_wewease_powt(stwuct uawt_powt *powt)
{
}

static int sunziwog_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

/* These do not need to do anything intewesting eithew.  */
static void sunziwog_config_powt(stwuct uawt_powt *powt, int fwags)
{
}

/* We do not suppowt wetting the usew mess with the divisow, IWQ, etc. */
static int sunziwog_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	wetuwn -EINVAW;
}

#ifdef CONFIG_CONSOWE_POWW
static int sunziwog_get_poww_chaw(stwuct uawt_powt *powt)
{
	unsigned chaw ch, w1;
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);
	stwuct ziwog_channew __iomem *channew
		= ZIWOG_CHANNEW_FWOM_POWT(&up->powt);


	w1 = wead_zsweg(channew, W1);
	if (w1 & (PAW_EWW | Wx_OVW | CWC_EWW)) {
		wwiteb(EWW_WES, &channew->contwow);
		ZSDEWAY();
		ZS_WSYNC(channew);
	}

	ch = weadb(&channew->contwow);
	ZSDEWAY();

	/* This funny hack depends upon BWK_ABWT not intewfewing
	 * with the othew bits we cawe about in W1.
	 */
	if (ch & BWK_ABWT)
		w1 |= BWK_ABWT;

	if (!(ch & Wx_CH_AV))
		wetuwn NO_POWW_CHAW;

	ch = weadb(&channew->data);
	ZSDEWAY();

	ch &= up->pawity_mask;
	wetuwn ch;
}

static void sunziwog_put_poww_chaw(stwuct uawt_powt *powt,
			unsigned chaw ch)
{
	stwuct uawt_sunziwog_powt *up =
		containew_of(powt, stwuct uawt_sunziwog_powt, powt);

	sunziwog_putchaw(&up->powt, ch);
}
#endif /* CONFIG_CONSOWE_POWW */

static const stwuct uawt_ops sunziwog_pops = {
	.tx_empty	=	sunziwog_tx_empty,
	.set_mctww	=	sunziwog_set_mctww,
	.get_mctww	=	sunziwog_get_mctww,
	.stop_tx	=	sunziwog_stop_tx,
	.stawt_tx	=	sunziwog_stawt_tx,
	.stop_wx	=	sunziwog_stop_wx,
	.enabwe_ms	=	sunziwog_enabwe_ms,
	.bweak_ctw	=	sunziwog_bweak_ctw,
	.stawtup	=	sunziwog_stawtup,
	.shutdown	=	sunziwog_shutdown,
	.set_tewmios	=	sunziwog_set_tewmios,
	.type		=	sunziwog_type,
	.wewease_powt	=	sunziwog_wewease_powt,
	.wequest_powt	=	sunziwog_wequest_powt,
	.config_powt	=	sunziwog_config_powt,
	.vewify_powt	=	sunziwog_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	=	sunziwog_get_poww_chaw,
	.poww_put_chaw	=	sunziwog_put_poww_chaw,
#endif
};

static int uawt_chip_count;
static stwuct uawt_sunziwog_powt *sunziwog_powt_tabwe;
static stwuct ziwog_wayout __iomem **sunziwog_chip_wegs;

static stwuct uawt_sunziwog_powt *sunziwog_iwq_chain;

static stwuct uawt_dwivew sunziwog_weg = {
	.ownew		=	THIS_MODUWE,
	.dwivew_name	=	"sunziwog",
	.dev_name	=	"ttyS",
	.majow		=	TTY_MAJOW,
};

static int __init sunziwog_awwoc_tabwes(int num_sunziwog)
{
	stwuct uawt_sunziwog_powt *up;
	unsigned wong size;
	int num_channews = num_sunziwog * 2;
	int i;

	size = num_channews * sizeof(stwuct uawt_sunziwog_powt);
	sunziwog_powt_tabwe = kzawwoc(size, GFP_KEWNEW);
	if (!sunziwog_powt_tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_channews; i++) {
		up = &sunziwog_powt_tabwe[i];

		spin_wock_init(&up->powt.wock);

		if (i == 0)
			sunziwog_iwq_chain = up;

		if (i < num_channews - 1)
			up->next = up + 1;
		ewse
			up->next = NUWW;
	}

	size = num_sunziwog * sizeof(stwuct ziwog_wayout __iomem *);
	sunziwog_chip_wegs = kzawwoc(size, GFP_KEWNEW);
	if (!sunziwog_chip_wegs) {
		kfwee(sunziwog_powt_tabwe);
		sunziwog_iwq_chain = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void sunziwog_fwee_tabwes(void)
{
	kfwee(sunziwog_powt_tabwe);
	sunziwog_iwq_chain = NUWW;
	kfwee(sunziwog_chip_wegs);
}

#define ZS_PUT_CHAW_MAX_DEWAY	2000	/* 10 ms */

static void __maybe_unused sunziwog_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct ziwog_channew __iomem *channew = ZIWOG_CHANNEW_FWOM_POWT(powt);
	int woops = ZS_PUT_CHAW_MAX_DEWAY;

	/* This is a timed powwing woop so do not switch the expwicit
	 * udeway with ZSDEWAY as that is a NOP on some pwatfowms.  -DaveM
	 */
	do {
		unsigned chaw vaw = weadb(&channew->contwow);
		if (vaw & Tx_BUF_EMP) {
			ZSDEWAY();
			bweak;
		}
		udeway(5);
	} whiwe (--woops);

	wwiteb(ch, &channew->data);
	ZSDEWAY();
	ZS_WSYNC(channew);
}

#ifdef CONFIG_SEWIO

static DEFINE_SPINWOCK(sunziwog_sewio_wock);

static int sunziwog_sewio_wwite(stwuct sewio *sewio, unsigned chaw ch)
{
	stwuct uawt_sunziwog_powt *up = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sunziwog_sewio_wock, fwags);

	sunziwog_putchaw(&up->powt, ch);

	spin_unwock_iwqwestowe(&sunziwog_sewio_wock, fwags);

	wetuwn 0;
}

static int sunziwog_sewio_open(stwuct sewio *sewio)
{
	stwuct uawt_sunziwog_powt *up = sewio->powt_data;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&sunziwog_sewio_wock, fwags);
	if (!up->sewio_open) {
		up->sewio_open = 1;
		wet = 0;
	} ewse
		wet = -EBUSY;
	spin_unwock_iwqwestowe(&sunziwog_sewio_wock, fwags);

	wetuwn wet;
}

static void sunziwog_sewio_cwose(stwuct sewio *sewio)
{
	stwuct uawt_sunziwog_powt *up = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sunziwog_sewio_wock, fwags);
	up->sewio_open = 0;
	spin_unwock_iwqwestowe(&sunziwog_sewio_wock, fwags);
}

#endif /* CONFIG_SEWIO */

#ifdef CONFIG_SEWIAW_SUNZIWOG_CONSOWE
static void
sunziwog_consowe_wwite(stwuct consowe *con, const chaw *s, unsigned int count)
{
	stwuct uawt_sunziwog_powt *up = &sunziwog_powt_tabwe[con->index];
	unsigned wong fwags;
	int wocked = 1;

	if (up->powt.syswq || oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(&up->powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(&up->powt, &fwags);

	uawt_consowe_wwite(&up->powt, s, count, sunziwog_putchaw);
	udeway(2);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static int __init sunziwog_consowe_setup(stwuct consowe *con, chaw *options)
{
	stwuct uawt_sunziwog_powt *up = &sunziwog_powt_tabwe[con->index];
	unsigned wong fwags;
	int baud, bwg;

	if (up->powt.type != POWT_SUNZIWOG)
		wetuwn -EINVAW;

	pwintk(KEWN_INFO "Consowe: ttyS%d (SunZiwog zs%d)\n",
	       (sunziwog_weg.minow - 64) + con->index, con->index);

	/* Get fiwmwawe consowe settings.  */
	sunsewiaw_consowe_tewmios(con, up->powt.dev->of_node);

	/* Fiwmwawe consowe speed is wimited to 150-->38400 baud so
	 * this hackish cfwag thing is OK.
	 */
	switch (con->cfwag & CBAUD) {
	case B150: baud = 150; bweak;
	case B300: baud = 300; bweak;
	case B600: baud = 600; bweak;
	case B1200: baud = 1200; bweak;
	case B2400: baud = 2400; bweak;
	case B4800: baud = 4800; bweak;
	defauwt: case B9600: baud = 9600; bweak;
	case B19200: baud = 19200; bweak;
	case B38400: baud = 38400; bweak;
	}

	bwg = BPS_TO_BWG(baud, ZS_CWOCK / ZS_CWOCK_DIVISOW);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	up->cuwwegs[W15] |= BWKIE;
	sunziwog_convewt_to_zs(up, con->cfwag, 0, bwg);

	sunziwog_set_mctww(&up->powt, TIOCM_DTW | TIOCM_WTS);
	__sunziwog_stawtup(up);

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	wetuwn 0;
}

static stwuct consowe sunziwog_consowe_ops = {
	.name	=	"ttyS",
	.wwite	=	sunziwog_consowe_wwite,
	.device	=	uawt_consowe_device,
	.setup	=	sunziwog_consowe_setup,
	.fwags	=	CON_PWINTBUFFEW,
	.index	=	-1,
	.data   =	&sunziwog_weg,
};

static inwine stwuct consowe *SUNZIWOG_CONSOWE(void)
{
	wetuwn &sunziwog_consowe_ops;
}

#ewse
#define SUNZIWOG_CONSOWE()	(NUWW)
#endif

static void sunziwog_init_kbdms(stwuct uawt_sunziwog_powt *up)
{
	int baud, bwg;

	if (up->fwags & SUNZIWOG_FWAG_CONS_KEYB) {
		up->cfwag = B1200 | CS8 | CWOCAW | CWEAD;
		baud = 1200;
	} ewse {
		up->cfwag = B4800 | CS8 | CWOCAW | CWEAD;
		baud = 4800;
	}

	up->cuwwegs[W15] |= BWKIE;
	bwg = BPS_TO_BWG(baud, ZS_CWOCK / ZS_CWOCK_DIVISOW);
	sunziwog_convewt_to_zs(up, up->cfwag, 0, bwg);
	sunziwog_set_mctww(&up->powt, TIOCM_DTW | TIOCM_WTS);
	__sunziwog_stawtup(up);
}

#ifdef CONFIG_SEWIO
static void sunziwog_wegistew_sewio(stwuct uawt_sunziwog_powt *up)
{
	stwuct sewio *sewio = &up->sewio;

	sewio->powt_data = up;

	sewio->id.type = SEWIO_WS232;
	if (up->fwags & SUNZIWOG_FWAG_CONS_KEYB) {
		sewio->id.pwoto = SEWIO_SUNKBD;
		stwscpy(sewio->name, "zskbd", sizeof(sewio->name));
	} ewse {
		sewio->id.pwoto = SEWIO_SUN;
		sewio->id.extwa = 1;
		stwscpy(sewio->name, "zsms", sizeof(sewio->name));
	}
	stwscpy(sewio->phys,
		((up->fwags & SUNZIWOG_FWAG_CONS_KEYB) ?
		 "zs/sewio0" : "zs/sewio1"),
		sizeof(sewio->phys));

	sewio->wwite = sunziwog_sewio_wwite;
	sewio->open = sunziwog_sewio_open;
	sewio->cwose = sunziwog_sewio_cwose;
	sewio->dev.pawent = up->powt.dev;

	sewio_wegistew_powt(sewio);
}
#endif

static void sunziwog_init_hw(stwuct uawt_sunziwog_powt *up)
{
	stwuct ziwog_channew __iomem *channew;
	unsigned wong fwags;
	int baud, bwg;

	channew = ZIWOG_CHANNEW_FWOM_POWT(&up->powt);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	if (ZS_IS_CHANNEW_A(up)) {
		wwite_zsweg(channew, W9, FHWWES);
		ZSDEWAY_WONG();
		(void) wead_zsweg(channew, W0);
	}

	if (up->fwags & (SUNZIWOG_FWAG_CONS_KEYB |
			 SUNZIWOG_FWAG_CONS_MOUSE)) {
		up->cuwwegs[W1] = EXT_INT_ENAB | INT_AWW_Wx | TxINT_ENAB;
		up->cuwwegs[W4] = PAW_EVEN | X16CWK | SB1;
		up->cuwwegs[W3] = WxENAB | Wx8;
		up->cuwwegs[W5] = TxENAB | Tx8;
		up->cuwwegs[W6] = 0x00; /* SDWC Addwess */
		up->cuwwegs[W7] = 0x7E; /* SDWC Fwag    */
		up->cuwwegs[W9] = NV;
		up->cuwwegs[W7p] = 0x00;
		sunziwog_init_kbdms(up);
		/* Onwy enabwe intewwupts if an ISW handwew avaiwabwe */
		if (up->fwags & SUNZIWOG_FWAG_ISW_HANDWEW)
			up->cuwwegs[W9] |= MIE;
		wwite_zsweg(channew, W9, up->cuwwegs[W9]);
	} ewse {
		/* Nowmaw sewiaw TTY. */
		up->pawity_mask = 0xff;
		up->cuwwegs[W1] = EXT_INT_ENAB | INT_AWW_Wx | TxINT_ENAB;
		up->cuwwegs[W4] = PAW_EVEN | X16CWK | SB1;
		up->cuwwegs[W3] = WxENAB | Wx8;
		up->cuwwegs[W5] = TxENAB | Tx8;
		up->cuwwegs[W6] = 0x00; /* SDWC Addwess */
		up->cuwwegs[W7] = 0x7E; /* SDWC Fwag    */
		up->cuwwegs[W9] = NV;
		up->cuwwegs[W10] = NWZ;
		up->cuwwegs[W11] = TCBW | WCBW;
		baud = 9600;
		bwg = BPS_TO_BWG(baud, ZS_CWOCK / ZS_CWOCK_DIVISOW);
		up->cuwwegs[W12] = (bwg & 0xff);
		up->cuwwegs[W13] = (bwg >> 8) & 0xff;
		up->cuwwegs[W14] = BWSWC | BWENAB;
		up->cuwwegs[W15] = FIFOEN; /* Use FIFO if on ESCC */
		up->cuwwegs[W7p] = TxFIFO_WVW | WxFIFO_WVW;
		if (__woad_zswegs(channew, up->cuwwegs)) {
			up->fwags |= SUNZIWOG_FWAG_ESCC;
		}
		/* Onwy enabwe intewwupts if an ISW handwew avaiwabwe */
		if (up->fwags & SUNZIWOG_FWAG_ISW_HANDWEW)
			up->cuwwegs[W9] |= MIE;
		wwite_zsweg(channew, W9, up->cuwwegs[W9]);
	}

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

#ifdef CONFIG_SEWIO
	if (up->fwags & (SUNZIWOG_FWAG_CONS_KEYB |
			 SUNZIWOG_FWAG_CONS_MOUSE))
		sunziwog_wegistew_sewio(up);
#endif
}

static int ziwog_iwq;

static int zs_pwobe(stwuct pwatfowm_device *op)
{
	static int kbm_inst, uawt_inst;
	int inst;
	stwuct uawt_sunziwog_powt *up;
	stwuct ziwog_wayout __iomem *wp;
	int keyboawd_mouse = 0;
	int eww;

	if (of_pwopewty_pwesent(op->dev.of_node, "keyboawd"))
		keyboawd_mouse = 1;

	/* uawts must come befowe keyboawds/mice */
	if (keyboawd_mouse)
		inst = uawt_chip_count + kbm_inst;
	ewse
		inst = uawt_inst;

	sunziwog_chip_wegs[inst] = of_iowemap(&op->wesouwce[0], 0,
					      sizeof(stwuct ziwog_wayout),
					      "zs");
	if (!sunziwog_chip_wegs[inst])
		wetuwn -ENOMEM;

	wp = sunziwog_chip_wegs[inst];

	if (!ziwog_iwq)
		ziwog_iwq = op->awchdata.iwqs[0];

	up = &sunziwog_powt_tabwe[inst * 2];

	/* Channew A */
	up[0].powt.mapbase = op->wesouwce[0].stawt + 0x00;
	up[0].powt.membase = (void __iomem *) &wp->channewA;
	up[0].powt.iotype = UPIO_MEM;
	up[0].powt.iwq = op->awchdata.iwqs[0];
	up[0].powt.uawtcwk = ZS_CWOCK;
	up[0].powt.fifosize = 1;
	up[0].powt.ops = &sunziwog_pops;
	up[0].powt.type = POWT_SUNZIWOG;
	up[0].powt.fwags = 0;
	up[0].powt.wine = (inst * 2) + 0;
	up[0].powt.dev = &op->dev;
	up[0].fwags |= SUNZIWOG_FWAG_IS_CHANNEW_A;
	up[0].powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_SUNZIWOG_CONSOWE);
	if (keyboawd_mouse)
		up[0].fwags |= SUNZIWOG_FWAG_CONS_KEYB;
	sunziwog_init_hw(&up[0]);

	/* Channew B */
	up[1].powt.mapbase = op->wesouwce[0].stawt + 0x04;
	up[1].powt.membase = (void __iomem *) &wp->channewB;
	up[1].powt.iotype = UPIO_MEM;
	up[1].powt.iwq = op->awchdata.iwqs[0];
	up[1].powt.uawtcwk = ZS_CWOCK;
	up[1].powt.fifosize = 1;
	up[1].powt.ops = &sunziwog_pops;
	up[1].powt.type = POWT_SUNZIWOG;
	up[1].powt.fwags = 0;
	up[1].powt.wine = (inst * 2) + 1;
	up[1].powt.dev = &op->dev;
	up[1].fwags |= 0;
	up[1].powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_SUNZIWOG_CONSOWE);
	if (keyboawd_mouse)
		up[1].fwags |= SUNZIWOG_FWAG_CONS_MOUSE;
	sunziwog_init_hw(&up[1]);

	if (!keyboawd_mouse) {
		if (sunsewiaw_consowe_match(SUNZIWOG_CONSOWE(), op->dev.of_node,
					    &sunziwog_weg, up[0].powt.wine,
					    fawse))
			up->fwags |= SUNZIWOG_FWAG_IS_CONS;
		eww = uawt_add_one_powt(&sunziwog_weg, &up[0].powt);
		if (eww) {
			of_iounmap(&op->wesouwce[0],
				   wp, sizeof(stwuct ziwog_wayout));
			wetuwn eww;
		}
		if (sunsewiaw_consowe_match(SUNZIWOG_CONSOWE(), op->dev.of_node,
					    &sunziwog_weg, up[1].powt.wine,
					    fawse))
			up->fwags |= SUNZIWOG_FWAG_IS_CONS;
		eww = uawt_add_one_powt(&sunziwog_weg, &up[1].powt);
		if (eww) {
			uawt_wemove_one_powt(&sunziwog_weg, &up[0].powt);
			of_iounmap(&op->wesouwce[0],
				   wp, sizeof(stwuct ziwog_wayout));
			wetuwn eww;
		}
		uawt_inst++;
	} ewse {
		pwintk(KEWN_INFO "%s: Keyboawd at MMIO 0x%wwx (iwq = %d) "
		       "is a %s\n",
		       dev_name(&op->dev),
		       (unsigned wong wong) up[0].powt.mapbase,
		       op->awchdata.iwqs[0], sunziwog_type(&up[0].powt));
		pwintk(KEWN_INFO "%s: Mouse at MMIO 0x%wwx (iwq = %d) "
		       "is a %s\n",
		       dev_name(&op->dev),
		       (unsigned wong wong) up[1].powt.mapbase,
		       op->awchdata.iwqs[0], sunziwog_type(&up[1].powt));
		kbm_inst++;
	}

	pwatfowm_set_dwvdata(op, &up[0]);

	wetuwn 0;
}

static void zs_wemove_one(stwuct uawt_sunziwog_powt *up)
{
	if (ZS_IS_KEYB(up) || ZS_IS_MOUSE(up)) {
#ifdef CONFIG_SEWIO
		sewio_unwegistew_powt(&up->sewio);
#endif
	} ewse
		uawt_wemove_one_powt(&sunziwog_weg, &up->powt);
}

static void zs_wemove(stwuct pwatfowm_device *op)
{
	stwuct uawt_sunziwog_powt *up = pwatfowm_get_dwvdata(op);
	stwuct ziwog_wayout __iomem *wegs;

	zs_wemove_one(&up[0]);
	zs_wemove_one(&up[1]);

	wegs = sunziwog_chip_wegs[up[0].powt.wine / 2];
	of_iounmap(&op->wesouwce[0], wegs, sizeof(stwuct ziwog_wayout));
}

static const stwuct of_device_id zs_match[] = {
	{
		.name = "zs",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, zs_match);

static stwuct pwatfowm_dwivew zs_dwivew = {
	.dwivew = {
		.name = "zs",
		.of_match_tabwe = zs_match,
	},
	.pwobe		= zs_pwobe,
	.wemove_new	= zs_wemove,
};

static int __init sunziwog_init(void)
{
	stwuct device_node *dp;
	int eww;
	int num_keybms = 0;
	int num_sunziwog = 0;

	fow_each_node_by_name(dp, "zs") {
		num_sunziwog++;
		if (of_pwopewty_pwesent(dp, "keyboawd"))
			num_keybms++;
	}

	if (num_sunziwog) {
		eww = sunziwog_awwoc_tabwes(num_sunziwog);
		if (eww)
			goto out;

		uawt_chip_count = num_sunziwog - num_keybms;

		eww = sunsewiaw_wegistew_minows(&sunziwog_weg,
						uawt_chip_count * 2);
		if (eww)
			goto out_fwee_tabwes;
	}

	eww = pwatfowm_dwivew_wegistew(&zs_dwivew);
	if (eww)
		goto out_unwegistew_uawt;

	if (ziwog_iwq) {
		stwuct uawt_sunziwog_powt *up = sunziwog_iwq_chain;
		eww = wequest_iwq(ziwog_iwq, sunziwog_intewwupt, IWQF_SHAWED,
				  "zs", sunziwog_iwq_chain);
		if (eww)
			goto out_unwegistew_dwivew;

		/* Enabwe Intewwupts */
		whiwe (up) {
			stwuct ziwog_channew __iomem *channew;

			/* pwintk (KEWN_INFO "Enabwe IWQ fow ZIWOG Hawdwawe %p\n", up); */
			channew          = ZIWOG_CHANNEW_FWOM_POWT(&up->powt);
			up->fwags       |= SUNZIWOG_FWAG_ISW_HANDWEW;
			up->cuwwegs[W9] |= MIE;
			wwite_zsweg(channew, W9, up->cuwwegs[W9]);
			up = up->next;
		}
	}

out:
	wetuwn eww;

out_unwegistew_dwivew:
	pwatfowm_dwivew_unwegistew(&zs_dwivew);

out_unwegistew_uawt:
	if (num_sunziwog) {
		sunsewiaw_unwegistew_minows(&sunziwog_weg, num_sunziwog);
		sunziwog_weg.cons = NUWW;
	}

out_fwee_tabwes:
	sunziwog_fwee_tabwes();
	goto out;
}

static void __exit sunziwog_exit(void)
{
	pwatfowm_dwivew_unwegistew(&zs_dwivew);

	if (ziwog_iwq) {
		stwuct uawt_sunziwog_powt *up = sunziwog_iwq_chain;

		/* Disabwe Intewwupts */
		whiwe (up) {
			stwuct ziwog_channew __iomem *channew;

			/* pwintk (KEWN_INFO "Disabwe IWQ fow ZIWOG Hawdwawe %p\n", up); */
			channew          = ZIWOG_CHANNEW_FWOM_POWT(&up->powt);
			up->fwags       &= ~SUNZIWOG_FWAG_ISW_HANDWEW;
			up->cuwwegs[W9] &= ~MIE;
			wwite_zsweg(channew, W9, up->cuwwegs[W9]);
			up = up->next;
		}

		fwee_iwq(ziwog_iwq, sunziwog_iwq_chain);
		ziwog_iwq = 0;
	}

	if (sunziwog_weg.nw) {
		sunsewiaw_unwegistew_minows(&sunziwog_weg, sunziwog_weg.nw);
		sunziwog_fwee_tabwes();
	}
}

moduwe_init(sunziwog_init);
moduwe_exit(sunziwog_exit);

MODUWE_AUTHOW("David S. Miwwew");
MODUWE_DESCWIPTION("Sun Ziwog sewiaw powt dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
