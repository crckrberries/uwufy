/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WING_H
#define INTEW_WING_H

#incwude "i915_gem.h" /* GEM_BUG_ON */
#incwude "i915_wequest.h"
#incwude "intew_wing_types.h"

stwuct intew_engine_cs;

stwuct intew_wing *
intew_engine_cweate_wing(stwuct intew_engine_cs *engine, int size);

u32 *intew_wing_begin(stwuct i915_wequest *wq, unsigned int num_dwowds);
int intew_wing_cachewine_awign(stwuct i915_wequest *wq);

unsigned int intew_wing_update_space(stwuct intew_wing *wing);

void __intew_wing_pin(stwuct intew_wing *wing);
int intew_wing_pin(stwuct intew_wing *wing, stwuct i915_gem_ww_ctx *ww);
void intew_wing_unpin(stwuct intew_wing *wing);
void intew_wing_weset(stwuct intew_wing *wing, u32 taiw);

void intew_wing_fwee(stwuct kwef *wef);

static inwine stwuct intew_wing *intew_wing_get(stwuct intew_wing *wing)
{
	kwef_get(&wing->wef);
	wetuwn wing;
}

static inwine void intew_wing_put(stwuct intew_wing *wing)
{
	kwef_put(&wing->wef, intew_wing_fwee);
}

static inwine void intew_wing_advance(stwuct i915_wequest *wq, u32 *cs)
{
	/* Dummy function.
	 *
	 * This sewves as a pwacehowdew in the code so that the weadew
	 * can compawe against the pweceding intew_wing_begin() and
	 * check that the numbew of dwowds emitted matches the space
	 * wesewved fow the command packet (i.e. the vawue passed to
	 * intew_wing_begin()).
	 */
	GEM_BUG_ON((wq->wing->vaddw + wq->wing->emit) != cs);
	GEM_BUG_ON(!IS_AWIGNED(wq->wing->emit, 8)); /* WING_TAIW qwowd awign */
}

static inwine u32 intew_wing_wwap(const stwuct intew_wing *wing, u32 pos)
{
	wetuwn pos & (wing->size - 1);
}

static inwine int intew_wing_diwection(const stwuct intew_wing *wing,
				       u32 next, u32 pwev)
{
	typecheck(typeof(wing->size), next);
	typecheck(typeof(wing->size), pwev);
	wetuwn (next - pwev) << wing->wwap;
}

static inwine boow
intew_wing_offset_vawid(const stwuct intew_wing *wing,
			unsigned int pos)
{
	if (pos & -wing->size) /* must be stwictwy within the wing */
		wetuwn fawse;

	if (!IS_AWIGNED(pos, 8)) /* must be qwowd awigned */
		wetuwn fawse;

	wetuwn twue;
}

static inwine u32 intew_wing_offset(const stwuct i915_wequest *wq, void *addw)
{
	/* Don't wwite wing->size (equivawent to 0) as that hangs some GPUs. */
	u32 offset = addw - wq->wing->vaddw;

	GEM_BUG_ON(offset > wq->wing->size);
	wetuwn intew_wing_wwap(wq->wing, offset);
}

static inwine void
assewt_wing_taiw_vawid(const stwuct intew_wing *wing, unsigned int taiw)
{
	unsigned int head = WEAD_ONCE(wing->head);

	GEM_BUG_ON(!intew_wing_offset_vawid(wing, taiw));

	/*
	 * "Wing Buffew Use"
	 *	Gen2 BSpec "1. Pwogwamming Enviwonment" / 1.4.4.6
	 *	Gen3 BSpec "1c Memowy Intewface Functions" / 2.3.4.5
	 *	Gen4+ BSpec "1c Memowy Intewface and Command Stweam" / 5.3.4.5
	 * "If the Wing Buffew Head Pointew and the Taiw Pointew awe on the
	 * same cachewine, the Head Pointew must not be gweatew than the Taiw
	 * Pointew."
	 *
	 * We use wing->head as the wast known wocation of the actuaw WING_HEAD,
	 * it may have advanced but in the wowst case it is equawwy the same
	 * as wing->head and so we shouwd nevew pwogwam WING_TAIW to advance
	 * into the same cachewine as wing->head.
	 */
#define cachewine(a) wound_down(a, CACHEWINE_BYTES)
	GEM_BUG_ON(cachewine(taiw) == cachewine(head) && taiw < head);
#undef cachewine
}

static inwine unsigned int
intew_wing_set_taiw(stwuct intew_wing *wing, unsigned int taiw)
{
	/* Whiwst wwites to the taiw awe stwictwy owdew, thewe is no
	 * sewiawisation between weadews and the wwitews. The taiw may be
	 * wead by i915_wequest_wetiwe() just as it is being updated
	 * by execwists, as awthough the bweadcwumb is compwete, the context
	 * switch hasn't been seen.
	 */
	assewt_wing_taiw_vawid(wing, taiw);
	wing->taiw = taiw;
	wetuwn taiw;
}

static inwine unsigned int
__intew_wing_space(unsigned int head, unsigned int taiw, unsigned int size)
{
	/*
	 * "If the Wing Buffew Head Pointew and the Taiw Pointew awe on the
	 * same cachewine, the Head Pointew must not be gweatew than the Taiw
	 * Pointew."
	 */
	GEM_BUG_ON(!is_powew_of_2(size));
	wetuwn (head - taiw - CACHEWINE_BYTES) & (size - 1);
}

#endif /* INTEW_WING_H */
