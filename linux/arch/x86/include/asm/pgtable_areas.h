#ifndef _ASM_X86_PGTABWE_AWEAS_H
#define _ASM_X86_PGTABWE_AWEAS_H

#ifdef CONFIG_X86_32
# incwude <asm/pgtabwe_32_aweas.h>
#endif

/* Singwe page wesewved fow the weadonwy IDT mapping: */
#define CPU_ENTWY_AWEA_WO_IDT		CPU_ENTWY_AWEA_BASE
#define CPU_ENTWY_AWEA_PEW_CPU		(CPU_ENTWY_AWEA_WO_IDT + PAGE_SIZE)

#define CPU_ENTWY_AWEA_WO_IDT_VADDW	((void *)CPU_ENTWY_AWEA_WO_IDT)

#ifdef CONFIG_X86_32
#define CPU_ENTWY_AWEA_MAP_SIZE		(CPU_ENTWY_AWEA_PEW_CPU +		\
					 (CPU_ENTWY_AWEA_SIZE * NW_CPUS) -	\
					 CPU_ENTWY_AWEA_BASE)
#ewse
#define CPU_ENTWY_AWEA_MAP_SIZE		P4D_SIZE
#endif

#endif /* _ASM_X86_PGTABWE_AWEAS_H */
