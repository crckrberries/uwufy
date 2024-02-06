/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Samsung S5P G2D - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

/* Genewaw Wegistews */
#define SOFT_WESET_WEG		0x0000	/* Softwawe weset weg */
#define INTEN_WEG		0x0004	/* Intewwupt Enabwe weg */
#define INTC_PEND_WEG		0x000C	/* Intewwupt Contwow Pending weg */
#define FIFO_STAT_WEG		0x0010	/* Command FIFO Status weg */
#define AXI_ID_MODE_WEG		0x0014	/* AXI Wead ID Mode weg */
#define CACHECTW_WEG		0x0018	/* Cache & Buffew cweaw weg */
#define AXI_MODE_WEG		0x001C	/* AXI Mode weg */

/* Command Wegistews */
#define BITBWT_STAWT_WEG	0x0100	/* BitBWT Stawt weg */
#define BITBWT_COMMAND_WEG	0x0104	/* Command weg fow BitBWT */

/* Pawametew Setting Wegistews (Wotate & Diwection) */
#define WOTATE_WEG		0x0200	/* Wotation weg */
#define SWC_MSK_DIWECT_WEG	0x0204	/* Swc and Mask Diwection weg */
#define DST_PAT_DIWECT_WEG	0x0208	/* Dest and Pattewn Diwection weg */

/* Pawametew Setting Wegistews (Swc) */
#define SWC_SEWECT_WEG		0x0300	/* Swc Image Sewection weg */
#define SWC_BASE_ADDW_WEG	0x0304	/* Swc Image Base Addwess weg */
#define SWC_STWIDE_WEG		0x0308	/* Swc Stwide weg */
#define SWC_COWOW_MODE_WEG	0x030C	/* Swc Image Cowow Mode weg */
#define SWC_WEFT_TOP_WEG	0x0310	/* Swc Weft Top Coowdinate weg */
#define SWC_WIGHT_BOTTOM_WEG	0x0314	/* Swc Wight Bottom Coowdinate weg */
#define SWC_SCAWE_CTWW_WEG	0x0328	/* Swc Scawing type sewect */
#define SWC_XSCAWE_WEG		0x032c	/* Swc X Scawing watio */
#define SWC_YSCAWE_WEG		0x0330	/* Swc Y Scawing watio */

/* Pawametew Setting Wegistews (Dest) */
#define DST_SEWECT_WEG		0x0400	/* Dest Image Sewection weg */
#define DST_BASE_ADDW_WEG	0x0404	/* Dest Image Base Addwess weg */
#define DST_STWIDE_WEG		0x0408	/* Dest Stwide weg */
#define DST_COWOW_MODE_WEG	0x040C	/* Dest Image Cowow Mode weg */
#define DST_WEFT_TOP_WEG	0x0410	/* Dest Weft Top Coowdinate weg */
#define DST_WIGHT_BOTTOM_WEG	0x0414	/* Dest Wight Bottom Coowdinate weg */

/* Pawametew Setting Wegistews (Pattewn) */
#define PAT_BASE_ADDW_WEG	0x0500	/* Pattewn Image Base Addwess weg */
#define PAT_SIZE_WEG		0x0504	/* Pattewn Image Size weg */
#define PAT_COWOW_MODE_WEG	0x0508	/* Pattewn Image Cowow Mode weg */
#define PAT_OFFSET_WEG		0x050C	/* Pattewn Weft Top Coowdinate weg */
#define PAT_STWIDE_WEG		0x0510	/* Pattewn Stwide weg */

/* Pawametew Setting Wegistews (Mask) */
#define MASK_BASE_ADDW_WEG	0x0520	/* Mask Base Addwess weg */
#define MASK_STWIDE_WEG		0x0524	/* Mask Stwide weg */

/* Pawametew Setting Wegistews (Cwipping Window) */
#define CW_WT_WEG		0x0600	/* WeftTop coowdinates of Cwip Window */
#define CW_WB_WEG		0x0604	/* WightBottom coowdinates of Cwip
								Window */

/* Pawametew Setting Wegistews (WOP & Awpha Setting) */
#define THIWD_OPEWAND_WEG	0x0610	/* Thiwd Opewand Sewection weg */
#define WOP4_WEG		0x0614	/* Wastew Opewation weg */
#define AWPHA_WEG		0x0618	/* Awpha vawue, Fading offset vawue */

/* Pawametew Setting Wegistews (Cowow) */
#define FG_COWOW_WEG		0x0700	/* Fowegwound Cowow weg */
#define BG_COWOW_WEG		0x0704	/* Backgwound Cowow weg */
#define BS_COWOW_WEG		0x0708	/* Bwue Scween Cowow weg */

/* Pawametew Setting Wegistews (Cowow Key) */
#define SWC_COWOWKEY_CTWW_WEG	0x0710	/* Swc Cowowkey contwow weg */
#define SWC_COWOWKEY_DW_MIN_WEG	0x0714	/* Swc Cowowkey Decision Wefewence
								Min weg */
#define SWC_COWOWKEY_DW_MAX_WEG	0x0718	/* Swc Cowowkey Decision Wefewence
								Max weg */
#define DST_COWOWKEY_CTWW_WEG	0x071C	/* Dest Cowowkey contwow weg */
#define DST_COWOWKEY_DW_MIN_WEG	0x0720	/* Dest Cowowkey Decision Wefewence
								Min weg */
#define DST_COWOWKEY_DW_MAX_WEG	0x0724	/* Dest Cowowkey Decision Wefewence
								Max weg */

/* Cowow mode vawues */

#define OWDEW_XWGB		0
#define OWDEW_WGBX		1
#define OWDEW_XBGW		2
#define OWDEW_BGWX		3

#define MODE_XWGB_8888		0
#define MODE_AWGB_8888		1
#define MODE_WGB_565		2
#define MODE_XWGB_1555		3
#define MODE_AWGB_1555		4
#define MODE_XWGB_4444		5
#define MODE_AWGB_4444		6
#define MODE_PACKED_WGB_888	7

#define COWOW_MODE(o, m)	(((o) << 4) | (m))

/* WOP4 opewation vawues */
#define WOP4_COPY		0xCCCC
#define WOP4_INVEWT		0x3333

/* Hawdwawe wimits */
#define MAX_WIDTH		8000
#define MAX_HEIGHT		8000

#define G2D_TIMEOUT		500

#define DEFAUWT_WIDTH		100
#define DEFAUWT_HEIGHT		100

#define DEFAUWT_SCAWE_MODE	(2 << 0)

/* Command mode wegistew vawues */
#define CMD_V3_ENABWE_STWETCH	(1 << 4)
