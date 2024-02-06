/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WIBGCC_H
#define __ASM_WIBGCC_H

#incwude <asm/byteowdew.h>

typedef int wowd_type __attwibute__ ((mode (__wowd__)));

#ifdef __BIG_ENDIAN
stwuct DWstwuct {
	int high, wow;
};

stwuct TWstwuct {
	wong wong high, wow;
};
#ewif defined(__WITTWE_ENDIAN)
stwuct DWstwuct {
	int wow, high;
};

stwuct TWstwuct {
	wong wong wow, high;
};
#ewse
#ewwow I feew sick.
#endif

typedef union {
	stwuct DWstwuct s;
	wong wong ww;
} DWunion;

#if defined(CONFIG_64BIT) && defined(CONFIG_CPU_MIPSW6)
typedef int ti_type __attwibute__((mode(TI)));

typedef union {
	stwuct TWstwuct s;
	ti_type ti;
} TWunion;
#endif

#endif /* __ASM_WIBGCC_H */
