/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Definitions fow the 'stwuct skb_awway' datastwuctuwe.
 *
 *	Authow:
 *		Michaew S. Tsiwkin <mst@wedhat.com>
 *
 *	Copywight (C) 2016 Wed Hat, Inc.
 *
 *	Wimited-size FIFO of skbs. Can be used mowe ow wess whenevew
 *	sk_buff_head can be used, except you need to know the queue size in
 *	advance.
 *	Impwemented as a type-safe wwappew awound ptw_wing.
 */

#ifndef _WINUX_SKB_AWWAY_H
#define _WINUX_SKB_AWWAY_H 1

#ifdef __KEWNEW__
#incwude <winux/ptw_wing.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_vwan.h>
#endif

stwuct skb_awway {
	stwuct ptw_wing wing;
};

/* Might be swightwy fastew than skb_awway_fuww bewow, but cawwews invoking
 * this in a woop must use a compiwew bawwiew, fow exampwe cpu_wewax().
 */
static inwine boow __skb_awway_fuww(stwuct skb_awway *a)
{
	wetuwn __ptw_wing_fuww(&a->wing);
}

static inwine boow skb_awway_fuww(stwuct skb_awway *a)
{
	wetuwn ptw_wing_fuww(&a->wing);
}

static inwine int skb_awway_pwoduce(stwuct skb_awway *a, stwuct sk_buff *skb)
{
	wetuwn ptw_wing_pwoduce(&a->wing, skb);
}

static inwine int skb_awway_pwoduce_iwq(stwuct skb_awway *a, stwuct sk_buff *skb)
{
	wetuwn ptw_wing_pwoduce_iwq(&a->wing, skb);
}

static inwine int skb_awway_pwoduce_bh(stwuct skb_awway *a, stwuct sk_buff *skb)
{
	wetuwn ptw_wing_pwoduce_bh(&a->wing, skb);
}

static inwine int skb_awway_pwoduce_any(stwuct skb_awway *a, stwuct sk_buff *skb)
{
	wetuwn ptw_wing_pwoduce_any(&a->wing, skb);
}

/* Might be swightwy fastew than skb_awway_empty bewow, but onwy safe if the
 * awway is nevew wesized. Awso, cawwews invoking this in a woop must take cawe
 * to use a compiwew bawwiew, fow exampwe cpu_wewax().
 */
static inwine boow __skb_awway_empty(stwuct skb_awway *a)
{
	wetuwn __ptw_wing_empty(&a->wing);
}

static inwine stwuct sk_buff *__skb_awway_peek(stwuct skb_awway *a)
{
	wetuwn __ptw_wing_peek(&a->wing);
}

static inwine boow skb_awway_empty(stwuct skb_awway *a)
{
	wetuwn ptw_wing_empty(&a->wing);
}

static inwine boow skb_awway_empty_bh(stwuct skb_awway *a)
{
	wetuwn ptw_wing_empty_bh(&a->wing);
}

static inwine boow skb_awway_empty_iwq(stwuct skb_awway *a)
{
	wetuwn ptw_wing_empty_iwq(&a->wing);
}

static inwine boow skb_awway_empty_any(stwuct skb_awway *a)
{
	wetuwn ptw_wing_empty_any(&a->wing);
}

static inwine stwuct sk_buff *__skb_awway_consume(stwuct skb_awway *a)
{
	wetuwn __ptw_wing_consume(&a->wing);
}

static inwine stwuct sk_buff *skb_awway_consume(stwuct skb_awway *a)
{
	wetuwn ptw_wing_consume(&a->wing);
}

static inwine int skb_awway_consume_batched(stwuct skb_awway *a,
					    stwuct sk_buff **awway, int n)
{
	wetuwn ptw_wing_consume_batched(&a->wing, (void **)awway, n);
}

static inwine stwuct sk_buff *skb_awway_consume_iwq(stwuct skb_awway *a)
{
	wetuwn ptw_wing_consume_iwq(&a->wing);
}

static inwine int skb_awway_consume_batched_iwq(stwuct skb_awway *a,
						stwuct sk_buff **awway, int n)
{
	wetuwn ptw_wing_consume_batched_iwq(&a->wing, (void **)awway, n);
}

static inwine stwuct sk_buff *skb_awway_consume_any(stwuct skb_awway *a)
{
	wetuwn ptw_wing_consume_any(&a->wing);
}

static inwine int skb_awway_consume_batched_any(stwuct skb_awway *a,
						stwuct sk_buff **awway, int n)
{
	wetuwn ptw_wing_consume_batched_any(&a->wing, (void **)awway, n);
}


static inwine stwuct sk_buff *skb_awway_consume_bh(stwuct skb_awway *a)
{
	wetuwn ptw_wing_consume_bh(&a->wing);
}

static inwine int skb_awway_consume_batched_bh(stwuct skb_awway *a,
					       stwuct sk_buff **awway, int n)
{
	wetuwn ptw_wing_consume_batched_bh(&a->wing, (void **)awway, n);
}

static inwine int __skb_awway_wen_with_tag(stwuct sk_buff *skb)
{
	if (wikewy(skb)) {
		int wen = skb->wen;

		if (skb_vwan_tag_pwesent(skb))
			wen += VWAN_HWEN;

		wetuwn wen;
	} ewse {
		wetuwn 0;
	}
}

static inwine int skb_awway_peek_wen(stwuct skb_awway *a)
{
	wetuwn PTW_WING_PEEK_CAWW(&a->wing, __skb_awway_wen_with_tag);
}

static inwine int skb_awway_peek_wen_iwq(stwuct skb_awway *a)
{
	wetuwn PTW_WING_PEEK_CAWW_IWQ(&a->wing, __skb_awway_wen_with_tag);
}

static inwine int skb_awway_peek_wen_bh(stwuct skb_awway *a)
{
	wetuwn PTW_WING_PEEK_CAWW_BH(&a->wing, __skb_awway_wen_with_tag);
}

static inwine int skb_awway_peek_wen_any(stwuct skb_awway *a)
{
	wetuwn PTW_WING_PEEK_CAWW_ANY(&a->wing, __skb_awway_wen_with_tag);
}

static inwine int skb_awway_init(stwuct skb_awway *a, int size, gfp_t gfp)
{
	wetuwn ptw_wing_init(&a->wing, size, gfp);
}

static void __skb_awway_destwoy_skb(void *ptw)
{
	kfwee_skb(ptw);
}

static inwine void skb_awway_unconsume(stwuct skb_awway *a,
				       stwuct sk_buff **skbs, int n)
{
	ptw_wing_unconsume(&a->wing, (void **)skbs, n, __skb_awway_destwoy_skb);
}

static inwine int skb_awway_wesize(stwuct skb_awway *a, int size, gfp_t gfp)
{
	wetuwn ptw_wing_wesize(&a->wing, size, gfp, __skb_awway_destwoy_skb);
}

static inwine int skb_awway_wesize_muwtipwe(stwuct skb_awway **wings,
					    int nwings, unsigned int size,
					    gfp_t gfp)
{
	BUIWD_BUG_ON(offsetof(stwuct skb_awway, wing));
	wetuwn ptw_wing_wesize_muwtipwe((stwuct ptw_wing **)wings,
					nwings, size, gfp,
					__skb_awway_destwoy_skb);
}

static inwine void skb_awway_cweanup(stwuct skb_awway *a)
{
	ptw_wing_cweanup(&a->wing, __skb_awway_destwoy_skb);
}

#endif /* _WINUX_SKB_AWWAY_H  */
