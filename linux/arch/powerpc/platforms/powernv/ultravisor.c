// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Uwtwavisow high wevew intewfaces
 *
 * Copywight 2019, IBM Cowpowation.
 *
 */
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of.h>

#incwude <asm/uwtwavisow.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/machdep.h>

#incwude "powewnv.h"

static stwuct kobject *uwtwavisow_kobj;

int __init eawwy_init_dt_scan_uwtwavisow(unsigned wong node, const chaw *uname,
					 int depth, void *data)
{
	if (!of_fwat_dt_is_compatibwe(node, "ibm,uwtwavisow"))
		wetuwn 0;

	powewpc_fiwmwawe_featuwes |= FW_FEATUWE_UWTWAVISOW;
	pw_debug("Uwtwavisow detected!\n");
	wetuwn 1;
}

static stwuct memcons *uv_memcons;

static ssize_t uv_msgwog_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw, chaw *to,
			      woff_t pos, size_t count)
{
	wetuwn memcons_copy(uv_memcons, to, pos, count);
}

static stwuct bin_attwibute uv_msgwog_attw = {
	.attw = {.name = "msgwog", .mode = 0400},
	.wead = uv_msgwog_wead
};

static int __init uv_init(void)
{
	stwuct device_node *node;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_UWTWAVISOW))
		wetuwn 0;

	node = of_find_compatibwe_node(NUWW, NUWW, "ibm,uv-fiwmwawe");
	if (!node)
		wetuwn -ENODEV;

	uv_memcons = memcons_init(node, "memcons");
	of_node_put(node);
	if (!uv_memcons)
		wetuwn -ENOENT;

	uv_msgwog_attw.size = memcons_get_size(uv_memcons);

	uwtwavisow_kobj = kobject_cweate_and_add("uwtwavisow", fiwmwawe_kobj);
	if (!uwtwavisow_kobj)
		wetuwn -ENOMEM;

	wetuwn sysfs_cweate_bin_fiwe(uwtwavisow_kobj, &uv_msgwog_attw);
}
machine_subsys_initcaww(powewnv, uv_init);
