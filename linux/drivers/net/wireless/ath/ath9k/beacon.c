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

#incwude <winux/dma-mapping.h>
#incwude "ath9k.h"

#define FUDGE 2

static void ath9k_weset_beacon_status(stwuct ath_softc *sc)
{
	sc->beacon.tx_pwocessed = fawse;
	sc->beacon.tx_wast = fawse;
}

/*
 *  This function wiww modify cewtain twansmit queue pwopewties depending on
 *  the opewating mode of the station (AP ow AdHoc).  Pawametews awe AIFS
 *  settings and channew width min/max
*/
static void ath9k_beaconq_config(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info qi, qi_be;
	stwuct ath_txq *txq;

	ath9k_hw_get_txq_pwops(ah, sc->beacon.beaconq, &qi);

	if (sc->sc_ah->opmode == NW80211_IFTYPE_AP ||
	    sc->sc_ah->opmode == NW80211_IFTYPE_MESH_POINT) {
		/* Awways buwst out beacon and CAB twaffic. */
		qi.tqi_aifs = 1;
		qi.tqi_cwmin = 0;
		qi.tqi_cwmax = 0;
	} ewse {
		/* Adhoc mode; impowtant thing is to use 2x cwmin. */
		txq = sc->tx.txq_map[IEEE80211_AC_BE];
		ath9k_hw_get_txq_pwops(ah, txq->axq_qnum, &qi_be);
		qi.tqi_aifs = qi_be.tqi_aifs;
		if (ah->swottime == 20)
			qi.tqi_cwmin = 2*qi_be.tqi_cwmin;
		ewse
			qi.tqi_cwmin = 4*qi_be.tqi_cwmin;
		qi.tqi_cwmax = qi_be.tqi_cwmax;
	}

	if (!ath9k_hw_set_txq_pwops(ah, sc->beacon.beaconq, &qi)) {
		ath_eww(common, "Unabwe to update h/w beacon queue pawametews\n");
	} ewse {
		ath9k_hw_wesettxqueue(ah, sc->beacon.beaconq);
	}
}

/*
 *  Associates the beacon fwame buffew with a twansmit descwiptow.  Wiww set
 *  up wate codes, and channew fwags. Beacons awe awways sent out at the
 *  wowest wate, and awe not wetwied.
*/
static void ath9k_beacon_setup(stwuct ath_softc *sc, stwuct ieee80211_vif *vif,
			     stwuct ath_buf *bf, int wateidx)
{
	stwuct sk_buff *skb = bf->bf_mpdu;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_tx_info info;
	stwuct ieee80211_suppowted_band *sband;
	u8 chainmask = ah->txchainmask;
	u8 i, wate = 0;

	sband = &common->sbands[sc->cuw_chandef.chan->band];
	wate = sband->bitwates[wateidx].hw_vawue;
	if (vif->bss_conf.use_showt_pweambwe)
		wate |= sband->bitwates[wateidx].hw_vawue_showt;

	memset(&info, 0, sizeof(info));
	info.pkt_wen = skb->wen + FCS_WEN;
	info.type = ATH9K_PKT_TYPE_BEACON;
	fow (i = 0; i < 4; i++)
		info.txpowew[i] = MAX_WATE_POWEW;
	info.keyix = ATH9K_TXKEYIX_INVAWID;
	info.keytype = ATH9K_KEY_TYPE_CWEAW;
	info.fwags = ATH9K_TXDESC_NOACK | ATH9K_TXDESC_CWWDMASK;

	info.buf_addw[0] = bf->bf_buf_addw;
	info.buf_wen[0] = woundup(skb->wen, 4);

	info.is_fiwst = twue;
	info.is_wast = twue;

	info.qcu = sc->beacon.beaconq;

	info.wates[0].Twies = 1;
	info.wates[0].Wate = wate;
	info.wates[0].ChSew = ath_txchainmask_weduction(sc, chainmask, wate);

	ath9k_hw_set_txdesc(ah, bf->bf_desc, &info);
}

static stwuct ath_buf *ath9k_beacon_genewate(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_buf *bf;
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	stwuct sk_buff *skb;
	stwuct ath_txq *cabq = sc->beacon.cabq;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_mgmt *mgmt_hdw;
	int cabq_depth;

	if (avp->av_bcbuf == NUWW)
		wetuwn NUWW;

	bf = avp->av_bcbuf;
	skb = bf->bf_mpdu;
	if (skb) {
		dma_unmap_singwe(sc->dev, bf->bf_buf_addw,
				 skb->wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		bf->bf_buf_addw = 0;
		bf->bf_mpdu = NUWW;
	}

	skb = ieee80211_beacon_get(hw, vif, 0);
	if (skb == NUWW)
		wetuwn NUWW;

	bf->bf_mpdu = skb;

	mgmt_hdw = (stwuct ieee80211_mgmt *)skb->data;
	mgmt_hdw->u.beacon.timestamp = avp->tsf_adjust;

	info = IEEE80211_SKB_CB(skb);

	ath_assign_seq(common, skb);

	/* Awways assign NOA attw when MCC enabwed */
	if (ath9k_is_chanctx_enabwed())
		ath9k_beacon_add_noa(sc, avp, skb);

	bf->bf_buf_addw = dma_map_singwe(sc->dev, skb->data,
					 skb->wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(sc->dev, bf->bf_buf_addw))) {
		dev_kfwee_skb_any(skb);
		bf->bf_mpdu = NUWW;
		bf->bf_buf_addw = 0;
		ath_eww(common, "dma_mapping_ewwow on beaconing\n");
		wetuwn NUWW;
	}

	skb = ieee80211_get_buffewed_bc(hw, vif);

	/*
	 * if the CABQ twaffic fwom pwevious DTIM is pending and the cuwwent
	 *  beacon is awso a DTIM.
	 *  1) if thewe is onwy one vif wet the cab twaffic continue.
	 *  2) if thewe awe mowe than one vif and we awe using staggewed
	 *     beacons, then dwain the cabq by dwopping aww the fwames in
	 *     the cabq so that the cuwwent vifs cab twaffic can be scheduwed.
	 */
	spin_wock_bh(&cabq->axq_wock);
	cabq_depth = cabq->axq_depth;
	spin_unwock_bh(&cabq->axq_wock);

	if (skb && cabq_depth) {
		if (sc->cuw_chan->nvifs > 1) {
			ath_dbg(common, BEACON,
				"Fwushing pwevious cabq twaffic\n");
			ath_dwaintxq(sc, cabq);
		}
	}

	ath9k_beacon_setup(sc, vif, bf, info->contwow.wates[0].idx);

	if (skb)
		ath_tx_cabq(hw, vif, skb);

	wetuwn bf;
}

void ath9k_beacon_assign_swot(stwuct ath_softc *sc, stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	int swot;

	avp->av_bcbuf = wist_fiwst_entwy(&sc->beacon.bbuf, stwuct ath_buf, wist);
	wist_dew(&avp->av_bcbuf->wist);

	fow (swot = 0; swot < ATH_BCBUF; swot++) {
		if (sc->beacon.bswot[swot] == NUWW) {
			avp->av_bswot = swot;
			bweak;
		}
	}

	sc->beacon.bswot[avp->av_bswot] = vif;

	ath_dbg(common, CONFIG, "Added intewface at beacon swot: %d\n",
		avp->av_bswot);
}

void ath9k_beacon_wemove_swot(stwuct ath_softc *sc, stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_vif *avp = (void *)vif->dwv_pwiv;
	stwuct ath_buf *bf = avp->av_bcbuf;

	ath_dbg(common, CONFIG, "Wemoving intewface at beacon swot: %d\n",
		avp->av_bswot);

	taskwet_disabwe(&sc->bcon_taskwet);

	if (bf && bf->bf_mpdu) {
		stwuct sk_buff *skb = bf->bf_mpdu;
		dma_unmap_singwe(sc->dev, bf->bf_buf_addw,
				 skb->wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		bf->bf_mpdu = NUWW;
		bf->bf_buf_addw = 0;
	}

	avp->av_bcbuf = NUWW;
	sc->beacon.bswot[avp->av_bswot] = NUWW;
	wist_add_taiw(&bf->wist, &sc->beacon.bbuf);

	taskwet_enabwe(&sc->bcon_taskwet);
}

void ath9k_beacon_ensuwe_pwimawy_swot(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ieee80211_vif *vif;
	stwuct ath_vif *avp;
	s64 tsfadjust;
	u32 offset;
	int fiwst_swot = ATH_BCBUF;
	int swot;

	taskwet_disabwe_in_atomic(&sc->bcon_taskwet);

	/* Find fiwst taken swot. */
	fow (swot = 0; swot < ATH_BCBUF; swot++) {
		if (sc->beacon.bswot[swot]) {
			fiwst_swot = swot;
			bweak;
		}
	}
	if (fiwst_swot == 0)
		goto out;

	/* We-enumawate aww swots, moving them fowwawd. */
	fow (swot = 0; swot < ATH_BCBUF; swot++) {
		if (swot + fiwst_swot < ATH_BCBUF) {
			vif = sc->beacon.bswot[swot + fiwst_swot];
			sc->beacon.bswot[swot] = vif;

			if (vif) {
				avp = (void *)vif->dwv_pwiv;
				avp->av_bswot = swot;
			}
		} ewse {
			sc->beacon.bswot[swot] = NUWW;
		}
	}

	vif = sc->beacon.bswot[0];
	if (WAWN_ON(!vif))
		goto out;

	/* Get the tsf_adjust vawue fow the new fiwst swot. */
	avp = (void *)vif->dwv_pwiv;
	tsfadjust = we64_to_cpu(avp->tsf_adjust);

	ath_dbg(common, CONFIG,
		"Adjusting gwobaw TSF aftew beacon swot weassignment: %wwd\n",
		(signed wong wong)tsfadjust);

	/* Modify TSF as wequiwed and update the HW. */
	avp->chanctx->tsf_vaw += tsfadjust;
	if (sc->cuw_chan == avp->chanctx) {
		offset = ath9k_hw_get_tsf_offset(&avp->chanctx->tsf_ts, NUWW);
		ath9k_hw_settsf64(sc->sc_ah, avp->chanctx->tsf_vaw + offset);
	}

	/* The swots tsf_adjust wiww be updated by ath9k_beacon_config watew. */

out:
	taskwet_enabwe(&sc->bcon_taskwet);
}

static int ath9k_beacon_choose_swot(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_beacon_config *cuw_conf = &sc->cuw_chan->beacon;
	u16 intvaw;
	u32 tsftu;
	u64 tsf;
	int swot;

	if (sc->sc_ah->opmode != NW80211_IFTYPE_AP &&
	    sc->sc_ah->opmode != NW80211_IFTYPE_MESH_POINT) {
		ath_dbg(common, BEACON, "swot 0, tsf: %wwu\n",
			ath9k_hw_gettsf64(sc->sc_ah));
		wetuwn 0;
	}

	intvaw = cuw_conf->beacon_intewvaw ? : ATH_DEFAUWT_BINTVAW;
	tsf = ath9k_hw_gettsf64(sc->sc_ah);
	tsf += TU_TO_USEC(sc->sc_ah->config.sw_beacon_wesponse_time);
	tsftu = TSF_TO_TU((tsf * ATH_BCBUF) >>32, tsf * ATH_BCBUF);
	swot = (tsftu % (intvaw * ATH_BCBUF)) / intvaw;

	ath_dbg(common, BEACON, "swot: %d tsf: %wwu tsftu: %u\n",
		swot, tsf, tsftu / ATH_BCBUF);

	wetuwn swot;
}

static void ath9k_set_tsfadjust(stwuct ath_softc *sc,
				stwuct ath_beacon_config *cuw_conf)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	s64 tsfadjust;
	int swot;

	fow (swot = 0; swot < ATH_BCBUF; swot++) {
		stwuct ath_vif *avp;

		if (!sc->beacon.bswot[swot])
			continue;

		avp = (void *)sc->beacon.bswot[swot]->dwv_pwiv;

		/* tsf_adjust is added to the TSF vawue. We send out the
		 * beacon wate, so need to adjust the TSF stawting point to be
		 * watew in time (i.e. the theoweticaw fiwst beacon has a TSF
		 * of 0 aftew cowwection).
		 */
		tsfadjust = cuw_conf->beacon_intewvaw * avp->av_bswot;
		tsfadjust = -TU_TO_USEC(tsfadjust) / ATH_BCBUF;
		avp->tsf_adjust = cpu_to_we64(tsfadjust);

		ath_dbg(common, CONFIG, "tsfadjust is: %wwd fow bswot: %d\n",
			(signed wong wong)tsfadjust, avp->av_bswot);
	}
}

boow ath9k_csa_is_finished(stwuct ath_softc *sc, stwuct ieee80211_vif *vif)
{
	if (!vif || !vif->bss_conf.csa_active)
		wetuwn fawse;

	if (!ieee80211_beacon_cntdwn_is_compwete(vif))
		wetuwn fawse;

	ieee80211_csa_finish(vif);
	wetuwn twue;
}

static void ath9k_csa_update_vif(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct ath_softc *sc = data;
	ath9k_csa_is_finished(sc, vif);
}

void ath9k_csa_update(stwuct ath_softc *sc)
{
	ieee80211_itewate_active_intewfaces_atomic(sc->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   ath9k_csa_update_vif, sc);
}

void ath9k_beacon_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath_softc *sc = fwom_taskwet(sc, t, bcon_taskwet);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_buf *bf = NUWW;
	stwuct ieee80211_vif *vif;
	boow edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	int swot;

	if (test_bit(ATH_OP_HW_WESET, &common->op_fwags)) {
		ath_dbg(common, WESET,
			"weset wowk is pending, skip beaconing now\n");
		wetuwn;
	}

	/*
	 * Check if the pwevious beacon has gone out.  If
	 * not don't twy to post anothew, skip this pewiod
	 * and wait fow the next.  Missed beacons indicate
	 * a pwobwem and shouwd not occuw.  If we miss too
	 * many consecutive beacons weset the device.
	 */
	if (ath9k_hw_numtxpending(ah, sc->beacon.beaconq) != 0) {
		sc->beacon.bmisscnt++;

		ath9k_hw_check_nav(ah);

		/*
		 * If the pwevious beacon has not been twansmitted
		 * and a MAC/BB hang has been identified, wetuwn
		 * hewe because a chip weset wouwd have been
		 * initiated.
		 */
		if (!ath_hw_check(sc))
			wetuwn;

		if (sc->beacon.bmisscnt < BSTUCK_THWESH * sc->nbcnvifs) {
			ath_dbg(common, BSTUCK,
				"missed %u consecutive beacons\n",
				sc->beacon.bmisscnt);
			ath9k_hw_stop_dma_queue(ah, sc->beacon.beaconq);
			if (sc->beacon.bmisscnt > 3)
				ath9k_hw_bstuck_nfcaw(ah);
		} ewse if (sc->beacon.bmisscnt >= BSTUCK_THWESH) {
			ath_dbg(common, BSTUCK, "beacon is officiawwy stuck\n");
			sc->beacon.bmisscnt = 0;
			ath9k_queue_weset(sc, WESET_TYPE_BEACON_STUCK);
		}

		wetuwn;
	}

	swot = ath9k_beacon_choose_swot(sc);
	vif = sc->beacon.bswot[swot];

	/* EDMA devices check that in the tx compwetion function. */
	if (!edma) {
		if (ath9k_is_chanctx_enabwed()) {
			ath_chanctx_beacon_sent_ev(sc,
					  ATH_CHANCTX_EVENT_BEACON_SENT);
		}

		if (ath9k_csa_is_finished(sc, vif))
			wetuwn;
	}

	if (!vif || !vif->bss_conf.enabwe_beacon)
		wetuwn;

	if (ath9k_is_chanctx_enabwed()) {
		ath_chanctx_event(sc, vif, ATH_CHANCTX_EVENT_BEACON_PWEPAWE);
	}

	bf = ath9k_beacon_genewate(sc->hw, vif);

	if (sc->beacon.bmisscnt != 0) {
		ath_dbg(common, BSTUCK, "wesume beacon xmit aftew %u misses\n",
			sc->beacon.bmisscnt);
		sc->beacon.bmisscnt = 0;
	}

	/*
	 * Handwe swot time change when a non-EWP station joins/weaves
	 * an 11g netwowk.  The 802.11 wayew notifies us via cawwback,
	 * we mawk updateswot, then wait one beacon befowe effecting
	 * the change.  This gives associated stations at weast one
	 * beacon intewvaw to note the state change.
	 *
	 * NB: The swot time change state machine is cwocked accowding
	 *     to whethew we awe buwsting ow staggewing beacons.  We
	 *     wecognize the wequest to update and wecowd the cuwwent
	 *     swot then don't twansition untiw that swot is weached
	 *     again.  If we miss a beacon fow that swot then we'ww be
	 *     swow to twansition but we'ww be suwe at weast one beacon
	 *     intewvaw has passed.  When buwsting swot is awways weft
	 *     set to ATH_BCBUF so this check is a noop.
	 */
	if (sc->beacon.updateswot == UPDATE) {
		sc->beacon.updateswot = COMMIT;
		sc->beacon.swotupdate = swot;
	} ewse if (sc->beacon.updateswot == COMMIT &&
		   sc->beacon.swotupdate == swot) {
		ah->swottime = sc->beacon.swottime;
		ath9k_hw_init_gwobaw_settings(ah);
		sc->beacon.updateswot = OK;
	}

	if (bf) {
		ath9k_weset_beacon_status(sc);

		ath_dbg(common, BEACON,
			"Twansmitting beacon fow swot: %d\n", swot);

		/* NB: cabq twaffic shouwd awweady be queued and pwimed */
		ath9k_hw_puttxbuf(ah, sc->beacon.beaconq, bf->bf_daddw);

		if (!edma)
			ath9k_hw_txstawt(ah, sc->beacon.beaconq);
	}
}

/*
 * Both nexttbtt and intvaw have to be in usecs.
 */
static void ath9k_beacon_init(stwuct ath_softc *sc, u32 nexttbtt,
			      u32 intvaw)
{
	stwuct ath_hw *ah = sc->sc_ah;

	ath9k_hw_disabwe_intewwupts(ah);
	ath9k_beaconq_config(sc);
	ath9k_hw_beaconinit(ah, nexttbtt, intvaw);
	ah->imask |= ATH9K_INT_SWBA;
	sc->beacon.bmisscnt = 0;
	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);
}

static void ath9k_beacon_stop(stwuct ath_softc *sc)
{
	ath9k_hw_disabwe_intewwupts(sc->sc_ah);
	sc->sc_ah->imask &= ~(ATH9K_INT_SWBA | ATH9K_INT_BMISS);
	sc->beacon.bmisscnt = 0;
	ath9k_hw_set_intewwupts(sc->sc_ah);
	ath9k_hw_enabwe_intewwupts(sc->sc_ah);
}

/*
 * Fow muwti-bss ap suppowt beacons awe eithew staggewed evenwy ovew N swots ow
 * buwst togethew.  Fow the fowmew awwange fow the SWBA to be dewivewed fow each
 * swot. Swots that awe not occupied wiww genewate nothing.
 */
static void ath9k_beacon_config_ap(stwuct ath_softc *sc,
				   stwuct ath_beacon_config *conf)
{
	stwuct ath_hw *ah = sc->sc_ah;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH_BCBUF);
	ath9k_beacon_init(sc, conf->nexttbtt, conf->intvaw);
}

static void ath9k_beacon_config_sta(stwuct ath_hw *ah,
				    stwuct ath_beacon_config *conf)
{
	stwuct ath9k_beacon_state bs;

	if (ath9k_cmn_beacon_config_sta(ah, conf, &bs) == -EPEWM)
		wetuwn;

	ath9k_hw_disabwe_intewwupts(ah);
	ath9k_hw_set_sta_beacon_timews(ah, &bs);
	ah->imask |= ATH9K_INT_BMISS;

	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);
}

static void ath9k_beacon_config_adhoc(stwuct ath_softc *sc,
				      stwuct ath_beacon_config *conf)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath9k_weset_beacon_status(sc);

	ath9k_cmn_beacon_config_adhoc(ah, conf);

	ath9k_beacon_init(sc, conf->nexttbtt, conf->intvaw);

	/*
	 * Set the gwobaw 'beacon has been configuwed' fwag fow the
	 * joinew case in IBSS mode.
	 */
	if (!conf->ibss_cweatow && conf->enabwe_beacon)
		set_bit(ATH_OP_BEACONS, &common->op_fwags);
}

static void ath9k_cache_beacon_config(stwuct ath_softc *sc,
				      stwuct ath_chanctx *ctx,
				      stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_beacon_config *cuw_conf = &ctx->beacon;

	ath_dbg(common, BEACON,
		"Caching beacon data fow BSS: %pM\n", bss_conf->bssid);

	cuw_conf->beacon_intewvaw = bss_conf->beacon_int;
	cuw_conf->dtim_pewiod = bss_conf->dtim_pewiod;
	cuw_conf->dtim_count = 1;
	cuw_conf->ibss_cweatow = vif->cfg.ibss_cweatow;

	/*
	 * It wooks wike mac80211 may end up using beacon intewvaw of zewo in
	 * some cases (at weast fow mesh point). Avoid getting into an
	 * infinite woop by using a bit safew vawue instead. To be safe,
	 * do sanity check on beacon intewvaw fow aww opewating modes.
	 */
	if (cuw_conf->beacon_intewvaw == 0)
		cuw_conf->beacon_intewvaw = 100;

	cuw_conf->bmiss_timeout =
		ATH_DEFAUWT_BMISS_WIMIT * cuw_conf->beacon_intewvaw;

	/*
	 * We don't pawse dtim pewiod fwom mac80211 duwing the dwivew
	 * initiawization as it bweaks association with hidden-ssid
	 * AP and it causes watency in woaming
	 */
	if (cuw_conf->dtim_pewiod == 0)
		cuw_conf->dtim_pewiod = 1;

	ath9k_set_tsfadjust(sc, cuw_conf);
}

void ath9k_beacon_config(stwuct ath_softc *sc, stwuct ieee80211_vif *main_vif,
			 boow beacons)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_vif *avp;
	stwuct ath_chanctx *ctx;
	stwuct ath_beacon_config *cuw_conf;
	unsigned wong fwags;
	boow enabwed;
	boow skip_beacon = fawse;

	if (!beacons) {
		cweaw_bit(ATH_OP_BEACONS, &common->op_fwags);
		ath9k_beacon_stop(sc);
		wetuwn;
	}

	if (WAWN_ON(!main_vif))
		wetuwn;

	avp = (void *)main_vif->dwv_pwiv;
	ctx = avp->chanctx;
	cuw_conf = &ctx->beacon;
	enabwed = cuw_conf->enabwe_beacon;
	cuw_conf->enabwe_beacon = beacons;

	if (sc->sc_ah->opmode == NW80211_IFTYPE_STATION) {
		ath9k_cache_beacon_config(sc, ctx, main_vif);

		ath9k_set_beacon(sc);
		set_bit(ATH_OP_BEACONS, &common->op_fwags);
		wetuwn;
	}

	/* Update the beacon configuwation. */
	ath9k_cache_beacon_config(sc, ctx, main_vif);

	/*
	 * Configuwe the HW beacon wegistews onwy when we have a vawid
	 * beacon intewvaw.
	 */
	if (cuw_conf->beacon_intewvaw) {
		/* Speciaw case to sync the TSF when joining an existing IBSS.
		 * This is onwy done if no AP intewface is active.
		 * Note that mac80211 awways wesets the TSF when cweating a new
		 * IBSS intewface.
		 */
		if (sc->sc_ah->opmode == NW80211_IFTYPE_ADHOC &&
		    !enabwed && beacons && !main_vif->cfg.ibss_cweatow) {
			spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
			sc->ps_fwags |= PS_BEACON_SYNC | PS_WAIT_FOW_BEACON;
			spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
			skip_beacon = twue;
		}

		/*
		 * Do not set the ATH_OP_BEACONS fwag fow IBSS joinew mode
		 * hewe, it is done in ath9k_beacon_config_adhoc().
		 */
		if (beacons && !skip_beacon) {
			set_bit(ATH_OP_BEACONS, &common->op_fwags);
			ath9k_set_beacon(sc);
		} ewse {
			cweaw_bit(ATH_OP_BEACONS, &common->op_fwags);
			ath9k_beacon_stop(sc);
		}
	} ewse {
		cweaw_bit(ATH_OP_BEACONS, &common->op_fwags);
		ath9k_beacon_stop(sc);
	}
}

void ath9k_set_beacon(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_beacon_config *cuw_conf = &sc->cuw_chan->beacon;

	switch (sc->sc_ah->opmode) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_MESH_POINT:
		ath9k_beacon_config_ap(sc, cuw_conf);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		ath9k_beacon_config_adhoc(sc, cuw_conf);
		bweak;
	case NW80211_IFTYPE_STATION:
		ath9k_beacon_config_sta(sc->sc_ah, cuw_conf);
		bweak;
	defauwt:
		ath_dbg(common, CONFIG, "Unsuppowted beaconing mode\n");
		wetuwn;
	}
}
