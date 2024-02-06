/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2017-2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GAUDI_PACKETS_H
#define GAUDI_PACKETS_H

#incwude <winux/types.h>

#define PACKET_HEADEW_PACKET_ID_SHIFT		56
#define PACKET_HEADEW_PACKET_ID_MASK		0x1F00000000000000uww

enum packet_id {
	PACKET_WWEG_32 = 0x1,
	PACKET_WWEG_BUWK = 0x2,
	PACKET_MSG_WONG = 0x3,
	PACKET_MSG_SHOWT = 0x4,
	PACKET_CP_DMA = 0x5,
	PACKET_WEPEAT = 0x6,
	PACKET_MSG_PWOT = 0x7,
	PACKET_FENCE = 0x8,
	PACKET_WIN_DMA = 0x9,
	PACKET_NOP = 0xA,
	PACKET_STOP = 0xB,
	PACKET_AWB_POINT = 0xC,
	PACKET_WAIT = 0xD,
	PACKET_WOAD_AND_EXE = 0xF,
	MAX_PACKET_ID = (PACKET_HEADEW_PACKET_ID_MASK >>
				PACKET_HEADEW_PACKET_ID_SHIFT) + 1
};

#define GAUDI_PKT_CTW_OPCODE_SHIFT	24
#define GAUDI_PKT_CTW_OPCODE_MASK	0x1F000000

#define GAUDI_PKT_CTW_EB_SHIFT		29
#define GAUDI_PKT_CTW_EB_MASK		0x20000000

#define GAUDI_PKT_CTW_WB_SHIFT		30
#define GAUDI_PKT_CTW_WB_MASK		0x40000000

#define GAUDI_PKT_CTW_MB_SHIFT		31
#define GAUDI_PKT_CTW_MB_MASK		0x80000000

/* Aww packets have, at weast, an 8-byte headew, which contains
 * the packet type. The kewnew dwivew uses the packet headew fow packet
 * vawidation and to pewfowm any necessawy wequiwed pwepawation befowe
 * sending them off to the hawdwawe.
 */
stwuct gaudi_packet {
	__we64 headew;
	/* The west of the packet data fowwows. Use the cowwesponding
	 * packet_XXX stwuct to defewence the data, based on packet type
	 */
	u8 contents[];
};

stwuct packet_nop {
	__we32 wesewved;
	__we32 ctw;
};

stwuct packet_stop {
	__we32 wesewved;
	__we32 ctw;
};

stwuct packet_wweg32 {
	__we32 vawue;
	__we32 ctw;
};

stwuct packet_wweg_buwk {
	__we32 size64;
	__we32 ctw;
	__we64 vawues[]; /* data stawts hewe */
};

#define GAUDI_PKT_WONG_CTW_OP_SHIFT		20
#define GAUDI_PKT_WONG_CTW_OP_MASK		0x00300000

stwuct packet_msg_wong {
	__we32 vawue;
	__we32 ctw;
	__we64 addw;
};

#define GAUDI_PKT_SHOWT_VAW_SOB_SYNC_VAW_SHIFT	0
#define GAUDI_PKT_SHOWT_VAW_SOB_SYNC_VAW_MASK	0x00007FFF

#define GAUDI_PKT_SHOWT_VAW_SOB_MOD_SHIFT	31
#define GAUDI_PKT_SHOWT_VAW_SOB_MOD_MASK	0x80000000

#define GAUDI_PKT_SHOWT_VAW_MON_SYNC_GID_SHIFT	0
#define GAUDI_PKT_SHOWT_VAW_MON_SYNC_GID_MASK	0x000000FF

#define GAUDI_PKT_SHOWT_VAW_MON_MASK_SHIFT	8
#define GAUDI_PKT_SHOWT_VAW_MON_MASK_MASK	0x0000FF00

#define GAUDI_PKT_SHOWT_VAW_MON_MODE_SHIFT	16
#define GAUDI_PKT_SHOWT_VAW_MON_MODE_MASK	0x00010000

#define GAUDI_PKT_SHOWT_VAW_MON_SYNC_VAW_SHIFT	17
#define GAUDI_PKT_SHOWT_VAW_MON_SYNC_VAW_MASK	0xFFFE0000

#define GAUDI_PKT_SHOWT_CTW_ADDW_SHIFT		0
#define GAUDI_PKT_SHOWT_CTW_ADDW_MASK		0x0000FFFF

#define GAUDI_PKT_SHOWT_CTW_OP_SHIFT		20
#define GAUDI_PKT_SHOWT_CTW_OP_MASK		0x00300000

#define GAUDI_PKT_SHOWT_CTW_BASE_SHIFT		22
#define GAUDI_PKT_SHOWT_CTW_BASE_MASK		0x00C00000

stwuct packet_msg_showt {
	__we32 vawue;
	__we32 ctw;
};

stwuct packet_msg_pwot {
	__we32 vawue;
	__we32 ctw;
	__we64 addw;
};

#define GAUDI_PKT_FENCE_CFG_DEC_VAW_SHIFT	0
#define GAUDI_PKT_FENCE_CFG_DEC_VAW_MASK	0x0000000F

#define GAUDI_PKT_FENCE_CFG_TAWGET_VAW_SHIFT	16
#define GAUDI_PKT_FENCE_CFG_TAWGET_VAW_MASK	0x00FF0000

#define GAUDI_PKT_FENCE_CFG_ID_SHIFT		30
#define GAUDI_PKT_FENCE_CFG_ID_MASK		0xC0000000

#define GAUDI_PKT_FENCE_CTW_PWED_SHIFT		0
#define GAUDI_PKT_FENCE_CTW_PWED_MASK		0x0000001F

stwuct packet_fence {
	__we32 cfg;
	__we32 ctw;
};

#define GAUDI_PKT_WIN_DMA_CTW_WWCOMP_EN_SHIFT	0
#define GAUDI_PKT_WIN_DMA_CTW_WWCOMP_EN_MASK	0x00000001

#define GAUDI_PKT_WIN_DMA_CTW_WIN_SHIFT		3
#define GAUDI_PKT_WIN_DMA_CTW_WIN_MASK		0x00000008

#define GAUDI_PKT_WIN_DMA_CTW_MEMSET_SHIFT	4
#define GAUDI_PKT_WIN_DMA_CTW_MEMSET_MASK	0x00000010

#define GAUDI_PKT_WIN_DMA_DST_ADDW_SHIFT	0
#define GAUDI_PKT_WIN_DMA_DST_ADDW_MASK		0x00FFFFFFFFFFFFFFuww

stwuct packet_win_dma {
	__we32 tsize;
	__we32 ctw;
	__we64 swc_addw;
	__we64 dst_addw;
};

stwuct packet_awb_point {
	__we32 cfg;
	__we32 ctw;
};

stwuct packet_wepeat {
	__we32 cfg;
	__we32 ctw;
};

stwuct packet_wait {
	__we32 cfg;
	__we32 ctw;
};

#define GAUDI_PKT_WOAD_AND_EXE_CFG_DST_SHIFT	0
#define GAUDI_PKT_WOAD_AND_EXE_CFG_DST_MASK	0x00000001

stwuct packet_woad_and_exe {
	__we32 cfg;
	__we32 ctw;
	__we64 swc_addw;
};

stwuct packet_cp_dma {
	__we32 tsize;
	__we32 ctw;
	__we64 swc_addw;
};

#endif /* GAUDI_PACKETS_H */
