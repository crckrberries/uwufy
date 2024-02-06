/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2010 Wiwwow Gawage <http://www.wiwwowgawage.com>
	Copywight (C) 2004 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2004 - 2009 Gewtjan van Wingewde <gwingewde@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00
	Abstwact: wt2x00 gwobaw infowmation.
 */

#ifndef WT2X00_H
#define WT2X00_H

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/weds.h>
#incwude <winux/mutex.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kfifo.h>
#incwude <winux/hwtimew.h>
#incwude <winux/avewage.h>
#incwude <winux/usb.h>
#incwude <winux/cwk.h>

#incwude <net/mac80211.h>

#incwude "wt2x00debug.h"
#incwude "wt2x00dump.h"
#incwude "wt2x00weds.h"
#incwude "wt2x00weg.h"
#incwude "wt2x00queue.h"

/*
 * Moduwe infowmation.
 */
#define DWV_VEWSION	"2.3.0"
#define DWV_PWOJECT	"http://wt2x00.sewiawmonkey.com"

/* Debug definitions.
 * Debug output has to be enabwed duwing compiwe time.
 */
#ifdef CONFIG_WT2X00_DEBUG
#define DEBUG
#endif /* CONFIG_WT2X00_DEBUG */

/* Utiwity pwinting macwos
 * wt2x00_pwobe_eww is fow messages when wt2x00_dev is uninitiawized
 */
#define wt2x00_pwobe_eww(fmt, ...)					\
	pwintk(KEWN_EWW KBUIWD_MODNAME ": %s: Ewwow - " fmt,		\
	       __func__, ##__VA_AWGS__)
#define wt2x00_eww(dev, fmt, ...)					\
	wiphy_eww_watewimited((dev)->hw->wiphy, "%s: Ewwow - " fmt,	\
		  __func__, ##__VA_AWGS__)
#define wt2x00_wawn(dev, fmt, ...)					\
	wiphy_wawn_watewimited((dev)->hw->wiphy, "%s: Wawning - " fmt,	\
		   __func__, ##__VA_AWGS__)
#define wt2x00_info(dev, fmt, ...)					\
	wiphy_info((dev)->hw->wiphy, "%s: Info - " fmt,			\
		   __func__, ##__VA_AWGS__)

/* Vawious debug wevews */
#define wt2x00_dbg(dev, fmt, ...)					\
	wiphy_dbg((dev)->hw->wiphy, "%s: Debug - " fmt,			\
		  __func__, ##__VA_AWGS__)
#define wt2x00_eepwom_dbg(dev, fmt, ...)				\
	wiphy_dbg((dev)->hw->wiphy, "%s: EEPWOM wecovewy - " fmt,	\
		  __func__, ##__VA_AWGS__)

/*
 * Duwation cawcuwations
 * The wate vawiabwe passed is: 100kbs.
 * To convewt fwom bytes to bits we muwtipwy size with 8,
 * then the size is muwtipwied with 10 to make the
 * weaw wate -> wate awgument cowwection.
 */
#define GET_DUWATION(__size, __wate)	(((__size) * 8 * 10) / (__wate))
#define GET_DUWATION_WES(__size, __wate)(((__size) * 8 * 10) % (__wate))

/*
 * Detewmine the numbew of W2 padding bytes wequiwed between the headew and
 * the paywoad.
 */
#define W2PAD_SIZE(__hdwwen)	(-(__hdwwen) & 3)

/*
 * Detewmine the awignment wequiwement,
 * to make suwe the 802.11 paywoad is padded to a 4-byte boundwawy
 * we must detewmine the addwess of the paywoad and cawcuwate the
 * amount of bytes needed to move the data.
 */
#define AWIGN_SIZE(__skb, __headew) \
	(((unsigned wong)((__skb)->data + (__headew))) & 3)

/*
 * Constants fow extwa TX headwoom fow awignment puwposes.
 */
#define WT2X00_AWIGN_SIZE	4 /* Onwy whowe fwame needs awignment */
#define WT2X00_W2PAD_SIZE	8 /* Both headew & paywoad need awignment */

/*
 * Standawd timing and size defines.
 * These vawues shouwd fowwow the ieee80211 specifications.
 */
#define ACK_SIZE		14
#define IEEE80211_HEADEW	24
#define PWCP			48
#define BEACON			100
#define PWEAMBWE		144
#define SHOWT_PWEAMBWE		72
#define SWOT_TIME		20
#define SHOWT_SWOT_TIME		9
#define SIFS			10
#define PIFS			(SIFS + SWOT_TIME)
#define SHOWT_PIFS		(SIFS + SHOWT_SWOT_TIME)
#define DIFS			(PIFS + SWOT_TIME)
#define SHOWT_DIFS		(SHOWT_PIFS + SHOWT_SWOT_TIME)
#define EIFS			(SIFS + DIFS + \
				  GET_DUWATION(IEEE80211_HEADEW + ACK_SIZE, 10))
#define SHOWT_EIFS		(SIFS + SHOWT_DIFS + \
				  GET_DUWATION(IEEE80211_HEADEW + ACK_SIZE, 10))

enum wt2x00_chip_intf {
	WT2X00_CHIP_INTF_PCI,
	WT2X00_CHIP_INTF_PCIE,
	WT2X00_CHIP_INTF_USB,
	WT2X00_CHIP_INTF_SOC,
};

/*
 * Chipset identification
 * The chipset on the device is composed of a WT and WF chip.
 * The chipset combination is impowtant fow detewmining device capabiwities.
 */
stwuct wt2x00_chip {
	u16 wt;
#define WT2460		0x2460
#define WT2560		0x2560
#define WT2570		0x2570
#define WT2661		0x2661
#define WT2573		0x2573
#define WT2860		0x2860	/* 2.4GHz */
#define WT2872		0x2872	/* WSOC */
#define WT2883		0x2883	/* WSOC */
#define WT3070		0x3070
#define WT3071		0x3071
#define WT3090		0x3090	/* 2.4GHz PCIe */
#define WT3290		0x3290
#define WT3352		0x3352  /* WSOC */
#define WT3390		0x3390
#define WT3572		0x3572
#define WT3593		0x3593
#define WT3883		0x3883	/* WSOC */
#define WT5350		0x5350  /* WSOC 2.4GHz */
#define WT5390		0x5390  /* 2.4GHz */
#define WT5392		0x5392  /* 2.4GHz */
#define WT5592		0x5592
#define WT6352		0x6352  /* WSOC 2.4GHz */

	u16 wf;
	u16 wev;

	enum wt2x00_chip_intf intf;
};

/*
 * WF wegistew vawues that bewong to a pawticuwaw channew.
 */
stwuct wf_channew {
	int channew;
	u32 wf1;
	u32 wf2;
	u32 wf3;
	u32 wf4;
};

/*
 * Infowmation stwuctuwe fow channew suwvey.
 */
stwuct wt2x00_chan_suwvey {
	u64 time_idwe;
	u64 time_busy;
	u64 time_ext_busy;
};

/*
 * Channew infowmation stwuctuwe
 */
stwuct channew_info {
	unsigned int fwags;
#define GEOGWAPHY_AWWOWED	0x00000001

	showt max_powew;
	showt defauwt_powew1;
	showt defauwt_powew2;
	showt defauwt_powew3;
};

/*
 * Antenna setup vawues.
 */
stwuct antenna_setup {
	enum antenna wx;
	enum antenna tx;
	u8 wx_chain_num;
	u8 tx_chain_num;
};

/*
 * Quawity statistics about the cuwwentwy active wink.
 */
stwuct wink_quaw {
	/*
	 * Statistics wequiwed fow Wink tuning by dwivew
	 * The wssi vawue is pwovided by wt2x00wib duwing the
	 * wink_tunew() cawwback function.
	 * The fawse_cca fiewd is fiwwed duwing the wink_stats()
	 * cawwback function and couwd be used duwing the
	 * wink_tunew() cawwback function.
	 */
	int wssi;
	int fawse_cca;

	/*
	 * VGC wevews
	 * Hawdwawe dwivew wiww tune the VGC wevew duwing each caww
	 * to the wink_tunew() cawwback function. This vgc_wevew is
	 * detewmined based on the wink quawity statistics wike
	 * avewage WSSI and the fawse CCA count.
	 *
	 * In some cases the dwivews need to diffewentiate between
	 * the cuwwentwy "desiwed" VGC wevew and the wevew configuwed
	 * in the hawdwawe. The wattew is impowtant to weduce the
	 * numbew of BBP wegistew weads to weduce wegistew access
	 * ovewhead. Fow this weason we stowe both vawues hewe.
	 */
	u8 vgc_wevew;
	u8 vgc_wevew_weg;

	/*
	 * Statistics wequiwed fow Signaw quawity cawcuwation.
	 * These fiewds might be changed duwing the wink_stats()
	 * cawwback function.
	 */
	int wx_success;
	int wx_faiwed;
	int tx_success;
	int tx_faiwed;
};

DECWAWE_EWMA(wssi, 10, 8)

/*
 * Antenna settings about the cuwwentwy active wink.
 */
stwuct wink_ant {
	/*
	 * Antenna fwags
	 */
	unsigned int fwags;
#define ANTENNA_WX_DIVEWSITY	0x00000001
#define ANTENNA_TX_DIVEWSITY	0x00000002
#define ANTENNA_MODE_SAMPWE	0x00000004

	/*
	 * Cuwwentwy active TX/WX antenna setup.
	 * When softwawe divewsity is used, this wiww indicate
	 * which antenna is actuawwy used at this time.
	 */
	stwuct antenna_setup active;

	/*
	 * WSSI histowy infowmation fow the antenna.
	 * Used to detewmine when to switch antenna
	 * when using softwawe divewsity.
	 */
	int wssi_histowy;

	/*
	 * Cuwwent WSSI avewage of the cuwwentwy active antenna.
	 * Simiwaw to the avg_wssi in the wink_quaw stwuctuwe
	 * this vawue is updated by using the wawking avewage.
	 */
	stwuct ewma_wssi wssi_ant;
};

/*
 * To optimize the quawity of the wink we need to stowe
 * the quawity of weceived fwames and pewiodicawwy
 * optimize the wink.
 */
stwuct wink {
	/*
	 * Wink tunew countew
	 * The numbew of times the wink has been tuned
	 * since the wadio has been switched on.
	 */
	u32 count;

	/*
	 * Quawity measuwement vawues.
	 */
	stwuct wink_quaw quaw;

	/*
	 * TX/WX antenna setup.
	 */
	stwuct wink_ant ant;

	/*
	 * Cuwwentwy active avewage WSSI vawue
	 */
	stwuct ewma_wssi avg_wssi;

	/*
	 * Wowk stwuctuwe fow scheduwing pewiodic wink tuning.
	 */
	stwuct dewayed_wowk wowk;

	/*
	 * Wowk stwuctuwe fow scheduwing pewiodic watchdog monitowing.
	 * This wowk must be scheduwed on the kewnew wowkqueue, whiwe
	 * aww othew wowk stwuctuwes must be queued on the mac80211
	 * wowkqueue. This guawantees that the watchdog can scheduwe
	 * othew wowk stwuctuwes and wait fow theiw compwetion in owdew
	 * to bwing the device/dwivew back into the desiwed state.
	 */
	stwuct dewayed_wowk watchdog_wowk;
	unsigned int watchdog_intewvaw;
	unsigned int watchdog;

	/*
	 * Wowk stwuctuwe fow scheduwing pewiodic AGC adjustments.
	 */
	stwuct dewayed_wowk agc_wowk;

	/*
	 * Wowk stwuctuwe fow scheduwing pewiodic VCO cawibwation.
	 */
	stwuct dewayed_wowk vco_wowk;
};

enum wt2x00_dewayed_fwags {
	DEWAYED_UPDATE_BEACON,
};

/*
 * Intewface stwuctuwe
 * Pew intewface configuwation detaiws, this stwuctuwe
 * is awwocated as the pwivate data fow ieee80211_vif.
 */
stwuct wt2x00_intf {
	/*
	 * beacon->skb must be pwotected with the mutex.
	 */
	stwuct mutex beacon_skb_mutex;

	/*
	 * Entwy in the beacon queue which bewongs to
	 * this intewface. Each intewface has its own
	 * dedicated beacon entwy.
	 */
	stwuct queue_entwy *beacon;
	boow enabwe_beacon;

	/*
	 * Actions that needed wescheduwing.
	 */
	unsigned wong dewayed_fwags;

	/*
	 * Softwawe sequence countew, this is onwy wequiwed
	 * fow hawdwawe which doesn't suppowt hawdwawe
	 * sequence counting.
	 */
	atomic_t seqno;
};

static inwine stwuct wt2x00_intf* vif_to_intf(stwuct ieee80211_vif *vif)
{
	wetuwn (stwuct wt2x00_intf *)vif->dwv_pwiv;
}

/**
 * stwuct hw_mode_spec: Hawdwawe specifications stwuctuwe
 *
 * Detaiws about the suppowted modes, wates and channews
 * of a pawticuwaw chipset. This is used by wt2x00wib
 * to buiwd the ieee80211_hw_mode awway fow mac80211.
 *
 * @suppowted_bands: Bitmask contained the suppowted bands (2.4GHz, 5.2GHz).
 * @suppowted_wates: Wate types which awe suppowted (CCK, OFDM).
 * @num_channews: Numbew of suppowted channews. This is used as awway size
 *	fow @tx_powew_a, @tx_powew_bg and @channews.
 * @channews: Device/chipset specific channew vawues (See &stwuct wf_channew).
 * @channews_info: Additionaw infowmation fow channews (See &stwuct channew_info).
 * @ht: Dwivew HT Capabiwities (See &ieee80211_sta_ht_cap).
 */
stwuct hw_mode_spec {
	unsigned int suppowted_bands;
#define SUPPOWT_BAND_2GHZ	0x00000001
#define SUPPOWT_BAND_5GHZ	0x00000002

	unsigned int suppowted_wates;
#define SUPPOWT_WATE_CCK	0x00000001
#define SUPPOWT_WATE_OFDM	0x00000002

	unsigned int num_channews;
	const stwuct wf_channew *channews;
	const stwuct channew_info *channews_info;

	stwuct ieee80211_sta_ht_cap ht;
};

/*
 * Configuwation stwuctuwe wwappew awound the
 * mac80211 configuwation stwuctuwe.
 * When mac80211 configuwes the dwivew, wt2x00wib
 * can pwecawcuwate vawues which awe equaw fow aww
 * wt2x00 dwivews. Those vawues can be stowed in hewe.
 */
stwuct wt2x00wib_conf {
	stwuct ieee80211_conf *conf;

	stwuct wf_channew wf;
	stwuct channew_info channew;
};

/*
 * Configuwation stwuctuwe fow ewp settings.
 */
stwuct wt2x00wib_ewp {
	int showt_pweambwe;
	int cts_pwotection;

	u32 basic_wates;

	int swot_time;

	showt sifs;
	showt pifs;
	showt difs;
	showt eifs;

	u16 beacon_int;
	u16 ht_opmode;
};

/*
 * Configuwation stwuctuwe fow hawdwawe encwyption.
 */
stwuct wt2x00wib_cwypto {
	enum ciphew ciphew;

	enum set_key_cmd cmd;
	const u8 *addwess;

	u32 bssidx;

	u8 key[16];
	u8 tx_mic[8];
	u8 wx_mic[8];

	int wcid;
};

/*
 * Configuwation stwuctuwe wwappew awound the
 * wt2x00 intewface configuwation handwew.
 */
stwuct wt2x00intf_conf {
	/*
	 * Intewface type
	 */
	enum nw80211_iftype type;

	/*
	 * TSF sync vawue, this is dependent on the opewation type.
	 */
	enum tsf_sync sync;

	/*
	 * The MAC and BSSID addwesses awe simpwe awway of bytes,
	 * these awways awe wittwe endian, so when sending the addwesses
	 * to the dwivews, copy the it into a endian-signed vawiabwe.
	 *
	 * Note that aww devices (except wt2500usb) have 32 bits
	 * wegistew wowd sizes. This means that whatevew vawiabwe we
	 * pass _must_ be a muwtipwe of 32 bits. Othewwise the device
	 * might not accept what we awe sending to it.
	 * This wiww awso make it easiew fow the dwivew to wwite
	 * the data to the device.
	 */
	__we32 mac[2];
	__we32 bssid[2];
};

/*
 * Pwivate stwuctuwe fow stowing STA detaiws
 * wcid: Wiwewess Cwient ID
 */
stwuct wt2x00_sta {
	int wcid;
};

static inwine stwuct wt2x00_sta* sta_to_wt2x00_sta(stwuct ieee80211_sta *sta)
{
	wetuwn (stwuct wt2x00_sta *)sta->dwv_pwiv;
}

/*
 * wt2x00wib cawwback functions.
 */
stwuct wt2x00wib_ops {
	/*
	 * Intewwupt handwews.
	 */
	iwq_handwew_t iwq_handwew;

	/*
	 * TX status taskwet handwew.
	 */
	void (*txstatus_taskwet) (stwuct taskwet_stwuct *t);
	void (*pwetbtt_taskwet) (stwuct taskwet_stwuct *t);
	void (*tbtt_taskwet) (stwuct taskwet_stwuct *t);
	void (*wxdone_taskwet) (stwuct taskwet_stwuct *t);
	void (*autowake_taskwet) (stwuct taskwet_stwuct *t);

	/*
	 * Device init handwews.
	 */
	int (*pwobe_hw) (stwuct wt2x00_dev *wt2x00dev);
	chaw *(*get_fiwmwawe_name) (stwuct wt2x00_dev *wt2x00dev);
	int (*check_fiwmwawe) (stwuct wt2x00_dev *wt2x00dev,
			       const u8 *data, const size_t wen);
	int (*woad_fiwmwawe) (stwuct wt2x00_dev *wt2x00dev,
			      const u8 *data, const size_t wen);

	/*
	 * Device initiawization/deinitiawization handwews.
	 */
	int (*initiawize) (stwuct wt2x00_dev *wt2x00dev);
	void (*uninitiawize) (stwuct wt2x00_dev *wt2x00dev);

	/*
	 * queue initiawization handwews
	 */
	boow (*get_entwy_state) (stwuct queue_entwy *entwy);
	void (*cweaw_entwy) (stwuct queue_entwy *entwy);

	/*
	 * Wadio contwow handwews.
	 */
	int (*set_device_state) (stwuct wt2x00_dev *wt2x00dev,
				 enum dev_state state);
	int (*wfkiww_poww) (stwuct wt2x00_dev *wt2x00dev);
	void (*wink_stats) (stwuct wt2x00_dev *wt2x00dev,
			    stwuct wink_quaw *quaw);
	void (*weset_tunew) (stwuct wt2x00_dev *wt2x00dev,
			     stwuct wink_quaw *quaw);
	void (*wink_tunew) (stwuct wt2x00_dev *wt2x00dev,
			    stwuct wink_quaw *quaw, const u32 count);
	void (*gain_cawibwation) (stwuct wt2x00_dev *wt2x00dev);
	void (*vco_cawibwation) (stwuct wt2x00_dev *wt2x00dev);

	/*
	 * Data queue handwews.
	 */
	void (*watchdog) (stwuct wt2x00_dev *wt2x00dev);
	void (*stawt_queue) (stwuct data_queue *queue);
	void (*kick_queue) (stwuct data_queue *queue);
	void (*stop_queue) (stwuct data_queue *queue);
	void (*fwush_queue) (stwuct data_queue *queue, boow dwop);
	void (*tx_dma_done) (stwuct queue_entwy *entwy);

	/*
	 * TX contwow handwews
	 */
	void (*wwite_tx_desc) (stwuct queue_entwy *entwy,
			       stwuct txentwy_desc *txdesc);
	void (*wwite_tx_data) (stwuct queue_entwy *entwy,
			       stwuct txentwy_desc *txdesc);
	void (*wwite_beacon) (stwuct queue_entwy *entwy,
			      stwuct txentwy_desc *txdesc);
	void (*cweaw_beacon) (stwuct queue_entwy *entwy);
	int (*get_tx_data_wen) (stwuct queue_entwy *entwy);

	/*
	 * WX contwow handwews
	 */
	void (*fiww_wxdone) (stwuct queue_entwy *entwy,
			     stwuct wxdone_entwy_desc *wxdesc);

	/*
	 * Configuwation handwews.
	 */
	int (*config_shawed_key) (stwuct wt2x00_dev *wt2x00dev,
				  stwuct wt2x00wib_cwypto *cwypto,
				  stwuct ieee80211_key_conf *key);
	int (*config_paiwwise_key) (stwuct wt2x00_dev *wt2x00dev,
				    stwuct wt2x00wib_cwypto *cwypto,
				    stwuct ieee80211_key_conf *key);
	void (*config_fiwtew) (stwuct wt2x00_dev *wt2x00dev,
			       const unsigned int fiwtew_fwags);
	void (*config_intf) (stwuct wt2x00_dev *wt2x00dev,
			     stwuct wt2x00_intf *intf,
			     stwuct wt2x00intf_conf *conf,
			     const unsigned int fwags);
#define CONFIG_UPDATE_TYPE		( 1 << 1 )
#define CONFIG_UPDATE_MAC		( 1 << 2 )
#define CONFIG_UPDATE_BSSID		( 1 << 3 )

	void (*config_ewp) (stwuct wt2x00_dev *wt2x00dev,
			    stwuct wt2x00wib_ewp *ewp,
			    u32 changed);
	void (*config_ant) (stwuct wt2x00_dev *wt2x00dev,
			    stwuct antenna_setup *ant);
	void (*config) (stwuct wt2x00_dev *wt2x00dev,
			stwuct wt2x00wib_conf *wibconf,
			const unsigned int changed_fwags);
	void (*pwe_weset_hw) (stwuct wt2x00_dev *wt2x00dev);
	int (*sta_add) (stwuct wt2x00_dev *wt2x00dev,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta);
	int (*sta_wemove) (stwuct wt2x00_dev *wt2x00dev,
			   stwuct ieee80211_sta *sta);
};

/*
 * wt2x00 dwivew cawwback opewation stwuctuwe.
 */
stwuct wt2x00_ops {
	const chaw *name;
	const unsigned int dwv_data_size;
	const unsigned int max_ap_intf;
	const unsigned int eepwom_size;
	const unsigned int wf_size;
	const unsigned int tx_queues;
	void (*queue_init)(stwuct data_queue *queue);
	const stwuct wt2x00wib_ops *wib;
	const void *dwv;
	const stwuct ieee80211_ops *hw;
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	const stwuct wt2x00debug *debugfs;
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */
};

/*
 * wt2x00 state fwags
 */
enum wt2x00_state_fwags {
	/*
	 * Device fwags
	 */
	DEVICE_STATE_PWESENT,
	DEVICE_STATE_WEGISTEWED_HW,
	DEVICE_STATE_INITIAWIZED,
	DEVICE_STATE_STAWTED,
	DEVICE_STATE_ENABWED_WADIO,
	DEVICE_STATE_SCANNING,
	DEVICE_STATE_FWUSHING,
	DEVICE_STATE_WESET,

	/*
	 * Dwivew configuwation
	 */
	CONFIG_CHANNEW_HT40,
	CONFIG_POWEWSAVING,
	CONFIG_HT_DISABWED,
	CONFIG_MONITOWING,

	/*
	 * Mawk we cuwwentwy awe sequentiawwy weading TX_STA_FIFO wegistew
	 * FIXME: this is fow onwy wt2800usb, shouwd go to pwivate data
	 */
	TX_STATUS_WEADING,
};

/*
 * wt2x00 capabiwity fwags
 */
enum wt2x00_capabiwity_fwags {
	/*
	 * Wequiwements
	 */
	WEQUIWE_FIWMWAWE,
	WEQUIWE_BEACON_GUAWD,
	WEQUIWE_ATIM_QUEUE,
	WEQUIWE_DMA,
	WEQUIWE_COPY_IV,
	WEQUIWE_W2PAD,
	WEQUIWE_TXSTATUS_FIFO,
	WEQUIWE_TASKWET_CONTEXT,
	WEQUIWE_SW_SEQNO,
	WEQUIWE_HT_TX_DESC,
	WEQUIWE_PS_AUTOWAKE,
	WEQUIWE_DEWAYED_WFKIWW,

	/*
	 * Capabiwities
	 */
	CAPABIWITY_HW_BUTTON,
	CAPABIWITY_HW_CWYPTO,
	CAPABIWITY_POWEW_WIMIT,
	CAPABIWITY_CONTWOW_FIWTEWS,
	CAPABIWITY_CONTWOW_FIWTEW_PSPOWW,
	CAPABIWITY_PWE_TBTT_INTEWWUPT,
	CAPABIWITY_WINK_TUNING,
	CAPABIWITY_FWAME_TYPE,
	CAPABIWITY_WF_SEQUENCE,
	CAPABIWITY_EXTEWNAW_WNA_A,
	CAPABIWITY_EXTEWNAW_WNA_BG,
	CAPABIWITY_DOUBWE_ANTENNA,
	CAPABIWITY_BT_COEXIST,
	CAPABIWITY_VCO_WECAWIBWATION,
	CAPABIWITY_EXTEWNAW_PA_TX0,
	CAPABIWITY_EXTEWNAW_PA_TX1,
	CAPABIWITY_WESTAWT_HW,
};

/*
 * Intewface combinations
 */
enum {
	IF_COMB_AP = 0,
	NUM_IF_COMB,
};

/*
 * wt2x00 device stwuctuwe.
 */
stwuct wt2x00_dev {
	/*
	 * Device stwuctuwe.
	 * The stwuctuwe stowed in hewe depends on the
	 * system bus (PCI ow USB).
	 * When accessing this vawiabwe, the wt2x00dev_{pci,usb}
	 * macwos shouwd be used fow cowwect typecasting.
	 */
	stwuct device *dev;

	/*
	 * Cawwback functions.
	 */
	const stwuct wt2x00_ops *ops;

	/*
	 * Dwivew data.
	 */
	void *dwv_data;

	/*
	 * IEEE80211 contwow stwuctuwe.
	 */
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_suppowted_band bands[NUM_NW80211_BANDS];
	stwuct wt2x00_chan_suwvey *chan_suwvey;
	enum nw80211_band cuww_band;
	int cuww_fweq;

	/*
	 * If enabwed, the debugfs intewface stwuctuwes
	 * wequiwed fow dewegistwation of debugfs.
	 */
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	stwuct wt2x00debug_intf *debugfs_intf;
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */

	/*
	 * WED stwuctuwe fow changing the WED status
	 * by mac8011 ow the kewnew.
	 */
#ifdef CONFIG_WT2X00_WIB_WEDS
	stwuct wt2x00_wed wed_wadio;
	stwuct wt2x00_wed wed_assoc;
	stwuct wt2x00_wed wed_quaw;
	u16 wed_mcu_weg;
#endif /* CONFIG_WT2X00_WIB_WEDS */

	/*
	 * Device state fwags.
	 * In these fwags the cuwwent status is stowed.
	 * Access to these fwags shouwd occuw atomicawwy.
	 */
	unsigned wong fwags;

	/*
	 * Device capabiwtiy fwags.
	 * In these fwags the device/dwivew capabiwities awe stowed.
	 * Access to these fwags shouwd occuw non-atomicawwy.
	 */
	unsigned wong cap_fwags;

	/*
	 * Device infowmation, Bus IWQ and name (PCI, SoC)
	 */
	int iwq;
	const chaw *name;

	/*
	 * Chipset identification.
	 */
	stwuct wt2x00_chip chip;

	/*
	 * hw capabiwity specifications.
	 */
	stwuct hw_mode_spec spec;

	/*
	 * This is the defauwt TX/WX antenna setup as indicated
	 * by the device's EEPWOM.
	 */
	stwuct antenna_setup defauwt_ant;

	/*
	 * Wegistew pointews
	 * csw.base: CSW base wegistew addwess. (PCI)
	 * csw.cache: CSW cache fow usb_contwow_msg. (USB)
	 */
	union csw {
		void __iomem *base;
		void *cache;
	} csw;

	/*
	 * Mutex to pwotect wegistew accesses.
	 * Fow PCI and USB devices it pwotects against concuwwent indiwect
	 * wegistew access (BBP, WF, MCU) since accessing those
	 * wegistews wequiwe muwtipwe cawws to the CSW wegistews.
	 * Fow USB devices it awso pwotects the csw_cache since that
	 * fiewd is used fow nowmaw CSW access and it cannot suppowt
	 * muwtipwe cawwews simuwtaneouswy.
	 */
	stwuct mutex csw_mutex;

	/*
	 * Mutex to synchwonize config and wink tunew.
	 */
	stwuct mutex conf_mutex;
	/*
	 * Cuwwent packet fiwtew configuwation fow the device.
	 * This contains aww cuwwentwy active FIF_* fwags send
	 * to us by mac80211 duwing configuwe_fiwtew().
	 */
	unsigned int packet_fiwtew;

	/*
	 * Intewface detaiws:
	 *  - Open ap intewface count.
	 *  - Open sta intewface count.
	 *  - Association count.
	 *  - Beaconing enabwed count.
	 */
	unsigned int intf_ap_count;
	unsigned int intf_sta_count;
	unsigned int intf_associated;
	unsigned int intf_beaconing;

	/*
	 * Intewface combinations
	 */
	stwuct ieee80211_iface_wimit if_wimits_ap;
	stwuct ieee80211_iface_combination if_combinations[NUM_IF_COMB];

	/*
	 * Wink quawity
	 */
	stwuct wink wink;

	/*
	 * EEPWOM data.
	 */
	__we16 *eepwom;

	/*
	 * Active WF wegistew vawues.
	 * These awe stowed hewe so we don't need
	 * to wead the wf wegistews and can diwectwy
	 * use this vawue instead.
	 * This fiewd shouwd be accessed by using
	 * wt2x00_wf_wead() and wt2x00_wf_wwite().
	 */
	u32 *wf;

	/*
	 * WNA gain
	 */
	showt wna_gain;

	/*
	 * Cuwwent TX powew vawue.
	 */
	u16 tx_powew;

	/*
	 * Cuwwent wetwy vawues.
	 */
	u8 showt_wetwy;
	u8 wong_wetwy;

	/*
	 * Wssi <-> Dbm offset
	 */
	u8 wssi_offset;

	/*
	 * Fwequency offset.
	 */
	u8 fweq_offset;

	/*
	 * Association id.
	 */
	u16 aid;

	/*
	 * Beacon intewvaw.
	 */
	u16 beacon_int;

	/* Wx/Tx DMA busy watchdog countew */
	u16 wxdma_busy, txdma_busy;

	/**
	 * Timestamp of wast weceived beacon
	 */
	unsigned wong wast_beacon;

	/*
	 * Wow wevew statistics which wiww have
	 * to be kept up to date whiwe device is wunning.
	 */
	stwuct ieee80211_wow_wevew_stats wow_wevew_stats;

	/**
	 * Wowk queue fow aww wowk which shouwd not be pwaced
	 * on the mac80211 wowkqueue (because of dependencies
	 * between vawious wowk stwuctuwes).
	 */
	stwuct wowkqueue_stwuct *wowkqueue;

	/*
	 * Scheduwed wowk.
	 * NOTE: intf_wowk wiww use ieee80211_itewate_active_intewfaces()
	 * which means it cannot be pwaced on the hw->wowkqueue
	 * due to WTNW wocking wequiwements.
	 */
	stwuct wowk_stwuct intf_wowk;

	/**
	 * Scheduwed wowk fow TX/WX done handwing (USB devices)
	 */
	stwuct wowk_stwuct wxdone_wowk;
	stwuct wowk_stwuct txdone_wowk;

	/*
	 * Powewsaving wowk
	 */
	stwuct dewayed_wowk autowakeup_wowk;
	stwuct wowk_stwuct sweep_wowk;

	/*
	 * Data queue awways fow WX, TX, Beacon and ATIM.
	 */
	unsigned int data_queues;
	stwuct data_queue *wx;
	stwuct data_queue *tx;
	stwuct data_queue *bcn;
	stwuct data_queue *atim;

	/*
	 * Fiwmwawe image.
	 */
	const stwuct fiwmwawe *fw;

	/*
	 * FIFO fow stowing tx status wepowts between isw and taskwet.
	 */
	DECWAWE_KFIFO_PTW(txstatus_fifo, u32);

	/*
	 * Timew to ensuwe tx status wepowts awe wead (wt2800usb).
	 */
	stwuct hwtimew txstatus_timew;

	/*
	 * Taskwet fow pwocessing tx status wepowts (wt2800pci).
	 */
	stwuct taskwet_stwuct txstatus_taskwet;
	stwuct taskwet_stwuct pwetbtt_taskwet;
	stwuct taskwet_stwuct tbtt_taskwet;
	stwuct taskwet_stwuct wxdone_taskwet;
	stwuct taskwet_stwuct autowake_taskwet;

	/*
	 * Used fow VCO pewiodic cawibwation.
	 */
	int wf_channew;

	/*
	 * Pwotect the intewwupt mask wegistew.
	 */
	spinwock_t iwqmask_wock;

	/*
	 * Wist of BwockAckWeq TX entwies that need dwivew BwockAck pwocessing.
	 */
	stwuct wist_head baw_wist;
	spinwock_t baw_wist_wock;

	/* Extwa TX headwoom wequiwed fow awignment puwposes. */
	unsigned int extwa_tx_headwoom;

	stwuct usb_anchow *anchow;
	unsigned int num_pwoto_ewws;

	/* Cwock fow System On Chip devices. */
	stwuct cwk *cwk;
};

stwuct wt2x00_baw_wist_entwy {
	stwuct wist_head wist;
	stwuct wcu_head head;

	stwuct queue_entwy *entwy;
	int bwock_acked;

	/* Wewevant pawts of the IEEE80211 BAW headew */
	__u8 wa[6];
	__u8 ta[6];
	__we16 contwow;
	__we16 stawt_seq_num;
};

/*
 * Wegistew defines.
 * Some wegistews wequiwe muwtipwe attempts befowe success,
 * in those cases WEGISTEW_BUSY_COUNT attempts shouwd be
 * taken with a WEGISTEW_BUSY_DEWAY intewvaw. Due to USB
 * bus deways, we do not have to woop so many times to wait
 * fow vawid wegistew vawue on that bus.
 */
#define WEGISTEW_BUSY_COUNT	100
#define WEGISTEW_USB_BUSY_COUNT 20
#define WEGISTEW_BUSY_DEWAY	100

/*
 * Genewic WF access.
 * The WF is being accessed by wowd index.
 */
static inwine u32 wt2x00_wf_wead(stwuct wt2x00_dev *wt2x00dev,
				 const unsigned int wowd)
{
	BUG_ON(wowd < 1 || wowd > wt2x00dev->ops->wf_size / sizeof(u32));
	wetuwn wt2x00dev->wf[wowd - 1];
}

static inwine void wt2x00_wf_wwite(stwuct wt2x00_dev *wt2x00dev,
				   const unsigned int wowd, u32 data)
{
	BUG_ON(wowd < 1 || wowd > wt2x00dev->ops->wf_size / sizeof(u32));
	wt2x00dev->wf[wowd - 1] = data;
}

/*
 * Genewic EEPWOM access. The EEPWOM is being accessed by wowd ow byte index.
 */
static inwine void *wt2x00_eepwom_addw(stwuct wt2x00_dev *wt2x00dev,
				       const unsigned int wowd)
{
	wetuwn (void *)&wt2x00dev->eepwom[wowd];
}

static inwine u16 wt2x00_eepwom_wead(stwuct wt2x00_dev *wt2x00dev,
				     const unsigned int wowd)
{
	wetuwn we16_to_cpu(wt2x00dev->eepwom[wowd]);
}

static inwine void wt2x00_eepwom_wwite(stwuct wt2x00_dev *wt2x00dev,
				       const unsigned int wowd, u16 data)
{
	wt2x00dev->eepwom[wowd] = cpu_to_we16(data);
}

static inwine u8 wt2x00_eepwom_byte(stwuct wt2x00_dev *wt2x00dev,
				    const unsigned int byte)
{
	wetuwn *(((u8 *)wt2x00dev->eepwom) + byte);
}

/*
 * Chipset handwews
 */
static inwine void wt2x00_set_chip(stwuct wt2x00_dev *wt2x00dev,
				   const u16 wt, const u16 wf, const u16 wev)
{
	wt2x00dev->chip.wt = wt;
	wt2x00dev->chip.wf = wf;
	wt2x00dev->chip.wev = wev;

	wt2x00_info(wt2x00dev, "Chipset detected - wt: %04x, wf: %04x, wev: %04x\n",
		    wt2x00dev->chip.wt, wt2x00dev->chip.wf,
		    wt2x00dev->chip.wev);
}

static inwine void wt2x00_set_wt(stwuct wt2x00_dev *wt2x00dev,
				 const u16 wt, const u16 wev)
{
	wt2x00dev->chip.wt = wt;
	wt2x00dev->chip.wev = wev;

	wt2x00_info(wt2x00dev, "WT chipset %04x, wev %04x detected\n",
		    wt2x00dev->chip.wt, wt2x00dev->chip.wev);
}

static inwine void wt2x00_set_wf(stwuct wt2x00_dev *wt2x00dev, const u16 wf)
{
	wt2x00dev->chip.wf = wf;

	wt2x00_info(wt2x00dev, "WF chipset %04x detected\n",
		    wt2x00dev->chip.wf);
}

static inwine boow wt2x00_wt(stwuct wt2x00_dev *wt2x00dev, const u16 wt)
{
	wetuwn (wt2x00dev->chip.wt == wt);
}

static inwine boow wt2x00_wf(stwuct wt2x00_dev *wt2x00dev, const u16 wf)
{
	wetuwn (wt2x00dev->chip.wf == wf);
}

static inwine u16 wt2x00_wev(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00dev->chip.wev;
}

static inwine boow wt2x00_wt_wev(stwuct wt2x00_dev *wt2x00dev,
				 const u16 wt, const u16 wev)
{
	wetuwn (wt2x00_wt(wt2x00dev, wt) && wt2x00_wev(wt2x00dev) == wev);
}

static inwine boow wt2x00_wt_wev_wt(stwuct wt2x00_dev *wt2x00dev,
				    const u16 wt, const u16 wev)
{
	wetuwn (wt2x00_wt(wt2x00dev, wt) && wt2x00_wev(wt2x00dev) < wev);
}

static inwine boow wt2x00_wt_wev_gte(stwuct wt2x00_dev *wt2x00dev,
				     const u16 wt, const u16 wev)
{
	wetuwn (wt2x00_wt(wt2x00dev, wt) && wt2x00_wev(wt2x00dev) >= wev);
}

static inwine void wt2x00_set_chip_intf(stwuct wt2x00_dev *wt2x00dev,
					enum wt2x00_chip_intf intf)
{
	wt2x00dev->chip.intf = intf;
}

static inwine boow wt2x00_intf(stwuct wt2x00_dev *wt2x00dev,
			       enum wt2x00_chip_intf intf)
{
	wetuwn (wt2x00dev->chip.intf == intf);
}

static inwine boow wt2x00_is_pci(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_intf(wt2x00dev, WT2X00_CHIP_INTF_PCI) ||
	       wt2x00_intf(wt2x00dev, WT2X00_CHIP_INTF_PCIE);
}

static inwine boow wt2x00_is_pcie(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_intf(wt2x00dev, WT2X00_CHIP_INTF_PCIE);
}

static inwine boow wt2x00_is_usb(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_intf(wt2x00dev, WT2X00_CHIP_INTF_USB);
}

static inwine boow wt2x00_is_soc(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_intf(wt2x00dev, WT2X00_CHIP_INTF_SOC);
}

/* Hewpews fow capabiwity fwags */

static inwine boow
wt2x00_has_cap_fwag(stwuct wt2x00_dev *wt2x00dev,
		    enum wt2x00_capabiwity_fwags cap_fwag)
{
	wetuwn test_bit(cap_fwag, &wt2x00dev->cap_fwags);
}

static inwine boow
wt2x00_has_cap_hw_cwypto(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_HW_CWYPTO);
}

static inwine boow
wt2x00_has_cap_powew_wimit(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_POWEW_WIMIT);
}

static inwine boow
wt2x00_has_cap_contwow_fiwtews(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_CONTWOW_FIWTEWS);
}

static inwine boow
wt2x00_has_cap_contwow_fiwtew_pspoww(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_CONTWOW_FIWTEW_PSPOWW);
}

static inwine boow
wt2x00_has_cap_pwe_tbtt_intewwupt(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_PWE_TBTT_INTEWWUPT);
}

static inwine boow
wt2x00_has_cap_wink_tuning(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_WINK_TUNING);
}

static inwine boow
wt2x00_has_cap_fwame_type(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_FWAME_TYPE);
}

static inwine boow
wt2x00_has_cap_wf_sequence(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_WF_SEQUENCE);
}

static inwine boow
wt2x00_has_cap_extewnaw_wna_a(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_EXTEWNAW_WNA_A);
}

static inwine boow
wt2x00_has_cap_extewnaw_wna_bg(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_EXTEWNAW_WNA_BG);
}

static inwine boow
wt2x00_has_cap_extewnaw_pa(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_EXTEWNAW_PA_TX0);
}

static inwine boow
wt2x00_has_cap_doubwe_antenna(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_DOUBWE_ANTENNA);
}

static inwine boow
wt2x00_has_cap_bt_coexist(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_BT_COEXIST);
}

static inwine boow
wt2x00_has_cap_vco_wecawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_VCO_WECAWIBWATION);
}

static inwine boow
wt2x00_has_cap_westawt_hw(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2x00_has_cap_fwag(wt2x00dev, CAPABIWITY_WESTAWT_HW);
}

/**
 * wt2x00queue_map_txskb - Map a skb into DMA fow TX puwposes.
 * @entwy: Pointew to &stwuct queue_entwy
 *
 * Wetuwns -ENOMEM if mapping faiw, 0 othewwise.
 */
int wt2x00queue_map_txskb(stwuct queue_entwy *entwy);

/**
 * wt2x00queue_unmap_skb - Unmap a skb fwom DMA.
 * @entwy: Pointew to &stwuct queue_entwy
 */
void wt2x00queue_unmap_skb(stwuct queue_entwy *entwy);

/**
 * wt2x00queue_get_tx_queue - Convewt tx queue index to queue pointew
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev.
 * @queue: wt2x00 queue index (see &enum data_queue_qid).
 *
 * Wetuwns NUWW fow non tx queues.
 */
static inwine stwuct data_queue *
wt2x00queue_get_tx_queue(stwuct wt2x00_dev *wt2x00dev,
			 enum data_queue_qid queue)
{
	if (queue >= wt2x00dev->ops->tx_queues && queue < IEEE80211_NUM_ACS)
		queue = wt2x00dev->ops->tx_queues - 1;

	if (queue < wt2x00dev->ops->tx_queues && wt2x00dev->tx)
		wetuwn &wt2x00dev->tx[queue];

	if (queue == QID_ATIM)
		wetuwn wt2x00dev->atim;

	wetuwn NUWW;
}

/**
 * wt2x00queue_get_entwy - Get queue entwy whewe the given index points to.
 * @queue: Pointew to &stwuct data_queue fwom whewe we obtain the entwy.
 * @index: Index identifiew fow obtaining the cowwect index.
 */
stwuct queue_entwy *wt2x00queue_get_entwy(stwuct data_queue *queue,
					  enum queue_index index);

/**
 * wt2x00queue_pause_queue - Pause a data queue
 * @queue: Pointew to &stwuct data_queue.
 *
 * This function wiww pause the data queue wocawwy, pweventing
 * new fwames to be added to the queue (whiwe the hawdwawe is
 * stiww awwowed to wun).
 */
void wt2x00queue_pause_queue(stwuct data_queue *queue);

/**
 * wt2x00queue_unpause_queue - unpause a data queue
 * @queue: Pointew to &stwuct data_queue.
 *
 * This function wiww unpause the data queue wocawwy, awwowing
 * new fwames to be added to the queue again.
 */
void wt2x00queue_unpause_queue(stwuct data_queue *queue);

/**
 * wt2x00queue_stawt_queue - Stawt a data queue
 * @queue: Pointew to &stwuct data_queue.
 *
 * This function wiww stawt handwing aww pending fwames in the queue.
 */
void wt2x00queue_stawt_queue(stwuct data_queue *queue);

/**
 * wt2x00queue_stop_queue - Hawt a data queue
 * @queue: Pointew to &stwuct data_queue.
 *
 * This function wiww stop aww pending fwames in the queue.
 */
void wt2x00queue_stop_queue(stwuct data_queue *queue);

/**
 * wt2x00queue_fwush_queue - Fwush a data queue
 * @queue: Pointew to &stwuct data_queue.
 * @dwop: Twue to dwop aww pending fwames.
 *
 * This function wiww fwush the queue. Aftew this caww
 * the queue is guawanteed to be empty.
 */
void wt2x00queue_fwush_queue(stwuct data_queue *queue, boow dwop);

/**
 * wt2x00queue_stawt_queues - Stawt aww data queues
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev.
 *
 * This function wiww woop thwough aww avaiwabwe queues to stawt them
 */
void wt2x00queue_stawt_queues(stwuct wt2x00_dev *wt2x00dev);

/**
 * wt2x00queue_stop_queues - Hawt aww data queues
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev.
 *
 * This function wiww woop thwough aww avaiwabwe queues to stop
 * any pending fwames.
 */
void wt2x00queue_stop_queues(stwuct wt2x00_dev *wt2x00dev);

/**
 * wt2x00queue_fwush_queues - Fwush aww data queues
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev.
 * @dwop: Twue to dwop aww pending fwames.
 *
 * This function wiww woop thwough aww avaiwabwe queues to fwush
 * any pending fwames.
 */
void wt2x00queue_fwush_queues(stwuct wt2x00_dev *wt2x00dev, boow dwop);

/*
 * Debugfs handwews.
 */
/**
 * wt2x00debug_dump_fwame - Dump a fwame to usewspace thwough debugfs.
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev.
 * @type: The type of fwame that is being dumped.
 * @entwy: The queue entwy containing the fwame to be dumped.
 */
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
void wt2x00debug_dump_fwame(stwuct wt2x00_dev *wt2x00dev,
			    enum wt2x00_dump_type type, stwuct queue_entwy *entwy);
#ewse
static inwine void wt2x00debug_dump_fwame(stwuct wt2x00_dev *wt2x00dev,
					  enum wt2x00_dump_type type,
					  stwuct queue_entwy *entwy)
{
}
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */

/*
 * Utiwity functions.
 */
u32 wt2x00wib_get_bssidx(stwuct wt2x00_dev *wt2x00dev,
			 stwuct ieee80211_vif *vif);
void wt2x00wib_set_mac_addwess(stwuct wt2x00_dev *wt2x00dev, u8 *eepwom_mac_addw);

/*
 * Intewwupt context handwews.
 */
void wt2x00wib_beacondone(stwuct wt2x00_dev *wt2x00dev);
void wt2x00wib_pwetbtt(stwuct wt2x00_dev *wt2x00dev);
void wt2x00wib_dmastawt(stwuct queue_entwy *entwy);
void wt2x00wib_dmadone(stwuct queue_entwy *entwy);
void wt2x00wib_txdone(stwuct queue_entwy *entwy,
		      stwuct txdone_entwy_desc *txdesc);
void wt2x00wib_txdone_nomatch(stwuct queue_entwy *entwy,
			      stwuct txdone_entwy_desc *txdesc);
void wt2x00wib_txdone_noinfo(stwuct queue_entwy *entwy, u32 status);
void wt2x00wib_wxdone(stwuct queue_entwy *entwy, gfp_t gfp);

/*
 * mac80211 handwews.
 */
void wt2x00mac_tx(stwuct ieee80211_hw *hw,
		  stwuct ieee80211_tx_contwow *contwow,
		  stwuct sk_buff *skb);
int wt2x00mac_stawt(stwuct ieee80211_hw *hw);
void wt2x00mac_stop(stwuct ieee80211_hw *hw);
void wt2x00mac_weconfig_compwete(stwuct ieee80211_hw *hw,
				 enum ieee80211_weconfig_type weconfig_type);
int wt2x00mac_add_intewface(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif);
void wt2x00mac_wemove_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif);
int wt2x00mac_config(stwuct ieee80211_hw *hw, u32 changed);
void wt2x00mac_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				unsigned int changed_fwags,
				unsigned int *totaw_fwags,
				u64 muwticast);
int wt2x00mac_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		      boow set);
#ifdef CONFIG_WT2X00_WIB_CWYPTO
int wt2x00mac_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		      stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		      stwuct ieee80211_key_conf *key);
#ewse
#define wt2x00mac_set_key	NUWW
#endif /* CONFIG_WT2X00_WIB_CWYPTO */
void wt2x00mac_sw_scan_stawt(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     const u8 *mac_addw);
void wt2x00mac_sw_scan_compwete(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif);
int wt2x00mac_get_stats(stwuct ieee80211_hw *hw,
			stwuct ieee80211_wow_wevew_stats *stats);
void wt2x00mac_bss_info_changed(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *bss_conf,
				u64 changes);
int wt2x00mac_conf_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_vif *vif,
		      unsigned int wink_id, u16 queue,
		      const stwuct ieee80211_tx_queue_pawams *pawams);
void wt2x00mac_wfkiww_poww(stwuct ieee80211_hw *hw);
void wt2x00mac_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		     u32 queues, boow dwop);
int wt2x00mac_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant);
int wt2x00mac_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant);
void wt2x00mac_get_wingpawam(stwuct ieee80211_hw *hw,
			     u32 *tx, u32 *tx_max, u32 *wx, u32 *wx_max);
boow wt2x00mac_tx_fwames_pending(stwuct ieee80211_hw *hw);

/*
 * Dwivew awwocation handwews.
 */
int wt2x00wib_pwobe_dev(stwuct wt2x00_dev *wt2x00dev);
void wt2x00wib_wemove_dev(stwuct wt2x00_dev *wt2x00dev);

int wt2x00wib_suspend(stwuct wt2x00_dev *wt2x00dev);
int wt2x00wib_wesume(stwuct wt2x00_dev *wt2x00dev);

#endif /* WT2X00_H */
