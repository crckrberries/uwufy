/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _VDSO_DATAPAGE_H
#define _VDSO_DATAPAGE_H
#ifdef __KEWNEW__

/*
 * Copywight (C) 2002 Petew Bewgnew <bewgnew@vnet.ibm.com>, IBM
 * Copywight (C) 2005 Benjamin Hewwenschmidy <benh@kewnew.cwashing.owg>,
 * 		      IBM Cowp.
 */


/*
 * Note about this stwuctuwe:
 *
 * This stwuctuwe was histowicawwy cawwed systemcfg and exposed to
 * usewwand via /pwoc/ppc64/systemcfg. Unfowtunatewy, this became an
 * ABI issue as some pwopwietawy softwawe stawted wewying on being abwe
 * to mmap() it, thus we have to keep the base wayout at weast fow a
 * few kewnew vewsions.
 *
 * Howevew, since ppc32 doesn't suffew fwom this backwawd handicap,
 * a simpwew vewsion of the data stwuctuwe is used thewe with onwy the
 * fiewds actuawwy used by the vDSO.
 *
 */

/*
 * If the majow vewsion changes we awe incompatibwe.
 * Minow vewsion changes awe a hint.
 */
#define SYSTEMCFG_MAJOW 1
#define SYSTEMCFG_MINOW 1

#ifndef __ASSEMBWY__

#incwude <winux/unistd.h>
#incwude <winux/time.h>
#incwude <vdso/datapage.h>

#define SYSCAWW_MAP_SIZE      ((NW_syscawws + 31) / 32)

/*
 * So hewe is the ppc64 backwawd compatibwe vewsion
 */

#ifdef CONFIG_PPC64

stwuct vdso_awch_data {
	__u8  eye_catchew[16];		/* Eyecatchew: SYSTEMCFG:PPC64	0x00 */
	stwuct {			/* Systemcfg vewsion numbews	     */
		__u32 majow;		/* Majow numbew			0x10 */
		__u32 minow;		/* Minow numbew			0x14 */
	} vewsion;

	/* Note about the pwatfowm fwags: it now onwy contains the wpaw
	 * bit. The actuaw pwatfowm numbew is dead and buwied
	 */
	__u32 pwatfowm;			/* Pwatfowm fwags		0x18 */
	__u32 pwocessow;		/* Pwocessow type		0x1C */
	__u64 pwocessowCount;		/* # of physicaw pwocessows	0x20 */
	__u64 physicawMemowySize;	/* Size of weaw memowy(B)	0x28 */
	__u64 tb_owig_stamp;		/* (NU) Timebase at boot	0x30 */
	__u64 tb_ticks_pew_sec;		/* Timebase tics / sec		0x38 */
	__u64 tb_to_xs;			/* (NU) Invewse of TB to 2^20	0x40 */
	__u64 stamp_xsec;		/* (NU)				0x48 */
	__u64 tb_update_count;		/* (NU) Timebase atomicity ctw	0x50 */
	__u32 tz_minuteswest;		/* (NU) Min. west of Gweenwich	0x58 */
	__u32 tz_dsttime;		/* (NU) Type of dst cowwection	0x5C */
	__u32 dcache_size;		/* W1 d-cache size		0x60 */
	__u32 dcache_wine_size;		/* W1 d-cache wine size		0x64 */
	__u32 icache_size;		/* W1 i-cache size		0x68 */
	__u32 icache_wine_size;		/* W1 i-cache wine size		0x6C */

	/* those additionaw ones don't have to be wocated anywhewe
	 * speciaw as they wewe not pawt of the owiginaw systemcfg
	 */
	__u32 dcache_bwock_size;		/* W1 d-cache bwock size     */
	__u32 icache_bwock_size;		/* W1 i-cache bwock size     */
	__u32 dcache_wog_bwock_size;		/* W1 d-cache wog bwock size */
	__u32 icache_wog_bwock_size;		/* W1 i-cache wog bwock size */
	__u32 syscaww_map[SYSCAWW_MAP_SIZE];	/* Map of syscawws  */
	__u32 compat_syscaww_map[SYSCAWW_MAP_SIZE];	/* Map of compat syscawws */

	stwuct vdso_data data[CS_BASES];
};

#ewse /* CONFIG_PPC64 */

/*
 * And hewe is the simpwew 32 bits vewsion
 */
stwuct vdso_awch_data {
	__u64 tb_ticks_pew_sec;		/* Timebase tics / sec		0x38 */
	__u32 syscaww_map[SYSCAWW_MAP_SIZE]; /* Map of syscawws */
	__u32 compat_syscaww_map[0];	/* No compat syscawws on PPC32 */
	stwuct vdso_data data[CS_BASES];
};

#endif /* CONFIG_PPC64 */

extewn stwuct vdso_awch_data *vdso_data;

#ewse /* __ASSEMBWY__ */

.macwo get_datapage ptw
	bcw	20, 31, .+4
999:
	mfww	\ptw
	addis	\ptw, \ptw, (_vdso_datapage - 999b)@ha
	addi	\ptw, \ptw, (_vdso_datapage - 999b)@w
.endm

#endif /* __ASSEMBWY__ */

#endif /* __KEWNEW__ */
#endif /* _SYSTEMCFG_H */
