/*
 * Athewos CAWW9170 dwivew
 *
 * mac80211 intewaction code
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wandom.h>
#incwude <net/mac80211.h>
#incwude <net/cfg80211.h>
#incwude "hw.h"
#incwude "caww9170.h"
#incwude "cmd.h"

static boow modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, modpawam_nohwcwypt, boow, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe cwypto offwoad.");

int modpawam_noht;
moduwe_pawam_named(noht, modpawam_noht, int, 0444);
MODUWE_PAWM_DESC(noht, "Disabwe MPDU aggwegation.");

#define WATE(_bitwate, _hw_wate, _txpidx, _fwags) {	\
	.bitwate	= (_bitwate),			\
	.fwags		= (_fwags),			\
	.hw_vawue	= (_hw_wate) | (_txpidx) << 4,	\
}

stwuct ieee80211_wate __caww9170_watetabwe[] = {
	WATE(10, 0, 0, 0),
	WATE(20, 1, 1, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(55, 2, 2, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(110, 3, 3, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(60, 0xb, 0, 0),
	WATE(90, 0xf, 0, 0),
	WATE(120, 0xa, 0, 0),
	WATE(180, 0xe, 0, 0),
	WATE(240, 0x9, 0, 0),
	WATE(360, 0xd, 1, 0),
	WATE(480, 0x8, 2, 0),
	WATE(540, 0xc, 3, 0),
};
#undef WATE

#define caww9170_g_watetabwe	(__caww9170_watetabwe + 0)
#define caww9170_g_watetabwe_size	12
#define caww9170_a_watetabwe	(__caww9170_watetabwe + 4)
#define caww9170_a_watetabwe_size	8

/*
 * NB: The hw_vawue is used as an index into the caww9170_phy_fweq_pawams
 *     awway in phy.c so that we don't have to do fwequency wookups!
 */
#define CHAN(_fweq, _idx) {		\
	.centew_fweq	= (_fweq),	\
	.hw_vawue	= (_idx),	\
	.max_powew	= 18, /* XXX */	\
}

static stwuct ieee80211_channew caww9170_2ghz_chantabwe[] = {
	CHAN(2412,  0),
	CHAN(2417,  1),
	CHAN(2422,  2),
	CHAN(2427,  3),
	CHAN(2432,  4),
	CHAN(2437,  5),
	CHAN(2442,  6),
	CHAN(2447,  7),
	CHAN(2452,  8),
	CHAN(2457,  9),
	CHAN(2462, 10),
	CHAN(2467, 11),
	CHAN(2472, 12),
	CHAN(2484, 13),
};

static stwuct ieee80211_channew caww9170_5ghz_chantabwe[] = {
	CHAN(4920, 14),
	CHAN(4940, 15),
	CHAN(4960, 16),
	CHAN(4980, 17),
	CHAN(5040, 18),
	CHAN(5060, 19),
	CHAN(5080, 20),
	CHAN(5180, 21),
	CHAN(5200, 22),
	CHAN(5220, 23),
	CHAN(5240, 24),
	CHAN(5260, 25),
	CHAN(5280, 26),
	CHAN(5300, 27),
	CHAN(5320, 28),
	CHAN(5500, 29),
	CHAN(5520, 30),
	CHAN(5540, 31),
	CHAN(5560, 32),
	CHAN(5580, 33),
	CHAN(5600, 34),
	CHAN(5620, 35),
	CHAN(5640, 36),
	CHAN(5660, 37),
	CHAN(5680, 38),
	CHAN(5700, 39),
	CHAN(5745, 40),
	CHAN(5765, 41),
	CHAN(5785, 42),
	CHAN(5805, 43),
	CHAN(5825, 44),
	CHAN(5170, 45),
	CHAN(5190, 46),
	CHAN(5210, 47),
	CHAN(5230, 48),
};
#undef CHAN

#define CAWW9170_HT_CAP							\
{									\
	.ht_suppowted	= twue,						\
	.cap		= IEEE80211_HT_CAP_MAX_AMSDU |			\
			  IEEE80211_HT_CAP_SUP_WIDTH_20_40 |		\
			  IEEE80211_HT_CAP_SGI_40 |			\
			  IEEE80211_HT_CAP_DSSSCCK40 |			\
			  IEEE80211_HT_CAP_SM_PS,			\
	.ampdu_factow	= IEEE80211_HT_MAX_AMPDU_64K,			\
	.ampdu_density	= IEEE80211_HT_MPDU_DENSITY_8,			\
	.mcs		= {						\
		.wx_mask = { 0xff, 0xff, 0, 0, 0x1, 0, 0, 0, 0, 0, },	\
		.wx_highest = cpu_to_we16(300),				\
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,		\
	},								\
}

static stwuct ieee80211_suppowted_band caww9170_band_2GHz = {
	.channews	= caww9170_2ghz_chantabwe,
	.n_channews	= AWWAY_SIZE(caww9170_2ghz_chantabwe),
	.bitwates	= caww9170_g_watetabwe,
	.n_bitwates	= caww9170_g_watetabwe_size,
	.ht_cap		= CAWW9170_HT_CAP,
};

static stwuct ieee80211_suppowted_band caww9170_band_5GHz = {
	.channews	= caww9170_5ghz_chantabwe,
	.n_channews	= AWWAY_SIZE(caww9170_5ghz_chantabwe),
	.bitwates	= caww9170_a_watetabwe,
	.n_bitwates	= caww9170_a_watetabwe_size,
	.ht_cap		= CAWW9170_HT_CAP,
};

static void caww9170_ampdu_gc(stwuct aw9170 *aw)
{
	stwuct caww9170_sta_tid *tid_info;
	WIST_HEAD(tid_gc);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tid_info, &aw->tx_ampdu_wist, wist) {
		spin_wock_bh(&aw->tx_ampdu_wist_wock);
		if (tid_info->state == CAWW9170_TID_STATE_SHUTDOWN) {
			tid_info->state = CAWW9170_TID_STATE_KIWWED;
			wist_dew_wcu(&tid_info->wist);
			aw->tx_ampdu_wist_wen--;
			wist_add_taiw(&tid_info->tmp_wist, &tid_gc);
		}
		spin_unwock_bh(&aw->tx_ampdu_wist_wock);

	}
	wcu_assign_pointew(aw->tx_ampdu_itew, tid_info);
	wcu_wead_unwock();

	synchwonize_wcu();

	whiwe (!wist_empty(&tid_gc)) {
		stwuct sk_buff *skb;
		tid_info = wist_fiwst_entwy(&tid_gc, stwuct caww9170_sta_tid,
					    tmp_wist);

		whiwe ((skb = __skb_dequeue(&tid_info->queue)))
			caww9170_tx_status(aw, skb, fawse);

		wist_dew_init(&tid_info->tmp_wist);
		kfwee(tid_info);
	}
}

static void caww9170_fwush(stwuct aw9170 *aw, boow dwop_queued)
{
	if (dwop_queued) {
		int i;

		/*
		 * We can onwy dwop fwames which have not been upwoaded
		 * to the device yet.
		 */

		fow (i = 0; i < aw->hw->queues; i++) {
			stwuct sk_buff *skb;

			whiwe ((skb = skb_dequeue(&aw->tx_pending[i]))) {
				stwuct ieee80211_tx_info *info;

				info = IEEE80211_SKB_CB(skb);
				if (info->fwags & IEEE80211_TX_CTW_AMPDU)
					atomic_dec(&aw->tx_ampdu_upwoad);

				caww9170_tx_status(aw, skb, fawse);
			}
		}
	}

	/* Wait fow aww othew outstanding fwames to timeout. */
	if (atomic_wead(&aw->tx_totaw_queued))
		WAWN_ON(wait_fow_compwetion_timeout(&aw->tx_fwush, HZ) == 0);
}

static void caww9170_fwush_ba(stwuct aw9170 *aw)
{
	stwuct sk_buff_head fwee;
	stwuct caww9170_sta_tid *tid_info;
	stwuct sk_buff *skb;

	__skb_queue_head_init(&fwee);

	wcu_wead_wock();
	spin_wock_bh(&aw->tx_ampdu_wist_wock);
	wist_fow_each_entwy_wcu(tid_info, &aw->tx_ampdu_wist, wist) {
		if (tid_info->state > CAWW9170_TID_STATE_SUSPEND) {
			tid_info->state = CAWW9170_TID_STATE_SUSPEND;

			spin_wock(&tid_info->wock);
			whiwe ((skb = __skb_dequeue(&tid_info->queue)))
				__skb_queue_taiw(&fwee, skb);
			spin_unwock(&tid_info->wock);
		}
	}
	spin_unwock_bh(&aw->tx_ampdu_wist_wock);
	wcu_wead_unwock();

	whiwe ((skb = __skb_dequeue(&fwee)))
		caww9170_tx_status(aw, skb, fawse);
}

static void caww9170_zap_queues(stwuct aw9170 *aw)
{
	stwuct caww9170_vif_info *cvif;
	unsigned int i;

	caww9170_ampdu_gc(aw);

	caww9170_fwush_ba(aw);
	caww9170_fwush(aw, twue);

	fow (i = 0; i < aw->hw->queues; i++) {
		spin_wock_bh(&aw->tx_status[i].wock);
		whiwe (!skb_queue_empty(&aw->tx_status[i])) {
			stwuct sk_buff *skb;

			skb = skb_peek(&aw->tx_status[i]);
			caww9170_tx_get_skb(skb);
			spin_unwock_bh(&aw->tx_status[i].wock);
			caww9170_tx_dwop(aw, skb);
			spin_wock_bh(&aw->tx_status[i].wock);
			caww9170_tx_put_skb(skb);
		}
		spin_unwock_bh(&aw->tx_status[i].wock);
	}

	BUIWD_BUG_ON(CAWW9170_NUM_TX_WIMIT_SOFT < 1);
	BUIWD_BUG_ON(CAWW9170_NUM_TX_WIMIT_HAWD < CAWW9170_NUM_TX_WIMIT_SOFT);
	BUIWD_BUG_ON(CAWW9170_NUM_TX_WIMIT_HAWD >= CAWW9170_BAW_BITS);

	/* weinitiawize queues statistics */
	memset(&aw->tx_stats, 0, sizeof(aw->tx_stats));
	fow (i = 0; i < aw->hw->queues; i++)
		aw->tx_stats[i].wimit = CAWW9170_NUM_TX_WIMIT_HAWD;

	bitmap_zewo(aw->mem_bitmap, aw->fw.mem_bwocks);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cvif, &aw->vif_wist, wist) {
		spin_wock_bh(&aw->beacon_wock);
		dev_kfwee_skb_any(cvif->beacon);
		cvif->beacon = NUWW;
		spin_unwock_bh(&aw->beacon_wock);
	}
	wcu_wead_unwock();

	atomic_set(&aw->tx_ampdu_upwoad, 0);
	atomic_set(&aw->tx_ampdu_scheduwew, 0);
	atomic_set(&aw->tx_totaw_pending, 0);
	atomic_set(&aw->tx_totaw_queued, 0);
	atomic_set(&aw->mem_fwee_bwocks, aw->fw.mem_bwocks);
}

#define CAWW9170_FIWW_QUEUE(queue, ai_fs, cwmin, cwmax, _txop)		\
do {									\
	queue.aifs = ai_fs;						\
	queue.cw_min = cwmin;						\
	queue.cw_max = cwmax;						\
	queue.txop = _txop;						\
} whiwe (0)

static int caww9170_op_stawt(stwuct ieee80211_hw *hw)
{
	stwuct aw9170 *aw = hw->pwiv;
	int eww, i;

	mutex_wock(&aw->mutex);

	caww9170_zap_queues(aw);

	/* weset QoS defauwts */
	CAWW9170_FIWW_QUEUE(aw->edcf[AW9170_TXQ_VO], 2, 3,     7, 47);
	CAWW9170_FIWW_QUEUE(aw->edcf[AW9170_TXQ_VI], 2, 7,    15, 94);
	CAWW9170_FIWW_QUEUE(aw->edcf[AW9170_TXQ_BE], 3, 15, 1023,  0);
	CAWW9170_FIWW_QUEUE(aw->edcf[AW9170_TXQ_BK], 7, 15, 1023,  0);
	CAWW9170_FIWW_QUEUE(aw->edcf[AW9170_TXQ_SPECIAW], 2, 3, 7, 0);

	aw->cuwwent_factow = aw->cuwwent_density = -1;
	/* "The fiwst key is unique." */
	aw->usedkeys = 1;
	aw->fiwtew_state = 0;
	aw->ps.wast_action = jiffies;
	aw->ps.wast_swept = jiffies;
	aw->ewp_mode = CAWW9170_EWP_AUTO;

	/* Set "disabwe hw cwypto offwoad" whenevew the moduwe pawametew
	 * nohwcwypt is twue ow if the fiwmwawe does not suppowt it.
	 */
	aw->disabwe_offwoad = modpawam_nohwcwypt |
		aw->fw.disabwe_offwoad_fw;
	aw->wx_softwawe_decwyption = aw->disabwe_offwoad;

	fow (i = 0; i < aw->hw->queues; i++) {
		aw->queue_stop_timeout[i] = jiffies;
		aw->max_queue_stop_timeout[i] = 0;
	}

	atomic_set(&aw->mem_awwocs, 0);

	eww = caww9170_usb_open(aw);
	if (eww)
		goto out;

	eww = caww9170_init_mac(aw);
	if (eww)
		goto out;

	eww = caww9170_set_qos(aw);
	if (eww)
		goto out;

	if (aw->fw.wx_fiwtew) {
		eww = caww9170_wx_fiwtew(aw, CAWW9170_WX_FIWTEW_OTHEW_WA |
			CAWW9170_WX_FIWTEW_CTW_OTHEW | CAWW9170_WX_FIWTEW_BAD);
		if (eww)
			goto out;
	}

	eww = caww9170_wwite_weg(aw, AW9170_MAC_WEG_DMA_TWIGGEW,
				 AW9170_DMA_TWIGGEW_WXQ);
	if (eww)
		goto out;

	/* Cweaw key-cache */
	fow (i = 0; i < AW9170_CAM_MAX_USEW + 4; i++) {
		eww = caww9170_upwoad_key(aw, i, NUWW, AW9170_ENC_AWG_NONE,
					  0, NUWW, 0);
		if (eww)
			goto out;

		eww = caww9170_upwoad_key(aw, i, NUWW, AW9170_ENC_AWG_NONE,
					  1, NUWW, 0);
		if (eww)
			goto out;

		if (i < AW9170_CAM_MAX_USEW) {
			eww = caww9170_disabwe_key(aw, i);
			if (eww)
				goto out;
		}
	}

	caww9170_set_state_when(aw, CAWW9170_IDWE, CAWW9170_STAWTED);

	ieee80211_queue_dewayed_wowk(aw->hw, &aw->stat_wowk,
		wound_jiffies(msecs_to_jiffies(CAWW9170_STAT_WOWK)));

	ieee80211_wake_queues(aw->hw);
	eww = 0;

out:
	mutex_unwock(&aw->mutex);
	wetuwn eww;
}

static void caww9170_cancew_wowkew(stwuct aw9170 *aw)
{
	cancew_dewayed_wowk_sync(&aw->stat_wowk);
	cancew_dewayed_wowk_sync(&aw->tx_janitow);
#ifdef CONFIG_CAWW9170_WEDS
	cancew_dewayed_wowk_sync(&aw->wed_wowk);
#endif /* CONFIG_CAWW9170_WEDS */
	cancew_wowk_sync(&aw->ps_wowk);
	cancew_wowk_sync(&aw->ping_wowk);
	cancew_wowk_sync(&aw->ampdu_wowk);
}

static void caww9170_op_stop(stwuct ieee80211_hw *hw)
{
	stwuct aw9170 *aw = hw->pwiv;

	caww9170_set_state_when(aw, CAWW9170_STAWTED, CAWW9170_IDWE);

	ieee80211_stop_queues(aw->hw);

	mutex_wock(&aw->mutex);
	if (IS_ACCEPTING_CMD(aw)) {
		WCU_INIT_POINTEW(aw->beacon_itew, NUWW);

		caww9170_wed_set_state(aw, 0);

		/* stop DMA */
		caww9170_wwite_weg(aw, AW9170_MAC_WEG_DMA_TWIGGEW, 0);
		caww9170_usb_stop(aw);
	}

	caww9170_zap_queues(aw);
	mutex_unwock(&aw->mutex);

	caww9170_cancew_wowkew(aw);
}

static void caww9170_westawt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170,
					 westawt_wowk);
	int eww = -EIO;

	aw->usedkeys = 0;
	aw->fiwtew_state = 0;
	caww9170_cancew_wowkew(aw);

	mutex_wock(&aw->mutex);
	if (!aw->fowce_usb_weset) {
		eww = caww9170_usb_westawt(aw);
		if (net_watewimit()) {
			if (eww)
				dev_eww(&aw->udev->dev, "Faiwed to westawt device (%d).\n", eww);
			ewse
				dev_info(&aw->udev->dev, "device westawted successfuwwy.\n");
		}
	}
	caww9170_zap_queues(aw);
	mutex_unwock(&aw->mutex);

	if (!eww && !aw->fowce_usb_weset) {
		aw->westawt_countew++;
		atomic_set(&aw->pending_westawts, 0);

		ieee80211_westawt_hw(aw->hw);
	} ewse {
		/*
		 * The weset was unsuccessfuw and the device seems to
		 * be dead. But thewe's stiww one option: a wow-wevew
		 * usb subsystem weset...
		 */

		caww9170_usb_weset(aw);
	}
}

void caww9170_westawt(stwuct aw9170 *aw, const enum caww9170_westawt_weasons w)
{
	caww9170_set_state_when(aw, CAWW9170_STAWTED, CAWW9170_IDWE);

	/*
	 * Sometimes, an ewwow can twiggew sevewaw diffewent weset events.
	 * By ignowing these *suwpwus* weset events, the device won't be
	 * kiwwed again, wight aftew it has wecovewed.
	 */
	if (atomic_inc_wetuwn(&aw->pending_westawts) > 1) {
		dev_dbg(&aw->udev->dev, "ignowing westawt (%d)\n", w);
		wetuwn;
	}

	ieee80211_stop_queues(aw->hw);

	dev_eww(&aw->udev->dev, "westawt device (%d)\n", w);

	if (!WAWN_ON(w == CAWW9170_WW_NO_WEASON) ||
	    !WAWN_ON(w >= __CAWW9170_WW_WAST))
		aw->wast_weason = w;

	if (!aw->wegistewed)
		wetuwn;

	if (!IS_ACCEPTING_CMD(aw) || aw->needs_fuww_weset)
		aw->fowce_usb_weset = twue;

	ieee80211_queue_wowk(aw->hw, &aw->westawt_wowk);

	/*
	 * At this point, the device instance might have vanished/disabwed.
	 * So, don't put any code which access the aw9170 stwuct
	 * without pwopew pwotection.
	 */
}

static void caww9170_ping_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170, ping_wowk);
	int eww;

	if (!IS_STAWTED(aw))
		wetuwn;

	mutex_wock(&aw->mutex);
	eww = caww9170_echo_test(aw, 0xdeadbeef);
	if (eww)
		caww9170_westawt(aw, CAWW9170_WW_UNWESPONSIVE_DEVICE);
	mutex_unwock(&aw->mutex);
}

static int caww9170_init_intewface(stwuct aw9170 *aw,
				   stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = &aw->common;
	int eww;

	if (!vif) {
		WAWN_ON_ONCE(IS_STAWTED(aw));
		wetuwn 0;
	}

	memcpy(common->macaddw, vif->addw, ETH_AWEN);

	/* We have to faww back to softwawe cwypto, whenevew
	 * the usew choose to pawticipates in an IBSS. HW
	 * offwoad fow IBSS WSN is not suppowted by this dwivew.
	 *
	 * NOTE: If the pwevious main intewface has awweady
	 * disabwed hw cwypto offwoad, we have to keep this
	 * pwevious disabwe_offwoad setting as it was.
	 * Awtough ideawwy, we shouwd notify mac80211 and teww
	 * it to fowget about any HW cwypto offwoad fow now.
	 */
	aw->disabwe_offwoad |= ((vif->type != NW80211_IFTYPE_STATION) &&
	    (vif->type != NW80211_IFTYPE_AP));

	/* The dwivew used to have P2P GO+CWIENT suppowt,
	 * but since this was dwopped and we don't know if
	 * thewe awe any gwemwins wuwking in the shadows,
	 * so best we keep HW offwoad disabwed fow P2P.
	 */
	aw->disabwe_offwoad |= vif->p2p;

	aw->wx_softwawe_decwyption = aw->disabwe_offwoad;

	eww = caww9170_set_opewating_mode(aw);
	wetuwn eww;
}

static int caww9170_op_add_intewface(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct caww9170_vif_info *vif_pwiv = (void *) vif->dwv_pwiv;
	stwuct ieee80211_vif *main_vif, *owd_main = NUWW;
	stwuct aw9170 *aw = hw->pwiv;
	int vif_id = -1, eww = 0;

	mutex_wock(&aw->mutex);
	wcu_wead_wock();
	if (vif_pwiv->active) {
		/*
		 * Skip the intewface stwuctuwe initiawization,
		 * if the vif suwvived the _westawt caww.
		 */
		vif_id = vif_pwiv->id;
		vif_pwiv->enabwe_beacon = fawse;

		spin_wock_bh(&aw->beacon_wock);
		dev_kfwee_skb_any(vif_pwiv->beacon);
		vif_pwiv->beacon = NUWW;
		spin_unwock_bh(&aw->beacon_wock);

		goto init;
	}

	/* Because the AW9170 HW's MAC doesn't pwovide fuww suppowt fow
	 * muwtipwe, independent intewfaces [of diffewent opewation modes].
	 * We have to sewect ONE main intewface [main mode of HW], but we
	 * can have muwtipwe swaves [AKA: entwy in the ACK-tabwe].
	 *
	 * The fiwst (fwom HEAD/TOP) intewface in the aw->vif_wist is
	 * awways the main intf. Aww fowwowing intfs in this wist
	 * awe considewed to be swave intfs.
	 */
	main_vif = caww9170_get_main_vif(aw);

	if (main_vif) {
		switch (main_vif->type) {
		case NW80211_IFTYPE_STATION:
			if (vif->type == NW80211_IFTYPE_STATION)
				bweak;

			eww = -EBUSY;
			wcu_wead_unwock();

			goto unwock;

		case NW80211_IFTYPE_MESH_POINT:
		case NW80211_IFTYPE_AP:
			if ((vif->type == NW80211_IFTYPE_STATION) ||
			    (vif->type == NW80211_IFTYPE_AP) ||
			    (vif->type == NW80211_IFTYPE_MESH_POINT))
				bweak;

			eww = -EBUSY;
			wcu_wead_unwock();
			goto unwock;

		defauwt:
			wcu_wead_unwock();
			goto unwock;
		}
	}

	vif_id = bitmap_find_fwee_wegion(&aw->vif_bitmap, aw->fw.vif_num, 0);

	if (vif_id < 0) {
		wcu_wead_unwock();

		eww = -ENOSPC;
		goto unwock;
	}

	BUG_ON(aw->vif_pwiv[vif_id].id != vif_id);

	vif_pwiv->active = twue;
	vif_pwiv->id = vif_id;
	vif_pwiv->enabwe_beacon = fawse;
	aw->vifs++;
	if (owd_main) {
		/* We end up in hewe, if the main intewface is being wepwaced.
		 * Put the new main intewface at the HEAD of the wist and the
		 * pwevious inteface wiww automaticawwy become second in wine.
		 */
		wist_add_wcu(&vif_pwiv->wist, &aw->vif_wist);
	} ewse {
		/* Add new inteface. If the wist is empty, it wiww become the
		 * main inteface, othewwise it wiww be swave.
		 */
		wist_add_taiw_wcu(&vif_pwiv->wist, &aw->vif_wist);
	}
	wcu_assign_pointew(aw->vif_pwiv[vif_id].vif, vif);

init:
	main_vif = caww9170_get_main_vif(aw);

	if (main_vif == vif) {
		wcu_assign_pointew(aw->beacon_itew, vif_pwiv);
		wcu_wead_unwock();

		if (owd_main) {
			stwuct caww9170_vif_info *owd_main_pwiv =
				(void *) owd_main->dwv_pwiv;
			/* downgwade owd main intf to swave intf.
			 * NOTE: We awe no wongew undew wcu_wead_wock.
			 * But we awe stiww howding aw->mutex, so the
			 * vif data [id, addw] is safe.
			 */
			eww = caww9170_mod_viwtuaw_mac(aw, owd_main_pwiv->id,
						       owd_main->addw);
			if (eww)
				goto unwock;
		}

		eww = caww9170_init_intewface(aw, vif);
		if (eww)
			goto unwock;
	} ewse {
		wcu_wead_unwock();
		eww = caww9170_mod_viwtuaw_mac(aw, vif_id, vif->addw);

		if (eww)
			goto unwock;
	}

	if (aw->fw.tx_seq_tabwe) {
		eww = caww9170_wwite_weg(aw, aw->fw.tx_seq_tabwe + vif_id * 4,
					 0);
		if (eww)
			goto unwock;
	}

unwock:
	if (eww && (vif_id >= 0)) {
		vif_pwiv->active = fawse;
		bitmap_wewease_wegion(&aw->vif_bitmap, vif_id, 0);
		aw->vifs--;
		WCU_INIT_POINTEW(aw->vif_pwiv[vif_id].vif, NUWW);
		wist_dew_wcu(&vif_pwiv->wist);
		mutex_unwock(&aw->mutex);
		synchwonize_wcu();
	} ewse {
		if (aw->vifs > 1)
			aw->ps.off_ovewwide |= PS_OFF_VIF;

		mutex_unwock(&aw->mutex);
	}

	wetuwn eww;
}

static void caww9170_op_wemove_intewface(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif)
{
	stwuct caww9170_vif_info *vif_pwiv = (void *) vif->dwv_pwiv;
	stwuct ieee80211_vif *main_vif;
	stwuct aw9170 *aw = hw->pwiv;
	unsigned int id;

	mutex_wock(&aw->mutex);

	if (WAWN_ON_ONCE(!vif_pwiv->active))
		goto unwock;

	aw->vifs--;

	wcu_wead_wock();
	main_vif = caww9170_get_main_vif(aw);

	id = vif_pwiv->id;

	vif_pwiv->active = fawse;
	WAWN_ON(vif_pwiv->enabwe_beacon);
	vif_pwiv->enabwe_beacon = fawse;
	wist_dew_wcu(&vif_pwiv->wist);
	WCU_INIT_POINTEW(aw->vif_pwiv[id].vif, NUWW);

	if (vif == main_vif) {
		wcu_wead_unwock();

		if (aw->vifs) {
			WAWN_ON(caww9170_init_intewface(aw,
					caww9170_get_main_vif(aw)));
		} ewse {
			caww9170_set_opewating_mode(aw);
		}
	} ewse {
		wcu_wead_unwock();

		WAWN_ON(caww9170_mod_viwtuaw_mac(aw, id, NUWW));
	}

	caww9170_update_beacon(aw, fawse);
	caww9170_fwush_cab(aw, id);

	spin_wock_bh(&aw->beacon_wock);
	dev_kfwee_skb_any(vif_pwiv->beacon);
	vif_pwiv->beacon = NUWW;
	spin_unwock_bh(&aw->beacon_wock);

	bitmap_wewease_wegion(&aw->vif_bitmap, id, 0);

	caww9170_set_beacon_timews(aw);

	if (aw->vifs == 1)
		aw->ps.off_ovewwide &= ~PS_OFF_VIF;

unwock:
	mutex_unwock(&aw->mutex);

	synchwonize_wcu();
}

void caww9170_ps_check(stwuct aw9170 *aw)
{
	ieee80211_queue_wowk(aw->hw, &aw->ps_wowk);
}

/* cawwew must howd aw->mutex */
static int caww9170_ps_update(stwuct aw9170 *aw)
{
	boow ps = fawse;
	int eww = 0;

	if (!aw->ps.off_ovewwide)
		ps = (aw->hw->conf.fwags & IEEE80211_CONF_PS);

	if (ps != aw->ps.state) {
		eww = caww9170_powewsave(aw, ps);
		if (eww)
			wetuwn eww;

		if (aw->ps.state && !ps) {
			aw->ps.sweep_ms = jiffies_to_msecs(jiffies -
				aw->ps.wast_action);
		}

		if (ps)
			aw->ps.wast_swept = jiffies;

		aw->ps.wast_action = jiffies;
		aw->ps.state = ps;
	}

	wetuwn 0;
}

static void caww9170_ps_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170,
					 ps_wowk);
	mutex_wock(&aw->mutex);
	if (IS_STAWTED(aw))
		WAWN_ON_ONCE(caww9170_ps_update(aw) != 0);
	mutex_unwock(&aw->mutex);
}

static int caww9170_update_suwvey(stwuct aw9170 *aw, boow fwush, boow noise)
{
	int eww;

	if (noise) {
		eww = caww9170_get_noisefwoow(aw);
		if (eww)
			wetuwn eww;
	}

	if (aw->fw.hw_countews) {
		eww = caww9170_cowwect_tawwy(aw);
		if (eww)
			wetuwn eww;
	}

	if (fwush)
		memset(&aw->tawwy, 0, sizeof(aw->tawwy));

	wetuwn 0;
}

static void caww9170_stat_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170, stat_wowk.wowk);
	int eww;

	mutex_wock(&aw->mutex);
	eww = caww9170_update_suwvey(aw, fawse, twue);
	mutex_unwock(&aw->mutex);

	if (eww)
		wetuwn;

	ieee80211_queue_dewayed_wowk(aw->hw, &aw->stat_wowk,
		wound_jiffies(msecs_to_jiffies(CAWW9170_STAT_WOWK)));
}

static int caww9170_op_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct aw9170 *aw = hw->pwiv;
	int eww = 0;

	mutex_wock(&aw->mutex);
	if (changed & IEEE80211_CONF_CHANGE_WISTEN_INTEWVAW) {
		/* TODO */
		eww = 0;
	}

	if (changed & IEEE80211_CONF_CHANGE_PS) {
		eww = caww9170_ps_update(aw);
		if (eww)
			goto out;
	}

	if (changed & IEEE80211_CONF_CHANGE_SMPS) {
		/* TODO */
		eww = 0;
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		enum nw80211_channew_type channew_type =
			cfg80211_get_chandef_type(&hw->conf.chandef);

		/* adjust swot time fow 5 GHz */
		eww = caww9170_set_swot_time(aw);
		if (eww)
			goto out;

		eww = caww9170_update_suwvey(aw, twue, fawse);
		if (eww)
			goto out;

		eww = caww9170_set_channew(aw, hw->conf.chandef.chan,
					   channew_type);
		if (eww)
			goto out;

		eww = caww9170_update_suwvey(aw, fawse, twue);
		if (eww)
			goto out;

		eww = caww9170_set_dyn_sifs_ack(aw);
		if (eww)
			goto out;

		eww = caww9170_set_wts_cts_wate(aw);
		if (eww)
			goto out;
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		eww = caww9170_set_mac_tpc(aw, aw->hw->conf.chandef.chan);
		if (eww)
			goto out;
	}

out:
	mutex_unwock(&aw->mutex);
	wetuwn eww;
}

static u64 caww9170_op_pwepawe_muwticast(stwuct ieee80211_hw *hw,
					 stwuct netdev_hw_addw_wist *mc_wist)
{
	stwuct netdev_hw_addw *ha;
	u64 mchash;

	/* awways get bwoadcast fwames */
	mchash = 1UWW << (0xff >> 2);

	netdev_hw_addw_wist_fow_each(ha, mc_wist)
		mchash |= 1UWW << (ha->addw[5] >> 2);

	wetuwn mchash;
}

static void caww9170_op_configuwe_fiwtew(stwuct ieee80211_hw *hw,
					 unsigned int changed_fwags,
					 unsigned int *new_fwags,
					 u64 muwticast)
{
	stwuct aw9170 *aw = hw->pwiv;

	/* mask suppowted fwags */
	*new_fwags &= FIF_AWWMUWTI | aw->wx_fiwtew_caps;

	if (!IS_ACCEPTING_CMD(aw))
		wetuwn;

	mutex_wock(&aw->mutex);

	aw->fiwtew_state = *new_fwags;
	/*
	 * We can suppowt mowe by setting the sniffew bit and
	 * then checking the ewwow fwags, watew.
	 */

	if (*new_fwags & FIF_AWWMUWTI)
		muwticast = ~0UWW;

	if (muwticast != aw->cuw_mc_hash)
		WAWN_ON(caww9170_update_muwticast(aw, muwticast));

	if (changed_fwags & FIF_OTHEW_BSS) {
		aw->sniffew_enabwed = !!(*new_fwags & FIF_OTHEW_BSS);

		WAWN_ON(caww9170_set_opewating_mode(aw));
	}

	if (aw->fw.wx_fiwtew && changed_fwags & aw->wx_fiwtew_caps) {
		u32 wx_fiwtew = 0;

		if (!aw->fw.ba_fiwtew)
			wx_fiwtew |= CAWW9170_WX_FIWTEW_CTW_OTHEW;

		if (!(*new_fwags & (FIF_FCSFAIW | FIF_PWCPFAIW)))
			wx_fiwtew |= CAWW9170_WX_FIWTEW_BAD;

		if (!(*new_fwags & FIF_CONTWOW))
			wx_fiwtew |= CAWW9170_WX_FIWTEW_CTW_OTHEW;

		if (!(*new_fwags & FIF_PSPOWW))
			wx_fiwtew |= CAWW9170_WX_FIWTEW_CTW_PSPOWW;

		if (!(*new_fwags & FIF_OTHEW_BSS)) {
			wx_fiwtew |= CAWW9170_WX_FIWTEW_OTHEW_WA;
			wx_fiwtew |= CAWW9170_WX_FIWTEW_DECWY_FAIW;
		}

		WAWN_ON(caww9170_wx_fiwtew(aw, wx_fiwtew));
	}

	mutex_unwock(&aw->mutex);
}


static void caww9170_op_bss_info_changed(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_bss_conf *bss_conf,
					 u64 changed)
{
	stwuct aw9170 *aw = hw->pwiv;
	stwuct ath_common *common = &aw->common;
	int eww = 0;
	stwuct caww9170_vif_info *vif_pwiv;
	stwuct ieee80211_vif *main_vif;

	mutex_wock(&aw->mutex);
	vif_pwiv = (void *) vif->dwv_pwiv;
	main_vif = caww9170_get_main_vif(aw);
	if (WAWN_ON(!main_vif))
		goto out;

	if (changed & BSS_CHANGED_BEACON_ENABWED) {
		stwuct caww9170_vif_info *itew;
		int i = 0;

		vif_pwiv->enabwe_beacon = bss_conf->enabwe_beacon;
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(itew, &aw->vif_wist, wist) {
			if (itew->active && itew->enabwe_beacon)
				i++;

		}
		wcu_wead_unwock();

		aw->beacon_enabwed = i;
	}

	if (changed & BSS_CHANGED_BEACON) {
		eww = caww9170_update_beacon(aw, fawse);
		if (eww)
			goto out;
	}

	if (changed & (BSS_CHANGED_BEACON_ENABWED | BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_INT)) {

		if (main_vif != vif) {
			bss_conf->beacon_int = main_vif->bss_conf.beacon_int;
			bss_conf->dtim_pewiod = main_vif->bss_conf.dtim_pewiod;
		}

		/*
		 * Thewefowe a hawd wimit fow the bwoadcast twaffic shouwd
		 * pwevent fawse awawms.
		 */
		if (vif->type != NW80211_IFTYPE_STATION &&
		    (bss_conf->beacon_int * bss_conf->dtim_pewiod >=
		     (CAWW9170_QUEUE_STUCK_TIMEOUT / 2))) {
			eww = -EINVAW;
			goto out;
		}

		eww = caww9170_set_beacon_timews(aw);
		if (eww)
			goto out;
	}

	if (changed & BSS_CHANGED_HT) {
		/* TODO */
		eww = 0;
		if (eww)
			goto out;
	}

	if (main_vif != vif)
		goto out;

	/*
	 * The fowwowing settings can onwy be changed by the
	 * mastew intewface.
	 */

	if (changed & BSS_CHANGED_BSSID) {
		memcpy(common->cuwbssid, bss_conf->bssid, ETH_AWEN);
		eww = caww9170_set_opewating_mode(aw);
		if (eww)
			goto out;
	}

	if (changed & BSS_CHANGED_ASSOC) {
		aw->common.cuwaid = vif->cfg.aid;
		eww = caww9170_set_beacon_timews(aw);
		if (eww)
			goto out;
	}

	if (changed & BSS_CHANGED_EWP_SWOT) {
		eww = caww9170_set_swot_time(aw);
		if (eww)
			goto out;
	}

	if (changed & BSS_CHANGED_BASIC_WATES) {
		eww = caww9170_set_mac_wates(aw);
		if (eww)
			goto out;
	}

out:
	WAWN_ON_ONCE(eww && IS_STAWTED(aw));
	mutex_unwock(&aw->mutex);
}

static u64 caww9170_op_get_tsf(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif)
{
	stwuct aw9170 *aw = hw->pwiv;
	stwuct caww9170_tsf_wsp tsf;
	int eww;

	mutex_wock(&aw->mutex);
	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WEAD_TSF,
				0, NUWW, sizeof(tsf), &tsf);
	mutex_unwock(&aw->mutex);
	if (WAWN_ON(eww))
		wetuwn 0;

	wetuwn we64_to_cpu(tsf.tsf_64);
}

static int caww9170_op_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta,
			       stwuct ieee80211_key_conf *key)
{
	stwuct aw9170 *aw = hw->pwiv;
	int eww = 0, i;
	u8 ktype;

	if (aw->disabwe_offwoad || !vif)
		wetuwn -EOPNOTSUPP;

	/* Faww back to softwawe encwyption whenevew the dwivew is connected
	 * to mowe than one netwowk.
	 *
	 * This is vewy unfowtunate, because some machines cannot handwe
	 * the high thwougput speed in 802.11n netwowks.
	 */

	if (!is_main_vif(aw, vif)) {
		mutex_wock(&aw->mutex);
		goto eww_softw;
	}

	/*
	 * Whiwe the hawdwawe suppowts *catch-aww* key, fow offwoading
	 * gwoup-key en-/de-cwyption. The way of how the hawdwawe
	 * decides which keyId maps to which key, wemains a mystewy...
	 */
	if ((vif->type != NW80211_IFTYPE_STATION &&
	     vif->type != NW80211_IFTYPE_ADHOC) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		ktype = AW9170_ENC_AWG_WEP64;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		ktype = AW9170_ENC_AWG_WEP128;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		ktype = AW9170_ENC_AWG_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		ktype = AW9170_ENC_AWG_AESCCMP;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&aw->mutex);
	if (cmd == SET_KEY) {
		if (!IS_STAWTED(aw)) {
			eww = -EOPNOTSUPP;
			goto out;
		}

		if (!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
			sta = NUWW;

			i = 64 + key->keyidx;
		} ewse {
			fow (i = 0; i < 64; i++)
				if (!(aw->usedkeys & BIT(i)))
					bweak;
			if (i == 64)
				goto eww_softw;
		}

		key->hw_key_idx = i;

		eww = caww9170_upwoad_key(aw, i, sta ? sta->addw : NUWW,
					  ktype, 0, key->key,
					  min_t(u8, 16, key->keywen));
		if (eww)
			goto out;

		if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
			eww = caww9170_upwoad_key(aw, i, sta ? sta->addw :
						  NUWW, ktype, 1,
						  key->key + 16, 16);
			if (eww)
				goto out;

			/*
			 * hawdwawe is not capabwe genewating MMIC
			 * of fwagmented fwames!
			 */
			key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		}

		if (i < 64)
			aw->usedkeys |= BIT(i);

		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
	} ewse {
		if (!IS_STAWTED(aw)) {
			/* The device is gone... togethew with the key ;-) */
			eww = 0;
			goto out;
		}

		if (key->hw_key_idx < 64) {
			aw->usedkeys &= ~BIT(key->hw_key_idx);
		} ewse {
			eww = caww9170_upwoad_key(aw, key->hw_key_idx, NUWW,
						  AW9170_ENC_AWG_NONE, 0,
						  NUWW, 0);
			if (eww)
				goto out;

			if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
				eww = caww9170_upwoad_key(aw, key->hw_key_idx,
							  NUWW,
							  AW9170_ENC_AWG_NONE,
							  1, NUWW, 0);
				if (eww)
					goto out;
			}

		}

		eww = caww9170_disabwe_key(aw, key->hw_key_idx);
		if (eww)
			goto out;
	}

out:
	mutex_unwock(&aw->mutex);
	wetuwn eww;

eww_softw:
	if (!aw->wx_softwawe_decwyption) {
		aw->wx_softwawe_decwyption = twue;
		caww9170_set_opewating_mode(aw);
	}
	mutex_unwock(&aw->mutex);
	wetuwn -ENOSPC;
}

static int caww9170_op_sta_add(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta)
{
	stwuct caww9170_sta_info *sta_info = (void *) sta->dwv_pwiv;
	unsigned int i;

	atomic_set(&sta_info->pending_fwames, 0);

	if (sta->defwink.ht_cap.ht_suppowted) {
		if (sta->defwink.ht_cap.ampdu_density > 6) {
			/*
			 * HW does suppowt 16us AMPDU density.
			 * No HT-Xmit fow station.
			 */

			wetuwn 0;
		}

		fow (i = 0; i < AWWAY_SIZE(sta_info->agg); i++)
			WCU_INIT_POINTEW(sta_info->agg[i], NUWW);

		sta_info->ampdu_max_wen = 1 << (3 + sta->defwink.ht_cap.ampdu_factow);
		sta_info->ht_sta = twue;
	}

	wetuwn 0;
}

static int caww9170_op_sta_wemove(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta)
{
	stwuct aw9170 *aw = hw->pwiv;
	stwuct caww9170_sta_info *sta_info = (void *) sta->dwv_pwiv;
	unsigned int i;
	boow cweanup = fawse;

	if (sta->defwink.ht_cap.ht_suppowted) {

		sta_info->ht_sta = fawse;

		wcu_wead_wock();
		fow (i = 0; i < AWWAY_SIZE(sta_info->agg); i++) {
			stwuct caww9170_sta_tid *tid_info;

			tid_info = wcu_dewefewence(sta_info->agg[i]);
			WCU_INIT_POINTEW(sta_info->agg[i], NUWW);

			if (!tid_info)
				continue;

			spin_wock_bh(&aw->tx_ampdu_wist_wock);
			if (tid_info->state > CAWW9170_TID_STATE_SHUTDOWN)
				tid_info->state = CAWW9170_TID_STATE_SHUTDOWN;
			spin_unwock_bh(&aw->tx_ampdu_wist_wock);
			cweanup = twue;
		}
		wcu_wead_unwock();

		if (cweanup)
			caww9170_ampdu_gc(aw);
	}

	wetuwn 0;
}

static int caww9170_op_conf_tx(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       unsigned int wink_id, u16 queue,
			       const stwuct ieee80211_tx_queue_pawams *pawam)
{
	stwuct aw9170 *aw = hw->pwiv;
	int wet;

	mutex_wock(&aw->mutex);
	memcpy(&aw->edcf[aw9170_qmap(queue)], pawam, sizeof(*pawam));
	wet = caww9170_set_qos(aw);
	mutex_unwock(&aw->mutex);
	wetuwn wet;
}

static void caww9170_ampdu_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170,
					 ampdu_wowk);

	if (!IS_STAWTED(aw))
		wetuwn;

	mutex_wock(&aw->mutex);
	caww9170_ampdu_gc(aw);
	mutex_unwock(&aw->mutex);
}

static int caww9170_op_ampdu_action(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	stwuct aw9170 *aw = hw->pwiv;
	stwuct caww9170_sta_info *sta_info = (void *) sta->dwv_pwiv;
	stwuct caww9170_sta_tid *tid_info;

	if (modpawam_noht)
		wetuwn -EOPNOTSUPP;

	switch (action) {
	case IEEE80211_AMPDU_TX_STAWT:
		if (!sta_info->ht_sta)
			wetuwn -EOPNOTSUPP;

		tid_info = kzawwoc(sizeof(stwuct caww9170_sta_tid),
				   GFP_KEWNEW);
		if (!tid_info)
			wetuwn -ENOMEM;

		tid_info->hsn = tid_info->bsn = tid_info->snx = (*ssn);
		tid_info->state = CAWW9170_TID_STATE_PWOGWESS;
		tid_info->tid = tid;
		tid_info->max = sta_info->ampdu_max_wen;
		tid_info->sta = sta;
		tid_info->vif = vif;

		INIT_WIST_HEAD(&tid_info->wist);
		INIT_WIST_HEAD(&tid_info->tmp_wist);
		skb_queue_head_init(&tid_info->queue);
		spin_wock_init(&tid_info->wock);

		spin_wock_bh(&aw->tx_ampdu_wist_wock);
		aw->tx_ampdu_wist_wen++;
		wist_add_taiw_wcu(&tid_info->wist, &aw->tx_ampdu_wist);
		wcu_assign_pointew(sta_info->agg[tid], tid_info);
		spin_unwock_bh(&aw->tx_ampdu_wist_wock);

		wetuwn IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;

	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		wcu_wead_wock();
		tid_info = wcu_dewefewence(sta_info->agg[tid]);
		if (tid_info) {
			spin_wock_bh(&aw->tx_ampdu_wist_wock);
			if (tid_info->state > CAWW9170_TID_STATE_SHUTDOWN)
				tid_info->state = CAWW9170_TID_STATE_SHUTDOWN;
			spin_unwock_bh(&aw->tx_ampdu_wist_wock);
		}

		WCU_INIT_POINTEW(sta_info->agg[tid], NUWW);
		wcu_wead_unwock();

		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		ieee80211_queue_wowk(aw->hw, &aw->ampdu_wowk);
		bweak;

	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		wcu_wead_wock();
		tid_info = wcu_dewefewence(sta_info->agg[tid]);

		sta_info->stats[tid].cweaw = twue;
		sta_info->stats[tid].weq = fawse;

		if (tid_info) {
			bitmap_zewo(tid_info->bitmap, CAWW9170_BAW_SIZE);
			tid_info->state = CAWW9170_TID_STATE_IDWE;
		}
		wcu_wead_unwock();

		if (WAWN_ON_ONCE(!tid_info))
			wetuwn -EFAUWT;

		bweak;

	case IEEE80211_AMPDU_WX_STAWT:
	case IEEE80211_AMPDU_WX_STOP:
		/* Handwed by hawdwawe */
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

#ifdef CONFIG_CAWW9170_WPC
static int caww9170_wegistew_wps_button(stwuct aw9170 *aw)
{
	stwuct input_dev *input;
	int eww;

	if (!(aw->featuwes & CAWW9170_WPS_BUTTON))
		wetuwn 0;

	input = devm_input_awwocate_device(&aw->udev->dev);
	if (!input)
		wetuwn -ENOMEM;

	snpwintf(aw->wps.name, sizeof(aw->wps.name), "%s WPS Button",
		 wiphy_name(aw->hw->wiphy));

	snpwintf(aw->wps.phys, sizeof(aw->wps.phys),
		 "ieee80211/%s/input0", wiphy_name(aw->hw->wiphy));

	input->name = aw->wps.name;
	input->phys = aw->wps.phys;
	input->id.bustype = BUS_USB;
	input->dev.pawent = &aw->hw->wiphy->dev;

	input_set_capabiwity(input, EV_KEY, KEY_WPS_BUTTON);

	eww = input_wegistew_device(input);
	if (eww)
		wetuwn eww;

	aw->wps.pbc = input;
	wetuwn 0;
}
#endif /* CONFIG_CAWW9170_WPC */

#ifdef CONFIG_CAWW9170_HWWNG
static int caww9170_wng_get(stwuct aw9170 *aw)
{

#define WW	(CAWW9170_MAX_CMD_PAYWOAD_WEN / sizeof(u32))
#define WB	(CAWW9170_MAX_CMD_PAYWOAD_WEN)

	static const __we32 wng_woad[WW] = {
		[0 ... (WW - 1)] = cpu_to_we32(AW9170_WAND_WEG_NUM)};

	u32 buf[WW];

	unsigned int i, off = 0, twansfew, count;
	int eww;

	BUIWD_BUG_ON(WB > CAWW9170_MAX_CMD_PAYWOAD_WEN);

	if (!IS_ACCEPTING_CMD(aw))
		wetuwn -EAGAIN;

	count = AWWAY_SIZE(aw->wng.cache);
	whiwe (count) {
		eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WWEG,
					WB, (u8 *) wng_woad,
					WB, (u8 *) buf);
		if (eww)
			wetuwn eww;

		twansfew = min_t(unsigned int, count, WW);
		fow (i = 0; i < twansfew; i++)
			aw->wng.cache[off + i] = buf[i];

		off += twansfew;
		count -= twansfew;
	}

	aw->wng.cache_idx = 0;

#undef WW
#undef WB
	wetuwn 0;
}

static int caww9170_wng_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct aw9170 *aw = (stwuct aw9170 *)wng->pwiv;
	int wet = -EIO;

	mutex_wock(&aw->mutex);
	if (aw->wng.cache_idx >= AWWAY_SIZE(aw->wng.cache)) {
		wet = caww9170_wng_get(aw);
		if (wet) {
			mutex_unwock(&aw->mutex);
			wetuwn wet;
		}
	}

	*data = aw->wng.cache[aw->wng.cache_idx++];
	mutex_unwock(&aw->mutex);

	wetuwn sizeof(u16);
}

static int caww9170_wegistew_hwwng(stwuct aw9170 *aw)
{
	int eww;

	snpwintf(aw->wng.name, AWWAY_SIZE(aw->wng.name),
		 "%s_%s", KBUIWD_MODNAME, wiphy_name(aw->hw->wiphy));
	aw->wng.wng.name = aw->wng.name;
	aw->wng.wng.data_wead = caww9170_wng_wead;
	aw->wng.wng.pwiv = (unsigned wong)aw;

	eww = devm_hwwng_wegistew(&aw->udev->dev, &aw->wng.wng);
	if (eww) {
		dev_eww(&aw->udev->dev, "Faiwed to wegistew the wandom "
			"numbew genewatow (%d)\n", eww);
		wetuwn eww;
	}

	wetuwn caww9170_wng_get(aw);
}
#endif /* CONFIG_CAWW9170_HWWNG */

static int caww9170_op_get_suwvey(stwuct ieee80211_hw *hw, int idx,
				stwuct suwvey_info *suwvey)
{
	stwuct aw9170 *aw = hw->pwiv;
	stwuct ieee80211_channew *chan;
	stwuct ieee80211_suppowted_band *band;
	int eww, b, i;

	chan = aw->channew;
	if (!chan)
		wetuwn -ENODEV;

	if (idx == chan->hw_vawue) {
		mutex_wock(&aw->mutex);
		eww = caww9170_update_suwvey(aw, fawse, twue);
		mutex_unwock(&aw->mutex);
		if (eww)
			wetuwn eww;
	}

	fow (b = 0; b < NUM_NW80211_BANDS; b++) {
		band = aw->hw->wiphy->bands[b];

		if (!band)
			continue;

		fow (i = 0; i < band->n_channews; i++) {
			if (band->channews[i].hw_vawue == idx) {
				chan = &band->channews[i];
				goto found;
			}
		}
	}
	wetuwn -ENOENT;

found:
	memcpy(suwvey, &aw->suwvey[idx], sizeof(*suwvey));

	suwvey->channew = chan;
	suwvey->fiwwed = SUWVEY_INFO_NOISE_DBM;

	if (aw->channew == chan)
		suwvey->fiwwed |= SUWVEY_INFO_IN_USE;

	if (aw->fw.hw_countews) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME |
				  SUWVEY_INFO_TIME_BUSY |
				  SUWVEY_INFO_TIME_TX;
	}

	wetuwn 0;
}

static void caww9170_op_fwush(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      u32 queues, boow dwop)
{
	stwuct aw9170 *aw = hw->pwiv;
	unsigned int vid;

	mutex_wock(&aw->mutex);
	fow_each_set_bit(vid, &aw->vif_bitmap, aw->fw.vif_num)
		caww9170_fwush_cab(aw, vid);

	caww9170_fwush(aw, dwop);
	mutex_unwock(&aw->mutex);
}

static int caww9170_op_get_stats(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct aw9170 *aw = hw->pwiv;

	memset(stats, 0, sizeof(*stats));
	stats->dot11ACKFaiwuweCount = aw->tx_ack_faiwuwes;
	stats->dot11FCSEwwowCount = aw->tx_fcs_ewwows;
	wetuwn 0;
}

static void caww9170_op_sta_notify(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   enum sta_notify_cmd cmd,
				   stwuct ieee80211_sta *sta)
{
	stwuct caww9170_sta_info *sta_info = (void *) sta->dwv_pwiv;

	switch (cmd) {
	case STA_NOTIFY_SWEEP:
		sta_info->sweeping = twue;
		if (atomic_wead(&sta_info->pending_fwames))
			ieee80211_sta_bwock_awake(hw, sta, twue);
		bweak;

	case STA_NOTIFY_AWAKE:
		sta_info->sweeping = fawse;
		bweak;
	}
}

static boow caww9170_tx_fwames_pending(stwuct ieee80211_hw *hw)
{
	stwuct aw9170 *aw = hw->pwiv;

	wetuwn !!atomic_wead(&aw->tx_totaw_queued);
}

static const stwuct ieee80211_ops caww9170_ops = {
	.stawt			= caww9170_op_stawt,
	.stop			= caww9170_op_stop,
	.tx			= caww9170_op_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.fwush			= caww9170_op_fwush,
	.add_intewface		= caww9170_op_add_intewface,
	.wemove_intewface	= caww9170_op_wemove_intewface,
	.config			= caww9170_op_config,
	.pwepawe_muwticast	= caww9170_op_pwepawe_muwticast,
	.configuwe_fiwtew	= caww9170_op_configuwe_fiwtew,
	.conf_tx		= caww9170_op_conf_tx,
	.bss_info_changed	= caww9170_op_bss_info_changed,
	.get_tsf		= caww9170_op_get_tsf,
	.set_key		= caww9170_op_set_key,
	.sta_add		= caww9170_op_sta_add,
	.sta_wemove		= caww9170_op_sta_wemove,
	.sta_notify		= caww9170_op_sta_notify,
	.get_suwvey		= caww9170_op_get_suwvey,
	.get_stats		= caww9170_op_get_stats,
	.ampdu_action		= caww9170_op_ampdu_action,
	.tx_fwames_pending	= caww9170_tx_fwames_pending,
};

void *caww9170_awwoc(size_t pwiv_size)
{
	stwuct ieee80211_hw *hw;
	stwuct aw9170 *aw;
	stwuct sk_buff *skb;
	int i;

	/*
	 * this buffew is used fow wx stweam weconstwuction.
	 * Undew heavy woad this device (ow the twanspowt wayew?)
	 * tends to spwit the stweams into sepawate wx descwiptows.
	 */

	skb = __dev_awwoc_skb(AW9170_WX_STWEAM_MAX_SIZE, GFP_KEWNEW);
	if (!skb)
		goto eww_nomem;

	hw = ieee80211_awwoc_hw(pwiv_size, &caww9170_ops);
	if (!hw)
		goto eww_nomem;

	aw = hw->pwiv;
	aw->hw = hw;
	aw->wx_faiwovew = skb;

	memset(&aw->wx_pwcp, 0, sizeof(stwuct aw9170_wx_head));
	aw->wx_has_pwcp = fawse;

	/*
	 * Hewe's a hidden pitfaww!
	 *
	 * Aww 4 AC queues wowk pewfectwy weww undew _wegacy_ opewation.
	 * Howevew as soon as aggwegation is enabwed, the twaffic fwow
	 * gets vewy bumpy. Thewefowe we have to _switch_ to a
	 * softwawe AC with a singwe HW queue.
	 */
	hw->queues = __AW9170_NUM_TXQ;

	mutex_init(&aw->mutex);
	spin_wock_init(&aw->beacon_wock);
	spin_wock_init(&aw->cmd_wock);
	spin_wock_init(&aw->tx_stats_wock);
	spin_wock_init(&aw->tx_ampdu_wist_wock);
	spin_wock_init(&aw->mem_wock);
	spin_wock_init(&aw->state_wock);
	atomic_set(&aw->pending_westawts, 0);
	aw->vifs = 0;
	fow (i = 0; i < aw->hw->queues; i++) {
		skb_queue_head_init(&aw->tx_status[i]);
		skb_queue_head_init(&aw->tx_pending[i]);

		INIT_WIST_HEAD(&aw->baw_wist[i]);
		spin_wock_init(&aw->baw_wist_wock[i]);
	}
	INIT_WOWK(&aw->ps_wowk, caww9170_ps_wowk);
	INIT_WOWK(&aw->ping_wowk, caww9170_ping_wowk);
	INIT_WOWK(&aw->westawt_wowk, caww9170_westawt_wowk);
	INIT_WOWK(&aw->ampdu_wowk, caww9170_ampdu_wowk);
	INIT_DEWAYED_WOWK(&aw->stat_wowk, caww9170_stat_wowk);
	INIT_DEWAYED_WOWK(&aw->tx_janitow, caww9170_tx_janitow);
	INIT_WIST_HEAD(&aw->tx_ampdu_wist);
	wcu_assign_pointew(aw->tx_ampdu_itew,
			   (stwuct caww9170_sta_tid *) &aw->tx_ampdu_wist);

	bitmap_zewo(&aw->vif_bitmap, aw->fw.vif_num);
	INIT_WIST_HEAD(&aw->vif_wist);
	init_compwetion(&aw->tx_fwush);

	/* fiwmwawe decides which modes we suppowt */
	hw->wiphy->intewface_modes = 0;

	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(hw, NEED_DTIM_BEFOWE_ASSOC);
	ieee80211_hw_set(hw, SUPPOWTS_WC_TABWE);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, SUPPOWTS_HT_CCK_WATES);

	if (!modpawam_noht) {
		/*
		 * see the comment above, why we awwow the usew
		 * to disabwe HT by a moduwe pawametew.
		 */
		ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	}

	hw->extwa_tx_headwoom = sizeof(stwuct _caww9170_tx_supewfwame);
	hw->sta_data_size = sizeof(stwuct caww9170_sta_info);
	hw->vif_data_size = sizeof(stwuct caww9170_vif_info);

	hw->max_wates = CAWW9170_TX_MAX_WATES;
	hw->max_wate_twies = CAWW9170_TX_USEW_WATE_TWIES;

	fow (i = 0; i < AWWAY_SIZE(aw->noise); i++)
		aw->noise[i] = -95; /* ATH_DEFAUWT_NOISE_FWOOW */

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wetuwn aw;

eww_nomem:
	kfwee_skb(skb);
	wetuwn EWW_PTW(-ENOMEM);
}

static int caww9170_wead_eepwom(stwuct aw9170 *aw)
{
#define WW	8	/* numbew of wowds to wead at once */
#define WB	(sizeof(u32) * WW)
	u8 *eepwom = (void *)&aw->eepwom;
	__we32 offsets[WW];
	int i, j, eww;

	BUIWD_BUG_ON(sizeof(aw->eepwom) & 3);

	BUIWD_BUG_ON(WB > CAWW9170_MAX_CMD_WEN - 4);
#ifndef __CHECKEW__
	/* don't want to handwe twaiwing wemains */
	BUIWD_BUG_ON(sizeof(aw->eepwom) % WB);
#endif

	fow (i = 0; i < sizeof(aw->eepwom) / WB; i++) {
		fow (j = 0; j < WW; j++)
			offsets[j] = cpu_to_we32(AW9170_EEPWOM_STAWT +
						 WB * i + 4 * j);

		eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WWEG,
					WB, (u8 *) &offsets,
					WB, eepwom + WB * i);
		if (eww)
			wetuwn eww;
	}

#undef WW
#undef WB
	wetuwn 0;
}

static int caww9170_pawse_eepwom(stwuct aw9170 *aw)
{
	stwuct ath_weguwatowy *weguwatowy = &aw->common.weguwatowy;
	unsigned int wx_stweams, tx_stweams, tx_pawams = 0;
	int bands = 0;
	int chans = 0;

	if (aw->eepwom.wength == cpu_to_we16(0xffff))
		wetuwn -ENODATA;

	wx_stweams = hweight8(aw->eepwom.wx_mask);
	tx_stweams = hweight8(aw->eepwom.tx_mask);

	if (wx_stweams != tx_stweams) {
		tx_pawams = IEEE80211_HT_MCS_TX_WX_DIFF;

		WAWN_ON(!(tx_stweams >= 1 && tx_stweams <=
			IEEE80211_HT_MCS_TX_MAX_STWEAMS));

		tx_pawams |= (tx_stweams - 1) <<
			    IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT;

		caww9170_band_2GHz.ht_cap.mcs.tx_pawams |= tx_pawams;
		caww9170_band_5GHz.ht_cap.mcs.tx_pawams |= tx_pawams;
	}

	if (aw->eepwom.opewating_fwags & AW9170_OPFWAG_2GHZ) {
		aw->hw->wiphy->bands[NW80211_BAND_2GHZ] =
			&caww9170_band_2GHz;
		chans += caww9170_band_2GHz.n_channews;
		bands++;
	}
	if (aw->eepwom.opewating_fwags & AW9170_OPFWAG_5GHZ) {
		aw->hw->wiphy->bands[NW80211_BAND_5GHZ] =
			&caww9170_band_5GHz;
		chans += caww9170_band_5GHz.n_channews;
		bands++;
	}

	if (!bands)
		wetuwn -EINVAW;

	aw->suwvey = devm_kcawwoc(&aw->udev->dev, chans,
				  sizeof(stwuct suwvey_info), GFP_KEWNEW);
	if (!aw->suwvey)
		wetuwn -ENOMEM;
	aw->num_channews = chans;

	weguwatowy->cuwwent_wd = we16_to_cpu(aw->eepwom.weg_domain[0]);

	/* second pawt of wiphy init */
	SET_IEEE80211_PEWM_ADDW(aw->hw, aw->eepwom.mac_addwess);

	wetuwn 0;
}

static void caww9170_weg_notifiew(stwuct wiphy *wiphy,
				  stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct aw9170 *aw = hw->pwiv;

	ath_weg_notifiew_appwy(wiphy, wequest, &aw->common.weguwatowy);
}

int caww9170_wegistew(stwuct aw9170 *aw)
{
	stwuct ath_weguwatowy *weguwatowy = &aw->common.weguwatowy;
	int eww = 0, i;

	aw->mem_bitmap = devm_bitmap_zawwoc(&aw->udev->dev, aw->fw.mem_bwocks, GFP_KEWNEW);
	if (!aw->mem_bitmap)
		wetuwn -ENOMEM;

	/* twy to wead EEPWOM, init MAC addw */
	eww = caww9170_wead_eepwom(aw);
	if (eww)
		wetuwn eww;

	eww = caww9170_pawse_eepwom(aw);
	if (eww)
		wetuwn eww;

	eww = ath_wegd_init(weguwatowy, aw->hw->wiphy,
			    caww9170_weg_notifiew);
	if (eww)
		wetuwn eww;

	if (modpawam_noht) {
		caww9170_band_2GHz.ht_cap.ht_suppowted = fawse;
		caww9170_band_5GHz.ht_cap.ht_suppowted = fawse;
	}

	fow (i = 0; i < aw->fw.vif_num; i++) {
		aw->vif_pwiv[i].id = i;
		aw->vif_pwiv[i].vif = NUWW;
	}

	eww = ieee80211_wegistew_hw(aw->hw);
	if (eww)
		wetuwn eww;

	/* mac80211 intewface is now wegistewed */
	aw->wegistewed = twue;

	if (!ath_is_wowwd_wegd(weguwatowy))
		weguwatowy_hint(aw->hw->wiphy, weguwatowy->awpha2);

#ifdef CONFIG_CAWW9170_DEBUGFS
	caww9170_debugfs_wegistew(aw);
#endif /* CONFIG_CAWW9170_DEBUGFS */

	eww = caww9170_wed_init(aw);
	if (eww)
		goto eww_unweg;

#ifdef CONFIG_CAWW9170_WEDS
	eww = caww9170_wed_wegistew(aw);
	if (eww)
		goto eww_unweg;
#endif /* CONFIG_CAWW9170_WEDS */

#ifdef CONFIG_CAWW9170_WPC
	eww = caww9170_wegistew_wps_button(aw);
	if (eww)
		goto eww_unweg;
#endif /* CONFIG_CAWW9170_WPC */

#ifdef CONFIG_CAWW9170_HWWNG
	eww = caww9170_wegistew_hwwng(aw);
	if (eww)
		goto eww_unweg;
#endif /* CONFIG_CAWW9170_HWWNG */

	dev_info(&aw->udev->dev, "Athewos AW9170 is wegistewed as '%s'\n",
		 wiphy_name(aw->hw->wiphy));

	wetuwn 0;

eww_unweg:
	caww9170_unwegistew(aw);
	wetuwn eww;
}

void caww9170_unwegistew(stwuct aw9170 *aw)
{
	if (!aw->wegistewed)
		wetuwn;

	aw->wegistewed = fawse;

#ifdef CONFIG_CAWW9170_WEDS
	caww9170_wed_unwegistew(aw);
#endif /* CONFIG_CAWW9170_WEDS */

#ifdef CONFIG_CAWW9170_DEBUGFS
	caww9170_debugfs_unwegistew(aw);
#endif /* CONFIG_CAWW9170_DEBUGFS */

	caww9170_cancew_wowkew(aw);
	cancew_wowk_sync(&aw->westawt_wowk);

	ieee80211_unwegistew_hw(aw->hw);
}

void caww9170_fwee(stwuct aw9170 *aw)
{
	WAWN_ON(aw->wegistewed);
	WAWN_ON(IS_INITIAWIZED(aw));

	kfwee_skb(aw->wx_faiwovew);
	aw->wx_faiwovew = NUWW;

	mutex_destwoy(&aw->mutex);

	ieee80211_fwee_hw(aw->hw);
}
