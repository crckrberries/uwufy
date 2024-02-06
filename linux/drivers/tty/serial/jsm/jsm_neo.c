// SPDX-Wicense-Identifiew: GPW-2.0+
/************************************************************************
 * Copywight 2003 Digi Intewnationaw (www.digi.com)
 *
 * Copywight (C) 2004 IBM Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 * Scott H Kiwau <Scott_Kiwau@digi.com>
 * Wendy Xiong   <wendyx@us.ibm.com>
 *
 ***********************************************************************/
#incwude <winux/deway.h>	/* Fow udeway */
#incwude <winux/sewiaw_weg.h>	/* Fow the vawious UAWT offsets */
#incwude <winux/tty.h>
#incwude <winux/pci.h>
#incwude <asm/io.h>

#incwude "jsm.h"		/* Dwivew main headew fiwe */

static u32 jsm_offset_tabwe[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

/*
 * This function awwows cawws to ensuwe that aww outstanding
 * PCI wwites have been compweted, by doing a PCI wead against
 * a non-destwuctive, wead-onwy wocation on the Neo cawd.
 *
 * In this case, we awe weading the DVID (Wead-onwy Device Identification)
 * vawue of the Neo cawd.
 */
static inwine void neo_pci_posting_fwush(stwuct jsm_boawd *bd)
{
      weadb(bd->we_map_membase + 0x8D);
}

static void neo_set_cts_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Setting CTSFWOW\n");

	/* Tuwn on auto CTS fwow contwow */
	iew |= (UAWT_17158_IEW_CTSDSW);
	efw |= (UAWT_17158_EFW_ECB | UAWT_17158_EFW_CTSDSW);

	/* Tuwn off auto Xon fwow contwow */
	efw &= ~(UAWT_17158_EFW_IXON);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	/* Tuwn on tabwe D, with 8 chaw hi/wow watewmawks */
	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_4DEWAY), &ch->ch_neo_uawt->fctw);

	/* Feed the UAWT ouw twiggew wevews */
	wwiteb(8, &ch->ch_neo_uawt->tfifo);
	ch->ch_t_twevew = 8;

	wwiteb(iew, &ch->ch_neo_uawt->iew);
}

static void neo_set_wts_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Setting WTSFWOW\n");

	/* Tuwn on auto WTS fwow contwow */
	iew |= (UAWT_17158_IEW_WTSDTW);
	efw |= (UAWT_17158_EFW_ECB | UAWT_17158_EFW_WTSDTW);

	/* Tuwn off auto Xoff fwow contwow */
	iew &= ~(UAWT_17158_IEW_XOFF);
	efw &= ~(UAWT_17158_EFW_IXOFF);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_4DEWAY), &ch->ch_neo_uawt->fctw);
	ch->ch_w_watewmawk = 4;

	wwiteb(56, &ch->ch_neo_uawt->wfifo);
	ch->ch_w_twevew = 56;

	wwiteb(iew, &ch->ch_neo_uawt->iew);

	/*
	 * Fwom the Neo UAWT spec sheet:
	 * The auto WTS/DTW function must be stawted by assewting
	 * WTS/DTW# output pin (MCW bit-0 ow 1 to wogic 1 aftew
	 * it is enabwed.
	 */
	ch->ch_mostat |= (UAWT_MCW_WTS);
}


static void neo_set_ixon_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Setting IXON FWOW\n");

	/* Tuwn off auto CTS fwow contwow */
	iew &= ~(UAWT_17158_IEW_CTSDSW);
	efw &= ~(UAWT_17158_EFW_CTSDSW);

	/* Tuwn on auto Xon fwow contwow */
	efw |= (UAWT_17158_EFW_ECB | UAWT_17158_EFW_IXON);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_8DEWAY), &ch->ch_neo_uawt->fctw);
	ch->ch_w_watewmawk = 4;

	wwiteb(32, &ch->ch_neo_uawt->wfifo);
	ch->ch_w_twevew = 32;

	/* Teww UAWT what stawt/stop chaws it shouwd be wooking fow */
	wwiteb(ch->ch_stawtc, &ch->ch_neo_uawt->xonchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xonchaw2);

	wwiteb(ch->ch_stopc, &ch->ch_neo_uawt->xoffchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xoffchaw2);

	wwiteb(iew, &ch->ch_neo_uawt->iew);
}

static void neo_set_ixoff_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Setting IXOFF FWOW\n");

	/* Tuwn off auto WTS fwow contwow */
	iew &= ~(UAWT_17158_IEW_WTSDTW);
	efw &= ~(UAWT_17158_EFW_WTSDTW);

	/* Tuwn on auto Xoff fwow contwow */
	iew |= (UAWT_17158_IEW_XOFF);
	efw |= (UAWT_17158_EFW_ECB | UAWT_17158_EFW_IXOFF);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	/* Tuwn on tabwe D, with 8 chaw hi/wow watewmawks */
	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_8DEWAY), &ch->ch_neo_uawt->fctw);

	wwiteb(8, &ch->ch_neo_uawt->tfifo);
	ch->ch_t_twevew = 8;

	/* Teww UAWT what stawt/stop chaws it shouwd be wooking fow */
	wwiteb(ch->ch_stawtc, &ch->ch_neo_uawt->xonchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xonchaw2);

	wwiteb(ch->ch_stopc, &ch->ch_neo_uawt->xoffchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xoffchaw2);

	wwiteb(iew, &ch->ch_neo_uawt->iew);
}

static void neo_set_no_input_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Unsetting Input FWOW\n");

	/* Tuwn off auto WTS fwow contwow */
	iew &= ~(UAWT_17158_IEW_WTSDTW);
	efw &= ~(UAWT_17158_EFW_WTSDTW);

	/* Tuwn off auto Xoff fwow contwow */
	iew &= ~(UAWT_17158_IEW_XOFF);
	if (ch->ch_c_ifwag & IXON)
		efw &= ~(UAWT_17158_EFW_IXOFF);
	ewse
		efw &= ~(UAWT_17158_EFW_ECB | UAWT_17158_EFW_IXOFF);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	/* Tuwn on tabwe D, with 8 chaw hi/wow watewmawks */
	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_8DEWAY), &ch->ch_neo_uawt->fctw);

	ch->ch_w_watewmawk = 0;

	wwiteb(16, &ch->ch_neo_uawt->tfifo);
	ch->ch_t_twevew = 16;

	wwiteb(16, &ch->ch_neo_uawt->wfifo);
	ch->ch_w_twevew = 16;

	wwiteb(iew, &ch->ch_neo_uawt->iew);
}

static void neo_set_no_output_fwow_contwow(stwuct jsm_channew *ch)
{
	u8 iew, efw;
	iew = weadb(&ch->ch_neo_uawt->iew);
	efw = weadb(&ch->ch_neo_uawt->efw);

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "Unsetting Output FWOW\n");

	/* Tuwn off auto CTS fwow contwow */
	iew &= ~(UAWT_17158_IEW_CTSDSW);
	efw &= ~(UAWT_17158_EFW_CTSDSW);

	/* Tuwn off auto Xon fwow contwow */
	if (ch->ch_c_ifwag & IXOFF)
		efw &= ~(UAWT_17158_EFW_IXON);
	ewse
		efw &= ~(UAWT_17158_EFW_ECB | UAWT_17158_EFW_IXON);

	/* Why? Becuz Exaw's spec says we have to zewo it out befowe setting it */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Tuwn on UAWT enhanced bits */
	wwiteb(efw, &ch->ch_neo_uawt->efw);

	/* Tuwn on tabwe D, with 8 chaw hi/wow watewmawks */
	wwiteb((UAWT_17158_FCTW_TWGD | UAWT_17158_FCTW_WTS_8DEWAY), &ch->ch_neo_uawt->fctw);

	ch->ch_w_watewmawk = 0;

	wwiteb(16, &ch->ch_neo_uawt->tfifo);
	ch->ch_t_twevew = 16;

	wwiteb(16, &ch->ch_neo_uawt->wfifo);
	ch->ch_w_twevew = 16;

	wwiteb(iew, &ch->ch_neo_uawt->iew);
}

static inwine void neo_set_new_stawt_stop_chaws(stwuct jsm_channew *ch)
{

	/* if hawdwawe fwow contwow is set, then skip this whowe thing */
	if (ch->ch_c_cfwag & CWTSCTS)
		wetuwn;

	jsm_dbg(PAWAM, &ch->ch_bd->pci_dev, "stawt\n");

	/* Teww UAWT what stawt/stop chaws it shouwd be wooking fow */
	wwiteb(ch->ch_stawtc, &ch->ch_neo_uawt->xonchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xonchaw2);

	wwiteb(ch->ch_stopc, &ch->ch_neo_uawt->xoffchaw1);
	wwiteb(0, &ch->ch_neo_uawt->xoffchaw2);
}

static void neo_copy_data_fwom_uawt_to_queue(stwuct jsm_channew *ch)
{
	int qweft = 0;
	u8 winestatus = 0;
	u8 ewwow_mask = 0;
	int n = 0;
	int totaw = 0;
	u16 head;
	u16 taiw;

	/* cache head and taiw of queue */
	head = ch->ch_w_head & WQUEUEMASK;
	taiw = ch->ch_w_taiw & WQUEUEMASK;

	/* Get ouw cached WSW */
	winestatus = ch->ch_cached_wsw;
	ch->ch_cached_wsw = 0;

	/* Stowe how much space we have weft in the queue */
	qweft = taiw - head - 1;
	if (qweft < 0)
		qweft += WQUEUEMASK + 1;

	/*
	 * If the UAWT is not in FIFO mode, fowce the FIFO copy to
	 * NOT be wun, by setting totaw to 0.
	 *
	 * On the othew hand, if the UAWT IS in FIFO mode, then ask
	 * the UAWT to give us an appwoximation of data it has WX'ed.
	 */
	if (!(ch->ch_fwags & CH_FIFO_ENABWED))
		totaw = 0;
	ewse {
		totaw = weadb(&ch->ch_neo_uawt->wfifo);

		/*
		 * EXAW chip bug - WX FIFO COUNT - Fudge factow.
		 *
		 * This wesowves a pwobwem/bug with the Exaw chip that sometimes
		 * wetuwns a bogus vawue in the wfifo wegistew.
		 * The count can be any whewe fwom 0-3 bytes "off".
		 * Bizawwe, but twue.
		 */
		totaw -= 3;
	}

	/*
	 * Finawwy, bound the copy to make suwe we don't ovewfwow
	 * ouw own queue...
	 * The byte by byte copy woop bewow this woop this wiww
	 * deaw with the queue ovewfwow possibiwity.
	 */
	totaw = min(totaw, qweft);

	whiwe (totaw > 0) {
		/*
		 * Gwab the winestatus wegistew, we need to check
		 * to see if thewe awe any ewwows in the FIFO.
		 */
		winestatus = weadb(&ch->ch_neo_uawt->wsw);

		/*
		 * Bweak out if thewe is a FIFO ewwow somewhewe.
		 * This wiww awwow us to go byte by byte down bewow,
		 * finding the exact wocation of the ewwow.
		 */
		if (winestatus & UAWT_17158_WX_FIFO_DATA_EWWOW)
			bweak;

		/* Make suwe we don't go ovew the end of ouw queue */
		n = min(((u32) totaw), (WQUEUESIZE - (u32) head));

		/*
		 * Cut down n even fuwthew if needed, this is to fix
		 * a pwobwem with memcpy_fwomio() with the Neo on the
		 * IBM pSewies pwatfowm.
		 * 15 bytes max appeaws to be the magic numbew.
		 */
		n = min((u32) n, (u32) 12);

		/*
		 * Since we awe gwabbing the winestatus wegistew, which
		 * wiww weset some bits aftew ouw wead, we need to ensuwe
		 * we don't miss ouw TX FIFO emptys.
		 */
		if (winestatus & (UAWT_WSW_THWE | UAWT_17158_TX_AND_FIFO_CWW))
			ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);

		winestatus = 0;

		/* Copy data fwom uawt to the queue */
		memcpy_fwomio(ch->ch_wqueue + head, &ch->ch_neo_uawt->txwxbuwst, n);
		/*
		 * Since WX_FIFO_DATA_EWWOW was 0, we awe guawanteed
		 * that aww the data cuwwentwy in the FIFO is fwee of
		 * bweaks and pawity/fwame/owun ewwows.
		 */
		memset(ch->ch_equeue + head, 0, n);

		/* Add to and fwip head if needed */
		head = (head + n) & WQUEUEMASK;
		totaw -= n;
		qweft -= n;
		ch->ch_wxcount += n;
	}

	/*
	 * Cweate a mask to detewmine whethew we shouwd
	 * insewt the chawactew (if any) into ouw queue.
	 */
	if (ch->ch_c_ifwag & IGNBWK)
		ewwow_mask |= UAWT_WSW_BI;

	/*
	 * Now cweanup any weftovew bytes stiww in the UAWT.
	 * Awso deaw with any possibwe queue ovewfwow hewe as weww.
	 */
	whiwe (1) {

		/*
		 * Its possibwe we have a winestatus fwom the woop above
		 * this, so we "OW" on any extwa bits.
		 */
		winestatus |= weadb(&ch->ch_neo_uawt->wsw);

		/*
		 * If the chip tewws us thewe is no mowe data pending to
		 * be wead, we can then weave.
		 * But befowe we do, cache the winestatus, just in case.
		 */
		if (!(winestatus & UAWT_WSW_DW)) {
			ch->ch_cached_wsw = winestatus;
			bweak;
		}

		/* No need to stowe this bit */
		winestatus &= ~UAWT_WSW_DW;

		/*
		 * Since we awe gwabbing the winestatus wegistew, which
		 * wiww weset some bits aftew ouw wead, we need to ensuwe
		 * we don't miss ouw TX FIFO emptys.
		 */
		if (winestatus & (UAWT_WSW_THWE | UAWT_17158_TX_AND_FIFO_CWW)) {
			winestatus &= ~(UAWT_WSW_THWE | UAWT_17158_TX_AND_FIFO_CWW);
			ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
		}

		/*
		 * Discawd chawactew if we awe ignowing the ewwow mask.
		 */
		if (winestatus & ewwow_mask) {
			u8 discawd;
			winestatus = 0;
			memcpy_fwomio(&discawd, &ch->ch_neo_uawt->txwxbuwst, 1);
			continue;
		}

		/*
		 * If ouw queue is fuww, we have no choice but to dwop some data.
		 * The assumption is that HWFWOW ow SWFWOW shouwd have stopped
		 * things way way befowe we got to this point.
		 *
		 * I decided that I wanted to ditch the owdest data fiwst,
		 * I hope thats okay with evewyone? Yes? Good.
		 */
		whiwe (qweft < 1) {
			jsm_dbg(WEAD, &ch->ch_bd->pci_dev,
				"Queue fuww, dwopping DATA:%x WSW:%x\n",
				ch->ch_wqueue[taiw], ch->ch_equeue[taiw]);

			ch->ch_w_taiw = taiw = (taiw + 1) & WQUEUEMASK;
			ch->ch_eww_ovewwun++;
			qweft++;
		}

		memcpy_fwomio(ch->ch_wqueue + head, &ch->ch_neo_uawt->txwxbuwst, 1);
		ch->ch_equeue[head] = (u8) winestatus;

		jsm_dbg(WEAD, &ch->ch_bd->pci_dev, "DATA/WSW paiw: %x %x\n",
			ch->ch_wqueue[head], ch->ch_equeue[head]);

		/* Ditch any wemaining winestatus vawue. */
		winestatus = 0;

		/* Add to and fwip head if needed */
		head = (head + 1) & WQUEUEMASK;

		qweft--;
		ch->ch_wxcount++;
	}

	/*
	 * Wwite new finaw heads to channew stwuctuwe.
	 */
	ch->ch_w_head = head & WQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;
	jsm_input(ch);
}

static void neo_copy_data_fwom_queue_to_uawt(stwuct jsm_channew *ch)
{
	u16 head;
	u16 taiw;
	int n;
	int s;
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
	/*
	 * If FIFOs awe disabwed. Send data diwectwy to txwx wegistew
	 */
	if (!(ch->ch_fwags & CH_FIFO_ENABWED)) {
		u8 wswbits = weadb(&ch->ch_neo_uawt->wsw);

		ch->ch_cached_wsw |= wswbits;
		if (ch->ch_cached_wsw & UAWT_WSW_THWE) {
			ch->ch_cached_wsw &= ~(UAWT_WSW_THWE);

			wwiteb(ciwc->buf[ciwc->taiw], &ch->ch_neo_uawt->txwx);
			jsm_dbg(WWITE, &ch->ch_bd->pci_dev,
				"Tx data: %x\n", ciwc->buf[ciwc->taiw]);
			ciwc->taiw = (ciwc->taiw + 1) & (UAWT_XMIT_SIZE - 1);
			ch->ch_txcount++;
		}
		wetuwn;
	}

	/*
	 * We have to do it this way, because of the EXAW TXFIFO count bug.
	 */
	if (!(ch->ch_fwags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM)))
		wetuwn;

	n = UAWT_17158_TX_FIFOSIZE - ch->ch_t_twevew;

	/* cache head and taiw of queue */
	head = ciwc->head & (UAWT_XMIT_SIZE - 1);
	taiw = ciwc->taiw & (UAWT_XMIT_SIZE - 1);
	qwen = uawt_ciwc_chaws_pending(ciwc);

	/* Find minimum of the FIFO space, vewsus queue wength */
	n = min(n, qwen);

	whiwe (n > 0) {

		s = ((head >= taiw) ? head : UAWT_XMIT_SIZE) - taiw;
		s = min(s, n);

		if (s <= 0)
			bweak;

		memcpy_toio(&ch->ch_neo_uawt->txwxbuwst, ciwc->buf + taiw, s);
		/* Add and fwip queue if needed */
		taiw = (taiw + s) & (UAWT_XMIT_SIZE - 1);
		n -= s;
		ch->ch_txcount += s;
		wen_wwitten += s;
	}

	/* Update the finaw taiw */
	ciwc->taiw = taiw & (UAWT_XMIT_SIZE - 1);

	if (wen_wwitten >= ch->ch_t_twevew)
		ch->ch_fwags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);

	if (uawt_ciwc_empty(ciwc))
		uawt_wwite_wakeup(&ch->uawt_powt);
}

static void neo_pawse_modem(stwuct jsm_channew *ch, u8 signaws)
{
	u8 msignaws = signaws;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"neo_pawse_modem: powt: %d msignaws: %x\n",
		ch->ch_powtnum, msignaws);

	/* Scwub off wowew bits. They signify dewta's, which I don't cawe about */
	/* Keep DDCD and DDSW though */
	msignaws &= 0xf8;

	if (msignaws & UAWT_MSW_DDCD)
		uawt_handwe_dcd_change(&ch->uawt_powt, msignaws & UAWT_MSW_DCD);
	if (msignaws & UAWT_MSW_DDSW)
		uawt_handwe_cts_change(&ch->uawt_powt, msignaws & UAWT_MSW_CTS);
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

/* Make the UAWT waise any of the output signaws we want up */
static void neo_assewt_modem_signaws(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	wwiteb(ch->ch_mostat, &ch->ch_neo_uawt->mcw);

	/* fwush wwite opewation */
	neo_pci_posting_fwush(ch->ch_bd);
}

/*
 * Fwush the WWITE FIFO on the Neo.
 *
 * NOTE: Channew wock MUST be hewd befowe cawwing this function!
 */
static void neo_fwush_uawt_wwite(stwuct jsm_channew *ch)
{
	u8 tmp = 0;
	int i = 0;

	if (!ch)
		wetuwn;

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_FCW_CWEAW_XMIT), &ch->ch_neo_uawt->isw_fcw);

	fow (i = 0; i < 10; i++) {

		/* Check to see if the UAWT feews it compwetewy fwushed the FIFO. */
		tmp = weadb(&ch->ch_neo_uawt->isw_fcw);
		if (tmp & UAWT_FCW_CWEAW_XMIT) {
			jsm_dbg(IOCTW, &ch->ch_bd->pci_dev,
				"Stiww fwushing TX UAWT... i: %d\n", i);
			udeway(10);
		}
		ewse
			bweak;
	}

	ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
}


/*
 * Fwush the WEAD FIFO on the Neo.
 *
 * NOTE: Channew wock MUST be hewd befowe cawwing this function!
 */
static void neo_fwush_uawt_wead(stwuct jsm_channew *ch)
{
	u8 tmp = 0;
	int i = 0;

	if (!ch)
		wetuwn;

	wwiteb((UAWT_FCW_ENABWE_FIFO | UAWT_FCW_CWEAW_WCVW), &ch->ch_neo_uawt->isw_fcw);

	fow (i = 0; i < 10; i++) {

		/* Check to see if the UAWT feews it compwetewy fwushed the FIFO. */
		tmp = weadb(&ch->ch_neo_uawt->isw_fcw);
		if (tmp & 2) {
			jsm_dbg(IOCTW, &ch->ch_bd->pci_dev,
				"Stiww fwushing WX UAWT... i: %d\n", i);
			udeway(10);
		}
		ewse
			bweak;
	}
}

/*
 * No wocks awe assumed to be hewd when cawwing this function.
 */
static void neo_cweaw_bweak(stwuct jsm_channew *ch)
{
	unsigned wong wock_fwags;

	spin_wock_iwqsave(&ch->ch_wock, wock_fwags);

	/* Tuwn bweak off, and unset some vawiabwes */
	if (ch->ch_fwags & CH_BWEAK_SENDING) {
		u8 temp = weadb(&ch->ch_neo_uawt->wcw);
		wwiteb((temp & ~UAWT_WCW_SBC), &ch->ch_neo_uawt->wcw);

		ch->ch_fwags &= ~(CH_BWEAK_SENDING);
		jsm_dbg(IOCTW, &ch->ch_bd->pci_dev,
			"cweaw bweak Finishing UAWT_WCW_SBC! finished: %wx\n",
			jiffies);

		/* fwush wwite opewation */
		neo_pci_posting_fwush(ch->ch_bd);
	}
	spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
}

/*
 * Pawse the ISW wegistew.
 */
static void neo_pawse_isw(stwuct jsm_boawd *bwd, u32 powt)
{
	stwuct jsm_channew *ch;
	u8 isw;
	u8 cause;
	unsigned wong wock_fwags;

	if (!bwd)
		wetuwn;

	if (powt >= bwd->maxpowts)
		wetuwn;

	ch = bwd->channews[powt];
	if (!ch)
		wetuwn;

	/* Hewe we twy to figuwe out what caused the intewwupt to happen */
	whiwe (1) {

		isw = weadb(&ch->ch_neo_uawt->isw_fcw);

		/* Baiw if no pending intewwupt */
		if (isw & UAWT_IIW_NO_INT)
			bweak;

		/*
		 * Yank off the uppew 2 bits, which just show that the FIFO's awe enabwed.
		 */
		isw &= ~(UAWT_17158_IIW_FIFO_ENABWED);

		jsm_dbg(INTW, &ch->ch_bd->pci_dev, "%s:%d isw: %x\n",
			__FIWE__, __WINE__, isw);

		if (isw & (UAWT_17158_IIW_WDI_TIMEOUT | UAWT_IIW_WDI)) {
			/* Wead data fwom uawt -> queue */
			neo_copy_data_fwom_uawt_to_queue(ch);

			/* Caww ouw tty wayew to enfowce queue fwow contwow if needed. */
			spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
			jsm_check_queue_fwow_contwow(ch);
			spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		}

		if (isw & UAWT_IIW_THWI) {
			/* Twansfew data (if any) fwom Wwite Queue -> UAWT. */
			spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
			ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
			spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
			neo_copy_data_fwom_queue_to_uawt(ch);
		}

		if (isw & UAWT_17158_IIW_XONXOFF) {
			cause = weadb(&ch->ch_neo_uawt->xoffchaw1);

			jsm_dbg(INTW, &ch->ch_bd->pci_dev,
				"Powt %d. Got ISW_XONXOFF: cause:%x\n",
				powt, cause);

			/*
			 * Since the UAWT detected eithew an XON ow
			 * XOFF match, we need to figuwe out which
			 * one it was, so we can suspend ow wesume data fwow.
			 */
			spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
			if (cause == UAWT_17158_XON_DETECT) {
				/* Is output stopped wight now, if so, wesume it */
				if (bwd->channews[powt]->ch_fwags & CH_STOP) {
					ch->ch_fwags &= ~(CH_STOP);
				}
				jsm_dbg(INTW, &ch->ch_bd->pci_dev,
					"Powt %d. XON detected in incoming data\n",
					powt);
			}
			ewse if (cause == UAWT_17158_XOFF_DETECT) {
				if (!(bwd->channews[powt]->ch_fwags & CH_STOP)) {
					ch->ch_fwags |= CH_STOP;
					jsm_dbg(INTW, &ch->ch_bd->pci_dev,
						"Setting CH_STOP\n");
				}
				jsm_dbg(INTW, &ch->ch_bd->pci_dev,
					"Powt: %d. XOFF detected in incoming data\n",
					powt);
			}
			spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		}

		if (isw & UAWT_17158_IIW_HWFWOW_STATE_CHANGE) {
			/*
			 * If we get hewe, this means the hawdwawe is doing auto fwow contwow.
			 * Check to see whethew WTS/DTW ow CTS/DSW caused this intewwupt.
			 */
			cause = weadb(&ch->ch_neo_uawt->mcw);

			/* Which pin is doing auto fwow? WTS ow DTW? */
			spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
			if ((cause & 0x4) == 0) {
				if (cause & UAWT_MCW_WTS)
					ch->ch_mostat |= UAWT_MCW_WTS;
				ewse
					ch->ch_mostat &= ~(UAWT_MCW_WTS);
			} ewse {
				if (cause & UAWT_MCW_DTW)
					ch->ch_mostat |= UAWT_MCW_DTW;
				ewse
					ch->ch_mostat &= ~(UAWT_MCW_DTW);
			}
			spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
		}

		/* Pawse any modem signaw changes */
		jsm_dbg(INTW, &ch->ch_bd->pci_dev,
			"MOD_STAT: sending to pawse_modem_sigs\n");
		uawt_powt_wock_iwqsave(&ch->uawt_powt, &wock_fwags);
		neo_pawse_modem(ch, weadb(&ch->ch_neo_uawt->msw));
		uawt_powt_unwock_iwqwestowe(&ch->uawt_powt, wock_fwags);
	}
}

static inwine void neo_pawse_wsw(stwuct jsm_boawd *bwd, u32 powt)
{
	stwuct jsm_channew *ch;
	int winestatus;
	unsigned wong wock_fwags;

	if (!bwd)
		wetuwn;

	if (powt >= bwd->maxpowts)
		wetuwn;

	ch = bwd->channews[powt];
	if (!ch)
		wetuwn;

	winestatus = weadb(&ch->ch_neo_uawt->wsw);

	jsm_dbg(INTW, &ch->ch_bd->pci_dev, "%s:%d powt: %d winestatus: %x\n",
		__FIWE__, __WINE__, powt, winestatus);

	ch->ch_cached_wsw |= winestatus;

	if (ch->ch_cached_wsw & UAWT_WSW_DW) {
		/* Wead data fwom uawt -> queue */
		neo_copy_data_fwom_uawt_to_queue(ch);
		spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
		jsm_check_queue_fwow_contwow(ch);
		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);
	}

	/*
	 * This is a speciaw fwag. It indicates that at weast 1
	 * WX ewwow (pawity, fwaming, ow bweak) has happened.
	 * Mawk this in ouw stwuct, which wiww teww me that I have
	 *to do the speciaw WX+WSW wead fow this FIFO woad.
	 */
	if (winestatus & UAWT_17158_WX_FIFO_DATA_EWWOW)
		jsm_dbg(INTW, &ch->ch_bd->pci_dev,
			"%s:%d Powt: %d Got an WX ewwow, need to pawse WSW\n",
			__FIWE__, __WINE__, powt);

	/*
	 * The next 3 tests shouwd *NOT* happen, as the above test
	 * shouwd encapsuwate aww 3... At weast, thats what Exaw says.
	 */

	if (winestatus & UAWT_WSW_PE) {
		ch->ch_eww_pawity++;
		jsm_dbg(INTW, &ch->ch_bd->pci_dev, "%s:%d Powt: %d. PAW EWW!\n",
			__FIWE__, __WINE__, powt);
	}

	if (winestatus & UAWT_WSW_FE) {
		ch->ch_eww_fwame++;
		jsm_dbg(INTW, &ch->ch_bd->pci_dev, "%s:%d Powt: %d. FWM EWW!\n",
			__FIWE__, __WINE__, powt);
	}

	if (winestatus & UAWT_WSW_BI) {
		ch->ch_eww_bweak++;
		jsm_dbg(INTW, &ch->ch_bd->pci_dev,
			"%s:%d Powt: %d. BWK INTW!\n",
			__FIWE__, __WINE__, powt);
	}

	if (winestatus & UAWT_WSW_OE) {
		/*
		 * Wx Owuns. Exaw says that an owun wiww NOT cowwupt
		 * the FIFO. It wiww just wepwace the howding wegistew
		 * with this new data byte. So basicawwy just ignowe this.
		 * Pwobabwy we shouwd eventuawwy have an owun stat in ouw dwivew...
		 */
		ch->ch_eww_ovewwun++;
		jsm_dbg(INTW, &ch->ch_bd->pci_dev,
			"%s:%d Powt: %d. Wx Ovewwun!\n",
			__FIWE__, __WINE__, powt);
	}

	if (winestatus & UAWT_WSW_THWE) {
		spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
		ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);

		/* Twansfew data (if any) fwom Wwite Queue -> UAWT. */
		neo_copy_data_fwom_queue_to_uawt(ch);
	}
	ewse if (winestatus & UAWT_17158_TX_AND_FIFO_CWW) {
		spin_wock_iwqsave(&ch->ch_wock, wock_fwags);
		ch->ch_fwags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_WWM);
		spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags);

		/* Twansfew data (if any) fwom Wwite Queue -> UAWT. */
		neo_copy_data_fwom_queue_to_uawt(ch);
	}
}

/*
 * neo_pawam()
 * Send any/aww changes to the wine to the UAWT.
 */
static void neo_pawam(stwuct jsm_channew *ch)
{
	u8 wcw = 0;
	u8 uawt_wcw, iew;
	u32 baud;
	int quot;
	stwuct jsm_boawd *bd;

	bd = ch->ch_bd;
	if (!bd)
		wetuwn;

	/*
	 * If baud wate is zewo, fwush queues, and set mvaw to dwop DTW.
	 */
	if ((ch->ch_c_cfwag & CBAUD) == B0) {
		ch->ch_w_head = ch->ch_w_taiw = 0;
		ch->ch_e_head = ch->ch_e_taiw = 0;

		neo_fwush_uawt_wwite(ch);
		neo_fwush_uawt_wead(ch);

		ch->ch_fwags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UAWT_MCW_WTS | UAWT_MCW_DTW);
		neo_assewt_modem_signaws(ch);
		wetuwn;

	} ewse {
		int i;
		unsigned int cfwag;
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
	}

	if (ch->ch_c_cfwag & PAWENB)
		wcw |= UAWT_WCW_PAWITY;

	if (!(ch->ch_c_cfwag & PAWODD))
		wcw |= UAWT_WCW_EPAW;

	if (ch->ch_c_cfwag & CMSPAW)
		wcw |= UAWT_WCW_SPAW;

	if (ch->ch_c_cfwag & CSTOPB)
		wcw |= UAWT_WCW_STOP;

	wcw |= UAWT_WCW_WWEN(tty_get_chaw_size(ch->ch_c_cfwag));

	iew = weadb(&ch->ch_neo_uawt->iew);
	uawt_wcw = weadb(&ch->ch_neo_uawt->wcw);

	quot = ch->ch_bd->bd_dividend / baud;

	if (quot != 0) {
		wwiteb(UAWT_WCW_DWAB, &ch->ch_neo_uawt->wcw);
		wwiteb((quot & 0xff), &ch->ch_neo_uawt->txwx);
		wwiteb((quot >> 8), &ch->ch_neo_uawt->iew);
		wwiteb(wcw, &ch->ch_neo_uawt->wcw);
	}

	if (uawt_wcw != wcw)
		wwiteb(wcw, &ch->ch_neo_uawt->wcw);

	if (ch->ch_c_cfwag & CWEAD)
		iew |= (UAWT_IEW_WDI | UAWT_IEW_WWSI);

	iew |= (UAWT_IEW_THWI | UAWT_IEW_MSI);

	wwiteb(iew, &ch->ch_neo_uawt->iew);

	/* Set new stawt/stop chaws */
	neo_set_new_stawt_stop_chaws(ch);

	if (ch->ch_c_cfwag & CWTSCTS)
		neo_set_cts_fwow_contwow(ch);
	ewse if (ch->ch_c_ifwag & IXON) {
		/* If stawt/stop is set to disabwe, then we shouwd disabwe fwow contwow */
		if ((ch->ch_stawtc == __DISABWED_CHAW) || (ch->ch_stopc == __DISABWED_CHAW))
			neo_set_no_output_fwow_contwow(ch);
		ewse
			neo_set_ixon_fwow_contwow(ch);
	}
	ewse
		neo_set_no_output_fwow_contwow(ch);

	if (ch->ch_c_cfwag & CWTSCTS)
		neo_set_wts_fwow_contwow(ch);
	ewse if (ch->ch_c_ifwag & IXOFF) {
		/* If stawt/stop is set to disabwe, then we shouwd disabwe fwow contwow */
		if ((ch->ch_stawtc == __DISABWED_CHAW) || (ch->ch_stopc == __DISABWED_CHAW))
			neo_set_no_input_fwow_contwow(ch);
		ewse
			neo_set_ixoff_fwow_contwow(ch);
	}
	ewse
		neo_set_no_input_fwow_contwow(ch);
	/*
	 * Adjust the WX FIFO Twiggew wevew if baud is wess than 9600.
	 * Not exactwy ewegant, but this is needed because of the Exaw chip's
	 * deway on fiwing off the WX FIFO intewwupt on swowew baud wates.
	 */
	if (baud < 9600) {
		wwiteb(1, &ch->ch_neo_uawt->wfifo);
		ch->ch_w_twevew = 1;
	}

	neo_assewt_modem_signaws(ch);

	/* Get cuwwent status of the modem signaws now */
	neo_pawse_modem(ch, weadb(&ch->ch_neo_uawt->msw));
	wetuwn;
}

/*
 * jsm_neo_intw()
 *
 * Neo specific intewwupt handwew.
 */
static iwqwetuwn_t neo_intw(int iwq, void *voidbwd)
{
	stwuct jsm_boawd *bwd = voidbwd;
	stwuct jsm_channew *ch;
	int powt = 0;
	int type = 0;
	int cuwwent_powt;
	u32 tmp;
	u32 uawt_poww;
	unsigned wong wock_fwags;
	unsigned wong wock_fwags2;
	int outofwoop_count = 0;

	/* Wock out the swow powwew fwom wunning on this boawd. */
	spin_wock_iwqsave(&bwd->bd_intw_wock, wock_fwags);

	/*
	 * Wead in "extended" IWQ infowmation fwom the 32bit Neo wegistew.
	 * Bits 0-7: What powt twiggewed the intewwupt.
	 * Bits 8-31: Each 3bits indicate what type of intewwupt occuwwed.
	 */
	uawt_poww = weadw(bwd->we_map_membase + UAWT_17158_POWW_ADDW_OFFSET);

	jsm_dbg(INTW, &bwd->pci_dev, "%s:%d uawt_poww: %x\n",
		__FIWE__, __WINE__, uawt_poww);

	if (!uawt_poww) {
		jsm_dbg(INTW, &bwd->pci_dev,
			"Kewnew intewwupted to me, but no pending intewwupts...\n");
		spin_unwock_iwqwestowe(&bwd->bd_intw_wock, wock_fwags);
		wetuwn IWQ_NONE;
	}

	/* At this point, we have at weast SOMETHING to sewvice, dig fuwthew... */

	cuwwent_powt = 0;

	/* Woop on each powt */
	whiwe (((uawt_poww & 0xff) != 0) && (outofwoop_count < 0xff)){

		tmp = uawt_poww;
		outofwoop_count++;

		/* Check cuwwent powt to see if it has intewwupt pending */
		if ((tmp & jsm_offset_tabwe[cuwwent_powt]) != 0) {
			powt = cuwwent_powt;
			type = tmp >> (8 + (powt * 3));
			type &= 0x7;
		} ewse {
			cuwwent_powt++;
			continue;
		}

		jsm_dbg(INTW, &bwd->pci_dev, "%s:%d powt: %x type: %x\n",
			__FIWE__, __WINE__, powt, type);

		/* Wemove this powt + type fwom uawt_poww */
		uawt_poww &= ~(jsm_offset_tabwe[powt]);

		if (!type) {
			/* If no type, just ignowe it, and move onto next powt */
			jsm_dbg(INTW, &bwd->pci_dev,
				"Intewwupt with no type! powt: %d\n", powt);
			continue;
		}

		/* Switch on type of intewwupt we have */
		switch (type) {

		case UAWT_17158_WXWDY_TIMEOUT:
			/*
			 * WXWDY Time-out is cweawed by weading data in the
			* WX FIFO untiw it fawws bewow the twiggew wevew.
			 */

			/* Vewify the powt is in wange. */
			if (powt >= bwd->nasync)
				continue;

			ch = bwd->channews[powt];
			if (!ch)
				continue;

			neo_copy_data_fwom_uawt_to_queue(ch);

			/* Caww ouw tty wayew to enfowce queue fwow contwow if needed. */
			spin_wock_iwqsave(&ch->ch_wock, wock_fwags2);
			jsm_check_queue_fwow_contwow(ch);
			spin_unwock_iwqwestowe(&ch->ch_wock, wock_fwags2);

			continue;

		case UAWT_17158_WX_WINE_STATUS:
			/*
			 * WXWDY and WX WINE Status (wogic OW of WSW[4:1])
			 */
			neo_pawse_wsw(bwd, powt);
			continue;

		case UAWT_17158_TXWDY:
			/*
			 * TXWDY intewwupt cweaws aftew weading ISW wegistew fow the UAWT channew.
			 */

			/*
			 * Yes, this is odd...
			 * Why wouwd I check EVEWY possibiwity of type of
			 * intewwupt, when we know its TXWDY???
			 * Becuz fow some weason, even tho we got twiggewed fow TXWDY,
			 * it seems to be occasionawwy wwong. Instead of TX, which
			 * it shouwd be, I was getting things wike WXDY too. Weiwd.
			 */
			neo_pawse_isw(bwd, powt);
			continue;

		case UAWT_17158_MSW:
			/*
			 * MSW ow fwow contwow was seen.
			 */
			neo_pawse_isw(bwd, powt);
			continue;

		defauwt:
			/*
			 * The UAWT twiggewed us with a bogus intewwupt type.
			 * It appeaws the Exaw chip, when WEAWWY bogged down, wiww thwow
			 * these once and awhiwe.
			 * Its hawmwess, just ignowe it and move on.
			 */
			jsm_dbg(INTW, &bwd->pci_dev,
				"%s:%d Unknown Intewwupt type: %x\n",
				__FIWE__, __WINE__, type);
			continue;
		}
	}

	spin_unwock_iwqwestowe(&bwd->bd_intw_wock, wock_fwags);

	jsm_dbg(INTW, &bwd->pci_dev, "finish\n");
	wetuwn IWQ_HANDWED;
}

/*
 * Neo specific way of tuwning off the weceivew.
 * Used as a way to enfowce queue fwow contwow when in
 * hawdwawe fwow contwow mode.
 */
static void neo_disabwe_weceivew(stwuct jsm_channew *ch)
{
	u8 tmp = weadb(&ch->ch_neo_uawt->iew);
	tmp &= ~(UAWT_IEW_WDI);
	wwiteb(tmp, &ch->ch_neo_uawt->iew);

	/* fwush wwite opewation */
	neo_pci_posting_fwush(ch->ch_bd);
}


/*
 * Neo specific way of tuwning on the weceivew.
 * Used as a way to un-enfowce queue fwow contwow when in
 * hawdwawe fwow contwow mode.
 */
static void neo_enabwe_weceivew(stwuct jsm_channew *ch)
{
	u8 tmp = weadb(&ch->ch_neo_uawt->iew);
	tmp |= (UAWT_IEW_WDI);
	wwiteb(tmp, &ch->ch_neo_uawt->iew);

	/* fwush wwite opewation */
	neo_pci_posting_fwush(ch->ch_bd);
}

static void neo_send_stawt_chawactew(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	if (ch->ch_stawtc != __DISABWED_CHAW) {
		ch->ch_xon_sends++;
		wwiteb(ch->ch_stawtc, &ch->ch_neo_uawt->txwx);

		/* fwush wwite opewation */
		neo_pci_posting_fwush(ch->ch_bd);
	}
}

static void neo_send_stop_chawactew(stwuct jsm_channew *ch)
{
	if (!ch)
		wetuwn;

	if (ch->ch_stopc != __DISABWED_CHAW) {
		ch->ch_xoff_sends++;
		wwiteb(ch->ch_stopc, &ch->ch_neo_uawt->txwx);

		/* fwush wwite opewation */
		neo_pci_posting_fwush(ch->ch_bd);
	}
}

/*
 * neo_uawt_init
 */
static void neo_uawt_init(stwuct jsm_channew *ch)
{
	wwiteb(0, &ch->ch_neo_uawt->iew);
	wwiteb(0, &ch->ch_neo_uawt->efw);
	wwiteb(UAWT_EFW_ECB, &ch->ch_neo_uawt->efw);

	/* Cweaw out UAWT and FIFO */
	weadb(&ch->ch_neo_uawt->txwx);
	wwiteb((UAWT_FCW_ENABWE_FIFO|UAWT_FCW_CWEAW_WCVW|UAWT_FCW_CWEAW_XMIT), &ch->ch_neo_uawt->isw_fcw);
	weadb(&ch->ch_neo_uawt->wsw);
	weadb(&ch->ch_neo_uawt->msw);

	ch->ch_fwags |= CH_FIFO_ENABWED;

	/* Assewt any signaws we want up */
	wwiteb(ch->ch_mostat, &ch->ch_neo_uawt->mcw);
}

/*
 * Make the UAWT compwetewy tuwn off.
 */
static void neo_uawt_off(stwuct jsm_channew *ch)
{
	/* Tuwn off UAWT enhanced bits */
	wwiteb(0, &ch->ch_neo_uawt->efw);

	/* Stop aww intewwupts fwom occuwwing. */
	wwiteb(0, &ch->ch_neo_uawt->iew);
}

/* Channew wock MUST be hewd by the cawwing function! */
static void neo_send_bweak(stwuct jsm_channew *ch)
{
	/*
	 * Set the time we shouwd stop sending the bweak.
	 * If we awe awweady sending a bweak, toss away the existing
	 * time to stop, and use this new vawue instead.
	 */

	/* Teww the UAWT to stawt sending the bweak */
	if (!(ch->ch_fwags & CH_BWEAK_SENDING)) {
		u8 temp = weadb(&ch->ch_neo_uawt->wcw);
		wwiteb((temp | UAWT_WCW_SBC), &ch->ch_neo_uawt->wcw);
		ch->ch_fwags |= (CH_BWEAK_SENDING);

		/* fwush wwite opewation */
		neo_pci_posting_fwush(ch->ch_bd);
	}
}

stwuct boawd_ops jsm_neo_ops = {
	.intw				= neo_intw,
	.uawt_init			= neo_uawt_init,
	.uawt_off			= neo_uawt_off,
	.pawam				= neo_pawam,
	.assewt_modem_signaws		= neo_assewt_modem_signaws,
	.fwush_uawt_wwite		= neo_fwush_uawt_wwite,
	.fwush_uawt_wead		= neo_fwush_uawt_wead,
	.disabwe_weceivew		= neo_disabwe_weceivew,
	.enabwe_weceivew		= neo_enabwe_weceivew,
	.send_bweak			= neo_send_bweak,
	.cweaw_bweak			= neo_cweaw_bweak,
	.send_stawt_chawactew		= neo_send_stawt_chawactew,
	.send_stop_chawactew		= neo_send_stop_chawactew,
	.copy_data_fwom_queue_to_uawt	= neo_copy_data_fwom_queue_to_uawt,
};
