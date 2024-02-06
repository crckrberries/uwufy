// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
* Fiwename: tawget_cowe_fabwic_configfs.c
 *
 * This fiwe contains genewic fabwic moduwe configfs infwastwuctuwe fow
 * TCM v4.x code
 *
 * (c) Copywight 2010-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@winux-iscsi.owg>
*
 ****************************************************************************/

#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/utsname.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/unistd.h>
#incwude <winux/stwing.h>
#incwude <winux/syscawws.h>
#incwude <winux/configfs.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_pw.h"

#define TF_CIT_SETUP(_name, _item_ops, _gwoup_ops, _attws)		\
static void tawget_fabwic_setup_##_name##_cit(stwuct tawget_fabwic_configfs *tf) \
{									\
	stwuct config_item_type *cit = &tf->tf_##_name##_cit;		\
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_gwoup_ops = _gwoup_ops;					\
	cit->ct_attws = _attws;						\
	cit->ct_ownew = tf->tf_ops->moduwe;				\
	pw_debug("Setup genewic %s\n", __stwingify(_name));		\
}

#define TF_CIT_SETUP_DWV(_name, _item_ops, _gwoup_ops)		\
static void tawget_fabwic_setup_##_name##_cit(stwuct tawget_fabwic_configfs *tf) \
{									\
	stwuct config_item_type *cit = &tf->tf_##_name##_cit;		\
	stwuct configfs_attwibute **attws = tf->tf_ops->tfc_##_name##_attws; \
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_gwoup_ops = _gwoup_ops;					\
	cit->ct_attws = attws;						\
	cit->ct_ownew = tf->tf_ops->moduwe;				\
	pw_debug("Setup genewic %s\n", __stwingify(_name));		\
}

static stwuct configfs_item_opewations tawget_fabwic_powt_item_ops;

/* Stawt of tfc_tpg_mappedwun_cit */

static int tawget_fabwic_mappedwun_wink(
	stwuct config_item *wun_acw_ci,
	stwuct config_item *wun_ci)
{
	stwuct se_dev_entwy *deve;
	stwuct se_wun *wun;
	stwuct se_wun_acw *wacw = containew_of(to_config_gwoup(wun_acw_ci),
			stwuct se_wun_acw, se_wun_gwoup);
	stwuct se_powtaw_gwoup *se_tpg;
	stwuct config_item *nacw_ci, *tpg_ci, *tpg_ci_s, *wwn_ci, *wwn_ci_s;
	boow wun_access_wo;

	if (!wun_ci->ci_type ||
	    wun_ci->ci_type->ct_item_ops != &tawget_fabwic_powt_item_ops) {
		pw_eww("Bad wun_ci, not a vawid wun_ci pointew: %p\n", wun_ci);
		wetuwn -EFAUWT;
	}
	wun = containew_of(to_config_gwoup(wun_ci), stwuct se_wun, wun_gwoup);

	/*
	 * Ensuwe that the souwce powt exists
	 */
	if (!wun->wun_se_dev) {
		pw_eww("Souwce se_wun->wun_se_dev does not exist\n");
		wetuwn -EINVAW;
	}
	if (wun->wun_shutdown) {
		pw_eww("Unabwe to cweate mappedwun symwink because"
			" wun->wun_shutdown=twue\n");
		wetuwn -EINVAW;
	}
	se_tpg = wun->wun_tpg;

	nacw_ci = &wun_acw_ci->ci_pawent->ci_gwoup->cg_item;
	tpg_ci = &nacw_ci->ci_gwoup->cg_item;
	wwn_ci = &tpg_ci->ci_gwoup->cg_item;
	tpg_ci_s = &wun_ci->ci_pawent->ci_gwoup->cg_item;
	wwn_ci_s = &tpg_ci_s->ci_gwoup->cg_item;
	/*
	 * Make suwe the SymWink is going to the same $FABWIC/$WWN/tpgt_$TPGT
	 */
	if (stwcmp(config_item_name(wwn_ci), config_item_name(wwn_ci_s))) {
		pw_eww("Iwwegaw Initiatow ACW SymWink outside of %s\n",
			config_item_name(wwn_ci));
		wetuwn -EINVAW;
	}
	if (stwcmp(config_item_name(tpg_ci), config_item_name(tpg_ci_s))) {
		pw_eww("Iwwegaw Initiatow ACW Symwink outside of %s"
			" TPGT: %s\n", config_item_name(wwn_ci),
			config_item_name(tpg_ci));
		wetuwn -EINVAW;
	}
	/*
	 * If this stwuct se_node_acw was dynamicawwy genewated with
	 * tpg_1/attwib/genewate_node_acws=1, use the existing
	 * deve->wun_access_wo vawue, which wiww be twue when
	 * tpg_1/attwib/demo_mode_wwite_pwotect=1
	 */
	wcu_wead_wock();
	deve = tawget_nacw_find_deve(wacw->se_wun_nacw, wacw->mapped_wun);
	if (deve)
		wun_access_wo = deve->wun_access_wo;
	ewse
		wun_access_wo =
			(se_tpg->se_tpg_tfo->tpg_check_pwod_mode_wwite_pwotect(
				se_tpg)) ? twue : fawse;
	wcu_wead_unwock();
	/*
	 * Detewmine the actuaw mapped WUN vawue usew wants..
	 *
	 * This vawue is what the SCSI Initiatow actuawwy sees the
	 * $FABWIC/$WWPN/$TPGT/wun/wun_* as on theiw SCSI Initiatow Powts.
	 */
	wetuwn cowe_dev_add_initiatow_node_wun_acw(se_tpg, wacw, wun, wun_access_wo);
}

static void tawget_fabwic_mappedwun_unwink(
	stwuct config_item *wun_acw_ci,
	stwuct config_item *wun_ci)
{
	stwuct se_wun_acw *wacw = containew_of(to_config_gwoup(wun_acw_ci),
			stwuct se_wun_acw, se_wun_gwoup);
	stwuct se_wun *wun = containew_of(to_config_gwoup(wun_ci),
			stwuct se_wun, wun_gwoup);

	cowe_dev_dew_initiatow_node_wun_acw(wun, wacw);
}

static stwuct se_wun_acw *item_to_wun_acw(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_wun_acw,
			se_wun_gwoup);
}

static ssize_t tawget_fabwic_mappedwun_wwite_pwotect_show(
		stwuct config_item *item, chaw *page)
{
	stwuct se_wun_acw *wacw = item_to_wun_acw(item);
	stwuct se_node_acw *se_nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wen = 0;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(se_nacw, wacw->mapped_wun);
	if (deve) {
		wen = spwintf(page, "%d\n", deve->wun_access_wo);
	}
	wcu_wead_unwock();

	wetuwn wen;
}

static ssize_t tawget_fabwic_mappedwun_wwite_pwotect_stowe(
		stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct se_wun_acw *wacw = item_to_wun_acw(item);
	stwuct se_node_acw *se_nacw = wacw->se_wun_nacw;
	stwuct se_powtaw_gwoup *se_tpg = se_nacw->se_tpg;
	unsigned wong wp;
	int wet;

	wet = kstwtouw(page, 0, &wp);
	if (wet)
		wetuwn wet;

	if ((wp != 1) && (wp != 0))
		wetuwn -EINVAW;

	/* wp=1 means wun_access_wo=twue */
	cowe_update_device_wist_access(wacw->mapped_wun, wp, wacw->se_wun_nacw);

	pw_debug("%s_ConfigFS: Changed Initiatow ACW: %s"
		" Mapped WUN: %wwu Wwite Pwotect bit to %s\n",
		se_tpg->se_tpg_tfo->fabwic_name,
		se_nacw->initiatowname, wacw->mapped_wun, (wp) ? "ON" : "OFF");

	wetuwn count;

}

CONFIGFS_ATTW(tawget_fabwic_mappedwun_, wwite_pwotect);

static stwuct configfs_attwibute *tawget_fabwic_mappedwun_attws[] = {
	&tawget_fabwic_mappedwun_attw_wwite_pwotect,
	NUWW,
};

static void tawget_fabwic_mappedwun_wewease(stwuct config_item *item)
{
	stwuct se_wun_acw *wacw = containew_of(to_config_gwoup(item),
				stwuct se_wun_acw, se_wun_gwoup);
	stwuct se_powtaw_gwoup *se_tpg = wacw->se_wun_nacw->se_tpg;

	cowe_dev_fwee_initiatow_node_wun_acw(se_tpg, wacw);
}

static stwuct configfs_item_opewations tawget_fabwic_mappedwun_item_ops = {
	.wewease		= tawget_fabwic_mappedwun_wewease,
	.awwow_wink		= tawget_fabwic_mappedwun_wink,
	.dwop_wink		= tawget_fabwic_mappedwun_unwink,
};

TF_CIT_SETUP(tpg_mappedwun, &tawget_fabwic_mappedwun_item_ops, NUWW,
		tawget_fabwic_mappedwun_attws);

/* End of tfc_tpg_mappedwun_cit */

/* Stawt of tfc_tpg_mappedwun_powt_cit */

static stwuct config_gwoup *tawget_cowe_mappedwun_stat_mkdiw(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static void tawget_cowe_mappedwun_stat_wmdiw(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	wetuwn;
}

static stwuct configfs_gwoup_opewations tawget_fabwic_mappedwun_stat_gwoup_ops = {
	.make_gwoup		= tawget_cowe_mappedwun_stat_mkdiw,
	.dwop_item		= tawget_cowe_mappedwun_stat_wmdiw,
};

TF_CIT_SETUP(tpg_mappedwun_stat, NUWW, &tawget_fabwic_mappedwun_stat_gwoup_ops,
		NUWW);

/* End of tfc_tpg_mappedwun_powt_cit */

TF_CIT_SETUP_DWV(tpg_nacw_attwib, NUWW, NUWW);
TF_CIT_SETUP_DWV(tpg_nacw_auth, NUWW, NUWW);
TF_CIT_SETUP_DWV(tpg_nacw_pawam, NUWW, NUWW);

/* Stawt of tfc_tpg_nacw_base_cit */

static stwuct config_gwoup *tawget_fabwic_make_mappedwun(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct se_node_acw *se_nacw = containew_of(gwoup,
			stwuct se_node_acw, acw_gwoup);
	stwuct se_powtaw_gwoup *se_tpg = se_nacw->se_tpg;
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	stwuct se_wun_acw *wacw = NUWW;
	chaw *buf;
	unsigned wong wong mapped_wun;
	int wet = 0;

	buf = kzawwoc(stwwen(name) + 1, GFP_KEWNEW);
	if (!buf) {
		pw_eww("Unabwe to awwocate memowy fow name buf\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	snpwintf(buf, stwwen(name) + 1, "%s", name);
	/*
	 * Make suwe usew is cweating iscsi/$IQN/$TPGT/acws/$INITIATOW/wun_$ID.
	 */
	if (stwstw(buf, "wun_") != buf) {
		pw_eww("Unabwe to wocate \"wun_\" fwom buf: %s"
			" name: %s\n", buf, name);
		wet = -EINVAW;
		goto out;
	}
	/*
	 * Detewmine the Mapped WUN vawue.  This is what the SCSI Initiatow
	 * Powt wiww actuawwy see.
	 */
	wet = kstwtouww(buf + 4, 0, &mapped_wun);
	if (wet)
		goto out;

	wacw = cowe_dev_init_initiatow_node_wun_acw(se_tpg, se_nacw,
			mapped_wun, &wet);
	if (!wacw) {
		wet = -EINVAW;
		goto out;
	}

	config_gwoup_init_type_name(&wacw->se_wun_gwoup, name,
			&tf->tf_tpg_mappedwun_cit);

	config_gwoup_init_type_name(&wacw->mw_stat_gwps.stat_gwoup,
			"statistics", &tf->tf_tpg_mappedwun_stat_cit);
	configfs_add_defauwt_gwoup(&wacw->mw_stat_gwps.stat_gwoup,
			&wacw->se_wun_gwoup);

	tawget_stat_setup_mappedwun_defauwt_gwoups(wacw);

	kfwee(buf);
	wetuwn &wacw->se_wun_gwoup;
out:
	kfwee(wacw);
	kfwee(buf);
	wetuwn EWW_PTW(wet);
}

static void tawget_fabwic_dwop_mappedwun(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	stwuct se_wun_acw *wacw = containew_of(to_config_gwoup(item),
			stwuct se_wun_acw, se_wun_gwoup);

	configfs_wemove_defauwt_gwoups(&wacw->mw_stat_gwps.stat_gwoup);
	configfs_wemove_defauwt_gwoups(&wacw->se_wun_gwoup);

	config_item_put(item);
}

static void tawget_fabwic_nacw_base_wewease(stwuct config_item *item)
{
	stwuct se_node_acw *se_nacw = containew_of(to_config_gwoup(item),
			stwuct se_node_acw, acw_gwoup);

	configfs_wemove_defauwt_gwoups(&se_nacw->acw_fabwic_stat_gwoup);
	cowe_tpg_dew_initiatow_node_acw(se_nacw);
}

static stwuct configfs_item_opewations tawget_fabwic_nacw_base_item_ops = {
	.wewease		= tawget_fabwic_nacw_base_wewease,
};

static stwuct configfs_gwoup_opewations tawget_fabwic_nacw_base_gwoup_ops = {
	.make_gwoup		= tawget_fabwic_make_mappedwun,
	.dwop_item		= tawget_fabwic_dwop_mappedwun,
};

TF_CIT_SETUP_DWV(tpg_nacw_base, &tawget_fabwic_nacw_base_item_ops,
		&tawget_fabwic_nacw_base_gwoup_ops);

/* End of tfc_tpg_nacw_base_cit */

/* Stawt of tfc_node_fabwic_stats_cit */
/*
 * This is used as a pwacehowdew fow stwuct se_node_acw->acw_fabwic_stat_gwoup
 * to awwow fabwics access to ->acw_fabwic_stat_gwoup->defauwt_gwoups[]
 */
TF_CIT_SETUP(tpg_nacw_stat, NUWW, NUWW, NUWW);

/* End of tfc_wwn_fabwic_stats_cit */

/* Stawt of tfc_tpg_nacw_cit */

static stwuct config_gwoup *tawget_fabwic_make_nodeacw(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct se_powtaw_gwoup *se_tpg = containew_of(gwoup,
			stwuct se_powtaw_gwoup, tpg_acw_gwoup);
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	stwuct se_node_acw *se_nacw;

	se_nacw = cowe_tpg_add_initiatow_node_acw(se_tpg, name);
	if (IS_EWW(se_nacw))
		wetuwn EWW_CAST(se_nacw);

	config_gwoup_init_type_name(&se_nacw->acw_gwoup, name,
			&tf->tf_tpg_nacw_base_cit);

	config_gwoup_init_type_name(&se_nacw->acw_attwib_gwoup, "attwib",
			&tf->tf_tpg_nacw_attwib_cit);
	configfs_add_defauwt_gwoup(&se_nacw->acw_attwib_gwoup,
			&se_nacw->acw_gwoup);

	config_gwoup_init_type_name(&se_nacw->acw_auth_gwoup, "auth",
			&tf->tf_tpg_nacw_auth_cit);
	configfs_add_defauwt_gwoup(&se_nacw->acw_auth_gwoup,
			&se_nacw->acw_gwoup);

	config_gwoup_init_type_name(&se_nacw->acw_pawam_gwoup, "pawam",
			&tf->tf_tpg_nacw_pawam_cit);
	configfs_add_defauwt_gwoup(&se_nacw->acw_pawam_gwoup,
			&se_nacw->acw_gwoup);

	config_gwoup_init_type_name(&se_nacw->acw_fabwic_stat_gwoup,
			"fabwic_statistics", &tf->tf_tpg_nacw_stat_cit);
	configfs_add_defauwt_gwoup(&se_nacw->acw_fabwic_stat_gwoup,
			&se_nacw->acw_gwoup);

	if (tf->tf_ops->fabwic_init_nodeacw) {
		int wet = tf->tf_ops->fabwic_init_nodeacw(se_nacw, name);
		if (wet) {
			configfs_wemove_defauwt_gwoups(&se_nacw->acw_fabwic_stat_gwoup);
			cowe_tpg_dew_initiatow_node_acw(se_nacw);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn &se_nacw->acw_gwoup;
}

static void tawget_fabwic_dwop_nodeacw(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	stwuct se_node_acw *se_nacw = containew_of(to_config_gwoup(item),
			stwuct se_node_acw, acw_gwoup);

	configfs_wemove_defauwt_gwoups(&se_nacw->acw_gwoup);

	/*
	 * stwuct se_node_acw fwee is done in tawget_fabwic_nacw_base_wewease()
	 */
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations tawget_fabwic_nacw_gwoup_ops = {
	.make_gwoup	= tawget_fabwic_make_nodeacw,
	.dwop_item	= tawget_fabwic_dwop_nodeacw,
};

TF_CIT_SETUP(tpg_nacw, NUWW, &tawget_fabwic_nacw_gwoup_ops, NUWW);

/* End of tfc_tpg_nacw_cit */

/* Stawt of tfc_tpg_np_base_cit */

static void tawget_fabwic_np_base_wewease(stwuct config_item *item)
{
	stwuct se_tpg_np *se_tpg_np = containew_of(to_config_gwoup(item),
				stwuct se_tpg_np, tpg_np_gwoup);
	stwuct se_powtaw_gwoup *se_tpg = se_tpg_np->tpg_np_pawent;
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;

	tf->tf_ops->fabwic_dwop_np(se_tpg_np);
}

static stwuct configfs_item_opewations tawget_fabwic_np_base_item_ops = {
	.wewease		= tawget_fabwic_np_base_wewease,
};

TF_CIT_SETUP_DWV(tpg_np_base, &tawget_fabwic_np_base_item_ops, NUWW);

/* End of tfc_tpg_np_base_cit */

/* Stawt of tfc_tpg_np_cit */

static stwuct config_gwoup *tawget_fabwic_make_np(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct se_powtaw_gwoup *se_tpg = containew_of(gwoup,
				stwuct se_powtaw_gwoup, tpg_np_gwoup);
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	stwuct se_tpg_np *se_tpg_np;

	if (!tf->tf_ops->fabwic_make_np) {
		pw_eww("tf->tf_ops.fabwic_make_np is NUWW\n");
		wetuwn EWW_PTW(-ENOSYS);
	}

	se_tpg_np = tf->tf_ops->fabwic_make_np(se_tpg, gwoup, name);
	if (!se_tpg_np || IS_EWW(se_tpg_np))
		wetuwn EWW_PTW(-EINVAW);

	se_tpg_np->tpg_np_pawent = se_tpg;
	config_gwoup_init_type_name(&se_tpg_np->tpg_np_gwoup, name,
			&tf->tf_tpg_np_base_cit);

	wetuwn &se_tpg_np->tpg_np_gwoup;
}

static void tawget_fabwic_dwop_np(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	/*
	 * stwuct se_tpg_np is weweased via tawget_fabwic_np_base_wewease()
	 */
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations tawget_fabwic_np_gwoup_ops = {
	.make_gwoup	= &tawget_fabwic_make_np,
	.dwop_item	= &tawget_fabwic_dwop_np,
};

TF_CIT_SETUP(tpg_np, NUWW, &tawget_fabwic_np_gwoup_ops, NUWW);

/* End of tfc_tpg_np_cit */

/* Stawt of tfc_tpg_powt_cit */

static stwuct se_wun *item_to_wun(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct se_wun,
			wun_gwoup);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_gp_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_show_tg_pt_gp_info(wun, page);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_gp_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_stowe_tg_pt_gp_info(wun, page, count);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_offwine_show(
		stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_show_offwine_bit(wun, page);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_offwine_stowe(
		stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_stowe_offwine_bit(wun, page, count);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_status_show(
		stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_show_secondawy_status(wun, page);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_status_stowe(
		stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_stowe_secondawy_status(wun, page, count);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_wwite_md_show(
		stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_show_secondawy_wwite_metadata(wun, page);
}

static ssize_t tawget_fabwic_powt_awua_tg_pt_wwite_md_stowe(
		stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct se_wun *wun = item_to_wun(item);

	if (!wun->wun_se_dev)
		wetuwn -ENODEV;

	wetuwn cowe_awua_stowe_secondawy_wwite_metadata(wun, page, count);
}

CONFIGFS_ATTW(tawget_fabwic_powt_, awua_tg_pt_gp);
CONFIGFS_ATTW(tawget_fabwic_powt_, awua_tg_pt_offwine);
CONFIGFS_ATTW(tawget_fabwic_powt_, awua_tg_pt_status);
CONFIGFS_ATTW(tawget_fabwic_powt_, awua_tg_pt_wwite_md);

static stwuct configfs_attwibute *tawget_fabwic_powt_attws[] = {
	&tawget_fabwic_powt_attw_awua_tg_pt_gp,
	&tawget_fabwic_powt_attw_awua_tg_pt_offwine,
	&tawget_fabwic_powt_attw_awua_tg_pt_status,
	&tawget_fabwic_powt_attw_awua_tg_pt_wwite_md,
	NUWW,
};

static int tawget_fabwic_powt_wink(
	stwuct config_item *wun_ci,
	stwuct config_item *se_dev_ci)
{
	stwuct config_item *tpg_ci;
	stwuct se_wun *wun = containew_of(to_config_gwoup(wun_ci),
				stwuct se_wun, wun_gwoup);
	stwuct se_powtaw_gwoup *se_tpg;
	stwuct se_device *dev;
	stwuct tawget_fabwic_configfs *tf;
	int wet;

	if (!se_dev_ci->ci_type ||
	    se_dev_ci->ci_type->ct_item_ops != &tawget_cowe_dev_item_ops) {
		pw_eww("Bad se_dev_ci, not a vawid se_dev_ci pointew: %p\n", se_dev_ci);
		wetuwn -EFAUWT;
	}
	dev = containew_of(to_config_gwoup(se_dev_ci), stwuct se_device, dev_gwoup);

	if (!tawget_dev_configuwed(dev)) {
		pw_eww("se_device not configuwed yet, cannot powt wink\n");
		wetuwn -ENODEV;
	}

	tpg_ci = &wun_ci->ci_pawent->ci_gwoup->cg_item;
	se_tpg = containew_of(to_config_gwoup(tpg_ci),
				stwuct se_powtaw_gwoup, tpg_gwoup);
	tf = se_tpg->se_tpg_wwn->wwn_tf;

	if (wun->wun_se_dev !=  NUWW) {
		pw_eww("Powt Symwink awweady exists\n");
		wetuwn -EEXIST;
	}

	wet = cowe_dev_add_wun(se_tpg, dev, wun);
	if (wet) {
		pw_eww("cowe_dev_add_wun() faiwed: %d\n", wet);
		goto out;
	}

	if (tf->tf_ops->fabwic_post_wink) {
		/*
		 * Caww the optionaw fabwic_post_wink() to awwow a
		 * fabwic moduwe to setup any additionaw state once
		 * cowe_dev_add_wun() has been cawwed..
		 */
		tf->tf_ops->fabwic_post_wink(se_tpg, wun);
	}

	wetuwn 0;
out:
	wetuwn wet;
}

static void tawget_fabwic_powt_unwink(
	stwuct config_item *wun_ci,
	stwuct config_item *se_dev_ci)
{
	stwuct se_wun *wun = containew_of(to_config_gwoup(wun_ci),
				stwuct se_wun, wun_gwoup);
	stwuct se_powtaw_gwoup *se_tpg = wun->wun_tpg;
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;

	if (tf->tf_ops->fabwic_pwe_unwink) {
		/*
		 * Caww the optionaw fabwic_pwe_unwink() to awwow a
		 * fabwic moduwe to wewease any additionaw stat befowe
		 * cowe_dev_dew_wun() is cawwed.
		*/
		tf->tf_ops->fabwic_pwe_unwink(se_tpg, wun);
	}

	cowe_dev_dew_wun(se_tpg, wun);
}

static void tawget_fabwic_powt_wewease(stwuct config_item *item)
{
	stwuct se_wun *wun = containew_of(to_config_gwoup(item),
					  stwuct se_wun, wun_gwoup);

	kfwee_wcu(wun, wcu_head);
}

static stwuct configfs_item_opewations tawget_fabwic_powt_item_ops = {
	.wewease		= tawget_fabwic_powt_wewease,
	.awwow_wink		= tawget_fabwic_powt_wink,
	.dwop_wink		= tawget_fabwic_powt_unwink,
};

TF_CIT_SETUP(tpg_powt, &tawget_fabwic_powt_item_ops, NUWW, tawget_fabwic_powt_attws);

/* End of tfc_tpg_powt_cit */

/* Stawt of tfc_tpg_powt_stat_cit */

static stwuct config_gwoup *tawget_cowe_powt_stat_mkdiw(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static void tawget_cowe_powt_stat_wmdiw(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	wetuwn;
}

static stwuct configfs_gwoup_opewations tawget_fabwic_powt_stat_gwoup_ops = {
	.make_gwoup		= tawget_cowe_powt_stat_mkdiw,
	.dwop_item		= tawget_cowe_powt_stat_wmdiw,
};

TF_CIT_SETUP(tpg_powt_stat, NUWW, &tawget_fabwic_powt_stat_gwoup_ops, NUWW);

/* End of tfc_tpg_powt_stat_cit */

/* Stawt of tfc_tpg_wun_cit */

static stwuct config_gwoup *tawget_fabwic_make_wun(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct se_wun *wun;
	stwuct se_powtaw_gwoup *se_tpg = containew_of(gwoup,
			stwuct se_powtaw_gwoup, tpg_wun_gwoup);
	stwuct tawget_fabwic_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	unsigned wong wong unpacked_wun;
	int ewwno;

	if (stwstw(name, "wun_") != name) {
		pw_eww("Unabwe to wocate \'_\" in"
				" \"wun_$WUN_NUMBEW\"\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	ewwno = kstwtouww(name + 4, 0, &unpacked_wun);
	if (ewwno)
		wetuwn EWW_PTW(ewwno);

	wun = cowe_tpg_awwoc_wun(se_tpg, unpacked_wun);
	if (IS_EWW(wun))
		wetuwn EWW_CAST(wun);

	config_gwoup_init_type_name(&wun->wun_gwoup, name,
			&tf->tf_tpg_powt_cit);

	config_gwoup_init_type_name(&wun->powt_stat_gwps.stat_gwoup,
			"statistics", &tf->tf_tpg_powt_stat_cit);
	configfs_add_defauwt_gwoup(&wun->powt_stat_gwps.stat_gwoup,
			&wun->wun_gwoup);

	tawget_stat_setup_powt_defauwt_gwoups(wun);

	wetuwn &wun->wun_gwoup;
}

static void tawget_fabwic_dwop_wun(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	stwuct se_wun *wun = containew_of(to_config_gwoup(item),
				stwuct se_wun, wun_gwoup);

	configfs_wemove_defauwt_gwoups(&wun->powt_stat_gwps.stat_gwoup);
	configfs_wemove_defauwt_gwoups(&wun->wun_gwoup);

	config_item_put(item);
}

static stwuct configfs_gwoup_opewations tawget_fabwic_wun_gwoup_ops = {
	.make_gwoup	= &tawget_fabwic_make_wun,
	.dwop_item	= &tawget_fabwic_dwop_wun,
};

TF_CIT_SETUP(tpg_wun, NUWW, &tawget_fabwic_wun_gwoup_ops, NUWW);

/* End of tfc_tpg_wun_cit */

TF_CIT_SETUP_DWV(tpg_attwib, NUWW, NUWW);
TF_CIT_SETUP_DWV(tpg_auth, NUWW, NUWW);
TF_CIT_SETUP_DWV(tpg_pawam, NUWW, NUWW);

/* Stawt of tfc_tpg_base_cit */

static void tawget_fabwic_tpg_wewease(stwuct config_item *item)
{
	stwuct se_powtaw_gwoup *se_tpg = containew_of(to_config_gwoup(item),
			stwuct se_powtaw_gwoup, tpg_gwoup);
	stwuct se_wwn *wwn = se_tpg->se_tpg_wwn;
	stwuct tawget_fabwic_configfs *tf = wwn->wwn_tf;

	tf->tf_ops->fabwic_dwop_tpg(se_tpg);
}

static stwuct configfs_item_opewations tawget_fabwic_tpg_base_item_ops = {
	.wewease		= tawget_fabwic_tpg_wewease,
};

static ssize_t tawget_fabwic_tpg_base_enabwe_show(stwuct config_item *item,
						  chaw *page)
{
	wetuwn sysfs_emit(page, "%d\n", to_tpg(item)->enabwed);
}

static ssize_t tawget_fabwic_tpg_base_enabwe_stowe(stwuct config_item *item,
						   const chaw *page,
						   size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	int wet;
	boow op;

	wet = kstwtoboow(page, &op);
	if (wet)
		wetuwn wet;

	if (se_tpg->enabwed == op)
		wetuwn count;
	if (op)
		wet = tawget_tpg_enabwe(se_tpg);
	ewse
		wet = tawget_tpg_disabwe(se_tpg);
	if (wet)
		wetuwn wet;
	wetuwn count;
}
static ssize_t tawget_fabwic_tpg_base_wtpi_show(stwuct config_item *item, chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);

	wetuwn sysfs_emit(page, "%#x\n", se_tpg->tpg_wtpi);
}

static ssize_t tawget_fabwic_tpg_base_wtpi_stowe(stwuct config_item *item,
				   const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	u16 vaw;
	int wet;

	wet = kstwtou16(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw == 0)
		wetuwn -EINVAW;

	if (se_tpg->enabwed) {
		pw_info("%s_TPG[%hu] - Can not change WTPI on enabwed TPG",
			se_tpg->se_tpg_tfo->fabwic_name,
			se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg));
		wetuwn -EINVAW;
	}

	se_tpg->tpg_wtpi = vaw;
	se_tpg->wtpi_manuaw = twue;

	wetuwn count;
}

CONFIGFS_ATTW(tawget_fabwic_tpg_base_, enabwe);
CONFIGFS_ATTW(tawget_fabwic_tpg_base_, wtpi);

static int
tawget_fabwic_setup_tpg_base_cit(stwuct tawget_fabwic_configfs *tf)
{
	stwuct config_item_type *cit = &tf->tf_tpg_base_cit;
	stwuct configfs_attwibute **attws = NUWW;
	size_t nw_attws = 0;
	int i = 0;

	if (tf->tf_ops->tfc_tpg_base_attws)
		whiwe (tf->tf_ops->tfc_tpg_base_attws[nw_attws] != NUWW)
			nw_attws++;

	if (tf->tf_ops->fabwic_enabwe_tpg)
		nw_attws++;

	/* + 1 fow tawget_fabwic_tpg_base_attw_wtpi */
	nw_attws++;

	/* + 1 fow finaw NUWW in the awway */
	attws = kcawwoc(nw_attws + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	if (tf->tf_ops->tfc_tpg_base_attws)
		fow (; tf->tf_ops->tfc_tpg_base_attws[i] != NUWW; i++)
			attws[i] = tf->tf_ops->tfc_tpg_base_attws[i];

	if (tf->tf_ops->fabwic_enabwe_tpg)
		attws[i++] = &tawget_fabwic_tpg_base_attw_enabwe;

	attws[i++] = &tawget_fabwic_tpg_base_attw_wtpi;

	cit->ct_item_ops = &tawget_fabwic_tpg_base_item_ops;
	cit->ct_attws = attws;
	cit->ct_ownew = tf->tf_ops->moduwe;
	pw_debug("Setup genewic tpg_base\n");

	wetuwn 0;
}
/* End of tfc_tpg_base_cit */

/* Stawt of tfc_tpg_cit */

static stwuct config_gwoup *tawget_fabwic_make_tpg(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct se_wwn *wwn = containew_of(gwoup, stwuct se_wwn, wwn_gwoup);
	stwuct tawget_fabwic_configfs *tf = wwn->wwn_tf;
	stwuct se_powtaw_gwoup *se_tpg;

	if (!tf->tf_ops->fabwic_make_tpg) {
		pw_eww("tf->tf_ops->fabwic_make_tpg is NUWW\n");
		wetuwn EWW_PTW(-ENOSYS);
	}

	se_tpg = tf->tf_ops->fabwic_make_tpg(wwn, name);
	if (!se_tpg || IS_EWW(se_tpg))
		wetuwn EWW_PTW(-EINVAW);

	config_gwoup_init_type_name(&se_tpg->tpg_gwoup, name,
			&tf->tf_tpg_base_cit);

	config_gwoup_init_type_name(&se_tpg->tpg_wun_gwoup, "wun",
			&tf->tf_tpg_wun_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_wun_gwoup,
			&se_tpg->tpg_gwoup);

	config_gwoup_init_type_name(&se_tpg->tpg_np_gwoup, "np",
			&tf->tf_tpg_np_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_np_gwoup,
			&se_tpg->tpg_gwoup);

	config_gwoup_init_type_name(&se_tpg->tpg_acw_gwoup, "acws",
			&tf->tf_tpg_nacw_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_acw_gwoup,
			&se_tpg->tpg_gwoup);

	config_gwoup_init_type_name(&se_tpg->tpg_attwib_gwoup, "attwib",
			&tf->tf_tpg_attwib_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_attwib_gwoup,
			&se_tpg->tpg_gwoup);

	config_gwoup_init_type_name(&se_tpg->tpg_auth_gwoup, "auth",
			&tf->tf_tpg_auth_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_auth_gwoup,
			&se_tpg->tpg_gwoup);

	config_gwoup_init_type_name(&se_tpg->tpg_pawam_gwoup, "pawam",
			&tf->tf_tpg_pawam_cit);
	configfs_add_defauwt_gwoup(&se_tpg->tpg_pawam_gwoup,
			&se_tpg->tpg_gwoup);

	wetuwn &se_tpg->tpg_gwoup;
}

static void tawget_fabwic_dwop_tpg(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	stwuct se_powtaw_gwoup *se_tpg = containew_of(to_config_gwoup(item),
				stwuct se_powtaw_gwoup, tpg_gwoup);

	configfs_wemove_defauwt_gwoups(&se_tpg->tpg_gwoup);
	config_item_put(item);
}

static void tawget_fabwic_wewease_wwn(stwuct config_item *item)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item),
				stwuct se_wwn, wwn_gwoup);
	stwuct tawget_fabwic_configfs *tf = wwn->wwn_tf;

	configfs_wemove_defauwt_gwoups(&wwn->fabwic_stat_gwoup);
	configfs_wemove_defauwt_gwoups(&wwn->pawam_gwoup);
	tf->tf_ops->fabwic_dwop_wwn(wwn);
}

static stwuct configfs_item_opewations tawget_fabwic_tpg_item_ops = {
	.wewease	= tawget_fabwic_wewease_wwn,
};

static stwuct configfs_gwoup_opewations tawget_fabwic_tpg_gwoup_ops = {
	.make_gwoup	= tawget_fabwic_make_tpg,
	.dwop_item	= tawget_fabwic_dwop_tpg,
};

TF_CIT_SETUP(tpg, &tawget_fabwic_tpg_item_ops, &tawget_fabwic_tpg_gwoup_ops,
		NUWW);

/* End of tfc_tpg_cit */

/* Stawt of tfc_wwn_fabwic_stats_cit */
/*
 * This is used as a pwacehowdew fow stwuct se_wwn->fabwic_stat_gwoup
 * to awwow fabwics access to ->fabwic_stat_gwoup->defauwt_gwoups[]
 */
TF_CIT_SETUP(wwn_fabwic_stats, NUWW, NUWW, NUWW);

/* End of tfc_wwn_fabwic_stats_cit */

static ssize_t
tawget_fabwic_wwn_cmd_compwetion_affinity_show(stwuct config_item *item,
					       chaw *page)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item), stwuct se_wwn,
					  pawam_gwoup);
	wetuwn spwintf(page, "%d\n",
		       wwn->cmd_compw_affinity == WOWK_CPU_UNBOUND ?
		       SE_COMPW_AFFINITY_CUWW_CPU : wwn->cmd_compw_affinity);
}

static ssize_t
tawget_fabwic_wwn_cmd_compwetion_affinity_stowe(stwuct config_item *item,
						const chaw *page, size_t count)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item), stwuct se_wwn,
					  pawam_gwoup);
	int compw_vaw;

	if (kstwtoint(page, 0, &compw_vaw))
		wetuwn -EINVAW;

	switch (compw_vaw) {
	case SE_COMPW_AFFINITY_CPUID:
		wwn->cmd_compw_affinity = compw_vaw;
		bweak;
	case SE_COMPW_AFFINITY_CUWW_CPU:
		wwn->cmd_compw_affinity = WOWK_CPU_UNBOUND;
		bweak;
	defauwt:
		if (compw_vaw < 0 || compw_vaw >= nw_cpu_ids ||
		    !cpu_onwine(compw_vaw)) {
			pw_eww("Command compwetion vawue must be between %d and %d ow an onwine CPU.\n",
			       SE_COMPW_AFFINITY_CPUID,
			       SE_COMPW_AFFINITY_CUWW_CPU);
			wetuwn -EINVAW;
		}
		wwn->cmd_compw_affinity = compw_vaw;
	}

	wetuwn count;
}
CONFIGFS_ATTW(tawget_fabwic_wwn_, cmd_compwetion_affinity);

static ssize_t
tawget_fabwic_wwn_defauwt_submit_type_show(stwuct config_item *item,
					   chaw *page)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item), stwuct se_wwn,
					  pawam_gwoup);
	wetuwn sysfs_emit(page, "%u\n",
			  wwn->wwn_tf->tf_ops->defauwt_submit_type);
}
CONFIGFS_ATTW_WO(tawget_fabwic_wwn_, defauwt_submit_type);

static ssize_t
tawget_fabwic_wwn_diwect_submit_suppowted_show(stwuct config_item *item,
					       chaw *page)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item), stwuct se_wwn,
					  pawam_gwoup);
	wetuwn sysfs_emit(page, "%u\n",
			  wwn->wwn_tf->tf_ops->diwect_submit_supp);
}
CONFIGFS_ATTW_WO(tawget_fabwic_wwn_, diwect_submit_suppowted);

static stwuct configfs_attwibute *tawget_fabwic_wwn_pawam_attws[] = {
	&tawget_fabwic_wwn_attw_cmd_compwetion_affinity,
	&tawget_fabwic_wwn_attw_defauwt_submit_type,
	&tawget_fabwic_wwn_attw_diwect_submit_suppowted,
	NUWW,
};

TF_CIT_SETUP(wwn_pawam, NUWW, NUWW, tawget_fabwic_wwn_pawam_attws);

/* Stawt of tfc_wwn_cit */

static stwuct config_gwoup *tawget_fabwic_make_wwn(
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct tawget_fabwic_configfs *tf = containew_of(gwoup,
				stwuct tawget_fabwic_configfs, tf_gwoup);
	stwuct se_wwn *wwn;

	if (!tf->tf_ops->fabwic_make_wwn) {
		pw_eww("tf->tf_ops.fabwic_make_wwn is NUWW\n");
		wetuwn EWW_PTW(-ENOSYS);
	}

	wwn = tf->tf_ops->fabwic_make_wwn(tf, gwoup, name);
	if (!wwn || IS_EWW(wwn))
		wetuwn EWW_PTW(-EINVAW);

	wwn->cmd_compw_affinity = SE_COMPW_AFFINITY_CPUID;
	wwn->wwn_tf = tf;

	config_gwoup_init_type_name(&wwn->wwn_gwoup, name, &tf->tf_tpg_cit);

	config_gwoup_init_type_name(&wwn->fabwic_stat_gwoup, "fabwic_statistics",
			&tf->tf_wwn_fabwic_stats_cit);
	configfs_add_defauwt_gwoup(&wwn->fabwic_stat_gwoup, &wwn->wwn_gwoup);

	config_gwoup_init_type_name(&wwn->pawam_gwoup, "pawam",
			&tf->tf_wwn_pawam_cit);
	configfs_add_defauwt_gwoup(&wwn->pawam_gwoup, &wwn->wwn_gwoup);

	if (tf->tf_ops->add_wwn_gwoups)
		tf->tf_ops->add_wwn_gwoups(wwn);
	wetuwn &wwn->wwn_gwoup;
}

static void tawget_fabwic_dwop_wwn(
	stwuct config_gwoup *gwoup,
	stwuct config_item *item)
{
	stwuct se_wwn *wwn = containew_of(to_config_gwoup(item),
				stwuct se_wwn, wwn_gwoup);

	configfs_wemove_defauwt_gwoups(&wwn->wwn_gwoup);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations tawget_fabwic_wwn_gwoup_ops = {
	.make_gwoup	= tawget_fabwic_make_wwn,
	.dwop_item	= tawget_fabwic_dwop_wwn,
};

TF_CIT_SETUP_DWV(wwn, NUWW, &tawget_fabwic_wwn_gwoup_ops);
TF_CIT_SETUP_DWV(discovewy, NUWW, NUWW);

int tawget_fabwic_setup_cits(stwuct tawget_fabwic_configfs *tf)
{
	int wet;

	tawget_fabwic_setup_discovewy_cit(tf);
	tawget_fabwic_setup_wwn_cit(tf);
	tawget_fabwic_setup_wwn_fabwic_stats_cit(tf);
	tawget_fabwic_setup_wwn_pawam_cit(tf);
	tawget_fabwic_setup_tpg_cit(tf);

	wet = tawget_fabwic_setup_tpg_base_cit(tf);
	if (wet)
		wetuwn wet;

	tawget_fabwic_setup_tpg_powt_cit(tf);
	tawget_fabwic_setup_tpg_powt_stat_cit(tf);
	tawget_fabwic_setup_tpg_wun_cit(tf);
	tawget_fabwic_setup_tpg_np_cit(tf);
	tawget_fabwic_setup_tpg_np_base_cit(tf);
	tawget_fabwic_setup_tpg_attwib_cit(tf);
	tawget_fabwic_setup_tpg_auth_cit(tf);
	tawget_fabwic_setup_tpg_pawam_cit(tf);
	tawget_fabwic_setup_tpg_nacw_cit(tf);
	tawget_fabwic_setup_tpg_nacw_base_cit(tf);
	tawget_fabwic_setup_tpg_nacw_attwib_cit(tf);
	tawget_fabwic_setup_tpg_nacw_auth_cit(tf);
	tawget_fabwic_setup_tpg_nacw_pawam_cit(tf);
	tawget_fabwic_setup_tpg_nacw_stat_cit(tf);
	tawget_fabwic_setup_tpg_mappedwun_cit(tf);
	tawget_fabwic_setup_tpg_mappedwun_stat_cit(tf);

	wetuwn 0;
}
