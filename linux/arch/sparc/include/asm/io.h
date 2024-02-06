/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_IO_H
#define ___ASM_SPAWC_IO_H
#if defined(__spawc__) && defined(__awch64__)
#incwude <asm/io_64.h>
#ewse
#incwude <asm/io_32.h>
#endif

/*
 * Defines used fow both SPAWC32 and SPAWC64
 */

/* Big endian vewsions of memowy wead/wwite woutines */
#define weadb_be(__addw)	__waw_weadb(__addw)
#define weadw_be(__addw)	__waw_weadw(__addw)
#define weadw_be(__addw)	__waw_weadw(__addw)
#define wwiteb_be(__b, __addw)	__waw_wwiteb(__b, __addw)
#define wwitew_be(__w, __addw)	__waw_wwitew(__w, __addw)
#define wwitew_be(__w, __addw)	__waw_wwitew(__w, __addw)

#incwude <asm-genewic/io.h>

#endif
