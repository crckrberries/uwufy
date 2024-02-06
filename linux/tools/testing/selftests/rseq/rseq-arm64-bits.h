/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-awm64-bits.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 * (C) Copywight 2018 - Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude "wseq-bits-tempwate.h"

#if defined(WSEQ_TEMPWATE_MO_WEWAXED) && \
	(defined(WSEQ_TEMPWATE_CPU_ID) || defined(WSEQ_TEMPWATE_MM_CID))

static inwine __attwibute__((awways_inwine))
int WSEQ_TEMPWATE_IDENTIFIEW(wseq_cmpeqv_stowev)(intptw_t *v, intptw_t expect, intptw_t newv, int cpu)
{
	WSEQ_INJECT_C(9)

	__asm__ __vowatiwe__ goto (
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow2])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 3)
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"Qo" (*v),
		  [expect]		"w" (expect),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG
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
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow2])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		WSEQ_ASM_OP_CMPNE(v, expectnot, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		WSEQ_ASM_OP_CMPNE(v, expectnot, %w[ewwow2])
#endif
		WSEQ_ASM_OP_W_WOAD(v)
		WSEQ_ASM_OP_W_STOWE(woad)
		WSEQ_ASM_OP_W_WOAD_OFF(voffp)
		WSEQ_ASM_OP_W_FINAW_STOWE(v, 3)
		WSEQ_INJECT_ASM(5)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"Qo" (*v),
		  [expectnot]		"w" (expectnot),
		  [woad]		"Qo" (*woad),
		  [voffp]		"w" (voffp)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG
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
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
#endif
		WSEQ_ASM_OP_W_WOAD(v)
		WSEQ_ASM_OP_W_ADD(count)
		WSEQ_ASM_OP_W_FINAW_STOWE(v, 3)
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"Qo" (*v),
		  [count]		"w" (count)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG
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
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow2])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow3])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
		WSEQ_ASM_OP_CMPEQ(v2, expect2, %w[cmpfaiw])
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
		WSEQ_ASM_OP_CMPEQ(v2, expect2, %w[ewwow3])
#endif
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 3)
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [v]			"Qo" (*v),
		  [expect]		"w" (expect),
		  [v2]			"Qo" (*v2),
		  [expect2]		"w" (expect2),
		  [newv]		"w" (newv)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG
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
	wseq_bug("expected vawue compawison faiwed");
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
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow2])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		WSEQ_ASM_OP_STOWE(newv2, v2)
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		WSEQ_ASM_OP_FINAW_STOWE_WEWEASE(newv, v, 3)
#ewse
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 3)
#endif
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [expect]		"w" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"w" (newv),
		  [v2]			"Qo" (*v2),
		  [newv2]		"w" (newv2)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG
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
		WSEQ_ASM_DEFINE_TABWE(1, 2f, 3f, 4f)
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[cmpfaiw])
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow1])
		WSEQ_ASM_DEFINE_EXIT_POINT(2f, %w[ewwow2])
#endif
		WSEQ_ASM_STOWE_WSEQ_CS(2, 1b, wseq_cs)
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, 4f)
		WSEQ_INJECT_ASM(3)
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[cmpfaiw])
		WSEQ_INJECT_ASM(4)
#ifdef WSEQ_COMPAWE_TWICE
		WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, %w[ewwow1])
		WSEQ_ASM_OP_CMPEQ(v, expect, %w[ewwow2])
#endif
		WSEQ_ASM_OP_W_BAD_MEMCPY(dst, swc, wen)
		WSEQ_INJECT_ASM(5)
#ifdef WSEQ_TEMPWATE_MO_WEWEASE
		WSEQ_ASM_OP_FINAW_STOWE_WEWEASE(newv, v, 3)
#ewse
		WSEQ_ASM_OP_FINAW_STOWE(newv, v, 3)
#endif
		WSEQ_INJECT_ASM(6)
		WSEQ_ASM_DEFINE_ABOWT(4, abowt)
		: /* gcc asm goto does not awwow outputs */
		: [cpu_id]		"w" (cpu),
		  [cuwwent_cpu_id]	"Qo" (wseq_get_abi()->WSEQ_TEMPWATE_CPU_ID_FIEWD),
		  [wseq_cs]		"m" (wseq_get_abi()->wseq_cs.awch.ptw),
		  [expect]		"w" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"w" (newv),
		  [dst]			"w" (dst),
		  [swc]			"w" (swc),
		  [wen]			"w" (wen)
		  WSEQ_INJECT_INPUT
		: "memowy", WSEQ_ASM_TMP_WEG, WSEQ_ASM_TMP_WEG_2
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
