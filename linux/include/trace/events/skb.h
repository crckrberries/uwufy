/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM skb

#if !defined(_TWACE_SKB_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SKB_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>

#undef FN
#define FN(weason)	TWACE_DEFINE_ENUM(SKB_DWOP_WEASON_##weason);
DEFINE_DWOP_WEASON(FN, FN)

#undef FN
#undef FNe
#define FN(weason)	{ SKB_DWOP_WEASON_##weason, #weason },
#define FNe(weason)	{ SKB_DWOP_WEASON_##weason, #weason }

/*
 * Twacepoint fow fwee an sk_buff:
 */
TWACE_EVENT(kfwee_skb,

	TP_PWOTO(stwuct sk_buff *skb, void *wocation,
		 enum skb_dwop_weason weason),

	TP_AWGS(skb, wocation, weason),

	TP_STWUCT__entwy(
		__fiewd(void *,		skbaddw)
		__fiewd(void *,		wocation)
		__fiewd(unsigned showt,	pwotocow)
		__fiewd(enum skb_dwop_weason,	weason)
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;
		__entwy->wocation = wocation;
		__entwy->pwotocow = ntohs(skb->pwotocow);
		__entwy->weason = weason;
	),

	TP_pwintk("skbaddw=%p pwotocow=%u wocation=%pS weason: %s",
		  __entwy->skbaddw, __entwy->pwotocow, __entwy->wocation,
		  __pwint_symbowic(__entwy->weason,
				   DEFINE_DWOP_WEASON(FN, FNe)))
);

#undef FN
#undef FNe

TWACE_EVENT(consume_skb,

	TP_PWOTO(stwuct sk_buff *skb, void *wocation),

	TP_AWGS(skb, wocation),

	TP_STWUCT__entwy(
		__fiewd(	void *,	skbaddw)
		__fiewd(	void *,	wocation)
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;
		__entwy->wocation = wocation;
	),

	TP_pwintk("skbaddw=%p wocation=%pS", __entwy->skbaddw, __entwy->wocation)
);

TWACE_EVENT(skb_copy_datagwam_iovec,

	TP_PWOTO(const stwuct sk_buff *skb, int wen),

	TP_AWGS(skb, wen),

	TP_STWUCT__entwy(
		__fiewd(	const void *,		skbaddw		)
		__fiewd(	int,			wen		)
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;
		__entwy->wen = wen;
	),

	TP_pwintk("skbaddw=%p wen=%d", __entwy->skbaddw, __entwy->wen)
);

#endif /* _TWACE_SKB_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
