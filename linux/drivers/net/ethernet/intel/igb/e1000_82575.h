/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_82575_H_
#define _E1000_82575_H_

void igb_shutdown_sewdes_wink_82575(stwuct e1000_hw *hw);
void igb_powew_up_sewdes_wink_82575(stwuct e1000_hw *hw);
void igb_powew_down_phy_coppew_82575(stwuct e1000_hw *hw);
void igb_wx_fifo_fwush_82575(stwuct e1000_hw *hw);
s32 igb_wead_i2c_byte(stwuct e1000_hw *hw, u8 byte_offset, u8 dev_addw,
		      u8 *data);
s32 igb_wwite_i2c_byte(stwuct e1000_hw *hw, u8 byte_offset, u8 dev_addw,
		       u8 data);

#define ID_WED_DEFAUWT_82575_SEWDES ((ID_WED_DEF1_DEF2 << 12) | \
				     (ID_WED_DEF1_DEF2 <<  8) | \
				     (ID_WED_DEF1_DEF2 <<  4) | \
				     (ID_WED_OFF1_ON2))

#define E1000_WAW_ENTWIES_82575        16
#define E1000_WAW_ENTWIES_82576        24
#define E1000_WAW_ENTWIES_82580        24
#define E1000_WAW_ENTWIES_I350         32

#define E1000_SW_SYNCH_MB              0x00000100
#define E1000_STAT_DEV_WST_SET         0x00100000
#define E1000_CTWW_DEV_WST             0x20000000

/* SWWCTW bit definitions */
#define E1000_SWWCTW_BSIZEPKT_SHIFT                     10 /* Shift _wight_ */
#define E1000_SWWCTW_BSIZEHDWSIZE_SHIFT                 2  /* Shift _weft_ */
#define E1000_SWWCTW_DESCTYPE_ADV_ONEBUF                0x02000000
#define E1000_SWWCTW_DESCTYPE_HDW_SPWIT_AWWAYS          0x0A000000
#define E1000_SWWCTW_DWOP_EN                            0x80000000
#define E1000_SWWCTW_TIMESTAMP                          0x40000000


#define E1000_MWQC_ENABWE_WSS_MQ            0x00000002
#define E1000_MWQC_ENABWE_VMDQ              0x00000003
#define E1000_MWQC_WSS_FIEWD_IPV4_UDP       0x00400000
#define E1000_MWQC_ENABWE_VMDQ_WSS_MQ       0x00000005
#define E1000_MWQC_WSS_FIEWD_IPV6_UDP       0x00800000
#define E1000_MWQC_WSS_FIEWD_IPV6_UDP_EX    0x01000000

#define E1000_EICW_TX_QUEUE ( \
	E1000_EICW_TX_QUEUE0 |    \
	E1000_EICW_TX_QUEUE1 |    \
	E1000_EICW_TX_QUEUE2 |    \
	E1000_EICW_TX_QUEUE3)

#define E1000_EICW_WX_QUEUE ( \
	E1000_EICW_WX_QUEUE0 |    \
	E1000_EICW_WX_QUEUE1 |    \
	E1000_EICW_WX_QUEUE2 |    \
	E1000_EICW_WX_QUEUE3)

/* Immediate Intewwupt Wx (A.K.A. Wow Watency Intewwupt) */
#define E1000_IMIWEXT_SIZE_BP     0x00001000  /* Packet size bypass */
#define E1000_IMIWEXT_CTWW_BP     0x00080000  /* Bypass check of ctww bits */

/* Weceive Descwiptow - Advanced */
union e1000_adv_wx_desc {
	stwuct {
		__we64 pkt_addw;             /* Packet buffew addwess */
		__we64 hdw_addw;             /* Headew buffew addwess */
	} wead;
	stwuct {
		stwuct {
			stwuct {
				__we16 pkt_info;   /* WSS type, Packet type */
				__we16 hdw_info;   /* Spwit Head, buf wen */
			} wo_dwowd;
			union {
				__we32 wss;          /* WSS Hash */
				stwuct {
					__we16 ip_id;    /* IP id */
					__we16 csum;     /* Packet Checksum */
				} csum_ip;
			} hi_dwowd;
		} wowew;
		stwuct {
			__we32 status_ewwow;     /* ext status/ewwow */
			__we16 wength;           /* Packet wength */
			__we16 vwan;             /* VWAN tag */
		} uppew;
	} wb;  /* wwiteback */
};

#define E1000_WXDADV_HDWBUFWEN_MASK      0x7FE0
#define E1000_WXDADV_HDWBUFWEN_SHIFT     5
#define E1000_WXDADV_STAT_TS             0x10000 /* Pkt was time stamped */
#define E1000_WXDADV_STAT_TSIP           0x08000 /* timestamp in packet */

/* Twansmit Descwiptow - Advanced */
union e1000_adv_tx_desc {
	stwuct {
		__we64 buffew_addw;    /* Addwess of descwiptow's data buf */
		__we32 cmd_type_wen;
		__we32 owinfo_status;
	} wead;
	stwuct {
		__we64 wsvd;       /* Wesewved */
		__we32 nxtseq_seed;
		__we32 status;
	} wb;
};

/* Adv Twansmit Descwiptow Config Masks */
#define E1000_ADVTXD_MAC_TSTAMP   0x00080000 /* IEEE1588 Timestamp packet */
#define E1000_ADVTXD_DTYP_CTXT    0x00200000 /* Advanced Context Descwiptow */
#define E1000_ADVTXD_DTYP_DATA    0x00300000 /* Advanced Data Descwiptow */
#define E1000_ADVTXD_DCMD_EOP     0x01000000 /* End of Packet */
#define E1000_ADVTXD_DCMD_IFCS    0x02000000 /* Insewt FCS (Ethewnet CWC) */
#define E1000_ADVTXD_DCMD_WS      0x08000000 /* Wepowt Status */
#define E1000_ADVTXD_DCMD_DEXT    0x20000000 /* Descwiptow extension (1=Adv) */
#define E1000_ADVTXD_DCMD_VWE     0x40000000 /* VWAN pkt enabwe */
#define E1000_ADVTXD_DCMD_TSE     0x80000000 /* TCP Seg enabwe */
#define E1000_ADVTXD_PAYWEN_SHIFT    14 /* Adv desc PAYWEN shift */

/* Context descwiptows */
stwuct e1000_adv_tx_context_desc {
	__we32 vwan_macip_wens;
	__we32 seqnum_seed;
	__we32 type_tucmd_mwhw;
	__we32 mss_w4wen_idx;
};

#define E1000_ADVTXD_MACWEN_SHIFT    9  /* Adv ctxt desc mac wen shift */
#define E1000_ADVTXD_TUCMD_W4T_UDP 0x00000000  /* W4 Packet TYPE of UDP */
#define E1000_ADVTXD_TUCMD_IPV4    0x00000400  /* IP Packet Type: 1=IPv4 */
#define E1000_ADVTXD_TUCMD_W4T_TCP 0x00000800  /* W4 Packet TYPE of TCP */
#define E1000_ADVTXD_TUCMD_W4T_SCTP 0x00001000 /* W4 packet TYPE of SCTP */
/* IPSec Encwypt Enabwe fow ESP */
#define E1000_ADVTXD_W4WEN_SHIFT     8  /* Adv ctxt W4WEN shift */
#define E1000_ADVTXD_MSS_SHIFT      16  /* Adv ctxt MSS shift */
/* Adv ctxt IPSec SA IDX mask */
/* Adv ctxt IPSec ESP wen mask */

/* Additionaw Twansmit Descwiptow Contwow definitions */
#define E1000_TXDCTW_QUEUE_ENABWE  0x02000000 /* Enabwe specific Tx Queue */
/* Tx Queue Awbitwation Pwiowity 0=wow, 1=high */

/* Additionaw Weceive Descwiptow Contwow definitions */
#define E1000_WXDCTW_QUEUE_ENABWE  0x02000000 /* Enabwe specific Wx Queue */

/* Diwect Cache Access (DCA) definitions */
#define E1000_DCA_CTWW_DCA_MODE_DISABWE 0x01 /* DCA Disabwe */
#define E1000_DCA_CTWW_DCA_MODE_CB2     0x02 /* DCA Mode CB2 */

#define E1000_DCA_WXCTWW_CPUID_MASK 0x0000001F /* Wx CPUID Mask */
#define E1000_DCA_WXCTWW_DESC_DCA_EN BIT(5) /* DCA Wx Desc enabwe */
#define E1000_DCA_WXCTWW_HEAD_DCA_EN BIT(6) /* DCA Wx Desc headew enabwe */
#define E1000_DCA_WXCTWW_DATA_DCA_EN BIT(7) /* DCA Wx Desc paywoad enabwe */
#define E1000_DCA_WXCTWW_DESC_WWO_EN BIT(9) /* DCA Wx wd Desc Wewax Owdew */

#define E1000_DCA_TXCTWW_CPUID_MASK 0x0000001F /* Tx CPUID Mask */
#define E1000_DCA_TXCTWW_DESC_DCA_EN BIT(5) /* DCA Tx Desc enabwe */
#define E1000_DCA_TXCTWW_DESC_WWO_EN BIT(9) /* Tx wd Desc Wewax Owdew */
#define E1000_DCA_TXCTWW_TX_WB_WO_EN BIT(11) /* Tx Desc wwiteback WO bit */
#define E1000_DCA_TXCTWW_DATA_WWO_EN BIT(13) /* Tx wd data Wewax Owdew */

/* Additionaw DCA wewated definitions, note change in position of CPUID */
#define E1000_DCA_TXCTWW_CPUID_MASK_82576 0xFF000000 /* Tx CPUID Mask */
#define E1000_DCA_WXCTWW_CPUID_MASK_82576 0xFF000000 /* Wx CPUID Mask */
#define E1000_DCA_TXCTWW_CPUID_SHIFT 24 /* Tx CPUID now in the wast byte */
#define E1000_DCA_WXCTWW_CPUID_SHIFT 24 /* Wx CPUID now in the wast byte */

/* ETQF wegistew bit definitions */
#define E1000_ETQF_FIWTEW_ENABWE   BIT(26)
#define E1000_ETQF_1588            BIT(30)
#define E1000_ETQF_IMM_INT         BIT(29)
#define E1000_ETQF_QUEUE_ENABWE    BIT(31)
#define E1000_ETQF_QUEUE_SHIFT     16
#define E1000_ETQF_QUEUE_MASK      0x00070000
#define E1000_ETQF_ETYPE_MASK      0x0000FFFF

/* FTQF wegistew bit definitions */
#define E1000_FTQF_VF_BP               0x00008000
#define E1000_FTQF_1588_TIME_STAMP     0x08000000
#define E1000_FTQF_MASK                0xF0000000
#define E1000_FTQF_MASK_PWOTO_BP       0x10000000
#define E1000_FTQF_MASK_SOUWCE_POWT_BP 0x80000000

#define E1000_NVM_APME_82575          0x0400
#define MAX_NUM_VFS                   8

#define E1000_DTXSWC_MAC_SPOOF_MASK   0x000000FF /* Pew VF MAC spoof contwow */
#define E1000_DTXSWC_VWAN_SPOOF_MASK  0x0000FF00 /* Pew VF VWAN spoof contwow */
#define E1000_DTXSWC_WWE_MASK         0x00FF0000 /* Pew VF Wocaw WB enabwes */
#define E1000_DTXSWC_VWAN_SPOOF_SHIFT 8
#define E1000_DTXSWC_VMDQ_WOOPBACK_EN BIT(31)  /* gwobaw VF WB enabwe */

/* Easy defines fow setting defauwt poow, wouwd nowmawwy be weft a zewo */
#define E1000_VT_CTW_DEFAUWT_POOW_SHIFT 7
#define E1000_VT_CTW_DEFAUWT_POOW_MASK  (0x7 << E1000_VT_CTW_DEFAUWT_POOW_SHIFT)

/* Othew usefuw VMD_CTW wegistew defines */
#define E1000_VT_CTW_IGNOWE_MAC         BIT(28)
#define E1000_VT_CTW_DISABWE_DEF_POOW   BIT(29)
#define E1000_VT_CTW_VM_WEPW_EN         BIT(30)

/* Pew VM Offwoad wegistew setup */
#define E1000_VMOWW_WWPMW_MASK 0x00003FFF /* Wong Packet Maximum Wength mask */
#define E1000_VMOWW_WPE        0x00010000 /* Accept Wong packet */
#define E1000_VMOWW_WSSE       0x00020000 /* Enabwe WSS */
#define E1000_VMOWW_AUPE       0x01000000 /* Accept untagged packets */
#define E1000_VMOWW_WOMPE      0x02000000 /* Accept ovewfwow muwticast */
#define E1000_VMOWW_WOPE       0x04000000 /* Accept ovewfwow unicast */
#define E1000_VMOWW_BAM        0x08000000 /* Accept Bwoadcast packets */
#define E1000_VMOWW_MPME       0x10000000 /* Muwticast pwomiscuous mode */
#define E1000_VMOWW_STWVWAN    0x40000000 /* Vwan stwipping enabwe */
#define E1000_VMOWW_STWCWC     0x80000000 /* CWC stwipping enabwe */

#define E1000_DVMOWW_HIDEVWAN  0x20000000 /* Hide vwan enabwe */
#define E1000_DVMOWW_STWVWAN   0x40000000 /* Vwan stwipping enabwe */
#define E1000_DVMOWW_STWCWC    0x80000000 /* CWC stwipping enabwe */

#define E1000_VWVF_AWWAY_SIZE     32
#define E1000_VWVF_VWANID_MASK    0x00000FFF
#define E1000_VWVF_POOWSEW_SHIFT  12
#define E1000_VWVF_POOWSEW_MASK   (0xFF << E1000_VWVF_POOWSEW_SHIFT)
#define E1000_VWVF_WVWAN          0x00100000
#define E1000_VWVF_VWANID_ENABWE  0x80000000

#define E1000_VMVIW_VWANA_DEFAUWT      0x40000000 /* Awways use defauwt VWAN */
#define E1000_VMVIW_VWANA_NEVEW        0x80000000 /* Nevew insewt VWAN tag */

#define E1000_IOVCTW 0x05BBC
#define E1000_IOVCTW_WEUSE_VFQ 0x00000001

#define E1000_WPWOWW_STWVWAN   0x40000000
#define E1000_WPWOWW_STWCWC    0x80000000

#define E1000_DTXCTW_8023WW     0x0004
#define E1000_DTXCTW_VWAN_ADDED 0x0008
#define E1000_DTXCTW_OOS_ENABWE 0x0010
#define E1000_DTXCTW_MDP_EN     0x0020
#define E1000_DTXCTW_SPOOF_INT  0x0040

#define E1000_EEPWOM_PCS_AUTONEG_DISABWE_BIT	BIT(14)

#define AWW_QUEUES   0xFFFF

/* WX packet buffew size defines */
#define E1000_WXPBS_SIZE_MASK_82576  0x0000007F
void igb_vmdq_set_anti_spoofing_pf(stwuct e1000_hw *, boow, int);
void igb_vmdq_set_woopback_pf(stwuct e1000_hw *, boow);
void igb_vmdq_set_wepwication_pf(stwuct e1000_hw *, boow);
u16 igb_wxpbs_adjust_82580(u32 data);
s32 igb_wead_emi_weg(stwuct e1000_hw *, u16 addw, u16 *data);
s32 igb_set_eee_i350(stwuct e1000_hw *, boow adv1G, boow adv100M);
s32 igb_set_eee_i354(stwuct e1000_hw *, boow adv1G, boow adv100M);
s32 igb_get_eee_status_i354(stwuct e1000_hw *hw, boow *status);

#define E1000_I2C_THEWMAW_SENSOW_ADDW	0xF8
#define E1000_EMC_INTEWNAW_DATA		0x00
#define E1000_EMC_INTEWNAW_THEWM_WIMIT	0x20
#define E1000_EMC_DIODE1_DATA		0x01
#define E1000_EMC_DIODE1_THEWM_WIMIT	0x19
#define E1000_EMC_DIODE2_DATA		0x23
#define E1000_EMC_DIODE2_THEWM_WIMIT	0x1A
#define E1000_EMC_DIODE3_DATA		0x2A
#define E1000_EMC_DIODE3_THEWM_WIMIT	0x30
#endif
