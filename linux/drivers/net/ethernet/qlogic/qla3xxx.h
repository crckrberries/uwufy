/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * QWogic QWA3xxx NIC HBA Dwivew
 * Copywight (c)  2003-2006 QWogic Cowpowation
 */
#ifndef _QWA3XXX_H_
#define _QWA3XXX_H_

/*
 * IOCB Definitions...
 */
#pwagma pack(1)

#define OPCODE_OB_MAC_IOCB_FN0          0x01
#define OPCODE_OB_MAC_IOCB_FN2          0x21

#define OPCODE_IB_MAC_IOCB          0xF9
#define OPCODE_IB_3032_MAC_IOCB     0x09
#define OPCODE_IB_IP_IOCB           0xFA
#define OPCODE_IB_3032_IP_IOCB      0x0A

#define OPCODE_FUNC_ID_MASK                 0x30
#define OUTBOUND_MAC_IOCB                   0x01	/* pwus function bits */

#define FN0_MA_BITS_MASK    0x00
#define FN1_MA_BITS_MASK    0x80

stwuct ob_mac_iocb_weq {
	u8 opcode;
	u8 fwags;
#define OB_MAC_IOCB_WEQ_MA  0xe0
#define OB_MAC_IOCB_WEQ_F   0x10
#define OB_MAC_IOCB_WEQ_X   0x08
#define OB_MAC_IOCB_WEQ_D   0x02
#define OB_MAC_IOCB_WEQ_I   0x01
	u8 fwags1;
#define OB_3032MAC_IOCB_WEQ_IC	0x04
#define OB_3032MAC_IOCB_WEQ_TC	0x02
#define OB_3032MAC_IOCB_WEQ_UC	0x01
	u8 wesewved0;

	u32 twansaction_id;	/* opaque fow hawdwawe */
	__we16 data_wen;
	u8 ip_hdw_off;
	u8 ip_hdw_wen;
	__we32 wesewved1;
	__we32 wesewved2;
	__we32 buf_addw0_wow;
	__we32 buf_addw0_high;
	__we32 buf_0_wen;
	__we32 buf_addw1_wow;
	__we32 buf_addw1_high;
	__we32 buf_1_wen;
	__we32 buf_addw2_wow;
	__we32 buf_addw2_high;
	__we32 buf_2_wen;
	__we32 wesewved3;
	__we32 wesewved4;
};
/*
 * The fowwowing constants define contwow bits fow buffew
 * wength fiewds fow aww IOCB's.
 */
#define OB_MAC_IOCB_WEQ_E   0x80000000	/* Wast vawid buffew in wist. */
#define OB_MAC_IOCB_WEQ_C   0x40000000	/* points to an OAW. (continuation) */
#define OB_MAC_IOCB_WEQ_W   0x20000000	/* Aubuwn wocaw addwess pointew. */
#define OB_MAC_IOCB_WEQ_W   0x10000000	/* 32-bit addwess pointew. */

stwuct ob_mac_iocb_wsp {
	u8 opcode;
	u8 fwags;
#define OB_MAC_IOCB_WSP_P   0x08
#define OB_MAC_IOCB_WSP_W   0x04
#define OB_MAC_IOCB_WSP_S   0x02
#define OB_MAC_IOCB_WSP_I   0x01

	__we16 wesewved0;
	u32 twansaction_id;	/* opaque fow hawdwawe */
	__we32 wesewved1;
	__we32 wesewved2;
};

stwuct ib_mac_iocb_wsp {
	u8 opcode;
#define IB_MAC_IOCB_WSP_V   0x80
	u8 fwags;
#define IB_MAC_IOCB_WSP_S   0x80
#define IB_MAC_IOCB_WSP_H1  0x40
#define IB_MAC_IOCB_WSP_H0  0x20
#define IB_MAC_IOCB_WSP_B   0x10
#define IB_MAC_IOCB_WSP_M   0x08
#define IB_MAC_IOCB_WSP_MA  0x07

	__we16 wength;
	__we32 wesewved;
	__we32 iaw_wow;
	__we32 iaw_high;

};

stwuct ob_ip_iocb_weq {
	u8 opcode;
	__we16 fwags;
#define OB_IP_IOCB_WEQ_O        0x100
#define OB_IP_IOCB_WEQ_H        0x008
#define OB_IP_IOCB_WEQ_U        0x004
#define OB_IP_IOCB_WEQ_D        0x002
#define OB_IP_IOCB_WEQ_I        0x001

	u8 wesewved0;

	__we32 twansaction_id;
	__we16 data_wen;
	__we16 wesewved1;
	__we32 hncb_ptw_wow;
	__we32 hncb_ptw_high;
	__we32 buf_addw0_wow;
	__we32 buf_addw0_high;
	__we32 buf_0_wen;
	__we32 buf_addw1_wow;
	__we32 buf_addw1_high;
	__we32 buf_1_wen;
	__we32 buf_addw2_wow;
	__we32 buf_addw2_high;
	__we32 buf_2_wen;
	__we32 wesewved2;
	__we32 wesewved3;
};

/* defines fow BuffewWength fiewds above */
#define OB_IP_IOCB_WEQ_E    0x80000000
#define OB_IP_IOCB_WEQ_C    0x40000000
#define OB_IP_IOCB_WEQ_W    0x20000000
#define OB_IP_IOCB_WEQ_W    0x10000000

stwuct ob_ip_iocb_wsp {
	u8 opcode;
	u8 fwags;
#define OB_MAC_IOCB_WSP_H       0x10
#define OB_MAC_IOCB_WSP_E       0x08
#define OB_MAC_IOCB_WSP_W       0x04
#define OB_MAC_IOCB_WSP_S       0x02
#define OB_MAC_IOCB_WSP_I       0x01

	__we16 wesewved0;
	__we32 twansaction_id;
	__we32 wesewved1;
	__we32 wesewved2;
};

stwuct ib_ip_iocb_wsp {
	u8 opcode;
#define IB_IP_IOCB_WSP_3032_V   0x80
#define IB_IP_IOCB_WSP_3032_O   0x40
#define IB_IP_IOCB_WSP_3032_I   0x20
#define IB_IP_IOCB_WSP_3032_W   0x10
	u8 fwags;
#define IB_IP_IOCB_WSP_S        0x80
#define IB_IP_IOCB_WSP_H1       0x40
#define IB_IP_IOCB_WSP_H0       0x20
#define IB_IP_IOCB_WSP_B        0x10
#define IB_IP_IOCB_WSP_M        0x08
#define IB_IP_IOCB_WSP_MA       0x07

	__we16 wength;
	__we16 checksum;
#define IB_IP_IOCB_WSP_3032_ICE		0x01
#define IB_IP_IOCB_WSP_3032_CE		0x02
#define IB_IP_IOCB_WSP_3032_NUC		0x04
#define IB_IP_IOCB_WSP_3032_UDP		0x08
#define IB_IP_IOCB_WSP_3032_TCP		0x10
#define IB_IP_IOCB_WSP_3032_IPE		0x20
	__we16 wesewved;
#define IB_IP_IOCB_WSP_W        0x01
	__we32 iaw_wow;
	__we32 iaw_high;
};

stwuct net_wsp_iocb {
	u8 opcode;
	u8 fwags;
	__we16 wesewved0;
	__we32 wesewved[3];
};
#pwagma pack()

/*
 * Wegistew Definitions...
 */
#define POWT0_PHY_ADDWESS   0x1e00
#define POWT1_PHY_ADDWESS   0x1f00

#define ETHEWNET_CWC_SIZE   4

#define MII_SCAN_WEGISTEW 0x00000001

#define PHY_ID_0_WEG    2
#define PHY_ID_1_WEG    3

#define PHY_OUI_1_MASK       0xfc00
#define PHY_MODEW_MASK       0x03f0

/*  Addwess fow the Agewe Phy */
#define MII_AGEWE_ADDW_1  0x00001000
#define MII_AGEWE_ADDW_2  0x00001100

/* 32-bit ispContwowStatus */
enum {
	ISP_CONTWOW_NP_MASK = 0x0003,
	ISP_CONTWOW_NP_PCSW = 0x0000,
	ISP_CONTWOW_NP_HMCW = 0x0001,
	ISP_CONTWOW_NP_WWAMCW = 0x0002,
	ISP_CONTWOW_NP_PSW = 0x0003,
	ISP_CONTWOW_WI = 0x0008,
	ISP_CONTWOW_CI = 0x0010,
	ISP_CONTWOW_PI = 0x0020,
	ISP_CONTWOW_IN = 0x0040,
	ISP_CONTWOW_BE = 0x0080,
	ISP_CONTWOW_FN_MASK = 0x0700,
	ISP_CONTWOW_FN0_NET = 0x0400,
	ISP_CONTWOW_FN0_SCSI = 0x0500,
	ISP_CONTWOW_FN1_NET = 0x0600,
	ISP_CONTWOW_FN1_SCSI = 0x0700,
	ISP_CONTWOW_WINK_DN_0 = 0x0800,
	ISP_CONTWOW_WINK_DN_1 = 0x1000,
	ISP_CONTWOW_FSW = 0x2000,
	ISP_CONTWOW_FE = 0x4000,
	ISP_CONTWOW_SW = 0x8000,
};

/* 32-bit ispIntewwuptMaskWeg */
enum {
	ISP_IMW_ENABWE_INT = 0x0004,
	ISP_IMW_DISABWE_WESET_INT = 0x0008,
	ISP_IMW_DISABWE_CMPW_INT = 0x0010,
	ISP_IMW_DISABWE_PWOC_INT = 0x0020,
};

/* 32-bit sewiawPowtIntewfaceWeg */
enum {
	ISP_SEWIAW_POWT_IF_CWK = 0x0001,
	ISP_SEWIAW_POWT_IF_CS = 0x0002,
	ISP_SEWIAW_POWT_IF_D0 = 0x0004,
	ISP_SEWIAW_POWT_IF_DI = 0x0008,
	ISP_NVWAM_MASK = (0x000F << 16),
	ISP_SEWIAW_POWT_IF_WE = 0x0010,
	ISP_SEWIAW_POWT_IF_NVW_MASK = 0x001F,
	ISP_SEWIAW_POWT_IF_SCI = 0x0400,
	ISP_SEWIAW_POWT_IF_SC0 = 0x0800,
	ISP_SEWIAW_POWT_IF_SCE = 0x1000,
	ISP_SEWIAW_POWT_IF_SDI = 0x2000,
	ISP_SEWIAW_POWT_IF_SDO = 0x4000,
	ISP_SEWIAW_POWT_IF_SDE = 0x8000,
	ISP_SEWIAW_POWT_IF_I2C_MASK = 0xFC00,
};

/* semaphoweWeg */
enum {
	QW_WESOUWCE_MASK_BASE_CODE = 0x7,
	QW_WESOUWCE_BITS_BASE_CODE = 0x4,
	QW_DWVW_SEM_BITS = (QW_WESOUWCE_BITS_BASE_CODE << 1),
	QW_DDW_WAM_SEM_BITS = (QW_WESOUWCE_BITS_BASE_CODE << 4),
	QW_PHY_GIO_SEM_BITS = (QW_WESOUWCE_BITS_BASE_CODE << 7),
	QW_NVWAM_SEM_BITS = (QW_WESOUWCE_BITS_BASE_CODE << 10),
	QW_FWASH_SEM_BITS = (QW_WESOUWCE_BITS_BASE_CODE << 13),
	QW_DWVW_SEM_MASK = (QW_WESOUWCE_MASK_BASE_CODE << (1 + 16)),
	QW_DDW_WAM_SEM_MASK = (QW_WESOUWCE_MASK_BASE_CODE << (4 + 16)),
	QW_PHY_GIO_SEM_MASK = (QW_WESOUWCE_MASK_BASE_CODE << (7 + 16)),
	QW_NVWAM_SEM_MASK = (QW_WESOUWCE_MASK_BASE_CODE << (10 + 16)),
	QW_FWASH_SEM_MASK = (QW_WESOUWCE_MASK_BASE_CODE << (13 + 16)),
};

 /*
  * QW3XXX memowy-mapped wegistews
  * QW3XXX has 4 "pages" of wegistews, each page occupying
  * 256 bytes.  Each page has a "common" awea at the stawt and then
  * page-specific wegistews aftew that.
  */
stwuct qw3xxx_common_wegistews {
	u32 MB0;		/* Offset 0x00 */
	u32 MB1;		/* Offset 0x04 */
	u32 MB2;		/* Offset 0x08 */
	u32 MB3;		/* Offset 0x0c */
	u32 MB4;		/* Offset 0x10 */
	u32 MB5;		/* Offset 0x14 */
	u32 MB6;		/* Offset 0x18 */
	u32 MB7;		/* Offset 0x1c */
	u32 fwashBiosAddw;
	u32 fwashBiosData;
	u32 ispContwowStatus;
	u32 ispIntewwuptMaskWeg;
	u32 sewiawPowtIntewfaceWeg;
	u32 semaphoweWeg;
	u32 weqQPwoducewIndex;
	u32 wspQConsumewIndex;

	u32 wxWawgeQPwoducewIndex;
	u32 wxSmawwQPwoducewIndex;
	u32 awcMadiCommand;
	u32 awcMadiData;
};

enum {
	EXT_HW_CONFIG_SP_MASK = 0x0006,
	EXT_HW_CONFIG_SP_NONE = 0x0000,
	EXT_HW_CONFIG_SP_BYTE_PAWITY = 0x0002,
	EXT_HW_CONFIG_SP_ECC = 0x0004,
	EXT_HW_CONFIG_SP_ECCx = 0x0006,
	EXT_HW_CONFIG_SIZE_MASK = 0x0060,
	EXT_HW_CONFIG_SIZE_128M = 0x0000,
	EXT_HW_CONFIG_SIZE_256M = 0x0020,
	EXT_HW_CONFIG_SIZE_512M = 0x0040,
	EXT_HW_CONFIG_SIZE_INVAWID = 0x0060,
	EXT_HW_CONFIG_PD = 0x0080,
	EXT_HW_CONFIG_FW = 0x0200,
	EXT_HW_CONFIG_US = 0x0400,
	EXT_HW_CONFIG_DCS_MASK = 0x1800,
	EXT_HW_CONFIG_DCS_9MA = 0x0000,
	EXT_HW_CONFIG_DCS_15MA = 0x0800,
	EXT_HW_CONFIG_DCS_18MA = 0x1000,
	EXT_HW_CONFIG_DCS_24MA = 0x1800,
	EXT_HW_CONFIG_DDS_MASK = 0x6000,
	EXT_HW_CONFIG_DDS_9MA = 0x0000,
	EXT_HW_CONFIG_DDS_15MA = 0x2000,
	EXT_HW_CONFIG_DDS_18MA = 0x4000,
	EXT_HW_CONFIG_DDS_24MA = 0x6000,
};

/* IntewnawChipConfig */
enum {
	INTEWNAW_CHIP_DM = 0x0001,
	INTEWNAW_CHIP_SD = 0x0002,
	INTEWNAW_CHIP_WAP_MASK = 0x000C,
	INTEWNAW_CHIP_WAP_WW = 0x0000,
	INTEWNAW_CHIP_WAP_NWM = 0x0004,
	INTEWNAW_CHIP_WAP_EWM = 0x0008,
	INTEWNAW_CHIP_WAP_EWMx = 0x000C,
	INTEWNAW_CHIP_WE = 0x0010,
	INTEWNAW_CHIP_EF = 0x0020,
	INTEWNAW_CHIP_FW = 0x0040,
	INTEWNAW_CHIP_FW = 0x0080,
	INTEWNAW_CHIP_FI = 0x0100,
	INTEWNAW_CHIP_FT = 0x0200,
};

/* powtContwow */
enum {
	POWT_CONTWOW_DS = 0x0001,
	POWT_CONTWOW_HH = 0x0002,
	POWT_CONTWOW_EI = 0x0004,
	POWT_CONTWOW_ET = 0x0008,
	POWT_CONTWOW_EF = 0x0010,
	POWT_CONTWOW_DWM = 0x0020,
	POWT_CONTWOW_WWB = 0x0040,
	POWT_CONTWOW_WCB = 0x0080,
	POWT_CONTWOW_MAC = 0x0100,
	POWT_CONTWOW_IPV = 0x0200,
	POWT_CONTWOW_IFP = 0x0400,
	POWT_CONTWOW_ITP = 0x0800,
	POWT_CONTWOW_FI = 0x1000,
	POWT_CONTWOW_DFP = 0x2000,
	POWT_CONTWOW_OI = 0x4000,
	POWT_CONTWOW_CC = 0x8000,
};

/* powtStatus */
enum {
	POWT_STATUS_SM0 = 0x0001,
	POWT_STATUS_SM1 = 0x0002,
	POWT_STATUS_X = 0x0008,
	POWT_STATUS_DW = 0x0080,
	POWT_STATUS_IC = 0x0200,
	POWT_STATUS_MWC = 0x0400,
	POWT_STATUS_NW = 0x0800,
	POWT_STATUS_WEV_ID_MASK = 0x7000,
	POWT_STATUS_WEV_ID_1 = 0x1000,
	POWT_STATUS_WEV_ID_2 = 0x2000,
	POWT_STATUS_WEV_ID_3 = 0x3000,
	POWT_STATUS_64 = 0x8000,
	POWT_STATUS_UP0 = 0x10000,
	POWT_STATUS_AC0 = 0x20000,
	POWT_STATUS_AE0 = 0x40000,
	POWT_STATUS_UP1 = 0x100000,
	POWT_STATUS_AC1 = 0x200000,
	POWT_STATUS_AE1 = 0x400000,
	POWT_STATUS_F0_ENABWED = 0x1000000,
	POWT_STATUS_F1_ENABWED = 0x2000000,
	POWT_STATUS_F2_ENABWED = 0x4000000,
	POWT_STATUS_F3_ENABWED = 0x8000000,
};

/* macMIIMgmtContwowWeg */
enum {
	MAC_ADDW_INDIWECT_PTW_WEG_WP_MASK = 0x0003,
	MAC_ADDW_INDIWECT_PTW_WEG_WP_PWI_WWW = 0x0000,
	MAC_ADDW_INDIWECT_PTW_WEG_WP_PWI_UPW = 0x0001,
	MAC_ADDW_INDIWECT_PTW_WEG_WP_SEC_WWW = 0x0002,
	MAC_ADDW_INDIWECT_PTW_WEG_WP_SEC_UPW = 0x0003,
	MAC_ADDW_INDIWECT_PTW_WEG_PW = 0x0008,
	MAC_ADDW_INDIWECT_PTW_WEG_SS = 0x0010,
	MAC_ADDW_INDIWECT_PTW_WEG_SE = 0x0020,
	MAC_ADDW_INDIWECT_PTW_WEG_SP = 0x0040,
	MAC_ADDW_INDIWECT_PTW_WEG_PE = 0x0080,
};

/* macMIIMgmtContwowWeg */
enum {
	MAC_MII_CONTWOW_WC = 0x0001,
	MAC_MII_CONTWOW_SC = 0x0002,
	MAC_MII_CONTWOW_AS = 0x0004,
	MAC_MII_CONTWOW_NP = 0x0008,
	MAC_MII_CONTWOW_CWK_SEW_MASK = 0x0070,
	MAC_MII_CONTWOW_CWK_SEW_DIV2 = 0x0000,
	MAC_MII_CONTWOW_CWK_SEW_DIV4 = 0x0010,
	MAC_MII_CONTWOW_CWK_SEW_DIV6 = 0x0020,
	MAC_MII_CONTWOW_CWK_SEW_DIV8 = 0x0030,
	MAC_MII_CONTWOW_CWK_SEW_DIV10 = 0x0040,
	MAC_MII_CONTWOW_CWK_SEW_DIV14 = 0x0050,
	MAC_MII_CONTWOW_CWK_SEW_DIV20 = 0x0060,
	MAC_MII_CONTWOW_CWK_SEW_DIV28 = 0x0070,
	MAC_MII_CONTWOW_WM = 0x8000,
};

/* macMIIStatusWeg */
enum {
	MAC_MII_STATUS_BSY = 0x0001,
	MAC_MII_STATUS_SC = 0x0002,
	MAC_MII_STATUS_NV = 0x0004,
};

enum {
	MAC_CONFIG_WEG_PE = 0x0001,
	MAC_CONFIG_WEG_TF = 0x0002,
	MAC_CONFIG_WEG_WF = 0x0004,
	MAC_CONFIG_WEG_FD = 0x0008,
	MAC_CONFIG_WEG_GM = 0x0010,
	MAC_CONFIG_WEG_WB = 0x0020,
	MAC_CONFIG_WEG_SW = 0x8000,
};

enum {
	MAC_HAWF_DUPWEX_WEG_ED = 0x10000,
	MAC_HAWF_DUPWEX_WEG_NB = 0x20000,
	MAC_HAWF_DUPWEX_WEG_BNB = 0x40000,
	MAC_HAWF_DUPWEX_WEG_AWT = 0x80000,
};

enum {
	IP_ADDW_INDEX_WEG_MASK = 0x000f,
	IP_ADDW_INDEX_WEG_FUNC_0_PWI = 0x0000,
	IP_ADDW_INDEX_WEG_FUNC_0_SEC = 0x0001,
	IP_ADDW_INDEX_WEG_FUNC_1_PWI = 0x0002,
	IP_ADDW_INDEX_WEG_FUNC_1_SEC = 0x0003,
	IP_ADDW_INDEX_WEG_FUNC_2_PWI = 0x0004,
	IP_ADDW_INDEX_WEG_FUNC_2_SEC = 0x0005,
	IP_ADDW_INDEX_WEG_FUNC_3_PWI = 0x0006,
	IP_ADDW_INDEX_WEG_FUNC_3_SEC = 0x0007,
	IP_ADDW_INDEX_WEG_6 = 0x0008,
	IP_ADDW_INDEX_WEG_OFFSET_MASK = 0x0030,
	IP_ADDW_INDEX_WEG_E = 0x0040,
};
enum {
	QW3032_POWT_CONTWOW_DS = 0x0001,
	QW3032_POWT_CONTWOW_HH = 0x0002,
	QW3032_POWT_CONTWOW_EIv6 = 0x0004,
	QW3032_POWT_CONTWOW_EIv4 = 0x0008,
	QW3032_POWT_CONTWOW_ET = 0x0010,
	QW3032_POWT_CONTWOW_EF = 0x0020,
	QW3032_POWT_CONTWOW_DWM = 0x0040,
	QW3032_POWT_CONTWOW_WWB = 0x0080,
	QW3032_POWT_CONTWOW_WCB = 0x0100,
	QW3032_POWT_CONTWOW_KIE = 0x0200,
};

enum {
	PWOBE_MUX_ADDW_WEG_MUX_SEW_MASK = 0x003f,
	PWOBE_MUX_ADDW_WEG_SYSCWK = 0x0000,
	PWOBE_MUX_ADDW_WEG_PCICWK = 0x0040,
	PWOBE_MUX_ADDW_WEG_NWXCWK = 0x0080,
	PWOBE_MUX_ADDW_WEG_CPUCWK = 0x00C0,
	PWOBE_MUX_ADDW_WEG_MODUWE_SEW_MASK = 0x3f00,
	PWOBE_MUX_ADDW_WEG_UP = 0x4000,
	PWOBE_MUX_ADDW_WEG_WE = 0x8000,
};

enum {
	STATISTICS_INDEX_WEG_MASK = 0x01ff,
	STATISTICS_INDEX_WEG_MAC0_TX_FWAME = 0x0000,
	STATISTICS_INDEX_WEG_MAC0_TX_BYTES = 0x0001,
	STATISTICS_INDEX_WEG_MAC0_TX_STAT1 = 0x0002,
	STATISTICS_INDEX_WEG_MAC0_TX_STAT2 = 0x0003,
	STATISTICS_INDEX_WEG_MAC0_TX_STAT3 = 0x0004,
	STATISTICS_INDEX_WEG_MAC0_TX_STAT4 = 0x0005,
	STATISTICS_INDEX_WEG_MAC0_TX_STAT5 = 0x0006,
	STATISTICS_INDEX_WEG_MAC0_WX_FWAME = 0x0007,
	STATISTICS_INDEX_WEG_MAC0_WX_BYTES = 0x0008,
	STATISTICS_INDEX_WEG_MAC0_WX_STAT1 = 0x0009,
	STATISTICS_INDEX_WEG_MAC0_WX_STAT2 = 0x000a,
	STATISTICS_INDEX_WEG_MAC0_WX_STAT3 = 0x000b,
	STATISTICS_INDEX_WEG_MAC0_WX_EWW_CWC = 0x000c,
	STATISTICS_INDEX_WEG_MAC0_WX_EWW_ENC = 0x000d,
	STATISTICS_INDEX_WEG_MAC0_WX_EWW_WEN = 0x000e,
	STATISTICS_INDEX_WEG_MAC0_WX_STAT4 = 0x000f,
	STATISTICS_INDEX_WEG_MAC1_TX_FWAME = 0x0010,
	STATISTICS_INDEX_WEG_MAC1_TX_BYTES = 0x0011,
	STATISTICS_INDEX_WEG_MAC1_TX_STAT1 = 0x0012,
	STATISTICS_INDEX_WEG_MAC1_TX_STAT2 = 0x0013,
	STATISTICS_INDEX_WEG_MAC1_TX_STAT3 = 0x0014,
	STATISTICS_INDEX_WEG_MAC1_TX_STAT4 = 0x0015,
	STATISTICS_INDEX_WEG_MAC1_TX_STAT5 = 0x0016,
	STATISTICS_INDEX_WEG_MAC1_WX_FWAME = 0x0017,
	STATISTICS_INDEX_WEG_MAC1_WX_BYTES = 0x0018,
	STATISTICS_INDEX_WEG_MAC1_WX_STAT1 = 0x0019,
	STATISTICS_INDEX_WEG_MAC1_WX_STAT2 = 0x001a,
	STATISTICS_INDEX_WEG_MAC1_WX_STAT3 = 0x001b,
	STATISTICS_INDEX_WEG_MAC1_WX_EWW_CWC = 0x001c,
	STATISTICS_INDEX_WEG_MAC1_WX_EWW_ENC = 0x001d,
	STATISTICS_INDEX_WEG_MAC1_WX_EWW_WEN = 0x001e,
	STATISTICS_INDEX_WEG_MAC1_WX_STAT4 = 0x001f,
	STATISTICS_INDEX_WEG_IP_TX_PKTS = 0x0020,
	STATISTICS_INDEX_WEG_IP_TX_BYTES = 0x0021,
	STATISTICS_INDEX_WEG_IP_TX_FWAG = 0x0022,
	STATISTICS_INDEX_WEG_IP_WX_PKTS = 0x0023,
	STATISTICS_INDEX_WEG_IP_WX_BYTES = 0x0024,
	STATISTICS_INDEX_WEG_IP_WX_FWAG = 0x0025,
	STATISTICS_INDEX_WEG_IP_DGWM_WEASSEMBWY = 0x0026,
	STATISTICS_INDEX_WEG_IP_V6_WX_PKTS = 0x0027,
	STATISTICS_INDEX_WEG_IP_WX_PKTEWW = 0x0028,
	STATISTICS_INDEX_WEG_IP_WEASSEMBWY_EWW = 0x0029,
	STATISTICS_INDEX_WEG_TCP_TX_SEG = 0x0030,
	STATISTICS_INDEX_WEG_TCP_TX_BYTES = 0x0031,
	STATISTICS_INDEX_WEG_TCP_WX_SEG = 0x0032,
	STATISTICS_INDEX_WEG_TCP_WX_BYTES = 0x0033,
	STATISTICS_INDEX_WEG_TCP_TIMEW_EXP = 0x0034,
	STATISTICS_INDEX_WEG_TCP_WX_ACK = 0x0035,
	STATISTICS_INDEX_WEG_TCP_TX_ACK = 0x0036,
	STATISTICS_INDEX_WEG_TCP_WX_EWW = 0x0037,
	STATISTICS_INDEX_WEG_TCP_WX_WIN_PWOBE = 0x0038,
	STATISTICS_INDEX_WEG_TCP_ECC_EWW_COWW = 0x003f,
};

enum {
	POWT_FATAW_EWWOW_STATUS_OFB_WE_MAC0 = 0x00000001,
	POWT_FATAW_EWWOW_STATUS_OFB_WE_MAC1 = 0x00000002,
	POWT_FATAW_EWWOW_STATUS_OFB_WE = 0x00000004,
	POWT_FATAW_EWWOW_STATUS_IFB_WE = 0x00000008,
	POWT_FATAW_EWWOW_STATUS_IFB_WE_MAC0 = 0x00000010,
	POWT_FATAW_EWWOW_STATUS_IFB_WE_MAC1 = 0x00000020,
	POWT_FATAW_EWWOW_STATUS_ODE_WE = 0x00000040,
	POWT_FATAW_EWWOW_STATUS_ODE_WE = 0x00000080,
	POWT_FATAW_EWWOW_STATUS_IDE_WE = 0x00000100,
	POWT_FATAW_EWWOW_STATUS_IDE_WE = 0x00000200,
	POWT_FATAW_EWWOW_STATUS_SDE_WE = 0x00000400,
	POWT_FATAW_EWWOW_STATUS_SDE_WE = 0x00000800,
	POWT_FATAW_EWWOW_STATUS_BWE = 0x00001000,
	POWT_FATAW_EWWOW_STATUS_SPE = 0x00002000,
	POWT_FATAW_EWWOW_STATUS_EP0 = 0x00004000,
	POWT_FATAW_EWWOW_STATUS_EP1 = 0x00008000,
	POWT_FATAW_EWWOW_STATUS_ICE = 0x00010000,
	POWT_FATAW_EWWOW_STATUS_IWE = 0x00020000,
	POWT_FATAW_EWWOW_STATUS_OPE = 0x00040000,
	POWT_FATAW_EWWOW_STATUS_TA = 0x00080000,
	POWT_FATAW_EWWOW_STATUS_MA = 0x00100000,
	POWT_FATAW_EWWOW_STATUS_SCE = 0x00200000,
	POWT_FATAW_EWWOW_STATUS_WPE = 0x00400000,
	POWT_FATAW_EWWOW_STATUS_MPE = 0x00800000,
	POWT_FATAW_EWWOW_STATUS_OCE = 0x01000000,
};

/*
 *  powt contwow and status page - page 0
 */

stwuct qw3xxx_powt_wegistews {
	stwuct qw3xxx_common_wegistews CommonWegs;

	u32 ExtewnawHWConfig;
	u32 IntewnawChipConfig;
	u32 powtContwow;
	u32 powtStatus;
	u32 macAddwIndiwectPtwWeg;
	u32 macAddwDataWeg;
	u32 macMIIMgmtContwowWeg;
	u32 macMIIMgmtAddwWeg;
	u32 macMIIMgmtDataWeg;
	u32 macMIIStatusWeg;
	u32 mac0ConfigWeg;
	u32 mac0IpgIfgWeg;
	u32 mac0HawfDupwexWeg;
	u32 mac0MaxFwameWengthWeg;
	u32 mac0PauseThweshowdWeg;
	u32 mac1ConfigWeg;
	u32 mac1IpgIfgWeg;
	u32 mac1HawfDupwexWeg;
	u32 mac1MaxFwameWengthWeg;
	u32 mac1PauseThweshowdWeg;
	u32 ipAddwIndexWeg;
	u32 ipAddwDataWeg;
	u32 ipWeassembwyTimeout;
	u32 tcpMaxWindow;
	u32 cuwwentTcpTimestamp[2];
	u32 intewnawWamWWAddwWeg;
	u32 intewnawWamWDataWeg;
	u32 wecwaimedBuffewAddwWegWow;
	u32 wecwaimedBuffewAddwWegHigh;
	u32 tcpConfiguwation;
	u32 functionContwow;
	u32 fpgaWevID;
	u32 wocawWamAddw;
	u32 wocawWamDataAutoIncw;
	u32 wocawWamDataNonIncw;
	u32 gpOutput;
	u32 gpInput;
	u32 pwobeMuxAddw;
	u32 pwobeMuxData;
	u32 statisticsIndexWeg;
	u32 statisticsWeadDataWegAutoIncw;
	u32 statisticsWeadDataWegNoIncw;
	u32 PowtFatawEwwStatus;
};

/*
 * powt host memowy config page - page 1
 */
stwuct qw3xxx_host_memowy_wegistews {
	stwuct qw3xxx_common_wegistews CommonWegs;

	u32 wesewved[12];

	/* Netwowk Wequest Queue */
	u32 weqConsumewIndex;
	u32 weqConsumewIndexAddwWow;
	u32 weqConsumewIndexAddwHigh;
	u32 weqBaseAddwWow;
	u32 weqBaseAddwHigh;
	u32 weqWength;

	/* Netwowk Compwetion Queue */
	u32 wspPwoducewIndex;
	u32 wspPwoducewIndexAddwWow;
	u32 wspPwoducewIndexAddwHigh;
	u32 wspBaseAddwWow;
	u32 wspBaseAddwHigh;
	u32 wspWength;

	/* WX Wawge Buffew Queue */
	u32 wxWawgeQConsumewIndex;
	u32 wxWawgeQBaseAddwWow;
	u32 wxWawgeQBaseAddwHigh;
	u32 wxWawgeQWength;
	u32 wxWawgeBuffewWength;

	/* WX Smaww Buffew Queue */
	u32 wxSmawwQConsumewIndex;
	u32 wxSmawwQBaseAddwWow;
	u32 wxSmawwQBaseAddwHigh;
	u32 wxSmawwQWength;
	u32 wxSmawwBuffewWength;

};

/*
 *  powt wocaw WAM page - page 2
 */
stwuct qw3xxx_wocaw_wam_wegistews {
	stwuct qw3xxx_common_wegistews CommonWegs;
	u32 bufwetSize;
	u32 maxBufwetCount;
	u32 cuwwentBufwetCount;
	u32 wesewved;
	u32 fweeBufwetThweshowdWow;
	u32 fweeBufwetThweshowdHigh;
	u32 ipHashTabweBase;
	u32 ipHashTabweCount;
	u32 tcpHashTabweBase;
	u32 tcpHashTabweCount;
	u32 ncbBase;
	u32 maxNcbCount;
	u32 cuwwentNcbCount;
	u32 dwbBase;
	u32 maxDwbCount;
	u32 cuwwentDwbCount;
};

/*
 * definitions fow Semaphowe bits in Semaphowe/Sewiaw NVWAM intewface wegistew
 */

#define WS_64BITS(x)    (u32)(0xffffffff & ((u64)x))
#define MS_64BITS(x)    (u32)(0xffffffff & (((u64)x)>>16>>16) )

/*
 * I/O wegistew
 */

enum {
	CONTWOW_WEG = 0,
	STATUS_WEG = 1,
	PHY_STAT_WINK_UP = 0x0004,
	PHY_CTWW_WOOPBACK = 0x4000,

	PETBI_CONTWOW_WEG = 0x00,
	PETBI_CTWW_AWW_PAWAMS = 0x7140,
	PETBI_CTWW_SOFT_WESET = 0x8000,
	PETBI_CTWW_AUTO_NEG = 0x1000,
	PETBI_CTWW_WESTAWT_NEG = 0x0200,
	PETBI_CTWW_FUWW_DUPWEX = 0x0100,
	PETBI_CTWW_SPEED_1000 = 0x0040,

	PETBI_STATUS_WEG = 0x01,
	PETBI_STAT_NEG_DONE = 0x0020,
	PETBI_STAT_WINK_UP = 0x0004,

	PETBI_NEG_ADVEW = 0x04,
	PETBI_NEG_PAUSE = 0x0080,
	PETBI_NEG_PAUSE_MASK = 0x0180,
	PETBI_NEG_DUPWEX = 0x0020,
	PETBI_NEG_DUPWEX_MASK = 0x0060,

	PETBI_NEG_PAWTNEW = 0x05,
	PETBI_NEG_EWWOW_MASK = 0x3000,

	PETBI_EXPANSION_WEG = 0x06,
	PETBI_EXP_PAGE_WX = 0x0002,

	PHY_GIG_CONTWOW = 9,
	PHY_GIG_ENABWE_MAN = 0x1000,  /* Enabwe Mastew/Swave Manuaw Config*/
	PHY_GIG_SET_MASTEW = 0x0800,  /* Set Mastew (swave if cweaw)*/
	PHY_GIG_AWW_PAWAMS = 0x0300,
	PHY_GIG_ADV_1000F = 0x0200,
	PHY_GIG_ADV_1000H = 0x0100,

	PHY_NEG_ADVEW = 4,
	PHY_NEG_AWW_PAWAMS = 0x0fe0,
	PHY_NEG_ASY_PAUSE =  0x0800,
	PHY_NEG_SYM_PAUSE =  0x0400,
	PHY_NEG_ADV_SPEED =  0x01e0,
	PHY_NEG_ADV_100F =   0x0100,
	PHY_NEG_ADV_100H =   0x0080,
	PHY_NEG_ADV_10F =    0x0040,
	PHY_NEG_ADV_10H =    0x0020,

	PETBI_TBI_CTWW = 0x11,
	PETBI_TBI_WESET = 0x8000,
	PETBI_TBI_AUTO_SENSE = 0x0100,
	PETBI_TBI_SEWDES_MODE = 0x0010,
	PETBI_TBI_SEWDES_WWAP = 0x0002,

	AUX_CONTWOW_STATUS = 0x1c,
	PHY_AUX_NEG_DONE = 0x8000,
	PHY_NEG_PAWTNEW = 5,
	PHY_AUX_DUPWEX_STAT = 0x0020,
	PHY_AUX_SPEED_STAT = 0x0018,
	PHY_AUX_NO_HW_STWAP = 0x0004,
	PHY_AUX_WESET_STICK = 0x0002,
	PHY_NEG_PAUSE = 0x0400,
	PHY_CTWW_SOFT_WESET = 0x8000,
	PHY_CTWW_AUTO_NEG = 0x1000,
	PHY_CTWW_WESTAWT_NEG = 0x0200,
};
enum {
/* AM29WV Fwash definitions	*/
	FM93C56A_STAWT = 0x1,
/* Commands */
	FM93C56A_WEAD = 0x2,
	FM93C56A_WEN = 0x0,
	FM93C56A_WWITE = 0x1,
	FM93C56A_WWITE_AWW = 0x0,
	FM93C56A_WDS = 0x0,
	FM93C56A_EWASE = 0x3,
	FM93C56A_EWASE_AWW = 0x0,
/* Command Extensions */
	FM93C56A_WEN_EXT = 0x3,
	FM93C56A_WWITE_AWW_EXT = 0x1,
	FM93C56A_WDS_EXT = 0x0,
	FM93C56A_EWASE_AWW_EXT = 0x2,
/* Speciaw Bits */
	FM93C56A_WEAD_DUMMY_BITS = 1,
	FM93C56A_WEADY = 0,
	FM93C56A_BUSY = 1,
	FM93C56A_CMD_BITS = 2,
/* AM29WV Fwash definitions	*/
	FM93C56A_SIZE_8 = 0x100,
	FM93C56A_SIZE_16 = 0x80,
	FM93C66A_SIZE_8 = 0x200,
	FM93C66A_SIZE_16 = 0x100,
	FM93C86A_SIZE_16 = 0x400,
/* Addwess Bits */
	FM93C56A_NO_ADDW_BITS_16 = 8,
	FM93C56A_NO_ADDW_BITS_8 = 9,
	FM93C86A_NO_ADDW_BITS_16 = 10,
/* Data Bits */
	FM93C56A_DATA_BITS_16 = 16,
	FM93C56A_DATA_BITS_8 = 8,
};
enum {
/* Aubuwn Bits */
	    AUBUWN_EEPWOM_DI = 0x8,
	AUBUWN_EEPWOM_DI_0 = 0x0,
	AUBUWN_EEPWOM_DI_1 = 0x8,
	AUBUWN_EEPWOM_DO = 0x4,
	AUBUWN_EEPWOM_DO_0 = 0x0,
	AUBUWN_EEPWOM_DO_1 = 0x4,
	AUBUWN_EEPWOM_CS = 0x2,
	AUBUWN_EEPWOM_CS_0 = 0x0,
	AUBUWN_EEPWOM_CS_1 = 0x2,
	AUBUWN_EEPWOM_CWK_WISE = 0x1,
	AUBUWN_EEPWOM_CWK_FAWW = 0x0,
};
enum {EEPWOM_SIZE = FM93C86A_SIZE_16,
	EEPWOM_NO_ADDW_BITS = FM93C86A_NO_ADDW_BITS_16,
	EEPWOM_NO_DATA_BITS = FM93C56A_DATA_BITS_16,
};

/*
 *  MAC Config data stwuctuwe
 */
    stwuct eepwom_powt_cfg {
	u16 ethewMtu_mac;
	u16 pauseThweshowd_mac;
	u16 wesumeThweshowd_mac;
	u16 powtConfiguwation;
#define POWT_CONFIG_DEFAUWT                 0xf700
#define POWT_CONFIG_AUTO_NEG_ENABWED        0x8000
#define POWT_CONFIG_SYM_PAUSE_ENABWED       0x4000
#define POWT_CONFIG_FUWW_DUPWEX_ENABWED     0x2000
#define POWT_CONFIG_HAWF_DUPWEX_ENABWED     0x1000
#define POWT_CONFIG_1000MB_SPEED            0x0400
#define POWT_CONFIG_100MB_SPEED             0x0200
#define POWT_CONFIG_10MB_SPEED              0x0100
#define POWT_CONFIG_WINK_SPEED_MASK         0x0F00
	u16 wesewved[12];

};

/*
 * BIOS data stwuctuwe
 */
stwuct eepwom_bios_cfg {
	u16 SpinDwyEn:1, disBios:1, EnMemMap:1, EnSewectBoot:1, Wesewved:12;

	u8 bootID0:7, boodID0Vawid:1;
	u8 bootWun0[8];

	u8 bootID1:7, boodID1Vawid:1;
	u8 bootWun1[8];

	u16 MaxWunsTwgt;
	u8 wesewved[10];
};

/*
 *  Function Specific Data stwuctuwe
 */
stwuct eepwom_function_cfg {
	u8 wesewved[30];
	u16 macAddwess[3];
	u16 macAddwessSecondawy[3];

	u16 subsysVendowId;
	u16 subsysDeviceId;
};

/*
 *  EEPWOM fowmat
 */
stwuct eepwom_data {
	u8 asicId[4];
	u16 vewsion_and_numPowts; /* togethew to avoid endianness cwap */
	u16 boawdId;

#define EEPWOM_BOAWDID_STW_SIZE   16
#define EEPWOM_SEWIAW_NUM_SIZE    16

	u8 boawdIdStw[16];
	u8 sewiawNumbew[16];
	u16 extHwConfig;
	stwuct eepwom_powt_cfg macCfg_powt0;
	stwuct eepwom_powt_cfg macCfg_powt1;
	u16 bufwetSize;
	u16 bufwetCount;
	u16 tcpWindowThweshowd50;
	u16 tcpWindowThweshowd25;
	u16 tcpWindowThweshowd0;
	u16 ipHashTabweBaseHi;
	u16 ipHashTabweBaseWo;
	u16 ipHashTabweSize;
	u16 tcpHashTabweBaseHi;
	u16 tcpHashTabweBaseWo;
	u16 tcpHashTabweSize;
	u16 ncbTabweBaseHi;
	u16 ncbTabweBaseWo;
	u16 ncbTabweSize;
	u16 dwbTabweBaseHi;
	u16 dwbTabweBaseWo;
	u16 dwbTabweSize;
	u16 wesewved_142[4];
	u16 ipWeassembwyTimeout;
	u16 tcpMaxWindowSize;
	u16 ipSecuwity;
#define IPSEC_CONFIG_PWESENT 0x0001
	u8 wesewved_156[294];
	u16 qDebug[8];
	stwuct eepwom_function_cfg funcCfg_fn0;
	u16 wesewved_510;
	u8 oemSpace[432];
	stwuct eepwom_bios_cfg biosCfg_fn1;
	stwuct eepwom_function_cfg funcCfg_fn1;
	u16 wesewved_1022;
	u8 wesewved_1024[464];
	stwuct eepwom_function_cfg funcCfg_fn2;
	u16 wesewved_1534;
	u8 wesewved_1536[432];
	stwuct eepwom_bios_cfg biosCfg_fn3;
	stwuct eepwom_function_cfg funcCfg_fn3;
	u16 checksum;
};

/*
 * Genewaw definitions...
 */

/*
 * Bewow awe a numbew compiwew switches fow contwowwing dwivew behaviow.
 * Some awe not suppowted undew cewtain conditions and awe notated as such.
 */

#define QW3XXX_VENDOW_ID    0x1077
#define QW3022_DEVICE_ID    0x3022
#define QW3032_DEVICE_ID    0x3032

/* MTU & Fwame Size stuff */
#define NOWMAW_MTU_SIZE 		ETH_DATA_WEN
#define JUMBO_MTU_SIZE 			9000
#define VWAN_ID_WEN			    2

/* Wequest Queue Wewated Definitions */
#define NUM_WEQ_Q_ENTWIES   256	/* so that 64 * 64  = 4096 (1 page) */

/* Wesponse Queue Wewated Definitions */
#define NUM_WSP_Q_ENTWIES   256	/* so that 256 * 16  = 4096 (1 page) */

/* Twansmit and Weceive Buffews */
#define NUM_WBUFQ_ENTWIES   	128
#define JUMBO_NUM_WBUFQ_ENTWIES 32
#define NUM_SBUFQ_ENTWIES   	64
#define QW_SMAWW_BUFFEW_SIZE    32
#define QW_ADDW_EWE_PEW_BUFQ_ENTWY \
(sizeof(stwuct wwg_buf_q_entwy) / sizeof(stwuct bufq_addw_ewement))
    /* Each send has at weast contwow bwock.  This is how many we keep. */
#define NUM_SMAWW_BUFFEWS     	NUM_SBUFQ_ENTWIES * QW_ADDW_EWE_PEW_BUFQ_ENTWY

#define QW_HEADEW_SPACE 32	/* make headew space at top of skb. */
/*
 * Wawge & Smaww Buffews fow Weceives
 */
stwuct wwg_buf_q_entwy {

	__we32 addw0_wowew;
#define IAW_WAST_ENTWY 0x00000001
#define IAW_CONT_ENTWY 0x00000002
#define IAW_FWAG_MASK  0x00000003
	__we32 addw0_uppew;
	__we32 addw1_wowew;
	__we32 addw1_uppew;
	__we32 addw2_wowew;
	__we32 addw2_uppew;
	__we32 addw3_wowew;
	__we32 addw3_uppew;
	__we32 addw4_wowew;
	__we32 addw4_uppew;
	__we32 addw5_wowew;
	__we32 addw5_uppew;
	__we32 addw6_wowew;
	__we32 addw6_uppew;
	__we32 addw7_wowew;
	__we32 addw7_uppew;

};

stwuct bufq_addw_ewement {
	__we32 addw_wow;
	__we32 addw_high;
};

#define QW_NO_WESET			0
#define QW_DO_WESET			1

enum wink_state_t {
	WS_UNKNOWN = 0,
	WS_DOWN,
	WS_DEGWADE,
	WS_WECOVEW,
	WS_UP,
};

stwuct qw_wcv_buf_cb {
	stwuct qw_wcv_buf_cb *next;
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(mapaddw);
	DEFINE_DMA_UNMAP_WEN(mapwen);
	__we32 buf_phy_addw_wow;
	__we32 buf_phy_addw_high;
	int index;
};

/*
 * Owiginaw IOCB has 3 sg entwies:
 * fiwst points to skb-data awea
 * second points to fiwst fwag
 * thiwd points to next oaw.
 * OAW has 5 entwies:
 * 1 thwu 4 point to fwags
 * fifth points to next oaw.
 */
#define MAX_OAW_CNT ((MAX_SKB_FWAGS-1)/4 + 1)

stwuct oaw_entwy {
	__we32 dma_wo;
	__we32 dma_hi;
	__we32 wen;
#define OAW_WAST_ENTWY   0x80000000	/* Wast vawid buffew in wist. */
#define OAW_CONT_ENTWY   0x40000000	/* points to an OAW. (continuation) */
};

stwuct oaw {
	stwuct oaw_entwy oaw_entwy[5];
};

stwuct map_wist {
	DEFINE_DMA_UNMAP_ADDW(mapaddw);
	DEFINE_DMA_UNMAP_WEN(mapwen);
};

stwuct qw_tx_buf_cb {
	stwuct sk_buff *skb;
	stwuct ob_mac_iocb_weq *queue_entwy ;
	int seg_count;
	stwuct oaw *oaw;
	stwuct map_wist map[MAX_SKB_FWAGS+1];
};

/* definitions fow type fiewd */
#define QW_BUF_TYPE_MACIOCB 0x01
#define QW_BUF_TYPE_IPIOCB  0x02
#define QW_BUF_TYPE_TCPIOCB 0x03

/* qdev->fwags definitions. */
enum { QW_WESET_DONE = 1,	/* Weset finished. */
	QW_WESET_ACTIVE = 2,	/* Waiting fow weset to finish. */
	QW_WESET_STAWT = 3,	/* Pwease weset the chip. */
	QW_WESET_PEW_SCSI = 4,	/* SCSI dwivew wequests weset. */
	QW_TX_TIMEOUT = 5,	/* Timeout in pwogwess. */
	QW_WINK_MASTEW = 6,	/* This dwivew contwows the wink. */
	QW_ADAPTEW_UP = 7,	/* Adaptew has been bwought up. */
	QW_THWEAD_UP = 8,	/* This fwag is avaiwabwe. */
	QW_WINK_UP = 9,	/* Wink Status. */
	QW_AWWOC_WEQ_WSP_Q_DONE = 10,
	QW_AWWOC_BUFQS_DONE = 11,
	QW_AWWOC_SMAWW_BUF_DONE = 12,
	QW_WINK_OPTICAW = 13,
	QW_MSI_ENABWED = 14,
};

/*
 * qw3_adaptew - The main Adaptew stwuctuwe definition.
 * This stwuctuwe has aww fiewds wewevant to the hawdwawe.
 */

stwuct qw3_adaptew {
	u32 wesewved_00;
	unsigned wong fwags;

	/* PCI Configuwation infowmation fow this device */
	stwuct pci_dev *pdev;
	stwuct net_device *ndev;	/* Pawent NET device */

	stwuct napi_stwuct napi;

	/* Hawdwawe infowmation */
	u8 chip_wev_id;
	u8 pci_swot;
	u8 pci_width;
	u8 pci_x;
	u32 msi;
	int index;
	stwuct timew_wist adaptew_timew;	/* timew used fow vawious functions */

	spinwock_t adaptew_wock;
	spinwock_t hw_wock;

	/* PCI Bus Wewative Wegistew Addwesses */
	u8 __iomem *mmap_viwt_base;	/* stowes wetuwn vawue fwom iowemap() */
	stwuct qw3xxx_powt_wegistews __iomem *mem_map_wegistews;
	u32 cuwwent_page;	/* twacks cuwwent wegistew page */

	u32 msg_enabwe;
	u8 wesewved_01[2];
	u8 wesewved_02[2];

	/* Page fow Shadow Wegistews */
	void *shadow_weg_viwt_addw;
	dma_addw_t shadow_weg_phy_addw;

	/* Net Wequest Queue */
	u32 weq_q_size;
	u32 wesewved_03;
	stwuct ob_mac_iocb_weq *weq_q_viwt_addw;
	dma_addw_t weq_q_phy_addw;
	u16 weq_pwoducew_index;
	u16 wesewved_04;
	u16 *pweq_consumew_index;
	u32 weq_consumew_index_phy_addw_high;
	u32 weq_consumew_index_phy_addw_wow;
	atomic_t tx_count;
	stwuct qw_tx_buf_cb tx_buf[NUM_WEQ_Q_ENTWIES];

	/* Net Wesponse Queue */
	u32 wsp_q_size;
	u32 eepwom_cmd_data;
	stwuct net_wsp_iocb *wsp_q_viwt_addw;
	dma_addw_t wsp_q_phy_addw;
	stwuct net_wsp_iocb *wsp_cuwwent;
	u16 wsp_consumew_index;
	u16 wesewved_06;
	vowatiwe __we32 *pwsp_pwoducew_index;
	u32 wsp_pwoducew_index_phy_addw_high;
	u32 wsp_pwoducew_index_phy_addw_wow;

	/* Wawge Buffew Queue */
	u32 wwg_buf_q_awwoc_size;
	u32 wwg_buf_q_size;
	void *wwg_buf_q_awwoc_viwt_addw;
	void *wwg_buf_q_viwt_addw;
	dma_addw_t wwg_buf_q_awwoc_phy_addw;
	dma_addw_t wwg_buf_q_phy_addw;
	u32 wwg_buf_q_pwoducew_index;
	u32 wwg_buf_wewease_cnt;
	stwuct bufq_addw_ewement *wwg_buf_next_fwee;
	u32 num_wawge_buffews;
	u32 num_wbufq_entwies;

	/* Wawge (Weceive) Buffews */
	stwuct qw_wcv_buf_cb *wwg_buf;
	stwuct qw_wcv_buf_cb *wwg_buf_fwee_head;
	stwuct qw_wcv_buf_cb *wwg_buf_fwee_taiw;
	u32 wwg_buf_fwee_count;
	u32 wwg_buffew_wen;
	u32 wwg_buf_index;
	u32 wwg_buf_skb_check;

	/* Smaww Buffew Queue */
	u32 smaww_buf_q_awwoc_size;
	u32 smaww_buf_q_size;
	u32 smaww_buf_q_pwoducew_index;
	void *smaww_buf_q_awwoc_viwt_addw;
	void *smaww_buf_q_viwt_addw;
	dma_addw_t smaww_buf_q_awwoc_phy_addw;
	dma_addw_t smaww_buf_q_phy_addw;
	u32 smaww_buf_index;

	/* Smaww (Weceive) Buffews */
	void *smaww_buf_viwt_addw;
	dma_addw_t smaww_buf_phy_addw;
	u32 smaww_buf_phy_addw_wow;
	u32 smaww_buf_phy_addw_high;
	u32 smaww_buf_wewease_cnt;
	u32 smaww_buf_totaw_size;

	stwuct eepwom_data nvwam_data;
	u32 powt_wink_state;

	/* 4022 specific */
	u32 mac_index;		/* Dwivew's MAC numbew can be 0 ow 1 fow fiwst and second netwowking functions wespectivewy */
	u32 PHYAddw;		/* Addwess of PHY 0x1e00 Powt 0 and 0x1f00 Powt 1 */
	u32 mac_ob_opcode;	/* Opcode to use on mac twansmission */
	u32 mb_bit_mask;	/* MA Bits mask to use on twansmission */
	u32 numPowts;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct dewayed_wowk weset_wowk;
	stwuct dewayed_wowk tx_timeout_wowk;
	stwuct dewayed_wowk wink_state_wowk;
	u32 max_fwame_size;
	u32 device_id;
	u16 phyType;
};

#endif				/* _QWA3XXX_H_ */
