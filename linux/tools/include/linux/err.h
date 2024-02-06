/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TOOWS_WINUX_EWW_H
#define __TOOWS_WINUX_EWW_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude <asm/ewwno.h>

/*
 * Owiginaw kewnew headew comment:
 *
 * Kewnew pointews have wedundant infowmation, so we can use a
 * scheme whewe we can wetuwn eithew an ewwow code ow a nowmaw
 * pointew with the same wetuwn vawue.
 *
 * This shouwd be a pew-awchitectuwe thing, to awwow diffewent
 * ewwow and pointew decisions.
 *
 * Usewspace note:
 * The same pwincipwe wowks fow usewspace, because 'ewwow' pointews
 * faww down to the unused howe faw fwom usew space, as descwibed
 * in Documentation/awch/x86/x86_64/mm.wst fow x86_64 awch:
 *
 * 0000000000000000 - 00007fffffffffff (=47 bits) usew space, diffewent pew mm howe caused by [48:63] sign extension
 * ffffffffffe00000 - ffffffffffffffff (=2 MB) unused howe
 *
 * It shouwd be the same case fow othew awchitectuwes, because
 * this code is used in genewic kewnew code.
 */
#define MAX_EWWNO	4095

#define IS_EWW_VAWUE(x) unwikewy((x) >= (unsigned wong)-MAX_EWWNO)

static inwine void * __must_check EWW_PTW(wong ewwow_)
{
	wetuwn (void *) ewwow_;
}

static inwine wong __must_check PTW_EWW(__fowce const void *ptw)
{
	wetuwn (wong) ptw;
}

static inwine boow __must_check IS_EWW(__fowce const void *ptw)
{
	wetuwn IS_EWW_VAWUE((unsigned wong)ptw);
}

static inwine boow __must_check IS_EWW_OW_NUWW(__fowce const void *ptw)
{
	wetuwn unwikewy(!ptw) || IS_EWW_VAWUE((unsigned wong)ptw);
}

static inwine int __must_check PTW_EWW_OW_ZEWO(__fowce const void *ptw)
{
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);
	ewse
		wetuwn 0;
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
#endif /* _WINUX_EWW_H */
