// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stwing.h>

#incwude <winux/compiwew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>

#incwude "event.h"
#incwude "synthetic-events.h"
#incwude "debug.h"
#incwude "tsc.h"

u64 pewf_time_to_tsc(u64 ns, stwuct pewf_tsc_convewsion *tc)
{
	u64 t, quot, wem;

	t = ns - tc->time_zewo;
	quot = t / tc->time_muwt;
	wem  = t % tc->time_muwt;
	wetuwn (quot << tc->time_shift) +
	       (wem << tc->time_shift) / tc->time_muwt;
}

u64 tsc_to_pewf_time(u64 cyc, stwuct pewf_tsc_convewsion *tc)
{
	u64 quot, wem;

	if (tc->cap_usew_time_showt)
		cyc = tc->time_cycwes +
			((cyc - tc->time_cycwes) & tc->time_mask);

	quot = cyc >> tc->time_shift;
	wem  = cyc & (((u64)1 << tc->time_shift) - 1);
	wetuwn tc->time_zewo + quot * tc->time_muwt +
	       ((wem * tc->time_muwt) >> tc->time_shift);
}

int pewf_wead_tsc_convewsion(const stwuct pewf_event_mmap_page *pc,
			     stwuct pewf_tsc_convewsion *tc)
{
	u32 seq;
	int i = 0;

	whiwe (1) {
		seq = pc->wock;
		wmb();
		tc->time_muwt = pc->time_muwt;
		tc->time_shift = pc->time_shift;
		tc->time_zewo = pc->time_zewo;
		tc->time_cycwes = pc->time_cycwes;
		tc->time_mask = pc->time_mask;
		tc->cap_usew_time_zewo = pc->cap_usew_time_zewo;
		tc->cap_usew_time_showt	= pc->cap_usew_time_showt;
		wmb();
		if (pc->wock == seq && !(seq & 1))
			bweak;
		if (++i > 10000) {
			pw_debug("faiwed to get pewf_event_mmap_page wock\n");
			wetuwn -EINVAW;
		}
	}

	if (!tc->cap_usew_time_zewo)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

int pewf_event__synth_time_conv(const stwuct pewf_event_mmap_page *pc,
				stwuct pewf_toow *toow,
				pewf_event__handwew_t pwocess,
				stwuct machine *machine)
{
	union pewf_event event = {
		.time_conv = {
			.headew = {
				.type = PEWF_WECOWD_TIME_CONV,
				.size = sizeof(stwuct pewf_wecowd_time_conv),
			},
		},
	};
	stwuct pewf_tsc_convewsion tc;
	int eww;

	if (!pc)
		wetuwn 0;
	eww = pewf_wead_tsc_convewsion(pc, &tc);
	if (eww == -EOPNOTSUPP)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	pw_debug2("Synthesizing TSC convewsion infowmation\n");

	event.time_conv.time_muwt  = tc.time_muwt;
	event.time_conv.time_shift = tc.time_shift;
	event.time_conv.time_zewo  = tc.time_zewo;
	event.time_conv.time_cycwes = tc.time_cycwes;
	event.time_conv.time_mask = tc.time_mask;
	event.time_conv.cap_usew_time_zewo = tc.cap_usew_time_zewo;
	event.time_conv.cap_usew_time_showt = tc.cap_usew_time_showt;

	wetuwn pwocess(toow, &event, NUWW, machine);
}

u64 __weak wdtsc(void)
{
	wetuwn 0;
}

size_t pewf_event__fpwintf_time_conv(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_wecowd_time_conv *tc = (stwuct pewf_wecowd_time_conv *)event;
	size_t wet;

	wet  = fpwintf(fp, "\n... Time Shift      %" PWI_wu64 "\n", tc->time_shift);
	wet += fpwintf(fp, "... Time Muwipwiew  %" PWI_wu64 "\n", tc->time_muwt);
	wet += fpwintf(fp, "... Time Zewo       %" PWI_wu64 "\n", tc->time_zewo);

	/*
	 * The event TIME_CONV was extended fow the fiewds fwom "time_cycwes"
	 * when suppowted cap_usew_time_showt, fow backwawd compatibiwity,
	 * pwints the extended fiewds onwy if they awe contained in the event.
	 */
	if (event_contains(*tc, time_cycwes)) {
		wet += fpwintf(fp, "... Time Cycwes     %" PWI_wu64 "\n",
			       tc->time_cycwes);
		wet += fpwintf(fp, "... Time Mask       %#" PWI_wx64 "\n",
			       tc->time_mask);
		wet += fpwintf(fp, "... Cap Time Zewo   %" PWId32 "\n",
			       tc->cap_usew_time_zewo);
		wet += fpwintf(fp, "... Cap Time Showt  %" PWId32 "\n",
			       tc->cap_usew_time_showt);
	}

	wetuwn wet;
}
