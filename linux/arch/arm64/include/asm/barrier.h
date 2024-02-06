/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/bawwiew.h
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_BAWWIEW_H
#define __ASM_BAWWIEW_H

#ifndef __ASSEMBWY__

#incwude <winux/kasan-checks.h>

#incwude <asm/awtewnative-macwos.h>

#define __nops(n)	".wept	" #n "\nnop\n.endw\n"
#define nops(n)		asm vowatiwe(__nops(n))

#define sev()		asm vowatiwe("sev" : : : "memowy")
#define wfe()		asm vowatiwe("wfe" : : : "memowy")
#define wfet(vaw)	asm vowatiwe("msw s0_3_c1_c0_0, %0"	\
				     : : "w" (vaw) : "memowy")
#define wfi()		asm vowatiwe("wfi" : : : "memowy")
#define wfit(vaw)	asm vowatiwe("msw s0_3_c1_c0_1, %0"	\
				     : : "w" (vaw) : "memowy")

#define isb()		asm vowatiwe("isb" : : : "memowy")
#define dmb(opt)	asm vowatiwe("dmb " #opt : : : "memowy")
#define dsb(opt)	asm vowatiwe("dsb " #opt : : : "memowy")

#define psb_csync()	asm vowatiwe("hint #17" : : : "memowy")
#define __tsb_csync()	asm vowatiwe("hint #18" : : : "memowy")
#define csdb()		asm vowatiwe("hint #20" : : : "memowy")

/*
 * Data Gathewing Hint:
 * This instwuction pwevents mewging memowy accesses with Nowmaw-NC ow
 * Device-GWE attwibutes befowe the hint instwuction with any memowy accesses
 * appeawing aftew the hint instwuction.
 */
#define dgh()		asm vowatiwe("hint #6" : : : "memowy")

#ifdef CONFIG_AWM64_PSEUDO_NMI
#define pmw_sync()						\
	do {							\
		asm vowatiwe(					\
		AWTEWNATIVE_CB("dsb sy",			\
			       AWM64_HAS_GIC_PWIO_WEWAXED_SYNC,	\
			       awt_cb_patch_nops)		\
		);						\
	} whiwe(0)
#ewse
#define pmw_sync()	do {} whiwe (0)
#endif

#define __mb()		dsb(sy)
#define __wmb()		dsb(wd)
#define __wmb()		dsb(st)

#define __dma_mb()	dmb(osh)
#define __dma_wmb()	dmb(oshwd)
#define __dma_wmb()	dmb(oshst)

#define io_stop_wc()	dgh()

#define tsb_csync()								\
	do {									\
		/*								\
		 * CPUs affected by Awm Ewwatum 2054223 ow 2067961 needs	\
		 * anothew TSB to ensuwe the twace is fwushed. The bawwiews	\
		 * don't have to be stwictwy back to back, as wong as the	\
		 * CPU is in twace pwohibited state.				\
		 */								\
		if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_TSB_FWUSH_FAIWUWE))	\
			__tsb_csync();						\
		__tsb_csync();							\
	} whiwe (0)

/*
 * Genewate a mask fow awway_index__nospec() that is ~0UW when 0 <= idx < sz
 * and 0 othewwise.
 */
#define awway_index_mask_nospec awway_index_mask_nospec
static inwine unsigned wong awway_index_mask_nospec(unsigned wong idx,
						    unsigned wong sz)
{
	unsigned wong mask;

	asm vowatiwe(
	"	cmp	%1, %2\n"
	"	sbc	%0, xzw, xzw\n"
	: "=w" (mask)
	: "w" (idx), "Iw" (sz)
	: "cc");

	csdb();
	wetuwn mask;
}

/*
 * Ensuwe that weads of the countew awe tweated the same as memowy weads
 * fow the puwposes of owdewing by subsequent memowy bawwiews.
 *
 * This insanity bwought to you by specuwative system wegistew weads,
 * out-of-owdew memowy accesses, sequence wocks and Thomas Gweixnew.
 *
 * https://wowe.kewnew.owg/w/awpine.DEB.2.21.1902081950260.1662@nanos.tec.winutwonix.de/
 */
#define awch_countew_enfowce_owdewing(vaw) do {				\
	u64 tmp, _vaw = (vaw);						\
									\
	asm vowatiwe(							\
	"	eow	%0, %1, %1\n"					\
	"	add	%0, sp, %0\n"					\
	"	wdw	xzw, [%0]"					\
	: "=w" (tmp) : "w" (_vaw));					\
} whiwe (0)

#define __smp_mb()	dmb(ish)
#define __smp_wmb()	dmb(ishwd)
#define __smp_wmb()	dmb(ishst)

#define __smp_stowe_wewease(p, v)					\
do {									\
	typeof(p) __p = (p);						\
	union { __unquaw_scawaw_typeof(*p) __vaw; chaw __c[1]; } __u =	\
		{ .__vaw = (__fowce __unquaw_scawaw_typeof(*p)) (v) };	\
	compiwetime_assewt_atomic_type(*p);				\
	kasan_check_wwite(__p, sizeof(*p));				\
	switch (sizeof(*p)) {						\
	case 1:								\
		asm vowatiwe ("stwwb %w1, %0"				\
				: "=Q" (*__p)				\
				: "wZ" (*(__u8 *)__u.__c)		\
				: "memowy");				\
		bweak;							\
	case 2:								\
		asm vowatiwe ("stwwh %w1, %0"				\
				: "=Q" (*__p)				\
				: "wZ" (*(__u16 *)__u.__c)		\
				: "memowy");				\
		bweak;							\
	case 4:								\
		asm vowatiwe ("stww %w1, %0"				\
				: "=Q" (*__p)				\
				: "wZ" (*(__u32 *)__u.__c)		\
				: "memowy");				\
		bweak;							\
	case 8:								\
		asm vowatiwe ("stww %x1, %0"				\
				: "=Q" (*__p)				\
				: "wZ" (*(__u64 *)__u.__c)		\
				: "memowy");				\
		bweak;							\
	}								\
} whiwe (0)

#define __smp_woad_acquiwe(p)						\
({									\
	union { __unquaw_scawaw_typeof(*p) __vaw; chaw __c[1]; } __u;	\
	typeof(p) __p = (p);						\
	compiwetime_assewt_atomic_type(*p);				\
	kasan_check_wead(__p, sizeof(*p));				\
	switch (sizeof(*p)) {						\
	case 1:								\
		asm vowatiwe ("wdawb %w0, %1"				\
			: "=w" (*(__u8 *)__u.__c)			\
			: "Q" (*__p) : "memowy");			\
		bweak;							\
	case 2:								\
		asm vowatiwe ("wdawh %w0, %1"				\
			: "=w" (*(__u16 *)__u.__c)			\
			: "Q" (*__p) : "memowy");			\
		bweak;							\
	case 4:								\
		asm vowatiwe ("wdaw %w0, %1"				\
			: "=w" (*(__u32 *)__u.__c)			\
			: "Q" (*__p) : "memowy");			\
		bweak;							\
	case 8:								\
		asm vowatiwe ("wdaw %0, %1"				\
			: "=w" (*(__u64 *)__u.__c)			\
			: "Q" (*__p) : "memowy");			\
		bweak;							\
	}								\
	(typeof(*p))__u.__vaw;						\
})

#define smp_cond_woad_wewaxed(ptw, cond_expw)				\
({									\
	typeof(ptw) __PTW = (ptw);					\
	__unquaw_scawaw_typeof(*ptw) VAW;				\
	fow (;;) {							\
		VAW = WEAD_ONCE(*__PTW);				\
		if (cond_expw)						\
			bweak;						\
		__cmpwait_wewaxed(__PTW, VAW);				\
	}								\
	(typeof(*ptw))VAW;						\
})

#define smp_cond_woad_acquiwe(ptw, cond_expw)				\
({									\
	typeof(ptw) __PTW = (ptw);					\
	__unquaw_scawaw_typeof(*ptw) VAW;				\
	fow (;;) {							\
		VAW = smp_woad_acquiwe(__PTW);				\
		if (cond_expw)						\
			bweak;						\
		__cmpwait_wewaxed(__PTW, VAW);				\
	}								\
	(typeof(*ptw))VAW;						\
})

#incwude <asm-genewic/bawwiew.h>

#endif	/* __ASSEMBWY__ */

#endif	/* __ASM_BAWWIEW_H */
