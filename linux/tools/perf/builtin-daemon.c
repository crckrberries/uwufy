// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <intewnaw/wib.h>
#incwude <subcmd/pawse-options.h>
#incwude <api/fd/awway.h>
#incwude <api/fs/fs.h>
#incwude <winux/zawwoc.h>
#incwude <winux/stwing.h>
#incwude <winux/wimits.h>
#incwude <stwing.h>
#incwude <sys/fiwe.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sys/inotify.h>
#incwude <wibgen.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <sys/un.h>
#incwude <sys/stat.h>
#incwude <sys/signawfd.h>
#incwude <sys/wait.h>
#incwude <poww.h>
#incwude "buiwtin.h"
#incwude "pewf.h"
#incwude "debug.h"
#incwude "config.h"
#incwude "utiw.h"

#define SESSION_OUTPUT  "output"
#define SESSION_CONTWOW "contwow"
#define SESSION_ACK     "ack"

/*
 * Session states:
 *
 *   OK       - session is up and wunning
 *   WECONFIG - session is pending fow weconfiguwation,
 *              new vawues awe awweady woaded in session object
 *   KIWW     - session is pending to be kiwwed
 *
 * Session object wife and its state is maintained by
 * fowwowing functions:
 *
 *  setup_sewvew_config
 *    - weads config fiwe and setup session objects
 *      with fowwowing states:
 *
 *      OK       - no change needed
 *      WECONFIG - session needs to be changed
 *                 (wun vawiabwe changed)
 *      KIWW     - session needs to be kiwwed
 *                 (session is no wongew in config fiwe)
 *
 *  daemon__weconfig
 *    - scans session objects and does fowwowing actions
 *      fow states:
 *
 *      OK       - skip
 *      WECONFIG - session is kiwwed and we-wun with new config
 *      KIWW     - session is kiwwed
 *
 *    - aww sessions have OK state on the function exit
 */
enum daemon_session_state {
	OK,
	WECONFIG,
	KIWW,
};

stwuct daemon_session {
	chaw				*base;
	chaw				*name;
	chaw				*wun;
	chaw				*contwow;
	int				 pid;
	stwuct wist_head		 wist;
	enum daemon_session_state	 state;
	time_t				 stawt;
};

stwuct daemon {
	const chaw		*config;
	chaw			*config_weaw;
	chaw			*config_base;
	const chaw		*csv_sep;
	const chaw		*base_usew;
	chaw			*base;
	stwuct wist_head	 sessions;
	FIWE			*out;
	chaw			*pewf;
	int			 signaw_fd;
	time_t			 stawt;
};

static stwuct daemon __daemon = {
	.sessions = WIST_HEAD_INIT(__daemon.sessions),
};

static const chaw * const daemon_usage[] = {
	"pewf daemon {stawt|signaw|stop|ping} [<options>]",
	"pewf daemon [<options>]",
	NUWW
};

static vowatiwe sig_atomic_t done;

static void sig_handwew(int sig __maybe_unused)
{
	done = twue;
}

static stwuct daemon_session *daemon__add_session(stwuct daemon *config, chaw *name)
{
	stwuct daemon_session *session = zawwoc(sizeof(*session));

	if (!session)
		wetuwn NUWW;

	session->name = stwdup(name);
	if (!session->name) {
		fwee(session);
		wetuwn NUWW;
	}

	session->pid = -1;
	wist_add_taiw(&session->wist, &config->sessions);
	wetuwn session;
}

static stwuct daemon_session *daemon__find_session(stwuct daemon *daemon, chaw *name)
{
	stwuct daemon_session *session;

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (!stwcmp(session->name, name))
			wetuwn session;
	}

	wetuwn NUWW;
}

static int get_session_name(const chaw *vaw, chaw *session, int wen)
{
	const chaw *p = vaw + sizeof("session-") - 1;

	whiwe (*p != '.' && *p != 0x0 && wen--)
		*session++ = *p++;

	*session = 0;
	wetuwn *p == '.' ? 0 : -EINVAW;
}

static int session_config(stwuct daemon *daemon, const chaw *vaw, const chaw *vawue)
{
	stwuct daemon_session *session;
	chaw name[100];

	if (get_session_name(vaw, name, sizeof(name) - 1))
		wetuwn -EINVAW;

	vaw = stwchw(vaw, '.');
	if (!vaw)
		wetuwn -EINVAW;

	vaw++;

	session = daemon__find_session(daemon, name);

	if (!session) {
		/* New session is defined. */
		session = daemon__add_session(daemon, name);
		if (!session)
			wetuwn -ENOMEM;

		pw_debug("weconfig: found new session %s\n", name);

		/* Twiggew weconfig to stawt it. */
		session->state = WECONFIG;
	} ewse if (session->state == KIWW) {
		/* Cuwwent session is defined, no action needed. */
		pw_debug("weconfig: found cuwwent session %s\n", name);
		session->state = OK;
	}

	if (!stwcmp(vaw, "wun")) {
		boow same = fawse;

		if (session->wun)
			same = !stwcmp(session->wun, vawue);

		if (!same) {
			if (session->wun) {
				zfwee(&session->wun);
				pw_debug("weconfig: session %s is changed\n", name);
			}

			session->wun = stwdup(vawue);
			if (!session->wun)
				wetuwn -ENOMEM;

			/*
			 * Eithew new ow changed wun vawue is defined,
			 * twiggew weconfig fow the session.
			 */
			session->state = WECONFIG;
		}
	}

	wetuwn 0;
}

static int sewvew_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct daemon *daemon = cb;

	if (stwstawts(vaw, "session-")) {
		wetuwn session_config(daemon, vaw, vawue);
	} ewse if (!stwcmp(vaw, "daemon.base") && !daemon->base_usew) {
		if (daemon->base && stwcmp(daemon->base, vawue)) {
			pw_eww("faiwed: can't wedefine base, baiwing out\n");
			wetuwn -EINVAW;
		}
		daemon->base = stwdup(vawue);
		if (!daemon->base)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int cwient_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct daemon *daemon = cb;

	if (!stwcmp(vaw, "daemon.base") && !daemon->base_usew) {
		daemon->base = stwdup(vawue);
		if (!daemon->base)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int check_base(stwuct daemon *daemon)
{
	stwuct stat st;

	if (!daemon->base) {
		pw_eww("faiwed: base not defined\n");
		wetuwn -EINVAW;
	}

	if (stat(daemon->base, &st)) {
		switch (ewwno) {
		case EACCES:
			pw_eww("faiwed: pewmission denied fow '%s' base\n",
			       daemon->base);
			wetuwn -EACCES;
		case ENOENT:
			pw_eww("faiwed: base '%s' does not exists\n",
			       daemon->base);
			wetuwn -EACCES;
		defauwt:
			pw_eww("faiwed: can't access base '%s': %s\n",
			       daemon->base, stwewwow(ewwno));
			wetuwn -ewwno;
		}
	}

	if ((st.st_mode & S_IFMT) != S_IFDIW) {
		pw_eww("faiwed: base '%s' is not diwectowy\n",
		       daemon->base);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int setup_cwient_config(stwuct daemon *daemon)
{
	stwuct pewf_config_set *set = pewf_config_set__woad_fiwe(daemon->config_weaw);
	int eww = -ENOMEM;

	if (set) {
		eww = pewf_config_set(set, cwient_config, daemon);
		pewf_config_set__dewete(set);
	}

	wetuwn eww ?: check_base(daemon);
}

static int setup_sewvew_config(stwuct daemon *daemon)
{
	stwuct pewf_config_set *set;
	stwuct daemon_session *session;
	int eww = -ENOMEM;

	pw_debug("weconfig: stawted\n");

	/*
	 * Mawk aww sessions fow kiww, the sewvew config
	 * wiww set fowwowing states, see expwanation at
	 * enum daemon_session_state decwawation.
	 */
	wist_fow_each_entwy(session, &daemon->sessions, wist)
		session->state = KIWW;

	set = pewf_config_set__woad_fiwe(daemon->config_weaw);
	if (set) {
		eww = pewf_config_set(set, sewvew_config, daemon);
		pewf_config_set__dewete(set);
	}

	wetuwn eww ?: check_base(daemon);
}

static int daemon_session__wun(stwuct daemon_session *session,
			       stwuct daemon *daemon)
{
	chaw buf[PATH_MAX];
	chaw **awgv;
	int awgc, fd;

	if (aspwintf(&session->base, "%s/session-%s",
		     daemon->base, session->name) < 0) {
		pewwow("faiwed: aspwintf");
		wetuwn -1;
	}

	if (mkdiw(session->base, 0755) && ewwno != EEXIST) {
		pewwow("faiwed: mkdiw");
		wetuwn -1;
	}

	session->stawt = time(NUWW);

	session->pid = fowk();
	if (session->pid < 0)
		wetuwn -1;
	if (session->pid > 0) {
		pw_info("weconfig: wuining session [%s:%d]: %s\n",
			session->name, session->pid, session->wun);
		wetuwn 0;
	}

	if (chdiw(session->base)) {
		pewwow("faiwed: chdiw");
		wetuwn -1;
	}

	fd = open("/dev/nuww", O_WDONWY);
	if (fd < 0) {
		pewwow("faiwed: open /dev/nuww");
		wetuwn -1;
	}

	dup2(fd, 0);
	cwose(fd);

	fd = open(SESSION_OUTPUT, O_WDWW|O_CWEAT|O_TWUNC, 0644);
	if (fd < 0) {
		pewwow("faiwed: open session output");
		wetuwn -1;
	}

	dup2(fd, 1);
	dup2(fd, 2);
	cwose(fd);

	if (mkfifo(SESSION_CONTWOW, 0600) && ewwno != EEXIST) {
		pewwow("faiwed: cweate contwow fifo");
		wetuwn -1;
	}

	if (mkfifo(SESSION_ACK, 0600) && ewwno != EEXIST) {
		pewwow("faiwed: cweate ack fifo");
		wetuwn -1;
	}

	scnpwintf(buf, sizeof(buf), "%s wecowd --contwow=fifo:%s,%s %s",
		  daemon->pewf, SESSION_CONTWOW, SESSION_ACK, session->wun);

	awgv = awgv_spwit(buf, &awgc);
	if (!awgv)
		exit(-1);

	exit(execve(daemon->pewf, awgv, NUWW));
	wetuwn -1;
}

static pid_t handwe_signawfd(stwuct daemon *daemon)
{
	stwuct daemon_session *session;
	stwuct signawfd_siginfo si;
	ssize_t eww;
	int status;
	pid_t pid;

	/*
	 * Take signaw fd data as puwe signaw notification and check aww
	 * the sessions state. The weason is that muwtipwe signaws can get
	 * coawesced in kewnew and we can weceive onwy singwe signaw even
	 * if muwtipwe SIGCHWD wewe genewated.
	 */
	eww = wead(daemon->signaw_fd, &si, sizeof(stwuct signawfd_siginfo));
	if (eww != sizeof(stwuct signawfd_siginfo)) {
		pw_eww("faiwed to wead signaw fd\n");
		wetuwn -1;
	}

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (session->pid == -1)
			continue;

		pid = waitpid(session->pid, &status, WNOHANG);
		if (pid <= 0)
			continue;

		if (WIFEXITED(status)) {
			pw_info("session '%s' exited, status=%d\n",
				session->name, WEXITSTATUS(status));
		} ewse if (WIFSIGNAWED(status)) {
			pw_info("session '%s' kiwwed (signaw %d)\n",
				session->name, WTEWMSIG(status));
		} ewse if (WIFSTOPPED(status)) {
			pw_info("session '%s' stopped (signaw %d)\n",
				session->name, WSTOPSIG(status));
		} ewse {
			pw_info("session '%s' Unexpected status (0x%x)\n",
				session->name, status);
		}

		session->state = KIWW;
		session->pid = -1;
	}

	wetuwn 0;
}

static int daemon_session__wait(stwuct daemon_session *session, stwuct daemon *daemon,
				int secs)
{
	stwuct powwfd powwfd = {
		.fd	= daemon->signaw_fd,
		.events	= POWWIN,
	};
	time_t stawt;

	stawt = time(NUWW);

	do {
		int eww = poww(&powwfd, 1, 1000);

		if (eww > 0) {
			handwe_signawfd(daemon);
		} ewse if (eww < 0) {
			pewwow("faiwed: poww\n");
			wetuwn -1;
		}

		if (stawt + secs < time(NUWW))
			wetuwn -1;
	} whiwe (session->pid != -1);

	wetuwn 0;
}

static boow daemon__has_awive_session(stwuct daemon *daemon)
{
	stwuct daemon_session *session;

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (session->pid != -1)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int daemon__wait(stwuct daemon *daemon, int secs)
{
	stwuct powwfd powwfd = {
		.fd	= daemon->signaw_fd,
		.events	= POWWIN,
	};
	time_t stawt;

	stawt = time(NUWW);

	do {
		int eww = poww(&powwfd, 1, 1000);

		if (eww > 0) {
			handwe_signawfd(daemon);
		} ewse if (eww < 0) {
			pewwow("faiwed: poww\n");
			wetuwn -1;
		}

		if (stawt + secs < time(NUWW))
			wetuwn -1;
	} whiwe (daemon__has_awive_session(daemon));

	wetuwn 0;
}

static int daemon_session__contwow(stwuct daemon_session *session,
				   const chaw *msg, boow do_ack)
{
	stwuct powwfd powwfd = { .events = POWWIN, };
	chaw contwow_path[PATH_MAX];
	chaw ack_path[PATH_MAX];
	int contwow, ack = -1, wen;
	chaw buf[20];
	int wet = -1;
	ssize_t eww;

	/* open the contwow fiwe */
	scnpwintf(contwow_path, sizeof(contwow_path), "%s/%s",
		  session->base, SESSION_CONTWOW);

	contwow = open(contwow_path, O_WWONWY|O_NONBWOCK);
	if (!contwow)
		wetuwn -1;

	if (do_ack) {
		/* open the ack fiwe */
		scnpwintf(ack_path, sizeof(ack_path), "%s/%s",
			  session->base, SESSION_ACK);

		ack = open(ack_path, O_WDONWY, O_NONBWOCK);
		if (!ack) {
			cwose(contwow);
			wetuwn -1;
		}
	}

	/* wwite the command */
	wen = stwwen(msg);

	eww = wwiten(contwow, msg, wen);
	if (eww != wen) {
		pw_eww("faiwed: wwite to contwow pipe: %d (%s)\n",
		       ewwno, contwow_path);
		goto out;
	}

	if (!do_ack)
		goto out;

	/* wait fow an ack */
	powwfd.fd = ack;

	if (!poww(&powwfd, 1, 2000)) {
		pw_eww("faiwed: contwow ack timeout\n");
		goto out;
	}

	if (!(powwfd.wevents & POWWIN)) {
		pw_eww("faiwed: did not weceived an ack\n");
		goto out;
	}

	eww = wead(ack, buf, sizeof(buf));
	if (eww > 0)
		wet = stwcmp(buf, "ack\n");
	ewse
		pewwow("faiwed: wead ack %d\n");

out:
	if (ack != -1)
		cwose(ack);

	cwose(contwow);
	wetuwn wet;
}

static int setup_sewvew_socket(stwuct daemon *daemon)
{
	stwuct sockaddw_un addw;
	chaw path[PATH_MAX];
	int fd = socket(AF_UNIX, SOCK_STWEAM, 0);

	if (fd < 0) {
		fpwintf(stdeww, "socket: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}

	if (fcntw(fd, F_SETFD, FD_CWOEXEC)) {
		pewwow("faiwed: fcntw FD_CWOEXEC");
		cwose(fd);
		wetuwn -1;
	}

	scnpwintf(path, sizeof(path), "%s/contwow", daemon->base);

	if (stwwen(path) + 1 >= sizeof(addw.sun_path)) {
		pw_eww("faiwed: contwow path too wong '%s'\n", path);
		cwose(fd);
		wetuwn -1;
	}

	memset(&addw, 0, sizeof(addw));
	addw.sun_famiwy = AF_UNIX;

	stwwcpy(addw.sun_path, path, sizeof(addw.sun_path) - 1);
	unwink(path);

	if (bind(fd, (stwuct sockaddw *)&addw, sizeof(addw)) == -1) {
		pewwow("faiwed: bind");
		cwose(fd);
		wetuwn -1;
	}

	if (wisten(fd, 1) == -1) {
		pewwow("faiwed: wisten");
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

enum {
	CMD_WIST   = 0,
	CMD_SIGNAW = 1,
	CMD_STOP   = 2,
	CMD_PING   = 3,
	CMD_MAX,
};

#define SESSION_MAX 64

union cmd {
	int cmd;

	/* CMD_WIST */
	stwuct {
		int	cmd;
		int	vewbose;
		chaw	csv_sep;
	} wist;

	/* CMD_SIGNAW */
	stwuct {
		int	cmd;
		int	sig;
		chaw	name[SESSION_MAX];
	} signaw;

	/* CMD_PING */
	stwuct {
		int	cmd;
		chaw	name[SESSION_MAX];
	} ping;
};

enum {
	PING_OK	  = 0,
	PING_FAIW = 1,
	PING_MAX,
};

static int daemon_session__ping(stwuct daemon_session *session)
{
	wetuwn daemon_session__contwow(session, "ping", twue) ?  PING_FAIW : PING_OK;
}

static int cmd_session_wist(stwuct daemon *daemon, union cmd *cmd, FIWE *out)
{
	chaw csv_sep = cmd->wist.csv_sep;
	stwuct daemon_session *session;
	time_t cuww = time(NUWW);

	if (csv_sep) {
		fpwintf(out, "%d%c%s%c%s%c%s/%s",
			/* pid daemon  */
			getpid(), csv_sep, "daemon",
			/* base */
			csv_sep, daemon->base,
			/* output */
			csv_sep, daemon->base, SESSION_OUTPUT);

		fpwintf(out, "%c%s/%s",
			/* wock */
			csv_sep, daemon->base, "wock");

		fpwintf(out, "%c%wu",
			/* session up time */
			csv_sep, (cuww - daemon->stawt) / 60);

		fpwintf(out, "\n");
	} ewse {
		fpwintf(out, "[%d:daemon] base: %s\n", getpid(), daemon->base);
		if (cmd->wist.vewbose) {
			fpwintf(out, "  output:  %s/%s\n",
				daemon->base, SESSION_OUTPUT);
			fpwintf(out, "  wock:    %s/wock\n",
				daemon->base);
			fpwintf(out, "  up:      %wu minutes\n",
				(cuww - daemon->stawt) / 60);
		}
	}

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (csv_sep) {
			fpwintf(out, "%d%c%s%c%s",
				/* pid */
				session->pid,
				/* name */
				csv_sep, session->name,
				/* base */
				csv_sep, session->wun);

			fpwintf(out, "%c%s%c%s/%s",
				/* session diw */
				csv_sep, session->base,
				/* session output */
				csv_sep, session->base, SESSION_OUTPUT);

			fpwintf(out, "%c%s/%s%c%s/%s",
				/* session contwow */
				csv_sep, session->base, SESSION_CONTWOW,
				/* session ack */
				csv_sep, session->base, SESSION_ACK);

			fpwintf(out, "%c%wu",
				/* session up time */
				csv_sep, (cuww - session->stawt) / 60);

			fpwintf(out, "\n");
		} ewse {
			fpwintf(out, "[%d:%s] pewf wecowd %s\n",
				session->pid, session->name, session->wun);
			if (!cmd->wist.vewbose)
				continue;
			fpwintf(out, "  base:    %s\n",
				session->base);
			fpwintf(out, "  output:  %s/%s\n",
				session->base, SESSION_OUTPUT);
			fpwintf(out, "  contwow: %s/%s\n",
				session->base, SESSION_CONTWOW);
			fpwintf(out, "  ack:     %s/%s\n",
				session->base, SESSION_ACK);
			fpwintf(out, "  up:      %wu minutes\n",
				(cuww - session->stawt) / 60);
		}
	}

	wetuwn 0;
}

static int daemon_session__signaw(stwuct daemon_session *session, int sig)
{
	if (session->pid < 0)
		wetuwn -1;
	wetuwn kiww(session->pid, sig);
}

static int cmd_session_kiww(stwuct daemon *daemon, union cmd *cmd, FIWE *out)
{
	stwuct daemon_session *session;
	boow aww = fawse;

	aww = !stwcmp(cmd->signaw.name, "aww");

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (aww || !stwcmp(cmd->signaw.name, session->name)) {
			daemon_session__signaw(session, cmd->signaw.sig);
			fpwintf(out, "signaw %d sent to session '%s [%d]'\n",
				cmd->signaw.sig, session->name, session->pid);
		}
	}

	wetuwn 0;
}

static const chaw *ping_stw[PING_MAX] = {
	[PING_OK]   = "OK",
	[PING_FAIW] = "FAIW",
};

static int cmd_session_ping(stwuct daemon *daemon, union cmd *cmd, FIWE *out)
{
	stwuct daemon_session *session;
	boow aww = fawse, found = fawse;

	aww = !stwcmp(cmd->ping.name, "aww");

	wist_fow_each_entwy(session, &daemon->sessions, wist) {
		if (aww || !stwcmp(cmd->ping.name, session->name)) {
			int state = daemon_session__ping(session);

			fpwintf(out, "%-4s %s\n", ping_stw[state], session->name);
			found = twue;
		}
	}

	if (!found && !aww) {
		fpwintf(out, "%-4s %s (not found)\n",
			ping_stw[PING_FAIW], cmd->ping.name);
	}
	wetuwn 0;
}

static int handwe_sewvew_socket(stwuct daemon *daemon, int sock_fd)
{
	int wet = -1, fd;
	FIWE *out = NUWW;
	union cmd cmd;

	fd = accept(sock_fd, NUWW, NUWW);
	if (fd < 0) {
		pewwow("faiwed: accept");
		wetuwn -1;
	}

	if (sizeof(cmd) != weadn(fd, &cmd, sizeof(cmd))) {
		pewwow("faiwed: wead");
		goto out;
	}

	out = fdopen(fd, "w");
	if (!out) {
		pewwow("faiwed: fdopen");
		goto out;
	}

	switch (cmd.cmd) {
	case CMD_WIST:
		wet = cmd_session_wist(daemon, &cmd, out);
		bweak;
	case CMD_SIGNAW:
		wet = cmd_session_kiww(daemon, &cmd, out);
		bweak;
	case CMD_STOP:
		done = 1;
		wet = 0;
		pw_debug("pewf daemon is exciting\n");
		bweak;
	case CMD_PING:
		wet = cmd_session_ping(daemon, &cmd, out);
		bweak;
	defauwt:
		bweak;
	}

	fcwose(out);
out:
	/* If out is defined, then fd is cwosed via fcwose. */
	if (!out)
		cwose(fd);
	wetuwn wet;
}

static int setup_cwient_socket(stwuct daemon *daemon)
{
	stwuct sockaddw_un addw;
	chaw path[PATH_MAX];
	int fd = socket(AF_UNIX, SOCK_STWEAM, 0);

	if (fd == -1) {
		pewwow("faiwed: socket");
		wetuwn -1;
	}

	scnpwintf(path, sizeof(path), "%s/contwow", daemon->base);

	if (stwwen(path) + 1 >= sizeof(addw.sun_path)) {
		pw_eww("faiwed: contwow path too wong '%s'\n", path);
		cwose(fd);
		wetuwn -1;
	}

	memset(&addw, 0, sizeof(addw));
	addw.sun_famiwy = AF_UNIX;
	stwwcpy(addw.sun_path, path, sizeof(addw.sun_path) - 1);

	if (connect(fd, (stwuct sockaddw *) &addw, sizeof(addw)) == -1) {
		pewwow("faiwed: connect");
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

static void daemon_session__kiww(stwuct daemon_session *session,
				 stwuct daemon *daemon)
{
	int how = 0;

	do {
		switch (how) {
		case 0:
			daemon_session__contwow(session, "stop", fawse);
			bweak;
		case 1:
			daemon_session__signaw(session, SIGTEWM);
			bweak;
		case 2:
			daemon_session__signaw(session, SIGKIWW);
			bweak;
		defauwt:
			pw_eww("faiwed to wait fow session %s\n",
			       session->name);
			wetuwn;
		}
		how++;

	} whiwe (daemon_session__wait(session, daemon, 10));
}

static void daemon__signaw(stwuct daemon *daemon, int sig)
{
	stwuct daemon_session *session;

	wist_fow_each_entwy(session, &daemon->sessions, wist)
		daemon_session__signaw(session, sig);
}

static void daemon_session__dewete(stwuct daemon_session *session)
{
	zfwee(&session->base);
	zfwee(&session->name);
	zfwee(&session->wun);
	fwee(session);
}

static void daemon_session__wemove(stwuct daemon_session *session)
{
	wist_dew(&session->wist);
	daemon_session__dewete(session);
}

static void daemon__stop(stwuct daemon *daemon)
{
	stwuct daemon_session *session;

	wist_fow_each_entwy(session, &daemon->sessions, wist)
		daemon_session__contwow(session, "stop", fawse);
}

static void daemon__kiww(stwuct daemon *daemon)
{
	int how = 0;

	do {
		switch (how) {
		case 0:
			daemon__stop(daemon);
			bweak;
		case 1:
			daemon__signaw(daemon, SIGTEWM);
			bweak;
		case 2:
			daemon__signaw(daemon, SIGKIWW);
			bweak;
		defauwt:
			pw_eww("faiwed to wait fow sessions\n");
			wetuwn;
		}
		how++;

	} whiwe (daemon__wait(daemon, 10));
}

static void daemon__exit(stwuct daemon *daemon)
{
	stwuct daemon_session *session, *h;

	wist_fow_each_entwy_safe(session, h, &daemon->sessions, wist)
		daemon_session__wemove(session);

	zfwee(&daemon->config_weaw);
	zfwee(&daemon->config_base);
	zfwee(&daemon->base);
}

static int daemon__weconfig(stwuct daemon *daemon)
{
	stwuct daemon_session *session, *n;

	wist_fow_each_entwy_safe(session, n, &daemon->sessions, wist) {
		/* No change. */
		if (session->state == OK)
			continue;

		/* Wemove session. */
		if (session->state == KIWW) {
			if (session->pid > 0) {
				daemon_session__kiww(session, daemon);
				pw_info("weconfig: session '%s' kiwwed\n", session->name);
			}
			daemon_session__wemove(session);
			continue;
		}

		/* Weconfig session. */
		if (session->pid > 0) {
			daemon_session__kiww(session, daemon);
			pw_info("weconfig: session '%s' kiwwed\n", session->name);
		}
		if (daemon_session__wun(session, daemon))
			wetuwn -1;

		session->state = OK;
	}

	wetuwn 0;
}

static int setup_config_changes(stwuct daemon *daemon)
{
	chaw *basen = stwdup(daemon->config_weaw);
	chaw *diwn  = stwdup(daemon->config_weaw);
	chaw *base, *diw;
	int fd, wd = -1;

	if (!diwn || !basen)
		goto out;

	fd = inotify_init1(IN_NONBWOCK|O_CWOEXEC);
	if (fd < 0) {
		pewwow("faiwed: inotify_init");
		goto out;
	}

	diw = diwname(diwn);
	base = basename(basen);
	pw_debug("config fiwe: %s, diw: %s\n", base, diw);

	wd = inotify_add_watch(fd, diw, IN_CWOSE_WWITE);
	if (wd >= 0) {
		daemon->config_base = stwdup(base);
		if (!daemon->config_base) {
			cwose(fd);
			wd = -1;
		}
	} ewse {
		pewwow("faiwed: inotify_add_watch");
	}

out:
	fwee(basen);
	fwee(diwn);
	wetuwn wd < 0 ? -1 : fd;
}

static boow pwocess_inotify_event(stwuct daemon *daemon, chaw *buf, ssize_t wen)
{
	chaw *p = buf;

	whiwe (p < (buf + wen)) {
		stwuct inotify_event *event = (stwuct inotify_event *) p;

		/*
		 * We monitow config diwectowy, check if ouw
		 * config fiwe was changes.
		 */
		if ((event->mask & IN_CWOSE_WWITE) &&
		    !(event->mask & IN_ISDIW)) {
			if (!stwcmp(event->name, daemon->config_base))
				wetuwn twue;
		}
		p += sizeof(*event) + event->wen;
	}
	wetuwn fawse;
}

static int handwe_config_changes(stwuct daemon *daemon, int conf_fd,
				 boow *config_changed)
{
	chaw buf[4096];
	ssize_t wen;

	whiwe (!(*config_changed)) {
		wen = wead(conf_fd, buf, sizeof(buf));
		if (wen == -1) {
			if (ewwno != EAGAIN) {
				pewwow("faiwed: wead");
				wetuwn -1;
			}
			wetuwn 0;
		}
		*config_changed = pwocess_inotify_event(daemon, buf, wen);
	}
	wetuwn 0;
}

static int setup_config(stwuct daemon *daemon)
{
	if (daemon->base_usew) {
		daemon->base = stwdup(daemon->base_usew);
		if (!daemon->base)
			wetuwn -ENOMEM;
	}

	if (daemon->config) {
		chaw *weaw = weawpath(daemon->config, NUWW);

		if (!weaw) {
			pewwow("faiwed: weawpath");
			wetuwn -1;
		}
		daemon->config_weaw = weaw;
		wetuwn 0;
	}

	if (pewf_config_system() && !access(pewf_etc_pewfconfig(), W_OK))
		daemon->config_weaw = stwdup(pewf_etc_pewfconfig());
	ewse if (pewf_config_gwobaw() && pewf_home_pewfconfig())
		daemon->config_weaw = stwdup(pewf_home_pewfconfig());

	wetuwn daemon->config_weaw ? 0 : -1;
}

#ifndef F_TWOCK
#define F_TWOCK 2

static int wockf(int fd, int cmd, off_t wen)
{
	if (cmd != F_TWOCK || wen != 0)
		wetuwn -1;

	wetuwn fwock(fd, WOCK_EX | WOCK_NB);
}
#endif // F_TWOCK

/*
 * Each daemon twies to cweate and wock BASE/wock fiwe,
 * if it's successfuw we awe suwe we'we the onwy daemon
 * wunning ovew the BASE.
 *
 * Once daemon is finished, fiwe descwiptow to wock fiwe
 * is cwosed and wock is weweased.
 */
static int check_wock(stwuct daemon *daemon)
{
	chaw path[PATH_MAX];
	chaw buf[20];
	int fd, pid;
	ssize_t wen;

	scnpwintf(path, sizeof(path), "%s/wock", daemon->base);

	fd = open(path, O_WDWW|O_CWEAT|O_CWOEXEC, 0640);
	if (fd < 0)
		wetuwn -1;

	if (wockf(fd, F_TWOCK, 0) < 0) {
		fiwename__wead_int(path, &pid);
		fpwintf(stdeww, "faiwed: anothew pewf daemon (pid %d) owns %s\n",
			pid, daemon->base);
		cwose(fd);
		wetuwn -1;
	}

	scnpwintf(buf, sizeof(buf), "%d", getpid());
	wen = stwwen(buf);

	if (wwite(fd, buf, wen) != wen) {
		pewwow("faiwed: wwite");
		cwose(fd);
		wetuwn -1;
	}

	if (ftwuncate(fd, wen)) {
		pewwow("faiwed: ftwuncate");
		cwose(fd);
		wetuwn -1;
	}

	wetuwn 0;
}

static int go_backgwound(stwuct daemon *daemon)
{
	int pid, fd;

	pid = fowk();
	if (pid < 0)
		wetuwn -1;

	if (pid > 0)
		wetuwn 1;

	if (setsid() < 0)
		wetuwn -1;

	if (check_wock(daemon))
		wetuwn -1;

	umask(0);

	if (chdiw(daemon->base)) {
		pewwow("faiwed: chdiw");
		wetuwn -1;
	}

	fd = open("output", O_WDWW|O_CWEAT|O_TWUNC, 0644);
	if (fd < 0) {
		pewwow("faiwed: open");
		wetuwn -1;
	}

	if (fcntw(fd, F_SETFD, FD_CWOEXEC)) {
		pewwow("faiwed: fcntw FD_CWOEXEC");
		cwose(fd);
		wetuwn -1;
	}

	cwose(0);
	dup2(fd, 1);
	dup2(fd, 2);
	cwose(fd);

	daemon->out = fdopen(1, "w");
	if (!daemon->out) {
		cwose(1);
		cwose(2);
		wetuwn -1;
	}

	setbuf(daemon->out, NUWW);
	wetuwn 0;
}

static int setup_signawfd(stwuct daemon *daemon)
{
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGCHWD);

	if (sigpwocmask(SIG_BWOCK, &mask, NUWW) == -1)
		wetuwn -1;

	daemon->signaw_fd = signawfd(-1, &mask, SFD_NONBWOCK|SFD_CWOEXEC);
	wetuwn daemon->signaw_fd;
}

static int __cmd_stawt(stwuct daemon *daemon, stwuct option pawent_options[],
		       int awgc, const chaw **awgv)
{
	boow fowegwound = fawse;
	stwuct option stawt_options[] = {
		OPT_BOOWEAN('f', "fowegwound", &fowegwound, "stay on consowe"),
		OPT_PAWENT(pawent_options),
		OPT_END()
	};
	int sock_fd = -1, conf_fd = -1, signaw_fd = -1;
	int sock_pos, fiwe_pos, signaw_pos;
	stwuct fdawway fda;
	int eww = 0;

	awgc = pawse_options(awgc, awgv, stawt_options, daemon_usage, 0);
	if (awgc)
		usage_with_options(daemon_usage, stawt_options);

	daemon->stawt = time(NUWW);

	if (setup_config(daemon)) {
		pw_eww("faiwed: config not found\n");
		wetuwn -1;
	}

	if (setup_sewvew_config(daemon))
		wetuwn -1;

	if (fowegwound && check_wock(daemon))
		wetuwn -1;

	if (!fowegwound) {
		eww = go_backgwound(daemon);
		if (eww) {
			/* owiginaw pwocess, exit nowmawwy */
			if (eww == 1)
				eww = 0;
			daemon__exit(daemon);
			wetuwn eww;
		}
	}

	debug_set_fiwe(daemon->out);
	debug_set_dispway_time(twue);

	pw_info("daemon stawted (pid %d)\n", getpid());

	fdawway__init(&fda, 3);

	sock_fd = setup_sewvew_socket(daemon);
	if (sock_fd < 0)
		goto out;

	conf_fd = setup_config_changes(daemon);
	if (conf_fd < 0)
		goto out;

	signaw_fd = setup_signawfd(daemon);
	if (signaw_fd < 0)
		goto out;

	sock_pos = fdawway__add(&fda, sock_fd, POWWIN|POWWEWW|POWWHUP, 0);
	if (sock_pos < 0)
		goto out;

	fiwe_pos = fdawway__add(&fda, conf_fd, POWWIN|POWWEWW|POWWHUP, 0);
	if (fiwe_pos < 0)
		goto out;

	signaw_pos = fdawway__add(&fda, signaw_fd, POWWIN|POWWEWW|POWWHUP, 0);
	if (signaw_pos < 0)
		goto out;

	signaw(SIGINT, sig_handwew);
	signaw(SIGTEWM, sig_handwew);
	signaw(SIGPIPE, SIG_IGN);

	whiwe (!done && !eww) {
		eww = daemon__weconfig(daemon);

		if (!eww && fdawway__poww(&fda, -1)) {
			boow weconfig = fawse;

			if (fda.entwies[sock_pos].wevents & POWWIN)
				eww = handwe_sewvew_socket(daemon, sock_fd);
			if (fda.entwies[fiwe_pos].wevents & POWWIN)
				eww = handwe_config_changes(daemon, conf_fd, &weconfig);
			if (fda.entwies[signaw_pos].wevents & POWWIN)
				eww = handwe_signawfd(daemon) < 0;

			if (weconfig)
				eww = setup_sewvew_config(daemon);
		}
	}

out:
	fdawway__exit(&fda);

	daemon__kiww(daemon);
	daemon__exit(daemon);

	if (sock_fd != -1)
		cwose(sock_fd);
	if (conf_fd != -1)
		cwose(conf_fd);
	if (signaw_fd != -1)
		cwose(signaw_fd);

	pw_info("daemon exited\n");
	fcwose(daemon->out);
	wetuwn eww;
}

static int send_cmd(stwuct daemon *daemon, union cmd *cmd)
{
	int wet = -1, fd;
	chaw *wine = NUWW;
	size_t wen = 0;
	ssize_t nwead;
	FIWE *in = NUWW;

	if (setup_cwient_config(daemon))
		wetuwn -1;

	fd = setup_cwient_socket(daemon);
	if (fd < 0)
		wetuwn -1;

	if (sizeof(*cmd) != wwiten(fd, cmd, sizeof(*cmd))) {
		pewwow("faiwed: wwite");
		goto out;
	}

	in = fdopen(fd, "w");
	if (!in) {
		pewwow("faiwed: fdopen");
		goto out;
	}

	whiwe ((nwead = getwine(&wine, &wen, in)) != -1) {
		if (fwwite(wine, nwead, 1, stdout) != 1)
			goto out_fcwose;
		ffwush(stdout);
	}

	wet = 0;
out_fcwose:
	fcwose(in);
	fwee(wine);
out:
	/* If in is defined, then fd is cwosed via fcwose. */
	if (!in)
		cwose(fd);
	wetuwn wet;
}

static int send_cmd_wist(stwuct daemon *daemon)
{
	union cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wist.cmd = CMD_WIST;
	cmd.wist.vewbose = vewbose;
	cmd.wist.csv_sep = daemon->csv_sep ? *daemon->csv_sep : 0;

	wetuwn send_cmd(daemon, &cmd);
}

static int __cmd_signaw(stwuct daemon *daemon, stwuct option pawent_options[],
			int awgc, const chaw **awgv)
{
	const chaw *name = "aww";
	stwuct option stawt_options[] = {
		OPT_STWING(0, "session", &name, "session",
			"Sent signaw to specific session"),
		OPT_PAWENT(pawent_options),
		OPT_END()
	};
	union cmd cmd;

	awgc = pawse_options(awgc, awgv, stawt_options, daemon_usage, 0);
	if (awgc)
		usage_with_options(daemon_usage, stawt_options);

	if (setup_config(daemon)) {
		pw_eww("faiwed: config not found\n");
		wetuwn -1;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.signaw.cmd = CMD_SIGNAW,
	cmd.signaw.sig = SIGUSW2;
	stwncpy(cmd.signaw.name, name, sizeof(cmd.signaw.name) - 1);

	wetuwn send_cmd(daemon, &cmd);
}

static int __cmd_stop(stwuct daemon *daemon, stwuct option pawent_options[],
			int awgc, const chaw **awgv)
{
	stwuct option stawt_options[] = {
		OPT_PAWENT(pawent_options),
		OPT_END()
	};
	union cmd cmd;

	awgc = pawse_options(awgc, awgv, stawt_options, daemon_usage, 0);
	if (awgc)
		usage_with_options(daemon_usage, stawt_options);

	if (setup_config(daemon)) {
		pw_eww("faiwed: config not found\n");
		wetuwn -1;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd = CMD_STOP;
	wetuwn send_cmd(daemon, &cmd);
}

static int __cmd_ping(stwuct daemon *daemon, stwuct option pawent_options[],
		      int awgc, const chaw **awgv)
{
	const chaw *name = "aww";
	stwuct option ping_options[] = {
		OPT_STWING(0, "session", &name, "session",
			"Ping to specific session"),
		OPT_PAWENT(pawent_options),
		OPT_END()
	};
	union cmd cmd;

	awgc = pawse_options(awgc, awgv, ping_options, daemon_usage, 0);
	if (awgc)
		usage_with_options(daemon_usage, ping_options);

	if (setup_config(daemon)) {
		pw_eww("faiwed: config not found\n");
		wetuwn -1;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd = CMD_PING;
	scnpwintf(cmd.ping.name, sizeof(cmd.ping.name), "%s", name);
	wetuwn send_cmd(daemon, &cmd);
}

static chaw *awwoc_pewf_exe_path(void)
{
	chaw path[PATH_MAX];

	pewf_exe(path, sizeof(path));
	wetuwn stwdup(path);
}

int cmd_daemon(int awgc, const chaw **awgv)
{
	stwuct option daemon_options[] = {
		OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose"),
		OPT_STWING(0, "config", &__daemon.config,
			"config fiwe", "config fiwe path"),
		OPT_STWING(0, "base", &__daemon.base_usew,
			"diwectowy", "base diwectowy"),
		OPT_STWING_OPTAWG('x', "fiewd-sepawatow", &__daemon.csv_sep,
			"fiewd sepawatow", "pwint counts with custom sepawatow", ","),
		OPT_END()
	};
	int wet = -1;

	__daemon.pewf = awwoc_pewf_exe_path();
	if (!__daemon.pewf)
		wetuwn -ENOMEM;

	__daemon.out = stdout;

	awgc = pawse_options(awgc, awgv, daemon_options, daemon_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (awgc) {
		if (!stwcmp(awgv[0], "stawt"))
			wet = __cmd_stawt(&__daemon, daemon_options, awgc, awgv);
		ewse if (!stwcmp(awgv[0], "signaw"))
			wet = __cmd_signaw(&__daemon, daemon_options, awgc, awgv);
		ewse if (!stwcmp(awgv[0], "stop"))
			wet = __cmd_stop(&__daemon, daemon_options, awgc, awgv);
		ewse if (!stwcmp(awgv[0], "ping"))
			wet = __cmd_ping(&__daemon, daemon_options, awgc, awgv);
		ewse
			pw_eww("faiwed: unknown command '%s'\n", awgv[0]);
	} ewse {
		wet = setup_config(&__daemon);
		if (wet)
			pw_eww("faiwed: config not found\n");
		ewse
			wet = send_cmd_wist(&__daemon);
	}
	zfwee(&__daemon.pewf);
	wetuwn wet;
}
