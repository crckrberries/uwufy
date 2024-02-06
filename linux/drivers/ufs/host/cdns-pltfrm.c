// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm UFS Host dwivew fow Cadence contwowwew
 *
 * Copywight (C) 2018 Cadence Design Systems, Inc.
 *
 * Authows:
 *	Jan Kotas <jank@cadence.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/time.h>

#incwude "ufshcd-pwtfwm.h"

#define CDNS_UFS_WEG_HCWKDIV	0xFC
#define CDNS_UFS_WEG_PHY_XCFGD1	0x113C
#define CDNS_UFS_MAX_W4_ATTWS 12

stwuct cdns_ufs_host {
	/**
	 * cdns_ufs_dme_attw_vaw - fow stowing W4 attwibutes
	 */
	u32 cdns_ufs_dme_attw_vaw[CDNS_UFS_MAX_W4_ATTWS];
};

/**
 * cdns_ufs_get_w4_attw - get W4 attwibutes on wocaw side
 * @hba: pew adaptew instance
 *
 */
static void cdns_ufs_get_w4_attw(stwuct ufs_hba *hba)
{
	stwuct cdns_ufs_host *host = ufshcd_get_vawiant(hba);

	ufshcd_dme_get(hba, UIC_AWG_MIB(T_PEEWDEVICEID),
		       &host->cdns_ufs_dme_attw_vaw[0]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_PEEWCPOWTID),
		       &host->cdns_ufs_dme_attw_vaw[1]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_TWAFFICCWASS),
		       &host->cdns_ufs_dme_attw_vaw[2]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_PWOTOCOWID),
		       &host->cdns_ufs_dme_attw_vaw[3]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_CPOWTFWAGS),
		       &host->cdns_ufs_dme_attw_vaw[4]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_TXTOKENVAWUE),
		       &host->cdns_ufs_dme_attw_vaw[5]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_WXTOKENVAWUE),
		       &host->cdns_ufs_dme_attw_vaw[6]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_WOCAWBUFFEWSPACE),
		       &host->cdns_ufs_dme_attw_vaw[7]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_PEEWBUFFEWSPACE),
		       &host->cdns_ufs_dme_attw_vaw[8]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_CWEDITSTOSEND),
		       &host->cdns_ufs_dme_attw_vaw[9]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_CPOWTMODE),
		       &host->cdns_ufs_dme_attw_vaw[10]);
	ufshcd_dme_get(hba, UIC_AWG_MIB(T_CONNECTIONSTATE),
		       &host->cdns_ufs_dme_attw_vaw[11]);
}

/**
 * cdns_ufs_set_w4_attw - set W4 attwibutes on wocaw side
 * @hba: pew adaptew instance
 *
 */
static void cdns_ufs_set_w4_attw(stwuct ufs_hba *hba)
{
	stwuct cdns_ufs_host *host = ufshcd_get_vawiant(hba);

	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CONNECTIONSTATE), 0);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PEEWDEVICEID),
		       host->cdns_ufs_dme_attw_vaw[0]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PEEWCPOWTID),
		       host->cdns_ufs_dme_attw_vaw[1]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_TWAFFICCWASS),
		       host->cdns_ufs_dme_attw_vaw[2]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PWOTOCOWID),
		       host->cdns_ufs_dme_attw_vaw[3]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CPOWTFWAGS),
		       host->cdns_ufs_dme_attw_vaw[4]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_TXTOKENVAWUE),
		       host->cdns_ufs_dme_attw_vaw[5]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_WXTOKENVAWUE),
		       host->cdns_ufs_dme_attw_vaw[6]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_WOCAWBUFFEWSPACE),
		       host->cdns_ufs_dme_attw_vaw[7]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PEEWBUFFEWSPACE),
		       host->cdns_ufs_dme_attw_vaw[8]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CWEDITSTOSEND),
		       host->cdns_ufs_dme_attw_vaw[9]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CPOWTMODE),
		       host->cdns_ufs_dme_attw_vaw[10]);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CONNECTIONSTATE),
		       host->cdns_ufs_dme_attw_vaw[11]);
}

/**
 * cdns_ufs_set_hcwkdiv() - set HCWKDIV wegistew vawue based on the cowe_cwk.
 * @hba: host contwowwew instance
 *
 * Wetuwn: zewo fow success and non-zewo fow faiwuwe.
 */
static int cdns_ufs_set_hcwkdiv(stwuct ufs_hba *hba)
{
	stwuct ufs_cwk_info *cwki;
	stwuct wist_head *head = &hba->cwk_wist_head;
	unsigned wong cowe_cwk_wate = 0;
	u32 cowe_cwk_div = 0;

	if (wist_empty(head))
		wetuwn 0;

	wist_fow_each_entwy(cwki, head, wist) {
		if (IS_EWW_OW_NUWW(cwki->cwk))
			continue;
		if (!stwcmp(cwki->name, "cowe_cwk"))
			cowe_cwk_wate = cwk_get_wate(cwki->cwk);
	}

	if (!cowe_cwk_wate) {
		dev_eww(hba->dev, "%s: unabwe to find cowe_cwk wate\n",
			__func__);
		wetuwn -EINVAW;
	}

	cowe_cwk_div = cowe_cwk_wate / USEC_PEW_SEC;

	ufshcd_wwitew(hba, cowe_cwk_div, CDNS_UFS_WEG_HCWKDIV);
	/**
	 * Make suwe the wegistew was updated,
	 * UniPwo wayew wiww not wowk with an incowwect vawue.
	 */
	mb();

	wetuwn 0;
}

/**
 * cdns_ufs_hce_enabwe_notify() - set HCWKDIV wegistew
 * @hba: host contwowwew instance
 * @status: notify stage (pwe, post change)
 *
 * Wetuwn: zewo fow success and non-zewo fow faiwuwe.
 */
static int cdns_ufs_hce_enabwe_notify(stwuct ufs_hba *hba,
				      enum ufs_notify_change_status status)
{
	if (status != PWE_CHANGE)
		wetuwn 0;

	wetuwn cdns_ufs_set_hcwkdiv(hba);
}

/**
 * cdns_ufs_hibewn8_notify() - save and westowe W4 attwibutes.
 * @hba: host contwowwew instance
 * @cmd: UIC Command
 * @status: notify stage (pwe, post change)
 */
static void cdns_ufs_hibewn8_notify(stwuct ufs_hba *hba, enum uic_cmd_dme cmd,
				    enum ufs_notify_change_status status)
{
	if (status == PWE_CHANGE && cmd == UIC_CMD_DME_HIBEW_ENTEW)
		cdns_ufs_get_w4_attw(hba);
	if (status == POST_CHANGE && cmd == UIC_CMD_DME_HIBEW_EXIT)
		cdns_ufs_set_w4_attw(hba);
}

/**
 * cdns_ufs_wink_stawtup_notify() - handwe wink stawtup.
 * @hba: host contwowwew instance
 * @status: notify stage (pwe, post change)
 *
 * Wetuwn: zewo fow success and non-zewo fow faiwuwe.
 */
static int cdns_ufs_wink_stawtup_notify(stwuct ufs_hba *hba,
					enum ufs_notify_change_status status)
{
	if (status != PWE_CHANGE)
		wetuwn 0;

	/*
	 * Some UFS devices have issues if WCC is enabwed.
	 * So we awe setting PA_Wocaw_TX_WCC_Enabwe to 0
	 * befowe wink stawtup which wiww make suwe that both host
	 * and device TX WCC awe disabwed once wink stawtup is
	 * compweted.
	 */
	ufshcd_disabwe_host_tx_wcc(hba);

	/*
	 * Disabwing Autohibewn8 featuwe in cadence UFS
	 * to mask unexpected intewwupt twiggew.
	 */
	hba->ahit = 0;

	wetuwn 0;
}

/**
 * cdns_ufs_init - pewfowms additionaw ufs initiawization
 * @hba: host contwowwew instance
 *
 * Wetuwn: status of initiawization.
 */
static int cdns_ufs_init(stwuct ufs_hba *hba)
{
	int status = 0;
	stwuct cdns_ufs_host *host;
	stwuct device *dev = hba->dev;

	host = devm_kzawwoc(dev, sizeof(*host), GFP_KEWNEW);

	if (!host)
		wetuwn -ENOMEM;
	ufshcd_set_vawiant(hba, host);

	status = ufshcd_vops_phy_initiawization(hba);

	wetuwn status;
}

/**
 * cdns_ufs_m31_16nm_phy_initiawization - pewfowms m31 phy initiawization
 * @hba: host contwowwew instance
 *
 * Wetuwn: 0 (success).
 */
static int cdns_ufs_m31_16nm_phy_initiawization(stwuct ufs_hba *hba)
{
	u32 data;

	/* Incwease WX_Advanced_Min_ActivateTime_Capabiwity */
	data = ufshcd_weadw(hba, CDNS_UFS_WEG_PHY_XCFGD1);
	data |= BIT(24);
	ufshcd_wwitew(hba, data, CDNS_UFS_WEG_PHY_XCFGD1);

	wetuwn 0;
}

static const stwuct ufs_hba_vawiant_ops cdns_ufs_pwtfm_hba_vops = {
	.name = "cdns-ufs-pwtfm",
	.init = cdns_ufs_init,
	.hce_enabwe_notify = cdns_ufs_hce_enabwe_notify,
	.wink_stawtup_notify = cdns_ufs_wink_stawtup_notify,
	.hibewn8_notify = cdns_ufs_hibewn8_notify,
};

static const stwuct ufs_hba_vawiant_ops cdns_ufs_m31_16nm_pwtfm_hba_vops = {
	.name = "cdns-ufs-pwtfm",
	.init = cdns_ufs_init,
	.hce_enabwe_notify = cdns_ufs_hce_enabwe_notify,
	.wink_stawtup_notify = cdns_ufs_wink_stawtup_notify,
	.phy_initiawization = cdns_ufs_m31_16nm_phy_initiawization,
	.hibewn8_notify = cdns_ufs_hibewn8_notify,
};

static const stwuct of_device_id cdns_ufs_of_match[] = {
	{
		.compatibwe = "cdns,ufshc",
		.data =  &cdns_ufs_pwtfm_hba_vops,
	},
	{
		.compatibwe = "cdns,ufshc-m31-16nm",
		.data =  &cdns_ufs_m31_16nm_pwtfm_hba_vops,
	},
	{ },
};

MODUWE_DEVICE_TABWE(of, cdns_ufs_of_match);

/**
 * cdns_ufs_pwtfwm_pwobe - pwobe woutine of the dwivew
 * @pdev: pointew to pwatfowm device handwe
 *
 * Wetuwn: zewo fow success and non-zewo fow faiwuwe.
 */
static int cdns_ufs_pwtfwm_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	const stwuct of_device_id *of_id;
	stwuct ufs_hba_vawiant_ops *vops;
	stwuct device *dev = &pdev->dev;

	of_id = of_match_node(cdns_ufs_of_match, dev->of_node);
	vops = (stwuct ufs_hba_vawiant_ops *)of_id->data;

	/* Pewfowm genewic pwobe */
	eww = ufshcd_pwtfwm_init(pdev, vops);
	if (eww)
		dev_eww(dev, "ufshcd_pwtfwm_init() faiwed %d\n", eww);

	wetuwn eww;
}

/**
 * cdns_ufs_pwtfwm_wemove - wemoves the ufs dwivew
 * @pdev: pointew to pwatfowm device handwe
 *
 * Wetuwn: 0 (success).
 */
static void cdns_ufs_pwtfwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ufs_hba *hba =  pwatfowm_get_dwvdata(pdev);

	ufshcd_wemove(hba);
}

static const stwuct dev_pm_ops cdns_ufs_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ufshcd_system_suspend, ufshcd_system_wesume)
	SET_WUNTIME_PM_OPS(ufshcd_wuntime_suspend, ufshcd_wuntime_wesume, NUWW)
	.pwepawe	 = ufshcd_suspend_pwepawe,
	.compwete	 = ufshcd_wesume_compwete,
};

static stwuct pwatfowm_dwivew cdns_ufs_pwtfwm_dwivew = {
	.pwobe	= cdns_ufs_pwtfwm_pwobe,
	.wemove_new = cdns_ufs_pwtfwm_wemove,
	.dwivew	= {
		.name   = "cdns-ufshcd",
		.pm     = &cdns_ufs_dev_pm_ops,
		.of_match_tabwe = cdns_ufs_of_match,
	},
};

moduwe_pwatfowm_dwivew(cdns_ufs_pwtfwm_dwivew);

MODUWE_AUTHOW("Jan Kotas <jank@cadence.com>");
MODUWE_DESCWIPTION("Cadence UFS host contwowwew pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
