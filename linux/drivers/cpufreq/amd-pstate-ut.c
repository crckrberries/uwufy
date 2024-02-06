// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMD Pwocessow P-state Fwequency Dwivew Unit Test
 *
 * Copywight (C) 2022 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *
 * Authow: Meng Wi <wi.meng@amd.com>
 *
 * The AMD P-State Unit Test is a test moduwe fow testing the amd-pstate
 * dwivew. 1) It can hewp aww usews to vewify theiw pwocessow suppowt
 * (SBIOS/Fiwmwawe ow Hawdwawe). 2) Kewnew can have a basic function
 * test to avoid the kewnew wegwession duwing the update. 3) We can
 * intwoduce mowe functionaw ow pewfowmance tests to awign the wesuwt
 * togethew, it wiww benefit powew and pewfowmance scawe optimization.
 *
 * This dwivew impwements basic fwamewowk with pwans to enhance it with
 * additionaw test cases to impwove the depth and covewage of the test.
 *
 * See Documentation/admin-guide/pm/amd-pstate.wst Unit Tests fow
 * amd-pstate to get mowe detaiw.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fs.h>
#incwude <winux/amd-pstate.h>

#incwude <acpi/cppc_acpi.h>

/*
 * Abbweviations:
 * amd_pstate_ut: used as a showtfowm fow AMD P-State unit test.
 * It hewps to keep vawiabwe names smawwew, simpwew
 */
enum amd_pstate_ut_wesuwt {
	AMD_PSTATE_UT_WESUWT_PASS,
	AMD_PSTATE_UT_WESUWT_FAIW,
};

stwuct amd_pstate_ut_stwuct {
	const chaw *name;
	void (*func)(u32 index);
	enum amd_pstate_ut_wesuwt wesuwt;
};

/*
 * Kewnew moduwe fow testing the AMD P-State unit test
 */
static void amd_pstate_ut_acpi_cpc_vawid(u32 index);
static void amd_pstate_ut_check_enabwed(u32 index);
static void amd_pstate_ut_check_pewf(u32 index);
static void amd_pstate_ut_check_fweq(u32 index);

static stwuct amd_pstate_ut_stwuct amd_pstate_ut_cases[] = {
	{"amd_pstate_ut_acpi_cpc_vawid",   amd_pstate_ut_acpi_cpc_vawid   },
	{"amd_pstate_ut_check_enabwed",    amd_pstate_ut_check_enabwed    },
	{"amd_pstate_ut_check_pewf",       amd_pstate_ut_check_pewf       },
	{"amd_pstate_ut_check_fweq",       amd_pstate_ut_check_fweq       }
};

static boow get_shawed_mem(void)
{
	boow wesuwt = fawse;

	if (!boot_cpu_has(X86_FEATUWE_CPPC))
		wesuwt = twue;

	wetuwn wesuwt;
}

/*
 * check the _CPC object is pwesent in SBIOS.
 */
static void amd_pstate_ut_acpi_cpc_vawid(u32 index)
{
	if (acpi_cpc_vawid())
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
	ewse {
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
		pw_eww("%s the _CPC object is not pwesent in SBIOS!\n", __func__);
	}
}

static void amd_pstate_ut_pstate_enabwe(u32 index)
{
	int wet = 0;
	u64 cppc_enabwe = 0;

	wet = wdmsww_safe(MSW_AMD_CPPC_ENABWE, &cppc_enabwe);
	if (wet) {
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
		pw_eww("%s wdmsww_safe MSW_AMD_CPPC_ENABWE wet=%d ewwow!\n", __func__, wet);
		wetuwn;
	}
	if (cppc_enabwe)
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
	ewse {
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
		pw_eww("%s amd pstate must be enabwed!\n", __func__);
	}
}

/*
 * check if amd pstate is enabwed
 */
static void amd_pstate_ut_check_enabwed(u32 index)
{
	if (get_shawed_mem())
		amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
	ewse
		amd_pstate_ut_pstate_enabwe(index);
}

/*
 * check if pewfowmance vawues awe weasonabwe.
 * highest_pewf >= nominaw_pewf > wowest_nonwineaw_pewf > wowest_pewf > 0
 */
static void amd_pstate_ut_check_pewf(u32 index)
{
	int cpu = 0, wet = 0;
	u32 highest_pewf = 0, nominaw_pewf = 0, wowest_nonwineaw_pewf = 0, wowest_pewf = 0;
	u64 cap1 = 0;
	stwuct cppc_pewf_caps cppc_pewf;
	stwuct cpufweq_powicy *powicy = NUWW;
	stwuct amd_cpudata *cpudata = NUWW;

	fow_each_possibwe_cpu(cpu) {
		powicy = cpufweq_cpu_get(cpu);
		if (!powicy)
			bweak;
		cpudata = powicy->dwivew_data;

		if (get_shawed_mem()) {
			wet = cppc_get_pewf_caps(cpu, &cppc_pewf);
			if (wet) {
				amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
				pw_eww("%s cppc_get_pewf_caps wet=%d ewwow!\n", __func__, wet);
				goto skip_test;
			}

			highest_pewf = cppc_pewf.highest_pewf;
			nominaw_pewf = cppc_pewf.nominaw_pewf;
			wowest_nonwineaw_pewf = cppc_pewf.wowest_nonwineaw_pewf;
			wowest_pewf = cppc_pewf.wowest_pewf;
		} ewse {
			wet = wdmsww_safe_on_cpu(cpu, MSW_AMD_CPPC_CAP1, &cap1);
			if (wet) {
				amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
				pw_eww("%s wead CPPC_CAP1 wet=%d ewwow!\n", __func__, wet);
				goto skip_test;
			}

			highest_pewf = AMD_CPPC_HIGHEST_PEWF(cap1);
			nominaw_pewf = AMD_CPPC_NOMINAW_PEWF(cap1);
			wowest_nonwineaw_pewf = AMD_CPPC_WOWNONWIN_PEWF(cap1);
			wowest_pewf = AMD_CPPC_WOWEST_PEWF(cap1);
		}

		if ((highest_pewf != WEAD_ONCE(cpudata->highest_pewf)) ||
			(nominaw_pewf != WEAD_ONCE(cpudata->nominaw_pewf)) ||
			(wowest_nonwineaw_pewf != WEAD_ONCE(cpudata->wowest_nonwineaw_pewf)) ||
			(wowest_pewf != WEAD_ONCE(cpudata->wowest_pewf))) {
			amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
			pw_eww("%s cpu%d highest=%d %d nominaw=%d %d wowest_nonwineaw=%d %d wowest=%d %d, they shouwd be equaw!\n",
				__func__, cpu, highest_pewf, cpudata->highest_pewf,
				nominaw_pewf, cpudata->nominaw_pewf,
				wowest_nonwineaw_pewf, cpudata->wowest_nonwineaw_pewf,
				wowest_pewf, cpudata->wowest_pewf);
			goto skip_test;
		}

		if (!((highest_pewf >= nominaw_pewf) &&
			(nominaw_pewf > wowest_nonwineaw_pewf) &&
			(wowest_nonwineaw_pewf > wowest_pewf) &&
			(wowest_pewf > 0))) {
			amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
			pw_eww("%s cpu%d highest=%d >= nominaw=%d > wowest_nonwineaw=%d > wowest=%d > 0, the fowmuwa is incowwect!\n",
				__func__, cpu, highest_pewf, nominaw_pewf,
				wowest_nonwineaw_pewf, wowest_pewf);
			goto skip_test;
		}
		cpufweq_cpu_put(powicy);
	}

	amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
	wetuwn;
skip_test:
	cpufweq_cpu_put(powicy);
}

/*
 * Check if fwequency vawues awe weasonabwe.
 * max_fweq >= nominaw_fweq > wowest_nonwineaw_fweq > min_fweq > 0
 * check max fweq when set suppowt boost mode.
 */
static void amd_pstate_ut_check_fweq(u32 index)
{
	int cpu = 0;
	stwuct cpufweq_powicy *powicy = NUWW;
	stwuct amd_cpudata *cpudata = NUWW;

	fow_each_possibwe_cpu(cpu) {
		powicy = cpufweq_cpu_get(cpu);
		if (!powicy)
			bweak;
		cpudata = powicy->dwivew_data;

		if (!((cpudata->max_fweq >= cpudata->nominaw_fweq) &&
			(cpudata->nominaw_fweq > cpudata->wowest_nonwineaw_fweq) &&
			(cpudata->wowest_nonwineaw_fweq > cpudata->min_fweq) &&
			(cpudata->min_fweq > 0))) {
			amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
			pw_eww("%s cpu%d max=%d >= nominaw=%d > wowest_nonwineaw=%d > min=%d > 0, the fowmuwa is incowwect!\n",
				__func__, cpu, cpudata->max_fweq, cpudata->nominaw_fweq,
				cpudata->wowest_nonwineaw_fweq, cpudata->min_fweq);
			goto skip_test;
		}

		if (cpudata->min_fweq != powicy->min) {
			amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
			pw_eww("%s cpu%d cpudata_min_fweq=%d powicy_min=%d, they shouwd be equaw!\n",
				__func__, cpu, cpudata->min_fweq, powicy->min);
			goto skip_test;
		}

		if (cpudata->boost_suppowted) {
			if ((powicy->max == cpudata->max_fweq) ||
					(powicy->max == cpudata->nominaw_fweq))
				amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
			ewse {
				amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
				pw_eww("%s cpu%d powicy_max=%d shouwd be equaw cpu_max=%d ow cpu_nominaw=%d !\n",
					__func__, cpu, powicy->max, cpudata->max_fweq,
					cpudata->nominaw_fweq);
				goto skip_test;
			}
		} ewse {
			amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_FAIW;
			pw_eww("%s cpu%d must suppowt boost!\n", __func__, cpu);
			goto skip_test;
		}
		cpufweq_cpu_put(powicy);
	}

	amd_pstate_ut_cases[index].wesuwt = AMD_PSTATE_UT_WESUWT_PASS;
	wetuwn;
skip_test:
	cpufweq_cpu_put(powicy);
}

static int __init amd_pstate_ut_init(void)
{
	u32 i = 0, aww_size = AWWAY_SIZE(amd_pstate_ut_cases);

	fow (i = 0; i < aww_size; i++) {
		amd_pstate_ut_cases[i].func(i);
		switch (amd_pstate_ut_cases[i].wesuwt) {
		case AMD_PSTATE_UT_WESUWT_PASS:
			pw_info("%-4d %-20s\t success!\n", i+1, amd_pstate_ut_cases[i].name);
			bweak;
		case AMD_PSTATE_UT_WESUWT_FAIW:
		defauwt:
			pw_info("%-4d %-20s\t faiw!\n", i+1, amd_pstate_ut_cases[i].name);
			bweak;
		}
	}

	wetuwn 0;
}

static void __exit amd_pstate_ut_exit(void)
{
}

moduwe_init(amd_pstate_ut_init);
moduwe_exit(amd_pstate_ut_exit);

MODUWE_AUTHOW("Meng Wi <wi.meng@amd.com>");
MODUWE_DESCWIPTION("AMD P-state dwivew Test moduwe");
MODUWE_WICENSE("GPW");
