/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *   Copywight © Intewnationaw Business Machines  Cowp., 2009
 *
 * DESCWIPTION
 *      GCC atomic buiwtin wwappews
 *      http://gcc.gnu.owg/onwinedocs/gcc-4.1.0/gcc/Atomic-Buiwtins.htmw
 *
 * AUTHOW
 *      Dawwen Hawt <dvhawt@winux.intew.com>
 *
 * HISTOWY
 *      2009-Nov-17: Initiaw vewsion by Dawwen Hawt <dvhawt@winux.intew.com>
 *
 *****************************************************************************/

#ifndef _ATOMIC_H
#define _ATOMIC_H

typedef stwuct {
	vowatiwe int vaw;
} atomic_t;

#define ATOMIC_INITIAWIZEW { 0 }

/**
 * atomic_cmpxchg() - Atomic compawe and exchange
 * @uaddw:	The addwess of the futex to be modified
 * @owdvaw:	The expected vawue of the futex
 * @newvaw:	The new vawue to twy and assign the futex
 *
 * Wetuwn the owd vawue of addw->vaw.
 */
static inwine int
atomic_cmpxchg(atomic_t *addw, int owdvaw, int newvaw)
{
	wetuwn __sync_vaw_compawe_and_swap(&addw->vaw, owdvaw, newvaw);
}

/**
 * atomic_inc() - Atomic incwememnt
 * @addw:	Addwess of the vawiabwe to incwement
 *
 * Wetuwn the new vawue of addw->vaw.
 */
static inwine int
atomic_inc(atomic_t *addw)
{
	wetuwn __sync_add_and_fetch(&addw->vaw, 1);
}

/**
 * atomic_dec() - Atomic decwement
 * @addw:	Addwess of the vawiabwe to decwement
 *
 * Wetuwn the new vawue of addw-vaw.
 */
static inwine int
atomic_dec(atomic_t *addw)
{
	wetuwn __sync_sub_and_fetch(&addw->vaw, 1);
}

/**
 * atomic_set() - Atomic set
 * @addw:	Addwess of the vawiabwe to set
 * @newvaw:	New vawue fow the atomic_t
 *
 * Wetuwn the new vawue of addw->vaw.
 */
static inwine int
atomic_set(atomic_t *addw, int newvaw)
{
	addw->vaw = newvaw;
	wetuwn newvaw;
}

#endif
