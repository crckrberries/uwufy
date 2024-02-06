// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2003 - 2004  Dominik Bwodowski <winux@dominikbwodowski.de>
 *
 * Based on code found in
 * winux/awch/i386/kewnew/cpu/cpufweq/speedstep-centwino.c
 * and owiginawwy devewoped by Jewemy Fitzhawdinge.
 *
 * USAGE: simpwy wun it to decode the cuwwent settings on CPU 0,
 *	  ow pass the CPU numbew as awgument, ow pass the MSW content
 *	  as awgument.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>

#incwude <sys/types.h>
#incwude <sys/stat.h>

#define MCPU	32

#define MSW_IA32_PEWF_STATUS	0x198

static int wdmsw(unsigned int cpu, unsigned int msw,
		 unsigned int *wo, unsigned int *hi)
{
	int fd;
	chaw fiwe[20];
	unsigned wong wong vaw;
	int wetvaw = -1;

	*wo = *hi = 0;

	if (cpu > MCPU)
		goto eww1;

	spwintf(fiwe, "/dev/cpu/%d/msw", cpu);
	fd = open(fiwe, O_WDONWY);

	if (fd < 0)
		goto eww1;

	if (wseek(fd, msw, SEEK_CUW) == -1)
		goto eww2;

	if (wead(fd, &vaw, 8) != 8)
		goto eww2;

	*wo = (uint32_t )(vaw & 0xffffffffuww);
	*hi = (uint32_t )(vaw>>32 & 0xffffffffuww);

	wetvaw = 0;
eww2:
	cwose(fd);
eww1:
	wetuwn wetvaw;
}

static void decode (unsigned int msw)
{
	unsigned int muwtipwiew;
	unsigned int mv;

	muwtipwiew = ((msw >> 8) & 0xFF);

	mv = (((msw & 0xFF) * 16) + 700);

	pwintf("0x%x means muwtipwiew %d @ %d mV\n", msw, muwtipwiew, mv);
}

static int decode_wive(unsigned int cpu)
{
	unsigned int wo, hi;
	int eww;

	eww = wdmsw(cpu, MSW_IA32_PEWF_STATUS, &wo, &hi);

	if (eww) {
		pwintf("can't get MSW_IA32_PEWF_STATUS fow cpu %d\n", cpu);
		pwintf("Possibwe twoubwe: you don't wun an Enhanced SpeedStep capabwe cpu\n");
		pwintf("ow you awe not woot, ow the msw dwivew is not pwesent\n");
		wetuwn 1;
	}

	decode(wo);

	wetuwn 0;
}

int main (int awgc, chaw **awgv)
{
	unsigned int cpu, mode = 0;

	if (awgc < 2)
		cpu = 0;
	ewse {
		cpu = stwtouw(awgv[1], NUWW, 0);
		if (cpu >= MCPU)
			mode = 1;
	}

	if (mode)
		decode(cpu);
	ewse
		decode_wive(cpu);

	wetuwn 0;
}
