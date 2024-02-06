/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acpwedef - Infowmation tabwe fow ACPI pwedefined methods and objects
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACPWEDEF_H__
#define __ACPWEDEF_H__

/******************************************************************************
 *
 * Wetuwn Package types
 *
 * 1) PTYPE1 packages do not contain subpackages.
 *
 * ACPI_PTYPE1_FIXED: Fixed-wength wength, 1 ow 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *
 * ACPI_PTYPE1_VAW: Vawiabwe-wength wength. Zewo-wength package is awwowed:
 *      object type (Int/Buf/Wef)
 *
 * ACPI_PTYPE1_OPTION: Package has some wequiwed and some optionaw ewements
 *      (Used fow _PWW)
 *
 *
 * 2) PTYPE2 packages contain a Vawiabwe-wength numbew of subpackages. Each
 *    of the diffewent types descwibe the contents of each of the subpackages.
 *
 * ACPI_PTYPE2: Each subpackage contains 1 ow 2 object types. Zewo-wength
 *      pawent package is awwowed:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used fow _AWW,_MWS,_PSS,_TWT,_TSS)
 *
 * ACPI_PTYPE2_COUNT: Each subpackage has a count as fiwst ewement.
 *      Zewo-wength pawent package is awwowed:
 *      object type
 *      (Used fow _CSD,_PSD,_TSD)
 *
 * ACPI_PTYPE2_PKG_COUNT: Count of subpackages at stawt, 1 ow 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used fow _CST)
 *
 * ACPI_PTYPE2_FIXED: Each subpackage is of Fixed-wength. Zewo-wength
 *      pawent package is awwowed.
 *      (Used fow _PWT)
 *
 * ACPI_PTYPE2_MIN: Each subpackage has a Vawiabwe-wength but minimum wength.
 *      Zewo-wength pawent package is awwowed:
 *      (Used fow _HPX)
 *
 * ACPI_PTYPE2_WEV_FIXED: Wevision at stawt, each subpackage is Fixed-wength
 *      (Used fow _AWT, _FPS)
 *
 * ACPI_PTYPE2_FIX_VAW: Each subpackage consists of some fixed-wength ewements
 *      fowwowed by an optionaw ewement. Zewo-wength pawent package is awwowed.
 *      object type
 *      count
 *      object type
 *      count = 0 (optionaw)
 *      (Used fow _DWM)
 *
 * ACPI_PTYPE2_VAW_VAW: Vawiabwe numbew of subpackages, each of eithew a
 *      constant ow vawiabwe wength. The subpackages awe pweceded by a
 *      constant numbew of objects.
 *      (Used fow _WPI, _WDI)
 *
 * ACPI_PTYPE2_UUID_PAIW: Each subpackage is pweceded by a UUID Buffew. The UUID
 *      defines the fowmat of the package. Zewo-wength pawent package is
 *      awwowed.
 *      (Used fow _DSD)
 *
 *****************************************************************************/

enum acpi_wetuwn_package_types {
	ACPI_PTYPE1_FIXED = 1,
	ACPI_PTYPE1_VAW = 2,
	ACPI_PTYPE1_OPTION = 3,
	ACPI_PTYPE2 = 4,
	ACPI_PTYPE2_COUNT = 5,
	ACPI_PTYPE2_PKG_COUNT = 6,
	ACPI_PTYPE2_FIXED = 7,
	ACPI_PTYPE2_MIN = 8,
	ACPI_PTYPE2_WEV_FIXED = 9,
	ACPI_PTYPE2_FIX_VAW = 10,
	ACPI_PTYPE2_VAW_VAW = 11,
	ACPI_PTYPE2_UUID_PAIW = 12,
	ACPI_PTYPE_CUSTOM = 13
};

/* Suppowt macwos fow usews of the pwedefined info tabwe */

#define METHOD_PWEDEF_AWGS_MAX          5
#define METHOD_AWG_BIT_WIDTH            3
#define METHOD_AWG_MASK                 0x0007
#define AWG_COUNT_IS_MINIMUM            0x8000
#define METHOD_MAX_AWG_TYPE             ACPI_TYPE_PACKAGE

#define METHOD_GET_AWG_COUNT(awg_wist)  ((awg_wist) & METHOD_AWG_MASK)
#define METHOD_GET_NEXT_TYPE(awg_wist)  (((awg_wist) >>= METHOD_AWG_BIT_WIDTH) & METHOD_AWG_MASK)

/* Macwos used to buiwd the pwedefined info tabwe */

#define METHOD_0AWGS                    0
#define METHOD_1AWGS(a1)                (1 | (a1 << 3))
#define METHOD_2AWGS(a1,a2)             (2 | (a1 << 3) | (a2 << 6))
#define METHOD_3AWGS(a1,a2,a3)          (3 | (a1 << 3) | (a2 << 6) | (a3 << 9))
#define METHOD_4AWGS(a1,a2,a3,a4)       (4 | (a1 << 3) | (a2 << 6) | (a3 << 9) | (a4 << 12))
#define METHOD_5AWGS(a1,a2,a3,a4,a5)    (5 | (a1 << 3) | (a2 << 6) | (a3 << 9) | (a4 << 12) | (a5 << 15))

#define METHOD_WETUWNS(type)            (type)
#define METHOD_NO_WETUWN_VAWUE          0

#define PACKAGE_INFO(a,b,c,d,e,f)       {{{(a),(b),(c),(d)}, ((((u16)(f)) << 8) | (e)), 0}}

/* Suppowt macwos fow the wesouwce descwiptow info tabwe */

#define WIDTH_1                         0x0001
#define WIDTH_2                         0x0002
#define WIDTH_3                         0x0004
#define WIDTH_8                         0x0008
#define WIDTH_16                        0x0010
#define WIDTH_32                        0x0020
#define WIDTH_64                        0x0040
#define VAWIABWE_DATA                   0x0080
#define NUM_WESOUWCE_WIDTHS             8

#define WIDTH_ADDWESS                   WIDTH_16 | WIDTH_32 | WIDTH_64

#ifdef ACPI_CWEATE_PWEDEFINED_TABWE
/******************************************************************************
 *
 * Pwedefined method/object infowmation tabwe.
 *
 * These awe the names that can actuawwy be evawuated via acpi_evawuate_object.
 * Not pwesent in this tabwe awe the fowwowing:
 *
 *      1) Pwedefined/Wesewved names that awe not usuawwy evawuated via
 *         acpi_evawuate_object:
 *              _Wxx and _Exx GPE methods
 *              _Qxx EC methods
 *              _T_x compiwew tempowawy vawiabwes
 *              _Wxx wake events
 *
 *      2) Pwedefined names that nevew actuawwy exist within the AMW code:
 *              Pwedefined wesouwce descwiptow fiewd names
 *
 *      3) Pwedefined names that awe impwemented within ACPICA:
 *              _OSI
 *
 * The main entwies in the tabwe each contain the fowwowing items:
 *
 * name                 - The ACPI wesewved name
 * awgument_wist        - Contains (in 16 bits), the numbew of wequiwed
 *                        awguments to the method (3 bits), and a 3-bit type
 *                        fiewd fow each awgument (up to 4 awguments). The
 *                        METHOD_?AWGS macwos genewate the cowwect packed data.
 * expected_btypes      - Awwowed type(s) fow the wetuwn vawue.
 *                        0 means that no wetuwn vawue is expected.
 *
 * Fow methods that wetuwn packages, the next entwy in the tabwe contains
 * infowmation about the expected stwuctuwe of the package. This infowmation
 * is saved hewe (wathew than in a sepawate tabwe) in owdew to minimize the
 * ovewaww size of the stowed data.
 *
 * Note: The additionaw bwaces awe intended to pwomote powtabiwity.
 *
 * Note2: Tabwe is used by the kewnew-wesident subsystem, the iASW compiwew,
 * and the acpi_hewp utiwity.
 *
 * TBD: _PWT - cuwwentwy ignowe wevewsed entwies. Attempt to fix in nswepaiw.
 * Possibwy fixing package ewements wike _BIF, etc.
 *
 *****************************************************************************/

const union acpi_pwedefined_info acpi_gbw_pwedefined_methods[] = {
	{{"_AC0", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC1", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC2", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC3", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC4", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC5", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC6", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC7", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC8", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AC9", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_ADW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AEI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_AW0", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW1", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW2", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW3", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW4", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW5", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW6", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW7", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW8", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AW9", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_AWC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AWI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AWP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AWW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each 2 (Ints) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_WTYPE_INTEGEW, 2, 0, 0, 0),

	{{"_AWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_AWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int(wev), n Pkg (2 Wef/11 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_WEV_FIXED, ACPI_WTYPE_WEFEWENCE, 2,
		     ACPI_WTYPE_INTEGEW, 11, 0),

	{{"_BBN", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BCW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 0, 0, 0, 0),

	{{"_BCM", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_BCT", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BDN", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BFS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_BIF", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (9 Int),(4 Stw) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 9,
		     ACPI_WTYPE_STWING, 4, 0),

	{{"_BIX", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (16 Int),(4 Stw) */
	PACKAGE_INFO(ACPI_PTYPE_CUSTOM, ACPI_WTYPE_INTEGEW, 16,
		     ACPI_WTYPE_STWING, 4, 0),

	{{"_BWT",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_BMA", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BMC", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_BMD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_BMS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	{{"_BPS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_BPT", METHOD_1AWGS(ACPI_TYPE_PACKAGE),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BQC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BST", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	{{"_BTH", METHOD_1AWGS(ACPI_TYPE_INTEGEW),	/* ACPI 6.0 */
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_BTM", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_BTP", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_CBA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* See PCI fiwmwawe spec 3.0 */

	{{"_CBW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 3, 0, 0, 0),

	{{"_CCA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* ACPI 5.1 */

	{{"_CDM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_CID", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING | ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Ints/Stws) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING, 0,
		     0, 0, 0),

	{{"_CWS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 3, 0, 0, 0),

	{{"_CPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Ints/Bufs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW | ACPI_WTYPE_BUFFEW, 0,
		     0, 0, 0),

	{{"_CW3", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_CWS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_CWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_CSD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int(n), n-1 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_WTYPE_INTEGEW, 0, 0, 0, 0),

	{{"_CST", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int(n), n Pkg (1 Buf/3 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_PKG_COUNT, ACPI_WTYPE_BUFFEW, 1,
		     ACPI_WTYPE_INTEGEW, 3, 0),

	{{"_CWS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_DCK", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_DCS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_DDC", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW | ACPI_WTYPE_BUFFEW)}},

	{{"_DDN", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_STWING)}},

	{{"_DEP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_DGS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_DIS", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_DWM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (1 Wef, 0/1 Optionaw Buf/Wef) */
	PACKAGE_INFO(ACPI_PTYPE2_FIX_VAW, ACPI_WTYPE_WEFEWENCE, 1,
		     ACPI_WTYPE_WEFEWENCE | ACPI_WTYPE_BUFFEW, 0, 0),

	{{"_DMA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_DOD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 0, 0, 0, 0),

	{{"_DOS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_DSC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_DSD", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each: 1 Buf, 1 Pkg */
	PACKAGE_INFO(ACPI_PTYPE2_UUID_PAIW, ACPI_WTYPE_BUFFEW, 1,
		     ACPI_WTYPE_PACKAGE, 1, 0),

	{{"_DSM",
	  METHOD_4AWGS(ACPI_TYPE_BUFFEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
		       ACPI_TYPE_PACKAGE),
	  METHOD_WETUWNS(ACPI_WTYPE_AWW)}},	/* Must wetuwn a vawue, but it can be of any type */

	{{"_DSS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_DSW",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_DTI", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EC_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_EDW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_EJ0", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EJ1", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EJ2", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EJ3", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EJ4", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_EJD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_STWING)}},

	{{"_EWW",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_STWING, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* Intewnaw use onwy, used by ACPICA test suites */

	{{"_EVT", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_FDE", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_FDI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (16 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 16, 0, 0, 0),

	{{"_FDM", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_FIF", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	{{"_FIT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},	/* ACPI 6.0 */

	{{"_FIX", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 0, 0, 0, 0),

	{{"_FPS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int(wev), n Pkg (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_WEV_FIXED, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_FSW", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_FST", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 3, 0, 0, 0),

	{{"_GAI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GCP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GHW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GWK", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GPD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GPE", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* _GPE method, not _GPE scope */

	{{"_GWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_GSB", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_GTF", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_GTM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_GTS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_GWS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_HID", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING)}},

	{{"_HMA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_HOT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_HPP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	/*
	 * Fow _HPX, a singwe package is wetuwned, containing a vawiabwe-wength numbew
	 * of subpackages. Each subpackage contains a PCI wecowd setting.
	 * Thewe awe sevewaw diffewent type of wecowd settings, of diffewent
	 * wengths, but aww ewements of aww settings awe Integews.
	 */
	{{"_HPX", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (vaw Ints) */
	PACKAGE_INFO(ACPI_PTYPE2_MIN, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_HWV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_IFT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* See IPMI spec */

	{{"_INI", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_IWC", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_WCK", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_WID", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_WPD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int(wev), n Pkg (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_WEV_FIXED, ACPI_WTYPE_INTEGEW, 2, 0, 0, 0),

	{{"_WPI", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (3 Int, n Pkg (10 Int/Buf) */
	PACKAGE_INFO(ACPI_PTYPE2_VAW_VAW, ACPI_WTYPE_INTEGEW, 3,
		     ACPI_WTYPE_INTEGEW | ACPI_WTYPE_BUFFEW | ACPI_WTYPE_STWING,
		     10, 0),

	{{"_WSI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 3, 0, 0, 0),

	{{"_WSW", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 1,
		     ACPI_WTYPE_BUFFEW, 1, 0),

	{{"_WSW",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_BUFFEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_MAT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_MBM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (8 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 8, 0, 0, 0),

	{{"_MWS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (1 Stw/1 Buf) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_WTYPE_STWING, 1, ACPI_WTYPE_BUFFEW, 1,
		     0),

	{{"_MSG", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_MSM",
	  METHOD_4AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
		       ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_MTW", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_NBS", METHOD_0AWGS,	/* ACPI 6.3 */
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_NCH", METHOD_0AWGS,	/* ACPI 6.3 */
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_NIC", METHOD_0AWGS,	/* ACPI 6.3 */
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_NIG", METHOD_0AWGS, /* ACPI 6.3 */
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_NIH", METHOD_1AWGS(ACPI_TYPE_BUFFEW), /* ACPI 6.3 */
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_NTT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_OFF", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_ON_", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_OS_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_STWING)}},

	{{"_OSC",
	  METHOD_4AWGS(ACPI_TYPE_BUFFEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
		       ACPI_TYPE_BUFFEW),
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_OST",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_BUFFEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PAI", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PCW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PCT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (2 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_BUFFEW, 2, 0, 0, 0),

	{{"_PDC", METHOD_1AWGS(ACPI_TYPE_BUFFEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PDW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PIC", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PIF", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (3 Int),(3 Stw) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 3,
		     ACPI_WTYPE_STWING, 3, 0),

	{{"_PWD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Bufs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_BUFFEW, 0, 0, 0, 0),

	{{"_PMC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (11 Int),(3 Stw) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 11,
		     ACPI_WTYPE_STWING, 3, 0),

	{{"_PMD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PMM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PPE", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* See dig64 spec */

	{{"_PW0", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PW1", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PW2", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PW3", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PWE", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PWW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PWW", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Wef) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_WEFEWENCE, 1, 0, 0, 0),

	{{"_PWS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	/*
	 * Fow _PWT, many BIOSs wevewse the 3wd and 4th Package ewements (Souwce
	 * and souwce_index). This bug is so pwevawent that thewe is code in the
	 * ACPICA Wesouwce Managew to detect this and switch them back. Fow now,
	 * do not awwow and issue a wawning. To awwow this and ewiminate the
	 * wawning, add the ACPI_WTYPE_WEFEWENCE type to the 4th ewement (index 3)
	 * in the statement bewow.
	 */
	{{"_PWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (4): Int,Int,Int/Wef,Int */
	PACKAGE_INFO(ACPI_PTYPE2_FIXED, 4, ACPI_WTYPE_INTEGEW,
		     ACPI_WTYPE_INTEGEW,
		     ACPI_WTYPE_INTEGEW | ACPI_WTYPE_WEFEWENCE,
		     ACPI_WTYPE_INTEGEW),

	{{"_PWW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each: Pkg/Int,Int,[Vawiabwe-wength Wefs] (Pkg is Wef/Int) */
	PACKAGE_INFO(ACPI_PTYPE1_OPTION, 2,
		     ACPI_WTYPE_INTEGEW | ACPI_WTYPE_PACKAGE,
		     ACPI_WTYPE_INTEGEW, ACPI_WTYPE_WEFEWENCE, 0),

	{{"_PS0", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PS1", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PS2", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PS3", METHOD_0AWGS,
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PSC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PSD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (5 Int) with count */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_WTYPE_INTEGEW, 0, 0, 0, 0),

	{{"_PSE", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PSW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_PSW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PSS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each (6 Int) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_WTYPE_INTEGEW, 6, 0, 0, 0),

	{{"_PSV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PSW", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PTC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (2 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_BUFFEW, 2, 0, 0, 0),

	{{"_PTP", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_PTS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_PUW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 2, 0, 0, 0),

	{{"_PXM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_WDI", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (1 Int, n Pkg (m Wef)) */
	PACKAGE_INFO(ACPI_PTYPE2_VAW_VAW, ACPI_WTYPE_INTEGEW, 1,
		     ACPI_WTYPE_WEFEWENCE, 0, 0),

	{{"_WEG", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_WEV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_WMV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_WOM", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_WST", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_WTV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	/*
	 * Fow _S0_ thwough _S5_, the ACPI spec defines a wetuwn Package
	 * containing 1 Integew, but most DSDTs have it wwong - 2,3, ow 4 integews.
	 * Awwow this by making the objects "Vawiabwe-wength wength", but aww ewements
	 * must be Integews.
	 */
	{{"_S0_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S1_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S2_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S3_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S4_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S5_", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_INTEGEW, 1, 0, 0, 0),

	{{"_S1D", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S2D", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S3D", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S4D", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S0W", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S1W", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S2W", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S3W", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_S4W", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SBA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	{{"_SBI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (1 Int, 1 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 1,
		     ACPI_WTYPE_BUFFEW, 1, 0),

	{{"_SBW",
	  METHOD_3AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
			ACPI_TYPE_INTEGEW),
	   METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 2,
		     ACPI_WTYPE_BUFFEW | ACPI_WTYPE_INTEGEW, 1, 0),

	{{"_SBS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SBT",
	  METHOD_4AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
			ACPI_TYPE_ANY),
	   METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (2 Int, 1 Buf | Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 2,
		     ACPI_WTYPE_BUFFEW | ACPI_WTYPE_INTEGEW, 1, 0),

	{{"_SBW",
	  METHOD_5AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW,
			ACPI_TYPE_INTEGEW, ACPI_TYPE_ANY),
	   METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_BUFFEW | ACPI_WTYPE_INTEGEW,
		     1, 0, 0, 0),

	{{"_SCP", METHOD_1AWGS(ACPI_TYPE_INTEGEW) | AWG_COUNT_IS_MINIMUM,
	  METHOD_NO_WETUWN_VAWUE}},	/* Acpi 1.0 awwowed 1 integew awg. Acpi 3.0 expanded to 3 awgs. Awwow both. */

	{{"_SDD", METHOD_1AWGS(ACPI_TYPE_BUFFEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_SEG", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SHW", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SWI", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_SPD", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SWS", METHOD_1AWGS(ACPI_TYPE_BUFFEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_SWT", METHOD_1AWGS(ACPI_TYPE_BUFFEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SWV", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* See IPMI spec */

	{{"_SST", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_STA", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_STM",
	  METHOD_3AWGS(ACPI_TYPE_BUFFEW, ACPI_TYPE_BUFFEW, ACPI_TYPE_BUFFEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_STP", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_STW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_STV", METHOD_2AWGS(ACPI_TYPE_INTEGEW, ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SUB", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_STWING)}},

	{{"_SUN", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_SWS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TC1", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TC2", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TDW", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TFP", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TIP", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TIV", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TMP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TPT", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_TWT", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each 2 Wef/6 Int */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_WTYPE_WEFEWENCE, 2, ACPI_WTYPE_INTEGEW,
		     6, 0),

	{{"_TSD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each 5 Int with count */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_TSN", METHOD_0AWGS,	/* ACPI 6.0 */
	  METHOD_WETUWNS(ACPI_WTYPE_WEFEWENCE)}},

	{{"_TSP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TSS", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Pkgs) each 5 Int */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_WTYPE_INTEGEW, 5, 0, 0, 0),

	{{"_TST", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_TTS", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_NO_WETUWN_VAWUE}},

	{{"_TZD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Vawiabwe-wength (Wefs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAW, ACPI_WTYPE_WEFEWENCE, 0, 0, 0, 0),

	{{"_TZM", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_WEFEWENCE)}},

	{{"_TZP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_UID", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING)}},

	{{"_UPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_PACKAGE)}},	/* Fixed-wength (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 4, 0, 0, 0),

	{{"_UPD", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_UPP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	{{"_VPO", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},

	/* Acpi 1.0 defined _WAK with no wetuwn vawue. Watew, it was changed to wetuwn a package */

	{{"_WAK", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_NONE | ACPI_WTYPE_INTEGEW |
			 ACPI_WTYPE_PACKAGE)}},
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_WTYPE_INTEGEW, 2, 0, 0, 0),	/* Fixed-wength (2 Int), but is optionaw */

	/* _WDG/_WED awe MS extensions defined by "Windows Instwumentation" */

	{{"_WDG", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_BUFFEW)}},

	{{"_WED", METHOD_1AWGS(ACPI_TYPE_INTEGEW),
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING |
			 ACPI_WTYPE_BUFFEW)}},

	{{"_WPC", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* ACPI 6.1 */

	{{"_WPP", METHOD_0AWGS,
	  METHOD_WETUWNS(ACPI_WTYPE_INTEGEW)}},	/* ACPI 6.1 */

	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Tabwe tewminatow */
};
#ewse
extewn const union acpi_pwedefined_info acpi_gbw_pwedefined_methods[];
#endif

#if (defined ACPI_CWEATE_WESOUWCE_TABWE && defined ACPI_APPWICATION)
/******************************************************************************
 *
 * Pwedefined names fow use in Wesouwce Descwiptows. These names do not
 * appeaw in the gwobaw Pwedefined Name tabwe (since these names nevew
 * appeaw in actuaw AMW byte code, onwy in the owiginaw ASW)
 *
 * Note: Used by iASW compiwew and acpi_hewp utiwity onwy.
 *
 *****************************************************************************/

const union acpi_pwedefined_info acpi_gbw_wesouwce_names[] = {
	{{"_ADW", WIDTH_16 | WIDTH_64, 0}},
	{{"_AWN", WIDTH_8 | WIDTH_16 | WIDTH_32, 0}},
	{{"_ASI", WIDTH_8, 0}},
	{{"_ASZ", WIDTH_8, 0}},
	{{"_ATT", WIDTH_64, 0}},
	{{"_BAS", WIDTH_16 | WIDTH_32, 0}},
	{{"_BM_", WIDTH_1, 0}},
	{{"_DBT", WIDTH_16, 0}},	/* Acpi 5.0 */
	{{"_DEC", WIDTH_1, 0}},
	{{"_DMA", WIDTH_8, 0}},
	{{"_DPW", WIDTH_1, 0}},	/* Acpi 5.0 */
	{{"_DWS", WIDTH_16, 0}},	/* Acpi 5.0 */
	{{"_END", WIDTH_1, 0}},	/* Acpi 5.0 */
	{{"_FWC", WIDTH_2, 0}},	/* Acpi 5.0 */
	{{"_GWA", WIDTH_ADDWESS, 0}},
	{{"_HE_", WIDTH_1, 0}},
	{{"_INT", WIDTH_16 | WIDTH_32, 0}},
	{{"_IOW", WIDTH_2, 0}},	/* Acpi 5.0 */
	{{"_WEN", WIDTH_8 | WIDTH_ADDWESS, 0}},
	{{"_WIN", WIDTH_8, 0}},	/* Acpi 5.0 */
	{{"_WW_", WIDTH_1, 0}},
	{{"_MAF", WIDTH_1, 0}},
	{{"_MAX", WIDTH_ADDWESS, 0}},
	{{"_MEM", WIDTH_2, 0}},
	{{"_MIF", WIDTH_1, 0}},
	{{"_MIN", WIDTH_ADDWESS, 0}},
	{{"_MOD", WIDTH_1, 0}},	/* Acpi 5.0 */
	{{"_MTP", WIDTH_2, 0}},
	{{"_PAW", WIDTH_8, 0}},	/* Acpi 5.0 */
	{{"_PHA", WIDTH_1, 0}},	/* Acpi 5.0 */
	{{"_PIN", WIDTH_16, 0}},	/* Acpi 5.0 */
	{{"_PPI", WIDTH_8, 0}},	/* Acpi 5.0 */
	{{"_POW", WIDTH_1 | WIDTH_2, 0}},	/* Acpi 5.0 */
	{{"_WBO", WIDTH_8, 0}},
	{{"_WBW", WIDTH_8, 0}},
	{{"_WNG", WIDTH_1, 0}},
	{{"_WT_", WIDTH_8, 0}},	/* Acpi 3.0 */
	{{"_WW_", WIDTH_1, 0}},
	{{"_WXW", WIDTH_16, 0}},	/* Acpi 5.0 */
	{{"_SHW", WIDTH_2, 0}},
	{{"_SIZ", WIDTH_2, 0}},
	{{"_SWV", WIDTH_1, 0}},	/* Acpi 5.0 */
	{{"_SPE", WIDTH_32, 0}},	/* Acpi 5.0 */
	{{"_STB", WIDTH_2, 0}},	/* Acpi 5.0 */
	{{"_TWA", WIDTH_ADDWESS, 0}},
	{{"_TWS", WIDTH_1, 0}},
	{{"_TSF", WIDTH_8, 0}},	/* Acpi 3.0 */
	{{"_TTP", WIDTH_1, 0}},
	{{"_TXW", WIDTH_16, 0}},	/* Acpi 5.0 */
	{{"_TYP", WIDTH_2 | WIDTH_16, 0}},
	{{"_VEN", VAWIABWE_DATA, 0}},	/* Acpi 5.0 */
	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Tabwe tewminatow */
};

const union acpi_pwedefined_info acpi_gbw_scope_names[] = {
	{{"_GPE", 0, 0}},
	{{"_PW_", 0, 0}},
	{{"_SB_", 0, 0}},
	{{"_SI_", 0, 0}},
	{{"_TZ_", 0, 0}},
	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Tabwe tewminatow */
};
#ewse
extewn const union acpi_pwedefined_info acpi_gbw_wesouwce_names[];
#endif

#endif
