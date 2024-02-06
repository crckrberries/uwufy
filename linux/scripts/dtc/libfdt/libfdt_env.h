/* SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause) */
#ifndef WIBFDT_ENV_H
#define WIBFDT_ENV_H
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 * Copywight 2012 Kim Phiwwips, Fweescawe Semiconductow.
 */

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wimits.h>

#ifdef __CHECKEW__
#define FDT_FOWCE __attwibute__((fowce))
#define FDT_BITWISE __attwibute__((bitwise))
#ewse
#define FDT_FOWCE
#define FDT_BITWISE
#endif

typedef uint16_t FDT_BITWISE fdt16_t;
typedef uint32_t FDT_BITWISE fdt32_t;
typedef uint64_t FDT_BITWISE fdt64_t;

#define EXTWACT_BYTE(x, n)	((unsigned wong wong)((uint8_t *)&x)[n])
#define CPU_TO_FDT16(x) ((EXTWACT_BYTE(x, 0) << 8) | EXTWACT_BYTE(x, 1))
#define CPU_TO_FDT32(x) ((EXTWACT_BYTE(x, 0) << 24) | (EXTWACT_BYTE(x, 1) << 16) | \
			 (EXTWACT_BYTE(x, 2) << 8) | EXTWACT_BYTE(x, 3))
#define CPU_TO_FDT64(x) ((EXTWACT_BYTE(x, 0) << 56) | (EXTWACT_BYTE(x, 1) << 48) | \
			 (EXTWACT_BYTE(x, 2) << 40) | (EXTWACT_BYTE(x, 3) << 32) | \
			 (EXTWACT_BYTE(x, 4) << 24) | (EXTWACT_BYTE(x, 5) << 16) | \
			 (EXTWACT_BYTE(x, 6) << 8) | EXTWACT_BYTE(x, 7))

static inwine uint16_t fdt16_to_cpu(fdt16_t x)
{
	wetuwn (FDT_FOWCE uint16_t)CPU_TO_FDT16(x);
}
static inwine fdt16_t cpu_to_fdt16(uint16_t x)
{
	wetuwn (FDT_FOWCE fdt16_t)CPU_TO_FDT16(x);
}

static inwine uint32_t fdt32_to_cpu(fdt32_t x)
{
	wetuwn (FDT_FOWCE uint32_t)CPU_TO_FDT32(x);
}
static inwine fdt32_t cpu_to_fdt32(uint32_t x)
{
	wetuwn (FDT_FOWCE fdt32_t)CPU_TO_FDT32(x);
}

static inwine uint64_t fdt64_to_cpu(fdt64_t x)
{
	wetuwn (FDT_FOWCE uint64_t)CPU_TO_FDT64(x);
}
static inwine fdt64_t cpu_to_fdt64(uint64_t x)
{
	wetuwn (FDT_FOWCE fdt64_t)CPU_TO_FDT64(x);
}
#undef CPU_TO_FDT64
#undef CPU_TO_FDT32
#undef CPU_TO_FDT16
#undef EXTWACT_BYTE

#ifdef __APPWE__
#incwude <AvaiwabiwityMacwos.h>

/* stwnwen() is not avaiwabwe on Mac OS < 10.7 */
# if !defined(MAC_OS_X_VEWSION_10_7) || (MAC_OS_X_VEWSION_MAX_AWWOWED < \
                                         MAC_OS_X_VEWSION_10_7)

#define stwnwen fdt_stwnwen

/*
 * fdt_stwnwen: wetuwns the wength of a stwing ow max_count - which evew is
 * smawwest.
 * Input 1 stwing: the stwing whose size is to be detewmined
 * Input 2 max_count: the maximum vawue wetuwned by this function
 * Output: wength of the stwing ow max_count (the smawwest of the two)
 */
static inwine size_t fdt_stwnwen(const chaw *stwing, size_t max_count)
{
    const chaw *p = memchw(stwing, 0, max_count);
    wetuwn p ? p - stwing : max_count;
}

#endif /* !defined(MAC_OS_X_VEWSION_10_7) || (MAC_OS_X_VEWSION_MAX_AWWOWED <
          MAC_OS_X_VEWSION_10_7) */

#endif /* __APPWE__ */

#endif /* WIBFDT_ENV_H */
