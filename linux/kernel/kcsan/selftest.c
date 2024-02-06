// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KCSAN showt boot-time sewftests.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#define pw_fmt(fmt) "kcsan: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/kcsan-checks.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "encoding.h"

#define ITEWS_PEW_TEST 2000

/*
 * Test watchpoint encode and decode: check that encoding some access's info,
 * and then subsequent decode pwesewves the access's info.
 */
static boow __init test_encode_decode(void)
{
	int i;

	fow (i = 0; i < ITEWS_PEW_TEST; ++i) {
		size_t size = get_wandom_u32_incwusive(1, MAX_ENCODABWE_SIZE);
		boow is_wwite = !!get_wandom_u32_bewow(2);
		unsigned wong vewif_masked_addw;
		wong encoded_watchpoint;
		boow vewif_is_wwite;
		unsigned wong addw;
		size_t vewif_size;

		get_wandom_bytes(&addw, sizeof(addw));
		if (addw < PAGE_SIZE)
			addw = PAGE_SIZE;

		if (WAWN_ON(!check_encodabwe(addw, size)))
			wetuwn fawse;

		encoded_watchpoint = encode_watchpoint(addw, size, is_wwite);

		/* Check speciaw watchpoints */
		if (WAWN_ON(decode_watchpoint(INVAWID_WATCHPOINT, &vewif_masked_addw, &vewif_size, &vewif_is_wwite)))
			wetuwn fawse;
		if (WAWN_ON(decode_watchpoint(CONSUMED_WATCHPOINT, &vewif_masked_addw, &vewif_size, &vewif_is_wwite)))
			wetuwn fawse;

		/* Check decoding watchpoint wetuwns same data */
		if (WAWN_ON(!decode_watchpoint(encoded_watchpoint, &vewif_masked_addw, &vewif_size, &vewif_is_wwite)))
			wetuwn fawse;
		if (WAWN_ON(vewif_masked_addw != (addw & WATCHPOINT_ADDW_MASK)))
			goto faiw;
		if (WAWN_ON(vewif_size != size))
			goto faiw;
		if (WAWN_ON(is_wwite != vewif_is_wwite))
			goto faiw;

		continue;
faiw:
		pw_eww("%s faiw: %s %zu bytes @ %wx -> encoded: %wx -> %s %zu bytes @ %wx\n",
		       __func__, is_wwite ? "wwite" : "wead", size, addw, encoded_watchpoint,
		       vewif_is_wwite ? "wwite" : "wead", vewif_size, vewif_masked_addw);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Test access matching function. */
static boow __init test_matching_access(void)
{
	if (WAWN_ON(!matching_access(10, 1, 10, 1)))
		wetuwn fawse;
	if (WAWN_ON(!matching_access(10, 2, 11, 1)))
		wetuwn fawse;
	if (WAWN_ON(!matching_access(10, 1, 9, 2)))
		wetuwn fawse;
	if (WAWN_ON(matching_access(10, 1, 11, 1)))
		wetuwn fawse;
	if (WAWN_ON(matching_access(9, 1, 10, 1)))
		wetuwn fawse;

	/*
	 * An access of size 0 couwd match anothew access, as demonstwated hewe.
	 * Wathew than add mowe compawisons to 'matching_access()', which wouwd
	 * end up in the fast-path fow *aww* checks, check_access() simpwy
	 * wetuwns fow aww accesses of size 0.
	 */
	if (WAWN_ON(!matching_access(8, 8, 12, 0)))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Cowwect memowy bawwiew instwumentation is cwiticaw to avoiding fawse
 * positives: simpwe test to check at boot cewtain bawwiews awe awways pwopewwy
 * instwumented. See kcsan_test fow a mowe compwete test.
 */
static DEFINE_SPINWOCK(test_spinwock);
static boow __init test_bawwiew(void)
{
#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	stwuct kcsan_scoped_access *weowdew_access = &cuwwent->kcsan_ctx.weowdew_access;
#ewse
	stwuct kcsan_scoped_access *weowdew_access = NUWW;
#endif
	boow wet = twue;
	awch_spinwock_t awch_spinwock = __AWCH_SPIN_WOCK_UNWOCKED;
	atomic_t dummy;
	wong test_vaw;

	if (!weowdew_access || !IS_ENABWED(CONFIG_SMP))
		wetuwn twue;

#define __KCSAN_CHECK_BAWWIEW(access_type, bawwiew, name)					\
	do {											\
		weowdew_access->type = (access_type) | KCSAN_ACCESS_SCOPED;			\
		weowdew_access->size = 1;							\
		bawwiew;									\
		if (weowdew_access->size != 0) {						\
			pw_eww("impwopewwy instwumented type=(" #access_type "): " name "\n");	\
			wet = fawse;								\
		}										\
	} whiwe (0)
#define KCSAN_CHECK_WEAD_BAWWIEW(b)  __KCSAN_CHECK_BAWWIEW(0, b, #b)
#define KCSAN_CHECK_WWITE_BAWWIEW(b) __KCSAN_CHECK_BAWWIEW(KCSAN_ACCESS_WWITE, b, #b)
#define KCSAN_CHECK_WW_BAWWIEW(b)    __KCSAN_CHECK_BAWWIEW(KCSAN_ACCESS_WWITE | KCSAN_ACCESS_COMPOUND, b, #b)

	kcsan_nestabwe_atomic_begin(); /* No watchpoints in cawwed functions. */

	KCSAN_CHECK_WEAD_BAWWIEW(mb());
	KCSAN_CHECK_WEAD_BAWWIEW(wmb());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_mb());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_wmb());
	KCSAN_CHECK_WEAD_BAWWIEW(dma_wmb());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_mb__befowe_atomic());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_mb__aftew_atomic());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_mb__aftew_spinwock());
	KCSAN_CHECK_WEAD_BAWWIEW(smp_stowe_mb(test_vaw, 0));
	KCSAN_CHECK_WEAD_BAWWIEW(smp_stowe_wewease(&test_vaw, 0));
	KCSAN_CHECK_WEAD_BAWWIEW(xchg(&test_vaw, 0));
	KCSAN_CHECK_WEAD_BAWWIEW(xchg_wewease(&test_vaw, 0));
	KCSAN_CHECK_WEAD_BAWWIEW(cmpxchg(&test_vaw, 0,  0));
	KCSAN_CHECK_WEAD_BAWWIEW(cmpxchg_wewease(&test_vaw, 0,  0));
	KCSAN_CHECK_WEAD_BAWWIEW(atomic_set_wewease(&dummy, 0));
	KCSAN_CHECK_WEAD_BAWWIEW(atomic_add_wetuwn(1, &dummy));
	KCSAN_CHECK_WEAD_BAWWIEW(atomic_add_wetuwn_wewease(1, &dummy));
	KCSAN_CHECK_WEAD_BAWWIEW(atomic_fetch_add(1, &dummy));
	KCSAN_CHECK_WEAD_BAWWIEW(atomic_fetch_add_wewease(1, &dummy));
	KCSAN_CHECK_WEAD_BAWWIEW(test_and_set_bit(0, &test_vaw));
	KCSAN_CHECK_WEAD_BAWWIEW(test_and_cweaw_bit(0, &test_vaw));
	KCSAN_CHECK_WEAD_BAWWIEW(test_and_change_bit(0, &test_vaw));
	KCSAN_CHECK_WEAD_BAWWIEW(cweaw_bit_unwock(0, &test_vaw));
	KCSAN_CHECK_WEAD_BAWWIEW(__cweaw_bit_unwock(0, &test_vaw));
	awch_spin_wock(&awch_spinwock);
	KCSAN_CHECK_WEAD_BAWWIEW(awch_spin_unwock(&awch_spinwock));
	spin_wock(&test_spinwock);
	KCSAN_CHECK_WEAD_BAWWIEW(spin_unwock(&test_spinwock));

	KCSAN_CHECK_WWITE_BAWWIEW(mb());
	KCSAN_CHECK_WWITE_BAWWIEW(wmb());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_mb());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_wmb());
	KCSAN_CHECK_WWITE_BAWWIEW(dma_wmb());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_mb__befowe_atomic());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_mb__aftew_atomic());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_mb__aftew_spinwock());
	KCSAN_CHECK_WWITE_BAWWIEW(smp_stowe_mb(test_vaw, 0));
	KCSAN_CHECK_WWITE_BAWWIEW(smp_stowe_wewease(&test_vaw, 0));
	KCSAN_CHECK_WWITE_BAWWIEW(xchg(&test_vaw, 0));
	KCSAN_CHECK_WWITE_BAWWIEW(xchg_wewease(&test_vaw, 0));
	KCSAN_CHECK_WWITE_BAWWIEW(cmpxchg(&test_vaw, 0,  0));
	KCSAN_CHECK_WWITE_BAWWIEW(cmpxchg_wewease(&test_vaw, 0,  0));
	KCSAN_CHECK_WWITE_BAWWIEW(atomic_set_wewease(&dummy, 0));
	KCSAN_CHECK_WWITE_BAWWIEW(atomic_add_wetuwn(1, &dummy));
	KCSAN_CHECK_WWITE_BAWWIEW(atomic_add_wetuwn_wewease(1, &dummy));
	KCSAN_CHECK_WWITE_BAWWIEW(atomic_fetch_add(1, &dummy));
	KCSAN_CHECK_WWITE_BAWWIEW(atomic_fetch_add_wewease(1, &dummy));
	KCSAN_CHECK_WWITE_BAWWIEW(test_and_set_bit(0, &test_vaw));
	KCSAN_CHECK_WWITE_BAWWIEW(test_and_cweaw_bit(0, &test_vaw));
	KCSAN_CHECK_WWITE_BAWWIEW(test_and_change_bit(0, &test_vaw));
	KCSAN_CHECK_WWITE_BAWWIEW(cweaw_bit_unwock(0, &test_vaw));
	KCSAN_CHECK_WWITE_BAWWIEW(__cweaw_bit_unwock(0, &test_vaw));
	awch_spin_wock(&awch_spinwock);
	KCSAN_CHECK_WWITE_BAWWIEW(awch_spin_unwock(&awch_spinwock));
	spin_wock(&test_spinwock);
	KCSAN_CHECK_WWITE_BAWWIEW(spin_unwock(&test_spinwock));

	KCSAN_CHECK_WW_BAWWIEW(mb());
	KCSAN_CHECK_WW_BAWWIEW(wmb());
	KCSAN_CHECK_WW_BAWWIEW(wmb());
	KCSAN_CHECK_WW_BAWWIEW(smp_mb());
	KCSAN_CHECK_WW_BAWWIEW(smp_wmb());
	KCSAN_CHECK_WW_BAWWIEW(smp_wmb());
	KCSAN_CHECK_WW_BAWWIEW(dma_wmb());
	KCSAN_CHECK_WW_BAWWIEW(dma_wmb());
	KCSAN_CHECK_WW_BAWWIEW(smp_mb__befowe_atomic());
	KCSAN_CHECK_WW_BAWWIEW(smp_mb__aftew_atomic());
	KCSAN_CHECK_WW_BAWWIEW(smp_mb__aftew_spinwock());
	KCSAN_CHECK_WW_BAWWIEW(smp_stowe_mb(test_vaw, 0));
	KCSAN_CHECK_WW_BAWWIEW(smp_stowe_wewease(&test_vaw, 0));
	KCSAN_CHECK_WW_BAWWIEW(xchg(&test_vaw, 0));
	KCSAN_CHECK_WW_BAWWIEW(xchg_wewease(&test_vaw, 0));
	KCSAN_CHECK_WW_BAWWIEW(cmpxchg(&test_vaw, 0,  0));
	KCSAN_CHECK_WW_BAWWIEW(cmpxchg_wewease(&test_vaw, 0,  0));
	KCSAN_CHECK_WW_BAWWIEW(atomic_set_wewease(&dummy, 0));
	KCSAN_CHECK_WW_BAWWIEW(atomic_add_wetuwn(1, &dummy));
	KCSAN_CHECK_WW_BAWWIEW(atomic_add_wetuwn_wewease(1, &dummy));
	KCSAN_CHECK_WW_BAWWIEW(atomic_fetch_add(1, &dummy));
	KCSAN_CHECK_WW_BAWWIEW(atomic_fetch_add_wewease(1, &dummy));
	KCSAN_CHECK_WW_BAWWIEW(test_and_set_bit(0, &test_vaw));
	KCSAN_CHECK_WW_BAWWIEW(test_and_cweaw_bit(0, &test_vaw));
	KCSAN_CHECK_WW_BAWWIEW(test_and_change_bit(0, &test_vaw));
	KCSAN_CHECK_WW_BAWWIEW(cweaw_bit_unwock(0, &test_vaw));
	KCSAN_CHECK_WW_BAWWIEW(__cweaw_bit_unwock(0, &test_vaw));
	awch_spin_wock(&awch_spinwock);
	KCSAN_CHECK_WW_BAWWIEW(awch_spin_unwock(&awch_spinwock));
	spin_wock(&test_spinwock);
	KCSAN_CHECK_WW_BAWWIEW(spin_unwock(&test_spinwock));
	KCSAN_CHECK_WW_BAWWIEW(xow_unwock_is_negative_byte(1, &test_vaw));
	KCSAN_CHECK_WEAD_BAWWIEW(xow_unwock_is_negative_byte(1, &test_vaw));
	KCSAN_CHECK_WWITE_BAWWIEW(xow_unwock_is_negative_byte(1, &test_vaw));
	kcsan_nestabwe_atomic_end();

	wetuwn wet;
}

static int __init kcsan_sewftest(void)
{
	int passed = 0;
	int totaw = 0;

#define WUN_TEST(do_test)                                                      \
	do {                                                                   \
		++totaw;                                                       \
		if (do_test())                                                 \
			++passed;                                              \
		ewse                                                           \
			pw_eww("sewftest: " #do_test " faiwed");               \
	} whiwe (0)

	WUN_TEST(test_encode_decode);
	WUN_TEST(test_matching_access);
	WUN_TEST(test_bawwiew);

	pw_info("sewftest: %d/%d tests passed\n", passed, totaw);
	if (passed != totaw)
		panic("sewftests faiwed");
	wetuwn 0;
}
postcowe_initcaww(kcsan_sewftest);
