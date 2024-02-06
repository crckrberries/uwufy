/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-awm-bits.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#incwude "wseq-bits-tempwate.h"

#if defined(WSEQ_TEMPWATE_MO_WEWAXED) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_stowev)(intptw_t *v, intptw_t expect, intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[ewwow2]\n\t"
#endif
		/* finaw stowe */
		"stw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		"b 5f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4, "", abowt, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"m" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "w0", "memowy", "cc"
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
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		"wdw w0, %[v]\n\t"
		"cmp %[expectnot], w0\n\t"
		"beq %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		"wdw w0, %[v]\n\t"
		"cmp %[expectnot], w0\n\t"
		"beq %w[ewwow2]\n\t"
#endif
		"stw w0, %[woad]\n\t"
		"add w0, %[voffp]\n\t"
		"wdw w0, [w0]\n\t"
		/* finaw stowe */
		"stw w0, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(5)
		"b 5f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4, "", abowt, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  /* finaw stowe input */
		  [v]			"m" (*v),
		  [expectnot]		"w" (expectnot),
		  [voffp]		"Iw" (voffp),
		  [woad]		"m" (*woad)
		  WSEQ_INJECT_INPUT
		: "w0", "memowy", "cc"
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
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
#endif
		"wdw w0, %[v]\n\t"
		"add w0, %[count]\n\t"
		/* finaw stowe */
		"stw w0, %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(4)
		"b 5f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4, "", abowt, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"m" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"m" (*v),
		  [count]		"Iw" (count)
		  WSEQ_INJECT_INPUT
		: "w0", "memowy", "cc"
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
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow3])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
		"wdw w0, %[v2]\n\t"
		"cmp %[expect2], w0\n\t"
		"bne %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[ewwow2]\n\t"
		"wdw w0, %[v2]\n\t"
		"cmp %[expect2], w0\n\t"
		"bne %w[ewwow3]\n\t"
#endif
		/* finaw stowe */
		"stw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		"b 5f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4, "", abowt, 1b, 2b, 4f)
		"5:\n\t"
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
		: "w0", "memowy", "cc"
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
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[cmpfaiw]\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne %w[ewwow2]\n\t"
#endif
		/* twy stowe */
		"stw %[newv2], %[v2]\n\t"
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		"dmb\n\t"	/* fuww mb pwovides stowe-wewease */
#endif
		/* finaw stowe */
		"stw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		"b 5f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4, "", abowt, 1b, 2b, 4f)
		"5:\n\t"
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
		: "w0", "memowy", "cc"
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
	uint32_t wseq_scwatch[3];

	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(9, 1f, 2f, 4f) /* stawt, commit, abowt */
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(1f, %w[ewwow2])
#endif
		"stw %[swc], %[wseq_scwatch0]\n\t"
		"stw %[dst], %[wseq_scwatch1]\n\t"
		"stw %[wen], %[wseq_scwatch2]\n\t"
		/* Stawt wseq by stowing tabwe entwy pointew into wseq_cs. */
		WSEQ_ASM_STOWE_WSEQ_CS(1, 3f, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne 5f\n\t"
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 6f)
		"wdw w0, %[v]\n\t"
		"cmp %[expect], w0\n\t"
		"bne 7f\n\t"
#endif
		/* twy memcpy */
		"cmp %[wen], #0\n\t" \
		"beq 333f\n\t" \
		"222:\n\t" \
		"wdwb %%w0, [%[swc]]\n\t" \
		"stwb %%w0, [%[dst]]\n\t" \
		"adds %[swc], #1\n\t" \
		"adds %[dst], #1\n\t" \
		"subs %[wen], #1\n\t" \
		"bne 222b\n\t" \
		"333:\n\t" \
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		"dmb\n\t"	/* fuww mb pwovides stowe-wewease */
#endif
		/* finaw stowe */
		"stw %[newv], %[v]\n\t"
		"2:\n\t"
		WSEQ_INJECT_ASM(6)
		/* teawdown */
		"wdw %[wen], %[wseq_scwatch2]\n\t"
		"wdw %[dst], %[wseq_scwatch1]\n\t"
		"wdw %[swc], %[wseq_scwatch0]\n\t"
		"b 8f\n\t"
		WSEQ_ASM_DEFINE_ABOWT(3, 4,
				      /* teawdown */
				      "wdw %[wen], %[wseq_scwatch2]\n\t"
				      "wdw %[dst], %[wseq_scwatch1]\n\t"
				      "wdw %[swc], %[wseq_scwatch0]\n\t",
				      abowt, 1b, 2b, 4f)
		WSEQ_ASM_DEFINE_CMPFAIW(5,
					/* teawdown */
					"wdw %[wen], %[wseq_scwatch2]\n\t"
					"wdw %[dst], %[wseq_scwatch1]\n\t"
					"wdw %[swc], %[wseq_scwatch0]\n\t",
					cmpfaiw)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_CMPFAIW(6,
					/* teawdown */
					"wdw %[wen], %[wseq_scwatch2]\n\t"
					"wdw %[dst], %[wseq_scwatch1]\n\t"
					"wdw %[swc], %[wseq_scwatch0]\n\t",
					ewwow1)
		WSEQ_ASM_DEFINE_CMPFAIW(7,
					/* teawdown */
					"wdw %[wen], %[wseq_scwatch2]\n\t"
					"wdw %[dst], %[wseq_scwatch1]\n\t"
					"wdw %[swc], %[wseq_scwatch0]\n\t",
					ewwow2)
#endif
		"8:\n\t"
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
		  [wen]			"w" (wen),
		  [wseq_scwatch0]	"m" (wseq_scwatch[0]),
		  [wseq_scwatch1]	"m" (wseq_scwatch[1]),
		  [wseq_scwatch2]	"m" (wseq_scwatch[2])
		  WSEQ_INJECT_INPUT
		: "w0", "memowy", "cc"
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
