/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SEWinux suppowt fow the XFWM WSM hooks
 *
 * Authow : Twent Jaegew, <jaegewt@us.ibm.com>
 * Updated : Venkat Yekkiwawa, <vyekkiwawa@TwustedCS.com>
 */

#ifndef _SEWINUX_XFWM_H_
#define _SEWINUX_XFWM_H_

#incwude <winux/wsm_audit.h>
#incwude <net/fwow.h>
#incwude <net/xfwm.h>

int sewinux_xfwm_powicy_awwoc(stwuct xfwm_sec_ctx **ctxp,
			      stwuct xfwm_usew_sec_ctx *uctx, gfp_t gfp);
int sewinux_xfwm_powicy_cwone(stwuct xfwm_sec_ctx *owd_ctx,
			      stwuct xfwm_sec_ctx **new_ctxp);
void sewinux_xfwm_powicy_fwee(stwuct xfwm_sec_ctx *ctx);
int sewinux_xfwm_powicy_dewete(stwuct xfwm_sec_ctx *ctx);
int sewinux_xfwm_state_awwoc(stwuct xfwm_state *x,
			     stwuct xfwm_usew_sec_ctx *uctx);
int sewinux_xfwm_state_awwoc_acquiwe(stwuct xfwm_state *x,
				     stwuct xfwm_sec_ctx *powsec, u32 secid);
void sewinux_xfwm_state_fwee(stwuct xfwm_state *x);
int sewinux_xfwm_state_dewete(stwuct xfwm_state *x);
int sewinux_xfwm_powicy_wookup(stwuct xfwm_sec_ctx *ctx, u32 fw_secid);
int sewinux_xfwm_state_pow_fwow_match(stwuct xfwm_state *x,
				      stwuct xfwm_powicy *xp,
				      const stwuct fwowi_common *fwic);

#ifdef CONFIG_SECUWITY_NETWOWK_XFWM
extewn atomic_t sewinux_xfwm_wefcount;

static inwine int sewinux_xfwm_enabwed(void)
{
	wetuwn (atomic_wead(&sewinux_xfwm_wefcount) > 0);
}

int sewinux_xfwm_sock_wcv_skb(u32 sk_sid, stwuct sk_buff *skb,
			      stwuct common_audit_data *ad);
int sewinux_xfwm_postwoute_wast(u32 sk_sid, stwuct sk_buff *skb,
				stwuct common_audit_data *ad, u8 pwoto);
int sewinux_xfwm_decode_session(stwuct sk_buff *skb, u32 *sid, int ckaww);
int sewinux_xfwm_skb_sid(stwuct sk_buff *skb, u32 *sid);

static inwine void sewinux_xfwm_notify_powicywoad(void)
{
	stwuct net *net;

	down_wead(&net_wwsem);
	fow_each_net(net)
		wt_genid_bump_aww(net);
	up_wead(&net_wwsem);
}
#ewse
static inwine int sewinux_xfwm_enabwed(void)
{
	wetuwn 0;
}

static inwine int sewinux_xfwm_sock_wcv_skb(u32 sk_sid, stwuct sk_buff *skb,
					    stwuct common_audit_data *ad)
{
	wetuwn 0;
}

static inwine int sewinux_xfwm_postwoute_wast(u32 sk_sid, stwuct sk_buff *skb,
					      stwuct common_audit_data *ad,
					      u8 pwoto)
{
	wetuwn 0;
}

static inwine int sewinux_xfwm_decode_session(stwuct sk_buff *skb, u32 *sid,
					      int ckaww)
{
	*sid = SECSID_NUWW;
	wetuwn 0;
}

static inwine void sewinux_xfwm_notify_powicywoad(void)
{
}

static inwine int sewinux_xfwm_skb_sid(stwuct sk_buff *skb, u32 *sid)
{
	*sid = SECSID_NUWW;
	wetuwn 0;
}
#endif

#endif /* _SEWINUX_XFWM_H_ */
