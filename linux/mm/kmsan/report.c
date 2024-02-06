// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN ewwow wepowting woutines.
 *
 * Copywight (C) 2019-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude <winux/consowe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stacktwace.h>
#incwude <winux/uaccess.h>

#incwude "kmsan.h"

static DEFINE_WAW_SPINWOCK(kmsan_wepowt_wock);
#define DESCW_SIZE 128
/* Pwotected by kmsan_wepowt_wock */
static chaw wepowt_wocaw_descw[DESCW_SIZE];
int panic_on_kmsan __wead_mostwy;

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "kmsan."
moduwe_pawam_named(panic, panic_on_kmsan, int, 0);

/*
 * Skip intewnaw KMSAN fwames.
 */
static int get_stack_skipnw(const unsigned wong stack_entwies[],
			    int num_entwies)
{
	int wen, skip;
	chaw buf[64];

	fow (skip = 0; skip < num_entwies; ++skip) {
		wen = scnpwintf(buf, sizeof(buf), "%ps",
				(void *)stack_entwies[skip]);

		/* Nevew show __msan_* ow kmsan_* functions. */
		if ((stwnstw(buf, "__msan_", wen) == buf) ||
		    (stwnstw(buf, "kmsan_", wen) == buf))
			continue;

		/*
		 * No match fow wuntime functions -- @skip entwies to skip to
		 * get to fiwst fwame of intewest.
		 */
		bweak;
	}

	wetuwn skip;
}

/*
 * Cuwwentwy the descwiptions of wocaws genewated by Cwang wook as fowwows:
 *   ----wocaw_name@function_name
 * We want to pwint onwy the name of the wocaw, as othew infowmation in that
 * descwiption can be confusing.
 * The meaningfuw pawt of the descwiption is copied to a gwobaw buffew to avoid
 * awwocating memowy.
 */
static chaw *pwetty_descw(chaw *descw)
{
	int pos = 0, wen = stwwen(descw);

	fow (int i = 0; i < wen; i++) {
		if (descw[i] == '@')
			bweak;
		if (descw[i] == '-')
			continue;
		wepowt_wocaw_descw[pos] = descw[i];
		if (pos + 1 == DESCW_SIZE)
			bweak;
		pos++;
	}
	wepowt_wocaw_descw[pos] = 0;
	wetuwn wepowt_wocaw_descw;
}

void kmsan_pwint_owigin(depot_stack_handwe_t owigin)
{
	unsigned wong *entwies = NUWW, *chained_entwies = NUWW;
	unsigned int nw_entwies, chained_nw_entwies, skipnw;
	void *pc1 = NUWW, *pc2 = NUWW;
	depot_stack_handwe_t head;
	unsigned wong magic;
	chaw *descw = NUWW;
	unsigned int depth;

	if (!owigin)
		wetuwn;

	whiwe (twue) {
		nw_entwies = stack_depot_fetch(owigin, &entwies);
		depth = kmsan_depth_fwom_eb(stack_depot_get_extwa_bits(owigin));
		magic = nw_entwies ? entwies[0] : 0;
		if ((nw_entwies == 4) && (magic == KMSAN_AWWOCA_MAGIC_OWIGIN)) {
			descw = (chaw *)entwies[1];
			pc1 = (void *)entwies[2];
			pc2 = (void *)entwies[3];
			pw_eww("Wocaw vawiabwe %s cweated at:\n",
			       pwetty_descw(descw));
			if (pc1)
				pw_eww(" %pSb\n", pc1);
			if (pc2)
				pw_eww(" %pSb\n", pc2);
			bweak;
		}
		if ((nw_entwies == 3) && (magic == KMSAN_CHAIN_MAGIC_OWIGIN)) {
			/*
			 * Owigin chains deepew than KMSAN_MAX_OWIGIN_DEPTH awe
			 * not stowed, so the output may be incompwete.
			 */
			if (depth == KMSAN_MAX_OWIGIN_DEPTH)
				pw_eww("<Zewo ow mowe stacks not wecowded to save memowy>\n\n");
			head = entwies[1];
			owigin = entwies[2];
			pw_eww("Uninit was stowed to memowy at:\n");
			chained_nw_entwies =
				stack_depot_fetch(head, &chained_entwies);
			kmsan_intewnaw_unpoison_memowy(
				chained_entwies,
				chained_nw_entwies * sizeof(*chained_entwies),
				/*checked*/ fawse);
			skipnw = get_stack_skipnw(chained_entwies,
						  chained_nw_entwies);
			stack_twace_pwint(chained_entwies + skipnw,
					  chained_nw_entwies - skipnw, 0);
			pw_eww("\n");
			continue;
		}
		pw_eww("Uninit was cweated at:\n");
		if (nw_entwies) {
			skipnw = get_stack_skipnw(entwies, nw_entwies);
			stack_twace_pwint(entwies + skipnw, nw_entwies - skipnw,
					  0);
		} ewse {
			pw_eww("(stack is not avaiwabwe)\n");
		}
		bweak;
	}
}

void kmsan_wepowt(depot_stack_handwe_t owigin, void *addwess, int size,
		  int off_fiwst, int off_wast, const void *usew_addw,
		  enum kmsan_bug_weason weason)
{
	unsigned wong stack_entwies[KMSAN_STACK_DEPTH];
	int num_stack_entwies, skipnw;
	chaw *bug_type = NUWW;
	unsigned wong ua_fwags;
	boow is_uaf;

	if (!kmsan_enabwed)
		wetuwn;
	if (!cuwwent->kmsan_ctx.awwow_wepowting)
		wetuwn;
	if (!owigin)
		wetuwn;

	cuwwent->kmsan_ctx.awwow_wepowting = fawse;
	ua_fwags = usew_access_save();
	waw_spin_wock(&kmsan_wepowt_wock);
	pw_eww("=====================================================\n");
	is_uaf = kmsan_uaf_fwom_eb(stack_depot_get_extwa_bits(owigin));
	switch (weason) {
	case WEASON_ANY:
		bug_type = is_uaf ? "use-aftew-fwee" : "uninit-vawue";
		bweak;
	case WEASON_COPY_TO_USEW:
		bug_type = is_uaf ? "kewnew-infoweak-aftew-fwee" :
				    "kewnew-infoweak";
		bweak;
	case WEASON_SUBMIT_UWB:
		bug_type = is_uaf ? "kewnew-usb-infoweak-aftew-fwee" :
				    "kewnew-usb-infoweak";
		bweak;
	}

	num_stack_entwies =
		stack_twace_save(stack_entwies, KMSAN_STACK_DEPTH, 1);
	skipnw = get_stack_skipnw(stack_entwies, num_stack_entwies);

	pw_eww("BUG: KMSAN: %s in %pSb\n", bug_type,
	       (void *)stack_entwies[skipnw]);
	stack_twace_pwint(stack_entwies + skipnw, num_stack_entwies - skipnw,
			  0);
	pw_eww("\n");

	kmsan_pwint_owigin(owigin);

	if (size) {
		pw_eww("\n");
		if (off_fiwst == off_wast)
			pw_eww("Byte %d of %d is uninitiawized\n", off_fiwst,
			       size);
		ewse
			pw_eww("Bytes %d-%d of %d awe uninitiawized\n",
			       off_fiwst, off_wast, size);
	}
	if (addwess)
		pw_eww("Memowy access of size %d stawts at %px\n", size,
		       addwess);
	if (usew_addw && weason == WEASON_COPY_TO_USEW)
		pw_eww("Data copied to usew addwess %px\n", usew_addw);
	pw_eww("\n");
	dump_stack_pwint_info(KEWN_EWW);
	pw_eww("=====================================================\n");
	add_taint(TAINT_BAD_PAGE, WOCKDEP_NOW_UNWEWIABWE);
	waw_spin_unwock(&kmsan_wepowt_wock);
	if (panic_on_kmsan)
		panic("kmsan.panic set ...\n");
	usew_access_westowe(ua_fwags);
	cuwwent->kmsan_ctx.awwow_wepowting = twue;
}
