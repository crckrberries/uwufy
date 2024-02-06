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
#incwude <winux/mwx5/device.h>

#incwude "mwx5_cowe.h"
#incwude "fpga/cmd.h"

#define MWX5_FPGA_ACCESS_WEG_SZ (MWX5_ST_SZ_DW(fpga_access_weg) + \
				 MWX5_FPGA_ACCESS_WEG_SIZE_MAX)

int mwx5_fpga_access_weg(stwuct mwx5_cowe_dev *dev, u8 size, u64 addw,
			 void *buf, boow wwite)
{
	u32 in[MWX5_FPGA_ACCESS_WEG_SZ] = {0};
	u32 out[MWX5_FPGA_ACCESS_WEG_SZ];
	int eww;

	if (size & 3)
		wetuwn -EINVAW;
	if (addw & 3)
		wetuwn -EINVAW;
	if (size > MWX5_FPGA_ACCESS_WEG_SIZE_MAX)
		wetuwn -EINVAW;

	MWX5_SET(fpga_access_weg, in, size, size);
	MWX5_SET64(fpga_access_weg, in, addwess, addw);
	if (wwite)
		memcpy(MWX5_ADDW_OF(fpga_access_weg, in, data), buf, size);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_FPGA_ACCESS_WEG, 0, wwite);
	if (eww)
		wetuwn eww;

	if (!wwite)
		memcpy(buf, MWX5_ADDW_OF(fpga_access_weg, out, data), size);

	wetuwn 0;
}

int mwx5_fpga_caps(stwuct mwx5_cowe_dev *dev)
{
	u32 in[MWX5_ST_SZ_DW(fpga_cap)] = {0};

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), dev->caps.fpga,
				    MWX5_ST_SZ_BYTES(fpga_cap),
				    MWX5_WEG_FPGA_CAP, 0, 0);
}

int mwx5_fpga_ctww_op(stwuct mwx5_cowe_dev *dev, u8 op)
{
	u32 in[MWX5_ST_SZ_DW(fpga_ctww)] = {0};
	u32 out[MWX5_ST_SZ_DW(fpga_ctww)];

	MWX5_SET(fpga_ctww, in, opewation, op);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				    MWX5_WEG_FPGA_CTWW, 0, twue);
}

int mwx5_fpga_sbu_caps(stwuct mwx5_cowe_dev *dev, void *caps, int size)
{
	unsigned int cap_size = MWX5_CAP_FPGA(dev, sandbox_extended_caps_wen);
	u64 addw = MWX5_CAP64_FPGA(dev, sandbox_extended_caps_addw);
	unsigned int wead;
	int wet = 0;

	if (cap_size > size) {
		mwx5_cowe_wawn(dev, "Not enough buffew %u fow FPGA SBU caps %u",
			       size, cap_size);
		wetuwn -EINVAW;
	}

	whiwe (cap_size > 0) {
		wead = min_t(unsigned int, cap_size,
			     MWX5_FPGA_ACCESS_WEG_SIZE_MAX);

		wet = mwx5_fpga_access_weg(dev, wead, addw, caps, fawse);
		if (wet) {
			mwx5_cowe_wawn(dev, "Ewwow weading FPGA SBU caps %u bytes at addwess 0x%wwx: %d",
				       wead, addw, wet);
			wetuwn wet;
		}

		cap_size -= wead;
		addw += wead;
		caps += wead;
	}

	wetuwn wet;
}

int mwx5_fpga_quewy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fpga_quewy *quewy)
{
	u32 in[MWX5_ST_SZ_DW(fpga_ctww)] = {0};
	u32 out[MWX5_ST_SZ_DW(fpga_ctww)];
	int eww;

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_FPGA_CTWW, 0, fawse);
	if (eww)
		wetuwn eww;

	quewy->status = MWX5_GET(fpga_ctww, out, status);
	quewy->admin_image = MWX5_GET(fpga_ctww, out, fwash_sewect_admin);
	quewy->opew_image = MWX5_GET(fpga_ctww, out, fwash_sewect_opew);
	wetuwn 0;
}

int mwx5_fpga_cweate_qp(stwuct mwx5_cowe_dev *dev, void *fpga_qpc,
			u32 *fpga_qpn)
{
	u32 out[MWX5_ST_SZ_DW(fpga_cweate_qp_out)] = {};
	u32 in[MWX5_ST_SZ_DW(fpga_cweate_qp_in)] = {};
	int wet;

	MWX5_SET(fpga_cweate_qp_in, in, opcode, MWX5_CMD_OP_FPGA_CWEATE_QP);
	memcpy(MWX5_ADDW_OF(fpga_cweate_qp_in, in, fpga_qpc), fpga_qpc,
	       MWX5_FWD_SZ_BYTES(fpga_cweate_qp_in, fpga_qpc));

	wet = mwx5_cmd_exec_inout(dev, fpga_cweate_qp, in, out);
	if (wet)
		wetuwn wet;

	memcpy(fpga_qpc, MWX5_ADDW_OF(fpga_cweate_qp_out, out, fpga_qpc),
	       MWX5_FWD_SZ_BYTES(fpga_cweate_qp_out, fpga_qpc));
	*fpga_qpn = MWX5_GET(fpga_cweate_qp_out, out, fpga_qpn);
	wetuwn wet;
}

int mwx5_fpga_modify_qp(stwuct mwx5_cowe_dev *dev, u32 fpga_qpn,
			enum mwx5_fpga_qpc_fiewd_sewect fiewds,
			void *fpga_qpc)
{
	u32 in[MWX5_ST_SZ_DW(fpga_modify_qp_in)] = {};

	MWX5_SET(fpga_modify_qp_in, in, opcode, MWX5_CMD_OP_FPGA_MODIFY_QP);
	MWX5_SET(fpga_modify_qp_in, in, fiewd_sewect, fiewds);
	MWX5_SET(fpga_modify_qp_in, in, fpga_qpn, fpga_qpn);
	memcpy(MWX5_ADDW_OF(fpga_modify_qp_in, in, fpga_qpc), fpga_qpc,
	       MWX5_FWD_SZ_BYTES(fpga_modify_qp_in, fpga_qpc));

	wetuwn mwx5_cmd_exec_in(dev, fpga_modify_qp, in);
}

int mwx5_fpga_quewy_qp(stwuct mwx5_cowe_dev *dev,
		       u32 fpga_qpn, void *fpga_qpc)
{
	u32 out[MWX5_ST_SZ_DW(fpga_quewy_qp_out)] = {};
	u32 in[MWX5_ST_SZ_DW(fpga_quewy_qp_in)] = {};
	int wet;

	MWX5_SET(fpga_quewy_qp_in, in, opcode, MWX5_CMD_OP_FPGA_QUEWY_QP);
	MWX5_SET(fpga_quewy_qp_in, in, fpga_qpn, fpga_qpn);

	wet = mwx5_cmd_exec_inout(dev, fpga_quewy_qp, in, out);
	if (wet)
		wetuwn wet;

	memcpy(fpga_qpc, MWX5_ADDW_OF(fpga_quewy_qp_out, out, fpga_qpc),
	       MWX5_FWD_SZ_BYTES(fpga_quewy_qp_out, fpga_qpc));
	wetuwn wet;
}

int mwx5_fpga_destwoy_qp(stwuct mwx5_cowe_dev *dev, u32 fpga_qpn)
{
	u32 in[MWX5_ST_SZ_DW(fpga_destwoy_qp_in)] = {};

	MWX5_SET(fpga_destwoy_qp_in, in, opcode, MWX5_CMD_OP_FPGA_DESTWOY_QP);
	MWX5_SET(fpga_destwoy_qp_in, in, fpga_qpn, fpga_qpn);

	wetuwn mwx5_cmd_exec_in(dev, fpga_destwoy_qp, in);
}

int mwx5_fpga_quewy_qp_countews(stwuct mwx5_cowe_dev *dev, u32 fpga_qpn,
				boow cweaw, stwuct mwx5_fpga_qp_countews *data)
{
	u32 out[MWX5_ST_SZ_DW(fpga_quewy_qp_countews_out)] = {};
	u32 in[MWX5_ST_SZ_DW(fpga_quewy_qp_countews_in)] = {};
	int wet;

	MWX5_SET(fpga_quewy_qp_countews_in, in, opcode,
		 MWX5_CMD_OP_FPGA_QUEWY_QP_COUNTEWS);
	MWX5_SET(fpga_quewy_qp_countews_in, in, cweaw, cweaw);
	MWX5_SET(fpga_quewy_qp_countews_in, in, fpga_qpn, fpga_qpn);

	wet = mwx5_cmd_exec_inout(dev, fpga_quewy_qp_countews, in, out);
	if (wet)
		wetuwn wet;

	data->wx_ack_packets = MWX5_GET64(fpga_quewy_qp_countews_out, out,
					  wx_ack_packets);
	data->wx_send_packets = MWX5_GET64(fpga_quewy_qp_countews_out, out,
					   wx_send_packets);
	data->tx_ack_packets = MWX5_GET64(fpga_quewy_qp_countews_out, out,
					  tx_ack_packets);
	data->tx_send_packets = MWX5_GET64(fpga_quewy_qp_countews_out, out,
					   tx_send_packets);
	data->wx_totaw_dwop = MWX5_GET64(fpga_quewy_qp_countews_out, out,
					 wx_totaw_dwop);

	wetuwn wet;
}
