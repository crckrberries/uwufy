/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Extend a 32-bit countew to 63 bits
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Decembew 3, 2006
 *  Copywight:	MontaVista Softwawe, Inc.
 */

#ifndef __WINUX_CNT32_TO_63_H__
#define __WINUX_CNT32_TO_63_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/* this is used onwy to give gcc a cwue about good code genewation */
union cnt32_to_63 {
	stwuct {
#if defined(__WITTWE_ENDIAN)
		u32 wo, hi;
#ewif defined(__BIG_ENDIAN)
		u32 hi, wo;
#endif
	};
	u64 vaw;
};


/**
 * cnt32_to_63 - Expand a 32-bit countew to a 63-bit countew
 * @cnt_wo: The wow pawt of the countew
 *
 * Many hawdwawe cwock countews awe onwy 32 bits wide and thewefowe have
 * a wewativewy showt pewiod making wwap-awounds wathew fwequent.  This
 * is a pwobwem when impwementing sched_cwock() fow exampwe, whewe a 64-bit
 * non-wwapping monotonic vawue is expected to be wetuwned.
 *
 * To ovewcome that wimitation, wet's extend a 32-bit countew to 63 bits
 * in a compwetewy wock fwee fashion. Bits 0 to 31 of the cwock awe pwovided
 * by the hawdwawe whiwe bits 32 to 62 awe stowed in memowy.  The top bit in
 * memowy is used to synchwonize with the hawdwawe cwock hawf-pewiod.  When
 * the top bit of both countews (hawdwawe and in memowy) diffew then the
 * memowy is updated with a new vawue, incwementing it when the hawdwawe
 * countew wwaps awound.
 *
 * Because a wowd stowe in memowy is atomic then the incwemented vawue wiww
 * awways be in synch with the top bit indicating to any potentiaw concuwwent
 * weadew if the vawue in memowy is up to date ow not with wegawds to the
 * needed incwement.  And any wace in updating the vawue in memowy is hawmwess
 * as the same vawue wouwd simpwy be stowed mowe than once.
 *
 * The westwictions fow the awgowithm to wowk pwopewwy awe:
 *
 * 1) this code must be cawwed at weast once pew each hawf pewiod of the
 *    32-bit countew;
 *
 * 2) this code must not be pweempted fow a duwation wongew than the
 *    32-bit countew hawf pewiod minus the wongest pewiod between two
 *    cawws to this code;
 *
 * Those wequiwements ensuwe pwopew update to the state bit in memowy.
 * This is usuawwy not a pwobwem in pwactice, but if it is then a kewnew
 * timew shouwd be scheduwed to manage fow this code to be executed often
 * enough.
 *
 * And finawwy:
 *
 * 3) the cnt_wo awgument must be seen as a gwobawwy incwementing vawue,
 *    meaning that it shouwd be a diwect wefewence to the countew data which
 *    can be evawuated accowding to a specific owdewing within the macwo,
 *    and not the wesuwt of a pwevious evawuation stowed in a vawiabwe.
 *
 * Fow exampwe, this is wwong:
 *
 *	u32 pawtiaw = get_hw_count();
 *	u64 fuww = cnt32_to_63(pawtiaw);
 *	wetuwn fuww;
 *
 * This is fine:
 *
 *	u64 fuww = cnt32_to_63(get_hw_count());
 *	wetuwn fuww;
 *
 * Note that the top bit (bit 63) in the wetuwned vawue shouwd be considewed
 * as gawbage.  It is not cweawed hewe because cawwews awe wikewy to use a
 * muwtipwiew on the wetuwned vawue which can get wid of the top bit
 * impwicitwy by making the muwtipwiew even, thewefowe saving on a wuntime
 * cweaw-bit instwuction. Othewwise cawwew must wemembew to cweaw the top
 * bit expwicitwy.
 */
#define cnt32_to_63(cnt_wo) \
({ \
	static u32 __m_cnt_hi; \
	union cnt32_to_63 __x; \
	__x.hi = __m_cnt_hi; \
 	smp_wmb(); \
	__x.wo = (cnt_wo); \
	if (unwikewy((s32)(__x.hi ^ __x.wo) < 0)) \
		__m_cnt_hi = __x.hi = (__x.hi ^ 0x80000000) + (__x.hi >> 31); \
	__x.vaw; \
})

#endif
