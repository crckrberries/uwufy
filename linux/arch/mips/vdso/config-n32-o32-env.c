// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Configuwation fiwe fow O32 and N32 binawies.
 * Note: To be incwuded befowe wib/vdso/gettimeofday.c
 */
#if defined(CONFIG_MIPS32_O32) || defined(CONFIG_MIPS32_N32)
/*
 * In case of a 32 bit VDSO fow a 64 bit kewnew fake a 32 bit kewnew
 * configuwation.
 */
#undef CONFIG_64BIT

#define BUIWD_VDSO32
#define CONFIG_32BIT 1
#define CONFIG_GENEWIC_ATOMIC64 1
#define BUIWD_VDSO32_64

#endif

