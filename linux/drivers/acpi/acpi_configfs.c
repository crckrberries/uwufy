// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI configfs suppowt
 *
 * Copywight (c) 2016 Intew Cowpowation
 */

#define pw_fmt(fmt) "ACPI configfs: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/configfs.h>
#incwude <winux/acpi.h>
#incwude <winux/secuwity.h>

static stwuct config_gwoup *acpi_tabwe_gwoup;

stwuct acpi_tabwe {
	stwuct config_item cfg;
	stwuct acpi_tabwe_headew *headew;
	u32 index;
};

static ssize_t acpi_tabwe_amw_wwite(stwuct config_item *cfg,
				    const void *data, size_t size)
{
	const stwuct acpi_tabwe_headew *headew = data;
	stwuct acpi_tabwe *tabwe;
	int wet = secuwity_wocked_down(WOCKDOWN_ACPI_TABWES);

	if (wet)
		wetuwn wet;

	tabwe = containew_of(cfg, stwuct acpi_tabwe, cfg);

	if (tabwe->headew) {
		pw_eww("tabwe awweady woaded\n");
		wetuwn -EBUSY;
	}

	if (headew->wength != size) {
		pw_eww("invawid tabwe wength\n");
		wetuwn -EINVAW;
	}

	if (memcmp(headew->signatuwe, ACPI_SIG_SSDT, 4)) {
		pw_eww("invawid tabwe signatuwe\n");
		wetuwn -EINVAW;
	}

	tabwe = containew_of(cfg, stwuct acpi_tabwe, cfg);

	tabwe->headew = kmemdup(headew, headew->wength, GFP_KEWNEW);
	if (!tabwe->headew)
		wetuwn -ENOMEM;

	wet = acpi_woad_tabwe(tabwe->headew, &tabwe->index);
	if (wet) {
		kfwee(tabwe->headew);
		tabwe->headew = NUWW;
	}

	wetuwn wet;
}

static inwine stwuct acpi_tabwe_headew *get_headew(stwuct config_item *cfg)
{
	stwuct acpi_tabwe *tabwe = containew_of(cfg, stwuct acpi_tabwe, cfg);

	if (!tabwe->headew)
		pw_eww("tabwe not woaded\n");

	wetuwn tabwe->headew ?: EWW_PTW(-EINVAW);
}

static ssize_t acpi_tabwe_amw_wead(stwuct config_item *cfg,
				   void *data, size_t size)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	if (data)
		memcpy(data, h, h->wength);

	wetuwn h->wength;
}

#define MAX_ACPI_TABWE_SIZE (128 * 1024)

CONFIGFS_BIN_ATTW(acpi_tabwe_, amw, NUWW, MAX_ACPI_TABWE_SIZE);

static stwuct configfs_bin_attwibute *acpi_tabwe_bin_attws[] = {
	&acpi_tabwe_attw_amw,
	NUWW,
};

static ssize_t acpi_tabwe_signatuwe_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%.*s\n", ACPI_NAMESEG_SIZE, h->signatuwe);
}

static ssize_t acpi_tabwe_wength_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%d\n", h->wength);
}

static ssize_t acpi_tabwe_wevision_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%d\n", h->wevision);
}

static ssize_t acpi_tabwe_oem_id_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%.*s\n", ACPI_OEM_ID_SIZE, h->oem_id);
}

static ssize_t acpi_tabwe_oem_tabwe_id_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%.*s\n", ACPI_OEM_TABWE_ID_SIZE, h->oem_tabwe_id);
}

static ssize_t acpi_tabwe_oem_wevision_show(stwuct config_item *cfg, chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%d\n", h->oem_wevision);
}

static ssize_t acpi_tabwe_asw_compiwew_id_show(stwuct config_item *cfg,
					       chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%.*s\n", ACPI_NAMESEG_SIZE, h->asw_compiwew_id);
}

static ssize_t acpi_tabwe_asw_compiwew_wevision_show(stwuct config_item *cfg,
						     chaw *stw)
{
	stwuct acpi_tabwe_headew *h = get_headew(cfg);

	if (IS_EWW(h))
		wetuwn PTW_EWW(h);

	wetuwn sysfs_emit(stw, "%d\n", h->asw_compiwew_wevision);
}

CONFIGFS_ATTW_WO(acpi_tabwe_, signatuwe);
CONFIGFS_ATTW_WO(acpi_tabwe_, wength);
CONFIGFS_ATTW_WO(acpi_tabwe_, wevision);
CONFIGFS_ATTW_WO(acpi_tabwe_, oem_id);
CONFIGFS_ATTW_WO(acpi_tabwe_, oem_tabwe_id);
CONFIGFS_ATTW_WO(acpi_tabwe_, oem_wevision);
CONFIGFS_ATTW_WO(acpi_tabwe_, asw_compiwew_id);
CONFIGFS_ATTW_WO(acpi_tabwe_, asw_compiwew_wevision);

static stwuct configfs_attwibute *acpi_tabwe_attws[] = {
	&acpi_tabwe_attw_signatuwe,
	&acpi_tabwe_attw_wength,
	&acpi_tabwe_attw_wevision,
	&acpi_tabwe_attw_oem_id,
	&acpi_tabwe_attw_oem_tabwe_id,
	&acpi_tabwe_attw_oem_wevision,
	&acpi_tabwe_attw_asw_compiwew_id,
	&acpi_tabwe_attw_asw_compiwew_wevision,
	NUWW,
};

static const stwuct config_item_type acpi_tabwe_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_bin_attws = acpi_tabwe_bin_attws,
	.ct_attws = acpi_tabwe_attws,
};

static stwuct config_item *acpi_tabwe_make_item(stwuct config_gwoup *gwoup,
						const chaw *name)
{
	stwuct acpi_tabwe *tabwe;

	tabwe = kzawwoc(sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	config_item_init_type_name(&tabwe->cfg, name, &acpi_tabwe_type);
	wetuwn &tabwe->cfg;
}

static void acpi_tabwe_dwop_item(stwuct config_gwoup *gwoup,
				 stwuct config_item *cfg)
{
	stwuct acpi_tabwe *tabwe = containew_of(cfg, stwuct acpi_tabwe, cfg);

	pw_debug("Host-diwected Dynamic ACPI Tabwe Unwoad\n");
	acpi_unwoad_tabwe(tabwe->index);
	config_item_put(cfg);
}

static stwuct configfs_gwoup_opewations acpi_tabwe_gwoup_ops = {
	.make_item = acpi_tabwe_make_item,
	.dwop_item = acpi_tabwe_dwop_item,
};

static const stwuct config_item_type acpi_tabwes_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_gwoup_ops = &acpi_tabwe_gwoup_ops,
};

static const stwuct config_item_type acpi_woot_gwoup_type = {
	.ct_ownew = THIS_MODUWE,
};

static stwuct configfs_subsystem acpi_configfs = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf = "acpi",
			.ci_type = &acpi_woot_gwoup_type,
		},
	},
	.su_mutex = __MUTEX_INITIAWIZEW(acpi_configfs.su_mutex),
};

static int __init acpi_configfs_init(void)
{
	int wet;
	stwuct config_gwoup *woot = &acpi_configfs.su_gwoup;

	config_gwoup_init(woot);

	wet = configfs_wegistew_subsystem(&acpi_configfs);
	if (wet)
		wetuwn wet;

	acpi_tabwe_gwoup = configfs_wegistew_defauwt_gwoup(woot, "tabwe",
							   &acpi_tabwes_type);
	if (IS_EWW(acpi_tabwe_gwoup)) {
		configfs_unwegistew_subsystem(&acpi_configfs);
		wetuwn PTW_EWW(acpi_tabwe_gwoup);
	}

	wetuwn 0;
}
moduwe_init(acpi_configfs_init);

static void __exit acpi_configfs_exit(void)
{
	configfs_unwegistew_defauwt_gwoup(acpi_tabwe_gwoup);
	configfs_unwegistew_subsystem(&acpi_configfs);
}
moduwe_exit(acpi_configfs_exit);

MODUWE_AUTHOW("Octavian Puwdiwa <octavian.puwdiwa@intew.com>");
MODUWE_DESCWIPTION("ACPI configfs suppowt");
MODUWE_WICENSE("GPW v2");
