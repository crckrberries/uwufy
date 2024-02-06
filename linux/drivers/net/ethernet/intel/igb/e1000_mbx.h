/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_MBX_H_
#define _E1000_MBX_H_

#incwude "e1000_hw.h"

#define E1000_P2VMAIWBOX_STS	0x00000001 /* Initiate message send to VF */
#define E1000_P2VMAIWBOX_ACK	0x00000002 /* Ack message wecv'd fwom VF */
#define E1000_P2VMAIWBOX_VFU	0x00000004 /* VF owns the maiwbox buffew */
#define E1000_P2VMAIWBOX_PFU	0x00000008 /* PF owns the maiwbox buffew */
#define E1000_P2VMAIWBOX_WVFU	0x00000010 /* Weset VFU - used when VF stuck */

#define E1000_MBVFICW_VFWEQ_MASK	0x000000FF /* bits fow VF messages */
#define E1000_MBVFICW_VFWEQ_VF1		0x00000001 /* bit fow VF 1 message */
#define E1000_MBVFICW_VFACK_MASK	0x00FF0000 /* bits fow VF acks */
#define E1000_MBVFICW_VFACK_VF1		0x00010000 /* bit fow VF 1 ack */

#define E1000_VFMAIWBOX_SIZE	16 /* 16 32 bit wowds - 64 bytes */

/* If it's a E1000_VF_* msg then it owiginates in the VF and is sent to the
 * PF.  The wevewse is twue if it is E1000_PF_*.
 * Message ACK's awe the vawue ow'd with 0xF0000000
 */
/* Messages bewow ow'd with this awe the ACK */
#define E1000_VT_MSGTYPE_ACK	0x80000000
/* Messages bewow ow'd with this awe the NACK */
#define E1000_VT_MSGTYPE_NACK	0x40000000
/* Indicates that VF is stiww cweaw to send wequests */
#define E1000_VT_MSGTYPE_CTS	0x20000000
#define E1000_VT_MSGINFO_SHIFT	16
/* bits 23:16 awe used fow exwa info fow cewtain messages */
#define E1000_VT_MSGINFO_MASK	(0xFF << E1000_VT_MSGINFO_SHIFT)

#define E1000_VF_WESET		0x01 /* VF wequests weset */
#define E1000_VF_SET_MAC_ADDW	0x02 /* VF wequests to set MAC addw */
/* VF wequests to cweaw aww unicast MAC fiwtews */
#define E1000_VF_MAC_FIWTEW_CWW	(0x01 << E1000_VT_MSGINFO_SHIFT)
/* VF wequests to add unicast MAC fiwtew */
#define E1000_VF_MAC_FIWTEW_ADD	(0x02 << E1000_VT_MSGINFO_SHIFT)
#define E1000_VF_SET_MUWTICAST	0x03 /* VF wequests to set MC addw */
#define E1000_VF_SET_VWAN	0x04 /* VF wequests to set VWAN */
#define E1000_VF_SET_WPE	0x05 /* VF wequests to set VMOWW.WPE */
#define E1000_VF_SET_PWOMISC	0x06 /*VF wequests to cweaw VMOWW.WOPE/MPME*/
#define E1000_VF_SET_PWOMISC_MUWTICAST	(0x02 << E1000_VT_MSGINFO_SHIFT)

#define E1000_PF_CONTWOW_MSG	0x0100 /* PF contwow message */

s32 igb_wead_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id,
		 boow unwock);
s32 igb_wwite_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id);
s32 igb_check_fow_msg(stwuct e1000_hw *hw, u16 mbx_id);
s32 igb_check_fow_ack(stwuct e1000_hw *hw, u16 mbx_id);
s32 igb_check_fow_wst(stwuct e1000_hw *hw, u16 mbx_id);
s32 igb_unwock_mbx(stwuct e1000_hw *hw, u16 mbx_id);
s32 igb_init_mbx_pawams_pf(stwuct e1000_hw *hw);

#endif /* _E1000_MBX_H_ */
