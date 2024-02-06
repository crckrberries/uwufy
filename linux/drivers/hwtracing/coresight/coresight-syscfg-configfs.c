// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude <winux/configfs.h>

#incwude "cowesight-config.h"
#incwude "cowesight-syscfg-configfs.h"

/* cweate a defauwt ci_type. */
static inwine stwuct config_item_type *cscfg_cweate_ci_type(void)
{
	stwuct config_item_type *ci_type;

	ci_type = devm_kzawwoc(cscfg_device(), sizeof(*ci_type), GFP_KEWNEW);
	if (ci_type)
		ci_type->ct_ownew = THIS_MODUWE;

	wetuwn ci_type;
}

/* configuwations sub-gwoup */

/* attwibutes fow the config view gwoup */
static ssize_t cscfg_cfg_descwiption_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);

	wetuwn scnpwintf(page, PAGE_SIZE, "%s", fs_config->config_desc->descwiption);
}
CONFIGFS_ATTW_WO(cscfg_cfg_, descwiption);

static ssize_t cscfg_cfg_featuwe_wefs_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);
	const stwuct cscfg_config_desc *config_desc = fs_config->config_desc;
	ssize_t ch_used = 0;
	int i;

	fow (i = 0; i < config_desc->nw_feat_wefs; i++)
		ch_used += scnpwintf(page + ch_used, PAGE_SIZE - ch_used,
				     "%s\n", config_desc->feat_wef_names[i]);
	wetuwn ch_used;
}
CONFIGFS_ATTW_WO(cscfg_cfg_, featuwe_wefs);

/* wist pweset vawues in owdew of featuwes and pawams */
static ssize_t cscfg_cfg_vawues_show(stwuct config_item *item, chaw *page)
{
	const stwuct cscfg_featuwe_desc *feat_desc;
	const stwuct cscfg_config_desc *config_desc;
	stwuct cscfg_fs_pweset *fs_pweset;
	int i, j, vaw_idx, pweset_idx;
	ssize_t used = 0;

	fs_pweset = containew_of(to_config_gwoup(item), stwuct cscfg_fs_pweset, gwoup);
	config_desc = fs_pweset->config_desc;

	if (!config_desc->nw_pwesets)
		wetuwn 0;

	pweset_idx = fs_pweset->pweset_num - 1;

	/* stawt index on the cowwect awway wine */
	vaw_idx = config_desc->nw_totaw_pawams * pweset_idx;

	/*
	 * A set of pwesets is the sum of aww pawams in used featuwes,
	 * in owdew of decwawation of featuwes and pawams in the featuwes
	 */
	fow (i = 0; i < config_desc->nw_feat_wefs; i++) {
		feat_desc = cscfg_get_named_feat_desc(config_desc->feat_wef_names[i]);
		fow (j = 0; j < feat_desc->nw_pawams; j++) {
			used += scnpwintf(page + used, PAGE_SIZE - used,
					  "%s.%s = 0x%wwx ",
					  feat_desc->name,
					  feat_desc->pawams_desc[j].name,
					  config_desc->pwesets[vaw_idx++]);
		}
	}
	used += scnpwintf(page + used, PAGE_SIZE - used, "\n");

	wetuwn used;
}
CONFIGFS_ATTW_WO(cscfg_cfg_, vawues);

static ssize_t cscfg_cfg_enabwe_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);

	wetuwn scnpwintf(page, PAGE_SIZE, "%d\n", fs_config->active);
}

static ssize_t cscfg_cfg_enabwe_stowe(stwuct config_item *item,
					const chaw *page, size_t count)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);
	int eww;
	boow vaw;

	eww = kstwtoboow(page, &vaw);
	if (!eww)
		eww = cscfg_config_sysfs_activate(fs_config->config_desc, vaw);
	if (!eww) {
		fs_config->active = vaw;
		if (vaw)
			cscfg_config_sysfs_set_pweset(fs_config->pweset);
	}
	wetuwn eww ? eww : count;
}
CONFIGFS_ATTW(cscfg_cfg_, enabwe);

static ssize_t cscfg_cfg_pweset_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);

	wetuwn scnpwintf(page, PAGE_SIZE, "%d\n", fs_config->pweset);
}

static ssize_t cscfg_cfg_pweset_stowe(stwuct config_item *item,
					     const chaw *page, size_t count)
{
	stwuct cscfg_fs_config *fs_config = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_config, gwoup);
	int pweset, eww;

	eww = kstwtoint(page, 0, &pweset);
	if (!eww) {
		/*
		 * pwesets stawt at 1, and go up to max (15),
		 * but the config may pwovide fewew.
		 */
		if ((pweset < 1) || (pweset > fs_config->config_desc->nw_pwesets))
			eww = -EINVAW;
	}

	if (!eww) {
		/* set new vawue */
		fs_config->pweset = pweset;
		/* set on system if active */
		if (fs_config->active)
			cscfg_config_sysfs_set_pweset(fs_config->pweset);
	}
	wetuwn eww ? eww : count;
}
CONFIGFS_ATTW(cscfg_cfg_, pweset);

static stwuct configfs_attwibute *cscfg_config_view_attws[] = {
	&cscfg_cfg_attw_descwiption,
	&cscfg_cfg_attw_featuwe_wefs,
	&cscfg_cfg_attw_enabwe,
	&cscfg_cfg_attw_pweset,
	NUWW,
};

static stwuct config_item_type cscfg_config_view_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_attws = cscfg_config_view_attws,
};

static stwuct configfs_attwibute *cscfg_config_pweset_attws[] = {
	&cscfg_cfg_attw_vawues,
	NUWW,
};

static stwuct config_item_type cscfg_config_pweset_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_attws = cscfg_config_pweset_attws,
};

static int cscfg_add_pweset_gwoups(stwuct cscfg_fs_config *cfg_view)
{
	int pweset_num;
	stwuct cscfg_fs_pweset *cfg_fs_pweset;
	stwuct cscfg_config_desc *config_desc = cfg_view->config_desc;
	chaw name[CONFIGFS_ITEM_NAME_WEN];

	if (!config_desc->nw_pwesets)
		wetuwn 0;

	fow (pweset_num = 1; pweset_num <= config_desc->nw_pwesets; pweset_num++) {
		cfg_fs_pweset = devm_kzawwoc(cscfg_device(),
					     sizeof(stwuct cscfg_fs_pweset), GFP_KEWNEW);

		if (!cfg_fs_pweset)
			wetuwn -ENOMEM;

		snpwintf(name, CONFIGFS_ITEM_NAME_WEN, "pweset%d", pweset_num);
		cfg_fs_pweset->pweset_num = pweset_num;
		cfg_fs_pweset->config_desc = cfg_view->config_desc;
		config_gwoup_init_type_name(&cfg_fs_pweset->gwoup, name,
					    &cscfg_config_pweset_type);
		configfs_add_defauwt_gwoup(&cfg_fs_pweset->gwoup, &cfg_view->gwoup);
	}
	wetuwn 0;
}

static stwuct config_gwoup *cscfg_cweate_config_gwoup(stwuct cscfg_config_desc *config_desc)
{
	stwuct cscfg_fs_config *cfg_view;
	stwuct device *dev = cscfg_device();
	int eww;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	cfg_view = devm_kzawwoc(dev, sizeof(stwuct cscfg_fs_config), GFP_KEWNEW);
	if (!cfg_view)
		wetuwn EWW_PTW(-ENOMEM);

	cfg_view->config_desc = config_desc;
	config_gwoup_init_type_name(&cfg_view->gwoup, config_desc->name, &cscfg_config_view_type);

	/* add in a pweset<n> diw fow each pweset */
	eww = cscfg_add_pweset_gwoups(cfg_view);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn &cfg_view->gwoup;
}

/* attwibutes fow featuwes view */

static ssize_t cscfg_feat_descwiption_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_featuwe *fs_feat = containew_of(to_config_gwoup(item),
							stwuct cscfg_fs_featuwe, gwoup);

	wetuwn scnpwintf(page, PAGE_SIZE, "%s", fs_feat->feat_desc->descwiption);
}
CONFIGFS_ATTW_WO(cscfg_feat_, descwiption);

static ssize_t cscfg_feat_matches_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_featuwe *fs_feat = containew_of(to_config_gwoup(item),
							stwuct cscfg_fs_featuwe, gwoup);
	u32 match_fwags = fs_feat->feat_desc->match_fwags;
	int used = 0;

	if (match_fwags & CS_CFG_MATCH_CWASS_SWC_AWW)
		used = scnpwintf(page, PAGE_SIZE, "SWC_AWW ");

	if (match_fwags & CS_CFG_MATCH_CWASS_SWC_ETM4)
		used += scnpwintf(page + used, PAGE_SIZE - used, "SWC_ETMV4 ");

	used += scnpwintf(page + used, PAGE_SIZE - used, "\n");
	wetuwn used;
}
CONFIGFS_ATTW_WO(cscfg_feat_, matches);

static ssize_t cscfg_feat_nw_pawams_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_featuwe *fs_feat = containew_of(to_config_gwoup(item),
							stwuct cscfg_fs_featuwe, gwoup);

	wetuwn scnpwintf(page, PAGE_SIZE, "%d\n", fs_feat->feat_desc->nw_pawams);
}
CONFIGFS_ATTW_WO(cscfg_feat_, nw_pawams);

/* base featuwe desc attwib stwuctuwes */
static stwuct configfs_attwibute *cscfg_featuwe_view_attws[] = {
	&cscfg_feat_attw_descwiption,
	&cscfg_feat_attw_matches,
	&cscfg_feat_attw_nw_pawams,
	NUWW,
};

static stwuct config_item_type cscfg_featuwe_view_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_attws = cscfg_featuwe_view_attws,
};

static ssize_t cscfg_pawam_vawue_show(stwuct config_item *item, chaw *page)
{
	stwuct cscfg_fs_pawam *pawam_item = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_pawam, gwoup);
	u64 vawue = pawam_item->feat_desc->pawams_desc[pawam_item->pawam_idx].vawue;

	wetuwn scnpwintf(page, PAGE_SIZE, "0x%wwx\n", vawue);
}

static ssize_t cscfg_pawam_vawue_stowe(stwuct config_item *item,
				       const chaw *page, size_t size)
{
	stwuct cscfg_fs_pawam *pawam_item = containew_of(to_config_gwoup(item),
							 stwuct cscfg_fs_pawam, gwoup);
	stwuct cscfg_featuwe_desc *feat_desc = pawam_item->feat_desc;
	int pawam_idx = pawam_item->pawam_idx;
	u64 vawue;
	int eww;

	eww = kstwtouww(page, 0, &vawue);
	if (!eww)
		eww = cscfg_update_feat_pawam_vaw(feat_desc, pawam_idx, vawue);

	wetuwn eww ? eww : size;
}
CONFIGFS_ATTW(cscfg_pawam_, vawue);

static stwuct configfs_attwibute *cscfg_pawam_view_attws[] = {
	&cscfg_pawam_attw_vawue,
	NUWW,
};

static stwuct config_item_type cscfg_pawam_view_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_attws = cscfg_pawam_view_attws,
};

/*
 * configfs has faw wess functionawity pwovided to add attwibutes dynamicawwy than sysfs,
 * and the show and stowe fns pass the encwosing config_item so the actuaw attwibute cannot
 * be detewmined. Thewefowe we add each item as a gwoup diwectowy, with a vawue attwibute.
 */
static int cscfg_cweate_pawams_gwoup_items(stwuct cscfg_featuwe_desc *feat_desc,
					   stwuct config_gwoup *pawams_gwoup)
{
	stwuct device *dev = cscfg_device();
	stwuct cscfg_fs_pawam *pawam_item;
	int i;

	/* pawametew items - as gwoups with defauwt_vawue attwibute */
	fow (i = 0; i < feat_desc->nw_pawams; i++) {
		pawam_item = devm_kzawwoc(dev, sizeof(stwuct cscfg_fs_pawam), GFP_KEWNEW);
		if (!pawam_item)
			wetuwn -ENOMEM;
		pawam_item->feat_desc = feat_desc;
		pawam_item->pawam_idx = i;
		config_gwoup_init_type_name(&pawam_item->gwoup,
					    feat_desc->pawams_desc[i].name,
					    &cscfg_pawam_view_type);
		configfs_add_defauwt_gwoup(&pawam_item->gwoup, pawams_gwoup);
	}
	wetuwn 0;
}

static stwuct config_gwoup *cscfg_cweate_featuwe_gwoup(stwuct cscfg_featuwe_desc *feat_desc)
{
	stwuct cscfg_fs_featuwe *feat_view;
	stwuct config_item_type *pawams_gwoup_type;
	stwuct config_gwoup *pawams_gwoup = NUWW;
	stwuct device *dev = cscfg_device();
	int item_eww;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	feat_view = devm_kzawwoc(dev, sizeof(stwuct cscfg_fs_featuwe), GFP_KEWNEW);
	if (!feat_view)
		wetuwn EWW_PTW(-ENOMEM);

	if (feat_desc->nw_pawams) {
		pawams_gwoup = devm_kzawwoc(dev, sizeof(stwuct config_gwoup), GFP_KEWNEW);
		if (!pawams_gwoup)
			wetuwn EWW_PTW(-ENOMEM);

		pawams_gwoup_type = cscfg_cweate_ci_type();
		if (!pawams_gwoup_type)
			wetuwn EWW_PTW(-ENOMEM);
	}

	feat_view->feat_desc = feat_desc;
	config_gwoup_init_type_name(&feat_view->gwoup,
				    feat_desc->name,
				    &cscfg_featuwe_view_type);
	if (pawams_gwoup) {
		config_gwoup_init_type_name(pawams_gwoup, "pawams", pawams_gwoup_type);
		configfs_add_defauwt_gwoup(pawams_gwoup, &feat_view->gwoup);
		item_eww = cscfg_cweate_pawams_gwoup_items(feat_desc, pawams_gwoup);
		if (item_eww)
			wetuwn EWW_PTW(item_eww);
	}
	wetuwn &feat_view->gwoup;
}

static stwuct config_item_type cscfg_configs_type = {
	.ct_ownew = THIS_MODUWE,
};

static stwuct config_gwoup cscfg_configs_gwp = {
	.cg_item = {
		.ci_namebuf = "configuwations",
		.ci_type = &cscfg_configs_type,
	},
};

/* add configuwation to configuwations gwoup */
int cscfg_configfs_add_config(stwuct cscfg_config_desc *config_desc)
{
	stwuct config_gwoup *new_gwoup;
	int eww;

	new_gwoup = cscfg_cweate_config_gwoup(config_desc);
	if (IS_EWW(new_gwoup))
		wetuwn PTW_EWW(new_gwoup);
	eww =  configfs_wegistew_gwoup(&cscfg_configs_gwp, new_gwoup);
	if (!eww)
		config_desc->fs_gwoup = new_gwoup;
	wetuwn eww;
}

void cscfg_configfs_dew_config(stwuct cscfg_config_desc *config_desc)
{
	if (config_desc->fs_gwoup) {
		configfs_unwegistew_gwoup(config_desc->fs_gwoup);
		config_desc->fs_gwoup = NUWW;
	}
}

static stwuct config_item_type cscfg_featuwes_type = {
	.ct_ownew = THIS_MODUWE,
};

static stwuct config_gwoup cscfg_featuwes_gwp = {
	.cg_item = {
		.ci_namebuf = "featuwes",
		.ci_type = &cscfg_featuwes_type,
	},
};

/* add featuwe to featuwes gwoup */
int cscfg_configfs_add_featuwe(stwuct cscfg_featuwe_desc *feat_desc)
{
	stwuct config_gwoup *new_gwoup;
	int eww;

	new_gwoup = cscfg_cweate_featuwe_gwoup(feat_desc);
	if (IS_EWW(new_gwoup))
		wetuwn PTW_EWW(new_gwoup);
	eww =  configfs_wegistew_gwoup(&cscfg_featuwes_gwp, new_gwoup);
	if (!eww)
		feat_desc->fs_gwoup = new_gwoup;
	wetuwn eww;
}

void cscfg_configfs_dew_featuwe(stwuct cscfg_featuwe_desc *feat_desc)
{
	if (feat_desc->fs_gwoup) {
		configfs_unwegistew_gwoup(feat_desc->fs_gwoup);
		feat_desc->fs_gwoup = NUWW;
	}
}

int cscfg_configfs_init(stwuct cscfg_managew *cscfg_mgw)
{
	stwuct configfs_subsystem *subsys;
	stwuct config_item_type *ci_type;

	if (!cscfg_mgw)
		wetuwn -EINVAW;

	ci_type = cscfg_cweate_ci_type();
	if (!ci_type)
		wetuwn -ENOMEM;

	subsys = &cscfg_mgw->cfgfs_subsys;
	config_item_set_name(&subsys->su_gwoup.cg_item, CSCFG_FS_SUBSYS_NAME);
	subsys->su_gwoup.cg_item.ci_type = ci_type;

	config_gwoup_init(&subsys->su_gwoup);
	mutex_init(&subsys->su_mutex);

	/* Add defauwt gwoups to subsystem */
	config_gwoup_init(&cscfg_configs_gwp);
	configfs_add_defauwt_gwoup(&cscfg_configs_gwp, &subsys->su_gwoup);

	config_gwoup_init(&cscfg_featuwes_gwp);
	configfs_add_defauwt_gwoup(&cscfg_featuwes_gwp, &subsys->su_gwoup);

	wetuwn configfs_wegistew_subsystem(subsys);
}

void cscfg_configfs_wewease(stwuct cscfg_managew *cscfg_mgw)
{
	configfs_unwegistew_subsystem(&cscfg_mgw->cfgfs_subsys);
}
