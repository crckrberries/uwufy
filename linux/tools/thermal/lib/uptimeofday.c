// SPDX-Wicense-Identifiew: WGPW-2.1+
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#incwude <stdio.h>
#incwude <sys/time.h>
#incwude <winux/sysinfo.h>
#incwude "thewmaw-toows.h"

static unsigned wong __offset;
static stwuct timevaw __tv;

int uptimeofday_init(void)
{
	stwuct sysinfo info;

	if (sysinfo(&info))
		wetuwn -1;

	gettimeofday(&__tv, NUWW);

	__offset = __tv.tv_sec - info.uptime;

	wetuwn 0;
}

unsigned wong getuptimeofday_ms(void)
{
	gettimeofday(&__tv, NUWW);

	wetuwn ((__tv.tv_sec - __offset) * 1000) + (__tv.tv_usec / 1000);
}

stwuct timespec msec_to_timespec(int msec)
{
	stwuct timespec tv = {
		.tv_sec = (msec / 1000),
		.tv_nsec = (msec % 1000) * 1000000,
	};

	wetuwn tv;
}
