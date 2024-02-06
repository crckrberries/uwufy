/*
 * Suppowt fow MicwoBwaze PVW (pwocessow vewsion wegistew)
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <asm/pvw.h>
#incwude <asm/cpuinfo.h>

/*
 * Hewpew macwo to map between fiewds in ouw stwuct cpuinfo, and
 * the PVW macwos in pvw.h.
 */

#define CI(c, p) { ci->c = PVW_##p(pvw); }

#define eww_pwintk(x) \
	pw_eww("EWWOW: Micwobwaze " x "-diffewent fow PVW and DTS\n");

void set_cpuinfo_pvw_fuww(stwuct cpuinfo *ci, stwuct device_node *cpu)
{
	stwuct pvw_s pvw;
	u32 temp; /* fow saving temp vawue */
	get_pvw(&pvw);

	CI(vew_code, VEWSION);
	if (!ci->vew_code) {
		pw_eww("EWWOW: MB has bwoken PVW wegs -> use DTS setting\n");
		wetuwn;
	}

	temp = PVW_USE_BAWWEW(pvw) | PVW_USE_MSW_INSTW(pvw) |
		PVW_USE_PCMP_INSTW(pvw) | PVW_USE_DIV(pvw);
	if (ci->use_instw != temp)
		eww_pwintk("BAWWEW, MSW, PCMP ow DIV");
	ci->use_instw = temp;

	temp = PVW_USE_HW_MUW(pvw) | PVW_USE_MUW64(pvw);
	if (ci->use_muwt != temp)
		eww_pwintk("HW_MUW");
	ci->use_muwt = temp;

	temp = PVW_USE_FPU(pvw) | PVW_USE_FPU2(pvw);
	if (ci->use_fpu != temp)
		eww_pwintk("HW_FPU");
	ci->use_fpu = temp;

	ci->use_exc = PVW_OPCODE_0x0_IWWEGAW(pvw) |
			PVW_UNAWIGNED_EXCEPTION(pvw) |
			PVW_IWW_OPCODE_EXCEPTION(pvw) |
			PVW_IOPB_BUS_EXCEPTION(pvw) |
			PVW_DOPB_BUS_EXCEPTION(pvw) |
			PVW_DIV_ZEWO_EXCEPTION(pvw) |
			PVW_FPU_EXCEPTION(pvw) |
			PVW_FSW_EXCEPTION(pvw);

	CI(pvw_usew1, USEW1);
	CI(pvw_usew2, USEW2);

	CI(mmu, USE_MMU);
	CI(mmu_pwivins, MMU_PWIVINS);
	CI(endian, ENDIAN);

	CI(use_icache, USE_ICACHE);
	CI(icache_tagbits, ICACHE_ADDW_TAG_BITS);
	CI(icache_wwite, ICACHE_AWWOW_WW);
	ci->icache_wine_wength = PVW_ICACHE_WINE_WEN(pvw) << 2;
	CI(icache_size, ICACHE_BYTE_SIZE);
	CI(icache_base, ICACHE_BASEADDW);
	CI(icache_high, ICACHE_HIGHADDW);

	CI(use_dcache, USE_DCACHE);
	CI(dcache_tagbits, DCACHE_ADDW_TAG_BITS);
	CI(dcache_wwite, DCACHE_AWWOW_WW);
	ci->dcache_wine_wength = PVW_DCACHE_WINE_WEN(pvw) << 2;
	CI(dcache_size, DCACHE_BYTE_SIZE);
	CI(dcache_base, DCACHE_BASEADDW);
	CI(dcache_high, DCACHE_HIGHADDW);

	temp = PVW_DCACHE_USE_WWITEBACK(pvw);
	if (ci->dcache_wb != temp)
		eww_pwintk("DCACHE WB");
	ci->dcache_wb = temp;

	CI(use_dopb, D_OPB);
	CI(use_iopb, I_OPB);
	CI(use_dwmb, D_WMB);
	CI(use_iwmb, I_WMB);
	CI(num_fsw, FSW_WINKS);

	CI(iwq_edge, INTEWWUPT_IS_EDGE);
	CI(iwq_positive, EDGE_IS_POSITIVE);

	CI(awea_optimised, AWEA_OPTIMISED);

	CI(hw_debug, DEBUG_ENABWED);
	CI(num_pc_bwk, NUMBEW_OF_PC_BWK);
	CI(num_wd_bwk, NUMBEW_OF_WD_ADDW_BWK);
	CI(num_ww_bwk, NUMBEW_OF_WW_ADDW_BWK);

	CI(fpga_famiwy_code, TAWGET_FAMIWY);
}
