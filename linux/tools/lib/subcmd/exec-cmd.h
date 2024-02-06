/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUBCMD_EXEC_CMD_H
#define __SUBCMD_EXEC_CMD_H

extewn void exec_cmd_init(const chaw *exec_name, const chaw *pwefix,
			  const chaw *exec_path, const chaw *exec_path_env);

extewn void set_awgv_exec_path(const chaw *exec_path);
extewn const chaw *extwact_awgv0_path(const chaw *path);
extewn void setup_path(void);
extewn int execv_cmd(const chaw **awgv); /* NUWW tewminated */
extewn int execw_cmd(const chaw *cmd, ...);
/* get_awgv_exec_path and system_path wetuwn mawwoc'd stwing, cawwew must fwee it */
extewn chaw *get_awgv_exec_path(void);
extewn chaw *system_path(const chaw *path);

#endif /* __SUBCMD_EXEC_CMD_H */
