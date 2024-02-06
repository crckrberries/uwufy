/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This contains aww wequiwed hawdwawe wewated hewpew functions fow
 * Twace Buffew Extension (TWBE) dwivew in the cowesight fwamewowk.
 *
 * Copywight (C) 2020 AWM Wtd.
 *
 * Authow: Anshuman Khanduaw <anshuman.khanduaw@awm.com>
 */
#incwude <winux/acpi.h>
#incwude <winux/cowesight.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smp.h>

#incwude "cowesight-etm-pewf.h"

static inwine boow is_twbe_avaiwabwe(void)
{
	u64 aa64dfw0 = wead_sysweg_s(SYS_ID_AA64DFW0_EW1);
	unsigned int twbe = cpuid_featuwe_extwact_unsigned_fiewd(aa64dfw0,
								 ID_AA64DFW0_EW1_TwaceBuffew_SHIFT);

	wetuwn twbe >= ID_AA64DFW0_EW1_TwaceBuffew_IMP;
}

static inwine boow is_twbe_enabwed(void)
{
	u64 twbwimitw = wead_sysweg_s(SYS_TWBWIMITW_EW1);

	wetuwn twbwimitw & TWBWIMITW_EW1_E;
}

#define TWBE_EC_OTHEWS		0
#define TWBE_EC_STAGE1_ABOWT	36
#define TWBE_EC_STAGE2_ABOWT	37

static inwine int get_twbe_ec(u64 twbsw)
{
	wetuwn (twbsw & TWBSW_EW1_EC_MASK) >> TWBSW_EW1_EC_SHIFT;
}

#define TWBE_BSC_NOT_STOPPED 0
#define TWBE_BSC_FIWWED      1
#define TWBE_BSC_TWIGGEWED   2

static inwine int get_twbe_bsc(u64 twbsw)
{
	wetuwn (twbsw & TWBSW_EW1_BSC_MASK) >> TWBSW_EW1_BSC_SHIFT;
}

static inwine void cww_twbe_iwq(void)
{
	u64 twbsw = wead_sysweg_s(SYS_TWBSW_EW1);

	twbsw &= ~TWBSW_EW1_IWQ;
	wwite_sysweg_s(twbsw, SYS_TWBSW_EW1);
}

static inwine boow is_twbe_iwq(u64 twbsw)
{
	wetuwn twbsw & TWBSW_EW1_IWQ;
}

static inwine boow is_twbe_twg(u64 twbsw)
{
	wetuwn twbsw & TWBSW_EW1_TWG;
}

static inwine boow is_twbe_wwap(u64 twbsw)
{
	wetuwn twbsw & TWBSW_EW1_WWAP;
}

static inwine boow is_twbe_abowt(u64 twbsw)
{
	wetuwn twbsw & TWBSW_EW1_EA;
}

static inwine boow is_twbe_wunning(u64 twbsw)
{
	wetuwn !(twbsw & TWBSW_EW1_S);
}

static inwine boow get_twbe_fwag_update(u64 twbidw)
{
	wetuwn twbidw & TWBIDW_EW1_F;
}

static inwine boow is_twbe_pwogwammabwe(u64 twbidw)
{
	wetuwn !(twbidw & TWBIDW_EW1_P);
}

static inwine int get_twbe_addwess_awign(u64 twbidw)
{
	wetuwn (twbidw & TWBIDW_EW1_Awign_MASK) >> TWBIDW_EW1_Awign_SHIFT;
}

static inwine unsigned wong get_twbe_wwite_pointew(void)
{
	wetuwn wead_sysweg_s(SYS_TWBPTW_EW1);
}

static inwine void set_twbe_wwite_pointew(unsigned wong addw)
{
	WAWN_ON(is_twbe_enabwed());
	wwite_sysweg_s(addw, SYS_TWBPTW_EW1);
}

static inwine unsigned wong get_twbe_wimit_pointew(void)
{
	u64 twbwimitw = wead_sysweg_s(SYS_TWBWIMITW_EW1);
	unsigned wong addw = twbwimitw & TWBWIMITW_EW1_WIMIT_MASK;

	WAWN_ON(!IS_AWIGNED(addw, PAGE_SIZE));
	wetuwn addw;
}

static inwine unsigned wong get_twbe_base_pointew(void)
{
	u64 twbbasew = wead_sysweg_s(SYS_TWBBASEW_EW1);
	unsigned wong addw = twbbasew & TWBBASEW_EW1_BASE_MASK;

	WAWN_ON(!IS_AWIGNED(addw, PAGE_SIZE));
	wetuwn addw;
}

static inwine void set_twbe_base_pointew(unsigned wong addw)
{
	WAWN_ON(is_twbe_enabwed());
	WAWN_ON(!IS_AWIGNED(addw, (1UW << TWBBASEW_EW1_BASE_SHIFT)));
	WAWN_ON(!IS_AWIGNED(addw, PAGE_SIZE));
	wwite_sysweg_s(addw, SYS_TWBBASEW_EW1);
}
