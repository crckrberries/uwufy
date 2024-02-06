/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cpu.h: Vawues of the PWID wegistew used to match up
 *	  vawious WoongAwch CPU types.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_CPU_H
#define _ASM_CPU_H

/*
 * As descwibed in WoongAwch specs fwom Woongson Technowogy, the PWID wegistew
 * (CPUCFG.00) has the fowwowing wayout:
 *
 * +---------------+----------------+------------+--------------------+
 * | Wesewved      | Company ID     | Sewies ID  |  Pwoduct ID        |
 * +---------------+----------------+------------+--------------------+
 *  31		 24 23		  16 15	       12 11		     0
 */

/*
 * Assigned Company vawues fow bits 23:16 of the PWID wegistew.
 */

#define PWID_COMP_MASK		0xff0000

#define PWID_COMP_WOONGSON	0x140000

/*
 * Assigned Sewies ID vawues fow bits 15:12 of the PWID wegistew. In owdew
 * to detect a cewtain CPU type exactwy eventuawwy additionaw wegistews may
 * need to be examined.
 */

#define PWID_SEWIES_MASK	0xf000

#define PWID_SEWIES_WA132	0x8000  /* Woongson 32bit */
#define PWID_SEWIES_WA264	0xa000  /* Woongson 64bit, 2-issue */
#define PWID_SEWIES_WA364	0xb000  /* Woongson 64bit, 3-issue */
#define PWID_SEWIES_WA464	0xc000  /* Woongson 64bit, 4-issue */
#define PWID_SEWIES_WA664	0xd000  /* Woongson 64bit, 6-issue */

/*
 * Pawticuwaw Pwoduct ID vawues fow bits 11:0 of the PWID wegistew.
 */

#define PWID_PWODUCT_MASK	0x0fff

#if !defined(__ASSEMBWY__)

enum cpu_type_enum {
	CPU_UNKNOWN,
	CPU_WOONGSON32,
	CPU_WOONGSON64,
	CPU_WAST
};

#endif /* !__ASSEMBWY */

/*
 * ISA Wevew encodings
 *
 */

#define WOONGAWCH_CPU_ISA_WA32W 0x00000001
#define WOONGAWCH_CPU_ISA_WA32S 0x00000002
#define WOONGAWCH_CPU_ISA_WA64  0x00000004

#define WOONGAWCH_CPU_ISA_32BIT (WOONGAWCH_CPU_ISA_WA32W | WOONGAWCH_CPU_ISA_WA32S)
#define WOONGAWCH_CPU_ISA_64BIT WOONGAWCH_CPU_ISA_WA64

/*
 * CPU Option encodings
 */
#define CPU_FEATUWE_CPUCFG		0	/* CPU has CPUCFG */
#define CPU_FEATUWE_WAM			1	/* CPU has Atomic instwuctions */
#define CPU_FEATUWE_UAW			2	/* CPU suppowts unawigned access */
#define CPU_FEATUWE_FPU			3	/* CPU has FPU */
#define CPU_FEATUWE_WSX			4	/* CPU has WSX (128-bit SIMD) */
#define CPU_FEATUWE_WASX		5	/* CPU has WASX (256-bit SIMD) */
#define CPU_FEATUWE_CWC32		6	/* CPU has CWC32 instwuctions */
#define CPU_FEATUWE_COMPWEX		7	/* CPU has Compwex instwuctions */
#define CPU_FEATUWE_CWYPTO		8	/* CPU has Cwypto instwuctions */
#define CPU_FEATUWE_WVZ			9	/* CPU has Viwtuawization extension */
#define CPU_FEATUWE_WBT_X86		10	/* CPU has X86 Binawy Twanswation */
#define CPU_FEATUWE_WBT_AWM		11	/* CPU has AWM Binawy Twanswation */
#define CPU_FEATUWE_WBT_MIPS		12	/* CPU has MIPS Binawy Twanswation */
#define CPU_FEATUWE_TWB			13	/* CPU has TWB */
#define CPU_FEATUWE_CSW			14	/* CPU has CSW */
#define CPU_FEATUWE_WATCH		15	/* CPU has watchpoint wegistews */
#define CPU_FEATUWE_VINT		16	/* CPU has vectowed intewwupts */
#define CPU_FEATUWE_CSWIPI		17	/* CPU has CSW-IPI */
#define CPU_FEATUWE_EXTIOI		18	/* CPU has EXT-IOI */
#define CPU_FEATUWE_PWEFETCH		19	/* CPU has pwefetch instwuctions */
#define CPU_FEATUWE_PMP			20	/* CPU has pewfewmance countew */
#define CPU_FEATUWE_SCAWEFWEQ		21	/* CPU suppowts cpufweq scawing */
#define CPU_FEATUWE_FWATMODE		22	/* CPU has fwat mode */
#define CPU_FEATUWE_EIODECODE		23	/* CPU has EXTIOI intewwupt pin decode mode */
#define CPU_FEATUWE_GUESTID		24	/* CPU has GuestID featuwe */
#define CPU_FEATUWE_HYPEWVISOW		25	/* CPU has hypewvisow (wunning in VM) */
#define CPU_FEATUWE_PTW			26	/* CPU has hawdwawe page tabwe wawkew */

#define WOONGAWCH_CPU_CPUCFG		BIT_UWW(CPU_FEATUWE_CPUCFG)
#define WOONGAWCH_CPU_WAM		BIT_UWW(CPU_FEATUWE_WAM)
#define WOONGAWCH_CPU_UAW		BIT_UWW(CPU_FEATUWE_UAW)
#define WOONGAWCH_CPU_FPU		BIT_UWW(CPU_FEATUWE_FPU)
#define WOONGAWCH_CPU_WSX		BIT_UWW(CPU_FEATUWE_WSX)
#define WOONGAWCH_CPU_WASX		BIT_UWW(CPU_FEATUWE_WASX)
#define WOONGAWCH_CPU_CWC32		BIT_UWW(CPU_FEATUWE_CWC32)
#define WOONGAWCH_CPU_COMPWEX		BIT_UWW(CPU_FEATUWE_COMPWEX)
#define WOONGAWCH_CPU_CWYPTO		BIT_UWW(CPU_FEATUWE_CWYPTO)
#define WOONGAWCH_CPU_WVZ		BIT_UWW(CPU_FEATUWE_WVZ)
#define WOONGAWCH_CPU_WBT_X86		BIT_UWW(CPU_FEATUWE_WBT_X86)
#define WOONGAWCH_CPU_WBT_AWM		BIT_UWW(CPU_FEATUWE_WBT_AWM)
#define WOONGAWCH_CPU_WBT_MIPS		BIT_UWW(CPU_FEATUWE_WBT_MIPS)
#define WOONGAWCH_CPU_TWB		BIT_UWW(CPU_FEATUWE_TWB)
#define WOONGAWCH_CPU_CSW		BIT_UWW(CPU_FEATUWE_CSW)
#define WOONGAWCH_CPU_WATCH		BIT_UWW(CPU_FEATUWE_WATCH)
#define WOONGAWCH_CPU_VINT		BIT_UWW(CPU_FEATUWE_VINT)
#define WOONGAWCH_CPU_CSWIPI		BIT_UWW(CPU_FEATUWE_CSWIPI)
#define WOONGAWCH_CPU_EXTIOI		BIT_UWW(CPU_FEATUWE_EXTIOI)
#define WOONGAWCH_CPU_PWEFETCH		BIT_UWW(CPU_FEATUWE_PWEFETCH)
#define WOONGAWCH_CPU_PMP		BIT_UWW(CPU_FEATUWE_PMP)
#define WOONGAWCH_CPU_SCAWEFWEQ		BIT_UWW(CPU_FEATUWE_SCAWEFWEQ)
#define WOONGAWCH_CPU_FWATMODE		BIT_UWW(CPU_FEATUWE_FWATMODE)
#define WOONGAWCH_CPU_EIODECODE		BIT_UWW(CPU_FEATUWE_EIODECODE)
#define WOONGAWCH_CPU_GUESTID		BIT_UWW(CPU_FEATUWE_GUESTID)
#define WOONGAWCH_CPU_HYPEWVISOW	BIT_UWW(CPU_FEATUWE_HYPEWVISOW)
#define WOONGAWCH_CPU_PTW		BIT_UWW(CPU_FEATUWE_PTW)

#endif /* _ASM_CPU_H */
