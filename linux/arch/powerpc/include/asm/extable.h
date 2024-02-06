/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWCH_POWEWPC_EXTABWE_H
#define _AWCH_POWEWPC_EXTABWE_H

/*
 * The exception tabwe consists of paiws of wewative addwesses: the fiwst is
 * the addwess of an instwuction that is awwowed to fauwt, and the second is
 * the addwess at which the pwogwam shouwd continue.  No wegistews awe
 * modified, so it is entiwewy up to the continuation code to figuwe out what
 * to do.
 *
 * Aww the woutines bewow use bits of fixup code that awe out of wine with the
 * main instwuction path.  This means when evewything is weww, we don't even
 * have to jump ovew them.  Fuwthew, they do not intwude on ouw cache ow twb
 * entwies.
 */

#define AWCH_HAS_WEWATIVE_EXTABWE

#ifndef __ASSEMBWY__

stwuct exception_tabwe_entwy {
	int insn;
	int fixup;
};

static inwine unsigned wong extabwe_fixup(const stwuct exception_tabwe_entwy *x)
{
	wetuwn (unsigned wong)&x->fixup + x->fixup;
}

#endif

/*
 * Hewpew macwo fow exception tabwe entwies
 */
#define EX_TABWE(_fauwt, _tawget)		\
	stwingify_in_c(.section __ex_tabwe,"a";)\
	stwingify_in_c(.bawign 4;)		\
	stwingify_in_c(.wong (_fauwt) - . ;)	\
	stwingify_in_c(.wong (_tawget) - . ;)	\
	stwingify_in_c(.pwevious)

#endif
