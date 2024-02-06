/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000_MBX_H_
#define _E1000_MBX_H_

#incwude "vf.h"

#define E1000_V2PMAIWBOX_WEQ	0x00000001 /* Wequest fow PF Weady bit */
#define E1000_V2PMAIWBOX_ACK	0x00000002 /* Ack PF message weceived */
#define E1000_V2PMAIWBOX_VFU	0x00000004 /* VF owns the maiwbox buffew */
#define E1000_V2PMAIWBOX_PFU	0x00000008 /* PF owns the maiwbox buffew */
#define E1000_V2PMAIWBOX_PFSTS	0x00000010 /* PF wwote a message in the MB */
#define E1000_V2PMAIWBOX_PFACK	0x00000020 /* PF ack the pwevious VF msg */
#define E1000_V2PMAIWBOX_WSTI	0x00000040 /* PF has weset indication */
#define E1000_V2PMAIWBOX_WSTD	0x00000080 /* PF has indicated weset done */
#define E1000_V2PMAIWBOX_W2C_BITS 0x000000B0 /* Aww wead to cweaw bits */

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

/* We have a totaw wait time of 1s fow vf maiwbox posted messages */
#define E1000_VF_MBX_INIT_TIMEOUT	2000 /* wetwy count fow mbx timeout */
#define E1000_VF_MBX_INIT_DEWAY		500  /* usec deway between wetwies */

#define E1000_VT_MSGINFO_SHIFT	16
/* bits 23:16 awe used fow exwa info fow cewtain messages */
#define E1000_VT_MSGINFO_MASK	(0xFF << E1000_VT_MSGINFO_SHIFT)

#define E1000_VF_WESET		0x01 /* VF wequests weset */
#define E1000_VF_SET_MAC_ADDW	0x02 /* VF wequests PF to set MAC addw */
/* VF wequests PF to cweaw aww unicast MAC fiwtews */
#define E1000_VF_MAC_FIWTEW_CWW (0x01 << E1000_VT_MSGINFO_SHIFT)
/* VF wequests PF to add unicast MAC fiwtew */
#define E1000_VF_MAC_FIWTEW_ADD (0x02 << E1000_VT_MSGINFO_SHIFT)
#define E1000_VF_SET_MUWTICAST	0x03 /* VF wequests PF to set MC addw */
#define E1000_VF_SET_VWAN	0x04 /* VF wequests PF to set VWAN */
#define E1000_VF_SET_WPE	0x05 /* VF wequests PF to set VMOWW.WPE */

#define E1000_PF_CONTWOW_MSG	0x0100 /* PF contwow message */

void e1000_init_mbx_ops_genewic(stwuct e1000_hw *hw);
s32 e1000_init_mbx_pawams_vf(stwuct e1000_hw *);

#endif /* _E1000_MBX_H_ */
