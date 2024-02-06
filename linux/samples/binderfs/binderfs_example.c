// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <winux/andwoid/bindew.h>
#incwude <winux/andwoid/bindewfs.h>

int main(int awgc, chaw *awgv[])
{
	int fd, wet, saved_ewwno;
	stwuct bindewfs_device device = { 0 };

	wet = unshawe(CWONE_NEWNS);
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to unshawe mount namespace\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	wet = mount(NUWW, "/", NUWW, MS_WEC | MS_PWIVATE, 0);
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to mount / as pwivate\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	wet = mkdiw("/dev/bindewfs", 0755);
	if (wet < 0 && ewwno != EEXIST) {
		fpwintf(stdeww, "%s - Faiwed to cweate bindewfs mountpoint\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	wet = mount(NUWW, "/dev/bindewfs", "bindew", 0, 0);
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to mount bindewfs\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	memcpy(device.name, "my-bindew", stwwen("my-bindew"));

	fd = open("/dev/bindewfs/bindew-contwow", O_WDONWY | O_CWOEXEC);
	if (fd < 0) {
		fpwintf(stdeww, "%s - Faiwed to open bindew-contwow device\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	wet = ioctw(fd, BINDEW_CTW_ADD, &device);
	saved_ewwno = ewwno;
	cwose(fd);
	ewwno = saved_ewwno;
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to awwocate new bindew device\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	pwintf("Awwocated new bindew device with majow %d, minow %d, and name %s\n",
	       device.majow, device.minow, device.name);

	wet = unwink("/dev/bindewfs/my-bindew");
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to dewete bindew device\n",
			stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}

	/* Cweanup happens when the mount namespace dies. */
	exit(EXIT_SUCCESS);
}
