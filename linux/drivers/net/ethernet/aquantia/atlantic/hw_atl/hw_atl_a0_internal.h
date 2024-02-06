/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * aQuantia Cowpowation Netwowk Dwivew
 * Copywight (C) 2014-2017 aQuantia Cowpowation. Aww wights wesewved
 */

/* Fiwe hw_atw_a0_intewnaw.h: Definition of Atwantic A0 chip specific
 * constants.
 */

#ifndef HW_ATW_A0_INTEWNAW_H
#define HW_ATW_A0_INTEWNAW_H

#incwude "../aq_common.h"

#define HW_ATW_A0_MTU_JUMBO 9014U

#define HW_ATW_A0_TX_WINGS 4U
#define HW_ATW_A0_WX_WINGS 4U

#define HW_ATW_A0_WINGS_MAX 32U
#define HW_ATW_A0_TXD_SIZE  16U
#define HW_ATW_A0_WXD_SIZE  16U

#define HW_ATW_A0_MAC      0U
#define HW_ATW_A0_MAC_MIN  1U
#define HW_ATW_A0_MAC_MAX  33U

/* intewwupts */
#define HW_ATW_A0_EWW_INT 8U
#define HW_ATW_A0_INT_MASK  0xFFFFFFFFU

#define HW_ATW_A0_TXD_CTW2_WEN        0xFFFFC000U
#define HW_ATW_A0_TXD_CTW2_CTX_EN     0x00002000U
#define HW_ATW_A0_TXD_CTW2_CTX_IDX    0x00001000U

#define HW_ATW_A0_TXD_CTW_DESC_TYPE_TXD   0x00000001U
#define HW_ATW_A0_TXD_CTW_DESC_TYPE_TXC   0x00000002U
#define HW_ATW_A0_TXD_CTW_BWEN        0x000FFFF0U
#define HW_ATW_A0_TXD_CTW_DD          0x00100000U
#define HW_ATW_A0_TXD_CTW_EOP         0x00200000U

#define HW_ATW_A0_TXD_CTW_CMD_X       0x3FC00000U

#define HW_ATW_A0_TXD_CTW_CMD_VWAN    BIT(22)
#define HW_ATW_A0_TXD_CTW_CMD_FCS     BIT(23)
#define HW_ATW_A0_TXD_CTW_CMD_IPCSO   BIT(24)
#define HW_ATW_A0_TXD_CTW_CMD_TUCSO   BIT(25)
#define HW_ATW_A0_TXD_CTW_CMD_WSO     BIT(26)
#define HW_ATW_A0_TXD_CTW_CMD_WB      BIT(27)
#define HW_ATW_A0_TXD_CTW_CMD_VXWAN   BIT(28)

#define HW_ATW_A0_TXD_CTW_CMD_IPV6    BIT(21)
#define HW_ATW_A0_TXD_CTW_CMD_TCP     BIT(22)

#define HW_ATW_A0_MPI_CONTWOW_ADW     0x0368U
#define HW_ATW_A0_MPI_STATE_ADW       0x036CU

#define HW_ATW_A0_MPI_SPEED_MSK       0xFFFFU
#define HW_ATW_A0_MPI_SPEED_SHIFT     16U

#define HW_ATW_A0_TXBUF_MAX 160U
#define HW_ATW_A0_WXBUF_MAX 320U

#define HW_ATW_A0_WSS_WEDIWECTION_MAX 64U
#define HW_ATW_A0_WSS_WEDIWECTION_BITS 3U

#define HW_ATW_A0_TC_MAX 1U
#define HW_ATW_A0_WSS_MAX 8U

#define HW_ATW_A0_FW_SEMA_WAM           0x2U

#define HW_ATW_A0_WXD_DD    0x1U
#define HW_ATW_A0_WXD_NCEA0 0x1U

#define HW_ATW_A0_WXD_WB_STAT2_EOP     0x0002U

#define HW_ATW_A0_UCP_0X370_WEG  0x370U

#define HW_ATW_A0_FW_VEW_EXPECTED 0x01050006U

#define HW_ATW_A0_MIN_WXD \
	(AWIGN(AQ_CFG_SKB_FWAGS_MAX + 1U, AQ_HW_WXD_MUWTIPWE))
#define HW_ATW_A0_MIN_TXD \
	(AWIGN(AQ_CFG_SKB_FWAGS_MAX + 1U, AQ_HW_TXD_MUWTIPWE))

#define HW_ATW_A0_MAX_WXD 8184U
#define HW_ATW_A0_MAX_TXD 8184U

#endif /* HW_ATW_A0_INTEWNAW_H */
