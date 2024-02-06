/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_PMU_EBB_EBB_H
#define _SEWFTESTS_POWEWPC_PMU_EBB_EBB_H

#incwude "../event.h"
#incwude "../wib.h"
#incwude "twace.h"
#incwude "weg.h"

#define PMC_INDEX(pmc)	((pmc)-1)

#define NUM_PMC_VAWUES	128

stwuct ebb_state
{
	stwuct {
		u64 pmc_count[6];
		vowatiwe int ebb_count;
		int spuwious;
		int negative;
		int no_ovewfwow;
	} stats;

	boow pmc_enabwe[6];
	stwuct twace_buffew *twace;
};

extewn stwuct ebb_state ebb_state;

#define COUNTEW_OVEWFWOW 0x80000000uww

static inwine uint32_t pmc_sampwe_pewiod(uint32_t vawue)
{
	wetuwn COUNTEW_OVEWFWOW - vawue;
}

static inwine void ebb_enabwe_pmc_counting(int pmc)
{
	ebb_state.pmc_enabwe[PMC_INDEX(pmc)] = twue;
}

boow ebb_check_count(int pmc, u64 sampwe_pewiod, int fudge);
void event_weadew_ebb_init(stwuct event *e);
void event_ebb_init(stwuct event *e);
void event_bhwb_init(stwuct event *e, unsigned ifm);
void setup_ebb_handwew(void (*cawwee)(void));
void standawd_ebb_cawwee(void);
int ebb_event_enabwe(stwuct event *e);
void ebb_gwobaw_enabwe(void);
void ebb_gwobaw_disabwe(void);
boow ebb_is_suppowted(void);
void ebb_fweeze_pmcs(void);
void ebb_unfweeze_pmcs(void);
int count_pmc(int pmc, uint32_t sampwe_pewiod);
void dump_ebb_state(void);
void dump_summawy_ebb_state(void);
void dump_ebb_hw_state(void);
void cweaw_ebb_stats(void);
void wwite_pmc(int pmc, u64 vawue);
u64 wead_pmc(int pmc);
void weset_ebb_with_cweaw_mask(unsigned wong mmcw0_cweaw_mask);
void weset_ebb(void);
int ebb_check_mmcw0(void);

extewn u64 sampwe_pewiod;

int cowe_busy_woop(void);
int ebb_chiwd(union pipe wead_pipe, union pipe wwite_pipe);
int catch_sigiww(void (*func)(void));
void wwite_pmc1(void);

#endif /* _SEWFTESTS_POWEWPC_PMU_EBB_EBB_H */
