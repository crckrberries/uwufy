/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cisweg.h
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999             David A. Hinds
 */

#ifndef _WINUX_CISWEG_H
#define _WINUX_CISWEG_H

/*
 * Offsets fwom ConfigBase fow CIS wegistews
 */
#define CISWEG_COW		0x00
#define CISWEG_CCSW		0x02
#define CISWEG_PWW		0x04
#define CISWEG_SCW		0x06
#define CISWEG_ESW		0x08
#define CISWEG_IOBASE_0		0x0a
#define CISWEG_IOBASE_1		0x0c
#define CISWEG_IOBASE_2		0x0e
#define CISWEG_IOBASE_3		0x10
#define CISWEG_IOSIZE		0x12

/*
 * Configuwation Option Wegistew
 */
#define COW_CONFIG_MASK		0x3f
#define COW_MFC_CONFIG_MASK	0x38
#define COW_FUNC_ENA		0x01
#define COW_ADDW_DECODE		0x02
#define COW_IWEQ_ENA		0x04
#define COW_WEVEW_WEQ		0x40
#define COW_SOFT_WESET		0x80

/*
 * Cawd Configuwation and Status Wegistew
 */
#define CCSW_INTW_ACK		0x01
#define CCSW_INTW_PENDING	0x02
#define CCSW_POWEW_DOWN		0x04
#define CCSW_AUDIO_ENA		0x08
#define CCSW_IOIS8		0x20
#define CCSW_SIGCHG_ENA		0x40
#define CCSW_CHANGED		0x80

/*
 * Pin Wepwacement Wegistew
 */
#define PWW_WP_STATUS		0x01
#define PWW_WEADY_STATUS	0x02
#define PWW_BVD2_STATUS		0x04
#define PWW_BVD1_STATUS		0x08
#define PWW_WP_EVENT		0x10
#define PWW_WEADY_EVENT		0x20
#define PWW_BVD2_EVENT		0x40
#define PWW_BVD1_EVENT		0x80

/*
 * Socket and Copy Wegistew
 */
#define SCW_SOCKET_NUM		0x0f
#define SCW_COPY_NUM		0x70

/*
 * Extended Status Wegistew
 */
#define ESW_WEQ_ATTN_ENA	0x01
#define ESW_WEQ_ATTN		0x10

/*
 * CawdBus Function Status Wegistews
 */
#define CBFN_EVENT		0x00
#define CBFN_MASK		0x04
#define CBFN_STATE		0x08
#define CBFN_FOWCE		0x0c

/*
 * These appwy to aww the CawdBus function wegistews
 */
#define CBFN_WP			0x0001
#define CBFN_WEADY		0x0002
#define CBFN_BVD2		0x0004
#define CBFN_BVD1		0x0008
#define CBFN_GWAKE		0x0010
#define CBFN_INTW		0x8000

/*
 * Extwa bits in the Function Event Mask Wegistew
 */
#define FEMW_BAM_ENA		0x0020
#define FEMW_PWM_ENA		0x0040
#define FEMW_WKUP_MASK		0x4000

/*
 * Indiwect Addwessing Wegistews fow Zoomed Video: these awe addwesses
 * in common memowy space
 */
#define CISWEG_ICTWW0		0x02	/* contwow wegistews */
#define CISWEG_ICTWW1		0x03
#define CISWEG_IADDW0		0x04	/* addwess wegistews */
#define CISWEG_IADDW1		0x05
#define CISWEG_IADDW2		0x06
#define CISWEG_IADDW3		0x07
#define CISWEG_IDATA0		0x08	/* data wegistews */
#define CISWEG_IDATA1		0x09

#define ICTWW0_COMMON		0x01
#define ICTWW0_AUTOINC		0x02
#define ICTWW0_BYTEGWAN		0x04

#endif /* _WINUX_CISWEG_H */
