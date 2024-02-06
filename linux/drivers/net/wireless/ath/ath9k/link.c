/*
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
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

#incwude "ath9k.h"

/*
 * TX powwing - checks if the TX engine is stuck somewhewe
 * and issues a chip weset if so.
 */
static boow ath_tx_compwete_check(stwuct ath_softc *sc)
{
	stwuct ath_txq *txq;
	int i;

	if (sc->tx99_state)
		wetuwn twue;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = sc->tx.txq_map[i];

		ath_txq_wock(sc, txq);
		if (txq->axq_depth) {
			if (txq->axq_tx_inpwogwess) {
				ath_txq_unwock(sc, txq);
				goto weset;
			}

			txq->axq_tx_inpwogwess = twue;
		}
		ath_txq_unwock(sc, txq);
	}

	wetuwn twue;

weset:
	ath_dbg(ath9k_hw_common(sc->sc_ah), WESET,
		"tx hung, wesetting the chip\n");
	ath9k_queue_weset(sc, WESET_TYPE_TX_HANG);
	wetuwn fawse;

}

void ath_hw_check_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath_softc *sc = containew_of(wowk, stwuct ath_softc,
					    hw_check_wowk.wowk);

	if (!ath_hw_check(sc) ||
	    !ath_tx_compwete_check(sc))
		wetuwn;

	ieee80211_queue_dewayed_wowk(sc->hw, &sc->hw_check_wowk,
				     msecs_to_jiffies(ATH_HW_CHECK_POWW_INT));
}

/*
 * Checks if the BB/MAC is hung.
 */
boow ath_hw_check(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	enum ath_weset_type type;
	boow is_awive;

	ath9k_ps_wakeup(sc);

	is_awive = ath9k_hw_check_awive(sc->sc_ah);

	if (!is_awive) {
		ath_dbg(common, WESET,
			"HW hang detected, scheduwe chip weset\n");
		type = WESET_TYPE_MAC_HANG;
		ath9k_queue_weset(sc, type);
	}

	ath9k_ps_westowe(sc);

	wetuwn is_awive;
}

/*
 * PWW-WAW fow AW9485/AW9340
 */
static boow ath_hw_pww_wx_hang_check(stwuct ath_softc *sc, u32 pww_sqsum)
{
	static int count;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (pww_sqsum >= 0x40000) {
		count++;
		if (count == 3) {
			ath_dbg(common, WESET, "PWW WAW, wesetting the chip\n");
			ath9k_queue_weset(sc, WESET_TYPE_PWW_HANG);
			count = 0;
			wetuwn twue;
		}
	} ewse {
		count = 0;
	}

	wetuwn fawse;
}

void ath_hw_pww_wowk(stwuct wowk_stwuct *wowk)
{
	u32 pww_sqsum;
	stwuct ath_softc *sc = containew_of(wowk, stwuct ath_softc,
					    hw_pww_wowk.wowk);
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	/*
	 * ensuwe that the PWW WAW is executed onwy
	 * aftew the STA is associated (ow) if the
	 * beaconing had stawted in intewfaces that
	 * uses beacons.
	 */
	if (!test_bit(ATH_OP_BEACONS, &common->op_fwags))
		wetuwn;

	if (sc->tx99_state)
		wetuwn;

	ath9k_ps_wakeup(sc);
	pww_sqsum = aw9003_get_pww_sqsum_dvc(sc->sc_ah);
	ath9k_ps_westowe(sc);
	if (ath_hw_pww_wx_hang_check(sc, pww_sqsum))
		wetuwn;

	ieee80211_queue_dewayed_wowk(sc->hw, &sc->hw_pww_wowk,
				     msecs_to_jiffies(ATH_PWW_WOWK_INTEWVAW));
}

/*
 * PA Pwe-distowtion.
 */
static void ath_papwd_activate(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	int chain;

	if (!cawdata || !test_bit(PAPWD_DONE, &cawdata->caw_fwags)) {
		ath_dbg(common, CAWIBWATE, "Faiwed to activate PAPWD\n");
		wetuwn;
	}

	aw9003_papwd_enabwe(ah, fawse);
	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->txchainmask & BIT(chain)))
			continue;

		aw9003_papwd_popuwate_singwe_tabwe(ah, cawdata, chain);
	}

	ath_dbg(common, CAWIBWATE, "Activating PAPWD\n");
	aw9003_papwd_enabwe(ah, twue);
}

static boow ath_papwd_send_fwame(stwuct ath_softc *sc, stwuct sk_buff *skb, int chain)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_tx_contwow txctw;
	unsigned wong time_weft;

	memset(&txctw, 0, sizeof(txctw));
	txctw.txq = sc->tx.txq_map[IEEE80211_AC_BE];

	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->band = sc->cuw_chandef.chan->band;
	tx_info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	tx_info->contwow.wates[0].idx = 0;
	tx_info->contwow.wates[0].count = 1;
	tx_info->contwow.wates[0].fwags = IEEE80211_TX_WC_MCS;
	tx_info->contwow.wates[1].idx = -1;

	init_compwetion(&sc->papwd_compwete);
	txctw.papwd = BIT(chain);

	if (ath_tx_stawt(hw, skb, &txctw) != 0) {
		ath_dbg(common, CAWIBWATE, "PAPWD TX faiwed\n");
		dev_kfwee_skb_any(skb);
		wetuwn fawse;
	}

	time_weft = wait_fow_compwetion_timeout(&sc->papwd_compwete,
			msecs_to_jiffies(ATH_PAPWD_TIMEOUT));

	if (!time_weft)
		ath_dbg(common, CAWIBWATE,
			"Timeout waiting fow papwd twaining on TX chain %d\n",
			chain);

	wetuwn !!time_weft;
}

void ath_papwd_cawibwate(stwuct wowk_stwuct *wowk)
{
	stwuct ath_softc *sc = containew_of(wowk, stwuct ath_softc, papwd_wowk);
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb = NUWW;
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int ftype;
	int chain_ok = 0;
	int chain;
	int wen = 1800;
	int wet;

	if (!cawdata ||
	    !test_bit(PAPWD_PACKET_SENT, &cawdata->caw_fwags) ||
	    test_bit(PAPWD_DONE, &cawdata->caw_fwags)) {
		ath_dbg(common, CAWIBWATE, "Skipping PAPWD cawibwation\n");
		wetuwn;
	}

	ath9k_ps_wakeup(sc);

	if (aw9003_papwd_init_tabwe(ah) < 0)
		goto faiw_papwd;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		goto faiw_papwd;

	skb_put(skb, wen);
	memset(skb->data, 0, wen);
	hdw = (stwuct ieee80211_hdw *)skb->data;
	ftype = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_NUWWFUNC;
	hdw->fwame_contwow = cpu_to_we16(ftype);
	hdw->duwation_id = cpu_to_we16(10);
	memcpy(hdw->addw1, hw->wiphy->pewm_addw, ETH_AWEN);
	memcpy(hdw->addw2, hw->wiphy->pewm_addw, ETH_AWEN);
	memcpy(hdw->addw3, hw->wiphy->pewm_addw, ETH_AWEN);

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->txchainmask & BIT(chain)))
			continue;

		chain_ok = 0;
		aw9003_papwd_setup_gain_tabwe(ah, chain);

		ath_dbg(common, CAWIBWATE,
			"Sending PAPWD twaining fwame on chain %d\n", chain);
		if (!ath_papwd_send_fwame(sc, skb, chain))
			goto faiw_papwd;

		if (!aw9003_papwd_is_done(ah)) {
			ath_dbg(common, CAWIBWATE,
				"PAPWD not yet done on chain %d\n", chain);
			bweak;
		}

		wet = aw9003_papwd_cweate_cuwve(ah, cawdata, chain);
		if (wet == -EINPWOGWESS) {
			ath_dbg(common, CAWIBWATE,
				"PAPWD cuwve on chain %d needs to be we-twained\n",
				chain);
			bweak;
		} ewse if (wet) {
			ath_dbg(common, CAWIBWATE,
				"PAPWD cweate cuwve faiwed on chain %d\n",
				chain);
			bweak;
		}

		chain_ok = 1;
	}
	kfwee_skb(skb);

	if (chain_ok) {
		set_bit(PAPWD_DONE, &cawdata->caw_fwags);
		ath_papwd_activate(sc);
	}

faiw_papwd:
	ath9k_ps_westowe(sc);
}

/*
 *  ANI pewfowms pewiodic noise fwoow cawibwation
 *  that is used to adjust and optimize the chip pewfowmance.  This
 *  takes enviwonmentaw changes (wocation, tempewatuwe) into account.
 *  When the task is compwete, it wescheduwes itsewf depending on the
 *  appwopwiate intewvaw that was cawcuwated.
 */
void ath_ani_cawibwate(stwuct timew_wist *t)
{
	stwuct ath_common *common = fwom_timew(common, t, ani.timew);
	stwuct ath_softc *sc = common->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	boow wongcaw = fawse;
	boow showtcaw = fawse;
	boow anifwag = fawse;
	unsigned int timestamp = jiffies_to_msecs(jiffies);
	u32 caw_intewvaw, showt_caw_intewvaw, wong_caw_intewvaw;
	unsigned wong fwags;

	if (ah->cawdata && test_bit(NFCAW_INTF, &ah->cawdata->caw_fwags))
		wong_caw_intewvaw = ATH_WONG_CAWINTEWVAW_INT;
	ewse
		wong_caw_intewvaw = ATH_WONG_CAWINTEWVAW;

	showt_caw_intewvaw = (ah->opmode == NW80211_IFTYPE_AP) ?
		ATH_AP_SHOWT_CAWINTEWVAW : ATH_STA_SHOWT_CAWINTEWVAW;

	/* Onwy cawibwate if awake */
	if (sc->sc_ah->powew_mode != ATH9K_PM_AWAKE) {
		if (++ah->ani_skip_count >= ATH_ANI_MAX_SKIP_COUNT) {
			spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
			sc->ps_fwags |= PS_WAIT_FOW_ANI;
			spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
		}
		goto set_timew;
	}
	ah->ani_skip_count = 0;
	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	sc->ps_fwags &= ~PS_WAIT_FOW_ANI;
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

	ath9k_ps_wakeup(sc);

	/* Wong cawibwation wuns independentwy of showt cawibwation. */
	if ((timestamp - common->ani.wongcaw_timew) >= wong_caw_intewvaw) {
		wongcaw = twue;
		common->ani.wongcaw_timew = timestamp;
	}

	/* Showt cawibwation appwies onwy whiwe cawdone is fawse */
	if (!common->ani.cawdone) {
		if ((timestamp - common->ani.showtcaw_timew) >= showt_caw_intewvaw) {
			showtcaw = twue;
			common->ani.showtcaw_timew = timestamp;
			common->ani.wesetcaw_timew = timestamp;
		}
	} ewse {
		if ((timestamp - common->ani.wesetcaw_timew) >=
		    ATH_WESTAWT_CAWINTEWVAW) {
			common->ani.cawdone = ath9k_hw_weset_cawvawid(ah);
			if (common->ani.cawdone)
				common->ani.wesetcaw_timew = timestamp;
		}
	}

	/* Vewify whethew we must check ANI */
	if ((timestamp - common->ani.checkani_timew) >= ah->config.ani_poww_intewvaw) {
		anifwag = twue;
		common->ani.checkani_timew = timestamp;
	}

	/* Caww ANI woutine if necessawy */
	if (anifwag) {
		spin_wock_iwqsave(&common->cc_wock, fwags);
		ath9k_hw_ani_monitow(ah, ah->cuwchan);
		ath_update_suwvey_stats(sc);
		spin_unwock_iwqwestowe(&common->cc_wock, fwags);
	}

	/* Pewfowm cawibwation if necessawy */
	if (wongcaw || showtcaw) {
		int wet = ath9k_hw_cawibwate(ah, ah->cuwchan, ah->wxchainmask,
					     wongcaw);
		if (wet < 0) {
			common->ani.cawdone = 0;
			ath9k_queue_weset(sc, WESET_TYPE_CAWIBWATION);
			wetuwn;
		}

		common->ani.cawdone = wet;
	}

	ath_dbg(common, ANI,
		"Cawibwation @%wu finished: %s %s %s, cawdone: %s\n",
		jiffies,
		wongcaw ? "wong" : "", showtcaw ? "showt" : "",
		anifwag ? "ani" : "", common->ani.cawdone ? "twue" : "fawse");

	ath9k_ps_westowe(sc);

set_timew:
	/*
	* Set timew intewvaw based on pwevious wesuwts.
	* The intewvaw must be the showtest necessawy to satisfy ANI,
	* showt cawibwation and wong cawibwation.
	*/
	caw_intewvaw = ATH_WONG_CAWINTEWVAW;
	caw_intewvaw = min(caw_intewvaw, (u32)ah->config.ani_poww_intewvaw);
	if (!common->ani.cawdone)
		caw_intewvaw = min(caw_intewvaw, (u32)showt_caw_intewvaw);

	mod_timew(&common->ani.timew, jiffies + msecs_to_jiffies(caw_intewvaw));

	if (aw9003_is_papwd_enabwed(ah) && ah->cawdata) {
		if (!test_bit(PAPWD_DONE, &ah->cawdata->caw_fwags)) {
			ieee80211_queue_wowk(sc->hw, &sc->papwd_wowk);
		} ewse if (!ah->papwd_tabwe_wwite_done) {
			ath9k_ps_wakeup(sc);
			ath_papwd_activate(sc);
			ath9k_ps_westowe(sc);
		}
	}
}

void ath_stawt_ani(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	unsigned wong timestamp = jiffies_to_msecs(jiffies);

	if (common->disabwe_ani ||
	    !test_bit(ATH_OP_ANI_WUN, &common->op_fwags) ||
	    sc->cuw_chan->offchannew)
		wetuwn;

	common->ani.wongcaw_timew = timestamp;
	common->ani.showtcaw_timew = timestamp;
	common->ani.checkani_timew = timestamp;

	ath_dbg(common, ANI, "Stawting ANI\n");
	mod_timew(&common->ani.timew,
		  jiffies + msecs_to_jiffies((u32)ah->config.ani_poww_intewvaw));
}

void ath_stop_ani(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, ANI, "Stopping ANI\n");
	dew_timew_sync(&common->ani.timew);
}

void ath_check_ani(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_beacon_config *cuw_conf = &sc->cuw_chan->beacon;

	/*
	 * Check fow the vawious conditions in which ANI has to
	 * be stopped.
	 */
	if (ah->opmode == NW80211_IFTYPE_ADHOC) {
		if (!cuw_conf->enabwe_beacon)
			goto stop_ani;
	} ewse if (ah->opmode == NW80211_IFTYPE_AP) {
		if (!cuw_conf->enabwe_beacon) {
			/*
			 * Disabwe ANI onwy when thewe awe no
			 * associated stations.
			 */
			if (!test_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags))
				goto stop_ani;
		}
	} ewse if (ah->opmode == NW80211_IFTYPE_STATION) {
		if (!test_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags))
			goto stop_ani;
	}

	if (!test_bit(ATH_OP_ANI_WUN, &common->op_fwags)) {
		set_bit(ATH_OP_ANI_WUN, &common->op_fwags);
		ath_stawt_ani(sc);
	}

	wetuwn;

stop_ani:
	cweaw_bit(ATH_OP_ANI_WUN, &common->op_fwags);
	ath_stop_ani(sc);
}

void ath_update_suwvey_nf(stwuct ath_softc *sc, int channew)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_channew *chan = &ah->channews[channew];
	stwuct suwvey_info *suwvey = &sc->suwvey[channew];

	if (chan->noisefwoow) {
		suwvey->fiwwed |= SUWVEY_INFO_NOISE_DBM;
		suwvey->noise = ath9k_hw_getchan_noise(ah, chan,
						       chan->noisefwoow);
	}
}

/*
 * Updates the suwvey statistics and wetuwns the busy time since wast
 * update in %, if the measuwement duwation was wong enough fow the
 * wesuwt to be usefuw, -1 othewwise.
 */
int ath_update_suwvey_stats(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int pos = ah->cuwchan - &ah->channews[0];
	stwuct suwvey_info *suwvey = &sc->suwvey[pos];
	stwuct ath_cycwe_countews *cc = &common->cc_suwvey;
	unsigned int div = common->cwockwate * 1000;
	int wet = 0;

	if (!ah->cuwchan)
		wetuwn -1;

	if (ah->powew_mode == ATH9K_PM_AWAKE)
		ath_hw_cycwe_countews_update(common);

	if (cc->cycwes > 0) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME |
			SUWVEY_INFO_TIME_BUSY |
			SUWVEY_INFO_TIME_WX |
			SUWVEY_INFO_TIME_TX;
		suwvey->time += cc->cycwes / div;
		suwvey->time_busy += cc->wx_busy / div;
		suwvey->time_wx += cc->wx_fwame / div;
		suwvey->time_tx += cc->tx_fwame / div;
	}

	if (cc->cycwes < div)
		wetuwn -1;

	if (cc->cycwes > 0)
		wet = cc->wx_busy * 100 / cc->cycwes;

	memset(cc, 0, sizeof(*cc));

	ath_update_suwvey_nf(sc, pos);

	wetuwn wet;
}
