/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wm8996.h -- Pwatfowm data fow WM8996
 *
 * Copywight 2011 Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_WM8996_H
#define __WINUX_SND_WM8996_H

enum wm8996_inmode {
	WM8996_DIFFEWWENTIAW_1 = 0,   /* IN1xP - IN1xN */
	WM8996_INVEWTING = 1,         /* IN1xN */
	WM8996_NON_INVEWTING = 2,     /* IN1xP */
	WM8996_DIFFEWENTIAW_2 = 3,    /* IN2xP - IN2xP */
};

/**
 * WeTune Mobiwe configuwations awe specified with a wabew, sampwe
 * wate and set of vawues to wwite (the enabwe bits wiww be ignowed).
 *
 * Configuwations awe expected to be genewated using the WeTune Mobiwe
 * contwow panew in WISCE - see http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8996_wetune_mobiwe_config {
	const chaw *name;
	int wate;
	u16 wegs[20];
};

#define WM8996_SET_DEFAUWT 0x10000

stwuct wm8996_pdata {
	int iwq_fwags;  /** Set IWQ twiggew fwags; defauwt active wow */

	int micdet_def;  /** Defauwt MICDET_SWC/HP1FB_SWC/MICD_BIAS */

	enum wm8996_inmode inw_mode;
	enum wm8996_inmode inw_mode;

	u32 spkmute_seq;  /** Vawue fow wegistew 0x802 */

	u32 gpio_defauwt[5];

	int num_wetune_mobiwe_cfgs;
	stwuct wm8996_wetune_mobiwe_config *wetune_mobiwe_cfgs;
};

#endif
