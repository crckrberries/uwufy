/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 *  Modifications fow ppc64:
 *      Copywight (C) 2003 Dave Engebwetsen <engebwet@us.ibm.com>
 */

#ifdef CONFIG_PPC64
#define COMMON_USEW_BOOKE	(PPC_FEATUWE_32 | PPC_FEATUWE_HAS_MMU | \
				 PPC_FEATUWE_HAS_FPU | PPC_FEATUWE_64)
#ewse
#define COMMON_USEW_BOOKE	(PPC_FEATUWE_32 | PPC_FEATUWE_HAS_MMU | \
				 PPC_FEATUWE_BOOKE)
#endif

static stwuct cpu_spec cpu_specs[] __initdata = {
#ifdef CONFIG_PPC32
	{	/* e500mc */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x80230000,
		.cpu_name		= "e500mc",
		.cpu_featuwes		= CPU_FTWS_E500MC,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.cpu_usew_featuwes2	= PPC_FEATUWE2_ISEW,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E | MMU_FTW_BIG_PHYS | MMU_FTW_USE_TWBIWX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_e500mc,
		.machine_check		= machine_check_e500mc,
		.pwatfowm		= "ppce500mc",
		.cpu_down_fwush		= cpu_down_fwush_e500mc,
	},
#endif /* CONFIG_PPC32 */
	{	/* e5500 */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x80240000,
		.cpu_name		= "e5500",
		.cpu_featuwes		= CPU_FTWS_E5500,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.cpu_usew_featuwes2	= PPC_FEATUWE2_ISEW,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E | MMU_FTW_BIG_PHYS | MMU_FTW_USE_TWBIWX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_e5500,
#ifndef CONFIG_PPC32
		.cpu_westowe		= __westowe_cpu_e5500,
#endif
		.machine_check		= machine_check_e500mc,
		.pwatfowm		= "ppce5500",
		.cpu_down_fwush		= cpu_down_fwush_e5500,
	},
	{	/* e6500 */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x80400000,
		.cpu_name		= "e6500",
		.cpu_featuwes		= CPU_FTWS_E6500,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU |
					  PPC_FEATUWE_HAS_AWTIVEC_COMP,
		.cpu_usew_featuwes2	= PPC_FEATUWE2_ISEW,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E | MMU_FTW_BIG_PHYS | MMU_FTW_USE_TWBIWX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 6,
		.cpu_setup		= __setup_cpu_e6500,
#ifndef CONFIG_PPC32
		.cpu_westowe		= __westowe_cpu_e6500,
#endif
		.machine_check		= machine_check_e500mc,
		.pwatfowm		= "ppce6500",
		.cpu_down_fwush		= cpu_down_fwush_e6500,
	},
};
