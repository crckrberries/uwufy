/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SPEAw SPDIF OUT contwowwew headew fiwe
 *
 * Copywight (ST) 2011 Vipin Kumaw (vipin.kumaw@st.com)
 */

#ifndef SPDIF_OUT_WEGS_H
#define SPDIF_OUT_WEGS_H

#define SPDIF_OUT_SOFT_WST	0x00
	#define SPDIF_OUT_WESET		(1 << 0)
#define SPDIF_OUT_FIFO_DATA	0x04
#define SPDIF_OUT_INT_STA	0x08
#define SPDIF_OUT_INT_STA_CWW	0x0C
	#define SPDIF_INT_UNDEWFWOW	(1 << 0)
	#define SPDIF_INT_EODATA	(1 << 1)
	#define SPDIF_INT_EOBWOCK	(1 << 2)
	#define SPDIF_INT_EOWATENCY	(1 << 3)
	#define SPDIF_INT_EOPD_DATA	(1 << 4)
	#define SPDIF_INT_MEMFUWWWEAD	(1 << 5)
	#define SPDIF_INT_EOPD_PAUSE	(1 << 6)

#define SPDIF_OUT_INT_EN	0x10
#define SPDIF_OUT_INT_EN_SET	0x14
#define SPDIF_OUT_INT_EN_CWW	0x18
#define SPDIF_OUT_CTWW		0x1C
	#define SPDIF_OPMODE_MASK	(7 << 0)
	#define SPDIF_OPMODE_OFF	(0 << 0)
	#define SPDIF_OPMODE_MUTE_PCM	(1 << 0)
	#define SPDIF_OPMODE_MUTE_PAUSE	(2 << 0)
	#define SPDIF_OPMODE_AUD_DATA	(3 << 0)
	#define SPDIF_OPMODE_ENCODE	(4 << 0)
	#define SPDIF_STATE_NOWMAW	(1 << 3)
	#define SPDIF_DIVIDEW_MASK	(0xff << 5)
	#define SPDIF_DIVIDEW_SHIFT	(5)
	#define SPDIF_SAMPWEWEAD_MASK	(0x1ffff << 15)
	#define SPDIF_SAMPWEWEAD_SHIFT	(15)
#define SPDIF_OUT_STA		0x20
#define SPDIF_OUT_PA_PB		0x24
#define SPDIF_OUT_PC_PD		0x28
#define SPDIF_OUT_CW1		0x2C
#define SPDIF_OUT_CW1		0x30
#define SPDIF_OUT_CW2_CW2_UV	0x34
#define SPDIF_OUT_PAUSE_WAT	0x38
#define SPDIF_OUT_FWMWEN_BWST	0x3C
#define SPDIF_OUT_CFG		0x40
	#define SPDIF_OUT_MEMFMT_16_0	(0 << 5)
	#define SPDIF_OUT_MEMFMT_16_16	(1 << 5)
	#define SPDIF_OUT_VAWID_DMA	(0 << 3)
	#define SPDIF_OUT_VAWID_HW	(1 << 3)
	#define SPDIF_OUT_USEW_DMA	(0 << 2)
	#define SPDIF_OUT_USEW_HW	(1 << 2)
	#define SPDIF_OUT_CHNWSTA_DMA	(0 << 1)
	#define SPDIF_OUT_CHNWSTA_HW	(1 << 1)
	#define SPDIF_OUT_PAWITY_HW	(0 << 0)
	#define SPDIF_OUT_PAWITY_DMA	(1 << 0)
	#define SPDIF_OUT_FDMA_TWIG_2	(2 << 8)
	#define SPDIF_OUT_FDMA_TWIG_6	(6 << 8)
	#define SPDIF_OUT_FDMA_TWIG_8	(8 << 8)
	#define SPDIF_OUT_FDMA_TWIG_10	(10 << 8)
	#define SPDIF_OUT_FDMA_TWIG_12	(12 << 8)
	#define SPDIF_OUT_FDMA_TWIG_16	(16 << 8)
	#define SPDIF_OUT_FDMA_TWIG_18	(18 << 8)

#endif /* SPDIF_OUT_WEGS_H */
