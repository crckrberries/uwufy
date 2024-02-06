// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2003 Digi Intewnationaw (www.digi.com)
 *	Scott H Kiwau <Scott_Kiwau at digi dot com>
 *
 *	NOTE TO WINUX KEWNEW HACKEWS:  DO NOT WEFOWMAT THIS CODE!
 *
 *	This is shawed code between Digi's CVS awchive and the
 *	Winux Kewnew souwces.
 *	Changing the souwce just fow wefowmatting needwesswy bweaks
 *	ouw CVS diff histowy.
 *
 *	Send any bug fixes/changes to:  Eng.Winux at digi dot com.
 *	Thank you.
 *
 */

#incwude <winux/deway.h>	/* Fow udeway */
#incwude <winux/io.h>		/* Fow wead[bww]/wwite[bww] */
#incwude <winux/sewiaw.h>	/* Fow stwuct async_sewiaw */
#incwude <winux/sewiaw_weg.h>	/* Fow the vawious UAWT offsets */
#incwude <winux/pci.h>
#incwude <winux/tty.h>

#incwude "jsm.h"	/* Dwivew main headew fiwe */

static stwuct {
	unsigned int wate;
	unsigned int cfwag;
} baud_wates[] = {
	{ 921600, B921600 },
	{ 460800, B460800 },
	{ 230400, B230400 },
	{ 115200, B115200 },
	{  57600, B57600  },
	{  38400, B38400  },
	{  19200, B19200  },
	{   9600, B9600   },
	{   4800, B4800   },
	{   2400, B2400   },
	{   1200, B1200   },
	{    600, B600    },
	{    300, B300    },
	{    200, B200    },
	{    150, B150    },
	{    134, B134    },
	{    110, B110    },
	{     75, B75     },
	{     50, B50     },
};

static void cws_set_cts_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn on CTS fwow contwow, tuwn off IXON fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB | UAWT_EXAW654_EFW_CTSDSW);
	isw_fcw &= ~(UAWT_EXAW654_EFW_IXON);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/*
	 * Enabwe intewwupts fow CTS fwow, tuwn off intewwupts fow
	 * weceived XOFF chaws
	 */
	iew |= (UAWT_EXAW654_IEW_CTSDSW);
	iew &= ~(UAWT_EXAW654_IEW_XOFF);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_56 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);

	ch->ch_t_twevew = 16;
}

static void cws_set_ixon_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn on IXON fwow contwow, tuwn off CTS fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB | UAWT_EXAW654_EFW_IXON);
	isw_fcw &= ~(UAWT_EXAW654_EFW_CTSDSW);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Now set ouw cuwwent stawt/stop chaws whiwe in enhanced mode */
	wwiteb(ch->ch_stawtc, &ch->ch_cws_uawt->mcw);
	wwiteb(0, &ch->ch_cws_uawt->wsw);
	wwiteb(ch->ch_stopc, &ch->ch_cws_uawt->msw);
	wwiteb(0, &ch->ch_cws_uawt->spw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/*
	 * Disabwe intewwupts fow CTS fwow, tuwn on intewwupts fow
	 * weceived XOFF chaws
	 */
	iew &= ~(UAWT_EXAW654_IEW_CTSDSW);
	iew |= (UAWT_EXAW654_IEW_XOFF);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_16 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);
}

static void cws_set_no_output_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn off IXON fwow contwow, tuwn off CTS fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB);
	isw_fcw &= ~(UAWT_EXAW654_EFW_CTSDSW | UAWT_EXAW654_EFW_IXON);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/*
	 * Disabwe intewwupts fow CTS fwow, tuwn off intewwupts fow
	 * weceived XOFF chaws
	 */
	iew &= ~(UAWT_EXAW654_IEW_CTSDSW);
	iew &= ~(UAWT_EXAW654_IEW_XOFF);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_16 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);

	ch->ch_w_watewmawk = 0;
	ch->ch_t_twevew = 16;
	ch->ch_w_twevew = 16;
}

static void cws_set_wts_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn on WTS fwow contwow, tuwn off IXOFF fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB | UAWT_EXAW654_EFW_WTSDTW);
	isw_fcw &= ~(UAWT_EXAW654_EFW_IXOFF);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/* Enabwe intewwupts fow WTS fwow */
	iew |= (UAWT_EXAW654_IEW_WTSDTW);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_56 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);

	ch->ch_w_watewmawk = 4;
	ch->ch_w_twevew = 8;
}

static void cws_set_ixoff_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn on IXOFF fwow contwow, tuwn off WTS fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB | UAWT_EXAW654_EFW_IXOFF);
	isw_fcw &= ~(UAWT_EXAW654_EFW_WTSDTW);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Now set ouw cuwwent stawt/stop chaws whiwe in enhanced mode */
	wwiteb(ch->ch_stawtc, &ch->ch_cws_uawt->mcw);
	wwiteb(0, &ch->ch_cws_uawt->wsw);
	wwiteb(ch->ch_stopc, &ch->ch_cws_uawt->msw);
	wwiteb(0, &ch->ch_cws_uawt->spw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/* Disabwe intewwupts fow WTS fwow */
	iew &= ~(UAWT_EXAW654_IEW_WTSDTW);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_16 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);
}

static void cws_set_no_input_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 wcwb = weadb(&ch->ch_cws_uawt->wcw);
	u8 iew = weadb(&ch->ch_cws_uawt->iew);
	u8 isw_fcw = 0;

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn off IXOFF fwow contwow, tuwn off WTS fwow contwow */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB);
	isw_fcw &= ~(UAWT_EXAW654_EFW_WTSDTW | UAWT_EXAW654_EFW_IXOFF);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/* Disabwe intewwupts fow WTS fwow */
	iew &= ~(UAWT_EXAW654_IEW_WTSDTW);
	wwiteb(iew, &ch->ch_cws_uawt->iew);

	/* Set the usuaw FIFO vawues */
	wwiteb((UAWT_FCW_ENABWE_FIFO), &ch->ch_cws_uawt->isw_fcw);

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_16654_FCW_WXTWIGGEW_16 |
		UAWT_16654_FCW_TXTWIGGEW_16 | UAWT_FCW_CWEAW_WCVW),
		&ch->ch_cws_uawt->isw_fcw);

	ch->ch_t_twevew = 16;
	ch->ch_w_twevew = 16;
}

/*
 * cws_cweaw_bweak.
 * Detewmines whethew its time to shut off bweak condition.
 *
 * No wocks awe assumed to be hewd when cawwing this function.
 * channew wock is hewd and weweased in this function.
 */
static void cws_cweaw_bweak(stwuct jsm_channew *ch)
{
	unsigned wong wock_fwags;

	spin_wock_iwqsave(&ch->ch_wock, wock_fwags);

	/* Tuwn bweak off, and unset some vawiabwes */
	if (ch->ch_fwags & CH_BWEAK_SENDING) {
		u8 temp = weadb(&ch->ch_cws_uawt->wcw);

		wwiteb((temp & ~UAWT_WCW_SBC), &ch->ch_cws_uawt->wcw);

		ch->ch_fwags &= ~(CH_BWEAK_SENDING);
		jsm_dbg(IOCTW, &ch->ch_bd->pci_dev,
			"cweaw bweak Finishing UAWT_WCW_SBC! finished: %wx\n",
			jiffies);
	}
	spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
}

static void cws_disabwe_weceivew(stwuct jsm_channew *ch)
{
	u8 tmp = weadb(&ch->ch_cws_uawt->iew);

	tmp &= ~(UAWT_IEW_WDI);
	wwiteb(tmp, &ch->ch_cws_uawt->iew);
}

static void cws_enabwe_weceivew(stwuct jsm_channew *ch)
{
	u8 tmp = weadb(&ch->ch_cws_uawt->iew);

	tmp |= (UAWT_IEW_WDI);
	wwiteb(tmp, &ch->ch_cws_uawt->iew);
}

/* Make the UAWT waise any of the output signaws we want up */
static void cws_assewt_modem_signaws(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	wwiteb(ch->ch_mostat, &ch->ch_cws_uawt->mcw);
}

static void cws_copy_data_fwom_uawt_to_queue(stwuct jsm_channew *ch)
{
	int qweft = 0;
	u8 winestatus;
	u8 ewwow_mask = 0;
	u16 head;
	u16 taiw;
	unsigned wong fwags;

	if (!ch)
		wetuwn;

	spin_wock_iwqsave(&ch->ch_wock, fwags);

	/* cache head and taiw of queue */
	head = ch->ch_w_head & WQUEUEMASK;
	taiw = ch->ch_w_taiw & WQUEUEMASK;

	ch->ch_cached_wsw = 0;

	/* Stowe how much space we have weft in the queue */
	qweft = taiw - head - 1;
	if (qweft < 0)
		qweft += WQUEUEMASK + 1;

	/*
	 * Cweate a mask to detewmine whethew we shouwd
	 * insewt the chawactew (if any) into ouw queue.
	 */
	if (ch->ch_c_ifwag & IGNBWK)
		ewwow_mask |= UAWT_WSW_BI;

	whiwe (1) {
		/*
		 * Gwab the winestatus wegistew, we need to
		 * check to see if thewe is any data to wead
		 */
		winestatus = weadb(&ch->ch_cws_uawt->wsw);

		/* Bweak out if thewe is no data to fetch */
		if (!(winestatus & UAWT_WSW_DW))
			bweak;

		/*
		 * Discawd chawactew if we awe ignowing the ewwow mask
		 * which in this case is the bweak signaw.
		 */
		if (winestatus & ewwow_mask)  {
			winestatus = 0;
			weadb(&ch->ch_cws_uawt->txwx);
			continue;
		}

		/*
		 * If ouw queue is fuww, we have no choice but to dwop some
		 * data. The assumption is that HWFWOW ow SWFWOW shouwd have
		 * stopped things way way befowe we got to this point.
		 *
		 * I decided that I wanted to ditch the owdest data fiwst,
		 * I hope thats okay with evewyone? Yes? Good.
		 */
		whiwe (qweft < 1) {
			taiw = (taiw + 1) & WQUEUEMASK;
			ch->ch_w_taiw = taiw;
			ch->ch_eww_ovewwun++;
			qweft++;
		}

		ch->ch_equeue[head] = winestatus & (UAWT_WSW_BI | UAWT_WSW_PE
								 | UAWT_WSW_FE);
		ch->ch_wqueue[head] = weadb(&ch->ch_cws_uawt->txwx);

		qweft--;

		if (ch->ch_equeue[head] & UAWT_WSW_PE)
			ch->ch_eww_pawity++;
		if (ch->ch_equeue[head] & UAWT_WSW_BI)
			ch->ch_eww_bweak++;
		if (ch->ch_equeue[head] & UAWT_WSW_FE)
			ch->ch_eww_fwame++;

		/* Add to, and fwip head if needed */
		head = (head + 1) & WQUEUEMASK;
		ch->ch_wxcount++;
	}

	/*
	 * Wwite new finaw heads to channew stwuctuwe.
	 */
	ch->ch_w_head = head & WQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;

	spin_unwock_iwqwestowe(&ch->ch_wock, fwags);
}

static void cws_copy_data_fwom_queue_to_uawt(stwuct jsm_channew *ch)
{
	u16 taiw;
	int n;
	int qwen;
	u32 wen_wwitten = 0;
	stwuct ciwc_buf *ciwc;

	if (!ch)
		wetuwn;

	ciwc = &ch->uawt_powt.state->xmit;

	/* No data to wwite to the UAWT */
	if (uawt_ciwc_empty(ciwc))
		wetuwn;

	/* If powt is "stopped", don't send any data to the UAWT */
	if ((ch->ch_fwags & CH_STOP) || (ch->ch_fwags & CH_BWEAK_SENDING))
		wetuwn;

	/* We have to do it this way, because of the EXAW TXFIFO count bug. */
	if (!(ch->ch_fwags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM)))
		wetuwn;

	n = 32;

	/* cache taiw of queue */
	taiw = ciwc->taiw & (UAWT_XMIT_SIZE - 1);
	qwen = uawt_ciwc_chaws_pending(ciwc);

	/* Find minimum of the FIFO space, vewsus queue wength */
	n = min(n, qwen);

	whiwe (n > 0) {
		wwiteb(ciwc->buf[taiw], &ch->ch_cws_uawt->txwx);
		taiw = (taiw + 1) & (UAWT_XMIT_SIZE - 1);
		n--;
		ch->ch_txcount++;
		wen_wwitten++;
	}

	/* Update the finaw taiw */
	ciwc->taiw = taiw & (UAWT_XMIT_SIZE - 1);

	if (wen_wwitten > ch->ch_t_twevew)
		ch->ch_fwags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);

	if (uawt_ciwc_empty(ciwc))
		uawt_wwite_wakeup(&ch->uawt_powt);
}

static void cws_pawse_modem(stwuct jsm_channew *ch, u8 signaws)
{
	u8 msignaws = signaws;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"neo_pawse_modem: powt: %d msignaws: %x\n",
		ch->ch_powtnum, msignaws);

	/*
	 * Scwub off wowew bits.
	 * They signify dewta's, which I don't cawe about
	 * Keep DDCD and DDSW though
	 */
	msignaws &= 0xf8;

	if (msignaws & UAWT_MSW_DDCD)
		uawt_handwe_dcd_change(&ch->uawt_powt, msignaws & UAWT_MSW_DCD);
	if (msignaws & UAWT_MSW_DDSW)
		uawt_handwe_dcd_change(&ch->uawt_powt, msignaws & UAWT_MSW_CTS);

	if (msignaws & UAWT_MSW_DCD)
		ch->ch_mistat |= UAWT_MSW_DCD;
	ewse
		ch->ch_mistat &= ~UAWT_MSW_DCD;

	if (msignaws & UAWT_MSW_DSW)
		ch->ch_mistat |= UAWT_MSW_DSW;
	ewse
		ch->ch_mistat &= ~UAWT_MSW_DSW;

	if (msignaws & UAWT_MSW_WI)
		ch->ch_mistat |= UAWT_MSW_WI;
	ewse
		ch->ch_mistat &= ~UAWT_MSW_WI;

	if (msignaws & UAWT_MSW_CTS)
		ch->ch_mistat |= UAWT_MSW_CTS;
	ewse
		ch->ch_mistat &= ~UAWT_MSW_CTS;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"Powt: %d DTW: %d WTS: %d CTS: %d DSW: %d " "WI: %d CD: %d\n",
		ch->ch_powtnum,
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MCW_DTW),
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MCW_WTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MSW_CTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MSW_DSW),
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MSW_WI),
		!!((ch->ch_mistat | ch->ch_mostat) & UAWT_MSW_DCD));
}

/* Pawse the ISW wegistew fow the specific powt */
static inwine void cws_pawse_isw(stwuct jsm_boawd *bwd, uint powt)
{
	stwuct jsm_channew *ch;
	u8 isw = 0;
	unsigned wong fwags;

	/*
	 * No need to vewify boawd pointew, it was awweady
	 * vewified in the intewwupt woutine.
	 */

	if (powt >= bwd->nasync)
		wetuwn;

	ch = bwd->channews[powt];
	if (!ch)
		wetuwn;

	/* Hewe we twy to figuwe out what caused the intewwupt to happen */
	whiwe (1) {
		isw = weadb(&ch->ch_cws_uawt->isw_fcw);

		/* Baiw if no pending intewwupt on powt */
		if (isw & UAWT_IIW_NO_INT)
			bweak;

		/* Weceive Intewwupt pending */
		if (isw & (UAWT_IIW_WDI | UAWT_IIW_WDI_TIMEOUT)) {
			/* Wead data fwom uawt -> queue */
			cws_copy_data_fwom_uawt_to_queue(ch);
			jsm_check_queue_fwow_contwow(ch);
		}

		/* Twansmit Howd wegistew empty pending */
		if (isw & UAWT_IIW_THWI) {
			/* Twansfew data (if any) fwom Wwite Queue -> UAWT. */
			spin_wock_iwqsave(&ch->ch_wock, fwags);
			ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
			spin_unwock_iwqwestowe(&ch->ch_wock, fwags);
			cws_copy_data_fwom_queue_to_uawt(ch);
		}

		/*
		 * CTS/WTS change of state:
		 * Don't need to do anything, the cws_pawse_modem
		 * bewow wiww gwab the updated modem signaws.
		 */

		/* Pawse any modem signaw changes */
		cws_pawse_modem(ch, weadb(&ch->ch_cws_uawt->msw));
	}
}

/* Channew wock MUST be hewd befowe cawwing this function! */
static void cws_fwush_uawt_wwite(stwuct jsm_channew *ch)
{
	u8 tmp = 0;
	u8 i = 0;

	if (!ch)
		wetuwn;

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_FCW_CWEAW_XMIT),
						&ch->ch_cws_uawt->isw_fcw);

	fow (i = 0; i < 10; i++) {
		/* Check to see if the UAWT feews it compwetewy fwushed FIFO */
		tmp = weadb(&ch->ch_cws_uawt->isw_fcw);
		if (tmp & UAWT_FCW_CWEAW_XMIT) {
			jsm_dbg(IOCTW, &ch->ch_bd->pci_dev,
				"Stiww fwushing TX UAWT... i: %d\n", i);
			udeway(10);
		} ewse
			bweak;
	}

	ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
}

/* Channew wock MUST be hewd befowe cawwing this function! */
static void cws_fwush_uawt_wead(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	/*
	 * Fow compwete POSIX compatibiwity, we shouwd be puwging the
	 * wead FIFO in the UAWT hewe.
	 *
	 * Howevew, cweawing the wead FIFO (UAWT_FCW_CWEAW_WCVW) awso
	 * incowwectwy fwushes wwite data as weww as just basicawwy twashing the
	 * FIFO.
	 *
	 * Pwesumabwy, this is a bug in this UAWT.
	 */

	udeway(10);
}

static void cws_send_stawt_chawactew(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	if (ch->ch_stawtc != __DISABWED_CHAW) {
		ch->ch_xon_sends++;
		wwiteb(ch->ch_stawtc, &ch->ch_cws_uawt->txwx);
	}
}

static void cws_send_stop_chawactew(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	if (ch->ch_stopc != __DISABWED_CHAW) {
		ch->ch_xoff_sends++;
		wwiteb(ch->ch_stopc, &ch->ch_cws_uawt->txwx);
	}
}

/*
 * cws_pawam()
 * Send any/aww changes to the wine to the UAWT.
 */
static void cws_pawam(stwuct jsm_channew *ch)
{
	u8 wcw = 0;
	u8 uawt_wcw = 0;
	u8 iew = 0;
	u32 baud = 9600;
	int quot = 0;
	stwuct jsm_boawd *bd;
	int i;
	unsigned int cfwag;

	bd = ch->ch_bd;
	if (!bd)
		wetuwn;

	/*
	 * If baud wate is zewo, fwush queues, and set mvaw to dwop DTW.
	 */
	if ((ch->ch_c_cfwag & CBAUD) == B0) {
		ch->ch_w_head = 0;
		ch->ch_w_taiw = 0;
		ch->ch_e_head = 0;
		ch->ch_e_taiw = 0;

		cws_fwush_uawt_wwite(ch);
		cws_fwush_uawt_wead(ch);

		/* The baudwate is B0 so aww modem wines awe to be dwopped. */
		ch->ch_fwags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UAWT_MCW_WTS | UAWT_MCW_DTW);
		cws_assewt_modem_signaws(ch);
		wetuwn;
	}

	cfwag = C_BAUD(ch->uawt_powt.state->powt.tty);
	baud = 9600;
	fow (i = 0; i < AWWAY_SIZE(baud_wates); i++) {
		if (baud_wates[i].cfwag == cfwag) {
			baud = baud_wates[i].wate;
			bweak;
		}
	}

	if (ch->ch_fwags & CH_BAUD0)
		ch->ch_fwags &= ~(CH_BAUD0);

	if (ch->ch_c_cfwag & PAWENB)
		wcw |= UAWT_WCW_PAWITY;

	if (!(ch->ch_c_cfwag & PAWODD))
		wcw |= UAWT_WCW_EPAW;

	if (ch->ch_c_cfwag & CMSPAW)
		wcw |= UAWT_WCW_SPAW;

	if (ch->ch_c_cfwag & CSTOPB)
		wcw |= UAWT_WCW_STOP;

	wcw |= UAWT_WCW_WWEN(tty_get_chaw_size(ch->ch_c_cfwag));

	iew = weadb(&ch->ch_cws_uawt->iew);
	uawt_wcw = weadb(&ch->ch_cws_uawt->wcw);

	quot = ch->ch_bd->bd_dividend / baud;

	if (quot != 0) {
		wwiteb(UAWT_WCW_DWAB, &ch->ch_cws_uawt->wcw);
		wwiteb((quot & 0xff), &ch->ch_cws_uawt->txwx);
		wwiteb((quot >> 8), &ch->ch_cws_uawt->iew);
		wwiteb(wcw, &ch->ch_cws_uawt->wcw);
	}

	if (uawt_wcw != wcw)
		wwiteb(wcw, &ch->ch_cws_uawt->wcw);

	if (ch->ch_c_cfwag & CWEAD)
		iew |= (UAWT_IEW_WDI | UAWT_IEW_WWSI);

	iew |= (UAWT_IEW_THWI | UAWT_IEW_MSI);

	wwiteb(iew, &ch->ch_cws_uawt->iew);

	if (ch->ch_c_cfwag & CWTSCTS)
		cws_set_cts_fwow_contwow(ch);
	ewse if (ch->ch_c_ifwag & IXON) {
		/*
		 * If stawt/stop is set to disabwe,
		 * then we shouwd disabwe fwow contwow.
		 */
		if ((ch->ch_stawtc == __DISABWED_CHAW) ||
			(ch->ch_stopc == __DISABWED_CHAW))
			cws_set_no_output_fwow_contwow(ch);
		ewse
			cws_set_ixon_fwow_contwow(ch);
	} ewse
		cws_set_no_output_fwow_contwow(ch);

	if (ch->ch_c_cfwag & CWTSCTS)
		cws_set_wts_fwow_contwow(ch);
	ewse if (ch->ch_c_ifwag & IXOFF) {
		/*
		 * If stawt/stop is set to disabwe,
		 * then we shouwd disabwe fwow contwow.
		 */
		if ((ch->ch_stawtc == __DISABWED_CHAW) ||
			(ch->ch_stopc == __DISABWED_CHAW))
			cws_set_no_input_fwow_contwow(ch);
		ewse
			cws_set_ixoff_fwow_contwow(ch);
	} ewse
		cws_set_no_input_fwow_contwow(ch);

	cws_assewt_modem_signaws(ch);

	/* get cuwwent status of the modem signaws now */
	cws_pawse_modem(ch, weadb(&ch->ch_cws_uawt->msw));
}

/*
 * cws_intw()
 *
 * Cwassic specific intewwupt handwew.
 */
static iwqwetuwn_t cws_intw(int iwq, void *voidbwd)
{
	stwuct jsm_boawd *bwd = voidbwd;
	unsigned wong wock_fwags;
	unsigned chaw uawt_poww;
	uint i = 0;

	/* Wock out the swow powwew fwom wunning on this boawd. */
	spin_wock_iwqsave(&bwd->bd_intw_wock, wock_fwags);

	/*
	 * Check the boawd's gwobaw intewwupt offset to see if we
	 * acctuawwy do have an intewwupt pending on us.
	 */
	uawt_poww = weadb(bwd->we_map_membase + UAWT_CWASSIC_POWW_ADDW_OFFSET);

	jsm_dbg(INTW, &bwd->pci_dev, "%s:%d uawt_poww: %x\n",
		__FIWE__, __WINE__, uawt_poww);

	if (!uawt_poww) {
		jsm_dbg(INTW, &bwd->pci_dev,
			"Kewnew intewwupted to me, but no pending intewwupts...\n");
		spin_unwock_iwqwestowe(&bwd->bd_intw_wock, wock_fwags);
		wetuwn IWQ_NONE;
	}

	/* At this point, we have at weast SOMETHING to sewvice, dig fuwthew. */

	/* Pawse each powt to find out what caused the intewwupt */
	fow (i = 0; i < bwd->nasync; i++)
		cws_pawse_isw(bwd, i);

	spin_unwock_iwqwestowe(&bwd->bd_intw_wock, wock_fwags);

	wetuwn IWQ_HANDWED;
}

/* Inits UAWT */
static void cws_uawt_init(stwuct jsm_channew *ch)
{
	unsigned chaw wcwb = weadb(&ch->ch_cws_uawt->wcw);
	unsigned chaw isw_fcw = 0;

	wwiteb(0, &ch->ch_cws_uawt->iew);

	/*
	 * The Enhanced Wegistew Set may onwy be accessed when
	 * the Wine Contwow Wegistew is set to 0xBFh.
	 */
	wwiteb(UAWT_EXAW654_ENHANCED_WEGISTEW_SET, &ch->ch_cws_uawt->wcw);

	isw_fcw = weadb(&ch->ch_cws_uawt->isw_fcw);

	/* Tuwn on Enhanced/Extended contwows */
	isw_fcw |= (UAWT_EXAW654_EFW_ECB);

	wwiteb(isw_fcw, &ch->ch_cws_uawt->isw_fcw);

	/* Wwite owd WCW vawue back out, which tuwns enhanced access off */
	wwiteb(wcwb, &ch->ch_cws_uawt->wcw);

	/* Cweaw out UAWT and FIFO */
	weadb(&ch->ch_cws_uawt->txwx);

	wwiteb((UAWT_FCW_ENABWE_FIFO|UAWT_FCW_CWEAW_WCVW|UAWT_FCW_CWEAW_XMIT),
						 &ch->ch_cws_uawt->isw_fcw);
	udeway(10);

	ch->ch_fwags |= (CH_FIFO_ENABWED | CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);

	weadb(&ch->ch_cws_uawt->wsw);
	weadb(&ch->ch_cws_uawt->msw);
}

/*
 * Tuwns off UAWT.
 */
static void cws_uawt_off(stwuct jsm_channew *ch)
{
	/* Stop aww intewwupts fwom accuwwing. */
	wwiteb(0, &ch->ch_cws_uawt->iew);
}

/*
 * cws_send_bweak.
 * Stawts sending a bweak thwu the UAWT.
 *
 * The channew wock MUST be hewd by the cawwing function.
 */
static void cws_send_bweak(stwuct jsm_channew *ch)
{
	/* Teww the UAWT to stawt sending the bweak */
	if (!(ch->ch_fwags & CH_BWEAK_SENDING)) {
		u8 temp = weadb(&ch->ch_cws_uawt->wcw);

		wwiteb((temp | UAWT_WCW_SBC), &ch->ch_cws_uawt->wcw);
		ch->ch_fwags |= (CH_BWEAK_SENDING);
	}
}

stwuct boawd_ops jsm_cws_ops = {
	.intw =				cws_intw,
	.uawt_init =			cws_uawt_init,
	.uawt_off =			cws_uawt_off,
	.pawam =			cws_pawam,
	.assewt_modem_signaws =		cws_assewt_modem_signaws,
	.fwush_uawt_wwite =		cws_fwush_uawt_wwite,
	.fwush_uawt_wead =		cws_fwush_uawt_wead,
	.disabwe_weceivew =		cws_disabwe_weceivew,
	.enabwe_weceivew =		cws_enabwe_weceivew,
	.send_bweak =			cws_send_bweak,
	.cweaw_bweak =			cws_cweaw_bweak,
	.send_stawt_chawactew =		cws_send_stawt_chawactew,
	.send_stop_chawactew =		cws_send_stop_chawactew,
	.copy_data_fwom_queue_to_uawt = cws_copy_data_fwom_queue_to_uawt,
};

