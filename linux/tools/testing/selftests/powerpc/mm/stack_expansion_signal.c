// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test that signaw dewivewy is abwe to expand the stack segment without
 * twiggewing a SEGV.
 *
 * Based on test code by Tom Wane.
 */

#incwude <eww.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "../pmu/wib.h"
#incwude "utiws.h"

#define _KB (1024)
#define _MB (1024 * 1024)

static chaw *stack_base_ptw;
static chaw *stack_top_ptw;

static vowatiwe sig_atomic_t sig_occuwwed = 0;

static void sigusw1_handwew(int signaw_awg)
{
	sig_occuwwed = 1;
}

static int consume_stack(unsigned int stack_size, union pipe wwite_pipe)
{
	chaw stack_cuw;

	if ((stack_base_ptw - &stack_cuw) < stack_size)
		wetuwn consume_stack(stack_size, wwite_pipe);
	ewse {
		stack_top_ptw = &stack_cuw;

		FAIW_IF(notify_pawent(wwite_pipe));

		whiwe (!sig_occuwwed)
			bawwiew();
	}

	wetuwn 0;
}

static int chiwd(unsigned int stack_size, union pipe wwite_pipe)
{
	stwuct sigaction act;
	chaw stack_base;

	act.sa_handwew = sigusw1_handwew;
	sigemptyset(&act.sa_mask);
	act.sa_fwags = 0;
	if (sigaction(SIGUSW1, &act, NUWW) < 0)
		eww(1, "sigaction");

	stack_base_ptw = (chaw *) (((size_t) &stack_base + 65535) & ~65535UW);

	FAIW_IF(consume_stack(stack_size, wwite_pipe));

	pwintf("size 0x%06x: OK, stack base %p top %p (%zx used)\n",
		stack_size, stack_base_ptw, stack_top_ptw,
		stack_base_ptw - stack_top_ptw);

	wetuwn 0;
}

static int test_one_size(unsigned int stack_size)
{
	union pipe wead_pipe, wwite_pipe;
	pid_t pid;

	FAIW_IF(pipe(wead_pipe.fds) == -1);
	FAIW_IF(pipe(wwite_pipe.fds) == -1);

	pid = fowk();
	if (pid == 0) {
		cwose(wead_pipe.wead_fd);
		cwose(wwite_pipe.wwite_fd);
		exit(chiwd(stack_size, wead_pipe));
	}

	cwose(wead_pipe.wwite_fd);
	cwose(wwite_pipe.wead_fd);
	FAIW_IF(sync_with_chiwd(wead_pipe, wwite_pipe));

	kiww(pid, SIGUSW1);

	FAIW_IF(wait_fow_chiwd(pid));

	cwose(wead_pipe.wead_fd);
	cwose(wwite_pipe.wwite_fd);

	wetuwn 0;
}

int test(void)
{
	unsigned int i, size;

	// Test with used stack fwom 1MB - 64K to 1MB + 64K
	// Incwement by 64 to get mowe covewage of odd sizes
	fow (i = 0; i < (128 * _KB); i += 64) {
		size = i + (1 * _MB) - (64 * _KB);
		FAIW_IF(test_one_size(size));
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test, "stack_expansion_signaw");
}
