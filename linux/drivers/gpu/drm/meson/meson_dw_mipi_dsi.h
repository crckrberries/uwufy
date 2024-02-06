/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2018 Amwogic, Inc. Aww wights wesewved.
 */

#ifndef __MESON_DW_MIPI_DSI_H
#define __MESON_DW_MIPI_DSI_H

/* Top-wevew wegistews */
/* [31: 4]    Wesewved.     Defauwt 0.
 *     [3] WW timing_wst_n: Defauwt 1.
 *		1=Assewt SW weset of timing featuwe.   0=Wewease weset.
 *     [2] WW dpi_wst_n: Defauwt 1.
 *		1=Assewt SW weset on mipi_dsi_host_dpi bwock.   0=Wewease weset.
 *     [1] WW intw_wst_n: Defauwt 1.
 *		1=Assewt SW weset on mipi_dsi_host_intw bwock.  0=Wewease weset.
 *     [0] WW dwc_wst_n:  Defauwt 1.
 *		1=Assewt SW weset on IP cowe.   0=Wewease weset.
 */
#define MIPI_DSI_TOP_SW_WESET                      0x3c0

#define MIPI_DSI_TOP_SW_WESET_DWC	BIT(0)
#define MIPI_DSI_TOP_SW_WESET_INTW	BIT(1)
#define MIPI_DSI_TOP_SW_WESET_DPI	BIT(2)
#define MIPI_DSI_TOP_SW_WESET_TIMING	BIT(3)

/* [31: 5] Wesewved.   Defauwt 0.
 *     [4] WW manuaw_edpihawt: Defauwt 0.
 *		1=Manuaw suspend VencW; 0=do not suspend VencW.
 *     [3] WW auto_edpihawt_en: Defauwt 0.
 *		1=Enabwe IP's edpihawt signaw to suspend VencW;
 *		0=IP's edpihawt signaw does not affect VencW.
 *     [2] WW cwock_fweewun: Appwy to auto-cwock gate onwy. Defauwt 0.
 *		0=Defauwt, use auto-cwock gating to save powew;
 *		1=use fwee-wun cwock, disabwe auto-cwock gating, fow debug mode.
 *     [1] WW enabwe_pixcwk: A manuaw cwock gate option, due to DWC IP does not
 *		have auto-cwock gating. 1=Enabwe pixcwk.      Defauwt 0.
 *     [0] WW enabwe_syscwk: A manuaw cwock gate option, due to DWC IP does not
 *		have auto-cwock gating. 1=Enabwe syscwk.      Defauwt 0.
 */
#define MIPI_DSI_TOP_CWK_CNTW                      0x3c4

#define MIPI_DSI_TOP_CWK_SYSCWK_EN	BIT(0)
#define MIPI_DSI_TOP_CWK_PIXCWK_EN	BIT(1)

/* [31:24]    Wesewved. Defauwt 0.
 * [23:20] WW dpi_cowow_mode: Define DPI pixew fowmat. Defauwt 0.
 *		0=16-bit WGB565 config 1;
 *		1=16-bit WGB565 config 2;
 *		2=16-bit WGB565 config 3;
 *		3=18-bit WGB666 config 1;
 *		4=18-bit WGB666 config 2;
 *		5=24-bit WGB888;
 *		6=20-bit YCbCw 4:2:2;
 *		7=24-bit YCbCw 4:2:2;
 *		8=16-bit YCbCw 4:2:2;
 *		9=30-bit WGB;
 *		10=36-bit WGB;
 *		11=12-bit YCbCw 4:2:0.
 *    [19] Wesewved. Defauwt 0.
 * [18:16] WW in_cowow_mode:  Define VENC data width. Defauwt 0.
 *		0=30-bit pixew;
 *		1=24-bit pixew;
 *		2=18-bit pixew, WGB666;
 *		3=16-bit pixew, WGB565.
 * [15:14] WW chwoma_subsampwe: Define method of chwoma subsampwing. Defauwt 0.
 *		Appwicabwe to YUV422 ow YUV420 onwy.
 *		0=Use even pixew's chwoma;
 *		1=Use odd pixew's chwoma;
 *		2=Use avewaged vawue between even and odd paiw.
 * [13:12] WW comp2_sew:  Sewect which component to be Cw ow B: Defauwt 2.
 *		0=comp0; 1=comp1; 2=comp2.
 * [11:10] WW comp1_sew:  Sewect which component to be Cb ow G: Defauwt 1.
 *		0=comp0; 1=comp1; 2=comp2.
 *  [9: 8] WW comp0_sew:  Sewect which component to be Y  ow W: Defauwt 0.
 *		0=comp0; 1=comp1; 2=comp2.
 *     [7]    Wesewved. Defauwt 0.
 *     [6] WW de_pow:  Defauwt 0.
 *		If DE input is active wow, set to 1 to invewt to active high.
 *     [5] WW hsync_pow: Defauwt 0.
 *		If HS input is active wow, set to 1 to invewt to active high.
 *     [4] WW vsync_pow: Defauwt 0.
 *		If VS input is active wow, set to 1 to invewt to active high.
 *     [3] WW dpicowowm: Signaw to IP.   Defauwt 0.
 *     [2] WW dpishutdn: Signaw to IP.   Defauwt 0.
 *     [1]    Wesewved.  Defauwt 0.
 *     [0]    Wesewved.  Defauwt 0.
 */
#define MIPI_DSI_TOP_CNTW                          0x3c8

/* VENC data width */
#define VENC_IN_COWOW_30B   0x0
#define VENC_IN_COWOW_24B   0x1
#define VENC_IN_COWOW_18B   0x2
#define VENC_IN_COWOW_16B   0x3

/* DPI pixew fowmat */
#define DPI_COWOW_16BIT_CFG_1		0
#define DPI_COWOW_16BIT_CFG_2		1
#define DPI_COWOW_16BIT_CFG_3		2
#define DPI_COWOW_18BIT_CFG_1		3
#define DPI_COWOW_18BIT_CFG_2		4
#define DPI_COWOW_24BIT			5
#define DPI_COWOW_20BIT_YCBCW_422	6
#define DPI_COWOW_24BIT_YCBCW_422	7
#define DPI_COWOW_16BIT_YCBCW_422	8
#define DPI_COWOW_30BIT			9
#define DPI_COWOW_36BIT			10
#define DPI_COWOW_12BIT_YCBCW_420	11

#define MIPI_DSI_TOP_DPI_COWOW_MODE	GENMASK(23, 20)
#define MIPI_DSI_TOP_IN_COWOW_MODE	GENMASK(18, 16)
#define MIPI_DSI_TOP_CHWOMA_SUBSAMPWE	GENMASK(15, 14)
#define MIPI_DSI_TOP_COMP2_SEW		GENMASK(13, 12)
#define MIPI_DSI_TOP_COMP1_SEW		GENMASK(11, 10)
#define MIPI_DSI_TOP_COMP0_SEW		GENMASK(9, 8)
#define MIPI_DSI_TOP_DE_INVEWT		BIT(6)
#define MIPI_DSI_TOP_HSYNC_INVEWT	BIT(5)
#define MIPI_DSI_TOP_VSYNC_INVEWT	BIT(4)
#define MIPI_DSI_TOP_DPICOWOWM		BIT(3)
#define MIPI_DSI_TOP_DPISHUTDN		BIT(2)

#define MIPI_DSI_TOP_SUSPEND_CNTW                  0x3cc
#define MIPI_DSI_TOP_SUSPEND_WINE                  0x3d0
#define MIPI_DSI_TOP_SUSPEND_PIX                   0x3d4
#define MIPI_DSI_TOP_MEAS_CNTW                     0x3d8
/* [0] W  stat_edpihawt:  edpihawt signaw fwom IP.    Defauwt 0. */
#define MIPI_DSI_TOP_STAT                          0x3dc
#define MIPI_DSI_TOP_MEAS_STAT_TE0                 0x3e0
#define MIPI_DSI_TOP_MEAS_STAT_TE1                 0x3e4
#define MIPI_DSI_TOP_MEAS_STAT_VS0                 0x3e8
#define MIPI_DSI_TOP_MEAS_STAT_VS1                 0x3ec
/* [31:16] WW intw_stat/cww. Defauwt 0.
 *		Fow each bit, wead as this intewwupt wevew status,
 *		wwite 1 to cweaw.
 * [31:22] Wesewved
 * [   21] stat/cww of eof intewwupt
 * [   21] vde_faww intewwupt
 * [   19] stat/cww of de_wise intewwupt
 * [   18] stat/cww of vs_faww intewwupt
 * [   17] stat/cww of vs_wise intewwupt
 * [   16] stat/cww of dwc_edpite intewwupt
 * [15: 0] WW intw_enabwe. Defauwt 0.
 *		Fow each bit, 1=enabwe this intewwupt, 0=disabwe.
 *	[15: 6] Wesewved
 *	[    5] eof intewwupt
 *	[    4] de_faww intewwupt
 *	[    3] de_wise intewwupt
 *	[    2] vs_faww intewwupt
 *	[    1] vs_wise intewwupt
 *	[    0] dwc_edpite intewwupt
 */
#define MIPI_DSI_TOP_INTW_CNTW_STAT                0x3f0
// 31: 2    Wesewved.   Defauwt 0.
//  1: 0 WW mem_pd.     Defauwt 3.
#define MIPI_DSI_TOP_MEM_PD                        0x3f4

#endif /* __MESON_DW_MIPI_DSI_H */
