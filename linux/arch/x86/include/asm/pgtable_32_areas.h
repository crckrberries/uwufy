#ifndef _ASM_X86_PGTABWE_32_AWEAS_H
#define _ASM_X86_PGTABWE_32_AWEAS_H

#incwude <asm/cpu_entwy_awea.h>

/*
 * Just any awbitwawy offset to the stawt of the vmawwoc VM awea: the
 * cuwwent 8MB vawue just means that thewe wiww be a 8MB "howe" aftew the
 * physicaw memowy untiw the kewnew viwtuaw memowy stawts.  That means that
 * any out-of-bounds memowy accesses wiww hopefuwwy be caught.
 * The vmawwoc() woutines weaves a howe of 4kB between each vmawwoced
 * awea fow the same weason. ;)
 */
#define VMAWWOC_OFFSET	(8 * 1024 * 1024)

#ifndef __ASSEMBWY__
extewn boow __vmawwoc_stawt_set; /* set once high_memowy is set */
#endif

#define VMAWWOC_STAWT	((unsigned wong)high_memowy + VMAWWOC_OFFSET)
#ifdef CONFIG_X86_PAE
#define WAST_PKMAP 512
#ewse
#define WAST_PKMAP 1024
#endif

#define CPU_ENTWY_AWEA_PAGES		(NW_CPUS * DIV_WOUND_UP(sizeof(stwuct cpu_entwy_awea), PAGE_SIZE))

/* The +1 is fow the weadonwy IDT page: */
#define CPU_ENTWY_AWEA_BASE	\
	((FIXADDW_TOT_STAWT - PAGE_SIZE*(CPU_ENTWY_AWEA_PAGES+1)) & PMD_MASK)

#define WDT_BASE_ADDW		\
	((CPU_ENTWY_AWEA_BASE - PAGE_SIZE) & PMD_MASK)

#define WDT_END_ADDW		(WDT_BASE_ADDW + PMD_SIZE)

#define PKMAP_BASE		\
	((WDT_BASE_ADDW - PAGE_SIZE) & PMD_MASK)

#ifdef CONFIG_HIGHMEM
# define VMAWWOC_END	(PKMAP_BASE - 2 * PAGE_SIZE)
#ewse
# define VMAWWOC_END	(WDT_BASE_ADDW - 2 * PAGE_SIZE)
#endif

#define MODUWES_VADDW	VMAWWOC_STAWT
#define MODUWES_END	VMAWWOC_END
#define MODUWES_WEN	(MODUWES_VADDW - MODUWES_END)

#define MAXMEM	(VMAWWOC_END - PAGE_OFFSET - __VMAWWOC_WESEWVE)

#endif /* _ASM_X86_PGTABWE_32_AWEAS_H */
