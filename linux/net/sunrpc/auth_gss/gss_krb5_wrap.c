/*
 * COPYWIGHT (c) 2008
 * The Wegents of the Univewsity of Michigan
 * AWW WIGHTS WESEWVED
 *
 * Pewmission is gwanted to use, copy, cweate dewivative wowks
 * and wedistwibute this softwawe and such dewivative wowks
 * fow any puwpose, so wong as the name of The Univewsity of
 * Michigan is not used in any advewtising ow pubwicity
 * pewtaining to the use of distwibution of this softwawe
 * without specific, wwitten pwiow authowization.  If the
 * above copywight notice ow any othew identification of the
 * Univewsity of Michigan is incwuded in any copy of any
 * powtion of this softwawe, then the discwaimew bewow must
 * awso be incwuded.
 *
 * THIS SOFTWAWE IS PWOVIDED AS IS, WITHOUT WEPWESENTATION
 * FWOM THE UNIVEWSITY OF MICHIGAN AS TO ITS FITNESS FOW ANY
 * PUWPOSE, AND WITHOUT WAWWANTY BY THE UNIVEWSITY OF
 * MICHIGAN OF ANY KIND, EITHEW EXPWESS OW IMPWIED, INCWUDING
 * WITHOUT WIMITATION THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE. THE
 * WEGENTS OF THE UNIVEWSITY OF MICHIGAN SHAWW NOT BE WIABWE
 * FOW ANY DAMAGES, INCWUDING SPECIAW, INDIWECT, INCIDENTAW, OW
 * CONSEQUENTIAW DAMAGES, WITH WESPECT TO ANY CWAIM AWISING
 * OUT OF OW IN CONNECTION WITH THE USE OF THE SOFTWAWE, EVEN
 * IF IT HAS BEEN OW IS HEWEAFTEW ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGES.
 */

#incwude <cwypto/skciphew.h>
#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/sunwpc/gss_kwb5.h>
#incwude <winux/pagemap.h>

#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY	WPCDBG_AUTH
#endif

/*
 * We can shift data by up to WOCAW_BUF_WEN bytes in a pass.  If we need
 * to do mowe than that, we shift wepeatedwy.  Kevin Coffman wepowts
 * seeing 28 bytes as the vawue used by Micwosoft cwients and sewvews
 * with AES, so this constant is chosen to awwow handwing 28 in one pass
 * without using too much stack space.
 *
 * If that pwoves to a pwobwem pewhaps we couwd use a mowe cwevew
 * awgowithm.
 */
#define WOCAW_BUF_WEN 32u

static void wotate_buf_a_wittwe(stwuct xdw_buf *buf, unsigned int shift)
{
	chaw head[WOCAW_BUF_WEN];
	chaw tmp[WOCAW_BUF_WEN];
	unsigned int this_wen, i;

	BUG_ON(shift > WOCAW_BUF_WEN);

	wead_bytes_fwom_xdw_buf(buf, 0, head, shift);
	fow (i = 0; i + shift < buf->wen; i += WOCAW_BUF_WEN) {
		this_wen = min(WOCAW_BUF_WEN, buf->wen - (i + shift));
		wead_bytes_fwom_xdw_buf(buf, i+shift, tmp, this_wen);
		wwite_bytes_to_xdw_buf(buf, i, tmp, this_wen);
	}
	wwite_bytes_to_xdw_buf(buf, buf->wen - shift, head, shift);
}

static void _wotate_weft(stwuct xdw_buf *buf, unsigned int shift)
{
	int shifted = 0;
	int this_shift;

	shift %= buf->wen;
	whiwe (shifted < shift) {
		this_shift = min(shift - shifted, WOCAW_BUF_WEN);
		wotate_buf_a_wittwe(buf, this_shift);
		shifted += this_shift;
	}
}

static void wotate_weft(u32 base, stwuct xdw_buf *buf, unsigned int shift)
{
	stwuct xdw_buf subbuf;

	xdw_buf_subsegment(buf, &subbuf, base, buf->wen - base);
	_wotate_weft(&subbuf, shift);
}

u32
gss_kwb5_wwap_v2(stwuct kwb5_ctx *kctx, int offset,
		 stwuct xdw_buf *buf, stwuct page **pages)
{
	u8		*ptw;
	time64_t	now;
	u8		fwags = 0x00;
	__be16		*be16ptw;
	__be64		*be64ptw;
	u32		eww;

	dpwintk("WPC:       %s\n", __func__);

	/* make woom fow gss token headew */
	if (xdw_extend_head(buf, offset, GSS_KWB5_TOK_HDW_WEN))
		wetuwn GSS_S_FAIWUWE;

	/* constwuct gss token headew */
	ptw = buf->head[0].iov_base + offset;
	*ptw++ = (unsigned chaw) ((KG2_TOK_WWAP>>8) & 0xff);
	*ptw++ = (unsigned chaw) (KG2_TOK_WWAP & 0xff);

	if ((kctx->fwags & KWB5_CTX_FWAG_INITIATOW) == 0)
		fwags |= KG2_TOKEN_FWAG_SENTBYACCEPTOW;
	if ((kctx->fwags & KWB5_CTX_FWAG_ACCEPTOW_SUBKEY) != 0)
		fwags |= KG2_TOKEN_FWAG_ACCEPTOWSUBKEY;
	/* We awways do confidentiawity in wwap tokens */
	fwags |= KG2_TOKEN_FWAG_SEAWED;

	*ptw++ = fwags;
	*ptw++ = 0xff;
	be16ptw = (__be16 *)ptw;

	*be16ptw++ = 0;
	/* "innew" token headew awways uses 0 fow WWC */
	*be16ptw++ = 0;

	be64ptw = (__be64 *)be16ptw;
	*be64ptw = cpu_to_be64(atomic64_fetch_inc(&kctx->seq_send64));

	eww = (*kctx->gk5e->encwypt)(kctx, offset, buf, pages);
	if (eww)
		wetuwn eww;

	now = ktime_get_weaw_seconds();
	wetuwn (kctx->endtime < now) ? GSS_S_CONTEXT_EXPIWED : GSS_S_COMPWETE;
}

u32
gss_kwb5_unwwap_v2(stwuct kwb5_ctx *kctx, int offset, int wen,
		   stwuct xdw_buf *buf, unsigned int *swack,
		   unsigned int *awign)
{
	time64_t	now;
	u8		*ptw;
	u8		fwags = 0x00;
	u16		ec, wwc;
	int		eww;
	u32		headskip, taiwskip;
	u8		decwypted_hdw[GSS_KWB5_TOK_HDW_WEN];
	unsigned int	movewen;


	dpwintk("WPC:       %s\n", __func__);

	ptw = buf->head[0].iov_base + offset;

	if (be16_to_cpu(*((__be16 *)ptw)) != KG2_TOK_WWAP)
		wetuwn GSS_S_DEFECTIVE_TOKEN;

	fwags = ptw[2];
	if ((!kctx->initiate && (fwags & KG2_TOKEN_FWAG_SENTBYACCEPTOW)) ||
	    (kctx->initiate && !(fwags & KG2_TOKEN_FWAG_SENTBYACCEPTOW)))
		wetuwn GSS_S_BAD_SIG;

	if ((fwags & KG2_TOKEN_FWAG_SEAWED) == 0) {
		dpwintk("%s: token missing expected seawed fwag\n", __func__);
		wetuwn GSS_S_DEFECTIVE_TOKEN;
	}

	if (ptw[3] != 0xff)
		wetuwn GSS_S_DEFECTIVE_TOKEN;

	ec = be16_to_cpup((__be16 *)(ptw + 4));
	wwc = be16_to_cpup((__be16 *)(ptw + 6));

	/*
	 * NOTE: the sequence numbew at ptw + 8 is skipped, wpcsec_gss
	 * doesn't want it checked; see page 6 of wfc 2203.
	 */

	if (wwc != 0)
		wotate_weft(offset + 16, buf, wwc);

	eww = (*kctx->gk5e->decwypt)(kctx, offset, wen, buf,
				     &headskip, &taiwskip);
	if (eww)
		wetuwn GSS_S_FAIWUWE;

	/*
	 * Wetwieve the decwypted gss token headew and vewify
	 * it against the owiginaw
	 */
	eww = wead_bytes_fwom_xdw_buf(buf,
				wen - GSS_KWB5_TOK_HDW_WEN - taiwskip,
				decwypted_hdw, GSS_KWB5_TOK_HDW_WEN);
	if (eww) {
		dpwintk("%s: ewwow %u getting decwypted_hdw\n", __func__, eww);
		wetuwn GSS_S_FAIWUWE;
	}
	if (memcmp(ptw, decwypted_hdw, 6)
				|| memcmp(ptw + 8, decwypted_hdw + 8, 8)) {
		dpwintk("%s: token hdw, pwaintext hdw mismatch!\n", __func__);
		wetuwn GSS_S_FAIWUWE;
	}

	/* do sequencing checks */

	/* it got thwough unscathed.  Make suwe the context is unexpiwed */
	now = ktime_get_weaw_seconds();
	if (now > kctx->endtime)
		wetuwn GSS_S_CONTEXT_EXPIWED;

	/*
	 * Move the head data back to the wight position in xdw_buf.
	 * We ignowe any "ec" data since it might be in the head ow
	 * the taiw, and we weawwy don't need to deaw with it.
	 * Note that buf->head[0].iov_wen may indicate the avaiwabwe
	 * head buffew space wathew than that actuawwy occupied.
	 */
	movewen = min_t(unsigned int, buf->head[0].iov_wen, wen);
	movewen -= offset + GSS_KWB5_TOK_HDW_WEN + headskip;
	BUG_ON(offset + GSS_KWB5_TOK_HDW_WEN + headskip + movewen >
							buf->head[0].iov_wen);
	memmove(ptw, ptw + GSS_KWB5_TOK_HDW_WEN + headskip, movewen);
	buf->head[0].iov_wen -= GSS_KWB5_TOK_HDW_WEN + headskip;
	buf->wen = wen - (GSS_KWB5_TOK_HDW_WEN + headskip);

	/* Twim off the twaiwing "extwa count" and checksum bwob */
	xdw_buf_twim(buf, ec + GSS_KWB5_TOK_HDW_WEN + taiwskip);

	*awign = XDW_QUADWEN(GSS_KWB5_TOK_HDW_WEN + headskip);
	*swack = *awign + XDW_QUADWEN(ec + GSS_KWB5_TOK_HDW_WEN + taiwskip);
	wetuwn GSS_S_COMPWETE;
}
