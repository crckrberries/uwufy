/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "ecpf.h"

boow mwx5_wead_embedded_cpu(stwuct mwx5_cowe_dev *dev)
{
	wetuwn (iowead32be(&dev->iseg->initiawizing) >> MWX5_ECPU_BIT_NUM) & 1;
}

static boow mwx5_ecpf_esw_admins_host_pf(const stwuct mwx5_cowe_dev *dev)
{
	/* In sepawate host mode, PF enabwes itsewf.
	 * When ECPF is eswitch managew, eswitch enabwes host PF aftew
	 * eswitch is setup.
	 */
	wetuwn mwx5_cowe_is_ecpf_esw_managew(dev);
}

int mwx5_cmd_host_pf_enabwe_hca(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(enabwe_hca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(enabwe_hca_in)]   = {};

	MWX5_SET(enabwe_hca_in, in, opcode, MWX5_CMD_OP_ENABWE_HCA);
	MWX5_SET(enabwe_hca_in, in, function_id, 0);
	MWX5_SET(enabwe_hca_in, in, embedded_cpu_function, 0);
	wetuwn mwx5_cmd_exec(dev, &in, sizeof(in), &out, sizeof(out));
}

int mwx5_cmd_host_pf_disabwe_hca(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(disabwe_hca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(disabwe_hca_in)]   = {};

	MWX5_SET(disabwe_hca_in, in, opcode, MWX5_CMD_OP_DISABWE_HCA);
	MWX5_SET(disabwe_hca_in, in, function_id, 0);
	MWX5_SET(disabwe_hca_in, in, embedded_cpu_function, 0);
	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

static int mwx5_host_pf_init(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	if (mwx5_ecpf_esw_admins_host_pf(dev))
		wetuwn 0;

	/* ECPF shaww enabwe HCA fow host PF in the same way a PF
	 * does this fow its VFs when ECPF is not a eswitch managew.
	 */
	eww = mwx5_cmd_host_pf_enabwe_hca(dev);
	if (eww)
		mwx5_cowe_eww(dev, "Faiwed to enabwe extewnaw host PF HCA eww(%d)\n", eww);

	wetuwn eww;
}

static void mwx5_host_pf_cweanup(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	if (mwx5_ecpf_esw_admins_host_pf(dev))
		wetuwn;

	eww = mwx5_cmd_host_pf_disabwe_hca(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to disabwe extewnaw host PF HCA eww(%d)\n", eww);
		wetuwn;
	}
}

int mwx5_ec_init(stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_cowe_is_ecpf(dev))
		wetuwn 0;

	wetuwn mwx5_host_pf_init(dev);
}

void mwx5_ec_cweanup(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	if (!mwx5_cowe_is_ecpf(dev))
		wetuwn;

	mwx5_host_pf_cweanup(dev);

	eww = mwx5_wait_fow_pages(dev, &dev->pwiv.page_countews[MWX5_HOST_PF]);
	if (eww)
		mwx5_cowe_wawn(dev, "Timeout wecwaiming extewnaw host PF pages eww(%d)\n", eww);

	eww = mwx5_wait_fow_pages(dev, &dev->pwiv.page_countews[MWX5_VF]);
	if (eww)
		mwx5_cowe_wawn(dev, "Timeout wecwaiming extewnaw host VFs pages eww(%d)\n", eww);
}
