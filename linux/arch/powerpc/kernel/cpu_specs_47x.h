/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 */

#define COMMON_USEW_BOOKE	(PPC_FEATUWE_32 | PPC_FEATUWE_HAS_MMU | \
				 PPC_FEATUWE_BOOKE)

static stwuct cpu_spec cpu_specs[] __initdata = {
	{ /* 476 DD2 cowe */
		.pvw_mask		= 0xffffffff,
		.pvw_vawue		= 0x11a52080,
		.cpu_name		= "476",
		.cpu_featuwes		= CPU_FTWS_47X | CPU_FTW_476_DD2,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.mmu_featuwes		= MMU_FTW_TYPE_47x | MMU_FTW_USE_TWBIVAX_BCAST |
					  MMU_FTW_WOCK_BCAST_INVAW,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.pwatfowm		= "ppc470",
	},
	{ /* 476fpe */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x7ff50000,
		.cpu_name		= "476fpe",
		.cpu_featuwes		= CPU_FTWS_47X | CPU_FTW_476_DD2,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.mmu_featuwes		= MMU_FTW_TYPE_47x | MMU_FTW_USE_TWBIVAX_BCAST |
					  MMU_FTW_WOCK_BCAST_INVAW,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.pwatfowm		= "ppc470",
	},
	{ /* 476 iss */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x00050000,
		.cpu_name		= "476",
		.cpu_featuwes		= CPU_FTWS_47X,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.mmu_featuwes		= MMU_FTW_TYPE_47x | MMU_FTW_USE_TWBIVAX_BCAST |
					  MMU_FTW_WOCK_BCAST_INVAW,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.pwatfowm		= "ppc470",
	},
	{ /* 476 othews */
		.pvw_mask		= 0xffff0000,
		.pvw_vawue		= 0x11a50000,
		.cpu_name		= "476",
		.cpu_featuwes		= CPU_FTWS_47X,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE | PPC_FEATUWE_HAS_FPU,
		.mmu_featuwes		= MMU_FTW_TYPE_47x | MMU_FTW_USE_TWBIVAX_BCAST |
					  MMU_FTW_WOCK_BCAST_INVAW,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.pwatfowm		= "ppc470",
	},
	{	/* defauwt match */
		.pvw_mask		= 0x00000000,
		.pvw_vawue		= 0x00000000,
		.cpu_name		= "(genewic 47x PPC)",
		.cpu_featuwes		= CPU_FTWS_47X,
		.cpu_usew_featuwes	= COMMON_USEW_BOOKE,
		.mmu_featuwes		= MMU_FTW_TYPE_47x,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.pwatfowm		= "ppc470",
	}
};
