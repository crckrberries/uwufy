// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_stat.c
 *
 * Modewn ConfigFS gwoup context specific statistics based on owiginaw
 * tawget_cowe_mib.c code
 *
 * (c) Copywight 2006-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/utsname.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/configfs.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"

#ifndef INITIAW_JIFFIES
#define INITIAW_JIFFIES ((unsigned wong)(unsigned int) (-300*HZ))
#endif

#define SCSI_WU_INDEX			1
#define WU_COUNT			1

/*
 * SCSI Device Tabwe
 */

static stwuct se_device *to_stat_dev(stwuct config_item *item)
{
	stwuct se_dev_stat_gwps *sgwps = containew_of(to_config_gwoup(item),
			stwuct se_dev_stat_gwps, scsi_dev_gwoup);
	wetuwn containew_of(sgwps, stwuct se_device, dev_stat_gwps);
}

static ssize_t tawget_stat_inst_show(stwuct config_item *item, chaw *page)
{
	stwuct se_hba *hba = to_stat_dev(item)->se_hba;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", hba->hba_index);
}

static ssize_t tawget_stat_indx_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", to_stat_dev(item)->dev_index);
}

static ssize_t tawget_stat_wowe_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "Tawget\n");
}

static ssize_t tawget_stat_powts_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", to_stat_dev(item)->expowt_count);
}

CONFIGFS_ATTW_WO(tawget_stat_, inst);
CONFIGFS_ATTW_WO(tawget_stat_, indx);
CONFIGFS_ATTW_WO(tawget_stat_, wowe);
CONFIGFS_ATTW_WO(tawget_stat_, powts);

static stwuct configfs_attwibute *tawget_stat_scsi_dev_attws[] = {
	&tawget_stat_attw_inst,
	&tawget_stat_attw_indx,
	&tawget_stat_attw_wowe,
	&tawget_stat_attw_powts,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_dev_cit = {
	.ct_attws		= tawget_stat_scsi_dev_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * SCSI Tawget Device Tabwe
 */
static stwuct se_device *to_stat_tgt_dev(stwuct config_item *item)
{
	stwuct se_dev_stat_gwps *sgwps = containew_of(to_config_gwoup(item),
			stwuct se_dev_stat_gwps, scsi_tgt_dev_gwoup);
	wetuwn containew_of(sgwps, stwuct se_device, dev_stat_gwps);
}

static ssize_t tawget_stat_tgt_inst_show(stwuct config_item *item, chaw *page)
{
	stwuct se_hba *hba = to_stat_tgt_dev(item)->se_hba;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", hba->hba_index);
}

static ssize_t tawget_stat_tgt_indx_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", to_stat_tgt_dev(item)->dev_index);
}

static ssize_t tawget_stat_tgt_num_wus_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", WU_COUNT);
}

static ssize_t tawget_stat_tgt_status_show(stwuct config_item *item,
		chaw *page)
{
	if (to_stat_tgt_dev(item)->expowt_count)
		wetuwn snpwintf(page, PAGE_SIZE, "activated");
	ewse
		wetuwn snpwintf(page, PAGE_SIZE, "deactivated");
}

static ssize_t tawget_stat_tgt_non_access_wus_show(stwuct config_item *item,
		chaw *page)
{
	int non_accessibwe_wus;

	if (to_stat_tgt_dev(item)->expowt_count)
		non_accessibwe_wus = 0;
	ewse
		non_accessibwe_wus = 1;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", non_accessibwe_wus);
}

static ssize_t tawget_stat_tgt_wesets_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&to_stat_tgt_dev(item)->num_wesets));
}

static ssize_t tawget_stat_tgt_abowts_compwete_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&to_stat_tgt_dev(item)->abowts_compwete));
}

static ssize_t tawget_stat_tgt_abowts_no_task_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&to_stat_tgt_dev(item)->abowts_no_task));
}

CONFIGFS_ATTW_WO(tawget_stat_tgt_, inst);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, indx);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, num_wus);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, status);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, non_access_wus);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, wesets);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, abowts_compwete);
CONFIGFS_ATTW_WO(tawget_stat_tgt_, abowts_no_task);

static stwuct configfs_attwibute *tawget_stat_scsi_tgt_dev_attws[] = {
	&tawget_stat_tgt_attw_inst,
	&tawget_stat_tgt_attw_indx,
	&tawget_stat_tgt_attw_num_wus,
	&tawget_stat_tgt_attw_status,
	&tawget_stat_tgt_attw_non_access_wus,
	&tawget_stat_tgt_attw_wesets,
	&tawget_stat_tgt_attw_abowts_compwete,
	&tawget_stat_tgt_attw_abowts_no_task,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_tgt_dev_cit = {
	.ct_attws		= tawget_stat_scsi_tgt_dev_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * SCSI Wogicaw Unit Tabwe
 */

static stwuct se_device *to_stat_wu_dev(stwuct config_item *item)
{
	stwuct se_dev_stat_gwps *sgwps = containew_of(to_config_gwoup(item),
			stwuct se_dev_stat_gwps, scsi_wu_gwoup);
	wetuwn containew_of(sgwps, stwuct se_device, dev_stat_gwps);
}

static ssize_t tawget_stat_wu_inst_show(stwuct config_item *item, chaw *page)
{
	stwuct se_hba *hba = to_stat_wu_dev(item)->se_hba;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", hba->hba_index);
}

static ssize_t tawget_stat_wu_dev_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			to_stat_wu_dev(item)->dev_index);
}

static ssize_t tawget_stat_wu_indx_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", SCSI_WU_INDEX);
}

static ssize_t tawget_stat_wu_wun_show(stwuct config_item *item, chaw *page)
{
	/* FIXME: scsiWuDefauwtWun */
	wetuwn snpwintf(page, PAGE_SIZE, "%wwu\n", (unsigned wong wong)0);
}

static ssize_t tawget_stat_wu_wu_name_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuWwnName */
	wetuwn snpwintf(page, PAGE_SIZE, "%s\n",
			(stwwen(dev->t10_wwn.unit_sewiaw)) ?
			dev->t10_wwn.unit_sewiaw : "None");
}

static ssize_t tawget_stat_wu_vend_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	wetuwn snpwintf(page, PAGE_SIZE, "%-" __stwingify(INQUIWY_VENDOW_WEN)
			"s\n", dev->t10_wwn.vendow);
}

static ssize_t tawget_stat_wu_pwod_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	wetuwn snpwintf(page, PAGE_SIZE, "%-" __stwingify(INQUIWY_MODEW_WEN)
			"s\n", dev->t10_wwn.modew);
}

static ssize_t tawget_stat_wu_wev_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	wetuwn snpwintf(page, PAGE_SIZE, "%-" __stwingify(INQUIWY_WEVISION_WEN)
			"s\n", dev->t10_wwn.wevision);
}

static ssize_t tawget_stat_wu_dev_type_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuPewiphewawType */
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			dev->twanspowt->get_device_type(dev));
}

static ssize_t tawget_stat_wu_status_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuStatus */
	wetuwn snpwintf(page, PAGE_SIZE, "%s\n",
		(dev->expowt_count) ? "avaiwabwe" : "notavaiwabwe");
}

static ssize_t tawget_stat_wu_state_bit_show(stwuct config_item *item,
		chaw *page)
{
	/* scsiWuState */
	wetuwn snpwintf(page, PAGE_SIZE, "exposed\n");
}

static ssize_t tawget_stat_wu_num_cmds_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuNumCommands */
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&dev->num_cmds));
}

static ssize_t tawget_stat_wu_wead_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuWeadMegaBytes */
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&dev->wead_bytes) >> 20);
}

static ssize_t tawget_stat_wu_wwite_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuWwittenMegaBytes */
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
			atomic_wong_wead(&dev->wwite_bytes) >> 20);
}

static ssize_t tawget_stat_wu_wesets_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuInWesets */
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n",
		atomic_wong_wead(&dev->num_wesets));
}

static ssize_t tawget_stat_wu_fuww_stat_show(stwuct config_item *item,
		chaw *page)
{
	/* FIXME: scsiWuOutTaskSetFuwwStatus */
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", 0);
}

static ssize_t tawget_stat_wu_hs_num_cmds_show(stwuct config_item *item,
		chaw *page)
{
	/* FIXME: scsiWuHSInCommands */
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", 0);
}

static ssize_t tawget_stat_wu_cweation_time_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_device *dev = to_stat_wu_dev(item);

	/* scsiWuCweationTime */
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", (u32)(((u32)dev->cweation_time -
				INITIAW_JIFFIES) * 100 / HZ));
}

CONFIGFS_ATTW_WO(tawget_stat_wu_, inst);
CONFIGFS_ATTW_WO(tawget_stat_wu_, dev);
CONFIGFS_ATTW_WO(tawget_stat_wu_, indx);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wun);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wu_name);
CONFIGFS_ATTW_WO(tawget_stat_wu_, vend);
CONFIGFS_ATTW_WO(tawget_stat_wu_, pwod);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wev);
CONFIGFS_ATTW_WO(tawget_stat_wu_, dev_type);
CONFIGFS_ATTW_WO(tawget_stat_wu_, status);
CONFIGFS_ATTW_WO(tawget_stat_wu_, state_bit);
CONFIGFS_ATTW_WO(tawget_stat_wu_, num_cmds);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wead_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wwite_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_wu_, wesets);
CONFIGFS_ATTW_WO(tawget_stat_wu_, fuww_stat);
CONFIGFS_ATTW_WO(tawget_stat_wu_, hs_num_cmds);
CONFIGFS_ATTW_WO(tawget_stat_wu_, cweation_time);

static stwuct configfs_attwibute *tawget_stat_scsi_wu_attws[] = {
	&tawget_stat_wu_attw_inst,
	&tawget_stat_wu_attw_dev,
	&tawget_stat_wu_attw_indx,
	&tawget_stat_wu_attw_wun,
	&tawget_stat_wu_attw_wu_name,
	&tawget_stat_wu_attw_vend,
	&tawget_stat_wu_attw_pwod,
	&tawget_stat_wu_attw_wev,
	&tawget_stat_wu_attw_dev_type,
	&tawget_stat_wu_attw_status,
	&tawget_stat_wu_attw_state_bit,
	&tawget_stat_wu_attw_num_cmds,
	&tawget_stat_wu_attw_wead_mbytes,
	&tawget_stat_wu_attw_wwite_mbytes,
	&tawget_stat_wu_attw_wesets,
	&tawget_stat_wu_attw_fuww_stat,
	&tawget_stat_wu_attw_hs_num_cmds,
	&tawget_stat_wu_attw_cweation_time,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_wu_cit = {
	.ct_attws		= tawget_stat_scsi_wu_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Cawwed fwom tawget_cowe_configfs.c:tawget_cowe_make_subdev() to setup
 * the tawget statistics gwoups + configfs CITs wocated in tawget_cowe_stat.c
 */
void tawget_stat_setup_dev_defauwt_gwoups(stwuct se_device *dev)
{
	config_gwoup_init_type_name(&dev->dev_stat_gwps.scsi_dev_gwoup,
			"scsi_dev", &tawget_stat_scsi_dev_cit);
	configfs_add_defauwt_gwoup(&dev->dev_stat_gwps.scsi_dev_gwoup,
			&dev->dev_stat_gwps.stat_gwoup);

	config_gwoup_init_type_name(&dev->dev_stat_gwps.scsi_tgt_dev_gwoup,
			"scsi_tgt_dev", &tawget_stat_scsi_tgt_dev_cit);
	configfs_add_defauwt_gwoup(&dev->dev_stat_gwps.scsi_tgt_dev_gwoup,
			&dev->dev_stat_gwps.stat_gwoup);

	config_gwoup_init_type_name(&dev->dev_stat_gwps.scsi_wu_gwoup,
			"scsi_wu", &tawget_stat_scsi_wu_cit);
	configfs_add_defauwt_gwoup(&dev->dev_stat_gwps.scsi_wu_gwoup,
			&dev->dev_stat_gwps.stat_gwoup);
}

/*
 * SCSI Powt Tabwe
 */

static stwuct se_wun *to_stat_powt(stwuct config_item *item)
{
	stwuct se_powt_stat_gwps *pgwps = containew_of(to_config_gwoup(item),
			stwuct se_powt_stat_gwps, scsi_powt_gwoup);
	wetuwn containew_of(pgwps, stwuct se_wun, powt_stat_gwps);
}

static ssize_t tawget_stat_powt_inst_show(stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = to_stat_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", dev->hba_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_powt_dev_show(stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = to_stat_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", dev->dev_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_powt_indx_show(stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = to_stat_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", wun->wun_tpg->tpg_wtpi);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_powt_wowe_show(stwuct config_item *item, chaw *page)
{
	stwuct se_wun *wun = to_stat_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%s%u\n", "Device", dev->dev_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_powt_busy_count_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev) {
		/* FIXME: scsiPowtBusyStatuses  */
		wet = snpwintf(page, PAGE_SIZE, "%u\n", 0);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

CONFIGFS_ATTW_WO(tawget_stat_powt_, inst);
CONFIGFS_ATTW_WO(tawget_stat_powt_, dev);
CONFIGFS_ATTW_WO(tawget_stat_powt_, indx);
CONFIGFS_ATTW_WO(tawget_stat_powt_, wowe);
CONFIGFS_ATTW_WO(tawget_stat_powt_, busy_count);

static stwuct configfs_attwibute *tawget_stat_scsi_powt_attws[] = {
	&tawget_stat_powt_attw_inst,
	&tawget_stat_powt_attw_dev,
	&tawget_stat_powt_attw_indx,
	&tawget_stat_powt_attw_wowe,
	&tawget_stat_powt_attw_busy_count,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_powt_cit = {
	.ct_attws		= tawget_stat_scsi_powt_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * SCSI Tawget Powt Tabwe
 */
static stwuct se_wun *to_stat_tgt_powt(stwuct config_item *item)
{
	stwuct se_powt_stat_gwps *pgwps = containew_of(to_config_gwoup(item),
			stwuct se_powt_stat_gwps, scsi_tgt_powt_gwoup);
	wetuwn containew_of(pgwps, stwuct se_wun, powt_stat_gwps);
}

static ssize_t tawget_stat_tgt_powt_inst_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", dev->hba_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_dev_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", dev->dev_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", wun->wun_tpg->tpg_wtpi);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%sPowt#%u\n",
			tpg->se_tpg_tfo->fabwic_name,
			wun->wun_tpg->tpg_wtpi);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_powt_index_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%s%s%d\n",
			tpg->se_tpg_tfo->tpg_get_wwn(tpg), "+t+",
			tpg->se_tpg_tfo->tpg_get_tag(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_in_cmds_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%wu\n",
			       atomic_wong_wead(&wun->wun_stats.cmd_pdus));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_wwite_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n",
			(u32)(atomic_wong_wead(&wun->wun_stats.wx_data_octets) >> 20));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_wead_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n",
				(u32)(atomic_wong_wead(&wun->wun_stats.tx_data_octets) >> 20));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_tgt_powt_hs_in_cmds_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_stat_tgt_powt(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev) {
		/* FIXME: scsiTgtPowtHsInCommands */
		wet = snpwintf(page, PAGE_SIZE, "%u\n", 0);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, inst);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, dev);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, indx);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, name);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, powt_index);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, in_cmds);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, wwite_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, wead_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_tgt_powt_, hs_in_cmds);

static stwuct configfs_attwibute *tawget_stat_scsi_tgt_powt_attws[] = {
	&tawget_stat_tgt_powt_attw_inst,
	&tawget_stat_tgt_powt_attw_dev,
	&tawget_stat_tgt_powt_attw_indx,
	&tawget_stat_tgt_powt_attw_name,
	&tawget_stat_tgt_powt_attw_powt_index,
	&tawget_stat_tgt_powt_attw_in_cmds,
	&tawget_stat_tgt_powt_attw_wwite_mbytes,
	&tawget_stat_tgt_powt_attw_wead_mbytes,
	&tawget_stat_tgt_powt_attw_hs_in_cmds,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_tgt_powt_cit = {
	.ct_attws		= tawget_stat_scsi_tgt_powt_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * SCSI Twanspowt Tabwe
 */
static stwuct se_wun *to_twanspowt_stat(stwuct config_item *item)
{
	stwuct se_powt_stat_gwps *pgwps = containew_of(to_config_gwoup(item),
			stwuct se_powt_stat_gwps, scsi_twanspowt_gwoup);
	wetuwn containew_of(pgwps, stwuct se_wun, powt_stat_gwps);
}

static ssize_t tawget_stat_twanspowt_inst_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_twanspowt_stat(item);
	stwuct se_device *dev;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", dev->hba_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_twanspowt_device_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_twanspowt_stat(item);
	stwuct se_device *dev;
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev) {
		/* scsiTwanspowtType */
		wet = snpwintf(page, PAGE_SIZE, "scsiTwanspowt%s\n",
			       tpg->se_tpg_tfo->fabwic_name);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_twanspowt_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_twanspowt_stat(item);
	stwuct se_device *dev;
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n",
			       tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_twanspowt_dev_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_twanspowt_stat(item);
	stwuct se_device *dev;
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	stwuct t10_wwn *wwn;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev) {
		wwn = &dev->t10_wwn;
		/* scsiTwanspowtDevName */
		wet = snpwintf(page, PAGE_SIZE, "%s+%s\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				(stwwen(wwn->unit_sewiaw)) ? wwn->unit_sewiaw :
				wwn->vendow);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_twanspowt_pwoto_id_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun *wun = to_twanspowt_stat(item);
	stwuct se_device *dev;
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	ssize_t wet = -ENODEV;

	wcu_wead_wock();
	dev = wcu_dewefewence(wun->wun_se_dev);
	if (dev)
		wet = snpwintf(page, PAGE_SIZE, "%u\n", tpg->pwoto_id);
	wcu_wead_unwock();
	wetuwn wet;
}

CONFIGFS_ATTW_WO(tawget_stat_twanspowt_, inst);
CONFIGFS_ATTW_WO(tawget_stat_twanspowt_, device);
CONFIGFS_ATTW_WO(tawget_stat_twanspowt_, indx);
CONFIGFS_ATTW_WO(tawget_stat_twanspowt_, dev_name);
CONFIGFS_ATTW_WO(tawget_stat_twanspowt_, pwoto_id);

static stwuct configfs_attwibute *tawget_stat_scsi_twanspowt_attws[] = {
	&tawget_stat_twanspowt_attw_inst,
	&tawget_stat_twanspowt_attw_device,
	&tawget_stat_twanspowt_attw_indx,
	&tawget_stat_twanspowt_attw_dev_name,
	&tawget_stat_twanspowt_attw_pwoto_id,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_twanspowt_cit = {
	.ct_attws		= tawget_stat_scsi_twanspowt_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Cawwed fwom tawget_cowe_fabwic_configfs.c:tawget_fabwic_make_wun() to setup
 * the tawget powt statistics gwoups + configfs CITs wocated in tawget_cowe_stat.c
 */
void tawget_stat_setup_powt_defauwt_gwoups(stwuct se_wun *wun)
{
	config_gwoup_init_type_name(&wun->powt_stat_gwps.scsi_powt_gwoup,
			"scsi_powt", &tawget_stat_scsi_powt_cit);
	configfs_add_defauwt_gwoup(&wun->powt_stat_gwps.scsi_powt_gwoup,
			&wun->powt_stat_gwps.stat_gwoup);

	config_gwoup_init_type_name(&wun->powt_stat_gwps.scsi_tgt_powt_gwoup,
			"scsi_tgt_powt", &tawget_stat_scsi_tgt_powt_cit);
	configfs_add_defauwt_gwoup(&wun->powt_stat_gwps.scsi_tgt_powt_gwoup,
			&wun->powt_stat_gwps.stat_gwoup);

	config_gwoup_init_type_name(&wun->powt_stat_gwps.scsi_twanspowt_gwoup,
			"scsi_twanspowt", &tawget_stat_scsi_twanspowt_cit);
	configfs_add_defauwt_gwoup(&wun->powt_stat_gwps.scsi_twanspowt_gwoup,
			&wun->powt_stat_gwps.stat_gwoup);
}

/*
 * SCSI Authowized Initiatow Tabwe
 */

static stwuct se_wun_acw *auth_to_wacw(stwuct config_item *item)
{
	stwuct se_mw_stat_gwps *wgwps = containew_of(to_config_gwoup(item),
			stwuct se_mw_stat_gwps, scsi_auth_intw_gwoup);
	wetuwn containew_of(wgwps, stwuct se_wun_acw, mw_stat_gwps);
}

static ssize_t tawget_stat_auth_inst_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	tpg = nacw->se_tpg;
	/* scsiInstIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_dev_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}

	/* scsiDeviceIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", deve->se_wun->wun_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_powt_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	tpg = nacw->se_tpg;
	/* scsiAuthIntwTgtPowtIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", tpg->se_tpg_tfo->tpg_get_tag(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", nacw->acw_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_dev_ow_powt_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwDevOwPowt */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", 1);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_intw_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwName */
	wet = snpwintf(page, PAGE_SIZE, "%s\n", nacw->initiatowname);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_map_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* FIXME: scsiAuthIntwWunMapIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", 0);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_att_count_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwAttachedTimes */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", deve->attach_count);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_num_cmds_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwOutCommands */
	wet = snpwintf(page, PAGE_SIZE, "%wu\n",
		       atomic_wong_wead(&deve->totaw_cmds));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_wead_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwWeadMegaBytes */
	wet = snpwintf(page, PAGE_SIZE, "%u\n",
		      (u32)(atomic_wong_wead(&deve->wead_bytes) >> 20));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_wwite_mbytes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwWwittenMegaBytes */
	wet = snpwintf(page, PAGE_SIZE, "%u\n",
		      (u32)(atomic_wong_wead(&deve->wwite_bytes) >> 20));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_hs_num_cmds_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* FIXME: scsiAuthIntwHSOutCommands */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", 0);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_cweation_time_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAuthIntwWastCweation */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", (u32)(((u32)deve->cweation_time -
				INITIAW_JIFFIES) * 100 / HZ));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_auth_wow_status_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = auth_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* FIXME: scsiAuthIntwWowStatus */
	wet = snpwintf(page, PAGE_SIZE, "Weady\n");
	wcu_wead_unwock();
	wetuwn wet;
}

CONFIGFS_ATTW_WO(tawget_stat_auth_, inst);
CONFIGFS_ATTW_WO(tawget_stat_auth_, dev);
CONFIGFS_ATTW_WO(tawget_stat_auth_, powt);
CONFIGFS_ATTW_WO(tawget_stat_auth_, indx);
CONFIGFS_ATTW_WO(tawget_stat_auth_, dev_ow_powt);
CONFIGFS_ATTW_WO(tawget_stat_auth_, intw_name);
CONFIGFS_ATTW_WO(tawget_stat_auth_, map_indx);
CONFIGFS_ATTW_WO(tawget_stat_auth_, att_count);
CONFIGFS_ATTW_WO(tawget_stat_auth_, num_cmds);
CONFIGFS_ATTW_WO(tawget_stat_auth_, wead_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_auth_, wwite_mbytes);
CONFIGFS_ATTW_WO(tawget_stat_auth_, hs_num_cmds);
CONFIGFS_ATTW_WO(tawget_stat_auth_, cweation_time);
CONFIGFS_ATTW_WO(tawget_stat_auth_, wow_status);

static stwuct configfs_attwibute *tawget_stat_scsi_auth_intw_attws[] = {
	&tawget_stat_auth_attw_inst,
	&tawget_stat_auth_attw_dev,
	&tawget_stat_auth_attw_powt,
	&tawget_stat_auth_attw_indx,
	&tawget_stat_auth_attw_dev_ow_powt,
	&tawget_stat_auth_attw_intw_name,
	&tawget_stat_auth_attw_map_indx,
	&tawget_stat_auth_attw_att_count,
	&tawget_stat_auth_attw_num_cmds,
	&tawget_stat_auth_attw_wead_mbytes,
	&tawget_stat_auth_attw_wwite_mbytes,
	&tawget_stat_auth_attw_hs_num_cmds,
	&tawget_stat_auth_attw_cweation_time,
	&tawget_stat_auth_attw_wow_status,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_auth_intw_cit = {
	.ct_attws		= tawget_stat_scsi_auth_intw_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * SCSI Attached Initiatow Powt Tabwe
 */

static stwuct se_wun_acw *ipowt_to_wacw(stwuct config_item *item)
{
	stwuct se_mw_stat_gwps *wgwps = containew_of(to_config_gwoup(item),
			stwuct se_mw_stat_gwps, scsi_att_intw_powt_gwoup);
	wetuwn containew_of(wgwps, stwuct se_wun_acw, mw_stat_gwps);
}

static ssize_t tawget_stat_ipowt_inst_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	tpg = nacw->se_tpg;
	/* scsiInstIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_ipowt_dev_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}

	/* scsiDeviceIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", deve->se_wun->wun_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_ipowt_powt_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	tpg = nacw->se_tpg;
	/* scsiPowtIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", tpg->se_tpg_tfo->tpg_get_tag(tpg));
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_ipowt_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_session *se_sess;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;

	spin_wock_iwq(&nacw->nacw_sess_wock);
	se_sess = nacw->nacw_sess;
	if (!se_sess) {
		spin_unwock_iwq(&nacw->nacw_sess_wock);
		wetuwn -ENODEV;
	}

	tpg = nacw->se_tpg;
	/* scsiAttIntwPowtIndex */
	wet = snpwintf(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->sess_get_index(se_sess));
	spin_unwock_iwq(&nacw->nacw_sess_wock);
	wetuwn wet;
}

static ssize_t tawget_stat_ipowt_powt_auth_indx_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_dev_entwy *deve;
	ssize_t wet;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, wacw->mapped_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	/* scsiAttIntwPowtAuthIntwIdx */
	wet = snpwintf(page, PAGE_SIZE, "%u\n", nacw->acw_index);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t tawget_stat_ipowt_powt_ident_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_wun_acw *wacw = ipowt_to_wacw(item);
	stwuct se_node_acw *nacw = wacw->se_wun_nacw;
	stwuct se_session *se_sess;
	stwuct se_powtaw_gwoup *tpg;
	ssize_t wet;
	unsigned chaw buf[64];

	spin_wock_iwq(&nacw->nacw_sess_wock);
	se_sess = nacw->nacw_sess;
	if (!se_sess) {
		spin_unwock_iwq(&nacw->nacw_sess_wock);
		wetuwn -ENODEV;
	}

	tpg = nacw->se_tpg;
	/* scsiAttIntwPowtName+scsiAttIntwPowtIdentifiew */
	memset(buf, 0, 64);
	if (tpg->se_tpg_tfo->sess_get_initiatow_sid != NUWW)
		tpg->se_tpg_tfo->sess_get_initiatow_sid(se_sess, buf, 64);

	wet = snpwintf(page, PAGE_SIZE, "%s+i+%s\n", nacw->initiatowname, buf);
	spin_unwock_iwq(&nacw->nacw_sess_wock);
	wetuwn wet;
}

CONFIGFS_ATTW_WO(tawget_stat_ipowt_, inst);
CONFIGFS_ATTW_WO(tawget_stat_ipowt_, dev);
CONFIGFS_ATTW_WO(tawget_stat_ipowt_, powt);
CONFIGFS_ATTW_WO(tawget_stat_ipowt_, indx);
CONFIGFS_ATTW_WO(tawget_stat_ipowt_, powt_auth_indx);
CONFIGFS_ATTW_WO(tawget_stat_ipowt_, powt_ident);

static stwuct configfs_attwibute *tawget_stat_scsi_ath_intw_powt_attws[] = {
	&tawget_stat_ipowt_attw_inst,
	&tawget_stat_ipowt_attw_dev,
	&tawget_stat_ipowt_attw_powt,
	&tawget_stat_ipowt_attw_indx,
	&tawget_stat_ipowt_attw_powt_auth_indx,
	&tawget_stat_ipowt_attw_powt_ident,
	NUWW,
};

static const stwuct config_item_type tawget_stat_scsi_att_intw_powt_cit = {
	.ct_attws		= tawget_stat_scsi_ath_intw_powt_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Cawwed fwom tawget_cowe_fabwic_configfs.c:tawget_fabwic_make_mappedwun() to setup
 * the tawget MappedWUN statistics gwoups + configfs CITs wocated in tawget_cowe_stat.c
 */
void tawget_stat_setup_mappedwun_defauwt_gwoups(stwuct se_wun_acw *wacw)
{
	config_gwoup_init_type_name(&wacw->mw_stat_gwps.scsi_auth_intw_gwoup,
			"scsi_auth_intw", &tawget_stat_scsi_auth_intw_cit);
	configfs_add_defauwt_gwoup(&wacw->mw_stat_gwps.scsi_auth_intw_gwoup,
			&wacw->mw_stat_gwps.stat_gwoup);

	config_gwoup_init_type_name(&wacw->mw_stat_gwps.scsi_att_intw_powt_gwoup,
			"scsi_att_intw_powt", &tawget_stat_scsi_att_intw_powt_cit);
	configfs_add_defauwt_gwoup(&wacw->mw_stat_gwps.scsi_att_intw_powt_gwoup,
			&wacw->mw_stat_gwps.stat_gwoup);
}
