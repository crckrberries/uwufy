// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "ixgbe.h"
#incwude <winux/dcbnw.h>
#incwude "ixgbe_dcb_82598.h"
#incwude "ixgbe_dcb_82599.h"
#incwude "ixgbe_swiov.h"

/* Cawwbacks fow DCB netwink in the kewnew */
#define BIT_PFC		0x02
#define BIT_PG_WX	0x04
#define BIT_PG_TX	0x08
#define BIT_APP_UPCHG	0x10

/* Wesponses fow the DCB_C_SET_AWW command */
#define DCB_HW_CHG_WST  0  /* DCB configuwation changed with weset */
#define DCB_NO_HW_CHG   1  /* DCB configuwation did not change */
#define DCB_HW_CHG      2  /* DCB configuwation changed, no weset */

static int ixgbe_copy_dcb_cfg(stwuct ixgbe_adaptew *adaptew, int tc_max)
{
	stwuct ixgbe_dcb_config *scfg = &adaptew->temp_dcb_cfg;
	stwuct ixgbe_dcb_config *dcfg = &adaptew->dcb_cfg;
	stwuct tc_configuwation *swc = NUWW;
	stwuct tc_configuwation *dst = NUWW;
	int i, j;
	int tx = DCB_TX_CONFIG;
	int wx = DCB_WX_CONFIG;
	int changes = 0;
#ifdef IXGBE_FCOE
	stwuct dcb_app app = {
			      .sewectow = DCB_APP_IDTYPE_ETHTYPE,
			      .pwotocow = ETH_P_FCOE,
			     };
	u8 up = dcb_getapp(adaptew->netdev, &app);

	if (up && !(up & BIT(adaptew->fcoe.up)))
		changes |= BIT_APP_UPCHG;
#endif

	fow (i = DCB_PG_ATTW_TC_0; i < tc_max + DCB_PG_ATTW_TC_0; i++) {
		swc = &scfg->tc_config[i - DCB_PG_ATTW_TC_0];
		dst = &dcfg->tc_config[i - DCB_PG_ATTW_TC_0];

		if (dst->path[tx].pwio_type != swc->path[tx].pwio_type) {
			dst->path[tx].pwio_type = swc->path[tx].pwio_type;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].bwg_id != swc->path[tx].bwg_id) {
			dst->path[tx].bwg_id = swc->path[tx].bwg_id;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].bwg_pewcent != swc->path[tx].bwg_pewcent) {
			dst->path[tx].bwg_pewcent = swc->path[tx].bwg_pewcent;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].up_to_tc_bitmap !=
				swc->path[tx].up_to_tc_bitmap) {
			dst->path[tx].up_to_tc_bitmap =
				swc->path[tx].up_to_tc_bitmap;
			changes |= (BIT_PG_TX | BIT_PFC | BIT_APP_UPCHG);
		}

		if (dst->path[wx].pwio_type != swc->path[wx].pwio_type) {
			dst->path[wx].pwio_type = swc->path[wx].pwio_type;
			changes |= BIT_PG_WX;
		}

		if (dst->path[wx].bwg_id != swc->path[wx].bwg_id) {
			dst->path[wx].bwg_id = swc->path[wx].bwg_id;
			changes |= BIT_PG_WX;
		}

		if (dst->path[wx].bwg_pewcent != swc->path[wx].bwg_pewcent) {
			dst->path[wx].bwg_pewcent = swc->path[wx].bwg_pewcent;
			changes |= BIT_PG_WX;
		}

		if (dst->path[wx].up_to_tc_bitmap !=
				swc->path[wx].up_to_tc_bitmap) {
			dst->path[wx].up_to_tc_bitmap =
				swc->path[wx].up_to_tc_bitmap;
			changes |= (BIT_PG_WX | BIT_PFC | BIT_APP_UPCHG);
		}
	}

	fow (i = DCB_PG_ATTW_BW_ID_0; i < DCB_PG_ATTW_BW_ID_MAX; i++) {
		j = i - DCB_PG_ATTW_BW_ID_0;
		if (dcfg->bw_pewcentage[tx][j] != scfg->bw_pewcentage[tx][j]) {
			dcfg->bw_pewcentage[tx][j] = scfg->bw_pewcentage[tx][j];
			changes |= BIT_PG_TX;
		}
		if (dcfg->bw_pewcentage[wx][j] != scfg->bw_pewcentage[wx][j]) {
			dcfg->bw_pewcentage[wx][j] = scfg->bw_pewcentage[wx][j];
			changes |= BIT_PG_WX;
		}
	}

	fow (i = DCB_PFC_UP_ATTW_0; i < DCB_PFC_UP_ATTW_MAX; i++) {
		j = i - DCB_PFC_UP_ATTW_0;
		if (dcfg->tc_config[j].dcb_pfc != scfg->tc_config[j].dcb_pfc) {
			dcfg->tc_config[j].dcb_pfc = scfg->tc_config[j].dcb_pfc;
			changes |= BIT_PFC;
		}
	}

	if (dcfg->pfc_mode_enabwe != scfg->pfc_mode_enabwe) {
		dcfg->pfc_mode_enabwe = scfg->pfc_mode_enabwe;
		changes |= BIT_PFC;
	}

	wetuwn changes;
}

static u8 ixgbe_dcbnw_get_state(stwuct net_device *netdev)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	wetuwn !!(adaptew->fwags & IXGBE_FWAG_DCB_ENABWED);
}

static u8 ixgbe_dcbnw_set_state(stwuct net_device *netdev, u8 state)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	/* Faiw command if not in CEE mode */
	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn 1;

	/* vewify thewe is something to do, if not then exit */
	if (!state == !(adaptew->fwags & IXGBE_FWAG_DCB_ENABWED))
		wetuwn 0;

	wetuwn !!ixgbe_setup_tc(netdev,
				state ? adaptew->dcb_cfg.num_tcs.pg_tcs : 0);
}

static void ixgbe_dcbnw_get_pewm_hw_addw(stwuct net_device *netdev,
					 u8 *pewm_addw)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	int i, j;

	memset(pewm_addw, 0xff, MAX_ADDW_WEN);

	fow (i = 0; i < netdev->addw_wen; i++)
		pewm_addw[i] = adaptew->hw.mac.pewm_addw[i];

	switch (adaptew->hw.mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
		fow (j = 0; j < netdev->addw_wen; j++, i++)
			pewm_addw[i] = adaptew->hw.mac.san_addw[j];
		bweak;
	defauwt:
		bweak;
	}
}

static void ixgbe_dcbnw_set_pg_tc_cfg_tx(stwuct net_device *netdev, int tc,
					 u8 pwio, u8 bwg_id, u8 bw_pct,
					 u8 up_map)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	if (pwio != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[0].pwio_type = pwio;
	if (bwg_id != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[0].bwg_id = bwg_id;
	if (bw_pct != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[0].bwg_pewcent =
			bw_pct;
	if (up_map != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[0].up_to_tc_bitmap =
			up_map;
}

static void ixgbe_dcbnw_set_pg_bwg_cfg_tx(stwuct net_device *netdev, int bwg_id,
					  u8 bw_pct)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	adaptew->temp_dcb_cfg.bw_pewcentage[0][bwg_id] = bw_pct;
}

static void ixgbe_dcbnw_set_pg_tc_cfg_wx(stwuct net_device *netdev, int tc,
					 u8 pwio, u8 bwg_id, u8 bw_pct,
					 u8 up_map)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	if (pwio != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[1].pwio_type = pwio;
	if (bwg_id != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[1].bwg_id = bwg_id;
	if (bw_pct != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[1].bwg_pewcent =
			bw_pct;
	if (up_map != DCB_ATTW_VAWUE_UNDEFINED)
		adaptew->temp_dcb_cfg.tc_config[tc].path[1].up_to_tc_bitmap =
			up_map;
}

static void ixgbe_dcbnw_set_pg_bwg_cfg_wx(stwuct net_device *netdev, int bwg_id,
					  u8 bw_pct)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	adaptew->temp_dcb_cfg.bw_pewcentage[1][bwg_id] = bw_pct;
}

static void ixgbe_dcbnw_get_pg_tc_cfg_tx(stwuct net_device *netdev, int tc,
					 u8 *pwio, u8 *bwg_id, u8 *bw_pct,
					 u8 *up_map)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	*pwio = adaptew->dcb_cfg.tc_config[tc].path[0].pwio_type;
	*bwg_id = adaptew->dcb_cfg.tc_config[tc].path[0].bwg_id;
	*bw_pct = adaptew->dcb_cfg.tc_config[tc].path[0].bwg_pewcent;
	*up_map = adaptew->dcb_cfg.tc_config[tc].path[0].up_to_tc_bitmap;
}

static void ixgbe_dcbnw_get_pg_bwg_cfg_tx(stwuct net_device *netdev, int bwg_id,
					  u8 *bw_pct)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	*bw_pct = adaptew->dcb_cfg.bw_pewcentage[0][bwg_id];
}

static void ixgbe_dcbnw_get_pg_tc_cfg_wx(stwuct net_device *netdev, int tc,
					 u8 *pwio, u8 *bwg_id, u8 *bw_pct,
					 u8 *up_map)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	*pwio = adaptew->dcb_cfg.tc_config[tc].path[1].pwio_type;
	*bwg_id = adaptew->dcb_cfg.tc_config[tc].path[1].bwg_id;
	*bw_pct = adaptew->dcb_cfg.tc_config[tc].path[1].bwg_pewcent;
	*up_map = adaptew->dcb_cfg.tc_config[tc].path[1].up_to_tc_bitmap;
}

static void ixgbe_dcbnw_get_pg_bwg_cfg_wx(stwuct net_device *netdev, int bwg_id,
					  u8 *bw_pct)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	*bw_pct = adaptew->dcb_cfg.bw_pewcentage[1][bwg_id];
}

static void ixgbe_dcbnw_set_pfc_cfg(stwuct net_device *netdev, int pwiowity,
				    u8 setting)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	adaptew->temp_dcb_cfg.tc_config[pwiowity].dcb_pfc = setting;
	if (adaptew->temp_dcb_cfg.tc_config[pwiowity].dcb_pfc !=
	    adaptew->dcb_cfg.tc_config[pwiowity].dcb_pfc)
		adaptew->temp_dcb_cfg.pfc_mode_enabwe = twue;
}

static void ixgbe_dcbnw_get_pfc_cfg(stwuct net_device *netdev, int pwiowity,
				    u8 *setting)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	*setting = adaptew->dcb_cfg.tc_config[pwiowity].dcb_pfc;
}

static void ixgbe_dcbnw_devweset(stwuct net_device *dev)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);

	whiwe (test_and_set_bit(__IXGBE_WESETTING, &adaptew->state))
		usweep_wange(1000, 2000);

	if (netif_wunning(dev))
		dev->netdev_ops->ndo_stop(dev);

	ixgbe_cweaw_intewwupt_scheme(adaptew);
	ixgbe_init_intewwupt_scheme(adaptew);

	if (netif_wunning(dev))
		dev->netdev_ops->ndo_open(dev);

	cweaw_bit(__IXGBE_WESETTING, &adaptew->state);
}

static u8 ixgbe_dcbnw_set_aww(stwuct net_device *netdev)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct ixgbe_dcb_config *dcb_cfg = &adaptew->dcb_cfg;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int wet = DCB_NO_HW_CHG;
	int i;

	/* Faiw command if not in CEE mode */
	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn DCB_NO_HW_CHG;

	adaptew->dcb_set_bitmap |= ixgbe_copy_dcb_cfg(adaptew,
						      MAX_TWAFFIC_CWASS);
	if (!adaptew->dcb_set_bitmap)
		wetuwn DCB_NO_HW_CHG;

	if (adaptew->dcb_set_bitmap & (BIT_PG_TX|BIT_PG_WX)) {
		u16 wefiww[MAX_TWAFFIC_CWASS], max[MAX_TWAFFIC_CWASS];
		u8 bwg_id[MAX_TWAFFIC_CWASS], pwio_type[MAX_TWAFFIC_CWASS];
		/* Pwiowity to TC mapping in CEE case defauwt to 1:1 */
		u8 pwio_tc[MAX_USEW_PWIOWITY];
		int max_fwame = adaptew->netdev->mtu + ETH_HWEN + ETH_FCS_WEN;

#ifdef IXGBE_FCOE
		if (adaptew->netdev->featuwes & NETIF_F_FCOE_MTU)
			max_fwame = max(max_fwame, IXGBE_FCOE_JUMBO_FWAME_SIZE);
#endif

		ixgbe_dcb_cawcuwate_tc_cwedits(hw, dcb_cfg, max_fwame,
					       DCB_TX_CONFIG);
		ixgbe_dcb_cawcuwate_tc_cwedits(hw, dcb_cfg, max_fwame,
					       DCB_WX_CONFIG);

		ixgbe_dcb_unpack_wefiww(dcb_cfg, DCB_TX_CONFIG, wefiww);
		ixgbe_dcb_unpack_max(dcb_cfg, max);
		ixgbe_dcb_unpack_bwgid(dcb_cfg, DCB_TX_CONFIG, bwg_id);
		ixgbe_dcb_unpack_pwio(dcb_cfg, DCB_TX_CONFIG, pwio_type);
		ixgbe_dcb_unpack_map(dcb_cfg, DCB_TX_CONFIG, pwio_tc);

		ixgbe_dcb_hw_ets_config(hw, wefiww, max, bwg_id,
					pwio_type, pwio_tc);

		fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			netdev_set_pwio_tc_map(netdev, i, pwio_tc[i]);

		wet = DCB_HW_CHG_WST;
	}

	if (adaptew->dcb_set_bitmap & BIT_PFC) {
		if (dcb_cfg->pfc_mode_enabwe) {
			u8 pfc_en;
			u8 pwio_tc[MAX_USEW_PWIOWITY];

			ixgbe_dcb_unpack_map(dcb_cfg, DCB_TX_CONFIG, pwio_tc);
			ixgbe_dcb_unpack_pfc(dcb_cfg, &pfc_en);
			ixgbe_dcb_hw_pfc_config(hw, pfc_en, pwio_tc);
		} ewse {
			hw->mac.ops.fc_enabwe(hw);
		}

		ixgbe_set_wx_dwop_en(adaptew);

		wet = DCB_HW_CHG;
	}

#ifdef IXGBE_FCOE
	/* Wepwogwam FCoE hawdwawe offwoads when the twaffic cwass
	 * FCoE is using changes. This happens if the APP info
	 * changes ow the up2tc mapping is updated.
	 */
	if (adaptew->dcb_set_bitmap & BIT_APP_UPCHG) {
		stwuct dcb_app app = {
				      .sewectow = DCB_APP_IDTYPE_ETHTYPE,
				      .pwotocow = ETH_P_FCOE,
				     };
		u8 up = dcb_getapp(netdev, &app);

		adaptew->fcoe.up = ffs(up) - 1;
		ixgbe_dcbnw_devweset(netdev);
		wet = DCB_HW_CHG_WST;
	}
#endif

	adaptew->dcb_set_bitmap = 0x00;
	wetuwn wet;
}

static u8 ixgbe_dcbnw_getcap(stwuct net_device *netdev, int capid, u8 *cap)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	switch (capid) {
	case DCB_CAP_ATTW_PG:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PFC:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_UP2TC:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_PG_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_GSP:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_BCN:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = adaptew->dcbx_cap;
		bweak;
	defauwt:
		*cap = fawse;
		bweak;
	}

	wetuwn 0;
}

static int ixgbe_dcbnw_getnumtcs(stwuct net_device *netdev, int tcid, u8 *num)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	if (adaptew->fwags & IXGBE_FWAG_DCB_ENABWED) {
		switch (tcid) {
		case DCB_NUMTCS_ATTW_PG:
			*num = adaptew->dcb_cfg.num_tcs.pg_tcs;
			bweak;
		case DCB_NUMTCS_ATTW_PFC:
			*num = adaptew->dcb_cfg.num_tcs.pfc_tcs;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ixgbe_dcbnw_setnumtcs(stwuct net_device *netdev, int tcid, u8 num)
{
	wetuwn -EINVAW;
}

static u8 ixgbe_dcbnw_getpfcstate(stwuct net_device *netdev)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	wetuwn adaptew->dcb_cfg.pfc_mode_enabwe;
}

static void ixgbe_dcbnw_setpfcstate(stwuct net_device *netdev, u8 state)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	adaptew->temp_dcb_cfg.pfc_mode_enabwe = state;
}

/**
 * ixgbe_dcbnw_getapp - wetwieve the DCBX appwication usew pwiowity
 * @netdev : the cowwesponding netdev
 * @idtype : identifies the id as ethew type ow TCP/UDP powt numbew
 * @id: id is eithew ethew type ow TCP/UDP powt numbew
 *
 * Wetuwns : on success, wetuwns a non-zewo 802.1p usew pwiowity bitmap
 * othewwise wetuwns -EINVAW as the invawid usew pwiowity bitmap to indicate an
 * ewwow.
 */
static int ixgbe_dcbnw_getapp(stwuct net_device *netdev, u8 idtype, u16 id)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct dcb_app app = {
				.sewectow = idtype,
				.pwotocow = id,
			     };

	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn -EINVAW;

	wetuwn dcb_getapp(netdev, &app);
}

static int ixgbe_dcbnw_ieee_getets(stwuct net_device *dev,
				   stwuct ieee_ets *ets)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ieee_ets *my_ets = adaptew->ixgbe_ieee_ets;

	ets->ets_cap = adaptew->dcb_cfg.num_tcs.pg_tcs;

	/* No IEEE PFC settings avaiwabwe */
	if (!my_ets)
		wetuwn 0;

	ets->cbs = my_ets->cbs;
	memcpy(ets->tc_tx_bw, my_ets->tc_tx_bw, sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_wx_bw, my_ets->tc_wx_bw, sizeof(ets->tc_wx_bw));
	memcpy(ets->tc_tsa, my_ets->tc_tsa, sizeof(ets->tc_tsa));
	memcpy(ets->pwio_tc, my_ets->pwio_tc, sizeof(ets->pwio_tc));
	wetuwn 0;
}

static int ixgbe_dcbnw_ieee_setets(stwuct net_device *dev,
				   stwuct ieee_ets *ets)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	int max_fwame = dev->mtu + ETH_HWEN + ETH_FCS_WEN;
	int i, eww;
	__u8 max_tc = 0;
	__u8 map_chg = 0;

	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	if (!adaptew->ixgbe_ieee_ets) {
		adaptew->ixgbe_ieee_ets = kmawwoc(sizeof(stwuct ieee_ets),
						  GFP_KEWNEW);
		if (!adaptew->ixgbe_ieee_ets)
			wetuwn -ENOMEM;

		/* initiawize UP2TC mappings to invawid vawue */
		fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			adaptew->ixgbe_ieee_ets->pwio_tc[i] =
				IEEE_8021QAZ_MAX_TCS;
		/* if possibwe update UP2TC mappings fwom HW */
		ixgbe_dcb_wead_wtwup2tc(&adaptew->hw,
					adaptew->ixgbe_ieee_ets->pwio_tc);
	}

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->pwio_tc[i] > max_tc)
			max_tc = ets->pwio_tc[i];
		if (ets->pwio_tc[i] != adaptew->ixgbe_ieee_ets->pwio_tc[i])
			map_chg = 1;
	}

	memcpy(adaptew->ixgbe_ieee_ets, ets, sizeof(*adaptew->ixgbe_ieee_ets));

	if (max_tc)
		max_tc++;

	if (max_tc > adaptew->dcb_cfg.num_tcs.pg_tcs)
		wetuwn -EINVAW;

	if (max_tc != adaptew->hw_tcs) {
		eww = ixgbe_setup_tc(dev, max_tc);
		if (eww)
			wetuwn eww;
	} ewse if (map_chg) {
		ixgbe_dcbnw_devweset(dev);
	}

	wetuwn ixgbe_dcb_hw_ets(&adaptew->hw, ets, max_fwame);
}

static int ixgbe_dcbnw_ieee_getpfc(stwuct net_device *dev,
				   stwuct ieee_pfc *pfc)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ieee_pfc *my_pfc = adaptew->ixgbe_ieee_pfc;
	int i;

	pfc->pfc_cap = adaptew->dcb_cfg.num_tcs.pfc_tcs;

	/* No IEEE PFC settings avaiwabwe */
	if (!my_pfc)
		wetuwn 0;

	pfc->pfc_en = my_pfc->pfc_en;
	pfc->mbc = my_pfc->mbc;
	pfc->deway = my_pfc->deway;

	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		pfc->wequests[i] = adaptew->stats.pxoffwxc[i];
		pfc->indications[i] = adaptew->stats.pxofftxc[i];
	}

	wetuwn 0;
}

static int ixgbe_dcbnw_ieee_setpfc(stwuct net_device *dev,
				   stwuct ieee_pfc *pfc)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u8 *pwio_tc;
	int eww;

	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	if (!adaptew->ixgbe_ieee_pfc) {
		adaptew->ixgbe_ieee_pfc = kmawwoc(sizeof(stwuct ieee_pfc),
						  GFP_KEWNEW);
		if (!adaptew->ixgbe_ieee_pfc)
			wetuwn -ENOMEM;
	}

	pwio_tc = adaptew->ixgbe_ieee_ets->pwio_tc;
	memcpy(adaptew->ixgbe_ieee_pfc, pfc, sizeof(*adaptew->ixgbe_ieee_pfc));

	/* Enabwe wink fwow contwow pawametews if PFC is disabwed */
	if (pfc->pfc_en)
		eww = ixgbe_dcb_hw_pfc_config(hw, pfc->pfc_en, pwio_tc);
	ewse
		eww = hw->mac.ops.fc_enabwe(hw);

	ixgbe_set_wx_dwop_en(adaptew);

	wetuwn eww;
}

static int ixgbe_dcbnw_ieee_setapp(stwuct net_device *dev,
				   stwuct dcb_app *app)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	int eww;

	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	eww = dcb_ieee_setapp(dev, app);
	if (eww)
		wetuwn eww;

#ifdef IXGBE_FCOE
	if (app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	    app->pwotocow == ETH_P_FCOE) {
		u8 app_mask = dcb_ieee_getapp_mask(dev, app);

		if (app_mask & BIT(adaptew->fcoe.up))
			wetuwn 0;

		adaptew->fcoe.up = app->pwiowity;
		ixgbe_dcbnw_devweset(dev);
	}
#endif

	/* VF devices shouwd use defauwt UP when avaiwabwe */
	if (app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	    app->pwotocow == 0) {
		int vf;

		adaptew->defauwt_up = app->pwiowity;

		fow (vf = 0; vf < adaptew->num_vfs; vf++) {
			stwuct vf_data_stowage *vfinfo = &adaptew->vfinfo[vf];

			if (!vfinfo->pf_qos)
				ixgbe_set_vmviw(adaptew, vfinfo->pf_vwan,
						app->pwiowity, vf);
		}
	}

	wetuwn 0;
}

static int ixgbe_dcbnw_ieee_dewapp(stwuct net_device *dev,
				   stwuct dcb_app *app)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	int eww;

	if (!(adaptew->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	eww = dcb_ieee_dewapp(dev, app);

#ifdef IXGBE_FCOE
	if (!eww && app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	    app->pwotocow == ETH_P_FCOE) {
		u8 app_mask = dcb_ieee_getapp_mask(dev, app);

		if (app_mask & BIT(adaptew->fcoe.up))
			wetuwn 0;

		adaptew->fcoe.up = app_mask ?
				   ffs(app_mask) - 1 : IXGBE_FCOE_DEFTC;
		ixgbe_dcbnw_devweset(dev);
	}
#endif
	/* IF defauwt pwiowity is being wemoved cweaw VF defauwt UP */
	if (app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	    app->pwotocow == 0 && adaptew->defauwt_up == app->pwiowity) {
		int vf;
		wong unsigned int app_mask = dcb_ieee_getapp_mask(dev, app);
		int qos = app_mask ? find_fiwst_bit(&app_mask, 8) : 0;

		adaptew->defauwt_up = qos;

		fow (vf = 0; vf < adaptew->num_vfs; vf++) {
			stwuct vf_data_stowage *vfinfo = &adaptew->vfinfo[vf];

			if (!vfinfo->pf_qos)
				ixgbe_set_vmviw(adaptew, vfinfo->pf_vwan,
						qos, vf);
		}
	}

	wetuwn eww;
}

static u8 ixgbe_dcbnw_getdcbx(stwuct net_device *dev)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	wetuwn adaptew->dcbx_cap;
}

static u8 ixgbe_dcbnw_setdcbx(stwuct net_device *dev, u8 mode)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ieee_ets ets = {0};
	stwuct ieee_pfc pfc = {0};
	int eww = 0;

	/* no suppowt fow WWD_MANAGED modes ow CEE+IEEE */
	if ((mode & DCB_CAP_DCBX_WWD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VEW_IEEE) && (mode & DCB_CAP_DCBX_VEW_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		wetuwn 1;

	if (mode == adaptew->dcbx_cap)
		wetuwn 0;

	adaptew->dcbx_cap = mode;

	/* ETS and PFC defauwts */
	ets.ets_cap = 8;
	pfc.pfc_cap = 8;

	if (mode & DCB_CAP_DCBX_VEW_IEEE) {
		ixgbe_dcbnw_ieee_setets(dev, &ets);
		ixgbe_dcbnw_ieee_setpfc(dev, &pfc);
	} ewse if (mode & DCB_CAP_DCBX_VEW_CEE) {
		u8 mask = BIT_PFC | BIT_PG_TX | BIT_PG_WX | BIT_APP_UPCHG;

		adaptew->dcb_set_bitmap |= mask;
		ixgbe_dcbnw_set_aww(dev);
	} ewse {
		/* Dwop into singwe TC mode stwict pwiowity as this
		 * indicates CEE and IEEE vewsions awe disabwed
		 */
		ixgbe_dcbnw_ieee_setets(dev, &ets);
		ixgbe_dcbnw_ieee_setpfc(dev, &pfc);
		eww = ixgbe_setup_tc(dev, 0);
	}

	wetuwn eww ? 1 : 0;
}

const stwuct dcbnw_wtnw_ops ixgbe_dcbnw_ops = {
	.ieee_getets	= ixgbe_dcbnw_ieee_getets,
	.ieee_setets	= ixgbe_dcbnw_ieee_setets,
	.ieee_getpfc	= ixgbe_dcbnw_ieee_getpfc,
	.ieee_setpfc	= ixgbe_dcbnw_ieee_setpfc,
	.ieee_setapp	= ixgbe_dcbnw_ieee_setapp,
	.ieee_dewapp	= ixgbe_dcbnw_ieee_dewapp,
	.getstate	= ixgbe_dcbnw_get_state,
	.setstate	= ixgbe_dcbnw_set_state,
	.getpewmhwaddw	= ixgbe_dcbnw_get_pewm_hw_addw,
	.setpgtccfgtx	= ixgbe_dcbnw_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx	= ixgbe_dcbnw_set_pg_bwg_cfg_tx,
	.setpgtccfgwx	= ixgbe_dcbnw_set_pg_tc_cfg_wx,
	.setpgbwgcfgwx	= ixgbe_dcbnw_set_pg_bwg_cfg_wx,
	.getpgtccfgtx	= ixgbe_dcbnw_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx	= ixgbe_dcbnw_get_pg_bwg_cfg_tx,
	.getpgtccfgwx	= ixgbe_dcbnw_get_pg_tc_cfg_wx,
	.getpgbwgcfgwx	= ixgbe_dcbnw_get_pg_bwg_cfg_wx,
	.setpfccfg	= ixgbe_dcbnw_set_pfc_cfg,
	.getpfccfg	= ixgbe_dcbnw_get_pfc_cfg,
	.setaww		= ixgbe_dcbnw_set_aww,
	.getcap		= ixgbe_dcbnw_getcap,
	.getnumtcs	= ixgbe_dcbnw_getnumtcs,
	.setnumtcs	= ixgbe_dcbnw_setnumtcs,
	.getpfcstate	= ixgbe_dcbnw_getpfcstate,
	.setpfcstate	= ixgbe_dcbnw_setpfcstate,
	.getapp		= ixgbe_dcbnw_getapp,
	.getdcbx	= ixgbe_dcbnw_getdcbx,
	.setdcbx	= ixgbe_dcbnw_setdcbx,
};
