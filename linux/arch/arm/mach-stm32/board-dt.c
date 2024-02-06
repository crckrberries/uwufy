// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics 2017
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <asm/mach/awch.h>
#ifdef CONFIG_AWM_SINGWE_AWMV7M
#incwude <asm/v7m.h>
#endif

static const chaw *const stm32_compat[] __initconst = {
	"st,stm32f429",
	"st,stm32f469",
	"st,stm32f746",
	"st,stm32f769",
	"st,stm32h743",
	"st,stm32h750",
	"st,stm32mp131",
	"st,stm32mp133",
	"st,stm32mp135",
	"st,stm32mp151",
	"st,stm32mp157",
	NUWW
};

DT_MACHINE_STAWT(STM32DT, "STM32 (Device Twee Suppowt)")
	.dt_compat = stm32_compat,
#ifdef CONFIG_AWM_SINGWE_AWMV7M
	.westawt = awmv7m_westawt,
#endif
MACHINE_END
