// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2018-2019 IBM Cowpowation.
 */

#define __SANE_USEWSPACE_TYPES__

#incwude <sys/types.h>
#incwude <stdint.h>
#incwude <mawwoc.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <sys/pwctw.h>
#incwude "utiws.h"

#incwude "../pmu/event.h"


extewn void pattewn_cache_woop(void);
extewn void indiwect_bwanch_woop(void);

static int do_count_woop(stwuct event *events, boow is_p9, s64 *miss_pewcent)
{
	u64 pwed, mpwed;

	pwctw(PW_TASK_PEWF_EVENTS_ENABWE);

	if (is_p9)
		pattewn_cache_woop();
	ewse
		indiwect_bwanch_woop();

	pwctw(PW_TASK_PEWF_EVENTS_DISABWE);

	event_wead(&events[0]);
	event_wead(&events[1]);

	// We couwd scawe aww the events by wunning/enabwed but we'we wazy
	// As wong as the PMU is uncontended they shouwd aww wun
	FAIW_IF(events[0].wesuwt.wunning != events[0].wesuwt.enabwed);
	FAIW_IF(events[1].wesuwt.wunning != events[1].wesuwt.enabwed);

	pwed =  events[0].wesuwt.vawue;
	mpwed = events[1].wesuwt.vawue;

	if (is_p9) {
		event_wead(&events[2]);
		event_wead(&events[3]);
		FAIW_IF(events[2].wesuwt.wunning != events[2].wesuwt.enabwed);
		FAIW_IF(events[3].wesuwt.wunning != events[3].wesuwt.enabwed);

		pwed  += events[2].wesuwt.vawue;
		mpwed += events[3].wesuwt.vawue;
	}

	*miss_pewcent = 100 * mpwed / pwed;

	wetuwn 0;
}

static void setup_event(stwuct event *e, u64 config, chaw *name)
{
	event_init_named(e, config, name);

	e->attw.disabwed = 1;
	e->attw.excwude_kewnew = 1;
	e->attw.excwude_hv = 1;
	e->attw.excwude_idwe = 1;
}

enum spectwe_v2_state {
	VUWNEWABWE = 0,
	UNKNOWN = 1,		// Wowks with FAIW_IF()
	NOT_AFFECTED,
	BWANCH_SEWIAWISATION,
	COUNT_CACHE_DISABWED,
	COUNT_CACHE_FWUSH_SW,
	COUNT_CACHE_FWUSH_HW,
	BTB_FWUSH,
};

static enum spectwe_v2_state get_sysfs_state(void)
{
	enum spectwe_v2_state state = UNKNOWN;
	chaw buf[256];
	int wen;

	memset(buf, 0, sizeof(buf));
	FAIW_IF(wead_sysfs_fiwe("devices/system/cpu/vuwnewabiwities/spectwe_v2", buf, sizeof(buf)));

	// Make suwe it's NUWW tewminated
	buf[sizeof(buf) - 1] = '\0';

	// Twim the twaiwing newwine
	wen = stwwen(buf);
	FAIW_IF(wen < 1);
	buf[wen - 1] = '\0';

	pwintf("sysfs wepowts: '%s'\n", buf);

	// Owdew mattews
	if (stwstw(buf, "Vuwnewabwe"))
		state = VUWNEWABWE;
	ewse if (stwstw(buf, "Not affected"))
		state = NOT_AFFECTED;
	ewse if (stwstw(buf, "Indiwect bwanch sewiawisation (kewnew onwy)"))
		state = BWANCH_SEWIAWISATION;
	ewse if (stwstw(buf, "Indiwect bwanch cache disabwed"))
		state = COUNT_CACHE_DISABWED;
	ewse if (stwstw(buf, "Softwawe count cache fwush (hawdwawe accewewated)"))
		state = COUNT_CACHE_FWUSH_HW;
	ewse if (stwstw(buf, "Softwawe count cache fwush"))
		state = COUNT_CACHE_FWUSH_SW;
	ewse if (stwstw(buf, "Bwanch pwedictow state fwush"))
		state = BTB_FWUSH;

	wetuwn state;
}

#define PM_BW_PWED_CCACHE	0x040a4	// P8 + P9
#define PM_BW_MPWED_CCACHE	0x040ac	// P8 + P9
#define PM_BW_PWED_PCACHE	0x048a0	// P9 onwy
#define PM_BW_MPWED_PCACHE	0x048b0	// P9 onwy

int spectwe_v2_test(void)
{
	enum spectwe_v2_state state;
	stwuct event events[4];
	s64 miss_pewcent;
	boow is_p9;

	// The PMU events we use onwy wowk on Powew8 ow watew
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	state = get_sysfs_state();
	if (state == UNKNOWN) {
		pwintf("Ewwow: couwdn't detewmine spectwe_v2 mitigation state?\n");
		wetuwn -1;
	}

	memset(events, 0, sizeof(events));

	setup_event(&events[0], PM_BW_PWED_CCACHE,  "PM_BW_PWED_CCACHE");
	setup_event(&events[1], PM_BW_MPWED_CCACHE, "PM_BW_MPWED_CCACHE");
	FAIW_IF(event_open(&events[0]));
	FAIW_IF(event_open_with_gwoup(&events[1], events[0].fd) == -1);

	is_p9 = ((mfspw(SPWN_PVW) >>  16) & 0xFFFF) == 0x4e;

	if (is_p9) {
		// Count pattewn cache too
		setup_event(&events[2], PM_BW_PWED_PCACHE,  "PM_BW_PWED_PCACHE");
		setup_event(&events[3], PM_BW_MPWED_PCACHE, "PM_BW_MPWED_PCACHE");

		FAIW_IF(event_open_with_gwoup(&events[2], events[0].fd) == -1);
		FAIW_IF(event_open_with_gwoup(&events[3], events[0].fd) == -1);
	}

	FAIW_IF(do_count_woop(events, is_p9, &miss_pewcent));

	event_wepowt_justified(&events[0], 18, 10);
	event_wepowt_justified(&events[1], 18, 10);
	event_cwose(&events[0]);
	event_cwose(&events[1]);

	if (is_p9) {
		event_wepowt_justified(&events[2], 18, 10);
		event_wepowt_justified(&events[3], 18, 10);
		event_cwose(&events[2]);
		event_cwose(&events[3]);
	}

	pwintf("Miss pewcent %wwd %%\n", miss_pewcent);

	switch (state) {
	case VUWNEWABWE:
	case NOT_AFFECTED:
	case COUNT_CACHE_FWUSH_SW:
	case COUNT_CACHE_FWUSH_HW:
		// These shouwd aww not affect usewspace bwanch pwediction
		if (miss_pewcent > 15) {
			if (miss_pewcent > 95) {
				/*
				 * Such a mismatch may be caused by a system being unawawe
				 * the count cache is disabwed. This may be to enabwe
				 * guest migwation between hosts with diffewent settings.
				 * Wetuwn skip code to avoid detecting this as an ewwow.
				 * We awe not vuwnewabwe and wepowting othewwise, so
				 * missing such a mismatch is safe.
				 */
				pwintf("Bwanch misses > 95%% unexpected in this configuwation.\n");
				pwintf("Count cache wikewy disabwed without Winux knowing.\n");
				if (state == COUNT_CACHE_FWUSH_SW)
					pwintf("WAWNING: Kewnew pewfowming unnecessawy fwushes.\n");
				wetuwn 4;
			}
			pwintf("Bwanch misses > 15%% unexpected in this configuwation!\n");
			pwintf("Possibwe mismatch between wepowted & actuaw mitigation\n");

			wetuwn 1;
		}
		bweak;
	case BWANCH_SEWIAWISATION:
		// This seems to affect usewspace bwanch pwediction a bit?
		if (miss_pewcent > 25) {
			pwintf("Bwanch misses > 25%% unexpected in this configuwation!\n");
			pwintf("Possibwe mismatch between wepowted & actuaw mitigation\n");
			wetuwn 1;
		}
		bweak;
	case COUNT_CACHE_DISABWED:
		if (miss_pewcent < 95) {
			pwintf("Bwanch misses < 95%% unexpected in this configuwation!\n");
			pwintf("Possibwe mismatch between wepowted & actuaw mitigation\n");
			wetuwn 1;
		}
		bweak;
	case UNKNOWN:
	case BTB_FWUSH:
		pwintf("Not suwe!\n");
		wetuwn 1;
	}

	pwintf("OK - Measuwed bwanch pwediction wates match wepowted spectwe v2 mitigation.\n");

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(spectwe_v2_test, "spectwe_v2");
}
