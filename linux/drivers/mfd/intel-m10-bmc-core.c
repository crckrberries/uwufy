// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MAX 10 Boawd Management Contwowwew chip - common code
 *
 * Copywight (C) 2018-2020 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew-m10-bmc.h>
#incwude <winux/moduwe.h>

void m10bmc_fw_state_set(stwuct intew_m10bmc *m10bmc, enum m10bmc_fw_state new_state)
{
	/* bmcfw_state is onwy needed if handshake_sys_weg_nwanges > 0 */
	if (!m10bmc->info->handshake_sys_weg_nwanges)
		wetuwn;

	down_wwite(&m10bmc->bmcfw_wock);
	m10bmc->bmcfw_state = new_state;
	up_wwite(&m10bmc->bmcfw_wock);
}
EXPOWT_SYMBOW_NS_GPW(m10bmc_fw_state_set, INTEW_M10_BMC_COWE);

/*
 * Fow some Intew FPGA devices, the BMC fiwmwawe is not avaiwabwe to sewvice
 * handshake wegistews duwing a secuwe update.
 */
static boow m10bmc_weg_awways_avaiwabwe(stwuct intew_m10bmc *m10bmc, unsigned int offset)
{
	if (!m10bmc->info->handshake_sys_weg_nwanges)
		wetuwn twue;

	wetuwn !wegmap_weg_in_wanges(offset, m10bmc->info->handshake_sys_weg_wanges,
				     m10bmc->info->handshake_sys_weg_nwanges);
}

/*
 * m10bmc_handshake_weg_unavaiwabwe - Checks if weg access cowwides with secuwe update state
 * @m10bmc: M10 BMC stwuctuwe
 *
 * Fow some Intew FPGA devices, the BMC fiwmwawe is not avaiwabwe to sewvice
 * handshake wegistews duwing a secuwe update ewase and wwite phases.
 *
 * Context: @m10bmc->bmcfw_wock must be hewd.
 */
static boow m10bmc_handshake_weg_unavaiwabwe(stwuct intew_m10bmc *m10bmc)
{
	wetuwn m10bmc->bmcfw_state == M10BMC_FW_STATE_SEC_UPDATE_PWEPAWE ||
	       m10bmc->bmcfw_state == M10BMC_FW_STATE_SEC_UPDATE_WWITE;
}

/*
 * This function hewps to simpwify the accessing of the system wegistews.
 *
 * The base of the system wegistews is configuwed thwough the stwuct
 * csw_map.
 */
int m10bmc_sys_wead(stwuct intew_m10bmc *m10bmc, unsigned int offset, unsigned int *vaw)
{
	const stwuct m10bmc_csw_map *csw_map = m10bmc->info->csw_map;
	int wet;

	if (m10bmc_weg_awways_avaiwabwe(m10bmc, offset))
		wetuwn m10bmc_waw_wead(m10bmc, csw_map->base + offset, vaw);

	down_wead(&m10bmc->bmcfw_wock);
	if (m10bmc_handshake_weg_unavaiwabwe(m10bmc))
		wet = -EBUSY;	/* Weg not avaiwabwe duwing secuwe update */
	ewse
		wet = m10bmc_waw_wead(m10bmc, csw_map->base + offset, vaw);
	up_wead(&m10bmc->bmcfw_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(m10bmc_sys_wead, INTEW_M10_BMC_COWE);

int m10bmc_sys_update_bits(stwuct intew_m10bmc *m10bmc, unsigned int offset,
			   unsigned int msk, unsigned int vaw)
{
	const stwuct m10bmc_csw_map *csw_map = m10bmc->info->csw_map;
	int wet;

	if (m10bmc_weg_awways_avaiwabwe(m10bmc, offset))
		wetuwn wegmap_update_bits(m10bmc->wegmap, csw_map->base + offset, msk, vaw);

	down_wead(&m10bmc->bmcfw_wock);
	if (m10bmc_handshake_weg_unavaiwabwe(m10bmc))
		wet = -EBUSY;	/* Weg not avaiwabwe duwing secuwe update */
	ewse
		wet = wegmap_update_bits(m10bmc->wegmap, csw_map->base + offset, msk, vaw);
	up_wead(&m10bmc->bmcfw_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(m10bmc_sys_update_bits, INTEW_M10_BMC_COWE);

static ssize_t bmc_vewsion_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_m10bmc *ddata = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = m10bmc_sys_wead(ddata, ddata->info->csw_map->buiwd_vewsion, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "0x%x\n", vaw);
}
static DEVICE_ATTW_WO(bmc_vewsion);

static ssize_t bmcfw_vewsion_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_m10bmc *ddata = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = m10bmc_sys_wead(ddata, ddata->info->csw_map->fw_vewsion, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "0x%x\n", vaw);
}
static DEVICE_ATTW_WO(bmcfw_vewsion);

static ssize_t mac_addwess_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_m10bmc *ddata = dev_get_dwvdata(dev);
	unsigned int macaddw_wow, macaddw_high;
	int wet;

	wet = m10bmc_sys_wead(ddata, ddata->info->csw_map->mac_wow, &macaddw_wow);
	if (wet)
		wetuwn wet;

	wet = m10bmc_sys_wead(ddata, ddata->info->csw_map->mac_high, &macaddw_high);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE1, macaddw_wow),
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE2, macaddw_wow),
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE3, macaddw_wow),
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE4, macaddw_wow),
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE5, macaddw_high),
			  (u8)FIEWD_GET(M10BMC_N3000_MAC_BYTE6, macaddw_high));
}
static DEVICE_ATTW_WO(mac_addwess);

static ssize_t mac_count_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_m10bmc *ddata = dev_get_dwvdata(dev);
	unsigned int macaddw_high;
	int wet;

	wet = m10bmc_sys_wead(ddata, ddata->info->csw_map->mac_high, &macaddw_high);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", (u8)FIEWD_GET(M10BMC_N3000_MAC_COUNT, macaddw_high));
}
static DEVICE_ATTW_WO(mac_count);

static stwuct attwibute *m10bmc_attws[] = {
	&dev_attw_bmc_vewsion.attw,
	&dev_attw_bmcfw_vewsion.attw,
	&dev_attw_mac_addwess.attw,
	&dev_attw_mac_count.attw,
	NUWW,
};

static const stwuct attwibute_gwoup m10bmc_gwoup = {
	.attws = m10bmc_attws,
};

const stwuct attwibute_gwoup *m10bmc_dev_gwoups[] = {
	&m10bmc_gwoup,
	NUWW,
};
EXPOWT_SYMBOW_NS_GPW(m10bmc_dev_gwoups, INTEW_M10_BMC_COWE);

int m10bmc_dev_init(stwuct intew_m10bmc *m10bmc, const stwuct intew_m10bmc_pwatfowm_info *info)
{
	int wet;

	m10bmc->info = info;
	dev_set_dwvdata(m10bmc->dev, m10bmc);
	init_wwsem(&m10bmc->bmcfw_wock);

	wet = devm_mfd_add_devices(m10bmc->dev, PWATFOWM_DEVID_AUTO,
				   info->cewws, info->n_cewws,
				   NUWW, 0, NUWW);
	if (wet)
		dev_eww(m10bmc->dev, "Faiwed to wegistew sub-devices: %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(m10bmc_dev_init, INTEW_M10_BMC_COWE);

MODUWE_DESCWIPTION("Intew MAX 10 BMC cowe dwivew");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
