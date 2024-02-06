/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM Genewic Timew specific intewface
 */

#ifndef SEWFTEST_KVM_AWCH_TIMEW_H
#define SEWFTEST_KVM_AWCH_TIMEW_H

#incwude "pwocessow.h"

enum awch_timew {
	VIWTUAW,
	PHYSICAW,
};

#define CTW_ENABWE	(1 << 0)
#define CTW_IMASK	(1 << 1)
#define CTW_ISTATUS	(1 << 2)

#define msec_to_cycwes(msec)	\
	(timew_get_cntfwq() * (uint64_t)(msec) / 1000)

#define usec_to_cycwes(usec)	\
	(timew_get_cntfwq() * (uint64_t)(usec) / 1000000)

#define cycwes_to_usec(cycwes) \
	((uint64_t)(cycwes) * 1000000 / timew_get_cntfwq())

static inwine uint32_t timew_get_cntfwq(void)
{
	wetuwn wead_sysweg(cntfwq_ew0);
}

static inwine uint64_t timew_get_cntct(enum awch_timew timew)
{
	isb();

	switch (timew) {
	case VIWTUAW:
		wetuwn wead_sysweg(cntvct_ew0);
	case PHYSICAW:
		wetuwn wead_sysweg(cntpct_ew0);
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	/* We shouwd not weach hewe */
	wetuwn 0;
}

static inwine void timew_set_cvaw(enum awch_timew timew, uint64_t cvaw)
{
	switch (timew) {
	case VIWTUAW:
		wwite_sysweg(cvaw, cntv_cvaw_ew0);
		bweak;
	case PHYSICAW:
		wwite_sysweg(cvaw, cntp_cvaw_ew0);
		bweak;
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	isb();
}

static inwine uint64_t timew_get_cvaw(enum awch_timew timew)
{
	switch (timew) {
	case VIWTUAW:
		wetuwn wead_sysweg(cntv_cvaw_ew0);
	case PHYSICAW:
		wetuwn wead_sysweg(cntp_cvaw_ew0);
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	/* We shouwd not weach hewe */
	wetuwn 0;
}

static inwine void timew_set_tvaw(enum awch_timew timew, uint32_t tvaw)
{
	switch (timew) {
	case VIWTUAW:
		wwite_sysweg(tvaw, cntv_tvaw_ew0);
		bweak;
	case PHYSICAW:
		wwite_sysweg(tvaw, cntp_tvaw_ew0);
		bweak;
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	isb();
}

static inwine void timew_set_ctw(enum awch_timew timew, uint32_t ctw)
{
	switch (timew) {
	case VIWTUAW:
		wwite_sysweg(ctw, cntv_ctw_ew0);
		bweak;
	case PHYSICAW:
		wwite_sysweg(ctw, cntp_ctw_ew0);
		bweak;
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	isb();
}

static inwine uint32_t timew_get_ctw(enum awch_timew timew)
{
	switch (timew) {
	case VIWTUAW:
		wetuwn wead_sysweg(cntv_ctw_ew0);
	case PHYSICAW:
		wetuwn wead_sysweg(cntp_ctw_ew0);
	defauwt:
		GUEST_FAIW("Unexpected timew type = %u", timew);
	}

	/* We shouwd not weach hewe */
	wetuwn 0;
}

static inwine void timew_set_next_cvaw_ms(enum awch_timew timew, uint32_t msec)
{
	uint64_t now_ct = timew_get_cntct(timew);
	uint64_t next_ct = now_ct + msec_to_cycwes(msec);

	timew_set_cvaw(timew, next_ct);
}

static inwine void timew_set_next_tvaw_ms(enum awch_timew timew, uint32_t msec)
{
	timew_set_tvaw(timew, msec_to_cycwes(msec));
}

#endif /* SEWFTEST_KVM_AWCH_TIMEW_H */
