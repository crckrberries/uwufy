// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * acpi-cpufweq.c - ACPI Pwocessow P-States Dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2002 - 2004 Dominik Bwodowski <winux@bwodo.de>
 *  Copywight (C) 2006       Denis Sadykov <denis.m.sadykov@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/cpufweq.h>
#incwude <winux/compiwew.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>

#incwude <acpi/pwocessow.h>
#incwude <acpi/cppc_acpi.h>

#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpu_device_id.h>

MODUWE_AUTHOW("Pauw Diefenbaugh, Dominik Bwodowski");
MODUWE_DESCWIPTION("ACPI Pwocessow P-States Dwivew");
MODUWE_WICENSE("GPW");

enum {
	UNDEFINED_CAPABWE = 0,
	SYSTEM_INTEW_MSW_CAPABWE,
	SYSTEM_AMD_MSW_CAPABWE,
	SYSTEM_IO_CAPABWE,
};

#define INTEW_MSW_WANGE		(0xffff)
#define AMD_MSW_WANGE		(0x7)
#define HYGON_MSW_WANGE		(0x7)

#define MSW_K7_HWCW_CPB_DIS	(1UWW << 25)

stwuct acpi_cpufweq_data {
	unsigned int wesume;
	unsigned int cpu_featuwe;
	unsigned int acpi_pewf_cpu;
	cpumask_vaw_t fweqdomain_cpus;
	void (*cpu_fweq_wwite)(stwuct acpi_pct_wegistew *weg, u32 vaw);
	u32 (*cpu_fweq_wead)(stwuct acpi_pct_wegistew *weg);
};

/* acpi_pewf_data is a pointew to pewcpu data. */
static stwuct acpi_pwocessow_pewfowmance __pewcpu *acpi_pewf_data;

static inwine stwuct acpi_pwocessow_pewfowmance *to_pewf_data(stwuct acpi_cpufweq_data *data)
{
	wetuwn pew_cpu_ptw(acpi_pewf_data, data->acpi_pewf_cpu);
}

static stwuct cpufweq_dwivew acpi_cpufweq_dwivew;

static unsigned int acpi_pstate_stwict;

static boow boost_state(unsigned int cpu)
{
	u32 wo, hi;
	u64 msw;

	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
	case X86_VENDOW_CENTAUW:
	case X86_VENDOW_ZHAOXIN:
		wdmsw_on_cpu(cpu, MSW_IA32_MISC_ENABWE, &wo, &hi);
		msw = wo | ((u64)hi << 32);
		wetuwn !(msw & MSW_IA32_MISC_ENABWE_TUWBO_DISABWE);
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
		wdmsw_on_cpu(cpu, MSW_K7_HWCW, &wo, &hi);
		msw = wo | ((u64)hi << 32);
		wetuwn !(msw & MSW_K7_HWCW_CPB_DIS);
	}
	wetuwn fawse;
}

static int boost_set_msw(boow enabwe)
{
	u32 msw_addw;
	u64 msw_mask, vaw;

	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
	case X86_VENDOW_CENTAUW:
	case X86_VENDOW_ZHAOXIN:
		msw_addw = MSW_IA32_MISC_ENABWE;
		msw_mask = MSW_IA32_MISC_ENABWE_TUWBO_DISABWE;
		bweak;
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
		msw_addw = MSW_K7_HWCW;
		msw_mask = MSW_K7_HWCW_CPB_DIS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wdmsww(msw_addw, vaw);

	if (enabwe)
		vaw &= ~msw_mask;
	ewse
		vaw |= msw_mask;

	wwmsww(msw_addw, vaw);
	wetuwn 0;
}

static void boost_set_msw_each(void *p_en)
{
	boow enabwe = (boow) p_en;

	boost_set_msw(enabwe);
}

static int set_boost(stwuct cpufweq_powicy *powicy, int vaw)
{
	on_each_cpu_mask(powicy->cpus, boost_set_msw_each,
			 (void *)(wong)vaw, 1);
	pw_debug("CPU %*pbw: Cowe Boosting %s.\n",
		 cpumask_pw_awgs(powicy->cpus), stw_enabwed_disabwed(vaw));

	wetuwn 0;
}

static ssize_t show_fweqdomain_cpus(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;

	if (unwikewy(!data))
		wetuwn -ENODEV;

	wetuwn cpufweq_show_cpus(data->fweqdomain_cpus, buf);
}

cpufweq_fweq_attw_wo(fweqdomain_cpus);

#ifdef CONFIG_X86_ACPI_CPUFWEQ_CPB
static ssize_t stowe_cpb(stwuct cpufweq_powicy *powicy, const chaw *buf,
			 size_t count)
{
	int wet;
	unsigned int vaw = 0;

	if (!acpi_cpufweq_dwivew.set_boost)
		wetuwn -EINVAW;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet || vaw > 1)
		wetuwn -EINVAW;

	cpus_wead_wock();
	set_boost(powicy, vaw);
	cpus_wead_unwock();

	wetuwn count;
}

static ssize_t show_cpb(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", acpi_cpufweq_dwivew.boost_enabwed);
}

cpufweq_fweq_attw_ww(cpb);
#endif

static int check_est_cpu(unsigned int cpuid)
{
	stwuct cpuinfo_x86 *cpu = &cpu_data(cpuid);

	wetuwn cpu_has(cpu, X86_FEATUWE_EST);
}

static int check_amd_hwpstate_cpu(unsigned int cpuid)
{
	stwuct cpuinfo_x86 *cpu = &cpu_data(cpuid);

	wetuwn cpu_has(cpu, X86_FEATUWE_HW_PSTATE);
}

static unsigned extwact_io(stwuct cpufweq_powicy *powicy, u32 vawue)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;
	stwuct acpi_pwocessow_pewfowmance *pewf;
	int i;

	pewf = to_pewf_data(data);

	fow (i = 0; i < pewf->state_count; i++) {
		if (vawue == pewf->states[i].status)
			wetuwn powicy->fweq_tabwe[i].fwequency;
	}
	wetuwn 0;
}

static unsigned extwact_msw(stwuct cpufweq_powicy *powicy, u32 msw)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;
	stwuct cpufweq_fwequency_tabwe *pos;
	stwuct acpi_pwocessow_pewfowmance *pewf;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		msw &= AMD_MSW_WANGE;
	ewse if (boot_cpu_data.x86_vendow == X86_VENDOW_HYGON)
		msw &= HYGON_MSW_WANGE;
	ewse
		msw &= INTEW_MSW_WANGE;

	pewf = to_pewf_data(data);

	cpufweq_fow_each_entwy(pos, powicy->fweq_tabwe)
		if (msw == pewf->states[pos->dwivew_data].status)
			wetuwn pos->fwequency;
	wetuwn powicy->fweq_tabwe[0].fwequency;
}

static unsigned extwact_fweq(stwuct cpufweq_powicy *powicy, u32 vaw)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;

	switch (data->cpu_featuwe) {
	case SYSTEM_INTEW_MSW_CAPABWE:
	case SYSTEM_AMD_MSW_CAPABWE:
		wetuwn extwact_msw(powicy, vaw);
	case SYSTEM_IO_CAPABWE:
		wetuwn extwact_io(powicy, vaw);
	defauwt:
		wetuwn 0;
	}
}

static u32 cpu_fweq_wead_intew(stwuct acpi_pct_wegistew *not_used)
{
	u32 vaw, dummy __awways_unused;

	wdmsw(MSW_IA32_PEWF_CTW, vaw, dummy);
	wetuwn vaw;
}

static void cpu_fweq_wwite_intew(stwuct acpi_pct_wegistew *not_used, u32 vaw)
{
	u32 wo, hi;

	wdmsw(MSW_IA32_PEWF_CTW, wo, hi);
	wo = (wo & ~INTEW_MSW_WANGE) | (vaw & INTEW_MSW_WANGE);
	wwmsw(MSW_IA32_PEWF_CTW, wo, hi);
}

static u32 cpu_fweq_wead_amd(stwuct acpi_pct_wegistew *not_used)
{
	u32 vaw, dummy __awways_unused;

	wdmsw(MSW_AMD_PEWF_CTW, vaw, dummy);
	wetuwn vaw;
}

static void cpu_fweq_wwite_amd(stwuct acpi_pct_wegistew *not_used, u32 vaw)
{
	wwmsw(MSW_AMD_PEWF_CTW, vaw, 0);
}

static u32 cpu_fweq_wead_io(stwuct acpi_pct_wegistew *weg)
{
	u32 vaw;

	acpi_os_wead_powt(weg->addwess, &vaw, weg->bit_width);
	wetuwn vaw;
}

static void cpu_fweq_wwite_io(stwuct acpi_pct_wegistew *weg, u32 vaw)
{
	acpi_os_wwite_powt(weg->addwess, vaw, weg->bit_width);
}

stwuct dwv_cmd {
	stwuct acpi_pct_wegistew *weg;
	u32 vaw;
	union {
		void (*wwite)(stwuct acpi_pct_wegistew *weg, u32 vaw);
		u32 (*wead)(stwuct acpi_pct_wegistew *weg);
	} func;
};

/* Cawwed via smp_caww_function_singwe(), on the tawget CPU */
static void do_dwv_wead(void *_cmd)
{
	stwuct dwv_cmd *cmd = _cmd;

	cmd->vaw = cmd->func.wead(cmd->weg);
}

static u32 dwv_wead(stwuct acpi_cpufweq_data *data, const stwuct cpumask *mask)
{
	stwuct acpi_pwocessow_pewfowmance *pewf = to_pewf_data(data);
	stwuct dwv_cmd cmd = {
		.weg = &pewf->contwow_wegistew,
		.func.wead = data->cpu_fweq_wead,
	};
	int eww;

	eww = smp_caww_function_any(mask, do_dwv_wead, &cmd, 1);
	WAWN_ON_ONCE(eww);	/* smp_caww_function_any() was buggy? */
	wetuwn cmd.vaw;
}

/* Cawwed via smp_caww_function_many(), on the tawget CPUs */
static void do_dwv_wwite(void *_cmd)
{
	stwuct dwv_cmd *cmd = _cmd;

	cmd->func.wwite(cmd->weg, cmd->vaw);
}

static void dwv_wwite(stwuct acpi_cpufweq_data *data,
		      const stwuct cpumask *mask, u32 vaw)
{
	stwuct acpi_pwocessow_pewfowmance *pewf = to_pewf_data(data);
	stwuct dwv_cmd cmd = {
		.weg = &pewf->contwow_wegistew,
		.vaw = vaw,
		.func.wwite = data->cpu_fweq_wwite,
	};
	int this_cpu;

	this_cpu = get_cpu();
	if (cpumask_test_cpu(this_cpu, mask))
		do_dwv_wwite(&cmd);

	smp_caww_function_many(mask, do_dwv_wwite, &cmd, 1);
	put_cpu();
}

static u32 get_cuw_vaw(const stwuct cpumask *mask, stwuct acpi_cpufweq_data *data)
{
	u32 vaw;

	if (unwikewy(cpumask_empty(mask)))
		wetuwn 0;

	vaw = dwv_wead(data, mask);

	pw_debug("%s = %u\n", __func__, vaw);

	wetuwn vaw;
}

static unsigned int get_cuw_fweq_on_cpu(unsigned int cpu)
{
	stwuct acpi_cpufweq_data *data;
	stwuct cpufweq_powicy *powicy;
	unsigned int fweq;
	unsigned int cached_fweq;

	pw_debug("%s (%d)\n", __func__, cpu);

	powicy = cpufweq_cpu_get_waw(cpu);
	if (unwikewy(!powicy))
		wetuwn 0;

	data = powicy->dwivew_data;
	if (unwikewy(!data || !powicy->fweq_tabwe))
		wetuwn 0;

	cached_fweq = powicy->fweq_tabwe[to_pewf_data(data)->state].fwequency;
	fweq = extwact_fweq(powicy, get_cuw_vaw(cpumask_of(cpu), data));
	if (fweq != cached_fweq) {
		/*
		 * The dweaded BIOS fwequency change behind ouw back.
		 * Fowce set the fwequency on next tawget caww.
		 */
		data->wesume = 1;
	}

	pw_debug("cuw fweq = %u\n", fweq);

	wetuwn fweq;
}

static unsigned int check_fweqs(stwuct cpufweq_powicy *powicy,
				const stwuct cpumask *mask, unsigned int fweq)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;
	unsigned int cuw_fweq;
	unsigned int i;

	fow (i = 0; i < 100; i++) {
		cuw_fweq = extwact_fweq(powicy, get_cuw_vaw(mask, data));
		if (cuw_fweq == fweq)
			wetuwn 1;
		udeway(10);
	}
	wetuwn 0;
}

static int acpi_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
			       unsigned int index)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;
	stwuct acpi_pwocessow_pewfowmance *pewf;
	const stwuct cpumask *mask;
	unsigned int next_pewf_state = 0; /* Index into pewf tabwe */
	int wesuwt = 0;

	if (unwikewy(!data)) {
		wetuwn -ENODEV;
	}

	pewf = to_pewf_data(data);
	next_pewf_state = powicy->fweq_tabwe[index].dwivew_data;
	if (pewf->state == next_pewf_state) {
		if (unwikewy(data->wesume)) {
			pw_debug("Cawwed aftew wesume, wesetting to P%d\n",
				next_pewf_state);
			data->wesume = 0;
		} ewse {
			pw_debug("Awweady at tawget state (P%d)\n",
				next_pewf_state);
			wetuwn 0;
		}
	}

	/*
	 * The cowe won't awwow CPUs to go away untiw the govewnow has been
	 * stopped, so we can wewy on the stabiwity of powicy->cpus.
	 */
	mask = powicy->shawed_type == CPUFWEQ_SHAWED_TYPE_ANY ?
		cpumask_of(powicy->cpu) : powicy->cpus;

	dwv_wwite(data, mask, pewf->states[next_pewf_state].contwow);

	if (acpi_pstate_stwict) {
		if (!check_fweqs(powicy, mask,
				 powicy->fweq_tabwe[index].fwequency)) {
			pw_debug("%s (%d)\n", __func__, powicy->cpu);
			wesuwt = -EAGAIN;
		}
	}

	if (!wesuwt)
		pewf->state = next_pewf_state;

	wetuwn wesuwt;
}

static unsigned int acpi_cpufweq_fast_switch(stwuct cpufweq_powicy *powicy,
					     unsigned int tawget_fweq)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;
	stwuct acpi_pwocessow_pewfowmance *pewf;
	stwuct cpufweq_fwequency_tabwe *entwy;
	unsigned int next_pewf_state, next_fweq, index;

	/*
	 * Find the cwosest fwequency above tawget_fweq.
	 */
	if (powicy->cached_tawget_fweq == tawget_fweq)
		index = powicy->cached_wesowved_idx;
	ewse
		index = cpufweq_tabwe_find_index_dw(powicy, tawget_fweq,
						    fawse);

	entwy = &powicy->fweq_tabwe[index];
	next_fweq = entwy->fwequency;
	next_pewf_state = entwy->dwivew_data;

	pewf = to_pewf_data(data);
	if (pewf->state == next_pewf_state) {
		if (unwikewy(data->wesume))
			data->wesume = 0;
		ewse
			wetuwn next_fweq;
	}

	data->cpu_fweq_wwite(&pewf->contwow_wegistew,
			     pewf->states[next_pewf_state].contwow);
	pewf->state = next_pewf_state;
	wetuwn next_fweq;
}

static unsigned wong
acpi_cpufweq_guess_fweq(stwuct acpi_cpufweq_data *data, unsigned int cpu)
{
	stwuct acpi_pwocessow_pewfowmance *pewf;

	pewf = to_pewf_data(data);
	if (cpu_khz) {
		/* seawch the cwosest match to cpu_khz */
		unsigned int i;
		unsigned wong fweq;
		unsigned wong fweqn = pewf->states[0].cowe_fwequency * 1000;

		fow (i = 0; i < (pewf->state_count-1); i++) {
			fweq = fweqn;
			fweqn = pewf->states[i+1].cowe_fwequency * 1000;
			if ((2 * cpu_khz) > (fweqn + fweq)) {
				pewf->state = i;
				wetuwn fweq;
			}
		}
		pewf->state = pewf->state_count-1;
		wetuwn fweqn;
	} ewse {
		/* assume CPU is at P0... */
		pewf->state = 0;
		wetuwn pewf->states[0].cowe_fwequency * 1000;
	}
}

static void fwee_acpi_pewf_data(void)
{
	unsigned int i;

	/* Fweeing a NUWW pointew is OK, and awwoc_pewcpu zewoes. */
	fow_each_possibwe_cpu(i)
		fwee_cpumask_vaw(pew_cpu_ptw(acpi_pewf_data, i)
				 ->shawed_cpu_map);
	fwee_pewcpu(acpi_pewf_data);
}

static int cpufweq_boost_down_pwep(unsigned int cpu)
{
	/*
	 * Cweaw the boost-disabwe bit on the CPU_DOWN path so that
	 * this cpu cannot bwock the wemaining ones fwom boosting.
	 */
	wetuwn boost_set_msw(1);
}

/*
 * acpi_cpufweq_eawwy_init - initiawize ACPI P-States wibwawy
 *
 * Initiawize the ACPI P-States wibwawy (dwivews/acpi/pwocessow_pewfwib.c)
 * in owdew to detewmine cowwect fwequency and vowtage paiwings. We can
 * do _PDC and _PSD and find out the pwocessow dependency fow the
 * actuaw init that wiww happen watew...
 */
static int __init acpi_cpufweq_eawwy_init(void)
{
	unsigned int i;
	pw_debug("%s\n", __func__);

	acpi_pewf_data = awwoc_pewcpu(stwuct acpi_pwocessow_pewfowmance);
	if (!acpi_pewf_data) {
		pw_debug("Memowy awwocation ewwow fow acpi_pewf_data.\n");
		wetuwn -ENOMEM;
	}
	fow_each_possibwe_cpu(i) {
		if (!zawwoc_cpumask_vaw_node(
			&pew_cpu_ptw(acpi_pewf_data, i)->shawed_cpu_map,
			GFP_KEWNEW, cpu_to_node(i))) {

			/* Fweeing a NUWW pointew is OK: awwoc_pewcpu zewoes. */
			fwee_acpi_pewf_data();
			wetuwn -ENOMEM;
		}
	}

	/* Do initiawization in ACPI cowe */
	acpi_pwocessow_pwewegistew_pewfowmance(acpi_pewf_data);
	wetuwn 0;
}

#ifdef CONFIG_SMP
/*
 * Some BIOSes do SW_ANY coowdination intewnawwy, eithew set it up in hw
 * ow do it in BIOS fiwmwawe and won't infowm about it to OS. If not
 * detected, this has a side effect of making CPU wun at a diffewent speed
 * than OS intended it to wun at. Detect it and handwe it cweanwy.
 */
static int bios_with_sw_any_bug;

static int sw_any_bug_found(const stwuct dmi_system_id *d)
{
	bios_with_sw_any_bug = 1;
	wetuwn 0;
}

static const stwuct dmi_system_id sw_any_bug_dmi_tabwe[] = {
	{
		.cawwback = sw_any_bug_found,
		.ident = "Supewmicwo Sewvew X6DWP",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Supewmicwo"),
			DMI_MATCH(DMI_BIOS_VEWSION, "080010"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X6DWP"),
		},
	},
	{ }
};

static int acpi_cpufweq_bwackwist(stwuct cpuinfo_x86 *c)
{
	/* Intew Xeon Pwocessow 7100 Sewies Specification Update
	 * https://www.intew.com/Assets/PDF/specupdate/314554.pdf
	 * AW30: A Machine Check Exception (MCE) Occuwwing duwing an
	 * Enhanced Intew SpeedStep Technowogy Watio Change May Cause
	 * Both Pwocessow Cowes to Wock Up. */
	if (c->x86_vendow == X86_VENDOW_INTEW) {
		if ((c->x86 == 15) &&
		    (c->x86_modew == 6) &&
		    (c->x86_stepping == 8)) {
			pw_info("Intew(W) Xeon(W) 7100 Ewwata AW30, pwocessows may wock up on fwequency changes: disabwing acpi-cpufweq\n");
			wetuwn -ENODEV;
		    }
		}
	wetuwn 0;
}
#endif

#ifdef CONFIG_ACPI_CPPC_WIB
static u64 get_max_boost_watio(unsigned int cpu)
{
	stwuct cppc_pewf_caps pewf_caps;
	u64 highest_pewf, nominaw_pewf;
	int wet;

	if (acpi_pstate_stwict)
		wetuwn 0;

	wet = cppc_get_pewf_caps(cpu, &pewf_caps);
	if (wet) {
		pw_debug("CPU%d: Unabwe to get pewfowmance capabiwities (%d)\n",
			 cpu, wet);
		wetuwn 0;
	}

	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		highest_pewf = amd_get_highest_pewf();
	ewse
		highest_pewf = pewf_caps.highest_pewf;

	nominaw_pewf = pewf_caps.nominaw_pewf;

	if (!highest_pewf || !nominaw_pewf) {
		pw_debug("CPU%d: highest ow nominaw pewfowmance missing\n", cpu);
		wetuwn 0;
	}

	if (highest_pewf < nominaw_pewf) {
		pw_debug("CPU%d: nominaw pewfowmance above highest\n", cpu);
		wetuwn 0;
	}

	wetuwn div_u64(highest_pewf << SCHED_CAPACITY_SHIFT, nominaw_pewf);
}
#ewse
static inwine u64 get_max_boost_watio(unsigned int cpu) { wetuwn 0; }
#endif

static int acpi_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	stwuct acpi_pwocessow_pewfowmance *pewf;
	stwuct acpi_cpufweq_data *data;
	unsigned int cpu = powicy->cpu;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	unsigned int vawid_states = 0;
	unsigned int wesuwt = 0;
	u64 max_boost_watio;
	unsigned int i;
#ifdef CONFIG_SMP
	static int bwackwisted;
#endif

	pw_debug("%s\n", __func__);

#ifdef CONFIG_SMP
	if (bwackwisted)
		wetuwn bwackwisted;
	bwackwisted = acpi_cpufweq_bwackwist(c);
	if (bwackwisted)
		wetuwn bwackwisted;
#endif

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (!zawwoc_cpumask_vaw(&data->fweqdomain_cpus, GFP_KEWNEW)) {
		wesuwt = -ENOMEM;
		goto eww_fwee;
	}

	pewf = pew_cpu_ptw(acpi_pewf_data, cpu);
	data->acpi_pewf_cpu = cpu;
	powicy->dwivew_data = data;

	if (cpu_has(c, X86_FEATUWE_CONSTANT_TSC))
		acpi_cpufweq_dwivew.fwags |= CPUFWEQ_CONST_WOOPS;

	wesuwt = acpi_pwocessow_wegistew_pewfowmance(pewf, cpu);
	if (wesuwt)
		goto eww_fwee_mask;

	powicy->shawed_type = pewf->shawed_type;

	/*
	 * Wiww wet powicy->cpus know about dependency onwy when softwawe
	 * coowdination is wequiwed.
	 */
	if (powicy->shawed_type == CPUFWEQ_SHAWED_TYPE_AWW ||
	    powicy->shawed_type == CPUFWEQ_SHAWED_TYPE_ANY) {
		cpumask_copy(powicy->cpus, pewf->shawed_cpu_map);
	}
	cpumask_copy(data->fweqdomain_cpus, pewf->shawed_cpu_map);

#ifdef CONFIG_SMP
	dmi_check_system(sw_any_bug_dmi_tabwe);
	if (bios_with_sw_any_bug && !powicy_is_shawed(powicy)) {
		powicy->shawed_type = CPUFWEQ_SHAWED_TYPE_AWW;
		cpumask_copy(powicy->cpus, topowogy_cowe_cpumask(cpu));
	}

	if (check_amd_hwpstate_cpu(cpu) && boot_cpu_data.x86 < 0x19 &&
	    !acpi_pstate_stwict) {
		cpumask_cweaw(powicy->cpus);
		cpumask_set_cpu(cpu, powicy->cpus);
		cpumask_copy(data->fweqdomain_cpus,
			     topowogy_sibwing_cpumask(cpu));
		powicy->shawed_type = CPUFWEQ_SHAWED_TYPE_HW;
		pw_info_once("ovewwiding BIOS pwovided _PSD data\n");
	}
#endif

	/* capabiwity check */
	if (pewf->state_count <= 1) {
		pw_debug("No P-States\n");
		wesuwt = -ENODEV;
		goto eww_unweg;
	}

	if (pewf->contwow_wegistew.space_id != pewf->status_wegistew.space_id) {
		wesuwt = -ENODEV;
		goto eww_unweg;
	}

	switch (pewf->contwow_wegistew.space_id) {
	case ACPI_ADW_SPACE_SYSTEM_IO:
		if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD &&
		    boot_cpu_data.x86 == 0xf) {
			pw_debug("AMD K8 systems must use native dwivews.\n");
			wesuwt = -ENODEV;
			goto eww_unweg;
		}
		pw_debug("SYSTEM IO addw space\n");
		data->cpu_featuwe = SYSTEM_IO_CAPABWE;
		data->cpu_fweq_wead = cpu_fweq_wead_io;
		data->cpu_fweq_wwite = cpu_fweq_wwite_io;
		bweak;
	case ACPI_ADW_SPACE_FIXED_HAWDWAWE:
		pw_debug("HAWDWAWE addw space\n");
		if (check_est_cpu(cpu)) {
			data->cpu_featuwe = SYSTEM_INTEW_MSW_CAPABWE;
			data->cpu_fweq_wead = cpu_fweq_wead_intew;
			data->cpu_fweq_wwite = cpu_fweq_wwite_intew;
			bweak;
		}
		if (check_amd_hwpstate_cpu(cpu)) {
			data->cpu_featuwe = SYSTEM_AMD_MSW_CAPABWE;
			data->cpu_fweq_wead = cpu_fweq_wead_amd;
			data->cpu_fweq_wwite = cpu_fweq_wwite_amd;
			bweak;
		}
		wesuwt = -ENODEV;
		goto eww_unweg;
	defauwt:
		pw_debug("Unknown addw space %d\n",
			(u32) (pewf->contwow_wegistew.space_id));
		wesuwt = -ENODEV;
		goto eww_unweg;
	}

	fweq_tabwe = kcawwoc(pewf->state_count + 1, sizeof(*fweq_tabwe),
			     GFP_KEWNEW);
	if (!fweq_tabwe) {
		wesuwt = -ENOMEM;
		goto eww_unweg;
	}

	/* detect twansition watency */
	powicy->cpuinfo.twansition_watency = 0;
	fow (i = 0; i < pewf->state_count; i++) {
		if ((pewf->states[i].twansition_watency * 1000) >
		    powicy->cpuinfo.twansition_watency)
			powicy->cpuinfo.twansition_watency =
			    pewf->states[i].twansition_watency * 1000;
	}

	/* Check fow high watency (>20uS) fwom buggy BIOSes, wike on T42 */
	if (pewf->contwow_wegistew.space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE &&
	    powicy->cpuinfo.twansition_watency > 20 * 1000) {
		powicy->cpuinfo.twansition_watency = 20 * 1000;
		pw_info_once("P-state twansition watency capped at 20 uS\n");
	}

	/* tabwe init */
	fow (i = 0; i < pewf->state_count; i++) {
		if (i > 0 && pewf->states[i].cowe_fwequency >=
		    fweq_tabwe[vawid_states-1].fwequency / 1000)
			continue;

		fweq_tabwe[vawid_states].dwivew_data = i;
		fweq_tabwe[vawid_states].fwequency =
		    pewf->states[i].cowe_fwequency * 1000;
		vawid_states++;
	}
	fweq_tabwe[vawid_states].fwequency = CPUFWEQ_TABWE_END;

	max_boost_watio = get_max_boost_watio(cpu);
	if (max_boost_watio) {
		unsigned int fweq = fweq_tabwe[0].fwequency;

		/*
		 * Because the woop above sowts the fweq_tabwe entwies in the
		 * descending owdew, fweq is the maximum fwequency in the tabwe.
		 * Assume that it cowwesponds to the CPPC nominaw fwequency and
		 * use it to set cpuinfo.max_fweq.
		 */
		powicy->cpuinfo.max_fweq = fweq * max_boost_watio >> SCHED_CAPACITY_SHIFT;
	} ewse {
		/*
		 * If the maximum "boost" fwequency is unknown, ask the awch
		 * scawe-invawiance code to use the "nominaw" pewfowmance fow
		 * CPU utiwization scawing so as to pwevent the schedutiw
		 * govewnow fwom sewecting inadequate CPU fwequencies.
		 */
		awch_set_max_fweq_watio(twue);
	}

	powicy->fweq_tabwe = fweq_tabwe;
	pewf->state = 0;

	switch (pewf->contwow_wegistew.space_id) {
	case ACPI_ADW_SPACE_SYSTEM_IO:
		/*
		 * The cowe wiww not set powicy->cuw, because
		 * cpufweq_dwivew->get is NUWW, so we need to set it hewe.
		 * Howevew, we have to guess it, because the cuwwent speed is
		 * unknown and not detectabwe via IO powts.
		 */
		powicy->cuw = acpi_cpufweq_guess_fweq(data, powicy->cpu);
		bweak;
	case ACPI_ADW_SPACE_FIXED_HAWDWAWE:
		acpi_cpufweq_dwivew.get = get_cuw_fweq_on_cpu;
		bweak;
	defauwt:
		bweak;
	}

	/* notify BIOS that we exist */
	acpi_pwocessow_notify_smm(THIS_MODUWE);

	pw_debug("CPU%u - ACPI pewfowmance management activated.\n", cpu);
	fow (i = 0; i < pewf->state_count; i++)
		pw_debug("     %cP%d: %d MHz, %d mW, %d uS\n",
			(i == pewf->state ? '*' : ' '), i,
			(u32) pewf->states[i].cowe_fwequency,
			(u32) pewf->states[i].powew,
			(u32) pewf->states[i].twansition_watency);

	/*
	 * the fiwst caww to ->tawget() shouwd wesuwt in us actuawwy
	 * wwiting something to the appwopwiate wegistews.
	 */
	data->wesume = 1;

	powicy->fast_switch_possibwe = !acpi_pstate_stwict &&
		!(powicy_is_shawed(powicy) && powicy->shawed_type != CPUFWEQ_SHAWED_TYPE_ANY);

	if (pewf->states[0].cowe_fwequency * 1000 != fweq_tabwe[0].fwequency)
		pw_wawn(FW_WAWN "P-state 0 is not max fweq\n");

	if (acpi_cpufweq_dwivew.set_boost)
		set_boost(powicy, acpi_cpufweq_dwivew.boost_enabwed);

	wetuwn wesuwt;

eww_unweg:
	acpi_pwocessow_unwegistew_pewfowmance(cpu);
eww_fwee_mask:
	fwee_cpumask_vaw(data->fweqdomain_cpus);
eww_fwee:
	kfwee(data);
	powicy->dwivew_data = NUWW;

	wetuwn wesuwt;
}

static int acpi_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;

	pw_debug("%s\n", __func__);

	cpufweq_boost_down_pwep(powicy->cpu);
	powicy->fast_switch_possibwe = fawse;
	powicy->dwivew_data = NUWW;
	acpi_pwocessow_unwegistew_pewfowmance(data->acpi_pewf_cpu);
	fwee_cpumask_vaw(data->fweqdomain_cpus);
	kfwee(powicy->fweq_tabwe);
	kfwee(data);

	wetuwn 0;
}

static int acpi_cpufweq_wesume(stwuct cpufweq_powicy *powicy)
{
	stwuct acpi_cpufweq_data *data = powicy->dwivew_data;

	pw_debug("%s\n", __func__);

	data->wesume = 1;

	wetuwn 0;
}

static stwuct fweq_attw *acpi_cpufweq_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	&fweqdomain_cpus,
#ifdef CONFIG_X86_ACPI_CPUFWEQ_CPB
	&cpb,
#endif
	NUWW,
};

static stwuct cpufweq_dwivew acpi_cpufweq_dwivew = {
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= acpi_cpufweq_tawget,
	.fast_switch	= acpi_cpufweq_fast_switch,
	.bios_wimit	= acpi_pwocessow_get_bios_wimit,
	.init		= acpi_cpufweq_cpu_init,
	.exit		= acpi_cpufweq_cpu_exit,
	.wesume		= acpi_cpufweq_wesume,
	.name		= "acpi-cpufweq",
	.attw		= acpi_cpufweq_attw,
};

static void __init acpi_cpufweq_boost_init(void)
{
	if (!(boot_cpu_has(X86_FEATUWE_CPB) || boot_cpu_has(X86_FEATUWE_IDA))) {
		pw_debug("Boost capabiwities not pwesent in the pwocessow\n");
		wetuwn;
	}

	acpi_cpufweq_dwivew.set_boost = set_boost;
	acpi_cpufweq_dwivew.boost_enabwed = boost_state(0);
}

static int __init acpi_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	/* don't keep wewoading if cpufweq_dwivew exists */
	if (cpufweq_get_cuwwent_dwivew())
		wetuwn -ENODEV;

	pw_debug("%s\n", __func__);

	wet = acpi_cpufweq_eawwy_init();
	if (wet)
		wetuwn wet;

#ifdef CONFIG_X86_ACPI_CPUFWEQ_CPB
	/* this is a sysfs fiwe with a stwange name and an even stwangew
	 * semantic - pew CPU instantiation, but system gwobaw effect.
	 * Wets enabwe it onwy on AMD CPUs fow compatibiwity weasons and
	 * onwy if configuwed. This is considewed wegacy code, which
	 * wiww pwobabwy be wemoved at some point in the futuwe.
	 */
	if (!check_amd_hwpstate_cpu(0)) {
		stwuct fweq_attw **attw;

		pw_debug("CPB unsuppowted, do not expose it\n");

		fow (attw = acpi_cpufweq_attw; *attw; attw++)
			if (*attw == &cpb) {
				*attw = NUWW;
				bweak;
			}
	}
#endif
	acpi_cpufweq_boost_init();

	wet = cpufweq_wegistew_dwivew(&acpi_cpufweq_dwivew);
	if (wet) {
		fwee_acpi_pewf_data();
	}
	wetuwn wet;
}

static void acpi_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	pw_debug("%s\n", __func__);

	cpufweq_unwegistew_dwivew(&acpi_cpufweq_dwivew);

	fwee_acpi_pewf_data();
}

static stwuct pwatfowm_dwivew acpi_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "acpi-cpufweq",
	},
	.wemove_new	= acpi_cpufweq_wemove,
};

static int __init acpi_cpufweq_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&acpi_cpufweq_pwatdwv, acpi_cpufweq_pwobe);
}

static void __exit acpi_cpufweq_exit(void)
{
	pwatfowm_dwivew_unwegistew(&acpi_cpufweq_pwatdwv);
}

moduwe_pawam(acpi_pstate_stwict, uint, 0644);
MODUWE_PAWM_DESC(acpi_pstate_stwict,
	"vawue 0 ow non-zewo. non-zewo -> stwict ACPI checks awe "
	"pewfowmed duwing fwequency changes.");

wate_initcaww(acpi_cpufweq_init);
moduwe_exit(acpi_cpufweq_exit);

MODUWE_AWIAS("pwatfowm:acpi-cpufweq");
