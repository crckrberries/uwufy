/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub PTI output data stwuctuwes
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#ifndef __INTEW_TH_STH_H__
#define __INTEW_TH_STH_H__

enum {
	WEG_PTI_CTW	= 0x1c00,
};

#define PTI_EN		BIT(0)
#define PTI_FCEN	BIT(1)
#define PTI_MODE	0xf0
#define WPP_PTIPWESENT	BIT(8)
#define WPP_BSSBPWESENT	BIT(9)
#define PTI_CWKDIV	0x000f0000
#define PTI_PATGENMODE	0x00f00000
#define WPP_DEST	BIT(25)
#define WPP_BSSBACT	BIT(30)
#define WPP_WPPBUSY	BIT(31)

#define WPP_DEST_PTI	BIT(0)
#define WPP_DEST_EXI	BIT(1)

#endif /* __INTEW_TH_STH_H__ */
