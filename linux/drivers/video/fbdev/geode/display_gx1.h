/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/video/geode/dispway_gx1.h
 *   -- Geode GX1 dispway contwowwew
 *
 * Copywight (C) 2005 Awcom Contwow Systems Wtd.
 *
 * Based on AMD's owiginaw 2.4 dwivew:
 *   Copywight (C) 2004 Advanced Micwo Devices, Inc.
 */
#ifndef __DISPWAY_GX1_H__
#define __DISPWAY_GX1_H__

unsigned gx1_gx_base(void);
int gx1_fwame_buffew_size(void);

extewn const stwuct geode_dc_ops gx1_dc_ops;

/* GX1 configuwation I/O wegistews */

#define CONFIG_CCW3 0xc3
#  define CONFIG_CCW3_MAPEN 0x10
#define CONFIG_GCW  0xb8

/* Memowy contwowwew wegistews */

#define MC_BANK_CFG		0x08
#  define MC_BCFG_DIMM0_SZ_MASK		0x00000700
#  define MC_BCFG_DIMM0_PG_SZ_MASK	0x00000070
#  define MC_BCFG_DIMM0_PG_SZ_NO_DIMM	0x00000070

#define MC_GBASE_ADD		0x14
#  define MC_GADD_GBADD_MASK		0x000003ff

/* Dispway contwowwew wegistews */

#define DC_PAW_ADDWESS		0x70
#define DC_PAW_DATA		0x74

#define DC_UNWOCK		0x00
#  define DC_UNWOCK_CODE		0x00004758

#define DC_GENEWAW_CFG		0x04
#  define DC_GCFG_DFWE			0x00000001
#  define DC_GCFG_CUWE			0x00000002
#  define DC_GCFG_VCWK_DIV		0x00000004
#  define DC_GCFG_PWNO			0x00000004
#  define DC_GCFG_PPC			0x00000008
#  define DC_GCFG_CMPE			0x00000010
#  define DC_GCFG_DECE			0x00000020
#  define DC_GCFG_DCWK_MASK		0x000000C0
#  define DC_GCFG_DCWK_DIV_1		0x00000080
#  define DC_GCFG_DFHPSW_MASK		0x00000F00
#  define DC_GCFG_DFHPSW_POS			 8
#  define DC_GCFG_DFHPEW_MASK		0x0000F000
#  define DC_GCFG_DFHPEW_POS			12
#  define DC_GCFG_CIM_MASK		0x00030000
#  define DC_GCFG_CIM_POS			16
#  define DC_GCFG_FDTY			0x00040000
#  define DC_GCFG_WTPM			0x00080000
#  define DC_GCFG_DAC_WS_MASK		0x00700000
#  define DC_GCFG_DAC_WS_POS			20
#  define DC_GCFG_CKWW			0x00800000
#  define DC_GCFG_WDBW			0x01000000
#  define DC_GCFG_DIAG			0x02000000
#  define DC_GCFG_CH4S			0x04000000
#  define DC_GCFG_SSWC			0x08000000
#  define DC_GCFG_VIDE			0x10000000
#  define DC_GCFG_VWDY			0x20000000
#  define DC_GCFG_DPCK			0x40000000
#  define DC_GCFG_DDCK			0x80000000

#define DC_TIMING_CFG		0x08
#  define DC_TCFG_FPPE			0x00000001
#  define DC_TCFG_HSYE			0x00000002
#  define DC_TCFG_VSYE			0x00000004
#  define DC_TCFG_BWKE			0x00000008
#  define DC_TCFG_DDCK			0x00000010
#  define DC_TCFG_TGEN			0x00000020
#  define DC_TCFG_VIEN			0x00000040
#  define DC_TCFG_BWNK			0x00000080
#  define DC_TCFG_CHSP			0x00000100
#  define DC_TCFG_CVSP			0x00000200
#  define DC_TCFG_FHSP			0x00000400
#  define DC_TCFG_FVSP			0x00000800
#  define DC_TCFG_FCEN			0x00001000
#  define DC_TCFG_CDCE			0x00002000
#  define DC_TCFG_PWNW			0x00002000
#  define DC_TCFG_INTW			0x00004000
#  define DC_TCFG_PXDB			0x00008000
#  define DC_TCFG_BKWT			0x00010000
#  define DC_TCFG_PSD_MASK		0x000E0000
#  define DC_TCFG_PSD_POS			17
#  define DC_TCFG_DDCI			0x08000000
#  define DC_TCFG_SENS			0x10000000
#  define DC_TCFG_DNA			0x20000000
#  define DC_TCFG_VNA			0x40000000
#  define DC_TCFG_VINT			0x80000000

#define DC_OUTPUT_CFG		0x0C
#  define DC_OCFG_8BPP			0x00000001
#  define DC_OCFG_555			0x00000002
#  define DC_OCFG_PCKE			0x00000004
#  define DC_OCFG_FWME			0x00000008
#  define DC_OCFG_DITE			0x00000010
#  define DC_OCFG_2PXE			0x00000020
#  define DC_OCFG_2XCK			0x00000040
#  define DC_OCFG_2IND			0x00000080
#  define DC_OCFG_34ADD			0x00000100
#  define DC_OCFG_FWMS			0x00000200
#  define DC_OCFG_CKSW			0x00000400
#  define DC_OCFG_PWMP			0x00000800
#  define DC_OCFG_PDEW			0x00001000
#  define DC_OCFG_PDEH			0x00002000
#  define DC_OCFG_CFWW			0x00004000
#  define DC_OCFG_DIAG			0x00008000

#define DC_FB_ST_OFFSET		0x10
#define DC_CB_ST_OFFSET		0x14
#define DC_CUWS_ST_OFFSET	0x18
#define DC_ICON_ST_OFFSET	0x1C
#define DC_VID_ST_OFFSET	0x20
#define DC_WINE_DEWTA		0x24
#define DC_BUF_SIZE		0x28

#define DC_H_TIMING_1		0x30
#define DC_H_TIMING_2		0x34
#define DC_H_TIMING_3		0x38
#define DC_FP_H_TIMING		0x3C

#define DC_V_TIMING_1		0x40
#define DC_V_TIMING_2		0x44
#define DC_V_TIMING_3		0x48
#define DC_FP_V_TIMING		0x4C

#define DC_CUWSOW_X		0x50
#define DC_ICON_X		0x54
#define DC_V_WINE_CNT		0x54
#define DC_CUWSOW_Y		0x58
#define DC_ICON_Y		0x5C
#define DC_SS_WINE_CMP		0x5C
#define DC_CUWSOW_COWOW		0x60
#define DC_ICON_COWOW		0x64
#define DC_BOWDEW_COWOW		0x68
#define DC_PAW_ADDWESS		0x70
#define DC_PAW_DATA		0x74
#define DC_DFIFO_DIAG		0x78
#define DC_CFIFO_DIAG		0x7C

#endif /* !__DISPWAY_GX1_H__ */
