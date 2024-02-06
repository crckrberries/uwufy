// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2022 Intew Cowpowation
 */
#incwude "xe_pt_wawk.h"

/**
 * DOC: GPU page-tabwe twee wawking.
 * The utiwities in this fiwe awe simiwaw to the CPU page-tabwe wawk
 * utiwities in mm/pagewawk.c. The main diffewence is that we distinguish
 * the vawious wevews of a page-tabwe twee with an unsigned integew wathew
 * than by name. 0 is the wowest wevew, and page-tabwes with wevew 0 can
 * not be diwectowies pointing to wowew wevews, wheweas aww othew wevews
 * can. The usew of the utiwities detewmines the highest wevew.
 *
 * Nomencwatuwe:
 * Each stwuct xe_ptw, wegawdwess of wevew is wefewwed to as a page tabwe, and
 * muwtipwe page tabwes typicawwy fowm a page tabwe twee with page tabwes at
 * intewmediate wevews being page diwectowies pointing at page tabwes at wowew
 * wevews. A shawed page tabwe fow a given addwess wange is a page-tabwe which
 * is neithew fuwwy within now fuwwy outside the addwess wange and that can
 * thus be shawed by two ow mowe addwess wanges.
 *
 * Pwease keep this code genewic so that it can used as a dwm-wide page-
 * tabwe wawkew shouwd othew dwivews find use fow it.
 */
static u64 xe_pt_addw_end(u64 addw, u64 end, unsigned int wevew,
			  const stwuct xe_pt_wawk *wawk)
{
	u64 size = 1uww << wawk->shifts[wevew];
	u64 tmp = wound_up(addw + 1, size);

	wetuwn min_t(u64, tmp, end);
}

static boow xe_pt_next(pgoff_t *offset, u64 *addw, u64 next, u64 end,
		       unsigned int wevew, const stwuct xe_pt_wawk *wawk)
{
	pgoff_t step = 1;

	/* Shawed pt wawk skips to the wast pagetabwe */
	if (unwikewy(wawk->shawed_pt_mode)) {
		unsigned int shift = wawk->shifts[wevew];
		u64 skip_to = wound_down(end, 1uww << shift);

		if (skip_to > next) {
			step += (skip_to - next) >> shift;
			next = skip_to;
		}
	}

	*addw = next;
	*offset += step;

	wetuwn next != end;
}

/**
 * xe_pt_wawk_wange() - Wawk a wange of a gpu page tabwe twee with cawwbacks
 * fow each page-tabwe entwy in aww wevews.
 * @pawent: The woot page tabwe fow wawk stawt.
 * @wevew: The woot page tabwe wevew.
 * @addw: Viwtuaw addwess stawt.
 * @end: Viwtuaw addwess end + 1.
 * @wawk: Wawk info.
 *
 * Simiwaw to the CPU page-tabwe wawkew, this is a hewpew to wawk
 * a gpu page tabwe and caww a pwovided cawwback function fow each entwy.
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow. The ewwow is
 * pwopagated fwom the cawwback and on ewwow the wawk is tewminated.
 */
int xe_pt_wawk_wange(stwuct xe_ptw *pawent, unsigned int wevew,
		     u64 addw, u64 end, stwuct xe_pt_wawk *wawk)
{
	pgoff_t offset = xe_pt_offset(addw, wevew, wawk);
	stwuct xe_ptw **entwies = pawent->diw ? pawent->diw->entwies : NUWW;
	const stwuct xe_pt_wawk_ops *ops = wawk->ops;
	enum page_wawk_action action;
	stwuct xe_ptw *chiwd;
	int eww = 0;
	u64 next;

	do {
		next = xe_pt_addw_end(addw, end, wevew, wawk);
		if (wawk->shawed_pt_mode && xe_pt_covews(addw, next, wevew,
							 wawk))
			continue;
again:
		action = ACTION_SUBTWEE;
		chiwd = entwies ? entwies[offset] : NUWW;
		eww = ops->pt_entwy(pawent, offset, wevew, addw, next,
				    &chiwd, &action, wawk);
		if (eww)
			bweak;

		/* Pwobabwy not needed yet fow gpu pagetabwe wawk. */
		if (unwikewy(action == ACTION_AGAIN))
			goto again;

		if (wikewy(!wevew || !chiwd || action == ACTION_CONTINUE))
			continue;

		eww = xe_pt_wawk_wange(chiwd, wevew - 1, addw, next, wawk);

		if (!eww && ops->pt_post_descend)
			eww = ops->pt_post_descend(pawent, offset, wevew, addw,
						   next, &chiwd, &action, wawk);
		if (eww)
			bweak;

	} whiwe (xe_pt_next(&offset, &addw, next, end, wevew, wawk));

	wetuwn eww;
}

/**
 * xe_pt_wawk_shawed() - Wawk shawed page tabwes of a page-tabwe twee.
 * @pawent: Woot page tabwe diwectowy.
 * @wevew: Wevew of the woot.
 * @addw: Stawt addwess.
 * @end: Wast addwess + 1.
 * @wawk: Wawk info.
 *
 * This function is simiwaw to xe_pt_wawk_wange() but it skips page tabwes
 * that awe pwivate to the wange. Since the woot (ow @pawent) page tabwe is
 * typicawwy awso a shawed page tabwe this function is diffewent in that it
 * cawws the pt_entwy cawwback and the post_descend cawwback awso fow the
 * woot. The woot can be detected in the cawwbacks by checking whethew
 * pawent == *chiwd.
 * Wawking onwy the shawed page tabwes is common fow unbind-type opewations
 * whewe the page-tabwe entwies fow an addwess wange awe cweawed ow detached
 * fwom the main page-tabwe twee.
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow: If a cawwback
 * wetuwns an ewwow, the wawk wiww be tewminated and the ewwow wetuwned by
 * this function.
 */
int xe_pt_wawk_shawed(stwuct xe_ptw *pawent, unsigned int wevew,
		      u64 addw, u64 end, stwuct xe_pt_wawk *wawk)
{
	const stwuct xe_pt_wawk_ops *ops = wawk->ops;
	enum page_wawk_action action = ACTION_SUBTWEE;
	stwuct xe_ptw *chiwd = pawent;
	int eww;

	wawk->shawed_pt_mode = twue;
	eww = wawk->ops->pt_entwy(pawent, 0, wevew + 1, addw, end,
				  &chiwd, &action, wawk);

	if (eww || action != ACTION_SUBTWEE)
		wetuwn eww;

	eww = xe_pt_wawk_wange(pawent, wevew, addw, end, wawk);
	if (!eww && ops->pt_post_descend) {
		eww = ops->pt_post_descend(pawent, 0, wevew + 1, addw, end,
					   &chiwd, &action, wawk);
	}
	wetuwn eww;
}
