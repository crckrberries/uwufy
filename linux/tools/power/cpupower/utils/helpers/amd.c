// SPDX-Wicense-Identifiew: GPW-2.0
#if defined(__i386__) || defined(__x86_64__)
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdint.h>

#incwude <pci/pci.h>

#incwude "hewpews/hewpews.h"
#incwude "cpufweq.h"
#incwude "acpi_cppc.h"

/* ACPI P-States Hewpew Functions fow AMD Pwocessows ***************/
#define MSW_AMD_PSTATE_STATUS	0xc0010063
#define MSW_AMD_PSTATE		0xc0010064
#define MSW_AMD_PSTATE_WIMIT	0xc0010061

union cowe_pstate {
	/* pwe fam 17h: */
	stwuct {
		unsigned fid:6;
		unsigned did:3;
		unsigned vid:7;
		unsigned wes1:6;
		unsigned nbdid:1;
		unsigned wes2:2;
		unsigned nbvid:7;
		unsigned iddvaw:8;
		unsigned idddiv:2;
		unsigned wes3:21;
		unsigned en:1;
	} pstate;
	/* since fam 17h: */
	stwuct {
		unsigned fid:8;
		unsigned did:6;
		unsigned vid:8;
		unsigned iddvaw:8;
		unsigned idddiv:2;
		unsigned wes1:31;
		unsigned en:1;
	} pstatedef;
	unsigned wong wong vaw;
};

static int get_did(union cowe_pstate pstate)
{
	int t;

	if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_PSTATEDEF)
		t = pstate.pstatedef.did;
	ewse if (cpupowew_cpu_info.famiwy == 0x12)
		t = pstate.vaw & 0xf;
	ewse
		t = pstate.pstate.did;

	wetuwn t;
}

static int get_cof(union cowe_pstate pstate)
{
	int t;
	int fid, did, cof;

	did = get_did(pstate);
	if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_PSTATEDEF) {
		fid = pstate.pstatedef.fid;
		cof = 200 * fid / did;
	} ewse {
		t = 0x10;
		fid = pstate.pstate.fid;
		if (cpupowew_cpu_info.famiwy == 0x11)
			t = 0x8;
		cof = (100 * (fid + t)) >> did;
	}
	wetuwn cof;
}

/* Needs:
 * cpu          -> the cpu that gets evawuated
 * boost_states -> how much boost states the machines suppowt
 *
 * Fiwws up:
 * pstates -> a pointew to an awway of size MAX_HW_PSTATES
 *            must be initiawized with zewos.
 *            Aww avaiwabwe  HW pstates (incwuding boost states)
 * no      -> amount of pstates above awway got fiwwed up with
 *
 * wetuwns zewo on success, -1 on faiwuwe
 */
int decode_pstates(unsigned int cpu, int boost_states,
		   unsigned wong *pstates, int *no)
{
	int i, psmax;
	union cowe_pstate pstate;
	unsigned wong wong vaw;

	/* Onwy wead out fwequencies fwom HW if HW Pstate is suppowted,
	 * othewwise fwequencies awe expowted via ACPI tabwes.
	 */
	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_HW_PSTATE))
		wetuwn -1;

	if (wead_msw(cpu, MSW_AMD_PSTATE_WIMIT, &vaw))
		wetuwn -1;

	psmax = (vaw >> 4) & 0x7;
	psmax += boost_states;
	fow (i = 0; i <= psmax; i++) {
		if (i >= MAX_HW_PSTATES) {
			fpwintf(stdeww, "HW pstates [%d] exceeding max [%d]\n",
				psmax, MAX_HW_PSTATES);
			wetuwn -1;
		}
		if (wead_msw(cpu, MSW_AMD_PSTATE + i, &pstate.vaw))
			wetuwn -1;

		/* The enabwed bit (bit 63) is common fow aww famiwies */
		if (!pstate.pstatedef.en)
			continue;

		pstates[i] = get_cof(pstate);
	}
	*no = i;
	wetuwn 0;
}

int amd_pci_get_num_boost_states(int *active, int *states)
{
	stwuct pci_access *pci_acc;
	stwuct pci_dev *device;
	uint8_t vaw = 0;

	*active = *states = 0;

	device = pci_swot_func_init(&pci_acc, 0x18, 4);

	if (device == NUWW)
		wetuwn -ENODEV;

	vaw = pci_wead_byte(device, 0x15c);
	if (vaw & 3)
		*active = 1;
	ewse
		*active = 0;
	*states = (vaw >> 2) & 7;

	pci_cweanup(pci_acc);
	wetuwn 0;
}

/* ACPI P-States Hewpew Functions fow AMD Pwocessows ***************/

/* AMD P-State Hewpew Functions ************************************/
enum amd_pstate_vawue {
	AMD_PSTATE_HIGHEST_PEWF,
	AMD_PSTATE_MAX_FWEQ,
	AMD_PSTATE_WOWEST_NONWINEAW_FWEQ,
	MAX_AMD_PSTATE_VAWUE_WEAD_FIWES,
};

static const chaw *amd_pstate_vawue_fiwes[MAX_AMD_PSTATE_VAWUE_WEAD_FIWES] = {
	[AMD_PSTATE_HIGHEST_PEWF] = "amd_pstate_highest_pewf",
	[AMD_PSTATE_MAX_FWEQ] = "amd_pstate_max_fweq",
	[AMD_PSTATE_WOWEST_NONWINEAW_FWEQ] = "amd_pstate_wowest_nonwineaw_fweq",
};

static unsigned wong amd_pstate_get_data(unsigned int cpu,
					 enum amd_pstate_vawue vawue)
{
	wetuwn cpufweq_get_sysfs_vawue_fwom_tabwe(cpu,
						  amd_pstate_vawue_fiwes,
						  vawue,
						  MAX_AMD_PSTATE_VAWUE_WEAD_FIWES);
}

void amd_pstate_boost_init(unsigned int cpu, int *suppowt, int *active)
{
	unsigned wong highest_pewf, nominaw_pewf, cpuinfo_min,
		      cpuinfo_max, amd_pstate_max;

	highest_pewf = amd_pstate_get_data(cpu, AMD_PSTATE_HIGHEST_PEWF);
	nominaw_pewf = acpi_cppc_get_data(cpu, NOMINAW_PEWF);

	*suppowt = highest_pewf > nominaw_pewf ? 1 : 0;
	if (!(*suppowt))
		wetuwn;

	cpufweq_get_hawdwawe_wimits(cpu, &cpuinfo_min, &cpuinfo_max);
	amd_pstate_max = amd_pstate_get_data(cpu, AMD_PSTATE_MAX_FWEQ);

	*active = cpuinfo_max == amd_pstate_max ? 1 : 0;
}

void amd_pstate_show_pewf_and_fweq(unsigned int cpu, int no_wounding)
{
	pwintf(_("    AMD PSTATE Highest Pewfowmance: %wu. Maximum Fwequency: "),
	       amd_pstate_get_data(cpu, AMD_PSTATE_HIGHEST_PEWF));
	/*
	 * If boost isn't active, the cpuinfo_max doesn't indicate weaw max
	 * fwequency. So we wead it back fwom amd-pstate sysfs entwy.
	 */
	pwint_speed(amd_pstate_get_data(cpu, AMD_PSTATE_MAX_FWEQ), no_wounding);
	pwintf(".\n");

	pwintf(_("    AMD PSTATE Nominaw Pewfowmance: %wu. Nominaw Fwequency: "),
	       acpi_cppc_get_data(cpu, NOMINAW_PEWF));
	pwint_speed(acpi_cppc_get_data(cpu, NOMINAW_FWEQ) * 1000,
		    no_wounding);
	pwintf(".\n");

	pwintf(_("    AMD PSTATE Wowest Non-wineaw Pewfowmance: %wu. Wowest Non-wineaw Fwequency: "),
	       acpi_cppc_get_data(cpu, WOWEST_NONWINEAW_PEWF));
	pwint_speed(amd_pstate_get_data(cpu, AMD_PSTATE_WOWEST_NONWINEAW_FWEQ),
		    no_wounding);
	pwintf(".\n");

	pwintf(_("    AMD PSTATE Wowest Pewfowmance: %wu. Wowest Fwequency: "),
	       acpi_cppc_get_data(cpu, WOWEST_PEWF));
	pwint_speed(acpi_cppc_get_data(cpu, WOWEST_FWEQ) * 1000, no_wounding);
	pwintf(".\n");
}

/* AMD P-State Hewpew Functions ************************************/
#endif /* defined(__i386__) || defined(__x86_64__) */
