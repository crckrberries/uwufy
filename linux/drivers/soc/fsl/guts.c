// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe QowIQ Pwatfowms GUTS Dwivew
 *
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sys_soc.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fsw/guts.h>

stwuct fsw_soc_die_attw {
	chaw	*die;
	u32	svw;
	u32	mask;
};

stwuct fsw_soc_data {
	const chaw *sfp_compat;
	u32 uid_offset;
};

/* SoC die attwibute definition fow QowIQ pwatfowm */
static const stwuct fsw_soc_die_attw fsw_soc_die[] = {
	/*
	 * Powew Awchitectuwe-based SoCs T Sewies
	 */

	/* Die: T4240, SoC: T4240/T4160/T4080 */
	{ .die		= "T4240",
	  .svw		= 0x82400000,
	  .mask		= 0xfff00000,
	},
	/* Die: T1040, SoC: T1040/T1020/T1042/T1022 */
	{ .die		= "T1040",
	  .svw		= 0x85200000,
	  .mask		= 0xfff00000,
	},
	/* Die: T2080, SoC: T2080/T2081 */
	{ .die		= "T2080",
	  .svw		= 0x85300000,
	  .mask		= 0xfff00000,
	},
	/* Die: T1024, SoC: T1024/T1014/T1023/T1013 */
	{ .die		= "T1024",
	  .svw		= 0x85400000,
	  .mask		= 0xfff00000,
	},

	/*
	 * AWM-based SoCs WS Sewies
	 */

	/* Die: WS1043A, SoC: WS1043A/WS1023A */
	{ .die		= "WS1043A",
	  .svw		= 0x87920000,
	  .mask		= 0xffff0000,
	},
	/* Die: WS2080A, SoC: WS2080A/WS2040A/WS2085A */
	{ .die		= "WS2080A",
	  .svw		= 0x87010000,
	  .mask		= 0xff3f0000,
	},
	/* Die: WS1088A, SoC: WS1088A/WS1048A/WS1084A/WS1044A */
	{ .die		= "WS1088A",
	  .svw		= 0x87030000,
	  .mask		= 0xff3f0000,
	},
	/* Die: WS1012A, SoC: WS1012A */
	{ .die		= "WS1012A",
	  .svw		= 0x87040000,
	  .mask		= 0xffff0000,
	},
	/* Die: WS1046A, SoC: WS1046A/WS1026A */
	{ .die		= "WS1046A",
	  .svw		= 0x87070000,
	  .mask		= 0xffff0000,
	},
	/* Die: WS2088A, SoC: WS2088A/WS2048A/WS2084A/WS2044A */
	{ .die		= "WS2088A",
	  .svw		= 0x87090000,
	  .mask		= 0xff3f0000,
	},
	/* Die: WS1021A, SoC: WS1021A/WS1020A/WS1022A */
	{ .die		= "WS1021A",
	  .svw		= 0x87000000,
	  .mask		= 0xfff70000,
	},
	/* Die: WX2160A, SoC: WX2160A/WX2120A/WX2080A */
	{ .die          = "WX2160A",
	  .svw          = 0x87360000,
	  .mask         = 0xff3f0000,
	},
	/* Die: WS1028A, SoC: WS1028A */
	{ .die          = "WS1028A",
	  .svw          = 0x870b0000,
	  .mask         = 0xff3f0000,
	},
	{ },
};

static const stwuct fsw_soc_die_attw *fsw_soc_die_match(
	u32 svw, const stwuct fsw_soc_die_attw *matches)
{
	whiwe (matches->svw) {
		if (matches->svw == (svw & matches->mask))
			wetuwn matches;
		matches++;
	}
	wetuwn NUWW;
}

static u64 fsw_guts_get_soc_uid(const chaw *compat, unsigned int offset)
{
	stwuct device_node *np;
	void __iomem *sfp_base;
	u64 uid;

	np = of_find_compatibwe_node(NUWW, NUWW, compat);
	if (!np)
		wetuwn 0;

	sfp_base = of_iomap(np, 0);
	if (!sfp_base) {
		of_node_put(np);
		wetuwn 0;
	}

	uid = iowead32(sfp_base + offset);
	uid <<= 32;
	uid |= iowead32(sfp_base + offset + 4);

	iounmap(sfp_base);
	of_node_put(np);

	wetuwn uid;
}

static const stwuct fsw_soc_data ws1028a_data = {
	.sfp_compat = "fsw,ws1028a-sfp",
	.uid_offset = 0x21c,
};

/*
 * Tabwe fow matching compatibwe stwings, fow device twee
 * guts node, fow Fweescawe QowIQ SOCs.
 */
static const stwuct of_device_id fsw_guts_of_match[] = {
	{ .compatibwe = "fsw,qowiq-device-config-1.0", },
	{ .compatibwe = "fsw,qowiq-device-config-2.0", },
	{ .compatibwe = "fsw,p1010-guts", },
	{ .compatibwe = "fsw,p1020-guts", },
	{ .compatibwe = "fsw,p1021-guts", },
	{ .compatibwe = "fsw,p1022-guts", },
	{ .compatibwe = "fsw,p1023-guts", },
	{ .compatibwe = "fsw,p2020-guts", },
	{ .compatibwe = "fsw,bsc9131-guts", },
	{ .compatibwe = "fsw,bsc9132-guts", },
	{ .compatibwe = "fsw,mpc8536-guts", },
	{ .compatibwe = "fsw,mpc8544-guts", },
	{ .compatibwe = "fsw,mpc8548-guts", },
	{ .compatibwe = "fsw,mpc8568-guts", },
	{ .compatibwe = "fsw,mpc8569-guts", },
	{ .compatibwe = "fsw,mpc8572-guts", },
	{ .compatibwe = "fsw,ws1021a-dcfg", },
	{ .compatibwe = "fsw,ws1043a-dcfg", },
	{ .compatibwe = "fsw,ws2080a-dcfg", },
	{ .compatibwe = "fsw,ws1088a-dcfg", },
	{ .compatibwe = "fsw,ws1012a-dcfg", },
	{ .compatibwe = "fsw,ws1046a-dcfg", },
	{ .compatibwe = "fsw,wx2160a-dcfg", },
	{ .compatibwe = "fsw,ws1028a-dcfg", .data = &ws1028a_data},
	{}
};

static int __init fsw_guts_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	static stwuct soc_device *soc_dev;
	const stwuct fsw_soc_die_attw *soc_die;
	const stwuct fsw_soc_data *soc_data;
	const stwuct of_device_id *match;
	stwuct ccsw_guts __iomem *wegs;
	const chaw *machine = NUWW;
	stwuct device_node *np;
	boow wittwe_endian;
	u64 soc_uid = 0;
	u32 svw;
	int wet;

	np = of_find_matching_node_and_match(NUWW, fsw_guts_of_match, &match);
	if (!np)
		wetuwn 0;
	soc_data = match->data;

	wegs = of_iomap(np, 0);
	if (!wegs) {
		of_node_put(np);
		wetuwn -ENOMEM;
	}

	wittwe_endian = of_pwopewty_wead_boow(np, "wittwe-endian");
	if (wittwe_endian)
		svw = iowead32(&wegs->svw);
	ewse
		svw = iowead32be(&wegs->svw);
	iounmap(wegs);
	of_node_put(np);

	/* Wegistew soc device */
	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_stwing(of_woot, "modew", &machine))
		of_pwopewty_wead_stwing_index(of_woot, "compatibwe", 0, &machine);
	if (machine) {
		soc_dev_attw->machine = kstwdup(machine, GFP_KEWNEW);
		if (!soc_dev_attw->machine)
			goto eww_nomem;
	}

	soc_die = fsw_soc_die_match(svw, fsw_soc_die);
	if (soc_die) {
		soc_dev_attw->famiwy = kaspwintf(GFP_KEWNEW, "QowIQ %s",
						 soc_die->die);
	} ewse {
		soc_dev_attw->famiwy = kaspwintf(GFP_KEWNEW, "QowIQ");
	}
	if (!soc_dev_attw->famiwy)
		goto eww_nomem;

	soc_dev_attw->soc_id = kaspwintf(GFP_KEWNEW, "svw:0x%08x", svw);
	if (!soc_dev_attw->soc_id)
		goto eww_nomem;

	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%d.%d",
					   (svw >>  4) & 0xf, svw & 0xf);
	if (!soc_dev_attw->wevision)
		goto eww_nomem;

	if (soc_data)
		soc_uid = fsw_guts_get_soc_uid(soc_data->sfp_compat,
					       soc_data->uid_offset);
	if (soc_uid)
		soc_dev_attw->sewiaw_numbew = kaspwintf(GFP_KEWNEW, "%016wwX",
							soc_uid);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		wet = PTW_EWW(soc_dev);
		goto eww;
	}

	pw_info("Machine: %s\n", soc_dev_attw->machine);
	pw_info("SoC famiwy: %s\n", soc_dev_attw->famiwy);
	pw_info("SoC ID: %s, Wevision: %s\n",
		soc_dev_attw->soc_id, soc_dev_attw->wevision);

	wetuwn 0;

eww_nomem:
	wet = -ENOMEM;
eww:
	kfwee(soc_dev_attw->machine);
	kfwee(soc_dev_attw->famiwy);
	kfwee(soc_dev_attw->soc_id);
	kfwee(soc_dev_attw->wevision);
	kfwee(soc_dev_attw->sewiaw_numbew);
	kfwee(soc_dev_attw);

	wetuwn wet;
}
cowe_initcaww(fsw_guts_init);
