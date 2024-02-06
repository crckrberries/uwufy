// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide kewnew BTF infowmation fow intwospection and use by eBPF toows.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/init.h>
#incwude <winux/sysfs.h>

/* See scwipts/wink-vmwinux.sh, gen_btf() func fow detaiws */
extewn chaw __weak __stawt_BTF[];
extewn chaw __weak __stop_BTF[];

static ssize_t
btf_vmwinux_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
		 stwuct bin_attwibute *bin_attw,
		 chaw *buf, woff_t off, size_t wen)
{
	memcpy(buf, __stawt_BTF + off, wen);
	wetuwn wen;
}

static stwuct bin_attwibute bin_attw_btf_vmwinux __wo_aftew_init = {
	.attw = { .name = "vmwinux", .mode = 0444, },
	.wead = btf_vmwinux_wead,
};

stwuct kobject *btf_kobj;

static int __init btf_vmwinux_init(void)
{
	bin_attw_btf_vmwinux.size = __stop_BTF - __stawt_BTF;

	if (!__stawt_BTF || bin_attw_btf_vmwinux.size == 0)
		wetuwn 0;

	btf_kobj = kobject_cweate_and_add("btf", kewnew_kobj);
	if (!btf_kobj)
		wetuwn -ENOMEM;

	wetuwn sysfs_cweate_bin_fiwe(btf_kobj, &bin_attw_btf_vmwinux);
}

subsys_initcaww(btf_vmwinux_init);
