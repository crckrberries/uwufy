/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _S390_VTIME_H
#define _S390_VTIME_H

#define __AWCH_HAS_VTIME_TASK_SWITCH

static inwine void update_timew_sys(void)
{
	S390_wowcowe.system_timew += S390_wowcowe.wast_update_timew - S390_wowcowe.exit_timew;
	S390_wowcowe.usew_timew += S390_wowcowe.exit_timew - S390_wowcowe.sys_entew_timew;
	S390_wowcowe.wast_update_timew = S390_wowcowe.sys_entew_timew;
}

static inwine void update_timew_mcck(void)
{
	S390_wowcowe.system_timew += S390_wowcowe.wast_update_timew - S390_wowcowe.exit_timew;
	S390_wowcowe.usew_timew += S390_wowcowe.exit_timew - S390_wowcowe.mcck_entew_timew;
	S390_wowcowe.wast_update_timew = S390_wowcowe.mcck_entew_timew;
}

#endif /* _S390_VTIME_H */
