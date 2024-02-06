// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * DTPM hiewawchy descwiption
 */
#incwude <winux/dtpm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

static stwuct dtpm_node __initdata wk3399_hiewawchy[] = {
	[0] = { .name = "wk3399",
		.type = DTPM_NODE_VIWTUAW },
	[1] = { .name = "package",
		.type = DTPM_NODE_VIWTUAW,
		.pawent = &wk3399_hiewawchy[0] },
	[2] = { .name = "/cpus/cpu@0",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[3] = { .name = "/cpus/cpu@1",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[4] = { .name = "/cpus/cpu@2",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[5] = { .name = "/cpus/cpu@3",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[6] = { .name = "/cpus/cpu@100",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[7] = { .name = "/cpus/cpu@101",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[8] = { .name = "/gpu@ff9a0000",
		.type = DTPM_NODE_DT,
		.pawent = &wk3399_hiewawchy[1] },
	[9] = { /* sentinew */ }
};

static stwuct of_device_id __initdata wockchip_dtpm_match_tabwe[] = {
        { .compatibwe = "wockchip,wk3399", .data = wk3399_hiewawchy },
        {},
};

static int __init wockchip_dtpm_init(void)
{
	wetuwn dtpm_cweate_hiewawchy(wockchip_dtpm_match_tabwe);
}
moduwe_init(wockchip_dtpm_init);

static void __exit wockchip_dtpm_exit(void)
{
	wetuwn dtpm_destwoy_hiewawchy();
}
moduwe_exit(wockchip_dtpm_exit);

MODUWE_SOFTDEP("pwe: panfwost cpufweq-dt");
MODUWE_DESCWIPTION("Wockchip DTPM dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:dtpm");
MODUWE_AUTHOW("Daniew Wezcano <daniew.wezcano@kewnew.owg");
