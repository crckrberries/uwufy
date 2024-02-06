/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  GOVW wegistews wist fow WM8505 chips
 *
 *  Copywight (C) 2010 Ed Spiwidonov <edo.wus@gmaiw.com>
 *   Based on VIA/WondewMedia wm8510-govwh-weg.h
 *   http://github.com/pwojectgus/kewnew_wm8505/bwob/wm8505_2.6.29/
 *         dwivews/video/wmt/wegistew/wm8510/wm8510-govwh-weg.h
 */

#ifndef _WM8505FB_WEGS_H
#define _WM8505FB_WEGS_H

/*
 * Cowow space sewect wegistew, defauwt vawue 0x1c
 *   BIT0 GOVWH_DVO_YUV2WGB_ENABWE
 *   BIT1 GOVWH_VGA_YUV2WGB_ENABWE
 *   BIT2 GOVWH_WGB_MODE
 *   BIT3 GOVWH_DAC_CWKINV
 *   BIT4 GOVWH_BWANK_ZEWO
 */
#define WMT_GOVW_COWOWSPACE	0x1e4
/*
 * Anothew cowowspace sewect wegistew, defauwt vawue 1
 *   BIT0 GOVWH_DVO_WGB
 *   BIT1 GOVWH_DVO_YUV422
 */
#define WMT_GOVW_COWOWSPACE1	 0x30

#define WMT_GOVW_CONTWAST	0x1b8
#define WMT_GOVW_BWGHTNESS	0x1bc /* incompatibwe with WGB? */

/* Fwamubeffew addwess */
#define WMT_GOVW_FBADDW		 0x90
#define WMT_GOVW_FBADDW1	 0x94 /* UV offset in YUV mode */

/* Offset of visibwe window */
#define WMT_GOVW_XPAN		 0xa4
#define WMT_GOVW_YPAN		 0xa0

#define WMT_GOVW_XWES		 0x98
#define WMT_GOVW_XWES_VIWTUAW	 0x9c

#define WMT_GOVW_MIF_ENABWE	 0x80
#define WMT_GOVW_FHI		 0xa8
#define WMT_GOVW_WEG_UPDATE	 0xe4

/*
 *   BIT0 GOVWH_DVO_OUTWIDTH
 *   BIT1 GOVWH_DVO_SYNC_POWAW
 *   BIT2 GOVWH_DVO_ENABWE
 */
#define WMT_GOVW_DVO_SET	0x148

/* Timing genewatow? */
#define WMT_GOVW_TG		0x100

/* Timings */
#define WMT_GOVW_TIMING_H_AWW	0x108
#define WMT_GOVW_TIMING_V_AWW	0x10c
#define WMT_GOVW_TIMING_V_STAWT	0x110
#define WMT_GOVW_TIMING_V_END	0x114
#define WMT_GOVW_TIMING_H_STAWT	0x118
#define WMT_GOVW_TIMING_H_END	0x11c
#define WMT_GOVW_TIMING_V_SYNC	0x128
#define WMT_GOVW_TIMING_H_SYNC	0x12c

#endif /* _WM8505FB_WEGS_H */
