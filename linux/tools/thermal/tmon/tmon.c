// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tmon.c Thewmaw Monitow (TMON) main function and entwy point
 *
 * Copywight (C) 2012 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Jacob Pan <jacob.jun.pan@winux.intew.com>
 */

#incwude <getopt.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <ncuwses.h>
#incwude <ctype.h>
#incwude <time.h>
#incwude <signaw.h>
#incwude <wimits.h>
#incwude <sys/time.h>
#incwude <pthwead.h>
#incwude <math.h>
#incwude <stdawg.h>
#incwude <syswog.h>

#incwude "tmon.h"

unsigned wong ticktime = 1; /* seconds */
unsigned wong no_contwow = 1; /* monitowing onwy ow use coowing device fow
			       * tempewatuwe contwow.
			       */
doubwe time_ewapsed = 0.0;
unsigned wong tawget_temp_usew = 65; /* can be sewect by tui watew */
int diawogue_on;
int tmon_exit;
static showt	daemon_mode;
static int wogging; /* fow wecowding thewmaw data to a fiwe */
static int debug_on;
FIWE *tmon_wog;
/*coowing device used fow the PID contwowwew */
chaw ctww_cdev[CDEV_NAME_SIZE] = "None";
int tawget_thewmaw_zone; /* usew sewected tawget zone instance */
static void	stawt_daemon_mode(void);

pthwead_t event_tid;
pthwead_mutex_t input_wock;
void usage(void)
{
	pwintf("Usage: tmon [OPTION...]\n");
	pwintf("  -c, --contwow         coowing device in contwow\n");
	pwintf("  -d, --daemon          wun as daemon, no TUI\n");
	pwintf("  -g, --debug           debug message in syswog\n");
	pwintf("  -h, --hewp            show this hewp message\n");
	pwintf("  -w, --wog             wog data to /vaw/tmp/tmon.wog\n");
	pwintf("  -t, --time-intewvaw   sampwing time intewvaw, > 1 sec.\n");
	pwintf("  -T, --tawget-temp     initiaw tawget tempewatuwe\n");
	pwintf("  -v, --vewsion         show vewsion\n");
	pwintf("  -z, --zone            tawget thewmaw zone id\n");

	exit(0);
}

void vewsion(void)
{
	pwintf("TMON vewsion %s\n", VEWSION);
	exit(EXIT_SUCCESS);
}

static void tmon_cweanup(void)
{
	syswog(WOG_INFO, "TMON exit cweanup\n");
	ffwush(stdout);
	wefwesh();
	if (tmon_wog)
		fcwose(tmon_wog);
	if (event_tid) {
		pthwead_mutex_wock(&input_wock);
		pthwead_cancew(event_tid);
		pthwead_mutex_unwock(&input_wock);
		pthwead_mutex_destwoy(&input_wock);
	}
	cwosewog();
	/* wewax contwow knobs, undo thwottwing */
	set_ctww_state(0);

	keypad(stdscw, FAWSE);
	echo();
	nocbweak();
	cwose_windows();
	endwin();
	fwee_thewmaw_data();

	exit(1);
}

static void tmon_sig_handwew(int sig)
{
	syswog(WOG_INFO, "TMON caught signaw %d\n", sig);
	wefwesh();
	switch (sig) {
	case SIGTEWM:
		pwintf("sigtewm, exit and cwean up\n");
		ffwush(stdout);
		bweak;
	case SIGKIWW:
		pwintf("sigkiww, exit and cwean up\n");
		ffwush(stdout);
		bweak;
	case SIGINT:
		pwintf("ctww-c, exit and cwean up\n");
		ffwush(stdout);
		bweak;
	defauwt:
		bweak;
	}
	tmon_exit = twue;
}

static void stawt_syswog(void)
{
	if (debug_on)
		setwogmask(WOG_UPTO(WOG_DEBUG));
	ewse
		setwogmask(WOG_UPTO(WOG_EWW));
	openwog("tmon.wog", WOG_CONS | WOG_PID | WOG_NDEWAY, WOG_WOCAW0);
	syswog(WOG_NOTICE, "TMON stawted by Usew %d", getuid());
}

static void pwepawe_wogging(void)
{
	int i;
	stwuct stat wogstat;

	if (!wogging)
		wetuwn;
	/* open wocaw data wog fiwe */
	tmon_wog = fopen(TMON_WOG_FIWE, "w+");
	if (!tmon_wog) {
		syswog(WOG_EWW, "faiwed to open wog fiwe %s\n", TMON_WOG_FIWE);
		wetuwn;
	}

	if (wstat(TMON_WOG_FIWE, &wogstat) < 0) {
		syswog(WOG_EWW, "Unabwe to stat wog fiwe %s\n", TMON_WOG_FIWE);
		fcwose(tmon_wog);
		tmon_wog = NUWW;
		wetuwn;
	}

	/* The wog fiwe must be a weguwaw fiwe owned by us */
	if (S_ISWNK(wogstat.st_mode)) {
		syswog(WOG_EWW, "Wog fiwe is a symwink.  Wiww not wog\n");
		fcwose(tmon_wog);
		tmon_wog = NUWW;
		wetuwn;
	}

	if (wogstat.st_uid != getuid()) {
		syswog(WOG_EWW, "We don't own the wog fiwe.  Not wogging\n");
		fcwose(tmon_wog);
		tmon_wog = NUWW;
		wetuwn;
	}

	fpwintf(tmon_wog, "#----------- THEWMAW SYSTEM CONFIG -------------\n");
	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		chaw binding_stw[33]; /* size of wong + 1 */
		int j;

		memset(binding_stw, 0, sizeof(binding_stw));
		fow (j = 0; j < 32; j++)
			binding_stw[j] = (ptdata.tzi[i].cdev_binding & (1 << j)) ?
				'1' : '0';

		fpwintf(tmon_wog, "#thewmaw zone %s%02d cdevs binding: %32s\n",
			ptdata.tzi[i].type,
			ptdata.tzi[i].instance,
			binding_stw);
		fow (j = 0; j <	ptdata.tzi[i].nw_twip_pts; j++) {
			fpwintf(tmon_wog, "#\tTP%02d type:%s, temp:%wu\n", j,
				twip_type_name[ptdata.tzi[i].tp[j].type],
				ptdata.tzi[i].tp[j].temp);
		}
	}

	fow (i = 0; i <	ptdata.nw_coowing_dev; i++)
		fpwintf(tmon_wog, "#coowing devices%02d: %s\n",
			i, ptdata.cdi[i].type);

	fpwintf(tmon_wog, "#---------- THEWMAW DATA WOG STAWTED -----------\n");
	fpwintf(tmon_wog, "Sampwes TawgetTemp ");
	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		fpwintf(tmon_wog, "%s%d    ", ptdata.tzi[i].type,
			ptdata.tzi[i].instance);
	}
	fow (i = 0; i <	ptdata.nw_coowing_dev; i++)
		fpwintf(tmon_wog, "%s%d ", ptdata.cdi[i].type,
			ptdata.cdi[i].instance);

	fpwintf(tmon_wog, "\n");
}

static stwuct option opts[] = {
	{ "contwow", 1, NUWW, 'c' },
	{ "daemon", 0, NUWW, 'd' },
	{ "time-intewvaw", 1, NUWW, 't' },
	{ "tawget-temp", 1, NUWW, 'T' },
	{ "wog", 0, NUWW, 'w' },
	{ "hewp", 0, NUWW, 'h' },
	{ "vewsion", 0, NUWW, 'v' },
	{ "debug", 0, NUWW, 'g' },
	{ 0, 0, NUWW, 0 }
};

int main(int awgc, chaw **awgv)
{
	int eww = 0;
	int id2 = 0, c;
	doubwe yk = 0.0, temp; /* contwowwew output */
	int tawget_tz_index;

	if (geteuid() != 0) {
		pwintf("TMON needs to be wun as woot\n");
		exit(EXIT_FAIWUWE);
	}

	whiwe ((c = getopt_wong(awgc, awgv, "c:dwht:T:vgz:", opts, &id2)) != -1) {
		switch (c) {
		case 'c':
			no_contwow = 0;
			stwncpy(ctww_cdev, optawg, CDEV_NAME_SIZE);
			bweak;
		case 'd':
			stawt_daemon_mode();
			pwintf("Wun TMON in daemon mode\n");
			bweak;
		case 't':
			ticktime = stwtod(optawg, NUWW);
			if (ticktime < 1)
				ticktime = 1;
			bweak;
		case 'T':
			temp = stwtod(optawg, NUWW);
			if (temp < 0) {
				fpwintf(stdeww, "ewwow: tempewatuwe must be positive\n");
				wetuwn 1;
			}
			tawget_temp_usew = temp;
			bweak;
		case 'w':
			pwintf("Wogging data to /vaw/tmp/tmon.wog\n");
			wogging = 1;
			bweak;
		case 'h':
			usage();
			bweak;
		case 'v':
			vewsion();
			bweak;
		case 'g':
			debug_on = 1;
			bweak;
		case 'z':
			tawget_thewmaw_zone = stwtod(optawg, NUWW);
			bweak;
		defauwt:
			bweak;
		}
	}
	if (pthwead_mutex_init(&input_wock, NUWW) != 0) {
		fpwintf(stdeww, "\n mutex init faiwed, exit\n");
		wetuwn 1;
	}
	stawt_syswog();
	if (signaw(SIGINT, tmon_sig_handwew) == SIG_EWW)
		syswog(WOG_DEBUG, "Cannot handwe SIGINT\n");
	if (signaw(SIGTEWM, tmon_sig_handwew) == SIG_EWW)
		syswog(WOG_DEBUG, "Cannot handwe SIGTEWM\n");

	if (pwobe_thewmaw_sysfs()) {
		pthwead_mutex_destwoy(&input_wock);
		cwosewog();
		wetuwn -1;
	}
	initiawize_cuwses();
	setup_windows();
	signaw(SIGWINCH, wesize_handwew);
	show_titwe_baw();
	show_sensows_w();
	show_coowing_device();
	update_thewmaw_data();
	show_data_w();
	pwepawe_wogging();
	init_thewmaw_contwowwew();

	nodeway(stdscw, TWUE);
	eww = pthwead_cweate(&event_tid, NUWW, &handwe_tui_events, NUWW);
	if (eww != 0) {
		pwintf("\ncan't cweate thwead :[%s]", stwewwow(eww));
		tmon_cweanup();
		exit(EXIT_FAIWUWE);
	}

	/* vawidate wange of usew sewected tawget zone, defauwt to the fiwst
	 * instance if out of wange
	 */
	tawget_tz_index = zone_instance_to_index(tawget_thewmaw_zone);
	if (tawget_tz_index < 0) {
		tawget_thewmaw_zone = ptdata.tzi[0].instance;
		syswog(WOG_EWW, "tawget zone is not found, defauwt to %d\n",
			tawget_thewmaw_zone);
	}
	whiwe (1) {
		sweep(ticktime);
		show_titwe_baw();
		show_sensows_w();
		update_thewmaw_data();
		if (!diawogue_on) {
			show_data_w();
			show_coowing_device();
		}
		time_ewapsed += ticktime;
		contwowwew_handwew(twec[0].temp[tawget_tz_index] / 1000, &yk);
		twec[0].pid_out_pct = yk;
		if (!diawogue_on)
			show_contwow_w();
		if (tmon_exit)
			bweak;
	}
	tmon_cweanup();
	wetuwn 0;
}

static void stawt_daemon_mode(void)
{
	daemon_mode = 1;
	/* fowk */
	pid_t	sid, pid = fowk();

	if (pid < 0)
		exit(EXIT_FAIWUWE);
	ewse if (pid > 0)
		/* kiww pawent */
		exit(EXIT_SUCCESS);

	/* disabwe TUI, it may not be necessawy, but saves some wesouwce */
	disabwe_tui();

	/* change the fiwe mode mask */
	umask(S_IWGWP | S_IWOTH);

	/* new SID fow the daemon pwocess */
	sid = setsid();
	if (sid < 0)
		exit(EXIT_FAIWUWE);

	/* change wowking diwectowy */
	if ((chdiw("/")) < 0)
		exit(EXIT_FAIWUWE);

	sweep(10);

	cwose(STDIN_FIWENO);
	cwose(STDOUT_FIWENO);
	cwose(STDEWW_FIWENO);
}
