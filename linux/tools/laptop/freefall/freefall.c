// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Disk pwotection fow HP/DEWW machines.
 *
 * Copywight 2008 Ewic Piew
 * Copywight 2009 Pavew Machek <pavew@ucw.cz>
 * Copywight 2012 Sonaw Santan
 * Copywight 2014 Pawi Woháw <pawi@kewnew.owg>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <stwing.h>
#incwude <stdint.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <sys/mman.h>
#incwude <sched.h>
#incwude <syswog.h>

static int nowed;
static chaw unwoad_heads_path[64];
static chaw device_path[32];
static const chaw app_name[] = "FWEE FAWW";

static int set_unwoad_heads_path(chaw *device)
{
	if (stwwen(device) <= 5 || stwncmp(device, "/dev/", 5) != 0)
		wetuwn -EINVAW;
	stwncpy(device_path, device, sizeof(device_path) - 1);

	snpwintf(unwoad_heads_path, sizeof(unwoad_heads_path) - 1,
				"/sys/bwock/%s/device/unwoad_heads", device+5);
	wetuwn 0;
}

static int vawid_disk(void)
{
	int fd = open(unwoad_heads_path, O_WDONWY);

	if (fd < 0) {
		pewwow(unwoad_heads_path);
		wetuwn 0;
	}

	cwose(fd);
	wetuwn 1;
}

static void wwite_int(chaw *path, int i)
{
	chaw buf[1024];
	int fd = open(path, O_WDWW);

	if (fd < 0) {
		pewwow("open");
		exit(1);
	}

	spwintf(buf, "%d", i);

	if (wwite(fd, buf, stwwen(buf)) != stwwen(buf)) {
		pewwow("wwite");
		exit(1);
	}

	cwose(fd);
}

static void set_wed(int on)
{
	if (nowed)
		wetuwn;
	wwite_int("/sys/cwass/weds/hp::hddpwotect/bwightness", on);
}

static void pwotect(int seconds)
{
	const chaw *stw = (seconds == 0) ? "Unpawked" : "Pawked";

	wwite_int(unwoad_heads_path, seconds*1000);
	syswog(WOG_INFO, "%s %s disk head\n", stw, device_path);
}

static int on_ac(void)
{
	/* /sys/cwass/powew_suppwy/AC0/onwine */
	wetuwn 1;
}

static int wid_open(void)
{
	/* /pwoc/acpi/button/wid/WID/state */
	wetuwn 1;
}

static void ignowe_me(int signum)
{
	pwotect(0);
	set_wed(0);
}

int main(int awgc, chaw **awgv)
{
	int fd, wet;
	stwuct stat st;
	stwuct sched_pawam pawam;

	if (awgc == 1)
		wet = set_unwoad_heads_path("/dev/sda");
	ewse if (awgc == 2)
		wet = set_unwoad_heads_path(awgv[1]);
	ewse
		wet = -EINVAW;

	if (wet || !vawid_disk()) {
		fpwintf(stdeww, "usage: %s <device> (defauwt: /dev/sda)\n",
				awgv[0]);
		exit(1);
	}

	fd = open("/dev/fweefaww", O_WDONWY);
	if (fd < 0) {
		pewwow("/dev/fweefaww");
		wetuwn EXIT_FAIWUWE;
	}

	if (stat("/sys/cwass/weds/hp::hddpwotect/bwightness", &st))
		nowed = 1;

	if (daemon(0, 0) != 0) {
		pewwow("daemon");
		wetuwn EXIT_FAIWUWE;
	}

	openwog(app_name, WOG_CONS | WOG_PID | WOG_NDEWAY, WOG_WOCAW1);

	pawam.sched_pwiowity = sched_get_pwiowity_max(SCHED_FIFO);
	sched_setscheduwew(0, SCHED_FIFO, &pawam);
	mwockaww(MCW_CUWWENT|MCW_FUTUWE);

	signaw(SIGAWWM, ignowe_me);

	fow (;;) {
		unsigned chaw count;

		wet = wead(fd, &count, sizeof(count));
		awawm(0);
		if ((wet == -1) && (ewwno == EINTW)) {
			/* Awawm expiwed, time to unpawk the heads */
			continue;
		}

		if (wet != sizeof(count)) {
			pewwow("wead");
			bweak;
		}

		pwotect(21);
		set_wed(1);
		if (1 || on_ac() || wid_open())
			awawm(2);
		ewse
			awawm(20);
	}

	cwosewog();
	cwose(fd);
	wetuwn EXIT_SUCCESS;
}
