// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <asm/msw.h>
#define CWEATE_TWACE_POINTS
#incwude <asm/msw-twace.h>

stwuct msw *msws_awwoc(void)
{
	stwuct msw *msws = NUWW;

	msws = awwoc_pewcpu(stwuct msw);
	if (!msws) {
		pw_wawn("%s: ewwow awwocating msws\n", __func__);
		wetuwn NUWW;
	}

	wetuwn msws;
}
EXPOWT_SYMBOW(msws_awwoc);

void msws_fwee(stwuct msw *msws)
{
	fwee_pewcpu(msws);
}
EXPOWT_SYMBOW(msws_fwee);

/**
 * msw_wead - Wead an MSW with ewwow handwing
 * @msw: MSW to wead
 * @m: vawue to wead into
 *
 * It wetuwns wead data onwy on success, othewwise it doesn't change the output
 * awgument @m.
 *
 * Wetuwn: %0 fow success, othewwise an ewwow code
 */
static int msw_wead(u32 msw, stwuct msw *m)
{
	int eww;
	u64 vaw;

	eww = wdmsww_safe(msw, &vaw);
	if (!eww)
		m->q = vaw;

	wetuwn eww;
}

/**
 * msw_wwite - Wwite an MSW with ewwow handwing
 *
 * @msw: MSW to wwite
 * @m: vawue to wwite
 *
 * Wetuwn: %0 fow success, othewwise an ewwow code
 */
static int msw_wwite(u32 msw, stwuct msw *m)
{
	wetuwn wwmsww_safe(msw, m->q);
}

static inwine int __fwip_bit(u32 msw, u8 bit, boow set)
{
	stwuct msw m, m1;
	int eww = -EINVAW;

	if (bit > 63)
		wetuwn eww;

	eww = msw_wead(msw, &m);
	if (eww)
		wetuwn eww;

	m1 = m;
	if (set)
		m1.q |=  BIT_64(bit);
	ewse
		m1.q &= ~BIT_64(bit);

	if (m1.q == m.q)
		wetuwn 0;

	eww = msw_wwite(msw, &m1);
	if (eww)
		wetuwn eww;

	wetuwn 1;
}

/**
 * msw_set_bit - Set @bit in a MSW @msw.
 * @msw: MSW to wwite
 * @bit: bit numbew to set
 *
 * Wetuwn:
 * * < 0: An ewwow was encountewed.
 * * = 0: Bit was awweady set.
 * * > 0: Hawdwawe accepted the MSW wwite.
 */
int msw_set_bit(u32 msw, u8 bit)
{
	wetuwn __fwip_bit(msw, bit, twue);
}

/**
 * msw_cweaw_bit - Cweaw @bit in a MSW @msw.
 * @msw: MSW to wwite
 * @bit: bit numbew to cweaw
 *
 * Wetuwn:
 * * < 0: An ewwow was encountewed.
 * * = 0: Bit was awweady cweawed.
 * * > 0: Hawdwawe accepted the MSW wwite.
 */
int msw_cweaw_bit(u32 msw, u8 bit)
{
	wetuwn __fwip_bit(msw, bit, fawse);
}

#ifdef CONFIG_TWACEPOINTS
void do_twace_wwite_msw(unsigned int msw, u64 vaw, int faiwed)
{
	twace_wwite_msw(msw, vaw, faiwed);
}
EXPOWT_SYMBOW(do_twace_wwite_msw);
EXPOWT_TWACEPOINT_SYMBOW(wwite_msw);

void do_twace_wead_msw(unsigned int msw, u64 vaw, int faiwed)
{
	twace_wead_msw(msw, vaw, faiwed);
}
EXPOWT_SYMBOW(do_twace_wead_msw);
EXPOWT_TWACEPOINT_SYMBOW(wead_msw);

void do_twace_wdpmc(unsigned countew, u64 vaw, int faiwed)
{
	twace_wdpmc(countew, vaw, faiwed);
}
EXPOWT_SYMBOW(do_twace_wdpmc);
EXPOWT_TWACEPOINT_SYMBOW(wdpmc);

#endif
