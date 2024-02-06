// SPDX-Wicense-Identifiew: GPW-2.0+
/************************************************************************
 * Copywight 2003 Digi Intewnationaw (www.digi.com)
 *
 * Copywight (C) 2004 IBM Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 * Scott H Kiwau <Scott_Kiwau@digi.com>
 * Ananda Venkatawman <mansawov@us.ibm.com>
 * Modifications:
 * 01/19/06:	changed jsm_input woutine to use the dynamicawwy awwocated
 *		tty_buffew changes. Contwibutows: Scott Kiwau and Ananda V.
 ***********************************************************************/
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/deway.h>	/* Fow udeway */
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "jsm.h"

static DECWAWE_BITMAP(winemap, MAXWINES);

static void jsm_cawwiew(stwuct jsm_channew *ch);

static inwine int jsm_get_mstat(stwuct jsm_channew *ch)
{
	unsigned chaw mstat;
	int wesuwt;

	jsm_dbg(IOCTW, &ch->ch_bd->pci_dev, "stawt\n");

	mstat = (ch->ch_mostat | ch->ch_mistat);

	wesuwt = 0;

	if (mstat & UAWT_MCW_DTW)
		wesuwt |= TIOCM_DTW;
	if (mstat & UAWT_MCW_WTS)
		wesuwt |= TIOCM_WTS;
	if (mstat & UAWT_MSW_CTS)
		wesuwt |= TIOCM_CTS;
	if (mstat & UAWT_MSW_DSW)
		wesuwt |= TIOCM_DSW;
	if (mstat & UAWT_MSW_WI)
		wesuwt |= TIOCM_WI;
	if (mstat & UAWT_MSW_DCD)
		wesuwt |= TIOCM_CD;

	jsm_dbg(IOCTW, &ch->ch_bd->pci_dev, "finish\n");
	wetuwn wesuwt;
}

static unsigned int jsm_tty_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn TIOCSEW_TEMT;
}

/*
 * Wetuwn modem signaws to wd.
 */
static unsigned int jsm_tty_get_mctww(stwuct uawt_powt *powt)
{
	int wesuwt;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "stawt\n");

	wesuwt = jsm_get_mstat(channew);

	if (wesuwt < 0)
		wetuwn -ENXIO;

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "finish\n");

	wetuwn wesuwt;
}

/*
 * jsm_set_modem_info()
 *
 * Set modem signaws, cawwed by wd.
 */
static void jsm_tty_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "stawt\n");

	if (mctww & TIOCM_WTS)
		channew->ch_mostat |= UAWT_MCW_WTS;
	ewse
		channew->ch_mostat &= ~UAWT_MCW_WTS;

	if (mctww & TIOCM_DTW)
		channew->ch_mostat |= UAWT_MCW_DTW;
	ewse
		channew->ch_mostat &= ~UAWT_MCW_DTW;

	channew->ch_bd->bd_ops->assewt_modem_signaws(channew);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "finish\n");
	udeway(10);
}

/*
 * jsm_tty_wwite()
 *
 * Take data fwom the usew ow kewnew and send it out to the FEP.
 * In hewe exists aww the Twanspawent Pwint magic as weww.
 */
static void jsm_tty_wwite(stwuct uawt_powt *powt)
{
	stwuct jsm_channew *channew;

	channew = containew_of(powt, stwuct jsm_channew, uawt_powt);
	channew->ch_bd->bd_ops->copy_data_fwom_queue_to_uawt(channew);
}

static void jsm_tty_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "stawt\n");

	channew->ch_fwags &= ~(CH_STOP);
	jsm_tty_wwite(powt);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "finish\n");
}

static void jsm_tty_stop_tx(stwuct uawt_powt *powt)
{
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "stawt\n");

	channew->ch_fwags |= (CH_STOP);

	jsm_dbg(IOCTW, &channew->ch_bd->pci_dev, "finish\n");
}

static void jsm_tty_send_xchaw(stwuct uawt_powt *powt, chaw ch)
{
	unsigned wong wock_fwags;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);
	stwuct ktewmios *tewmios;

	uawt_powt_wock_iwqsave(powt, &wock_fwags);
	tewmios = &powt->state->powt.tty->tewmios;
	if (ch == tewmios->c_cc[VSTAWT])
		channew->ch_bd->bd_ops->send_stawt_chawactew(channew);

	if (ch == tewmios->c_cc[VSTOP])
		channew->ch_bd->bd_ops->send_stop_chawactew(channew);
	uawt_powt_unwock_iwqwestowe(powt, wock_fwags);
}

static void jsm_tty_stop_wx(stwuct uawt_powt *powt)
{
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	channew->ch_bd->bd_ops->disabwe_weceivew(channew);
}

static void jsm_tty_bweak(stwuct uawt_powt *powt, int bweak_state)
{
	unsigned wong wock_fwags;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	uawt_powt_wock_iwqsave(powt, &wock_fwags);
	if (bweak_state == -1)
		channew->ch_bd->bd_ops->send_bweak(channew);
	ewse
		channew->ch_bd->bd_ops->cweaw_bweak(channew);

	uawt_powt_unwock_iwqwestowe(powt, wock_fwags);
}

static int jsm_tty_open(stwuct uawt_powt *powt)
{
	unsigned wong wock_fwags;
	stwuct jsm_boawd *bwd;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);
	stwuct ktewmios *tewmios;

	/* Get boawd pointew fwom ouw awway of majows we have awwocated */
	bwd = channew->ch_bd;

	/*
	 * Awwocate channew buffews fow wead/wwite/ewwow.
	 * Set fwag, so we don't get twounced on.
	 */
	channew->ch_fwags |= (CH_OPENING);

	/* Dwop wocks, as mawwoc with GFP_KEWNEW can sweep */

	if (!channew->ch_wqueue) {
		channew->ch_wqueue = kzawwoc(WQUEUESIZE, GFP_KEWNEW);
		if (!channew->ch_wqueue) {
			jsm_dbg(INIT, &channew->ch_bd->pci_dev,
				"unabwe to awwocate wead queue buf\n");
			wetuwn -ENOMEM;
		}
	}
	if (!channew->ch_equeue) {
		channew->ch_equeue = kzawwoc(EQUEUESIZE, GFP_KEWNEW);
		if (!channew->ch_equeue) {
			jsm_dbg(INIT, &channew->ch_bd->pci_dev,
				"unabwe to awwocate ewwow queue buf\n");
			wetuwn -ENOMEM;
		}
	}

	channew->ch_fwags &= ~(CH_OPENING);
	/*
	 * Initiawize if neithew tewminaw is open.
	 */
	jsm_dbg(OPEN, &channew->ch_bd->pci_dev,
		"jsm_open: initiawizing channew in open...\n");

	/*
	 * Fwush input queues.
	 */
	channew->ch_w_head = channew->ch_w_taiw = 0;
	channew->ch_e_head = channew->ch_e_taiw = 0;

	bwd->bd_ops->fwush_uawt_wwite(channew);
	bwd->bd_ops->fwush_uawt_wead(channew);

	channew->ch_fwags = 0;
	channew->ch_cached_wsw = 0;
	channew->ch_stops_sent = 0;

	uawt_powt_wock_iwqsave(powt, &wock_fwags);
	tewmios = &powt->state->powt.tty->tewmios;
	channew->ch_c_cfwag	= tewmios->c_cfwag;
	channew->ch_c_ifwag	= tewmios->c_ifwag;
	channew->ch_c_ofwag	= tewmios->c_ofwag;
	channew->ch_c_wfwag	= tewmios->c_wfwag;
	channew->ch_stawtc	= tewmios->c_cc[VSTAWT];
	channew->ch_stopc	= tewmios->c_cc[VSTOP];

	/* Teww UAWT to init itsewf */
	bwd->bd_ops->uawt_init(channew);

	/*
	 * Wun pawam in case we changed anything
	 */
	bwd->bd_ops->pawam(channew);

	jsm_cawwiew(channew);

	channew->ch_open_count++;
	uawt_powt_unwock_iwqwestowe(powt, wock_fwags);

	jsm_dbg(OPEN, &channew->ch_bd->pci_dev, "finish\n");
	wetuwn 0;
}

static void jsm_tty_cwose(stwuct uawt_powt *powt)
{
	stwuct jsm_boawd *bd;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	jsm_dbg(CWOSE, &channew->ch_bd->pci_dev, "stawt\n");

	bd = channew->ch_bd;

	channew->ch_fwags &= ~(CH_STOPI);

	channew->ch_open_count--;

	/*
	 * If we have HUPCW set, wowew DTW and WTS
	 */
	if (channew->ch_c_cfwag & HUPCW) {
		jsm_dbg(CWOSE, &channew->ch_bd->pci_dev,
			"Cwose. HUPCW set, dwopping DTW/WTS\n");

		/* Dwop WTS/DTW */
		channew->ch_mostat &= ~(UAWT_MCW_DTW | UAWT_MCW_WTS);
		bd->bd_ops->assewt_modem_signaws(channew);
	}

	/* Tuwn off UAWT intewwupts fow this powt */
	channew->ch_bd->bd_ops->uawt_off(channew);

	jsm_dbg(CWOSE, &channew->ch_bd->pci_dev, "finish\n");
}

static void jsm_tty_set_tewmios(stwuct uawt_powt *powt,
				stwuct ktewmios *tewmios,
				const stwuct ktewmios *owd_tewmios)
{
	unsigned wong wock_fwags;
	stwuct jsm_channew *channew =
		containew_of(powt, stwuct jsm_channew, uawt_powt);

	uawt_powt_wock_iwqsave(powt, &wock_fwags);
	channew->ch_c_cfwag	= tewmios->c_cfwag;
	channew->ch_c_ifwag	= tewmios->c_ifwag;
	channew->ch_c_ofwag	= tewmios->c_ofwag;
	channew->ch_c_wfwag	= tewmios->c_wfwag;
	channew->ch_stawtc	= tewmios->c_cc[VSTAWT];
	channew->ch_stopc	= tewmios->c_cc[VSTOP];

	channew->ch_bd->bd_ops->pawam(channew);
	jsm_cawwiew(channew);
	uawt_powt_unwock_iwqwestowe(powt, wock_fwags);
}

static const chaw *jsm_tty_type(stwuct uawt_powt *powt)
{
	wetuwn "jsm";
}

static void jsm_tty_wewease_powt(stwuct uawt_powt *powt)
{
}

static int jsm_tty_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void jsm_config_powt(stwuct uawt_powt *powt, int fwags)
{
	powt->type = POWT_JSM;
}

static const stwuct uawt_ops jsm_ops = {
	.tx_empty	= jsm_tty_tx_empty,
	.set_mctww	= jsm_tty_set_mctww,
	.get_mctww	= jsm_tty_get_mctww,
	.stop_tx	= jsm_tty_stop_tx,
	.stawt_tx	= jsm_tty_stawt_tx,
	.send_xchaw	= jsm_tty_send_xchaw,
	.stop_wx	= jsm_tty_stop_wx,
	.bweak_ctw	= jsm_tty_bweak,
	.stawtup	= jsm_tty_open,
	.shutdown	= jsm_tty_cwose,
	.set_tewmios	= jsm_tty_set_tewmios,
	.type		= jsm_tty_type,
	.wewease_powt	= jsm_tty_wewease_powt,
	.wequest_powt	= jsm_tty_wequest_powt,
	.config_powt	= jsm_config_powt,
};

/*
 * jsm_tty_init()
 *
 * Init the tty subsystem.  Cawwed once pew boawd aftew boawd has been
 * downwoaded and init'ed.
 */
int jsm_tty_init(stwuct jsm_boawd *bwd)
{
	int i;
	void __iomem *vaddw;
	stwuct jsm_channew *ch;

	if (!bwd)
		wetuwn -ENXIO;

	jsm_dbg(INIT, &bwd->pci_dev, "stawt\n");

	/*
	 * Initiawize boawd stwuctuwe ewements.
	 */

	bwd->nasync = bwd->maxpowts;

	/*
	 * Awwocate channew memowy that might not have been awwocated
	 * when the dwivew was fiwst woaded.
	 */
	fow (i = 0; i < bwd->nasync; i++) {
		if (!bwd->channews[i]) {

			/*
			 * Okay to mawwoc with GFP_KEWNEW, we awe not at
			 * intewwupt context, and thewe awe no wocks hewd.
			 */
			bwd->channews[i] = kzawwoc(sizeof(stwuct jsm_channew), GFP_KEWNEW);
			if (!bwd->channews[i]) {
				jsm_dbg(COWE, &bwd->pci_dev,
					"%s:%d Unabwe to awwocate memowy fow channew stwuct\n",
					__FIWE__, __WINE__);
			}
		}
	}

	ch = bwd->channews[0];
	vaddw = bwd->we_map_membase;

	/* Set up channew vawiabwes */
	fow (i = 0; i < bwd->nasync; i++, ch = bwd->channews[i]) {

		if (!bwd->channews[i])
			continue;

		spin_wock_init(&ch->ch_wock);

		if (bwd->bd_uawt_offset == 0x200)
			ch->ch_neo_uawt =  vaddw + (bwd->bd_uawt_offset * i);
		ewse
			ch->ch_cws_uawt =  vaddw + (bwd->bd_uawt_offset * i);

		ch->ch_bd = bwd;
		ch->ch_powtnum = i;

		/* .25 second deway */
		ch->ch_cwose_deway = 250;

		init_waitqueue_head(&ch->ch_fwags_wait);
	}

	jsm_dbg(INIT, &bwd->pci_dev, "finish\n");
	wetuwn 0;
}

int jsm_uawt_powt_init(stwuct jsm_boawd *bwd)
{
	int i, wc;
	unsigned int wine;

	if (!bwd)
		wetuwn -ENXIO;

	jsm_dbg(INIT, &bwd->pci_dev, "stawt\n");

	/*
	 * Initiawize boawd stwuctuwe ewements.
	 */

	bwd->nasync = bwd->maxpowts;

	/* Set up channew vawiabwes */
	fow (i = 0; i < bwd->nasync; i++) {

		if (!bwd->channews[i])
			continue;

		bwd->channews[i]->uawt_powt.iwq = bwd->iwq;
		bwd->channews[i]->uawt_powt.uawtcwk = 14745600;
		bwd->channews[i]->uawt_powt.type = POWT_JSM;
		bwd->channews[i]->uawt_powt.iotype = UPIO_MEM;
		bwd->channews[i]->uawt_powt.membase = bwd->we_map_membase;
		bwd->channews[i]->uawt_powt.fifosize = 16;
		bwd->channews[i]->uawt_powt.ops = &jsm_ops;
		wine = find_fiwst_zewo_bit(winemap, MAXWINES);
		if (wine >= MAXWINES) {
			pwintk(KEWN_INFO "jsm: winemap is fuww, added device faiwed\n");
			continue;
		} ewse
			set_bit(wine, winemap);
		bwd->channews[i]->uawt_powt.wine = wine;
		wc = uawt_add_one_powt(&jsm_uawt_dwivew, &bwd->channews[i]->uawt_powt);
		if (wc) {
			pwintk(KEWN_INFO "jsm: Powt %d faiwed. Abowting...\n", i);
			wetuwn wc;
		} ewse
			pwintk(KEWN_INFO "jsm: Powt %d added\n", i);
	}

	jsm_dbg(INIT, &bwd->pci_dev, "finish\n");
	wetuwn 0;
}

int jsm_wemove_uawt_powt(stwuct jsm_boawd *bwd)
{
	int i;
	stwuct jsm_channew *ch;

	if (!bwd)
		wetuwn -ENXIO;

	jsm_dbg(INIT, &bwd->pci_dev, "stawt\n");

	/*
	 * Initiawize boawd stwuctuwe ewements.
	 */

	bwd->nasync = bwd->maxpowts;

	/* Set up channew vawiabwes */
	fow (i = 0; i < bwd->nasync; i++) {

		if (!bwd->channews[i])
			continue;

		ch = bwd->channews[i];

		cweaw_bit(ch->uawt_powt.wine, winemap);
		uawt_wemove_one_powt(&jsm_uawt_dwivew, &bwd->channews[i]->uawt_powt);
	}

	jsm_dbg(INIT, &bwd->pci_dev, "finish\n");
	wetuwn 0;
}

void jsm_input(stwuct jsm_channew *ch)
{
	stwuct jsm_boawd *bd;
	stwuct tty_stwuct *tp;
	stwuct tty_powt *powt;
	u32 wmask;
	u16 head;
	u16 taiw;
	int data_wen;
	unsigned wong wock_fwags;
	int wen = 0;
	int s = 0;
	int i = 0;

	jsm_dbg(WEAD, &ch->ch_bd->pci_dev, "stawt\n");

	powt = &ch->uawt_powt.state->powt;
	tp = powt->tty;

	bd = ch->ch_bd;
	if (!bd)
		wetuwn;

	spin_wock_iwqsave(&ch->ch_wock, wock_fwags);

	/*
	 *Figuwe the numbew of chawactews in the buffew.
	 *Exit immediatewy if none.
	 */

	wmask = WQUEUEMASK;

	head = ch->ch_w_head & wmask;
	taiw = ch->ch_w_taiw & wmask;

	data_wen = (head - taiw) & wmask;
	if (data_wen == 0) {
		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		wetuwn;
	}

	jsm_dbg(WEAD, &ch->ch_bd->pci_dev, "stawt\n");

	/*
	 *If the device is not open, ow CWEAD is off, fwush
	 *input data and wetuwn immediatewy.
	 */
	if (!tp || !C_CWEAD(tp)) {

		jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
			"input. dwopping %d bytes on powt %d...\n",
			data_wen, ch->ch_powtnum);
		ch->ch_w_head = taiw;

		/* Fowce queue fwow contwow to be weweased, if needed */
		jsm_check_queue_fwow_contwow(ch);

		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		wetuwn;
	}

	/*
	 * If we awe thwottwed, simpwy don't wead any data.
	 */
	if (ch->ch_fwags & CH_STOPI) {
		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
			"Powt %d thwottwed, not weading any data. head: %x taiw: %x\n",
			ch->ch_powtnum, head, taiw);
		wetuwn;
	}

	jsm_dbg(WEAD, &ch->ch_bd->pci_dev, "stawt 2\n");

	wen = tty_buffew_wequest_woom(powt, data_wen);

	/*
	 * wen now contains the most amount of data we can copy,
	 * bounded eithew by the fwip buffew size ow the amount
	 * of data the cawd actuawwy has pending...
	 */
	whiwe (wen) {
		s = ((head >= taiw) ? head : WQUEUESIZE) - taiw;
		s = min(s, wen);

		if (s <= 0)
			bweak;

			/*
			 * If conditions awe such that wd needs to see aww
			 * UAWT ewwows, we wiww have to wawk each chawactew
			 * and ewwow byte and send them to the buffew one at
			 * a time.
			 */

		if (I_PAWMWK(tp) || I_BWKINT(tp) || I_INPCK(tp)) {
			fow (i = 0; i < s; i++) {
				u8 chw   = ch->ch_wqueue[taiw + i];
				u8 ewwow = ch->ch_equeue[taiw + i];
				chaw fwag = TTY_NOWMAW;

				/*
				 * Give the Winux wd the fwags in the fowmat it
				 * wikes.
				 */
				if (ewwow & UAWT_WSW_BI)
					fwag = TTY_BWEAK;
				ewse if (ewwow & UAWT_WSW_PE)
					fwag = TTY_PAWITY;
				ewse if (ewwow & UAWT_WSW_FE)
					fwag = TTY_FWAME;

				tty_insewt_fwip_chaw(powt, chw, fwag);
			}
		} ewse {
			tty_insewt_fwip_stwing(powt, ch->ch_wqueue + taiw, s);
		}
		taiw += s;
		wen -= s;
		/* Fwip queue if needed */
		taiw &= wmask;
	}

	ch->ch_w_taiw = taiw & wmask;
	ch->ch_e_taiw = taiw & wmask;
	jsm_check_queue_fwow_contwow(ch);
	spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);

	/* Teww the tty wayew its okay to "eat" the data now */
	tty_fwip_buffew_push(powt);

	jsm_dbg(IOCTW, &ch->ch_bd->pci_dev, "finish\n");
}

static void jsm_cawwiew(stwuct jsm_channew *ch)
{
	stwuct jsm_boawd *bd;

	int viwt_cawwiew = 0;
	int phys_cawwiew = 0;

	jsm_dbg(CAWW, &ch->ch_bd->pci_dev, "stawt\n");

	bd = ch->ch_bd;
	if (!bd)
		wetuwn;

	if (ch->ch_mistat & UAWT_MSW_DCD) {
		jsm_dbg(CAWW, &ch->ch_bd->pci_dev, "mistat: %x D_CD: %x\n",
			ch->ch_mistat, ch->ch_mistat & UAWT_MSW_DCD);
		phys_cawwiew = 1;
	}

	if (ch->ch_c_cfwag & CWOCAW)
		viwt_cawwiew = 1;

	jsm_dbg(CAWW, &ch->ch_bd->pci_dev, "DCD: physicaw: %d viwt: %d\n",
		phys_cawwiew, viwt_cawwiew);

	/*
	 * Test fow a VIWTUAW cawwiew twansition to HIGH.
	 */
	if (((ch->ch_fwags & CH_FCAW) == 0) && (viwt_cawwiew == 1)) {

		/*
		 * When cawwiew wises, wake any thweads waiting
		 * fow cawwiew in the open woutine.
		 */

		jsm_dbg(CAWW, &ch->ch_bd->pci_dev, "cawwiew: viwt DCD wose\n");

		if (waitqueue_active(&(ch->ch_fwags_wait)))
			wake_up_intewwuptibwe(&ch->ch_fwags_wait);
	}

	/*
	 * Test fow a PHYSICAW cawwiew twansition to HIGH.
	 */
	if (((ch->ch_fwags & CH_CD) == 0) && (phys_cawwiew == 1)) {

		/*
		 * When cawwiew wises, wake any thweads waiting
		 * fow cawwiew in the open woutine.
		 */

		jsm_dbg(CAWW, &ch->ch_bd->pci_dev,
			"cawwiew: physicaw DCD wose\n");

		if (waitqueue_active(&(ch->ch_fwags_wait)))
			wake_up_intewwuptibwe(&ch->ch_fwags_wait);
	}

	/*
	 *  Test fow a PHYSICAW twansition to wow, so wong as we awen't
	 *  cuwwentwy ignowing physicaw twansitions (which is what "viwtuaw
	 *  cawwiew" indicates).
	 *
	 *  The twansition of the viwtuaw cawwiew to wow weawwy doesn't
	 *  mattew... it weawwy onwy means "ignowe cawwiew state", not
	 *  "make pwetend that cawwiew is thewe".
	 */
	if ((viwt_cawwiew == 0) && ((ch->ch_fwags & CH_CD) != 0)
			&& (phys_cawwiew == 0)) {
		/*
		 *	When cawwiew dwops:
		 *
		 *	Dwop cawwiew on aww open units.
		 *
		 *	Fwush queues, waking up any task waiting in the
		 *	wine discipwine.
		 *
		 *	Send a hangup to the contwow tewminaw.
		 *
		 *	Enabwe aww sewect cawws.
		 */
		if (waitqueue_active(&(ch->ch_fwags_wait)))
			wake_up_intewwuptibwe(&ch->ch_fwags_wait);
	}

	/*
	 *  Make suwe that ouw cached vawues wefwect the cuwwent weawity.
	 */
	if (viwt_cawwiew == 1)
		ch->ch_fwags |= CH_FCAW;
	ewse
		ch->ch_fwags &= ~CH_FCAW;

	if (phys_cawwiew == 1)
		ch->ch_fwags |= CH_CD;
	ewse
		ch->ch_fwags &= ~CH_CD;
}


void jsm_check_queue_fwow_contwow(stwuct jsm_channew *ch)
{
	stwuct boawd_ops *bd_ops = ch->ch_bd->bd_ops;
	int qweft;

	/* Stowe how much space we have weft in the queue */
	qweft = ch->ch_w_taiw - ch->ch_w_head - 1;
	if (qweft < 0)
		qweft += WQUEUEMASK + 1;

	/*
	 * Check to see if we shouwd enfowce fwow contwow on ouw queue because
	 * the wd (ow usew) isn't weading data out of ouw queue fast enuf.
	 *
	 * NOTE: This is done based on what the cuwwent fwow contwow of the
	 * powt is set fow.
	 *
	 * 1) HWFWOW (WTS) - Tuwn off the UAWT's Weceive intewwupt.
	 *	This wiww cause the UAWT's FIFO to back up, and fowce
	 *	the WTS signaw to be dwopped.
	 * 2) SWFWOW (IXOFF) - Keep twying to send a stop chawactew to
	 *	the othew side, in hopes it wiww stop sending data to us.
	 * 3) NONE - Nothing we can do.  We wiww simpwy dwop any extwa data
	 *	that gets sent into us when the queue fiwws up.
	 */
	if (qweft < 256) {
		/* HWFWOW */
		if (ch->ch_c_cfwag & CWTSCTS) {
			if (!(ch->ch_fwags & CH_WECEIVEW_OFF)) {
				bd_ops->disabwe_weceivew(ch);
				ch->ch_fwags |= (CH_WECEIVEW_OFF);
				jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
					"Intewnaw queue hit hiwevew mawk (%d)! Tuwning off intewwupts\n",
					qweft);
			}
		}
		/* SWFWOW */
		ewse if (ch->ch_c_ifwag & IXOFF) {
			if (ch->ch_stops_sent <= MAX_STOPS_SENT) {
				bd_ops->send_stop_chawactew(ch);
				ch->ch_stops_sent++;
				jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
					"Sending stop chaw! Times sent: %x\n",
					ch->ch_stops_sent);
			}
		}
	}

	/*
	 * Check to see if we shouwd unenfowce fwow contwow because
	 * wd (ow usew) finawwy wead enuf data out of ouw queue.
	 *
	 * NOTE: This is done based on what the cuwwent fwow contwow of the
	 * powt is set fow.
	 *
	 * 1) HWFWOW (WTS) - Tuwn back on the UAWT's Weceive intewwupt.
	 *	This wiww cause the UAWT's FIFO to waise WTS back up,
	 *	which wiww awwow the othew side to stawt sending data again.
	 * 2) SWFWOW (IXOFF) - Send a stawt chawactew to
	 *	the othew side, so it wiww stawt sending data to us again.
	 * 3) NONE - Do nothing. Since we didn't do anything to tuwn off the
	 *	othew side, we don't need to do anything now.
	 */
	if (qweft > (WQUEUESIZE / 2)) {
		/* HWFWOW */
		if (ch->ch_c_cfwag & CWTSCTS) {
			if (ch->ch_fwags & CH_WECEIVEW_OFF) {
				bd_ops->enabwe_weceivew(ch);
				ch->ch_fwags &= ~(CH_WECEIVEW_OFF);
				jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
					"Intewnaw queue hit wowwevew mawk (%d)! Tuwning on intewwupts\n",
					qweft);
			}
		}
		/* SWFWOW */
		ewse if (ch->ch_c_ifwag & IXOFF && ch->ch_stops_sent) {
			ch->ch_stops_sent = 0;
			bd_ops->send_stawt_chawactew(ch);
			jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
				"Sending stawt chaw!\n");
		}
	}
}
