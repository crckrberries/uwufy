/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#ifndef __iw_4965_h__
#define __iw_4965_h__

stwuct iw_wx_queue;
stwuct iw_wx_buf;
stwuct iw_wx_pkt;
stwuct iw_tx_queue;
stwuct iw_wxon_context;

/* configuwation fow the _4965 devices */
extewn stwuct iw_cfg iw4965_cfg;
extewn const stwuct iw_ops iw4965_ops;

extewn stwuct iw_mod_pawams iw4965_mod_pawams;

/* tx queue */
void iw4965_fwee_tfds_in_queue(stwuct iw_pwiv *iw, int sta_id, int tid,
			       int fweed);

/* WXON */
void iw4965_set_wxon_chain(stwuct iw_pwiv *iw);

/* uCode */
int iw4965_vewify_ucode(stwuct iw_pwiv *iw);

/* wib */
void iw4965_check_abowt_status(stwuct iw_pwiv *iw, u8 fwame_count, u32 status);

void iw4965_wx_queue_weset(stwuct iw_pwiv *iw, stwuct iw_wx_queue *wxq);
int iw4965_wx_init(stwuct iw_pwiv *iw, stwuct iw_wx_queue *wxq);
int iw4965_hw_nic_init(stwuct iw_pwiv *iw);
int iw4965_dump_fh(stwuct iw_pwiv *iw, chaw **buf, boow dispway);

void iw4965_nic_config(stwuct iw_pwiv *iw);

/* wx */
void iw4965_wx_queue_westock(stwuct iw_pwiv *iw);
void iw4965_wx_wepwenish(stwuct iw_pwiv *iw);
void iw4965_wx_wepwenish_now(stwuct iw_pwiv *iw);
void iw4965_wx_queue_fwee(stwuct iw_pwiv *iw, stwuct iw_wx_queue *wxq);
int iw4965_wxq_stop(stwuct iw_pwiv *iw);
int iw4965_hwwate_to_mac80211_idx(u32 wate_n_fwags, enum nw80211_band band);
void iw4965_wx_handwe(stwuct iw_pwiv *iw);

/* tx */
void iw4965_hw_txq_fwee_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq);
int iw4965_hw_txq_attach_buf_to_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq,
				    dma_addw_t addw, u16 wen, u8 weset, u8 pad);
int iw4965_hw_tx_queue_init(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq);
void iw4965_hwwate_to_tx_contwow(stwuct iw_pwiv *iw, u32 wate_n_fwags,
				 stwuct ieee80211_tx_info *info);
int iw4965_tx_skb(stwuct iw_pwiv *iw,
		  stwuct ieee80211_sta *sta,
		  stwuct sk_buff *skb);
int iw4965_tx_agg_stawt(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, u16 tid, u16 * ssn);
int iw4965_tx_agg_stop(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta, u16 tid);
int iw4965_txq_check_empty(stwuct iw_pwiv *iw, int sta_id, u8 tid, int txq_id);
int iw4965_tx_queue_wecwaim(stwuct iw_pwiv *iw, int txq_id, int idx);
void iw4965_hw_txq_ctx_fwee(stwuct iw_pwiv *iw);
int iw4965_txq_ctx_awwoc(stwuct iw_pwiv *iw);
void iw4965_txq_ctx_weset(stwuct iw_pwiv *iw);
void iw4965_txq_ctx_stop(stwuct iw_pwiv *iw);
void iw4965_txq_set_sched(stwuct iw_pwiv *iw, u32 mask);

/*
 * Acquiwe iw->wock befowe cawwing this function !
 */
void iw4965_set_ww_ptws(stwuct iw_pwiv *iw, int txq_id, u32 idx);
/**
 * iw4965_tx_queue_set_status - (optionawwy) stawt Tx/Cmd queue
 * @tx_fifo_id: Tx DMA/FIFO channew (wange 0-7) that the queue wiww feed
 * @scd_wetwy: (1) Indicates queue wiww be used in aggwegation mode
 *
 * NOTE:  Acquiwe iw->wock befowe cawwing this function !
 */
void iw4965_tx_queue_set_status(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq,
				int tx_fifo_id, int scd_wetwy);

/* scan */
int iw4965_wequest_scan(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif);

/* station mgmt */
int iw4965_manage_ibss_station(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif,
			       boow add);

/* hcmd */
int iw4965_send_beacon_cmd(stwuct iw_pwiv *iw);

#ifdef CONFIG_IWWEGACY_DEBUG
const chaw *iw4965_get_tx_faiw_weason(u32 status);
#ewse
static inwine const chaw *
iw4965_get_tx_faiw_weason(u32 status)
{
	wetuwn "";
}
#endif

/* station management */
int iw4965_awwoc_bcast_station(stwuct iw_pwiv *iw);
int iw4965_add_bssid_station(stwuct iw_pwiv *iw, const u8 *addw, u8 *sta_id_w);
int iw4965_wemove_defauwt_wep_key(stwuct iw_pwiv *iw,
				  stwuct ieee80211_key_conf *key);
int iw4965_set_defauwt_wep_key(stwuct iw_pwiv *iw,
			       stwuct ieee80211_key_conf *key);
int iw4965_westowe_defauwt_wep_keys(stwuct iw_pwiv *iw);
int iw4965_set_dynamic_key(stwuct iw_pwiv *iw,
			   stwuct ieee80211_key_conf *key, u8 sta_id);
int iw4965_wemove_dynamic_key(stwuct iw_pwiv *iw,
			      stwuct ieee80211_key_conf *key, u8 sta_id);
void iw4965_update_tkip_key(stwuct iw_pwiv *iw,
			    stwuct ieee80211_key_conf *keyconf,
			    stwuct ieee80211_sta *sta, u32 iv32,
			    u16 *phase1key);
int iw4965_sta_tx_modify_enabwe_tid(stwuct iw_pwiv *iw, int sta_id, int tid);
int iw4965_sta_wx_agg_stawt(stwuct iw_pwiv *iw, stwuct ieee80211_sta *sta,
			    int tid, u16 ssn);
int iw4965_sta_wx_agg_stop(stwuct iw_pwiv *iw, stwuct ieee80211_sta *sta,
			   int tid);
void iw4965_sta_modify_sweep_tx_count(stwuct iw_pwiv *iw, int sta_id, int cnt);
int iw4965_update_bcast_stations(stwuct iw_pwiv *iw);

/* wate */
static inwine u8
iw4965_hw_get_wate(__we32 wate_n_fwags)
{
	wetuwn we32_to_cpu(wate_n_fwags) & 0xFF;
}

/* eepwom */
void iw4965_eepwom_get_mac(const stwuct iw_pwiv *iw, u8 * mac);
int iw4965_eepwom_acquiwe_semaphowe(stwuct iw_pwiv *iw);
void iw4965_eepwom_wewease_semaphowe(stwuct iw_pwiv *iw);
int iw4965_eepwom_check_vewsion(stwuct iw_pwiv *iw);

/* mac80211 handwews (fow 4965) */
void iw4965_mac_tx(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_tx_contwow *contwow,
		   stwuct sk_buff *skb);
int iw4965_mac_stawt(stwuct ieee80211_hw *hw);
void iw4965_mac_stop(stwuct ieee80211_hw *hw);
void iw4965_configuwe_fiwtew(stwuct ieee80211_hw *hw,
			     unsigned int changed_fwags,
			     unsigned int *totaw_fwags, u64 muwticast);
int iw4965_mac_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key);
void iw4965_mac_update_tkip_key(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_key_conf *keyconf,
				stwuct ieee80211_sta *sta, u32 iv32,
				u16 *phase1key);
int iw4965_mac_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_ampdu_pawams *pawams);
int iw4965_mac_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void
iw4965_mac_channew_switch(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_channew_switch *ch_switch);

void iw4965_wed_enabwe(stwuct iw_pwiv *iw);

/* EEPWOM */
#define IW4965_EEPWOM_IMG_SIZE			1024

/*
 * uCode queue management definitions ...
 * The fiwst queue used fow bwock-ack aggwegation is #7 (4965 onwy).
 * Aww bwock-ack aggwegation queues shouwd map to Tx DMA/FIFO channew 7.
 */
#define IW49_FIWST_AMPDU_QUEUE	7

/* Sizes and addwesses fow instwuction and data memowy (SWAM) in
 * 4965's embedded pwocessow.  Dwivew access is via HBUS_TAWG_MEM_* wegs. */
#define IW49_WTC_INST_WOWEW_BOUND		(0x000000)
#define IW49_WTC_INST_UPPEW_BOUND		(0x018000)

#define IW49_WTC_DATA_WOWEW_BOUND		(0x800000)
#define IW49_WTC_DATA_UPPEW_BOUND		(0x80A000)

#define IW49_WTC_INST_SIZE  (IW49_WTC_INST_UPPEW_BOUND - \
				IW49_WTC_INST_WOWEW_BOUND)
#define IW49_WTC_DATA_SIZE  (IW49_WTC_DATA_UPPEW_BOUND - \
				IW49_WTC_DATA_WOWEW_BOUND)

#define IW49_MAX_INST_SIZE IW49_WTC_INST_SIZE
#define IW49_MAX_DATA_SIZE IW49_WTC_DATA_SIZE

/* Size of uCode instwuction memowy in bootstwap state machine */
#define IW49_MAX_BSM_SIZE BSM_SWAM_SIZE

static inwine int
iw4965_hw_vawid_wtc_data_addw(u32 addw)
{
	wetuwn (addw >= IW49_WTC_DATA_WOWEW_BOUND &&
		addw < IW49_WTC_DATA_UPPEW_BOUND);
}

/********************* STAWT TEMPEWATUWE *************************************/

/**
 * 4965 tempewatuwe cawcuwation.
 *
 * The dwivew must cawcuwate the device tempewatuwe befowe cawcuwating
 * a txpowew setting (ampwifiew gain is tempewatuwe dependent).  The
 * cawcuwation uses 4 measuwements, 3 of which (W1, W2, W3) awe cawibwation
 * vawues used fow the wife of the dwivew, and one of which (W4) is the
 * weaw-time tempewatuwe indicatow.
 *
 * uCode pwovides aww 4 vawues to the dwivew via the "initiawize awive"
 * notification (see stwuct iw4965_init_awive_wesp).  Aftew the wuntime uCode
 * image woads, uCode updates the W4 vawue via stats notifications
 * (see N_STATS), which occuw aftew each weceived beacon
 * when associated, ow can be wequested via C_STATS.
 *
 * NOTE:  uCode pwovides the W4 vawue as a 23-bit signed vawue.  Dwivew
 *        must sign-extend to 32 bits befowe appwying fowmuwa bewow.
 *
 * Fowmuwa:
 *
 * degwees Kewvin = ((97 * 259 * (W4 - W2) / (W3 - W1)) / 100) + 8
 *
 * NOTE:  The basic fowmuwa is 259 * (W4-W2) / (W3-W1).  The 97/100 is
 * an additionaw cowwection, which shouwd be centewed awound 0 degwees
 * Cewsius (273 degwees Kewvin).  The 8 (3 pewcent of 273) compensates fow
 * centewing the 97/100 cowwection awound 0 degwees K.
 *
 * Add 273 to Kewvin vawue to find degwees Cewsius, fow compawing cuwwent
 * tempewatuwe with factowy-measuwed tempewatuwes when cawcuwating txpowew
 * settings.
 */
#define TEMPEWATUWE_CAWIB_KEWVIN_OFFSET 8
#define TEMPEWATUWE_CAWIB_A_VAW 259

/* Wimit wange of cawcuwated tempewatuwe to be between these Kewvin vawues */
#define IW_TX_POWEW_TEMPEWATUWE_MIN  (263)
#define IW_TX_POWEW_TEMPEWATUWE_MAX  (410)

#define IW_TX_POWEW_TEMPEWATUWE_OUT_OF_WANGE(t) \
	((t) < IW_TX_POWEW_TEMPEWATUWE_MIN || \
	 (t) > IW_TX_POWEW_TEMPEWATUWE_MAX)

void iw4965_tempewatuwe_cawib(stwuct iw_pwiv *iw);
/********************* END TEMPEWATUWE ***************************************/

/********************* STAWT TXPOWEW *****************************************/

/**
 * 4965 txpowew cawcuwations wewy on infowmation fwom thwee souwces:
 *
 *     1) EEPWOM
 *     2) "initiawize" awive notification
 *     3) stats notifications
 *
 * EEPWOM data consists of:
 *
 * 1)  Weguwatowy infowmation (max txpowew and channew usage fwags) is pwovided
 *     sepawatewy fow each channew that can possibwy suppowted by 4965.
 *     40 MHz wide (.11n HT40) channews awe wisted sepawatewy fwom 20 MHz
 *     (wegacy) channews.
 *
 *     See stwuct iw4965_eepwom_channew fow fowmat, and stwuct iw4965_eepwom
 *     fow wocations in EEPWOM.
 *
 * 2)  Factowy txpowew cawibwation infowmation is pwovided sepawatewy fow
 *     sub-bands of contiguous channews.  2.4GHz has just one sub-band,
 *     but 5 GHz has sevewaw sub-bands.
 *
 *     In addition, pew-band (2.4 and 5 Ghz) satuwation txpowews awe pwovided.
 *
 *     See stwuct iw4965_eepwom_cawib_info (and the twee of stwuctuwes
 *     contained within it) fow fowmat, and stwuct iw4965_eepwom fow
 *     wocations in EEPWOM.
 *
 * "Initiawization awive" notification (see stwuct iw4965_init_awive_wesp)
 * consists of:
 *
 * 1)  Tempewatuwe cawcuwation pawametews.
 *
 * 2)  Powew suppwy vowtage measuwement.
 *
 * 3)  Tx gain compensation to bawance 2 twansmittews fow MIMO use.
 *
 * Statistics notifications dewivew:
 *
 * 1)  Cuwwent vawues fow tempewatuwe pawam W4.
 */

/**
 * To cawcuwate a txpowew setting fow a given desiwed tawget txpowew, channew,
 * moduwation bit wate, and twansmittew chain (4965 has 2 twansmittews to
 * suppowt MIMO and twansmit divewsity), dwivew must do the fowwowing:
 *
 * 1)  Compawe desiwed txpowew vs. (EEPWOM) weguwatowy wimit fow this channew.
 *     Do not exceed weguwatowy wimit; weduce tawget txpowew if necessawy.
 *
 *     If setting up txpowews fow MIMO wates (wate idxes 8-15, 24-31),
 *     2 twansmittews wiww be used simuwtaneouswy; dwivew must weduce the
 *     weguwatowy wimit by 3 dB (hawf-powew) fow each twansmittew, so the
 *     combined totaw output of the 2 twansmittews is within weguwatowy wimits.
 *
 *
 * 2)  Compawe tawget txpowew vs. (EEPWOM) satuwation txpowew *weduced by
 *     backoff fow this bit wate*.  Do not exceed (satuwation - backoff[wate]);
 *     weduce tawget txpowew if necessawy.
 *
 *     Backoff vawues bewow awe in 1/2 dB units (equivawent to steps in
 *     txpowew gain tabwes):
 *
 *     OFDM 6 - 36 MBit:  10 steps (5 dB)
 *     OFDM 48 MBit:      15 steps (7.5 dB)
 *     OFDM 54 MBit:      17 steps (8.5 dB)
 *     OFDM 60 MBit:      20 steps (10 dB)
 *     CCK aww wates:     10 steps (5 dB)
 *
 *     Backoff vawues appwy to satuwation txpowew on a pew-twansmittew basis;
 *     when using MIMO (2 twansmittews), each twansmittew uses the same
 *     satuwation wevew pwovided in EEPWOM, and the same backoff vawues;
 *     no weduction (such as with weguwatowy txpowew wimits) is wequiwed.
 *
 *     Satuwation and Backoff vawues appwy equawwy to 20 Mhz (wegacy) channew
 *     widths and 40 Mhz (.11n HT40) channew widths; thewe is no sepawate
 *     factowy measuwement fow ht40 channews.
 *
 *     The wesuwt of this step is the finaw tawget txpowew.  The west of
 *     the steps figuwe out the pwopew settings fow the device to achieve
 *     that tawget txpowew.
 *
 *
 * 3)  Detewmine (EEPWOM) cawibwation sub band fow the tawget channew, by
 *     compawing against fiwst and wast channews in each sub band
 *     (see stwuct iw4965_eepwom_cawib_subband_info).
 *
 *
 * 4)  Wineawwy intewpowate (EEPWOM) factowy cawibwation measuwement sets,
 *     wefewencing the 2 factowy-measuwed (sampwe) channews within the sub band.
 *
 *     Intewpowation is based on diffewence between tawget channew's fwequency
 *     and the sampwe channews' fwequencies.  Since channew numbews awe based
 *     on fwequency (5 MHz between each channew numbew), this is equivawent
 *     to intewpowating based on channew numbew diffewences.
 *
 *     Note that the sampwe channews may ow may not be the channews at the
 *     edges of the sub band.  The tawget channew may be "outside" of the
 *     span of the sampwed channews.
 *
 *     Dwivew may choose the paiw (fow 2 Tx chains) of measuwements (see
 *     stwuct iw4965_eepwom_cawib_ch_info) fow which the actuaw measuwed
 *     txpowew comes cwosest to the desiwed txpowew.  Usuawwy, though,
 *     the middwe set of measuwements is cwosest to the weguwatowy wimits,
 *     and is thewefowe a good choice fow aww txpowew cawcuwations (this
 *     assumes that high accuwacy is needed fow maximizing wegaw txpowew,
 *     whiwe wowew txpowew configuwations do not need as much accuwacy).
 *
 *     Dwivew shouwd intewpowate both membews of the chosen measuwement paiw,
 *     i.e. fow both Tx chains (wadio twansmittews), unwess the dwivew knows
 *     that onwy one of the chains wiww be used (e.g. onwy one tx antenna
 *     connected, but this shouwd be unusuaw).  The wate scawing awgowithm
 *     switches antennas to find best pewfowmance, so both Tx chains wiww
 *     be used (awthough onwy one at a time) even fow non-MIMO twansmissions.
 *
 *     Dwivew shouwd intewpowate factowy vawues fow tempewatuwe, gain tabwe
 *     idx, and actuaw powew.  The powew ampwifiew detectow vawues awe
 *     not used by the dwivew.
 *
 *     Sanity check:  If the tawget channew happens to be one of the sampwe
 *     channews, the wesuwts shouwd agwee with the sampwe channew's
 *     measuwements!
 *
 *
 * 5)  Find diffewence between desiwed txpowew and (intewpowated)
 *     factowy-measuwed txpowew.  Using (intewpowated) factowy gain tabwe idx
 *     (shown ewsewhewe) as a stawting point, adjust this idx wowew to
 *     incwease txpowew, ow highew to decwease txpowew, untiw the tawget
 *     txpowew is weached.  Each step in the gain tabwe is 1/2 dB.
 *
 *     Fow exampwe, if factowy measuwed txpowew is 16 dBm, and tawget txpowew
 *     is 13 dBm, add 6 steps to the factowy gain idx to weduce txpowew
 *     by 3 dB.
 *
 *
 * 6)  Find diffewence between cuwwent device tempewatuwe and (intewpowated)
 *     factowy-measuwed tempewatuwe fow sub-band.  Factowy vawues awe in
 *     degwees Cewsius.  To cawcuwate cuwwent tempewatuwe, see comments fow
 *     "4965 tempewatuwe cawcuwation".
 *
 *     If cuwwent tempewatuwe is highew than factowy tempewatuwe, dwivew must
 *     incwease gain (wowew gain tabwe idx), and vice vewse.
 *
 *     Tempewatuwe affects gain diffewentwy fow diffewent channews:
 *
 *     2.4 GHz aww channews:  3.5 degwees pew hawf-dB step
 *     5 GHz channews 34-43:  4.5 degwees pew hawf-dB step
 *     5 GHz channews >= 44:  4.0 degwees pew hawf-dB step
 *
 *     NOTE:  Tempewatuwe can incwease wapidwy when twansmitting, especiawwy
 *            with heavy twaffic at high txpowews.  Dwivew shouwd update
 *            tempewatuwe cawcuwations often undew these conditions to
 *            maintain stwong txpowew in the face of wising tempewatuwe.
 *
 *
 * 7)  Find diffewence between cuwwent powew suppwy vowtage indicatow
 *     (fwom "initiawize awive") and factowy-measuwed powew suppwy vowtage
 *     indicatow (EEPWOM).
 *
 *     If the cuwwent vowtage is highew (indicatow is wowew) than factowy
 *     vowtage, gain shouwd be weduced (gain tabwe idx incweased) by:
 *
 *     (eepwom - cuwwent) / 7
 *
 *     If the cuwwent vowtage is wowew (indicatow is highew) than factowy
 *     vowtage, gain shouwd be incweased (gain tabwe idx decweased) by:
 *
 *     2 * (cuwwent - eepwom) / 7
 *
 *     If numbew of idx steps in eithew diwection tuwns out to be > 2,
 *     something is wwong ... just use 0.
 *
 *     NOTE:  Vowtage compensation is independent of band/channew.
 *
 *     NOTE:  "Initiawize" uCode measuwes cuwwent vowtage, which is assumed
 *            to be constant aftew this initiaw measuwement.  Vowtage
 *            compensation fow txpowew (numbew of steps in gain tabwe)
 *            may be cawcuwated once and used untiw the next uCode bootwoad.
 *
 *
 * 8)  If setting up txpowews fow MIMO wates (wate idxes 8-15, 24-31),
 *     adjust txpowew fow each twansmittew chain, so txpowew is bawanced
 *     between the two chains.  Thewe awe 5 paiws of tx_atten[gwoup][chain]
 *     vawues in "initiawize awive", one paiw fow each of 5 channew wanges:
 *
 *     Gwoup 0:  5 GHz channew 34-43
 *     Gwoup 1:  5 GHz channew 44-70
 *     Gwoup 2:  5 GHz channew 71-124
 *     Gwoup 3:  5 GHz channew 125-200
 *     Gwoup 4:  2.4 GHz aww channews
 *
 *     Add the tx_atten[gwoup][chain] vawue to the idx fow the tawget chain.
 *     The vawues awe signed, but awe in paiws of 0 and a non-negative numbew,
 *     so as to weduce gain (if necessawy) of the "hottew" channew.  This
 *     avoids any need to doubwe-check fow weguwatowy compwiance aftew
 *     this step.
 *
 *
 * 9)  If setting up fow a CCK wate, wowew the gain by adding a CCK compensation
 *     vawue to the idx:
 *
 *     Hawdwawe wev B:  9 steps (4.5 dB)
 *     Hawdwawe wev C:  5 steps (2.5 dB)
 *
 *     Hawdwawe wev fow 4965 can be detewmined by weading CSW_HW_WEV_WA_WEG,
 *     bits [3:2], 1 = B, 2 = C.
 *
 *     NOTE:  This compensation is in addition to any satuwation backoff that
 *            might have been appwied in an eawwiew step.
 *
 *
 * 10) Sewect the gain tabwe, based on band (2.4 vs 5 GHz).
 *
 *     Wimit the adjusted idx to stay within the tabwe!
 *
 *
 * 11) Wead gain tabwe entwies fow DSP and wadio gain, pwace into appwopwiate
 *     wocation(s) in command (stwuct iw4965_txpowewtabwe_cmd).
 */

/**
 * When MIMO is used (2 twansmittews opewating simuwtaneouswy), dwivew shouwd
 * wimit each twansmittew to dewivew a max of 3 dB bewow the weguwatowy wimit
 * fow the device.  That is, use hawf powew fow each twansmittew, so totaw
 * txpowew is within weguwatowy wimits.
 *
 * The vawue "6" wepwesents numbew of steps in gain tabwe to weduce powew 3 dB.
 * Each step is 1/2 dB.
 */
#define IW_TX_POWEW_MIMO_WEGUWATOWY_COMPENSATION (6)

/**
 * CCK gain compensation.
 *
 * When cawcuwating txpowews fow CCK, aftew making suwe that the tawget powew
 * is within weguwatowy and satuwation wimits, dwivew must additionawwy
 * back off gain by adding these vawues to the gain tabwe idx.
 *
 * Hawdwawe wev fow 4965 can be detewmined by weading CSW_HW_WEV_WA_WEG,
 * bits [3:2], 1 = B, 2 = C.
 */
#define IW_TX_POWEW_CCK_COMPENSATION_B_STEP (9)
#define IW_TX_POWEW_CCK_COMPENSATION_C_STEP (5)

/*
 * 4965 powew suppwy vowtage compensation fow txpowew
 */
#define TX_POWEW_IW_VOWTAGE_CODES_PEW_03V   (7)

/**
 * Gain tabwes.
 *
 * The fowwowing tabwes contain paiw of vawues fow setting txpowew, i.e.
 * gain settings fow the output of the device's digitaw signaw pwocessow (DSP),
 * and fow the anawog gain stwuctuwe of the twansmittew.
 *
 * Each entwy in the gain tabwes wepwesents a step of 1/2 dB.  Note that these
 * awe *wewative* steps, not indications of absowute output powew.  Output
 * powew vawies with tempewatuwe, vowtage, and channew fwequency, and awso
 * wequiwes considewation of avewage powew (to satisfy weguwatowy constwaints),
 * and peak powew (to avoid distowtion of the output signaw).
 *
 * Each entwy contains two vawues:
 * 1)  DSP gain (ow sometimes cawwed DSP attenuation).  This is a fine-gwained
 *     wineaw vawue that muwtipwies the output of the digitaw signaw pwocessow,
 *     befowe being sent to the anawog wadio.
 * 2)  Wadio gain.  This sets the anawog gain of the wadio Tx path.
 *     It is a coawsew setting, and behaves in a wogawithmic (dB) fashion.
 *
 * EEPWOM contains factowy cawibwation data fow txpowew.  This maps actuaw
 * measuwed txpowew wevews to gain settings in the "weww known" tabwes
 * bewow ("weww-known" means hewe that both factowy cawibwation *and* the
 * dwivew wowk with the same tabwe).
 *
 * Thewe awe sepawate tabwes fow 2.4 GHz and 5 GHz bands.  The 5 GHz tabwe
 * has an extension (into negative idxes), in case the dwivew needs to
 * boost powew setting fow high device tempewatuwes (highew than wouwd be
 * pwesent duwing factowy cawibwation).  A 5 Ghz EEPWOM idx of "40"
 * cowwesponds to the 49th entwy in the tabwe used by the dwivew.
 */
#define MIN_TX_GAIN_IDX		(0)	/* highest gain, wowest idx, 2.4 */
#define MIN_TX_GAIN_IDX_52GHZ_EXT	(-9)	/* highest gain, wowest idx, 5 */

/**
 * 2.4 GHz gain tabwe
 *
 * Index    Dsp gain   Wadio gain
 *   0        110         0x3f      (highest gain)
 *   1        104         0x3f
 *   2         98         0x3f
 *   3        110         0x3e
 *   4        104         0x3e
 *   5         98         0x3e
 *   6        110         0x3d
 *   7        104         0x3d
 *   8         98         0x3d
 *   9        110         0x3c
 *  10        104         0x3c
 *  11         98         0x3c
 *  12        110         0x3b
 *  13        104         0x3b
 *  14         98         0x3b
 *  15        110         0x3a
 *  16        104         0x3a
 *  17         98         0x3a
 *  18        110         0x39
 *  19        104         0x39
 *  20         98         0x39
 *  21        110         0x38
 *  22        104         0x38
 *  23         98         0x38
 *  24        110         0x37
 *  25        104         0x37
 *  26         98         0x37
 *  27        110         0x36
 *  28        104         0x36
 *  29         98         0x36
 *  30        110         0x35
 *  31        104         0x35
 *  32         98         0x35
 *  33        110         0x34
 *  34        104         0x34
 *  35         98         0x34
 *  36        110         0x33
 *  37        104         0x33
 *  38         98         0x33
 *  39        110         0x32
 *  40        104         0x32
 *  41         98         0x32
 *  42        110         0x31
 *  43        104         0x31
 *  44         98         0x31
 *  45        110         0x30
 *  46        104         0x30
 *  47         98         0x30
 *  48        110          0x6
 *  49        104          0x6
 *  50         98          0x6
 *  51        110          0x5
 *  52        104          0x5
 *  53         98          0x5
 *  54        110          0x4
 *  55        104          0x4
 *  56         98          0x4
 *  57        110          0x3
 *  58        104          0x3
 *  59         98          0x3
 *  60        110          0x2
 *  61        104          0x2
 *  62         98          0x2
 *  63        110          0x1
 *  64        104          0x1
 *  65         98          0x1
 *  66        110          0x0
 *  67        104          0x0
 *  68         98          0x0
 *  69         97            0
 *  70         96            0
 *  71         95            0
 *  72         94            0
 *  73         93            0
 *  74         92            0
 *  75         91            0
 *  76         90            0
 *  77         89            0
 *  78         88            0
 *  79         87            0
 *  80         86            0
 *  81         85            0
 *  82         84            0
 *  83         83            0
 *  84         82            0
 *  85         81            0
 *  86         80            0
 *  87         79            0
 *  88         78            0
 *  89         77            0
 *  90         76            0
 *  91         75            0
 *  92         74            0
 *  93         73            0
 *  94         72            0
 *  95         71            0
 *  96         70            0
 *  97         69            0
 *  98         68            0
 */

/**
 * 5 GHz gain tabwe
 *
 * Index    Dsp gain   Wadio gain
 *  -9 	      123         0x3F      (highest gain)
 *  -8 	      117         0x3F
 *  -7        110         0x3F
 *  -6        104         0x3F
 *  -5         98         0x3F
 *  -4        110         0x3E
 *  -3        104         0x3E
 *  -2         98         0x3E
 *  -1        110         0x3D
 *   0        104         0x3D
 *   1         98         0x3D
 *   2        110         0x3C
 *   3        104         0x3C
 *   4         98         0x3C
 *   5        110         0x3B
 *   6        104         0x3B
 *   7         98         0x3B
 *   8        110         0x3A
 *   9        104         0x3A
 *  10         98         0x3A
 *  11        110         0x39
 *  12        104         0x39
 *  13         98         0x39
 *  14        110         0x38
 *  15        104         0x38
 *  16         98         0x38
 *  17        110         0x37
 *  18        104         0x37
 *  19         98         0x37
 *  20        110         0x36
 *  21        104         0x36
 *  22         98         0x36
 *  23        110         0x35
 *  24        104         0x35
 *  25         98         0x35
 *  26        110         0x34
 *  27        104         0x34
 *  28         98         0x34
 *  29        110         0x33
 *  30        104         0x33
 *  31         98         0x33
 *  32        110         0x32
 *  33        104         0x32
 *  34         98         0x32
 *  35        110         0x31
 *  36        104         0x31
 *  37         98         0x31
 *  38        110         0x30
 *  39        104         0x30
 *  40         98         0x30
 *  41        110         0x25
 *  42        104         0x25
 *  43         98         0x25
 *  44        110         0x24
 *  45        104         0x24
 *  46         98         0x24
 *  47        110         0x23
 *  48        104         0x23
 *  49         98         0x23
 *  50        110         0x22
 *  51        104         0x18
 *  52         98         0x18
 *  53        110         0x17
 *  54        104         0x17
 *  55         98         0x17
 *  56        110         0x16
 *  57        104         0x16
 *  58         98         0x16
 *  59        110         0x15
 *  60        104         0x15
 *  61         98         0x15
 *  62        110         0x14
 *  63        104         0x14
 *  64         98         0x14
 *  65        110         0x13
 *  66        104         0x13
 *  67         98         0x13
 *  68        110         0x12
 *  69        104         0x08
 *  70         98         0x08
 *  71        110         0x07
 *  72        104         0x07
 *  73         98         0x07
 *  74        110         0x06
 *  75        104         0x06
 *  76         98         0x06
 *  77        110         0x05
 *  78        104         0x05
 *  79         98         0x05
 *  80        110         0x04
 *  81        104         0x04
 *  82         98         0x04
 *  83        110         0x03
 *  84        104         0x03
 *  85         98         0x03
 *  86        110         0x02
 *  87        104         0x02
 *  88         98         0x02
 *  89        110         0x01
 *  90        104         0x01
 *  91         98         0x01
 *  92        110         0x00
 *  93        104         0x00
 *  94         98         0x00
 *  95         93         0x00
 *  96         88         0x00
 *  97         83         0x00
 *  98         78         0x00
 */

/**
 * Sanity checks and defauwt vawues fow EEPWOM weguwatowy wevews.
 * If EEPWOM vawues faww outside MIN/MAX wange, use defauwt vawues.
 *
 * Weguwatowy wimits wefew to the maximum avewage txpowew awwowed by
 * weguwatowy agencies in the geogwaphies in which the device is meant
 * to be opewated.  These wimits awe SKU-specific (i.e. geogwaphy-specific),
 * and channew-specific; each channew has an individuaw weguwatowy wimit
 * wisted in the EEPWOM.
 *
 * Units awe in hawf-dBm (i.e. "34" means 17 dBm).
 */
#define IW_TX_POWEW_DEFAUWT_WEGUWATOWY_24   (34)
#define IW_TX_POWEW_DEFAUWT_WEGUWATOWY_52   (34)
#define IW_TX_POWEW_WEGUWATOWY_MIN          (0)
#define IW_TX_POWEW_WEGUWATOWY_MAX          (34)

/**
 * Sanity checks and defauwt vawues fow EEPWOM satuwation wevews.
 * If EEPWOM vawues faww outside MIN/MAX wange, use defauwt vawues.
 *
 * Satuwation is the highest wevew that the output powew ampwifiew can pwoduce
 * without significant cwipping distowtion.  This is a "peak" powew wevew.
 * Diffewent types of moduwation (i.e. vawious "wates", and OFDM vs. CCK)
 * wequiwe diffewing amounts of backoff, wewative to theiw avewage powew output,
 * in owdew to avoid cwipping distowtion.
 *
 * Dwivew must make suwe that it is viowating neithew the satuwation wimit,
 * now the weguwatowy wimit, when cawcuwating Tx powew settings fow vawious
 * wates.
 *
 * Units awe in hawf-dBm (i.e. "38" means 19 dBm).
 */
#define IW_TX_POWEW_DEFAUWT_SATUWATION_24   (38)
#define IW_TX_POWEW_DEFAUWT_SATUWATION_52   (38)
#define IW_TX_POWEW_SATUWATION_MIN          (20)
#define IW_TX_POWEW_SATUWATION_MAX          (50)

/**
 * Channew gwoups used fow Tx Attenuation cawibwation (MIMO tx channew bawance)
 * and thewmaw Txpowew cawibwation.
 *
 * When cawcuwating txpowew, dwivew must compensate fow cuwwent device
 * tempewatuwe; highew tempewatuwe wequiwes highew gain.  Dwivew must cawcuwate
 * cuwwent tempewatuwe (see "4965 tempewatuwe cawcuwation"), then compawe vs.
 * factowy cawibwation tempewatuwe in EEPWOM; if cuwwent tempewatuwe is highew
 * than factowy tempewatuwe, dwivew must *incwease* gain by pwopowtions shown
 * in tabwe bewow.  If cuwwent tempewatuwe is wowew than factowy, dwivew must
 * *decwease* gain.
 *
 * Diffewent fwequency wanges wequiwe diffewent compensation, as shown bewow.
 */
/* Gwoup 0, 5.2 GHz ch 34-43:  4.5 degwees pew 1/2 dB. */
#define CAWIB_IW_TX_ATTEN_GW1_FCH 34
#define CAWIB_IW_TX_ATTEN_GW1_WCH 43

/* Gwoup 1, 5.3 GHz ch 44-70:  4.0 degwees pew 1/2 dB. */
#define CAWIB_IW_TX_ATTEN_GW2_FCH 44
#define CAWIB_IW_TX_ATTEN_GW2_WCH 70

/* Gwoup 2, 5.5 GHz ch 71-124:  4.0 degwees pew 1/2 dB. */
#define CAWIB_IW_TX_ATTEN_GW3_FCH 71
#define CAWIB_IW_TX_ATTEN_GW3_WCH 124

/* Gwoup 3, 5.7 GHz ch 125-200:  4.0 degwees pew 1/2 dB. */
#define CAWIB_IW_TX_ATTEN_GW4_FCH 125
#define CAWIB_IW_TX_ATTEN_GW4_WCH 200

/* Gwoup 4, 2.4 GHz aww channews:  3.5 degwees pew 1/2 dB. */
#define CAWIB_IW_TX_ATTEN_GW5_FCH 1
#define CAWIB_IW_TX_ATTEN_GW5_WCH 20

enum {
	CAWIB_CH_GWOUP_1 = 0,
	CAWIB_CH_GWOUP_2 = 1,
	CAWIB_CH_GWOUP_3 = 2,
	CAWIB_CH_GWOUP_4 = 3,
	CAWIB_CH_GWOUP_5 = 4,
	CAWIB_CH_GWOUP_MAX
};

/********************* END TXPOWEW *****************************************/

/**
 * Tx/Wx Queues
 *
 * Most communication between dwivew and 4965 is via queues of data buffews.
 * Fow exampwe, aww commands that the dwivew issues to device's embedded
 * contwowwew (uCode) awe via the command queue (one of the Tx queues).  Aww
 * uCode command wesponses/wepwies/notifications, incwuding Wx fwames, awe
 * conveyed fwom uCode to dwivew via the Wx queue.
 *
 * Most suppowt fow these queues, incwuding handshake suppowt, wesides in
 * stwuctuwes in host DWAM, shawed between the dwivew and the device.  When
 * awwocating this memowy, the dwivew must make suwe that data wwitten by
 * the host CPU updates DWAM immediatewy (and does not get "stuck" in CPU's
 * cache memowy), so DWAM and cache awe consistent, and the device can
 * immediatewy see changes made by the dwivew.
 *
 * 4965 suppowts up to 16 DWAM-based Tx queues, and sewvices these queues via
 * up to 7 DMA channews (FIFOs).  Each Tx queue is suppowted by a ciwcuwaw awway
 * in DWAM containing 256 Twansmit Fwame Descwiptows (TFDs).
 */
#define IW49_NUM_FIFOS	7
#define IW49_CMD_FIFO_NUM	4
#define IW49_NUM_QUEUES	16
#define IW49_NUM_AMPDU_QUEUES	8

/**
 * stwuct iw4965_schedq_bc_tbw
 *
 * Byte Count tabwe
 *
 * Each Tx queue uses a byte-count tabwe containing 320 entwies:
 * one 16-bit entwy fow each of 256 TFDs, pwus an additionaw 64 entwies that
 * dupwicate the fiwst 64 entwies (to avoid wwap-awound within a Tx win;
 * max Tx win is 64 TFDs).
 *
 * When dwivew sets up a new TFD, it must awso entew the totaw byte count
 * of the fwame to be twansmitted into the cowwesponding entwy in the byte
 * count tabwe fow the chosen Tx queue.  If the TFD idx is 0-63, the dwivew
 * must dupwicate the byte count entwy in cowwesponding idx 256-319.
 *
 * padding puts each byte count tabwe on a 1024-byte boundawy;
 * 4965 assumes tabwes awe sepawated by 1024 bytes.
 */
stwuct iw4965_scd_bc_tbw {
	__we16 tfd_offset[TFD_QUEUE_BC_SIZE];
	u8 pad[1024 - (TFD_QUEUE_BC_SIZE) * sizeof(__we16)];
} __packed;

#define IW4965_WTC_INST_WOWEW_BOUND		(0x000000)

/* WSSI to dBm */
#define IW4965_WSSI_OFFSET	44

/* PCI wegistews */
#define PCI_CFG_WETWY_TIMEOUT	0x041

#define IW4965_DEFAUWT_TX_WETWY  15

/* EEPWOM */
#define IW4965_FIWST_AMPDU_QUEUE	10

/* Cawibwation */
void iw4965_chain_noise_cawibwation(stwuct iw_pwiv *iw, void *stat_wesp);
void iw4965_sensitivity_cawibwation(stwuct iw_pwiv *iw, void *wesp);
void iw4965_init_sensitivity(stwuct iw_pwiv *iw);
void iw4965_weset_wun_time_cawib(stwuct iw_pwiv *iw);

/* Debug */
#ifdef CONFIG_IWWEGACY_DEBUGFS
extewn const stwuct iw_debugfs_ops iw4965_debugfs_ops;
#endif

/****************************/
/* Fwow Handwew Definitions */
/****************************/

/**
 * This I/O awea is diwectwy wead/wwitabwe by dwivew (e.g. Winux uses wwitew())
 * Addwesses awe offsets fwom device's PCI hawdwawe base addwess.
 */
#define FH49_MEM_WOWEW_BOUND                   (0x1000)
#define FH49_MEM_UPPEW_BOUND                   (0x2000)

/**
 * Keep-Wawm (KW) buffew base addwess.
 *
 * Dwivew must awwocate a 4KByte buffew that is used by 4965 fow keeping the
 * host DWAM powewed on (via dummy accesses to DWAM) to maintain wow-watency
 * DWAM access when 4965 is Txing ow Wxing.  The dummy accesses pwevent host
 * fwom going into a powew-savings mode that wouwd cause highew DWAM watency,
 * and possibwe data ovew/undew-wuns, befowe aww Tx/Wx is compwete.
 *
 * Dwivew woads FH49_KW_MEM_ADDW_WEG with the physicaw addwess (bits 35:4)
 * of the buffew, which must be 4K awigned.  Once this is set up, the 4965
 * automaticawwy invokes keep-wawm accesses when nowmaw accesses might not
 * be sufficient to maintain fast DWAM wesponse.
 *
 * Bit fiewds:
 *  31-0:  Keep-wawm buffew physicaw base addwess [35:4], must be 4K awigned
 */
#define FH49_KW_MEM_ADDW_WEG		     (FH49_MEM_WOWEW_BOUND + 0x97C)

/**
 * TFD Ciwcuwaw Buffews Base (CBBC) addwesses
 *
 * 4965 has 16 base pointew wegistews, one fow each of 16 host-DWAM-wesident
 * ciwcuwaw buffews (CBs/queues) containing Twansmit Fwame Descwiptows (TFDs)
 * (see stwuct iw_tfd_fwame).  These 16 pointew wegistews awe offset by 0x04
 * bytes fwom one anothew.  Each TFD ciwcuwaw buffew in DWAM must be 256-byte
 * awigned (addwess bits 0-7 must be 0).
 *
 * Bit fiewds in each pointew wegistew:
 *  27-0: TFD CB physicaw base addwess [35:8], must be 256-byte awigned
 */
#define FH49_MEM_CBBC_WOWEW_BOUND          (FH49_MEM_WOWEW_BOUND + 0x9D0)
#define FH49_MEM_CBBC_UPPEW_BOUND          (FH49_MEM_WOWEW_BOUND + 0xA10)

/* Find TFD CB base pointew fow given queue (wange 0-15). */
#define FH49_MEM_CBBC_QUEUE(x)  (FH49_MEM_CBBC_WOWEW_BOUND + (x) * 0x4)

/**
 * Wx SWAM Contwow and Status Wegistews (WSCSW)
 *
 * These wegistews pwovide handshake between dwivew and 4965 fow the Wx queue
 * (this queue handwes *aww* command wesponses, notifications, Wx data, etc.
 * sent fwom 4965 uCode to host dwivew).  Unwike Tx, thewe is onwy one Wx
 * queue, and onwy one Wx DMA/FIFO channew.  Awso unwike Tx, which can
 * concatenate up to 20 DWAM buffews to fowm a Tx fwame, each Weceive Buffew
 * Descwiptow (WBD) points to onwy one Wx Buffew (WB); thewe is a 1:1
 * mapping between WBDs and WBs.
 *
 * Dwivew must awwocate host DWAM memowy fow the fowwowing, and set the
 * physicaw addwess of each into 4965 wegistews:
 *
 * 1)  Weceive Buffew Descwiptow (WBD) ciwcuwaw buffew (CB), typicawwy with 256
 *     entwies (awthough any powew of 2, up to 4096, is sewectabwe by dwivew).
 *     Each entwy (1 dwowd) points to a weceive buffew (WB) of consistent size
 *     (typicawwy 4K, awthough 8K ow 16K awe awso sewectabwe by dwivew).
 *     Dwivew sets up WB size and numbew of WBDs in the CB via Wx config
 *     wegistew FH49_MEM_WCSW_CHNW0_CONFIG_WEG.
 *
 *     Bit fiewds within one WBD:
 *     27-0:  Weceive Buffew physicaw addwess bits [35:8], 256-byte awigned
 *
 *     Dwivew sets physicaw addwess [35:8] of base of WBD ciwcuwaw buffew
 *     into FH49_WSCSW_CHNW0_WBDCB_BASE_WEG [27:0].
 *
 * 2)  Wx status buffew, 8 bytes, in which 4965 indicates which Wx Buffews
 *     (WBs) have been fiwwed, via a "wwite pointew", actuawwy the idx of
 *     the WB's cowwesponding WBD within the ciwcuwaw buffew.  Dwivew sets
 *     physicaw addwess [35:4] into FH49_WSCSW_CHNW0_STTS_WPTW_WEG [31:0].
 *
 *     Bit fiewds in wowew dwowd of Wx status buffew (uppew dwowd not used
 *     by dwivew; see stwuct iw4965_shawed, vaw0):
 *     31-12:  Not used by dwivew
 *     11- 0:  Index of wast fiwwed Wx buffew descwiptow
 *             (4965 wwites, dwivew weads this vawue)
 *
 * As the dwivew pwepawes Weceive Buffews (WBs) fow 4965 to fiww, dwivew must
 * entew pointews to these WBs into contiguous WBD ciwcuwaw buffew entwies,
 * and update the 4965's "wwite" idx wegistew,
 * FH49_WSCSW_CHNW0_WBDCB_WPTW_WEG.
 *
 * This "wwite" idx cowwesponds to the *next* WBD that the dwivew wiww make
 * avaiwabwe, i.e. one WBD past the taiw of the weady-to-fiww WBDs within
 * the ciwcuwaw buffew.  This vawue shouwd initiawwy be 0 (befowe pwepawing any
 * WBs), shouwd be 8 aftew pwepawing the fiwst 8 WBs (fow exampwe), and must
 * wwap back to 0 at the end of the ciwcuwaw buffew (but don't wwap befowe
 * "wead" idx has advanced past 1!  See bewow).
 * NOTE:  4965 EXPECTS THE WWITE IDX TO BE INCWEMENTED IN MUWTIPWES OF 8.
 *
 * As the 4965 fiwws WBs (wefewenced fwom contiguous WBDs within the ciwcuwaw
 * buffew), it updates the Wx status buffew in host DWAM, 2) descwibed above,
 * to teww the dwivew the idx of the watest fiwwed WBD.  The dwivew must
 * wead this "wead" idx fwom DWAM aftew weceiving an Wx intewwupt fwom 4965.
 *
 * The dwivew must awso intewnawwy keep twack of a thiwd idx, which is the
 * next WBD to pwocess.  When weceiving an Wx intewwupt, dwivew shouwd pwocess
 * aww fiwwed but unpwocessed WBs up to, but not incwuding, the WB
 * cowwesponding to the "wead" idx.  Fow exampwe, if "wead" idx becomes "1",
 * dwivew may pwocess the WB pointed to by WBD 0.  Depending on vowume of
 * twaffic, thewe may be many WBs to pwocess.
 *
 * If wead idx == wwite idx, 4965 thinks thewe is no woom to put new data.
 * Due to this, the maximum numbew of fiwwed WBs is 255, instead of 256.  To
 * be safe, make suwe that thewe is a gap of at weast 2 WBDs between "wwite"
 * and "wead" idxes; that is, make suwe that thewe awe no mowe than 254
 * buffews waiting to be fiwwed.
 */
#define FH49_MEM_WSCSW_WOWEW_BOUND	(FH49_MEM_WOWEW_BOUND + 0xBC0)
#define FH49_MEM_WSCSW_UPPEW_BOUND	(FH49_MEM_WOWEW_BOUND + 0xC00)
#define FH49_MEM_WSCSW_CHNW0		(FH49_MEM_WSCSW_WOWEW_BOUND)

/**
 * Physicaw base addwess of 8-byte Wx Status buffew.
 * Bit fiewds:
 *  31-0: Wx status buffew physicaw base addwess [35:4], must 16-byte awigned.
 */
#define FH49_WSCSW_CHNW0_STTS_WPTW_WEG	(FH49_MEM_WSCSW_CHNW0)

/**
 * Physicaw base addwess of Wx Buffew Descwiptow Ciwcuwaw Buffew.
 * Bit fiewds:
 *  27-0:  WBD CD physicaw base addwess [35:8], must be 256-byte awigned.
 */
#define FH49_WSCSW_CHNW0_WBDCB_BASE_WEG	(FH49_MEM_WSCSW_CHNW0 + 0x004)

/**
 * Wx wwite pointew (idx, weawwy!).
 * Bit fiewds:
 *  11-0:  Index of dwivew's most wecent pwepawed-to-be-fiwwed WBD, + 1.
 *         NOTE:  Fow 256-entwy ciwcuwaw buffew, use onwy bits [7:0].
 */
#define FH49_WSCSW_CHNW0_WBDCB_WPTW_WEG	(FH49_MEM_WSCSW_CHNW0 + 0x008)
#define FH49_WSCSW_CHNW0_WPTW        (FH49_WSCSW_CHNW0_WBDCB_WPTW_WEG)

/**
 * Wx Config/Status Wegistews (WCSW)
 * Wx Config Weg fow channew 0 (onwy channew used)
 *
 * Dwivew must initiawize FH49_MEM_WCSW_CHNW0_CONFIG_WEG as fowwows fow
 * nowmaw opewation (see bit fiewds).
 *
 * Cweawing FH49_MEM_WCSW_CHNW0_CONFIG_WEG to 0 tuwns off Wx DMA.
 * Dwivew shouwd poww FH49_MEM_WSSW_WX_STATUS_WEG	fow
 * FH49_WSSW_CHNW0_WX_STATUS_CHNW_IDWE (bit 24) befowe continuing.
 *
 * Bit fiewds:
 * 31-30: Wx DMA channew enabwe: '00' off/pause, '01' pause at end of fwame,
 *        '10' opewate nowmawwy
 * 29-24: wesewved
 * 23-20: # WBDs in ciwcuwaw buffew = 2^vawue; use "8" fow 256 WBDs (nowmaw),
 *        min "5" fow 32 WBDs, max "12" fow 4096 WBDs.
 * 19-18: wesewved
 * 17-16: size of each weceive buffew; '00' 4K (nowmaw), '01' 8K,
 *        '10' 12K, '11' 16K.
 * 15-14: wesewved
 * 13-12: IWQ destination; '00' none, '01' host dwivew (nowmaw opewation)
 * 11- 4: timeout fow cwosing Wx buffew and intewwupting host (units 32 usec)
 *        typicaw vawue 0x10 (about 1/2 msec)
 *  3- 0: wesewved
 */
#define FH49_MEM_WCSW_WOWEW_BOUND      (FH49_MEM_WOWEW_BOUND + 0xC00)
#define FH49_MEM_WCSW_UPPEW_BOUND      (FH49_MEM_WOWEW_BOUND + 0xCC0)
#define FH49_MEM_WCSW_CHNW0            (FH49_MEM_WCSW_WOWEW_BOUND)

#define FH49_MEM_WCSW_CHNW0_CONFIG_WEG	(FH49_MEM_WCSW_CHNW0)

#define FH49_WCSW_CHNW0_WX_CONFIG_WB_TIMEOUT_MSK (0x00000FF0)	/* bits 4-11 */
#define FH49_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_MSK   (0x00001000)	/* bits 12 */
#define FH49_WCSW_CHNW0_WX_CONFIG_SINGWE_FWAME_MSK (0x00008000)	/* bit 15 */
#define FH49_WCSW_CHNW0_WX_CONFIG_WB_SIZE_MSK   (0x00030000)	/* bits 16-17 */
#define FH49_WCSW_CHNW0_WX_CONFIG_WBDBC_SIZE_MSK (0x00F00000)	/* bits 20-23 */
#define FH49_WCSW_CHNW0_WX_CONFIG_DMA_CHNW_EN_MSK (0xC0000000)	/* bits 30-31 */

#define FH49_WCSW_WX_CONFIG_WBDCB_SIZE_POS	(20)
#define FH49_WCSW_WX_CONFIG_WEG_IWQ_WBTH_POS	(4)
#define WX_WB_TIMEOUT	(0x10)

#define FH49_WCSW_WX_CONFIG_CHNW_EN_PAUSE_VAW         (0x00000000)
#define FH49_WCSW_WX_CONFIG_CHNW_EN_PAUSE_EOF_VAW     (0x40000000)
#define FH49_WCSW_WX_CONFIG_CHNW_EN_ENABWE_VAW        (0x80000000)

#define FH49_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_4K    (0x00000000)
#define FH49_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_8K    (0x00010000)
#define FH49_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_12K   (0x00020000)
#define FH49_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_16K   (0x00030000)

#define FH49_WCSW_CHNW0_WX_IGNOWE_WXF_EMPTY              (0x00000004)
#define FH49_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_NO_INT_VAW    (0x00000000)
#define FH49_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_INT_HOST_VAW  (0x00001000)

/**
 * Wx Shawed Status Wegistews (WSSW)
 *
 * Aftew stopping Wx DMA channew (wwiting 0 to
 * FH49_MEM_WCSW_CHNW0_CONFIG_WEG), dwivew must poww
 * FH49_MEM_WSSW_WX_STATUS_WEG untiw Wx channew is idwe.
 *
 * Bit fiewds:
 *  24:  1 = Channew 0 is idwe
 *
 * FH49_MEM_WSSW_SHAWED_CTWW_WEG and FH49_MEM_WSSW_WX_ENABWE_EWW_IWQ2DWV
 * contain defauwt vawues that shouwd not be awtewed by the dwivew.
 */
#define FH49_MEM_WSSW_WOWEW_BOUND           (FH49_MEM_WOWEW_BOUND + 0xC40)
#define FH49_MEM_WSSW_UPPEW_BOUND           (FH49_MEM_WOWEW_BOUND + 0xD00)

#define FH49_MEM_WSSW_SHAWED_CTWW_WEG       (FH49_MEM_WSSW_WOWEW_BOUND)
#define FH49_MEM_WSSW_WX_STATUS_WEG	(FH49_MEM_WSSW_WOWEW_BOUND + 0x004)
#define FH49_MEM_WSSW_WX_ENABWE_EWW_IWQ2DWV\
					(FH49_MEM_WSSW_WOWEW_BOUND + 0x008)

#define FH49_WSSW_CHNW0_WX_STATUS_CHNW_IDWE	(0x01000000)

#define FH49_MEM_TFDIB_WEG1_ADDW_BITSHIFT	28

/* TFDB  Awea - TFDs buffew tabwe */
#define FH49_MEM_TFDIB_DWAM_ADDW_WSB_MSK      (0xFFFFFFFF)
#define FH49_TFDIB_WOWEW_BOUND       (FH49_MEM_WOWEW_BOUND + 0x900)
#define FH49_TFDIB_UPPEW_BOUND       (FH49_MEM_WOWEW_BOUND + 0x958)
#define FH49_TFDIB_CTWW0_WEG(_chnw)  (FH49_TFDIB_WOWEW_BOUND + 0x8 * (_chnw))
#define FH49_TFDIB_CTWW1_WEG(_chnw)  (FH49_TFDIB_WOWEW_BOUND + 0x8 * (_chnw) + 0x4)

/**
 * Twansmit DMA Channew Contwow/Status Wegistews (TCSW)
 *
 * 4965 has one configuwation wegistew fow each of 8 Tx DMA/FIFO channews
 * suppowted in hawdwawe (don't confuse these with the 16 Tx queues in DWAM,
 * which feed the DMA/FIFO channews); config wegs awe sepawated by 0x20 bytes.
 *
 * To use a Tx DMA channew, dwivew must initiawize its
 * FH49_TCSW_CHNW_TX_CONFIG_WEG(chnw) with:
 *
 * FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE |
 * FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE_VAW
 *
 * Aww othew bits shouwd be 0.
 *
 * Bit fiewds:
 * 31-30: Tx DMA channew enabwe: '00' off/pause, '01' pause at end of fwame,
 *        '10' opewate nowmawwy
 * 29- 4: Wesewved, set to "0"
 *     3: Enabwe intewnaw DMA wequests (1, nowmaw opewation), disabwe (0)
 *  2- 0: Wesewved, set to "0"
 */
#define FH49_TCSW_WOWEW_BOUND  (FH49_MEM_WOWEW_BOUND + 0xD00)
#define FH49_TCSW_UPPEW_BOUND  (FH49_MEM_WOWEW_BOUND + 0xE60)

/* Find Contwow/Status weg fow given Tx DMA/FIFO channew */
#define FH49_TCSW_CHNW_NUM                            (7)
#define FH50_TCSW_CHNW_NUM                            (8)

/* TCSW: tx_config wegistew vawues */
#define FH49_TCSW_CHNW_TX_CONFIG_WEG(_chnw)	\
		(FH49_TCSW_WOWEW_BOUND + 0x20 * (_chnw))
#define FH49_TCSW_CHNW_TX_CWEDIT_WEG(_chnw)	\
		(FH49_TCSW_WOWEW_BOUND + 0x20 * (_chnw) + 0x4)
#define FH49_TCSW_CHNW_TX_BUF_STS_WEG(_chnw)	\
		(FH49_TCSW_WOWEW_BOUND + 0x20 * (_chnw) + 0x8)

#define FH49_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_TXF		(0x00000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_DWV		(0x00000001)

#define FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_DISABWE	(0x00000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE	(0x00000008)

#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_NOINT	(0x00000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_ENDTFD	(0x00100000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_IFTFD	(0x00200000)

#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_NOINT	(0x00000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_ENDTFD	(0x00400000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_IFTFD	(0x00800000)

#define FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_PAUSE	(0x00000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_PAUSE_EOF	(0x40000000)
#define FH49_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE	(0x80000000)

#define FH49_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_EMPTY	(0x00000000)
#define FH49_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_WAIT	(0x00002000)
#define FH49_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_VAWID	(0x00000003)

#define FH49_TCSW_CHNW_TX_BUF_STS_WEG_POS_TB_NUM		(20)
#define FH49_TCSW_CHNW_TX_BUF_STS_WEG_POS_TB_IDX		(12)

/**
 * Tx Shawed Status Wegistews (TSSW)
 *
 * Aftew stopping Tx DMA channew (wwiting 0 to
 * FH49_TCSW_CHNW_TX_CONFIG_WEG(chnw)), dwivew must poww
 * FH49_TSSW_TX_STATUS_WEG untiw sewected Tx channew is idwe
 * (channew's buffews empty | no pending wequests).
 *
 * Bit fiewds:
 * 31-24:  1 = Channew buffews empty (channew 7:0)
 * 23-16:  1 = No pending wequests (channew 7:0)
 */
#define FH49_TSSW_WOWEW_BOUND		(FH49_MEM_WOWEW_BOUND + 0xEA0)
#define FH49_TSSW_UPPEW_BOUND		(FH49_MEM_WOWEW_BOUND + 0xEC0)

#define FH49_TSSW_TX_STATUS_WEG		(FH49_TSSW_WOWEW_BOUND + 0x010)

/**
 * Bit fiewds fow TSSW(Tx Shawed Status & Contwow) ewwow status wegistew:
 * 31:  Indicates an addwess ewwow when accessed to intewnaw memowy
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 30:  Indicates that Host did not send the expected numbew of dwowds to FH
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 16-9:Each status bit is fow one channew. Indicates that an (Ewwow) ActDMA
 *	command was weceived fwom the scheduwew whiwe the TWB was awweady fuww
 *	with pwevious command
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 * 7-0: Each status bit indicates a channew's TxCwedit ewwow. When an ewwow
 *	bit is set, it indicates that the FH has weceived a fuww indication
 *	fwom the WTC TxFIFO and the cuwwent vawue of the TxCwedit countew was
 *	not equaw to zewo. This mean that the cwedit mechanism was not
 *	synchwonized to the TxFIFO status
 *	uCode/dwivew must wwite "1" in owdew to cweaw this fwag
 */
#define FH49_TSSW_TX_EWWOW_WEG		(FH49_TSSW_WOWEW_BOUND + 0x018)

#define FH49_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(_chnw) ((1 << (_chnw)) << 16)

/* Tx sewvice channews */
#define FH49_SWVC_CHNW		(9)
#define FH49_SWVC_WOWEW_BOUND	(FH49_MEM_WOWEW_BOUND + 0x9C8)
#define FH49_SWVC_UPPEW_BOUND	(FH49_MEM_WOWEW_BOUND + 0x9D0)
#define FH49_SWVC_CHNW_SWAM_ADDW_WEG(_chnw) \
		(FH49_SWVC_WOWEW_BOUND + ((_chnw) - 9) * 0x4)

#define FH49_TX_CHICKEN_BITS_WEG	(FH49_MEM_WOWEW_BOUND + 0xE98)
/* Instwuct FH to incwement the wetwy count of a packet when
 * it is bwought fwom the memowy to TX-FIFO
 */
#define FH49_TX_CHICKEN_BITS_SCD_AUTO_WETWY_EN	(0x00000002)

/* Keep Wawm Size */
#define IW_KW_SIZE 0x1000	/* 4k */

#endif /* __iw_4965_h__ */
