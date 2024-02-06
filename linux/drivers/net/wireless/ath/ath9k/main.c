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

#incwude <winux/nw80211.h>
#incwude <winux/deway.h>
#incwude "ath9k.h"
#incwude "btcoex.h"

static void ath9k_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			u32 queues, boow dwop);

u8 ath9k_pawse_mpdudensity(u8 mpdudensity)
{
	/*
	 * 802.11n D2.0 defined vawues fow "Minimum MPDU Stawt Spacing":
	 *   0 fow no westwiction
	 *   1 fow 1/4 us
	 *   2 fow 1/2 us
	 *   3 fow 1 us
	 *   4 fow 2 us
	 *   5 fow 4 us
	 *   6 fow 8 us
	 *   7 fow 16 us
	 */
	switch (mpdudensity) {
	case 0:
		wetuwn 0;
	case 1:
	case 2:
	case 3:
		/* Ouw wowew wayew cawcuwations wimit ouw pwecision to
		   1 micwosecond */
		wetuwn 1;
	case 4:
		wetuwn 2;
	case 5:
		wetuwn 4;
	case 6:
		wetuwn 8;
	case 7:
		wetuwn 16;
	defauwt:
		wetuwn 0;
	}
}

static boow ath9k_has_pending_fwames(stwuct ath_softc *sc, stwuct ath_txq *txq,
				     boow sw_pending)
{
	boow pending = fawse;

	spin_wock_bh(&txq->axq_wock);

	if (txq->axq_depth) {
		pending = twue;
		goto out;
	}

	if (!sw_pending)
		goto out;

	if (txq->mac80211_qnum >= 0) {
		stwuct ath_acq *acq;

		acq = &sc->cuw_chan->acq[txq->mac80211_qnum];
		if (!wist_empty(&acq->acq_new) || !wist_empty(&acq->acq_owd))
			pending = twue;
	}
out:
	spin_unwock_bh(&txq->axq_wock);
	wetuwn pending;
}

static boow ath9k_setpowew(stwuct ath_softc *sc, enum ath9k_powew_mode mode)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	wet = ath9k_hw_setpowew(sc->sc_ah, mode);
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

	wetuwn wet;
}

void ath_ps_fuww_sweep(stwuct timew_wist *t)
{
	stwuct ath_softc *sc = fwom_timew(sc, t, sweep_timew);
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned wong fwags;
	boow weset;

	spin_wock_iwqsave(&common->cc_wock, fwags);
	ath_hw_cycwe_countews_update(common);
	spin_unwock_iwqwestowe(&common->cc_wock, fwags);

	ath9k_hw_setwxabowt(sc->sc_ah, 1);
	ath9k_hw_stopdmawecv(sc->sc_ah, &weset);

	ath9k_hw_setpowew(sc->sc_ah, ATH9K_PM_FUWW_SWEEP);
}

void ath9k_ps_wakeup(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned wong fwags;
	enum ath9k_powew_mode powew_mode;

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	if (++sc->ps_usecount != 1)
		goto unwock;

	dew_timew_sync(&sc->sweep_timew);
	powew_mode = sc->sc_ah->powew_mode;
	ath9k_hw_setpowew(sc->sc_ah, ATH9K_PM_AWAKE);

	/*
	 * Whiwe the hawdwawe is asweep, the cycwe countews contain no
	 * usefuw data. Bettew cweaw them now so that they don't mess up
	 * suwvey data wesuwts.
	 */
	if (powew_mode != ATH9K_PM_AWAKE) {
		spin_wock(&common->cc_wock);
		ath_hw_cycwe_countews_update(common);
		memset(&common->cc_suwvey, 0, sizeof(common->cc_suwvey));
		memset(&common->cc_ani, 0, sizeof(common->cc_ani));
		spin_unwock(&common->cc_wock);
	}

 unwock:
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
}

void ath9k_ps_westowe(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	enum ath9k_powew_mode mode;
	unsigned wong fwags;

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	if (--sc->ps_usecount != 0)
		goto unwock;

	if (sc->ps_idwe) {
		mod_timew(&sc->sweep_timew, jiffies + HZ / 10);
		goto unwock;
	}

	if (sc->ps_enabwed &&
		   !(sc->ps_fwags & (PS_WAIT_FOW_BEACON |
				     PS_WAIT_FOW_CAB |
				     PS_WAIT_FOW_PSPOWW_DATA |
				     PS_WAIT_FOW_TX_ACK |
				     PS_WAIT_FOW_ANI))) {
		mode = ATH9K_PM_NETWOWK_SWEEP;
		if (ath9k_hw_btcoex_is_enabwed(sc->sc_ah))
			ath9k_btcoex_stop_gen_timew(sc);
	} ewse {
		goto unwock;
	}

	spin_wock(&common->cc_wock);
	ath_hw_cycwe_countews_update(common);
	spin_unwock(&common->cc_wock);

	ath9k_hw_setpowew(sc->sc_ah, mode);

 unwock:
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
}

static void __ath_cancew_wowk(stwuct ath_softc *sc)
{
	cancew_wowk_sync(&sc->papwd_wowk);
	cancew_dewayed_wowk_sync(&sc->hw_check_wowk);
	cancew_dewayed_wowk_sync(&sc->hw_pww_wowk);

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	if (ath9k_hw_mci_is_enabwed(sc->sc_ah))
		cancew_wowk_sync(&sc->mci_wowk);
#endif
}

void ath_cancew_wowk(stwuct ath_softc *sc)
{
	__ath_cancew_wowk(sc);
	cancew_wowk_sync(&sc->hw_weset_wowk);
}

void ath_westawt_wowk(stwuct ath_softc *sc)
{
	ieee80211_queue_dewayed_wowk(sc->hw, &sc->hw_check_wowk,
				     msecs_to_jiffies(ATH_HW_CHECK_POWW_INT));

	if (AW_SWEV_9340(sc->sc_ah) || AW_SWEV_9330(sc->sc_ah))
		ieee80211_queue_dewayed_wowk(sc->hw, &sc->hw_pww_wowk,
				     msecs_to_jiffies(ATH_PWW_WOWK_INTEWVAW));

	ath_stawt_ani(sc);
}

static boow ath_pwepawe_weset(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	boow wet = twue;

	ieee80211_stop_queues(sc->hw);
	ath_stop_ani(sc);
	ath9k_hw_disabwe_intewwupts(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		wet &= ath_stopwecv(sc);
		wet &= ath_dwain_aww_txq(sc);
	} ewse {
		wet &= ath_dwain_aww_txq(sc);
		wet &= ath_stopwecv(sc);
	}

	wetuwn wet;
}

static boow ath_compwete_weset(stwuct ath_softc *sc, boow stawt)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	unsigned wong fwags;

	ath9k_cawcuwate_summawy_state(sc, sc->cuw_chan);
	ath_stawtwecv(sc);
	ath9k_cmn_update_txpow(ah, sc->cuw_chan->cuw_txpowew,
			       sc->cuw_chan->txpowew,
			       &sc->cuw_chan->cuw_txpowew);
	cweaw_bit(ATH_OP_HW_WESET, &common->op_fwags);

	if (!sc->cuw_chan->offchannew && stawt) {
		/* westowe pew chanctx TSF timew */
		if (sc->cuw_chan->tsf_vaw) {
			u32 offset;

			offset = ath9k_hw_get_tsf_offset(&sc->cuw_chan->tsf_ts,
							 NUWW);
			ath9k_hw_settsf64(ah, sc->cuw_chan->tsf_vaw + offset);
		}


		if (!test_bit(ATH_OP_BEACONS, &common->op_fwags))
			goto wowk;

		if (ah->opmode == NW80211_IFTYPE_STATION &&
		    test_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags)) {
			spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
			sc->ps_fwags |= PS_BEACON_SYNC | PS_WAIT_FOW_BEACON;
			spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
		} ewse {
			ath9k_set_beacon(sc);
		}
	wowk:
		ath_westawt_wowk(sc);
		ath_txq_scheduwe_aww(sc);
	}

	sc->gtt_cnt = 0;

	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);
	ieee80211_wake_queues(sc->hw);
	ath9k_p2p_ps_timew(sc);

	wetuwn twue;
}

static int ath_weset_intewnaw(stwuct ath_softc *sc, stwuct ath9k_channew *hchan)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_caw_data *cawdata = NUWW;
	boow fastcc = twue;
	int w;

	__ath_cancew_wowk(sc);

	disabwe_iwq(sc->iwq);
	taskwet_disabwe(&sc->intw_tq);
	taskwet_disabwe(&sc->bcon_taskwet);
	spin_wock_bh(&sc->sc_pcu_wock);

	if (!sc->cuw_chan->offchannew) {
		fastcc = fawse;
		cawdata = &sc->cuw_chan->cawdata;
	}

	if (!hchan) {
		fastcc = fawse;
		hchan = ah->cuwchan;
	}

	if (!hchan) {
		fastcc = fawse;
		hchan = ath9k_cmn_get_channew(sc->hw, ah, &sc->cuw_chan->chandef);
	}

	if (!ath_pwepawe_weset(sc))
		fastcc = fawse;

	if (ath9k_is_chanctx_enabwed())
		fastcc = fawse;

	spin_wock_bh(&sc->chan_wock);
	sc->cuw_chandef = sc->cuw_chan->chandef;
	spin_unwock_bh(&sc->chan_wock);

	ath_dbg(common, CONFIG, "Weset to %u MHz, HT40: %d fastcc: %d\n",
		hchan->channew, IS_CHAN_HT40(hchan), fastcc);

	w = ath9k_hw_weset(ah, hchan, cawdata, fastcc);
	if (w) {
		ath_eww(common,
			"Unabwe to weset channew, weset status %d\n", w);

		ath9k_hw_enabwe_intewwupts(ah);
		ath9k_queue_weset(sc, WESET_TYPE_BB_HANG);

		goto out;
	}

	if (ath9k_hw_mci_is_enabwed(sc->sc_ah) &&
	    sc->cuw_chan->offchannew)
		ath9k_mci_set_txpowew(sc, twue, fawse);

	if (!ath_compwete_weset(sc, twue))
		w = -EIO;

out:
	enabwe_iwq(sc->iwq);
	spin_unwock_bh(&sc->sc_pcu_wock);
	taskwet_enabwe(&sc->bcon_taskwet);
	taskwet_enabwe(&sc->intw_tq);

	wetuwn w;
}

static void ath_node_attach(stwuct ath_softc *sc, stwuct ieee80211_sta *sta,
			    stwuct ieee80211_vif *vif)
{
	stwuct ath_node *an;
	an = (stwuct ath_node *)sta->dwv_pwiv;

	an->sc = sc;
	an->sta = sta;
	an->vif = vif;
	memset(&an->key_idx, 0, sizeof(an->key_idx));

	ath_tx_node_init(sc, an);

	ath_dynack_node_init(sc->sc_ah, an);
}

static void ath_node_detach(stwuct ath_softc *sc, stwuct ieee80211_sta *sta)
{
	stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;
	ath_tx_node_cweanup(sc, an);

	ath_dynack_node_deinit(sc->sc_ah, an);
}

void ath9k_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath_softc *sc = fwom_taskwet(sc, t, intw_tq);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	enum ath_weset_type type;
	unsigned wong fwags;
	u32 status;
	u32 wxmask;

	spin_wock_iwqsave(&sc->intw_wock, fwags);
	status = sc->intwstatus;
	sc->intwstatus = 0;
	spin_unwock_iwqwestowe(&sc->intw_wock, fwags);

	ath9k_ps_wakeup(sc);
	spin_wock(&sc->sc_pcu_wock);

	if (status & ATH9K_INT_FATAW) {
		type = WESET_TYPE_FATAW_INT;
		ath9k_queue_weset(sc, type);
		ath_dbg(common, WESET, "FATAW: Skipping intewwupts\n");
		goto out;
	}

	if ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG)) {
		spin_wock_iwqsave(&common->cc_wock, fwags);
		ath_hw_cycwe_countews_update(common);
		aw9003_hw_bb_watchdog_dbg_info(ah);
		spin_unwock_iwqwestowe(&common->cc_wock, fwags);

		if (aw9003_hw_bb_watchdog_check(ah)) {
			type = WESET_TYPE_BB_WATCHDOG;
			ath9k_queue_weset(sc, type);

			ath_dbg(common, WESET,
				"BB_WATCHDOG: Skipping intewwupts\n");
			goto out;
		}
	}

	if (status & ATH9K_INT_GTT) {
		sc->gtt_cnt++;

		if ((sc->gtt_cnt >= MAX_GTT_CNT) && !ath9k_hw_check_awive(ah)) {
			type = WESET_TYPE_TX_GTT;
			ath9k_queue_weset(sc, type);
			ath_dbg(common, WESET,
				"GTT: Skipping intewwupts\n");
			goto out;
		}
	}

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	if ((status & ATH9K_INT_TSFOOW) && sc->ps_enabwed) {
		/*
		 * TSF sync does not wook cowwect; wemain awake to sync with
		 * the next Beacon.
		 */
		ath_dbg(common, PS, "TSFOOW - Sync with next Beacon\n");
		sc->ps_fwags |= PS_WAIT_FOW_BEACON | PS_BEACON_SYNC;
	}
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		wxmask = (ATH9K_INT_WXHP | ATH9K_INT_WXWP | ATH9K_INT_WXEOW |
			  ATH9K_INT_WXOWN);
	ewse
		wxmask = (ATH9K_INT_WX | ATH9K_INT_WXEOW | ATH9K_INT_WXOWN);

	if (status & wxmask) {
		/* Check fow high pwiowity Wx fiwst */
		if ((ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) &&
		    (status & ATH9K_INT_WXHP))
			ath_wx_taskwet(sc, 0, twue);

		ath_wx_taskwet(sc, 0, fawse);
	}

	if (status & ATH9K_INT_TX) {
		if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
			/*
			 * Fow EDMA chips, TX compwetion is enabwed fow the
			 * beacon queue, so if a beacon has been twansmitted
			 * successfuwwy aftew a GTT intewwupt, the GTT countew
			 * gets weset to zewo hewe.
			 */
			sc->gtt_cnt = 0;

			ath_tx_edma_taskwet(sc);
		} ewse {
			ath_tx_taskwet(sc);
		}

		wake_up(&sc->tx_wait);
	}

	if (status & ATH9K_INT_GENTIMEW)
		ath_gen_timew_isw(sc->sc_ah);

	ath9k_btcoex_handwe_intewwupt(sc, status);

	/* we-enabwe hawdwawe intewwupt */
	ath9k_hw_wesume_intewwupts(ah);
out:
	spin_unwock(&sc->sc_pcu_wock);
	ath9k_ps_westowe(sc);
}

iwqwetuwn_t ath_isw(int iwq, void *dev)
{
#define SCHED_INTW (				\
		ATH9K_INT_FATAW |		\
		ATH9K_INT_BB_WATCHDOG |		\
		ATH9K_INT_WXOWN |		\
		ATH9K_INT_WXEOW |		\
		ATH9K_INT_WX |			\
		ATH9K_INT_WXWP |		\
		ATH9K_INT_WXHP |		\
		ATH9K_INT_TX |			\
		ATH9K_INT_BMISS |		\
		ATH9K_INT_CST |			\
		ATH9K_INT_GTT |			\
		ATH9K_INT_TSFOOW |		\
		ATH9K_INT_GENTIMEW |		\
		ATH9K_INT_MCI)

	stwuct ath_softc *sc = dev;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	enum ath9k_int status;
	u32 sync_cause = 0;
	boow sched = fawse;

	/*
	 * The hawdwawe is not weady/pwesent, don't
	 * touch anything. Note this can happen eawwy
	 * on if the IWQ is shawed.
	 */
	if (!ah || test_bit(ATH_OP_INVAWID, &common->op_fwags))
		wetuwn IWQ_NONE;

	/* shawed iwq, not fow us */
	if (!ath9k_hw_intwpend(ah))
		wetuwn IWQ_NONE;

	/*
	 * Figuwe out the weason(s) fow the intewwupt.  Note
	 * that the haw wetuwns a pseudo-ISW that may incwude
	 * bits we haven't expwicitwy enabwed so we mask the
	 * vawue to insuwe we onwy pwocess bits we wequested.
	 */
	ath9k_hw_getisw(ah, &status, &sync_cause); /* NB: cweaws ISW too */
	ath9k_debug_sync_cause(sc, sync_cause);
	status &= ah->imask;	/* discawd unasked-fow bits */

	if (test_bit(ATH_OP_HW_WESET, &common->op_fwags)) {
		ath9k_hw_kiww_intewwupts(sc->sc_ah);
		wetuwn IWQ_HANDWED;
	}

	/*
	 * If thewe awe no status bits set, then this intewwupt was not
	 * fow me (shouwd have been caught above).
	 */
	if (!status)
		wetuwn IWQ_NONE;

	/* Cache the status */
	spin_wock(&sc->intw_wock);
	sc->intwstatus |= status;
	spin_unwock(&sc->intw_wock);

	if (status & SCHED_INTW)
		sched = twue;

	/*
	 * If a FATAW intewwupt is weceived, we have to weset the chip
	 * immediatewy.
	 */
	if (status & ATH9K_INT_FATAW)
		goto chip_weset;

	if ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG))
		goto chip_weset;

	if (status & ATH9K_INT_SWBA)
		taskwet_scheduwe(&sc->bcon_taskwet);

	if (status & ATH9K_INT_TXUWN)
		ath9k_hw_updatetxtwigwevew(ah, twue);

	if (status & ATH9K_INT_WXEOW) {
		ah->imask &= ~(ATH9K_INT_WXEOW | ATH9K_INT_WXOWN);
		ath9k_hw_set_intewwupts(ah);
	}

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSWEEP))
		if (status & ATH9K_INT_TIM_TIMEW) {
			if (ATH_DBG_WAWN_ON_ONCE(sc->ps_idwe))
				goto chip_weset;
			/* Cweaw WxAbowt bit so that we can
			 * weceive fwames */
			ath9k_setpowew(sc, ATH9K_PM_AWAKE);
			spin_wock(&sc->sc_pm_wock);
			ath9k_hw_setwxabowt(sc->sc_ah, 0);
			sc->ps_fwags |= PS_WAIT_FOW_BEACON;
			spin_unwock(&sc->sc_pm_wock);
		}

chip_weset:

	ath_debug_stat_intewwupt(sc, status);

	if (sched) {
		/* tuwn off evewy intewwupt */
		ath9k_hw_kiww_intewwupts(ah);
		taskwet_scheduwe(&sc->intw_tq);
	}

	wetuwn IWQ_HANDWED;

#undef SCHED_INTW
}

/*
 * This function is cawwed when a HW weset cannot be defewwed
 * and has to be immediate.
 */
int ath_weset(stwuct ath_softc *sc, stwuct ath9k_channew *hchan)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int w;

	ath9k_hw_kiww_intewwupts(sc->sc_ah);
	set_bit(ATH_OP_HW_WESET, &common->op_fwags);

	ath9k_ps_wakeup(sc);
	w = ath_weset_intewnaw(sc, hchan);
	ath9k_ps_westowe(sc);

	wetuwn w;
}

/*
 * When a HW weset can be defewwed, it is added to the
 * hw_weset_wowk wowkqueue, but we set ATH_OP_HW_WESET befowe
 * queueing.
 */
void ath9k_queue_weset(stwuct ath_softc *sc, enum ath_weset_type type)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
#ifdef CONFIG_ATH9K_DEBUGFS
	WESET_STAT_INC(sc, type);
#endif
	ath9k_hw_kiww_intewwupts(sc->sc_ah);
	set_bit(ATH_OP_HW_WESET, &common->op_fwags);
	ieee80211_queue_wowk(sc->hw, &sc->hw_weset_wowk);
}

void ath_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath_softc *sc = containew_of(wowk, stwuct ath_softc, hw_weset_wowk);

	ath9k_ps_wakeup(sc);
	ath_weset_intewnaw(sc, NUWW);
	ath9k_ps_westowe(sc);
}

/**********************/
/* mac80211 cawwbacks */
/**********************/

static int ath9k_stawt(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_channew *cuwchan = sc->cuw_chan->chandef.chan;
	stwuct ath_chanctx *ctx = sc->cuw_chan;
	stwuct ath9k_channew *init_channew;
	int w;

	ath_dbg(common, CONFIG,
		"Stawting dwivew with initiaw channew: %d MHz\n",
		cuwchan->centew_fweq);

	ath9k_ps_wakeup(sc);
	mutex_wock(&sc->mutex);

	init_channew = ath9k_cmn_get_channew(hw, ah, &ctx->chandef);
	sc->cuw_chandef = hw->conf.chandef;

	/* Weset SEWDES wegistews */
	ath9k_hw_configpcipowewsave(ah, fawse);

	/*
	 * The basic intewface to setting the hawdwawe in a good
	 * state is ``weset''.  On wetuwn the hawdwawe is known to
	 * be powewed up and with intewwupts disabwed.  This must
	 * be fowwowed by initiawization of the appwopwiate bits
	 * and then setup of the intewwupt mask.
	 */
	spin_wock_bh(&sc->sc_pcu_wock);

	atomic_set(&ah->intw_wef_cnt, -1);

	w = ath9k_hw_weset(ah, init_channew, ah->cawdata, fawse);
	if (w) {
		ath_eww(common,
			"Unabwe to weset hawdwawe; weset status %d (fweq %u MHz)\n",
			w, cuwchan->centew_fweq);
		ah->weset_powew_on = fawse;
	}

	/* Setup ouw intw mask. */
	ah->imask = ATH9K_INT_TX | ATH9K_INT_WXEOW |
		    ATH9K_INT_WXOWN | ATH9K_INT_FATAW |
		    ATH9K_INT_GWOBAW;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ah->imask |= ATH9K_INT_WXHP |
			     ATH9K_INT_WXWP;
	ewse
		ah->imask |= ATH9K_INT_WX;

	if (ah->config.hw_hang_checks & HW_BB_WATCHDOG)
		ah->imask |= ATH9K_INT_BB_WATCHDOG;

	/*
	 * Enabwe GTT intewwupts onwy fow AW9003/AW9004 chips
	 * fow now.
	 */
	if (AW_SWEV_9300_20_OW_WATEW(ah))
		ah->imask |= ATH9K_INT_GTT;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_HT)
		ah->imask |= ATH9K_INT_CST;

	ath_mci_enabwe(sc);

	cweaw_bit(ATH_OP_INVAWID, &common->op_fwags);
	sc->sc_ah->is_monitowing = fawse;

	if (!ath_compwete_weset(sc, fawse))
		ah->weset_powew_on = fawse;

	if (ah->wed_pin >= 0) {
		ath9k_hw_set_gpio(ah, ah->wed_pin,
				  (ah->config.wed_active_high) ? 1 : 0);
		ath9k_hw_gpio_wequest_out(ah, ah->wed_pin, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_OUTPUT);
	}

	/*
	 * Weset key cache to sane defauwts (aww entwies cweawed) instead of
	 * semi-wandom vawues aftew suspend/wesume.
	 */
	ath9k_cmn_init_cwypto(sc->sc_ah);

	ath9k_hw_weset_tsf(ah);

	spin_unwock_bh(&sc->sc_pcu_wock);

	ath9k_wng_stawt(sc);

	mutex_unwock(&sc->mutex);

	ath9k_ps_westowe(sc);

	wetuwn 0;
}

static void ath9k_tx(stwuct ieee80211_hw *hw,
		     stwuct ieee80211_tx_contwow *contwow,
		     stwuct sk_buff *skb)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_tx_contwow txctw;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	unsigned wong fwags;

	if (sc->ps_enabwed) {
		/*
		 * mac80211 does not set PM fiewd fow nowmaw data fwames, so we
		 * need to update that based on the cuwwent PS mode.
		 */
		if (ieee80211_is_data(hdw->fwame_contwow) &&
		    !ieee80211_is_nuwwfunc(hdw->fwame_contwow) &&
		    !ieee80211_has_pm(hdw->fwame_contwow)) {
			ath_dbg(common, PS,
				"Add PM=1 fow a TX fwame whiwe in PS mode\n");
			hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PM);
		}
	}

	if (unwikewy(sc->sc_ah->powew_mode == ATH9K_PM_NETWOWK_SWEEP)) {
		/*
		 * We awe using PS-Poww and mac80211 can wequest TX whiwe in
		 * powew save mode. Need to wake up hawdwawe fow the TX to be
		 * compweted and if needed, awso fow WX of buffewed fwames.
		 */
		ath9k_ps_wakeup(sc);
		spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
		if (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSWEEP))
			ath9k_hw_setwxabowt(sc->sc_ah, 0);
		if (ieee80211_is_pspoww(hdw->fwame_contwow)) {
			ath_dbg(common, PS,
				"Sending PS-Poww to pick a buffewed fwame\n");
			sc->ps_fwags |= PS_WAIT_FOW_PSPOWW_DATA;
		} ewse {
			ath_dbg(common, PS, "Wake up to compwete TX\n");
			sc->ps_fwags |= PS_WAIT_FOW_TX_ACK;
		}
		/*
		 * The actuaw westowe opewation wiww happen onwy aftew
		 * the ps_fwags bit is cweawed. We awe just dwopping
		 * the ps_usecount hewe.
		 */
		spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
		ath9k_ps_westowe(sc);
	}

	/*
	 * Cannot tx whiwe the hawdwawe is in fuww sweep, it fiwst needs a fuww
	 * chip weset to wecovew fwom that
	 */
	if (unwikewy(sc->sc_ah->powew_mode == ATH9K_PM_FUWW_SWEEP)) {
		ath_eww(common, "TX whiwe HW is in FUWW_SWEEP mode\n");
		goto exit;
	}

	memset(&txctw, 0, sizeof(stwuct ath_tx_contwow));
	txctw.txq = sc->tx.txq_map[skb_get_queue_mapping(skb)];
	txctw.sta = contwow->sta;

	ath_dbg(common, XMIT, "twansmitting packet, skb: %p\n", skb);

	if (ath_tx_stawt(hw, skb, &txctw) != 0) {
		ath_dbg(common, XMIT, "TX faiwed\n");
		TX_STAT_INC(sc, txctw.txq->axq_qnum, txfaiwed);
		goto exit;
	}

	wetuwn;
exit:
	ieee80211_fwee_txskb(hw, skb);
}

static boow ath9k_txq_wist_has_key(stwuct wist_head *txq_wist, u32 keyix)
{
	stwuct ath_buf *bf;
	stwuct ieee80211_tx_info *txinfo;
	stwuct ath_fwame_info *fi;

	wist_fow_each_entwy(bf, txq_wist, wist) {
		if (bf->bf_state.stawe || !bf->bf_mpdu)
			continue;

		txinfo = IEEE80211_SKB_CB(bf->bf_mpdu);
		fi = (stwuct ath_fwame_info *)&txinfo->status.status_dwivew_data[0];
		if (fi->keyix == keyix)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow ath9k_txq_has_key(stwuct ath_softc *sc, u32 keyix)
{
	stwuct ath_hw *ah = sc->sc_ah;
	int i, j;
	stwuct ath_txq *txq;
	boow key_in_use = fawse;

	fow (i = 0; !key_in_use && i < ATH9K_NUM_TX_QUEUES; i++) {
		if (!ATH_TXQ_SETUP(sc, i))
			continue;
		txq = &sc->tx.txq[i];
		if (!txq->axq_depth)
			continue;
		if (!ath9k_hw_numtxpending(ah, txq->axq_qnum))
			continue;

		ath_txq_wock(sc, txq);
		key_in_use = ath9k_txq_wist_has_key(&txq->axq_q, keyix);
		if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
			int idx = txq->txq_taiwidx;

			fow (j = 0; !key_in_use &&
			     !wist_empty(&txq->txq_fifo[idx]) &&
			     j < ATH_TXFIFO_DEPTH; j++) {
				key_in_use = ath9k_txq_wist_has_key(
					&txq->txq_fifo[idx], keyix);
				INCW(idx, ATH_TXFIFO_DEPTH);
			}
		}
		ath_txq_unwock(sc, txq);
	}

	wetuwn key_in_use;
}

static void ath9k_pending_key_dew(stwuct ath_softc *sc, u8 keyix)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!test_bit(keyix, ah->pending_dew_keymap) ||
	    ath9k_txq_has_key(sc, keyix))
		wetuwn;

	/* No mowe TXQ fwames point to this key cache entwy, so dewete it. */
	cweaw_bit(keyix, ah->pending_dew_keymap);
	ath_key_dewete(common, keyix);
}

static void ath9k_stop(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	boow pwev_idwe;
	int i;

	ath9k_deinit_channew_context(sc);

	mutex_wock(&sc->mutex);

	ath9k_wng_stop(sc);

	ath_cancew_wowk(sc);

	if (test_bit(ATH_OP_INVAWID, &common->op_fwags)) {
		ath_dbg(common, ANY, "Device not pwesent\n");
		mutex_unwock(&sc->mutex);
		wetuwn;
	}

	/* Ensuwe HW is awake when we twy to shut it down. */
	ath9k_ps_wakeup(sc);

	spin_wock_bh(&sc->sc_pcu_wock);

	/* pwevent taskwets to enabwe intewwupts once we disabwe them */
	ah->imask &= ~ATH9K_INT_GWOBAW;

	/* make suwe h/w wiww not genewate any intewwupt
	 * befowe setting the invawid fwag. */
	ath9k_hw_disabwe_intewwupts(ah);

	spin_unwock_bh(&sc->sc_pcu_wock);

	/* we can now sync iwq and kiww any wunning taskwets, since we awweady
	 * disabwed intewwupts and not howding a spin wock */
	synchwonize_iwq(sc->iwq);
	taskwet_kiww(&sc->intw_tq);
	taskwet_kiww(&sc->bcon_taskwet);

	pwev_idwe = sc->ps_idwe;
	sc->ps_idwe = twue;

	spin_wock_bh(&sc->sc_pcu_wock);

	if (ah->wed_pin >= 0) {
		ath9k_hw_set_gpio(ah, ah->wed_pin,
				  (ah->config.wed_active_high) ? 0 : 1);
		ath9k_hw_gpio_wequest_in(ah, ah->wed_pin, NUWW);
	}

	ath_pwepawe_weset(sc);

	if (sc->wx.fwag) {
		dev_kfwee_skb_any(sc->wx.fwag);
		sc->wx.fwag = NUWW;
	}

	if (!ah->cuwchan)
		ah->cuwchan = ath9k_cmn_get_channew(hw, ah,
						    &sc->cuw_chan->chandef);

	ath9k_hw_weset(ah, ah->cuwchan, ah->cawdata, fawse);

	set_bit(ATH_OP_INVAWID, &common->op_fwags);

	ath9k_hw_phy_disabwe(ah);

	ath9k_hw_configpcipowewsave(ah, twue);

	spin_unwock_bh(&sc->sc_pcu_wock);

	fow (i = 0; i < ATH_KEYMAX; i++)
		ath9k_pending_key_dew(sc, i);

	/* Cweaw key cache entwies expwicitwy to get wid of any potentiawwy
	 * wemaining keys.
	 */
	ath9k_cmn_init_cwypto(sc->sc_ah);

	ath9k_ps_westowe(sc);

	sc->ps_idwe = pwev_idwe;

	mutex_unwock(&sc->mutex);

	ath_dbg(common, CONFIG, "Dwivew hawt\n");
}

static boow ath9k_uses_beacons(int type)
{
	switch (type) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void ath9k_vif_itew_set_beacon(stwuct ath9k_vif_itew_data *itew_data,
				      stwuct ieee80211_vif *vif)
{
	/* Use the fiwst (configuwed) intewface, but pwefewing AP intewfaces. */
	if (!itew_data->pwimawy_beacon_vif) {
		itew_data->pwimawy_beacon_vif = vif;
	} ewse {
		if (itew_data->pwimawy_beacon_vif->type != NW80211_IFTYPE_AP &&
		    vif->type == NW80211_IFTYPE_AP)
			itew_data->pwimawy_beacon_vif = vif;
	}

	itew_data->beacons = twue;
	itew_data->nbcnvifs += 1;
}

static void ath9k_vif_itew(stwuct ath9k_vif_itew_data *itew_data,
			   u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct ath_vif *avp = (stwuct ath_vif *)vif->dwv_pwiv;
	int i;

	if (itew_data->has_hw_macaddw) {
		fow (i = 0; i < ETH_AWEN; i++)
			itew_data->mask[i] &=
				~(itew_data->hw_macaddw[i] ^ mac[i]);
	} ewse {
		memcpy(itew_data->hw_macaddw, mac, ETH_AWEN);
		itew_data->has_hw_macaddw = twue;
	}

	if (!vif->bss_conf.use_showt_swot)
		itew_data->swottime = 20;

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
		itew_data->naps++;
		if (vif->bss_conf.enabwe_beacon)
			ath9k_vif_itew_set_beacon(itew_data, vif);
		bweak;
	case NW80211_IFTYPE_STATION:
		itew_data->nstations++;
		if (avp->assoc && !itew_data->pwimawy_sta)
			itew_data->pwimawy_sta = vif;
		bweak;
	case NW80211_IFTYPE_OCB:
		itew_data->nocbs++;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		itew_data->nadhocs++;
		if (vif->bss_conf.enabwe_beacon)
			ath9k_vif_itew_set_beacon(itew_data, vif);
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		itew_data->nmeshes++;
		if (vif->bss_conf.enabwe_beacon)
			ath9k_vif_itew_set_beacon(itew_data, vif);
		bweak;
	defauwt:
		bweak;
	}
}

static void ath9k_update_bssid_mask(stwuct ath_softc *sc,
				    stwuct ath_chanctx *ctx,
				    stwuct ath9k_vif_itew_data *itew_data)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp;
	int i;

	if (!ath9k_is_chanctx_enabwed())
		wetuwn;

	wist_fow_each_entwy(avp, &ctx->vifs, wist) {
		if (ctx->nvifs_assigned != 1)
			continue;

		if (!itew_data->has_hw_macaddw)
			continue;

		ethew_addw_copy(common->cuwbssid, avp->bssid);

		/* pewm_addw wiww be used as the p2p device addwess. */
		fow (i = 0; i < ETH_AWEN; i++)
			itew_data->mask[i] &=
				~(itew_data->hw_macaddw[i] ^
				  sc->hw->wiphy->pewm_addw[i]);
	}
}

/* Cawwed with sc->mutex hewd. */
void ath9k_cawcuwate_itew_data(stwuct ath_softc *sc,
			       stwuct ath_chanctx *ctx,
			       stwuct ath9k_vif_itew_data *itew_data)
{
	stwuct ath_vif *avp;

	/*
	 * The hawdwawe wiww use pwimawy station addw togethew with the
	 * BSSID mask when matching addwesses.
	 */
	memset(itew_data, 0, sizeof(*itew_data));
	eth_bwoadcast_addw(itew_data->mask);
	itew_data->swottime = 9;

	wist_fow_each_entwy(avp, &ctx->vifs, wist)
		ath9k_vif_itew(itew_data, avp->vif->addw, avp->vif);

	ath9k_update_bssid_mask(sc, ctx, itew_data);
}

static void ath9k_set_assoc_state(stwuct ath_softc *sc,
				  stwuct ieee80211_vif *vif, boow changed)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (stwuct ath_vif *)vif->dwv_pwiv;
	unsigned wong fwags;

	set_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags);

	ethew_addw_copy(common->cuwbssid, avp->bssid);
	common->cuwaid = avp->aid;
	ath9k_hw_wwite_associd(sc->sc_ah);

	if (changed) {
		common->wast_wssi = ATH_WSSI_DUMMY_MAWKEW;
		sc->sc_ah->stats.avgbwssi = ATH_WSSI_DUMMY_MAWKEW;

		spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
		sc->ps_fwags |= PS_BEACON_SYNC | PS_WAIT_FOW_BEACON;
		spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
	}

	if (ath9k_hw_mci_is_enabwed(sc->sc_ah))
		ath9k_mci_update_wwan_channews(sc, fawse);

	ath_dbg(common, CONFIG,
		"Pwimawy Station intewface: %pM, BSSID: %pM\n",
		vif->addw, common->cuwbssid);
}

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
static void ath9k_set_offchannew_state(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_vif *vif = NUWW;

	ath9k_ps_wakeup(sc);

	if (sc->offchannew.state < ATH_OFFCHANNEW_WOC_STAWT)
		vif = sc->offchannew.scan_vif;
	ewse
		vif = sc->offchannew.woc_vif;

	if (WAWN_ON(!vif))
		goto exit;

	eth_zewo_addw(common->cuwbssid);
	eth_bwoadcast_addw(common->bssidmask);
	memcpy(common->macaddw, vif->addw, ETH_AWEN);
	common->cuwaid = 0;
	ah->opmode = vif->type;
	ah->imask &= ~ATH9K_INT_SWBA;
	ah->imask &= ~ATH9K_INT_TSFOOW;
	ah->swottime = 9;

	ath_hw_setbssidmask(common);
	ath9k_hw_setopmode(ah);
	ath9k_hw_wwite_associd(sc->sc_ah);
	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_init_gwobaw_settings(ah);

exit:
	ath9k_ps_westowe(sc);
}
#endif

/* Cawwed with sc->mutex hewd. */
void ath9k_cawcuwate_summawy_state(stwuct ath_softc *sc,
				   stwuct ath_chanctx *ctx)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_vif_itew_data itew_data;

	ath_chanctx_check_active(sc, ctx);

	if (ctx != sc->cuw_chan)
		wetuwn;

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
	if (ctx == &sc->offchannew.chan)
		wetuwn ath9k_set_offchannew_state(sc);
#endif

	ath9k_ps_wakeup(sc);
	ath9k_cawcuwate_itew_data(sc, ctx, &itew_data);

	if (itew_data.has_hw_macaddw)
		memcpy(common->macaddw, itew_data.hw_macaddw, ETH_AWEN);

	memcpy(common->bssidmask, itew_data.mask, ETH_AWEN);
	ath_hw_setbssidmask(common);

	if (itew_data.naps > 0) {
		ath9k_hw_set_tsfadjust(ah, twue);
		ah->opmode = NW80211_IFTYPE_AP;
	} ewse {
		ath9k_hw_set_tsfadjust(ah, fawse);
		if (itew_data.beacons)
			ath9k_beacon_ensuwe_pwimawy_swot(sc);

		if (itew_data.nmeshes)
			ah->opmode = NW80211_IFTYPE_MESH_POINT;
		ewse if (itew_data.nocbs)
			ah->opmode = NW80211_IFTYPE_OCB;
		ewse if (itew_data.nadhocs)
			ah->opmode = NW80211_IFTYPE_ADHOC;
		ewse
			ah->opmode = NW80211_IFTYPE_STATION;
	}

	ath9k_hw_setopmode(ah);

	ctx->switch_aftew_beacon = fawse;
	if ((itew_data.nstations + itew_data.nadhocs + itew_data.nmeshes) > 0)
		ah->imask |= ATH9K_INT_TSFOOW;
	ewse {
		ah->imask &= ~ATH9K_INT_TSFOOW;
		if (itew_data.naps == 1 && itew_data.beacons)
			ctx->switch_aftew_beacon = twue;
	}

	if (ah->opmode == NW80211_IFTYPE_STATION) {
		boow changed = (itew_data.pwimawy_sta != ctx->pwimawy_sta);

		if (itew_data.pwimawy_sta) {
			itew_data.pwimawy_beacon_vif = itew_data.pwimawy_sta;
			itew_data.beacons = twue;
			ath9k_set_assoc_state(sc, itew_data.pwimawy_sta,
					      changed);
			ctx->pwimawy_sta = itew_data.pwimawy_sta;
		} ewse {
			ctx->pwimawy_sta = NUWW;
			eth_zewo_addw(common->cuwbssid);
			common->cuwaid = 0;
			ath9k_hw_wwite_associd(sc->sc_ah);
			if (ath9k_hw_mci_is_enabwed(sc->sc_ah))
				ath9k_mci_update_wwan_channews(sc, twue);
		}
	}
	sc->nbcnvifs = itew_data.nbcnvifs;
	ath9k_beacon_config(sc, itew_data.pwimawy_beacon_vif,
			    itew_data.beacons);
	ath9k_hw_set_intewwupts(ah);

	if (ah->swottime != itew_data.swottime) {
		ah->swottime = itew_data.swottime;
		ath9k_hw_init_gwobaw_settings(ah);
	}

	if (itew_data.pwimawy_sta)
		set_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags);
	ewse
		cweaw_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags);

	ath_dbg(common, CONFIG,
		"macaddw: %pM, bssid: %pM, bssidmask: %pM\n",
		common->macaddw, common->cuwbssid, common->bssidmask);

	ath9k_ps_westowe(sc);
}

static void ath9k_tpc_vif_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	int *powew = data;

	if (vif->bss_conf.txpowew == INT_MIN)
		wetuwn;

	if (*powew < vif->bss_conf.txpowew)
		*powew = vif->bss_conf.txpowew;
}

/* Cawwed with sc->mutex hewd. */
void ath9k_set_txpowew(stwuct ath_softc *sc, stwuct ieee80211_vif *vif)
{
	int powew;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_weguwatowy *weg = ath9k_hw_weguwatowy(ah);

	ath9k_ps_wakeup(sc);
	if (ah->tpc_enabwed) {
		powew = (vif) ? vif->bss_conf.txpowew : -1;
		ieee80211_itewate_active_intewfaces_atomic(
				sc->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
				ath9k_tpc_vif_itew, &powew);
		if (powew == -1)
			powew = sc->hw->conf.powew_wevew;
	} ewse {
		powew = sc->hw->conf.powew_wevew;
	}
	sc->cuw_chan->txpowew = 2 * powew;
	ath9k_hw_set_txpowewwimit(ah, sc->cuw_chan->txpowew, fawse);
	sc->cuw_chan->cuw_txpowew = weg->max_powew_wevew;
	ath9k_ps_westowe(sc);
}

static void ath9k_assign_hw_queues(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	int i;

	if (!ath9k_is_chanctx_enabwed())
		wetuwn;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++)
		vif->hw_queue[i] = i;

	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_MESH_POINT)
		vif->cab_queue = hw->queues - 2;
	ewse
		vif->cab_queue = IEEE80211_INVAW_HW_QUEUE;
}

static int ath9k_add_intewface(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	stwuct ath_node *an = &avp->mcast_node;

	mutex_wock(&sc->mutex);
	if (IS_ENABWED(CONFIG_ATH9K_TX99)) {
		if (sc->cuw_chan->nvifs >= 1) {
			mutex_unwock(&sc->mutex);
			wetuwn -EOPNOTSUPP;
		}
		sc->tx99_vif = vif;
	}

	ath_dbg(common, CONFIG, "Attach a VIF of type: %d\n", vif->type);
	sc->cuw_chan->nvifs++;

	if (vif->type == NW80211_IFTYPE_STATION && ath9k_is_chanctx_enabwed())
		vif->dwivew_fwags |= IEEE80211_VIF_GET_NOA_UPDATE;

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_assign_swot(sc, vif);

	avp->vif = vif;
	if (!ath9k_is_chanctx_enabwed()) {
		avp->chanctx = sc->cuw_chan;
		wist_add_taiw(&avp->wist, &avp->chanctx->vifs);
	}

	ath9k_cawcuwate_summawy_state(sc, avp->chanctx);

	ath9k_assign_hw_queues(hw, vif);

	ath9k_set_txpowew(sc, vif);

	an->sc = sc;
	an->sta = NUWW;
	an->vif = vif;
	an->no_ps_fiwtew = twue;
	ath_tx_node_init(sc, an);

	mutex_unwock(&sc->mutex);
	wetuwn 0;
}

static int ath9k_change_intewface(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  enum nw80211_iftype new_type,
				  boow p2p)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;

	mutex_wock(&sc->mutex);

	if (IS_ENABWED(CONFIG_ATH9K_TX99)) {
		mutex_unwock(&sc->mutex);
		wetuwn -EOPNOTSUPP;
	}

	ath_dbg(common, CONFIG, "Change Intewface\n");

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_wemove_swot(sc, vif);

	vif->type = new_type;
	vif->p2p = p2p;

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_assign_swot(sc, vif);

	ath9k_assign_hw_queues(hw, vif);
	ath9k_cawcuwate_summawy_state(sc, avp->chanctx);

	ath9k_set_txpowew(sc, vif);

	mutex_unwock(&sc->mutex);
	wetuwn 0;
}

static void ath9k_wemove_intewface(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;

	ath_dbg(common, CONFIG, "Detach Intewface\n");

	mutex_wock(&sc->mutex);

	ath9k_p2p_wemove_vif(sc, vif);

	sc->cuw_chan->nvifs--;
	sc->tx99_vif = NUWW;
	if (!ath9k_is_chanctx_enabwed())
		wist_dew(&avp->wist);

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_wemove_swot(sc, vif);

	ath_tx_node_cweanup(sc, &avp->mcast_node);

	ath9k_cawcuwate_summawy_state(sc, avp->chanctx);

	ath9k_set_txpowew(sc, NUWW);

	mutex_unwock(&sc->mutex);
}

static void ath9k_enabwe_ps(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn;

	sc->ps_enabwed = twue;
	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSWEEP)) {
		if ((ah->imask & ATH9K_INT_TIM_TIMEW) == 0) {
			ah->imask |= ATH9K_INT_TIM_TIMEW;
			ath9k_hw_set_intewwupts(ah);
		}
		ath9k_hw_setwxabowt(ah, 1);
	}
	ath_dbg(common, PS, "PowewSave enabwed\n");
}

static void ath9k_disabwe_ps(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn;

	sc->ps_enabwed = fawse;
	ath9k_hw_setpowew(ah, ATH9K_PM_AWAKE);
	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSWEEP)) {
		ath9k_hw_setwxabowt(ah, 0);
		sc->ps_fwags &= ~(PS_WAIT_FOW_BEACON |
				  PS_WAIT_FOW_CAB |
				  PS_WAIT_FOW_PSPOWW_DATA |
				  PS_WAIT_FOW_TX_ACK);
		if (ah->imask & ATH9K_INT_TIM_TIMEW) {
			ah->imask &= ~ATH9K_INT_TIM_TIMEW;
			ath9k_hw_set_intewwupts(ah);
		}
	}
	ath_dbg(common, PS, "PowewSave disabwed\n");
}

static int ath9k_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ath_chanctx *ctx = sc->cuw_chan;

	ath9k_ps_wakeup(sc);
	mutex_wock(&sc->mutex);

	if (changed & IEEE80211_CONF_CHANGE_IDWE) {
		sc->ps_idwe = !!(conf->fwags & IEEE80211_CONF_IDWE);
		if (sc->ps_idwe) {
			ath_cancew_wowk(sc);
			ath9k_stop_btcoex(sc);
		} ewse {
			ath9k_stawt_btcoex(sc);
			/*
			 * The chip needs a weset to pwopewwy wake up fwom
			 * fuww sweep
			 */
			ath_chanctx_set_channew(sc, ctx, &ctx->chandef);
		}
	}

	/*
	 * We just pwepawe to enabwe PS. We have to wait untiw ouw AP has
	 * ACK'd ouw nuww data fwame to disabwe WX othewwise we'ww ignowe
	 * those ACKs and end up wetwansmitting the same nuww data fwames.
	 * IEEE80211_CONF_CHANGE_PS is onwy passed by mac80211 fow STA mode.
	 */
	if (changed & IEEE80211_CONF_CHANGE_PS) {
		unsigned wong fwags;
		spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
		if (conf->fwags & IEEE80211_CONF_PS)
			ath9k_enabwe_ps(sc);
		ewse
			ath9k_disabwe_ps(sc);
		spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
	}

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		if (conf->fwags & IEEE80211_CONF_MONITOW) {
			ath_dbg(common, CONFIG, "Monitow mode is enabwed\n");
			sc->sc_ah->is_monitowing = twue;
		} ewse {
			ath_dbg(common, CONFIG, "Monitow mode is disabwed\n");
			sc->sc_ah->is_monitowing = fawse;
		}
	}

	if (!ath9k_is_chanctx_enabwed() && (changed & IEEE80211_CONF_CHANGE_CHANNEW)) {
		ctx->offchannew = !!(conf->fwags & IEEE80211_CONF_OFFCHANNEW);
		ath_chanctx_set_channew(sc, ctx, &hw->conf.chandef);
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW)
		ath9k_set_txpowew(sc, NUWW);

	mutex_unwock(&sc->mutex);
	ath9k_ps_westowe(sc);

	wetuwn 0;
}

#define SUPPOWTED_FIWTEWS			\
	(FIF_AWWMUWTI |				\
	FIF_CONTWOW |				\
	FIF_PSPOWW |				\
	FIF_OTHEW_BSS |				\
	FIF_BCN_PWBWESP_PWOMISC |		\
	FIF_PWOBE_WEQ |				\
	FIF_MCAST_ACTION |			\
	FIF_FCSFAIW)

/* FIXME: sc->sc_fuww_weset ? */
static void ath9k_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				   unsigned int changed_fwags,
				   unsigned int *totaw_fwags,
				   u64 muwticast)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_chanctx *ctx;
	u32 wfiwt;

	*totaw_fwags &= SUPPOWTED_FIWTEWS;

	spin_wock_bh(&sc->chan_wock);
	ath_fow_each_chanctx(sc, ctx)
		ctx->wxfiwtew = *totaw_fwags;
#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
	sc->offchannew.chan.wxfiwtew = *totaw_fwags;
#endif
	spin_unwock_bh(&sc->chan_wock);

	ath9k_ps_wakeup(sc);
	wfiwt = ath_cawcwxfiwtew(sc);
	ath9k_hw_setwxfiwtew(sc->sc_ah, wfiwt);
	ath9k_ps_westowe(sc);

	ath_dbg(ath9k_hw_common(sc->sc_ah), CONFIG, "Set HW WX fiwtew: 0x%x\n",
		wfiwt);
}

static int ath9k_sta_add(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_node *an = (stwuct ath_node *) sta->dwv_pwiv;
	stwuct ieee80211_key_conf ps_key = { };
	int key;

	ath_node_attach(sc, sta, vif);

	if (vif->type != NW80211_IFTYPE_AP &&
	    vif->type != NW80211_IFTYPE_AP_VWAN)
		wetuwn 0;

	key = ath_key_config(common, vif, sta, &ps_key);
	if (key > 0) {
		an->ps_key = key;
		an->key_idx[0] = key;
	}

	wetuwn 0;
}

static void ath9k_dew_ps_key(stwuct ath_softc *sc,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_node *an = (stwuct ath_node *) sta->dwv_pwiv;

	if (!an->ps_key)
	    wetuwn;

	ath_key_dewete(common, an->ps_key);
	an->ps_key = 0;
	an->key_idx[0] = 0;
}

static int ath9k_sta_wemove(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta)
{
	stwuct ath_softc *sc = hw->pwiv;

	ath9k_dew_ps_key(sc, vif, sta);
	ath_node_detach(sc, sta);

	wetuwn 0;
}

static int ath9k_sta_state(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta,
			   enum ieee80211_sta_state owd_state,
			   enum ieee80211_sta_state new_state)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int wet = 0;

	if (owd_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		wet = ath9k_sta_add(hw, vif, sta);
		ath_dbg(common, CONFIG,
			"Add station: %pM\n", sta->addw);
	} ewse if (owd_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) {
		wet = ath9k_sta_wemove(hw, vif, sta);
		ath_dbg(common, CONFIG,
			"Wemove station: %pM\n", sta->addw);
	}

	if (ath9k_is_chanctx_enabwed()) {
		if (vif->type == NW80211_IFTYPE_STATION) {
			if (owd_state == IEEE80211_STA_ASSOC &&
			    new_state == IEEE80211_STA_AUTHOWIZED)
				ath_chanctx_event(sc, vif,
						  ATH_CHANCTX_EVENT_AUTHOWIZED);
		}
	}

	wetuwn wet;
}

static void ath9k_sta_set_tx_fiwtew(stwuct ath_hw *ah,
				    stwuct ath_node *an,
				    boow set)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(an->key_idx); i++) {
		if (!an->key_idx[i])
			continue;
		ath9k_hw_set_tx_fiwtew(ah, an->key_idx[i], set);
	}
}

static void ath9k_sta_notify(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 enum sta_notify_cmd cmd,
			 stwuct ieee80211_sta *sta)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_node *an = (stwuct ath_node *) sta->dwv_pwiv;

	switch (cmd) {
	case STA_NOTIFY_SWEEP:
		an->sweeping = twue;
		ath_tx_aggw_sweep(sta, sc, an);
		ath9k_sta_set_tx_fiwtew(sc->sc_ah, an, twue);
		bweak;
	case STA_NOTIFY_AWAKE:
		ath9k_sta_set_tx_fiwtew(sc->sc_ah, an, fawse);
		an->sweeping = fawse;
		ath_tx_aggw_wakeup(sc, an);
		bweak;
	}
}

static int ath9k_conf_tx(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 unsigned int wink_id, u16 queue,
			 const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_txq *txq;
	stwuct ath9k_tx_queue_info qi;
	int wet = 0;

	if (queue >= IEEE80211_NUM_ACS)
		wetuwn 0;

	txq = sc->tx.txq_map[queue];

	ath9k_ps_wakeup(sc);
	mutex_wock(&sc->mutex);

	memset(&qi, 0, sizeof(stwuct ath9k_tx_queue_info));

	qi.tqi_aifs = pawams->aifs;
	qi.tqi_cwmin = pawams->cw_min;
	qi.tqi_cwmax = pawams->cw_max;
	qi.tqi_buwstTime = pawams->txop * 32;

	ath_dbg(common, CONFIG,
		"Configuwe tx [queue/hawq] [%d/%d], aifs: %d, cw_min: %d, cw_max: %d, txop: %d\n",
		queue, txq->axq_qnum, pawams->aifs, pawams->cw_min,
		pawams->cw_max, pawams->txop);

	ath_update_max_aggw_fwamewen(sc, queue, qi.tqi_buwstTime);
	wet = ath_txq_update(sc, txq->axq_qnum, &qi);
	if (wet)
		ath_eww(common, "TXQ Update faiwed\n");

	mutex_unwock(&sc->mutex);
	ath9k_ps_westowe(sc);

	wetuwn wet;
}

static int ath9k_set_key(stwuct ieee80211_hw *hw,
			 enum set_key_cmd cmd,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta,
			 stwuct ieee80211_key_conf *key)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_node *an = NUWW;
	int wet = 0, i;

	if (ath9k_modpawam_nohwcwypt)
		wetuwn -ENOSPC;

	if ((vif->type == NW80211_IFTYPE_ADHOC ||
	     vif->type == NW80211_IFTYPE_MESH_POINT) &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_TKIP ||
	     key->ciphew == WWAN_CIPHEW_SUITE_CCMP) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		/*
		 * Fow now, disabwe hw cwypto fow the WSN IBSS gwoup keys. This
		 * couwd be optimized in the futuwe to use a modified key cache
		 * design to suppowt pew-STA WX GTK, but untiw that gets
		 * impwemented, use of softwawe cwypto fow gwoup addwessed
		 * fwames is a acceptabwe to awwow WSN IBSS to be used.
		 */
		wetuwn -EOPNOTSUPP;
	}

	/* Thewe may be MPDUs queued fow the outgoing PTK key. Fwush queues to
	 * make suwe these awe not send unencwypted ow with a wwong (new) key
	 */
	if (cmd == DISABWE_KEY && key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
		ieee80211_stop_queues(hw);
		ath9k_fwush(hw, vif, 0, twue);
		ieee80211_wake_queues(hw);
	}

	mutex_wock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	ath_dbg(common, CONFIG, "Set HW Key %d\n", cmd);
	if (sta)
		an = (stwuct ath_node *)sta->dwv_pwiv;

	/* Dewete pending key cache entwies if no mowe fwames awe pointing to
	 * them in TXQs.
	 */
	fow (i = 0; i < ATH_KEYMAX; i++)
		ath9k_pending_key_dew(sc, i);

	switch (cmd) {
	case SET_KEY:
		if (sta)
			ath9k_dew_ps_key(sc, vif, sta);

		key->hw_key_idx = 0;
		wet = ath_key_config(common, vif, sta, key);
		if (wet >= 0) {
			key->hw_key_idx = wet;
			/* push IV and Michaew MIC genewation to stack */
			key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
			if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
				key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
			if (sc->sc_ah->sw_mgmt_cwypto_tx &&
			    key->ciphew == WWAN_CIPHEW_SUITE_CCMP)
				key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
			wet = 0;
		}
		if (an && key->hw_key_idx) {
			fow (i = 0; i < AWWAY_SIZE(an->key_idx); i++) {
				if (an->key_idx[i])
					continue;
				an->key_idx[i] = key->hw_key_idx;
				bweak;
			}
			WAWN_ON(i == AWWAY_SIZE(an->key_idx));
		}
		bweak;
	case DISABWE_KEY:
		if (ath9k_txq_has_key(sc, key->hw_key_idx)) {
			/* Deway key cache entwy dewetion untiw thewe awe no
			 * wemaining TXQ fwames pointing to this entwy.
			 */
			set_bit(key->hw_key_idx, sc->sc_ah->pending_dew_keymap);
			ath_hw_keysetmac(common, key->hw_key_idx, NUWW);
		} ewse {
			ath_key_dewete(common, key->hw_key_idx);
		}
		if (an) {
			fow (i = 0; i < AWWAY_SIZE(an->key_idx); i++) {
				if (an->key_idx[i] != key->hw_key_idx)
					continue;
				an->key_idx[i] = 0;
				bweak;
			}
		}
		key->hw_key_idx = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	ath9k_ps_westowe(sc);
	mutex_unwock(&sc->mutex);

	wetuwn wet;
}

static void ath9k_bss_info_changed(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_bss_conf *bss_conf,
				   u64 changed)
{
#define CHECK_ANI				\
	(BSS_CHANGED_ASSOC |			\
	 BSS_CHANGED_IBSS |			\
	 BSS_CHANGED_BEACON_ENABWED)

	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	int swottime;

	ath9k_ps_wakeup(sc);
	mutex_wock(&sc->mutex);

	if (changed & BSS_CHANGED_ASSOC) {
		ath_dbg(common, CONFIG, "BSSID %pM Changed ASSOC %d\n",
			bss_conf->bssid, vif->cfg.assoc);

		memcpy(avp->bssid, bss_conf->bssid, ETH_AWEN);
		avp->aid = vif->cfg.aid;
		avp->assoc = vif->cfg.assoc;

		ath9k_cawcuwate_summawy_state(sc, avp->chanctx);
	}

	if ((changed & BSS_CHANGED_IBSS) ||
	      (changed & BSS_CHANGED_OCB)) {
		memcpy(common->cuwbssid, bss_conf->bssid, ETH_AWEN);
		common->cuwaid = vif->cfg.aid;
		ath9k_hw_wwite_associd(sc->sc_ah);
	}

	if ((changed & BSS_CHANGED_BEACON_ENABWED) ||
	    (changed & BSS_CHANGED_BEACON_INT) ||
	    (changed & BSS_CHANGED_BEACON_INFO)) {
		ath9k_cawcuwate_summawy_state(sc, avp->chanctx);
	}

	if ((avp->chanctx == sc->cuw_chan) &&
	    (changed & BSS_CHANGED_EWP_SWOT)) {
		if (bss_conf->use_showt_swot)
			swottime = 9;
		ewse
			swottime = 20;

		if (vif->type == NW80211_IFTYPE_AP) {
			/*
			 * Defew update, so that connected stations can adjust
			 * theiw settings at the same time.
			 * See beacon.c fow mowe detaiws
			 */
			sc->beacon.swottime = swottime;
			sc->beacon.updateswot = UPDATE;
		} ewse {
			ah->swottime = swottime;
			ath9k_hw_init_gwobaw_settings(ah);
		}
	}

	if (changed & BSS_CHANGED_P2P_PS)
		ath9k_p2p_bss_info_changed(sc, vif);

	if (changed & CHECK_ANI)
		ath_check_ani(sc);

	if (changed & BSS_CHANGED_TXPOWEW) {
		ath_dbg(common, CONFIG, "vif %pM powew %d dbm powew_type %d\n",
			vif->addw, bss_conf->txpowew, bss_conf->txpowew_type);
		ath9k_set_txpowew(sc, vif);
	}

	mutex_unwock(&sc->mutex);
	ath9k_ps_westowe(sc);

#undef CHECK_ANI
}

static u64 ath9k_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	u64 tsf;

	mutex_wock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	/* Get cuwwent TSF eithew fwom HW ow kewnew time. */
	if (sc->cuw_chan == avp->chanctx) {
		tsf = ath9k_hw_gettsf64(sc->sc_ah);
	} ewse {
		tsf = sc->cuw_chan->tsf_vaw +
		      ath9k_hw_get_tsf_offset(&sc->cuw_chan->tsf_ts, NUWW);
	}
	tsf += we64_to_cpu(avp->tsf_adjust);
	ath9k_ps_westowe(sc);
	mutex_unwock(&sc->mutex);

	wetuwn tsf;
}

static void ath9k_set_tsf(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif,
			  u64 tsf)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;

	mutex_wock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	tsf -= we64_to_cpu(avp->tsf_adjust);
	ktime_get_waw_ts64(&avp->chanctx->tsf_ts);
	if (sc->cuw_chan == avp->chanctx)
		ath9k_hw_settsf64(sc->sc_ah, tsf);
	avp->chanctx->tsf_vaw = tsf;
	ath9k_ps_westowe(sc);
	mutex_unwock(&sc->mutex);
}

static void ath9k_weset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;

	mutex_wock(&sc->mutex);

	ath9k_ps_wakeup(sc);
	ktime_get_waw_ts64(&avp->chanctx->tsf_ts);
	if (sc->cuw_chan == avp->chanctx)
		ath9k_hw_weset_tsf(sc->sc_ah);
	avp->chanctx->tsf_vaw = 0;
	ath9k_ps_westowe(sc);

	mutex_unwock(&sc->mutex);
}

static int ath9k_ampdu_action(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	boow fwush = fawse;
	int wet = 0;
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	stwuct ath_atx_tid *atid;

	mutex_wock(&sc->mutex);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		if (ath9k_is_chanctx_enabwed()) {
			if (test_bit(ATH_OP_SCANNING, &common->op_fwags)) {
				wet = -EBUSY;
				bweak;
			}
		}
		ath9k_ps_wakeup(sc);
		wet = ath_tx_aggw_stawt(sc, sta, tid, ssn);
		if (!wet)
			wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		ath9k_ps_westowe(sc);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		fwush = twue;
		fawwthwough;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		ath9k_ps_wakeup(sc);
		ath_tx_aggw_stop(sc, sta, tid);
		if (!fwush)
			ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		ath9k_ps_westowe(sc);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		atid = ath_node_to_tid(an, tid);
		atid->baw_size = IEEE80211_MIN_AMPDU_BUF <<
					sta->defwink.ht_cap.ampdu_factow;
		bweak;
	defauwt:
		ath_eww(ath9k_hw_common(sc->sc_ah), "Unknown AMPDU action\n");
	}

	mutex_unwock(&sc->mutex);

	wetuwn wet;
}

static int ath9k_get_suwvey(stwuct ieee80211_hw *hw, int idx,
			     stwuct suwvey_info *suwvey)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *chan;
	unsigned wong fwags;
	int pos;

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn -EOPNOTSUPP;

	spin_wock_iwqsave(&common->cc_wock, fwags);
	if (idx == 0)
		ath_update_suwvey_stats(sc);

	sband = hw->wiphy->bands[NW80211_BAND_2GHZ];
	if (sband && idx >= sband->n_channews) {
		idx -= sband->n_channews;
		sband = NUWW;
	}

	if (!sband)
		sband = hw->wiphy->bands[NW80211_BAND_5GHZ];

	if (!sband || idx >= sband->n_channews) {
		spin_unwock_iwqwestowe(&common->cc_wock, fwags);
		wetuwn -ENOENT;
	}

	chan = &sband->channews[idx];
	pos = chan->hw_vawue;
	memcpy(suwvey, &sc->suwvey[pos], sizeof(*suwvey));
	suwvey->channew = chan;
	spin_unwock_iwqwestowe(&common->cc_wock, fwags);

	wetuwn 0;
}

static void ath9k_enabwe_dynack(stwuct ath_softc *sc)
{
#ifdef CONFIG_ATH9K_DYNACK
	u32 wfiwt;
	stwuct ath_hw *ah = sc->sc_ah;

	ath_dynack_weset(ah);

	ah->dynack.enabwed = twue;
	wfiwt = ath_cawcwxfiwtew(sc);
	ath9k_hw_setwxfiwtew(ah, wfiwt);
#endif
}

static void ath9k_set_covewage_cwass(stwuct ieee80211_hw *hw,
				     s16 covewage_cwass)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn;

	mutex_wock(&sc->mutex);

	if (covewage_cwass >= 0) {
		ah->covewage_cwass = covewage_cwass;
		if (ah->dynack.enabwed) {
			u32 wfiwt;

			ah->dynack.enabwed = fawse;
			wfiwt = ath_cawcwxfiwtew(sc);
			ath9k_hw_setwxfiwtew(ah, wfiwt);
		}
		ath9k_ps_wakeup(sc);
		ath9k_hw_init_gwobaw_settings(ah);
		ath9k_ps_westowe(sc);
	} ewse if (!ah->dynack.enabwed) {
		ath9k_enabwe_dynack(sc);
	}

	mutex_unwock(&sc->mutex);
}

static boow ath9k_has_tx_pending(stwuct ath_softc *sc,
				 boow sw_pending)
{
	int i, npend = 0;

	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (!ATH_TXQ_SETUP(sc, i))
			continue;

		npend = ath9k_has_pending_fwames(sc, &sc->tx.txq[i],
						 sw_pending);
		if (npend)
			bweak;
	}

	wetuwn !!npend;
}

static void ath9k_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			u32 queues, boow dwop)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (ath9k_is_chanctx_enabwed()) {
		if (!test_bit(ATH_OP_MUWTI_CHANNEW, &common->op_fwags))
			goto fwush;

		/*
		 * If MCC is active, extend the fwush timeout
		 * and wait fow the HW/SW queues to become
		 * empty. This needs to be done outside the
		 * sc->mutex wock to awwow the channew scheduwew
		 * to switch channew contexts.
		 *
		 * The vif queues have been stopped in mac80211,
		 * so thewe won't be any incoming fwames.
		 */
		__ath9k_fwush(hw, queues, dwop, twue, twue);
		wetuwn;
	}
fwush:
	mutex_wock(&sc->mutex);
	__ath9k_fwush(hw, queues, dwop, twue, fawse);
	mutex_unwock(&sc->mutex);
}

void __ath9k_fwush(stwuct ieee80211_hw *hw, u32 queues, boow dwop,
		   boow sw_pending, boow timeout_ovewwide)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int timeout;
	boow dwain_txq;

	cancew_dewayed_wowk_sync(&sc->hw_check_wowk);

	if (ah->ah_fwags & AH_UNPWUGGED) {
		ath_dbg(common, ANY, "Device has been unpwugged!\n");
		wetuwn;
	}

	if (test_bit(ATH_OP_INVAWID, &common->op_fwags)) {
		ath_dbg(common, ANY, "Device not pwesent\n");
		wetuwn;
	}

	spin_wock_bh(&sc->chan_wock);
	if (timeout_ovewwide)
		timeout = HZ / 5;
	ewse
		timeout = sc->cuw_chan->fwush_timeout;
	spin_unwock_bh(&sc->chan_wock);

	ath_dbg(common, CHAN_CTX,
		"Fwush timeout: %d\n", jiffies_to_msecs(timeout));

	if (wait_event_timeout(sc->tx_wait, !ath9k_has_tx_pending(sc, sw_pending),
			       timeout) > 0)
		dwop = fawse;

	if (dwop) {
		ath9k_ps_wakeup(sc);
		spin_wock_bh(&sc->sc_pcu_wock);
		dwain_txq = ath_dwain_aww_txq(sc);
		spin_unwock_bh(&sc->sc_pcu_wock);

		if (!dwain_txq)
			ath_weset(sc, NUWW);

		ath9k_ps_westowe(sc);
	}

	ieee80211_queue_dewayed_wowk(hw, &sc->hw_check_wowk,
				     msecs_to_jiffies(ATH_HW_CHECK_POWW_INT));
}

static boow ath9k_tx_fwames_pending(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;

	wetuwn ath9k_has_tx_pending(sc, twue);
}

static int ath9k_tx_wast_beacon(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ieee80211_vif *vif;
	stwuct ath_vif *avp;
	stwuct ath_buf *bf;
	stwuct ath_tx_status ts;
	boow edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	int status;

	vif = sc->beacon.bswot[0];
	if (!vif)
		wetuwn 0;

	if (!vif->bss_conf.enabwe_beacon)
		wetuwn 0;

	avp = (void *)vif->dwv_pwiv;

	if (!sc->beacon.tx_pwocessed && !edma) {
		taskwet_disabwe(&sc->bcon_taskwet);

		bf = avp->av_bcbuf;
		if (!bf || !bf->bf_mpdu)
			goto skip;

		status = ath9k_hw_txpwocdesc(ah, bf->bf_desc, &ts);
		if (status == -EINPWOGWESS)
			goto skip;

		sc->beacon.tx_pwocessed = twue;
		sc->beacon.tx_wast = !(ts.ts_status & ATH9K_TXEWW_MASK);

skip:
		taskwet_enabwe(&sc->bcon_taskwet);
	}

	wetuwn sc->beacon.tx_wast;
}

static int ath9k_get_stats(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_mib_stats *mib_stats = &ah->ah_mibStats;

	stats->dot11ACKFaiwuweCount = mib_stats->ackwcv_bad;
	stats->dot11WTSFaiwuweCount = mib_stats->wts_bad;
	stats->dot11FCSEwwowCount = mib_stats->fcs_bad;
	stats->dot11WTSSuccessCount = mib_stats->wts_good;
	wetuwn 0;
}

static u32 fiww_chainmask(u32 cap, u32 new)
{
	u32 fiwwed = 0;
	int i;

	fow (i = 0; cap && new; i++, cap >>= 1) {
		if (!(cap & BIT(0)))
			continue;

		if (new & BIT(0))
			fiwwed |= BIT(i);

		new >>= 1;
	}

	wetuwn fiwwed;
}

static boow vawidate_antenna_mask(stwuct ath_hw *ah, u32 vaw)
{
	if (AW_SWEV_9300_20_OW_WATEW(ah))
		wetuwn twue;

	switch (vaw & 0x7) {
	case 0x1:
	case 0x3:
	case 0x7:
		wetuwn twue;
	case 0x2:
		wetuwn (ah->caps.wx_chainmask == 1);
	defauwt:
		wetuwn fawse;
	}
}

static int ath9k_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;

	if (ah->caps.wx_chainmask != 1)
		wx_ant |= tx_ant;

	if (!vawidate_antenna_mask(ah, wx_ant) || !tx_ant)
		wetuwn -EINVAW;

	sc->ant_wx = wx_ant;
	sc->ant_tx = tx_ant;

	if (ah->caps.wx_chainmask == 1)
		wetuwn 0;

	/* AW9100 wuns into cawibwation issues if not aww wx chains awe enabwed */
	if (AW_SWEV_9100(ah))
		ah->wxchainmask = 0x7;
	ewse
		ah->wxchainmask = fiww_chainmask(ah->caps.wx_chainmask, wx_ant);

	ah->txchainmask = fiww_chainmask(ah->caps.tx_chainmask, tx_ant);
	ath9k_cmn_wewoad_chainmask(ah);

	wetuwn 0;
}

static int ath9k_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant)
{
	stwuct ath_softc *sc = hw->pwiv;

	*tx_ant = sc->ant_tx;
	*wx_ant = sc->ant_wx;
	wetuwn 0;
}

static void ath9k_sw_scan_stawt(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				const u8 *mac_addw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct cfg80211_chan_def *chandef = &sc->cuw_chan->chandef;
	stwuct ieee80211_channew *chan = chandef->chan;
	int pos = chan->hw_vawue;
	set_bit(ATH_OP_SCANNING, &common->op_fwags);

	/* Weset cuwwent suwvey */
	if (!sc->cuw_chan->offchannew) {
		if (sc->cuw_suwvey != &sc->suwvey[pos]) {
			if (sc->cuw_suwvey)
				sc->cuw_suwvey->fiwwed &= ~SUWVEY_INFO_IN_USE;
			sc->cuw_suwvey = &sc->suwvey[pos];
		}

		memset(sc->cuw_suwvey, 0, sizeof(stwuct suwvey_info));
		sc->cuw_suwvey->fiwwed |= SUWVEY_INFO_IN_USE;
	}
}

static void ath9k_sw_scan_compwete(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	cweaw_bit(ATH_OP_SCANNING, &common->op_fwags);
}

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT

static void ath9k_cancew_pending_offchannew(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (sc->offchannew.woc_vif) {
		ath_dbg(common, CHAN_CTX,
			"%s: Abowting WoC\n", __func__);

		dew_timew_sync(&sc->offchannew.timew);
		if (sc->offchannew.state >= ATH_OFFCHANNEW_WOC_STAWT)
			ath_woc_compwete(sc, ATH_WOC_COMPWETE_ABOWT);
	}

	if (test_bit(ATH_OP_SCANNING, &common->op_fwags)) {
		ath_dbg(common, CHAN_CTX,
			"%s: Abowting HW scan\n", __func__);

		dew_timew_sync(&sc->offchannew.timew);
		ath_scan_compwete(sc, twue);
	}
}

static int ath9k_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct cfg80211_scan_wequest *weq = &hw_weq->weq;
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int wet = 0;

	mutex_wock(&sc->mutex);

	if (WAWN_ON(sc->offchannew.scan_weq)) {
		wet = -EBUSY;
		goto out;
	}

	ath9k_ps_wakeup(sc);
	set_bit(ATH_OP_SCANNING, &common->op_fwags);
	sc->offchannew.scan_vif = vif;
	sc->offchannew.scan_weq = weq;
	sc->offchannew.scan_idx = 0;

	ath_dbg(common, CHAN_CTX, "HW scan wequest weceived on vif: %pM\n",
		vif->addw);

	if (sc->offchannew.state == ATH_OFFCHANNEW_IDWE) {
		ath_dbg(common, CHAN_CTX, "Stawting HW scan\n");
		ath_offchannew_next(sc);
	}

out:
	mutex_unwock(&sc->mutex);

	wetuwn wet;
}

static void ath9k_cancew_hw_scan(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CHAN_CTX, "Cancew HW scan on vif: %pM\n", vif->addw);

	mutex_wock(&sc->mutex);
	dew_timew_sync(&sc->offchannew.timew);
	ath_scan_compwete(sc, twue);
	mutex_unwock(&sc->mutex);
}

static int ath9k_wemain_on_channew(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_channew *chan, int duwation,
				   enum ieee80211_woc_type type)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int wet = 0;

	mutex_wock(&sc->mutex);

	if (WAWN_ON(sc->offchannew.woc_vif)) {
		wet = -EBUSY;
		goto out;
	}

	ath9k_ps_wakeup(sc);
	sc->offchannew.woc_vif = vif;
	sc->offchannew.woc_chan = chan;
	sc->offchannew.woc_duwation = duwation;

	ath_dbg(common, CHAN_CTX,
		"WoC wequest on vif: %pM, type: %d duwation: %d\n",
		vif->addw, type, duwation);

	if (sc->offchannew.state == ATH_OFFCHANNEW_IDWE) {
		ath_dbg(common, CHAN_CTX, "Stawting WoC pewiod\n");
		ath_offchannew_next(sc);
	}

out:
	mutex_unwock(&sc->mutex);

	wetuwn wet;
}

static int ath9k_cancew_wemain_on_channew(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	mutex_wock(&sc->mutex);

	ath_dbg(common, CHAN_CTX, "Cancew WoC\n");
	dew_timew_sync(&sc->offchannew.timew);

	if (sc->offchannew.woc_vif) {
		if (sc->offchannew.state >= ATH_OFFCHANNEW_WOC_STAWT)
			ath_woc_compwete(sc, ATH_WOC_COMPWETE_CANCEW);
	}

	mutex_unwock(&sc->mutex);

	wetuwn 0;
}

static int ath9k_add_chanctx(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_chanctx_conf *conf)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_chanctx *ctx, **ptw;
	int pos;

	mutex_wock(&sc->mutex);

	ath_fow_each_chanctx(sc, ctx) {
		if (ctx->assigned)
			continue;

		ptw = (void *) conf->dwv_pwiv;
		*ptw = ctx;
		ctx->assigned = twue;
		pos = ctx - &sc->chanctx[0];
		ctx->hw_queue_base = pos * IEEE80211_NUM_ACS;

		ath_dbg(common, CHAN_CTX,
			"Add channew context: %d MHz\n",
			conf->def.chan->centew_fweq);

		ath_chanctx_set_channew(sc, ctx, &conf->def);

		mutex_unwock(&sc->mutex);
		wetuwn 0;
	}

	mutex_unwock(&sc->mutex);
	wetuwn -ENOSPC;
}


static void ath9k_wemove_chanctx(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_chanctx_conf *conf)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_chanctx *ctx = ath_chanctx_get(conf);

	mutex_wock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Wemove channew context: %d MHz\n",
		conf->def.chan->centew_fweq);

	ctx->assigned = fawse;
	ctx->hw_queue_base = 0;
	ath_chanctx_event(sc, NUWW, ATH_CHANCTX_EVENT_UNASSIGN);

	mutex_unwock(&sc->mutex);
}

static void ath9k_change_chanctx(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_chanctx_conf *conf,
				 u32 changed)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_chanctx *ctx = ath_chanctx_get(conf);

	mutex_wock(&sc->mutex);
	ath_dbg(common, CHAN_CTX,
		"Change channew context: %d MHz\n",
		conf->def.chan->centew_fweq);
	ath_chanctx_set_channew(sc, ctx, &conf->def);
	mutex_unwock(&sc->mutex);
}

static int ath9k_assign_vif_chanctx(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *wink_conf,
				    stwuct ieee80211_chanctx_conf *conf)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	stwuct ath_chanctx *ctx = ath_chanctx_get(conf);
	int i;

	ath9k_cancew_pending_offchannew(sc);

	mutex_wock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Assign VIF (addw: %pM, type: %d, p2p: %d) to channew context: %d MHz\n",
		vif->addw, vif->type, vif->p2p,
		conf->def.chan->centew_fweq);

	avp->chanctx = ctx;
	ctx->nvifs_assigned++;
	wist_add_taiw(&avp->wist, &ctx->vifs);
	ath9k_cawcuwate_summawy_state(sc, ctx);
	fow (i = 0; i < IEEE80211_NUM_ACS; i++)
		vif->hw_queue[i] = ctx->hw_queue_base + i;

	mutex_unwock(&sc->mutex);

	wetuwn 0;
}

static void ath9k_unassign_vif_chanctx(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_bss_conf *wink_conf,
				       stwuct ieee80211_chanctx_conf *conf)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	stwuct ath_chanctx *ctx = ath_chanctx_get(conf);
	int ac;

	ath9k_cancew_pending_offchannew(sc);

	mutex_wock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Wemove VIF (addw: %pM, type: %d, p2p: %d) fwom channew context: %d MHz\n",
		vif->addw, vif->type, vif->p2p,
		conf->def.chan->centew_fweq);

	avp->chanctx = NUWW;
	ctx->nvifs_assigned--;
	wist_dew(&avp->wist);
	ath9k_cawcuwate_summawy_state(sc, ctx);
	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		vif->hw_queue[ac] = IEEE80211_INVAW_HW_QUEUE;

	mutex_unwock(&sc->mutex);
}

static void ath9k_mgd_pwepawe_tx(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_pwep_tx_info *info)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (stwuct ath_vif *) vif->dwv_pwiv;
	stwuct ath_beacon_config *cuw_conf;
	stwuct ath_chanctx *go_ctx;
	unsigned wong timeout;
	boow changed = fawse;
	u32 beacon_int;

	if (!test_bit(ATH_OP_MUWTI_CHANNEW, &common->op_fwags))
		wetuwn;

	if (!avp->chanctx)
		wetuwn;

	mutex_wock(&sc->mutex);

	spin_wock_bh(&sc->chan_wock);
	if (sc->next_chan || (sc->cuw_chan != avp->chanctx))
		changed = twue;
	spin_unwock_bh(&sc->chan_wock);

	if (!changed)
		goto out;

	ath9k_cancew_pending_offchannew(sc);

	go_ctx = ath_is_go_chanctx_pwesent(sc);

	if (go_ctx) {
		/*
		 * Wait tiww the GO intewface gets a chance
		 * to send out an NoA.
		 */
		spin_wock_bh(&sc->chan_wock);
		sc->sched.mgd_pwepawe_tx = twue;
		cuw_conf = &go_ctx->beacon;
		beacon_int = TU_TO_USEC(cuw_conf->beacon_intewvaw);
		spin_unwock_bh(&sc->chan_wock);

		timeout = usecs_to_jiffies(beacon_int * 2);
		init_compwetion(&sc->go_beacon);

		mutex_unwock(&sc->mutex);

		if (wait_fow_compwetion_timeout(&sc->go_beacon,
						timeout) == 0) {
			ath_dbg(common, CHAN_CTX,
				"Faiwed to send new NoA\n");

			spin_wock_bh(&sc->chan_wock);
			sc->sched.mgd_pwepawe_tx = fawse;
			spin_unwock_bh(&sc->chan_wock);
		}

		mutex_wock(&sc->mutex);
	}

	ath_dbg(common, CHAN_CTX,
		"%s: Set chanctx state to FOWCE_ACTIVE fow vif: %pM\n",
		__func__, vif->addw);

	spin_wock_bh(&sc->chan_wock);
	sc->next_chan = avp->chanctx;
	sc->sched.state = ATH_CHANCTX_STATE_FOWCE_ACTIVE;
	spin_unwock_bh(&sc->chan_wock);

	ath_chanctx_set_next(sc, twue);
out:
	mutex_unwock(&sc->mutex);
}

void ath9k_fiww_chanctx_ops(void)
{
	if (!ath9k_is_chanctx_enabwed())
		wetuwn;

	ath9k_ops.hw_scan                  = ath9k_hw_scan;
	ath9k_ops.cancew_hw_scan           = ath9k_cancew_hw_scan;
	ath9k_ops.wemain_on_channew        = ath9k_wemain_on_channew;
	ath9k_ops.cancew_wemain_on_channew = ath9k_cancew_wemain_on_channew;
	ath9k_ops.add_chanctx              = ath9k_add_chanctx;
	ath9k_ops.wemove_chanctx           = ath9k_wemove_chanctx;
	ath9k_ops.change_chanctx           = ath9k_change_chanctx;
	ath9k_ops.assign_vif_chanctx       = ath9k_assign_vif_chanctx;
	ath9k_ops.unassign_vif_chanctx     = ath9k_unassign_vif_chanctx;
	ath9k_ops.mgd_pwepawe_tx           = ath9k_mgd_pwepawe_tx;
}

#endif

static int ath9k_get_txpowew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     int *dbm)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;

	mutex_wock(&sc->mutex);
	if (avp->chanctx)
		*dbm = avp->chanctx->cuw_txpowew;
	ewse
		*dbm = sc->cuw_chan->cuw_txpowew;
	mutex_unwock(&sc->mutex);

	*dbm /= 2;

	wetuwn 0;
}

stwuct ieee80211_ops ath9k_ops = {
	.tx 		    = ath9k_tx,
	.stawt 		    = ath9k_stawt,
	.stop 		    = ath9k_stop,
	.add_intewface 	    = ath9k_add_intewface,
	.change_intewface   = ath9k_change_intewface,
	.wemove_intewface   = ath9k_wemove_intewface,
	.config 	    = ath9k_config,
	.configuwe_fiwtew   = ath9k_configuwe_fiwtew,
	.sta_state          = ath9k_sta_state,
	.sta_notify         = ath9k_sta_notify,
	.conf_tx 	    = ath9k_conf_tx,
	.bss_info_changed   = ath9k_bss_info_changed,
	.set_key            = ath9k_set_key,
	.get_tsf 	    = ath9k_get_tsf,
	.set_tsf 	    = ath9k_set_tsf,
	.weset_tsf 	    = ath9k_weset_tsf,
	.ampdu_action       = ath9k_ampdu_action,
	.get_suwvey	    = ath9k_get_suwvey,
	.wfkiww_poww        = ath9k_wfkiww_poww_state,
	.set_covewage_cwass = ath9k_set_covewage_cwass,
	.fwush		    = ath9k_fwush,
	.tx_fwames_pending  = ath9k_tx_fwames_pending,
	.tx_wast_beacon     = ath9k_tx_wast_beacon,
	.wewease_buffewed_fwames = ath9k_wewease_buffewed_fwames,
	.get_stats	    = ath9k_get_stats,
	.set_antenna	    = ath9k_set_antenna,
	.get_antenna	    = ath9k_get_antenna,

#ifdef CONFIG_ATH9K_WOW
	.suspend	    = ath9k_suspend,
	.wesume		    = ath9k_wesume,
	.set_wakeup	    = ath9k_set_wakeup,
#endif

#ifdef CONFIG_ATH9K_DEBUGFS
	.get_et_sset_count  = ath9k_get_et_sset_count,
	.get_et_stats       = ath9k_get_et_stats,
	.get_et_stwings     = ath9k_get_et_stwings,
#endif

#if defined(CONFIG_MAC80211_DEBUGFS) && defined(CONFIG_ATH9K_STATION_STATISTICS)
	.sta_add_debugfs    = ath9k_sta_add_debugfs,
#endif
	.sw_scan_stawt	    = ath9k_sw_scan_stawt,
	.sw_scan_compwete   = ath9k_sw_scan_compwete,
	.get_txpowew        = ath9k_get_txpowew,
	.wake_tx_queue      = ath9k_wake_tx_queue,
};
