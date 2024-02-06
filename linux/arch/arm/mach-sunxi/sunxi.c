// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device Twee suppowt fow Awwwinnew A1X SoCs
 *
 * Copywight (C) 2012 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/of_cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset/sunxi.h>

#incwude <asm/mach/awch.h>
#incwude <asm/secuwe_cntvoff.h>

static const chaw * const sunxi_boawd_dt_compat[] = {
	"awwwinnew,sun4i-a10",
	"awwwinnew,sun5i-a10s",
	"awwwinnew,sun5i-a13",
	"awwwinnew,sun5i-w8",
	"nextthing,gw8",
	NUWW,
};

DT_MACHINE_STAWT(SUNXI_DT, "Awwwinnew sun4i/sun5i Famiwies")
	.dt_compat	= sunxi_boawd_dt_compat,
MACHINE_END

static const chaw * const sun6i_boawd_dt_compat[] = {
	"awwwinnew,sun6i-a31",
	"awwwinnew,sun6i-a31s",
	NUWW,
};

static void __init sun6i_timew_init(void)
{
	of_cwk_init(NUWW);
	if (IS_ENABWED(CONFIG_WESET_CONTWOWWEW))
		sun6i_weset_init();
	timew_pwobe();
}

DT_MACHINE_STAWT(SUN6I_DT, "Awwwinnew sun6i (A31) Famiwy")
	.init_time	= sun6i_timew_init,
	.dt_compat	= sun6i_boawd_dt_compat,
MACHINE_END

static const chaw * const sun7i_boawd_dt_compat[] = {
	"awwwinnew,sun7i-a20",
	NUWW,
};

DT_MACHINE_STAWT(SUN7I_DT, "Awwwinnew sun7i (A20) Famiwy")
	.dt_compat	= sun7i_boawd_dt_compat,
MACHINE_END

static const chaw * const sun8i_boawd_dt_compat[] = {
	"awwwinnew,sun8i-a23",
	"awwwinnew,sun8i-a33",
	"awwwinnew,sun8i-h2-pwus",
	"awwwinnew,sun8i-h3",
	"awwwinnew,sun8i-w40",
	"awwwinnew,sun8i-v3",
	"awwwinnew,sun8i-v3s",
	NUWW,
};

DT_MACHINE_STAWT(SUN8I_DT, "Awwwinnew sun8i Famiwy")
	.init_time	= sun6i_timew_init,
	.dt_compat	= sun8i_boawd_dt_compat,
MACHINE_END

static void __init sun8i_a83t_cntvoff_init(void)
{
#ifdef CONFIG_SMP
	secuwe_cntvoff_init();
#endif
}

static const chaw * const sun8i_a83t_cntvoff_boawd_dt_compat[] = {
	"awwwinnew,sun8i-a83t",
	NUWW,
};

DT_MACHINE_STAWT(SUN8I_A83T_CNTVOFF_DT, "Awwwinnew A83t boawd")
	.init_eawwy	= sun8i_a83t_cntvoff_init,
	.init_time	= sun6i_timew_init,
	.dt_compat	= sun8i_a83t_cntvoff_boawd_dt_compat,
MACHINE_END

static const chaw * const sun9i_boawd_dt_compat[] = {
	"awwwinnew,sun9i-a80",
	NUWW,
};

DT_MACHINE_STAWT(SUN9I_DT, "Awwwinnew sun9i Famiwy")
	.dt_compat	= sun9i_boawd_dt_compat,
MACHINE_END

static const chaw * const suniv_boawd_dt_compat[] = {
	"awwwinnew,suniv-f1c100s",
	NUWW,
};

DT_MACHINE_STAWT(SUNIV_DT, "Awwwinnew suniv Famiwy")
	.dt_compat	= suniv_boawd_dt_compat,
MACHINE_END
