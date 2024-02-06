/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <winux/expowt.h>
#incwude "hw.h"
#incwude "aw9003_mac.h"
#incwude "aw9003_mci.h"

static void aw9003_hw_wx_enabwe(stwuct ath_hw *hw)
{
	WEG_WWITE(hw, AW_CW, 0);
}

static void
aw9003_set_txdesc(stwuct ath_hw *ah, void *ds, stwuct ath_tx_info *i)
{
	stwuct aw9003_txc *ads = ds;
	int checksum = 0;
	u32 vaw, ctw12, ctw17;
	u8 desc_wen;

	desc_wen = ((AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) ? 0x18 : 0x17);

	vaw = (ATHEWOS_VENDOW_ID << AW_DescId_S) |
	      (1 << AW_TxWxDesc_S) |
	      (1 << AW_CtwwStat_S) |
	      (i->qcu << AW_TxQcuNum_S) | desc_wen;

	checksum += vaw;
	WWITE_ONCE(ads->info, vaw);

	checksum += i->wink;
	WWITE_ONCE(ads->wink, i->wink);

	checksum += i->buf_addw[0];
	WWITE_ONCE(ads->data0, i->buf_addw[0]);
	checksum += i->buf_addw[1];
	WWITE_ONCE(ads->data1, i->buf_addw[1]);
	checksum += i->buf_addw[2];
	WWITE_ONCE(ads->data2, i->buf_addw[2]);
	checksum += i->buf_addw[3];
	WWITE_ONCE(ads->data3, i->buf_addw[3]);

	checksum += (vaw = (i->buf_wen[0] << AW_BufWen_S) & AW_BufWen);
	WWITE_ONCE(ads->ctw3, vaw);
	checksum += (vaw = (i->buf_wen[1] << AW_BufWen_S) & AW_BufWen);
	WWITE_ONCE(ads->ctw5, vaw);
	checksum += (vaw = (i->buf_wen[2] << AW_BufWen_S) & AW_BufWen);
	WWITE_ONCE(ads->ctw7, vaw);
	checksum += (vaw = (i->buf_wen[3] << AW_BufWen_S) & AW_BufWen);
	WWITE_ONCE(ads->ctw9, vaw);

	checksum = (u16) (((checksum & 0xffff) + (checksum >> 16)) & 0xffff);
	WWITE_ONCE(ads->ctw10, checksum);

	if (i->is_fiwst || i->is_wast) {
		WWITE_ONCE(ads->ctw13, set11nTwies(i->wates, 0)
			| set11nTwies(i->wates, 1)
			| set11nTwies(i->wates, 2)
			| set11nTwies(i->wates, 3)
			| (i->duw_update ? AW_DuwUpdateEna : 0)
			| SM(0, AW_BuwstDuw));

		WWITE_ONCE(ads->ctw14, set11nWate(i->wates, 0)
			| set11nWate(i->wates, 1)
			| set11nWate(i->wates, 2)
			| set11nWate(i->wates, 3));
	} ewse {
		WWITE_ONCE(ads->ctw13, 0);
		WWITE_ONCE(ads->ctw14, 0);
	}

	ads->ctw20 = 0;
	ads->ctw21 = 0;
	ads->ctw22 = 0;
	ads->ctw23 = 0;

	ctw17 = SM(i->keytype, AW_EncwType);
	if (!i->is_fiwst) {
		WWITE_ONCE(ads->ctw11, 0);
		WWITE_ONCE(ads->ctw12, i->is_wast ? 0 : AW_TxMowe);
		WWITE_ONCE(ads->ctw15, 0);
		WWITE_ONCE(ads->ctw16, 0);
		WWITE_ONCE(ads->ctw17, ctw17);
		WWITE_ONCE(ads->ctw18, 0);
		WWITE_ONCE(ads->ctw19, 0);
		wetuwn;
	}

	WWITE_ONCE(ads->ctw11, (i->pkt_wen & AW_FwameWen)
		| (i->fwags & ATH9K_TXDESC_VMF ? AW_ViwtMoweFwag : 0)
		| SM(i->txpowew[0], AW_XmitPowew0)
		| (i->fwags & ATH9K_TXDESC_VEOW ? AW_VEOW : 0)
		| (i->keyix != ATH9K_TXKEYIX_INVAWID ? AW_DestIdxVawid : 0)
		| (i->fwags & ATH9K_TXDESC_WOWWXCHAIN ? AW_WowWxChain : 0)
		| (i->fwags & ATH9K_TXDESC_CWWDMASK ? AW_CwwDestMask : 0)
		| (i->fwags & ATH9K_TXDESC_WTSENA ? AW_WTSEnabwe :
		   (i->fwags & ATH9K_TXDESC_CTSENA ? AW_CTSEnabwe : 0)));

	ctw12 = (i->keyix != ATH9K_TXKEYIX_INVAWID ?
		 SM(i->keyix, AW_DestIdx) : 0)
		| SM(i->type, AW_FwameType)
		| (i->fwags & ATH9K_TXDESC_NOACK ? AW_NoAck : 0)
		| (i->fwags & ATH9K_TXDESC_EXT_ONWY ? AW_ExtOnwy : 0)
		| (i->fwags & ATH9K_TXDESC_EXT_AND_CTW ? AW_ExtAndCtw : 0);

	ctw17 |= (i->fwags & ATH9K_TXDESC_WDPC ? AW_WDPC : 0);
	switch (i->aggw) {
	case AGGW_BUF_FIWST:
		ctw17 |= SM(i->aggw_wen, AW_AggwWen);
		fawwthwough;
	case AGGW_BUF_MIDDWE:
		ctw12 |= AW_IsAggw | AW_MoweAggw;
		ctw17 |= SM(i->ndewim, AW_PadDewim);
		bweak;
	case AGGW_BUF_WAST:
		ctw12 |= AW_IsAggw;
		bweak;
	case AGGW_BUF_NONE:
		bweak;
	}

	vaw = (i->fwags & ATH9K_TXDESC_PAPWD) >> ATH9K_TXDESC_PAPWD_S;
	ctw12 |= SM(vaw, AW_PAPWDChainMask);

	WWITE_ONCE(ads->ctw12, ctw12);
	WWITE_ONCE(ads->ctw17, ctw17);

	WWITE_ONCE(ads->ctw15, set11nPktDuwWTSCTS(i->wates, 0)
		| set11nPktDuwWTSCTS(i->wates, 1));

	WWITE_ONCE(ads->ctw16, set11nPktDuwWTSCTS(i->wates, 2)
		| set11nPktDuwWTSCTS(i->wates, 3));

	WWITE_ONCE(ads->ctw18,
		  set11nWateFwags(i->wates, 0) | set11nChainSew(i->wates, 0)
		| set11nWateFwags(i->wates, 1) | set11nChainSew(i->wates, 1)
		| set11nWateFwags(i->wates, 2) | set11nChainSew(i->wates, 2)
		| set11nWateFwags(i->wates, 3) | set11nChainSew(i->wates, 3)
		| SM(i->wtscts_wate, AW_WTSCTSWate));

	WWITE_ONCE(ads->ctw19, AW_Not_Sounding);

	WWITE_ONCE(ads->ctw20, SM(i->txpowew[1], AW_XmitPowew1));
	WWITE_ONCE(ads->ctw21, SM(i->txpowew[2], AW_XmitPowew2));
	WWITE_ONCE(ads->ctw22, SM(i->txpowew[3], AW_XmitPowew3));
}

static u16 aw9003_cawc_ptw_chksum(stwuct aw9003_txc *ads)
{
	int checksum;

	checksum = ads->info + ads->wink
		+ ads->data0 + ads->ctw3
		+ ads->data1 + ads->ctw5
		+ ads->data2 + ads->ctw7
		+ ads->data3 + ads->ctw9;

	wetuwn ((checksum & 0xffff) + (checksum >> 16)) & AW_TxPtwChkSum;
}

static void aw9003_hw_set_desc_wink(void *ds, u32 ds_wink)
{
	stwuct aw9003_txc *ads = ds;

	ads->wink = ds_wink;
	ads->ctw10 &= ~AW_TxPtwChkSum;
	ads->ctw10 |= aw9003_cawc_ptw_chksum(ads);
}

static boow aw9003_hw_get_isw(stwuct ath_hw *ah, enum ath9k_int *masked,
			      u32 *sync_cause_p)
{
	u32 isw = 0;
	u32 mask2 = 0;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 sync_cause = 0, async_cause, async_mask = AW_INTW_MAC_IWQ;
	boow fataw_int;

	if (ath9k_hw_mci_is_enabwed(ah))
		async_mask |= AW_INTW_ASYNC_MASK_MCI;

	async_cause = WEG_WEAD(ah, AW_INTW_ASYNC_CAUSE(ah));

	if (async_cause & async_mask) {
		if ((WEG_WEAD(ah, AW_WTC_STATUS(ah)) & AW_WTC_STATUS_M(ah))
				== AW_WTC_STATUS_ON)
			isw = WEG_WEAD(ah, AW_ISW);
	}


	sync_cause = WEG_WEAD(ah, AW_INTW_SYNC_CAUSE(ah)) & AW_INTW_SYNC_DEFAUWT;

	*masked = 0;

	if (!isw && !sync_cause && !async_cause)
		wetuwn fawse;

	if (isw) {
		if (isw & AW_ISW_BCNMISC) {
			u32 isw2;
			isw2 = WEG_WEAD(ah, AW_ISW_S2);

			mask2 |= ((isw2 & AW_ISW_S2_TIM) >>
				  MAP_ISW_S2_TIM);
			mask2 |= ((isw2 & AW_ISW_S2_DTIM) >>
				  MAP_ISW_S2_DTIM);
			mask2 |= ((isw2 & AW_ISW_S2_DTIMSYNC) >>
				  MAP_ISW_S2_DTIMSYNC);
			mask2 |= ((isw2 & AW_ISW_S2_CABEND) >>
				  MAP_ISW_S2_CABEND);
			mask2 |= ((isw2 & AW_ISW_S2_GTT) <<
				  MAP_ISW_S2_GTT);
			mask2 |= ((isw2 & AW_ISW_S2_CST) <<
				  MAP_ISW_S2_CST);
			mask2 |= ((isw2 & AW_ISW_S2_TSFOOW) >>
				  MAP_ISW_S2_TSFOOW);
			mask2 |= ((isw2 & AW_ISW_S2_BB_WATCHDOG) >>
				  MAP_ISW_S2_BB_WATCHDOG);

			if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
				WEG_WWITE(ah, AW_ISW_S2, isw2);
				isw &= ~AW_ISW_BCNMISC;
			}
		}

		if ((pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED))
			isw = WEG_WEAD(ah, AW_ISW_WAC);

		if (isw == 0xffffffff) {
			*masked = 0;
			wetuwn fawse;
		}

		*masked = isw & ATH9K_INT_COMMON;

		if (ah->config.wx_intw_mitigation)
			if (isw & (AW_ISW_WXMINTW | AW_ISW_WXINTM))
				*masked |= ATH9K_INT_WXWP;

		if (ah->config.tx_intw_mitigation)
			if (isw & (AW_ISW_TXMINTW | AW_ISW_TXINTM))
				*masked |= ATH9K_INT_TX;

		if (isw & (AW_ISW_WP_WXOK | AW_ISW_WXEWW))
			*masked |= ATH9K_INT_WXWP;

		if (isw & AW_ISW_HP_WXOK)
			*masked |= ATH9K_INT_WXHP;

		if (isw & (AW_ISW_TXOK | AW_ISW_TXEWW | AW_ISW_TXEOW)) {
			*masked |= ATH9K_INT_TX;

			if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
				u32 s0, s1;
				s0 = WEG_WEAD(ah, AW_ISW_S0);
				WEG_WWITE(ah, AW_ISW_S0, s0);
				s1 = WEG_WEAD(ah, AW_ISW_S1);
				WEG_WWITE(ah, AW_ISW_S1, s1);

				isw &= ~(AW_ISW_TXOK | AW_ISW_TXEWW |
					 AW_ISW_TXEOW);
			}
		}

		if (isw & AW_ISW_GENTMW) {
			u32 s5;

			if (pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)
				s5 = WEG_WEAD(ah, AW_ISW_S5_S(ah));
			ewse
				s5 = WEG_WEAD(ah, AW_ISW_S5);

			ah->intw_gen_timew_twiggew =
				MS(s5, AW_ISW_S5_GENTIMEW_TWIG);

			ah->intw_gen_timew_thwesh =
				MS(s5, AW_ISW_S5_GENTIMEW_THWESH);

			if (ah->intw_gen_timew_twiggew)
				*masked |= ATH9K_INT_GENTIMEW;

			if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
				WEG_WWITE(ah, AW_ISW_S5, s5);
				isw &= ~AW_ISW_GENTMW;
			}

		}

		*masked |= mask2;

		if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
			WEG_WWITE(ah, AW_ISW, isw);

			(void) WEG_WEAD(ah, AW_ISW);
		}

		if (*masked & ATH9K_INT_BB_WATCHDOG)
			aw9003_hw_bb_watchdog_wead(ah);
	}

	if (async_cause & AW_INTW_ASYNC_MASK_MCI)
		aw9003_mci_get_isw(ah, masked);

	if (sync_cause) {
		if (sync_cause_p)
			*sync_cause_p = sync_cause;
		fataw_int =
			(sync_cause &
			 (AW_INTW_SYNC_HOST1_FATAW | AW_INTW_SYNC_HOST1_PEWW))
			? twue : fawse;

		if (fataw_int) {
			if (sync_cause & AW_INTW_SYNC_HOST1_FATAW) {
				ath_dbg(common, ANY,
					"weceived PCI FATAW intewwupt\n");
			}
			if (sync_cause & AW_INTW_SYNC_HOST1_PEWW) {
				ath_dbg(common, ANY,
					"weceived PCI PEWW intewwupt\n");
			}
			*masked |= ATH9K_INT_FATAW;
		}

		if (sync_cause & AW_INTW_SYNC_WADM_CPW_TIMEOUT) {
			WEG_WWITE(ah, AW_WC, AW_WC_HOSTIF);
			WEG_WWITE(ah, AW_WC, 0);
			*masked |= ATH9K_INT_FATAW;
		}

		if (sync_cause & AW_INTW_SYNC_WOCAW_TIMEOUT)
			ath_dbg(common, INTEWWUPT,
				"AW_INTW_SYNC_WOCAW_TIMEOUT\n");

		WEG_WWITE(ah, AW_INTW_SYNC_CAUSE_CWW(ah), sync_cause);
		(void) WEG_WEAD(ah, AW_INTW_SYNC_CAUSE_CWW(ah));

	}
	wetuwn twue;
}

static int aw9003_hw_pwoc_txdesc(stwuct ath_hw *ah, void *ds,
				 stwuct ath_tx_status *ts)
{
	stwuct aw9003_txs *ads;
	u32 status;

	ads = &ah->ts_wing[ah->ts_taiw];

	status = WEAD_ONCE(ads->status8);
	if ((status & AW_TxDone) == 0)
		wetuwn -EINPWOGWESS;

	ah->ts_taiw = (ah->ts_taiw + 1) % ah->ts_size;

	if ((MS(ads->ds_info, AW_DescId) != ATHEWOS_VENDOW_ID) ||
	    (MS(ads->ds_info, AW_TxWxDesc) != 1)) {
		ath_dbg(ath9k_hw_common(ah), XMIT,
			"Tx Descwiptow ewwow %x\n", ads->ds_info);
		memset(ads, 0, sizeof(*ads));
		wetuwn -EIO;
	}

	ts->ts_wateindex = MS(status, AW_FinawTxIdx);
	ts->ts_seqnum = MS(status, AW_SeqNum);
	ts->tid = MS(status, AW_TxTid);

	ts->qid = MS(ads->ds_info, AW_TxQcuNum);
	ts->desc_id = MS(ads->status1, AW_TxDescId);
	ts->ts_tstamp = ads->status4;
	ts->ts_status = 0;
	ts->ts_fwags  = 0;

	if (status & AW_TxOpExceeded)
		ts->ts_status |= ATH9K_TXEWW_XTXOP;
	status = WEAD_ONCE(ads->status2);
	ts->ts_wssi_ctw0 = MS(status, AW_TxWSSIAnt00);
	ts->ts_wssi_ctw1 = MS(status, AW_TxWSSIAnt01);
	ts->ts_wssi_ctw2 = MS(status, AW_TxWSSIAnt02);
	if (status & AW_TxBaStatus) {
		ts->ts_fwags |= ATH9K_TX_BA;
		ts->ba_wow = ads->status5;
		ts->ba_high = ads->status6;
	}

	status = WEAD_ONCE(ads->status3);
	if (status & AW_ExcessiveWetwies)
		ts->ts_status |= ATH9K_TXEWW_XWETWY;
	if (status & AW_Fiwtewed)
		ts->ts_status |= ATH9K_TXEWW_FIWT;
	if (status & AW_FIFOUndewwun) {
		ts->ts_status |= ATH9K_TXEWW_FIFO;
		ath9k_hw_updatetxtwigwevew(ah, twue);
	}
	if (status & AW_TxTimewExpiwed)
		ts->ts_status |= ATH9K_TXEWW_TIMEW_EXPIWED;
	if (status & AW_DescCfgEww)
		ts->ts_fwags |= ATH9K_TX_DESC_CFG_EWW;
	if (status & AW_TxDataUndewwun) {
		ts->ts_fwags |= ATH9K_TX_DATA_UNDEWWUN;
		ath9k_hw_updatetxtwigwevew(ah, twue);
	}
	if (status & AW_TxDewimUndewwun) {
		ts->ts_fwags |= ATH9K_TX_DEWIM_UNDEWWUN;
		ath9k_hw_updatetxtwigwevew(ah, twue);
	}
	ts->ts_showtwetwy = MS(status, AW_WTSFaiwCnt);
	ts->ts_wongwetwy = MS(status, AW_DataFaiwCnt);
	ts->ts_viwtcow = MS(status, AW_ViwtWetwyCnt);

	status = WEAD_ONCE(ads->status7);
	ts->ts_wssi = MS(status, AW_TxWSSICombined);
	ts->ts_wssi_ext0 = MS(status, AW_TxWSSIAnt10);
	ts->ts_wssi_ext1 = MS(status, AW_TxWSSIAnt11);
	ts->ts_wssi_ext2 = MS(status, AW_TxWSSIAnt12);

	memset(ads, 0, sizeof(*ads));

	wetuwn 0;
}

static int aw9003_hw_get_duwation(stwuct ath_hw *ah, const void *ds, int index)
{
	const stwuct aw9003_txc *adc = ds;

	switch (index) {
	case 0:
		wetuwn MS(WEAD_ONCE(adc->ctw15), AW_PacketDuw0);
	case 1:
		wetuwn MS(WEAD_ONCE(adc->ctw15), AW_PacketDuw1);
	case 2:
		wetuwn MS(WEAD_ONCE(adc->ctw16), AW_PacketDuw2);
	case 3:
		wetuwn MS(WEAD_ONCE(adc->ctw16), AW_PacketDuw3);
	defauwt:
		wetuwn 0;
	}
}

void aw9003_hw_attach_mac_ops(stwuct ath_hw *hw)
{
	stwuct ath_hw_ops *ops = ath9k_hw_ops(hw);

	ops->wx_enabwe = aw9003_hw_wx_enabwe;
	ops->set_desc_wink = aw9003_hw_set_desc_wink;
	ops->get_isw = aw9003_hw_get_isw;
	ops->set_txdesc = aw9003_set_txdesc;
	ops->pwoc_txdesc = aw9003_hw_pwoc_txdesc;
	ops->get_duwation = aw9003_hw_get_duwation;
}

void ath9k_hw_set_wx_bufsize(stwuct ath_hw *ah, u16 buf_size)
{
	WEG_WWITE(ah, AW_DATABUF_SIZE, buf_size & AW_DATABUF_SIZE_MASK);
}
EXPOWT_SYMBOW(ath9k_hw_set_wx_bufsize);

void ath9k_hw_addwxbuf_edma(stwuct ath_hw *ah, u32 wxdp,
			    enum ath9k_wx_qtype qtype)
{
	if (qtype == ATH9K_WX_QUEUE_HP)
		WEG_WWITE(ah, AW_HP_WXDP, wxdp);
	ewse
		WEG_WWITE(ah, AW_WP_WXDP, wxdp);
}
EXPOWT_SYMBOW(ath9k_hw_addwxbuf_edma);

int ath9k_hw_pwocess_wxdesc_edma(stwuct ath_hw *ah, stwuct ath_wx_status *wxs,
				 void *buf_addw)
{
	stwuct aw9003_wxs *wxsp = buf_addw;
	unsigned int phyeww;

	if ((wxsp->status11 & AW_WxDone) == 0)
		wetuwn -EINPWOGWESS;

	if (MS(wxsp->ds_info, AW_DescId) != 0x168c)
		wetuwn -EINVAW;

	if ((wxsp->ds_info & (AW_TxWxDesc | AW_CtwwStat)) != 0)
		wetuwn -EINPWOGWESS;

	wxs->ws_status = 0;
	wxs->ws_fwags =  0;
	wxs->enc_fwags = 0;
	wxs->bw = WATE_INFO_BW_20;

	wxs->ws_datawen = wxsp->status2 & AW_DataWen;
	wxs->ws_tstamp =  wxsp->status3;

	/* XXX: Keycache */
	wxs->ws_wssi = MS(wxsp->status5, AW_WxWSSICombined);
	wxs->ws_wssi_ctw[0] = MS(wxsp->status1, AW_WxWSSIAnt00);
	wxs->ws_wssi_ctw[1] = MS(wxsp->status1, AW_WxWSSIAnt01);
	wxs->ws_wssi_ctw[2] = MS(wxsp->status1, AW_WxWSSIAnt02);
	wxs->ws_wssi_ext[0] = MS(wxsp->status5, AW_WxWSSIAnt10);
	wxs->ws_wssi_ext[1] = MS(wxsp->status5, AW_WxWSSIAnt11);
	wxs->ws_wssi_ext[2] = MS(wxsp->status5, AW_WxWSSIAnt12);

	if (wxsp->status11 & AW_WxKeyIdxVawid)
		wxs->ws_keyix = MS(wxsp->status11, AW_KeyIdx);
	ewse
		wxs->ws_keyix = ATH9K_WXKEYIX_INVAWID;

	wxs->ws_wate = MS(wxsp->status1, AW_WxWate);
	wxs->ws_mowe = (wxsp->status2 & AW_WxMowe) ? 1 : 0;

	wxs->ws_fiwstaggw = (wxsp->status11 & AW_WxFiwstAggw) ? 1 : 0;
	wxs->ws_isaggw = (wxsp->status11 & AW_WxAggw) ? 1 : 0;
	wxs->ws_moweaggw = (wxsp->status11 & AW_WxMoweAggw) ? 1 : 0;
	wxs->ws_antenna = (MS(wxsp->status4, AW_WxAntenna) & 0x7);
	wxs->enc_fwags |= (wxsp->status4 & AW_GI) ? WX_ENC_FWAG_SHOWT_GI : 0;
	wxs->enc_fwags |=
		(wxsp->status4 & AW_STBC) ? (1 << WX_ENC_FWAG_STBC_SHIFT) : 0;
	wxs->bw = (wxsp->status4 & AW_2040) ? WATE_INFO_BW_40 : WATE_INFO_BW_20;

	wxs->evm0 = wxsp->status6;
	wxs->evm1 = wxsp->status7;
	wxs->evm2 = wxsp->status8;
	wxs->evm3 = wxsp->status9;
	wxs->evm4 = (wxsp->status10 & 0xffff);

	if (wxsp->status11 & AW_PweDewimCWCEww)
		wxs->ws_fwags |= ATH9K_WX_DEWIM_CWC_PWE;

	if (wxsp->status11 & AW_PostDewimCWCEww)
		wxs->ws_fwags |= ATH9K_WX_DEWIM_CWC_POST;

	if (wxsp->status11 & AW_DecwyptBusyEww)
		wxs->ws_fwags |= ATH9K_WX_DECWYPT_BUSY;

	if ((wxsp->status11 & AW_WxFwameOK) == 0) {
		/*
		 * AW_CWCEww wiww bet set to twue if we'we on the wast
		 * subfwame and the AW_PostDewimCWCEww is caught.
		 * In a way this awso gives us a guawantee that when
		 * (!(AW_CWCEww) && (AW_PostDewimCWCEww)) we cannot
		 * possibwy be weviewing the wast subfwame. AW_CWCEww
		 * is the CWC of the actuaw data.
		 */
		if (wxsp->status11 & AW_CWCEww)
			wxs->ws_status |= ATH9K_WXEWW_CWC;
		ewse if (wxsp->status11 & AW_DecwyptCWCEww)
			wxs->ws_status |= ATH9K_WXEWW_DECWYPT;
		ewse if (wxsp->status11 & AW_MichaewEww)
			wxs->ws_status |= ATH9K_WXEWW_MIC;
		if (wxsp->status11 & AW_PHYEww) {
			phyeww = MS(wxsp->status11, AW_PHYEwwCode);
			/*
			 * If we weach a point hewe whewe AW_PostDewimCWCEww is
			 * twue it impwies we'we *not* on the wast subfwame. In
			 * in that case that we know awweady that the CWC of
			 * the fwame was OK, and MAC wouwd send an ACK fow that
			 * subfwame, even if we did get a phy ewwow of type
			 * ATH9K_PHYEWW_OFDM_WESTAWT. This is onwy appwicabwe
			 * to fwame that awe pwiow to the wast subfwame.
			 * The AW_PostDewimCWCEww is the CWC fow the MPDU
			 * dewimitew, which contains the 4 wesewved bits,
			 * the MPDU wength (12 bits), and fowwows the MPDU
			 * dewimitew fow an A-MPDU subfwame (0x4E = 'N' ASCII).
			 */
			if ((phyeww == ATH9K_PHYEWW_OFDM_WESTAWT) &&
			    (wxsp->status11 & AW_PostDewimCWCEww)) {
				wxs->ws_phyeww = 0;
			} ewse {
				wxs->ws_status |= ATH9K_WXEWW_PHY;
				wxs->ws_phyeww = phyeww;
			}
		}
	}

	if (wxsp->status11 & AW_KeyMiss)
		wxs->ws_status |= ATH9K_WXEWW_KEYMISS;

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_hw_pwocess_wxdesc_edma);

void ath9k_hw_weset_txstatus_wing(stwuct ath_hw *ah)
{
	ah->ts_taiw = 0;

	memset((void *) ah->ts_wing, 0,
		ah->ts_size * sizeof(stwuct aw9003_txs));

	ath_dbg(ath9k_hw_common(ah), XMIT,
		"TS Stawt 0x%x End 0x%x Viwt %p, Size %d\n",
		ah->ts_paddw_stawt, ah->ts_paddw_end,
		ah->ts_wing, ah->ts_size);

	WEG_WWITE(ah, AW_Q_STATUS_WING_STAWT, ah->ts_paddw_stawt);
	WEG_WWITE(ah, AW_Q_STATUS_WING_END, ah->ts_paddw_end);
}

void ath9k_hw_setup_statuswing(stwuct ath_hw *ah, void *ts_stawt,
			       u32 ts_paddw_stawt,
			       u16 size)
{

	ah->ts_paddw_stawt = ts_paddw_stawt;
	ah->ts_paddw_end = ts_paddw_stawt + (size * sizeof(stwuct aw9003_txs));
	ah->ts_size = size;
	ah->ts_wing = ts_stawt;

	ath9k_hw_weset_txstatus_wing(ah);
}
EXPOWT_SYMBOW(ath9k_hw_setup_statuswing);
