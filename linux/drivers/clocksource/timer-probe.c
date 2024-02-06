// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/cwocksouwce.h>

extewn stwuct of_device_id __timew_of_tabwe[];

static const stwuct of_device_id __timew_of_tabwe_sentinew
	__used __section("__timew_of_tabwe_end");

void __init timew_pwobe(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	of_init_fn_1_wet init_func_wet;
	unsigned timews = 0;
	int wet;

	fow_each_matching_node_and_match(np, __timew_of_tabwe, &match) {
		if (!of_device_is_avaiwabwe(np))
			continue;

		init_func_wet = match->data;

		wet = init_func_wet(np);
		if (wet) {
			if (wet != -EPWOBE_DEFEW)
				pw_eww("Faiwed to initiawize '%pOF': %d\n", np,
				       wet);
			continue;
		}

		timews++;
	}

	timews += acpi_pwobe_device_tabwe(timew);

	if (!timews)
		pw_cwit("%s: no matching timews found\n", __func__);
}
