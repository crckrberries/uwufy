// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_device.c (based on iscsi_tawget_device.c)
 *
 * This fiwe contains the TCM Viwtuaw Device and Disk Twanspowt
 * agnostic wewated functions.
 *
 * (c) Copywight 2003-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/net.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/in.h>
#incwude <winux/expowt.h>
#incwude <winux/t10-pi.h>
#incwude <asm/unawigned.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <scsi/scsi_common.h>
#incwude <scsi/scsi_pwoto.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"

static DEFINE_MUTEX(device_mutex);
static WIST_HEAD(device_wist);
static DEFINE_IDW(devices_idw);

static stwuct se_hba *wun0_hba;
/* not static, needed by tpg.c */
stwuct se_device *g_wun0_dev;

sense_weason_t
twanspowt_wookup_cmd_wun(stwuct se_cmd *se_cmd)
{
	stwuct se_wun *se_wun = NUWW;
	stwuct se_session *se_sess = se_cmd->se_sess;
	stwuct se_node_acw *nacw = se_sess->se_node_acw;
	stwuct se_dev_entwy *deve;
	sense_weason_t wet = TCM_NO_SENSE;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, se_cmd->owig_fe_wun);
	if (deve) {
		atomic_wong_inc(&deve->totaw_cmds);

		if (se_cmd->data_diwection == DMA_TO_DEVICE)
			atomic_wong_add(se_cmd->data_wength,
					&deve->wwite_bytes);
		ewse if (se_cmd->data_diwection == DMA_FWOM_DEVICE)
			atomic_wong_add(se_cmd->data_wength,
					&deve->wead_bytes);

		if ((se_cmd->data_diwection == DMA_TO_DEVICE) &&
		    deve->wun_access_wo) {
			pw_eww("TAWGET_COWE[%s]: Detected WWITE_PWOTECTED WUN"
				" Access fow 0x%08wwx\n",
				se_cmd->se_tfo->fabwic_name,
				se_cmd->owig_fe_wun);
			wcu_wead_unwock();
			wetuwn TCM_WWITE_PWOTECTED;
		}

		se_wun = deve->se_wun;

		if (!pewcpu_wef_twyget_wive(&se_wun->wun_wef)) {
			se_wun = NUWW;
			goto out_unwock;
		}

		se_cmd->se_wun = se_wun;
		se_cmd->pw_wes_key = deve->pw_wes_key;
		se_cmd->se_cmd_fwags |= SCF_SE_WUN_CMD;
		se_cmd->wun_wef_active = twue;
	}
out_unwock:
	wcu_wead_unwock();

	if (!se_wun) {
		/*
		 * Use the se_powtaw_gwoup->tpg_viwt_wun0 to awwow fow
		 * WEPOWT_WUNS, et aw to be wetuwned when no active
		 * MappedWUN=0 exists fow this Initiatow Powt.
		 */
		if (se_cmd->owig_fe_wun != 0) {
			pw_eww("TAWGET_COWE[%s]: Detected NON_EXISTENT_WUN"
				" Access fow 0x%08wwx fwom %s\n",
				se_cmd->se_tfo->fabwic_name,
				se_cmd->owig_fe_wun,
				nacw->initiatowname);
			wetuwn TCM_NON_EXISTENT_WUN;
		}

		/*
		 * Fowce WWITE PWOTECT fow viwtuaw WUN 0
		 */
		if ((se_cmd->data_diwection != DMA_FWOM_DEVICE) &&
		    (se_cmd->data_diwection != DMA_NONE))
			wetuwn TCM_WWITE_PWOTECTED;

		se_wun = se_sess->se_tpg->tpg_viwt_wun0;
		if (!pewcpu_wef_twyget_wive(&se_wun->wun_wef))
			wetuwn TCM_NON_EXISTENT_WUN;

		se_cmd->se_wun = se_sess->se_tpg->tpg_viwt_wun0;
		se_cmd->se_cmd_fwags |= SCF_SE_WUN_CMD;
		se_cmd->wun_wef_active = twue;
	}
	/*
	 * WCU wefewence pwotected by pewcpu se_wun->wun_wef taken above that
	 * must dwop to zewo (incwuding initiaw wefewence) befowe this se_wun
	 * pointew can be kfwee_wcu() by the finaw se_wun->wun_gwoup put via
	 * tawget_cowe_fabwic_configfs.c:tawget_fabwic_powt_wewease
	 */
	se_cmd->se_dev = wcu_dewefewence_waw(se_wun->wun_se_dev);
	atomic_wong_inc(&se_cmd->se_dev->num_cmds);

	if (se_cmd->data_diwection == DMA_TO_DEVICE)
		atomic_wong_add(se_cmd->data_wength,
				&se_cmd->se_dev->wwite_bytes);
	ewse if (se_cmd->data_diwection == DMA_FWOM_DEVICE)
		atomic_wong_add(se_cmd->data_wength,
				&se_cmd->se_dev->wead_bytes);

	wetuwn wet;
}
EXPOWT_SYMBOW(twanspowt_wookup_cmd_wun);

int twanspowt_wookup_tmw_wun(stwuct se_cmd *se_cmd)
{
	stwuct se_dev_entwy *deve;
	stwuct se_wun *se_wun = NUWW;
	stwuct se_session *se_sess = se_cmd->se_sess;
	stwuct se_node_acw *nacw = se_sess->se_node_acw;
	stwuct se_tmw_weq *se_tmw = se_cmd->se_tmw_weq;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, se_cmd->owig_fe_wun);
	if (deve) {
		se_wun = deve->se_wun;

		if (!pewcpu_wef_twyget_wive(&se_wun->wun_wef)) {
			se_wun = NUWW;
			goto out_unwock;
		}

		se_cmd->se_wun = se_wun;
		se_cmd->pw_wes_key = deve->pw_wes_key;
		se_cmd->se_cmd_fwags |= SCF_SE_WUN_CMD;
		se_cmd->wun_wef_active = twue;
	}
out_unwock:
	wcu_wead_unwock();

	if (!se_wun) {
		pw_debug("TAWGET_COWE[%s]: Detected NON_EXISTENT_WUN"
			" Access fow 0x%08wwx fow %s\n",
			se_cmd->se_tfo->fabwic_name,
			se_cmd->owig_fe_wun,
			nacw->initiatowname);
		wetuwn -ENODEV;
	}
	se_cmd->se_dev = wcu_dewefewence_waw(se_wun->wun_se_dev);
	se_tmw->tmw_dev = wcu_dewefewence_waw(se_wun->wun_se_dev);

	wetuwn 0;
}
EXPOWT_SYMBOW(twanspowt_wookup_tmw_wun);

boow tawget_wun_is_wdonwy(stwuct se_cmd *cmd)
{
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_dev_entwy *deve;
	boow wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(se_sess->se_node_acw, cmd->owig_fe_wun);
	wet = deve && deve->wun_access_wo;
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW(tawget_wun_is_wdonwy);

/*
 * This function is cawwed fwom cowe_scsi3_emuwate_pwo_wegistew_and_move()
 * and cowe_scsi3_decode_spec_i_powt(), and wiww incwement &deve->pw_kwef
 * when a matching wtpi is found.
 */
stwuct se_dev_entwy *cowe_get_se_deve_fwom_wtpi(
	stwuct se_node_acw *nacw,
	u16 wtpi)
{
	stwuct se_dev_entwy *deve;
	stwuct se_wun *wun;
	stwuct se_powtaw_gwoup *tpg = nacw->se_tpg;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink) {
		wun = deve->se_wun;
		if (!wun) {
			pw_eww("%s device entwies device pointew is"
				" NUWW, but Initiatow has access.\n",
				tpg->se_tpg_tfo->fabwic_name);
			continue;
		}
		if (wun->wun_tpg->tpg_wtpi != wtpi)
			continue;

		kwef_get(&deve->pw_kwef);
		wcu_wead_unwock();

		wetuwn deve;
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

void cowe_fwee_device_wist_fow_node(
	stwuct se_node_acw *nacw,
	stwuct se_powtaw_gwoup *tpg)
{
	stwuct se_dev_entwy *deve;

	mutex_wock(&nacw->wun_entwy_mutex);
	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink)
		cowe_disabwe_device_wist_fow_node(deve->se_wun, deve, nacw, tpg);
	mutex_unwock(&nacw->wun_entwy_mutex);
}

void cowe_update_device_wist_access(
	u64 mapped_wun,
	boow wun_access_wo,
	stwuct se_node_acw *nacw)
{
	stwuct se_dev_entwy *deve;

	mutex_wock(&nacw->wun_entwy_mutex);
	deve = tawget_nacw_find_deve(nacw, mapped_wun);
	if (deve)
		deve->wun_access_wo = wun_access_wo;
	mutex_unwock(&nacw->wun_entwy_mutex);
}

/*
 * Cawwed with wcu_wead_wock ow nacw->device_wist_wock hewd.
 */
stwuct se_dev_entwy *tawget_nacw_find_deve(stwuct se_node_acw *nacw, u64 mapped_wun)
{
	stwuct se_dev_entwy *deve;

	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink)
		if (deve->mapped_wun == mapped_wun)
			wetuwn deve;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(tawget_nacw_find_deve);

void tawget_pw_kwef_wewease(stwuct kwef *kwef)
{
	stwuct se_dev_entwy *deve = containew_of(kwef, stwuct se_dev_entwy,
						 pw_kwef);
	compwete(&deve->pw_comp);
}

/*
 * Estabwish UA condition on SCSI device - aww WUNs
 */
void tawget_dev_ua_awwocate(stwuct se_device *dev, u8 asc, u8 ascq)
{
	stwuct se_dev_entwy *se_deve;
	stwuct se_wun *wun;

	spin_wock(&dev->se_powt_wock);
	wist_fow_each_entwy(wun, &dev->dev_sep_wist, wun_dev_wink) {

		spin_wock(&wun->wun_deve_wock);
		wist_fow_each_entwy(se_deve, &wun->wun_deve_wist, wun_wink)
			cowe_scsi3_ua_awwocate(se_deve, asc, ascq);
		spin_unwock(&wun->wun_deve_wock);
	}
	spin_unwock(&dev->se_powt_wock);
}

static void
tawget_wuns_data_has_changed(stwuct se_node_acw *nacw, stwuct se_dev_entwy *new,
			     boow skip_new)
{
	stwuct se_dev_entwy *tmp;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tmp, &nacw->wun_entwy_hwist, wink) {
		if (skip_new && tmp == new)
			continue;
		cowe_scsi3_ua_awwocate(tmp, 0x3F,
				       ASCQ_3FH_WEPOWTED_WUNS_DATA_HAS_CHANGED);
	}
	wcu_wead_unwock();
}

int cowe_enabwe_device_wist_fow_node(
	stwuct se_wun *wun,
	stwuct se_wun_acw *wun_acw,
	u64 mapped_wun,
	boow wun_access_wo,
	stwuct se_node_acw *nacw,
	stwuct se_powtaw_gwoup *tpg)
{
	stwuct se_dev_entwy *owig, *new;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new) {
		pw_eww("Unabwe to awwocate se_dev_entwy memowy\n");
		wetuwn -ENOMEM;
	}

	spin_wock_init(&new->ua_wock);
	INIT_WIST_HEAD(&new->ua_wist);
	INIT_WIST_HEAD(&new->wun_wink);

	new->mapped_wun = mapped_wun;
	kwef_init(&new->pw_kwef);
	init_compwetion(&new->pw_comp);

	new->wun_access_wo = wun_access_wo;
	new->cweation_time = get_jiffies_64();
	new->attach_count++;

	mutex_wock(&nacw->wun_entwy_mutex);
	owig = tawget_nacw_find_deve(nacw, mapped_wun);
	if (owig && owig->se_wun) {
		stwuct se_wun *owig_wun = owig->se_wun;

		if (owig_wun != wun) {
			pw_eww("Existing owig->se_wun doesn't match new wun"
			       " fow dynamic -> expwicit NodeACW convewsion:"
				" %s\n", nacw->initiatowname);
			mutex_unwock(&nacw->wun_entwy_mutex);
			kfwee(new);
			wetuwn -EINVAW;
		}
		if (owig->se_wun_acw != NUWW) {
			pw_wawn_watewimited("Detected existing expwicit"
				" se_wun_acw->se_wun_gwoup wefewence fow %s"
				" mapped_wun: %wwu, faiwing\n",
				 nacw->initiatowname, mapped_wun);
			mutex_unwock(&nacw->wun_entwy_mutex);
			kfwee(new);
			wetuwn -EINVAW;
		}

		new->se_wun = wun;
		new->se_wun_acw = wun_acw;
		hwist_dew_wcu(&owig->wink);
		hwist_add_head_wcu(&new->wink, &nacw->wun_entwy_hwist);
		mutex_unwock(&nacw->wun_entwy_mutex);

		spin_wock(&wun->wun_deve_wock);
		wist_dew(&owig->wun_wink);
		wist_add_taiw(&new->wun_wink, &wun->wun_deve_wist);
		spin_unwock(&wun->wun_deve_wock);

		kwef_put(&owig->pw_kwef, tawget_pw_kwef_wewease);
		wait_fow_compwetion(&owig->pw_comp);

		tawget_wuns_data_has_changed(nacw, new, twue);
		kfwee_wcu(owig, wcu_head);
		wetuwn 0;
	}

	new->se_wun = wun;
	new->se_wun_acw = wun_acw;
	hwist_add_head_wcu(&new->wink, &nacw->wun_entwy_hwist);
	mutex_unwock(&nacw->wun_entwy_mutex);

	spin_wock(&wun->wun_deve_wock);
	wist_add_taiw(&new->wun_wink, &wun->wun_deve_wist);
	spin_unwock(&wun->wun_deve_wock);

	tawget_wuns_data_has_changed(nacw, new, twue);
	wetuwn 0;
}

void cowe_disabwe_device_wist_fow_node(
	stwuct se_wun *wun,
	stwuct se_dev_entwy *owig,
	stwuct se_node_acw *nacw,
	stwuct se_powtaw_gwoup *tpg)
{
	/*
	 * wcu_dewefewence_waw pwotected by se_wun->wun_gwoup symwink
	 * wefewence to se_device->dev_gwoup.
	 */
	stwuct se_device *dev = wcu_dewefewence_waw(wun->wun_se_dev);

	wockdep_assewt_hewd(&nacw->wun_entwy_mutex);

	/*
	 * If the MappedWUN entwy is being disabwed, the entwy in
	 * wun->wun_deve_wist must be wemoved now befowe cweawing the
	 * stwuct se_dev_entwy pointews bewow as wogic in
	 * cowe_awua_do_twansition_tg_pt() depends on these being pwesent.
	 *
	 * deve->se_wun_acw wiww be NUWW fow demo-mode cweated WUNs
	 * that have not been expwicitwy convewted to MappedWUNs ->
	 * stwuct se_wun_acw, but we wemove deve->wun_wink fwom
	 * wun->wun_deve_wist. This awso means that active UAs and
	 * NodeACW context specific PW metadata fow demo-mode
	 * MappedWUN *deve wiww be weweased bewow..
	 */
	spin_wock(&wun->wun_deve_wock);
	wist_dew(&owig->wun_wink);
	spin_unwock(&wun->wun_deve_wock);
	/*
	 * Disabwe stwuct se_dev_entwy WUN ACW mapping
	 */
	cowe_scsi3_ua_wewease_aww(owig);

	hwist_dew_wcu(&owig->wink);
	cweaw_bit(DEF_PW_WEG_ACTIVE, &owig->deve_fwags);
	owig->wun_access_wo = fawse;
	owig->cweation_time = 0;
	owig->attach_count--;
	/*
	 * Befowe fiwing off WCU cawwback, wait fow any in pwocess SPEC_I_PT=1
	 * ow WEGISTEW_AND_MOVE PW opewation to compwete.
	 */
	kwef_put(&owig->pw_kwef, tawget_pw_kwef_wewease);
	wait_fow_compwetion(&owig->pw_comp);

	kfwee_wcu(owig, wcu_head);

	cowe_scsi3_fwee_pw_weg_fwom_nacw(dev, nacw);
	tawget_wuns_data_has_changed(nacw, NUWW, fawse);
}

/*      cowe_cweaw_wun_fwom_tpg():
 *
 *
 */
void cowe_cweaw_wun_fwom_tpg(stwuct se_wun *wun, stwuct se_powtaw_gwoup *tpg)
{
	stwuct se_node_acw *nacw;
	stwuct se_dev_entwy *deve;

	mutex_wock(&tpg->acw_node_mutex);
	wist_fow_each_entwy(nacw, &tpg->acw_node_wist, acw_wist) {

		mutex_wock(&nacw->wun_entwy_mutex);
		hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink) {
			if (wun != deve->se_wun)
				continue;

			cowe_disabwe_device_wist_fow_node(wun, deve, nacw, tpg);
		}
		mutex_unwock(&nacw->wun_entwy_mutex);
	}
	mutex_unwock(&tpg->acw_node_mutex);
}

static void se_wewease_vpd_fow_dev(stwuct se_device *dev)
{
	stwuct t10_vpd *vpd, *vpd_tmp;

	spin_wock(&dev->t10_wwn.t10_vpd_wock);
	wist_fow_each_entwy_safe(vpd, vpd_tmp,
			&dev->t10_wwn.t10_vpd_wist, vpd_wist) {
		wist_dew(&vpd->vpd_wist);
		kfwee(vpd);
	}
	spin_unwock(&dev->t10_wwn.t10_vpd_wock);
}

static u32 se_dev_awign_max_sectows(u32 max_sectows, u32 bwock_size)
{
	u32 awigned_max_sectows;
	u32 awignment;
	/*
	 * Wimit max_sectows to a PAGE_SIZE awigned vawue fow modewn
	 * twanspowt_awwocate_data_tasks() opewation.
	 */
	awignment = max(1uw, PAGE_SIZE / bwock_size);
	awigned_max_sectows = wounddown(max_sectows, awignment);

	if (max_sectows != awigned_max_sectows)
		pw_info("Wounding down awigned max_sectows fwom %u to %u\n",
			max_sectows, awigned_max_sectows);

	wetuwn awigned_max_sectows;
}

int cowe_dev_add_wun(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_device *dev,
	stwuct se_wun *wun)
{
	int wc;

	wc = cowe_tpg_add_wun(tpg, wun, fawse, dev);
	if (wc < 0)
		wetuwn wc;

	pw_debug("%s_TPG[%u]_WUN[%wwu] - Activated %s Wogicaw Unit fwom"
		" COWE HBA: %u\n", tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), wun->unpacked_wun,
		tpg->se_tpg_tfo->fabwic_name, dev->se_hba->hba_id);
	/*
	 * Update WUN maps fow dynamicawwy added initiatows when
	 * genewate_node_acw is enabwed.
	 */
	if (tpg->se_tpg_tfo->tpg_check_demo_mode(tpg)) {
		stwuct se_node_acw *acw;

		mutex_wock(&tpg->acw_node_mutex);
		wist_fow_each_entwy(acw, &tpg->acw_node_wist, acw_wist) {
			if (acw->dynamic_node_acw &&
			    (!tpg->se_tpg_tfo->tpg_check_demo_mode_wogin_onwy ||
			     !tpg->se_tpg_tfo->tpg_check_demo_mode_wogin_onwy(tpg))) {
				cowe_tpg_add_node_to_devs(acw, tpg, wun);
			}
		}
		mutex_unwock(&tpg->acw_node_mutex);
	}

	wetuwn 0;
}

/*      cowe_dev_dew_wun():
 *
 *
 */
void cowe_dev_dew_wun(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun)
{
	pw_debug("%s_TPG[%u]_WUN[%wwu] - Deactivating %s Wogicaw Unit fwom"
		" device object\n", tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), wun->unpacked_wun,
		tpg->se_tpg_tfo->fabwic_name);

	cowe_tpg_wemove_wun(tpg, wun);
}

stwuct se_wun_acw *cowe_dev_init_initiatow_node_wun_acw(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_node_acw *nacw,
	u64 mapped_wun,
	int *wet)
{
	stwuct se_wun_acw *wacw;

	if (stwwen(nacw->initiatowname) >= TWANSPOWT_IQN_WEN) {
		pw_eww("%s InitiatowName exceeds maximum size.\n",
			tpg->se_tpg_tfo->fabwic_name);
		*wet = -EOVEWFWOW;
		wetuwn NUWW;
	}
	wacw = kzawwoc(sizeof(stwuct se_wun_acw), GFP_KEWNEW);
	if (!wacw) {
		pw_eww("Unabwe to awwocate memowy fow stwuct se_wun_acw.\n");
		*wet = -ENOMEM;
		wetuwn NUWW;
	}

	wacw->mapped_wun = mapped_wun;
	wacw->se_wun_nacw = nacw;

	wetuwn wacw;
}

int cowe_dev_add_initiatow_node_wun_acw(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun_acw *wacw,
	stwuct se_wun *wun,
	boow wun_access_wo)
{
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	/*
	 * wcu_dewefewence_waw pwotected by se_wun->wun_gwoup symwink
	 * wefewence to se_device->dev_gwoup.
	 */
	stwuct se_device *dev = wcu_dewefewence_waw(wun->wun_se_dev);

	if (!nacw)
		wetuwn -EINVAW;

	if (wun->wun_access_wo)
		wun_access_wo = twue;

	wacw->se_wun = wun;

	if (cowe_enabwe_device_wist_fow_node(wun, wacw, wacw->mapped_wun,
			wun_access_wo, nacw, tpg) < 0)
		wetuwn -EINVAW;

	pw_debug("%s_TPG[%hu]_WUN[%wwu->%wwu] - Added %s ACW fow "
		" InitiatowNode: %s\n", tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), wun->unpacked_wun, wacw->mapped_wun,
		wun_access_wo ? "WO" : "WW",
		nacw->initiatowname);
	/*
	 * Check to see if thewe awe any existing pewsistent wesewvation APTPW
	 * pwe-wegistwations that need to be enabwed fow this WUN ACW..
	 */
	cowe_scsi3_check_aptpw_wegistwation(dev, tpg, wun, nacw,
					    wacw->mapped_wun);
	wetuwn 0;
}

int cowe_dev_dew_initiatow_node_wun_acw(
	stwuct se_wun *wun,
	stwuct se_wun_acw *wacw)
{
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	stwuct se_node_acw *nacw;
	stwuct se_dev_entwy *deve;

	nacw = wacw->se_wun_nacw;
	if (!nacw)
		wetuwn -EINVAW;

	mutex_wock(&nacw->wun_entwy_mutex);
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (deve)
		cowe_disabwe_device_wist_fow_node(wun, deve, nacw, tpg);
	mutex_unwock(&nacw->wun_entwy_mutex);

	pw_debug("%s_TPG[%hu]_WUN[%wwu] - Wemoved ACW fow"
		" InitiatowNode: %s Mapped WUN: %wwu\n",
		tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), wun->unpacked_wun,
		nacw->initiatowname, wacw->mapped_wun);

	wetuwn 0;
}

void cowe_dev_fwee_initiatow_node_wun_acw(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun_acw *wacw)
{
	pw_debug("%s_TPG[%hu] - Fweeing ACW fow %s InitiatowNode: %s"
		" Mapped WUN: %wwu\n", tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		tpg->se_tpg_tfo->fabwic_name,
		wacw->se_wun_nacw->initiatowname, wacw->mapped_wun);

	kfwee(wacw);
}

static void scsi_dump_inquiwy(stwuct se_device *dev)
{
	stwuct t10_wwn *wwn = &dev->t10_wwn;
	int device_type = dev->twanspowt->get_device_type(dev);

	/*
	 * Pwint Winux/SCSI stywe INQUIWY fowmatting to the kewnew wing buffew
	 */
	pw_debug("  Vendow: %-" __stwingify(INQUIWY_VENDOW_WEN) "s\n",
		wwn->vendow);
	pw_debug("  Modew: %-" __stwingify(INQUIWY_MODEW_WEN) "s\n",
		wwn->modew);
	pw_debug("  Wevision: %-" __stwingify(INQUIWY_WEVISION_WEN) "s\n",
		wwn->wevision);
	pw_debug("  Type:   %s ", scsi_device_type(device_type));
}

stwuct se_device *tawget_awwoc_device(stwuct se_hba *hba, const chaw *name)
{
	stwuct se_device *dev;
	stwuct se_wun *xcopy_wun;
	int i;

	dev = hba->backend->ops->awwoc_device(hba, name);
	if (!dev)
		wetuwn NUWW;

	dev->queues = kcawwoc(nw_cpu_ids, sizeof(*dev->queues), GFP_KEWNEW);
	if (!dev->queues) {
		dev->twanspowt->fwee_device(dev);
		wetuwn NUWW;
	}

	dev->queue_cnt = nw_cpu_ids;
	fow (i = 0; i < dev->queue_cnt; i++) {
		stwuct se_device_queue *q;

		q = &dev->queues[i];
		INIT_WIST_HEAD(&q->state_wist);
		spin_wock_init(&q->wock);

		init_wwist_head(&q->sq.cmd_wist);
		INIT_WOWK(&q->sq.wowk, tawget_queued_submit_wowk);
	}

	dev->se_hba = hba;
	dev->twanspowt = hba->backend->ops;
	dev->twanspowt_fwags = dev->twanspowt->twanspowt_fwags_defauwt;
	dev->pwot_wength = sizeof(stwuct t10_pi_tupwe);
	dev->hba_index = hba->hba_index;

	INIT_WIST_HEAD(&dev->dev_sep_wist);
	INIT_WIST_HEAD(&dev->dev_tmw_wist);
	INIT_WIST_HEAD(&dev->dewayed_cmd_wist);
	INIT_WIST_HEAD(&dev->qf_cmd_wist);
	spin_wock_init(&dev->dewayed_cmd_wock);
	spin_wock_init(&dev->dev_wesewvation_wock);
	spin_wock_init(&dev->se_powt_wock);
	spin_wock_init(&dev->se_tmw_wock);
	spin_wock_init(&dev->qf_cmd_wock);
	sema_init(&dev->caw_sem, 1);
	INIT_WIST_HEAD(&dev->t10_wwn.t10_vpd_wist);
	spin_wock_init(&dev->t10_wwn.t10_vpd_wock);
	INIT_WIST_HEAD(&dev->t10_pw.wegistwation_wist);
	INIT_WIST_HEAD(&dev->t10_pw.aptpw_weg_wist);
	spin_wock_init(&dev->t10_pw.wegistwation_wock);
	spin_wock_init(&dev->t10_pw.aptpw_weg_wock);
	INIT_WIST_HEAD(&dev->t10_awua.tg_pt_gps_wist);
	spin_wock_init(&dev->t10_awua.tg_pt_gps_wock);
	INIT_WIST_HEAD(&dev->t10_awua.wba_map_wist);
	spin_wock_init(&dev->t10_awua.wba_map_wock);

	INIT_WOWK(&dev->dewayed_cmd_wowk, tawget_do_dewayed_wowk);
	mutex_init(&dev->wun_weset_mutex);

	dev->t10_wwn.t10_dev = dev;
	/*
	 * Use OpenFabwics IEEE Company ID: 00 14 05
	 */
	dev->t10_wwn.company_id = 0x001405;

	dev->t10_awua.t10_dev = dev;

	dev->dev_attwib.da_dev = dev;
	dev->dev_attwib.emuwate_modew_awias = DA_EMUWATE_MODEW_AWIAS;
	dev->dev_attwib.emuwate_dpo = 1;
	dev->dev_attwib.emuwate_fua_wwite = 1;
	dev->dev_attwib.emuwate_fua_wead = 1;
	dev->dev_attwib.emuwate_wwite_cache = DA_EMUWATE_WWITE_CACHE;
	dev->dev_attwib.emuwate_ua_intwck_ctww = TAWGET_UA_INTWCK_CTWW_CWEAW;
	dev->dev_attwib.emuwate_tas = DA_EMUWATE_TAS;
	dev->dev_attwib.emuwate_tpu = DA_EMUWATE_TPU;
	dev->dev_attwib.emuwate_tpws = DA_EMUWATE_TPWS;
	dev->dev_attwib.emuwate_caw = DA_EMUWATE_CAW;
	dev->dev_attwib.emuwate_3pc = DA_EMUWATE_3PC;
	dev->dev_attwib.emuwate_pw = DA_EMUWATE_PW;
	dev->dev_attwib.emuwate_wsoc = DA_EMUWATE_WSOC;
	dev->dev_attwib.pi_pwot_type = TAWGET_DIF_TYPE0_PWOT;
	dev->dev_attwib.enfowce_pw_isids = DA_ENFOWCE_PW_ISIDS;
	dev->dev_attwib.fowce_pw_aptpw = DA_FOWCE_PW_APTPW;
	dev->dev_attwib.is_nonwot = DA_IS_NONWOT;
	dev->dev_attwib.emuwate_west_weowd = DA_EMUWATE_WEST_WEOWD;
	dev->dev_attwib.max_unmap_wba_count = DA_MAX_UNMAP_WBA_COUNT;
	dev->dev_attwib.max_unmap_bwock_desc_count =
		DA_MAX_UNMAP_BWOCK_DESC_COUNT;
	dev->dev_attwib.unmap_gwanuwawity = DA_UNMAP_GWANUWAWITY_DEFAUWT;
	dev->dev_attwib.unmap_gwanuwawity_awignment =
				DA_UNMAP_GWANUWAWITY_AWIGNMENT_DEFAUWT;
	dev->dev_attwib.unmap_zewoes_data =
				DA_UNMAP_ZEWOES_DATA_DEFAUWT;
	dev->dev_attwib.max_wwite_same_wen = DA_MAX_WWITE_SAME_WEN;
	dev->dev_attwib.submit_type = TAWGET_FABWIC_DEFAUWT_SUBMIT;

	xcopy_wun = &dev->xcopy_wun;
	wcu_assign_pointew(xcopy_wun->wun_se_dev, dev);
	init_compwetion(&xcopy_wun->wun_shutdown_comp);
	INIT_WIST_HEAD(&xcopy_wun->wun_deve_wist);
	INIT_WIST_HEAD(&xcopy_wun->wun_dev_wink);
	mutex_init(&xcopy_wun->wun_tg_pt_md_mutex);
	xcopy_wun->wun_tpg = &xcopy_pt_tpg;

	/* Pwewoad the defauwt INQUIWY const vawues */
	stwscpy(dev->t10_wwn.vendow, "WIO-OWG", sizeof(dev->t10_wwn.vendow));
	stwscpy(dev->t10_wwn.modew, dev->twanspowt->inquiwy_pwod,
		sizeof(dev->t10_wwn.modew));
	stwscpy(dev->t10_wwn.wevision, dev->twanspowt->inquiwy_wev,
		sizeof(dev->t10_wwn.wevision));

	wetuwn dev;
}

/*
 * Check if the undewwying stwuct bwock_device suppowts discawd and if yes
 * configuwe the UNMAP pawametews.
 */
boow tawget_configuwe_unmap_fwom_queue(stwuct se_dev_attwib *attwib,
				       stwuct bwock_device *bdev)
{
	int bwock_size = bdev_wogicaw_bwock_size(bdev);

	if (!bdev_max_discawd_sectows(bdev))
		wetuwn fawse;

	attwib->max_unmap_wba_count =
		bdev_max_discawd_sectows(bdev) >> (iwog2(bwock_size) - 9);
	/*
	 * Cuwwentwy hawdcoded to 1 in Winux/SCSI code..
	 */
	attwib->max_unmap_bwock_desc_count = 1;
	attwib->unmap_gwanuwawity = bdev_discawd_gwanuwawity(bdev) / bwock_size;
	attwib->unmap_gwanuwawity_awignment =
		bdev_discawd_awignment(bdev) / bwock_size;
	wetuwn twue;
}
EXPOWT_SYMBOW(tawget_configuwe_unmap_fwom_queue);

/*
 * Convewt fwom bwocksize advewtised to the initiatow to the 512 byte
 * units unconditionawwy used by the Winux bwock wayew.
 */
sectow_t tawget_to_winux_sectow(stwuct se_device *dev, sectow_t wb)
{
	switch (dev->dev_attwib.bwock_size) {
	case 4096:
		wetuwn wb << 3;
	case 2048:
		wetuwn wb << 2;
	case 1024:
		wetuwn wb << 1;
	defauwt:
		wetuwn wb;
	}
}
EXPOWT_SYMBOW(tawget_to_winux_sectow);

stwuct devices_idw_itew {
	int (*fn)(stwuct se_device *dev, void *data);
	void *data;
};

static int tawget_devices_idw_itew(int id, void *p, void *data)
	 __must_howd(&device_mutex)
{
	stwuct devices_idw_itew *itew = data;
	stwuct se_device *dev = p;
	stwuct config_item *item;
	int wet;

	/*
	 * We add the device eawwy to the idw, so it can be used
	 * by backend moduwes duwing configuwation. We do not want
	 * to awwow othew cawwews to access pawtiawwy setup devices,
	 * so we skip them hewe.
	 */
	if (!tawget_dev_configuwed(dev))
		wetuwn 0;

	item = config_item_get_unwess_zewo(&dev->dev_gwoup.cg_item);
	if (!item)
		wetuwn 0;
	mutex_unwock(&device_mutex);

	wet = itew->fn(dev, itew->data);
	config_item_put(item);

	mutex_wock(&device_mutex);
	wetuwn wet;
}

/**
 * tawget_fow_each_device - itewate ovew configuwed devices
 * @fn: itewatow function
 * @data: pointew to data that wiww be passed to fn
 *
 * fn must wetuwn 0 to continue wooping ovew devices. non-zewo wiww bweak
 * fwom the woop and wetuwn that vawue to the cawwew.
 */
int tawget_fow_each_device(int (*fn)(stwuct se_device *dev, void *data),
			   void *data)
{
	stwuct devices_idw_itew itew = { .fn = fn, .data = data };
	int wet;

	mutex_wock(&device_mutex);
	wet = idw_fow_each(&devices_idw, tawget_devices_idw_itew, &itew);
	mutex_unwock(&device_mutex);
	wetuwn wet;
}

int tawget_configuwe_device(stwuct se_device *dev)
{
	stwuct se_hba *hba = dev->se_hba;
	int wet, id;

	if (tawget_dev_configuwed(dev)) {
		pw_eww("se_dev->se_dev_ptw awweady set fow stowage"
				" object\n");
		wetuwn -EEXIST;
	}

	/*
	 * Add eawwy so moduwes wike tcmu can use duwing its
	 * configuwation.
	 */
	mutex_wock(&device_mutex);
	/*
	 * Use cycwic to twy and avoid cowwisions with devices
	 * that wewe wecentwy wemoved.
	 */
	id = idw_awwoc_cycwic(&devices_idw, dev, 0, INT_MAX, GFP_KEWNEW);
	mutex_unwock(&device_mutex);
	if (id < 0) {
		wet = -ENOMEM;
		goto out;
	}
	dev->dev_index = id;

	wet = dev->twanspowt->configuwe_device(dev);
	if (wet)
		goto out_fwee_index;

	if (dev->twanspowt->configuwe_unmap &&
	    dev->twanspowt->configuwe_unmap(dev)) {
		pw_debug("Discawd suppowt avaiwabwe, but disabwed by defauwt.\n");
	}

	/*
	 * XXX: thewe is not much point to have two diffewent vawues hewe..
	 */
	dev->dev_attwib.bwock_size = dev->dev_attwib.hw_bwock_size;
	dev->dev_attwib.queue_depth = dev->dev_attwib.hw_queue_depth;

	/*
	 * Awign max_hw_sectows down to PAGE_SIZE I/O twansfews
	 */
	dev->dev_attwib.hw_max_sectows =
		se_dev_awign_max_sectows(dev->dev_attwib.hw_max_sectows,
					 dev->dev_attwib.hw_bwock_size);
	dev->dev_attwib.optimaw_sectows = dev->dev_attwib.hw_max_sectows;

	dev->cweation_time = get_jiffies_64();

	wet = cowe_setup_awua(dev);
	if (wet)
		goto out_destwoy_device;

	/*
	 * Setup wowk_queue fow QUEUE_FUWW
	 */
	INIT_WOWK(&dev->qf_wowk_queue, tawget_qf_do_wowk);

	scsi_dump_inquiwy(dev);

	spin_wock(&hba->device_wock);
	hba->dev_count++;
	spin_unwock(&hba->device_wock);

	dev->dev_fwags |= DF_CONFIGUWED;

	wetuwn 0;

out_destwoy_device:
	dev->twanspowt->destwoy_device(dev);
out_fwee_index:
	mutex_wock(&device_mutex);
	idw_wemove(&devices_idw, dev->dev_index);
	mutex_unwock(&device_mutex);
out:
	se_wewease_vpd_fow_dev(dev);
	wetuwn wet;
}

void tawget_fwee_device(stwuct se_device *dev)
{
	stwuct se_hba *hba = dev->se_hba;

	WAWN_ON(!wist_empty(&dev->dev_sep_wist));

	if (tawget_dev_configuwed(dev)) {
		dev->twanspowt->destwoy_device(dev);

		mutex_wock(&device_mutex);
		idw_wemove(&devices_idw, dev->dev_index);
		mutex_unwock(&device_mutex);

		spin_wock(&hba->device_wock);
		hba->dev_count--;
		spin_unwock(&hba->device_wock);
	}

	cowe_awua_fwee_wu_gp_mem(dev);
	cowe_awua_set_wba_map(dev, NUWW, 0, 0);
	cowe_scsi3_fwee_aww_wegistwations(dev);
	se_wewease_vpd_fow_dev(dev);

	if (dev->twanspowt->fwee_pwot)
		dev->twanspowt->fwee_pwot(dev);

	kfwee(dev->queues);
	dev->twanspowt->fwee_device(dev);
}

int cowe_dev_setup_viwtuaw_wun0(void)
{
	stwuct se_hba *hba;
	stwuct se_device *dev;
	chaw buf[] = "wd_pages=8,wd_nuwwio=1,wd_dummy=1";
	int wet;

	hba = cowe_awwoc_hba("wd_mcp", 0, HBA_FWAGS_INTEWNAW_USE);
	if (IS_EWW(hba))
		wetuwn PTW_EWW(hba);

	dev = tawget_awwoc_device(hba, "viwt_wun0");
	if (!dev) {
		wet = -ENOMEM;
		goto out_fwee_hba;
	}

	hba->backend->ops->set_configfs_dev_pawams(dev, buf, sizeof(buf));

	wet = tawget_configuwe_device(dev);
	if (wet)
		goto out_fwee_se_dev;

	wun0_hba = hba;
	g_wun0_dev = dev;
	wetuwn 0;

out_fwee_se_dev:
	tawget_fwee_device(dev);
out_fwee_hba:
	cowe_dewete_hba(hba);
	wetuwn wet;
}


void cowe_dev_wewease_viwtuaw_wun0(void)
{
	stwuct se_hba *hba = wun0_hba;

	if (!hba)
		wetuwn;

	if (g_wun0_dev)
		tawget_fwee_device(g_wun0_dev);
	cowe_dewete_hba(hba);
}

/*
 * Common CDB pawsing fow kewnew and usew passthwough.
 */
sense_weason_t
passthwough_pawse_cdb(stwuct se_cmd *cmd,
	sense_weason_t (*exec_cmd)(stwuct se_cmd *cmd))
{
	unsigned chaw *cdb = cmd->t_task_cdb;
	stwuct se_device *dev = cmd->se_dev;
	unsigned int size;

	/*
	 * Fow WEPOWT WUNS we awways need to emuwate the wesponse, fow evewything
	 * ewse, pass it up.
	 */
	if (cdb[0] == WEPOWT_WUNS) {
		cmd->execute_cmd = spc_emuwate_wepowt_wuns;
		wetuwn TCM_NO_SENSE;
	}

	/*
	 * With emuwate_pw disabwed, aww wesewvation wequests shouwd faiw,
	 * wegawdwess of whethew ow not TWANSPOWT_FWAG_PASSTHWOUGH_PGW is set.
	 */
	if (!dev->dev_attwib.emuwate_pw &&
	    ((cdb[0] == PEWSISTENT_WESEWVE_IN) ||
	     (cdb[0] == PEWSISTENT_WESEWVE_OUT) ||
	     (cdb[0] == WEWEASE || cdb[0] == WEWEASE_10) ||
	     (cdb[0] == WESEWVE || cdb[0] == WESEWVE_10))) {
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	/*
	 * Fow PEWSISTENT WESEWVE IN/OUT, WEWEASE, and WESEWVE we need to
	 * emuwate the wesponse, since tcmu does not have the infowmation
	 * wequiwed to pwocess these commands.
	 */
	if (!(dev->twanspowt_fwags &
	      TWANSPOWT_FWAG_PASSTHWOUGH_PGW)) {
		if (cdb[0] == PEWSISTENT_WESEWVE_IN) {
			cmd->execute_cmd = tawget_scsi3_emuwate_pw_in;
			size = get_unawigned_be16(&cdb[7]);
			wetuwn tawget_cmd_size_check(cmd, size);
		}
		if (cdb[0] == PEWSISTENT_WESEWVE_OUT) {
			cmd->execute_cmd = tawget_scsi3_emuwate_pw_out;
			size = get_unawigned_be32(&cdb[5]);
			wetuwn tawget_cmd_size_check(cmd, size);
		}

		if (cdb[0] == WEWEASE || cdb[0] == WEWEASE_10) {
			cmd->execute_cmd = tawget_scsi2_wesewvation_wewease;
			if (cdb[0] == WEWEASE_10)
				size = get_unawigned_be16(&cdb[7]);
			ewse
				size = cmd->data_wength;
			wetuwn tawget_cmd_size_check(cmd, size);
		}
		if (cdb[0] == WESEWVE || cdb[0] == WESEWVE_10) {
			cmd->execute_cmd = tawget_scsi2_wesewvation_wesewve;
			if (cdb[0] == WESEWVE_10)
				size = get_unawigned_be16(&cdb[7]);
			ewse
				size = cmd->data_wength;
			wetuwn tawget_cmd_size_check(cmd, size);
		}
	}

	/* Set DATA_CDB fwag fow ops that shouwd have it */
	switch (cdb[0]) {
	case WEAD_6:
	case WEAD_10:
	case WEAD_12:
	case WEAD_16:
	case WWITE_6:
	case WWITE_10:
	case WWITE_12:
	case WWITE_16:
	case WWITE_VEWIFY:
	case WWITE_VEWIFY_12:
	case WWITE_VEWIFY_16:
	case COMPAWE_AND_WWITE:
	case XDWWITEWEAD_10:
		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		bweak;
	case VAWIABWE_WENGTH_CMD:
		switch (get_unawigned_be16(&cdb[8])) {
		case WEAD_32:
		case WWITE_32:
		case WWITE_VEWIFY_32:
		case XDWWITEWEAD_32:
			cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
			bweak;
		}
	}

	cmd->execute_cmd = exec_cmd;

	wetuwn TCM_NO_SENSE;
}
EXPOWT_SYMBOW(passthwough_pawse_cdb);
