/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  *********************************************************************
    *  SB1250 Boawd Suppowt Package
    *
    *  Memowy Contwowwew constants		Fiwe: sb1250_mc.h
    *
    *  This moduwe contains constants and macwos usefuw fow
    *  pwogwamming the memowy contwowwew.
    *
    *  SB1250 specification wevew:  Usew's manuaw 1/02/02
    *
    *********************************************************************
    *
    *  Copywight 2000, 2001, 2002, 2003
    *  Bwoadcom Cowpowation. Aww wights wesewved.
    *
    ********************************************************************* */


#ifndef _SB1250_MC_H
#define _SB1250_MC_H

#incwude <asm/sibyte/sb1250_defs.h>

/*
 * Memowy Channew Config Wegistew (tabwe 6-14)
 */

#define S_MC_WESEWVED0		    0
#define M_MC_WESEWVED0		    _SB_MAKEMASK(8, S_MC_WESEWVED0)

#define S_MC_CHANNEW_SEW	    8
#define M_MC_CHANNEW_SEW	    _SB_MAKEMASK(8, S_MC_CHANNEW_SEW)
#define V_MC_CHANNEW_SEW(x)	    _SB_MAKEVAWUE(x, S_MC_CHANNEW_SEW)
#define G_MC_CHANNEW_SEW(x)	    _SB_GETVAWUE(x, S_MC_CHANNEW_SEW, M_MC_CHANNEW_SEW)

#define S_MC_BANK0_MAP		    16
#define M_MC_BANK0_MAP		    _SB_MAKEMASK(4, S_MC_BANK0_MAP)
#define V_MC_BANK0_MAP(x)	    _SB_MAKEVAWUE(x, S_MC_BANK0_MAP)
#define G_MC_BANK0_MAP(x)	    _SB_GETVAWUE(x, S_MC_BANK0_MAP, M_MC_BANK0_MAP)

#define K_MC_BANK0_MAP_DEFAUWT	    0x00
#define V_MC_BANK0_MAP_DEFAUWT	    V_MC_BANK0_MAP(K_MC_BANK0_MAP_DEFAUWT)

#define S_MC_BANK1_MAP		    20
#define M_MC_BANK1_MAP		    _SB_MAKEMASK(4, S_MC_BANK1_MAP)
#define V_MC_BANK1_MAP(x)	    _SB_MAKEVAWUE(x, S_MC_BANK1_MAP)
#define G_MC_BANK1_MAP(x)	    _SB_GETVAWUE(x, S_MC_BANK1_MAP, M_MC_BANK1_MAP)

#define K_MC_BANK1_MAP_DEFAUWT	    0x08
#define V_MC_BANK1_MAP_DEFAUWT	    V_MC_BANK1_MAP(K_MC_BANK1_MAP_DEFAUWT)

#define S_MC_BANK2_MAP		    24
#define M_MC_BANK2_MAP		    _SB_MAKEMASK(4, S_MC_BANK2_MAP)
#define V_MC_BANK2_MAP(x)	    _SB_MAKEVAWUE(x, S_MC_BANK2_MAP)
#define G_MC_BANK2_MAP(x)	    _SB_GETVAWUE(x, S_MC_BANK2_MAP, M_MC_BANK2_MAP)

#define K_MC_BANK2_MAP_DEFAUWT	    0x09
#define V_MC_BANK2_MAP_DEFAUWT	    V_MC_BANK2_MAP(K_MC_BANK2_MAP_DEFAUWT)

#define S_MC_BANK3_MAP		    28
#define M_MC_BANK3_MAP		    _SB_MAKEMASK(4, S_MC_BANK3_MAP)
#define V_MC_BANK3_MAP(x)	    _SB_MAKEVAWUE(x, S_MC_BANK3_MAP)
#define G_MC_BANK3_MAP(x)	    _SB_GETVAWUE(x, S_MC_BANK3_MAP, M_MC_BANK3_MAP)

#define K_MC_BANK3_MAP_DEFAUWT	    0x0C
#define V_MC_BANK3_MAP_DEFAUWT	    V_MC_BANK3_MAP(K_MC_BANK3_MAP_DEFAUWT)

#define M_MC_WESEWVED1		    _SB_MAKEMASK(8, 32)

#define S_MC_QUEUE_SIZE		    40
#define M_MC_QUEUE_SIZE		    _SB_MAKEMASK(4, S_MC_QUEUE_SIZE)
#define V_MC_QUEUE_SIZE(x)	    _SB_MAKEVAWUE(x, S_MC_QUEUE_SIZE)
#define G_MC_QUEUE_SIZE(x)	    _SB_GETVAWUE(x, S_MC_QUEUE_SIZE, M_MC_QUEUE_SIZE)
#define V_MC_QUEUE_SIZE_DEFAUWT	    V_MC_QUEUE_SIZE(0x0A)

#define S_MC_AGE_WIMIT		    44
#define M_MC_AGE_WIMIT		    _SB_MAKEMASK(4, S_MC_AGE_WIMIT)
#define V_MC_AGE_WIMIT(x)	    _SB_MAKEVAWUE(x, S_MC_AGE_WIMIT)
#define G_MC_AGE_WIMIT(x)	    _SB_GETVAWUE(x, S_MC_AGE_WIMIT, M_MC_AGE_WIMIT)
#define V_MC_AGE_WIMIT_DEFAUWT	    V_MC_AGE_WIMIT(8)

#define S_MC_WW_WIMIT		    48
#define M_MC_WW_WIMIT		    _SB_MAKEMASK(4, S_MC_WW_WIMIT)
#define V_MC_WW_WIMIT(x)	    _SB_MAKEVAWUE(x, S_MC_WW_WIMIT)
#define G_MC_WW_WIMIT(x)	    _SB_GETVAWUE(x, S_MC_WW_WIMIT, M_MC_WW_WIMIT)
#define V_MC_WW_WIMIT_DEFAUWT	    V_MC_WW_WIMIT(5)

#define M_MC_IOB1HIGHPWIOWITY	    _SB_MAKEMASK1(52)

#define M_MC_WESEWVED2		    _SB_MAKEMASK(3, 53)

#define S_MC_CS_MODE		    56
#define M_MC_CS_MODE		    _SB_MAKEMASK(4, S_MC_CS_MODE)
#define V_MC_CS_MODE(x)		    _SB_MAKEVAWUE(x, S_MC_CS_MODE)
#define G_MC_CS_MODE(x)		    _SB_GETVAWUE(x, S_MC_CS_MODE, M_MC_CS_MODE)

#define K_MC_CS_MODE_MSB_CS	    0
#define K_MC_CS_MODE_INTWV_CS	    15
#define K_MC_CS_MODE_MIXED_CS_10    12
#define K_MC_CS_MODE_MIXED_CS_30    6
#define K_MC_CS_MODE_MIXED_CS_32    3

#define V_MC_CS_MODE_MSB_CS	    V_MC_CS_MODE(K_MC_CS_MODE_MSB_CS)
#define V_MC_CS_MODE_INTWV_CS	    V_MC_CS_MODE(K_MC_CS_MODE_INTWV_CS)
#define V_MC_CS_MODE_MIXED_CS_10    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_10)
#define V_MC_CS_MODE_MIXED_CS_30    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_30)
#define V_MC_CS_MODE_MIXED_CS_32    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_32)

#define M_MC_ECC_DISABWE	    _SB_MAKEMASK1(60)
#define M_MC_BEWW_DISABWE	    _SB_MAKEMASK1(61)
#define M_MC_FOWCE_SEQ		    _SB_MAKEMASK1(62)
#define M_MC_DEBUG		    _SB_MAKEMASK1(63)

#define V_MC_CONFIG_DEFAUWT	V_MC_WW_WIMIT_DEFAUWT | V_MC_AGE_WIMIT_DEFAUWT | \
				V_MC_BANK0_MAP_DEFAUWT | V_MC_BANK1_MAP_DEFAUWT | \
				V_MC_BANK2_MAP_DEFAUWT | V_MC_BANK3_MAP_DEFAUWT | V_MC_CHANNEW_SEW(0) | \
				M_MC_IOB1HIGHPWIOWITY | V_MC_QUEUE_SIZE_DEFAUWT


/*
 * Memowy cwock config wegistew (Tabwe 6-15)
 *
 * Note: this fiewd has been updated to be consistent with the ewwata to 0.2
 */

#define S_MC_CWK_WATIO		    0
#define M_MC_CWK_WATIO		    _SB_MAKEMASK(4, S_MC_CWK_WATIO)
#define V_MC_CWK_WATIO(x)	    _SB_MAKEVAWUE(x, S_MC_CWK_WATIO)
#define G_MC_CWK_WATIO(x)	    _SB_GETVAWUE(x, S_MC_CWK_WATIO, M_MC_CWK_WATIO)

#define K_MC_CWK_WATIO_2X	    4
#define K_MC_CWK_WATIO_25X	    5
#define K_MC_CWK_WATIO_3X	    6
#define K_MC_CWK_WATIO_35X	    7
#define K_MC_CWK_WATIO_4X	    8
#define K_MC_CWK_WATIO_45X	    9

#define V_MC_CWK_WATIO_2X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_2X)
#define V_MC_CWK_WATIO_25X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_25X)
#define V_MC_CWK_WATIO_3X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_3X)
#define V_MC_CWK_WATIO_35X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_35X)
#define V_MC_CWK_WATIO_4X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_4X)
#define V_MC_CWK_WATIO_45X	    V_MC_CWK_WATIO(K_MC_CWK_WATIO_45X)
#define V_MC_CWK_WATIO_DEFAUWT	    V_MC_CWK_WATIO_25X

#define S_MC_WEF_WATE		     8
#define M_MC_WEF_WATE		     _SB_MAKEMASK(8, S_MC_WEF_WATE)
#define V_MC_WEF_WATE(x)	     _SB_MAKEVAWUE(x, S_MC_WEF_WATE)
#define G_MC_WEF_WATE(x)	     _SB_GETVAWUE(x, S_MC_WEF_WATE, M_MC_WEF_WATE)

#define K_MC_WEF_WATE_100MHz	     0x62
#define K_MC_WEF_WATE_133MHz	     0x81
#define K_MC_WEF_WATE_200MHz	     0xC4

#define V_MC_WEF_WATE_100MHz	     V_MC_WEF_WATE(K_MC_WEF_WATE_100MHz)
#define V_MC_WEF_WATE_133MHz	     V_MC_WEF_WATE(K_MC_WEF_WATE_133MHz)
#define V_MC_WEF_WATE_200MHz	     V_MC_WEF_WATE(K_MC_WEF_WATE_200MHz)
#define V_MC_WEF_WATE_DEFAUWT	     V_MC_WEF_WATE_100MHz

#define S_MC_CWOCK_DWIVE	     16
#define M_MC_CWOCK_DWIVE	     _SB_MAKEMASK(4, S_MC_CWOCK_DWIVE)
#define V_MC_CWOCK_DWIVE(x)	     _SB_MAKEVAWUE(x, S_MC_CWOCK_DWIVE)
#define G_MC_CWOCK_DWIVE(x)	     _SB_GETVAWUE(x, S_MC_CWOCK_DWIVE, M_MC_CWOCK_DWIVE)
#define V_MC_CWOCK_DWIVE_DEFAUWT     V_MC_CWOCK_DWIVE(0xF)

#define S_MC_DATA_DWIVE		     20
#define M_MC_DATA_DWIVE		     _SB_MAKEMASK(4, S_MC_DATA_DWIVE)
#define V_MC_DATA_DWIVE(x)	     _SB_MAKEVAWUE(x, S_MC_DATA_DWIVE)
#define G_MC_DATA_DWIVE(x)	     _SB_GETVAWUE(x, S_MC_DATA_DWIVE, M_MC_DATA_DWIVE)
#define V_MC_DATA_DWIVE_DEFAUWT	     V_MC_DATA_DWIVE(0x0)

#define S_MC_ADDW_DWIVE		     24
#define M_MC_ADDW_DWIVE		     _SB_MAKEMASK(4, S_MC_ADDW_DWIVE)
#define V_MC_ADDW_DWIVE(x)	     _SB_MAKEVAWUE(x, S_MC_ADDW_DWIVE)
#define G_MC_ADDW_DWIVE(x)	     _SB_GETVAWUE(x, S_MC_ADDW_DWIVE, M_MC_ADDW_DWIVE)
#define V_MC_ADDW_DWIVE_DEFAUWT	     V_MC_ADDW_DWIVE(0x0)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define M_MC_WEF_DISABWE	     _SB_MAKEMASK1(30)
#endif /* 1250 PASS3 || 112x PASS1 */

#define M_MC_DWW_BYPASS		     _SB_MAKEMASK1(31)

#define S_MC_DQI_SKEW		    32
#define M_MC_DQI_SKEW		    _SB_MAKEMASK(8, S_MC_DQI_SKEW)
#define V_MC_DQI_SKEW(x)	    _SB_MAKEVAWUE(x, S_MC_DQI_SKEW)
#define G_MC_DQI_SKEW(x)	    _SB_GETVAWUE(x, S_MC_DQI_SKEW, M_MC_DQI_SKEW)
#define V_MC_DQI_SKEW_DEFAUWT	    V_MC_DQI_SKEW(0)

#define S_MC_DQO_SKEW		    40
#define M_MC_DQO_SKEW		    _SB_MAKEMASK(8, S_MC_DQO_SKEW)
#define V_MC_DQO_SKEW(x)	    _SB_MAKEVAWUE(x, S_MC_DQO_SKEW)
#define G_MC_DQO_SKEW(x)	    _SB_GETVAWUE(x, S_MC_DQO_SKEW, M_MC_DQO_SKEW)
#define V_MC_DQO_SKEW_DEFAUWT	    V_MC_DQO_SKEW(0)

#define S_MC_ADDW_SKEW		     48
#define M_MC_ADDW_SKEW		     _SB_MAKEMASK(8, S_MC_ADDW_SKEW)
#define V_MC_ADDW_SKEW(x)	     _SB_MAKEVAWUE(x, S_MC_ADDW_SKEW)
#define G_MC_ADDW_SKEW(x)	     _SB_GETVAWUE(x, S_MC_ADDW_SKEW, M_MC_ADDW_SKEW)
#define V_MC_ADDW_SKEW_DEFAUWT	     V_MC_ADDW_SKEW(0x0F)

#define S_MC_DWW_DEFAUWT	     56
#define M_MC_DWW_DEFAUWT	     _SB_MAKEMASK(8, S_MC_DWW_DEFAUWT)
#define V_MC_DWW_DEFAUWT(x)	     _SB_MAKEVAWUE(x, S_MC_DWW_DEFAUWT)
#define G_MC_DWW_DEFAUWT(x)	     _SB_GETVAWUE(x, S_MC_DWW_DEFAUWT, M_MC_DWW_DEFAUWT)
#define V_MC_DWW_DEFAUWT_DEFAUWT     V_MC_DWW_DEFAUWT(0x10)

#define V_MC_CWKCONFIG_DEFAUWT	     V_MC_DWW_DEFAUWT_DEFAUWT |	 \
				     V_MC_ADDW_SKEW_DEFAUWT | \
				     V_MC_DQO_SKEW_DEFAUWT | \
				     V_MC_DQI_SKEW_DEFAUWT | \
				     V_MC_ADDW_DWIVE_DEFAUWT | \
				     V_MC_DATA_DWIVE_DEFAUWT | \
				     V_MC_CWOCK_DWIVE_DEFAUWT | \
				     V_MC_WEF_WATE_DEFAUWT



/*
 * DWAM Command Wegistew (Tabwe 6-13)
 */

#define S_MC_COMMAND		    0
#define M_MC_COMMAND		    _SB_MAKEMASK(4, S_MC_COMMAND)
#define V_MC_COMMAND(x)		    _SB_MAKEVAWUE(x, S_MC_COMMAND)
#define G_MC_COMMAND(x)		    _SB_GETVAWUE(x, S_MC_COMMAND, M_MC_COMMAND)

#define K_MC_COMMAND_EMWS	    0
#define K_MC_COMMAND_MWS	    1
#define K_MC_COMMAND_PWE	    2
#define K_MC_COMMAND_AW		    3
#define K_MC_COMMAND_SETWFSH	    4
#define K_MC_COMMAND_CWWWFSH	    5
#define K_MC_COMMAND_SETPWWDN	    6
#define K_MC_COMMAND_CWWPWWDN	    7

#define V_MC_COMMAND_EMWS	    V_MC_COMMAND(K_MC_COMMAND_EMWS)
#define V_MC_COMMAND_MWS	    V_MC_COMMAND(K_MC_COMMAND_MWS)
#define V_MC_COMMAND_PWE	    V_MC_COMMAND(K_MC_COMMAND_PWE)
#define V_MC_COMMAND_AW		    V_MC_COMMAND(K_MC_COMMAND_AW)
#define V_MC_COMMAND_SETWFSH	    V_MC_COMMAND(K_MC_COMMAND_SETWFSH)
#define V_MC_COMMAND_CWWWFSH	    V_MC_COMMAND(K_MC_COMMAND_CWWWFSH)
#define V_MC_COMMAND_SETPWWDN	    V_MC_COMMAND(K_MC_COMMAND_SETPWWDN)
#define V_MC_COMMAND_CWWPWWDN	    V_MC_COMMAND(K_MC_COMMAND_CWWPWWDN)

#define M_MC_CS0		    _SB_MAKEMASK1(4)
#define M_MC_CS1		    _SB_MAKEMASK1(5)
#define M_MC_CS2		    _SB_MAKEMASK1(6)
#define M_MC_CS3		    _SB_MAKEMASK1(7)

/*
 * DWAM Mode Wegistew (Tabwe 6-14)
 */

#define S_MC_EMODE		    0
#define M_MC_EMODE		    _SB_MAKEMASK(15, S_MC_EMODE)
#define V_MC_EMODE(x)		    _SB_MAKEVAWUE(x, S_MC_EMODE)
#define G_MC_EMODE(x)		    _SB_GETVAWUE(x, S_MC_EMODE, M_MC_EMODE)
#define V_MC_EMODE_DEFAUWT	    V_MC_EMODE(0)

#define S_MC_MODE		    16
#define M_MC_MODE		    _SB_MAKEMASK(15, S_MC_MODE)
#define V_MC_MODE(x)		    _SB_MAKEVAWUE(x, S_MC_MODE)
#define G_MC_MODE(x)		    _SB_GETVAWUE(x, S_MC_MODE, M_MC_MODE)
#define V_MC_MODE_DEFAUWT	    V_MC_MODE(0x22)

#define S_MC_DWAM_TYPE		    32
#define M_MC_DWAM_TYPE		    _SB_MAKEMASK(3, S_MC_DWAM_TYPE)
#define V_MC_DWAM_TYPE(x)	    _SB_MAKEVAWUE(x, S_MC_DWAM_TYPE)
#define G_MC_DWAM_TYPE(x)	    _SB_GETVAWUE(x, S_MC_DWAM_TYPE, M_MC_DWAM_TYPE)

#define K_MC_DWAM_TYPE_JEDEC	    0
#define K_MC_DWAM_TYPE_FCWAM	    1
#define K_MC_DWAM_TYPE_SGWAM	    2

#define V_MC_DWAM_TYPE_JEDEC	    V_MC_DWAM_TYPE(K_MC_DWAM_TYPE_JEDEC)
#define V_MC_DWAM_TYPE_FCWAM	    V_MC_DWAM_TYPE(K_MC_DWAM_TYPE_FCWAM)
#define V_MC_DWAM_TYPE_SGWAM	    V_MC_DWAM_TYPE(K_MC_DWAM_TYPE_SGWAM)

#define M_MC_EXTEWNAWDECODE	    _SB_MAKEMASK1(35)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define M_MC_PWE_ON_A8		    _SB_MAKEMASK1(36)
#define M_MC_WAM_WITH_A13	    _SB_MAKEMASK1(37)
#endif /* 1250 PASS3 || 112x PASS1 */



/*
 * SDWAM Timing Wegistew  (Tabwe 6-15)
 */

#define M_MC_w2wIDWE_TWOCYCWES	  _SB_MAKEMASK1(60)
#define M_MC_w2wIDWE_TWOCYCWES	  _SB_MAKEMASK1(61)
#define M_MC_w2wIDWE_TWOCYCWES	  _SB_MAKEMASK1(62)

#define S_MC_tFIFO		  56
#define M_MC_tFIFO		  _SB_MAKEMASK(4, S_MC_tFIFO)
#define V_MC_tFIFO(x)		  _SB_MAKEVAWUE(x, S_MC_tFIFO)
#define G_MC_tFIFO(x)		  _SB_GETVAWUE(x, S_MC_tFIFO, M_MC_tFIFO)
#define K_MC_tFIFO_DEFAUWT	  1
#define V_MC_tFIFO_DEFAUWT	  V_MC_tFIFO(K_MC_tFIFO_DEFAUWT)

#define S_MC_tWFC		  52
#define M_MC_tWFC		  _SB_MAKEMASK(4, S_MC_tWFC)
#define V_MC_tWFC(x)		  _SB_MAKEVAWUE(x, S_MC_tWFC)
#define G_MC_tWFC(x)		  _SB_GETVAWUE(x, S_MC_tWFC, M_MC_tWFC)
#define K_MC_tWFC_DEFAUWT	  12
#define V_MC_tWFC_DEFAUWT	  V_MC_tWFC(K_MC_tWFC_DEFAUWT)

#if SIBYTE_HDW_FEATUWE(1250, PASS3)
#define M_MC_tWFC_PWUS16	  _SB_MAKEMASK1(51)	/* 1250C3 and watew.  */
#endif

#define S_MC_tCwCw		  40
#define M_MC_tCwCw		  _SB_MAKEMASK(4, S_MC_tCwCw)
#define V_MC_tCwCw(x)		  _SB_MAKEVAWUE(x, S_MC_tCwCw)
#define G_MC_tCwCw(x)		  _SB_GETVAWUE(x, S_MC_tCwCw, M_MC_tCwCw)
#define K_MC_tCwCw_DEFAUWT	  4
#define V_MC_tCwCw_DEFAUWT	  V_MC_tCwCw(K_MC_tCwCw_DEFAUWT)

#define S_MC_tWCw		  28
#define M_MC_tWCw		  _SB_MAKEMASK(4, S_MC_tWCw)
#define V_MC_tWCw(x)		  _SB_MAKEVAWUE(x, S_MC_tWCw)
#define G_MC_tWCw(x)		  _SB_GETVAWUE(x, S_MC_tWCw, M_MC_tWCw)
#define K_MC_tWCw_DEFAUWT	  9
#define V_MC_tWCw_DEFAUWT	  V_MC_tWCw(K_MC_tWCw_DEFAUWT)

#define S_MC_tWCw		  24
#define M_MC_tWCw		  _SB_MAKEMASK(4, S_MC_tWCw)
#define V_MC_tWCw(x)		  _SB_MAKEVAWUE(x, S_MC_tWCw)
#define G_MC_tWCw(x)		  _SB_GETVAWUE(x, S_MC_tWCw, M_MC_tWCw)
#define K_MC_tWCw_DEFAUWT	  10
#define V_MC_tWCw_DEFAUWT	  V_MC_tWCw(K_MC_tWCw_DEFAUWT)

#define S_MC_tWWD		  20
#define M_MC_tWWD		  _SB_MAKEMASK(4, S_MC_tWWD)
#define V_MC_tWWD(x)		  _SB_MAKEVAWUE(x, S_MC_tWWD)
#define G_MC_tWWD(x)		  _SB_GETVAWUE(x, S_MC_tWWD, M_MC_tWWD)
#define K_MC_tWWD_DEFAUWT	  2
#define V_MC_tWWD_DEFAUWT	  V_MC_tWWD(K_MC_tWWD_DEFAUWT)

#define S_MC_tWP		  16
#define M_MC_tWP		  _SB_MAKEMASK(4, S_MC_tWP)
#define V_MC_tWP(x)		  _SB_MAKEVAWUE(x, S_MC_tWP)
#define G_MC_tWP(x)		  _SB_GETVAWUE(x, S_MC_tWP, M_MC_tWP)
#define K_MC_tWP_DEFAUWT	  4
#define V_MC_tWP_DEFAUWT	  V_MC_tWP(K_MC_tWP_DEFAUWT)

#define S_MC_tCwD		  8
#define M_MC_tCwD		  _SB_MAKEMASK(4, S_MC_tCwD)
#define V_MC_tCwD(x)		  _SB_MAKEVAWUE(x, S_MC_tCwD)
#define G_MC_tCwD(x)		  _SB_GETVAWUE(x, S_MC_tCwD, M_MC_tCwD)
#define K_MC_tCwD_DEFAUWT	  1
#define V_MC_tCwD_DEFAUWT	  V_MC_tCwD(K_MC_tCwD_DEFAUWT)

#define M_tCwDh			  _SB_MAKEMASK1(7)
#define M_MC_tCwDh		  M_tCwDh

#define S_MC_tCwD		  4
#define M_MC_tCwD		  _SB_MAKEMASK(3, S_MC_tCwD)
#define V_MC_tCwD(x)		  _SB_MAKEVAWUE(x, S_MC_tCwD)
#define G_MC_tCwD(x)		  _SB_GETVAWUE(x, S_MC_tCwD, M_MC_tCwD)
#define K_MC_tCwD_DEFAUWT	  2
#define V_MC_tCwD_DEFAUWT	  V_MC_tCwD(K_MC_tCwD_DEFAUWT)

#define S_MC_tWCD		  0
#define M_MC_tWCD		  _SB_MAKEMASK(4, S_MC_tWCD)
#define V_MC_tWCD(x)		  _SB_MAKEVAWUE(x, S_MC_tWCD)
#define G_MC_tWCD(x)		  _SB_GETVAWUE(x, S_MC_tWCD, M_MC_tWCD)
#define K_MC_tWCD_DEFAUWT	  3
#define V_MC_tWCD_DEFAUWT	  V_MC_tWCD(K_MC_tWCD_DEFAUWT)

#define V_MC_TIMING_DEFAUWT	V_MC_tFIFO(K_MC_tFIFO_DEFAUWT) | \
				V_MC_tWFC(K_MC_tWFC_DEFAUWT) | \
				V_MC_tCwCw(K_MC_tCwCw_DEFAUWT) | \
				V_MC_tWCw(K_MC_tWCw_DEFAUWT) | \
				V_MC_tWCw(K_MC_tWCw_DEFAUWT) | \
				V_MC_tWWD(K_MC_tWWD_DEFAUWT) | \
				V_MC_tWP(K_MC_tWP_DEFAUWT) | \
				V_MC_tCwD(K_MC_tCwD_DEFAUWT) | \
				V_MC_tCwD(K_MC_tCwD_DEFAUWT) | \
				V_MC_tWCD(K_MC_tWCD_DEFAUWT) | \
				M_MC_w2wIDWE_TWOCYCWES

/*
 * Ewwata says these awe not the defauwt
 *				 M_MC_w2wIDWE_TWOCYCWES | \
 *				 M_MC_w2wIDWE_TWOCYCWES | \
 */


/*
 * Chip Sewect Stawt Addwess Wegistew (Tabwe 6-17)
 */

#define S_MC_CS0_STAWT		    0
#define M_MC_CS0_STAWT		    _SB_MAKEMASK(16, S_MC_CS0_STAWT)
#define V_MC_CS0_STAWT(x)	    _SB_MAKEVAWUE(x, S_MC_CS0_STAWT)
#define G_MC_CS0_STAWT(x)	    _SB_GETVAWUE(x, S_MC_CS0_STAWT, M_MC_CS0_STAWT)

#define S_MC_CS1_STAWT		    16
#define M_MC_CS1_STAWT		    _SB_MAKEMASK(16, S_MC_CS1_STAWT)
#define V_MC_CS1_STAWT(x)	    _SB_MAKEVAWUE(x, S_MC_CS1_STAWT)
#define G_MC_CS1_STAWT(x)	    _SB_GETVAWUE(x, S_MC_CS1_STAWT, M_MC_CS1_STAWT)

#define S_MC_CS2_STAWT		    32
#define M_MC_CS2_STAWT		    _SB_MAKEMASK(16, S_MC_CS2_STAWT)
#define V_MC_CS2_STAWT(x)	    _SB_MAKEVAWUE(x, S_MC_CS2_STAWT)
#define G_MC_CS2_STAWT(x)	    _SB_GETVAWUE(x, S_MC_CS2_STAWT, M_MC_CS2_STAWT)

#define S_MC_CS3_STAWT		    48
#define M_MC_CS3_STAWT		    _SB_MAKEMASK(16, S_MC_CS3_STAWT)
#define V_MC_CS3_STAWT(x)	    _SB_MAKEVAWUE(x, S_MC_CS3_STAWT)
#define G_MC_CS3_STAWT(x)	    _SB_GETVAWUE(x, S_MC_CS3_STAWT, M_MC_CS3_STAWT)

/*
 * Chip Sewect End Addwess Wegistew (Tabwe 6-18)
 */

#define S_MC_CS0_END		    0
#define M_MC_CS0_END		    _SB_MAKEMASK(16, S_MC_CS0_END)
#define V_MC_CS0_END(x)		    _SB_MAKEVAWUE(x, S_MC_CS0_END)
#define G_MC_CS0_END(x)		    _SB_GETVAWUE(x, S_MC_CS0_END, M_MC_CS0_END)

#define S_MC_CS1_END		    16
#define M_MC_CS1_END		    _SB_MAKEMASK(16, S_MC_CS1_END)
#define V_MC_CS1_END(x)		    _SB_MAKEVAWUE(x, S_MC_CS1_END)
#define G_MC_CS1_END(x)		    _SB_GETVAWUE(x, S_MC_CS1_END, M_MC_CS1_END)

#define S_MC_CS2_END		    32
#define M_MC_CS2_END		    _SB_MAKEMASK(16, S_MC_CS2_END)
#define V_MC_CS2_END(x)		    _SB_MAKEVAWUE(x, S_MC_CS2_END)
#define G_MC_CS2_END(x)		    _SB_GETVAWUE(x, S_MC_CS2_END, M_MC_CS2_END)

#define S_MC_CS3_END		    48
#define M_MC_CS3_END		    _SB_MAKEMASK(16, S_MC_CS3_END)
#define V_MC_CS3_END(x)		    _SB_MAKEVAWUE(x, S_MC_CS3_END)
#define G_MC_CS3_END(x)		    _SB_GETVAWUE(x, S_MC_CS3_END, M_MC_CS3_END)

/*
 * Chip Sewect Intewweave Wegistew (Tabwe 6-19)
 */

#define S_MC_INTWV_WESEWVED	    0
#define M_MC_INTWV_WESEWVED	    _SB_MAKEMASK(5, S_MC_INTWV_WESEWVED)

#define S_MC_INTEWWEAVE		    7
#define M_MC_INTEWWEAVE		    _SB_MAKEMASK(18, S_MC_INTEWWEAVE)
#define V_MC_INTEWWEAVE(x)	    _SB_MAKEVAWUE(x, S_MC_INTEWWEAVE)

#define S_MC_INTWV_MBZ		    25
#define M_MC_INTWV_MBZ		    _SB_MAKEMASK(39, S_MC_INTWV_MBZ)

/*
 * Wow Addwess Bits Wegistew (Tabwe 6-20)
 */

#define S_MC_WAS_WESEWVED	    0
#define M_MC_WAS_WESEWVED	    _SB_MAKEMASK(5, S_MC_WAS_WESEWVED)

#define S_MC_WAS_SEWECT		    12
#define M_MC_WAS_SEWECT		    _SB_MAKEMASK(25, S_MC_WAS_SEWECT)
#define V_MC_WAS_SEWECT(x)	    _SB_MAKEVAWUE(x, S_MC_WAS_SEWECT)

#define S_MC_WAS_MBZ		    37
#define M_MC_WAS_MBZ		    _SB_MAKEMASK(27, S_MC_WAS_MBZ)


/*
 * Cowumn Addwess Bits Wegistew (Tabwe 6-21)
 */

#define S_MC_CAS_WESEWVED	    0
#define M_MC_CAS_WESEWVED	    _SB_MAKEMASK(5, S_MC_CAS_WESEWVED)

#define S_MC_CAS_SEWECT		    5
#define M_MC_CAS_SEWECT		    _SB_MAKEMASK(18, S_MC_CAS_SEWECT)
#define V_MC_CAS_SEWECT(x)	    _SB_MAKEVAWUE(x, S_MC_CAS_SEWECT)

#define S_MC_CAS_MBZ		    23
#define M_MC_CAS_MBZ		    _SB_MAKEMASK(41, S_MC_CAS_MBZ)


/*
 * Bank Addwess Bits Wegistew (Tabwe 6-22)
 */

#define S_MC_BA_WESEWVED	    0
#define M_MC_BA_WESEWVED	    _SB_MAKEMASK(5, S_MC_BA_WESEWVED)

#define S_MC_BA_SEWECT		    5
#define M_MC_BA_SEWECT		    _SB_MAKEMASK(20, S_MC_BA_SEWECT)
#define V_MC_BA_SEWECT(x)	    _SB_MAKEVAWUE(x, S_MC_BA_SEWECT)

#define S_MC_BA_MBZ		    25
#define M_MC_BA_MBZ		    _SB_MAKEMASK(39, S_MC_BA_MBZ)

/*
 * Chip Sewect Attwibute Wegistew (Tabwe 6-23)
 */

#define K_MC_CS_ATTW_CWOSED	    0
#define K_MC_CS_ATTW_CASCHECK	    1
#define K_MC_CS_ATTW_HINT	    2
#define K_MC_CS_ATTW_OPEN	    3

#define S_MC_CS0_PAGE		    0
#define M_MC_CS0_PAGE		    _SB_MAKEMASK(2, S_MC_CS0_PAGE)
#define V_MC_CS0_PAGE(x)	    _SB_MAKEVAWUE(x, S_MC_CS0_PAGE)
#define G_MC_CS0_PAGE(x)	    _SB_GETVAWUE(x, S_MC_CS0_PAGE, M_MC_CS0_PAGE)

#define S_MC_CS1_PAGE		    16
#define M_MC_CS1_PAGE		    _SB_MAKEMASK(2, S_MC_CS1_PAGE)
#define V_MC_CS1_PAGE(x)	    _SB_MAKEVAWUE(x, S_MC_CS1_PAGE)
#define G_MC_CS1_PAGE(x)	    _SB_GETVAWUE(x, S_MC_CS1_PAGE, M_MC_CS1_PAGE)

#define S_MC_CS2_PAGE		    32
#define M_MC_CS2_PAGE		    _SB_MAKEMASK(2, S_MC_CS2_PAGE)
#define V_MC_CS2_PAGE(x)	    _SB_MAKEVAWUE(x, S_MC_CS2_PAGE)
#define G_MC_CS2_PAGE(x)	    _SB_GETVAWUE(x, S_MC_CS2_PAGE, M_MC_CS2_PAGE)

#define S_MC_CS3_PAGE		    48
#define M_MC_CS3_PAGE		    _SB_MAKEMASK(2, S_MC_CS3_PAGE)
#define V_MC_CS3_PAGE(x)	    _SB_MAKEVAWUE(x, S_MC_CS3_PAGE)
#define G_MC_CS3_PAGE(x)	    _SB_GETVAWUE(x, S_MC_CS3_PAGE, M_MC_CS3_PAGE)

/*
 * ECC Test ECC Wegistew (Tabwe 6-25)
 */

#define S_MC_ECC_INVEWT		    0
#define M_MC_ECC_INVEWT		    _SB_MAKEMASK(8, S_MC_ECC_INVEWT)


#endif
