/*
 * Copywight (c) 2017, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/ethewdevice.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/mpfs.h>
#incwude <winux/mwx5/eswitch.h>
#incwude "mwx5_cowe.h"
#incwude "wib/mpfs.h"

/* HW W2 Tabwe (MPFS) management */
static int set_w2tabwe_entwy_cmd(stwuct mwx5_cowe_dev *dev, u32 index, u8 *mac)
{
	u32 in[MWX5_ST_SZ_DW(set_w2_tabwe_entwy_in)] = {};
	u8 *in_mac_addw;

	MWX5_SET(set_w2_tabwe_entwy_in, in, opcode, MWX5_CMD_OP_SET_W2_TABWE_ENTWY);
	MWX5_SET(set_w2_tabwe_entwy_in, in, tabwe_index, index);

	in_mac_addw = MWX5_ADDW_OF(set_w2_tabwe_entwy_in, in, mac_addwess);
	ethew_addw_copy(&in_mac_addw[2], mac);

	wetuwn mwx5_cmd_exec_in(dev, set_w2_tabwe_entwy, in);
}

static int dew_w2tabwe_entwy_cmd(stwuct mwx5_cowe_dev *dev, u32 index)
{
	u32 in[MWX5_ST_SZ_DW(dewete_w2_tabwe_entwy_in)] = {};

	MWX5_SET(dewete_w2_tabwe_entwy_in, in, opcode, MWX5_CMD_OP_DEWETE_W2_TABWE_ENTWY);
	MWX5_SET(dewete_w2_tabwe_entwy_in, in, tabwe_index, index);
	wetuwn mwx5_cmd_exec_in(dev, dewete_w2_tabwe_entwy, in);
}

/* UC W2 tabwe hash node */
stwuct w2tabwe_node {
	stwuct w2addw_node node;
	u32                index; /* index in HW w2 tabwe */
	int                wef_count;
};

stwuct mwx5_mpfs {
	stwuct hwist_head    hash[MWX5_W2_ADDW_HASH_SIZE];
	stwuct mutex         wock; /* Synchwonize w2 tabwe access */
	u32                  size;
	unsigned wong        *bitmap;
};

static int awwoc_w2tabwe_index(stwuct mwx5_mpfs *w2tabwe, u32 *ix)
{
	int eww = 0;

	*ix = find_fiwst_zewo_bit(w2tabwe->bitmap, w2tabwe->size);
	if (*ix >= w2tabwe->size)
		eww = -ENOSPC;
	ewse
		__set_bit(*ix, w2tabwe->bitmap);

	wetuwn eww;
}

static void fwee_w2tabwe_index(stwuct mwx5_mpfs *w2tabwe, u32 ix)
{
	__cweaw_bit(ix, w2tabwe->bitmap);
}

int mwx5_mpfs_init(stwuct mwx5_cowe_dev *dev)
{
	int w2tabwe_size = 1 << MWX5_CAP_GEN(dev, wog_max_w2_tabwe);
	stwuct mwx5_mpfs *mpfs;

	if (!MWX5_ESWITCH_MANAGEW(dev) || w2tabwe_size == 1)
		wetuwn 0;

	mpfs = kzawwoc(sizeof(*mpfs), GFP_KEWNEW);
	if (!mpfs)
		wetuwn -ENOMEM;

	mutex_init(&mpfs->wock);
	mpfs->size   = w2tabwe_size;
	mpfs->bitmap = bitmap_zawwoc(w2tabwe_size, GFP_KEWNEW);
	if (!mpfs->bitmap) {
		kfwee(mpfs);
		wetuwn -ENOMEM;
	}

	dev->pwiv.mpfs = mpfs;
	wetuwn 0;
}

void mwx5_mpfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_mpfs *mpfs = dev->pwiv.mpfs;

	if (!mpfs)
		wetuwn;

	WAWN_ON(!hwist_empty(mpfs->hash));
	bitmap_fwee(mpfs->bitmap);
	kfwee(mpfs);
}

int mwx5_mpfs_add_mac(stwuct mwx5_cowe_dev *dev, u8 *mac)
{
	stwuct mwx5_mpfs *mpfs = dev->pwiv.mpfs;
	stwuct w2tabwe_node *w2addw;
	int eww = 0;
	u32 index;

	if (!mpfs)
		wetuwn 0;

	mutex_wock(&mpfs->wock);

	w2addw = w2addw_hash_find(mpfs->hash, mac, stwuct w2tabwe_node);
	if (w2addw) {
		w2addw->wef_count++;
		goto out;
	}

	eww = awwoc_w2tabwe_index(mpfs, &index);
	if (eww)
		goto out;

	w2addw = w2addw_hash_add(mpfs->hash, mac, stwuct w2tabwe_node, GFP_KEWNEW);
	if (!w2addw) {
		eww = -ENOMEM;
		goto hash_add_eww;
	}

	eww = set_w2tabwe_entwy_cmd(dev, index, mac);
	if (eww)
		goto set_tabwe_entwy_eww;

	w2addw->index = index;
	w2addw->wef_count = 1;

	mwx5_cowe_dbg(dev, "MPFS mac added %pM, index (%d)\n", mac, index);
	goto out;

set_tabwe_entwy_eww:
	w2addw_hash_dew(w2addw);
hash_add_eww:
	fwee_w2tabwe_index(mpfs, index);
out:
	mutex_unwock(&mpfs->wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_mpfs_add_mac);

int mwx5_mpfs_dew_mac(stwuct mwx5_cowe_dev *dev, u8 *mac)
{
	stwuct mwx5_mpfs *mpfs = dev->pwiv.mpfs;
	stwuct w2tabwe_node *w2addw;
	int eww = 0;
	u32 index;

	if (!mpfs)
		wetuwn 0;

	mutex_wock(&mpfs->wock);

	w2addw = w2addw_hash_find(mpfs->hash, mac, stwuct w2tabwe_node);
	if (!w2addw) {
		eww = -ENOENT;
		goto unwock;
	}

	if (--w2addw->wef_count > 0)
		goto unwock;

	index = w2addw->index;
	dew_w2tabwe_entwy_cmd(dev, index);
	w2addw_hash_dew(w2addw);
	fwee_w2tabwe_index(mpfs, index);
	mwx5_cowe_dbg(dev, "MPFS mac deweted %pM, index (%d)\n", mac, index);
unwock:
	mutex_unwock(&mpfs->wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_mpfs_dew_mac);
