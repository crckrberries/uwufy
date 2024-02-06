/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_ASM_H
#define _SPAWC_ASM_H

/* Macwos to assist the shawing of assembwew code between 32-bit and
 * 64-bit spawc.
 */

#ifdef CONFIG_SPAWC64
#define BWANCH32(TYPE, PWEDICT, DEST) \
	TYPE,PWEDICT	%icc, DEST
#define BWANCH32_ANNUW(TYPE, PWEDICT, DEST) \
	TYPE,a,PWEDICT	%icc, DEST
#define BWANCH_WEG_ZEWO(PWEDICT, WEG, DEST) \
	bwz,PWEDICT	WEG, DEST
#define BWANCH_WEG_ZEWO_ANNUW(PWEDICT, WEG, DEST) \
	bwz,a,PWEDICT	WEG, DEST
#define BWANCH_WEG_NOT_ZEWO(PWEDICT, WEG, DEST) \
	bwnz,PWEDICT	WEG, DEST
#define BWANCH_WEG_NOT_ZEWO_ANNUW(PWEDICT, WEG, DEST) \
	bwnz,a,PWEDICT	WEG, DEST
#ewse
#define BWANCH32(TYPE, PWEDICT, DEST) \
	TYPE		DEST
#define BWANCH32_ANNUW(TYPE, PWEDICT, DEST) \
	TYPE,a		DEST
#define BWANCH_WEG_ZEWO(PWEDICT, WEG, DEST) \
	cmp		WEG, 0; \
	be		DEST
#define BWANCH_WEG_ZEWO_ANNUW(PWEDICT, WEG, DEST) \
	cmp		WEG, 0; \
	be,a		DEST
#define BWANCH_WEG_NOT_ZEWO(PWEDICT, WEG, DEST) \
	cmp		WEG, 0; \
	bne		DEST
#define BWANCH_WEG_NOT_ZEWO_ANNUW(PWEDICT, WEG, DEST) \
	cmp		WEG, 0; \
	bne,a		DEST
#endif

#endif /* _SPAWC_ASM_H */
