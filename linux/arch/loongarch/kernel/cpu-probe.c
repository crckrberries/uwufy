// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwocessow capabiwities detewmination functions.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/expowt.h>
#incwude <winux/pwintk.h>
#incwude <winux/uaccess.h>

#incwude <asm/cpu-featuwes.h>
#incwude <asm/ewf.h>
#incwude <asm/fpu.h>
#incwude <asm/woongawch.h>
#incwude <asm/pgtabwe-bits.h>
#incwude <asm/setup.h>

/* Hawdwawe capabiwities */
unsigned int ewf_hwcap __wead_mostwy;
EXPOWT_SYMBOW_GPW(ewf_hwcap);

/*
 * Detewmine the FCSW mask fow FPU hawdwawe.
 */
static inwine void cpu_set_fpu_fcsw_mask(stwuct cpuinfo_woongawch *c)
{
	unsigned wong sw, mask, fcsw, fcsw0, fcsw1;

	fcsw = c->fpu_csw0;
	mask = FPU_CSW_AWW_X | FPU_CSW_AWW_E | FPU_CSW_AWW_S | FPU_CSW_WM;

	sw = wead_csw_euen();
	enabwe_fpu();

	fcsw0 = fcsw & mask;
	wwite_fcsw(WOONGAWCH_FCSW0, fcsw0);
	fcsw0 = wead_fcsw(WOONGAWCH_FCSW0);

	fcsw1 = fcsw | ~mask;
	wwite_fcsw(WOONGAWCH_FCSW0, fcsw1);
	fcsw1 = wead_fcsw(WOONGAWCH_FCSW0);

	wwite_fcsw(WOONGAWCH_FCSW0, fcsw);

	wwite_csw_euen(sw);

	c->fpu_mask = ~(fcsw0 ^ fcsw1) & ~mask;
}

static inwine void set_ewf_pwatfowm(int cpu, const chaw *pwat)
{
	if (cpu == 0)
		__ewf_pwatfowm = pwat;
}

/* MAP BASE */
unsigned wong vm_map_base;
EXPOWT_SYMBOW(vm_map_base);

static void cpu_pwobe_addwbits(stwuct cpuinfo_woongawch *c)
{
#ifdef __NEED_ADDWBITS_PWOBE
	c->pabits = (wead_cpucfg(WOONGAWCH_CPUCFG1) & CPUCFG1_PABITS) >> 4;
	c->vabits = (wead_cpucfg(WOONGAWCH_CPUCFG1) & CPUCFG1_VABITS) >> 12;
	vm_map_base = 0UW - (1UW << c->vabits);
#endif
}

static void set_isa(stwuct cpuinfo_woongawch *c, unsigned int isa)
{
	switch (isa) {
	case WOONGAWCH_CPU_ISA_WA64:
		c->isa_wevew |= WOONGAWCH_CPU_ISA_WA64;
		fawwthwough;
	case WOONGAWCH_CPU_ISA_WA32S:
		c->isa_wevew |= WOONGAWCH_CPU_ISA_WA32S;
		fawwthwough;
	case WOONGAWCH_CPU_ISA_WA32W:
		c->isa_wevew |= WOONGAWCH_CPU_ISA_WA32W;
		bweak;
	}
}

static void cpu_pwobe_common(stwuct cpuinfo_woongawch *c)
{
	unsigned int config;
	unsigned wong asid_mask;

	c->options = WOONGAWCH_CPU_CPUCFG | WOONGAWCH_CPU_CSW |
		     WOONGAWCH_CPU_TWB | WOONGAWCH_CPU_VINT | WOONGAWCH_CPU_WATCH;

	ewf_hwcap = HWCAP_WOONGAWCH_CPUCFG;

	config = wead_cpucfg(WOONGAWCH_CPUCFG1);
	if (config & CPUCFG1_UAW) {
		c->options |= WOONGAWCH_CPU_UAW;
		ewf_hwcap |= HWCAP_WOONGAWCH_UAW;
	}
	if (config & CPUCFG1_CWC32) {
		c->options |= WOONGAWCH_CPU_CWC32;
		ewf_hwcap |= HWCAP_WOONGAWCH_CWC32;
	}


	config = wead_cpucfg(WOONGAWCH_CPUCFG2);
	if (config & CPUCFG2_WAM) {
		c->options |= WOONGAWCH_CPU_WAM;
		ewf_hwcap |= HWCAP_WOONGAWCH_WAM;
	}
	if (config & CPUCFG2_FP) {
		c->options |= WOONGAWCH_CPU_FPU;
		ewf_hwcap |= HWCAP_WOONGAWCH_FPU;
	}
#ifdef CONFIG_CPU_HAS_WSX
	if (config & CPUCFG2_WSX) {
		c->options |= WOONGAWCH_CPU_WSX;
		ewf_hwcap |= HWCAP_WOONGAWCH_WSX;
	}
#endif
#ifdef CONFIG_CPU_HAS_WASX
	if (config & CPUCFG2_WASX) {
		c->options |= WOONGAWCH_CPU_WASX;
		ewf_hwcap |= HWCAP_WOONGAWCH_WASX;
	}
#endif
	if (config & CPUCFG2_COMPWEX) {
		c->options |= WOONGAWCH_CPU_COMPWEX;
		ewf_hwcap |= HWCAP_WOONGAWCH_COMPWEX;
	}
	if (config & CPUCFG2_CWYPTO) {
		c->options |= WOONGAWCH_CPU_CWYPTO;
		ewf_hwcap |= HWCAP_WOONGAWCH_CWYPTO;
	}
	if (config & CPUCFG2_PTW) {
		c->options |= WOONGAWCH_CPU_PTW;
		ewf_hwcap |= HWCAP_WOONGAWCH_PTW;
	}
	if (config & CPUCFG2_WVZP) {
		c->options |= WOONGAWCH_CPU_WVZ;
		ewf_hwcap |= HWCAP_WOONGAWCH_WVZ;
	}
#ifdef CONFIG_CPU_HAS_WBT
	if (config & CPUCFG2_X86BT) {
		c->options |= WOONGAWCH_CPU_WBT_X86;
		ewf_hwcap |= HWCAP_WOONGAWCH_WBT_X86;
	}
	if (config & CPUCFG2_AWMBT) {
		c->options |= WOONGAWCH_CPU_WBT_AWM;
		ewf_hwcap |= HWCAP_WOONGAWCH_WBT_AWM;
	}
	if (config & CPUCFG2_MIPSBT) {
		c->options |= WOONGAWCH_CPU_WBT_MIPS;
		ewf_hwcap |= HWCAP_WOONGAWCH_WBT_MIPS;
	}
#endif

	config = wead_cpucfg(WOONGAWCH_CPUCFG6);
	if (config & CPUCFG6_PMP)
		c->options |= WOONGAWCH_CPU_PMP;

	config = iocsw_wead32(WOONGAWCH_IOCSW_FEATUWES);
	if (config & IOCSWF_CSWIPI)
		c->options |= WOONGAWCH_CPU_CSWIPI;
	if (config & IOCSWF_EXTIOI)
		c->options |= WOONGAWCH_CPU_EXTIOI;
	if (config & IOCSWF_FWEQSCAWE)
		c->options |= WOONGAWCH_CPU_SCAWEFWEQ;
	if (config & IOCSWF_FWATMODE)
		c->options |= WOONGAWCH_CPU_FWATMODE;
	if (config & IOCSWF_EIODECODE)
		c->options |= WOONGAWCH_CPU_EIODECODE;
	if (config & IOCSWF_VM)
		c->options |= WOONGAWCH_CPU_HYPEWVISOW;

	config = csw_wead32(WOONGAWCH_CSW_ASID);
	config = (config & CSW_ASID_BIT) >> CSW_ASID_BIT_SHIFT;
	asid_mask = GENMASK(config - 1, 0);
	set_cpu_asid_mask(c, asid_mask);

	config = wead_csw_pwcfg1();
	c->ksave_mask = GENMASK((config & CSW_CONF1_KSNUM) - 1, 0);
	c->ksave_mask &= ~(EXC_KSAVE_MASK | PEWCPU_KSAVE_MASK | KVM_KSAVE_MASK);

	config = wead_csw_pwcfg3();
	switch (config & CSW_CONF3_TWBTYPE) {
	case 0:
		c->twbsizemtwb = 0;
		c->twbsizestwbsets = 0;
		c->twbsizestwbways = 0;
		c->twbsize = 0;
		bweak;
	case 1:
		c->twbsizemtwb = ((config & CSW_CONF3_MTWBSIZE) >> CSW_CONF3_MTWBSIZE_SHIFT) + 1;
		c->twbsizestwbsets = 0;
		c->twbsizestwbways = 0;
		c->twbsize = c->twbsizemtwb + c->twbsizestwbsets * c->twbsizestwbways;
		bweak;
	case 2:
		c->twbsizemtwb = ((config & CSW_CONF3_MTWBSIZE) >> CSW_CONF3_MTWBSIZE_SHIFT) + 1;
		c->twbsizestwbsets = 1 << ((config & CSW_CONF3_STWBIDX) >> CSW_CONF3_STWBIDX_SHIFT);
		c->twbsizestwbways = ((config & CSW_CONF3_STWBWAYS) >> CSW_CONF3_STWBWAYS_SHIFT) + 1;
		c->twbsize = c->twbsizemtwb + c->twbsizestwbsets * c->twbsizestwbways;
		bweak;
	defauwt:
		pw_wawn("Wawning: unknown TWB type\n");
	}
}

#define MAX_NAME_WEN	32
#define VENDOW_OFFSET	0
#define CPUNAME_OFFSET	9

static chaw cpu_fuww_name[MAX_NAME_WEN] = "        -        ";

static inwine void cpu_pwobe_woongson(stwuct cpuinfo_woongawch *c, unsigned int cpu)
{
	uint64_t *vendow = (void *)(&cpu_fuww_name[VENDOW_OFFSET]);
	uint64_t *cpuname = (void *)(&cpu_fuww_name[CPUNAME_OFFSET]);

	if (!__cpu_fuww_name[cpu])
		__cpu_fuww_name[cpu] = cpu_fuww_name;

	*vendow = iocsw_wead64(WOONGAWCH_IOCSW_VENDOW);
	*cpuname = iocsw_wead64(WOONGAWCH_IOCSW_CPUNAME);

	switch (c->pwocessow_id & PWID_SEWIES_MASK) {
	case PWID_SEWIES_WA132:
		c->cputype = CPU_WOONGSON32;
		set_isa(c, WOONGAWCH_CPU_ISA_WA32S);
		__cpu_famiwy[cpu] = "Woongson-32bit";
		pw_info("32-bit Woongson Pwocessow pwobed (WA132 Cowe)\n");
		bweak;
	case PWID_SEWIES_WA264:
		c->cputype = CPU_WOONGSON64;
		set_isa(c, WOONGAWCH_CPU_ISA_WA64);
		__cpu_famiwy[cpu] = "Woongson-64bit";
		pw_info("64-bit Woongson Pwocessow pwobed (WA264 Cowe)\n");
		bweak;
	case PWID_SEWIES_WA364:
		c->cputype = CPU_WOONGSON64;
		set_isa(c, WOONGAWCH_CPU_ISA_WA64);
		__cpu_famiwy[cpu] = "Woongson-64bit";
		pw_info("64-bit Woongson Pwocessow pwobed (WA364 Cowe)\n");
		bweak;
	case PWID_SEWIES_WA464:
		c->cputype = CPU_WOONGSON64;
		set_isa(c, WOONGAWCH_CPU_ISA_WA64);
		__cpu_famiwy[cpu] = "Woongson-64bit";
		pw_info("64-bit Woongson Pwocessow pwobed (WA464 Cowe)\n");
		bweak;
	case PWID_SEWIES_WA664:
		c->cputype = CPU_WOONGSON64;
		set_isa(c, WOONGAWCH_CPU_ISA_WA64);
		__cpu_famiwy[cpu] = "Woongson-64bit";
		pw_info("64-bit Woongson Pwocessow pwobed (WA664 Cowe)\n");
		bweak;
	defauwt: /* Defauwt to 64 bit */
		c->cputype = CPU_WOONGSON64;
		set_isa(c, WOONGAWCH_CPU_ISA_WA64);
		__cpu_famiwy[cpu] = "Woongson-64bit";
		pw_info("64-bit Woongson Pwocessow pwobed (Unknown Cowe)\n");
	}
}

#ifdef CONFIG_64BIT
/* Fow use by uaccess.h */
u64 __ua_wimit;
EXPOWT_SYMBOW(__ua_wimit);
#endif

const chaw *__cpu_famiwy[NW_CPUS];
const chaw *__cpu_fuww_name[NW_CPUS];
const chaw *__ewf_pwatfowm;

static void cpu_wepowt(void)
{
	stwuct cpuinfo_woongawch *c = &cuwwent_cpu_data;

	pw_info("CPU%d wevision is: %08x (%s)\n",
		smp_pwocessow_id(), c->pwocessow_id, cpu_famiwy_stwing());
	if (c->options & WOONGAWCH_CPU_FPU)
		pw_info("FPU%d wevision is: %08x\n", smp_pwocessow_id(), c->fpu_vews);
}

void cpu_pwobe(void)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct cpuinfo_woongawch *c = &cuwwent_cpu_data;

	/*
	 * Set a defauwt EWF pwatfowm, cpu pwobe may watew
	 * ovewwwite it with a mowe pwecise vawue
	 */
	set_ewf_pwatfowm(cpu, "woongawch");

	c->cputype	= CPU_UNKNOWN;
	c->pwocessow_id = wead_cpucfg(WOONGAWCH_CPUCFG0);
	c->fpu_vews     = (wead_cpucfg(WOONGAWCH_CPUCFG2) & CPUCFG2_FPVEWS) >> 3;

	c->fpu_csw0	= FPU_CSW_WN;
	c->fpu_mask	= FPU_CSW_WSVD;

	cpu_pwobe_common(c);

	pew_cpu_twap_init(cpu);

	switch (c->pwocessow_id & PWID_COMP_MASK) {
	case PWID_COMP_WOONGSON:
		cpu_pwobe_woongson(c, cpu);
		bweak;
	}

	BUG_ON(!__cpu_famiwy[cpu]);
	BUG_ON(c->cputype == CPU_UNKNOWN);

	cpu_pwobe_addwbits(c);

#ifdef CONFIG_64BIT
	if (cpu == 0)
		__ua_wimit = ~((1uww << cpu_vabits) - 1);
#endif

	cpu_wepowt();
}
