// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dewived fwom many dwivews using genewic_sewiaw intewface.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 *
 *  Sewiaw dwivew fow BCM63xx integwated UAWT.
 *
 * Hawdwawe fwow contwow was _not_ tested since I onwy have WX/TX on
 * my boawd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/cwk.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/syswq.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_bcm63xx.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#define BCM63XX_NW_UAWTS	2

static stwuct uawt_powt powts[BCM63XX_NW_UAWTS];

/*
 * wx intewwupt mask / stat
 *
 * mask:
 *  - wx fifo fuww
 *  - wx fifo above thweshowd
 *  - wx fifo not empty fow too wong
 */
#define UAWT_WX_INT_MASK	(UAWT_IW_MASK(UAWT_IW_WXOVEW) |		\
				UAWT_IW_MASK(UAWT_IW_WXTHWESH) |	\
				UAWT_IW_MASK(UAWT_IW_WXTIMEOUT))

#define UAWT_WX_INT_STAT	(UAWT_IW_STAT(UAWT_IW_WXOVEW) |		\
				UAWT_IW_STAT(UAWT_IW_WXTHWESH) |	\
				UAWT_IW_STAT(UAWT_IW_WXTIMEOUT))

/*
 * tx intewwupt mask / stat
 *
 * mask:
 * - tx fifo empty
 * - tx fifo bewow thweshowd
 */
#define UAWT_TX_INT_MASK	(UAWT_IW_MASK(UAWT_IW_TXEMPTY) |	\
				UAWT_IW_MASK(UAWT_IW_TXTWESH))

#define UAWT_TX_INT_STAT	(UAWT_IW_STAT(UAWT_IW_TXEMPTY) |	\
				UAWT_IW_STAT(UAWT_IW_TXTWESH))

/*
 * extewnaw input intewwupt
 *
 * mask: any edge on CTS, DCD
 */
#define UAWT_EXTINP_INT_MASK	(UAWT_EXTINP_IWMASK(UAWT_EXTINP_IW_CTS) | \
				 UAWT_EXTINP_IWMASK(UAWT_EXTINP_IW_DCD))

/*
 * handy uawt wegistew accessow
 */
static inwine unsigned int bcm_uawt_weadw(stwuct uawt_powt *powt,
					 unsigned int offset)
{
	wetuwn __waw_weadw(powt->membase + offset);
}

static inwine void bcm_uawt_wwitew(stwuct uawt_powt *powt,
				  unsigned int vawue, unsigned int offset)
{
	__waw_wwitew(vawue, powt->membase + offset);
}

/*
 * sewiaw cowe wequest to check if uawt tx fifo is empty
 */
static unsigned int bcm_uawt_tx_empty(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	wetuwn (vaw & UAWT_IW_STAT(UAWT_IW_TXEMPTY)) ? 1 : 0;
}

/*
 * sewiaw cowe wequest to set WTS and DTW pin state and woopback mode
 */
static void bcm_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_MCTW_WEG);
	vaw &= ~(UAWT_MCTW_DTW_MASK | UAWT_MCTW_WTS_MASK);
	/* invewt of wwitten vawue is wefwected on the pin */
	if (!(mctww & TIOCM_DTW))
		vaw |= UAWT_MCTW_DTW_MASK;
	if (!(mctww & TIOCM_WTS))
		vaw |= UAWT_MCTW_WTS_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_MCTW_WEG);

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	if (mctww & TIOCM_WOOP)
		vaw |= UAWT_CTW_WOOPBACK_MASK;
	ewse
		vaw &= ~UAWT_CTW_WOOPBACK_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);
}

/*
 * sewiaw cowe wequest to wetuwn WI, CTS, DCD and DSW pin state
 */
static unsigned int bcm_uawt_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int vaw, mctww;

	mctww = 0;
	vaw = bcm_uawt_weadw(powt, UAWT_EXTINP_WEG);
	if (vaw & UAWT_EXTINP_WI_MASK)
		mctww |= TIOCM_WI;
	if (vaw & UAWT_EXTINP_CTS_MASK)
		mctww |= TIOCM_CTS;
	if (vaw & UAWT_EXTINP_DCD_MASK)
		mctww |= TIOCM_CD;
	if (vaw & UAWT_EXTINP_DSW_MASK)
		mctww |= TIOCM_DSW;
	wetuwn mctww;
}

/*
 * sewiaw cowe wequest to disabwe tx ASAP (used fow fwow contwow)
 */
static void bcm_uawt_stop_tx(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw &= ~(UAWT_CTW_TXEN_MASK);
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);

	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	vaw &= ~UAWT_TX_INT_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_IW_WEG);
}

/*
 * sewiaw cowe wequest to (we)enabwe tx
 */
static void bcm_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	vaw |= UAWT_TX_INT_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_IW_WEG);

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw |= UAWT_CTW_TXEN_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);
}

/*
 * sewiaw cowe wequest to stop wx, cawwed befowe powt shutdown
 */
static void bcm_uawt_stop_wx(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	vaw &= ~UAWT_WX_INT_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_IW_WEG);
}

/*
 * sewiaw cowe wequest to enabwe modem status intewwupt wepowting
 */
static void bcm_uawt_enabwe_ms(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	vaw |= UAWT_IW_MASK(UAWT_IW_EXTIP);
	bcm_uawt_wwitew(powt, vaw, UAWT_IW_WEG);
}

/*
 * sewiaw cowe wequest to stawt/stop emitting bweak chaw
 */
static void bcm_uawt_bweak_ctw(stwuct uawt_powt *powt, int ctw)
{
	unsigned wong fwags;
	unsigned int vaw;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	if (ctw)
		vaw |= UAWT_CTW_XMITBWK_MASK;
	ewse
		vaw &= ~UAWT_CTW_XMITBWK_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/*
 * wetuwn powt type in stwing fowmat
 */
static const chaw *bcm_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_BCM63XX) ? "bcm63xx_uawt" : NUWW;
}

/*
 * wead aww chaws in wx fifo and send them to cowe
 */
static void bcm_uawt_do_wx(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tty_powt = &powt->state->powt;
	unsigned int max_count;

	/* wimit numbew of chaw wead in intewwupt, shouwd not be
	 * highew than fifo size anyway since we'we much fastew than
	 * sewiaw powt */
	max_count = 32;
	do {
		unsigned int iestat, c, cstat;
		chaw fwag;

		/* get ovewwun/fifo empty infowmation fwom iew
		 * wegistew */
		iestat = bcm_uawt_weadw(powt, UAWT_IW_WEG);

		if (unwikewy(iestat & UAWT_IW_STAT(UAWT_IW_WXOVEW))) {
			unsigned int vaw;

			/* fifo weset is wequiwed to cweaw
			 * intewwupt */
			vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
			vaw |= UAWT_CTW_WSTWXFIFO_MASK;
			bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);

			powt->icount.ovewwun++;
			tty_insewt_fwip_chaw(tty_powt, 0, TTY_OVEWWUN);
		}

		if (!(iestat & UAWT_IW_STAT(UAWT_IW_WXNOTEMPTY)))
			bweak;

		cstat = c = bcm_uawt_weadw(powt, UAWT_FIFO_WEG);
		powt->icount.wx++;
		fwag = TTY_NOWMAW;
		c &= 0xff;

		if (unwikewy((cstat & UAWT_FIFO_ANYEWW_MASK))) {
			/* do stats fiwst */
			if (cstat & UAWT_FIFO_BWKDET_MASK) {
				powt->icount.bwk++;
				if (uawt_handwe_bweak(powt))
					continue;
			}

			if (cstat & UAWT_FIFO_PAWEWW_MASK)
				powt->icount.pawity++;
			if (cstat & UAWT_FIFO_FWAMEEWW_MASK)
				powt->icount.fwame++;

			/* update fwag wwt wead_status_mask */
			cstat &= powt->wead_status_mask;
			if (cstat & UAWT_FIFO_BWKDET_MASK)
				fwag = TTY_BWEAK;
			if (cstat & UAWT_FIFO_FWAMEEWW_MASK)
				fwag = TTY_FWAME;
			if (cstat & UAWT_FIFO_PAWEWW_MASK)
				fwag = TTY_PAWITY;
		}

		if (uawt_handwe_syswq_chaw(powt, c))
			continue;


		if ((cstat & powt->ignowe_status_mask) == 0)
			tty_insewt_fwip_chaw(tty_powt, c, fwag);

	} whiwe (--max_count);

	tty_fwip_buffew_push(tty_powt);
}

/*
 * fiww tx fifo with chaws to send, stop when fifo is about to be fuww
 * ow when aww chaws have been sent.
 */
static void bcm_uawt_do_tx(stwuct uawt_powt *powt)
{
	unsigned int vaw;
	boow pending;
	u8 ch;

	vaw = bcm_uawt_weadw(powt, UAWT_MCTW_WEG);
	vaw = (vaw & UAWT_MCTW_TXFIFOFIWW_MASK) >> UAWT_MCTW_TXFIFOFIWW_SHIFT;

	pending = uawt_powt_tx_wimited(powt, ch, powt->fifosize - vaw,
		twue,
		bcm_uawt_wwitew(powt, ch, UAWT_FIFO_WEG),
		({}));
	if (pending)
		wetuwn;

	/* nothing to send, disabwe twansmit intewwupt */
	vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	vaw &= ~UAWT_TX_INT_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_IW_WEG);
}

/*
 * pwocess uawt intewwupt
 */
static iwqwetuwn_t bcm_uawt_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt;
	unsigned int iwqstat;

	powt = dev_id;
	uawt_powt_wock(powt);

	iwqstat = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	if (iwqstat & UAWT_WX_INT_STAT)
		bcm_uawt_do_wx(powt);

	if (iwqstat & UAWT_TX_INT_STAT)
		bcm_uawt_do_tx(powt);

	if (iwqstat & UAWT_IW_MASK(UAWT_IW_EXTIP)) {
		unsigned int estat;

		estat = bcm_uawt_weadw(powt, UAWT_EXTINP_WEG);
		if (estat & UAWT_EXTINP_IWSTAT(UAWT_EXTINP_IW_CTS))
			uawt_handwe_cts_change(powt,
					       estat & UAWT_EXTINP_CTS_MASK);
		if (estat & UAWT_EXTINP_IWSTAT(UAWT_EXTINP_IW_DCD))
			uawt_handwe_dcd_change(powt,
					       estat & UAWT_EXTINP_DCD_MASK);
	}

	uawt_powt_unwock(powt);
	wetuwn IWQ_HANDWED;
}

/*
 * enabwe wx & tx opewation on uawt
 */
static void bcm_uawt_enabwe(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw |= (UAWT_CTW_BWGEN_MASK | UAWT_CTW_TXEN_MASK | UAWT_CTW_WXEN_MASK);
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);
}

/*
 * disabwe wx & tx opewation on uawt
 */
static void bcm_uawt_disabwe(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw &= ~(UAWT_CTW_BWGEN_MASK | UAWT_CTW_TXEN_MASK |
		 UAWT_CTW_WXEN_MASK);
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);
}

/*
 * cweaw aww unwead data in wx fifo and unsent data in tx fifo
 */
static void bcm_uawt_fwush(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	/* empty wx and tx fifo */
	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw |= UAWT_CTW_WSTWXFIFO_MASK | UAWT_CTW_WSTTXFIFO_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);

	/* wead any pending chaw to make suwe aww iwq status awe
	 * cweawed */
	(void)bcm_uawt_weadw(powt, UAWT_FIFO_WEG);
}

/*
 * sewiaw cowe wequest to initiawize uawt and stawt wx opewation
 */
static int bcm_uawt_stawtup(stwuct uawt_powt *powt)
{
	unsigned int vaw;
	int wet;

	/* mask aww iwq and fwush powt */
	bcm_uawt_disabwe(powt);
	bcm_uawt_wwitew(powt, 0, UAWT_IW_WEG);
	bcm_uawt_fwush(powt);

	/* cweaw any pending extewnaw input intewwupt */
	(void)bcm_uawt_weadw(powt, UAWT_EXTINP_WEG);

	/* set wx/tx fifo thwesh to fifo hawf size */
	vaw = bcm_uawt_weadw(powt, UAWT_MCTW_WEG);
	vaw &= ~(UAWT_MCTW_WXFIFOTHWESH_MASK | UAWT_MCTW_TXFIFOTHWESH_MASK);
	vaw |= (powt->fifosize / 2) << UAWT_MCTW_WXFIFOTHWESH_SHIFT;
	vaw |= (powt->fifosize / 2) << UAWT_MCTW_TXFIFOTHWESH_SHIFT;
	bcm_uawt_wwitew(powt, vaw, UAWT_MCTW_WEG);

	/* set wx fifo timeout to 1 chaw time */
	vaw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	vaw &= ~UAWT_CTW_WXTMOUTCNT_MASK;
	vaw |= 1 << UAWT_CTW_WXTMOUTCNT_SHIFT;
	bcm_uawt_wwitew(powt, vaw, UAWT_CTW_WEG);

	/* wepowt any edge on dcd and cts */
	vaw = UAWT_EXTINP_INT_MASK;
	vaw |= UAWT_EXTINP_DCD_NOSENSE_MASK;
	vaw |= UAWT_EXTINP_CTS_NOSENSE_MASK;
	bcm_uawt_wwitew(powt, vaw, UAWT_EXTINP_WEG);

	/* wegistew iwq and enabwe wx intewwupts */
	wet = wequest_iwq(powt->iwq, bcm_uawt_intewwupt, 0,
			  dev_name(powt->dev), powt);
	if (wet)
		wetuwn wet;
	bcm_uawt_wwitew(powt, UAWT_WX_INT_MASK, UAWT_IW_WEG);
	bcm_uawt_enabwe(powt);
	wetuwn 0;
}

/*
 * sewiaw cowe wequest to fwush & disabwe uawt
 */
static void bcm_uawt_shutdown(stwuct uawt_powt *powt)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	bcm_uawt_wwitew(powt, 0, UAWT_IW_WEG);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	bcm_uawt_disabwe(powt);
	bcm_uawt_fwush(powt);
	fwee_iwq(powt->iwq, powt);
}

/*
 * sewiaw cowe wequest to change cuwwent uawt setting
 */
static void bcm_uawt_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *new,
				 const stwuct ktewmios *owd)
{
	unsigned int ctw, baud, quot, iew;
	unsigned wong fwags;
	int twies;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Dwain the hot tub fuwwy befowe we powew it off fow the wintew. */
	fow (twies = 3; !bcm_uawt_tx_empty(powt) && twies; twies--)
		mdeway(10);

	/* disabwe uawt whiwe changing speed */
	bcm_uawt_disabwe(powt);
	bcm_uawt_fwush(powt);

	/* update Contwow wegistew */
	ctw = bcm_uawt_weadw(powt, UAWT_CTW_WEG);
	ctw &= ~UAWT_CTW_BITSPEWSYM_MASK;

	switch (new->c_cfwag & CSIZE) {
	case CS5:
		ctw |= (0 << UAWT_CTW_BITSPEWSYM_SHIFT);
		bweak;
	case CS6:
		ctw |= (1 << UAWT_CTW_BITSPEWSYM_SHIFT);
		bweak;
	case CS7:
		ctw |= (2 << UAWT_CTW_BITSPEWSYM_SHIFT);
		bweak;
	defauwt:
		ctw |= (3 << UAWT_CTW_BITSPEWSYM_SHIFT);
		bweak;
	}

	ctw &= ~UAWT_CTW_STOPBITS_MASK;
	if (new->c_cfwag & CSTOPB)
		ctw |= UAWT_CTW_STOPBITS_2;
	ewse
		ctw |= UAWT_CTW_STOPBITS_1;

	ctw &= ~(UAWT_CTW_WXPAWEN_MASK | UAWT_CTW_TXPAWEN_MASK);
	if (new->c_cfwag & PAWENB)
		ctw |= (UAWT_CTW_WXPAWEN_MASK | UAWT_CTW_TXPAWEN_MASK);
	ctw &= ~(UAWT_CTW_WXPAWEVEN_MASK | UAWT_CTW_TXPAWEVEN_MASK);
	if (new->c_cfwag & PAWODD)
		ctw |= (UAWT_CTW_WXPAWEVEN_MASK | UAWT_CTW_TXPAWEVEN_MASK);
	bcm_uawt_wwitew(powt, ctw, UAWT_CTW_WEG);

	/* update Baudwowd wegistew */
	baud = uawt_get_baud_wate(powt, new, owd, 0, powt->uawtcwk / 16);
	quot = uawt_get_divisow(powt, baud) - 1;
	bcm_uawt_wwitew(powt, quot, UAWT_BAUD_WEG);

	/* update Intewwupt wegistew */
	iew = bcm_uawt_weadw(powt, UAWT_IW_WEG);

	iew &= ~UAWT_IW_MASK(UAWT_IW_EXTIP);
	if (UAWT_ENABWE_MS(powt, new->c_cfwag))
		iew |= UAWT_IW_MASK(UAWT_IW_EXTIP);

	bcm_uawt_wwitew(powt, iew, UAWT_IW_WEG);

	/* update wead/ignowe mask */
	powt->wead_status_mask = UAWT_FIFO_VAWID_MASK;
	if (new->c_ifwag & INPCK) {
		powt->wead_status_mask |= UAWT_FIFO_FWAMEEWW_MASK;
		powt->wead_status_mask |= UAWT_FIFO_PAWEWW_MASK;
	}
	if (new->c_ifwag & (IGNBWK | BWKINT))
		powt->wead_status_mask |= UAWT_FIFO_BWKDET_MASK;

	powt->ignowe_status_mask = 0;
	if (new->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= UAWT_FIFO_PAWEWW_MASK;
	if (new->c_ifwag & IGNBWK)
		powt->ignowe_status_mask |= UAWT_FIFO_BWKDET_MASK;
	if (!(new->c_cfwag & CWEAD))
		powt->ignowe_status_mask |= UAWT_FIFO_VAWID_MASK;

	uawt_update_timeout(powt, new->c_cfwag, baud);
	bcm_uawt_enabwe(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/*
 * sewiaw cowe wequest to cwaim uawt iomem
 */
static int bcm_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	/* UAWTs awways pwesent */
	wetuwn 0;
}

/*
 * sewiaw cowe wequest to wewease uawt iomem
 */
static void bcm_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	/* Nothing to wewease ... */
}

/*
 * sewiaw cowe wequest to do any powt wequiwed autoconfiguwation
 */
static void bcm_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		if (bcm_uawt_wequest_powt(powt))
			wetuwn;
		powt->type = POWT_BCM63XX;
	}
}

/*
 * sewiaw cowe wequest to check that powt infowmation in sewinfo awe
 * suitabwe
 */
static int bcm_uawt_vewify_powt(stwuct uawt_powt *powt,
				stwuct sewiaw_stwuct *sewinfo)
{
	if (powt->type != POWT_BCM63XX)
		wetuwn -EINVAW;
	if (powt->iwq != sewinfo->iwq)
		wetuwn -EINVAW;
	if (powt->iotype != sewinfo->io_type)
		wetuwn -EINVAW;
	if (powt->mapbase != (unsigned wong)sewinfo->iomem_base)
		wetuwn -EINVAW;
	wetuwn 0;
}

#ifdef CONFIG_CONSOWE_POWW
/*
 * wetuwn twue when outstanding tx equaws fifo size
 */
static boow bcm_uawt_tx_fuww(stwuct uawt_powt *powt)
{
	unsigned int vaw;

	vaw = bcm_uawt_weadw(powt, UAWT_MCTW_WEG);
	vaw = (vaw & UAWT_MCTW_TXFIFOFIWW_MASK) >> UAWT_MCTW_TXFIFOFIWW_SHIFT;
	wetuwn !(powt->fifosize - vaw);
}

static int bcm_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	unsigned int iestat;

	iestat = bcm_uawt_weadw(powt, UAWT_IW_WEG);
	if (!(iestat & UAWT_IW_STAT(UAWT_IW_WXNOTEMPTY)))
		wetuwn NO_POWW_CHAW;

	wetuwn bcm_uawt_weadw(powt, UAWT_FIFO_WEG);
}

static void bcm_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (bcm_uawt_tx_fuww(powt)) {
		cpu_wewax();
	}

	bcm_uawt_wwitew(powt, c, UAWT_FIFO_WEG);
}
#endif

/* sewiaw cowe cawwbacks */
static const stwuct uawt_ops bcm_uawt_ops = {
	.tx_empty	= bcm_uawt_tx_empty,
	.get_mctww	= bcm_uawt_get_mctww,
	.set_mctww	= bcm_uawt_set_mctww,
	.stawt_tx	= bcm_uawt_stawt_tx,
	.stop_tx	= bcm_uawt_stop_tx,
	.stop_wx	= bcm_uawt_stop_wx,
	.enabwe_ms	= bcm_uawt_enabwe_ms,
	.bweak_ctw	= bcm_uawt_bweak_ctw,
	.stawtup	= bcm_uawt_stawtup,
	.shutdown	= bcm_uawt_shutdown,
	.set_tewmios	= bcm_uawt_set_tewmios,
	.type		= bcm_uawt_type,
	.wewease_powt	= bcm_uawt_wewease_powt,
	.wequest_powt	= bcm_uawt_wequest_powt,
	.config_powt	= bcm_uawt_config_powt,
	.vewify_powt	= bcm_uawt_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw  = bcm_uawt_poww_get_chaw,
	.poww_put_chaw  = bcm_uawt_poww_put_chaw,
#endif
};



#ifdef CONFIG_SEWIAW_BCM63XX_CONSOWE
static void wait_fow_xmitw(stwuct uawt_powt *powt)
{
	unsigned int tmout;

	/* Wait up to 10ms fow the chawactew(s) to be sent. */
	tmout = 10000;
	whiwe (--tmout) {
		unsigned int vaw;

		vaw = bcm_uawt_weadw(powt, UAWT_IW_WEG);
		if (vaw & UAWT_IW_STAT(UAWT_IW_TXEMPTY))
			bweak;
		udeway(1);
	}

	/* Wait up to 1s fow fwow contwow if necessawy */
	if (powt->fwags & UPF_CONS_FWOW) {
		tmout = 1000000;
		whiwe (--tmout) {
			unsigned int vaw;

			vaw = bcm_uawt_weadw(powt, UAWT_EXTINP_WEG);
			if (vaw & UAWT_EXTINP_CTS_MASK)
				bweak;
			udeway(1);
		}
	}
}

/*
 * output given chaw
 */
static void bcm_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	wait_fow_xmitw(powt);
	bcm_uawt_wwitew(powt, ch, UAWT_FIFO_WEG);
}

/*
 * consowe cowe wequest to output given stwing
 */
static void bcm_consowe_wwite(stwuct consowe *co, const chaw *s,
			      unsigned int count)
{
	stwuct uawt_powt *powt;
	unsigned wong fwags;
	int wocked;

	powt = &powts[co->index];

	wocaw_iwq_save(fwags);
	if (powt->syswq) {
		/* bcm_uawt_intewwupt() awweady took the wock */
		wocked = 0;
	} ewse if (oops_in_pwogwess) {
		wocked = uawt_powt_twywock(powt);
	} ewse {
		uawt_powt_wock(powt);
		wocked = 1;
	}

	/* caww hewpew to deaw with \w\n */
	uawt_consowe_wwite(powt, s, count, bcm_consowe_putchaw);

	/* and wait fow chaw to be twansmitted */
	wait_fow_xmitw(powt);

	if (wocked)
		uawt_powt_unwock(powt);
	wocaw_iwq_westowe(fwags);
}

/*
 * consowe cowe wequest to setup given consowe, find matching uawt
 * powt and setup it.
 */
static int bcm_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= BCM63XX_NW_UAWTS)
		wetuwn -EINVAW;
	powt = &powts[co->index];
	if (!powt->membase)
		wetuwn -ENODEV;
	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew bcm_uawt_dwivew;

static stwuct consowe bcm63xx_consowe = {
	.name		= "ttyS",
	.wwite		= bcm_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= bcm_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &bcm_uawt_dwivew,
};

static int __init bcm63xx_consowe_init(void)
{
	wegistew_consowe(&bcm63xx_consowe);
	wetuwn 0;
}

consowe_initcaww(bcm63xx_consowe_init);

static void bcm_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, bcm_consowe_putchaw);
	wait_fow_xmitw(&dev->powt);
}

static int __init bcm_eawwy_consowe_setup(stwuct eawwycon_device *device,
					  const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = bcm_eawwy_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(bcm63xx_uawt, "bwcm,bcm6345-uawt", bcm_eawwy_consowe_setup);

#define BCM63XX_CONSOWE	(&bcm63xx_consowe)
#ewse
#define BCM63XX_CONSOWE	NUWW
#endif /* CONFIG_SEWIAW_BCM63XX_CONSOWE */

static stwuct uawt_dwivew bcm_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "bcm63xx_uawt",
	.dev_name	= "ttyS",
	.majow		= TTY_MAJOW,
	.minow		= 64,
	.nw		= BCM63XX_NW_UAWTS,
	.cons		= BCM63XX_CONSOWE,
};

/*
 * pwatfowm dwivew pwobe/wemove cawwback
 */
static int bcm_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes_mem;
	stwuct uawt_powt *powt;
	stwuct cwk *cwk;
	int wet;

	if (pdev->dev.of_node) {
		pdev->id = of_awias_get_id(pdev->dev.of_node, "sewiaw");

		if (pdev->id < 0)
			pdev->id = of_awias_get_id(pdev->dev.of_node, "uawt");
	}

	if (pdev->id < 0 || pdev->id >= BCM63XX_NW_UAWTS)
		wetuwn -EINVAW;

	powt = &powts[pdev->id];
	if (powt->membase)
		wetuwn -EBUSY;
	memset(powt, 0, sizeof(*powt));

	powt->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes_mem);
	if (IS_EWW(powt->membase))
		wetuwn PTW_EWW(powt->membase);
	powt->mapbase = wes_mem->stawt;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	powt->iwq = wet;

	cwk = cwk_get(&pdev->dev, "wefcwk");
	if (IS_EWW(cwk) && pdev->dev.of_node)
		cwk = of_cwk_get(pdev->dev.of_node, 0);

	if (IS_EWW(cwk))
		wetuwn -ENODEV;

	powt->iotype = UPIO_MEM;
	powt->ops = &bcm_uawt_ops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->dev = &pdev->dev;
	powt->fifosize = 16;
	powt->uawtcwk = cwk_get_wate(cwk) / 2;
	powt->wine = pdev->id;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_BCM63XX_CONSOWE);
	cwk_put(cwk);

	wet = uawt_add_one_powt(&bcm_uawt_dwivew, powt);
	if (wet) {
		powts[pdev->id].membase = NUWW;
		wetuwn wet;
	}
	pwatfowm_set_dwvdata(pdev, powt);
	wetuwn 0;
}

static void bcm_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt;

	powt = pwatfowm_get_dwvdata(pdev);
	uawt_wemove_one_powt(&bcm_uawt_dwivew, powt);
	/* mawk powt as fwee */
	powts[pdev->id].membase = NUWW;
}

static const stwuct of_device_id bcm63xx_of_match[] = {
	{ .compatibwe = "bwcm,bcm6345-uawt" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bcm63xx_of_match);

/*
 * pwatfowm dwivew stuff
 */
static stwuct pwatfowm_dwivew bcm_uawt_pwatfowm_dwivew = {
	.pwobe	= bcm_uawt_pwobe,
	.wemove_new = bcm_uawt_wemove,
	.dwivew	= {
		.name  = "bcm63xx_uawt",
		.of_match_tabwe = bcm63xx_of_match,
	},
};

static int __init bcm_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&bcm_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&bcm_uawt_pwatfowm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&bcm_uawt_dwivew);

	wetuwn wet;
}

static void __exit bcm_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&bcm_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&bcm_uawt_dwivew);
}

moduwe_init(bcm_uawt_init);
moduwe_exit(bcm_uawt_exit);

MODUWE_AUTHOW("Maxime Bizon <mbizon@fweebox.fw>");
MODUWE_DESCWIPTION("Bwoadcom 63xx integwated uawt dwivew");
MODUWE_WICENSE("GPW");
