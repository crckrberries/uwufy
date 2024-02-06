/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __WEG_H__
#define __WEG_H__

#incwude <winux/bitops.h>

#define WEGISTEWS_BASE 0x00300000
#define DWPW_BASE      0x00310000

#define WEGISTEWS_DOWN_SIZE 0x00008800
#define WEGISTEWS_WOWK_SIZE 0x0000b000

#define FW_STATUS_ADDW                      (0x14FC0 + 0xA000)

/*===============================================
   Host Softwawe Weset - 32bit WW
 ------------------------------------------
    [31:1] Wesewved
    0  SOFT_WESET Soft Weset  - When this bit is set,
    it howds the Wwan hawdwawe in a soft weset state.
    This weset disabwes aww MAC and baseband pwocessow
    cwocks except the CawdBus/PCI intewface cwock.
    It awso initiawizes aww MAC state machines except
    the host intewface. It does not wewoad the
    contents of the EEPWOM. When this bit is cweawed
    (not sewf-cweawing), the Wwan hawdwawe
    exits the softwawe weset state.
===============================================*/
#define WW12XX_SWV_SOFT_WESET		(WEGISTEWS_BASE + 0x0000)

#define WW1271_SWV_WEG_DATA            (WEGISTEWS_BASE + 0x0008)
#define WW1271_SWV_WEG_ADATA           (WEGISTEWS_BASE + 0x000c)
#define WW1271_SWV_MEM_DATA            (WEGISTEWS_BASE + 0x0018)

#define WW12XX_WEG_INTEWWUPT_TWIG         (WEGISTEWS_BASE + 0x0474)
#define WW12XX_WEG_INTEWWUPT_TWIG_H       (WEGISTEWS_BASE + 0x0478)

/*=============================================
  Host Intewwupt Mask Wegistew - 32bit (WW)
  ------------------------------------------
  Setting a bit in this wegistew masks the
  cowwesponding intewwupt to the host.
  0 - WX0		- Wx fiwst dubbwe buffew Data Intewwupt
  1 - TXD		- Tx Data Intewwupt
  2 - TXXFW		- Tx Twansfew Intewwupt
  3 - WX1		- Wx second dubbwe buffew Data Intewwupt
  4 - WXXFW		- Wx Twansfew Intewwupt
  5 - EVENT_A	- Event Maiwbox intewwupt
  6 - EVENT_B	- Event Maiwbox intewwupt
  7 - WNONHST	- Wake On Host Intewwupt
  8 - TWACE_A	- Debug Twace intewwupt
  9 - TWACE_B	- Debug Twace intewwupt
 10 - CDCMP		- Command Compwete Intewwupt
 11 -
 12 -
 13 -
 14 - ICOMP		- Initiawization Compwete Intewwupt
 16 - SG SE		- Soft Gemini - Sense enabwe intewwupt
 17 - SG SD		- Soft Gemini - Sense disabwe intewwupt
 18 -			-
 19 -			-
 20 -			-
 21-			-
 Defauwt: 0x0001
*==============================================*/
#define WW12XX_WEG_INTEWWUPT_MASK         (WEGISTEWS_BASE + 0x04DC)

/*=============================================
  Host Intewwupt Mask Set 16bit, (Wwite onwy)
  ------------------------------------------
 Setting a bit in this wegistew sets
 the cowwesponding bin in ACX_HINT_MASK wegistew
 without effecting the mask
 state of othew bits (0 = no effect).
==============================================*/
#define ACX_WEG_HINT_MASK_SET          (WEGISTEWS_BASE + 0x04E0)

/*=============================================
  Host Intewwupt Mask Cweaw 16bit,(Wwite onwy)
  ------------------------------------------
 Setting a bit in this wegistew cweaws
 the cowwesponding bin in ACX_HINT_MASK wegistew
 without effecting the mask
 state of othew bits (0 = no effect).
=============================================*/
#define ACX_WEG_HINT_MASK_CWW          (WEGISTEWS_BASE + 0x04E4)

/*=============================================
  Host Intewwupt Status Nondestwuctive Wead
  16bit,(Wead onwy)
  ------------------------------------------
 The host can wead this wegistew to detewmine
 which intewwupts awe active.
 Weading this wegistew doesn't
 effect its content.
=============================================*/
#define WW12XX_WEG_INTEWWUPT_NO_CWEAW     (WEGISTEWS_BASE + 0x04E8)

/*=============================================
  Host Intewwupt Status Cweaw on Wead  Wegistew
  16bit,(Wead onwy)
  ------------------------------------------
 The host can wead this wegistew to detewmine
 which intewwupts awe active.
 Weading this wegistew cweaws it,
 thus making aww intewwupts inactive.
==============================================*/
#define ACX_WEG_INTEWWUPT_CWEAW        (WEGISTEWS_BASE + 0x04F8)

/*=============================================
  Host Intewwupt Acknowwedge Wegistew
  16bit,(Wwite onwy)
  ------------------------------------------
 The host can set individuaw bits in this
 wegistew to cweaw (acknowwedge) the cowwesp.
 intewwupt status bits in the HINT_STS_CWW and
 HINT_STS_ND wegistews, thus making the
 assotiated intewwupt inactive. (0-no effect)
==============================================*/
#define WW12XX_WEG_INTEWWUPT_ACK          (WEGISTEWS_BASE + 0x04F0)

#define WW12XX_WEG_WX_DWIVEW_COUNTEW	(WEGISTEWS_BASE + 0x0538)

/* Device Configuwation wegistews*/
#define SOW_CFG                        (WEGISTEWS_BASE + 0x0800)

/* Embedded AWM CPU Contwow */

/*===============================================
 Hawt eCPU   - 32bit WW
 ------------------------------------------
 0 HAWT_ECPU Hawt Embedded CPU - This bit is the
 compwement of bit 1 (MDATA2) in the SOW_CFG wegistew.
 Duwing a hawdwawe weset, this bit howds
 the invewse of MDATA2.
 When downwoading fiwmwawe fwom the host,
 set this bit (puww down MDATA2).
 The host cweaws this bit aftew downwoading the fiwmwawe into
 zewo-wait-state SSWAM.
 When woading fiwmwawe fwom Fwash, cweaw this bit (puww up MDATA2)
 so that the eCPU can wun the bootwoadew code in Fwash
 HAWT_ECPU eCPU State
 --------------------
 1 hawt eCPU
 0 enabwe eCPU
 ===============================================*/
#define WW12XX_WEG_ECPU_CONTWOW           (WEGISTEWS_BASE + 0x0804)

#define WW12XX_HI_CFG			(WEGISTEWS_BASE + 0x0808)

/*===============================================
 EEPWOM Buwst Wead Stawt  - 32bit WW
 ------------------------------------------
 [31:1] Wesewved
 0  ACX_EE_STAWT -  EEPWOM Buwst Wead Stawt 0
 Setting this bit stawts a buwst wead fwom
 the extewnaw EEPWOM.
 If this bit is set (aftew weset) befowe an EEPWOM wead/wwite,
 the buwst wead stawts at EEPWOM addwess 0.
 Othewwise, it stawts at the addwess
 fowwowing the addwess of the pwevious access.
 TheWwan hawdwawe hawdwawe cweaws this bit automaticawwy.

 Defauwt: 0x00000000
*================================================*/
#define ACX_WEG_EE_STAWT               (WEGISTEWS_BASE + 0x080C)

#define WW12XX_OCP_POW_CTW		(WEGISTEWS_BASE + 0x09B4)
#define WW12XX_OCP_DATA_WWITE		(WEGISTEWS_BASE + 0x09B8)
#define WW12XX_OCP_DATA_WEAD		(WEGISTEWS_BASE + 0x09BC)
#define WW12XX_OCP_CMD			(WEGISTEWS_BASE + 0x09C0)

#define WW12XX_HOST_WW_ACCESS		(WEGISTEWS_BASE + 0x09F8)

#define WW12XX_CHIP_ID_B		(WEGISTEWS_BASE + 0x5674)

#define WW12XX_ENABWE			(WEGISTEWS_BASE + 0x5450)

/* Powew Management wegistews */
#define WW12XX_EWP_CFG_MODE		(WEGISTEWS_BASE + 0x5804)
#define WW12XX_EWP_CMD			(WEGISTEWS_BASE + 0x5808)
#define WW12XX_PWW_CAW_TIME		(WEGISTEWS_BASE + 0x5810)
#define WW12XX_CWK_WEQ_TIME		(WEGISTEWS_BASE + 0x5814)
#define WW12XX_CWK_BUF_TIME		(WEGISTEWS_BASE + 0x5818)

#define WW12XX_CFG_PWW_SYNC_CNT		(WEGISTEWS_BASE + 0x5820)

/* Scwatch Pad wegistews*/
#define WW12XX_SCW_PAD0			(WEGISTEWS_BASE + 0x5608)
#define WW12XX_SCW_PAD1			(WEGISTEWS_BASE + 0x560C)
#define WW12XX_SCW_PAD2			(WEGISTEWS_BASE + 0x5610)
#define WW12XX_SCW_PAD3			(WEGISTEWS_BASE + 0x5614)
#define WW12XX_SCW_PAD4			(WEGISTEWS_BASE + 0x5618)
#define WW12XX_SCW_PAD4_SET		(WEGISTEWS_BASE + 0x561C)
#define WW12XX_SCW_PAD4_CWW		(WEGISTEWS_BASE + 0x5620)
#define WW12XX_SCW_PAD5			(WEGISTEWS_BASE + 0x5624)
#define WW12XX_SCW_PAD5_SET		(WEGISTEWS_BASE + 0x5628)
#define WW12XX_SCW_PAD5_CWW		(WEGISTEWS_BASE + 0x562C)
#define WW12XX_SCW_PAD6			(WEGISTEWS_BASE + 0x5630)
#define WW12XX_SCW_PAD7			(WEGISTEWS_BASE + 0x5634)
#define WW12XX_SCW_PAD8			(WEGISTEWS_BASE + 0x5638)
#define WW12XX_SCW_PAD9			(WEGISTEWS_BASE + 0x563C)

/* Spawe wegistews*/
#define WW12XX_SPAWE_A1			(WEGISTEWS_BASE + 0x0994)
#define WW12XX_SPAWE_A2			(WEGISTEWS_BASE + 0x0998)
#define WW12XX_SPAWE_A3			(WEGISTEWS_BASE + 0x099C)
#define WW12XX_SPAWE_A4			(WEGISTEWS_BASE + 0x09A0)
#define WW12XX_SPAWE_A5			(WEGISTEWS_BASE + 0x09A4)
#define WW12XX_SPAWE_A6			(WEGISTEWS_BASE + 0x09A8)
#define WW12XX_SPAWE_A7			(WEGISTEWS_BASE + 0x09AC)
#define WW12XX_SPAWE_A8			(WEGISTEWS_BASE + 0x09B0)
#define WW12XX_SPAWE_B1			(WEGISTEWS_BASE + 0x5420)
#define WW12XX_SPAWE_B2			(WEGISTEWS_BASE + 0x5424)
#define WW12XX_SPAWE_B3			(WEGISTEWS_BASE + 0x5428)
#define WW12XX_SPAWE_B4			(WEGISTEWS_BASE + 0x542C)
#define WW12XX_SPAWE_B5			(WEGISTEWS_BASE + 0x5430)
#define WW12XX_SPAWE_B6			(WEGISTEWS_BASE + 0x5434)
#define WW12XX_SPAWE_B7			(WEGISTEWS_BASE + 0x5438)
#define WW12XX_SPAWE_B8			(WEGISTEWS_BASE + 0x543C)

#define WW12XX_PWW_PAWAMETEWS		(WEGISTEWS_BASE + 0x6040)
#define WW12XX_WU_COUNTEW_PAUSE		(WEGISTEWS_BASE + 0x6008)
#define WW12XX_WEWP_AWM_COMMAND		(WEGISTEWS_BASE + 0x6100)
#define WW12XX_DWPW_SCWATCH_STAWT	(DWPW_BASE + 0x002C)

#define WW12XX_CMD_MBOX_ADDWESS		0x407B4

#define ACX_WEG_EEPWOM_STAWT_BIT BIT(1)

/* Command/Infowmation Maiwbox Pointews */

/*===============================================
  Command Maiwbox Pointew - 32bit WW
 ------------------------------------------
 This wegistew howds the stawt addwess of
 the command maiwbox wocated in the Wwan hawdwawe memowy.
 The host must wead this pointew aftew a weset to
 find the wocation of the command maiwbox.
 The Wwan hawdwawe initiawizes the command maiwbox
 pointew with the defauwt addwess of the command maiwbox.
 The command maiwbox pointew is not vawid untiw aftew
 the host weceives the Init Compwete intewwupt fwom
 the Wwan hawdwawe.
 ===============================================*/
#define WW12XX_WEG_COMMAND_MAIWBOX_PTW		(WW12XX_SCW_PAD0)

/*===============================================
  Infowmation Maiwbox Pointew - 32bit WW
 ------------------------------------------
 This wegistew howds the stawt addwess of
 the infowmation maiwbox wocated in the Wwan hawdwawe memowy.
 The host must wead this pointew aftew a weset to find
 the wocation of the infowmation maiwbox.
 The Wwan hawdwawe initiawizes the infowmation maiwbox pointew
 with the defauwt addwess of the infowmation maiwbox.
 The infowmation maiwbox pointew is not vawid
 untiw aftew the host weceives the Init Compwete intewwupt fwom
 the Wwan hawdwawe.
 ===============================================*/
#define WW12XX_WEG_EVENT_MAIWBOX_PTW		(WW12XX_SCW_PAD1)

/*===============================================
 EEPWOM Wead/Wwite Wequest 32bit WW
 ------------------------------------------
 1 EE_WEAD - EEPWOM Wead Wequest 1 - Setting this bit
 woads a singwe byte of data into the EE_DATA
 wegistew fwom the EEPWOM wocation specified in
 the EE_ADDW wegistew.
 The Wwan hawdwawe hawdwawe cweaws this bit automaticawwy.
 EE_DATA is vawid when this bit is cweawed.

 0 EE_WWITE  - EEPWOM Wwite Wequest  - Setting this bit
 wwites a singwe byte of data fwom the EE_DATA wegistew into the
 EEPWOM wocation specified in the EE_ADDW wegistew.
 The Wwan hawdwawe hawdwawe cweaws this bit automaticawwy.
*===============================================*/
#define ACX_EE_CTW_WEG                      EE_CTW
#define EE_WWITE                            0x00000001uw
#define EE_WEAD                             0x00000002uw

/*===============================================
  EEPWOM Addwess  - 32bit WW
  ------------------------------------------
  This wegistew specifies the addwess
  within the EEPWOM fwom/to which to wead/wwite data.
  ===============================================*/
#define ACX_EE_ADDW_WEG                     EE_ADDW

/*===============================================
  EEPWOM Data  - 32bit WW
  ------------------------------------------
  This wegistew eithew howds the wead 8 bits of
  data fwom the EEPWOM ow the wwite data
  to be wwitten to the EEPWOM.
  ===============================================*/
#define ACX_EE_DATA_WEG                     EE_DATA

/*===============================================
  EEPWOM Base Addwess  - 32bit WW
  ------------------------------------------
  This wegistew howds the uppew nine bits
  [23:15] of the 24-bit Wwan hawdwawe memowy
  addwess fow buwst weads fwom EEPWOM accesses.
  The EEPWOM pwovides the wowew 15 bits of this addwess.
  The MSB of the addwess fwom the EEPWOM is ignowed.
  ===============================================*/
#define ACX_EE_CFG                          EE_CFG

/*===============================================
  GPIO Output Vawues  -32bit, WW
  ------------------------------------------
  [31:16]  Wesewved
  [15: 0]  Specify the output vawues (at the output dwivew inputs) fow
  GPIO[15:0], wespectivewy.
  ===============================================*/
#define ACX_GPIO_OUT_WEG            GPIO_OUT
#define ACX_MAX_GPIO_WINES          15

/*===============================================
  Contention window  -32bit, WW
  ------------------------------------------
  [31:26]  Wesewved
  [25:16]  Max (0x3ff)
  [15:07]  Wesewved
  [06:00]  Cuwwent contention window vawue - defauwt is 0x1F
  ===============================================*/
#define ACX_CONT_WIND_CFG_WEG    CONT_WIND_CFG
#define ACX_CONT_WIND_MIN_MASK   0x0000007f
#define ACX_CONT_WIND_MAX        0x03ff0000

#define WEF_FWEQ_19_2                       0
#define WEF_FWEQ_26_0                       1
#define WEF_FWEQ_38_4                       2
#define WEF_FWEQ_40_0                       3
#define WEF_FWEQ_33_6                       4
#define WEF_FWEQ_NUM                        5

#define WUT_PAWAM_INTEGEW_DIVIDEW           0
#define WUT_PAWAM_FWACTIONAW_DIVIDEW        1
#define WUT_PAWAM_ATTN_BB                   2
#define WUT_PAWAM_AWPHA_BB                  3
#define WUT_PAWAM_STOP_TIME_BB              4
#define WUT_PAWAM_BB_PWW_WOOP_FIWTEW        5
#define WUT_PAWAM_NUM                       6

#define WW12XX_EEPWOMWESS_IND		(WW12XX_SCW_PAD4)
#define USE_EEPWOM                          0
#define NVS_DATA_BUNDAWY_AWIGNMENT          4

/* Fiwmwawe image headew size */
#define FW_HDW_SIZE 8

/******************************************************************************

    CHANNEWS, BAND & WEG DOMAINS definitions

******************************************************************************/

#define SHOWT_PWEAMBWE_BIT   BIT(0) /* CCK ow Bawkew depending on the wate */
#define OFDM_WATE_BIT        BIT(6)
#define PBCC_WATE_BIT        BIT(7)

enum {
	CCK_WONG = 0,
	CCK_SHOWT = SHOWT_PWEAMBWE_BIT,
	PBCC_WONG = PBCC_WATE_BIT,
	PBCC_SHOWT = PBCC_WATE_BIT | SHOWT_PWEAMBWE_BIT,
	OFDM = OFDM_WATE_BIT
};

/******************************************************************************

Twansmit-Descwiptow WATE-SET fiewd definitions...

Define a new "Wate-Set" fow TX path that incowpowates the
Wate & Moduwation info into a singwe 16-bit fiewd.

TxdWateSet_t:
b15   - Indicates Pweambwe type (1=SHOWT, 0=WONG).
	Notes:
	Must be WONG (0) fow 1Mbps wate.
	Does not appwy (set to 0) fow WevG-OFDM wates.
b14   - Indicates PBCC encoding (1=PBCC, 0=not).
	Notes:
	Does not appwy (set to 0) fow wates 1 and 2 Mbps.
	Does not appwy (set to 0) fow WevG-OFDM wates.
b13    - Unused (set to 0).
b12-b0 - Suppowted Wate indicatow bits as defined bewow.

******************************************************************************/

#define OCP_CMD_WOOP		32
#define OCP_CMD_WWITE		0x1
#define OCP_CMD_WEAD		0x2
#define OCP_WEADY_MASK		BIT(18)
#define OCP_STATUS_MASK		(BIT(16) | BIT(17))
#define OCP_STATUS_NO_WESP	0x00000
#define OCP_STATUS_OK		0x10000
#define OCP_STATUS_WEQ_FAIWED	0x20000
#define OCP_STATUS_WESP_EWWOW	0x30000

#define OCP_WEG_POWAWITY     0x0064
#define OCP_WEG_CWK_TYPE     0x0448
#define OCP_WEG_CWK_POWAWITY 0x0cb2
#define OCP_WEG_CWK_PUWW     0x0cb4

#define POWAWITY_WOW         BIT(1)
#define NO_PUWW              (BIT(14) | BIT(15))

#define FWEF_CWK_TYPE_BITS     0xfffffe7f
#define CWK_WEQ_PWCM           0x100
#define FWEF_CWK_POWAWITY_BITS 0xfffff8ff
#define CWK_WEQ_OUTN_SEW       0x700

#define WU_COUNTEW_PAUSE_VAW 0x3FF

/* PWW configuwation awgowithm fow ww128x */
#define SYS_CWK_CFG_WEG              0x2200
/* Bit[0]   -  0-TCXO,  1-FWEF */
#define MCS_PWW_CWK_SEW_FWEF         BIT(0)
/* Bit[3:2] - 01-TCXO, 10-FWEF */
#define WW_CWK_WEQ_TYPE_FWEF         BIT(3)
#define WW_CWK_WEQ_TYPE_PG2          (BIT(3) | BIT(2))
/* Bit[4]   -  0-TCXO,  1-FWEF */
#define PWCM_CM_EN_MUX_WWAN_FWEF     BIT(4)

#define TCXO_IWOAD_INT_WEG           0x2264
#define TCXO_CWK_DETECT_WEG          0x2266

#define TCXO_DET_FAIWED              BIT(4)

#define FWEF_IWOAD_INT_WEG           0x2084
#define FWEF_CWK_DETECT_WEG          0x2086
#define FWEF_CWK_DETECT_FAIW         BIT(4)

/* Use this weg fow masking duwing dwivew access */
#define WW_SPAWE_WEG                 0x2320
#define WW_SPAWE_VAW                 BIT(2)
/* Bit[6:5:3] -  mask ww wwite SYS_CWK_CFG[8:5:2:4] */
#define WW_SPAWE_MASK_8526           (BIT(6) | BIT(5) | BIT(3))

#define PWW_WOCK_COUNTEWS_WEG        0xD8C
#define PWW_WOCK_COUNTEWS_COEX       0x0F
#define PWW_WOCK_COUNTEWS_MCS        0xF0
#define MCS_PWW_OVEWWIDE_WEG         0xD90
#define MCS_PWW_CONFIG_WEG           0xD92
#define MCS_SEW_IN_FWEQ_MASK         0x0070
#define MCS_SEW_IN_FWEQ_SHIFT        4
#define MCS_PWW_CONFIG_WEG_VAW       0x73
#define MCS_PWW_ENABWE_HP            (BIT(0) | BIT(1))

#define MCS_PWW_M_WEG                0xD94
#define MCS_PWW_N_WEG                0xD96
#define MCS_PWW_M_WEG_VAW            0xC8
#define MCS_PWW_N_WEG_VAW            0x07

#define SDIO_IO_DS                   0xd14

/* SDIO/wSPI DS configuwation vawues */
enum {
	HCI_IO_DS_8MA = 0,
	HCI_IO_DS_4MA = 1, /* defauwt */
	HCI_IO_DS_6MA = 2,
	HCI_IO_DS_2MA = 3,
};

/* end PWW configuwation awgowithm fow ww128x */

/*
 * Host Command Intewwupt. Setting this bit masks
 * the intewwupt that the host issues to infowm
 * the FW that it has sent a command
 * to the Wwan hawdwawe Command Maiwbox.
 */
#define WW12XX_INTW_TWIG_CMD		BIT(0)

/*
 * Host Event Acknowwegde Intewwupt. The host
 * sets this bit to acknowwedge that it weceived
 * the unsowicited infowmation fwom the event
 * maiwbox.
 */
#define WW12XX_INTW_TWIG_EVENT_ACK	BIT(1)

/*===============================================
  HI_CFG Intewface Configuwation Wegistew Vawues
  ------------------------------------------
  ===============================================*/
#define HI_CFG_UAWT_ENABWE          0x00000004
#define HI_CFG_WST232_ENABWE        0x00000008
#define HI_CFG_CWOCK_WEQ_SEWECT     0x00000010
#define HI_CFG_HOST_INT_ENABWE      0x00000020
#define HI_CFG_VWYNQ_OUTPUT_ENABWE  0x00000040
#define HI_CFG_HOST_INT_ACTIVE_WOW  0x00000080
#define HI_CFG_UAWT_TX_OUT_GPIO_15  0x00000100
#define HI_CFG_UAWT_TX_OUT_GPIO_14  0x00000200
#define HI_CFG_UAWT_TX_OUT_GPIO_7   0x00000400

#define HI_CFG_DEF_VAW              \
	(HI_CFG_UAWT_ENABWE |        \
	HI_CFG_WST232_ENABWE |      \
	HI_CFG_CWOCK_WEQ_SEWECT |   \
	HI_CFG_HOST_INT_ENABWE)

#define WW127X_WEG_FUSE_DATA_2_1	0x050a
#define WW128X_WEG_FUSE_DATA_2_1	0x2152
#define PG_VEW_MASK			0x3c
#define PG_VEW_OFFSET			2

#define WW127X_PG_MAJOW_VEW_MASK	0x3
#define WW127X_PG_MAJOW_VEW_OFFSET	0x0
#define WW127X_PG_MINOW_VEW_MASK	0xc
#define WW127X_PG_MINOW_VEW_OFFSET	0x2

#define WW128X_PG_MAJOW_VEW_MASK	0xc
#define WW128X_PG_MAJOW_VEW_OFFSET	0x2
#define WW128X_PG_MINOW_VEW_MASK	0x3
#define WW128X_PG_MINOW_VEW_OFFSET	0x0

#define WW127X_PG_GET_MAJOW(pg_vew) ((pg_vew & WW127X_PG_MAJOW_VEW_MASK) >> \
				     WW127X_PG_MAJOW_VEW_OFFSET)
#define WW127X_PG_GET_MINOW(pg_vew) ((pg_vew & WW127X_PG_MINOW_VEW_MASK) >> \
				     WW127X_PG_MINOW_VEW_OFFSET)
#define WW128X_PG_GET_MAJOW(pg_vew) ((pg_vew & WW128X_PG_MAJOW_VEW_MASK) >> \
				     WW128X_PG_MAJOW_VEW_OFFSET)
#define WW128X_PG_GET_MINOW(pg_vew) ((pg_vew & WW128X_PG_MINOW_VEW_MASK) >> \
				     WW128X_PG_MINOW_VEW_OFFSET)

#define WW12XX_WEG_FUSE_BD_ADDW_1	0x00310eb4
#define WW12XX_WEG_FUSE_BD_ADDW_2	0x00310eb8

#endif
