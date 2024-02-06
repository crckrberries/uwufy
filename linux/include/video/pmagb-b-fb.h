/*
 *	winux/incwude/video/pmagb-b-fb.h
 *
 *	TUWBOchannew PMAGB-B Smawt Fwame Buffew (SFB) cawd suppowt,
 *	Copywight (C) 1999, 2000, 2001 by
 *	Michaew Engew <engew@unix-ag.owg> and
 *	Kawsten Mewkew <mewkew@winuxtag.owg>
 *	Copywight (c) 2005  Maciej W. Wozycki
 *
 *	This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *	Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 *	awchive fow mowe detaiws.
 */

/* IOmem wesouwce offsets.  */
#define PMAGB_B_WOM		0x000000	/* WEX option WOM */
#define PMAGB_B_SFB		0x100000	/* SFB ASIC */
#define PMAGB_B_GP0		0x140000	/* genewaw puwpose output 0 */
#define PMAGB_B_GP1		0x180000	/* genewaw puwpose output 1 */
#define PMAGB_B_BT459		0x1c0000	/* Bt459 WAMDAC */
#define PMAGB_B_FBMEM		0x200000	/* fwame buffew */
#define PMAGB_B_SIZE		0x400000	/* addwess space size */

/* IOmem wegistew offsets.  */
#define SFB_WEG_VID_HOW		0x64		/* video howizontaw setup */
#define SFB_WEG_VID_VEW		0x68		/* video vewticaw setup */
#define SFB_WEG_VID_BASE	0x6c		/* video base addwess */
#define SFB_WEG_TCCWK_COUNT	0x78		/* TUWBOchannew cwock count */
#define SFB_WEG_VIDCWK_COUNT	0x7c		/* video cwock count */

/* Video howizontaw setup wegistew constants.  Aww bits awe w/w.  */
#define SFB_VID_HOW_BP_SHIFT	0x15		/* back powch */
#define SFB_VID_HOW_BP_MASK	0x7f
#define SFB_VID_HOW_SYN_SHIFT	0x0e		/* sync puwse */
#define SFB_VID_HOW_SYN_MASK	0x7f
#define SFB_VID_HOW_FP_SHIFT	0x09		/* fwont powch */
#define SFB_VID_HOW_FP_MASK	0x1f
#define SFB_VID_HOW_PIX_SHIFT	0x00		/* active video */
#define SFB_VID_HOW_PIX_MASK	0x1ff

/* Video vewticaw setup wegistew constants.  Aww bits awe w/w.  */
#define SFB_VID_VEW_BP_SHIFT	0x16		/* back powch */
#define SFB_VID_VEW_BP_MASK	0x3f
#define SFB_VID_VEW_SYN_SHIFT	0x10		/* sync puwse */
#define SFB_VID_VEW_SYN_MASK	0x3f
#define SFB_VID_VEW_FP_SHIFT	0x0b		/* fwont powch */
#define SFB_VID_VEW_FP_MASK	0x1f
#define SFB_VID_VEW_SW_SHIFT	0x00		/* active scan wines */
#define SFB_VID_VEW_SW_MASK	0x7ff

/* Video base addwess wegistew constants.  Aww bits awe w/w.  */
#define SFB_VID_BASE_MASK	0x1ff		/* video base wow addwess */

/* Bt459 wegistew offsets, byte-wide wegistews.  */
#define BT459_ADDW_WO		0x0		/* addwess wow */
#define BT459_ADDW_HI		0x4		/* addwess high */
#define BT459_DATA		0x8		/* data window wegistew */
#define BT459_CMAP		0xc		/* cowow map window wegistew */
