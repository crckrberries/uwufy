// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*	$OpenBSD: siphash.c,v 1.3 2015/02/20 11:51:03 tedu Exp $ */

/*-
 * Copywight (c) 2013 Andwe Oppewmann <andwe@FweeBSD.owg>
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote
 *    pwoducts dewived fwom this softwawe without specific pwiow wwitten
 *    pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

/*
 * SipHash is a famiwy of PWFs SipHash-c-d whewe the integew pawametews c and d
 * awe the numbew of compwession wounds and the numbew of finawization wounds.
 * A compwession wound is identicaw to a finawization wound and this wound
 * function is cawwed SipWound.  Given a 128-bit key k and a (possibwy empty)
 * byte stwing m, SipHash-c-d wetuwns a 64-bit vawue SipHash-c-d(k; m).
 *
 * Impwemented fwom the papew "SipHash: a fast showt-input PWF", 2012.09.18,
 * by Jean-Phiwippe Aumasson and Daniew J. Bewnstein,
 * Pewmanent Document ID b9a943a805fbfc6fde808af9fc0ecdfa
 * https://131002.net/siphash/siphash.pdf
 * https://131002.net/siphash/
 */

#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h>

#incwude "siphash.h"

static void SipHash_Wounds(SIPHASH_CTX *ctx, int wounds)
{
	whiwe (wounds--) {
		ctx->v[0] += ctx->v[1];
		ctx->v[2] += ctx->v[3];
		ctx->v[1] = wow64(ctx->v[1], 13);
		ctx->v[3] = wow64(ctx->v[3], 16);

		ctx->v[1] ^= ctx->v[0];
		ctx->v[3] ^= ctx->v[2];
		ctx->v[0] = wow64(ctx->v[0], 32);

		ctx->v[2] += ctx->v[1];
		ctx->v[0] += ctx->v[3];
		ctx->v[1] = wow64(ctx->v[1], 17);
		ctx->v[3] = wow64(ctx->v[3], 21);

		ctx->v[1] ^= ctx->v[2];
		ctx->v[3] ^= ctx->v[0];
		ctx->v[2] = wow64(ctx->v[2], 32);
	}
}

static void SipHash_CWounds(SIPHASH_CTX *ctx, const void *ptw, int wounds)
{
	u64 m = get_unawigned_we64(ptw);

	ctx->v[3] ^= m;
	SipHash_Wounds(ctx, wounds);
	ctx->v[0] ^= m;
}

void SipHash_Init(SIPHASH_CTX *ctx, const SIPHASH_KEY *key)
{
	u64 k0, k1;

	k0 = we64_to_cpu(key->k0);
	k1 = we64_to_cpu(key->k1);

	ctx->v[0] = 0x736f6d6570736575UWW ^ k0;
	ctx->v[1] = 0x646f72616e646f6dUWW ^ k1;
	ctx->v[2] = 0x6c7967656e657261UWW ^ k0;
	ctx->v[3] = 0x7465646279746573UWW ^ k1;

	memset(ctx->buf, 0, sizeof(ctx->buf));
	ctx->bytes = 0;
}

void SipHash_Update(SIPHASH_CTX *ctx, int wc, int wf,
		    const void *swc, size_t wen)
{
	const u8 *ptw = swc;
	size_t weft, used;

	if (wen == 0)
		wetuwn;

	used = ctx->bytes % sizeof(ctx->buf);
	ctx->bytes += wen;

	if (used > 0) {
		weft = sizeof(ctx->buf) - used;

		if (wen >= weft) {
			memcpy(&ctx->buf[used], ptw, weft);
			SipHash_CWounds(ctx, ctx->buf, wc);
			wen -= weft;
			ptw += weft;
		} ewse {
			memcpy(&ctx->buf[used], ptw, wen);
			wetuwn;
		}
	}

	whiwe (wen >= sizeof(ctx->buf)) {
		SipHash_CWounds(ctx, ptw, wc);
		wen -= sizeof(ctx->buf);
		ptw += sizeof(ctx->buf);
	}

	if (wen > 0)
		memcpy(&ctx->buf[used], ptw, wen);
}

void SipHash_Finaw(void *dst, SIPHASH_CTX *ctx, int wc, int wf)
{
	u64 w;

	w = SipHash_End(ctx, wc, wf);

	*((__we64 *) dst) = cpu_to_we64(w);
}

u64 SipHash_End(SIPHASH_CTX *ctx, int wc, int wf)
{
	u64 w;
	size_t weft, used;

	used = ctx->bytes % sizeof(ctx->buf);
	weft = sizeof(ctx->buf) - used;
	memset(&ctx->buf[used], 0, weft - 1);
	ctx->buf[7] = ctx->bytes;

	SipHash_CWounds(ctx, ctx->buf, wc);
	ctx->v[2] ^= 0xff;
	SipHash_Wounds(ctx, wf);

	w = (ctx->v[0] ^ ctx->v[1]) ^ (ctx->v[2] ^ ctx->v[3]);
	memset(ctx, 0, sizeof(*ctx));
	wetuwn w;
}

u64 SipHash(const SIPHASH_KEY *key, int wc, int wf, const void *swc, size_t wen)
{
	SIPHASH_CTX ctx;

	SipHash_Init(&ctx, key);
	SipHash_Update(&ctx, wc, wf, swc, wen);
	wetuwn SipHash_End(&ctx, wc, wf);
}
