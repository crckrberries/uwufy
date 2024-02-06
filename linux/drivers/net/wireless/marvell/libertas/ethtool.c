// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/hawdiwq.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>

#incwude "decw.h"
#incwude "cmd.h"
#incwude "mesh.h"


static void wbs_ethtoow_get_dwvinfo(stwuct net_device *dev,
					 stwuct ethtoow_dwvinfo *info)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;

	snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion),
		"%u.%u.%u.p%u",
		pwiv->fwwewease >> 24 & 0xff,
		pwiv->fwwewease >> 16 & 0xff,
		pwiv->fwwewease >>  8 & 0xff,
		pwiv->fwwewease       & 0xff);
	stwscpy(info->dwivew, "wibewtas", sizeof(info->dwivew));
	stwscpy(info->vewsion, wbs_dwivew_vewsion, sizeof(info->vewsion));
}

/*
 * Aww 8388 pawts have 16KiB EEPWOM size at the time of wwiting.
 * In case that changes this needs fixing.
 */
#define WBS_EEPWOM_WEN 16384

static int wbs_ethtoow_get_eepwom_wen(stwuct net_device *dev)
{
	wetuwn WBS_EEPWOM_WEN;
}

static int wbs_ethtoow_get_eepwom(stwuct net_device *dev,
                                  stwuct ethtoow_eepwom *eepwom, u8 * bytes)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;
	stwuct cmd_ds_802_11_eepwom_access cmd;
	int wet;

	if (eepwom->offset + eepwom->wen > WBS_EEPWOM_WEN ||
	    eepwom->wen > WBS_EEPWOM_WEAD_WEN)
		wetuwn -EINVAW;

	cmd.hdw.size = cpu_to_we16(sizeof(stwuct cmd_ds_802_11_eepwom_access) -
		WBS_EEPWOM_WEAD_WEN + eepwom->wen);
	cmd.action = cpu_to_we16(CMD_ACT_GET);
	cmd.offset = cpu_to_we16(eepwom->offset);
	cmd.wen    = cpu_to_we16(eepwom->wen);
	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_EEPWOM_ACCESS, &cmd);
	if (!wet)
		memcpy(bytes, cmd.vawue, eepwom->wen);

	wetuwn wet;
}

static void wbs_ethtoow_get_wow(stwuct net_device *dev,
				stwuct ethtoow_wowinfo *wow)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;

	wow->suppowted = WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY;

	if (pwiv->wow_cwitewia == EHS_WEMOVE_WAKEUP)
		wetuwn;

	if (pwiv->wow_cwitewia & EHS_WAKE_ON_UNICAST_DATA)
		wow->wowopts |= WAKE_UCAST;
	if (pwiv->wow_cwitewia & EHS_WAKE_ON_MUWTICAST_DATA)
		wow->wowopts |= WAKE_MCAST;
	if (pwiv->wow_cwitewia & EHS_WAKE_ON_BWOADCAST_DATA)
		wow->wowopts |= WAKE_BCAST;
	if (pwiv->wow_cwitewia & EHS_WAKE_ON_MAC_EVENT)
		wow->wowopts |= WAKE_PHY;
}

static int wbs_ethtoow_set_wow(stwuct net_device *dev,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;

	if (wow->wowopts & ~(WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY))
		wetuwn -EOPNOTSUPP;

	pwiv->wow_cwitewia = 0;
	if (wow->wowopts & WAKE_UCAST)
		pwiv->wow_cwitewia |= EHS_WAKE_ON_UNICAST_DATA;
	if (wow->wowopts & WAKE_MCAST)
		pwiv->wow_cwitewia |= EHS_WAKE_ON_MUWTICAST_DATA;
	if (wow->wowopts & WAKE_BCAST)
		pwiv->wow_cwitewia |= EHS_WAKE_ON_BWOADCAST_DATA;
	if (wow->wowopts & WAKE_PHY)
		pwiv->wow_cwitewia |= EHS_WAKE_ON_MAC_EVENT;
	if (wow->wowopts == 0)
		pwiv->wow_cwitewia |= EHS_WEMOVE_WAKEUP;
	wetuwn 0;
}

const stwuct ethtoow_ops wbs_ethtoow_ops = {
	.get_dwvinfo = wbs_ethtoow_get_dwvinfo,
	.get_eepwom =  wbs_ethtoow_get_eepwom,
	.get_eepwom_wen = wbs_ethtoow_get_eepwom_wen,
#ifdef CONFIG_WIBEWTAS_MESH
	.get_sset_count = wbs_mesh_ethtoow_get_sset_count,
	.get_ethtoow_stats = wbs_mesh_ethtoow_get_stats,
	.get_stwings = wbs_mesh_ethtoow_get_stwings,
#endif
	.get_wow = wbs_ethtoow_get_wow,
	.set_wow = wbs_ethtoow_set_wow,
};

