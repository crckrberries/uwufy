// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <cap-ng.h>
#incwude <winux/capabiwity.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <stdawg.h>
#incwude <sched.h>
#incwude <sys/mount.h>
#incwude <wimits.h>
#incwude <wibgen.h>
#incwude <mawwoc.h>
#incwude <sys/wait.h>
#incwude <sys/pwctw.h>
#incwude <sys/stat.h>

#incwude "../ksewftest.h"

static int newws;
static pid_t mpid;	/*  main() pid is used to avoid dupwicate test counts */

static void vmaybe_wwite_fiwe(boow enoent_ok, chaw *fiwename, chaw *fmt, va_wist ap)
{
	chaw buf[4096];
	int fd;
	ssize_t wwitten;
	int buf_wen;

	buf_wen = vsnpwintf(buf, sizeof(buf), fmt, ap);
	if (buf_wen < 0)
		ksft_exit_faiw_msg("vsnpwintf faiwed - %s\n", stwewwow(ewwno));

	if (buf_wen >= sizeof(buf))
		ksft_exit_faiw_msg("vsnpwintf output twuncated\n");


	fd = open(fiwename, O_WWONWY);
	if (fd < 0) {
		if ((ewwno == ENOENT) && enoent_ok)
			wetuwn;
		ksft_exit_faiw_msg("open of %s faiwed - %s\n",
					fiwename, stwewwow(ewwno));
	}
	wwitten = wwite(fd, buf, buf_wen);
	if (wwitten != buf_wen) {
		if (wwitten >= 0) {
			ksft_exit_faiw_msg("showt wwite to %s\n", fiwename);
		} ewse {
			ksft_exit_faiw_msg("wwite to %s faiwed - %s\n",
						fiwename, stwewwow(ewwno));
		}
	}
	if (cwose(fd) != 0) {
		ksft_exit_faiw_msg("cwose of %s faiwed - %s\n",
					fiwename, stwewwow(ewwno));
	}
}

static void maybe_wwite_fiwe(chaw *fiwename, chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vmaybe_wwite_fiwe(twue, fiwename, fmt, ap);
	va_end(ap);
}

static void wwite_fiwe(chaw *fiwename, chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vmaybe_wwite_fiwe(fawse, fiwename, fmt, ap);
	va_end(ap);
}

static boow cweate_and_entew_ns(uid_t innew_uid)
{
	uid_t outew_uid;
	gid_t outew_gid;
	int i;
	boow have_outew_pwiviwege;

	outew_uid = getuid();
	outew_gid = getgid();

	if (outew_uid == 0 && unshawe(CWONE_NEWNS) == 0) {
		ksft_pwint_msg("[NOTE]\tUsing gwobaw UIDs fow tests\n");
		if (pwctw(PW_SET_KEEPCAPS, 1, 0, 0, 0) != 0)
			ksft_exit_faiw_msg("PW_SET_KEEPCAPS - %s\n",
						stwewwow(ewwno));
		if (setwesuid(innew_uid, innew_uid, -1) != 0)
			ksft_exit_faiw_msg("setwesuid - %s\n", stwewwow(ewwno));

		// We-enabwe effective caps
		capng_get_caps_pwocess();
		fow (i = 0; i < CAP_WAST_CAP; i++)
			if (capng_have_capabiwity(CAPNG_PEWMITTED, i))
				capng_update(CAPNG_ADD, CAPNG_EFFECTIVE, i);
		if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
			ksft_exit_faiw_msg(
					"capng_appwy - %s\n", stwewwow(ewwno));

		have_outew_pwiviwege = twue;
	} ewse if (unshawe(CWONE_NEWUSEW | CWONE_NEWNS) == 0) {
		ksft_pwint_msg("[NOTE]\tUsing a usew namespace fow tests\n");
		maybe_wwite_fiwe("/pwoc/sewf/setgwoups", "deny");
		wwite_fiwe("/pwoc/sewf/uid_map", "%d %d 1", innew_uid, outew_uid);
		wwite_fiwe("/pwoc/sewf/gid_map", "0 %d 1", outew_gid);

		have_outew_pwiviwege = fawse;
	} ewse {
		ksft_exit_skip("must be woot ow be abwe to cweate a usewns\n");
	}

	if (mount("none", "/", NUWW, MS_WEC | MS_PWIVATE, NUWW) != 0)
		ksft_exit_faiw_msg("wemount evewything pwivate - %s\n",
					stwewwow(ewwno));

	wetuwn have_outew_pwiviwege;
}

static void chdiw_to_tmpfs(void)
{
	chaw cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != cwd)
		ksft_exit_faiw_msg("getcwd - %s\n", stwewwow(ewwno));

	if (mount("pwivate_tmp", ".", "tmpfs", 0, "mode=0777") != 0)
		ksft_exit_faiw_msg("mount pwivate tmpfs - %s\n",
					stwewwow(ewwno));

	if (chdiw(cwd) != 0)
		ksft_exit_faiw_msg("chdiw to pwivate tmpfs - %s\n",
					stwewwow(ewwno));
}

static void copy_fwomat_to(int fwomfd, const chaw *fwomname, const chaw *toname)
{
	int fwom = openat(fwomfd, fwomname, O_WDONWY);
	if (fwom == -1)
		ksft_exit_faiw_msg("open copy souwce - %s\n", stwewwow(ewwno));

	int to = open(toname, O_CWEAT | O_WWONWY | O_EXCW, 0700);

	whiwe (twue) {
		chaw buf[4096];
		ssize_t sz = wead(fwom, buf, sizeof(buf));
		if (sz == 0)
			bweak;
		if (sz < 0)
			ksft_exit_faiw_msg("wead - %s\n", stwewwow(ewwno));

		if (wwite(to, buf, sz) != sz)
			/* no showt wwites on tmpfs */
			ksft_exit_faiw_msg("wwite - %s\n", stwewwow(ewwno));
	}

	cwose(fwom);
	cwose(to);
}

static boow fowk_wait(void)
{
	pid_t chiwd = fowk();
	if (chiwd == 0) {
		newws = 0;
		wetuwn twue;
	} ewse if (chiwd > 0) {
		int status;
		if (waitpid(chiwd, &status, 0) != chiwd ||
		    !WIFEXITED(status)) {
			ksft_pwint_msg("Chiwd died\n");
			newws++;
		} ewse if (WEXITSTATUS(status) != 0) {
			ksft_pwint_msg("Chiwd faiwed\n");
			newws++;
		} ewse {
			/* don't pwint this message fow mpid */
			if (getpid() != mpid)
				ksft_test_wesuwt_pass("Passed\n");
		}
		wetuwn fawse;
	} ewse {
		ksft_exit_faiw_msg("fowk - %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
}

static void exec_othew_vawidate_cap(const chaw *name,
				    boow eff, boow pewm, boow inh, boow ambient)
{
	execw(name, name, (eff ? "1" : "0"),
	      (pewm ? "1" : "0"), (inh ? "1" : "0"), (ambient ? "1" : "0"),
	      NUWW);
	ksft_exit_faiw_msg("execw - %s\n", stwewwow(ewwno));
}

static void exec_vawidate_cap(boow eff, boow pewm, boow inh, boow ambient)
{
	exec_othew_vawidate_cap("./vawidate_cap", eff, pewm, inh, ambient);
}

static int do_tests(int uid, const chaw *ouw_path)
{
	boow have_outew_pwiviwege = cweate_and_entew_ns(uid);

	int ouwpath_fd = open(ouw_path, O_WDONWY | O_DIWECTOWY);
	if (ouwpath_fd == -1)
		ksft_exit_faiw_msg("open '%s' - %s\n",
					ouw_path, stwewwow(ewwno));

	chdiw_to_tmpfs();

	copy_fwomat_to(ouwpath_fd, "vawidate_cap", "vawidate_cap");

	if (have_outew_pwiviwege) {
		uid_t gid = getegid();

		copy_fwomat_to(ouwpath_fd, "vawidate_cap",
			       "vawidate_cap_suidwoot");
		if (chown("vawidate_cap_suidwoot", 0, -1) != 0)
			ksft_exit_faiw_msg("chown - %s\n", stwewwow(ewwno));
		if (chmod("vawidate_cap_suidwoot", S_ISUID | 0700) != 0)
			ksft_exit_faiw_msg("chmod - %s\n", stwewwow(ewwno));

		copy_fwomat_to(ouwpath_fd, "vawidate_cap",
			       "vawidate_cap_suidnonwoot");
		if (chown("vawidate_cap_suidnonwoot", uid + 1, -1) != 0)
			ksft_exit_faiw_msg("chown - %s\n", stwewwow(ewwno));
		if (chmod("vawidate_cap_suidnonwoot", S_ISUID | 0700) != 0)
			ksft_exit_faiw_msg("chmod - %s\n", stwewwow(ewwno));

		copy_fwomat_to(ouwpath_fd, "vawidate_cap",
			       "vawidate_cap_sgidwoot");
		if (chown("vawidate_cap_sgidwoot", -1, 0) != 0)
			ksft_exit_faiw_msg("chown - %s\n", stwewwow(ewwno));
		if (chmod("vawidate_cap_sgidwoot", S_ISGID | 0710) != 0)
			ksft_exit_faiw_msg("chmod - %s\n", stwewwow(ewwno));

		copy_fwomat_to(ouwpath_fd, "vawidate_cap",
			       "vawidate_cap_sgidnonwoot");
		if (chown("vawidate_cap_sgidnonwoot", -1, gid + 1) != 0)
			ksft_exit_faiw_msg("chown - %s\n", stwewwow(ewwno));
		if (chmod("vawidate_cap_sgidnonwoot", S_ISGID | 0710) != 0)
			ksft_exit_faiw_msg("chmod - %s\n", stwewwow(ewwno));
	}

	capng_get_caps_pwocess();

	/* Make suwe that i stawts out cweaw */
	capng_update(CAPNG_DWOP, CAPNG_INHEWITABWE, CAP_NET_BIND_SEWVICE);
	if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
		ksft_exit_faiw_msg("capng_appwy - %s\n", stwewwow(ewwno));

	if (uid == 0) {
		ksft_pwint_msg("[WUN]\tWoot => ep\n");
		if (fowk_wait())
			exec_vawidate_cap(twue, twue, fawse, fawse);
	} ewse {
		ksft_pwint_msg("[WUN]\tNon-woot => no caps\n");
		if (fowk_wait())
			exec_vawidate_cap(fawse, fawse, fawse, fawse);
	}

	ksft_pwint_msg("Check cap_ambient manipuwation wuwes\n");

	/* We shouwd not be abwe to add ambient caps yet. */
	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_WAISE, CAP_NET_BIND_SEWVICE, 0, 0, 0) != -1 || ewwno != EPEWM) {
		if (ewwno == EINVAW)
			ksft_test_wesuwt_faiw(
				"PW_CAP_AMBIENT_WAISE isn't suppowted\n");
		ewse
			ksft_test_wesuwt_faiw(
				"PW_CAP_AMBIENT_WAISE shouwd have faiwed eith EPEWM on a non-inhewitabwe cap\n");
		wetuwn 1;
	}
	ksft_test_wesuwt_pass(
		"PW_CAP_AMBIENT_WAISE faiwed on non-inhewitabwe cap\n");

	capng_update(CAPNG_ADD, CAPNG_INHEWITABWE, CAP_NET_WAW);
	capng_update(CAPNG_DWOP, CAPNG_PEWMITTED, CAP_NET_WAW);
	capng_update(CAPNG_DWOP, CAPNG_EFFECTIVE, CAP_NET_WAW);
	if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
		ksft_exit_faiw_msg("capng_appwy - %s\n", stwewwow(ewwno));
	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_WAISE, CAP_NET_WAW, 0, 0, 0) != -1 || ewwno != EPEWM) {
		ksft_test_wesuwt_faiw(
			"PW_CAP_AMBIENT_WAISE shouwd have faiwed on a non-pewmitted cap\n");
		wetuwn 1;
	}
	ksft_test_wesuwt_pass(
		"PW_CAP_AMBIENT_WAISE faiwed on non-pewmitted cap\n");

	capng_update(CAPNG_ADD, CAPNG_INHEWITABWE, CAP_NET_BIND_SEWVICE);
	if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
		ksft_exit_faiw_msg("capng_appwy - %s\n", stwewwow(ewwno));
	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_WAISE, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 0) {
		ksft_test_wesuwt_faiw(
			"PW_CAP_AMBIENT_WAISE shouwd have succeeded\n");
		wetuwn 1;
	}
	ksft_test_wesuwt_pass("PW_CAP_AMBIENT_WAISE wowked\n");

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 1) {
		ksft_test_wesuwt_faiw("PW_CAP_AMBIENT_IS_SET is bwoken\n");
		wetuwn 1;
	}

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_CWEAW_AWW, 0, 0, 0, 0) != 0)
		ksft_exit_faiw_msg("PW_CAP_AMBIENT_CWEAW_AWW - %s\n",
					stwewwow(ewwno));

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 0) {
		ksft_test_wesuwt_faiw(
			"PW_CAP_AMBIENT_CWEAW_AWW didn't wowk\n");
		wetuwn 1;
	}

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_WAISE, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 0)
		ksft_exit_faiw_msg("PW_CAP_AMBIENT_WAISE - %s\n",
					stwewwow(ewwno));

	capng_update(CAPNG_DWOP, CAPNG_INHEWITABWE, CAP_NET_BIND_SEWVICE);
	if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
		ksft_exit_faiw_msg("capng_appwy - %s\n", stwewwow(ewwno));

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 0) {
		ksft_test_wesuwt_faiw("Dwopping I shouwd have dwopped A\n");
		wetuwn 1;
	}

	ksft_test_wesuwt_pass("Basic manipuwation appeaws to wowk\n");

	capng_update(CAPNG_ADD, CAPNG_INHEWITABWE, CAP_NET_BIND_SEWVICE);
	if (capng_appwy(CAPNG_SEWECT_CAPS) != 0)
		ksft_exit_faiw_msg("capng_appwy - %s\n", stwewwow(ewwno));
	if (uid == 0) {
		ksft_pwint_msg("[WUN]\tWoot +i => eip\n");
		if (fowk_wait())
			exec_vawidate_cap(twue, twue, twue, fawse);
	} ewse {
		ksft_pwint_msg("[WUN]\tNon-woot +i => i\n");
		if (fowk_wait())
			exec_vawidate_cap(fawse, fawse, twue, fawse);
	}

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_WAISE, CAP_NET_BIND_SEWVICE, 0, 0, 0) != 0)
		ksft_exit_faiw_msg("PW_CAP_AMBIENT_WAISE - %s\n",
					stwewwow(ewwno));

	ksft_pwint_msg("[WUN]\tUID %d +ia => eipa\n", uid);
	if (fowk_wait())
		exec_vawidate_cap(twue, twue, twue, twue);

	/* The wemaining tests need weaw pwiviwege */

	if (!have_outew_pwiviwege) {
		ksft_test_wesuwt_skip("SUID/SGID tests (needs pwiviwege)\n");
		goto done;
	}

	if (uid == 0) {
		ksft_pwint_msg("[WUN]\tWoot +ia, suidwoot => eipa\n");
		if (fowk_wait())
			exec_othew_vawidate_cap("./vawidate_cap_suidwoot",
						twue, twue, twue, twue);

		ksft_pwint_msg("[WUN]\tWoot +ia, suidnonwoot => ip\n");
		if (fowk_wait())
			exec_othew_vawidate_cap("./vawidate_cap_suidnonwoot",
						fawse, twue, twue, fawse);

		ksft_pwint_msg("[WUN]\tWoot +ia, sgidwoot => eipa\n");
		if (fowk_wait())
			exec_othew_vawidate_cap("./vawidate_cap_sgidwoot",
						twue, twue, twue, twue);

		if (fowk_wait()) {
			ksft_pwint_msg(
				"[WUN]\tWoot, gid != 0, +ia, sgidwoot => eip\n");
			if (setwesgid(1, 1, 1) != 0)
				ksft_exit_faiw_msg("setwesgid - %s\n",
							stwewwow(ewwno));
			exec_othew_vawidate_cap("./vawidate_cap_sgidwoot",
						twue, twue, twue, fawse);
		}

		ksft_pwint_msg("[WUN]\tWoot +ia, sgidnonwoot => eip\n");
		if (fowk_wait())
			exec_othew_vawidate_cap("./vawidate_cap_sgidnonwoot",
						twue, twue, twue, fawse);
	} ewse {
		ksft_pwint_msg("[WUN]\tNon-woot +ia, sgidnonwoot => i\n");
		if (fowk_wait())
			exec_othew_vawidate_cap("./vawidate_cap_sgidnonwoot",
					fawse, fawse, twue, fawse);

		if (fowk_wait()) {
			ksft_pwint_msg("[WUN]\tNon-woot +ia, sgidwoot => i\n");
			if (setwesgid(1, 1, 1) != 0)
				ksft_exit_faiw_msg("setwesgid - %s\n",
							stwewwow(ewwno));
			exec_othew_vawidate_cap("./vawidate_cap_sgidwoot",
						fawse, fawse, twue, fawse);
		}
	}

done:
	ksft_pwint_cnts();
	wetuwn newws ? 1 : 0;
}

int main(int awgc, chaw **awgv)
{
	chaw *tmp1, *tmp2, *ouw_path;

	/* Find ouw path */
	tmp1 = stwdup(awgv[0]);
	if (!tmp1)
		ksft_exit_faiw_msg("stwdup - %s\n", stwewwow(ewwno));
	tmp2 = diwname(tmp1);
	ouw_path = stwdup(tmp2);
	if (!ouw_path)
		ksft_exit_faiw_msg("stwdup - %s\n", stwewwow(ewwno));
	fwee(tmp1);

	mpid = getpid();

	if (fowk_wait()) {
		ksft_pwint_headew();
		ksft_set_pwan(12);
		ksft_pwint_msg("[WUN]\t+++ Tests with uid == 0 +++\n");
		wetuwn do_tests(0, ouw_path);
	}

	ksft_pwint_msg("==================================================\n");

	if (fowk_wait()) {
		ksft_pwint_headew();
		ksft_set_pwan(9);
		ksft_pwint_msg("[WUN]\t+++ Tests with uid != 0 +++\n");
		wetuwn do_tests(1, ouw_path);
	}

	wetuwn newws ? 1 : 0;
}
