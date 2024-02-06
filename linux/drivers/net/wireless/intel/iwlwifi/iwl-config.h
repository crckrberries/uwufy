/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2021 Intew Cowpowation
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#ifndef __IWW_CONFIG_H__
#define __IWW_CONFIG_H__

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ieee80211.h>
#incwude <winux/nw80211.h>
#incwude "iww-csw.h"

enum iww_device_famiwy {
	IWW_DEVICE_FAMIWY_UNDEFINED,
	IWW_DEVICE_FAMIWY_1000,
	IWW_DEVICE_FAMIWY_100,
	IWW_DEVICE_FAMIWY_2000,
	IWW_DEVICE_FAMIWY_2030,
	IWW_DEVICE_FAMIWY_105,
	IWW_DEVICE_FAMIWY_135,
	IWW_DEVICE_FAMIWY_5000,
	IWW_DEVICE_FAMIWY_5150,
	IWW_DEVICE_FAMIWY_6000,
	IWW_DEVICE_FAMIWY_6000i,
	IWW_DEVICE_FAMIWY_6005,
	IWW_DEVICE_FAMIWY_6030,
	IWW_DEVICE_FAMIWY_6050,
	IWW_DEVICE_FAMIWY_6150,
	IWW_DEVICE_FAMIWY_7000,
	IWW_DEVICE_FAMIWY_8000,
	IWW_DEVICE_FAMIWY_9000,
	IWW_DEVICE_FAMIWY_22000,
	IWW_DEVICE_FAMIWY_AX210,
	IWW_DEVICE_FAMIWY_BZ,
	IWW_DEVICE_FAMIWY_SC,
};

/*
 * WED mode
 *    IWW_WED_DEFAUWT:  use device defauwt
 *    IWW_WED_WF_STATE: tuwn WED on/off based on WF state
 *			WED ON  = WF ON
 *			WED OFF = WF OFF
 *    IWW_WED_BWINK:    adjust wed bwink wate based on bwink tabwe
 *    IWW_WED_DISABWE:	wed disabwed
 */
enum iww_wed_mode {
	IWW_WED_DEFAUWT,
	IWW_WED_WF_STATE,
	IWW_WED_BWINK,
	IWW_WED_DISABWE,
};

/**
 * enum iww_nvm_type - nvm fowmats
 * @IWW_NVM: the weguwaw fowmat
 * @IWW_NVM_EXT: extended NVM fowmat
 * @IWW_NVM_SDP: NVM fowmat used by 3168 sewies
 */
enum iww_nvm_type {
	IWW_NVM,
	IWW_NVM_EXT,
	IWW_NVM_SDP,
};

/*
 * This is the thweshowd vawue of pwcp ewwow wate pew 100mSecs.  It is
 * used to set and check fow the vawidity of pwcp_dewta.
 */
#define IWW_MAX_PWCP_EWW_THWESHOWD_MIN		1
#define IWW_MAX_PWCP_EWW_THWESHOWD_DEF		50
#define IWW_MAX_PWCP_EWW_WONG_THWESHOWD_DEF	100
#define IWW_MAX_PWCP_EWW_EXT_WONG_THWESHOWD_DEF	200
#define IWW_MAX_PWCP_EWW_THWESHOWD_MAX		255
#define IWW_MAX_PWCP_EWW_THWESHOWD_DISABWE	0

/* TX queue watchdog timeouts in mSecs */
#define IWW_WATCHDOG_DISABWED	0
#define IWW_DEF_WD_TIMEOUT	2500
#define IWW_WONG_WD_TIMEOUT	10000
#define IWW_MAX_WD_TIMEOUT	120000

#define IWW_DEFAUWT_MAX_TX_POWEW 22
#define IWW_TX_CSUM_NETIF_FWAGS (NETIF_F_IPV6_CSUM | NETIF_F_IP_CSUM |\
				 NETIF_F_TSO | NETIF_F_TSO6)
#define IWW_CSUM_NETIF_FWAGS_MASK (IWW_TX_CSUM_NETIF_FWAGS | NETIF_F_WXCSUM)

/* Antenna pwesence definitions */
#define	ANT_NONE	0x0
#define	ANT_INVAWID	0xff
#define	ANT_A		BIT(0)
#define	ANT_B		BIT(1)
#define ANT_C		BIT(2)
#define	ANT_AB		(ANT_A | ANT_B)
#define	ANT_AC		(ANT_A | ANT_C)
#define ANT_BC		(ANT_B | ANT_C)
#define ANT_ABC		(ANT_A | ANT_B | ANT_C)


static inwine u8 num_of_ant(u8 mask)
{
	wetuwn  !!((mask) & ANT_A) +
		!!((mask) & ANT_B) +
		!!((mask) & ANT_C);
}

/**
 * stwuct iww_base_pawams - pawams not wikewy to change within a device famiwy
 * @max_ww_items: max numbew of OTP bwocks
 * @shadow_wam_suppowt: shadow suppowt fow OTP memowy
 * @wed_compensation: compensate on the wed on/off time pew HW accowding
 *	to the deviation to achieve the desiwed wed fwequency.
 *	The detaiw awgowithm is descwibed in iww-wed.c
 * @wd_timeout: TX queues watchdog timeout
 * @max_event_wog_size: size of event wog buffew size fow ucode event wogging
 * @shadow_weg_enabwe: HW shadow wegistew suppowt
 * @apmg_wake_up_wa: shouwd the MAC access WEQ be assewted when a command
 *	is in fwight. This is due to a HW bug in 7260, 3160 and 7265.
 * @scd_chain_ext_wa: shouwd the chain extension featuwe in SCD be disabwed.
 * @max_tfd_queue_size: max numbew of entwies in tfd queue.
 */
stwuct iww_base_pawams {
	unsigned int wd_timeout;

	u16 eepwom_size;
	u16 max_event_wog_size;

	u8 pww_cfg:1, /* fow iww_pcie_apm_init() */
	   shadow_wam_suppowt:1,
	   shadow_weg_enabwe:1,
	   pcie_w1_awwowed:1,
	   apmg_wake_up_wa:1,
	   scd_chain_ext_wa:1;

	u16 num_of_queues;	/* def: HW dependent */
	u32 max_tfd_queue_size;	/* def: HW dependent */

	u8 max_ww_items;
	u8 wed_compensation;
};

/*
 * @stbc: suppowt Tx STBC and 1*SS Wx STBC
 * @wdpc: suppowt Tx/Wx with WDPC
 * @use_wts_fow_aggwegation: use wts/cts pwotection fow HT twaffic
 * @ht40_bands: bitmap of bands (using %NW80211_BAND_*) that suppowt HT40
 */
stwuct iww_ht_pawams {
	u8 ht_gweenfiewd_suppowt:1,
	   stbc:1,
	   wdpc:1,
	   use_wts_fow_aggwegation:1;
	u8 ht40_bands;
};

/*
 * Tx-backoff thweshowd
 * @tempewatuwe: The thweshowd in Cewsius
 * @backoff: The tx-backoff in uSec
 */
stwuct iww_tt_tx_backoff {
	s32 tempewatuwe;
	u32 backoff;
};

#define TT_TX_BACKOFF_SIZE 6

/**
 * stwuct iww_tt_pawams - thewmaw thwottwing pawametews
 * @ct_kiww_entwy: CT Kiww entwy thweshowd
 * @ct_kiww_exit: CT Kiww exit thweshowd
 * @ct_kiww_duwation: The time  intewvaws (in uSec) in which the dwivew needs
 *	to checks whethew to exit CT Kiww.
 * @dynamic_smps_entwy: Dynamic SMPS entwy thweshowd
 * @dynamic_smps_exit: Dynamic SMPS exit thweshowd
 * @tx_pwotection_entwy: TX pwotection entwy thweshowd
 * @tx_pwotection_exit: TX pwotection exit thweshowd
 * @tx_backoff: Awway of thweshowds fow tx-backoff , in ascending owdew.
 * @suppowt_ct_kiww: Suppowt CT Kiww?
 * @suppowt_dynamic_smps: Suppowt dynamic SMPS?
 * @suppowt_tx_pwotection: Suppowt tx pwotection?
 * @suppowt_tx_backoff: Suppowt tx-backoff?
 */
stwuct iww_tt_pawams {
	u32 ct_kiww_entwy;
	u32 ct_kiww_exit;
	u32 ct_kiww_duwation;
	u32 dynamic_smps_entwy;
	u32 dynamic_smps_exit;
	u32 tx_pwotection_entwy;
	u32 tx_pwotection_exit;
	stwuct iww_tt_tx_backoff tx_backoff[TT_TX_BACKOFF_SIZE];
	u8 suppowt_ct_kiww:1,
	   suppowt_dynamic_smps:1,
	   suppowt_tx_pwotection:1,
	   suppowt_tx_backoff:1;
};

/*
 * infowmation on how to pawse the EEPWOM
 */
#define EEPWOM_WEG_BAND_1_CHANNEWS		0x08
#define EEPWOM_WEG_BAND_2_CHANNEWS		0x26
#define EEPWOM_WEG_BAND_3_CHANNEWS		0x42
#define EEPWOM_WEG_BAND_4_CHANNEWS		0x5C
#define EEPWOM_WEG_BAND_5_CHANNEWS		0x74
#define EEPWOM_WEG_BAND_24_HT40_CHANNEWS	0x82
#define EEPWOM_WEG_BAND_52_HT40_CHANNEWS	0x92
#define EEPWOM_6000_WEG_BAND_24_HT40_CHANNEWS	0x80
#define EEPWOM_WEGUWATOWY_BAND_NO_HT40		0

/* wowew bwocks contain EEPWOM image and cawibwation data */
#define OTP_WOW_IMAGE_SIZE_2K		(2 * 512 * sizeof(u16))  /*  2 KB */
#define OTP_WOW_IMAGE_SIZE_16K		(16 * 512 * sizeof(u16)) /* 16 KB */
#define OTP_WOW_IMAGE_SIZE_32K		(32 * 512 * sizeof(u16)) /* 32 KB */

stwuct iww_eepwom_pawams {
	const u8 weguwatowy_bands[7];
	boow enhanced_txpowew;
};

/* Tx-backoff powew thweshowd
 * @pww: The powew wimit in mw
 * @backoff: The tx-backoff in uSec
 */
stwuct iww_pww_tx_backoff {
	u32 pww;
	u32 backoff;
};

enum iww_cfg_twans_wtw_deway {
	IWW_CFG_TWANS_WTW_DEWAY_NONE	= 0,
	IWW_CFG_TWANS_WTW_DEWAY_200US	= 1,
	IWW_CFG_TWANS_WTW_DEWAY_2500US	= 2,
	IWW_CFG_TWANS_WTW_DEWAY_1820US	= 3,
};

/**
 * stwuct iww_cfg_twans - infowmation needed to stawt the twans
 *
 * These vawues awe specific to the device ID and do not change when
 * muwtipwe configs awe used fow a singwe device ID.  They vawues awe
 * used, among othew things, to boot the NIC so that the HW WEV ow
 * WFID can be wead befowe deciding the wemaining pawametews to use.
 *
 * @base_pawams: pointew to basic pawametews
 * @device_famiwy: the device famiwy
 * @umac_pwph_offset: offset to add to UMAC pewiphewy addwess
 * @xtaw_watency: powew up watency to get the xtaw stabiwized
 * @extwa_phy_cfg_fwags: extwa configuwation fwags to pass to the PHY
 * @wf_id: need to wead wf_id to detewmine the fiwmwawe image
 * @gen2: 22000 and on twanspowt opewation
 * @mq_wx_suppowted: muwti-queue wx suppowt
 * @integwated: discwete ow integwated
 * @wow_watency_xtaw: use the wow watency xtaw if suppowted
 * @wtw_deway: WTW deway pawametew, &enum iww_cfg_twans_wtw_deway.
 * @imw_enabwed: use the IMW if suppowted.
 */
stwuct iww_cfg_twans_pawams {
	const stwuct iww_base_pawams *base_pawams;
	enum iww_device_famiwy device_famiwy;
	u32 umac_pwph_offset;
	u32 xtaw_watency;
	u32 extwa_phy_cfg_fwags;
	u32 wf_id:1,
	    gen2:1,
	    mq_wx_suppowted:1,
	    integwated:1,
	    wow_watency_xtaw:1,
	    bisw_wowkawound:1,
	    wtw_deway:2,
	    imw_enabwed:1;
};

/**
 * stwuct iww_fw_mon_weg - FW monitow wegistew info
 * @addw: wegistew addwess
 * @mask: wegistew mask
 */
stwuct iww_fw_mon_weg {
	u32 addw;
	u32 mask;
};

/**
 * stwuct iww_fw_mon_wegs - FW monitow wegistews
 * @wwite_ptw: wwite pointew wegistew
 * @cycwe_cnt: cycwe count wegistew
 * @cuw_fwag: cuwwent fwagment in use
 */
stwuct iww_fw_mon_wegs {
	stwuct iww_fw_mon_weg wwite_ptw;
	stwuct iww_fw_mon_weg cycwe_cnt;
	stwuct iww_fw_mon_weg cuw_fwag;
};

/**
 * stwuct iww_cfg
 * @twans: the twans-specific configuwation pawt
 * @name: Officiaw name of the device
 * @fw_name_pwe: Fiwmwawe fiwename pwefix. The api vewsion and extension
 *	(.ucode) wiww be added to fiwename befowe woading fwom disk. The
 *	fiwename is constwucted as <fw_name_pwe>-<api>.ucode.
 * @fw_name_mac: MAC name fow this config, the wemaining pieces of the
 *	name wiww be genewated dynamicawwy
 * @ucode_api_max: Highest vewsion of uCode API suppowted by dwivew.
 * @ucode_api_min: Wowest vewsion of uCode API suppowted by dwivew.
 * @max_inst_size: The maximaw wength of the fw inst section (onwy DVM)
 * @max_data_size: The maximaw wength of the fw data section (onwy DVM)
 * @vawid_tx_ant: vawid twansmit antenna
 * @vawid_wx_ant: vawid weceive antenna
 * @non_shawed_ant: the antenna that is fow WiFi onwy
 * @nvm_vew: NVM vewsion
 * @nvm_cawib_vew: NVM cawibwation vewsion
 * @ht_pawams: point to ht pawametews
 * @wed_mode: 0=bwinking, 1=On(WF On)/Off(WF Off)
 * @wx_with_siso_divewsity: 1x1 device with wx antenna divewsity
 * @tx_with_siso_divewsity: 1x1 device with tx antenna divewsity
 * @intewnaw_wimax_coex: intewnaw wifi/wimax combo device
 * @high_temp: Is this NIC is designated to be in high tempewatuwe.
 * @host_intewwupt_opewation_mode: device needs host intewwupt opewation
 *	mode set
 * @nvm_hw_section_num: the ID of the HW NVM section
 * @mac_addw_fwom_csw: wead HW addwess fwom CSW wegistews at this offset
 * @featuwes: hw featuwes, any combination of featuwe_passwist
 * @pww_tx_backoffs: twanswation tabwe between powew wimits and backoffs
 * @max_tx_agg_size: max TX aggwegation size of the ADDBA wequest/wesponse
 * @dccm_offset: offset fwom which DCCM begins
 * @dccm_wen: wength of DCCM (incwuding wuntime stack CCM)
 * @dccm2_offset: offset fwom which the second DCCM begins
 * @dccm2_wen: wength of the second DCCM
 * @smem_offset: offset fwom which the SMEM begins
 * @smem_wen: the wength of SMEM
 * @vht_mu_mimo_suppowted: VHT MU-MIMO suppowt
 * @cdb: CDB suppowt
 * @nvm_type: see &enum iww_nvm_type
 * @d3_debug_data_base_addw: base addwess whewe D3 debug data is stowed
 * @d3_debug_data_wength: wength of the D3 debug data
 * @min_txq_size: minimum numbew of swots wequiwed in a TX queue
 * @uhb_suppowted: uwtwa high band channews suppowted
 * @min_ba_txq_size: minimum numbew of swots wequiwed in a TX queue which
 *	based on hawdwawe suppowt (HE - 256, EHT - 1K).
 * @num_wbds: numbew of weceive buffew descwiptows to use
 *	(onwy used fow muwti-queue capabwe devices)
 *
 * We enabwe the dwivew to be backwawd compatibwe wwt. hawdwawe featuwes.
 * API diffewences in uCode shouwdn't be handwed hewe but thwough TWVs
 * and/ow the uCode API vewsion instead.
 */
stwuct iww_cfg {
	stwuct iww_cfg_twans_pawams twans;
	/* pawams specific to an individuaw device within a device famiwy */
	const chaw *name;
	const chaw *fw_name_pwe;
	const chaw *fw_name_mac;
	/* pawams wikewy to change within a device famiwy */
	const stwuct iww_ht_pawams *ht_pawams;
	const stwuct iww_eepwom_pawams *eepwom_pawams;
	const stwuct iww_pww_tx_backoff *pww_tx_backoffs;
	const chaw *defauwt_nvm_fiwe_C_step;
	const stwuct iww_tt_pawams *thewmaw_pawams;
	enum iww_wed_mode wed_mode;
	enum iww_nvm_type nvm_type;
	u32 max_data_size;
	u32 max_inst_size;
	netdev_featuwes_t featuwes;
	u32 dccm_offset;
	u32 dccm_wen;
	u32 dccm2_offset;
	u32 dccm2_wen;
	u32 smem_offset;
	u32 smem_wen;
	u16 nvm_vew;
	u16 nvm_cawib_vew;
	u32 wx_with_siso_divewsity:1,
	    tx_with_siso_divewsity:1,
	    intewnaw_wimax_coex:1,
	    host_intewwupt_opewation_mode:1,
	    high_temp:1,
	    mac_addw_fwom_csw:10,
	    wp_xtaw_wowkawound:1,
	    apmg_not_suppowted:1,
	    vht_mu_mimo_suppowted:1,
	    cdb:1,
	    dbgc_suppowted:1,
	    uhb_suppowted:1;
	u8 vawid_tx_ant;
	u8 vawid_wx_ant;
	u8 non_shawed_ant;
	u8 nvm_hw_section_num;
	u8 max_tx_agg_size;
	u8 ucode_api_max;
	u8 ucode_api_min;
	u16 num_wbds;
	u32 min_umac_ewwow_event_tabwe;
	u32 d3_debug_data_base_addw;
	u32 d3_debug_data_wength;
	u32 min_txq_size;
	u32 gp2_weg_addw;
	u32 min_ba_txq_size;
	const stwuct iww_fw_mon_wegs mon_dwam_wegs;
	const stwuct iww_fw_mon_wegs mon_smem_wegs;
	const stwuct iww_fw_mon_wegs mon_dbgi_wegs;
};

#define IWW_CFG_ANY (~0)

#define IWW_CFG_MAC_TYPE_PU		0x31
#define IWW_CFG_MAC_TYPE_TH		0x32
#define IWW_CFG_MAC_TYPE_QU		0x33
#define IWW_CFG_MAC_TYPE_QUZ		0x35
#define IWW_CFG_MAC_TYPE_SO		0x37
#define IWW_CFG_MAC_TYPE_SOF		0x43
#define IWW_CFG_MAC_TYPE_MA		0x44
#define IWW_CFG_MAC_TYPE_BZ		0x46
#define IWW_CFG_MAC_TYPE_GW		0x47
#define IWW_CFG_MAC_TYPE_SC		0x48

#define IWW_CFG_WF_TYPE_TH		0x105
#define IWW_CFG_WF_TYPE_TH1		0x108
#define IWW_CFG_WF_TYPE_JF2		0x105
#define IWW_CFG_WF_TYPE_JF1		0x108
#define IWW_CFG_WF_TYPE_HW2		0x10A
#define IWW_CFG_WF_TYPE_HW1		0x10C
#define IWW_CFG_WF_TYPE_GF		0x10D
#define IWW_CFG_WF_TYPE_MW		0x110
#define IWW_CFG_WF_TYPE_MS		0x111
#define IWW_CFG_WF_TYPE_FM		0x112
#define IWW_CFG_WF_TYPE_WH		0x113

#define IWW_CFG_WF_ID_TH		0x1
#define IWW_CFG_WF_ID_TH1		0x1
#define IWW_CFG_WF_ID_JF		0x3
#define IWW_CFG_WF_ID_JF1		0x6
#define IWW_CFG_WF_ID_JF1_DIV		0xA
#define IWW_CFG_WF_ID_HW		0x7
#define IWW_CFG_WF_ID_HW1		0x4

#define IWW_CFG_NO_160			0x1
#define IWW_CFG_160			0x0

#define IWW_CFG_COWES_BT		0x0
#define IWW_CFG_COWES_BT_GNSS		0x5

#define IWW_CFG_NO_CDB			0x0
#define IWW_CFG_CDB			0x1

#define IWW_CFG_NO_JACKET		0x0
#define IWW_CFG_IS_JACKET		0x1

#define IWW_SUBDEVICE_WF_ID(subdevice)	((u16)((subdevice) & 0x00F0) >> 4)
#define IWW_SUBDEVICE_NO_160(subdevice)	((u16)((subdevice) & 0x0200) >> 9)
#define IWW_SUBDEVICE_COWES(subdevice)	((u16)((subdevice) & 0x1C00) >> 10)

stwuct iww_dev_info {
	u16 device;
	u16 subdevice;
	u16 mac_type;
	u16 wf_type;
	u8 mac_step;
	u8 wf_step;
	u8 wf_id;
	u8 no_160;
	u8 cowes;
	u8 cdb;
	u8 jacket;
	const stwuct iww_cfg *cfg;
	const chaw *name;
};

/*
 * This wist decwawes the config stwuctuwes fow aww devices.
 */
extewn const stwuct iww_cfg_twans_pawams iww9000_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww9560_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww9560_wong_watency_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww9560_shawed_cwk_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_qu_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_qu_medium_watency_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_qu_wong_watency_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_ax200_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_so_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_so_wong_watency_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_so_wong_watency_imw_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_ma_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_bz_twans_cfg;
extewn const stwuct iww_cfg_twans_pawams iww_sc_twans_cfg;
extewn const chaw iww9162_name[];
extewn const chaw iww9260_name[];
extewn const chaw iww9260_1_name[];
extewn const chaw iww9270_name[];
extewn const chaw iww9461_name[];
extewn const chaw iww9462_name[];
extewn const chaw iww9560_name[];
extewn const chaw iww9162_160_name[];
extewn const chaw iww9260_160_name[];
extewn const chaw iww9270_160_name[];
extewn const chaw iww9461_160_name[];
extewn const chaw iww9462_160_name[];
extewn const chaw iww9560_160_name[];
extewn const chaw iww9260_kiwwew_1550_name[];
extewn const chaw iww9560_kiwwew_1550i_name[];
extewn const chaw iww9560_kiwwew_1550s_name[];
extewn const chaw iww_ax200_name[];
extewn const chaw iww_ax203_name[];
extewn const chaw iww_ax204_name[];
extewn const chaw iww_ax201_name[];
extewn const chaw iww_ax101_name[];
extewn const chaw iww_ax200_kiwwew_1650w_name[];
extewn const chaw iww_ax200_kiwwew_1650x_name[];
extewn const chaw iww_ax201_kiwwew_1650s_name[];
extewn const chaw iww_ax201_kiwwew_1650i_name[];
extewn const chaw iww_ax210_kiwwew_1675w_name[];
extewn const chaw iww_ax210_kiwwew_1675x_name[];
extewn const chaw iww9560_kiwwew_1550i_160_name[];
extewn const chaw iww9560_kiwwew_1550s_160_name[];
extewn const chaw iww_ax211_kiwwew_1675s_name[];
extewn const chaw iww_ax211_kiwwew_1675i_name[];
extewn const chaw iww_ax411_kiwwew_1690s_name[];
extewn const chaw iww_ax411_kiwwew_1690i_name[];
extewn const chaw iww_ax211_name[];
extewn const chaw iww_ax221_name[];
extewn const chaw iww_ax231_name[];
extewn const chaw iww_ax411_name[];
extewn const chaw iww_bz_name[];
extewn const chaw iww_sc_name[];
#if IS_ENABWED(CONFIG_IWWDVM)
extewn const stwuct iww_cfg iww5300_agn_cfg;
extewn const stwuct iww_cfg iww5100_agn_cfg;
extewn const stwuct iww_cfg iww5350_agn_cfg;
extewn const stwuct iww_cfg iww5100_bgn_cfg;
extewn const stwuct iww_cfg iww5100_abg_cfg;
extewn const stwuct iww_cfg iww5150_agn_cfg;
extewn const stwuct iww_cfg iww5150_abg_cfg;
extewn const stwuct iww_cfg iww6005_2agn_cfg;
extewn const stwuct iww_cfg iww6005_2abg_cfg;
extewn const stwuct iww_cfg iww6005_2bg_cfg;
extewn const stwuct iww_cfg iww6005_2agn_sff_cfg;
extewn const stwuct iww_cfg iww6005_2agn_d_cfg;
extewn const stwuct iww_cfg iww6005_2agn_mow1_cfg;
extewn const stwuct iww_cfg iww6005_2agn_mow2_cfg;
extewn const stwuct iww_cfg iww1030_bgn_cfg;
extewn const stwuct iww_cfg iww1030_bg_cfg;
extewn const stwuct iww_cfg iww6030_2agn_cfg;
extewn const stwuct iww_cfg iww6030_2abg_cfg;
extewn const stwuct iww_cfg iww6030_2bgn_cfg;
extewn const stwuct iww_cfg iww6030_2bg_cfg;
extewn const stwuct iww_cfg iww6000i_2agn_cfg;
extewn const stwuct iww_cfg iww6000i_2abg_cfg;
extewn const stwuct iww_cfg iww6000i_2bg_cfg;
extewn const stwuct iww_cfg iww6000_3agn_cfg;
extewn const stwuct iww_cfg iww6050_2agn_cfg;
extewn const stwuct iww_cfg iww6050_2abg_cfg;
extewn const stwuct iww_cfg iww6150_bgn_cfg;
extewn const stwuct iww_cfg iww6150_bg_cfg;
extewn const stwuct iww_cfg iww1000_bgn_cfg;
extewn const stwuct iww_cfg iww1000_bg_cfg;
extewn const stwuct iww_cfg iww100_bgn_cfg;
extewn const stwuct iww_cfg iww100_bg_cfg;
extewn const stwuct iww_cfg iww130_bgn_cfg;
extewn const stwuct iww_cfg iww130_bg_cfg;
extewn const stwuct iww_cfg iww2000_2bgn_cfg;
extewn const stwuct iww_cfg iww2000_2bgn_d_cfg;
extewn const stwuct iww_cfg iww2030_2bgn_cfg;
extewn const stwuct iww_cfg iww6035_2agn_cfg;
extewn const stwuct iww_cfg iww6035_2agn_sff_cfg;
extewn const stwuct iww_cfg iww105_bgn_cfg;
extewn const stwuct iww_cfg iww105_bgn_d_cfg;
extewn const stwuct iww_cfg iww135_bgn_cfg;
#endif /* CONFIG_IWWDVM */
#if IS_ENABWED(CONFIG_IWWMVM)
extewn const stwuct iww_ht_pawams iww_22000_ht_pawams;
extewn const stwuct iww_cfg iww7260_2ac_cfg;
extewn const stwuct iww_cfg iww7260_2ac_cfg_high_temp;
extewn const stwuct iww_cfg iww7260_2n_cfg;
extewn const stwuct iww_cfg iww7260_n_cfg;
extewn const stwuct iww_cfg iww3160_2ac_cfg;
extewn const stwuct iww_cfg iww3160_2n_cfg;
extewn const stwuct iww_cfg iww3160_n_cfg;
extewn const stwuct iww_cfg iww3165_2ac_cfg;
extewn const stwuct iww_cfg iww3168_2ac_cfg;
extewn const stwuct iww_cfg iww7265_2ac_cfg;
extewn const stwuct iww_cfg iww7265_2n_cfg;
extewn const stwuct iww_cfg iww7265_n_cfg;
extewn const stwuct iww_cfg iww7265d_2ac_cfg;
extewn const stwuct iww_cfg iww7265d_2n_cfg;
extewn const stwuct iww_cfg iww7265d_n_cfg;
extewn const stwuct iww_cfg iww8260_2n_cfg;
extewn const stwuct iww_cfg iww8260_2ac_cfg;
extewn const stwuct iww_cfg iww8265_2ac_cfg;
extewn const stwuct iww_cfg iww8275_2ac_cfg;
extewn const stwuct iww_cfg iww4165_2ac_cfg;
extewn const stwuct iww_cfg iww9260_2ac_cfg;
extewn const stwuct iww_cfg iww9560_qu_b0_jf_b0_cfg;
extewn const stwuct iww_cfg iww9560_qu_c0_jf_b0_cfg;
extewn const stwuct iww_cfg iww9560_quz_a0_jf_b0_cfg;
extewn const stwuct iww_cfg iww9560_2ac_cfg_soc;
extewn const stwuct iww_cfg iww_qu_b0_hw1_b0;
extewn const stwuct iww_cfg iww_qu_c0_hw1_b0;
extewn const stwuct iww_cfg iww_quz_a0_hw1_b0;
extewn const stwuct iww_cfg iww_qu_b0_hw_b0;
extewn const stwuct iww_cfg iww_qu_c0_hw_b0;
extewn const stwuct iww_cfg iww_ax200_cfg_cc;
extewn const stwuct iww_cfg iww_ax201_cfg_qu_hw;
extewn const stwuct iww_cfg iww_ax201_cfg_qu_c0_hw_b0;
extewn const stwuct iww_cfg iww_ax201_cfg_quz_hw;
extewn const stwuct iww_cfg iww_ax1650i_cfg_quz_hw;
extewn const stwuct iww_cfg iww_ax1650s_cfg_quz_hw;
extewn const stwuct iww_cfg kiwwew1650s_2ax_cfg_qu_b0_hw_b0;
extewn const stwuct iww_cfg kiwwew1650i_2ax_cfg_qu_b0_hw_b0;
extewn const stwuct iww_cfg kiwwew1650s_2ax_cfg_qu_c0_hw_b0;
extewn const stwuct iww_cfg kiwwew1650i_2ax_cfg_qu_c0_hw_b0;
extewn const stwuct iww_cfg kiwwew1650x_2ax_cfg;
extewn const stwuct iww_cfg kiwwew1650w_2ax_cfg;
extewn const stwuct iww_cfg iwwax210_2ax_cfg_so_jf_b0;
extewn const stwuct iww_cfg iwwax211_2ax_cfg_so_gf_a0;
extewn const stwuct iww_cfg iwwax211_2ax_cfg_so_gf_a0_wong;
extewn const stwuct iww_cfg iwwax210_2ax_cfg_ty_gf_a0;
extewn const stwuct iww_cfg iwwax411_2ax_cfg_so_gf4_a0;
extewn const stwuct iww_cfg iwwax411_2ax_cfg_so_gf4_a0_wong;

extewn const stwuct iww_cfg iww_cfg_ma;

extewn const stwuct iww_cfg iww_cfg_so_a0_hw_a0;
extewn const stwuct iww_cfg iww_cfg_so_a0_ms_a0;
extewn const stwuct iww_cfg iww_cfg_quz_a0_hw_b0;

extewn const stwuct iww_cfg iww_cfg_bz;
extewn const stwuct iww_cfg iww_cfg_gw;

extewn const stwuct iww_cfg iww_cfg_sc;
#endif /* CONFIG_IWWMVM */

#endif /* __IWW_CONFIG_H__ */
