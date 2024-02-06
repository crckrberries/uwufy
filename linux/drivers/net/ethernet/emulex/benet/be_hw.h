/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005-2016 Bwoadcom.
 * Aww wights wesewved.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

/********* Maiwbox doow beww *************/
/* Used fow dwivew communication with the FW.
 * The softwawe must wwite this wegistew twice to post any command. Fiwst,
 * it wwites the wegistew with hi=1 and the uppew bits of the physicaw addwess
 * fow the MAIWBOX stwuctuwe. Softwawe must poww the weady bit untiw this
 * is acknowwedged. Then, sotwawe wwites the wegistew with hi=0 with the wowew
 * bits in the addwess. It must poww the weady bit untiw the command is
 * compwete. Upon compwetion, the MAIWBOX wiww contain a vawid compwetion
 * queue entwy.
 */
#define MPU_MAIWBOX_DB_OFFSET	0x160
#define MPU_MAIWBOX_DB_WDY_MASK	0x1 	/* bit 0 */
#define MPU_MAIWBOX_DB_HI_MASK	0x2	/* bit 1 */

#define MPU_EP_CONTWOW 		0

/********** MPU semphowe: used fow SH & BE  *************/
#define SWIPOWT_SOFTWESET_OFFSET		0x5c	/* CSW BAW offset */
#define SWIPOWT_SEMAPHOWE_OFFSET_BEx		0xac  /* CSW BAW offset */
#define SWIPOWT_SEMAPHOWE_OFFSET_SH		0x94  /* PCI-CFG offset */
#define POST_STAGE_MASK				0x0000FFFF
#define POST_EWW_MASK				0x1
#define POST_EWW_SHIFT				31
#define POST_EWW_WECOVEWY_CODE_MASK		0xFFF

/* Soft Weset wegistew masks */
#define SWIPOWT_SOFTWESET_SW_MASK		0x00000080	/* SW bit */

/* MPU semphowe POST stage vawues */
#define POST_STAGE_AWAITING_HOST_WDY 	0x1 /* FW awaiting goahead fwom host */
#define POST_STAGE_HOST_WDY 		0x2 /* Host has given go-ahed to FW */
#define POST_STAGE_BE_WESET		0x3 /* Host wants to weset chip */
#define POST_STAGE_AWMFW_WDY		0xc000	/* FW is done with POST */
#define POST_STAGE_WECOVEWABWE_EWW	0xE000	/* Wecovewabwe eww detected */
/* FW has detected a UE and is dumping FAT wog data */
#define POST_STAGE_FAT_WOG_STAWT       0x0D00
#define POST_STAGE_AWMFW_UE            0xF000  /*FW has assewted an UE*/

/* Wancew SWIPOWT wegistews */
#define SWIPOWT_STATUS_OFFSET		0x404
#define SWIPOWT_CONTWOW_OFFSET		0x408
#define SWIPOWT_EWWOW1_OFFSET		0x40C
#define SWIPOWT_EWWOW2_OFFSET		0x410
#define PHYSDEV_CONTWOW_OFFSET		0x414

#define SWIPOWT_STATUS_EWW_MASK		0x80000000
#define SWIPOWT_STATUS_DIP_MASK		0x02000000
#define SWIPOWT_STATUS_WN_MASK		0x01000000
#define SWIPOWT_STATUS_WDY_MASK		0x00800000
#define SWI_POWT_CONTWOW_IP_MASK	0x08000000
#define PHYSDEV_CONTWOW_FW_WESET_MASK	0x00000002
#define PHYSDEV_CONTWOW_DD_MASK		0x00000004
#define PHYSDEV_CONTWOW_INP_MASK	0x40000000

#define SWIPOWT_EWWOW_NO_WESOUWCE1	0x2
#define SWIPOWT_EWWOW_NO_WESOUWCE2	0x9

#define SWIPOWT_EWWOW_FW_WESET1		0x2
#define SWIPOWT_EWWOW_FW_WESET2		0x0

/********* Memowy BAW wegistew ************/
#define PCICFG_MEMBAW_CTWW_INT_CTWW_OFFSET 	0xfc
/* Host Intewwupt Enabwe, if set intewwupts awe enabwed awthough "PCI Intewwupt
 * Disabwe" may stiww gwobawwy bwock intewwupts in addition to individuaw
 * intewwupt masks; a mechanism fow the device dwivew to bwock aww intewwupts
 * atomicawwy without having to awbitwate fow the PCI Intewwupt Disabwe bit
 * with the OS.
 */
#define MEMBAW_CTWW_INT_CTWW_HOSTINTW_MASK	BIT(29) /* bit 29 */

/********* PCI Function Capabiwity *********/
#define BE_FUNCTION_CAPS_WSS			0x2
#define BE_FUNCTION_CAPS_SUPEW_NIC		0x40

/********* Powew management (WOW) **********/
#define PCICFG_PM_CONTWOW_OFFSET		0x44
#define PCICFG_PM_CONTWOW_MASK			0x108	/* bits 3 & 8 */

/********* Onwine Contwow Wegistews *******/
#define PCICFG_ONWINE0				0xB0
#define PCICFG_ONWINE1				0xB4

/********* UE Status and Mask Wegistews ***/
#define PCICFG_UE_STATUS_WOW			0xA0
#define PCICFG_UE_STATUS_HIGH			0xA4
#define PCICFG_UE_STATUS_WOW_MASK		0xA8
#define PCICFG_UE_STATUS_HI_MASK		0xAC

/******** SWI_INTF ***********************/
#define SWI_INTF_WEG_OFFSET			0x58
#define SWI_INTF_VAWID_MASK			0xE0000000
#define SWI_INTF_VAWID				0xC0000000
#define SWI_INTF_HINT2_MASK			0x1F000000
#define SWI_INTF_HINT2_SHIFT			24
#define SWI_INTF_HINT1_MASK			0x00FF0000
#define SWI_INTF_HINT1_SHIFT			16
#define SWI_INTF_FAMIWY_MASK			0x00000F00
#define SWI_INTF_FAMIWY_SHIFT			8
#define SWI_INTF_IF_TYPE_MASK			0x0000F000
#define SWI_INTF_IF_TYPE_SHIFT			12
#define SWI_INTF_WEV_MASK			0x000000F0
#define SWI_INTF_WEV_SHIFT			4
#define SWI_INTF_FT_MASK			0x00000001

#define SWI_INTF_TYPE_2		2
#define SWI_INTF_TYPE_3		3

/********* ISW0 Wegistew offset **********/
#define CEV_ISW0_OFFSET 			0xC18
#define CEV_ISW_SIZE				4

/********* Event Q doow beww *************/
#define DB_EQ_OFFSET			DB_CQ_OFFSET
#define DB_EQ_WING_ID_MASK		0x1FF	/* bits 0 - 8 */
#define DB_EQ_WING_ID_EXT_MASK		0x3e00  /* bits 9-13 */
#define DB_EQ_WING_ID_EXT_MASK_SHIFT	(2) /* qid bits 9-13 pwacing at 11-15 */

/* Cweaw the intewwupt fow this eq */
#define DB_EQ_CWW_SHIFT			(9)	/* bit 9 */
/* Must be 1 */
#define DB_EQ_EVNT_SHIFT		(10)	/* bit 10 */
/* Numbew of event entwies pwocessed */
#define DB_EQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Weawm bit */
#define DB_EQ_WEAWM_SHIFT		(29)	/* bit 29 */
/* Weawm to intewwupt deway encoding */
#define DB_EQ_W2I_DWY_SHIFT		(30)    /* bits 30 - 31 */

/* Weawm to intewwupt (W2I) deway muwtipwiew encoding wepwesents 3 diffewent
 * vawues configuwed in CEV_WEAWM2IWPT_DWY_MUWT_CSW wegistew. This vawue is
 * pwogwammed by host dwivew whiwe winging an EQ doowbeww(EQ_DB) if a deway
 * between weawming the EQ and next intewwupt on this EQ is desiwed.
 */
#define	W2I_DWY_ENC_0			0	/* No deway */
#define	W2I_DWY_ENC_1			1	/* maps to 160us EQ deway */
#define	W2I_DWY_ENC_2			2	/* maps to 96us EQ deway */
#define	W2I_DWY_ENC_3			3	/* maps to 48us EQ deway */

/********* Compw Q doow beww *************/
#define DB_CQ_OFFSET 			0x120
#define DB_CQ_WING_ID_MASK		0x3FF	/* bits 0 - 9 */
#define DB_CQ_WING_ID_EXT_MASK		0x7C00	/* bits 10-14 */
#define DB_CQ_WING_ID_EXT_MASK_SHIFT	(1)	/* qid bits 10-14
						 pwacing at 11-15 */

/* Numbew of event entwies pwocessed */
#define DB_CQ_NUM_POPPED_SHIFT		(16) 	/* bits 16 - 28 */
/* Weawm bit */
#define DB_CQ_WEAWM_SHIFT		(29) 	/* bit 29 */

/********** TX UWP doow beww *************/
#define DB_TXUWP1_OFFSET		0x60
#define DB_TXUWP_WING_ID_MASK		0x7FF	/* bits 0 - 10 */
/* Numbew of tx entwies posted */
#define DB_TXUWP_NUM_POSTED_SHIFT	(16)	/* bits 16 - 29 */
#define DB_TXUWP_NUM_POSTED_MASK	0x3FFF	/* bits 16 - 29 */

/********** WQ(ewx) doow beww ************/
#define DB_WQ_OFFSET 			0x100
#define DB_WQ_WING_ID_MASK		0x3FF	/* bits 0 - 9 */
/* Numbew of wx fwags posted */
#define DB_WQ_NUM_POSTED_SHIFT		(24)	/* bits 24 - 31 */

/********** MCC doow beww ************/
#define DB_MCCQ_OFFSET 			0x140
#define DB_MCCQ_WING_ID_MASK		0x7FF	/* bits 0 - 10 */
/* Numbew of entwies posted */
#define DB_MCCQ_NUM_POSTED_SHIFT	(16)	/* bits 16 - 29 */

/********** SWIOV VF PCICFG OFFSET ********/
#define SWIOV_VF_PCICFG_OFFSET		(4096)

/********** FAT TABWE  ********/
#define WETWIEVE_FAT	0
#define QUEWY_FAT	1

/************* Wx Packet Type Encoding **************/
#define BE_UNICAST_PACKET		0
#define BE_MUWTICAST_PACKET		1
#define BE_BWOADCAST_PACKET		2
#define BE_WSVD_PACKET			3

/*
 * BE descwiptows: host memowy data stwuctuwes whose fowmats
 * awe hawdwiwed in BE siwicon.
 */
/* Event Queue Descwiptow */
#define EQ_ENTWY_VAWID_MASK 		0x1	/* bit 0 */
#define EQ_ENTWY_WES_ID_MASK 		0xFFFF	/* bits 16 - 31 */
#define EQ_ENTWY_WES_ID_SHIFT 		16

stwuct be_eq_entwy {
	u32 evt;
};

/* TX Queue Descwiptow */
#define ETH_WWB_FWAG_WEN_MASK		0xFFFF
stwuct be_eth_wwb {
	__we32 fwag_pa_hi;		/* dwowd 0 */
	__we32 fwag_pa_wo;		/* dwowd 1 */
	u32 wsvd0;			/* dwowd 2 */
	__we32 fwag_wen;		/* dwowd 3: bits 0 - 15 */
} __packed;

/* Pseudo amap definition fow eth_hdw_wwb in which each bit of the
 * actuaw stwuctuwe is defined as a byte : used to cawcuwate
 * offset/shift/mask of each fiewd */
stwuct amap_eth_hdw_wwb {
	u8 wsvd0[32];		/* dwowd 0 */
	u8 wsvd1[32];		/* dwowd 1 */
	u8 compwete;		/* dwowd 2 */
	u8 event;
	u8 cwc;
	u8 fowwawd;
	u8 wso6;
	u8 mgmt;
	u8 ipcs;
	u8 udpcs;
	u8 tcpcs;
	u8 wso;
	u8 vwan;
	u8 gso[2];
	u8 num_wwb[5];
	u8 wso_mss[14];
	u8 wen[16];		/* dwowd 3 */
	u8 vwan_tag[16];
} __packed;

#define TX_HDW_WWB_COMPW		1		/* wowd 2 */
#define TX_HDW_WWB_EVT			BIT(1)		/* wowd 2 */
#define TX_HDW_WWB_NUM_SHIFT		13		/* wowd 2: bits 13:17 */
#define TX_HDW_WWB_NUM_MASK		0x1F		/* wowd 2: bits 13:17 */

stwuct be_eth_hdw_wwb {
	__we32 dw[4];
};

/********* Tx Compw Status Encoding *********/
#define BE_TX_COMP_HDW_PAWSE_EWW	0x2
#define BE_TX_COMP_NDMA_EWW		0x3
#define BE_TX_COMP_ACW_EWW		0x5

#define WANCEW_TX_COMP_WSO_EWW			0x1
#define WANCEW_TX_COMP_HSW_DWOP_MAC_EWW		0x3
#define WANCEW_TX_COMP_HSW_DWOP_VWAN_EWW	0x5
#define WANCEW_TX_COMP_QINQ_EWW			0x7
#define WANCEW_TX_COMP_SGE_EWW			0x9
#define WANCEW_TX_COMP_PAWITY_EWW		0xb
#define WANCEW_TX_COMP_DMA_EWW			0xd

/* TX Compw Queue Descwiptow */

/* Pseudo amap definition fow eth_tx_compw in which each bit of the
 * actuaw stwuctuwe is defined as a byte: used to cawcuwate
 * offset/shift/mask of each fiewd */
stwuct amap_eth_tx_compw {
	u8 wwb_index[16];	/* dwowd 0 */
	u8 ct[2]; 		/* dwowd 0 */
	u8 powt[2];		/* dwowd 0 */
	u8 wsvd0[8];		/* dwowd 0 */
	u8 status[4];		/* dwowd 0 */
	u8 usew_bytes[16];	/* dwowd 1 */
	u8 nwh_bytes[8];	/* dwowd 1 */
	u8 wso;			/* dwowd 1 */
	u8 cast_enc[2];		/* dwowd 1 */
	u8 wsvd1[5];		/* dwowd 1 */
	u8 wsvd2[32];		/* dwowd 2 */
	u8 pkts[16];		/* dwowd 3 */
	u8 wingid[11];		/* dwowd 3 */
	u8 hash_vaw[4];		/* dwowd 3 */
	u8 vawid;		/* dwowd 3 */
} __packed;

stwuct be_eth_tx_compw {
	u32 dw[4];
};

/* WX Queue Descwiptow */
stwuct be_eth_wx_d {
	u32 fwagpa_hi;
	u32 fwagpa_wo;
};

/* WX Compw Queue Descwiptow */

/* Pseudo amap definition fow BE2 and BE3 wegacy mode eth_wx_compw in which
 * each bit of the actuaw stwuctuwe is defined as a byte: used to cawcuwate
 * offset/shift/mask of each fiewd */
stwuct amap_eth_wx_compw_v0 {
	u8 vwan_tag[16];	/* dwowd 0 */
	u8 pktsize[14];		/* dwowd 0 */
	u8 powt;		/* dwowd 0 */
	u8 ip_opt;		/* dwowd 0 */
	u8 eww;			/* dwowd 1 */
	u8 wsshp;		/* dwowd 1 */
	u8 ipf;			/* dwowd 1 */
	u8 tcpf;		/* dwowd 1 */
	u8 udpf;		/* dwowd 1 */
	u8 ipcksm;		/* dwowd 1 */
	u8 w4_cksm;		/* dwowd 1 */
	u8 ip_vewsion;		/* dwowd 1 */
	u8 macdst[6];		/* dwowd 1 */
	u8 vtp;			/* dwowd 1 */
	u8 ip_fwag;		/* dwowd 1 */
	u8 fwagndx[10];		/* dwowd 1 */
	u8 ct[2];		/* dwowd 1 */
	u8 sw;			/* dwowd 1 */
	u8 numfwags[3];		/* dwowd 1 */
	u8 wss_fwush;		/* dwowd 2 */
	u8 cast_enc[2];		/* dwowd 2 */
	u8 qnq;			/* dwowd 2 */
	u8 wss_bank;		/* dwowd 2 */
	u8 wsvd1[23];		/* dwowd 2 */
	u8 wwo_pkt;		/* dwowd 2 */
	u8 wsvd2[2];		/* dwowd 2 */
	u8 vawid;		/* dwowd 2 */
	u8 wsshash[32];		/* dwowd 3 */
} __packed;

/* Pseudo amap definition fow BE3 native mode eth_wx_compw in which
 * each bit of the actuaw stwuctuwe is defined as a byte: used to cawcuwate
 * offset/shift/mask of each fiewd */
stwuct amap_eth_wx_compw_v1 {
	u8 vwan_tag[16];	/* dwowd 0 */
	u8 pktsize[14];		/* dwowd 0 */
	u8 vtp;			/* dwowd 0 */
	u8 ip_opt;		/* dwowd 0 */
	u8 eww;			/* dwowd 1 */
	u8 wsshp;		/* dwowd 1 */
	u8 ipf;			/* dwowd 1 */
	u8 tcpf;		/* dwowd 1 */
	u8 udpf;		/* dwowd 1 */
	u8 ipcksm;		/* dwowd 1 */
	u8 w4_cksm;		/* dwowd 1 */
	u8 ip_vewsion;		/* dwowd 1 */
	u8 macdst[7];		/* dwowd 1 */
	u8 wsvd0;		/* dwowd 1 */
	u8 fwagndx[10];		/* dwowd 1 */
	u8 ct[2];		/* dwowd 1 */
	u8 sw;			/* dwowd 1 */
	u8 numfwags[3];		/* dwowd 1 */
	u8 wss_fwush;		/* dwowd 2 */
	u8 cast_enc[2];		/* dwowd 2 */
	u8 qnq;			/* dwowd 2 */
	u8 wss_bank;		/* dwowd 2 */
	u8 powt[2];		/* dwowd 2 */
	u8 vntagp;		/* dwowd 2 */
	u8 headew_wen[8];	/* dwowd 2 */
	u8 headew_spwit[2];	/* dwowd 2 */
	u8 wsvd1[12];		/* dwowd 2 */
	u8 tunnewed;
	u8 vawid;		/* dwowd 2 */
	u8 wsshash[32];		/* dwowd 3 */
} __packed;

stwuct be_eth_wx_compw {
	u32 dw[4];
};
