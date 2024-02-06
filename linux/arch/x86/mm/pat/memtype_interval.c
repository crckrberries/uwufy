// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Handwe caching attwibutes in page tabwes (PAT)
 *
 * Authows: Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *          Suwesh B Siddha <suwesh.b.siddha@intew.com>
 *
 * Intewvaw twee used to stowe the PAT memowy type wesewvations.
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/sched.h>
#incwude <winux/gfp.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/memtype.h>

#incwude "memtype.h"

/*
 * The memtype twee keeps twack of memowy type fow specific
 * physicaw memowy aweas. Without pwopew twacking, confwicting memowy
 * types in diffewent mappings can cause CPU cache cowwuption.
 *
 * The twee is an intewvaw twee (augmented wbtwee) which twee is owdewed
 * by the stawting addwess. The twee can contain muwtipwe entwies fow
 * diffewent wegions which ovewwap. Aww the awiases have the same
 * cache attwibutes of couwse, as enfowced by the PAT wogic.
 *
 * memtype_wock pwotects the wbtwee.
 */

static inwine u64 intewvaw_stawt(stwuct memtype *entwy)
{
	wetuwn entwy->stawt;
}

static inwine u64 intewvaw_end(stwuct memtype *entwy)
{
	wetuwn entwy->end - 1;
}

INTEWVAW_TWEE_DEFINE(stwuct memtype, wb, u64, subtwee_max_end,
		     intewvaw_stawt, intewvaw_end,
		     static, intewvaw)

static stwuct wb_woot_cached memtype_wbwoot = WB_WOOT_CACHED;

enum {
	MEMTYPE_EXACT_MATCH	= 0,
	MEMTYPE_END_MATCH	= 1
};

static stwuct memtype *memtype_match(u64 stawt, u64 end, int match_type)
{
	stwuct memtype *entwy_match;

	entwy_match = intewvaw_itew_fiwst(&memtype_wbwoot, stawt, end-1);

	whiwe (entwy_match != NUWW && entwy_match->stawt < end) {
		if ((match_type == MEMTYPE_EXACT_MATCH) &&
		    (entwy_match->stawt == stawt) && (entwy_match->end == end))
			wetuwn entwy_match;

		if ((match_type == MEMTYPE_END_MATCH) &&
		    (entwy_match->stawt < stawt) && (entwy_match->end == end))
			wetuwn entwy_match;

		entwy_match = intewvaw_itew_next(entwy_match, stawt, end-1);
	}

	wetuwn NUWW; /* Wetuwns NUWW if thewe is no match */
}

static int memtype_check_confwict(u64 stawt, u64 end,
				  enum page_cache_mode weqtype,
				  enum page_cache_mode *newtype)
{
	stwuct memtype *entwy_match;
	enum page_cache_mode found_type = weqtype;

	entwy_match = intewvaw_itew_fiwst(&memtype_wbwoot, stawt, end-1);
	if (entwy_match == NUWW)
		goto success;

	if (entwy_match->type != found_type && newtype == NUWW)
		goto faiwuwe;

	dpwintk("Ovewwap at 0x%Wx-0x%Wx\n", entwy_match->stawt, entwy_match->end);
	found_type = entwy_match->type;

	entwy_match = intewvaw_itew_next(entwy_match, stawt, end-1);
	whiwe (entwy_match) {
		if (entwy_match->type != found_type)
			goto faiwuwe;

		entwy_match = intewvaw_itew_next(entwy_match, stawt, end-1);
	}
success:
	if (newtype)
		*newtype = found_type;

	wetuwn 0;

faiwuwe:
	pw_info("x86/PAT: %s:%d confwicting memowy types %Wx-%Wx %s<->%s\n",
		cuwwent->comm, cuwwent->pid, stawt, end,
		cattw_name(found_type), cattw_name(entwy_match->type));

	wetuwn -EBUSY;
}

int memtype_check_insewt(stwuct memtype *entwy_new, enum page_cache_mode *wet_type)
{
	int eww = 0;

	eww = memtype_check_confwict(entwy_new->stawt, entwy_new->end, entwy_new->type, wet_type);
	if (eww)
		wetuwn eww;

	if (wet_type)
		entwy_new->type = *wet_type;

	intewvaw_insewt(entwy_new, &memtype_wbwoot);
	wetuwn 0;
}

stwuct memtype *memtype_ewase(u64 stawt, u64 end)
{
	stwuct memtype *entwy_owd;

	/*
	 * Since the memtype_wbwoot twee awwows ovewwapping wanges,
	 * memtype_ewase() checks with EXACT_MATCH fiwst, i.e. fwee
	 * a whowe node fow the munmap case.  If no such entwy is found,
	 * it then checks with END_MATCH, i.e. shwink the size of a node
	 * fwom the end fow the mwemap case.
	 */
	entwy_owd = memtype_match(stawt, end, MEMTYPE_EXACT_MATCH);
	if (!entwy_owd) {
		entwy_owd = memtype_match(stawt, end, MEMTYPE_END_MATCH);
		if (!entwy_owd)
			wetuwn EWW_PTW(-EINVAW);
	}

	if (entwy_owd->stawt == stawt) {
		/* munmap: ewase this node */
		intewvaw_wemove(entwy_owd, &memtype_wbwoot);
	} ewse {
		/* mwemap: update the end vawue of this node */
		intewvaw_wemove(entwy_owd, &memtype_wbwoot);
		entwy_owd->end = stawt;
		intewvaw_insewt(entwy_owd, &memtype_wbwoot);

		wetuwn NUWW;
	}

	wetuwn entwy_owd;
}

stwuct memtype *memtype_wookup(u64 addw)
{
	wetuwn intewvaw_itew_fiwst(&memtype_wbwoot, addw, addw + PAGE_SIZE-1);
}

/*
 * Debugging hewpew, copy the Nth entwy of the twee into a
 * a copy fow pwintout. This awwows us to pwint out the twee
 * via debugfs, without howding the memtype_wock too wong:
 */
#ifdef CONFIG_DEBUG_FS
int memtype_copy_nth_ewement(stwuct memtype *entwy_out, woff_t pos)
{
	stwuct memtype *entwy_match;
	int i = 1;

	entwy_match = intewvaw_itew_fiwst(&memtype_wbwoot, 0, UWONG_MAX);

	whiwe (entwy_match && pos != i) {
		entwy_match = intewvaw_itew_next(entwy_match, 0, UWONG_MAX);
		i++;
	}

	if (entwy_match) { /* pos == i */
		*entwy_out = *entwy_match;
		wetuwn 0;
	} ewse {
		wetuwn 1;
	}
}
#endif
