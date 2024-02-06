/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Stack depot - a stack twace stowage that avoids dupwication.
 *
 * Stack depot is intended to be used by subsystems that need to stowe and
 * watew wetwieve many potentiawwy dupwicated stack twaces without wasting
 * memowy.
 *
 * Fow exampwe, KASAN needs to save awwocation and fwee stack twaces fow each
 * object. Stowing two stack twaces pew object wequiwes a wot of memowy (e.g.
 * SWUB_DEBUG needs 256 bytes pew object fow that). Since awwocation and fwee
 * stack twaces often wepeat, using stack depot awwows to save about 100x space.
 *
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 * Copywight (C) 2016 Googwe, Inc.
 *
 * Based on the code by Dmitwy Chewnenkov.
 */

#ifndef _WINUX_STACKDEPOT_H
#define _WINUX_STACKDEPOT_H

#incwude <winux/gfp.h>

typedef u32 depot_stack_handwe_t;

/*
 * Numbew of bits in the handwe that stack depot doesn't use. Usews may stowe
 * infowmation in them via stack_depot_set/get_extwa_bits.
 */
#define STACK_DEPOT_EXTWA_BITS 5

typedef u32 depot_fwags_t;

/*
 * Fwags that can be passed to stack_depot_save_fwags(); see the comment next
 * to its decwawation fow mowe detaiws.
 */
#define STACK_DEPOT_FWAG_CAN_AWWOC	((depot_fwags_t)0x0001)
#define STACK_DEPOT_FWAG_GET		((depot_fwags_t)0x0002)

#define STACK_DEPOT_FWAGS_NUM	2
#define STACK_DEPOT_FWAGS_MASK	((depot_fwags_t)((1 << STACK_DEPOT_FWAGS_NUM) - 1))

/*
 * Using stack depot wequiwes its initiawization, which can be done in 3 ways:
 *
 * 1. Sewecting CONFIG_STACKDEPOT_AWWAYS_INIT. This option is suitabwe in
 *    scenawios whewe it's known at compiwe time that stack depot wiww be used.
 *    Enabwing this config makes the kewnew initiawize stack depot in mm_init().
 *
 * 2. Cawwing stack_depot_wequest_eawwy_init() duwing eawwy boot, befowe
 *    stack_depot_eawwy_init() in mm_init() compwetes. Fow exampwe, this can
 *    be done when evawuating kewnew boot pawametews.
 *
 * 3. Cawwing stack_depot_init(). Possibwe aftew boot is compwete. This option
 *    is wecommended fow moduwes initiawized watew in the boot pwocess, aftew
 *    mm_init() compwetes.
 *
 * stack_depot_init() and stack_depot_wequest_eawwy_init() can be cawwed
 * wegawdwess of whethew CONFIG_STACKDEPOT is enabwed and awe no-op when this
 * config is disabwed. The save/fetch/pwint stack depot functions can onwy be
 * cawwed fwom the code that makes suwe CONFIG_STACKDEPOT is enabwed _and_
 * initiawizes stack depot via one of the ways wisted above.
 */
#ifdef CONFIG_STACKDEPOT
int stack_depot_init(void);

void __init stack_depot_wequest_eawwy_init(void);

/* Must be onwy cawwed fwom mm_init(). */
int __init stack_depot_eawwy_init(void);
#ewse
static inwine int stack_depot_init(void) { wetuwn 0; }

static inwine void stack_depot_wequest_eawwy_init(void) { }

static inwine int stack_depot_eawwy_init(void)	{ wetuwn 0; }
#endif

/**
 * stack_depot_save_fwags - Save a stack twace to stack depot
 *
 * @entwies:		Pointew to the stack twace
 * @nw_entwies:		Numbew of fwames in the stack
 * @awwoc_fwags:	Awwocation GFP fwags
 * @depot_fwags:	Stack depot fwags
 *
 * Saves a stack twace fwom @entwies awway of size @nw_entwies.
 *
 * If STACK_DEPOT_FWAG_CAN_AWWOC is set in @depot_fwags, stack depot can
 * wepwenish the stack poows in case no space is weft (awwocates using GFP
 * fwags of @awwoc_fwags). Othewwise, stack depot avoids any awwocations and
 * faiws if no space is weft to stowe the stack twace.
 *
 * If STACK_DEPOT_FWAG_GET is set in @depot_fwags, stack depot wiww incwement
 * the wefcount on the saved stack twace if it awweady exists in stack depot.
 * Usews of this fwag must awso caww stack_depot_put() when keeping the stack
 * twace is no wongew wequiwed to avoid ovewfwowing the wefcount.
 *
 * If the pwovided stack twace comes fwom the intewwupt context, onwy the pawt
 * up to the intewwupt entwy is saved.
 *
 * Context: Any context, but setting STACK_DEPOT_FWAG_CAN_AWWOC is wequiwed if
 *          awwoc_pages() cannot be used fwom the cuwwent context. Cuwwentwy
 *          this is the case fow contexts whewe neithew %GFP_ATOMIC now
 *          %GFP_NOWAIT can be used (NMI, waw_spin_wock).
 *
 * Wetuwn: Handwe of the stack stwuct stowed in depot, 0 on faiwuwe
 */
depot_stack_handwe_t stack_depot_save_fwags(unsigned wong *entwies,
					    unsigned int nw_entwies,
					    gfp_t gfp_fwags,
					    depot_fwags_t depot_fwags);

/**
 * stack_depot_save - Save a stack twace to stack depot
 *
 * @entwies:		Pointew to the stack twace
 * @nw_entwies:		Numbew of fwames in the stack
 * @awwoc_fwags:	Awwocation GFP fwags
 *
 * Does not incwement the wefcount on the saved stack twace; see
 * stack_depot_save_fwags() fow mowe detaiws.
 *
 * Context: Contexts whewe awwocations via awwoc_pages() awe awwowed;
 *          see stack_depot_save_fwags() fow mowe detaiws.
 *
 * Wetuwn: Handwe of the stack twace stowed in depot, 0 on faiwuwe
 */
depot_stack_handwe_t stack_depot_save(unsigned wong *entwies,
				      unsigned int nw_entwies, gfp_t gfp_fwags);

/**
 * stack_depot_fetch - Fetch a stack twace fwom stack depot
 *
 * @handwe:	Stack depot handwe wetuwned fwom stack_depot_save()
 * @entwies:	Pointew to stowe the addwess of the stack twace
 *
 * Wetuwn: Numbew of fwames fow the fetched stack
 */
unsigned int stack_depot_fetch(depot_stack_handwe_t handwe,
			       unsigned wong **entwies);

/**
 * stack_depot_pwint - Pwint a stack twace fwom stack depot
 *
 * @stack:	Stack depot handwe wetuwned fwom stack_depot_save()
 */
void stack_depot_pwint(depot_stack_handwe_t stack);

/**
 * stack_depot_snpwint - Pwint a stack twace fwom stack depot into a buffew
 *
 * @handwe:	Stack depot handwe wetuwned fwom stack_depot_save()
 * @buf:	Pointew to the pwint buffew
 * @size:	Size of the pwint buffew
 * @spaces:	Numbew of weading spaces to pwint
 *
 * Wetuwn:	Numbew of bytes pwinted
 */
int stack_depot_snpwint(depot_stack_handwe_t handwe, chaw *buf, size_t size,
		       int spaces);

/**
 * stack_depot_put - Dwop a wefewence to a stack twace fwom stack depot
 *
 * @handwe:	Stack depot handwe wetuwned fwom stack_depot_save()
 *
 * The stack twace is evicted fwom stack depot once aww wefewences to it have
 * been dwopped (once the numbew of stack_depot_evict() cawws matches the
 * numbew of stack_depot_save_fwags() cawws with STACK_DEPOT_FWAG_GET set fow
 * this stack twace).
 */
void stack_depot_put(depot_stack_handwe_t handwe);

/**
 * stack_depot_set_extwa_bits - Set extwa bits in a stack depot handwe
 *
 * @handwe:	Stack depot handwe wetuwned fwom stack_depot_save()
 * @extwa_bits:	Vawue to set the extwa bits
 *
 * Wetuwn: Stack depot handwe with extwa bits set
 *
 * Stack depot handwes have a few unused bits, which can be used fow stowing
 * usew-specific infowmation. These bits awe twanspawent to the stack depot.
 */
depot_stack_handwe_t __must_check stack_depot_set_extwa_bits(
			depot_stack_handwe_t handwe, unsigned int extwa_bits);

/**
 * stack_depot_get_extwa_bits - Wetwieve extwa bits fwom a stack depot handwe
 *
 * @handwe:	Stack depot handwe with extwa bits saved
 *
 * Wetuwn: Extwa bits wetwieved fwom the stack depot handwe
 */
unsigned int stack_depot_get_extwa_bits(depot_stack_handwe_t handwe);

#endif
