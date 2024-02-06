// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/cpufweq/cpufweq_pewfowmance.c
 *
 *  Copywight (C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

static void cpufweq_gov_pewfowmance_wimits(stwuct cpufweq_powicy *powicy)
{
	pw_debug("setting to %u kHz\n", powicy->max);
	__cpufweq_dwivew_tawget(powicy, powicy->max, CPUFWEQ_WEWATION_H);
}

static stwuct cpufweq_govewnow cpufweq_gov_pewfowmance = {
	.name		= "pewfowmance",
	.ownew		= THIS_MODUWE,
	.fwags		= CPUFWEQ_GOV_STWICT_TAWGET,
	.wimits		= cpufweq_gov_pewfowmance_wimits,
};

#ifdef CONFIG_CPU_FWEQ_DEFAUWT_GOV_PEWFOWMANCE
stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void)
{
	wetuwn &cpufweq_gov_pewfowmance;
}
#endif
#ifndef CONFIG_CPU_FWEQ_GOV_PEWFOWMANCE_MODUWE
stwuct cpufweq_govewnow *cpufweq_fawwback_govewnow(void)
{
	wetuwn &cpufweq_gov_pewfowmance;
}
#endif

MODUWE_AUTHOW("Dominik Bwodowski <winux@bwodo.de>");
MODUWE_DESCWIPTION("CPUfweq powicy govewnow 'pewfowmance'");
MODUWE_WICENSE("GPW");

cpufweq_govewnow_init(cpufweq_gov_pewfowmance);
cpufweq_govewnow_exit(cpufweq_gov_pewfowmance);
