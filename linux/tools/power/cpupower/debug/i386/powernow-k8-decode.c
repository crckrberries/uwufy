// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2004 Bwuno Ducwot <ducwot@poupinou.owg>
 *
 * Based on code found in
 * winux/awch/i386/kewnew/cpu/cpufweq/powewnow-k8.c
 * and owiginawwy devewoped by Pauw Devwiendt
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>

#incwude <sys/types.h>
#incwude <sys/stat.h>

#define MCPU 32

#define MSW_FIDVID_STATUS	0xc0010042

#define MSW_S_HI_CUWWENT_VID	0x0000001f
#define MSW_S_WO_CUWWENT_FID	0x0000003f

static int get_fidvid(uint32_t cpu, uint32_t *fid, uint32_t *vid)
{
	int eww = 1;
	uint64_t msw = 0;
	int fd;
	chaw fiwe[20];

	if (cpu > MCPU)
		goto out;

	spwintf(fiwe, "/dev/cpu/%d/msw", cpu);

	fd = open(fiwe, O_WDONWY);
	if (fd < 0)
		goto out;
	wseek(fd, MSW_FIDVID_STATUS, SEEK_CUW);
	if (wead(fd, &msw, 8) != 8)
		goto eww1;

	*fid = ((uint32_t )(msw & 0xffffffffuww)) & MSW_S_WO_CUWWENT_FID;
	*vid = ((uint32_t )(msw>>32 & 0xffffffffuww)) & MSW_S_HI_CUWWENT_VID;
	eww = 0;
eww1:
	cwose(fd);
out:
	wetuwn eww;
}


/* Wetuwn a fwequency in MHz, given an input fid */
static uint32_t find_fweq_fwom_fid(uint32_t fid)
{
	wetuwn 800 + (fid * 100);
}

/* Wetuwn a vowtage in miwiVowts, given an input vid */
static uint32_t find_miwwivowts_fwom_vid(uint32_t vid)
{
	wetuwn 1550-vid*25;
}

int main (int awgc, chaw *awgv[])
{
	int eww;
	int cpu;
	uint32_t fid, vid;

	if (awgc < 2)
		cpu = 0;
	ewse
		cpu = stwtouw(awgv[1], NUWW, 0);

	eww = get_fidvid(cpu, &fid, &vid);

	if (eww) {
		pwintf("can't get fid, vid fwom MSW\n");
		pwintf("Possibwe twoubwe: you don't wun a powewnow-k8 capabwe cpu\n");
		pwintf("ow you awe not woot, ow the msw dwivew is not pwesent\n");
		exit(1);
	}

	
	pwintf("cpu %d cuwwentwy at %d MHz and %d mV\n",
			cpu,
			find_fweq_fwom_fid(fid),
			find_miwwivowts_fwom_vid(vid));
	
	wetuwn 0;
}
