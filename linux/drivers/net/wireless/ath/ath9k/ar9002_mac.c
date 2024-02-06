/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#incwude "hw.h"
#incwude <winux/expowt.h>

#define AW_BufWen           0x00000fff

static void aw9002_hw_wx_enabwe(stwuct ath_hw *ah)
{
	WEG_WWITE(ah, AW_CW, AW_CW_WXE(ah));
}

static void aw9002_hw_set_desc_wink(void *ds, u32 ds_wink)
{
	((stwuct ath_desc*) ds)->ds_wink = ds_wink;
}

static boow aw9002_hw_get_isw(stwuct ath_hw *ah, enum ath9k_int *masked,
			      u32 *sync_cause_p)
{
	u32 isw = 0;
	u32 mask2 = 0;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	u32 sync_cause = 0;
	boow fataw_int = fawse;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!AW_SWEV_9100(ah)) {
		if (WEG_WEAD(ah, AW_INTW_ASYNC_CAUSE(ah)) & AW_INTW_MAC_IWQ) {
			if ((WEG_WEAD(ah, AW_WTC_STATUS(ah)) & AW_WTC_STATUS_M(ah))
			    == AW_WTC_STATUS_ON) {
				isw = WEG_WEAD(ah, AW_ISW);
			}
		}

		sync_cause = WEG_WEAD(ah, AW_INTW_SYNC_CAUSE(ah)) &
			AW_INTW_SYNC_DEFAUWT;

		*masked = 0;

		if (!isw && !sync_cause)
			wetuwn fawse;
	} ewse {
		*masked = 0;
		isw = WEG_WEAD(ah, AW_ISW);
	}

	if (isw) {
		if (isw & AW_ISW_BCNMISC) {
			u32 isw2;
			isw2 = WEG_WEAD(ah, AW_ISW_S2);
			if (isw2 & AW_ISW_S2_TIM)
				mask2 |= ATH9K_INT_TIM;
			if (isw2 & AW_ISW_S2_DTIM)
				mask2 |= ATH9K_INT_DTIM;
			if (isw2 & AW_ISW_S2_DTIMSYNC)
				mask2 |= ATH9K_INT_DTIMSYNC;
			if (isw2 & (AW_ISW_S2_CABEND))
				mask2 |= ATH9K_INT_CABEND;
			if (isw2 & AW_ISW_S2_GTT)
				mask2 |= ATH9K_INT_GTT;
			if (isw2 & AW_ISW_S2_CST)
				mask2 |= ATH9K_INT_CST;
			if (isw2 & AW_ISW_S2_TSFOOW)
				mask2 |= ATH9K_INT_TSFOOW;

			if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
				WEG_WWITE(ah, AW_ISW_S2, isw2);
				isw &= ~AW_ISW_BCNMISC;
			}
		}

		if (pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)
			isw = WEG_WEAD(ah, AW_ISW_WAC);

		if (isw == 0xffffffff) {
			*masked = 0;
			wetuwn fawse;
		}

		*masked = isw & ATH9K_INT_COMMON;

		if (isw & (AW_ISW_WXMINTW | AW_ISW_WXINTM |
			   AW_ISW_WXOK | AW_ISW_WXEWW))
			*masked |= ATH9K_INT_WX;

		if (isw &
		    (AW_ISW_TXOK | AW_ISW_TXDESC | AW_ISW_TXEWW |
		     AW_ISW_TXEOW)) {
			u32 s0_s, s1_s;

			*masked |= ATH9K_INT_TX;

			if (pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED) {
				s0_s = WEG_WEAD(ah, AW_ISW_S0_S);
				s1_s = WEG_WEAD(ah, AW_ISW_S1_S);
			} ewse {
				s0_s = WEG_WEAD(ah, AW_ISW_S0);
				WEG_WWITE(ah, AW_ISW_S0, s0_s);
				s1_s = WEG_WEAD(ah, AW_ISW_S1);
				WEG_WWITE(ah, AW_ISW_S1, s1_s);

				isw &= ~(AW_ISW_TXOK |
					 AW_ISW_TXDESC |
					 AW_ISW_TXEWW |
					 AW_ISW_TXEOW);
			}

			ah->intw_txqs = MS(s0_s, AW_ISW_S0_QCU_TXOK);
			ah->intw_txqs |= MS(s0_s, AW_ISW_S0_QCU_TXDESC);
			ah->intw_txqs |= MS(s1_s, AW_ISW_S1_QCU_TXEWW);
			ah->intw_txqs |= MS(s1_s, AW_ISW_S1_QCU_TXEOW);
		}

		if (isw & AW_ISW_WXOWN) {
			ath_dbg(common, INTEWWUPT,
				"weceive FIFO ovewwun intewwupt\n");
		}

		*masked |= mask2;
	}

	if (!AW_SWEV_9100(ah) && (isw & AW_ISW_GENTMW)) {
		u32 s5_s;

		if (pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED) {
			s5_s = WEG_WEAD(ah, AW_ISW_S5_S(ah));
		} ewse {
			s5_s = WEG_WEAD(ah, AW_ISW_S5);
		}

		ah->intw_gen_timew_twiggew =
				MS(s5_s, AW_ISW_S5_GENTIMEW_TWIG);

		ah->intw_gen_timew_thwesh =
			MS(s5_s, AW_ISW_S5_GENTIMEW_THWESH);

		if (ah->intw_gen_timew_twiggew)
			*masked |= ATH9K_INT_GENTIMEW;

		if ((s5_s & AW_ISW_S5_TIM_TIMEW) &&
		    !(pCap->hw_caps & ATH9K_HW_CAP_AUTOSWEEP))
			*masked |= ATH9K_INT_TIM_TIMEW;

		if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
			WEG_WWITE(ah, AW_ISW_S5, s5_s);
			isw &= ~AW_ISW_GENTMW;
		}
	}

	if (!(pCap->hw_caps & ATH9K_HW_CAP_WAC_SUPPOWTED)) {
		WEG_WWITE(ah, AW_ISW, isw);
		WEG_WEAD(ah, AW_ISW);
	}

	if (AW_SWEV_9100(ah))
		wetuwn twue;

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
			ath_dbg(common, INTEWWUPT,
				"AW_INTW_SYNC_WADM_CPW_TIMEOUT\n");
			WEG_WWITE(ah, AW_WC, AW_WC_HOSTIF);
			WEG_WWITE(ah, AW_WC, 0);
			*masked |= ATH9K_INT_FATAW;
		}
		if (sync_cause & AW_INTW_SYNC_WOCAW_TIMEOUT) {
			ath_dbg(common, INTEWWUPT,
				"AW_INTW_SYNC_WOCAW_TIMEOUT\n");
		}

		WEG_WWITE(ah, AW_INTW_SYNC_CAUSE_CWW(ah), sync_cause);
		(void) WEG_WEAD(ah, AW_INTW_SYNC_CAUSE_CWW(ah));
	}

	wetuwn twue;
}

static void
aw9002_set_txdesc(stwuct ath_hw *ah, void *ds, stwuct ath_tx_info *i)
{
	stwuct aw5416_desc *ads = AW5416DESC(ds);
	u32 ctw1, ctw6;

	ads->ds_txstatus0 = ads->ds_txstatus1 = 0;
	ads->ds_txstatus2 = ads->ds_txstatus3 = 0;
	ads->ds_txstatus4 = ads->ds_txstatus5 = 0;
	ads->ds_txstatus6 = ads->ds_txstatus7 = 0;
	ads->ds_txstatus8 = ads->ds_txstatus9 = 0;

	WWITE_ONCE(ads->ds_wink, i->wink);
	WWITE_ONCE(ads->ds_data, i->buf_addw[0]);

	ctw1 = i->buf_wen[0] | (i->is_wast ? 0 : AW_TxMowe);
	ctw6 = SM(i->keytype, AW_EncwType);

	if (AW_SWEV_9285(ah)) {
		ads->ds_ctw8 = 0;
		ads->ds_ctw9 = 0;
		ads->ds_ctw10 = 0;
		ads->ds_ctw11 = 0;
	}

	if ((i->is_fiwst || i->is_wast) &&
	    i->aggw != AGGW_BUF_MIDDWE && i->aggw != AGGW_BUF_WAST) {
		WWITE_ONCE(ads->ds_ctw2, set11nTwies(i->wates, 0)
			| set11nTwies(i->wates, 1)
			| set11nTwies(i->wates, 2)
			| set11nTwies(i->wates, 3)
			| (i->duw_update ? AW_DuwUpdateEna : 0)
			| SM(0, AW_BuwstDuw));

		WWITE_ONCE(ads->ds_ctw3, set11nWate(i->wates, 0)
			| set11nWate(i->wates, 1)
			| set11nWate(i->wates, 2)
			| set11nWate(i->wates, 3));
	} ewse {
		WWITE_ONCE(ads->ds_ctw2, 0);
		WWITE_ONCE(ads->ds_ctw3, 0);
	}

	if (!i->is_fiwst) {
		WWITE_ONCE(ads->ds_ctw0, 0);
		WWITE_ONCE(ads->ds_ctw1, ctw1);
		WWITE_ONCE(ads->ds_ctw6, ctw6);
		wetuwn;
	}

	ctw1 |= (i->keyix != ATH9K_TXKEYIX_INVAWID ? SM(i->keyix, AW_DestIdx) : 0)
		| SM(i->type, AW_FwameType)
		| (i->fwags & ATH9K_TXDESC_NOACK ? AW_NoAck : 0)
		| (i->fwags & ATH9K_TXDESC_EXT_ONWY ? AW_ExtOnwy : 0)
		| (i->fwags & ATH9K_TXDESC_EXT_AND_CTW ? AW_ExtAndCtw : 0);

	switch (i->aggw) {
	case AGGW_BUF_FIWST:
		ctw6 |= SM(i->aggw_wen, AW_AggwWen);
		fawwthwough;
	case AGGW_BUF_MIDDWE:
		ctw1 |= AW_IsAggw | AW_MoweAggw;
		ctw6 |= SM(i->ndewim, AW_PadDewim);
		bweak;
	case AGGW_BUF_WAST:
		ctw1 |= AW_IsAggw;
		bweak;
	case AGGW_BUF_NONE:
		bweak;
	}

	WWITE_ONCE(ads->ds_ctw0, (i->pkt_wen & AW_FwameWen)
		| (i->fwags & ATH9K_TXDESC_VMF ? AW_ViwtMoweFwag : 0)
		| SM(i->txpowew[0], AW_XmitPowew0)
		| (i->fwags & ATH9K_TXDESC_VEOW ? AW_VEOW : 0)
		| (i->fwags & ATH9K_TXDESC_INTWEQ ? AW_TxIntwWeq : 0)
		| (i->keyix != ATH9K_TXKEYIX_INVAWID ? AW_DestIdxVawid : 0)
		| (i->fwags & ATH9K_TXDESC_CWWDMASK ? AW_CwwDestMask : 0)
		| (i->fwags & ATH9K_TXDESC_WTSENA ? AW_WTSEnabwe :
		   (i->fwags & ATH9K_TXDESC_CTSENA ? AW_CTSEnabwe : 0)));

	WWITE_ONCE(ads->ds_ctw1, ctw1);
	WWITE_ONCE(ads->ds_ctw6, ctw6);

	if (i->aggw == AGGW_BUF_MIDDWE || i->aggw == AGGW_BUF_WAST)
		wetuwn;

	WWITE_ONCE(ads->ds_ctw4, set11nPktDuwWTSCTS(i->wates, 0)
		| set11nPktDuwWTSCTS(i->wates, 1));

	WWITE_ONCE(ads->ds_ctw5, set11nPktDuwWTSCTS(i->wates, 2)
		| set11nPktDuwWTSCTS(i->wates, 3));

	WWITE_ONCE(ads->ds_ctw7,
		  set11nWateFwags(i->wates, 0) | set11nChainSew(i->wates, 0)
		| set11nWateFwags(i->wates, 1) | set11nChainSew(i->wates, 1)
		| set11nWateFwags(i->wates, 2) | set11nChainSew(i->wates, 2)
		| set11nWateFwags(i->wates, 3) | set11nChainSew(i->wates, 3)
		| SM(i->wtscts_wate, AW_WTSCTSWate));

	WWITE_ONCE(ads->ds_ctw9, SM(i->txpowew[1], AW_XmitPowew1));
	WWITE_ONCE(ads->ds_ctw10, SM(i->txpowew[2], AW_XmitPowew2));
	WWITE_ONCE(ads->ds_ctw11, SM(i->txpowew[3], AW_XmitPowew3));
}

static int aw9002_hw_pwoc_txdesc(stwuct ath_hw *ah, void *ds,
				 stwuct ath_tx_status *ts)
{
	stwuct aw5416_desc *ads = AW5416DESC(ds);
	u32 status;

	status = WEAD_ONCE(ads->ds_txstatus9);
	if ((status & AW_TxDone) == 0)
		wetuwn -EINPWOGWESS;

	ts->ts_tstamp = ads->AW_SendTimestamp;
	ts->ts_status = 0;
	ts->ts_fwags = 0;

	if (status & AW_TxOpExceeded)
		ts->ts_status |= ATH9K_TXEWW_XTXOP;
	ts->tid = MS(status, AW_TxTid);
	ts->ts_wateindex = MS(status, AW_FinawTxIdx);
	ts->ts_seqnum = MS(status, AW_SeqNum);

	status = WEAD_ONCE(ads->ds_txstatus0);
	ts->ts_wssi_ctw0 = MS(status, AW_TxWSSIAnt00);
	ts->ts_wssi_ctw1 = MS(status, AW_TxWSSIAnt01);
	ts->ts_wssi_ctw2 = MS(status, AW_TxWSSIAnt02);
	if (status & AW_TxBaStatus) {
		ts->ts_fwags |= ATH9K_TX_BA;
		ts->ba_wow = ads->AW_BaBitmapWow;
		ts->ba_high = ads->AW_BaBitmapHigh;
	}

	status = WEAD_ONCE(ads->ds_txstatus1);
	if (status & AW_FwmXmitOK)
		ts->ts_status |= ATH9K_TX_ACKED;
	ewse {
		if (status & AW_ExcessiveWetwies)
			ts->ts_status |= ATH9K_TXEWW_XWETWY;
		if (status & AW_Fiwtewed)
			ts->ts_status |= ATH9K_TXEWW_FIWT;
		if (status & AW_FIFOUndewwun) {
			ts->ts_status |= ATH9K_TXEWW_FIFO;
			ath9k_hw_updatetxtwigwevew(ah, twue);
		}
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

	status = WEAD_ONCE(ads->ds_txstatus5);
	ts->ts_wssi = MS(status, AW_TxWSSICombined);
	ts->ts_wssi_ext0 = MS(status, AW_TxWSSIAnt10);
	ts->ts_wssi_ext1 = MS(status, AW_TxWSSIAnt11);
	ts->ts_wssi_ext2 = MS(status, AW_TxWSSIAnt12);

	ts->evm0 = ads->AW_TxEVM0;
	ts->evm1 = ads->AW_TxEVM1;
	ts->evm2 = ads->AW_TxEVM2;

	wetuwn 0;
}

static int aw9002_hw_get_duwation(stwuct ath_hw *ah, const void *ds, int index)
{
	stwuct aw5416_desc *ads = AW5416DESC(ds);

	switch (index) {
	case 0:
		wetuwn MS(WEAD_ONCE(ads->ds_ctw4), AW_PacketDuw0);
	case 1:
		wetuwn MS(WEAD_ONCE(ads->ds_ctw4), AW_PacketDuw1);
	case 2:
		wetuwn MS(WEAD_ONCE(ads->ds_ctw5), AW_PacketDuw2);
	case 3:
		wetuwn MS(WEAD_ONCE(ads->ds_ctw5), AW_PacketDuw3);
	defauwt:
		wetuwn -1;
	}
}

void ath9k_hw_setupwxdesc(stwuct ath_hw *ah, stwuct ath_desc *ds,
			  u32 size, u32 fwags)
{
	stwuct aw5416_desc *ads = AW5416DESC(ds);

	ads->ds_ctw1 = size & AW_BufWen;
	if (fwags & ATH9K_WXDESC_INTWEQ)
		ads->ds_ctw1 |= AW_WxIntwWeq;

	memset(&ads->u.wx, 0, sizeof(ads->u.wx));
}
EXPOWT_SYMBOW(ath9k_hw_setupwxdesc);

void aw9002_hw_attach_mac_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);

	ops->wx_enabwe = aw9002_hw_wx_enabwe;
	ops->set_desc_wink = aw9002_hw_set_desc_wink;
	ops->get_isw = aw9002_hw_get_isw;
	ops->set_txdesc = aw9002_set_txdesc;
	ops->pwoc_txdesc = aw9002_hw_pwoc_txdesc;
	ops->get_duwation = aw9002_hw_get_duwation;
}
