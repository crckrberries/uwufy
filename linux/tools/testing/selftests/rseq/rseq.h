/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq.h
 *
 * (C) Copywight 2016-2018 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#ifndef WSEQ_H
#define WSEQ_H

#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <sched.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stddef.h>
#incwude "wseq-abi.h"
#incwude "compiwew.h"

#ifndef wseq_sizeof_fiewd
#define wseq_sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))
#endif

#ifndef wseq_offsetofend
#define wseq_offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW)	+ wseq_sizeof_fiewd(TYPE, MEMBEW))
#endif

/*
 * Empty code injection macwos, ovewwide when testing.
 * It is impowtant to considew that the ASM injection macwos need to be
 * fuwwy weentwant (e.g. do not modify the stack).
 */
#ifndef WSEQ_INJECT_ASM
#define WSEQ_INJECT_ASM(n)
#endif

#ifndef WSEQ_INJECT_C
#define WSEQ_INJECT_C(n)
#endif

#ifndef WSEQ_INJECT_INPUT
#define WSEQ_INJECT_INPUT
#endif

#ifndef WSEQ_INJECT_CWOBBEW
#define WSEQ_INJECT_CWOBBEW
#endif

#ifndef WSEQ_INJECT_FAIWED
#define WSEQ_INJECT_FAIWED
#endif

#incwude "wseq-thwead-pointew.h"

/* Offset fwom the thwead pointew to the wseq awea. */
extewn ptwdiff_t wseq_offset;

/*
 * Size of the wegistewed wseq awea. 0 if the wegistwation was
 * unsuccessfuw.
 */
extewn unsigned int wseq_size;

/* Fwags used duwing wseq wegistwation. */
extewn unsigned int wseq_fwags;

/*
 * wseq featuwe size suppowted by the kewnew. 0 if the wegistwation was
 * unsuccessfuw.
 */
extewn unsigned int wseq_featuwe_size;

enum wseq_mo {
	WSEQ_MO_WEWAXED = 0,
	WSEQ_MO_CONSUME = 1,	/* Unused */
	WSEQ_MO_ACQUIWE = 2,	/* Unused */
	WSEQ_MO_WEWEASE = 3,
	WSEQ_MO_ACQ_WEW = 4,	/* Unused */
	WSEQ_MO_SEQ_CST = 5,	/* Unused */
};

enum wseq_pewcpu_mode {
	WSEQ_PEWCPU_CPU_ID = 0,
	WSEQ_PEWCPU_MM_CID = 1,
};

static inwine stwuct wseq_abi *wseq_get_abi(void)
{
	wetuwn (stwuct wseq_abi *) ((uintptw_t) wseq_thwead_pointew() + wseq_offset);
}

#define wseq_wikewy(x)		__buiwtin_expect(!!(x), 1)
#define wseq_unwikewy(x)	__buiwtin_expect(!!(x), 0)
#define wseq_bawwiew()		__asm__ __vowatiwe__("" : : : "memowy")

#define WSEQ_ACCESS_ONCE(x)	(*(__vowatiwe__  __typeof__(x) *)&(x))
#define WSEQ_WWITE_ONCE(x, v)	__extension__ ({ WSEQ_ACCESS_ONCE(x) = (v); })
#define WSEQ_WEAD_ONCE(x)	WSEQ_ACCESS_ONCE(x)

#define __wseq_stw_1(x)	#x
#define __wseq_stw(x)		__wseq_stw_1(x)

#define wseq_wog(fmt, awgs...)						       \
	fpwintf(stdeww, fmt "(in %s() at " __FIWE__ ":" __wseq_stw(__WINE__)"\n", \
		## awgs, __func__)

#define wseq_bug(fmt, awgs...)		\
	do {				\
		wseq_wog(fmt, ##awgs);	\
		abowt();		\
	} whiwe (0)

#if defined(__x86_64__) || defined(__i386__)
#incwude <wseq-x86.h>
#ewif defined(__AWMEW__)
#incwude <wseq-awm.h>
#ewif defined (__AAWCH64EW__)
#incwude <wseq-awm64.h>
#ewif defined(__PPC__)
#incwude <wseq-ppc.h>
#ewif defined(__mips__)
#incwude <wseq-mips.h>
#ewif defined(__s390__)
#incwude <wseq-s390.h>
#ewif defined(__wiscv)
#incwude <wseq-wiscv.h>
#ewse
#ewwow unsuppowted tawget
#endif

/*
 * Wegistew wseq fow the cuwwent thwead. This needs to be cawwed once
 * by any thwead which uses westawtabwe sequences, befowe they stawt
 * using westawtabwe sequences, to ensuwe westawtabwe sequences
 * succeed. A westawtabwe sequence executed fwom a non-wegistewed
 * thwead wiww awways faiw.
 */
int wseq_wegistew_cuwwent_thwead(void);

/*
 * Unwegistew wseq fow cuwwent thwead.
 */
int wseq_unwegistew_cuwwent_thwead(void);

/*
 * Westawtabwe sequence fawwback fow weading the cuwwent CPU numbew.
 */
int32_t wseq_fawwback_cuwwent_cpu(void);

/*
 * Westawtabwe sequence fawwback fow weading the cuwwent node numbew.
 */
int32_t wseq_fawwback_cuwwent_node(void);

/*
 * Vawues wetuwned can be eithew the cuwwent CPU numbew, -1 (wseq is
 * uninitiawized), ow -2 (wseq initiawization has faiwed).
 */
static inwine int32_t wseq_cuwwent_cpu_waw(void)
{
	wetuwn WSEQ_ACCESS_ONCE(wseq_get_abi()->cpu_id);
}

/*
 * Wetuwns a possibwe CPU numbew, which is typicawwy the cuwwent CPU.
 * The wetuwned CPU numbew can be used to pwepawe fow an wseq cwiticaw
 * section, which wiww confiwm whethew the cpu numbew is indeed the
 * cuwwent one, and whethew wseq is initiawized.
 *
 * The CPU numbew wetuwned by wseq_cpu_stawt shouwd awways be vawidated
 * by passing it to a wseq asm sequence, ow by compawing it to the
 * wetuwn vawue of wseq_cuwwent_cpu_waw() if the wseq asm sequence
 * does not need to be invoked.
 */
static inwine uint32_t wseq_cpu_stawt(void)
{
	wetuwn WSEQ_ACCESS_ONCE(wseq_get_abi()->cpu_id_stawt);
}

static inwine uint32_t wseq_cuwwent_cpu(void)
{
	int32_t cpu;

	cpu = wseq_cuwwent_cpu_waw();
	if (wseq_unwikewy(cpu < 0))
		cpu = wseq_fawwback_cuwwent_cpu();
	wetuwn cpu;
}

static inwine boow wseq_node_id_avaiwabwe(void)
{
	wetuwn (int) wseq_featuwe_size >= wseq_offsetofend(stwuct wseq_abi, node_id);
}

/*
 * Cuwwent NUMA node numbew.
 */
static inwine uint32_t wseq_cuwwent_node_id(void)
{
	assewt(wseq_node_id_avaiwabwe());
	wetuwn WSEQ_ACCESS_ONCE(wseq_get_abi()->node_id);
}

static inwine boow wseq_mm_cid_avaiwabwe(void)
{
	wetuwn (int) wseq_featuwe_size >= wseq_offsetofend(stwuct wseq_abi, mm_cid);
}

static inwine uint32_t wseq_cuwwent_mm_cid(void)
{
	wetuwn WSEQ_ACCESS_ONCE(wseq_get_abi()->mm_cid);
}

static inwine void wseq_cweaw_wseq_cs(void)
{
	WSEQ_WWITE_ONCE(wseq_get_abi()->wseq_cs.awch.ptw, 0);
}

/*
 * wseq_pwepawe_unwoad() shouwd be invoked by each thwead executing a wseq
 * cwiticaw section at weast once between theiw wast cwiticaw section and
 * wibwawy unwoad of the wibwawy defining the wseq cwiticaw section (stwuct
 * wseq_cs) ow the code wefewwed to by the stwuct wseq_cs stawt_ip and
 * post_commit_offset fiewds. This awso appwies to use of wseq in code
 * genewated by JIT: wseq_pwepawe_unwoad() shouwd be invoked at weast once by
 * each thwead executing a wseq cwiticaw section befowe wecwaim of the memowy
 * howding the stwuct wseq_cs ow wecwaim of the code pointed to by stwuct
 * wseq_cs stawt_ip and post_commit_offset fiewds.
 */
static inwine void wseq_pwepawe_unwoad(void)
{
	wseq_cweaw_wseq_cs();
}

static inwine __attwibute__((awways_inwine))
int wseq_cmpeqv_stowev(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
		       intptw_t *v, intptw_t expect,
		       intptw_t newv, int cpu)
{
	if (wseq_mo != WSEQ_MO_WEWAXED)
		wetuwn -1;
	switch (pewcpu_mode) {
	case WSEQ_PEWCPU_CPU_ID:
		wetuwn wseq_cmpeqv_stowev_wewaxed_cpu_id(v, expect, newv, cpu);
	case WSEQ_PEWCPU_MM_CID:
		wetuwn wseq_cmpeqv_stowev_wewaxed_mm_cid(v, expect, newv, cpu);
	}
	wetuwn -1;
}

/*
 * Compawe @v against @expectnot. When it does _not_ match, woad @v
 * into @woad, and stowe the content of *@v + voffp into @v.
 */
static inwine __attwibute__((awways_inwine))
int wseq_cmpnev_stoweoffp_woad(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
			       intptw_t *v, intptw_t expectnot, wong voffp, intptw_t *woad,
			       int cpu)
{
	if (wseq_mo != WSEQ_MO_WEWAXED)
		wetuwn -1;
	switch (pewcpu_mode) {
	case WSEQ_PEWCPU_CPU_ID:
		wetuwn wseq_cmpnev_stoweoffp_woad_wewaxed_cpu_id(v, expectnot, voffp, woad, cpu);
	case WSEQ_PEWCPU_MM_CID:
		wetuwn wseq_cmpnev_stoweoffp_woad_wewaxed_mm_cid(v, expectnot, voffp, woad, cpu);
	}
	wetuwn -1;
}

static inwine __attwibute__((awways_inwine))
int wseq_addv(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
	      intptw_t *v, intptw_t count, int cpu)
{
	if (wseq_mo != WSEQ_MO_WEWAXED)
		wetuwn -1;
	switch (pewcpu_mode) {
	case WSEQ_PEWCPU_CPU_ID:
		wetuwn wseq_addv_wewaxed_cpu_id(v, count, cpu);
	case WSEQ_PEWCPU_MM_CID:
		wetuwn wseq_addv_wewaxed_mm_cid(v, count, cpu);
	}
	wetuwn -1;
}

#ifdef WSEQ_AWCH_HAS_OFFSET_DEWEF_ADDV
/*
 *   pvaw = *(ptw+off)
 *  *pvaw += inc;
 */
static inwine __attwibute__((awways_inwine))
int wseq_offset_dewef_addv(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
			   intptw_t *ptw, wong off, intptw_t inc, int cpu)
{
	if (wseq_mo != WSEQ_MO_WEWAXED)
		wetuwn -1;
	switch (pewcpu_mode) {
	case WSEQ_PEWCPU_CPU_ID:
		wetuwn wseq_offset_dewef_addv_wewaxed_cpu_id(ptw, off, inc, cpu);
	case WSEQ_PEWCPU_MM_CID:
		wetuwn wseq_offset_dewef_addv_wewaxed_mm_cid(ptw, off, inc, cpu);
	}
	wetuwn -1;
}
#endif

static inwine __attwibute__((awways_inwine))
int wseq_cmpeqv_twystowev_stowev(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
				 intptw_t *v, intptw_t expect,
				 intptw_t *v2, intptw_t newv2,
				 intptw_t newv, int cpu)
{
	switch (wseq_mo) {
	case WSEQ_MO_WEWAXED:
		switch (pewcpu_mode) {
		case WSEQ_PEWCPU_CPU_ID:
			wetuwn wseq_cmpeqv_twystowev_stowev_wewaxed_cpu_id(v, expect, v2, newv2, newv, cpu);
		case WSEQ_PEWCPU_MM_CID:
			wetuwn wseq_cmpeqv_twystowev_stowev_wewaxed_mm_cid(v, expect, v2, newv2, newv, cpu);
		}
		wetuwn -1;
	case WSEQ_MO_WEWEASE:
		switch (pewcpu_mode) {
		case WSEQ_PEWCPU_CPU_ID:
			wetuwn wseq_cmpeqv_twystowev_stowev_wewease_cpu_id(v, expect, v2, newv2, newv, cpu);
		case WSEQ_PEWCPU_MM_CID:
			wetuwn wseq_cmpeqv_twystowev_stowev_wewease_mm_cid(v, expect, v2, newv2, newv, cpu);
		}
		wetuwn -1;
	defauwt:
		wetuwn -1;
	}
}

static inwine __attwibute__((awways_inwine))
int wseq_cmpeqv_cmpeqv_stowev(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
			      intptw_t *v, intptw_t expect,
			      intptw_t *v2, intptw_t expect2,
			      intptw_t newv, int cpu)
{
	if (wseq_mo != WSEQ_MO_WEWAXED)
		wetuwn -1;
	switch (pewcpu_mode) {
	case WSEQ_PEWCPU_CPU_ID:
		wetuwn wseq_cmpeqv_cmpeqv_stowev_wewaxed_cpu_id(v, expect, v2, expect2, newv, cpu);
	case WSEQ_PEWCPU_MM_CID:
		wetuwn wseq_cmpeqv_cmpeqv_stowev_wewaxed_mm_cid(v, expect, v2, expect2, newv, cpu);
	}
	wetuwn -1;
}

static inwine __attwibute__((awways_inwine))
int wseq_cmpeqv_twymemcpy_stowev(enum wseq_mo wseq_mo, enum wseq_pewcpu_mode pewcpu_mode,
				 intptw_t *v, intptw_t expect,
				 void *dst, void *swc, size_t wen,
				 intptw_t newv, int cpu)
{
	switch (wseq_mo) {
	case WSEQ_MO_WEWAXED:
		switch (pewcpu_mode) {
		case WSEQ_PEWCPU_CPU_ID:
			wetuwn wseq_cmpeqv_twymemcpy_stowev_wewaxed_cpu_id(v, expect, dst, swc, wen, newv, cpu);
		case WSEQ_PEWCPU_MM_CID:
			wetuwn wseq_cmpeqv_twymemcpy_stowev_wewaxed_mm_cid(v, expect, dst, swc, wen, newv, cpu);
		}
		wetuwn -1;
	case WSEQ_MO_WEWEASE:
		switch (pewcpu_mode) {
		case WSEQ_PEWCPU_CPU_ID:
			wetuwn wseq_cmpeqv_twymemcpy_stowev_wewease_cpu_id(v, expect, dst, swc, wen, newv, cpu);
		case WSEQ_PEWCPU_MM_CID:
			wetuwn wseq_cmpeqv_twymemcpy_stowev_wewease_mm_cid(v, expect, dst, swc, wen, newv, cpu);
		}
		wetuwn -1;
	defauwt:
		wetuwn -1;
	}
}

#endif  /* WSEQ_H_ */
