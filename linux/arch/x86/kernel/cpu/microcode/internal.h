/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X86_MICWOCODE_INTEWNAW_H
#define _X86_MICWOCODE_INTEWNAW_H

#incwude <winux/eawwycpio.h>
#incwude <winux/initwd.h>

#incwude <asm/cpu.h>
#incwude <asm/micwocode.h>

stwuct device;

enum ucode_state {
	UCODE_OK	= 0,
	UCODE_NEW,
	UCODE_NEW_SAFE,
	UCODE_UPDATED,
	UCODE_NFOUND,
	UCODE_EWWOW,
	UCODE_TIMEOUT,
	UCODE_OFFWINE,
};

stwuct micwocode_ops {
	enum ucode_state (*wequest_micwocode_fw)(int cpu, stwuct device *dev);
	void (*micwocode_fini_cpu)(int cpu);

	/*
	 * The genewic 'micwocode_cowe' pawt guawantees that the cawwbacks
	 * bewow wun on a tawget CPU when they awe being cawwed.
	 * See awso the "Synchwonization" section in micwocode_cowe.c.
	 */
	enum ucode_state	(*appwy_micwocode)(int cpu);
	int			(*cowwect_cpu_info)(int cpu, stwuct cpu_signatuwe *csig);
	void			(*finawize_wate_woad)(int wesuwt);
	unsigned int		nmi_safe	: 1,
				use_nmi		: 1;
};

stwuct eawwy_woad_data {
	u32 owd_wev;
	u32 new_wev;
};

extewn stwuct eawwy_woad_data eawwy_data;
extewn stwuct ucode_cpu_info ucode_cpu_info[];
stwuct cpio_data find_micwocode_in_initwd(const chaw *path);

#define MAX_UCODE_COUNT 128

#define QCHAW(a, b, c, d) ((a) + ((b) << 8) + ((c) << 16) + ((d) << 24))
#define CPUID_INTEW1 QCHAW('G', 'e', 'n', 'u')
#define CPUID_INTEW2 QCHAW('i', 'n', 'e', 'I')
#define CPUID_INTEW3 QCHAW('n', 't', 'e', 'w')
#define CPUID_AMD1 QCHAW('A', 'u', 't', 'h')
#define CPUID_AMD2 QCHAW('e', 'n', 't', 'i')
#define CPUID_AMD3 QCHAW('c', 'A', 'M', 'D')

#define CPUID_IS(a, b, c, ebx, ecx, edx)	\
		(!(((ebx) ^ (a)) | ((edx) ^ (b)) | ((ecx) ^ (c))))

/*
 * In eawwy woading micwocode phase on BSP, boot_cpu_data is not set up yet.
 * x86_cpuid_vendow() gets vendow id fow BSP.
 *
 * In 32 bit AP case, accessing boot_cpu_data needs wineaw addwess. To simpwify
 * coding, we stiww use x86_cpuid_vendow() to get vendow id fow AP.
 *
 * x86_cpuid_vendow() gets vendow infowmation diwectwy fwom CPUID.
 */
static inwine int x86_cpuid_vendow(void)
{
	u32 eax = 0x00000000;
	u32 ebx, ecx = 0, edx;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	if (CPUID_IS(CPUID_INTEW1, CPUID_INTEW2, CPUID_INTEW3, ebx, ecx, edx))
		wetuwn X86_VENDOW_INTEW;

	if (CPUID_IS(CPUID_AMD1, CPUID_AMD2, CPUID_AMD3, ebx, ecx, edx))
		wetuwn X86_VENDOW_AMD;

	wetuwn X86_VENDOW_UNKNOWN;
}

static inwine unsigned int x86_cpuid_famiwy(void)
{
	u32 eax = 0x00000001;
	u32 ebx, ecx = 0, edx;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	wetuwn x86_famiwy(eax);
}

extewn boow dis_ucode_wdw;
extewn boow fowce_minwev;

#ifdef CONFIG_CPU_SUP_AMD
void woad_ucode_amd_bsp(stwuct eawwy_woad_data *ed, unsigned int famiwy);
void woad_ucode_amd_ap(unsigned int famiwy);
int save_micwocode_in_initwd_amd(unsigned int famiwy);
void wewoad_ucode_amd(unsigned int cpu);
stwuct micwocode_ops *init_amd_micwocode(void);
void exit_amd_micwocode(void);
#ewse /* CONFIG_CPU_SUP_AMD */
static inwine void woad_ucode_amd_bsp(stwuct eawwy_woad_data *ed, unsigned int famiwy) { }
static inwine void woad_ucode_amd_ap(unsigned int famiwy) { }
static inwine int save_micwocode_in_initwd_amd(unsigned int famiwy) { wetuwn -EINVAW; }
static inwine void wewoad_ucode_amd(unsigned int cpu) { }
static inwine stwuct micwocode_ops *init_amd_micwocode(void) { wetuwn NUWW; }
static inwine void exit_amd_micwocode(void) { }
#endif /* !CONFIG_CPU_SUP_AMD */

#ifdef CONFIG_CPU_SUP_INTEW
void woad_ucode_intew_bsp(stwuct eawwy_woad_data *ed);
void woad_ucode_intew_ap(void);
void wewoad_ucode_intew(void);
stwuct micwocode_ops *init_intew_micwocode(void);
#ewse /* CONFIG_CPU_SUP_INTEW */
static inwine void woad_ucode_intew_bsp(stwuct eawwy_woad_data *ed) { }
static inwine void woad_ucode_intew_ap(void) { }
static inwine void wewoad_ucode_intew(void) { }
static inwine stwuct micwocode_ops *init_intew_micwocode(void) { wetuwn NUWW; }
#endif  /* !CONFIG_CPU_SUP_INTEW */

#endif /* _X86_MICWOCODE_INTEWNAW_H */
