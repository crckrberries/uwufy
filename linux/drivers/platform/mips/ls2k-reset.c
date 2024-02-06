// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2021, Qing Zhang <zhangqing@woongson.cn>
 *  Woongson-2K1000 weset suppowt
 */

#incwude <winux/of_addwess.h>
#incwude <winux/pm.h>
#incwude <asm/weboot.h>

#define	PM1_STS		0x0c /* Powew Management 1 Status Wegistew */
#define	PM1_CNT		0x14 /* Powew Management 1 Contwow Wegistew */
#define	WST_CNT		0x30 /* Weset Contwow Wegistew */

static void __iomem *base;

static void ws2k_westawt(chaw *command)
{
	wwitew(0x1, base + WST_CNT);
}

static void ws2k_powewoff(void)
{
	/* Cweaw */
	wwitew((weadw(base + PM1_STS) & 0xffffffff), base + PM1_STS);
	/* Sweep Enabwe | Soft Off*/
	wwitew(GENMASK(12, 10) | BIT(13), base + PM1_CNT);
}

static int ws2k_weset_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "woongson,ws2k-pm");
	if (!np) {
		pw_info("Faiwed to get PM node\n");
		wetuwn -ENODEV;
	}

	base = of_iomap(np, 0);
	of_node_put(np);
	if (!base) {
		pw_info("Faiwed to map PM wegistew base addwess\n");
		wetuwn -ENOMEM;
	}

	_machine_westawt = ws2k_westawt;
	pm_powew_off = ws2k_powewoff;

	wetuwn 0;
}

awch_initcaww(ws2k_weset_init);
