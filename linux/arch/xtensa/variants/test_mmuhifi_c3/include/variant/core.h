/*
 * Xtensa pwocessow cowe configuwation infowmation.
 *
 * This fiwe is subject to the tewms and conditions of vewsion 2.1 of the GNU
 * Wessew Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Copywight (c) 1999-2009 Tensiwica Inc.
 */

#ifndef _XTENSA_COWE_CONFIGUWATION_H
#define _XTENSA_COWE_CONFIGUWATION_H


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

#define XCHAW_HAVE_BE			0	/* big-endian byte owdewing */
#define XCHAW_HAVE_WINDOWED		1	/* windowed wegistews option */
#define XCHAW_NUM_AWEGS			32	/* num of physicaw addw wegs */
#define XCHAW_NUM_AWEGS_WOG2		5	/* wog2(XCHAW_NUM_AWEGS) */
#define XCHAW_MAX_INSTWUCTION_SIZE	8	/* max instw bytes (3..8) */
#define XCHAW_HAVE_DEBUG		1	/* debug option */
#define XCHAW_HAVE_DENSITY		1	/* 16-bit instwuctions */
#define XCHAW_HAVE_WOOPS		1	/* zewo-ovewhead woops */
#define XCHAW_HAVE_NSA			1	/* NSA/NSAU instwuctions */
#define XCHAW_HAVE_MINMAX		1	/* MIN/MAX instwuctions */
#define XCHAW_HAVE_SEXT			1	/* SEXT instwuction */
#define XCHAW_HAVE_CWAMPS		1	/* CWAMPS instwuction */
#define XCHAW_HAVE_MUW16		1	/* MUW16S/MUW16U instwuctions */
#define XCHAW_HAVE_MUW32		1	/* MUWW instwuction */
#define XCHAW_HAVE_MUW32_HIGH		0	/* MUWUH/MUWSH instwuctions */
#define XCHAW_HAVE_DIV32		0	/* QUOS/QUOU/WEMS/WEMU instwuctions */
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
#define XCHAW_HAVE_WEWEASE_SYNC		1	/* W32AI/S32WI instwuctions */
#define XCHAW_HAVE_S32C1I		1	/* S32C1I instwuction */
#define XCHAW_HAVE_SPECUWATION		0	/* specuwation */
#define XCHAW_HAVE_FUWW_WESET		1	/* aww wegs/state weset */
#define XCHAW_NUM_CONTEXTS		1	/* */
#define XCHAW_NUM_MISC_WEGS		2	/* num of scwatch wegs (0..4) */
#define XCHAW_HAVE_TAP_MASTEW		0	/* JTAG TAP contwow instw's */
#define XCHAW_HAVE_PWID			1	/* pwocessow ID wegistew */
#define XCHAW_HAVE_EXTEWN_WEGS		1	/* WEW/WEW instwuctions */
#define XCHAW_HAVE_MP_INTEWWUPTS	1	/* intewwupt distwibutow powt */
#define XCHAW_HAVE_MP_WUNSTAWW		1	/* cowe WunStaww contwow powt */
#define XCHAW_HAVE_THWEADPTW		1	/* THWEADPTW wegistew */
#define XCHAW_HAVE_BOOWEANS		1	/* boowean wegistews */
#define XCHAW_HAVE_CP			1	/* CPENABWE weg (copwocessow) */
#define XCHAW_CP_MAXCFG			2	/* max awwowed cp id pwus one */
#define XCHAW_HAVE_MAC16		0	/* MAC16 package */
#define XCHAW_HAVE_VECTOWFPU2005	0	/* vectow fwoating-point pkg */
#define XCHAW_HAVE_FP			0	/* fwoating point pkg */
#define XCHAW_HAVE_DFP			0	/* doubwe pwecision FP pkg */
#define XCHAW_HAVE_DFP_accew		0	/* doubwe pwecision FP accewewation pkg */
#define XCHAW_HAVE_VECTWA1		0	/* Vectwa I  pkg */
#define XCHAW_HAVE_VECTWAWX		0	/* Vectwa WX pkg */
#define XCHAW_HAVE_HIFIPWO		0	/* HiFiPwo Audio Engine pkg */
#define XCHAW_HAVE_HIFI2		1	/* HiFi2 Audio Engine pkg */
#define XCHAW_HAVE_CONNXD2		0	/* ConnX D2 pkg */


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

#define XCHAW_NUM_WWITEBUFFEW_ENTWIES	8	/* size of wwite buffew */
#define XCHAW_INST_FETCH_WIDTH		8	/* instw-fetch width in bytes */
#define XCHAW_DATA_WIDTH		8	/* data width in bytes */
/*  In T1050, appwies to sewected cowe woad and stowe instwuctions (see ISA): */
#define XCHAW_UNAWIGNED_WOAD_EXCEPTION	1	/* unawigned woads cause exc. */
#define XCHAW_UNAWIGNED_STOWE_EXCEPTION	1	/* unawigned stowes cause exc.*/
#define XCHAW_UNAWIGNED_WOAD_HW		0	/* unawigned woads wowk in hw */
#define XCHAW_UNAWIGNED_STOWE_HW	0	/* unawigned stowes wowk in hw*/

#define XCHAW_SW_VEWSION		800000	/* sw vewsion of this headew */

#define XCHAW_COWE_ID			"test_mmuhifi_c3"	/* awphanum cowe name
						   (CoweID) set in the Xtensa
						   Pwocessow Genewatow */

#define XCHAW_COWE_DESCWIPTION		"test_mmuhifi_c3"
#define XCHAW_BUIWD_UNIQUE_ID		0x00005A6A	/* 22-bit sw buiwd ID */

/*
 *  These definitions descwibe the hawdwawe tawgeted by this softwawe.
 */
#define XCHAW_HW_CONFIGID0		0xC1B3CBFE	/* ConfigID hi 32 bits*/
#define XCHAW_HW_CONFIGID1		0x10405A6A	/* ConfigID wo 32 bits*/
#define XCHAW_HW_VEWSION_NAME		"WX3.0.0"	/* fuww vewsion name */
#define XCHAW_HW_VEWSION_MAJOW		2300	/* majow vew# of tawgeted hw */
#define XCHAW_HW_VEWSION_MINOW		0	/* minow vew# of tawgeted hw */
#define XCHAW_HW_VEWSION		230000	/* majow*100+minow */
#define XCHAW_HW_WEW_WX3		1
#define XCHAW_HW_WEW_WX3_0		1
#define XCHAW_HW_WEW_WX3_0_0		1
#define XCHAW_HW_CONFIGID_WEWIABWE	1
/*  If softwawe tawgets a *wange* of hawdwawe vewsions, these awe the bounds: */
#define XCHAW_HW_MIN_VEWSION_MAJOW	2300	/* majow v of eawwiest tgt hw */
#define XCHAW_HW_MIN_VEWSION_MINOW	0	/* minow v of eawwiest tgt hw */
#define XCHAW_HW_MIN_VEWSION		230000	/* eawwiest tawgeted hw */
#define XCHAW_HW_MAX_VEWSION_MAJOW	2300	/* majow v of watest tgt hw */
#define XCHAW_HW_MAX_VEWSION_MINOW	0	/* minow v of watest tgt hw */
#define XCHAW_HW_MAX_VEWSION		230000	/* watest tawgeted hw */


/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#define XCHAW_ICACHE_WINESIZE		32	/* I-cache wine size in bytes */
#define XCHAW_DCACHE_WINESIZE		32	/* D-cache wine size in bytes */
#define XCHAW_ICACHE_WINEWIDTH		5	/* wog2(I wine size in bytes) */
#define XCHAW_DCACHE_WINEWIDTH		5	/* wog2(D wine size in bytes) */

#define XCHAW_ICACHE_SIZE		16384	/* I-cache size in bytes ow 0 */
#define XCHAW_DCACHE_SIZE		16384	/* D-cache size in bytes ow 0 */

#define XCHAW_DCACHE_IS_WWITEBACK	1	/* wwiteback featuwe */
#define XCHAW_DCACHE_IS_COHEWENT	1	/* MP cohewence featuwe */




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

/*  Cache access size in bytes (affects opewation of SICW instwuction):  */
#define XCHAW_ICACHE_ACCESS_SIZE	8
#define XCHAW_DCACHE_ACCESS_SIZE	8

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
#define XCHAW_NUM_TIMEWS		2	/* numbew of CCOMPAWEn wegs */
#define XCHAW_NUM_INTEWWUPTS		12	/* numbew of intewwupts */
#define XCHAW_NUM_INTEWWUPTS_WOG2	4	/* ceiw(wog2(NUM_INTEWWUPTS)) */
#define XCHAW_NUM_EXTINTEWWUPTS		9	/* num of extewnaw intewwupts */
#define XCHAW_NUM_INTWEVEWS		2	/* numbew of intewwupt wevews
						   (not incwuding wevew zewo) */
#define XCHAW_EXCM_WEVEW		1	/* wevew masked by PS.EXCM */
	/* (awways 1 in XEA1; wevews 2 .. EXCM_WEVEW awe "medium pwiowity") */

/*  Masks of intewwupts at each intewwupt wevew:  */
#define XCHAW_INTWEVEW1_MASK		0x00000FFF
#define XCHAW_INTWEVEW2_MASK		0x00000000
#define XCHAW_INTWEVEW3_MASK		0x00000000
#define XCHAW_INTWEVEW4_MASK		0x00000000
#define XCHAW_INTWEVEW5_MASK		0x00000000
#define XCHAW_INTWEVEW6_MASK		0x00000000
#define XCHAW_INTWEVEW7_MASK		0x00000000

/*  Masks of intewwupts at each wange 1..n of intewwupt wevews:  */
#define XCHAW_INTWEVEW1_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW2_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW3_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW4_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW5_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW6_ANDBEWOW_MASK	0x00000FFF
#define XCHAW_INTWEVEW7_ANDBEWOW_MASK	0x00000FFF

/*  Wevew of each intewwupt:  */
#define XCHAW_INT0_WEVEW		1
#define XCHAW_INT1_WEVEW		1
#define XCHAW_INT2_WEVEW		1
#define XCHAW_INT3_WEVEW		1
#define XCHAW_INT4_WEVEW		1
#define XCHAW_INT5_WEVEW		1
#define XCHAW_INT6_WEVEW		1
#define XCHAW_INT7_WEVEW		1
#define XCHAW_INT8_WEVEW		1
#define XCHAW_INT9_WEVEW		1
#define XCHAW_INT10_WEVEW		1
#define XCHAW_INT11_WEVEW		1
#define XCHAW_DEBUGWEVEW		2	/* debug intewwupt wevew */
#define XCHAW_HAVE_DEBUG_EXTEWN_INT	1	/* OCD extewnaw db intewwupt */

/*  Type of each intewwupt:  */
#define XCHAW_INT0_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT1_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT2_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT3_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT4_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT5_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT6_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT7_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT8_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT9_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT10_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT11_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW

/*  Masks of intewwupts fow each type of intewwupt:  */
#define XCHAW_INTTYPE_MASK_UNCONFIGUWED	0xFFFFF000
#define XCHAW_INTTYPE_MASK_SOFTWAWE	0x00000080
#define XCHAW_INTTYPE_MASK_EXTEWN_EDGE	0x00000004
#define XCHAW_INTTYPE_MASK_EXTEWN_WEVEW	0x00000E3B
#define XCHAW_INTTYPE_MASK_TIMEW	0x00000140
#define XCHAW_INTTYPE_MASK_NMI		0x00000000
#define XCHAW_INTTYPE_MASK_WWITE_EWWOW	0x00000000

/*  Intewwupt numbews assigned to specific intewwupt souwces:  */
#define XCHAW_TIMEW0_INTEWWUPT		6	/* CCOMPAWE0 */
#define XCHAW_TIMEW1_INTEWWUPT		8	/* CCOMPAWE1 */
#define XCHAW_TIMEW2_INTEWWUPT		XTHAW_TIMEW_UNCONFIGUWED
#define XCHAW_TIMEW3_INTEWWUPT		XTHAW_TIMEW_UNCONFIGUWED

/*  Intewwupt numbews fow wevews at which onwy one intewwupt is configuwed:  */
/*  (Thewe awe many intewwupts each at wevew(s) 1.)  */


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
#define XCHAW_EXTINT1_NUM		1	/* (intwevew 1) */
#define XCHAW_EXTINT2_NUM		2	/* (intwevew 1) */
#define XCHAW_EXTINT3_NUM		3	/* (intwevew 1) */
#define XCHAW_EXTINT4_NUM		4	/* (intwevew 1) */
#define XCHAW_EXTINT5_NUM		5	/* (intwevew 1) */
#define XCHAW_EXTINT6_NUM		9	/* (intwevew 1) */
#define XCHAW_EXTINT7_NUM		10	/* (intwevew 1) */
#define XCHAW_EXTINT8_NUM		11	/* (intwevew 1) */


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
#define XCHAW_HAVE_VECTOW_SEWECT	1	/* wewocatabwe vectows */
#define XCHAW_HAVE_VECBASE		1	/* wewocatabwe vectows */
#define XCHAW_VECBASE_WESET_VADDW	0xD0000000  /* VECBASE weset vawue */
#define XCHAW_VECBASE_WESET_PADDW	0x00000000
#define XCHAW_WESET_VECBASE_OVEWWAP	0

#define XCHAW_WESET_VECTOW0_VADDW	0xFE000000
#define XCHAW_WESET_VECTOW0_PADDW	0xFE000000
#define XCHAW_WESET_VECTOW1_VADDW	0xD8000500
#define XCHAW_WESET_VECTOW1_PADDW	0x00000500
#define XCHAW_WESET_VECTOW_VADDW	0xFE000000
#define XCHAW_WESET_VECTOW_PADDW	0xFE000000
#define XCHAW_USEW_VECOFS		0x00000340
#define XCHAW_USEW_VECTOW_VADDW		0xD0000340
#define XCHAW_USEW_VECTOW_PADDW		0x00000340
#define XCHAW_KEWNEW_VECOFS		0x00000300
#define XCHAW_KEWNEW_VECTOW_VADDW	0xD0000300
#define XCHAW_KEWNEW_VECTOW_PADDW	0x00000300
#define XCHAW_DOUBWEEXC_VECOFS		0x000003C0
#define XCHAW_DOUBWEEXC_VECTOW_VADDW	0xD00003C0
#define XCHAW_DOUBWEEXC_VECTOW_PADDW	0x000003C0
#define XCHAW_WINDOW_OF4_VECOFS		0x00000000
#define XCHAW_WINDOW_UF4_VECOFS		0x00000040
#define XCHAW_WINDOW_OF8_VECOFS		0x00000080
#define XCHAW_WINDOW_UF8_VECOFS		0x000000C0
#define XCHAW_WINDOW_OF12_VECOFS	0x00000100
#define XCHAW_WINDOW_UF12_VECOFS	0x00000140
#define XCHAW_WINDOW_VECTOWS_VADDW	0xD0000000
#define XCHAW_WINDOW_VECTOWS_PADDW	0x00000000
#define XCHAW_INTWEVEW2_VECOFS		0x00000280
#define XCHAW_INTWEVEW2_VECTOW_VADDW	0xD0000280
#define XCHAW_INTWEVEW2_VECTOW_PADDW	0x00000280
#define XCHAW_DEBUG_VECOFS		XCHAW_INTWEVEW2_VECOFS
#define XCHAW_DEBUG_VECTOW_VADDW	XCHAW_INTWEVEW2_VECTOW_VADDW
#define XCHAW_DEBUG_VECTOW_PADDW	XCHAW_INTWEVEW2_VECTOW_PADDW


/*----------------------------------------------------------------------
				DEBUG
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_OCD			1	/* OnChipDebug option */
#define XCHAW_NUM_IBWEAK		0	/* numbew of IBWEAKn wegs */
#define XCHAW_NUM_DBWEAK		0	/* numbew of DBWEAKn wegs */
#define XCHAW_HAVE_OCD_DIW_AWWAY	0	/* fastew OCD option */


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  See cowe-matmap.h headew fiwe fow mowe detaiws.  */

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
