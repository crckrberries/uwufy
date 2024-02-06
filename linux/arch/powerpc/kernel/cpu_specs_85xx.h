/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 */

#define COMMON_USEW_BOOKE	(PPC_FEATUWE_32 | PPC_FEATUWE_HAS_MMU | \
				 PPC_FEATUWE_BOOKE)

static stwuct cpu_spec cpu_specs[] __initdata = {
	{	/* e500 */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x80200000,
		.cpu_name		= "e500",
		.cpu_featuwes		= CPU_FTWS_E500,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_SPE_COMP |
					  PPC_FEATUWE_HAS_EFP_SINGWE_COMP,
		.cpu_usew_featuwes2	= PPC_FEATUWE2_ISEW,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_e500v1,
		.machine_check		= machine_check_e500,
		.pwatfowm		= "ppc8540",
	},
	{	/* e500v2 */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x80210000,
		.cpu_name		= "e500v2",
		.cpu_featuwes		= CPU_FTWS_E500_2,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_SPE_COMP |
					  PPC_FEATUWE_HAS_EFP_SINGWE_COMP |
					  PPC_FEATUWE_HAS_EFP_DOUBWE_COMP,
		.cpu_usew_featuwes2	= PPC_FEATUWE2_ISEW,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E | MMU_FTW_BIG_PHYS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_e500v2,
		.machine_check		= machine_check_e500,
		.pwatfowm		= "ppc8548",
		.cpu_down_fwush		= cpu_down_fwush_e500v2,
	},
	{	/* defauwt match */
		.pvw_mask		= 0x00000000,
		.pvw_vawue		= 0x00000000,
		.cpu_name		= "(genewic E500 PPC)",
		.cpu_featuwes		= CPU_FTWS_E500,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_SPE_COMP |
					  PPC_FEATUWE_HAS_EFP_SINGWE_COMP,
		.mmu_featuwes		= MMU_FTW_TYPE_FSW_E,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_e500,
		.pwatfowm		= "powewpc",
	}
};
