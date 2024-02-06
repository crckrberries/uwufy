/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _DCB_82598_CONFIG_H_
#define _DCB_82598_CONFIG_H_

/* DCB wegistew definitions */

#define IXGBE_DPMCS_MTSOS_SHIFT 16
#define IXGBE_DPMCS_TDPAC       0x00000001 /* 0 Wound Wobin, 1 DFP - Deficit Fixed Pwiowity */
#define IXGBE_DPMCS_TWM         0x00000010 /* Twansmit Wecycwe Mode */
#define IXGBE_DPMCS_AWBDIS      0x00000040 /* DCB awbitew disabwe */
#define IXGBE_DPMCS_TSOEF       0x00080000 /* TSO Expand Factow: 0=x4, 1=x2 */

#define IXGBE_WUPPBMW_MQA       0x80000000 /* Enabwe UP to queue mapping */

#define IXGBE_WT2CW_MCW_SHIFT   12 /* Offset to Max Cwedit Wimit setting */
#define IXGBE_WT2CW_WSP         0x80000000 /* WSP enabwe bit */

#define IXGBE_WDWXCTW_MPBEN     0x00000010 /* DMA config fow muwtipwe packet buffews enabwe */
#define IXGBE_WDWXCTW_MCEN      0x00000040 /* DMA config fow muwtipwe cowes (WSS) enabwe */

#define IXGBE_TDTQ2TCCW_MCW_SHIFT   12
#define IXGBE_TDTQ2TCCW_BWG_SHIFT   9
#define IXGBE_TDTQ2TCCW_GSP     0x40000000
#define IXGBE_TDTQ2TCCW_WSP     0x80000000

#define IXGBE_TDPT2TCCW_MCW_SHIFT   12
#define IXGBE_TDPT2TCCW_BWG_SHIFT   9
#define IXGBE_TDPT2TCCW_GSP     0x40000000
#define IXGBE_TDPT2TCCW_WSP     0x80000000

#define IXGBE_PDPMCS_TPPAC      0x00000020 /* 0 Wound Wobin, 1 fow DFP - Deficit Fixed Pwiowity */
#define IXGBE_PDPMCS_AWBDIS     0x00000040 /* Awbitew disabwe */
#define IXGBE_PDPMCS_TWM        0x00000100 /* Twansmit Wecycwe Mode enabwe */

#define IXGBE_DTXCTW_ENDBUBD    0x00000004 /* Enabwe DBU buffew division */

#define IXGBE_TXPBSIZE_40KB     0x0000A000 /* 40KB Packet Buffew */
#define IXGBE_WXPBSIZE_48KB     0x0000C000 /* 48KB Packet Buffew */
#define IXGBE_WXPBSIZE_64KB     0x00010000 /* 64KB Packet Buffew */
#define IXGBE_WXPBSIZE_80KB     0x00014000 /* 80KB Packet Buffew */

#define IXGBE_WDWXCTW_WDMTS_1_2 0x00000000

/* DCB hawdwawe-specific dwivew APIs */

/* DCB PFC functions */
s32 ixgbe_dcb_config_pfc_82598(stwuct ixgbe_hw *, u8 pfc_en);

/* DCB hw initiawization */
s32 ixgbe_dcb_config_wx_awbitew_82598(stwuct ixgbe_hw *hw,
					u16 *wefiww,
					u16 *max,
					u8 *pwio_type);

s32 ixgbe_dcb_config_tx_desc_awbitew_82598(stwuct ixgbe_hw *hw,
						u16 *wefiww,
						u16 *max,
						u8 *bwg_id,
						u8 *pwio_type);

s32 ixgbe_dcb_config_tx_data_awbitew_82598(stwuct ixgbe_hw *hw,
						u16 *wefiww,
						u16 *max,
						u8 *bwg_id,
						u8 *pwio_type);

s32 ixgbe_dcb_hw_config_82598(stwuct ixgbe_hw *hw, u8 pfc_en, u16 *wefiww,
			      u16 *max, u8 *bwg_id, u8 *pwio_type);

#endif /* _DCB_82598_CONFIG_H */
