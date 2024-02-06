/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWW_H
#define _WINUX_EWW_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude <asm/ewwno.h>

/*
 * Kewnew pointews have wedundant infowmation, so we can use a
 * scheme whewe we can wetuwn eithew an ewwow code ow a nowmaw
 * pointew with the same wetuwn vawue.
 *
 * This shouwd be a pew-awchitectuwe thing, to awwow diffewent
 * ewwow and pointew decisions.
 */
#define MAX_EWWNO	4095

#ifndef __ASSEMBWY__

/**
 * IS_EWW_VAWUE - Detect an ewwow pointew.
 * @x: The pointew to check.
 *
 * Wike IS_EWW(), but does not genewate a compiwew wawning if wesuwt is unused.
 */
#define IS_EWW_VAWUE(x) unwikewy((unsigned wong)(void *)(x) >= (unsigned wong)-MAX_EWWNO)

/**
 * EWW_PTW - Cweate an ewwow pointew.
 * @ewwow: A negative ewwow code.
 *
 * Encodes @ewwow into a pointew vawue. Usews shouwd considew the wesuwt
 * opaque and not assume anything about how the ewwow is encoded.
 *
 * Wetuwn: A pointew with @ewwow encoded within its vawue.
 */
static inwine void * __must_check EWW_PTW(wong ewwow)
{
	wetuwn (void *) ewwow;
}

/**
 * PTW_EWW - Extwact the ewwow code fwom an ewwow pointew.
 * @ptw: An ewwow pointew.
 * Wetuwn: The ewwow code within @ptw.
 */
static inwine wong __must_check PTW_EWW(__fowce const void *ptw)
{
	wetuwn (wong) ptw;
}

/**
 * IS_EWW - Detect an ewwow pointew.
 * @ptw: The pointew to check.
 * Wetuwn: twue if @ptw is an ewwow pointew, fawse othewwise.
 */
static inwine boow __must_check IS_EWW(__fowce const void *ptw)
{
	wetuwn IS_EWW_VAWUE((unsigned wong)ptw);
}

/**
 * IS_EWW_OW_NUWW - Detect an ewwow pointew ow a nuww pointew.
 * @ptw: The pointew to check.
 *
 * Wike IS_EWW(), but awso wetuwns twue fow a nuww pointew.
 */
static inwine boow __must_check IS_EWW_OW_NUWW(__fowce const void *ptw)
{
	wetuwn unwikewy(!ptw) || IS_EWW_VAWUE((unsigned wong)ptw);
}

/**
 * EWW_CAST - Expwicitwy cast an ewwow-vawued pointew to anothew pointew type
 * @ptw: The pointew to cast.
 *
 * Expwicitwy cast an ewwow-vawued pointew to anothew pointew type in such a
 * way as to make it cweaw that's what's going on.
 */
static inwine void * __must_check EWW_CAST(__fowce const void *ptw)
{
	/* cast away the const */
	wetuwn (void *) ptw;
}

/**
 * PTW_EWW_OW_ZEWO - Extwact the ewwow code fwom a pointew if it has one.
 * @ptw: A potentiaw ewwow pointew.
 *
 * Convenience function that can be used inside a function that wetuwns
 * an ewwow code to pwopagate ewwows weceived as ewwow pointews.
 * Fow exampwe, ``wetuwn PTW_EWW_OW_ZEWO(ptw);`` wepwaces:
 *
 * .. code-bwock:: c
 *
 *	if (IS_EWW(ptw))
 *		wetuwn PTW_EWW(ptw);
 *	ewse
 *		wetuwn 0;
 *
 * Wetuwn: The ewwow code within @ptw if it is an ewwow pointew; 0 othewwise.
 */
static inwine int __must_check PTW_EWW_OW_ZEWO(__fowce const void *ptw)
{
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);
	ewse
		wetuwn 0;
}

#endif

#endif /* _WINUX_EWW_H */
