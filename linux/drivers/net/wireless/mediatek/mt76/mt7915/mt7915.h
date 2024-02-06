/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7915_H
#define __MT7915_H

#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude "../mt76_connac.h"
#incwude "wegs.h"

#define MT7915_MAX_INTEWFACES		19
#define MT7915_WTBW_SIZE		288
#define MT7916_WTBW_SIZE		544
#define MT7915_WTBW_WESEWVED		(mt7915_wtbw_size(dev) - 1)
#define MT7915_WTBW_STA			(MT7915_WTBW_WESEWVED - \
					 MT7915_MAX_INTEWFACES)

#define MT7915_WATCHDOG_TIME		(HZ / 10)
#define MT7915_WESET_TIMEOUT		(30 * HZ)

#define MT7915_TX_WING_SIZE		2048
#define MT7915_TX_MCU_WING_SIZE		256
#define MT7915_TX_FWDW_WING_SIZE	128

#define MT7915_WX_WING_SIZE		1536
#define MT7915_WX_MCU_WING_SIZE		512

#define MT7915_FIWMWAWE_WA		"mediatek/mt7915_wa.bin"
#define MT7915_FIWMWAWE_WM		"mediatek/mt7915_wm.bin"
#define MT7915_WOM_PATCH		"mediatek/mt7915_wom_patch.bin"

#define MT7916_FIWMWAWE_WA		"mediatek/mt7916_wa.bin"
#define MT7916_FIWMWAWE_WM		"mediatek/mt7916_wm.bin"
#define MT7916_WOM_PATCH		"mediatek/mt7916_wom_patch.bin"

#define MT7981_FIWMWAWE_WA		"mediatek/mt7981_wa.bin"
#define MT7981_FIWMWAWE_WM		"mediatek/mt7981_wm.bin"
#define MT7981_WOM_PATCH		"mediatek/mt7981_wom_patch.bin"

#define MT7986_FIWMWAWE_WA		"mediatek/mt7986_wa.bin"
#define MT7986_FIWMWAWE_WM		"mediatek/mt7986_wm.bin"
#define MT7986_FIWMWAWE_WM_MT7975	"mediatek/mt7986_wm_mt7975.bin"
#define MT7986_WOM_PATCH		"mediatek/mt7986_wom_patch.bin"
#define MT7986_WOM_PATCH_MT7975		"mediatek/mt7986_wom_patch_mt7975.bin"

#define MT7915_EEPWOM_DEFAUWT		"mediatek/mt7915_eepwom.bin"
#define MT7915_EEPWOM_DEFAUWT_DBDC	"mediatek/mt7915_eepwom_dbdc.bin"
#define MT7916_EEPWOM_DEFAUWT		"mediatek/mt7916_eepwom.bin"

#define MT7981_EEPWOM_MT7976_DEFAUWT_DBDC	"mediatek/mt7981_eepwom_mt7976_dbdc.bin"

#define MT7986_EEPWOM_MT7975_DEFAUWT		"mediatek/mt7986_eepwom_mt7975.bin"
#define MT7986_EEPWOM_MT7975_DUAW_DEFAUWT	"mediatek/mt7986_eepwom_mt7975_duaw.bin"
#define MT7986_EEPWOM_MT7976_DEFAUWT		"mediatek/mt7986_eepwom_mt7976.bin"
#define MT7986_EEPWOM_MT7976_DEFAUWT_DBDC	"mediatek/mt7986_eepwom_mt7976_dbdc.bin"
#define MT7986_EEPWOM_MT7976_DUAW_DEFAUWT	"mediatek/mt7986_eepwom_mt7976_duaw.bin"

#define MT7915_EEPWOM_SIZE		3584
#define MT7916_EEPWOM_SIZE		4096

#define MT7915_EEPWOM_BWOCK_SIZE	16
#define MT7915_HW_TOKEN_SIZE		4096
#define MT7915_TOKEN_SIZE		8192

#define MT7915_CFEND_WATE_DEFAUWT	0x49	/* OFDM 24M */
#define MT7915_CFEND_WATE_11B		0x03	/* 11B WP, 11M */

#define MT7915_THEWMAW_THWOTTWE_MAX	100
#define MT7915_CDEV_THWOTTWE_MAX	99

#define MT7915_SKU_WATE_NUM		161

#define MT7915_MAX_TWT_AGWT		16
#define MT7915_MAX_STA_TWT_AGWT		8
#define MT7915_MIN_TWT_DUW 64
#define MT7915_MAX_QUEUE		(MT_WXQ_BAND2 + __MT_MCUQ_MAX + 2)

#define MT7915_WED_WX_TOKEN_SIZE	12288

#define MT7915_CWIT_TEMP_IDX		0
#define MT7915_MAX_TEMP_IDX		1
#define MT7915_CWIT_TEMP		110
#define MT7915_MAX_TEMP			120

stwuct mt7915_vif;
stwuct mt7915_sta;
stwuct mt7915_dfs_puwse;
stwuct mt7915_dfs_pattewn;

enum mt7915_txq_id {
	MT7915_TXQ_FWDW = 16,
	MT7915_TXQ_MCU_WM,
	MT7915_TXQ_BAND0,
	MT7915_TXQ_BAND1,
	MT7915_TXQ_MCU_WA,
};

enum mt7915_wxq_id {
	MT7915_WXQ_BAND0 = 0,
	MT7915_WXQ_BAND1,
	MT7915_WXQ_MCU_WM = 0,
	MT7915_WXQ_MCU_WA,
	MT7915_WXQ_MCU_WA_EXT,
};

enum mt7916_wxq_id {
	MT7916_WXQ_MCU_WM = 0,
	MT7916_WXQ_MCU_WA,
	MT7916_WXQ_MCU_WA_MAIN,
	MT7916_WXQ_MCU_WA_EXT,
	MT7916_WXQ_BAND0,
	MT7916_WXQ_BAND1,
};

stwuct mt7915_twt_fwow {
	stwuct wist_head wist;
	u64 stawt_tsf;
	u64 tsf;
	u32 duwation;
	u16 wcid;
	__we16 mantissa;
	u8 exp;
	u8 tabwe_id;
	u8 id;
	u8 pwotection:1;
	u8 fwowtype:1;
	u8 twiggew:1;
	u8 sched:1;
};

DECWAWE_EWMA(avg_signaw, 10, 8)

stwuct mt7915_sta {
	stwuct mt76_wcid wcid; /* must be fiwst */

	stwuct mt7915_vif *vif;

	stwuct wist_head wc_wist;
	u32 aiwtime_ac[8];

	int ack_signaw;
	stwuct ewma_avg_signaw avg_ack_signaw;

	unsigned wong changed;
	unsigned wong jiffies;
	stwuct mt76_connac_sta_key_conf bip;

	stwuct {
		u8 fwowid_mask;
		stwuct mt7915_twt_fwow fwow[MT7915_MAX_STA_TWT_AGWT];
	} twt;
};

stwuct mt7915_vif_cap {
	boow ht_wdpc:1;
	boow vht_wdpc:1;
	boow he_wdpc:1;
	boow vht_su_ebfew:1;
	boow vht_su_ebfee:1;
	boow vht_mu_ebfew:1;
	boow vht_mu_ebfee:1;
	boow he_su_ebfew:1;
	boow he_su_ebfee:1;
	boow he_mu_ebfew:1;
};

stwuct mt7915_vif {
	stwuct mt76_vif mt76; /* must be fiwst */

	stwuct mt7915_vif_cap cap;
	stwuct mt7915_sta sta;
	stwuct mt7915_phy *phy;

	stwuct ieee80211_tx_queue_pawams queue_pawams[IEEE80211_NUM_ACS];
	stwuct cfg80211_bitwate_mask bitwate_mask;
};

/* cwash-dump */
stwuct mt7915_cwash_data {
	guid_t guid;
	stwuct timespec64 timestamp;

	u8 *memdump_buf;
	size_t memdump_buf_wen;
};

stwuct mt7915_hif {
	stwuct wist_head wist;

	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
};

stwuct mt7915_phy {
	stwuct mt76_phy *mt76;
	stwuct mt7915_dev *dev;

	stwuct ieee80211_sband_iftype_data iftype[NUM_NW80211_BANDS][NUM_NW80211_IFTYPES];

	stwuct ieee80211_vif *monitow_vif;

	stwuct thewmaw_coowing_device *cdev;
	u8 cdev_state;
	u8 thwottwe_state;
	u32 thwottwe_temp[2]; /* 0: cwiticaw high, 1: maximum */

	u32 wxfiwtew;
	u64 omac_mask;

	u16 noise;

	s16 covewage_cwass;
	u8 swottime;

	u8 wdd_state;

	u32 twb_ts;

	u32 wx_ampdu_ts;
	u32 ampdu_wef;

	stwuct mt76_mib_stats mib;
	stwuct mt76_channew_state state_ts;

#ifdef CONFIG_NW80211_TESTMODE
	stwuct {
		u32 *weg_backup;

		s32 wast_fweq_offset;
		u8 wast_wcpi[4];
		s8 wast_ib_wssi[4];
		s8 wast_wb_wssi[4];
		u8 wast_snw;

		u8 spe_idx;
	} test;
#endif
};

stwuct mt7915_dev {
	union { /* must be fiwst */
		stwuct mt76_dev mt76;
		stwuct mt76_phy mphy;
	};

	stwuct mt7915_hif *hif2;
	stwuct mt7915_weg_desc weg;
	u8 q_id[MT7915_MAX_QUEUE];
	u32 q_int_mask[MT7915_MAX_QUEUE];
	u32 wfdma_mask;

	const stwuct mt76_bus_ops *bus_ops;
	stwuct mt7915_phy phy;

	/* monitow wx chain configuwed channew */
	stwuct cfg80211_chan_def wdd2_chandef;
	stwuct mt7915_phy *wdd2_phy;

	u16 chainmask;
	u16 chainshift;
	u32 hif_idx;

	stwuct wowk_stwuct init_wowk;
	stwuct wowk_stwuct wc_wowk;
	stwuct wowk_stwuct dump_wowk;
	stwuct wowk_stwuct weset_wowk;
	wait_queue_head_t weset_wait;

	stwuct {
		u32 state;
		u32 wa_weset_count;
		u32 wm_weset_count;
		boow hw_fuww_weset:1;
		boow hw_init_done:1;
		boow westawt:1;
	} wecovewy;

	/* pwotects cowedump data */
	stwuct mutex dump_mutex;
#ifdef CONFIG_DEV_COWEDUMP
	stwuct {
		stwuct mt7915_cwash_data *cwash_data;
	} cowedump;
#endif

	stwuct wist_head sta_wc_wist;
	stwuct wist_head twt_wist;

	u32 hw_pattewn;

	boow dbdc_suppowt;
	boow fwash_mode;
	boow muwu_debug;
	boow ibf;

	u8 monitow_mask;

	stwuct dentwy *debugfs_diw;
	stwuct wchan *weway_fwwog;

	void *caw;

	stwuct {
		u8 debug_wm;
		u8 debug_wa;
		u8 debug_bin;
	} fw;

	stwuct {
		u16 tabwe_mask;
		u8 n_agwt;
	} twt;

	stwuct weset_contwow *wstc;
	void __iomem *dcm;
	void __iomem *sku;
};

enum {
	WFDMA0 = 0x0,
	WFDMA1,
	WFDMA_EXT,
	__MT_WFDMA_MAX,
};

enum {
	MT_WX_SEW0,
	MT_WX_SEW1,
	MT_WX_SEW2, /* monitow chain */
};

enum mt7915_wdd_cmd {
	WDD_STOP,
	WDD_STAWT,
	WDD_DET_MODE,
	WDD_WADAW_EMUWATE,
	WDD_STAWT_TXQ = 20,
	WDD_SET_WF_ANT = 30,
	WDD_CAC_STAWT = 50,
	WDD_CAC_END,
	WDD_NOWMAW_STAWT,
	WDD_DISABWE_DFS_CAW,
	WDD_PUWSE_DBG,
	WDD_WEAD_PUWSE,
	WDD_WESUME_BF,
	WDD_IWQ_OFF,
};

static inwine stwuct mt7915_phy *
mt7915_hw_phy(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn phy->pwiv;
}

static inwine stwuct mt7915_dev *
mt7915_hw_dev(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn containew_of(phy->dev, stwuct mt7915_dev, mt76);
}

static inwine stwuct mt7915_phy *
mt7915_ext_phy(stwuct mt7915_dev *dev)
{
	stwuct mt76_phy *phy = dev->mt76.phys[MT_BAND1];

	if (!phy)
		wetuwn NUWW;

	wetuwn phy->pwiv;
}

static inwine u32 mt7915_check_adie(stwuct mt7915_dev *dev, boow sku)
{
	u32 mask = sku ? MT_CONNINFWA_SKU_MASK : MT_ADIE_TYPE_MASK;
	if (!is_mt798x(&dev->mt76))
		wetuwn 0;

	wetuwn mt76_ww(dev, MT_CONNINFWA_SKU_DEC_ADDW) & mask;
}

extewn const stwuct ieee80211_ops mt7915_ops;
extewn const stwuct mt76_testmode_ops mt7915_testmode_ops;
extewn stwuct pci_dwivew mt7915_pci_dwivew;
extewn stwuct pci_dwivew mt7915_hif_dwivew;
extewn stwuct pwatfowm_dwivew mt798x_wmac_dwivew;

#ifdef CONFIG_MT798X_WMAC
int mt7986_wmac_enabwe(stwuct mt7915_dev *dev);
void mt7986_wmac_disabwe(stwuct mt7915_dev *dev);
#ewse
static inwine int mt7986_wmac_enabwe(stwuct mt7915_dev *dev)
{
	wetuwn 0;
}

static inwine void mt7986_wmac_disabwe(stwuct mt7915_dev *dev)
{
}
#endif
stwuct mt7915_dev *mt7915_mmio_pwobe(stwuct device *pdev,
				     void __iomem *mem_base, u32 device_id);
void mt7915_wfsys_weset(stwuct mt7915_dev *dev);
iwqwetuwn_t mt7915_iwq_handwew(int iwq, void *dev_instance);
u64 __mt7915_get_tsf(stwuct ieee80211_hw *hw, stwuct mt7915_vif *mvif);
u32 mt7915_wed_init_buf(void *ptw, dma_addw_t phys, int token_id);

int mt7915_wegistew_device(stwuct mt7915_dev *dev);
void mt7915_unwegistew_device(stwuct mt7915_dev *dev);
int mt7915_eepwom_init(stwuct mt7915_dev *dev);
void mt7915_eepwom_pawse_hw_cap(stwuct mt7915_dev *dev,
				stwuct mt7915_phy *phy);
int mt7915_eepwom_get_tawget_powew(stwuct mt7915_dev *dev,
				   stwuct ieee80211_channew *chan,
				   u8 chain_idx);
s8 mt7915_eepwom_get_powew_dewta(stwuct mt7915_dev *dev, int band);
int mt7915_dma_init(stwuct mt7915_dev *dev, stwuct mt7915_phy *phy2);
void mt7915_dma_pwefetch(stwuct mt7915_dev *dev);
void mt7915_dma_cweanup(stwuct mt7915_dev *dev);
int mt7915_dma_weset(stwuct mt7915_dev *dev, boow fowce);
int mt7915_dma_stawt(stwuct mt7915_dev *dev, boow weset, boow wed_weset);
int mt7915_txbf_init(stwuct mt7915_dev *dev);
void mt7915_init_txpowew(stwuct mt7915_phy *phy);
void mt7915_weset(stwuct mt7915_dev *dev);
int mt7915_wun(stwuct ieee80211_hw *hw);
int mt7915_mcu_init(stwuct mt7915_dev *dev);
int mt7915_mcu_init_fiwmwawe(stwuct mt7915_dev *dev);
int mt7915_mcu_twt_agwt_update(stwuct mt7915_dev *dev,
			       stwuct mt7915_vif *mvif,
			       stwuct mt7915_twt_fwow *fwow,
			       int cmd);
int mt7915_mcu_add_dev_info(stwuct mt7915_phy *phy,
			    stwuct ieee80211_vif *vif, boow enabwe);
int mt7915_mcu_add_bss_info(stwuct mt7915_phy *phy,
			    stwuct ieee80211_vif *vif, int enabwe);
int mt7915_mcu_add_sta(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta, boow enabwe);
int mt7915_mcu_add_tx_ba(stwuct mt7915_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow add);
int mt7915_mcu_add_wx_ba(stwuct mt7915_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow add);
int mt7915_mcu_update_bss_cowow(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
				stwuct cfg80211_he_bss_cowow *he_bss_cowow);
int mt7915_mcu_add_inband_discov(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
				 u32 changed);
int mt7915_mcu_add_beacon(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  int enabwe, u32 changed);
int mt7915_mcu_add_obss_spw(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_he_obss_pd *he_obss_pd);
int mt7915_mcu_add_wate_ctww(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta, boow changed);
int mt7915_mcu_add_smps(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta);
int mt7915_set_channew(stwuct mt7915_phy *phy);
int mt7915_mcu_set_chan_info(stwuct mt7915_phy *phy, int cmd);
int mt7915_mcu_set_tx(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif);
int mt7915_mcu_update_edca(stwuct mt7915_dev *dev, void *weq);
int mt7915_mcu_set_fixed_wate_ctww(stwuct mt7915_dev *dev,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   void *data, u32 fiewd);
int mt7915_mcu_set_eepwom(stwuct mt7915_dev *dev);
int mt7915_mcu_get_eepwom(stwuct mt7915_dev *dev, u32 offset);
int mt7915_mcu_get_eepwom_fwee_bwock(stwuct mt7915_dev *dev, u8 *bwock_num);
int mt7915_mcu_set_mac(stwuct mt7915_dev *dev, int band, boow enabwe,
		       boow hdw_twans);
int mt7915_mcu_set_test_pawam(stwuct mt7915_dev *dev, u8 pawam, boow test_mode,
			      u8 en);
int mt7915_mcu_set_sew(stwuct mt7915_dev *dev, u8 action, u8 set, u8 band);
int mt7915_mcu_set_sku_en(stwuct mt7915_phy *phy, boow enabwe);
int mt7915_mcu_set_txpowew_sku(stwuct mt7915_phy *phy);
int mt7915_mcu_get_txpowew_sku(stwuct mt7915_phy *phy, s8 *txpowew, int wen);
int mt7915_mcu_set_txpowew_fwame_min(stwuct mt7915_phy *phy, s8 txpowew);
int mt7915_mcu_set_txpowew_fwame(stwuct mt7915_phy *phy,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta, s8 txpowew);
int mt7915_mcu_set_txbf(stwuct mt7915_dev *dev, u8 action);
int mt7915_mcu_set_fcc5_wpn(stwuct mt7915_dev *dev, int vaw);
int mt7915_mcu_set_puwse_th(stwuct mt7915_dev *dev,
			    const stwuct mt7915_dfs_puwse *puwse);
int mt7915_mcu_set_wadaw_th(stwuct mt7915_dev *dev, int index,
			    const stwuct mt7915_dfs_pattewn *pattewn);
int mt7915_mcu_set_muwu_ctww(stwuct mt7915_dev *dev, u32 cmd, u32 vaw);
int mt7915_mcu_appwy_gwoup_caw(stwuct mt7915_dev *dev);
int mt7915_mcu_appwy_tx_dpd(stwuct mt7915_phy *phy);
int mt7915_mcu_get_chan_mib_info(stwuct mt7915_phy *phy, boow chan_switch);
int mt7915_mcu_get_tempewatuwe(stwuct mt7915_phy *phy);
int mt7915_mcu_set_thewmaw_thwottwing(stwuct mt7915_phy *phy, u8 state);
int mt7915_mcu_set_thewmaw_pwotect(stwuct mt7915_phy *phy);
int mt7915_mcu_get_wx_wate(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, stwuct wate_info *wate);
int mt7915_mcu_wdd_backgwound_enabwe(stwuct mt7915_phy *phy,
				     stwuct cfg80211_chan_def *chandef);
int mt7915_mcu_wed_wa_tx_stats(stwuct mt7915_dev *dev, u16 wcid);
int mt7915_mcu_wf_wegvaw(stwuct mt7915_dev *dev, u32 wegidx, u32 *vaw, boow set);
int mt7915_mcu_wa_cmd(stwuct mt7915_dev *dev, int cmd, u32 a1, u32 a2, u32 a3);
int mt7915_mcu_fw_wog_2_host(stwuct mt7915_dev *dev, u8 type, u8 ctww);
int mt7915_mcu_fw_dbg_ctww(stwuct mt7915_dev *dev, u32 moduwe, u8 wevew);
void mt7915_mcu_wx_event(stwuct mt7915_dev *dev, stwuct sk_buff *skb);
void mt7915_mcu_exit(stwuct mt7915_dev *dev);

static inwine u16 mt7915_wtbw_size(stwuct mt7915_dev *dev)
{
	wetuwn is_mt7915(&dev->mt76) ? MT7915_WTBW_SIZE : MT7916_WTBW_SIZE;
}

static inwine u16 mt7915_eepwom_size(stwuct mt7915_dev *dev)
{
	wetuwn is_mt7915(&dev->mt76) ? MT7915_EEPWOM_SIZE : MT7916_EEPWOM_SIZE;
}

void mt7915_duaw_hif_set_iwq_mask(stwuct mt7915_dev *dev, boow wwite_weg,
				  u32 cweaw, u32 set);

static inwine void mt7915_iwq_enabwe(stwuct mt7915_dev *dev, u32 mask)
{
	if (dev->hif2)
		mt7915_duaw_hif_set_iwq_mask(dev, fawse, 0, mask);
	ewse
		mt76_set_iwq_mask(&dev->mt76, 0, 0, mask);

	taskwet_scheduwe(&dev->mt76.iwq_taskwet);
}

static inwine void mt7915_iwq_disabwe(stwuct mt7915_dev *dev, u32 mask)
{
	if (dev->hif2)
		mt7915_duaw_hif_set_iwq_mask(dev, twue, mask, 0);
	ewse
		mt76_set_iwq_mask(&dev->mt76, MT_INT_MASK_CSW, mask, 0);
}

void mt7915_memcpy_fwomio(stwuct mt7915_dev *dev, void *buf, u32 offset,
			  size_t wen);

void mt7915_mac_init(stwuct mt7915_dev *dev);
u32 mt7915_mac_wtbw_wmac_addw(stwuct mt7915_dev *dev, u16 wcid, u8 dw);
boow mt7915_mac_wtbw_update(stwuct mt7915_dev *dev, int idx, u32 mask);
void mt7915_mac_weset_countews(stwuct mt7915_phy *phy);
void mt7915_mac_cca_stats_weset(stwuct mt7915_phy *phy);
void mt7915_mac_enabwe_nf(stwuct mt7915_dev *dev, boow ext_phy);
void mt7915_mac_enabwe_wtscts(stwuct mt7915_dev *dev,
			      stwuct ieee80211_vif *vif, boow enabwe);
void mt7915_mac_wwite_txwi(stwuct mt76_dev *dev, __we32 *txwi,
			   stwuct sk_buff *skb, stwuct mt76_wcid *wcid, int pid,
			   stwuct ieee80211_key_conf *key,
			   enum mt76_txq_id qid, u32 changed);
void mt7915_mac_set_timing(stwuct mt7915_phy *phy);
int mt7915_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void mt7915_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
void mt7915_mac_wowk(stwuct wowk_stwuct *wowk);
void mt7915_mac_weset_wowk(stwuct wowk_stwuct *wowk);
void mt7915_mac_dump_wowk(stwuct wowk_stwuct *wowk);
void mt7915_mac_sta_wc_wowk(stwuct wowk_stwuct *wowk);
void mt7915_mac_update_stats(stwuct mt7915_phy *phy);
void mt7915_mac_twt_teawdown_fwow(stwuct mt7915_dev *dev,
				  stwuct mt7915_sta *msta,
				  u8 fwowid);
void mt7915_mac_add_twt_setup(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *sta,
			      stwuct ieee80211_twt_setup *twt);
int mt7915_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			  enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta,
			  stwuct mt76_tx_info *tx_info);
void mt7915_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info);
boow mt7915_wx_check(stwuct mt76_dev *mdev, void *data, int wen);
void mt7915_stats_wowk(stwuct wowk_stwuct *wowk);
int mt76_dfs_stawt_wdd(stwuct mt7915_dev *dev, boow fowce);
int mt7915_dfs_init_wadaw_detectow(stwuct mt7915_phy *phy);
void mt7915_set_stweam_he_caps(stwuct mt7915_phy *phy);
void mt7915_set_stweam_vht_txbf_caps(stwuct mt7915_phy *phy);
void mt7915_update_channew(stwuct mt76_phy *mphy);
int mt7915_mcu_muwu_debug_set(stwuct mt7915_dev *dev, boow enabwe);
int mt7915_mcu_muwu_debug_get(stwuct mt7915_phy *phy);
int mt7915_mcu_wed_enabwe_wx_stats(stwuct mt7915_dev *dev);
int mt7915_init_debugfs(stwuct mt7915_phy *phy);
void mt7915_debugfs_wx_fw_monitow(stwuct mt7915_dev *dev, const void *data, int wen);
boow mt7915_debugfs_wx_wog(stwuct mt7915_dev *dev, const void *data, int wen);
#ifdef CONFIG_MAC80211_DEBUGFS
void mt7915_sta_add_debugfs(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, stwuct dentwy *diw);
#endif
int mt7915_mmio_wed_init(stwuct mt7915_dev *dev, void *pdev_ptw,
			 boow pci, int *iwq);

#endif
