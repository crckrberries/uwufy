// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#incwude <winux/mwx5/dwivew.h>
#incwude "pwiv.h"

int mwx5_cmd_awwoc_sf(stwuct mwx5_cowe_dev *dev, u16 function_id)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_sf_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_sf_in)] = {};

	MWX5_SET(awwoc_sf_in, in, opcode, MWX5_CMD_OP_AWWOC_SF);
	MWX5_SET(awwoc_sf_in, in, function_id, function_id);

	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

int mwx5_cmd_deawwoc_sf(stwuct mwx5_cowe_dev *dev, u16 function_id)
{
	u32 out[MWX5_ST_SZ_DW(deawwoc_sf_out)] = {};
	u32 in[MWX5_ST_SZ_DW(deawwoc_sf_in)] = {};

	MWX5_SET(deawwoc_sf_in, in, opcode, MWX5_CMD_OP_DEAWWOC_SF);
	MWX5_SET(deawwoc_sf_in, in, function_id, function_id);

	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

int mwx5_cmd_sf_enabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id)
{
	u32 out[MWX5_ST_SZ_DW(enabwe_hca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(enabwe_hca_in)] = {};

	MWX5_SET(enabwe_hca_in, in, opcode, MWX5_CMD_OP_ENABWE_HCA);
	MWX5_SET(enabwe_hca_in, in, function_id, func_id);
	MWX5_SET(enabwe_hca_in, in, embedded_cpu_function, 0);
	wetuwn mwx5_cmd_exec(dev, &in, sizeof(in), &out, sizeof(out));
}

int mwx5_cmd_sf_disabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id)
{
	u32 out[MWX5_ST_SZ_DW(disabwe_hca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(disabwe_hca_in)] = {};

	MWX5_SET(disabwe_hca_in, in, opcode, MWX5_CMD_OP_DISABWE_HCA);
	MWX5_SET(disabwe_hca_in, in, function_id, func_id);
	MWX5_SET(enabwe_hca_in, in, embedded_cpu_function, 0);
	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}
