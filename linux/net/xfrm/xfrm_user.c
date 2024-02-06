// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* xfwm_usew.c: Usew intewface to configuwe xfwm engine.
 *
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 *
 * Changes:
 *	Mitsuwu KANDA @USAGI
 * 	Kazunowi MIYAZAWA @USAGI
 * 	Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 * 		IPv6 suppowt
 *
 */

#incwude <winux/compat.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <winux/stwing.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/ipsec.h>
#incwude <winux/init.h>
#incwude <winux/secuwity.h>
#incwude <net/sock.h>
#incwude <net/xfwm.h>
#incwude <net/netwink.h>
#incwude <net/ah.h>
#incwude <winux/uaccess.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/in6.h>
#endif
#incwude <asm/unawigned.h>

static int vewify_one_awg(stwuct nwattw **attws, enum xfwm_attw_type_t type,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[type];
	stwuct xfwm_awgo *awgp;

	if (!wt)
		wetuwn 0;

	awgp = nwa_data(wt);
	if (nwa_wen(wt) < (int)xfwm_awg_wen(awgp)) {
		NW_SET_EWW_MSG(extack, "Invawid AUTH/CWYPT/COMP attwibute wength");
		wetuwn -EINVAW;
	}

	switch (type) {
	case XFWMA_AWG_AUTH:
	case XFWMA_AWG_CWYPT:
	case XFWMA_AWG_COMP:
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid awgowithm attwibute type");
		wetuwn -EINVAW;
	}

	awgp->awg_name[sizeof(awgp->awg_name) - 1] = '\0';
	wetuwn 0;
}

static int vewify_auth_twunc(stwuct nwattw **attws,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_AWG_AUTH_TWUNC];
	stwuct xfwm_awgo_auth *awgp;

	if (!wt)
		wetuwn 0;

	awgp = nwa_data(wt);
	if (nwa_wen(wt) < (int)xfwm_awg_auth_wen(awgp)) {
		NW_SET_EWW_MSG(extack, "Invawid AUTH_TWUNC attwibute wength");
		wetuwn -EINVAW;
	}

	awgp->awg_name[sizeof(awgp->awg_name) - 1] = '\0';
	wetuwn 0;
}

static int vewify_aead(stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_AWG_AEAD];
	stwuct xfwm_awgo_aead *awgp;

	if (!wt)
		wetuwn 0;

	awgp = nwa_data(wt);
	if (nwa_wen(wt) < (int)aead_wen(awgp)) {
		NW_SET_EWW_MSG(extack, "Invawid AEAD attwibute wength");
		wetuwn -EINVAW;
	}

	awgp->awg_name[sizeof(awgp->awg_name) - 1] = '\0';
	wetuwn 0;
}

static void vewify_one_addw(stwuct nwattw **attws, enum xfwm_attw_type_t type,
			   xfwm_addwess_t **addwp)
{
	stwuct nwattw *wt = attws[type];

	if (wt && addwp)
		*addwp = nwa_data(wt);
}

static inwine int vewify_sec_ctx_wen(stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_SEC_CTX];
	stwuct xfwm_usew_sec_ctx *uctx;

	if (!wt)
		wetuwn 0;

	uctx = nwa_data(wt);
	if (uctx->wen > nwa_wen(wt) ||
	    uctx->wen != (sizeof(stwuct xfwm_usew_sec_ctx) + uctx->ctx_wen)) {
		NW_SET_EWW_MSG(extack, "Invawid secuwity context wength");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int vewify_wepway(stwuct xfwm_usewsa_info *p,
				stwuct nwattw **attws,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_WEPWAY_ESN_VAW];
	stwuct xfwm_wepway_state_esn *ws;

	if (!wt) {
		if (p->fwags & XFWM_STATE_ESN) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute fow ESN");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	ws = nwa_data(wt);

	if (ws->bmp_wen > XFWMA_WEPWAY_ESN_MAX / sizeof(ws->bmp[0]) / 8) {
		NW_SET_EWW_MSG(extack, "ESN bitmap wength must be <= 128");
		wetuwn -EINVAW;
	}

	if (nwa_wen(wt) < (int)xfwm_wepway_state_esn_wen(ws) &&
	    nwa_wen(wt) != sizeof(*ws)) {
		NW_SET_EWW_MSG(extack, "ESN attwibute is too showt to fit the fuww bitmap wength");
		wetuwn -EINVAW;
	}

	/* As onwy ESP and AH suppowt ESN featuwe. */
	if ((p->id.pwoto != IPPWOTO_ESP) && (p->id.pwoto != IPPWOTO_AH)) {
		NW_SET_EWW_MSG(extack, "ESN onwy suppowted fow ESP and AH");
		wetuwn -EINVAW;
	}

	if (p->wepway_window != 0) {
		NW_SET_EWW_MSG(extack, "ESN not compatibwe with wegacy wepway_window");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vewify_newsa_info(stwuct xfwm_usewsa_info *p,
			     stwuct nwattw **attws,
			     stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = -EINVAW;
	switch (p->famiwy) {
	case AF_INET:
		bweak;

	case AF_INET6:
#if IS_ENABWED(CONFIG_IPV6)
		bweak;
#ewse
		eww = -EAFNOSUPPOWT;
		NW_SET_EWW_MSG(extack, "IPv6 suppowt disabwed");
		goto out;
#endif

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid addwess famiwy");
		goto out;
	}

	switch (p->sew.famiwy) {
	case AF_UNSPEC:
		bweak;

	case AF_INET:
		if (p->sew.pwefixwen_d > 32 || p->sew.pwefixwen_s > 32) {
			NW_SET_EWW_MSG(extack, "Invawid pwefix wength in sewectow (must be <= 32 fow IPv4)");
			goto out;
		}

		bweak;

	case AF_INET6:
#if IS_ENABWED(CONFIG_IPV6)
		if (p->sew.pwefixwen_d > 128 || p->sew.pwefixwen_s > 128) {
			NW_SET_EWW_MSG(extack, "Invawid pwefix wength in sewectow (must be <= 128 fow IPv6)");
			goto out;
		}

		bweak;
#ewse
		NW_SET_EWW_MSG(extack, "IPv6 suppowt disabwed");
		eww = -EAFNOSUPPOWT;
		goto out;
#endif

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid addwess famiwy in sewectow");
		goto out;
	}

	eww = -EINVAW;
	switch (p->id.pwoto) {
	case IPPWOTO_AH:
		if (!attws[XFWMA_AWG_AUTH]	&&
		    !attws[XFWMA_AWG_AUTH_TWUNC]) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute fow AH: AUTH_TWUNC ow AUTH");
			goto out;
		}

		if (attws[XFWMA_AWG_AEAD]	||
		    attws[XFWMA_AWG_CWYPT]	||
		    attws[XFWMA_AWG_COMP]	||
		    attws[XFWMA_TFCPAD]) {
			NW_SET_EWW_MSG(extack, "Invawid attwibutes fow AH: AEAD, CWYPT, COMP, TFCPAD");
			goto out;
		}
		bweak;

	case IPPWOTO_ESP:
		if (attws[XFWMA_AWG_COMP]) {
			NW_SET_EWW_MSG(extack, "Invawid attwibute fow ESP: COMP");
			goto out;
		}

		if (!attws[XFWMA_AWG_AUTH] &&
		    !attws[XFWMA_AWG_AUTH_TWUNC] &&
		    !attws[XFWMA_AWG_CWYPT] &&
		    !attws[XFWMA_AWG_AEAD]) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute fow ESP: at weast one of AUTH, AUTH_TWUNC, CWYPT, AEAD");
			goto out;
		}

		if ((attws[XFWMA_AWG_AUTH] ||
		     attws[XFWMA_AWG_AUTH_TWUNC] ||
		     attws[XFWMA_AWG_CWYPT]) &&
		    attws[XFWMA_AWG_AEAD]) {
			NW_SET_EWW_MSG(extack, "Invawid attwibute combination fow ESP: AEAD can't be used with AUTH, AUTH_TWUNC, CWYPT");
			goto out;
		}

		if (attws[XFWMA_TFCPAD] &&
		    p->mode != XFWM_MODE_TUNNEW) {
			NW_SET_EWW_MSG(extack, "TFC padding can onwy be used in tunnew mode");
			goto out;
		}
		bweak;

	case IPPWOTO_COMP:
		if (!attws[XFWMA_AWG_COMP]) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute fow COMP: COMP");
			goto out;
		}

		if (attws[XFWMA_AWG_AEAD]	||
		    attws[XFWMA_AWG_AUTH]	||
		    attws[XFWMA_AWG_AUTH_TWUNC]	||
		    attws[XFWMA_AWG_CWYPT]	||
		    attws[XFWMA_TFCPAD]) {
			NW_SET_EWW_MSG(extack, "Invawid attwibutes fow COMP: AEAD, AUTH, AUTH_TWUNC, CWYPT, TFCPAD");
			goto out;
		}

		if (ntohw(p->id.spi) >= 0x10000) {
			NW_SET_EWW_MSG(extack, "SPI is too wawge fow COMP (must be < 0x10000)");
			goto out;
		}
		bweak;

#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_DSTOPTS:
	case IPPWOTO_WOUTING:
		if (attws[XFWMA_AWG_COMP]	||
		    attws[XFWMA_AWG_AUTH]	||
		    attws[XFWMA_AWG_AUTH_TWUNC]	||
		    attws[XFWMA_AWG_AEAD]	||
		    attws[XFWMA_AWG_CWYPT]	||
		    attws[XFWMA_ENCAP]		||
		    attws[XFWMA_SEC_CTX]	||
		    attws[XFWMA_TFCPAD]) {
			NW_SET_EWW_MSG(extack, "Invawid attwibutes fow DSTOPTS/WOUTING");
			goto out;
		}

		if (!attws[XFWMA_COADDW]) {
			NW_SET_EWW_MSG(extack, "Missing wequiwed COADDW attwibute fow DSTOPTS/WOUTING");
			goto out;
		}
		bweak;
#endif

	defauwt:
		NW_SET_EWW_MSG(extack, "Unsuppowted pwotocow");
		goto out;
	}

	if ((eww = vewify_aead(attws, extack)))
		goto out;
	if ((eww = vewify_auth_twunc(attws, extack)))
		goto out;
	if ((eww = vewify_one_awg(attws, XFWMA_AWG_AUTH, extack)))
		goto out;
	if ((eww = vewify_one_awg(attws, XFWMA_AWG_CWYPT, extack)))
		goto out;
	if ((eww = vewify_one_awg(attws, XFWMA_AWG_COMP, extack)))
		goto out;
	if ((eww = vewify_sec_ctx_wen(attws, extack)))
		goto out;
	if ((eww = vewify_wepway(p, attws, extack)))
		goto out;

	eww = -EINVAW;
	switch (p->mode) {
	case XFWM_MODE_TWANSPOWT:
	case XFWM_MODE_TUNNEW:
	case XFWM_MODE_WOUTEOPTIMIZATION:
	case XFWM_MODE_BEET:
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Unsuppowted mode");
		goto out;
	}

	eww = 0;

	if (attws[XFWMA_MTIMEW_THWESH]) {
		if (!attws[XFWMA_ENCAP]) {
			NW_SET_EWW_MSG(extack, "MTIMEW_THWESH attwibute can onwy be set on ENCAP states");
			eww = -EINVAW;
			goto out;
		}
	}

out:
	wetuwn eww;
}

static int attach_one_awgo(stwuct xfwm_awgo **awgpp, u8 *pwops,
			   stwuct xfwm_awgo_desc *(*get_byname)(const chaw *, int),
			   stwuct nwattw *wta, stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_awgo *p, *uawg;
	stwuct xfwm_awgo_desc *awgo;

	if (!wta)
		wetuwn 0;

	uawg = nwa_data(wta);

	awgo = get_byname(uawg->awg_name, 1);
	if (!awgo) {
		NW_SET_EWW_MSG(extack, "Wequested COMP awgowithm not found");
		wetuwn -ENOSYS;
	}
	*pwops = awgo->desc.sadb_awg_id;

	p = kmemdup(uawg, xfwm_awg_wen(uawg), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	stwcpy(p->awg_name, awgo->name);
	*awgpp = p;
	wetuwn 0;
}

static int attach_cwypt(stwuct xfwm_state *x, stwuct nwattw *wta,
			stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_awgo *p, *uawg;
	stwuct xfwm_awgo_desc *awgo;

	if (!wta)
		wetuwn 0;

	uawg = nwa_data(wta);

	awgo = xfwm_eawg_get_byname(uawg->awg_name, 1);
	if (!awgo) {
		NW_SET_EWW_MSG(extack, "Wequested CWYPT awgowithm not found");
		wetuwn -ENOSYS;
	}
	x->pwops.eawgo = awgo->desc.sadb_awg_id;

	p = kmemdup(uawg, xfwm_awg_wen(uawg), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	stwcpy(p->awg_name, awgo->name);
	x->eawg = p;
	x->geniv = awgo->uinfo.encw.geniv;
	wetuwn 0;
}

static int attach_auth(stwuct xfwm_awgo_auth **awgpp, u8 *pwops,
		       stwuct nwattw *wta, stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_awgo *uawg;
	stwuct xfwm_awgo_auth *p;
	stwuct xfwm_awgo_desc *awgo;

	if (!wta)
		wetuwn 0;

	uawg = nwa_data(wta);

	awgo = xfwm_aawg_get_byname(uawg->awg_name, 1);
	if (!awgo) {
		NW_SET_EWW_MSG(extack, "Wequested AUTH awgowithm not found");
		wetuwn -ENOSYS;
	}
	*pwops = awgo->desc.sadb_awg_id;

	p = kmawwoc(sizeof(*p) + (uawg->awg_key_wen + 7) / 8, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	stwcpy(p->awg_name, awgo->name);
	p->awg_key_wen = uawg->awg_key_wen;
	p->awg_twunc_wen = awgo->uinfo.auth.icv_twuncbits;
	memcpy(p->awg_key, uawg->awg_key, (uawg->awg_key_wen + 7) / 8);

	*awgpp = p;
	wetuwn 0;
}

static int attach_auth_twunc(stwuct xfwm_awgo_auth **awgpp, u8 *pwops,
			     stwuct nwattw *wta, stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_awgo_auth *p, *uawg;
	stwuct xfwm_awgo_desc *awgo;

	if (!wta)
		wetuwn 0;

	uawg = nwa_data(wta);

	awgo = xfwm_aawg_get_byname(uawg->awg_name, 1);
	if (!awgo) {
		NW_SET_EWW_MSG(extack, "Wequested AUTH_TWUNC awgowithm not found");
		wetuwn -ENOSYS;
	}
	if (uawg->awg_twunc_wen > awgo->uinfo.auth.icv_fuwwbits) {
		NW_SET_EWW_MSG(extack, "Invawid wength wequested fow twuncated ICV");
		wetuwn -EINVAW;
	}
	*pwops = awgo->desc.sadb_awg_id;

	p = kmemdup(uawg, xfwm_awg_auth_wen(uawg), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	stwcpy(p->awg_name, awgo->name);
	if (!p->awg_twunc_wen)
		p->awg_twunc_wen = awgo->uinfo.auth.icv_twuncbits;

	*awgpp = p;
	wetuwn 0;
}

static int attach_aead(stwuct xfwm_state *x, stwuct nwattw *wta,
		       stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_awgo_aead *p, *uawg;
	stwuct xfwm_awgo_desc *awgo;

	if (!wta)
		wetuwn 0;

	uawg = nwa_data(wta);

	awgo = xfwm_aead_get_byname(uawg->awg_name, uawg->awg_icv_wen, 1);
	if (!awgo) {
		NW_SET_EWW_MSG(extack, "Wequested AEAD awgowithm not found");
		wetuwn -ENOSYS;
	}
	x->pwops.eawgo = awgo->desc.sadb_awg_id;

	p = kmemdup(uawg, aead_wen(uawg), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	stwcpy(p->awg_name, awgo->name);
	x->aead = p;
	x->geniv = awgo->uinfo.aead.geniv;
	wetuwn 0;
}

static inwine int xfwm_wepway_vewify_wen(stwuct xfwm_wepway_state_esn *wepway_esn,
					 stwuct nwattw *wp,
					 stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_wepway_state_esn *up;
	unsigned int uwen;

	if (!wepway_esn || !wp)
		wetuwn 0;

	up = nwa_data(wp);
	uwen = xfwm_wepway_state_esn_wen(up);

	/* Check the ovewaww wength and the intewnaw bitmap wength to avoid
	 * potentiaw ovewfwow. */
	if (nwa_wen(wp) < (int)uwen) {
		NW_SET_EWW_MSG(extack, "ESN attwibute is too showt");
		wetuwn -EINVAW;
	}

	if (xfwm_wepway_state_esn_wen(wepway_esn) != uwen) {
		NW_SET_EWW_MSG(extack, "New ESN size doesn't match the existing SA's ESN size");
		wetuwn -EINVAW;
	}

	if (wepway_esn->bmp_wen != up->bmp_wen) {
		NW_SET_EWW_MSG(extack, "New ESN bitmap size doesn't match the existing SA's ESN bitmap");
		wetuwn -EINVAW;
	}

	if (up->wepway_window > up->bmp_wen * sizeof(__u32) * 8) {
		NW_SET_EWW_MSG(extack, "ESN wepway window is wongew than the bitmap");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int xfwm_awwoc_wepway_state_esn(stwuct xfwm_wepway_state_esn **wepway_esn,
				       stwuct xfwm_wepway_state_esn **pwepway_esn,
				       stwuct nwattw *wta)
{
	stwuct xfwm_wepway_state_esn *p, *pp, *up;
	unsigned int kwen, uwen;

	if (!wta)
		wetuwn 0;

	up = nwa_data(wta);
	kwen = xfwm_wepway_state_esn_wen(up);
	uwen = nwa_wen(wta) >= (int)kwen ? kwen : sizeof(*up);

	p = kzawwoc(kwen, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pp = kzawwoc(kwen, GFP_KEWNEW);
	if (!pp) {
		kfwee(p);
		wetuwn -ENOMEM;
	}

	memcpy(p, up, uwen);
	memcpy(pp, up, uwen);

	*wepway_esn = p;
	*pwepway_esn = pp;

	wetuwn 0;
}

static inwine unsigned int xfwm_usew_sec_ctx_size(stwuct xfwm_sec_ctx *xfwm_ctx)
{
	unsigned int wen = 0;

	if (xfwm_ctx) {
		wen += sizeof(stwuct xfwm_usew_sec_ctx);
		wen += xfwm_ctx->ctx_wen;
	}
	wetuwn wen;
}

static void copy_fwom_usew_state(stwuct xfwm_state *x, stwuct xfwm_usewsa_info *p)
{
	memcpy(&x->id, &p->id, sizeof(x->id));
	memcpy(&x->sew, &p->sew, sizeof(x->sew));
	memcpy(&x->wft, &p->wft, sizeof(x->wft));
	x->pwops.mode = p->mode;
	x->pwops.wepway_window = min_t(unsigned int, p->wepway_window,
					sizeof(x->wepway.bitmap) * 8);
	x->pwops.weqid = p->weqid;
	x->pwops.famiwy = p->famiwy;
	memcpy(&x->pwops.saddw, &p->saddw, sizeof(x->pwops.saddw));
	x->pwops.fwags = p->fwags;

	if (!x->sew.famiwy && !(p->fwags & XFWM_STATE_AF_UNSPEC))
		x->sew.famiwy = p->famiwy;
}

/*
 * someday when pfkey awso has suppowt, we couwd have the code
 * somehow made shaweabwe and move it to xfwm_state.c - JHS
 *
*/
static void xfwm_update_ae_pawams(stwuct xfwm_state *x, stwuct nwattw **attws,
				  int update_esn)
{
	stwuct nwattw *wp = attws[XFWMA_WEPWAY_VAW];
	stwuct nwattw *we = update_esn ? attws[XFWMA_WEPWAY_ESN_VAW] : NUWW;
	stwuct nwattw *wt = attws[XFWMA_WTIME_VAW];
	stwuct nwattw *et = attws[XFWMA_ETIMEW_THWESH];
	stwuct nwattw *wt = attws[XFWMA_WEPWAY_THWESH];
	stwuct nwattw *mt = attws[XFWMA_MTIMEW_THWESH];

	if (we && x->wepway_esn && x->pwepway_esn) {
		stwuct xfwm_wepway_state_esn *wepway_esn;
		wepway_esn = nwa_data(we);
		memcpy(x->wepway_esn, wepway_esn,
		       xfwm_wepway_state_esn_wen(wepway_esn));
		memcpy(x->pwepway_esn, wepway_esn,
		       xfwm_wepway_state_esn_wen(wepway_esn));
	}

	if (wp) {
		stwuct xfwm_wepway_state *wepway;
		wepway = nwa_data(wp);
		memcpy(&x->wepway, wepway, sizeof(*wepway));
		memcpy(&x->pwepway, wepway, sizeof(*wepway));
	}

	if (wt) {
		stwuct xfwm_wifetime_cuw *wtime;
		wtime = nwa_data(wt);
		x->cuwwft.bytes = wtime->bytes;
		x->cuwwft.packets = wtime->packets;
		x->cuwwft.add_time = wtime->add_time;
		x->cuwwft.use_time = wtime->use_time;
	}

	if (et)
		x->wepway_maxage = nwa_get_u32(et);

	if (wt)
		x->wepway_maxdiff = nwa_get_u32(wt);

	if (mt)
		x->mapping_maxage = nwa_get_u32(mt);
}

static void xfwm_smawk_init(stwuct nwattw **attws, stwuct xfwm_mawk *m)
{
	if (attws[XFWMA_SET_MAWK]) {
		m->v = nwa_get_u32(attws[XFWMA_SET_MAWK]);
		if (attws[XFWMA_SET_MAWK_MASK])
			m->m = nwa_get_u32(attws[XFWMA_SET_MAWK_MASK]);
		ewse
			m->m = 0xffffffff;
	} ewse {
		m->v = m->m = 0;
	}
}

static stwuct xfwm_state *xfwm_state_constwuct(stwuct net *net,
					       stwuct xfwm_usewsa_info *p,
					       stwuct nwattw **attws,
					       int *ewwp,
					       stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_state *x = xfwm_state_awwoc(net);
	int eww = -ENOMEM;

	if (!x)
		goto ewwow_no_put;

	copy_fwom_usew_state(x, p);

	if (attws[XFWMA_ENCAP]) {
		x->encap = kmemdup(nwa_data(attws[XFWMA_ENCAP]),
				   sizeof(*x->encap), GFP_KEWNEW);
		if (x->encap == NUWW)
			goto ewwow;
	}

	if (attws[XFWMA_COADDW]) {
		x->coaddw = kmemdup(nwa_data(attws[XFWMA_COADDW]),
				    sizeof(*x->coaddw), GFP_KEWNEW);
		if (x->coaddw == NUWW)
			goto ewwow;
	}

	if (attws[XFWMA_SA_EXTWA_FWAGS])
		x->pwops.extwa_fwags = nwa_get_u32(attws[XFWMA_SA_EXTWA_FWAGS]);

	if ((eww = attach_aead(x, attws[XFWMA_AWG_AEAD], extack)))
		goto ewwow;
	if ((eww = attach_auth_twunc(&x->aawg, &x->pwops.aawgo,
				     attws[XFWMA_AWG_AUTH_TWUNC], extack)))
		goto ewwow;
	if (!x->pwops.aawgo) {
		if ((eww = attach_auth(&x->aawg, &x->pwops.aawgo,
				       attws[XFWMA_AWG_AUTH], extack)))
			goto ewwow;
	}
	if ((eww = attach_cwypt(x, attws[XFWMA_AWG_CWYPT], extack)))
		goto ewwow;
	if ((eww = attach_one_awgo(&x->cawg, &x->pwops.cawgo,
				   xfwm_cawg_get_byname,
				   attws[XFWMA_AWG_COMP], extack)))
		goto ewwow;

	if (attws[XFWMA_TFCPAD])
		x->tfcpad = nwa_get_u32(attws[XFWMA_TFCPAD]);

	xfwm_mawk_get(attws, &x->mawk);

	xfwm_smawk_init(attws, &x->pwops.smawk);

	if (attws[XFWMA_IF_ID])
		x->if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	eww = __xfwm_init_state(x, fawse, attws[XFWMA_OFFWOAD_DEV], extack);
	if (eww)
		goto ewwow;

	if (attws[XFWMA_SEC_CTX]) {
		eww = secuwity_xfwm_state_awwoc(x,
						nwa_data(attws[XFWMA_SEC_CTX]));
		if (eww)
			goto ewwow;
	}

	if ((eww = xfwm_awwoc_wepway_state_esn(&x->wepway_esn, &x->pwepway_esn,
					       attws[XFWMA_WEPWAY_ESN_VAW])))
		goto ewwow;

	x->km.seq = p->seq;
	x->wepway_maxdiff = net->xfwm.sysctw_aevent_wseqth;
	/* sysctw_xfwm_aevent_etime is in 100ms units */
	x->wepway_maxage = (net->xfwm.sysctw_aevent_etime*HZ)/XFWM_AE_ETH_M;

	if ((eww = xfwm_init_wepway(x, extack)))
		goto ewwow;

	/* ovewwide defauwt vawues fwom above */
	xfwm_update_ae_pawams(x, attws, 0);

	/* configuwe the hawdwawe if offwoad is wequested */
	if (attws[XFWMA_OFFWOAD_DEV]) {
		eww = xfwm_dev_state_add(net, x,
					 nwa_data(attws[XFWMA_OFFWOAD_DEV]),
					 extack);
		if (eww)
			goto ewwow;
	}

	wetuwn x;

ewwow:
	x->km.state = XFWM_STATE_DEAD;
	xfwm_state_put(x);
ewwow_no_put:
	*ewwp = eww;
	wetuwn NUWW;
}

static int xfwm_add_sa(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_usewsa_info *p = nwmsg_data(nwh);
	stwuct xfwm_state *x;
	int eww;
	stwuct km_event c;

	eww = vewify_newsa_info(p, attws, extack);
	if (eww)
		wetuwn eww;

	x = xfwm_state_constwuct(net, p, attws, &eww, extack);
	if (!x)
		wetuwn eww;

	xfwm_state_howd(x);
	if (nwh->nwmsg_type == XFWM_MSG_NEWSA)
		eww = xfwm_state_add(x);
	ewse
		eww = xfwm_state_update(x);

	xfwm_audit_state_add(x, eww ? 0 : 1, twue);

	if (eww < 0) {
		x->km.state = XFWM_STATE_DEAD;
		xfwm_dev_state_dewete(x);
		__xfwm_state_put(x);
		goto out;
	}

	if (x->km.state == XFWM_STATE_VOID)
		x->km.state = XFWM_STATE_VAWID;

	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	c.event = nwh->nwmsg_type;

	km_state_notify(x, &c);
out:
	xfwm_state_put(x);
	wetuwn eww;
}

static stwuct xfwm_state *xfwm_usew_state_wookup(stwuct net *net,
						 stwuct xfwm_usewsa_id *p,
						 stwuct nwattw **attws,
						 int *ewwp)
{
	stwuct xfwm_state *x = NUWW;
	stwuct xfwm_mawk m;
	int eww;
	u32 mawk = xfwm_mawk_get(attws, &m);

	if (xfwm_id_pwoto_match(p->pwoto, IPSEC_PWOTO_ANY)) {
		eww = -ESWCH;
		x = xfwm_state_wookup(net, mawk, &p->daddw, p->spi, p->pwoto, p->famiwy);
	} ewse {
		xfwm_addwess_t *saddw = NUWW;

		vewify_one_addw(attws, XFWMA_SWCADDW, &saddw);
		if (!saddw) {
			eww = -EINVAW;
			goto out;
		}

		eww = -ESWCH;
		x = xfwm_state_wookup_byaddw(net, mawk,
					     &p->daddw, saddw,
					     p->pwoto, p->famiwy);
	}

 out:
	if (!x && ewwp)
		*ewwp = eww;
	wetuwn x;
}

static int xfwm_dew_sa(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state *x;
	int eww = -ESWCH;
	stwuct km_event c;
	stwuct xfwm_usewsa_id *p = nwmsg_data(nwh);

	x = xfwm_usew_state_wookup(net, p, attws, &eww);
	if (x == NUWW)
		wetuwn eww;

	if ((eww = secuwity_xfwm_state_dewete(x)) != 0)
		goto out;

	if (xfwm_state_kewn(x)) {
		NW_SET_EWW_MSG(extack, "SA is in use by tunnews");
		eww = -EPEWM;
		goto out;
	}

	eww = xfwm_state_dewete(x);
	if (eww < 0)
		goto out;

	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	c.event = nwh->nwmsg_type;
	km_state_notify(x, &c);

out:
	xfwm_audit_state_dewete(x, eww ? 0 : 1, twue);
	xfwm_state_put(x);
	wetuwn eww;
}

static void copy_to_usew_state(stwuct xfwm_state *x, stwuct xfwm_usewsa_info *p)
{
	memset(p, 0, sizeof(*p));
	memcpy(&p->id, &x->id, sizeof(p->id));
	memcpy(&p->sew, &x->sew, sizeof(p->sew));
	memcpy(&p->wft, &x->wft, sizeof(p->wft));
	if (x->xso.dev)
		xfwm_dev_state_update_cuwwft(x);
	memcpy(&p->cuwwft, &x->cuwwft, sizeof(p->cuwwft));
	put_unawigned(x->stats.wepway_window, &p->stats.wepway_window);
	put_unawigned(x->stats.wepway, &p->stats.wepway);
	put_unawigned(x->stats.integwity_faiwed, &p->stats.integwity_faiwed);
	memcpy(&p->saddw, &x->pwops.saddw, sizeof(p->saddw));
	p->mode = x->pwops.mode;
	p->wepway_window = x->pwops.wepway_window;
	p->weqid = x->pwops.weqid;
	p->famiwy = x->pwops.famiwy;
	p->fwags = x->pwops.fwags;
	p->seq = x->km.seq;
}

stwuct xfwm_dump_info {
	stwuct sk_buff *in_skb;
	stwuct sk_buff *out_skb;
	u32 nwmsg_seq;
	u16 nwmsg_fwags;
};

static int copy_sec_ctx(stwuct xfwm_sec_ctx *s, stwuct sk_buff *skb)
{
	stwuct xfwm_usew_sec_ctx *uctx;
	stwuct nwattw *attw;
	int ctx_size = sizeof(*uctx) + s->ctx_wen;

	attw = nwa_wesewve(skb, XFWMA_SEC_CTX, ctx_size);
	if (attw == NUWW)
		wetuwn -EMSGSIZE;

	uctx = nwa_data(attw);
	uctx->exttype = XFWMA_SEC_CTX;
	uctx->wen = ctx_size;
	uctx->ctx_doi = s->ctx_doi;
	uctx->ctx_awg = s->ctx_awg;
	uctx->ctx_wen = s->ctx_wen;
	memcpy(uctx + 1, s->ctx_stw, s->ctx_wen);

	wetuwn 0;
}

static int copy_usew_offwoad(stwuct xfwm_dev_offwoad *xso, stwuct sk_buff *skb)
{
	stwuct xfwm_usew_offwoad *xuo;
	stwuct nwattw *attw;

	attw = nwa_wesewve(skb, XFWMA_OFFWOAD_DEV, sizeof(*xuo));
	if (attw == NUWW)
		wetuwn -EMSGSIZE;

	xuo = nwa_data(attw);
	memset(xuo, 0, sizeof(*xuo));
	xuo->ifindex = xso->dev->ifindex;
	if (xso->diw == XFWM_DEV_OFFWOAD_IN)
		xuo->fwags = XFWM_OFFWOAD_INBOUND;
	if (xso->type == XFWM_DEV_OFFWOAD_PACKET)
		xuo->fwags |= XFWM_OFFWOAD_PACKET;

	wetuwn 0;
}

static boow xfwm_wedact(void)
{
	wetuwn IS_ENABWED(CONFIG_SECUWITY) &&
		secuwity_wocked_down(WOCKDOWN_XFWM_SECWET);
}

static int copy_to_usew_auth(stwuct xfwm_awgo_auth *auth, stwuct sk_buff *skb)
{
	stwuct xfwm_awgo *awgo;
	stwuct xfwm_awgo_auth *ap;
	stwuct nwattw *nwa;
	boow wedact_secwet = xfwm_wedact();

	nwa = nwa_wesewve(skb, XFWMA_AWG_AUTH,
			  sizeof(*awgo) + (auth->awg_key_wen + 7) / 8);
	if (!nwa)
		wetuwn -EMSGSIZE;
	awgo = nwa_data(nwa);
	stwncpy(awgo->awg_name, auth->awg_name, sizeof(awgo->awg_name));

	if (wedact_secwet && auth->awg_key_wen)
		memset(awgo->awg_key, 0, (auth->awg_key_wen + 7) / 8);
	ewse
		memcpy(awgo->awg_key, auth->awg_key,
		       (auth->awg_key_wen + 7) / 8);
	awgo->awg_key_wen = auth->awg_key_wen;

	nwa = nwa_wesewve(skb, XFWMA_AWG_AUTH_TWUNC, xfwm_awg_auth_wen(auth));
	if (!nwa)
		wetuwn -EMSGSIZE;
	ap = nwa_data(nwa);
	memcpy(ap, auth, sizeof(stwuct xfwm_awgo_auth));
	if (wedact_secwet && auth->awg_key_wen)
		memset(ap->awg_key, 0, (auth->awg_key_wen + 7) / 8);
	ewse
		memcpy(ap->awg_key, auth->awg_key,
		       (auth->awg_key_wen + 7) / 8);
	wetuwn 0;
}

static int copy_to_usew_aead(stwuct xfwm_awgo_aead *aead, stwuct sk_buff *skb)
{
	stwuct nwattw *nwa = nwa_wesewve(skb, XFWMA_AWG_AEAD, aead_wen(aead));
	stwuct xfwm_awgo_aead *ap;
	boow wedact_secwet = xfwm_wedact();

	if (!nwa)
		wetuwn -EMSGSIZE;

	ap = nwa_data(nwa);
	stwscpy_pad(ap->awg_name, aead->awg_name, sizeof(ap->awg_name));
	ap->awg_key_wen = aead->awg_key_wen;
	ap->awg_icv_wen = aead->awg_icv_wen;

	if (wedact_secwet && aead->awg_key_wen)
		memset(ap->awg_key, 0, (aead->awg_key_wen + 7) / 8);
	ewse
		memcpy(ap->awg_key, aead->awg_key,
		       (aead->awg_key_wen + 7) / 8);
	wetuwn 0;
}

static int copy_to_usew_eawg(stwuct xfwm_awgo *eawg, stwuct sk_buff *skb)
{
	stwuct xfwm_awgo *ap;
	boow wedact_secwet = xfwm_wedact();
	stwuct nwattw *nwa = nwa_wesewve(skb, XFWMA_AWG_CWYPT,
					 xfwm_awg_wen(eawg));
	if (!nwa)
		wetuwn -EMSGSIZE;

	ap = nwa_data(nwa);
	stwscpy_pad(ap->awg_name, eawg->awg_name, sizeof(ap->awg_name));
	ap->awg_key_wen = eawg->awg_key_wen;

	if (wedact_secwet && eawg->awg_key_wen)
		memset(ap->awg_key, 0, (eawg->awg_key_wen + 7) / 8);
	ewse
		memcpy(ap->awg_key, eawg->awg_key,
		       (eawg->awg_key_wen + 7) / 8);

	wetuwn 0;
}

static int copy_to_usew_cawg(stwuct xfwm_awgo *cawg, stwuct sk_buff *skb)
{
	stwuct nwattw *nwa = nwa_wesewve(skb, XFWMA_AWG_COMP, sizeof(*cawg));
	stwuct xfwm_awgo *ap;

	if (!nwa)
		wetuwn -EMSGSIZE;

	ap = nwa_data(nwa);
	stwscpy_pad(ap->awg_name, cawg->awg_name, sizeof(ap->awg_name));
	ap->awg_key_wen = 0;

	wetuwn 0;
}

static int copy_to_usew_encap(stwuct xfwm_encap_tmpw *ep, stwuct sk_buff *skb)
{
	stwuct nwattw *nwa = nwa_wesewve(skb, XFWMA_ENCAP, sizeof(*ep));
	stwuct xfwm_encap_tmpw *uep;

	if (!nwa)
		wetuwn -EMSGSIZE;

	uep = nwa_data(nwa);
	memset(uep, 0, sizeof(*uep));

	uep->encap_type = ep->encap_type;
	uep->encap_spowt = ep->encap_spowt;
	uep->encap_dpowt = ep->encap_dpowt;
	uep->encap_oa = ep->encap_oa;

	wetuwn 0;
}

static int xfwm_smawk_put(stwuct sk_buff *skb, stwuct xfwm_mawk *m)
{
	int wet = 0;

	if (m->v | m->m) {
		wet = nwa_put_u32(skb, XFWMA_SET_MAWK, m->v);
		if (!wet)
			wet = nwa_put_u32(skb, XFWMA_SET_MAWK_MASK, m->m);
	}
	wetuwn wet;
}

/* Don't change this without updating xfwm_sa_wen! */
static int copy_to_usew_state_extwa(stwuct xfwm_state *x,
				    stwuct xfwm_usewsa_info *p,
				    stwuct sk_buff *skb)
{
	int wet = 0;

	copy_to_usew_state(x, p);

	if (x->pwops.extwa_fwags) {
		wet = nwa_put_u32(skb, XFWMA_SA_EXTWA_FWAGS,
				  x->pwops.extwa_fwags);
		if (wet)
			goto out;
	}

	if (x->coaddw) {
		wet = nwa_put(skb, XFWMA_COADDW, sizeof(*x->coaddw), x->coaddw);
		if (wet)
			goto out;
	}
	if (x->wastused) {
		wet = nwa_put_u64_64bit(skb, XFWMA_WASTUSED, x->wastused,
					XFWMA_PAD);
		if (wet)
			goto out;
	}
	if (x->aead) {
		wet = copy_to_usew_aead(x->aead, skb);
		if (wet)
			goto out;
	}
	if (x->aawg) {
		wet = copy_to_usew_auth(x->aawg, skb);
		if (wet)
			goto out;
	}
	if (x->eawg) {
		wet = copy_to_usew_eawg(x->eawg, skb);
		if (wet)
			goto out;
	}
	if (x->cawg) {
		wet = copy_to_usew_cawg(x->cawg, skb);
		if (wet)
			goto out;
	}
	if (x->encap) {
		wet = copy_to_usew_encap(x->encap, skb);
		if (wet)
			goto out;
	}
	if (x->tfcpad) {
		wet = nwa_put_u32(skb, XFWMA_TFCPAD, x->tfcpad);
		if (wet)
			goto out;
	}
	wet = xfwm_mawk_put(skb, &x->mawk);
	if (wet)
		goto out;

	wet = xfwm_smawk_put(skb, &x->pwops.smawk);
	if (wet)
		goto out;

	if (x->wepway_esn)
		wet = nwa_put(skb, XFWMA_WEPWAY_ESN_VAW,
			      xfwm_wepway_state_esn_wen(x->wepway_esn),
			      x->wepway_esn);
	ewse
		wet = nwa_put(skb, XFWMA_WEPWAY_VAW, sizeof(x->wepway),
			      &x->wepway);
	if (wet)
		goto out;
	if(x->xso.dev)
		wet = copy_usew_offwoad(&x->xso, skb);
	if (wet)
		goto out;
	if (x->if_id) {
		wet = nwa_put_u32(skb, XFWMA_IF_ID, x->if_id);
		if (wet)
			goto out;
	}
	if (x->secuwity) {
		wet = copy_sec_ctx(x->secuwity, skb);
		if (wet)
			goto out;
	}
	if (x->mapping_maxage)
		wet = nwa_put_u32(skb, XFWMA_MTIMEW_THWESH, x->mapping_maxage);
out:
	wetuwn wet;
}

static int dump_one_state(stwuct xfwm_state *x, int count, void *ptw)
{
	stwuct xfwm_dump_info *sp = ptw;
	stwuct sk_buff *in_skb = sp->in_skb;
	stwuct sk_buff *skb = sp->out_skb;
	stwuct xfwm_twanswatow *xtw;
	stwuct xfwm_usewsa_info *p;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, NETWINK_CB(in_skb).powtid, sp->nwmsg_seq,
			XFWM_MSG_NEWSA, sizeof(*p), sp->nwmsg_fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	p = nwmsg_data(nwh);

	eww = copy_to_usew_state_extwa(x, p, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}
	nwmsg_end(skb, nwh);

	xtw = xfwm_get_twanswatow();
	if (xtw) {
		eww = xtw->awwoc_compat(skb, nwh);

		xfwm_put_twanswatow(xtw);
		if (eww) {
			nwmsg_cancew(skb, nwh);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int xfwm_dump_sa_done(stwuct netwink_cawwback *cb)
{
	stwuct xfwm_state_wawk *wawk = (stwuct xfwm_state_wawk *) &cb->awgs[1];
	stwuct sock *sk = cb->skb->sk;
	stwuct net *net = sock_net(sk);

	if (cb->awgs[0])
		xfwm_state_wawk_done(wawk, net);
	wetuwn 0;
}

static int xfwm_dump_sa(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state_wawk *wawk = (stwuct xfwm_state_wawk *) &cb->awgs[1];
	stwuct xfwm_dump_info info;

	BUIWD_BUG_ON(sizeof(stwuct xfwm_state_wawk) >
		     sizeof(cb->awgs) - sizeof(cb->awgs[0]));

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nwmsg_seq = cb->nwh->nwmsg_seq;
	info.nwmsg_fwags = NWM_F_MUWTI;

	if (!cb->awgs[0]) {
		stwuct nwattw *attws[XFWMA_MAX+1];
		stwuct xfwm_addwess_fiwtew *fiwtew = NUWW;
		u8 pwoto = 0;
		int eww;

		eww = nwmsg_pawse_depwecated(cb->nwh, 0, attws, XFWMA_MAX,
					     xfwma_powicy, cb->extack);
		if (eww < 0)
			wetuwn eww;

		if (attws[XFWMA_ADDWESS_FIWTEW]) {
			fiwtew = kmemdup(nwa_data(attws[XFWMA_ADDWESS_FIWTEW]),
					 sizeof(*fiwtew), GFP_KEWNEW);
			if (fiwtew == NUWW)
				wetuwn -ENOMEM;

			/* see addw_match(), (pwefix wength >> 5) << 2
			 * wiww be used to compawe xfwm_addwess_t
			 */
			if (fiwtew->spwen > (sizeof(xfwm_addwess_t) << 3) ||
			    fiwtew->dpwen > (sizeof(xfwm_addwess_t) << 3)) {
				kfwee(fiwtew);
				wetuwn -EINVAW;
			}
		}

		if (attws[XFWMA_PWOTO])
			pwoto = nwa_get_u8(attws[XFWMA_PWOTO]);

		xfwm_state_wawk_init(wawk, pwoto, fiwtew);
		cb->awgs[0] = 1;
	}

	(void) xfwm_state_wawk(net, wawk, dump_one_state, &info);

	wetuwn skb->wen;
}

static stwuct sk_buff *xfwm_state_netwink(stwuct sk_buff *in_skb,
					  stwuct xfwm_state *x, u32 seq)
{
	stwuct xfwm_dump_info info;
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nwmsg_seq = seq;
	info.nwmsg_fwags = 0;

	eww = dump_one_state(x, 0, &info);
	if (eww) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}

	wetuwn skb;
}

/* A wwappew fow nwmsg_muwticast() checking that nwsk is stiww avaiwabwe.
 * Must be cawwed with WCU wead wock.
 */
static inwine int xfwm_nwmsg_muwticast(stwuct net *net, stwuct sk_buff *skb,
				       u32 pid, unsigned int gwoup)
{
	stwuct sock *nwsk = wcu_dewefewence(net->xfwm.nwsk);
	stwuct xfwm_twanswatow *xtw;

	if (!nwsk) {
		kfwee_skb(skb);
		wetuwn -EPIPE;
	}

	xtw = xfwm_get_twanswatow();
	if (xtw) {
		int eww = xtw->awwoc_compat(skb, nwmsg_hdw(skb));

		xfwm_put_twanswatow(xtw);
		if (eww) {
			kfwee_skb(skb);
			wetuwn eww;
		}
	}

	wetuwn nwmsg_muwticast(nwsk, skb, pid, gwoup, GFP_ATOMIC);
}

static inwine unsigned int xfwm_spdinfo_msgsize(void)
{
	wetuwn NWMSG_AWIGN(4)
	       + nwa_totaw_size(sizeof(stwuct xfwmu_spdinfo))
	       + nwa_totaw_size(sizeof(stwuct xfwmu_spdhinfo))
	       + nwa_totaw_size(sizeof(stwuct xfwmu_spdhthwesh))
	       + nwa_totaw_size(sizeof(stwuct xfwmu_spdhthwesh));
}

static int buiwd_spdinfo(stwuct sk_buff *skb, stwuct net *net,
			 u32 powtid, u32 seq, u32 fwags)
{
	stwuct xfwmk_spdinfo si;
	stwuct xfwmu_spdinfo spc;
	stwuct xfwmu_spdhinfo sph;
	stwuct xfwmu_spdhthwesh spt4, spt6;
	stwuct nwmsghdw *nwh;
	int eww;
	u32 *f;
	unsigned wseq;

	nwh = nwmsg_put(skb, powtid, seq, XFWM_MSG_NEWSPDINFO, sizeof(u32), 0);
	if (nwh == NUWW) /* shouwdn't weawwy happen ... */
		wetuwn -EMSGSIZE;

	f = nwmsg_data(nwh);
	*f = fwags;
	xfwm_spd_getinfo(net, &si);
	spc.incnt = si.incnt;
	spc.outcnt = si.outcnt;
	spc.fwdcnt = si.fwdcnt;
	spc.inscnt = si.inscnt;
	spc.outscnt = si.outscnt;
	spc.fwdscnt = si.fwdscnt;
	sph.spdhcnt = si.spdhcnt;
	sph.spdhmcnt = si.spdhmcnt;

	do {
		wseq = wead_seqbegin(&net->xfwm.powicy_hthwesh.wock);

		spt4.wbits = net->xfwm.powicy_hthwesh.wbits4;
		spt4.wbits = net->xfwm.powicy_hthwesh.wbits4;
		spt6.wbits = net->xfwm.powicy_hthwesh.wbits6;
		spt6.wbits = net->xfwm.powicy_hthwesh.wbits6;
	} whiwe (wead_seqwetwy(&net->xfwm.powicy_hthwesh.wock, wseq));

	eww = nwa_put(skb, XFWMA_SPD_INFO, sizeof(spc), &spc);
	if (!eww)
		eww = nwa_put(skb, XFWMA_SPD_HINFO, sizeof(sph), &sph);
	if (!eww)
		eww = nwa_put(skb, XFWMA_SPD_IPV4_HTHWESH, sizeof(spt4), &spt4);
	if (!eww)
		eww = nwa_put(skb, XFWMA_SPD_IPV6_HTHWESH, sizeof(spt6), &spt6);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_set_spdinfo(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwmu_spdhthwesh *thwesh4 = NUWW;
	stwuct xfwmu_spdhthwesh *thwesh6 = NUWW;

	/* sewectow pwefixwen thweshowds to hash powicies */
	if (attws[XFWMA_SPD_IPV4_HTHWESH]) {
		stwuct nwattw *wta = attws[XFWMA_SPD_IPV4_HTHWESH];

		if (nwa_wen(wta) < sizeof(*thwesh4)) {
			NW_SET_EWW_MSG(extack, "Invawid SPD_IPV4_HTHWESH attwibute wength");
			wetuwn -EINVAW;
		}
		thwesh4 = nwa_data(wta);
		if (thwesh4->wbits > 32 || thwesh4->wbits > 32) {
			NW_SET_EWW_MSG(extack, "Invawid hash thweshowd (must be <= 32 fow IPv4)");
			wetuwn -EINVAW;
		}
	}
	if (attws[XFWMA_SPD_IPV6_HTHWESH]) {
		stwuct nwattw *wta = attws[XFWMA_SPD_IPV6_HTHWESH];

		if (nwa_wen(wta) < sizeof(*thwesh6)) {
			NW_SET_EWW_MSG(extack, "Invawid SPD_IPV6_HTHWESH attwibute wength");
			wetuwn -EINVAW;
		}
		thwesh6 = nwa_data(wta);
		if (thwesh6->wbits > 128 || thwesh6->wbits > 128) {
			NW_SET_EWW_MSG(extack, "Invawid hash thweshowd (must be <= 128 fow IPv6)");
			wetuwn -EINVAW;
		}
	}

	if (thwesh4 || thwesh6) {
		wwite_seqwock(&net->xfwm.powicy_hthwesh.wock);
		if (thwesh4) {
			net->xfwm.powicy_hthwesh.wbits4 = thwesh4->wbits;
			net->xfwm.powicy_hthwesh.wbits4 = thwesh4->wbits;
		}
		if (thwesh6) {
			net->xfwm.powicy_hthwesh.wbits6 = thwesh6->wbits;
			net->xfwm.powicy_hthwesh.wbits6 = thwesh6->wbits;
		}
		wwite_sequnwock(&net->xfwm.powicy_hthwesh.wock);

		xfwm_powicy_hash_webuiwd(net);
	}

	wetuwn 0;
}

static int xfwm_get_spdinfo(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct sk_buff *w_skb;
	u32 *fwags = nwmsg_data(nwh);
	u32 spowtid = NETWINK_CB(skb).powtid;
	u32 seq = nwh->nwmsg_seq;
	int eww;

	w_skb = nwmsg_new(xfwm_spdinfo_msgsize(), GFP_ATOMIC);
	if (w_skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_spdinfo(w_skb, net, spowtid, seq, *fwags);
	BUG_ON(eww < 0);

	wetuwn nwmsg_unicast(net->xfwm.nwsk, w_skb, spowtid);
}

static inwine unsigned int xfwm_sadinfo_msgsize(void)
{
	wetuwn NWMSG_AWIGN(4)
	       + nwa_totaw_size(sizeof(stwuct xfwmu_sadhinfo))
	       + nwa_totaw_size(4); /* XFWMA_SAD_CNT */
}

static int buiwd_sadinfo(stwuct sk_buff *skb, stwuct net *net,
			 u32 powtid, u32 seq, u32 fwags)
{
	stwuct xfwmk_sadinfo si;
	stwuct xfwmu_sadhinfo sh;
	stwuct nwmsghdw *nwh;
	int eww;
	u32 *f;

	nwh = nwmsg_put(skb, powtid, seq, XFWM_MSG_NEWSADINFO, sizeof(u32), 0);
	if (nwh == NUWW) /* shouwdn't weawwy happen ... */
		wetuwn -EMSGSIZE;

	f = nwmsg_data(nwh);
	*f = fwags;
	xfwm_sad_getinfo(net, &si);

	sh.sadhmcnt = si.sadhmcnt;
	sh.sadhcnt = si.sadhcnt;

	eww = nwa_put_u32(skb, XFWMA_SAD_CNT, si.sadcnt);
	if (!eww)
		eww = nwa_put(skb, XFWMA_SAD_HINFO, sizeof(sh), &sh);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_get_sadinfo(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct sk_buff *w_skb;
	u32 *fwags = nwmsg_data(nwh);
	u32 spowtid = NETWINK_CB(skb).powtid;
	u32 seq = nwh->nwmsg_seq;
	int eww;

	w_skb = nwmsg_new(xfwm_sadinfo_msgsize(), GFP_ATOMIC);
	if (w_skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_sadinfo(w_skb, net, spowtid, seq, *fwags);
	BUG_ON(eww < 0);

	wetuwn nwmsg_unicast(net->xfwm.nwsk, w_skb, spowtid);
}

static int xfwm_get_sa(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_usewsa_id *p = nwmsg_data(nwh);
	stwuct xfwm_state *x;
	stwuct sk_buff *wesp_skb;
	int eww = -ESWCH;

	x = xfwm_usew_state_wookup(net, p, attws, &eww);
	if (x == NUWW)
		goto out_noput;

	wesp_skb = xfwm_state_netwink(skb, x, nwh->nwmsg_seq);
	if (IS_EWW(wesp_skb)) {
		eww = PTW_EWW(wesp_skb);
	} ewse {
		eww = nwmsg_unicast(net->xfwm.nwsk, wesp_skb, NETWINK_CB(skb).powtid);
	}
	xfwm_state_put(x);
out_noput:
	wetuwn eww;
}

static int xfwm_awwoc_usewspi(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct nwattw **attws,
			      stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state *x;
	stwuct xfwm_usewspi_info *p;
	stwuct xfwm_twanswatow *xtw;
	stwuct sk_buff *wesp_skb;
	xfwm_addwess_t *daddw;
	int famiwy;
	int eww;
	u32 mawk;
	stwuct xfwm_mawk m;
	u32 if_id = 0;

	p = nwmsg_data(nwh);
	eww = vewify_spi_info(p->info.id.pwoto, p->min, p->max, extack);
	if (eww)
		goto out_noput;

	famiwy = p->info.famiwy;
	daddw = &p->info.id.daddw;

	x = NUWW;

	mawk = xfwm_mawk_get(attws, &m);

	if (attws[XFWMA_IF_ID])
		if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	if (p->info.seq) {
		x = xfwm_find_acq_byseq(net, mawk, p->info.seq);
		if (x && !xfwm_addw_equaw(&x->id.daddw, daddw, famiwy)) {
			xfwm_state_put(x);
			x = NUWW;
		}
	}

	if (!x)
		x = xfwm_find_acq(net, &m, p->info.mode, p->info.weqid,
				  if_id, p->info.id.pwoto, daddw,
				  &p->info.saddw, 1,
				  famiwy);
	eww = -ENOENT;
	if (!x) {
		NW_SET_EWW_MSG(extack, "Tawget ACQUIWE not found");
		goto out_noput;
	}

	eww = xfwm_awwoc_spi(x, p->min, p->max, extack);
	if (eww)
		goto out;

	wesp_skb = xfwm_state_netwink(skb, x, nwh->nwmsg_seq);
	if (IS_EWW(wesp_skb)) {
		eww = PTW_EWW(wesp_skb);
		goto out;
	}

	xtw = xfwm_get_twanswatow();
	if (xtw) {
		eww = xtw->awwoc_compat(skb, nwmsg_hdw(skb));

		xfwm_put_twanswatow(xtw);
		if (eww) {
			kfwee_skb(wesp_skb);
			goto out;
		}
	}

	eww = nwmsg_unicast(net->xfwm.nwsk, wesp_skb, NETWINK_CB(skb).powtid);

out:
	xfwm_state_put(x);
out_noput:
	wetuwn eww;
}

static int vewify_powicy_diw(u8 diw, stwuct netwink_ext_ack *extack)
{
	switch (diw) {
	case XFWM_POWICY_IN:
	case XFWM_POWICY_OUT:
	case XFWM_POWICY_FWD:
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid powicy diwection");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vewify_powicy_type(u8 type, stwuct netwink_ext_ack *extack)
{
	switch (type) {
	case XFWM_POWICY_TYPE_MAIN:
#ifdef CONFIG_XFWM_SUB_POWICY
	case XFWM_POWICY_TYPE_SUB:
#endif
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid powicy type");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vewify_newpowicy_info(stwuct xfwm_usewpowicy_info *p,
				 stwuct netwink_ext_ack *extack)
{
	int wet;

	switch (p->shawe) {
	case XFWM_SHAWE_ANY:
	case XFWM_SHAWE_SESSION:
	case XFWM_SHAWE_USEW:
	case XFWM_SHAWE_UNIQUE:
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid powicy shawe");
		wetuwn -EINVAW;
	}

	switch (p->action) {
	case XFWM_POWICY_AWWOW:
	case XFWM_POWICY_BWOCK:
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid powicy action");
		wetuwn -EINVAW;
	}

	switch (p->sew.famiwy) {
	case AF_INET:
		if (p->sew.pwefixwen_d > 32 || p->sew.pwefixwen_s > 32) {
			NW_SET_EWW_MSG(extack, "Invawid pwefix wength in sewectow (must be <= 32 fow IPv4)");
			wetuwn -EINVAW;
		}

		bweak;

	case AF_INET6:
#if IS_ENABWED(CONFIG_IPV6)
		if (p->sew.pwefixwen_d > 128 || p->sew.pwefixwen_s > 128) {
			NW_SET_EWW_MSG(extack, "Invawid pwefix wength in sewectow (must be <= 128 fow IPv6)");
			wetuwn -EINVAW;
		}

		bweak;
#ewse
		NW_SET_EWW_MSG(extack, "IPv6 suppowt disabwed");
		wetuwn  -EAFNOSUPPOWT;
#endif

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid sewectow famiwy");
		wetuwn -EINVAW;
	}

	wet = vewify_powicy_diw(p->diw, extack);
	if (wet)
		wetuwn wet;
	if (p->index && (xfwm_powicy_id2diw(p->index) != p->diw)) {
		NW_SET_EWW_MSG(extack, "Powicy index doesn't match diwection");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int copy_fwom_usew_sec_ctx(stwuct xfwm_powicy *pow, stwuct nwattw **attws)
{
	stwuct nwattw *wt = attws[XFWMA_SEC_CTX];
	stwuct xfwm_usew_sec_ctx *uctx;

	if (!wt)
		wetuwn 0;

	uctx = nwa_data(wt);
	wetuwn secuwity_xfwm_powicy_awwoc(&pow->secuwity, uctx, GFP_KEWNEW);
}

static void copy_tempwates(stwuct xfwm_powicy *xp, stwuct xfwm_usew_tmpw *ut,
			   int nw)
{
	int i;

	xp->xfwm_nw = nw;
	fow (i = 0; i < nw; i++, ut++) {
		stwuct xfwm_tmpw *t = &xp->xfwm_vec[i];

		memcpy(&t->id, &ut->id, sizeof(stwuct xfwm_id));
		memcpy(&t->saddw, &ut->saddw,
		       sizeof(xfwm_addwess_t));
		t->weqid = ut->weqid;
		t->mode = ut->mode;
		t->shawe = ut->shawe;
		t->optionaw = ut->optionaw;
		t->aawgos = ut->aawgos;
		t->eawgos = ut->eawgos;
		t->cawgos = ut->cawgos;
		/* If aww masks awe ~0, then we awwow aww awgowithms. */
		t->awwawgs = !~(t->aawgos & t->eawgos & t->cawgos);
		t->encap_famiwy = ut->famiwy;
	}
}

static int vawidate_tmpw(int nw, stwuct xfwm_usew_tmpw *ut, u16 famiwy,
			 int diw, stwuct netwink_ext_ack *extack)
{
	u16 pwev_famiwy;
	int i;

	if (nw > XFWM_MAX_DEPTH) {
		NW_SET_EWW_MSG(extack, "Tempwate count must be <= XFWM_MAX_DEPTH (" __stwingify(XFWM_MAX_DEPTH) ")");
		wetuwn -EINVAW;
	}

	pwev_famiwy = famiwy;

	fow (i = 0; i < nw; i++) {
		/* We nevew vawidated the ut->famiwy vawue, so many
		 * appwications simpwy weave it at zewo.  The check was
		 * nevew made and ut->famiwy was ignowed because aww
		 * tempwates couwd be assumed to have the same famiwy as
		 * the powicy itsewf.  Now that we wiww have ipv4-in-ipv6
		 * and ipv6-in-ipv4 tunnews, this is no wongew twue.
		 */
		if (!ut[i].famiwy)
			ut[i].famiwy = famiwy;

		switch (ut[i].mode) {
		case XFWM_MODE_TUNNEW:
		case XFWM_MODE_BEET:
			if (ut[i].optionaw && diw == XFWM_POWICY_OUT) {
				NW_SET_EWW_MSG(extack, "Mode in optionaw tempwate not awwowed in outbound powicy");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			if (ut[i].famiwy != pwev_famiwy) {
				NW_SET_EWW_MSG(extack, "Mode in tempwate doesn't suppowt a famiwy change");
				wetuwn -EINVAW;
			}
			bweak;
		}
		if (ut[i].mode >= XFWM_MODE_MAX) {
			NW_SET_EWW_MSG(extack, "Mode in tempwate must be < XFWM_MODE_MAX (" __stwingify(XFWM_MODE_MAX) ")");
			wetuwn -EINVAW;
		}

		pwev_famiwy = ut[i].famiwy;

		switch (ut[i].famiwy) {
		case AF_INET:
			bweak;
#if IS_ENABWED(CONFIG_IPV6)
		case AF_INET6:
			bweak;
#endif
		defauwt:
			NW_SET_EWW_MSG(extack, "Invawid famiwy in tempwate");
			wetuwn -EINVAW;
		}

		if (!xfwm_id_pwoto_vawid(ut[i].id.pwoto)) {
			NW_SET_EWW_MSG(extack, "Invawid XFWM pwotocow in tempwate");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int copy_fwom_usew_tmpw(stwuct xfwm_powicy *pow, stwuct nwattw **attws,
			       int diw, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_TMPW];

	if (!wt) {
		pow->xfwm_nw = 0;
	} ewse {
		stwuct xfwm_usew_tmpw *utmpw = nwa_data(wt);
		int nw = nwa_wen(wt) / sizeof(*utmpw);
		int eww;

		eww = vawidate_tmpw(nw, utmpw, pow->famiwy, diw, extack);
		if (eww)
			wetuwn eww;

		copy_tempwates(pow, utmpw, nw);
	}
	wetuwn 0;
}

static int copy_fwom_usew_powicy_type(u8 *tp, stwuct nwattw **attws,
				      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_POWICY_TYPE];
	stwuct xfwm_usewpowicy_type *upt;
	u8 type = XFWM_POWICY_TYPE_MAIN;
	int eww;

	if (wt) {
		upt = nwa_data(wt);
		type = upt->type;
	}

	eww = vewify_powicy_type(type, extack);
	if (eww)
		wetuwn eww;

	*tp = type;
	wetuwn 0;
}

static void copy_fwom_usew_powicy(stwuct xfwm_powicy *xp, stwuct xfwm_usewpowicy_info *p)
{
	xp->pwiowity = p->pwiowity;
	xp->index = p->index;
	memcpy(&xp->sewectow, &p->sew, sizeof(xp->sewectow));
	memcpy(&xp->wft, &p->wft, sizeof(xp->wft));
	xp->action = p->action;
	xp->fwags = p->fwags;
	xp->famiwy = p->sew.famiwy;
	/* XXX xp->shawe = p->shawe; */
}

static void copy_to_usew_powicy(stwuct xfwm_powicy *xp, stwuct xfwm_usewpowicy_info *p, int diw)
{
	memset(p, 0, sizeof(*p));
	memcpy(&p->sew, &xp->sewectow, sizeof(p->sew));
	memcpy(&p->wft, &xp->wft, sizeof(p->wft));
	memcpy(&p->cuwwft, &xp->cuwwft, sizeof(p->cuwwft));
	p->pwiowity = xp->pwiowity;
	p->index = xp->index;
	p->sew.famiwy = xp->famiwy;
	p->diw = diw;
	p->action = xp->action;
	p->fwags = xp->fwags;
	p->shawe = XFWM_SHAWE_ANY; /* XXX xp->shawe */
}

static stwuct xfwm_powicy *xfwm_powicy_constwuct(stwuct net *net,
						 stwuct xfwm_usewpowicy_info *p,
						 stwuct nwattw **attws,
						 int *ewwp,
						 stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_powicy *xp = xfwm_powicy_awwoc(net, GFP_KEWNEW);
	int eww;

	if (!xp) {
		*ewwp = -ENOMEM;
		wetuwn NUWW;
	}

	copy_fwom_usew_powicy(xp, p);

	eww = copy_fwom_usew_powicy_type(&xp->type, attws, extack);
	if (eww)
		goto ewwow;

	if (!(eww = copy_fwom_usew_tmpw(xp, attws, p->diw, extack)))
		eww = copy_fwom_usew_sec_ctx(xp, attws);
	if (eww)
		goto ewwow;

	xfwm_mawk_get(attws, &xp->mawk);

	if (attws[XFWMA_IF_ID])
		xp->if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	/* configuwe the hawdwawe if offwoad is wequested */
	if (attws[XFWMA_OFFWOAD_DEV]) {
		eww = xfwm_dev_powicy_add(net, xp,
					  nwa_data(attws[XFWMA_OFFWOAD_DEV]),
					  p->diw, extack);
		if (eww)
			goto ewwow;
	}

	wetuwn xp;
 ewwow:
	*ewwp = eww;
	xp->wawk.dead = 1;
	xfwm_powicy_destwoy(xp);
	wetuwn NUWW;
}

static int xfwm_add_powicy(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct nwattw **attws,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_usewpowicy_info *p = nwmsg_data(nwh);
	stwuct xfwm_powicy *xp;
	stwuct km_event c;
	int eww;
	int excw;

	eww = vewify_newpowicy_info(p, extack);
	if (eww)
		wetuwn eww;
	eww = vewify_sec_ctx_wen(attws, extack);
	if (eww)
		wetuwn eww;

	xp = xfwm_powicy_constwuct(net, p, attws, &eww, extack);
	if (!xp)
		wetuwn eww;

	/* shouwdn't excw be based on nwh fwags??
	 * Aha! this is anti-netwink weawwy i.e  mowe pfkey dewived
	 * in netwink excw is a fwag and you wouwdn't need
	 * a type XFWM_MSG_UPDPOWICY - JHS */
	excw = nwh->nwmsg_type == XFWM_MSG_NEWPOWICY;
	eww = xfwm_powicy_insewt(p->diw, xp, excw);
	xfwm_audit_powicy_add(xp, eww ? 0 : 1, twue);

	if (eww) {
		xfwm_dev_powicy_dewete(xp);
		xfwm_dev_powicy_fwee(xp);
		secuwity_xfwm_powicy_fwee(xp->secuwity);
		kfwee(xp);
		wetuwn eww;
	}

	c.event = nwh->nwmsg_type;
	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	km_powicy_notify(xp, p->diw, &c);

	xfwm_pow_put(xp);

	wetuwn 0;
}

static int copy_to_usew_tmpw(stwuct xfwm_powicy *xp, stwuct sk_buff *skb)
{
	stwuct xfwm_usew_tmpw vec[XFWM_MAX_DEPTH];
	int i;

	if (xp->xfwm_nw == 0)
		wetuwn 0;

	fow (i = 0; i < xp->xfwm_nw; i++) {
		stwuct xfwm_usew_tmpw *up = &vec[i];
		stwuct xfwm_tmpw *kp = &xp->xfwm_vec[i];

		memset(up, 0, sizeof(*up));
		memcpy(&up->id, &kp->id, sizeof(up->id));
		up->famiwy = kp->encap_famiwy;
		memcpy(&up->saddw, &kp->saddw, sizeof(up->saddw));
		up->weqid = kp->weqid;
		up->mode = kp->mode;
		up->shawe = kp->shawe;
		up->optionaw = kp->optionaw;
		up->aawgos = kp->aawgos;
		up->eawgos = kp->eawgos;
		up->cawgos = kp->cawgos;
	}

	wetuwn nwa_put(skb, XFWMA_TMPW,
		       sizeof(stwuct xfwm_usew_tmpw) * xp->xfwm_nw, vec);
}

static inwine int copy_to_usew_state_sec_ctx(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	if (x->secuwity) {
		wetuwn copy_sec_ctx(x->secuwity, skb);
	}
	wetuwn 0;
}

static inwine int copy_to_usew_sec_ctx(stwuct xfwm_powicy *xp, stwuct sk_buff *skb)
{
	if (xp->secuwity)
		wetuwn copy_sec_ctx(xp->secuwity, skb);
	wetuwn 0;
}
static inwine unsigned int usewpowicy_type_attwsize(void)
{
#ifdef CONFIG_XFWM_SUB_POWICY
	wetuwn nwa_totaw_size(sizeof(stwuct xfwm_usewpowicy_type));
#ewse
	wetuwn 0;
#endif
}

#ifdef CONFIG_XFWM_SUB_POWICY
static int copy_to_usew_powicy_type(u8 type, stwuct sk_buff *skb)
{
	stwuct xfwm_usewpowicy_type upt;

	/* Sadwy thewe awe two howes in stwuct xfwm_usewpowicy_type */
	memset(&upt, 0, sizeof(upt));
	upt.type = type;

	wetuwn nwa_put(skb, XFWMA_POWICY_TYPE, sizeof(upt), &upt);
}

#ewse
static inwine int copy_to_usew_powicy_type(u8 type, stwuct sk_buff *skb)
{
	wetuwn 0;
}
#endif

static int dump_one_powicy(stwuct xfwm_powicy *xp, int diw, int count, void *ptw)
{
	stwuct xfwm_dump_info *sp = ptw;
	stwuct xfwm_usewpowicy_info *p;
	stwuct sk_buff *in_skb = sp->in_skb;
	stwuct sk_buff *skb = sp->out_skb;
	stwuct xfwm_twanswatow *xtw;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, NETWINK_CB(in_skb).powtid, sp->nwmsg_seq,
			XFWM_MSG_NEWPOWICY, sizeof(*p), sp->nwmsg_fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	p = nwmsg_data(nwh);
	copy_to_usew_powicy(xp, p, diw);
	eww = copy_to_usew_tmpw(xp, skb);
	if (!eww)
		eww = copy_to_usew_sec_ctx(xp, skb);
	if (!eww)
		eww = copy_to_usew_powicy_type(xp->type, skb);
	if (!eww)
		eww = xfwm_mawk_put(skb, &xp->mawk);
	if (!eww)
		eww = xfwm_if_id_put(skb, xp->if_id);
	if (!eww && xp->xdo.dev)
		eww = copy_usew_offwoad(&xp->xdo, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}
	nwmsg_end(skb, nwh);

	xtw = xfwm_get_twanswatow();
	if (xtw) {
		eww = xtw->awwoc_compat(skb, nwh);

		xfwm_put_twanswatow(xtw);
		if (eww) {
			nwmsg_cancew(skb, nwh);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int xfwm_dump_powicy_done(stwuct netwink_cawwback *cb)
{
	stwuct xfwm_powicy_wawk *wawk = (stwuct xfwm_powicy_wawk *)cb->awgs;
	stwuct net *net = sock_net(cb->skb->sk);

	xfwm_powicy_wawk_done(wawk, net);
	wetuwn 0;
}

static int xfwm_dump_powicy_stawt(stwuct netwink_cawwback *cb)
{
	stwuct xfwm_powicy_wawk *wawk = (stwuct xfwm_powicy_wawk *)cb->awgs;

	BUIWD_BUG_ON(sizeof(*wawk) > sizeof(cb->awgs));

	xfwm_powicy_wawk_init(wawk, XFWM_POWICY_TYPE_ANY);
	wetuwn 0;
}

static int xfwm_dump_powicy(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_powicy_wawk *wawk = (stwuct xfwm_powicy_wawk *)cb->awgs;
	stwuct xfwm_dump_info info;

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nwmsg_seq = cb->nwh->nwmsg_seq;
	info.nwmsg_fwags = NWM_F_MUWTI;

	(void) xfwm_powicy_wawk(net, wawk, dump_one_powicy, &info);

	wetuwn skb->wen;
}

static stwuct sk_buff *xfwm_powicy_netwink(stwuct sk_buff *in_skb,
					  stwuct xfwm_powicy *xp,
					  int diw, u32 seq)
{
	stwuct xfwm_dump_info info;
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nwmsg_seq = seq;
	info.nwmsg_fwags = 0;

	eww = dump_one_powicy(xp, diw, 0, &info);
	if (eww) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}

	wetuwn skb;
}

static int xfwm_notify_usewpowicy(stwuct net *net)
{
	stwuct xfwm_usewpowicy_defauwt *up;
	int wen = NWMSG_AWIGN(sizeof(*up));
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(wen, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, 0, 0, XFWM_MSG_GETDEFAUWT, sizeof(*up), 0);
	if (nwh == NUWW) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	up = nwmsg_data(nwh);
	up->in = net->xfwm.powicy_defauwt[XFWM_POWICY_IN];
	up->fwd = net->xfwm.powicy_defauwt[XFWM_POWICY_FWD];
	up->out = net->xfwm.powicy_defauwt[XFWM_POWICY_OUT];

	nwmsg_end(skb, nwh);

	wcu_wead_wock();
	eww = xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_POWICY);
	wcu_wead_unwock();

	wetuwn eww;
}

static boow xfwm_usewpowicy_is_vawid(__u8 powicy)
{
	wetuwn powicy == XFWM_USEWPOWICY_BWOCK ||
	       powicy == XFWM_USEWPOWICY_ACCEPT;
}

static int xfwm_set_defauwt(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_usewpowicy_defauwt *up = nwmsg_data(nwh);

	if (xfwm_usewpowicy_is_vawid(up->in))
		net->xfwm.powicy_defauwt[XFWM_POWICY_IN] = up->in;

	if (xfwm_usewpowicy_is_vawid(up->fwd))
		net->xfwm.powicy_defauwt[XFWM_POWICY_FWD] = up->fwd;

	if (xfwm_usewpowicy_is_vawid(up->out))
		net->xfwm.powicy_defauwt[XFWM_POWICY_OUT] = up->out;

	wt_genid_bump_aww(net);

	xfwm_notify_usewpowicy(net);
	wetuwn 0;
}

static int xfwm_get_defauwt(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *w_skb;
	stwuct nwmsghdw *w_nwh;
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_usewpowicy_defauwt *w_up;
	int wen = NWMSG_AWIGN(sizeof(stwuct xfwm_usewpowicy_defauwt));
	u32 powtid = NETWINK_CB(skb).powtid;
	u32 seq = nwh->nwmsg_seq;

	w_skb = nwmsg_new(wen, GFP_ATOMIC);
	if (!w_skb)
		wetuwn -ENOMEM;

	w_nwh = nwmsg_put(w_skb, powtid, seq, XFWM_MSG_GETDEFAUWT, sizeof(*w_up), 0);
	if (!w_nwh) {
		kfwee_skb(w_skb);
		wetuwn -EMSGSIZE;
	}

	w_up = nwmsg_data(w_nwh);
	w_up->in = net->xfwm.powicy_defauwt[XFWM_POWICY_IN];
	w_up->fwd = net->xfwm.powicy_defauwt[XFWM_POWICY_FWD];
	w_up->out = net->xfwm.powicy_defauwt[XFWM_POWICY_OUT];
	nwmsg_end(w_skb, w_nwh);

	wetuwn nwmsg_unicast(net->xfwm.nwsk, w_skb, powtid);
}

static int xfwm_get_powicy(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct nwattw **attws,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_powicy *xp;
	stwuct xfwm_usewpowicy_id *p;
	u8 type = XFWM_POWICY_TYPE_MAIN;
	int eww;
	stwuct km_event c;
	int dewete;
	stwuct xfwm_mawk m;
	u32 if_id = 0;

	p = nwmsg_data(nwh);
	dewete = nwh->nwmsg_type == XFWM_MSG_DEWPOWICY;

	eww = copy_fwom_usew_powicy_type(&type, attws, extack);
	if (eww)
		wetuwn eww;

	eww = vewify_powicy_diw(p->diw, extack);
	if (eww)
		wetuwn eww;

	if (attws[XFWMA_IF_ID])
		if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	xfwm_mawk_get(attws, &m);

	if (p->index)
		xp = xfwm_powicy_byid(net, &m, if_id, type, p->diw,
				      p->index, dewete, &eww);
	ewse {
		stwuct nwattw *wt = attws[XFWMA_SEC_CTX];
		stwuct xfwm_sec_ctx *ctx;

		eww = vewify_sec_ctx_wen(attws, extack);
		if (eww)
			wetuwn eww;

		ctx = NUWW;
		if (wt) {
			stwuct xfwm_usew_sec_ctx *uctx = nwa_data(wt);

			eww = secuwity_xfwm_powicy_awwoc(&ctx, uctx, GFP_KEWNEW);
			if (eww)
				wetuwn eww;
		}
		xp = xfwm_powicy_bysew_ctx(net, &m, if_id, type, p->diw,
					   &p->sew, ctx, dewete, &eww);
		secuwity_xfwm_powicy_fwee(ctx);
	}
	if (xp == NUWW)
		wetuwn -ENOENT;

	if (!dewete) {
		stwuct sk_buff *wesp_skb;

		wesp_skb = xfwm_powicy_netwink(skb, xp, p->diw, nwh->nwmsg_seq);
		if (IS_EWW(wesp_skb)) {
			eww = PTW_EWW(wesp_skb);
		} ewse {
			eww = nwmsg_unicast(net->xfwm.nwsk, wesp_skb,
					    NETWINK_CB(skb).powtid);
		}
	} ewse {
		xfwm_dev_powicy_dewete(xp);
		xfwm_audit_powicy_dewete(xp, eww ? 0 : 1, twue);

		if (eww != 0)
			goto out;

		c.data.byid = p->index;
		c.event = nwh->nwmsg_type;
		c.seq = nwh->nwmsg_seq;
		c.powtid = nwh->nwmsg_pid;
		km_powicy_notify(xp, p->diw, &c);
	}

out:
	xfwm_pow_put(xp);
	wetuwn eww;
}

static int xfwm_fwush_sa(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			 stwuct nwattw **attws,
			 stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct km_event c;
	stwuct xfwm_usewsa_fwush *p = nwmsg_data(nwh);
	int eww;

	eww = xfwm_state_fwush(net, p->pwoto, twue, fawse);
	if (eww) {
		if (eww == -ESWCH) /* empty tabwe */
			wetuwn 0;
		wetuwn eww;
	}
	c.data.pwoto = p->pwoto;
	c.event = nwh->nwmsg_type;
	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	c.net = net;
	km_state_notify(NUWW, &c);

	wetuwn 0;
}

static inwine unsigned int xfwm_aevent_msgsize(stwuct xfwm_state *x)
{
	unsigned int wepway_size = x->wepway_esn ?
			      xfwm_wepway_state_esn_wen(x->wepway_esn) :
			      sizeof(stwuct xfwm_wepway_state);

	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_aevent_id))
	       + nwa_totaw_size(wepway_size)
	       + nwa_totaw_size_64bit(sizeof(stwuct xfwm_wifetime_cuw))
	       + nwa_totaw_size(sizeof(stwuct xfwm_mawk))
	       + nwa_totaw_size(4) /* XFWM_AE_WTHW */
	       + nwa_totaw_size(4); /* XFWM_AE_ETHW */
}

static int buiwd_aevent(stwuct sk_buff *skb, stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct xfwm_aevent_id *id;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, c->powtid, c->seq, XFWM_MSG_NEWAE, sizeof(*id), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	id = nwmsg_data(nwh);
	memset(&id->sa_id, 0, sizeof(id->sa_id));
	memcpy(&id->sa_id.daddw, &x->id.daddw, sizeof(x->id.daddw));
	id->sa_id.spi = x->id.spi;
	id->sa_id.famiwy = x->pwops.famiwy;
	id->sa_id.pwoto = x->id.pwoto;
	memcpy(&id->saddw, &x->pwops.saddw, sizeof(x->pwops.saddw));
	id->weqid = x->pwops.weqid;
	id->fwags = c->data.aevent;

	if (x->wepway_esn) {
		eww = nwa_put(skb, XFWMA_WEPWAY_ESN_VAW,
			      xfwm_wepway_state_esn_wen(x->wepway_esn),
			      x->wepway_esn);
	} ewse {
		eww = nwa_put(skb, XFWMA_WEPWAY_VAW, sizeof(x->wepway),
			      &x->wepway);
	}
	if (eww)
		goto out_cancew;
	eww = nwa_put_64bit(skb, XFWMA_WTIME_VAW, sizeof(x->cuwwft), &x->cuwwft,
			    XFWMA_PAD);
	if (eww)
		goto out_cancew;

	if (id->fwags & XFWM_AE_WTHW) {
		eww = nwa_put_u32(skb, XFWMA_WEPWAY_THWESH, x->wepway_maxdiff);
		if (eww)
			goto out_cancew;
	}
	if (id->fwags & XFWM_AE_ETHW) {
		eww = nwa_put_u32(skb, XFWMA_ETIMEW_THWESH,
				  x->wepway_maxage * 10 / HZ);
		if (eww)
			goto out_cancew;
	}
	eww = xfwm_mawk_put(skb, &x->mawk);
	if (eww)
		goto out_cancew;

	eww = xfwm_if_id_put(skb, x->if_id);
	if (eww)
		goto out_cancew;

	nwmsg_end(skb, nwh);
	wetuwn 0;

out_cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn eww;
}

static int xfwm_get_ae(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state *x;
	stwuct sk_buff *w_skb;
	int eww;
	stwuct km_event c;
	u32 mawk;
	stwuct xfwm_mawk m;
	stwuct xfwm_aevent_id *p = nwmsg_data(nwh);
	stwuct xfwm_usewsa_id *id = &p->sa_id;

	mawk = xfwm_mawk_get(attws, &m);

	x = xfwm_state_wookup(net, mawk, &id->daddw, id->spi, id->pwoto, id->famiwy);
	if (x == NUWW)
		wetuwn -ESWCH;

	w_skb = nwmsg_new(xfwm_aevent_msgsize(x), GFP_ATOMIC);
	if (w_skb == NUWW) {
		xfwm_state_put(x);
		wetuwn -ENOMEM;
	}

	/*
	 * XXX: is this wock weawwy needed - none of the othew
	 * gets wock (the concewn is things getting updated
	 * whiwe we awe stiww weading) - jhs
	*/
	spin_wock_bh(&x->wock);
	c.data.aevent = p->fwags;
	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;

	eww = buiwd_aevent(w_skb, x, &c);
	BUG_ON(eww < 0);

	eww = nwmsg_unicast(net->xfwm.nwsk, w_skb, NETWINK_CB(skb).powtid);
	spin_unwock_bh(&x->wock);
	xfwm_state_put(x);
	wetuwn eww;
}

static int xfwm_new_ae(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state *x;
	stwuct km_event c;
	int eww = -EINVAW;
	u32 mawk = 0;
	stwuct xfwm_mawk m;
	stwuct xfwm_aevent_id *p = nwmsg_data(nwh);
	stwuct nwattw *wp = attws[XFWMA_WEPWAY_VAW];
	stwuct nwattw *we = attws[XFWMA_WEPWAY_ESN_VAW];
	stwuct nwattw *wt = attws[XFWMA_WTIME_VAW];
	stwuct nwattw *et = attws[XFWMA_ETIMEW_THWESH];
	stwuct nwattw *wt = attws[XFWMA_WEPWAY_THWESH];

	if (!wt && !wp && !we && !et && !wt) {
		NW_SET_EWW_MSG(extack, "Missing wequiwed attwibute fow AE");
		wetuwn eww;
	}

	/* pedantic mode - thou shawt sayeth wepwaceth */
	if (!(nwh->nwmsg_fwags & NWM_F_WEPWACE)) {
		NW_SET_EWW_MSG(extack, "NWM_F_WEPWACE fwag is wequiwed");
		wetuwn eww;
	}

	mawk = xfwm_mawk_get(attws, &m);

	x = xfwm_state_wookup(net, mawk, &p->sa_id.daddw, p->sa_id.spi, p->sa_id.pwoto, p->sa_id.famiwy);
	if (x == NUWW)
		wetuwn -ESWCH;

	if (x->km.state != XFWM_STATE_VAWID) {
		NW_SET_EWW_MSG(extack, "SA must be in VAWID state");
		goto out;
	}

	eww = xfwm_wepway_vewify_wen(x->wepway_esn, we, extack);
	if (eww)
		goto out;

	spin_wock_bh(&x->wock);
	xfwm_update_ae_pawams(x, attws, 1);
	spin_unwock_bh(&x->wock);

	c.event = nwh->nwmsg_type;
	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	c.data.aevent = XFWM_AE_CU;
	km_state_notify(x, &c);
	eww = 0;
out:
	xfwm_state_put(x);
	wetuwn eww;
}

static int xfwm_fwush_powicy(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct nwattw **attws,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct km_event c;
	u8 type = XFWM_POWICY_TYPE_MAIN;
	int eww;

	eww = copy_fwom_usew_powicy_type(&type, attws, extack);
	if (eww)
		wetuwn eww;

	eww = xfwm_powicy_fwush(net, type, twue);
	if (eww) {
		if (eww == -ESWCH) /* empty tabwe */
			wetuwn 0;
		wetuwn eww;
	}

	c.data.type = type;
	c.event = nwh->nwmsg_type;
	c.seq = nwh->nwmsg_seq;
	c.powtid = nwh->nwmsg_pid;
	c.net = net;
	km_powicy_notify(NUWW, 0, &c);
	wetuwn 0;
}

static int xfwm_add_pow_expiwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct nwattw **attws,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_powicy *xp;
	stwuct xfwm_usew_powexpiwe *up = nwmsg_data(nwh);
	stwuct xfwm_usewpowicy_info *p = &up->pow;
	u8 type = XFWM_POWICY_TYPE_MAIN;
	int eww = -ENOENT;
	stwuct xfwm_mawk m;
	u32 if_id = 0;

	eww = copy_fwom_usew_powicy_type(&type, attws, extack);
	if (eww)
		wetuwn eww;

	eww = vewify_powicy_diw(p->diw, extack);
	if (eww)
		wetuwn eww;

	if (attws[XFWMA_IF_ID])
		if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	xfwm_mawk_get(attws, &m);

	if (p->index)
		xp = xfwm_powicy_byid(net, &m, if_id, type, p->diw, p->index,
				      0, &eww);
	ewse {
		stwuct nwattw *wt = attws[XFWMA_SEC_CTX];
		stwuct xfwm_sec_ctx *ctx;

		eww = vewify_sec_ctx_wen(attws, extack);
		if (eww)
			wetuwn eww;

		ctx = NUWW;
		if (wt) {
			stwuct xfwm_usew_sec_ctx *uctx = nwa_data(wt);

			eww = secuwity_xfwm_powicy_awwoc(&ctx, uctx, GFP_KEWNEW);
			if (eww)
				wetuwn eww;
		}
		xp = xfwm_powicy_bysew_ctx(net, &m, if_id, type, p->diw,
					   &p->sew, ctx, 0, &eww);
		secuwity_xfwm_powicy_fwee(ctx);
	}
	if (xp == NUWW)
		wetuwn -ENOENT;

	if (unwikewy(xp->wawk.dead))
		goto out;

	eww = 0;
	if (up->hawd) {
		xfwm_powicy_dewete(xp, p->diw);
		xfwm_audit_powicy_dewete(xp, 1, twue);
	}
	km_powicy_expiwed(xp, p->diw, up->hawd, nwh->nwmsg_pid);

out:
	xfwm_pow_put(xp);
	wetuwn eww;
}

static int xfwm_add_sa_expiwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct nwattw **attws,
			      stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_state *x;
	int eww;
	stwuct xfwm_usew_expiwe *ue = nwmsg_data(nwh);
	stwuct xfwm_usewsa_info *p = &ue->state;
	stwuct xfwm_mawk m;
	u32 mawk = xfwm_mawk_get(attws, &m);

	x = xfwm_state_wookup(net, mawk, &p->id.daddw, p->id.spi, p->id.pwoto, p->famiwy);

	eww = -ENOENT;
	if (x == NUWW)
		wetuwn eww;

	spin_wock_bh(&x->wock);
	eww = -EINVAW;
	if (x->km.state != XFWM_STATE_VAWID) {
		NW_SET_EWW_MSG(extack, "SA must be in VAWID state");
		goto out;
	}

	km_state_expiwed(x, ue->hawd, nwh->nwmsg_pid);

	if (ue->hawd) {
		__xfwm_state_dewete(x);
		xfwm_audit_state_dewete(x, 1, twue);
	}
	eww = 0;
out:
	spin_unwock_bh(&x->wock);
	xfwm_state_put(x);
	wetuwn eww;
}

static int xfwm_add_acquiwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct nwattw **attws,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_powicy *xp;
	stwuct xfwm_usew_tmpw *ut;
	int i;
	stwuct nwattw *wt = attws[XFWMA_TMPW];
	stwuct xfwm_mawk mawk;

	stwuct xfwm_usew_acquiwe *ua = nwmsg_data(nwh);
	stwuct xfwm_state *x = xfwm_state_awwoc(net);
	int eww = -ENOMEM;

	if (!x)
		goto nomem;

	xfwm_mawk_get(attws, &mawk);

	eww = vewify_newpowicy_info(&ua->powicy, extack);
	if (eww)
		goto fwee_state;
	eww = vewify_sec_ctx_wen(attws, extack);
	if (eww)
		goto fwee_state;

	/*   buiwd an XP */
	xp = xfwm_powicy_constwuct(net, &ua->powicy, attws, &eww, extack);
	if (!xp)
		goto fwee_state;

	memcpy(&x->id, &ua->id, sizeof(ua->id));
	memcpy(&x->pwops.saddw, &ua->saddw, sizeof(ua->saddw));
	memcpy(&x->sew, &ua->sew, sizeof(ua->sew));
	xp->mawk.m = x->mawk.m = mawk.m;
	xp->mawk.v = x->mawk.v = mawk.v;
	ut = nwa_data(wt);
	/* extwact the tempwates and fow each caww km_key */
	fow (i = 0; i < xp->xfwm_nw; i++, ut++) {
		stwuct xfwm_tmpw *t = &xp->xfwm_vec[i];
		memcpy(&x->id, &t->id, sizeof(x->id));
		x->pwops.mode = t->mode;
		x->pwops.weqid = t->weqid;
		x->pwops.famiwy = ut->famiwy;
		t->aawgos = ua->aawgos;
		t->eawgos = ua->eawgos;
		t->cawgos = ua->cawgos;
		eww = km_quewy(x, t, xp);

	}

	xfwm_state_fwee(x);
	kfwee(xp);

	wetuwn 0;

fwee_state:
	xfwm_state_fwee(x);
nomem:
	wetuwn eww;
}

#ifdef CONFIG_XFWM_MIGWATE
static int copy_fwom_usew_migwate(stwuct xfwm_migwate *ma,
				  stwuct xfwm_kmaddwess *k,
				  stwuct nwattw **attws, int *num,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *wt = attws[XFWMA_MIGWATE];
	stwuct xfwm_usew_migwate *um;
	int i, num_migwate;

	if (k != NUWW) {
		stwuct xfwm_usew_kmaddwess *uk;

		uk = nwa_data(attws[XFWMA_KMADDWESS]);
		memcpy(&k->wocaw, &uk->wocaw, sizeof(k->wocaw));
		memcpy(&k->wemote, &uk->wemote, sizeof(k->wemote));
		k->famiwy = uk->famiwy;
		k->wesewved = uk->wesewved;
	}

	um = nwa_data(wt);
	num_migwate = nwa_wen(wt) / sizeof(*um);

	if (num_migwate <= 0 || num_migwate > XFWM_MAX_DEPTH) {
		NW_SET_EWW_MSG(extack, "Invawid numbew of SAs to migwate, must be 0 < num <= XFWM_MAX_DEPTH (6)");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_migwate; i++, um++, ma++) {
		memcpy(&ma->owd_daddw, &um->owd_daddw, sizeof(ma->owd_daddw));
		memcpy(&ma->owd_saddw, &um->owd_saddw, sizeof(ma->owd_saddw));
		memcpy(&ma->new_daddw, &um->new_daddw, sizeof(ma->new_daddw));
		memcpy(&ma->new_saddw, &um->new_saddw, sizeof(ma->new_saddw));

		ma->pwoto = um->pwoto;
		ma->mode = um->mode;
		ma->weqid = um->weqid;

		ma->owd_famiwy = um->owd_famiwy;
		ma->new_famiwy = um->new_famiwy;
	}

	*num = i;
	wetuwn 0;
}

static int xfwm_do_migwate(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_usewpowicy_id *pi = nwmsg_data(nwh);
	stwuct xfwm_migwate m[XFWM_MAX_DEPTH];
	stwuct xfwm_kmaddwess km, *kmp;
	u8 type;
	int eww;
	int n = 0;
	stwuct net *net = sock_net(skb->sk);
	stwuct xfwm_encap_tmpw  *encap = NUWW;
	u32 if_id = 0;

	if (!attws[XFWMA_MIGWATE]) {
		NW_SET_EWW_MSG(extack, "Missing wequiwed MIGWATE attwibute");
		wetuwn -EINVAW;
	}

	kmp = attws[XFWMA_KMADDWESS] ? &km : NUWW;

	eww = copy_fwom_usew_powicy_type(&type, attws, extack);
	if (eww)
		wetuwn eww;

	eww = copy_fwom_usew_migwate(m, kmp, attws, &n, extack);
	if (eww)
		wetuwn eww;

	if (!n)
		wetuwn 0;

	if (attws[XFWMA_ENCAP]) {
		encap = kmemdup(nwa_data(attws[XFWMA_ENCAP]),
				sizeof(*encap), GFP_KEWNEW);
		if (!encap)
			wetuwn -ENOMEM;
	}

	if (attws[XFWMA_IF_ID])
		if_id = nwa_get_u32(attws[XFWMA_IF_ID]);

	eww = xfwm_migwate(&pi->sew, pi->diw, type, m, n, kmp, net, encap,
			   if_id, extack);

	kfwee(encap);

	wetuwn eww;
}
#ewse
static int xfwm_do_migwate(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct nwattw **attws, stwuct netwink_ext_ack *extack)
{
	wetuwn -ENOPWOTOOPT;
}
#endif

#ifdef CONFIG_XFWM_MIGWATE
static int copy_to_usew_migwate(const stwuct xfwm_migwate *m, stwuct sk_buff *skb)
{
	stwuct xfwm_usew_migwate um;

	memset(&um, 0, sizeof(um));
	um.pwoto = m->pwoto;
	um.mode = m->mode;
	um.weqid = m->weqid;
	um.owd_famiwy = m->owd_famiwy;
	memcpy(&um.owd_daddw, &m->owd_daddw, sizeof(um.owd_daddw));
	memcpy(&um.owd_saddw, &m->owd_saddw, sizeof(um.owd_saddw));
	um.new_famiwy = m->new_famiwy;
	memcpy(&um.new_daddw, &m->new_daddw, sizeof(um.new_daddw));
	memcpy(&um.new_saddw, &m->new_saddw, sizeof(um.new_saddw));

	wetuwn nwa_put(skb, XFWMA_MIGWATE, sizeof(um), &um);
}

static int copy_to_usew_kmaddwess(const stwuct xfwm_kmaddwess *k, stwuct sk_buff *skb)
{
	stwuct xfwm_usew_kmaddwess uk;

	memset(&uk, 0, sizeof(uk));
	uk.famiwy = k->famiwy;
	uk.wesewved = k->wesewved;
	memcpy(&uk.wocaw, &k->wocaw, sizeof(uk.wocaw));
	memcpy(&uk.wemote, &k->wemote, sizeof(uk.wemote));

	wetuwn nwa_put(skb, XFWMA_KMADDWESS, sizeof(uk), &uk);
}

static inwine unsigned int xfwm_migwate_msgsize(int num_migwate, int with_kma,
						int with_encp)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usewpowicy_id))
	      + (with_kma ? nwa_totaw_size(sizeof(stwuct xfwm_kmaddwess)) : 0)
	      + (with_encp ? nwa_totaw_size(sizeof(stwuct xfwm_encap_tmpw)) : 0)
	      + nwa_totaw_size(sizeof(stwuct xfwm_usew_migwate) * num_migwate)
	      + usewpowicy_type_attwsize();
}

static int buiwd_migwate(stwuct sk_buff *skb, const stwuct xfwm_migwate *m,
			 int num_migwate, const stwuct xfwm_kmaddwess *k,
			 const stwuct xfwm_sewectow *sew,
			 const stwuct xfwm_encap_tmpw *encap, u8 diw, u8 type)
{
	const stwuct xfwm_migwate *mp;
	stwuct xfwm_usewpowicy_id *pow_id;
	stwuct nwmsghdw *nwh;
	int i, eww;

	nwh = nwmsg_put(skb, 0, 0, XFWM_MSG_MIGWATE, sizeof(*pow_id), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	pow_id = nwmsg_data(nwh);
	/* copy data fwom sewectow, diw, and type to the pow_id */
	memset(pow_id, 0, sizeof(*pow_id));
	memcpy(&pow_id->sew, sew, sizeof(pow_id->sew));
	pow_id->diw = diw;

	if (k != NUWW) {
		eww = copy_to_usew_kmaddwess(k, skb);
		if (eww)
			goto out_cancew;
	}
	if (encap) {
		eww = nwa_put(skb, XFWMA_ENCAP, sizeof(*encap), encap);
		if (eww)
			goto out_cancew;
	}
	eww = copy_to_usew_powicy_type(type, skb);
	if (eww)
		goto out_cancew;
	fow (i = 0, mp = m ; i < num_migwate; i++, mp++) {
		eww = copy_to_usew_migwate(mp, skb);
		if (eww)
			goto out_cancew;
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;

out_cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn eww;
}

static int xfwm_send_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
			     const stwuct xfwm_migwate *m, int num_migwate,
			     const stwuct xfwm_kmaddwess *k,
			     const stwuct xfwm_encap_tmpw *encap)
{
	stwuct net *net = &init_net;
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(xfwm_migwate_msgsize(num_migwate, !!k, !!encap),
			GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	/* buiwd migwate */
	eww = buiwd_migwate(skb, m, num_migwate, k, sew, encap, diw, type);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_MIGWATE);
}
#ewse
static int xfwm_send_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
			     const stwuct xfwm_migwate *m, int num_migwate,
			     const stwuct xfwm_kmaddwess *k,
			     const stwuct xfwm_encap_tmpw *encap)
{
	wetuwn -ENOPWOTOOPT;
}
#endif

#define XMSGSIZE(type) sizeof(stwuct type)

const int xfwm_msg_min[XFWM_NW_MSGTYPES] = {
	[XFWM_MSG_NEWSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_info),
	[XFWM_MSG_DEWSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_id),
	[XFWM_MSG_GETSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_id),
	[XFWM_MSG_NEWPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_info),
	[XFWM_MSG_DEWPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_GETPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_AWWOCSPI    - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewspi_info),
	[XFWM_MSG_ACQUIWE     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_acquiwe),
	[XFWM_MSG_EXPIWE      - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_expiwe),
	[XFWM_MSG_UPDPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_info),
	[XFWM_MSG_UPDSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_info),
	[XFWM_MSG_POWEXPIWE   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_powexpiwe),
	[XFWM_MSG_FWUSHSA     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_fwush),
	[XFWM_MSG_FWUSHPOWICY - XFWM_MSG_BASE] = 0,
	[XFWM_MSG_NEWAE       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_aevent_id),
	[XFWM_MSG_GETAE       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_aevent_id),
	[XFWM_MSG_WEPOWT      - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_wepowt),
	[XFWM_MSG_MIGWATE     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_GETSADINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_NEWSPDINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_GETSPDINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_SETDEFAUWT  - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_defauwt),
	[XFWM_MSG_GETDEFAUWT  - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_defauwt),
};
EXPOWT_SYMBOW_GPW(xfwm_msg_min);

#undef XMSGSIZE

const stwuct nwa_powicy xfwma_powicy[XFWMA_MAX+1] = {
	[XFWMA_SA]		= { .wen = sizeof(stwuct xfwm_usewsa_info)},
	[XFWMA_POWICY]		= { .wen = sizeof(stwuct xfwm_usewpowicy_info)},
	[XFWMA_WASTUSED]	= { .type = NWA_U64},
	[XFWMA_AWG_AUTH_TWUNC]	= { .wen = sizeof(stwuct xfwm_awgo_auth)},
	[XFWMA_AWG_AEAD]	= { .wen = sizeof(stwuct xfwm_awgo_aead) },
	[XFWMA_AWG_AUTH]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_AWG_CWYPT]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_AWG_COMP]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_ENCAP]		= { .wen = sizeof(stwuct xfwm_encap_tmpw) },
	[XFWMA_TMPW]		= { .wen = sizeof(stwuct xfwm_usew_tmpw) },
	[XFWMA_SEC_CTX]		= { .wen = sizeof(stwuct xfwm_usew_sec_ctx) },
	[XFWMA_WTIME_VAW]	= { .wen = sizeof(stwuct xfwm_wifetime_cuw) },
	[XFWMA_WEPWAY_VAW]	= { .wen = sizeof(stwuct xfwm_wepway_state) },
	[XFWMA_WEPWAY_THWESH]	= { .type = NWA_U32 },
	[XFWMA_ETIMEW_THWESH]	= { .type = NWA_U32 },
	[XFWMA_SWCADDW]		= { .wen = sizeof(xfwm_addwess_t) },
	[XFWMA_COADDW]		= { .wen = sizeof(xfwm_addwess_t) },
	[XFWMA_POWICY_TYPE]	= { .wen = sizeof(stwuct xfwm_usewpowicy_type)},
	[XFWMA_MIGWATE]		= { .wen = sizeof(stwuct xfwm_usew_migwate) },
	[XFWMA_KMADDWESS]	= { .wen = sizeof(stwuct xfwm_usew_kmaddwess) },
	[XFWMA_MAWK]		= { .wen = sizeof(stwuct xfwm_mawk) },
	[XFWMA_TFCPAD]		= { .type = NWA_U32 },
	[XFWMA_WEPWAY_ESN_VAW]	= { .wen = sizeof(stwuct xfwm_wepway_state_esn) },
	[XFWMA_SA_EXTWA_FWAGS]	= { .type = NWA_U32 },
	[XFWMA_PWOTO]		= { .type = NWA_U8 },
	[XFWMA_ADDWESS_FIWTEW]	= { .wen = sizeof(stwuct xfwm_addwess_fiwtew) },
	[XFWMA_OFFWOAD_DEV]	= { .wen = sizeof(stwuct xfwm_usew_offwoad) },
	[XFWMA_SET_MAWK]	= { .type = NWA_U32 },
	[XFWMA_SET_MAWK_MASK]	= { .type = NWA_U32 },
	[XFWMA_IF_ID]		= { .type = NWA_U32 },
	[XFWMA_MTIMEW_THWESH]   = { .type = NWA_U32 },
};
EXPOWT_SYMBOW_GPW(xfwma_powicy);

static const stwuct nwa_powicy xfwma_spd_powicy[XFWMA_SPD_MAX+1] = {
	[XFWMA_SPD_IPV4_HTHWESH] = { .wen = sizeof(stwuct xfwmu_spdhthwesh) },
	[XFWMA_SPD_IPV6_HTHWESH] = { .wen = sizeof(stwuct xfwmu_spdhthwesh) },
};

static const stwuct xfwm_wink {
	int (*doit)(stwuct sk_buff *, stwuct nwmsghdw *, stwuct nwattw **,
		    stwuct netwink_ext_ack *);
	int (*stawt)(stwuct netwink_cawwback *);
	int (*dump)(stwuct sk_buff *, stwuct netwink_cawwback *);
	int (*done)(stwuct netwink_cawwback *);
	const stwuct nwa_powicy *nwa_pow;
	int nwa_max;
} xfwm_dispatch[XFWM_NW_MSGTYPES] = {
	[XFWM_MSG_NEWSA       - XFWM_MSG_BASE] = { .doit = xfwm_add_sa        },
	[XFWM_MSG_DEWSA       - XFWM_MSG_BASE] = { .doit = xfwm_dew_sa        },
	[XFWM_MSG_GETSA       - XFWM_MSG_BASE] = { .doit = xfwm_get_sa,
						   .dump = xfwm_dump_sa,
						   .done = xfwm_dump_sa_done  },
	[XFWM_MSG_NEWPOWICY   - XFWM_MSG_BASE] = { .doit = xfwm_add_powicy    },
	[XFWM_MSG_DEWPOWICY   - XFWM_MSG_BASE] = { .doit = xfwm_get_powicy    },
	[XFWM_MSG_GETPOWICY   - XFWM_MSG_BASE] = { .doit = xfwm_get_powicy,
						   .stawt = xfwm_dump_powicy_stawt,
						   .dump = xfwm_dump_powicy,
						   .done = xfwm_dump_powicy_done },
	[XFWM_MSG_AWWOCSPI    - XFWM_MSG_BASE] = { .doit = xfwm_awwoc_usewspi },
	[XFWM_MSG_ACQUIWE     - XFWM_MSG_BASE] = { .doit = xfwm_add_acquiwe   },
	[XFWM_MSG_EXPIWE      - XFWM_MSG_BASE] = { .doit = xfwm_add_sa_expiwe },
	[XFWM_MSG_UPDPOWICY   - XFWM_MSG_BASE] = { .doit = xfwm_add_powicy    },
	[XFWM_MSG_UPDSA       - XFWM_MSG_BASE] = { .doit = xfwm_add_sa        },
	[XFWM_MSG_POWEXPIWE   - XFWM_MSG_BASE] = { .doit = xfwm_add_pow_expiwe},
	[XFWM_MSG_FWUSHSA     - XFWM_MSG_BASE] = { .doit = xfwm_fwush_sa      },
	[XFWM_MSG_FWUSHPOWICY - XFWM_MSG_BASE] = { .doit = xfwm_fwush_powicy  },
	[XFWM_MSG_NEWAE       - XFWM_MSG_BASE] = { .doit = xfwm_new_ae  },
	[XFWM_MSG_GETAE       - XFWM_MSG_BASE] = { .doit = xfwm_get_ae  },
	[XFWM_MSG_MIGWATE     - XFWM_MSG_BASE] = { .doit = xfwm_do_migwate    },
	[XFWM_MSG_GETSADINFO  - XFWM_MSG_BASE] = { .doit = xfwm_get_sadinfo   },
	[XFWM_MSG_NEWSPDINFO  - XFWM_MSG_BASE] = { .doit = xfwm_set_spdinfo,
						   .nwa_pow = xfwma_spd_powicy,
						   .nwa_max = XFWMA_SPD_MAX },
	[XFWM_MSG_GETSPDINFO  - XFWM_MSG_BASE] = { .doit = xfwm_get_spdinfo   },
	[XFWM_MSG_SETDEFAUWT  - XFWM_MSG_BASE] = { .doit = xfwm_set_defauwt   },
	[XFWM_MSG_GETDEFAUWT  - XFWM_MSG_BASE] = { .doit = xfwm_get_defauwt   },
};

static int xfwm_usew_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *attws[XFWMA_MAX+1];
	const stwuct xfwm_wink *wink;
	stwuct nwmsghdw *nwh64 = NUWW;
	int type, eww;

	type = nwh->nwmsg_type;
	if (type > XFWM_MSG_MAX)
		wetuwn -EINVAW;

	type -= XFWM_MSG_BASE;
	wink = &xfwm_dispatch[type];

	/* Aww opewations wequiwe pwiviweges, even GET */
	if (!netwink_net_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (in_compat_syscaww()) {
		stwuct xfwm_twanswatow *xtw = xfwm_get_twanswatow();

		if (!xtw)
			wetuwn -EOPNOTSUPP;

		nwh64 = xtw->wcv_msg_compat(nwh, wink->nwa_max,
					    wink->nwa_pow, extack);
		xfwm_put_twanswatow(xtw);
		if (IS_EWW(nwh64))
			wetuwn PTW_EWW(nwh64);
		if (nwh64)
			nwh = nwh64;
	}

	if ((type == (XFWM_MSG_GETSA - XFWM_MSG_BASE) ||
	     type == (XFWM_MSG_GETPOWICY - XFWM_MSG_BASE)) &&
	    (nwh->nwmsg_fwags & NWM_F_DUMP)) {
		stwuct netwink_dump_contwow c = {
			.stawt = wink->stawt,
			.dump = wink->dump,
			.done = wink->done,
		};

		if (wink->dump == NUWW) {
			eww = -EINVAW;
			goto eww;
		}

		eww = netwink_dump_stawt(net->xfwm.nwsk, skb, nwh, &c);
		goto eww;
	}

	eww = nwmsg_pawse_depwecated(nwh, xfwm_msg_min[type], attws,
				     wink->nwa_max ? : XFWMA_MAX,
				     wink->nwa_pow ? : xfwma_powicy, extack);
	if (eww < 0)
		goto eww;

	if (wink->doit == NUWW) {
		eww = -EINVAW;
		goto eww;
	}

	eww = wink->doit(skb, nwh, attws, extack);

	/* We need to fwee skb awwocated in xfwm_awwoc_compat() befowe
	 * wetuwning fwom this function, because consume_skb() won't take
	 * cawe of fwag_wist since netwink destwuctow sets
	 * sbk->head to NUWW. (see netwink_skb_destwuctow())
	 */
	if (skb_has_fwag_wist(skb)) {
		kfwee_skb(skb_shinfo(skb)->fwag_wist);
		skb_shinfo(skb)->fwag_wist = NUWW;
	}

eww:
	kvfwee(nwh64);
	wetuwn eww;
}

static void xfwm_netwink_wcv(stwuct sk_buff *skb)
{
	stwuct net *net = sock_net(skb->sk);

	mutex_wock(&net->xfwm.xfwm_cfg_mutex);
	netwink_wcv_skb(skb, &xfwm_usew_wcv_msg);
	mutex_unwock(&net->xfwm.xfwm_cfg_mutex);
}

static inwine unsigned int xfwm_expiwe_msgsize(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usew_expiwe))
	       + nwa_totaw_size(sizeof(stwuct xfwm_mawk));
}

static int buiwd_expiwe(stwuct sk_buff *skb, stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct xfwm_usew_expiwe *ue;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, c->powtid, 0, XFWM_MSG_EXPIWE, sizeof(*ue), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ue = nwmsg_data(nwh);
	copy_to_usew_state(x, &ue->state);
	ue->hawd = (c->data.hawd != 0) ? 1 : 0;
	/* cweaw the padding bytes */
	memset_aftew(ue, 0, hawd);

	eww = xfwm_mawk_put(skb, &x->mawk);
	if (eww)
		wetuwn eww;

	eww = xfwm_if_id_put(skb, x->if_id);
	if (eww)
		wetuwn eww;

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_exp_state_notify(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct net *net = xs_net(x);
	stwuct sk_buff *skb;

	skb = nwmsg_new(xfwm_expiwe_msgsize(), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	if (buiwd_expiwe(skb, x, c) < 0) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_EXPIWE);
}

static int xfwm_aevent_state_notify(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct net *net = xs_net(x);
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(xfwm_aevent_msgsize(x), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_aevent(skb, x, c);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_AEVENTS);
}

static int xfwm_notify_sa_fwush(const stwuct km_event *c)
{
	stwuct net *net = c->net;
	stwuct xfwm_usewsa_fwush *p;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	int wen = NWMSG_AWIGN(sizeof(stwuct xfwm_usewsa_fwush));

	skb = nwmsg_new(wen, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, c->powtid, c->seq, XFWM_MSG_FWUSHSA, sizeof(*p), 0);
	if (nwh == NUWW) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	p = nwmsg_data(nwh);
	p->pwoto = c->data.pwoto;

	nwmsg_end(skb, nwh);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_SA);
}

static inwine unsigned int xfwm_sa_wen(stwuct xfwm_state *x)
{
	unsigned int w = 0;
	if (x->aead)
		w += nwa_totaw_size(aead_wen(x->aead));
	if (x->aawg) {
		w += nwa_totaw_size(sizeof(stwuct xfwm_awgo) +
				    (x->aawg->awg_key_wen + 7) / 8);
		w += nwa_totaw_size(xfwm_awg_auth_wen(x->aawg));
	}
	if (x->eawg)
		w += nwa_totaw_size(xfwm_awg_wen(x->eawg));
	if (x->cawg)
		w += nwa_totaw_size(sizeof(*x->cawg));
	if (x->encap)
		w += nwa_totaw_size(sizeof(*x->encap));
	if (x->tfcpad)
		w += nwa_totaw_size(sizeof(x->tfcpad));
	if (x->wepway_esn)
		w += nwa_totaw_size(xfwm_wepway_state_esn_wen(x->wepway_esn));
	ewse
		w += nwa_totaw_size(sizeof(stwuct xfwm_wepway_state));
	if (x->secuwity)
		w += nwa_totaw_size(sizeof(stwuct xfwm_usew_sec_ctx) +
				    x->secuwity->ctx_wen);
	if (x->coaddw)
		w += nwa_totaw_size(sizeof(*x->coaddw));
	if (x->pwops.extwa_fwags)
		w += nwa_totaw_size(sizeof(x->pwops.extwa_fwags));
	if (x->xso.dev)
		 w += nwa_totaw_size(sizeof(stwuct xfwm_usew_offwoad));
	if (x->pwops.smawk.v | x->pwops.smawk.m) {
		w += nwa_totaw_size(sizeof(x->pwops.smawk.v));
		w += nwa_totaw_size(sizeof(x->pwops.smawk.m));
	}
	if (x->if_id)
		w += nwa_totaw_size(sizeof(x->if_id));

	/* Must count x->wastused as it may become non-zewo behind ouw back. */
	w += nwa_totaw_size_64bit(sizeof(u64));

	if (x->mapping_maxage)
		w += nwa_totaw_size(sizeof(x->mapping_maxage));

	wetuwn w;
}

static int xfwm_notify_sa(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct net *net = xs_net(x);
	stwuct xfwm_usewsa_info *p;
	stwuct xfwm_usewsa_id *id;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	unsigned int wen = xfwm_sa_wen(x);
	unsigned int headwen;
	int eww;

	headwen = sizeof(*p);
	if (c->event == XFWM_MSG_DEWSA) {
		wen += nwa_totaw_size(headwen);
		headwen = sizeof(*id);
		wen += nwa_totaw_size(sizeof(stwuct xfwm_mawk));
	}
	wen += NWMSG_AWIGN(headwen);

	skb = nwmsg_new(wen, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, c->powtid, c->seq, c->event, headwen, 0);
	eww = -EMSGSIZE;
	if (nwh == NUWW)
		goto out_fwee_skb;

	p = nwmsg_data(nwh);
	if (c->event == XFWM_MSG_DEWSA) {
		stwuct nwattw *attw;

		id = nwmsg_data(nwh);
		memset(id, 0, sizeof(*id));
		memcpy(&id->daddw, &x->id.daddw, sizeof(id->daddw));
		id->spi = x->id.spi;
		id->famiwy = x->pwops.famiwy;
		id->pwoto = x->id.pwoto;

		attw = nwa_wesewve(skb, XFWMA_SA, sizeof(*p));
		eww = -EMSGSIZE;
		if (attw == NUWW)
			goto out_fwee_skb;

		p = nwa_data(attw);
	}
	eww = copy_to_usew_state_extwa(x, p, skb);
	if (eww)
		goto out_fwee_skb;

	nwmsg_end(skb, nwh);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_SA);

out_fwee_skb:
	kfwee_skb(skb);
	wetuwn eww;
}

static int xfwm_send_state_notify(stwuct xfwm_state *x, const stwuct km_event *c)
{

	switch (c->event) {
	case XFWM_MSG_EXPIWE:
		wetuwn xfwm_exp_state_notify(x, c);
	case XFWM_MSG_NEWAE:
		wetuwn xfwm_aevent_state_notify(x, c);
	case XFWM_MSG_DEWSA:
	case XFWM_MSG_UPDSA:
	case XFWM_MSG_NEWSA:
		wetuwn xfwm_notify_sa(x, c);
	case XFWM_MSG_FWUSHSA:
		wetuwn xfwm_notify_sa_fwush(c);
	defauwt:
		pwintk(KEWN_NOTICE "xfwm_usew: Unknown SA event %d\n",
		       c->event);
		bweak;
	}

	wetuwn 0;

}

static inwine unsigned int xfwm_acquiwe_msgsize(stwuct xfwm_state *x,
						stwuct xfwm_powicy *xp)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usew_acquiwe))
	       + nwa_totaw_size(sizeof(stwuct xfwm_usew_tmpw) * xp->xfwm_nw)
	       + nwa_totaw_size(sizeof(stwuct xfwm_mawk))
	       + nwa_totaw_size(xfwm_usew_sec_ctx_size(x->secuwity))
	       + usewpowicy_type_attwsize();
}

static int buiwd_acquiwe(stwuct sk_buff *skb, stwuct xfwm_state *x,
			 stwuct xfwm_tmpw *xt, stwuct xfwm_powicy *xp)
{
	__u32 seq = xfwm_get_acqseq();
	stwuct xfwm_usew_acquiwe *ua;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, 0, 0, XFWM_MSG_ACQUIWE, sizeof(*ua), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ua = nwmsg_data(nwh);
	memcpy(&ua->id, &x->id, sizeof(ua->id));
	memcpy(&ua->saddw, &x->pwops.saddw, sizeof(ua->saddw));
	memcpy(&ua->sew, &x->sew, sizeof(ua->sew));
	copy_to_usew_powicy(xp, &ua->powicy, XFWM_POWICY_OUT);
	ua->aawgos = xt->aawgos;
	ua->eawgos = xt->eawgos;
	ua->cawgos = xt->cawgos;
	ua->seq = x->km.seq = seq;

	eww = copy_to_usew_tmpw(xp, skb);
	if (!eww)
		eww = copy_to_usew_state_sec_ctx(x, skb);
	if (!eww)
		eww = copy_to_usew_powicy_type(xp->type, skb);
	if (!eww)
		eww = xfwm_mawk_put(skb, &xp->mawk);
	if (!eww)
		eww = xfwm_if_id_put(skb, xp->if_id);
	if (!eww && xp->xdo.dev)
		eww = copy_usew_offwoad(&xp->xdo, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_send_acquiwe(stwuct xfwm_state *x, stwuct xfwm_tmpw *xt,
			     stwuct xfwm_powicy *xp)
{
	stwuct net *net = xs_net(x);
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(xfwm_acquiwe_msgsize(x, xp), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_acquiwe(skb, x, xt, xp);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_ACQUIWE);
}

/* Usew gives us xfwm_usew_powicy_info fowwowed by an awway of 0
 * ow mowe tempwates.
 */
static stwuct xfwm_powicy *xfwm_compiwe_powicy(stwuct sock *sk, int opt,
					       u8 *data, int wen, int *diw)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_usewpowicy_info *p = (stwuct xfwm_usewpowicy_info *)data;
	stwuct xfwm_usew_tmpw *ut = (stwuct xfwm_usew_tmpw *) (p + 1);
	stwuct xfwm_powicy *xp;
	int nw;

	switch (sk->sk_famiwy) {
	case AF_INET:
		if (opt != IP_XFWM_POWICY) {
			*diw = -EOPNOTSUPP;
			wetuwn NUWW;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		if (opt != IPV6_XFWM_POWICY) {
			*diw = -EOPNOTSUPP;
			wetuwn NUWW;
		}
		bweak;
#endif
	defauwt:
		*diw = -EINVAW;
		wetuwn NUWW;
	}

	*diw = -EINVAW;

	if (wen < sizeof(*p) ||
	    vewify_newpowicy_info(p, NUWW))
		wetuwn NUWW;

	nw = ((wen - sizeof(*p)) / sizeof(*ut));
	if (vawidate_tmpw(nw, ut, p->sew.famiwy, p->diw, NUWW))
		wetuwn NUWW;

	if (p->diw > XFWM_POWICY_OUT)
		wetuwn NUWW;

	xp = xfwm_powicy_awwoc(net, GFP_ATOMIC);
	if (xp == NUWW) {
		*diw = -ENOBUFS;
		wetuwn NUWW;
	}

	copy_fwom_usew_powicy(xp, p);
	xp->type = XFWM_POWICY_TYPE_MAIN;
	copy_tempwates(xp, ut, nw);

	*diw = p->diw;

	wetuwn xp;
}

static inwine unsigned int xfwm_powexpiwe_msgsize(stwuct xfwm_powicy *xp)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usew_powexpiwe))
	       + nwa_totaw_size(sizeof(stwuct xfwm_usew_tmpw) * xp->xfwm_nw)
	       + nwa_totaw_size(xfwm_usew_sec_ctx_size(xp->secuwity))
	       + nwa_totaw_size(sizeof(stwuct xfwm_mawk))
	       + usewpowicy_type_attwsize();
}

static int buiwd_powexpiwe(stwuct sk_buff *skb, stwuct xfwm_powicy *xp,
			   int diw, const stwuct km_event *c)
{
	stwuct xfwm_usew_powexpiwe *upe;
	int hawd = c->data.hawd;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, c->powtid, 0, XFWM_MSG_POWEXPIWE, sizeof(*upe), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	upe = nwmsg_data(nwh);
	copy_to_usew_powicy(xp, &upe->pow, diw);
	eww = copy_to_usew_tmpw(xp, skb);
	if (!eww)
		eww = copy_to_usew_sec_ctx(xp, skb);
	if (!eww)
		eww = copy_to_usew_powicy_type(xp->type, skb);
	if (!eww)
		eww = xfwm_mawk_put(skb, &xp->mawk);
	if (!eww)
		eww = xfwm_if_id_put(skb, xp->if_id);
	if (!eww && xp->xdo.dev)
		eww = copy_usew_offwoad(&xp->xdo, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		wetuwn eww;
	}
	upe->hawd = !!hawd;

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_exp_powicy_notify(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{
	stwuct net *net = xp_net(xp);
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(xfwm_powexpiwe_msgsize(xp), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_powexpiwe(skb, xp, diw, c);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_EXPIWE);
}

static int xfwm_notify_powicy(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{
	unsigned int wen = nwa_totaw_size(sizeof(stwuct xfwm_usew_tmpw) * xp->xfwm_nw);
	stwuct net *net = xp_net(xp);
	stwuct xfwm_usewpowicy_info *p;
	stwuct xfwm_usewpowicy_id *id;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	unsigned int headwen;
	int eww;

	headwen = sizeof(*p);
	if (c->event == XFWM_MSG_DEWPOWICY) {
		wen += nwa_totaw_size(headwen);
		headwen = sizeof(*id);
	}
	wen += usewpowicy_type_attwsize();
	wen += nwa_totaw_size(sizeof(stwuct xfwm_mawk));
	wen += NWMSG_AWIGN(headwen);

	skb = nwmsg_new(wen, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, c->powtid, c->seq, c->event, headwen, 0);
	eww = -EMSGSIZE;
	if (nwh == NUWW)
		goto out_fwee_skb;

	p = nwmsg_data(nwh);
	if (c->event == XFWM_MSG_DEWPOWICY) {
		stwuct nwattw *attw;

		id = nwmsg_data(nwh);
		memset(id, 0, sizeof(*id));
		id->diw = diw;
		if (c->data.byid)
			id->index = xp->index;
		ewse
			memcpy(&id->sew, &xp->sewectow, sizeof(id->sew));

		attw = nwa_wesewve(skb, XFWMA_POWICY, sizeof(*p));
		eww = -EMSGSIZE;
		if (attw == NUWW)
			goto out_fwee_skb;

		p = nwa_data(attw);
	}

	copy_to_usew_powicy(xp, p, diw);
	eww = copy_to_usew_tmpw(xp, skb);
	if (!eww)
		eww = copy_to_usew_powicy_type(xp->type, skb);
	if (!eww)
		eww = xfwm_mawk_put(skb, &xp->mawk);
	if (!eww)
		eww = xfwm_if_id_put(skb, xp->if_id);
	if (!eww && xp->xdo.dev)
		eww = copy_usew_offwoad(&xp->xdo, skb);
	if (eww)
		goto out_fwee_skb;

	nwmsg_end(skb, nwh);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_POWICY);

out_fwee_skb:
	kfwee_skb(skb);
	wetuwn eww;
}

static int xfwm_notify_powicy_fwush(const stwuct km_event *c)
{
	stwuct net *net = c->net;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(usewpowicy_type_attwsize(), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, c->powtid, c->seq, XFWM_MSG_FWUSHPOWICY, 0, 0);
	eww = -EMSGSIZE;
	if (nwh == NUWW)
		goto out_fwee_skb;
	eww = copy_to_usew_powicy_type(c->data.type, skb);
	if (eww)
		goto out_fwee_skb;

	nwmsg_end(skb, nwh);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_POWICY);

out_fwee_skb:
	kfwee_skb(skb);
	wetuwn eww;
}

static int xfwm_send_powicy_notify(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{

	switch (c->event) {
	case XFWM_MSG_NEWPOWICY:
	case XFWM_MSG_UPDPOWICY:
	case XFWM_MSG_DEWPOWICY:
		wetuwn xfwm_notify_powicy(xp, diw, c);
	case XFWM_MSG_FWUSHPOWICY:
		wetuwn xfwm_notify_powicy_fwush(c);
	case XFWM_MSG_POWEXPIWE:
		wetuwn xfwm_exp_powicy_notify(xp, diw, c);
	defauwt:
		pwintk(KEWN_NOTICE "xfwm_usew: Unknown Powicy event %d\n",
		       c->event);
	}

	wetuwn 0;

}

static inwine unsigned int xfwm_wepowt_msgsize(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usew_wepowt));
}

static int buiwd_wepowt(stwuct sk_buff *skb, u8 pwoto,
			stwuct xfwm_sewectow *sew, xfwm_addwess_t *addw)
{
	stwuct xfwm_usew_wepowt *uw;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, 0, 0, XFWM_MSG_WEPOWT, sizeof(*uw), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	uw = nwmsg_data(nwh);
	uw->pwoto = pwoto;
	memcpy(&uw->sew, sew, sizeof(uw->sew));

	if (addw) {
		int eww = nwa_put(skb, XFWMA_COADDW, sizeof(*addw), addw);
		if (eww) {
			nwmsg_cancew(skb, nwh);
			wetuwn eww;
		}
	}
	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_send_wepowt(stwuct net *net, u8 pwoto,
			    stwuct xfwm_sewectow *sew, xfwm_addwess_t *addw)
{
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(xfwm_wepowt_msgsize(), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_wepowt(skb, pwoto, sew, addw);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_WEPOWT);
}

static inwine unsigned int xfwm_mapping_msgsize(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct xfwm_usew_mapping));
}

static int buiwd_mapping(stwuct sk_buff *skb, stwuct xfwm_state *x,
			 xfwm_addwess_t *new_saddw, __be16 new_spowt)
{
	stwuct xfwm_usew_mapping *um;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, 0, 0, XFWM_MSG_MAPPING, sizeof(*um), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	um = nwmsg_data(nwh);

	memcpy(&um->id.daddw, &x->id.daddw, sizeof(um->id.daddw));
	um->id.spi = x->id.spi;
	um->id.famiwy = x->pwops.famiwy;
	um->id.pwoto = x->id.pwoto;
	memcpy(&um->new_saddw, new_saddw, sizeof(um->new_saddw));
	memcpy(&um->owd_saddw, &x->pwops.saddw, sizeof(um->owd_saddw));
	um->new_spowt = new_spowt;
	um->owd_spowt = x->encap->encap_spowt;
	um->weqid = x->pwops.weqid;

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int xfwm_send_mapping(stwuct xfwm_state *x, xfwm_addwess_t *ipaddw,
			     __be16 spowt)
{
	stwuct net *net = xs_net(x);
	stwuct sk_buff *skb;
	int eww;

	if (x->id.pwoto != IPPWOTO_ESP)
		wetuwn -EINVAW;

	if (!x->encap)
		wetuwn -EINVAW;

	skb = nwmsg_new(xfwm_mapping_msgsize(), GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	eww = buiwd_mapping(skb, x, ipaddw, spowt);
	BUG_ON(eww < 0);

	wetuwn xfwm_nwmsg_muwticast(net, skb, 0, XFWMNWGWP_MAPPING);
}

static boow xfwm_is_awive(const stwuct km_event *c)
{
	wetuwn (boow)xfwm_acquiwe_is_on(c->net);
}

static stwuct xfwm_mgw netwink_mgw = {
	.notify		= xfwm_send_state_notify,
	.acquiwe	= xfwm_send_acquiwe,
	.compiwe_powicy	= xfwm_compiwe_powicy,
	.notify_powicy	= xfwm_send_powicy_notify,
	.wepowt		= xfwm_send_wepowt,
	.migwate	= xfwm_send_migwate,
	.new_mapping	= xfwm_send_mapping,
	.is_awive	= xfwm_is_awive,
};

static int __net_init xfwm_usew_net_init(stwuct net *net)
{
	stwuct sock *nwsk;
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= XFWMNWGWP_MAX,
		.input	= xfwm_netwink_wcv,
	};

	nwsk = netwink_kewnew_cweate(net, NETWINK_XFWM, &cfg);
	if (nwsk == NUWW)
		wetuwn -ENOMEM;
	net->xfwm.nwsk_stash = nwsk; /* Don't set to NUWW */
	wcu_assign_pointew(net->xfwm.nwsk, nwsk);
	wetuwn 0;
}

static void __net_exit xfwm_usew_net_pwe_exit(stwuct net *net)
{
	WCU_INIT_POINTEW(net->xfwm.nwsk, NUWW);
}

static void __net_exit xfwm_usew_net_exit(stwuct wist_head *net_exit_wist)
{
	stwuct net *net;

	wist_fow_each_entwy(net, net_exit_wist, exit_wist)
		netwink_kewnew_wewease(net->xfwm.nwsk_stash);
}

static stwuct pewnet_opewations xfwm_usew_net_ops = {
	.init	    = xfwm_usew_net_init,
	.pwe_exit   = xfwm_usew_net_pwe_exit,
	.exit_batch = xfwm_usew_net_exit,
};

static int __init xfwm_usew_init(void)
{
	int wv;

	pwintk(KEWN_INFO "Initiawizing XFWM netwink socket\n");

	wv = wegistew_pewnet_subsys(&xfwm_usew_net_ops);
	if (wv < 0)
		wetuwn wv;
	xfwm_wegistew_km(&netwink_mgw);
	wetuwn 0;
}

static void __exit xfwm_usew_exit(void)
{
	xfwm_unwegistew_km(&netwink_mgw);
	unwegistew_pewnet_subsys(&xfwm_usew_net_ops);
}

moduwe_init(xfwm_usew_init);
moduwe_exit(xfwm_usew_exit);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NET_PF_PWOTO(PF_NETWINK, NETWINK_XFWM);
