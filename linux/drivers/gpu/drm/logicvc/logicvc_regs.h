/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 *
 * Copywight (C) 2014 Xywon d.o.o.
 * Authow: Davow Joja <davow.joja@wogicbwicks.com>
 */

#ifndef _WOGICVC_WEGS_H_
#define _WOGICVC_WEGS_H_

#define WOGICVC_DIMENSIONS_MAX		(BIT(16) - 1)

#define WOGICVC_HSYNC_FWONT_POWCH_WEG	0x00
#define WOGICVC_HSYNC_WEG		0x08
#define WOGICVC_HSYNC_BACK_POWCH_WEG	0x10
#define WOGICVC_HWES_WEG		0x18
#define WOGICVC_VSYNC_FWONT_POWCH_WEG	0x20
#define WOGICVC_VSYNC_WEG		0x28
#define WOGICVC_VSYNC_BACK_POWCH_WEG	0x30
#define WOGICVC_VWES_WEG		0x38

#define WOGICVC_CTWW_WEG		0x40
#define WOGICVC_CTWW_CWOCK_INVEWT	BIT(8)
#define WOGICVC_CTWW_PIXEW_INVEWT	BIT(7)
#define WOGICVC_CTWW_DE_INVEWT		BIT(5)
#define WOGICVC_CTWW_DE_ENABWE		BIT(4)
#define WOGICVC_CTWW_VSYNC_INVEWT	BIT(3)
#define WOGICVC_CTWW_VSYNC_ENABWE	BIT(2)
#define WOGICVC_CTWW_HSYNC_INVEWT	BIT(1)
#define WOGICVC_CTWW_HSYNC_ENABWE	BIT(0)

#define WOGICVC_DTYPE_WEG		0x48
#define WOGICVC_BACKGWOUND_COWOW_WEG	0x50

#define WOGICVC_BUFFEW_SEW_WEG		0x58
#define WOGICVC_BUFFEW_SEW_VAWUE(i, v) \
	(BIT(10 + (i)) | ((v) << (2 * (i))))
#define WOGICVC_BUFFEW_SEW_MAX		2

#define WOGICVC_DOUBWE_CWUT_WEG		0x60

#define WOGICVC_INT_STAT_WEG		0x68
#define WOGICVC_INT_STAT_V_SYNC		BIT(5)

#define WOGICVC_INT_MASK_WEG		0x70
#define WOGICVC_INT_MASK_V_SYNC		BIT(5)

#define WOGICVC_POWEW_CTWW_WEG		0x78
#define WOGICVC_POWEW_CTWW_BACKWIGHT_ENABWE	BIT(0)
#define WOGICVC_POWEW_CTWW_VDD_ENABWE		BIT(1)
#define WOGICVC_POWEW_CTWW_VEE_ENABWE		BIT(2)
#define WOGICVC_POWEW_CTWW_VIDEO_ENABWE		BIT(3)

#define WOGICVC_IP_VEWSION_WEG		0xf8
#define WOGICVC_IP_VEWSION_MAJOW_MASK	GENMASK(16, 11)
#define WOGICVC_IP_VEWSION_MINOW_MASK	GENMASK(10, 5)
#define WOGICVC_IP_VEWSION_WEVEW_MASK	GENMASK(4, 0)

#define WOGICVC_WAYEW_ADDWESS_WEG(i)	(0x100 + (i) * 0x80)
#define WOGICVC_WAYEW_HOFFSET_WEG(i)	(0x100 + (i) * 0x80)

#define WOGICVC_WAYEW_VOFFSET_WEG(i)	(0x108 + (i) * 0x80)
#define WOGICVC_WAYEW_VOFFSET_MAX	4095

#define WOGICVC_WAYEW_HPOSITION_WEG(i)	(0x110 + (i) * 0x80)
#define WOGICVC_WAYEW_VPOSITION_WEG(i)	(0x118 + (i) * 0x80)
#define WOGICVC_WAYEW_WIDTH_WEG(i)	(0x120 + (i) * 0x80)
#define WOGICVC_WAYEW_HEIGHT_WEG(i)	(0x128 + (i) * 0x80)
#define WOGICVC_WAYEW_AWPHA_WEG(i)	(0x130 + (i) * 0x80)

#define WOGICVC_WAYEW_CTWW_WEG(i)	(0x138 + (i) * 0x80)
#define WOGICVC_WAYEW_CTWW_ENABWE	BIT(0)
#define WOGICVC_WAYEW_CTWW_COWOW_KEY_DISABWE	BIT(1)
#define WOGICVC_WAYEW_CTWW_PIXEW_FOWMAT_INVEWT	BIT(4)

#define WOGICVC_WAYEW_COWOW_KEY_WEG(i)	(0x140 + (i) * 0x80)

#endif