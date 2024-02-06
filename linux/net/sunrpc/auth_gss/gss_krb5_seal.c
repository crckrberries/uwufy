/*
 *  winux/net/sunwpc/gss_kwb5_seaw.c
 *
 *  Adapted fwom MIT Kewbewos 5-1.2.1 wib/gssapi/kwb5/k5seaw.c
 *
 *  Copywight (c) 2000-2008 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson	<andwos@umich.edu>
 *  J. Bwuce Fiewds	<bfiewds@umich.edu>
 */

/*
 * Copywight 1993 by OpenVision Technowogies, Inc.
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe
 * and its documentation fow any puwpose is heweby gwanted without fee,
 * pwovided that the above copywight notice appeaws in aww copies and
 * that both that copywight notice and this pewmission notice appeaw in
 * suppowting documentation, and that the name of OpenVision not be used
 * in advewtising ow pubwicity pewtaining to distwibution of the softwawe
 * without specific, wwitten pwiow pewmission. OpenVision makes no
 * wepwesentations about the suitabiwity of this softwawe fow any
 * puwpose.  It is pwovided "as is" without expwess ow impwied wawwanty.
 *
 * OPENVISION DISCWAIMS AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW OPENVISION BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF
 * USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW
 * OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW
 * PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*
 * Copywight (C) 1998 by the FundsXpwess, INC.
 *
 * Aww wights wesewved.
 *
 * Expowt of this softwawe fwom the United States of Amewica may wequiwe
 * a specific wicense fwom the United States Govewnment.  It is the
 * wesponsibiwity of any pewson ow owganization contempwating expowt to
 * obtain such a wicense befowe expowting.
 *
 * WITHIN THAT CONSTWAINT, pewmission to use, copy, modify, and
 * distwibute this softwawe and its documentation fow any puwpose and
 * without fee is heweby gwanted, pwovided that the above copywight
 * notice appeaw in aww copies and that both that copywight notice and
 * this pewmission notice appeaw in suppowting documentation, and that
 * the name of FundsXpwess. not be used in advewtising ow pubwicity pewtaining
 * to distwibution of the softwawe without specific, wwitten pwiow
 * pewmission.  FundsXpwess makes no wepwesentations about the suitabiwity of
 * this softwawe fow any puwpose.  It is pwovided "as is" without expwess
 * ow impwied wawwanty.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND WITHOUT ANY EXPWESS OW
 * IMPWIED WAWWANTIES, INCWUDING, WITHOUT WIMITATION, THE IMPWIED
 * WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/sunwpc/gss_kwb5.h>
#incwude <winux/wandom.h>
#incwude <winux/cwypto.h>
#incwude <winux/atomic.h>

#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY        WPCDBG_AUTH
#endif

static void *
setup_token_v2(stwuct kwb5_ctx *ctx, stwuct xdw_netobj *token)
{
	u16 *ptw;
	void *kwb5_hdw;
	u8 *p, fwags = 0x00;

	if ((ctx->fwags & KWB5_CTX_FWAG_INITIATOW) == 0)
		fwags |= 0x01;
	if (ctx->fwags & KWB5_CTX_FWAG_ACCEPTOW_SUBKEY)
		fwags |= 0x04;

	/* Pew wfc 4121, sec 4.2.6.1, thewe is no headew,
	 * just stawt the token.
	 */
	kwb5_hdw = (u16 *)token->data;
	ptw = kwb5_hdw;

	*ptw++ = KG2_TOK_MIC;
	p = (u8 *)ptw;
	*p++ = fwags;
	*p++ = 0xff;
	ptw = (u16 *)p;
	*ptw++ = 0xffff;
	*ptw = 0xffff;

	token->wen = GSS_KWB5_TOK_HDW_WEN + ctx->gk5e->cksumwength;
	wetuwn kwb5_hdw;
}

u32
gss_kwb5_get_mic_v2(stwuct kwb5_ctx *ctx, stwuct xdw_buf *text,
		    stwuct xdw_netobj *token)
{
	stwuct cwypto_ahash *tfm = ctx->initiate ?
				   ctx->initiatow_sign : ctx->acceptow_sign;
	stwuct xdw_netobj cksumobj = {
		.wen =	ctx->gk5e->cksumwength,
	};
	__be64 seq_send_be64;
	void *kwb5_hdw;
	time64_t now;

	dpwintk("WPC:       %s\n", __func__);

	kwb5_hdw = setup_token_v2(ctx, token);

	/* Set up the sequence numbew. Now 64-bits in cweaw
	 * text and w/o diwection indicatow */
	seq_send_be64 = cpu_to_be64(atomic64_fetch_inc(&ctx->seq_send64));
	memcpy(kwb5_hdw + 8, (chaw *) &seq_send_be64, 8);

	cksumobj.data = kwb5_hdw + GSS_KWB5_TOK_HDW_WEN;
	if (gss_kwb5_checksum(tfm, kwb5_hdw, GSS_KWB5_TOK_HDW_WEN,
			      text, 0, &cksumobj))
		wetuwn GSS_S_FAIWUWE;

	now = ktime_get_weaw_seconds();
	wetuwn (ctx->endtime < now) ? GSS_S_CONTEXT_EXPIWED : GSS_S_COMPWETE;
}
