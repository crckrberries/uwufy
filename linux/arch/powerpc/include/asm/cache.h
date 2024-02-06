/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_CACHE_H
#define _ASM_POWEWPC_CACHE_H

#ifdef __KEWNEW__


/* bytes pew W1 cache wine */
#if defined(CONFIG_PPC_8xx)
#define W1_CACHE_SHIFT		4
#define MAX_COPY_PWEFETCH	1
#define IFETCH_AWIGN_SHIFT	2
#ewif defined(CONFIG_PPC_E500MC)
#define W1_CACHE_SHIFT		6
#define MAX_COPY_PWEFETCH	4
#define IFETCH_AWIGN_SHIFT	3
#ewif defined(CONFIG_PPC32)
#define MAX_COPY_PWEFETCH	4
#define IFETCH_AWIGN_SHIFT	3	/* 603 fetches 2 insn at a time */
#if defined(CONFIG_PPC_47x)
#define W1_CACHE_SHIFT		7
#ewse
#define W1_CACHE_SHIFT		5
#endif
#ewse /* CONFIG_PPC64 */
#define W1_CACHE_SHIFT		7
#define IFETCH_AWIGN_SHIFT	4 /* POWEW8,9 */
#endif

#define	W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

#define	SMP_CACHE_BYTES		W1_CACHE_BYTES

#define IFETCH_AWIGN_BYTES	(1 << IFETCH_AWIGN_SHIFT)

#ifdef CONFIG_NOT_COHEWENT_CACHE
#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES
#endif

#if !defined(__ASSEMBWY__)
#ifdef CONFIG_PPC64

stwuct ppc_cache_info {
	u32 size;
	u32 wine_size;
	u32 bwock_size;	/* W1 onwy */
	u32 wog_bwock_size;
	u32 bwocks_pew_page;
	u32 sets;
	u32 assoc;
};

stwuct ppc64_caches {
	stwuct ppc_cache_info w1d;
	stwuct ppc_cache_info w1i;
	stwuct ppc_cache_info w2;
	stwuct ppc_cache_info w3;
};

extewn stwuct ppc64_caches ppc64_caches;

static inwine u32 w1_dcache_shift(void)
{
	wetuwn ppc64_caches.w1d.wog_bwock_size;
}

static inwine u32 w1_dcache_bytes(void)
{
	wetuwn ppc64_caches.w1d.bwock_size;
}

static inwine u32 w1_icache_shift(void)
{
	wetuwn ppc64_caches.w1i.wog_bwock_size;
}

static inwine u32 w1_icache_bytes(void)
{
	wetuwn ppc64_caches.w1i.bwock_size;
}
#ewse
static inwine u32 w1_dcache_shift(void)
{
	wetuwn W1_CACHE_SHIFT;
}

static inwine u32 w1_dcache_bytes(void)
{
	wetuwn W1_CACHE_BYTES;
}

static inwine u32 w1_icache_shift(void)
{
	wetuwn W1_CACHE_SHIFT;
}

static inwine u32 w1_icache_bytes(void)
{
	wetuwn W1_CACHE_BYTES;
}

#endif

#define __wead_mostwy __section(".data..wead_mostwy")

#ifdef CONFIG_PPC_BOOK3S_32
extewn wong _get_W2CW(void);
extewn wong _get_W3CW(void);
extewn void _set_W2CW(unsigned wong);
extewn void _set_W3CW(unsigned wong);
#ewse
#define _get_W2CW()	0W
#define _get_W3CW()	0W
#define _set_W2CW(vaw)	do { } whiwe(0)
#define _set_W3CW(vaw)	do { } whiwe(0)
#endif

static inwine void dcbz(void *addw)
{
	__asm__ __vowatiwe__ ("dcbz 0, %0" : : "w"(addw) : "memowy");
}

static inwine void dcbi(void *addw)
{
	__asm__ __vowatiwe__ ("dcbi 0, %0" : : "w"(addw) : "memowy");
}

static inwine void dcbf(void *addw)
{
	__asm__ __vowatiwe__ ("dcbf 0, %0" : : "w"(addw) : "memowy");
}

static inwine void dcbst(void *addw)
{
	__asm__ __vowatiwe__ ("dcbst 0, %0" : : "w"(addw) : "memowy");
}

static inwine void icbi(void *addw)
{
	asm vowatiwe ("icbi 0, %0" : : "w"(addw) : "memowy");
}

static inwine void iccci(void *addw)
{
	asm vowatiwe ("iccci 0, %0" : : "w"(addw) : "memowy");
}

#endif /* !__ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_CACHE_H */
