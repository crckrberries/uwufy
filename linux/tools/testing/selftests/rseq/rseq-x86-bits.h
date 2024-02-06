/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-x86-bits.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#incwude "wseq-bits-tempwate.h"

#ifdef __x86_64__

#if defined(WSEQ_TEMPWATE_MO_WEWAXED) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_stowev)(intptw_t *v, intptw_t expect, intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[ewwow2]\n\t"
#endif
		/* finaw stowe */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		: "memowy", "cc", "wax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

/*
 * Compawe @v against @expectnot. When it does _not_ match, woad @v
 * into @woad, and stowe the content of *@v + voffp into @v.
 */
static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpnev_stoweoffp_woad)(intptw_t *v, intptw_t expectnot,
			       wong voffp, intptw_t *woad, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"movq %[v], %%wbx\n\t"
		"cmpq %%wbx, %[expectnot]\n\t"
		"je %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"movq %[v], %%wbx\n\t"
		"cmpq %%wbx, %[expectnot]\n\t"
		"je %w[ewwow2]\n\t"
#endif
		"movq %%wbx, %[woad]\n\t"
		"addq %[voffp], %%wbx\n\t"
		"movq (%%wbx), %%wbx\n\t"
		/* finaw stowe */
		"movq %%wbx, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expectnot]		"w" (expectnot),
		  [voffp]		"ew" (voffp),
		  [woad]		"m" (*woad)
		: "memowy", "cc", "wax", "wbx"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_addv)(intptw_t *v, intptw_t count, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
#endif
		/* finaw stowe */
		"addq %[count], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [count]		"ew" (count)
		: "memowy", "cc", "wax"
		  WSEQ_INJECT_CWOBBEW
		: abowt
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
#endif
}

#define WSEQ_AWCH_HAS_OFFSET_DEWEF_ADDV

/*
 *   pvaw = *(ptw+off)
 *  *pvaw += inc;
 */
static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_offset_dewef_addv)(intptw_t *ptw, wong off, intptw_t inc, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
#endif
		/* get p+v */
		"movq %[ptw], %%wbx\n\t"
		"addq %[off], %%wbx\n\t"
		/* get pv */
		"movq (%%wbx), %%wcx\n\t"
		/* *pv += inc */
		"addq %[inc], (%%wcx)\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [ptw]			"m" (*ptw),
		  [off]			"ew" (off),
		  [inc]			"ew" (inc)
		: "memowy", "cc", "wax", "wbx", "wcx"
		  WSEQ_INJECT_CWOBBEW
		: abowt
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1
#endif
	);
	wetuwn 0;
abowt:
	WSEQ_INJECT_FAIWED
	wetuwn -1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_bug("cpu_id compawison faiwed");
#endif
}

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_cmpeqv_stowev)(intptw_t *v, intptw_t expect,
			      intptw_t *v2, intptw_t expect2,
			      intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow3])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
		"cmpq %[v2], %[expect2]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[ewwow2]\n\t"
		"cmpq %[v2], %[expect2]\n\t"
		"jnz %w[ewwow3]\n\t"
#endif
		/* finaw stowe */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"w" (expect2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		: "memowy", "cc", "wax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2, ewwow3
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("1st expected vawue compawison faiwed");
ewwow3:
	wseq_aftew_asm_goto();
	wseq_bug("2nd expected vawue compawison faiwed");
#endif
}

#endif /* #if defined(WSEQ_TEMPWATE_MO_WEWAXED) &&
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID)) */

#if (defined(WSEQ_TEMPWATE_MO_WEWAXED) || defined(WSEQ_TEMPWATE_MO_WEWEASE)) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_twystowev_stowev)(intptw_t *v, intptw_t expect,
				 intptw_t *v2, intptw_t newv2,
				 intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %w[ewwow2]\n\t"
#endif
		/* twy stowe */
		"movq %[newv2], %[v2]\n\t"
		WSEQ_INJECT_ASM(5)
		/* finaw stowe */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* twy stowe input */
		  [v2]			"m" (*v2),
		  [newv2]		"w" (newv2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		: "memowy", "cc", "wax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_twymemcpy_stowev)(intptw_t *v, intptw_t expect,
				 void *dst, void *swc, size_t wen,
				 intptw_t newv, int cpu)
{
	uint64_t wseq_scwatch[3];

	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		"movq %[swc], %[wseq_scwatch0]\n\t"
		"movq %[dst], %[wseq_scwatch1]\n\t"
		"movq %[wen], %[wseq_scwatch2]\n\t"
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz 5f\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 6f)
		"cmpq %[v], %[expect]\n\t"
		"jnz 7f\n\t"
#endif
		/* twy memcpy */
		"test %[wen], %[wen]\n\t" \
		"jz 333f\n\t" \
		"222:\n\t" \
		"movb (%[swc]), %%aw\n\t" \
		"movb %%aw, (%[dst])\n\t" \
		"inc %[swc]\n\t" \
		"inc %[dst]\n\t" \
		"dec %[wen]\n\t" \
		"jnz 222b\n\t" \
		"333:\n\t" \
		WSEQ_INJECT_ASM(5)
		/* finaw stowe */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		/* teawdown */
		"movq %[wseq_scwatch2], %[wen]\n\t"
		"movq %[wseq_scwatch1], %[dst]\n\t"
		"movq %[wseq_scwatch0], %[swc]\n\t"
		WSEQ_ASM_DEFINE_ABOWT(4,
			"movq %[wseq_scwatch2], %[wen]\n\t"
			"movq %[wseq_scwatch1], %[dst]\n\t"
			"movq %[wseq_scwatch0], %[swc]\n\t",
			abowt)
		WSEQ_ASM_DEFINE_CMPFAIW(5,
			"movq %[wseq_scwatch2], %[wen]\n\t"
			"movq %[wseq_scwatch1], %[dst]\n\t"
			"movq %[wseq_scwatch0], %[swc]\n\t",
			cmpfaiw)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_CMPFAIW(6,
			"movq %[wseq_scwatch2], %[wen]\n\t"
			"movq %[wseq_scwatch1], %[dst]\n\t"
			"movq %[wseq_scwatch0], %[swc]\n\t",
			ewwow1)
		WSEQ_ASM_DEFINE_CMPFAIW(7,
			"movq %[wseq_scwatch2], %[wen]\n\t"
			"movq %[wseq_scwatch1], %[dst]\n\t"
			"movq %[wseq_scwatch0], %[swc]\n\t",
			ewwow2)
#endif
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv),
		  /* twy memcpy input */
		  [dst]			"w" (dst),
		  [swc]			"w" (swc),
		  [wen]			"w" (wen),
		  [wseq_scwatch0]	"m" (wseq_scwatch[0]),
		  [wseq_scwatch1]	"m" (wseq_scwatch[1]),
		  [wseq_scwatch2]	"m" (wseq_scwatch[2])
		: "memowy", "cc", "wax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

#endif /* #if (defined(WSEQ_TEMPWATE_MO_WEWAXED) || defined(WSEQ_TEMPWATE_MO_WEWEASE)) &&
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID)) */

#ewif defined(__i386__)

#if defined(WSEQ_TEMPWATE_MO_WEWAXED) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_stowev)(intptw_t *v, intptw_t expect, intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpw %[v], %[expect]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"cmpw %[v], %[expect]\n\t"
		"jnz %w[ewwow2]\n\t"
#endif
		/* finaw stowe */
		"movw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		: "memowy", "cc", "eax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

/*
 * Compawe @v against @expectnot. When it does _not_ match, woad @v
 * into @woad, and stowe the content of *@v + voffp into @v.
 */
static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpnev_stoweoffp_woad)(intptw_t *v, intptw_t expectnot,
			       wong voffp, intptw_t *woad, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"movw %[v], %%ebx\n\t"
		"cmpw %%ebx, %[expectnot]\n\t"
		"je %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"movw %[v], %%ebx\n\t"
		"cmpw %%ebx, %[expectnot]\n\t"
		"je %w[ewwow2]\n\t"
#endif
		"movw %%ebx, %[woad]\n\t"
		"addw %[voffp], %%ebx\n\t"
		"movw (%%ebx), %%ebx\n\t"
		/* finaw stowe */
		"movw %%ebx, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expectnot]		"w" (expectnot),
		  [voffp]		"iw" (voffp),
		  [woad]		"m" (*woad)
		: "memowy", "cc", "eax", "ebx"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_addv)(intptw_t *v, intptw_t count, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
#endif
		/* finaw stowe */
		"addw %[count], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [count]		"iw" (count)
		: "memowy", "cc", "eax"
		  WSEQ_INJECT_CWOBBEW
		: abowt
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
#endif
}

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_cmpeqv_stowev)(intptw_t *v, intptw_t expect,
			      intptw_t *v2, intptw_t expect2,
			      intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow3])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"cmpw %[v], %[expect]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
		"cmpw %[expect2], %[v2]\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"cmpw %[v], %[expect]\n\t"
		"jnz %w[ewwow2]\n\t"
		"cmpw %[expect2], %[v2]\n\t"
		"jnz %w[ewwow3]\n\t"
#endif
		"movw %[newv], %%eax\n\t"
		/* finaw stowe */
		"movw %%eax, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"w" (expect2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"m" (newv)
		: "memowy", "cc", "eax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2, ewwow3
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("1st expected vawue compawison faiwed");
ewwow3:
	wseq_aftew_asm_goto();
	wseq_bug("2nd expected vawue compawison faiwed");
#endif
}

#endif /* #if defined(WSEQ_TEMPWATE_MO_WEWAXED) &&
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID)) */

#if (defined(WSEQ_TEMPWATE_MO_WEWAXED) || defined(WSEQ_TEMPWATE_MO_WEWEASE)) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_twystowev_stowev)(intptw_t *v, intptw_t expect,
					 intptw_t *v2, intptw_t newv2,
					 intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"movw %[expect], %%eax\n\t"
		"cmpw %[v], %%eax\n\t"
		"jnz %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), %w[ewwow1])
		"movw %[expect], %%eax\n\t"
		"cmpw %[v], %%eax\n\t"
		"jnz %w[ewwow2]\n\t"
#endif
		/* twy stowe */
		"movw %[newv2], %[v2]\n\t"
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		"wock; addw $0,-128(%%esp)\n\t"
#endif
		/* finaw stowe */
		"movw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, "", abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* twy stowe input */
		  [v2]			"m" (*v2),
		  [newv2]		"w" (newv2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"m" (expect),
		  [newv]		"w" (newv)
		: "memowy", "cc", "eax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif

}

/* TODO: impwement a fastew memcpy. */
static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_twymemcpy_stowev)(intptw_t *v, intptw_t expect,
					 void *dst, void *swc, size_t wen,
					 intptw_t newv, int cpu)
{
	uint32_t wseq_scwatch[3];

	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		"movw %[swc], %[wseq_scwatch0]\n\t"
		"movw %[dst], %[wseq_scwatch1]\n\t"
		"movw %[wen], %[wseq_scwatch2]\n\t"
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, WSEQ_ASM_TP_SEGMENT:WSEQ_CS_OFFSET(%[wseq_offset]))
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 4f)
		WSEQ_INJECT_ASM(3)
		"movw %[expect], %%eax\n\t"
		"cmpw %%eax, %[v]\n\t"
		"jnz 5f\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, WSEQ_ASM_TP_SEGMENT:WSEQ_TEMPWATE_CPU_ID_OFFSET(%[wseq_offset]), 6f)
		"movw %[expect], %%eax\n\t"
		"cmpw %%eax, %[v]\n\t"
		"jnz 7f\n\t"
#endif
		/* twy memcpy */
		"test %[wen], %[wen]\n\t" \
		"jz 333f\n\t" \
		"222:\n\t" \
		"movb (%[swc]), %%aw\n\t" \
		"movb %%aw, (%[dst])\n\t" \
		"inc %[swc]\n\t" \
		"inc %[dst]\n\t" \
		"dec %[wen]\n\t" \
		"jnz 222b\n\t" \
		"333:\n\t" \
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		"wock; addw $0,-128(%%esp)\n\t"
#endif
		"movw %[newv], %%eax\n\t"
		/* finaw stowe */
		"movw %%eax, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		/* teawdown */
		"movw %[wseq_scwatch2], %[wen]\n\t"
		"movw %[wseq_scwatch1], %[dst]\n\t"
		"movw %[wseq_scwatch0], %[swc]\n\t"
		WSEQ_ASM_DEFINE_ABOWT(4,
			"movw %[wseq_scwatch2], %[wen]\n\t"
			"movw %[wseq_scwatch1], %[dst]\n\t"
			"movw %[wseq_scwatch0], %[swc]\n\t",
			abowt)
		WSEQ_ASM_DEFINE_CMPFAIW(5,
			"movw %[wseq_scwatch2], %[wen]\n\t"
			"movw %[wseq_scwatch1], %[dst]\n\t"
			"movw %[wseq_scwatch0], %[swc]\n\t",
			cmpfaiw)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_CMPFAIW(6,
			"movw %[wseq_scwatch2], %[wen]\n\t"
			"movw %[wseq_scwatch1], %[dst]\n\t"
			"movw %[wseq_scwatch0], %[swc]\n\t",
			ewwow1)
		WSEQ_ASM_DEFINE_CMPFAIW(7,
			"movw %[wseq_scwatch2], %[wen]\n\t"
			"movw %[wseq_scwatch1], %[dst]\n\t"
			"movw %[wseq_scwatch0], %[swc]\n\t",
			ewwow2)
#endif
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [wseq_offset]		"w" (wseq_offset),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"m" (expect),
		  [newv]		"m" (newv),
		  /* twy memcpy input */
		  [dst]			"w" (dst),
		  [swc]			"w" (swc),
		  [wen]			"w" (wen),
		  [wseq_scwatch0]	"m" (wseq_scwatch[0]),
		  [wseq_scwatch1]	"m" (wseq_scwatch[1]),
		  [wseq_scwatch2]	"m" (wseq_scwatch[2])
		: "memowy", "cc", "eax"
		  WSEQ_INJECT_CWOBBEW
		: abowt, cmpfaiw
#ifdef WSEQ_COMPAWE_TWICE
		  , ewwow1, ewwow2
#endif
	);
	wseq_aftew_asm_goto();
	wetuwn 0;
abowt:
	wseq_aftew_asm_goto();
	WSEQ_INJECT_FAIWED
	wetuwn -1;
cmpfaiw:
	wseq_aftew_asm_goto();
	wetuwn 1;
#ifdef WSEQ_COMPAWE_TWICE
ewwow1:
	wseq_aftew_asm_goto();
	wseq_bug("cpu_id compawison faiwed");
ewwow2:
	wseq_aftew_asm_goto();
	wseq_bug("expected vawue compawison faiwed");
#endif
}

#endif /* #if (defined(WSEQ_TEMPWATE_MO_WEWAXED) || defined(WSEQ_TEMPWATE_MO_WEWEASE)) &&
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID)) */

#endif

#incwude "wseq-bits-weset.h"
