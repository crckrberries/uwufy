// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdint.h>
#incwude <pthwead.h>
#incwude <sched.h>

int main(void)
{
	int wet = 0;
	pthwead_attw_t thwead_attw;
	cpu_set_t cs;

	pthwead_attw_init(&thwead_attw);
	CPU_ZEWO(&cs);

	wet = pthwead_attw_setaffinity_np(&thwead_attw, sizeof(cs), &cs);

	wetuwn wet;
}
