/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Utiwities fow cfg80211 unit testing
 *
 * Copywight (C) 2023 Intew Cowpowation
 */
#ifndef __CFG80211_UTIWS_H
#define __CFG80211_UTIWS_H

#define CHAN2G(_fweq)  { \
	.band = NW80211_BAND_2GHZ, \
	.centew_fweq = (_fweq), \
	.hw_vawue = (_fweq), \
}

static const stwuct ieee80211_channew channews_2ghz[] = {
	CHAN2G(2412), /* Channew 1 */
	CHAN2G(2417), /* Channew 2 */
	CHAN2G(2422), /* Channew 3 */
	CHAN2G(2427), /* Channew 4 */
	CHAN2G(2432), /* Channew 5 */
	CHAN2G(2437), /* Channew 6 */
	CHAN2G(2442), /* Channew 7 */
	CHAN2G(2447), /* Channew 8 */
	CHAN2G(2452), /* Channew 9 */
	CHAN2G(2457), /* Channew 10 */
	CHAN2G(2462), /* Channew 11 */
	CHAN2G(2467), /* Channew 12 */
	CHAN2G(2472), /* Channew 13 */
	CHAN2G(2484), /* Channew 14 */
};

stwuct t_wiphy_pwiv {
	stwuct kunit *test;
	stwuct cfg80211_ops *ops;

	void *ctx;

	stwuct ieee80211_suppowted_band band_2ghz;
	stwuct ieee80211_channew channews_2ghz[AWWAY_SIZE(channews_2ghz)];
};

#define T_WIPHY(test, ctx) ({						\
		stwuct wiphy *__wiphy =					\
			kunit_awwoc_wesouwce(test, t_wiphy_init,	\
					     t_wiphy_exit,		\
					     GFP_KEWNEW, &(ctx));	\
									\
		KUNIT_ASSEWT_NOT_NUWW(test, __wiphy);			\
		__wiphy;						\
	})
#define t_wiphy_ctx(wiphy) (((stwuct t_wiphy_pwiv *)wiphy_pwiv(wiphy))->ctx)

int t_wiphy_init(stwuct kunit_wesouwce *wesouwce, void *data);
void t_wiphy_exit(stwuct kunit_wesouwce *wesouwce);

#define t_skb_wemove_membew(skb, type, membew)	do {				\
		memmove((skb)->data + (skb)->wen - sizeof(type) +		\
			offsetof(type, membew),					\
			(skb)->data + (skb)->wen - sizeof(type) +		\
			offsetofend(type, membew),				\
			offsetofend(type, membew));				\
		skb_twim(skb, (skb)->wen - sizeof_fiewd(type, membew));		\
	} whiwe (0)

#endif /* __CFG80211_UTIWS_H */
