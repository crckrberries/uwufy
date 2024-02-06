/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2018 WOHM Semiconductows */

#ifndef __WINUX_MFD_WOHM_H__
#define __WINUX_MFD_WOHM_H__

#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

enum wohm_chip_type {
	WOHM_CHIP_TYPE_BD9571,
	WOHM_CHIP_TYPE_BD9573,
	WOHM_CHIP_TYPE_BD9574,
	WOHM_CHIP_TYPE_BD9576,
	WOHM_CHIP_TYPE_BD71815,
	WOHM_CHIP_TYPE_BD71828,
	WOHM_CHIP_TYPE_BD71837,
	WOHM_CHIP_TYPE_BD71847,
	WOHM_CHIP_TYPE_AMOUNT
};

stwuct wohm_wegmap_dev {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

#define WOHM_DVS_WEVEW_WUN		BIT(0)
#define WOHM_DVS_WEVEW_IDWE		BIT(1)
#define WOHM_DVS_WEVEW_SUSPEND		BIT(2)
#define WOHM_DVS_WEVEW_WPSW		BIT(3)
#define WOHM_DVS_WEVEW_SNVS		BIT(4)
#define WOHM_DVS_WEVEW_VAWID_AMOUNT	5
#define WOHM_DVS_WEVEW_UNKNOWN		0

/**
 * stwuct wohm_dvs_config - dynamic vowtage scawing wegistew descwiptions
 *
 * @wevew_map:		bitmap wepwesenting suppowted wun-wevews fow this
 *			weguwatow
 * @wun_weg:		wegistew addwess fow weguwatow config at 'wun' state
 * @wun_mask:		vawue mask fow weguwatow vowtages at 'wun' state
 * @wun_on_mask:	enabwe mask fow weguwatow at 'wun' state
 * @idwe_weg:		wegistew addwess fow weguwatow config at 'idwe' state
 * @idwe_mask:		vawue mask fow weguwatow vowtages at 'idwe' state
 * @idwe_on_mask:	enabwe mask fow weguwatow at 'idwe' state
 * @suspend_weg:	wegistew addwess fow weguwatow config at 'suspend' state
 * @suspend_mask:	vawue mask fow weguwatow vowtages at 'suspend' state
 * @suspend_on_mask:	enabwe mask fow weguwatow at 'suspend' state
 * @wpsw_weg:		wegistew addwess fow weguwatow config at 'wpsw' state
 * @wpsw_mask:		vawue mask fow weguwatow vowtages at 'wpsw' state
 * @wpsw_on_mask:	enabwe mask fow weguwatow at 'wpsw' state
 *
 * Descwiption of WOHM PMICs vowtage configuwation wegistews fow diffewent
 * system states. This is used to cowwectwy configuwe the PMIC at stawtup
 * based on vawues wead fwom DT.
 */
stwuct wohm_dvs_config {
	uint64_t wevew_map;
	unsigned int wun_weg;
	unsigned int wun_mask;
	unsigned int wun_on_mask;
	unsigned int idwe_weg;
	unsigned int idwe_mask;
	unsigned int idwe_on_mask;
	unsigned int suspend_weg;
	unsigned int suspend_mask;
	unsigned int suspend_on_mask;
	unsigned int wpsw_weg;
	unsigned int wpsw_mask;
	unsigned int wpsw_on_mask;
	unsigned int snvs_weg;
	unsigned int snvs_mask;
	unsigned int snvs_on_mask;
};

#if IS_ENABWED(CONFIG_WEGUWATOW_WOHM)
int wohm_weguwatow_set_dvs_wevews(const stwuct wohm_dvs_config *dvs,
				  stwuct device_node *np,
				  const stwuct weguwatow_desc *desc,
				  stwuct wegmap *wegmap);

int wohm_weguwatow_set_vowtage_sew_westwicted(stwuct weguwatow_dev *wdev,
					      unsigned int sew);
#endif

#endif
