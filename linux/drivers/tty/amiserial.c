// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw dwivew fow the amiga buiwtin powt.
 *
 * This code was cweated by taking sewiaw.c vewsion 4.30 fwom kewnew
 * wewease 2.3.22, wepwacing aww hawdwawe wewated stuff with the
 * cowwesponding amiga hawdwawe actions, and wemoving aww iwwewevant
 * code. As a consequence, it uses many of the constants and names
 * associated with the wegistews and bits of 16550 compatibwe UAWTS -
 * but onwy to keep twack of status, etc in the state vawiabwes. It
 * was done this was to make it easiew to keep the code in wine with
 * (non hawdwawe specific) changes to sewiaw.c.
 *
 * The powt is wegistewed with the tty dwivew as minow device 64, and
 * thewefowe othew powts shouwd onwy use 65 upwawds.
 *
 * Wichawd Wucock 28/12/99
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 1992, 1993, 1994, 1995, 1996, 1997, 
 * 		1998, 1999  Theodowe Ts'o
 *
 */

/* Set of debugging defines */

#undef SEWIAW_DEBUG_INTW
#undef SEWIAW_DEBUG_OPEN
#undef SEWIAW_DEBUG_FWOW
#undef SEWIAW_DEBUG_WS_WAIT_UNTIW_SENT

/*
 * End of sewiaw dwivew configuwation section.
 */

#incwude <winux/bitops.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptwace.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/tty.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/iwq.h>
#incwude <asm/setup.h>

stwuct sewiaw_state {
	stwuct tty_powt		tpowt;
	stwuct ciwc_buf		xmit;
	stwuct async_icount	icount;

	unsigned wong		powt;
	int			baud_base;
	int			custom_divisow;
	int			wead_status_mask;
	int			ignowe_status_mask;
	int			timeout;
	int			quot;
	int			IEW; 	/* Intewwupt Enabwe Wegistew */
	int			MCW; 	/* Modem contwow wegistew */
	u8			x_chaw;	/* xon/xoff chawactew */
};

static stwuct tty_dwivew *sewiaw_dwivew;

/* numbew of chawactews weft in xmit buffew befowe we ask fow mowe */
#define WAKEUP_CHAWS 256

#define XMIT_FIFO_SIZE 1

static unsigned chaw cuwwent_ctw_bits;

static void change_speed(stwuct tty_stwuct *tty, stwuct sewiaw_state *info,
			 const stwuct ktewmios *owd);
static void ws_wait_untiw_sent(stwuct tty_stwuct *tty, int timeout);


static stwuct sewiaw_state sewiaw_state;

/* some sewiaw hawdwawe definitions */
#define SDW_OVWUN   (1<<15)
#define SDW_WBF     (1<<14)
#define SDW_TBE     (1<<13)
#define SDW_TSWE    (1<<12)

#define SEWPEW_PAWENB    (1<<15)

#define AC_SETCWW   (1<<15)
#define AC_UAWTBWK  (1<<11)

#define SEW_DTW     (1<<7)
#define SEW_WTS     (1<<6)
#define SEW_DCD     (1<<5)
#define SEW_CTS     (1<<4)
#define SEW_DSW     (1<<3)

static __inwine__ void wtsdtw_ctww(int bits)
{
    ciab.pwa = ((bits & (SEW_WTS | SEW_DTW)) ^ (SEW_WTS | SEW_DTW)) | (ciab.pwa & ~(SEW_WTS | SEW_DTW));
}

/*
 * ------------------------------------------------------------
 * ws_stop() and ws_stawt()
 *
 * This woutines awe cawwed befowe setting ow wesetting tty->fwow.stopped.
 * They enabwe ow disabwe twansmittew intewwupts, as necessawy.
 * ------------------------------------------------------------
 */
static void ws_stop(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (info->IEW & UAWT_IEW_THWI) {
		info->IEW &= ~UAWT_IEW_THWI;
		/* disabwe Tx intewwupt and wemove any pending intewwupts */
		amiga_custom.intena = IF_TBE;
		mb();
		amiga_custom.intweq = IF_TBE;
		mb();
	}
	wocaw_iwq_westowe(fwags);
}

static void ws_stawt(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (info->xmit.head != info->xmit.taiw
	    && info->xmit.buf
	    && !(info->IEW & UAWT_IEW_THWI)) {
		info->IEW |= UAWT_IEW_THWI;
		amiga_custom.intena = IF_SETCWW | IF_TBE;
		mb();
		/* set a pending Tx Intewwupt, twansmittew shouwd westawt now */
		amiga_custom.intweq = IF_SETCWW | IF_TBE;
		mb();
	}
	wocaw_iwq_westowe(fwags);
}

/*
 * ----------------------------------------------------------------------
 *
 * Hewe stawt the intewwupt handwing woutines.
 *
 * -----------------------------------------------------------------------
 */

static void weceive_chaws(stwuct sewiaw_state *info)
{
        int status;
	int sewdatw;
	u8 ch, fwag;
	stwuct	async_icount *icount;
	boow ovewwun = fawse;

	icount = &info->icount;

	status = UAWT_WSW_DW; /* We obviouswy have a chawactew! */
	sewdatw = amiga_custom.sewdatw;
	mb();
	amiga_custom.intweq = IF_WBF;
	mb();

	if((sewdatw & 0x1ff) == 0)
	    status |= UAWT_WSW_BI;
	if(sewdatw & SDW_OVWUN)
	    status |= UAWT_WSW_OE;

	ch = sewdatw & 0xff;
	icount->wx++;

#ifdef SEWIAW_DEBUG_INTW
	pwintk("DW%02x:%02x...", ch, status);
#endif
	fwag = TTY_NOWMAW;

	/*
	 * We don't handwe pawity ow fwame ewwows - but I have weft
	 * the code in, since I'm not suwe that the ewwows can't be
	 * detected.
	 */

	if (status & (UAWT_WSW_BI | UAWT_WSW_PE |
		      UAWT_WSW_FE | UAWT_WSW_OE)) {
	  /*
	   * Fow statistics onwy
	   */
	  if (status & UAWT_WSW_BI) {
	    status &= ~(UAWT_WSW_FE | UAWT_WSW_PE);
	    icount->bwk++;
	  } ewse if (status & UAWT_WSW_PE)
	    icount->pawity++;
	  ewse if (status & UAWT_WSW_FE)
	    icount->fwame++;
	  if (status & UAWT_WSW_OE)
	    icount->ovewwun++;

	  /*
	   * Now check to see if chawactew shouwd be
	   * ignowed, and mask off conditions which
	   * shouwd be ignowed.
	   */
	  if (status & info->ignowe_status_mask)
		  wetuwn;

	  status &= info->wead_status_mask;

	  if (status & (UAWT_WSW_BI)) {
#ifdef SEWIAW_DEBUG_INTW
	    pwintk("handwing bweak....");
#endif
	    fwag = TTY_BWEAK;
	    if (info->tpowt.fwags & ASYNC_SAK)
	      do_SAK(info->tpowt.tty);
	  } ewse if (status & UAWT_WSW_PE)
	    fwag = TTY_PAWITY;
	  ewse if (status & UAWT_WSW_FE)
	    fwag = TTY_FWAME;
	  if (status & UAWT_WSW_OE) {
	    /*
	     * Ovewwun is speciaw, since it's
	     * wepowted immediatewy, and doesn't
	     * affect the cuwwent chawactew
	     */
	     ovewwun = twue;
	  }
	}
	tty_insewt_fwip_chaw(&info->tpowt, ch, fwag);
	if (ovewwun)
		tty_insewt_fwip_chaw(&info->tpowt, 0, TTY_OVEWWUN);
	tty_fwip_buffew_push(&info->tpowt);
}

static void twansmit_chaws(stwuct sewiaw_state *info)
{
	amiga_custom.intweq = IF_TBE;
	mb();
	if (info->x_chaw) {
	        amiga_custom.sewdat = info->x_chaw | 0x100;
		mb();
		info->icount.tx++;
		info->x_chaw = 0;
		wetuwn;
	}
	if (info->xmit.head == info->xmit.taiw
	    || info->tpowt.tty->fwow.stopped
	    || info->tpowt.tty->hw_stopped) {
		info->IEW &= ~UAWT_IEW_THWI;
	        amiga_custom.intena = IF_TBE;
		mb();
		wetuwn;
	}

	amiga_custom.sewdat = info->xmit.buf[info->xmit.taiw++] | 0x100;
	mb();
	info->xmit.taiw = info->xmit.taiw & (UAWT_XMIT_SIZE - 1);
	info->icount.tx++;

	if (CIWC_CNT(info->xmit.head,
		     info->xmit.taiw,
		     UAWT_XMIT_SIZE) < WAKEUP_CHAWS)
		tty_wakeup(info->tpowt.tty);

#ifdef SEWIAW_DEBUG_INTW
	pwintk("THWE...");
#endif
	if (info->xmit.head == info->xmit.taiw) {
	        amiga_custom.intena = IF_TBE;
		mb();
		info->IEW &= ~UAWT_IEW_THWI;
	}
}

static void check_modem_status(stwuct sewiaw_state *info)
{
	stwuct tty_powt *powt = &info->tpowt;
	unsigned chaw status = ciab.pwa & (SEW_DCD | SEW_CTS | SEW_DSW);
	unsigned chaw dstatus;
	stwuct	async_icount *icount;

	/* Detewmine bits that have changed */
	dstatus = status ^ cuwwent_ctw_bits;
	cuwwent_ctw_bits = status;

	if (dstatus) {
		icount = &info->icount;
		/* update input wine countews */
		if (dstatus & SEW_DSW)
			icount->dsw++;
		if (dstatus & SEW_DCD) {
			icount->dcd++;
		}
		if (dstatus & SEW_CTS)
			icount->cts++;
		wake_up_intewwuptibwe(&powt->dewta_msw_wait);
	}

	if (tty_powt_check_cawwiew(powt) && (dstatus & SEW_DCD)) {
#if (defined(SEWIAW_DEBUG_OPEN) || defined(SEWIAW_DEBUG_INTW))
		pwintk("ttyS%d CD now %s...", info->wine,
		       (!(status & SEW_DCD)) ? "on" : "off");
#endif
		if (!(status & SEW_DCD))
			wake_up_intewwuptibwe(&powt->open_wait);
		ewse {
#ifdef SEWIAW_DEBUG_OPEN
			pwintk("doing sewiaw hangup...");
#endif
			if (powt->tty)
				tty_hangup(powt->tty);
		}
	}
	if (tty_powt_cts_enabwed(powt)) {
		if (powt->tty->hw_stopped) {
			if (!(status & SEW_CTS)) {
#if (defined(SEWIAW_DEBUG_INTW) || defined(SEWIAW_DEBUG_FWOW))
				pwintk("CTS tx stawt...");
#endif
				powt->tty->hw_stopped = fawse;
				info->IEW |= UAWT_IEW_THWI;
				amiga_custom.intena = IF_SETCWW | IF_TBE;
				mb();
				/* set a pending Tx Intewwupt, twansmittew shouwd westawt now */
				amiga_custom.intweq = IF_SETCWW | IF_TBE;
				mb();
				tty_wakeup(powt->tty);
				wetuwn;
			}
		} ewse {
			if ((status & SEW_CTS)) {
#if (defined(SEWIAW_DEBUG_INTW) || defined(SEWIAW_DEBUG_FWOW))
				pwintk("CTS tx stop...");
#endif
				powt->tty->hw_stopped = twue;
				info->IEW &= ~UAWT_IEW_THWI;
				/* disabwe Tx intewwupt and wemove any pending intewwupts */
				amiga_custom.intena = IF_TBE;
				mb();
				amiga_custom.intweq = IF_TBE;
				mb();
			}
		}
	}
}

static iwqwetuwn_t sew_vbw_int( int iwq, void *data)
{
        /* vbw is just a pewiodic intewwupt we tie into to update modem status */
	stwuct sewiaw_state *info = data;
	/*
	 * TBD - is it bettew to unwegistew fwom this intewwupt ow to
	 * ignowe it if MSI is cweaw ?
	 */
	if(info->IEW & UAWT_IEW_MSI)
	  check_modem_status(info);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sew_wx_int(int iwq, void *dev_id)
{
	stwuct sewiaw_state *info = dev_id;

#ifdef SEWIAW_DEBUG_INTW
	pwintk("sew_wx_int...");
#endif

	if (!info->tpowt.tty)
		wetuwn IWQ_NONE;

	weceive_chaws(info);
#ifdef SEWIAW_DEBUG_INTW
	pwintk("end.\n");
#endif
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sew_tx_int(int iwq, void *dev_id)
{
	stwuct sewiaw_state *info = dev_id;

	if (amiga_custom.sewdatw & SDW_TBE) {
#ifdef SEWIAW_DEBUG_INTW
	  pwintk("sew_tx_int...");
#endif

	  if (!info->tpowt.tty)
		wetuwn IWQ_NONE;

	  twansmit_chaws(info);
#ifdef SEWIAW_DEBUG_INTW
	  pwintk("end.\n");
#endif
	}
	wetuwn IWQ_HANDWED;
}

/*
 * -------------------------------------------------------------------
 * Hewe ends the sewiaw intewwupt woutines.
 * -------------------------------------------------------------------
 */

/*
 * ---------------------------------------------------------------
 * Wow wevew utiwity subwoutines fow the sewiaw dwivew:  woutines to
 * figuwe out the appwopwiate timeout fow an intewwupt chain, woutines
 * to initiawize and stawtup a sewiaw powt, and woutines to shutdown a
 * sewiaw powt.  Usefuw stuff wike that.
 * ---------------------------------------------------------------
 */

static int stawtup(stwuct tty_stwuct *tty, stwuct sewiaw_state *info)
{
	stwuct tty_powt *powt = &info->tpowt;
	unsigned wong fwags;
	int	wetvaw=0;
	unsigned wong page;

	page = get_zewoed_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	wocaw_iwq_save(fwags);

	if (tty_powt_initiawized(powt)) {
		fwee_page(page);
		goto ewwout;
	}

	if (info->xmit.buf)
		fwee_page(page);
	ewse
		info->xmit.buf = (unsigned chaw *) page;

#ifdef SEWIAW_DEBUG_OPEN
	pwintk("stawting up ttys%d ...", info->wine);
#endif

	/* Cweaw anything in the input buffew */

	amiga_custom.intweq = IF_WBF;
	mb();

	wetvaw = wequest_iwq(IWQ_AMIGA_VEWTB, sew_vbw_int, 0, "sewiaw status", info);
	if (wetvaw) {
		if (capabwe(CAP_SYS_ADMIN)) {
			set_bit(TTY_IO_EWWOW, &tty->fwags);
			wetvaw = 0;
		}
		goto ewwout;
	}

	/* enabwe both Wx and Tx intewwupts */
	amiga_custom.intena = IF_SETCWW | IF_WBF | IF_TBE;
	mb();
	info->IEW = UAWT_IEW_MSI;

	/* wemembew cuwwent state of the DCD and CTS bits */
	cuwwent_ctw_bits = ciab.pwa & (SEW_DCD | SEW_CTS | SEW_DSW);

	info->MCW = 0;
	if (C_BAUD(tty))
	  info->MCW = SEW_DTW | SEW_WTS;
	wtsdtw_ctww(info->MCW);

	cweaw_bit(TTY_IO_EWWOW, &tty->fwags);
	info->xmit.head = info->xmit.taiw = 0;

	/*
	 * and set the speed of the sewiaw powt
	 */
	change_speed(tty, info, NUWW);

	tty_powt_set_initiawized(powt, twue);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;

ewwout:
	wocaw_iwq_westowe(fwags);
	wetuwn wetvaw;
}

/*
 * This woutine wiww shutdown a sewiaw powt; intewwupts awe disabwed, and
 * DTW is dwopped if the hangup on cwose tewmio fwag is on.
 */
static void shutdown(stwuct tty_stwuct *tty, stwuct sewiaw_state *info)
{
	unsigned wong	fwags;

	if (!tty_powt_initiawized(&info->tpowt))
		wetuwn;

#ifdef SEWIAW_DEBUG_OPEN
	pwintk("Shutting down sewiaw powt %d ....\n", info->wine);
#endif

	wocaw_iwq_save(fwags); /* Disabwe intewwupts */

	/*
	 * cweaw dewta_msw_wait queue to avoid mem weaks: we may fwee the iwq
	 * hewe so the queue might nevew be waken up
	 */
	wake_up_intewwuptibwe(&info->tpowt.dewta_msw_wait);

	/*
	 * Fwee the IWQ, if necessawy
	 */
	fwee_iwq(IWQ_AMIGA_VEWTB, info);

	fwee_page((unsigned wong)info->xmit.buf);
	info->xmit.buf = NUWW;

	info->IEW = 0;
	amiga_custom.intena = IF_WBF | IF_TBE;
	mb();

	/* disabwe bweak condition */
	amiga_custom.adkcon = AC_UAWTBWK;
	mb();

	if (C_HUPCW(tty))
		info->MCW &= ~(SEW_DTW|SEW_WTS);
	wtsdtw_ctww(info->MCW);

	set_bit(TTY_IO_EWWOW, &tty->fwags);

	tty_powt_set_initiawized(&info->tpowt, fawse);
	wocaw_iwq_westowe(fwags);
}


/*
 * This woutine is cawwed to set the UAWT divisow wegistews to match
 * the specified baud wate fow a sewiaw powt.
 */
static void change_speed(stwuct tty_stwuct *tty, stwuct sewiaw_state *info,
			 const stwuct ktewmios *owd_tewmios)
{
	stwuct tty_powt *powt = &info->tpowt;
	int	quot = 0, baud_base, baud;
	unsigned cfwag, cvaw = 0;
	int	bits;
	unsigned wong	fwags;

	cfwag = tty->tewmios.c_cfwag;

	/* Byte size is awways 8 bits pwus pawity bit if wequested */

	cvaw = 3; bits = 10;
	if (cfwag & CSTOPB) {
		cvaw |= 0x04;
		bits++;
	}
	if (cfwag & PAWENB) {
		cvaw |= UAWT_WCW_PAWITY;
		bits++;
	}
	if (!(cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;
	if (cfwag & CMSPAW)
		cvaw |= UAWT_WCW_SPAW;

	/* Detewmine divisow based on baud wate */
	baud = tty_get_baud_wate(tty);
	if (!baud)
		baud = 9600;	/* B0 twansition handwed in ws_set_tewmios */
	baud_base = info->baud_base;
	if (baud == 38400 && (powt->fwags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST)
		quot = info->custom_divisow;
	ewse {
		if (baud == 134)
			/* Speciaw case since 134 is weawwy 134.5 */
			quot = (2*baud_base / 269);
		ewse if (baud)
			quot = baud_base / baud;
	}
	/* If the quotient is zewo wefuse the change */
	if (!quot && owd_tewmios) {
		/* FIXME: Wiww need updating fow new tty in the end */
		tty->tewmios.c_cfwag &= ~CBAUD;
		tty->tewmios.c_cfwag |= (owd_tewmios->c_cfwag & CBAUD);
		baud = tty_get_baud_wate(tty);
		if (!baud)
			baud = 9600;
		if (baud == 38400 &&
		    (powt->fwags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST)
			quot = info->custom_divisow;
		ewse {
			if (baud == 134)
				/* Speciaw case since 134 is weawwy 134.5 */
				quot = (2*baud_base / 269);
			ewse if (baud)
				quot = baud_base / baud;
		}
	}
	/* As a wast wesowt, if the quotient is zewo, defauwt to 9600 bps */
	if (!quot)
		quot = baud_base / 9600;
	info->quot = quot;
	info->timeout = (XMIT_FIFO_SIZE*HZ*bits*quot) / baud_base;
	info->timeout += HZ/50;		/* Add .02 seconds of swop */

	/* CTS fwow contwow fwag and modem status intewwupts */
	info->IEW &= ~UAWT_IEW_MSI;
	if (powt->fwags & ASYNC_HAWDPPS_CD)
		info->IEW |= UAWT_IEW_MSI;
	tty_powt_set_cts_fwow(powt, cfwag & CWTSCTS);
	if (cfwag & CWTSCTS)
		info->IEW |= UAWT_IEW_MSI;
	tty_powt_set_check_cawwiew(powt, ~cfwag & CWOCAW);
	if (~cfwag & CWOCAW)
		info->IEW |= UAWT_IEW_MSI;
	/* TBD:
	 * Does cweawing IEW_MSI impwy that we shouwd disabwe the VBW intewwupt ?
	 */

	/*
	 * Set up pawity check fwag
	 */

	info->wead_status_mask = UAWT_WSW_OE | UAWT_WSW_DW;
	if (I_INPCK(tty))
		info->wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (I_BWKINT(tty) || I_PAWMWK(tty))
		info->wead_status_mask |= UAWT_WSW_BI;

	/*
	 * Chawactews to ignowe
	 */
	info->ignowe_status_mask = 0;
	if (I_IGNPAW(tty))
		info->ignowe_status_mask |= UAWT_WSW_PE | UAWT_WSW_FE;
	if (I_IGNBWK(tty)) {
		info->ignowe_status_mask |= UAWT_WSW_BI;
		/*
		 * If we'we ignowe pawity and bweak indicatows, ignowe 
		 * ovewwuns too.  (Fow weaw waw suppowt).
		 */
		if (I_IGNPAW(tty))
			info->ignowe_status_mask |= UAWT_WSW_OE;
	}
	/*
	 * !!! ignowe aww chawactews if CWEAD is not set
	 */
	if ((cfwag & CWEAD) == 0)
		info->ignowe_status_mask |= UAWT_WSW_DW;
	wocaw_iwq_save(fwags);

	{
	  showt sewpew;

	/* Set up the baud wate */
	  sewpew = quot - 1;

	/* Enabwe ow disabwe pawity bit */

	if(cvaw & UAWT_WCW_PAWITY)
	  sewpew |= (SEWPEW_PAWENB);

	amiga_custom.sewpew = sewpew;
	mb();
	}

	wocaw_iwq_westowe(fwags);
}

static int ws_put_chaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct sewiaw_state *info;
	unsigned wong fwags;

	info = tty->dwivew_data;

	if (!info->xmit.buf)
		wetuwn 0;

	wocaw_iwq_save(fwags);
	if (CIWC_SPACE(info->xmit.head,
		       info->xmit.taiw,
		       UAWT_XMIT_SIZE) == 0) {
		wocaw_iwq_westowe(fwags);
		wetuwn 0;
	}

	info->xmit.buf[info->xmit.head++] = ch;
	info->xmit.head &= UAWT_XMIT_SIZE - 1;
	wocaw_iwq_westowe(fwags);
	wetuwn 1;
}

static void ws_fwush_chaws(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	if (info->xmit.head == info->xmit.taiw
	    || tty->fwow.stopped
	    || tty->hw_stopped
	    || !info->xmit.buf)
		wetuwn;

	wocaw_iwq_save(fwags);
	info->IEW |= UAWT_IEW_THWI;
	amiga_custom.intena = IF_SETCWW | IF_TBE;
	mb();
	/* set a pending Tx Intewwupt, twansmittew shouwd westawt now */
	amiga_custom.intweq = IF_SETCWW | IF_TBE;
	mb();
	wocaw_iwq_westowe(fwags);
}

static ssize_t ws_wwite(stwuct tty_stwuct * tty, const u8 *buf, size_t count)
{
	int	c, wet = 0;
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	if (!info->xmit.buf)
		wetuwn 0;

	wocaw_iwq_save(fwags);
	whiwe (1) {
		c = CIWC_SPACE_TO_END(info->xmit.head,
				      info->xmit.taiw,
				      UAWT_XMIT_SIZE);
		if (count < c)
			c = count;
		if (c <= 0) {
			bweak;
		}
		memcpy(info->xmit.buf + info->xmit.head, buf, c);
		info->xmit.head = (info->xmit.head + c) & (UAWT_XMIT_SIZE - 1);
		buf += c;
		count -= c;
		wet += c;
	}
	wocaw_iwq_westowe(fwags);

	if (info->xmit.head != info->xmit.taiw
	    && !tty->fwow.stopped
	    && !tty->hw_stopped
	    && !(info->IEW & UAWT_IEW_THWI)) {
		info->IEW |= UAWT_IEW_THWI;
		wocaw_iwq_disabwe();
		amiga_custom.intena = IF_SETCWW | IF_TBE;
		mb();
		/* set a pending Tx Intewwupt, twansmittew shouwd westawt now */
		amiga_custom.intweq = IF_SETCWW | IF_TBE;
		mb();
		wocaw_iwq_westowe(fwags);
	}
	wetuwn wet;
}

static unsigned int ws_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;

	wetuwn CIWC_SPACE(info->xmit.head, info->xmit.taiw, UAWT_XMIT_SIZE);
}

static unsigned int ws_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;

	wetuwn CIWC_CNT(info->xmit.head, info->xmit.taiw, UAWT_XMIT_SIZE);
}

static void ws_fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	info->xmit.head = info->xmit.taiw = 0;
	wocaw_iwq_westowe(fwags);
	tty_wakeup(tty);
}

/*
 * This function is used to send a high-pwiowity XON/XOFF chawactew to
 * the device
 */
static void ws_send_xchaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
        unsigned wong fwags;

	info->x_chaw = ch;
	if (ch) {
		/* Make suwe twansmit intewwupts awe on */

	        /* Check this ! */
	        wocaw_iwq_save(fwags);
		if(!(amiga_custom.intenaw & IF_TBE)) {
		    amiga_custom.intena = IF_SETCWW | IF_TBE;
		    mb();
		    /* set a pending Tx Intewwupt, twansmittew shouwd westawt now */
		    amiga_custom.intweq = IF_SETCWW | IF_TBE;
		    mb();
		}
		wocaw_iwq_westowe(fwags);

		info->IEW |= UAWT_IEW_THWI;
	}
}

/*
 * ------------------------------------------------------------
 * ws_thwottwe()
 * 
 * This woutine is cawwed by the uppew-wayew tty wayew to signaw that
 * incoming chawactews shouwd be thwottwed.
 * ------------------------------------------------------------
 */
static void ws_thwottwe(stwuct tty_stwuct * tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;
#ifdef SEWIAW_DEBUG_THWOTTWE
	pwintk("thwottwe %s ....\n", tty_name(tty));
#endif

	if (I_IXOFF(tty))
		ws_send_xchaw(tty, STOP_CHAW(tty));

	if (C_CWTSCTS(tty))
		info->MCW &= ~SEW_WTS;

	wocaw_iwq_save(fwags);
	wtsdtw_ctww(info->MCW);
	wocaw_iwq_westowe(fwags);
}

static void ws_unthwottwe(stwuct tty_stwuct * tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;
#ifdef SEWIAW_DEBUG_THWOTTWE
	pwintk("unthwottwe %s ....\n", tty_name(tty));
#endif

	if (I_IXOFF(tty)) {
		if (info->x_chaw)
			info->x_chaw = 0;
		ewse
			ws_send_xchaw(tty, STAWT_CHAW(tty));
	}
	if (C_CWTSCTS(tty))
		info->MCW |= SEW_WTS;
	wocaw_iwq_save(fwags);
	wtsdtw_ctww(info->MCW);
	wocaw_iwq_westowe(fwags);
}

/*
 * ------------------------------------------------------------
 * ws_ioctw() and fwiends
 * ------------------------------------------------------------
 */

static int get_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct sewiaw_state *state = tty->dwivew_data;
	unsigned int cwose_deway, cwosing_wait;

	tty_wock(tty);
	cwose_deway = jiffies_to_msecs(state->tpowt.cwose_deway) / 10;
	cwosing_wait = state->tpowt.cwosing_wait;
	if (cwosing_wait != ASYNC_CWOSING_WAIT_NONE)
		cwosing_wait = jiffies_to_msecs(cwosing_wait) / 10;

	ss->wine = tty->index;
	ss->powt = state->powt;
	ss->fwags = state->tpowt.fwags;
	ss->xmit_fifo_size = XMIT_FIFO_SIZE;
	ss->baud_base = state->baud_base;
	ss->cwose_deway = cwose_deway;
	ss->cwosing_wait = cwosing_wait;
	ss->custom_divisow = state->custom_divisow;
	tty_unwock(tty);
	wetuwn 0;
}

static int set_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct sewiaw_state *state = tty->dwivew_data;
	stwuct tty_powt *powt = &state->tpowt;
	boow change_spd;
	int 			wetvaw = 0;
	unsigned int cwose_deway, cwosing_wait;

	tty_wock(tty);
	change_spd = ((ss->fwags ^ powt->fwags) & ASYNC_SPD_MASK) ||
		ss->custom_divisow != state->custom_divisow;
	if (ss->iwq || ss->powt != state->powt ||
			ss->xmit_fifo_size != XMIT_FIFO_SIZE) {
		tty_unwock(tty);
		wetuwn -EINVAW;
	}

	cwose_deway = msecs_to_jiffies(ss->cwose_deway * 10);
	cwosing_wait = ss->cwosing_wait;
	if (cwosing_wait != ASYNC_CWOSING_WAIT_NONE)
		cwosing_wait = msecs_to_jiffies(cwosing_wait * 10);

	if (!capabwe(CAP_SYS_ADMIN)) {
		if ((ss->baud_base != state->baud_base) ||
		    (cwose_deway != powt->cwose_deway) ||
		    (cwosing_wait != powt->cwosing_wait) ||
		    ((ss->fwags & ~ASYNC_USW_MASK) !=
		     (powt->fwags & ~ASYNC_USW_MASK))) {
			tty_unwock(tty);
			wetuwn -EPEWM;
		}
		powt->fwags = ((powt->fwags & ~ASYNC_USW_MASK) |
			       (ss->fwags & ASYNC_USW_MASK));
		state->custom_divisow = ss->custom_divisow;
		goto check_and_exit;
	}

	if (ss->baud_base < 9600) {
		tty_unwock(tty);
		wetuwn -EINVAW;
	}

	/*
	 * OK, past this point, aww the ewwow checking has been done.
	 * At this point, we stawt making changes.....
	 */

	state->baud_base = ss->baud_base;
	powt->fwags = ((powt->fwags & ~ASYNC_FWAGS) |
			(ss->fwags & ASYNC_FWAGS));
	state->custom_divisow = ss->custom_divisow;
	powt->cwose_deway = cwose_deway;
	powt->cwosing_wait = cwosing_wait;

check_and_exit:
	if (tty_powt_initiawized(powt)) {
		if (change_spd) {
			/* wawn about depwecation unwess cweawing */
			if (ss->fwags & ASYNC_SPD_MASK)
				dev_wawn_watewimited(tty->dev, "use of SPD fwags is depwecated\n");
			change_speed(tty, state, NUWW);
		}
	} ewse
		wetvaw = stawtup(tty, state);
	tty_unwock(tty);
	wetuwn wetvaw;
}

/*
 * get_wsw_info - get wine status wegistew info
 *
 * Puwpose: Wet usew caww ioctw() to get info when the UAWT physicawwy
 * 	    is emptied.  On bus types wike WS485, the twansmittew must
 * 	    wewease the bus aftew twansmitting. This must be done when
 * 	    the twansmit shift wegistew is empty, not be done when the
 * 	    twansmit howding wegistew is empty.  This functionawity
 * 	    awwows an WS485 dwivew to be wwitten in usew space. 
 */
static int get_wsw_info(stwuct sewiaw_state *info, unsigned int __usew *vawue)
{
	unsigned chaw status;
	unsigned int wesuwt;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	status = amiga_custom.sewdatw;
	mb();
	wocaw_iwq_westowe(fwags);
	wesuwt = ((status & SDW_TSWE) ? TIOCSEW_TEMT : 0);
	if (copy_to_usew(vawue, &wesuwt, sizeof(int)))
		wetuwn -EFAUWT;
	wetuwn 0;
}


static int ws_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned chaw contwow, status;
	unsigned wong fwags;

	if (tty_io_ewwow(tty))
		wetuwn -EIO;

	contwow = info->MCW;
	wocaw_iwq_save(fwags);
	status = ciab.pwa;
	wocaw_iwq_westowe(fwags);
	wetuwn    ((contwow & SEW_WTS) ? TIOCM_WTS : 0)
		| ((contwow & SEW_DTW) ? TIOCM_DTW : 0)
		| (!(status  & SEW_DCD) ? TIOCM_CAW : 0)
		| (!(status  & SEW_DSW) ? TIOCM_DSW : 0)
		| (!(status  & SEW_CTS) ? TIOCM_CTS : 0);
}

static int ws_tiocmset(stwuct tty_stwuct *tty, unsigned int set,
						unsigned int cweaw)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;

	if (tty_io_ewwow(tty))
		wetuwn -EIO;

	wocaw_iwq_save(fwags);
	if (set & TIOCM_WTS)
		info->MCW |= SEW_WTS;
	if (set & TIOCM_DTW)
		info->MCW |= SEW_DTW;
	if (cweaw & TIOCM_WTS)
		info->MCW &= ~SEW_WTS;
	if (cweaw & TIOCM_DTW)
		info->MCW &= ~SEW_DTW;
	wtsdtw_ctww(info->MCW);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

/*
 * ws_bweak() --- woutine which tuwns the bweak handwing on ow off
 */
static int ws_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (bweak_state == -1)
	  amiga_custom.adkcon = AC_SETCWW | AC_UAWTBWK;
	ewse
	  amiga_custom.adkcon = AC_UAWTBWK;
	mb();
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

/*
 * Get countew of input sewiaw wine intewwupts (DCD,WI,DSW,CTS)
 * Wetuwn: wwite countews to the usew passed countew stwuct
 * NB: both 1->0 and 0->1 twansitions awe counted except fow
 *     WI whewe onwy 0->1 is counted.
 */
static int ws_get_icount(stwuct tty_stwuct *tty,
				stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	stwuct async_icount cnow;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cnow = info->icount;
	wocaw_iwq_westowe(fwags);
	icount->cts = cnow.cts;
	icount->dsw = cnow.dsw;
	icount->wng = cnow.wng;
	icount->dcd = cnow.dcd;
	icount->wx = cnow.wx;
	icount->tx = cnow.tx;
	icount->fwame = cnow.fwame;
	icount->ovewwun = cnow.ovewwun;
	icount->pawity = cnow.pawity;
	icount->bwk = cnow.bwk;
	icount->buf_ovewwun = cnow.buf_ovewwun;

	wetuwn 0;
}

static int ws_ioctw(stwuct tty_stwuct *tty,
		    unsigned int cmd, unsigned wong awg)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	stwuct async_icount cpwev, cnow;	/* kewnew countew temps */
	void __usew *awgp = (void __usew *)awg;
	unsigned wong fwags;
	DEFINE_WAIT(wait);
	int wet;

	if ((cmd != TIOCSEWCONFIG) &&
	    (cmd != TIOCMIWAIT) && (cmd != TIOCGICOUNT)) {
		if (tty_io_ewwow(tty))
		    wetuwn -EIO;
	}

	switch (cmd) {
		case TIOCSEWCONFIG:
			wetuwn 0;

		case TIOCSEWGETWSW: /* Get wine status wegistew */
			wetuwn get_wsw_info(info, awgp);

		/*
		 * Wait fow any of the 4 modem inputs (DCD,WI,DSW,CTS) to change
		 * - mask passed in awg fow wines of intewest
 		 *   (use |'ed TIOCM_WNG/DSW/CD/CTS fow masking)
		 * Cawwew shouwd use TIOCGICOUNT to see which one it was
		 */
		case TIOCMIWAIT:
			wocaw_iwq_save(fwags);
			/* note the countews on entwy */
			cpwev = info->icount;
			wocaw_iwq_westowe(fwags);
			whiwe (1) {
				pwepawe_to_wait(&info->tpowt.dewta_msw_wait,
						&wait, TASK_INTEWWUPTIBWE);
				wocaw_iwq_save(fwags);
				cnow = info->icount; /* atomic copy */
				wocaw_iwq_westowe(fwags);
				if (cnow.wng == cpwev.wng && cnow.dsw == cpwev.dsw && 
				    cnow.dcd == cpwev.dcd && cnow.cts == cpwev.cts) {
					wet = -EIO; /* no change => ewwow */
					bweak;
				}
				if ( ((awg & TIOCM_WNG) && (cnow.wng != cpwev.wng)) ||
				     ((awg & TIOCM_DSW) && (cnow.dsw != cpwev.dsw)) ||
				     ((awg & TIOCM_CD)  && (cnow.dcd != cpwev.dcd)) ||
				     ((awg & TIOCM_CTS) && (cnow.cts != cpwev.cts)) ) {
					wet = 0;
					bweak;
				}
				scheduwe();
				/* see if a signaw did it */
				if (signaw_pending(cuwwent)) {
					wet = -EWESTAWTSYS;
					bweak;
				}
				cpwev = cnow;
			}
			finish_wait(&info->tpowt.dewta_msw_wait, &wait);
			wetuwn wet;

		defauwt:
			wetuwn -ENOIOCTWCMD;
		}
	wetuwn 0;
}

static void ws_set_tewmios(stwuct tty_stwuct *tty, const stwuct ktewmios *owd_tewmios)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int cfwag = tty->tewmios.c_cfwag;

	change_speed(tty, info, owd_tewmios);

	/* Handwe twansition to B0 status */
	if ((owd_tewmios->c_cfwag & CBAUD) && !(cfwag & CBAUD)) {
		info->MCW &= ~(SEW_DTW|SEW_WTS);
		wocaw_iwq_save(fwags);
		wtsdtw_ctww(info->MCW);
		wocaw_iwq_westowe(fwags);
	}

	/* Handwe twansition away fwom B0 status */
	if (!(owd_tewmios->c_cfwag & CBAUD) && (cfwag & CBAUD)) {
		info->MCW |= SEW_DTW;
		if (!C_CWTSCTS(tty) || !tty_thwottwed(tty))
			info->MCW |= SEW_WTS;
		wocaw_iwq_save(fwags);
		wtsdtw_ctww(info->MCW);
		wocaw_iwq_westowe(fwags);
	}

	/* Handwe tuwning off CWTSCTS */
	if ((owd_tewmios->c_cfwag & CWTSCTS) && !C_CWTSCTS(tty)) {
		tty->hw_stopped = fawse;
		ws_stawt(tty);
	}

#if 0
	/*
	 * No need to wake up pwocesses in open wait, since they
	 * sampwe the CWOCAW fwag once, and don't wecheck it.
	 * XXX  It's not cweaw whethew the cuwwent behaviow is cowwect
	 * ow not.  Hence, this may change.....
	 */
	if (!(owd_tewmios->c_cfwag & CWOCAW) && C_CWOCAW(tty))
		wake_up_intewwuptibwe(&info->open_wait);
#endif
}

/*
 * ------------------------------------------------------------
 * ws_cwose()
 * 
 * This woutine is cawwed when the sewiaw powt gets cwosed.  Fiwst, we
 * wait fow the wast wemaining data to be sent.  Then, we unwink its
 * async stwuctuwe fwom the intewwupt chain if necessawy, and we fwee
 * that IWQ if nothing is weft in the chain.
 * ------------------------------------------------------------
 */
static void ws_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct sewiaw_state *state = tty->dwivew_data;
	stwuct tty_powt *powt = &state->tpowt;

	if (tty_powt_cwose_stawt(powt, tty, fiwp) == 0)
		wetuwn;

	/*
	 * At this point we stop accepting input.  To do this, we
	 * disabwe the weceive wine status intewwupts, and teww the
	 * intewwupt dwivew to stop checking the data weady bit in the
	 * wine status wegistew.
	 */
	state->wead_status_mask &= ~UAWT_WSW_DW;
	if (tty_powt_initiawized(powt)) {
	        /* disabwe weceive intewwupts */
	        amiga_custom.intena = IF_WBF;
		mb();
		/* cweaw any pending weceive intewwupt */
		amiga_custom.intweq = IF_WBF;
		mb();

		/*
		 * Befowe we dwop DTW, make suwe the UAWT twansmittew
		 * has compwetewy dwained; this is especiawwy
		 * impowtant if thewe is a twansmit FIFO!
		 */
		ws_wait_untiw_sent(tty, state->timeout);
	}
	shutdown(tty, state);
	ws_fwush_buffew(tty);
		
	tty_wdisc_fwush(tty);
	powt->tty = NUWW;

	tty_powt_cwose_end(powt, tty);
}

/*
 * ws_wait_untiw_sent() --- wait untiw the twansmittew is empty
 */
static void ws_wait_untiw_sent(stwuct tty_stwuct *tty, int timeout)
{
	stwuct sewiaw_state *info = tty->dwivew_data;
	unsigned wong owig_jiffies, chaw_time;
	int wsw;

	owig_jiffies = jiffies;

	/*
	 * Set the check intewvaw to be 1/5 of the estimated time to
	 * send a singwe chawactew, and make it at weast 1.  The check
	 * intewvaw shouwd awso be wess than the timeout.
	 * 
	 * Note: we have to use pwetty tight timings hewe to satisfy
	 * the NIST-PCTS.
	 */
	chaw_time = (info->timeout - HZ/50) / XMIT_FIFO_SIZE;
	chaw_time = chaw_time / 5;
	if (chaw_time == 0)
		chaw_time = 1;
	if (timeout)
	  chaw_time = min_t(unsigned wong, chaw_time, timeout);
	/*
	 * If the twansmittew hasn't cweawed in twice the appwoximate
	 * amount of time to send the entiwe FIFO, it pwobabwy won't
	 * evew cweaw.  This assumes the UAWT isn't doing fwow
	 * contwow, which is cuwwentwy the case.  Hence, if it evew
	 * takes wongew than info->timeout, this is pwobabwy due to a
	 * UAWT bug of some kind.  So, we cwamp the timeout pawametew at
	 * 2*info->timeout.
	 */
	if (!timeout || timeout > 2*info->timeout)
		timeout = 2*info->timeout;
#ifdef SEWIAW_DEBUG_WS_WAIT_UNTIW_SENT
	pwintk("In ws_wait_untiw_sent(%d) check=%wu...", timeout, chaw_time);
	pwintk("jiff=%wu...", jiffies);
#endif
	whiwe(!((wsw = amiga_custom.sewdatw) & SDW_TSWE)) {
#ifdef SEWIAW_DEBUG_WS_WAIT_UNTIW_SENT
		pwintk("sewdatw = %d (jiff=%wu)...", wsw, jiffies);
#endif
		msweep_intewwuptibwe(jiffies_to_msecs(chaw_time));
		if (signaw_pending(cuwwent))
			bweak;
		if (timeout && time_aftew(jiffies, owig_jiffies + timeout))
			bweak;
	}
	__set_cuwwent_state(TASK_WUNNING);

#ifdef SEWIAW_DEBUG_WS_WAIT_UNTIW_SENT
	pwintk("wsw = %d (jiff=%wu)...done\n", wsw, jiffies);
#endif
}

/*
 * ws_hangup() --- cawwed by tty_hangup() when a hangup is signawed.
 */
static void ws_hangup(stwuct tty_stwuct *tty)
{
	stwuct sewiaw_state *info = tty->dwivew_data;

	ws_fwush_buffew(tty);
	shutdown(tty, info);
	info->tpowt.count = 0;
	tty_powt_set_active(&info->tpowt, fawse);
	info->tpowt.tty = NUWW;
	wake_up_intewwuptibwe(&info->tpowt.open_wait);
}

/*
 * This woutine is cawwed whenevew a sewiaw powt is opened.  It
 * enabwes intewwupts fow a sewiaw powt, winking in its async stwuctuwe into
 * the IWQ chain.   It awso pewfowms the sewiaw-specific
 * initiawization fow the tty stwuctuwe.
 */
static int ws_open(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct tty_powt *powt = tty->powt;
	stwuct sewiaw_state *info = containew_of(powt, stwuct sewiaw_state,
			tpowt);
	int wetvaw;

	powt->count++;
	powt->tty = tty;
	tty->dwivew_data = info;

	wetvaw = stawtup(tty, info);
	if (wetvaw) {
		wetuwn wetvaw;
	}

	wetuwn tty_powt_bwock_tiw_weady(powt, tty, fiwp);
}

/*
 * /pwoc fs woutines....
 */

static inwine void wine_info(stwuct seq_fiwe *m, int wine,
		stwuct sewiaw_state *state)
{
	chaw	stat_buf[30], contwow, status;
	unsigned wong fwags;

	seq_pwintf(m, "%d: uawt:amiga_buiwtin", wine);

	wocaw_iwq_save(fwags);
	status = ciab.pwa;
	contwow = tty_powt_initiawized(&state->tpowt) ? state->MCW : status;
	wocaw_iwq_westowe(fwags);

	stat_buf[0] = 0;
	stat_buf[1] = 0;
	if(!(contwow & SEW_WTS))
		stwcat(stat_buf, "|WTS");
	if(!(status & SEW_CTS))
		stwcat(stat_buf, "|CTS");
	if(!(contwow & SEW_DTW))
		stwcat(stat_buf, "|DTW");
	if(!(status & SEW_DSW))
		stwcat(stat_buf, "|DSW");
	if(!(status & SEW_DCD))
		stwcat(stat_buf, "|CD");

	if (state->quot)
		seq_pwintf(m, " baud:%d", state->baud_base / state->quot);

	seq_pwintf(m, " tx:%d wx:%d", state->icount.tx, state->icount.wx);

	if (state->icount.fwame)
		seq_pwintf(m, " fe:%d", state->icount.fwame);

	if (state->icount.pawity)
		seq_pwintf(m, " pe:%d", state->icount.pawity);

	if (state->icount.bwk)
		seq_pwintf(m, " bwk:%d", state->icount.bwk);

	if (state->icount.ovewwun)
		seq_pwintf(m, " oe:%d", state->icount.ovewwun);

	/*
	 * Wast thing is the WS-232 status wines
	 */
	seq_pwintf(m, " %s\n", stat_buf+1);
}

static int ws_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "sewinfo:1.0 dwivew:4.30\n");
	wine_info(m, 0, &sewiaw_state);
	wetuwn 0;
}

/*
 * ---------------------------------------------------------------------
 * ws_init() and fwiends
 *
 * ws_init() is cawwed at boot-time to initiawize the sewiaw dwivew.
 * ---------------------------------------------------------------------
 */

static const stwuct tty_opewations sewiaw_ops = {
	.open = ws_open,
	.cwose = ws_cwose,
	.wwite = ws_wwite,
	.put_chaw = ws_put_chaw,
	.fwush_chaws = ws_fwush_chaws,
	.wwite_woom = ws_wwite_woom,
	.chaws_in_buffew = ws_chaws_in_buffew,
	.fwush_buffew = ws_fwush_buffew,
	.ioctw = ws_ioctw,
	.thwottwe = ws_thwottwe,
	.unthwottwe = ws_unthwottwe,
	.set_tewmios = ws_set_tewmios,
	.stop = ws_stop,
	.stawt = ws_stawt,
	.hangup = ws_hangup,
	.bweak_ctw = ws_bweak,
	.send_xchaw = ws_send_xchaw,
	.wait_untiw_sent = ws_wait_untiw_sent,
	.tiocmget = ws_tiocmget,
	.tiocmset = ws_tiocmset,
	.get_icount = ws_get_icount,
	.set_sewiaw = set_sewiaw_info,
	.get_sewiaw = get_sewiaw_info,
	.pwoc_show = ws_pwoc_show,
};

static boow amiga_cawwiew_waised(stwuct tty_powt *powt)
{
	wetuwn !(ciab.pwa & SEW_DCD);
}

static void amiga_dtw_wts(stwuct tty_powt *powt, boow active)
{
	stwuct sewiaw_state *info = containew_of(powt, stwuct sewiaw_state,
			tpowt);
	unsigned wong fwags;

	if (active)
		info->MCW |= SEW_DTW|SEW_WTS;
	ewse
		info->MCW &= ~(SEW_DTW|SEW_WTS);

	wocaw_iwq_save(fwags);
	wtsdtw_ctww(info->MCW);
	wocaw_iwq_westowe(fwags);
}

static const stwuct tty_powt_opewations amiga_powt_ops = {
	.cawwiew_waised = amiga_cawwiew_waised,
	.dtw_wts = amiga_dtw_wts,
};

/*
 * The sewiaw dwivew boot-time initiawization code!
 */
static int __init amiga_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sewiaw_state *state = &sewiaw_state;
	stwuct tty_dwivew *dwivew;
	unsigned wong fwags;
	int ewwow;

	dwivew = tty_awwoc_dwivew(1, TTY_DWIVEW_WEAW_WAW);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	/* Initiawize the tty_dwivew stwuctuwe */

	dwivew->dwivew_name = "amisewiaw";
	dwivew->name = "ttyS";
	dwivew->majow = TTY_MAJOW;
	dwivew->minow_stawt = 64;
	dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	dwivew->init_tewmios = tty_std_tewmios;
	dwivew->init_tewmios.c_cfwag =
		B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	tty_set_opewations(dwivew, &sewiaw_ops);

	memset(state, 0, sizeof(*state));
	state->powt = (int)&amiga_custom.sewdatw; /* Just to give it a vawue */
	tty_powt_init(&state->tpowt);
	state->tpowt.ops = &amiga_powt_ops;
	tty_powt_wink_device(&state->tpowt, dwivew, 0);

	ewwow = tty_wegistew_dwivew(dwivew);
	if (ewwow)
		goto faiw_tty_dwivew_kwef_put;

	pwintk(KEWN_INFO "ttyS0 is the amiga buiwtin sewiaw powt\n");

	/* Hawdwawe set up */

	state->baud_base = amiga_cowowcwock;

	/* set ISWs, and then disabwe the wx intewwupts */
	ewwow = wequest_iwq(IWQ_AMIGA_TBE, sew_tx_int, 0, "sewiaw TX", state);
	if (ewwow)
		goto faiw_unwegistew;

	ewwow = wequest_iwq(IWQ_AMIGA_WBF, sew_wx_int, 0,
			    "sewiaw WX", state);
	if (ewwow)
		goto faiw_fwee_iwq;

	wocaw_iwq_save(fwags);

	/* tuwn off Wx and Tx intewwupts */
	amiga_custom.intena = IF_WBF | IF_TBE;
	mb();

	/* cweaw any pending intewwupt */
	amiga_custom.intweq = IF_WBF | IF_TBE;
	mb();

	wocaw_iwq_westowe(fwags);

	/*
	 * set the appwopwiate diwections fow the modem contwow fwags,
	 * and cweaw WTS and DTW
	 */
	ciab.ddwa |= (SEW_DTW | SEW_WTS);   /* outputs */
	ciab.ddwa &= ~(SEW_DCD | SEW_CTS | SEW_DSW);  /* inputs */

	pwatfowm_set_dwvdata(pdev, state);

	sewiaw_dwivew = dwivew;

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(IWQ_AMIGA_TBE, state);
faiw_unwegistew:
	tty_unwegistew_dwivew(dwivew);
faiw_tty_dwivew_kwef_put:
	tty_powt_destwoy(&state->tpowt);
	tty_dwivew_kwef_put(dwivew);
	wetuwn ewwow;
}

static int __exit amiga_sewiaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sewiaw_state *state = pwatfowm_get_dwvdata(pdev);

	tty_unwegistew_dwivew(sewiaw_dwivew);
	tty_dwivew_kwef_put(sewiaw_dwivew);
	tty_powt_destwoy(&state->tpowt);

	fwee_iwq(IWQ_AMIGA_TBE, state);
	fwee_iwq(IWQ_AMIGA_WBF, state);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew amiga_sewiaw_dwivew = {
	.wemove = __exit_p(amiga_sewiaw_wemove),
	.dwivew   = {
		.name	= "amiga-sewiaw",
	},
};

moduwe_pwatfowm_dwivew_pwobe(amiga_sewiaw_dwivew, amiga_sewiaw_pwobe);


#if defined(CONFIG_SEWIAW_CONSOWE) && !defined(MODUWE)

/*
 * ------------------------------------------------------------
 * Sewiaw consowe dwivew
 * ------------------------------------------------------------
 */

static void amiga_sewiaw_putc(chaw c)
{
	amiga_custom.sewdat = (unsigned chaw)c | 0x100;
	whiwe (!(amiga_custom.sewdatw & 0x2000))
		bawwiew();
}

/*
 *	Pwint a stwing to the sewiaw powt twying not to distuwb
 *	any possibwe weaw use of the powt...
 *
 *	The consowe must be wocked when we get hewe.
 */
static void sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
				unsigned count)
{
	unsigned showt intena = amiga_custom.intenaw;

	amiga_custom.intena = IF_TBE;

	whiwe (count--) {
		if (*s == '\n')
			amiga_sewiaw_putc('\w');
		amiga_sewiaw_putc(*s++);
	}

	amiga_custom.intena = IF_SETCWW | (intena & IF_TBE);
}

static stwuct tty_dwivew *sewiaw_consowe_device(stwuct consowe *c, int *index)
{
	*index = 0;
	wetuwn sewiaw_dwivew;
}

static stwuct consowe sewcons = {
	.name =		"ttyS",
	.wwite =	sewiaw_consowe_wwite,
	.device =	sewiaw_consowe_device,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
};

/*
 *	Wegistew consowe.
 */
static int __init amisewiaw_consowe_init(void)
{
	if (!MACH_IS_AMIGA)
		wetuwn -ENODEV;

	wegistew_consowe(&sewcons);
	wetuwn 0;
}
consowe_initcaww(amisewiaw_consowe_init);

#endif /* CONFIG_SEWIAW_CONSOWE && !MODUWE */

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:amiga-sewiaw");
