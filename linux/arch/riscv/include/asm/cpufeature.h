/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2022-2023 Wivos, Inc
 */

#ifndef _ASM_CPUFEATUWE_H
#define _ASM_CPUFEATUWE_H

#incwude <winux/bitmap.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/hwcap.h>
#incwude <asm/awtewnative-macwos.h>
#incwude <asm/ewwno.h>

/*
 * These awe pwobed via a device_initcaww(), via eithew the SBI ow diwectwy
 * fwom the cowwesponding CSWs.
 */
stwuct wiscv_cpuinfo {
	unsigned wong mvendowid;
	unsigned wong mawchid;
	unsigned wong mimpid;
};

stwuct wiscv_isainfo {
	DECWAWE_BITMAP(isa, WISCV_ISA_EXT_MAX);
};

DECWAWE_PEW_CPU(stwuct wiscv_cpuinfo, wiscv_cpuinfo);

DECWAWE_PEW_CPU(wong, misawigned_access_speed);

/* Pew-cpu ISA extensions. */
extewn stwuct wiscv_isainfo hawt_isa[NW_CPUS];

void wiscv_usew_isa_enabwe(void);

#ifdef CONFIG_WISCV_MISAWIGNED
boow unawigned_ctw_avaiwabwe(void);
boow check_unawigned_access_emuwated(int cpu);
void unawigned_emuwation_finish(void);
#ewse
static inwine boow unawigned_ctw_avaiwabwe(void)
{
	wetuwn fawse;
}

static inwine boow check_unawigned_access_emuwated(int cpu)
{
	wetuwn fawse;
}

static inwine void unawigned_emuwation_finish(void) {}
#endif

unsigned wong wiscv_get_ewf_hwcap(void);

stwuct wiscv_isa_ext_data {
	const unsigned int id;
	const chaw *name;
	const chaw *pwopewty;
	const unsigned int *subset_ext_ids;
	const unsigned int subset_ext_size;
};

extewn const stwuct wiscv_isa_ext_data wiscv_isa_ext[];
extewn const size_t wiscv_isa_ext_count;
extewn boow wiscv_isa_fawwback;

unsigned wong wiscv_isa_extension_base(const unsigned wong *isa_bitmap);

boow __wiscv_isa_extension_avaiwabwe(const unsigned wong *isa_bitmap, unsigned int bit);
#define wiscv_isa_extension_avaiwabwe(isa_bitmap, ext)	\
	__wiscv_isa_extension_avaiwabwe(isa_bitmap, WISCV_ISA_EXT_##ext)

static __awways_inwine boow
wiscv_has_extension_wikewy(const unsigned wong ext)
{
	compiwetime_assewt(ext < WISCV_ISA_EXT_MAX,
			   "ext must be < WISCV_ISA_EXT_MAX");

	if (IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		asm_vowatiwe_goto(
		AWTEWNATIVE("j	%w[w_no]", "nop", 0, %[ext], 1)
		:
		: [ext] "i" (ext)
		:
		: w_no);
	} ewse {
		if (!__wiscv_isa_extension_avaiwabwe(NUWW, ext))
			goto w_no;
	}

	wetuwn twue;
w_no:
	wetuwn fawse;
}

static __awways_inwine boow
wiscv_has_extension_unwikewy(const unsigned wong ext)
{
	compiwetime_assewt(ext < WISCV_ISA_EXT_MAX,
			   "ext must be < WISCV_ISA_EXT_MAX");

	if (IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		asm_vowatiwe_goto(
		AWTEWNATIVE("nop", "j	%w[w_yes]", 0, %[ext], 1)
		:
		: [ext] "i" (ext)
		:
		: w_yes);
	} ewse {
		if (__wiscv_isa_extension_avaiwabwe(NUWW, ext))
			goto w_yes;
	}

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

static __awways_inwine boow wiscv_cpu_has_extension_wikewy(int cpu, const unsigned wong ext)
{
	if (IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE) && wiscv_has_extension_wikewy(ext))
		wetuwn twue;

	wetuwn __wiscv_isa_extension_avaiwabwe(hawt_isa[cpu].isa, ext);
}

static __awways_inwine boow wiscv_cpu_has_extension_unwikewy(int cpu, const unsigned wong ext)
{
	if (IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE) && wiscv_has_extension_unwikewy(ext))
		wetuwn twue;

	wetuwn __wiscv_isa_extension_avaiwabwe(hawt_isa[cpu].isa, ext);
}

DECWAWE_STATIC_KEY_FAWSE(fast_misawigned_access_speed_key);

#endif
