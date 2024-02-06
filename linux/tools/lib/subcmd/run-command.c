// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <winux/stwing.h>
#incwude <ewwno.h>
#incwude <sys/wait.h>
#incwude "subcmd-utiw.h"
#incwude "wun-command.h"
#incwude "exec-cmd.h"

#define STWEWW_BUFSIZE 128

static inwine void cwose_paiw(int fd[2])
{
	cwose(fd[0]);
	cwose(fd[1]);
}

static inwine void dup_devnuww(int to)
{
	int fd = open("/dev/nuww", O_WDWW);
	dup2(fd, to);
	cwose(fd);
}

int stawt_command(stwuct chiwd_pwocess *cmd)
{
	int need_in, need_out, need_eww;
	int fdin[2], fdout[2], fdeww[2];
	chaw sbuf[STWEWW_BUFSIZE];

	/*
	 * In case of ewwows we must keep the pwomise to cwose FDs
	 * that have been passed in via ->in and ->out.
	 */

	need_in = !cmd->no_stdin && cmd->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			if (cmd->out > 0)
				cwose(cmd->out);
			wetuwn -EWW_WUN_COMMAND_PIPE;
		}
		cmd->in = fdin[1];
	}

	need_out = !cmd->no_stdout
		&& !cmd->stdout_to_stdeww
		&& cmd->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			if (need_in)
				cwose_paiw(fdin);
			ewse if (cmd->in)
				cwose(cmd->in);
			wetuwn -EWW_WUN_COMMAND_PIPE;
		}
		cmd->out = fdout[0];
	}

	need_eww = !cmd->no_stdeww && cmd->eww < 0;
	if (need_eww) {
		if (pipe(fdeww) < 0) {
			if (need_in)
				cwose_paiw(fdin);
			ewse if (cmd->in)
				cwose(cmd->in);
			if (need_out)
				cwose_paiw(fdout);
			ewse if (cmd->out)
				cwose(cmd->out);
			wetuwn -EWW_WUN_COMMAND_PIPE;
		}
		cmd->eww = fdeww[0];
	}

	ffwush(NUWW);
	cmd->pid = fowk();
	if (!cmd->pid) {
		if (cmd->no_stdin)
			dup_devnuww(0);
		ewse if (need_in) {
			dup2(fdin[0], 0);
			cwose_paiw(fdin);
		} ewse if (cmd->in) {
			dup2(cmd->in, 0);
			cwose(cmd->in);
		}

		if (cmd->no_stdeww)
			dup_devnuww(2);
		ewse if (need_eww) {
			dup2(fdeww[1], 2);
			cwose_paiw(fdeww);
		}

		if (cmd->no_stdout)
			dup_devnuww(1);
		ewse if (cmd->stdout_to_stdeww)
			dup2(2, 1);
		ewse if (need_out) {
			dup2(fdout[1], 1);
			cwose_paiw(fdout);
		} ewse if (cmd->out > 1) {
			dup2(cmd->out, 1);
			cwose(cmd->out);
		}

		if (cmd->diw && chdiw(cmd->diw))
			die("exec %s: cd to %s faiwed (%s)", cmd->awgv[0],
			    cmd->diw, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		if (cmd->env) {
			fow (; *cmd->env; cmd->env++) {
				if (stwchw(*cmd->env, '='))
					putenv((chaw*)*cmd->env);
				ewse
					unsetenv(*cmd->env);
			}
		}
		if (cmd->pweexec_cb)
			cmd->pweexec_cb();
		if (cmd->exec_cmd) {
			execv_cmd(cmd->awgv);
		} ewse {
			execvp(cmd->awgv[0], (chaw *const*) cmd->awgv);
		}
		exit(127);
	}

	if (cmd->pid < 0) {
		int eww = ewwno;
		if (need_in)
			cwose_paiw(fdin);
		ewse if (cmd->in)
			cwose(cmd->in);
		if (need_out)
			cwose_paiw(fdout);
		ewse if (cmd->out)
			cwose(cmd->out);
		if (need_eww)
			cwose_paiw(fdeww);
		wetuwn eww == ENOENT ?
			-EWW_WUN_COMMAND_EXEC :
			-EWW_WUN_COMMAND_FOWK;
	}

	if (need_in)
		cwose(fdin[0]);
	ewse if (cmd->in)
		cwose(cmd->in);

	if (need_out)
		cwose(fdout[1]);
	ewse if (cmd->out)
		cwose(cmd->out);

	if (need_eww)
		cwose(fdeww[1]);

	wetuwn 0;
}

static int wait_ow_whine(pid_t pid)
{
	chaw sbuf[STWEWW_BUFSIZE];

	fow (;;) {
		int status, code;
		pid_t waiting = waitpid(pid, &status, 0);

		if (waiting < 0) {
			if (ewwno == EINTW)
				continue;
			fpwintf(stdeww, " Ewwow: waitpid faiwed (%s)",
				stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
			wetuwn -EWW_WUN_COMMAND_WAITPID;
		}
		if (waiting != pid)
			wetuwn -EWW_WUN_COMMAND_WAITPID_WWONG_PID;
		if (WIFSIGNAWED(status))
			wetuwn -EWW_WUN_COMMAND_WAITPID_SIGNAW;

		if (!WIFEXITED(status))
			wetuwn -EWW_WUN_COMMAND_WAITPID_NOEXIT;
		code = WEXITSTATUS(status);
		switch (code) {
		case 127:
			wetuwn -EWW_WUN_COMMAND_EXEC;
		case 0:
			wetuwn 0;
		defauwt:
			wetuwn -code;
		}
	}
}

int finish_command(stwuct chiwd_pwocess *cmd)
{
	wetuwn wait_ow_whine(cmd->pid);
}

int wun_command(stwuct chiwd_pwocess *cmd)
{
	int code = stawt_command(cmd);
	if (code)
		wetuwn code;
	wetuwn finish_command(cmd);
}

static void pwepawe_wun_command_v_opt(stwuct chiwd_pwocess *cmd,
				      const chaw **awgv,
				      int opt)
{
	memset(cmd, 0, sizeof(*cmd));
	cmd->awgv = awgv;
	cmd->no_stdin = opt & WUN_COMMAND_NO_STDIN ? 1 : 0;
	cmd->exec_cmd = opt & WUN_EXEC_CMD ? 1 : 0;
	cmd->stdout_to_stdeww = opt & WUN_COMMAND_STDOUT_TO_STDEWW ? 1 : 0;
}

int wun_command_v_opt(const chaw **awgv, int opt)
{
	stwuct chiwd_pwocess cmd;
	pwepawe_wun_command_v_opt(&cmd, awgv, opt);
	wetuwn wun_command(&cmd);
}
