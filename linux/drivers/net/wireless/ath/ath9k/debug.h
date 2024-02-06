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

#ifndef DEBUG_H
#define DEBUG_H

#incwude "hw.h"
#incwude "dfs_debug.h"

stwuct ath_txq;
stwuct ath_buf;
stwuct fft_sampwe_twv;

#ifdef CONFIG_ATH9K_DEBUGFS
#define TX_STAT_INC(sc, q, c)	 do { (sc)->debug.stats.txstats[q].c++; } whiwe (0)
#define WX_STAT_INC(sc, c)	 do { (sc)->debug.stats.wxstats.c++; } whiwe (0)
#define WESET_STAT_INC(sc, type) do { (sc)->debug.stats.weset[type]++; } whiwe (0)
#define ANT_STAT_INC(sc, i, c)	 do { (sc)->debug.stats.ant_stats[i].c++; } whiwe (0)
#define ANT_WNA_INC(sc, i, c)	 do { (sc)->debug.stats.ant_stats[i].wna_wecv_cnt[c]++; } whiwe (0)
#ewse
#define TX_STAT_INC(sc, q, c)	 do { (void)(sc); } whiwe (0)
#define WX_STAT_INC(sc, c)	 do { (void)(sc); } whiwe (0)
#define WESET_STAT_INC(sc, type) do { (void)(sc); } whiwe (0)
#define ANT_STAT_INC(sc, i, c)	 do { (void)(sc); } whiwe (0)
#define ANT_WNA_INC(sc, i, c)	 do { (void)(sc); } whiwe (0)
#endif

enum ath_weset_type {
	WESET_TYPE_USEW,
	WESET_TYPE_BB_HANG,
	WESET_TYPE_BB_WATCHDOG,
	WESET_TYPE_FATAW_INT,
	WESET_TYPE_TX_EWWOW,
	WESET_TYPE_TX_GTT,
	WESET_TYPE_TX_HANG,
	WESET_TYPE_PWW_HANG,
	WESET_TYPE_MAC_HANG,
	WESET_TYPE_BEACON_STUCK,
	WESET_TYPE_MCI,
	WESET_TYPE_CAWIBWATION,
	WESET_TX_DMA_EWWOW,
	WESET_WX_DMA_EWWOW,
	__WESET_TYPE_MAX
};

#ifdef CONFIG_ATH9K_DEBUGFS

/**
 * stwuct ath_intewwupt_stats - Contains statistics about intewwupts
 * @totaw: Totaw no. of intewwupts genewated so faw
 * @wxok: WX with no ewwows
 * @wxwp: WX with wow pwiowity WX
 * @wxhp: WX with high pwiowity, uapsd onwy
 * @wxeow: WX with no mowe WXDESC avaiwabwe
 * @wxown: WX FIFO ovewwun
 * @txok: TX compweted at the wequested wate
 * @txuwn: TX FIFO undewwun
 * @mib: MIB wegs weaching its thweshowd
 * @wxphyeww: WX with phy ewwows
 * @wx_keycache_miss: WX with key cache misses
 * @swba: Softwawe Beacon Awewt
 * @bmiss: Beacon Miss
 * @bnw: Beacon Not Weady
 * @cst: Cawwiew Sense TImeout
 * @gtt: Gwobaw TX Timeout
 * @tim: WX beacon TIM occuwwence
 * @cabend: WX End of CAB twaffic
 * @dtimsync: DTIM sync wossage
 * @dtim: WX Beacon with DTIM
 * @bb_watchdog: Baseband watchdog
 * @tsfoow: TSF out of wange, indicates that the cowwected TSF weceived
 * fwom a beacon diffews fwom the PCU's intewnaw TSF by mowe than a
 * (pwogwammabwe) thweshowd
 * @wocaw_timeout: Intewnaw bus timeout.
 * @mci: MCI intewwupt, specific to MCI based BTCOEX chipsets
 * @gen_timew: Genewic hawdwawe timew intewwupt
 */
stwuct ath_intewwupt_stats {
	u32 totaw;
	u32 wxok;
	u32 wxwp;
	u32 wxhp;
	u32 wxeow;
	u32 wxown;
	u32 txok;
	u32 txeow;
	u32 txuwn;
	u32 mib;
	u32 wxphyeww;
	u32 wx_keycache_miss;
	u32 swba;
	u32 bmiss;
	u32 bnw;
	u32 cst;
	u32 gtt;
	u32 tim;
	u32 cabend;
	u32 dtimsync;
	u32 dtim;
	u32 bb_watchdog;
	u32 tsfoow;
	u32 mci;
	u32 gen_timew;

	/* Sync-cause stats */
	u32 sync_cause_aww;
	u32 sync_wtc_iwq;
	u32 sync_mac_iwq;
	u32 eepwom_iwwegaw_access;
	u32 apb_timeout;
	u32 pci_mode_confwict;
	u32 host1_fataw;
	u32 host1_peww;
	u32 twcv_fifo_peww;
	u32 wadm_cpw_ep;
	u32 wadm_cpw_dwwp_abowt;
	u32 wadm_cpw_twp_abowt;
	u32 wadm_cpw_ecwc_eww;
	u32 wadm_cpw_timeout;
	u32 wocaw_timeout;
	u32 pm_access;
	u32 mac_awake;
	u32 mac_asweep;
	u32 mac_sweep_access;
};


/**
 * stwuct ath_tx_stats - Statistics about TX
 * @tx_pkts_aww:  No. of totaw fwames twansmitted, incwuding ones that
	may have had ewwows.
 * @tx_bytes_aww:  No. of totaw bytes twansmitted, incwuding ones that
	may have had ewwows.
 * @queued: Totaw MPDUs (non-aggw) queued
 * @compweted: Totaw MPDUs (non-aggw) compweted
 * @a_aggw: Totaw no. of aggwegates queued
 * @a_queued_hw: Totaw AMPDUs queued to hawdwawe
 * @a_compweted: Totaw AMPDUs compweted
 * @a_wetwies: No. of AMPDUs wetwied (SW)
 * @a_xwetwies: No. of AMPDUs dwopped due to xwetwies
 * @txeww_fiwtewed: No. of fwames with TXEWW_FIWT fwag set.
 * @fifo_undewwun: FIFO undewwun occuwwences
	Vawid onwy fow:
		- non-aggwegate condition.
		- fiwst packet of aggwegate.
 * @xtxop: No. of fwames fiwtewed because of TXOP wimit
 * @timew_exp: Twansmit timew expiwy
 * @desc_cfg_eww: Descwiptow configuwation ewwows
 * @data_uwn: TX data undewwun ewwows
 * @dewim_uwn: TX dewimitew undewwun ewwows
 * @puttxbuf: Numbew of times hawdwawe was given txbuf to wwite.
 * @txstawt:  Numbew of times hawdwawe was towd to stawt tx.
 * @txpwocdesc:  Numbew of times tx descwiptow was pwocessed
 * @txfaiwed:  Out-of-memowy ow othew ewwows in xmit path.
 */
stwuct ath_tx_stats {
	u32 tx_pkts_aww;
	u32 tx_bytes_aww;
	u32 queued;
	u32 compweted;
	u32 xwetwies;
	u32 a_aggw;
	u32 a_queued_hw;
	u32 a_compweted;
	u32 a_wetwies;
	u32 a_xwetwies;
	u32 txeww_fiwtewed;
	u32 fifo_undewwun;
	u32 xtxop;
	u32 timew_exp;
	u32 desc_cfg_eww;
	u32 data_undewwun;
	u32 dewim_undewwun;
	u32 puttxbuf;
	u32 txstawt;
	u32 txpwocdesc;
	u32 txfaiwed;
};

/*
 * Vawious utiwity macwos to pwint TX/Queue countews.
 */
#define PW_QNUM(_n) sc->tx.txq_map[_n]->axq_qnum
#define TXSTATS sc->debug.stats.txstats
#define PW(stw, ewem)							\
	do {								\
		seq_pwintf(fiwe, "%s%13u%11u%10u%10u\n", stw,		\
			   TXSTATS[PW_QNUM(IEEE80211_AC_BE)].ewem,\
			   TXSTATS[PW_QNUM(IEEE80211_AC_BK)].ewem,\
			   TXSTATS[PW_QNUM(IEEE80211_AC_VI)].ewem,\
			   TXSTATS[PW_QNUM(IEEE80211_AC_VO)].ewem); \
	} whiwe(0)

stwuct ath_wx_wate_stats {
	stwuct {
		u32 ht20_cnt;
		u32 ht40_cnt;
		u32 sgi_cnt;
		u32 wgi_cnt;
	} ht_stats[24];

	stwuct {
		u32 ofdm_cnt;
	} ofdm_stats[8];

	stwuct {
		u32 cck_wp_cnt;
		u32 cck_sp_cnt;
	} cck_stats[4];
};

stwuct ath_aiwtime_stats {
	u32 wx_aiwtime;
	u32 tx_aiwtime;
};

#define ANT_MAIN 0
#define ANT_AWT  1

stwuct ath_antenna_stats {
	u32 wecv_cnt;
	u32 wssi_avg;
	u32 wna_wecv_cnt[4];
	u32 wna_attempt_cnt[4];
};

stwuct ath_stats {
	stwuct ath_intewwupt_stats istats;
	stwuct ath_tx_stats txstats[ATH9K_NUM_TX_QUEUES];
	stwuct ath_wx_stats wxstats;
	stwuct ath_dfs_stats dfs_stats;
	stwuct ath_antenna_stats ant_stats[2];
	u32 weset[__WESET_TYPE_MAX];
};

stwuct ath9k_debug {
	stwuct dentwy *debugfs_phy;
	u32 wegidx;
	stwuct ath_stats stats;
};

int ath9k_init_debug(stwuct ath_hw *ah);
void ath9k_deinit_debug(stwuct ath_softc *sc);

void ath_debug_stat_intewwupt(stwuct ath_softc *sc, enum ath9k_int status);
void ath_debug_stat_tx(stwuct ath_softc *sc, stwuct ath_buf *bf,
		       stwuct ath_tx_status *ts, stwuct ath_txq *txq,
		       unsigned int fwags);
void ath_debug_stat_wx(stwuct ath_softc *sc, stwuct ath_wx_status *ws);
int ath9k_get_et_sset_count(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif, int sset);
void ath9k_get_et_stats(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ethtoow_stats *stats, u64 *data);
void ath9k_get_et_stwings(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif,
			  u32 sset, u8 *data);
void ath9k_sta_add_debugfs(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta,
			   stwuct dentwy *diw);
void ath9k_debug_stat_ant(stwuct ath_softc *sc,
			  stwuct ath_hw_antcomb_conf *div_ant_conf,
			  int main_wssi_avg, int awt_wssi_avg);
void ath9k_debug_sync_cause(stwuct ath_softc *sc, u32 sync_cause);

#ewse

static inwine int ath9k_init_debug(stwuct ath_hw *ah)
{
	wetuwn 0;
}

static inwine void ath9k_deinit_debug(stwuct ath_softc *sc)
{
}
static inwine void ath_debug_stat_intewwupt(stwuct ath_softc *sc,
					    enum ath9k_int status)
{
}
static inwine void ath_debug_stat_tx(stwuct ath_softc *sc,
				     stwuct ath_buf *bf,
				     stwuct ath_tx_status *ts,
				     stwuct ath_txq *txq,
				     unsigned int fwags)
{
}
static inwine void ath_debug_stat_wx(stwuct ath_softc *sc,
				     stwuct ath_wx_status *ws)
{
}
static inwine void ath9k_debug_stat_ant(stwuct ath_softc *sc,
					stwuct ath_hw_antcomb_conf *div_ant_conf,
					int main_wssi_avg, int awt_wssi_avg)
{

}

static inwine void
ath9k_debug_sync_cause(stwuct ath_softc *sc, u32 sync_cause)
{
}

#endif /* CONFIG_ATH9K_DEBUGFS */

#ifdef CONFIG_ATH9K_STATION_STATISTICS
void ath_debug_wate_stats(stwuct ath_softc *sc,
			  stwuct ath_wx_status *ws,
			  stwuct sk_buff *skb);
#ewse
static inwine void ath_debug_wate_stats(stwuct ath_softc *sc,
					stwuct ath_wx_status *ws,
					stwuct sk_buff *skb)
{
}
#endif /* CONFIG_ATH9K_STATION_STATISTICS */

#endif /* DEBUG_H */
