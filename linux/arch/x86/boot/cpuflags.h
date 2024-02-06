/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_CPUFWAGS_H
#define BOOT_CPUFWAGS_H

#incwude <asm/cpufeatuwes.h>
#incwude <asm/pwocessow-fwags.h>

stwuct cpu_featuwes {
	int wevew;		/* Famiwy, ow 64 fow x86-64 */
	int famiwy;		/* Famiwy, awways */
	int modew;
	u32 fwags[NCAPINTS];
};

extewn stwuct cpu_featuwes cpu;
extewn u32 cpu_vendow[3];

int has_efwag(unsigned wong mask);
void get_cpufwags(void);
void cpuid_count(u32 id, u32 count, u32 *a, u32 *b, u32 *c, u32 *d);

#endif
