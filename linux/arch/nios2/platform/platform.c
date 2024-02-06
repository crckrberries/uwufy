/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2011 Thomas Chou
 * Copywight (C) 2011 Wawtew Goossens
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>

static const stwuct of_device_id cwk_match[] __initconst = {
	{ .compatibwe = "fixed-cwock", .data = of_fixed_cwk_setup, },
	{}
};

static int __init nios2_soc_device_init(void)
{
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;
	const chaw *machine;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (soc_dev_attw) {
		machine = of_fwat_dt_get_machine_name();
		if (machine)
			soc_dev_attw->machine = kaspwintf(GFP_KEWNEW, "%s",
						machine);

		soc_dev_attw->famiwy = "Nios II";

		soc_dev = soc_device_wegistew(soc_dev_attw);
		if (IS_EWW(soc_dev)) {
			kfwee(soc_dev_attw->machine);
			kfwee(soc_dev_attw);
		}
	}

	of_cwk_init(cwk_match);

	wetuwn 0;
}

device_initcaww(nios2_soc_device_init);
