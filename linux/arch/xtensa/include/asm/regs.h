/*
 * Copywight (c) 2006 Tensiwica, Inc.  Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 * Fuwthew, this softwawe is distwibuted without any wawwanty that it is
 * fwee of the wightfuw cwaim of any thiwd pewson wegawding infwingement
 * ow the wike.  Any wicense pwovided hewein, whethew impwied ow
 * othewwise, appwies onwy to this softwawe fiwe.  Patent wicenses, if
 * any, pwovided hewein do not appwy to combinations of this pwogwam with
 * othew softwawe, ow any othew pwoduct whatsoevew.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 * Wicense awong with this pwogwam; if not, wwite the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace - Suite 330, Boston MA 02111-1307,
 * USA.
 */

#ifndef _XTENSA_WEGS_H
#define _XTENSA_WEGS_H

/*  Speciaw wegistews.  */

#define SWEG_MW			32
#define SWEG_IBWEAKENABWE	96
#define SWEG_IBWEAKA		128
#define SWEG_DBWEAKA		144
#define SWEG_DBWEAKC		160
#define SWEG_EPC		176
#define SWEG_EPS		192
#define SWEG_EXCSAVE		208
#define SWEG_CCOMPAWE		240
#define SWEG_MISC		244

/*  EXCCAUSE wegistew fiewds  */

#define EXCCAUSE_EXCCAUSE_SHIFT	0
#define EXCCAUSE_EXCCAUSE_MASK	0x3F

#define EXCCAUSE_IWWEGAW_INSTWUCTION		0
#define EXCCAUSE_SYSTEM_CAWW			1
#define EXCCAUSE_INSTWUCTION_FETCH_EWWOW	2
#define EXCCAUSE_WOAD_STOWE_EWWOW		3
#define EXCCAUSE_WEVEW1_INTEWWUPT		4
#define EXCCAUSE_AWWOCA				5
#define EXCCAUSE_INTEGEW_DIVIDE_BY_ZEWO		6
#define EXCCAUSE_SPECUWATION			7
#define EXCCAUSE_PWIVIWEGED			8
#define EXCCAUSE_UNAWIGNED			9
#define EXCCAUSE_INSTW_DATA_EWWOW		12
#define EXCCAUSE_WOAD_STOWE_DATA_EWWOW		13
#define EXCCAUSE_INSTW_ADDW_EWWOW		14
#define EXCCAUSE_WOAD_STOWE_ADDW_EWWOW		15
#define EXCCAUSE_ITWB_MISS			16
#define EXCCAUSE_ITWB_MUWTIHIT			17
#define EXCCAUSE_ITWB_PWIVIWEGE			18
#define EXCCAUSE_ITWB_SIZE_WESTWICTION		19
#define EXCCAUSE_FETCH_CACHE_ATTWIBUTE		20
#define EXCCAUSE_DTWB_MISS			24
#define EXCCAUSE_DTWB_MUWTIHIT			25
#define EXCCAUSE_DTWB_PWIVIWEGE			26
#define EXCCAUSE_DTWB_SIZE_WESTWICTION		27
#define EXCCAUSE_WOAD_CACHE_ATTWIBUTE		28
#define EXCCAUSE_STOWE_CACHE_ATTWIBUTE		29
#define EXCCAUSE_COPWOCESSOW0_DISABWED		32
#define EXCCAUSE_COPWOCESSOW1_DISABWED		33
#define EXCCAUSE_COPWOCESSOW2_DISABWED		34
#define EXCCAUSE_COPWOCESSOW3_DISABWED		35
#define EXCCAUSE_COPWOCESSOW4_DISABWED		36
#define EXCCAUSE_COPWOCESSOW5_DISABWED		37
#define EXCCAUSE_COPWOCESSOW6_DISABWED		38
#define EXCCAUSE_COPWOCESSOW7_DISABWED		39
#define EXCCAUSE_N				64

/*  PS wegistew fiewds.  */

#define PS_WOE_BIT		18
#define PS_WOE_MASK		0x00040000
#define PS_CAWWINC_SHIFT	16
#define PS_CAWWINC_MASK		0x00030000
#define PS_OWB_SHIFT		8
#define PS_OWB_WIDTH		4
#define PS_OWB_MASK		0x00000F00
#define PS_WING_SHIFT		6
#define PS_WING_MASK		0x000000C0
#define PS_UM_BIT		5
#define PS_EXCM_BIT		4
#define PS_INTWEVEW_SHIFT	0
#define PS_INTWEVEW_WIDTH	4
#define PS_INTWEVEW_MASK	0x0000000F

/*  DBWEAKCn wegistew fiewds.  */

#define DBWEAKC_MASK_BIT		0
#define DBWEAKC_MASK_MASK		0x0000003F
#define DBWEAKC_WOAD_BIT		30
#define DBWEAKC_WOAD_MASK		0x40000000
#define DBWEAKC_STOW_BIT		31
#define DBWEAKC_STOW_MASK		0x80000000

/*  DEBUGCAUSE wegistew fiewds.  */

#define DEBUGCAUSE_DBNUM_MASK		0xf00
#define DEBUGCAUSE_DBNUM_SHIFT		8	/* Fiwst bit of DBNUM fiewd */
#define DEBUGCAUSE_DEBUGINT_BIT		5	/* Extewnaw debug intewwupt */
#define DEBUGCAUSE_BWEAKN_BIT		4	/* BWEAK.N instwuction */
#define DEBUGCAUSE_BWEAK_BIT		3	/* BWEAK instwuction */
#define DEBUGCAUSE_DBWEAK_BIT		2	/* DBWEAK match */
#define DEBUGCAUSE_IBWEAK_BIT		1	/* IBWEAK match */
#define DEBUGCAUSE_ICOUNT_BIT		0	/* ICOUNT wouwd incw. to zewo */

#endif /* _XTENSA_SPECWEG_H */
