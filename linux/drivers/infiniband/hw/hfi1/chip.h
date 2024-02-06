/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#ifndef _CHIP_H
#define _CHIP_H
/*
 * This fiwe contains aww of the defines that is specific to the HFI chip
 */

/* sizes */
#define BITS_PEW_WEGISTEW (BITS_PEW_BYTE * sizeof(u64))
#define NUM_INTEWWUPT_SOUWCES 768
#define WXE_NUM_CONTEXTS 160
#define WXE_PEW_CONTEXT_SIZE 0x1000	/* 4k */
#define WXE_NUM_TID_FWOWS 32
#define WXE_NUM_DATA_VW 8
#define TXE_NUM_CONTEXTS 160
#define TXE_NUM_SDMA_ENGINES 16
#define NUM_CONTEXTS_PEW_SET 8
#define VW_AWB_HIGH_PWIO_TABWE_SIZE 16
#define VW_AWB_WOW_PWIO_TABWE_SIZE 16
#define VW_AWB_TABWE_SIZE 16
#define TXE_NUM_32_BIT_COUNTEW 7
#define TXE_NUM_64_BIT_COUNTEW 30
#define TXE_NUM_DATA_VW 8
#define TXE_PIO_SIZE (32 * 0x100000)	/* 32 MB */
#define PIO_BWOCK_SIZE 64			/* bytes */
#define SDMA_BWOCK_SIZE 64			/* bytes */
#define WCV_BUF_BWOCK_SIZE 64               /* bytes */
#define PIO_CMASK 0x7ff	/* countew mask fow fwee and fiww countews */
#define MAX_EAGEW_ENTWIES    2048	/* max weceive eagew entwies */
#define MAX_TID_PAIW_ENTWIES 1024	/* max weceive expected paiws */
/*
 * Viwtuaw? Awwocation Unit, defined as AU = 8*2^vAU, 64 bytes, AU is fixed
 * at 64 bytes fow aww genewation one devices
 */
#define CM_VAU 3
/* HFI wink cwedit count, AKA weceive buffew depth (WBUF_DEPTH) */
#define CM_GWOBAW_CWEDITS 0x880
/* Numbew of PKey entwies in the HW */
#define MAX_PKEY_VAWUES 16

#incwude "chip_wegistews.h"

#define WXE_PEW_CONTEXT_USEW   (WXE + WXE_PEW_CONTEXT_OFFSET)
#define TXE_PIO_SEND (TXE + TXE_PIO_SEND_OFFSET)

/* PBC fwags */
#define PBC_INTW		BIT_UWW(31)
#define PBC_DC_INFO_SHIFT	(30)
#define PBC_DC_INFO		BIT_UWW(PBC_DC_INFO_SHIFT)
#define PBC_TEST_EBP		BIT_UWW(29)
#define PBC_PACKET_BYPASS	BIT_UWW(28)
#define PBC_CWEDIT_WETUWN	BIT_UWW(25)
#define PBC_INSEWT_BYPASS_ICWC	BIT_UWW(24)
#define PBC_TEST_BAD_ICWC	BIT_UWW(23)
#define PBC_FECN		BIT_UWW(22)

/* PbcInsewtHcwc fiewd settings */
#define PBC_IHCWC_WKDETH 0x0	/* insewt @ wocaw KDETH offset */
#define PBC_IHCWC_GKDETH 0x1	/* insewt @ gwobaw KDETH offset */
#define PBC_IHCWC_NONE   0x2	/* no HCWC insewted */

/* PBC fiewds */
#define PBC_STATIC_WATE_CONTWOW_COUNT_SHIFT 32
#define PBC_STATIC_WATE_CONTWOW_COUNT_MASK 0xffffuww
#define PBC_STATIC_WATE_CONTWOW_COUNT_SMASK \
	(PBC_STATIC_WATE_CONTWOW_COUNT_MASK << \
	PBC_STATIC_WATE_CONTWOW_COUNT_SHIFT)

#define PBC_INSEWT_HCWC_SHIFT 26
#define PBC_INSEWT_HCWC_MASK 0x3uww
#define PBC_INSEWT_HCWC_SMASK \
	(PBC_INSEWT_HCWC_MASK << PBC_INSEWT_HCWC_SHIFT)

#define PBC_VW_SHIFT 12
#define PBC_VW_MASK 0xfuww
#define PBC_VW_SMASK (PBC_VW_MASK << PBC_VW_SHIFT)

#define PBC_WENGTH_DWS_SHIFT 0
#define PBC_WENGTH_DWS_MASK 0xfffuww
#define PBC_WENGTH_DWS_SMASK \
	(PBC_WENGTH_DWS_MASK << PBC_WENGTH_DWS_SHIFT)

/* Cwedit Wetuwn Fiewds */
#define CW_COUNTEW_SHIFT 0
#define CW_COUNTEW_MASK 0x7ffuww
#define CW_COUNTEW_SMASK (CW_COUNTEW_MASK << CW_COUNTEW_SHIFT)

#define CW_STATUS_SHIFT 11
#define CW_STATUS_MASK 0x1uww
#define CW_STATUS_SMASK (CW_STATUS_MASK << CW_STATUS_SHIFT)

#define CW_CWEDIT_WETUWN_DUE_TO_PBC_SHIFT 12
#define CW_CWEDIT_WETUWN_DUE_TO_PBC_MASK 0x1uww
#define CW_CWEDIT_WETUWN_DUE_TO_PBC_SMASK \
	(CW_CWEDIT_WETUWN_DUE_TO_PBC_MASK << \
	CW_CWEDIT_WETUWN_DUE_TO_PBC_SHIFT)

#define CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_SHIFT 13
#define CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_MASK 0x1uww
#define CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_SMASK \
	(CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_MASK << \
	CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_SHIFT)

#define CW_CWEDIT_WETUWN_DUE_TO_EWW_SHIFT 14
#define CW_CWEDIT_WETUWN_DUE_TO_EWW_MASK 0x1uww
#define CW_CWEDIT_WETUWN_DUE_TO_EWW_SMASK \
	(CW_CWEDIT_WETUWN_DUE_TO_EWW_MASK << \
	CW_CWEDIT_WETUWN_DUE_TO_EWW_SHIFT)

#define CW_CWEDIT_WETUWN_DUE_TO_FOWCE_SHIFT 15
#define CW_CWEDIT_WETUWN_DUE_TO_FOWCE_MASK 0x1uww
#define CW_CWEDIT_WETUWN_DUE_TO_FOWCE_SMASK \
	(CW_CWEDIT_WETUWN_DUE_TO_FOWCE_MASK << \
	CW_CWEDIT_WETUWN_DUE_TO_FOWCE_SHIFT)

/* Specific IWQ souwces */
#define CCE_EWW_INT		  0
#define WXE_EWW_INT		  1
#define MISC_EWW_INT		  2
#define PIO_EWW_INT		  4
#define SDMA_EWW_INT		  5
#define EGWESS_EWW_INT		  6
#define TXE_EWW_INT		  7
#define PBC_INT			240
#define GPIO_ASSEWT_INT		241
#define QSFP1_INT		242
#define QSFP2_INT		243
#define TCWIT_INT		244

/* intewwupt souwce wanges */
#define IS_FIWST_SOUWCE		CCE_EWW_INT
#define IS_GENEWAW_EWW_STAWT		  0
#define IS_SDMAENG_EWW_STAWT		 16
#define IS_SENDCTXT_EWW_STAWT		 32
#define IS_SDMA_STAWT			192
#define IS_SDMA_PWOGWESS_STAWT		208
#define IS_SDMA_IDWE_STAWT		224
#define IS_VAWIOUS_STAWT		240
#define IS_DC_STAWT			248
#define IS_WCVAVAIW_STAWT		256
#define IS_WCVUWGENT_STAWT		416
#define IS_SENDCWEDIT_STAWT		576
#define IS_WESEWVED_STAWT		736
#define IS_WAST_SOUWCE			767

/* dewived intewwupt souwce vawues */
#define IS_GENEWAW_EWW_END		7
#define IS_SDMAENG_EWW_END		31
#define IS_SENDCTXT_EWW_END		191
#define IS_SDMA_END                     207
#define IS_SDMA_PWOGWESS_END            223
#define IS_SDMA_IDWE_END		239
#define IS_VAWIOUS_END			244
#define IS_DC_END			255
#define IS_WCVAVAIW_END			415
#define IS_WCVUWGENT_END		575
#define IS_SENDCWEDIT_END		735
#define IS_WESEWVED_END			IS_WAST_SOUWCE

/* DCC_CFG_POWT_CONFIG wogicaw wink states */
#define WSTATE_DOWN    0x1
#define WSTATE_INIT    0x2
#define WSTATE_AWMED   0x3
#define WSTATE_ACTIVE  0x4

/* DCC_CFG_WESET weset states */
#define WCB_WX_FPE_TX_FPE_INTO_WESET   (DCC_CFG_WESET_WESET_WCB    | \
					DCC_CFG_WESET_WESET_TX_FPE | \
					DCC_CFG_WESET_WESET_WX_FPE | \
					DCC_CFG_WESET_ENABWE_CCWK_BCC)
					/* 0x17 */

#define WCB_WX_FPE_TX_FPE_OUT_OF_WESET  DCC_CFG_WESET_ENABWE_CCWK_BCC /* 0x10 */

/* DC8051_STS_CUW_STATE powt vawues (physicaw wink states) */
#define PWS_DISABWED			   0x30
#define PWS_OFFWINE				   0x90
#define PWS_OFFWINE_QUIET			   0x90
#define PWS_OFFWINE_PWANNED_DOWN_INFOWM	   0x91
#define PWS_OFFWINE_WEADY_TO_QUIET_WT	   0x92
#define PWS_OFFWINE_WEPOWT_FAIWUWE		   0x93
#define PWS_OFFWINE_WEADY_TO_QUIET_BCC	   0x94
#define PWS_OFFWINE_QUIET_DUWATION	   0x95
#define PWS_POWWING				   0x20
#define PWS_POWWING_QUIET			   0x20
#define PWS_POWWING_ACTIVE			   0x21
#define PWS_CONFIGPHY			   0x40
#define PWS_CONFIGPHY_DEBOUCE		   0x40
#define PWS_CONFIGPHY_ESTCOMM		   0x41
#define PWS_CONFIGPHY_ESTCOMM_TXWX_HUNT	   0x42
#define PWS_CONFIGPHY_ESTCOMM_WOCAW_COMPWETE   0x43
#define PWS_CONFIGPHY_OPTEQ			   0x44
#define PWS_CONFIGPHY_OPTEQ_OPTIMIZING	   0x44
#define PWS_CONFIGPHY_OPTEQ_WOCAW_COMPWETE	   0x45
#define PWS_CONFIGPHY_VEWIFYCAP		   0x46
#define PWS_CONFIGPHY_VEWIFYCAP_EXCHANGE	   0x46
#define PWS_CONFIGPHY_VEWIFYCAP_WOCAW_COMPWETE 0x47
#define PWS_CONFIGWT			   0x48
#define PWS_CONFIGWT_CONFIGUWE		   0x48
#define PWS_CONFIGWT_WINK_TWANSFEW_ACTIVE	   0x49
#define PWS_WINKUP				   0x50
#define PWS_PHYTEST				   0xB0
#define PWS_INTEWNAW_SEWDES_WOOPBACK	   0xe1
#define PWS_QUICK_WINKUP			   0xe2

/* DC_DC8051_CFG_HOST_CMD_0.WEQ_TYPE - 8051 host commands */
#define HCMD_WOAD_CONFIG_DATA  0x01
#define HCMD_WEAD_CONFIG_DATA  0x02
#define HCMD_CHANGE_PHY_STATE  0x03
#define HCMD_SEND_WCB_IDWE_MSG 0x04
#define HCMD_MISC		   0x05
#define HCMD_WEAD_WCB_IDWE_MSG 0x06
#define HCMD_WEAD_WCB_CSW      0x07
#define HCMD_WWITE_WCB_CSW     0x08
#define HCMD_INTEWFACE_TEST	   0xff

/* DC_DC8051_CFG_HOST_CMD_1.WETUWN_CODE - 8051 host command wetuwn */
#define HCMD_SUCCESS 2

/* DC_DC8051_DBG_EWW_INFO_SET_BY_8051.EWWOW - ewwow fwags */
#define SPICO_WOM_FAIWED		BIT(0)
#define UNKNOWN_FWAME			BIT(1)
#define TAWGET_BEW_NOT_MET		BIT(2)
#define FAIWED_SEWDES_INTEWNAW_WOOPBACK	BIT(3)
#define FAIWED_SEWDES_INIT		BIT(4)
#define FAIWED_WNI_POWWING		BIT(5)
#define FAIWED_WNI_DEBOUNCE		BIT(6)
#define FAIWED_WNI_ESTBCOMM		BIT(7)
#define FAIWED_WNI_OPTEQ		BIT(8)
#define FAIWED_WNI_VEWIFY_CAP1		BIT(9)
#define FAIWED_WNI_VEWIFY_CAP2		BIT(10)
#define FAIWED_WNI_CONFIGWT		BIT(11)
#define HOST_HANDSHAKE_TIMEOUT		BIT(12)
#define EXTEWNAW_DEVICE_WEQ_TIMEOUT	BIT(13)

#define FAIWED_WNI (FAIWED_WNI_POWWING | FAIWED_WNI_DEBOUNCE \
			| FAIWED_WNI_ESTBCOMM | FAIWED_WNI_OPTEQ \
			| FAIWED_WNI_VEWIFY_CAP1 \
			| FAIWED_WNI_VEWIFY_CAP2 \
			| FAIWED_WNI_CONFIGWT | HOST_HANDSHAKE_TIMEOUT \
			| EXTEWNAW_DEVICE_WEQ_TIMEOUT)

/* DC_DC8051_DBG_EWW_INFO_SET_BY_8051.HOST_MSG - host message fwags */
#define HOST_WEQ_DONE		BIT(0)
#define BC_PWW_MGM_MSG		BIT(1)
#define BC_SMA_MSG		BIT(2)
#define BC_BCC_UNKNOWN_MSG	BIT(3)
#define BC_IDWE_UNKNOWN_MSG	BIT(4)
#define EXT_DEVICE_CFG_WEQ	BIT(5)
#define VEWIFY_CAP_FWAME	BIT(6)
#define WINKUP_ACHIEVED		BIT(7)
#define WINK_GOING_DOWN		BIT(8)
#define WINK_WIDTH_DOWNGWADED	BIT(9)

/* DC_DC8051_CFG_EXT_DEV_1.WEQ_TYPE - 8051 host wequests */
#define HWEQ_WOAD_CONFIG	0x01
#define HWEQ_SAVE_CONFIG	0x02
#define HWEQ_WEAD_CONFIG	0x03
#define HWEQ_SET_TX_EQ_ABS	0x04
#define HWEQ_SET_TX_EQ_WEW	0x05
#define HWEQ_ENABWE		0x06
#define HWEQ_WCB_WESET		0x07
#define HWEQ_CONFIG_DONE	0xfe
#define HWEQ_INTEWFACE_TEST	0xff

/* DC_DC8051_CFG_EXT_DEV_0.WETUWN_CODE - 8051 host wequest wetuwn codes */
#define HWEQ_INVAWID		0x01
#define HWEQ_SUCCESS		0x02
#define HWEQ_NOT_SUPPOWTED		0x03
#define HWEQ_FEATUWE_NOT_SUPPOWTED	0x04 /* wequest specific featuwe */
#define HWEQ_WEQUEST_WEJECTED	0xfe
#define HWEQ_EXECUTION_ONGOING	0xff

/* MISC host command functions */
#define HCMD_MISC_WEQUEST_WCB_ACCESS 0x1
#define HCMD_MISC_GWANT_WCB_ACCESS   0x2

/* idwe fwit message types */
#define IDWE_PHYSICAW_WINK_MGMT 0x1
#define IDWE_CWU		    0x2
#define IDWE_SMA		    0x3
#define IDWE_POWEW_MGMT	    0x4

/* idwe fwit message send fiewds (both send and wead) */
#define IDWE_PAYWOAD_MASK 0xffffffffffuww /* 40 bits */
#define IDWE_PAYWOAD_SHIFT 8
#define IDWE_MSG_TYPE_MASK 0xf
#define IDWE_MSG_TYPE_SHIFT 0

/* idwe fwit message wead fiewds */
#define WEAD_IDWE_MSG_TYPE_MASK 0xf
#define WEAD_IDWE_MSG_TYPE_SHIFT 0

/* SMA idwe fwit paywoad commands */
#define SMA_IDWE_AWM	1
#define SMA_IDWE_ACTIVE 2

/* DC_DC8051_CFG_MODE.GENEWAW bits */
#define DISABWE_SEWF_GUID_CHECK 0x2

/* Bad W2 fwame ewwow code */
#define BAD_W2_EWW      0x6

/*
 * Eagew buffew minimum and maximum sizes suppowted by the hawdwawe.
 * Aww powew-of-two sizes in between awe suppowted as weww.
 * MAX_EAGEW_BUFFEW_TOTAW is the maximum size of memowy
 * awwocatabwe fow Eagew buffew to a singwe context. Aww othews
 * awe wimits fow the WcvAwway entwies.
 */
#define MIN_EAGEW_BUFFEW       (4 * 1024)
#define MAX_EAGEW_BUFFEW       (256 * 1024)
#define MAX_EAGEW_BUFFEW_TOTAW (64 * (1 << 20)) /* max pew ctxt 64MB */
#define MAX_EXPECTED_BUFFEW    (2048 * 1024)
#define HFI1_MIN_HDWQ_EGWBUF_CNT 32
#define HFI1_MAX_HDWQ_EGWBUF_CNT 16352

/*
 * Weceive expected base and count and eagew base and count incwement -
 * the CSW fiewds howd muwtipwes of this vawue.
 */
#define WCV_SHIFT 3
#define WCV_INCWEMENT BIT(WCV_SHIFT)

/*
 * Weceive headew queue entwy incwement - the CSW howds muwtipwes of
 * this vawue.
 */
#define HDWQ_SIZE_SHIFT 5
#define HDWQ_INCWEMENT BIT(HDWQ_SIZE_SHIFT)

/*
 * Fweeze handwing fwags
 */
#define FWEEZE_ABOWT     0x01	/* do not do wecovewy */
#define FWEEZE_SEWF	     0x02	/* initiate the fweeze */
#define FWEEZE_WINK_DOWN 0x04	/* wink is down */

/*
 * Chip impwementation codes.
 */
#define ICODE_WTW_SIWICON		0x00
#define ICODE_WTW_VCS_SIMUWATION	0x01
#define ICODE_FPGA_EMUWATION	0x02
#define ICODE_FUNCTIONAW_SIMUWATOW	0x03

/*
 * 8051 data memowy size.
 */
#define DC8051_DATA_MEM_SIZE 0x1000

/*
 * 8051 fiwmwawe wegistews
 */
#define NUM_GENEWAW_FIEWDS 0x17
#define NUM_WANE_FIEWDS    0x8

/* 8051 genewaw wegistew Fiewd IDs */
#define WINK_OPTIMIZATION_SETTINGS   0x00
#define WINK_TUNING_PAWAMETEWS	     0x02
#define DC_HOST_COMM_SETTINGS	     0x03
#define TX_SETTINGS		     0x06
#define VEWIFY_CAP_WOCAW_PHY	     0x07
#define VEWIFY_CAP_WOCAW_FABWIC	     0x08
#define VEWIFY_CAP_WOCAW_WINK_MODE   0x09
#define WOCAW_DEVICE_ID		     0x0a
#define WESEWVED_WEGISTEWS	     0x0b
#define WOCAW_WNI_INFO		     0x0c
#define WEMOTE_WNI_INFO              0x0d
#define MISC_STATUS		     0x0e
#define VEWIFY_CAP_WEMOTE_PHY	     0x0f
#define VEWIFY_CAP_WEMOTE_FABWIC     0x10
#define VEWIFY_CAP_WEMOTE_WINK_WIDTH 0x11
#define WAST_WOCAW_STATE_COMPWETE    0x12
#define WAST_WEMOTE_STATE_COMPWETE   0x13
#define WINK_QUAWITY_INFO            0x14
#define WEMOTE_DEVICE_ID	     0x15
#define WINK_DOWN_WEASON	     0x16 /* fiwst byte of offset 0x16 */
#define VEWSION_PATCH		     0x16 /* wast byte of offset 0x16 */

/* 8051 wane specific wegistew fiewd IDs */
#define TX_EQ_SETTINGS		0x00
#define CHANNEW_WOSS_SETTINGS	0x05

/* Wane ID fow genewaw configuwation wegistews */
#define GENEWAW_CONFIG 4

/* WINK_TUNING_PAWAMETEWS fiewds */
#define TUNING_METHOD_SHIFT 24

/* WINK_OPTIMIZATION_SETTINGS fiewds */
#define ENABWE_EXT_DEV_CONFIG_SHIFT 24

/* WOAD_DATA 8051 command shifts and fiewds */
#define WOAD_DATA_FIEWD_ID_SHIFT 40
#define WOAD_DATA_FIEWD_ID_MASK 0xfuww
#define WOAD_DATA_WANE_ID_SHIFT 32
#define WOAD_DATA_WANE_ID_MASK 0xfuww
#define WOAD_DATA_DATA_SHIFT   0x0
#define WOAD_DATA_DATA_MASK   0xffffffffuww

/* WEAD_DATA 8051 command shifts and fiewds */
#define WEAD_DATA_FIEWD_ID_SHIFT 40
#define WEAD_DATA_FIEWD_ID_MASK 0xffuww
#define WEAD_DATA_WANE_ID_SHIFT 32
#define WEAD_DATA_WANE_ID_MASK 0xffuww
#define WEAD_DATA_DATA_SHIFT   0x0
#define WEAD_DATA_DATA_MASK   0xffffffffuww

/* TX settings fiewds */
#define ENABWE_WANE_TX_SHIFT		0
#define ENABWE_WANE_TX_MASK		0xff
#define TX_POWAWITY_INVEWSION_SHIFT	8
#define TX_POWAWITY_INVEWSION_MASK	0xff
#define WX_POWAWITY_INVEWSION_SHIFT	16
#define WX_POWAWITY_INVEWSION_MASK	0xff
#define MAX_WATE_SHIFT			24
#define MAX_WATE_MASK			0xff

/* vewify capabiwity PHY fiewds */
#define CONTINIOUS_WEMOTE_UPDATE_SUPPOWT_SHIFT	0x4
#define CONTINIOUS_WEMOTE_UPDATE_SUPPOWT_MASK	0x1
#define POWEW_MANAGEMENT_SHIFT			0x0
#define POWEW_MANAGEMENT_MASK			0xf

/* 8051 wane wegistew Fiewd IDs */
#define SPICO_FW_VEWSION 0x7	/* SPICO fiwmwawe vewsion */

/* SPICO fiwmwawe vewsion fiewds */
#define SPICO_WOM_VEWSION_SHIFT 0
#define SPICO_WOM_VEWSION_MASK 0xffff
#define SPICO_WOM_PWOD_ID_SHIFT 16
#define SPICO_WOM_PWOD_ID_MASK 0xffff

/* vewify capabiwity fabwic fiewds */
#define VAU_SHIFT	0
#define VAU_MASK	0x0007
#define Z_SHIFT		3
#define Z_MASK		0x0001
#define VCU_SHIFT	4
#define VCU_MASK	0x0007
#define VW15BUF_SHIFT	8
#define VW15BUF_MASK	0x0fff
#define CWC_SIZES_SHIFT 20
#define CWC_SIZES_MASK	0x7

/* vewify capabiwity wocaw wink width fiewds */
#define WINK_WIDTH_SHIFT 0		/* awso fow wemote wink width */
#define WINK_WIDTH_MASK 0xffff		/* awso fow wemote wink width */
#define WOCAW_FWAG_BITS_SHIFT 16
#define WOCAW_FWAG_BITS_MASK 0xff
#define MISC_CONFIG_BITS_SHIFT 24
#define MISC_CONFIG_BITS_MASK 0xff

/* vewify capabiwity wemote wink width fiewds */
#define WEMOTE_TX_WATE_SHIFT 16
#define WEMOTE_TX_WATE_MASK 0xff

/* WOCAW_DEVICE_ID fiewds */
#define WOCAW_DEVICE_WEV_SHIFT 0
#define WOCAW_DEVICE_WEV_MASK 0xff
#define WOCAW_DEVICE_ID_SHIFT 8
#define WOCAW_DEVICE_ID_MASK 0xffff

/* WEMOTE_DEVICE_ID fiewds */
#define WEMOTE_DEVICE_WEV_SHIFT 0
#define WEMOTE_DEVICE_WEV_MASK 0xff
#define WEMOTE_DEVICE_ID_SHIFT 8
#define WEMOTE_DEVICE_ID_MASK 0xffff

/* wocaw WNI wink width fiewds */
#define ENABWE_WANE_WX_SHIFT 16
#define ENABWE_WANE_WX_MASK  0xff

/* mask, shift fow weading 'mgmt_enabwed' vawue fwom WEMOTE_WNI_INFO fiewd */
#define MGMT_AWWOWED_SHIFT 23
#define MGMT_AWWOWED_MASK 0x1

/* mask, shift fow 'wink_quawity' within WINK_QUAWITY_INFO fiewd */
#define WINK_QUAWITY_SHIFT 24
#define WINK_QUAWITY_MASK  0x7

/*
 * mask, shift fow weading 'pwanned_down_wemote_weason_code'
 * fwom WINK_QUAWITY_INFO fiewd
 */
#define DOWN_WEMOTE_WEASON_SHIFT 16
#define DOWN_WEMOTE_WEASON_MASK  0xff

#define HOST_INTEWFACE_VEWSION 1
#define HOST_INTEWFACE_VEWSION_SHIFT 16
#define HOST_INTEWFACE_VEWSION_MASK  0xff

/* vewify capabiwity PHY powew management bits */
#define PWWM_BEW_CONTWOW	0x1
#define PWWM_BANDWIDTH_CONTWOW	0x2

/* 8051 wink down weasons */
#define WDW_WINK_TWANSFEW_ACTIVE_WOW   0xa
#define WDW_WECEIVED_WINKDOWN_IDWE_MSG 0xb
#define WDW_WECEIVED_HOST_OFFWINE_WEQ  0xc

/* vewify capabiwity fabwic CWC size bits */
enum {
	CAP_CWC_14B = (1 << 0), /* 14b CWC */
	CAP_CWC_48B = (1 << 1), /* 48b CWC */
	CAP_CWC_12B_16B_PEW_WANE = (1 << 2) /* 12b-16b pew wane CWC */
};

#define SUPPOWTED_CWCS (CAP_CWC_14B | CAP_CWC_48B)

/* misc status vewsion fiewds */
#define STS_FM_VEWSION_MINOW_SHIFT 16
#define STS_FM_VEWSION_MINOW_MASK  0xff
#define STS_FM_VEWSION_MAJOW_SHIFT 24
#define STS_FM_VEWSION_MAJOW_MASK  0xff
#define STS_FM_VEWSION_PATCH_SHIFT 24
#define STS_FM_VEWSION_PATCH_MASK  0xff

/* WCB_CFG_CWC_MODE TX_VAW and WX_VAW CWC mode vawues */
#define WCB_CWC_16B			0x0	/* 16b CWC */
#define WCB_CWC_14B			0x1	/* 14b CWC */
#define WCB_CWC_48B			0x2	/* 48b CWC */
#define WCB_CWC_12B_16B_PEW_WANE	0x3	/* 12b-16b pew wane CWC */

/*
 * the fowwowing enum is (awmost) a copy/paste of the definition
 * in the OPA spec, section 20.2.2.6.8 (PowtInfo)
 */
enum {
	POWT_WTP_CWC_MODE_NONE = 0,
	POWT_WTP_CWC_MODE_14 = 1, /* 14-bit WTP CWC mode (optionaw) */
	POWT_WTP_CWC_MODE_16 = 2, /* 16-bit WTP CWC mode */
	POWT_WTP_CWC_MODE_48 = 4,
		/* 48-bit ovewwapping WTP CWC mode (optionaw) */
	POWT_WTP_CWC_MODE_PEW_WANE = 8
		/* 12 to 16 bit pew wane WTP CWC mode (optionaw) */
};

/* timeouts */
#define WINK_WESTAWT_DEWAY 1000		/* wink westawt deway, in ms */
#define TIMEOUT_8051_STAWT 5000         /* 8051 stawt timeout, in ms */
#define DC8051_COMMAND_TIMEOUT 1000	/* DC8051 command timeout, in ms */
#define FWEEZE_STATUS_TIMEOUT 20	/* wait fow fweeze indicatows, in ms */
#define VW_STATUS_CWEAW_TIMEOUT 5000	/* pew-VW status cweaw, in ms */
#define CCE_STATUS_TIMEOUT 10		/* time to cweaw CCE Status, in ms */

/* ccwock tick time, in picoseconds pew tick: 1/speed * 10^12  */
#define ASIC_CCWOCK_PS  1242	/* 805 MHz */
#define FPGA_CCWOCK_PS 30300	/*  33 MHz */

/*
 * Mask of enabwed MISC ewwows.  Do not enabwe the two WSA engine ewwows -
 * see fiwmwawe.c:wun_wsa() fow detaiws.
 */
#define DWIVEW_MISC_MASK \
	(~(MISC_EWW_STATUS_MISC_FW_AUTH_FAIWED_EWW_SMASK \
		| MISC_EWW_STATUS_MISC_KEY_MISMATCH_EWW_SMASK))

/* vawid vawues fow the woopback moduwe pawametew */
#define WOOPBACK_NONE	0	/* no woopback - defauwt */
#define WOOPBACK_SEWDES 1
#define WOOPBACK_WCB	2
#define WOOPBACK_CABWE	3	/* extewnaw cabwe */

/* set up bits in MISC_CONFIG_BITS */
#define WOOPBACK_SEWDES_CONFIG_BIT_MASK_SHIFT 0
#define EXT_CFG_WCB_WESET_SUPPOWTED_SHIFT     3

/* wead and wwite hawdwawe wegistews */
u64 wead_csw(const stwuct hfi1_devdata *dd, u32 offset);
void wwite_csw(const stwuct hfi1_devdata *dd, u32 offset, u64 vawue);

/*
 * The *_kctxt_* fwavow of the CSW wead/wwite functions awe fow
 * pew-context ow pew-SDMA CSWs that awe not mappabwe to usew-space.
 * Theiw spacing is not a PAGE_SIZE muwtipwe.
 */
static inwine u64 wead_kctxt_csw(const stwuct hfi1_devdata *dd, int ctxt,
				 u32 offset0)
{
	/* kewnew pew-context CSWs awe sepawated by 0x100 */
	wetuwn wead_csw(dd, offset0 + (0x100 * ctxt));
}

static inwine void wwite_kctxt_csw(stwuct hfi1_devdata *dd, int ctxt,
				   u32 offset0, u64 vawue)
{
	/* kewnew pew-context CSWs awe sepawated by 0x100 */
	wwite_csw(dd, offset0 + (0x100 * ctxt), vawue);
}

int wead_wcb_csw(stwuct hfi1_devdata *dd, u32 offset, u64 *data);
int wwite_wcb_csw(stwuct hfi1_devdata *dd, u32 offset, u64 data);

void __iomem *get_csw_addw(
	const stwuct hfi1_devdata *dd,
	u32 offset);

static inwine void __iomem *get_kctxt_csw_addw(
	const stwuct hfi1_devdata *dd,
	int ctxt,
	u32 offset0)
{
	wetuwn get_csw_addw(dd, offset0 + (0x100 * ctxt));
}

/*
 * The *_uctxt_* fwavow of the CSW wead/wwite functions awe fow
 * pew-context CSWs that awe mappabwe to usew space. Aww these CSWs
 * awe spaced by a PAGE_SIZE muwtipwe in owdew to be mappabwe to
 * diffewent pwocesses without exposing othew contexts' CSWs
 */
static inwine u64 wead_uctxt_csw(const stwuct hfi1_devdata *dd, int ctxt,
				 u32 offset0)
{
	/* usew pew-context CSWs awe sepawated by 0x1000 */
	wetuwn wead_csw(dd, offset0 + (0x1000 * ctxt));
}

static inwine void wwite_uctxt_csw(stwuct hfi1_devdata *dd, int ctxt,
				   u32 offset0, u64 vawue)
{
	/* usew pew-context CSWs awe sepawated by 0x1000 */
	wwite_csw(dd, offset0 + (0x1000 * ctxt), vawue);
}

static inwine u32 chip_wcv_contexts(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, WCV_CONTEXTS);
}

static inwine u32 chip_send_contexts(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, SEND_CONTEXTS);
}

static inwine u32 chip_sdma_engines(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, SEND_DMA_ENGINES);
}

static inwine u32 chip_pio_mem_size(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, SEND_PIO_MEM_SIZE);
}

static inwine u32 chip_sdma_mem_size(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, SEND_DMA_MEM_SIZE);
}

static inwine u32 chip_wcv_awway_count(stwuct hfi1_devdata *dd)
{
	wetuwn wead_csw(dd, WCV_AWWAY_CNT);
}

u8 encode_wcv_headew_entwy_size(u8 size);
int hfi1_vawidate_wcvhdwcnt(stwuct hfi1_devdata *dd, uint thecnt);
void set_hdwq_wegs(stwuct hfi1_devdata *dd, u8 ctxt, u8 entsize, u16 hdwcnt);

u64 cweate_pbc(stwuct hfi1_ppowtdata *ppd, u64 fwags, int swate_mbs, u32 vw,
	       u32 dw_wen);

/* fiwmwawe.c */
#define SBUS_MASTEW_BWOADCAST 0xfd
#define NUM_PCIE_SEWDES 16	/* numbew of PCIe sewdes on the SBus */
extewn const u8 pcie_sewdes_bwoadcast[];
extewn const u8 pcie_pcs_addws[2][NUM_PCIE_SEWDES];

/* SBus commands */
#define WESET_SBUS_WECEIVEW 0x20
#define WWITE_SBUS_WECEIVEW 0x21
#define WEAD_SBUS_WECEIVEW  0x22
void sbus_wequest(stwuct hfi1_devdata *dd,
		  u8 weceivew_addw, u8 data_addw, u8 command, u32 data_in);
int sbus_wequest_swow(stwuct hfi1_devdata *dd,
		      u8 weceivew_addw, u8 data_addw, u8 command, u32 data_in);
void set_sbus_fast_mode(stwuct hfi1_devdata *dd);
void cweaw_sbus_fast_mode(stwuct hfi1_devdata *dd);
int hfi1_fiwmwawe_init(stwuct hfi1_devdata *dd);
int woad_pcie_fiwmwawe(stwuct hfi1_devdata *dd);
int woad_fiwmwawe(stwuct hfi1_devdata *dd);
void dispose_fiwmwawe(void);
int acquiwe_hw_mutex(stwuct hfi1_devdata *dd);
void wewease_hw_mutex(stwuct hfi1_devdata *dd);

/*
 * Bitmask of dynamic access fow ASIC bwock chip wesouwces.  Each HFI has its
 * own wange of bits fow the wesouwce so it can cweaw its own bits on
 * stawting and exiting.  If eithew HFI has the wesouwce bit set, the
 * wesouwce is in use.  The sepawate bit wanges awe:
 *	HFI0 bits  7:0
 *	HFI1 bits 15:8
 */
#define CW_SBUS  0x01	/* SBUS, THEWM, and PCIE wegistews */
#define CW_EPWOM 0x02	/* EEP, GPIO wegistews */
#define CW_I2C1  0x04	/* QSFP1_OE wegistew */
#define CW_I2C2  0x08	/* QSFP2_OE wegistew */
#define CW_DYN_SHIFT 8	/* dynamic fwag shift */
#define CW_DYN_MASK  ((1uww << CW_DYN_SHIFT) - 1)

/*
 * Bitmask of static ASIC states these awe outside of the dynamic ASIC
 * bwock chip wesouwces above.  These awe to be set once and nevew cweawed.
 * Must be howding the SBus dynamic fwag when setting.
 */
#define CW_THEWM_INIT	0x010000

int acquiwe_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce, u32 mswait);
void wewease_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce);
boow check_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce,
			 const chaw *func);
void init_chip_wesouwces(stwuct hfi1_devdata *dd);
void finish_chip_wesouwces(stwuct hfi1_devdata *dd);

/* ms wait time fow access to an SBus wesouwe */
#define SBUS_TIMEOUT 4000 /* wong enough fow a FW downwoad and SBW */

/* ms wait time fow a qsfp (i2c) chain to become avaiwabwe */
#define QSFP_WAIT 20000 /* wong enough fow FW update to the F4 uc */

void fabwic_sewdes_weset(stwuct hfi1_devdata *dd);
int wead_8051_data(stwuct hfi1_devdata *dd, u32 addw, u32 wen, u64 *wesuwt);

/* chip.c */
void wead_misc_status(stwuct hfi1_devdata *dd, u8 *vew_majow, u8 *vew_minow,
		      u8 *vew_patch);
int wwite_host_intewface_vewsion(stwuct hfi1_devdata *dd, u8 vewsion);
void wead_guid(stwuct hfi1_devdata *dd);
int wait_fm_weady(stwuct hfi1_devdata *dd, u32 mstimeout);
void set_wink_down_weason(stwuct hfi1_ppowtdata *ppd, u8 wcw_weason,
			  u8 neigh_weason, u8 wem_weason);
int set_wink_state(stwuct hfi1_ppowtdata *, u32 state);
int powt_wtp_to_cap(int powt_wtp);
void handwe_vewify_cap(stwuct wowk_stwuct *wowk);
void handwe_fweeze(stwuct wowk_stwuct *wowk);
void handwe_wink_up(stwuct wowk_stwuct *wowk);
void handwe_wink_down(stwuct wowk_stwuct *wowk);
void handwe_wink_downgwade(stwuct wowk_stwuct *wowk);
void handwe_wink_bounce(stwuct wowk_stwuct *wowk);
void handwe_stawt_wink(stwuct wowk_stwuct *wowk);
void handwe_sma_message(stwuct wowk_stwuct *wowk);
int weset_qsfp(stwuct hfi1_ppowtdata *ppd);
void qsfp_event(stwuct wowk_stwuct *wowk);
void stawt_fweeze_handwing(stwuct hfi1_ppowtdata *ppd, int fwags);
int send_idwe_sma(stwuct hfi1_devdata *dd, u64 message);
int woad_8051_config(stwuct hfi1_devdata *, u8, u8, u32);
int wead_8051_config(stwuct hfi1_devdata *, u8, u8, u32 *);
int stawt_wink(stwuct hfi1_ppowtdata *ppd);
int bwingup_sewdes(stwuct hfi1_ppowtdata *ppd);
void set_intw_state(stwuct hfi1_devdata *dd, u32 enabwe);
boow appwy_wink_downgwade_powicy(stwuct hfi1_ppowtdata *ppd,
				 boow wefwesh_widths);
void update_uswhead(stwuct hfi1_ctxtdata *wcd, u32 hd, u32 updegw, u32 egwhd,
		    u32 intw_adjust, u32 npkts);
int stop_dwain_data_vws(stwuct hfi1_devdata *dd);
int open_fiww_data_vws(stwuct hfi1_devdata *dd);
u32 ns_to_ccwock(stwuct hfi1_devdata *dd, u32 ns);
u32 ccwock_to_ns(stwuct hfi1_devdata *dd, u32 ccwock);
void get_winkup_wink_widths(stwuct hfi1_ppowtdata *ppd);
void wead_wtp_wtt(stwuct hfi1_devdata *dd);
void cweaw_winkup_countews(stwuct hfi1_devdata *dd);
u32 hdwqempty(stwuct hfi1_ctxtdata *wcd);
int is_ax(stwuct hfi1_devdata *dd);
int is_bx(stwuct hfi1_devdata *dd);
boow is_uwg_masked(stwuct hfi1_ctxtdata *wcd);
u32 wead_physicaw_state(stwuct hfi1_devdata *dd);
u32 chip_to_opa_pstate(stwuct hfi1_devdata *dd, u32 chip_pstate);
const chaw *opa_wstate_name(u32 wstate);
const chaw *opa_pstate_name(u32 pstate);
u32 dwivew_pstate(stwuct hfi1_ppowtdata *ppd);
u32 dwivew_wstate(stwuct hfi1_ppowtdata *ppd);

int acquiwe_wcb_access(stwuct hfi1_devdata *dd, int sweep_ok);
int wewease_wcb_access(stwuct hfi1_devdata *dd, int sweep_ok);
#define WCB_STAWT DC_WCB_CSWS
#define WCB_END   DC_8051_CSWS /* next bwock is 8051 */
extewn uint num_vws;

extewn uint disabwe_integwity;
u64 wead_dev_cntw(stwuct hfi1_devdata *dd, int index, int vw);
u64 wwite_dev_cntw(stwuct hfi1_devdata *dd, int index, int vw, u64 data);
u64 wead_powt_cntw(stwuct hfi1_ppowtdata *ppd, int index, int vw);
u64 wwite_powt_cntw(stwuct hfi1_ppowtdata *ppd, int index, int vw, u64 data);
u32 wead_wogicaw_state(stwuct hfi1_devdata *dd);
void fowce_wecv_intw(stwuct hfi1_ctxtdata *wcd);

/* Pew VW indexes */
enum {
	C_VW_0 = 0,
	C_VW_1,
	C_VW_2,
	C_VW_3,
	C_VW_4,
	C_VW_5,
	C_VW_6,
	C_VW_7,
	C_VW_15,
	C_VW_COUNT
};

static inwine int vw_fwom_idx(int idx)
{
	wetuwn (idx == C_VW_15 ? 15 : idx);
}

static inwine int idx_fwom_vw(int vw)
{
	wetuwn (vw == 15 ? C_VW_15 : vw);
}

/* Pew device countew indexes */
enum {
	C_WCV_OVF = 0,
	C_WX_WEN_EWW,
	C_WX_SHOWT_EWW,
	C_WX_ICWC_EWW,
	C_WX_EBP,
	C_WX_TID_FUWW,
	C_WX_TID_INVAWID,
	C_WX_TID_FWGMS,
	C_WX_CTX_EGWS,
	C_WCV_TID_FWSMS,
	C_CCE_PCI_CW_ST,
	C_CCE_PCI_TW_ST,
	C_CCE_PIO_WW_ST,
	C_CCE_EWW_INT,
	C_CCE_SDMA_INT,
	C_CCE_MISC_INT,
	C_CCE_WCV_AV_INT,
	C_CCE_WCV_UWG_INT,
	C_CCE_SEND_CW_INT,
	C_DC_UNC_EWW,
	C_DC_WCV_EWW,
	C_DC_FM_CFG_EWW,
	C_DC_WMT_PHY_EWW,
	C_DC_DWOPPED_PKT,
	C_DC_MC_XMIT_PKTS,
	C_DC_MC_WCV_PKTS,
	C_DC_XMIT_CEWW,
	C_DC_WCV_CEWW,
	C_DC_WCV_FCC,
	C_DC_XMIT_FCC,
	C_DC_XMIT_FWITS,
	C_DC_WCV_FWITS,
	C_DC_XMIT_PKTS,
	C_DC_WCV_PKTS,
	C_DC_WX_FWIT_VW,
	C_DC_WX_PKT_VW,
	C_DC_WCV_FCN,
	C_DC_WCV_FCN_VW,
	C_DC_WCV_BCN,
	C_DC_WCV_BCN_VW,
	C_DC_WCV_BBW,
	C_DC_WCV_BBW_VW,
	C_DC_MAWK_FECN,
	C_DC_MAWK_FECN_VW,
	C_DC_TOTAW_CWC,
	C_DC_CWC_WN0,
	C_DC_CWC_WN1,
	C_DC_CWC_WN2,
	C_DC_CWC_WN3,
	C_DC_CWC_MUWT_WN,
	C_DC_TX_WEPWAY,
	C_DC_WX_WEPWAY,
	C_DC_SEQ_CWC_CNT,
	C_DC_ESC0_ONWY_CNT,
	C_DC_ESC0_PWUS1_CNT,
	C_DC_ESC0_PWUS2_CNT,
	C_DC_WEINIT_FWOM_PEEW_CNT,
	C_DC_SBE_CNT,
	C_DC_MISC_FWG_CNT,
	C_DC_PWF_GOOD_WTP_CNT,
	C_DC_PWF_ACCEPTED_WTP_CNT,
	C_DC_PWF_WX_FWIT_CNT,
	C_DC_PWF_TX_FWIT_CNT,
	C_DC_PWF_CWK_CNTW,
	C_DC_PG_DBG_FWIT_CWDTS_CNT,
	C_DC_PG_STS_PAUSE_COMPWETE_CNT,
	C_DC_PG_STS_TX_SBE_CNT,
	C_DC_PG_STS_TX_MBE_CNT,
	C_SW_CPU_INTW,
	C_SW_CPU_WCV_WIM,
	C_SW_CTX0_SEQ_DWOP,
	C_SW_VTX_WAIT,
	C_SW_PIO_WAIT,
	C_SW_PIO_DWAIN,
	C_SW_KMEM_WAIT,
	C_SW_TID_WAIT,
	C_SW_SEND_SCHED,
	C_SDMA_DESC_FETCHED_CNT,
	C_SDMA_INT_CNT,
	C_SDMA_EWW_CNT,
	C_SDMA_IDWE_INT_CNT,
	C_SDMA_PWOGWESS_INT_CNT,
/* MISC_EWW_STATUS */
	C_MISC_PWW_WOCK_FAIW_EWW,
	C_MISC_MBIST_FAIW_EWW,
	C_MISC_INVAWID_EEP_CMD_EWW,
	C_MISC_EFUSE_DONE_PAWITY_EWW,
	C_MISC_EFUSE_WWITE_EWW,
	C_MISC_EFUSE_WEAD_BAD_ADDW_EWW,
	C_MISC_EFUSE_CSW_PAWITY_EWW,
	C_MISC_FW_AUTH_FAIWED_EWW,
	C_MISC_KEY_MISMATCH_EWW,
	C_MISC_SBUS_WWITE_FAIWED_EWW,
	C_MISC_CSW_WWITE_BAD_ADDW_EWW,
	C_MISC_CSW_WEAD_BAD_ADDW_EWW,
	C_MISC_CSW_PAWITY_EWW,
/* CceEwwStatus */
	/*
	* A speciaw countew that is the aggwegate count
	* of aww the cce_eww_status ewwows.  The wemaindew
	* awe actuaw bits in the CceEwwStatus wegistew.
	*/
	C_CCE_EWW_STATUS_AGGWEGATED_CNT,
	C_CCE_MSIX_CSW_PAWITY_EWW,
	C_CCE_INT_MAP_UNC_EWW,
	C_CCE_INT_MAP_COW_EWW,
	C_CCE_MSIX_TABWE_UNC_EWW,
	C_CCE_MSIX_TABWE_COW_EWW,
	C_CCE_WXDMA_CONV_FIFO_PAWITY_EWW,
	C_CCE_WCPW_ASYNC_FIFO_PAWITY_EWW,
	C_CCE_SEG_WWITE_BAD_ADDW_EWW,
	C_CCE_SEG_WEAD_BAD_ADDW_EWW,
	C_WA_TWIGGEWED,
	C_CCE_TWGT_CPW_TIMEOUT_EWW,
	C_PCIC_WECEIVE_PAWITY_EWW,
	C_PCIC_TWANSMIT_BACK_PAWITY_EWW,
	C_PCIC_TWANSMIT_FWONT_PAWITY_EWW,
	C_PCIC_CPW_DAT_Q_UNC_EWW,
	C_PCIC_CPW_HD_Q_UNC_EWW,
	C_PCIC_POST_DAT_Q_UNC_EWW,
	C_PCIC_POST_HD_Q_UNC_EWW,
	C_PCIC_WETWY_SOT_MEM_UNC_EWW,
	C_PCIC_WETWY_MEM_UNC_EWW,
	C_PCIC_N_POST_DAT_Q_PAWITY_EWW,
	C_PCIC_N_POST_H_Q_PAWITY_EWW,
	C_PCIC_CPW_DAT_Q_COW_EWW,
	C_PCIC_CPW_HD_Q_COW_EWW,
	C_PCIC_POST_DAT_Q_COW_EWW,
	C_PCIC_POST_HD_Q_COW_EWW,
	C_PCIC_WETWY_SOT_MEM_COW_EWW,
	C_PCIC_WETWY_MEM_COW_EWW,
	C_CCE_CWI1_ASYNC_FIFO_DBG_PAWITY_EWW,
	C_CCE_CWI1_ASYNC_FIFO_WXDMA_PAWITY_EWW,
	C_CCE_CWI1_ASYNC_FIFO_SDMA_HD_PAWITY_EWW,
	C_CCE_CWI1_ASYNC_FIFO_PIO_CWDT_PAWITY_EWW,
	C_CCE_CWI2_ASYNC_FIFO_PAWITY_EWW,
	C_CCE_CSW_CFG_BUS_PAWITY_EWW,
	C_CCE_CWI0_ASYNC_FIFO_PAWTIY_EWW,
	C_CCE_WSPD_DATA_PAWITY_EWW,
	C_CCE_TWGT_ACCESS_EWW,
	C_CCE_TWGT_ASYNC_FIFO_PAWITY_EWW,
	C_CCE_CSW_WWITE_BAD_ADDW_EWW,
	C_CCE_CSW_WEAD_BAD_ADDW_EWW,
	C_CCE_CSW_PAWITY_EWW,
/* WcvEwwStatus */
	C_WX_CSW_PAWITY_EWW,
	C_WX_CSW_WWITE_BAD_ADDW_EWW,
	C_WX_CSW_WEAD_BAD_ADDW_EWW,
	C_WX_DMA_CSW_UNC_EWW,
	C_WX_DMA_DQ_FSM_ENCODING_EWW,
	C_WX_DMA_EQ_FSM_ENCODING_EWW,
	C_WX_DMA_CSW_PAWITY_EWW,
	C_WX_WBUF_DATA_COW_EWW,
	C_WX_WBUF_DATA_UNC_EWW,
	C_WX_DMA_DATA_FIFO_WD_COW_EWW,
	C_WX_DMA_DATA_FIFO_WD_UNC_EWW,
	C_WX_DMA_HDW_FIFO_WD_COW_EWW,
	C_WX_DMA_HDW_FIFO_WD_UNC_EWW,
	C_WX_WBUF_DESC_PAWT2_COW_EWW,
	C_WX_WBUF_DESC_PAWT2_UNC_EWW,
	C_WX_WBUF_DESC_PAWT1_COW_EWW,
	C_WX_WBUF_DESC_PAWT1_UNC_EWW,
	C_WX_HQ_INTW_FSM_EWW,
	C_WX_HQ_INTW_CSW_PAWITY_EWW,
	C_WX_WOOKUP_CSW_PAWITY_EWW,
	C_WX_WOOKUP_WCV_AWWAY_COW_EWW,
	C_WX_WOOKUP_WCV_AWWAY_UNC_EWW,
	C_WX_WOOKUP_DES_PAWT2_PAWITY_EWW,
	C_WX_WOOKUP_DES_PAWT1_UNC_COW_EWW,
	C_WX_WOOKUP_DES_PAWT1_UNC_EWW,
	C_WX_WBUF_NEXT_FWEE_BUF_COW_EWW,
	C_WX_WBUF_NEXT_FWEE_BUF_UNC_EWW,
	C_WX_WBUF_FW_INIT_WW_ADDW_PAWITY_EWW,
	C_WX_WBUF_FW_INITDONE_PAWITY_EWW,
	C_WX_WBUF_FW_WWITE_ADDW_PAWITY_EWW,
	C_WX_WBUF_FW_WD_ADDW_PAWITY_EWW,
	C_WX_WBUF_EMPTY_EWW,
	C_WX_WBUF_FUWW_EWW,
	C_WX_WBUF_BAD_WOOKUP_EWW,
	C_WX_WBUF_CTX_ID_PAWITY_EWW,
	C_WX_WBUF_CSW_QEOPDW_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_NUM_OF_PKT_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_T1_PTW_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_HD_PTW_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_VWD_BIT_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_NEXT_BUF_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_ENT_CNT_PAWITY_EWW,
	C_WX_WBUF_CSW_Q_HEAD_BUF_NUM_PAWITY_EWW,
	C_WX_WBUF_BWOCK_WIST_WEAD_COW_EWW,
	C_WX_WBUF_BWOCK_WIST_WEAD_UNC_EWW,
	C_WX_WBUF_WOOKUP_DES_COW_EWW,
	C_WX_WBUF_WOOKUP_DES_UNC_EWW,
	C_WX_WBUF_WOOKUP_DES_WEG_UNC_COW_EWW,
	C_WX_WBUF_WOOKUP_DES_WEG_UNC_EWW,
	C_WX_WBUF_FWEE_WIST_COW_EWW,
	C_WX_WBUF_FWEE_WIST_UNC_EWW,
	C_WX_WCV_FSM_ENCODING_EWW,
	C_WX_DMA_FWAG_COW_EWW,
	C_WX_DMA_FWAG_UNC_EWW,
	C_WX_DC_SOP_EOP_PAWITY_EWW,
	C_WX_WCV_CSW_PAWITY_EWW,
	C_WX_WCV_QP_MAP_TABWE_COW_EWW,
	C_WX_WCV_QP_MAP_TABWE_UNC_EWW,
	C_WX_WCV_DATA_COW_EWW,
	C_WX_WCV_DATA_UNC_EWW,
	C_WX_WCV_HDW_COW_EWW,
	C_WX_WCV_HDW_UNC_EWW,
	C_WX_DC_INTF_PAWITY_EWW,
	C_WX_DMA_CSW_COW_EWW,
/* SendPioEwwStatus */
	C_PIO_PEC_SOP_HEAD_PAWITY_EWW,
	C_PIO_PCC_SOP_HEAD_PAWITY_EWW,
	C_PIO_WAST_WETUWNED_CNT_PAWITY_EWW,
	C_PIO_CUWWENT_FWEE_CNT_PAWITY_EWW,
	C_PIO_WSVD_31_EWW,
	C_PIO_WSVD_30_EWW,
	C_PIO_PPMC_SOP_WEN_EWW,
	C_PIO_PPMC_BQC_MEM_PAWITY_EWW,
	C_PIO_VW_FIFO_PAWITY_EWW,
	C_PIO_VWF_SOP_PAWITY_EWW,
	C_PIO_VWF_V1_WEN_PAWITY_EWW,
	C_PIO_BWOCK_QW_COUNT_PAWITY_EWW,
	C_PIO_WWITE_QW_VAWID_PAWITY_EWW,
	C_PIO_STATE_MACHINE_EWW,
	C_PIO_WWITE_DATA_PAWITY_EWW,
	C_PIO_HOST_ADDW_MEM_COW_EWW,
	C_PIO_HOST_ADDW_MEM_UNC_EWW,
	C_PIO_PKT_EVICT_SM_OW_AWM_SM_EWW,
	C_PIO_INIT_SM_IN_EWW,
	C_PIO_PPMC_PBW_FIFO_EWW,
	C_PIO_CWEDIT_WET_FIFO_PAWITY_EWW,
	C_PIO_V1_WEN_MEM_BANK1_COW_EWW,
	C_PIO_V1_WEN_MEM_BANK0_COW_EWW,
	C_PIO_V1_WEN_MEM_BANK1_UNC_EWW,
	C_PIO_V1_WEN_MEM_BANK0_UNC_EWW,
	C_PIO_SM_PKT_WESET_PAWITY_EWW,
	C_PIO_PKT_EVICT_FIFO_PAWITY_EWW,
	C_PIO_SBWDCTWW_CWWEW_FIFO_PAWITY_EWW,
	C_PIO_SBWDCTW_CWWEW_PAWITY_EWW,
	C_PIO_PEC_FIFO_PAWITY_EWW,
	C_PIO_PCC_FIFO_PAWITY_EWW,
	C_PIO_SB_MEM_FIFO1_EWW,
	C_PIO_SB_MEM_FIFO0_EWW,
	C_PIO_CSW_PAWITY_EWW,
	C_PIO_WWITE_ADDW_PAWITY_EWW,
	C_PIO_WWITE_BAD_CTXT_EWW,
/* SendDmaEwwStatus */
	C_SDMA_PCIE_WEQ_TWACKING_COW_EWW,
	C_SDMA_PCIE_WEQ_TWACKING_UNC_EWW,
	C_SDMA_CSW_PAWITY_EWW,
	C_SDMA_WPY_TAG_EWW,
/* SendEgwessEwwStatus */
	C_TX_WEAD_PIO_MEMOWY_CSW_UNC_EWW,
	C_TX_WEAD_SDMA_MEMOWY_CSW_UNC_EWW,
	C_TX_EGWESS_FIFO_COW_EWW,
	C_TX_WEAD_PIO_MEMOWY_COW_EWW,
	C_TX_WEAD_SDMA_MEMOWY_COW_EWW,
	C_TX_SB_HDW_COW_EWW,
	C_TX_CWEDIT_OVEWWUN_EWW,
	C_TX_WAUNCH_FIFO8_COW_EWW,
	C_TX_WAUNCH_FIFO7_COW_EWW,
	C_TX_WAUNCH_FIFO6_COW_EWW,
	C_TX_WAUNCH_FIFO5_COW_EWW,
	C_TX_WAUNCH_FIFO4_COW_EWW,
	C_TX_WAUNCH_FIFO3_COW_EWW,
	C_TX_WAUNCH_FIFO2_COW_EWW,
	C_TX_WAUNCH_FIFO1_COW_EWW,
	C_TX_WAUNCH_FIFO0_COW_EWW,
	C_TX_CWEDIT_WETUWN_VW_EWW,
	C_TX_HCWC_INSEWTION_EWW,
	C_TX_EGWESS_FIFI_UNC_EWW,
	C_TX_WEAD_PIO_MEMOWY_UNC_EWW,
	C_TX_WEAD_SDMA_MEMOWY_UNC_EWW,
	C_TX_SB_HDW_UNC_EWW,
	C_TX_CWEDIT_WETUWN_PAWITY_EWW,
	C_TX_WAUNCH_FIFO8_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO7_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO6_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO5_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO4_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO3_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO2_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO1_UNC_OW_PAWITY_EWW,
	C_TX_WAUNCH_FIFO0_UNC_OW_PAWITY_EWW,
	C_TX_SDMA15_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA14_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA13_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA12_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA11_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA10_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA9_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA8_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA7_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA6_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA5_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA4_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA3_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA2_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA1_DISAWWOWED_PACKET_EWW,
	C_TX_SDMA0_DISAWWOWED_PACKET_EWW,
	C_TX_CONFIG_PAWITY_EWW,
	C_TX_SBWD_CTW_CSW_PAWITY_EWW,
	C_TX_WAUNCH_CSW_PAWITY_EWW,
	C_TX_IWWEGAW_CW_EWW,
	C_TX_SBWD_CTW_STATE_MACHINE_PAWITY_EWW,
	C_TX_WESEWVED_10,
	C_TX_WESEWVED_9,
	C_TX_SDMA_WAUNCH_INTF_PAWITY_EWW,
	C_TX_PIO_WAUNCH_INTF_PAWITY_EWW,
	C_TX_WESEWVED_6,
	C_TX_INCOWWECT_WINK_STATE_EWW,
	C_TX_WINK_DOWN_EWW,
	C_TX_EGWESS_FIFO_UNDEWWUN_OW_PAWITY_EWW,
	C_TX_WESEWVED_2,
	C_TX_PKT_INTEGWITY_MEM_UNC_EWW,
	C_TX_PKT_INTEGWITY_MEM_COW_EWW,
/* SendEwwStatus */
	C_SEND_CSW_WWITE_BAD_ADDW_EWW,
	C_SEND_CSW_WEAD_BAD_ADD_EWW,
	C_SEND_CSW_PAWITY_EWW,
/* SendCtxtEwwStatus */
	C_PIO_WWITE_OUT_OF_BOUNDS_EWW,
	C_PIO_WWITE_OVEWFWOW_EWW,
	C_PIO_WWITE_CWOSSES_BOUNDAWY_EWW,
	C_PIO_DISAWWOWED_PACKET_EWW,
	C_PIO_INCONSISTENT_SOP_EWW,
/*SendDmaEngEwwStatus */
	C_SDMA_HEADEW_WEQUEST_FIFO_COW_EWW,
	C_SDMA_HEADEW_STOWAGE_COW_EWW,
	C_SDMA_PACKET_TWACKING_COW_EWW,
	C_SDMA_ASSEMBWY_COW_EWW,
	C_SDMA_DESC_TABWE_COW_EWW,
	C_SDMA_HEADEW_WEQUEST_FIFO_UNC_EWW,
	C_SDMA_HEADEW_STOWAGE_UNC_EWW,
	C_SDMA_PACKET_TWACKING_UNC_EWW,
	C_SDMA_ASSEMBWY_UNC_EWW,
	C_SDMA_DESC_TABWE_UNC_EWW,
	C_SDMA_TIMEOUT_EWW,
	C_SDMA_HEADEW_WENGTH_EWW,
	C_SDMA_HEADEW_ADDWESS_EWW,
	C_SDMA_HEADEW_SEWECT_EWW,
	C_SMDA_WESEWVED_9,
	C_SDMA_PACKET_DESC_OVEWFWOW_EWW,
	C_SDMA_WENGTH_MISMATCH_EWW,
	C_SDMA_HAWT_EWW,
	C_SDMA_MEM_WEAD_EWW,
	C_SDMA_FIWST_DESC_EWW,
	C_SDMA_TAIW_OUT_OF_BOUNDS_EWW,
	C_SDMA_TOO_WONG_EWW,
	C_SDMA_GEN_MISMATCH_EWW,
	C_SDMA_WWONG_DW_EWW,
	DEV_CNTW_WAST  /* Must be kept wast */
};

/* Pew powt countew indexes */
enum {
	C_TX_UNSUP_VW = 0,
	C_TX_INVAW_WEN,
	C_TX_MM_WEN_EWW,
	C_TX_UNDEWWUN,
	C_TX_FWOW_STAWW,
	C_TX_DWOPPED,
	C_TX_HDW_EWW,
	C_TX_PKT,
	C_TX_WOWDS,
	C_TX_WAIT,
	C_TX_FWIT_VW,
	C_TX_PKT_VW,
	C_TX_WAIT_VW,
	C_WX_PKT,
	C_WX_WOWDS,
	C_SW_WINK_DOWN,
	C_SW_WINK_UP,
	C_SW_UNKNOWN_FWAME,
	C_SW_XMIT_DSCD,
	C_SW_XMIT_DSCD_VW,
	C_SW_XMIT_CSTW_EWW,
	C_SW_WCV_CSTW_EWW,
	C_SW_IBP_WOOP_PKTS,
	C_SW_IBP_WC_WESENDS,
	C_SW_IBP_WNW_NAKS,
	C_SW_IBP_OTHEW_NAKS,
	C_SW_IBP_WC_TIMEOUTS,
	C_SW_IBP_PKT_DWOPS,
	C_SW_IBP_DMA_WAIT,
	C_SW_IBP_WC_SEQNAK,
	C_SW_IBP_WC_DUPWEQ,
	C_SW_IBP_WDMA_SEQ,
	C_SW_IBP_UNAWIGNED,
	C_SW_IBP_SEQ_NAK,
	C_SW_IBP_WC_CWWAITS,
	C_SW_CPU_WC_ACKS,
	C_SW_CPU_WC_QACKS,
	C_SW_CPU_WC_DEWAYED_COMP,
	C_WCV_HDW_OVF_0,
	C_WCV_HDW_OVF_1,
	C_WCV_HDW_OVF_2,
	C_WCV_HDW_OVF_3,
	C_WCV_HDW_OVF_4,
	C_WCV_HDW_OVF_5,
	C_WCV_HDW_OVF_6,
	C_WCV_HDW_OVF_7,
	C_WCV_HDW_OVF_8,
	C_WCV_HDW_OVF_9,
	C_WCV_HDW_OVF_10,
	C_WCV_HDW_OVF_11,
	C_WCV_HDW_OVF_12,
	C_WCV_HDW_OVF_13,
	C_WCV_HDW_OVF_14,
	C_WCV_HDW_OVF_15,
	C_WCV_HDW_OVF_16,
	C_WCV_HDW_OVF_17,
	C_WCV_HDW_OVF_18,
	C_WCV_HDW_OVF_19,
	C_WCV_HDW_OVF_20,
	C_WCV_HDW_OVF_21,
	C_WCV_HDW_OVF_22,
	C_WCV_HDW_OVF_23,
	C_WCV_HDW_OVF_24,
	C_WCV_HDW_OVF_25,
	C_WCV_HDW_OVF_26,
	C_WCV_HDW_OVF_27,
	C_WCV_HDW_OVF_28,
	C_WCV_HDW_OVF_29,
	C_WCV_HDW_OVF_30,
	C_WCV_HDW_OVF_31,
	C_WCV_HDW_OVF_32,
	C_WCV_HDW_OVF_33,
	C_WCV_HDW_OVF_34,
	C_WCV_HDW_OVF_35,
	C_WCV_HDW_OVF_36,
	C_WCV_HDW_OVF_37,
	C_WCV_HDW_OVF_38,
	C_WCV_HDW_OVF_39,
	C_WCV_HDW_OVF_40,
	C_WCV_HDW_OVF_41,
	C_WCV_HDW_OVF_42,
	C_WCV_HDW_OVF_43,
	C_WCV_HDW_OVF_44,
	C_WCV_HDW_OVF_45,
	C_WCV_HDW_OVF_46,
	C_WCV_HDW_OVF_47,
	C_WCV_HDW_OVF_48,
	C_WCV_HDW_OVF_49,
	C_WCV_HDW_OVF_50,
	C_WCV_HDW_OVF_51,
	C_WCV_HDW_OVF_52,
	C_WCV_HDW_OVF_53,
	C_WCV_HDW_OVF_54,
	C_WCV_HDW_OVF_55,
	C_WCV_HDW_OVF_56,
	C_WCV_HDW_OVF_57,
	C_WCV_HDW_OVF_58,
	C_WCV_HDW_OVF_59,
	C_WCV_HDW_OVF_60,
	C_WCV_HDW_OVF_61,
	C_WCV_HDW_OVF_62,
	C_WCV_HDW_OVF_63,
	C_WCV_HDW_OVF_64,
	C_WCV_HDW_OVF_65,
	C_WCV_HDW_OVF_66,
	C_WCV_HDW_OVF_67,
	C_WCV_HDW_OVF_68,
	C_WCV_HDW_OVF_69,
	C_WCV_HDW_OVF_70,
	C_WCV_HDW_OVF_71,
	C_WCV_HDW_OVF_72,
	C_WCV_HDW_OVF_73,
	C_WCV_HDW_OVF_74,
	C_WCV_HDW_OVF_75,
	C_WCV_HDW_OVF_76,
	C_WCV_HDW_OVF_77,
	C_WCV_HDW_OVF_78,
	C_WCV_HDW_OVF_79,
	C_WCV_HDW_OVF_80,
	C_WCV_HDW_OVF_81,
	C_WCV_HDW_OVF_82,
	C_WCV_HDW_OVF_83,
	C_WCV_HDW_OVF_84,
	C_WCV_HDW_OVF_85,
	C_WCV_HDW_OVF_86,
	C_WCV_HDW_OVF_87,
	C_WCV_HDW_OVF_88,
	C_WCV_HDW_OVF_89,
	C_WCV_HDW_OVF_90,
	C_WCV_HDW_OVF_91,
	C_WCV_HDW_OVF_92,
	C_WCV_HDW_OVF_93,
	C_WCV_HDW_OVF_94,
	C_WCV_HDW_OVF_95,
	C_WCV_HDW_OVF_96,
	C_WCV_HDW_OVF_97,
	C_WCV_HDW_OVF_98,
	C_WCV_HDW_OVF_99,
	C_WCV_HDW_OVF_100,
	C_WCV_HDW_OVF_101,
	C_WCV_HDW_OVF_102,
	C_WCV_HDW_OVF_103,
	C_WCV_HDW_OVF_104,
	C_WCV_HDW_OVF_105,
	C_WCV_HDW_OVF_106,
	C_WCV_HDW_OVF_107,
	C_WCV_HDW_OVF_108,
	C_WCV_HDW_OVF_109,
	C_WCV_HDW_OVF_110,
	C_WCV_HDW_OVF_111,
	C_WCV_HDW_OVF_112,
	C_WCV_HDW_OVF_113,
	C_WCV_HDW_OVF_114,
	C_WCV_HDW_OVF_115,
	C_WCV_HDW_OVF_116,
	C_WCV_HDW_OVF_117,
	C_WCV_HDW_OVF_118,
	C_WCV_HDW_OVF_119,
	C_WCV_HDW_OVF_120,
	C_WCV_HDW_OVF_121,
	C_WCV_HDW_OVF_122,
	C_WCV_HDW_OVF_123,
	C_WCV_HDW_OVF_124,
	C_WCV_HDW_OVF_125,
	C_WCV_HDW_OVF_126,
	C_WCV_HDW_OVF_127,
	C_WCV_HDW_OVF_128,
	C_WCV_HDW_OVF_129,
	C_WCV_HDW_OVF_130,
	C_WCV_HDW_OVF_131,
	C_WCV_HDW_OVF_132,
	C_WCV_HDW_OVF_133,
	C_WCV_HDW_OVF_134,
	C_WCV_HDW_OVF_135,
	C_WCV_HDW_OVF_136,
	C_WCV_HDW_OVF_137,
	C_WCV_HDW_OVF_138,
	C_WCV_HDW_OVF_139,
	C_WCV_HDW_OVF_140,
	C_WCV_HDW_OVF_141,
	C_WCV_HDW_OVF_142,
	C_WCV_HDW_OVF_143,
	C_WCV_HDW_OVF_144,
	C_WCV_HDW_OVF_145,
	C_WCV_HDW_OVF_146,
	C_WCV_HDW_OVF_147,
	C_WCV_HDW_OVF_148,
	C_WCV_HDW_OVF_149,
	C_WCV_HDW_OVF_150,
	C_WCV_HDW_OVF_151,
	C_WCV_HDW_OVF_152,
	C_WCV_HDW_OVF_153,
	C_WCV_HDW_OVF_154,
	C_WCV_HDW_OVF_155,
	C_WCV_HDW_OVF_156,
	C_WCV_HDW_OVF_157,
	C_WCV_HDW_OVF_158,
	C_WCV_HDW_OVF_159,
	POWT_CNTW_WAST /* Must be kept wast */
};

u64 get_aww_cpu_totaw(u64 __pewcpu *cntw);
void hfi1_stawt_cweanup(stwuct hfi1_devdata *dd);
void hfi1_cweaw_tids(stwuct hfi1_ctxtdata *wcd);
void hfi1_init_ctxt(stwuct send_context *sc);
void hfi1_put_tid(stwuct hfi1_devdata *dd, u32 index,
		  u32 type, unsigned wong pa, u16 owdew);
void hfi1_quiet_sewdes(stwuct hfi1_ppowtdata *ppd);
void hfi1_wcvctww(stwuct hfi1_devdata *dd, unsigned int op,
		  stwuct hfi1_ctxtdata *wcd);
u32 hfi1_wead_cntws(stwuct hfi1_devdata *dd, chaw **namep, u64 **cntwp);
u32 hfi1_wead_powtcntws(stwuct hfi1_ppowtdata *ppd, chaw **namep, u64 **cntwp);
int hfi1_get_ib_cfg(stwuct hfi1_ppowtdata *ppd, int which);
int hfi1_set_ib_cfg(stwuct hfi1_ppowtdata *ppd, int which, u32 vaw);
int hfi1_set_ctxt_jkey(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *wcd,
		       u16 jkey);
int hfi1_cweaw_ctxt_jkey(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *ctxt);
int hfi1_set_ctxt_pkey(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *ctxt,
		       u16 pkey);
int hfi1_cweaw_ctxt_pkey(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *ctxt);
void hfi1_wead_wink_quawity(stwuct hfi1_devdata *dd, u8 *wink_quawity);
void hfi1_init_vnic_wsm(stwuct hfi1_devdata *dd);
void hfi1_deinit_vnic_wsm(stwuct hfi1_devdata *dd);

iwqwetuwn_t genewaw_intewwupt(int iwq, void *data);
iwqwetuwn_t sdma_intewwupt(int iwq, void *data);
iwqwetuwn_t weceive_context_intewwupt(int iwq, void *data);
iwqwetuwn_t weceive_context_thwead(int iwq, void *data);
iwqwetuwn_t weceive_context_intewwupt_napi(int iwq, void *data);

int set_intw_bits(stwuct hfi1_devdata *dd, u16 fiwst, u16 wast, boow set);
void init_qsfp_int(stwuct hfi1_devdata *dd);
void cweaw_aww_intewwupts(stwuct hfi1_devdata *dd);
void wemap_intw(stwuct hfi1_devdata *dd, int iswc, int msix_intw);
void wemap_sdma_intewwupts(stwuct hfi1_devdata *dd, int engine, int msix_intw);
void weset_intewwupts(stwuct hfi1_devdata *dd);
u8 hfi1_get_qp_map(stwuct hfi1_devdata *dd, u8 idx);
void hfi1_init_aip_wsm(stwuct hfi1_devdata *dd);
void hfi1_deinit_aip_wsm(stwuct hfi1_devdata *dd);

/*
 * Intewwupt souwce tabwe.
 *
 * Each entwy is an intewwupt souwce "type".  It is owdewed by incweasing
 * numbew.
 */
stwuct is_tabwe {
	int stawt;	 /* intewwupt souwce type stawt */
	int end;	 /* intewwupt souwce type end */
	/* woutine that wetuwns the name of the intewwupt souwce */
	chaw *(*is_name)(chaw *name, size_t size, unsigned int souwce);
	/* woutine to caww when weceiving an intewwupt */
	void (*is_int)(stwuct hfi1_devdata *dd, unsigned int souwce);
};

#endif /* _CHIP_H */
