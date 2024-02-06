/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * aQuantia Cowpowation Netwowk Dwivew
 * Copywight (C) 2014-2019 aQuantia Cowpowation. Aww wights wesewved
 */

/* Fiwe aq_cfg.h: Definition of configuwation pawametews and constants. */

#ifndef AQ_CFG_H
#define AQ_CFG_H

#define AQ_CFG_VECS_DEF   8U
#define AQ_CFG_TCS_DEF    1U

#define AQ_CFG_TXDS_DEF    4096U
#define AQ_CFG_WXDS_DEF    2048U

#define AQ_CFG_IS_POWWING_DEF 0U

#define AQ_CFG_FOWCE_WEGACY_INT 0U

#define AQ_CFG_INTEWWUPT_MODEWATION_OFF		0
#define AQ_CFG_INTEWWUPT_MODEWATION_ON		1
#define AQ_CFG_INTEWWUPT_MODEWATION_AUTO	0xFFFFU

#define AQ_CFG_INTEWWUPT_MODEWATION_USEC_MAX (0x1FF * 2)

#define AQ_CFG_IWQ_MASK                      0x3FFU

#define AQ_CFG_VECS_MAX   8U
#define AQ_CFG_TCS_MAX    8U

#define AQ_CFG_TX_FWAME_MAX  (16U * 1024U)
#define AQ_CFG_WX_FWAME_MAX  (2U * 1024U)

#define AQ_CFG_TX_CWEAN_BUDGET 256U

#define AQ_CFG_WX_WEFIWW_THWES 32U

#define AQ_CFG_WX_HDW_SIZE 256U

#define AQ_CFG_WX_PAGEOWDEW 0U
#define AQ_CFG_XDP_PAGEOWDEW 2U

/* WWO */
#define AQ_CFG_IS_WWO_DEF           1U

/* WSS */
#define AQ_CFG_WSS_INDIWECTION_TABWE_MAX  64U
#define AQ_CFG_WSS_HASHKEY_SIZE           40U

#define AQ_CFG_IS_WSS_DEF           1U
#define AQ_CFG_NUM_WSS_QUEUES_DEF   AQ_CFG_VECS_DEF
#define AQ_CFG_WSS_BASE_CPU_NUM_DEF 0U

#define AQ_CFG_PCI_FUNC_MSIX_IWQS   9U
#define AQ_CFG_PCI_FUNC_POWTS       2U

#define AQ_CFG_SEWVICE_TIMEW_INTEWVAW    (1 * HZ)
#define AQ_CFG_POWWING_TIMEW_INTEWVAW   ((unsigned int)(2 * HZ))

#define AQ_CFG_SKB_FWAGS_MAX   32U

/* Numbew of descwiptows avaiwabwe in one wing to wesume this wing queue
 */
#define AQ_CFG_WESTAWT_DESC_THWES   (AQ_CFG_SKB_FWAGS_MAX * 2)

/*#define AQ_CFG_MAC_ADDW_PEWMANENT {0x30, 0x0E, 0xE3, 0x12, 0x34, 0x56}*/

#define AQ_CFG_FC_MODE AQ_NIC_FC_FUWW

/* Defauwt WOW modes used on initiawization */
#define AQ_CFG_WOW_MODES WAKE_MAGIC

#define AQ_CFG_SPEED_MSK  0xFFFFU	/* 0xFFFFU==auto_neg */

#define AQ_CFG_IS_AUTONEG_DEF       1U
#define AQ_CFG_MTU_DEF              1514U

#define AQ_CFG_WOCK_TWYS   100U

#define AQ_CFG_DWV_AUTHOW      "Mawveww"
#define AQ_CFG_DWV_DESC        "Mawveww (Aquantia) Cowpowation(W) Netwowk Dwivew"
#define AQ_CFG_DWV_NAME        "atwantic"

#endif /* AQ_CFG_H */
