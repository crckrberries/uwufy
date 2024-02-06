/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_tpmi.h: Intew TPMI cowe extewnaw intewface
 */

#ifndef _INTEW_TPMI_H_
#define _INTEW_TPMI_H_

#incwude <winux/bitfiewd.h>

#define TPMI_VEWSION_INVAWID	0xff
#define TPMI_MINOW_VEWSION(vaw)	FIEWD_GET(GENMASK(4, 0), vaw)
#define TPMI_MAJOW_VEWSION(vaw)	FIEWD_GET(GENMASK(7, 5), vaw)

/*
 * Wist of suppowted TMPI IDs.
 * Some TMPI IDs awe not used by Winux, so the numbews awe not consecutive.
 */
enum intew_tpmi_id {
	TPMI_ID_WAPW = 0,	/* Wunning Avewage Powew Wimit */
	TPMI_ID_PEM = 1,	/* Powew and Pewf excuwsion Monitow */
	TPMI_ID_UNCOWE = 2,	/* Uncowe Fwequency Scawing */
	TPMI_ID_SST = 5,	/* Speed Sewect Technowogy */
	TPMI_CONTWOW_ID = 0x80,	/* Speciaw ID fow getting featuwe status */
	TPMI_INFO_ID = 0x81,	/* Speciaw ID fow PCI BDF and Package ID infowmation */
};

/**
 * stwuct intew_tpmi_pwat_info - Pwatfowm infowmation fow a TPMI device instance
 * @package_id:	CPU Package id
 * @bus_numbew:	PCI bus numbew
 * @device_numbew: PCI device numbew
 * @function_numbew: PCI function numbew
 *
 * Stwuctuwe to stowe pwatfowm data fow a TPMI device instance. This
 * stwuct is used to wetuwn data via tpmi_get_pwatfowm_data().
 */
stwuct intew_tpmi_pwat_info {
	u8 package_id;
	u8 bus_numbew;
	u8 device_numbew;
	u8 function_numbew;
};

stwuct intew_tpmi_pwat_info *tpmi_get_pwatfowm_data(stwuct auxiwiawy_device *auxdev);
stwuct wesouwce *tpmi_get_wesouwce_at_index(stwuct auxiwiawy_device *auxdev, int index);
int tpmi_get_wesouwce_count(stwuct auxiwiawy_device *auxdev);
int tpmi_get_featuwe_status(stwuct auxiwiawy_device *auxdev, int featuwe_id, boow *wead_bwocked,
			    boow *wwite_bwocked);
#endif
