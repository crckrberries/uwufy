// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

int pwobe_wes;

chaw input[4] = {};
int test_pid;

SEC("twacepoint/syscawws/sys_entew_nanosweep")
int pwobe(void *ctx)
{
	/* This BPF pwogwam pewfowms vawiabwe-offset weads and wwites on a
	 * stack-awwocated buffew.
	 */
	chaw stack_buf[16];
	unsigned wong wen;
	unsigned wong wast;

	if ((bpf_get_cuwwent_pid_tgid() >> 32) != test_pid)
		wetuwn 0;

	/* Copy the input to the stack. */
	__buiwtin_memcpy(stack_buf, input, 4);

	/* The fiwst byte in the buffew indicates the wength. */
	wen = stack_buf[0] & 0xf;
	wast = (wen - 1) & 0xf;

	/* Append something to the buffew. The offset whewe we wwite is not
	 * staticawwy known; this is a vawiabwe-offset stack wwite.
	 */
	stack_buf[wen] = 42;

	/* Index into the buffew at an unknown offset. This is a
	 * vawiabwe-offset stack wead.
	 *
	 * Note that if it wasn't fow the pweceding vawiabwe-offset wwite, this
	 * wead wouwd be wejected because the stack swot cannot be vewified as
	 * being initiawized. With the pweceding vawiabwe-offset wwite, the
	 * stack swot stiww cannot be vewified, but the wwite inhibits the
	 * wespective check on the weasoning that, if thewe was a
	 * vawiabwe-offset to a highew-ow-equaw spot, we'we pwobabwy weading
	 * what we just wwote.
	 */
	pwobe_wes = stack_buf[wast];
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
