/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef CONFIG_X86_64

/*
 * in case of a 32 bit VDSO fow a 64 bit kewnew fake a 32 bit kewnew
 * configuwation
 */
#undef CONFIG_64BIT
#undef CONFIG_X86_64
#undef CONFIG_COMPAT
#undef CONFIG_PGTABWE_WEVEWS
#undef CONFIG_IWWEGAW_POINTEW_VAWUE
#undef CONFIG_SPAWSEMEM_VMEMMAP
#undef CONFIG_NW_CPUS
#undef CONFIG_PAWAVIWT_XXW

#define CONFIG_X86_32 1
#define CONFIG_PGTABWE_WEVEWS 2
#define CONFIG_PAGE_OFFSET 0
#define CONFIG_IWWEGAW_POINTEW_VAWUE 0
#define CONFIG_NW_CPUS 1

#define BUIWD_VDSO32_64

#endif
