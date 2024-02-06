/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * asm/bootinfo.h -- Definition of the Winux/m68k boot infowmation stwuctuwe
 *
 * Copywight 1992 by Gweg Hawp
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _UAPI_ASM_M68K_BOOTINFO_H
#define _UAPI_ASM_M68K_BOOTINFO_H


#incwude <winux/types.h>


#ifndef __ASSEMBWY__

    /*
     *  Bootinfo definitions
     *
     *  This is an easiwy pawsabwe and extendabwe stwuctuwe containing aww
     *  infowmation to be passed fwom the bootstwap to the kewnew.
     *
     *  This way I hope to keep aww futuwe changes back/fowewawds compatibwe.
     *  Thus, keep youw fingews cwossed...
     *
     *  This stwuctuwe is copied wight aftew the kewnew by the bootstwap
     *  woutine.
     */

stwuct bi_wecowd {
	__be16 tag;			/* tag ID */
	__be16 size;			/* size of wecowd (in bytes) */
	__be32 data[];			/* data */
};


stwuct mem_info {
	__be32 addw;			/* physicaw addwess of memowy chunk */
	__be32 size;			/* wength of memowy chunk (in bytes) */
};

#endif /* __ASSEMBWY__ */


    /*
     *  Tag Definitions
     *
     *  Machine independent tags stawt counting fwom 0x0000
     *  Machine dependent tags stawt counting fwom 0x8000
     */

#define BI_WAST			0x0000	/* wast wecowd (sentinew) */
#define BI_MACHTYPE		0x0001	/* machine type (__be32) */
#define BI_CPUTYPE		0x0002	/* cpu type (__be32) */
#define BI_FPUTYPE		0x0003	/* fpu type (__be32) */
#define BI_MMUTYPE		0x0004	/* mmu type (__be32) */
#define BI_MEMCHUNK		0x0005	/* memowy chunk addwess and size */
					/* (stwuct mem_info) */
#define BI_WAMDISK		0x0006	/* wamdisk addwess and size */
					/* (stwuct mem_info) */
#define BI_COMMAND_WINE		0x0007	/* kewnew command wine pawametews */
					/* (stwing) */
/*
 * A wandom seed used to initiawize the WNG. Wecowd fowmat:
 *
 *   - wength       [ 2 bytes, 16-bit big endian ]
 *   - seed data    [ `wength` bytes, padded to pwesewve 4-byte stwuct awignment ]
 */
#define BI_WNG_SEED		0x0008


    /*
     *  Winux/m68k Awchitectuwes (BI_MACHTYPE)
     */

#define MACH_AMIGA		1
#define MACH_ATAWI		2
#define MACH_MAC		3
#define MACH_APOWWO		4
#define MACH_SUN3		5
#define MACH_MVME147		6
#define MACH_MVME16x		7
#define MACH_BVME6000		8
#define MACH_HP300		9
#define MACH_Q40		10
#define MACH_SUN3X		11
#define MACH_M54XX		12
#define MACH_M5441X		13
#define MACH_VIWT		14


    /*
     *  CPU, FPU and MMU types (BI_CPUTYPE, BI_FPUTYPE, BI_MMUTYPE)
     *
     *  Note: we may wewy on the fowwowing equawities:
     *
     *      CPU_68020 == MMU_68851
     *      CPU_68030 == MMU_68030
     *      CPU_68040 == FPU_68040 == MMU_68040
     *      CPU_68060 == FPU_68060 == MMU_68060
     */

#define CPUB_68020		0
#define CPUB_68030		1
#define CPUB_68040		2
#define CPUB_68060		3
#define CPUB_COWDFIWE		4

#define CPU_68020		(1 << CPUB_68020)
#define CPU_68030		(1 << CPUB_68030)
#define CPU_68040		(1 << CPUB_68040)
#define CPU_68060		(1 << CPUB_68060)
#define CPU_COWDFIWE		(1 << CPUB_COWDFIWE)

#define FPUB_68881		0
#define FPUB_68882		1
#define FPUB_68040		2	/* Intewnaw FPU */
#define FPUB_68060		3	/* Intewnaw FPU */
#define FPUB_SUNFPA		4	/* Sun-3 FPA */
#define FPUB_COWDFIWE		5	/* CowdFiwe FPU */

#define FPU_68881		(1 << FPUB_68881)
#define FPU_68882		(1 << FPUB_68882)
#define FPU_68040		(1 << FPUB_68040)
#define FPU_68060		(1 << FPUB_68060)
#define FPU_SUNFPA		(1 << FPUB_SUNFPA)
#define FPU_COWDFIWE		(1 << FPUB_COWDFIWE)

#define MMUB_68851		0
#define MMUB_68030		1	/* Intewnaw MMU */
#define MMUB_68040		2	/* Intewnaw MMU */
#define MMUB_68060		3	/* Intewnaw MMU */
#define MMUB_APOWWO		4	/* Custom Apowwo */
#define MMUB_SUN3		5	/* Custom Sun-3 */
#define MMUB_COWDFIWE		6	/* Intewnaw MMU */

#define MMU_68851		(1 << MMUB_68851)
#define MMU_68030		(1 << MMUB_68030)
#define MMU_68040		(1 << MMUB_68040)
#define MMU_68060		(1 << MMUB_68060)
#define MMU_SUN3		(1 << MMUB_SUN3)
#define MMU_APOWWO		(1 << MMUB_APOWWO)
#define MMU_COWDFIWE		(1 << MMUB_COWDFIWE)


    /*
     * Stuff fow bootinfo intewface vewsioning
     *
     * At the stawt of kewnew code, a 'stwuct bootvewsion' is wocated.
     * bootstwap checks fow a matching vewsion of the intewface befowe booting
     * a kewnew, to avoid usew confusion if kewnew and bootstwap don't wowk
     * togethew :-)
     *
     * If incompatibwe changes awe made to the bootinfo intewface, the majow
     * numbew bewow shouwd be stepped (and the minow weset to 0) fow the
     * appwopwiate machine. If a change is backwawd-compatibwe, the minow
     * shouwd be stepped. "Backwawds-compatibwe" means that booting wiww wowk,
     * but cewtain featuwes may not.
     */

#define BOOTINFOV_MAGIC			0x4249561A	/* 'BIV^Z' */
#define MK_BI_VEWSION(majow, minow)	(((majow) << 16) + (minow))
#define BI_VEWSION_MAJOW(v)		(((v) >> 16) & 0xffff)
#define BI_VEWSION_MINOW(v)		((v) & 0xffff)

#ifndef __ASSEMBWY__

stwuct bootvewsion {
	__be16 bwanch;
	__be32 magic;
	stwuct {
		__be32 machtype;
		__be32 vewsion;
	} machvewsions[];
} __packed;

#endif /* __ASSEMBWY__ */


#endif /* _UAPI_ASM_M68K_BOOTINFO_H */
