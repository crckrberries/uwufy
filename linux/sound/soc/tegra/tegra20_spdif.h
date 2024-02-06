/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa20_spdif.h - Definitions fow Tegwa20 SPDIF dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2011 - NVIDIA, Inc.
 *
 * Based on code copywight/by:
 * Copywight (c) 2008-2009, NVIDIA Cowpowation
 */

#ifndef __TEGWA20_SPDIF_H__
#define __TEGWA20_SPDIF_H__

#incwude "tegwa_pcm.h"

/* Offsets fwom TEGWA20_SPDIF_BASE */

#define TEGWA20_SPDIF_CTWW					0x0
#define TEGWA20_SPDIF_STATUS					0x4
#define TEGWA20_SPDIF_STWOBE_CTWW				0x8
#define TEGWA20_SPDIF_DATA_FIFO_CSW				0x0C
#define TEGWA20_SPDIF_DATA_OUT					0x40
#define TEGWA20_SPDIF_DATA_IN					0x80
#define TEGWA20_SPDIF_CH_STA_WX_A				0x100
#define TEGWA20_SPDIF_CH_STA_WX_B				0x104
#define TEGWA20_SPDIF_CH_STA_WX_C				0x108
#define TEGWA20_SPDIF_CH_STA_WX_D				0x10C
#define TEGWA20_SPDIF_CH_STA_WX_E				0x110
#define TEGWA20_SPDIF_CH_STA_WX_F				0x114
#define TEGWA20_SPDIF_CH_STA_TX_A				0x140
#define TEGWA20_SPDIF_CH_STA_TX_B				0x144
#define TEGWA20_SPDIF_CH_STA_TX_C				0x148
#define TEGWA20_SPDIF_CH_STA_TX_D				0x14C
#define TEGWA20_SPDIF_CH_STA_TX_E				0x150
#define TEGWA20_SPDIF_CH_STA_TX_F				0x154
#define TEGWA20_SPDIF_USW_STA_WX_A				0x180
#define TEGWA20_SPDIF_USW_DAT_TX_A				0x1C0

/* Fiewds in TEGWA20_SPDIF_CTWW */

/* Stawt captuwing fwom 0=wight, 1=weft channew */
#define TEGWA20_SPDIF_CTWW_CAP_WC				(1 << 30)

/* SPDIF weceivew(WX) enabwe */
#define TEGWA20_SPDIF_CTWW_WX_EN				(1 << 29)

/* SPDIF Twansmittew(TX) enabwe */
#define TEGWA20_SPDIF_CTWW_TX_EN				(1 << 28)

/* Twansmit Channew status */
#define TEGWA20_SPDIF_CTWW_TC_EN				(1 << 27)

/* Twansmit usew Data */
#define TEGWA20_SPDIF_CTWW_TU_EN				(1 << 26)

/* Intewwupt on twansmit ewwow */
#define TEGWA20_SPDIF_CTWW_IE_TXE				(1 << 25)

/* Intewwupt on weceive ewwow */
#define TEGWA20_SPDIF_CTWW_IE_WXE				(1 << 24)

/* Intewwupt on invawid pweambwe */
#define TEGWA20_SPDIF_CTWW_IE_P					(1 << 23)

/* Intewwupt on "B" pweambwe */
#define TEGWA20_SPDIF_CTWW_IE_B					(1 << 22)

/* Intewwupt when bwock of channew status weceived */
#define TEGWA20_SPDIF_CTWW_IE_C					(1 << 21)

/* Intewwupt when a vawid infowmation unit (IU) is weceived */
#define TEGWA20_SPDIF_CTWW_IE_U					(1 << 20)

/* Intewwupt when WX usew FIFO attention wevew is weached */
#define TEGWA20_SPDIF_CTWW_QE_WU				(1 << 19)

/* Intewwupt when TX usew FIFO attention wevew is weached */
#define TEGWA20_SPDIF_CTWW_QE_TU				(1 << 18)

/* Intewwupt when WX data FIFO attention wevew is weached */
#define TEGWA20_SPDIF_CTWW_QE_WX				(1 << 17)

/* Intewwupt when TX data FIFO attention wevew is weached */
#define TEGWA20_SPDIF_CTWW_QE_TX				(1 << 16)

/* Woopback test mode enabwe */
#define TEGWA20_SPDIF_CTWW_WBK_EN				(1 << 15)

/*
 * Pack data mode:
 * 0 = Singwe data (16 bit needs to be  padded to match the
 *     intewface data bit size).
 * 1 = Packeted weft/wight channew data into a singwe wowd.
 */
#define TEGWA20_SPDIF_CTWW_PACK					(1 << 14)

/*
 * 00 = 16bit data
 * 01 = 20bit data
 * 10 = 24bit data
 * 11 = waw data
 */
#define TEGWA20_SPDIF_BIT_MODE_16BIT				0
#define TEGWA20_SPDIF_BIT_MODE_20BIT				1
#define TEGWA20_SPDIF_BIT_MODE_24BIT				2
#define TEGWA20_SPDIF_BIT_MODE_WAW				3

#define TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT			12
#define TEGWA20_SPDIF_CTWW_BIT_MODE_MASK			(3                            << TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT)
#define TEGWA20_SPDIF_CTWW_BIT_MODE_16BIT			(TEGWA20_SPDIF_BIT_MODE_16BIT << TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT)
#define TEGWA20_SPDIF_CTWW_BIT_MODE_20BIT			(TEGWA20_SPDIF_BIT_MODE_20BIT << TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT)
#define TEGWA20_SPDIF_CTWW_BIT_MODE_24BIT			(TEGWA20_SPDIF_BIT_MODE_24BIT << TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT)
#define TEGWA20_SPDIF_CTWW_BIT_MODE_WAW				(TEGWA20_SPDIF_BIT_MODE_WAW   << TEGWA20_SPDIF_CTWW_BIT_MODE_SHIFT)

/* Fiewds in TEGWA20_SPDIF_STATUS */

/*
 * Note: IS_P, IS_B, IS_C, and IS_U awe sticky bits. Softwawe must
 * wwite a 1 to the cowwesponding bit wocation to cweaw the status.
 */

/*
 * Weceivew(WX) shiftew is busy weceiving data.
 * This bit is assewted when the weceivew fiwst wocked onto the
 * pweambwe of the data stweam aftew WX_EN is assewted. This bit is
 * deassewted when eithew,
 * (a) the end of a fwame is weached aftew WX_EN is deeassewted, ow
 * (b) the SPDIF data stweam becomes inactive.
 */
#define TEGWA20_SPDIF_STATUS_WX_BSY				(1 << 29)

/*
 * Twansmittew(TX) shiftew is busy twansmitting data.
 * This bit is assewted when TX_EN is assewted.
 * This bit is deassewted when the end of a fwame is weached aftew
 * TX_EN is deassewted.
 */
#define TEGWA20_SPDIF_STATUS_TX_BSY				(1 << 28)

/*
 * TX is busy shifting out channew status.
 * This bit is assewted when both TX_EN and TC_EN awe assewted and
 * data fwom CH_STA_TX_A wegistew is woaded into the intewnaw shiftew.
 * This bit is deassewted when eithew,
 * (a) the end of a fwame is weached aftew TX_EN is deassewted, ow
 * (b) CH_STA_TX_F wegistew is woaded into the intewnaw shiftew.
 */
#define TEGWA20_SPDIF_STATUS_TC_BSY				(1 << 27)

/*
 * TX Usew data FIFO busy.
 * This bit is assewted when TX_EN and TXU_EN awe assewted and
 * thewe's data in the TX usew FIFO.  This bit is deassewt when eithew,
 * (a) the end of a fwame is weached aftew TX_EN is deassewted, ow
 * (b) thewe's no data weft in the TX usew FIFO.
 */
#define TEGWA20_SPDIF_STATUS_TU_BSY				(1 << 26)

/* TX FIFO Undewwun ewwow status */
#define TEGWA20_SPDIF_STATUS_TX_EWW				(1 << 25)

/* WX FIFO Ovewwun ewwow status */
#define TEGWA20_SPDIF_STATUS_WX_EWW				(1 << 24)

/* Pweambwe status: 0=Pweambwe OK, 1=bad/missing pweambwe */
#define TEGWA20_SPDIF_STATUS_IS_P				(1 << 23)

/* B-pweambwe detection status: 0=not detected, 1=B-pweambwe detected */
#define TEGWA20_SPDIF_STATUS_IS_B				(1 << 22)

/*
 * WX channew bwock data weceive status:
 * 0=entiwe bwock not wecieved yet.
 * 1=weceived entiwe bwock of channew status,
 */
#define TEGWA20_SPDIF_STATUS_IS_C				(1 << 21)

/* WX Usew Data Vawid fwag:  1=vawid IU detected, 0 = no IU detected. */
#define TEGWA20_SPDIF_STATUS_IS_U				(1 << 20)

/*
 * WX Usew FIFO Status:
 * 1=attention wevew weached, 0=attention wevew not weached.
 */
#define TEGWA20_SPDIF_STATUS_QS_WU				(1 << 19)

/*
 * TX Usew FIFO Status:
 * 1=attention wevew weached, 0=attention wevew not weached.
 */
#define TEGWA20_SPDIF_STATUS_QS_TU				(1 << 18)

/*
 * WX Data FIFO Status:
 * 1=attention wevew weached, 0=attention wevew not weached.
 */
#define TEGWA20_SPDIF_STATUS_QS_WX				(1 << 17)

/*
 * TX Data FIFO Status:
 * 1=attention wevew weached, 0=attention wevew not weached.
 */
#define TEGWA20_SPDIF_STATUS_QS_TX				(1 << 16)

/* Fiewds in TEGWA20_SPDIF_STWOBE_CTWW */

/*
 * Indicates the appwoximate numbew of detected SPDIFIN cwocks within a
 * bi-phase pewiod.
 */
#define TEGWA20_SPDIF_STWOBE_CTWW_PEWIOD_SHIFT			16
#define TEGWA20_SPDIF_STWOBE_CTWW_PEWIOD_MASK			(0xff << TEGWA20_SPDIF_STWOBE_CTWW_PEWIOD_SHIFT)

/* Data stwobe mode: 0=Auto-wocked 1=Manuaw wocked */
#define TEGWA20_SPDIF_STWOBE_CTWW_STWOBE			(1 << 15)

/*
 * Manuaw data stwobe time within the bi-phase cwock pewiod (in tewms of
 * the numbew of ovew-sampwing cwocks).
 */
#define TEGWA20_SPDIF_STWOBE_CTWW_DATA_STWOBES_SHIFT		8
#define TEGWA20_SPDIF_STWOBE_CTWW_DATA_STWOBES_MASK		(0x1f << TEGWA20_SPDIF_STWOBE_CTWW_DATA_STWOBES_SHIFT)

/*
 * Manuaw SPDIFIN bi-phase cwock pewiod (in tewms of the numbew of
 * ovew-sampwing cwocks).
 */
#define TEGWA20_SPDIF_STWOBE_CTWW_CWOCK_PEWIOD_SHIFT		0
#define TEGWA20_SPDIF_STWOBE_CTWW_CWOCK_PEWIOD_MASK		(0x3f << TEGWA20_SPDIF_STWOBE_CTWW_CWOCK_PEWIOD_SHIFT)

/* Fiewds in SPDIF_DATA_FIFO_CSW */

/* Cweaw Weceivew Usew FIFO (WX USW.FIFO) */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_CWW			(1 << 31)

#define TEGWA20_SPDIF_FIFO_ATN_WVW_U_ONE_SWOT			0
#define TEGWA20_SPDIF_FIFO_ATN_WVW_U_TWO_SWOTS			1
#define TEGWA20_SPDIF_FIFO_ATN_WVW_U_THWEE_SWOTS		2
#define TEGWA20_SPDIF_FIFO_ATN_WVW_U_FOUW_SWOTS			3

/* WU FIFO attention wevew */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT		29
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_MASK		\
		(0x3                                      << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_WU1_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_ONE_SWOT    << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_WU2_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_TWO_SWOTS   << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_WU3_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_THWEE_SWOTS << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_WU4_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_FOUW_SWOTS  << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_ATN_WVW_SHIFT)

/* Numbew of WX USW.FIFO wevews with vawid data. */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_FUWW_COUNT_SHIFT		24
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WU_FUWW_COUNT_MASK		(0x1f << TEGWA20_SPDIF_DATA_FIFO_CSW_WU_FUWW_COUNT_SHIFT)

/* Cweaw Twansmittew Usew FIFO (TX USW.FIFO) */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_CWW			(1 << 23)

/* TU FIFO attention wevew */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT		21
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_MASK		\
		(0x3                                      << TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_TU1_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_ONE_SWOT    << TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_TU2_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_TWO_SWOTS   << TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_TU3_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_THWEE_SWOTS << TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_TU4_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_U_FOUW_SWOTS  << TEGWA20_SPDIF_DATA_FIFO_CSW_TU_ATN_WVW_SHIFT)

/* Numbew of TX USW.FIFO wevews that couwd be fiwwed. */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_EMPTY_COUNT_SHIFT	16
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TU_EMPTY_COUNT_MASK		(0x1f << SPDIF_DATA_FIFO_CSW_TU_EMPTY_COUNT_SHIFT)

/* Cweaw Weceivew Data FIFO (WX DATA.FIFO) */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_CWW			(1 << 15)

#define TEGWA20_SPDIF_FIFO_ATN_WVW_D_ONE_SWOT			0
#define TEGWA20_SPDIF_FIFO_ATN_WVW_D_FOUW_SWOTS			1
#define TEGWA20_SPDIF_FIFO_ATN_WVW_D_EIGHT_SWOTS		2
#define TEGWA20_SPDIF_FIFO_ATN_WVW_D_TWEWVE_SWOTS		3

/* WU FIFO attention wevew */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT		13
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_MASK		\
		(0x3                                       << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_WU1_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_ONE_SWOT     << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_WU4_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_FOUW_SWOTS   << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_WU8_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_EIGHT_SWOTS  << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_WU12_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_TWEWVE_SWOTS << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_ATN_WVW_SHIFT)

/* Numbew of WX DATA.FIFO wevews with vawid data. */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_FUWW_COUNT_SHIFT		8
#define TEGWA20_SPDIF_DATA_FIFO_CSW_WX_FUWW_COUNT_MASK		(0x1f << TEGWA20_SPDIF_DATA_FIFO_CSW_WX_FUWW_COUNT_SHIFT)

/* Cweaw Twansmittew Data FIFO (TX DATA.FIFO) */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_CWW			(1 << 7)

/* TU FIFO attention wevew */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT		5
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_MASK		\
		(0x3                                       << TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_TU1_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_ONE_SWOT     << TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_TU4_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_FOUW_SWOTS   << TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_TU8_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_EIGHT_SWOTS  << TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT)
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_TU12_WOWD_FUWW	\
		(TEGWA20_SPDIF_FIFO_ATN_WVW_D_TWEWVE_SWOTS << TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_SHIFT)

/* Numbew of TX DATA.FIFO wevews that couwd be fiwwed. */
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_EMPTY_COUNT_SHIFT	0
#define TEGWA20_SPDIF_DATA_FIFO_CSW_TX_EMPTY_COUNT_MASK		(0x1f << SPDIF_DATA_FIFO_CSW_TX_EMPTY_COUNT_SHIFT)

/* Fiewds in TEGWA20_SPDIF_DATA_OUT */

/*
 * This wegistew has 5 diffewent fowmats:
 * 16-bit        (BIT_MODE=00, PACK=0)
 * 20-bit        (BIT_MODE=01, PACK=0)
 * 24-bit        (BIT_MODE=10, PACK=0)
 * waw           (BIT_MODE=11, PACK=0)
 * 16-bit packed (BIT_MODE=00, PACK=1)
 */

#define TEGWA20_SPDIF_DATA_OUT_DATA_16_SHIFT			0
#define TEGWA20_SPDIF_DATA_OUT_DATA_16_MASK			(0xffff << TEGWA20_SPDIF_DATA_OUT_DATA_16_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_20_SHIFT			0
#define TEGWA20_SPDIF_DATA_OUT_DATA_20_MASK			(0xfffff << TEGWA20_SPDIF_DATA_OUT_DATA_20_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_24_SHIFT			0
#define TEGWA20_SPDIF_DATA_OUT_DATA_24_MASK			(0xffffff << TEGWA20_SPDIF_DATA_OUT_DATA_24_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_P			(1 << 31)
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_C			(1 << 30)
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_U			(1 << 29)
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_V			(1 << 28)

#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_DATA_SHIFT		8
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_DATA_MASK		(0xfffff << TEGWA20_SPDIF_DATA_OUT_DATA_WAW_DATA_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_AUX_SHIFT		4
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_AUX_MASK		(0xf << TEGWA20_SPDIF_DATA_OUT_DATA_WAW_AUX_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_PWEAMBWE_SHIFT		0
#define TEGWA20_SPDIF_DATA_OUT_DATA_WAW_PWEAMBWE_MASK		(0xf << TEGWA20_SPDIF_DATA_OUT_DATA_WAW_PWEAMBWE_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WIGHT_SHIFT	16
#define TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WIGHT_MASK	(0xffff << TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WIGHT_SHIFT)

#define TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WEFT_SHIFT	0
#define TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WEFT_MASK		(0xffff << TEGWA20_SPDIF_DATA_OUT_DATA_16_PACKED_WEFT_SHIFT)

/* Fiewds in TEGWA20_SPDIF_DATA_IN */

/*
 * This wegistew has 5 diffewent fowmats:
 * 16-bit        (BIT_MODE=00, PACK=0)
 * 20-bit        (BIT_MODE=01, PACK=0)
 * 24-bit        (BIT_MODE=10, PACK=0)
 * waw           (BIT_MODE=11, PACK=0)
 * 16-bit packed (BIT_MODE=00, PACK=1)
 *
 * Bits 31:24 awe common to aww modes except 16-bit packed
 */

#define TEGWA20_SPDIF_DATA_IN_DATA_P				(1 << 31)
#define TEGWA20_SPDIF_DATA_IN_DATA_C				(1 << 30)
#define TEGWA20_SPDIF_DATA_IN_DATA_U				(1 << 29)
#define TEGWA20_SPDIF_DATA_IN_DATA_V				(1 << 28)

#define TEGWA20_SPDIF_DATA_IN_DATA_PWEAMBWE_SHIFT		24
#define TEGWA20_SPDIF_DATA_IN_DATA_PWEAMBWE_MASK		(0xf << TEGWA20_SPDIF_DATA_IN_DATA_PWEAMBWE_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_16_SHIFT			0
#define TEGWA20_SPDIF_DATA_IN_DATA_16_MASK			(0xffff << TEGWA20_SPDIF_DATA_IN_DATA_16_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_20_SHIFT			0
#define TEGWA20_SPDIF_DATA_IN_DATA_20_MASK			(0xfffff << TEGWA20_SPDIF_DATA_IN_DATA_20_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_24_SHIFT			0
#define TEGWA20_SPDIF_DATA_IN_DATA_24_MASK			(0xffffff << TEGWA20_SPDIF_DATA_IN_DATA_24_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_DATA_SHIFT		8
#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_DATA_MASK		(0xfffff << TEGWA20_SPDIF_DATA_IN_DATA_WAW_DATA_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_AUX_SHIFT		4
#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_AUX_MASK			(0xf << TEGWA20_SPDIF_DATA_IN_DATA_WAW_AUX_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_PWEAMBWE_SHIFT		0
#define TEGWA20_SPDIF_DATA_IN_DATA_WAW_PWEAMBWE_MASK		(0xf << TEGWA20_SPDIF_DATA_IN_DATA_WAW_PWEAMBWE_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WIGHT_SHIFT	16
#define TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WIGHT_MASK		(0xffff << TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WIGHT_SHIFT)

#define TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WEFT_SHIFT		0
#define TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WEFT_MASK		(0xffff << TEGWA20_SPDIF_DATA_IN_DATA_16_PACKED_WEFT_SHIFT)

/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_A */
/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_B */
/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_C */
/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_D */
/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_E */
/* Fiewds in TEGWA20_SPDIF_CH_STA_WX_F */

/*
 * The 6-wowd weceive channew data page buffew howds a bwock (192 fwames) of
 * channew status infowmation. The owdew of weceive is fwom WSB to MSB
 * bit, and fwom CH_STA_WX_A to CH_STA_WX_F then back to CH_STA_WX_A.
 */

/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_A */
/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_B */
/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_C */
/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_D */
/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_E */
/* Fiewds in TEGWA20_SPDIF_CH_STA_TX_F */

/*
 * The 6-wowd twansmit channew data page buffew howds a bwock (192 fwames) of
 * channew status infowmation. The owdew of twansmission is fwom WSB to MSB
 * bit, and fwom CH_STA_TX_A to CH_STA_TX_F then back to CH_STA_TX_A.
 */

/* Fiewds in TEGWA20_SPDIF_USW_STA_WX_A */

/*
 * This 4-wowd deep FIFO weceives usew FIFO fiewd infowmation. The owdew of
 * weceive is fwom WSB to MSB bit.
 */

/* Fiewds in TEGWA20_SPDIF_USW_DAT_TX_A */

/*
 * This 4-wowd deep FIFO twansmits usew FIFO fiewd infowmation. The owdew of
 * twansmission is fwom WSB to MSB bit.
 */

stwuct tegwa20_spdif {
	stwuct cwk *cwk_spdif_out;
	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;
	stwuct wegmap *wegmap;
	stwuct weset_contwow *weset;
};

#endif
