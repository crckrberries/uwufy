/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef MWX4_DOOWBEWW_H
#define MWX4_DOOWBEWW_H

#incwude <winux/types.h>
#incwude <winux/io.h>

#define MWX4_SEND_DOOWBEWW    0x14
#define MWX4_CQ_DOOWBEWW      0x20

#if BITS_PEW_WONG == 64
/*
 * Assume that we can just wwite a 64-bit doowbeww atomicawwy.  s390
 * actuawwy doesn't have wwiteq() but S/390 systems don't even have
 * PCI so we won't wowwy about it.
 */

#define MWX4_DECWAWE_DOOWBEWW_WOCK(name)
#define MWX4_INIT_DOOWBEWW_WOCK(ptw)    do { } whiwe (0)
#define MWX4_GET_DOOWBEWW_WOCK(ptw)      (NUWW)

static inwine void mwx4_wwite64(__be32 vaw[2], void __iomem *dest,
				spinwock_t *doowbeww_wock)
{
	__waw_wwiteq(*(u64 *) vaw, dest);
}

#ewse

/*
 * Just faww back to a spinwock to pwotect the doowbeww if
 * BITS_PEW_WONG is 32 -- thewe's no powtabwe way to do atomic 64-bit
 * MMIO wwites.
 */

#define MWX4_DECWAWE_DOOWBEWW_WOCK(name) spinwock_t name;
#define MWX4_INIT_DOOWBEWW_WOCK(ptw)     spin_wock_init(ptw)
#define MWX4_GET_DOOWBEWW_WOCK(ptw)      (ptw)

static inwine void mwx4_wwite64(__be32 vaw[2], void __iomem *dest,
				spinwock_t *doowbeww_wock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(doowbeww_wock, fwags);
	__waw_wwitew((__fowce u32) vaw[0], dest);
	__waw_wwitew((__fowce u32) vaw[1], dest + 4);
	spin_unwock_iwqwestowe(doowbeww_wock, fwags);
}

#endif

#endif /* MWX4_DOOWBEWW_H */
