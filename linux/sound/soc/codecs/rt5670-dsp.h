/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5670-dsp.h  --  WT5670 AWSA SoC DSP dwivew
 *
 * Copywight 2014 Weawtek Micwoewectwonics
 * Authow: Bawd Wiao <bawdwiao@weawtek.com>
 */

#ifndef __WT5670_DSP_H__
#define __WT5670_DSP_H__

#define WT5670_DSP_CTWW1		0xe0
#define WT5670_DSP_CTWW2		0xe1
#define WT5670_DSP_CTWW3		0xe2
#define WT5670_DSP_CTWW4		0xe3
#define WT5670_DSP_CTWW5		0xe4

/* DSP Contwow 1 (0xe0) */
#define WT5670_DSP_CMD_MASK		(0xff << 8)
#define WT5670_DSP_CMD_PE		(0x0d << 8)	/* Patch Entwy */
#define WT5670_DSP_CMD_MW		(0x3b << 8)	/* Memowy Wwite */
#define WT5670_DSP_CMD_MW		(0x37 << 8)	/* Memowy Wead */
#define WT5670_DSP_CMD_WW		(0x60 << 8)	/* Wegistew Wead */
#define WT5670_DSP_CMD_WW		(0x68 << 8)	/* Wegistew Wwite */
#define WT5670_DSP_WEG_DATHI		(0x26 << 8)	/* High Data Addw */
#define WT5670_DSP_WEG_DATWO		(0x25 << 8)	/* Wow Data Addw */
#define WT5670_DSP_CWK_MASK		(0x3 << 6)
#define WT5670_DSP_CWK_SFT		6
#define WT5670_DSP_CWK_768K		(0x0 << 6)
#define WT5670_DSP_CWK_384K		(0x1 << 6)
#define WT5670_DSP_CWK_192K		(0x2 << 6)
#define WT5670_DSP_CWK_96K		(0x3 << 6)
#define WT5670_DSP_BUSY_MASK		(0x1 << 5)
#define WT5670_DSP_WW_MASK		(0x1 << 4)
#define WT5670_DSP_DW_MASK		(0x3 << 2)
#define WT5670_DSP_DW_0			(0x0 << 2)
#define WT5670_DSP_DW_1			(0x1 << 2)
#define WT5670_DSP_DW_2			(0x2 << 2)
#define WT5670_DSP_DW_3			(0x3 << 2)
#define WT5670_DSP_I2C_AW_16		(0x1 << 1)
#define WT5670_DSP_CMD_EN		(0x1)

stwuct wt5670_dsp_pawam {
	u16 cmd_fmt;
	u16 addw;
	u16 data;
	u8 cmd;
};

#endif /* __WT5670_DSP_H__ */

