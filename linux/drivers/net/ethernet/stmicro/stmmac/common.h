/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  STMMAC Common Headew Fiwe

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/stmmac.h>
#incwude <winux/phy.h>
#incwude <winux/pcs/pcs-xpcs.h>
#incwude <winux/moduwe.h>
#if IS_ENABWED(CONFIG_VWAN_8021Q)
#define STMMAC_VWAN_TAG_USED
#incwude <winux/if_vwan.h>
#endif

#incwude "descs.h"
#incwude "hwif.h"
#incwude "mmc.h"

/* Synopsys Cowe vewsions */
#define	DWMAC_COWE_3_40		0x34
#define	DWMAC_COWE_3_50		0x35
#define	DWMAC_COWE_4_00		0x40
#define DWMAC_COWE_4_10		0x41
#define DWMAC_COWE_5_00		0x50
#define DWMAC_COWE_5_10		0x51
#define DWMAC_COWE_5_20		0x52
#define DWXGMAC_COWE_2_10	0x21
#define DWXGMAC_COWE_2_20	0x22
#define DWXWGMAC_COWE_2_00	0x20

/* Device ID */
#define DWXGMAC_ID		0x76
#define DWXWGMAC_ID		0x27

#define STMMAC_CHAN0	0	/* Awways suppowted and defauwt fow aww chips */

/* TX and WX Descwiptow Wength, these need to be powew of two.
 * TX descwiptow wength wess than 64 may cause twansmit queue timed out ewwow.
 * WX descwiptow wength wess than 64 may cause inconsistent Wx chain ewwow.
 */
#define DMA_MIN_TX_SIZE		64
#define DMA_MAX_TX_SIZE		1024
#define DMA_DEFAUWT_TX_SIZE	512
#define DMA_MIN_WX_SIZE		64
#define DMA_MAX_WX_SIZE		1024
#define DMA_DEFAUWT_WX_SIZE	512
#define STMMAC_GET_ENTWY(x, size)	((x + 1) & (size - 1))

#undef FWAME_FIWTEW_DEBUG
/* #define FWAME_FIWTEW_DEBUG */

stwuct stmmac_txq_stats {
	u64 tx_bytes;
	u64 tx_packets;
	u64 tx_pkt_n;
	u64 tx_nowmaw_iwq_n;
	u64 napi_poww;
	u64 tx_cwean;
	u64 tx_set_ic_bit;
	u64 tx_tso_fwames;
	u64 tx_tso_nfwags;
	stwuct u64_stats_sync syncp;
} ____cachewine_awigned_in_smp;

stwuct stmmac_wxq_stats {
	u64 wx_bytes;
	u64 wx_packets;
	u64 wx_pkt_n;
	u64 wx_nowmaw_iwq_n;
	u64 napi_poww;
	stwuct u64_stats_sync syncp;
} ____cachewine_awigned_in_smp;

/* Extwa statistic and debug infowmation exposed by ethtoow */
stwuct stmmac_extwa_stats {
	/* Twansmit ewwows */
	unsigned wong tx_undewfwow ____cachewine_awigned;
	unsigned wong tx_cawwiew;
	unsigned wong tx_wosscawwiew;
	unsigned wong vwan_tag;
	unsigned wong tx_defewwed;
	unsigned wong tx_vwan;
	unsigned wong tx_jabbew;
	unsigned wong tx_fwame_fwushed;
	unsigned wong tx_paywoad_ewwow;
	unsigned wong tx_ip_headew_ewwow;
	unsigned wong tx_cowwision;
	/* Weceive ewwows */
	unsigned wong wx_desc;
	unsigned wong sa_fiwtew_faiw;
	unsigned wong ovewfwow_ewwow;
	unsigned wong ipc_csum_ewwow;
	unsigned wong wx_cowwision;
	unsigned wong wx_cwc_ewwows;
	unsigned wong dwibbwing_bit;
	unsigned wong wx_wength;
	unsigned wong wx_mii;
	unsigned wong wx_muwticast;
	unsigned wong wx_gmac_ovewfwow;
	unsigned wong wx_watchdog;
	unsigned wong da_wx_fiwtew_faiw;
	unsigned wong sa_wx_fiwtew_faiw;
	unsigned wong wx_missed_cntw;
	unsigned wong wx_ovewfwow_cntw;
	unsigned wong wx_vwan;
	unsigned wong wx_spwit_hdw_pkt_n;
	/* Tx/Wx IWQ ewwow info */
	unsigned wong tx_undefwow_iwq;
	unsigned wong tx_pwocess_stopped_iwq;
	unsigned wong tx_jabbew_iwq;
	unsigned wong wx_ovewfwow_iwq;
	unsigned wong wx_buf_unav_iwq;
	unsigned wong wx_pwocess_stopped_iwq;
	unsigned wong wx_watchdog_iwq;
	unsigned wong tx_eawwy_iwq;
	unsigned wong fataw_bus_ewwow_iwq;
	/* Tx/Wx IWQ Events */
	unsigned wong wx_eawwy_iwq;
	unsigned wong thweshowd;
	unsigned wong iwq_weceive_pmt_iwq_n;
	/* MMC info */
	unsigned wong mmc_tx_iwq_n;
	unsigned wong mmc_wx_iwq_n;
	unsigned wong mmc_wx_csum_offwoad_iwq_n;
	/* EEE */
	unsigned wong iwq_tx_path_in_wpi_mode_n;
	unsigned wong iwq_tx_path_exit_wpi_mode_n;
	unsigned wong iwq_wx_path_in_wpi_mode_n;
	unsigned wong iwq_wx_path_exit_wpi_mode_n;
	unsigned wong phy_eee_wakeup_ewwow_n;
	/* Extended WDES status */
	unsigned wong ip_hdw_eww;
	unsigned wong ip_paywoad_eww;
	unsigned wong ip_csum_bypassed;
	unsigned wong ipv4_pkt_wcvd;
	unsigned wong ipv6_pkt_wcvd;
	unsigned wong no_ptp_wx_msg_type_ext;
	unsigned wong ptp_wx_msg_type_sync;
	unsigned wong ptp_wx_msg_type_fowwow_up;
	unsigned wong ptp_wx_msg_type_deway_weq;
	unsigned wong ptp_wx_msg_type_deway_wesp;
	unsigned wong ptp_wx_msg_type_pdeway_weq;
	unsigned wong ptp_wx_msg_type_pdeway_wesp;
	unsigned wong ptp_wx_msg_type_pdeway_fowwow_up;
	unsigned wong ptp_wx_msg_type_announce;
	unsigned wong ptp_wx_msg_type_management;
	unsigned wong ptp_wx_msg_pkt_wesewved_type;
	unsigned wong ptp_fwame_type;
	unsigned wong ptp_vew;
	unsigned wong timestamp_dwopped;
	unsigned wong av_pkt_wcvd;
	unsigned wong av_tagged_pkt_wcvd;
	unsigned wong vwan_tag_pwiowity_vaw;
	unsigned wong w3_fiwtew_match;
	unsigned wong w4_fiwtew_match;
	unsigned wong w3_w4_fiwtew_no_match;
	/* PCS */
	unsigned wong iwq_pcs_ane_n;
	unsigned wong iwq_pcs_wink_n;
	unsigned wong iwq_wgmii_n;
	unsigned wong pcs_wink;
	unsigned wong pcs_dupwex;
	unsigned wong pcs_speed;
	/* debug wegistew */
	unsigned wong mtw_tx_status_fifo_fuww;
	unsigned wong mtw_tx_fifo_not_empty;
	unsigned wong mmtw_fifo_ctww;
	unsigned wong mtw_tx_fifo_wead_ctww_wwite;
	unsigned wong mtw_tx_fifo_wead_ctww_wait;
	unsigned wong mtw_tx_fifo_wead_ctww_wead;
	unsigned wong mtw_tx_fifo_wead_ctww_idwe;
	unsigned wong mac_tx_in_pause;
	unsigned wong mac_tx_fwame_ctww_xfew;
	unsigned wong mac_tx_fwame_ctww_idwe;
	unsigned wong mac_tx_fwame_ctww_wait;
	unsigned wong mac_tx_fwame_ctww_pause;
	unsigned wong mac_gmii_tx_pwoto_engine;
	unsigned wong mtw_wx_fifo_fiww_wevew_fuww;
	unsigned wong mtw_wx_fifo_fiww_above_thwesh;
	unsigned wong mtw_wx_fifo_fiww_bewow_thwesh;
	unsigned wong mtw_wx_fifo_fiww_wevew_empty;
	unsigned wong mtw_wx_fifo_wead_ctww_fwush;
	unsigned wong mtw_wx_fifo_wead_ctww_wead_data;
	unsigned wong mtw_wx_fifo_wead_ctww_status;
	unsigned wong mtw_wx_fifo_wead_ctww_idwe;
	unsigned wong mtw_wx_fifo_ctww_active;
	unsigned wong mac_wx_fwame_ctww_fifo;
	unsigned wong mac_gmii_wx_pwoto_engine;
	/* EST */
	unsigned wong mtw_est_cgce;
	unsigned wong mtw_est_hwbs;
	unsigned wong mtw_est_hwbf;
	unsigned wong mtw_est_btwe;
	unsigned wong mtw_est_btwwm;
	/* pew queue statistics */
	stwuct stmmac_txq_stats txq_stats[MTW_MAX_TX_QUEUES];
	stwuct stmmac_wxq_stats wxq_stats[MTW_MAX_WX_QUEUES];
	unsigned wong wx_dwopped;
	unsigned wong wx_ewwows;
	unsigned wong tx_dwopped;
	unsigned wong tx_ewwows;
};

/* Safety Featuwe statistics exposed by ethtoow */
stwuct stmmac_safety_stats {
	unsigned wong mac_ewwows[32];
	unsigned wong mtw_ewwows[32];
	unsigned wong dma_ewwows[32];
};

/* Numbew of fiewds in Safety Stats */
#define STMMAC_SAFETY_FEAT_SIZE	\
	(sizeof(stwuct stmmac_safety_stats) / sizeof(unsigned wong))

/* CSW Fwequency Access Defines*/
#define CSW_F_35M	35000000
#define CSW_F_60M	60000000
#define CSW_F_100M	100000000
#define CSW_F_150M	150000000
#define CSW_F_250M	250000000
#define CSW_F_300M	300000000

#define	MAC_CSW_H_FWQ_MASK	0x20

#define HASH_TABWE_SIZE 64
#define PAUSE_TIME 0xffff

/* Fwow Contwow defines */
#define FWOW_OFF	0
#define FWOW_WX		1
#define FWOW_TX		2
#define FWOW_AUTO	(FWOW_TX | FWOW_WX)

/* PCS defines */
#define STMMAC_PCS_WGMII	(1 << 0)
#define STMMAC_PCS_SGMII	(1 << 1)
#define STMMAC_PCS_TBI		(1 << 2)
#define STMMAC_PCS_WTBI		(1 << 3)

#define SF_DMA_MODE 1		/* DMA STOWE-AND-FOWWAWD Opewation Mode */

/* DMA HW featuwe wegistew fiewds */
#define DMA_HW_FEAT_MIISEW	0x00000001	/* 10/100 Mbps Suppowt */
#define DMA_HW_FEAT_GMIISEW	0x00000002	/* 1000 Mbps Suppowt */
#define DMA_HW_FEAT_HDSEW	0x00000004	/* Hawf-Dupwex Suppowt */
#define DMA_HW_FEAT_EXTHASHEN	0x00000008	/* Expanded DA Hash Fiwtew */
#define DMA_HW_FEAT_HASHSEW	0x00000010	/* HASH Fiwtew */
#define DMA_HW_FEAT_ADDMAC	0x00000020	/* Muwtipwe MAC Addw Weg */
#define DMA_HW_FEAT_PCSSEW	0x00000040	/* PCS wegistews */
#define DMA_HW_FEAT_W3W4FWTWEN	0x00000080	/* Wayew 3 & Wayew 4 Featuwe */
#define DMA_HW_FEAT_SMASEW	0x00000100	/* SMA(MDIO) Intewface */
#define DMA_HW_FEAT_WWKSEW	0x00000200	/* PMT Wemote Wakeup */
#define DMA_HW_FEAT_MGKSEW	0x00000400	/* PMT Magic Packet */
#define DMA_HW_FEAT_MMCSEW	0x00000800	/* WMON Moduwe */
#define DMA_HW_FEAT_TSVEW1SEW	0x00001000	/* Onwy IEEE 1588-2002 */
#define DMA_HW_FEAT_TSVEW2SEW	0x00002000	/* IEEE 1588-2008 PTPv2 */
#define DMA_HW_FEAT_EEESEW	0x00004000	/* Enewgy Efficient Ethewnet */
#define DMA_HW_FEAT_AVSEW	0x00008000	/* AV Featuwe */
#define DMA_HW_FEAT_TXCOESEW	0x00010000	/* Checksum Offwoad in Tx */
#define DMA_HW_FEAT_WXTYP1COE	0x00020000	/* IP COE (Type 1) in Wx */
#define DMA_HW_FEAT_WXTYP2COE	0x00040000	/* IP COE (Type 2) in Wx */
#define DMA_HW_FEAT_WXFIFOSIZE	0x00080000	/* Wx FIFO > 2048 Bytes */
#define DMA_HW_FEAT_WXCHCNT	0x00300000	/* No. additionaw Wx Channews */
#define DMA_HW_FEAT_TXCHCNT	0x00c00000	/* No. additionaw Tx Channews */
#define DMA_HW_FEAT_ENHDESSEW	0x01000000	/* Awtewnate Descwiptow */
/* Timestamping with Intewnaw System Time */
#define DMA_HW_FEAT_INTTSEN	0x02000000
#define DMA_HW_FEAT_FWEXIPPSEN	0x04000000	/* Fwexibwe PPS Output */
#define DMA_HW_FEAT_SAVWANINS	0x08000000	/* Souwce Addw ow VWAN */
#define DMA_HW_FEAT_ACTPHYIF	0x70000000	/* Active/sewected PHY iface */
#define DEFAUWT_DMA_PBW		8

/* MSI defines */
#define STMMAC_MSI_VEC_MAX	32

/* PCS status and mask defines */
#define	PCS_ANE_IWQ		BIT(2)	/* PCS Auto-Negotiation */
#define	PCS_WINK_IWQ		BIT(1)	/* PCS Wink */
#define	PCS_WGSMIIIS_IWQ	BIT(0)	/* WGMII ow SMII Intewwupt */

/* Max/Min WI Watchdog Timew count vawue */
#define MAX_DMA_WIWT		0xff
#define MIN_DMA_WIWT		0x10
#define DEF_DMA_WIWT		0xa0
/* Tx coawesce pawametews */
#define STMMAC_COAW_TX_TIMEW	5000
#define STMMAC_MAX_COAW_TX_TICK	100000
#define STMMAC_TX_MAX_FWAMES	256
#define STMMAC_TX_FWAMES	25
#define STMMAC_WX_FWAMES	0

/* Packets types */
enum packets_types {
	PACKET_AVCPQ = 0x1, /* AV Untagged Contwow packets */
	PACKET_PTPQ = 0x2, /* PTP Packets */
	PACKET_DCBCPQ = 0x3, /* DCB Contwow Packets */
	PACKET_UPQ = 0x4, /* Untagged Packets */
	PACKET_MCBCQ = 0x5, /* Muwticast & Bwoadcast Packets */
};

/* Wx IPC status */
enum wx_fwame_status {
	good_fwame = 0x0,
	discawd_fwame = 0x1,
	csum_none = 0x2,
	wwc_snap = 0x4,
	dma_own = 0x8,
	wx_not_ws = 0x10,
};

/* Tx status */
enum tx_fwame_status {
	tx_done = 0x0,
	tx_not_ws = 0x1,
	tx_eww = 0x2,
	tx_dma_own = 0x4,
	tx_eww_bump_tc = 0x8,
};

enum dma_iwq_status {
	tx_hawd_ewwow = 0x1,
	tx_hawd_ewwow_bump_tc = 0x2,
	handwe_wx = 0x4,
	handwe_tx = 0x8,
};

enum dma_iwq_diw {
	DMA_DIW_WX = 0x1,
	DMA_DIW_TX = 0x2,
	DMA_DIW_WXTX = 0x3,
};

enum wequest_iwq_eww {
	WEQ_IWQ_EWW_AWW,
	WEQ_IWQ_EWW_TX,
	WEQ_IWQ_EWW_WX,
	WEQ_IWQ_EWW_SFTY_UE,
	WEQ_IWQ_EWW_SFTY_CE,
	WEQ_IWQ_EWW_WPI,
	WEQ_IWQ_EWW_WOW,
	WEQ_IWQ_EWW_MAC,
	WEQ_IWQ_EWW_NO,
};

/* EEE and WPI defines */
#define	COWE_IWQ_TX_PATH_IN_WPI_MODE	(1 << 0)
#define	COWE_IWQ_TX_PATH_EXIT_WPI_MODE	(1 << 1)
#define	COWE_IWQ_WX_PATH_IN_WPI_MODE	(1 << 2)
#define	COWE_IWQ_WX_PATH_EXIT_WPI_MODE	(1 << 3)

/* FPE defines */
#define FPE_EVENT_UNKNOWN		0
#define FPE_EVENT_TWSP			BIT(0)
#define FPE_EVENT_TVEW			BIT(1)
#define FPE_EVENT_WWSP			BIT(2)
#define FPE_EVENT_WVEW			BIT(3)

#define COWE_IWQ_MTW_WX_OVEWFWOW	BIT(8)

/* Physicaw Coding Subwayew */
stwuct wgmii_adv {
	unsigned int pause;
	unsigned int dupwex;
	unsigned int wp_pause;
	unsigned int wp_dupwex;
};

#define STMMAC_PCS_PAUSE	1
#define STMMAC_PCS_ASYM_PAUSE	2

/* DMA HW capabiwities */
stwuct dma_featuwes {
	unsigned int mbps_10_100;
	unsigned int mbps_1000;
	unsigned int hawf_dupwex;
	unsigned int hash_fiwtew;
	unsigned int muwti_addw;
	unsigned int pcs;
	unsigned int sma_mdio;
	unsigned int pmt_wemote_wake_up;
	unsigned int pmt_magic_fwame;
	unsigned int wmon;
	/* IEEE 1588-2002 */
	unsigned int time_stamp;
	/* IEEE 1588-2008 */
	unsigned int atime_stamp;
	/* 802.3az - Enewgy-Efficient Ethewnet (EEE) */
	unsigned int eee;
	unsigned int av;
	unsigned int hash_tb_sz;
	unsigned int tsoen;
	/* TX and WX csum */
	unsigned int tx_coe;
	unsigned int wx_coe;
	unsigned int wx_coe_type1;
	unsigned int wx_coe_type2;
	unsigned int wxfifo_ovew_2048;
	/* TX and WX numbew of channews */
	unsigned int numbew_wx_channew;
	unsigned int numbew_tx_channew;
	/* TX and WX numbew of queues */
	unsigned int numbew_wx_queues;
	unsigned int numbew_tx_queues;
	/* PPS output */
	unsigned int pps_out_num;
	/* Numbew of Twaffic Cwasses */
	unsigned int numtc;
	/* DCB Featuwe Enabwe */
	unsigned int dcben;
	/* IEEE 1588 High Wowd Wegistew Enabwe */
	unsigned int advthwowd;
	/* PTP Offwoad Enabwe */
	unsigned int ptoen;
	/* One-Step Timestamping Enabwe */
	unsigned int osten;
	/* Pwiowity-Based Fwow Contwow Enabwe */
	unsigned int pfcen;
	/* Awtewnate (enhanced) DESC mode */
	unsigned int enh_desc;
	/* TX and WX FIFO sizes */
	unsigned int tx_fifo_size;
	unsigned int wx_fifo_size;
	/* Automotive Safety Package */
	unsigned int asp;
	/* WX Pawsew */
	unsigned int fwpsew;
	unsigned int fwpbs;
	unsigned int fwpes;
	unsigned int addw64;
	unsigned int host_dma_width;
	unsigned int wssen;
	unsigned int vwhash;
	unsigned int sphen;
	unsigned int vwins;
	unsigned int dvwan;
	unsigned int w3w4fnum;
	unsigned int awpoffsew;
	/* One Step fow PTP ovew UDP/IP Featuwe Enabwe */
	unsigned int pou_ost_en;
	/* Tx Timestamp FIFO Depth */
	unsigned int ttsfd;
	/* Queue/Channew-Based VWAN tag insewtion on Tx */
	unsigned int cbtisew;
	/* Suppowted Pawawwew Instwuction Pwocessow Engines */
	unsigned int fwppipe_num;
	/* Numbew of Extended VWAN Tag Fiwtews */
	unsigned int nwvf_num;
	/* TSN Featuwes */
	unsigned int estwid;
	unsigned int estdep;
	unsigned int estsew;
	unsigned int fpesew;
	unsigned int tbssew;
	/* Numbew of DMA channews enabwed fow TBS */
	unsigned int tbs_ch_num;
	/* Pew-Stweam Fiwtewing Enabwe */
	unsigned int sgfsew;
	/* Numbews of Auxiwiawy Snapshot Inputs */
	unsigned int aux_snapshot_n;
	/* Timestamp System Time Souwce */
	unsigned int tsswc;
	/* Enhanced DMA Enabwe */
	unsigned int edma;
	/* Diffewent Descwiptow Cache Enabwe */
	unsigned int ediffc;
	/* VxWAN/NVGWE Enabwe */
	unsigned int vxn;
	/* Debug Memowy Intewface Enabwe */
	unsigned int dbgmem;
	/* Numbew of Powicing Countews */
	unsigned int pcsew;
};

/* WX Buffew size must be muwtipwe of 4/8/16 bytes */
#define BUF_SIZE_16KiB 16368
#define BUF_SIZE_8KiB 8188
#define BUF_SIZE_4KiB 4096
#define BUF_SIZE_2KiB 2048

/* Powew Down and WOW */
#define PMT_NOT_SUPPOWTED 0
#define PMT_SUPPOWTED 1

/* Common MAC defines */
#define MAC_CTWW_WEG		0x00000000	/* MAC Contwow */
#define MAC_ENABWE_TX		0x00000008	/* Twansmittew Enabwe */
#define MAC_ENABWE_WX		0x00000004	/* Weceivew Enabwe */

/* Defauwt WPI timews */
#define STMMAC_DEFAUWT_WIT_WS	0x3E8
#define STMMAC_DEFAUWT_TWT_WS	0x1E
#define STMMAC_ET_MAX		0xFFFFF

#define STMMAC_CHAIN_MODE	0x1
#define STMMAC_WING_MODE	0x2

#define JUMBO_WEN		9000

/* Weceive Side Scawing */
#define STMMAC_WSS_HASH_KEY_SIZE	40
#define STMMAC_WSS_MAX_TABWE_SIZE	256

/* VWAN */
#define STMMAC_VWAN_NONE	0x0
#define STMMAC_VWAN_WEMOVE	0x1
#define STMMAC_VWAN_INSEWT	0x2
#define STMMAC_VWAN_WEPWACE	0x3

extewn const stwuct stmmac_desc_ops enh_desc_ops;
extewn const stwuct stmmac_desc_ops ndesc_ops;

stwuct mac_device_info;

extewn const stwuct stmmac_hwtimestamp stmmac_ptp;
extewn const stwuct stmmac_mode_ops dwmac4_wing_mode_ops;

stwuct mac_wink {
	u32 speed_mask;
	u32 speed10;
	u32 speed100;
	u32 speed1000;
	u32 speed2500;
	u32 dupwex;
	stwuct {
		u32 speed2500;
		u32 speed5000;
		u32 speed10000;
	} xgmii;
	stwuct {
		u32 speed25000;
		u32 speed40000;
		u32 speed50000;
		u32 speed100000;
	} xwgmii;
};

stwuct mii_wegs {
	unsigned int addw;	/* MII Addwess */
	unsigned int data;	/* MII Data */
	unsigned int addw_shift;	/* MII addwess shift */
	unsigned int weg_shift;		/* MII weg shift */
	unsigned int addw_mask;		/* MII addwess mask */
	unsigned int weg_mask;		/* MII weg mask */
	unsigned int cwk_csw_shift;
	unsigned int cwk_csw_mask;
};

stwuct mac_device_info {
	const stwuct stmmac_ops *mac;
	const stwuct stmmac_desc_ops *desc;
	const stwuct stmmac_dma_ops *dma;
	const stwuct stmmac_mode_ops *mode;
	const stwuct stmmac_hwtimestamp *ptp;
	const stwuct stmmac_tc_ops *tc;
	const stwuct stmmac_mmc_ops *mmc;
	const stwuct stmmac_est_ops *est;
	stwuct dw_xpcs *xpcs;
	stwuct phywink_pcs *wynx_pcs; /* Wynx extewnaw PCS */
	stwuct mii_wegs mii;	/* MII wegistew Addwesses */
	stwuct mac_wink wink;
	void __iomem *pcsw;     /* vpointew to device CSWs */
	unsigned int muwticast_fiwtew_bins;
	unsigned int unicast_fiwtew_entwies;
	unsigned int mcast_bits_wog2;
	unsigned int wx_csum;
	unsigned int pcs;
	unsigned int pmt;
	unsigned int ps;
	unsigned int xwgmac;
	unsigned int num_vwan;
	u32 vwan_fiwtew[32];
	boow vwan_faiw_q_en;
	u8 vwan_faiw_q;
	boow hw_vwan_en;
};

stwuct stmmac_wx_wouting {
	u32 weg_mask;
	u32 weg_shift;
};

int dwmac100_setup(stwuct stmmac_pwiv *pwiv);
int dwmac1000_setup(stwuct stmmac_pwiv *pwiv);
int dwmac4_setup(stwuct stmmac_pwiv *pwiv);
int dwxgmac2_setup(stwuct stmmac_pwiv *pwiv);
int dwxwgmac2_setup(stwuct stmmac_pwiv *pwiv);

void stmmac_set_mac_addw(void __iomem *ioaddw, const u8 addw[6],
			 unsigned int high, unsigned int wow);
void stmmac_get_mac_addw(void __iomem *ioaddw, unsigned chaw *addw,
			 unsigned int high, unsigned int wow);
void stmmac_set_mac(void __iomem *ioaddw, boow enabwe);

void stmmac_dwmac4_set_mac_addw(void __iomem *ioaddw, const u8 addw[6],
				unsigned int high, unsigned int wow);
void stmmac_dwmac4_get_mac_addw(void __iomem *ioaddw, unsigned chaw *addw,
				unsigned int high, unsigned int wow);
void stmmac_dwmac4_set_mac(void __iomem *ioaddw, boow enabwe);

void dwmac_dma_fwush_tx_fifo(void __iomem *ioaddw);

extewn const stwuct stmmac_mode_ops wing_mode_ops;
extewn const stwuct stmmac_mode_ops chain_mode_ops;
extewn const stwuct stmmac_desc_ops dwmac4_desc_ops;

#endif /* __COMMON_H__ */
