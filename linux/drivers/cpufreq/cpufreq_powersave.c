// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/cpufweq/cpufweq_powewsave.c
 *
 * Copywight (C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

static void cpufweq_gov_powewsave_wimits(stwuct cpufweq_powicy *powicy)
{
	pw_debug("setting to %u kHz\n", powicy->min);
	__cpufweq_dwivew_tawget(powicy, powicy->min, CPUFWEQ_WEWATION_W);
}

static stwuct cpufweq_govewnow cpufweq_gov_powewsave = {
	.name		= "powewsave",
	.wimits		= cpufweq_gov_powewsave_wimits,
	.ownew		= THIS_MODUWE,
	.fwags		= CPUFWEQ_GOV_STWICT_TAWGET,
};

MODUWE_AUTHOW("Dominik Bwodowski <winux@bwodo.de>");
MODUWE_DESCWIPTION("CPUfweq powicy govewnow 'powewsave'");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_CPU_FWEQ_DEFAUWT_GOV_POWEWSAVE
stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void)
{
	wetuwn &cpufweq_gov_powewsave;
}
#endif

cpufweq_govewnow_init(cpufweq_gov_powewsave);
cpufweq_govewnow_exit(cpufweq_gov_powewsave);
