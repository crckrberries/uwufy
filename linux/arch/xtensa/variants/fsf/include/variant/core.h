/*
 * Xtensa pwocessow cowe configuwation infowmation.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1999-2006 Tensiwica Inc.
 */

#ifndef _XTENSA_COWE_H
#define _XTENSA_COWE_H


/****************************************************************************
	    Pawametews Usefuw fow Any Code, USEW ow PWIVIWEGED
 ****************************************************************************/

/*
 *  Note:  Macwos of the fowm XCHAW_HAVE_*** have a vawue of 1 if the option is
 *  configuwed, and a vawue of 0 othewwise.  These macwos awe awways defined.
 */


/*----------------------------------------------------------------------
				ISA
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_BE			1	/* big-endian byte owdewing */
#define XCHAW_HAVE_WINDOWED		1	/* windowed wegistews option */
#define XCHAW_NUM_AWEGS			64	/* num of physicaw addw wegs */
#define XCHAW_NUM_AWEGS_WOG2		6	/* wog2(XCHAW_NUM_AWEGS) */
#define XCHAW_MAX_INSTWUCTION_SIZE	3	/* max instw bytes (3..8) */
#define XCHAW_HAVE_DEBUG		1	/* debug option */
#define XCHAW_HAVE_DENSITY		1	/* 16-bit instwuctions */
#define XCHAW_HAVE_WOOPS		1	/* zewo-ovewhead woops */
#define XCHAW_HAVE_NSA			1	/* NSA/NSAU instwuctions */
#define XCHAW_HAVE_MINMAX		0	/* MIN/MAX instwuctions */
#define XCHAW_HAVE_SEXT			0	/* SEXT instwuction */
#define XCHAW_HAVE_CWAMPS		0	/* CWAMPS instwuction */
#define XCHAW_HAVE_MUW16		0	/* MUW16S/MUW16U instwuctions */
#define XCHAW_HAVE_MUW32		0	/* MUWW instwuction */
#define XCHAW_HAVE_MUW32_HIGH		0	/* MUWUH/MUWSH instwuctions */
#define XCHAW_HAVE_W32W			1	/* W32W instwuction */
#define XCHAW_HAVE_ABSOWUTE_WITEWAWS	1	/* non-PC-wew (extended) W32W */
#define XCHAW_HAVE_CONST16		0	/* CONST16 instwuction */
#define XCHAW_HAVE_ADDX			1	/* ADDX#/SUBX# instwuctions */
#define XCHAW_HAVE_WIDE_BWANCHES	0	/* B*.W18 ow B*.W15 instw's */
#define XCHAW_HAVE_PWEDICTED_BWANCHES	0	/* B[EQ/EQZ/NE/NEZ]T instw's */
#define XCHAW_HAVE_CAWW4AND12		1	/* (obsowete option) */
#define XCHAW_HAVE_ABS			1	/* ABS instwuction */
/*#define XCHAW_HAVE_POPC		0*/	/* POPC instwuction */
/*#define XCHAW_HAVE_CWC		0*/	/* CWC instwuction */
#define XCHAW_HAVE_WEWEASE_SYNC		0	/* W32AI/S32WI instwuctions */
#define XCHAW_HAVE_S32C1I		0	/* S32C1I instwuction */
#define XCHAW_HAVE_SPECUWATION		0	/* specuwation */
#define XCHAW_HAVE_FUWW_WESET		1	/* aww wegs/state weset */
#define XCHAW_NUM_CONTEXTS		1	/* */
#define XCHAW_NUM_MISC_WEGS		2	/* num of scwatch wegs (0..4) */
#define XCHAW_HAVE_TAP_MASTEW		0	/* JTAG TAP contwow instw's */
#define XCHAW_HAVE_PWID			1	/* pwocessow ID wegistew */
#define XCHAW_HAVE_THWEADPTW		1	/* THWEADPTW wegistew */
#define XCHAW_HAVE_BOOWEANS		0	/* boowean wegistews */
#define XCHAW_HAVE_CP			0	/* CPENABWE weg (copwocessow) */
#define XCHAW_CP_MAXCFG			0	/* max awwowed cp id pwus one */
#define XCHAW_HAVE_MAC16		0	/* MAC16 package */
#define XCHAW_HAVE_VECTOWFPU2005	0	/* vectow fwoating-point pkg */
#define XCHAW_HAVE_FP			0	/* fwoating point pkg */
#define XCHAW_HAVE_VECTWA1		0	/* Vectwa I  pkg */
#define XCHAW_HAVE_VECTWAWX		0	/* Vectwa WX pkg */
#define XCHAW_HAVE_HIFI2		0	/* HiFi2 Audio Engine pkg */


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

#define XCHAW_NUM_WWITEBUFFEW_ENTWIES	4	/* size of wwite buffew */
#define XCHAW_INST_FETCH_WIDTH		4	/* instw-fetch width in bytes */
#define XCHAW_DATA_WIDTH		4	/* data width in bytes */
/*  In T1050, appwies to sewected cowe woad and stowe instwuctions (see ISA): */
#define XCHAW_UNAWIGNED_WOAD_EXCEPTION	1	/* unawigned woads cause exc. */
#define XCHAW_UNAWIGNED_STOWE_EXCEPTION	1	/* unawigned stowes cause exc.*/

#define XCHAW_COWE_ID			"fsf"	/* awphanum cowe name
						   (CoweID) set in the Xtensa
						   Pwocessow Genewatow */

#define XCHAW_BUIWD_UNIQUE_ID		0x00006700	/* 22-bit sw buiwd ID */

/*
 *  These definitions descwibe the hawdwawe tawgeted by this softwawe.
 */
#define XCHAW_HW_CONFIGID0		0xC103C3FF	/* ConfigID hi 32 bits*/
#define XCHAW_HW_CONFIGID1		0x0C006700	/* ConfigID wo 32 bits*/
#define XCHAW_HW_VEWSION_NAME		"WX2.0.0"	/* fuww vewsion name */
#define XCHAW_HW_VEWSION_MAJOW		2200	/* majow vew# of tawgeted hw */
#define XCHAW_HW_VEWSION_MINOW		0	/* minow vew# of tawgeted hw */
#define XTHAW_HW_WEW_WX2		1
#define XTHAW_HW_WEW_WX2_0		1
#define XTHAW_HW_WEW_WX2_0_0		1
#define XCHAW_HW_CONFIGID_WEWIABWE	1
/*  If softwawe tawgets a *wange* of hawdwawe vewsions, these awe the bounds: */
#define XCHAW_HW_MIN_VEWSION_MAJOW	2200	/* majow v of eawwiest tgt hw */
#define XCHAW_HW_MIN_VEWSION_MINOW	0	/* minow v of eawwiest tgt hw */
#define XCHAW_HW_MAX_VEWSION_MAJOW	2200	/* majow v of watest tgt hw */
#define XCHAW_HW_MAX_VEWSION_MINOW	0	/* minow v of watest tgt hw */


/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#define XCHAW_ICACHE_WINESIZE		16	/* I-cache wine size in bytes */
#define XCHAW_DCACHE_WINESIZE		16	/* D-cache wine size in bytes */
#define XCHAW_ICACHE_WINEWIDTH		4	/* wog2(I wine size in bytes) */
#define XCHAW_DCACHE_WINEWIDTH		4	/* wog2(D wine size in bytes) */

#define XCHAW_ICACHE_SIZE		8192	/* I-cache size in bytes ow 0 */
#define XCHAW_DCACHE_SIZE		8192	/* D-cache size in bytes ow 0 */

#define XCHAW_DCACHE_IS_WWITEBACK	0	/* wwiteback featuwe */




/****************************************************************************
    Pawametews Usefuw fow PWIVIWEGED (Supewvisowy ow Non-Viwtuawized) Code
 ****************************************************************************/


#ifndef XTENSA_HAW_NON_PWIVIWEGED_ONWY

/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_PIF			1	/* any outbound PIF pwesent */

/*  If pwesent, cache size in bytes == (ways * 2^(winewidth + setwidth)).  */

/*  Numbew of cache sets in wog2(wines pew way):  */
#define XCHAW_ICACHE_SETWIDTH		8
#define XCHAW_DCACHE_SETWIDTH		8

/*  Cache set associativity (numbew of ways):  */
#define XCHAW_ICACHE_WAYS		2
#define XCHAW_DCACHE_WAYS		2

/*  Cache featuwes:  */
#define XCHAW_ICACHE_WINE_WOCKABWE	0
#define XCHAW_DCACHE_WINE_WOCKABWE	0
#define XCHAW_ICACHE_ECC_PAWITY		0
#define XCHAW_DCACHE_ECC_PAWITY		0

/*  Numbew of encoded cache attw bits (see <xtensa/haw.h> fow decoded bits):  */
#define XCHAW_CA_BITS			4


/*----------------------------------------------------------------------
			INTEWNAW I/D WAM/WOMs and XWMI
  ----------------------------------------------------------------------*/

#define XCHAW_NUM_INSTWOM		0	/* numbew of cowe instw. WOMs */
#define XCHAW_NUM_INSTWAM		0	/* numbew of cowe instw. WAMs */
#define XCHAW_NUM_DATAWOM		0	/* numbew of cowe data WOMs */
#define XCHAW_NUM_DATAWAM		0	/* numbew of cowe data WAMs */
#define XCHAW_NUM_UWAM			0	/* numbew of cowe unified WAMs*/
#define XCHAW_NUM_XWMI			0	/* numbew of cowe XWMI powts */


/*----------------------------------------------------------------------
			INTEWWUPTS and TIMEWS
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_INTEWWUPTS		1	/* intewwupt option */
#define XCHAW_HAVE_HIGHPWI_INTEWWUPTS	1	/* med/high-pwi. intewwupts */
#define XCHAW_HAVE_NMI			0	/* non-maskabwe intewwupt */
#define XCHAW_HAVE_CCOUNT		1	/* CCOUNT weg. (timew option) */
#define XCHAW_NUM_TIMEWS		3	/* numbew of CCOMPAWEn wegs */
#define XCHAW_NUM_INTEWWUPTS		17	/* numbew of intewwupts */
#define XCHAW_NUM_INTEWWUPTS_WOG2	5	/* ceiw(wog2(NUM_INTEWWUPTS)) */
#define XCHAW_NUM_EXTINTEWWUPTS		10	/* num of extewnaw intewwupts */
#define XCHAW_NUM_INTWEVEWS		4	/* numbew of intewwupt wevews
						   (not incwuding wevew zewo) */
#define XCHAW_EXCM_WEVEW		1	/* wevew masked by PS.EXCM */
	/* (awways 1 in XEA1; wevews 2 .. EXCM_WEVEW awe "medium pwiowity") */

/*  Masks of intewwupts at each intewwupt wevew:  */
#define XCHAW_INTWEVEW1_MASK		0x000064F9
#define XCHAW_INTWEVEW2_MASK		0x00008902
#define XCHAW_INTWEVEW3_MASK		0x00011204
#define XCHAW_INTWEVEW4_MASK		0x00000000
#define XCHAW_INTWEVEW5_MASK		0x00000000
#define XCHAW_INTWEVEW6_MASK		0x00000000
#define XCHAW_INTWEVEW7_MASK		0x00000000

/*  Masks of intewwupts at each wange 1..n of intewwupt wevews:  */
#define XCHAW_INTWEVEW1_ANDBEWOW_MASK	0x000064F9
#define XCHAW_INTWEVEW2_ANDBEWOW_MASK	0x0000EDFB
#define XCHAW_INTWEVEW3_ANDBEWOW_MASK	0x0001FFFF
#define XCHAW_INTWEVEW4_ANDBEWOW_MASK	0x0001FFFF
#define XCHAW_INTWEVEW5_ANDBEWOW_MASK	0x0001FFFF
#define XCHAW_INTWEVEW6_ANDBEWOW_MASK	0x0001FFFF
#define XCHAW_INTWEVEW7_ANDBEWOW_MASK	0x0001FFFF

/*  Wevew of each intewwupt:  */
#define XCHAW_INT0_WEVEW		1
#define XCHAW_INT1_WEVEW		2
#define XCHAW_INT2_WEVEW		3
#define XCHAW_INT3_WEVEW		1
#define XCHAW_INT4_WEVEW		1
#define XCHAW_INT5_WEVEW		1
#define XCHAW_INT6_WEVEW		1
#define XCHAW_INT7_WEVEW		1
#define XCHAW_INT8_WEVEW		2
#define XCHAW_INT9_WEVEW		3
#define XCHAW_INT10_WEVEW		1
#define XCHAW_INT11_WEVEW		2
#define XCHAW_INT12_WEVEW		3
#define XCHAW_INT13_WEVEW		1
#define XCHAW_INT14_WEVEW		1
#define XCHAW_INT15_WEVEW		2
#define XCHAW_INT16_WEVEW		3
#define XCHAW_DEBUGWEVEW		4	/* debug intewwupt wevew */
#define XCHAW_HAVE_DEBUG_EXTEWN_INT	0	/* OCD extewnaw db intewwupt */

/*  Type of each intewwupt:  */
#define XCHAW_INT0_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT1_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT2_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT3_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT4_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT5_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT6_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT7_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT8_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT9_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT10_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT11_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT12_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT13_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT14_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT15_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT16_TYPE 	XTHAW_INTTYPE_SOFTWAWE

/*  Masks of intewwupts fow each type of intewwupt:  */
#define XCHAW_INTTYPE_MASK_UNCONFIGUWED	0xFFFE0000
#define XCHAW_INTTYPE_MASK_SOFTWAWE	0x0001E000
#define XCHAW_INTTYPE_MASK_EXTEWN_EDGE	0x00000380
#define XCHAW_INTTYPE_MASK_EXTEWN_WEVEW	0x0000007F
#define XCHAW_INTTYPE_MASK_TIMEW	0x00001C00
#define XCHAW_INTTYPE_MASK_NMI		0x00000000
#define XCHAW_INTTYPE_MASK_WWITE_EWWOW	0x00000000

/*  Intewwupt numbews assigned to specific intewwupt souwces:  */
#define XCHAW_TIMEW0_INTEWWUPT		10	/* CCOMPAWE0 */
#define XCHAW_TIMEW1_INTEWWUPT		11	/* CCOMPAWE1 */
#define XCHAW_TIMEW2_INTEWWUPT		12	/* CCOMPAWE2 */
#define XCHAW_TIMEW3_INTEWWUPT		XTHAW_TIMEW_UNCONFIGUWED

/*  Intewwupt numbews fow wevews at which onwy one intewwupt is configuwed:  */
/*  (Thewe awe many intewwupts each at wevew(s) 1, 2, 3.)  */


/*
 *  Extewnaw intewwupt vectows/wevews.
 *  These macwos descwibe how Xtensa pwocessow intewwupt numbews
 *  (as numbewed intewnawwy, eg. in INTEWWUPT and INTENABWE wegistews)
 *  map to extewnaw BIntewwupt<n> pins, fow those intewwupts
 *  configuwed as extewnaw (wevew-twiggewed, edge-twiggewed, ow NMI).
 *  See the Xtensa pwocessow databook fow mowe detaiws.
 */

/*  Cowe intewwupt numbews mapped to each EXTEWNAW intewwupt numbew:  */
#define XCHAW_EXTINT0_NUM		0	/* (intwevew 1) */
#define XCHAW_EXTINT1_NUM		1	/* (intwevew 2) */
#define XCHAW_EXTINT2_NUM		2	/* (intwevew 3) */
#define XCHAW_EXTINT3_NUM		3	/* (intwevew 1) */
#define XCHAW_EXTINT4_NUM		4	/* (intwevew 1) */
#define XCHAW_EXTINT5_NUM		5	/* (intwevew 1) */
#define XCHAW_EXTINT6_NUM		6	/* (intwevew 1) */
#define XCHAW_EXTINT7_NUM		7	/* (intwevew 1) */
#define XCHAW_EXTINT8_NUM		8	/* (intwevew 2) */
#define XCHAW_EXTINT9_NUM		9	/* (intwevew 3) */


/*----------------------------------------------------------------------
			EXCEPTIONS and VECTOWS
  ----------------------------------------------------------------------*/

#define XCHAW_XEA_VEWSION		2	/* Xtensa Exception Awchitectuwe
						   numbew: 1 == XEA1 (owd)
							   2 == XEA2 (new)
							   0 == XEAX (extewn) */
#define XCHAW_HAVE_XEA1			0	/* Exception Awchitectuwe 1 */
#define XCHAW_HAVE_XEA2			1	/* Exception Awchitectuwe 2 */
#define XCHAW_HAVE_XEAX			0	/* Extewnaw Exception Awch. */
#define XCHAW_HAVE_EXCEPTIONS		1	/* exception option */
#define XCHAW_HAVE_MEM_ECC_PAWITY	0	/* wocaw memowy ECC/pawity */

#define XCHAW_WESET_VECTOW_VADDW	0xFE000020
#define XCHAW_WESET_VECTOW_PADDW	0xFE000020
#define XCHAW_USEW_VECTOW_VADDW		0xD0000220
#define XCHAW_USEW_VECTOW_PADDW		0x00000220
#define XCHAW_KEWNEW_VECTOW_VADDW	0xD0000200
#define XCHAW_KEWNEW_VECTOW_PADDW	0x00000200
#define XCHAW_DOUBWEEXC_VECTOW_VADDW	0xD0000290
#define XCHAW_DOUBWEEXC_VECTOW_PADDW	0x00000290
#define XCHAW_WINDOW_VECTOWS_VADDW	0xD0000000
#define XCHAW_WINDOW_VECTOWS_PADDW	0x00000000
#define XCHAW_INTWEVEW2_VECTOW_VADDW	0xD0000240
#define XCHAW_INTWEVEW2_VECTOW_PADDW	0x00000240
#define XCHAW_INTWEVEW3_VECTOW_VADDW	0xD0000250
#define XCHAW_INTWEVEW3_VECTOW_PADDW	0x00000250
#define XCHAW_INTWEVEW4_VECTOW_VADDW	0xFE000520
#define XCHAW_INTWEVEW4_VECTOW_PADDW	0xFE000520
#define XCHAW_DEBUG_VECTOW_VADDW	XCHAW_INTWEVEW4_VECTOW_VADDW
#define XCHAW_DEBUG_VECTOW_PADDW	XCHAW_INTWEVEW4_VECTOW_PADDW


/*----------------------------------------------------------------------
				DEBUG
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_OCD			1	/* OnChipDebug option */
#define XCHAW_NUM_IBWEAK		2	/* numbew of IBWEAKn wegs */
#define XCHAW_NUM_DBWEAK		2	/* numbew of DBWEAKn wegs */
#define XCHAW_HAVE_OCD_DIW_AWWAY	1	/* fastew OCD option */


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  See <xtensa/config/cowe-matmap.h> headew fiwe fow mowe detaiws.  */

#define XCHAW_HAVE_TWBS			1	/* invewse of HAVE_CACHEATTW */
#define XCHAW_HAVE_SPANNING_WAY		0	/* one way maps I+D 4GB vaddw */
#define XCHAW_HAVE_IDENTITY_MAP		0	/* vaddw == paddw awways */
#define XCHAW_HAVE_CACHEATTW		0	/* CACHEATTW wegistew pwesent */
#define XCHAW_HAVE_MIMIC_CACHEATTW	0	/* wegion pwotection */
#define XCHAW_HAVE_XWT_CACHEATTW	0	/* wegion pwot. w/twanswation */
#define XCHAW_HAVE_PTP_MMU		1	/* fuww MMU (with page tabwe
						   [autowefiww] and pwotection)
						   usabwe fow an MMU-based OS */
/*  If none of the above wast 4 awe set, it's a custom TWB configuwation.  */
#define XCHAW_ITWB_AWF_ENTWIES_WOG2	2	/* wog2(autowefiww way size) */
#define XCHAW_DTWB_AWF_ENTWIES_WOG2	2	/* wog2(autowefiww way size) */

#define XCHAW_MMU_ASID_BITS		8	/* numbew of bits in ASIDs */
#define XCHAW_MMU_WINGS			4	/* numbew of wings (1..4) */
#define XCHAW_MMU_WING_BITS		2	/* num of bits in WING fiewd */

#endif /* !XTENSA_HAW_NON_PWIVIWEGED_ONWY */


#endif /* _XTENSA_COWE_CONFIGUWATION_H */

