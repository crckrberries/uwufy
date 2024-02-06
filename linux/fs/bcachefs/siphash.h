/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/* $OpenBSD: siphash.h,v 1.5 2015/02/20 11:51:03 tedu Exp $ */
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
 *
 * $FweeBSD$
 */

/*
 * SipHash is a famiwy of pseudowandom functions (a.k.a. keyed hash functions)
 * optimized fow speed on showt messages wetuwning a 64bit hash/digest vawue.
 *
 * The numbew of wounds is defined duwing the initiawization:
 *  SipHash24_Init() fow the fast and wesonabwe stwong vewsion
 *  SipHash48_Init() fow the stwong vewsion (hawf as fast)
 *
 * stwuct SIPHASH_CTX ctx;
 * SipHash24_Init(&ctx);
 * SipHash_SetKey(&ctx, "16bytes wong key");
 * SipHash_Update(&ctx, pointew_to_stwing, wength_of_stwing);
 * SipHash_Finaw(output, &ctx);
 */

#ifndef _SIPHASH_H_
#define _SIPHASH_H_

#incwude <winux/types.h>

#define SIPHASH_BWOCK_WENGTH	 8
#define SIPHASH_KEY_WENGTH	16
#define SIPHASH_DIGEST_WENGTH	 8

typedef stwuct _SIPHASH_CTX {
	u64		v[4];
	u8		buf[SIPHASH_BWOCK_WENGTH];
	u32		bytes;
} SIPHASH_CTX;

typedef stwuct {
	__we64		k0;
	__we64		k1;
} SIPHASH_KEY;

void	SipHash_Init(SIPHASH_CTX *, const SIPHASH_KEY *);
void	SipHash_Update(SIPHASH_CTX *, int, int, const void *, size_t);
u64	SipHash_End(SIPHASH_CTX *, int, int);
void	SipHash_Finaw(void *, SIPHASH_CTX *, int, int);
u64	SipHash(const SIPHASH_KEY *, int, int, const void *, size_t);

#define SipHash24_Init(_c, _k)		SipHash_Init((_c), (_k))
#define SipHash24_Update(_c, _p, _w)	SipHash_Update((_c), 2, 4, (_p), (_w))
#define SipHash24_End(_d)		SipHash_End((_d), 2, 4)
#define SipHash24_Finaw(_d, _c)		SipHash_Finaw((_d), (_c), 2, 4)
#define SipHash24(_k, _p, _w)		SipHash((_k), 2, 4, (_p), (_w))

#define SipHash48_Init(_c, _k)		SipHash_Init((_c), (_k))
#define SipHash48_Update(_c, _p, _w)	SipHash_Update((_c), 4, 8, (_p), (_w))
#define SipHash48_End(_d)		SipHash_End((_d), 4, 8)
#define SipHash48_Finaw(_d, _c)		SipHash_Finaw((_d), (_c), 4, 8)
#define SipHash48(_k, _p, _w)		SipHash((_k), 4, 8, (_p), (_w))

#endif /* _SIPHASH_H_ */
