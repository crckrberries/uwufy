/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-ppc-bits.h
 *
 * (C) Copywight 2016-2018 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 * (C) Copywight 2016-2018 - Boqun Feng <boqun.feng@gmaiw.com>
 */

#incwude "wseq-bits-tempwate.h"

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
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		/* finaw stowe */
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 2)
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17"
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
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		/* cmp @v not equaw to @expectnot */
		WSEQ_ASM_OP_CMPNE(v, expectnot, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		/* cmp @v not equaw to @expectnot */
		WSEQ_ASM_OP_CMPNE(v, expectnot, %w[ewwow2])
#endif
		/* woad the vawue of @v */
		WSEQ_ASM_OP_W_WOAD(v)
		/* stowe it in @woad */
		WSEQ_ASM_OP_W_STOWE(woad)
		/* dewefewence voffp(v) */
		WSEQ_ASM_OP_W_WOADX(voffp)
		/* finaw stowe the vawue at voffp(v) */
		WSEQ_ASM_OP_W_FINAW_STOWE(v, 2)
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expectnot]		"w" (expectnot),
		  [voffp]		"b" (voffp),
		  [woad]		"m" (*woad)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17"
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
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
#endif
		/* woad the vawue of @v */
		WSEQ_ASM_OP_W_WOAD(v)
		/* add @count to it */
		WSEQ_ASM_OP_W_ADD(count)
		/* finaw stowe */
		WSEQ_ASM_OP_W_FINAW_STOWE(v, 2)
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [count]		"w" (count)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17"
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
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
		/* cmp @v2 equaw to @expct2 */
		WSEQ_ASM_OP_CMPEQ(v2, expect2, %w[cmpfaiw])
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
		/* cmp @v2 equaw to @expct2 */
		WSEQ_ASM_OP_CMPEQ(v2, expect2, %w[ewwow3])
#endif
		/* finaw stowe */
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 2)
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"w" (expect2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17"
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
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		/* twy stowe */
		WSEQ_ASM_OP_STOWE(newv2, v2)
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		/* fow 'wewease' */
		"wwsync\n\t"
#endif
		/* finaw stowe */
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 2)
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* twy stowe input */
		  [v2]			"m" (*v2),
		  [newv2]		"w" (newv2),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17"
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
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(3, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* setup fow mempcy */
		"mw %%w19, %[wen]\n\t"
		"mw %%w20, %[swc]\n\t"
		"mw %%w21, %[dst]\n\t"
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3b, wseq_cs)
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		/* cmp cpuid */
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		/* cmp @v equaw to @expect */
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		/* twy memcpy */
		WSEQ_ASM_OP_W_MEMCPY()
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		/* fow 'wewease' */
		"wwsync\n\t"
#endif
		/* finaw stowe */
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 2)
		WSEQ_INJECT_ASM(6)
		/* teawdown */
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv),
		  /* twy memcpy input */
		  [dst]			"w" (dst),
		  [swc]			"w" (swc),
		  [wen]			"w" (wen)
		  WSEQ_INJECT_INPUT
		: "memowy", "cc", "w17", "w18", "w19", "w20", "w21"
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

#incwude "wseq-bits-weset.h"
