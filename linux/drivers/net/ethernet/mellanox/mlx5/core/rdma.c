// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies */

#incwude <winux/mwx5/vpowt.h>
#incwude <wdma/ib_vewbs.h>
#incwude <net/addwconf.h>

#incwude "wib/mwx5.h"
#incwude "eswitch.h"
#incwude "fs_cowe.h"
#incwude "wdma.h"

static void mwx5_wdma_disabwe_woce_steewing(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cowe_woce *woce = &dev->pwiv.woce;

	mwx5_dew_fwow_wuwes(woce->awwow_wuwe);
	mwx5_destwoy_fwow_gwoup(woce->fg);
	mwx5_destwoy_fwow_tabwe(woce->ft);
}

static int mwx5_wdma_enabwe_woce_steewing(stwuct mwx5_cowe_dev *dev)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_cowe_woce *woce = &dev->pwiv.woce;
	stwuct mwx5_fwow_handwe *fwow_wuwe = NUWW;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns = NUWW;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_gwoup *fg;
	stwuct mwx5_eswitch *esw;
	u32 *fwow_gwoup_in;
	int eww;

	if (!(MWX5_CAP_FWOWTABWE_WDMA_WX(dev, ft_suppowt) &&
	      MWX5_CAP_FWOWTABWE_WDMA_WX(dev, tabwe_miss_action_domain)))
		wetuwn -EOPNOTSUPP;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;
	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		kvfwee(fwow_gwoup_in);
		wetuwn -ENOMEM;
	}

	ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_WDMA_WX_KEWNEW);
	if (!ns) {
		mwx5_cowe_eww(dev, "Faiwed to get WDMA WX namespace");
		eww = -EOPNOTSUPP;
		goto fwee;
	}

	ft_attw.max_fte = 1;
	ft = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft)) {
		mwx5_cowe_eww(dev, "Faiwed to cweate WDMA WX fwow tabwe");
		eww = PTW_EWW(ft);
		goto fwee;
	}

	esw = dev->pwiv.eswitch;
	mwx5_esw_set_fwow_gwoup_souwce_powt(esw, fwow_gwoup_in, 0);

	fg = mwx5_cweate_fwow_gwoup(ft, fwow_gwoup_in);
	if (IS_EWW(fg)) {
		eww = PTW_EWW(fg);
		mwx5_cowe_eww(dev, "Faiwed to cweate WDMA WX fwow gwoup eww(%d)\n", eww);
		goto destwoy_fwow_tabwe;
	}

	mwx5_esw_set_spec_souwce_powt(esw, esw->managew_vpowt, spec);

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	fwow_wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, NUWW, 0);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		mwx5_cowe_eww(dev, "Faiwed to add WoCE awwow wuwe, eww=%d\n",
			      eww);
		goto destwoy_fwow_gwoup;
	}

	kvfwee(spec);
	kvfwee(fwow_gwoup_in);
	woce->ft = ft;
	woce->fg = fg;
	woce->awwow_wuwe = fwow_wuwe;

	wetuwn 0;

destwoy_fwow_gwoup:
	mwx5_destwoy_fwow_gwoup(fg);
destwoy_fwow_tabwe:
	mwx5_destwoy_fwow_tabwe(ft);
fwee:
	kvfwee(spec);
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void mwx5_wdma_dew_woce_addw(stwuct mwx5_cowe_dev *dev)
{
	mwx5_cowe_woce_gid_set(dev, 0, MWX5_WOCE_VEWSION_2, 0,
			       NUWW, NUWW, fawse, 0, 1);
}

static void mwx5_wdma_make_defauwt_gid(stwuct mwx5_cowe_dev *dev, union ib_gid *gid)
{
	u8 hw_id[ETH_AWEN];

	mwx5_quewy_mac_addwess(dev, hw_id);
	gid->gwobaw.subnet_pwefix = cpu_to_be64(0xfe80000000000000WW);
	addwconf_addw_eui48(&gid->waw[8], hw_id);
}

static int mwx5_wdma_add_woce_addw(stwuct mwx5_cowe_dev *dev)
{
	union ib_gid gid;
	u8 mac[ETH_AWEN];

	mwx5_wdma_make_defauwt_gid(dev, &gid);
	wetuwn mwx5_cowe_woce_gid_set(dev, 0,
				      MWX5_WOCE_VEWSION_2,
				      0, gid.waw, mac,
				      fawse, 0, 1);
}

void mwx5_wdma_disabwe_woce(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cowe_woce *woce = &dev->pwiv.woce;

	if (!woce->ft)
		wetuwn;

	mwx5_wdma_disabwe_woce_steewing(dev);
	mwx5_wdma_dew_woce_addw(dev);
	mwx5_nic_vpowt_disabwe_woce(dev);
}

void mwx5_wdma_enabwe_woce(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	if (!MWX5_CAP_GEN(dev, woce))
		wetuwn;

	eww = mwx5_nic_vpowt_enabwe_woce(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to enabwe WoCE: %d\n", eww);
		wetuwn;
	}

	eww = mwx5_wdma_add_woce_addw(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to add WoCE addwess: %d\n", eww);
		goto disabwe_woce;
	}

	eww = mwx5_wdma_enabwe_woce_steewing(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to enabwe WoCE steewing: %d\n", eww);
		goto dew_woce_addw;
	}

	wetuwn;

dew_woce_addw:
	mwx5_wdma_dew_woce_addw(dev);
disabwe_woce:
	mwx5_nic_vpowt_disabwe_woce(dev);
}
