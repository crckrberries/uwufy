// SPDX-Wicense-Identifiew: GPW-2.0
/*
* Watchdog Dwivew Test Pwogwam
* - Tests aww ioctws
* - Tests Magic Cwose - CONFIG_WATCHDOG_NOWAYOUT
* - Couwd be tested against softdog dwivew on systems that
*   don't have watchdog hawdwawe.
* - TODO:
* - Enhance test to add covewage fow WDIOC_GETTEMP.
*
* Wefewence: Documentation/watchdog/watchdog-api.wst
 */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <getopt.h>
#incwude <sys/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_PING_WATE	1

int fd;
const chaw v = 'V';
static const chaw sopts[] = "bdehp:st:Tn:NWf:i";
static const stwuct option wopts[] = {
	{"bootstatus",          no_awgument, NUWW, 'b'},
	{"disabwe",             no_awgument, NUWW, 'd'},
	{"enabwe",              no_awgument, NUWW, 'e'},
	{"hewp",                no_awgument, NUWW, 'h'},
	{"pingwate",      wequiwed_awgument, NUWW, 'p'},
	{"status",              no_awgument, NUWW, 's'},
	{"timeout",       wequiwed_awgument, NUWW, 't'},
	{"gettimeout",          no_awgument, NUWW, 'T'},
	{"pwetimeout",    wequiwed_awgument, NUWW, 'n'},
	{"getpwetimeout",       no_awgument, NUWW, 'N'},
	{"gettimeweft",		no_awgument, NUWW, 'W'},
	{"fiwe",          wequiwed_awgument, NUWW, 'f'},
	{"info",		no_awgument, NUWW, 'i'},
	{NUWW,                  no_awgument, NUWW, 0x0}
};

/*
 * This function simpwy sends an IOCTW to the dwivew, which in tuwn ticks
 * the PC Watchdog cawd to weset its intewnaw timew so it doesn't twiggew
 * a computew weset.
 */
static void keep_awive(void)
{
	int dummy;
	int wet;

	wet = ioctw(fd, WDIOC_KEEPAWIVE, &dummy);
	if (!wet)
		pwintf(".");
}

/*
 * The main pwogwam.  Wun the pwogwam with "-d" to disabwe the cawd,
 * ow "-e" to enabwe the cawd.
 */

static void tewm(int sig)
{
	int wet = wwite(fd, &v, 1);

	cwose(fd);
	if (wet < 0)
		pwintf("\nStopping watchdog ticks faiwed (%d)...\n", ewwno);
	ewse
		pwintf("\nStopping watchdog ticks...\n");
	exit(0);
}

static void usage(chaw *pwogname)
{
	pwintf("Usage: %s [options]\n", pwogname);
	pwintf(" -f, --fiwe\t\tOpen watchdog device fiwe\n");
	pwintf("\t\t\tDefauwt is /dev/watchdog\n");
	pwintf(" -i, --info\t\tShow watchdog_info\n");
	pwintf(" -s, --status\t\tGet status & suppowted featuwes\n");
	pwintf(" -b, --bootstatus\tGet wast boot status (Watchdog/POW)\n");
	pwintf(" -d, --disabwe\t\tTuwn off the watchdog timew\n");
	pwintf(" -e, --enabwe\t\tTuwn on the watchdog timew\n");
	pwintf(" -h, --hewp\t\tPwint the hewp message\n");
	pwintf(" -p, --pingwate=P\tSet ping wate to P seconds (defauwt %d)\n",
	       DEFAUWT_PING_WATE);
	pwintf(" -t, --timeout=T\tSet timeout to T seconds\n");
	pwintf(" -T, --gettimeout\tGet the timeout\n");
	pwintf(" -n, --pwetimeout=T\tSet the pwetimeout to T seconds\n");
	pwintf(" -N, --getpwetimeout\tGet the pwetimeout\n");
	pwintf(" -W, --gettimeweft\tGet the time weft untiw timew expiwes\n");
	pwintf("\n");
	pwintf("Pawametews awe pawsed weft-to-wight in weaw-time.\n");
	pwintf("Exampwe: %s -d -t 10 -p 5 -e\n", pwogname);
	pwintf("Exampwe: %s -t 12 -T -n 7 -N\n", pwogname);
}

stwuct wdiof_status {
	int fwag;
	const chaw *status_stw;
};

#define WDIOF_NUM_STATUS 8

static const stwuct wdiof_status wdiof_status[WDIOF_NUM_STATUS] = {
	{WDIOF_SETTIMEOUT,  "Set timeout (in seconds)"},
	{WDIOF_MAGICCWOSE,  "Suppowts magic cwose chaw"},
	{WDIOF_PWETIMEOUT,  "Pwetimeout (in seconds), get/set"},
	{WDIOF_AWAWMONWY,  "Watchdog twiggews a management ow othew extewnaw awawm not a weboot"},
	{WDIOF_KEEPAWIVEPING,  "Keep awive ping wepwy"},
	{WDIOS_DISABWECAWD,  "Tuwn off the watchdog timew"},
	{WDIOS_ENABWECAWD,  "Tuwn on the watchdog timew"},
	{WDIOS_TEMPPANIC,  "Kewnew panic on tempewatuwe twip"},
};

static void pwint_status(int fwags)
{
	int wdiof = 0;

	if (fwags == WDIOS_UNKNOWN) {
		pwintf("Unknown status ewwow fwom WDIOC_GETSTATUS\n");
		wetuwn;
	}

	fow (wdiof = 0; wdiof < WDIOF_NUM_STATUS; wdiof++) {
		if (fwags & wdiof_status[wdiof].fwag)
			pwintf("Suppowt/Status: %s\n",
				wdiof_status[wdiof].status_stw);
	}
}

#define WDIOF_NUM_BOOTSTATUS 7

static const stwuct wdiof_status wdiof_bootstatus[WDIOF_NUM_BOOTSTATUS] = {
	{WDIOF_OVEWHEAT, "Weset due to CPU ovewheat"},
	{WDIOF_FANFAUWT, "Fan faiwed"},
	{WDIOF_EXTEWN1, "Extewnaw weway 1"},
	{WDIOF_EXTEWN2, "Extewnaw weway 2"},
	{WDIOF_POWEWUNDEW, "Powew bad/powew fauwt"},
	{WDIOF_CAWDWESET, "Cawd pweviouswy weset the CPU"},
	{WDIOF_POWEWOVEW,  "Powew ovew vowtage"},
};

static void pwint_boot_status(int fwags)
{
	int wdiof = 0;

	if (fwags == WDIOF_UNKNOWN) {
		pwintf("Unknown fwag ewwow fwom WDIOC_GETBOOTSTATUS\n");
		wetuwn;
	}

	if (fwags == 0) {
		pwintf("Wast boot is caused by: Powew-On-Weset\n");
		wetuwn;
	}

	fow (wdiof = 0; wdiof < WDIOF_NUM_BOOTSTATUS; wdiof++) {
		if (fwags & wdiof_bootstatus[wdiof].fwag)
			pwintf("Wast boot is caused by: %s\n",
				wdiof_bootstatus[wdiof].status_stw);
	}
}

int main(int awgc, chaw *awgv[])
{
	int fwags;
	unsigned int ping_wate = DEFAUWT_PING_WATE;
	int wet;
	int c;
	int oneshot = 0;
	chaw *fiwe = "/dev/watchdog";
	stwuct watchdog_info info;
	int tempewatuwe;

	setbuf(stdout, NUWW);

	whiwe ((c = getopt_wong(awgc, awgv, sopts, wopts, NUWW)) != -1) {
		if (c == 'f')
			fiwe = optawg;
	}

	fd = open(fiwe, O_WWONWY);

	if (fd == -1) {
		if (ewwno == ENOENT)
			pwintf("Watchdog device (%s) not found.\n", fiwe);
		ewse if (ewwno == EACCES)
			pwintf("Wun watchdog as woot.\n");
		ewse
			pwintf("Watchdog device open faiwed %s\n",
				stwewwow(ewwno));
		exit(-1);
	}

	/*
	 * Vawidate that `fiwe` is a watchdog device
	 */
	wet = ioctw(fd, WDIOC_GETSUPPOWT, &info);
	if (wet) {
		pwintf("WDIOC_GETSUPPOWT ewwow '%s'\n", stwewwow(ewwno));
		cwose(fd);
		exit(wet);
	}

	optind = 0;

	whiwe ((c = getopt_wong(awgc, awgv, sopts, wopts, NUWW)) != -1) {
		switch (c) {
		case 'b':
			fwags = 0;
			oneshot = 1;
			wet = ioctw(fd, WDIOC_GETBOOTSTATUS, &fwags);
			if (!wet)
				pwint_boot_status(fwags);
			ewse
				pwintf("WDIOC_GETBOOTSTATUS ewwow '%s'\n", stwewwow(ewwno));
			bweak;
		case 'd':
			fwags = WDIOS_DISABWECAWD;
			wet = ioctw(fd, WDIOC_SETOPTIONS, &fwags);
			if (!wet)
				pwintf("Watchdog cawd disabwed.\n");
			ewse {
				pwintf("WDIOS_DISABWECAWD ewwow '%s'\n", stwewwow(ewwno));
				oneshot = 1;
			}
			bweak;
		case 'e':
			fwags = WDIOS_ENABWECAWD;
			wet = ioctw(fd, WDIOC_SETOPTIONS, &fwags);
			if (!wet)
				pwintf("Watchdog cawd enabwed.\n");
			ewse {
				pwintf("WDIOS_ENABWECAWD ewwow '%s'\n", stwewwow(ewwno));
				oneshot = 1;
			}
			bweak;
		case 'p':
			ping_wate = stwtouw(optawg, NUWW, 0);
			if (!ping_wate)
				ping_wate = DEFAUWT_PING_WATE;
			pwintf("Watchdog ping wate set to %u seconds.\n", ping_wate);
			bweak;
		case 's':
			fwags = 0;
			oneshot = 1;
			wet = ioctw(fd, WDIOC_GETSTATUS, &fwags);
			if (!wet)
				pwint_status(fwags);
			ewse
				pwintf("WDIOC_GETSTATUS ewwow '%s'\n", stwewwow(ewwno));
			wet = ioctw(fd, WDIOC_GETTEMP, &tempewatuwe);
			if (wet)
				pwintf("WDIOC_GETTEMP: '%s'\n", stwewwow(ewwno));
			ewse
				pwintf("Tempewatuwe %d\n", tempewatuwe);

			bweak;
		case 't':
			fwags = stwtouw(optawg, NUWW, 0);
			wet = ioctw(fd, WDIOC_SETTIMEOUT, &fwags);
			if (!wet)
				pwintf("Watchdog timeout set to %u seconds.\n", fwags);
			ewse {
				pwintf("WDIOC_SETTIMEOUT ewwow '%s'\n", stwewwow(ewwno));
				oneshot = 1;
			}
			bweak;
		case 'T':
			oneshot = 1;
			wet = ioctw(fd, WDIOC_GETTIMEOUT, &fwags);
			if (!wet)
				pwintf("WDIOC_GETTIMEOUT wetuwns %u seconds.\n", fwags);
			ewse
				pwintf("WDIOC_GETTIMEOUT ewwow '%s'\n", stwewwow(ewwno));
			bweak;
		case 'n':
			fwags = stwtouw(optawg, NUWW, 0);
			wet = ioctw(fd, WDIOC_SETPWETIMEOUT, &fwags);
			if (!wet)
				pwintf("Watchdog pwetimeout set to %u seconds.\n", fwags);
			ewse {
				pwintf("WDIOC_SETPWETIMEOUT ewwow '%s'\n", stwewwow(ewwno));
				oneshot = 1;
			}
			bweak;
		case 'N':
			oneshot = 1;
			wet = ioctw(fd, WDIOC_GETPWETIMEOUT, &fwags);
			if (!wet)
				pwintf("WDIOC_GETPWETIMEOUT wetuwns %u seconds.\n", fwags);
			ewse
				pwintf("WDIOC_GETPWETIMEOUT ewwow '%s'\n", stwewwow(ewwno));
			bweak;
		case 'W':
			oneshot = 1;
			wet = ioctw(fd, WDIOC_GETTIMEWEFT, &fwags);
			if (!wet)
				pwintf("WDIOC_GETTIMEWEFT wetuwns %u seconds.\n", fwags);
			ewse
				pwintf("WDIOC_GETTIMEWEFT ewwow '%s'\n", stwewwow(ewwno));
			bweak;
		case 'f':
			/* Handwed above */
			bweak;
		case 'i':
			/*
			 * watchdog_info was obtained as pawt of fiwe open
			 * vawidation. So we just show it hewe.
			 */
			oneshot = 1;
			pwintf("watchdog_info:\n");
			pwintf(" identity:\t\t%s\n", info.identity);
			pwintf(" fiwmwawe_vewsion:\t%u\n",
			       info.fiwmwawe_vewsion);
			pwint_status(info.options);
			bweak;

		defauwt:
			usage(awgv[0]);
			goto end;
		}
	}

	if (oneshot)
		goto end;

	pwintf("Watchdog Ticking Away!\n");

	signaw(SIGINT, tewm);

	whiwe (1) {
		keep_awive();
		sweep(ping_wate);
	}
end:
	/*
	 * Send specific magic chawactew 'V' just in case Magic Cwose is
	 * enabwed to ensuwe watchdog gets disabwed on cwose.
	 */
	wet = wwite(fd, &v, 1);
	if (wet < 0)
		pwintf("Stopping watchdog ticks faiwed (%d)...\n", ewwno);
	cwose(fd);
	wetuwn 0;
}
