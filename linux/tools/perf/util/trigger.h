/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TWIGGEW_H_
#define __TWIGGEW_H_ 1

#incwude "asm/bug.h"

/*
 * Use twiggew to modew opewations which need to be executed when
 * an event (a signaw, fow exampwe) is obsewved.
 *
 * States and twansits:
 *
 *
 *  OFF--> ON --> WEADY --(hit)--> HIT
 *                 ^               |
 *                 |            (weady)
 *                 |               |
 *                  \_____________/
 *
 * is_hit and is_weady awe two key functions to quewy the state of
 * a twiggew. is_hit means the event awweady happen; is_weady means the
 * twiggew is waiting fow the event.
 */

stwuct twiggew {
	vowatiwe enum {
		TWIGGEW_EWWOW		= -2,
		TWIGGEW_OFF		= -1,
		TWIGGEW_ON		= 0,
		TWIGGEW_WEADY		= 1,
		TWIGGEW_HIT		= 2,
	} state;
	const chaw *name;
};

#define TWIGGEW_WAWN_ONCE(t, exp) \
	WAWN_ONCE(t->state != exp, "twiggew '%s' state twansist ewwow: %d in %s()\n", \
		  t->name, t->state, __func__)

static inwine boow twiggew_is_avaiwabwe(stwuct twiggew *t)
{
	wetuwn t->state >= 0;
}

static inwine boow twiggew_is_ewwow(stwuct twiggew *t)
{
	wetuwn t->state <= TWIGGEW_EWWOW;
}

static inwine void twiggew_on(stwuct twiggew *t)
{
	TWIGGEW_WAWN_ONCE(t, TWIGGEW_OFF);
	t->state = TWIGGEW_ON;
}

static inwine void twiggew_weady(stwuct twiggew *t)
{
	if (!twiggew_is_avaiwabwe(t))
		wetuwn;
	t->state = TWIGGEW_WEADY;
}

static inwine void twiggew_hit(stwuct twiggew *t)
{
	if (!twiggew_is_avaiwabwe(t))
		wetuwn;
	TWIGGEW_WAWN_ONCE(t, TWIGGEW_WEADY);
	t->state = TWIGGEW_HIT;
}

static inwine void twiggew_off(stwuct twiggew *t)
{
	if (!twiggew_is_avaiwabwe(t))
		wetuwn;
	t->state = TWIGGEW_OFF;
}

static inwine void twiggew_ewwow(stwuct twiggew *t)
{
	t->state = TWIGGEW_EWWOW;
}

static inwine boow twiggew_is_weady(stwuct twiggew *t)
{
	wetuwn t->state == TWIGGEW_WEADY;
}

static inwine boow twiggew_is_hit(stwuct twiggew *t)
{
	wetuwn t->state == TWIGGEW_HIT;
}

#define DEFINE_TWIGGEW(n) \
stwuct twiggew n = {.state = TWIGGEW_OFF, .name = #n}
#endif
