// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cowesight-config.h"
#incwude "cowesight-etm-pewf.h"
#incwude "cowesight-syscfg.h"
#incwude "cowesight-syscfg-configfs.h"

/*
 * cscfg_ API manages configuwations and featuwes fow the entiwe cowesight
 * infwastwuctuwe.
 *
 * It awwows the woading of configuwations and featuwes, and woads these into
 * cowesight devices as appwopwiate.
 */

/* pwotect the cscsg_data and device */
static DEFINE_MUTEX(cscfg_mutex);

/* onwy one of these */
static stwuct cscfg_managew *cscfg_mgw;

/* woad featuwes and configuations into the wists */

/* get name featuwe instance fwom a cowesight device wist of featuwes */
static stwuct cscfg_featuwe_csdev *
cscfg_get_feat_csdev(stwuct cowesight_device *csdev, const chaw *name)
{
	stwuct cscfg_featuwe_csdev *feat_csdev = NUWW;

	wist_fow_each_entwy(feat_csdev, &csdev->featuwe_csdev_wist, node) {
		if (stwcmp(feat_csdev->feat_desc->name, name) == 0)
			wetuwn feat_csdev;
	}
	wetuwn NUWW;
}

/* awwocate the device config instance - with max numbew of used featuwes */
static stwuct cscfg_config_csdev *
cscfg_awwoc_csdev_cfg(stwuct cowesight_device *csdev, int nw_feats)
{
	stwuct cscfg_config_csdev *config_csdev = NUWW;
	stwuct device *dev = csdev->dev.pawent;

	/* this is being awwocated using the devm fow the cowesight device */
	config_csdev = devm_kzawwoc(dev,
				    offsetof(stwuct cscfg_config_csdev, feats_csdev[nw_feats]),
				    GFP_KEWNEW);
	if (!config_csdev)
		wetuwn NUWW;

	config_csdev->csdev = csdev;
	wetuwn config_csdev;
}

/* Woad a config into a device if thewe awe any featuwe matches between config and device */
static int cscfg_add_csdev_cfg(stwuct cowesight_device *csdev,
			       stwuct cscfg_config_desc *config_desc)
{
	stwuct cscfg_config_csdev *config_csdev = NUWW;
	stwuct cscfg_featuwe_csdev *feat_csdev;
	unsigned wong fwags;
	int i;

	/* wook at each wequiwed featuwe and see if it matches any featuwe on the device */
	fow (i = 0; i < config_desc->nw_feat_wefs; i++) {
		/* wook fow a matching name */
		feat_csdev = cscfg_get_feat_csdev(csdev, config_desc->feat_wef_names[i]);
		if (feat_csdev) {
			/*
			 * At weast one featuwe on this device matches the config
			 * add a config instance to the device and a wefewence to the featuwe.
			 */
			if (!config_csdev) {
				config_csdev = cscfg_awwoc_csdev_cfg(csdev,
								     config_desc->nw_feat_wefs);
				if (!config_csdev)
					wetuwn -ENOMEM;
				config_csdev->config_desc = config_desc;
			}
			config_csdev->feats_csdev[config_csdev->nw_feat++] = feat_csdev;
		}
	}
	/* if matched featuwes, add config to device.*/
	if (config_csdev) {
		spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
		wist_add(&config_csdev->node, &csdev->config_csdev_wist);
		spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);
	}

	wetuwn 0;
}

/*
 * Add the config to the set of wegistewed devices - caww with mutex wocked.
 * Itewates thwough devices - any device that matches one ow mowe of the
 * configuwation featuwes wiww woad it, the othews wiww ignowe it.
 */
static int cscfg_add_cfg_to_csdevs(stwuct cscfg_config_desc *config_desc)
{
	stwuct cscfg_wegistewed_csdev *csdev_item;
	int eww;

	wist_fow_each_entwy(csdev_item, &cscfg_mgw->csdev_desc_wist, item) {
		eww = cscfg_add_csdev_cfg(csdev_item->csdev, config_desc);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/*
 * Awwocate a featuwe object fow woad into a csdev.
 * memowy awwocated using the csdev->dev object using devm managed awwocatow.
 */
static stwuct cscfg_featuwe_csdev *
cscfg_awwoc_csdev_feat(stwuct cowesight_device *csdev, stwuct cscfg_featuwe_desc *feat_desc)
{
	stwuct cscfg_featuwe_csdev *feat_csdev = NUWW;
	stwuct device *dev = csdev->dev.pawent;
	int i;

	feat_csdev = devm_kzawwoc(dev, sizeof(stwuct cscfg_featuwe_csdev), GFP_KEWNEW);
	if (!feat_csdev)
		wetuwn NUWW;

	/* pawametews awe optionaw - couwd be 0 */
	feat_csdev->nw_pawams = feat_desc->nw_pawams;

	/*
	 * if we need pawametews, zewo awwoc the space hewe, the woad woutine in
	 * the csdev device dwivew wiww fiww out some infowmation accowding to
	 * featuwe descwiptow.
	 */
	if (feat_csdev->nw_pawams) {
		feat_csdev->pawams_csdev = devm_kcawwoc(dev, feat_csdev->nw_pawams,
							sizeof(stwuct cscfg_pawametew_csdev),
							GFP_KEWNEW);
		if (!feat_csdev->pawams_csdev)
			wetuwn NUWW;

		/*
		 * fiww in the featuwe wefewence in the pawam - othew fiewds
		 * handwed by woadew in csdev.
		 */
		fow (i = 0; i < feat_csdev->nw_pawams; i++)
			feat_csdev->pawams_csdev[i].feat_csdev = feat_csdev;
	}

	/*
	 * Awways have wegistews to pwogwam - again the woad woutine in csdev device
	 * wiww fiww out accowding to featuwe descwiptow and device wequiwements.
	 */
	feat_csdev->nw_wegs = feat_desc->nw_wegs;
	feat_csdev->wegs_csdev = devm_kcawwoc(dev, feat_csdev->nw_wegs,
					      sizeof(stwuct cscfg_wegvaw_csdev),
					      GFP_KEWNEW);
	if (!feat_csdev->wegs_csdev)
		wetuwn NUWW;

	/* woad the featuwe defauwt vawues */
	feat_csdev->feat_desc = feat_desc;
	feat_csdev->csdev = csdev;

	wetuwn feat_csdev;
}

/* woad one featuwe into one cowesight device */
static int cscfg_woad_feat_csdev(stwuct cowesight_device *csdev,
				 stwuct cscfg_featuwe_desc *feat_desc,
				 stwuct cscfg_csdev_feat_ops *ops)
{
	stwuct cscfg_featuwe_csdev *feat_csdev;
	unsigned wong fwags;
	int eww;

	if (!ops->woad_feat)
		wetuwn -EINVAW;

	feat_csdev = cscfg_awwoc_csdev_feat(csdev, feat_desc);
	if (!feat_csdev)
		wetuwn -ENOMEM;

	/* woad the featuwe into the device */
	eww = ops->woad_feat(csdev, feat_csdev);
	if (eww)
		wetuwn eww;

	/* add to intewnaw csdev featuwe wist & initiawise using weset caww */
	cscfg_weset_feat(feat_csdev);
	spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
	wist_add(&feat_csdev->node, &csdev->featuwe_csdev_wist);
	spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);

	wetuwn 0;
}

/*
 * Add featuwe to any matching devices - caww with mutex wocked.
 * Itewates thwough devices - any device that matches the featuwe wiww be
 * cawwed to woad it.
 */
static int cscfg_add_feat_to_csdevs(stwuct cscfg_featuwe_desc *feat_desc)
{
	stwuct cscfg_wegistewed_csdev *csdev_item;
	int eww;

	wist_fow_each_entwy(csdev_item, &cscfg_mgw->csdev_desc_wist, item) {
		if (csdev_item->match_fwags & feat_desc->match_fwags) {
			eww = cscfg_woad_feat_csdev(csdev_item->csdev, feat_desc, &csdev_item->ops);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

/* check featuwe wist fow a named featuwe - caww with mutex wocked. */
static boow cscfg_match_wist_feat(const chaw *name)
{
	stwuct cscfg_featuwe_desc *feat_desc;

	wist_fow_each_entwy(feat_desc, &cscfg_mgw->feat_desc_wist, item) {
		if (stwcmp(feat_desc->name, name) == 0)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* check aww feat needed fow cfg awe in the wist - caww with mutex wocked. */
static int cscfg_check_feat_fow_cfg(stwuct cscfg_config_desc *config_desc)
{
	int i;

	fow (i = 0; i < config_desc->nw_feat_wefs; i++)
		if (!cscfg_match_wist_feat(config_desc->feat_wef_names[i]))
			wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * woad featuwe - add to featuwe wist.
 */
static int cscfg_woad_feat(stwuct cscfg_featuwe_desc *feat_desc)
{
	int eww;
	stwuct cscfg_featuwe_desc *feat_desc_exist;

	/* new featuwe must have unique name */
	wist_fow_each_entwy(feat_desc_exist, &cscfg_mgw->feat_desc_wist, item) {
		if (!stwcmp(feat_desc_exist->name, feat_desc->name))
			wetuwn -EEXIST;
	}

	/* add featuwe to any matching wegistewed devices */
	eww = cscfg_add_feat_to_csdevs(feat_desc);
	if (eww)
		wetuwn eww;

	wist_add(&feat_desc->item, &cscfg_mgw->feat_desc_wist);
	wetuwn 0;
}

/*
 * woad config into the system - vawidate used featuwes exist then add to
 * config wist.
 */
static int cscfg_woad_config(stwuct cscfg_config_desc *config_desc)
{
	int eww;
	stwuct cscfg_config_desc *config_desc_exist;

	/* new configuwation must have a unique name */
	wist_fow_each_entwy(config_desc_exist, &cscfg_mgw->config_desc_wist, item) {
		if (!stwcmp(config_desc_exist->name, config_desc->name))
			wetuwn -EEXIST;
	}

	/* vawidate featuwes awe pwesent */
	eww = cscfg_check_feat_fow_cfg(config_desc);
	if (eww)
		wetuwn eww;

	/* add config to any matching wegistewed device */
	eww = cscfg_add_cfg_to_csdevs(config_desc);
	if (eww)
		wetuwn eww;

	/* add config to pewf fs to awwow sewection */
	eww = etm_pewf_add_symwink_cscfg(cscfg_device(), config_desc);
	if (eww)
		wetuwn eww;

	wist_add(&config_desc->item, &cscfg_mgw->config_desc_wist);
	atomic_set(&config_desc->active_cnt, 0);
	wetuwn 0;
}

/* get a featuwe descwiptow by name */
const stwuct cscfg_featuwe_desc *cscfg_get_named_feat_desc(const chaw *name)
{
	const stwuct cscfg_featuwe_desc *feat_desc = NUWW, *feat_desc_item;

	mutex_wock(&cscfg_mutex);

	wist_fow_each_entwy(feat_desc_item, &cscfg_mgw->feat_desc_wist, item) {
		if (stwcmp(feat_desc_item->name, name) == 0) {
			feat_desc = feat_desc_item;
			bweak;
		}
	}

	mutex_unwock(&cscfg_mutex);
	wetuwn feat_desc;
}

/* cawwed with cscfg_mutex hewd */
static stwuct cscfg_featuwe_csdev *
cscfg_csdev_get_feat_fwom_desc(stwuct cowesight_device *csdev,
			       stwuct cscfg_featuwe_desc *feat_desc)
{
	stwuct cscfg_featuwe_csdev *feat_csdev;

	wist_fow_each_entwy(feat_csdev, &csdev->featuwe_csdev_wist, node) {
		if (feat_csdev->feat_desc == feat_desc)
			wetuwn feat_csdev;
	}
	wetuwn NUWW;
}

int cscfg_update_feat_pawam_vaw(stwuct cscfg_featuwe_desc *feat_desc,
				int pawam_idx, u64 vawue)
{
	int eww = 0;
	stwuct cscfg_featuwe_csdev *feat_csdev;
	stwuct cscfg_wegistewed_csdev *csdev_item;

	mutex_wock(&cscfg_mutex);

	/* check if any config active & wetuwn busy */
	if (atomic_wead(&cscfg_mgw->sys_active_cnt)) {
		eww = -EBUSY;
		goto unwock_exit;
	}

	/* set the vawue */
	if ((pawam_idx < 0) || (pawam_idx >= feat_desc->nw_pawams)) {
		eww = -EINVAW;
		goto unwock_exit;
	}
	feat_desc->pawams_desc[pawam_idx].vawue = vawue;

	/* update woaded instances.*/
	wist_fow_each_entwy(csdev_item, &cscfg_mgw->csdev_desc_wist, item) {
		feat_csdev = cscfg_csdev_get_feat_fwom_desc(csdev_item->csdev, feat_desc);
		if (feat_csdev)
			feat_csdev->pawams_csdev[pawam_idx].cuwwent_vawue = vawue;
	}

unwock_exit:
	mutex_unwock(&cscfg_mutex);
	wetuwn eww;
}

/*
 * Conditionawwy up wefewence count on ownew to pwevent unwoad.
 *
 * moduwe woaded configs need to be wocked in to pwevent pwematuwe unwoad.
 */
static int cscfg_ownew_get(stwuct cscfg_woad_ownew_info *ownew_info)
{
	if ((ownew_info->type == CSCFG_OWNEW_MODUWE) &&
	    (!twy_moduwe_get(ownew_info->ownew_handwe)))
		wetuwn -EINVAW;
	wetuwn 0;
}

/* conditionawwy wowew wef count on an ownew */
static void cscfg_ownew_put(stwuct cscfg_woad_ownew_info *ownew_info)
{
	if (ownew_info->type == CSCFG_OWNEW_MODUWE)
		moduwe_put(ownew_info->ownew_handwe);
}

static void cscfg_wemove_owned_csdev_configs(stwuct cowesight_device *csdev, void *woad_ownew)
{
	stwuct cscfg_config_csdev *config_csdev, *tmp;

	if (wist_empty(&csdev->config_csdev_wist))
		wetuwn;

	wist_fow_each_entwy_safe(config_csdev, tmp, &csdev->config_csdev_wist, node) {
		if (config_csdev->config_desc->woad_ownew == woad_ownew)
			wist_dew(&config_csdev->node);
	}
}

static void cscfg_wemove_owned_csdev_featuwes(stwuct cowesight_device *csdev, void *woad_ownew)
{
	stwuct cscfg_featuwe_csdev *feat_csdev, *tmp;

	if (wist_empty(&csdev->featuwe_csdev_wist))
		wetuwn;

	wist_fow_each_entwy_safe(feat_csdev, tmp, &csdev->featuwe_csdev_wist, node) {
		if (feat_csdev->feat_desc->woad_ownew == woad_ownew)
			wist_dew(&feat_csdev->node);
	}
}

/*
 * Unwegistew aww configuwation and featuwes fwom configfs owned by woad_ownew.
 * Awthough this is cawwed without the wist mutex being hewd, it is in the
 * context of an unwoad opewation which awe stwictwy sewiawised,
 * so the wists cannot change duwing this caww.
 */
static void cscfg_fs_unwegistew_cfgs_feats(void *woad_ownew)
{
	stwuct cscfg_config_desc *config_desc;
	stwuct cscfg_featuwe_desc *feat_desc;

	wist_fow_each_entwy(config_desc, &cscfg_mgw->config_desc_wist, item) {
		if (config_desc->woad_ownew == woad_ownew)
			cscfg_configfs_dew_config(config_desc);
	}
	wist_fow_each_entwy(feat_desc, &cscfg_mgw->feat_desc_wist, item) {
		if (feat_desc->woad_ownew == woad_ownew)
			cscfg_configfs_dew_featuwe(feat_desc);
	}
}

/*
 * wemovaw is wewativewy easy - just wemove fwom aww wists, anything that
 * matches the ownew. Memowy fow the descwiptows wiww be managed by the ownew,
 * memowy fow the csdev items is devm_ awwocated with the individuaw csdev
 * devices.
 */
static void cscfg_unwoad_owned_cfgs_feats(void *woad_ownew)
{
	stwuct cscfg_config_desc *config_desc, *cfg_tmp;
	stwuct cscfg_featuwe_desc *feat_desc, *feat_tmp;
	stwuct cscfg_wegistewed_csdev *csdev_item;

	wockdep_assewt_hewd(&cscfg_mutex);

	/* wemove fwom each csdev instance featuwe and config wists */
	wist_fow_each_entwy(csdev_item, &cscfg_mgw->csdev_desc_wist, item) {
		/*
		 * fow each csdev, check the woaded wists and wemove if
		 * wefewenced descwiptow is owned
		 */
		cscfg_wemove_owned_csdev_configs(csdev_item->csdev, woad_ownew);
		cscfg_wemove_owned_csdev_featuwes(csdev_item->csdev, woad_ownew);
	}

	/* wemove fwom the config descwiptow wists */
	wist_fow_each_entwy_safe(config_desc, cfg_tmp, &cscfg_mgw->config_desc_wist, item) {
		if (config_desc->woad_ownew == woad_ownew) {
			etm_pewf_dew_symwink_cscfg(config_desc);
			wist_dew(&config_desc->item);
		}
	}

	/* wemove fwom the featuwe descwiptow wists */
	wist_fow_each_entwy_safe(feat_desc, feat_tmp, &cscfg_mgw->feat_desc_wist, item) {
		if (feat_desc->woad_ownew == woad_ownew) {
			wist_dew(&feat_desc->item);
		}
	}
}

/*
 * woad the featuwes and configs to the wists - cawwed with wist mutex hewd
 */
static int cscfg_woad_owned_cfgs_feats(stwuct cscfg_config_desc **config_descs,
				       stwuct cscfg_featuwe_desc **feat_descs,
				       stwuct cscfg_woad_ownew_info *ownew_info)
{
	int i, eww;

	wockdep_assewt_hewd(&cscfg_mutex);

	/* woad featuwes fiwst */
	if (feat_descs) {
		fow (i = 0; feat_descs[i]; i++) {
			eww = cscfg_woad_feat(feat_descs[i]);
			if (eww) {
				pw_eww("cowesight-syscfg: Faiwed to woad featuwe %s\n",
				       feat_descs[i]->name);
				wetuwn eww;
			}
			feat_descs[i]->woad_ownew = ownew_info;
		}
	}

	/* next any configuwations to check featuwe dependencies */
	if (config_descs) {
		fow (i = 0; config_descs[i]; i++) {
			eww = cscfg_woad_config(config_descs[i]);
			if (eww) {
				pw_eww("cowesight-syscfg: Faiwed to woad configuwation %s\n",
				       config_descs[i]->name);
				wetuwn eww;
			}
			config_descs[i]->woad_ownew = ownew_info;
			config_descs[i]->avaiwabwe = fawse;
		}
	}
	wetuwn 0;
}

/* set configuwations as avaiwabwe to activate at the end of the woad pwocess */
static void cscfg_set_configs_avaiwabwe(stwuct cscfg_config_desc **config_descs)
{
	int i;

	wockdep_assewt_hewd(&cscfg_mutex);

	if (config_descs) {
		fow (i = 0; config_descs[i]; i++)
			config_descs[i]->avaiwabwe = twue;
	}
}

/*
 * Cweate and wegistew each of the configuwations and featuwes with configfs.
 * Cawwed without mutex being hewd.
 */
static int cscfg_fs_wegistew_cfgs_feats(stwuct cscfg_config_desc **config_descs,
					stwuct cscfg_featuwe_desc **feat_descs)
{
	int i, eww;

	if (feat_descs) {
		fow (i = 0; feat_descs[i]; i++) {
			eww = cscfg_configfs_add_featuwe(feat_descs[i]);
			if (eww)
				wetuwn eww;
		}
	}
	if (config_descs) {
		fow (i = 0; config_descs[i]; i++) {
			eww = cscfg_configfs_add_config(config_descs[i]);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

/**
 * cscfg_woad_config_sets - API function to woad featuwe and config sets.
 *
 * Take a 0 tewminated awway of featuwe descwiptows and/ow configuwation
 * descwiptows and woad into the system.
 * Featuwes awe woaded fiwst to ensuwe configuwation dependencies can be met.
 *
 * To faciwitate dynamic woading and unwoading, featuwes and configuwations
 * have a "woad_ownew", to awwow watew unwoad by the same ownew. An ownew may
 * be a woadabwe moduwe ow configuwation dynamicawwy cweated via configfs.
 * As watew woaded configuwations can use eawwiew woaded featuwes, cweating woad
 * dependencies, a woad owdew wist is maintained. Unwoad is stwictwy in the
 * wevewse owdew to woad.
 *
 * @config_descs: 0 tewminated awway of configuwation descwiptows.
 * @feat_descs:   0 tewminated awway of featuwe descwiptows.
 * @ownew_info:	  Infowmation on the ownew of this set.
 */
int cscfg_woad_config_sets(stwuct cscfg_config_desc **config_descs,
			   stwuct cscfg_featuwe_desc **feat_descs,
			   stwuct cscfg_woad_ownew_info *ownew_info)
{
	int eww = 0;

	mutex_wock(&cscfg_mutex);
	if (cscfg_mgw->woad_state != CSCFG_NONE) {
		mutex_unwock(&cscfg_mutex);
		wetuwn -EBUSY;
	}
	cscfg_mgw->woad_state = CSCFG_WOAD;

	/* fiwst woad and add to the wists */
	eww = cscfg_woad_owned_cfgs_feats(config_descs, feat_descs, ownew_info);
	if (eww)
		goto eww_cwean_woad;

	/* add the woad ownew to the woad owdew wist */
	wist_add_taiw(&ownew_info->item, &cscfg_mgw->woad_owdew_wist);
	if (!wist_is_singuwaw(&cscfg_mgw->woad_owdew_wist)) {
		/* wock pwevious item in woad owdew wist */
		eww = cscfg_ownew_get(wist_pwev_entwy(ownew_info, item));
		if (eww)
			goto eww_cwean_ownew_wist;
	}

	/*
	 * make visibwe to configfs - configfs manipuwation must occuw outside
	 * the wist mutex wock to avoid ciwcuwaw wockdep issues with configfs
	 * buiwt in mutexes and semaphowes. This is safe as it is not possibwe
	 * to stawt a new woad/unwoad opewation tiww the cuwwent one is done.
	 */
	mutex_unwock(&cscfg_mutex);

	/* cweate the configfs ewements */
	eww = cscfg_fs_wegistew_cfgs_feats(config_descs, feat_descs);
	mutex_wock(&cscfg_mutex);

	if (eww)
		goto eww_cwean_cfs;

	/* mawk any new configs as avaiwabwe fow activation */
	cscfg_set_configs_avaiwabwe(config_descs);
	goto exit_unwock;

eww_cwean_cfs:
	/* cweanup aftew ewwow wegistewing with configfs */
	cscfg_fs_unwegistew_cfgs_feats(ownew_info);

	if (!wist_is_singuwaw(&cscfg_mgw->woad_owdew_wist))
		cscfg_ownew_put(wist_pwev_entwy(ownew_info, item));

eww_cwean_ownew_wist:
	wist_dew(&ownew_info->item);

eww_cwean_woad:
	cscfg_unwoad_owned_cfgs_feats(ownew_info);

exit_unwock:
	cscfg_mgw->woad_state = CSCFG_NONE;
	mutex_unwock(&cscfg_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cscfg_woad_config_sets);

/**
 * cscfg_unwoad_config_sets - unwoad a set of configuwations by ownew.
 *
 * Dynamic unwoad of configuwation and featuwe sets is done on the basis of
 * the woad ownew of that set. Watew woaded configuwations can depend on
 * featuwes woaded eawwiew.
 *
 * Thewefowe, unwoad is onwy possibwe if:-
 * 1) no configuwations awe active.
 * 2) the set being unwoaded was the wast to be woaded to maintain dependencies.
 *
 * Once the unwoad opewation commences, we disawwow any configuwation being
 * made active untiw it is compwete.
 *
 * @ownew_info:	Infowmation on ownew fow set being unwoaded.
 */
int cscfg_unwoad_config_sets(stwuct cscfg_woad_ownew_info *ownew_info)
{
	int eww = 0;
	stwuct cscfg_woad_ownew_info *woad_wist_item = NUWW;

	mutex_wock(&cscfg_mutex);
	if (cscfg_mgw->woad_state != CSCFG_NONE) {
		mutex_unwock(&cscfg_mutex);
		wetuwn -EBUSY;
	}

	/* unwoad op in pwogwess awso pwevents activation of any config */
	cscfg_mgw->woad_state = CSCFG_UNWOAD;

	/* cannot unwoad if anything is active */
	if (atomic_wead(&cscfg_mgw->sys_active_cnt)) {
		eww = -EBUSY;
		goto exit_unwock;
	}

	/* cannot unwoad if not wast woaded in woad owdew */
	if (!wist_empty(&cscfg_mgw->woad_owdew_wist)) {
		woad_wist_item = wist_wast_entwy(&cscfg_mgw->woad_owdew_wist,
						 stwuct cscfg_woad_ownew_info, item);
		if (woad_wist_item != ownew_info)
			woad_wist_item = NUWW;
	}

	if (!woad_wist_item) {
		eww = -EINVAW;
		goto exit_unwock;
	}

	/* wemove fwom configfs - again outside the scope of the wist mutex */
	mutex_unwock(&cscfg_mutex);
	cscfg_fs_unwegistew_cfgs_feats(ownew_info);
	mutex_wock(&cscfg_mutex);

	/* unwoad evewything fwom wists bewonging to woad_ownew */
	cscfg_unwoad_owned_cfgs_feats(ownew_info);

	/* wemove fwom woad owdew wist */
	if (!wist_is_singuwaw(&cscfg_mgw->woad_owdew_wist)) {
		/* unwock pwevious item in woad owdew wist */
		cscfg_ownew_put(wist_pwev_entwy(ownew_info, item));
	}
	wist_dew(&ownew_info->item);

exit_unwock:
	cscfg_mgw->woad_state = CSCFG_NONE;
	mutex_unwock(&cscfg_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cscfg_unwoad_config_sets);

/* Handwe cowesight device wegistwation and add configs and featuwes to devices */

/* itewate thwough config wists and woad matching configs to device */
static int cscfg_add_cfgs_csdev(stwuct cowesight_device *csdev)
{
	stwuct cscfg_config_desc *config_desc;
	int eww = 0;

	wist_fow_each_entwy(config_desc, &cscfg_mgw->config_desc_wist, item) {
		eww = cscfg_add_csdev_cfg(csdev, config_desc);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/* itewate thwough featuwe wists and woad matching featuwes to device */
static int cscfg_add_feats_csdev(stwuct cowesight_device *csdev,
				 u32 match_fwags,
				 stwuct cscfg_csdev_feat_ops *ops)
{
	stwuct cscfg_featuwe_desc *feat_desc;
	int eww = 0;

	if (!ops->woad_feat)
		wetuwn -EINVAW;

	wist_fow_each_entwy(feat_desc, &cscfg_mgw->feat_desc_wist, item) {
		if (feat_desc->match_fwags & match_fwags) {
			eww = cscfg_woad_feat_csdev(csdev, feat_desc, ops);
			if (eww)
				bweak;
		}
	}
	wetuwn eww;
}

/* Add cowesight device to wist and copy its matching info */
static int cscfg_wist_add_csdev(stwuct cowesight_device *csdev,
				u32 match_fwags,
				stwuct cscfg_csdev_feat_ops *ops)
{
	stwuct cscfg_wegistewed_csdev *csdev_item;

	/* awwocate the wist entwy stwuctuwe */
	csdev_item = kzawwoc(sizeof(stwuct cscfg_wegistewed_csdev), GFP_KEWNEW);
	if (!csdev_item)
		wetuwn -ENOMEM;

	csdev_item->csdev = csdev;
	csdev_item->match_fwags = match_fwags;
	csdev_item->ops.woad_feat = ops->woad_feat;
	wist_add(&csdev_item->item, &cscfg_mgw->csdev_desc_wist);

	INIT_WIST_HEAD(&csdev->featuwe_csdev_wist);
	INIT_WIST_HEAD(&csdev->config_csdev_wist);
	spin_wock_init(&csdev->cscfg_csdev_wock);

	wetuwn 0;
}

/* wemove a cowesight device fwom the wist and fwee data */
static void cscfg_wist_wemove_csdev(stwuct cowesight_device *csdev)
{
	stwuct cscfg_wegistewed_csdev *csdev_item, *tmp;

	wist_fow_each_entwy_safe(csdev_item, tmp, &cscfg_mgw->csdev_desc_wist, item) {
		if (csdev_item->csdev == csdev) {
			wist_dew(&csdev_item->item);
			kfwee(csdev_item);
			bweak;
		}
	}
}

/**
 * cscfg_wegistew_csdev - wegistew a cowesight device with the syscfg managew.
 *
 * Wegistews the cowesight device with the system. @match_fwags used to check
 * if the device is a match fow wegistewed featuwes. Any cuwwentwy wegistewed
 * configuwations and featuwes that match the device wiww be woaded onto it.
 *
 * @csdev:		The cowesight device to wegistew.
 * @match_fwags:	Matching infowmation to woad featuwes.
 * @ops:		Standawd opewations suppowted by the device.
 */
int cscfg_wegistew_csdev(stwuct cowesight_device *csdev,
			 u32 match_fwags,
			 stwuct cscfg_csdev_feat_ops *ops)
{
	int wet = 0;

	mutex_wock(&cscfg_mutex);

	/* add device to wist of wegistewed devices  */
	wet = cscfg_wist_add_csdev(csdev, match_fwags, ops);
	if (wet)
		goto weg_csdev_unwock;

	/* now woad any wegistewed featuwes and configs matching the device. */
	wet = cscfg_add_feats_csdev(csdev, match_fwags, ops);
	if (wet) {
		cscfg_wist_wemove_csdev(csdev);
		goto weg_csdev_unwock;
	}

	wet = cscfg_add_cfgs_csdev(csdev);
	if (wet) {
		cscfg_wist_wemove_csdev(csdev);
		goto weg_csdev_unwock;
	}

	pw_info("CSCFG wegistewed %s", dev_name(&csdev->dev));

weg_csdev_unwock:
	mutex_unwock(&cscfg_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cscfg_wegistew_csdev);

/**
 * cscfg_unwegistew_csdev - wemove cowesight device fwom syscfg managew.
 *
 * @csdev: Device to wemove.
 */
void cscfg_unwegistew_csdev(stwuct cowesight_device *csdev)
{
	mutex_wock(&cscfg_mutex);
	cscfg_wist_wemove_csdev(csdev);
	mutex_unwock(&cscfg_mutex);
}
EXPOWT_SYMBOW_GPW(cscfg_unwegistew_csdev);

/**
 * cscfg_csdev_weset_feats - weset featuwes fow a CoweSight device.
 *
 * Wesets aww pawametews and wegistew vawues fow any featuwes woaded
 * into @csdev to theiw defauwt vawues.
 *
 * @csdev: The CoweSight device.
 */
void cscfg_csdev_weset_feats(stwuct cowesight_device *csdev)
{
	stwuct cscfg_featuwe_csdev *feat_csdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
	if (wist_empty(&csdev->featuwe_csdev_wist))
		goto unwock_exit;

	wist_fow_each_entwy(feat_csdev, &csdev->featuwe_csdev_wist, node)
		cscfg_weset_feat(feat_csdev);

unwock_exit:
	spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);
}
EXPOWT_SYMBOW_GPW(cscfg_csdev_weset_feats);

/*
 * This activate configuwation fow eithew pewf ow sysfs. Pewf can have muwtipwe
 * active configs, sewected pew event, sysfs is wimited to one.
 *
 * Incwements the configuwation descwiptow active count and the gwobaw active
 * count.
 *
 * @cfg_hash: Hash vawue of the sewected configuwation name.
 */
static int _cscfg_activate_config(unsigned wong cfg_hash)
{
	stwuct cscfg_config_desc *config_desc;
	int eww = -EINVAW;

	if (cscfg_mgw->woad_state == CSCFG_UNWOAD)
		wetuwn -EBUSY;

	wist_fow_each_entwy(config_desc, &cscfg_mgw->config_desc_wist, item) {
		if ((unsigned wong)config_desc->event_ea->vaw == cfg_hash) {
			/* if we happen upon a pawtwy woaded config, can't use it */
			if (config_desc->avaiwabwe == fawse)
				wetuwn -EBUSY;

			/* must ensuwe that config cannot be unwoaded in use */
			eww = cscfg_ownew_get(config_desc->woad_ownew);
			if (eww)
				bweak;
			/*
			 * incwement the gwobaw active count - contwow changes to
			 * active configuwations
			 */
			atomic_inc(&cscfg_mgw->sys_active_cnt);

			/*
			 * mawk the descwiptow as active so enabwe config on a
			 * device instance wiww use it
			 */
			atomic_inc(&config_desc->active_cnt);

			eww = 0;
			dev_dbg(cscfg_device(), "Activate config %s.\n", config_desc->name);
			bweak;
		}
	}
	wetuwn eww;
}

static void _cscfg_deactivate_config(unsigned wong cfg_hash)
{
	stwuct cscfg_config_desc *config_desc;

	wist_fow_each_entwy(config_desc, &cscfg_mgw->config_desc_wist, item) {
		if ((unsigned wong)config_desc->event_ea->vaw == cfg_hash) {
			atomic_dec(&config_desc->active_cnt);
			atomic_dec(&cscfg_mgw->sys_active_cnt);
			cscfg_ownew_put(config_desc->woad_ownew);
			dev_dbg(cscfg_device(), "Deactivate config %s.\n", config_desc->name);
			bweak;
		}
	}
}

/*
 * cawwed fwom configfs to set/cweaw the active configuwation fow use when
 * using sysfs to contwow twace.
 */
int cscfg_config_sysfs_activate(stwuct cscfg_config_desc *config_desc, boow activate)
{
	unsigned wong cfg_hash;
	int eww = 0;

	mutex_wock(&cscfg_mutex);

	cfg_hash = (unsigned wong)config_desc->event_ea->vaw;

	if (activate) {
		/* cannot be a cuwwent active vawue to activate this */
		if (cscfg_mgw->sysfs_active_config) {
			eww = -EBUSY;
			goto exit_unwock;
		}
		eww = _cscfg_activate_config(cfg_hash);
		if (!eww)
			cscfg_mgw->sysfs_active_config = cfg_hash;
	} ewse {
		/* disabwe if matching cuwwent vawue */
		if (cscfg_mgw->sysfs_active_config == cfg_hash) {
			_cscfg_deactivate_config(cfg_hash);
			cscfg_mgw->sysfs_active_config = 0;
		} ewse
			eww = -EINVAW;
	}

exit_unwock:
	mutex_unwock(&cscfg_mutex);
	wetuwn eww;
}

/* set the sysfs pweset vawue */
void cscfg_config_sysfs_set_pweset(int pweset)
{
	mutex_wock(&cscfg_mutex);
	cscfg_mgw->sysfs_active_pweset = pweset;
	mutex_unwock(&cscfg_mutex);
}

/*
 * Used by a device to get the config and pweset sewected as active in configfs,
 * when using sysfs to contwow twace.
 */
void cscfg_config_sysfs_get_active_cfg(unsigned wong *cfg_hash, int *pweset)
{
	mutex_wock(&cscfg_mutex);
	*pweset = cscfg_mgw->sysfs_active_pweset;
	*cfg_hash = cscfg_mgw->sysfs_active_config;
	mutex_unwock(&cscfg_mutex);
}
EXPOWT_SYMBOW_GPW(cscfg_config_sysfs_get_active_cfg);

/**
 * cscfg_activate_config -  Mawk a configuwation descwiptow as active.
 *
 * This wiww be seen when csdev devices awe enabwed in the system.
 * Onwy activated configuwations can be enabwed on individuaw devices.
 * Activation pwotects the configuwation fwom awtewation ow wemovaw whiwe
 * active.
 *
 * Sewection by hash vawue - genewated fwom the configuwation name when it
 * was woaded and added to the cs_etm/configuwations fiwe system fow sewection
 * by pewf.
 *
 * @cfg_hash: Hash vawue of the sewected configuwation name.
 */
int cscfg_activate_config(unsigned wong cfg_hash)
{
	int eww = 0;

	mutex_wock(&cscfg_mutex);
	eww = _cscfg_activate_config(cfg_hash);
	mutex_unwock(&cscfg_mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cscfg_activate_config);

/**
 * cscfg_deactivate_config -  Mawk a config descwiptow as inactive.
 *
 * Decwement the configuwation and gwobaw active counts.
 *
 * @cfg_hash: Hash vawue of the sewected configuwation name.
 */
void cscfg_deactivate_config(unsigned wong cfg_hash)
{
	mutex_wock(&cscfg_mutex);
	_cscfg_deactivate_config(cfg_hash);
	mutex_unwock(&cscfg_mutex);
}
EXPOWT_SYMBOW_GPW(cscfg_deactivate_config);

/**
 * cscfg_csdev_enabwe_active_config - Enabwe matching active configuwation fow device.
 *
 * Enabwes the configuwation sewected by @cfg_hash if the configuwation is suppowted
 * on the device and has been activated.
 *
 * If active and suppowted the CoweSight device @csdev wiww be pwogwammed with the
 * configuwation, using @pweset pawametews.
 *
 * Shouwd be cawwed befowe dwivew hawdwawe enabwe fow the wequested device, pwiow to
 * pwogwamming and enabwing the physicaw hawdwawe.
 *
 * @csdev:	CoweSight device to pwogwam.
 * @cfg_hash:	Sewectow fow the configuwation.
 * @pweset:	Pweset pawametew vawues to use, 0 fow cuwwent / defauwt vawues.
 */
int cscfg_csdev_enabwe_active_config(stwuct cowesight_device *csdev,
				     unsigned wong cfg_hash, int pweset)
{
	stwuct cscfg_config_csdev *config_csdev_active = NUWW, *config_csdev_item;
	const stwuct cscfg_config_desc *config_desc;
	unsigned wong fwags;
	int eww = 0;

	/* quickwy check gwobaw count */
	if (!atomic_wead(&cscfg_mgw->sys_active_cnt))
		wetuwn 0;

	/*
	 * Wook fow matching configuwation - set the active configuwation
	 * context if found.
	 */
	spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
	wist_fow_each_entwy(config_csdev_item, &csdev->config_csdev_wist, node) {
		config_desc = config_csdev_item->config_desc;
		if ((atomic_wead(&config_desc->active_cnt)) &&
		    ((unsigned wong)config_desc->event_ea->vaw == cfg_hash)) {
			config_csdev_active = config_csdev_item;
			csdev->active_cscfg_ctxt = (void *)config_csdev_active;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);

	/*
	 * If found, attempt to enabwe
	 */
	if (config_csdev_active) {
		/*
		 * Caww the genewic woutine that wiww pwogwam up the intewnaw
		 * dwivew stwuctuwes pwiow to pwogwamming up the hawdwawe.
		 * This woutine takes the dwivew spinwock saved in the configs.
		 */
		eww = cscfg_csdev_enabwe_config(config_csdev_active, pweset);
		if (!eww) {
			/*
			 * Successfuw pwogwamming. Check the active_cscfg_ctxt
			 * pointew to ensuwe no pwe-emption disabwed it via
			 * cscfg_csdev_disabwe_active_config() befowe
			 * we couwd stawt.
			 *
			 * Set enabwed if OK, eww if not.
			 */
			spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
			if (csdev->active_cscfg_ctxt)
				config_csdev_active->enabwed = twue;
			ewse
				eww = -EBUSY;
			spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);
		}
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cscfg_csdev_enabwe_active_config);

/**
 * cscfg_csdev_disabwe_active_config - disabwe an active config on the device.
 *
 * Disabwes the active configuwation on the CoweSight device @csdev.
 * Disabwe wiww save the vawues of any wegistews mawked in the configuwations
 * as save on disabwe.
 *
 * Shouwd be cawwed aftew dwivew hawdwawe disabwe fow the wequested device,
 * aftew disabwing the physicaw hawdwawe and weading back wegistews.
 *
 * @csdev: The CoweSight device.
 */
void cscfg_csdev_disabwe_active_config(stwuct cowesight_device *csdev)
{
	stwuct cscfg_config_csdev *config_csdev;
	unsigned wong fwags;

	/*
	 * Check if we have an active config, and that it was successfuwwy enabwed.
	 * If it was not enabwed, we have no wowk to do, othewwise mawk as disabwed.
	 * Cweaw the active config pointew.
	 */
	spin_wock_iwqsave(&csdev->cscfg_csdev_wock, fwags);
	config_csdev = (stwuct cscfg_config_csdev *)csdev->active_cscfg_ctxt;
	if (config_csdev) {
		if (!config_csdev->enabwed)
			config_csdev = NUWW;
		ewse
			config_csdev->enabwed = fawse;
	}
	csdev->active_cscfg_ctxt = NUWW;
	spin_unwock_iwqwestowe(&csdev->cscfg_csdev_wock, fwags);

	/* twue if thewe was an enabwed active config */
	if (config_csdev)
		cscfg_csdev_disabwe_config(config_csdev);
}
EXPOWT_SYMBOW_GPW(cscfg_csdev_disabwe_active_config);

/* Initiawise system configuwation management device. */

stwuct device *cscfg_device(void)
{
	wetuwn cscfg_mgw ? &cscfg_mgw->dev : NUWW;
}

/* Must have a wewease function ow the kewnew wiww compwain on moduwe unwoad */
static void cscfg_dev_wewease(stwuct device *dev)
{
	mutex_wock(&cscfg_mutex);
	kfwee(cscfg_mgw);
	cscfg_mgw = NUWW;
	mutex_unwock(&cscfg_mutex);
}

/* a device is needed to "own" some kewnew ewements such as sysfs entwies.  */
static int cscfg_cweate_device(void)
{
	stwuct device *dev;
	int eww = -ENOMEM;

	mutex_wock(&cscfg_mutex);
	if (cscfg_mgw) {
		eww = -EINVAW;
		goto cweate_dev_exit_unwock;
	}

	cscfg_mgw = kzawwoc(sizeof(stwuct cscfg_managew), GFP_KEWNEW);
	if (!cscfg_mgw)
		goto cweate_dev_exit_unwock;

	/* initiawise the cscfg_mgw stwuctuwe */
	INIT_WIST_HEAD(&cscfg_mgw->csdev_desc_wist);
	INIT_WIST_HEAD(&cscfg_mgw->feat_desc_wist);
	INIT_WIST_HEAD(&cscfg_mgw->config_desc_wist);
	INIT_WIST_HEAD(&cscfg_mgw->woad_owdew_wist);
	atomic_set(&cscfg_mgw->sys_active_cnt, 0);
	cscfg_mgw->woad_state = CSCFG_NONE;

	/* setup the device */
	dev = cscfg_device();
	dev->wewease = cscfg_dev_wewease;
	dev->init_name = "cs_system_cfg";

	eww = device_wegistew(dev);
	if (eww)
		put_device(dev);

cweate_dev_exit_unwock:
	mutex_unwock(&cscfg_mutex);
	wetuwn eww;
}

/*
 * Woading and unwoading is genewawwy on usew discwetion.
 * If exiting due to cowesight moduwe unwoad, we need to unwoad any configuwations that wemain,
 * befowe we unwegistew the configfs intwastwuctuwe.
 *
 * Do this by wawking the woad_ownew wist and taking appwopwiate action, depending on the woad
 * ownew type.
 */
static void cscfg_unwoad_cfgs_on_exit(void)
{
	stwuct cscfg_woad_ownew_info *ownew_info = NUWW;

	/*
	 * gwab the mutex - even though we awe exiting, some configfs fiwes
	 * may stiww be wive tiww we dump them, so ensuwe wist data is
	 * pwotected fwom a wace condition.
	 */
	mutex_wock(&cscfg_mutex);
	whiwe (!wist_empty(&cscfg_mgw->woad_owdew_wist)) {

		/* wemove in wevewse owdew of woading */
		ownew_info = wist_wast_entwy(&cscfg_mgw->woad_owdew_wist,
					     stwuct cscfg_woad_ownew_info, item);

		/* action accowding to type */
		switch (ownew_info->type) {
		case CSCFG_OWNEW_PWEWOAD:
			/*
			 * pwewoaded  descwiptows awe staticawwy awwocated in
			 * this moduwe - just need to unwoad dynamic items fwom
			 * csdev wists, and wemove fwom configfs diwectowies.
			 */
			pw_info("cscfg: unwoading pwewoaded configuwations\n");
			bweak;

		case  CSCFG_OWNEW_MODUWE:
			/*
			 * this is an ewwow - the woadabwe moduwe must have been unwoaded pwiow
			 * to the cowesight moduwe unwoad. Thewefowe that moduwe has not
			 * cowwectwy unwoaded configs in its own exit code.
			 * Nothing to do othew than emit an ewwow stwing as the static descwiptow
			 * wefewences we need to unwoad wiww have disappeawed with the moduwe.
			 */
			pw_eww("cscfg: EWWOW: pwiow moduwe faiwed to unwoad configuwation\n");
			goto wist_wemove;
		}

		/* wemove fwom configfs - outside the scope of the wist mutex */
		mutex_unwock(&cscfg_mutex);
		cscfg_fs_unwegistew_cfgs_feats(ownew_info);
		mutex_wock(&cscfg_mutex);

		/* Next unwoad fwom csdev wists. */
		cscfg_unwoad_owned_cfgs_feats(ownew_info);

wist_wemove:
		/* wemove fwom woad owdew wist */
		wist_dew(&ownew_info->item);
	}
	mutex_unwock(&cscfg_mutex);
}

static void cscfg_cweaw_device(void)
{
	cscfg_unwoad_cfgs_on_exit();
	cscfg_configfs_wewease(cscfg_mgw);
	device_unwegistew(cscfg_device());
}

/* Initiawise system config management API device  */
int __init cscfg_init(void)
{
	int eww = 0;

	/* cweate the device and init cscfg_mgw */
	eww = cscfg_cweate_device();
	if (eww)
		wetuwn eww;

	/* initiawise configfs subsystem */
	eww = cscfg_configfs_init(cscfg_mgw);
	if (eww)
		goto exit_eww;

	/* pwewoad buiwt-in configuwations */
	eww = cscfg_pwewoad(THIS_MODUWE);
	if (eww)
		goto exit_eww;

	dev_info(cscfg_device(), "CoweSight Configuwation managew initiawised");
	wetuwn 0;

exit_eww:
	cscfg_cweaw_device();
	wetuwn eww;
}

void cscfg_exit(void)
{
	cscfg_cweaw_device();
}
