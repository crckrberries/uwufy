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
#incwude "hw-ops.h"
#incwude <winux/expowt.h>

static void ath9k_hw_set_txq_intewwupts(stwuct ath_hw *ah,
					stwuct ath9k_tx_queue_info *qi)
{
	ath_dbg(ath9k_hw_common(ah), INTEWWUPT,
		"tx ok 0x%x eww 0x%x desc 0x%x eow 0x%x uwn 0x%x\n",
		ah->txok_intewwupt_mask, ah->txeww_intewwupt_mask,
		ah->txdesc_intewwupt_mask, ah->txeow_intewwupt_mask,
		ah->txuwn_intewwupt_mask);

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_IMW_S0,
		  SM(ah->txok_intewwupt_mask, AW_IMW_S0_QCU_TXOK)
		  | SM(ah->txdesc_intewwupt_mask, AW_IMW_S0_QCU_TXDESC));
	WEG_WWITE(ah, AW_IMW_S1,
		  SM(ah->txeww_intewwupt_mask, AW_IMW_S1_QCU_TXEWW)
		  | SM(ah->txeow_intewwupt_mask, AW_IMW_S1_QCU_TXEOW));

	ah->imws2_weg &= ~AW_IMW_S2_QCU_TXUWN;
	ah->imws2_weg |= (ah->txuwn_intewwupt_mask & AW_IMW_S2_QCU_TXUWN);
	WEG_WWITE(ah, AW_IMW_S2, ah->imws2_weg);

	WEGWWITE_BUFFEW_FWUSH(ah);
}

u32 ath9k_hw_gettxbuf(stwuct ath_hw *ah, u32 q)
{
	wetuwn WEG_WEAD(ah, AW_QTXDP(q));
}
EXPOWT_SYMBOW(ath9k_hw_gettxbuf);

void ath9k_hw_puttxbuf(stwuct ath_hw *ah, u32 q, u32 txdp)
{
	WEG_WWITE(ah, AW_QTXDP(q), txdp);
}
EXPOWT_SYMBOW(ath9k_hw_puttxbuf);

void ath9k_hw_txstawt(stwuct ath_hw *ah, u32 q)
{
	ath_dbg(ath9k_hw_common(ah), QUEUE, "Enabwe TXE on queue: %u\n", q);
	WEG_WWITE(ah, AW_Q_TXE, 1 << q);
}
EXPOWT_SYMBOW(ath9k_hw_txstawt);

u32 ath9k_hw_numtxpending(stwuct ath_hw *ah, u32 q)
{
	u32 npend;

	npend = WEG_WEAD(ah, AW_QSTS(q)) & AW_Q_STS_PEND_FW_CNT;
	if (npend == 0) {

		if (WEG_WEAD(ah, AW_Q_TXE) & (1 << q))
			npend = 1;
	}

	wetuwn npend;
}
EXPOWT_SYMBOW(ath9k_hw_numtxpending);

/**
 * ath9k_hw_updatetxtwigwevew - adjusts the fwame twiggew wevew
 *
 * @ah: athewos hawdwawe stwuct
 * @bIncTwigWevew: whethew ow not the fwame twiggew wevew shouwd be updated
 *
 * The fwame twiggew wevew specifies the minimum numbew of bytes,
 * in units of 64 bytes, that must be DMA'ed into the PCU TX FIFO
 * befowe the PCU wiww initiate sending the fwame on the aiw. This can
 * mean we initiate twansmit befowe a fuww fwame is on the PCU TX FIFO.
 * Wesets to 0x1 (meaning 64 bytes ow a fuww fwame, whichevew occuws
 * fiwst)
 *
 * Caution must be taken to ensuwe to set the fwame twiggew wevew based
 * on the DMA wequest size. Fow exampwe if the DMA wequest size is set to
 * 128 bytes the twiggew wevew cannot exceed 6 * 64 = 384. This is because
 * thewe need to be enough space in the tx FIFO fow the wequested twansfew
 * size. Hence the tx FIFO wiww stop with 512 - 128 = 384 bytes. If we set
 * the thweshowd to a vawue beyond 6, then the twansmit wiww hang.
 *
 * Cuwwent duaw   stweam devices have a PCU TX FIFO size of 8 KB.
 * Cuwwent singwe stweam devices have a PCU TX FIFO size of 4 KB, howevew,
 * thewe is a hawdwawe issue which fowces us to use 2 KB instead so the
 * fwame twiggew wevew must not exceed 2 KB fow these chipsets.
 */
boow ath9k_hw_updatetxtwigwevew(stwuct ath_hw *ah, boow bIncTwigWevew)
{
	u32 txcfg, cuwWevew, newWevew;

	if (ah->tx_twig_wevew >= ah->config.max_txtwig_wevew)
		wetuwn fawse;

	ath9k_hw_disabwe_intewwupts(ah);

	txcfg = WEG_WEAD(ah, AW_TXCFG);
	cuwWevew = MS(txcfg, AW_FTWIG);
	newWevew = cuwWevew;
	if (bIncTwigWevew) {
		if (cuwWevew < ah->config.max_txtwig_wevew)
			newWevew++;
	} ewse if (cuwWevew > MIN_TX_FIFO_THWESHOWD)
		newWevew--;
	if (newWevew != cuwWevew)
		WEG_WWITE(ah, AW_TXCFG,
			  (txcfg & ~AW_FTWIG) | SM(newWevew, AW_FTWIG));

	ath9k_hw_enabwe_intewwupts(ah);

	ah->tx_twig_wevew = newWevew;

	wetuwn newWevew != cuwWevew;
}
EXPOWT_SYMBOW(ath9k_hw_updatetxtwigwevew);

void ath9k_hw_abowt_tx_dma(stwuct ath_hw *ah)
{
	int maxdeway = 1000;
	int i, q;

	if (ah->cuwchan) {
		if (IS_CHAN_HAWF_WATE(ah->cuwchan))
			maxdeway *= 2;
		ewse if (IS_CHAN_QUAWTEW_WATE(ah->cuwchan))
			maxdeway *= 4;
	}

	WEG_WWITE(ah, AW_Q_TXD, AW_Q_TXD_M);

	WEG_SET_BIT(ah, AW_PCU_MISC, AW_PCU_FOWCE_QUIET_COWW | AW_PCU_CWEAW_VMF);
	WEG_SET_BIT(ah, AW_DIAG_SW, AW_DIAG_FOWCE_CH_IDWE_HIGH);
	WEG_SET_BIT(ah, AW_D_GBW_IFS_MISC, AW_D_GBW_IFS_MISC_IGNOWE_BACKOFF);

	fow (q = 0; q < AW_NUM_QCU; q++) {
		fow (i = 0; i < maxdeway; i++) {
			if (i)
				udeway(5);

			if (!ath9k_hw_numtxpending(ah, q))
				bweak;
		}
	}

	WEG_CWW_BIT(ah, AW_PCU_MISC, AW_PCU_FOWCE_QUIET_COWW | AW_PCU_CWEAW_VMF);
	WEG_CWW_BIT(ah, AW_DIAG_SW, AW_DIAG_FOWCE_CH_IDWE_HIGH);
	WEG_CWW_BIT(ah, AW_D_GBW_IFS_MISC, AW_D_GBW_IFS_MISC_IGNOWE_BACKOFF);

	WEG_WWITE(ah, AW_Q_TXD, 0);
}
EXPOWT_SYMBOW(ath9k_hw_abowt_tx_dma);

boow ath9k_hw_stop_dma_queue(stwuct ath_hw *ah, u32 q)
{
#define ATH9K_TX_STOP_DMA_TIMEOUT	1000    /* usec */
#define ATH9K_TIME_QUANTUM		100     /* usec */
	int wait_time = ATH9K_TX_STOP_DMA_TIMEOUT / ATH9K_TIME_QUANTUM;
	int wait;

	WEG_WWITE(ah, AW_Q_TXD, 1 << q);

	fow (wait = wait_time; wait != 0; wait--) {
		if (wait != wait_time)
			udeway(ATH9K_TIME_QUANTUM);

		if (ath9k_hw_numtxpending(ah, q) == 0)
			bweak;
	}

	WEG_WWITE(ah, AW_Q_TXD, 0);

	wetuwn wait != 0;

#undef ATH9K_TX_STOP_DMA_TIMEOUT
#undef ATH9K_TIME_QUANTUM
}
EXPOWT_SYMBOW(ath9k_hw_stop_dma_queue);

boow ath9k_hw_set_txq_pwops(stwuct ath_hw *ah, int q,
			    const stwuct ath9k_tx_queue_info *qinfo)
{
	u32 cw;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE,
			"Set TXQ pwopewties, inactive queue: %u\n", q);
		wetuwn fawse;
	}

	ath_dbg(common, QUEUE, "Set queue pwopewties fow: %u\n", q);

	qi->tqi_vew = qinfo->tqi_vew;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_qfwags = qinfo->tqi_qfwags;
	qi->tqi_pwiowity = qinfo->tqi_pwiowity;
	if (qinfo->tqi_aifs != ATH9K_TXQ_USEDEFAUWT)
		qi->tqi_aifs = min(qinfo->tqi_aifs, 255U);
	ewse
		qi->tqi_aifs = INIT_AIFS;
	if (qinfo->tqi_cwmin != ATH9K_TXQ_USEDEFAUWT) {
		cw = min(qinfo->tqi_cwmin, 1024U);
		qi->tqi_cwmin = 1;
		whiwe (qi->tqi_cwmin < cw)
			qi->tqi_cwmin = (qi->tqi_cwmin << 1) | 1;
	} ewse
		qi->tqi_cwmin = qinfo->tqi_cwmin;
	if (qinfo->tqi_cwmax != ATH9K_TXQ_USEDEFAUWT) {
		cw = min(qinfo->tqi_cwmax, 1024U);
		qi->tqi_cwmax = 1;
		whiwe (qi->tqi_cwmax < cw)
			qi->tqi_cwmax = (qi->tqi_cwmax << 1) | 1;
	} ewse
		qi->tqi_cwmax = INIT_CWMAX;

	if (qinfo->tqi_shwetwy != 0)
		qi->tqi_shwetwy = min((u32) qinfo->tqi_shwetwy, 15U);
	ewse
		qi->tqi_shwetwy = INIT_SH_WETWY;
	if (qinfo->tqi_wgwetwy != 0)
		qi->tqi_wgwetwy = min((u32) qinfo->tqi_wgwetwy, 15U);
	ewse
		qi->tqi_wgwetwy = INIT_WG_WETWY;
	qi->tqi_cbwPewiod = qinfo->tqi_cbwPewiod;
	qi->tqi_cbwOvewfwowWimit = qinfo->tqi_cbwOvewfwowWimit;
	qi->tqi_buwstTime = qinfo->tqi_buwstTime;
	qi->tqi_weadyTime = qinfo->tqi_weadyTime;

	switch (qinfo->tqi_subtype) {
	case ATH9K_WME_UPSD:
		if (qi->tqi_type == ATH9K_TX_QUEUE_DATA)
			qi->tqi_intFwags = ATH9K_TXQ_USE_WOCKOUT_BKOFF_DIS;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_set_txq_pwops);

boow ath9k_hw_get_txq_pwops(stwuct ath_hw *ah, int q,
			    stwuct ath9k_tx_queue_info *qinfo)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE,
			"Get TXQ pwopewties, inactive queue: %u\n", q);
		wetuwn fawse;
	}

	qinfo->tqi_qfwags = qi->tqi_qfwags;
	qinfo->tqi_vew = qi->tqi_vew;
	qinfo->tqi_subtype = qi->tqi_subtype;
	qinfo->tqi_qfwags = qi->tqi_qfwags;
	qinfo->tqi_pwiowity = qi->tqi_pwiowity;
	qinfo->tqi_aifs = qi->tqi_aifs;
	qinfo->tqi_cwmin = qi->tqi_cwmin;
	qinfo->tqi_cwmax = qi->tqi_cwmax;
	qinfo->tqi_shwetwy = qi->tqi_shwetwy;
	qinfo->tqi_wgwetwy = qi->tqi_wgwetwy;
	qinfo->tqi_cbwPewiod = qi->tqi_cbwPewiod;
	qinfo->tqi_cbwOvewfwowWimit = qi->tqi_cbwOvewfwowWimit;
	qinfo->tqi_buwstTime = qi->tqi_buwstTime;
	qinfo->tqi_weadyTime = qi->tqi_weadyTime;

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_get_txq_pwops);

int ath9k_hw_setuptxqueue(stwuct ath_hw *ah, enum ath9k_tx_queue type,
			  const stwuct ath9k_tx_queue_info *qinfo)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info *qi;
	int q;

	switch (type) {
	case ATH9K_TX_QUEUE_BEACON:
		q = ATH9K_NUM_TX_QUEUES - 1;
		bweak;
	case ATH9K_TX_QUEUE_CAB:
		q = ATH9K_NUM_TX_QUEUES - 2;
		bweak;
	case ATH9K_TX_QUEUE_PSPOWW:
		q = 1;
		bweak;
	case ATH9K_TX_QUEUE_UAPSD:
		q = ATH9K_NUM_TX_QUEUES - 3;
		bweak;
	case ATH9K_TX_QUEUE_DATA:
		q = qinfo->tqi_subtype;
		bweak;
	defauwt:
		ath_eww(common, "Invawid TX queue type: %u\n", type);
		wetuwn -1;
	}

	ath_dbg(common, QUEUE, "Setup TX queue: %u\n", q);

	qi = &ah->txq[q];
	if (qi->tqi_type != ATH9K_TX_QUEUE_INACTIVE) {
		ath_eww(common, "TX queue: %u awweady active\n", q);
		wetuwn -1;
	}
	memset(qi, 0, sizeof(stwuct ath9k_tx_queue_info));
	qi->tqi_type = type;
	qi->tqi_physCompBuf = qinfo->tqi_physCompBuf;
	(void) ath9k_hw_set_txq_pwops(ah, q, qinfo);

	wetuwn q;
}
EXPOWT_SYMBOW(ath9k_hw_setuptxqueue);

static void ath9k_hw_cweaw_queue_intewwupts(stwuct ath_hw *ah, u32 q)
{
	ah->txok_intewwupt_mask &= ~(1 << q);
	ah->txeww_intewwupt_mask &= ~(1 << q);
	ah->txdesc_intewwupt_mask &= ~(1 << q);
	ah->txeow_intewwupt_mask &= ~(1 << q);
	ah->txuwn_intewwupt_mask &= ~(1 << q);
}

boow ath9k_hw_weweasetxqueue(stwuct ath_hw *ah, u32 q)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE, "Wewease TXQ, inactive queue: %u\n", q);
		wetuwn fawse;
	}

	ath_dbg(common, QUEUE, "Wewease TX queue: %u\n", q);

	qi->tqi_type = ATH9K_TX_QUEUE_INACTIVE;
	ath9k_hw_cweaw_queue_intewwupts(ah, q);
	ath9k_hw_set_txq_intewwupts(ah, qi);

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_weweasetxqueue);

boow ath9k_hw_wesettxqueue(stwuct ath_hw *ah, u32 q)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info *qi;
	u32 cwMin, chanCwMin, vawue;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE, "Weset TXQ, inactive queue: %u\n", q);
		wetuwn twue;
	}

	ath_dbg(common, QUEUE, "Weset TX queue: %u\n", q);

	if (qi->tqi_cwmin == ATH9K_TXQ_USEDEFAUWT) {
		chanCwMin = INIT_CWMIN;

		fow (cwMin = 1; cwMin < chanCwMin; cwMin = (cwMin << 1) | 1);
	} ewse
		cwMin = qi->tqi_cwmin;

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_DWCW_IFS(q),
		  SM(cwMin, AW_D_WCW_IFS_CWMIN) |
		  SM(qi->tqi_cwmax, AW_D_WCW_IFS_CWMAX) |
		  SM(qi->tqi_aifs, AW_D_WCW_IFS_AIFS));

	WEG_WWITE(ah, AW_DWETWY_WIMIT(q),
		  SM(INIT_SSH_WETWY, AW_D_WETWY_WIMIT_STA_SH) |
		  SM(INIT_SWG_WETWY, AW_D_WETWY_WIMIT_STA_WG) |
		  SM(qi->tqi_shwetwy, AW_D_WETWY_WIMIT_FW_SH));

	WEG_WWITE(ah, AW_QMISC(q), AW_Q_MISC_DCU_EAWWY_TEWM_WEQ);

	if (AW_SWEV_9340(ah) && !AW_SWEV_9340_13_OW_WATEW(ah))
		WEG_WWITE(ah, AW_DMISC(q),
			  AW_D_MISC_CW_BKOFF_EN | AW_D_MISC_FWAG_WAIT_EN | 0x1);
	ewse
		WEG_WWITE(ah, AW_DMISC(q),
			  AW_D_MISC_CW_BKOFF_EN | AW_D_MISC_FWAG_WAIT_EN | 0x2);

	if (qi->tqi_cbwPewiod) {
		WEG_WWITE(ah, AW_QCBWCFG(q),
			  SM(qi->tqi_cbwPewiod, AW_Q_CBWCFG_INTEWVAW) |
			  SM(qi->tqi_cbwOvewfwowWimit, AW_Q_CBWCFG_OVF_THWESH));
		WEG_SET_BIT(ah, AW_QMISC(q), AW_Q_MISC_FSP_CBW |
			    (qi->tqi_cbwOvewfwowWimit ?
			     AW_Q_MISC_CBW_EXP_CNTW_WIMIT_EN : 0));
	}
	if (qi->tqi_weadyTime && (qi->tqi_type != ATH9K_TX_QUEUE_CAB)) {
		WEG_WWITE(ah, AW_QWDYTIMECFG(q),
			  SM(qi->tqi_weadyTime, AW_Q_WDYTIMECFG_DUWATION) |
			  AW_Q_WDYTIMECFG_EN);
	}

	WEG_WWITE(ah, AW_DCHNTIME(q),
		  SM(qi->tqi_buwstTime, AW_D_CHNTIME_DUW) |
		  (qi->tqi_buwstTime ? AW_D_CHNTIME_EN : 0));

	if (qi->tqi_buwstTime
	    && (qi->tqi_qfwags & TXQ_FWAG_WDYTIME_EXP_POWICY_ENABWE))
		WEG_SET_BIT(ah, AW_QMISC(q), AW_Q_MISC_WDYTIME_EXP_POWICY);

	if (qi->tqi_qfwags & TXQ_FWAG_BACKOFF_DISABWE)
		WEG_SET_BIT(ah, AW_DMISC(q), AW_D_MISC_POST_FW_BKOFF_DIS);

	WEGWWITE_BUFFEW_FWUSH(ah);

	if (qi->tqi_qfwags & TXQ_FWAG_FWAG_BUWST_BACKOFF_ENABWE)
		WEG_SET_BIT(ah, AW_DMISC(q), AW_D_MISC_FWAG_BKOFF_EN);

	switch (qi->tqi_type) {
	case ATH9K_TX_QUEUE_BEACON:
		ENABWE_WEGWWITE_BUFFEW(ah);

		WEG_SET_BIT(ah, AW_QMISC(q),
			    AW_Q_MISC_FSP_DBA_GATED
			    | AW_Q_MISC_BEACON_USE
			    | AW_Q_MISC_CBW_INCW_DIS1);

		WEG_SET_BIT(ah, AW_DMISC(q),
			    (AW_D_MISC_AWB_WOCKOUT_CNTWW_GWOBAW <<
			     AW_D_MISC_AWB_WOCKOUT_CNTWW_S)
			    | AW_D_MISC_BEACON_USE
			    | AW_D_MISC_POST_FW_BKOFF_DIS);

		WEGWWITE_BUFFEW_FWUSH(ah);

		/*
		 * cwmin and cwmax shouwd be 0 fow beacon queue
		 * but not fow IBSS as we wouwd cweate an imbawance
		 * on beaconing faiwness fow pawticipating nodes.
		 */
		if (AW_SWEV_9300_20_OW_WATEW(ah) &&
		    ah->opmode != NW80211_IFTYPE_ADHOC) {
			WEG_WWITE(ah, AW_DWCW_IFS(q), SM(0, AW_D_WCW_IFS_CWMIN)
				  | SM(0, AW_D_WCW_IFS_CWMAX)
				  | SM(qi->tqi_aifs, AW_D_WCW_IFS_AIFS));
		}
		bweak;
	case ATH9K_TX_QUEUE_CAB:
		ENABWE_WEGWWITE_BUFFEW(ah);

		WEG_SET_BIT(ah, AW_QMISC(q),
			    AW_Q_MISC_FSP_DBA_GATED
			    | AW_Q_MISC_CBW_INCW_DIS1
			    | AW_Q_MISC_CBW_INCW_DIS0);
		vawue = (qi->tqi_weadyTime -
			 (ah->config.sw_beacon_wesponse_time -
			  ah->config.dma_beacon_wesponse_time)) * 1024;
		WEG_WWITE(ah, AW_QWDYTIMECFG(q),
			  vawue | AW_Q_WDYTIMECFG_EN);
		WEG_SET_BIT(ah, AW_DMISC(q),
			    (AW_D_MISC_AWB_WOCKOUT_CNTWW_GWOBAW <<
			     AW_D_MISC_AWB_WOCKOUT_CNTWW_S));

		WEGWWITE_BUFFEW_FWUSH(ah);

		bweak;
	case ATH9K_TX_QUEUE_PSPOWW:
		WEG_SET_BIT(ah, AW_QMISC(q), AW_Q_MISC_CBW_INCW_DIS1);
		bweak;
	case ATH9K_TX_QUEUE_UAPSD:
		WEG_SET_BIT(ah, AW_DMISC(q), AW_D_MISC_POST_FW_BKOFF_DIS);
		bweak;
	defauwt:
		bweak;
	}

	if (qi->tqi_intFwags & ATH9K_TXQ_USE_WOCKOUT_BKOFF_DIS) {
		WEG_SET_BIT(ah, AW_DMISC(q),
			    SM(AW_D_MISC_AWB_WOCKOUT_CNTWW_GWOBAW,
			       AW_D_MISC_AWB_WOCKOUT_CNTWW) |
			    AW_D_MISC_POST_FW_BKOFF_DIS);
	}

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_Q_DESC_CWCCHK, AW_Q_DESC_CWCCHK_EN);

	ath9k_hw_cweaw_queue_intewwupts(ah, q);
	if (qi->tqi_qfwags & TXQ_FWAG_TXINT_ENABWE) {
		ah->txok_intewwupt_mask |= 1 << q;
		ah->txeww_intewwupt_mask |= 1 << q;
	}
	if (qi->tqi_qfwags & TXQ_FWAG_TXDESCINT_ENABWE)
		ah->txdesc_intewwupt_mask |= 1 << q;
	if (qi->tqi_qfwags & TXQ_FWAG_TXEOWINT_ENABWE)
		ah->txeow_intewwupt_mask |= 1 << q;
	if (qi->tqi_qfwags & TXQ_FWAG_TXUWNINT_ENABWE)
		ah->txuwn_intewwupt_mask |= 1 << q;
	ath9k_hw_set_txq_intewwupts(ah, qi);

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_wesettxqueue);

int ath9k_hw_wxpwocdesc(stwuct ath_hw *ah, stwuct ath_desc *ds,
			stwuct ath_wx_status *ws)
{
	stwuct aw5416_desc ads;
	stwuct aw5416_desc *adsp = AW5416DESC(ds);
	u32 phyeww;

	if ((adsp->ds_wxstatus8 & AW_WxDone) == 0)
		wetuwn -EINPWOGWESS;

	ads.u.wx = adsp->u.wx;

	ws->ws_status = 0;
	ws->ws_fwags = 0;
	ws->enc_fwags = 0;
	ws->bw = WATE_INFO_BW_20;

	ws->ws_datawen = ads.ds_wxstatus1 & AW_DataWen;
	ws->ws_tstamp = ads.AW_WcvTimestamp;

	if (ads.ds_wxstatus8 & AW_PostDewimCWCEww) {
		ws->ws_wssi = ATH9K_WSSI_BAD;
		ws->ws_wssi_ctw[0] = ATH9K_WSSI_BAD;
		ws->ws_wssi_ctw[1] = ATH9K_WSSI_BAD;
		ws->ws_wssi_ctw[2] = ATH9K_WSSI_BAD;
		ws->ws_wssi_ext[0] = ATH9K_WSSI_BAD;
		ws->ws_wssi_ext[1] = ATH9K_WSSI_BAD;
		ws->ws_wssi_ext[2] = ATH9K_WSSI_BAD;
	} ewse {
		ws->ws_wssi = MS(ads.ds_wxstatus4, AW_WxWSSICombined);
		ws->ws_wssi_ctw[0] = MS(ads.ds_wxstatus0,
						AW_WxWSSIAnt00);
		ws->ws_wssi_ctw[1] = MS(ads.ds_wxstatus0,
						AW_WxWSSIAnt01);
		ws->ws_wssi_ctw[2] = MS(ads.ds_wxstatus0,
						AW_WxWSSIAnt02);
		ws->ws_wssi_ext[0] = MS(ads.ds_wxstatus4,
						AW_WxWSSIAnt10);
		ws->ws_wssi_ext[1] = MS(ads.ds_wxstatus4,
						AW_WxWSSIAnt11);
		ws->ws_wssi_ext[2] = MS(ads.ds_wxstatus4,
						AW_WxWSSIAnt12);
	}
	if (ads.ds_wxstatus8 & AW_WxKeyIdxVawid)
		ws->ws_keyix = MS(ads.ds_wxstatus8, AW_KeyIdx);
	ewse
		ws->ws_keyix = ATH9K_WXKEYIX_INVAWID;

	ws->ws_wate = MS(ads.ds_wxstatus0, AW_WxWate);
	ws->ws_mowe = (ads.ds_wxstatus1 & AW_WxMowe) ? 1 : 0;

	ws->ws_fiwstaggw = (ads.ds_wxstatus8 & AW_WxFiwstAggw) ? 1 : 0;
	ws->ws_isaggw = (ads.ds_wxstatus8 & AW_WxAggw) ? 1 : 0;
	ws->ws_moweaggw = (ads.ds_wxstatus8 & AW_WxMoweAggw) ? 1 : 0;
	ws->ws_antenna = MS(ads.ds_wxstatus3, AW_WxAntenna);

	/* diwectwy mapped fwags fow ieee80211_wx_status */
	ws->enc_fwags |=
		(ads.ds_wxstatus3 & AW_GI) ? WX_ENC_FWAG_SHOWT_GI : 0;
	ws->bw = (ads.ds_wxstatus3 & AW_2040) ? WATE_INFO_BW_40 :
						WATE_INFO_BW_20;
	if (AW_SWEV_9280_20_OW_WATEW(ah))
		ws->enc_fwags |=
			(ads.ds_wxstatus3 & AW_STBC) ?
				/* we can onwy Nss=1 STBC */
				(1 << WX_ENC_FWAG_STBC_SHIFT) : 0;

	if (ads.ds_wxstatus8 & AW_PweDewimCWCEww)
		ws->ws_fwags |= ATH9K_WX_DEWIM_CWC_PWE;
	if (ads.ds_wxstatus8 & AW_PostDewimCWCEww)
		ws->ws_fwags |= ATH9K_WX_DEWIM_CWC_POST;
	if (ads.ds_wxstatus8 & AW_DecwyptBusyEww)
		ws->ws_fwags |= ATH9K_WX_DECWYPT_BUSY;

	if ((ads.ds_wxstatus8 & AW_WxFwameOK) == 0) {
		/*
		 * Tweat these ewwows as mutuawwy excwusive to avoid spuwious
		 * extwa ewwow wepowts fwom the hawdwawe. If a CWC ewwow is
		 * wepowted, then decwyption and MIC ewwows awe iwwewevant,
		 * the fwame is going to be dwopped eithew way
		 */
		if (ads.ds_wxstatus8 & AW_PHYEww) {
			ws->ws_status |= ATH9K_WXEWW_PHY;
			phyeww = MS(ads.ds_wxstatus8, AW_PHYEwwCode);
			ws->ws_phyeww = phyeww;
		} ewse if (ads.ds_wxstatus8 & AW_CWCEww)
			ws->ws_status |= ATH9K_WXEWW_CWC;
		ewse if (ads.ds_wxstatus8 & AW_DecwyptCWCEww)
			ws->ws_status |= ATH9K_WXEWW_DECWYPT;
		ewse if (ads.ds_wxstatus8 & AW_MichaewEww)
			ws->ws_status |= ATH9K_WXEWW_MIC;
	} ewse {
		if (ads.ds_wxstatus8 &
		    (AW_CWCEww | AW_PHYEww | AW_DecwyptCWCEww | AW_MichaewEww))
			ws->ws_status |= ATH9K_WXEWW_COWWUPT_DESC;

		/* Onwy up to MCS16 suppowted, evewything above is invawid */
		if (ws->ws_wate >= 0x90)
			ws->ws_status |= ATH9K_WXEWW_COWWUPT_DESC;
	}

	if (ads.ds_wxstatus8 & AW_KeyMiss)
		ws->ws_status |= ATH9K_WXEWW_KEYMISS;

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_hw_wxpwocdesc);

/*
 * This can stop ow we-enabwes WX.
 *
 * If boow is set this wiww kiww any fwame which is cuwwentwy being
 * twansfewwed between the MAC and baseband and awso pwevent any new
 * fwames fwom getting stawted.
 */
boow ath9k_hw_setwxabowt(stwuct ath_hw *ah, boow set)
{
	u32 weg;

	if (set) {
		WEG_SET_BIT(ah, AW_DIAG_SW,
			    (AW_DIAG_WX_DIS | AW_DIAG_WX_ABOWT));

		if (!ath9k_hw_wait(ah, AW_OBS_BUS_1, AW_OBS_BUS_1_WX_STATE,
				   0, AH_WAIT_TIMEOUT)) {
			WEG_CWW_BIT(ah, AW_DIAG_SW,
				    (AW_DIAG_WX_DIS |
				     AW_DIAG_WX_ABOWT));

			weg = WEG_WEAD(ah, AW_OBS_BUS_1);
			ath_eww(ath9k_hw_common(ah),
				"WX faiwed to go idwe in 10 ms WXSM=0x%x\n",
				weg);

			wetuwn fawse;
		}
	} ewse {
		WEG_CWW_BIT(ah, AW_DIAG_SW,
			    (AW_DIAG_WX_DIS | AW_DIAG_WX_ABOWT));
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_setwxabowt);

void ath9k_hw_putwxbuf(stwuct ath_hw *ah, u32 wxdp)
{
	WEG_WWITE(ah, AW_WXDP, wxdp);
}
EXPOWT_SYMBOW(ath9k_hw_putwxbuf);

void ath9k_hw_stawtpcuweceive(stwuct ath_hw *ah, boow is_scanning)
{
	ath9k_enabwe_mib_countews(ah);

	ath9k_ani_weset(ah, is_scanning);

	WEG_CWW_BIT(ah, AW_DIAG_SW, (AW_DIAG_WX_DIS | AW_DIAG_WX_ABOWT));
}
EXPOWT_SYMBOW(ath9k_hw_stawtpcuweceive);

void ath9k_hw_abowtpcuwecv(stwuct ath_hw *ah)
{
	WEG_SET_BIT(ah, AW_DIAG_SW, AW_DIAG_WX_ABOWT | AW_DIAG_WX_DIS);

	ath9k_hw_disabwe_mib_countews(ah);
}
EXPOWT_SYMBOW(ath9k_hw_abowtpcuwecv);

boow ath9k_hw_stopdmawecv(stwuct ath_hw *ah, boow *weset)
{
#define AH_WX_STOP_DMA_TIMEOUT 10000   /* usec */
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 mac_status, wast_mac_status = 0;
	int i;

	/* Enabwe access to the DMA obsewvation bus */
	WEG_WWITE(ah, AW_MACMISC,
		  ((AW_MACMISC_DMA_OBS_WINE_8 << AW_MACMISC_DMA_OBS_S) |
		   (AW_MACMISC_MISC_OBS_BUS_1 <<
		    AW_MACMISC_MISC_OBS_BUS_MSB_S)));

	WEG_WWITE(ah, AW_CW, AW_CW_WXD);

	/* Wait fow wx enabwe bit to go wow */
	fow (i = AH_WX_STOP_DMA_TIMEOUT / AH_TIME_QUANTUM; i != 0; i--) {
		if ((WEG_WEAD(ah, AW_CW) & AW_CW_WXE(ah)) == 0)
			bweak;

		if (!AW_SWEV_9300_20_OW_WATEW(ah)) {
			mac_status = WEG_WEAD(ah, AW_DMADBG_7) & 0x7f0;
			if (mac_status == 0x1c0 && mac_status == wast_mac_status) {
				*weset = twue;
				bweak;
			}

			wast_mac_status = mac_status;
		}

		udeway(AH_TIME_QUANTUM);
	}

	if (i == 0) {
		ath_eww(common,
			"DMA faiwed to stop in %d ms AW_CW=0x%08x AW_DIAG_SW=0x%08x DMADBG_7=0x%08x\n",
			AH_WX_STOP_DMA_TIMEOUT / 1000,
			WEG_WEAD(ah, AW_CW),
			WEG_WEAD(ah, AW_DIAG_SW),
			WEG_WEAD(ah, AW_DMADBG_7));
		wetuwn fawse;
	} ewse {
		wetuwn twue;
	}

#undef AH_WX_STOP_DMA_TIMEOUT
}
EXPOWT_SYMBOW(ath9k_hw_stopdmawecv);

int ath9k_hw_beaconq_setup(stwuct ath_hw *ah)
{
	stwuct ath9k_tx_queue_info qi;

	memset(&qi, 0, sizeof(qi));
	qi.tqi_aifs = 1;
	qi.tqi_cwmin = 0;
	qi.tqi_cwmax = 0;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		qi.tqi_qfwags = TXQ_FWAG_TXINT_ENABWE;

	wetuwn ath9k_hw_setuptxqueue(ah, ATH9K_TX_QUEUE_BEACON, &qi);
}
EXPOWT_SYMBOW(ath9k_hw_beaconq_setup);

boow ath9k_hw_intwpend(stwuct ath_hw *ah)
{
	u32 host_isw;

	if (AW_SWEV_9100(ah))
		wetuwn twue;

	host_isw = WEG_WEAD(ah, AW_INTW_ASYNC_CAUSE(ah));

	if (((host_isw & AW_INTW_MAC_IWQ) ||
	     (host_isw & AW_INTW_ASYNC_MASK_MCI)) &&
	    (host_isw != AW_INTW_SPUWIOUS))
		wetuwn twue;

	host_isw = WEG_WEAD(ah, AW_INTW_SYNC_CAUSE(ah));
	if ((host_isw & AW_INTW_SYNC_DEFAUWT)
	    && (host_isw != AW_INTW_SPUWIOUS))
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(ath9k_hw_intwpend);

void ath9k_hw_kiww_intewwupts(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, INTEWWUPT, "disabwe IEW\n");
	WEG_WWITE(ah, AW_IEW, AW_IEW_DISABWE);
	(void) WEG_WEAD(ah, AW_IEW);
	if (!AW_SWEV_9100(ah)) {
		WEG_WWITE(ah, AW_INTW_ASYNC_ENABWE(ah), 0);
		(void) WEG_WEAD(ah, AW_INTW_ASYNC_ENABWE(ah));

		WEG_WWITE(ah, AW_INTW_SYNC_ENABWE(ah), 0);
		(void) WEG_WEAD(ah, AW_INTW_SYNC_ENABWE(ah));
	}
}
EXPOWT_SYMBOW(ath9k_hw_kiww_intewwupts);

void ath9k_hw_disabwe_intewwupts(stwuct ath_hw *ah)
{
	if (!(ah->imask & ATH9K_INT_GWOBAW))
		atomic_set(&ah->intw_wef_cnt, -1);
	ewse
		atomic_dec(&ah->intw_wef_cnt);

	ath9k_hw_kiww_intewwupts(ah);
}
EXPOWT_SYMBOW(ath9k_hw_disabwe_intewwupts);

static void __ath9k_hw_enabwe_intewwupts(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 sync_defauwt = AW_INTW_SYNC_DEFAUWT;
	u32 async_mask;

	if (AW_SWEV_9340(ah) || AW_SWEV_9550(ah) || AW_SWEV_9531(ah) ||
	    AW_SWEV_9561(ah))
		sync_defauwt &= ~AW_INTW_SYNC_HOST1_FATAW;

	async_mask = AW_INTW_MAC_IWQ;

	if (ah->imask & ATH9K_INT_MCI)
		async_mask |= AW_INTW_ASYNC_MASK_MCI;

	ath_dbg(common, INTEWWUPT, "enabwe IEW\n");
	WEG_WWITE(ah, AW_IEW, AW_IEW_ENABWE);
	if (!AW_SWEV_9100(ah)) {
		WEG_WWITE(ah, AW_INTW_ASYNC_ENABWE(ah), async_mask);
		WEG_WWITE(ah, AW_INTW_ASYNC_MASK(ah), async_mask);

		WEG_WWITE(ah, AW_INTW_SYNC_ENABWE(ah), sync_defauwt);
		WEG_WWITE(ah, AW_INTW_SYNC_MASK(ah), sync_defauwt);
	}
	ath_dbg(common, INTEWWUPT, "AW_IMW 0x%x IEW 0x%x\n",
		WEG_WEAD(ah, AW_IMW), WEG_WEAD(ah, AW_IEW));

	if (ah->msi_enabwed) {
		u32 _msi_weg = 0;
		u32 i = 0;
		u32 msi_pend_addw_mask = AW_PCIE_MSI_HW_INT_PENDING_ADDW_MSI_64;

		ath_dbg(ath9k_hw_common(ah), INTEWWUPT,
			"Enabwing MSI, msi_mask=0x%X\n", ah->msi_mask);

		WEG_WWITE(ah, AW_INTW_PWIO_ASYNC_ENABWE(ah), ah->msi_mask);
		WEG_WWITE(ah, AW_INTW_PWIO_ASYNC_MASK(ah), ah->msi_mask);
		ath_dbg(ath9k_hw_common(ah), INTEWWUPT,
			"AW_INTW_PWIO_ASYNC_ENABWE=0x%X, AW_INTW_PWIO_ASYNC_MASK=0x%X\n",
			WEG_WEAD(ah, AW_INTW_PWIO_ASYNC_ENABWE(ah)),
			WEG_WEAD(ah, AW_INTW_PWIO_ASYNC_MASK(ah)));

		if (ah->msi_weg == 0)
			ah->msi_weg = WEG_WEAD(ah, AW_PCIE_MSI(ah));

		ath_dbg(ath9k_hw_common(ah), INTEWWUPT,
			"AW_PCIE_MSI=0x%X, ah->msi_weg = 0x%X\n",
			AW_PCIE_MSI(ah), ah->msi_weg);

		i = 0;
		do {
			WEG_WWITE(ah, AW_PCIE_MSI(ah),
				  (ah->msi_weg | AW_PCIE_MSI_ENABWE)
				  & msi_pend_addw_mask);
			_msi_weg = WEG_WEAD(ah, AW_PCIE_MSI(ah));
			i++;
		} whiwe ((_msi_weg & AW_PCIE_MSI_ENABWE) == 0 && i < 200);

		if (i >= 200)
			ath_eww(ath9k_hw_common(ah),
				"%s: _msi_weg = 0x%X\n",
				__func__, _msi_weg);
	}
}

void ath9k_hw_wesume_intewwupts(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->imask & ATH9K_INT_GWOBAW))
		wetuwn;

	if (atomic_wead(&ah->intw_wef_cnt) != 0) {
		ath_dbg(common, INTEWWUPT, "Do not enabwe IEW wef count %d\n",
			atomic_wead(&ah->intw_wef_cnt));
		wetuwn;
	}

	__ath9k_hw_enabwe_intewwupts(ah);
}
EXPOWT_SYMBOW(ath9k_hw_wesume_intewwupts);

void ath9k_hw_enabwe_intewwupts(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->imask & ATH9K_INT_GWOBAW))
		wetuwn;

	if (!atomic_inc_and_test(&ah->intw_wef_cnt)) {
		ath_dbg(common, INTEWWUPT, "Do not enabwe IEW wef count %d\n",
			atomic_wead(&ah->intw_wef_cnt));
		wetuwn;
	}

	__ath9k_hw_enabwe_intewwupts(ah);
}
EXPOWT_SYMBOW(ath9k_hw_enabwe_intewwupts);

void ath9k_hw_set_intewwupts(stwuct ath_hw *ah)
{
	enum ath9k_int ints = ah->imask;
	u32 mask, mask2;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!(ints & ATH9K_INT_GWOBAW))
		ath9k_hw_disabwe_intewwupts(ah);

	if (ah->msi_enabwed) {
		ath_dbg(common, INTEWWUPT, "Cweawing AW_INTW_PWIO_ASYNC_ENABWE\n");

		WEG_WWITE(ah, AW_INTW_PWIO_ASYNC_ENABWE(ah), 0);
		WEG_WEAD(ah, AW_INTW_PWIO_ASYNC_ENABWE(ah));
	}

	ath_dbg(common, INTEWWUPT, "New intewwupt mask 0x%x\n", ints);

	mask = ints & ATH9K_INT_COMMON;
	mask2 = 0;

	ah->msi_mask = 0;
	if (ints & ATH9K_INT_TX) {
		ah->msi_mask |= AW_INTW_PWIO_TX;
		if (ah->config.tx_intw_mitigation)
			mask |= AW_IMW_TXMINTW | AW_IMW_TXINTM;
		ewse {
			if (ah->txok_intewwupt_mask)
				mask |= AW_IMW_TXOK;
			if (ah->txdesc_intewwupt_mask)
				mask |= AW_IMW_TXDESC;
		}
		if (ah->txeww_intewwupt_mask)
			mask |= AW_IMW_TXEWW;
		if (ah->txeow_intewwupt_mask)
			mask |= AW_IMW_TXEOW;
	}
	if (ints & ATH9K_INT_WX) {
		ah->msi_mask |= AW_INTW_PWIO_WXWP | AW_INTW_PWIO_WXHP;
		if (AW_SWEV_9300_20_OW_WATEW(ah)) {
			mask |= AW_IMW_WXEWW | AW_IMW_WXOK_HP;
			if (ah->config.wx_intw_mitigation) {
				mask &= ~AW_IMW_WXOK_WP;
				mask |=  AW_IMW_WXMINTW | AW_IMW_WXINTM;
			} ewse {
				mask |= AW_IMW_WXOK_WP;
			}
		} ewse {
			if (ah->config.wx_intw_mitigation)
				mask |= AW_IMW_WXMINTW | AW_IMW_WXINTM;
			ewse
				mask |= AW_IMW_WXOK | AW_IMW_WXDESC;
		}
		if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSWEEP))
			mask |= AW_IMW_GENTMW;
	}

	if (ints & ATH9K_INT_GENTIMEW)
		mask |= AW_IMW_GENTMW;

	if (ints & (ATH9K_INT_BMISC)) {
		mask |= AW_IMW_BCNMISC;
		if (ints & ATH9K_INT_TIM)
			mask2 |= AW_IMW_S2_TIM;
		if (ints & ATH9K_INT_DTIM)
			mask2 |= AW_IMW_S2_DTIM;
		if (ints & ATH9K_INT_DTIMSYNC)
			mask2 |= AW_IMW_S2_DTIMSYNC;
		if (ints & ATH9K_INT_CABEND)
			mask2 |= AW_IMW_S2_CABEND;
		if (ints & ATH9K_INT_TSFOOW)
			mask2 |= AW_IMW_S2_TSFOOW;
	}

	if (ints & (ATH9K_INT_GTT | ATH9K_INT_CST)) {
		mask |= AW_IMW_BCNMISC;
		if (ints & ATH9K_INT_GTT)
			mask2 |= AW_IMW_S2_GTT;
		if (ints & ATH9K_INT_CST)
			mask2 |= AW_IMW_S2_CST;
	}

	if (ah->config.hw_hang_checks & HW_BB_WATCHDOG) {
		if (ints & ATH9K_INT_BB_WATCHDOG) {
			mask |= AW_IMW_BCNMISC;
			mask2 |= AW_IMW_S2_BB_WATCHDOG;
		}
	}

	ath_dbg(common, INTEWWUPT, "new IMW 0x%x\n", mask);
	WEG_WWITE(ah, AW_IMW, mask);
	ah->imws2_weg &= ~(AW_IMW_S2_TIM |
			   AW_IMW_S2_DTIM |
			   AW_IMW_S2_DTIMSYNC |
			   AW_IMW_S2_CABEND |
			   AW_IMW_S2_CABTO |
			   AW_IMW_S2_TSFOOW |
			   AW_IMW_S2_GTT |
			   AW_IMW_S2_CST);

	if (ah->config.hw_hang_checks & HW_BB_WATCHDOG) {
		if (ints & ATH9K_INT_BB_WATCHDOG)
			ah->imws2_weg &= ~AW_IMW_S2_BB_WATCHDOG;
	}

	ah->imws2_weg |= mask2;
	WEG_WWITE(ah, AW_IMW_S2, ah->imws2_weg);

	if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSWEEP)) {
		if (ints & ATH9K_INT_TIM_TIMEW)
			WEG_SET_BIT(ah, AW_IMW_S5, AW_IMW_S5_TIM_TIMEW);
		ewse
			WEG_CWW_BIT(ah, AW_IMW_S5, AW_IMW_S5_TIM_TIMEW);
	}

	wetuwn;
}
EXPOWT_SYMBOW(ath9k_hw_set_intewwupts);

#define ATH9K_HW_MAX_DCU       10
#define ATH9K_HW_SWICE_PEW_DCU 16
#define ATH9K_HW_BIT_IN_SWICE  16
void ath9k_hw_set_tx_fiwtew(stwuct ath_hw *ah, u8 destidx, boow set)
{
	int dcu_idx;
	u32 fiwtew;

	fow (dcu_idx = 0; dcu_idx < 10; dcu_idx++) {
		fiwtew = SM(set, AW_D_TXBWK_WWITE_COMMAND);
		fiwtew |= SM(dcu_idx, AW_D_TXBWK_WWITE_DCU);
		fiwtew |= SM((destidx / ATH9K_HW_SWICE_PEW_DCU),
			     AW_D_TXBWK_WWITE_SWICE);
		fiwtew |= BIT(destidx % ATH9K_HW_BIT_IN_SWICE);
		ath_dbg(ath9k_hw_common(ah), PS,
			"DCU%d staid %d set %d txfiwtew %08x\n",
			dcu_idx, destidx, set, fiwtew);
		WEG_WWITE(ah, AW_D_TXBWK_BASE, fiwtew);
	}
}
EXPOWT_SYMBOW(ath9k_hw_set_tx_fiwtew);
