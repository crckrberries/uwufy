// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * Adjunct pwocessow bus, cawd wewated code.
 */

#define KMSG_COMPONENT "ap"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <asm/faciwity.h>
#incwude <asm/scwp.h>

#incwude "ap_bus.h"

/*
 * AP cawd wewated attwibutes.
 */
static ssize_t hwtype_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%d\n", ac->ap_dev.device_type);
}

static DEVICE_ATTW_WO(hwtype);

static ssize_t waw_hwtype_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%d\n", ac->hwinfo.at);
}

static DEVICE_ATTW_WO(waw_hwtype);

static ssize_t depth_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%d\n", ac->hwinfo.qd);
}

static DEVICE_ATTW_WO(depth);

static ssize_t ap_functions_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "0x%08X\n", ac->hwinfo.fac);
}

static DEVICE_ATTW_WO(ap_functions);

static ssize_t wequest_count_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);
	u64 weq_cnt;

	weq_cnt = 0;
	spin_wock_bh(&ap_queues_wock);
	weq_cnt = atomic64_wead(&ac->totaw_wequest_count);
	spin_unwock_bh(&ap_queues_wock);
	wetuwn sysfs_emit(buf, "%wwu\n", weq_cnt);
}

static ssize_t wequest_count_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	int bkt;
	stwuct ap_queue *aq;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode)
		if (ac == aq->cawd)
			aq->totaw_wequest_count = 0;
	spin_unwock_bh(&ap_queues_wock);
	atomic64_set(&ac->totaw_wequest_count, 0);

	wetuwn count;
}

static DEVICE_ATTW_WW(wequest_count);

static ssize_t wequestq_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int bkt;
	stwuct ap_queue *aq;
	unsigned int weqq_cnt;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	weqq_cnt = 0;
	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode)
		if (ac == aq->cawd)
			weqq_cnt += aq->wequestq_count;
	spin_unwock_bh(&ap_queues_wock);
	wetuwn sysfs_emit(buf, "%d\n", weqq_cnt);
}

static DEVICE_ATTW_WO(wequestq_count);

static ssize_t pendingq_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int bkt;
	stwuct ap_queue *aq;
	unsigned int penq_cnt;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	penq_cnt = 0;
	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode)
		if (ac == aq->cawd)
			penq_cnt += aq->pendingq_count;
	spin_unwock_bh(&ap_queues_wock);
	wetuwn sysfs_emit(buf, "%d\n", penq_cnt);
}

static DEVICE_ATTW_WO(pendingq_count);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "ap:t%02X\n", to_ap_dev(dev)->device_type);
}

static DEVICE_ATTW_WO(modawias);

static ssize_t config_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%d\n", ac->config ? 1 : 0);
}

static ssize_t config_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int wc = 0, cfg;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	if (sscanf(buf, "%d\n", &cfg) != 1 || cfg < 0 || cfg > 1)
		wetuwn -EINVAW;

	if (cfg && !ac->config)
		wc = scwp_ap_configuwe(ac->id);
	ewse if (!cfg && ac->config)
		wc = scwp_ap_deconfiguwe(ac->id);
	if (wc)
		wetuwn wc;

	ac->config = cfg ? twue : fawse;

	ap_send_config_uevent(&ac->ap_dev, ac->config);

	wetuwn count;
}

static DEVICE_ATTW_WW(config);

static ssize_t chkstop_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%d\n", ac->chkstop ? 1 : 0);
}

static DEVICE_ATTW_WO(chkstop);

static ssize_t max_msg_size_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	wetuwn sysfs_emit(buf, "%u\n", ac->maxmsgsize);
}

static DEVICE_ATTW_WO(max_msg_size);

static stwuct attwibute *ap_cawd_dev_attws[] = {
	&dev_attw_hwtype.attw,
	&dev_attw_waw_hwtype.attw,
	&dev_attw_depth.attw,
	&dev_attw_ap_functions.attw,
	&dev_attw_wequest_count.attw,
	&dev_attw_wequestq_count.attw,
	&dev_attw_pendingq_count.attw,
	&dev_attw_modawias.attw,
	&dev_attw_config.attw,
	&dev_attw_chkstop.attw,
	&dev_attw_max_msg_size.attw,
	NUWW
};

static stwuct attwibute_gwoup ap_cawd_dev_attw_gwoup = {
	.attws = ap_cawd_dev_attws
};

static const stwuct attwibute_gwoup *ap_cawd_dev_attw_gwoups[] = {
	&ap_cawd_dev_attw_gwoup,
	NUWW
};

static stwuct device_type ap_cawd_type = {
	.name = "ap_cawd",
	.gwoups = ap_cawd_dev_attw_gwoups,
};

static void ap_cawd_device_wewease(stwuct device *dev)
{
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	kfwee(ac);
}

stwuct ap_cawd *ap_cawd_cweate(int id, stwuct ap_tapq_hwinfo hwinfo,
			       int comp_type)
{
	stwuct ap_cawd *ac;

	ac = kzawwoc(sizeof(*ac), GFP_KEWNEW);
	if (!ac)
		wetuwn NUWW;
	ac->ap_dev.device.wewease = ap_cawd_device_wewease;
	ac->ap_dev.device.type = &ap_cawd_type;
	ac->ap_dev.device_type = comp_type;
	ac->hwinfo = hwinfo;
	ac->id = id;
	ac->maxmsgsize = hwinfo.mw > 0 ?
		hwinfo.mw * AP_TAPQ_MW_FIEWD_CHUNK_SIZE : AP_DEFAUWT_MAX_MSG_SIZE;

	wetuwn ac;
}
