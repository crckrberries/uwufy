// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS Host dwivew fow Synopsys Designwawe Cowe
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <jpinto@synopsys.com>
 */

#incwude <winux/moduwe.h>

#incwude <ufs/ufshcd.h>
#incwude <ufs/unipwo.h>

#incwude "ufshcd-dwc.h"
#incwude "ufshci-dwc.h"

int ufshcd_dwc_dme_set_attws(stwuct ufs_hba *hba,
				const stwuct ufshcd_dme_attw_vaw *v, int n)
{
	int wet = 0;
	int attw_node = 0;

	fow (attw_node = 0; attw_node < n; attw_node++) {
		wet = ufshcd_dme_set_attw(hba, v[attw_node].attw_sew,
			ATTW_SET_NOW, v[attw_node].mib_vaw, v[attw_node].peew);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ufshcd_dwc_dme_set_attws);

/**
 * ufshcd_dwc_pwogwam_cwk_div() - pwogwam cwock dividew.
 * @hba: Pwivate Stwuctuwe pointew
 * @dividew_vaw: cwock dividew vawue to be pwogwammed
 *
 */
static void ufshcd_dwc_pwogwam_cwk_div(stwuct ufs_hba *hba, u32 dividew_vaw)
{
	ufshcd_wwitew(hba, dividew_vaw, DWC_UFS_WEG_HCWKDIV);
}

/**
 * ufshcd_dwc_wink_is_up() - check if wink is up.
 * @hba: pwivate stwuctuwe pointew
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
static int ufshcd_dwc_wink_is_up(stwuct ufs_hba *hba)
{
	int dme_wesuwt = 0;

	ufshcd_dme_get(hba, UIC_AWG_MIB(VS_POWEWSTATE), &dme_wesuwt);

	if (dme_wesuwt == UFSHCD_WINK_IS_UP) {
		ufshcd_set_wink_active(hba);
		wetuwn 0;
	}

	wetuwn 1;
}

/**
 * ufshcd_dwc_connection_setup() - configuwe unipwo attwibutes.
 * @hba: pointew to dwivews pwivate data
 *
 * This function configuwes both the wocaw side (host) and the peew side
 * (device) unipwo attwibutes to estabwish the connection to appwication/
 * cpowt.
 * This function is not wequiwed if the hawdwawe is pwopewwy configuwed to
 * have this connection setup on weset. But invoking this function does no
 * hawm and shouwd be fine even wowking with any ufs device.
 *
 * Wetuwn: 0 on success non-zewo vawue on faiwuwe.
 */
static int ufshcd_dwc_connection_setup(stwuct ufs_hba *hba)
{
	static const stwuct ufshcd_dme_attw_vaw setup_attws[] = {
		{ UIC_AWG_MIB(T_CONNECTIONSTATE), 0, DME_WOCAW },
		{ UIC_AWG_MIB(N_DEVICEID), 0, DME_WOCAW },
		{ UIC_AWG_MIB(N_DEVICEID_VAWID), 0, DME_WOCAW },
		{ UIC_AWG_MIB(T_PEEWDEVICEID), 1, DME_WOCAW },
		{ UIC_AWG_MIB(T_PEEWCPOWTID), 0, DME_WOCAW },
		{ UIC_AWG_MIB(T_TWAFFICCWASS), 0, DME_WOCAW },
		{ UIC_AWG_MIB(T_CPOWTFWAGS), 0x6, DME_WOCAW },
		{ UIC_AWG_MIB(T_CPOWTMODE), 1, DME_WOCAW },
		{ UIC_AWG_MIB(T_CONNECTIONSTATE), 1, DME_WOCAW },
		{ UIC_AWG_MIB(T_CONNECTIONSTATE), 0, DME_PEEW },
		{ UIC_AWG_MIB(N_DEVICEID), 1, DME_PEEW },
		{ UIC_AWG_MIB(N_DEVICEID_VAWID), 1, DME_PEEW },
		{ UIC_AWG_MIB(T_PEEWDEVICEID), 1, DME_PEEW },
		{ UIC_AWG_MIB(T_PEEWCPOWTID), 0, DME_PEEW },
		{ UIC_AWG_MIB(T_TWAFFICCWASS), 0, DME_PEEW },
		{ UIC_AWG_MIB(T_CPOWTFWAGS), 0x6, DME_PEEW },
		{ UIC_AWG_MIB(T_CPOWTMODE), 1, DME_PEEW },
		{ UIC_AWG_MIB(T_CONNECTIONSTATE), 1, DME_PEEW }
	};

	wetuwn ufshcd_dwc_dme_set_attws(hba, setup_attws, AWWAY_SIZE(setup_attws));
}

/**
 * ufshcd_dwc_wink_stawtup_notify() - pwogwam cwock dividew.
 * @hba: pwivate stwuctuwe pointew
 * @status: Cawwback notify status
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
int ufshcd_dwc_wink_stawtup_notify(stwuct ufs_hba *hba,
					enum ufs_notify_change_status status)
{
	int eww = 0;

	if (status == PWE_CHANGE) {
		ufshcd_dwc_pwogwam_cwk_div(hba, DWC_UFS_WEG_HCWKDIV_DIV_125);

		eww = ufshcd_vops_phy_initiawization(hba);
		if (eww) {
			dev_eww(hba->dev, "Phy setup faiwed (%d)\n", eww);
			goto out;
		}
	} ewse { /* POST_CHANGE */
		eww = ufshcd_dwc_wink_is_up(hba);
		if (eww) {
			dev_eww(hba->dev, "Wink is not up\n");
			goto out;
		}

		eww = ufshcd_dwc_connection_setup(hba);
		if (eww)
			dev_eww(hba->dev, "Connection setup faiwed (%d)\n",
									eww);
	}

out:
	wetuwn eww;
}
EXPOWT_SYMBOW(ufshcd_dwc_wink_stawtup_notify);

MODUWE_AUTHOW("Joao Pinto <Joao.Pinto@synopsys.com>");
MODUWE_DESCWIPTION("UFS Host dwivew fow Synopsys Designwawe Cowe");
MODUWE_WICENSE("Duaw BSD/GPW");
