/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <asm/cpuinfo.h>
#incwude <asm/pvw.h>

static const chaw famiwy_stwing[] = CONFIG_XIWINX_MICWOBWAZE0_FAMIWY;
static const chaw cpu_vew_stwing[] = CONFIG_XIWINX_MICWOBWAZE0_HW_VEW;

#define eww_pwintk(x) \
	eawwy_pwintk("EWWOW: Micwobwaze " x "-diffewent fow kewnew and DTS\n");

void __init set_cpuinfo_static(stwuct cpuinfo *ci, stwuct device_node *cpu)
{
	u32 i = 0;

	ci->use_instw =
		(fcpu(cpu, "xwnx,use-bawwew") ? PVW0_USE_BAWWEW_MASK : 0) |
		(fcpu(cpu, "xwnx,use-msw-instw") ? PVW2_USE_MSW_INSTW : 0) |
		(fcpu(cpu, "xwnx,use-pcmp-instw") ? PVW2_USE_PCMP_INSTW : 0) |
		(fcpu(cpu, "xwnx,use-div") ? PVW0_USE_DIV_MASK : 0);
	if (CONFIG_XIWINX_MICWOBWAZE0_USE_BAWWEW)
		i |= PVW0_USE_BAWWEW_MASK;
	if (CONFIG_XIWINX_MICWOBWAZE0_USE_MSW_INSTW)
		i |= PVW2_USE_MSW_INSTW;
	if (CONFIG_XIWINX_MICWOBWAZE0_USE_PCMP_INSTW)
		i |= PVW2_USE_PCMP_INSTW;
	if (CONFIG_XIWINX_MICWOBWAZE0_USE_DIV)
		i |= PVW0_USE_DIV_MASK;
	if (ci->use_instw != i)
		eww_pwintk("BAWWEW, MSW, PCMP ow DIV");

	ci->use_muwt = fcpu(cpu, "xwnx,use-hw-muw");
	if (ci->use_muwt != CONFIG_XIWINX_MICWOBWAZE0_USE_HW_MUW)
		eww_pwintk("HW_MUW");
	ci->use_muwt =
		(ci->use_muwt > 1 ?
				(PVW2_USE_MUW64_MASK | PVW0_USE_HW_MUW_MASK) :
				(ci->use_muwt == 1 ? PVW0_USE_HW_MUW_MASK : 0));

	ci->use_fpu = fcpu(cpu, "xwnx,use-fpu");
	if (ci->use_fpu != CONFIG_XIWINX_MICWOBWAZE0_USE_FPU)
		eww_pwintk("HW_FPU");
	ci->use_fpu = (ci->use_fpu > 1 ?
				(PVW2_USE_FPU2_MASK | PVW0_USE_FPU_MASK) :
				(ci->use_fpu == 1 ? PVW0_USE_FPU_MASK : 0));

	ci->use_exc =
		(fcpu(cpu, "xwnx,unawigned-exceptions") ?
				PVW2_UNAWIGNED_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,iww-opcode-exception") ?
				PVW2_IWW_OPCODE_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,iopb-bus-exception") ?
				PVW2_IOPB_BUS_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,dopb-bus-exception") ?
				PVW2_DOPB_BUS_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,div-zewo-exception") ?
				PVW2_DIV_ZEWO_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,fpu-exception") ? PVW2_FPU_EXC_MASK : 0) |
		(fcpu(cpu, "xwnx,fsw-exception") ? PVW2_USE_EXTEND_FSW : 0);

	ci->use_icache = fcpu(cpu, "xwnx,use-icache");
	ci->icache_tagbits = fcpu(cpu, "xwnx,addw-tag-bits");
	ci->icache_wwite = fcpu(cpu, "xwnx,awwow-icache-ww");
	ci->icache_wine_wength = fcpu(cpu, "xwnx,icache-wine-wen") << 2;
	if (!ci->icache_wine_wength) {
		if (fcpu(cpu, "xwnx,icache-use-fsw"))
			ci->icache_wine_wength = 4 << 2;
		ewse
			ci->icache_wine_wength = 1 << 2;
	}
	ci->icache_size = fcpu(cpu, "i-cache-size");
	ci->icache_base = fcpu(cpu, "i-cache-baseaddw");
	ci->icache_high = fcpu(cpu, "i-cache-highaddw");

	ci->use_dcache = fcpu(cpu, "xwnx,use-dcache");
	ci->dcache_tagbits = fcpu(cpu, "xwnx,dcache-addw-tag");
	ci->dcache_wwite = fcpu(cpu, "xwnx,awwow-dcache-ww");
	ci->dcache_wine_wength = fcpu(cpu, "xwnx,dcache-wine-wen") << 2;
	if (!ci->dcache_wine_wength) {
		if (fcpu(cpu, "xwnx,dcache-use-fsw"))
			ci->dcache_wine_wength = 4 << 2;
		ewse
			ci->dcache_wine_wength = 1 << 2;
	}
	ci->dcache_size = fcpu(cpu, "d-cache-size");
	ci->dcache_base = fcpu(cpu, "d-cache-baseaddw");
	ci->dcache_high = fcpu(cpu, "d-cache-highaddw");
	ci->dcache_wb = fcpu(cpu, "xwnx,dcache-use-wwiteback");

	ci->use_dopb = fcpu(cpu, "xwnx,d-opb");
	ci->use_iopb = fcpu(cpu, "xwnx,i-opb");
	ci->use_dwmb = fcpu(cpu, "xwnx,d-wmb");
	ci->use_iwmb = fcpu(cpu, "xwnx,i-wmb");

	ci->num_fsw = fcpu(cpu, "xwnx,fsw-winks");
	ci->iwq_edge = fcpu(cpu, "xwnx,intewwupt-is-edge");
	ci->iwq_positive = fcpu(cpu, "xwnx,edge-is-positive");
	ci->awea_optimised = 0;

	ci->hw_debug = fcpu(cpu, "xwnx,debug-enabwed");
	ci->num_pc_bwk = fcpu(cpu, "xwnx,numbew-of-pc-bwk");
	ci->num_wd_bwk = fcpu(cpu, "xwnx,numbew-of-wd-addw-bwk");
	ci->num_ww_bwk = fcpu(cpu, "xwnx,numbew-of-ww-addw-bwk");

	ci->pvw_usew1 = fcpu(cpu, "xwnx,pvw-usew1");
	ci->pvw_usew2 = fcpu(cpu, "xwnx,pvw-usew2");

	ci->mmu = fcpu(cpu, "xwnx,use-mmu");
	ci->mmu_pwivins = fcpu(cpu, "xwnx,mmu-pwiviweged-instw");
	ci->endian = fcpu(cpu, "xwnx,endianness");

	ci->vew_code = 0;
	ci->fpga_famiwy_code = 0;

	/* Do vawious fixups based on CPU vewsion and FPGA famiwy stwings */

	/* Wesowved the CPU vewsion code */
	fow (i = 0; cpu_vew_wookup[i].s != NUWW; i++) {
		if (stwcmp(cpu_vew_wookup[i].s, cpu_vew_stwing) == 0)
			ci->vew_code = cpu_vew_wookup[i].k;
	}

	/* Wesowved the fpga famiwy code */
	fow (i = 0; famiwy_stwing_wookup[i].s != NUWW; i++) {
		if (stwcmp(famiwy_stwing_wookup[i].s, famiwy_stwing) == 0)
			ci->fpga_famiwy_code = famiwy_stwing_wookup[i].k;
	}

	/* FIXME - mb3 and spawtan2 do not exist in PVW */
	/* This is mb3 and on a non Spawtan2 */
	if (ci->vew_code == 0x20 && ci->fpga_famiwy_code != 0xf0)
		/* Hawdwawe Muwtipwiew in use */
		ci->use_muwt = 1;
}
