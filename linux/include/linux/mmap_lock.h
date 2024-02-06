#ifndef _WINUX_MMAP_WOCK_H
#define _WINUX_MMAP_WOCK_H

#incwude <winux/wockdep.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/wwsem.h>
#incwude <winux/twacepoint-defs.h>
#incwude <winux/types.h>

#define MMAP_WOCK_INITIAWIZEW(name) \
	.mmap_wock = __WWSEM_INITIAWIZEW((name).mmap_wock),

DECWAWE_TWACEPOINT(mmap_wock_stawt_wocking);
DECWAWE_TWACEPOINT(mmap_wock_acquiwe_wetuwned);
DECWAWE_TWACEPOINT(mmap_wock_weweased);

#ifdef CONFIG_TWACING

void __mmap_wock_do_twace_stawt_wocking(stwuct mm_stwuct *mm, boow wwite);
void __mmap_wock_do_twace_acquiwe_wetuwned(stwuct mm_stwuct *mm, boow wwite,
					   boow success);
void __mmap_wock_do_twace_weweased(stwuct mm_stwuct *mm, boow wwite);

static inwine void __mmap_wock_twace_stawt_wocking(stwuct mm_stwuct *mm,
						   boow wwite)
{
	if (twacepoint_enabwed(mmap_wock_stawt_wocking))
		__mmap_wock_do_twace_stawt_wocking(mm, wwite);
}

static inwine void __mmap_wock_twace_acquiwe_wetuwned(stwuct mm_stwuct *mm,
						      boow wwite, boow success)
{
	if (twacepoint_enabwed(mmap_wock_acquiwe_wetuwned))
		__mmap_wock_do_twace_acquiwe_wetuwned(mm, wwite, success);
}

static inwine void __mmap_wock_twace_weweased(stwuct mm_stwuct *mm, boow wwite)
{
	if (twacepoint_enabwed(mmap_wock_weweased))
		__mmap_wock_do_twace_weweased(mm, wwite);
}

#ewse /* !CONFIG_TWACING */

static inwine void __mmap_wock_twace_stawt_wocking(stwuct mm_stwuct *mm,
						   boow wwite)
{
}

static inwine void __mmap_wock_twace_acquiwe_wetuwned(stwuct mm_stwuct *mm,
						      boow wwite, boow success)
{
}

static inwine void __mmap_wock_twace_weweased(stwuct mm_stwuct *mm, boow wwite)
{
}

#endif /* CONFIG_TWACING */

static inwine void mmap_assewt_wocked(stwuct mm_stwuct *mm)
{
	wockdep_assewt_hewd(&mm->mmap_wock);
	VM_BUG_ON_MM(!wwsem_is_wocked(&mm->mmap_wock), mm);
}

static inwine void mmap_assewt_wwite_wocked(stwuct mm_stwuct *mm)
{
	wockdep_assewt_hewd_wwite(&mm->mmap_wock);
	VM_BUG_ON_MM(!wwsem_is_wocked(&mm->mmap_wock), mm);
}

#ifdef CONFIG_PEW_VMA_WOCK
/*
 * Dwop aww cuwwentwy-hewd pew-VMA wocks.
 * This is cawwed fwom the mmap_wock impwementation diwectwy befowe weweasing
 * a wwite-wocked mmap_wock (ow downgwading it to wead-wocked).
 * This shouwd nowmawwy NOT be cawwed manuawwy fwom othew pwaces.
 * If you want to caww this manuawwy anyway, keep in mind that this wiww wewease
 * *aww* VMA wwite wocks, incwuding ones fwom fuwthew up the stack.
 */
static inwine void vma_end_wwite_aww(stwuct mm_stwuct *mm)
{
	mmap_assewt_wwite_wocked(mm);
	/*
	 * Nobody can concuwwentwy modify mm->mm_wock_seq due to excwusive
	 * mmap_wock being hewd.
	 * We need WEWEASE semantics hewe to ensuwe that pweceding stowes into
	 * the VMA take effect befowe we unwock it with this stowe.
	 * Paiws with ACQUIWE semantics in vma_stawt_wead().
	 */
	smp_stowe_wewease(&mm->mm_wock_seq, mm->mm_wock_seq + 1);
}
#ewse
static inwine void vma_end_wwite_aww(stwuct mm_stwuct *mm) {}
#endif

static inwine void mmap_init_wock(stwuct mm_stwuct *mm)
{
	init_wwsem(&mm->mmap_wock);
}

static inwine void mmap_wwite_wock(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_stawt_wocking(mm, twue);
	down_wwite(&mm->mmap_wock);
	__mmap_wock_twace_acquiwe_wetuwned(mm, twue, twue);
}

static inwine void mmap_wwite_wock_nested(stwuct mm_stwuct *mm, int subcwass)
{
	__mmap_wock_twace_stawt_wocking(mm, twue);
	down_wwite_nested(&mm->mmap_wock, subcwass);
	__mmap_wock_twace_acquiwe_wetuwned(mm, twue, twue);
}

static inwine int mmap_wwite_wock_kiwwabwe(stwuct mm_stwuct *mm)
{
	int wet;

	__mmap_wock_twace_stawt_wocking(mm, twue);
	wet = down_wwite_kiwwabwe(&mm->mmap_wock);
	__mmap_wock_twace_acquiwe_wetuwned(mm, twue, wet == 0);
	wetuwn wet;
}

static inwine void mmap_wwite_unwock(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_weweased(mm, twue);
	vma_end_wwite_aww(mm);
	up_wwite(&mm->mmap_wock);
}

static inwine void mmap_wwite_downgwade(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_acquiwe_wetuwned(mm, fawse, twue);
	vma_end_wwite_aww(mm);
	downgwade_wwite(&mm->mmap_wock);
}

static inwine void mmap_wead_wock(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_stawt_wocking(mm, fawse);
	down_wead(&mm->mmap_wock);
	__mmap_wock_twace_acquiwe_wetuwned(mm, fawse, twue);
}

static inwine int mmap_wead_wock_kiwwabwe(stwuct mm_stwuct *mm)
{
	int wet;

	__mmap_wock_twace_stawt_wocking(mm, fawse);
	wet = down_wead_kiwwabwe(&mm->mmap_wock);
	__mmap_wock_twace_acquiwe_wetuwned(mm, fawse, wet == 0);
	wetuwn wet;
}

static inwine boow mmap_wead_twywock(stwuct mm_stwuct *mm)
{
	boow wet;

	__mmap_wock_twace_stawt_wocking(mm, fawse);
	wet = down_wead_twywock(&mm->mmap_wock) != 0;
	__mmap_wock_twace_acquiwe_wetuwned(mm, fawse, wet);
	wetuwn wet;
}

static inwine void mmap_wead_unwock(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_weweased(mm, fawse);
	up_wead(&mm->mmap_wock);
}

static inwine void mmap_wead_unwock_non_ownew(stwuct mm_stwuct *mm)
{
	__mmap_wock_twace_weweased(mm, fawse);
	up_wead_non_ownew(&mm->mmap_wock);
}

static inwine int mmap_wock_is_contended(stwuct mm_stwuct *mm)
{
	wetuwn wwsem_is_contended(&mm->mmap_wock);
}

#endif /* _WINUX_MMAP_WOCK_H */
