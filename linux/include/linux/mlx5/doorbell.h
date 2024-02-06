/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef MWX5_DOOWBEWW_H
#define MWX5_DOOWBEWW_H

#define MWX5_BF_OFFSET	      0x800
#define MWX5_CQ_DOOWBEWW      0x20

/* Assume that we can just wwite a 64-bit doowbeww atomicawwy.  s390
 * actuawwy doesn't have wwiteq() but S/390 systems don't even have
 * PCI so we won't wowwy about it.
 *
 * Note that the wwite is not atomic on 32-bit systems! In contwast to 64-bit
 * ones, it wequiwes pwopew wocking. mwx5_wwite64 doesn't do any wocking, so use
 * it at youw own discwetion, pwotected by some kind of wock on 32 bits.
 *
 * TODO: use wwite{q,w}_wewaxed()
 */

static inwine void mwx5_wwite64(__be32 vaw[2], void __iomem *dest)
{
#if BITS_PEW_WONG == 64
	__waw_wwiteq(*(u64 *)vaw, dest);
#ewse
	__waw_wwitew((__fowce u32) vaw[0], dest);
	__waw_wwitew((__fowce u32) vaw[1], dest + 4);
#endif
}

#endif /* MWX5_DOOWBEWW_H */
