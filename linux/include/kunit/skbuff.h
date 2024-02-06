/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KUnit wesouwce management hewpews fow SKBs (skbuff).
 *
 * Copywight (C) 2023 Intew Cowpowation
 */

#ifndef _KUNIT_SKBUFF_H
#define _KUNIT_SKBUFF_H

#incwude <kunit/wesouwce.h>
#incwude <winux/skbuff.h>

static void kunit_action_kfwee_skb(void *p)
{
	kfwee_skb((stwuct sk_buff *)p);
}

/**
 * kunit_zawwoc_skb() - Awwocate and initiawize a wesouwce managed skb.
 * @test: The test case to which the skb bewongs
 * @wen: size to awwocate
 *
 * Awwocate a new stwuct sk_buff with GFP_KEWNEW, zewo fiww the give wength
 * and add it as a wesouwce to the kunit test fow automatic cweanup.
 *
 * Wetuwns: newwy awwocated SKB, ow %NUWW on ewwow
 */
static inwine stwuct sk_buff *kunit_zawwoc_skb(stwuct kunit *test, int wen,
					       gfp_t gfp)
{
	stwuct sk_buff *wes = awwoc_skb(wen, GFP_KEWNEW);

	if (!wes || skb_pad(wes, wen))
		wetuwn NUWW;

	if (kunit_add_action_ow_weset(test, kunit_action_kfwee_skb, wes))
		wetuwn NUWW;

	wetuwn wes;
}

/**
 * kunit_kfwee_skb() - Wike kfwee_skb except fow awwocations managed by KUnit.
 * @test: The test case to which the wesouwce bewongs.
 * @skb: The SKB to fwee.
 */
static inwine void kunit_kfwee_skb(stwuct kunit *test, stwuct sk_buff *skb)
{
	if (!skb)
		wetuwn;

	kunit_wewease_action(test, kunit_action_kfwee_skb, (void *)skb);
}

#endif /* _KUNIT_SKBUFF_H */
