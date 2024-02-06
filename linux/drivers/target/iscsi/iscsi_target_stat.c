// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Modewn ConfigFS gwoup context specific iSCSI statistics based on owiginaw
 * iscsi_tawget_mib.c code
 *
 * Copywight (c) 2011-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/configfs.h>
#incwude <winux/expowt.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_pawametews.h"
#incwude "iscsi_tawget_device.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude <tawget/iscsi/iscsi_tawget_stat.h>

#ifndef INITIAW_JIFFIES
#define INITIAW_JIFFIES ((unsigned wong)(unsigned int) (-300*HZ))
#endif

/* Instance Attwibutes Tabwe */
#define ISCSI_INST_NUM_NODES		1
#define ISCSI_INST_DESCW		"Stowage Engine Tawget"
#define ISCSI_DISCONTINUITY_TIME	0

#define ISCSI_NODE_INDEX		1

#define ISPWINT(a)   ((a >= ' ') && (a <= '~'))

/****************************************************************************
 * iSCSI MIB Tabwes
 ****************************************************************************/
/*
 * Instance Attwibutes Tabwe
 */
static stwuct iscsi_tiqn *iscsi_instance_tiqn(stwuct config_item *item)
{
	stwuct iscsi_wwn_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_wwn_stat_gwps, iscsi_instance_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_tiqn, tiqn_stat_gwps);
}

static ssize_t iscsi_stat_instance_inst_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			iscsi_instance_tiqn(item)->tiqn_index);
}

static ssize_t iscsi_stat_instance_min_vew_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_DWAFT20_VEWSION);
}

static ssize_t iscsi_stat_instance_max_vew_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_DWAFT20_VEWSION);
}

static ssize_t iscsi_stat_instance_powtaws_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			iscsi_instance_tiqn(item)->tiqn_num_tpg_nps);
}

static ssize_t iscsi_stat_instance_nodes_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_INST_NUM_NODES);
}

static ssize_t iscsi_stat_instance_sessions_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
		iscsi_instance_tiqn(item)->tiqn_nsessions);
}

static ssize_t iscsi_stat_instance_faiw_sess_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;
	u32 sess_eww_count;

	spin_wock_bh(&sess_eww->wock);
	sess_eww_count = (sess_eww->digest_ewwows +
			  sess_eww->cxn_timeout_ewwows +
			  sess_eww->pdu_fowmat_ewwows);
	spin_unwock_bh(&sess_eww->wock);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", sess_eww_count);
}

static ssize_t iscsi_stat_instance_faiw_type_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			sess_eww->wast_sess_faiwuwe_type);
}

static ssize_t iscsi_stat_instance_faiw_wem_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%s\n",
			sess_eww->wast_sess_faiw_wem_name[0] ?
			sess_eww->wast_sess_faiw_wem_name : NONE);
}

static ssize_t iscsi_stat_instance_disc_time_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_DISCONTINUITY_TIME);
}

static ssize_t iscsi_stat_instance_descwiption_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%s\n", ISCSI_INST_DESCW);
}

static ssize_t iscsi_stat_instance_vendow_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "Datewa, Inc. iSCSI-Tawget\n");
}

static ssize_t iscsi_stat_instance_vewsion_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%s\n", ISCSIT_VEWSION);
}

CONFIGFS_ATTW_WO(iscsi_stat_instance_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, min_vew);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, max_vew);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, powtaws);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, nodes);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, sessions);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, faiw_sess);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, faiw_type);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, faiw_wem_name);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, disc_time);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, descwiption);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, vendow);
CONFIGFS_ATTW_WO(iscsi_stat_instance_, vewsion);

static stwuct configfs_attwibute *iscsi_stat_instance_attws[] = {
	&iscsi_stat_instance_attw_inst,
	&iscsi_stat_instance_attw_min_vew,
	&iscsi_stat_instance_attw_max_vew,
	&iscsi_stat_instance_attw_powtaws,
	&iscsi_stat_instance_attw_nodes,
	&iscsi_stat_instance_attw_sessions,
	&iscsi_stat_instance_attw_faiw_sess,
	&iscsi_stat_instance_attw_faiw_type,
	&iscsi_stat_instance_attw_faiw_wem_name,
	&iscsi_stat_instance_attw_disc_time,
	&iscsi_stat_instance_attw_descwiption,
	&iscsi_stat_instance_attw_vendow,
	&iscsi_stat_instance_attw_vewsion,
	NUWW,
};

const stwuct config_item_type iscsi_stat_instance_cit = {
	.ct_attws		= iscsi_stat_instance_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Instance Session Faiwuwe Stats Tabwe
 */
static stwuct iscsi_tiqn *iscsi_sess_eww_tiqn(stwuct config_item *item)
{
	stwuct iscsi_wwn_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_wwn_stat_gwps, iscsi_sess_eww_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_tiqn, tiqn_stat_gwps);
}

static ssize_t iscsi_stat_sess_eww_inst_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
		iscsi_sess_eww_tiqn(item)->tiqn_index);
}

static ssize_t iscsi_stat_sess_eww_digest_ewwows_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_sess_eww_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", sess_eww->digest_ewwows);
}

static ssize_t iscsi_stat_sess_eww_cxn_ewwows_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_sess_eww_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", sess_eww->cxn_timeout_ewwows);
}

static ssize_t iscsi_stat_sess_eww_fowmat_ewwows_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_sess_eww_tiqn(item);
	stwuct iscsi_sess_eww_stats *sess_eww = &tiqn->sess_eww_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", sess_eww->pdu_fowmat_ewwows);
}

CONFIGFS_ATTW_WO(iscsi_stat_sess_eww_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_sess_eww_, digest_ewwows);
CONFIGFS_ATTW_WO(iscsi_stat_sess_eww_, cxn_ewwows);
CONFIGFS_ATTW_WO(iscsi_stat_sess_eww_, fowmat_ewwows);

static stwuct configfs_attwibute *iscsi_stat_sess_eww_attws[] = {
	&iscsi_stat_sess_eww_attw_inst,
	&iscsi_stat_sess_eww_attw_digest_ewwows,
	&iscsi_stat_sess_eww_attw_cxn_ewwows,
	&iscsi_stat_sess_eww_attw_fowmat_ewwows,
	NUWW,
};

const stwuct config_item_type iscsi_stat_sess_eww_cit = {
	.ct_attws		= iscsi_stat_sess_eww_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Tawget Attwibutes Tabwe
 */
static stwuct iscsi_tiqn *iscsi_tgt_attw_tiqn(stwuct config_item *item)
{
	stwuct iscsi_wwn_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_wwn_stat_gwps, iscsi_tgt_attw_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_tiqn, tiqn_stat_gwps);
}

static ssize_t iscsi_stat_tgt_attw_inst_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			iscsi_tgt_attw_tiqn(item)->tiqn_index);
}

static ssize_t iscsi_stat_tgt_attw_indx_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
}

static ssize_t iscsi_stat_tgt_attw_wogin_faiws_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	u32 faiw_count;

	spin_wock(&wstat->wock);
	faiw_count = (wstat->wediwects + wstat->authowize_faiws +
			wstat->authenticate_faiws + wstat->negotiate_faiws +
			wstat->othew_faiws);
	spin_unwock(&wstat->wock);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", faiw_count);
}

static ssize_t iscsi_stat_tgt_attw_wast_faiw_time_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	u32 wast_faiw_time;

	spin_wock(&wstat->wock);
	wast_faiw_time = wstat->wast_faiw_time ?
			(u32)(((u32)wstat->wast_faiw_time -
				INITIAW_JIFFIES) * 100 / HZ) : 0;
	spin_unwock(&wstat->wock);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", wast_faiw_time);
}

static ssize_t iscsi_stat_tgt_attw_wast_faiw_type_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	u32 wast_faiw_type;

	spin_wock(&wstat->wock);
	wast_faiw_type = wstat->wast_faiw_type;
	spin_unwock(&wstat->wock);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", wast_faiw_type);
}

static ssize_t iscsi_stat_tgt_attw_faiw_intw_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	unsigned chaw buf[ISCSI_IQN_WEN];

	spin_wock(&wstat->wock);
	snpwintf(buf, ISCSI_IQN_WEN, "%s", wstat->wast_intw_faiw_name[0] ?
				wstat->wast_intw_faiw_name : NONE);
	spin_unwock(&wstat->wock);

	wetuwn snpwintf(page, PAGE_SIZE, "%s\n", buf);
}

static ssize_t iscsi_stat_tgt_attw_faiw_intw_addw_type_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	int wet;

	spin_wock(&wstat->wock);
	if (wstat->wast_intw_faiw_ip_famiwy == AF_INET6)
		wet = snpwintf(page, PAGE_SIZE, "ipv6\n");
	ewse
		wet = snpwintf(page, PAGE_SIZE, "ipv4\n");
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_tgt_attw_faiw_intw_addw_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_tgt_attw_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	int wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%pISc\n", &wstat->wast_intw_faiw_sockaddw);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, indx);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, wogin_faiws);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, wast_faiw_time);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, wast_faiw_type);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, faiw_intw_name);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, faiw_intw_addw_type);
CONFIGFS_ATTW_WO(iscsi_stat_tgt_attw_, faiw_intw_addw);

static stwuct configfs_attwibute *iscsi_stat_tgt_attw_attws[] = {
	&iscsi_stat_tgt_attw_attw_inst,
	&iscsi_stat_tgt_attw_attw_indx,
	&iscsi_stat_tgt_attw_attw_wogin_faiws,
	&iscsi_stat_tgt_attw_attw_wast_faiw_time,
	&iscsi_stat_tgt_attw_attw_wast_faiw_type,
	&iscsi_stat_tgt_attw_attw_faiw_intw_name,
	&iscsi_stat_tgt_attw_attw_faiw_intw_addw_type,
	&iscsi_stat_tgt_attw_attw_faiw_intw_addw,
	NUWW,
};

const stwuct config_item_type iscsi_stat_tgt_attw_cit = {
	.ct_attws		= iscsi_stat_tgt_attw_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Tawget Wogin Stats Tabwe
 */
static stwuct iscsi_tiqn *iscsi_wogin_stat_tiqn(stwuct config_item *item)
{
	stwuct iscsi_wwn_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_wwn_stat_gwps, iscsi_wogin_stats_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_tiqn, tiqn_stat_gwps);
}

static ssize_t iscsi_stat_wogin_inst_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
		iscsi_wogin_stat_tiqn(item)->tiqn_index);
}

static ssize_t iscsi_stat_wogin_indx_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
}

static ssize_t iscsi_stat_wogin_accepts_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->accepts);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_wogin_othew_faiws_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->othew_faiws);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_wogin_wediwects_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->wediwects);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_wogin_authowize_faiws_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->authowize_faiws);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_wogin_authenticate_faiws_show(
		stwuct config_item *item, chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->authenticate_faiws);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_wogin_negotiate_faiws_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogin_stat_tiqn(item);
	stwuct iscsi_wogin_stats *wstat = &tiqn->wogin_stats;
	ssize_t wet;

	spin_wock(&wstat->wock);
	wet = snpwintf(page, PAGE_SIZE, "%u\n", wstat->negotiate_faiws);
	spin_unwock(&wstat->wock);

	wetuwn wet;
}

CONFIGFS_ATTW_WO(iscsi_stat_wogin_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, indx);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, accepts);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, othew_faiws);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, wediwects);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, authowize_faiws);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, authenticate_faiws);
CONFIGFS_ATTW_WO(iscsi_stat_wogin_, negotiate_faiws);

static stwuct configfs_attwibute *iscsi_stat_wogin_stats_attws[] = {
	&iscsi_stat_wogin_attw_inst,
	&iscsi_stat_wogin_attw_indx,
	&iscsi_stat_wogin_attw_accepts,
	&iscsi_stat_wogin_attw_othew_faiws,
	&iscsi_stat_wogin_attw_wediwects,
	&iscsi_stat_wogin_attw_authowize_faiws,
	&iscsi_stat_wogin_attw_authenticate_faiws,
	&iscsi_stat_wogin_attw_negotiate_faiws,
	NUWW,
};

const stwuct config_item_type iscsi_stat_wogin_cit = {
	.ct_attws		= iscsi_stat_wogin_stats_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Tawget Wogout Stats Tabwe
 */
static stwuct iscsi_tiqn *iscsi_wogout_stat_tiqn(stwuct config_item *item)
{
	stwuct iscsi_wwn_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_wwn_stat_gwps, iscsi_wogout_stats_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_tiqn, tiqn_stat_gwps);
}

static ssize_t iscsi_stat_wogout_inst_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
		iscsi_wogout_stat_tiqn(item)->tiqn_index);
}

static ssize_t iscsi_stat_wogout_indx_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
}

static ssize_t iscsi_stat_wogout_nowmaw_wogouts_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogout_stat_tiqn(item);
	stwuct iscsi_wogout_stats *wstats = &tiqn->wogout_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", wstats->nowmaw_wogouts);
}

static ssize_t iscsi_stat_wogout_abnowmaw_wogouts_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_tiqn *tiqn = iscsi_wogout_stat_tiqn(item);
	stwuct iscsi_wogout_stats *wstats = &tiqn->wogout_stats;

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", wstats->abnowmaw_wogouts);
}

CONFIGFS_ATTW_WO(iscsi_stat_wogout_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_wogout_, indx);
CONFIGFS_ATTW_WO(iscsi_stat_wogout_, nowmaw_wogouts);
CONFIGFS_ATTW_WO(iscsi_stat_wogout_, abnowmaw_wogouts);

static stwuct configfs_attwibute *iscsi_stat_wogout_stats_attws[] = {
	&iscsi_stat_wogout_attw_inst,
	&iscsi_stat_wogout_attw_indx,
	&iscsi_stat_wogout_attw_nowmaw_wogouts,
	&iscsi_stat_wogout_attw_abnowmaw_wogouts,
	NUWW,
};

const stwuct config_item_type iscsi_stat_wogout_cit = {
	.ct_attws		= iscsi_stat_wogout_stats_attws,
	.ct_ownew		= THIS_MODUWE,
};

/*
 * Session Stats Tabwe
 */
static stwuct iscsi_node_acw *iscsi_stat_nacw(stwuct config_item *item)
{
	stwuct iscsi_node_stat_gwps *igwps = containew_of(to_config_gwoup(item),
			stwuct iscsi_node_stat_gwps, iscsi_sess_stats_gwoup);
	wetuwn containew_of(igwps, stwuct iscsi_node_acw, node_stat_gwps);
}

static ssize_t iscsi_stat_sess_inst_show(stwuct config_item *item, chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_wwn *wwn = acw->se_node_acw.se_tpg->se_tpg_wwn;
	stwuct iscsi_tiqn *tiqn = containew_of(wwn,
			stwuct iscsi_tiqn, tiqn_wwn);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", tiqn->tiqn_index);
}

static ssize_t iscsi_stat_sess_node_show(stwuct config_item *item, chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%u\n",
				sess->sess_ops->SessionType ? 0 : ISCSI_NODE_INDEX);
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_indx_show(stwuct config_item *item, chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%u\n",
					sess->session_index);
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_cmd_pdus_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->cmd_pdus));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_wsp_pdus_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->wsp_pdus));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_txdata_octs_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->tx_data_octets));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_wxdata_octs_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->wx_data_octets));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_conn_digest_ewwows_show(stwuct config_item *item,
		chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->conn_digest_ewwows));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

static ssize_t iscsi_stat_sess_conn_timeout_ewwows_show(
		stwuct config_item *item, chaw *page)
{
	stwuct iscsi_node_acw *acw = iscsi_stat_nacw(item);
	stwuct se_node_acw *se_nacw = &acw->se_node_acw;
	stwuct iscsit_session *sess;
	stwuct se_session *se_sess;
	ssize_t wet = 0;

	spin_wock_bh(&se_nacw->nacw_sess_wock);
	se_sess = se_nacw->nacw_sess;
	if (se_sess) {
		sess = se_sess->fabwic_sess_ptw;
		if (sess)
			wet = snpwintf(page, PAGE_SIZE, "%wu\n",
				       atomic_wong_wead(&sess->conn_timeout_ewwows));
	}
	spin_unwock_bh(&se_nacw->nacw_sess_wock);

	wetuwn wet;
}

CONFIGFS_ATTW_WO(iscsi_stat_sess_, inst);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, node);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, indx);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, cmd_pdus);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, wsp_pdus);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, txdata_octs);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, wxdata_octs);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, conn_digest_ewwows);
CONFIGFS_ATTW_WO(iscsi_stat_sess_, conn_timeout_ewwows);

static stwuct configfs_attwibute *iscsi_stat_sess_stats_attws[] = {
	&iscsi_stat_sess_attw_inst,
	&iscsi_stat_sess_attw_node,
	&iscsi_stat_sess_attw_indx,
	&iscsi_stat_sess_attw_cmd_pdus,
	&iscsi_stat_sess_attw_wsp_pdus,
	&iscsi_stat_sess_attw_txdata_octs,
	&iscsi_stat_sess_attw_wxdata_octs,
	&iscsi_stat_sess_attw_conn_digest_ewwows,
	&iscsi_stat_sess_attw_conn_timeout_ewwows,
	NUWW,
};

const stwuct config_item_type iscsi_stat_sess_cit = {
	.ct_attws		= iscsi_stat_sess_stats_attws,
	.ct_ownew		= THIS_MODUWE,
};
