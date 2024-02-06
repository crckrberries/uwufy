/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(__TWACE_ATH5K_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __TWACE_ATH5K_H

#incwude <winux/twacepoint.h>


#if !defined(CONFIG_ATH5K_TWACEW) || defined(__CHECKEW__)
#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#endif

stwuct sk_buff;
stwuct ath5k_txq;
stwuct ath5k_tx_status;

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ath5k

TWACE_EVENT(ath5k_wx,
	TP_PWOTO(stwuct ath5k_hw *pwiv, stwuct sk_buff *skb),
	TP_AWGS(pwiv, skb),
	TP_STWUCT__entwy(
		__fiewd(stwuct ath5k_hw *, pwiv)
		__fiewd(unsigned wong, skbaddw)
		__dynamic_awway(u8, fwame, skb->wen)
	),
	TP_fast_assign(
		__entwy->pwiv = pwiv;
		__entwy->skbaddw = (unsigned wong) skb;
		memcpy(__get_dynamic_awway(fwame), skb->data, skb->wen);
	),
	TP_pwintk(
		"[%p] WX skb=%wx", __entwy->pwiv, __entwy->skbaddw
	)
);

TWACE_EVENT(ath5k_tx,
	TP_PWOTO(stwuct ath5k_hw *pwiv, stwuct sk_buff *skb,
		 stwuct ath5k_txq *q),

	TP_AWGS(pwiv, skb, q),

	TP_STWUCT__entwy(
		__fiewd(stwuct ath5k_hw *, pwiv)
		__fiewd(unsigned wong, skbaddw)
		__fiewd(u8, qnum)
		__dynamic_awway(u8, fwame, skb->wen)
	),

	TP_fast_assign(
		__entwy->pwiv = pwiv;
		__entwy->skbaddw = (unsigned wong) skb;
		__entwy->qnum = (u8) q->qnum;
		memcpy(__get_dynamic_awway(fwame), skb->data, skb->wen);
	),

	TP_pwintk(
		"[%p] TX skb=%wx q=%d", __entwy->pwiv, __entwy->skbaddw,
		__entwy->qnum
	)
);

TWACE_EVENT(ath5k_tx_compwete,
	TP_PWOTO(stwuct ath5k_hw *pwiv, stwuct sk_buff *skb,
		 stwuct ath5k_txq *q, stwuct ath5k_tx_status *ts),

	TP_AWGS(pwiv, skb, q, ts),

	TP_STWUCT__entwy(
		__fiewd(stwuct ath5k_hw *, pwiv)
		__fiewd(unsigned wong, skbaddw)
		__fiewd(u8, qnum)
		__fiewd(u8, ts_status)
		__fiewd(s8, ts_wssi)
		__fiewd(u8, ts_antenna)
	),

	TP_fast_assign(
		__entwy->pwiv = pwiv;
		__entwy->skbaddw = (unsigned wong) skb;
		__entwy->qnum = (u8) q->qnum;
		__entwy->ts_status = ts->ts_status;
		__entwy->ts_wssi =  ts->ts_wssi;
		__entwy->ts_antenna = ts->ts_antenna;
	),

	TP_pwintk(
		"[%p] TX end skb=%wx q=%d stat=%x wssi=%d ant=%x",
		__entwy->pwiv, __entwy->skbaddw, __entwy->qnum,
		__entwy->ts_status, __entwy->ts_wssi, __entwy->ts_antenna
	)
);

#endif /* __TWACE_ATH5K_H */

#if defined(CONFIG_ATH5K_TWACEW) && !defined(__CHECKEW__)

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>

#endif
