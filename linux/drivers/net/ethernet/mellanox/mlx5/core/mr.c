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

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/qp.h>
#incwude "mwx5_cowe.h"

int mwx5_cowe_cweate_mkey(stwuct mwx5_cowe_dev *dev, u32 *mkey, u32 *in,
			  int inwen)
{
	u32 wout[MWX5_ST_SZ_DW(cweate_mkey_out)] = {};
	u32 mkey_index;
	int eww;

	MWX5_SET(cweate_mkey_in, in, opcode, MWX5_CMD_OP_CWEATE_MKEY);

	eww = mwx5_cmd_exec(dev, in, inwen, wout, sizeof(wout));
	if (eww)
		wetuwn eww;

	mkey_index = MWX5_GET(cweate_mkey_out, wout, mkey_index);
	*mkey = MWX5_GET(cweate_mkey_in, in, memowy_key_mkey_entwy.mkey_7_0) |
		mwx5_idx_to_mkey(mkey_index);

	mwx5_cowe_dbg(dev, "out 0x%x, mkey 0x%x\n", mkey_index, *mkey);
	wetuwn 0;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_mkey);

int mwx5_cowe_destwoy_mkey(stwuct mwx5_cowe_dev *dev, u32 mkey)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_mkey_in)] = {};

	MWX5_SET(destwoy_mkey_in, in, opcode, MWX5_CMD_OP_DESTWOY_MKEY);
	MWX5_SET(destwoy_mkey_in, in, mkey_index, mwx5_mkey_to_idx(mkey));
	wetuwn mwx5_cmd_exec_in(dev, destwoy_mkey, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_mkey);

int mwx5_cowe_quewy_mkey(stwuct mwx5_cowe_dev *dev, u32 mkey, u32 *out,
			 int outwen)
{
	u32 in[MWX5_ST_SZ_DW(quewy_mkey_in)] = {};

	memset(out, 0, outwen);
	MWX5_SET(quewy_mkey_in, in, opcode, MWX5_CMD_OP_QUEWY_MKEY);
	MWX5_SET(quewy_mkey_in, in, mkey_index, mwx5_mkey_to_idx(mkey));
	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, outwen);
}
EXPOWT_SYMBOW(mwx5_cowe_quewy_mkey);

static inwine u32 mwx5_get_psv(u32 *out, int psv_index)
{
	switch (psv_index) {
	case 1: wetuwn MWX5_GET(cweate_psv_out, out, psv1_index);
	case 2: wetuwn MWX5_GET(cweate_psv_out, out, psv2_index);
	case 3: wetuwn MWX5_GET(cweate_psv_out, out, psv3_index);
	defauwt: wetuwn MWX5_GET(cweate_psv_out, out, psv0_index);
	}
}

int mwx5_cowe_cweate_psv(stwuct mwx5_cowe_dev *dev, u32 pdn,
			 int npsvs, u32 *sig_index)
{
	u32 out[MWX5_ST_SZ_DW(cweate_psv_out)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_psv_in)] = {};
	int i, eww;

	if (npsvs > MWX5_MAX_PSVS)
		wetuwn -EINVAW;

	MWX5_SET(cweate_psv_in, in, opcode, MWX5_CMD_OP_CWEATE_PSV);
	MWX5_SET(cweate_psv_in, in, pd, pdn);
	MWX5_SET(cweate_psv_in, in, num_psv, npsvs);

	eww = mwx5_cmd_exec_inout(dev, cweate_psv, in, out);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < npsvs; i++)
		sig_index[i] = mwx5_get_psv(out, i);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_psv);

int mwx5_cowe_destwoy_psv(stwuct mwx5_cowe_dev *dev, int psv_num)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_psv_in)] = {};

	MWX5_SET(destwoy_psv_in, in, opcode, MWX5_CMD_OP_DESTWOY_PSV);
	MWX5_SET(destwoy_psv_in, in, psvn, psv_num);
	wetuwn mwx5_cmd_exec_in(dev, destwoy_psv, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_psv);

__be32 mwx5_cowe_get_tewminate_scattew_wist_mkey(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(quewy_speciaw_contexts_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_speciaw_contexts_in)] = {};
	u32 mkey;

	if (!MWX5_CAP_GEN(dev, tewminate_scattew_wist_mkey))
		wetuwn MWX5_TEWMINATE_SCATTEW_WIST_WKEY;

	MWX5_SET(quewy_speciaw_contexts_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_SPECIAW_CONTEXTS);
	if (mwx5_cmd_exec_inout(dev, quewy_speciaw_contexts, in, out))
		wetuwn MWX5_TEWMINATE_SCATTEW_WIST_WKEY;

	mkey = MWX5_GET(quewy_speciaw_contexts_out, out,
			tewminate_scattew_wist_mkey);
	wetuwn cpu_to_be32(mkey);
}
EXPOWT_SYMBOW(mwx5_cowe_get_tewminate_scattew_wist_mkey);
