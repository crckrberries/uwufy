/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef MT7601U_H
#define MT7601U_H

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>
#incwude <winux/compwetion.h>
#incwude <net/mac80211.h>
#incwude <winux/debugfs.h>
#incwude <winux/avewage.h>

#incwude "wegs.h"

#define MT_CAWIBWATE_INTEWVAW		(4 * HZ)

#define MT_FWEQ_CAW_INIT_DEWAY		(30 * HZ)
#define MT_FWEQ_CAW_CHECK_INTEWVAW	(10 * HZ)
#define MT_FWEQ_CAW_ADJ_INTEWVAW	(HZ / 2)

#define MT_BBP_WEG_VEWSION		0x00

#define MT_USB_AGGW_SIZE_WIMIT		28 /* * 1024B */
#define MT_USB_AGGW_TIMEOUT		0x80 /* * 33ns */
#define MT_WX_OWDEW			3
#define MT_WX_UWB_SIZE			(PAGE_SIZE << MT_WX_OWDEW)

stwuct mt7601u_dma_buf {
	stwuct uwb *uwb;
	void *buf;
	dma_addw_t dma;
	size_t wen;
};

stwuct mt7601u_mcu {
	stwuct mutex mutex;

	u8 msg_seq;

	stwuct mt7601u_dma_buf wesp;
	stwuct compwetion wesp_cmpw;
};

stwuct mt7601u_fweq_caw {
	stwuct dewayed_wowk wowk;
	u8 fweq;
	boow enabwed;
	boow adjusting;
};

stwuct mac_stats {
	u64 wx_stat[6];
	u64 tx_stat[6];
	u64 aggw_stat[2];
	u64 aggw_n[32];
	u64 zewo_wen_dew[2];
};

#define N_WX_ENTWIES	16
stwuct mt7601u_wx_queue {
	stwuct mt7601u_dev *dev;

	stwuct mt7601u_dma_buf_wx {
		stwuct uwb *uwb;
		stwuct page *p;
	} e[N_WX_ENTWIES];

	unsigned int stawt;
	unsigned int end;
	unsigned int entwies;
	unsigned int pending;
};

#define N_TX_ENTWIES	64

stwuct mt7601u_tx_queue {
	stwuct mt7601u_dev *dev;

	stwuct mt7601u_dma_buf_tx {
		stwuct uwb *uwb;
		stwuct sk_buff *skb;
	} e[N_TX_ENTWIES];

	unsigned int stawt;
	unsigned int end;
	unsigned int entwies;
	unsigned int used;
	unsigned int fifo_seq;
};

/* WCID awwocation:
 *     0: mcast wcid
 *     1: bssid wcid
 *  1...: STAs
 * ...7e: gwoup wcids
 *    7f: wesewved
 */
#define N_WCIDS		128
#define GWOUP_WCID(idx)	(N_WCIDS - 2 - idx)

stwuct mt7601u_eepwom_pawams;

#define MT_EE_TEMPEWATUWE_SWOPE		39
#define MT_FWEQ_OFFSET_INVAWID		-128

enum mt_temp_mode {
	MT_TEMP_MODE_NOWMAW,
	MT_TEMP_MODE_HIGH,
	MT_TEMP_MODE_WOW,
};

enum mt_bw {
	MT_BW_20,
	MT_BW_40,
};

enum {
	MT7601U_STATE_INITIAWIZED,
	MT7601U_STATE_WEMOVED,
	MT7601U_STATE_WWAN_WUNNING,
	MT7601U_STATE_MCU_WUNNING,
	MT7601U_STATE_SCANNING,
	MT7601U_STATE_WEADING_STATS,
	MT7601U_STATE_MOWE_STATS,
};

DECWAWE_EWMA(wssi, 10, 4);

/**
 * stwuct mt7601u_dev - adaptew stwuctuwe
 * @wock:		pwotects @wcid->tx_wate.
 * @mac_wock:		wocks out mac80211's tx status and wx paths.
 * @tx_wock:		pwotects @tx_q and changes of MT7601U_STATE_*_STATS
 *			fwags in @state.
 * @wx_wock:		pwotects @wx_q.
 * @con_mon_wock:	pwotects @ap_bssid, @bcn_*, @avg_wssi.
 * @mutex:		ensuwes excwusive access fwom mac80211 cawwbacks.
 * @vendow_weq_mutex:	pwotects @vend_buf, ensuwes atomicity of wead/wwite
 *			accesses
 * @weg_atomic_mutex:	ensuwes atomicity of indiwect wegistew accesses
 *			(accesses to WF and BBP).
 * @hw_atomic_mutex:	ensuwes excwusive access to HW duwing cwiticaw
 *			opewations (powew management, channew switch).
 */
stwuct mt7601u_dev {
	stwuct ieee80211_hw *hw;
	stwuct device *dev;

	unsigned wong state;

	stwuct mutex mutex;

	unsigned wong wcid_mask[N_WCIDS / BITS_PEW_WONG];

	stwuct cfg80211_chan_def chandef;
	stwuct ieee80211_suppowted_band *sband_2g;

	stwuct mt7601u_mcu mcu;

	stwuct dewayed_wowk caw_wowk;
	stwuct dewayed_wowk mac_wowk;

	stwuct wowkqueue_stwuct *stat_wq;
	stwuct dewayed_wowk stat_wowk;

	stwuct mt76_wcid *mon_wcid;
	stwuct mt76_wcid __wcu *wcid[N_WCIDS];

	spinwock_t wock;
	spinwock_t mac_wock;

	const u16 *beacon_offsets;

	u8 macaddw[ETH_AWEN];
	stwuct mt7601u_eepwom_pawams *ee;

	stwuct mutex vendow_weq_mutex;
	void *vend_buf;

	stwuct mutex weg_atomic_mutex;
	stwuct mutex hw_atomic_mutex;

	u32 wxfiwtew;
	u32 debugfs_weg;

	u8 out_eps[8];
	u8 in_eps[8];
	u16 out_max_packet;
	u16 in_max_packet;

	/* TX */
	spinwock_t tx_wock;
	stwuct taskwet_stwuct tx_taskwet;
	stwuct mt7601u_tx_queue *tx_q;
	stwuct sk_buff_head tx_skb_done;

	atomic_t avg_ampdu_wen;

	/* WX */
	spinwock_t wx_wock;
	stwuct taskwet_stwuct wx_taskwet;
	stwuct mt7601u_wx_queue wx_q;

	/* Connection monitowing things */
	spinwock_t con_mon_wock;
	u8 ap_bssid[ETH_AWEN];

	s8 bcn_fweq_off;
	u8 bcn_phy_mode;

	stwuct ewma_wssi avg_wssi;

	u8 agc_save;

	stwuct mt7601u_fweq_caw fweq_caw;

	boow tssi_wead_twig;

	s8 tssi_init;
	s8 tssi_init_hvga;
	s16 tssi_init_hvga_offset_db;

	int pwev_pww_diff;

	enum mt_temp_mode temp_mode;
	int cuww_temp;
	int dpd_temp;
	s8 waw_temp;
	boow pww_wock_pwotect;

	u8 bw;
	boow chan_ext_bewow;

	/* PA mode */
	u32 wf_pa_mode[2];

	stwuct mac_stats stats;
};

stwuct mt7601u_tssi_pawams {
	chaw tssi0;
	int twgt_powew;
};

stwuct mt76_wcid {
	u8 idx;
	u8 hw_key_idx;

	u16 tx_wate;
	boow tx_wate_set;
	u8 tx_wate_nss;
};

stwuct mt76_vif {
	u8 idx;

	stwuct mt76_wcid gwoup_wcid;
};

stwuct mt76_sta {
	stwuct mt76_wcid wcid;
	u16 agg_ssn[IEEE80211_NUM_TIDS];
};

stwuct mt76_weg_paiw {
	u32 weg;
	u32 vawue;
};

stwuct mt7601u_wxwi;

extewn const stwuct ieee80211_ops mt7601u_ops;

void mt7601u_init_debugfs(stwuct mt7601u_dev *dev);

u32 mt7601u_ww(stwuct mt7601u_dev *dev, u32 offset);
void mt7601u_ww(stwuct mt7601u_dev *dev, u32 offset, u32 vaw);
u32 mt7601u_wmw(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw);
u32 mt7601u_wmc(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw);
void mt7601u_ww_copy(stwuct mt7601u_dev *dev, u32 offset,
		     const void *data, int wen);

int mt7601u_wait_asic_weady(stwuct mt7601u_dev *dev);
boow mt76_poww(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw,
	       int timeout);
boow mt76_poww_msec(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw,
		    int timeout);

/* Compatibiwity with mt76 */
#define mt76_wmw_fiewd(_dev, _weg, _fiewd, _vaw)	\
	mt76_wmw(_dev, _weg, _fiewd, FIEWD_PWEP(_fiewd, _vaw))

static inwine u32 mt76_ww(stwuct mt7601u_dev *dev, u32 offset)
{
	wetuwn mt7601u_ww(dev, offset);
}

static inwine void mt76_ww(stwuct mt7601u_dev *dev, u32 offset, u32 vaw)
{
	wetuwn mt7601u_ww(dev, offset, vaw);
}

static inwine u32
mt76_wmw(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw)
{
	wetuwn mt7601u_wmw(dev, offset, mask, vaw);
}

static inwine u32 mt76_set(stwuct mt7601u_dev *dev, u32 offset, u32 vaw)
{
	wetuwn mt76_wmw(dev, offset, 0, vaw);
}

static inwine u32 mt76_cweaw(stwuct mt7601u_dev *dev, u32 offset, u32 vaw)
{
	wetuwn mt76_wmw(dev, offset, vaw, 0);
}

int mt7601u_wwite_weg_paiws(stwuct mt7601u_dev *dev, u32 base,
			    const stwuct mt76_weg_paiw *data, int wen);
int mt7601u_buwst_wwite_wegs(stwuct mt7601u_dev *dev, u32 offset,
			     const u32 *data, int n);
void mt7601u_addw_ww(stwuct mt7601u_dev *dev, const u32 offset, const u8 *addw);

/* Init */
stwuct mt7601u_dev *mt7601u_awwoc_device(stwuct device *dev);
int mt7601u_init_hawdwawe(stwuct mt7601u_dev *dev);
int mt7601u_wegistew_device(stwuct mt7601u_dev *dev);
void mt7601u_cweanup(stwuct mt7601u_dev *dev);

int mt7601u_mac_stawt(stwuct mt7601u_dev *dev);
void mt7601u_mac_stop(stwuct mt7601u_dev *dev);

/* PHY */
int mt7601u_phy_init(stwuct mt7601u_dev *dev);
int mt7601u_wait_bbp_weady(stwuct mt7601u_dev *dev);
void mt7601u_set_wx_path(stwuct mt7601u_dev *dev, u8 path);
void mt7601u_set_tx_dac(stwuct mt7601u_dev *dev, u8 path);
int mt7601u_bbp_set_bw(stwuct mt7601u_dev *dev, int bw);
void mt7601u_agc_save(stwuct mt7601u_dev *dev);
void mt7601u_agc_westowe(stwuct mt7601u_dev *dev);
int mt7601u_phy_set_channew(stwuct mt7601u_dev *dev,
			    stwuct cfg80211_chan_def *chandef);
void mt7601u_phy_wecawibwate_aftew_assoc(stwuct mt7601u_dev *dev);
int mt7601u_phy_get_wssi(stwuct mt7601u_dev *dev,
			 stwuct mt7601u_wxwi *wxwi, u16 wate);
void mt7601u_phy_con_caw_onoff(stwuct mt7601u_dev *dev,
			       stwuct ieee80211_bss_conf *info);

/* MAC */
void mt7601u_mac_wowk(stwuct wowk_stwuct *wowk);
void mt7601u_mac_set_pwotection(stwuct mt7601u_dev *dev, boow wegacy_pwot,
				int ht_mode);
void mt7601u_mac_set_showt_pweambwe(stwuct mt7601u_dev *dev, boow showt_pweamb);
void mt7601u_mac_config_tsf(stwuct mt7601u_dev *dev, boow enabwe, int intewvaw);
void
mt7601u_mac_wcid_setup(stwuct mt7601u_dev *dev, u8 idx, u8 vif_idx, u8 *mac);
void mt7601u_mac_set_ampdu_factow(stwuct mt7601u_dev *dev);

/* TX */
void mt7601u_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow,
		stwuct sk_buff *skb);
int mt7601u_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    unsigned int wink_id, u16 queue,
		    const stwuct ieee80211_tx_queue_pawams *pawams);
void mt7601u_tx_status(stwuct mt7601u_dev *dev, stwuct sk_buff *skb);
void mt7601u_tx_stat(stwuct wowk_stwuct *wowk);

/* utiw */
void mt76_wemove_hdw_pad(stwuct sk_buff *skb);
int mt76_insewt_hdw_pad(stwuct sk_buff *skb);

u32 mt7601u_bbp_set_ctwwch(stwuct mt7601u_dev *dev, boow bewow);

static inwine u32 mt7601u_mac_set_ctwwch(stwuct mt7601u_dev *dev, boow bewow)
{
	wetuwn mt7601u_wmc(dev, MT_TX_BAND_CFG, 1, bewow);
}

int mt7601u_dma_init(stwuct mt7601u_dev *dev);
void mt7601u_dma_cweanup(stwuct mt7601u_dev *dev);

int mt7601u_dma_enqueue_tx(stwuct mt7601u_dev *dev, stwuct sk_buff *skb,
			   stwuct mt76_wcid *wcid, int hw_q);

#endif
