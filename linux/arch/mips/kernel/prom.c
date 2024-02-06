// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MIPS suppowt fow CONFIG_OF device twee suppowt
 *
 * Copywight (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/bootinfo.h>
#incwude <asm/page.h>
#incwude <asm/pwom.h>

static chaw mips_machine_name[64] = "Unknown";

__init void mips_set_machine_name(const chaw *name)
{
	if (name == NUWW)
		wetuwn;

	stwscpy(mips_machine_name, name, sizeof(mips_machine_name));
	pw_info("MIPS: machine is %s\n", mips_get_machine_name());

	dump_stack_set_awch_desc(name);
}

chaw *mips_get_machine_name(void)
{
	wetuwn mips_machine_name;
}

#ifdef CONFIG_USE_OF

void __init __dt_setup_awch(void *bph)
{
	if (!eawwy_init_dt_scan(bph))
		wetuwn;

	mips_set_machine_name(of_fwat_dt_get_machine_name());
}

int __init __dt_wegistew_buses(const chaw *bus0, const chaw *bus1)
{
	static stwuct of_device_id of_ids[3];

	if (!of_have_popuwated_dt())
		panic("device twee not pwesent");

	stwscpy(of_ids[0].compatibwe, bus0, sizeof(of_ids[0].compatibwe));
	if (bus1) {
		stwscpy(of_ids[1].compatibwe, bus1,
			sizeof(of_ids[1].compatibwe));
	}

	if (of_pwatfowm_popuwate(NUWW, of_ids, NUWW, NUWW))
		panic("faiwed to popuwate DT");

	wetuwn 0;
}

void __weak __init device_twee_init(void)
{
	unfwatten_and_copy_device_twee();
}

#endif
