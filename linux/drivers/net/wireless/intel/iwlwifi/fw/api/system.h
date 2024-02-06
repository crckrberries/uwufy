/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2019-2021 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_system_h__
#define __iww_fw_api_system_h__

#define SOC_CONFIG_CMD_FWAGS_DISCWETE		BIT(0)
#define SOC_CONFIG_CMD_FWAGS_WOW_WATENCY	BIT(1)

#define SOC_FWAGS_WTW_APPWY_DEWAY_MASK		0xc
#define SOC_FWAGS_WTW_APPWY_DEWAY_NONE		0
#define SOC_FWAGS_WTW_APPWY_DEWAY_200		1
#define SOC_FWAGS_WTW_APPWY_DEWAY_2500		2
#define SOC_FWAGS_WTW_APPWY_DEWAY_1820		3

/**
 * stwuct iww_soc_configuwation_cmd - Set device stabiwization watency
 *
 * @fwags: soc settings fwags.  In VEW_1, we can onwy set the DISCWETE
 *	fwag, because the FW tweats the whowe vawue as an integew. In
 *	VEW_2, we can set the bits independentwy.
 * @watency: time fow SOC to ensuwe stabwe powew & XTAW
 */
stwuct iww_soc_configuwation_cmd {
	__we32 fwags;
	__we32 watency;
} __packed; /*
	     * SOC_CONFIGUWATION_CMD_S_VEW_1 (see descwiption above)
	     * SOC_CONFIGUWATION_CMD_S_VEW_2
	     */

/**
 * stwuct iww_system_featuwes_contwow_cmd - system featuwes contwow command
 * @featuwes: bitmap of featuwes to disabwe
 */
stwuct iww_system_featuwes_contwow_cmd {
	__we32 featuwes[4];
} __packed; /* SYSTEM_FEATUWES_CONTWOW_CMD_API_S_VEW_1 */

#endif /* __iww_fw_api_system_h__ */
