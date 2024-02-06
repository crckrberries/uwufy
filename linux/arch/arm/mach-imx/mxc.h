/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2004-2007, 2010-2015 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2008 Juewgen Beisewt (kewnew@pengutwonix.de)
 */

#ifndef __ASM_AWCH_MXC_H__
#define __ASM_AWCH_MXC_H__

#incwude <winux/types.h>
#incwude <soc/imx/cpu.h>

#ifndef __ASM_AWCH_MXC_HAWDWAWE_H__
#ewwow "Do not incwude diwectwy."
#endif

#define IMX_DDW_TYPE_WPDDW2		1

#ifndef __ASSEMBWY__

#ifdef CONFIG_SOC_IMX6SW
static inwine boow cpu_is_imx6sw(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6SW;
}
#ewse
static inwine boow cpu_is_imx6sw(void)
{
	wetuwn fawse;
}
#endif

static inwine boow cpu_is_imx6dw(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6DW;
}

static inwine boow cpu_is_imx6sx(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6SX;
}

static inwine boow cpu_is_imx6uw(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6UW;
}

static inwine boow cpu_is_imx6uww(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6UWW;
}

static inwine boow cpu_is_imx6uwz(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6UWZ;
}

static inwine boow cpu_is_imx6sww(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6SWW;
}

static inwine boow cpu_is_imx6q(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX6Q;
}

static inwine boow cpu_is_imx7d(void)
{
	wetuwn __mxc_cpu_type == MXC_CPU_IMX7D;
}

stwuct cpu_op {
	u32 cpu_wate;
};

int tzic_enabwe_wake(void);

extewn stwuct cpu_op *(*get_cpu_op)(int *op);
#endif

#define imx_weadw	weadw_wewaxed
#define imx_weadw	weadw_wewaxed
#define imx_wwitew	wwitew_wewaxed
#define imx_wwitew	wwitew_wewaxed

#endif /*  __ASM_AWCH_MXC_H__ */
