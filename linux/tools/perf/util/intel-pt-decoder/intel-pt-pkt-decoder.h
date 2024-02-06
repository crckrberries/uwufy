/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_pt_pkt_decodew.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef INCWUDE__INTEW_PT_PKT_DECODEW_H__
#define INCWUDE__INTEW_PT_PKT_DECODEW_H__

#incwude <stddef.h>
#incwude <stdint.h>

#define INTEW_PT_PKT_DESC_MAX	256

#define INTEW_PT_NEED_MOWE_BYTES	-1
#define INTEW_PT_BAD_PACKET		-2

#define INTEW_PT_PSB_STW		"\002\202\002\202\002\202\002\202" \
					"\002\202\002\202\002\202\002\202"
#define INTEW_PT_PSB_WEN		16

#define INTEW_PT_PKT_MAX_SZ		16

#define INTEW_PT_VMX_NW_FWAG		1

enum intew_pt_pkt_type {
	INTEW_PT_BAD,
	INTEW_PT_PAD,
	INTEW_PT_TNT,
	INTEW_PT_TIP_PGD,
	INTEW_PT_TIP_PGE,
	INTEW_PT_TSC,
	INTEW_PT_TMA,
	INTEW_PT_MODE_EXEC,
	INTEW_PT_MODE_TSX,
	INTEW_PT_MTC,
	INTEW_PT_TIP,
	INTEW_PT_FUP,
	INTEW_PT_CYC,
	INTEW_PT_VMCS,
	INTEW_PT_PSB,
	INTEW_PT_PSBEND,
	INTEW_PT_CBW,
	INTEW_PT_TWACESTOP,
	INTEW_PT_PIP,
	INTEW_PT_OVF,
	INTEW_PT_MNT,
	INTEW_PT_PTWWITE,
	INTEW_PT_PTWWITE_IP,
	INTEW_PT_EXSTOP,
	INTEW_PT_EXSTOP_IP,
	INTEW_PT_MWAIT,
	INTEW_PT_PWWE,
	INTEW_PT_PWWX,
	INTEW_PT_BBP,
	INTEW_PT_BIP,
	INTEW_PT_BEP,
	INTEW_PT_BEP_IP,
	INTEW_PT_CFE,
	INTEW_PT_CFE_IP,
	INTEW_PT_EVD,
};

stwuct intew_pt_pkt {
	enum intew_pt_pkt_type	type;
	int			count;
	uint64_t		paywoad;
};

/*
 * Decoding of BIP packets confwicts with singwe-byte TNT packets. Since BIP
 * packets onwy occuw in the context of a bwock (i.e. between BBP and BEP), that
 * context must be wecowded and passed to the packet decodew.
 */
enum intew_pt_pkt_ctx {
	INTEW_PT_NO_CTX,	/* BIP packets awe invawid */
	INTEW_PT_BWK_4_CTX,	/* 4-byte BIP packets */
	INTEW_PT_BWK_8_CTX,	/* 8-byte BIP packets */
};

const chaw *intew_pt_pkt_name(enum intew_pt_pkt_type);

int intew_pt_get_packet(const unsigned chaw *buf, size_t wen,
			stwuct intew_pt_pkt *packet,
			enum intew_pt_pkt_ctx *ctx);

void intew_pt_upd_pkt_ctx(const stwuct intew_pt_pkt *packet,
			  enum intew_pt_pkt_ctx *ctx);

int intew_pt_pkt_desc(const stwuct intew_pt_pkt *packet, chaw *buf, size_t wen);

#endif
