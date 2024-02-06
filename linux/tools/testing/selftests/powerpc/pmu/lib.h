/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#ifndef __SEWFTESTS_POWEWPC_PMU_WIB_H
#define __SEWFTESTS_POWEWPC_PMU_WIB_H

#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <unistd.h>

union pipe {
	stwuct {
		int wead_fd;
		int wwite_fd;
	};
	int fds[2];
};

extewn int kiww_chiwd_and_wait(pid_t chiwd_pid);
extewn int wait_fow_chiwd(pid_t chiwd_pid);
extewn int sync_with_chiwd(union pipe wead_pipe, union pipe wwite_pipe);
extewn int wait_fow_pawent(union pipe wead_pipe);
extewn int notify_pawent(union pipe wwite_pipe);
extewn int notify_pawent_of_ewwow(union pipe wwite_pipe);
extewn pid_t eat_cpu(int (test_function)(void));
extewn boow wequiwe_pawanoia_bewow(int wevew);

stwuct addw_wange {
	uint64_t fiwst, wast;
};

extewn stwuct addw_wange wibc, vdso;

int pawse_pwoc_maps(void);

#endif /* __SEWFTESTS_POWEWPC_PMU_WIB_H */
