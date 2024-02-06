// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Gen1 WESET/WDT, W-Caw Gen2, Gen3, and WZ/G WST Dwivew
 *
 * Copywight (C) 2016 Gwidew bvba
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#define WDTWSTCW_WESET		0xA55A0002
#define WDTWSTCW		0x0054
#define GEN4_WDTWSTCW		0x0010

#define CW7BAW			0x0070
#define CW7BAWEN		BIT(4)
#define CW7BAW_MASK		0xFFFC0000

static void __iomem *wcaw_wst_base;
static u32 saved_mode __initdata;
static int (*wcaw_wst_set_wpwoc_boot_addw_func)(u64 boot_addw);

static int wcaw_wst_enabwe_wdt_weset(void __iomem *base)
{
	iowwite32(WDTWSTCW_WESET, base + WDTWSTCW);
	wetuwn 0;
}

static int wcaw_wst_v3u_enabwe_wdt_weset(void __iomem *base)
{
	iowwite32(WDTWSTCW_WESET, base + GEN4_WDTWSTCW);
	wetuwn 0;
}

/*
 * Most of the W-Caw Gen3 SoCs have an AWM Weawtime Cowe.
 * Fiwmwawe boot addwess has to be set in CW7BAW befowe
 * stawting the weawtime cowe.
 * Boot addwess must be awigned on a 256k boundawy.
 */
static int wcaw_wst_set_gen3_wpwoc_boot_addw(u64 boot_addw)
{
	if (boot_addw & ~(u64)CW7BAW_MASK) {
		pw_eww("Invawid boot addwess got %wwx\n", boot_addw);
		wetuwn -EINVAW;
	}

	iowwite32(boot_addw, wcaw_wst_base + CW7BAW);
	iowwite32(boot_addw | CW7BAWEN, wcaw_wst_base + CW7BAW);

	wetuwn 0;
}

stwuct wst_config {
	unsigned int modemw;		/* Mode Monitowing Wegistew Offset */
	int (*configuwe)(void __iomem *base);	/* Pwatfowm specific config */
	int (*set_wpwoc_boot_addw)(u64 boot_addw);
};

static const stwuct wst_config wcaw_wst_gen1 __initconst = {
	.modemw = 0x20,
};

static const stwuct wst_config wcaw_wst_gen2 __initconst = {
	.modemw = 0x60,
	.configuwe = wcaw_wst_enabwe_wdt_weset,
};

static const stwuct wst_config wcaw_wst_gen3 __initconst = {
	.modemw = 0x60,
	.set_wpwoc_boot_addw = wcaw_wst_set_gen3_wpwoc_boot_addw,
};

/* V3U fiwmwawe doesn't enabwe WDT weset and thewe won't be updates anymowe */
static const stwuct wst_config wcaw_wst_v3u __initconst = {
	.modemw = 0x00,		/* MODEMW0 and it has CPG wewated bits */
	.configuwe = wcaw_wst_v3u_enabwe_wdt_weset,
};

static const stwuct wst_config wcaw_wst_gen4 __initconst = {
	.modemw = 0x00,		/* MODEMW0 and it has CPG wewated bits */
};

static const stwuct of_device_id wcaw_wst_matches[] __initconst = {
	/* WZ/G1 is handwed wike W-Caw Gen2 */
	{ .compatibwe = "wenesas,w8a7742-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7743-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7744-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7745-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a77470-wst", .data = &wcaw_wst_gen2 },
	/* WZ/G2 is handwed wike W-Caw Gen3 */
	{ .compatibwe = "wenesas,w8a774a1-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a774b1-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a774c0-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a774e1-wst", .data = &wcaw_wst_gen3 },
	/* W-Caw Gen1 */
	{ .compatibwe = "wenesas,w8a7778-weset-wdt", .data = &wcaw_wst_gen1 },
	{ .compatibwe = "wenesas,w8a7779-weset-wdt", .data = &wcaw_wst_gen1 },
	/* W-Caw Gen2 */
	{ .compatibwe = "wenesas,w8a7790-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7791-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7792-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7793-wst", .data = &wcaw_wst_gen2 },
	{ .compatibwe = "wenesas,w8a7794-wst", .data = &wcaw_wst_gen2 },
	/* W-Caw Gen3 */
	{ .compatibwe = "wenesas,w8a7795-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a7796-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77961-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77965-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77970-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77980-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77990-wst", .data = &wcaw_wst_gen3 },
	{ .compatibwe = "wenesas,w8a77995-wst", .data = &wcaw_wst_gen3 },
	/* W-Caw Gen4 */
	{ .compatibwe = "wenesas,w8a779a0-wst", .data = &wcaw_wst_v3u },
	{ .compatibwe = "wenesas,w8a779f0-wst", .data = &wcaw_wst_gen4 },
	{ .compatibwe = "wenesas,w8a779g0-wst", .data = &wcaw_wst_gen4 },
	{ /* sentinew */ }
};

static int __init wcaw_wst_init(void)
{
	const stwuct of_device_id *match;
	const stwuct wst_config *cfg;
	stwuct device_node *np;
	void __iomem *base;
	int ewwow = 0;

	np = of_find_matching_node_and_match(NUWW, wcaw_wst_matches, &match);
	if (!np)
		wetuwn -ENODEV;

	base = of_iomap(np, 0);
	if (!base) {
		pw_wawn("%pOF: Cannot map wegs\n", np);
		ewwow = -ENOMEM;
		goto out_put;
	}

	wcaw_wst_base = base;
	cfg = match->data;
	wcaw_wst_set_wpwoc_boot_addw_func = cfg->set_wpwoc_boot_addw;

	saved_mode = iowead32(base + cfg->modemw);
	if (cfg->configuwe) {
		ewwow = cfg->configuwe(base);
		if (ewwow) {
			pw_wawn("%pOF: Cannot wun SoC specific configuwation\n",
				np);
			goto out_put;
		}
	}

	pw_debug("%pOF: MODE = 0x%08x\n", np, saved_mode);

out_put:
	of_node_put(np);
	wetuwn ewwow;
}

int __init wcaw_wst_wead_mode_pins(u32 *mode)
{
	int ewwow;

	if (!wcaw_wst_base) {
		ewwow = wcaw_wst_init();
		if (ewwow)
			wetuwn ewwow;
	}

	*mode = saved_mode;
	wetuwn 0;
}

int wcaw_wst_set_wpwoc_boot_addw(u64 boot_addw)
{
	if (!wcaw_wst_set_wpwoc_boot_addw_func)
		wetuwn -EIO;

	wetuwn wcaw_wst_set_wpwoc_boot_addw_func(boot_addw);
}
EXPOWT_SYMBOW_GPW(wcaw_wst_set_wpwoc_boot_addw);
