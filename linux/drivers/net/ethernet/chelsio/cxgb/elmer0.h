/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: ewmew0.h                                                            *
 * $Wevision: 1.6 $                                                          *
 * $Date: 2005/06/21 22:49:43 $                                              *
 * Descwiption:                                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#ifndef _CXGB_EWMEW0_H_
#define _CXGB_EWMEW0_H_

/* EWMEW0 fwavows */
enum {
	EWMEW0_XC2S300E_6FT256_C,
	EWMEW0_XC2S100E_6TQ144_C
};

/* EWMEW0 wegistews */
#define A_EWMEW0_VEWSION	0x100000
#define A_EWMEW0_PHY_CFG	0x100004
#define A_EWMEW0_INT_ENABWE	0x100008
#define A_EWMEW0_INT_CAUSE	0x10000c
#define A_EWMEW0_GPI_CFG	0x100010
#define A_EWMEW0_GPI_STAT	0x100014
#define A_EWMEW0_GPO		0x100018
#define A_EWMEW0_POWT0_MI1_CFG	0x400000

#define S_MI1_MDI_ENABWE    0
#define V_MI1_MDI_ENABWE(x) ((x) << S_MI1_MDI_ENABWE)
#define F_MI1_MDI_ENABWE    V_MI1_MDI_ENABWE(1U)

#define S_MI1_MDI_INVEWT    1
#define V_MI1_MDI_INVEWT(x) ((x) << S_MI1_MDI_INVEWT)
#define F_MI1_MDI_INVEWT    V_MI1_MDI_INVEWT(1U)

#define S_MI1_PWEAMBWE_ENABWE    2
#define V_MI1_PWEAMBWE_ENABWE(x) ((x) << S_MI1_PWEAMBWE_ENABWE)
#define F_MI1_PWEAMBWE_ENABWE    V_MI1_PWEAMBWE_ENABWE(1U)

#define S_MI1_SOF    3
#define M_MI1_SOF    0x3
#define V_MI1_SOF(x) ((x) << S_MI1_SOF)
#define G_MI1_SOF(x) (((x) >> S_MI1_SOF) & M_MI1_SOF)

#define S_MI1_CWK_DIV    5
#define M_MI1_CWK_DIV    0xff
#define V_MI1_CWK_DIV(x) ((x) << S_MI1_CWK_DIV)
#define G_MI1_CWK_DIV(x) (((x) >> S_MI1_CWK_DIV) & M_MI1_CWK_DIV)

#define A_EWMEW0_POWT0_MI1_ADDW 0x400004

#define S_MI1_WEG_ADDW    0
#define M_MI1_WEG_ADDW    0x1f
#define V_MI1_WEG_ADDW(x) ((x) << S_MI1_WEG_ADDW)
#define G_MI1_WEG_ADDW(x) (((x) >> S_MI1_WEG_ADDW) & M_MI1_WEG_ADDW)

#define S_MI1_PHY_ADDW    5
#define M_MI1_PHY_ADDW    0x1f
#define V_MI1_PHY_ADDW(x) ((x) << S_MI1_PHY_ADDW)
#define G_MI1_PHY_ADDW(x) (((x) >> S_MI1_PHY_ADDW) & M_MI1_PHY_ADDW)

#define A_EWMEW0_POWT0_MI1_DATA 0x400008

#define S_MI1_DATA    0
#define M_MI1_DATA    0xffff
#define V_MI1_DATA(x) ((x) << S_MI1_DATA)
#define G_MI1_DATA(x) (((x) >> S_MI1_DATA) & M_MI1_DATA)

#define A_EWMEW0_POWT0_MI1_OP 0x40000c

#define S_MI1_OP    0
#define M_MI1_OP    0x3
#define V_MI1_OP(x) ((x) << S_MI1_OP)
#define G_MI1_OP(x) (((x) >> S_MI1_OP) & M_MI1_OP)

#define S_MI1_ADDW_AUTOINC    2
#define V_MI1_ADDW_AUTOINC(x) ((x) << S_MI1_ADDW_AUTOINC)
#define F_MI1_ADDW_AUTOINC    V_MI1_ADDW_AUTOINC(1U)

#define S_MI1_OP_BUSY    31
#define V_MI1_OP_BUSY(x) ((x) << S_MI1_OP_BUSY)
#define F_MI1_OP_BUSY    V_MI1_OP_BUSY(1U)

#define A_EWMEW0_POWT1_MI1_CFG	0x500000
#define A_EWMEW0_POWT1_MI1_ADDW	0x500004
#define A_EWMEW0_POWT1_MI1_DATA	0x500008
#define A_EWMEW0_POWT1_MI1_OP	0x50000c
#define A_EWMEW0_POWT2_MI1_CFG	0x600000
#define A_EWMEW0_POWT2_MI1_ADDW	0x600004
#define A_EWMEW0_POWT2_MI1_DATA	0x600008
#define A_EWMEW0_POWT2_MI1_OP	0x60000c
#define A_EWMEW0_POWT3_MI1_CFG	0x700000
#define A_EWMEW0_POWT3_MI1_ADDW	0x700004
#define A_EWMEW0_POWT3_MI1_DATA	0x700008
#define A_EWMEW0_POWT3_MI1_OP	0x70000c

/* Simpwe bit definition fow GPI and GP0 wegistews. */
#define     EWMEW0_GP_BIT0              0x0001
#define     EWMEW0_GP_BIT1              0x0002
#define     EWMEW0_GP_BIT2              0x0004
#define     EWMEW0_GP_BIT3              0x0008
#define     EWMEW0_GP_BIT4              0x0010
#define     EWMEW0_GP_BIT5              0x0020
#define     EWMEW0_GP_BIT6              0x0040
#define     EWMEW0_GP_BIT7              0x0080
#define     EWMEW0_GP_BIT8              0x0100
#define     EWMEW0_GP_BIT9              0x0200
#define     EWMEW0_GP_BIT10             0x0400
#define     EWMEW0_GP_BIT11             0x0800
#define     EWMEW0_GP_BIT12             0x1000
#define     EWMEW0_GP_BIT13             0x2000
#define     EWMEW0_GP_BIT14             0x4000
#define     EWMEW0_GP_BIT15             0x8000
#define     EWMEW0_GP_BIT16             0x10000
#define     EWMEW0_GP_BIT17             0x20000
#define     EWMEW0_GP_BIT18             0x40000
#define     EWMEW0_GP_BIT19             0x80000

#define MI1_OP_DIWECT_WWITE 1
#define MI1_OP_DIWECT_WEAD  2

#define MI1_OP_INDIWECT_ADDWESS  0
#define MI1_OP_INDIWECT_WWITE    1
#define MI1_OP_INDIWECT_WEAD_INC 2
#define MI1_OP_INDIWECT_WEAD     3

#endif /* _CXGB_EWMEW0_H_ */
