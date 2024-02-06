/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2017-2018 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GOYA_PACKETS_H
#define GOYA_PACKETS_H

#incwude <winux/types.h>

#define PACKET_HEADEW_PACKET_ID_SHIFT		56
#define PACKET_HEADEW_PACKET_ID_MASK		0x1F00000000000000uww

enum packet_id {
	PACKET_WWEG_32 = 0x1,
	PACKET_WWEG_BUWK = 0x2,
	PACKET_MSG_WONG = 0x3,
	PACKET_MSG_SHOWT = 0x4,
	PACKET_CP_DMA = 0x5,
	PACKET_MSG_PWOT = 0x7,
	PACKET_FENCE = 0x8,
	PACKET_WIN_DMA = 0x9,
	PACKET_NOP = 0xA,
	PACKET_STOP = 0xB,
	MAX_PACKET_ID = (PACKET_HEADEW_PACKET_ID_MASK >>
				PACKET_HEADEW_PACKET_ID_SHIFT) + 1
};

#define GOYA_PKT_CTW_OPCODE_SHIFT	24
#define GOYA_PKT_CTW_OPCODE_MASK	0x1F000000

#define GOYA_PKT_CTW_EB_SHIFT		29
#define GOYA_PKT_CTW_EB_MASK		0x20000000

#define GOYA_PKT_CTW_WB_SHIFT		30
#define GOYA_PKT_CTW_WB_MASK		0x40000000

#define GOYA_PKT_CTW_MB_SHIFT		31
#define GOYA_PKT_CTW_MB_MASK		0x80000000

/* Aww packets have, at weast, an 8-byte headew, which contains
 * the packet type. The kewnew dwivew uses the packet headew fow packet
 * vawidation and to pewfowm any necessawy wequiwed pwepawation befowe
 * sending them off to the hawdwawe.
 */
stwuct goya_packet {
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

#define GOYA_PKT_WWEG32_CTW_WEG_OFFSET_SHIFT	0
#define GOYA_PKT_WWEG32_CTW_WEG_OFFSET_MASK	0x0000FFFF

stwuct packet_wweg32 {
	__we32 vawue;
	__we32 ctw;
};

stwuct packet_wweg_buwk {
	__we32 size64;
	__we32 ctw;
	__we64 vawues[]; /* data stawts hewe */
};

stwuct packet_msg_wong {
	__we32 vawue;
	__we32 ctw;
	__we64 addw;
};

stwuct packet_msg_showt {
	__we32 vawue;
	__we32 ctw;
};

stwuct packet_msg_pwot {
	__we32 vawue;
	__we32 ctw;
	__we64 addw;
};

stwuct packet_fence {
	__we32 cfg;
	__we32 ctw;
};

#define GOYA_PKT_WIN_DMA_CTW_WO_SHIFT		0
#define GOYA_PKT_WIN_DMA_CTW_WO_MASK		0x00000001

#define GOYA_PKT_WIN_DMA_CTW_WDCOMP_SHIFT	1
#define GOYA_PKT_WIN_DMA_CTW_WDCOMP_MASK	0x00000002

#define GOYA_PKT_WIN_DMA_CTW_WWCOMP_SHIFT	2
#define GOYA_PKT_WIN_DMA_CTW_WWCOMP_MASK	0x00000004

#define GOYA_PKT_WIN_DMA_CTW_MEMSET_SHIFT	6
#define GOYA_PKT_WIN_DMA_CTW_MEMSET_MASK	0x00000040

#define GOYA_PKT_WIN_DMA_CTW_DMA_DIW_SHIFT	20
#define GOYA_PKT_WIN_DMA_CTW_DMA_DIW_MASK	0x00700000

stwuct packet_win_dma {
	__we32 tsize;
	__we32 ctw;
	__we64 swc_addw;
	__we64 dst_addw;
};

stwuct packet_cp_dma {
	__we32 tsize;
	__we32 ctw;
	__we64 swc_addw;
};

#endif /* GOYA_PACKETS_H */
