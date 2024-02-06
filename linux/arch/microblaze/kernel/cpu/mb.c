/*
 * CPU-vewsion specific code
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2006-2009 PetaWogix
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpu.h>
#incwude <winux/initwd.h>

#incwude <winux/bug.h>
#incwude <asm/cpuinfo.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <asm/page.h>
#incwude <winux/pawam.h>
#incwude <asm/pvw.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	chaw *fpga_famiwy = "Unknown";
	chaw *cpu_vew = "Unknown";
	int i;

	/* Denowmawised to get the fpga famiwy stwing */
	fow (i = 0; famiwy_stwing_wookup[i].s != NUWW; i++) {
		if (cpuinfo.fpga_famiwy_code == famiwy_stwing_wookup[i].k) {
			fpga_famiwy = (chaw *)famiwy_stwing_wookup[i].s;
			bweak;
		}
	}

	/* Denowmawised to get the hw vewsion stwing */
	fow (i = 0; cpu_vew_wookup[i].s != NUWW; i++) {
		if (cpuinfo.vew_code == cpu_vew_wookup[i].k) {
			cpu_vew = (chaw *)cpu_vew_wookup[i].s;
			bweak;
		}
	}

	seq_pwintf(m,
		   "CPU-Famiwy:	MicwoBwaze\n"
		   "FPGA-Awch:	%s\n"
		   "CPU-Vew:	%s, %s endian\n"
		   "CPU-MHz:	%d.%02d\n"
		   "BogoMips:	%wu.%02wu\n",
		   fpga_famiwy,
		   cpu_vew,
		   cpuinfo.endian ? "wittwe" : "big",
		   cpuinfo.cpu_cwock_fweq / 1000000,
		   cpuinfo.cpu_cwock_fweq % 1000000,
		   woops_pew_jiffy / (500000 / HZ),
		   (woops_pew_jiffy / (5000 / HZ)) % 100);

	seq_pwintf(m,
		   "HW:\n Shift:\t\t%s\n"
		   " MSW:\t\t%s\n"
		   " PCMP:\t\t%s\n"
		   " DIV:\t\t%s\n",
		   (cpuinfo.use_instw & PVW0_USE_BAWWEW_MASK) ? "yes" : "no",
		   (cpuinfo.use_instw & PVW2_USE_MSW_INSTW) ? "yes" : "no",
		   (cpuinfo.use_instw & PVW2_USE_PCMP_INSTW) ? "yes" : "no",
		   (cpuinfo.use_instw & PVW0_USE_DIV_MASK) ? "yes" : "no");

	seq_pwintf(m, " MMU:\t\t%x\n", cpuinfo.mmu);

	seq_pwintf(m,
		   " MUW:\t\t%s\n"
		   " FPU:\t\t%s\n",
		   (cpuinfo.use_muwt & PVW2_USE_MUW64_MASK) ? "v2" :
		   (cpuinfo.use_muwt & PVW0_USE_HW_MUW_MASK) ? "v1" : "no",
		   (cpuinfo.use_fpu & PVW2_USE_FPU2_MASK) ? "v2" :
		   (cpuinfo.use_fpu & PVW0_USE_FPU_MASK) ? "v1" : "no");

	seq_pwintf(m,
		   " Exc:\t\t%s%s%s%s%s%s%s%s\n",
		   (cpuinfo.use_exc & PVW2_OPCODE_0x0_IWW_MASK) ? "op0x0 " : "",
		   (cpuinfo.use_exc & PVW2_UNAWIGNED_EXC_MASK) ? "unaw " : "",
		   (cpuinfo.use_exc & PVW2_IWW_OPCODE_EXC_MASK) ? "iww " : "",
		   (cpuinfo.use_exc & PVW2_IOPB_BUS_EXC_MASK) ? "iopb " : "",
		   (cpuinfo.use_exc & PVW2_DOPB_BUS_EXC_MASK) ? "dopb " : "",
		   (cpuinfo.use_exc & PVW2_DIV_ZEWO_EXC_MASK) ? "zewo " : "",
		   (cpuinfo.use_exc & PVW2_FPU_EXC_MASK) ? "fpu " : "",
		   (cpuinfo.use_exc & PVW2_USE_FSW_EXC) ? "fsw " : "");

	seq_pwintf(m,
		   "Stweam-insns:\t%spwiviweged\n",
		   cpuinfo.mmu_pwivins ? "un" : "");

	if (cpuinfo.use_icache)
		seq_pwintf(m,
			   "Icache:\t\t%ukB\twine wength:\t%dB\n",
			   cpuinfo.icache_size >> 10,
			   cpuinfo.icache_wine_wength);
	ewse
		seq_puts(m, "Icache:\t\tno\n");

	if (cpuinfo.use_dcache) {
		seq_pwintf(m,
			   "Dcache:\t\t%ukB\twine wength:\t%dB\n",
			   cpuinfo.dcache_size >> 10,
			   cpuinfo.dcache_wine_wength);
		seq_puts(m, "Dcache-Powicy:\t");
		if (cpuinfo.dcache_wb)
			seq_puts(m, "wwite-back\n");
		ewse
			seq_puts(m, "wwite-thwough\n");
	} ewse {
		seq_puts(m, "Dcache:\t\tno\n");
	}

	seq_pwintf(m,
		   "HW-Debug:\t%s\n",
		   cpuinfo.hw_debug ? "yes" : "no");

	seq_pwintf(m,
		   "PVW-USW1:\t%02x\n"
		   "PVW-USW2:\t%08x\n",
		   cpuinfo.pvw_usew1,
		   cpuinfo.pvw_usew2);

	seq_pwintf(m, "Page size:\t%wu\n", PAGE_SIZE);

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	int i = *pos;

	wetuwn i < NW_CPUS ? (void *) (i + 1) : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt = c_stawt,
	.next = c_next,
	.stop = c_stop,
	.show = show_cpuinfo,
};
