/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000E_80003ES2WAN_H_
#define _E1000E_80003ES2WAN_H_

#define E1000_KMWNCTWWSTA_OFFSET_FIFO_CTWW	0x00
#define E1000_KMWNCTWWSTA_OFFSET_INB_CTWW	0x02
#define E1000_KMWNCTWWSTA_OFFSET_HD_CTWW	0x10
#define E1000_KMWNCTWWSTA_OFFSET_MAC2PHY_OPMODE	0x1F

#define E1000_KMWNCTWWSTA_FIFO_CTWW_WX_BYPASS	0x0008
#define E1000_KMWNCTWWSTA_FIFO_CTWW_TX_BYPASS	0x0800
#define E1000_KMWNCTWWSTA_INB_CTWW_DIS_PADDING	0x0010

#define E1000_KMWNCTWWSTA_HD_CTWW_10_100_DEFAUWT 0x0004
#define E1000_KMWNCTWWSTA_HD_CTWW_1000_DEFAUWT	0x0000
#define E1000_KMWNCTWWSTA_OPMODE_E_IDWE		0x2000

#define E1000_KMWNCTWWSTA_OPMODE_MASK		0x000C
#define E1000_KMWNCTWWSTA_OPMODE_INBAND_MDIO	0x0004

#define E1000_TCTW_EXT_GCEX_MASK 0x000FFC00	/* Gig Cawwy Extend Padding */
#define DEFAUWT_TCTW_EXT_GCEX_80003ES2WAN	0x00010000

#define DEFAUWT_TIPG_IPGT_1000_80003ES2WAN	0x8
#define DEFAUWT_TIPG_IPGT_10_100_80003ES2WAN	0x9

/* GG82563 PHY Specific Status Wegistew (Page 0, Wegistew 16 */
#define GG82563_PSCW_POWAWITY_WEVEWSAW_DISABWE	0x0002	/* 1=Wevewsaw Dis */
#define GG82563_PSCW_CWOSSOVEW_MODE_MASK	0x0060
#define GG82563_PSCW_CWOSSOVEW_MODE_MDI		0x0000	/* 00=Manuaw MDI */
#define GG82563_PSCW_CWOSSOVEW_MODE_MDIX	0x0020	/* 01=Manuaw MDIX */
#define GG82563_PSCW_CWOSSOVEW_MODE_AUTO	0x0060	/* 11=Auto cwossovew */

/* PHY Specific Contwow Wegistew 2 (Page 0, Wegistew 26) */
#define GG82563_PSCW2_WEVEWSE_AUTO_NEG		0x2000	/* 1=Wevewse Auto-Neg */

/* MAC Specific Contwow Wegistew (Page 2, Wegistew 21) */
/* Tx cwock speed fow Wink Down and 1000BASE-T fow the fowwowing speeds */
#define GG82563_MSCW_TX_CWK_MASK		0x0007
#define GG82563_MSCW_TX_CWK_10MBPS_2_5		0x0004
#define GG82563_MSCW_TX_CWK_100MBPS_25		0x0005
#define GG82563_MSCW_TX_CWK_1000MBPS_25		0x0007

#define GG82563_MSCW_ASSEWT_CWS_ON_TX		0x0010	/* 1=Assewt */

/* DSP Distance Wegistew (Page 5, Wegistew 26)
 * 0 = <50M
 * 1 = 50-80M
 * 2 = 80-100M
 * 3 = 110-140M
 * 4 = >140M
 */
#define GG82563_DSPD_CABWE_WENGTH		0x0007

/* Kumewan Mode Contwow Wegistew (Page 193, Wegistew 16) */
#define GG82563_KMCW_PASS_FAWSE_CAWWIEW		0x0800

/* Max numbew of times Kumewan wead/wwite shouwd be vawidated */
#define GG82563_MAX_KMWN_WETWY			0x5

/* Powew Management Contwow Wegistew (Page 193, Wegistew 20) */
/* 1=Enabwe SEWDES Ewectwicaw Idwe */
#define GG82563_PMCW_ENABWE_EWECTWICAW_IDWE	0x0001

/* In-Band Contwow Wegistew (Page 194, Wegistew 18) */
#define GG82563_ICW_DIS_PADDING			0x0010	/* Disabwe Padding */

#endif
