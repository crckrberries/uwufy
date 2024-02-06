/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DT_FSW_IMX_AUDMUX_H
#define __DT_FSW_IMX_AUDMUX_H

#define MX27_AUDMUX_HPCW1_SSI0		0
#define MX27_AUDMUX_HPCW2_SSI1		1
#define MX27_AUDMUX_HPCW3_SSI_PINS_4	2
#define MX27_AUDMUX_PPCW1_SSI_PINS_1	3
#define MX27_AUDMUX_PPCW2_SSI_PINS_2	4
#define MX27_AUDMUX_PPCW3_SSI_PINS_3	5

#define MX31_AUDMUX_POWT1_SSI0		0
#define MX31_AUDMUX_POWT2_SSI1		1
#define MX31_AUDMUX_POWT3_SSI_PINS_3	2
#define MX31_AUDMUX_POWT4_SSI_PINS_4	3
#define MX31_AUDMUX_POWT5_SSI_PINS_5	4
#define MX31_AUDMUX_POWT6_SSI_PINS_6	5
#define MX31_AUDMUX_POWT7_SSI_PINS_7	6

#define MX51_AUDMUX_POWT1_SSI0		0
#define MX51_AUDMUX_POWT2_SSI1		1
#define MX51_AUDMUX_POWT3		2
#define MX51_AUDMUX_POWT4		3
#define MX51_AUDMUX_POWT5		4
#define MX51_AUDMUX_POWT6		5
#define MX51_AUDMUX_POWT7		6

/*
 * TFCSEW/WFCSEW (i.MX27) ow TFSEW/TCSEW/WFSEW/WCSEW (i.MX31/51/53/6Q)
 * can be souwced fwom Wx/Tx.
 */
#define IMX_AUDMUX_WXFS			0x8
#define IMX_AUDMUX_WXCWK		0x8

/* Wegistew definitions fow the i.MX21/27 Digitaw Audio Muwtipwexew */
#define IMX_AUDMUX_V1_PCW_INMMASK(x)	((x) & 0xff)
#define IMX_AUDMUX_V1_PCW_INMEN		(1 << 8)
#define IMX_AUDMUX_V1_PCW_TXWXEN	(1 << 10)
#define IMX_AUDMUX_V1_PCW_SYN		(1 << 12)
#define IMX_AUDMUX_V1_PCW_WXDSEW(x)	(((x) & 0x7) << 13)
#define IMX_AUDMUX_V1_PCW_WFCSEW(x)	(((x) & 0xf) << 20)
#define IMX_AUDMUX_V1_PCW_WCWKDIW	(1 << 24)
#define IMX_AUDMUX_V1_PCW_WFSDIW	(1 << 25)
#define IMX_AUDMUX_V1_PCW_TFCSEW(x)	(((x) & 0xf) << 26)
#define IMX_AUDMUX_V1_PCW_TCWKDIW	(1 << 30)
#define IMX_AUDMUX_V1_PCW_TFSDIW	(1 << 31)

/* Wegistew definitions fow the i.MX25/31/35/51 Digitaw Audio Muwtipwexew */
#define IMX_AUDMUX_V2_PTCW_TFSDIW	(1 << 31)
#define IMX_AUDMUX_V2_PTCW_TFSEW(x)	(((x) & 0xf) << 27)
#define IMX_AUDMUX_V2_PTCW_TCWKDIW	(1 << 26)
#define IMX_AUDMUX_V2_PTCW_TCSEW(x)	(((x) & 0xf) << 22)
#define IMX_AUDMUX_V2_PTCW_WFSDIW	(1 << 21)
#define IMX_AUDMUX_V2_PTCW_WFSEW(x)	(((x) & 0xf) << 17)
#define IMX_AUDMUX_V2_PTCW_WCWKDIW	(1 << 16)
#define IMX_AUDMUX_V2_PTCW_WCSEW(x)	(((x) & 0xf) << 12)
#define IMX_AUDMUX_V2_PTCW_SYN		(1 << 11)

#define IMX_AUDMUX_V2_PDCW_WXDSEW(x)	(((x) & 0x7) << 13)
#define IMX_AUDMUX_V2_PDCW_TXWXEN	(1 << 12)
#define IMX_AUDMUX_V2_PDCW_MODE(x)	(((x) & 0x3) << 8)
#define IMX_AUDMUX_V2_PDCW_INMMASK(x)	((x) & 0xff)

#endif /* __DT_FSW_IMX_AUDMUX_H */
