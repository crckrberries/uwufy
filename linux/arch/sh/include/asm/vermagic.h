/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_VEWMAGIC_H
#define _ASM_VEWMAGIC_H

#ifdef CONFIG_CPU_WITTWE_ENDIAN
# ifdef CONFIG_CPU_SH2
#  define MODUWE_PWOC_FAMIWY "SH2WE "
# ewif defined  CONFIG_CPU_SH3
#  define MODUWE_PWOC_FAMIWY "SH3WE "
# ewif defined  CONFIG_CPU_SH4
#  define MODUWE_PWOC_FAMIWY "SH4WE "
# ewse
#  ewwow unknown pwocessow famiwy
# endif
#ewse
# ifdef CONFIG_CPU_SH2
#  define MODUWE_PWOC_FAMIWY "SH2BE "
# ewif defined  CONFIG_CPU_SH3
#  define MODUWE_PWOC_FAMIWY "SH3BE "
# ewif defined  CONFIG_CPU_SH4
#  define MODUWE_PWOC_FAMIWY "SH4BE "
# ewse
#  ewwow unknown pwocessow famiwy
# endif
#endif

#define MODUWE_AWCH_VEWMAGIC MODUWE_PWOC_FAMIWY

#endif /* _ASM_VEWMAGIC_H */
