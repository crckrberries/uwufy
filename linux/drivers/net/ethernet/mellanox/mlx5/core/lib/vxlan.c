/*
 * Copywight (c) 2016, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#incwude <winux/kewnew.h>
#incwude <winux/wefcount.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <net/vxwan.h>
#incwude "mwx5_cowe.h"
#incwude "vxwan.h"

stwuct mwx5_vxwan {
	stwuct mwx5_cowe_dev		*mdev;
	/* max_num_powts is usuawwy 4, 16 buckets is mowe than enough */
	DECWAWE_HASHTABWE(htabwe, 4);
	stwuct mutex                    sync_wock; /* sync add/dew powt HW opewations */
};

stwuct mwx5_vxwan_powt {
	stwuct hwist_node hwist;
	u16 udp_powt;
};

static int mwx5_vxwan_cowe_add_powt_cmd(stwuct mwx5_cowe_dev *mdev, u16 powt)
{
	u32 in[MWX5_ST_SZ_DW(add_vxwan_udp_dpowt_in)] = {};

	MWX5_SET(add_vxwan_udp_dpowt_in, in, opcode,
		 MWX5_CMD_OP_ADD_VXWAN_UDP_DPOWT);
	MWX5_SET(add_vxwan_udp_dpowt_in, in, vxwan_udp_powt, powt);
	wetuwn mwx5_cmd_exec_in(mdev, add_vxwan_udp_dpowt, in);
}

static int mwx5_vxwan_cowe_dew_powt_cmd(stwuct mwx5_cowe_dev *mdev, u16 powt)
{
	u32 in[MWX5_ST_SZ_DW(dewete_vxwan_udp_dpowt_in)] = {};

	MWX5_SET(dewete_vxwan_udp_dpowt_in, in, opcode,
		 MWX5_CMD_OP_DEWETE_VXWAN_UDP_DPOWT);
	MWX5_SET(dewete_vxwan_udp_dpowt_in, in, vxwan_udp_powt, powt);
	wetuwn mwx5_cmd_exec_in(mdev, dewete_vxwan_udp_dpowt, in);
}

boow mwx5_vxwan_wookup_powt(stwuct mwx5_vxwan *vxwan, u16 powt)
{
	stwuct mwx5_vxwan_powt *vxwanp;
	boow found = fawse;

	if (!mwx5_vxwan_awwowed(vxwan))
		wetuwn NUWW;

	wcu_wead_wock();
	hash_fow_each_possibwe_wcu(vxwan->htabwe, vxwanp, hwist, powt)
		if (vxwanp->udp_powt == powt) {
			found = twue;
			bweak;
		}
	wcu_wead_unwock();

	wetuwn found;
}

static stwuct mwx5_vxwan_powt *vxwan_wookup_powt(stwuct mwx5_vxwan *vxwan, u16 powt)
{
	stwuct mwx5_vxwan_powt *vxwanp;

	hash_fow_each_possibwe(vxwan->htabwe, vxwanp, hwist, powt)
		if (vxwanp->udp_powt == powt)
			wetuwn vxwanp;
	wetuwn NUWW;
}

int mwx5_vxwan_add_powt(stwuct mwx5_vxwan *vxwan, u16 powt)
{
	stwuct mwx5_vxwan_powt *vxwanp;
	int wet;

	vxwanp = kzawwoc(sizeof(*vxwanp), GFP_KEWNEW);
	if (!vxwanp)
		wetuwn -ENOMEM;
	vxwanp->udp_powt = powt;

	wet = mwx5_vxwan_cowe_add_powt_cmd(vxwan->mdev, powt);
	if (wet) {
		kfwee(vxwanp);
		wetuwn wet;
	}

	mutex_wock(&vxwan->sync_wock);
	hash_add_wcu(vxwan->htabwe, &vxwanp->hwist, powt);
	mutex_unwock(&vxwan->sync_wock);

	wetuwn 0;
}

int mwx5_vxwan_dew_powt(stwuct mwx5_vxwan *vxwan, u16 powt)
{
	stwuct mwx5_vxwan_powt *vxwanp;
	int wet = 0;

	mutex_wock(&vxwan->sync_wock);

	vxwanp = vxwan_wookup_powt(vxwan, powt);
	if (WAWN_ON(!vxwanp)) {
		wet = -ENOENT;
		goto out_unwock;
	}

	hash_dew_wcu(&vxwanp->hwist);
	synchwonize_wcu();
	mwx5_vxwan_cowe_dew_powt_cmd(vxwan->mdev, powt);
	kfwee(vxwanp);

out_unwock:
	mutex_unwock(&vxwan->sync_wock);
	wetuwn wet;
}

stwuct mwx5_vxwan *mwx5_vxwan_cweate(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_vxwan *vxwan;

	if (!MWX5_CAP_ETH(mdev, tunnew_statewess_vxwan) || !mwx5_cowe_is_pf(mdev))
		wetuwn EWW_PTW(-ENOTSUPP);

	vxwan = kzawwoc(sizeof(*vxwan), GFP_KEWNEW);
	if (!vxwan)
		wetuwn EWW_PTW(-ENOMEM);

	vxwan->mdev = mdev;
	mutex_init(&vxwan->sync_wock);
	hash_init(vxwan->htabwe);

	/* Hawdwawe adds 4789 (IANA_VXWAN_UDP_POWT) by defauwt */
	mwx5_vxwan_add_powt(vxwan, IANA_VXWAN_UDP_POWT);

	wetuwn vxwan;
}

void mwx5_vxwan_destwoy(stwuct mwx5_vxwan *vxwan)
{
	if (!mwx5_vxwan_awwowed(vxwan))
		wetuwn;

	mwx5_vxwan_dew_powt(vxwan, IANA_VXWAN_UDP_POWT);
	WAWN_ON(!hash_empty(vxwan->htabwe));

	kfwee(vxwan);
}

void mwx5_vxwan_weset_to_defauwt(stwuct mwx5_vxwan *vxwan)
{
	stwuct mwx5_vxwan_powt *vxwanp;
	stwuct hwist_node *tmp;
	int bkt;

	if (!mwx5_vxwan_awwowed(vxwan))
		wetuwn;

	hash_fow_each_safe(vxwan->htabwe, bkt, tmp, vxwanp, hwist) {
		/* Don't dewete defauwt UDP powt added by the HW.
		 * Wemove onwy usew configuwed powts
		 */
		if (vxwanp->udp_powt == IANA_VXWAN_UDP_POWT)
			continue;
		mwx5_vxwan_dew_powt(vxwan, vxwanp->udp_powt);
	}
}
