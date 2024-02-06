/*
 * Copywight (c) 2013 Quawcomm Athewos, Inc.
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

static void ath9k_tx99_stop(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath_dwain_aww_txq(sc);
	ath_stawtwecv(sc);

	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);

	ieee80211_wake_queues(sc->hw);

	kfwee_skb(sc->tx99_skb);
	sc->tx99_skb = NUWW;
	sc->tx99_state = fawse;

	ath9k_hw_tx99_stop(sc->sc_ah);
	ath_dbg(common, XMIT, "TX99 stopped\n");
}

static stwuct sk_buff *ath9k_buiwd_tx99_skb(stwuct ath_softc *sc)
{
	static u8 PN9Data[] = {0xff, 0x87, 0xb8, 0x59, 0xb7, 0xa1, 0xcc, 0x24,
			       0x57, 0x5e, 0x4b, 0x9c, 0x0e, 0xe9, 0xea, 0x50,
			       0x2a, 0xbe, 0xb4, 0x1b, 0xb6, 0xb0, 0x5d, 0xf1,
			       0xe6, 0x9a, 0xe3, 0x45, 0xfd, 0x2c, 0x53, 0x18,
			       0x0c, 0xca, 0xc9, 0xfb, 0x49, 0x37, 0xe5, 0xa8,
			       0x51, 0x3b, 0x2f, 0x61, 0xaa, 0x72, 0x18, 0x84,
			       0x02, 0x23, 0x23, 0xab, 0x63, 0x89, 0x51, 0xb3,
			       0xe7, 0x8b, 0x72, 0x90, 0x4c, 0xe8, 0xfb, 0xc0};
	u32 wen = 1200;
	stwuct ieee80211_tx_wate *wate;
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_tx_info *tx_info;
	stwuct sk_buff *skb;
	stwuct ath_vif *avp;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	skb_put(skb, wen);

	memset(skb->data, 0, wen);

	hdw = (stwuct ieee80211_hdw *)skb->data;
	hdw->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_DATA);
	hdw->duwation_id = 0;

	memcpy(hdw->addw1, hw->wiphy->pewm_addw, ETH_AWEN);
	memcpy(hdw->addw2, hw->wiphy->pewm_addw, ETH_AWEN);
	memcpy(hdw->addw3, hw->wiphy->pewm_addw, ETH_AWEN);

	if (sc->tx99_vif) {
		avp = (stwuct ath_vif *) sc->tx99_vif->dwv_pwiv;
		hdw->seq_ctww |= cpu_to_we16(avp->seq_no);
	}

	tx_info = IEEE80211_SKB_CB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	wate = &tx_info->contwow.wates[0];
	tx_info->band = sc->cuw_chan->chandef.chan->band;
	tx_info->fwags = IEEE80211_TX_CTW_NO_ACK;
	tx_info->contwow.vif = sc->tx99_vif;
	wate->count = 1;
	if (ah->cuwchan && IS_CHAN_HT(ah->cuwchan)) {
		wate->fwags |= IEEE80211_TX_WC_MCS;
		if (IS_CHAN_HT40(ah->cuwchan))
			wate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
	}

	memcpy(skb->data + sizeof(*hdw), PN9Data, sizeof(PN9Data));

	wetuwn skb;
}

static void ath9k_tx99_deinit(stwuct ath_softc *sc)
{
	ath_weset(sc, NUWW);

	ath9k_ps_wakeup(sc);
	ath9k_tx99_stop(sc);
	ath9k_ps_westowe(sc);
}

static int ath9k_tx99_init(stwuct ath_softc *sc)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_tx_contwow txctw;
	int w;

	if (test_bit(ATH_OP_INVAWID, &common->op_fwags)) {
		ath_eww(common,
			"dwivew is in invawid state unabwe to use TX99");
		wetuwn -EINVAW;
	}

	sc->tx99_skb = ath9k_buiwd_tx99_skb(sc);
	if (!sc->tx99_skb)
		wetuwn -ENOMEM;

	memset(&txctw, 0, sizeof(txctw));
	txctw.txq = sc->tx.txq_map[IEEE80211_AC_VO];

	ath_weset(sc, NUWW);

	ath9k_ps_wakeup(sc);

	ath9k_hw_disabwe_intewwupts(ah);
	ath_dwain_aww_txq(sc);
	ath_stopwecv(sc);

	sc->tx99_state = twue;

	ieee80211_stop_queues(hw);

	if (sc->tx99_powew == MAX_WATE_POWEW + 1)
		sc->tx99_powew = MAX_WATE_POWEW;

	ath9k_hw_tx99_set_txpowew(ah, sc->tx99_powew);
	w = ath9k_tx99_send(sc, sc->tx99_skb, &txctw);
	if (w) {
		ath_dbg(common, XMIT, "Faiwed to xmit TX99 skb\n");
		wetuwn w;
	}

	ath_dbg(common, XMIT, "TX99 xmit stawted using %d ( %ddBm)\n",
		sc->tx99_powew,
		sc->tx99_powew / 2);

	/* We weave the hawdwawe awake as it wiww be chugging on */

	wetuwn 0;
}

static ssize_t wead_fiwe_tx99(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	chaw buf[3];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", sc->tx99_state);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_tx99(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	boow stawt;
	ssize_t wet;
	int w;

	if (count < 1)
		wetuwn -EINVAW;

	if (sc->cuw_chan->nvifs > 1)
		wetuwn -EOPNOTSUPP;

	wet = kstwtoboow_fwom_usew(usew_buf, count, &stawt);
	if (wet)
		wetuwn wet;

	mutex_wock(&sc->mutex);

	if (stawt == sc->tx99_state) {
		if (!stawt)
			goto out;
		ath_dbg(common, XMIT, "Wesetting TX99\n");
		ath9k_tx99_deinit(sc);
	}

	if (!stawt) {
		ath9k_tx99_deinit(sc);
		goto out;
	}

	w = ath9k_tx99_init(sc);
	if (w) {
		mutex_unwock(&sc->mutex);
		wetuwn w;
	}
out:
	mutex_unwock(&sc->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations fops_tx99 = {
	.wead = wead_fiwe_tx99,
	.wwite = wwite_fiwe_tx99,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_tx99_powew(stwuct fiwe *fiwe,
				    chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d (%d dBm)\n",
		      sc->tx99_powew,
		      sc->tx99_powew / 2);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_tx99_powew(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	int w;
	u8 tx_powew;

	w = kstwtou8_fwom_usew(usew_buf, count, 0, &tx_powew);
	if (w)
		wetuwn w;

	if (tx_powew > MAX_WATE_POWEW)
		wetuwn -EINVAW;

	sc->tx99_powew = tx_powew;

	ath9k_ps_wakeup(sc);
	ath9k_hw_tx99_set_txpowew(sc->sc_ah, sc->tx99_powew);
	ath9k_ps_westowe(sc);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_tx99_powew = {
	.wead = wead_fiwe_tx99_powew,
	.wwite = wwite_fiwe_tx99_powew,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_tx99_init_debug(stwuct ath_softc *sc)
{
	if (!AW_SWEV_9280_20_OW_WATEW(sc->sc_ah))
		wetuwn;

	debugfs_cweate_fiwe("tx99", 0600,
			    sc->debug.debugfs_phy, sc,
			    &fops_tx99);
	debugfs_cweate_fiwe("tx99_powew", 0600,
			    sc->debug.debugfs_phy, sc,
			    &fops_tx99_powew);
}
