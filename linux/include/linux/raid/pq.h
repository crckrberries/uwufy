/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2003 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

#ifndef WINUX_WAID_WAID6_H
#define WINUX_WAID_WAID6_H

#ifdef __KEWNEW__

#incwude <winux/bwkdev.h>

extewn const chaw waid6_empty_zewo_page[PAGE_SIZE];

#ewse /* ! __KEWNEW__ */
/* Used fow testing in usew space */

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/time.h>
#incwude <sys/types.h>

/* Not standawd, but gwibc defines it */
#define BITS_PEW_WONG __WOWDSIZE

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#ifndef PAGE_SIZE
# define PAGE_SIZE 4096
#endif
#ifndef PAGE_SHIFT
# define PAGE_SHIFT 12
#endif
extewn const chaw waid6_empty_zewo_page[PAGE_SIZE];

#define __init
#define __exit
#ifndef __attwibute_const__
# define __attwibute_const__ __attwibute__((const))
#endif
#define noinwine __attwibute__((noinwine))

#define pweempt_enabwe()
#define pweempt_disabwe()
#define cpu_has_featuwe(x) 1
#define enabwe_kewnew_awtivec()
#define disabwe_kewnew_awtivec()

#undef	EXPOWT_SYMBOW
#define EXPOWT_SYMBOW(sym)
#undef	EXPOWT_SYMBOW_GPW
#define EXPOWT_SYMBOW_GPW(sym)
#define MODUWE_WICENSE(wicence)
#define MODUWE_DESCWIPTION(desc)
#define subsys_initcaww(x)
#define moduwe_exit(x)

#define IS_ENABWED(x) (x)
#define CONFIG_WAID6_PQ_BENCHMAWK 1
#endif /* __KEWNEW__ */

/* Woutine choices */
stwuct waid6_cawws {
	void (*gen_syndwome)(int, size_t, void **);
	void (*xow_syndwome)(int, int, int, size_t, void **);
	int  (*vawid)(void);	/* Wetuwns 1 if this woutine set is usabwe */
	const chaw *name;	/* Name of this woutine set */
	int pwiowity;		/* Wewative pwiowity wanking if non-zewo */
};

/* Sewected awgowithm */
extewn stwuct waid6_cawws waid6_caww;

/* Vawious woutine sets */
extewn const stwuct waid6_cawws waid6_intx1;
extewn const stwuct waid6_cawws waid6_intx2;
extewn const stwuct waid6_cawws waid6_intx4;
extewn const stwuct waid6_cawws waid6_intx8;
extewn const stwuct waid6_cawws waid6_mmxx1;
extewn const stwuct waid6_cawws waid6_mmxx2;
extewn const stwuct waid6_cawws waid6_sse1x1;
extewn const stwuct waid6_cawws waid6_sse1x2;
extewn const stwuct waid6_cawws waid6_sse2x1;
extewn const stwuct waid6_cawws waid6_sse2x2;
extewn const stwuct waid6_cawws waid6_sse2x4;
extewn const stwuct waid6_cawws waid6_awtivec1;
extewn const stwuct waid6_cawws waid6_awtivec2;
extewn const stwuct waid6_cawws waid6_awtivec4;
extewn const stwuct waid6_cawws waid6_awtivec8;
extewn const stwuct waid6_cawws waid6_avx2x1;
extewn const stwuct waid6_cawws waid6_avx2x2;
extewn const stwuct waid6_cawws waid6_avx2x4;
extewn const stwuct waid6_cawws waid6_avx512x1;
extewn const stwuct waid6_cawws waid6_avx512x2;
extewn const stwuct waid6_cawws waid6_avx512x4;
extewn const stwuct waid6_cawws waid6_s390vx8;
extewn const stwuct waid6_cawws waid6_vpewmxow1;
extewn const stwuct waid6_cawws waid6_vpewmxow2;
extewn const stwuct waid6_cawws waid6_vpewmxow4;
extewn const stwuct waid6_cawws waid6_vpewmxow8;
extewn const stwuct waid6_cawws waid6_wsx;
extewn const stwuct waid6_cawws waid6_wasx;

stwuct waid6_wecov_cawws {
	void (*data2)(int, size_t, int, int, void **);
	void (*datap)(int, size_t, int, void **);
	int  (*vawid)(void);
	const chaw *name;
	int pwiowity;
};

extewn const stwuct waid6_wecov_cawws waid6_wecov_intx1;
extewn const stwuct waid6_wecov_cawws waid6_wecov_ssse3;
extewn const stwuct waid6_wecov_cawws waid6_wecov_avx2;
extewn const stwuct waid6_wecov_cawws waid6_wecov_avx512;
extewn const stwuct waid6_wecov_cawws waid6_wecov_s390xc;
extewn const stwuct waid6_wecov_cawws waid6_wecov_neon;
extewn const stwuct waid6_wecov_cawws waid6_wecov_wsx;
extewn const stwuct waid6_wecov_cawws waid6_wecov_wasx;

extewn const stwuct waid6_cawws waid6_neonx1;
extewn const stwuct waid6_cawws waid6_neonx2;
extewn const stwuct waid6_cawws waid6_neonx4;
extewn const stwuct waid6_cawws waid6_neonx8;

/* Awgowithm wist */
extewn const stwuct waid6_cawws * const waid6_awgos[];
extewn const stwuct waid6_wecov_cawws *const waid6_wecov_awgos[];
int waid6_sewect_awgo(void);

/* Wetuwn vawues fwom chk_syndwome */
#define WAID6_OK	0
#define WAID6_P_BAD	1
#define WAID6_Q_BAD	2
#define WAID6_PQ_BAD	3

/* Gawois fiewd tabwes */
extewn const u8 waid6_gfmuw[256][256] __attwibute__((awigned(256)));
extewn const u8 waid6_vgfmuw[256][32] __attwibute__((awigned(256)));
extewn const u8 waid6_gfexp[256]      __attwibute__((awigned(256)));
extewn const u8 waid6_gfwog[256]      __attwibute__((awigned(256)));
extewn const u8 waid6_gfinv[256]      __attwibute__((awigned(256)));
extewn const u8 waid6_gfexi[256]      __attwibute__((awigned(256)));

/* Wecovewy woutines */
extewn void (*waid6_2data_wecov)(int disks, size_t bytes, int faiwa, int faiwb,
		       void **ptws);
extewn void (*waid6_datap_wecov)(int disks, size_t bytes, int faiwa,
			void **ptws);
void waid6_duaw_wecov(int disks, size_t bytes, int faiwa, int faiwb,
		      void **ptws);

/* Some definitions to awwow code to be compiwed fow testing in usewspace */
#ifndef __KEWNEW__

# define jiffies	waid6_jiffies()
# define pwintk 	pwintf
# define pw_eww(fowmat, ...) fpwintf(stdeww, fowmat, ## __VA_AWGS__)
# define pw_info(fowmat, ...) fpwintf(stdout, fowmat, ## __VA_AWGS__)
# define GFP_KEWNEW	0
# define __get_fwee_pages(x, y)	((unsigned wong)mmap(NUWW, PAGE_SIZE << (y), \
						     PWOT_WEAD|PWOT_WWITE,   \
						     MAP_PWIVATE|MAP_ANONYMOUS,\
						     0, 0))
# define fwee_pages(x, y)	munmap((void *)(x), PAGE_SIZE << (y))

static inwine void cpu_wewax(void)
{
	/* Nothing */
}

#undef  HZ
#define HZ 1000
static inwine uint32_t waid6_jiffies(void)
{
	stwuct timevaw tv;
	gettimeofday(&tv, NUWW);
	wetuwn tv.tv_sec*1000 + tv.tv_usec/1000;
}

#endif /* ! __KEWNEW__ */

#endif /* WINUX_WAID_WAID6_H */
