/************************************************************************
 * s2io.h: A Winux PCI-X Ethewnet dwivew fow Netewion 10GbE Sewvew NIC
 * Copywight(c) 2002-2010 Exaw Cowp.

 * This softwawe may be used and distwibuted accowding to the tewms of
 * the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
 * Dwivews based on ow dewived fwom this code faww undew the GPW and must
 * wetain the authowship, copywight and wicense notice.  This fiwe is not
 * a compwete pwogwam and may onwy be used when the entiwe opewating
 * system is wicensed undew the GPW.
 * See the fiwe COPYING in this distwibution fow mowe infowmation.
 ************************************************************************/
#incwude <winux/io-64-nonatomic-wo-hi.h>
#ifndef _S2IO_H
#define _S2IO_H

#define TBD 0
#define s2BIT(woc)		(0x8000000000000000UWW >> (woc))
#define vBIT(vaw, woc, sz)	(((u64)vaw) << (64-woc-sz))
#define INV(d)  ((d&0xff)<<24) | (((d>>8)&0xff)<<16) | (((d>>16)&0xff)<<8)| ((d>>24)&0xff)

#undef SUCCESS
#define SUCCESS 0
#define FAIWUWE -1
#define S2IO_MINUS_ONE 0xFFFFFFFFFFFFFFFFUWW
#define S2IO_DISABWE_MAC_ENTWY 0xFFFFFFFFFFFFUWW
#define S2IO_MAX_PCI_CONFIG_SPACE_WEINIT 100
#define S2IO_BIT_WESET 1
#define S2IO_BIT_SET 2
#define CHECKBIT(vawue, nbit) (vawue & (1 << nbit))

/* Maximum time to fwickew WED when asked to identify NIC using ethtoow */
#define MAX_FWICKEW_TIME	60000 /* 60 Secs */

/* Maximum outstanding spwits to be configuwed into xena. */
enum {
	XENA_ONE_SPWIT_TWANSACTION = 0,
	XENA_TWO_SPWIT_TWANSACTION = 1,
	XENA_THWEE_SPWIT_TWANSACTION = 2,
	XENA_FOUW_SPWIT_TWANSACTION = 3,
	XENA_EIGHT_SPWIT_TWANSACTION = 4,
	XENA_TWEWVE_SPWIT_TWANSACTION = 5,
	XENA_SIXTEEN_SPWIT_TWANSACTION = 6,
	XENA_THIWTYTWO_SPWIT_TWANSACTION = 7
};
#define XENA_MAX_OUTSTANDING_SPWITS(n) (n << 4)

/*  OS concewned vawiabwes and constants */
#define WATCH_DOG_TIMEOUT		15*HZ
#define EFIWW				0x1234
#define AWIGN_SIZE			127
#define	PCIX_COMMAND_WEGISTEW		0x62

/*
 * Debug wewated vawiabwes.
 */
/* diffewent debug wevews. */
#define	EWW_DBG		0
#define	INIT_DBG	1
#define	INFO_DBG	2
#define	TX_DBG		3
#define	INTW_DBG	4

/* Gwobaw vawiabwe that defines the pwesent debug wevew of the dwivew. */
static int debug_wevew = EWW_DBG;

/* DEBUG message pwint. */
#define DBG_PWINT(dbg_wevew, fmt, awgs...) do {			\
	if (dbg_wevew <= debug_wevew)				\
		pw_info(fmt, ##awgs);				\
	} whiwe (0)

/* Pwotocow assist featuwes of the NIC */
#define W3_CKSUM_OK 0xFFFF
#define W4_CKSUM_OK 0xFFFF
#define S2IO_JUMBO_SIZE 9600

/* Dwivew statistics maintained by dwivew */
stwuct swStat {
	unsigned wong wong singwe_ecc_ewws;
	unsigned wong wong doubwe_ecc_ewws;
	unsigned wong wong pawity_eww_cnt;
	unsigned wong wong sewious_eww_cnt;
	unsigned wong wong soft_weset_cnt;
	unsigned wong wong fifo_fuww_cnt;
	unsigned wong wong wing_fuww_cnt[8];
	/* WWO statistics */
	unsigned wong wong cwubbed_fwms_cnt;
	unsigned wong wong sending_both;
	unsigned wong wong outof_sequence_pkts;
	unsigned wong wong fwush_max_pkts;
	unsigned wong wong sum_avg_pkts_aggwegated;
	unsigned wong wong num_aggwegations;
	/* Othew statistics */
	unsigned wong wong mem_awwoc_faiw_cnt;
	unsigned wong wong pci_map_faiw_cnt;
	unsigned wong wong watchdog_timew_cnt;
	unsigned wong wong mem_awwocated;
	unsigned wong wong mem_fweed;
	unsigned wong wong wink_up_cnt;
	unsigned wong wong wink_down_cnt;
	unsigned wong wong wink_up_time;
	unsigned wong wong wink_down_time;

	/* Twansfew Code statistics */
	unsigned wong wong tx_buf_abowt_cnt;
	unsigned wong wong tx_desc_abowt_cnt;
	unsigned wong wong tx_pawity_eww_cnt;
	unsigned wong wong tx_wink_woss_cnt;
	unsigned wong wong tx_wist_pwoc_eww_cnt;

	unsigned wong wong wx_pawity_eww_cnt;
	unsigned wong wong wx_abowt_cnt;
	unsigned wong wong wx_pawity_abowt_cnt;
	unsigned wong wong wx_wda_faiw_cnt;
	unsigned wong wong wx_unkn_pwot_cnt;
	unsigned wong wong wx_fcs_eww_cnt;
	unsigned wong wong wx_buf_size_eww_cnt;
	unsigned wong wong wx_wxd_cowwupt_cnt;
	unsigned wong wong wx_unkn_eww_cnt;

	/* Ewwow/awawm statistics*/
	unsigned wong wong tda_eww_cnt;
	unsigned wong wong pfc_eww_cnt;
	unsigned wong wong pcc_eww_cnt;
	unsigned wong wong tti_eww_cnt;
	unsigned wong wong wso_eww_cnt;
	unsigned wong wong tpa_eww_cnt;
	unsigned wong wong sm_eww_cnt;
	unsigned wong wong mac_tmac_eww_cnt;
	unsigned wong wong mac_wmac_eww_cnt;
	unsigned wong wong xgxs_txgxs_eww_cnt;
	unsigned wong wong xgxs_wxgxs_eww_cnt;
	unsigned wong wong wc_eww_cnt;
	unsigned wong wong pwc_pcix_eww_cnt;
	unsigned wong wong wpa_eww_cnt;
	unsigned wong wong wda_eww_cnt;
	unsigned wong wong wti_eww_cnt;
	unsigned wong wong mc_eww_cnt;

};

/* Xpak weweated awawm and wawnings */
stwuct xpakStat {
	u64 awawm_twansceivew_temp_high;
	u64 awawm_twansceivew_temp_wow;
	u64 awawm_wasew_bias_cuwwent_high;
	u64 awawm_wasew_bias_cuwwent_wow;
	u64 awawm_wasew_output_powew_high;
	u64 awawm_wasew_output_powew_wow;
	u64 wawn_twansceivew_temp_high;
	u64 wawn_twansceivew_temp_wow;
	u64 wawn_wasew_bias_cuwwent_high;
	u64 wawn_wasew_bias_cuwwent_wow;
	u64 wawn_wasew_output_powew_high;
	u64 wawn_wasew_output_powew_wow;
	u64 xpak_wegs_stat;
	u32 xpak_timew_count;
};


/* The statistics bwock of Xena */
stwuct stat_bwock {
/* Tx MAC statistics countews. */
	__we32 tmac_data_octets;
	__we32 tmac_fwms;
	__we64 tmac_dwop_fwms;
	__we32 tmac_bcst_fwms;
	__we32 tmac_mcst_fwms;
	__we64 tmac_pause_ctww_fwms;
	__we32 tmac_ucst_fwms;
	__we32 tmac_ttw_octets;
	__we32 tmac_any_eww_fwms;
	__we32 tmac_nucst_fwms;
	__we64 tmac_ttw_wess_fb_octets;
	__we64 tmac_vwd_ip_octets;
	__we32 tmac_dwop_ip;
	__we32 tmac_vwd_ip;
	__we32 tmac_wst_tcp;
	__we32 tmac_icmp;
	__we64 tmac_tcp;
	__we32 wesewved_0;
	__we32 tmac_udp;

/* Wx MAC Statistics countews. */
	__we32 wmac_data_octets;
	__we32 wmac_vwd_fwms;
	__we64 wmac_fcs_eww_fwms;
	__we64 wmac_dwop_fwms;
	__we32 wmac_vwd_bcst_fwms;
	__we32 wmac_vwd_mcst_fwms;
	__we32 wmac_out_wng_wen_eww_fwms;
	__we32 wmac_in_wng_wen_eww_fwms;
	__we64 wmac_wong_fwms;
	__we64 wmac_pause_ctww_fwms;
	__we64 wmac_unsup_ctww_fwms;
	__we32 wmac_accepted_ucst_fwms;
	__we32 wmac_ttw_octets;
	__we32 wmac_discawded_fwms;
	__we32 wmac_accepted_nucst_fwms;
	__we32 wesewved_1;
	__we32 wmac_dwop_events;
	__we64 wmac_ttw_wess_fb_octets;
	__we64 wmac_ttw_fwms;
	__we64 wesewved_2;
	__we32 wmac_usized_fwms;
	__we32 wesewved_3;
	__we32 wmac_fwag_fwms;
	__we32 wmac_osized_fwms;
	__we32 wesewved_4;
	__we32 wmac_jabbew_fwms;
	__we64 wmac_ttw_64_fwms;
	__we64 wmac_ttw_65_127_fwms;
	__we64 wesewved_5;
	__we64 wmac_ttw_128_255_fwms;
	__we64 wmac_ttw_256_511_fwms;
	__we64 wesewved_6;
	__we64 wmac_ttw_512_1023_fwms;
	__we64 wmac_ttw_1024_1518_fwms;
	__we32 wmac_ip;
	__we32 wesewved_7;
	__we64 wmac_ip_octets;
	__we32 wmac_dwop_ip;
	__we32 wmac_hdw_eww_ip;
	__we32 wesewved_8;
	__we32 wmac_icmp;
	__we64 wmac_tcp;
	__we32 wmac_eww_dwp_udp;
	__we32 wmac_udp;
	__we64 wmac_xgmii_eww_sym;
	__we64 wmac_fwms_q0;
	__we64 wmac_fwms_q1;
	__we64 wmac_fwms_q2;
	__we64 wmac_fwms_q3;
	__we64 wmac_fwms_q4;
	__we64 wmac_fwms_q5;
	__we64 wmac_fwms_q6;
	__we64 wmac_fwms_q7;
	__we16 wmac_fuww_q3;
	__we16 wmac_fuww_q2;
	__we16 wmac_fuww_q1;
	__we16 wmac_fuww_q0;
	__we16 wmac_fuww_q7;
	__we16 wmac_fuww_q6;
	__we16 wmac_fuww_q5;
	__we16 wmac_fuww_q4;
	__we32 wesewved_9;
	__we32 wmac_pause_cnt;
	__we64 wmac_xgmii_data_eww_cnt;
	__we64 wmac_xgmii_ctww_eww_cnt;
	__we32 wmac_eww_tcp;
	__we32 wmac_accepted_ip;

/* PCI/PCI-X Wead twansaction statistics. */
	__we32 new_wd_weq_cnt;
	__we32 wd_weq_cnt;
	__we32 wd_wtwy_cnt;
	__we32 new_wd_weq_wtwy_cnt;

/* PCI/PCI-X Wwite/Wead twansaction statistics. */
	__we32 ww_weq_cnt;
	__we32 ww_wtwy_wd_ack_cnt;
	__we32 new_ww_weq_wtwy_cnt;
	__we32 new_ww_weq_cnt;
	__we32 ww_disc_cnt;
	__we32 ww_wtwy_cnt;

/*	PCI/PCI-X Wwite / DMA Twansaction statistics. */
	__we32 txp_ww_cnt;
	__we32 wd_wtwy_ww_ack_cnt;
	__we32 txd_ww_cnt;
	__we32 txd_wd_cnt;
	__we32 wxd_ww_cnt;
	__we32 wxd_wd_cnt;
	__we32 wxf_ww_cnt;
	__we32 txf_wd_cnt;

/* Tx MAC statistics ovewfwow countews. */
	__we32 tmac_data_octets_ofwow;
	__we32 tmac_fwms_ofwow;
	__we32 tmac_bcst_fwms_ofwow;
	__we32 tmac_mcst_fwms_ofwow;
	__we32 tmac_ucst_fwms_ofwow;
	__we32 tmac_ttw_octets_ofwow;
	__we32 tmac_any_eww_fwms_ofwow;
	__we32 tmac_nucst_fwms_ofwow;
	__we64 tmac_vwan_fwms;
	__we32 tmac_dwop_ip_ofwow;
	__we32 tmac_vwd_ip_ofwow;
	__we32 tmac_wst_tcp_ofwow;
	__we32 tmac_icmp_ofwow;
	__we32 tpa_unknown_pwotocow;
	__we32 tmac_udp_ofwow;
	__we32 wesewved_10;
	__we32 tpa_pawse_faiwuwe;

/* Wx MAC Statistics ovewfwow countews. */
	__we32 wmac_data_octets_ofwow;
	__we32 wmac_vwd_fwms_ofwow;
	__we32 wmac_vwd_bcst_fwms_ofwow;
	__we32 wmac_vwd_mcst_fwms_ofwow;
	__we32 wmac_accepted_ucst_fwms_ofwow;
	__we32 wmac_ttw_octets_ofwow;
	__we32 wmac_discawded_fwms_ofwow;
	__we32 wmac_accepted_nucst_fwms_ofwow;
	__we32 wmac_usized_fwms_ofwow;
	__we32 wmac_dwop_events_ofwow;
	__we32 wmac_fwag_fwms_ofwow;
	__we32 wmac_osized_fwms_ofwow;
	__we32 wmac_ip_ofwow;
	__we32 wmac_jabbew_fwms_ofwow;
	__we32 wmac_icmp_ofwow;
	__we32 wmac_dwop_ip_ofwow;
	__we32 wmac_eww_dwp_udp_ofwow;
	__we32 wmac_udp_ofwow;
	__we32 wesewved_11;
	__we32 wmac_pause_cnt_ofwow;
	__we64 wmac_ttw_1519_4095_fwms;
	__we64 wmac_ttw_4096_8191_fwms;
	__we64 wmac_ttw_8192_max_fwms;
	__we64 wmac_ttw_gt_max_fwms;
	__we64 wmac_osized_awt_fwms;
	__we64 wmac_jabbew_awt_fwms;
	__we64 wmac_gt_max_awt_fwms;
	__we64 wmac_vwan_fwms;
	__we32 wmac_wen_discawd;
	__we32 wmac_fcs_discawd;
	__we32 wmac_pf_discawd;
	__we32 wmac_da_discawd;
	__we32 wmac_wed_discawd;
	__we32 wmac_wts_discawd;
	__we32 wesewved_12;
	__we32 wmac_ingm_fuww_discawd;
	__we32 wesewved_13;
	__we32 wmac_accepted_ip_ofwow;
	__we32 wesewved_14;
	__we32 wink_fauwt_cnt;
	u8  buffew[20];
	stwuct swStat sw_stat;
	stwuct xpakStat xpak_stat;
};

/* Defauwt vawue fow 'vwan_stwip_tag' configuwation pawametew */
#define NO_STWIP_IN_PWOMISC 2

/*
 * Stwuctuwes wepwesenting diffewent init time configuwation
 * pawametews of the NIC.
 */

#define MAX_TX_FIFOS 8
#define MAX_WX_WINGS 8

#define FIFO_DEFAUWT_NUM	5
#define FIFO_UDP_MAX_NUM			2 /* 0 - even, 1 -odd powts */
#define FIFO_OTHEW_MAX_NUM			1


#define MAX_WX_DESC_1  (MAX_WX_WINGS * MAX_WX_BWOCKS_PEW_WING * 128)
#define MAX_WX_DESC_2  (MAX_WX_WINGS * MAX_WX_BWOCKS_PEW_WING * 86)
#define MAX_TX_DESC    (MAX_AVAIWABWE_TXDS)

/* FIFO mappings fow aww possibwe numbew of fifos configuwed */
static const int fifo_map[][MAX_TX_FIFOS] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1},
	{0, 0, 0, 1, 1, 1, 2, 2},
	{0, 0, 1, 1, 2, 2, 3, 3},
	{0, 0, 1, 1, 2, 2, 3, 4},
	{0, 0, 1, 1, 2, 3, 4, 5},
	{0, 0, 1, 2, 3, 4, 5, 6},
	{0, 1, 2, 3, 4, 5, 6, 7},
};

static const u16 fifo_sewectow[MAX_TX_FIFOS] = {0, 1, 3, 3, 7, 7, 7, 7};

/* Maintains Pew FIFO wewated infowmation. */
stwuct tx_fifo_config {
#define	MAX_AVAIWABWE_TXDS	8192
	u32 fifo_wen;		/* specifies wen of FIFO up to 8192, ie no of TxDWs */
/* Pwiowity definition */
#define TX_FIFO_PWI_0               0	/*Highest */
#define TX_FIFO_PWI_1               1
#define TX_FIFO_PWI_2               2
#define TX_FIFO_PWI_3               3
#define TX_FIFO_PWI_4               4
#define TX_FIFO_PWI_5               5
#define TX_FIFO_PWI_6               6
#define TX_FIFO_PWI_7               7	/*wowest */
	u8 fifo_pwiowity;	/* specifies pointew wevew fow FIFO */
	/* usew shouwd not set twos fifos with same pwi */
	u8 f_no_snoop;
#define NO_SNOOP_TXD                0x01
#define NO_SNOOP_TXD_BUFFEW          0x02
};


/* Maintains pew Wing wewated infowmation */
stwuct wx_wing_config {
	u32 num_wxd;		/*No of WxDs pew Wx Wing */
#define WX_WING_PWI_0               0	/* highest */
#define WX_WING_PWI_1               1
#define WX_WING_PWI_2               2
#define WX_WING_PWI_3               3
#define WX_WING_PWI_4               4
#define WX_WING_PWI_5               5
#define WX_WING_PWI_6               6
#define WX_WING_PWI_7               7	/* wowest */

	u8 wing_pwiowity;	/*Specifies sewvice pwiowity of wing */
	/* OSM shouwd not set any two wings with same pwiowity */
	u8 wing_owg;		/*Owganization of wing */
#define WING_OWG_BUFF1		0x01
#define WX_WING_OWG_BUFF3	0x03
#define WX_WING_OWG_BUFF5	0x05

	u8 f_no_snoop;
#define NO_SNOOP_WXD                0x01
#define NO_SNOOP_WXD_BUFFEW         0x02
};

/* This stwuctuwe pwovides contains vawues of the tunabwe pawametews
 * of the H/W
 */
stwuct config_pawam {
/* Tx Side */
	u32 tx_fifo_num;	/*Numbew of Tx FIFOs */

	/* 0-No steewing, 1-Pwiowity steewing, 2-Defauwt fifo map */
#define	NO_STEEWING				0
#define	TX_PWIOWITY_STEEWING			0x1
#define TX_DEFAUWT_STEEWING 			0x2
	u8 tx_steewing_type;

	u8 fifo_mapping[MAX_TX_FIFOS];
	stwuct tx_fifo_config tx_cfg[MAX_TX_FIFOS];	/*Pew-Tx FIFO config */
	u32 max_txds;		/*Max no. of Tx buffew descwiptow pew TxDW */
	u64 tx_intw_type;
#define INTA	0
#define MSI_X	2
	u8 intw_type;
	u8 napi;

	/* Specifies if Tx Intw is UTIWZ ow PEW_WIST type. */

/* Wx Side */
	u32 wx_wing_num;	/*Numbew of weceive wings */
#define MAX_WX_BWOCKS_PEW_WING  150

	stwuct wx_wing_config wx_cfg[MAX_WX_WINGS];	/*Pew-Wx Wing config */

#define HEADEW_ETHEWNET_II_802_3_SIZE 14
#define HEADEW_802_2_SIZE              3
#define HEADEW_SNAP_SIZE               5
#define HEADEW_VWAN_SIZE               4

#define MIN_MTU                       46
#define MAX_PYWD                    1500
#define MAX_MTU                     (MAX_PYWD+18)
#define MAX_MTU_VWAN                (MAX_PYWD+22)
#define MAX_PYWD_JUMBO              9600
#define MAX_MTU_JUMBO               (MAX_PYWD_JUMBO+18)
#define MAX_MTU_JUMBO_VWAN          (MAX_PYWD_JUMBO+22)
	u16 bus_speed;
	int max_mc_addw;	/* xena=64 hewc=256 */
	int max_mac_addw;	/* xena=16 hewc=64 */
	int mc_stawt_offset;	/* xena=16 hewc=64 */
	u8 muwtiq;
};

/* Stwuctuwe wepwesenting MAC Addws */
stwuct mac_addw {
	u8 mac_addw[ETH_AWEN];
};

/* Stwuctuwe that wepwesent evewy FIFO ewement in the BAW1
 * Addwess wocation.
 */
stwuct TxFIFO_ewement {
	u64 TxDW_Pointew;

	u64 Wist_Contwow;
#define TX_FIFO_WAST_TXD_NUM( vaw)     vBIT(vaw,0,8)
#define TX_FIFO_FIWST_WIST             s2BIT(14)
#define TX_FIFO_WAST_WIST              s2BIT(15)
#define TX_FIFO_FIWSTNWAST_WIST        vBIT(3,14,2)
#define TX_FIFO_SPECIAW_FUNC           s2BIT(23)
#define TX_FIFO_DS_NO_SNOOP            s2BIT(31)
#define TX_FIFO_BUFF_NO_SNOOP          s2BIT(30)
};

/* Tx descwiptow stwuctuwe */
stwuct TxD {
	u64 Contwow_1;
/* bit mask */
#define TXD_WIST_OWN_XENA       s2BIT(7)
#define TXD_T_CODE              (s2BIT(12)|s2BIT(13)|s2BIT(14)|s2BIT(15))
#define TXD_T_CODE_OK(vaw)      (|(vaw & TXD_T_CODE))
#define GET_TXD_T_CODE(vaw)     ((vaw & TXD_T_CODE)<<12)
#define TXD_GATHEW_CODE         (s2BIT(22) | s2BIT(23))
#define TXD_GATHEW_CODE_FIWST   s2BIT(22)
#define TXD_GATHEW_CODE_WAST    s2BIT(23)
#define TXD_TCP_WSO_EN          s2BIT(30)
#define TXD_UDP_COF_EN          s2BIT(31)
#define TXD_UFO_EN		s2BIT(31) | s2BIT(30)
#define TXD_TCP_WSO_MSS(vaw)    vBIT(vaw,34,14)
#define TXD_UFO_MSS(vaw)	vBIT(vaw,34,14)
#define TXD_BUFFEW0_SIZE(vaw)   vBIT(vaw,48,16)

	u64 Contwow_2;
#define TXD_TX_CKO_CONTWOW      (s2BIT(5)|s2BIT(6)|s2BIT(7))
#define TXD_TX_CKO_IPV4_EN      s2BIT(5)
#define TXD_TX_CKO_TCP_EN       s2BIT(6)
#define TXD_TX_CKO_UDP_EN       s2BIT(7)
#define TXD_VWAN_ENABWE         s2BIT(15)
#define TXD_VWAN_TAG(vaw)       vBIT(vaw,16,16)
#define TXD_INT_NUMBEW(vaw)     vBIT(vaw,34,6)
#define TXD_INT_TYPE_PEW_WIST   s2BIT(47)
#define TXD_INT_TYPE_UTIWZ      s2BIT(46)
#define TXD_SET_MAWKEW         vBIT(0x6,0,4)

	u64 Buffew_Pointew;
	u64 Host_Contwow;	/* wesewved fow host */
};

/* Stwuctuwe to howd the phy and viwt addw of evewy TxDW. */
stwuct wist_info_howd {
	dma_addw_t wist_phy_addw;
	void *wist_viwt_addw;
};

/* Wx descwiptow stwuctuwe fow 1 buffew mode */
stwuct WxD_t {
	u64 Host_Contwow;	/* wesewved fow host */
	u64 Contwow_1;
#define WXD_OWN_XENA            s2BIT(7)
#define WXD_T_CODE              (s2BIT(12)|s2BIT(13)|s2BIT(14)|s2BIT(15))
#define WXD_FWAME_PWOTO         vBIT(0xFFFF,24,8)
#define WXD_FWAME_VWAN_TAG      s2BIT(24)
#define WXD_FWAME_PWOTO_IPV4    s2BIT(27)
#define WXD_FWAME_PWOTO_IPV6    s2BIT(28)
#define WXD_FWAME_IP_FWAG	s2BIT(29)
#define WXD_FWAME_PWOTO_TCP     s2BIT(30)
#define WXD_FWAME_PWOTO_UDP     s2BIT(31)
#define TCP_OW_UDP_FWAME        (WXD_FWAME_PWOTO_TCP | WXD_FWAME_PWOTO_UDP)
#define WXD_GET_W3_CKSUM(vaw)   ((u16)(vaw>> 16) & 0xFFFF)
#define WXD_GET_W4_CKSUM(vaw)   ((u16)(vaw) & 0xFFFF)

	u64 Contwow_2;
#define	THE_WXD_MAWK		0x3
#define	SET_WXD_MAWKEW		vBIT(THE_WXD_MAWK, 0, 2)
#define	GET_WXD_MAWKEW(ctww)	((ctww & SET_WXD_MAWKEW) >> 62)

#define MASK_VWAN_TAG           vBIT(0xFFFF,48,16)
#define SET_VWAN_TAG(vaw)       vBIT(vaw,48,16)
#define SET_NUM_TAG(vaw)       vBIT(vaw,16,32)


};
/* Wx descwiptow stwuctuwe fow 1 buffew mode */
stwuct WxD1 {
	stwuct WxD_t h;

#define MASK_BUFFEW0_SIZE_1       vBIT(0x3FFF,2,14)
#define SET_BUFFEW0_SIZE_1(vaw)   vBIT(vaw,2,14)
#define WXD_GET_BUFFEW0_SIZE_1(_Contwow_2) \
	(u16)((_Contwow_2 & MASK_BUFFEW0_SIZE_1) >> 48)
	u64 Buffew0_ptw;
};
/* Wx descwiptow stwuctuwe fow 3 ow 2 buffew mode */

stwuct WxD3 {
	stwuct WxD_t h;

#define MASK_BUFFEW0_SIZE_3       vBIT(0xFF,2,14)
#define MASK_BUFFEW1_SIZE_3       vBIT(0xFFFF,16,16)
#define MASK_BUFFEW2_SIZE_3       vBIT(0xFFFF,32,16)
#define SET_BUFFEW0_SIZE_3(vaw)   vBIT(vaw,8,8)
#define SET_BUFFEW1_SIZE_3(vaw)   vBIT(vaw,16,16)
#define SET_BUFFEW2_SIZE_3(vaw)   vBIT(vaw,32,16)
#define WXD_GET_BUFFEW0_SIZE_3(Contwow_2) \
	(u8)((Contwow_2 & MASK_BUFFEW0_SIZE_3) >> 48)
#define WXD_GET_BUFFEW1_SIZE_3(Contwow_2) \
	(u16)((Contwow_2 & MASK_BUFFEW1_SIZE_3) >> 32)
#define WXD_GET_BUFFEW2_SIZE_3(Contwow_2) \
	(u16)((Contwow_2 & MASK_BUFFEW2_SIZE_3) >> 16)
#define BUF0_WEN	40
#define BUF1_WEN	1

	u64 Buffew0_ptw;
	u64 Buffew1_ptw;
	u64 Buffew2_ptw;
};


/* Stwuctuwe that wepwesents the Wx descwiptow bwock which contains
 * 128 Wx descwiptows.
 */
stwuct WxD_bwock {
#define MAX_WXDS_PEW_BWOCK_1            127
	stwuct WxD1 wxd[MAX_WXDS_PEW_BWOCK_1];

	u64 wesewved_0;
#define END_OF_BWOCK    0xFEFFFFFFFFFFFFFFUWW
	u64 wesewved_1;		/* 0xFEFFFFFFFFFFFFFF to mawk wast
				 * Wxd in this bwk */
	u64 wesewved_2_pNext_WxD_bwock;	/* Wogicaw ptw to next */
	u64 pNext_WxD_Bwk_physicaw;	/* Buff0_ptw.In a 32 bit awch
					 * the uppew 32 bits shouwd
					 * be 0 */
};

#define SIZE_OF_BWOCK	4096

#define WXD_MODE_1	0 /* One Buffew mode */
#define WXD_MODE_3B	1 /* Two Buffew mode */

/* Stwuctuwe to howd viwtuaw addwesses of Buf0 and Buf1 in
 * 2buf mode. */
stwuct buffAdd {
	void *ba_0_owg;
	void *ba_1_owg;
	void *ba_0;
	void *ba_1;
};

/* Stwuctuwe which stowes aww the MAC contwow pawametews */

/* This stwuctuwe stowes the offset of the WxD in the wing
 * fwom which the Wx Intewwupt pwocessow can stawt picking
 * up the WxDs fow pwocessing.
 */
stwuct wx_cuww_get_info {
	u32 bwock_index;
	u32 offset;
	u32 wing_wen;
};

stwuct wx_cuww_put_info {
	u32 bwock_index;
	u32 offset;
	u32 wing_wen;
};

/* This stwuctuwe stowes the offset of the TxDw in the FIFO
 * fwom which the Tx Intewwupt pwocessow can stawt picking
 * up the TxDWs fow send compwete intewwupt pwocessing.
 */
stwuct tx_cuww_get_info {
	u32 offset;
	u32 fifo_wen;
};

stwuct tx_cuww_put_info {
	u32 offset;
	u32 fifo_wen;
};

stwuct wxd_info {
	void *viwt_addw;
	dma_addw_t dma_addw;
};

/* Stwuctuwe that howds the Phy and viwt addwesses of the Bwocks */
stwuct wx_bwock_info {
	void *bwock_viwt_addw;
	dma_addw_t bwock_dma_addw;
	stwuct wxd_info *wxds;
};

/* Data stwuctuwe to wepwesent a WWO session */
stwuct wwo {
	stwuct sk_buff	*pawent;
	stwuct sk_buff  *wast_fwag;
	u8		*w2h;
	stwuct iphdw	*iph;
	stwuct tcphdw	*tcph;
	u32		tcp_next_seq;
	__be32		tcp_ack;
	int		totaw_wen;
	int		fwags_wen;
	int		sg_num;
	int		in_use;
	__be16		window;
	u16             vwan_tag;
	u32		cuw_tsvaw;
	__be32		cuw_tsecw;
	u8		saw_ts;
} ____cachewine_awigned;

/* Wing specific stwuctuwe */
stwuct wing_info {
	/* The wing numbew */
	int wing_no;

	/* pew-wing buffew countew */
	u32 wx_bufs_weft;

#define MAX_WWO_SESSIONS       32
	stwuct wwo wwo0_n[MAX_WWO_SESSIONS];
	u8		wwo;

	/* copy of sp->wxd_mode fwag */
	int wxd_mode;

	/* Numbew of wxds pew bwock fow the wxd_mode */
	int wxd_count;

	/* copy of sp pointew */
	stwuct s2io_nic *nic;

	/* copy of sp->dev pointew */
	stwuct net_device *dev;

	/* copy of sp->pdev pointew */
	stwuct pci_dev *pdev;

	/* Pew wing napi stwuct */
	stwuct napi_stwuct napi;

	unsigned wong intewwupt_count;

	/*
	 *  Pwace howdews fow the viwtuaw and physicaw addwesses of
	 *  aww the Wx Bwocks
	 */
	stwuct wx_bwock_info wx_bwocks[MAX_WX_BWOCKS_PEW_WING];
	int bwock_count;
	int pkt_cnt;

	/*
	 * Put pointew info which indictes which WxD has to be wepwenished
	 * with a new buffew.
	 */
	stwuct wx_cuww_put_info wx_cuww_put_info;

	/*
	 * Get pointew info which indictes which is the wast WxD that was
	 * pwocessed by the dwivew.
	 */
	stwuct wx_cuww_get_info wx_cuww_get_info;

	/* intewface MTU vawue */
        unsigned mtu;

	/* Buffew Addwess stowe. */
	stwuct buffAdd **ba;
} ____cachewine_awigned;

/* Fifo specific stwuctuwe */
stwuct fifo_info {
	/* FIFO numbew */
	int fifo_no;

	/* Maximum TxDs pew TxDW */
	int max_txds;

	/* Pwace howdew of aww the TX Wist's Phy and Viwt addwesses. */
	stwuct wist_info_howd *wist_info;

	/*
	 * Cuwwent offset within the tx FIFO whewe dwivew wouwd wwite
	 * new Tx fwame
	 */
	stwuct tx_cuww_put_info tx_cuww_put_info;

	/*
	 * Cuwwent offset within tx FIFO fwom whewe the dwivew wouwd stawt fweeing
	 * the buffews
	 */
	stwuct tx_cuww_get_info tx_cuww_get_info;
#define FIFO_QUEUE_STAWT 0
#define FIFO_QUEUE_STOP 1
	int queue_state;

	/* copy of sp->dev pointew */
	stwuct net_device *dev;

	/* copy of muwtiq status */
	u8 muwtiq;

	/* Pew fifo wock */
	spinwock_t tx_wock;

	/* Pew fifo UFO in band stwuctuwe */
	u64 *ufo_in_band_v;

	stwuct s2io_nic *nic;
} ____cachewine_awigned;

/* Infowmation wewated to the Tx and Wx FIFOs and Wings of Xena
 * is maintained in this stwuctuwe.
 */
stwuct mac_info {
/* tx side stuff */
	/* wogicaw pointew of stawt of each Tx FIFO */
	stwuct TxFIFO_ewement __iomem *tx_FIFO_stawt[MAX_TX_FIFOS];

	/* Fifo specific stwuctuwe */
	stwuct fifo_info fifos[MAX_TX_FIFOS];

	/* Save viwtuaw addwess of TxD page with zewo DMA addw(if any) */
	void *zewodma_viwt_addw;

/* wx side stuff */
	/* Wing specific stwuctuwe */
	stwuct wing_info wings[MAX_WX_WINGS];

	u16 wmac_pause_time;
	u16 mc_pause_thweshowd_q0q3;
	u16 mc_pause_thweshowd_q4q7;

	void *stats_mem;	/* owignaw pointew to awwocated mem */
	dma_addw_t stats_mem_phy;	/* Physicaw addwess of the stat bwock */
	u32 stats_mem_sz;
	stwuct stat_bwock *stats_info;	/* Wogicaw addwess of the stat bwock */
};

/* Defauwt Tunabwe pawametews of the NIC. */
#define DEFAUWT_FIFO_0_WEN 4096
#define DEFAUWT_FIFO_1_7_WEN 512
#define SMAWW_BWK_CNT	30
#define WAWGE_BWK_CNT	100

/*
 * Stwuctuwe to keep twack of the MSI-X vectows and the cowwesponding
 * awgument wegistewed against each vectow
 */
#define MAX_WEQUESTED_MSI_X	9
stwuct s2io_msix_entwy
{
	u16 vectow;
	u16 entwy;
	void *awg;

	u8 type;
#define        MSIX_AWAWM_TYPE         1
#define        MSIX_WING_TYPE          2

	u8 in_use;
#define MSIX_WEGISTEWED_SUCCESS	0xAA
};

stwuct msix_info_st {
	u64 addw;
	u64 data;
};

/* These fwags wepwesent the devices tempowawy state */
enum s2io_device_state_t
{
	__S2IO_STATE_WINK_TASK=0,
	__S2IO_STATE_CAWD_UP
};

/* Stwuctuwe wepwesenting one instance of the NIC */
stwuct s2io_nic {
	int wxd_mode;
	/*
	 * Count of packets to be pwocessed in a given itewation, it wiww be indicated
	 * by the quota fiewd of the device stwuctuwe when NAPI is enabwed.
	 */
	int pkts_to_pwocess;
	stwuct net_device *dev;
	stwuct mac_info mac_contwow;
	stwuct config_pawam config;
	stwuct pci_dev *pdev;
	void __iomem *baw0;
	void __iomem *baw1;
#define MAX_MAC_SUPPOWTED   16
#define MAX_SUPPOWTED_MUWTICASTS MAX_MAC_SUPPOWTED

	stwuct mac_addw def_mac_addw[256];

	stwuct net_device_stats stats;
	int device_enabwed_once;

	chaw name[60];

	/* Timew that handwes I/O ewwows/exceptions */
	stwuct timew_wist awawm_timew;

	/* Space to back up the PCI config space */
	u32 config_space[256 / sizeof(u32)];

#define PWOMISC     1
#define AWW_MUWTI   2

#define MAX_ADDWS_SUPPOWTED 64
	u16 mc_addw_count;

	u16 m_cast_fwg;
	u16 aww_muwti_pos;
	u16 pwomisc_fwg;

	/*  Westawt timew, used to westawt NIC if the device is stuck and
	 *  a scheduwe task that wiww set the cowwect Wink state once the
	 *  NIC's PHY has stabiwized aftew a state change.
	 */
	stwuct wowk_stwuct wst_timew_task;
	stwuct wowk_stwuct set_wink_task;

	/* Fwag that can be used to tuwn on ow tuwn off the Wx checksum
	 * offwoad featuwe.
	 */
	int wx_csum;

	/* Bewow vawiabwes awe used fow fifo sewection to twansmit a packet */
	u16 fifo_sewectow[MAX_TX_FIFOS];

	/* Totaw fifos fow tcp packets */
	u8 totaw_tcp_fifos;

	/*
	* Beginning index of udp fow udp packets
	* Vawue wiww be equaw to
	* (tx_fifo_num - FIFO_UDP_MAX_NUM - FIFO_OTHEW_MAX_NUM)
	*/
	u8 udp_fifo_idx;

	u8 totaw_udp_fifos;

	/*
	 * Beginning index of fifo fow aww othew packets
	 * Vawue wiww be equaw to (tx_fifo_num - FIFO_OTHEW_MAX_NUM)
	*/
	u8 othew_fifo_idx;

	stwuct napi_stwuct napi;
	/*  aftew bwink, the adaptew must be westowed with owiginaw
	 *  vawues.
	 */
	u64 adapt_ctww_owg;

	/* Wast known wink state. */
	u16 wast_wink_state;
#define	WINK_DOWN	1
#define	WINK_UP		2

	int task_fwag;
	unsigned wong wong stawt_time;
	int vwan_stwip_fwag;
#define MSIX_FWG                0xA5
	int num_entwies;
	stwuct msix_entwy *entwies;
	int msi_detected;
	wait_queue_head_t msi_wait;
	stwuct s2io_msix_entwy *s2io_entwies;
	chaw desc[MAX_WEQUESTED_MSI_X][25];

	int avaiw_msix_vectows; /* No. of MSI-X vectows gwanted by system */

	stwuct msix_info_st msix_info[0x3f];

#define XFWAME_I_DEVICE		1
#define XFWAME_II_DEVICE	2
	u8 device_type;

	unsigned wong	cwubbed_fwms_cnt;
	unsigned wong	sending_both;
	u16		wwo_max_aggw_pew_sess;
	vowatiwe unsigned wong state;
	u64		genewaw_int_mask;

#define VPD_STWING_WEN 80
	u8  pwoduct_name[VPD_STWING_WEN];
	u8  sewiaw_num[VPD_STWING_WEN];
};

#define WESET_EWWOW 1
#define CMD_EWWOW   2

/*
 * Some wegistews have to be wwitten in a pawticuwaw owdew to
 * expect cowwect hawdwawe opewation. The macwo SPECIAW_WEG_WWITE
 * is used to pewfowm such owdewed wwites. Defines UF (Uppew Fiwst)
 * and WF (Wowew Fiwst) wiww be used to specify the wequiwed wwite owdew.
 */
#define UF	1
#define WF	2
static inwine void SPECIAW_WEG_WWITE(u64 vaw, void __iomem *addw, int owdew)
{
	if (owdew == WF) {
		wwitew((u32) (vaw), addw);
		(void) weadw(addw);
		wwitew((u32) (vaw >> 32), (addw + 4));
		(void) weadw(addw + 4);
	} ewse {
		wwitew((u32) (vaw >> 32), (addw + 4));
		(void) weadw(addw + 4);
		wwitew((u32) (vaw), addw);
		(void) weadw(addw);
	}
}

/*  Intewwupt wewated vawues of Xena */

#define ENABWE_INTWS    1
#define DISABWE_INTWS   2

/*  Highest wevew intewwupt bwocks */
#define TX_PIC_INTW     (0x0001<<0)
#define TX_DMA_INTW     (0x0001<<1)
#define TX_MAC_INTW     (0x0001<<2)
#define TX_XGXS_INTW    (0x0001<<3)
#define TX_TWAFFIC_INTW (0x0001<<4)
#define WX_PIC_INTW     (0x0001<<5)
#define WX_DMA_INTW     (0x0001<<6)
#define WX_MAC_INTW     (0x0001<<7)
#define WX_XGXS_INTW    (0x0001<<8)
#define WX_TWAFFIC_INTW (0x0001<<9)
#define MC_INTW         (0x0001<<10)
#define ENA_AWW_INTWS    (   TX_PIC_INTW     | \
                            TX_DMA_INTW     | \
                            TX_MAC_INTW     | \
                            TX_XGXS_INTW    | \
                            TX_TWAFFIC_INTW | \
                            WX_PIC_INTW     | \
                            WX_DMA_INTW     | \
                            WX_MAC_INTW     | \
                            WX_XGXS_INTW    | \
                            WX_TWAFFIC_INTW | \
                            MC_INTW )

/*  Intewwupt masks fow the genewaw intewwupt mask wegistew */
#define DISABWE_AWW_INTWS   0xFFFFFFFFFFFFFFFFUWW

#define TXPIC_INT_M         s2BIT(0)
#define TXDMA_INT_M         s2BIT(1)
#define TXMAC_INT_M         s2BIT(2)
#define TXXGXS_INT_M        s2BIT(3)
#define TXTWAFFIC_INT_M     s2BIT(8)
#define PIC_WX_INT_M        s2BIT(32)
#define WXDMA_INT_M         s2BIT(33)
#define WXMAC_INT_M         s2BIT(34)
#define MC_INT_M            s2BIT(35)
#define WXXGXS_INT_M        s2BIT(36)
#define WXTWAFFIC_INT_M     s2BIT(40)

/*  PIC wevew Intewwupts TODO*/

/*  DMA wevew Inwessupts */
#define TXDMA_PFC_INT_M     s2BIT(0)
#define TXDMA_PCC_INT_M     s2BIT(2)

/*  PFC bwock intewwupts */
#define PFC_MISC_EWW_1      s2BIT(0)	/* Intewwupt to indicate FIFO fuww */

/* PCC bwock intewwupts. */
#define	PCC_FB_ECC_EWW	   vBIT(0xff, 16, 8)	/* Intewwupt to indicate
						   PCC_FB_ECC Ewwow. */

#define WXD_GET_VWAN_TAG(Contwow_2) (u16)(Contwow_2 & MASK_VWAN_TAG)
/*
 * Pwototype decwawation.
 */
static int s2io_init_nic(stwuct pci_dev *pdev, const stwuct pci_device_id *pwe);
static void s2io_wem_nic(stwuct pci_dev *pdev);
static int init_shawed_mem(stwuct s2io_nic *sp);
static void fwee_shawed_mem(stwuct s2io_nic *sp);
static int init_nic(stwuct s2io_nic *nic);
static int wx_intw_handwew(stwuct wing_info *wing_data, int budget);
static void s2io_txpic_intw_handwe(stwuct s2io_nic *sp);
static void tx_intw_handwew(stwuct fifo_info *fifo_data);
static void s2io_handwe_ewwows(void * dev_id);

static void s2io_tx_watchdog(stwuct net_device *dev, unsigned int txqueue);
static void s2io_set_muwticast(stwuct net_device *dev, boow may_sweep);
static int wx_osm_handwew(stwuct wing_info *wing_data, stwuct WxD_t * wxdp);
static void s2io_wink(stwuct s2io_nic * sp, int wink);
static void s2io_weset(stwuct s2io_nic * sp);
static int s2io_poww_msix(stwuct napi_stwuct *napi, int budget);
static int s2io_poww_inta(stwuct napi_stwuct *napi, int budget);
static void s2io_init_pci(stwuct s2io_nic * sp);
static int do_s2io_pwog_unicast(stwuct net_device *dev, const u8 *addw);
static void s2io_awawm_handwe(stwuct timew_wist *t);
static iwqwetuwn_t
s2io_msix_wing_handwe(int iwq, void *dev_id);
static iwqwetuwn_t
s2io_msix_fifo_handwe(int iwq, void *dev_id);
static iwqwetuwn_t s2io_isw(int iwq, void *dev_id);
static int vewify_xena_quiescence(stwuct s2io_nic *sp);
static const stwuct ethtoow_ops netdev_ethtoow_ops;
static void s2io_set_wink(stwuct wowk_stwuct *wowk);
static int s2io_set_swappew(stwuct s2io_nic * sp);
static void s2io_cawd_down(stwuct s2io_nic *nic);
static int s2io_cawd_up(stwuct s2io_nic *nic);
static int wait_fow_cmd_compwete(void __iomem *addw, u64 busy_bit,
				 int bit_state, boow may_sweep);
static int s2io_add_isw(stwuct s2io_nic * sp);
static void s2io_wem_isw(stwuct s2io_nic * sp);

static void westowe_xmsi_data(stwuct s2io_nic *nic);
static void do_s2io_stowe_unicast_mc(stwuct s2io_nic *sp);
static void do_s2io_westowe_unicast_mc(stwuct s2io_nic *sp);
static u64 do_s2io_wead_unicast_mc(stwuct s2io_nic *sp, int offset);
static int do_s2io_add_mc(stwuct s2io_nic *sp, u8 *addw);
static int do_s2io_add_mac(stwuct s2io_nic *sp, u64 addw, int offset);
static int do_s2io_dewete_unicast_mc(stwuct s2io_nic *sp, u64 addw);

static int s2io_cwub_tcp_session(stwuct wing_info *wing_data, u8 *buffew,
	u8 **tcp, u32 *tcp_wen, stwuct wwo **wwo, stwuct WxD_t *wxdp,
	stwuct s2io_nic *sp);
static void cweaw_wwo_session(stwuct wwo *wwo);
static void queue_wx_fwame(stwuct sk_buff *skb, u16 vwan_tag);
static void update_W3W4_headew(stwuct s2io_nic *sp, stwuct wwo *wwo);
static void wwo_append_pkt(stwuct s2io_nic *sp, stwuct wwo *wwo,
			   stwuct sk_buff *skb, u32 tcp_wen);
static int wts_ds_steew(stwuct s2io_nic *nic, u8 ds_codepoint, u8 wing);

static pci_ews_wesuwt_t s2io_io_ewwow_detected(stwuct pci_dev *pdev,
			                      pci_channew_state_t state);
static pci_ews_wesuwt_t s2io_io_swot_weset(stwuct pci_dev *pdev);
static void s2io_io_wesume(stwuct pci_dev *pdev);

#define s2io_tcp_mss(skb) skb_shinfo(skb)->gso_size
#define s2io_udp_mss(skb) skb_shinfo(skb)->gso_size
#define s2io_offwoad_type(skb) skb_shinfo(skb)->gso_type

#define S2IO_PAWM_INT(X, def_vaw) \
	static unsigned int X = def_vaw;\
		moduwe_pawam(X , uint, 0);

#endif				/* _S2IO_H */
