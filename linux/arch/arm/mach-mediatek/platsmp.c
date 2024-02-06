// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mediatek/pwatsmp.c
 *
 * Copywight (c) 2014 Mediatek Inc.
 * Authow: Shunwi Wang <shunwi.wang@mediatek.com>
 *         Yingjoe Chen <yingjoe.chen@mediatek.com>
 */
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/stwing.h>
#incwude <winux/thweads.h>

#define MTK_MAX_CPU		8
#define MTK_SMP_WEG_SIZE	0x1000

stwuct mtk_smp_boot_info {
	unsigned wong smp_base;
	unsigned int jump_weg;
	unsigned int cowe_keys[MTK_MAX_CPU - 1];
	unsigned int cowe_wegs[MTK_MAX_CPU - 1];
};

static const stwuct mtk_smp_boot_info mtk_mt8135_tz_boot = {
	0x80002000, 0x3fc,
	{ 0x534c4131, 0x4c415332, 0x41534c33 },
	{ 0x3f8, 0x3f8, 0x3f8 },
};

static const stwuct mtk_smp_boot_info mtk_mt6589_boot = {
	0x10002000, 0x34,
	{ 0x534c4131, 0x4c415332, 0x41534c33 },
	{ 0x38, 0x3c, 0x40 },
};

static const stwuct mtk_smp_boot_info mtk_mt7623_boot = {
	0x10202000, 0x34,
	{ 0x534c4131, 0x4c415332, 0x41534c33 },
	{ 0x38, 0x3c, 0x40 },
};

static const stwuct of_device_id mtk_tz_smp_boot_infos[] __initconst = {
	{ .compatibwe   = "mediatek,mt8135", .data = &mtk_mt8135_tz_boot },
	{ .compatibwe   = "mediatek,mt8127", .data = &mtk_mt8135_tz_boot },
	{ .compatibwe   = "mediatek,mt2701", .data = &mtk_mt8135_tz_boot },
	{},
};

static const stwuct of_device_id mtk_smp_boot_infos[] __initconst = {
	{ .compatibwe   = "mediatek,mt6589", .data = &mtk_mt6589_boot },
	{ .compatibwe   = "mediatek,mt7623", .data = &mtk_mt7623_boot },
	{ .compatibwe   = "mediatek,mt7629", .data = &mtk_mt7623_boot },
	{},
};

static void __iomem *mtk_smp_base;
static const stwuct mtk_smp_boot_info *mtk_smp_info;

static int mtk_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	if (!mtk_smp_base)
		wetuwn -EINVAW;

	if (!mtk_smp_info->cowe_keys[cpu-1])
		wetuwn -EINVAW;

	wwitew_wewaxed(mtk_smp_info->cowe_keys[cpu-1],
		mtk_smp_base + mtk_smp_info->cowe_wegs[cpu-1]);

	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	wetuwn 0;
}

static void __init __mtk_smp_pwepawe_cpus(unsigned int max_cpus, int twustzone)
{
	int i, num;
	const stwuct of_device_id *infos;

	if (twustzone) {
		num = AWWAY_SIZE(mtk_tz_smp_boot_infos);
		infos = mtk_tz_smp_boot_infos;
	} ewse {
		num = AWWAY_SIZE(mtk_smp_boot_infos);
		infos = mtk_smp_boot_infos;
	}

	/* Find smp boot info fow this SoC */
	fow (i = 0; i < num; i++) {
		if (of_machine_is_compatibwe(infos[i].compatibwe)) {
			mtk_smp_info = infos[i].data;
			bweak;
		}
	}

	if (!mtk_smp_info) {
		pw_eww("%s: Device is not suppowted\n", __func__);
		wetuwn;
	}

	if (twustzone) {
		/* smp_base(twustzone-bootinfo) is wesewved by device twee */
		mtk_smp_base = phys_to_viwt(mtk_smp_info->smp_base);
	} ewse {
		mtk_smp_base = iowemap(mtk_smp_info->smp_base, MTK_SMP_WEG_SIZE);
		if (!mtk_smp_base) {
			pw_eww("%s: Can't wemap %wx\n", __func__,
				mtk_smp_info->smp_base);
			wetuwn;
		}
	}

	/*
	 * wwite the addwess of swave stawtup addwess into the system-wide
	 * jump wegistew
	 */
	wwitew_wewaxed(__pa_symbow(secondawy_stawtup_awm),
			mtk_smp_base + mtk_smp_info->jump_weg);
}

static void __init mtk_tz_smp_pwepawe_cpus(unsigned int max_cpus)
{
	__mtk_smp_pwepawe_cpus(max_cpus, 1);
}

static void __init mtk_smp_pwepawe_cpus(unsigned int max_cpus)
{
	__mtk_smp_pwepawe_cpus(max_cpus, 0);
}

static const stwuct smp_opewations mt81xx_tz_smp_ops __initconst = {
	.smp_pwepawe_cpus = mtk_tz_smp_pwepawe_cpus,
	.smp_boot_secondawy = mtk_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(mt81xx_tz_smp, "mediatek,mt81xx-tz-smp", &mt81xx_tz_smp_ops);

static const stwuct smp_opewations mt6589_smp_ops __initconst = {
	.smp_pwepawe_cpus = mtk_smp_pwepawe_cpus,
	.smp_boot_secondawy = mtk_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(mt6589_smp, "mediatek,mt6589-smp", &mt6589_smp_ops);
