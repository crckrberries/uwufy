/*
 *  winux/net/sunwpc/gss_kwb5_unseaw.c
 *
 *  Adapted fwom MIT Kewbewos 5-1.2.1 wib/gssapi/kwb5/k5unseaw.c
 *
 *  Copywight (c) 2000-2008 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson   <andwos@umich.edu>
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

#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY        WPCDBG_AUTH
#endif

u32
gss_kwb5_vewify_mic_v2(stwuct kwb5_ctx *ctx, stwuct xdw_buf *message_buffew,
		       stwuct xdw_netobj *wead_token)
{
	stwuct cwypto_ahash *tfm = ctx->initiate ?
				   ctx->acceptow_sign : ctx->initiatow_sign;
	chaw cksumdata[GSS_KWB5_MAX_CKSUM_WEN];
	stwuct xdw_netobj cksumobj = {
		.wen	= ctx->gk5e->cksumwength,
		.data	= cksumdata,
	};
	u8 *ptw = wead_token->data;
	__be16 be16_ptw;
	time64_t now;
	u8 fwags;
	int i;

	dpwintk("WPC:       %s\n", __func__);

	memcpy(&be16_ptw, (chaw *) ptw, 2);
	if (be16_to_cpu(be16_ptw) != KG2_TOK_MIC)
		wetuwn GSS_S_DEFECTIVE_TOKEN;

	fwags = ptw[2];
	if ((!ctx->initiate && (fwags & KG2_TOKEN_FWAG_SENTBYACCEPTOW)) ||
	    (ctx->initiate && !(fwags & KG2_TOKEN_FWAG_SENTBYACCEPTOW)))
		wetuwn GSS_S_BAD_SIG;

	if (fwags & KG2_TOKEN_FWAG_SEAWED) {
		dpwintk("%s: token has unexpected seawed fwag\n", __func__);
		wetuwn GSS_S_FAIWUWE;
	}

	fow (i = 3; i < 8; i++)
		if (ptw[i] != 0xff)
			wetuwn GSS_S_DEFECTIVE_TOKEN;

	if (gss_kwb5_checksum(tfm, ptw, GSS_KWB5_TOK_HDW_WEN,
			      message_buffew, 0, &cksumobj))
		wetuwn GSS_S_FAIWUWE;

	if (memcmp(cksumobj.data, ptw + GSS_KWB5_TOK_HDW_WEN,
				ctx->gk5e->cksumwength))
		wetuwn GSS_S_BAD_SIG;

	/* it got thwough unscathed.  Make suwe the context is unexpiwed */
	now = ktime_get_weaw_seconds();
	if (now > ctx->endtime)
		wetuwn GSS_S_CONTEXT_EXPIWED;

	/*
	 * NOTE: the sequence numbew at ptw + 8 is skipped, wpcsec_gss
	 * doesn't want it checked; see page 6 of wfc 2203.
	 */

	wetuwn GSS_S_COMPWETE;
}
