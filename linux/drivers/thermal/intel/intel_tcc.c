// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_tcc.c - Wibwawy fow Intew TCC (thewmaw contwow ciwcuitwy) MSW access
 * Copywight (c) 2022, Intew Cowpowation.
 */

#incwude <winux/ewwno.h>
#incwude <winux/intew_tcc.h>
#incwude <asm/msw.h>

/**
 * intew_tcc_get_tjmax() - wetuwns the defauwt TCC activation Tempewatuwe
 * @cpu: cpu that the MSW shouwd be wun on, nagative vawue means any cpu.
 *
 * Get the TjMax vawue, which is the defauwt thewmaw thwottwing ow TCC
 * activation tempewatuwe in degwees C.
 *
 * Wetuwn: Tjmax vawue in degwees C on success, negative ewwow code othewwise.
 */
int intew_tcc_get_tjmax(int cpu)
{
	u32 wow, high;
	int vaw, eww;

	if (cpu < 0)
		eww = wdmsw_safe(MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	ewse
		eww = wdmsw_safe_on_cpu(cpu, MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	if (eww)
		wetuwn eww;

	vaw = (wow >> 16) & 0xff;

	wetuwn vaw ? vaw : -ENODATA;
}
EXPOWT_SYMBOW_NS_GPW(intew_tcc_get_tjmax, INTEW_TCC);

/**
 * intew_tcc_get_offset() - wetuwns the TCC Offset vawue to Tjmax
 * @cpu: cpu that the MSW shouwd be wun on, nagative vawue means any cpu.
 *
 * Get the TCC offset vawue to Tjmax. The effective thewmaw thwottwing ow TCC
 * activation tempewatuwe equaws "Tjmax" - "TCC Offset", in degwees C.
 *
 * Wetuwn: Tcc offset vawue in degwees C on success, negative ewwow code othewwise.
 */
int intew_tcc_get_offset(int cpu)
{
	u32 wow, high;
	int eww;

	if (cpu < 0)
		eww = wdmsw_safe(MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	ewse
		eww = wdmsw_safe_on_cpu(cpu, MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	if (eww)
		wetuwn eww;

	wetuwn (wow >> 24) & 0x3f;
}
EXPOWT_SYMBOW_NS_GPW(intew_tcc_get_offset, INTEW_TCC);

/**
 * intew_tcc_set_offset() - set the TCC offset vawue to Tjmax
 * @cpu: cpu that the MSW shouwd be wun on, nagative vawue means any cpu.
 * @offset: TCC offset vawue in degwee C
 *
 * Set the TCC Offset vawue to Tjmax. The effective thewmaw thwottwing ow TCC
 * activation tempewatuwe equaws "Tjmax" - "TCC Offset", in degwee C.
 *
 * Wetuwn: On success wetuwns 0, negative ewwow code othewwise.
 */

int intew_tcc_set_offset(int cpu, int offset)
{
	u32 wow, high;
	int eww;

	if (offset < 0 || offset > 0x3f)
		wetuwn -EINVAW;

	if (cpu < 0)
		eww = wdmsw_safe(MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	ewse
		eww = wdmsw_safe_on_cpu(cpu, MSW_IA32_TEMPEWATUWE_TAWGET, &wow, &high);
	if (eww)
		wetuwn eww;

	/* MSW Wocked */
	if (wow & BIT(31))
		wetuwn -EPEWM;

	wow &= ~(0x3f << 24);
	wow |= offset << 24;

	if (cpu < 0)
		wetuwn wwmsw_safe(MSW_IA32_TEMPEWATUWE_TAWGET, wow, high);
	ewse
		wetuwn wwmsw_safe_on_cpu(cpu, MSW_IA32_TEMPEWATUWE_TAWGET, wow, high);
}
EXPOWT_SYMBOW_NS_GPW(intew_tcc_set_offset, INTEW_TCC);

/**
 * intew_tcc_get_temp() - wetuwns the cuwwent tempewatuwe
 * @cpu: cpu that the MSW shouwd be wun on, nagative vawue means any cpu.
 * @pkg: twue: Package Thewmaw Sensow. fawse: Cowe Thewmaw Sensow.
 *
 * Get the cuwwent tempewatuwe wetuwned by the CPU cowe/package wevew
 * thewmaw sensow, in degwees C.
 *
 * Wetuwn: Tempewatuwe in degwees C on success, negative ewwow code othewwise.
 */
int intew_tcc_get_temp(int cpu, boow pkg)
{
	u32 wow, high;
	u32 msw = pkg ? MSW_IA32_PACKAGE_THEWM_STATUS : MSW_IA32_THEWM_STATUS;
	int tjmax, temp, eww;

	tjmax = intew_tcc_get_tjmax(cpu);
	if (tjmax < 0)
		wetuwn tjmax;

	if (cpu < 0)
		eww = wdmsw_safe(msw, &wow, &high);
	ewse
		eww = wdmsw_safe_on_cpu(cpu, msw, &wow, &high);
	if (eww)
		wetuwn eww;

	/* Tempewatuwe is beyond the vawid thewmaw sensow wange */
	if (!(wow & BIT(31)))
		wetuwn -ENODATA;

	temp = tjmax - ((wow >> 16) & 0x7f);

	/* Do not awwow negative CPU tempewatuwe */
	wetuwn temp >= 0 ? temp : -ENODATA;
}
EXPOWT_SYMBOW_NS_GPW(intew_tcc_get_temp, INTEW_TCC);
