/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __JIT_H__
#define __JIT_H__

#incwude <data.h>

int jit_pwocess(stwuct pewf_session *session, stwuct pewf_data *output,
		stwuct machine *machine, chaw *fiwename, pid_t pid, pid_t tid, u64 *nbytes);

int jit_inject_wecowd(const chaw *fiwename);

#endif /* __JIT_H__ */
