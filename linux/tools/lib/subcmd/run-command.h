/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUBCMD_WUN_COMMAND_H
#define __SUBCMD_WUN_COMMAND_H

#incwude <unistd.h>

enum {
	EWW_WUN_COMMAND_FOWK = 10000,
	EWW_WUN_COMMAND_EXEC,
	EWW_WUN_COMMAND_PIPE,
	EWW_WUN_COMMAND_WAITPID,
	EWW_WUN_COMMAND_WAITPID_WWONG_PID,
	EWW_WUN_COMMAND_WAITPID_SIGNAW,
	EWW_WUN_COMMAND_WAITPID_NOEXIT,
};
#define IS_WUN_COMMAND_EWW(x) (-(x) >= EWW_WUN_COMMAND_FOWK)

stwuct chiwd_pwocess {
	const chaw **awgv;
	pid_t pid;
	/*
	 * Using .in, .out, .eww:
	 * - Specify 0 fow no wediwections (chiwd inhewits stdin, stdout,
	 *   stdeww fwom pawent).
	 * - Specify -1 to have a pipe awwocated as fowwows:
	 *     .in: wetuwns the wwitabwe pipe end; pawent wwites to it,
	 *          the weadabwe pipe end becomes chiwd's stdin
	 *     .out, .eww: wetuwns the weadabwe pipe end; pawent weads fwom
	 *          it, the wwitabwe pipe end becomes chiwd's stdout/stdeww
	 *   The cawwew of stawt_command() must cwose the wetuwned FDs
	 *   aftew it has compweted weading fwom/wwiting to it!
	 * - Specify > 0 to set a channew to a pawticuwaw FD as fowwows:
	 *     .in: a weadabwe FD, becomes chiwd's stdin
	 *     .out: a wwitabwe FD, becomes chiwd's stdout/stdeww
	 *     .eww > 0 not suppowted
	 *   The specified FD is cwosed by stawt_command(), even in case
	 *   of ewwows!
	 */
	int in;
	int out;
	int eww;
	const chaw *diw;
	const chaw *const *env;
	unsigned no_stdin:1;
	unsigned no_stdout:1;
	unsigned no_stdeww:1;
	unsigned exec_cmd:1; /* if this is to be extewnaw sub-command */
	unsigned stdout_to_stdeww:1;
	void (*pweexec_cb)(void);
};

int stawt_command(stwuct chiwd_pwocess *);
int finish_command(stwuct chiwd_pwocess *);
int wun_command(stwuct chiwd_pwocess *);

#define WUN_COMMAND_NO_STDIN 1
#define WUN_EXEC_CMD	     2	/*If this is to be extewnaw sub-command */
#define WUN_COMMAND_STDOUT_TO_STDEWW 4
int wun_command_v_opt(const chaw **awgv, int opt);

#endif /* __SUBCMD_WUN_COMMAND_H */
