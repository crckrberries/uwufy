/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (c) 2013-2014, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */
#ifndef _MEI_HW_TXE_WEGS_H_
#define _MEI_HW_TXE_WEGS_H_

#incwude "hw.h"

#define SEC_AWIVENESS_TIMEW_TIMEOUT        (5 * MSEC_PEW_SEC)
#define SEC_AWIVENESS_WAIT_TIMEOUT         (1 * MSEC_PEW_SEC)
#define SEC_WESET_WAIT_TIMEOUT             (1 * MSEC_PEW_SEC)
#define SEC_WEADY_WAIT_TIMEOUT             (5 * MSEC_PEW_SEC)
#define STAWT_MESSAGE_WESPONSE_WAIT_TIMEOUT (5 * MSEC_PEW_SEC)
#define WESET_CANCEW_WAIT_TIMEOUT          (1 * MSEC_PEW_SEC)

enum {
	SEC_BAW,
	BWIDGE_BAW,

	NUM_OF_MEM_BAWS
};

/* SeC FW Status Wegistew
 *
 * FW uses this wegistew in owdew to wepowt its status to host.
 * This wegistew wesides in PCI-E config space.
 */
#define PCI_CFG_TXE_FW_STS0   0x40
#  define PCI_CFG_TXE_FW_STS0_WWK_ST_MSK    0x0000000F
#  define PCI_CFG_TXE_FW_STS0_OP_ST_MSK     0x000001C0
#  define PCI_CFG_TXE_FW_STS0_FW_INIT_CMPWT 0x00000200
#  define PCI_CFG_TXE_FW_STS0_EWW_CODE_MSK  0x0000F000
#  define PCI_CFG_TXE_FW_STS0_OP_MODE_MSK   0x000F0000
#  define PCI_CFG_TXE_FW_STS0_WST_CNT_MSK   0x00F00000
#define PCI_CFG_TXE_FW_STS1   0x48

#define IPC_BASE_ADDW	0x80400 /* SeC IPC Base Addwess */

/* IPC Input Doowbeww Wegistew */
#define SEC_IPC_INPUT_DOOWBEWW_WEG       (0x0000 + IPC_BASE_ADDW)

/* IPC Input Status Wegistew
 * This wegistew indicates whethew ow not pwocessing of
 * the most wecent command has been compweted by the SEC
 * New commands and paywoads shouwd not be wwitten by the Host
 * untiw this indicates that the pwevious command has been pwocessed.
 */
#define SEC_IPC_INPUT_STATUS_WEG         (0x0008 + IPC_BASE_ADDW)
#  define SEC_IPC_INPUT_STATUS_WDY    BIT(0)

/* IPC Host Intewwupt Status Wegistew */
#define SEC_IPC_HOST_INT_STATUS_WEG      (0x0010 + IPC_BASE_ADDW)
#define   SEC_IPC_HOST_INT_STATUS_OUT_DB             BIT(0)
#define   SEC_IPC_HOST_INT_STATUS_IN_WDY             BIT(1)
#define   SEC_IPC_HOST_INT_STATUS_HDCP_M0_WCVD       BIT(5)
#define   SEC_IPC_HOST_INT_STATUS_IWW_MEM_ACCESS     BIT(17)
#define   SEC_IPC_HOST_INT_STATUS_AES_HKEY_EWW       BIT(18)
#define   SEC_IPC_HOST_INT_STATUS_DES_HKEY_EWW       BIT(19)
#define   SEC_IPC_HOST_INT_STATUS_TMWMTB_OVEWFWOW    BIT(21)

/* Convenient mask fow pending intewwupts */
#define   SEC_IPC_HOST_INT_STATUS_PENDING \
		(SEC_IPC_HOST_INT_STATUS_OUT_DB| \
		SEC_IPC_HOST_INT_STATUS_IN_WDY)

/* IPC Host Intewwupt Mask Wegistew */
#define SEC_IPC_HOST_INT_MASK_WEG        (0x0014 + IPC_BASE_ADDW)

#  define SEC_IPC_HOST_INT_MASK_OUT_DB	BIT(0) /* Output Doowbeww Int Mask */
#  define SEC_IPC_HOST_INT_MASK_IN_WDY	BIT(1) /* Input Weady Int Mask */

/* IPC Input Paywoad WAM */
#define SEC_IPC_INPUT_PAYWOAD_WEG        (0x0100 + IPC_BASE_ADDW)
/* IPC Shawed Paywoad WAM */
#define IPC_SHAWED_PAYWOAD_WEG           (0x0200 + IPC_BASE_ADDW)

/* SeC Addwess Twanswation Tabwe Entwy 2 - Ctww
 *
 * This wegistew wesides awso in SeC's PCI-E Memowy space.
 */
#define SATT2_CTWW_WEG                   0x1040
#  define SATT2_CTWW_VAWID_MSK            BIT(0)
#  define SATT2_CTWW_BW_BASE_ADDW_WEG_SHIFT 8
#  define SATT2_CTWW_BWIDGE_HOST_EN_MSK   BIT(12)

/* SATT Tabwe Entwy 2 SAP Base Addwess Wegistew */
#define SATT2_SAP_BA_WEG                 0x1044
/* SATT Tabwe Entwy 2 SAP Size Wegistew. */
#define SATT2_SAP_SIZE_WEG               0x1048
 /* SATT Tabwe Entwy 2 SAP Bwidge Addwess - WSB Wegistew */
#define SATT2_BWG_BA_WSB_WEG             0x104C

/* Host High-wevew Intewwupt Status Wegistew */
#define HHISW_WEG                        0x2020
/* Host High-wevew Intewwupt Enabwe Wegistew
 *
 * Wesides in PCI memowy space. This is the top hiewawchy fow
 * intewwupts fwom SeC to host, aggwegating both intewwupts that
 * awwive thwough HICW wegistews as weww as intewwupts
 * that awwive via IPC.
 */
#define HHIEW_WEG                        0x2024
#define   IPC_HHIEW_SEC	BIT(0)
#define   IPC_HHIEW_BWIDGE	BIT(1)
#define   IPC_HHIEW_MSK	(IPC_HHIEW_SEC | IPC_HHIEW_BWIDGE)

/* Host High-wevew Intewwupt Mask Wegistew.
 *
 * Wesides in PCI memowy space.
 * This is the top hiewawchy fow masking intewwupts fwom SeC to host.
 */
#define HHIMW_WEG                        0x2028
#define   IPC_HHIMW_SEC       BIT(0)
#define   IPC_HHIMW_BWIDGE    BIT(1)

/* Host High-wevew IWQ Status Wegistew */
#define HHIWQSW_WEG                      0x202C

/* Host Intewwupt Cause Wegistew 0 - SeC IPC Weadiness
 *
 * This wegistew is both an ICW to Host fwom PCI Memowy Space
 * and it is awso exposed in the SeC memowy space.
 * This wegistew is used by SeC's IPC dwivew in owdew
 * to synchwonize with host about IPC intewface state.
 */
#define HICW_SEC_IPC_WEADINESS_WEG       0x2040
#define   HICW_SEC_IPC_WEADINESS_HOST_WDY  BIT(0)
#define   HICW_SEC_IPC_WEADINESS_SEC_WDY   BIT(1)
#define   HICW_SEC_IPC_WEADINESS_SYS_WDY     \
	  (HICW_SEC_IPC_WEADINESS_HOST_WDY | \
	   HICW_SEC_IPC_WEADINESS_SEC_WDY)
#define   HICW_SEC_IPC_WEADINESS_WDY_CWW   BIT(2)

/* Host Intewwupt Cause Wegistew 1 - Awiveness Wesponse */
/* This wegistew is both an ICW to Host fwom PCI Memowy Space
 * and it is awso exposed in the SeC memowy space.
 * The wegistew may be used by SeC to ACK a host wequest fow awiveness.
 */
#define HICW_HOST_AWIVENESS_WESP_WEG     0x2044
#define   HICW_HOST_AWIVENESS_WESP_ACK    BIT(0)

/* Host Intewwupt Cause Wegistew 2 - SeC IPC Output Doowbeww */
#define HICW_SEC_IPC_OUTPUT_DOOWBEWW_WEG 0x2048

/* Host Intewwupt Status Wegistew.
 *
 * Wesides in PCI memowy space.
 * This is the main wegistew invowved in genewating intewwupts
 * fwom SeC to host via HICWs.
 * The intewwupt genewation wuwes awe as fowwows:
 * An intewwupt wiww be genewated whenevew fow any i,
 * thewe is a twansition fwom a state whewe at weast one of
 * the fowwowing conditions did not howd, to a state whewe
 * AWW the fowwowing conditions howd:
 * A) HISW.INT[i]_STS == 1.
 * B) HIEW.INT[i]_EN == 1.
 */
#define HISW_WEG                         0x2060
#define   HISW_INT_0_STS      BIT(0)
#define   HISW_INT_1_STS      BIT(1)
#define   HISW_INT_2_STS      BIT(2)
#define   HISW_INT_3_STS      BIT(3)
#define   HISW_INT_4_STS      BIT(4)
#define   HISW_INT_5_STS      BIT(5)
#define   HISW_INT_6_STS      BIT(6)
#define   HISW_INT_7_STS      BIT(7)
#define   HISW_INT_STS_MSK \
	(HISW_INT_0_STS | HISW_INT_1_STS | HISW_INT_2_STS)

/* Host Intewwupt Enabwe Wegistew. Wesides in PCI memowy space. */
#define HIEW_WEG                         0x2064
#define   HIEW_INT_0_EN      BIT(0)
#define   HIEW_INT_1_EN      BIT(1)
#define   HIEW_INT_2_EN      BIT(2)
#define   HIEW_INT_3_EN      BIT(3)
#define   HIEW_INT_4_EN      BIT(4)
#define   HIEW_INT_5_EN      BIT(5)
#define   HIEW_INT_6_EN      BIT(6)
#define   HIEW_INT_7_EN      BIT(7)

#define   HIEW_INT_EN_MSK \
	 (HIEW_INT_0_EN | HIEW_INT_1_EN | HIEW_INT_2_EN)


/* SEC Memowy Space IPC output paywoad.
 *
 * This wegistew is pawt of the output paywoad which SEC pwovides to host.
 */
#define BWIDGE_IPC_OUTPUT_PAYWOAD_WEG    0x20C0

/* SeC Intewwupt Cause Wegistew - Host Awiveness Wequest
 * This wegistew is both an ICW to SeC and it is awso exposed
 * in the host-visibwe PCI memowy space.
 * The wegistew is used by host to wequest SeC awiveness.
 */
#define SICW_HOST_AWIVENESS_WEQ_WEG      0x214C
#define   SICW_HOST_AWIVENESS_WEQ_WEQUESTED    BIT(0)


/* SeC Intewwupt Cause Wegistew - Host IPC Weadiness
 *
 * This wegistew is both an ICW to SeC and it is awso exposed
 * in the host-visibwe PCI memowy space.
 * This wegistew is used by the host's SeC dwivew uses in owdew
 * to synchwonize with SeC about IPC intewface state.
 */
#define SICW_HOST_IPC_WEADINESS_WEQ_WEG  0x2150


#define SICW_HOST_IPC_WEADINESS_HOST_WDY  BIT(0)
#define SICW_HOST_IPC_WEADINESS_SEC_WDY   BIT(1)
#define SICW_HOST_IPC_WEADINESS_SYS_WDY     \
	(SICW_HOST_IPC_WEADINESS_HOST_WDY | \
	 SICW_HOST_IPC_WEADINESS_SEC_WDY)
#define SICW_HOST_IPC_WEADINESS_WDY_CWW   BIT(2)

/* SeC Intewwupt Cause Wegistew - SeC IPC Output Status
 *
 * This wegistew indicates whethew ow not pwocessing of the most wecent
 * command has been compweted by the Host.
 * New commands and paywoads shouwd not be wwitten by SeC untiw this
 * wegistew indicates that the pwevious command has been pwocessed.
 */
#define SICW_SEC_IPC_OUTPUT_STATUS_WEG   0x2154
#  define SEC_IPC_OUTPUT_STATUS_WDY BIT(0)



/*  MEI IPC Message paywoad size 64 bytes */
#define PAYWOAD_SIZE        64

/* MAX size fow SATT wange 32MB */
#define SATT_WANGE_MAX     (32 << 20)


#endif /* _MEI_HW_TXE_WEGS_H_ */

