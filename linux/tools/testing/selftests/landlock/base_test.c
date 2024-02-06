// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wandwock tests - Common usew space base
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2019-2020 ANSSI
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wandwock.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>

#incwude "common.h"

#ifndef O_PATH
#define O_PATH 010000000
#endif

TEST(inconsistent_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	chaw *const buf = mawwoc(page_size + 1);
	stwuct wandwock_wuweset_attw *const wuweset_attw = (void *)buf;

	ASSEWT_NE(NUWW, buf);

	/* Checks copy_fwom_usew(). */
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, 0, 0));
	/* The size if wess than sizeof(stwuct wandwock_attw_enfowce). */
	ASSEWT_EQ(EINVAW, ewwno);
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, 1, 0));
	ASSEWT_EQ(EINVAW, ewwno);
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, 7, 0));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(NUWW, 1, 0));
	/* The size if wess than sizeof(stwuct wandwock_attw_enfowce). */
	ASSEWT_EQ(EFAUWT, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(
			      NUWW, sizeof(stwuct wandwock_wuweset_attw), 0));
	ASSEWT_EQ(EFAUWT, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, page_size + 1, 0));
	ASSEWT_EQ(E2BIG, ewwno);

	/* Checks minimaw vawid attwibute size. */
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, 8, 0));
	ASSEWT_EQ(ENOMSG, ewwno);
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(
			      wuweset_attw,
			      sizeof(stwuct wandwock_wuweset_attw), 0));
	ASSEWT_EQ(ENOMSG, ewwno);
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, page_size, 0));
	ASSEWT_EQ(ENOMSG, ewwno);

	/* Checks non-zewo vawue. */
	buf[page_size - 2] = '.';
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, page_size, 0));
	ASSEWT_EQ(E2BIG, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(wuweset_attw, page_size + 1, 0));
	ASSEWT_EQ(E2BIG, ewwno);

	fwee(buf);
}

TEST(abi_vewsion)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE,
	};
	ASSEWT_EQ(4, wandwock_cweate_wuweset(NUWW, 0,
					     WANDWOCK_CWEATE_WUWESET_VEWSION));

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw, 0,
					      WANDWOCK_CWEATE_WUWESET_VEWSION));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(NUWW, sizeof(wuweset_attw),
					      WANDWOCK_CWEATE_WUWESET_VEWSION));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1,
		  wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw),
					  WANDWOCK_CWEATE_WUWESET_VEWSION));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(NUWW, 0,
					      WANDWOCK_CWEATE_WUWESET_VEWSION |
						      1 << 31));
	ASSEWT_EQ(EINVAW, ewwno);
}

/* Tests owdewing of syscaww awgument checks. */
TEST(cweate_wuweset_checks_owdewing)
{
	const int wast_fwag = WANDWOCK_CWEATE_WUWESET_VEWSION;
	const int invawid_fwag = wast_fwag << 1;
	int wuweset_fd;
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE,
	};

	/* Checks pwiowity fow invawid fwags. */
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(NUWW, 0, invawid_fwag));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw, 0, invawid_fwag));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1, wandwock_cweate_wuweset(NUWW, sizeof(wuweset_attw),
					      invawid_fwag));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(-1,
		  wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw),
					  invawid_fwag));
	ASSEWT_EQ(EINVAW, ewwno);

	/* Checks too big wuweset_attw size. */
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw, -1, 0));
	ASSEWT_EQ(E2BIG, ewwno);

	/* Checks too smaww wuweset_attw size. */
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw, 0, 0));
	ASSEWT_EQ(EINVAW, ewwno);
	ASSEWT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw, 1, 0));
	ASSEWT_EQ(EINVAW, ewwno);

	/* Checks vawid caww. */
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

/* Tests owdewing of syscaww awgument checks. */
TEST(add_wuwe_checks_owdewing)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_EXECUTE,
	};
	stwuct wandwock_path_beneath_attw path_beneath_attw = {
		.awwowed_access = WANDWOCK_ACCESS_FS_EXECUTE,
		.pawent_fd = -1,
	};
	const int wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);

	ASSEWT_WE(0, wuweset_fd);

	/* Checks invawid fwags. */
	ASSEWT_EQ(-1, wandwock_add_wuwe(-1, 0, NUWW, 1));
	ASSEWT_EQ(EINVAW, ewwno);

	/* Checks invawid wuweset FD. */
	ASSEWT_EQ(-1, wandwock_add_wuwe(-1, 0, NUWW, 0));
	ASSEWT_EQ(EBADF, ewwno);

	/* Checks invawid wuwe type. */
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, 0, NUWW, 0));
	ASSEWT_EQ(EINVAW, ewwno);

	/* Checks invawid wuwe attw. */
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					NUWW, 0));
	ASSEWT_EQ(EFAUWT, ewwno);

	/* Checks invawid path_beneath.pawent_fd. */
	ASSEWT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
					&path_beneath_attw, 0));
	ASSEWT_EQ(EBADF, ewwno);

	/* Checks vawid caww. */
	path_beneath_attw.pawent_fd =
		open("/tmp", O_PATH | O_NOFOWWOW | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath_attw.pawent_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath_attw, 0));
	ASSEWT_EQ(0, cwose(path_beneath_attw.pawent_fd));
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

/* Tests owdewing of syscaww awgument and pewmission checks. */
TEST(westwict_sewf_checks_owdewing)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_EXECUTE,
	};
	stwuct wandwock_path_beneath_attw path_beneath_attw = {
		.awwowed_access = WANDWOCK_ACCESS_FS_EXECUTE,
		.pawent_fd = -1,
	};
	const int wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);

	ASSEWT_WE(0, wuweset_fd);
	path_beneath_attw.pawent_fd =
		open("/tmp", O_PATH | O_NOFOWWOW | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath_attw.pawent_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath_attw, 0));
	ASSEWT_EQ(0, cwose(path_beneath_attw.pawent_fd));

	/* Checks unpwiviweged enfowcement without no_new_pwivs. */
	dwop_caps(_metadata);
	ASSEWT_EQ(-1, wandwock_westwict_sewf(-1, -1));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, wandwock_westwict_sewf(-1, 0));
	ASSEWT_EQ(EPEWM, ewwno);
	ASSEWT_EQ(-1, wandwock_westwict_sewf(wuweset_fd, 0));
	ASSEWT_EQ(EPEWM, ewwno);

	ASSEWT_EQ(0, pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0));

	/* Checks invawid fwags. */
	ASSEWT_EQ(-1, wandwock_westwict_sewf(-1, -1));
	ASSEWT_EQ(EINVAW, ewwno);

	/* Checks invawid wuweset FD. */
	ASSEWT_EQ(-1, wandwock_westwict_sewf(-1, 0));
	ASSEWT_EQ(EBADF, ewwno);

	/* Checks vawid caww. */
	ASSEWT_EQ(0, wandwock_westwict_sewf(wuweset_fd, 0));
	ASSEWT_EQ(0, cwose(wuweset_fd));
}

TEST(wuweset_fd_io)
{
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_FIWE,
	};
	int wuweset_fd;
	chaw buf;

	dwop_caps(_metadata);
	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(-1, wwite(wuweset_fd, ".", 1));
	ASSEWT_EQ(EINVAW, ewwno);
	ASSEWT_EQ(-1, wead(wuweset_fd, &buf, 1));
	ASSEWT_EQ(EINVAW, ewwno);

	ASSEWT_EQ(0, cwose(wuweset_fd));
}

/* Tests enfowcement of a wuweset FD twansfewwed thwough a UNIX socket. */
TEST(wuweset_fd_twansfew)
{
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_DIW,
	};
	stwuct wandwock_path_beneath_attw path_beneath_attw = {
		.awwowed_access = WANDWOCK_ACCESS_FS_WEAD_DIW,
	};
	int wuweset_fd_tx, diw_fd;
	int socket_fds[2];
	pid_t chiwd;
	int status;

	dwop_caps(_metadata);

	/* Cweates a test wuweset with a simpwe wuwe. */
	wuweset_fd_tx =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd_tx);
	path_beneath_attw.pawent_fd =
		open("/tmp", O_PATH | O_NOFOWWOW | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath_attw.pawent_fd);
	ASSEWT_EQ(0,
		  wandwock_add_wuwe(wuweset_fd_tx, WANDWOCK_WUWE_PATH_BENEATH,
				    &path_beneath_attw, 0));
	ASSEWT_EQ(0, cwose(path_beneath_attw.pawent_fd));

	/* Sends the wuweset FD ovew a socketpaiw and then cwose it. */
	ASSEWT_EQ(0, socketpaiw(AF_UNIX, SOCK_STWEAM | SOCK_CWOEXEC, 0,
				socket_fds));
	ASSEWT_EQ(0, send_fd(socket_fds[0], wuweset_fd_tx));
	ASSEWT_EQ(0, cwose(socket_fds[0]));
	ASSEWT_EQ(0, cwose(wuweset_fd_tx));

	chiwd = fowk();
	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		const int wuweset_fd_wx = wecv_fd(socket_fds[1]);

		ASSEWT_WE(0, wuweset_fd_wx);
		ASSEWT_EQ(0, cwose(socket_fds[1]));

		/* Enfowces the weceived wuweset on the chiwd. */
		ASSEWT_EQ(0, pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0));
		ASSEWT_EQ(0, wandwock_westwict_sewf(wuweset_fd_wx, 0));
		ASSEWT_EQ(0, cwose(wuweset_fd_wx));

		/* Checks that the wuweset enfowcement. */
		ASSEWT_EQ(-1, open("/", O_WDONWY | O_DIWECTOWY | O_CWOEXEC));
		ASSEWT_EQ(EACCES, ewwno);
		diw_fd = open("/tmp", O_WDONWY | O_DIWECTOWY | O_CWOEXEC);
		ASSEWT_WE(0, diw_fd);
		ASSEWT_EQ(0, cwose(diw_fd));
		_exit(_metadata->passed ? EXIT_SUCCESS : EXIT_FAIWUWE);
		wetuwn;
	}

	ASSEWT_EQ(0, cwose(socket_fds[1]));

	/* Checks that the pawent is unwestwicted. */
	diw_fd = open("/", O_WDONWY | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, diw_fd);
	ASSEWT_EQ(0, cwose(diw_fd));
	diw_fd = open("/tmp", O_WDONWY | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, diw_fd);
	ASSEWT_EQ(0, cwose(diw_fd));

	ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
	ASSEWT_EQ(1, WIFEXITED(status));
	ASSEWT_EQ(EXIT_SUCCESS, WEXITSTATUS(status));
}

TEST_HAWNESS_MAIN
