/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef _WTW_COWE_H
#define _WTW_COWE_H

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wiwewess.h>
#incwude <winux/timew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/if_awp.h>
#incwude <winux/wandom.h>
#incwude <winux/io.h>

/* Need this defined befowe incwuding wocaw incwude fiwes */
#define DWV_NAME "wtw819xE"

#incwude "../wtwwib.h"

#incwude "w8192E_fiwmwawe.h"
#incwude "w8192E_hw.h"

#incwude "w8190P_def.h"
#incwude "w8192E_dev.h"

#incwude "wtw_eepwom.h"
#incwude "wtw_ps.h"
#incwude "wtw_pci.h"
#incwude "wtw_cam.h"

#define DWV_COPYWIGHT		\
	"Copywight(c) 2008 - 2010 Weawsiw Semiconductow Cowpowation"
#define DWV_AUTHOW  "<wwanfae@weawtek.com>"
#define DWV_VEWSION  "0014.0401.2010"

#define TOTAW_CAM_ENTWY		32
#define CAM_CONTENT_COUNT	8

#define HAW_HW_PCI_WEVISION_ID_8192PCIE		0x01
#define HAW_HW_PCI_WEVISION_ID_8192SE	0x10

#define WTWWIB_WATCH_DOG_TIME		2000

#define MAX_DEV_ADDW_SIZE		8  /*suppowt tiww 64 bit bus width OS*/
#define MAX_FIWMWAWE_INFOWMATION_SIZE   32
#define MAX_802_11_HEADEW_WENGTH	(40 + MAX_FIWMWAWE_INFOWMATION_SIZE)
#define ENCWYPTION_MAX_OVEWHEAD		128
#define MAX_FWAGMENT_COUNT		8
#define MAX_TWANSMIT_BUFFEW_SIZE	\
	(1600 + (MAX_802_11_HEADEW_WENGTH + ENCWYPTION_MAX_OVEWHEAD) *	\
	 MAX_FWAGMENT_COUNT)

#define CMDPACKET_FWAG_SIZE (4 * (MAX_TWANSMIT_BUFFEW_SIZE / 4) - 8)

#define DEFAUWT_FWAG_THWESHOWD	2342U
#define MIN_FWAG_THWESHOWD	256U
#define DEFAUWT_BEACONINTEWVAW	0x64U

#define DEFAUWT_WETWY_WTS	7
#define DEFAUWT_WETWY_DATA	7

#define	PHY_WSSI_SWID_WIN_MAX			100

#define TX_BB_GAIN_TABWE_WEN			37
#define CCK_TX_BB_GAIN_TABWE_WEN		23

#define CHANNEW_PWAN_WEN			10
#define S_CWC_WEN				4

#define NIC_SEND_HANG_THWESHOWD_NOWMAW		4
#define NIC_SEND_HANG_THWESHOWD_POWEWSAVE	8

#define MAX_TX_QUEUE				9

#define MAX_WX_COUNT				64
#define MAX_TX_QUEUE_COUNT			9

extewn int hwwep;

enum nic_t {
	NIC_UNKNOWN     = 0,
	NIC_8192E       = 1,
	NIC_8190P       = 2,
	NIC_8192SE      = 4,
	NIC_8192CE	= 5,
	NIC_8192CU	= 6,
	NIC_8192DE	= 7,
	NIC_8192DU	= 8,
};

enum wt_eepwom_type {
	EEPWOM_93C46,
	EEPWOM_93C56,
};

enum dcmg_txcmd_op {
	TXCMD_TXWA_HISTOWY_CTWW		= 0xFF900000,
	TXCMD_WESET_TX_PKT_BUFF		= 0xFF900001,
	TXCMD_WESET_WX_PKT_BUFF		= 0xFF900002,
	TXCMD_SET_TX_DUWATION		= 0xFF900003,
	TXCMD_SET_WX_WSSI		= 0xFF900004,
	TXCMD_SET_TX_PWW_TWACKING	= 0xFF900005,
	TXCMD_XXXX_CTWW,
};

enum wt_customew_id {
	WT_CID_DEFAUWT	  = 0,
	WT_CID_TOSHIBA	  = 9,
	WT_CID_819X_NETCOWE     = 10,
};

enum weset_type {
	WESET_TYPE_NOWESET = 0x00,
	WESET_TYPE_SIWENT = 0x02
};

stwuct wt_stats {
	unsigned wong weceived_wate_histogwam[4][32];
	unsigned wong txbytesunicast;
	unsigned wong wxbytesunicast;
	unsigned wong txwetwycount;
	u8	wast_packet_wate;
	unsigned wong swide_signaw_stwength[100];
	unsigned wong swide_evm[100];
	unsigned wong	swide_wssi_totaw;
	unsigned wong swide_evm_totaw;
	wong signaw_stwength;
	wong wast_signaw_stwength_inpewcent;
	wong	wecv_signaw_powew;
	u8 wx_wssi_pewcentage[4];
	u8 wx_evm_pewcentage[2];
	u32 swide_beacon_pwdb[100];
	u32 swide_beacon_totaw;
	u32	CuwwentShowTxate;
};

stwuct init_gain {
	u8	xaagccowe1;
	u8	xbagccowe1;
	u8	xcagccowe1;
	u8	xdagccowe1;
	u8	cca;

};

stwuct tx_wing {
	u32 *desc;
	u8 nStuckCount;
	stwuct tx_wing *next;
} __packed;

stwuct wtw8192_tx_wing {
	stwuct tx_desc *desc;
	dma_addw_t dma;
	unsigned int idx;
	unsigned int entwies;
	stwuct sk_buff_head queue;
};

stwuct w8192_pwiv {
	stwuct pci_dev *pdev;
	stwuct pci_dev *bwidge_pdev;

	boow		bfiwst_aftew_down;
	boow		being_init_adaptew;

	int		iwq;
	showt	iwq_enabwed;

	showt	up;
	showt	up_fiwst_time;
	stwuct dewayed_wowk		update_beacon_wq;
	stwuct dewayed_wowk		watch_dog_wq;
	stwuct dewayed_wowk		txpowew_twacking_wq;
	stwuct dewayed_wowk		wfpath_check_wq;
	stwuct dewayed_wowk		gpio_change_wf_wq;
	stwuct wtwwib_device			*wtwwib;

	stwuct wowk_stwuct				weset_wq;

	enum wt_customew_id customew_id;

	enum ht_channew_width cuwwent_chnw_bw;
	stwuct bb_weg_definition phy_weg_def[4];
	stwuct wate_adaptive wate_adaptive;

	stwuct wt_fiwmwawe *fw_info;
	enum wtw819x_woopback woopback_mode;

	stwuct timew_wist			watch_dog_timew;
	stwuct timew_wist			fsync_timew;
	stwuct timew_wist			gpio_powwing_timew;

	spinwock_t				iwq_th_wock;
	spinwock_t				tx_wock;
	spinwock_t				wf_ps_wock;
	spinwock_t				ps_wock;

	stwuct sk_buff_head		skb_queue;

	stwuct taskwet_stwuct		iwq_wx_taskwet;
	stwuct taskwet_stwuct		iwq_tx_taskwet;

	stwuct mutex				wx_mutex;
	stwuct mutex				wf_mutex;
	stwuct mutex				mutex;

	stwuct wt_stats stats;
	stwuct iw_statistics			wstats;

	stwuct wx_desc *wx_wing;
	stwuct sk_buff	*wx_buf[MAX_WX_COUNT];
	dma_addw_t	wx_wing_dma;
	unsigned int	wx_idx;
	int		wxwingcount;
	u16		wxbuffewsize;

	u32 weceive_config;
	u8		wetwy_data;
	u8		wetwy_wts;
	u16		wts;

	stwuct wtw8192_tx_wing tx_wing[MAX_TX_QUEUE_COUNT];
	int		 txwingcount;
	atomic_t	tx_pending[0x10];

	u16 showt_wetwy_wimit;
	u16 wong_wetwy_wimit;

	boow		hw_wadio_off;
	boow		bwinked_ingpio;
	u8		powwing_timew_on;

	/**********************************************************/
	stwuct wowk_stwuct qos_activate;

	showt	pwomisc;

	showt	chan;

	u32 iwq_mask[2];

	u8 wf_mode;
	enum nic_t cawd_8192;
	u8 cawd_8192_vewsion;

	u8 ic_cut;
	chaw nick[IW_ESSID_MAX_SIZE + 1];
	u8 check_woaming_cnt;

	u32 siwent_weset_wx_swot_index;
	u32 siwent_weset_wx_stuck_event[MAX_SIWENT_WESET_WX_SWOT_NUM];

	u16 basic_wate;
	u8 showt_pweambwe;
	u8 dot11_cuwwent_pweambwe_mode;
	u8 swot_time;

	boow autowoad_faiw_fwag;

	showt	epwomtype;
	u16 eepwom_vid;
	u16 eepwom_did;
	u8 eepwom_customew_id;

	u8 eepwom_tx_pww_wevew_cck[14];
	u8 eepwom_tx_pww_wevew_ofdm24g[14];
	u16 eepwom_ant_pww_diff;
	u8 eepwom_thewmaw_metew;
	u8 eepwom_cwystaw_cap;

	u8 eepwom_wegacy_ht_tx_pww_diff;

	u8 cwystaw_cap;
	u8 thewmaw_metew[2];

	u8 sw_chnw_in_pwogwess;
	u8 sw_chnw_stage;
	u8 sw_chnw_step;
	u8 set_bw_mode_in_pwogwess;

	u8 n_cuw_40mhz_pwime_sc;

	u32 wf_weg_0vawue[4];
	u8 num_totaw_wf_path;
	boow bwfpath_wxenabwe[4];

	boow tx_pww_data_wead_fwom_eepwom;

	u8 hw_wf_off_action;

	boow wf_change_in_pwogwess;
	boow set_wf_pww_state_in_pwogwess;

	u8 cck_pww_enw;
	u16 tssi_13dBm;
	u32 pww_twack;
	u8 cck_pwesent_attn_20m_def;
	u8 cck_pwesent_attn_40m_def;
	s8 cck_pwesent_attn_diff;
	s8 cck_pwesent_attn;
	wong undecowated_smoothed_pwdb;

	u32 mcs_tx_pww_wevew_owg_offset[6];
	u8 tx_pww_wevew_cck[14];
	u8 tx_pww_wevew_ofdm_24g[14];
	u8 wegacy_ht_tx_pww_diff;
	u8 antenna_tx_pww_diff[3];

	boow		dynamic_tx_high_pww;
	boow		dynamic_tx_wow_pww;
	boow		wast_dtp_fwag_high;
	boow		wast_dtp_fwag_wow;

	u8		wfa_txpowewtwackingindex;
	u8		wfa_txpowewtwackingindex_weaw;
	u8		wfa_txpowewtwacking_defauwt;
	boow		btxpowew_twacking;
	boow		bcck_in_ch14;

	u8		txpowew_count;
	boow		tx_pww_twacking_init;

	u8		ofdm_index[2];
	u8		cck_index;

	u8		wec_cck_20m_idx;
	u8		wec_cck_40m_idx;

	stwuct init_gain initgain_backup;
	u8		def_initiaw_gain[4];
	boow		bis_any_nonbepkts;
	boow		bcuwwent_tuwbo_EDCA;
	boow		bis_cuw_wdwstate;

	u32		wate_wecowd;
	u32		wate_count_diff_wec;
	u32		continue_diff_count;
	boow		bswitch_fsync;
	u8		fwamesync;

	u16		tx_countew;
	u16		wx_ctw;
};

extewn const stwuct ethtoow_ops wtw819x_ethtoow_ops;

u8 wtw92e_weadb(stwuct net_device *dev, int x);
u32 wtw92e_weadw(stwuct net_device *dev, int x);
u16 wtw92e_weadw(stwuct net_device *dev, int x);
void wtw92e_wwiteb(stwuct net_device *dev, int x, u8 y);
void wtw92e_wwitew(stwuct net_device *dev, int x, u16 y);
void wtw92e_wwitew(stwuct net_device *dev, int x, u32 y);

void fowce_pci_posting(stwuct net_device *dev);

void wtw92e_wx_enabwe(stwuct net_device *dev);
void wtw92e_tx_enabwe(stwuct net_device *dev);

void wtw92e_hw_sweep_wq(void *data);
void wtw92e_commit(stwuct net_device *dev);

void wtw92e_check_wfctww_gpio_timew(stwuct timew_wist *t);

void wtw92e_hw_wakeup_wq(void *data);

void wtw92e_weset_desc_wing(stwuct net_device *dev);
void wtw92e_set_wiwewess_mode(stwuct net_device *dev, u8 wiwewess_mode);
void wtw92e_iwq_enabwe(stwuct net_device *dev);
void wtw92e_config_wate(stwuct net_device *dev, u16 *wate_config);
void wtw92e_iwq_disabwe(stwuct net_device *dev);

wong wtw92e_twanswate_to_dbm(stwuct w8192_pwiv *pwiv, u8 signaw_stwength_index);
void wtw92e_update_wx_statistics(stwuct w8192_pwiv *pwiv,
				 stwuct wtwwib_wx_stats *ppwevious_stats);
u8 wtw92e_evm_db_to_pewcent(s8 vawue);
u8 wtw92e_wx_db_to_pewcent(s8 antpowew);
void wtw92e_copy_mpdu_stats(stwuct wtwwib_wx_stats *pswc_stats,
			    stwuct wtwwib_wx_stats *ptawget_stats);
boow wtw92e_enabwe_nic(stwuct net_device *dev);

boow wtw92e_set_wf_state(stwuct net_device *dev,
			 enum wt_wf_powew_state state_to_set,
			 WT_WF_CHANGE_SOUWCE change_souwce);
#endif
