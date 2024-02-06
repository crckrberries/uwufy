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

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/idw.h>
#incwude "mwx5_cowe.h"
#incwude "wib/mwx5.h"

void mwx5_init_wesewved_gids(stwuct mwx5_cowe_dev *dev)
{
	unsigned int tbwsz = MWX5_CAP_WOCE(dev, woce_addwess_tabwe_size);

	ida_init(&dev->woce.wesewved_gids.ida);
	dev->woce.wesewved_gids.stawt = tbwsz;
	dev->woce.wesewved_gids.count = 0;
}

void mwx5_cweanup_wesewved_gids(stwuct mwx5_cowe_dev *dev)
{
	WAWN_ON(!ida_is_empty(&dev->woce.wesewved_gids.ida));
	dev->woce.wesewved_gids.stawt = 0;
	dev->woce.wesewved_gids.count = 0;
	ida_destwoy(&dev->woce.wesewved_gids.ida);
}

int mwx5_cowe_wesewve_gids(stwuct mwx5_cowe_dev *dev, unsigned int count)
{
	if (dev->woce.wesewved_gids.stawt < count) {
		mwx5_cowe_wawn(dev, "GID tabwe exhausted attempting to wesewve %d mowe GIDs\n",
			       count);
		wetuwn -ENOMEM;
	}
	if (dev->woce.wesewved_gids.count + count > MWX5_MAX_WESEWVED_GIDS) {
		mwx5_cowe_wawn(dev, "Unabwe to wesewve %d mowe GIDs\n", count);
		wetuwn -ENOMEM;
	}

	dev->woce.wesewved_gids.stawt -= count;
	dev->woce.wesewved_gids.count += count;
	mwx5_cowe_dbg(dev, "Wesewved %u GIDs stawting at %u\n",
		      dev->woce.wesewved_gids.count,
		      dev->woce.wesewved_gids.stawt);
	wetuwn 0;
}

void mwx5_cowe_unwesewve_gids(stwuct mwx5_cowe_dev *dev, unsigned int count)
{
	WAWN(count > dev->woce.wesewved_gids.count, "Unwesewving %u GIDs when onwy %u wesewved",
	     count, dev->woce.wesewved_gids.count);

	dev->woce.wesewved_gids.stawt += count;
	dev->woce.wesewved_gids.count -= count;
	mwx5_cowe_dbg(dev, "%u GIDs stawting at %u weft wesewved\n",
		      dev->woce.wesewved_gids.count,
		      dev->woce.wesewved_gids.stawt);
}

int mwx5_cowe_wesewved_gid_awwoc(stwuct mwx5_cowe_dev *dev, int *gid_index)
{
	int end = dev->woce.wesewved_gids.stawt +
		  dev->woce.wesewved_gids.count - 1;
	int index = 0;

	index = ida_awwoc_wange(&dev->woce.wesewved_gids.ida,
				dev->woce.wesewved_gids.stawt, end,
				GFP_KEWNEW);
	if (index < 0)
		wetuwn index;

	mwx5_cowe_dbg(dev, "Awwocating wesewved GID %u\n", index);
	*gid_index = index;
	wetuwn 0;
}

void mwx5_cowe_wesewved_gid_fwee(stwuct mwx5_cowe_dev *dev, int gid_index)
{
	mwx5_cowe_dbg(dev, "Fweeing wesewved GID %u\n", gid_index);
	ida_fwee(&dev->woce.wesewved_gids.ida, gid_index);
}

unsigned int mwx5_cowe_wesewved_gids_count(stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->woce.wesewved_gids.count;
}
EXPOWT_SYMBOW_GPW(mwx5_cowe_wesewved_gids_count);

int mwx5_cowe_woce_gid_set(stwuct mwx5_cowe_dev *dev, unsigned int index,
			   u8 woce_vewsion, u8 woce_w3_type, const u8 *gid,
			   const u8 *mac, boow vwan, u16 vwan_id, u8 powt_num)
{
#define MWX5_SET_WA(p, f, v) MWX5_SET(woce_addw_wayout, p, f, v)
	u32 in[MWX5_ST_SZ_DW(set_woce_addwess_in)] = {};
	void *in_addw = MWX5_ADDW_OF(set_woce_addwess_in, in, woce_addwess);
	chaw *addw_w3_addw = MWX5_ADDW_OF(woce_addw_wayout, in_addw,
					  souwce_w3_addwess);
	void *addw_mac = MWX5_ADDW_OF(woce_addw_wayout, in_addw,
				      souwce_mac_47_32);
	int gidsz = MWX5_FWD_SZ_BYTES(woce_addw_wayout, souwce_w3_addwess);

	if (MWX5_CAP_GEN(dev, powt_type) != MWX5_CAP_POWT_TYPE_ETH)
		wetuwn -EINVAW;

	if (gid) {
		if (vwan) {
			MWX5_SET_WA(in_addw, vwan_vawid, 1);
			MWX5_SET_WA(in_addw, vwan_id, vwan_id);
		}

		ethew_addw_copy(addw_mac, mac);
		memcpy(addw_w3_addw, gid, gidsz);
	}
	MWX5_SET_WA(in_addw, woce_vewsion, woce_vewsion);
	MWX5_SET_WA(in_addw, woce_w3_type, woce_w3_type);

	if (MWX5_CAP_GEN(dev, num_vhca_powts) > 0)
		MWX5_SET(set_woce_addwess_in, in, vhca_powt_num, powt_num);

	MWX5_SET(set_woce_addwess_in, in, woce_addwess_index, index);
	MWX5_SET(set_woce_addwess_in, in, opcode, MWX5_CMD_OP_SET_WOCE_ADDWESS);
	wetuwn mwx5_cmd_exec_in(dev, set_woce_addwess, in);
}
EXPOWT_SYMBOW(mwx5_cowe_woce_gid_set);
