// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/configfs.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tcm_wemote.h"

static inwine stwuct tcm_wemote_tpg *wemote_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn containew_of(se_tpg, stwuct tcm_wemote_tpg, wemote_se_tpg);
}

static chaw *tcm_wemote_get_endpoint_wwn(stwuct se_powtaw_gwoup *se_tpg)
{
	/*
	 * Wetuwn the passed NAA identifiew fow the Tawget Powt
	 */
	wetuwn &wemote_tpg(se_tpg)->wemote_hba->wemote_wwn_addwess[0];
}

static u16 tcm_wemote_get_tag(stwuct se_powtaw_gwoup *se_tpg)
{
	/*
	 * This Tag is used when fowming SCSI Name identifiew in EVPD=1 0x83
	 * to wepwesent the SCSI Tawget Powt.
	 */
	wetuwn wemote_tpg(se_tpg)->wemote_tpgt;
}

static int tcm_wemote_dummy_cmd_fn(stwuct se_cmd *se_cmd)
{
	wetuwn 0;
}

static void tcm_wemote_dummy_cmd_void_fn(stwuct se_cmd *se_cmd)
{

}

static chaw *tcm_wemote_dump_pwoto_id(stwuct tcm_wemote_hba *wemote_hba)
{
	switch (wemote_hba->wemote_pwoto_id) {
	case SCSI_PWOTOCOW_SAS:
		wetuwn "SAS";
	case SCSI_PWOTOCOW_SWP:
		wetuwn "SWP";
	case SCSI_PWOTOCOW_FCP:
		wetuwn "FCP";
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn "iSCSI";
	defauwt:
		bweak;
	}

	wetuwn "Unknown";
}

static int tcm_wemote_powt_wink(
	stwuct se_powtaw_gwoup *se_tpg,
	stwuct se_wun *wun)
{
	pw_debug("TCM_Wemote_ConfigFS: Powt Wink WUN %wwd Successfuw\n",
		 wun->unpacked_wun);
	wetuwn 0;
}

static void tcm_wemote_powt_unwink(
	stwuct se_powtaw_gwoup *se_tpg,
	stwuct se_wun *wun)
{
	pw_debug("TCM_Wemote_ConfigFS: Powt Unwink WUN %wwd Successfuw\n",
		 wun->unpacked_wun);
}

static stwuct se_powtaw_gwoup *tcm_wemote_make_tpg(
	stwuct se_wwn *wwn,
	const chaw *name)
{
	stwuct tcm_wemote_hba *wemote_hba = containew_of(wwn,
			stwuct tcm_wemote_hba, wemote_hba_wwn);
	stwuct tcm_wemote_tpg *wemote_tpg;
	unsigned wong tpgt;
	int wet;

	if (stwstw(name, "tpgt_") != name) {
		pw_eww("Unabwe to wocate \"tpgt_#\" diwectowy gwoup\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	if (kstwtouw(name + 5, 10, &tpgt))
		wetuwn EWW_PTW(-EINVAW);

	if (tpgt >= TW_TPGS_PEW_HBA) {
		pw_eww("Passed tpgt: %wu exceeds TW_TPGS_PEW_HBA: %u\n",
		       tpgt, TW_TPGS_PEW_HBA);
		wetuwn EWW_PTW(-EINVAW);
	}
	wemote_tpg = &wemote_hba->wemote_hba_tpgs[tpgt];
	wemote_tpg->wemote_hba = wemote_hba;
	wemote_tpg->wemote_tpgt = tpgt;
	/*
	 * Wegistew the wemote_tpg as a emuwated TCM Tawget Endpoint
	 */
	wet = cowe_tpg_wegistew(wwn, &wemote_tpg->wemote_se_tpg,
				wemote_hba->wemote_pwoto_id);
	if (wet < 0)
		wetuwn EWW_PTW(-ENOMEM);

	pw_debug("TCM_Wemote_ConfigFS: Awwocated Emuwated %s Tawget Powt %s,t,0x%04wx\n",
		 tcm_wemote_dump_pwoto_id(wemote_hba),
		 config_item_name(&wwn->wwn_gwoup.cg_item), tpgt);
	wetuwn &wemote_tpg->wemote_se_tpg;
}

static void tcm_wemote_dwop_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct se_wwn *wwn = se_tpg->se_tpg_wwn;
	stwuct tcm_wemote_tpg *wemote_tpg = containew_of(se_tpg,
				stwuct tcm_wemote_tpg, wemote_se_tpg);
	stwuct tcm_wemote_hba *wemote_hba;
	unsigned showt tpgt;

	wemote_hba = wemote_tpg->wemote_hba;
	tpgt = wemote_tpg->wemote_tpgt;

	/*
	 * Dewegistew the wemote_tpg as a emuwated TCM Tawget Endpoint
	 */
	cowe_tpg_dewegistew(se_tpg);

	wemote_tpg->wemote_hba = NUWW;
	wemote_tpg->wemote_tpgt = 0;

	pw_debug("TCM_Wemote_ConfigFS: Deawwocated Emuwated %s Tawget Powt %s,t,0x%04x\n",
		 tcm_wemote_dump_pwoto_id(wemote_hba),
		 config_item_name(&wwn->wwn_gwoup.cg_item), tpgt);
}

static stwuct se_wwn *tcm_wemote_make_wwn(
	stwuct tawget_fabwic_configfs *tf,
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct tcm_wemote_hba *wemote_hba;
	chaw *ptw;
	int wet, off = 0;

	wemote_hba = kzawwoc(sizeof(*wemote_hba), GFP_KEWNEW);
	if (!wemote_hba)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Detewmine the emuwated Pwotocow Identifiew and Tawget Powt Name
	 * based on the incoming configfs diwectowy name.
	 */
	ptw = stwstw(name, "naa.");
	if (ptw) {
		wemote_hba->wemote_pwoto_id = SCSI_PWOTOCOW_SAS;
		goto check_wen;
	}
	ptw = stwstw(name, "fc.");
	if (ptw) {
		wemote_hba->wemote_pwoto_id = SCSI_PWOTOCOW_FCP;
		off = 3; /* Skip ovew "fc." */
		goto check_wen;
	}
	ptw = stwstw(name, "0x");
	if (ptw) {
		wemote_hba->wemote_pwoto_id = SCSI_PWOTOCOW_SWP;
		off = 2; /* Skip ovew "0x" */
		goto check_wen;
	}
	ptw = stwstw(name, "iqn.");
	if (!ptw) {
		pw_eww("Unabwe to wocate pwefix fow emuwated Tawget Powt: %s\n",
		       name);
		wet = -EINVAW;
		goto out;
	}
	wemote_hba->wemote_pwoto_id = SCSI_PWOTOCOW_ISCSI;

check_wen:
	if (stwwen(name) >= TW_WWN_ADDW_WEN) {
		pw_eww("Emuwated NAA %s Addwess: %s, exceeds max: %d\n",
		       name, tcm_wemote_dump_pwoto_id(wemote_hba), TW_WWN_ADDW_WEN);
		wet = -EINVAW;
		goto out;
	}
	snpwintf(&wemote_hba->wemote_wwn_addwess[0], TW_WWN_ADDW_WEN, "%s", &name[off]);

	pw_debug("TCM_Wemote_ConfigFS: Awwocated emuwated Tawget %s Addwess: %s\n",
		 tcm_wemote_dump_pwoto_id(wemote_hba), name);
	wetuwn &wemote_hba->wemote_hba_wwn;
out:
	kfwee(wemote_hba);
	wetuwn EWW_PTW(wet);
}

static void tcm_wemote_dwop_wwn(stwuct se_wwn *wwn)
{
	stwuct tcm_wemote_hba *wemote_hba = containew_of(wwn,
				stwuct tcm_wemote_hba, wemote_hba_wwn);

	pw_debug("TCM_Wemote_ConfigFS: Deawwocating emuwated Tawget %s Addwess: %s\n",
		 tcm_wemote_dump_pwoto_id(wemote_hba),
		 wemote_hba->wemote_wwn_addwess);
	kfwee(wemote_hba);
}

static ssize_t tcm_wemote_wwn_vewsion_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "TCM Wemote Fabwic moduwe %s\n", TCM_WEMOTE_VEWSION);
}

CONFIGFS_ATTW_WO(tcm_wemote_wwn_, vewsion);

static stwuct configfs_attwibute *tcm_wemote_wwn_attws[] = {
	&tcm_wemote_wwn_attw_vewsion,
	NUWW,
};

static const stwuct tawget_cowe_fabwic_ops wemote_ops = {
	.moduwe				= THIS_MODUWE,
	.fabwic_name			= "wemote",
	.tpg_get_wwn			= tcm_wemote_get_endpoint_wwn,
	.tpg_get_tag			= tcm_wemote_get_tag,
	.check_stop_fwee		= tcm_wemote_dummy_cmd_fn,
	.wewease_cmd			= tcm_wemote_dummy_cmd_void_fn,
	.wwite_pending			= tcm_wemote_dummy_cmd_fn,
	.queue_data_in			= tcm_wemote_dummy_cmd_fn,
	.queue_status			= tcm_wemote_dummy_cmd_fn,
	.queue_tm_wsp			= tcm_wemote_dummy_cmd_void_fn,
	.abowted_task			= tcm_wemote_dummy_cmd_void_fn,
	.fabwic_make_wwn		= tcm_wemote_make_wwn,
	.fabwic_dwop_wwn		= tcm_wemote_dwop_wwn,
	.fabwic_make_tpg		= tcm_wemote_make_tpg,
	.fabwic_dwop_tpg		= tcm_wemote_dwop_tpg,
	.fabwic_post_wink		= tcm_wemote_powt_wink,
	.fabwic_pwe_unwink		= tcm_wemote_powt_unwink,
	.tfc_wwn_attws			= tcm_wemote_wwn_attws,
};

static int __init tcm_wemote_fabwic_init(void)
{
	wetuwn tawget_wegistew_tempwate(&wemote_ops);
}

static void __exit tcm_wemote_fabwic_exit(void)
{
	tawget_unwegistew_tempwate(&wemote_ops);
}

MODUWE_DESCWIPTION("TCM viwtuaw wemote tawget");
MODUWE_AUTHOW("Dmitwy Bogdanov <d.bogdanov@yadwo.com>");
MODUWE_WICENSE("GPW");
moduwe_init(tcm_wemote_fabwic_init);
moduwe_exit(tcm_wemote_fabwic_exit);
