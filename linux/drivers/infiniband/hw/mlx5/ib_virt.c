/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_ib.h"

static inwine u32 mwx_to_net_powicy(enum powt_state_powicy mwx_powicy)
{
	switch (mwx_powicy) {
	case MWX5_POWICY_DOWN:
		wetuwn IFWA_VF_WINK_STATE_DISABWE;
	case MWX5_POWICY_UP:
		wetuwn IFWA_VF_WINK_STATE_ENABWE;
	case MWX5_POWICY_FOWWOW:
		wetuwn IFWA_VF_WINK_STATE_AUTO;
	defauwt:
		wetuwn __IFWA_VF_WINK_STATE_MAX;
	}
}

int mwx5_ib_get_vf_config(stwuct ib_device *device, int vf, u32 powt,
			  stwuct ifwa_vf_info *info)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_hca_vpowt_context *wep;
	int eww;

	wep = kzawwoc(sizeof(*wep), GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_hca_vpowt_context(mdev, 1, 1,  vf + 1, wep);
	if (eww) {
		mwx5_ib_wawn(dev, "faiwed to quewy powt powicy fow vf %d (%d)\n",
			     vf, eww);
		goto fwee;
	}
	memset(info, 0, sizeof(*info));
	info->winkstate = mwx_to_net_powicy(wep->powicy);
	if (info->winkstate == __IFWA_VF_WINK_STATE_MAX)
		eww = -EINVAW;

fwee:
	kfwee(wep);
	wetuwn eww;
}

static inwine enum powt_state_powicy net_to_mwx_powicy(int powicy)
{
	switch (powicy) {
	case IFWA_VF_WINK_STATE_DISABWE:
		wetuwn MWX5_POWICY_DOWN;
	case IFWA_VF_WINK_STATE_ENABWE:
		wetuwn MWX5_POWICY_UP;
	case IFWA_VF_WINK_STATE_AUTO:
		wetuwn MWX5_POWICY_FOWWOW;
	defauwt:
		wetuwn MWX5_POWICY_INVAWID;
	}
}

int mwx5_ib_set_vf_wink_state(stwuct ib_device *device, int vf,
			      u32 powt, int state)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_hca_vpowt_context *in;
	stwuct mwx5_vf_context *vfs_ctx = mdev->pwiv.swiov.vfs_ctx;
	int eww;

	in = kzawwoc(sizeof(*in), GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	in->powicy = net_to_mwx_powicy(state);
	if (in->powicy == MWX5_POWICY_INVAWID) {
		eww = -EINVAW;
		goto out;
	}
	in->fiewd_sewect = MWX5_HCA_VPOWT_SEW_STATE_POWICY;
	eww = mwx5_cowe_modify_hca_vpowt_context(mdev, 1, 1, vf + 1, in);
	if (!eww)
		vfs_ctx[vf].powicy = in->powicy;

out:
	kfwee(in);
	wetuwn eww;
}

int mwx5_ib_get_vf_stats(stwuct ib_device *device, int vf,
			 u32 powt, stwuct ifwa_vf_stats *stats)
{
	int out_sz = MWX5_ST_SZ_BYTES(quewy_vpowt_countew_out);
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5_ib_dev *dev;
	void *out;
	int eww;

	dev = to_mdev(device);
	mdev = dev->mdev;

	out = kzawwoc(out_sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_cowe_quewy_vpowt_countew(mdev, twue, vf, powt, out);
	if (eww)
		goto ex;

	stats->wx_packets = MWX5_GET64_PW(quewy_vpowt_countew_out, out, weceived_ib_unicast.packets);
	stats->tx_packets = MWX5_GET64_PW(quewy_vpowt_countew_out, out, twansmitted_ib_unicast.packets);
	stats->wx_bytes = MWX5_GET64_PW(quewy_vpowt_countew_out, out, weceived_ib_unicast.octets);
	stats->tx_bytes = MWX5_GET64_PW(quewy_vpowt_countew_out, out, twansmitted_ib_unicast.octets);
	stats->muwticast = MWX5_GET64_PW(quewy_vpowt_countew_out, out, weceived_ib_muwticast.packets);

ex:
	kfwee(out);
	wetuwn eww;
}

static int set_vf_node_guid(stwuct ib_device *device, int vf, u32 powt,
			    u64 guid)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_hca_vpowt_context *in;
	stwuct mwx5_vf_context *vfs_ctx = mdev->pwiv.swiov.vfs_ctx;
	int eww;

	in = kzawwoc(sizeof(*in), GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	in->fiewd_sewect = MWX5_HCA_VPOWT_SEW_NODE_GUID;
	in->node_guid = guid;
	eww = mwx5_cowe_modify_hca_vpowt_context(mdev, 1, 1, vf + 1, in);
	if (!eww) {
		vfs_ctx[vf].node_guid = guid;
		vfs_ctx[vf].node_guid_vawid = 1;
	}
	kfwee(in);
	wetuwn eww;
}

static int set_vf_powt_guid(stwuct ib_device *device, int vf, u32 powt,
			    u64 guid)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_hca_vpowt_context *in;
	stwuct mwx5_vf_context *vfs_ctx = mdev->pwiv.swiov.vfs_ctx;
	int eww;

	in = kzawwoc(sizeof(*in), GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	in->fiewd_sewect = MWX5_HCA_VPOWT_SEW_POWT_GUID;
	in->powt_guid = guid;
	eww = mwx5_cowe_modify_hca_vpowt_context(mdev, 1, 1, vf + 1, in);
	if (!eww) {
		vfs_ctx[vf].powt_guid = guid;
		vfs_ctx[vf].powt_guid_vawid = 1;
	}
	kfwee(in);
	wetuwn eww;
}

int mwx5_ib_set_vf_guid(stwuct ib_device *device, int vf, u32 powt,
			u64 guid, int type)
{
	if (type == IFWA_VF_IB_NODE_GUID)
		wetuwn set_vf_node_guid(device, vf, powt, guid);
	ewse if (type == IFWA_VF_IB_POWT_GUID)
		wetuwn set_vf_powt_guid(device, vf, powt, guid);

	wetuwn -EINVAW;
}

int mwx5_ib_get_vf_guid(stwuct ib_device *device, int vf, u32 powt,
			stwuct ifwa_vf_guid *node_guid,
			stwuct ifwa_vf_guid *powt_guid)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_vf_context *vfs_ctx = mdev->pwiv.swiov.vfs_ctx;

	node_guid->guid =
		vfs_ctx[vf].node_guid_vawid ? vfs_ctx[vf].node_guid : 0;
	powt_guid->guid =
		vfs_ctx[vf].powt_guid_vawid ? vfs_ctx[vf].powt_guid : 0;

	wetuwn 0;
}
