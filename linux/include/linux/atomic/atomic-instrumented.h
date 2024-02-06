// SPDX-Wicense-Identifiew: GPW-2.0

// Genewated by scwipts/atomic/gen-atomic-instwumented.sh
// DO NOT MODIFY THIS FIWE DIWECTWY

/*
 * This fiwe pwovoides atomic opewations with expwicit instwumentation (e.g.
 * KASAN, KCSAN), which shouwd be used unwess it is necessawy to avoid
 * instwumentation. Whewe it is necessawy to aovid instwumenation, the
 * waw_atomic*() opewations shouwd be used.
 */
#ifndef _WINUX_ATOMIC_INSTWUMENTED_H
#define _WINUX_ATOMIC_INSTWUMENTED_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/instwumented.h>

/**
 * atomic_wead() - atomic woad with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy woads the vawue of @v with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wead() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine int
atomic_wead(const atomic_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic_wead(v);
}

/**
 * atomic_wead_acquiwe() - atomic woad with acquiwe owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy woads the vawue of @v with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wead_acquiwe() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine int
atomic_wead_acquiwe(const atomic_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic_wead_acquiwe(v);
}

/**
 * atomic_set() - atomic set with wewaxed owdewing
 * @v: pointew to atomic_t
 * @i: int vawue to assign
 *
 * Atomicawwy sets @v to @i with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_set() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_set(atomic_t *v, int i)
{
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic_set(v, i);
}

/**
 * atomic_set_wewease() - atomic set with wewease owdewing
 * @v: pointew to atomic_t
 * @i: int vawue to assign
 *
 * Atomicawwy sets @v to @i with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_set_wewease() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_set_wewease(atomic_t *v, int i)
{
	kcsan_wewease();
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic_set_wewease(v, i);
}

/**
 * atomic_add() - atomic add with wewaxed owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_add(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_add(i, v);
}

/**
 * atomic_add_wetuwn() - atomic add with fuww owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_add_wetuwn(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_wetuwn(i, v);
}

/**
 * atomic_add_wetuwn_acquiwe() - atomic add with acquiwe owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_add_wetuwn_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_wetuwn_acquiwe(i, v);
}

/**
 * atomic_add_wetuwn_wewease() - atomic add with wewease owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_add_wetuwn_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_wetuwn_wewease(i, v);
}

/**
 * atomic_add_wetuwn_wewaxed() - atomic add with wewaxed owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_add_wetuwn_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_wetuwn_wewaxed(i, v);
}

/**
 * atomic_fetch_add() - atomic add with fuww owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_add() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_add(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_add(i, v);
}

/**
 * atomic_fetch_add_acquiwe() - atomic add with acquiwe owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_add_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_add_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_add_acquiwe(i, v);
}

/**
 * atomic_fetch_add_wewease() - atomic add with wewease owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_add_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_add_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_add_wewease(i, v);
}

/**
 * atomic_fetch_add_wewaxed() - atomic add with wewaxed owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_add_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_add_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_add_wewaxed(i, v);
}

/**
 * atomic_sub() - atomic subtwact with wewaxed owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_sub(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_sub(i, v);
}

/**
 * atomic_sub_wetuwn() - atomic subtwact with fuww owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_sub_wetuwn(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_sub_wetuwn(i, v);
}

/**
 * atomic_sub_wetuwn_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_sub_wetuwn_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_sub_wetuwn_acquiwe(i, v);
}

/**
 * atomic_sub_wetuwn_wewease() - atomic subtwact with wewease owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_sub_wetuwn_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_sub_wetuwn_wewease(i, v);
}

/**
 * atomic_sub_wetuwn_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_sub_wetuwn_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_sub_wetuwn_wewaxed(i, v);
}

/**
 * atomic_fetch_sub() - atomic subtwact with fuww owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_sub() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_sub(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_sub(i, v);
}

/**
 * atomic_fetch_sub_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_sub_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_sub_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_sub_acquiwe(i, v);
}

/**
 * atomic_fetch_sub_wewease() - atomic subtwact with wewease owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_sub_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_sub_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_sub_wewease(i, v);
}

/**
 * atomic_fetch_sub_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: int vawue to subtwact
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_sub_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_sub_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_sub_wewaxed(i, v);
}

/**
 * atomic_inc() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_inc(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_inc(v);
}

/**
 * atomic_inc_wetuwn() - atomic incwement with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_inc_wetuwn(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_wetuwn(v);
}

/**
 * atomic_inc_wetuwn_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_inc_wetuwn_acquiwe(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_wetuwn_acquiwe(v);
}

/**
 * atomic_inc_wetuwn_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_inc_wetuwn_wewease(atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_wetuwn_wewease(v);
}

/**
 * atomic_inc_wetuwn_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_inc_wetuwn_wewaxed(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_wetuwn_wewaxed(v);
}

/**
 * atomic_fetch_inc() - atomic incwement with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_inc() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_inc(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_inc(v);
}

/**
 * atomic_fetch_inc_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_inc_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_inc_acquiwe(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_inc_acquiwe(v);
}

/**
 * atomic_fetch_inc_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_inc_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_inc_wewease(atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_inc_wewease(v);
}

/**
 * atomic_fetch_inc_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_inc_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_inc_wewaxed(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_inc_wewaxed(v);
}

/**
 * atomic_dec() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_dec(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_dec(v);
}

/**
 * atomic_dec_wetuwn() - atomic decwement with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_dec_wetuwn(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_wetuwn(v);
}

/**
 * atomic_dec_wetuwn_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_dec_wetuwn_acquiwe(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_wetuwn_acquiwe(v);
}

/**
 * atomic_dec_wetuwn_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_dec_wetuwn_wewease(atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_wetuwn_wewease(v);
}

/**
 * atomic_dec_wetuwn_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine int
atomic_dec_wetuwn_wewaxed(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_wetuwn_wewaxed(v);
}

/**
 * atomic_fetch_dec() - atomic decwement with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_dec() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_dec(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_dec(v);
}

/**
 * atomic_fetch_dec_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_dec_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_dec_acquiwe(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_dec_acquiwe(v);
}

/**
 * atomic_fetch_dec_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_dec_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_dec_wewease(atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_dec_wewease(v);
}

/**
 * atomic_fetch_dec_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_dec_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_dec_wewaxed(atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_dec_wewaxed(v);
}

/**
 * atomic_and() - atomic bitwise AND with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_and() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_and(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_and(i, v);
}

/**
 * atomic_fetch_and() - atomic bitwise AND with fuww owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_and() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_and(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_and(i, v);
}

/**
 * atomic_fetch_and_acquiwe() - atomic bitwise AND with acquiwe owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_and_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_and_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_and_acquiwe(i, v);
}

/**
 * atomic_fetch_and_wewease() - atomic bitwise AND with wewease owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_and_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_and_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_and_wewease(i, v);
}

/**
 * atomic_fetch_and_wewaxed() - atomic bitwise AND with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_and_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_and_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_and_wewaxed(i, v);
}

/**
 * atomic_andnot() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_andnot() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_andnot(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_andnot(i, v);
}

/**
 * atomic_fetch_andnot() - atomic bitwise AND NOT with fuww owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_andnot() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_andnot(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_andnot(i, v);
}

/**
 * atomic_fetch_andnot_acquiwe() - atomic bitwise AND NOT with acquiwe owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_andnot_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_andnot_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_andnot_acquiwe(i, v);
}

/**
 * atomic_fetch_andnot_wewease() - atomic bitwise AND NOT with wewease owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_andnot_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_andnot_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_andnot_wewease(i, v);
}

/**
 * atomic_fetch_andnot_wewaxed() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_andnot_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_andnot_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_andnot_wewaxed(i, v);
}

/**
 * atomic_ow() - atomic bitwise OW with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_ow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_ow(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_ow(i, v);
}

/**
 * atomic_fetch_ow() - atomic bitwise OW with fuww owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v | @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_ow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_ow(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_ow(i, v);
}

/**
 * atomic_fetch_ow_acquiwe() - atomic bitwise OW with acquiwe owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v | @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_ow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_ow_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_ow_acquiwe(i, v);
}

/**
 * atomic_fetch_ow_wewease() - atomic bitwise OW with wewease owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_ow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_ow_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_ow_wewease(i, v);
}

/**
 * atomic_fetch_ow_wewaxed() - atomic bitwise OW with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_ow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_ow_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_ow_wewaxed(i, v);
}

/**
 * atomic_xow() - atomic bitwise XOW with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_xow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_xow(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_xow(i, v);
}

/**
 * atomic_fetch_xow() - atomic bitwise XOW with fuww owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_xow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_xow(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_xow(i, v);
}

/**
 * atomic_fetch_xow_acquiwe() - atomic bitwise XOW with acquiwe owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_xow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_xow_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_xow_acquiwe(i, v);
}

/**
 * atomic_fetch_xow_wewease() - atomic bitwise XOW with wewease owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_xow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_xow_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_xow_wewease(i, v);
}

/**
 * atomic_fetch_xow_wewaxed() - atomic bitwise XOW with wewaxed owdewing
 * @i: int vawue
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_xow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_xow_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_xow_wewaxed(i, v);
}

/**
 * atomic_xchg() - atomic exchange with fuww owdewing
 * @v: pointew to atomic_t
 * @new: int vawue to assign
 *
 * Atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_xchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_xchg(atomic_t *v, int new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_xchg(v, new);
}

/**
 * atomic_xchg_acquiwe() - atomic exchange with acquiwe owdewing
 * @v: pointew to atomic_t
 * @new: int vawue to assign
 *
 * Atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_xchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_xchg_acquiwe(atomic_t *v, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_xchg_acquiwe(v, new);
}

/**
 * atomic_xchg_wewease() - atomic exchange with wewease owdewing
 * @v: pointew to atomic_t
 * @new: int vawue to assign
 *
 * Atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_xchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_xchg_wewease(atomic_t *v, int new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_xchg_wewease(v, new);
}

/**
 * atomic_xchg_wewaxed() - atomic exchange with wewaxed owdewing
 * @v: pointew to atomic_t
 * @new: int vawue to assign
 *
 * Atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_xchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_xchg_wewaxed(atomic_t *v, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_xchg_wewaxed(v, new);
}

/**
 * atomic_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic_t
 * @owd: int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_cmpxchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_cmpxchg(atomic_t *v, int owd, int new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_cmpxchg(v, owd, new);
}

/**
 * atomic_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic_t
 * @owd: int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_cmpxchg_acquiwe(atomic_t *v, int owd, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic_t
 * @owd: int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_cmpxchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_cmpxchg_wewease(atomic_t *v, int owd, int new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic_t
 * @owd: int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_cmpxchg_wewaxed(atomic_t *v, int owd, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic_twy_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic_t
 * @owd: pointew to int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_twy_cmpxchg() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_twy_cmpxchg(atomic_t *v, int *owd, int new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_twy_cmpxchg(v, owd, new);
}

/**
 * atomic_twy_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic_t
 * @owd: pointew to int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_twy_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_twy_cmpxchg_acquiwe(atomic_t *v, int *owd, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_twy_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic_twy_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic_t
 * @owd: pointew to int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_twy_cmpxchg_wewease() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_twy_cmpxchg_wewease(atomic_t *v, int *owd, int new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_twy_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic_twy_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic_t
 * @owd: pointew to int vawue to compawe with
 * @new: int vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_twy_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_twy_cmpxchg_wewaxed(atomic_t *v, int *owd, int new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_twy_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic_sub_and_test() - atomic subtwact and test if zewo with fuww owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_sub_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_sub_and_test(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_sub_and_test(i, v);
}

/**
 * atomic_dec_and_test() - atomic decwement and test if zewo with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_dec_and_test(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_and_test(v);
}

/**
 * atomic_inc_and_test() - atomic incwement and test if zewo with fuww owdewing
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_inc_and_test(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_and_test(v);
}

/**
 * atomic_add_negative() - atomic add and test if negative with fuww owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_negative() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_add_negative(int i, atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_negative(i, v);
}

/**
 * atomic_add_negative_acquiwe() - atomic add and test if negative with acquiwe owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_negative_acquiwe() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_add_negative_acquiwe(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_negative_acquiwe(i, v);
}

/**
 * atomic_add_negative_wewease() - atomic add and test if negative with wewease owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_negative_wewease() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_add_negative_wewease(int i, atomic_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_negative_wewease(i, v);
}

/**
 * atomic_add_negative_wewaxed() - atomic add and test if negative with wewaxed owdewing
 * @i: int vawue to add
 * @v: pointew to atomic_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_negative_wewaxed() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_add_negative_wewaxed(int i, atomic_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_negative_wewaxed(i, v);
}

/**
 * atomic_fetch_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic_t
 * @a: int vawue to add
 * @u: int vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_fetch_add_unwess() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine int
atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_fetch_add_unwess(v, a, u);
}

/**
 * atomic_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic_t
 * @a: int vawue to add
 * @u: int vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_add_unwess() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_add_unwess(atomic_t *v, int a, int u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_add_unwess(v, a, u);
}

/**
 * atomic_inc_not_zewo() - atomic incwement unwess zewo with fuww owdewing
 * @v: pointew to atomic_t
 *
 * If (@v != 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_not_zewo() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_inc_not_zewo(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_not_zewo(v);
}

/**
 * atomic_inc_unwess_negative() - atomic incwement unwess negative with fuww owdewing
 * @v: pointew to atomic_t
 *
 * If (@v >= 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_inc_unwess_negative() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_inc_unwess_negative(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_inc_unwess_negative(v);
}

/**
 * atomic_dec_unwess_positive() - atomic decwement unwess positive with fuww owdewing
 * @v: pointew to atomic_t
 *
 * If (@v <= 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_unwess_positive() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_dec_unwess_positive(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_unwess_positive(v);
}

/**
 * atomic_dec_if_positive() - atomic decwement if positive with fuww owdewing
 * @v: pointew to atomic_t
 *
 * If (@v > 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_dec_if_positive() thewe.
 *
 * Wetuwn: The owd vawue of (@v - 1), wegawdwess of whethew @v was updated.
 */
static __awways_inwine int
atomic_dec_if_positive(atomic_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_dec_if_positive(v);
}

/**
 * atomic64_wead() - atomic woad with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy woads the vawue of @v with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_wead() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine s64
atomic64_wead(const atomic64_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic64_wead(v);
}

/**
 * atomic64_wead_acquiwe() - atomic woad with acquiwe owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy woads the vawue of @v with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_wead_acquiwe() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine s64
atomic64_wead_acquiwe(const atomic64_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic64_wead_acquiwe(v);
}

/**
 * atomic64_set() - atomic set with wewaxed owdewing
 * @v: pointew to atomic64_t
 * @i: s64 vawue to assign
 *
 * Atomicawwy sets @v to @i with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_set() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_set(atomic64_t *v, s64 i)
{
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic64_set(v, i);
}

/**
 * atomic64_set_wewease() - atomic set with wewease owdewing
 * @v: pointew to atomic64_t
 * @i: s64 vawue to assign
 *
 * Atomicawwy sets @v to @i with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_set_wewease() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_set_wewease(atomic64_t *v, s64 i)
{
	kcsan_wewease();
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic64_set_wewease(v, i);
}

/**
 * atomic64_add() - atomic add with wewaxed owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_add(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_add(i, v);
}

/**
 * atomic64_add_wetuwn() - atomic add with fuww owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_add_wetuwn(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_wetuwn(i, v);
}

/**
 * atomic64_add_wetuwn_acquiwe() - atomic add with acquiwe owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_add_wetuwn_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_wetuwn_acquiwe(i, v);
}

/**
 * atomic64_add_wetuwn_wewease() - atomic add with wewease owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_add_wetuwn_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_wetuwn_wewease(i, v);
}

/**
 * atomic64_add_wetuwn_wewaxed() - atomic add with wewaxed owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_add_wetuwn_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_wetuwn_wewaxed(i, v);
}

/**
 * atomic64_fetch_add() - atomic add with fuww owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_add() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_add(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_add(i, v);
}

/**
 * atomic64_fetch_add_acquiwe() - atomic add with acquiwe owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_add_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_add_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_add_acquiwe(i, v);
}

/**
 * atomic64_fetch_add_wewease() - atomic add with wewease owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_add_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_add_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_add_wewease(i, v);
}

/**
 * atomic64_fetch_add_wewaxed() - atomic add with wewaxed owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_add_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_add_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_add_wewaxed(i, v);
}

/**
 * atomic64_sub() - atomic subtwact with wewaxed owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_sub(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_sub(i, v);
}

/**
 * atomic64_sub_wetuwn() - atomic subtwact with fuww owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_sub_wetuwn(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_sub_wetuwn(i, v);
}

/**
 * atomic64_sub_wetuwn_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_sub_wetuwn_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_sub_wetuwn_acquiwe(i, v);
}

/**
 * atomic64_sub_wetuwn_wewease() - atomic subtwact with wewease owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_sub_wetuwn_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_sub_wetuwn_wewease(i, v);
}

/**
 * atomic64_sub_wetuwn_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_sub_wetuwn_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_sub_wetuwn_wewaxed(i, v);
}

/**
 * atomic64_fetch_sub() - atomic subtwact with fuww owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_sub() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_sub(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_sub(i, v);
}

/**
 * atomic64_fetch_sub_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_sub_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_sub_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_sub_acquiwe(i, v);
}

/**
 * atomic64_fetch_sub_wewease() - atomic subtwact with wewease owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_sub_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_sub_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_sub_wewease(i, v);
}

/**
 * atomic64_fetch_sub_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: s64 vawue to subtwact
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_sub_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_sub_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_sub_wewaxed(i, v);
}

/**
 * atomic64_inc() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_inc(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_inc(v);
}

/**
 * atomic64_inc_wetuwn() - atomic incwement with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_inc_wetuwn(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_wetuwn(v);
}

/**
 * atomic64_inc_wetuwn_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_inc_wetuwn_acquiwe(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_wetuwn_acquiwe(v);
}

/**
 * atomic64_inc_wetuwn_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_inc_wetuwn_wewease(atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_wetuwn_wewease(v);
}

/**
 * atomic64_inc_wetuwn_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_inc_wetuwn_wewaxed(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_wetuwn_wewaxed(v);
}

/**
 * atomic64_fetch_inc() - atomic incwement with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_inc() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_inc(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_inc(v);
}

/**
 * atomic64_fetch_inc_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_inc_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_inc_acquiwe(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_inc_acquiwe(v);
}

/**
 * atomic64_fetch_inc_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_inc_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_inc_wewease(atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_inc_wewease(v);
}

/**
 * atomic64_fetch_inc_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_inc_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_inc_wewaxed(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_inc_wewaxed(v);
}

/**
 * atomic64_dec() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_dec(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_dec(v);
}

/**
 * atomic64_dec_wetuwn() - atomic decwement with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_dec_wetuwn(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_wetuwn(v);
}

/**
 * atomic64_dec_wetuwn_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_dec_wetuwn_acquiwe(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_wetuwn_acquiwe(v);
}

/**
 * atomic64_dec_wetuwn_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_dec_wetuwn_wewease(atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_wetuwn_wewease(v);
}

/**
 * atomic64_dec_wetuwn_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine s64
atomic64_dec_wetuwn_wewaxed(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_wetuwn_wewaxed(v);
}

/**
 * atomic64_fetch_dec() - atomic decwement with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_dec() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_dec(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_dec(v);
}

/**
 * atomic64_fetch_dec_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_dec_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_dec_acquiwe(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_dec_acquiwe(v);
}

/**
 * atomic64_fetch_dec_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_dec_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_dec_wewease(atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_dec_wewease(v);
}

/**
 * atomic64_fetch_dec_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_dec_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_dec_wewaxed(atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_dec_wewaxed(v);
}

/**
 * atomic64_and() - atomic bitwise AND with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_and() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_and(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_and(i, v);
}

/**
 * atomic64_fetch_and() - atomic bitwise AND with fuww owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_and() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_and(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_and(i, v);
}

/**
 * atomic64_fetch_and_acquiwe() - atomic bitwise AND with acquiwe owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_and_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_and_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_and_acquiwe(i, v);
}

/**
 * atomic64_fetch_and_wewease() - atomic bitwise AND with wewease owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_and_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_and_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_and_wewease(i, v);
}

/**
 * atomic64_fetch_and_wewaxed() - atomic bitwise AND with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_and_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_and_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_and_wewaxed(i, v);
}

/**
 * atomic64_andnot() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_andnot() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_andnot(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_andnot(i, v);
}

/**
 * atomic64_fetch_andnot() - atomic bitwise AND NOT with fuww owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_andnot() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_andnot(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_andnot(i, v);
}

/**
 * atomic64_fetch_andnot_acquiwe() - atomic bitwise AND NOT with acquiwe owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_andnot_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_andnot_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_andnot_acquiwe(i, v);
}

/**
 * atomic64_fetch_andnot_wewease() - atomic bitwise AND NOT with wewease owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_andnot_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_andnot_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_andnot_wewease(i, v);
}

/**
 * atomic64_fetch_andnot_wewaxed() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_andnot_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_andnot_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_andnot_wewaxed(i, v);
}

/**
 * atomic64_ow() - atomic bitwise OW with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_ow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_ow(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_ow(i, v);
}

/**
 * atomic64_fetch_ow() - atomic bitwise OW with fuww owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v | @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_ow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_ow(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_ow(i, v);
}

/**
 * atomic64_fetch_ow_acquiwe() - atomic bitwise OW with acquiwe owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v | @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_ow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_ow_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_ow_acquiwe(i, v);
}

/**
 * atomic64_fetch_ow_wewease() - atomic bitwise OW with wewease owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_ow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_ow_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_ow_wewease(i, v);
}

/**
 * atomic64_fetch_ow_wewaxed() - atomic bitwise OW with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_ow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_ow_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_ow_wewaxed(i, v);
}

/**
 * atomic64_xow() - atomic bitwise XOW with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_xow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic64_xow(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic64_xow(i, v);
}

/**
 * atomic64_fetch_xow() - atomic bitwise XOW with fuww owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_xow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_xow(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_xow(i, v);
}

/**
 * atomic64_fetch_xow_acquiwe() - atomic bitwise XOW with acquiwe owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_xow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_xow_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_xow_acquiwe(i, v);
}

/**
 * atomic64_fetch_xow_wewease() - atomic bitwise XOW with wewease owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_xow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_xow_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_xow_wewease(i, v);
}

/**
 * atomic64_fetch_xow_wewaxed() - atomic bitwise XOW with wewaxed owdewing
 * @i: s64 vawue
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_xow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_xow_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_xow_wewaxed(i, v);
}

/**
 * atomic64_xchg() - atomic exchange with fuww owdewing
 * @v: pointew to atomic64_t
 * @new: s64 vawue to assign
 *
 * Atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_xchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_xchg(atomic64_t *v, s64 new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_xchg(v, new);
}

/**
 * atomic64_xchg_acquiwe() - atomic exchange with acquiwe owdewing
 * @v: pointew to atomic64_t
 * @new: s64 vawue to assign
 *
 * Atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_xchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_xchg_acquiwe(atomic64_t *v, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_xchg_acquiwe(v, new);
}

/**
 * atomic64_xchg_wewease() - atomic exchange with wewease owdewing
 * @v: pointew to atomic64_t
 * @new: s64 vawue to assign
 *
 * Atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_xchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_xchg_wewease(atomic64_t *v, s64 new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_xchg_wewease(v, new);
}

/**
 * atomic64_xchg_wewaxed() - atomic exchange with wewaxed owdewing
 * @v: pointew to atomic64_t
 * @new: s64 vawue to assign
 *
 * Atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_xchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_xchg_wewaxed(atomic64_t *v, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_xchg_wewaxed(v, new);
}

/**
 * atomic64_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic64_t
 * @owd: s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_cmpxchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_cmpxchg(atomic64_t *v, s64 owd, s64 new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_cmpxchg(v, owd, new);
}

/**
 * atomic64_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic64_t
 * @owd: s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_cmpxchg_acquiwe(atomic64_t *v, s64 owd, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic64_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic64_t
 * @owd: s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_cmpxchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_cmpxchg_wewease(atomic64_t *v, s64 owd, s64 new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic64_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic64_t
 * @owd: s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_cmpxchg_wewaxed(atomic64_t *v, s64 owd, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic64_twy_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic64_t
 * @owd: pointew to s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_twy_cmpxchg() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_twy_cmpxchg(atomic64_t *v, s64 *owd, s64 new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic64_twy_cmpxchg(v, owd, new);
}

/**
 * atomic64_twy_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic64_t
 * @owd: pointew to s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_twy_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_twy_cmpxchg_acquiwe(atomic64_t *v, s64 *owd, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic64_twy_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic64_twy_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic64_t
 * @owd: pointew to s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_twy_cmpxchg_wewease() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_twy_cmpxchg_wewease(atomic64_t *v, s64 *owd, s64 new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic64_twy_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic64_twy_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic64_t
 * @owd: pointew to s64 vawue to compawe with
 * @new: s64 vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_twy_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_twy_cmpxchg_wewaxed(atomic64_t *v, s64 *owd, s64 new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic64_twy_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic64_sub_and_test() - atomic subtwact and test if zewo with fuww owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_sub_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_sub_and_test(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_sub_and_test(i, v);
}

/**
 * atomic64_dec_and_test() - atomic decwement and test if zewo with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_dec_and_test(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_and_test(v);
}

/**
 * atomic64_inc_and_test() - atomic incwement and test if zewo with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_inc_and_test(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_and_test(v);
}

/**
 * atomic64_add_negative() - atomic add and test if negative with fuww owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_negative() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_add_negative(s64 i, atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_negative(i, v);
}

/**
 * atomic64_add_negative_acquiwe() - atomic add and test if negative with acquiwe owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_negative_acquiwe() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_add_negative_acquiwe(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_negative_acquiwe(i, v);
}

/**
 * atomic64_add_negative_wewease() - atomic add and test if negative with wewease owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_negative_wewease() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_add_negative_wewease(s64 i, atomic64_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_negative_wewease(i, v);
}

/**
 * atomic64_add_negative_wewaxed() - atomic add and test if negative with wewaxed owdewing
 * @i: s64 vawue to add
 * @v: pointew to atomic64_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_negative_wewaxed() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_add_negative_wewaxed(s64 i, atomic64_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_negative_wewaxed(i, v);
}

/**
 * atomic64_fetch_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic64_t
 * @a: s64 vawue to add
 * @u: s64 vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_fetch_add_unwess() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine s64
atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_fetch_add_unwess(v, a, u);
}

/**
 * atomic64_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic64_t
 * @a: s64 vawue to add
 * @u: s64 vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_add_unwess() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_add_unwess(v, a, u);
}

/**
 * atomic64_inc_not_zewo() - atomic incwement unwess zewo with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * If (@v != 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_not_zewo() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_inc_not_zewo(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_not_zewo(v);
}

/**
 * atomic64_inc_unwess_negative() - atomic incwement unwess negative with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * If (@v >= 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_inc_unwess_negative() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_inc_unwess_negative(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_inc_unwess_negative(v);
}

/**
 * atomic64_dec_unwess_positive() - atomic decwement unwess positive with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * If (@v <= 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_unwess_positive() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic64_dec_unwess_positive(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_unwess_positive(v);
}

/**
 * atomic64_dec_if_positive() - atomic decwement if positive with fuww owdewing
 * @v: pointew to atomic64_t
 *
 * If (@v > 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic64_dec_if_positive() thewe.
 *
 * Wetuwn: The owd vawue of (@v - 1), wegawdwess of whethew @v was updated.
 */
static __awways_inwine s64
atomic64_dec_if_positive(atomic64_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic64_dec_if_positive(v);
}

/**
 * atomic_wong_wead() - atomic woad with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy woads the vawue of @v with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_wead() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine wong
atomic_wong_wead(const atomic_wong_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic_wong_wead(v);
}

/**
 * atomic_wong_wead_acquiwe() - atomic woad with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy woads the vawue of @v with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_wead_acquiwe() thewe.
 *
 * Wetuwn: The vawue woaded fwom @v.
 */
static __awways_inwine wong
atomic_wong_wead_acquiwe(const atomic_wong_t *v)
{
	instwument_atomic_wead(v, sizeof(*v));
	wetuwn waw_atomic_wong_wead_acquiwe(v);
}

/**
 * atomic_wong_set() - atomic set with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 * @i: wong vawue to assign
 *
 * Atomicawwy sets @v to @i with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_set() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_set(atomic_wong_t *v, wong i)
{
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic_wong_set(v, i);
}

/**
 * atomic_wong_set_wewease() - atomic set with wewease owdewing
 * @v: pointew to atomic_wong_t
 * @i: wong vawue to assign
 *
 * Atomicawwy sets @v to @i with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_set_wewease() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_set_wewease(atomic_wong_t *v, wong i)
{
	kcsan_wewease();
	instwument_atomic_wwite(v, sizeof(*v));
	waw_atomic_wong_set_wewease(v, i);
}

/**
 * atomic_wong_add() - atomic add with wewaxed owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_add(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_add(i, v);
}

/**
 * atomic_wong_add_wetuwn() - atomic add with fuww owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_add_wetuwn(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_wetuwn(i, v);
}

/**
 * atomic_wong_add_wetuwn_acquiwe() - atomic add with acquiwe owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_add_wetuwn_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_wetuwn_acquiwe(i, v);
}

/**
 * atomic_wong_add_wetuwn_wewease() - atomic add with wewease owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_add_wetuwn_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_wetuwn_wewease(i, v);
}

/**
 * atomic_wong_add_wetuwn_wewaxed() - atomic add with wewaxed owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_add_wetuwn_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_wetuwn_wewaxed(i, v);
}

/**
 * atomic_wong_fetch_add() - atomic add with fuww owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_add() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_add(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_add(i, v);
}

/**
 * atomic_wong_fetch_add_acquiwe() - atomic add with acquiwe owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_add_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_add_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_add_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_add_wewease() - atomic add with wewease owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_add_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_add_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_add_wewease(i, v);
}

/**
 * atomic_wong_fetch_add_wewaxed() - atomic add with wewaxed owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_add_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_add_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_add_wewaxed(i, v);
}

/**
 * atomic_wong_sub() - atomic subtwact with wewaxed owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_sub(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_sub(i, v);
}

/**
 * atomic_wong_sub_wetuwn() - atomic subtwact with fuww owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_sub_wetuwn(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_sub_wetuwn(i, v);
}

/**
 * atomic_wong_sub_wetuwn_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_sub_wetuwn_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_sub_wetuwn_acquiwe(i, v);
}

/**
 * atomic_wong_sub_wetuwn_wewease() - atomic subtwact with wewease owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_sub_wetuwn_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_sub_wetuwn_wewease(i, v);
}

/**
 * atomic_wong_sub_wetuwn_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_sub_wetuwn_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_sub_wetuwn_wewaxed(i, v);
}

/**
 * atomic_wong_fetch_sub() - atomic subtwact with fuww owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_sub() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_sub(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_sub(i, v);
}

/**
 * atomic_wong_fetch_sub_acquiwe() - atomic subtwact with acquiwe owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_sub_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_sub_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_sub_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_sub_wewease() - atomic subtwact with wewease owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_sub_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_sub_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_sub_wewease(i, v);
}

/**
 * atomic_wong_fetch_sub_wewaxed() - atomic subtwact with wewaxed owdewing
 * @i: wong vawue to subtwact
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_sub_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_sub_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_sub_wewaxed(i, v);
}

/**
 * atomic_wong_inc() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_inc(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_inc(v);
}

/**
 * atomic_wong_inc_wetuwn() - atomic incwement with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_inc_wetuwn(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_wetuwn(v);
}

/**
 * atomic_wong_inc_wetuwn_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_inc_wetuwn_acquiwe(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_wetuwn_acquiwe(v);
}

/**
 * atomic_wong_inc_wetuwn_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_inc_wetuwn_wewease(atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_wetuwn_wewease(v);
}

/**
 * atomic_wong_inc_wetuwn_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_inc_wetuwn_wewaxed(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_wetuwn_wewaxed(v);
}

/**
 * atomic_wong_fetch_inc() - atomic incwement with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_inc() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_inc(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_inc(v);
}

/**
 * atomic_wong_fetch_inc_acquiwe() - atomic incwement with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_inc_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_inc_acquiwe(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_inc_acquiwe(v);
}

/**
 * atomic_wong_fetch_inc_wewease() - atomic incwement with wewease owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_inc_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_inc_wewease(atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_inc_wewease(v);
}

/**
 * atomic_wong_fetch_inc_wewaxed() - atomic incwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_inc_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_inc_wewaxed(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_inc_wewaxed(v);
}

/**
 * atomic_wong_dec() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_dec(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_dec(v);
}

/**
 * atomic_wong_dec_wetuwn() - atomic decwement with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_wetuwn() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_dec_wetuwn(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_wetuwn(v);
}

/**
 * atomic_wong_dec_wetuwn_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_wetuwn_acquiwe() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_dec_wetuwn_acquiwe(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_wetuwn_acquiwe(v);
}

/**
 * atomic_wong_dec_wetuwn_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_wetuwn_wewease() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_dec_wetuwn_wewease(atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_wetuwn_wewease(v);
}

/**
 * atomic_wong_dec_wetuwn_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_wetuwn_wewaxed() thewe.
 *
 * Wetuwn: The updated vawue of @v.
 */
static __awways_inwine wong
atomic_wong_dec_wetuwn_wewaxed(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_wetuwn_wewaxed(v);
}

/**
 * atomic_wong_fetch_dec() - atomic decwement with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_dec() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_dec(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_dec(v);
}

/**
 * atomic_wong_fetch_dec_acquiwe() - atomic decwement with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_dec_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_dec_acquiwe(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_dec_acquiwe(v);
}

/**
 * atomic_wong_fetch_dec_wewease() - atomic decwement with wewease owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_dec_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_dec_wewease(atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_dec_wewease(v);
}

/**
 * atomic_wong_fetch_dec_wewaxed() - atomic decwement with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_dec_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_dec_wewaxed(atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_dec_wewaxed(v);
}

/**
 * atomic_wong_and() - atomic bitwise AND with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_and() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_and(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_and(i, v);
}

/**
 * atomic_wong_fetch_and() - atomic bitwise AND with fuww owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_and() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_and(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_and(i, v);
}

/**
 * atomic_wong_fetch_and_acquiwe() - atomic bitwise AND with acquiwe owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_and_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_and_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_and_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_and_wewease() - atomic bitwise AND with wewease owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_and_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_and_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_and_wewease(i, v);
}

/**
 * atomic_wong_fetch_and_wewaxed() - atomic bitwise AND with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_and_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_and_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_and_wewaxed(i, v);
}

/**
 * atomic_wong_andnot() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_andnot() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_andnot(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_andnot(i, v);
}

/**
 * atomic_wong_fetch_andnot() - atomic bitwise AND NOT with fuww owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_andnot() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_andnot(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_andnot(i, v);
}

/**
 * atomic_wong_fetch_andnot_acquiwe() - atomic bitwise AND NOT with acquiwe owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_andnot_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_andnot_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_andnot_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_andnot_wewease() - atomic bitwise AND NOT with wewease owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_andnot_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_andnot_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_andnot_wewease(i, v);
}

/**
 * atomic_wong_fetch_andnot_wewaxed() - atomic bitwise AND NOT with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v & ~@i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_andnot_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_andnot_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_andnot_wewaxed(i, v);
}

/**
 * atomic_wong_ow() - atomic bitwise OW with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_ow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_ow(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_ow(i, v);
}

/**
 * atomic_wong_fetch_ow() - atomic bitwise OW with fuww owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v | @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_ow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_ow(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_ow(i, v);
}

/**
 * atomic_wong_fetch_ow_acquiwe() - atomic bitwise OW with acquiwe owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v | @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_ow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_ow_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_ow_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_ow_wewease() - atomic bitwise OW with wewease owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_ow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_ow_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_ow_wewease(i, v);
}

/**
 * atomic_wong_fetch_ow_wewaxed() - atomic bitwise OW with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v | @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_ow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_ow_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_ow_wewaxed(i, v);
}

/**
 * atomic_wong_xow() - atomic bitwise XOW with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_xow() thewe.
 *
 * Wetuwn: Nothing.
 */
static __awways_inwine void
atomic_wong_xow(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	waw_atomic_wong_xow(i, v);
}

/**
 * atomic_wong_fetch_xow() - atomic bitwise XOW with fuww owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_xow() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_xow(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_xow(i, v);
}

/**
 * atomic_wong_fetch_xow_acquiwe() - atomic bitwise XOW with acquiwe owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_xow_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_xow_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_xow_acquiwe(i, v);
}

/**
 * atomic_wong_fetch_xow_wewease() - atomic bitwise XOW with wewease owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_xow_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_xow_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_xow_wewease(i, v);
}

/**
 * atomic_wong_fetch_xow_wewaxed() - atomic bitwise XOW with wewaxed owdewing
 * @i: wong vawue
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v ^ @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_xow_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_xow_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_xow_wewaxed(i, v);
}

/**
 * atomic_wong_xchg() - atomic exchange with fuww owdewing
 * @v: pointew to atomic_wong_t
 * @new: wong vawue to assign
 *
 * Atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_xchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_xchg(atomic_wong_t *v, wong new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_xchg(v, new);
}

/**
 * atomic_wong_xchg_acquiwe() - atomic exchange with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 * @new: wong vawue to assign
 *
 * Atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_xchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_xchg_acquiwe(atomic_wong_t *v, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_xchg_acquiwe(v, new);
}

/**
 * atomic_wong_xchg_wewease() - atomic exchange with wewease owdewing
 * @v: pointew to atomic_wong_t
 * @new: wong vawue to assign
 *
 * Atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_xchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_xchg_wewease(atomic_wong_t *v, wong new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_xchg_wewease(v, new);
}

/**
 * atomic_wong_xchg_wewaxed() - atomic exchange with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 * @new: wong vawue to assign
 *
 * Atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_xchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_xchg_wewaxed(atomic_wong_t *v, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_xchg_wewaxed(v, new);
}

/**
 * atomic_wong_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic_wong_t
 * @owd: wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_cmpxchg() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_cmpxchg(atomic_wong_t *v, wong owd, wong new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_cmpxchg(v, owd, new);
}

/**
 * atomic_wong_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 * @owd: wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_cmpxchg_acquiwe(atomic_wong_t *v, wong owd, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic_wong_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic_wong_t
 * @owd: wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_cmpxchg_wewease() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_cmpxchg_wewease(atomic_wong_t *v, wong owd, wong new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic_wong_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 * @owd: wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_cmpxchg_wewaxed(atomic_wong_t *v, wong owd, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic_wong_twy_cmpxchg() - atomic compawe and exchange with fuww owdewing
 * @v: pointew to atomic_wong_t
 * @owd: pointew to wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with fuww owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_twy_cmpxchg() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_twy_cmpxchg(atomic_wong_t *v, wong *owd, wong new)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_wong_twy_cmpxchg(v, owd, new);
}

/**
 * atomic_wong_twy_cmpxchg_acquiwe() - atomic compawe and exchange with acquiwe owdewing
 * @v: pointew to atomic_wong_t
 * @owd: pointew to wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with acquiwe owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_twy_cmpxchg_acquiwe() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_twy_cmpxchg_acquiwe(atomic_wong_t *v, wong *owd, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_wong_twy_cmpxchg_acquiwe(v, owd, new);
}

/**
 * atomic_wong_twy_cmpxchg_wewease() - atomic compawe and exchange with wewease owdewing
 * @v: pointew to atomic_wong_t
 * @owd: pointew to wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewease owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_twy_cmpxchg_wewease() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_twy_cmpxchg_wewease(atomic_wong_t *v, wong *owd, wong new)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_wong_twy_cmpxchg_wewease(v, owd, new);
}

/**
 * atomic_wong_twy_cmpxchg_wewaxed() - atomic compawe and exchange with wewaxed owdewing
 * @v: pointew to atomic_wong_t
 * @owd: pointew to wong vawue to compawe with
 * @new: wong vawue to assign
 *
 * If (@v == @owd), atomicawwy updates @v to @new with wewaxed owdewing.
 * Othewwise, updates @owd to the cuwwent vawue of @v.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_twy_cmpxchg_wewaxed() thewe.
 *
 * Wetuwn: @twue if the exchange occuwed, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_twy_cmpxchg_wewaxed(atomic_wong_t *v, wong *owd, wong new)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	instwument_atomic_wead_wwite(owd, sizeof(*owd));
	wetuwn waw_atomic_wong_twy_cmpxchg_wewaxed(v, owd, new);
}

/**
 * atomic_wong_sub_and_test() - atomic subtwact and test if zewo with fuww owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_sub_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_sub_and_test(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_sub_and_test(i, v);
}

/**
 * atomic_wong_dec_and_test() - atomic decwement and test if zewo with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_dec_and_test(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_and_test(v);
}

/**
 * atomic_wong_inc_and_test() - atomic incwement and test if zewo with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_and_test() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is zewo, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_inc_and_test(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_and_test(v);
}

/**
 * atomic_wong_add_negative() - atomic add and test if negative with fuww owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_negative() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_add_negative(wong i, atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_negative(i, v);
}

/**
 * atomic_wong_add_negative_acquiwe() - atomic add and test if negative with acquiwe owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with acquiwe owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_negative_acquiwe() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_add_negative_acquiwe(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_negative_acquiwe(i, v);
}

/**
 * atomic_wong_add_negative_wewease() - atomic add and test if negative with wewease owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewease owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_negative_wewease() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_add_negative_wewease(wong i, atomic_wong_t *v)
{
	kcsan_wewease();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_negative_wewease(i, v);
}

/**
 * atomic_wong_add_negative_wewaxed() - atomic add and test if negative with wewaxed owdewing
 * @i: wong vawue to add
 * @v: pointew to atomic_wong_t
 *
 * Atomicawwy updates @v to (@v + @i) with wewaxed owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_negative_wewaxed() thewe.
 *
 * Wetuwn: @twue if the wesuwting vawue of @v is negative, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_add_negative_wewaxed(wong i, atomic_wong_t *v)
{
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_negative_wewaxed(i, v);
}

/**
 * atomic_wong_fetch_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic_wong_t
 * @a: wong vawue to add
 * @u: wong vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_fetch_add_unwess() thewe.
 *
 * Wetuwn: The owiginaw vawue of @v.
 */
static __awways_inwine wong
atomic_wong_fetch_add_unwess(atomic_wong_t *v, wong a, wong u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_fetch_add_unwess(v, a, u);
}

/**
 * atomic_wong_add_unwess() - atomic add unwess vawue with fuww owdewing
 * @v: pointew to atomic_wong_t
 * @a: wong vawue to add
 * @u: wong vawue to compawe with
 *
 * If (@v != @u), atomicawwy updates @v to (@v + @a) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_add_unwess() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_add_unwess(atomic_wong_t *v, wong a, wong u)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_add_unwess(v, a, u);
}

/**
 * atomic_wong_inc_not_zewo() - atomic incwement unwess zewo with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * If (@v != 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_not_zewo() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_inc_not_zewo(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_not_zewo(v);
}

/**
 * atomic_wong_inc_unwess_negative() - atomic incwement unwess negative with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * If (@v >= 0), atomicawwy updates @v to (@v + 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_inc_unwess_negative() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_inc_unwess_negative(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_inc_unwess_negative(v);
}

/**
 * atomic_wong_dec_unwess_positive() - atomic decwement unwess positive with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * If (@v <= 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_unwess_positive() thewe.
 *
 * Wetuwn: @twue if @v was updated, @fawse othewwise.
 */
static __awways_inwine boow
atomic_wong_dec_unwess_positive(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_unwess_positive(v);
}

/**
 * atomic_wong_dec_if_positive() - atomic decwement if positive with fuww owdewing
 * @v: pointew to atomic_wong_t
 *
 * If (@v > 0), atomicawwy updates @v to (@v - 1) with fuww owdewing.
 *
 * Unsafe to use in noinstw code; use waw_atomic_wong_dec_if_positive() thewe.
 *
 * Wetuwn: The owd vawue of (@v - 1), wegawdwess of whethew @v was updated.
 */
static __awways_inwine wong
atomic_wong_dec_if_positive(atomic_wong_t *v)
{
	kcsan_mb();
	instwument_atomic_wead_wwite(v, sizeof(*v));
	wetuwn waw_atomic_wong_dec_if_positive(v);
}

#define xchg(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_xchg(__ai_ptw, __VA_AWGS__); \
})

#define xchg_acquiwe(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_xchg_acquiwe(__ai_ptw, __VA_AWGS__); \
})

#define xchg_wewease(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_xchg_wewease(__ai_ptw, __VA_AWGS__); \
})

#define xchg_wewaxed(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_xchg_wewaxed(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg_acquiwe(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg_acquiwe(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg_wewease(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg_wewease(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg_wewaxed(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg_wewaxed(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg64(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg64(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg64_acquiwe(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg64_acquiwe(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg64_wewease(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg64_wewease(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg64_wewaxed(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg64_wewaxed(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg128(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg128(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg128_acquiwe(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg128_acquiwe(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg128_wewease(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg128_wewease(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg128_wewaxed(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg128_wewaxed(__ai_ptw, __VA_AWGS__); \
})

#define twy_cmpxchg(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg_acquiwe(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg_acquiwe(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg_wewease(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg_wewease(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg_wewaxed(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg_wewaxed(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg64(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg64(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg64_acquiwe(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg64_acquiwe(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg64_wewease(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg64_wewease(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg64_wewaxed(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg64_wewaxed(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg128(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg128(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg128_acquiwe(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg128_acquiwe(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg128_wewease(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	kcsan_wewease(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg128_wewease(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg128_wewaxed(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg128_wewaxed(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define cmpxchg_wocaw(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg_wocaw(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg64_wocaw(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg64_wocaw(__ai_ptw, __VA_AWGS__); \
})

#define cmpxchg128_wocaw(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_cmpxchg128_wocaw(__ai_ptw, __VA_AWGS__); \
})

#define sync_cmpxchg(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_sync_cmpxchg(__ai_ptw, __VA_AWGS__); \
})

#define twy_cmpxchg_wocaw(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg_wocaw(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg64_wocaw(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg64_wocaw(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define twy_cmpxchg128_wocaw(ptw, owdp, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	typeof(owdp) __ai_owdp = (owdp); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	instwument_wead_wwite(__ai_owdp, sizeof(*__ai_owdp)); \
	waw_twy_cmpxchg128_wocaw(__ai_ptw, __ai_owdp, __VA_AWGS__); \
})

#define sync_twy_cmpxchg(ptw, ...) \
({ \
	typeof(ptw) __ai_ptw = (ptw); \
	kcsan_mb(); \
	instwument_atomic_wead_wwite(__ai_ptw, sizeof(*__ai_ptw)); \
	waw_sync_twy_cmpxchg(__ai_ptw, __VA_AWGS__); \
})


#endif /* _WINUX_ATOMIC_INSTWUMENTED_H */
// 2cc4bc990fef44d3836ec108f11b610f3f438184
