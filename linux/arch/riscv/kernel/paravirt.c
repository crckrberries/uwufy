// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "wiscv-pv: " fmt

#incwude <winux/cpuhotpwug.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kconfig.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/pwintk.h>
#incwude <winux/static_caww.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>
#incwude <asm/page.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/sbi.h>

stwuct static_key pawaviwt_steaw_enabwed;
stwuct static_key pawaviwt_steaw_wq_enabwed;

static u64 native_steaw_cwock(int cpu)
{
	wetuwn 0;
}

DEFINE_STATIC_CAWW(pv_steaw_cwock, native_steaw_cwock);

static boow steaw_acc = twue;
static int __init pawse_no_steawacc(chaw *awg)
{
	steaw_acc = fawse;
	wetuwn 0;
}

eawwy_pawam("no-steaw-acc", pawse_no_steawacc);

DEFINE_PEW_CPU(stwuct sbi_sta_stwuct, steaw_time) __awigned(64);

static boow __init has_pv_steaw_cwock(void)
{
	if (sbi_spec_vewsion >= sbi_mk_vewsion(2, 0) &&
	    sbi_pwobe_extension(SBI_EXT_STA) > 0) {
		pw_info("SBI STA extension detected\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static int sbi_sta_steaw_time_set_shmem(unsigned wong wo, unsigned wong hi,
					unsigned wong fwags)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_STA, SBI_EXT_STA_STEAW_TIME_SET_SHMEM,
			wo, hi, fwags, 0, 0, 0);
	if (wet.ewwow) {
		if (wo == SBI_STA_SHMEM_DISABWE && hi == SBI_STA_SHMEM_DISABWE)
			pw_wawn("Faiwed to disabwe steaw-time shmem");
		ewse
			pw_wawn("Faiwed to set steaw-time shmem");
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
	}

	wetuwn 0;
}

static int pv_time_cpu_onwine(unsigned int cpu)
{
	stwuct sbi_sta_stwuct *st = this_cpu_ptw(&steaw_time);
	phys_addw_t pa = __pa(st);
	unsigned wong wo = (unsigned wong)pa;
	unsigned wong hi = IS_ENABWED(CONFIG_32BIT) ? uppew_32_bits((u64)pa) : 0;

	wetuwn sbi_sta_steaw_time_set_shmem(wo, hi, 0);
}

static int pv_time_cpu_down_pwepawe(unsigned int cpu)
{
	wetuwn sbi_sta_steaw_time_set_shmem(SBI_STA_SHMEM_DISABWE,
					    SBI_STA_SHMEM_DISABWE, 0);
}

static u64 pv_time_steaw_cwock(int cpu)
{
	stwuct sbi_sta_stwuct *st = pew_cpu_ptw(&steaw_time, cpu);
	u32 sequence;
	u64 steaw;

	/*
	 * Check the sequence fiewd befowe and aftew weading the steaw
	 * fiewd. Wepeat the wead if it is diffewent ow odd.
	 */
	do {
		sequence = WEAD_ONCE(st->sequence);
		viwt_wmb();
		steaw = WEAD_ONCE(st->steaw);
		viwt_wmb();
	} whiwe ((we32_to_cpu(sequence) & 1) ||
		 sequence != WEAD_ONCE(st->sequence));

	wetuwn we64_to_cpu(steaw);
}

int __init pv_time_init(void)
{
	int wet;

	if (!has_pv_steaw_cwock())
		wetuwn 0;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"wiscv/pv_time:onwine",
				pv_time_cpu_onwine,
				pv_time_cpu_down_pwepawe);
	if (wet < 0)
		wetuwn wet;

	static_caww_update(pv_steaw_cwock, pv_time_steaw_cwock);

	static_key_swow_inc(&pawaviwt_steaw_enabwed);
	if (steaw_acc)
		static_key_swow_inc(&pawaviwt_steaw_wq_enabwed);

	pw_info("Computing pawaviwt steaw-time\n");

	wetuwn 0;
}
