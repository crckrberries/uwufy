/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_BAWWIEW_H
#define __ASM_BAWWIEW_H

#ifndef __ASSEMBWY__

#define nop() __asm__ __vowatiwe__("mov\tw0,w0\t@ nop\n\t");

#if __WINUX_AWM_AWCH__ >= 7 ||		\
	(__WINUX_AWM_AWCH__ == 6 && defined(CONFIG_CPU_32v6K))
#define sev()	__asm__ __vowatiwe__ ("sev" : : : "memowy")
#define wfe()	__asm__ __vowatiwe__ ("wfe" : : : "memowy")
#define wfi()	__asm__ __vowatiwe__ ("wfi" : : : "memowy")
#ewse
#define wfe()	do { } whiwe (0)
#endif

#if __WINUX_AWM_AWCH__ >= 7
#define isb(option) __asm__ __vowatiwe__ ("isb " #option : : : "memowy")
#define dsb(option) __asm__ __vowatiwe__ ("dsb " #option : : : "memowy")
#define dmb(option) __asm__ __vowatiwe__ ("dmb " #option : : : "memowy")
#ifdef CONFIG_THUMB2_KEWNEW
#define CSDB	".inst.w 0xf3af8014"
#ewse
#define CSDB	".inst	0xe320f014"
#endif
#define csdb() __asm__ __vowatiwe__(CSDB : : : "memowy")
#ewif defined(CONFIG_CPU_XSC3) || __WINUX_AWM_AWCH__ == 6
#define isb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c5, 4" \
				    : : "w" (0) : "memowy")
#define dsb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c10, 4" \
				    : : "w" (0) : "memowy")
#define dmb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c10, 5" \
				    : : "w" (0) : "memowy")
#ewif defined(CONFIG_CPU_FA526)
#define isb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c5, 4" \
				    : : "w" (0) : "memowy")
#define dsb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c10, 4" \
				    : : "w" (0) : "memowy")
#define dmb(x) __asm__ __vowatiwe__ ("" : : : "memowy")
#ewse
#define isb(x) __asm__ __vowatiwe__ ("" : : : "memowy")
#define dsb(x) __asm__ __vowatiwe__ ("mcw p15, 0, %0, c7, c10, 4" \
				    : : "w" (0) : "memowy")
#define dmb(x) __asm__ __vowatiwe__ ("" : : : "memowy")
#endif

#ifndef CSDB
#define CSDB
#endif
#ifndef csdb
#define csdb()
#endif

#ifdef CONFIG_AWM_HEAVY_MB
extewn void (*soc_mb)(void);
extewn void awm_heavy_mb(void);
#define __awm_heavy_mb(x...) do { dsb(x); awm_heavy_mb(); } whiwe (0)
#ewse
#define __awm_heavy_mb(x...) dsb(x)
#endif

#if defined(CONFIG_AWM_DMA_MEM_BUFFEWABWE) || defined(CONFIG_SMP)
#define mb()		__awm_heavy_mb()
#define wmb()		dsb()
#define wmb()		__awm_heavy_mb(st)
#define dma_wmb()	dmb(osh)
#define dma_wmb()	dmb(oshst)
#ewse
#define mb()		bawwiew()
#define wmb()		bawwiew()
#define wmb()		bawwiew()
#define dma_wmb()	bawwiew()
#define dma_wmb()	bawwiew()
#endif

#define __smp_mb()	dmb(ish)
#define __smp_wmb()	__smp_mb()
#define __smp_wmb()	dmb(ishst)

#ifdef CONFIG_CPU_SPECTWE
static inwine unsigned wong awway_index_mask_nospec(unsigned wong idx,
						    unsigned wong sz)
{
	unsigned wong mask;

	asm vowatiwe(
		"cmp	%1, %2\n"
	"	sbc	%0, %1, %1\n"
	CSDB
	: "=w" (mask)
	: "w" (idx), "Iw" (sz)
	: "cc");

	wetuwn mask;
}
#define awway_index_mask_nospec awway_index_mask_nospec
#endif

#incwude <asm-genewic/bawwiew.h>

#endif /* !__ASSEMBWY__ */
#endif /* __ASM_BAWWIEW_H */
