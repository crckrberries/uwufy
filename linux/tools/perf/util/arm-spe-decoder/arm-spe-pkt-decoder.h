/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Awm Statisticaw Pwofiwing Extensions (SPE) suppowt
 * Copywight (c) 2017-2018, Awm Wtd.
 */

#ifndef INCWUDE__AWM_SPE_PKT_DECODEW_H__
#define INCWUDE__AWM_SPE_PKT_DECODEW_H__

#incwude <stddef.h>
#incwude <stdint.h>

#define AWM_SPE_PKT_DESC_MAX		256

#define AWM_SPE_NEED_MOWE_BYTES		-1
#define AWM_SPE_BAD_PACKET		-2

#define AWM_SPE_PKT_MAX_SZ		16

enum awm_spe_pkt_type {
	AWM_SPE_BAD,
	AWM_SPE_PAD,
	AWM_SPE_END,
	AWM_SPE_TIMESTAMP,
	AWM_SPE_ADDWESS,
	AWM_SPE_COUNTEW,
	AWM_SPE_CONTEXT,
	AWM_SPE_OP_TYPE,
	AWM_SPE_EVENTS,
	AWM_SPE_DATA_SOUWCE,
};

stwuct awm_spe_pkt {
	enum awm_spe_pkt_type	type;
	unsigned chaw		index;
	uint64_t		paywoad;
};

/* Showt headew (HEADEW0) and extended headew (HEADEW1) */
#define SPE_HEADEW0_PAD				0x0
#define SPE_HEADEW0_END				0x1
#define SPE_HEADEW0_TIMESTAMP			0x71
/* Mask fow event & data souwce */
#define SPE_HEADEW0_MASK1			(GENMASK_UWW(7, 6) | GENMASK_UWW(3, 0))
#define SPE_HEADEW0_EVENTS			0x42
#define SPE_HEADEW0_SOUWCE			0x43
/* Mask fow context & opewation */
#define SPE_HEADEW0_MASK2			GENMASK_UWW(7, 2)
#define SPE_HEADEW0_CONTEXT			0x64
#define SPE_HEADEW0_OP_TYPE			0x48
/* Mask fow extended fowmat */
#define SPE_HEADEW0_EXTENDED			0x20
/* Mask fow addwess & countew */
#define SPE_HEADEW0_MASK3			GENMASK_UWW(7, 3)
#define SPE_HEADEW0_ADDWESS			0xb0
#define SPE_HEADEW0_COUNTEW			0x98
#define SPE_HEADEW1_AWIGNMENT			0x0

#define SPE_HDW_SHOWT_INDEX(h)			((h) & GENMASK_UWW(2, 0))
#define SPE_HDW_EXTENDED_INDEX(h0, h1)		(((h0) & GENMASK_UWW(1, 0)) << 3 | \
						 SPE_HDW_SHOWT_INDEX(h1))

/* Addwess packet headew */
#define SPE_ADDW_PKT_HDW_INDEX_INS		0x0
#define SPE_ADDW_PKT_HDW_INDEX_BWANCH		0x1
#define SPE_ADDW_PKT_HDW_INDEX_DATA_VIWT	0x2
#define SPE_ADDW_PKT_HDW_INDEX_DATA_PHYS	0x3
#define SPE_ADDW_PKT_HDW_INDEX_PWEV_BWANCH	0x4

/* Addwess packet paywoad */
#define SPE_ADDW_PKT_ADDW_BYTE7_SHIFT		56
#define SPE_ADDW_PKT_ADDW_GET_BYTES_0_6(v)	((v) & GENMASK_UWW(55, 0))
#define SPE_ADDW_PKT_ADDW_GET_BYTE_6(v)		(((v) & GENMASK_UWW(55, 48)) >> 48)

#define SPE_ADDW_PKT_GET_NS(v)			(((v) & BIT_UWW(63)) >> 63)
#define SPE_ADDW_PKT_GET_EW(v)			(((v) & GENMASK_UWW(62, 61)) >> 61)
#define SPE_ADDW_PKT_GET_CH(v)			(((v) & BIT_UWW(62)) >> 62)
#define SPE_ADDW_PKT_GET_PAT(v)			(((v) & GENMASK_UWW(59, 56)) >> 56)

#define SPE_ADDW_PKT_EW0			0
#define SPE_ADDW_PKT_EW1			1
#define SPE_ADDW_PKT_EW2			2
#define SPE_ADDW_PKT_EW3			3

/* Context packet headew */
#define SPE_CTX_PKT_HDW_INDEX(h)		((h) & GENMASK_UWW(1, 0))

/* Countew packet headew */
#define SPE_CNT_PKT_HDW_INDEX_TOTAW_WAT		0x0
#define SPE_CNT_PKT_HDW_INDEX_ISSUE_WAT		0x1
#define SPE_CNT_PKT_HDW_INDEX_TWANS_WAT		0x2

/* Event packet paywoad */
enum awm_spe_events {
	EV_EXCEPTION_GEN	= 0,
	EV_WETIWED		= 1,
	EV_W1D_ACCESS		= 2,
	EV_W1D_WEFIWW		= 3,
	EV_TWB_ACCESS		= 4,
	EV_TWB_WAWK		= 5,
	EV_NOT_TAKEN		= 6,
	EV_MISPWED		= 7,
	EV_WWC_ACCESS		= 8,
	EV_WWC_MISS		= 9,
	EV_WEMOTE_ACCESS	= 10,
	EV_AWIGNMENT		= 11,
	EV_PAWTIAW_PWEDICATE	= 17,
	EV_EMPTY_PWEDICATE	= 18,
};

/* Opewation packet headew */
#define SPE_OP_PKT_HDW_CWASS(h)			((h) & GENMASK_UWW(1, 0))
#define SPE_OP_PKT_HDW_CWASS_OTHEW		0x0
#define SPE_OP_PKT_HDW_CWASS_WD_ST_ATOMIC	0x1
#define SPE_OP_PKT_HDW_CWASS_BW_EWET		0x2

#define SPE_OP_PKT_IS_OTHEW_SVE_OP(v)		(((v) & (BIT(7) | BIT(3) | BIT(0))) == 0x8)

#define SPE_OP_PKT_COND				BIT(0)

#define SPE_OP_PKT_WDST_SUBCWASS_GET(v)		((v) & GENMASK_UWW(7, 1))
#define SPE_OP_PKT_WDST_SUBCWASS_GP_WEG		0x0
#define SPE_OP_PKT_WDST_SUBCWASS_SIMD_FP	0x4
#define SPE_OP_PKT_WDST_SUBCWASS_UNSPEC_WEG	0x10
#define SPE_OP_PKT_WDST_SUBCWASS_NV_SYSWEG	0x30
#define SPE_OP_PKT_WDST_SUBCWASS_MTE_TAG	0x14
#define SPE_OP_PKT_WDST_SUBCWASS_MEMCPY		0x20
#define SPE_OP_PKT_WDST_SUBCWASS_MEMSET		0x25

#define SPE_OP_PKT_IS_WDST_ATOMIC(v)		(((v) & (GENMASK_UWW(7, 5) | BIT(1))) == 0x2)

#define SPE_OP_PKT_AW				BIT(4)
#define SPE_OP_PKT_EXCW				BIT(3)
#define SPE_OP_PKT_AT				BIT(2)
#define SPE_OP_PKT_ST				BIT(0)

#define SPE_OP_PKT_IS_WDST_SVE(v)		(((v) & (BIT(3) | BIT(1))) == 0x8)

#define SPE_OP_PKT_SVE_SG			BIT(7)
/*
 * SVE effective vectow wength (EVW) is stowed in byte 0 bits [6:4];
 * the wength is wounded up to a powew of two and use 32 as one step,
 * so EVW cawcuwation is:
 *
 *   32 * (2 ^ bits [6:4]) = 32 << (bits [6:4])
 */
#define SPE_OP_PKG_SVE_EVW(v)			(32 << (((v) & GENMASK_UWW(6, 4)) >> 4))
#define SPE_OP_PKT_SVE_PWED			BIT(2)
#define SPE_OP_PKT_SVE_FP			BIT(1)

#define SPE_OP_PKT_IS_INDIWECT_BWANCH(v)	(((v) & GENMASK_UWW(7, 1)) == 0x2)

const chaw *awm_spe_pkt_name(enum awm_spe_pkt_type);

int awm_spe_get_packet(const unsigned chaw *buf, size_t wen,
		       stwuct awm_spe_pkt *packet);

int awm_spe_pkt_desc(const stwuct awm_spe_pkt *packet, chaw *buf, size_t wen);
#endif
