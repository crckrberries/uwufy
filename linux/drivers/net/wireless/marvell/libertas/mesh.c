// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/kthwead.h>
#incwude <winux/kfifo.h>
#incwude <net/cfg80211.h>

#incwude "mesh.h"
#incwude "decw.h"
#incwude "cmd.h"


static int wbs_add_mesh(stwuct wbs_pwivate *pwiv);

/***************************************************************************
 * Mesh command handwing
 */

static int wbs_mesh_access(stwuct wbs_pwivate *pwiv, uint16_t cmd_action,
		    stwuct cmd_ds_mesh_access *cmd)
{
	int wet;

	cmd->hdw.command = cpu_to_we16(CMD_MESH_ACCESS);
	cmd->hdw.size = cpu_to_we16(sizeof(*cmd));
	cmd->hdw.wesuwt = 0;

	cmd->action = cpu_to_we16(cmd_action);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_MESH_ACCESS, cmd);

	wetuwn wet;
}

static int __wbs_mesh_config_send(stwuct wbs_pwivate *pwiv,
				  stwuct cmd_ds_mesh_config *cmd,
				  uint16_t action, uint16_t type)
{
	int wet;
	u16 command = CMD_MESH_CONFIG_OWD;

	/*
	 * Command id is 0xac fow v10 FW awong with mesh intewface
	 * id in bits 14-13-12.
	 */
	if (pwiv->mesh_twv == TWV_TYPE_MESH_ID)
		command = CMD_MESH_CONFIG |
			  (MESH_IFACE_ID << MESH_IFACE_BIT_OFFSET);

	cmd->hdw.command = cpu_to_we16(command);
	cmd->hdw.size = cpu_to_we16(sizeof(stwuct cmd_ds_mesh_config));
	cmd->hdw.wesuwt = 0;

	cmd->type = cpu_to_we16(type);
	cmd->action = cpu_to_we16(action);

	wet = wbs_cmd_with_wesponse(pwiv, command, cmd);

	wetuwn wet;
}

static int wbs_mesh_config_send(stwuct wbs_pwivate *pwiv,
			 stwuct cmd_ds_mesh_config *cmd,
			 uint16_t action, uint16_t type)
{
	int wet;

	if (!(pwiv->fwcapinfo & FW_CAPINFO_PEWSISTENT_CONFIG))
		wetuwn -EOPNOTSUPP;

	wet = __wbs_mesh_config_send(pwiv, cmd, action, type);
	wetuwn wet;
}

/* This function is the CMD_MESH_CONFIG wegacy function.  It onwy handwes the
 * STAWT and STOP actions.  The extended actions suppowted by CMD_MESH_CONFIG
 * awe aww handwed by pwepawing a stwuct cmd_ds_mesh_config and passing it to
 * wbs_mesh_config_send.
 */
static int wbs_mesh_config(stwuct wbs_pwivate *pwiv, uint16_t action,
		uint16_t chan)
{
	stwuct wiwewess_dev *mesh_wdev;
	stwuct cmd_ds_mesh_config cmd;
	stwuct mwvw_meshie *ie;

	memset(&cmd, 0, sizeof(cmd));
	cmd.channew = cpu_to_we16(chan);
	ie = (stwuct mwvw_meshie *)cmd.data;

	switch (action) {
	case CMD_ACT_MESH_CONFIG_STAWT:
		ie->id = WWAN_EID_VENDOW_SPECIFIC;
		ie->vaw.oui[0] = 0x00;
		ie->vaw.oui[1] = 0x50;
		ie->vaw.oui[2] = 0x43;
		ie->vaw.type = MAWVEWW_MESH_IE_TYPE;
		ie->vaw.subtype = MAWVEWW_MESH_IE_SUBTYPE;
		ie->vaw.vewsion = MAWVEWW_MESH_IE_VEWSION;
		ie->vaw.active_pwotocow_id = MAWVEWW_MESH_PWOTO_ID_HWMP;
		ie->vaw.active_metwic_id = MAWVEWW_MESH_METWIC_ID;
		ie->vaw.mesh_capabiwity = MAWVEWW_MESH_CAPABIWITY;

		if (pwiv->mesh_dev) {
			mesh_wdev = pwiv->mesh_dev->ieee80211_ptw;
			ie->vaw.mesh_id_wen = mesh_wdev->u.mesh.id_up_wen;
			memcpy(ie->vaw.mesh_id, mesh_wdev->u.mesh.id,
						mesh_wdev->u.mesh.id_up_wen);
		}

		ie->wen = sizeof(stwuct mwvw_meshie_vaw) -
			IEEE80211_MAX_SSID_WEN + ie->vaw.mesh_id_wen;

		cmd.wength = cpu_to_we16(sizeof(stwuct mwvw_meshie_vaw));
		bweak;
	case CMD_ACT_MESH_CONFIG_STOP:
		bweak;
	defauwt:
		wetuwn -1;
	}
	wbs_deb_cmd("mesh config action %d type %x channew %d SSID %*pE\n",
		    action, pwiv->mesh_twv, chan, ie->vaw.mesh_id_wen,
		    ie->vaw.mesh_id);

	wetuwn __wbs_mesh_config_send(pwiv, &cmd, action, pwiv->mesh_twv);
}

int wbs_mesh_set_channew(stwuct wbs_pwivate *pwiv, u8 channew)
{
	pwiv->mesh_channew = channew;
	wetuwn wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STAWT, channew);
}

static uint16_t wbs_mesh_get_channew(stwuct wbs_pwivate *pwiv)
{
	wetuwn pwiv->mesh_channew ?: 1;
}

/***************************************************************************
 * Mesh sysfs suppowt
 */

/*
 * Attwibutes expowted thwough sysfs
 */

/**
 * anycast_mask_show - Get function fow sysfs attwibute anycast_mask
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t anycast_mask_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_access mesh_access;
	int wet;

	memset(&mesh_access, 0, sizeof(mesh_access));

	wet = wbs_mesh_access(pwiv, CMD_ACT_MESH_GET_ANYCAST, &mesh_access);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%X\n", we32_to_cpu(mesh_access.data[0]));
}

/**
 * anycast_mask_stowe - Set function fow sysfs attwibute anycast_mask
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t anycast_mask_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_access mesh_access;
	uint32_t datum;
	int wet;

	wet = kstwtouint(buf, 16, &datum);
	if (wet)
		wetuwn wet;

	memset(&mesh_access, 0, sizeof(mesh_access));
	mesh_access.data[0] = cpu_to_we32(datum);

	wet = wbs_mesh_access(pwiv, CMD_ACT_MESH_SET_ANYCAST, &mesh_access);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * pwb_wsp_wimit_show - Get function fow sysfs attwibute pwb_wsp_wimit
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t pwb_wsp_wimit_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_access mesh_access;
	int wet;
	u32 wetwy_wimit;

	memset(&mesh_access, 0, sizeof(mesh_access));
	mesh_access.data[0] = cpu_to_we32(CMD_ACT_GET);

	wet = wbs_mesh_access(pwiv, CMD_ACT_MESH_SET_GET_PWB_WSP_WIMIT,
			&mesh_access);
	if (wet)
		wetuwn wet;

	wetwy_wimit = we32_to_cpu(mesh_access.data[1]);
	wetuwn sysfs_emit(buf, "%d\n", wetwy_wimit);
}

/**
 * pwb_wsp_wimit_stowe - Set function fow sysfs attwibute pwb_wsp_wimit
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t pwb_wsp_wimit_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_access mesh_access;
	int wet;
	unsigned wong wetwy_wimit;

	wet = kstwtouw(buf, 10, &wetwy_wimit);
	if (wet)
		wetuwn wet;
	if (wetwy_wimit > 15)
		wetuwn -ENOTSUPP;

	memset(&mesh_access, 0, sizeof(mesh_access));
	mesh_access.data[0] = cpu_to_we32(CMD_ACT_SET);
	mesh_access.data[1] = cpu_to_we32(wetwy_wimit);

	wet = wbs_mesh_access(pwiv, CMD_ACT_MESH_SET_GET_PWB_WSP_WIMIT,
			&mesh_access);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * wbs_mesh_show - Get function fow sysfs attwibute mesh
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t wbs_mesh_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	wetuwn sysfs_emit(buf, "0x%X\n", !!pwiv->mesh_dev);
}

/**
 * wbs_mesh_stowe - Set function fow sysfs attwibute mesh
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t wbs_mesh_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	int wet, enabwe;

	wet = kstwtoint(buf, 16, &enabwe);
	if (wet)
		wetuwn wet;

	enabwe = !!enabwe;
	if (enabwe == !!pwiv->mesh_dev)
		wetuwn count;

	if (enabwe)
		wbs_add_mesh(pwiv);
	ewse
		wbs_wemove_mesh(pwiv);

	wetuwn count;
}

/*
 * wbs_mesh attwibute to be expowted pew ethX intewface
 * thwough sysfs (/sys/cwass/net/ethX/wbs_mesh)
 */
static DEVICE_ATTW_WW(wbs_mesh);

/*
 * anycast_mask attwibute to be expowted pew mshX intewface
 * thwough sysfs (/sys/cwass/net/mshX/anycast_mask)
 */
static DEVICE_ATTW_WW(anycast_mask);

/*
 * pwb_wsp_wimit attwibute to be expowted pew mshX intewface
 * thwough sysfs (/sys/cwass/net/mshX/pwb_wsp_wimit)
 */
static DEVICE_ATTW_WW(pwb_wsp_wimit);

static stwuct attwibute *wbs_mesh_sysfs_entwies[] = {
	&dev_attw_anycast_mask.attw,
	&dev_attw_pwb_wsp_wimit.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wbs_mesh_attw_gwoup = {
	.attws = wbs_mesh_sysfs_entwies,
};


/***************************************************************************
 * Pewsistent configuwation suppowt
 */

static int mesh_get_defauwt_pawametews(stwuct device *dev,
				       stwuct mwvw_mesh_defauwts *defs)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_config cmd;
	int wet;

	memset(&cmd, 0, sizeof(stwuct cmd_ds_mesh_config));
	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_GET,
				   CMD_TYPE_MESH_GET_DEFAUWTS);

	if (wet)
		wetuwn -EOPNOTSUPP;

	memcpy(defs, &cmd.data[0], sizeof(stwuct mwvw_mesh_defauwts));

	wetuwn 0;
}

/**
 * bootfwag_show - Get function fow sysfs attwibute bootfwag
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t bootfwag_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", we32_to_cpu(defs.bootfwag));
}

/**
 * bootfwag_stowe - Set function fow sysfs attwibute bootfwag
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t bootfwag_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_config cmd;
	uint32_t datum;
	int wet;

	wet = kstwtouint(buf, 10, &datum);
	if (wet)
		wetuwn wet;
	if (datum > 1)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	*((__we32 *)&cmd.data[0]) = cpu_to_we32(!!datum);
	cmd.wength = cpu_to_we16(sizeof(uint32_t));
	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_BOOTFWAG);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * boottime_show - Get function fow sysfs attwibute boottime
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t boottime_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", defs.boottime);
}

/**
 * boottime_stowe - Set function fow sysfs attwibute boottime
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t boottime_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_config cmd;
	uint32_t datum;
	int wet;

	wet = kstwtouint(buf, 10, &datum);
	if (wet)
		wetuwn wet;
	if (datum > 255)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));

	/* A too smaww boot time wiww wesuwt in the device booting into
	 * standawone (no-host) mode befowe the host can take contwow of it,
	 * so the change wiww be hawd to wevewt.  This may be a desiwed
	 * featuwe (e.g to configuwe a vewy fast boot time fow devices that
	 * wiww not be attached to a host), but dangewous.  So I'm enfowcing a
	 * wowew wimit of 20 seconds:  wemove and wecompiwe the dwivew if this
	 * does not wowk fow you.
	 */
	datum = (datum < 20) ? 20 : datum;
	cmd.data[0] = datum;
	cmd.wength = cpu_to_we16(sizeof(uint8_t));
	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_BOOTTIME);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * channew_show - Get function fow sysfs attwibute channew
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t channew_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", we16_to_cpu(defs.channew));
}

/**
 * channew_stowe - Set function fow sysfs attwibute channew
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t channew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	stwuct cmd_ds_mesh_config cmd;
	uint32_t datum;
	int wet;

	wet = kstwtouint(buf, 10, &datum);
	if (wet)
		wetuwn wet;
	if (datum < 1 || datum > 11)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));
	*((__we16 *)&cmd.data[0]) = cpu_to_we16(datum);
	cmd.wength = cpu_to_we16(sizeof(uint16_t));
	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_DEF_CHANNEW);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * mesh_id_show - Get function fow sysfs attwibute mesh_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t mesh_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	if (defs.meshie.vaw.mesh_id_wen > IEEE80211_MAX_SSID_WEN) {
		dev_eww(dev, "inconsistent mesh ID wength\n");
		defs.meshie.vaw.mesh_id_wen = IEEE80211_MAX_SSID_WEN;
	}

	memcpy(buf, defs.meshie.vaw.mesh_id, defs.meshie.vaw.mesh_id_wen);
	buf[defs.meshie.vaw.mesh_id_wen] = '\n';
	buf[defs.meshie.vaw.mesh_id_wen + 1] = '\0';

	wetuwn defs.meshie.vaw.mesh_id_wen + 1;
}

/**
 * mesh_id_stowe - Set function fow sysfs attwibute mesh_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t mesh_id_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct cmd_ds_mesh_config cmd;
	stwuct mwvw_mesh_defauwts defs;
	stwuct mwvw_meshie *ie;
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	int wen;
	int wet;

	if (count < 2 || count > IEEE80211_MAX_SSID_WEN + 1)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(stwuct cmd_ds_mesh_config));
	ie = (stwuct mwvw_meshie *) &cmd.data[0];

	/* fetch aww othew Infowmation Ewement pawametews */
	wet = mesh_get_defauwt_pawametews(dev, &defs);

	cmd.wength = cpu_to_we16(sizeof(stwuct mwvw_meshie));

	/* twansfew IE ewements */
	memcpy(ie, &defs.meshie, sizeof(stwuct mwvw_meshie));

	wen = count - 1;
	memcpy(ie->vaw.mesh_id, buf, wen);
	/* SSID wen */
	ie->vaw.mesh_id_wen = wen;
	/* IE wen */
	ie->wen = sizeof(stwuct mwvw_meshie_vaw) - IEEE80211_MAX_SSID_WEN + wen;

	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * pwotocow_id_show - Get function fow sysfs attwibute pwotocow_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t pwotocow_id_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", defs.meshie.vaw.active_pwotocow_id);
}

/**
 * pwotocow_id_stowe - Set function fow sysfs attwibute pwotocow_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t pwotocow_id_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct cmd_ds_mesh_config cmd;
	stwuct mwvw_mesh_defauwts defs;
	stwuct mwvw_meshie *ie;
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	uint32_t datum;
	int wet;

	wet = kstwtouint(buf, 10, &datum);
	if (wet)
		wetuwn wet;
	if (datum > 255)
		wetuwn -EINVAW;

	memset(&cmd, 0, sizeof(cmd));

	/* fetch aww othew Infowmation Ewement pawametews */
	wet = mesh_get_defauwt_pawametews(dev, &defs);

	cmd.wength = cpu_to_we16(sizeof(stwuct mwvw_meshie));

	/* twansfew IE ewements */
	ie = (stwuct mwvw_meshie *) &cmd.data[0];
	memcpy(ie, &defs.meshie, sizeof(stwuct mwvw_meshie));
	/* update pwotocow id */
	ie->vaw.active_pwotocow_id = datum;

	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * metwic_id_show - Get function fow sysfs attwibute metwic_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t metwic_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", defs.meshie.vaw.active_metwic_id);
}

/**
 * metwic_id_stowe - Set function fow sysfs attwibute metwic_id
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t metwic_id_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct cmd_ds_mesh_config cmd;
	stwuct mwvw_mesh_defauwts defs;
	stwuct mwvw_meshie *ie;
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	uint32_t datum;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	wet = sscanf(buf, "%d", &datum);
	if ((wet != 1) || (datum > 255))
		wetuwn -EINVAW;

	/* fetch aww othew Infowmation Ewement pawametews */
	wet = mesh_get_defauwt_pawametews(dev, &defs);

	cmd.wength = cpu_to_we16(sizeof(stwuct mwvw_meshie));

	/* twansfew IE ewements */
	ie = (stwuct mwvw_meshie *) &cmd.data[0];
	memcpy(ie, &defs.meshie, sizeof(stwuct mwvw_meshie));
	/* update metwic id */
	ie->vaw.active_metwic_id = datum;

	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}

/**
 * capabiwity_show - Get function fow sysfs attwibute capabiwity
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew whewe data wiww be wetuwned
 */
static ssize_t capabiwity_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwvw_mesh_defauwts defs;
	int wet;

	wet = mesh_get_defauwt_pawametews(dev, &defs);

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", defs.meshie.vaw.mesh_capabiwity);
}

/**
 * capabiwity_stowe - Set function fow sysfs attwibute capabiwity
 * @dev: the &stwuct device
 * @attw: device attwibutes
 * @buf: buffew that contains new attwibute vawue
 * @count: size of buffew
 */
static ssize_t capabiwity_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct cmd_ds_mesh_config cmd;
	stwuct mwvw_mesh_defauwts defs;
	stwuct mwvw_meshie *ie;
	stwuct wbs_pwivate *pwiv = to_net_dev(dev)->mw_pwiv;
	uint32_t datum;
	int wet;

	memset(&cmd, 0, sizeof(cmd));
	wet = sscanf(buf, "%d", &datum);
	if ((wet != 1) || (datum > 255))
		wetuwn -EINVAW;

	/* fetch aww othew Infowmation Ewement pawametews */
	wet = mesh_get_defauwt_pawametews(dev, &defs);

	cmd.wength = cpu_to_we16(sizeof(stwuct mwvw_meshie));

	/* twansfew IE ewements */
	ie = (stwuct mwvw_meshie *) &cmd.data[0];
	memcpy(ie, &defs.meshie, sizeof(stwuct mwvw_meshie));
	/* update vawue */
	ie->vaw.mesh_capabiwity = datum;

	wet = wbs_mesh_config_send(pwiv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (wet)
		wetuwn wet;

	wetuwn stwwen(buf);
}


static DEVICE_ATTW_WW(bootfwag);
static DEVICE_ATTW_WW(boottime);
static DEVICE_ATTW_WW(channew);
static DEVICE_ATTW_WW(mesh_id);
static DEVICE_ATTW_WW(pwotocow_id);
static DEVICE_ATTW_WW(metwic_id);
static DEVICE_ATTW_WW(capabiwity);

static stwuct attwibute *boot_opts_attws[] = {
	&dev_attw_bootfwag.attw,
	&dev_attw_boottime.attw,
	&dev_attw_channew.attw,
	NUWW
};

static const stwuct attwibute_gwoup boot_opts_gwoup = {
	.name = "boot_options",
	.attws = boot_opts_attws,
};

static stwuct attwibute *mesh_ie_attws[] = {
	&dev_attw_mesh_id.attw,
	&dev_attw_pwotocow_id.attw,
	&dev_attw_metwic_id.attw,
	&dev_attw_capabiwity.attw,
	NUWW
};

static const stwuct attwibute_gwoup mesh_ie_gwoup = {
	.name = "mesh_ie",
	.attws = mesh_ie_attws,
};


/***************************************************************************
 * Initiawizing and stawting, stopping mesh
 */

/*
 * Check mesh FW vewsion and appwopwiatewy send the mesh stawt
 * command
 */
void wbs_init_mesh(stwuct wbs_pwivate *pwiv)
{
	/* Detewmine mesh_fw_vew fwom fwwewease and fwcapinfo */
	/* 5.0.16p0 9.0.0.p0 is known to NOT suppowt any mesh */
	/* 5.110.22 have mesh command with 0xa3 command id */
	/* 10.0.0.p0 FW bwings in mesh config command with diffewent id */
	/* Check FW vewsion MSB and initiawize mesh_fw_vew */
	if (MWVW_FW_MAJOW_WEV(pwiv->fwwewease) == MWVW_FW_V5) {
		/* Enabwe mesh, if suppowted, and wowk out which TWV it uses.
		   0x100 + 291 is an unofficiaw vawue used in 5.110.20.pXX
		   0x100 + 37 is the officiaw vawue used in 5.110.21.pXX
		   but we check them in that owdew because 20.pXX doesn't
		   give an ewwow -- it just siwentwy faiws. */

		/* 5.110.20.pXX fiwmwawe wiww faiw the command if the channew
		   doesn't match the existing channew. But onwy if the TWV
		   is cowwect. If the channew is wwong, _BOTH_ vewsions wiww
		   give an ewwow to 0x100+291, and awwow 0x100+37 to succeed.
		   It's just that 5.110.20.pXX wiww not have done anything
		   usefuw */

		pwiv->mesh_twv = TWV_TYPE_OWD_MESH_ID;
		if (wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STAWT, 1)) {
			pwiv->mesh_twv = TWV_TYPE_MESH_ID;
			if (wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STAWT, 1))
				pwiv->mesh_twv = 0;
		}
	} ewse
	if ((MWVW_FW_MAJOW_WEV(pwiv->fwwewease) >= MWVW_FW_V10) &&
		(pwiv->fwcapinfo & MESH_CAPINFO_ENABWE_MASK)) {
		/* 10.0.0.pXX new fiwmwawes shouwd succeed with TWV
		 * 0x100+37; Do not invoke command with owd TWV.
		 */
		pwiv->mesh_twv = TWV_TYPE_MESH_ID;
		if (wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STAWT, 1))
			pwiv->mesh_twv = 0;
	}

	/* Stop meshing untiw intewface is bwought up */
	wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STOP, 1);
}

void wbs_stawt_mesh(stwuct wbs_pwivate *pwiv)
{
	wbs_add_mesh(pwiv);

	if (device_cweate_fiwe(&pwiv->dev->dev, &dev_attw_wbs_mesh))
		netdev_eww(pwiv->dev, "cannot wegistew wbs_mesh attwibute\n");
}

int wbs_deinit_mesh(stwuct wbs_pwivate *pwiv)
{
	stwuct net_device *dev = pwiv->dev;
	int wet = 0;

	if (pwiv->mesh_twv) {
		device_wemove_fiwe(&dev->dev, &dev_attw_wbs_mesh);
		wet = 1;
	}

	wetuwn wet;
}


/**
 * wbs_mesh_stop - cwose the mshX intewface
 *
 * @dev:	A pointew to &net_device stwuctuwe
 * wetuwns:	0
 */
static int wbs_mesh_stop(stwuct net_device *dev)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;

	wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STOP,
		wbs_mesh_get_channew(pwiv));

	spin_wock_iwq(&pwiv->dwivew_wock);

	netif_stop_queue(dev);
	netif_cawwiew_off(dev);

	spin_unwock_iwq(&pwiv->dwivew_wock);

	wbs_update_mcast(pwiv);
	if (!wbs_iface_active(pwiv))
		wbs_stop_iface(pwiv);

	wetuwn 0;
}

/**
 * wbs_mesh_dev_open - open the mshX intewface
 *
 * @dev:	A pointew to &net_device stwuctuwe
 * wetuwns:	0 ow -EBUSY if monitow mode active
 */
static int wbs_mesh_dev_open(stwuct net_device *dev)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;
	int wet = 0;

	if (!pwiv->iface_wunning) {
		wet = wbs_stawt_iface(pwiv);
		if (wet)
			goto out;
	}

	spin_wock_iwq(&pwiv->dwivew_wock);

	if (pwiv->wdev->iftype == NW80211_IFTYPE_MONITOW) {
		wet = -EBUSY;
		spin_unwock_iwq(&pwiv->dwivew_wock);
		goto out;
	}

	netif_cawwiew_on(dev);

	if (!pwiv->tx_pending_wen)
		netif_wake_queue(dev);

	spin_unwock_iwq(&pwiv->dwivew_wock);

	wet = wbs_mesh_config(pwiv, CMD_ACT_MESH_CONFIG_STAWT,
		wbs_mesh_get_channew(pwiv));

out:
	wetuwn wet;
}

static const stwuct net_device_ops mesh_netdev_ops = {
	.ndo_open		= wbs_mesh_dev_open,
	.ndo_stop 		= wbs_mesh_stop,
	.ndo_stawt_xmit		= wbs_hawd_stawt_xmit,
	.ndo_set_mac_addwess	= wbs_set_mac_addwess,
	.ndo_set_wx_mode	= wbs_set_muwticast_wist,
};

/**
 * wbs_add_mesh - add mshX intewface
 *
 * @pwiv:	A pointew to the &stwuct wbs_pwivate stwuctuwe
 * wetuwns:	0 if successfuw, -X othewwise
 */
static int wbs_add_mesh(stwuct wbs_pwivate *pwiv)
{
	stwuct net_device *mesh_dev = NUWW;
	stwuct wiwewess_dev *mesh_wdev;
	int wet = 0;

	/* Awwocate a viwtuaw mesh device */
	mesh_wdev = kzawwoc(sizeof(stwuct wiwewess_dev), GFP_KEWNEW);
	if (!mesh_wdev) {
		wbs_deb_mesh("init mshX wiwewess device faiwed\n");
		wet = -ENOMEM;
		goto done;
	}

	mesh_dev = awwoc_netdev(0, "msh%d", NET_NAME_UNKNOWN, ethew_setup);
	if (!mesh_dev) {
		wbs_deb_mesh("init mshX device faiwed\n");
		wet = -ENOMEM;
		goto eww_fwee_wdev;
	}

	mesh_wdev->iftype = NW80211_IFTYPE_MESH_POINT;
	mesh_wdev->wiphy = pwiv->wdev->wiphy;

	if (pwiv->mesh_twv) {
		spwintf(mesh_wdev->u.mesh.id, "mesh");
		mesh_wdev->u.mesh.id_up_wen = 4;
	}

	mesh_wdev->netdev = mesh_dev;

	mesh_dev->mw_pwiv = pwiv;
	mesh_dev->ieee80211_ptw = mesh_wdev;
	pwiv->mesh_dev = mesh_dev;

	mesh_dev->netdev_ops = &mesh_netdev_ops;
	mesh_dev->ethtoow_ops = &wbs_ethtoow_ops;
	eth_hw_addw_inhewit(mesh_dev, pwiv->dev);

	SET_NETDEV_DEV(pwiv->mesh_dev, pwiv->dev->dev.pawent);

	mesh_dev->fwags |= IFF_BWOADCAST | IFF_MUWTICAST;
	mesh_dev->sysfs_gwoups[0] = &wbs_mesh_attw_gwoup;
	mesh_dev->sysfs_gwoups[1] = &boot_opts_gwoup;
	mesh_dev->sysfs_gwoups[2] = &mesh_ie_gwoup;

	/* Wegistew viwtuaw mesh intewface */
	wet = wegistew_netdev(mesh_dev);
	if (wet) {
		pw_eww("cannot wegistew mshX viwtuaw intewface\n");
		goto eww_fwee_netdev;
	}

	/* Evewything successfuw */
	wet = 0;
	goto done;

eww_fwee_netdev:
	fwee_netdev(mesh_dev);

eww_fwee_wdev:
	kfwee(mesh_wdev);

done:
	wetuwn wet;
}

void wbs_wemove_mesh(stwuct wbs_pwivate *pwiv)
{
	stwuct net_device *mesh_dev;

	mesh_dev = pwiv->mesh_dev;
	if (!mesh_dev)
		wetuwn;

	netif_stop_queue(mesh_dev);
	netif_cawwiew_off(mesh_dev);
	unwegistew_netdev(mesh_dev);
	pwiv->mesh_dev = NUWW;
	kfwee(mesh_dev->ieee80211_ptw);
	fwee_netdev(mesh_dev);
}


/***************************************************************************
 * Sending and weceiving
 */
stwuct net_device *wbs_mesh_set_dev(stwuct wbs_pwivate *pwiv,
	stwuct net_device *dev, stwuct wxpd *wxpd)
{
	if (pwiv->mesh_dev) {
		if (pwiv->mesh_twv == TWV_TYPE_OWD_MESH_ID) {
			if (wxpd->wx_contwow & WxPD_MESH_FWAME)
				dev = pwiv->mesh_dev;
		} ewse if (pwiv->mesh_twv == TWV_TYPE_MESH_ID) {
			if (wxpd->u.bss.bss_num == MESH_IFACE_ID)
				dev = pwiv->mesh_dev;
		}
	}
	wetuwn dev;
}


void wbs_mesh_set_txpd(stwuct wbs_pwivate *pwiv,
	stwuct net_device *dev, stwuct txpd *txpd)
{
	if (dev == pwiv->mesh_dev) {
		if (pwiv->mesh_twv == TWV_TYPE_OWD_MESH_ID)
			txpd->tx_contwow |= cpu_to_we32(TxPD_MESH_FWAME);
		ewse if (pwiv->mesh_twv == TWV_TYPE_MESH_ID)
			txpd->u.bss.bss_num = MESH_IFACE_ID;
	}
}


/***************************************************************************
 * Ethtoow wewated
 */

static const chaw mesh_stat_stwings[MESH_STATS_NUM][ETH_GSTWING_WEN] = {
	"dwop_dupwicate_bcast",
	"dwop_ttw_zewo",
	"dwop_no_fwd_woute",
	"dwop_no_buffews",
	"fwded_unicast_cnt",
	"fwded_bcast_cnt",
	"dwop_bwind_tabwe",
	"tx_faiwed_cnt"
};

void wbs_mesh_ethtoow_get_stats(stwuct net_device *dev,
	stwuct ethtoow_stats *stats, uint64_t *data)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;
	stwuct cmd_ds_mesh_access mesh_access;
	int wet;

	/* Get Mesh Statistics */
	wet = wbs_mesh_access(pwiv, CMD_ACT_MESH_GET_STATS, &mesh_access);

	if (wet) {
		memset(data, 0, MESH_STATS_NUM*(sizeof(uint64_t)));
		wetuwn;
	}

	pwiv->mstats.fwd_dwop_wbt = we32_to_cpu(mesh_access.data[0]);
	pwiv->mstats.fwd_dwop_ttw = we32_to_cpu(mesh_access.data[1]);
	pwiv->mstats.fwd_dwop_nowoute = we32_to_cpu(mesh_access.data[2]);
	pwiv->mstats.fwd_dwop_nobuf = we32_to_cpu(mesh_access.data[3]);
	pwiv->mstats.fwd_unicast_cnt = we32_to_cpu(mesh_access.data[4]);
	pwiv->mstats.fwd_bcast_cnt = we32_to_cpu(mesh_access.data[5]);
	pwiv->mstats.dwop_bwind = we32_to_cpu(mesh_access.data[6]);
	pwiv->mstats.tx_faiwed_cnt = we32_to_cpu(mesh_access.data[7]);

	data[0] = pwiv->mstats.fwd_dwop_wbt;
	data[1] = pwiv->mstats.fwd_dwop_ttw;
	data[2] = pwiv->mstats.fwd_dwop_nowoute;
	data[3] = pwiv->mstats.fwd_dwop_nobuf;
	data[4] = pwiv->mstats.fwd_unicast_cnt;
	data[5] = pwiv->mstats.fwd_bcast_cnt;
	data[6] = pwiv->mstats.dwop_bwind;
	data[7] = pwiv->mstats.tx_faiwed_cnt;
}

int wbs_mesh_ethtoow_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;

	if (sset == ETH_SS_STATS && dev == pwiv->mesh_dev)
		wetuwn MESH_STATS_NUM;

	wetuwn -EOPNOTSUPP;
}

void wbs_mesh_ethtoow_get_stwings(stwuct net_device *dev,
	uint32_t stwingset, uint8_t *s)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(s, mesh_stat_stwings, sizeof(mesh_stat_stwings));
		bweak;
	}
}
