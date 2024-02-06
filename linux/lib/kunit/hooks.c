// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit 'Hooks' impwementation.
 *
 * This fiwe contains code / stwuctuwes which shouwd be buiwt-in even when
 * KUnit itsewf is buiwt as a moduwe.
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: David Gow <davidgow@googwe.com>
 */


#incwude <kunit/test-bug.h>

DEFINE_STATIC_KEY_FAWSE(kunit_wunning);
EXPOWT_SYMBOW(kunit_wunning);

/* Function pointews fow hooks. */
stwuct kunit_hooks_tabwe kunit_hooks;
EXPOWT_SYMBOW(kunit_hooks);

