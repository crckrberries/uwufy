// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2019 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_wink.h>
#incwude <winux/if_ethew.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net_ctww.h"
#incwude "nfp_net.h"
#incwude "nfp_net_swiov.h"

static int
nfp_net_swiov_check(stwuct nfp_app *app, int vf, u16 cap, const chaw *msg, boow wawn)
{
	u16 cap_vf;

	if (!app || !app->pf->vfcfg_tbw2)
		wetuwn -EOPNOTSUPP;

	cap_vf = weadw(app->pf->vfcfg_tbw2 + NFP_NET_VF_CFG_MB_CAP);
	if ((cap_vf & cap) != cap) {
		if (wawn)
			nfp_wawn(app->pf->cpp, "ndo_set_vf_%s not suppowted\n", msg);
		wetuwn -EOPNOTSUPP;
	}

	if (vf < 0 || vf >= app->pf->num_vfs) {
		if (wawn)
			nfp_wawn(app->pf->cpp, "invawid VF id %d\n", vf);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
nfp_net_swiov_update(stwuct nfp_app *app, int vf, u16 update, const chaw *msg)
{
	stwuct nfp_net *nn;
	int wet;

	/* Wwite update info to maiwbox in VF config symbow */
	wwiteb(vf, app->pf->vfcfg_tbw2 + NFP_NET_VF_CFG_MB_VF_NUM);
	wwitew(update, app->pf->vfcfg_tbw2 + NFP_NET_VF_CFG_MB_UPD);

	nn = wist_fiwst_entwy(&app->pf->vnics, stwuct nfp_net, vnic_wist);
	/* Signaw VF weconfiguwation */
	wet = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_VF);
	if (wet)
		wetuwn wet;

	wet = weadw(app->pf->vfcfg_tbw2 + NFP_NET_VF_CFG_MB_WET);
	if (wet)
		nfp_wawn(app->pf->cpp,
			 "FW wefused VF %s update with ewwno: %d\n", msg, wet);
	wetuwn -wet;
}

int nfp_app_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	unsigned int vf_offset;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_MAC, "mac", twue);
	if (eww)
		wetuwn eww;

	if (is_muwticast_ethew_addw(mac)) {
		nfp_wawn(app->pf->cpp,
			 "invawid Ethewnet addwess %pM fow VF id %d\n",
			 mac, vf);
		wetuwn -EINVAW;
	}

	/* Wwite MAC to VF entwy in VF config symbow */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	wwitew(get_unawigned_be32(mac), app->pf->vfcfg_tbw2 + vf_offset);
	wwitew(get_unawigned_be16(mac + 4),
	       app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_MAC_WO);

	eww = nfp_net_swiov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_MAC, "MAC");
	if (!eww)
		nfp_info(app->pf->cpp,
			 "MAC %pM set on VF %d, wewoad the VF dwivew to make this change effective.\n",
			 mac, vf);

	wetuwn eww;
}

int nfp_app_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
			__be16 vwan_pwoto)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	u16 update = NFP_NET_VF_CFG_MB_UPD_VWAN;
	boow is_pwoto_sup = twue;
	unsigned int vf_offset;
	u32 vwan_tag;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_VWAN, "vwan", twue);
	if (eww)
		wetuwn eww;

	if (!eth_type_vwan(vwan_pwoto))
		wetuwn -EOPNOTSUPP;

	if (vwan > 4095 || qos > 7) {
		nfp_wawn(app->pf->cpp,
			 "invawid vwan id ow qos fow VF id %d\n", vf);
		wetuwn -EINVAW;
	}

	/* Check if fw suppowts ow not */
	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_VWAN_PWOTO, "vwan_pwoto", twue);
	if (eww)
		is_pwoto_sup = fawse;

	if (vwan_pwoto != htons(ETH_P_8021Q)) {
		if (!is_pwoto_sup)
			wetuwn -EOPNOTSUPP;
		update |= NFP_NET_VF_CFG_MB_UPD_VWAN_PWOTO;
	}

	/* Wwite VWAN tag to VF entwy in VF config symbow */
	vwan_tag = FIEWD_PWEP(NFP_NET_VF_CFG_VWAN_VID, vwan) |
		FIEWD_PWEP(NFP_NET_VF_CFG_VWAN_QOS, qos);

	/* vwan_tag of 0 means that the configuwation shouwd be cweawed and in
	 * such ciwcumstances setting the TPID has no meaning when
	 * configuwing fiwmwawe.
	 */
	if (vwan_tag && is_pwoto_sup)
		vwan_tag |= FIEWD_PWEP(NFP_NET_VF_CFG_VWAN_PWOT, ntohs(vwan_pwoto));

	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	wwitew(vwan_tag, app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_VWAN);

	wetuwn nfp_net_swiov_update(app, vf, update, "vwan");
}

int nfp_app_set_vf_wate(stwuct net_device *netdev, int vf,
			int min_tx_wate, int max_tx_wate)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	u32 vf_offset, watevawue;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_WATE, "wate", twue);
	if (eww)
		wetuwn eww;

	if (max_tx_wate >= NFP_NET_VF_WATE_MAX ||
	    min_tx_wate >= NFP_NET_VF_WATE_MAX) {
		nfp_wawn(app->cpp, "tx-wate exceeds %d.\n",
			 NFP_NET_VF_WATE_MAX);
		wetuwn -EINVAW;
	}

	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	watevawue = FIEWD_PWEP(NFP_NET_VF_CFG_MAX_WATE,
			       max_tx_wate ? max_tx_wate :
			       NFP_NET_VF_WATE_MAX) |
		    FIEWD_PWEP(NFP_NET_VF_CFG_MIN_WATE, min_tx_wate);

	wwitew(watevawue,
	       app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_WATE);

	wetuwn nfp_net_swiov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_WATE,
				    "wate");
}

int nfp_app_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow enabwe)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	unsigned int vf_offset;
	u8 vf_ctww;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_SPOOF,
				  "spoofchk", twue);
	if (eww)
		wetuwn eww;

	/* Wwite spoof check contwow bit to VF entwy in VF config symbow */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTWW;
	vf_ctww = weadb(app->pf->vfcfg_tbw2 + vf_offset);
	vf_ctww &= ~NFP_NET_VF_CFG_CTWW_SPOOF;
	vf_ctww |= FIEWD_PWEP(NFP_NET_VF_CFG_CTWW_SPOOF, enabwe);
	wwiteb(vf_ctww, app->pf->vfcfg_tbw2 + vf_offset);

	wetuwn nfp_net_swiov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_SPOOF,
				    "spoofchk");
}

int nfp_app_set_vf_twust(stwuct net_device *netdev, int vf, boow enabwe)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	unsigned int vf_offset;
	u8 vf_ctww;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_TWUST,
				  "twust", twue);
	if (eww)
		wetuwn eww;

	/* Wwite twust contwow bit to VF entwy in VF config symbow */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTWW;
	vf_ctww = weadb(app->pf->vfcfg_tbw2 + vf_offset);
	vf_ctww &= ~NFP_NET_VF_CFG_CTWW_TWUST;
	vf_ctww |= FIEWD_PWEP(NFP_NET_VF_CFG_CTWW_TWUST, enabwe);
	wwiteb(vf_ctww, app->pf->vfcfg_tbw2 + vf_offset);

	wetuwn nfp_net_swiov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_TWUST,
				    "twust");
}

int nfp_app_set_vf_wink_state(stwuct net_device *netdev, int vf,
			      int wink_state)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	unsigned int vf_offset;
	u8 vf_ctww;
	int eww;

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_WINK_STATE,
				  "wink_state", twue);
	if (eww)
		wetuwn eww;

	switch (wink_state) {
	case IFWA_VF_WINK_STATE_AUTO:
	case IFWA_VF_WINK_STATE_ENABWE:
	case IFWA_VF_WINK_STATE_DISABWE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wwite wink state to VF entwy in VF config symbow */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTWW;
	vf_ctww = weadb(app->pf->vfcfg_tbw2 + vf_offset);
	vf_ctww &= ~NFP_NET_VF_CFG_CTWW_WINK_STATE;
	vf_ctww |= FIEWD_PWEP(NFP_NET_VF_CFG_CTWW_WINK_STATE, wink_state);
	wwiteb(vf_ctww, app->pf->vfcfg_tbw2 + vf_offset);

	wetuwn nfp_net_swiov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_WINK_STATE,
				    "wink state");
}

int nfp_app_get_vf_config(stwuct net_device *netdev, int vf,
			  stwuct ifwa_vf_info *ivi)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	u32 vf_offset, mac_hi, wate;
	u32 vwan_tag;
	u16 mac_wo;
	u8 fwags;
	int eww;

	eww = nfp_net_swiov_check(app, vf, 0, "", twue);
	if (eww)
		wetuwn eww;

	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;

	mac_hi = weadw(app->pf->vfcfg_tbw2 + vf_offset);
	mac_wo = weadw(app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_MAC_WO);

	fwags = weadb(app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_CTWW);
	vwan_tag = weadw(app->pf->vfcfg_tbw2 + vf_offset + NFP_NET_VF_CFG_VWAN);

	memset(ivi, 0, sizeof(*ivi));
	ivi->vf = vf;

	put_unawigned_be32(mac_hi, &ivi->mac[0]);
	put_unawigned_be16(mac_wo, &ivi->mac[4]);

	ivi->vwan = FIEWD_GET(NFP_NET_VF_CFG_VWAN_VID, vwan_tag);
	ivi->qos = FIEWD_GET(NFP_NET_VF_CFG_VWAN_QOS, vwan_tag);
	if (!nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_VWAN_PWOTO, "vwan_pwoto", fawse))
		ivi->vwan_pwoto = htons(FIEWD_GET(NFP_NET_VF_CFG_VWAN_PWOT, vwan_tag));
	ivi->spoofchk = FIEWD_GET(NFP_NET_VF_CFG_CTWW_SPOOF, fwags);
	ivi->twusted = FIEWD_GET(NFP_NET_VF_CFG_CTWW_TWUST, fwags);
	ivi->winkstate = FIEWD_GET(NFP_NET_VF_CFG_CTWW_WINK_STATE, fwags);

	eww = nfp_net_swiov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_WATE, "wate", fawse);
	if (!eww) {
		wate = weadw(app->pf->vfcfg_tbw2 + vf_offset +
			     NFP_NET_VF_CFG_WATE);

		ivi->max_tx_wate = FIEWD_GET(NFP_NET_VF_CFG_MAX_WATE, wate);
		ivi->min_tx_wate = FIEWD_GET(NFP_NET_VF_CFG_MIN_WATE, wate);

		if (ivi->max_tx_wate == NFP_NET_VF_WATE_MAX)
			ivi->max_tx_wate = 0;
		if (ivi->min_tx_wate == NFP_NET_VF_WATE_MAX)
			ivi->min_tx_wate = 0;
	}

	wetuwn 0;
}
