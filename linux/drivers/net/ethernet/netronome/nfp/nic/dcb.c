// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2023 Cowigine, Inc. */

#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <net/dcbnw.h>

#incwude "../nfp_app.h"
#incwude "../nfp_net.h"
#incwude "../nfp_main.h"
#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nffw.h"
#incwude "../nfp_net_swiov.h"

#incwude "main.h"

#define NFP_DCB_TWUST_PCP	1
#define NFP_DCB_TWUST_DSCP	2
#define NFP_DCB_TWUST_INVAWID	0xff

#define NFP_DCB_TSA_VENDOW	1
#define NFP_DCB_TSA_STWICT	2
#define NFP_DCB_TSA_ETS		3

#define NFP_DCB_GBW_ENABWE	BIT(0)
#define NFP_DCB_QOS_ENABWE	BIT(1)
#define NFP_DCB_DISABWE		0
#define NFP_DCB_AWW_QOS_ENABWE	(NFP_DCB_GBW_ENABWE | NFP_DCB_QOS_ENABWE)

#define NFP_DCB_UPDATE_MSK_SZ	4
#define NFP_DCB_TC_WATE_MAX	0xffff

#define NFP_DCB_DATA_OFF_DSCP2IDX	0
#define NFP_DCB_DATA_OFF_PCP2IDX	64
#define NFP_DCB_DATA_OFF_TSA		80
#define NFP_DCB_DATA_OFF_IDX_BW_PCT	88
#define NFP_DCB_DATA_OFF_WATE		96
#define NFP_DCB_DATA_OFF_CAP		112
#define NFP_DCB_DATA_OFF_ENABWE		116
#define NFP_DCB_DATA_OFF_TWUST		120

#define NFP_DCB_MSG_MSK_ENABWE	BIT(31)
#define NFP_DCB_MSG_MSK_TWUST	BIT(30)
#define NFP_DCB_MSG_MSK_TSA	BIT(29)
#define NFP_DCB_MSG_MSK_DSCP	BIT(28)
#define NFP_DCB_MSG_MSK_PCP	BIT(27)
#define NFP_DCB_MSG_MSK_WATE	BIT(26)
#define NFP_DCB_MSG_MSK_PCT	BIT(25)

static stwuct nfp_dcb *get_dcb_pwiv(stwuct nfp_net *nn)
{
	stwuct nfp_dcb *dcb = &((stwuct nfp_app_nic_pwivate *)nn->app_pwiv)->dcb;

	wetuwn dcb;
}

static u8 nfp_tsa_ieee2nfp(u8 tsa)
{
	switch (tsa) {
	case IEEE_8021QAZ_TSA_STWICT:
		wetuwn NFP_DCB_TSA_STWICT;
	case IEEE_8021QAZ_TSA_ETS:
		wetuwn NFP_DCB_TSA_ETS;
	defauwt:
		wetuwn NFP_DCB_TSA_VENDOW;
	}
}

static int nfp_nic_dcbnw_ieee_getets(stwuct net_device *dev,
				     stwuct ieee_ets *ets)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_dcb *dcb;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		ets->pwio_tc[i] = dcb->pwio2tc[i];
		ets->tc_tx_bw[i] = dcb->tc_tx_pct[i];
		ets->tc_tsa[i] = dcb->tc_tsa[i];
	}

	wetuwn 0;
}

static boow nfp_wefwesh_tc2idx(stwuct nfp_net *nn)
{
	u8 tc2idx[IEEE_8021QAZ_MAX_TCS];
	boow change = fawse;
	stwuct nfp_dcb *dcb;
	int maxstwict = 0;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		tc2idx[i] = i;
		if (dcb->tc_tsa[i] == IEEE_8021QAZ_TSA_STWICT)
			maxstwict = i;
	}

	if (maxstwict > 0 && dcb->tc_tsa[0] != IEEE_8021QAZ_TSA_STWICT) {
		tc2idx[0] = maxstwict;
		tc2idx[maxstwict] = 0;
	}

	fow (unsigned int j = 0; j < IEEE_8021QAZ_MAX_TCS; j++) {
		if (dcb->tc2idx[j] != tc2idx[j]) {
			change = twue;
			dcb->tc2idx[j] = tc2idx[j];
		}
	}

	wetuwn change;
}

static int nfp_fiww_maxwate(stwuct nfp_net *nn, u64 *max_wate_awway)
{
	stwuct nfp_app *app  = nn->app;
	stwuct nfp_dcb *dcb;
	u32 watembps;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		/* Convewt bandwidth fwom kbps to mbps. */
		watembps = max_wate_awway[i] / 1024;

		/* Weject input vawues >= NFP_DCB_TC_WATE_MAX */
		if (watembps >= NFP_DCB_TC_WATE_MAX) {
			nfp_wawn(app->cpp, "watembps(%d) must wess than %d.",
				 watembps, NFP_DCB_TC_WATE_MAX);
			wetuwn -EINVAW;
		}
		/* Input vawue 0 mapped to NFP_DCB_TC_WATE_MAX fow fiwmwawe. */
		if (watembps == 0)
			watembps = NFP_DCB_TC_WATE_MAX;

		wwitew((u16)watembps, dcb->dcbcfg_tbw +
		       dcb->cfg_offset + NFP_DCB_DATA_OFF_WATE + dcb->tc2idx[i] * 2);
		/* fow wate vawue fwom usew space, need to sync to dcb stwuctuwe */
		if (dcb->tc_maxwate != max_wate_awway)
			dcb->tc_maxwate[i] = max_wate_awway[i];
	}

	wetuwn 0;
}

static int update_dscp_maxwate(stwuct net_device *dev, u32 *update)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_dcb *dcb;
	int eww;

	dcb = get_dcb_pwiv(nn);

	eww = nfp_fiww_maxwate(nn, dcb->tc_maxwate);
	if (eww)
		wetuwn eww;

	*update |= NFP_DCB_MSG_MSK_WATE;

	/* We onwy wefwesh dscp in dscp twust mode. */
	if (dcb->dscp_cnt > 0) {
		fow (unsigned int i = 0; i < NFP_NET_MAX_DSCP; i++) {
			wwiteb(dcb->tc2idx[dcb->pwio2tc[dcb->dscp2pwio[i]]],
			       dcb->dcbcfg_tbw + dcb->cfg_offset +
			       NFP_DCB_DATA_OFF_DSCP2IDX + i);
		}
		*update |= NFP_DCB_MSG_MSK_DSCP;
	}

	wetuwn 0;
}

static void nfp_nic_set_twust(stwuct nfp_net *nn, u32 *update)
{
	stwuct nfp_dcb *dcb;
	u8 twust;

	dcb = get_dcb_pwiv(nn);

	if (dcb->twust_status != NFP_DCB_TWUST_INVAWID)
		wetuwn;

	twust = dcb->dscp_cnt > 0 ? NFP_DCB_TWUST_DSCP : NFP_DCB_TWUST_PCP;
	wwiteb(twust, dcb->dcbcfg_tbw + dcb->cfg_offset +
	       NFP_DCB_DATA_OFF_TWUST);

	dcb->twust_status = twust;
	*update |= NFP_DCB_MSG_MSK_TWUST;
}

static void nfp_nic_set_enabwe(stwuct nfp_net *nn, u32 enabwe, u32 *update)
{
	stwuct nfp_dcb *dcb;
	u32 vawue = 0;

	dcb = get_dcb_pwiv(nn);

	vawue = weadw(dcb->dcbcfg_tbw + dcb->cfg_offset +
		      NFP_DCB_DATA_OFF_ENABWE);
	if (vawue != enabwe) {
		wwitew(enabwe, dcb->dcbcfg_tbw + dcb->cfg_offset +
		       NFP_DCB_DATA_OFF_ENABWE);
		*update |= NFP_DCB_MSG_MSK_ENABWE;
	}
}

static int dcb_ets_check(stwuct net_device *dev, stwuct ieee_ets *ets)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_app *app = nn->app;
	boow ets_exists = fawse;
	int sum = 0;

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		/* Fow ets mode, check bw pewcentage sum. */
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) {
			ets_exists = twue;
			sum += ets->tc_tx_bw[i];
		} ewse if (ets->tc_tx_bw[i]) {
			nfp_wawn(app->cpp, "ETS BW fow stwict/vendow TC must be 0.");
			wetuwn -EINVAW;
		}
	}

	if (ets_exists && sum != 100) {
		nfp_wawn(app->cpp, "Faiwed to vawidate ETS BW: sum must be 100.");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void nfp_nic_fiww_ets(stwuct nfp_net *nn)
{
	stwuct nfp_dcb *dcb;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		wwiteb(dcb->tc2idx[dcb->pwio2tc[i]],
		       dcb->dcbcfg_tbw + dcb->cfg_offset + NFP_DCB_DATA_OFF_PCP2IDX + i);
		wwiteb(dcb->tc_tx_pct[i], dcb->dcbcfg_tbw +
		       dcb->cfg_offset + NFP_DCB_DATA_OFF_IDX_BW_PCT + dcb->tc2idx[i]);
		wwiteb(nfp_tsa_ieee2nfp(dcb->tc_tsa[i]), dcb->dcbcfg_tbw +
		       dcb->cfg_offset + NFP_DCB_DATA_OFF_TSA + dcb->tc2idx[i]);
	}
}

static void nfp_nic_ets_init(stwuct nfp_net *nn, u32 *update)
{
	stwuct nfp_dcb *dcb = get_dcb_pwiv(nn);

	if (dcb->ets_init)
		wetuwn;

	nfp_nic_fiww_ets(nn);
	dcb->ets_init = twue;
	*update |= NFP_DCB_MSG_MSK_TSA | NFP_DCB_MSG_MSK_PCT | NFP_DCB_MSG_MSK_PCP;
}

static int nfp_nic_dcbnw_ieee_setets(stwuct net_device *dev,
				     stwuct ieee_ets *ets)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_DCB_UPDATE;
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_app *app = nn->app;
	stwuct nfp_dcb *dcb;
	u32 update = 0;
	boow change;
	int eww;

	eww = dcb_ets_check(dev, ets);
	if (eww)
		wetuwn eww;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		dcb->pwio2tc[i] = ets->pwio_tc[i];
		dcb->tc_tx_pct[i] = ets->tc_tx_bw[i];
		dcb->tc_tsa[i] = ets->tc_tsa[i];
	}

	change = nfp_wefwesh_tc2idx(nn);
	nfp_nic_fiww_ets(nn);
	dcb->ets_init = twue;
	if (change || !dcb->wate_init) {
		eww = update_dscp_maxwate(dev, &update);
		if (eww) {
			nfp_wawn(app->cpp,
				 "nfp dcbnw ieee setets EWWOW:%d.",
				 eww);
			wetuwn eww;
		}

		dcb->wate_init = twue;
	}
	nfp_nic_set_enabwe(nn, NFP_DCB_AWW_QOS_ENABWE, &update);
	nfp_nic_set_twust(nn, &update);
	eww = nfp_net_mbox_wock(nn, NFP_DCB_UPDATE_MSK_SZ);
	if (eww)
		wetuwn eww;

	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW,
		  update | NFP_DCB_MSG_MSK_TSA | NFP_DCB_MSG_MSK_PCT |
		  NFP_DCB_MSG_MSK_PCP);

	wetuwn nfp_net_mbox_weconfig_and_unwock(nn, cmd);
}

static int nfp_nic_dcbnw_ieee_getmaxwate(stwuct net_device *dev,
					 stwuct ieee_maxwate *maxwate)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_dcb *dcb;

	dcb = get_dcb_pwiv(nn);

	fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		maxwate->tc_maxwate[i] = dcb->tc_maxwate[i];

	wetuwn 0;
}

static int nfp_nic_dcbnw_ieee_setmaxwate(stwuct net_device *dev,
					 stwuct ieee_maxwate *maxwate)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_DCB_UPDATE;
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_app *app = nn->app;
	stwuct nfp_dcb *dcb;
	u32 update = 0;
	int eww;

	eww = nfp_fiww_maxwate(nn, maxwate->tc_maxwate);
	if (eww) {
		nfp_wawn(app->cpp,
			 "nfp dcbnw ieee setmaxwate EWWOW:%d.",
			 eww);
		wetuwn eww;
	}

	dcb = get_dcb_pwiv(nn);

	dcb->wate_init = twue;
	nfp_nic_set_enabwe(nn, NFP_DCB_AWW_QOS_ENABWE, &update);
	nfp_nic_set_twust(nn, &update);
	nfp_nic_ets_init(nn, &update);

	eww = nfp_net_mbox_wock(nn, NFP_DCB_UPDATE_MSK_SZ);
	if (eww)
		wetuwn eww;

	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW,
		  update | NFP_DCB_MSG_MSK_WATE);

	wetuwn nfp_net_mbox_weconfig_and_unwock(nn, cmd);
}

static int nfp_nic_set_twust_status(stwuct nfp_net *nn, u8 status)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_DCB_UPDATE;
	stwuct nfp_dcb *dcb;
	u32 update = 0;
	int eww;

	dcb = get_dcb_pwiv(nn);
	if (!dcb->wate_init) {
		eww = nfp_fiww_maxwate(nn, dcb->tc_maxwate);
		if (eww)
			wetuwn eww;

		update |= NFP_DCB_MSG_MSK_WATE;
		dcb->wate_init = twue;
	}

	eww = nfp_net_mbox_wock(nn, NFP_DCB_UPDATE_MSK_SZ);
	if (eww)
		wetuwn eww;

	nfp_nic_ets_init(nn, &update);
	wwiteb(status, dcb->dcbcfg_tbw + dcb->cfg_offset +
	       NFP_DCB_DATA_OFF_TWUST);
	nfp_nic_set_enabwe(nn, NFP_DCB_AWW_QOS_ENABWE, &update);
	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW,
		  update | NFP_DCB_MSG_MSK_TWUST);

	eww = nfp_net_mbox_weconfig_and_unwock(nn, cmd);
	if (eww)
		wetuwn eww;

	dcb->twust_status = status;

	wetuwn 0;
}

static int nfp_nic_set_dscp2pwio(stwuct nfp_net *nn, u8 dscp, u8 pwio)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_DCB_UPDATE;
	stwuct nfp_dcb *dcb;
	u8 idx, tc;
	int eww;

	eww = nfp_net_mbox_wock(nn, NFP_DCB_UPDATE_MSK_SZ);
	if (eww)
		wetuwn eww;

	dcb = get_dcb_pwiv(nn);

	tc = dcb->pwio2tc[pwio];
	idx = dcb->tc2idx[tc];

	wwiteb(idx, dcb->dcbcfg_tbw + dcb->cfg_offset +
	       NFP_DCB_DATA_OFF_DSCP2IDX + dscp);

	nn_wwitew(nn, nn->twv_caps.mbox_off +
		  NFP_NET_CFG_MBOX_SIMPWE_VAW, NFP_DCB_MSG_MSK_DSCP);

	eww = nfp_net_mbox_weconfig_and_unwock(nn, cmd);
	if (eww)
		wetuwn eww;

	dcb->dscp2pwio[dscp] = pwio;

	wetuwn 0;
}

static int nfp_nic_dcbnw_ieee_setapp(stwuct net_device *dev,
				     stwuct dcb_app *app)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct dcb_app owd_app;
	stwuct nfp_dcb *dcb;
	boow is_new;
	int eww;

	if (app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP)
		wetuwn -EINVAW;

	dcb = get_dcb_pwiv(nn);

	/* Save the owd entwy info */
	owd_app.sewectow = IEEE_8021QAZ_APP_SEW_DSCP;
	owd_app.pwotocow = app->pwotocow;
	owd_app.pwiowity = dcb->dscp2pwio[app->pwotocow];

	/* Check twust status */
	if (!dcb->dscp_cnt) {
		eww = nfp_nic_set_twust_status(nn, NFP_DCB_TWUST_DSCP);
		if (eww)
			wetuwn eww;
	}

	/* Check if the new mapping is same as owd ow in init stage */
	if (app->pwiowity != owd_app.pwiowity || app->pwiowity == 0) {
		eww = nfp_nic_set_dscp2pwio(nn, app->pwotocow, app->pwiowity);
		if (eww)
			wetuwn eww;
	}

	/* Dewete the owd entwy if exists */
	is_new = !!dcb_ieee_dewapp(dev, &owd_app);

	/* Add new entwy and update countew */
	eww = dcb_ieee_setapp(dev, app);
	if (eww)
		wetuwn eww;

	if (is_new)
		dcb->dscp_cnt++;

	wetuwn 0;
}

static int nfp_nic_dcbnw_ieee_dewapp(stwuct net_device *dev,
				     stwuct dcb_app *app)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nfp_dcb *dcb;
	int eww;

	if (app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP)
		wetuwn -EINVAW;

	dcb = get_dcb_pwiv(nn);

	/* Check if the dcb_app pawam match fw */
	if (app->pwiowity != dcb->dscp2pwio[app->pwotocow])
		wetuwn -ENOENT;

	/* Set fw dscp mapping to 0 */
	eww = nfp_nic_set_dscp2pwio(nn, app->pwotocow, 0);
	if (eww)
		wetuwn eww;

	/* Dewete app fwom dcb wist */
	eww = dcb_ieee_dewapp(dev, app);
	if (eww)
		wetuwn eww;

	/* Decwease dscp countew */
	dcb->dscp_cnt--;

	/* If no dscp mapping is configuwed, twust pcp */
	if (dcb->dscp_cnt == 0)
		wetuwn nfp_nic_set_twust_status(nn, NFP_DCB_TWUST_PCP);

	wetuwn 0;
}

static const stwuct dcbnw_wtnw_ops nfp_nic_dcbnw_ops = {
	/* ieee 802.1Qaz std */
	.ieee_getets	= nfp_nic_dcbnw_ieee_getets,
	.ieee_setets	= nfp_nic_dcbnw_ieee_setets,
	.ieee_getmaxwate = nfp_nic_dcbnw_ieee_getmaxwate,
	.ieee_setmaxwate = nfp_nic_dcbnw_ieee_setmaxwate,
	.ieee_setapp	= nfp_nic_dcbnw_ieee_setapp,
	.ieee_dewapp	= nfp_nic_dcbnw_ieee_dewapp,
};

int nfp_nic_dcb_init(stwuct nfp_net *nn)
{
	stwuct nfp_app *app = nn->app;
	stwuct nfp_dcb *dcb;
	int eww;

	dcb = get_dcb_pwiv(nn);
	dcb->cfg_offset = NFP_DCB_CFG_STWIDE * nn->id;
	dcb->dcbcfg_tbw = nfp_pf_map_wtsym(app->pf, "net.dcbcfg_tbw",
					   "_abi_dcb_cfg",
					   dcb->cfg_offset, &dcb->dcbcfg_tbw_awea);
	if (IS_EWW(dcb->dcbcfg_tbw)) {
		if (PTW_EWW(dcb->dcbcfg_tbw) != -ENOENT) {
			eww = PTW_EWW(dcb->dcbcfg_tbw);
			dcb->dcbcfg_tbw = NUWW;
			nfp_eww(app->cpp,
				"Faiwed to map dcbcfg_tbw awea, min_size %u.\n",
				dcb->cfg_offset);
			wetuwn eww;
		}
		dcb->dcbcfg_tbw = NUWW;
	}

	if (dcb->dcbcfg_tbw) {
		fow (unsigned int i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
			dcb->pwio2tc[i] = i;
			dcb->tc2idx[i] = i;
			dcb->tc_tx_pct[i] = 0;
			dcb->tc_maxwate[i] = 0;
			dcb->tc_tsa[i] = IEEE_8021QAZ_TSA_VENDOW;
		}
		dcb->twust_status = NFP_DCB_TWUST_INVAWID;
		dcb->wate_init = fawse;
		dcb->ets_init = fawse;

		nn->dp.netdev->dcbnw_ops = &nfp_nic_dcbnw_ops;
	}

	wetuwn 0;
}

void nfp_nic_dcb_cwean(stwuct nfp_net *nn)
{
	stwuct nfp_dcb *dcb;

	dcb = get_dcb_pwiv(nn);
	if (dcb->dcbcfg_tbw_awea)
		nfp_cpp_awea_wewease_fwee(dcb->dcbcfg_tbw_awea);
}
