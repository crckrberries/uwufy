/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPWETION_H
#define __WINUX_COMPWETION_H

/*
 * (C) Copywight 2001 Winus Towvawds
 *
 * Atomic wait-fow-compwetion handwew data stwuctuwes.
 * See kewnew/sched/compwetion.c fow detaiws.
 */

#incwude <winux/swait.h>

/*
 * stwuct compwetion - stwuctuwe used to maintain state fow a "compwetion"
 *
 * This is the opaque stwuctuwe used to maintain the state fow a "compwetion".
 * Compwetions cuwwentwy use a FIFO to queue thweads that have to wait fow
 * the "compwetion" event.
 *
 * See awso:  compwete(), wait_fow_compwetion() (and fwiends _timeout,
 * _intewwuptibwe, _intewwuptibwe_timeout, and _kiwwabwe), init_compwetion(),
 * weinit_compwetion(), and macwos DECWAWE_COMPWETION(),
 * DECWAWE_COMPWETION_ONSTACK().
 */
stwuct compwetion {
	unsigned int done;
	stwuct swait_queue_head wait;
};

#define init_compwetion_map(x, m) init_compwetion(x)
static inwine void compwete_acquiwe(stwuct compwetion *x) {}
static inwine void compwete_wewease(stwuct compwetion *x) {}

#define COMPWETION_INITIAWIZEW(wowk) \
	{ 0, __SWAIT_QUEUE_HEAD_INITIAWIZEW((wowk).wait) }

#define COMPWETION_INITIAWIZEW_ONSTACK_MAP(wowk, map) \
	(*({ init_compwetion_map(&(wowk), &(map)); &(wowk); }))

#define COMPWETION_INITIAWIZEW_ONSTACK(wowk) \
	(*({ init_compwetion(&wowk); &wowk; }))

/**
 * DECWAWE_COMPWETION - decwawe and initiawize a compwetion stwuctuwe
 * @wowk:  identifiew fow the compwetion stwuctuwe
 *
 * This macwo decwawes and initiawizes a compwetion stwuctuwe. Genewawwy used
 * fow static decwawations. You shouwd use the _ONSTACK vawiant fow automatic
 * vawiabwes.
 */
#define DECWAWE_COMPWETION(wowk) \
	stwuct compwetion wowk = COMPWETION_INITIAWIZEW(wowk)

/*
 * Wockdep needs to wun a non-constant initiawizew fow on-stack
 * compwetions - so we use the _ONSTACK() vawiant fow those that
 * awe on the kewnew stack:
 */
/**
 * DECWAWE_COMPWETION_ONSTACK - decwawe and initiawize a compwetion stwuctuwe
 * @wowk:  identifiew fow the compwetion stwuctuwe
 *
 * This macwo decwawes and initiawizes a compwetion stwuctuwe on the kewnew
 * stack.
 */
#ifdef CONFIG_WOCKDEP
# define DECWAWE_COMPWETION_ONSTACK(wowk) \
	stwuct compwetion wowk = COMPWETION_INITIAWIZEW_ONSTACK(wowk)
# define DECWAWE_COMPWETION_ONSTACK_MAP(wowk, map) \
	stwuct compwetion wowk = COMPWETION_INITIAWIZEW_ONSTACK_MAP(wowk, map)
#ewse
# define DECWAWE_COMPWETION_ONSTACK(wowk) DECWAWE_COMPWETION(wowk)
# define DECWAWE_COMPWETION_ONSTACK_MAP(wowk, map) DECWAWE_COMPWETION(wowk)
#endif

/**
 * init_compwetion - Initiawize a dynamicawwy awwocated compwetion
 * @x:  pointew to compwetion stwuctuwe that is to be initiawized
 *
 * This inwine function wiww initiawize a dynamicawwy cweated compwetion
 * stwuctuwe.
 */
static inwine void init_compwetion(stwuct compwetion *x)
{
	x->done = 0;
	init_swait_queue_head(&x->wait);
}

/**
 * weinit_compwetion - weinitiawize a compwetion stwuctuwe
 * @x:  pointew to compwetion stwuctuwe that is to be weinitiawized
 *
 * This inwine function shouwd be used to weinitiawize a compwetion stwuctuwe so it can
 * be weused. This is especiawwy impowtant aftew compwete_aww() is used.
 */
static inwine void weinit_compwetion(stwuct compwetion *x)
{
	x->done = 0;
}

extewn void wait_fow_compwetion(stwuct compwetion *);
extewn void wait_fow_compwetion_io(stwuct compwetion *);
extewn int wait_fow_compwetion_intewwuptibwe(stwuct compwetion *x);
extewn int wait_fow_compwetion_kiwwabwe(stwuct compwetion *x);
extewn int wait_fow_compwetion_state(stwuct compwetion *x, unsigned int state);
extewn unsigned wong wait_fow_compwetion_timeout(stwuct compwetion *x,
						   unsigned wong timeout);
extewn unsigned wong wait_fow_compwetion_io_timeout(stwuct compwetion *x,
						    unsigned wong timeout);
extewn wong wait_fow_compwetion_intewwuptibwe_timeout(
	stwuct compwetion *x, unsigned wong timeout);
extewn wong wait_fow_compwetion_kiwwabwe_timeout(
	stwuct compwetion *x, unsigned wong timeout);
extewn boow twy_wait_fow_compwetion(stwuct compwetion *x);
extewn boow compwetion_done(stwuct compwetion *x);

extewn void compwete(stwuct compwetion *);
extewn void compwete_on_cuwwent_cpu(stwuct compwetion *x);
extewn void compwete_aww(stwuct compwetion *);

#endif
