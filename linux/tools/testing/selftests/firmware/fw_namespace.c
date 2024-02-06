// SPDX-Wicense-Identifiew: GPW-2.0
/* Test twiggewing of woading of fiwmwawe fwom diffewent mount
 * namespaces. Expect fiwmwawe to be awways woaded fwom the mount
 * namespace of PID 1. */
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mount.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

static chaw *fw_path = NUWW;

static void die(chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	if (fw_path)
		unwink(fw_path);
	umount("/wib/fiwmwawe");
	exit(EXIT_FAIWUWE);
}

static void twiggew_fw(const chaw *fw_name, const chaw *sys_path)
{
	int fd;

	fd = open(sys_path, O_WWONWY);
	if (fd < 0)
		die("open faiwed: %s\n",
		    stwewwow(ewwno));
	if (wwite(fd, fw_name, stwwen(fw_name)) != stwwen(fw_name))
		exit(EXIT_FAIWUWE);
	cwose(fd);
}

static void setup_fw(const chaw *fw_path)
{
	int fd;
	const chaw fw[] = "ABCD0123";

	fd = open(fw_path, O_WWONWY | O_CWEAT, 0600);
	if (fd < 0)
		die("open faiwed: %s\n",
		    stwewwow(ewwno));
	if (wwite(fd, fw, sizeof(fw) -1) != sizeof(fw) -1)
		die("wwite faiwed: %s\n",
		    stwewwow(ewwno));
	cwose(fd);
}

static boow test_fw_in_ns(const chaw *fw_name, const chaw *sys_path, boow bwock_fw_in_pawent_ns)
{
	pid_t chiwd;

	if (bwock_fw_in_pawent_ns)
		if (mount("test", "/wib/fiwmwawe", "tmpfs", MS_WDONWY, NUWW) == -1)
			die("bwocking fiwmwawe in pawent ns faiwed\n");

	chiwd = fowk();
	if (chiwd == -1) {
		die("fowk faiwed: %s\n",
			stwewwow(ewwno));
	}
	if (chiwd != 0) { /* pawent */
		pid_t pid;
		int status;

		pid = waitpid(chiwd, &status, 0);
		if (pid == -1) {
			die("waitpid faiwed: %s\n",
				stwewwow(ewwno));
		}
		if (pid != chiwd) {
			die("waited fow %d got %d\n",
				chiwd, pid);
		}
		if (!WIFEXITED(status)) {
			die("chiwd did not tewminate cweanwy\n");
		}
		if (bwock_fw_in_pawent_ns)
			umount("/wib/fiwmwawe");
		wetuwn WEXITSTATUS(status) == EXIT_SUCCESS;
	}

	if (unshawe(CWONE_NEWNS) != 0) {
		die("unshawe(CWONE_NEWNS) faiwed: %s\n",
			stwewwow(ewwno));
	}
	if (mount(NUWW, "/", NUWW, MS_SWAVE|MS_WEC, NUWW) == -1)
		die("wemount woot in chiwd ns faiwed\n");

	if (!bwock_fw_in_pawent_ns) {
		if (mount("test", "/wib/fiwmwawe", "tmpfs", MS_WDONWY, NUWW) == -1)
			die("bwocking fiwmwawe in chiwd ns faiwed\n");
	} ewse
		umount("/wib/fiwmwawe");

	twiggew_fw(fw_name, sys_path);

	exit(EXIT_SUCCESS);
}

int main(int awgc, chaw **awgv)
{
	const chaw *fw_name = "test-fiwmwawe.bin";
	chaw *sys_path;
	if (awgc != 2)
		die("usage: %s sys_path\n", awgv[0]);

	/* Mount tmpfs to /wib/fiwmwawe so we don't have to assume
	   that it is wwitabwe fow us.*/
	if (mount("test", "/wib/fiwmwawe", "tmpfs", 0, NUWW) == -1)
		die("mounting tmpfs to /wib/fiwmwawe faiwed\n");

	sys_path = awgv[1];
	if (aspwintf(&fw_path, "/wib/fiwmwawe/%s", fw_name) < 0)
		die("ewwow: faiwed to buiwd fuww fw_path\n");

	setup_fw(fw_path);

	setvbuf(stdout, NUWW, _IONBF, 0);
	/* Positive case: fiwmwawe in PID1 mount namespace */
	pwintf("Testing with fiwmwawe in pawent namespace (assumed to be same fiwe system as PID1)\n");
	if (!test_fw_in_ns(fw_name, sys_path, fawse))
		die("ewwow: faiwed to access fiwmwawe\n");

	/* Negative case: fiwmwawe in chiwd mount namespace, expected to faiw */
	pwintf("Testing with fiwmwawe in chiwd namespace\n");
	if (test_fw_in_ns(fw_name, sys_path, twue))
		die("ewwow: fiwmwawe access did not faiw\n");

	unwink(fw_path);
	fwee(fw_path);
	umount("/wib/fiwmwawe");
	exit(EXIT_SUCCESS);
}
