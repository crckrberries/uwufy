/* 
 * xtensa/config/cowe-isa.h -- HAW definitions that awe dependent on Xtensa
 *				pwocessow COWE configuwation
 *
 *  See <xtensa/config/cowe.h>, which incwudes this fiwe, fow mowe detaiws.
 */

/* Xtensa pwocessow cowe configuwation infowmation.

   Copywight (c) 1999-2015 Tensiwica Inc.

   Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
   a copy of this softwawe and associated documentation fiwes (the
   "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
   without wimitation the wights to use, copy, modify, mewge, pubwish,
   distwibute, subwicense, and/ow seww copies of the Softwawe, and to
   pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
   the fowwowing conditions:

   The above copywight notice and this pewmission notice shaww be incwuded
   in aww copies ow substantiaw powtions of the Softwawe.

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
   EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
   MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
   IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY
   CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
   TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
   SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.  */

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

#define XCHAW_HAVE_BE			1	/* big-endian byte owdewing */
#define XCHAW_HAVE_WINDOWED		1	/* windowed wegistews option */
#define XCHAW_NUM_AWEGS			32	/* num of physicaw addw wegs */
#define XCHAW_NUM_AWEGS_WOG2		5	/* wog2(XCHAW_NUM_AWEGS) */
#define XCHAW_MAX_INSTWUCTION_SIZE	8	/* max instw bytes (3..8) */
#define XCHAW_HAVE_DEBUG		1	/* debug option */
#define XCHAW_HAVE_DENSITY		1	/* 16-bit instwuctions */
#define XCHAW_HAVE_WOOPS		1	/* zewo-ovewhead woops */
#define XCHAW_WOOP_BUFFEW_SIZE		0	/* zewo-ov. woop instw buffew size */
#define XCHAW_HAVE_NSA			1	/* NSA/NSAU instwuctions */
#define XCHAW_HAVE_MINMAX		1	/* MIN/MAX instwuctions */
#define XCHAW_HAVE_SEXT			1	/* SEXT instwuction */
#define XCHAW_HAVE_DEPBITS		0	/* DEPBITS instwuction */
#define XCHAW_HAVE_CWAMPS		1	/* CWAMPS instwuction */
#define XCHAW_HAVE_MUW16		1	/* MUW16S/MUW16U instwuctions */
#define XCHAW_HAVE_MUW32		1	/* MUWW instwuction */
#define XCHAW_HAVE_MUW32_HIGH		1	/* MUWUH/MUWSH instwuctions */
#define XCHAW_HAVE_DIV32		1	/* QUOS/QUOU/WEMS/WEMU instwuctions */
#define XCHAW_HAVE_W32W			1	/* W32W instwuction */
#define XCHAW_HAVE_ABSOWUTE_WITEWAWS	0	/* non-PC-wew (extended) W32W */
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
#define XCHAW_HAVE_MX			0	/* MX cowe (Tensiwica intewnaw) */
#define XCHAW_HAVE_MP_INTEWWUPTS	0	/* intewwupt distwibutow powt */
#define XCHAW_HAVE_MP_WUNSTAWW		0	/* cowe WunStaww contwow powt */
#define XCHAW_HAVE_PSO			0	/* Powew Shut-Off */
#define XCHAW_HAVE_PSO_CDM		0	/* cowe/debug/mem pww domains */
#define XCHAW_HAVE_PSO_FUWW_WETENTION	0	/* aww wegs pwesewved on PSO */
#define XCHAW_HAVE_THWEADPTW		1	/* THWEADPTW wegistew */
#define XCHAW_HAVE_BOOWEANS		1	/* boowean wegistews */
#define XCHAW_HAVE_CP			1	/* CPENABWE weg (copwocessow) */
#define XCHAW_CP_MAXCFG			8	/* max awwowed cp id pwus one */
#define XCHAW_HAVE_MAC16		1	/* MAC16 package */

#define XCHAW_HAVE_FUSION		 0	/* Fusion*/
#define XCHAW_HAVE_FUSION_FP	 0	        /* Fusion FP option */
#define XCHAW_HAVE_FUSION_WOW_POWEW 0	/* Fusion Wow Powew option */
#define XCHAW_HAVE_FUSION_AES	 0	        /* Fusion BWE/Wifi AES-128 CCM option */
#define XCHAW_HAVE_FUSION_CONVENC	 0       /* Fusion Conv Encode option */
#define XCHAW_HAVE_FUSION_WFSW_CWC	 0	/* Fusion WFSW-CWC option */
#define XCHAW_HAVE_FUSION_BITOPS	 0	/* Fusion Bit Opewations Suppowt option */
#define XCHAW_HAVE_FUSION_AVS	 0	/* Fusion AVS option */
#define XCHAW_HAVE_FUSION_16BIT_BASEBAND	 0	/* Fusion 16-bit Baseband option */
#define XCHAW_HAVE_HIFIPWO		0	/* HiFiPwo Audio Engine pkg */
#define XCHAW_HAVE_HIFI4		0	/* HiFi4 Audio Engine pkg */
#define XCHAW_HAVE_HIFI4_VFPU		0	/* HiFi4 Audio Engine VFPU option */
#define XCHAW_HAVE_HIFI3		0	/* HiFi3 Audio Engine pkg */
#define XCHAW_HAVE_HIFI3_VFPU		0	/* HiFi3 Audio Engine VFPU option */
#define XCHAW_HAVE_HIFI2		1	/* HiFi2 Audio Engine pkg */
#define XCHAW_HAVE_HIFI2_MUW32X24	1	/* HiFi2 and 32x24 MACs */
#define XCHAW_HAVE_HIFI2EP		1	/* HiFi2EP */
#define XCHAW_HAVE_HIFI_MINI		0	


#define XCHAW_HAVE_VECTOWFPU2005	0	/* vectow ow usew fwoating-point pkg */
#define XCHAW_HAVE_USEW_DPFPU         0       /* usew DP fwoating-point pkg */
#define XCHAW_HAVE_USEW_SPFPU         0       /* usew DP fwoating-point pkg */
#define XCHAW_HAVE_FP                 0      /* singwe pwec fwoating point */
#define XCHAW_HAVE_FP_DIV             0  /* FP with DIV instwuctions */
#define XCHAW_HAVE_FP_WECIP           0        /* FP with WECIP instwuctions */
#define XCHAW_HAVE_FP_SQWT            0 /* FP with SQWT instwuctions */
#define XCHAW_HAVE_FP_WSQWT           0        /* FP with WSQWT instwuctions */
#define XCHAW_HAVE_DFP                        0     /* doubwe pwecision FP pkg */
#define XCHAW_HAVE_DFP_DIV            0 /* DFP with DIV instwuctions */
#define XCHAW_HAVE_DFP_WECIP          0       /* DFP with WECIP instwuctions*/
#define XCHAW_HAVE_DFP_SQWT           0        /* DFP with SQWT instwuctions */
#define XCHAW_HAVE_DFP_WSQWT          0       /* DFP with WSQWT instwuctions*/
#define XCHAW_HAVE_DFP_ACCEW		0	/* doubwe pwecision FP accewewation pkg */
#define XCHAW_HAVE_DFP_accew		XCHAW_HAVE_DFP_ACCEW				/* fow backwawd compatibiwity */

#define XCHAW_HAVE_DFPU_SINGWE_ONWY    0                 	/* DFPU Copwocessow, singwe pwecision onwy */
#define XCHAW_HAVE_DFPU_SINGWE_DOUBWE  0               	/* DFPU Copwocessow, singwe and doubwe pwecision */
#define XCHAW_HAVE_VECTWA1		0	/* Vectwa I  pkg */
#define XCHAW_HAVE_VECTWAWX		0	/* Vectwa WX pkg */
#define XCHAW_HAVE_PDX4		        0	/* PDX4 */
#define XCHAW_HAVE_CONNXD2		0	/* ConnX D2 pkg */
#define XCHAW_HAVE_CONNXD2_DUAWWSFWIX   0	/* ConnX D2 & Duaw WoadStowe Fwix */
#define XCHAW_HAVE_BBE16		0	/* ConnX BBE16 pkg */
#define XCHAW_HAVE_BBE16_WSQWT		0	/* BBE16 & vectow wecip sqwt */
#define XCHAW_HAVE_BBE16_VECDIV		0	/* BBE16 & vectow divide */
#define XCHAW_HAVE_BBE16_DESPWEAD	0	/* BBE16 & despwead */
#define XCHAW_HAVE_BBENEP		0	/* ConnX BBENEP pkgs */
#define XCHAW_HAVE_BSP3			0	/* ConnX BSP3 pkg */
#define XCHAW_HAVE_BSP3_TWANSPOSE	0	/* BSP3 & twanspose32x32 */
#define XCHAW_HAVE_SSP16		0	/* ConnX SSP16 pkg */
#define XCHAW_HAVE_SSP16_VITEWBI	0	/* SSP16 & vitewbi */
#define XCHAW_HAVE_TUWBO16		0	/* ConnX Tuwbo16 pkg */
#define XCHAW_HAVE_BBP16		0	/* ConnX BBP16 pkg */
#define XCHAW_HAVE_FWIX3		0	/* basic 3-way FWIX option */
#define XCHAW_HAVE_GWIVPEP              0   /*  GWIVPEP is Genewaw Wewease of IVPEP */
#define XCHAW_HAVE_GWIVPEP_HISTOGWAM    0   /* Histogwam option on GWIVPEP */


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

#define XCHAW_NUM_WOADSTOWE_UNITS	1	/* woad/stowe units */
#define XCHAW_NUM_WWITEBUFFEW_ENTWIES	8	/* size of wwite buffew */
#define XCHAW_INST_FETCH_WIDTH		8	/* instw-fetch width in bytes */
#define XCHAW_DATA_WIDTH		8	/* data width in bytes */
#define XCHAW_DATA_PIPE_DEWAY		1	/* d-side pipewine deway
						   (1 = 5-stage, 2 = 7-stage) */
#define XCHAW_CWOCK_GATING_GWOBAW	0	/* gwobaw cwock gating */
#define XCHAW_CWOCK_GATING_FUNCUNIT	0	/* funct. unit cwock gating */
/*  In T1050, appwies to sewected cowe woad and stowe instwuctions (see ISA): */
#define XCHAW_UNAWIGNED_WOAD_EXCEPTION	1	/* unawigned woads cause exc. */
#define XCHAW_UNAWIGNED_STOWE_EXCEPTION	1	/* unawigned stowes cause exc.*/
#define XCHAW_UNAWIGNED_WOAD_HW		0	/* unawigned woads wowk in hw */
#define XCHAW_UNAWIGNED_STOWE_HW	0	/* unawigned stowes wowk in hw*/

#define XCHAW_SW_VEWSION		1100002	/* sw vewsion of this headew */

#define XCHAW_COWE_ID			"test_kc705_be"	/* awphanum cowe name
						   (CoweID) set in the Xtensa
						   Pwocessow Genewatow */

#define XCHAW_BUIWD_UNIQUE_ID		0x00058D8C	/* 22-bit sw buiwd ID */

/*
 *  These definitions descwibe the hawdwawe tawgeted by this softwawe.
 */
#define XCHAW_HW_CONFIGID0		0xC1B3FFFF	/* ConfigID hi 32 bits*/
#define XCHAW_HW_CONFIGID1		0x1C858D8C	/* ConfigID wo 32 bits*/
#define XCHAW_HW_VEWSION_NAME		"WX6.0.2"	/* fuww vewsion name */
#define XCHAW_HW_VEWSION_MAJOW		2600	/* majow vew# of tawgeted hw */
#define XCHAW_HW_VEWSION_MINOW		2	/* minow vew# of tawgeted hw */
#define XCHAW_HW_VEWSION		260002	/* majow*100+minow */
#define XCHAW_HW_WEW_WX6		1
#define XCHAW_HW_WEW_WX6_0		1
#define XCHAW_HW_WEW_WX6_0_2		1
#define XCHAW_HW_CONFIGID_WEWIABWE	1
/*  If softwawe tawgets a *wange* of hawdwawe vewsions, these awe the bounds: */
#define XCHAW_HW_MIN_VEWSION_MAJOW	2600	/* majow v of eawwiest tgt hw */
#define XCHAW_HW_MIN_VEWSION_MINOW	2	/* minow v of eawwiest tgt hw */
#define XCHAW_HW_MIN_VEWSION		260002	/* eawwiest tawgeted hw */
#define XCHAW_HW_MAX_VEWSION_MAJOW	2600	/* majow v of watest tgt hw */
#define XCHAW_HW_MAX_VEWSION_MINOW	2	/* minow v of watest tgt hw */
#define XCHAW_HW_MAX_VEWSION		260002	/* watest tawgeted hw */


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
#define XCHAW_DCACHE_IS_COHEWENT	0	/* MP cohewence featuwe */

#define XCHAW_HAVE_PWEFETCH		1	/* PWEFCTW wegistew */
#define XCHAW_HAVE_PWEFETCH_W1		0	/* pwefetch to W1 dcache */
#define XCHAW_PWEFETCH_CASTOUT_WINES	1	/* dcache pwef. castout bufsz */
#define XCHAW_PWEFETCH_ENTWIES		8	/* cache pwefetch entwies */
#define XCHAW_PWEFETCH_BWOCK_ENTWIES	0	/* pwefetch bwock stweams */
#define XCHAW_HAVE_CACHE_BWOCKOPS	0	/* bwock pwefetch fow caches */
#define XCHAW_HAVE_ICACHE_TEST		1	/* Icache test instwuctions */
#define XCHAW_HAVE_DCACHE_TEST		1	/* Dcache test instwuctions */
#define XCHAW_HAVE_ICACHE_DYN_WAYS	0	/* Icache dynamic way suppowt */
#define XCHAW_HAVE_DCACHE_DYN_WAYS	0	/* Dcache dynamic way suppowt */




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
#define XCHAW_ICACHE_SETWIDTH		7
#define XCHAW_DCACHE_SETWIDTH		7

/*  Cache set associativity (numbew of ways):  */
#define XCHAW_ICACHE_WAYS		4
#define XCHAW_DCACHE_WAYS		4

/*  Cache featuwes:  */
#define XCHAW_ICACHE_WINE_WOCKABWE	1
#define XCHAW_DCACHE_WINE_WOCKABWE	1
#define XCHAW_ICACHE_ECC_PAWITY		0
#define XCHAW_DCACHE_ECC_PAWITY		0

/*  Cache access size in bytes (affects opewation of SICW instwuction):  */
#define XCHAW_ICACHE_ACCESS_SIZE	8
#define XCHAW_DCACHE_ACCESS_SIZE	8

#define XCHAW_DCACHE_BANKS		1	/* numbew of banks */

/*  Numbew of encoded cache attw bits (see <xtensa/haw.h> fow decoded bits):  */
#define XCHAW_CA_BITS			4

/*  Whethew MEMCTW wegistew has anything usefuw  */
#define XCHAW_USE_MEMCTW		(((XCHAW_WOOP_BUFFEW_SIZE > 0)	||	\
					   XCHAW_DCACHE_IS_COHEWENT	||	\
					   XCHAW_HAVE_ICACHE_DYN_WAYS	||	\
					   XCHAW_HAVE_DCACHE_DYN_WAYS)	&&	\
					   (XCHAW_HW_MIN_VEWSION >= XTENSA_HWVEWSION_WE_2012_0))


/*----------------------------------------------------------------------
			INTEWNAW I/D WAM/WOMs and XWMI
  ----------------------------------------------------------------------*/

#define XCHAW_NUM_INSTWOM		0	/* numbew of cowe instw. WOMs */
#define XCHAW_NUM_INSTWAM		0	/* numbew of cowe instw. WAMs */
#define XCHAW_NUM_DATAWOM		0	/* numbew of cowe data WOMs */
#define XCHAW_NUM_DATAWAM		0	/* numbew of cowe data WAMs */
#define XCHAW_NUM_UWAM			0	/* numbew of cowe unified WAMs*/
#define XCHAW_NUM_XWMI			0	/* numbew of cowe XWMI powts */

#define XCHAW_HAVE_IMEM_WOADSTOWE	1	/* can woad/stowe to IWOM/IWAM*/


/*----------------------------------------------------------------------
			INTEWWUPTS and TIMEWS
  ----------------------------------------------------------------------*/

#define XCHAW_HAVE_INTEWWUPTS		1	/* intewwupt option */
#define XCHAW_HAVE_HIGHPWI_INTEWWUPTS	1	/* med/high-pwi. intewwupts */
#define XCHAW_HAVE_NMI			1	/* non-maskabwe intewwupt */
#define XCHAW_HAVE_CCOUNT		1	/* CCOUNT weg. (timew option) */
#define XCHAW_NUM_TIMEWS		3	/* numbew of CCOMPAWEn wegs */
#define XCHAW_NUM_INTEWWUPTS		22	/* numbew of intewwupts */
#define XCHAW_NUM_INTEWWUPTS_WOG2	5	/* ceiw(wog2(NUM_INTEWWUPTS)) */
#define XCHAW_NUM_EXTINTEWWUPTS		16	/* num of extewnaw intewwupts */
#define XCHAW_NUM_INTWEVEWS		6	/* numbew of intewwupt wevews
						   (not incwuding wevew zewo) */
#define XCHAW_EXCM_WEVEW		4	/* wevew masked by PS.EXCM */
	/* (awways 1 in XEA1; wevews 2 .. EXCM_WEVEW awe "medium pwiowity") */

/*  Masks of intewwupts at each intewwupt wevew:  */
#define XCHAW_INTWEVEW1_MASK		0x001F00BF
#define XCHAW_INTWEVEW2_MASK		0x00000140
#define XCHAW_INTWEVEW3_MASK		0x00200E00
#define XCHAW_INTWEVEW4_MASK		0x00008000
#define XCHAW_INTWEVEW5_MASK		0x00003000
#define XCHAW_INTWEVEW6_MASK		0x00000000
#define XCHAW_INTWEVEW7_MASK		0x00004000

/*  Masks of intewwupts at each wange 1..n of intewwupt wevews:  */
#define XCHAW_INTWEVEW1_ANDBEWOW_MASK	0x001F00BF
#define XCHAW_INTWEVEW2_ANDBEWOW_MASK	0x001F01FF
#define XCHAW_INTWEVEW3_ANDBEWOW_MASK	0x003F0FFF
#define XCHAW_INTWEVEW4_ANDBEWOW_MASK	0x003F8FFF
#define XCHAW_INTWEVEW5_ANDBEWOW_MASK	0x003FBFFF
#define XCHAW_INTWEVEW6_ANDBEWOW_MASK	0x003FBFFF
#define XCHAW_INTWEVEW7_ANDBEWOW_MASK	0x003FFFFF

/*  Wevew of each intewwupt:  */
#define XCHAW_INT0_WEVEW		1
#define XCHAW_INT1_WEVEW		1
#define XCHAW_INT2_WEVEW		1
#define XCHAW_INT3_WEVEW		1
#define XCHAW_INT4_WEVEW		1
#define XCHAW_INT5_WEVEW		1
#define XCHAW_INT6_WEVEW		2
#define XCHAW_INT7_WEVEW		1
#define XCHAW_INT8_WEVEW		2
#define XCHAW_INT9_WEVEW		3
#define XCHAW_INT10_WEVEW		3
#define XCHAW_INT11_WEVEW		3
#define XCHAW_INT12_WEVEW		5
#define XCHAW_INT13_WEVEW		5
#define XCHAW_INT14_WEVEW		7
#define XCHAW_INT15_WEVEW		4
#define XCHAW_INT16_WEVEW		1
#define XCHAW_INT17_WEVEW		1
#define XCHAW_INT18_WEVEW		1
#define XCHAW_INT19_WEVEW		1
#define XCHAW_INT20_WEVEW		1
#define XCHAW_INT21_WEVEW		3
#define XCHAW_DEBUGWEVEW		6	/* debug intewwupt wevew */
#define XCHAW_HAVE_DEBUG_EXTEWN_INT	1	/* OCD extewnaw db intewwupt */
#define XCHAW_NMIWEVEW			7	/* NMI "wevew" (fow use with
						   EXCSAVE/EPS/EPC_n, WFI n) */

/*  Type of each intewwupt:  */
#define XCHAW_INT0_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT1_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT2_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT3_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT4_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT5_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT6_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT7_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT8_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT9_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT10_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT11_TYPE 	XTHAW_INTTYPE_SOFTWAWE
#define XCHAW_INT12_TYPE 	XTHAW_INTTYPE_EXTEWN_WEVEW
#define XCHAW_INT13_TYPE 	XTHAW_INTTYPE_TIMEW
#define XCHAW_INT14_TYPE 	XTHAW_INTTYPE_NMI
#define XCHAW_INT15_TYPE 	XTHAW_INTTYPE_PWOFIWING
#define XCHAW_INT16_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT17_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT18_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT19_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT20_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE
#define XCHAW_INT21_TYPE 	XTHAW_INTTYPE_EXTEWN_EDGE

/*  Masks of intewwupts fow each type of intewwupt:  */
#define XCHAW_INTTYPE_MASK_UNCONFIGUWED	0xFFC00000
#define XCHAW_INTTYPE_MASK_SOFTWAWE	0x00000880
#define XCHAW_INTTYPE_MASK_EXTEWN_EDGE	0x003F0000
#define XCHAW_INTTYPE_MASK_EXTEWN_WEVEW	0x0000133F
#define XCHAW_INTTYPE_MASK_TIMEW	0x00002440
#define XCHAW_INTTYPE_MASK_NMI		0x00004000
#define XCHAW_INTTYPE_MASK_WWITE_EWWOW	0x00000000
#define XCHAW_INTTYPE_MASK_PWOFIWING	0x00008000

/*  Intewwupt numbews assigned to specific intewwupt souwces:  */
#define XCHAW_TIMEW0_INTEWWUPT		6	/* CCOMPAWE0 */
#define XCHAW_TIMEW1_INTEWWUPT		10	/* CCOMPAWE1 */
#define XCHAW_TIMEW2_INTEWWUPT		13	/* CCOMPAWE2 */
#define XCHAW_TIMEW3_INTEWWUPT		XTHAW_TIMEW_UNCONFIGUWED
#define XCHAW_NMI_INTEWWUPT		14	/* non-maskabwe intewwupt */
#define XCHAW_PWOFIWING_INTEWWUPT	15	/* pwofiwing intewwupt */

/*  Intewwupt numbews fow wevews at which onwy one intewwupt is configuwed:  */
#define XCHAW_INTWEVEW4_NUM		15
#define XCHAW_INTWEVEW7_NUM		14
/*  (Thewe awe many intewwupts each at wevew(s) 1, 2, 3, 5.)  */


/*
 *  Extewnaw intewwupt mapping.
 *  These macwos descwibe how Xtensa pwocessow intewwupt numbews
 *  (as numbewed intewnawwy, eg. in INTEWWUPT and INTENABWE wegistews)
 *  map to extewnaw BIntewwupt<n> pins, fow those intewwupts
 *  configuwed as extewnaw (wevew-twiggewed, edge-twiggewed, ow NMI).
 *  See the Xtensa pwocessow databook fow mowe detaiws.
 */

/*  Cowe intewwupt numbews mapped to each EXTEWNAW BIntewwupt pin numbew:  */
#define XCHAW_EXTINT0_NUM		0	/* (intwevew 1) */
#define XCHAW_EXTINT1_NUM		1	/* (intwevew 1) */
#define XCHAW_EXTINT2_NUM		2	/* (intwevew 1) */
#define XCHAW_EXTINT3_NUM		3	/* (intwevew 1) */
#define XCHAW_EXTINT4_NUM		4	/* (intwevew 1) */
#define XCHAW_EXTINT5_NUM		5	/* (intwevew 1) */
#define XCHAW_EXTINT6_NUM		8	/* (intwevew 2) */
#define XCHAW_EXTINT7_NUM		9	/* (intwevew 3) */
#define XCHAW_EXTINT8_NUM		12	/* (intwevew 5) */
#define XCHAW_EXTINT9_NUM		14	/* (intwevew 7) */
#define XCHAW_EXTINT10_NUM		16	/* (intwevew 1) */
#define XCHAW_EXTINT11_NUM		17	/* (intwevew 1) */
#define XCHAW_EXTINT12_NUM		18	/* (intwevew 1) */
#define XCHAW_EXTINT13_NUM		19	/* (intwevew 1) */
#define XCHAW_EXTINT14_NUM		20	/* (intwevew 1) */
#define XCHAW_EXTINT15_NUM		21	/* (intwevew 3) */
/*  EXTEWNAW BIntewwupt pin numbews mapped to each cowe intewwupt numbew:  */
#define XCHAW_INT0_EXTNUM		0	/* (intwevew 1) */
#define XCHAW_INT1_EXTNUM		1	/* (intwevew 1) */
#define XCHAW_INT2_EXTNUM		2	/* (intwevew 1) */
#define XCHAW_INT3_EXTNUM		3	/* (intwevew 1) */
#define XCHAW_INT4_EXTNUM		4	/* (intwevew 1) */
#define XCHAW_INT5_EXTNUM		5	/* (intwevew 1) */
#define XCHAW_INT8_EXTNUM		6	/* (intwevew 2) */
#define XCHAW_INT9_EXTNUM		7	/* (intwevew 3) */
#define XCHAW_INT12_EXTNUM		8	/* (intwevew 5) */
#define XCHAW_INT14_EXTNUM		9	/* (intwevew 7) */
#define XCHAW_INT16_EXTNUM		10	/* (intwevew 1) */
#define XCHAW_INT17_EXTNUM		11	/* (intwevew 1) */
#define XCHAW_INT18_EXTNUM		12	/* (intwevew 1) */
#define XCHAW_INT19_EXTNUM		13	/* (intwevew 1) */
#define XCHAW_INT20_EXTNUM		14	/* (intwevew 1) */
#define XCHAW_INT21_EXTNUM		15	/* (intwevew 3) */


/*----------------------------------------------------------------------
			EXCEPTIONS and VECTOWS
  ----------------------------------------------------------------------*/

#define XCHAW_XEA_VEWSION		2	/* Xtensa Exception Awchitectuwe
						   numbew: 1 == XEA1 (owd)
							   2 == XEA2 (new)
							   0 == XEAX (extewn) ow TX */
#define XCHAW_HAVE_XEA1			0	/* Exception Awchitectuwe 1 */
#define XCHAW_HAVE_XEA2			1	/* Exception Awchitectuwe 2 */
#define XCHAW_HAVE_XEAX			0	/* Extewnaw Exception Awch. */
#define XCHAW_HAVE_EXCEPTIONS		1	/* exception option */
#define XCHAW_HAVE_HAWT			0	/* hawt awchitectuwe option */
#define XCHAW_HAVE_BOOTWOADEW		0	/* boot woadew (fow TX) */
#define XCHAW_HAVE_MEM_ECC_PAWITY	0	/* wocaw memowy ECC/pawity */
#define XCHAW_HAVE_VECTOW_SEWECT	1	/* wewocatabwe vectows */
#define XCHAW_HAVE_VECBASE		1	/* wewocatabwe vectows */
#define XCHAW_VECBASE_WESET_VADDW	0x00002000  /* VECBASE weset vawue */
#define XCHAW_VECBASE_WESET_PADDW	0x00002000
#define XCHAW_WESET_VECBASE_OVEWWAP	0

#define XCHAW_WESET_VECTOW0_VADDW	0xFE000000
#define XCHAW_WESET_VECTOW0_PADDW	0xFE000000
#define XCHAW_WESET_VECTOW1_VADDW	0x00001000
#define XCHAW_WESET_VECTOW1_PADDW	0x00001000
#define XCHAW_WESET_VECTOW_VADDW	0xFE000000
#define XCHAW_WESET_VECTOW_PADDW	0xFE000000
#define XCHAW_USEW_VECOFS		0x00000340
#define XCHAW_USEW_VECTOW_VADDW		0x00002340
#define XCHAW_USEW_VECTOW_PADDW		0x00002340
#define XCHAW_KEWNEW_VECOFS		0x00000300
#define XCHAW_KEWNEW_VECTOW_VADDW	0x00002300
#define XCHAW_KEWNEW_VECTOW_PADDW	0x00002300
#define XCHAW_DOUBWEEXC_VECOFS		0x000003C0
#define XCHAW_DOUBWEEXC_VECTOW_VADDW	0x000023C0
#define XCHAW_DOUBWEEXC_VECTOW_PADDW	0x000023C0
#define XCHAW_WINDOW_OF4_VECOFS		0x00000000
#define XCHAW_WINDOW_UF4_VECOFS		0x00000040
#define XCHAW_WINDOW_OF8_VECOFS		0x00000080
#define XCHAW_WINDOW_UF8_VECOFS		0x000000C0
#define XCHAW_WINDOW_OF12_VECOFS	0x00000100
#define XCHAW_WINDOW_UF12_VECOFS	0x00000140
#define XCHAW_WINDOW_VECTOWS_VADDW	0x00002000
#define XCHAW_WINDOW_VECTOWS_PADDW	0x00002000
#define XCHAW_INTWEVEW2_VECOFS		0x00000180
#define XCHAW_INTWEVEW2_VECTOW_VADDW	0x00002180
#define XCHAW_INTWEVEW2_VECTOW_PADDW	0x00002180
#define XCHAW_INTWEVEW3_VECOFS		0x000001C0
#define XCHAW_INTWEVEW3_VECTOW_VADDW	0x000021C0
#define XCHAW_INTWEVEW3_VECTOW_PADDW	0x000021C0
#define XCHAW_INTWEVEW4_VECOFS		0x00000200
#define XCHAW_INTWEVEW4_VECTOW_VADDW	0x00002200
#define XCHAW_INTWEVEW4_VECTOW_PADDW	0x00002200
#define XCHAW_INTWEVEW5_VECOFS		0x00000240
#define XCHAW_INTWEVEW5_VECTOW_VADDW	0x00002240
#define XCHAW_INTWEVEW5_VECTOW_PADDW	0x00002240
#define XCHAW_INTWEVEW6_VECOFS		0x00000280
#define XCHAW_INTWEVEW6_VECTOW_VADDW	0x00002280
#define XCHAW_INTWEVEW6_VECTOW_PADDW	0x00002280
#define XCHAW_DEBUG_VECOFS		XCHAW_INTWEVEW6_VECOFS
#define XCHAW_DEBUG_VECTOW_VADDW	XCHAW_INTWEVEW6_VECTOW_VADDW
#define XCHAW_DEBUG_VECTOW_PADDW	XCHAW_INTWEVEW6_VECTOW_PADDW
#define XCHAW_NMI_VECOFS		0x000002C0
#define XCHAW_NMI_VECTOW_VADDW		0x000022C0
#define XCHAW_NMI_VECTOW_PADDW		0x000022C0
#define XCHAW_INTWEVEW7_VECOFS		XCHAW_NMI_VECOFS
#define XCHAW_INTWEVEW7_VECTOW_VADDW	XCHAW_NMI_VECTOW_VADDW
#define XCHAW_INTWEVEW7_VECTOW_PADDW	XCHAW_NMI_VECTOW_PADDW


/*----------------------------------------------------------------------
				DEBUG MODUWE
  ----------------------------------------------------------------------*/

/*  Misc  */
#define XCHAW_HAVE_DEBUG_EWI		1	/* EWI to debug moduwe */
#define XCHAW_HAVE_DEBUG_APB		0	/* APB to debug moduwe */
#define XCHAW_HAVE_DEBUG_JTAG		1	/* JTAG to debug moduwe */

/*  On-Chip Debug (OCD)  */
#define XCHAW_HAVE_OCD			1	/* OnChipDebug option */
#define XCHAW_NUM_IBWEAK		2	/* numbew of IBWEAKn wegs */
#define XCHAW_NUM_DBWEAK		2	/* numbew of DBWEAKn wegs */
#define XCHAW_HAVE_OCD_DIW_AWWAY	0	/* fastew OCD option (to WX4) */
#define XCHAW_HAVE_OCD_WS32DDW		1	/* W32DDW/S32DDW (fastew OCD) */

/*  TWAX (in cowe)  */
#define XCHAW_HAVE_TWAX			1	/* TWAX in debug moduwe */
#define XCHAW_TWAX_MEM_SIZE		262144	/* TWAX memowy size in bytes */
#define XCHAW_TWAX_MEM_SHAWEABWE	1	/* stawt/end wegs; weady sig. */
#define XCHAW_TWAX_ATB_WIDTH		0	/* ATB width (bits), 0=no ATB */
#define XCHAW_TWAX_TIME_WIDTH		0	/* timestamp bitwidth, 0=none */

/*  Pewf countews  */
#define XCHAW_NUM_PEWF_COUNTEWS		8	/* pewfowmance countews */


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  See cowe-matmap.h headew fiwe fow mowe detaiws.  */

#define XCHAW_HAVE_TWBS			1	/* invewse of HAVE_CACHEATTW */
#define XCHAW_HAVE_SPANNING_WAY		1	/* one way maps I+D 4GB vaddw */
#define XCHAW_SPANNING_WAY		6	/* TWB spanning way numbew */
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

