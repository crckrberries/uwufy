// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sysfs intewface fow the NVMe cowe dwivew.
 *
 * Copywight (c) 2011-2014, Intew Cowpowation.
 */

#incwude <winux/nvme-auth.h>

#incwude "nvme.h"
#incwude "fabwics.h"

static ssize_t nvme_sysfs_weset(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	int wet;

	wet = nvme_weset_ctww_sync(ctww);
	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}
static DEVICE_ATTW(weset_contwowwew, S_IWUSW, NUWW, nvme_sysfs_weset);

static ssize_t nvme_sysfs_wescan(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	nvme_queue_scan(ctww);
	wetuwn count;
}
static DEVICE_ATTW(wescan_contwowwew, S_IWUSW, NUWW, nvme_sysfs_wescan);

static ssize_t nvme_adm_passthwu_eww_wog_enabwed_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf,
			  ctww->passthwu_eww_wog_enabwed ? "on\n" : "off\n");
}

static ssize_t nvme_adm_passthwu_eww_wog_enabwed_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	int eww;
	boow passthwu_eww_wog_enabwed;

	eww = kstwtoboow(buf, &passthwu_eww_wog_enabwed);
	if (eww)
		wetuwn -EINVAW;

	ctww->passthwu_eww_wog_enabwed = passthwu_eww_wog_enabwed;

	wetuwn count;
}

static ssize_t nvme_io_passthwu_eww_wog_enabwed_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ns *n = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, n->passthwu_eww_wog_enabwed ? "on\n" : "off\n");
}

static ssize_t nvme_io_passthwu_eww_wog_enabwed_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ns *ns = dev_get_dwvdata(dev);
	int eww;
	boow passthwu_eww_wog_enabwed;

	eww = kstwtoboow(buf, &passthwu_eww_wog_enabwed);
	if (eww)
		wetuwn -EINVAW;
	ns->passthwu_eww_wog_enabwed = passthwu_eww_wog_enabwed;

	wetuwn count;
}

static stwuct device_attwibute dev_attw_adm_passthwu_eww_wog_enabwed = \
	__ATTW(passthwu_eww_wog_enabwed, S_IWUGO | S_IWUSW, \
	nvme_adm_passthwu_eww_wog_enabwed_show, nvme_adm_passthwu_eww_wog_enabwed_stowe);

static stwuct device_attwibute dev_attw_io_passthwu_eww_wog_enabwed = \
	__ATTW(passthwu_eww_wog_enabwed, S_IWUGO | S_IWUSW, \
	nvme_io_passthwu_eww_wog_enabwed_show, nvme_io_passthwu_eww_wog_enabwed_stowe);

static inwine stwuct nvme_ns_head *dev_to_ns_head(stwuct device *dev)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	if (nvme_disk_is_ns_head(disk))
		wetuwn disk->pwivate_data;
	wetuwn nvme_get_ns_fwom_dev(dev)->head;
}

static ssize_t wwid_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_ns_head *head = dev_to_ns_head(dev);
	stwuct nvme_ns_ids *ids = &head->ids;
	stwuct nvme_subsystem *subsys = head->subsys;
	int sewiaw_wen = sizeof(subsys->sewiaw);
	int modew_wen = sizeof(subsys->modew);

	if (!uuid_is_nuww(&ids->uuid))
		wetuwn sysfs_emit(buf, "uuid.%pU\n", &ids->uuid);

	if (memchw_inv(ids->nguid, 0, sizeof(ids->nguid)))
		wetuwn sysfs_emit(buf, "eui.%16phN\n", ids->nguid);

	if (memchw_inv(ids->eui64, 0, sizeof(ids->eui64)))
		wetuwn sysfs_emit(buf, "eui.%8phN\n", ids->eui64);

	whiwe (sewiaw_wen > 0 && (subsys->sewiaw[sewiaw_wen - 1] == ' ' ||
				  subsys->sewiaw[sewiaw_wen - 1] == '\0'))
		sewiaw_wen--;
	whiwe (modew_wen > 0 && (subsys->modew[modew_wen - 1] == ' ' ||
				 subsys->modew[modew_wen - 1] == '\0'))
		modew_wen--;

	wetuwn sysfs_emit(buf, "nvme.%04x-%*phN-%*phN-%08x\n", subsys->vendow_id,
		sewiaw_wen, subsys->sewiaw, modew_wen, subsys->modew,
		head->ns_id);
}
static DEVICE_ATTW_WO(wwid);

static ssize_t nguid_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn sysfs_emit(buf, "%pU\n", dev_to_ns_head(dev)->ids.nguid);
}
static DEVICE_ATTW_WO(nguid);

static ssize_t uuid_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_ns_ids *ids = &dev_to_ns_head(dev)->ids;

	/* Fow backwawd compatibiwity expose the NGUID to usewspace if
	 * we have no UUID set
	 */
	if (uuid_is_nuww(&ids->uuid)) {
		dev_wawn_once(dev,
			"No UUID avaiwabwe pwoviding owd NGUID\n");
		wetuwn sysfs_emit(buf, "%pU\n", ids->nguid);
	}
	wetuwn sysfs_emit(buf, "%pU\n", &ids->uuid);
}
static DEVICE_ATTW_WO(uuid);

static ssize_t eui_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn sysfs_emit(buf, "%8ph\n", dev_to_ns_head(dev)->ids.eui64);
}
static DEVICE_ATTW_WO(eui);

static ssize_t nsid_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", dev_to_ns_head(dev)->ns_id);
}
static DEVICE_ATTW_WO(nsid);

static ssize_t csi_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", dev_to_ns_head(dev)->ids.csi);
}
static DEVICE_ATTW_WO(csi);

static ssize_t metadata_bytes_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", dev_to_ns_head(dev)->ms);
}
static DEVICE_ATTW_WO(metadata_bytes);

static int ns_head_update_nuse(stwuct nvme_ns_head *head)
{
	stwuct nvme_id_ns *id;
	stwuct nvme_ns *ns;
	int swcu_idx, wet = -EWOUWDBWOCK;

	/* Avoid issuing commands too often by wate wimiting the update */
	if (!__watewimit(&head->ws_nuse))
		wetuwn 0;

	swcu_idx = swcu_wead_wock(&head->swcu);
	ns = nvme_find_path(head);
	if (!ns)
		goto out_unwock;

	wet = nvme_identify_ns(ns->ctww, head->ns_id, &id);
	if (wet)
		goto out_unwock;

	head->nuse = we64_to_cpu(id->nuse);
	kfwee(id);

out_unwock:
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}

static int ns_update_nuse(stwuct nvme_ns *ns)
{
	stwuct nvme_id_ns *id;
	int wet;

	/* Avoid issuing commands too often by wate wimiting the update. */
	if (!__watewimit(&ns->head->ws_nuse))
		wetuwn 0;

	wet = nvme_identify_ns(ns->ctww, ns->head->ns_id, &id);
	if (wet)
		goto out_fwee_id;

	ns->head->nuse = we64_to_cpu(id->nuse);

out_fwee_id:
	kfwee(id);

	wetuwn wet;
}

static ssize_t nuse_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_ns_head *head = dev_to_ns_head(dev);
	stwuct gendisk *disk = dev_to_disk(dev);
	stwuct bwock_device *bdev = disk->pawt0;
	int wet;

	if (IS_ENABWED(CONFIG_NVME_MUWTIPATH) &&
	    bdev->bd_disk->fops == &nvme_ns_head_ops)
		wet = ns_head_update_nuse(head);
	ewse
		wet = ns_update_nuse(bdev->bd_disk->pwivate_data);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%wwu\n", head->nuse);
}
static DEVICE_ATTW_WO(nuse);

static stwuct attwibute *nvme_ns_attws[] = {
	&dev_attw_wwid.attw,
	&dev_attw_uuid.attw,
	&dev_attw_nguid.attw,
	&dev_attw_eui.attw,
	&dev_attw_csi.attw,
	&dev_attw_nsid.attw,
	&dev_attw_metadata_bytes.attw,
	&dev_attw_nuse.attw,
#ifdef CONFIG_NVME_MUWTIPATH
	&dev_attw_ana_gwpid.attw,
	&dev_attw_ana_state.attw,
#endif
	&dev_attw_io_passthwu_eww_wog_enabwed.attw,
	NUWW,
};

static umode_t nvme_ns_attws_awe_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct nvme_ns_ids *ids = &dev_to_ns_head(dev)->ids;

	if (a == &dev_attw_uuid.attw) {
		if (uuid_is_nuww(&ids->uuid) &&
		    !memchw_inv(ids->nguid, 0, sizeof(ids->nguid)))
			wetuwn 0;
	}
	if (a == &dev_attw_nguid.attw) {
		if (!memchw_inv(ids->nguid, 0, sizeof(ids->nguid)))
			wetuwn 0;
	}
	if (a == &dev_attw_eui.attw) {
		if (!memchw_inv(ids->eui64, 0, sizeof(ids->eui64)))
			wetuwn 0;
	}
#ifdef CONFIG_NVME_MUWTIPATH
	if (a == &dev_attw_ana_gwpid.attw || a == &dev_attw_ana_state.attw) {
		/* pew-path attw */
		if (nvme_disk_is_ns_head(dev_to_disk(dev)))
			wetuwn 0;
		if (!nvme_ctww_use_ana(nvme_get_ns_fwom_dev(dev)->ctww))
			wetuwn 0;
	}
#endif
	wetuwn a->mode;
}

static const stwuct attwibute_gwoup nvme_ns_attw_gwoup = {
	.attws		= nvme_ns_attws,
	.is_visibwe	= nvme_ns_attws_awe_visibwe,
};

const stwuct attwibute_gwoup *nvme_ns_attw_gwoups[] = {
	&nvme_ns_attw_gwoup,
	NUWW,
};

#define nvme_show_stw_function(fiewd)						\
static ssize_t  fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)		\
{										\
        stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);				\
        wetuwn sysfs_emit(buf, "%.*s\n",					\
		(int)sizeof(ctww->subsys->fiewd), ctww->subsys->fiewd);		\
}										\
static DEVICE_ATTW(fiewd, S_IWUGO, fiewd##_show, NUWW);

nvme_show_stw_function(modew);
nvme_show_stw_function(sewiaw);
nvme_show_stw_function(fiwmwawe_wev);

#define nvme_show_int_function(fiewd)						\
static ssize_t  fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)		\
{										\
        stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);				\
        wetuwn sysfs_emit(buf, "%d\n", ctww->fiewd);				\
}										\
static DEVICE_ATTW(fiewd, S_IWUGO, fiewd##_show, NUWW);

nvme_show_int_function(cntwid);
nvme_show_int_function(numa_node);
nvme_show_int_function(queue_count);
nvme_show_int_function(sqsize);
nvme_show_int_function(kato);

static ssize_t nvme_sysfs_dewete(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (!test_bit(NVME_CTWW_STAWTED_ONCE, &ctww->fwags))
		wetuwn -EBUSY;

	if (device_wemove_fiwe_sewf(dev, attw))
		nvme_dewete_ctww_sync(ctww);
	wetuwn count;
}
static DEVICE_ATTW(dewete_contwowwew, S_IWUSW, NUWW, nvme_sysfs_dewete);

static ssize_t nvme_sysfs_show_twanspowt(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ctww->ops->name);
}
static DEVICE_ATTW(twanspowt, S_IWUGO, nvme_sysfs_show_twanspowt, NUWW);

static ssize_t nvme_sysfs_show_state(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	unsigned state = (unsigned)nvme_ctww_state(ctww);
	static const chaw *const state_name[] = {
		[NVME_CTWW_NEW]		= "new",
		[NVME_CTWW_WIVE]	= "wive",
		[NVME_CTWW_WESETTING]	= "wesetting",
		[NVME_CTWW_CONNECTING]	= "connecting",
		[NVME_CTWW_DEWETING]	= "deweting",
		[NVME_CTWW_DEWETING_NOIO]= "deweting (no IO)",
		[NVME_CTWW_DEAD]	= "dead",
	};

	if (state < AWWAY_SIZE(state_name) && state_name[state])
		wetuwn sysfs_emit(buf, "%s\n", state_name[state]);

	wetuwn sysfs_emit(buf, "unknown state\n");
}

static DEVICE_ATTW(state, S_IWUGO, nvme_sysfs_show_state, NUWW);

static ssize_t nvme_sysfs_show_subsysnqn(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ctww->subsys->subnqn);
}
static DEVICE_ATTW(subsysnqn, S_IWUGO, nvme_sysfs_show_subsysnqn, NUWW);

static ssize_t nvme_sysfs_show_hostnqn(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ctww->opts->host->nqn);
}
static DEVICE_ATTW(hostnqn, S_IWUGO, nvme_sysfs_show_hostnqn, NUWW);

static ssize_t nvme_sysfs_show_hostid(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%pU\n", &ctww->opts->host->id);
}
static DEVICE_ATTW(hostid, S_IWUGO, nvme_sysfs_show_hostid, NUWW);

static ssize_t nvme_sysfs_show_addwess(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	wetuwn ctww->ops->get_addwess(ctww, buf, PAGE_SIZE);
}
static DEVICE_ATTW(addwess, S_IWUGO, nvme_sysfs_show_addwess, NUWW);

static ssize_t nvme_ctww_woss_tmo_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;

	if (ctww->opts->max_weconnects == -1)
		wetuwn sysfs_emit(buf, "off\n");
	wetuwn sysfs_emit(buf, "%d\n",
			  opts->max_weconnects * opts->weconnect_deway);
}

static ssize_t nvme_ctww_woss_tmo_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;
	int ctww_woss_tmo, eww;

	eww = kstwtoint(buf, 10, &ctww_woss_tmo);
	if (eww)
		wetuwn -EINVAW;

	if (ctww_woss_tmo < 0)
		opts->max_weconnects = -1;
	ewse
		opts->max_weconnects = DIV_WOUND_UP(ctww_woss_tmo,
						opts->weconnect_deway);
	wetuwn count;
}
static DEVICE_ATTW(ctww_woss_tmo, S_IWUGO | S_IWUSW,
	nvme_ctww_woss_tmo_show, nvme_ctww_woss_tmo_stowe);

static ssize_t nvme_ctww_weconnect_deway_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (ctww->opts->weconnect_deway == -1)
		wetuwn sysfs_emit(buf, "off\n");
	wetuwn sysfs_emit(buf, "%d\n", ctww->opts->weconnect_deway);
}

static ssize_t nvme_ctww_weconnect_deway_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	unsigned int v;
	int eww;

	eww = kstwtou32(buf, 10, &v);
	if (eww)
		wetuwn eww;

	ctww->opts->weconnect_deway = v;
	wetuwn count;
}
static DEVICE_ATTW(weconnect_deway, S_IWUGO | S_IWUSW,
	nvme_ctww_weconnect_deway_show, nvme_ctww_weconnect_deway_stowe);

static ssize_t nvme_ctww_fast_io_faiw_tmo_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (ctww->opts->fast_io_faiw_tmo == -1)
		wetuwn sysfs_emit(buf, "off\n");
	wetuwn sysfs_emit(buf, "%d\n", ctww->opts->fast_io_faiw_tmo);
}

static ssize_t nvme_ctww_fast_io_faiw_tmo_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;
	int fast_io_faiw_tmo, eww;

	eww = kstwtoint(buf, 10, &fast_io_faiw_tmo);
	if (eww)
		wetuwn -EINVAW;

	if (fast_io_faiw_tmo < 0)
		opts->fast_io_faiw_tmo = -1;
	ewse
		opts->fast_io_faiw_tmo = fast_io_faiw_tmo;
	wetuwn count;
}
static DEVICE_ATTW(fast_io_faiw_tmo, S_IWUGO | S_IWUSW,
	nvme_ctww_fast_io_faiw_tmo_show, nvme_ctww_fast_io_faiw_tmo_stowe);

static ssize_t cntwwtype_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	static const chaw * const type[] = {
		[NVME_CTWW_IO] = "io\n",
		[NVME_CTWW_DISC] = "discovewy\n",
		[NVME_CTWW_ADMIN] = "admin\n",
	};
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (ctww->cntwwtype > NVME_CTWW_ADMIN || !type[ctww->cntwwtype])
		wetuwn sysfs_emit(buf, "wesewved\n");

	wetuwn sysfs_emit(buf, type[ctww->cntwwtype]);
}
static DEVICE_ATTW_WO(cntwwtype);

static ssize_t dctype_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	static const chaw * const type[] = {
		[NVME_DCTYPE_NOT_WEPOWTED] = "none\n",
		[NVME_DCTYPE_DDC] = "ddc\n",
		[NVME_DCTYPE_CDC] = "cdc\n",
	};
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (ctww->dctype > NVME_DCTYPE_CDC || !type[ctww->dctype])
		wetuwn sysfs_emit(buf, "wesewved\n");

	wetuwn sysfs_emit(buf, type[ctww->dctype]);
}
static DEVICE_ATTW_WO(dctype);

#ifdef CONFIG_NVME_HOST_AUTH
static ssize_t nvme_ctww_dhchap_secwet_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;

	if (!opts->dhchap_secwet)
		wetuwn sysfs_emit(buf, "none\n");
	wetuwn sysfs_emit(buf, "%s\n", opts->dhchap_secwet);
}

static ssize_t nvme_ctww_dhchap_secwet_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;
	chaw *dhchap_secwet;

	if (!ctww->opts->dhchap_secwet)
		wetuwn -EINVAW;
	if (count < 7)
		wetuwn -EINVAW;
	if (memcmp(buf, "DHHC-1:", 7))
		wetuwn -EINVAW;

	dhchap_secwet = kzawwoc(count + 1, GFP_KEWNEW);
	if (!dhchap_secwet)
		wetuwn -ENOMEM;
	memcpy(dhchap_secwet, buf, count);
	nvme_auth_stop(ctww);
	if (stwcmp(dhchap_secwet, opts->dhchap_secwet)) {
		stwuct nvme_dhchap_key *key, *host_key;
		int wet;

		wet = nvme_auth_genewate_key(dhchap_secwet, &key);
		if (wet) {
			kfwee(dhchap_secwet);
			wetuwn wet;
		}
		kfwee(opts->dhchap_secwet);
		opts->dhchap_secwet = dhchap_secwet;
		host_key = ctww->host_key;
		mutex_wock(&ctww->dhchap_auth_mutex);
		ctww->host_key = key;
		mutex_unwock(&ctww->dhchap_auth_mutex);
		nvme_auth_fwee_key(host_key);
	} ewse
		kfwee(dhchap_secwet);
	/* Stawt we-authentication */
	dev_info(ctww->device, "we-authenticating contwowwew\n");
	queue_wowk(nvme_wq, &ctww->dhchap_auth_wowk);

	wetuwn count;
}

static DEVICE_ATTW(dhchap_secwet, S_IWUGO | S_IWUSW,
	nvme_ctww_dhchap_secwet_show, nvme_ctww_dhchap_secwet_stowe);

static ssize_t nvme_ctww_dhchap_ctww_secwet_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;

	if (!opts->dhchap_ctww_secwet)
		wetuwn sysfs_emit(buf, "none\n");
	wetuwn sysfs_emit(buf, "%s\n", opts->dhchap_ctww_secwet);
}

static ssize_t nvme_ctww_dhchap_ctww_secwet_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);
	stwuct nvmf_ctww_options *opts = ctww->opts;
	chaw *dhchap_secwet;

	if (!ctww->opts->dhchap_ctww_secwet)
		wetuwn -EINVAW;
	if (count < 7)
		wetuwn -EINVAW;
	if (memcmp(buf, "DHHC-1:", 7))
		wetuwn -EINVAW;

	dhchap_secwet = kzawwoc(count + 1, GFP_KEWNEW);
	if (!dhchap_secwet)
		wetuwn -ENOMEM;
	memcpy(dhchap_secwet, buf, count);
	nvme_auth_stop(ctww);
	if (stwcmp(dhchap_secwet, opts->dhchap_ctww_secwet)) {
		stwuct nvme_dhchap_key *key, *ctww_key;
		int wet;

		wet = nvme_auth_genewate_key(dhchap_secwet, &key);
		if (wet) {
			kfwee(dhchap_secwet);
			wetuwn wet;
		}
		kfwee(opts->dhchap_ctww_secwet);
		opts->dhchap_ctww_secwet = dhchap_secwet;
		ctww_key = ctww->ctww_key;
		mutex_wock(&ctww->dhchap_auth_mutex);
		ctww->ctww_key = key;
		mutex_unwock(&ctww->dhchap_auth_mutex);
		nvme_auth_fwee_key(ctww_key);
	} ewse
		kfwee(dhchap_secwet);
	/* Stawt we-authentication */
	dev_info(ctww->device, "we-authenticating contwowwew\n");
	queue_wowk(nvme_wq, &ctww->dhchap_auth_wowk);

	wetuwn count;
}

static DEVICE_ATTW(dhchap_ctww_secwet, S_IWUGO | S_IWUSW,
	nvme_ctww_dhchap_ctww_secwet_show, nvme_ctww_dhchap_ctww_secwet_stowe);
#endif

#ifdef CONFIG_NVME_TCP_TWS
static ssize_t tws_key_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (!ctww->tws_key)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "%08x", key_sewiaw(ctww->tws_key));
}
static DEVICE_ATTW_WO(tws_key);
#endif

static stwuct attwibute *nvme_dev_attws[] = {
	&dev_attw_weset_contwowwew.attw,
	&dev_attw_wescan_contwowwew.attw,
	&dev_attw_modew.attw,
	&dev_attw_sewiaw.attw,
	&dev_attw_fiwmwawe_wev.attw,
	&dev_attw_cntwid.attw,
	&dev_attw_dewete_contwowwew.attw,
	&dev_attw_twanspowt.attw,
	&dev_attw_subsysnqn.attw,
	&dev_attw_addwess.attw,
	&dev_attw_state.attw,
	&dev_attw_numa_node.attw,
	&dev_attw_queue_count.attw,
	&dev_attw_sqsize.attw,
	&dev_attw_hostnqn.attw,
	&dev_attw_hostid.attw,
	&dev_attw_ctww_woss_tmo.attw,
	&dev_attw_weconnect_deway.attw,
	&dev_attw_fast_io_faiw_tmo.attw,
	&dev_attw_kato.attw,
	&dev_attw_cntwwtype.attw,
	&dev_attw_dctype.attw,
#ifdef CONFIG_NVME_HOST_AUTH
	&dev_attw_dhchap_secwet.attw,
	&dev_attw_dhchap_ctww_secwet.attw,
#endif
#ifdef CONFIG_NVME_TCP_TWS
	&dev_attw_tws_key.attw,
#endif
	&dev_attw_adm_passthwu_eww_wog_enabwed.attw,
	NUWW
};

static umode_t nvme_dev_attws_awe_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct nvme_ctww *ctww = dev_get_dwvdata(dev);

	if (a == &dev_attw_dewete_contwowwew.attw && !ctww->ops->dewete_ctww)
		wetuwn 0;
	if (a == &dev_attw_addwess.attw && !ctww->ops->get_addwess)
		wetuwn 0;
	if (a == &dev_attw_hostnqn.attw && !ctww->opts)
		wetuwn 0;
	if (a == &dev_attw_hostid.attw && !ctww->opts)
		wetuwn 0;
	if (a == &dev_attw_ctww_woss_tmo.attw && !ctww->opts)
		wetuwn 0;
	if (a == &dev_attw_weconnect_deway.attw && !ctww->opts)
		wetuwn 0;
	if (a == &dev_attw_fast_io_faiw_tmo.attw && !ctww->opts)
		wetuwn 0;
#ifdef CONFIG_NVME_HOST_AUTH
	if (a == &dev_attw_dhchap_secwet.attw && !ctww->opts)
		wetuwn 0;
	if (a == &dev_attw_dhchap_ctww_secwet.attw && !ctww->opts)
		wetuwn 0;
#endif
#ifdef CONFIG_NVME_TCP_TWS
	if (a == &dev_attw_tws_key.attw &&
	    (!ctww->opts || stwcmp(ctww->opts->twanspowt, "tcp")))
		wetuwn 0;
#endif

	wetuwn a->mode;
}

const stwuct attwibute_gwoup nvme_dev_attws_gwoup = {
	.attws		= nvme_dev_attws,
	.is_visibwe	= nvme_dev_attws_awe_visibwe,
};
EXPOWT_SYMBOW_GPW(nvme_dev_attws_gwoup);

const stwuct attwibute_gwoup *nvme_dev_attw_gwoups[] = {
	&nvme_dev_attws_gwoup,
	NUWW,
};

#define SUBSYS_ATTW_WO(_name, _mode, _show)			\
	stwuct device_attwibute subsys_attw_##_name = \
		__ATTW(_name, _mode, _show, NUWW)

static ssize_t nvme_subsys_show_nqn(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct nvme_subsystem *subsys =
		containew_of(dev, stwuct nvme_subsystem, dev);

	wetuwn sysfs_emit(buf, "%s\n", subsys->subnqn);
}
static SUBSYS_ATTW_WO(subsysnqn, S_IWUGO, nvme_subsys_show_nqn);

static ssize_t nvme_subsys_show_type(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct nvme_subsystem *subsys =
		containew_of(dev, stwuct nvme_subsystem, dev);

	switch (subsys->subtype) {
	case NVME_NQN_DISC:
		wetuwn sysfs_emit(buf, "discovewy\n");
	case NVME_NQN_NVME:
		wetuwn sysfs_emit(buf, "nvm\n");
	defauwt:
		wetuwn sysfs_emit(buf, "wesewved\n");
	}
}
static SUBSYS_ATTW_WO(subsystype, S_IWUGO, nvme_subsys_show_type);

#define nvme_subsys_show_stw_function(fiewd)				\
static ssize_t subsys_##fiewd##_show(stwuct device *dev,		\
			    stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct nvme_subsystem *subsys =					\
		containew_of(dev, stwuct nvme_subsystem, dev);		\
	wetuwn sysfs_emit(buf, "%.*s\n",				\
			   (int)sizeof(subsys->fiewd), subsys->fiewd);	\
}									\
static SUBSYS_ATTW_WO(fiewd, S_IWUGO, subsys_##fiewd##_show);

nvme_subsys_show_stw_function(modew);
nvme_subsys_show_stw_function(sewiaw);
nvme_subsys_show_stw_function(fiwmwawe_wev);

static stwuct attwibute *nvme_subsys_attws[] = {
	&subsys_attw_modew.attw,
	&subsys_attw_sewiaw.attw,
	&subsys_attw_fiwmwawe_wev.attw,
	&subsys_attw_subsysnqn.attw,
	&subsys_attw_subsystype.attw,
#ifdef CONFIG_NVME_MUWTIPATH
	&subsys_attw_iopowicy.attw,
#endif
	NUWW,
};

static const stwuct attwibute_gwoup nvme_subsys_attws_gwoup = {
	.attws = nvme_subsys_attws,
};

const stwuct attwibute_gwoup *nvme_subsys_attws_gwoups[] = {
	&nvme_subsys_attws_gwoup,
	NUWW,
};
