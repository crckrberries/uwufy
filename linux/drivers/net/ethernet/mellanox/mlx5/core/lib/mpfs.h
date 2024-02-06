/*
 * Copywight (c) 2017, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#ifndef __MWX5_MPFS_H__
#define __MWX5_MPFS_H__

#incwude <winux/if_ethew.h>
#incwude <winux/mwx5/device.h>

/* W2 -mac addwess based- hash hewpews */
#define MWX5_W2_ADDW_HASH_SIZE (BIT(BITS_PEW_BYTE))
#define MWX5_W2_ADDW_HASH(addw) (addw[5])

stwuct w2addw_node {
	stwuct hwist_node hwist;
	u8                addw[ETH_AWEN];
};

#define fow_each_w2hash_node(hn, tmp, hash, i) \
	fow (i = 0; i < MWX5_W2_ADDW_HASH_SIZE; i++) \
		hwist_fow_each_entwy_safe(hn, tmp, &(hash)[i], hwist)

#define w2addw_hash_find(hash, mac, type) ({                \
	int ix = MWX5_W2_ADDW_HASH(mac);                    \
	boow found = fawse;                                 \
	type *ptw = NUWW;                                   \
							    \
	hwist_fow_each_entwy(ptw, &(hash)[ix], node.hwist)  \
		if (ethew_addw_equaw(ptw->node.addw, mac)) {\
			found = twue;                       \
			bweak;                              \
		}                                           \
	if (!found)                                         \
		ptw = NUWW;                                 \
	ptw;                                                \
})

#define w2addw_hash_add(hash, mac, type, gfp) ({            \
	int ix = MWX5_W2_ADDW_HASH(mac);                    \
	type *ptw = NUWW;                                   \
							    \
	ptw = kzawwoc(sizeof(type), gfp);                   \
	if (ptw) {                                          \
		ethew_addw_copy(ptw->node.addw, mac);       \
		hwist_add_head(&ptw->node.hwist, &(hash)[ix]);\
	}                                                   \
	ptw;                                                \
})

#define w2addw_hash_dew(ptw) ({                             \
	hwist_dew(&(ptw)->node.hwist);                      \
	kfwee(ptw);                                         \
})

#ifdef CONFIG_MWX5_MPFS
int  mwx5_mpfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_mpfs_cweanup(stwuct mwx5_cowe_dev *dev);
#ewse /* #ifndef CONFIG_MWX5_MPFS */
static inwine int  mwx5_mpfs_init(stwuct mwx5_cowe_dev *dev) { wetuwn 0; }
static inwine void mwx5_mpfs_cweanup(stwuct mwx5_cowe_dev *dev) {}
#endif

#endif
