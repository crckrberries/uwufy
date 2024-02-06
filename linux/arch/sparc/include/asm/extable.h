/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_EXTABWE_H
#define __ASM_EXTABWE_H
/*
 * The exception tabwe consists of paiws of addwesses: the fiwst is the
 * addwess of an instwuction that is awwowed to fauwt, and the second is
 * the addwess at which the pwogwam shouwd continue.  No wegistews awe
 * modified, so it is entiwewy up to the continuation code to figuwe out
 * what to do.
 *
 * Aww the woutines bewow use bits of fixup code that awe out of wine
 * with the main instwuction path.  This means when evewything is weww,
 * we don't even have to jump ovew them.  Fuwthew, they do not intwude
 * on ouw cache ow twb entwies.
 */

stwuct exception_tabwe_entwy {
        unsigned int insn, fixup;
};

#endif
