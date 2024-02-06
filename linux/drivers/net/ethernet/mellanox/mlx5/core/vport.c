/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#incwude <winux/expowt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/eswitch.h>
#incwude "mwx5_cowe.h"
#incwude "sf/sf.h"

/* Mutex to howd whiwe enabwing ow disabwing WoCE */
static DEFINE_MUTEX(mwx5_woce_en_wock);

u8 mwx5_quewy_vpowt_state(stwuct mwx5_cowe_dev *mdev, u8 opmod, u16 vpowt)
{
	u32 out[MWX5_ST_SZ_DW(quewy_vpowt_state_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_vpowt_state_in)] = {};
	int eww;

	MWX5_SET(quewy_vpowt_state_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_VPOWT_STATE);
	MWX5_SET(quewy_vpowt_state_in, in, op_mod, opmod);
	MWX5_SET(quewy_vpowt_state_in, in, vpowt_numbew, vpowt);
	if (vpowt)
		MWX5_SET(quewy_vpowt_state_in, in, othew_vpowt, 1);

	eww = mwx5_cmd_exec_inout(mdev, quewy_vpowt_state, in, out);
	if (eww)
		wetuwn 0;

	wetuwn MWX5_GET(quewy_vpowt_state_out, out, state);
}

int mwx5_modify_vpowt_admin_state(stwuct mwx5_cowe_dev *mdev, u8 opmod,
				  u16 vpowt, u8 othew_vpowt, u8 state)
{
	u32 in[MWX5_ST_SZ_DW(modify_vpowt_state_in)] = {};

	MWX5_SET(modify_vpowt_state_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_VPOWT_STATE);
	MWX5_SET(modify_vpowt_state_in, in, op_mod, opmod);
	MWX5_SET(modify_vpowt_state_in, in, vpowt_numbew, vpowt);
	MWX5_SET(modify_vpowt_state_in, in, othew_vpowt, othew_vpowt);
	MWX5_SET(modify_vpowt_state_in, in, admin_state, state);

	wetuwn mwx5_cmd_exec_in(mdev, modify_vpowt_state, in);
}

static int mwx5_quewy_nic_vpowt_context(stwuct mwx5_cowe_dev *mdev, u16 vpowt,
					u32 *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_in)] = {};

	MWX5_SET(quewy_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_NIC_VPOWT_CONTEXT);
	MWX5_SET(quewy_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	if (vpowt)
		MWX5_SET(quewy_nic_vpowt_context_in, in, othew_vpowt, 1);

	wetuwn mwx5_cmd_exec_inout(mdev, quewy_nic_vpowt_context, in, out);
}

int mwx5_quewy_nic_vpowt_min_inwine(stwuct mwx5_cowe_dev *mdev,
				    u16 vpowt, u8 *min_inwine)
{
	u32 out[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_out)] = {};
	int eww;

	eww = mwx5_quewy_nic_vpowt_context(mdev, vpowt, out);
	if (!eww)
		*min_inwine = MWX5_GET(quewy_nic_vpowt_context_out, out,
				       nic_vpowt_context.min_wqe_inwine_mode);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_min_inwine);

void mwx5_quewy_min_inwine(stwuct mwx5_cowe_dev *mdev,
			   u8 *min_inwine_mode)
{
	switch (MWX5_CAP_ETH(mdev, wqe_inwine_mode)) {
	case MWX5_CAP_INWINE_MODE_VPOWT_CONTEXT:
		if (!mwx5_quewy_nic_vpowt_min_inwine(mdev, 0, min_inwine_mode))
			bweak;
		fawwthwough;
	case MWX5_CAP_INWINE_MODE_W2:
		*min_inwine_mode = MWX5_INWINE_MODE_W2;
		bweak;
	case MWX5_CAP_INWINE_MODE_NOT_WEQUIWED:
		*min_inwine_mode = MWX5_INWINE_MODE_NONE;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_min_inwine);

int mwx5_modify_nic_vpowt_min_inwine(stwuct mwx5_cowe_dev *mdev,
				     u16 vpowt, u8 min_inwine)
{
	u32 in[MWX5_ST_SZ_DW(modify_nic_vpowt_context_in)] = {};
	void *nic_vpowt_ctx;

	MWX5_SET(modify_nic_vpowt_context_in, in,
		 fiewd_sewect.min_inwine, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	MWX5_SET(modify_nic_vpowt_context_in, in, othew_vpowt, 1);

	nic_vpowt_ctx = MWX5_ADDW_OF(modify_nic_vpowt_context_in,
				     in, nic_vpowt_context);
	MWX5_SET(nic_vpowt_context, nic_vpowt_ctx,
		 min_wqe_inwine_mode, min_inwine);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	wetuwn mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);
}

int mwx5_quewy_nic_vpowt_mac_addwess(stwuct mwx5_cowe_dev *mdev,
				     u16 vpowt, boow othew, u8 *addw)
{
	u32 out[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_in)] = {};
	u8 *out_addw;
	int eww;

	out_addw = MWX5_ADDW_OF(quewy_nic_vpowt_context_out, out,
				nic_vpowt_context.pewmanent_addwess);

	MWX5_SET(quewy_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_NIC_VPOWT_CONTEXT);
	MWX5_SET(quewy_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	MWX5_SET(quewy_nic_vpowt_context_in, in, othew_vpowt, othew);

	eww = mwx5_cmd_exec_inout(mdev, quewy_nic_vpowt_context, in, out);
	if (!eww)
		ethew_addw_copy(addw, &out_addw[2]);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_mac_addwess);

int mwx5_quewy_mac_addwess(stwuct mwx5_cowe_dev *mdev, u8 *addw)
{
	wetuwn mwx5_quewy_nic_vpowt_mac_addwess(mdev, 0, fawse, addw);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_mac_addwess);

int mwx5_modify_nic_vpowt_mac_addwess(stwuct mwx5_cowe_dev *mdev,
				      u16 vpowt, const u8 *addw)
{
	void *in;
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	int eww;
	void *nic_vpowt_ctx;
	u8 *pewm_mac;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in,
		 fiewd_sewect.pewmanent_addwess, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	MWX5_SET(modify_nic_vpowt_context_in, in, othew_vpowt, 1);

	nic_vpowt_ctx = MWX5_ADDW_OF(modify_nic_vpowt_context_in,
				     in, nic_vpowt_context);
	pewm_mac = MWX5_ADDW_OF(nic_vpowt_context, nic_vpowt_ctx,
				pewmanent_addwess);

	ethew_addw_copy(&pewm_mac[2], addw);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_modify_nic_vpowt_mac_addwess);

int mwx5_quewy_nic_vpowt_mtu(stwuct mwx5_cowe_dev *mdev, u16 *mtu)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);
	u32 *out;
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_nic_vpowt_context(mdev, 0, out);
	if (!eww)
		*mtu = MWX5_GET(quewy_nic_vpowt_context_out, out,
				nic_vpowt_context.mtu);

	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_mtu);

int mwx5_modify_nic_vpowt_mtu(stwuct mwx5_cowe_dev *mdev, u16 mtu)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.mtu, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, nic_vpowt_context.mtu, mtu);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_modify_nic_vpowt_mtu);

int mwx5_quewy_nic_vpowt_mac_wist(stwuct mwx5_cowe_dev *dev,
				  u16 vpowt,
				  enum mwx5_wist_type wist_type,
				  u8 addw_wist[][ETH_AWEN],
				  int *wist_size)
{
	u32 in[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_in)] = {0};
	void *nic_vpowt_ctx;
	int max_wist_size;
	int weq_wist_size;
	int out_sz;
	void *out;
	int eww;
	int i;

	weq_wist_size = *wist_size;

	max_wist_size = wist_type == MWX5_NVPWT_WIST_TYPE_UC ?
		1 << MWX5_CAP_GEN(dev, wog_max_cuwwent_uc_wist) :
		1 << MWX5_CAP_GEN(dev, wog_max_cuwwent_mc_wist);

	if (weq_wist_size > max_wist_size) {
		mwx5_cowe_wawn(dev, "Wequested wist size (%d) > (%d) max_wist_size\n",
			       weq_wist_size, max_wist_size);
		weq_wist_size = max_wist_size;
	}

	out_sz = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out) +
			weq_wist_size * MWX5_ST_SZ_BYTES(mac_addwess_wayout);

	out = kvzawwoc(out_sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_NIC_VPOWT_CONTEXT);
	MWX5_SET(quewy_nic_vpowt_context_in, in, awwowed_wist_type, wist_type);
	MWX5_SET(quewy_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	if (vpowt || mwx5_cowe_is_ecpf(dev))
		MWX5_SET(quewy_nic_vpowt_context_in, in, othew_vpowt, 1);

	eww = mwx5_cmd_exec(dev, in, sizeof(in), out, out_sz);
	if (eww)
		goto out;

	nic_vpowt_ctx = MWX5_ADDW_OF(quewy_nic_vpowt_context_out, out,
				     nic_vpowt_context);
	weq_wist_size = MWX5_GET(nic_vpowt_context, nic_vpowt_ctx,
				 awwowed_wist_size);

	*wist_size = weq_wist_size;
	fow (i = 0; i < weq_wist_size; i++) {
		u8 *mac_addw = MWX5_ADDW_OF(nic_vpowt_context,
					nic_vpowt_ctx,
					cuwwent_uc_mac_addwess[i]) + 2;
		ethew_addw_copy(addw_wist[i], mac_addw);
	}
out:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_mac_wist);

int mwx5_modify_nic_vpowt_mac_wist(stwuct mwx5_cowe_dev *dev,
				   enum mwx5_wist_type wist_type,
				   u8 addw_wist[][ETH_AWEN],
				   int wist_size)
{
	u32 out[MWX5_ST_SZ_DW(modify_nic_vpowt_context_out)] = {};
	void *nic_vpowt_ctx;
	int max_wist_size;
	int in_sz;
	void *in;
	int eww;
	int i;

	max_wist_size = wist_type == MWX5_NVPWT_WIST_TYPE_UC ?
		 1 << MWX5_CAP_GEN(dev, wog_max_cuwwent_uc_wist) :
		 1 << MWX5_CAP_GEN(dev, wog_max_cuwwent_mc_wist);

	if (wist_size > max_wist_size)
		wetuwn -ENOSPC;

	in_sz = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in) +
		wist_size * MWX5_ST_SZ_BYTES(mac_addwess_wayout);

	in = kvzawwoc(in_sz, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 fiewd_sewect.addwesses_wist, 1);

	nic_vpowt_ctx = MWX5_ADDW_OF(modify_nic_vpowt_context_in, in,
				     nic_vpowt_context);

	MWX5_SET(nic_vpowt_context, nic_vpowt_ctx,
		 awwowed_wist_type, wist_type);
	MWX5_SET(nic_vpowt_context, nic_vpowt_ctx,
		 awwowed_wist_size, wist_size);

	fow (i = 0; i < wist_size; i++) {
		u8 *cuww_mac = MWX5_ADDW_OF(nic_vpowt_context,
					    nic_vpowt_ctx,
					    cuwwent_uc_mac_addwess[i]) + 2;
		ethew_addw_copy(cuww_mac, addw_wist[i]);
	}

	eww = mwx5_cmd_exec(dev, in, in_sz, out, sizeof(out));
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_modify_nic_vpowt_mac_wist);

int mwx5_modify_nic_vpowt_vwans(stwuct mwx5_cowe_dev *dev,
				u16 vwans[],
				int wist_size)
{
	u32 out[MWX5_ST_SZ_DW(modify_nic_vpowt_context_out)];
	void *nic_vpowt_ctx;
	int max_wist_size;
	int in_sz;
	void *in;
	int eww;
	int i;

	max_wist_size = 1 << MWX5_CAP_GEN(dev, wog_max_vwan_wist);

	if (wist_size > max_wist_size)
		wetuwn -ENOSPC;

	in_sz = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in) +
		wist_size * MWX5_ST_SZ_BYTES(vwan_wayout);

	memset(out, 0, sizeof(out));
	in = kvzawwoc(in_sz, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 fiewd_sewect.addwesses_wist, 1);

	nic_vpowt_ctx = MWX5_ADDW_OF(modify_nic_vpowt_context_in, in,
				     nic_vpowt_context);

	MWX5_SET(nic_vpowt_context, nic_vpowt_ctx,
		 awwowed_wist_type, MWX5_NVPWT_WIST_TYPE_VWAN);
	MWX5_SET(nic_vpowt_context, nic_vpowt_ctx,
		 awwowed_wist_size, wist_size);

	fow (i = 0; i < wist_size; i++) {
		void *vwan_addw = MWX5_ADDW_OF(nic_vpowt_context,
					       nic_vpowt_ctx,
					       cuwwent_uc_mac_addwess[i]);
		MWX5_SET(vwan_wayout, vwan_addw, vwan, vwans[i]);
	}

	eww = mwx5_cmd_exec(dev, in, in_sz, out, sizeof(out));
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_modify_nic_vpowt_vwans);

int mwx5_quewy_nic_vpowt_system_image_guid(stwuct mwx5_cowe_dev *mdev,
					   u64 *system_image_guid)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_nic_vpowt_context(mdev, 0, out);
	if (eww)
		goto out;

	*system_image_guid = MWX5_GET64(quewy_nic_vpowt_context_out, out,
					nic_vpowt_context.system_image_guid);
out:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_system_image_guid);

int mwx5_quewy_nic_vpowt_sd_gwoup(stwuct mwx5_cowe_dev *mdev, u8 *sd_gwoup)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);
	u32 *out;
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_nic_vpowt_context(mdev, 0, out);
	if (eww)
		goto out;

	*sd_gwoup = MWX5_GET(quewy_nic_vpowt_context_out, out,
			     nic_vpowt_context.sd_gwoup);
out:
	kvfwee(out);
	wetuwn eww;
}

int mwx5_quewy_nic_vpowt_node_guid(stwuct mwx5_cowe_dev *mdev, u64 *node_guid)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	mwx5_quewy_nic_vpowt_context(mdev, 0, out);

	*node_guid = MWX5_GET64(quewy_nic_vpowt_context_out, out,
				nic_vpowt_context.node_guid);

	kvfwee(out);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_node_guid);

int mwx5_modify_nic_vpowt_node_guid(stwuct mwx5_cowe_dev *mdev,
				    u16 vpowt, u64 node_guid)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *nic_vpowt_context;
	void *in;
	int eww;

	if (!MWX5_CAP_GEN(mdev, vpowt_gwoup_managew))
		wetuwn -EACCES;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in,
		 fiewd_sewect.node_guid, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	MWX5_SET(modify_nic_vpowt_context_in, in, othew_vpowt, 1);

	nic_vpowt_context = MWX5_ADDW_OF(modify_nic_vpowt_context_in,
					 in, nic_vpowt_context);
	MWX5_SET64(nic_vpowt_context, nic_vpowt_context, node_guid, node_guid);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);

	wetuwn eww;
}

int mwx5_quewy_nic_vpowt_qkey_viow_cntw(stwuct mwx5_cowe_dev *mdev,
					u16 *qkey_viow_cntw)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	mwx5_quewy_nic_vpowt_context(mdev, 0, out);

	*qkey_viow_cntw = MWX5_GET(quewy_nic_vpowt_context_out, out,
				   nic_vpowt_context.qkey_viowation_countew);

	kvfwee(out);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_qkey_viow_cntw);

int mwx5_quewy_hca_vpowt_gid(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
			     u8 powt_num, u16  vf_num, u16 gid_index,
			     union ib_gid *gid)
{
	int in_sz = MWX5_ST_SZ_BYTES(quewy_hca_vpowt_gid_in);
	int out_sz = MWX5_ST_SZ_BYTES(quewy_hca_vpowt_gid_out);
	int is_gwoup_managew;
	void *out = NUWW;
	void *in = NUWW;
	union ib_gid *tmp;
	int tbsz;
	int nout;
	int eww;

	is_gwoup_managew = MWX5_CAP_GEN(dev, vpowt_gwoup_managew);
	tbsz = mwx5_get_gid_tabwe_wen(MWX5_CAP_GEN(dev, gid_tabwe_size));
	mwx5_cowe_dbg(dev, "vf_num %d, index %d, gid_tabwe_size %d\n",
		      vf_num, gid_index, tbsz);

	if (gid_index > tbsz && gid_index != 0xffff)
		wetuwn -EINVAW;

	if (gid_index == 0xffff)
		nout = tbsz;
	ewse
		nout = 1;

	out_sz += nout * sizeof(*gid);

	in = kvzawwoc(in_sz, GFP_KEWNEW);
	out = kvzawwoc(out_sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(quewy_hca_vpowt_gid_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_VPOWT_GID);
	if (othew_vpowt) {
		if (is_gwoup_managew) {
			MWX5_SET(quewy_hca_vpowt_gid_in, in, vpowt_numbew, vf_num);
			MWX5_SET(quewy_hca_vpowt_gid_in, in, othew_vpowt, 1);
		} ewse {
			eww = -EPEWM;
			goto out;
		}
	}
	MWX5_SET(quewy_hca_vpowt_gid_in, in, gid_index, gid_index);

	if (MWX5_CAP_GEN(dev, num_powts) == 2)
		MWX5_SET(quewy_hca_vpowt_gid_in, in, powt_num, powt_num);

	eww = mwx5_cmd_exec(dev, in, in_sz, out, out_sz);
	if (eww)
		goto out;

	tmp = out + MWX5_ST_SZ_BYTES(quewy_hca_vpowt_gid_out);
	gid->gwobaw.subnet_pwefix = tmp->gwobaw.subnet_pwefix;
	gid->gwobaw.intewface_id = tmp->gwobaw.intewface_id;

out:
	kvfwee(in);
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_hca_vpowt_gid);

int mwx5_quewy_hca_vpowt_pkey(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
			      u8 powt_num, u16 vf_num, u16 pkey_index,
			      u16 *pkey)
{
	int in_sz = MWX5_ST_SZ_BYTES(quewy_hca_vpowt_pkey_in);
	int out_sz = MWX5_ST_SZ_BYTES(quewy_hca_vpowt_pkey_out);
	int is_gwoup_managew;
	void *out = NUWW;
	void *in = NUWW;
	void *pkaww;
	int nout;
	int tbsz;
	int eww;
	int i;

	is_gwoup_managew = MWX5_CAP_GEN(dev, vpowt_gwoup_managew);

	tbsz = mwx5_to_sw_pkey_sz(MWX5_CAP_GEN(dev, pkey_tabwe_size));
	if (pkey_index > tbsz && pkey_index != 0xffff)
		wetuwn -EINVAW;

	if (pkey_index == 0xffff)
		nout = tbsz;
	ewse
		nout = 1;

	out_sz += nout * MWX5_ST_SZ_BYTES(pkey);

	in = kvzawwoc(in_sz, GFP_KEWNEW);
	out = kvzawwoc(out_sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(quewy_hca_vpowt_pkey_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_VPOWT_PKEY);
	if (othew_vpowt) {
		if (is_gwoup_managew) {
			MWX5_SET(quewy_hca_vpowt_pkey_in, in, vpowt_numbew, vf_num);
			MWX5_SET(quewy_hca_vpowt_pkey_in, in, othew_vpowt, 1);
		} ewse {
			eww = -EPEWM;
			goto out;
		}
	}
	MWX5_SET(quewy_hca_vpowt_pkey_in, in, pkey_index, pkey_index);

	if (MWX5_CAP_GEN(dev, num_powts) == 2)
		MWX5_SET(quewy_hca_vpowt_pkey_in, in, powt_num, powt_num);

	eww = mwx5_cmd_exec(dev, in, in_sz, out, out_sz);
	if (eww)
		goto out;

	pkaww = MWX5_ADDW_OF(quewy_hca_vpowt_pkey_out, out, pkey);
	fow (i = 0; i < nout; i++, pkey++, pkaww += MWX5_ST_SZ_BYTES(pkey))
		*pkey = MWX5_GET_PW(pkey, pkaww, pkey);

out:
	kvfwee(in);
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_hca_vpowt_pkey);

int mwx5_quewy_hca_vpowt_context(stwuct mwx5_cowe_dev *dev,
				 u8 othew_vpowt, u8 powt_num,
				 u16 vf_num,
				 stwuct mwx5_hca_vpowt_context *wep)
{
	int out_sz = MWX5_ST_SZ_BYTES(quewy_hca_vpowt_context_out);
	int in[MWX5_ST_SZ_DW(quewy_hca_vpowt_context_in)] = {};
	int is_gwoup_managew;
	void *out;
	void *ctx;
	int eww;

	is_gwoup_managew = MWX5_CAP_GEN(dev, vpowt_gwoup_managew);

	out = kvzawwoc(out_sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_hca_vpowt_context_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_VPOWT_CONTEXT);

	if (othew_vpowt) {
		if (is_gwoup_managew) {
			MWX5_SET(quewy_hca_vpowt_context_in, in, othew_vpowt, 1);
			MWX5_SET(quewy_hca_vpowt_context_in, in, vpowt_numbew, vf_num);
		} ewse {
			eww = -EPEWM;
			goto ex;
		}
	}

	if (MWX5_CAP_GEN(dev, num_powts) == 2)
		MWX5_SET(quewy_hca_vpowt_context_in, in, powt_num, powt_num);

	eww = mwx5_cmd_exec_inout(dev, quewy_hca_vpowt_context, in, out);
	if (eww)
		goto ex;

	ctx = MWX5_ADDW_OF(quewy_hca_vpowt_context_out, out, hca_vpowt_context);
	wep->fiewd_sewect = MWX5_GET_PW(hca_vpowt_context, ctx, fiewd_sewect);
	wep->sm_viwt_awawe = MWX5_GET_PW(hca_vpowt_context, ctx, sm_viwt_awawe);
	wep->has_smi = MWX5_GET_PW(hca_vpowt_context, ctx, has_smi);
	wep->has_waw = MWX5_GET_PW(hca_vpowt_context, ctx, has_waw);
	wep->powicy = MWX5_GET_PW(hca_vpowt_context, ctx, vpowt_state_powicy);
	wep->phys_state = MWX5_GET_PW(hca_vpowt_context, ctx,
				      powt_physicaw_state);
	wep->vpowt_state = MWX5_GET_PW(hca_vpowt_context, ctx, vpowt_state);
	wep->powt_physicaw_state = MWX5_GET_PW(hca_vpowt_context, ctx,
					       powt_physicaw_state);
	wep->powt_guid = MWX5_GET64_PW(hca_vpowt_context, ctx, powt_guid);
	wep->node_guid = MWX5_GET64_PW(hca_vpowt_context, ctx, node_guid);
	wep->cap_mask1 = MWX5_GET_PW(hca_vpowt_context, ctx, cap_mask1);
	wep->cap_mask1_pewm = MWX5_GET_PW(hca_vpowt_context, ctx,
					  cap_mask1_fiewd_sewect);
	wep->cap_mask2 = MWX5_GET_PW(hca_vpowt_context, ctx, cap_mask2);
	wep->cap_mask2_pewm = MWX5_GET_PW(hca_vpowt_context, ctx,
					  cap_mask2_fiewd_sewect);
	wep->wid = MWX5_GET_PW(hca_vpowt_context, ctx, wid);
	wep->init_type_wepwy = MWX5_GET_PW(hca_vpowt_context, ctx,
					   init_type_wepwy);
	wep->wmc = MWX5_GET_PW(hca_vpowt_context, ctx, wmc);
	wep->subnet_timeout = MWX5_GET_PW(hca_vpowt_context, ctx,
					  subnet_timeout);
	wep->sm_wid = MWX5_GET_PW(hca_vpowt_context, ctx, sm_wid);
	wep->sm_sw = MWX5_GET_PW(hca_vpowt_context, ctx, sm_sw);
	wep->qkey_viowation_countew = MWX5_GET_PW(hca_vpowt_context, ctx,
						  qkey_viowation_countew);
	wep->pkey_viowation_countew = MWX5_GET_PW(hca_vpowt_context, ctx,
						  pkey_viowation_countew);
	wep->gwh_wequiwed = MWX5_GET_PW(hca_vpowt_context, ctx, gwh_wequiwed);
	wep->sys_image_guid = MWX5_GET64_PW(hca_vpowt_context, ctx,
					    system_image_guid);

ex:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_hca_vpowt_context);

int mwx5_quewy_hca_vpowt_system_image_guid(stwuct mwx5_cowe_dev *dev,
					   u64 *sys_image_guid)
{
	stwuct mwx5_hca_vpowt_context *wep;
	int eww;

	wep = kvzawwoc(sizeof(*wep), GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_hca_vpowt_context(dev, 0, 1, 0, wep);
	if (!eww)
		*sys_image_guid = wep->sys_image_guid;

	kvfwee(wep);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_hca_vpowt_system_image_guid);

int mwx5_quewy_hca_vpowt_node_guid(stwuct mwx5_cowe_dev *dev,
				   u64 *node_guid)
{
	stwuct mwx5_hca_vpowt_context *wep;
	int eww;

	wep = kvzawwoc(sizeof(*wep), GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_hca_vpowt_context(dev, 0, 1, 0, wep);
	if (!eww)
		*node_guid = wep->node_guid;

	kvfwee(wep);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_hca_vpowt_node_guid);

int mwx5_quewy_nic_vpowt_pwomisc(stwuct mwx5_cowe_dev *mdev,
				 u16 vpowt,
				 int *pwomisc_uc,
				 int *pwomisc_mc,
				 int *pwomisc_aww)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_nic_vpowt_context(mdev, vpowt, out);
	if (eww)
		goto out;

	*pwomisc_uc = MWX5_GET(quewy_nic_vpowt_context_out, out,
			       nic_vpowt_context.pwomisc_uc);
	*pwomisc_mc = MWX5_GET(quewy_nic_vpowt_context_out, out,
			       nic_vpowt_context.pwomisc_mc);
	*pwomisc_aww = MWX5_GET(quewy_nic_vpowt_context_out, out,
				nic_vpowt_context.pwomisc_aww);

out:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_vpowt_pwomisc);

int mwx5_modify_nic_vpowt_pwomisc(stwuct mwx5_cowe_dev *mdev,
				  int pwomisc_uc,
				  int pwomisc_mc,
				  int pwomisc_aww)
{
	void *in;
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.pwomisc, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.pwomisc_uc, pwomisc_uc);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.pwomisc_mc, pwomisc_mc);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.pwomisc_aww, pwomisc_aww);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_modify_nic_vpowt_pwomisc);

enum {
	UC_WOCAW_WB,
	MC_WOCAW_WB
};

int mwx5_nic_vpowt_update_wocaw_wb(stwuct mwx5_cowe_dev *mdev, boow enabwe)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *in;
	int eww;

	if (!MWX5_CAP_GEN(mdev, disabwe_wocaw_wb_mc) &&
	    !MWX5_CAP_GEN(mdev, disabwe_wocaw_wb_uc))
		wetuwn 0;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.disabwe_mc_wocaw_wb, !enabwe);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.disabwe_uc_wocaw_wb, !enabwe);

	if (MWX5_CAP_GEN(mdev, disabwe_wocaw_wb_mc))
		MWX5_SET(modify_nic_vpowt_context_in, in,
			 fiewd_sewect.disabwe_mc_wocaw_wb, 1);

	if (MWX5_CAP_GEN(mdev, disabwe_wocaw_wb_uc))
		MWX5_SET(modify_nic_vpowt_context_in, in,
			 fiewd_sewect.disabwe_uc_wocaw_wb, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	if (!eww)
		mwx5_cowe_dbg(mdev, "%s wocaw_wb\n",
			      enabwe ? "enabwe" : "disabwe");

	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_nic_vpowt_update_wocaw_wb);

int mwx5_nic_vpowt_quewy_wocaw_wb(stwuct mwx5_cowe_dev *mdev, boow *status)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_nic_vpowt_context_out);
	u32 *out;
	int vawue;
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_quewy_nic_vpowt_context(mdev, 0, out);
	if (eww)
		goto out;

	vawue = MWX5_GET(quewy_nic_vpowt_context_out, out,
			 nic_vpowt_context.disabwe_mc_wocaw_wb) << MC_WOCAW_WB;

	vawue |= MWX5_GET(quewy_nic_vpowt_context_out, out,
			  nic_vpowt_context.disabwe_uc_wocaw_wb) << UC_WOCAW_WB;

	*status = !vawue;

out:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_nic_vpowt_quewy_wocaw_wb);

enum mwx5_vpowt_woce_state {
	MWX5_VPOWT_WOCE_DISABWED = 0,
	MWX5_VPOWT_WOCE_ENABWED  = 1,
};

static int mwx5_nic_vpowt_update_woce_state(stwuct mwx5_cowe_dev *mdev,
					    enum mwx5_vpowt_woce_state state)
{
	void *in;
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.woce_en, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, nic_vpowt_context.woce_en,
		 state);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);

	wetuwn eww;
}

int mwx5_nic_vpowt_enabwe_woce(stwuct mwx5_cowe_dev *mdev)
{
	int eww = 0;

	mutex_wock(&mwx5_woce_en_wock);
	if (!mdev->woce.woce_en)
		eww = mwx5_nic_vpowt_update_woce_state(mdev, MWX5_VPOWT_WOCE_ENABWED);

	if (!eww)
		mdev->woce.woce_en++;
	mutex_unwock(&mwx5_woce_en_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_nic_vpowt_enabwe_woce);

int mwx5_nic_vpowt_disabwe_woce(stwuct mwx5_cowe_dev *mdev)
{
	int eww = 0;

	mutex_wock(&mwx5_woce_en_wock);
	if (mdev->woce.woce_en) {
		mdev->woce.woce_en--;
		if (mdev->woce.woce_en == 0)
			eww = mwx5_nic_vpowt_update_woce_state(mdev, MWX5_VPOWT_WOCE_DISABWED);

		if (eww)
			mdev->woce.woce_en++;
	}
	mutex_unwock(&mwx5_woce_en_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_nic_vpowt_disabwe_woce);

int mwx5_cowe_quewy_vpowt_countew(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
				  int vf, u8 powt_num, void *out)
{
	int in_sz = MWX5_ST_SZ_BYTES(quewy_vpowt_countew_in);
	int is_gwoup_managew;
	void *in;
	int eww;

	is_gwoup_managew = MWX5_CAP_GEN(dev, vpowt_gwoup_managew);
	in = kvzawwoc(in_sz, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		wetuwn eww;
	}

	MWX5_SET(quewy_vpowt_countew_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_VPOWT_COUNTEW);
	if (othew_vpowt) {
		if (is_gwoup_managew) {
			MWX5_SET(quewy_vpowt_countew_in, in, othew_vpowt, 1);
			MWX5_SET(quewy_vpowt_countew_in, in, vpowt_numbew, vf + 1);
		} ewse {
			eww = -EPEWM;
			goto fwee;
		}
	}
	if (MWX5_CAP_GEN(dev, num_powts) == 2)
		MWX5_SET(quewy_vpowt_countew_in, in, powt_num, powt_num);

	eww = mwx5_cmd_exec_inout(dev, quewy_vpowt_countew, in, out);
fwee:
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_cowe_quewy_vpowt_countew);

int mwx5_quewy_vpowt_down_stats(stwuct mwx5_cowe_dev *mdev, u16 vpowt,
				u8 othew_vpowt, u64 *wx_discawd_vpowt_down,
				u64 *tx_discawd_vpowt_down)
{
	u32 out[MWX5_ST_SZ_DW(quewy_vnic_env_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_vnic_env_in)] = {};
	int eww;

	MWX5_SET(quewy_vnic_env_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_VNIC_ENV);
	MWX5_SET(quewy_vnic_env_in, in, op_mod, 0);
	MWX5_SET(quewy_vnic_env_in, in, vpowt_numbew, vpowt);
	MWX5_SET(quewy_vnic_env_in, in, othew_vpowt, othew_vpowt);

	eww = mwx5_cmd_exec_inout(mdev, quewy_vnic_env, in, out);
	if (eww)
		wetuwn eww;

	*wx_discawd_vpowt_down = MWX5_GET64(quewy_vnic_env_out, out,
					    vpowt_env.weceive_discawd_vpowt_down);
	*tx_discawd_vpowt_down = MWX5_GET64(quewy_vnic_env_out, out,
					    vpowt_env.twansmit_discawd_vpowt_down);
	wetuwn 0;
}

int mwx5_cowe_modify_hca_vpowt_context(stwuct mwx5_cowe_dev *dev,
				       u8 othew_vpowt, u8 powt_num,
				       int vf,
				       stwuct mwx5_hca_vpowt_context *weq)
{
	int in_sz = MWX5_ST_SZ_BYTES(modify_hca_vpowt_context_in);
	int is_gwoup_managew;
	void *ctx;
	void *in;
	int eww;

	mwx5_cowe_dbg(dev, "vf %d\n", vf);
	is_gwoup_managew = MWX5_CAP_GEN(dev, vpowt_gwoup_managew);
	in = kvzawwoc(in_sz, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_hca_vpowt_context_in, in, opcode, MWX5_CMD_OP_MODIFY_HCA_VPOWT_CONTEXT);
	if (othew_vpowt) {
		if (is_gwoup_managew) {
			MWX5_SET(modify_hca_vpowt_context_in, in, othew_vpowt, 1);
			MWX5_SET(modify_hca_vpowt_context_in, in, vpowt_numbew, vf);
		} ewse {
			eww = -EPEWM;
			goto ex;
		}
	}

	if (MWX5_CAP_GEN(dev, num_powts) > 1)
		MWX5_SET(modify_hca_vpowt_context_in, in, powt_num, powt_num);

	ctx = MWX5_ADDW_OF(modify_hca_vpowt_context_in, in, hca_vpowt_context);
	MWX5_SET(hca_vpowt_context, ctx, fiewd_sewect, weq->fiewd_sewect);
	if (weq->fiewd_sewect & MWX5_HCA_VPOWT_SEW_STATE_POWICY)
		MWX5_SET(hca_vpowt_context, ctx, vpowt_state_powicy,
			 weq->powicy);
	if (weq->fiewd_sewect & MWX5_HCA_VPOWT_SEW_POWT_GUID)
		MWX5_SET64(hca_vpowt_context, ctx, powt_guid, weq->powt_guid);
	if (weq->fiewd_sewect & MWX5_HCA_VPOWT_SEW_NODE_GUID)
		MWX5_SET64(hca_vpowt_context, ctx, node_guid, weq->node_guid);
	MWX5_SET(hca_vpowt_context, ctx, cap_mask1, weq->cap_mask1);
	MWX5_SET(hca_vpowt_context, ctx, cap_mask1_fiewd_sewect,
		 weq->cap_mask1_pewm);
	eww = mwx5_cmd_exec_in(dev, modify_hca_vpowt_context, in);
ex:
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_cowe_modify_hca_vpowt_context);

int mwx5_nic_vpowt_affiwiate_muwtipowt(stwuct mwx5_cowe_dev *mastew_mdev,
				       stwuct mwx5_cowe_dev *powt_mdev)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	eww = mwx5_nic_vpowt_enabwe_woce(powt_mdev);
	if (eww)
		goto fwee;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.affiwiation, 1);
	if (MWX5_CAP_GEN_2(mastew_mdev, sw_vhca_id_vawid)) {
		MWX5_SET(modify_nic_vpowt_context_in, in,
			 nic_vpowt_context.vhca_id_type, VHCA_ID_TYPE_SW);
		MWX5_SET(modify_nic_vpowt_context_in, in,
			 nic_vpowt_context.affiwiated_vhca_id,
			 MWX5_CAP_GEN_2(mastew_mdev, sw_vhca_id));
	} ewse {
		MWX5_SET(modify_nic_vpowt_context_in, in,
			 nic_vpowt_context.affiwiated_vhca_id,
			 MWX5_CAP_GEN(mastew_mdev, vhca_id));
	}
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.affiwiation_cwitewia,
		 MWX5_CAP_GEN(powt_mdev, affiwiate_nic_vpowt_cwitewia));
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(powt_mdev, modify_nic_vpowt_context, in);
	if (eww)
		mwx5_nic_vpowt_disabwe_woce(powt_mdev);

fwee:
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_nic_vpowt_affiwiate_muwtipowt);

int mwx5_nic_vpowt_unaffiwiate_muwtipowt(stwuct mwx5_cowe_dev *powt_mdev)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.affiwiation, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.affiwiated_vhca_id, 0);
	MWX5_SET(modify_nic_vpowt_context_in, in,
		 nic_vpowt_context.affiwiation_cwitewia, 0);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(powt_mdev, modify_nic_vpowt_context, in);
	if (!eww)
		mwx5_nic_vpowt_disabwe_woce(powt_mdev);

	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_nic_vpowt_unaffiwiate_muwtipowt);

u64 mwx5_quewy_nic_system_image_guid(stwuct mwx5_cowe_dev *mdev)
{
	int powt_type_cap = MWX5_CAP_GEN(mdev, powt_type);
	u64 tmp;
	int eww;

	if (mdev->sys_image_guid)
		wetuwn mdev->sys_image_guid;

	if (powt_type_cap == MWX5_CAP_POWT_TYPE_ETH)
		eww = mwx5_quewy_nic_vpowt_system_image_guid(mdev, &tmp);
	ewse
		eww = mwx5_quewy_hca_vpowt_system_image_guid(mdev, &tmp);

	mdev->sys_image_guid = eww ? 0 : tmp;

	wetuwn mdev->sys_image_guid;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_nic_system_image_guid);

int mwx5_vpowt_get_othew_func_cap(stwuct mwx5_cowe_dev *dev, u16 vpowt, void *out,
				  u16 opmod)
{
	boow ec_vf_func = mwx5_cowe_is_ec_vf_vpowt(dev, vpowt);
	u8 in[MWX5_ST_SZ_BYTES(quewy_hca_cap_in)] = {};

	opmod = (opmod << 1) | (HCA_CAP_OPMOD_GET_MAX & 0x01);
	MWX5_SET(quewy_hca_cap_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_CAP);
	MWX5_SET(quewy_hca_cap_in, in, op_mod, opmod);
	MWX5_SET(quewy_hca_cap_in, in, function_id, mwx5_vpowt_to_func_id(dev, vpowt, ec_vf_func));
	MWX5_SET(quewy_hca_cap_in, in, othew_function, twue);
	MWX5_SET(quewy_hca_cap_in, in, ec_vf_function, ec_vf_func);
	wetuwn mwx5_cmd_exec_inout(dev, quewy_hca_cap, in, out);
}
EXPOWT_SYMBOW_GPW(mwx5_vpowt_get_othew_func_cap);

int mwx5_vpowt_set_othew_func_cap(stwuct mwx5_cowe_dev *dev, const void *hca_cap,
				  u16 vpowt, u16 opmod)
{
	boow ec_vf_func = mwx5_cowe_is_ec_vf_vpowt(dev, vpowt);
	int set_sz = MWX5_ST_SZ_BYTES(set_hca_cap_in);
	void *set_hca_cap;
	void *set_ctx;
	int wet;

	set_ctx = kzawwoc(set_sz, GFP_KEWNEW);
	if (!set_ctx)
		wetuwn -ENOMEM;

	MWX5_SET(set_hca_cap_in, set_ctx, opcode, MWX5_CMD_OP_SET_HCA_CAP);
	MWX5_SET(set_hca_cap_in, set_ctx, op_mod, opmod << 1);
	set_hca_cap = MWX5_ADDW_OF(set_hca_cap_in, set_ctx, capabiwity);
	memcpy(set_hca_cap, hca_cap, MWX5_ST_SZ_BYTES(cmd_hca_cap));
	MWX5_SET(set_hca_cap_in, set_ctx, function_id,
		 mwx5_vpowt_to_func_id(dev, vpowt, ec_vf_func));
	MWX5_SET(set_hca_cap_in, set_ctx, othew_function, twue);
	MWX5_SET(set_hca_cap_in, set_ctx, ec_vf_function, ec_vf_func);
	wet = mwx5_cmd_exec_in(dev, set_hca_cap, set_ctx);

	kfwee(set_ctx);
	wetuwn wet;
}
