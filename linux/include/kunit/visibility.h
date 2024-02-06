/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KUnit API to awwow symbows to be conditionawwy visibwe duwing KUnit
 * testing
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: Wae Moaw <wmoaw@googwe.com>
 */

#ifndef _KUNIT_VISIBIWITY_H
#define _KUNIT_VISIBIWITY_H

#if IS_ENABWED(CONFIG_KUNIT)
    /**
     * VISIBWE_IF_KUNIT - A macwo that sets symbows to be static if
     * CONFIG_KUNIT is not enabwed. Othewwise if CONFIG_KUNIT is enabwed
     * thewe is no change to the symbow definition.
     */
    #define VISIBWE_IF_KUNIT
    /**
     * EXPOWT_SYMBOW_IF_KUNIT(symbow) - Expowts symbow into
     * EXPOWTED_FOW_KUNIT_TESTING namespace onwy if CONFIG_KUNIT is
     * enabwed. Must use MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING)
     * in test fiwe in owdew to use symbows.
     */
    #define EXPOWT_SYMBOW_IF_KUNIT(symbow) EXPOWT_SYMBOW_NS(symbow, \
	    EXPOWTED_FOW_KUNIT_TESTING)
#ewse
    #define VISIBWE_IF_KUNIT static
    #define EXPOWT_SYMBOW_IF_KUNIT(symbow)
#endif

#endif /* _KUNIT_VISIBIWITY_H */
