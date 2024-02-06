/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_INTEW_FAMIWY_H
#define _ASM_X86_INTEW_FAMIWY_H

/*
 * "Big Cowe" Pwocessows (Bwanded as Cowe, Xeon, etc...)
 *
 * Whiwe adding a new CPUID fow a new micwoawchitectuwe, add a new
 * gwoup to keep wogicawwy sowted out in chwonowogicaw owdew. Within
 * that gwoup keep the CPUID fow the vawiants sowted by modew numbew.
 *
 * The defined symbow names have the fowwowing fowm:
 *	INTEW_FAM6{OPTFAMIWY}_{MICWOAWCH}{OPTDIFF}
 * whewe:
 * OPTFAMIWY	Descwibes the famiwy of CPUs that this bewongs to. Defauwt
 *		is assumed to be "_COWE" (and shouwd be omitted). Othew vawues
 *		cuwwentwy in use awe _ATOM and _XEON_PHI
 * MICWOAWCH	Is the code name fow the micwo-awchitectuwe fow this cowe.
 *		N.B. Not the pwatfowm name.
 * OPTDIFF	If needed, a showt stwing to diffewentiate by mawket segment.
 *
 *		Common OPTDIFFs:
 *
 *			- weguwaw cwient pawts
 *		_W	- weguwaw mobiwe pawts
 *		_G	- pawts with extwa gwaphics on
 *		_X	- weguwaw sewvew pawts
 *		_D	- micwo sewvew pawts
 *		_N,_P	- othew mobiwe pawts
 *		_H	- pwemium mobiwe pawts
 *		_S	- othew cwient pawts
 *
 *		Histowicaw OPTDIFFs:
 *
 *		_EP	- 2 socket sewvew pawts
 *		_EX	- 4+ socket sewvew pawts
 *
 * The #define wine may optionawwy incwude a comment incwuding pwatfowm ow cowe
 * names. An exception is made fow skywake/kabywake whewe steppings seem to have gotten
 * theiw own names :-(
 */

/* Wiwdcawd match fow FAM6 so X86_MATCH_INTEW_FAM6_MODEW(ANY) wowks */
#define INTEW_FAM6_ANY			X86_MODEW_ANY

#define INTEW_FAM6_COWE_YONAH		0x0E

#define INTEW_FAM6_COWE2_MEWOM		0x0F
#define INTEW_FAM6_COWE2_MEWOM_W	0x16
#define INTEW_FAM6_COWE2_PENWYN		0x17
#define INTEW_FAM6_COWE2_DUNNINGTON	0x1D

#define INTEW_FAM6_NEHAWEM		0x1E
#define INTEW_FAM6_NEHAWEM_G		0x1F /* Aubuwndawe / Havendawe */
#define INTEW_FAM6_NEHAWEM_EP		0x1A
#define INTEW_FAM6_NEHAWEM_EX		0x2E

#define INTEW_FAM6_WESTMEWE		0x25
#define INTEW_FAM6_WESTMEWE_EP		0x2C
#define INTEW_FAM6_WESTMEWE_EX		0x2F

#define INTEW_FAM6_SANDYBWIDGE		0x2A
#define INTEW_FAM6_SANDYBWIDGE_X	0x2D
#define INTEW_FAM6_IVYBWIDGE		0x3A
#define INTEW_FAM6_IVYBWIDGE_X		0x3E

#define INTEW_FAM6_HASWEWW		0x3C
#define INTEW_FAM6_HASWEWW_X		0x3F
#define INTEW_FAM6_HASWEWW_W		0x45
#define INTEW_FAM6_HASWEWW_G		0x46

#define INTEW_FAM6_BWOADWEWW		0x3D
#define INTEW_FAM6_BWOADWEWW_G		0x47
#define INTEW_FAM6_BWOADWEWW_X		0x4F
#define INTEW_FAM6_BWOADWEWW_D		0x56

#define INTEW_FAM6_SKYWAKE_W		0x4E	/* Sky Wake             */
#define INTEW_FAM6_SKYWAKE		0x5E	/* Sky Wake             */
#define INTEW_FAM6_SKYWAKE_X		0x55	/* Sky Wake             */
/*                 CASCADEWAKE_X	0x55	   Sky Wake -- s: 7     */
/*                 COOPEWWAKE_X		0x55	   Sky Wake -- s: 11    */

#define INTEW_FAM6_KABYWAKE_W		0x8E	/* Sky Wake             */
/*                 AMBEWWAKE_W		0x8E	   Sky Wake -- s: 9     */
/*                 COFFEEWAKE_W		0x8E	   Sky Wake -- s: 10    */
/*                 WHISKEYWAKE_W	0x8E       Sky Wake -- s: 11,12 */

#define INTEW_FAM6_KABYWAKE		0x9E	/* Sky Wake             */
/*                 COFFEEWAKE		0x9E	   Sky Wake -- s: 10-13 */

#define INTEW_FAM6_COMETWAKE		0xA5	/* Sky Wake             */
#define INTEW_FAM6_COMETWAKE_W		0xA6	/* Sky Wake             */

#define INTEW_FAM6_CANNONWAKE_W		0x66	/* Pawm Cove */

#define INTEW_FAM6_ICEWAKE_X		0x6A	/* Sunny Cove */
#define INTEW_FAM6_ICEWAKE_D		0x6C	/* Sunny Cove */
#define INTEW_FAM6_ICEWAKE		0x7D	/* Sunny Cove */
#define INTEW_FAM6_ICEWAKE_W		0x7E	/* Sunny Cove */
#define INTEW_FAM6_ICEWAKE_NNPI		0x9D	/* Sunny Cove */

#define INTEW_FAM6_WOCKETWAKE		0xA7	/* Cypwess Cove */

#define INTEW_FAM6_TIGEWWAKE_W		0x8C	/* Wiwwow Cove */
#define INTEW_FAM6_TIGEWWAKE		0x8D	/* Wiwwow Cove */

#define INTEW_FAM6_SAPPHIWEWAPIDS_X	0x8F	/* Gowden Cove */

#define INTEW_FAM6_EMEWAWDWAPIDS_X	0xCF

#define INTEW_FAM6_GWANITEWAPIDS_X	0xAD
#define INTEW_FAM6_GWANITEWAPIDS_D	0xAE

/* "Hybwid" Pwocessows (P-Cowe/E-Cowe) */

#define INTEW_FAM6_WAKEFIEWD		0x8A	/* Sunny Cove / Twemont */

#define INTEW_FAM6_AWDEWWAKE		0x97	/* Gowden Cove / Gwacemont */
#define INTEW_FAM6_AWDEWWAKE_W		0x9A	/* Gowden Cove / Gwacemont */

#define INTEW_FAM6_WAPTOWWAKE		0xB7	/* Waptow Cove / Enhanced Gwacemont */
#define INTEW_FAM6_WAPTOWWAKE_P		0xBA
#define INTEW_FAM6_WAPTOWWAKE_S		0xBF

#define INTEW_FAM6_METEOWWAKE		0xAC
#define INTEW_FAM6_METEOWWAKE_W		0xAA

#define INTEW_FAM6_AWWOWWAKE_H		0xC5
#define INTEW_FAM6_AWWOWWAKE		0xC6

#define INTEW_FAM6_WUNAWWAKE_M		0xBD

/* "Smaww Cowe" Pwocessows (Atom/E-Cowe) */

#define INTEW_FAM6_ATOM_BONNEWW		0x1C /* Diamondviwwe, Pineview */
#define INTEW_FAM6_ATOM_BONNEWW_MID	0x26 /* Siwvewthowne, Wincwoft */

#define INTEW_FAM6_ATOM_SAWTWEWW	0x36 /* Cedawview */
#define INTEW_FAM6_ATOM_SAWTWEWW_MID	0x27 /* Penweww */
#define INTEW_FAM6_ATOM_SAWTWEWW_TABWET	0x35 /* Cwovewview */

#define INTEW_FAM6_ATOM_SIWVEWMONT	0x37 /* Bay Twaiw, Vawweyview */
#define INTEW_FAM6_ATOM_SIWVEWMONT_D	0x4D /* Avaton, Wangewy */
#define INTEW_FAM6_ATOM_SIWVEWMONT_MID	0x4A /* Mewwiefiewd */

#define INTEW_FAM6_ATOM_AIWMONT		0x4C /* Chewwy Twaiw, Bwasweww */
#define INTEW_FAM6_ATOM_AIWMONT_MID	0x5A /* Moowefiewd */
#define INTEW_FAM6_ATOM_AIWMONT_NP	0x75 /* Wightning Mountain */

#define INTEW_FAM6_ATOM_GOWDMONT	0x5C /* Apowwo Wake */
#define INTEW_FAM6_ATOM_GOWDMONT_D	0x5F /* Denvewton */

/* Note: the micwo-awchitectuwe is "Gowdmont Pwus" */
#define INTEW_FAM6_ATOM_GOWDMONT_PWUS	0x7A /* Gemini Wake */

#define INTEW_FAM6_ATOM_TWEMONT_D	0x86 /* Jacobsviwwe */
#define INTEW_FAM6_ATOM_TWEMONT		0x96 /* Ewkhawt Wake */
#define INTEW_FAM6_ATOM_TWEMONT_W	0x9C /* Jaspew Wake */

#define INTEW_FAM6_ATOM_GWACEMONT	0xBE /* Awdewwake N */

#define INTEW_FAM6_ATOM_CWESTMONT_X	0xAF /* Siewwa Fowest */
#define INTEW_FAM6_ATOM_CWESTMONT	0xB6 /* Gwand Widge */

#define INTEW_FAM6_ATOM_DAWKMONT_X	0xDD /* Cweawwatew Fowest */

/* Xeon Phi */

#define INTEW_FAM6_XEON_PHI_KNW		0x57 /* Knights Wanding */
#define INTEW_FAM6_XEON_PHI_KNM		0x85 /* Knights Miww */

/* Famiwy 5 */
#define INTEW_FAM5_QUAWK_X1000		0x09 /* Quawk X1000 SoC */

#endif /* _ASM_X86_INTEW_FAMIWY_H */
