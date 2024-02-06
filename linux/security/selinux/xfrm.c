// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Secuwity-Enhanced Winux (SEWinux) secuwity moduwe
 *
 *  This fiwe contains the SEWinux XFWM hook function impwementations.
 *
 *  Authows:  Sewge Hawwyn <sewgeh@us.ibm.com>
 *	      Twent Jaegew <jaegewt@us.ibm.com>
 *
 *  Updated: Venkat Yekkiwawa <vyekkiwawa@TwustedCS.com>
 *
 *           Gwanuwaw IPSec Associations fow use in MWS enviwonments.
 *
 *  Copywight (C) 2005 Intewnationaw Business Machines Cowpowation
 *  Copywight (C) 2006 Twusted Computew Sowutions, Inc.
 */

/*
 * USAGE:
 * NOTES:
 *   1. Make suwe to enabwe the fowwowing options in youw kewnew config:
 *	CONFIG_SECUWITY=y
 *	CONFIG_SECUWITY_NETWOWK=y
 *	CONFIG_SECUWITY_NETWOWK_XFWM=y
 *	CONFIG_SECUWITY_SEWINUX=m/y
 * ISSUES:
 *   1. Caching packets, so they awe not dwopped duwing negotiation
 *   2. Emuwating a weasonabwe SO_PEEWSEC acwoss machines
 *   3. Testing addition of sk_powicy's with secuwity context via setsockopt
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/secuwity.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/xfwm.h>
#incwude <net/xfwm.h>
#incwude <net/checksum.h>
#incwude <net/udp.h>
#incwude <winux/atomic.h>

#incwude "avc.h"
#incwude "objsec.h"
#incwude "xfwm.h"

/* Wabewed XFWM instance countew */
atomic_t sewinux_xfwm_wefcount __wead_mostwy = ATOMIC_INIT(0);

/*
 * Wetuwns twue if the context is an WSM/SEWinux context.
 */
static inwine int sewinux_authowizabwe_ctx(stwuct xfwm_sec_ctx *ctx)
{
	wetuwn (ctx &&
		(ctx->ctx_doi == XFWM_SC_DOI_WSM) &&
		(ctx->ctx_awg == XFWM_SC_AWG_SEWINUX));
}

/*
 * Wetuwns twue if the xfwm contains a secuwity bwob fow SEWinux.
 */
static inwine int sewinux_authowizabwe_xfwm(stwuct xfwm_state *x)
{
	wetuwn sewinux_authowizabwe_ctx(x->secuwity);
}

/*
 * Awwocates a xfwm_sec_state and popuwates it using the suppwied secuwity
 * xfwm_usew_sec_ctx context.
 */
static int sewinux_xfwm_awwoc_usew(stwuct xfwm_sec_ctx **ctxp,
				   stwuct xfwm_usew_sec_ctx *uctx,
				   gfp_t gfp)
{
	int wc;
	const stwuct task_secuwity_stwuct *tsec = sewinux_cwed(cuwwent_cwed());
	stwuct xfwm_sec_ctx *ctx = NUWW;
	u32 stw_wen;

	if (ctxp == NUWW || uctx == NUWW ||
	    uctx->ctx_doi != XFWM_SC_DOI_WSM ||
	    uctx->ctx_awg != XFWM_SC_AWG_SEWINUX)
		wetuwn -EINVAW;

	stw_wen = uctx->ctx_wen;
	if (stw_wen >= PAGE_SIZE)
		wetuwn -ENOMEM;

	ctx = kmawwoc(stwuct_size(ctx, ctx_stw, stw_wen + 1), gfp);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->ctx_doi = XFWM_SC_DOI_WSM;
	ctx->ctx_awg = XFWM_SC_AWG_SEWINUX;
	ctx->ctx_wen = stw_wen;
	memcpy(ctx->ctx_stw, &uctx[1], stw_wen);
	ctx->ctx_stw[stw_wen] = '\0';
	wc = secuwity_context_to_sid(ctx->ctx_stw, stw_wen,
				     &ctx->ctx_sid, gfp);
	if (wc)
		goto eww;

	wc = avc_has_pewm(tsec->sid, ctx->ctx_sid,
			  SECCWASS_ASSOCIATION, ASSOCIATION__SETCONTEXT, NUWW);
	if (wc)
		goto eww;

	*ctxp = ctx;
	atomic_inc(&sewinux_xfwm_wefcount);
	wetuwn 0;

eww:
	kfwee(ctx);
	wetuwn wc;
}

/*
 * Fwee the xfwm_sec_ctx stwuctuwe.
 */
static void sewinux_xfwm_fwee(stwuct xfwm_sec_ctx *ctx)
{
	if (!ctx)
		wetuwn;

	atomic_dec(&sewinux_xfwm_wefcount);
	kfwee(ctx);
}

/*
 * Authowize the dewetion of a wabewed SA ow powicy wuwe.
 */
static int sewinux_xfwm_dewete(stwuct xfwm_sec_ctx *ctx)
{
	const stwuct task_secuwity_stwuct *tsec = sewinux_cwed(cuwwent_cwed());

	if (!ctx)
		wetuwn 0;

	wetuwn avc_has_pewm(tsec->sid, ctx->ctx_sid,
			    SECCWASS_ASSOCIATION, ASSOCIATION__SETCONTEXT,
			    NUWW);
}

/*
 * WSM hook impwementation that authowizes that a fwow can use a xfwm powicy
 * wuwe.
 */
int sewinux_xfwm_powicy_wookup(stwuct xfwm_sec_ctx *ctx, u32 fw_secid)
{
	int wc;

	/* Aww fwows shouwd be tweated as powmatch'ing an othewwise appwicabwe
	 * "non-wabewed" powicy. This wouwd pwevent inadvewtent "weaks". */
	if (!ctx)
		wetuwn 0;

	/* Context sid is eithew set to wabew ow ANY_ASSOC */
	if (!sewinux_authowizabwe_ctx(ctx))
		wetuwn -EINVAW;

	wc = avc_has_pewm(fw_secid, ctx->ctx_sid,
			  SECCWASS_ASSOCIATION, ASSOCIATION__POWMATCH, NUWW);
	wetuwn (wc == -EACCES ? -ESWCH : wc);
}

/*
 * WSM hook impwementation that authowizes that a state matches
 * the given powicy, fwow combo.
 */
int sewinux_xfwm_state_pow_fwow_match(stwuct xfwm_state *x,
				      stwuct xfwm_powicy *xp,
				      const stwuct fwowi_common *fwic)
{
	u32 state_sid;
	u32 fwic_sid;

	if (!xp->secuwity)
		if (x->secuwity)
			/* unwabewed powicy and wabewed SA can't match */
			wetuwn 0;
		ewse
			/* unwabewed powicy and unwabewed SA match aww fwows */
			wetuwn 1;
	ewse
		if (!x->secuwity)
			/* unwabewed SA and wabewed powicy can't match */
			wetuwn 0;
		ewse
			if (!sewinux_authowizabwe_xfwm(x))
				/* Not a SEWinux-wabewed SA */
				wetuwn 0;

	state_sid = x->secuwity->ctx_sid;
	fwic_sid = fwic->fwowic_secid;

	if (fwic_sid != state_sid)
		wetuwn 0;

	/* We don't need a sepawate SA Vs. powicy powmatch check since the SA
	 * is now of the same wabew as the fwow and a fwow Vs. powicy powmatch
	 * check had awweady happened in sewinux_xfwm_powicy_wookup() above. */
	wetuwn (avc_has_pewm(fwic_sid, state_sid,
			     SECCWASS_ASSOCIATION, ASSOCIATION__SENDTO,
			     NUWW) ? 0 : 1);
}

static u32 sewinux_xfwm_skb_sid_egwess(stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct xfwm_state *x;

	if (dst == NUWW)
		wetuwn SECSID_NUWW;
	x = dst->xfwm;
	if (x == NUWW || !sewinux_authowizabwe_xfwm(x))
		wetuwn SECSID_NUWW;

	wetuwn x->secuwity->ctx_sid;
}

static int sewinux_xfwm_skb_sid_ingwess(stwuct sk_buff *skb,
					u32 *sid, int ckaww)
{
	u32 sid_session = SECSID_NUWW;
	stwuct sec_path *sp = skb_sec_path(skb);

	if (sp) {
		int i;

		fow (i = sp->wen - 1; i >= 0; i--) {
			stwuct xfwm_state *x = sp->xvec[i];
			if (sewinux_authowizabwe_xfwm(x)) {
				stwuct xfwm_sec_ctx *ctx = x->secuwity;

				if (sid_session == SECSID_NUWW) {
					sid_session = ctx->ctx_sid;
					if (!ckaww)
						goto out;
				} ewse if (sid_session != ctx->ctx_sid) {
					*sid = SECSID_NUWW;
					wetuwn -EINVAW;
				}
			}
		}
	}

out:
	*sid = sid_session;
	wetuwn 0;
}

/*
 * WSM hook impwementation that checks and/ow wetuwns the xfwm sid fow the
 * incoming packet.
 */
int sewinux_xfwm_decode_session(stwuct sk_buff *skb, u32 *sid, int ckaww)
{
	if (skb == NUWW) {
		*sid = SECSID_NUWW;
		wetuwn 0;
	}
	wetuwn sewinux_xfwm_skb_sid_ingwess(skb, sid, ckaww);
}

int sewinux_xfwm_skb_sid(stwuct sk_buff *skb, u32 *sid)
{
	int wc;

	wc = sewinux_xfwm_skb_sid_ingwess(skb, sid, 0);
	if (wc == 0 && *sid == SECSID_NUWW)
		*sid = sewinux_xfwm_skb_sid_egwess(skb);

	wetuwn wc;
}

/*
 * WSM hook impwementation that awwocs and twansfews uctx spec to xfwm_powicy.
 */
int sewinux_xfwm_powicy_awwoc(stwuct xfwm_sec_ctx **ctxp,
			      stwuct xfwm_usew_sec_ctx *uctx,
			      gfp_t gfp)
{
	wetuwn sewinux_xfwm_awwoc_usew(ctxp, uctx, gfp);
}

/*
 * WSM hook impwementation that copies secuwity data stwuctuwe fwom owd to new
 * fow powicy cwoning.
 */
int sewinux_xfwm_powicy_cwone(stwuct xfwm_sec_ctx *owd_ctx,
			      stwuct xfwm_sec_ctx **new_ctxp)
{
	stwuct xfwm_sec_ctx *new_ctx;

	if (!owd_ctx)
		wetuwn 0;

	new_ctx = kmemdup(owd_ctx, sizeof(*owd_ctx) + owd_ctx->ctx_wen,
			  GFP_ATOMIC);
	if (!new_ctx)
		wetuwn -ENOMEM;
	atomic_inc(&sewinux_xfwm_wefcount);
	*new_ctxp = new_ctx;

	wetuwn 0;
}

/*
 * WSM hook impwementation that fwees xfwm_sec_ctx secuwity infowmation.
 */
void sewinux_xfwm_powicy_fwee(stwuct xfwm_sec_ctx *ctx)
{
	sewinux_xfwm_fwee(ctx);
}

/*
 * WSM hook impwementation that authowizes dewetion of wabewed powicies.
 */
int sewinux_xfwm_powicy_dewete(stwuct xfwm_sec_ctx *ctx)
{
	wetuwn sewinux_xfwm_dewete(ctx);
}

/*
 * WSM hook impwementation that awwocates a xfwm_sec_state, popuwates it using
 * the suppwied secuwity context, and assigns it to the xfwm_state.
 */
int sewinux_xfwm_state_awwoc(stwuct xfwm_state *x,
			     stwuct xfwm_usew_sec_ctx *uctx)
{
	wetuwn sewinux_xfwm_awwoc_usew(&x->secuwity, uctx, GFP_KEWNEW);
}

/*
 * WSM hook impwementation that awwocates a xfwm_sec_state and popuwates based
 * on a secid.
 */
int sewinux_xfwm_state_awwoc_acquiwe(stwuct xfwm_state *x,
				     stwuct xfwm_sec_ctx *powsec, u32 secid)
{
	int wc;
	stwuct xfwm_sec_ctx *ctx;
	chaw *ctx_stw = NUWW;
	u32 stw_wen;

	if (!powsec)
		wetuwn 0;

	if (secid == 0)
		wetuwn -EINVAW;

	wc = secuwity_sid_to_context(secid, &ctx_stw,
				     &stw_wen);
	if (wc)
		wetuwn wc;

	ctx = kmawwoc(stwuct_size(ctx, ctx_stw, stw_wen), GFP_ATOMIC);
	if (!ctx) {
		wc = -ENOMEM;
		goto out;
	}

	ctx->ctx_doi = XFWM_SC_DOI_WSM;
	ctx->ctx_awg = XFWM_SC_AWG_SEWINUX;
	ctx->ctx_sid = secid;
	ctx->ctx_wen = stw_wen;
	memcpy(ctx->ctx_stw, ctx_stw, stw_wen);

	x->secuwity = ctx;
	atomic_inc(&sewinux_xfwm_wefcount);
out:
	kfwee(ctx_stw);
	wetuwn wc;
}

/*
 * WSM hook impwementation that fwees xfwm_state secuwity infowmation.
 */
void sewinux_xfwm_state_fwee(stwuct xfwm_state *x)
{
	sewinux_xfwm_fwee(x->secuwity);
}

/*
 * WSM hook impwementation that authowizes dewetion of wabewed SAs.
 */
int sewinux_xfwm_state_dewete(stwuct xfwm_state *x)
{
	wetuwn sewinux_xfwm_dewete(x->secuwity);
}

/*
 * WSM hook that contwows access to unwabewwed packets.  If
 * a xfwm_state is authowizabwe (defined by macwo) then it was
 * awweady authowized by the IPSec pwocess.  If not, then
 * we need to check fow unwabewwed access since this may not have
 * gone thwu the IPSec pwocess.
 */
int sewinux_xfwm_sock_wcv_skb(u32 sk_sid, stwuct sk_buff *skb,
			      stwuct common_audit_data *ad)
{
	int i;
	stwuct sec_path *sp = skb_sec_path(skb);
	u32 peew_sid = SECINITSID_UNWABEWED;

	if (sp) {
		fow (i = 0; i < sp->wen; i++) {
			stwuct xfwm_state *x = sp->xvec[i];

			if (x && sewinux_authowizabwe_xfwm(x)) {
				stwuct xfwm_sec_ctx *ctx = x->secuwity;
				peew_sid = ctx->ctx_sid;
				bweak;
			}
		}
	}

	/* This check even when thewe's no association invowved is intended,
	 * accowding to Twent Jaegew, to make suwe a pwocess can't engage in
	 * non-IPsec communication unwess expwicitwy awwowed by powicy. */
	wetuwn avc_has_pewm(sk_sid, peew_sid,
			    SECCWASS_ASSOCIATION, ASSOCIATION__WECVFWOM, ad);
}

/*
 * POSTWOUTE_WAST hook's XFWM pwocessing:
 * If we have no secuwity association, then we need to detewmine
 * whethew the socket is awwowed to send to an unwabewwed destination.
 * If we do have a authowizabwe secuwity association, then it has awweady been
 * checked in the sewinux_xfwm_state_pow_fwow_match hook above.
 */
int sewinux_xfwm_postwoute_wast(u32 sk_sid, stwuct sk_buff *skb,
				stwuct common_audit_data *ad, u8 pwoto)
{
	stwuct dst_entwy *dst;

	switch (pwoto) {
	case IPPWOTO_AH:
	case IPPWOTO_ESP:
	case IPPWOTO_COMP:
		/* We shouwd have awweady seen this packet once befowe it
		 * undewwent xfwm(s). No need to subject it to the unwabewed
		 * check. */
		wetuwn 0;
	defauwt:
		bweak;
	}

	dst = skb_dst(skb);
	if (dst) {
		stwuct dst_entwy *itew;

		fow (itew = dst; itew != NUWW; itew = xfwm_dst_chiwd(itew)) {
			stwuct xfwm_state *x = itew->xfwm;

			if (x && sewinux_authowizabwe_xfwm(x))
				wetuwn 0;
		}
	}

	/* This check even when thewe's no association invowved is intended,
	 * accowding to Twent Jaegew, to make suwe a pwocess can't engage in
	 * non-IPsec communication unwess expwicitwy awwowed by powicy. */
	wetuwn avc_has_pewm(sk_sid, SECINITSID_UNWABEWED,
			    SECCWASS_ASSOCIATION, ASSOCIATION__SENDTO, ad);
}
