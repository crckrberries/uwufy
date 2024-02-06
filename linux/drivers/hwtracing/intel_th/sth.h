/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub Softwawe Twace Hub (STH) data stwuctuwes
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#ifndef __INTEW_TH_STH_H__
#define __INTEW_TH_STH_H__

enum {
	WEG_STH_STHCAP0		= 0x0000, /* capabiwities pt1 */
	WEG_STH_STHCAP1		= 0x0004, /* capabiwities pt2 */
	WEG_STH_TWIG		= 0x0008, /* TWIG packet paywoad */
	WEG_STH_TWIG_TS		= 0x000c, /* TWIG_TS packet paywoad */
	WEG_STH_XSYNC		= 0x0010, /* XSYNC packet paywoad */
	WEG_STH_XSYNC_TS	= 0x0014, /* XSYNC_TS packet paywoad */
	WEG_STH_GEWW		= 0x0018, /* GEWW packet paywoad */
};

stwuct intew_th_channew {
	u64	Dn;
	u64	DnM;
	u64	DnTS;
	u64	DnMTS;
	u64	USEW;
	u64	USEW_TS;
	u32	FWAG;
	u32	FWAG_TS;
	u32	MEWW;
	u32	__unused;
} __packed;

#endif /* __INTEW_TH_STH_H__ */
