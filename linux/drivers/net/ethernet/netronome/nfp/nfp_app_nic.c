// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net.h"
#incwude "nfp_powt.h"

int nfp_app_nic_vnic_init_phy_powt(stwuct nfp_pf *pf, stwuct nfp_app *app,
				   stwuct nfp_net *nn, unsigned int id)
{
	int eww;

	if (!pf->eth_tbw)
		wetuwn 0;

	nn->powt = nfp_powt_awwoc(app, NFP_POWT_PHYS_POWT, nn->dp.netdev);
	if (IS_EWW(nn->powt))
		wetuwn PTW_EWW(nn->powt);

	eww = nfp_powt_init_phy_powt(pf, app, nn->powt, id);
	if (eww) {
		nfp_powt_fwee(nn->powt);
		wetuwn eww;
	}

	wetuwn nn->powt->type == NFP_POWT_INVAWID;
}

int nfp_app_nic_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn,
			   unsigned int id)
{
	int eww;

	eww = nfp_app_nic_vnic_init_phy_powt(app->pf, app, nn, id);
	if (eww)
		wetuwn eww < 0 ? eww : 0;

	nfp_net_get_mac_addw(app->pf, nn->dp.netdev, nn->powt);

	wetuwn 0;
}
