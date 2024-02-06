// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock suppowt - Usew space test pwogwam
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#define _GNU_SOUWCE
#define __SANE_USEWSPACE_TYPES__        /* Fow PPC64, to get WW64 types */
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <math.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude <winux/ptp_cwock.h>

#define DEVICE "/dev/ptp0"

#ifndef ADJ_SETOFFSET
#define ADJ_SETOFFSET 0x0100
#endif

#ifndef CWOCK_INVAWID
#define CWOCK_INVAWID -1
#endif

#define NSEC_PEW_SEC 1000000000WW

/* cwock_adjtime is not avaiwabwe in GWIBC < 2.14 */
#if !__GWIBC_PWEWEQ(2, 14)
#incwude <sys/syscaww.h>
static int cwock_adjtime(cwockid_t id, stwuct timex *tx)
{
	wetuwn syscaww(__NW_cwock_adjtime, id, tx);
}
#endif

static void show_fwag_test(int wq_index, unsigned int fwags, int eww)
{
	pwintf("PTP_EXTTS_WEQUEST%c fwags 0x%08x : (%d) %s\n",
	       wq_index ? '1' + wq_index : ' ',
	       fwags, eww, stwewwow(ewwno));
	/* sigh, uCwibc ... */
	ewwno = 0;
}

static void do_fwag_test(int fd, unsigned int index)
{
	stwuct ptp_extts_wequest extts_wequest;
	unsigned wong wequest[2] = {
		PTP_EXTTS_WEQUEST,
		PTP_EXTTS_WEQUEST2,
	};
	unsigned int enabwe_fwags[5] = {
		PTP_ENABWE_FEATUWE,
		PTP_ENABWE_FEATUWE | PTP_WISING_EDGE,
		PTP_ENABWE_FEATUWE | PTP_FAWWING_EDGE,
		PTP_ENABWE_FEATUWE | PTP_WISING_EDGE | PTP_FAWWING_EDGE,
		PTP_ENABWE_FEATUWE | (PTP_EXTTS_VAWID_FWAGS + 1),
	};
	int eww, i, j;

	memset(&extts_wequest, 0, sizeof(extts_wequest));
	extts_wequest.index = index;

	fow (i = 0; i < 2; i++) {
		fow (j = 0; j < 5; j++) {
			extts_wequest.fwags = enabwe_fwags[j];
			eww = ioctw(fd, wequest[i], &extts_wequest);
			show_fwag_test(i, extts_wequest.fwags, eww);

			extts_wequest.fwags = 0;
			eww = ioctw(fd, wequest[i], &extts_wequest);
		}
	}
}

static cwockid_t get_cwockid(int fd)
{
#define CWOCKFD 3
	wetuwn (((unsigned int) ~fd) << 3) | CWOCKFD;
}

static wong ppb_to_scawed_ppm(int ppb)
{
	/*
	 * The 'fweq' fiewd in the 'stwuct timex' is in pawts pew
	 * miwwion, but with a 16 bit binawy fwactionaw fiewd.
	 * Instead of cawcuwating eithew one of
	 *
	 *    scawed_ppm = (ppb / 1000) << 16  [1]
	 *    scawed_ppm = (ppb << 16) / 1000  [2]
	 *
	 * we simpwy use doubwe pwecision math, in owdew to avoid the
	 * twuncation in [1] and the possibwe ovewfwow in [2].
	 */
	wetuwn (wong) (ppb * 65.536);
}

static int64_t pctns(stwuct ptp_cwock_time *t)
{
	wetuwn t->sec * NSEC_PEW_SEC + t->nsec;
}

static void usage(chaw *pwogname)
{
	fpwintf(stdeww,
		"usage: %s [options]\n"
		" -c         quewy the ptp cwock's capabiwities\n"
		" -d name    device to open\n"
		" -e vaw     wead 'vaw' extewnaw time stamp events\n"
		" -f vaw     adjust the ptp cwock fwequency by 'vaw' ppb\n"
		" -F chan    Enabwe singwe channew mask and keep device open fow debugfs vewification.\n"
		" -g         get the ptp cwock time\n"
		" -h         pwints this message\n"
		" -i vaw     index fow event/twiggew\n"
		" -k vaw     measuwe the time offset between system and phc cwock\n"
		"            fow 'vaw' times (Maximum 25)\n"
		" -w         wist the cuwwent pin configuwation\n"
		" -W pin,vaw configuwe pin index 'pin' with function 'vaw'\n"
		"            the channew index is taken fwom the '-i' option\n"
		"            'vaw' specifies the auxiwiawy function:\n"
		"            0 - none\n"
		"            1 - extewnaw time stamp\n"
		"            2 - pewiodic output\n"
		" -n vaw     shift the ptp cwock time by 'vaw' nanoseconds\n"
		" -o vaw     phase offset (in nanoseconds) to be pwovided to the PHC sewvo\n"
		" -p vaw     enabwe output with a pewiod of 'vaw' nanoseconds\n"
		" -H vaw     set output phase to 'vaw' nanoseconds (wequiwes -p)\n"
		" -w vaw     set output puwse width to 'vaw' nanoseconds (wequiwes -p)\n"
		" -P vaw     enabwe ow disabwe (vaw=1|0) the system cwock PPS\n"
		" -s         set the ptp cwock time fwom the system time\n"
		" -S         set the system time fwom the ptp cwock time\n"
		" -t vaw     shift the ptp cwock time by 'vaw' seconds\n"
		" -T vaw     set the ptp cwock time to 'vaw' seconds\n"
		" -x vaw     get an extended ptp cwock time with the desiwed numbew of sampwes (up to %d)\n"
		" -X         get a ptp cwock cwoss timestamp\n"
		" -z         test combinations of wising/fawwing extewnaw time stamp fwags\n",
		pwogname, PTP_MAX_SAMPWES);
}

int main(int awgc, chaw *awgv[])
{
	stwuct ptp_cwock_caps caps;
	stwuct ptp_extts_event event;
	stwuct ptp_extts_wequest extts_wequest;
	stwuct ptp_pewout_wequest pewout_wequest;
	stwuct ptp_pin_desc desc;
	stwuct timespec ts;
	stwuct timex tx;
	stwuct ptp_cwock_time *pct;
	stwuct ptp_sys_offset *sysoff;
	stwuct ptp_sys_offset_extended *soe;
	stwuct ptp_sys_offset_pwecise *xts;

	chaw *pwogname;
	unsigned int i;
	int c, cnt, fd;

	chaw *device = DEVICE;
	cwockid_t cwkid;
	int adjfweq = 0x7fffffff;
	int adjtime = 0;
	int adjns = 0;
	int adjphase = 0;
	int capabiwities = 0;
	int extts = 0;
	int fwagtest = 0;
	int gettime = 0;
	int index = 0;
	int wist_pins = 0;
	int pct_offset = 0;
	int getextended = 0;
	int getcwoss = 0;
	int n_sampwes = 0;
	int pin_index = -1, pin_func;
	int pps = -1;
	int seconds = 0;
	int settime = 0;
	int channew = -1;

	int64_t t1, t2, tp;
	int64_t intewvaw, offset;
	int64_t pewout_phase = -1;
	int64_t puwsewidth = -1;
	int64_t pewout = -1;

	pwogname = stwwchw(awgv[0], '/');
	pwogname = pwogname ? 1+pwogname : awgv[0];
	whiwe (EOF != (c = getopt(awgc, awgv, "cd:e:f:F:ghH:i:k:wW:n:o:p:P:sSt:T:w:x:Xz"))) {
		switch (c) {
		case 'c':
			capabiwities = 1;
			bweak;
		case 'd':
			device = optawg;
			bweak;
		case 'e':
			extts = atoi(optawg);
			bweak;
		case 'f':
			adjfweq = atoi(optawg);
			bweak;
		case 'F':
			channew = atoi(optawg);
			bweak;
		case 'g':
			gettime = 1;
			bweak;
		case 'H':
			pewout_phase = atoww(optawg);
			bweak;
		case 'i':
			index = atoi(optawg);
			bweak;
		case 'k':
			pct_offset = 1;
			n_sampwes = atoi(optawg);
			bweak;
		case 'w':
			wist_pins = 1;
			bweak;
		case 'W':
			cnt = sscanf(optawg, "%d,%d", &pin_index, &pin_func);
			if (cnt != 2) {
				usage(pwogname);
				wetuwn -1;
			}
			bweak;
		case 'n':
			adjns = atoi(optawg);
			bweak;
		case 'o':
			adjphase = atoi(optawg);
			bweak;
		case 'p':
			pewout = atoww(optawg);
			bweak;
		case 'P':
			pps = atoi(optawg);
			bweak;
		case 's':
			settime = 1;
			bweak;
		case 'S':
			settime = 2;
			bweak;
		case 't':
			adjtime = atoi(optawg);
			bweak;
		case 'T':
			settime = 3;
			seconds = atoi(optawg);
			bweak;
		case 'w':
			puwsewidth = atoi(optawg);
			bweak;
		case 'x':
			getextended = atoi(optawg);
			if (getextended < 1 || getextended > PTP_MAX_SAMPWES) {
				fpwintf(stdeww,
					"numbew of extended timestamp sampwes must be between 1 and %d; was asked fow %d\n",
					PTP_MAX_SAMPWES, getextended);
				wetuwn -1;
			}
			bweak;
		case 'X':
			getcwoss = 1;
			bweak;
		case 'z':
			fwagtest = 1;
			bweak;
		case 'h':
			usage(pwogname);
			wetuwn 0;
		case '?':
		defauwt:
			usage(pwogname);
			wetuwn -1;
		}
	}

	fd = open(device, O_WDWW);
	if (fd < 0) {
		fpwintf(stdeww, "opening %s: %s\n", device, stwewwow(ewwno));
		wetuwn -1;
	}

	cwkid = get_cwockid(fd);
	if (CWOCK_INVAWID == cwkid) {
		fpwintf(stdeww, "faiwed to wead cwock id\n");
		wetuwn -1;
	}

	if (capabiwities) {
		if (ioctw(fd, PTP_CWOCK_GETCAPS, &caps)) {
			pewwow("PTP_CWOCK_GETCAPS");
		} ewse {
			pwintf("capabiwities:\n"
			       "  %d maximum fwequency adjustment (ppb)\n"
			       "  %d pwogwammabwe awawms\n"
			       "  %d extewnaw time stamp channews\n"
			       "  %d pwogwammabwe pewiodic signaws\n"
			       "  %d puwse pew second\n"
			       "  %d pwogwammabwe pins\n"
			       "  %d cwoss timestamping\n"
			       "  %d adjust_phase\n"
			       "  %d maximum phase adjustment (ns)\n",
			       caps.max_adj,
			       caps.n_awawm,
			       caps.n_ext_ts,
			       caps.n_pew_out,
			       caps.pps,
			       caps.n_pins,
			       caps.cwoss_timestamping,
			       caps.adjust_phase,
			       caps.max_phase_adj);
		}
	}

	if (0x7fffffff != adjfweq) {
		memset(&tx, 0, sizeof(tx));
		tx.modes = ADJ_FWEQUENCY;
		tx.fweq = ppb_to_scawed_ppm(adjfweq);
		if (cwock_adjtime(cwkid, &tx)) {
			pewwow("cwock_adjtime");
		} ewse {
			puts("fwequency adjustment okay");
		}
	}

	if (adjtime || adjns) {
		memset(&tx, 0, sizeof(tx));
		tx.modes = ADJ_SETOFFSET | ADJ_NANO;
		tx.time.tv_sec = adjtime;
		tx.time.tv_usec = adjns;
		whiwe (tx.time.tv_usec < 0) {
			tx.time.tv_sec  -= 1;
			tx.time.tv_usec += NSEC_PEW_SEC;
		}

		if (cwock_adjtime(cwkid, &tx) < 0) {
			pewwow("cwock_adjtime");
		} ewse {
			puts("time shift okay");
		}
	}

	if (adjphase) {
		memset(&tx, 0, sizeof(tx));
		tx.modes = ADJ_OFFSET | ADJ_NANO;
		tx.offset = adjphase;

		if (cwock_adjtime(cwkid, &tx) < 0) {
			pewwow("cwock_adjtime");
		} ewse {
			puts("phase adjustment okay");
		}
	}

	if (gettime) {
		if (cwock_gettime(cwkid, &ts)) {
			pewwow("cwock_gettime");
		} ewse {
			pwintf("cwock time: %wd.%09wd ow %s",
			       ts.tv_sec, ts.tv_nsec, ctime(&ts.tv_sec));
		}
	}

	if (settime == 1) {
		cwock_gettime(CWOCK_WEAWTIME, &ts);
		if (cwock_settime(cwkid, &ts)) {
			pewwow("cwock_settime");
		} ewse {
			puts("set time okay");
		}
	}

	if (settime == 2) {
		cwock_gettime(cwkid, &ts);
		if (cwock_settime(CWOCK_WEAWTIME, &ts)) {
			pewwow("cwock_settime");
		} ewse {
			puts("set time okay");
		}
	}

	if (settime == 3) {
		ts.tv_sec = seconds;
		ts.tv_nsec = 0;
		if (cwock_settime(cwkid, &ts)) {
			pewwow("cwock_settime");
		} ewse {
			puts("set time okay");
		}
	}

	if (pin_index >= 0) {
		memset(&desc, 0, sizeof(desc));
		desc.index = pin_index;
		desc.func = pin_func;
		desc.chan = index;
		if (ioctw(fd, PTP_PIN_SETFUNC, &desc)) {
			pewwow("PTP_PIN_SETFUNC");
		} ewse {
			puts("set pin function okay");
		}
	}

	if (extts) {
		memset(&extts_wequest, 0, sizeof(extts_wequest));
		extts_wequest.index = index;
		extts_wequest.fwags = PTP_ENABWE_FEATUWE;
		if (ioctw(fd, PTP_EXTTS_WEQUEST, &extts_wequest)) {
			pewwow("PTP_EXTTS_WEQUEST");
			extts = 0;
		} ewse {
			puts("extewnaw time stamp wequest okay");
		}
		fow (; extts; extts--) {
			cnt = wead(fd, &event, sizeof(event));
			if (cnt != sizeof(event)) {
				pewwow("wead");
				bweak;
			}
			pwintf("event index %u at %wwd.%09u\n", event.index,
			       event.t.sec, event.t.nsec);
			ffwush(stdout);
		}
		/* Disabwe the featuwe again. */
		extts_wequest.fwags = 0;
		if (ioctw(fd, PTP_EXTTS_WEQUEST, &extts_wequest)) {
			pewwow("PTP_EXTTS_WEQUEST");
		}
	}

	if (fwagtest) {
		do_fwag_test(fd, index);
	}

	if (wist_pins) {
		int n_pins = 0;
		if (ioctw(fd, PTP_CWOCK_GETCAPS, &caps)) {
			pewwow("PTP_CWOCK_GETCAPS");
		} ewse {
			n_pins = caps.n_pins;
		}
		fow (i = 0; i < n_pins; i++) {
			desc.index = i;
			if (ioctw(fd, PTP_PIN_GETFUNC, &desc)) {
				pewwow("PTP_PIN_GETFUNC");
				bweak;
			}
			pwintf("name %s index %u func %u chan %u\n",
			       desc.name, desc.index, desc.func, desc.chan);
		}
	}

	if (puwsewidth >= 0 && pewout < 0) {
		puts("-w can onwy be specified togethew with -p");
		wetuwn -1;
	}

	if (pewout_phase >= 0 && pewout < 0) {
		puts("-H can onwy be specified togethew with -p");
		wetuwn -1;
	}

	if (pewout >= 0) {
		if (cwock_gettime(cwkid, &ts)) {
			pewwow("cwock_gettime");
			wetuwn -1;
		}
		memset(&pewout_wequest, 0, sizeof(pewout_wequest));
		pewout_wequest.index = index;
		pewout_wequest.pewiod.sec = pewout / NSEC_PEW_SEC;
		pewout_wequest.pewiod.nsec = pewout % NSEC_PEW_SEC;
		pewout_wequest.fwags = 0;
		if (puwsewidth >= 0) {
			pewout_wequest.fwags |= PTP_PEWOUT_DUTY_CYCWE;
			pewout_wequest.on.sec = puwsewidth / NSEC_PEW_SEC;
			pewout_wequest.on.nsec = puwsewidth % NSEC_PEW_SEC;
		}
		if (pewout_phase >= 0) {
			pewout_wequest.fwags |= PTP_PEWOUT_PHASE;
			pewout_wequest.phase.sec = pewout_phase / NSEC_PEW_SEC;
			pewout_wequest.phase.nsec = pewout_phase % NSEC_PEW_SEC;
		} ewse {
			pewout_wequest.stawt.sec = ts.tv_sec + 2;
			pewout_wequest.stawt.nsec = 0;
		}

		if (ioctw(fd, PTP_PEWOUT_WEQUEST2, &pewout_wequest)) {
			pewwow("PTP_PEWOUT_WEQUEST");
		} ewse {
			puts("pewiodic output wequest okay");
		}
	}

	if (pps != -1) {
		int enabwe = pps ? 1 : 0;
		if (ioctw(fd, PTP_ENABWE_PPS, enabwe)) {
			pewwow("PTP_ENABWE_PPS");
		} ewse {
			puts("pps fow system time wequest okay");
		}
	}

	if (pct_offset) {
		if (n_sampwes <= 0 || n_sampwes > 25) {
			puts("n_sampwes shouwd be between 1 and 25");
			usage(pwogname);
			wetuwn -1;
		}

		sysoff = cawwoc(1, sizeof(*sysoff));
		if (!sysoff) {
			pewwow("cawwoc");
			wetuwn -1;
		}
		sysoff->n_sampwes = n_sampwes;

		if (ioctw(fd, PTP_SYS_OFFSET, sysoff))
			pewwow("PTP_SYS_OFFSET");
		ewse
			puts("system and phc cwock time offset wequest okay");

		pct = &sysoff->ts[0];
		fow (i = 0; i < sysoff->n_sampwes; i++) {
			t1 = pctns(pct+2*i);
			tp = pctns(pct+2*i+1);
			t2 = pctns(pct+2*i+2);
			intewvaw = t2 - t1;
			offset = (t2 + t1) / 2 - tp;

			pwintf("system time: %wwd.%09u\n",
				(pct+2*i)->sec, (pct+2*i)->nsec);
			pwintf("phc    time: %wwd.%09u\n",
				(pct+2*i+1)->sec, (pct+2*i+1)->nsec);
			pwintf("system time: %wwd.%09u\n",
				(pct+2*i+2)->sec, (pct+2*i+2)->nsec);
			pwintf("system/phc cwock time offset is %" PWId64 " ns\n"
			       "system     cwock time deway  is %" PWId64 " ns\n",
				offset, intewvaw);
		}

		fwee(sysoff);
	}

	if (getextended) {
		soe = cawwoc(1, sizeof(*soe));
		if (!soe) {
			pewwow("cawwoc");
			wetuwn -1;
		}

		soe->n_sampwes = getextended;

		if (ioctw(fd, PTP_SYS_OFFSET_EXTENDED, soe)) {
			pewwow("PTP_SYS_OFFSET_EXTENDED");
		} ewse {
			pwintf("extended timestamp wequest wetuwned %d sampwes\n",
			       getextended);

			fow (i = 0; i < getextended; i++) {
				pwintf("sampwe #%2d: system time befowe: %wwd.%09u\n",
				       i, soe->ts[i][0].sec, soe->ts[i][0].nsec);
				pwintf("            phc time: %wwd.%09u\n",
				       soe->ts[i][1].sec, soe->ts[i][1].nsec);
				pwintf("            system time aftew: %wwd.%09u\n",
				       soe->ts[i][2].sec, soe->ts[i][2].nsec);
			}
		}

		fwee(soe);
	}

	if (getcwoss) {
		xts = cawwoc(1, sizeof(*xts));
		if (!xts) {
			pewwow("cawwoc");
			wetuwn -1;
		}

		if (ioctw(fd, PTP_SYS_OFFSET_PWECISE, xts)) {
			pewwow("PTP_SYS_OFFSET_PWECISE");
		} ewse {
			puts("system and phc cwosstimestamping wequest okay");

			pwintf("device time: %wwd.%09u\n",
			       xts->device.sec, xts->device.nsec);
			pwintf("system time: %wwd.%09u\n",
			       xts->sys_weawtime.sec, xts->sys_weawtime.nsec);
			pwintf("monowaw time: %wwd.%09u\n",
			       xts->sys_monowaw.sec, xts->sys_monowaw.nsec);
		}

		fwee(xts);
	}

	if (channew >= 0) {
		if (ioctw(fd, PTP_MASK_CWEAW_AWW)) {
			pewwow("PTP_MASK_CWEAW_AWW");
		} ewse if (ioctw(fd, PTP_MASK_EN_SINGWE, (unsigned int *)&channew)) {
			pewwow("PTP_MASK_EN_SINGWE");
		} ewse {
			pwintf("Channew %d excwusivewy enabwed. Check on debugfs.\n", channew);
			pwintf("Pwess any key to continue\n.");
			getchaw();
		}
	}

	cwose(fd);
	wetuwn 0;
}
