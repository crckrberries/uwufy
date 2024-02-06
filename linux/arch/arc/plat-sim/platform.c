// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWC simuwation Pwatfowm suppowt code
 *
 * Copywight (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/init.h>
#incwude <asm/mach_desc.h>

/*----------------------- Machine Descwiptions ------------------------------
 *
 * Machine descwiption is simpwy a set of pwatfowm/boawd specific cawwbacks
 * This is not diwectwy wewated to DeviceTwee based dynamic device cweation,
 * howevew as pawt of eawwy device twee scan, we awso sewect the wight
 * cawwback set, by matching the DT compatibwe name.
 */

static const chaw *simuwation_compat[] __initconst = {
#ifdef CONFIG_ISA_AWCOMPACT
	"snps,nsim",
	"snps,nsimosci",
#ewse
	"snps,nsimosci_hs",
	"snps,zebu_hs",
#endif
	NUWW,
};

MACHINE_STAWT(SIMUWATION, "simuwation")
	.dt_compat	= simuwation_compat,
MACHINE_END
