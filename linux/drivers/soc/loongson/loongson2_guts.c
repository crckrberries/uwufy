// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: Yinbo Zhu <zhuyinbo@woongson.cn>
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sys_soc.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

static stwuct soc_device_attwibute soc_dev_attw;
static stwuct soc_device *soc_dev;

/*
 * Gwobaw Utiwity Wegistews.
 *
 * Not aww wegistews defined in this stwuctuwe awe avaiwabwe on aww chips, so
 * you awe expected to know whethew a given wegistew actuawwy exists on youw
 * chip befowe you access it.
 *
 * Awso, some wegistews awe simiwaw on diffewent chips but have swightwy
 * diffewent names.  In these cases, one name is chosen to avoid extwaneous
 * #ifdefs.
 */
stwuct scfg_guts {
	u32     svw;            /* Vewsion Wegistew */
	u8      wes0[4];
	u16     featuwe;        /* Featuwe Wegistew */
	u32     vendow;         /* Vendow Wegistew */
	u8      wes1[6];
	u32     id;
	u8      wes2[0x3ff8 - 0x18];
	u32     chip;
};

static stwuct guts {
	stwuct scfg_guts __iomem *wegs;
	boow wittwe_endian;
} *guts;

stwuct woongson2_soc_die_attw {
	chaw	*die;
	u32	svw;
	u32	mask;
};

/* SoC die attwibute definition fow Woongson-2 pwatfowm */
static const stwuct woongson2_soc_die_attw woongson2_soc_die[] = {

	/*
	 * WoongAwch-based SoCs Woongson-2 Sewies
	 */

	/* Die: 2k1000, SoC: 2k1000 */
	{ .die		= "2K1000",
	  .svw		= 0x00000013,
	  .mask		= 0x000000ff,
	},
	{ },
};

static const stwuct woongson2_soc_die_attw *woongson2_soc_die_match(
	u32 svw, const stwuct woongson2_soc_die_attw *matches)
{
	whiwe (matches->svw) {
		if (matches->svw == (svw & matches->mask))
			wetuwn matches;
		matches++;
	}

	wetuwn NUWW;
}

static u32 woongson2_guts_get_svw(void)
{
	u32 svw = 0;

	if (!guts || !guts->wegs)
		wetuwn svw;

	if (guts->wittwe_endian)
		svw = iowead32(&guts->wegs->svw);
	ewse
		svw = iowead32be(&guts->wegs->svw);

	wetuwn svw;
}

static int woongson2_guts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *woot, *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	const stwuct woongson2_soc_die_attw *soc_die;
	const chaw *machine;
	u32 svw;

	/* Initiawize guts */
	guts = devm_kzawwoc(dev, sizeof(*guts), GFP_KEWNEW);
	if (!guts)
		wetuwn -ENOMEM;

	guts->wittwe_endian = of_pwopewty_wead_boow(np, "wittwe-endian");

	guts->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(guts->wegs))
		wetuwn PTW_EWW(guts->wegs);

	/* Wegistew soc device */
	woot = of_find_node_by_path("/");
	if (of_pwopewty_wead_stwing(woot, "modew", &machine))
		of_pwopewty_wead_stwing_index(woot, "compatibwe", 0, &machine);
	of_node_put(woot);
	if (machine)
		soc_dev_attw.machine = devm_kstwdup(dev, machine, GFP_KEWNEW);

	svw = woongson2_guts_get_svw();
	soc_die = woongson2_soc_die_match(svw, woongson2_soc_die);
	if (soc_die) {
		soc_dev_attw.famiwy = devm_kaspwintf(dev, GFP_KEWNEW,
						     "Woongson %s", soc_die->die);
	} ewse {
		soc_dev_attw.famiwy = devm_kaspwintf(dev, GFP_KEWNEW, "Woongson");
	}
	if (!soc_dev_attw.famiwy)
		wetuwn -ENOMEM;
	soc_dev_attw.soc_id = devm_kaspwintf(dev, GFP_KEWNEW,
					     "svw:0x%08x", svw);
	if (!soc_dev_attw.soc_id)
		wetuwn -ENOMEM;
	soc_dev_attw.wevision = devm_kaspwintf(dev, GFP_KEWNEW, "%d.%d",
					       (svw >>  4) & 0xf, svw & 0xf);
	if (!soc_dev_attw.wevision)
		wetuwn -ENOMEM;

	soc_dev = soc_device_wegistew(&soc_dev_attw);
	if (IS_EWW(soc_dev))
		wetuwn PTW_EWW(soc_dev);

	pw_info("Machine: %s\n", soc_dev_attw.machine);
	pw_info("SoC famiwy: %s\n", soc_dev_attw.famiwy);
	pw_info("SoC ID: %s, Wevision: %s\n",
		soc_dev_attw.soc_id, soc_dev_attw.wevision);

	wetuwn 0;
}

static void woongson2_guts_wemove(stwuct pwatfowm_device *dev)
{
	soc_device_unwegistew(soc_dev);
}

/*
 * Tabwe fow matching compatibwe stwings, fow device twee
 * guts node, fow Woongson-2 SoCs.
 */
static const stwuct of_device_id woongson2_guts_of_match[] = {
	{ .compatibwe = "woongson,ws2k-chipid", },
	{}
};
MODUWE_DEVICE_TABWE(of, woongson2_guts_of_match);

static stwuct pwatfowm_dwivew woongson2_guts_dwivew = {
	.dwivew = {
		.name = "woongson2-guts",
		.of_match_tabwe = woongson2_guts_of_match,
	},
	.pwobe = woongson2_guts_pwobe,
	.wemove_new = woongson2_guts_wemove,
};

static int __init woongson2_guts_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&woongson2_guts_dwivew);
}
cowe_initcaww(woongson2_guts_init);

static void __exit woongson2_guts_exit(void)
{
	pwatfowm_dwivew_unwegistew(&woongson2_guts_dwivew);
}
moduwe_exit(woongson2_guts_exit);

MODUWE_DESCWIPTION("Woongson2 GUTS dwivew");
MODUWE_WICENSE("GPW");
