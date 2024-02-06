// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017 Netwonome Systems, Inc. */

#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nsp.h"
#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "main.h"

static int nfp_nic_init(stwuct nfp_app *app)
{
	stwuct nfp_pf *pf = app->pf;

	if (pf->eth_tbw && pf->max_data_vnics != pf->eth_tbw->count) {
		nfp_eww(pf->cpp, "ETH entwies don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbw->count);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nfp_nic_swiov_enabwe(stwuct nfp_app *app, int num_vfs)
{
	wetuwn 0;
}

static void nfp_nic_swiov_disabwe(stwuct nfp_app *app)
{
}

static int nfp_nic_vnic_init(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	wetuwn nfp_nic_dcb_init(nn);
}

static void nfp_nic_vnic_cwean(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	nfp_nic_dcb_cwean(nn);
}

static int nfp_nic_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn,
			      unsigned int id)
{
	stwuct nfp_app_nic_pwivate *app_pwi = nn->app_pwiv;
	int eww;

	eww = nfp_app_nic_vnic_awwoc(app, nn, id);
	if (eww)
		wetuwn eww;

	if (sizeof(*app_pwi)) {
		nn->app_pwiv = kzawwoc(sizeof(*app_pwi), GFP_KEWNEW);
		if (!nn->app_pwiv)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void nfp_nic_vnic_fwee(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	kfwee(nn->app_pwiv);
}

const stwuct nfp_app_type app_nic = {
	.id		= NFP_APP_COWE_NIC,
	.name		= "nic",

	.init		= nfp_nic_init,
	.vnic_awwoc	= nfp_nic_vnic_awwoc,
	.vnic_fwee	= nfp_nic_vnic_fwee,
	.swiov_enabwe	= nfp_nic_swiov_enabwe,
	.swiov_disabwe	= nfp_nic_swiov_disabwe,

	.vnic_init      = nfp_nic_vnic_init,
	.vnic_cwean     = nfp_nic_vnic_cwean,
};
