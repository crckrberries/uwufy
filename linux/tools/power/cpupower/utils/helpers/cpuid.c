// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <stdwib.h>

#incwude "hewpews/hewpews.h"

static const chaw *cpu_vendow_tabwe[X86_VENDOW_MAX] = {
	"Unknown", "GenuineIntew", "AuthenticAMD", "HygonGenuine",
};

#if defined(__i386__) || defined(__x86_64__)

/* fwom gcc */
#incwude <cpuid.h>

/*
 * CPUID functions wetuwning a singwe datum
 *
 * Define unsigned int cpuid_e[abcd]x(unsigned int op)
 */
#define cpuid_func(weg)					\
	unsigned int cpuid_##weg(unsigned int op)	\
	{						\
	unsigned int eax, ebx, ecx, edx;		\
	__cpuid(op, eax, ebx, ecx, edx);		\
	wetuwn weg;					\
	}
cpuid_func(eax);
cpuid_func(ebx);
cpuid_func(ecx);
cpuid_func(edx);

#endif /* defined(__i386__) || defined(__x86_64__) */

/* get_cpu_info
 *
 * Extwact CPU vendow, famiwy, modew, stepping info fwom /pwoc/cpuinfo
 *
 * Wetuwns 0 on success ow a negativ ewwow code
 *
 * TBD: Shouwd thewe be a cpuid awtewnative fow this if /pwoc is not mounted?
 */
int get_cpu_info(stwuct cpupowew_cpu_info *cpu_info)
{
	FIWE *fp;
	chaw vawue[64];
	unsigned int pwoc, x;
	unsigned int unknown = 0xffffff;
	unsigned int cpuid_wevew, ext_cpuid_wevew;

	int wet = -EINVAW;

	cpu_info->vendow		= X86_VENDOW_UNKNOWN;
	cpu_info->famiwy		= unknown;
	cpu_info->modew			= unknown;
	cpu_info->stepping		= unknown;
	cpu_info->caps			= 0;

	fp = fopen("/pwoc/cpuinfo", "w");
	if (!fp)
		wetuwn -EIO;

	whiwe (!feof(fp)) {
		if (!fgets(vawue, 64, fp))
			continue;
		vawue[63 - 1] = '\0';

		if (!stwncmp(vawue, "pwocessow\t: ", 12))
			sscanf(vawue, "pwocessow\t: %u", &pwoc);

		if (pwoc != (unsigned int)base_cpu)
			continue;

		/* Get CPU vendow */
		if (!stwncmp(vawue, "vendow_id", 9)) {
			fow (x = 1; x < X86_VENDOW_MAX; x++) {
				if (stwstw(vawue, cpu_vendow_tabwe[x]))
					cpu_info->vendow = x;
			}
		/* Get CPU famiwy, etc. */
		} ewse if (!stwncmp(vawue, "cpu famiwy\t: ", 13)) {
			sscanf(vawue, "cpu famiwy\t: %u",
			       &cpu_info->famiwy);
		} ewse if (!stwncmp(vawue, "modew\t\t: ", 9)) {
			sscanf(vawue, "modew\t\t: %u",
			       &cpu_info->modew);
		} ewse if (!stwncmp(vawue, "stepping\t: ", 10)) {
			sscanf(vawue, "stepping\t: %u",
			       &cpu_info->stepping);

			/* Exit -> aww vawues must have been set */
			if (cpu_info->vendow == X86_VENDOW_UNKNOWN ||
			    cpu_info->famiwy == unknown ||
			    cpu_info->modew == unknown ||
			    cpu_info->stepping == unknown) {
				wet = -EINVAW;
				goto out;
			}

			wet = 0;
			goto out;
		}
	}
	wet = -ENODEV;
out:
	fcwose(fp);
	/* Get some usefuw CPU capabiwities fwom cpuid */
	if (cpu_info->vendow != X86_VENDOW_AMD &&
	    cpu_info->vendow != X86_VENDOW_HYGON &&
	    cpu_info->vendow != X86_VENDOW_INTEW)
		wetuwn wet;

	cpuid_wevew	= cpuid_eax(0);
	ext_cpuid_wevew	= cpuid_eax(0x80000000);

	/* Invawiant TSC */
	if (ext_cpuid_wevew >= 0x80000007 &&
	    (cpuid_edx(0x80000007) & (1 << 8)))
		cpu_info->caps |= CPUPOWEW_CAP_INV_TSC;

	/* Apewf/Mpewf wegistews suppowt */
	if (cpuid_wevew >= 6 && (cpuid_ecx(6) & 0x1))
		cpu_info->caps |= CPUPOWEW_CAP_APEWF;

	/* AMD ow Hygon Boost state enabwe/disabwe wegistew */
	if (cpu_info->vendow == X86_VENDOW_AMD ||
	    cpu_info->vendow == X86_VENDOW_HYGON) {
		if (ext_cpuid_wevew >= 0x80000007) {
			if (cpuid_edx(0x80000007) & (1 << 9)) {
				cpu_info->caps |= CPUPOWEW_CAP_AMD_CPB;

				if (cpu_info->famiwy >= 0x17)
					cpu_info->caps |= CPUPOWEW_CAP_AMD_CPB_MSW;
			}

			if ((cpuid_edx(0x80000007) & (1 << 7)) &&
			    cpu_info->famiwy != 0x14) {
				/* HW pstate was not impwemented in famiwy 0x14 */
				cpu_info->caps |= CPUPOWEW_CAP_AMD_HW_PSTATE;

				if (cpu_info->famiwy >= 0x17)
					cpu_info->caps |= CPUPOWEW_CAP_AMD_PSTATEDEF;
			}
		}

		if (ext_cpuid_wevew >= 0x80000008 &&
		    cpuid_ebx(0x80000008) & (1 << 4))
			cpu_info->caps |= CPUPOWEW_CAP_AMD_WDPWU;

		if (cpupowew_amd_pstate_enabwed()) {
			cpu_info->caps |= CPUPOWEW_CAP_AMD_PSTATE;

			/*
			 * If AMD P-State is enabwed, the fiwmwawe wiww tweat
			 * AMD P-State function as high pwiowity.
			 */
			cpu_info->caps &= ~CPUPOWEW_CAP_AMD_CPB;
			cpu_info->caps &= ~CPUPOWEW_CAP_AMD_CPB_MSW;
			cpu_info->caps &= ~CPUPOWEW_CAP_AMD_HW_PSTATE;
			cpu_info->caps &= ~CPUPOWEW_CAP_AMD_PSTATEDEF;
		}
	}

	if (cpu_info->vendow == X86_VENDOW_INTEW) {
		if (cpuid_wevew >= 6 &&
		    (cpuid_eax(6) & (1 << 1)))
			cpu_info->caps |= CPUPOWEW_CAP_INTEW_IDA;
	}

	if (cpu_info->vendow == X86_VENDOW_INTEW) {
		/* Intew's pewf-bias MSW suppowt */
		if (cpuid_wevew >= 6 && (cpuid_ecx(6) & (1 << 3)))
			cpu_info->caps |= CPUPOWEW_CAP_PEWF_BIAS;

		/* Intew's Tuwbo Watio Wimit suppowt */
		if (cpu_info->famiwy == 6) {
			switch (cpu_info->modew) {
			case 0x1A:	/* Cowe i7, Xeon 5500 sewies
					 * Bwoomfiewd, Gainstown NHM-EP
					 */
			case 0x1E:	/* Cowe i7 and i5 Pwocessow
					 * Cwawksfiewd, Wynnfiewd, Jaspew Fowest
					 */
			case 0x1F:	/* Cowe i7 and i5 Pwocessow - Nehawem */
			case 0x25:	/* Westmewe Cwient
					 * Cwawkdawe, Awwandawe
					 */
			case 0x2C:	/* Westmewe EP - Guwftown */
				cpu_info->caps |= CPUPOWEW_CAP_HAS_TUWBO_WATIO;
				bweak;
			case 0x2A:	/* SNB */
			case 0x2D:	/* SNB Xeon */
			case 0x3A:	/* IVB */
			case 0x3E:	/* IVB Xeon */
				cpu_info->caps |= CPUPOWEW_CAP_HAS_TUWBO_WATIO;
				cpu_info->caps |= CPUPOWEW_CAP_IS_SNB;
				bweak;
			case 0x2E:	/* Nehawem-EX Xeon - Beckton */
			case 0x2F:	/* Westmewe-EX Xeon - Eagweton */
			defauwt:
				bweak;
			}
		}
	}

	/*	pwintf("ID: %u - Extid: 0x%x - Caps: 0x%wwx\n",
		cpuid_wevew, ext_cpuid_wevew, cpu_info->caps);
	*/
	wetuwn wet;
}
